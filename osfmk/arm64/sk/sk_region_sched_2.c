/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 *
 * Sub-range 2: 0x1a0000 - 0x1b0000 — scheduler + Swift runtime / collection machinery
 * (size-class selection, array/collection allocation, thread & sched-context plumbing,
 * run-queue iteration, preemption/fatal-error paths). Uses seL4/cL4 vocabulary.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Shared kernel / out-of-range helpers (FUN_ address in comment; bodies
 * reconstructed by sibling range workers). Names are estimates.
 * ------------------------------------------------------------------ */

/* Allocator / object primitives (region 0x0034xxxx-0x0037xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);               /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);         /* FUN_0036b270 */
extern void sk_free(void *ptr);                                             /* FUN_0036b118 */
extern void *sk_alloc_special(unsigned long a, unsigned long b, unsigned long tag); /* FUN_0036a940 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *dbg1, void *dbg2); /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a);                          /* FUN_00377bec */
extern unsigned long sk_lzcount(uint32_t v);                                /* LZCOUNT intrinsic */
extern reg16 sk_cpu_current(void);                                   /* FUN_0008e518 */
extern void sk_thread_epilogue(void);                                       /* FUN_0008e500 */
extern void sk_swift_fatal(const char *p1, uint64_t p2, uint32_t p3, ...);

/* Swift runtime collection alloc helpers. */
extern void *swift_array_alloc_with_count(uint64_t a, void *b);             /* FUN_003a25d4 */
extern void *swift_objc_metatype(void);                                     /* FUN_00376820 */
extern void *swift_array_init(void);                                        /* FUN_001a042c */
extern void *swift_alloc_small(uint64_t a, uint64_t b, uint64_t c);         /* FUN_003a261c */

/* Current-thread / misc helpers (region 0x0008xxxx / 0x0001xxxx). */
extern void *sk_current_tcb(void);                                          /* FUN_000867ec */
extern void sk_schedule_yield(void);                                        /* FUN_00084180 */


/* ==================================================================== *
 * compile-fix: generated declarations (register pseudos, types, externs)      *
 * ==================================================================== */
typedef uint64_t undefined8; typedef uint8_t undefined1; typedef uint64_t undefined;
typedef uint8_t byte; typedef uint16_t ushort; typedef uint32_t uint; typedef uint64_t ulong;
typedef uint64_t code;
typedef struct { uint64_t lo; uint64_t hi; } reg16;
typedef void (*code_fn)(void);

/* Ghidra CONCAT / borrow-carry / sign-extend helpers. */
static inline uint64_t CONCAT17(uint64_t a, uint64_t b){ return (a<<8)|(b&0xff); }
static inline uint64_t CONCAT71(uint64_t a, uint64_t b){ return (a<<7)|(b&0x7f); }
static inline uint64_t SBORROW8(uint64_t a, uint64_t b){ return ((int64_t)a < (int64_t)b); }
static inline uint64_t SCARRY8(uint64_t a, uint64_t b){ return (((uint64_t)a + (uint64_t)b) < (uint64_t)a); }
static inline uint64_t SEXT816(uint64_t v){ return (uint64_t)(int64_t)(int8_t)(v & 0xff); }
static inline uint64_t SUB168(uint64_t a, uint64_t b){ return a-b; }

/* Leaked register / pseudo-stack identifiers (compile-fix globals). */
uint64_t NG, OV, ZR, a0, a1, a2, als_50, aus_108, aus_130, aus_20, aus_28, aus_50, aus_58, aus_60, aus_78, aus_8, aus_90, aus_98, aus_b8, buf, cpu, cur, fatal_str, flags, i, is_0, is_10, is_18, is_20, is_28, is_30, is_38, is_40, is_48, is_60, is_68, is_8, is_e0, is_fff8, local, ls_38, ls_40, ls_50, ls_68, lv12, lv3, lv4, next, node, obj, out, r, reg12, s, slot_ptr, src, stack, stack_18, stack_20, stack_28, stack_2c, stack_2e, stack_2f, stack_30, stack_38, stack_40, stack_48, stack_50, stack_8, stack_88, stack_aligned, stack_arg, stack_buf, stack_d0, stack_e8, sv_10, sv_18, sv_20, sv_28, sv_30, sv_31, sv_32, sv_34, sv_37, sv_38, sv_39, sv_40, sv_47, sv_48, sv_50, sv_51, sv_52, sv_54, sv_58, sv_60, sv_64, sv_68, sv_70, sv_8, sv_80, sv_88, sv_90, sv_a0, sv_a8, sv_b0, sv_c0, sv_c8, sv_d8, sv_e0, sv_f0, u4, u8, us_24, us_28, us_2c, us_2e, us_2f, us_30, us_38, us_3f, us_40, us_48, us_50, us_58, us_68, us_78, us_88, us_a0, us_d0, us_d8, us_e8, v, v13b, v14, v14b, v19, v2, v5, v6, v7, v8, vv, w1, w10, w11, w14, w19, w4, w8, w9, x1, x10, x11, x11_00, x12, x13, x14, x15, x16, x16_00, x16_01, x19, x1_00, x1_02, x1_03, x20, x21, x22, x23, x24, x25, x26, x27, x28, x3, x30, x4, x5, x6, x7, x8, x8_00, x8_01, x8_02, x8_03, x8_04, x8_05, x8_06, x8_07, x8_08, x8_09, x8_10, x8_11, x8_13, x8_14, x9, x9_00, x9_01;
reg16 cpu, node, out, r, s, src, v, v14, v14b, v19, v2, v5, v6, v7, vv, x15;
uint64_t *obj, sv_10, sv_40, x20, x22, x25, x26, x3, x8, x8_07;
void (*entry)(void), (*fn)(void), (*fn1)(void), (*fn10)(void), (*fn12)(void), (*fn14)(void), (*fn17)(void), (*fn2)(void), (*fn3)(void), (*fn5)(void), (*fn5c)(void), (*fn6)(void), (*fn6b)(void), (*fn7)(void), (*fn8)(void), (*fn9)(void), (*jumptable)(void), (*x19_fn)(void), (*x20_fn)(void), (*x24_fn)(void), (*x25_fn)(void), (*x26_fn)(void), (*x27_fn)(void), (*x8_00_fn)(void), (*x8_01_fn)(void), (*x8_02_fn)(void), (*x8_03_fn)(void), (*x8_04_fn)(void), (*x8_05_fn)(void), (*x8_06_fn)(void), (*x8_07_fn)(void), (*x8_08_fn)(void), (*x8_09_fn)(void), (*x8_10_fn)(void), (*x8_11_fn)(void), (*x8_12_fn)(void), (*x8_13_fn)(void), (*x8_14_fn)(void), (*x8_15_fn)(void), (*x8_16_fn)(void), (*x8_17_fn)(void), (*x8_18_fn)(void), (*x8_19_fn)(void), (*x8_20_fn)(void), (*x8_21_fn)(void), (*x8_fn)(void), (*x9_00_fn)(void), (*x9_01_fn)(void), (*x9_02_fn)(void), (*x9_03_fn)(void), (*x9_04_fn)(void), (*x9_05_fn)(void), (*x9_06_fn)(void), (*x9_07_fn)(void), (*x9_08_fn)(void), (*x9_09_fn)(void), (*x9_10_fn)(void), (*x9_11_fn)(void), (*x9_12_fn)(void), (*x9_13_fn)(void), (*x9_14_fn)(void), (*x9_fn)(void);
void (*fn5b)(void), (*is_b8)(void);

/* Swift fatal/string constants (extern char arrays). */
extern char s_Fatal_error[]; extern char s_array_slice_with_unsafe_mut[]; extern char s_array_with_unsafe_mut[]; extern char s_buf_has_null[]; extern char s_cant_construct_array[]; extern char s_cant_remove_empty[]; extern char s_cant_remove_first[]; extern char s_cant_remove_last[]; extern char s_cant_remove_more[]; extern char s_cant_remove_more2[]; extern char s_count_must_not_neg[]; extern char s_identity_cast_wrong_type[]; extern char s_index_oob[]; extern char s_index_out_of_range[]; extern char s_insufficient_space[]; extern char s_invalid_less_than[]; extern char s_invalid_more_than[]; extern char s_num_to_remove[]; extern char s_range_requires[]; extern char s_reversed_key[]; extern char s_string_index_oob[]; extern char s_swift_array[]; extern char s_swift_array_slice[]; extern char s_swift_builtin[]; extern char s_swift_collection[]; extern char s_swift_contig_buf[]; extern char s_swift_optional[]; extern char s_swift_range[]; extern char s_swift_range_replaceable[]; extern char s_swift_span[]; extern char s_swift_string_utf16[]; extern char s_swift_unicode_helpers[]; extern char s_swift_unsafe_buf[]; extern char s_swift_valid_utf8[]; extern char s_unexpected_nil[]; extern char s_unsafe_mut_buf[]; extern char s_unsafely_unwrapped_nil[];
/* Data / memory symbols. */
extern uint64_t DAT_004baeb0, DAT_004c08a0, DAT_006adf10, DAT_006adf18, section_00000068, sk_array_metatype, sk_cstring, sk_empty_array, uRam_4baeb8, uRam_4c08a8;
extern uint64_t FUN_00072c0c, FUN_001a0d1c, FUN_002a9d64, FUN_00310d34, FUN_00319380, FUN_0031940c, FUN_00346744;

/* Forward declarations of in-file functions (used before definition). */
void sk_lock_guarded();
void sk_sched_queue_foreach();
void sk_swift_array_dispatch_impl();
void swift_array_destroy();
void swift_array_init_core();

/* Permissive externs for out-of-range helpers (arity unknown). */
extern uint64_t CONCAT17();
extern uint64_t CONCAT71();
extern uint64_t FUN_00002534();
extern uint64_t FUN_00002688();
extern uint64_t FUN_000026e8();
extern uint64_t FUN_00002834();
extern uint64_t FUN_00002850();
extern uint64_t FUN_0001a1c8();
extern reg16 FUN_0001d4a0();
extern uint64_t FUN_0001da84();
extern uint64_t FUN_00027614();
extern uint64_t FUN_00027754();
extern uint64_t FUN_00027788();
extern uint64_t FUN_000277b8();
extern reg16 FUN_00041138();
extern uint64_t FUN_00068e14();
extern uint64_t FUN_0006a4c0();
extern uint64_t FUN_0006b3f4();
extern uint64_t FUN_0006b42c();
extern uint64_t FUN_0006e778();
extern reg16 FUN_0006f6b4();
extern uint64_t FUN_0006f768();
extern uint64_t FUN_00071bd0();
extern uint64_t FUN_00077070();
extern uint64_t FUN_00077630();
extern uint64_t FUN_0007767c();
extern uint64_t FUN_00077698();
extern uint64_t FUN_000776cc();
extern uint64_t FUN_00077888();
extern uint64_t FUN_0007c028();
extern uint64_t FUN_0007c1a4();
extern uint64_t FUN_0007c1c4();
extern uint64_t FUN_000839d8();
extern uint64_t FUN_000839f8();
extern uint64_t FUN_00083a18();
extern reg16 FUN_0008409c();
extern reg16 FUN_00084180();
extern reg16 FUN_00084220();
extern uint64_t FUN_00084234();
extern uint64_t FUN_0008e0d4();
extern uint64_t FUN_0008e388();
extern uint64_t FUN_0008e518();
extern uint64_t FUN_0008f5f4();
extern uint64_t FUN_0008f6f4();
extern reg16 FUN_0009461c();
extern reg16 FUN_0009e234();
extern uint64_t FUN_000a6894();
extern uint64_t FUN_000a68f4();
extern uint64_t FUN_000a6f68();
extern uint64_t FUN_000a6f88();
extern uint64_t FUN_000a6fe0();
extern uint64_t FUN_000aa4ec();
extern uint64_t FUN_000b4390();
extern uint64_t FUN_000b43e8();
extern reg16 FUN_000b4594();
extern uint64_t FUN_000b45b0();
extern uint64_t FUN_000dbcc8();
extern uint64_t FUN_000dbd0c();
extern uint64_t FUN_000dbdf4();
extern uint64_t FUN_000dbe70();
extern uint64_t FUN_000dbf08();
extern uint64_t FUN_000e15d8();
extern uint64_t FUN_000e72b0();
extern reg16 FUN_00100c38();
extern uint64_t FUN_00100efc();
extern uint64_t FUN_0011e71c();
extern uint64_t FUN_0014ae44();
extern reg16 FUN_00167404();
extern reg16 FUN_0016749c();
extern uint64_t FUN_001676cc();
extern uint64_t FUN_0019c03c();
extern uint64_t FUN_0019c078();
extern uint64_t FUN_0019c20c();
extern uint64_t FUN_0019c258();
extern uint64_t FUN_0019c2fc();
extern uint64_t FUN_0019c44c();
extern uint64_t FUN_0019c53c();
extern uint64_t FUN_0019cb68();
extern uint64_t FUN_0019cc64();
extern uint64_t FUN_0019ce60();
extern uint64_t FUN_0019d15c();
extern uint64_t FUN_0019d40c();
extern uint64_t FUN_0019d6d0();
extern uint64_t FUN_0019da34();
extern uint64_t FUN_0019dadc();
extern uint64_t FUN_0019dd10();
extern uint64_t FUN_0019e538();
extern reg16 FUN_0019e578();
extern uint64_t FUN_0019e644();
extern reg16 FUN_0019e93c();
extern uint64_t FUN_0019ea20();
extern reg16 FUN_0019ed3c();
extern uint64_t FUN_0019f1ec();
extern uint64_t FUN_0019fa60();
extern uint64_t FUN_0019fd10();
extern uint64_t FUN_0019fe7c();
extern uint64_t FUN_001a0194();
extern uint64_t FUN_001a0414();
extern uint64_t FUN_001a0534();
extern uint64_t FUN_001a0640();
extern uint64_t FUN_001a06b8();
extern uint64_t FUN_001a0a70();
extern uint64_t FUN_001a0c98();
extern uint64_t FUN_001a0d1c();
extern uint64_t FUN_001a0dac();
extern uint64_t FUN_001a0fa4();
extern reg16 FUN_001a10d4();
extern reg16 FUN_001a10e4();
extern uint64_t FUN_001a1138();
extern uint64_t FUN_001a16e8();
extern uint64_t FUN_001a2128();
extern reg16 FUN_001a26e0();
extern uint64_t FUN_001a2740();
extern reg16 FUN_001a27f0();
extern uint64_t FUN_001a4554();
extern uint64_t FUN_001a4bbc();
extern uint64_t FUN_001a5110();
extern uint64_t FUN_001a5250();
extern uint64_t FUN_001a5968();
extern uint64_t FUN_001a5be8();
extern uint64_t FUN_001a67bc();
extern uint64_t FUN_001a6ab8();
extern uint64_t FUN_001a73cc();
extern uint64_t FUN_001a7914();
extern uint64_t FUN_001a7e5c();
extern uint64_t FUN_001a7fcc();
extern uint64_t FUN_001a8068();
extern uint64_t FUN_001a8368();
extern uint64_t FUN_001a842c();
extern uint64_t FUN_001a8498();
extern uint64_t FUN_001a84f4();
extern uint64_t FUN_001a8564();
extern uint64_t FUN_001a894c();
extern reg16 FUN_001a89a8();
extern uint64_t FUN_001a8b9c();
extern reg16 FUN_001a8cf0();
extern uint64_t FUN_001a9064();
extern uint64_t FUN_001a91c4();
extern uint64_t FUN_001a9640();
extern uint64_t FUN_001a964c();
extern uint64_t FUN_001a9714();
extern uint64_t FUN_001a97d4();
extern uint64_t FUN_001a983c();
extern uint64_t FUN_001a989c();
extern uint64_t FUN_001a9a84();
extern uint64_t FUN_001a9ac8();
extern uint64_t FUN_001a9b28();
extern reg16 FUN_001a9bf0();
extern uint64_t FUN_001a9c54();
extern uint64_t FUN_001a9cb8();
extern uint64_t FUN_001a9dd8();
extern uint64_t FUN_001aa318();
extern uint64_t FUN_001aa330();
extern uint64_t FUN_001aa538();
extern uint64_t FUN_001aa800();
extern uint64_t FUN_001aaa0c();
extern uint64_t FUN_001aab34();
extern reg16 FUN_001aab58();
extern reg16 FUN_001aad30();
extern uint64_t FUN_001aad64();
extern uint64_t FUN_001aadec();
extern uint64_t FUN_001aaef0();
extern uint64_t FUN_001ab008();
extern uint64_t FUN_001ab07c();
extern uint64_t FUN_001ab1ac();
extern uint64_t FUN_001ab52c();
extern uint64_t FUN_001ab924();
extern reg16 FUN_001ab9e0();
extern uint64_t FUN_001abe00();
extern uint64_t FUN_001ad190();
extern uint64_t FUN_001ad494();
extern uint64_t FUN_001ad668();
extern uint64_t FUN_001ad6e0();
extern reg16 FUN_001ad884();
extern uint64_t FUN_001adf20();
extern uint64_t FUN_001ae254();
extern uint64_t FUN_001aeab4();
extern reg16 FUN_001af990();
extern uint64_t FUN_001afa84();
extern uint64_t FUN_001afd38();
extern uint64_t FUN_001b012c();
extern uint64_t FUN_001b0174();
extern uint64_t FUN_001b05d8();
extern uint64_t FUN_001d2d1c();
extern reg16 FUN_001d96e0();
extern reg16 FUN_001d974c();
extern uint64_t FUN_001d9b18();
extern uint64_t FUN_001dd614();
extern uint64_t FUN_001de6c4();
extern uint64_t FUN_001de8a8();
extern uint64_t FUN_001dea60();
extern uint64_t FUN_001ded00();
extern uint64_t FUN_001dedf8();
extern uint64_t FUN_001defc8();
extern uint64_t FUN_001df334();
extern uint64_t FUN_001df428();
extern reg16 FUN_001dff60();
extern reg16 FUN_001e3730();
extern uint64_t FUN_001e5438();
extern uint64_t FUN_001e67d8();
extern uint64_t FUN_001e74ac();
extern uint64_t FUN_001ee030();
extern uint64_t FUN_001f1878();
extern uint64_t FUN_002060d4();
extern uint64_t FUN_0020c1bc();
extern uint64_t FUN_0020c5b0();
extern uint64_t FUN_0020c634();
extern reg16 FUN_0021398c();
extern uint64_t FUN_00228e78();
extern uint64_t FUN_00254fb4();
extern uint64_t FUN_00255324();
extern uint64_t FUN_00255d4c();
extern uint64_t FUN_00267510();
extern uint64_t FUN_00267820();
extern reg16 FUN_0026bd30();
extern uint64_t FUN_00273fe0();
extern uint64_t FUN_00281cc0();
extern uint64_t FUN_00281d4c();
extern uint64_t FUN_00281ef4();
extern uint64_t FUN_002821c4();
extern uint64_t FUN_00282bc0();
extern uint64_t FUN_00282e84();
extern uint64_t FUN_002830f4();
extern uint64_t FUN_00283290();
extern uint64_t FUN_002835c4();
extern uint64_t FUN_00283be4();
extern uint64_t FUN_00283d14();
extern uint64_t FUN_00283e7c();
extern reg16 FUN_00284148();
extern uint64_t FUN_0029b9a8();
extern uint64_t FUN_0029e8dc();
extern uint64_t FUN_0029fb80();
extern uint64_t FUN_002a4c98();
extern uint64_t FUN_002a5400();
extern uint64_t FUN_002a7c00();
extern uint64_t FUN_002a95b4();
extern reg16 FUN_002a9ba8();
extern uint64_t FUN_002a9d64();
extern uint64_t FUN_002ab4d4();
extern reg16 FUN_002ab5bc();
extern uint64_t FUN_002ab6a0();
extern uint64_t FUN_002ab8ac();
extern uint64_t FUN_002af74c();
extern uint64_t FUN_002afd38();
extern uint64_t FUN_002b0c84();
extern uint64_t FUN_002b3b84();
extern uint64_t FUN_002b4120();
extern reg16 FUN_002b439c();
extern uint64_t FUN_002b64cc();
extern uint64_t FUN_002b7088();
extern uint64_t FUN_002b71c4();
extern uint64_t FUN_002c8c2c();
extern reg16 FUN_002db6b8();
extern uint64_t FUN_002dc564();
extern uint64_t FUN_002dc5a4();
extern uint64_t FUN_002e1c9c();
extern uint64_t FUN_00310924();
extern uint64_t FUN_00310954();
extern uint64_t FUN_00310a14();
extern uint64_t FUN_00310aa4();
extern uint64_t FUN_00310ad4();
extern uint64_t FUN_00310b08();
extern uint64_t FUN_00310b68();
extern uint64_t FUN_00310bf8();
extern reg16 FUN_00310d34();
extern uint64_t FUN_00310d68();
extern reg16 FUN_00310d80();
extern uint64_t FUN_00310d98();
extern uint64_t FUN_00310da8();
extern uint64_t FUN_00310dd8();
extern uint64_t FUN_00310df0();
extern uint64_t FUN_00310e08();
extern uint64_t FUN_00310e20();
extern uint64_t FUN_00310f64();
extern uint64_t FUN_00310f94();
extern uint64_t FUN_00310fc4();
extern uint64_t FUN_003191e8();
extern uint64_t FUN_00319230();
extern uint64_t FUN_00319248();
extern uint64_t FUN_00319278();
extern uint64_t FUN_003192a8();
extern uint64_t FUN_003192d8();
extern uint64_t FUN_00319308();
extern uint64_t FUN_00319320();
extern uint64_t FUN_00319338();
extern uint64_t FUN_00319350();
extern uint64_t FUN_003193f4();
extern uint64_t FUN_0031945c();
extern uint64_t FUN_0031948c();
extern uint64_t FUN_003194e0();
extern uint64_t FUN_003194f8();
extern uint64_t FUN_00319568();
extern uint64_t FUN_00319598();
extern uint64_t FUN_003195b0();
extern uint64_t FUN_003195c8();
extern uint64_t FUN_003195f8();
extern uint64_t FUN_00319688();
extern uint64_t FUN_00319808();
extern reg16 FUN_003198cc();
extern uint64_t FUN_0031997c();
extern uint64_t FUN_003199ac();
extern uint64_t FUN_00319a4c();
extern uint64_t FUN_0031c3d0();
extern uint64_t FUN_0031d488();
extern uint64_t FUN_0031d798();
extern uint64_t FUN_003206bc();
extern uint64_t FUN_00321084();
extern uint64_t FUN_003430dc();
extern uint64_t FUN_00343a30();
extern uint64_t FUN_00344d4c();
extern uint64_t FUN_00344e54();
extern uint64_t FUN_00347d60();
extern uint64_t FUN_00347f2c();
extern uint64_t FUN_00348034();
extern uint64_t FUN_00348074();
extern uint64_t FUN_003480ac();
extern uint64_t FUN_00348128();
extern uint64_t FUN_00348194();
extern uint64_t FUN_00348284();
extern uint64_t FUN_003482c4();
extern uint64_t FUN_0034834c();
extern uint64_t FUN_003483c4();
extern uint64_t FUN_0034846c();
extern uint64_t FUN_00348508();
extern uint64_t FUN_00348638();
extern uint64_t FUN_003487a4();
extern uint64_t FUN_00348898();
extern uint64_t FUN_003488bc();
extern uint64_t FUN_003488f4();
extern uint64_t FUN_0034895c();
extern uint64_t FUN_003489a8();
extern uint64_t FUN_003489c0();
extern uint64_t FUN_003489dc();
extern uint64_t FUN_00348a34();
extern uint64_t FUN_00348a9c();
extern uint64_t FUN_00348b5c();
extern uint64_t FUN_00348b7c();
extern reg16 FUN_00348b94();
extern uint64_t FUN_00348c48();
extern uint64_t FUN_00348cd0();
extern uint64_t FUN_00348ce8();
extern uint64_t FUN_00348d00();
extern uint64_t FUN_00348d18();
extern uint64_t FUN_00348d30();
extern uint64_t FUN_00348d4c();
extern uint64_t FUN_00348d64();
extern uint64_t FUN_00348d7c();
extern uint64_t FUN_00348e00();
extern uint64_t FUN_00348e78();
extern uint64_t FUN_00348e9c();
extern uint64_t FUN_00348f14();
extern reg16 FUN_00348f38();
extern uint64_t FUN_00348f50();
extern uint64_t FUN_00349068();
extern uint64_t FUN_00349080();
extern uint64_t FUN_003490ec();
extern uint64_t FUN_00349178();
extern uint64_t FUN_0034921c();
extern uint64_t FUN_0034924c();
extern uint64_t FUN_0034926c();
extern uint64_t FUN_003492ac();
extern uint64_t FUN_00349370();
extern uint64_t FUN_003493ac();
extern uint64_t FUN_003493c4();
extern uint64_t FUN_003493ec();
extern uint64_t FUN_00349410();
extern uint64_t FUN_003494fc();
extern uint64_t FUN_00349644();
extern uint64_t FUN_00349720();
extern uint64_t FUN_003497b4();
extern uint64_t FUN_003497ec();
extern uint64_t FUN_00349830();
extern uint64_t FUN_00349844();
extern uint64_t FUN_003498c4();
extern uint64_t FUN_003498dc();
extern uint64_t FUN_0034998c();
extern uint64_t FUN_003499c8();
extern uint64_t FUN_003499f0();
extern uint64_t FUN_00349a04();
extern uint64_t FUN_00349a18();
extern uint64_t FUN_00349b00();
extern uint64_t FUN_00349b3c();
extern uint64_t FUN_00349b50();
extern uint64_t FUN_00349bfc();
extern uint64_t FUN_00349c70();
extern uint64_t FUN_00349de8();
extern uint64_t FUN_00349ee0();
extern uint64_t FUN_00349ef4();
extern uint64_t FUN_00349fb8();
extern uint64_t FUN_0034a000();
extern uint64_t FUN_0034a148();
extern uint64_t FUN_0034a180();
extern uint64_t FUN_0034a210();
extern uint64_t FUN_0034a2ac();
extern uint64_t FUN_0034a2f8();
extern uint64_t FUN_0034a3c4();
extern uint64_t FUN_0034a3d8();
extern uint64_t FUN_0034a414();
extern uint64_t FUN_0034a464();
extern uint64_t FUN_0034a5dc();
extern uint64_t FUN_0034a5f0();
extern uint64_t FUN_0034a62c();
extern uint64_t FUN_0034a654();
extern uint64_t FUN_0034a688();
extern uint64_t FUN_0034a69c();
extern uint64_t FUN_0034a74c();
extern uint64_t FUN_0034a798();
extern uint64_t FUN_0034a808();
extern uint64_t FUN_0034a958();
extern uint64_t FUN_0034a9c0();
extern uint64_t FUN_0034aa14();
extern uint64_t FUN_0034aa28();
extern uint64_t FUN_0034ab10();
extern uint64_t FUN_0034ab20();
extern uint64_t FUN_0034ac50();
extern uint64_t FUN_0034ac78();
extern uint64_t FUN_0034ad00();
extern uint64_t FUN_0034ad40();
extern uint64_t FUN_0034ad60();
extern uint64_t FUN_0034ae58();
extern uint64_t FUN_0034aea8();
extern uint64_t FUN_0034aee4();
extern uint64_t FUN_0034af20();
extern uint64_t FUN_0034b05c();
extern uint64_t FUN_0034b0b4();
extern uint64_t FUN_0034b0c4();
extern uint64_t FUN_0034b0d4();
extern uint64_t FUN_0034b1a0();
extern uint64_t FUN_0034b278();
extern uint64_t FUN_0034b288();
extern uint64_t FUN_0034b2a8();
extern uint64_t FUN_0034b2c8();
extern uint64_t FUN_0034b2f8();
extern uint64_t FUN_0034b348();
extern uint64_t FUN_0034b358();
extern uint64_t FUN_0034b3e8();
extern uint64_t FUN_0034b440();
extern uint64_t FUN_0034b460();
extern uint64_t FUN_0034b470();
extern uint64_t FUN_0034b508();
extern uint64_t FUN_0034b518();
extern uint64_t FUN_0034b5a8();
extern uint64_t FUN_0034b708();
extern uint64_t FUN_0034b778();
extern uint64_t FUN_0034b788();
extern uint64_t FUN_0034b7b8();
extern uint64_t FUN_0034b7c8();
extern uint64_t FUN_0034b7e4();
extern uint64_t FUN_0034b804();
extern uint64_t FUN_0034b824();
extern uint64_t FUN_0034b85c();
extern uint64_t FUN_0034b89c();
extern uint64_t FUN_0034b8bc();
extern uint64_t FUN_0034b918();
extern uint64_t FUN_0034ba28();
extern uint64_t FUN_0034ba38();
extern uint64_t FUN_0034ba48();
extern uint64_t FUN_0034ba68();
extern uint64_t FUN_0034baa8();
extern uint64_t FUN_0034baf0();
extern uint64_t FUN_0034bc94();
extern uint64_t FUN_0034bca4();
extern uint64_t FUN_0034bcf0();
extern uint64_t FUN_0034bd00();
extern uint64_t FUN_0034bd6c();
extern uint64_t FUN_0034bd80();
extern uint64_t FUN_0034bdfc();
extern uint64_t FUN_0034be0c();
extern uint64_t FUN_0034be54();
extern uint64_t FUN_0034bea4();
extern uint64_t FUN_0034bec4();
extern uint64_t FUN_0034bed4();
extern uint64_t FUN_0034befc();
extern uint64_t FUN_0034bfb4();
extern uint64_t FUN_0034c034();
extern uint64_t FUN_0034c094();
extern uint64_t FUN_0034c0a4();
extern uint64_t FUN_0034c158();
extern uint64_t FUN_0034c234();
extern uint64_t FUN_0034c280();
extern uint64_t FUN_0034c2c8();
extern uint64_t FUN_0034c2e8();
extern uint64_t FUN_0034c368();
extern uint64_t FUN_0034c434();
extern uint64_t FUN_0034c444();
extern uint64_t FUN_0034c4bc();
extern uint64_t FUN_0034c4dc();
extern uint64_t FUN_0034c654();
extern uint64_t FUN_0034c664();
extern uint64_t FUN_0034c684();
extern uint64_t FUN_0034c818();
extern uint64_t FUN_0034c8a0();
extern uint64_t FUN_0034c8b8();
extern uint64_t FUN_0034ce58();
extern uint64_t FUN_0034ce98();
extern uint64_t FUN_0034ced8();
extern uint64_t FUN_0034cfb4();
extern uint64_t FUN_0034cfc4();
extern uint64_t FUN_0034cff4();
extern uint64_t FUN_0034d0d0();
extern uint64_t FUN_0034d180();
extern uint64_t FUN_0034d190();
extern uint64_t FUN_0034d1fc();
extern uint64_t FUN_0034d244();
extern reg16 FUN_0034d264();
extern uint64_t FUN_0034d274();
extern uint64_t FUN_0034d2b4();
extern uint64_t FUN_0034d334();
extern uint64_t FUN_0034d364();
extern uint64_t FUN_0034d384();
extern uint64_t FUN_0034d3c4();
extern uint64_t FUN_0034d3f4();
extern uint64_t FUN_0034d464();
extern uint64_t FUN_0034d53c();
extern uint64_t FUN_0034d688();
extern uint64_t FUN_0034d698();
extern uint64_t FUN_0034d734();
extern uint64_t FUN_0034d7dc();
extern uint64_t FUN_0034d868();
extern uint64_t FUN_0034d8f4();
extern uint64_t FUN_0034d954();
extern uint64_t FUN_0034da18();
extern uint64_t FUN_0034dba8();
extern uint64_t FUN_0034dd14();
extern uint64_t FUN_0034df94();
extern uint64_t FUN_0034dfc4();
extern uint64_t FUN_0034dfe4();
extern uint64_t FUN_0034e004();
extern uint64_t FUN_0034e014();
extern uint64_t FUN_0034e054();
extern uint64_t FUN_0034e1b0();
extern uint64_t FUN_0034e2d0();
extern uint64_t FUN_0034e33c();
extern uint64_t FUN_0034e384();
extern uint64_t FUN_0034e3ac();
extern uint64_t FUN_0034e4ec();
extern uint64_t FUN_0034e52c();
extern uint64_t FUN_0034e55c();
extern uint64_t FUN_0034e57c();
extern uint64_t FUN_0034e64c();
extern uint64_t FUN_0034e784();
extern uint64_t FUN_0034e808();
extern uint64_t FUN_0034e81c();
extern uint64_t FUN_0034eb10();
extern uint64_t FUN_0034eb2c();
extern uint64_t FUN_0034ec0c();
extern uint64_t FUN_0034ed08();
extern uint64_t FUN_0034ee68();
extern uint64_t FUN_0034ee98();
extern uint64_t FUN_0034eea8();
extern uint64_t FUN_0034eef8();
extern uint64_t FUN_0034ef08();
extern uint64_t FUN_0034ef58();
extern uint64_t FUN_0034ef98();
extern uint64_t FUN_0034f030();
extern uint64_t FUN_0034f1c4();
extern uint64_t FUN_0034f1e0();
extern uint64_t FUN_0034f264();
extern uint64_t FUN_0034f3c4();
extern uint64_t FUN_0034f3d4();
extern uint64_t FUN_0034f414();
extern uint64_t FUN_0034f484();
extern uint64_t FUN_0034f554();
extern uint64_t FUN_0034f594();
extern uint64_t FUN_0034f5a4();
extern uint64_t FUN_0034f624();
extern uint64_t FUN_0034f730();
extern uint64_t FUN_0034f764();
extern uint64_t FUN_0034f99c();
extern uint64_t FUN_0034f9b4();
extern uint64_t FUN_0034facc();
extern uint64_t FUN_0034fcf4();
extern uint64_t FUN_0034fd5c();
extern uint64_t FUN_0034fe64();
extern uint64_t FUN_0034fe80();
extern uint64_t FUN_0034ffc8();
extern uint64_t FUN_0034fff0();
extern uint64_t FUN_00350028();
extern uint64_t FUN_00350078();
extern uint64_t FUN_00350164();
extern uint64_t FUN_003501d0();
extern uint64_t FUN_00350210();
extern uint64_t FUN_003502b8();
extern uint64_t FUN_00350308();
extern uint64_t FUN_00350410();
extern uint64_t FUN_00350428();
extern uint64_t FUN_00350464();
extern uint64_t FUN_0035047c();
extern reg16 FUN_00350488();
extern uint64_t FUN_00350494();
extern uint64_t FUN_003504a0();
extern uint64_t FUN_003504ac();
extern uint64_t FUN_003504b8();
extern reg16 FUN_003504c4();
extern reg16 FUN_003504d0();
extern uint64_t FUN_003504e8();
extern reg16 FUN_003504f4();
extern uint64_t FUN_00350500();
extern uint64_t FUN_0035050c();
extern uint64_t FUN_00350518();
extern uint64_t FUN_00350524();
extern uint64_t FUN_00350530();
extern uint64_t FUN_0035053c();
extern uint64_t FUN_00350560();
extern uint64_t FUN_0035056c();
extern uint64_t FUN_003505c4();
extern uint64_t FUN_003505d0();
extern uint64_t FUN_003505f4();
extern uint64_t FUN_00350618();
extern uint64_t FUN_00350624();
extern reg16 FUN_00350630();
extern uint64_t FUN_0035063c();
extern uint64_t FUN_00350648();
extern reg16 FUN_0035066c();
extern uint64_t FUN_003506b0();
extern uint64_t FUN_003506cc();
extern uint64_t FUN_00350720();
extern reg16 FUN_0035072c();
extern uint64_t FUN_00350738();
extern uint64_t FUN_00350744();
extern uint64_t FUN_0035075c();
extern uint64_t FUN_00350774();
extern reg16 FUN_00350798();
extern uint64_t FUN_003507bc();
extern uint64_t FUN_003507d4();
extern reg16 FUN_003507e0();
extern uint64_t FUN_00350810();
extern uint64_t FUN_0035084c();
extern uint64_t FUN_00350858();
extern uint64_t FUN_00350878();
extern uint64_t FUN_0035089c();
extern uint64_t FUN_003508a8();
extern uint64_t FUN_003508b4();
extern uint64_t FUN_003508c0();
extern reg16 FUN_003508cc();
extern uint64_t FUN_003508d8();
extern uint64_t FUN_003508e4();
extern reg16 FUN_003508f0();
extern uint64_t FUN_003508fc();
extern reg16 FUN_00350914();
extern uint64_t FUN_00350920();
extern reg16 FUN_00350944();
extern uint64_t FUN_00350950();
extern uint64_t FUN_00350974();
extern uint64_t FUN_00350980();
extern uint64_t FUN_003509a4();
extern reg16 FUN_003509b0();
extern uint64_t FUN_003509bc();
extern reg16 FUN_003509d4();
extern reg16 FUN_003509e0();
extern uint64_t FUN_003509f8();
extern reg16 FUN_00350a04();
extern uint64_t FUN_00350a28();
extern reg16 FUN_00350a34();
extern uint64_t FUN_00350a40();
extern uint64_t FUN_00350a4c();
extern uint64_t FUN_00350a64();
extern uint64_t FUN_00350a70();
extern uint64_t FUN_00350a7c();
extern reg16 FUN_00350a88();
extern uint64_t FUN_00350a94();
extern uint64_t FUN_00350aa0();
extern uint64_t FUN_00350ab8();
extern uint64_t FUN_00350ad0();
extern uint64_t FUN_00350adc();
extern reg16 FUN_00350af4();
extern reg16 FUN_00350b00();
extern uint64_t FUN_00350b18();
extern uint64_t FUN_00350b24();
extern uint64_t FUN_00350b30();
extern uint64_t FUN_00350b3c();
extern uint64_t FUN_00350b48();
extern uint64_t FUN_00350b54();
extern uint64_t FUN_00350b6c();
extern uint64_t FUN_00350b78();
extern uint64_t FUN_00350b90();
extern uint64_t FUN_00350bb4();
extern uint64_t FUN_00350bc0();
extern uint64_t FUN_00350bcc();
extern uint64_t FUN_00350bd8();
extern uint64_t FUN_00350c20();
extern uint64_t FUN_00350c2c();
extern uint64_t FUN_00350c38();
extern uint64_t FUN_00350c44();
extern uint64_t FUN_00350c50();
extern uint64_t FUN_00350c5c();
extern uint64_t FUN_00350c74();
extern reg16 FUN_00350c80();
extern uint64_t FUN_00350d24();
extern uint64_t FUN_00350e94();
extern uint64_t FUN_00350ea4();
extern uint64_t FUN_00350ed0();
extern uint64_t FUN_00351088();
extern uint64_t FUN_00351094();
extern uint64_t FUN_003510a0();
extern reg16 FUN_003510ac();
extern uint64_t FUN_003510b8();
extern uint64_t FUN_003510c4();
extern reg16 FUN_003510dc();
extern uint64_t FUN_00351100();
extern uint64_t FUN_0035110c();
extern uint64_t FUN_00351118();
extern uint64_t FUN_00351130();
extern uint64_t FUN_0035113c();
extern uint64_t FUN_00351154();
extern reg16 FUN_00351160();
extern uint64_t FUN_00351184();
extern uint64_t FUN_003511a8();
extern uint64_t FUN_003511b4();
extern uint64_t FUN_003511c0();
extern uint64_t FUN_003511cc();
extern uint64_t FUN_00351244();
extern uint64_t FUN_00351250();
extern uint64_t FUN_0035125c();
extern uint64_t FUN_00351274();
extern uint64_t FUN_00351280();
extern uint64_t FUN_003512c0();
extern uint64_t FUN_003512cc();
extern uint64_t FUN_003512f4();
extern uint64_t FUN_00351300();
extern uint64_t FUN_0035130c();
extern uint64_t FUN_00351324();
extern reg16 FUN_00351330();
extern uint64_t FUN_0035133c();
extern uint64_t FUN_00351348();
extern uint64_t FUN_00351354();
extern uint64_t FUN_00351360();
extern uint64_t FUN_0035136c();
extern uint64_t FUN_00351378();
extern uint64_t FUN_00351384();
extern uint64_t FUN_003513cc();
extern uint64_t FUN_003513d8();
extern uint64_t FUN_003513f0();
extern uint64_t FUN_003513fc();
extern uint64_t FUN_00351450();
extern uint64_t FUN_0035145c();
extern uint64_t FUN_00351494();
extern uint64_t FUN_003514b8();
extern reg16 FUN_003514d0();
extern uint64_t FUN_003514dc();
extern uint64_t FUN_003514e8();
extern uint64_t FUN_0035156c();
extern uint64_t FUN_00351584();
extern uint64_t FUN_0035159c();
extern uint64_t FUN_003515a8();
extern uint64_t FUN_003515b4();
extern reg16 FUN_003515cc();
extern uint64_t FUN_003515f0();
extern uint64_t FUN_003515fc();
extern uint64_t FUN_00351624();
extern uint64_t FUN_0035163c();
extern uint64_t FUN_0035166c();
extern uint64_t FUN_003516a8();
extern uint64_t FUN_003516b4();
extern uint64_t FUN_003516cc();
extern uint64_t FUN_003516e4();
extern uint64_t FUN_00351714();
extern uint64_t FUN_00351774();
extern reg16 FUN_003517a8();
extern uint64_t FUN_003517d8();
extern uint64_t FUN_003518a0();
extern uint64_t FUN_003518b8();
extern uint64_t FUN_003518c4();
extern uint64_t FUN_003518d0();
extern uint64_t FUN_003518f4();
extern uint64_t FUN_00351900();
extern uint64_t FUN_00351918();
extern reg16 FUN_0035193c();
extern uint64_t FUN_0035196c();
extern uint64_t FUN_00351990();
extern uint64_t FUN_003519c0();
extern uint64_t FUN_00351a08();
extern uint64_t FUN_00351a14();
extern uint64_t FUN_00351a50();
extern uint64_t FUN_00351a5c();
extern uint64_t FUN_00351a8c();
extern uint64_t FUN_00351a98();
extern uint64_t FUN_00351aa4();
extern uint64_t FUN_00351ab0();
extern uint64_t FUN_00351ad4();
extern uint64_t FUN_00351b20();
extern uint64_t FUN_00351b2c();
extern uint64_t FUN_00351b38();
extern uint64_t FUN_00351b78();
extern uint64_t FUN_00351be0();
extern uint64_t FUN_00351bec();
extern uint64_t FUN_00351c28();
extern uint64_t FUN_00351c7c();
extern uint64_t FUN_00351cc4();
extern uint64_t FUN_00351d00();
extern uint64_t FUN_00351d0c();
extern uint64_t FUN_00351d18();
extern uint64_t FUN_00351d4c();
extern uint64_t FUN_00351dfc();
extern uint64_t FUN_00351e3c();
extern uint64_t FUN_00351e54();
extern uint64_t FUN_00351e6c();
extern uint64_t FUN_00351e84();
extern uint64_t FUN_00351e90();
extern uint64_t FUN_00351ea8();
extern uint64_t FUN_00351ef8();
extern uint64_t FUN_00351f10();
extern uint64_t FUN_00351f1c();
extern uint64_t FUN_00351f40();
extern reg16 FUN_00351f64();
extern uint64_t FUN_00351f7c();
extern uint64_t FUN_00352008();
extern uint64_t FUN_00352098();
extern uint64_t FUN_003520b4();
extern uint64_t FUN_003520f8();
extern uint64_t FUN_003521a4();
extern uint64_t FUN_003521d4();
extern uint64_t FUN_00352260();
extern uint64_t FUN_00352314();
extern uint64_t FUN_003523f0();
extern uint64_t FUN_00352444();
extern uint64_t FUN_0035245c();
extern uint64_t FUN_00352474();
extern uint64_t FUN_003524c8();
extern uint64_t FUN_003524d4();
extern uint64_t FUN_00352554();
extern uint64_t FUN_00352590();
extern uint64_t FUN_00352680();
extern uint64_t FUN_003526d8();
extern uint64_t FUN_0035272c();
extern uint64_t FUN_003527e0();
extern uint64_t FUN_00352858();
extern uint64_t FUN_00352870();
extern uint64_t FUN_00352894();
extern uint64_t FUN_003528ac();
extern uint64_t FUN_00352920();
extern uint64_t FUN_00352974();
extern uint64_t FUN_003529a4();
extern uint64_t FUN_00352abc();
extern uint64_t FUN_00352ae4();
extern uint64_t FUN_00352bbc();
extern uint64_t FUN_00352c10();
extern uint64_t FUN_00352c1c();
extern uint64_t FUN_00352c40();
extern uint64_t FUN_00352c4c();
extern uint64_t FUN_00352c74();
extern uint64_t FUN_00352c80();
extern uint64_t FUN_00352c8c();
extern uint64_t FUN_00352cc8();
extern uint64_t FUN_00352d34();
extern uint64_t FUN_00352db8();
extern uint64_t FUN_00352ddc();
extern uint64_t FUN_00352ea8();
extern uint64_t FUN_00352eb4();
extern uint64_t FUN_00352ecc();
extern uint64_t FUN_00352ee4();
extern reg16 FUN_00352efc();
extern uint64_t FUN_00352f60();
extern uint64_t FUN_0035300c();
extern uint64_t FUN_00353098();
extern uint64_t FUN_003530d8();
extern uint64_t FUN_003530e8();
extern uint64_t FUN_00353124();
extern uint64_t FUN_00353148();
extern uint64_t FUN_00353154();
extern uint64_t FUN_00353160();
extern uint64_t FUN_00353178();
extern uint64_t FUN_003531a8();
extern uint64_t FUN_00353208();
extern uint64_t FUN_00353214();
extern uint64_t FUN_00353238();
extern uint64_t FUN_00353360();
extern reg16 FUN_00353390();
extern uint64_t FUN_003534a4();
extern uint64_t FUN_003534bc();
extern uint64_t FUN_003534d4();
extern uint64_t FUN_003534f8();
extern uint64_t FUN_00353504();
extern uint64_t FUN_00353540();
extern uint64_t FUN_0035362c();
extern uint64_t FUN_003536bc();
extern reg16 FUN_003537f0();
extern uint64_t FUN_003537fc();
extern uint64_t FUN_00353984();
extern uint64_t FUN_00353a84();
extern uint64_t FUN_00353aa0();
extern uint64_t FUN_00353b1c();
extern uint64_t FUN_00353b40();
extern uint64_t FUN_00353ba0();
extern uint64_t FUN_00353bc4();
extern uint64_t FUN_00353c48();
extern uint64_t FUN_00353c54();
extern uint64_t FUN_00353ccc();
extern reg16 FUN_00353cf0();
extern uint64_t FUN_00353cfc();
extern uint64_t FUN_00353d14();
extern uint64_t FUN_00353d64();
extern uint64_t FUN_00353db8();
extern uint64_t FUN_00353e2c();
extern uint64_t FUN_00353e5c();
extern uint64_t FUN_00353e88();
extern uint64_t FUN_00353efc();
extern uint64_t FUN_00353f14();
extern uint64_t FUN_00353f38();
extern uint64_t FUN_00353f5c();
extern uint64_t FUN_00353fd4();
extern uint64_t FUN_00354040();
extern uint64_t FUN_00354088();
extern uint64_t FUN_00354128();
extern reg16 FUN_003542e8();
extern uint64_t FUN_00354364();
extern uint64_t FUN_003543a0();
extern uint64_t FUN_003543c4();
extern uint64_t FUN_00354410();
extern uint64_t FUN_00354474();
extern uint64_t FUN_00354504();
extern uint64_t FUN_00354618();
extern uint64_t FUN_0035466c();
extern uint64_t FUN_00354858();
extern uint64_t FUN_003548a0();
extern uint64_t FUN_003548c4();
extern uint64_t FUN_00354924();
extern uint64_t FUN_003549a8();
extern uint64_t FUN_003549d8();
extern reg16 FUN_00354a34();
extern uint64_t FUN_00354a58();
extern uint64_t FUN_00354ab0();
extern uint64_t FUN_00354afc();
extern uint64_t FUN_00354b08();
extern uint64_t FUN_00354b20();
extern uint64_t FUN_00354b38();
extern uint64_t FUN_00354b50();
extern uint64_t FUN_00354bb0();
extern uint64_t FUN_00354bec();
extern reg16 FUN_00354cfc();
extern uint64_t FUN_00354d08();
extern uint64_t FUN_00354db8();
extern uint64_t FUN_00354dc4();
extern uint64_t FUN_00354ef8();
extern uint64_t FUN_00354f34();
extern uint64_t FUN_00355018();
extern uint64_t FUN_00355074();
extern uint64_t FUN_0035512c();
extern uint64_t FUN_00355160();
extern uint64_t FUN_00355224();
extern uint64_t FUN_00355270();
extern uint64_t FUN_00355334();
extern uint64_t FUN_00355340();
extern uint64_t FUN_003553b8();
extern uint64_t FUN_003553cc();
extern uint64_t FUN_003554d4();
extern uint64_t FUN_00355538();
extern uint64_t FUN_00355594();
extern uint64_t FUN_00355604();
extern uint64_t FUN_00355684();
extern uint64_t FUN_003556e0();
extern uint64_t FUN_0035583c();
extern uint64_t FUN_00355a14();
extern uint64_t FUN_00355ab4();
extern uint64_t FUN_00355af8();
extern uint64_t FUN_00355b74();
extern uint64_t FUN_00355c1c();
extern uint64_t FUN_00355cbc();
extern uint64_t FUN_00355d10();
extern uint64_t FUN_00355f88();
extern uint64_t FUN_00355f94();
extern reg16 FUN_00355fa0();
extern uint64_t FUN_00355fac();
extern uint64_t FUN_00355fb8();
extern uint64_t FUN_00356030();
extern uint64_t FUN_003560f8();
extern uint64_t FUN_00356188();
extern uint64_t FUN_003561dc();
extern uint64_t FUN_00356248();
extern uint64_t FUN_003562bc();
extern uint64_t FUN_00356328();
extern uint64_t FUN_00356358();
extern uint64_t FUN_00356364();
extern uint64_t FUN_00356370();
extern uint64_t FUN_0035638c();
extern uint64_t FUN_003563a8();
extern uint64_t FUN_003563c4();
extern uint64_t FUN_00356780();
extern uint64_t FUN_00356798();
extern uint64_t FUN_0035681c();
extern uint64_t FUN_00356834();
extern uint64_t FUN_00356870();
extern uint64_t FUN_00356940();
extern uint64_t FUN_00356958();
extern uint64_t FUN_003569b4();
extern uint64_t FUN_00356a14();
extern uint64_t FUN_00356ac4();
extern uint64_t FUN_00356b5c();
extern uint64_t FUN_00356ba4();
extern uint64_t FUN_00356cfc();
extern uint64_t FUN_00356d5c();
extern uint64_t FUN_00356e28();
extern uint64_t FUN_00356fcc();
extern uint64_t FUN_00356ff4();
extern uint64_t FUN_00357050();
extern uint64_t FUN_00357198();
extern uint64_t FUN_003571a4();
extern uint64_t FUN_00357228();
extern uint64_t FUN_00357400();
extern uint64_t FUN_00357418();
extern uint64_t FUN_00357664();
extern uint64_t FUN_0035767c();
extern uint64_t FUN_00357694();
extern uint64_t FUN_00357970();
extern uint64_t FUN_003579d8();
extern uint64_t FUN_00357a34();
extern uint64_t FUN_00357ab4();
extern uint64_t FUN_00357b20();
extern uint64_t FUN_00357bf8();
extern reg16 FUN_00357c20();
extern uint64_t FUN_00357c38();
extern uint64_t FUN_00357c44();
extern reg16 FUN_00357ca0();
extern uint64_t FUN_00357cb4();
extern uint64_t FUN_00357d0c();
extern uint64_t FUN_00357d64();
extern uint64_t FUN_00357e44();
extern uint64_t FUN_00357f24();
extern uint64_t FUN_00357fc4();
extern uint64_t FUN_00358024();
extern uint64_t FUN_003580e4();
extern uint64_t FUN_003582b8();
extern uint64_t FUN_003582d8();
extern uint64_t FUN_00358344();
extern uint64_t FUN_003583dc();
extern uint64_t FUN_0035847c();
extern uint64_t FUN_00358534();
extern uint64_t FUN_0035863c();
extern uint64_t FUN_00358684();
extern uint64_t FUN_003586fc();
extern uint64_t FUN_00358768();
extern uint64_t FUN_0035881c();
extern uint64_t FUN_003588b8();
extern uint64_t FUN_00358918();
extern uint64_t FUN_00358984();
extern uint64_t FUN_00358cc8();
extern uint64_t FUN_00358d10();
extern uint64_t FUN_00358e7c();
extern uint64_t FUN_00358eb8();
extern uint64_t FUN_00358fa8();
extern uint64_t FUN_00358fe8();
extern uint64_t FUN_00359018();
extern uint64_t FUN_003591e8();
extern uint64_t FUN_003592f0();
extern uint64_t FUN_00359350();
extern uint64_t FUN_003593e8();
extern uint64_t FUN_00359418();
extern uint64_t FUN_003595a8();
extern uint64_t FUN_00359634();
extern uint64_t FUN_003597b4();
extern uint64_t FUN_003597c0();
extern reg16 FUN_003597d8();
extern uint64_t FUN_00359810();
extern uint64_t FUN_003598a0();
extern uint64_t FUN_0035992c();
extern uint64_t FUN_00359a54();
extern uint64_t FUN_00359a84();
extern uint64_t FUN_00359aa4();
extern uint64_t FUN_00359ab0();
extern uint64_t FUN_00359b30();
extern uint64_t FUN_00359b3c();
extern uint64_t FUN_00359b64();
extern uint64_t FUN_00359be0();
extern uint64_t FUN_00359ca4();
extern uint64_t FUN_00359de8();
extern uint64_t FUN_00359f48();
extern uint64_t FUN_0035a040();
extern uint64_t FUN_0035a0b8();
extern uint64_t FUN_0035a25c();
extern uint64_t FUN_0035a3a0();
extern uint64_t FUN_0035a3b8();
extern uint64_t FUN_0035a490();
extern uint64_t FUN_0035a4bc();
extern uint64_t FUN_0035a4c8();
extern uint64_t FUN_0035a578();
extern uint64_t FUN_0035a5cc();
extern uint64_t FUN_0035a5d8();
extern uint64_t FUN_0035a7a4();
extern uint64_t FUN_0035a858();
extern uint64_t FUN_0035a8fc();
extern uint64_t FUN_0035ace8();
extern uint64_t FUN_00365b6c();
extern uint64_t FUN_0036a940();
extern reg16 FUN_0036a9a0();
extern uint64_t FUN_0036b118();
extern uint64_t FUN_0036b2d0();
extern uint64_t FUN_0036b588();
extern uint64_t FUN_0036b6ac();
extern uint64_t FUN_003722e4();
extern reg16 FUN_00377824();
extern uint64_t FUN_00377bec();
extern reg16 FUN_003a25d4();
extern uint64_t FUN_003a2610();
extern uint64_t FUN_003a261c();
extern uint64_t SBORROW8();
extern uint64_t SCARRY8();
extern uint64_t SEXT816();
extern uint64_t SUB168();
extern uint64_t dispatch_slot();
extern uint64_t sk_alloc_ok();
extern uint64_t sk_array_append_shared();
extern uint64_t sk_array_apply_shared();
extern uint64_t sk_array_elem_helper();
extern uint64_t sk_collection_apply_shared();
extern uint64_t sk_collection_init();
extern uint64_t sk_collection_reserve();
extern uint64_t sk_count_a();
extern uint64_t sk_ctx_restore();
extern uint64_t sk_ctx_save();
extern uint64_t sk_ctx_touch();
extern uint64_t sk_elem_accessor();
extern uint64_t sk_elem_destroy();
extern uint64_t sk_elem_prep();
extern uint64_t sk_elem_prep2();
extern uint64_t sk_elem_reserve();
extern uint64_t sk_elem_reserve_b();
extern uint64_t sk_elem_reserve_b2();
extern uint64_t sk_elem_reserve_c();
extern uint64_t sk_elem_reserve_str();
extern uint64_t sk_elem_retain();
extern uint64_t sk_elem_retain_b();
extern uint64_t sk_elem_retain_c();
extern uint64_t sk_elem_retain_d();
extern uint64_t sk_elem_retain_e();
extern uint64_t sk_elem_retain_f();
extern uint64_t sk_elem_retain_g();
extern uint64_t sk_elem_retain_h();
extern uint64_t sk_irqrestore();
extern uint64_t sk_lock_a();
extern uint64_t sk_lock_aa();
extern uint64_t sk_lock_ab();
extern uint64_t sk_lock_ac();
extern uint64_t sk_lock_ad();
extern uint64_t sk_lock_ae();
extern uint64_t sk_lock_af();
extern uint64_t sk_lock_ag();
extern uint64_t sk_lock_ah();
extern uint64_t sk_lock_ai();
extern uint64_t sk_lock_aj();
extern uint64_t sk_lock_ak();
extern uint64_t sk_lock_al();
extern uint64_t sk_lock_am();
extern uint64_t sk_lock_an();
extern uint64_t sk_lock_ao();
extern uint64_t sk_lock_ap();
extern uint64_t sk_lock_aq();
extern uint64_t sk_lock_ar();
extern uint64_t sk_lock_as();
extern uint64_t sk_lock_at();
extern uint64_t sk_lock_au();
extern uint64_t sk_lock_av();
extern uint64_t sk_lock_b();
extern uint64_t sk_lock_c();
extern uint64_t sk_lock_f();
extern uint64_t sk_lock_g();
extern uint64_t sk_lock_h();
extern uint64_t sk_lock_i();
extern uint64_t sk_lock_j();
extern uint64_t sk_lock_k();
extern uint64_t sk_lock_l();
extern uint64_t sk_lock_m();
extern uint64_t sk_lock_n();
extern uint64_t sk_lock_o();
extern uint64_t sk_lock_p();
extern uint64_t sk_lock_q();
extern uint64_t sk_lock_r();
extern uint64_t sk_lock_s();
extern uint64_t sk_lock_size_class();
extern uint64_t sk_lock_t();
extern uint64_t sk_lock_u();
extern uint64_t sk_lock_v();
extern uint64_t sk_lock_w();
extern uint64_t sk_lock_x();
extern uint64_t sk_lock_y();
extern uint64_t sk_lock_z();
extern uint64_t sk_meta_a();
extern uint64_t sk_meta_b();
extern uint64_t sk_metatype();
extern uint64_t sk_metatype_for();
extern uint64_t sk_obj_release();
extern uint64_t sk_obj_release2();
extern uint64_t sk_obj_retain();
extern uint64_t sk_objc_metatype();
extern uint64_t sk_ow_borrow();
extern uint64_t sk_ow_check();
extern uint64_t sk_ow_done();
extern uint64_t sk_ow_force();
extern uint64_t sk_ow_norm();
extern uint64_t sk_queue_realloc();
extern uint64_t sk_queue_realloc8();
extern uint64_t sk_sched_enqueue_core();
extern uint64_t sk_sched_flag();
extern uint64_t sk_sched_grow();
extern uint64_t sk_sched_tick_shared();
extern uint64_t sk_sched_touch();
extern uint64_t sk_spin_irqsave();
extern uint64_t sk_tick_b();
extern uint64_t swift_array_alloc();
extern uint64_t swift_array_touch_ret();
extern uint64_t swift_collection_reserve_r();
extern uint64_t swift_utf8_decode();
extern uint64_t thunk_FUN_00012568();
extern uint64_t thunk_FUN_000126e8();
extern uint64_t thunk_FUN_001dc298();
extern uint64_t thunk_FUN_00200b38();
extern uint64_t thunk_FUN_002298d4();
extern uint64_t thunk_FUN_0036b270();
/* ==================================================================== */
/*--------------------------------------------------------------------*/
/* FUN_001a002c @ 0x001a002c   (est. swift_array_construct_dispatch)
 * Ghidra: void FUN_001a002c(undefined8 param_1)
 * Resolves the element metatype for an array descriptor (DAT_004e8268) and
 * dispatches through FUN_001a0194 (jumptable) to construct the collection.
 * Confidence: medium
 * Notes: DAT_004e8268 metatype; indirect jump at 0x001a01cc (not recoverable).
 */
void swift_array_construct_dispatch(uint64_t param_1)
{
    uint64_t meta = sk_objc_metatype(&sk_array_metatype, param_1); /* FUN_00376820 */
    sk_swift_array_dispatch_impl(param_1, meta);                   /* FUN_001a0194 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a008c @ 0x001a008c   (est. sk_sched_size_class)
 * Ghidra: undefined8 FUN_001a008c(uint param_1)
 * Selects a size class (1..4) for a run-queue/slab item based on the value's
 * magnitude: >0x7f => 2, >0x7ff => 3, >0xffff => 4. Then invokes the
 * per-class CPU bookkeeping helpers and returns the class.
 * Confidence: medium
 * Notes: calls FUN_003504e8 / FUN_001dff60 / FUN_00351790 / FUN_0034d024 /
 *   FUN_0019fe7c / FUN_00351488.
 */
uint64_t sk_sched_size_class(uint32_t n)
{
    uint64_t c = 3;
    if (n > 0xffff) c = 4;
    uint64_t c2 = 2;
    if (n > 0x7ff) c2 = c;
    uint64_t c1 = 1;
    if (n > 0x7f) c1 = c2;

    sk_lock_a();          /* FUN_003504e8 */
    sk_tick_b();          /* FUN_001dff60 */
    sk_lock_b();          /* FUN_00351790 */
    sk_lock_c();          /* FUN_0034d024 */
    sk_sched_touch();     /* FUN_0019fe7c */
    sk_lock_a();          /* FUN_003504e8 */
    sk_tick_b();          /* FUN_001dff60 */
    sk_lock_b();          /* FUN_00351790 */
    sk_lock_size_class(c1); /* FUN_00351488 */
    sk_sched_touch();     /* FUN_0019fe7c */
    return c1;
}

/*--------------------------------------------------------------------*/
/* FUN_001a00fc @ 0x001a00fc   (est. sk_sched_capacity_class)
 * Ghidra: long FUN_001a00fc(undefined4 param_1)
 * Returns 4 - (LZCOUNT(param_1) >> 3) — the leading-zero based size class
 * for a scheduling/queue capacity hint.
 * Confidence: medium
 * Notes: pure computation, LZCOUNT intrinsic.
 */
long sk_sched_capacity_class(uint32_t n)
{
    return 4 - ((uint64_t)sk_lzcount(n) >> 3);
}

/*--------------------------------------------------------------------*/
/* FUN_001a013c @ 0x001a013c   (est. sk_sched_tick_thunk)
 * Ghidra: void FUN_001a013c(void)
 * Thunk: forwards to the shared scheduler tick/refresh helper.
 * Confidence: medium
 * Notes: FUN_002a999c.
 */
void sk_sched_tick_a(void) { sk_sched_tick_shared(); } /* FUN_002a999c */

/*--------------------------------------------------------------------*/
/* FUN_001a0140 @ 0x001a0140   (est. sk_sched_tick_thunk)
 * Ghidra: void FUN_001a0140(void)
 * Thunk: alias of FUN_001a013c, forwards to the shared tick helper.
 * Confidence: medium
 * Notes: FUN_002a999c.
 */
void sk_sched_tick_b(void) { sk_sched_tick_shared(); } /* FUN_002a999c */

/*--------------------------------------------------------------------*/
/* FUN_001a0158 @ 0x001a0158   (est. queue_len_delta)
 * Ghidra: long FUN_001a0158(long param_1, long param_2)
 * Returns param_2 - param_1 when param_1 is non-null, else 0. Computes the
 * number of slots between two linked-list/queue cursors.
 * Confidence: medium
 */
long queue_len_delta(long a, long b)
{
    return (a != 0) ? (b - a) : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0168 @ 0x001a0168   (est. swift_array_append_thunk)
 * Ghidra: void FUN_001a0168(undefined8 param_1, undefined8 param_2)
 * Thunk: appends param_1 to the array at param_2 via the shared append helper.
 * Confidence: medium
 * Notes: FUN_001ee030(param_1, param_2, FUN_002a9d64).
 */
void swift_array_append_a(uint64_t a, uint64_t b) { sk_array_append_shared(a, b); } /* FUN_001ee030,FUN_002a9d64 */

/*--------------------------------------------------------------------*/
/* FUN_001a016c @ 0x001a016c   (est. swift_array_append_thunk)
 * Ghidra: void FUN_001a016c(undefined8 param_1, undefined8 param_2)
 * Thunk: alias of FUN_001a0168; appends via the shared helper.
 * Confidence: medium
 * Notes: FUN_001ee030(param_1, param_2, FUN_002a9d64).
 */
void swift_array_append_b(uint64_t a, uint64_t b) { sk_array_append_shared(a, b); } /* FUN_001ee030,FUN_002a9d64 */

/*--------------------------------------------------------------------*/
/* FUN_001a0194 @ 0x001a0194   (est. sk_swift_array_dispatch_impl)
 * Ghidra: void FUN_001a0194(void)
 * Swift object/collection constructor dispatch: takes the object lock,
 * resolves the vtable entry via FUN_00027788, and jumps through it; wraps the
 * call with a scheduler yield (FUN_00084180).
 * Confidence: low (jumptable not recoverable)
 * Notes: FUN_0034f664 / FUN_00027788 / FUN_00084180; indirect jump at
 *   0x001a01cc "too many branches".
 */
void sk_swift_array_dispatch_impl()
{
    sk_lock_f();                    /* FUN_0034f664 */
    code_fn entry = (code_fn)sk_vtable_resolve(); /* FUN_00027788 */
    sk_schedule_yield();            /* FUN_00084180 */
    entry();                        /* jumptable via FUN_00027788 result */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0224 @ 0x001a0224   (est. sk_swift_array_reserve)
 * Ghidra: void FUN_001a0224(void)
 * Reserve/grow path for a Swift array: runs the preflight lock sequence, reads
 * the current length, and either extends the backing store or terminates via
 * the fatal-error path if the growth would overflow.
 * Confidence: low (many inlined helpers, unaff regs)
 * Notes: unaff_x19=array, unaff_x22/x23; FATAL FUN_001afe4c at 0x001a02d0.
 */
void sk_swift_array_reserve(void)
{
    sk_lock_g();           /* FUN_00354a34 */
    sk_lock_h();           /* FUN_003531d8 */
    sk_lock_i();           /* FUN_00354708 */
    sk_lock_j();           /* FUN_0035a01c */
    sk_lock_k();           /* FUN_003516cc */
    uint64_t v1 = sk_meta_a();    /* FUN_00310d34 */
    uint64_t v2 = sk_meta_b();    /* FUN_00348718 */
    sk_metatype(v2, v1);          /* FUN_00376820 */
    sk_lock_l();                  /* FUN_00357ab4 */
    uint64_t flags = sk_sched_flag(v1);  /* FUN_0019fd10 */
    if ((flags & 1) != 0) {
        sk_lock_m();      /* FUN_00354ef8 */
        return;
    }
    if (x22 == 0) {
        sk_count_a(1);    /* FUN_003488bc */
        sk_lock_n();      /* FUN_0034a3d8 */
    } else {
        if (*(long *)(x19 + 0x10) <= x23) {
            sk_lock_o();          /* FUN_00355730 */
            sk_lock_p(x19);       /* FUN_00351b78 */
            sk_sched_grow();      /* FUN_0019dadc */
            sk_lock_m();          /* FUN_00354ef8 */
            return;
        }
        sk_count_a(1);    /* FUN_003488bc */
        sk_lock_q();      /* FUN_00356870 */
        sk_lock_n();      /* FUN_0034a3d8 */
    }
    sk_lock_r();          /* FUN_003504b8 */
    sk_swift_fatal(0, 0, 0);     /* FUN_001afe4c — noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0304 @ 0x001a0304   (est. swift_array_init_thunk)
 * Ghidra: void FUN_001a0304(...)
 * Thunk: forwards array-init arguments to FUN_001a0328 with the object's
 * dispatch slot and param_4+0x10.
 * Confidence: medium
 */
void swift_array_init_a(uint64_t a, uint64_t b, uint64_t c, long p4)
{
    swift_array_init_core(a, b, *x20, *(uint64_t *)(p4 + 0x10), c); /* FUN_001a0328 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0308 @ 0x001a0308   (est. swift_array_init_thunk)
 * Ghidra: void FUN_001a0308(...)
 * Thunk: alias of FUN_001a0304; same forwarding to FUN_001a0328.
 * Confidence: medium
 */
void swift_array_init_b(uint64_t a, uint64_t b, uint64_t c, long p4)
{
    swift_array_init_core(a, b, *x20, *(uint64_t *)(p4 + 0x10), c); /* FUN_001a0328 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0328 @ 0x001a0328   (est. swift_array_init_core)
 * Ghidra: void FUN_001a0328(void)
 * Core array-initializer: forwards to the shared collection init helper.
 * Confidence: medium
 * Notes: FUN_001dd154.
 */
void swift_array_init_core(void)
{
    sk_collection_init();   /* FUN_001dd154 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0354 @ 0x001a0354   (est. swift_array_construct)
 * Ghidra: undefined * FUN_001a0354(undefined8 param_1, long param_2)
 * Constructs a Swift Array with `count` elements each initialized to `elem`.
 * On negative count it fatals ("Can't construct Array with count < 0");
 * on zero returns the shared empty-array singleton (DAT_00657778); otherwise
 * allocates a new backing buffer and fills the element slots.
 * Confidence: high (string-matched fatal + clear Swift Array shape)
 * Notes: strings s_Fatal_error_005accd0 / s_Can_t_construct_Array_with_count_005cdb70 /
 *   s_Swift_Array_swift_005cd990; DAT_00657778 empty array.
 */
void *swift_array_construct(uint64_t elem, long count)
{
    if (count < 0) {
        sk_swift_fatal(s_Fatal_error, 0xb, 2,
                       s_cant_construct_array, 0x24, 2,
                       s_swift_array, 0x11, 2, 0x3b3, 1);
    }
    if (count == 0)
        return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = swift_array_alloc(count); /* FUN_001a042c */
    *(long *)(buf + 0x10) = count;
    long i = 0x20;
    do {
        *(uint64_t *)(buf + i) = elem;
        i += 8;
        count--;
    } while (count != 0);
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a03fc @ 0x001a03fc   (est. swift_collection_reserve_thunk)
 * Ghidra: void FUN_001a03fc(void)
 * Thunk: forwards to the shared collection reserve helper.
 * Confidence: medium
 * Notes: FUN_001dd264.
 */
void swift_collection_reserve(void) { sk_collection_reserve(); } /* FUN_001dd264 */

/*--------------------------------------------------------------------*/
/* FUN_001a0414 @ 0x001a0414   (est. swift_array_apply_thunk)
 * Ghidra: void FUN_001a0414(undefined8 param_1, undefined8 param_2)
 * Thunk: applies a function to the array via the shared helper with the
 * element-destroy callback FUN_001a04c0.
 * Confidence: medium
 * Notes: FUN_001dd420(param_1, param_2, FUN_001a04c0).
 */
void swift_array_apply(uint64_t a, uint64_t b)
{
    sk_array_apply_shared(a, b, swift_array_destroy); /* FUN_001dd420, FUN_001a04c0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a042c @ 0x001a042c   (est. swift_array_alloc)
 * Ghidra: undefined * FUN_001a042c(long param_1)
 * Allocates the backing buffer for a Swift Array holding `count` elements
 * (each 8 bytes): computes the element-size/flag header, allocates
 * count*8+0x20 bytes (tag 7), and stores the element stride in the header.
 * Returns the shared empty singleton when count < 1.
 * Confidence: medium
 * Notes: FUN_00002534(s___cstring_0064c108+8, DAT_004c0740); FUN_0036a940
 *   (count*8+0x20, tag 7); thunk_FUN_000126e8.
 */
void *swift_array_alloc(long count)
{
    if (count < 1)
        return &sk_empty_array;             /* DAT_00657778 */
    uint64_t meta = sk_metatype_for(&sk_cstring + 8, (void*)0x004c0740); /* FUN_00002534 */
    uint8_t *buf = sk_alloc_special(meta, count * 8 + 0x20, 7);      /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();     /* FUN_000126e8 */
    *(uint64_t *)(buf + 0x10) = 0;
    *(long *)(buf + 0x18) = ((stride - 0x20) / 8) << 1;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a04a4 @ 0x001a04a4   (est. swift_array_touch)
 * Ghidra: void FUN_001a04a4(undefined8 param_1, undefined8 param_2)
 * Touches/marks the array's elements: copies param_2 through the element
 * accessor then invokes the shared element helper FUN_0019c44c.
 * Confidence: medium
 * Notes: FUN_00352efc(param_1,param_2,param_2); FUN_0019c44c.
 */
void swift_array_touch(uint64_t a, uint64_t b)
{
    sk_elem_accessor(a, b, b);  /* FUN_00352efc */
    sk_array_elem_helper();     /* FUN_0019c44c */
}

/*--------------------------------------------------------------------*/
/* FUN_001a04c0 @ 0x001a04c0   (est. swift_array_destroy)
 * Ghidra: void FUN_001a04c0(long param_1)
 * Destroys a Swift Array buffer: releases the element storage, frees the
 * buffer, and updates the refcounted object. Negative handle is treated as a
 * fatal error.
 * Confidence: medium
 * Notes: FUN_0006f6b4 / FUN_0036b118 / FUN_0009461c / FUN_001a04a4; fatal
 *   FUN_001afe4c on negative.
 */
void swift_array_destroy(long handle)
{
    if (handle >= 0) {
        if (handle == 0) {
            sk_obj_release();   /* FUN_0006f6b4 */
        } else {
            sk_obj_release();   /* FUN_0006f6b4 */
            sk_free(NULL);      /* FUN_0036b118 */
            sk_obj_retain();    /* FUN_0009461c */
            long h = swift_array_touch_ret(); /* FUN_001a04a4 */
            *(long *)(h + 0x10) = handle;
        }
        return;
    }
    sk_count_a(1);      /* FUN_003488bc */
    sk_lock_n();        /* FUN_0034a3d8 */
    sk_lock_r();        /* FUN_003504b8 */
    sk_swift_fatal(0, 0, 0);   /* FUN_001afe4c — noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0534 @ 0x001a0534   (est. sk_sched_budget_update)
 * Ghidra: void FUN_001a0534(long *param_1, long param_2)
 * Updates a per-run-queue budget structure: sets budget and doubled budget
 * fields, then refreshes the queue via the CPU context.
 * Confidence: medium
 * Notes: param_1[2]=param_2, param_1[3]=param_2<<1; FUN_003509c8 /
 *   FUN_00357c20 with extraout_x16+0x50.
 */
void sk_sched_budget_update(long *rq, long budget)
{
    rq[2] = budget;
    rq[3] = budget << 1;
    reg16 v = sk_cpu_ctx();                    /* FUN_003509c8 */
    sk_ctx_touch(*(uint8_t *)(x16 + 0x50), v.lo, v.hi); /* FUN_00357c20 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a05a8 @ 0x001a05a8   (est. sk_sched_queue_reserve)
 * Ghidra: void FUN_001a05a8(long param_1)
 * Ensures the run queue backing storage can hold param_1 entries; if the
 * capacity is exceeded it reallocates via FUN_001a09bc.
 * Confidence: medium
 * Notes: *unaff_x20=queue; FUN_003a261c check; FUN_001a09bc realloc.
 */
void sk_sched_queue_reserve(long need)
{
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);           /* FUN_003a261c */
    *x20 = *q;
    if (ok == 0 || (*(unsigned long *)(*q + 0x18) >> 1) < (unsigned long)need) {
        long cap = *(long *)(*q + 0x10);
        if (*(long *)(*q + 0x10) <= need) cap = need;
        *q = sk_queue_realloc(ok, cap, 0, *q); /* FUN_001a09bc */
    }
    *x20 = *q;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0640 @ 0x001a0640   (est. sk_sched_queue_reserve_fn)
 * Ghidra: void FUN_001a0640(long param_1, uint param_2, code *param_3)
 * Reserve variant that uses a caller-supplied allocator callback (param_3) to
 * grow the queue to fit param_1 entries.
 * Confidence: medium
 */
void sk_sched_queue_reserve_fn(long need, uint flags, void *(*alloc_fn)(uint64_t, long, uint64_t, long))
{
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);           /* FUN_003a261c */
    *x20 = *q;
    if (ok == 0 || (*(unsigned long *)(*q + 0x18) >> 1) < (unsigned long)need) {
        long cap = *(long *)(*q + 0x10);
        if (*(long *)(*q + 0x10) <= need) cap = need;
        *q = alloc_fn(ok, cap, flags & 1, *q);
        *x20 = *q;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a06b8 @ 0x001a06b8   (est. sk_sched_queue_append)
 * Ghidra: void FUN_001a06b8(void)
 * Appends the current element to the run queue: wraps the operation with the
 * CPU context save/restore, grows the queue if needed, and forwards through
 * the shared element-append helper.
 * Confidence: low (unaff regs, heavy inlining)
 * Notes: FUN_00084220/34 (ctx save/restore), FUN_0034cc94, FUN_003a261c,
 *   FUN_00354318, FUN_0035a134, FUN_001a0a70.
 */
void sk_sched_queue_append(void)
{
    sk_ctx_save();                      /* FUN_00084220 */
    reg16 v = FUN_0034cc94();
    long need = v.lo;
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);      /* FUN_003a261c */
    *x20 = *q;
    if (ok == 0 || (*(unsigned long *)(*q + 0x18) >> 1) < (unsigned long)need) {
        long cap = *(long *)(*q + 0x10);
        if (*(long *)(*q + 0x10) <= need) cap = need;
        sk_lock_s(ok, cap, v.hi & 1);   /* FUN_00354318 */
        sk_lock_t();                    /* FUN_0035a134 */
        *q = sk_queue_realloc8(0, *(long *)(*q + 0x10) + 1, 1, *q,
                               (void*)0x00657620, (void*)0x004f2100, 0x6562f8, (void*)0x004e8108); /* FUN_001a0a70 */
        *x20 = *q;
    }
    sk_ctx_restore(x30);                /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a0734 @ 0x001a0734   (est. sk_array_reserve_thunk_c98)
 * Ghidra: void FUN_001a0734(void)
 * Thunk: stores the result of FUN_001a0c98 (array reserve) into the slot.
 * Confidence: medium
 */
void sk_array_reserve_c98(void) { *x20 = FUN_001a0c98(); }

/*--------------------------------------------------------------------*/
/* FUN_001a0754 @ 0x001a0754   (est. sk_array_reserve_thunk_d1c)
 * Ghidra: void FUN_001a0754(void)
 * Thunk: stores the result of FUN_001a0d1c into the slot.
 * Confidence: medium
 */
void sk_array_reserve_d1c(void) { *x20 = FUN_001a0d1c(); }

/*--------------------------------------------------------------------*/
/* FUN_001a0774 @ 0x001a0774   (est. sk_array_reserve_thunk_dac)
 * Ghidra: void FUN_001a0774(void)
 * Thunk: stores the result of FUN_001a0dac into the slot.
 * Confidence: medium
 */
void sk_array_reserve_dac(void) { *x20 = FUN_001a0dac(); }

/*--------------------------------------------------------------------*/
/* FUN_001a0794 @ 0x001a0794   (est. sk_array_reserve_thunk_fa4)
 * Ghidra: void FUN_001a0794(void)
 * Thunk: stores the result of FUN_001a0fa4 into the slot.
 * Confidence: medium
 */
void sk_array_reserve_fa4(void) { *x20 = FUN_001a0fa4(); }

/*--------------------------------------------------------------------*/
/* FUN_001a0798 @ 0x001a0798   (est. sk_array_reserve_thunk_fa4b)
 * Ghidra: void FUN_001a0798(void)
 * Thunk: alias of FUN_001a0794; stores FUN_001a0fa4 result.
 * Confidence: medium
 */
void sk_array_reserve_fa4b(void) { *x20 = FUN_001a0fa4(); }

/*--------------------------------------------------------------------*/
/* FUN_001a07bc @ 0x001a07bc   (est. swift_array_reserve_generic)
 * Ghidra: long FUN_001a07bc(ulong param_1, ulong param_2, ulong param_3, long param_4)
 * Generic Swift Array reserve/replace: computes the required capacity from the
 * array descriptor (param_4+0x18), reallocates the backing store, and either
 * retains the old elements or destroys them depending on the is-uniquely-referenced
 * flag (param_1&1).
 * Confidence: medium
 * Notes: FUN_0019c348 / FUN_0019d234 / FUN_0019cbd4 / FUN_0036b118; the
 *   FUN_0019c2b0/…/FUN_0019c4xx family are element-specific alloc variants.
 */
long swift_array_reserve_generic(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0870) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x00657720, (void*)0x004f2230); /* FUN_0019c348 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d234 */
    else {
        sk_elem_destroy();                              /* FUN_0019cbd4 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0870 @ 0x001a0870   (est. swift_string_reserve)
 * Ghidra: undefined8 FUN_001a0870(...)
 * String reserve variant: validates uniqueness with the overflow-checking
 * accessors (FUN_00077560/70/24/50), then reallocates the backing storage.
 * Confidence: medium
 * Notes: unaff_x19=obj, unaff_x20=flags; DAT_004be910; FUN_0036b118.
 */
uint64_t swift_string_reserve(void)
{
    sk_ow_check();                  /* FUN_00077570 */
    uint64_t u = x1;
    if ((x20 & 1) != 0 && (sk_ow_borrow(), (x1 = x1, NG != OV))) {
        sk_ow_force();              /* FUN_00077624 */
        if (NG) __builtin_trap();   /* SoftwareBreakpoint(1,0x1a0908) */
        sk_ow_norm();               /* FUN_00077550 */
        u = x1_00;
    }
    u = sk_elem_reserve_str(*(uint64_t *)(x19 + 0x10), u, &sk_cstring, (void*)0x004be910); /* FUN_0019c258 */
    if ((x20 & 1) == 0) {
        sk_ow_done();               /* FUN_00077580 */
        sk_elem_retain_b();         /* FUN_0019d40c */
    } else {
        sk_lock_u();                /* FUN_003577b4 */
        sk_ow_done();               /* FUN_00077580 */
        sk_lock_v();                /* FUN_0035ab20 */
        *(uint64_t *)(x19 + 0x10) = 0;
    }
    sk_free(NULL);                  /* FUN_0036b118 */
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0908 @ 0x001a0908   (est. swift_array_reserve_variant)
 * Ghidra: long FUN_001a0908(ulong param_1, ulong param_2, ulong param_3, long param_4)
 * Element-specific Swift Array reserve variant (element descriptor DAT_006575b8 /
 * DAT_004f1948). Same capacity-computation + retain-or-destroy + free shape
 * as FUN_001a07bc.
 * Confidence: medium
 * Notes: FUN_0019c2b0 / FUN_0019d338 / FUN_0019cc64 / FUN_0036b118.
 */
long swift_array_reserve_variant(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a09bc) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x006575b8, (void*)0x004f1948); /* FUN_0019c2b0 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d338 */
    else {
        sk_elem_destroy();                              /* FUN_0019cc64 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a09bc @ 0x001a09bc   (est. swift_array_reserve_variant2)
 * Ghidra: long FUN_001a09bc(...)
 * Element-specific reserve variant (DAT_00657678 / DAT_005a4b20).
 * Confidence: medium
 * Notes: FUN_0019c2b0 / FUN_0019d498 / FUN_0019cc64 / FUN_0036b118.
 */
long swift_array_reserve_variant2(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0a70) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x00657678, (void*)0x005a4b20); /* FUN_0019c2b0 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d498 */
    else {
        sk_elem_destroy();                              /* FUN_0019cc64 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0a70 @ 0x001a0a70   (est. swift_array_reserve_variant3)
 * Ghidra: long FUN_001a0a70(...)
 * Element-specific reserve variant with element stride/accessor.
 * Confidence: medium
 * Notes: FUN_00354828 / FUN_0019c3f0 / FUN_0019da34 / FUN_0019cdf8 /
 *   FUN_0036b118.
 */
long swift_array_reserve_variant3(uint64_t flags, uint64_t need, uint64_t uniq, long arr,
                                  uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0b30) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    sk_elem_prep(elem, cap);                    /* FUN_00354828 */
    long ret = sk_elem_reserve_b();             /* FUN_0019c3f0 */
    if ((flags & 1) == 0)
        sk_elem_retain_c(arr + 0x20, elem, ret + 0x20, p7, p8); /* FUN_0019da34 */
    else {
        sk_elem_destroy();                      /* FUN_0019cdf8 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                               /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0b30 @ 0x001a0b30   (est. swift_array_reserve_variant4)
 * Ghidra: long FUN_001a0b30(...)
 * Element-specific reserve variant (DAT_00657710 / DAT_004f2220).
 * Confidence: medium
 * Notes: FUN_0019c3a4 / FUN_0019d528 / FUN_0019ccec / FUN_0036b118.
 */
long swift_array_reserve_variant4(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0be4) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x00657710, (void*)0x004f2220); /* FUN_0019c3a4 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d528 */
    else {
        sk_elem_destroy();                              /* FUN_0019ccec */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0be4 @ 0x001a0be4   (est. swift_array_reserve_variant5)
 * Ghidra: long FUN_001a0be4(...)
 * Element-specific reserve variant (LAB_006576b8 / DAT_004f21b0).
 * Confidence: medium
 * Notes: FUN_0019c258 / FUN_0019d600 / FUN_0019cd74 / FUN_0036b118.
 */
long swift_array_reserve_variant5(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0c98) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x006576b8, (void*)0x004f21b0); /* FUN_0019c258 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d600 */
    else {
        sk_elem_destroy();                              /* FUN_0019cd74 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0c98 @ 0x001a0c98   (est. swift_string_reserve_variant)
 * Ghidra: undefined8 FUN_001a0c98(...)
 * String reserve variant with uniqueness checks (FUN_00077560/70/24/50) and
 * element reallocation (FUN_0019c2fc).
 * Confidence: medium
 * Notes: unaff_x19=obj, unaff_x20=flags; FUN_0036b118.
 */
uint64_t swift_string_reserve_variant(void)
{
    uint64_t v = sk_ow_check();                 /* FUN_00077570 */
    reg16 vv = { v, x8 };
    if ((x20 & 1) != 0 && (vv = sk_ow_borrow(), NG != OV)) {
        sk_ow_force();                          /* FUN_00077624 */
        if (NG) __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0d1c) */
        vv = sk_ow_norm();                      /* FUN_00077550 */
    }
    uint64_t e = *(uint64_t *)(x19 + 0x10);
    sk_elem_prep2(vv.lo, vv.hi);                /* FUN_003556e0 */
    uint64_t ret = sk_elem_reserve_c(e);        /* FUN_0019c2fc */
    sk_ow_done();                               /* FUN_00077580 */
    if ((x20 & 1) == 0)
        sk_elem_retain_d();                     /* FUN_0019d15c */
    else {
        sk_obj_release2();                      /* FUN_00069970 */
        *(uint64_t *)(x19 + 0x10) = 0;
    }
    sk_free(NULL);                              /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0d1c @ 0x001a0d1c   (est. swift_string_reserve_variant2)
 * Ghidra: undefined8 FUN_001a0d1c(...)
 * String reserve variant (DAT_0064c040 / DAT_004bbf40).
 * Confidence: medium
 * Notes: FUN_0019c3a4 / FUN_0019d6d0 / FUN_0019ccec / FUN_0036b118.
 */
uint64_t swift_string_reserve_variant2(void)
{
    sk_ow_check();                              /* FUN_00077570 */
    uint64_t u = x8;
    if ((x20 & 1) != 0 && (sk_ow_borrow(), (u = x1, NG != OV))) {
        sk_ow_force();                          /* FUN_00077624 */
        if (NG) __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0dac) */
        sk_ow_norm();                           /* FUN_00077550 */
        u = x1_00;
    }
    u = sk_elem_reserve_str(*(uint64_t *)(x19 + 0x10), u, (void*)0x0064c040, (void*)0x004bbf40); /* FUN_0019c3a4 */
    sk_ow_done();                               /* FUN_00077580 */
    if ((x20 & 1) == 0)
        sk_elem_retain_e();                     /* FUN_0019d6d0 */
    else {
        sk_elem_destroy();                      /* FUN_0019ccec */
        *(uint64_t *)(x19 + 0x10) = 0;
    }
    sk_free(NULL);                              /* FUN_0036b118 */
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0dac @ 0x001a0dac   (est. swift_string_reserve_variant3)
 * Ghidra: undefined8 FUN_001a0dac(...)
 * String reserve variant (DAT_0064e838 / DAT_004c0690).
 * Confidence: medium
 * Notes: FUN_0019c2b0 / FUN_0019d7ac / FUN_0019cc64 / FUN_0036b118.
 */
uint64_t swift_string_reserve_variant3(void)
{
    sk_ow_check();                              /* FUN_00077570 */
    uint64_t u = x8;
    if ((x20 & 1) != 0 && (sk_ow_borrow(), (u = x1, NG != OV))) {
        sk_ow_force();                          /* FUN_00077624 */
        if (NG) __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0e3c) */
        sk_ow_norm();                           /* FUN_00077550 */
        u = x1_00;
    }
    u = sk_elem_reserve(*(uint64_t *)(x19 + 0x10), u, (void*)0x0064e838, (void*)0x004c0690); /* FUN_0019c2b0 */
    sk_ow_done();                               /* FUN_00077580 */
    if ((x20 & 1) == 0)
        sk_elem_retain_f();                     /* FUN_0019d7ac */
    else {
        sk_elem_destroy();                      /* FUN_0019cc64 */
        *(uint64_t *)(x19 + 0x10) = 0;
    }
    sk_free(NULL);                              /* FUN_0036b118 */
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0e3c @ 0x001a0e3c   (est. swift_array_reserve_variant6)
 * Ghidra: long FUN_001a0e3c(...)
 * Element-specific reserve variant (DAT_00657658 / DAT_004f2138).
 * Confidence: medium
 * Notes: FUN_0019c348 / FUN_0019d888 / FUN_0019cbd4 / FUN_0036b118.
 */
long swift_array_reserve_variant6(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0ef0) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x00657658, (void*)0x004f2138); /* FUN_0019c348 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d888 */
    else {
        sk_elem_destroy();                              /* FUN_0019cbd4 */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0ef0 @ 0x001a0ef0   (est. swift_array_reserve_variant7)
 * Ghidra: long FUN_001a0ef0(...)
 * Element-specific reserve variant (LAB_00657638 / DAT_004f2118).
 * Confidence: medium
 * Notes: FUN_0019c3a4 / FUN_0019d960 / FUN_0019ccec / FUN_0036b118.
 */
long swift_array_reserve_variant7(uint64_t flags, uint64_t need, uint64_t uniq, long arr)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a0fa4) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve(elem, cap, (void*)0x00657638, (void*)0x004f2118); /* FUN_0019c3a4 */
    if ((flags & 1) == 0)
        sk_elem_retain(arr + 0x20, elem, ret + 0x20);   /* FUN_0019d960 */
    else {
        sk_elem_destroy();                              /* FUN_0019ccec */
        *(uint64_t *)(arr + 0x10) = 0;
    }
    sk_free((void *)arr);                                   /* FUN_0036b118 */
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a0fa4 @ 0x001a0fa4   (est. swift_array_reserve_variant8)
 * Ghidra: long FUN_001a0fa4(...)
 * Reserve variant that reallocates with the element destructor/accessor
 * (FUN_0019c44c) and adjusts the element offset (param_5+0x50 byte).
 * Confidence: medium
 * Notes: FUN_0019c44c / FUN_001e5320 / FUN_0019ce60 / FUN_0036b118.
 */
long swift_array_reserve_variant8(uint64_t flags, uint64_t need, uint64_t uniq, long arr, long p5)
{
    uint64_t cap = need;
    if ((uniq & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0)
                __builtin_trap();               /* SoftwareBreakpoint(1,0x1a108c) */
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((uint64_t)cap <= (uint64_t)need) cap = need;
        }
    }
    uint64_t elem = *(uint64_t *)(arr + 0x10);
    long ret = sk_elem_reserve_b2(elem, cap, p5);       /* FUN_0019c44c */
    uint64_t off = (uint64_t)*(uint8_t *)(*(long *)(p5 - 8) + 0x50);
    off = off + 0x20 & (off ^ 0xffffffffffffffff);
    if ((flags & 1) == 0)
        sk_elem_retain_g(0, elem, ret + off, arr, p5);  /* FUN_001e5320 */
    else {
        sk_elem_retain_h(arr + off, elem, ret + off, p5); /* FUN_0019ce60 */
        *(uint64_t *)(arr + 0x10) = 0;
        sk_free((void *)arr);                                   /* FUN_0036b118 */
    }
    return ret;
}

/*--------------------------------------------------------------------*/
/* FUN_001a1090 @ 0x001a1090   (est. sk_sched_lock_release_path)
 * Ghidra: void FUN_001a1090(void)
 * Scheduler lock release / context-restore sequence: runs a series of lock and
 * CPU-context helpers then dispatches through a saved function pointer.
 * Confidence: low (opaque indirect dispatch)
 * Notes: FUN_0034a74c / FUN_00354db8 / FUN_00310f34 / FUN_0034eb10 + indirect.
 */
void sk_sched_lock_release_path(void)
{
    sk_lock_w();        /* FUN_0034a74c */
    sk_lock_x();        /* FUN_00354db8 */
    sk_lock_y();        /* FUN_00310f34 */
    sk_lock_z();        /* FUN_0034eb10 */
    x8_fn();            /* indirect dispatch */
}

/*--------------------------------------------------------------------*/
/* FUN_001a10d4 @ 0x001a10d4   (est. sk_sched_thread_enqueue)
 * Ghidra: void FUN_001a10d4(...)
 * Thunk: enqueues a thread (param_2) into the run queue via FUN_001a9064,
 * passing the thread as both element and key.
 * Confidence: medium
 */
void sk_sched_thread_enqueue(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    sk_sched_enqueue_core(a, b, b, c, d);   /* FUN_001a9064 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a10e4 @ 0x001a10e4   (est. sk_sched_queue_node_alloc)
 * Ghidra: undefined1 [16] FUN_001a10e4(undefined8 param_1, undefined8 param_2)
 * Allocates a 0x20-byte run-queue node (tag 7), stores the two payload words,
 * and returns a {vtable=FUN_0001a1c8, node} pair.
 * Confidence: medium
 * Notes: FUN_0036a940(0x678d78, 0x20, 7); vtable FUN_0001a1c8.
 */
reg16 sk_sched_queue_node_alloc(uint64_t a, uint64_t b)
{
    long node = (long)sk_alloc_special(0x678d78, 0x20, 7);   /* FUN_0036a940 */
    *(uint64_t *)(node + 0x10) = a;
    *(uint64_t *)(node + 0x18) = b;
    return (reg16){ FUN_0001a1c8, node };
}

/*--------------------------------------------------------------------*/
/* FUN_001a1138 @ 0x001a1138   (est. sk_sched_runqueue_requeue)
 * Ghidra: void FUN_001a1138(...)
 * Requeue/reschedule path: computes run-queue slots from the current CPU and
 * thread accounting, moves the thread between ready queues, and re-arms the
 * budget. Falls through to the fatal-error path on inconsistent state.
 * Confidence: low (heavy inlining, unaff regs, multiple SBORROW checks)
 * Notes: FUN_0008e518 (cpu), FUN_00377824 (lock), DAT_00658c00 dispatch slot,
 *   FUN_00084180 (yield), FUN_001afe4c fatal; traps at 0x1a14ec-0x1a1534.
 */
void sk_sched_runqueue_requeue(uint64_t p1, uint64_t p2, long p3, void (*cb)(uint64_t, long),
                               uint64_t p5, uint64_t p6, uint64_t p7)
{
    reg16 cpu = sk_cpu_current();                   /* FUN_0008e518 */
    long cput = cpu.hi;
    uint64_t t = p7;
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));        /* DAT_00658c00 */
    sk_lock_aa();                                   /* FUN_003493c4 */
    sk_lock_ab();                                   /* FUN_0034cde8 */
    dispatch_slot(0);                               /* DAT_00658c00 */
    sk_lock_ac();                                   /* FUN_0034d7fc */
    FUN_00027754(t);                                /* FUN_00027754 */
    sk_lock_ad();                                   /* FUN_00351bec */
    sk_lock_ae();                                   /* FUN_00353efc */
    sk_lock_af();                                   /* FUN_00350494 */
    long v6 = x8_fn();                              /* indirect */
    long rq = cpu.lo;
    reg16 v = FUN_00348b94();
    FUN_00377824(v.lo, v.hi, p6);                   /* lock */
    long budget = *(long *)(rq + 0x10) - cput;
    if (SBORROW8(*(long *)(rq + 0x10), cput)) __builtin_trap();   /* 0x1a14ec */
    budget -= p3;
    if (SBORROW8(budget + cput, p3)) __builtin_trap();           /* 0x1a14f0 */
    if (SBORROW8(v6, cput)) __builtin_trap();                    /* 0x1a14f4 */
    long rem = (v6 - cput) - budget;
    if (SBORROW8(v6 - cput, budget)) __builtin_trap();           /* 0x1a14f8 */
    sk_lock_ag();                                   /* FUN_0034ada0 */
    uint64_t elem_off = (uint64_t)*(uint8_t *)(x16_00 + 0x50) + 0x20 &
                        ((uint64_t)*(uint8_t *)(x16_00 + 0x50) ^ 0xffffffffffffffff);
    long stride = *(long *)(x8_01 + 0x48);
    long slot_lo = rq + elem_off;
    long slot_a = slot_lo + stride * cput;
    long slot_b = slot_a + stride * p3;
    uint64_t u8 = FUN_00310f64(p7);                 /* FUN_00310f64 */
    sk_lock_ah(u8, v6);                             /* FUN_003511d8 */
    long u9 = x8_fn();
    if (u9 == 0) {
        sk_lock_ai();                               /* FUN_0035156c */
        sk_schedule_yield();                        /* FUN_00084180 */
        x9_fn();
        long s = sv_8;
        long e = sv_8 + cput;
        if (SCARRY8(sv_8, cput)) __builtin_trap();           /* 0x1a1530 */
        fn2 = *(code_fn **)(x16 + 0x10);
        sk_lock_aj();                               /* FUN_003514a0 */
        fn2();
        if (s <= e) {
            fn1 = (code_fn *)FUN_00310bc8(p7);
            v = FUN_003509d4();
            uint64_t r = fn1(v.lo, v.hi, slot_lo, p6, p7);
            cb(r, p3);
            if (SCARRY8(e, rem)) __builtin_trap();              /* 0x1a1534 */
            sk_lock_ak();                           /* FUN_003589d8 */
            sk_lock_al();                           /* FUN_00351750 */
            sk_lock_am();                           /* FUN_0034ce08 */
            x9_00_fn();
            v = FUN_003509b0();
            fn2(v.lo, v.hi, p6);
            if (e + rem <= sv_8) {
                v = FUN_0009461c();
                fn1(v.lo, v.hi, slot_b, p6, p7);
                /* LAB_001a1474 */
                fn3 = (code_fn *)FUN_000277b8(stride);
                sk_alloc_pages(rq, 0);              /* FUN_0036b270 */
                sk_lock_am();                       /* FUN_0034ce08 */
                fn3();
                uint64_t u = FUN_0034e33c();
                x8_04_fn(u, p6);
                FUN_00310bf8(p7);                   /* FUN_00310bf8 */
                sk_lock_an();                       /* FUN_0035102c */
                sk_lock_ao();                       /* FUN_00350524 */
                sk_lock_ap();                       /* FUN_0034df74 */
                x9_01_fn();
                sk_thread_epilogue();               /* FUN_0008e500 */
                return;
            }
        }
        sk_lock_aq();                               /* FUN_00347d60 */
    } else {
        uint64_t u8b = FUN_00310b68(p7);            /* FUN_00310b68 */
        FUN_000b4390(u8b);
        long v10 = x8_03_fn();
        if (stride == 0) {
            sk_lock_ar();                           /* FUN_00350410 */
            sk_lock_as();                           /* FUN_00348074 */
        } else {
            long v3 = u9 + elem_off;
            long d = v10 - v3;
            if (d != -0x8000000000000000 || stride != -1) {
                long cnt = (stride != 0) ? d / stride : 0;
                sk_lock_at(cnt);                    /* FUN_00350c20 */
                FUN_0019cb68();
                v = FUN_00350c80();
                FUN_0019ce60(v.lo, v.hi, slot_lo, t);
                FUN_00350028();
                FUN_0019cb68();
                cb(slot_a, p3);
                FUN_0019ce60(v10 + stride * cput + stride * rem, s, slot_b, t);
                v10 += stride * v6;
                rem = (v3 + *(long *)(u9 + 0x10) * stride) - v10;
                if (rem != -0x8000000000000000 || stride != -1) {
                    long cnt2 = (stride != 0) ? rem / stride : 0;
                    FUN_0019cb68(cnt2, v10, t);
                    *(uint64_t *)(u9 + 0x10) = 0;
                    sk_free((void *)u9);                    /* FUN_0036b118 */
                    goto requeue_done;
                }
            }
            sk_lock_ar();                           /* FUN_00350410 */
            sk_lock_au();                           /* FUN_0034834c */
        }
        sk_lock_av();                               /* FUN_00351be0 */
    }
    /* fallthrough */
requeue_done:
    sk_swift_fatal(0, 0, 0);   /* FUN_001afe4c — noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1564 @ 0x001a1564   (est. sk_sched_run_foreach)
 * Ghidra: void FUN_001a1564(void)
 * Runs a callback over the ready queue with the callback FUN_00346d60.
 * Confidence: medium
 */
void sk_sched_run_foreach(void) { sk_sched_queue_foreach((void*)0x00346d60); } /* FUN_001a157c */

/*--------------------------------------------------------------------*/
/* FUN_001a157c @ 0x001a157c   (est. sk_sched_queue_foreach)
 * Ghidra: void FUN_001a157c(void)
 * Iterates the ready queue: unless the queue is locked (FUN_003592f0), copies
 * the head element and invokes the caller-supplied callback (unaff_x19).
 * Confidence: medium
 * Notes: FUN_003592f0 (try-lock), FUN_0006b3f4.
 */
void sk_sched_queue_foreach()
{
    uint32_t locked = FUN_003592f0();
    *x20 = x21;
    if ((locked & 1) == 0) {
        FUN_0006b3f4(*(uint64_t *)(x21 + 0x10));
        long r = x19_fn();          /* callback */
        *x20 = r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a15c4 @ 0x001a15c4   (est. sk_sched_queue_push_elem)
 * Ghidra: void FUN_001a15c4(void)
 * Pushes one element onto the queue: if the queue can grow (FUN_003a261c),
 * reallocates with capacity len+1 via FUN_001a0a70.
 * Confidence: medium
 */
void sk_sched_queue_push_elem(void)
{
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);          /* FUN_003a261c */
    *x20 = *q;
    if ((ok & 1) == 0)
        *q = FUN_001a0a70(0, *(long *)(*q + 0x10) + 1, 1, *q,
                          (void*)0x00657620, (void*)0x004f2100, 0x6562f8, (void*)0x004e8108);
    *x20 = *q;
}

/*--------------------------------------------------------------------*/
/* FUN_001a1648 @ 0x001a1648   (est. sk_sched_queue_grow_if_needed)
 * Ghidra: void FUN_001a1648(long param_1, code *param_2)
 * Grows the queue via the supplied allocator if its capacity is below
 * param_1+1.
 * Confidence: medium
 */
void sk_sched_queue_grow_if_needed(long need, void *(*alloc_fn)(uint64_t, long, uint64_t))
{
    long *q = x20;
    if ((long)(*(unsigned long *)(*q + 0x18) >> 1) < need + 1) {
        *q = (long)alloc_fn(1 < *(unsigned long *)(*q + 0x18), need + 1, 1);
        *x20 = *q;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a168c @ 0x001a168c   (est. sk_sched_queue_grow_push)
 * Ghidra: void FUN_001a168c(long param_1)
 * Grows the queue to fit param_1+1 entries and pushes an element via the
 * shared realloc FUN_001a0a70.
 * Confidence: medium
 */
void sk_sched_queue_grow_push(long need)
{
    long *q = x20;
    uint64_t cap = *(unsigned long *)(*q + 0x18);
    if ((long)(cap >> 1) < need + 1)
        *q = FUN_001a0a70(1 < cap, need + 1, 1, *q,
                          (void*)0x00657620, (void*)0x004f2100, 0x6562f8, (void*)0x004e8108);
    *x20 = *q;
}

/*--------------------------------------------------------------------*/
/* FUN_001a16e8 @ 0x001a16e8   (est. swift_collection_apply_thunk)
 * Ghidra: void FUN_001a16e8(undefined8 param_1, undefined8 param_2)
 * Thunk: applies FUN_001a0794 (array reserve) as a callback over the
 * collection.
 * Confidence: medium
 * Notes: FUN_001dd88c(param_1, param_2, FUN_001a0794).
 */
void swift_collection_apply(uint64_t a, uint64_t b) { sk_collection_apply_shared(a, b, sk_array_reserve_fa4); } /* FUN_001dd88c */

/*--------------------------------------------------------------------*/
/* FUN_001a1754 @ 0x001a1754   (est. sk_sched_queue_append_pair)
 * Ghidra: void FUN_001a1754(void)
 * Appends a two-word (key, value) pair to the queue: reserves capacity for
 * len+1, sets len to len+1, and stores the pair at the tail.
 * Confidence: medium
 * Notes: FUN_0008409c, FUN_001a157c(FUN_00072c0c), FUN_001a1648(FUN_00072c0c).
 */
void sk_sched_queue_append_pair(void)
{
    FUN_0008409c();
    sk_sched_queue_foreach(FUN_00072c0c);       /* FUN_001a157c */
    long len = *(long *)(*x20 + 0x10);
    sk_sched_queue_grow_if_needed(len, FUN_00072c0c);   /* FUN_001a1648 */
    long q = *x20;
    *(long *)(q + 0x10) = len + 1;
    long tail = q + len * 0x10;
    *(uint64_t *)(tail + 0x20) = x21;
    *(uint64_t *)(tail + 0x28) = x19;
    *x20 = q;
}

/*--------------------------------------------------------------------*/
/* FUN_001a17d0 @ 0x001a17d0   (est. sk_sched_queue_append_elems)
 * Ghidra: void FUN_001a17d0(undefined8 param_1)
 * Appends a block of elements to the queue: reserves capacity for len+1,
 * sets len to len+1, and copies param_1 into the tail slot via FUN_00310d98.
 * Confidence: medium
 * Notes: FUN_001a157c(FUN_001a0d1c), FUN_001a1648(FUN_001a0d1c), FUN_00310d98.
 */
void sk_sched_queue_append_elems(uint64_t elem)
{
    sk_sched_queue_foreach(FUN_001a0d1c);       /* FUN_001a157c */
    long len = *(long *)(*x20 + 0x10);
    sk_sched_queue_grow_if_needed(len, FUN_001a0d1c);   /* FUN_001a1648 */
    long q = *x20;
    *(long *)(q + 0x10) = len + 1;
    FUN_00310d98(elem, q + len * 0x20 + 0x20);  /* FUN_00310d98 */
    *x20 = q;
}

/*--------------------------------------------------------------------*/
/* FUN_001a1854 @ 0x001a1854   (est. sk_sched_queue_push_batch)
 * Ghidra: void FUN_001a1854(undefined8 param_1, undefined8 param_2)
 * Pushes a batch of elements through the guarded append path.
 * Confidence: medium
 * Notes: FUN_001a1894(param_1, param_2, DAT_001a1630, FUN_001a16e8,
 *   LAB_001a1750).
 */
void sk_sched_queue_push_batch(uint64_t a, uint64_t b)
{
    sk_lock_guarded(a, b, (void*)0x001a1630, swift_collection_apply, (void*)0x001a1750); /* FUN_001a1894 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1894 @ 0x001a1894   (est. sk_lock_guarded)
 * Ghidra: void FUN_001a1894(...)
 * Runs a callback under an irqsave/irqrestore lock: saves flags, runs param_3
 * and the saved callback, then restores flags. Ends with an unrecoverable
 * jumptable dispatch.
 * Confidence: medium
 * Notes: FUN_00357cb4 (spin_irqsave) / FUN_00350858 / FUN_00350560 /
 *   FUN_0034b508 / FUN_00357c74 (irqrestore); jumptable at 0x001a18f4.
 */
void sk_lock_guarded(uint64_t a, uint64_t b, void (*cb)(uint64_t), uint64_t p4, void (*jmp)(void))
{
    sk_spin_irqsave(&flags);                    /* FUN_00357cb4 */
    FUN_00350858();
    cb(x1);                                     /* (*param_3)(extraout_x1) */
    FUN_00350560();
    x19_fn();                                   /* saved callback */
    FUN_0034b508();
    sk_irqrestore(flags);                       /* FUN_00357c74 */
    jmp();                                      /* jumptable 0x001a18f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a18f8 @ 0x001a18f8   (est. swift_buffer_append_region)
 * Ghidra: void FUN_001a18f8(long param_1)
 * Appends the element region of param_1 to a Swift UnsafeMutableBufferPointer
 * queue, growing the backing store as needed. Fatals on insufficient space or
 * under-estimated new-elements count.
 * Confidence: high (string-matched fatal "UnsafeMutableBufferPointer",
 *   "Insufficient space allocated to c", "newElements under-estimatedCount")
 * Notes: FUN_001a06b8 grow, FUN_0019da34 copy, FUN_001a27f0 reserve,
 *   FUN_0036b118 free; strings at 0x005cdbe0 / 0x005cdc10 / 0x005cdb30 /
 *   0x005cdba0.
 */
void swift_buffer_append_region(long src)
{
    uint64_t n = *(uint64_t *)(src + 0x10);
    if (SCARRY8(*(long *)(*x20 + 0x10), n)) __builtin_trap();  /* 0x1a1a08 */
    FUN_001a06b8(*(long *)(*x20 + 0x10) + n, 1, 0x656120, (void*)0x004e7f10, 0x656118, (void*)0x004e7f08);
    long q = *x20;
    uint64_t avail = (*(uint64_t *)(q + 0x18) >> 1) - *(long *)(q + 0x10);
    if ((long)avail < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    long dst = q + *(long *)(q + 0x10) * 0x28;
    uint64_t copied;
    if (*(long *)(src + 0x10) == 0) {
        copied = 0;
    } else {
        if (avail < n) {
            goto insuff;                        /* 0x1a1aa0 */
        }
        FUN_0019da34(src + 0x20, n, dst + 0x20, 0x656118, (void*)0x004e7f08);  /* copy */
        copied = n;
    }
    dst = FUN_001a27f0(0, copied, dst + 0x20, avail);
    if ((long)n <= dst) {
        sk_free((void *)src);                           /* FUN_0036b118 */
        if (dst != 0) {
            if (SCARRY8(*(long *)(q + 0x10), dst)) __builtin_trap();  /* 0x1a1ac4 */
            *(long *)(q + 0x10) = *(long *)(q + 0x10) + dst;
        }
        *x20 = q;
        return;
    }
    /* 0x1a1aa0 */
insuff:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_insufficient_space, 0x33, 2,
                   s_swift_array, 0x11, 2, 0x767, 1);   /* 0x767 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1ac4 @ 0x001a1ac4   (est. sk_sched_queue_merge)
 * Ghidra: void FUN_001a1ac4(void)
 * Merges a batch of elements into the run queue: computes total, grows the
 * queue, and inserts elements from a bitmask-indexed source, updating the
 * length. Complex bit-reversal indexing into the source block.
 * Confidence: low (complex inlining, bit twiddling, unaff regs)
 * Notes: FUN_000b4594 / FUN_00353c48 / FUN_001a0640 / FUN_001a27f0 /
 *   FUN_00284148 / FUN_0036b118 / FUN_000b45b0; traps at 0x1a1b98-0x1a1d08.
 */
void sk_sched_queue_merge(void)
{
    reg16 src = FUN_000b4594();
    long n = *(long *)(src.lo + 0x10);
    FUN_00353c48();
    if (SCARRY8(x8, n)) __builtin_trap();               /* 0x1a1b98 */
    FUN_001a0640(x8 + n, 1, FUN_00072c0c);
    long q = *x20;
    long avail = (*(uint64_t *)(q + 0x18) >> 1) - *(long *)(q + 0x10);
    if (avail < 0) {
        FUN_003487a4();
        FUN_003524c8();
        sk_swift_fatal(0, 0, 0);                               /* noreturn */
    }
    long dst = q + *(long *)(q + 0x10) * 0x10;
    FUN_00351b78(&stack_arg, dst + 0x20);
    reg16 v = FUN_00284148();
    FUN_00350500(v.lo, v.hi, dst + 0x20);
    long got = FUN_001a27f0();
    if (got < n) {
        FUN_003488bc(1);
        FUN_00355594();
        FUN_0034a3d8();
        FUN_003504b8();
        sk_swift_fatal(0, 0, 0);                               /* noreturn */
    }
    if (got != 0) {
        if (SCARRY8(*(long *)(q + 0x10), got)) __builtin_trap();   /* 0x1a1bf8 */
        *(long *)(q + 0x10) = *(long *)(q + 0x10) + got;
    }
    if (v.lo != avail) {
        /* LAB_001a1b74 */
        sk_free((void *)lv3);                                   /* FUN_0036b118 */
        *x20 = q;
        FUN_000b45b0(src.hi);                           /* FUN_000b45b0 */
        return;
    }
    long len = *(long *)(q + 0x10);
    uint64_t idx = is_48;
    if (is_48 == 0) {
        FUN_00358984(is_38);
        do {
            long next = lv12 + 1;
            if (SCARRY8(lv12, 1)) __builtin_trap();     /* 0x1a1d08 */
            if (x26 <= next) goto merge_done;
            lv12 = next;
        } while (*(long *)(lv4 + next * 8) == 0);
        FUN_0034f264();
        idx = x11_00 & x9_01;
        u8 = x10 | x8_00 << 6;
        lv12 = x8_00;
    } else {
        FUN_0034f264();
        idx = x11 & x9;
        FUN_00358984();
        u8 = x9_00;
    }
    uint64_t *slot = (uint64_t *)(*(long *)(lv3 + 0x30) + u8 * 0x10);
    uint64_t v0 = slot[0];
    uint64_t v1 = slot[1];
    is_40 = lv12;
    is_48 = idx;
    sk_alloc_pages(v1, 0);                              /* thunk_FUN_0036b270 */
    for (;;) {
        uint64_t cap = *(uint64_t *)(q + 0x18) >> 1;
        if ((long)cap < len + 1) {
            FUN_0006b42c();
            FUN_00350774();
            q = FUN_001a0c98();
            *x20 = q;
            cap = *(uint64_t *)(q + 0x18) >> 1;
        }
        while (len < (long)cap) {
            uint64_t *dst_slot = (uint64_t *)(q + 0x20 + len * 0x10);
            dst_slot[0] = v0;
            dst_slot[1] = v1;
            len++;
            while (idx == 0) {
                bool carry = SCARRY8(lv12, 1);
                lv12++;
                if (carry) __builtin_trap();            /* 0x1a1d04 */
                if (x26 <= lv12) {
                    *(long *)(q + 0x10) = len;
                    goto merge_done;
                }
                idx = *(uint64_t *)(lv4 + lv12 * 8);
            }
            uint64_t rev = (idx & 0xaaaaaaaaaaaaaaaa) >> 1 | (idx & 0x5555555555555555) << 1;
            rev = (rev & 0xcccccccccccccccc) >> 2 | (rev & 0x3333333333333333) << 2;
            rev = (rev & 0xf0f0f0f0f0f0f0f0) >> 4 | (rev & 0x0f0f0f0f0f0f0f0f) << 4;
            rev = (rev & 0xff00ff00ff00ff00) >> 8 | (rev & 0x00ff00ff00ff00ff) << 8;
            rev = (rev & 0xffff0000ffff0000) >> 16 | (rev & 0x0000ffff0000ffff) << 16;
            slot = (uint64_t *)(*(long *)(lv3 + 0x30) + sk_lzcount(rev >> 0x20 | rev << 0x20) * 0x10
                                + lv12 * 0x400);
            v0 = slot[0];
            v1 = slot[1];
            idx = idx - 1 & idx;
            is_40 = lv12;
            is_48 = idx;
            sk_alloc_pages(v1, 0);                      /* thunk_FUN_0036b270 */
        }
        *(long *)(q + 0x10) = len;
    }
merge_done:
    sk_free((void *)lv3);                                       /* FUN_0036b118 */
    *x20 = q;
    FUN_000b45b0(src.hi);                               /* FUN_000b45b0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1d08 @ 0x001a1d08   (est. sk_sched_queue_append_str)
 * Ghidra: void FUN_001a1d08(void)
 * Appends a string/region to the queue: grows the queue, copies elements via
 * the string accessor (FUN_0019d6d0), and updates the length.
 * Confidence: low (unaff regs, inlined)
 * Notes: FUN_00357ca0 / FUN_00353c48 / FUN_001a0640 / FUN_001a27f0 /
 *   FUN_00354dc4 / FUN_00357c44 / FUN_0036b118; fatal on insufficient space.
 */
void sk_sched_queue_append_str(void)
{
    reg16 s = FUN_00357ca0();
    long src = s.lo;
    uint64_t n = *(uint64_t *)(src + 0x10);
    FUN_00353c48();
    if (SCARRY8(x8, n)) __builtin_trap();               /* 0x1a1de0 */
    FUN_001a0640(x8 + n, 1, FUN_001a0d1c);
    FUN_00358024();
    uint64_t avail = x9 - x8_00;
    if ((long)avail < 0) {
        FUN_003487a4();
        FUN_003524c8();
        sk_swift_fatal(0, 0, 0);                               /* noreturn */
    }
    long dst = x23 + x8_00 * 0x20;
    uint64_t copied;
    if (*(long *)(src + 0x10) == 0) {
        copied = 0;
    } else {
        if (avail < n) {
            FUN_003488bc(1);
            FUN_00356870();
            goto str_fatal;
        }
        FUN_0019d6d0(src + 0x20, n, dst + 0x20);        /* copy */
        copied = n;
    }
    src = FUN_001a27f0(0, copied, dst + 0x20, avail);
    if ((long)n <= src) {
        FUN_00354dc4();
        uint64_t u = FUN_0036b118();
        if (avail != 0) {
            if (SCARRY8(*(long *)(x23 + 0x10), avail)) __builtin_trap();  /* 0x1a1e30 */
            *(uint64_t *)(x23 + 0x10) = *(long *)(x23 + 0x10) + avail;
        }
        *x20 = x23;
        FUN_00357c44(u, s.hi);                          /* FUN_00357c44 */
        return;
    }
    FUN_003488bc(1);
    FUN_00355594();
str_fatal:
    FUN_0034a3d8();
    FUN_003504b8();
    sk_swift_fatal(0, 0, 0);                                   /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1e34 @ 0x001a1e34   (est. sk_sched_queue_append_str2)
 * Ghidra: void FUN_001a1e34(void)
 * String/region append variant using the FUN_0019d15c copy helper.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00357ca0 / FUN_001a0640(FUN_00072c0c) / FUN_001a27f0 /
 *   FUN_0019d15c / FUN_00357c44 / FUN_0036b118.
 */
void sk_sched_queue_append_str2(void)
{
    reg16 s = FUN_00357ca0();
    long src = s.lo;
    uint64_t n = *(uint64_t *)(src + 0x10);
    FUN_00353c48();
    if (SCARRY8(x8, n)) __builtin_trap();               /* 0x1a1f0c */
    FUN_001a0640(x8 + n, 1, FUN_00072c0c);
    FUN_00358024();
    uint64_t avail = x9 - x8_00;
    if ((long)avail < 0) {
        FUN_003487a4();
        FUN_003524c8();
        sk_swift_fatal(0, 0, 0);                               /* noreturn */
    }
    long dst = x23 + x8_00 * 0x10;
    uint64_t copied;
    if (*(long *)(src + 0x10) == 0) {
        copied = 0;
    } else {
        if (avail < n) {
            FUN_003488bc(1);
            FUN_00356870();
            goto str2_fatal;
        }
        FUN_0019d15c(src + 0x20, n, dst + 0x20);        /* copy */
        copied = n;
    }
    src = FUN_001a27f0(0, copied, dst + 0x20, avail);
    if ((long)n <= src) {
        FUN_00354dc4();
        FUN_0036b118();
        if (avail != 0) {
            if (SCARRY8(*(long *)(x23 + 0x10), avail)) __builtin_trap();  /* 0x1a1f5c */
            *(uint64_t *)(x23 + 0x10) = *(long *)(x23 + 0x10) + avail;
        }
        *x20 = x23;
        FUN_00357c44(s.hi);                             /* FUN_00357c44 */
        return;
    }
    FUN_003488bc(1);
    FUN_00355594();
str2_fatal:
    FUN_0034a3d8();
    FUN_003504b8();
    sk_swift_fatal(0, 0, 0);                                   /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a1f5c @ 0x001a1f5c   (est. swift_buffer_append_region2)
 * Ghidra: void FUN_001a1f5c(long param_1)
 * Buffer append variant (element descriptors 0x6562e8/0x6562f0).
 * Confidence: high (string-matched fatal as FUN_001a18f8)
 * Notes: FUN_001a06b8 / FUN_0019da34 / FUN_001a27f0 / FUN_0036b118;
 *   strings at 0x005cdbe0 / 0x005cdc10 / 0x005cdb30 / 0x005cdba0.
 */
void swift_buffer_append_region2(long src)
{
    uint64_t n = *(uint64_t *)(src + 0x10);
    if (SCARRY8(*(long *)(*x20 + 0x10), n)) __builtin_trap();  /* 0x1a206c */
    FUN_001a06b8(*(long *)(*x20 + 0x10) + n, 1, 0x6562e8, (void*)0x004e80f8, 0x6562f0, (void*)0x004e8100);
    long q = *x20;
    uint64_t avail = (*(uint64_t *)(q + 0x18) >> 1) - *(long *)(q + 0x10);
    if ((long)avail < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    long dst = q + *(long *)(q + 0x10) * 0x28;
    uint64_t copied;
    if (*(long *)(src + 0x10) == 0) {
        copied = 0;
    } else {
        if (avail < n) {
            goto insuff2;                               /* 0x1a2104 */
        }
        FUN_0019da34(src + 0x20, n, dst + 0x20, 0x6562f0, (void*)0x004e8100);  /* copy */
        copied = n;
    }
    dst = FUN_001a27f0(0, copied, dst + 0x20, avail);
    if ((long)n <= dst) {
        sk_free((void *)src);                                   /* FUN_0036b118 */
        if (dst != 0) {
            if (SCARRY8(*(long *)(q + 0x10), dst)) __builtin_trap();  /* 0x1a2128 */
            *(long *)(q + 0x10) = *(long *)(q + 0x10) + dst;
        }
        *x20 = q;
        return;
    }
insuff2:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_insufficient_space, 0x33, 2,
                   s_swift_array, 0x11, 2, 0x4eb, 1);   /* 0x4eb */
}

/*--------------------------------------------------------------------*/
/* FUN_001a2128 @ 0x001a2128   (est. sk_sched_queue_batch_insert)
 * Ghidra: void FUN_001a2128(...)
 * Inserts a batch of elements into the run queue: grows the queue to fit the
 * incoming count, copies the elements, and conditionally re-arms the queue
 * accounting and notification loop. Complex conditional tail (unaff regs).
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00 dispatch slot, FUN_00377824, FUN_001a26e0,
 *   FUN_001a2740, FUN_001a27f0, FUN_001a16e8; fatal on shortfall; traps at
 *   0x1a2568 / 0x1a2598.
 */
void sk_sched_queue_batch_insert(uint64_t p1, uint64_t p2, long p3, uint64_t p4)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    reg16 v = FUN_00353a24();
    FUN_00349b3c(v.lo, *(uint64_t *)(v.hi + 0x10));
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003490ec();
    uint64_t u3 = FUN_00310d68(0);
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40));/* DAT_00658c00 */
    FUN_003493c4();
    FUN_0034c684();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a62c();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aa28();
    FUN_00349830();
    FUN_000dbf08();
    uint64_t lock = FUN_00377824();         /* lock */
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b05c();
    FUN_00354f34(p4);
    FUN_00350c80();
    long n = x8_01_fn();                    /* indirect */
    if (SCARRY8(*(long *)(*x20 + 0x10), n)) __builtin_trap();  /* 0x1a2568 */
    uint64_t u6 = FUN_0034e384(*(long *)(*x20 + 0x10) + n);
    FUN_001dd614(u6, 1);
    long q = *x20;
    FUN_00357c20(*(uint8_t *)(x16 + 0x50));
    long stride = *(long *)(x16 + 0x48);
    FUN_001a26e0(q + x8_02 + stride * *(long *)(q + 0x10),
                 (*(uint64_t *)(q + 0x18) >> 1) - *(long *)(q + 0x10));
    FUN_003569b4();
    FUN_003504f4();
    long *slot = (long *)FUN_001a2740();
    FUN_0035113c();
    long got = FUN_001a27f0();
    if (got < n) {
        FUN_00348b7c(0x4eb);
        FUN_00355594();
        FUN_0034a3d8();
        FUN_003504b8();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
    FUN_0034dfe4();
    (**(code_fn **)(x16_01 + 8))();
    if (0 < got) {
        if (SCARRY8(*(long *)(q + 0x10), got)) __builtin_trap();  /* 0x1a2598 */
        *(long *)(q + 0x10) = *(long *)(q + 0x10) + got;
    }
    if ((slot == x20) && (p3 != x24)) {
        uint64_t len = *(uint64_t *)(q + 0x10);
        FUN_0034b278();
        v = FUN_003508f0();
        uint64_t u6b = FUN_00377bec(v.lo, v.hi, lock);
        FUN_00354474();
        FUN_00354bec();
        uint64_t u9 = FUN_0035245c();
        x9_fn(u9, u6b);
        FUN_0035a3b8();
        uint64_t u10 = x8_03 & 0xffffffffffff | 0xe3ba000000000000;
        FUN_00359ca4();
        for (;;) {
            v = FUN_0035072c();
            x9_00_fn(u10, v.lo, v.hi, u3);
            v = FUN_00351330();
            int eq = FUN_000839f8(v.lo, v.hi, x1);
            fn = *(code_fn **)(x8_03 - 8);
            if (eq == 1) break;
            FUN_0009461c();
            fn(x8_04);
            FUN_001a16e8(len, x24);
            long q2 = *x20;
            uint64_t cap2 = *(uint64_t *)(q2 + 0x18) >> 1;
            long base = q2 + x8_02;
            for (;;) {
                v = FUN_00350a34(base);
                x9_00_fn(u10, v.lo, v.hi, u3);
                uint64_t u9b = FUN_0034e1b0(sv_48);
                if (eq) break;
                fn2 = *(code_fn **)(x16 + 0x20);
                v = FUN_00353390(u9b, sv_48);
                fn2(v.lo, v.hi, x1);
                if (len == cap2) {
                    /* loop-end condition */
                }
                if ((long)cap2 <= (long)len) {
                    FUN_0034d688();
                    FUN_003508f0();
                    x8_05_fn();
                    goto insert_done;
                }
                u9b = FUN_0035466c();
                fn(x8_04, u9b, u3);
                v = FUN_003510ac();
                fn2(x16 + 0x20 & 0xffffffffffff | 0x48d8000000000000, v.lo, v.hi, x1);
                len++;
                x9_fn(q, u4, u6b);
                base = stride;
            }
            FUN_003508b4();
            fn(x8_04);
insert_done:
            *(uint64_t *)(q2 + 0x10) = len;
            q = sv_30;
        }
        FUN_00351714();
        fn();
        FUN_00356ac4(*(uint64_t *)(x16_00 + 8));
        x8_07_fn();
        FUN_0009461c();
        fn();
    } else {
        FUN_00356ac4(*(uint64_t *)(x16_00 + 8));
        x8_06_fn();
    }
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a25c4 @ 0x001a25c4   (est. sk_sched_lock_sequence)
 * Ghidra: void FUN_001a25c4(void)
 * Scheduler lock/context sequence followed by two indirect dispatches.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034c2e8 / FUN_00310f94 / FUN_00350164 / FUN_00351d18 /
 *   FUN_00310fc4 / FUN_00350c50 / FUN_003548c4 / FUN_0035056c + indirect.
 */
void sk_sched_lock_sequence(void)
{
    FUN_0034c2e8();
    FUN_00310f94(x3);
    FUN_00350164();
    x8_fn();
    FUN_00351d18();
    FUN_00310fc4();
    FUN_00350c50();
    FUN_003548c4();
    FUN_0035056c();
    x9_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a2630 @ 0x001a2630   (est. swift_buffer_precondition)
 * Ghidra: void FUN_001a2630(long param_1, long param_2)
 * Swift UnsafeMutableBufferPointer precondition check: fatals if count is
 * negative, or if count is non-zero while the base pointer is null.
 * Confidence: high (string-matched fatal "UnsafeMutableBufferPointer...")
 * Notes: strings at 0x005cdbe0 / 0x005cdc30 / 0x005cdc10.
 */
void swift_buffer_precondition(long base, long count)
{
    if (count < 0) {
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    }
    if (count == 0 || base != 0) return;
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_buf_has_null, 0x3c, 2,
                   s_swift_unsafe_buf, 0x1f, 2, 0x4c, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a26e0 @ 0x001a26e0   (est. sk_sched_count_precondition)
 * Ghidra: void FUN_001a26e0(long param_1, long param_2)
 * Precondition check for a count/length pair: fatals on negative count or on
 * non-zero count with null pointer.
 * Confidence: medium
 * Notes: FUN_00351088 / FUN_003487a4 / FUN_003488bc / FUN_00349a04 /
 *   FUN_003524c8 / fatal FUN_001afe4c.
 */
void sk_sched_count_precondition(long base, long count)
{
    if (count < 0) {
        FUN_00351088(1);
        FUN_003487a4();
    } else {
        if (count == 0 || base != 0) return;
        FUN_003488bc(1);
        FUN_00349a04();
    }
    FUN_003524c8();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a2740 @ 0x001a2740   (est. sk_sched_queue_slot)
 * Ghidra: void FUN_001a2740(void)
 * Resolves the current run-queue slot: runs lock/context helpers and
 * dispatches through the saved callback with a computed argument.
 * Confidence: low (indirect dispatch, in_x5)
 * Notes: FUN_00356940 / FUN_00353e88 / FUN_0007c028 / DAT_00658c00 /
 *   FUN_00348f38 / FUN_0035603c / FUN_003191e8 / FUN_0034c8b8 / FUN_00352920.
 */
void sk_sched_queue_slot(void)
{
    FUN_00356940();
    FUN_00353e88();
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348f38();
    reg16 v = FUN_0035603c();
    x8_00_fn(v.lo, v.hi, x5);
    FUN_003191e8();
    FUN_0034c8b8();
    FUN_00352920();
    x8_01_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a27f0 @ 0x001a27f0   (est. sk_sched_borrow_check)
 * Ghidra: void FUN_001a27f0(long param_1, long param_2)
 * Range/borrow precondition: if param_2 would borrow from param_1 (i.e.
 * param_2 < param_1), fatals after running the two lock helpers.
 * Confidence: medium
 * Notes: SBORROW8(param_2, param_1); FUN_0035047c / FUN_003480ac / fatal.
 */
void sk_sched_borrow_check(long lo, long hi)
{
    if (!SBORROW8(hi, lo)) return;
    FUN_0035047c(hi - lo);
    FUN_003480ac();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a2838 @ 0x001a2838   (est. swift_array_remove_last)
 * Ghidra: ulong FUN_001a2838(void)
 * Pops the last element from a Swift Array: shrinks the backing store if
 * needed, decrements the count, and returns the removed element. Fatals on
 * removing from an empty array.
 * Confidence: high (string-matched fatal "Can't removeLast from an empty A")
 * Notes: FUN_003a261c / FUN_0019e644 shrink; string at 0x005cdc70.
 */
uint64_t swift_array_remove_last(void)
{
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);          /* FUN_003a261c */
    *x20 = *q;
    if ((ok & 1) == 0) {
        *q = FUN_0019e644(*q);              /* shrink */
        *x20 = *q;
    }
    if (*(long *)(*q + 0x10) != 0) {
        long newlen = *(long *)(*q + 0x10) - 1;
        uint64_t el = *(uint64_t *)(*q + newlen * 8 + 0x20);
        *(long *)(*q + 0x10) = newlen;
        *x20 = *q;
        return el;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_last, 0x24, 2,
                   s_swift_array, 0x11, 2, 0x527, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a29a0 @ 0x001a29a0   (est. sk_sched_queue_notify)
 * Ghidra: void FUN_001a29a0(void)
 * Queue-notify dispatch: resolves the queue, then jumps through the saved
 * handler slot (extraout_x16+0x20).
 * Confidence: low (jumptable at 0x001a29d0 not recoverable)
 * Notes: FUN_0035a758.
 */
void sk_sched_queue_notify(void)
{
    reg16 v = FUN_0035a758();
    (**(code_fn **)(x16 + 0x20))(v.lo, x9, v.hi);   /* jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_001a29d4 @ 0x001a29d4   (est. swift_array_remove_at)
 * Ghidra: ulong FUN_001a29d4(long param_1)
 * Removes the element at index param_1 from a Swift Array, shifting the tail
 * down. Fatals with "Index out of range" if the index is invalid.
 * Confidence: high (string-matched fatal "Index out of range")
 * Notes: FUN_003a261c / FUN_0019e644 / FUN_0019cc64 shift; string at
 *   0x005cd940.
 */
uint64_t swift_array_remove_at(long index)
{
    long *q = x20;
    uint64_t ok = sk_alloc_ok(*q);          /* FUN_003a261c */
    *x20 = *q;
    if ((ok & 1) == 0) {
        *q = FUN_0019e644(*q);              /* shrink */
        *x20 = *q;
    }
    if (index < *(long *)(*q + 0x10)) {
        if (index >= 0) {
            long newlen = *(long *)(*q + 0x10) - 1;
            long slot = *q + index * 8;
            uint64_t el = *(uint64_t *)(slot + 0x20);
            FUN_0019cc64(slot + 0x28, newlen - index);  /* shift */
            *(long *)(*q + 0x10) = newlen;
            *x20 = *q;
            return el;
        }
        goto oob_neg;                       /* 0x547 */
    }
    /* 0x546 */
oob_neg:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_index_out_of_range, 0x12, 2,
                   s_swift_array, 0x11, 2, 0x546, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a2abc @ 0x001a2abc   (est. swift_array_remove_at_stride)
 * Ghidra: void FUN_001a2abc(void)
 * Removes the element at index unaff_x19 from a Swift Array with element
 * stride, shifting the tail down by one slot. Fatals on out-of-range index.
 * Confidence: medium
 * Notes: unaff_x19=index; FUN_003511b4 / FUN_003518d0 shift / FUN_0019ce60 /
 *   FUN_00354ef8; fatal FUN_001afe4c.
 */
void swift_array_remove_at_stride(void)
{
    FUN_00354a34();
    FUN_00351cc4();
    thunk_FUN_001dc298(x1);             /* FUN_001dc298 */
    long *q = x20;
    long len = *(long *)(*q + 0x10);
    if ((x19 < len) && (x19 >= 0)) {
        FUN_003511b4();
        uint8_t b = *(uint8_t *)(x16 + 0x50);
        long stride = *(long *)(x16 + 0x48);
        (**(code_fn **)(x16 + 0x20))();
        len--;
        FUN_003518d0(*q + ((uint64_t)b + 0x20 & ((uint64_t)b ^ 0xffffffffffffffff))
                     + stride * x19 + stride, len - x19);
        uint64_t u = FUN_0019ce60();
        *(long *)(*q + 0x10) = len;
        FUN_00354ef8(u, x30);
        return;
    }
    FUN_00348638(1);
    FUN_00349de8();
    sk_swift_fatal(0, 0, 0);                   /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a2b94 @ 0x001a2b94   (est. sk_sched_queue_clear_thunk)
 * Ghidra: void FUN_001a2b94(void)
 * Thunk: clears the queue via the shared helper.
 * Confidence: medium
 * Notes: FUN_001de6c4.
 */
void sk_sched_queue_clear(void) { FUN_001de6c4(); }

/*--------------------------------------------------------------------*/
/* FUN_001a2bec @ 0x001a2bec   (est. swift_buffer_init_pair)
 * Ghidra: void FUN_001a2bec(void)
 * Initializes a Swift UnsafeBufferPointer with two elements: allocates the
 * backing buffer, sets count=2, and fills both slots. Validates the element
 * count matches, else fatals.
 * Confidence: medium
 * Notes: FUN_00041138 / FUN_000867ec / FUN_0035a8fc / FUN_00355538 /
 *   FUN_0036a940 / FUN_00077630 / FUN_00353208 / FUN_00281cc0; fatal.
 */
void swift_buffer_init_pair(void)
{
    FUN_00041138();
    sk_current_tcb();                   /* FUN_000867ec */
    FUN_0035a8fc();
    FUN_00355538();
    sk_alloc_special(0, 0, 0);          /* FUN_0036a940 */
    FUN_00077630();
    *(uint64_t *)(x20 + 0x10) = 2;
    *(long *)(x20 + 0x18) = x8 / 8 << 1;
    FUN_00353208(&stack, x20 + 0x20, 2);
    long n = FUN_00281cc0();
    if (is_28 == 2) {
        if (n == 2) {
            FUN_0035847c();
            return;
        }
        FUN_003488bc(1);
        fatal_str = s_Fatal_error;
    } else {
        x19_fn(is_28, is_18, is_20);
        FUN_0035047c();
        fatal_str = s_Fatal_error;
    }
    FUN_00349ee0(fatal_str);
    FUN_00351a8c();
    sk_swift_fatal(0, 0, 0);                   /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a2cc4 @ 0x001a2cc4   (est. swift_contiguous_array_from_count)
 * Ghidra: undefined * FUN_001a2cc4(undefined8 param_1)
 * Builds a Swift ContiguousArrayBuffer with `count` elements: picks a size
 * class, allocates the buffer, initializes the slots, and validates the
 * resulting count. Fatals on invalid collection counts.
 * Confidence: high (string-matched fatal "invalid Collection: less than / more
 *   than")
 * Notes: FUN_001e67d8 / FUN_00071bd0 / FUN_00281d4c / FUN_00254fb4 /
 *   FUN_001e74ac; strings at 0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
void *swift_contiguous_array_from_count(uint64_t count)
{
    uint64_t cls = 1;
    if (0xffff < (uint32_t)count) cls = 2;
    long l = FUN_001e67d8(0, cls, count);
    if (l == 0) return &sk_empty_array;         /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_00071bd0(l, 0);
    if (l < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    long got = FUN_00281d4c(sv_40, buf + 0x20, l, count);
    if (sv_40[0] < 0x10000) {
        if (sv_38 == 1) goto check;          /* LAB_001a2d98 */
    } else if (sv_38 == 2) goto check;
    FUN_00254fb4(sv_38, sv_40[0]);
    FUN_001e74ac(sv_38, sv_40[0]);
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
check:
    if (got == l) return buf;
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x47a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a2e48 @ 0x001a2e48   (est. swift_string_from_count)
 * Ghidra: long FUN_001a2e48(undefined8 param_1)
 * Builds a Swift string with `count` characters: selects a size class, runs
 * the per-class helpers, allocates the storage, and validates the count.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_001dff60 / FUN_0019fe7c / FUN_0019c258 / FUN_00281ef4 /
 *   FUN_00255324 / FUN_0026bd30 / FUN_001d2d1c; strings at 0x005cdca0 /
 *   0x005cdce0 / 0x005cd960.
 */
long swift_string_from_count(uint64_t count)
{
    uint32_t u = (uint32_t)count;
    uint64_t cls = 3;
    if (0xffff < u) cls = 4;
    uint64_t cls2 = 2;
    if (0x7ff < u) cls2 = cls;
    uint64_t cls1 = 1;
    if (0x7f < u) cls1 = cls2;

    reg16 v = FUN_001dff60(0, cls1);
    FUN_0019fe7c(0, v.lo, v.hi);
    v = FUN_001dff60(0, cls1);
    FUN_0019fe7c(cls1, v.lo, v.hi);
    long l = FUN_0019c258(cls1, 0, &sk_cstring, (void*)0x004be910);
    long got = FUN_00281ef4(sv_40, l + 0x20, cls1, count);
    uint64_t rc2 = 3;
    if (0xffff < sv_40[0]) rc2 = 4;
    uint64_t rc2b = 2;
    if (0x7ff < sv_40[0]) rc2b = rc2;
    uint64_t rc1 = 1;
    if (0x7f < sv_40[0]) rc1 = rc2b;
    if (sv_38 == rc1) {
        if (got == cls1) return l;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    FUN_00255324(sv_38);
    v = FUN_0026bd30(0, rc1);
    FUN_001d2d1c(sv_38, v.lo, v.hi);
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a2ffc @ 0x001a2ffc   (est. swift_array_from_pair)
 * Ghidra: long FUN_001a2ffc(undefined8 param_1, undefined8 param_2)
 * Builds a Swift Array from a two-element pair: allocates a 0x30 buffer,
 * sets count=2, and stores both elements. Validates the count.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_00002534 / FUN_0036a940 / FUN_002821c4 / FUN_002e1c9c; strings
 *   at 0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
long swift_array_from_pair(uint64_t a, uint64_t b)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x30, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 2;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    long got = FUN_002821c4(&sv_50, buf + 0x20, 2, a, b);
    if (sv_40 == 2) {
        if (got == 2) return buf;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    FUN_002e1c9c(sv_40, sv_50, us_48);
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a311c @ 0x001a311c   (est. swift_buffer_init_u32)
 * Ghidra: long FUN_001a311c(ulong param_1)
 * Initializes a Swift buffer holding one uint32 (masked 32-bit) element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_u32(uint64_t v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(uint64_t *)(buf + 0x20) = v & 0xffffffff;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a3188 @ 0x001a3188   (est. swift_buffer_init_u16)
 * Ghidra: long FUN_001a3188(ulong param_1)
 * Initializes a Swift buffer holding one uint16 (masked 16-bit) element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_u16(uint64_t v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(uint64_t *)(buf + 0x20) = v & 0xffff;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a31f4 @ 0x001a31f4   (est. swift_buffer_init_u8)
 * Ghidra: long FUN_001a31f4(ulong param_1)
 * Initializes a Swift buffer holding one uint8 (masked 8-bit) element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_u8(uint64_t v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(uint64_t *)(buf + 0x20) = v & 0xff;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a3260 @ 0x001a3260   (est. swift_buffer_init_int)
 * Ghidra: long FUN_001a3260(int param_1)
 * Initializes a Swift buffer holding one int (sign-extended) element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_int(int v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(long *)(buf + 0x20) = (long)v;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a32cc @ 0x001a32cc   (est. swift_buffer_init_int16)
 * Ghidra: long FUN_001a32cc(short param_1)
 * Initializes a Swift buffer holding one int16 element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_int16(short v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(long *)(buf + 0x20) = (long)v;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a3338 @ 0x001a3338   (est. swift_buffer_init_int8)
 * Ghidra: long FUN_001a3338(char param_1)
 * Initializes a Swift buffer holding one int8 element.
 * Confidence: medium
 * Notes: FUN_00002534 / FUN_0036a940 / thunk_FUN_000126e8.
 */
long swift_buffer_init_int8(char v)
{
    uint64_t meta = FUN_00002534(0x64e670, (void*)0x004c2600);
    long buf = (long)sk_alloc_special(meta, 0x28, 7);     /* FUN_0036a940 */
    long stride = thunk_FUN_000126e8();
    *(uint64_t *)(buf + 0x10) = 1;
    *(long *)(buf + 0x18) = (stride - 0x20) / 8 << 1;
    *(long *)(buf + 0x20) = (long)v;
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a33a4 @ 0x001a33a4   (est. swift_array_from_lzcount)
 * Ghidra: undefined * FUN_001a33a4(undefined8 param_1)
 * Builds a Swift Array whose capacity derives from the leading-zero count of
 * param_1; returns the shared empty singleton for count 4 (zero elements).
 * Validates the collection count on completion.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_0019c258 / FUN_00282bc0; strings at 0x005cdca0 / 0x005cdce0 /
 *   0x005cd960.
 */
void *swift_array_from_lzcount(uint64_t count)
{
    uint64_t lz = (uint64_t)sk_lzcount((int32_t)count) >> 3;
    if ((int32_t)lz == 4) return &sk_empty_array;       /* DAT_00657778 */
    long cls = 4 - lz;
    uint8_t *buf = (uint8_t *)FUN_0019c258(cls, 0, &sk_cstring, (void*)0x004be910);
    long got = FUN_00282bc0(&sv_34, buf + 0x20, cls, count);
    if (sv_34 == 0) {
        if (got == cls) return buf;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a34b4 @ 0x001a34b4   (est. swift_string_from_discriminated)
 * Ghidra: undefined * FUN_001a34b4(undefined8 param_1, ulong param_2)
 * Builds a Swift string from a discriminated representation: the count is
 * taken from bits 56-59 of param_2. Validates the count and bounds.
 * Confidence: high (string-matched fatal "Index out of bounds" +
 *   "invalid Collection...")
 * Notes: FUN_0019c258 / FUN_00282e84; strings at 0x005cdab0 / 0x005cdad0 /
 *   0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
void *swift_string_from_discriminated(uint64_t data, uint64_t disc)
{
    uint64_t n = disc >> 0x38 & 0xf;
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c258(n, 0, &sk_cstring, (void*)0x004be910);
    uint64_t got = FUN_00282e84(stack_buf, buf + 0x20, n, data, disc);
    if (sv_38 == ((uint64_t)sv_39 & 0xf)) {
        if (got == n) return buf;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    if (((uint64_t)sv_39 & 0xf) <= sv_38)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_index_oob, 0x13, 2,
                       s_swift_collection, 0x16, 2, 0x2ca, 1);
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a360c @ 0x001a360c   (est. swift_string_from_range)
 * Ghidra: undefined * FUN_001a360c(long param_1, long param_2)
 * Builds a Swift string from a pointer range [param_1, param_2): allocates
 * storage for param_2-param_1 bytes and copies them. Validates the count.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_0019c258 / FUN_003206bc / FUN_00321084; strings at 0x005cdca0 /
 *   0x005cdce0 / 0x005cd960.
 */
void *swift_string_from_range(long lo, long hi)
{
    if (lo != 0 && (hi - lo) != 0) {
        long n = hi - lo;
        uint8_t *buf = (uint8_t *)FUN_0019c258(n, 0, &sk_cstring, (void*)0x004be910);
        FUN_003206bc(buf + 0x20, n, lo, hi);
        uint16_t st = FUN_00321084();
        if (st < 0x100) {
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                           s_swift_contig_buf, 0x21, 2, 0x475, 1);
        }
        if (lo == n) return buf;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    return &sk_empty_array;                         /* DAT_00657778 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a3728 @ 0x001a3728   (est. swift_string_builder)
 * Ghidra: undefined * FUN_001a3728(...)
 * Swift string builder: computes the count via FUN_002b4120, allocates the
 * storage, and fills it. Validates the resulting count, handling the
 * more/less-than invalid-collection cases.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_002b4120 / FUN_0019c2fc / FUN_002830f4 / FUN_002b439c /
 *   FUN_002ab6a0 / FUN_002b3b84 / FUN_003a25d4 / thunk_FUN_0036b270;
 *   strings at 0x005cdbe0 / 0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
void *swift_string_builder(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    long n = FUN_002b4120(p1, p2, p1, p2, p3, p4);
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c2fc(n, 0, (void*)0x0064e890, (void*)0x004f1980);
    if (n >= 0) {
        thunk_FUN_0036b270(p4);                     /* alloc pages */
        long got = FUN_002830f4(&sv_68, buf + 0x20, n, p1, p2, p3, p4);
        if ((sv_48 ^ sv_60) < 0x4000) {
            if (got == n) {
                FUN_003a25d4(sv_50);
                return buf;
            }
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                           s_swift_contig_buf, 0x21, 2, 0x47a, 1);
        }
        FUN_002b439c(sv_48, sv_68, sv_60, sv_58, sv_50);
        uint64_t u = FUN_002ab6a0(sv_48, sv_68, sv_60, sv_58, sv_50);
        FUN_002b3b84(u, sv_68, sv_60, sv_58, sv_50);
        FUN_003a25d4(x1);
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x475, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                   s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a3918 @ 0x001a3918   (est. swift_string_from_utf16)
 * Ghidra: undefined * FUN_001a3918(...)
 * Swift string from UTF-16 code units: computes the count, allocates storage,
 * fills it, and validates bounds (String.index out of bounds / UTF16View).
 * Confidence: high (string-matched fatal "String index is out of bounds" +
 *   "invalid Collection...")
 * Notes: FUN_002afd38 / FUN_00071bd0 / FUN_00283290 / FUN_002b64cc /
 *   FUN_0001da84 / FUN_001676cc / FUN_002a9ba8; strings at 0x005ce6a0 /
 *   0x005d05f0 / 0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
void *swift_string_from_utf16(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    long n = FUN_002afd38();
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_00071bd0(n, 0);
    if (n >= 0) {
        thunk_FUN_0036b270(p4);                     /* alloc pages */
        long got = FUN_00283290(&sv_68, buf + 0x20, n, p1, p2, p3, p4);
        if ((sv_48 ^ sv_60) < 0x4000) {
            if (got == n) {
                FUN_003a25d4(sv_50);
                return buf;
            }
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                           s_swift_contig_buf, 0x21, 2, 0x47a, 1);
        }
        FUN_002b64cc(sv_48, sv_68, sv_60, sv_58, sv_50);
        uint32_t b = (uint32_t)(sv_58 >> 0x3b) & 1;
        if ((sv_50 & 0x1000000000000000) == 0) b = 1;
        if ((sv_48 & 0xc) == 4L << b) sv_48 = FUN_0001da84(sv_48, sv_58, sv_50);
        uint64_t cnt = sv_58 & 0xffffffffffff;
        if ((sv_50 & 0x2000000000000000) != 0) cnt = sv_50 >> 0x38 & 0xf;
        if (cnt <= sv_48 >> 0x10)
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_string_index_oob, 0x1d, 2,
                           s_swift_string_utf16, 0x1b, 2, 0x93, 1);
        if ((sv_50 >> 0x3c & 1) == 0) {
            b = (uint32_t)((long)sv_58 < 0);
            if ((sv_50 & 0x2000000000000000) != 0) b = (uint32_t)(sv_50 >> 0x3e) & 1;
            if (b == 0) {
                if ((sv_48 & 0xc001) == 0) FUN_001676cc(sv_48, sv_58, sv_50);
                if ((sv_50 & 0x2000000000000000) == 0 && (sv_58 & 0x1000000000000000) == 0)
                    FUN_002a9ba8(sv_58, sv_50);
            }
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x475, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                   s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a3b90 @ 0x001a3b90   (est. swift_string_from_utf8_units)
 * Ghidra: undefined * FUN_001a3b90(...)
 * Swift string from UTF-8 code units: computes the count, allocates storage,
 * fills it, and validates Unicode helper bounds.
 * Confidence: high (string-matched fatal "Swift UnicodeHelpers" +
 *   "invalid Collection...")
 * Notes: FUN_002a9d64 / FUN_0019c20c / FUN_002835c4 / FUN_002ab4d4 /
 *   FUN_002a9ba8 / FUN_00167404 / FUN_001afa84; strings at 0x005ce730 /
 *   0x005cdca0 / 0x005cdce0 / 0x005cd960.
 */
void *swift_string_from_utf8_units(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    long n = FUN_002a9d64();
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c20c(n, 0, (void*)0x006575f0, (void*)0x005a19e0);
    if (n >= 0) {
        thunk_FUN_0036b270(p4);                     /* alloc pages */
        long got = FUN_002835c4(&sv_68, buf + 0x20, n, p1, p2, p3, p4);
        if ((sv_48 ^ sv_60) < 0x4000) {
            if (got == n) {
                FUN_003a25d4(sv_50);
                return buf;
            }
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                           s_swift_contig_buf, 0x21, 2, 0x47a, 1);
        }
        FUN_002ab4d4(sv_48, sv_68, sv_60, sv_58, sv_50);
        if ((sv_50 >> 0x3c & 1) != 0)
            FUN_001afa84(s_Fatal_error, 0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                         s_swift_unicode_helpers, 0x1a, 2, 0xfd, 1);
        if (((sv_50 >> 0x3d & 1) == 0) && ((sv_58 >> 0x3c & 1) == 0)) {
            FUN_002a9ba8(sv_58, sv_50);
            FUN_00167404(sv_48, sv_58, sv_50);
            FUN_002a9ba8(sv_58, sv_50);
        } else {
            FUN_00167404(sv_48, sv_58, sv_50);
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x475, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                   s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a3dc4 @ 0x001a3dc4   (est. swift_buffer_init_single)
 * Ghidra: void FUN_001a3dc4(undefined8 param_1)
 * Initializes a Swift buffer holding a single element param_1.
 * Confidence: medium
 * Notes: FUN_0035a8fc / FUN_00359018 / FUN_0036a940 / FUN_00077630.
 */
void swift_buffer_init_single(uint64_t v)
{
    FUN_0035a8fc();
    FUN_00359018();
    sk_alloc_special(0, 0, 0);          /* FUN_0036a940 */
    FUN_00077630();
    *(uint64_t *)(x20 + 0x10) = 1;
    *(long *)(x20 + 0x18) = x8 / 8 << 1;
    *(uint64_t *)(x20 + 0x20) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_001a3e10 @ 0x001a3e10   (est. swift_string_builder_disc)
 * Ghidra: undefined * FUN_001a3e10(ulong param_1, ulong param_2)
 * Swift string builder from a discriminated count: derives the element count
 * from param_2 bits 56-59, computes a capacity flag, allocates the storage,
 * fills it, and validates the collection count.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_0029e8dc / FUN_0019c2fc / FUN_00283be4 / FUN_0029fb80 /
 *   FUN_003a25d4 / thunk_FUN_0036b270; strings at 0x005cdca0 / 0x005cdce0 /
 *   0x005cd960 / 0x005cdbe0.
 */
void *swift_string_builder_disc(uint64_t data, uint64_t disc)
{
    uint64_t n = data;
    if ((disc & 0x2000000000000000) != 0)
        n = disc >> 0x38 & 0xf;
    uint32_t b = (uint32_t)(data >> 0x3b) & 1;
    if ((disc & 0x1000000000000000) == 0) b = 1;
    uint64_t tag = (b == 0) ? 0xb : 7;
    long l = FUN_0029e8dc(0xf, tag | n << 0x10, data, disc);
    if (l == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c2fc(l, 0, (void*)0x0064e890, (void*)0x004f1980);
    if (l < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    thunk_FUN_0036b270(disc);                       /* alloc pages */
    long got = FUN_00283be4(stack, buf + 0x20, l, data, disc);
    FUN_0029fb80();
    if (x1 == 0) {
        if (got == l) {
            FUN_003a25d4(sv_48);
            return buf;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    FUN_003a25d4(x1);
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a3fbc @ 0x001a3fbc   (est. swift_string_builder_disc2)
 * Ghidra: undefined * FUN_001a3fbc(ulong param_1, ulong param_2)
 * Swift string builder variant: selects between ASCII and non-ASCII paths via
 * the discriminator, allocates storage, fills it, and validates the count.
 * Confidence: high (string-matched fatal "invalid Collection...")
 * Notes: FUN_002af74c / FUN_0029b9a8 / FUN_00071bd0 / FUN_00283d14 /
 *   FUN_002b0c84 / FUN_003a25d4 / thunk_FUN_0036b270; strings at 0x005cdca0 /
 *   0x005cdce0 / 0x005cd960 / 0x005cdbe0.
 */
void *swift_string_builder_disc2(uint64_t data, uint64_t disc)
{
    long l;
    if ((disc >> 0x3c & 1) == 0) {
        uint64_t n = data;
        if ((disc & 0x2000000000000000) != 0) n = disc >> 0x38 & 0xf;
        l = FUN_002af74c(n << 0x10 | 7, data, disc);
    } else {
        l = FUN_0029b9a8(data, disc);
    }
    if (l == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_00071bd0(l, 0);
    if (l < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    thunk_FUN_0036b270(disc);                       /* alloc pages */
    long got = FUN_00283d14(stack, buf + 0x20, l, data, disc);
    uint32_t u = FUN_002b0c84();
    if ((u & 0xff0000) == 0x10000) {
        if (got == l) {
            FUN_003a25d4(sv_50);
            return buf;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                   s_swift_contig_buf, 0x21, 2, 0x475, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a4154 @ 0x001a4154   (est. swift_string_append_builder)
 * Ghidra: undefined * FUN_001a4154(...)
 * Swift string append builder: computes the combined count, allocates
 * storage, appends both parts, and validates Unicode/collection invariants.
 * Confidence: high (string-matched fatal "Swift UnicodeHelpers" +
 *   "invalid Collection...")
 * Notes: FUN_001ee030 / FUN_0019c20c / FUN_00283e7c / FUN_002a9ba8 /
 *   FUN_001afa84 / thunk_FUN_0036b270; strings at 0x005ce730 / 0x005cdca0 /
 *   0x005cdce0 / 0x005cd960.
 */
void *swift_string_append_builder(uint64_t p1, uint64_t p2)
{
    long n = FUN_001ee030(p1, p2, FUN_002a9d64);
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c20c(n, 0, (void*)0x006575f0, (void*)0x005a19e0);
    if (n >= 0) {
        thunk_FUN_0036b270(p2);                     /* alloc pages */
        long got = FUN_00283e7c(&sv_50, buf + 0x20, n, p1, p2);
        if (sv_40 < ls_38) {
            if ((sv_48 >> 0x3c & 1) != 0)
                FUN_001afa84(s_Fatal_error, 0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                             s_swift_unicode_helpers, 0x1a, 2, 0xfd, 1);
            if ((sv_48 & 0x2000000000000000) == 0 && (sv_50 & 0x1000000000000000) == 0)
                FUN_002a9ba8();
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_more_than, 0x3c, 2,
                           s_swift_contig_buf, 0x21, 2, 0x475, 1);
        }
        if (got == n) {
            FUN_003a25d4(sv_48);
            return buf;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_invalid_less_than, 0x3c, 2,
                       s_swift_contig_buf, 0x21, 2, 0x47a, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                   s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a433c @ 0x001a433c   (est. swift_array_from_raw)
 * Ghidra: undefined * FUN_001a433c(undefined8 param_1, long param_2)
 * Builds a Swift Array from a raw pointer + count: allocates storage for
 * count elements and copies them in (FUN_0019d40c). Empty count returns the
 * shared singleton.
 * Confidence: high (string-matched fatal "UnsafeMutableBufferPointer...")
 * Notes: FUN_0019c258 / FUN_0019d40c; strings at 0x005cdbe0 / 0x005cdc10.
 */
void *swift_array_from_raw(uint64_t src, long count)
{
    if (count == 0) return &sk_empty_array;         /* DAT_00657778 */
    uint8_t *buf = (uint8_t *)FUN_0019c258(count, 0, (void*)0x0064e888, (void*)0x004c06e0);
    if (count < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafe_mut_buf, 0x2e, 2,
                       s_swift_unsafe_buf, 0x1f, 2, 0x4a, 1);
    FUN_0019d40c(src, count, buf + 0x20);           /* copy */
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a4400 @ 0x001a4400   (est. swift_array_dedupe)
 * Ghidra: long FUN_001a4400(long param_1)
 * Deduplicates / compacts a Swift Array: iterates the source bitmask index,
 * copying unique elements into a fresh buffer. Fatals on invalid collection.
 * Confidence: medium
 * Notes: FUN_000776cc / FUN_003556e0 / FUN_0019c2fc / FUN_0035063c /
 *   FUN_00284148 / thunk_FUN_0036b270 / FUN_0036b118; trap at 0x1a44d0.
 */
long swift_array_dedupe(long src)
{
    long n = *(long *)(src + 0x10);
    if (n == 0) {
        FUN_000776cc();
        return x20;
    }
    FUN_003556e0();
    long dst = FUN_0019c2fc(n, 0);
    FUN_0035063c(&sv_58, dst + 0x20);
    long m = FUN_00284148();
    if (sv_38 == 0) {
        do {
            long i = ls_40 + 1;
            if (SCARRY8(ls_40, 1)) __builtin_trap();    /* 0x1a44d0 */
            if ((long)(sv_48 + 0x40 >> 6) <= i) {
                if (m == n) {
                    thunk_FUN_0036b270(src);        /* alloc pages */
                    FUN_0036b118(sv_58);         /* free */
                    return dst;
                }
                FUN_003488bc(1);
                goto dedupe_fatal;
            }
            ls_40 = i;
        } while (*(long *)(ls_50 + i * 8) == 0);
    }
    FUN_003488bc(1);
dedupe_fatal:
    FUN_00349ee0();
    FUN_00351a8c();
    sk_swift_fatal(0, 0, 0);                               /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a44f4 @ 0x001a44f4   (est. swift_array_copy)
 * Ghidra: undefined * FUN_001a44f4(long param_1)
 * Copies a Swift Array: allocates a new buffer and copies the elements.
 * Confidence: medium
 * Notes: FUN_003556e0 / FUN_00351244 / FUN_0019c2fc / FUN_0019d15c.
 */
void *swift_array_copy(long src)
{
    long n = *(long *)(src + 0x10);
    if (n == 0) return &sk_empty_array;             /* DAT_00657778 */
    FUN_003556e0();
    FUN_00351244();
    uint8_t *buf = (uint8_t *)FUN_0019c2fc();
    FUN_0019d15c(src + 0x20, n, buf + 0x20);        /* copy */
    return buf;
}

/*--------------------------------------------------------------------*/
/* FUN_001a4554 @ 0x001a4554   (est. sk_sched_queue_rebuild)
 * Ghidra: void FUN_001a4554(...)
 * Rebuilds the run queue from a source collection: allocates fresh storage,
 * copies the elements, and re-arms the queue accounting. Validates the copy
 * count and fatals on mismatch.
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_001a26e0,
 *   FUN_0019c44c, FUN_00377bec; fatal on mismatch; FUN_0008e500 epilogue.
 */
void sk_sched_queue_rebuild(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    uint64_t t = p3;
    FUN_003518c4();
    FUN_00351bec(t);
    FUN_003520f8();
    FUN_0034c280(0xff);
    FUN_00377824();                         /* lock */
    FUN_00352efc();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350428();
    FUN_00349080();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348f38();
    FUN_0034c280(0);
    FUN_00377824();                         /* lock */
    FUN_00348cd0();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034bdfc();
    FUN_00353efc(p3);
    FUN_0008e388();
    long n = x8_00_fn();                    /* indirect */
    if (n == 0) {
        long v = FUN_0006f6b4();
        goto rebuild_done;
    }
    FUN_0019c44c(n, 0, x1);
    FUN_00356030();
    long base = FUN_00357c20(*(uint8_t *)(x16_00 + 0x50));
    FUN_001a26e0(base + x8_01, n);
    FUN_00351a5c();
    FUN_00351360(*(uint64_t *)(x16 + 0x10));
    x8_02_fn();
    FUN_003191e8();
    reg16 v = FUN_0035012c();
    FUN_003513cc(v.lo, v.hi, n);
    long got = x8_03_fn();
    FUN_0034b278();
    FUN_003504f4();
    FUN_00377bec();
    FUN_00354474();
    FUN_00351918();
    FUN_003508a8();
    x9_fn();
    v = FUN_003517a8();
    FUN_000839f8(v.lo, v.hi, x1);
    FUN_0034eea8();
    FUN_00353f38();
    x8_04_fn();
    if (w19 == 1) {
        if (got == n) {
            FUN_003529a4();
            FUN_003510ac();
            x8_05_fn();
            goto rebuild_done;
        }
        FUN_00350410();
        FUN_003488bc();
    } else {
        FUN_00348b7c(0x475);
    }
    FUN_00349ee0();
    FUN_00351a8c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
rebuild_done:
    sk_thread_epilogue(v, x30);             /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a480c @ 0x001a480c   (est. sk_collection_init_out)
 * Ghidra: void FUN_001a480c(...)
 * Initializes a collection through the shared reserve helper (FUN_001a03fc)
 * and stores the result into *param_1.
 * Confidence: medium
 * Notes: FUN_001a03fc.
 */
void sk_collection_init_out(uint64_t *out, uint64_t a, uint64_t b, long p4)
{
    uint64_t v = swift_collection_reserve_r(a, b, *(uint64_t *)(p4 + 0x10)); /* FUN_001a03fc */
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_001a4838 @ 0x001a4838   (est. swift_array_init_out)
 * Ghidra: void FUN_001a4838(...)
 * Initializes a Swift Array through FUN_0019e578 and stores the result.
 * Confidence: medium
 * Notes: FUN_0019e578.
 */
void swift_array_init_out(uint64_t *out, uint64_t a, uint64_t b, uint64_t p4)
{
    uint64_t v = FUN_0019e578(a, b, b, p4);
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_001a488c @ 0x001a488c   (est. sk_sched_queue_notify_rearm)
 * Ghidra: void FUN_001a488c(...)
 * Rearms the run-queue notification/accounting state after an insert: runs
 * the lock sequence, dispatches through the saved handler slots, and updates
 * the queue slot. Fatals on inconsistent state.
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec,
 *   FUN_00310e08/0e20/0a40/0a88; fatal FUN_001afe4c.
 */
void sk_sched_queue_notify_rearm(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                                 uint64_t p5, uint64_t p6)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    FUN_0035125c(p5);
    FUN_0034a3c4();
    FUN_0034ef58();
    uint64_t lock = FUN_00377824();         /* lock */
    FUN_0034b0b4();
    FUN_003579d8();
    FUN_00348d7c();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003492ac();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350464();
    uint64_t u3 = FUN_003554d4();
    FUN_0035053c(u3, p3);
    uint64_t u3b = FUN_00377bec();
    reg16 v = FUN_00350798();
    long idx = FUN_00310e08(v.lo, v.hi, u3b);
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034cff4();
    FUN_00310e20(u3b);
    u3b = FUN_00350a40();
    FUN_00351378(u3b, cpu.hi);
    uint64_t ok = x8_01_fn();
    if ((ok & 1) != 0) {
        FUN_00349b00();
        fn6 = *(code_fn **)(x8_02 + 0x10);
        fn6(x8_00, cpu.hi, lock);
        FUN_00353214(x8_00 + *(int *)(x25 + 0x30));
        fn6();
        FUN_00352474();
        FUN_003509d4();
        x9_fn();
        int off = *(int *)(x25 + 0x30);
        fn7 = *(code_fn **)(x16_00 + 0x20);
        v = FUN_003514d0();
        fn7(v.lo, v.hi, lock);
        fn6b = *(code_fn **)(x16_00 + 8);
        fn6b(sv_38 + off, lock);
        FUN_003509d4(*(uint64_t *)(x16 + 0x20));
        x8_03_fn();
        fn7(x21 + *(int *)(idx + 0x24), sv_38 + *(int *)(x25 + 0x30), lock);
        FUN_00351e90();
        fn6b();
        FUN_00354d08();
        FUN_00319248();
        uint64_t u = FUN_00350a88();
        x8_04_fn(u, cpu.lo, p4, p6, p3, fn6b);
        FUN_00353154();
        FUN_003504ac();
        x8_05_fn();
        sk_thread_epilogue();               /* FUN_0008e500 */
        return;
    }
    FUN_00347d60();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a4b34 @ 0x001a4b34   (est. swift_string_remove_ascii_thunk)
 * Ghidra: void FUN_001a4b34(undefined8 param_1, undefined8 param_2)
 * Thunk: removes a range from a Swift string via FUN_002ab8ac with the
 * ASCII-character size tags (0x174/0x164) then re-validates.
 * Confidence: medium
 * Notes: FUN_002ab8ac / FUN_002a7c00; *unaff_x20/[1] = string discriminator.
 */
void swift_string_remove_ascii_a(uint64_t a, uint64_t b)
{
    FUN_002ab8ac(a, b, *x20, x20[1], 0x174, 0x164);
    FUN_002a7c00();
}

/*--------------------------------------------------------------------*/
/* FUN_001a4b38 @ 0x001a4b38   (est. swift_string_remove_ascii_thunk)
 * Ghidra: void FUN_001a4b38(undefined8 param_1, undefined8 param_2)
 * Thunk: alias of FUN_001a4b34; same range-remove with ASCII tags.
 * Confidence: medium
 * Notes: FUN_002ab8ac / FUN_002a7c00.
 */
void swift_string_remove_ascii_b(uint64_t a, uint64_t b)
{
    FUN_002ab8ac(a, b, *x20, x20[1], 0x174, 0x164);
    FUN_002a7c00();
}

/*--------------------------------------------------------------------*/
/* FUN_001a4b5c @ 0x001a4b5c   (est. swift_string_remove_utf8)
 * Ghidra: void FUN_001a4b5c(undefined8 param_1, undefined8 param_2)
 * Removes a range from a UTF-8 Swift string via FUN_002ab5bc with the full
 * 4-word string representation, then re-validates.
 * Confidence: medium
 * Notes: FUN_002ab5bc / FUN_003511cc / FUN_002a95b4.
 */
void swift_string_remove_utf8(uint64_t a, uint64_t b)
{
    FUN_002ab5bc(a, b, x20[0], x20[1], x20[2], x20[3]);
    FUN_003511cc();
    FUN_002a95b4();
}

/*--------------------------------------------------------------------*/
/* FUN_001a4bbc @ 0x001a4bbc   (est. swift_utf8_buffer_index)
 * Ghidra: void FUN_001a4bbc(ulong param_1)
 * Computes the byte index of a code unit in a Swift ValidUTF8Buffer by
 * decoding the value byte-by-byte into a bitmask. Fatals on index-out-of-
 * bounds or invalid UTF-8.
 * Confidence: high (string-matched fatal "Index out of bounds" +
 *   "Swift ValidUTF8Buffer")
 * Notes: FUN_002c8c2c / FUN_001d96e0 / FUN_001d974c; strings at 0x005cdab0 /
 *   0x005cdad0 / 0x005be7c0 / 0x005d08c0.
 */
void swift_utf8_buffer_index(uint64_t idx)
{
    uint32_t acc = *x20;
    uint64_t ok = FUN_002c8c2c(idx, acc);
    if ((ok & 1) == 0) goto fatal_c1;
    ok = FUN_002c8c2c(idx >> 0x20, acc);
    if ((ok & 1) != 0) {
        uint64_t r = FUN_001d96e0(idx, acc);
        uint32_t lo = (uint32_t)r;
        uint32_t hi = (uint32_t)(r >> 0x20);
        uint32_t mask = 0;
        if (lo != hi) {
            do {
                uint32_t cur = (uint32_t)r;
                if (lo < cur || cur <= hi) goto oob;      /* LAB_001a4cd4 */
                if ((mask & 0xff000000) != 0) goto fatal_a7;
                r = (uint64_t)(cur >> 8);
                mask = (cur & 0xff) << (uint32_t)(-((uint32_t)sk_lzcount(mask) & 0x18) & 0x18) | mask;
            } while (cur >> 8 != hi);
        }
        r = FUN_001d974c(idx >> 0x20, acc);
        lo = (uint32_t)r;
        hi = (uint32_t)(r >> 0x20);
        acc = lo;
        for (;;) {
            if (acc == hi) {
                *x20 = mask;
                return;
            }
            uint32_t cur = (uint32_t)r;
            if (lo < cur || cur <= hi) goto oob;
            if ((mask & 0xff000000) != 0) goto fatal_a7;
            acc = cur >> 8;
            r = (uint64_t)acc;
            mask = (cur & 0xff) << (uint32_t)(-((uint32_t)sk_lzcount(mask) & 0x18) & 0x18) | mask;
        }
    }
fatal_c1:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, (void*)0x005be7c0, 0, 2,
                   s_swift_valid_utf8, 0x1b, 2, 0xc1, 1);
oob:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_index_oob, 0x13, 2,
                   s_swift_collection, 0x16, 2, 0x2ca, 1);
fatal_a7:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, (void*)0x005be7c0, 0, 2,
                   s_swift_valid_utf8, 0x1b, 2, 0xa7, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a4d84 @ 0x001a4d84   (est. sk_sched_lock_release_full)
 * Ghidra: void FUN_001a4d84(void)
 * Full scheduler lock release: saves flags, runs the lock/refcount sequence,
 * and restores flags before jumping through an unrecoverable jumptable.
 * Confidence: low (jumptable at 0x001a4e04 not recoverable)
 * Notes: FUN_00357cb4 / FUN_0034a958 / FUN_00027754 / FUN_00348b94 /
 *   FUN_00377824 / FUN_00319248 / FUN_00350500 / FUN_00319230 /
 *   FUN_00348d18 / FUN_00376820 / FUN_003562bc / FUN_00357c74.
 */
void sk_sched_lock_release_full(void)
{
    sk_spin_irqsave(&flags);                /* FUN_00357cb4 */
    FUN_0034a958();
    FUN_00027754();
    FUN_00348b94();
    FUN_00377824();                         /* lock */
    uint64_t u1 = FUN_00319248();
    FUN_00350500();
    uint64_t u2 = FUN_00319230();
    uint64_t u3 = FUN_00348d18();
    sk_metatype(u3, u2);                    /* FUN_00376820 */
    uint64_t u2b = FUN_003562bc();
    sk_irqrestore(u2b, u1);                 /* FUN_00357c74 */
    jumptable();                            /* 0x001a4e04 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a4e10 @ 0x001a4e10   (est. swift_collection_remove_first)
 * Ghidra: undefined1 [16] FUN_001a4e10(void)
 * Removes the first element of a Swift collection; fatals on empty collection
 * or unexpected nil while unwrapping.
 * Confidence: high (string-matched fatal "Can't remove first element from a"
 *   + "Unexpectedly found nil while unw")
 * Notes: FUN_001aea6c / FUN_001a5250; strings at 0x005cdd50 / 0x005cd7d0 /
 *   0x005cdd20.
 */
reg16 swift_collection_remove_first(void)
{
    uint64_t n = *x20 & 0xffffffffffff;
    if ((x20[1] & 0x2000000000000000) != 0) n = x20[1] >> 0x38 & 0xf;
    if (n == 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_first, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x26c, 1);
    reg16 r = FUN_001aea6c();
    if (r.hi != 0) {
        FUN_001a5250(1);
        return r;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unexpected_nil, 0x39, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x26e, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a4efc @ 0x001a4efc   (est. swift_collection_pop_first)
 * Ghidra: ulong FUN_001a4efc(void)
 * Pops the first element of a Swift collection (optional); fatals on empty
 * or unexpected nil while unwrapping.
 * Confidence: high (string-matched fatal as FUN_001a4e10)
 * Notes: FUN_0016749c / FUN_001a5110; strings at 0x005cdd50 / 0x005cd7d0 /
 *   0x005cdd20.
 */
uint64_t swift_collection_pop_first(void)
{
    uint64_t n = *x20 & 0xffffffffffff;
    if ((x20[1] & 0x2000000000000000) != 0) n = x20[1] >> 0x38 & 0xf;
    if (n == 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_first, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x26c, 1);
    uint64_t v = FUN_0016749c();
    if ((v & 0xff00000000) != 0x100000000) {
        FUN_001a5110(1);
        return v;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unexpected_nil, 0x39, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x26e, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a4fe4 @ 0x001a4fe4   (est. swift_collection_remove_first_dispatch)
 * Ghidra: void FUN_001a4fe4(void)
 * Dispatch wrapper for remove-first: saves the CPU context, runs the lock
 * sequence, and dispatches through the saved handler. Fatals on unexpected
 * nil.
 * Confidence: low (indirect dispatch, in_ZR condition)
 * Notes: FUN_00084220 / FUN_00377824 / DAT_00658c00 / FUN_00084234;
 *   fatal FUN_001afe4c.
 */
void swift_collection_remove_first_dispatch(void)
{
    FUN_00084220();
    FUN_0034bd6c();
    FUN_00352894();
    FUN_00348f14();
    FUN_003560f8();
    FUN_00377824();                         /* lock */
    FUN_0034f624();
    FUN_0034d464();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b05c();
    FUN_003192a8();
    FUN_0034e64c();
    uint64_t ok = x8_fn();
    if ((ok & 1) == 0) {
        FUN_00350c2c();
        FUN_001aeab4();
        FUN_0034b2a8();
        if (!ZR) {
            FUN_0034c664();
            (**(code_fn **)(x16 + 0x20))();
            uint64_t u = FUN_00319278();
            FUN_003504a0(u, 1);
            x8_00_fn();
            FUN_00084234(x30);
            return;
        }
        FUN_003489dc(0x26e);
        FUN_0034a69c();
    } else {
        FUN_00350410();
        FUN_003488bc();
        FUN_0034a69c();
    }
    FUN_00353f14();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a5110 @ 0x001a5110   (est. swift_collection_remove_prefix)
 * Ghidra: void FUN_001a5110(long param_1)
 * Removes the first `param_1` elements of a Swift RangeReplaceableCollection;
 * validates the count and the remaining-element invariant. Fatals on negative
 * count or removing more items than present.
 * Confidence: high (string-matched fatal "Number of elements to remove sho" +
 *   "Can't remove more items from a c")
 * Notes: FUN_002ae2c0 / FUN_002ab8ac / FUN_002a7c00; strings at 0x005cddd0 /
 *   0x005cdd90 / 0x005cdd20.
 */
void swift_collection_remove_prefix(long count)
{
    if (count == 0) return;
    if (count < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_num_to_remove, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x252, 1);
    uint64_t v3 = *x20;
    uint64_t v4 = x20[1];
    uint64_t n = v3;
    if ((v4 & 0x2000000000000000) != 0) n = v4 >> 0x38 & 0xf;
    uint32_t b = (uint32_t)(v3 >> 0x3b) & 1;
    if ((v4 & 0x1000000000000000) == 0) b = 1;
    uint64_t tag = (b == 0) ? 0xb : 7;
    reg12 r = FUN_002ae2c0(0xf, count, tag | n << 0x10, v3, v4);
    if ((r.hi & 0xff) != 1) {
        FUN_002ab8ac(0xf, r.lo, v3, v4, 0x174, 0x164);
        FUN_002a7c00();
        return;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more, 0x35, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x254, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5250 @ 0x001a5250   (est. swift_collection_remove_prefix2)
 * Ghidra: void FUN_001a5250(long param_1)
 * Remove-prefix variant using FUN_0029f368 and the smaller element tags
 * (0xd2/0x50).
 * Confidence: high (string-matched fatal as FUN_001a5110)
 * Notes: FUN_0029f368 / FUN_002ab8ac / FUN_002a5400; strings at 0x005cddd0 /
 *   0x005cdd90 / 0x005cdd20.
 */
void swift_collection_remove_prefix2(long count)
{
    if (count == 0) return;
    if (count < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_num_to_remove, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x252, 1);
    uint64_t v3 = *x20;
    uint64_t v4 = x20[1];
    uint64_t n = v3;
    if ((v4 & 0x2000000000000000) != 0) n = v4 >> 0x38 & 0xf;
    uint32_t b = (uint32_t)(v3 >> 0x3b) & 1;
    if ((v4 & 0x1000000000000000) == 0) b = 1;
    uint64_t tag = (b == 0) ? 0xb : 7;
    reg12 r = FUN_0029f368(0xf, count, tag | n << 0x10, v3, v4);
    if ((r.hi & 0xff) != 1) {
        FUN_002ab8ac(0xf, r.lo, v3, v4, 0xd2, 0x50);
        FUN_002a5400();
        return;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more, 0x35, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x254, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5390 @ 0x001a5390   (est. swift_collection_remove_range)
 * Ghidra: void FUN_001a5390(long param_1)
 * Removes a range of elements from a Swift RangeReplaceableCollection;
 * validates the range bounds and the remaining-element invariant. Fatals on
 * invalid range ordering or removing more items than present.
 * Confidence: high (string-matched fatal "Range requires lowerBound <= upp" +
 *   "Can't remove more items from a c")
 * Notes: FUN_001e3730 / FUN_001a4bbc; strings at 0x005cda00 / 0x005cda30 /
 *   0x005cdd90 / 0x005cdd20.
 */
void swift_collection_remove_range(long count)
{
    if (count == 0) return;
    if (count < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_num_to_remove, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x252, 1);
    uint32_t lo = *x20;
    uint64_t v5 = (uint64_t)lo;
    uint64_t r = FUN_001e3730(v5, count, 0, v5);
    if ((r & 0xff00000000) != 0x100000000) {
        if ((uint32_t)r <= lo) {
            FUN_001a4bbc(v5 | r << 0x20);
            return;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more, 0x35, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x254, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a54d4 @ 0x001a54d4   (est. sk_sched_queue_insert_dispatch)
 * Ghidra: void FUN_001a54d4(...)
 * Inserts a batch into the run queue under the full lock sequence: computes
 * the count, grows the queue, dispatches through the saved handler slots, and
 * re-arms the queue accounting. Fatals on inconsistent state.
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec; fatal
 *   FUN_001afe4c; traps none; FUN_0008e500 epilogue.
 */
void sk_sched_queue_insert_dispatch(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_00350980();
    FUN_00351ef8(p3);
    FUN_0034a3c4();
    FUN_000dbf08();
    FUN_00377824();                         /* lock */
    long base = FUN_0034a654();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348a9c();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034ac50();
    FUN_0034ef58();
    FUN_00377bec();
    FUN_0034d734();
    FUN_00310e08();
    long idx = FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034eb2c();
    FUN_00350500();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034af20();
    FUN_0034998c();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40));/* DAT_00658c00 */
    FUN_003493c4();
    FUN_0034d698();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034baa8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aea8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    uint64_t u4 = FUN_0034c2c8();
    if (x13 == 0) {
        goto insert_epilogue;
    }
    if (x13 < 0) {
        FUN_00350410();
        FUN_003488bc();
        FUN_00358918();
        FUN_0034a69c();
    } else {
        FUN_000277b8();
        FUN_00350b30();
        FUN_00350a04();
        x9_fn();
        FUN_00310924();
        FUN_00351250();
        FUN_00350a04();
        x9_00_fn();
        FUN_003192d8();
        FUN_00351184();
        FUN_003502b8();
        x9_01_fn();
        fn7 = *(code_fn **)(x16_00 + 8);
        FUN_000e15d8();
        fn7();
        FUN_00351274();
        fn7();
        uint64_t u5 = FUN_0034b2a8();
        if (!ZR) {
            fn8 = *(code_fn **)(x16_00 + 0x20);
            FUN_00351324();
            fn8();
            FUN_00350a04(sv_18);
            x9_fn();
            FUN_0035166c(p3);
            FUN_003508cc();
            FUN_003516b4();
            uint64_t ok = x8_01_fn();
            if ((ok & 1) != 0) {
                FUN_003511c0(sv_48);
                fn8();
                FUN_00350810(sv_48 + *(int *)(base + 0x30));
                fn8();
                FUN_00351d0c();
                reg16 v = FUN_003510dc();
                x9_02_fn(v.lo, v.hi, base);
                int off = *(int *)(base + 0x30);
                FUN_00350ad0(sv_50);
                fn8();
                fn7(us_28 + off);
                v = FUN_003510dc(*(uint64_t *)(x16 + 0x20));
                x8_02_fn(v.lo, v.hi, base);
                fn8(sv_50 + *(int *)(idx + 0x24), us_28 + *(int *)(base + 0x30));
                FUN_00351274();
                fn7();
                FUN_0031d488(x21);
                u4 = FUN_00350648();
                x8_03_fn(u4, x22, x21);
                FUN_00354364();
                FUN_00350a04();
                x8_04_fn();
                goto insert_epilogue;
            }
            FUN_00347d60();
            goto insert_fatal;
        }
        FUN_00351e6c(u5, u4);
        x8_05_fn();
        FUN_00348b7c(0x254);
        FUN_0034a69c();
    }
    FUN_00353f14();
insert_fatal:
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
insert_epilogue:
    sk_thread_epilogue(x30);                /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a58f0 @ 0x001a58f0   (est. sk_obj_metatype_dispatch)
 * Ghidra: void FUN_001a58f0(...)
 * Resolves the metatype for param_3 (DAT_004e8230) then dispatches the
 * constructor FUN_001a5968 with the resolved type.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_001a5968.
 */
void sk_obj_metatype_dispatch(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e8230, p3);   /* FUN_00376820 */
    FUN_001a5968(p1, p2, p3, meta, p4);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5968 @ 0x001a5968   (est. sk_sched_queue_construct)
 * Ghidra: void FUN_001a5968(void)
 * Constructs a run-queue object under the full lock sequence: acquires locks,
 * allocates the backing storage, and runs the constructor pipeline. Fatals on
 * inconsistent state.
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_00353cfc / FUN_00027754 / FUN_00377824 / FUN_00377bec /
 *   DAT_00658c00 / FUN_001d9b18; fatal FUN_001afe4c.
 */
void sk_sched_queue_construct(void)
{
    uint64_t u1 = FUN_00353cfc();
    FUN_00352c10();
    uint64_t u2 = FUN_00027754(x3);
    FUN_003521d4();
    FUN_003505c4(0xff);
    uint64_t lock = FUN_00377824();         /* lock */
    FUN_0034d868();
    uint64_t u4 = FUN_00377bec();
    FUN_0034d8f4();
    FUN_00319308();
    FUN_00348d7c();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034af20();
    FUN_003499c8();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b460();
    FUN_00350810(u2, u1);
    FUN_001d9b18();
    if (x21 == 0) {
        FUN_00351ad4(u4);
        FUN_0014ae44();
        u1 = FUN_000dbdf4();
        FUN_003512cc(u1, u2);
        uint64_t ok = x8_fn();
        if ((ok & 1) == 0) {
            FUN_00350410();
            FUN_003488bc();
            FUN_003593e8();
            FUN_00349410();
            FUN_003504b8();
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        reg16 v = FUN_00350b00(*(uint64_t *)(x16 + 0x20));
        x8_00_fn(v.lo, v.hi, lock);
        FUN_003489a8();
        FUN_0035136c();
        FUN_00273fe0();
        FUN_00351e54();
        FUN_00350b3c();
        x8_01_fn();
    }
    FUN_00359b64();
    FUN_00353d14(is_38);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5b28 @ 0x001a5b28   (est. sk_sched_queue_create)
 * Ghidra: undefined8 FUN_001a5b28(void)
 * Creates a run queue: prepares the descriptor, allocates the backing
 * storage, and inserts it via FUN_001a2128. Returns the new queue handle.
 * Confidence: medium
 * Notes: FUN_003504d0 / FUN_00350a64 / FUN_00310d34 / FUN_00356328 /
 *   FUN_0036b270 / FUN_0034921c / FUN_001a2128.
 */
uint64_t sk_sched_queue_create(void)
{
    reg16 v = FUN_003504d0();
    uint64_t hi = v.hi;
    uint64_t lo = v.lo;
    FUN_00350a64();
    FUN_00310d34();
    FUN_00356328();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_0034921c();
    FUN_001a2128(&hi);
    return lo;
}

/*--------------------------------------------------------------------*/
/* FUN_001a5b90 @ 0x001a5b90   (est. sk_sched_queue_create2)
 * Ghidra: void FUN_001a5b90(void)
 * Create-queue variant: prepares the descriptor, allocates storage, and
 * inserts via FUN_001a2128.
 * Confidence: medium
 * Notes: FUN_003504d0 / FUN_00350a64 / FUN_00310d34 / FUN_00354924 /
 *   FUN_0036b270 / FUN_0034921c / FUN_001a2128.
 */
void sk_sched_queue_create2(void)
{
    FUN_003504d0();
    uint64_t lo = x1;
    FUN_00350a64();
    FUN_00310d34();
    FUN_00354924();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_0034921c();
    FUN_001a2128(&lo);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5be8 @ 0x001a5be8   (est. swift_collection_apply_thunk)
 * Ghidra: void FUN_001a5be8(undefined8 param_1, undefined8 param_2)
 * Thunk: applies FUN_00310d34 as a callback over the collection with the
 * metatype DAT_004e8268.
 * Confidence: medium
 * Notes: FUN_001dea60(param_1, param_2, FUN_00310d34, (void*)0x004e8268).
 */
void swift_collection_apply_meta(uint64_t a, uint64_t b)
{
    FUN_001dea60(a, b, FUN_00310d34, (void*)0x004e8268);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5c14 @ 0x001a5c14   (est. sk_sched_queue_ctx_init)
 * Ghidra: void FUN_001a5c14(...)
 * Initializes a run-queue context object: resolves the type descriptors,
 * allocates the backing storage, runs the setup pipeline, and stores the
 * initialized state into the output array.
 * Confidence: medium
 * Notes: FUN_002db6b8 / FUN_00319350 / FUN_00002534 / FUN_0036a940 /
 *   FUN_0020c5b0 / FUN_00365b6c / FUN_000026e8; tags 0x6740f8.
 */
void sk_sched_queue_ctx_init(uint64_t *out, uint32_t p2, uint8_t p3, uint64_t p4, uint64_t p5)
{
    sv_54 = p2;
    reg16 v = FUN_002db6b8(&sv_54, p4, p5, 0x6740f8);
    FUN_00319350(p4, p5);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_58 = p2;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_58, 0x6740f8, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x6740f8;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p3;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5d34 @ 0x001a5d34   (est. sk_sched_queue_ctx_alloc)
 * Ghidra: void FUN_001a5d34(void)
 * Allocates a run-queue context: prepares the descriptor, allocates the
 * backing storage, and runs the setup pipeline.
 * Confidence: low (inlined allocator, unaff regs)
 * Notes: FUN_000b4594 / FUN_00353178 / FUN_002db6b8 / FUN_0034dd14 /
 *   FUN_00002850 / FUN_0036a940 / FUN_00352444 / FUN_00359418 /
 *   FUN_0034f9b4 / FUN_003582b8 / FUN_00356ff4 / FUN_003588b8 /
 *   FUN_00359b3c / FUN_000b45b0.
 */
void sk_sched_queue_ctx_alloc(void)
{
    reg16 v = FUN_000b4594();
    is_40 = v;
    FUN_00353178(&stack_40);
    FUN_002db6b8();
    FUN_0034dd14();
    FUN_00002850();
    sk_alloc_special(0, 0, 0);              /* FUN_0036a940 */
    FUN_00352444();
    FUN_00359418();
    is_30 = v;
    FUN_0034f9b4();
    FUN_003582b8();
    int ok = FUN_00356ff4();
    if (ok != 0) FUN_003588b8(&stack_8);
    FUN_00359b3c();
    FUN_000b45b0(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5dd4 @ 0x001a5dd4   (est. sk_sched_queue_ctx_alloc2)
 * Ghidra: void FUN_001a5dd4(void)
 * Alloc-queue-context variant using FUN_0034f99c as the descriptor source.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_0035300c / FUN_0034f99c / FUN_0034df94 / FUN_002db6b8 /
 *   FUN_0034dd14 / FUN_00002850 / FUN_0036a940 / FUN_00352444 /
 *   FUN_00359418 / FUN_0034f9b4 / FUN_003582b8 / FUN_00357bf8 /
 *   FUN_003588b8 / FUN_003526d8 / FUN_00353238.
 */
void sk_sched_queue_ctx_alloc2(void)
{
    FUN_0035300c();
    uint64_t u = FUN_0034f99c();
    is_38 = u;
    FUN_0034df94(&stack_38);
    FUN_002db6b8();
    FUN_0034dd14();
    FUN_00002850();
    sk_alloc_special(0, 0, 0);              /* FUN_0036a940 */
    FUN_00352444();
    FUN_00359418();
    is_30 = u;
    FUN_0034f9b4();
    FUN_003582b8();
    int ok = FUN_00357bf8();
    if (ok != 0) FUN_003588b8(&stack_8);
    FUN_003526d8();
    FUN_00353238(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5e5c @ 0x001a5e5c   (est. sk_sched_queue_ctx_alloc_u32)
 * Ghidra: void FUN_001a5e5c(void)
 * Allocates a run-queue context keyed by a 32-bit value.
 * Confidence: low (inlined allocator)
 * Notes: FUN_0035193c / FUN_0034f99c / FUN_00359b30 / FUN_0034df94 /
 *   FUN_002db6b8 / FUN_0034dd14 / FUN_00002850 / FUN_0036a940 /
 *   FUN_00352444 / FUN_00359418 / FUN_0034f9b4 / FUN_003582d8 /
 *   FUN_00357bf8 / FUN_003588b8 / FUN_003526d8 / FUN_00351774.
 */
void sk_sched_queue_ctx_alloc_u32(void)
{
    FUN_0035193c();
    FUN_0034f99c();
    us_2c = FUN_00359b30();
    FUN_0034df94(&stack_2c);
    FUN_002db6b8();
    FUN_0034dd14();
    FUN_00002850();
    sk_alloc_special(0, 0, 0);              /* FUN_0036a940 */
    FUN_00352444();
    FUN_00359418();
    FUN_0034f9b4();
    FUN_003582d8();
    int ok = FUN_00357bf8();
    if (ok != 0) FUN_003588b8();
    FUN_003526d8();
    FUN_00351774(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5ee0 @ 0x001a5ee0   (est. sk_sched_queue_ctx_alloc_u16)
 * Ghidra: void FUN_001a5ee0(void)
 * Allocates a run-queue context keyed by a 16-bit value.
 * Confidence: low (inlined allocator)
 * Notes: FUN_0035193c / FUN_0034f99c / FUN_00359b30 / FUN_0034df94 /
 *   FUN_002db6b8 / FUN_0034dd14 / FUN_00002850 / FUN_0036a940 /
 *   FUN_00352444 / FUN_00359418 / FUN_0034f9b4 / FUN_00357bf8 /
 *   FUN_003588b8 / FUN_003526d8 / FUN_00351774.
 */
void sk_sched_queue_ctx_alloc_u16(void)
{
    FUN_0035193c();
    FUN_0034f99c();
    us_2e = FUN_00359b30();
    FUN_0034df94(&stack_2e);
    FUN_002db6b8();
    FUN_0034dd14();
    FUN_00002850();
    sk_alloc_special(0, 0, 0);              /* FUN_0036a940 */
    FUN_00352444();
    FUN_00359418();
    FUN_0034f9b4();
    int ok = FUN_00357bf8();
    if (ok != 0) FUN_003588b8();
    FUN_003526d8();
    FUN_00351774(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5f6c @ 0x001a5f6c   (est. sk_sched_queue_ctx_alloc_u8)
 * Ghidra: void FUN_001a5f6c(void)
 * Allocates a run-queue context keyed by an 8-bit value.
 * Confidence: low (inlined allocator)
 * Notes: FUN_0035193c / FUN_0034f99c / FUN_00359b30 / FUN_0034df94 /
 *   FUN_002db6b8 / FUN_0034dd14 / FUN_00002850 / FUN_0036a940 /
 *   FUN_00352444 / FUN_00359418 / FUN_0034f9b4 / FUN_00357bf8 /
 *   FUN_003588b8 / FUN_003526d8 / FUN_00351774.
 */
void sk_sched_queue_ctx_alloc_u8(void)
{
    FUN_0035193c();
    FUN_0034f99c();
    us_2f = FUN_00359b30();
    FUN_0034df94(&stack_2f);
    FUN_002db6b8();
    FUN_0034dd14();
    FUN_00002850();
    sk_alloc_special(0, 0, 0);              /* FUN_0036a940 */
    FUN_00352444();
    FUN_00359418();
    FUN_0034f9b4();
    int ok = FUN_00357bf8();
    if (ok != 0) FUN_003588b8();
    FUN_003526d8();
    FUN_00351774(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a5ff8 @ 0x001a5ff8   (est. sk_sched_ctx_init_tag677398)
 * Ghidra: void FUN_001a5ff8(...)
 * Initializes a run-queue context tagged 0x677398. (Same shape as
 * FUN_001a5c14 with a different tag.)
 * Confidence: medium
 * Notes: FUN_002db6b8 / FUN_00319350 / FUN_00002534 / FUN_0036a940 /
 *   FUN_0020c5b0 / FUN_00365b6c / FUN_000026e8; tag 0x677398.
 */
void sk_sched_ctx_init_677398(uint64_t *out, uint64_t p2, uint64_t p3, uint8_t p4,
                              uint64_t p5, uint64_t p6)
{
    sv_70 = p2;
    us_68 = p3;
    reg16 v = FUN_002db6b8(&sv_70, p5, p6, 0x677398);
    FUN_00319350(p5, p6);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_80 = p2;
    us_78 = p3;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_80, 0x677398, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x677398;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p4;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6124 @ 0x001a6124   (est. sk_sched_ctx_init_tag677540)
 * Ghidra: void FUN_001a6124(...)
 * Run-queue context initializer tagged 0x677540.
 * Confidence: medium
 * Notes: same shape as FUN_001a5c14; tag 0x677540.
 */
void sk_sched_ctx_init_677540(uint64_t *out, uint32_t p2, uint8_t p3, uint64_t p4, uint64_t p5)
{
    sv_64 = p2;
    reg16 v = FUN_002db6b8(&sv_64, p4, p5, 0x677540);
    FUN_00319350(p4, p5);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_68 = p2;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_68, 0x677540, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x677540;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p3;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6244 @ 0x001a6244   (est. sk_sched_ctx_init_tag677568)
 * Ghidra: void FUN_001a6244(...)
 * Run-queue context initializer tagged 0x677568.
 * Confidence: medium
 * Notes: same shape; tag 0x677568.
 */
void sk_sched_ctx_init_677568(uint64_t *out, uint64_t p2, uint8_t p3, uint64_t p4, uint64_t p5)
{
    sv_68 = p2;
    reg16 v = FUN_002db6b8(&sv_68, p4, p5, 0x677568);
    FUN_00319350(p4, p5);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_70 = p2;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_70, 0x677568, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x677568;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p3;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6364 @ 0x001a6364   (est. sk_sched_ctx_init_tag672870)
 * Ghidra: void FUN_001a6364(...)
 * Run-queue context initializer tagged 0x672870 (byte-keyed).
 * Confidence: medium
 * Notes: same shape; tag 0x672870.
 */
void sk_sched_ctx_init_672870(uint64_t *out, uint8_t p2, uint8_t p3, uint64_t p4, uint64_t p5)
{
    sv_51 = p2;
    reg16 v = FUN_002db6b8(&sv_51, p4, p5, 0x672870);
    FUN_00319350(p4, p5);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_52 = p2;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_52, 0x672870, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x672870;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p3;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6484 @ 0x001a6484   (est. sk_sched_ctx_init_tag6753a0)
 * Ghidra: void FUN_001a6484(...)
 * Run-queue context initializer tagged 0x6753a0.
 * Confidence: medium
 * Notes: same shape; tag 0x6753a0.
 */
void sk_sched_ctx_init_6753a0(uint64_t *out, uint64_t p2, uint64_t p3, uint8_t p4,
                              uint64_t p5, uint64_t p6)
{
    sv_70 = p2;
    us_68 = p3;
    reg16 v = FUN_002db6b8(&sv_70, p5, p6, 0x6753a0);
    FUN_00319350(p5, p6);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_80 = p2;
    us_78 = p3;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_80, 0x6753a0, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x6753a0;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p4;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a65b0 @ 0x001a65b0   (est. sk_sched_ctx_init_dynamic)
 * Ghidra: void FUN_001a65b0(void)
 * Dynamic run-queue context initializer that reads its tag and key from
 * registers/stack and writes the initialized context into unaff_x22.
 * Confidence: low (unaff regs, inlined)
 * Notes: FUN_0035638c / FUN_003515f0 / FUN_002db6b8 / FUN_003512c0 /
 *   FUN_00319350 / FUN_00351360 / FUN_00002534 / FUN_00358fe8 /
 *   FUN_00353ccc / FUN_0020c634 / FUN_0034f9b4 / FUN_00356ff4 /
 *   FUN_003588b8 / FUN_00356370.
 */
void sk_sched_ctx_init_dynamic(void)
{
    FUN_0035638c();
    uint64_t tag = x7;
    us_24 = w4;
    is_60 = FUN_003515f0();
    reg16 v = FUN_002db6b8(&stack_60, x5, x6, tag);
    FUN_003512c0();
    FUN_00319350();
    FUN_00351360();
    FUN_00002534();
    FUN_00358fe8();
    uint64_t u2 = FUN_00353ccc();
    u2 = FUN_0020c634(u2, x3, is_e0, 0);
    FUN_0034f9b4();
    int ok = FUN_00356ff4(&stack_28, &stack_50);
    uint8_t r;
    if (ok == 0) r = 0;
    else { FUN_003588b8(&stack_28); r = w8; }
    x22[0] = x7;
    x22[1] = u2;
    *(char *)(x22 + 2) = (char)us_24;
    *(reg16 *)(x22 + 3) = v;
    *(uint8_t *)(x22 + 5) = r;
    FUN_00356370(x9);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6690 @ 0x001a6690   (est. sk_sched_ctx_init_tag6728f0)
 * Ghidra: void FUN_001a6690(...)
 * Run-queue context initializer tagged 0x6728f0.
 * Confidence: medium
 * Notes: same shape; tag 0x6728f0.
 */
void sk_sched_ctx_init_6728f0(uint64_t *out, uint64_t p2, uint64_t p3, uint8_t p4,
                              uint64_t p5, uint64_t p6)
{
    sv_70 = p2;
    us_68 = p3;
    reg16 v = FUN_002db6b8(&sv_70, p5, p6, 0x6728f0);
    FUN_00319350(p5, p6);
    uint64_t m = FUN_00002534((void*)0x00657628, (void*)0x004f2108);
    sk_alloc_special(m, 0x40, 7);           /* FUN_0036a940 */
    uint64_t u2 = FUN_0020c5b0((void*)0x0034724c, 0);
    sv_80 = p2;
    us_78 = p3;
    uint64_t m2 = FUN_00002534(0x6560e8, (void*)0x004e7ed0);
    int ok = FUN_00365b6c(stack, &sv_80, 0x6728f0, m2, 6);
    if (ok != 0) FUN_000026e8(stack);
    out[0] = 0x6728f0;
    out[1] = u2;
    *(uint8_t *)(out + 2) = p4;
    *(reg16 *)(out + 3) = v;
    *(bool *)(out + 5) = (ok != 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001a67bc @ 0x001a67bc   (est. sk_sched_ctx_init_full)
 * Ghidra: void FUN_001a67bc(...)
 * Full run-queue context initializer: acquires the lock sequence, resolves the
 * type descriptors, allocates the context object, fills its fields, and
 * dispatches through the saved handler slots. Writes the initialized context
 * into the caller's slot.
 * Confidence: low (heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00027614, FUN_002db6b8,
 *   FUN_00365b6c, FUN_0036a940, FUN_0036b118, FUN_0008e500.
 */
void sk_sched_ctx_init_full(uint64_t p1, uint64_t p2, uint8_t p3, uint64_t p4,
                            uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    uint64_t u2 = p8;
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40));/* DAT_00658c00 */
    FUN_003497b4();
    FUN_003514b8(u2);
    FUN_0034b7b8();
    FUN_00319320();
    FUN_00348cd0();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b0c4();
    FUN_00027614(0x6560e0, (void*)0x004e7ec8);
    FUN_00350210(0);
    u2 = FUN_00319338();
    FUN_0034ab20();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b05c();
    FUN_0009461c();
    FUN_00350974();
    reg16 v = FUN_002db6b8();
    FUN_0007c1c4();
    FUN_00319350();
    FUN_00353984();
    thunk_FUN_00200b38();
    FUN_0034b804();
    (**(code_fn **)(x16_01 + 8))(cpu.hi, p7);
    FUN_00359018(0x66a998);
    long obj = FUN_0036a940();
    *(uint64_t *)(obj + 0x10) = p6;
    *(uint64_t *)(obj + 0x18) = p7;
    *(uint64_t *)(obj + 0x20) = p8;
    FUN_0034f5a4(FUN_00319380);
    FUN_001f1878();
    sk_free((void *)obj);                           /* FUN_0036b118 */
    FUN_00351354(*(uint64_t *)(x16_00 + 8));
    x8_02_fn();
    sv_8 = p8;
    uint64_t u4 = FUN_0034a180();
    sk_metatype(u4, u2, &sv_8);          /* FUN_00376820 */
    FUN_0034d734();
    FUN_003193f4();
    FUN_003515a8();
    u2 = FUN_0020c1bc();
    (**(code_fn **)(x16 + 0x20))(x8_01, cpu.lo, p6);
    FUN_0034f9b4();
    FUN_0035a5d8();
    FUN_00350878();
    int ok = FUN_00365b6c();
    uint8_t r;
    if (ok == 0) r = 0;
    else { FUN_003588b8(stack); r = w8; }
    x8[0] = p6;
    x8[1] = u2;
    *(uint8_t *)(x8 + 2) = p3;
    *(reg16 *)(x8 + 3) = v;
    *(uint8_t *)(x8 + 5) = r;
    sk_thread_epilogue(x9);                 /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a6a40 @ 0x001a6a40   (est. swift_collection_init_pair)
 * Ghidra: void FUN_001a6a40(undefined8 *param_1, long param_2)
 * Initializes a Swift collection from a pair of elements: builds the backing
 * buffer via FUN_001a5be8 and copies the resulting 6-word structure into the
 * output array.
 * Confidence: medium
 * Notes: FUN_001a5be8.
 */
void swift_collection_init_pair(uint64_t *out, long p2)
{
    FUN_001a5be8(&sv_50, *x20, *(uint64_t *)(p2 + 0x10));
    out[1] = us_48;
    out[0] = sv_50;
    out[3] = CONCAT71(sv_37, us_38);
    out[2] = us_40;
    *(uint64_t *)((long)out + 0x21) = us_2f;
    *(uint64_t *)((long)out + 0x19) = CONCAT17(us_30, sv_37);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6a8c @ 0x001a6a8c   (est. swift_collection_apply_meta2)
 * Ghidra: void FUN_001a6a8c(undefined8 param_1, undefined8 param_2)
 * Thunk: applies FUN_00310d34 over the collection with metatype DAT_004e8268.
 * Confidence: medium
 * Notes: FUN_003591e8(param_1, param_2, FUN_00310d34, (void*)0x004e8268).
 */
void swift_collection_apply_meta2(uint64_t a, uint64_t b)
{
    FUN_003591e8(a, b, FUN_00310d34, (void*)0x004e8268);
}

/*--------------------------------------------------------------------*/
/* FUN_001a6ab8 @ 0x001a6ab8   (est. sk_sched_runqueue_walk)
 * Ghidra: void FUN_001a6ab8(...)
 * Walks/iterates the run queue, handling string/collection discriminators,
 * appending elements, and re-arming accounting. This is the main scheduler
 * run-queue iteration loop with nested element-append and free paths.
 * Confidence: low (very heavy inlining, indirect dispatch, many unaff regs,
 *   3 unreachable blocks removed by decompiler)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_001a89a8,
 *   FUN_003a25d4, FUN_002a4c98, FUN_00084180, FUN_0036a9a0, FUN_0036b588,
 *   FUN_0008e500; DAT_005d3ebd / DAT_005d32c2 / DAT_005d3eba strings.
 */
void sk_sched_runqueue_walk(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    reg16 x15 = { x22, x24 };
    sk_cpu_current();                       /* FUN_0008e518 */
    reg16 v14 = FUN_00358864();
    uint64_t v10 = v14.hi;
    uint64_t v8 = v14.lo;
    FUN_00350950(p4);
    FUN_0034c654();
    FUN_003514dc();
    uint64_t lock = FUN_00377824();         /* lock */
    FUN_000a6f88(lock, lock);
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_003501d0();
    FUN_0034d464(0);
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350428();
    FUN_003509a4();
    FUN_0034a688();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003497b4();
    FUN_003509a4();
    FUN_0034bd80();
    FUN_003514dc();
    lock = FUN_00377824();                  /* lock */
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350428();
    FUN_00355fac();
    FUN_003497ec();
    FUN_001a89a8();
    FUN_0035a25c();
    uint64_t v13 = x1_00 >> 0x38 & 0xf;
    if (v10 == 0) {
        FUN_00359ab0();
        FUN_00350744();
        FUN_001a89a8();
        FUN_00356e28();
        FUN_00359aa4();
        v10 = x8_01;
        if (!ZR) v10 = v13;
        if (v10 == 0) {
            FUN_003a25d4();
            goto walk_empty;
        }
        if ((x25 >> 0x3d & 1) == 0) {
            FUN_00356798();
            goto walk_lock;
        }
        if ((x22 >> 0x3d & 1) == 0) goto walk_lock;
        FUN_003509e0();
        FUN_0034a148();
        v13 = x1;
        if (!ZR) {
            FUN_00351a50();
            FUN_003a25d4();
            goto walk_done;
        }
        FUN_0034fd5c();
        FUN_002a4c98();
    } else {
        FUN_003497ec();
        FUN_001a89a8();
        FUN_00351a5c();
        FUN_003a25d4(0xe000000000000000);
        FUN_0034c094(v10 & 0xffffffffffff);
        if ((x8_00 == 0) && (((v10 & (x22 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_00354b50(&stack);
            thunk_FUN_0036b270();
            FUN_003a25d4();
            x24 = v8;
        } else {
            if (((x22 >> 0x3d & 1) != 0) && ((v10 >> 0x3d & 1) != 0)) {
                x15 = FUN_00350af4();
                FUN_0034b89c(x15.lo, x15.hi, v8);
                if (!ZR) {
                    FUN_00354410();
                    FUN_003a25d4();
                    goto walk_merge;
                }
            }
            FUN_0034ced8(v8 & 0xffffffffffff);
            x15 = FUN_003515cc();
            FUN_002a4c98(x15.lo, x15.hi, 0);
            x24 = v10;
            v10 = x22;
        }
walk_merge:
        v14 = { x24, v10 };
        x15 = FUN_00355fa0((void*)0x005d3ebd);
        uint64_t v6 = x15.hi;
        v8 = x15.lo;
        FUN_0034b824(x24 & 0xffffffffffff);
        if ((x8_02 == 0) && (((x24 & (v10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(v10);
        } else {
            if ((v10 >> 0x3d & 1) == 0) {
                FUN_00359a84(v8 & 0xffffffffffff);
            } else if ((v6 >> 0x3d & 1) != 0) {
                FUN_000dbe70(x24);
                FUN_0034b1a0();
                x15 = { v8, x1_01 };
                if (!ZR) {
                    FUN_00356b5c();
                    FUN_003a25d4();
                    FUN_003a25d4(v6);
                    goto walk_merge2;
                }
            }
            FUN_00351160();
            FUN_00352db8();
            FUN_002a4c98();
            FUN_003a25d4(v6);
            x15 = v14;
        }
walk_merge2:
        FUN_00359aa4();
        v10 = x8_03;
        if (!ZR) v10 = v13;
        if (v10 == 0) {
            FUN_003a25d4();
walk_empty:
            FUN_00354bb0();
            goto walk_after;
        }
        if ((x25 >> 0x3d & 1) == 0) {
            FUN_00359a84(x15.lo & 0xffffffffffff);
            goto walk_lock2;
        }
        if ((x15.hi >> 0x3d & 1) == 0) goto walk_lock2;
        v14 = FUN_003509e0();
        FUN_0034b1a0(v14.lo, v14.hi, x15.lo);
        v13 = x1;
        if (!ZR) {
            FUN_00351a50();
            FUN_003a25d4();
walk_done:
            FUN_003a25d4();
            v13 = x1;
            goto walk_after;
        }
        FUN_00351160();
        FUN_00352db8();
        FUN_002a4c98();
    }
    FUN_003a25d4();
walk_after:
    uint64_t u5 = FUN_00356780(*(uint64_t *)(x16 + 0x10));
    x8_04_fn(u5, sv_c0, p3);
    FUN_00352680(x21);
    FUN_003508a8(sv_b0);
    x9_fn();
    FUN_003553b8();
    reg16 v14b = FUN_0035190c();
    FUN_00377bec(v14b.lo, v14b.hi, lock);
    FUN_00355fb8();
    FUN_000a68f4();
    FUN_003553cc();
    FUN_00353148();
    uint64_t iter = 1;
    FUN_00354128(x8_05 + 0x20);
    FUN_00353360(x8_06 & 0xffffffffffff | 0x48d8000000000000);
    uint64_t v3 = uRam_4baeb8;
    uint64_t v5 = DAT_004baeb0;
    /* LAB_001a6e70: main iteration loop */
    for (;;) {
        v8 = x15.lo;
        FUN_00352098(&stack_48);
        FUN_00353e2c(lock, sv_c0);
        x9_00_fn();
        FUN_0034b2a8(v8);
        if (ZR) {
            FUN_00350bc0(aus_8);
            x8_12_fn(sv_b0, lock);
            FUN_00352bbc();
            uint8_t *s;
            uint64_t sel;
            if (x8_13 == 0) { s = (void*)0x005d32c2; sel = 1; }
            else { s = (void*)0x005d3eba; sel = 2; }
            FUN_001a89a8(s, sel, 1);
            FUN_00352c80();
            uint64_t v13b = FUN_00349bfc();
            if ((x8_14 == 0) && (((v13b & ((uint64_t)sv_b0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(sv_b0);
            } else {
                if (((uint64_t)sv_b0 >> 0x3d & 1) == 0) FUN_0034a798();
                FUN_0034c0a4();
                FUN_002a4c98();
                FUN_003a25d4(iter);
            }
            x15 = FUN_00084180();           /* yield */
            sk_thread_epilogue(x15.lo, x15.hi, x30); /* FUN_0008e500 */
            return;
        }
        FUN_00353148();
        fn12 = (code_fn *)*x8_07;
        FUN_003505c4(sv_a0);
        fn12();
        slot_ptr = sv_b0;
        if ((int)iter == 0) {
            FUN_003536bc();
            FUN_00356e28();
            uint64_t v6b = FUN_00349bfc();
            if ((x8_08 == 0) && (((v6b & ((uint64_t)sv_b0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(sv_b0);
            } else {
                iter = v8 >> 0x38 & 0xf;
                if (((uint64_t)sv_b0 >> 0x3d & 1) == 0) {
                    FUN_00356798();
                    v6b = x8_09;
                    if (!ZR) v6b = iter;
                } else if ((v8 >> 0x3d & 1) == 0) {
                    v6b = x15.hi & 0xffffffffffff;
                } else {
                    FUN_00351494();
                    FUN_0034a148();
                    v6b = iter;
                    if (!ZR) {
                        FUN_0034f484();
                        FUN_003a25d4();
                        FUN_003a25d4(v8);
                        goto walk_node;
                    }
                }
                FUN_0034fd5c();
                FUN_002a4c98();
                FUN_003a25d4(v8);
                iter = v6b;
                slot_ptr = &stack_e8;
            }
        }
walk_node:
        uint64_t u7 = FUN_0008e0d4();
        uint64_t node = FUN_0036a9a0(u7, aus_58);
        *(uint64_t *)(node + 0x18) = v3;
        *(uint64_t *)(node + 0x10) = v5;
        *(uint64_t *)(node + 0x38) = v13b;
        uint64_t u7b = FUN_00319a4c(node + 0x20);
        FUN_00354618(u7b, sv_a0, v13b);
        fn12();
        FUN_00359a54();
        FUN_003509f8(iter);
        x15 = FUN_001a89a8();
        uint64_t v6c = x15.hi;
        uint64_t v7c = x15.lo;
        FUN_0034f030();
        x15 = { x1_02, v7c };
        reg16 a2 = { x1_02, v7c };
        reg16 a1 = { x1_02, v7c };
        FUN_003509f8(iter);
        FUN_001a89a8();
        FUN_00319808(node + 0x20, &stack_88);
        FUN_00310d98(&stack_88, aus_98);
        iter = FUN_00349bfc();
        if ((x8_10 == 0) && (((iter & ((uint64_t)slot_ptr ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(slot_ptr);
        } else {
            if (((uint64_t)slot_ptr >> 0x3d & 1) == 0) {
                ZR = (x1_03 & 0x2000000000000000) == 0;
            } else if ((x1_03 >> 0x3d & 1) != 0) {
                FUN_00353098();
                FUN_0034b7c8();
                if (!ZR) {
                    FUN_00352c74();
                    FUN_003a25d4(slot_ptr);
                    FUN_003a25d4(x1_03);
                    FUN_00354bb0();
                    goto walk_loop_tail;
                }
                FUN_00354bb0();
            }
            thunk_FUN_0036b270(x1_03);
            FUN_00350b6c();
            FUN_00352cc8();
            FUN_002a4c98();
            FUN_003a2610(x1_03, 2);
        }
walk_loop_tail:
        FUN_0034895c();
        FUN_0034d274(aus_98, &stack_e8);
        FUN_00353d64();
        FUN_002060d4();
        FUN_000026e8(aus_98);
        FUN_0036b588(node);
        FUN_00002688();
        FUN_00002834();
        FUN_0036b6ac();
        FUN_003a25d4(x1_02);
        iter = FUN_00349bfc();
        if ((x8_11 != 0) || (((iter & (node ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
            if ((node >> 0x3d & 1) == 0) {
                ZR = (v6c & 0x2000000000000000) == 0;
            } else if ((v6c >> 0x3d & 1) != 0) {
                FUN_00351494();
                FUN_0034b7c8();
                if (!ZR) {
                    FUN_00354858();
                    FUN_003a25d4(node);
                    FUN_003a25d4(v6c);
                    iter = 0;
                    x15 = a2;
                    continue;               /* back to LAB_001a6e70 */
                }
            }
            FUN_003516e4();
            FUN_00352cc8();
            FUN_002a4c98();
            FUN_003a25d4(v6c);
            iter = 0;
            x15 = a1;
            continue;                       /* back to LAB_001a6e70 */
        }
        FUN_003a25d4(node);
        iter = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a7310 @ 0x001a7310   (est. swift_collection_init_from)
 * Ghidra: void FUN_001a7310(...)
 * Initializes a Swift collection from a source: builds the backing buffer via
 * FUN_001a73cc and stores the resulting structure.
 * Confidence: medium
 * Notes: FUN_0034a210 / FUN_00002534 / FUN_001a73cc / FUN_00310d80 /
 *   FUN_003488f4 / FUN_0019e578.
 */
void swift_collection_init_from(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sv_50 = p4;
    us_48 = p2;
    sv_40 = p3;
    FUN_0034a210();
    uint64_t u1 = FUN_00002534();
    sv_28 = FUN_001a73cc(p1, FUN_0031940c, aus_60, p4, u1, 0x66c1c8, &sv_28);
    if (x21 == 0) {
        FUN_003504e8();
        reg16 v = FUN_00310d80();
        FUN_003488f4(v.lo, v.hi, v.lo);
        FUN_0019e578(&sv_28);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a73cc @ 0x001a73cc   (est. swift_buffer_build)
 * Ghidra: undefined8 FUN_001a73cc(...)
 * Builds a Swift buffer: resolves the type descriptor, dispatches through the
 * metatype slot, initializes the element storage, and runs the constructor
 * pipeline (FUN_001ded00). Returns the initialized buffer.
 * Confidence: medium
 * Notes: DAT_00658c00 dispatch, FUN_001dd408, FUN_001a26e0, FUN_001ded00,
 *   FUN_0036b118.
 */
uint64_t swift_buffer_build(uint64_t p1, void (*cb)(void), uint64_t p3, uint64_t p4,
                            long p5, uint64_t p6, uint64_t p7)
{
    long desc = *(long *)(p5 - 8);
    uint64_t u2 = p4;
    sv_88 = p6;
    uint64_t u1 = dispatch_slot(*(uint64_t *)(desc + 0x40)); /* DAT_00658c00 */
    reg16 v = FUN_001dd408(u1, u2);
    uint64_t hi = v.hi;
    uint64_t lo = v.lo;
    sv_70 = 0;
    sv_80 = FUN_001a26e0(hi, p1);
    cb(sv_80, &sv_70, stack_aligned);
    if (x21 == 0) {
        FUN_001ded00(&sv_70, p1, sv_80, &hi, &lo, p4, p5, sv_88);
    } else {
        (**(code_fn **)(desc + 0x20))(p7, stack_aligned, p5);
        FUN_001ded00(&sv_70, p1, sv_80, &hi, &lo, p4, p5, sv_88);
        lo = FUN_0036b118(lo);              /* free */
    }
    return lo;
}

/*--------------------------------------------------------------------*/
/* FUN_001a7544 @ 0x001a7544   (est. swift_buffer_build_thunk)
 * Ghidra: void FUN_001a7544(void)
 * Buffer-build thunk: resolves the type descriptor, builds the buffer via
 * FUN_001a73cc, and stores the result.
 * Confidence: medium
 * Notes: DAT_00658c00, FUN_001a73cc, FUN_00310d80, FUN_0019e578.
 */
void swift_buffer_build_thunk(void)
{
    long desc = *(long *)(x4 - 8);
    dispatch_slot(*(uint64_t *)(desc + 0x40));  /* DAT_00658c00 */
    sv_48 = FUN_001a73cc();
    if (x21 == 0) {
        reg16 v = FUN_00310d80(0, x3);
        FUN_0019e578(&sv_48, v.hi, v.lo, 0x66b5c8);
    } else {
        (**(code_fn **)(desc + 0x20))(x6, stack_aligned, x4);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a7644 @ 0x001a7644   (est. sk_sched_queue_advance)
 * Ghidra: void FUN_001a7644(...)
 * Advances the run-queue cursor: runs the lock sequence, computes the new slot
 * index by stride, and dispatches through the saved handler.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_00349ef4 / FUN_00310f94 / FUN_0034bcf0 / FUN_0034ce98 /
 *   FUN_00377824 / FUN_00351f10 / FUN_00310fc4 / FUN_0035133c /
 *   FUN_0034d334.
 */
void sk_sched_queue_advance(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_00349ef4();
    FUN_00310f94(p3);
    FUN_0034bcf0();
    long base = x8_fn();
    FUN_0034ce98();
    FUN_00377824();                         /* lock */
    FUN_00351f10();
    long stride = *(long *)(x16 + 0x48);
    FUN_00310fc4();
    FUN_0035133c();
    FUN_0034d334(base + stride * x22);
    x9_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a76d0 @ 0x001a76d0   (est. sk_sched_queue_trim_thunk)
 * Ghidra: void FUN_001a76d0(void)
 * Thunk: trims/compacts the queue via the shared helper.
 * Confidence: medium
 * Notes: FUN_001dedf8.
 */
void sk_sched_queue_trim_a(void) { FUN_001dedf8(); }

/*--------------------------------------------------------------------*/
/* FUN_001a76d4 @ 0x001a76d4   (est. sk_sched_queue_trim_thunk)
 * Ghidra: void FUN_001a76d4(void)
 * Thunk: alias of FUN_001a76d0; same shared trim helper.
 * Confidence: medium
 * Notes: FUN_001dedf8.
 */
void sk_sched_queue_trim_b(void) { FUN_001dedf8(); }

/*--------------------------------------------------------------------*/
/* FUN_001a76fc @ 0x001a76fc   (est. swift_buffer_foreach_elem)
 * Ghidra: void FUN_001a76fc(...)
 * Iterates the elements of a Swift buffer, dispatching through the metatype
 * slot and invoking the caller-supplied callback for each element.
 * Confidence: medium
 * Notes: DAT_00658c00 dispatch, FUN_001e4cbc, FUN_00027788-style type walk.
 */
void swift_buffer_foreach_elem(uint64_t p1, void (*cb)(void), uint64_t p3, long p4,
                               long p5, uint64_t p6, long p7, uint64_t p8, uint64_t p9)
{
    long desc = *(long *)(p7 - 8);
    dispatch_slot(*(uint64_t *)(desc + 0x40));       /* DAT_00658c00 */
    uint64_t off = (uint64_t)*(uint8_t *)(*(long *)(p5 - 8) + 0x50);
    reg16 v = FUN_001e4cbc(p4 + (off + 0x20 & (off ^ 0xffffffffffffffff)),
                           *(uint64_t *)(p4 + 0x10));
    cb(p1, v.lo, v.hi, stack_aligned);
    if (x21 != 0)
        (**(code_fn **)(desc + 0x20))(p9, stack_aligned, p7);
}

/*--------------------------------------------------------------------*/
/* FUN_001a7804 @ 0x001a7804   (est. swift_span_precondition)
 * Ghidra: void FUN_001a7804(undefined8 param_1, long param_2)
 * Swift Span precondition: fatals if the count is negative.
 * Confidence: high (string-matched fatal "Count must not be negative" +
 *   "Swift.Span")
 * Notes: strings at 0x005d3630 / 0x005d35c0.
 */
void swift_span_precondition(uint64_t p1, long count)
{
    if (count >= 0) return;
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_count_must_not_neg, 0x1a, 2,
                   s_swift_span, 0x10, 2, 0xa1, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a7864 @ 0x001a7864   (est. swift_array_with_unsafe_mut)
 * Ghidra: void FUN_001a7864(...)
 * Runs a closure with the array's unsafe mutable buffer pointer: resolves the
 * element stride, initializes the buffer, invokes the closure, then validates
 * the buffer pointers.
 * Confidence: medium
 * Notes: FUN_0034e4ec / FUN_001dc298 / FUN_001a26e0 / FUN_00358eb8 /
 *   FUN_001a7914.
 */
void swift_array_with_unsafe_mut(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0034e4ec();
    thunk_FUN_001dc298(p3);
    long *q = x20;
    uint64_t len = *(uint64_t *)(*q + 0x10);
    uint64_t off = (uint64_t)*(uint8_t *)(*(long *)(*(long *)(x23 + 0x10) - 8) + 0x50);
    off = off + 0x20 & (off ^ 0xffffffffffffffff);
    reg16 buf = FUN_001a26e0(*q + off, len);
    FUN_00358eb8(x8, buf);
    x25_fn();                                   /* closure */
    FUN_001a7914(buf, *q + off, len);
}

/*--------------------------------------------------------------------*/
/* FUN_001a7914 @ 0x001a7914   (est. swift_buffer_validate_ptr)
 * Ghidra: void FUN_001a7914(long *param_1, long param_2, long param_3)
 * Validates a Swift buffer pointer against the expected base/length; fatals
 * on mismatch.
 * Confidence: medium
 * Notes: fatal FUN_001afe4c on mismatch.
 */
void swift_buffer_validate_ptr(long *buf, long base, long len)
{
    if (*buf != 0 && base == *buf && buf[1] == len) return;
    FUN_003488bc(1);
    FUN_0034a3d8();
    FUN_003504b8();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7988 @ 0x001a7988   (est. swift_array_with_unsafe_mut_fatal)
 * Ghidra: void FUN_001a7988(void)
 * Fatal path for Array.withUnsafeMutableBufferPointer misuse.
 * Confidence: high (string-matched fatal "Array.withUnsafeMutableBufferPoi")
 * Notes: string at 0x005d3e70.
 */
void swift_array_with_unsafe_mut_fatal(void)
{
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_array_with_unsafe_mut, 0x49, 2,
                   s_swift_array, 0x11, 2, 0x73b, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001a79e0 @ 0x001a79e0   (est. swift_fatal_error_alt)
 * Ghidra: void FUN_001a79e0(...)
 * Alternate Swift fatal-error entry: formats the message via FUN_0006f768
 * then fatals.
 * Confidence: medium
 * Notes: FUN_0006f768(param_4, s_Fatal_error, ...); fatal FUN_001afe4c.
 */
void swift_fatal_error_alt(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    FUN_0006f768(p4, s_Fatal_error, p2, p3, p1, p2);
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7ae4 @ 0x001a7ae4   (est. sk_sched_borrow_fatal)
 * Ghidra: void FUN_001a7ae4(void)
 * Fatal path for a borrow/underflow condition in the scheduler.
 * Confidence: medium
 * Notes: FUN_0035047c / FUN_003480ac / fatal FUN_001afe4c.
 */
void sk_sched_borrow_fatal(void)
{
    FUN_0035047c();
    FUN_003480ac();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7b08 @ 0x001a7b08   (est. sk_sched_queue_rebuild_thunk)
 * Ghidra: void FUN_001a7b08(void)
 * Thunk: rebuilds the queue via the shared helper.
 * Confidence: medium
 * Notes: FUN_001defc8.
 */
void sk_sched_queue_rebuild_thunk(void) { FUN_001defc8(); }

/*--------------------------------------------------------------------*/
/* FUN_001a7b38 @ 0x001a7b38   (est. sk_sched_queue_foreach_slot)
 * Ghidra: void FUN_001a7b38(void)
 * Iterates the run-queue slots: for each of the len slots, runs the lock
 * sequence and dispatches through the saved handler. Ends with the thread
 * epilogue.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_002298d4, FUN_0031945c,
 *   FUN_0019ea20; trap at 0x1a7c1c; FUN_0008e500 epilogue.
 */
void sk_sched_queue_foreach_slot(void)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_00349a18();
    FUN_00349720();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348f38();
    thunk_FUN_002298d4(*(uint64_t *)(x1 + 0x10));
    if (*(long *)(x22 + 0x10) != 0) {
        code_fn *fn = (code_fn *)FUN_0031945c();
        long i = 0;
        do {
            FUN_0034d7dc();
            FUN_0019ea20();
            long next = i + 1;
            if (SCARRY8(i, 1)) __builtin_trap();    /* 0x1a7c1c */
            FUN_00355af8();
            FUN_003504a0();
            fn();
            FUN_003507bc(*(uint64_t *)(x16 + 8));
            x8_00_fn();
            i++;
        } while (next != *(long *)(x22 + 0x10));
    }
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7c1c @ 0x001a7c1c   (est. sk_sched_slot_step)
 * Ghidra: void FUN_001a7c1c(void)
 * Advances one run-queue slot: runs the lock sequence and dispatches.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034a958 / FUN_0031945c / FUN_0034c8a0 + indirect.
 */
void sk_sched_slot_step(void)
{
    FUN_0034a958();
    FUN_0031945c();
    FUN_0034c8a0();
    x8_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a7c6c @ 0x001a7c6c   (est. sk_sched_queue_dispatch_elem)
 * Ghidra: void FUN_001a7c6c(...)
 * Dispatches one element through the queue handler: resolves the type and
 * jumps through the saved callback.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034c034 / FUN_0031948c / FUN_0034bec4 + indirect.
 */
void sk_sched_queue_dispatch_elem(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0034c034();
    uint64_t u = FUN_0031948c(p3);
    FUN_0034bec4(u);
    x8_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a7cf4 @ 0x001a7cf4   (est. sk_sched_queue_step_loop)
 * Ghidra: void FUN_001a7cf4(...)
 * Steps through a run-queue slot under the lock sequence and dispatches.
 * Confidence: low (indirect dispatch, many helpers)
 * Notes: FUN_00350b54 / FUN_0034e2d0 / FUN_00351624 / FUN_0034a808 /
 *   FUN_0034a5f0 / FUN_0034bed4 / FUN_0034a5dc / FUN_00355340 /
 *   FUN_0031945c / FUN_00357b20 / FUN_003504a0 / FUN_001a8564.
 */
void sk_sched_queue_step_loop(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_00350b54();
    FUN_0034e2d0();
    FUN_00351624();
    FUN_0034a808();
    FUN_0034a5f0();
    FUN_0034bed4();
    FUN_0034a5dc();
    FUN_00355340();
    FUN_0031945c(p3);
    FUN_00357b20();
    FUN_003504a0();
    x8_fn();
    FUN_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_001a7d64 @ 0x001a7d64   (est. sk_sched_queue_sync_thunk)
 * Ghidra: void FUN_001a7d64(void)
 * Thunk: syncs the queue via the shared helper.
 * Confidence: medium
 * Notes: FUN_001df334.
 */
void sk_sched_queue_sync_a(void) { FUN_001df334(); }

/*--------------------------------------------------------------------*/
/* FUN_001a7d68 @ 0x001a7d68   (est. sk_sched_queue_sync_thunk)
 * Ghidra: void FUN_001a7d68(void)
 * Thunk: alias of FUN_001a7d64.
 * Confidence: medium
 * Notes: FUN_001df334.
 */
void sk_sched_queue_sync_b(void) { FUN_001df334(); }

/*--------------------------------------------------------------------*/
/* FUN_001a7da4 @ 0x001a7da4   (est. swift_buffer_multiply_check)
 * Ghidra: void FUN_001a7da4(long param_1, long param_2, long param_3)
 * Validates a Swift buffer base/length with overflow-checked stride multiply.
 * Fatals on negative length or on a non-null-required length with null base.
 * Confidence: medium
 * Notes: overflow trap at 0x1a7e24; fatal FUN_001afe4c.
 */
void swift_buffer_multiply_check(long base, long count, long desc)
{
    long stride = *(long *)(*(long *)(desc - 8) + 0x48);
    long nbytes = count * stride;
    if (SUB168(SEXT816(count) * SEXT816(stride), 8) != nbytes >> 0x3f) __builtin_trap(); /* 0x1a7e24 */
    if (nbytes < 0) {
        FUN_003483c4();
    } else {
        if (nbytes == 0 || base != 0) return;
        FUN_003488bc(1);
        FUN_00349644();
    }
    FUN_00351094();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7e30 @ 0x001a7e30   (est. sk_sched_queue_alloc_ctx_thunk)
 * Ghidra: void FUN_001a7e30(void)
 * Thunk: allocates the queue context via FUN_001a7e5c.
 * Confidence: medium
 */
void sk_sched_queue_alloc_ctx_a(void) { FUN_001a7e5c(); }

/*--------------------------------------------------------------------*/
/* FUN_001a7e34 @ 0x001a7e34   (est. sk_sched_queue_alloc_ctx_thunk)
 * Ghidra: void FUN_001a7e34(void)
 * Thunk: alias of FUN_001a7e30.
 * Confidence: medium
 */
void sk_sched_queue_alloc_ctx_b(void) { FUN_001a7e5c(); }

/*--------------------------------------------------------------------*/
/* FUN_001a7e5c @ 0x001a7e5c   (est. sk_sched_queue_alloc_ctx)
 * Ghidra: void FUN_001a7e5c(void)
 * Allocates the run-queue context: runs the descriptor/lock sequence and
 * forwards to the shared allocator helper.
 * Confidence: low (inlined)
 * Notes: FUN_0034d2b4 / FUN_0034a210 / FUN_00002534 / FUN_003498c4 /
 *   FUN_0035a0b8 / FUN_00352d34 / FUN_0034ef08 / FUN_001de8a8.
 */
void sk_sched_queue_alloc_ctx(void)
{
    FUN_0034d2b4();
    FUN_0034a210();
    FUN_00002534();
    FUN_003498c4();
    FUN_0035a0b8();
    FUN_00352d34();
    FUN_0034ef08();
    FUN_001de8a8();
}

/*--------------------------------------------------------------------*/
/* FUN_001a7ed8 @ 0x001a7ed8   (est. swift_buffer_multiply_check2)
 * Ghidra: void FUN_001a7ed8(long param_1, long param_2, long param_3)
 * Buffer multiply-check variant with different fatal helpers.
 * Confidence: medium
 * Notes: overflow trap at 0x1a7f40; FUN_00348284 / FUN_00348508;
 *   fatal FUN_001afe4c.
 */
void swift_buffer_multiply_check2(long base, long count, long desc)
{
    long stride = *(long *)(*(long *)(desc - 8) + 0x48);
    long nbytes = count * stride;
    if (SUB168(SEXT816(count) * SEXT816(stride), 8) != nbytes >> 0x3f) __builtin_trap(); /* 0x1a7f40 */
    if (nbytes < 0) {
        FUN_00348284();
    } else {
        if (nbytes == 0 || base != 0) return;
        FUN_00348508();
    }
    FUN_00351094();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7f4c @ 0x001a7f4c   (est. sk_sched_queue_meta_set)
 * Ghidra: void FUN_001a7f4c(void)
 * Sets the run-queue metadata slots: resolves the type descriptor and stores
 * it with the element-dispatch pointer into the queue context array.
 * Confidence: medium
 * Notes: FUN_0034ed08 / FUN_003194e0 / DAT_004f18d8.
 */
void sk_sched_queue_meta_set(void)
{
    FUN_0034ed08();
    uint64_t u = FUN_003194e0();
    x20[3] = u;
    x20[4] = (void*)0x004f18d8;
    *x20 = x19;
}

/*--------------------------------------------------------------------*/
/* FUN_001a7fa0 @ 0x001a7fa0   (est. sk_sched_queue_meta_alloc)
 * Ghidra: void FUN_001a7fa0(void)
 * Allocates the run-queue metadata: resolves the type descriptor and
 * allocates the backing pages.
 * Confidence: medium
 * Notes: FUN_0034ed08 / FUN_00310d34 / FUN_00357f24 / FUN_0036b270.
 */
void sk_sched_queue_meta_alloc(void)
{
    FUN_0034ed08();
    FUN_00310d34();
    FUN_00357f24();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a7fcc @ 0x001a7fcc   (est. sk_sched_queue_slot_dispatch)
 * Ghidra: void FUN_001a7fcc(void)
 * Dispatches one run-queue slot: runs the lock sequence, forwards through
 * FUN_001a8068, and jumps through the saved handler.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_00077888 / DAT_00658c00 / FUN_0034c818 / FUN_001a8068 /
 *   FUN_00350aa0.
 */
void sk_sched_queue_slot_dispatch(void)
{
    FUN_00077888();
    FUN_00349720();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_003490ec();
    FUN_0019ea20();
    FUN_0034c818(x8);
    FUN_001a8068();
    FUN_00350aa0(*(uint64_t *)(x16 + 8));
    x8_01_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8068 @ 0x001a8068   (est. sk_sched_queue_advance_dispatch)
 * Ghidra: void FUN_001a8068(void)
 * Advances the run-queue cursor through the lock sequence and dispatch slots.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_00350a28 / FUN_00356ba4 / FUN_00349b00 / DAT_00658c00 /
 *   FUN_00349178 / FUN_00353ba0 / FUN_0034ba28 / FUN_00228e78.
 */
void sk_sched_queue_advance_dispatch(void)
{
    FUN_00350a28();
    FUN_00356ba4();
    FUN_00349b00();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00349178();
    FUN_00353ba0();
    x8_00_fn();
    FUN_0034ba28();
    FUN_00228e78();
}

/*--------------------------------------------------------------------*/
/* FUN_001a80f4 @ 0x001a80f4   (est. sk_sched_queue_walk_result)
 * Ghidra: undefined8 FUN_001a80f4(void)
 * Walks the run queue and returns the outcome: 2 on empty input, 1 on a full
 * successful walk, 0 if the walk terminated early. Iterates each element,
 * dispatching through the slot handler.
 * Confidence: low (inlined walk loop, unaff regs)
 * Notes: FUN_00350980 / FUN_00344d4c / FUN_00002534 / FUN_00356fcc /
 *   FUN_00344e54 / FUN_00077070 / FUN_001a7fcc / FUN_0031997c.
 */
uint64_t sk_sched_queue_walk_result(void)
{
    uint64_t u3 = FUN_00350980();
    FUN_00344d4c(u3, aus_b8);
    FUN_003519c0();
    FUN_00002534((void*)0x00657578, (void*)0x004f1908);
    int init = FUN_00356fcc(&sv_e0, aus_b8);
    if (init == 0) {
        sv_c0 = 0;
        us_d8 = 0;
        sv_e0 = 0;
        sv_c8 = 0;
        us_d0 = 0;
        FUN_00344e54(&sv_e0, (void*)0x00657580, (void*)0x004f1910);
        return 2;
    }
    FUN_00077070(&sv_e0, aus_90);
    long n = *(long *)(x22 + 0x10);
    FUN_0034b440(aus_90);
    FUN_00083a18();
    FUN_0034ce58();
    long got = x8_fn();
    if (n == got) {
        if (n != 0) {
            long i = 0;
            do {
                FUN_0034b508(aus_b8);
                FUN_001a7fcc();
                FUN_0034c4dc(aus_90);
                FUN_003430dc();
                FUN_0034fe80(&sv_e0);
                x9_fn();
                FUN_0034bca4(aus_b8);
                FUN_000dbd0c(aus_108);
                x9_00_fn();
                u3 = us_e8;
                FUN_0006a4c0(aus_108, sv_f0);
                uint64_t u1 = sv_c0;
                FUN_000dbcc8(&sv_e0, sv_c8);
                FUN_00353b1c(u1);
                FUN_00350944(aus_130);
                x9_01_fn();
                u3 = FUN_0031997c(u3);
                FUN_00350b18(u3, aus_130);
                uint64_t ok = x8_00_fn();
                FUN_000026e8(aus_130);
                FUN_000026e8(aus_108);
                FUN_003199ac(&sv_e0);
                FUN_003199ac(aus_b8);
                if ((ok & 1) == 0) goto walk_short;
                i++;
            } while (n != i);
        }
        FUN_000026e8(aus_90);
        return 1;
    }
walk_short:
    FUN_000026e8(aus_90);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001a82dc @ 0x001a82dc   (est. sk_sched_key_setup)
 * Ghidra: void FUN_001a82dc(void)
 * Sets up a scheduler key: derives a per-CPU byte via FUN_00348c48, mixes it
 * with a reversed string constant (s_uespemosmodnarodarenegylsetybdet — the
 * reversed "type-derandomized-modern-..." scheduler key material), then
 * initializes the two queue stages.
 * Confidence: medium
 * Notes: FUN_00355684 / FUN_00348c48 / FUN_0034d264 / FUN_001a8368 /
 *   FUN_001a842c; string at 0x004e7a30.
 */
void sk_sched_key_setup(void)
{
    FUN_00355684();
    uint8_t b = FUN_00348c48();
    FUN_0034d264(b, s_reversed_key._16_8_, b ^ s_reversed_key._0_8_);
    FUN_001a8368();
    FUN_001a842c();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8368 @ 0x001a8368   (est. sk_sched_key_stage1)
 * Ghidra: void FUN_001a8368(void)
 * First stage of scheduler key expansion: iterates over the key material,
 * mixing each element through the queue slot dispatcher.
 * Confidence: low (inlined loop, unaff regs)
 * Notes: FUN_000b4594 / FUN_00349a18 / FUN_002298d4 / FUN_001a7fcc /
 *   FUN_0034b8cc / FUN_000b45b0.
 */
void sk_sched_key_stage1(void)
{
    FUN_000b4594();
    FUN_00349a18();
    long n = *(long *)(x1 + 0x10);
    thunk_FUN_002298d4(n);
    if (n != 0) {
        long i = 0;
        do {
            i++;
            FUN_0034b358(&stack_28);
            FUN_001a7fcc();
            FUN_0006a4c0(&stack_28, is_40);
            FUN_0035159c();
            FUN_00353b1c();
            FUN_00350738();
            x9_fn();
            FUN_0006a4c0();
            FUN_0035159c();
            FUN_00343a30();
            reg16 v = FUN_0034b8cc();
            x8_fn(v.lo, v.hi, is_20);
            FUN_000026e8();
            FUN_003199ac(&stack_28);
        } while (n != i);
    }
    FUN_000b45b0(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a842c @ 0x001a842c   (est. sk_sched_key_mix)
 * Ghidra: void FUN_001a842c(void)
 * Mixes the 5-word scheduler key state (a reduced SHA-256-style compression
 * round: XOR/rotate/add on the key words) and stores the result.
 * Confidence: medium (crypto-style mixing constant structure)
 * Notes: word rotations (0xd/0x10/0x15/0x2b/0x33), XOR with 0xff; passes to
 *   FUN_00351d4c.
 */
void sk_sched_key_mix(void)
{
    uint64_t w0 = x20[2];
    uint64_t w4 = x20[4] ^ *x20;
    uint64_t a = w0 + x20[1];
    uint64_t b = a ^ (w0 >> 0x33 | w0 << 0xd);
    uint64_t c = w4 + x20[3] + b;
    uint64_t d = w4 + x20[3] ^ (w4 >> 0x30 | w4 << 0x10);
    uint64_t e = d + (a >> 0x20 | a << 0x20);
    uint64_t f = e ^ (d >> 0x2b | d << 0x15);
    uint64_t g = (e ^ *x20) + (c ^ (b >> 0x2f | b << 0x11));
    uint64_t h = ((c >> 0x20 | c << 0x20) ^ 0xff) + f ^ (f >> 0x30 | f << 0x10);
    FUN_00351d4c((g >> 0x20 | g << 0x20) + h ^ (h >> 0x2b | h << 0x15));
}

/*--------------------------------------------------------------------*/
/* FUN_001a8498 @ 0x001a8498   (est. sk_sched_key_round)
 * Ghidra: void FUN_001a8498(void)
 * Runs one scheduler key round: lock sequence, key stage1, then key mix.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034e2d0 / FUN_00351624 / FUN_0034a808 / FUN_0034a5f0 /
 *   FUN_0034bed4 / FUN_0034a5dc / FUN_00355334 / FUN_001a8368 /
 *   FUN_001a8564.
 */
void sk_sched_key_round(void)
{
    FUN_0034e2d0();
    FUN_00351624();
    FUN_0034a808();
    FUN_0034a5f0();
    FUN_0034bed4();
    FUN_0034a5dc();
    FUN_00355334();
    FUN_001a8368();
    FUN_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_001a84f4 @ 0x001a84f4   (est. sk_sha256_iv_init)
 * Ghidra: void FUN_001a84f4(undefined8 *param_1, ulong param_2)
 * Initializes a SHA-256 IV (or key-schedule state) with the standard SHA-256
 * initial hash constants XORed with a per-context key: the literals
 * "somepseu"/"dorandom"/"tedbytes" are the rotated SHA-256 IV words
 * 0x6a09e667 (some...), etc. Seeds the 5-word state.
 * Confidence: high (crypto constants 0x736f6d6570736575="somepseu",
 *   0x646f72616e646f6d="dorandom", 0x7465646279746573="tedbytes" match the
 *   SHA-256 IV endian-reversed)
 * Notes: _DAT_006adf10 / _DAT_006adf18 key globals; FUN_00352f60.
 */
void sk_sha256_iv_init(uint64_t *state, uint64_t key)
{
    uint64_t k = DAT_006adf10 ^ key;
    uint64_t c2 = DAT_006adf18 ^ 0x7465646279746573;
    uint64_t c1 = DAT_006adf18 ^ 0x646f72616e646f6d;
    state[0] = 0;
    state[1] = k ^ 0x736f6d6570736575;
    state[2] = c1;
    state[3] = k ^ 0x6c7967656e657261;
    state[4] = c2;
    FUN_00352f60();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8564 @ 0x001a8564   (est. sk_sha256_compress_round)
 * Ghidra: ulong FUN_001a8564(void)
 * One SHA-256-style compression round over the 5-word state (rotations
 * 0xd/0x10/0x15/0x2b/0x2f/0x30/0x33, add-with-XOR). Returns a mixing
 * aggregate and updates the state words.
 * Confidence: medium (crypto mixing structure)
 * Notes: rotation constants; FUN_00353fd4; word stores at x20[1..4].
 */
uint64_t sk_sha256_compress_round(void)
{
    uint64_t w1 = x20[4] ^ *x20;
    uint64_t w5 = x20[2];
    uint64_t a = w5 + x20[1];
    uint64_t b = a ^ (w5 >> 0x33 | w5 << 0xd);
    uint64_t c = x20[3] + w1 + b;
    uint64_t d = x20[3] + w1 ^ (w1 >> 0x30 | w1 << 0x10);
    uint64_t e = d + (a >> 0x20 | a << 0x20);
    uint64_t f = e ^ (d >> 0x2b | d << 0x15);
    uint64_t g = c ^ (b >> 0x2f | b << 0x11);
    uint64_t h = (e ^ *x20) + g;
    uint64_t i = h ^ (g >> 0x33 | g << 0xd);
    uint64_t j = ((c >> 0x20 | c << 0x20) ^ 0xff) + f;
    uint64_t k = i + j;
    uint64_t l = j ^ (f >> 0x30 | f << 0x10);
    uint64_t m = (h >> 0x20 | h << 0x20) + l;
    uint64_t n = (k ^ (i >> 0x2f | i << 0x11)) + m;
    uint64_t o = m ^ (l >> 0x2b | l << 0x15);
    uint64_t p = (k >> 0x20 | k << 0x20) + o ^ (o >> 0x30 | o << 0x10);
    FUN_00353fd4((n >> 0x20 | n << 0x20) + p ^ (p >> 0x2b | p << 0x15));
    uint64_t r3 = x10 ^ (x8 >> 0x2b | x8 << 0x15);
    x20[3] = x12 >> 0x20 | x12 << 0x20;
    x20[4] = r3;
    x20[1] = x10;
    x20[2] = x9;
    return x9 ^ x10 ^ (x12 >> 0x20 | x12 << 0x20) ^ r3;
}

/*--------------------------------------------------------------------*/
/* FUN_001a862c @ 0x001a862c   (est. sk_sched_key_stage2)
 * Ghidra: void FUN_001a862c(void)
 * Second stage of scheduler key expansion: allocates the key pages and
 * derives a final selector byte (uVar1 ^ 1).
 * Confidence: low (inlined)
 * Notes: FUN_003530e8 / FUN_00352ddc / FUN_00310d34 / FUN_00356b5c /
 *   FUN_0036b270 / FUN_003515fc / FUN_00365b6c / FUN_0034dba8 /
 *   FUN_000839d8.
 */
void sk_sched_key_stage2(void)
{
    FUN_003530e8();
    FUN_00352ddc();
    FUN_00310d34();
    FUN_00356b5c();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_003515fc();
    uint64_t u = FUN_00365b6c();
    FUN_0034dba8(u, (uint32_t)u ^ 1);
    FUN_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8690 @ 0x001a8690   (est. sk_sched_key_derive)
 * Ghidra: void FUN_001a8690(void)
 * Derives the scheduler key under the lock sequence: allocates key pages,
 * runs the derivation, and dispatches through the saved handler. Ends with
 * the thread epilogue.
 * Confidence: low (indirect dispatch, inlined)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00365b6c, FUN_000839d8,
 *   FUN_0008e500.
 */
void sk_sched_key_derive(void)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_00359de8();
    FUN_003516cc();
    FUN_00310d68();
    FUN_00348e00();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034924c();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348f50();
    FUN_003508e4();
    FUN_00310d34();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_0035992c();
    FUN_003518a0();
    int ok = FUN_00365b6c();
    if (ok == 0) {
        FUN_0034bd00();
        x8_00_fn();
    } else {
        FUN_0034bc94();
        FUN_000839d8();
        fn2 = *(code_fn **)(x16 + 0x20);
        FUN_0034dfc4();
        fn2();
        FUN_003508c0();
        fn2();
    }
    reg16 v = FUN_00359920();
    sk_thread_epilogue(v.lo, v.hi, is_48);  /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a87d8 @ 0x001a87d8   (est. sk_sched_queue_node_link)
 * Ghidra: void FUN_001a87d8(long param_1, undefined8 param_2, undefined8 param_3)
 * Links a run-queue node: stores the two payload words and dispatches through
 * the saved handler slot (jumptable at 0x001a8824).
 * Confidence: low (jumptable not recoverable)
 * Notes: FUN_00319a4c / FUN_00350bcc / indirect via x16+0x10.
 */
void sk_sched_queue_node_link(long node, uint64_t a, uint64_t b)
{
    *(uint64_t *)(node + 0x18) = a;
    *(uint64_t *)(node + 0x20) = b;
    FUN_00319a4c(node);
    FUN_00350bcc();
    (**(code_fn **)(x16 + 0x10))();         /* jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_001a8850 @ 0x001a8850   (est. sk_sched_key_prepare_a)
 * Ghidra: void FUN_001a8850(void)
 * Prepares the scheduler key: runs the meta helper then key stage1.
 * Confidence: medium
 * Notes: FUN_00359350 / FUN_001a8368.
 */
void sk_sched_key_prepare_a(void)
{
    FUN_00359350();
    FUN_001a8368();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8868 @ 0x001a8868   (est. sk_sched_key_prepare_b)
 * Ghidra: void FUN_001a8868(void)
 * Prepares the scheduler key: runs the meta helper then the key round.
 * Confidence: medium
 * Notes: FUN_00359350 / FUN_001a8498.
 */
void sk_sched_key_prepare_b(void)
{
    FUN_00359350();
    FUN_001a8498();
}

/*--------------------------------------------------------------------*/
/* FUN_001a88b4 @ 0x001a88b4   (est. sk_sched_queue_grow_cap)
 * Ghidra: void FUN_001a88b4(void)
 * Grows the run queue to fit unaff_x19 elements: resolves the element type,
 * allocates the new backing storage with the computed capacity, and updates
 * the budget. On an empty queue it takes the retain/append path.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00350c5c / FUN_001a894c / FUN_003549d8 / FUN_0036a940 /
 *   FUN_001a0534 / FUN_0009461c / FUN_001a0414.
 */
void sk_sched_queue_grow_cap(void)
{
    long n = FUN_00350c5c();
    if (0 < n) {
        FUN_001a894c();
        uint64_t u2 = FUN_003549d8(*(uint64_t *)(x20 - 8));
        uint64_t off = (uint64_t)*(uint8_t *)(x16 + 0x50);
        sk_alloc_special(u2, (off + x10 & (off ^ 0xffffffffffffffff))
                          + *(long *)(x8 + 0x48) * x19, off | x11);  /* FUN_0036a940 */
        FUN_001a0534();
        return;
    }
    FUN_0009461c();
    FUN_001a0414();
}

/*--------------------------------------------------------------------*/
/* FUN_001a894c @ 0x001a894c   (est. sk_sched_elem_type)
 * Ghidra: void FUN_001a894c(undefined8 param_1, undefined8 param_2)
 * Resolves the element type descriptor for the run queue, returning either
 * the direct metatype or a lazily-initialized type.
 * Confidence: medium
 * Notes: FUN_003198cc / FUN_00002534 / FUN_0031d798.
 */
void sk_sched_elem_type(uint64_t p1, uint64_t p2)
{
    long v = FUN_003198cc(p2);
    if (v != 0) {
        FUN_00002534((void*)0x0064e838, (void*)0x004c0690);
        return;
    }
    FUN_0031d798(0, p2);
}

/*--------------------------------------------------------------------*/
/* FUN_001a89a8 @ 0x001a89a8   (est. swift_small_string_encode)
 * Ghidra: ulong FUN_001a89a8(undefined8 param_1, ulong param_2, uint param_3)
 * Encodes a small Swift string into its inline 11-byte representation:
 * validates the count, packs the bytes into the discriminator, and sets the
 * inline-flag/tag bits. Fatals on malformed input.
 * Confidence: high (Swift small-string encoding with 0xc000... tag and
 *   0x1000000000000000 inline flag)
 * Notes: FUN_0011e71c / FUN_00358768 / FUN_0034da18 / FUN_00354b38;
 *   fatal FUN_001afe4c.
 */
uint64_t swift_small_string_encode(uint64_t p1, uint64_t count, uint32_t flags)
{
    if ((long)count < 0) {
        FUN_0034846c();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
    if (count == 0) return FUN_0011e71c();
    bool is_large = 0xe < count;
    if (count < 0x10) {
        FUN_00358768();
        uint64_t v5 = x1;
        if (is_large) v5 = x10;
        uint64_t v6 = x1;
        if (v5 - 1 <= x1) v6 = v5 - 1;
        if (v5 == v6) goto encode_fatal;
        uint64_t acc = 0;
        uint64_t i = 0;
        uint8_t *p = x8;
        do {
            acc = (uint64_t)*p << (i & 0x3f) | acc;
            i += 8;
            p++;
        } while (v5 * 8 - i != 0);
        bool ok = (x1 == 9);
        if (8 < x1) {
            ok = (x9 == x1 - 9);
            if (x9 <= x1 - 9) goto encode_fatal;
            FUN_0034da18(acc);
            do {
                FUN_0034b918();
            } while (!ok);
        }
        FUN_0034ec0c();
        uint64_t tag = 0xe000000000000000;
        if (!ok) tag = x8_00;
        return FUN_00354b38(tag);
    }
    uint64_t v5 = count | 0xc000000000000000;
    if ((flags & 1) == 0) v5 = count;
    return v5 | 0x1000000000000000;
encode_fatal:
    FUN_00348034();
    FUN_003504b8();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a8a8c @ 0x001a8a8c   (est. sk_sched_queue_reserve2x)
 * Ghidra: void FUN_001a8a8c(long param_1, long param_2)
 * Doubles the run-queue reservation: validates the count is non-negative and
 * the doubled size doesn't overflow, then allocates via FUN_0006e778.
 * Confidence: medium
 * Notes: traps at 0x1a8abc / 0x1a8ac0; FUN_0006e778.
 */
void sk_sched_queue_reserve2x(long base, long count)
{
    if (count + 0x4000000000000000 < 0) __builtin_trap();  /* 0x1a8abc */
    if (!SCARRY8(base, count * 2)) {
        FUN_0006e778(base + count * 2);
        return;
    }
    __builtin_trap();                       /* 0x1a8ac0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a8ac0 @ 0x001a8ac0   (est. sk_sched_queue_meta_dispatch)
 * Ghidra: void FUN_001a8ac0(void)
 * Dispatches the queue metadata: resolves the descriptor and jumps through
 * the saved handler.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034e004 / FUN_003194f8 / FUN_003548c4 / FUN_00352920.
 */
void sk_sched_queue_meta_dispatch(void)
{
    FUN_0034e004();
    uint64_t u = FUN_003194f8();
    FUN_003548c4(u, u, 0x6756a8, 0x66e1b8);
    FUN_00352920();
    x8_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8b20 @ 0x001a8b20   (est. sk_sched_queue_swap)
 * Ghidra: void FUN_001a8b20(void)
 * Swaps the run-queue head: reads the current head element, and either frees
 * it and installs the new head, or yields and runs the full rebuild path.
 * Confidence: low (indirect, unaff regs)
 * Notes: FUN_0034c034 / FUN_003598a0 / FUN_003a25d4 / FUN_00084180 /
 *   FUN_00267820; thunk_FUN_0036b270.
 */
void sk_sched_queue_swap(void)
{
    uint64_t *head = (uint64_t *)FUN_0034c034();
    uint64_t u1 = head[1];
    FUN_003598a0(*head);
    if ((x9 == 0) && (((x8 & (u1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        thunk_FUN_0036b270();
        FUN_003a25d4(u1);
        *x20 = x21;
        x20[1] = x19;
    } else {
        FUN_00084180();                     /* yield */
        FUN_00267820();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a8b7c @ 0x001a8b7c   (est. sk_sched_queue_touch_thunk)
 * Ghidra: void FUN_001a8b7c(void)
 * Thunk: touches the queue via the shared helper.
 * Confidence: medium
 * Notes: FUN_00355270.
 */
void sk_sched_queue_touch(void) { FUN_00355270(); }

/*--------------------------------------------------------------------*/
/* FUN_001a8b9c @ 0x001a8b9c   (est. sk_sched_runqueue_advance)
 * Ghidra: void FUN_001a8b9c(...)
 * Advances the run queue by one element with full accounting: computes the
 * remaining budget, dispatches through FUN_001a1138 (requeue), and re-arms
 * the queue. Traps on budget underflow.
 * Confidence: low (heavy inlining, indirect dispatch)
 * Notes: FUN_0008e518, FUN_00027754, FUN_001a8cf0, DAT_00658c00,
 *   FUN_001a1138, FUN_0036b118, FUN_0008e500; traps at 0x1a8ce4-0x1a8cf0.
 */
void sk_sched_runqueue_advance(uint64_t p1, uint64_t p2, uint64_t p3, long p4,
                               uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    long cur = cpu.lo;
    long used = cpu.hi - cur;
    if (SBORROW8(cpu.hi, cur)) __builtin_trap();        /* 0x1a8ce4 */
    long budget = p4 - used;
    if (SBORROW8(p4, used)) __builtin_trap();           /* 0x1a8ce8 */
    FUN_00027754(p7);
    FUN_00352ee4();
    FUN_00027788();
    FUN_003505d0();
    long v5 = x8_00_fn();
    long total = v5 + budget;
    if (SCARRY8(v5, budget)) __builtin_trap();          /* 0x1a8cec */
    FUN_00351e3c(total, total);
    uint64_t u6 = FUN_001a8cf0();
    sv_8 = u6;
    FUN_0035156c();
    FUN_0035145c(&sv_10);
    uint64_t u7 = x9_fn();
    if (!SBORROW8(cur, sv_10)) {
        dispatch_slot(u7, cur - sv_10);              /* DAT_00658c00 */
        sv_40 = p5;
        us_38 = p6;
        sv_30 = p7;
        us_28 = p8;
        sv_20 = p3;
        FUN_001a1138(&sv_8, x1, p4, (void*)0x00319528, aus_50, p5, p7);
        sk_free((void *)u6);                                    /* FUN_0036b118 */
        FUN_0034b3e8();
        (**(code_fn **)(x16 + 8))(p3, p6);
        sk_thread_epilogue(x8);                         /* FUN_0008e500 */
        return;
    }
    __builtin_trap();                       /* 0x1a8cf0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a8cf0 @ 0x001a8cf0   (est. sk_sched_queue_node_alloc)
 * Ghidra: void FUN_001a8cf0(void)
 * Allocates a run-queue node via FUN_001a9064.
 * Confidence: medium
 * Notes: FUN_00355684 / FUN_001a9064.
 */
void sk_sched_queue_node_alloc(void)
{
    FUN_00355684();
    FUN_001a9064();
}

/*--------------------------------------------------------------------*/
/* FUN_001a8d0c @ 0x001a8d0c   (est. swift_range_copy_elements)
 * Ghidra: void FUN_001a8d0c(...)
 * Copies a range of elements from a Swift RangeReplaceableCollection: walks
 * each element with the type's element-move vtable, validating the range
 * bounds. Fatals on invalid range/index.
 * Confidence: high (string-matched fatal "Range requires lowerBound <= upp" +
 *   "Index out of range")
 * Notes: FUN_00377824, DAT_00658c00 dispatch, FUN_000277b8/e8/18,
 *   FUN_0019dd10; strings at 0x005cda00 / 0x005cda30 / 0x005cd940.
 */
void swift_range_copy_elements(long dst, long count, uint64_t p3, uint64_t p4,
                               uint64_t p5, uint64_t p6, uint64_t p7)
{
    FUN_00027754(p6);
    FUN_00027754();
    uint64_t u3 = FUN_00027754();
    long d1 = FUN_00377824(0, u3, p4, (void*)0x00611b24, (void*)0x00611b34);
    long t1 = *(long *)(d1 - 8);
    dispatch_slot(*(long *)(t1 + 0x40) + 0xf & 0xfffffffffffffff0); /* DAT_00658c00 */
    long base = (long)&sv_b0 - x8;
    long d2 = FUN_00377824(0, p7, p5, (void*)0x0060e208, (void*)0x0060e230);
    long t2 = *(long *)(d2 - 8);
    dispatch_slot(*(long *)(t2 + 0x40) + 0xf & 0xfffffffffffffff0); /* DAT_00658c00 */
    long nbytes = ((long)&sv_b0 - x8) - x8_00;
    fn5 = (code_fn *)FUN_000277b8(p7);
    fn5(nbytes, p5, p7);
    if (count < 0) {
        *(uint32_t *)(nbytes - 0x10) = 1;
        *(uint64_t *)(nbytes - 0x18) = 0x2f9;
        *(uint8_t *)(nbytes - 0x20) = 2;
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    if (count != 0) {
        long slot = t1 + 0x10;
        do {
            if (count == 0) {
                *(uint32_t *)(nbytes - 0x10) = 1;
                *(uint64_t *)(nbytes - 0x18) = 0x136;
                *(uint8_t *)(nbytes - 0x20) = 2;
                sk_swift_fatal(s_Fatal_error, 0xb, 2, s_index_out_of_range, 0x12, 2,
                               s_swift_array, 0x11, 2, 0x136, 1);
            }
            fn5b = (code_fn *)FUN_000277e8(p7);
            reg16 v = fn5b(stack, nbytes, p5, p7);
            long d1c = d1;
            long basec = base;
            sv_b0 = p3;
            sv_a8 = t2;
            us_a0 = p5;
            (**(code_fn **)(t1 + 0x10))(base, v.hi, d1);
            (*v.lo)(stack, stack, 0);
            p5 = us_a0;
            t2 = sv_a8;
            p3 = sv_b0;
            (**(code_fn **)(t1 + 0x20))(dst, basec, d1c);
            fn5c = (code_fn *)FUN_00027818(p7);
            fn5c(nbytes, p5, p7);
            dst += *(long *)(t1 + 0x48);
            count--;
        } while (count != 0);
    }
    FUN_0019dd10(p3, nbytes, p5, p7);
    (**(code_fn **)(t2 + 8))(nbytes, d2);
}

/*--------------------------------------------------------------------*/
/* FUN_001a9064 @ 0x001a9064   (est. sk_sched_queue_enqueue_core)
 * Ghidra: void FUN_001a9064(void)
 * Core run-queue enqueue: saves the CPU context, resolves the queue lock,
 * and enqueues the thread under the lock. Ends with the element helper.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_00084220 (ctx save) / FUN_00084234 (restore), FUN_0031c3d0,
 *   FUN_000b4390, FUN_00027754, FUN_00348b94, FUN_00377824, FUN_0009461c,
 *   FUN_0019c44c; trap at 0x1a9110.
 */
void sk_sched_queue_enqueue_core(void)
{
    FUN_00084220();
    uint64_t u4 = x4;
    FUN_00351a14();
    fn1 = (code_fn *)FUN_0031c3d0(u4);
    FUN_000b4390();
    long a = fn1();
    FUN_000b4390();
    long b = fn1();
    if ((a < x24) && (b + 0x4000000000000000 < 0)) __builtin_trap();  /* 0x1a9110 */
    FUN_00027754(x4);
    FUN_00027754();
    reg16 v = FUN_00348b94();
    v = FUN_00377824(v.lo, v.hi, x3);
    FUN_0009461c(v.lo, v.hi, v.lo);
    FUN_00084234();
    FUN_0019c44c();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9128 @ 0x001a9128   (est. sk_sched_queue_set_len)
 * Ghidra: void FUN_001a9128(undefined8 param_1, long param_2)
 * Sets the run-queue length field.
 * Confidence: medium
 * Notes: *(param_2+0x10) = param_1.
 */
void sk_sched_queue_set_len(uint64_t len, long q)
{
    *(uint64_t *)(q + 0x10) = len;
}

/*--------------------------------------------------------------------*/
/* FUN_001a9130 @ 0x001a9130   (est. sk_sched_queue_push)
 * Ghidra: void FUN_001a9130(...)
 * Pushes an element onto the run queue under irqsave: acquires the lock,
 * allocates a node, links it via FUN_001a1138, and restores flags.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00357cb4 (irqsave) / FUN_00357c74 (restore), FUN_001a8cf0,
 *   FUN_00084180, FUN_001a10e4, FUN_003524d4, FUN_001a1138,
 *   FUN_0036b118.
 */
void sk_sched_queue_push(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_spin_irqsave(&flags);                /* FUN_00357cb4 */
    FUN_0034a958();
    uint64_t u1 = FUN_00310f64();
    FUN_0034b778(u1);
    long v = x8_fn();
    if (v == 0) {
        FUN_0034b358();
        v = FUN_001a8cf0();
        is_8 = v;
        FUN_00084180();                     /* yield */
        reg16 node = FUN_001a10e4();
        FUN_003524d4(&stack_8, node.hi, p3, node.lo);
        FUN_001a1138();
        sk_free((void *)node.hi);                   /* FUN_0036b118 */
    }
    sk_irqrestore(v, x30);                  /* FUN_00357c74 */
    sk_free(NULL);                          /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a91c4 @ 0x001a91c4   (est. sk_sched_runqueue_walk_advance)
 * Ghidra: void FUN_001a91c4(...)
 * Walks and advances the run queue, appending elements one at a time through
 * the full lock/accounting sequence. Ends on a done flag or the thread
 * epilogue.
 * Confidence: low (very heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, FUN_00027754, DAT_00658c00, FUN_00377824,
 *   FUN_00377bec, FUN_001a10d4, FUN_001a10e4, FUN_001a1138,
 *   FUN_0036b118, FUN_0008e500; trap at 0x1a95d0.
 */
void sk_sched_runqueue_walk_advance(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, long p5)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_00027754(p4);
    FUN_00352894();
    FUN_00350bd8();
    FUN_00354b20();
    FUN_00350974();
    FUN_00377824();                         /* lock */
    FUN_00348d64();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b708();
    FUN_00350500();
    uint64_t u2 = FUN_00310d68();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348a34();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a9c0();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034c2c8();
    reg16 v = FUN_00350488();
    FUN_00377824(v.lo, v.hi, p3);
    FUN_00348cd0();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aee4();
    FUN_00353efc();
    long l3 = x8_00_fn(x1);
    FUN_003506b0();
    FUN_000b4390(p3);
    x9_fn();
    FUN_0034b278();
    FUN_00100efc();
    uint64_t u4 = FUN_00377bec();
    FUN_000a68f4();
    FUN_00351f7c();
    x9_00_fn();
    fn7 = *(code_fn **)(x16_00 + 0x10);
    uint64_t u10 = (uint64_t)(x16_00 + 0x10) & 0xffffffffffff | 0xe3ba000000000000;
    uint64_t v5 = p3;
    for (;;) {
        v = FUN_003507e0();
        fn7(u10, v.lo, v.hi, u2);
        v = FUN_00351330();
        FUN_0035681c(v.lo, v.hi, x23);
        fn8 = *(code_fn **)(x16_00 + 8);
        FUN_003508fc();
        x9_01_fn();
        if ((int)v5 == 1) {
            FUN_00351130();
            fn8();
            FUN_00354afc();
            x8_06_fn(p3, x27);
            sk_thread_epilogue();           /* FUN_0008e500 */
            return;
        }
        bool done = (l3 + 1 == 0);
        if (SCARRY8(l3, 1)) __builtin_trap();        /* 0x1a95d0 */
        v5 = FUN_001a10d4(l3, l3 + 1, x1, p4);
        sv_10[0] = v5;
        FUN_003510ac();
        FUN_001a10e4();
        FUN_0035a5cc();
        FUN_001a1138(sv_10, l3, 0);
        sk_free((void *)p5);                        /* FUN_0036b118 */
        sk_free((void *)v5);                        /* FUN_0036b118 */
        FUN_0031c3d0(p4);
        v5 = FUN_00350a88();
        long l6 = x8_01_fn(v5, p4);
        FUN_00310b68(p4);
        v5 = FUN_00350a88();
        p5 = x8_02_fn(v5, p4);
        for (;;) {
            v = FUN_003509d4();
            fn7(u10, v.lo, v.hi, u2);
            FUN_0034b2a8(x28);
            if (done) break;
            fn9 = *(code_fn **)(x16 + 0x20);
            v = FUN_00350944();
            fn9(v.lo, v.hi, x23);
            done = (l3 == l6);
            if (l6 <= l3) {
                FUN_00355224();
                FUN_00350a70();
                x8_04_fn();
                goto walk_advance_done;
            }
            FUN_003508fc(fn8);
            x8_03_fn();
            fn9(p5 + *(long *)(x16 + 0x48) * l3, sv_48, x23);
            l3++;
            x9_00_fn(x1, x27, u4);
        }
        FUN_00350ab8();
        fn8();
walk_advance_done:
        FUN_00319568(p4);
        v5 = FUN_0035066c();
        x8_05_fn(v5, x1, p4);
        v5 = x20;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a95d0 @ 0x001a95d0   (est. sk_sched_queue_alloc_pages)
 * Ghidra: void FUN_001a95d0(void)
 * Allocates queue backing pages: runs the two alloc helpers.
 * Confidence: medium
 * Notes: FUN_0034b85c / FUN_0036b270 / FUN_0034b788.
 */
void sk_sched_queue_alloc_pages(void)
{
    FUN_0034b85c();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_0034b788();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9600 @ 0x001a9600   (est. sk_sched_queue_reset)
 * Ghidra: void FUN_001a9600(void)
 * Resets the run-queue state: frees the old backing storage and installs the
 * fresh element pointers from registers.
 * Confidence: medium
 * Notes: FUN_00349a18 / FUN_0036b118; unaff_x19..x23 = new element words.
 */
void sk_sched_queue_reset(void)
{
    FUN_00349a18();
    sk_free((void *)*x20);                          /* FUN_0036b118 */
    *x20 = x23;
    x20[1] = x22;
    x20[2] = x21;
    x20[3] = x19;
}

/*--------------------------------------------------------------------*/
/* FUN_001a9640 @ 0x001a9640   (est. swift_array_reserve_zero)
 * Ghidra: void FUN_001a9640(undefined8 param_1, undefined8 param_2)
 * Reserves a zero-filled array: forwards to FUN_001a964c with a zero flag.
 * Confidence: medium
 */
void swift_array_reserve_zero(uint64_t a, uint64_t b) { FUN_001a964c(a, 0, b); }

/*--------------------------------------------------------------------*/
/* FUN_001a964c @ 0x001a964c   (est. swift_array_reserve_core)
 * Ghidra: void FUN_001a964c(void)
 * Core Swift Array reserve: validates the count range, allocates the backing
 * storage, resolves the element metatype, and completes the reserve. Traps
 * on count overflow.
 * Confidence: medium
 * Notes: FUN_00357ca0 / FUN_0034f414 / FUN_0036b270 / FUN_00376820 /
 *   FUN_0019c03c / FUN_0036b118 / FUN_003513fc / FUN_001e5438 /
 *   FUN_00357c44; traps at 0x1a96fc / 0x1a9700.
 */
void swift_array_reserve_core(void)
{
    FUN_00357ca0();
    if (SBORROW8(0, x1)) __builtin_trap();  /* 0x1a96fc */
    FUN_0034f414();
    sk_alloc_pages(0, 0);                   /* FUN_0036b270 */
    FUN_00350488();
    uint64_t u2 = FUN_00310dd8();
    uint64_t u3 = FUN_003498dc();
    sk_metatype(u3, u2);                    /* FUN_00376820 */
    FUN_00357ab4();
    FUN_0019c03c(u2);
    if (!SCARRY8(x19, *(long *)(x21 + 0x10))) {
        if (x19 <= x19 + *(long *)(x21 + 0x10)) {
            sk_free(NULL);                  /* FUN_0036b118 */
            FUN_003513fc();
            FUN_001e5438();
            FUN_00357c44();
            return;
        }
        FUN_00347d60();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
    __builtin_trap();                       /* 0x1a9700 */
}

/*--------------------------------------------------------------------*/
/* FUN_001a9714 @ 0x001a9714   (est. swift_array_capacity_fit)
 * Ghidra: long FUN_001a9714(...)
 * Computes the number of elements that fit in the array's remaining capacity,
 * merging the existing tail when the storage is uniquely referenced.
 * Confidence: medium
 * Notes: traps at 0x1a97d0 / 0x1a97d4; FUN_003534d4 / FUN_002dc564 /
 *   FUN_0035362c / FUN_0036b118.
 */
long swift_array_capacity_fit(uint64_t p1, uint64_t p2, long need, uint64_t cap)
{
    long room = (cap >> 1) - need;
    if (SBORROW8(cap >> 1, need)) __builtin_trap();     /* 0x1a97d0 */
    if ((cap & 1) != 0) {
        FUN_003534d4();
        FUN_002dc564();
        long cur = FUN_0035362c();
        long n = *(long *)(cur + 0x10);
        long stride = *(long *)(x8 + 0x48);
        if (x22 + stride * x20 + stride * room ==
            cur + ((uint64_t)*(uint8_t *)(x16 + 0x50) + 0x20 &
                   ((uint64_t)*(uint8_t *)(x16 + 0x50) ^ 0xffffffffffffffff)) + stride * n) {
            uint64_t c2 = *(uint64_t *)(cur + 0x18);
            sk_free(NULL);                  /* FUN_0036b118 */
            long extra = (c2 >> 1) - n;
            bool carry = SCARRY8(room, extra);
            room += extra;
            if (carry) __builtin_trap();    /* 0x1a97d4 */
        } else {
            sk_free(NULL);                  /* FUN_0036b118 */
        }
    }
    return room;
}

/*--------------------------------------------------------------------*/
/* FUN_001a97d4 @ 0x001a97d4   (est. swift_array_reserve_meta)
 * Ghidra: void FUN_001a97d4(void)
 * Reserves array storage using the element metatype: resolves the type,
 * allocates, and stores the 4-word structure.
 * Confidence: low (indirect, unaff regs)
 * Notes: FUN_0035a040 / FUN_00319598 / FUN_0008f5f4 / FUN_0034ad60 /
 *   FUN_00376820 / FUN_00359810 / FUN_0019c078.
 */
void swift_array_reserve_meta(void)
{
    FUN_0035a040();
    uint64_t u1 = FUN_00319598();
    uint32_t ok = FUN_0008f5f4();
    if ((ok & 1) == 0) {
        uint32_t u3 = FUN_0034ad60();
        uint64_t u4 = sk_metatype(u3, u1);  /* FUN_00376820 */
        u3 = FUN_00359810((int32_t)u4, x1, u4);
        FUN_0019c078(u3, u1);
        x20[1] = us_38;
        *x20 = sv_40;
        x20[3] = us_28;
        x20[2] = us_30;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a983c @ 0x001a983c   (est. swift_array_index_check)
 * Ghidra: void FUN_001a983c(long param_1, ..., long param_4, ulong param_5)
 * Validates an array index: fatals if param_1 is outside [param_4, param_5>>1).
 * Confidence: medium
 * Notes: fatal FUN_001afe4c.
 */
void swift_array_index_check(long idx, uint64_t p2, uint64_t p3, long lo, uint64_t cap)
{
    if (idx < lo || (long)(cap >> 1) <= idx) {
        FUN_003488bc(1);
        FUN_00352974();
        FUN_00349b50();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001a9884 @ 0x001a9884   (est. swift_array_index_check_thunk)
 * Ghidra: void FUN_001a9884(void)
 * Thunk: index-check wrapper.
 * Confidence: medium
 * Notes: FUN_00356358 / FUN_001a983c.
 */
void swift_array_index_check_thunk(void)
{
    FUN_00356358();
    FUN_001a983c();
}

/*--------------------------------------------------------------------*/
/* FUN_001a989c @ 0x001a989c   (est. swift_array_index_check2)
 * Ghidra: void FUN_001a989c(...)
 * Index-check variant: fatals if idx >= cap>>1 or idx < lo.
 * Confidence: medium
 * Notes: fatal FUN_001afe4c.
 */
void swift_array_index_check2(long idx, uint64_t p2, uint64_t p3, long lo, uint64_t cap)
{
    if ((long)(cap >> 1) < idx) {
        FUN_003488bc(1);
        FUN_0034baf0();
    } else {
        if (lo <= idx) return;
        FUN_003488bc(1);
        FUN_0034baf0();
    }
    FUN_0035110c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a993c @ 0x001a993c   (est. swift_array_elem_get)
 * Ghidra: void FUN_001a993c(...)
 * Returns the element at index param_2 of the array: dispatches through the
 * type's element-get vtable slot.
 * Confidence: medium
 * Notes: jumptable at 0x001a9968; indirect via *(desc+0x10).
 */
void swift_array_elem_get(uint64_t p1, long idx, uint64_t p3, long base, uint64_t p5,
                          uint64_t p6, long desc)
{
    (**(code_fn **)(*(long *)(desc - 8) + 0x10))
        (p1, base + *(long *)(*(long *)(desc - 8) + 0x48) * idx, desc);
}

/*--------------------------------------------------------------------*/
/* FUN_001a99c8 @ 0x001a99c8   (est. swift_array_iterator_init)
 * Ghidra: void FUN_001a99c8(...)
 * Initializes an array iterator: resolves the element type, builds the
 * iterator state via FUN_001a9a30, and stores the type + tag into the output.
 * Confidence: medium
 * Notes: FUN_00319598 / FUN_001a9a30; tag 0x66fa18.
 */
void swift_array_iterator_init(reg16 *out, uint64_t p2, long p3)
{
    uint64_t u3 = *(uint64_t *)(p3 + 0x10);
    uint64_t u1 = FUN_00319598(0, u3);
    uint64_t tag = 0x66fa18;
    reg16 v = FUN_001a9a30(p2, u3);
    *out = v;
    *(uint64_t *)out[1] = u1;
    *(uint64_t *)(out[1] + 8) = tag;
}

/*--------------------------------------------------------------------*/
/* FUN_001a9a30 @ 0x001a9a30   (est. swift_array_iterator_alloc)
 * Ghidra: void FUN_001a9a30(void)
 * Allocates an array iterator: runs the type/lock sequence and reserves the
 * backing buffer.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_0034b470 / FUN_00355cbc / FUN_00310da8 / FUN_0034bcf0 /
 *   FUN_001a9640.
 */
void swift_array_iterator_alloc(void)
{
    FUN_0034b470();
    FUN_00355cbc();
    FUN_00310da8();
    FUN_0034bcf0();
    x8_fn();
    FUN_001a9640();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9a84 @ 0x001a9a84   (est. swift_range_advance)
 * Ghidra: long FUN_001a9a84(long param_1, ulong param_2, long param_3)
 * Advances a Swift Range: computes the offset from the bounds, validates it
 * fits, and returns the new position. Traps on overflow.
 * Confidence: medium
 * Notes: traps at 0x1a9ac4 / 0x1a9ac8; FUN_00068e14.
 */
long swift_range_advance(long lo, uint64_t step, long hi)
{
    uint64_t span = hi - lo;
    if (SBORROW8(hi, lo)) __builtin_trap();          /* 0x1a9ac4 */
    if ((long)step < 1) {
        if (0 < (long)span || (long)span <= (long)step) goto oob;
    } else if (((long)span < 0) || (step <= span)) {
oob:
        if (!SCARRY8(lo, step)) return lo + step;
        __builtin_trap();                            /* 0x1a9ac8 */
    }
    return FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9ac8 @ 0x001a9ac8   (est. swift_array_index_dispatch)
 * Ghidra: void FUN_001a9ac8(void)
 * Validates and dispatches an array index through the element-get vtable.
 * Confidence: low (jumptable at 0x001a9b24)
 * Notes: FUN_003515f0 / FUN_001a983c / FUN_00350bcc.
 */
void swift_array_index_dispatch(void)
{
    FUN_003515f0();
    FUN_001a983c();
    FUN_00350bcc();
    (**(code_fn **)(x16 + 0x10))();         /* jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_001a9b28 @ 0x001a9b28   (est. swift_array_slice_elem)
 * Ghidra: undefined1 [16] FUN_001a9b28(void)
 * Returns a slice/iterator over the array: reserves storage and computes the
 * element pointer from the stride and index.
 * Confidence: medium
 * Notes: FUN_0034a958 / FUN_001a97d4 / FUN_0035a858 / FUN_003597d8;
 *   vtable FUN_0001a1c8.
 */
reg16 swift_array_slice_elem(void)
{
    FUN_0034a958();
    FUN_001a97d4();
    FUN_0035a858();
    FUN_003597d8();
    return (reg16){ FUN_0001a1c8, x23 + *(long *)(x16 + 0x48) * x21 };
}

/*--------------------------------------------------------------------*/
/* FUN_001a9b8c @ 0x001a9b8c   (est. swift_array_slice_dispatch)
 * Ghidra: void FUN_001a9b8c(void)
 * Reserves array storage then dispatches through the saved element handler
 * (jumptable at 0x001a9bec).
 * Confidence: low (jumptable)
 * Notes: FUN_0034a958 / FUN_001a97d4 / FUN_0035a858 / FUN_00350bcc.
 */
void swift_array_slice_dispatch(void)
{
    FUN_0034a958();
    FUN_001a97d4();
    FUN_0035a858();
    FUN_00350bcc();
    (**(code_fn **)(x16 + 0x28))(x23 + *(long *)(x16 + 0x48) * x21);  /* jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_001a9bf0 @ 0x001a9bf0   (est. swift_array_replace_range)
 * Ghidra: void FUN_001a9bf0(void)
 * Replaces a range of the array: saves the CPU context, validates the bounds,
 * and performs the replacement via FUN_001a9c54.
 * Confidence: medium
 * Notes: FUN_00084220/34 (ctx save/restore), FUN_001a989c (index check),
 *   FUN_001a9c54.
 */
void swift_array_replace_range(void)
{
    FUN_00084220();
    FUN_00356188();
    FUN_0034b5a8();
    FUN_00356358();
    FUN_001a989c();
    FUN_001a989c();
    FUN_0034e55c();
    FUN_00084234();
    FUN_001a9c54();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9c54 @ 0x001a9c54   (est. swift_array_replace_core)
 * Ghidra: void FUN_001a9c54(...)
 * Core array-range replacement: forwards to the shared replace helper and
 * reallocates the backing storage.
 * Confidence: medium
 * Notes: FUN_001e5438 / FUN_00350b90 / FUN_0035a4c8 / FUN_0036b270 /
 *   FUN_0034c444.
 */
void swift_array_replace_core(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                              uint64_t p5, uint32_t p6)
{
    FUN_001e5438(p3, p4, p1, p2, p6 & 1);
    FUN_00350b90();
    FUN_0035a4c8();
    sk_alloc_pages(p3, 0);                  /* FUN_0036b270 */
    FUN_0034c444();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9cb8 @ 0x001a9cb8   (est. swift_array_assign_range)
 * Ghidra: void FUN_001a9cb8(...)
 * Assigns a range into the array: validates bounds, and either updates in
 * place or reallocates via FUN_001a9dd8. Ends with the thread epilogue.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_000b4594 / FUN_003542e8 / FUN_001a989c / FUN_001a9bf0 /
 *   FUN_001a9dd8 / FUN_00376820 / FUN_000b45b0; fatal FUN_001afe4c.
 */
void swift_array_assign_range(uint64_t p1, uint64_t p2, long p3, uint64_t p4,
                              uint64_t p5, uint64_t p6, uint64_t p7)
{
    FUN_000b4594();
    reg16 v = FUN_003542e8();
    long q = *x20;
    FUN_001a989c(p5);
    FUN_001a989c();
    FUN_00100efc();
    FUN_00353bc4();
    FUN_001a9bf0();
    FUN_003597c0();
    long stride = *(long *)(x16 + 0x48);
    sk_free(NULL);                          /* FUN_0036b118 */
    if (x1 + stride * q == v.hi + stride * p3) {
        if ((long)(p4 >> 1) < p3) {
            FUN_00347d60();
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        if (x22 == p3 && x21 == p4 >> 1) {
            FUN_000b45b0(v.lo, x30);
            sk_free(NULL);                  /* FUN_0036b118 */
            return;
        }
    }
    is_40 = p3;
    is_48 = p4;
    is_30 = v;
    uint64_t u1 = FUN_00348d00();
    v = sk_metatype(u1, p7);                /* FUN_00376820 */
    FUN_00100efc(v.lo, v.hi, &stack_30);
    FUN_001a9dd8();
    FUN_000b45b0(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001a9dd8 @ 0x001a9dd8   (est. swift_array_replace_realloc)
 * Ghidra: void FUN_001a9dd8(void)
 * Reallocates an array during a range replacement: computes the new capacity,
 * validates the range, and either grows in place or reallocates via
 * FUN_001a8b9c. Fatals on invalid range.
 * Confidence: low (inlined, many traps)
 * Notes: FUN_0035193c / FUN_00027788 / FUN_00319598 / FUN_0008f5f4 /
 *   FUN_001a9714 / FUN_001ad6e0 / FUN_00376820 / FUN_001a8b9c;
 *   traps at 0x1a9f48-0x1a9f54; fatal FUN_001afe4c.
 */
void swift_array_replace_realloc(void)
{
    reg16 v = FUN_0035193c();
    long hi = v.hi;
    long lo = v.lo;
    long n = *(long *)(x20 + 0x10);
    if (lo < n) {
        FUN_003488bc(1);
        FUN_0034baf0();
    } else {
        uint64_t cap = *(uint64_t *)(x20 + 0x18) >> 1;
        if (hi <= (long)cap) {
            if (SBORROW8(cap, n)) __builtin_trap();     /* 0x1a9f48 */
            if (SBORROW8(hi, lo)) __builtin_trap();     /* 0x1a9f4c */
            FUN_00027788(x5);
            FUN_0035075c();
            FUN_003508a8();
            long v3 = x8_fn();
            long rem = v3 - (hi - lo);
            if (SBORROW8(v3, hi - lo)) __builtin_trap();/* 0x1a9f50 */
            FUN_0035113c();
            uint64_t u4 = FUN_00319598();
            uint64_t ok = FUN_0008f5f4();
            if ((ok & 1) != 0) {
                FUN_00357228();
                lo = FUN_001a9714();
                if (SCARRY8(cap - n, rem)) __builtin_trap();  /* 0x1a9f54 */
                if ((long)((cap - n) + rem) <= lo) {
                    FUN_00350618();
                    FUN_00351b2c();
                    FUN_00351774();
                    FUN_001ad6e0();
                    return;
                }
            }
            uint64_t u7 = FUN_0034ad60();
            sk_metatype(u7, u4);            /* FUN_00376820 */
            FUN_0034e55c();
            FUN_00353504();
            FUN_00351774(x30);
            FUN_001a8b9c();
            return;
        }
        FUN_003488bc(1);
        FUN_0034baf0();
    }
    FUN_0035110c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001a9f54 @ 0x001a9f54   (est. swift_array_replace_alloc)
 * Ghidra: void FUN_001a9f54(void)
 * Allocates a replacement array buffer: allocates 0x40 bytes (tag 0x15d5),
 * runs the type/init sequence, and replaces the range.
 * Confidence: medium
 * Notes: FUN_00349a18 / FUN_0036a908(0x40, 0x15d5) / FUN_003501fc /
 *   FUN_00100efc / FUN_001a9bf0 / FUN_00357694 / FUN_00353c54.
 */
void swift_array_replace_alloc(void)
{
    FUN_00349a18();
    sk_alloc(0x40, 0x15d5);                 /* FUN_0036a908 */
    reg16 v = FUN_003501fc();
    FUN_00100efc(v.lo, v.hi, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(x19 + 0x10));
    FUN_001a9bf0();
    FUN_00357694();
    FUN_00353c54();
}

/*--------------------------------------------------------------------*/
/* FUN_001a9fc4 @ 0x001a9fc4   (est. swift_array_replace_dispatch)
 * Ghidra: void FUN_001a9fc4(void)
 * Dispatch wrapper for array-range replacement: saves the CPU context,
 * handles the uniquely-referenced vs shared cases, and runs the replacement.
 * Confidence: medium
 * Notes: FUN_00084220/34, FUN_0034be0c, FUN_0035a3a0, FUN_001a9cb8,
 *   FUN_0036b270, FUN_0036b118, thunk_FUN_00012568.
 */
void swift_array_replace_dispatch(void)
{
    reg16 v = FUN_00084220();
    uint64_t *head = (uint64_t *)*v.lo;
    if ((v.hi & 1) == 0) {
        FUN_0034be0c(*head);
        FUN_0035a3a0();
        FUN_001a9cb8();
    } else {
        sk_alloc_pages(0, 0);               /* FUN_0036b270 */
        FUN_0034be0c();
        FUN_0035a3a0();
        FUN_001a9cb8();
        sk_free((void *)*head);                     /* FUN_0036b118 */
    }
    FUN_00084234(head, x30);
    thunk_FUN_00012568();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa040 @ 0x001aa040   (est. swift_array_remaining)
 * Ghidra: long FUN_001aa040(undefined8 param_1, undefined8 param_2, long param_3, ulong param_4)
 * Returns the number of remaining slots: (cap>>1) - need. Traps on borrow.
 * Confidence: medium
 * Notes: trap at 0x1aa054.
 */
long swift_array_remaining(uint64_t p1, uint64_t p2, long need, uint64_t cap)
{
    if (!SBORROW8(cap >> 1, need)) return (cap >> 1) - need;
    __builtin_trap();                       /* 0x1aa054 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aa054 @ 0x001aa054   (est. swift_array_elem_set)
 * Ghidra: void FUN_001aa054(undefined8 param_1, long *param_2, long param_3)
 * Sets the element at index *param_2 in the array: validates the index,
 * dispatches through the element-set vtable slot, and runs the teardown.
 * Confidence: medium
 * Notes: FUN_001a97d4 / FUN_001a983c / FUN_0001a1c8.
 */
void swift_array_elem_set(uint64_t val, long *idxp, long arr)
{
    long idx = *idxp;
    FUN_001a97d4(arr);
    long v1 = *(long *)(x20 + 8);
    long t = *(long *)(arr + 0x10);
    FUN_001a983c(idx);
    long desc = *(long *)(t - 8);
    (**(code_fn **)(desc + 0x28))(v1 + *(long *)(desc + 0x48) * idx, val, t);
    FUN_0001a1c8();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa0e4 @ 0x001aa0e4   (est. swift_array_iterator_alloc2)
 * Ghidra: undefined * FUN_001aa0e4(long *param_1, undefined8 *param_2, undefined8 param_3)
 * Allocates an array iterator object (0x28 bytes, tag 0xc7af), builds a slice
 * via FUN_001a9b28, and stores the vtable.
 * Confidence: medium
 * Notes: FUN_0036a908(0x28, 0xc7af) / FUN_001a9b28 / DAT_003471a0.
 */
void *swift_array_iterator_alloc2(long *out, uint64_t *p2, uint64_t p3)
{
    long obj = (long)sk_alloc(0x28, 0xc7af);      /* FUN_0036a908 */
    *out = obj;
    uint64_t u = FUN_001a9b28(obj, *p2, p3);
    *(uint64_t *)(obj + 0x20) = u;
    return (void*)0x003471a0;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa174 @ 0x001aa174   (est. swift_array_iterator_build)
 * Ghidra: undefined1 [16] FUN_001aa174(...)
 * Builds an array iterator: allocates the 0x40-byte iterator (tag 0x118b),
 * populates the element/iterator fields, and returns the {vtable, obj} pair.
 * Confidence: medium
 * Notes: FUN_0036a908(0x40, 0x118b) / FUN_001a9bf0 / FUN_001aa200.
 */
reg16 swift_array_iterator_build(long *out, uint64_t *p2, uint64_t p3)
{
    reg16 *obj = (reg16 *)sk_alloc(0x40, 0x118b);  /* FUN_0036a908 */
    *out = (long)obj;
    *(uint64_t **)obj[2] = x20;
    *(uint64_t *)(obj[2] + 8) = p3;
    uint64_t u2 = p2[1];
    *(uint64_t *)obj[3] = *p2;
    *(uint64_t *)(obj[3] + 8) = u2;
    uint64_t u2b = *x20;
    uint64_t u3 = x20[1];
    reg16 v = FUN_001a9bf0();
    *obj = v;
    *(uint64_t *)obj[1] = u2b;
    *(uint64_t *)(obj[1] + 8) = u3;
    return (reg16){ FUN_001aa200, obj };
}

/*--------------------------------------------------------------------*/
/* FUN_001aa200 @ 0x001aa200   (est. swift_array_iterator_dispatch)
 * Ghidra: void FUN_001aa200(void)
 * Dispatch wrapper for the array iterator: handles uniquely-referenced vs
 * shared backing storage then runs the replacement via FUN_001a9cb8.
 * Confidence: medium
 * Notes: FUN_00084220/34, FUN_0034c444, FUN_0035a3a0, FUN_001a9cb8,
 *   FUN_0036b270, FUN_0036b118, thunk_FUN_00012568.
 */
void swift_array_iterator_dispatch(void)
{
    reg16 v = FUN_00084220();
    uint64_t *head = (uint64_t *)*v.lo;
    if ((v.hi & 1) == 0) {
        FUN_0034c444(*head);
        FUN_0035a3a0();
        FUN_001a9cb8();
    } else {
        sk_alloc_pages(0, 0);               /* FUN_0036b270 */
        FUN_0034c444();
        FUN_0035a3a0();
        FUN_001a9cb8();
        sk_free((void *)*head);                     /* FUN_0036b118 */
    }
    FUN_00084234(head, x30);
    thunk_FUN_00012568();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa27c @ 0x001aa27c   (est. swift_collection_apply_meta3)
 * Ghidra: void FUN_001aa27c(...)
 * Resolves the metatype for param_4 (DAT_004e83e4) then dispatches the
 * collection apply.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_0019f1ec.
 */
void swift_collection_apply_meta3(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e83e4, p4);   /* FUN_00376820 */
    FUN_0019f1ec(p1, p2, p3, p4, meta, p5);
}

/*--------------------------------------------------------------------*/
/* FUN_001aa2fc @ 0x001aa2fc   (est. sk_sched_key_prepare_c)
 * Ghidra: void FUN_001aa2fc(void)
 * Prepares the scheduler key stage 3.
 * Confidence: medium
 * Notes: FUN_003580e4 / FUN_001aa318.
 */
void sk_sched_key_prepare_c(void)
{
    FUN_003580e4();
    FUN_001aa318();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa318 @ 0x001aa318   (est. sk_sched_key_stage3_thunk)
 * Ghidra: void FUN_001aa318(void)
 * Thunk: forwards to FUN_001aa330.
 * Confidence: medium
 */
void sk_sched_key_stage3_thunk(void) { FUN_001aa330(); }

/*--------------------------------------------------------------------*/
/* FUN_001aa330 @ 0x001aa330   (est. sk_sched_key_stage3)
 * Ghidra: void FUN_001aa330(...)
 * Third scheduler key stage: reserves storage, runs the derive pipeline, and
 * completes with the epilogue. Traps on borrow.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_0035ace8 / FUN_003586fc / FUN_001a97d4 / FUN_003571a4 /
 *   FUN_00100c38 / FUN_001a26e0 / FUN_00351ea8 / FUN_001ad668 /
 *   FUN_000839d8; trap at 0x1aa430.
 */
void sk_sched_key_stage3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0035ace8();
    code_fn *fn = (code_fn *)FUN_003586fc();
    if (!SBORROW8(x9, x8_00)) {
        FUN_001a97d4(p3);
        FUN_003571a4(*(uint64_t *)(x20 + 8));
        FUN_00100c38();
        reg16 v = FUN_001a26e0();
        FUN_00351ea8(v);
        fn();
        FUN_0034a210();
        if (x21 == 0) {
            FUN_00002534();
            FUN_00348d30();
            FUN_00351118(v);
            FUN_00352c40();
            FUN_001ad668();
            FUN_0034bc94(x8);
            FUN_000839d8();
        } else {
            FUN_00002534();
            FUN_00348d30();
            FUN_00351118(v);
            FUN_00352c40();
            FUN_001ad668();
        }
        FUN_0035a7a4(x30);
        return;
    }
    __builtin_trap();                       /* 0x1aa430 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aa430 @ 0x001aa430   (est. swift_collection_convert)
 * Ghidra: void FUN_001aa430(undefined8 *param_1, undefined8 *param_2)
 * Converts a collection: forwards to FUN_0019e93c and stores the result.
 * Confidence: medium
 * Notes: FUN_0019e93c.
 */
void swift_collection_convert(uint64_t *out, uint64_t *src)
{
    uint64_t v = FUN_0019e93c(*src);
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa45c @ 0x001aa45c   (est. swift_range_advance_thunk)
 * Ghidra: void FUN_001aa45c(void)
 * Thunk: advances a range via FUN_001a9a84.
 * Confidence: medium
 * Notes: FUN_0034c434 / FUN_001a9a84 / FUN_0035272c.
 */
void swift_range_advance_thunk(void)
{
    FUN_0034c434();
    FUN_001a9a84();
    FUN_0035272c();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa490 @ 0x001aa490   (est. swift_collection_convert2)
 * Ghidra: void FUN_001aa490(undefined8 *param_1)
 * Converts via FUN_0019ed3c and stores the result.
 * Confidence: medium
 * Notes: FUN_0019ed3c.
 */
void swift_collection_convert2(uint64_t *out)
{
    uint64_t v = FUN_0019ed3c();
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa4bc @ 0x001aa4bc   (est. swift_array_iterator_alloc3)
 * Ghidra: undefined * FUN_001aa4bc(long *param_1, undefined8 *param_2, long param_3)
 * Allocates an array iterator (0x28 bytes, tag 0xb73a) and builds the slice
 * via FUN_001aa538.
 * Confidence: medium
 * Notes: FUN_0036a908(0x28, 0xb73a) / FUN_001aa538 / DAT_003471a4.
 */
void *swift_array_iterator_alloc3(long *out, uint64_t *p2, long p3)
{
    long obj = (long)sk_alloc(0x28, 0xb73a);      /* FUN_0036a908 */
    *out = obj;
    uint64_t u = FUN_001aa538(obj, *p2, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(p3 + 0x10));
    *(uint64_t *)(obj + 0x20) = u;
    return (void*)0x003471a4;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa538 @ 0x001aa538   (est. swift_array_iterator_core)
 * Ghidra: undefined1 [16] FUN_001aa538(...)
 * Core array-iterator build: records the element type, allocates the iterator
 * storage, and dispatches through FUN_001a9ac8.
 * Confidence: medium
 * Notes: FUN_0036a908(..., 0xb8e7) / FUN_001a9ac8 / DAT_003471a8.
 */
reg16 swift_array_iterator_core(long *out, uint64_t p2, uint64_t p3, uint64_t p4,
                                uint64_t p5, uint64_t p6, long p7)
{
    long t = *(long *)(p7 - 8);
    *out = p7;
    out[1] = t;
    reg16 v = sk_alloc_special(*(uint64_t *)(t + 0x40), 0, 0xb8e7);  /* FUN_0036a908 */
    long obj = v.lo;
    out[2] = obj;
    FUN_001a9ac8(obj, p2, v.hi, p4, p5, p6, p7);
    return (reg16){ (void*)0x003471a8, obj };
}

/*--------------------------------------------------------------------*/
/* FUN_001aa5fc @ 0x001aa5fc   (est. swift_array_iterator_build2)
 * Ghidra: void FUN_001aa5fc(...)
 * Builds an array iterator from the current queue element words.
 * Confidence: medium
 * Notes: FUN_001a9bf0.
 */
void swift_array_iterator_build2(reg16 *out, uint64_t *p2, long p3)
{
    uint64_t u1 = *x20;
    uint64_t u2 = x20[1];
    reg16 v = FUN_001a9bf0(*p2, p2[1], u1, u2, x20[2], x20[3], *(uint64_t *)(p3 + 0x10));
    *out = v;
    *(uint64_t *)out[1] = u1;
    *(uint64_t *)(out[1] + 8) = u2;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa640 @ 0x001aa640   (est. swift_collection_apply_meta4)
 * Ghidra: void FUN_001aa640(...)
 * Resolves the metatype for param_2 (DAT_004e83ac) and dispatches the
 * collection apply.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_0019fa60; tag 0x6720e8.
 */
void swift_collection_apply_meta4(uint64_t p1, uint64_t p2)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e83ac, p2);   /* FUN_00376820 */
    FUN_0019fa60(p1, p2, meta, 0x6720e8);
}

/*--------------------------------------------------------------------*/
/* FUN_001aa6c8 @ 0x001aa6c8   (est. swift_collection_construct_meta)
 * Ghidra: void FUN_001aa6c8(undefined8 param_1)
 * Resolves the metatype for param_1 (DAT_004e8400) and constructs the
 * collection via FUN_001a0194.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_001a0194.
 */
void swift_collection_construct_meta(uint64_t p1)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e8400, p1);   /* FUN_00376820 */
    FUN_001a0194(p1, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_001aa728 @ 0x001aa728   (est. swift_array_init_finalize)
 * Ghidra: void FUN_001aa728(void)
 * Finalizes array initialization: if the array is empty, resolves the element
 * metatype and rebuilds via FUN_001a4554; then re-arms and frees.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00357ca0 / FUN_0034d0d0 / FUN_001ab9e0 / FUN_00376820 /
 *   FUN_001a4554 / FUN_00354924 / FUN_0036b118 / FUN_00357c44.
 */
void swift_array_init_finalize(void)
{
    FUN_00357ca0();
    FUN_0034d0d0();
    long v = FUN_001ab9e0();
    if (v == 0) {
        uint64_t u2 = FUN_00310df0(0, x4);
        uint64_t u3 = FUN_00348d00();
        sk_metatype(u3, u2);                /* FUN_00376820 */
        FUN_001a4554();
    }
    FUN_00354924();
    sk_free(NULL);                          /* FUN_0036b118 */
    FUN_00357c44();
}

/*--------------------------------------------------------------------*/
/* FUN_001aa7a4 @ 0x001aa7a4   (est. swift_array_build_from)
 * Ghidra: undefined8 FUN_001aa7a4(...)
 * Builds a Swift Array from the current element words via FUN_001aa800 and
 * copies the 5-word result into the output.
 * Confidence: medium
 * Notes: FUN_001aa800.
 */
uint64_t swift_array_build_from(uint64_t *out, uint64_t p2, uint64_t p3, long p4)
{
    FUN_001aa800(&sv_50, p2, p3, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(p4 + 0x10));
    out[1] = us_48;
    out[0] = sv_50;
    out[3] = us_38;
    out[2] = us_40;
    out[4] = sv_30;
    return us_28;
}

/*--------------------------------------------------------------------*/
/* FUN_001aa800 @ 0x001aa800   (est. swift_array_build_core)
 * Ghidra: void FUN_001aa800(void)
 * Core Swift Array builder: computes capacity from the input words, fills the
 * element slots, and stores the 6-word array structure. Fatals on insufficient
 * space.
 * Confidence: low (inlined fill loop, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00376820, FUN_0019fd10,
 *   FUN_001a9ac8; traps at 0x1aa99c / 0x1aa998; fatal FUN_001afe4c.
 */
void swift_array_build_core(void)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    long v3 = FUN_003543a0();
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_003493ac();
    FUN_00355d10();
    uint64_t u4 = FUN_00310df0();
    uint64_t u5 = FUN_00348d00();
    sk_metatype(u5, u4);                    /* FUN_00376820 */
    FUN_00358e7c();
    uint64_t u6 = FUN_0019fd10(u4);
    long l8 = 0;
    uint64_t u7 = x4;
    if ((u6 & 1) != 0) goto store_done;
    if (v3 == 0) {
        FUN_00350410();
        FUN_003488bc();
        FUN_0034baf0();
    } else {
        uint64_t u6b = x5 >> 1;
        l8 = u6b - x4;
        if (SBORROW8(u6b, x4)) __builtin_trap();    /* 0x1aa99c */
        if (l8 <= x1) {
            if (x21 == 0) {
                if (x4 != u6b) {
                    uint64_t u9 = x4;
                    do {
                        FUN_003534f8();
                        FUN_00353b40();
                        FUN_001a9ac8();
                        uint64_t next = u9 + 1;
                        if (SCARRY8(u9, 1)) __builtin_trap();  /* 0x1aa998 */
                        reg16 v = FUN_00350a04(*(uint64_t *)(x16 + 0x20));
                        x8_01_fn(v.lo, v.hi, x6);
                        u9++;
                        u7 = u6b;
                    } while (next != u6b);
                }
            } else {
                FUN_00352858(x21 + *(long *)(x16 + 0x48) * x4);
                FUN_0019dadc();
                u7 = u6b;
            }
            goto store_done;
        }
        FUN_00350410();
        FUN_003488bc();
        FUN_00356870();
        FUN_0034baf0();
    }
    FUN_0035110c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
store_done:
    *x8 = x23;
    x8[1] = x21;
    x8[2] = x4;
    x8[3] = x5;
    x8[4] = u7;
    x8[5] = l8;
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aa9e0 @ 0x001aa9e0   (est. swift_array_apply_thunk)
 * Ghidra: void FUN_001aa9e0(...)
 * Thunk: forwards to FUN_001aaa0c with the current element words.
 * Confidence: medium
 */
void swift_array_apply_a(uint64_t p1, uint64_t p2, uint64_t p3, long p4)
{
    FUN_001aaa0c(p1, p2, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(p4 + 0x10), p3);
}

/*--------------------------------------------------------------------*/
/* FUN_001aa9e4 @ 0x001aa9e4   (est. swift_array_apply_thunk)
 * Ghidra: void FUN_001aa9e4(...)
 * Thunk: alias of FUN_001aa9e0.
 * Confidence: medium
 */
void swift_array_apply_b(uint64_t p1, uint64_t p2, uint64_t p3, long p4)
{
    FUN_001aaa0c(p1, p2, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(p4 + 0x10), p3);
}

/*--------------------------------------------------------------------*/
/* FUN_001aaa0c @ 0x001aaa0c   (est. swift_array_apply_core)
 * Ghidra: void FUN_001aaa0c(void)
 * Core array-apply: runs the type/init sequence and completes.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00358bfc / FUN_0034a210 / FUN_00002534 / FUN_00353e5c /
 *   FUN_00351f40 / FUN_0035a4bc / FUN_001ab924 / FUN_00357418 /
 *   FUN_0034bc94 / FUN_000839d8.
 */
void swift_array_apply_core(void)
{
    reg16 v = FUN_00358bfc();
    sv_80 = x6;
    us_78 = x7;
    FUN_0034a210();
    FUN_00002534();
    FUN_00353e5c();
    FUN_00351f40(x8, FUN_00346744, aus_90);
    FUN_0035a4bc();
    FUN_001ab924();
    if (x21 == 0) {
        FUN_00357418();
        FUN_0034bc94();
        FUN_000839d8();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001aaabc @ 0x001aaabc   (est. swift_array_init_from_words)
 * Ghidra: void FUN_001aaabc(...)
 * Initializes an array from the current element words and reserves storage.
 * Confidence: medium
 * Notes: FUN_00352ddc / FUN_00310d34 / FUN_0034921c / FUN_0019e578 /
 *   FUN_001a9640.
 */
void swift_array_init_from_words(uint64_t p1, uint64_t p2)
{
    FUN_00352ddc();
    reg16 v = FUN_00310d34();
    FUN_0034921c(v.lo, v.hi, v.lo);
    uint64_t u = FUN_0019e578(aus_28);
    FUN_001a9640(u, p2);
}

/*--------------------------------------------------------------------*/
/* FUN_001aab04 @ 0x001aab04   (est. swift_array_init_from_words2)
 * Ghidra: void FUN_001aab04(...)
 * Initializes an array from words and stores the result with the type/tag.
 * Confidence: medium
 * Notes: FUN_001aaabc.
 */
void swift_array_init_from_words2(reg16 *out, uint64_t p2, long p3, uint64_t p4, uint64_t p5)
{
    reg16 v = FUN_001aaabc(p2, *(uint64_t *)(p3 + 0x10));
    *out = v;
    *(uint64_t *)out[1] = p4;
    *(uint64_t *)(out[1] + 8) = p5;
}

/*--------------------------------------------------------------------*/
/* FUN_001aab34 @ 0x001aab34   (est. sk_sched_queue_release)
 * Ghidra: void FUN_001aab34(void)
 * Releases the run queue: frees the backing storage then the object.
 * Confidence: medium
 * Notes: FUN_001aab58 / FUN_0006f6b4.
 */
void sk_sched_queue_release(void)
{
    FUN_001aab58();
    FUN_0006f6b4();
}

/*--------------------------------------------------------------------*/
/* FUN_001aab58 @ 0x001aab58   (est. sk_sched_queue_free_storage)
 * Ghidra: void FUN_001aab58(void)
 * Frees the run-queue backing storage.
 * Confidence: medium
 * Notes: FUN_00351f10 / FUN_000a6fe0 / FUN_0036b118.
 */
void sk_sched_queue_free_storage(void)
{
    FUN_00351f10();
    FUN_000a6fe0();
    sk_free(NULL);                          /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aaba8 @ 0x001aaba8   (est. sk_sched_queue_remove_all)
 * Ghidra: void FUN_001aaba8(...)
 * Removes all elements from the run queue: dispatches through the element-
 * destroy loop, or frees the storage if the queue is empty.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00348f38, FUN_001aab58,
 *   FUN_0006f6b4, FUN_001aad30, FUN_0008e500.
 */
void sk_sched_queue_remove_all(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    uint64_t u4 = p3;
    uint64_t u1 = x30;
    FUN_00349720();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    reg16 v5 = FUN_00348f38();
    if (v5.hi < 0) {
        FUN_00350410();
        FUN_003488bc();
        FUN_0034baf0();
        FUN_0035110c();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
    if (x1 == 0) {
        (**(code_fn **)(x16 + 8))(v5.lo, p3);
        FUN_001aab58(p3);
        u4 = 0;
        reg16 v6 = FUN_0006f6b4();
        u1 = 1;
    } else {
        FUN_00350524();
        reg16 v6 = FUN_001aad30();
        FUN_003504e8();
        FUN_00319598();
        FUN_00358e7c();
        FUN_001aad64(x1);
        fn2 = *(code_fn **)(x16 + 0x10);
        long n = x1;
        do {
            if (n == 0) {
                FUN_00348034();
                FUN_003504b8();
                sk_swift_fatal(0, 0, 0);           /* noreturn */
            }
            reg16 v7 = FUN_00354d14();
            fn2(v7.lo, v7.hi, p3);
            v7 = FUN_00100c38(*(uint64_t *)(x16 + 0x20));
            x8_00_fn(v7.lo, v7.hi, p3);
            n--;
        } while (n != 0);
        (**(code_fn **)(x16 + 8))(v5.lo, p3);
    }
    sk_thread_epilogue(v6.lo, v6.hi, u4, u1, x30);  /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aad30 @ 0x001aad30   (est. sk_sched_queue_foreach_destroy)
 * Ghidra: void FUN_001aad30(...)
 * Iterates and destroys queue elements: forwards each through the element
 * accessor and reserve path.
 * Confidence: medium
 * Notes: FUN_00352efc / FUN_0019c44c / FUN_00357970 / FUN_001a964c.
 */
void sk_sched_queue_foreach_destroy(uint64_t p1, uint64_t p2)
{
    reg16 v = FUN_00352efc();
    FUN_0019c44c(v.lo, v.hi, p2);
    FUN_00357970();
    FUN_001a964c();
}

/*--------------------------------------------------------------------*/
/* FUN_001aad64 @ 0x001aad64   (est. swift_array_grow_count)
 * Ghidra: void FUN_001aad64(long param_1)
 * Grows the array count by param_1: computes the free slots, validates, and
 * extends the count. Traps on overflow.
 * Confidence: medium
 * Notes: traps at 0x1aade0 / 0x1aade4 / 0x1aade8 / 0x1aadec;
 *   FUN_002dc564 / FUN_002dc5a4 / FUN_0036b118.
 */
void swift_array_grow_count(long delta)
{
    uint64_t cap = (uint64_t)x20[3] >> 1;
    long free = cap - x20[2];
    if (SBORROW8(cap, x20[2])) __builtin_trap();        /* 0x1aade0 */
    long need = delta - free;
    if (SBORROW8(delta, free)) __builtin_trap();        /* 0x1aade4 */
    if (need == 0) return;
    long cur = FUN_002dc564(*x20);
    if (!SCARRY8(*(long *)(cur + 0x10), need)) {
        *(long *)(cur + 0x10) = *(long *)(cur + 0x10) + need;
        sk_free(NULL);                          /* FUN_0036b118 */
        if (!SCARRY8(cap, need)) {
            FUN_002dc5a4(cap + need);
            return;
        }
        __builtin_trap();                       /* 0x1aadec */
    }
    __builtin_trap();                           /* 0x1aade8 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aadec @ 0x001aadec   (est. sk_sched_queue_dealloc)
 * Ghidra: undefined8 FUN_001aadec(long param_1)
 * Deallocates the run queue: frees the storage (or retains/refcounts it if
 * still referenced), returning the final handle. Fatals on negative count.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00350c5c / FUN_001aab58 / FUN_0006f6b4 / FUN_0009461c /
 *   FUN_001aad30 / FUN_000b43e8 / FUN_0035a490 / FUN_0036b118 /
 *   FUN_00350798 / FUN_00319598 / FUN_001aad64; fatal FUN_001afe4c.
 */
uint64_t sk_sched_queue_dealloc(long count)
{
    if (count >= 0) {
        FUN_00350c5c();
        reg16 v = FUN_001aab58(x1);
        if (x19 == 0) {
            return FUN_0006f6b4(v.lo, v.hi, 0);
        }
        FUN_0009461c();
        FUN_001aad30();
        FUN_000b43e8();
        FUN_0035a490();
        FUN_0006f6b4();
        sk_free(NULL);                          /* FUN_0036b118 */
        FUN_00350798();
        FUN_00319598();
        FUN_001aad64();
        return x21;
    }
    FUN_003488bc(1);
    FUN_0034baf0();
    FUN_0035110c();
    sk_swift_fatal(0, 0, 0);                           /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001aaea8 @ 0x001aaea8   (est. swift_array_subrange)
 * Ghidra: void FUN_001aaea8(...)
 * Returns a subrange of the array: computes the element pointer for the
 * subrange base and length.
 * Confidence: medium
 * Notes: FUN_001aadec / FUN_003597d8.
 */
void swift_array_subrange(reg16 *out, uint64_t p2, uint64_t p3, long base, uint64_t p5)
{
    FUN_001aadec();
    reg16 v = FUN_003597d8();
    long stride = *(long *)(x16 + 0x48);
    *out = v;
    *(long *)out[1] = base;
    *(uint64_t *)(out[1] + 8) = p5;
    *(long *)out[2] = v.hi + stride * base;
}

/*--------------------------------------------------------------------*/
/* FUN_001aaef0 @ 0x001aaef0   (est. swift_array_reserve_realloc)
 * Ghidra: void FUN_001aaef0(void)
 * Reallocates an array to a larger capacity: computes the new capacity,
 * allocates a fresh buffer, copies the elements, and updates the array words.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00358374 / FUN_00319598 / FUN_0008f5f4 / FUN_001a9714 /
 *   FUN_0019c44c / FUN_00376820 / FUN_0019fa60 / FUN_001ab008 /
 *   FUN_0036b118; trap at 0x1ab008.
 */
void swift_array_reserve_realloc(void)
{
    reg16 v = FUN_00358374();
    long l8 = *(long *)(v.hi + 0x10);
    FUN_00350530();
    long l2 = FUN_00319598();
    uint64_t ok = FUN_0008f5f4();
    if ((ok & 1) != 0) {
        FUN_00357228();
        long l4 = FUN_001a9714();
        if (v.lo <= l4) goto done;
    }
    long l4 = x20[2];
    uint64_t u3 = x20[3];
    uint64_t cap = u3 >> 1;
    if (SBORROW8(cap, l4)) __builtin_trap();    /* 0x1ab008 */
    long l10 = x20[1];
    long l9 = *x20;
    FUN_003510a0(cap - l4);
    long l5 = FUN_0019c44c();
    sv_70 = l9;
    ls_68 = l10;
    sv_60 = l4;
    us_58 = u3;
    sk_alloc_pages(l9, 0);                      /* FUN_0036b270 */
    uint64_t u6 = FUN_0034a000();
    u6 = sk_metatype(u6, l2);                   /* FUN_00376820 */
    FUN_00348e9c(u6, u6);
    FUN_0019fa60(&sv_80, l2);
    FUN_003561dc(sv_80, us_78);
    v = FUN_00357c20(*(uint8_t *)(x16 + 0x50));
    FUN_003527e0(v.lo, v.hi, l5 + x8);
    FUN_001ab008();
    FUN_0034d7dc();
    FUN_001a964c();
    FUN_00350b90();
    FUN_0035a4c8();
    sk_free((void *)l9);                                /* FUN_0036b118 */
    *x20 = (long)&sv_70;
    x20[1] = l8;
    x20[2] = l4;
    x20[3] = l2;
done:
    FUN_00358344(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001ab008 @ 0x001ab008   (est. swift_array_copy_elements)
 * Ghidra: long FUN_001ab008(...)
 * Copies array elements between storage regions, returning the new element
 * count. Traps on borrow.
 * Confidence: medium
 * Notes: FUN_0035089c / FUN_0036b118 / FUN_0034b518 / FUN_0035056c /
 *   FUN_0019dadc; trap at 0x1ab07c.
 */
long swift_array_copy_elements(uint64_t p1, uint64_t p2, long p3, uint64_t p4, long p5)
{
    FUN_0035089c();
    sk_free((void *)p4);                                /* FUN_0036b118 */
    if (!SBORROW8(x22, x23)) {
        FUN_0034b518();
        long stride = *(long *)(x16 + 0x48);
        FUN_0035056c(p5 + stride * x23);
        FUN_0019dadc();
        return p3 + stride * (x22 - x23);
    }
    __builtin_trap();                           /* 0x1ab07c */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab07c @ 0x001ab07c   (est. sk_sched_queue_push_node)
 * Ghidra: void FUN_001ab07c(void)
 * Pushes a new node onto the run queue under irqsave: acquires the lock,
 * resolves the element type, links the node, and restores flags.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00357cb4/74 (irqsave/restore), FUN_00376820, FUN_001a10d4,
 *   FUN_001a10e4, FUN_0036b118.
 */
void sk_sched_queue_push_node(void)
{
    long flags = FUN_00357cb4();
    FUN_00356834();
    uint64_t u2 = FUN_00319598();
    uint64_t u3 = FUN_0034ad60();
    sk_metatype(u3, u2);                        /* FUN_00376820 */
    FUN_003511cc(flags, flags + 1);
    u2 = FUN_001a10d4();
    FUN_000b4390();
    FUN_001a10e4();
    FUN_00356cfc();
    sk_free(NULL);                              /* FUN_0036b118 */
    sk_irqrestore(u2, x30);                     /* FUN_00357c74 */
    sk_free(NULL);                              /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab0fc @ 0x001ab0fc   (est. swift_array_push_elem)
 * Ghidra: void FUN_001ab0fc(undefined8 param_1)
 * Pushes an element onto the array: if uniquely referenced, computes the free
 * space and appends via FUN_001ab07c.
 * Confidence: medium
 * Notes: FUN_0035a040 / FUN_00319598 / FUN_0008f5f4 / FUN_003586fc /
 *   FUN_001ab07c; trap at 0x1ab150.
 */
void swift_array_push_elem(uint64_t p1)
{
    FUN_0035a040();
    FUN_00319598();
    uint64_t ok = FUN_0008f5f4();
    if ((ok & 1) != 0) return;
    FUN_003586fc();
    if (!SBORROW8(x9, x8)) {
        FUN_001ab07c(x9 - x8, p1);
        return;
    }
    __builtin_trap();                           /* 0x1ab150 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab150 @ 0x001ab150   (est. swift_array_reserve_push)
 * Ghidra: void FUN_001ab150(void)
 * Reserves space and pushes an element: if the current element fits, done;
 * otherwise yields and reallocates via FUN_001ab07c.
 * Confidence: medium
 * Notes: FUN_0008409c / FUN_001a9714 / FUN_00084180 / FUN_001ab07c.
 */
void swift_array_reserve_push(void)
{
    FUN_0008409c();
    long cap = FUN_001a9714(*x20, x20[1], x20[2], x20[3], *(uint64_t *)(x19 + 0x10));
    if (x21 + 1 <= cap) return;
    FUN_00084180();                             /* yield */
    FUN_001ab07c();
}

/*--------------------------------------------------------------------*/
/* FUN_001ab1ac @ 0x001ab1ac   (est. swift_array_is_unique)
 * Ghidra: undefined8 FUN_001ab1ac(void)
 * Returns whether the array backing storage is uniquely referenced.
 * Confidence: medium
 * Notes: *(byte*)(x20+3) & 1; FUN_003a261c.
 */
uint64_t swift_array_is_unique(void)
{
    if ((*(uint8_t *)(x20 + 3) & 1) == 0) return 0;
    return FUN_003a261c(*x20);
}

/*--------------------------------------------------------------------*/
/* FUN_001ab1d8 @ 0x001ab1d8   (est. swift_array_elem_store)
 * Ghidra: void FUN_001ab1d8(...)
 * Stores an element at the array tail: grows the count, resolves the element
 * type, and dispatches through the element-set vtable.
 * Confidence: low (jumptable at 0x001ab24c)
 * Notes: FUN_0008409c / FUN_00350488 / FUN_00319598 / FUN_001aad64.
 */
void swift_array_elem_store(uint64_t val, uint64_t p2, long arr)
{
    FUN_0008409c();
    long t = *(long *)(arr + 0x10);
    FUN_00350488();
    uint64_t u1 = FUN_00319598();
    FUN_001aad64(x21 + 1, u1);
    long desc = *(long *)(t - 8);
    long stride = *(long *)(desc + 0x48);
    (**(code_fn **)(desc + 0x20))
        (*(long *)(x20 + 8) + stride * *(long *)(x20 + 0x10) + stride * x21);  /* jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab29c @ 0x001ab29c   (est. swift_array_reserve_grow)
 * Ghidra: void FUN_001ab29c(...)
 * Grows a Swift Array to hold more elements: computes the free space,
 * reallocates the backing store, copies the existing elements, and updates
 * the array words. Fatals on insufficient capacity.
 * Confidence: low (inlined, unaff regs, many traps)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_001ab52c,
 *   FUN_001a9714, FUN_001a26e0, FUN_001a2740, FUN_001a27f0, FUN_001aad64,
 *   FUN_001a91c4; traps at 0x1ab500-0x1ab52c; fatal FUN_001afe4c.
 */
void swift_array_reserve_grow(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    FUN_00355160();
    FUN_00353160();
    uint64_t lock = FUN_00377824();         /* lock */
    FUN_0034cfb4();
    FUN_00377bec();
    FUN_0034fcf4();
    uint64_t u4 = FUN_003195b0();
    FUN_0034ab20();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350428();
    FUN_00349080();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034f3c4();
    FUN_000a6894(p4);
    FUN_00350c74();
    FUN_003518b8();
    long l5 = x8_fn();
    FUN_001ab52c(l5, cpu.hi);
    FUN_00350720();
    uint64_t u6 = FUN_00319598();
    FUN_0008f5f4();
    long l8 = x20[2];
    long free = ((uint64_t)x20[3] >> 1) - l8;
    if (SBORROW8((uint64_t)x20[3] >> 1, l8)) __builtin_trap();   /* 0x1ab500 */
    long l9 = x20[1];
    FUN_003597b4(*x20);
    FUN_00351b38();
    long l7 = FUN_001a9714();
    if (!SBORROW8(l7, free)) {
        reg16 v = FUN_001a26e0(l9 + *(long *)(x16_00 + 0x48) * l8
                               + *(long *)(x16_00 + 0x48) * free, l7 - free);
        FUN_00350ea4(v.lo, v.hi, v.lo);
        l8 = FUN_001a2740();
        FUN_00350920();
        long l9b = FUN_001a27f0();
        if (l9b < l5) {
            FUN_00350410();
            FUN_003488bc();
            FUN_00355594();
            FUN_0034baf0();
            FUN_0035110c();
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        FUN_0034c664();
        (**(code_fn **)(x16_01 + 8))(cpu.lo, p3);
        if (0 < l9b) {
            if (SCARRY8(free, l9b)) __builtin_trap();   /* 0x1ab52c */
            FUN_001aad64(free + l9b, u6);
        }
        if (l8 == v.hi) {
            reg16 v2 = FUN_00351648(*(uint64_t *)(x16 + 0x20));
            x8_00_fn(v2.lo, v2.hi, lock);
            uint64_t u3 = FUN_0034ad60();
            sk_metatype(u3, u6);            /* FUN_00376820 */
            v2 = FUN_00353cf0();
            FUN_001a91c4(v2.lo, v2.hi, u4);
        } else {
            FUN_003507d4(*(uint64_t *)(x16 + 8));
            x8_01_fn();
        }
        sk_thread_epilogue();               /* FUN_0008e500 */
        return;
    }
    __builtin_trap();                       /* 0x1ab504 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab52c @ 0x001ab52c   (est. swift_array_capacity_double)
 * Ghidra: void FUN_001ab52c(void)
 * Doubles the array capacity if needed to fit the requested count; reallocates
 * via FUN_001aaef0. Traps on overflow.
 * Confidence: medium
 * Notes: traps at 0x1ab5a8-0x1ab5b0; FUN_001a9714 / FUN_001aaef0.
 */
void swift_array_capacity_double(void)
{
    long free = ((uint64_t)x20[3] >> 1) - x20[2];
    if (SBORROW8((uint64_t)x20[3] >> 1, x20[2])) __builtin_trap();  /* 0x1ab5a8 */
    FUN_0008409c();
    long l3 = FUN_001a9714(*x20, x20[1]);
    long need = free + x21;
    if (SCARRY8(free, x21)) __builtin_trap();           /* 0x1ab5ac */
    long cap = need;
    if (l3 < need) {
        if (l3 + 0x4000000000000000 < 0) __builtin_trap();  /* 0x1ab5b0 */
        cap = l3 * 2;
        if (cap - need == 0 || cap < need) cap = need;
    }
    FUN_001aaef0(cap);
}

/*--------------------------------------------------------------------*/
/* FUN_001ab5b0 @ 0x001ab5b0   (est. swift_array_reserve_extra)
 * Ghidra: void FUN_001ab5b0(void)
 * Reserves extra capacity in the array: if there is free space, dispatches
 * the reserve and rebuilds; otherwise fatals.
 * Confidence: low (indirect dispatch, inlined)
 * Notes: FUN_00354a34 / FUN_00356248 / FUN_001a9ac8 / FUN_00376820 /
 *   FUN_001a9dd8 / FUN_000839d8; trap at 0x1ab64c; fatal FUN_001afe4c.
 */
void swift_array_reserve_extra(void)
{
    reg16 v = FUN_00354a34();
    uint64_t cap = *(uint64_t *)(x20 + 0x18) >> 1;
    if (SBORROW8(cap, *(long *)(x20 + 0x10))) __builtin_trap();    /* 0x1ab64c */
    if (0 < (long)(cap - *(long *)(x20 + 0x10))) {
        FUN_00356248(v.lo, v.hi, *(uint64_t *)(x20 + 8));
        FUN_001a9ac8();
        FUN_00350500();
        uint64_t u2 = FUN_00319230();
        uint64_t u3 = FUN_00348d18();
        sk_metatype(u3, u2);                /* FUN_00376820 */
        FUN_00351384();
        FUN_003513cc();
        FUN_001a9dd8();
        FUN_0034ba48();
        FUN_00354ef8();
        FUN_000839d8();
        return;
    }
    FUN_003488bc(1);
    FUN_0034baf0();
    FUN_0035110c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab670 @ 0x001ab670   (est. sk_sched_lock_seq_ab)
 * Ghidra: void FUN_001ab670(void)
 * Scheduler lock sequence followed by an indirect dispatch.
 * Confidence: low (indirect)
 * Notes: FUN_0034a74c / FUN_00354db8 / FUN_003195c8 / FUN_0034eb10.
 */
void sk_sched_lock_seq_ab(void)
{
    FUN_0034a74c();
    FUN_00354db8();
    FUN_003195c8();
    FUN_0034eb10();
    x8_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_001ab6b4 @ 0x001ab6b4   (est. swift_array_append_elem)
 * Ghidra: void FUN_001ab6b4(void)
 * Appends an element to the array: dispatches the element-store, then
 * rebuilds if capacity allows. Fatals on count overflow.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_00357ca0 / FUN_0008409c / FUN_001a9ac8 / FUN_00376820 /
 *   FUN_001a9dd8 / FUN_00357c44; trap at 0x1ab734; fatal FUN_001afe4c.
 */
void swift_array_append_elem(void)
{
    FUN_00357ca0();
    reg16 v = FUN_0008409c();
    FUN_001a9ac8(v.lo, v.hi, *(uint64_t *)(x20 + 8), *(uint64_t *)(x20 + 0x10),
                 *(uint64_t *)(x20 + 0x18), *(uint64_t *)(v.hi + 0x10));
    if (SCARRY8(x21, 1)) __builtin_trap();  /* 0x1ab734 */
    if (x21 <= x21 + 1) {
        FUN_00350500();
        uint64_t u2 = FUN_00319230();
        uint64_t u3 = FUN_00348d18();
        sk_metatype(u3, u2);                /* FUN_00376820 */
        FUN_000b4390();
        v = FUN_00351f64();
        FUN_00357c44(v.lo, v.hi, x30);
        FUN_001a9dd8();
        return;
    }
    FUN_00347d60();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001ab808 @ 0x001ab808   (est. swift_array_reset_or_grow)
 * Ghidra: void FUN_001ab808(void)
 * Resets a Swift Array or grows its backing store depending on whether the
 * storage is uniquely referenced. Ends with the teardown.
 * Confidence: low (inlined, unaff regs)
 * Notes: FUN_00041138 / FUN_001aab58 / FUN_0036b118 / FUN_001ab1ac /
 *   FUN_001a9714 / FUN_00376820 / FUN_0019fa60 / FUN_001a9dd8 /
 *   FUN_0035847c.
 */
void swift_array_reset_or_grow(void)
{
    reg16 v = FUN_00041138();
    long t = v.hi;
    uint64_t u5 = *(uint64_t *)(t + 0x10);
    if ((v.lo & 1) == 0) {
        FUN_001aab58(u5);
        sk_free((void *)*x20);                      /* FUN_0036b118 */
        FUN_000a6f68();
        *x20 = x8;
        x20[1] = x1;
        u5 = DAT_004c08a0;
        x20[3] = uRam_4c08a8;
        x20[2] = u5;
    } else {
        uint64_t uniq = FUN_001ab1ac();
        uint64_t u6 = *x20;
        uint64_t u2 = x20[2];
        if ((uniq & 1) == 0) {
            FUN_003548a0(uniq, x20[1]);
            uint64_t u3 = FUN_001a9714();
            FUN_003512f4(u3, u3);
            FUN_0019c44c();
            FUN_003510c4();
            FUN_001a964c();
            FUN_00350b90();
            FUN_0035a490();
            sk_free((void *)u6);                    /* FUN_0036b118 */
            *x20 = u2;
            x20[1] = u5;
            x20[2] = x23;
            x20[3] = x24;
        } else {
            u5 = FUN_00356d5c();
            u5 = sk_metatype(u5, t);        /* FUN_00376820 */
            FUN_00348e9c(u5, u5);
            FUN_0019fa60(t);
            FUN_00350530();
            u5 = FUN_00319230();
            u2 = FUN_00348d18();
            sk_metatype(u2, u5);            /* FUN_00376820 */
            FUN_00351450();
            FUN_00353208();
            FUN_001a9dd8();
        }
    }
    FUN_0035847c(x30);
}

/*--------------------------------------------------------------------*/
/* FUN_001ab924 @ 0x001ab924   (est. swift_buffer_apply_cb)
 * Ghidra: void FUN_001ab924(void)
 * Applies a callback to a Swift buffer: resolves the type descriptor, sets up
 * the stack frame, and dispatches through FUN_001ad494.
 * Confidence: low (inlined, stack setup)
 * Notes: DAT_00658c00, FUN_001ad494.
 */
void swift_buffer_apply_cb(void)
{
    long desc = *(long *)(is_0 - 8);
    dispatch_slot(0);                       /* DAT_00658c00 */
    long off = -(x12 + 0xf & 0xfffffffffffffff0);
    *(uint64_t *)((long)als_50 + off + 8) = x13;
    *(void **)((long)als_50 + off + 0x10) = &stack_d0 + off;
    *(long *)((long)als_50 + off) = is_0;
    FUN_001ad494();
    if (x21 != 0)
        (**(code_fn **)(desc + 0x20))(is_10, &stack_d0 + off, is_0);
}

/*--------------------------------------------------------------------*/
/* FUN_001ab9e0 @ 0x001ab9e0   (est. swift_array_capacity_check)
 * Ghidra: undefined8 FUN_001ab9e0(void)
 * Checks whether the array has a specific free capacity; returns the backing
 * object if so, else 0.
 * Confidence: medium
 * Notes: FUN_00357a34 / FUN_002dc564 / FUN_0036b118; trap at 0x1aba44.
 */
uint64_t swift_array_capacity_check(void)
{
    if ((x3 & 1) != 0) {
        FUN_00357a34();
        long l2 = FUN_002dc564();
        l2 = *(long *)(l2 + 0x10);
        sk_free(NULL);                      /* FUN_0036b118 */
        if (SBORROW8(x3 >> 1, x20)) __builtin_trap();   /* 0x1aba44 */
        if (l2 == (x3 >> 1) - x20) return FUN_002dc564();
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001aba44 @ 0x001aba44   (est. swift_array_empty_init)
 * Ghidra: void FUN_001aba44(undefined8 *param_1, long param_2)
 * Initializes an empty Swift Array: releases the queue storage and installs
 * the shared empty-array singleton.
 * Confidence: high (DAT_00657778 empty-array singleton)
 * Notes: FUN_001aab34; DAT_00657778 / DAT_004c08a0 / uRam_4c08a8.
 */
void swift_array_empty_init(uint64_t *out, long p2)
{
    FUN_001aab34(*(uint64_t *)(p2 + 0x10));
    *out = (uint64_t)0x00657778;
    out[1] = x1;
    uint64_t u1 = DAT_004c08a0;
    out[3] = uRam_4c08a8;
    out[2] = u1;
}

/*--------------------------------------------------------------------*/
/* FUN_001abaa8 @ 0x001abaa8   (est. swift_array_remove_all)
 * Ghidra: void FUN_001abaa8(...)
 * Removes all elements of the array: releases via FUN_001aaba8 and stores the
 * element type/tag.
 * Confidence: medium
 * Notes: FUN_001aaba8.
 */
void swift_array_remove_all(reg16 *out, uint64_t p2, uint64_t p3, long p4, uint64_t p5)
{
    uint64_t u1 = *(uint64_t *)(p4 + 0x10);
    reg16 v = FUN_001aaba8();
    *out = v;
    *(uint64_t *)out[1] = u1;
    *(uint64_t *)(out[1] + 8) = p5;
}

/*--------------------------------------------------------------------*/
/* FUN_001abad8 @ 0x001abad8   (est. swift_array_iterator_init2)
 * Ghidra: void FUN_001abad8(...)
 * Initializes an array iterator via FUN_001a9a30 and stores type/tag.
 * Confidence: medium
 * Notes: FUN_001a9a30.
 */
void swift_array_iterator_init2(reg16 *out, uint64_t p2, uint64_t p3, uint64_t p4, long p5)
{
    reg16 v = FUN_001a9a30(p2, *(uint64_t *)(p5 + 0x10));
    *out = v;
    *(uint64_t *)out[1] = p3;
    *(uint64_t *)(out[1] + 8) = p4;
}

/*--------------------------------------------------------------------*/
/* FUN_001abb40 @ 0x001abb40   (est. swift_string_append_dispatch)
 * Ghidra: undefined8 FUN_001abb40(undefined8 param_1, undefined8 param_2)
 * Resolves the metatype for the string append and dispatches through
 * FUN_001abe00; returns 1 on success.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_001abe00.
 */
uint64_t swift_string_append_dispatch(uint64_t p1, uint64_t p2)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e83e4);    /* FUN_00376820 */
    FUN_001abe00(p1, p2, meta);
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001abb98 @ 0x001abb98   (est. swift_string_remove_suffix)
 * Ghidra: undefined8 FUN_001abb98(long param_1)
 * Removes `param_1` characters from the end of a Swift string; validates the
 * range bounds. Fatals on removing more items than present.
 * Confidence: high (string-matched fatal "Range requires lowerBound <= upp" +
 *   "Can't remove more items from a c")
 * Notes: FUN_002ae2c0 / FUN_002ab5bc; strings at 0x005cda00 / 0x005cda30 /
 *   0x005ce120 / 0x005cdd20; trap at 0x1abc38.
 */
uint64_t swift_string_remove_suffix(long n)
{
    if (SBORROW8(0, n)) __builtin_trap();               /* 0x1abc38 */
    uint64_t u1 = *(uint64_t *)*x20;
    uint64_t u3 = *(uint64_t *)(*x20 + 8);
    uint64_t u2 = *(uint64_t *)x20[1];
    uint64_t u4 = *(uint64_t *)(x20[1] + 8);
    reg12 r = FUN_002ae2c0(u3, -n, u1, u2, u4);
    if ((r.hi & 0xff) != 1) {
        if (u1 >> 0xe <= r.lo >> 0xe) {
            reg16 v = FUN_002ab5bc(u1, r.lo, u1, u3, u2, u4);
            *x20 = v;
            *(uint64_t *)x20[1] = u2;
            *(uint64_t *)(x20[1] + 8) = u4;
            return 1;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more2, 0x3a, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x33a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001abcc8 @ 0x001abcc8   (est. swift_string_remove_suffix2)
 * Ghidra: undefined8 FUN_001abcc8(long param_1)
 * Remove-suffix variant using FUN_002b3f40.
 * Confidence: high (string-matched fatal as FUN_001abb98)
 * Notes: FUN_002b3f40 / FUN_002ab5bc; trap at 0x1abd70; strings at 0x005cda00 /
 *   0x005ce120 / 0x005cdd20.
 */
uint64_t swift_string_remove_suffix2(long n)
{
    if (SBORROW8(0, n)) __builtin_trap();               /* 0x1abd70 */
    uint64_t u1 = *(uint64_t *)*x20;
    uint64_t u3 = *(uint64_t *)(*x20 + 8);
    uint64_t u2 = *(uint64_t *)x20[1];
    uint64_t u4 = *(uint64_t *)(x20[1] + 8);
    reg12 r = FUN_002b3f40(u3, -n, u1, u1, u3, u2, u4);
    if ((r.hi & 0xff) != 1) {
        if (u1 >> 0xe <= r.lo >> 0xe) {
            reg16 v = FUN_002ab5bc(u1, r.lo, u1, u3, u2, u4);
            *x20 = v;
            *(uint64_t *)x20[1] = u2;
            *(uint64_t *)(x20[1] + 8) = u4;
            return 1;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more2, 0x3a, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x33a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001abe00 @ 0x001abe00   (est. swift_string_append_core)
 * Ghidra: void FUN_001abe00(...)
 * Core Swift string append: computes the combined length, reallocates the
 * backing storage, and appends the second string. Ends with the thread
 * epilogue.
 * Confidence: low (very heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec,
 *   FUN_000277b8, FUN_0008e500; trap at 0x1ac23c; fatal FUN_001afe4c.
 */
void swift_string_append_core(uint64_t p1, uint64_t p2, uint64_t p3)
{
    long l3 = FUN_0008e518();
    FUN_00352894(p3);
    FUN_0034c158();
    FUN_00352314();
    FUN_00377824();                         /* lock */
    long base = FUN_0034a654();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003493c4();
    FUN_0034d244();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034ffc8();
    FUN_003516e4();
    FUN_00351584();
    FUN_00377bec();
    FUN_0034d734();
    FUN_00310e08();
    FUN_00348e00();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b0d4();
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_000aa4ec();
    FUN_0035196c();
    FUN_00350500();
    FUN_00310d68();
    uint64_t u5 = FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b05c();
    FUN_0034998c();
    dispatch_slot(*(uint64_t *)(x8_01 + 0x40)); /* DAT_00658c00 */
    FUN_00348b5c();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034baa8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a464();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aa14();
    FUN_00310924();
    FUN_00350b24();
    FUN_00350c38();
    x9_fn();
    bool empty = (l3 == 0);
    if (SBORROW8(0, l3)) __builtin_trap();  /* 0x1ac23c */
    FUN_0035512c();
    fn6 = (code_fn *)FUN_000277b8();
    FUN_003507e0();
    fn6();
    FUN_00358d10();
    FUN_003195f8();
    FUN_00350b30();
    FUN_00350ea4();
    x9_00_fn();
    fn9 = *(code_fn **)(x16_01 + 8);
    FUN_000e15d8();
    fn9();
    FUN_000e72b0();
    fn9();
    FUN_00357400();
    uint64_t u7 = FUN_0034b2a8();
    if (empty) {
        FUN_00351c28(u7, u5);
        x8_05_fn();
        FUN_00348b7c(0x33a);
        FUN_0035863c();
        FUN_0034a69c();
        FUN_00353f14();
    } else {
        fn10 = *(code_fn **)(x16_01 + 0x20);
        FUN_00350494();
        fn10();
        FUN_00351990();
        FUN_00358684(x19, x20);
        x9_01_fn();
        u5 = FUN_00352d34();
        fn6(u5, x24);
        fn6 = *(code_fn **)(x16_00 + 8);
        FUN_0007c1c4();
        fn6();
        FUN_003537f0();
        FUN_00310e20();
        FUN_0034eef8();
        FUN_00351280();
        uint64_t ok = x8_02_fn();
        if ((ok & 1) != 0) {
            FUN_0034ef98();
            fn10();
            FUN_00350ed0(sv_80 + *(int *)(base + 0x30));
            fn10();
            FUN_0034d384();
            FUN_00350c20();
            x9_02_fn();
            int off = *(int *)(base + 0x30);
            FUN_0034cfc4();
            fn10();
            fn9(us_68 + off);
            reg16 v = FUN_0035060c(*(uint64_t *)(x16 + 0x20));
            x8_03_fn(v.lo, v.hi, base);
            FUN_00357fc4((long)*(int *)(base + 0x30));
            fn10();
            FUN_00351274();
            fn9();
            FUN_00352abc();
            FUN_00350878(x20, x27);
            x9_03_fn();
            FUN_00353db8();
            FUN_003508b4();
            x8_04_fn();
            FUN_0007c1c4();
            fn6();
            sk_thread_epilogue(1, x30);     /* FUN_0008e500 */
            return;
        }
        FUN_00347d60();
    }
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001ac288 @ 0x001ac288   (est. swift_string_remove_all)
 * Ghidra: undefined8 FUN_001ac288(void)
 * Removes all characters from a Swift string; fatals on an already-empty
 * string.
 * Confidence: high (string-matched fatal "Can't remove items from an empty" +
 *   "Range requires lowerBound <= upp")
 * Notes: FUN_002b7088 / FUN_002b71c4 / FUN_002ab5bc / thunk_FUN_0036b270 /
 *   FUN_003a25d4; strings at 0x005ce160 / 0x005cdd20 / 0x005cda00 /
 *   0x005cda30.
 */
uint64_t swift_string_remove_all(void)
{
    uint64_t u1 = *(uint64_t *)*x20;
    uint64_t u3 = *(uint64_t *)(*x20 + 8);
    if (u3 >> 0xe == u1 >> 0xe)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_empty, 0x2b, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x2a5, 1);
    uint64_t u2 = *(uint64_t *)x20[1];
    uint64_t u4 = *(uint64_t *)(x20[1] + 8);
    uint64_t u5 = FUN_002b7088(u1, u1, u3, u2, u4);
    thunk_FUN_0036b270(u4);                 /* alloc pages */
    uint64_t u6 = FUN_002b71c4(u1);
    if (u6 >> 0xe <= u3 >> 0xe) {
        FUN_003a25d4(u4);
        reg16 v = FUN_002ab5bc(u6, u3, u1, u3, u2, u4);
        *x20 = v;
        *(uint64_t *)x20[1] = u2;
        *(uint64_t *)(x20[1] + 8) = u4;
        return u5;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                   s_swift_range, 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001ac3d8 @ 0x001ac3d8   (est. swift_string_remove_all2)
 * Ghidra: undefined1 [16] FUN_001ac3d8(void)
 * Remove-all variant using the multi-step realloc helpers.
 * Confidence: high (string-matched fatal as FUN_001ac288)
 * Notes: FUN_002b439c / FUN_002ab6a0 / FUN_002b3b84 / FUN_002ab5bc; strings
 *   at 0x005ce160 / 0x005cda00 / 0x005cda30 / 0x005cdd20.
 */
reg16 swift_string_remove_all2(void)
{
    uint64_t u1 = *(uint64_t *)*x20;
    uint64_t u3 = *(uint64_t *)(*x20 + 8);
    if (u3 >> 0xe == u1 >> 0xe)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_empty, 0x2b, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x2a5, 1);
    uint64_t u2 = *(uint64_t *)x20[1];
    uint64_t u4 = *(uint64_t *)(x20[1] + 8);
    reg16 v7 = FUN_002b439c(u1, u1, u3, u2, u4);
    uint64_t u5 = FUN_002ab6a0(u1, u1, u3, u2, u4);
    uint64_t u6 = FUN_002b3b84(u5, u1, u3, u2, u4);
    if (u6 >> 0xe <= u3 >> 0xe) {
        reg16 v8 = FUN_002ab5bc(u6, u3, u1, u3, u2, u4);
        *x20 = v8;
        *(uint64_t *)x20[1] = u2;
        *(uint64_t *)(x20[1] + 8) = u4;
        return v7;
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                   s_swift_range, 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001ac9b0 @ 0x001ac9b0   (est. swift_string_remove_prefix)
 * Ghidra: void FUN_001ac9b0(long param_1)
 * Removes `param_1` characters from the start of a Swift string; validates
 * bounds. Fatals on negative count or removing more than present.
 * Confidence: high (string-matched fatal "Number of elements to remove sho" +
 *   "Can't remove more items from a c" + "Range requires...")
 * Notes: FUN_002ae2c0 / FUN_002ab5bc; strings at 0x005cddd0 / 0x005ce120 /
 *   0x005cdd20 / 0x005cda00 / 0x005cda30.
 */
void swift_string_remove_prefix(long n)
{
    if (n == 0) return;
    if (n < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_num_to_remove, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x2bf, 1);
    uint64_t u4 = *(uint64_t *)*x20;
    uint64_t u1 = *(uint64_t *)(*x20 + 8);
    uint64_t u7 = *(uint64_t *)x20[1];
    uint64_t u2 = *(uint64_t *)(x20[1] + 8);
    reg12 r = FUN_002ae2c0(u4, n, u1, u7, u2);
    if ((r.hi & 0xff) != 1) {
        if (r.lo >> 0xe <= u1 >> 0xe) {
            reg16 v = FUN_002ab5bc(r.lo, u1, u4, u1, u7, u2);
            *x20 = v;
            *(uint64_t *)x20[1] = u7;
            *(uint64_t *)(x20[1] + 8) = u2;
            return;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more2, 0x3a, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x2c1, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001acb10 @ 0x001acb10   (est. swift_string_remove_prefix2)
 * Ghidra: void FUN_001acb10(long param_1)
 * Remove-prefix variant using FUN_002b3f40.
 * Confidence: high (string-matched fatal as FUN_001ac9b0)
 * Notes: FUN_002b3f40 / FUN_002ab5bc; strings at 0x005cddd0 / 0x005ce120 /
 *   0x005cdd20 / 0x005cda00 / 0x005cda30.
 */
void swift_string_remove_prefix2(long n)
{
    if (n == 0) return;
    if (n < 0)
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_num_to_remove, 0x33, 2,
                       s_swift_range_replaceable, 0x26, 2, 0x2bf, 1);
    uint64_t u4 = *(uint64_t *)*x20;
    uint64_t u1 = *(uint64_t *)(*x20 + 8);
    uint64_t u7 = *(uint64_t *)x20[1];
    uint64_t u2 = *(uint64_t *)(x20[1] + 8);
    reg12 r = FUN_002b3f40(u4, n, u1, u4, u1, u7, u2);
    if ((r.hi & 0xff) != 1) {
        if (r.lo >> 0xe <= u1 >> 0xe) {
            reg16 v = FUN_002ab5bc(r.lo, u1, u4, u1, u7, u2);
            *x20 = v;
            *(uint64_t *)x20[1] = u7;
            *(uint64_t *)(x20[1] + 8) = u2;
            return;
        }
        sk_swift_fatal(s_Fatal_error, 0xb, 2, s_range_requires, 0x27, 2,
                       s_swift_range, 0x11, 2, 0x2f9, 1);
    }
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_cant_remove_more2, 0x3a, 2,
                   s_swift_range_replaceable, 0x26, 2, 0x2c1, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001acc78 @ 0x001acc78   (est. sk_sched_queue_insert_dispatch2)
 * Ghidra: void FUN_001acc78(...)
 * Inserts a batch into the run queue under the full lock sequence, dispatching
 * through the saved handler slots. Ends with the thread epilogue or fatal.
 * Confidence: low (very heavy inlining, indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec,
 *   FUN_00310e08, FUN_0008e500; fatal FUN_001afe4c.
 */
void sk_sched_queue_insert_dispatch2(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_0035125c(p3);
    FUN_0034c158();
    FUN_0034ba38();
    FUN_00377824();                         /* lock */
    long base = FUN_0034a654();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003492ac();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034ae58();
    FUN_0034ac78();
    uint64_t u3 = FUN_00377bec();
    FUN_0034d3f4();
    FUN_00310e08();
    FUN_00348e00();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034f3d4();
    FUN_0034e3ac();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_000aa4ec();
    FUN_0035196c();
    FUN_00350500();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b0c4();
    FUN_0034998c();
    dispatch_slot(*(uint64_t *)(x8_01 + 0x40)); /* DAT_00658c00 */
    FUN_003489c0();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a464();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aea8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    uint64_t u4 = FUN_00350464();
    if (x13 == 0) goto ins2_epilogue;
    if (x13 < 0) {
        FUN_00350410();
        FUN_003488bc();
        FUN_00358918();
        FUN_0034a69c();
    } else {
        FUN_0034f1e0();
        FUN_003504ac();
        x9_fn();
        FUN_00310924(x22);
        FUN_00350b24();
        FUN_003504ac();
        x9_00_fn();
        FUN_003192d8(x22);
        FUN_00350c50();
        FUN_003504f4();
        FUN_003518a0();
        x9_01_fn();
        fn7 = *(code_fn **)(x16_01 + 8);
        FUN_000e72b0();
        fn7();
        FUN_00351274();
        fn7();
        FUN_00359be0();
        uint64_t u5 = FUN_0034b2a8();
        if (!ZR) {
            FUN_0034e55c(*(uint64_t *)(x16_01 + 0x20));
            x8_03_fn();
            FUN_003534bc();
            FUN_00350624(x1);
            x9_02_fn();
            FUN_003504ac();
            x9_00_fn();
            FUN_0007c1c4(*(uint64_t *)(x16_00 + 8));
            x8_04_fn();
            FUN_00310e20(u3);
            FUN_003505f4();
            FUN_003516b4();
            uint64_t ok = x8_05_fn();
            if ((ok & 1) != 0) {
                FUN_0034ef98();
                x8_03_fn();
                FUN_003595a8();
                FUN_003511c0();
                x8_03_fn();
                FUN_003534bc();
                reg16 v = FUN_003508cc();
                x9_03_fn(v.lo, v.hi, base);
                int off = *(int *)(base + 0x30);
                FUN_00350c80();
                x8_03_fn();
                fn7(us_38 + off);
                v = FUN_003508cc(*(uint64_t *)(x16 + 0x20));
                x8_06_fn(v.lo, v.hi, base);
                x8_03_fn(sv_58 + *(int *)(x21 + 0x24), us_38 + *(int *)(base + 0x30));
                FUN_00350a70();
                fn7();
                FUN_003517d8();
                FUN_00352eb4();
                FUN_00350878(x20, sv_58);
                x9_04_fn();
                FUN_00353154();
                FUN_00351160();
                x8_07_fn();
                FUN_0007c1c4();
                x8_04_fn();
                goto ins2_epilogue;
            }
            FUN_00347d60();
            goto ins2_fatal;
        }
        FUN_00351a08(u5, u4);
        x8_08_fn();
        *(int *)(x8_02 - 0x10) = (int)fn7;
        FUN_00348b7c(0x2c1);
        FUN_0035863c();
        FUN_0034a69c();
    }
    FUN_00353f14();
ins2_fatal:
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
ins2_epilogue:
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ad118 @ 0x001ad118   (est. sk_obj_metatype_dispatch2)
 * Ghidra: void FUN_001ad118(...)
 * Resolves the metatype for param_3 (DAT_004e83c8) then dispatches the
 * constructor FUN_001a5968.
 * Confidence: medium
 * Notes: FUN_00376820 / FUN_001a5968.
 */
void sk_obj_metatype_dispatch2(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t meta = sk_objc_metatype((void*)0x004e83c8, p3);   /* FUN_00376820 */
    FUN_001a5968(p1, p2, p3, meta, p4);
}

/*--------------------------------------------------------------------*/
/* FUN_001ad190 @ 0x001ad190   (est. swift_collection_init_full)
 * Ghidra: void FUN_001ad190(...)
 * Fully initializes a Swift collection from the current element words: builds
 * the backing buffer, resolves the metatype, and stores the 6-word structure.
 * Confidence: medium
 * Notes: FUN_00352800 / FUN_00353540 / FUN_00310df0 / FUN_00376820 /
 *   FUN_0036b2d0 / FUN_003515b4 / FUN_001a67bc.
 */
void swift_collection_init_full(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    reg16 a0 = FUN_00352800();
    sv_90 = p3;
    us_88 = p4;
    sv_70 = p3;
    us_68 = p4;
    sv_80 = a0;
    FUN_00353540();
    uint64_t u1 = FUN_00310df0();
    uint64_t u2 = FUN_00348d00();
    sk_metatype(u2, u1);                    /* FUN_00376820 */
    u1 = FUN_00354dc4();
    FUN_0036b2d0(u1, 2);
    FUN_003515b4(&sv_60, sv_80, a0, 5);
    FUN_001a67bc();
    x20[1] = us_58;
    *x20 = sv_60;
    x20[3] = CONCAT71(sv_47, us_48);
    x20[2] = us_50;
    *(uint64_t *)((long)x20 + 0x21) = us_3f;
    *(uint64_t *)((long)x20 + 0x19) = CONCAT17(us_40, sv_47);
}

/*--------------------------------------------------------------------*/
/* FUN_001ad228 @ 0x001ad228   (est. swift_collection_init_full2)
 * Ghidra: void FUN_001ad228(...)
 * Collection-init variant forwarding to FUN_001ad190 and copying the result.
 * Confidence: medium
 * Notes: FUN_001ad190.
 */
void swift_collection_init_full2(uint64_t *out, long p2)
{
    FUN_001ad190(&sv_50, x20[0], x20[1], x20[2], x20[3], *(uint64_t *)(p2 + 0x10));
    out[1] = us_48;
    out[0] = sv_50;
    out[3] = CONCAT71(sv_37, us_38);
    out[2] = us_40;
    *(uint64_t *)((long)out + 0x21) = us_2f;
    *(uint64_t *)((long)out + 0x19) = CONCAT17(us_30, sv_37);
}

/*--------------------------------------------------------------------*/
/* FUN_001ad2a0 @ 0x001ad2a0   (est. swift_collection_init_walk)
 * Ghidra: void FUN_001ad2a0(void)
 * Initializes a collection by walking: resolves the metatype and dispatches
 * through the run-queue walk (FUN_001a6ab8).
 * Confidence: medium
 * Notes: FUN_00356940 / FUN_00353540 / FUN_00310df0 / FUN_00376820 /
 *   FUN_0034d190 / FUN_001a6ab8.
 */
void swift_collection_init_walk(void)
{
    FUN_00356940();
    FUN_00353540();
    uint64_t u1 = FUN_00310df0();
    uint64_t u2 = FUN_00348d00();
    sk_metatype(u2, u1);                    /* FUN_00376820 */
    FUN_0034d190();
    FUN_001a6ab8();
}

/*--------------------------------------------------------------------*/
/* FUN_001ad44c @ 0x001ad44c   (est. sk_sched_queue_trim_thunk2)
 * Ghidra: void FUN_001ad44c(void)
 * Thunk: forwards to FUN_001ae254.
 * Confidence: medium
 */
void sk_sched_queue_trim_thunk2(void) { FUN_001ae254(); }

/*--------------------------------------------------------------------*/
/* FUN_001ad494 @ 0x001ad494   (est. swift_buffer_foreach_elem2)
 * Ghidra: void FUN_001ad494(...)
 * Iterates a Swift buffer's elements: validates the count, resolves the
 * element pointer, and dispatches through the callback.
 * Confidence: medium
 * Notes: DAT_00658c00, FUN_001e4cbc; trap at 0x1ad59c.
 */
void swift_buffer_foreach_elem2(uint64_t p1, void (*cb)(void), uint64_t p3, uint64_t p4,
                                long p5, long p6, uint64_t p7, long p8, uint64_t p9,
                                long p10, uint64_t p11, uint64_t p12)
{
    long desc = *(long *)(p10 - 8);
    dispatch_slot(*(uint64_t *)(desc + 0x40));      /* DAT_00658c00 */
    if (!SBORROW8(p7 >> 1, p6)) {
        reg16 v = FUN_001e4cbc(p5 + *(long *)(*(long *)(p8 - 8) + 0x48) * p6,
                               (p7 >> 1) - p6);
        cb(p1, v.lo, v.hi, stack_aligned);
        if (x21 != 0)
            (**(code_fn **)(desc + 0x20))(p12, stack_aligned, p10);
        return;
    }
    __builtin_trap();                       /* 0x1ad59c */
}

/*--------------------------------------------------------------------*/
/* FUN_001ad59c @ 0x001ad59c   (est. swift_array_reserve_push2)
 * Ghidra: void FUN_001ad59c(...)
 * Reserve-and-push variant: validates the free space, reserves, and pushes
 * the element via the queue.
 * Confidence: low (inlined, indirect dispatch)
 * Notes: FUN_0035ace8 / FUN_003586fc / FUN_001a97d4 / FUN_003571a4 /
 *   FUN_00350618 / FUN_001a26e0 / FUN_001ad668; trap at 0x1ad668.
 */
void swift_array_reserve_push2(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0035ace8();
    FUN_003586fc();
    if (!SBORROW8(x9, x8_00)) {
        FUN_00359f48();
        FUN_001a97d4(p3);
        FUN_003571a4(*(uint64_t *)(x20 + 8));
        FUN_00350618();
        reg16 v = FUN_001a26e0();
        x27_fn(x8, v);
        FUN_0034a210();
        FUN_00002534();
        FUN_00348d30();
        FUN_00351300(v);
        FUN_00352c40();
        FUN_001ad668();
        FUN_0035a7a4(x30);
        return;
    }
    __builtin_trap();                       /* 0x1ad668 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ad668 @ 0x001ad668   (est. swift_array_slice_validate)
 * Ghidra: void FUN_001ad668(long *param_1, long param_2, long param_3)
 * Validates an ArraySlice buffer pointer; fatals on mismatch.
 * Confidence: high (string-matched fatal "ArraySlice.withUnsafeMutableBuff" +
 *   "Swift.ArraySlice")
 * Notes: strings at 0x005d3e20 / 0x005cdfb0.
 */
void swift_array_slice_validate(long *buf, long base, long len)
{
    if (*buf != 0 && base == *buf && buf[1] == len) return;
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_array_slice_with_unsafe_mut, 0x4e, 2,
                   s_swift_array_slice, 0x16, 2, 0x51b, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001ad6e0 @ 0x001ad6e0   (est. swift_array_reserve_inplace)
 * Ghidra: void FUN_001ad6e0(...)
 * Reserves space in place in the array, computing the element offset and
 * growing the count if the storage can absorb it. Fatals on inconsistency.
 * Confidence: low (inlined, many traps)
 * Notes: FUN_0035193c / FUN_002dc564 / FUN_0034b7e4 / FUN_00376820 /
 *   FUN_002dc5a4 / FUN_00351774; traps at 0x1ad838-0x1ad870; fatal.
 */
void swift_array_reserve_inplace(uint64_t p1, uint64_t p2, long p3)
{
    reg16 v = FUN_0035193c();
    long hi = v.hi;
    long lo = v.lo;
    if (SBORROW8(hi, lo)) __builtin_trap();         /* 0x1ad838 */
    long delta = p3 - (hi - lo);
    if (SBORROW8(p3, hi - lo)) __builtin_trap();    /* 0x1ad83c */
    long l1 = x20[2];
    long free = ((uint64_t)x20[3] >> 1) - l1;
    if (SBORROW8((uint64_t)x20[3] >> 1, l1)) __builtin_trap();  /* 0x1ad840 */
    long l11 = x20[1];
    uint64_t u6 = FUN_002dc564(*x20);
    long l7 = FUN_0034b7e4();
    long stride = *(long *)(x9 + 0x48);
    if (stride == 0) {
        FUN_00348074(1);
    } else {
        l11 = (l11 + stride * l1) -
              (l7 + ((uint64_t)*(uint8_t *)(x16 + 0x50) + 0x20 &
                     ((uint64_t)*(uint8_t *)(x16 + 0x50) ^ 0xffffffffffffffff)));
        if (stride != -1 || l11 != -0x8000000000000000) {
            if (SBORROW8(lo, l1)) __builtin_trap(); /* 0x1ad854 */
            long cnt = (stride != 0) ? l11 / stride : 0;
            if (SCARRY8(lo - l1, cnt)) __builtin_trap();    /* 0x1ad858 */
            if (SBORROW8(hi, l1)) __builtin_trap();         /* 0x1ad85c */
            if (!SCARRY8(hi - l1, cnt)) {
                if ((hi - l1) + cnt < (lo - l1) + cnt) {
                    FUN_00347d60();
                    sk_swift_fatal(0, 0, 0);       /* noreturn */
                }
                FUN_00350720();
                uint64_t u8 = FUN_00310dd8();
                uint64_t u9 = FUN_003498dc();
                sk_metatype(u9, u8);        /* FUN_00376820 */
                FUN_00350a04();
                FUN_00352ae4();
                FUN_0019c53c();
                sk_free((void *)u6);                /* FUN_0036b118 */
                long l5 = l1 + free;
                if (!SCARRY8(l1, free)) {
                    if (!SCARRY8(l5, delta)) {
                        FUN_002dc5a4(l5 + delta);
                        FUN_00351774(x30);
                        return;
                    }
                    __builtin_trap();       /* 0x1ad870 */
                }
                __builtin_trap();           /* 0x1ad86c */
            }
            __builtin_trap();               /* 0x1ad860 */
        }
        FUN_0034834c(1);
    }
    FUN_00351be0();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001ad884 @ 0x001ad884   (est. swift_range_replace_loop)
 * Ghidra: void FUN_001ad884(...)
 * Replaces a range of one collection with another, walking both in lockstep
 * and copying elements until done. Ends with the thread epilogue.
 * Confidence: low (very heavy inlining, indirect dispatch, many traps)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_003722e4, FUN_001a9ac8,
 *   FUN_0008e500; traps at 0x1adec4-0x1aded4.
 */
void swift_range_replace_loop(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                              uint64_t p5, long p6, uint64_t p7, uint64_t p8)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    long l8 = cpu.hi;
    FUN_00349b00();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_003497b4();
    FUN_00310d68(0xff, is_60);
    FUN_0034e57c();
    FUN_003515b4();
    long l6 = FUN_003722e4();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_0034926c();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00349c70();
    dispatch_slot(*(uint64_t *)(x8_01 + 0x40)); /* DAT_00658c00 */
    FUN_0034ab10();
    FUN_00352008();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00349fb8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034baa8();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a414();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_00350464();
    reg16 v19 = FUN_00355b1c();
    uint64_t u10 = v19.lo;
    uint64_t c1 = p4 >> 1;
    if (SBORROW8(c1, p3)) __builtin_trap();         /* 0x1adecc */
    uint64_t c2 = p8 >> 1;
    if (SBORROW8(c2, p7)) __builtin_trap();         /* 0x1aded0 */
    if (c1 - p3 == c2 - p7) {
        if ((c1 != p3) &&
            (l8 + *(long *)(x16 + 0x48) * p3 != p6 + *(long *)(x16 + 0x48) * p7)) {
            uint64_t r9;
            uint64_t src_i;
            if (p3 == c1) {
                r9 = 1;
                src_i = p3;
            } else {
                u10 = FUN_001a9ac8(sv_10, p3, v19.hi, l8, p3, p4, is_60);
                src_i = p3 + 1;
                if (SCARRY8(p3, 1)) __builtin_trap();       /* 0x1aded4 */
                r9 = 0;
            }
            FUN_00355f94(u10, r9);
            FUN_0035881c();
            FUN_00352554(is_68);
            FUN_0035512c();
            FUN_00351c7c();
            FUN_000839d8();
            uint64_t *pu1 = (uint64_t *)(x16_00 + 8);
            uint64_t u11 = x16_00 + 0x10 & 0xffffffffffff | 0xe3ba000000000000;
            uint64_t cur_src = c1;
            uint64_t cur_dst = p7;
            for (;;) {
                FUN_00355a14();
                FUN_0034fff0();
                FUN_000839d8();
                long off = (long)*(int *)(l6 + 0x30);
                fn17 = *(code_fn **)(x16_00 + 0x10);
                v19 = FUN_003504f4();
                fn17(v19.lo, v19.hi, x25);
                fn12 = *(code_fn **)(x16_00 + 0x20);
                fn12(x14 + off, cur_src, x25);
                FUN_0035163c(x14);
                int eq = FUN_000839f8();
                bool cond = (eq == 1);
                if (cond) {
                    FUN_0034ad40(x14 + off);
                    if (cond) {
                        fn14 = (code_fn *)*pu1;
                        FUN_00350738();
                        fn14();
                        goto loop_done_break;
                    }
                    goto loop_mid;
                }
                FUN_00355f88();
                v19 = FUN_0009e234();
                fn17(u11, v19.lo, v19.hi, x25);
                FUN_0034ad40(x14 + off);
                if (cond) {
                    FUN_00354ab0();
                    FUN_003509bc();
                    x8_02_fn();
                    goto loop_mid;
                }
                u10 = FUN_00350d24();
                v19 = FUN_003537f0(u10, x14 + off);
                x8_04_fn(v19.lo, v19.hi, is_60);
                FUN_00353124(&stack_40);
                FUN_00350adc();
                FUN_0034d180();
                uint32_t ok5 = x8_05_fn();
                fn14 = *(code_fn **)(x16 + 8);
                fn14(l6, is_60);
                FUN_003509bc();
                fn14();
                fn14 = (code_fn *)*pu1;
                FUN_00350738();
                v19 = fn14();
                if ((ok5 & 1) != 0) goto loop_done_break;
loop_mid:
                u10 = v19.lo;
                bool dst_done = (cur_dst == c2);
                if (dst_done) {
                    r9 = 1;
                    cur_dst = c2;
                } else {
                    u10 = FUN_001a9ac8(sv_28, cur_dst, v19.hi, p6, p7, sv_d8, is_60);
                    bool carry = SCARRY8(cur_dst, 1);
                    cur_dst++;
                    dst_done = (cur_dst == 0);
                    if (carry) __builtin_trap();        /* 0x1adec4 */
                    r9 = 0;
                }
                FUN_00352c8c(u10, r9);
                FUN_00351c7c();
                FUN_000839d8();
                off = (long)*(int *)(l6 + 0x30);
                fn12(sv_a8, sv_10, x25);
                FUN_00351dfc(sv_a8 + off);
                fn12();
                FUN_0034ad40(sv_a8);
                if (dst_done) {
                    FUN_0034ad40(sv_a8 + off);
                    if (!dst_done) {
                        FUN_0034d688();
                        FUN_003510b8();
                        x8_11_fn();
                        goto loop_exit;
                    }
                    FUN_00350b78(*pu1);
                    x8_06_fn();
                } else {
                    FUN_00355074();
                    v19 = FUN_003504c4();
                    fn17(u11, v19.lo, v19.hi, x25);
                    FUN_0034ad40(sv_a8 + off);
                    if (dst_done) {
                        FUN_00354ab0();
                        FUN_00350aa0();
                        x8_10_fn();
                        goto loop_exit2;
                    }
                    u10 = FUN_00350d24();
                    v19 = FUN_003537f0(u10, sv_a8 + off);
                    x8_07_fn(v19.lo, v19.hi, is_60);
                    FUN_003520b4(&stack_40);
                    FUN_00350adc();
                    FUN_0034d364();
                    cur_src = x8_08_fn();
                    fn12 = *(code_fn **)(x16 + 8);
                    fn12(l6, is_60);
                    FUN_00350aa0();
                    fn12();
                    FUN_00350b78(*pu1);
                    x8_09_fn();
                    if ((cur_src & 1) == 0) goto loop_exit;
                }
                if (src_i == c1) {
                    u10 = 1;
                    src_i = c1;
                } else {
                    v19 = FUN_00354cfc();
                    FUN_001a9ac8(v19.lo, v19.hi, l8, p3, p4, is_60);
                    bool carry2 = SCARRY8(src_i, 1);
                    src_i++;
                    if (carry2) __builtin_trap();       /* 0x1adec8 */
                    u10 = 0;
                }
                FUN_00351c7c(sv_10, u10);
                FUN_000839d8();
                cur_src = x25;
            }
loop_done_break:
            fn14(sv_10, x25);
            break;
loop_exit2:
loop_exit:
            u10 = 0;
        } else {
            u10 = 1;
        }
    } else {
        u10 = 0;
    }
    sk_thread_epilogue(u10, cpu.lo);        /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aded4 @ 0x001aded4   (est. swift_collection_range_equal)
 * Ghidra: uint FUN_001aded4(...)
 * Tests whether two collection ranges are equal: forwards to the range-replace
 * loop FUN_001ad884 and returns the low bit.
 * Confidence: medium
 * Notes: FUN_001ad884.
 */
uint32_t swift_collection_range_equal(long a, long b, long c, uint64_t d, uint64_t e)
{
    uint32_t r = FUN_001ad884(a, *(uint64_t *)(a + 8), *(uint64_t *)(a + 0x10),
                              *(uint64_t *)(a + 0x18), e, *(uint64_t *)(b + 8),
                              *(uint64_t *)(b + 0x10), *(uint64_t *)(b + 0x18),
                              *(uint64_t *)(c + 0x10),
                              *(uint64_t *)((d & 0xfffffffffffffffe) - 8));
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001adf20 @ 0x001adf20   (est. swift_range_apply_loop)
 * Ghidra: void FUN_001adf20(...)
 * Applies a function over a range of elements: iterates from param_4 to
 * cap>>1, dispatching each element through the element handler.
 * Confidence: low (indirect dispatch, unaff regs)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_002298d4, FUN_0031945c,
 *   FUN_001a9ac8, FUN_0008e500; traps at 0x1ae040 / 0x1ae03c.
 */
void swift_range_apply_loop(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                            uint64_t p5, uint64_t p6, uint64_t p7)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    uint64_t u3 = p4;
    FUN_0007c028();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00349068();
    uint64_t cap = p5 >> 1;
    if (SBORROW8(cap, u3)) __builtin_trap();        /* 0x1ae040 */
    thunk_FUN_002298d4(cap - u3);
    if (p4 != cap) {
        fn2 = (code_fn *)FUN_0031945c(p7);
        u3 = p4;
        do {
            reg16 v = FUN_00352e3c();
            FUN_001a9ac8(v.lo, v.hi, p3, p4, p5, p6);
            uint64_t next = u3 + 1;
            if (SCARRY8(u3, 1)) __builtin_trap();   /* 0x1ae03c */
            fn2(x12, p6, p7);
            FUN_003507d4(*(uint64_t *)(x16 + 8));
            x8_00_fn();
            u3++;
        } while (next != cap);
    }
    sk_thread_epilogue(x1);                 /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001ae040 @ 0x001ae040   (est. sk_sched_key_stage4)
 * Ghidra: void FUN_001ae040(void)
 * Fourth scheduler key stage: derives a per-CPU byte, mixes it with the
 * reversed key string, and runs the range-apply loop + key mix.
 * Confidence: medium
 * Notes: FUN_00355018 / FUN_00348c48 / FUN_0034d264 / FUN_001adf20 /
 *   FUN_001a8564; string at 0x004e7a30.
 */
void sk_sched_key_stage4(void)
{
    FUN_00355018();
    uint8_t b = FUN_00348c48();
    reg16 v = FUN_0034d264(b, s_reversed_key._16_8_, b ^ s_reversed_key._0_8_);
    FUN_001adf20(v.lo, v.hi, v.hi);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_001ae0c8 @ 0x001ae0c8   (est. swift_range_apply_meta)
 * Ghidra: void FUN_001ae0c8(...)
 * Applies a function over a range using the SHA-256 IV state: initializes the
 * key state, runs the range-apply loop, and mixes.
 * Confidence: medium
 * Notes: FUN_001a84f4 (IV init) / FUN_001adf20 / FUN_001a8564.
 */
void swift_range_apply_meta(uint64_t p1, long p2, uint64_t p3)
{
    uint64_t u1 = *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8);
    FUN_001a84f4(aus_78);
    FUN_001adf20(aus_78, x1, *(uint64_t *)(x20 + 8), *(uint64_t *)(x20 + 0x10),
                 *(uint64_t *)(x20 + 0x18), *(uint64_t *)(p2 + 0x10), u1);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_001ae128 @ 0x001ae128   (est. swift_array_apply_push)
 * Ghidra: void FUN_001ae128(...)
 * Applies a push over the array: reserves storage and dispatches. Traps on
 * borrow.
 * Confidence: low (inlined, indirect)
 * Notes: FUN_003586fc / FUN_001a97d4 / FUN_003571a4 / FUN_00350518 /
 *   FUN_001a26e0 / FUN_001ad668 / FUN_001df428; trap at 0x1ae20c.
 */
void swift_array_apply_push(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    FUN_003586fc();
    if (!SBORROW8(x9, x8)) {
        FUN_003537fc();
        FUN_001a97d4(p4);
        FUN_003571a4(*(uint64_t *)(x20 + 8));
        FUN_00350518();
        reg16 v = FUN_001a26e0();
        FUN_00352c4c(p1, v);
        FUN_003543c4();
        FUN_001df428();
        FUN_0034a210();
        FUN_00002534();
        FUN_00348d30();
        FUN_00350b48(v);
        FUN_001ad668();
        return;
    }
    __builtin_trap();                       /* 0x1ae20c */
}

/*--------------------------------------------------------------------*/
/* FUN_001ae20c @ 0x001ae20c   (est. sk_sched_queue_trim_thunk3)
 * Ghidra: void FUN_001ae20c(void)
 * Thunk: forwards to FUN_001ae254.
 * Confidence: medium
 */
void sk_sched_queue_trim_thunk3(void) { FUN_001ae254(); }

/*--------------------------------------------------------------------*/
/* FUN_001ae254 @ 0x001ae254   (est. swift_buffer_apply_finalize)
 * Ghidra: void FUN_001ae254(void)
 * Finalizes a Swift buffer apply: runs the type/init sequence and dispatches
 * through the saved callback.
 * Confidence: low (inlined, indirect)
 * Notes: FUN_003563c4 / FUN_00357198 / FUN_0034a210 / FUN_00002534 /
 *   FUN_00353e5c / FUN_003534f8 / FUN_00352ea8 / FUN_0035767c /
 *   FUN_003563a8.
 */
void swift_buffer_apply_finalize(void)
{
    FUN_003563c4();
    is_40 = FUN_00357198();
    is_30 = x6;
    is_38 = x7;
    FUN_0034a210();
    FUN_00002534();
    uint64_t u = FUN_00353e5c();
    FUN_003534f8(u, &stack_20);
    FUN_00352ea8();
    FUN_0035767c();
    (*is_b8)();                       /* callback */
    FUN_003563a8(x9);
}

/*--------------------------------------------------------------------*/
/* FUN_001ae2e0 @ 0x001ae2e0   (est. swift_array_release)
 * Ghidra: void FUN_001ae2e0(void)
 * Releases a Swift Array: runs the teardown helpers and reserves.
 * Confidence: medium
 * Notes: FUN_00358fa8 / FUN_0006f6b4 / FUN_001a964c.
 */
void swift_array_release(void)
{
    FUN_00358fa8();
    FUN_0006f6b4();
    FUN_001a964c();
}

/*--------------------------------------------------------------------*/
/* FUN_001ae30c @ 0x001ae30c   (est. sk_sched_queue_foreach_apply)
 * Ghidra: void FUN_001ae30c(...)
 * Iterates the run queue applying a callback, dispatching through the saved
 * handler slots. Ends with the thread teardown.
 * Confidence: low (heavy inlining, indirect dispatch, in_ZR condition)
 * Notes: FUN_00353cfc / FUN_0008f6f4 / FUN_00027754 / FUN_00377824 /
 *   DAT_00658c00 / FUN_00377bec / FUN_00310d80 / FUN_0019e578 /
 *   FUN_00351348 / FUN_00353d14.
 */
void sk_sched_queue_foreach_apply(uint64_t p1, uint64_t p2, void (*cb)(uint64_t), uint64_t p4)
{
    FUN_00353cfc();
    FUN_0008f6f4(p4);
    FUN_00027754();
    FUN_00351ad4();
    FUN_0034e81c();
    FUN_003513d8();
    FUN_00377824();                         /* lock */
    FUN_0034f554();
    FUN_00310d68();
    uint64_t u1 = FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b0d4();
    FUN_003499c8();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034af20();
    FUN_00350308();
    FUN_00377824();                         /* lock */
    FUN_00348ce8();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b05c();
    FUN_003521a4();
    FUN_00352680();
    FUN_003511a8();
    x9_fn();
    FUN_0034b278();
    FUN_000e72b0();
    FUN_00377bec();
    FUN_00355b74();
    FUN_00357e44();
    for (;;) {
        cb(x22);
        FUN_0034c4bc();
        if (ZR) {
            FUN_00352260();
            uint64_t u3 = x8_02_fn();
            FUN_00351a98(u3, u1);
            x8_03_fn();
            FUN_0035050c();
            reg16 v = FUN_00310d80();
            FUN_003488f4(v.lo, v.hi, v.lo);
            FUN_0019e578(&stack_8);
            goto foreach_done;
        }
        FUN_003509b0(*x26);
        x8_fn();
        FUN_00357050();
        uint64_t u2 = x8_00_fn();
        if (x21 != 0) {
            FUN_00350c38(*x25);
            x8_04_fn();
            FUN_00352260();
            x8_05_fn();
            sk_free((void *)is_8);            /* FUN_0036b118 */
            goto foreach_done;
        }
        if ((u2 & 1) == 0) {
            FUN_00350c38(*x25);
            x8_01_fn();
        } else {
            FUN_0035050c();
            FUN_00310d80();
            FUN_00355c1c();
            FUN_0019e538();
        }
    }
foreach_done:
    uint64_t u1b = FUN_00351348();
    FUN_00353d14(u1b, is_18);
}

/*--------------------------------------------------------------------*/
/* FUN_001ae564 @ 0x001ae564   (est. sk_sched_queue_foreach_apply2)
 * Ghidra: void FUN_001ae564(void)
 * Queue-foreach variant with the full lock sequence and saved-handler
 * dispatch.
 * Confidence: low (very heavy inlining, indirect dispatch)
 * Notes: FUN_00353cfc / FUN_00359634 / FUN_00377824 / DAT_00658c00 /
 *   FUN_00377bec / FUN_000a68f4 / FUN_00310d80 / FUN_0019e578 /
 *   FUN_00351348 / FUN_00353d14.
 */
void sk_sched_queue_foreach_apply2(void)
{
    FUN_00353cfc();
    FUN_00359634();
    uint64_t *pu5 = x3;
    uint64_t u1 = FUN_00352590();
    FUN_00377824(u1, pu5);                  /* lock */
    FUN_0034ee68();
    FUN_00310d68();
    u1 = FUN_000a6f88();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b0d4();
    FUN_003499f0();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034af20();
    FUN_0034998c();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00348f38();
    FUN_00350308();
    FUN_00377824();                         /* lock */
    FUN_00348d7c();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034d3c4();
    uint64_t u2 = FUN_003521a4();
    FUN_00356a14(*(uint64_t *)(x16 + 0x10), u2, is_fff8);
    x8_00_fn();
    FUN_00352680(x3);
    FUN_003511a8();
    x9_fn();
    FUN_0034b278();
    FUN_000e72b0();
    u2 = FUN_00377bec();
    fn3 = (code_fn *)FUN_000a68f4();
    FUN_00357e44();
    for (;;) {
        fn3(x25, u2);
        FUN_0034b2c8();
        if (ZR) {
            FUN_00352260();
            u2 = x8_04_fn();
            FUN_00351a98(u2, u1);
            x8_05_fn();
            FUN_00350488();
            reg16 v = FUN_00310d80();
            FUN_003488f4(v.lo, v.hi, v.lo);
            FUN_0019e578(&stack_8);
            goto fae_done;
        }
        FUN_003509b0(*x3);
        x8_01_fn();
        FUN_00357050();
        uint64_t u4 = x8_02_fn();
        if (x21 != 0) {
            FUN_00350b00(*x25);
            x8_06_fn();
            FUN_00352260();
            x8_07_fn();
            sk_free((void *)is_8);            /* FUN_0036b118 */
            goto fae_done;
        }
        if ((u4 & 1) == 0) {
            FUN_00350b00(*x25);
            x8_03_fn();
        } else {
            FUN_00350488();
            FUN_00310d80();
            FUN_00355c1c();
            FUN_0019e538();
        }
    }
fae_done:
    u1 = FUN_00351348();
    FUN_00353d14(u1, is_18);
}

/*--------------------------------------------------------------------*/
/* FUN_001ae82c @ 0x001ae82c   (est. swift_optional_release)
 * Ghidra: void FUN_001ae82c(undefined8 *param_1, long *param_2)
 * Releases a Swift optional value: if the payload is non-empty, dispatches the
 * value destructor through the type vtable (*param_2+0xe8); otherwise zeroes
 * the output.
 * Confidence: medium
 * Notes: FUN_0021398c; indirect call via (*param_2+0xe8).
 */
void swift_optional_release(uint64_t *out, long *desc)
{
    long a = desc[2];
    long b = desc[3];
    uint64_t r = FUN_0021398c(a, b, desc[4], desc[5]);
    if ((r & 1) == 0) {
        (**(code_fn **)(*desc + 0xe8))(out, a, b);
    } else {
        out[3] = 0;
        out[2] = 0;
        out[5] = 0;
        out[4] = 0;
        out[1] = 0;
        out[0] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001ae8a8 @ 0x001ae8a8   (est. swift_unicode_scalar_decode)
 * Ghidra: ulong FUN_001ae8a8(ulong param_1, ulong param_2)
 * Decodes the Unicode scalar at the given index of a Swift string, handling
 * both inline (small) and heap-backed representations. Fatals on invalid
 * UTF-8 via the Unicode helpers.
 * Confidence: high (Swift UnicodeHelpers fatal + UTF-8 decode switch)
 * Notes: FUN_00167404 / FUN_002a9ba8 / FUN_001afa84; string at 0x005ce730.
 */
uint64_t swift_unicode_scalar_decode(uint64_t data, uint64_t disc)
{
    uint64_t idx = data & 0xffffffffffff;
    if ((disc & 0x2000000000000000) != 0) idx = disc >> 0x38 & 0xf;
    if (idx == 0) return 0x100000000;
    uint64_t r = FUN_00167404(0xf, data, disc);
    if ((disc >> 0x3c & 1) != 0)
        FUN_001afa84(s_Fatal_error, 0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                     s_swift_unicode_helpers, 0x1a, 2, 0xfd, 1);
    if ((disc >> 0x3d & 1) == 0) {
        if ((data >> 0x3c & 1) == 0) {
            r = FUN_002a9ba8(data, disc);
        } else {
            r = (disc & 0xfffffffffffffff) + 0x20;
        }
        return swift_utf8_decode((uint8_t *)(r + (idx >> 0x10)));
    }
    /* inline small-string path */
    reg16 local = { data, disc & 0xffffffffffffff };
    return swift_utf8_decode((uint8_t *)((long)&local + (idx >> 0x10)));
}

/* helper: decode one UTF-8 scalar from a byte pointer */
static uint64_t swift_utf8_decode(const uint8_t *p)
{
    uint8_t b0 = *p;
    if ((int8_t)b0 >= 0) return (uint64_t)b0;
    switch (sk_lzcount((uint32_t)b0 << 0x18 ^ 0xffffffff)) {
    default:
        return (uint64_t)b0;
    case 2:
        return (uint64_t)p[1] & 0x3f | ((uint64_t)b0 & 0x1f) << 6;
    case 3: {
        uint8_t b2 = p[2];
        uint64_t v = ((uint64_t)b0 & 0xf) << 0xc | ((uint64_t)p[1] & 0x3f) << 6;
        return v | (uint64_t)b2 & 0x3f;
    }
    case 4: {
        uint8_t b3 = p[3];
        uint64_t v = ((uint64_t)b0 & 0xf) << 0x12 | ((uint64_t)p[1] & 0x3f) << 0xc |
                     ((uint64_t)p[2] & 0x3f) << 6;
        return v | (uint64_t)b3 & 0x3f;
    }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001aea6c @ 0x001aea6c   (est. swift_string_next_scalar)
 * Ghidra: undefined8 FUN_001aea6c(ulong param_1, ulong param_2)
 * Returns the next Unicode scalar of a Swift string, or 0 at the end.
 * Confidence: medium
 * Notes: FUN_00267510.
 */
uint64_t swift_string_next_scalar(uint64_t data, uint64_t disc)
{
    uint64_t n = data & 0xffffffffffff;
    if ((disc & 0x2000000000000000) != 0) n = disc >> 0x38 & 0xf;
    if (n != 0) return FUN_00267510(0xf, data, disc);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001aeab4 @ 0x001aeab4   (est. sk_sched_queue_foreach_full)
 * Ghidra: void FUN_001aeab4(void)
 * Iterates the run queue under the full lock sequence, dispatching each
 * element through the saved handler slots. Ends with the thread epilogue.
 * Confidence: low (heavy inlining, indirect dispatch)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec,
 *   FUN_0008e388, FUN_000839d8, FUN_0008e500.
 */
void sk_sched_queue_foreach_full(void)
{
    sk_cpu_current();                       /* FUN_0008e518 */
    FUN_0035583c();
    FUN_0034e808();
    FUN_00351900();
    FUN_00377824();                         /* lock */
    FUN_00348ce8();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_00348a34();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b8bc();
    FUN_0034fe64();
    FUN_0008e388();
    x9_fn();
    FUN_00310924();
    FUN_00351184();
    FUN_0008e388();
    x9_00_fn();
    FUN_0034e52c();
    FUN_00377bec();
    FUN_00351ef8();
    FUN_0034f1c4();
    FUN_00351b20();
    uint64_t ok = x8_01_fn();
    fn2 = *(code_fn **)(x16 + 8);
    FUN_00350b00();
    fn2();
    if ((ok & 1) == 0) {
        FUN_00352ecc();
        FUN_003513f0(aus_20);
        x8_02_fn();
        FUN_003530d8();
        FUN_00348b94();
        FUN_00377824();                     /* lock */
        FUN_0034ab20();
        (**(code_fn **)(x16_00 + 0x10))(x8);
        FUN_00351d00();
        x20_fn();                           /* callback */
        FUN_00351384();
        fn2();
        FUN_0034befc(x8);
    } else {
        FUN_00351384();
        fn2();
        FUN_00348b94();
        FUN_00377824();                     /* lock */
        FUN_00350744(x8);
    }
    FUN_000839d8();
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001aec78 @ 0x001aec78   (est. sk_sched_queue_next_avail)
 * Ghidra: void FUN_001aec78(void)
 * Advances to the next available run-queue slot; traps if none.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_00353aa0 / FUN_00349178 / FUN_00351e84 / FUN_003548a0 /
 *   FUN_0034b2a8 / FUN_0034c664 / trap at 0x1aed4c.
 */
void sk_sched_queue_next_avail(void)
{
    FUN_00353aa0();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00349178();
    FUN_00351e84();
    FUN_003548a0();
    x9_fn();
    FUN_0034b2a8();
    if (!ZR) {
        FUN_0034c664();
        (**(code_fn **)(x16_00 + 0x20))();
        return;
    }
    FUN_003509bc(*(uint64_t *)(x16 + 8));
    x8_00_fn();
    __builtin_trap();                       /* 0x1aed4c */
}

/*--------------------------------------------------------------------*/
/* FUN_001aed4c @ 0x001aed4c   (est. sk_sched_runqueue_tick)
 * Ghidra: void FUN_001aed4c(...)
 * Scheduler run-queue tick: processes pending work with full lock/accounting,
 * dispatching through the saved handler slots, and re-arms. Ends with the
 * thread epilogue or fatal.
 * Confidence: low (extremely heavy inlining, dozens of indirect dispatches)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_00377824, FUN_00377bec,
 *   FUN_00100c38, FUN_0008e500; fatal FUN_001afe4c.
 */
void sk_sched_runqueue_tick(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                            uint64_t p5, uint64_t p6)
{
    reg16 cpu = sk_cpu_current();           /* FUN_0008e518 */
    long l9 = cpu.hi;
    uint64_t u3 = FUN_00027754(p4);
    FUN_0034be54();
    FUN_0034f764();
    FUN_00351100();
    FUN_00377824();                         /* lock */
    FUN_0034ab20();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034a2ac();
    FUN_003549d8(*(uint64_t *)(l9 - 8));
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_00348b5c();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034aa28();
    FUN_003499c8();
    dispatch_slot(*(uint64_t *)(x8_01 + 0x40)); /* DAT_00658c00 */
    FUN_00348f50();
    FUN_00355ab4(p6);
    FUN_003508e4();
    FUN_00351f1c();
    FUN_00377824();                         /* lock */
    FUN_0034ab20();
    FUN_0007c1a4();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034b2f8();
    FUN_00310a14(p6);
    FUN_00350c44();
    FUN_003514e8();
    uint64_t ok = x8_02_fn();
    if ((ok & 1) != 0) {
        FUN_00100c38();
        FUN_003511cc();
        FUN_00377bec();
        uint64_t u5 = FUN_003494fc();
        FUN_00350e94(u5, 0x100);
        x9_fn();
        FUN_0034d954();
        FUN_00355af8();
        FUN_00351dfc();
        x9_00_fn();
        FUN_00310ad4(p6);
        FUN_00351ef8();
        FUN_00310954();
        FUN_00350a7c();
        FUN_00351300();
        ok = x8_03_fn();
        FUN_00352870();
        FUN_00350618();
        x9_01_fn();
        if ((ok & 1) == 0) {
            FUN_003482c4();
            goto tick_fatal;
        }
    }
    fn6 = (code_fn *)FUN_00310a44(p6);
    FUN_003514e8();
    long l7 = fn6();
    FUN_00357664();
    FUN_003534a4();
    FUN_00351450();
    long l8 = x8_04_fn();
    if (l7 < l8) goto tick_done;
    FUN_00310aa4();
    FUN_00353f5c();
    FUN_000e15d8();
    x9_02_fn();
    FUN_003549a8(u3);
    FUN_00351160();
    uint32_t u1 = x26_fn();
    FUN_00350524();
    uint32_t u2 = x8_02_fn();
    if (((u1 ^ u2) & 1) == 0) {
        FUN_0034c368();
        FUN_00350c38();
        l9 = x8_08_fn();
        FUN_00350524();
        l7 = fn6();
        if (l9 < l7) {
            FUN_00350a4c(p6);
            FUN_00354b08();
            reg16 v = FUN_00350630();
            FUN_003518f4(v.lo, v.hi, u3);
            x9_04_fn();
            FUN_00348e78(p6);
            FUN_00350914();
            FUN_00351584();
            ok = x8_09_fn();
            FUN_00354364();
            FUN_00350a70();
            x8_10_fn();
        } else {
            FUN_00358cc8();
            FUN_00358534();
            FUN_003513d8();
            x8_13_fn();
            FUN_0034d1fc();
            FUN_0034f594(sv_50);
            FUN_0034facc();
            x9_06_fn();
            FUN_00348e78(u3);
            FUN_00350b6c();
            FUN_00351b78();
            ok = x8_14_fn();
            fn6 = *(code_fn **)(x16 + 8);
            FUN_003508b4();
            fn6();
            FUN_00350630();
            fn6();
        }
        if ((ok & 1) == 0) goto tick_done;
    } else {
        FUN_00350c38();
        ok = x26_fn();
        FUN_0034c368();
        FUN_00350c38();
        l7 = x8_05_fn();
        FUN_00350524();
        l8 = fn6();
        if ((ok & 1) == 0) {
            if (l7 < l8) {
                FUN_0034d53c();
                FUN_00356958(x25, sv_30, l9, u3);
                x9_05_fn();
                FUN_00348e78(p6);
                FUN_00351324();
                FUN_003528ac();
                ok = x8_11_fn();
                FUN_0035072c(*(uint64_t *)(x16_00 + 8));
                x8_12_fn();
            } else {
                FUN_0034ad00();
                FUN_0035072c();
                FUN_0035130c();
                FUN_00377bec();
                FUN_003493ec();
                FUN_00354088();
                FUN_0034bea4();
                x9_11_fn();
                FUN_0034e784();
                FUN_00352c1c();
                FUN_003508d8();
                x9_12_fn();
                FUN_0034b288();
                FUN_00310b08();
                FUN_0034e054();
                FUN_003528ac();
                ok = x8_18_fn();
                FUN_0035a578();
                FUN_00351160();
                x9_13_fn();
                if ((ok & 1) == 0) {
                    FUN_00353154();
                    x8_21_fn(sv_30, l9);
                    goto tick_done;
                }
                reg16 v = FUN_00350bf0(*(uint64_t *)(x16_00 + 0x10));
                x8_19_fn(v.lo, v.hi, p3);
                FUN_00355604();
                FUN_00350a4c();
                v = FUN_00351160(sv_50);
                FUN_00351154(v.lo, v.hi, p6);
                x9_14_fn();
                FUN_00348e78(x26);
                FUN_00350738();
                FUN_00351b78();
                ok = x8_20_fn();
                fn6 = *(code_fn **)(x16 + 8);
                FUN_0035084c();
                fn6();
                FUN_00350630();
                fn6();
            }
            if ((ok & 1) == 0) goto tick_done;
        }
        if (l8 < l7) {
            FUN_00358cc8();
            FUN_00358534();
            FUN_003516a8();
            x8_06_fn();
            FUN_00355604();
            FUN_00350a4c();
            FUN_00353a84();
            FUN_00351dfc();
            FUN_00351154();
            x9_03_fn();
            FUN_00348e78(p6);
            FUN_00350b6c();
            FUN_00351b78();
            ok = x8_07_fn();
            fn6 = *(code_fn **)(x16 + 8);
            FUN_003508b4();
            fn6();
            FUN_00350630();
            fn6();
            if ((ok & 1) == 0) goto tick_done;
        }
        FUN_0034ad00();
        FUN_00350bb4(x1);
        FUN_00377bec();
        FUN_00349370();
        FUN_0034c234(sv_68);
        x9_07_fn();
        FUN_0034e784();
        FUN_003531a8();
        FUN_0035056c();
        x9_08_fn();
        FUN_00355604();
        FUN_00348e78();
        FUN_0034ee98();
        ok = x8_15_fn();
        fn6 = *(code_fn **)(x16 + 8);
        FUN_0035084c();
        fn6();
        if ((ok & 1) == 0) {
            FUN_0034d53c();
            FUN_00350078(x25);
            FUN_00356958();
            x9_09_fn();
            FUN_00348e78(p6);
            FUN_003510dc();
            FUN_003528ac();
            ok = x8_16_fn();
            FUN_00354364();
            FUN_00350618();
            x8_17_fn();
            if ((ok & 1) == 0) goto tick_done;
        }
        FUN_003508b4();
        fn6();
    }
    FUN_00350410();
    FUN_00348194();
tick_fatal:
    FUN_003523f0();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
tick_done:
    FUN_003506cc();
    FUN_0034e014(x8, cpu.lo);
    x9_10_fn();
    sk_thread_epilogue();                   /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_001af528 @ 0x001af528   (est. swift_optional_read_flag)
 * Ghidra: uint FUN_001af528(uint *param_1, undefined8 param_2, long param_3, undefined8 param_4)
 * Reads an optional flag from a Swift Optional: returns the byte value plus a
 * "has value" bit. Handles both direct and heap-backed representations.
 * Confidence: high (Swift Optional pattern)
 * Notes: FUN_00354fc0 / FUN_00377824 / FUN_00319688; tags 0x6768d0/0x676518.
 */
uint32_t swift_optional_read_flag(uint32_t *p, uint64_t p2, long p3, uint64_t p4)
{
    if (ZR) {
        long l4 = FUN_00354a58();
        reg16 v = FUN_00354a4c();
        FUN_00350530(v.lo, v.hi, 0x6768d0);
        long l5 = FUN_00377824();
        if (l5 != l4) goto opt_fatal;
        bool has = (*p & 0xff80) != 0;
        uint32_t flag = has ? 0 : *p;
        return flag & 0xff | (uint32_t)has << 8;
    }
    FUN_00354040();
    bool direct = (p3 == x8);
    if (direct) {
        reg16 v = FUN_00354a4c();
        FUN_00350530(v.lo, v.hi, 0x676518);
        FUN_00377824();
        FUN_00357d64();
        if (!direct) goto opt_fatal;
        if (*p == 0) {
            FUN_00347f2c();
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        uint32_t v7 = *p - 1;
        uint32_t v1 = (uint32_t)(char)v7;
        uint32_t flag = v7 >> 7 & 1;
        v7 = v1 & ((int32_t)v1 >> 0x1f ^ 0xffffffffU);
        return v7 & 0xff | flag << 8;
    }
    uint64_t u6 = FUN_00319688(p4);
    FUN_0034bfb4(u6);
    uint32_t flag = x8_00_fn();
    uint32_t v7 = (flag < 0x80) ? flag : 0;
    return v7 & 0xff | (uint32_t)(0x7f < flag) << 8;
opt_fatal:
    FUN_003488bc(1);
    FUN_00349844();
    FUN_00350a94();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001af67c @ 0x001af67c   (est. swift_optional_fatal)
 * Ghidra: void FUN_001af67c(void)
 * Fatal path for invalid Swift Optional access.
 * Confidence: medium
 * Notes: fatal FUN_001afe4c.
 */
void swift_optional_fatal(void)
{
    FUN_003488bc(1);
    FUN_00349844();
    FUN_00350a94();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001af6b0 @ 0x001af6b0   (est. sk_sched_queue_next_avail2)
 * Ghidra: void FUN_001af6b0(void)
 * Advance-to-next-available-slot variant; fatals (not trap) when exhausted.
 * Confidence: low (indirect dispatch)
 * Notes: FUN_00353aa0 / FUN_00349178 / FUN_00351e84 / FUN_003548a0 /
 *   FUN_0034c664 / FUN_000839d8 / fatal FUN_001afe4c.
 */
void sk_sched_queue_next_avail2(void)
{
    FUN_00353aa0();
    FUN_000a6f88();
    dispatch_slot(*(uint64_t *)(x8 + 0x40));/* DAT_00658c00 */
    FUN_00349178();
    FUN_00351e84();
    FUN_003548a0();
    x9_fn();
    FUN_0034b2a8();
    if (!ZR) {
        FUN_0034c664();
        (**(code_fn **)(x16_00 + 0x20))();
        return;
    }
    FUN_003509bc(*(uint64_t *)(x16 + 8));
    x8_00_fn();
    FUN_00348128();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001af7c4 @ 0x001af7c4   (est. swift_optional_decode)
 * Ghidra: void FUN_001af7c4(byte *param_1, uint *param_2, undefined8 param_3, long param_4,
 *                           undefined8 param_5)
 * Decodes a Swift Optional payload into a value+flag pair, handling both the
 * tagged and heap-backed representations. Fatals on wrong type cast or nil
 * unsafely-unwrapped.
 * Confidence: high (string-matched fatal "_identityCast to wrong type" +
 *   "unsafelyUnwrapped of nil optional" + "Swift.Optional")
 * Notes: FUN_00002534 / FUN_00377824 / FUN_00319688; tags 0x6768d0/0x676518;
 *   strings at 0x005ce210 / 0x005ce230 / 0x005ce1c0 / 0x005ce1f0.
 */
void swift_optional_decode(uint8_t *out, uint32_t *p, uint64_t p3, long p4, uint64_t p5)
{
    uint32_t v;
    bool has;
    if (p4 == 0x6768d0) {
        long l4 = FUN_00002534(0x6560f0, (void*)0x004e7ed8);
        long l5 = FUN_00377824(0, p5, 0x6768d0, (void*)0x00612b58, (void*)0x00612b90);
        if (l5 != l4) goto wrong_type;
        has = (*p & 0xff80) != 0;
        v = has ? 0 : *p;
    } else if (p4 == 0x676518) {
        long l4 = FUN_00377824(0, p5, 0x676518, (void*)0x00612b58, (void*)0x00612b90);
        if (l4 != 0x676bd0) goto wrong_type;
        if (*p == 0)
            sk_swift_fatal(s_Fatal_error, 0xb, 2, s_unsafely_unwrapped_nil, 0x21, 2,
                           s_swift_optional, 0x14, 2, 0x179, 1);
        uint32_t v7 = *p - 1;
        uint8_t b = (uint8_t)v7;
        b = b & ((int8_t)b >> 0x1f ^ 0xffU);
        has = (bool)((uint8_t)(v7 >> 7) & 1);
        out[0] = b;
        out[1] = has;
        return;
    } else {
        fn6 = (code_fn *)FUN_00319688(p5);
        uint32_t u3 = fn6(p, p4, p5);
        v = (u3 < 0x80) ? u3 : 0;
        has = 0x7f < u3;
    }
    out[0] = (uint8_t)v;
    out[1] = (uint8_t)has;
    return;
wrong_type:
    sk_swift_fatal(s_Fatal_error, 0xb, 2, s_identity_cast_wrong_type, 0x1b, 2,
                   s_swift_builtin, 0x13, 2, 0x6d, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001af990 @ 0x001af990   (est. swift_collection_is_empty)
 * Ghidra: char FUN_001af990(...)
 * Returns whether a Swift collection is empty: runs the emptiness check and
 * folds the flag.
 * Confidence: medium
 * Notes: FUN_0034c034 / FUN_00354474 / FUN_00084180.
 */
char swift_collection_is_empty(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0034c034();
    FUN_00354474(p3);
    FUN_00084180(&sv_32);                /* yield */
    x9_fn();
    if (sv_32 < 0) sv_32 = '\x01';
    char c = '\0';
    if (sv_31 != '\x01') c = sv_32;
    return c;
}

/*--------------------------------------------------------------------*/
/* FUN_001afa24 @ 0x001afa24   (est. swift_collection_is_empty_out)
 * Ghidra: void FUN_001afa24(undefined8 *param_1)
 * Stores the collection emptiness result + flag into the output.
 * Confidence: medium
 * Notes: FUN_001af990.
 */
void swift_collection_is_empty_out(uint64_t *out)
{
    uint64_t v = FUN_001af990();
    *out = v;
    *(uint8_t *)(out + 1) = w1;
}

/*--------------------------------------------------------------------*/
/* FUN_001afa54 @ 0x001afa54   (est. swift_string_precondition_thunk)
 * Ghidra: void FUN_001afa54(void)
 * Thunk: forwards to FUN_001afd38.
 * Confidence: medium
 */
void swift_string_precondition_a(void) { FUN_001afd38(); }

/*--------------------------------------------------------------------*/
/* FUN_001afa84 @ 0x001afa84   (est. swift_string_fatal_precondition)
 * Ghidra: void FUN_001afa84(...)
 * Swift string precondition-fatal path: validates the payload, computes the
 * message length, and formats/traps with the fatal message. Used by the
 * UnicodeHelpers path.
 * Confidence: high (Swift fatal message construction)
 * Notes: FUN_0035193c / FUN_00255d4c / thunk_FUN_0036b270 / FUN_00356364 /
 *   FUN_002a9ba8 / FUN_003a25d4 / FUN_001b05d8; trap at 0x1afce0.
 */
void swift_string_fatal_precondition(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                                     uint64_t p5)
{
    reg16 v = FUN_0035193c();
    reg16 out = { p4, p5 };
    uint64_t u3 = v.lo;
    if ((p3 & 1) != 0) {
        if (u3 >> 0x20 != 0) {
            uint64_t u4 = FUN_003583dc(x8);
            FUN_00348194();
            FUN_003523f0(u4);
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        if ((0x10 < u3 >> 0x10) || (0xfffffffffffff7ff < u3 - 0xe000)) goto invalid;
        int len;
        if (u3 < 0x80) len = v.lo4 + 1;
        else {
            FUN_00357d0c(x8);
            len = w9;
            if (0x7ff < u3) len = w8;
        }
        is_28 = FUN_00255d4c(len);
        uint64_t u4 = 0x1afb10;
        reg16 v2 = thunk_FUN_0036b270(p5);  /* alloc pages */
        if ((p5 >> 0x3c & 1) == 0) {
            if ((p5 >> 0x3d & 1) != 0) goto inline_path;
            goto heap_path;
        }
        FUN_003514e8(v2.lo, v2.hi, 0x1afb10);
        out = FUN_0001d4a0();
        u4 = 0x1afc98;
        v2 = FUN_003a25d4(p5);
        if ((out.hi >> 0x3d & 1) == 0) goto heap_path;
inline_path:
        is_20 = out.hi & 0xffffffffffffff;
        v2 = { &stack_18, out.hi >> 0x38 & 0xf };
        goto format;
    }
    if (u3 == 0) goto invalid;
    if (v.hi < 0) {
        FUN_0034846c();
        sk_swift_fatal(0, 0, 0);                   /* noreturn */
    }
    u4 = 0x1afb44;
    v2 = thunk_FUN_0036b270(p5);            /* alloc pages */
    if ((p5 >> 0x3c & 1) == 0) {
        if ((p5 >> 0x3d & 1) != 0) goto inline_path2;
        goto heap_path2;
    }
    FUN_003514e8(v2.lo, v2.hi, 0x1afb44);
    out = FUN_0001d4a0();
    u4 = 0x1afbf4;
    v2 = FUN_003a25d4(p5);
    if ((out.hi >> 0x3d & 1) == 0) goto heap_path2;
inline_path2:
    is_20 = out.hi & 0xffffffffffffff;
    v2 = { &stack_18, out.hi >> 0x38 & 0xf };
    goto format;
heap_path:
    u3 = out.lo;
    if ((u3 >> 0x3c & 1) == 0) {
        FUN_003514e8(v2.lo, v2.hi, u4);
        v2 = FUN_002a9ba8();
        out.hi = out.hi;
        out.lo = is_18;
    } else {
        u4 = FUN_00356364(v2.lo, u4);
        out.hi = out.hi;
        out.lo = is_18;
        v2 = { u4, u3 & 0xffffffffffff };
    }
    goto format;
heap_path2:
    u3 = out.lo;
    if ((u3 >> 0x3c & 1) == 0) {
        FUN_003514e8(v2.lo, v2.hi, u4);
        reg16 v7 = FUN_002a9ba8();
        out.hi = out.hi;
        out.lo = is_18;
    } else {
        u4 = FUN_00356364(v2.lo, u4);
        out.hi = out.hi;
        out.lo = is_18;
        v2 = { u4, u3 & 0xffffffffffff };
    }
format:
    u4 = out.hi;
    is_18 = out.lo;
    FUN_00351e3c(v2.lo, v2.hi);
    FUN_001b05d8();
    FUN_003a25d4(u4);
    __builtin_trap();                       /* 0x1afce0 */
invalid:
    FUN_00348898(1, u3, x8);
    FUN_0034a2f8();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001afd08 @ 0x001afd08   (est. swift_string_precondition_thunk)
 * Ghidra: void FUN_001afd08(void)
 * Thunk: forwards to FUN_001afd38.
 * Confidence: medium
 */
void swift_string_precondition_b(void) { FUN_001afd38(); }

/*--------------------------------------------------------------------*/
/* FUN_001afd38 @ 0x001afd38   (est. swift_string_precondition)
 * Ghidra: void FUN_001afd38(void)
 * String precondition: checks the string's invariant and either succeeds or
 * fatals via FUN_001afa84.
 * Confidence: medium
 * Notes: FUN_00077698 / FUN_003542e8 / FUN_00358da0 / FUN_0007767c /
 *   FUN_00357c38 / FUN_00350914 / FUN_001afa84.
 */
void swift_string_precondition(void)
{
    FUN_00077698();
    FUN_003542e8();
    code_fn *fn = (code_fn *)FUN_00358da0();
    uint64_t ok = fn();
    if ((ok & 1) != 0) {
        FUN_0007767c(x8);
        return;
    }
    x24_fn();                               /* callback */
    FUN_00357c38();
    reg16 v = FUN_00350914();
    FUN_001afa84(v.lo, v.hi, 2);            /* fatal */
}

/*--------------------------------------------------------------------*/
/* FUN_001afdbc @ 0x001afdbc   (est. swift_string_fatal_dispatch)
 * Ghidra: void FUN_001afdbc(void)
 * Dispatch wrapper for the string fatal path: acquires the lock, resolves the
 * message, and fatals.
 * Confidence: medium
 * Notes: FUN_00357cb4 / FUN_00353274 / FUN_00357c38 / FUN_0006f768 /
 *   FUN_001afa84.
 */
void swift_string_fatal_dispatch(void)
{
    FUN_00357cb4();
    code_fn *fn = (code_fn *)FUN_00353274();
    reg16 v = fn();
    FUN_00357c38(v.lo, v.hi, 0x1afdf4);
    FUN_0006f768(s_Fatal_error);
    FUN_001afa84();                         /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001afe4c @ 0x001afe4c   (est. sk_swift_fatal)
 * Ghidra: void FUN_001afe4c(undefined8 param_1, undefined8 param_2, uint param_3)
 * The Swift runtime fatal-error entry: validates the message payload,
 * resolves its length, formats the message, and traps. This is the shared
 * noreturn fatal used throughout the kernel's Swift runtime.
 * Confidence: high (string/format construction; noreturn trap)
 * Notes: FUN_00354a34 / FUN_00356c84 / FUN_00352ae4 / FUN_001b0174 /
 *   FUN_00354504 / FUN_00255d4c / FUN_00348898 / FUN_0034a2f8; trap at
 *   0x1aff14.
 */
void sk_swift_fatal(const char *p1, uint64_t p2, uint32_t p3, ...)
{
    FUN_00354a34();
    uint64_t u5 = x8;
    reg16 v = FUN_00356c84();
    uint64_t *msg = v.lo;
    if ((p3 & 1) == 0) {
        if (msg != NULL) {
            if (v.hi < 0) {
                FUN_0034846c();
                sk_swift_fatal(0, 0, 0);           /* noreturn */
            }
            goto print_trap;
        }
    } else {
        if ((uint64_t)msg >> 0x20 != 0) {
            u5 = FUN_003583dc(u5);
            FUN_00348194();
            FUN_003523f0(u5);
            sk_swift_fatal(0, 0, 0);               /* noreturn */
        }
        if (((uint64_t)msg >> 0x10 < 0x11) && (msg - 0x1c00 < (uint64_t *)0xfffffffffffff800)) {
            bool small = (section_00000068.segname + 7 < (char *)msg);
            uint64_t addr;
            uint32_t extra;
            if (small) {
                uint64_t u6 = FUN_00354504(msg, u5);
                uint32_t a = (w11 | w14) << 8;
                uint32_t b = (uint32_t)(u6 >> 0x12) & 0x3fff;
                int32_t c = -0x7e7e7e0f;
                if (u6 < 0x800) {
                    a = w9;
                    b = w8;
                    c = w10;
                }
                msg = (uint64_t *)(uint64_t)(b + c);
                extra = a;
            } else {
                extra = 1;
            }
            is_18 = FUN_00255d4c((int32_t)((uint64_t)msg + extra));
            msg = &stack_18;
            goto print_trap;
        }
    }
    FUN_00348898(1, msg, u5);
    FUN_0034a2f8();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
print_trap:
    FUN_00352ae4(msg);
    FUN_001b0174();
    __builtin_trap();                       /* 0x1aff14 */
}

/*--------------------------------------------------------------------*/
/* FUN_001affc0 @ 0x001affc0   (est. sk_sched_queue_tick_step)
 * Ghidra: void FUN_001affc0(void)
 * One run-queue tick step: dispatches through the queue slot handlers,
 * checking a completion flag; fatals if the flag indicates an invalid state.
 * Confidence: low (heavy inlining, indirect dispatch)
 * Notes: FUN_0008e518, DAT_00658c00, FUN_003722e4, FUN_0008e500;
 *   fatal FUN_001afe4c.
 */
void sk_sched_queue_tick_step(void)
{
    reg16 v = sk_cpu_current();             /* FUN_0008e518 */
    FUN_00355d10(v.lo, v.hi, 0x672870);
    FUN_003515b4();
    FUN_003722e4();
    FUN_00348d4c();
    dispatch_slot(*(uint64_t *)(x8_00 + 0x40)); /* DAT_00658c00 */
    FUN_0034ab10();
    FUN_0034f730();
    dispatch_slot(0);                       /* DAT_00658c00 */
    FUN_0034ba68();
    FUN_00356030();
    FUN_00351aa4(x16_00);
    FUN_00350810();
    x9_fn();
    *(char *)(x27 + *(int *)(x24 + 0x30)) = v[8];
    FUN_00352474();
    FUN_00351ab0();
    x9_00_fn();
    char c = *(char *)(x20 + *(int *)(x24 + 0x30));
    FUN_00350ed0(*(uint64_t *)(x16_00 + 0x20), x8);
    x8_01_fn();
    if (c != '\x01') {
        FUN_00350a34(*(uint64_t *)(x16 + 8));
        x8_02_fn();
        sk_thread_epilogue();               /* FUN_0008e500 */
        return;
    }
    FUN_0034b348();
    FUN_00349de8(s_Fatal_error);
    FUN_001b012c();
    sk_swift_fatal(0, 0, 0);                       /* noreturn */
}
