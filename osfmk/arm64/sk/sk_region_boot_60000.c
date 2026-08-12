/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * This file covers the 0x60000-0x70000 region: object method-dispatch tables
 * and the early boot / object-constructor dispatch machinery. SeL4/cL4
 * vocabulary (TCB, cap, CNode, IPC, notification, endpoint, vspace, sched,
 * boot, etc.). Confidence is medium unless a string matches. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Reconstruction support: cL4/arm64e helper types, macros and register
 * placeholders used across this region's bodies. */
typedef uint64_t sk_word_t;
typedef unsigned int uint;
typedef struct { sk_word_t v0, v1; } sk_ctx_frame_t;

/* Supervisor-call / GENTER-adjacent primitives (cL4 SM ops). */
#define CallSupervisor(n) do { __asm__ volatile("svc #0" ::: "memory"); } while (0)
#define LOAcquire()       do { } while (0)
#define SoftwareBreakpoint(a, b) ((void(*)())0)

/* Ghidra pseudo-functions used in faithful reconstructions. */
#define __builtin_thread_pointer_ro() ((volatile unsigned char *)__builtin_thread_pointer())
static inline void wr64(volatile unsigned char *p, sk_word_t v){ p[0]=(unsigned char)v; p[1]=(unsigned char)(v>>8); p[2]=(unsigned char)(v>>16); p[3]=(unsigned char)(v>>24); p[4]=(unsigned char)(v>>32); p[5]=(unsigned char)(v>>40); p[6]=(unsigned char)(v>>48); p[7]=(unsigned char)(v>>56); }
static inline sk_word_t rd64(const unsigned char *p){ return (sk_word_t)p[0]|(sk_word_t)p[1]<<8|(sk_word_t)p[2]<<16|(sk_word_t)p[3]<<24|(sk_word_t)p[4]<<32|(sk_word_t)p[5]<<40|(sk_word_t)p[6]<<48|(sk_word_t)p[7]<<56; }
static inline unsigned int LZCOUNT(sk_word_t v){ return v?__builtin_clzll(v):64; }

/* Ghidra CONCAT/bit-vector helpers (mostly no-ops for syntax purposes). */
#define CONCAT11(a,b) ((a)|((b)<<8))
#define CONCAT12(a,b) ((a)|((b)<<16))
#define CONCAT13(a,b) ((a)|((b)<<24))
#define CONCAT14(a,b) ((a)|((b)<<32))
#define CONCAT15(a,b) ((a)|((b)<<40))
#define CONCAT16(a,b) ((a)|((b)<<48))
#define CONCAT17(a,b) ((a)|((b)<<56))
#define CONCAT71(a,b) (((a)<<56)|(b))
#define ZEXT816(x) ((x))
#define SEXT816(x) ((long)(x))
#define SUB168(a,b) ((unsigned long)(a))
#define CARRY8(a,b) (0)
#define SBORROW8(a,b) (0)
#define SCARRY8(a,b) (0)

/* Register / frame placeholders (values passed in registers at the call
 * site; reconstructed from the decompiler). */
extern sk_word_t in_w8, in_x3, in_x4, extraout_x1, extraout_x8, extraout_x9;
extern sk_word_t *unaff_x20, *unaff_x22, *unaff_x27;
extern sk_word_t unaff_x21, unaff_x23;
extern sk_word_t uVar3, canary, local_88, local_90, local_38;
extern sk_word_t __thread_bss;

/* Boot-descriptor iterator helpers (reconstructed by the range worker). */
sk_word_t sk_boot_begin(void);
void *sk_boot_next(void);
void *sk_boot_iter(void);
sk_word_t sk_boot_more(void*);
void *sk_boot_ent(void*);
int sk_boot_code(void*);
unsigned char *sk_boot_key(void*, int);
sk_word_t sk_boot_pack_key(unsigned char*);
sk_ctx_frame_t sk_ctx_frame(void);
unsigned char sk_err_reg(void);
unsigned char *sk_err_out(void);

/* Out-of-range data globals referenced by this region. */
extern sk_word_t DAT_005c99ee;

/* Short-form boot strings referenced by bodies. */
extern const char s_Fatal_error[];
extern const char s_DeviceTreeKit_DeviceTreeKit_swif[];
extern const char s_InternalExclaveLauncher_PacResou[];
extern const char s_Swift_NativeDictionary_swift[];
extern const char s__AppleInternal_Library_BuildRoot[];
extern const char s_context____NULL[];
extern const char s_device_tree_integrity_parse_call[];
extern const char s_device_tree_node_children_iterat[];
extern const char s_iterator_gt_node_size[];
extern const char s_InternalExclaveLauncher_Commpage[];
extern sk_word_t DAT_004be938, DAT_004bed40, DAT_004bee78, DAT_004ea504, DAT_005a4b80;
/* Stray reconstruction locals (declared globally for -fsyntax-only). */
extern sk_word_t bit, ctx, dp, entry, keep, local_30, local_b0, q, uStack_28, val;
extern sk_word_t *local88;
extern sk_word_t unaff_x19;

extern sk_word_t DAT_006be46c, DAT_006be674, DAT_006be660, DAT_006be868;
extern sk_word_t DAT_006b2830, DAT_006b27f0, _DAT_006b2838, _DAT_006b27f8, _DAT_006b2840;
extern sk_word_t _DAT_004bee90, uRam00000000004bee98, _DAT_004beea0, uRam00000000004beea8;
extern sk_word_t _DAT_004beeb0, uRam00000000004beeb8;
extern sk_word_t _DAT_006be8e8, _DAT_006be898, _DAT_006be8a0, _DAT_006be8a8, _DAT_006be8b4;
extern sk_word_t DAT_006be8b0, _DAT_006be8b8, _DAT_006be8c0, _DAT_006be8c8, _DAT_006be8d0;
extern sk_word_t _DAT_006be870, _DAT_006be878, _DAT_006be880, _DAT_006be888;
extern sk_word_t _DAT_006be890, _DAT_006be8d8, _DAT_006be8e0, _DAT_006be660;
extern sk_word_t _DAT_006ad6e0, _DAT_006ad988, _DAT_006ad990;
extern sk_word_t _DAT_2bc686b8528, _DAT_2bc686b8530, _DAT_2bc686b8538, _DAT_2bc686b8540;
extern sk_word_t _DAT_2bc686b8548, _DAT_2bc686b8550, _DAT_2bc686b8378;
extern sk_word_t _DAT_4d5e91ca80, _DAT_4d5e91c8a0, _DAT_9fd86d1380, _DAT_9fd86d11a0;
extern sk_word_t _DAT_ee50745750;

extern sk_word_t DAT_006ad900, DAT_006ad980, DAT_006b26c8, DAT_006b26c9;
extern sk_word_t DAT_006b26d0, DAT_006b26d8, DAT_006b2710, DAT_006b2718, DAT_006b2720;
extern sk_word_t DAT_006b2728, DAT_006b2730, DAT_006b2738, DAT_006b2740, DAT_006b2748;
extern sk_word_t DAT_006b2750, DAT_006b27e0, DAT_006b27e8, DAT_006b2808, DAT_006b2820;
extern sk_word_t DAT_006b2828, DAT_006b2918, DAT_006b2920, DAT_006b2928, DAT_006b2930;
extern sk_word_t DAT_006b2938, DAT_006b2940, DAT_006b2948, DAT_006b2950, DAT_006b2958;
extern sk_word_t DAT_004bf000, DAT_004bf010, DAT_004bf018, DAT_004bf170, DAT_004bf180, DAT_004bf188;
extern sk_word_t DAT_004be310, DAT_004be770, DAT_004be5e0, DAT_004be8e0, DAT_004be8e8;
extern sk_word_t DAT_004bf020, DAT_004bf028, DAT_004be5f0, DAT_004be5f8, DAT_004be600;
extern const char s_Fatal_error_005accd0[];
extern const char s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0[];
extern const char s__AppleInternal_Library_BuildRoot_005be68f[];
extern const char s_context____NULL_005be787[];
extern const char s_device_tree_integrity_parse_call_005be797[];
extern const char s_device_tree_node_children_iterat_005be75f[];
extern const char s_iterator_gt_node_size[];
extern const char s_InternalExclaveLauncher_PacResou_005bfbb0[];


/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / kernel helper declarations (declared extern with a one-
 * line note; their bodies are reconstructed by the range worker that owns
 * them). Names are estimates. */

const char *sk_reg_name(sk_word_t);  /* helper */
int sk_addrspace(sk_word_t*);  /* FUN_0005b860 */
int sk_commpage_status(void);  /* FUN_0006e6dc */
int sk_component(int,sk_word_t*);  /* FUN_0005d154 */
int sk_dart_table(sk_word_t*);  /* FUN_000554bc */
int sk_dt_node_name_is(sk_word_t*,const char*);  /* FUN_00065d18 */
int sk_isprint(unsigned char);  /* FUN_00115448 */
int sk_log_push(sk_word_t);  /* thunk_FUN_000544d0 */
int sk_ref_valid(void*);  /* FUN_0011817c */
int sk_strcmp(const char*,const char*);  /* thunk_FUN_00114d10 */
long *sk_boot_caps;  /* _DAT_006be890 */
long sk_boot_cnt(void*);  /* FUN_000556c8 */
long sk_cb_bind(sk_word_t,sk_word_t);  /* FUN_00376820 */
long sk_cb_bind2(sk_word_t,sk_word_t,sk_word_t*);  /* FUN_00376820 */
long sk_len2(void);  /* thunk_FUN_000126e8 */
long sk_seg_find(void*,const char*);  /* FUN_00051e5c */
short sk_exc_next(sk_word_t,sk_word_t,sk_word_t*);  /* FUN_004b75e4 */
sk_word_t (*dt_cb)(sk_word_t,sk_word_t,sk_word_t*);  /* indirect */
sk_word_t *sk_console_state(void);  /* FUN_0006b330 */
sk_word_t *sk_console_state2(void);  /* FUN_0006b5c0 */
sk_word_t *sk_console_state3(void);  /* FUN_0006b5e0 */
sk_word_t *sk_dt_boot_enter3(void);  /* FUN_0006b2dc */
sk_word_t *sk_ep_state(int);  /* FUN_0005fad8 */
sk_word_t *sk_hash_fail2(void);  /* FUN_0036993c */
sk_word_t *sk_hex_emit2(void);  /* FUN_0006b610 */
sk_word_t *sk_key_table_p(void);  /* helper */
sk_word_t *sk_regs_buffer;  /* helper */
sk_word_t *sk_report_cat(sk_word_t,sk_word_t,sk_word_t,sk_word_t);  /* FUN_001bc440 */
sk_word_t *sk_report_lookup(sk_word_t,sk_word_t);  /* FUN_0006ae9c */
sk_word_t *sk_report_state(void);  /* FUN_0006b584 */
sk_word_t *sk_report_state2(void);  /* FUN_0006b680 */
sk_word_t DAT_006b27e0;  /* ipmm flag */
sk_word_t DAT_006b27e8;  /* frame space flag */
sk_word_t DAT_006be8b0;
sk_word_t _DAT_004bf000;  /* err fallback w0 */
sk_word_t _DAT_004bf010;  /* err fallback w2 */
sk_word_t _DAT_004bf170, uRam00000000004bf178, _DAT_004bf180, uRam00000000004bf188;
sk_word_t _DAT_006ad6e0, _DAT_006ad988, _DAT_006ad990;
sk_word_t _DAT_006b2808, _DAT_006b2820, _DAT_006b2828, _DAT_006b2830, _DAT_006b2838;
sk_word_t _DAT_006b2928;  /* ipmm bump count */
sk_word_t _DAT_006b2930;  /* ipmm alloc count */
sk_word_t _DAT_006b2938;  /* ipmm free count */
sk_word_t _DAT_006b2940, _DAT_006b2948, _DAT_006b2950;
sk_word_t _DAT_006be870, _DAT_006be878, _DAT_006be880, _DAT_006be888, _DAT_006be660, _DAT_006be868;
sk_word_t _DAT_006be880, _DAT_006be8b4;
sk_word_t _DAT_006be898, _DAT_006be8a0, _DAT_006be8a8, _DAT_006be8b4, _DAT_006be8b8, _DAT_006be8c0, _DAT_006be8c8, _DAT_006be8d0, _DAT_006be8e8;
sk_word_t _DAT_006be8d8, _DAT_006be8e0;
sk_word_t _DAT_2bc686b8378;
sk_word_t _DAT_2bc686b8528, _DAT_2bc686b8530, _DAT_2bc686b8538, _DAT_2bc686b8540, _DAT_2bc686b8548, _DAT_2bc686b8550;
sk_word_t _DAT_2bc686b8528, _DAT_2bc686b8530, _DAT_2bc686b8548, _DAT_2bc686b8550;
sk_word_t _DAT_4d5e91ca80, _DAT_4d5e91c8a0;
sk_word_t _DAT_9fd86d1380, _DAT_9fd86d11a0;
sk_word_t _DAT_ee50745750;
sk_word_t bitrev(sk_word_t);  /* helper */
sk_word_t canary;  /* 0xd37afd4bb400012a */
sk_word_t extraout_x8;  /* register */
sk_word_t in_w8;  /* register */
sk_word_t in_x3, in_x4;  /* registers */
sk_word_t local_90;  /* iterator state */
sk_word_t local_90;  /* report frame */
sk_word_t rd64(const unsigned char*);  /* helper */
sk_word_t sk_778a0(void);  /* FUN_000778a0 */
sk_word_t sk_alloc_big(sk_word_t,sk_word_t);  /* FUN_0006d240 */
sk_word_t sk_alloc_rt(sk_word_t,sk_word_t);  /* FUN_0036a9d4 */
sk_word_t sk_alloc_word(sk_word_t,sk_word_t);  /* FUN_0036a804 */
sk_word_t sk_amx_bad(sk_word_t) __attribute__((noreturn));  /* FUN_004b7664 */
sk_word_t sk_amx_seed_hi;  /* uRam00000000004be5e8 */
sk_word_t sk_amx_seed_lo;  /* _DAT_004be5e0 */
sk_word_t sk_boot_copy(sk_word_t,sk_word_t);  /* FUN_0005c184 */
sk_word_t sk_boot_enter(void);  /* FUN_00002534 */
sk_word_t sk_boot_feature(void*,sk_word_t,int,int,int,int);  /* FUN_003a26e8 */
sk_word_t sk_boot_obj_helper(sk_word_t);  /* FUN_0001a1c8 */
sk_word_t sk_boot_pack_key_sel(unsigned char*,int,unsigned int);  /* FUN_0004e774 */
sk_word_t sk_boot_sz(void*);  /* FUN_000556e4 */
sk_word_t sk_buf_cap(void*);  /* FUN_003a261c */
sk_word_t sk_cap1(void), sk_cap2(void), sk_cap3(void);  /* FUN_000552a4/00055328/00055344 */
sk_word_t sk_cap_addr(sk_word_t,sk_word_t*);  /* FUN_00054c9c */
sk_word_t sk_cap_of(sk_word_t);  /* FUN_00063970 */
sk_word_t sk_cmp_tag(sk_word_t,sk_word_t,sk_word_t,sk_word_t,int);  /* FUN_002a0cf8 */
sk_word_t sk_ctx2(void);  /* FUN_000ec8f8 */
sk_word_t sk_ctx6(void);  /* FUN_00083c34 */
sk_word_t sk_ctx7(sk_word_t);  /* FUN_000773f0 */
sk_word_t sk_ctx_alloc(void);  /* FUN_00063a50 */
sk_word_t sk_ctx_m(void);  /* FUN_00086590 */
sk_word_t sk_ctx_t(void);  /* FUN_00086440 */
sk_word_t sk_ctxa(void);  /* FUN_000aa6d0 */
sk_word_t sk_ctxb(void);  /* FUN_000ec964 */
sk_word_t sk_ctxc(void);  /* FUN_0006f800 */
sk_word_t sk_dart_sid(sk_word_t*), sk_dart_sid2(sk_word_t*);  /* FUN_0005537c/000553b0 */
sk_word_t sk_dart_tid(sk_word_t*), sk_dart_tid2(sk_word_t*);  /* FUN_000554f0/00055524 */
sk_word_t sk_dev, sk_dev2;  /* DAT_004bf020/004bf028 */
sk_word_t sk_disp_a(void);  /* FUN_0006f6d0 */
sk_word_t sk_disp_done(void);  /* FUN_001f0130 */
sk_word_t sk_dt_base;  /* _DAT_004be8e0 */
sk_word_t sk_dt_lim;  /* uRam00000000004be8e8 */
sk_word_t sk_dt_node(sk_word_t,sk_word_t*);  /* FUN_00065f48 */
sk_word_t sk_dt_node_get2(sk_word_t,sk_word_t);  /* FUN_00066804 */
sk_word_t sk_dt_node_init2(sk_word_t,sk_word_t,sk_word_t*);  /* FUN_000662b8 */
sk_word_t sk_dt_prop_base;  /* _DAT_006b2748 */
sk_word_t sk_dt_prop_hi;  /* uRam00000000006b2750 */
sk_word_t sk_dt_prop_ready;  /* DAT_006b2740 */
sk_word_t sk_dt_prop_size;  /* s_L4_ErrorCodeOperationInvalid_0068a4c8._6_8_ */
sk_word_t sk_dt_resolve(sk_word_t,int,sk_word_t*);  /* FUN_00066178 */
sk_word_t sk_dt_table2;  /* DAT_006b2738 */
sk_word_t sk_dt_table;  /* DAT_006b2730 */
sk_word_t sk_dt_walk_end(void);  /* FUN_00066030 */
sk_word_t sk_eb(void);  /* FUN_0006eb1c */
sk_word_t sk_ep_lock(sk_word_t*);  /* FUN_0005cdbc */
sk_word_t sk_exc_default2(void*,sk_word_t*);  /* FUN_00064de8 */
sk_word_t sk_exc_ep;  /* DAT_006b2720 */
sk_word_t sk_exc_list;  /* DAT_006ad928 */
sk_word_t sk_exc_marker;  /* L4_ErrorCodeTruncated derived */
sk_word_t sk_exc_report2(sk_word_t,sk_word_t,sk_word_t);  /* FUN_00064e84 */
sk_word_t sk_exc_seed_hi;  /* uRam00000000004be318 */
sk_word_t sk_exc_seed_lo;  /* _DAT_004be310 */
sk_word_t sk_exc_slot;  /* DAT_006b2728 */
sk_word_t sk_exc_special_bad(sk_word_t) __attribute__((noreturn));  /* FUN_004b7ac8 */
sk_word_t sk_get4_0456c_x(void);  /* 0x0456c */
sk_word_t sk_h_1a1c8(sk_word_t);  /* FUN_0001a1c8 */
sk_word_t sk_h_84cc4(sk_word_t,sk_word_t);  /* FUN_00084cc4 */
sk_word_t sk_h_85754(sk_word_t,sk_word_t);  /* FUN_00085754 */
sk_word_t sk_h_aae60(void);  /* FUN_000aae60 */
sk_word_t sk_h_af4d8(sk_word_t,sk_word_t);  /* FUN_000af4d8 */
sk_word_t sk_h_af56c(sk_word_t);  /* FUN_000af56c */
sk_word_t sk_h_af5fc(sk_word_t);  /* FUN_000af5fc */
sk_word_t sk_hash_emit(sk_word_t,sk_word_t*,sk_word_t,sk_word_t,int);  /* FUN_00365b6c */
sk_word_t sk_hash_insert(int,sk_word_t,sk_word_t);  /* FUN_00258c60 */
sk_word_t sk_hex_digit(unsigned char);  /* FUN_0006b2fc */
sk_word_t sk_hex_push(void*,sk_word_t);  /* FUN_0006b3d0 + FUN_0006b6a0 + FUN_0006a374 */
sk_word_t sk_ipmm_abort(sk_word_t);  /* FUN_004b7cd4 */
sk_word_t sk_ipmm_alloc_count, sk_ipmm_free_count;  /* _DAT_006b2930/006b2938 */
sk_word_t sk_ipmm_cnt;  /* _DAT_006b2828 */
sk_word_t sk_ipmm_count;  /* _DAT_006b2928 */
sk_word_t sk_ipmm_de;  /* _DAT_006b2840 */
sk_word_t sk_ipmm_hi;  /* _DAT_006b2920 */
sk_word_t sk_ipmm_lo, sk_ipmm_hi;  /* _DAT_006b2918/006b2920 */
sk_word_t sk_ipmm_lo;  /* _DAT_006b2918 */
sk_word_t sk_ipmm_return(sk_word_t);  /* FUN_004b7edc */
sk_word_t sk_ipmm_slot;  /* _DAT_006b2808 */
sk_word_t sk_kern_alloc(void);  /* FUN_00063a94 */
sk_word_t sk_key_table;  /* DAT_006b2718 */
sk_word_t sk_link_of(sk_word_t);  /* FUN_0019afbc */
sk_word_t sk_log_cpu(void);  /* FUN_0005b8c8 */
sk_word_t sk_macho_header(void);  /* FUN_00054ba8 */
sk_word_t sk_macho_slide(void);  /* FUN_00054bc8 */
sk_word_t sk_msg_copy(sk_word_t,sk_word_t,int,sk_word_t,sk_word_t*,void*);  /* FUN_0011546c */
sk_word_t sk_perm_hi;  /* s_L4_ErrorCodePermissionInvalid_0068a4e8._6_8_ */
sk_word_t sk_perm_lo;  /* _DAT_0068a4e6 */
sk_word_t sk_reg_a(void);  /* FUN_000537c4 */
sk_word_t sk_region_addr(void);  /* FUN_004b83bc */
sk_word_t sk_region_lo(void), sk_region_hi(void);  /* FUN_00055718/0005574c */
sk_word_t sk_region_map(sk_word_t,sk_word_t,sk_word_t,sk_word_t);  /* FUN_000f6d20 */
sk_word_t sk_rep2(sk_word_t);  /* FUN_0006a3cc */
sk_word_t sk_report_buf(void);  /* FUN_0006b388 */
sk_word_t sk_report_cb(void);  /* indirect */
sk_word_t sk_report_cmp3(long,long);  /* FUN_00068ef8 */
sk_word_t sk_report_slot(void);  /* FUN_0006b2bc */
sk_word_t sk_ro_write8u(sk_word_t);  /* FUN_000639a0 */
sk_word_t sk_sme_bad(sk_word_t) __attribute__((noreturn));  /* FUN_004b76b4 */
sk_word_t sk_strlen(const char*);  /* thunk_FUN_00115080 */
sk_word_t sk_sym_resolve(sk_word_t,void*);  /* FUN_00027614 */
sk_word_t sk_vspace_ready;  /* _DAT_006b2958 */
sk_word_t thunk_len(sk_word_t,int);  /* thunk_FUN_00114fe0 */
sk_word_t uRam00000000004bf008;  /* err fallback w1 */
sk_word_t uRam00000000004bf018;  /* err fallback w3 */
sk_word_t uVar3;  /* supervisor status */
sk_word_t *unaff_x20, *unaff_x22, *unaff_x27;  /* registers (pointer) */
sk_word_t unaff_x21, unaff_x23;  /* registers (scalar) */
unsigned char *sk_boot_strings(void);  /* FUN_00054610 */
unsigned char sk_flag_1;  /* DAT_006b26c8 */
unsigned char sk_flag_2;  /* DAT_006b26c9 */
unsigned char sk_perm_flag(void);  /* FUN_00084dc8 */
unsigned int *sk_dt_node_hdr(sk_word_t*);  /* FUN_00065c30 */
unsigned long DAT_00657778;  /* empty buf */
unsigned long DAT_00657788;  /* console count */
unsigned long DAT_00657790;  /* console cap */
unsigned long DAT_00657798;  /* console table */
unsigned long DAT_00657798;  /* empty table */
unsigned long DAT_006577e0;  /* boot dt slot */
unsigned long DAT_006b2b10, DAT_006b2b18;  /* region table */
unsigned long DAT_006b2b18, DAT_006b2b10;  /* region tables */
unsigned long sk_boot_counter;  /* DAT_006ad900 */
unsigned long sk_stack_cursor;  /* DAT_006b2710 */
unsigned short *sk_vspace_client_list;  /* _DAT_006ad980 */
void **sk_exc_slot_p(void);  /* DAT_006b2728 */
void *prev_after(long,void*);  /* helper */
void *sk_alloc_ep(int);  /* FUN_0019ae2c */
void *sk_alloc_names(sk_word_t,sk_word_t);  /* FUN_001fac04 */
void *sk_alloc_obj(sk_word_t,int,int);  /* FUN_0036a940 */
void *sk_alloc_pages(sk_word_t,sk_word_t);  /* FUN_0036b270 */
void *sk_alloc_pagetable(sk_word_t,sk_word_t,int,int,int);  /* FUN_00085a54 */
void *sk_alloc_small(sk_word_t,int,sk_word_t);  /* FUN_00010244 */
void *sk_amx_state(void);  /* FUN_00034f70 */
void *sk_boot_data(void*);  /* FUN_00054624 */
void *sk_boot_data2(void);  /* FUN_0005ace4 */
void *sk_boot_lookup(int,const char*);  /* FUN_0004dfd0 */
void *sk_boot_obj_helper2(void*);  /* FUN_00027724 */
void *sk_buf_grow(void*);  /* FUN_0006b42c + FUN_0006b6d4 + FUN_0006b3e0 */
void *sk_buf_new(void);  /* FUN_0006b3e0 */
void *sk_cap_resolve(sk_word_t*,int);  /* FUN_0005bc48 */
void *sk_cpu_phase(void);  /* FUN_004b7098 */
void *sk_cpu_phase_slow(void);  /* FUN_004b70c8 */
void *sk_ctx_state(void);  /* FUN_00034f70 */
void *sk_ep_new_thread(void*,int);  /* FUN_0005eec4 */
void *sk_ep_return(void*,int);  /* FUN_0006393c */
void *sk_exc_first(void);  /* FUN_000533ec */
void *sk_handler_table(unsigned long,int,int);  /* FUN_0005acac */
void *sk_hex_buf(void);  /* FUN_0006b630 */
void *sk_irq_handler(int,int);  /* FUN_00062a48 */
void *sk_panic_hooks(void);  /* FUN_0005ba14 */
void *sk_per_cpu_base(void);  /* FUN_00060524 */
void *sk_pt_ctx(void);  /* FUN_00034a2c */
void *sk_root_task;  /* DAT_006b26d0 */
void *sk_sym_e3d6c, *sk_sym_e3dd0, *sk_sym_e3e34, *sk_sym_e3f10;  /* symbols */
void *sk_tcb_current(void);  /* FUN_0005bb68 */

void sk_alloc_teardown(void);  /* FUN_0036b21c */
void sk_altstack_body(void **svc, void *a, void *b);  /* FUN_0005cf18 */
void sk_amx_free(void*,void*,int);  /* FUN_004b23d8 */
void sk_amx_setup(void*,long*);  /* FUN_004b7704 */
void sk_banner(const char*,int,int,char*);  /* FUN_00118abc */
void sk_bb(sk_word_t*);  /* FUN_0006d7d0 */
void sk_boot_abort(void) __attribute__((noreturn));  /* FUN_004b82b4 */
void sk_boot_attached(long,void*);  /* FUN_000549c0 */
void sk_boot_bad(void) __attribute__((noreturn));  /* FUN_00116d60 */
void sk_boot_data_free(void*);  /* FUN_00052c4c */
void sk_boot_descr(void*);  /* FUN_00063ea4 */
void sk_boot_done_copy(void);  /* FUN_00054dec */
void sk_boot_early(void);  /* FUN_0005ba40 */
void sk_boot_early2(unsigned long);  /* FUN_0005ba5c */
void sk_boot_exception(void*,sk_word_t);  /* FUN_000604f8 */
void sk_boot_fail(void) __attribute__((noreturn));  /* FUN_004b7120 */
void sk_boot_helper(int);  /* FUN_00229a3c */
void sk_boot_helper2(long);  /* thunk_FUN_002298d4 */
void sk_boot_irq_init(void);  /* FUN_0005d5dc */
void sk_boot_lock(void);  /* LOAcquire */
void sk_boot_mm_init(void);  /* FUN_0005ad40 */
void sk_boot_no_irq(void);  /* FUN_00053418 */
void sk_boot_none(void) __attribute__((noreturn));  /* FUN_004b7138 */
void sk_boot_print(void);  /* FUN_0011d790 */
void sk_boot_ret(sk_word_t);  /* FUN_0004ed84 */
void sk_boot_taken(void);  /* FUN_004b70f8 */
void sk_boot_x(void*);  /* FUN_00065620 */
void sk_boot_y(void*);  /* FUN_000656d8 */
void sk_boot_z(void);  /* FUN_0005ac2c */
void sk_breakpoint(int a, int b) __attribute__((noreturn));  /* SoftwareBreakpoint(0x5519,..) */
void sk_buf_free(void*);  /* FUN_0006b45c */
void sk_buf_free2(void);  /* FUN_0006b6e0 */
void sk_buf_memcpy(sk_word_t,sk_word_t,long,sk_word_t);  /* FUN_0035b67c */
void sk_cap_done(void*);  /* FUN_00052c54 */
void sk_cap_init(void*);  /* FUN_00052a04 */
void sk_commpage_map(void*,void*,void*);  /* FUN_0006f130 */
void sk_commpage_prep(void);  /* FUN_0006f70c */
void sk_console_enter(void);  /* FUN_0006b374 */
void sk_console_flush(void);  /* FUN_0006b630 */
void sk_console_grow(sk_word_t);  /* FUN_0006b42c + FUN_0006a468 */
void sk_console_init3(void);  /* FUN_0006b48c+668a0+66950 */
void sk_console_init4(sk_word_t,sk_word_t,sk_word_t);  /* FUN_0006a468 */
void sk_console_init_seq(void);  /* FUN_0006b374+668a0+66950 */
void sk_console_names(void*,int,sk_word_t**);  /* FUN_0006abac */
void sk_console_read_state(void);  /* FUN_001eb088 */
void sk_cpu_yield(void *cpu);  /* FUN_0005deb4 */
void sk_ctx_bind_h(sk_word_t,sk_word_t,sk_word_t);  /* FUN_0001a0d0 */
void sk_ctx_bind_h2(sk_word_t);  /* FUN_0001c2a4 */
void sk_ctx_finish(void *cs);  /* FUN_004b23d8 */
void sk_ctx_import(sk_word_t,sk_word_t,int);  /* FUN_00114790 */
void sk_ctx_init(void *ctx, void *a, unsigned long n);  /* FUN_0005ff04 */
void sk_ctx_restore(void);  /* FUN_001a8564 */
void sk_ctx_save(int);  /* FUN_001a84f4 */
void sk_disp0(sk_word_t);  /* FUN_001404d0/000773f0 */
void sk_disp_b(sk_word_t,sk_word_t);  /* FUN_0006f69c */
void sk_disp_c(sk_word_t,sk_word_t);  /* FUN_0006f684 */
void sk_disp_pair(sk_word_t,sk_word_t);  /* FUN_0014aea4 */
void sk_dt_begin(void);  /* FUN_00066210 */
sk_word_t *sk_dt_boot_enter(void);  /* FUN_0006b2ec */
void sk_dt_boot_enter2(sk_word_t);  /* FUN_0006b2dc */
void sk_dt_boot_publish(void);  /* FUN_000651bc: no-op stub */
void sk_dt_boot_publish2(void);  /* FUN_000651bc: no-op stub */
void sk_dt_boot_store(sk_word_t,sk_word_t,sk_word_t);  /* FUN_0006b360 */
void sk_dt_fail(void) __attribute__((noreturn));  /* FUN_00066204 */
void sk_dt_iter_init(sk_word_t,sk_word_t,void(*)(void));  /* FUN_00068700 */
void sk_dt_list_copy4x(sk_word_t,sk_word_t,sk_word_t,sk_word_t);  /* FUN_001b58b0 */
void sk_ep_activate(void*);  /* FUN_0005fbc0 */
void sk_ep_activate_id(void*,int);  /* FUN_0005e0dc */
void sk_ep_activate_remote(void*);  /* FUN_004b6d60 */
void sk_ep_bad2(sk_word_t) __attribute__((noreturn));  /* FUN_004b7428 */
void sk_ep_bad_mode(sk_word_t) __attribute__((noreturn));  /* FUN_004b73d0 */
void sk_ep_final(void*);  /* FUN_0005b0bc */
void sk_ep_release(sk_word_t,int);  /* FUN_0019ae60 */
void sk_ep_setup_done(sk_word_t*);  /* FUN_0005ce54 */
void sk_ep_teardown(void*);  /* FUN_004b7278 */
void sk_exc_bad(sk_word_t) __attribute__((noreturn));  /* FUN_004b7594 */
void sk_exc_bad2(sk_word_t,sk_word_t*) __attribute__((noreturn));  /* FUN_004b7544 */
void sk_exc_classify2(sk_word_t*,void*,sk_word_t*);  /* FUN_000651e8 */
void sk_exc_fail(sk_word_t) __attribute__((noreturn));  /* FUN_004b71a8/FUN_0011d7e8 */
void sk_exc_handler_cb(void);  /* FUN_00063eb4-based */
void sk_fatal(const char*,int,int,sk_word_t,sk_word_t,const char*,int,int,int,int) __attribute__((noreturn));  /* FUN_001afa84 */
void sk_fatal0(void) __attribute__((noreturn));  /* FUN_001afa84 */
void sk_fmt(char*,const char*,...);  /* FUN_001185ec */
void sk_fmt_newline(char*);  /* thunk_FUN_001187f4(10,..) */
void sk_format(sk_word_t,sk_word_t*,sk_word_t,sk_word_t);  /* FUN_002060d4 */
void sk_format2(sk_word_t*,sk_word_t*,sk_word_t,sk_word_t,sk_word_t);  /* FUN_00205844 */
void sk_free(void*);  /* FUN_0036b118 */
void sk_free2(void);  /* thunk_FUN_00012568 */
void sk_freeze_ep(sk_word_t,int);  /* FUN_004b7984 */
void sk_freeze_no_ep(void) __attribute__((noreturn));  /* FUN_004b79c8 */
void sk_hash_fail3(void);  /* FUN_0036986c */
void sk_hash_mismatch(sk_word_t) __attribute__((noreturn));  /* FUN_002591b4 */
void sk_hex_cat(sk_word_t,sk_word_t,sk_word_t);  /* FUN_001bc440 */
void sk_hex_col(sk_word_t);  /* FUN_0006b440 */
void sk_hex_col2(sk_word_t,sk_word_t);  /* FUN_0006b2bc + FUN_0006a3cc */
void sk_hex_col_emit(void);  /* FUN_00294cb4 */
void sk_hex_done(void);  /* FUN_0006b700 */
void sk_hex_emit(sk_word_t,sk_word_t,sk_word_t);  /* FUN_0006b5a0 */
void sk_hex_flush(void*);  /* FUN_0006b640 */
void sk_hex_fmt(unsigned char*,sk_word_t,void*);  /* FUN_00369efc */
void sk_hex_line_begin(void);  /* FUN_0006b4ac */
void sk_hex_nibble(sk_word_t);  /* FUN_0001cba4 */
void sk_hook_capture(void*,sk_word_t*);  /* FUN_004b78c0 */
void sk_ipc_cb(void);  /* LAB_00062974 */
void sk_ipc_cb2(void);  /* DAT_000629ec / local_70 */
void sk_ipmm_abort_cap(sk_word_t) __attribute__((noreturn));  /* FUN_004b7ba0 */
void sk_ipmm_alloc_bad(sk_word_t) __attribute__((noreturn));  /* FUN_004b7c88 */
void sk_ipmm_done(void);  /* FUN_004b7dec */
void sk_ipmm_err(sk_word_t);  /* FUN_004b7e64 */
void sk_ipmm_finish(sk_word_t);  /* FUN_004b7bec */
void sk_ipmm_free2(sk_word_t);  /* FUN_004b7f24 */
void sk_ipmm_free3(sk_word_t);  /* FUN_004b7f6c */
void sk_ipmm_free_bad(sk_word_t) __attribute__((noreturn));  /* FUN_0011d7e8 */
void sk_ipmm_free_done(void) __attribute__((noreturn));  /* FUN_004b7eb0 */
void sk_ipmm_grow(void);  /* FUN_004b7008 */
void sk_ipmm_map_back(sk_word_t);  /* FUN_004b7fb4 */
void sk_ipmm_map_zero(sk_word_t);  /* FUN_004b7d20 */
void sk_ipmm_nofunc(void) __attribute__((noreturn));  /* FUN_00054354 */
void sk_key_not_owned(void);  /* FUN_004b749c */
void sk_key_owned(void);  /* FUN_004b7480 */
void sk_link_boot(void*,void*);  /* FUN_0005be48 */
void sk_link_release(void*);  /* FUN_0005bce0 */
void sk_lock_acquire(void *);  /* FUN_0005cb9c */
void sk_lock_release_glue(void *);  /* FUN_0005ce54 */
void sk_log1(sk_word_t);  /* FUN_0005e958 */
void sk_log_pop(sk_word_t);  /* thunk_FUN_0005453c */
void sk_logf(sk_word_t,sk_word_t,int,const char*);  /* FUN_0005b824 */
void sk_logf0(const char*);  /* FUN_00118b28 */
void sk_logf1(const char*);  /* FUN_00118b28 */
void sk_memcpy(void*,const void*,unsigned long);  /* FUN_00117cc4 */
void sk_memmove(void*,const void*,unsigned long);  /* FUN_00117d14 */
void sk_msg_copy2(sk_word_t,sk_word_t*,sk_word_t,sk_word_t,void*,void*);  /* FUN_001156c4 */
void sk_msg_copy3(sk_word_t,sk_word_t*,sk_word_t,int);  /* FUN_001155e0 */
void sk_obj_link(sk_word_t);  /* FUN_000359ac */
void sk_obj_reg(void*,void*);  /* FUN_0006166c */
void sk_panic(const char *fmt, ...) __attribute__((noreturn));  /* FUN_004afae4 */
void sk_panic_assert(const char*) __attribute__((noreturn));  /* FUN_001150e0 */
void sk_panic_bad(int,const char*) __attribute__((noreturn));  /* FUN_0005b190 */
void sk_panic_dbg(const char*,const char*,const char*,int) __attribute__((noreturn));  /* FUN_00115424 */
void sk_panic_halt(void);  /* FUN_001ba7d4 */
void sk_panic_halt2(void);  /* FUN_001bdb28 */
void sk_panic_msg0(const char*) __attribute__((noreturn));  /* FUN_0006f6e0 */
void sk_panic_reset(void);  /* FUN_0001df60 */
void sk_pending_cb(void(*)(void),void*);  /* FUN_0005bd7c */
void sk_pin_cpu(void);  /* FUN_0005fe48 */
void sk_pmm_bad(void) __attribute__((noreturn));  /* FUN_004b8414 */
void sk_pmm_bad2(void) __attribute__((noreturn));  /* FUN_004b83e8 */
void sk_pmm_bad3(void) __attribute__((noreturn));  /* FUN_004b8440 */
void sk_pmm_bad4(void) __attribute__((noreturn));  /* FUN_004b846c */
void sk_pmm_grow2(sk_word_t,sk_word_t) __attribute__((noreturn));  /* FUN_004b7008 */
void sk_print_rec(sk_word_t,int,const char*,sk_word_t);  /* FUN_00116bb4 */
void sk_putch(int,char*);  /* FUN_001187f4 */
void sk_ref_finalize(void*);  /* FUN_00118194 */
void sk_reg_pending(void(*)(void),void*);  /* FUN_0005bd7c */
void sk_report_cat2(sk_word_t,sk_word_t,sk_word_t);  /* FUN_001bea18 */
void sk_report_emit(sk_word_t,sk_word_t);  /* thunk_FUN_002acbb8 */
void sk_report_emit2(void);  /* FUN_0006b404 */
void sk_report_end(void);  /* FUN_0006b550 */
void sk_report_end2(void);  /* FUN_0006b6ac */
void sk_report_end3(void);  /* FUN_0006b4d0 */
void sk_report_finish(void*);  /* FUN_000026e8 */
void sk_report_flush(void);  /* FUN_0006b560 */
void sk_report_flush2(void);  /* FUN_0006b728 */
void sk_report_flush3(void);  /* FUN_0006b714 */
void sk_report_free(sk_word_t);  /* FUN_003a25d4 */
void sk_report_iter_init(sk_word_t*,long*);  /* FUN_0006afb4 */
void sk_report_lock(int);  /* FUN_002a4ab4 */
void sk_report_lock2(void);  /* FUN_0006b65c */
void sk_report_lock3(void);  /* FUN_0006b3a4 */
void sk_report_lookup_save(sk_word_t,sk_word_t);  /* FUN_001b9084 */
void sk_report_proc(void*,void*);  /* FUN_0006a4c0 */
void sk_report_proc2(sk_word_t);  /* FUN_0006a4f0 */
void sk_report_proc3(void);  /* FUN_0006a520 */
void sk_report_proc4(void);  /* FUN_0006a5e4 */
void sk_report_proc5(sk_word_t);  /* FUN_0006a668 */
void sk_report_proc6(void);  /* FUN_0006a698 */
void sk_report_proc7(void);  /* FUN_0006a7c8 */
void sk_report_ref(void*,int);  /* FUN_003a25e0 */
void sk_report_unref(sk_word_t*);  /* FUN_0006afec */
void sk_ro_frame_set(sk_word_t,sk_word_t,sk_word_t);  /* helper */
void sk_ro_frame_write(sk_word_t);  /* helper */
void sk_ro_slot_set(int,sk_word_t);  /* helper */
void sk_ro_slot_set2(int,sk_word_t);  /* helper */
void sk_ro_write8(sk_word_t);  /* helper */
void sk_root_helper(sk_word_t);  /* FUN_0005562c */
void sk_root_helper2(sk_word_t);  /* FUN_00055660 */
void sk_root_helper3(sk_word_t);  /* FUN_00055694 */
void sk_sched_init(void);  /* FUN_00055164 */
void sk_slide_sync(void);  /* FUN_004b8498 */
void sk_stack_ctx_init(void*,sk_word_t*);  /* thunk_FUN_00114aa0 */
void sk_stack_fail(void) __attribute__((noreturn));  /* FUN_0011d7e8 */
void sk_stack_zero(void *p);  /* thunk_FUN_00114330 */
void sk_state_export(void);  /* FUN_0036a1a0 */
void sk_state_import(void*,sk_word_t,int,int);  /* FUN_0036a1a0 */
void sk_state_prep(void*);  /* FUN_0006fd6c */
void sk_strlcpy(char*,const char*,unsigned long);  /* FUN_00117cc4 */
void sk_uart_init(void);  /* FUN_0005c16c */
void sk_unpin_cpu(void);  /* FUN_0005fea8 */
void sk_untyped_fail(sk_word_t,int);  /* FUN_00055a90 */
void sk_uuid(sk_word_t*);  /* FUN_00054c3c */
void sk_vspace_bad(void) __attribute__((noreturn));  /* FUN_004b808c */
void sk_vspace_build(sk_word_t,sk_word_t*);  /* FUN_0006e7c0 */
void sk_zero(sk_word_t,int,unsigned long);  /* FUN_001143a0 */
void sk_zero32(void*,unsigned long);  /* thunk_FUN_00114330 */
void wr64(volatile unsigned char*,sk_word_t);  
/* ------------------------------------------------------------------ *
 * Forward declarations for every function defined in this region. */
sk_word_t sk_altstack_launch(void *arg0, void *arg1, void *arg2);
sk_word_t sk_altstack_setup(sk_word_t *frame, void *arg1, void *arg2);
void sk_cpu_frame_guard(void);
void sk_dispatch_indirect(sk_word_t (*fp)(sk_word_t), sk_word_t arg);
sk_word_t sk_obj_field_a8(void *obj);
sk_word_t sk_boot_error_string(void);
void sk_error_code_to_string(unsigned char code, char *out, unsigned long n);
void sk_error_string_table_copy(void);
void sk_noop_604f8(void);
long sk_thread_ref_bump(void);
void sk_flag_enable(void);
unsigned char sk_flag_get(void);
unsigned char sk_flag_get2(void);
unsigned char sk_boot_const_a2(void);
void sk_boot_phase_notify(void *phase);
void sk_boot_phase_drain(void);
sk_word_t sk_stack_alloc_top(sk_word_t size);
void sk_boot_main(void *arg0, sk_word_t boot_type, void **rsp, void **arg4, void *arg5);
sk_word_t sk_ipc_msg_dispatch(void *tcb, sk_word_t *word, void *a, sk_word_t b, sk_word_t flags, unsigned char c);
void sk_ipc_msg_dispatch_fwd(void);
sk_word_t sk_ipc_msg_dispatch2(void *tcb, sk_word_t *word, void *a, sk_word_t b, sk_word_t flags, unsigned char c);
sk_word_t sk_ipc_transfer(void *mr, sk_word_t *word, sk_word_t *dst, sk_word_t lim, sk_word_t mode, unsigned char k, sk_word_t *extra, unsigned char *consumed);
void sk_obj_slot_set(void *obj, sk_word_t v);
sk_word_t sk_stack_alloc(sk_word_t size, sk_word_t off);
sk_word_t sk_obj_field_140(void *obj);
sk_word_t sk_stack_alloc_type(sk_word_t size, unsigned char kind);
sk_word_t sk_stack_alloc_hi(sk_word_t off, sk_word_t size);
sk_word_t sk_stack_alloc_off(sk_word_t off);
sk_word_t sk_stack_alloc_low(sk_word_t off);
sk_word_t sk_stack_alloc_mid(sk_word_t off);
void sk_region_bounds_get(void *obj, sk_word_t *base, sk_word_t *size);
void sk_region_layout_set(void *obj, sk_word_t a, sk_word_t b, sk_word_t base, sk_word_t hi);
sk_word_t sk_obj_field_28(void *obj);
sk_word_t sk_exc_state_read_wrap(void *obj);
void sk_exc_state_read_discard(void *obj);
void sk_exc_state_read(sk_word_t *out, sk_word_t ctx);
void sk_obj_id_set(void *obj, unsigned int id);
void sk_log_obj_fields(void *obj, sk_word_t tag);
sk_word_t sk_obj_field_120(void *obj);
void sk_obj_link_set(void *obj, void *link);
void sk_exc_state_read_cpu(sk_word_t *out, void *ctx);
void sk_exc_state_read2(sk_word_t *out, sk_word_t sel);
void sk_error_code_str_out(char *out, unsigned char code);
sk_word_t sk_ipc_load_word(void *tcb);
void sk_backtrace_dump(char *out, void *tcb);
bool sk_regs_capture(void *tcb, sk_word_t *buf);
void sk_regs_dump(char *out, void *tcb);
void sk_crash_report(char *out, int a2, long a3, void *thread, int show_bt, int show_regs, sk_word_t esr, sk_word_t far);
void sk_rule(char *out, int fill, long text);
bool sk_flag_test_41(void *obj);
sk_word_t sk_ref_acquire_flag(void *obj, void *arg);
sk_word_t sk_ref_acquire_flag2(void *obj, void *arg);
void sk_ref_release_flag(void *obj, void *arg);
void sk_handler_set(long idx, void *handler, void *arg);
sk_word_t sk_cap_resolve_word(sk_word_t cap);
void sk_tightbeam_lookup(int kind, unsigned int sub);
void sk_error_str_fwd(void);
void sk_key_set_deleted_panic(void) __attribute__((noreturn));
void sk_key_set_destructor_panic(void) __attribute__((noreturn));
void sk_ep_lock_setup(sk_word_t *ep, sk_word_t key, long *cfg);
void sk_ep_return_dispatch(void *arg1, void *arg2);
void sk_error_str_out2(char *out, unsigned char code);
void sk_ep_create_threads(void *ep, sk_word_t want);
void sk_ep_setup_wrap(sk_word_t *ep, sk_word_t key, void *a, sk_word_t *cfg);
sk_word_t sk_ep_notif_tail(void);
sk_word_t sk_ep_notif_at(void *ep, long i);
sk_word_t sk_obj_field_20(void *obj);
sk_word_t sk_obj_field_28b(void *obj);
void sk_ep_drain(void *ctx);
void sk_ep_restore(void *ctx);
void sk_error_str_fwd2(void);
sk_word_t sk_list_pop(sk_word_t out, sk_word_t count);
sk_word_t sk_ep_obj_get(sk_word_t obj);
void sk_ep_obj_check(sk_word_t obj);
unsigned int sk_ep_id(sk_word_t obj);
void sk_ro_write(void *a, sk_word_t *word);
void sk_key_table_get(void);
void sk_key_table_seed(void);
sk_word_t sk_key_alloc(void *a, void *b, void *c);
void sk_key_lock(void);
void sk_key_store(long idx, long val, sk_word_t cb, int do_cb);
void sk_key_unlock(void);
void sk_key_construct_all(long *vals);
void sk_key_drain(void);
void sk_per_cpu_set(sk_word_t cpu);
sk_word_t sk_key_construct_cb(long *idx, sk_word_t a);
sk_word_t sk_stack_base(void);
void sk_obj_ctx_init(sk_word_t obj);
bool sk_exc_ep_active(void);
void sk_exc_ep_setup(void);
long sk_vspace_freeze(void *a, sk_word_t mode, void *obj);
void sk_error_str_out3(char *out, unsigned char code);
sk_word_t sk_amx_cap_alloc_fwd(void *a, void *obj);
sk_word_t sk_amx_cap_alloc(void *a, void *obj, long *req);
void sk_list_push(void **node);
sk_word_t sk_sme_cap_alloc(void *a, void *obj, long *req);
void sk_amx_cap_alloc2(void *obj);
long sk_amx_ep_alloc(sk_word_t a);
sk_word_t sk_exc_default(void *a, sk_word_t *cls);
void sk_exc_report(sk_word_t a, sk_word_t esr, sk_word_t far);
sk_word_t sk_xrt_freeze(void);
void sk_error_str_fwd3(void);
void sk_noop_65158(void);
void sk_noop_6516c(void);
void sk_ro_frame_byte(sk_word_t a, sk_word_t b, sk_word_t c);
void sk_noop_651ac(void);
void sk_noop_651bc(void);
void sk_error_str_fwd4(void);
void sk_exc_classify(sk_word_t *out, void *obj, sk_word_t *in);
void sk_exc_16_copy(void *dst, const void *src);
sk_word_t sk_exc_special(void);
void sk_error_str_out4(char *out, unsigned char code);
void sk_dt_table_set(sk_word_t t);
void sk_dt_lookup_global(sk_word_t a, void *b);
long sk_dt_lookup(long *tbl, sk_word_t key, long *out);
void sk_dt_table_set2(sk_word_t t);
void sk_dt_lookup_global2(sk_word_t a, void *b);
sk_word_t sk_dt_property_get(sk_word_t *out);
sk_word_t sk_dt_parse(sk_word_t base, sk_word_t size, sk_word_t *out);
sk_word_t sk_dt_lookup_region(sk_word_t base, sk_word_t size, sk_word_t *out);
void sk_dt_integrity_parse(sk_word_t a, sk_word_t b, sk_word_t (*cb)(sk_word_t*, sk_word_t), sk_word_t cbarg);
sk_word_t sk_dt_parse_cb(sk_word_t *ctx, sk_word_t p2);
sk_word_t sk_dt_validate_range(long base, sk_word_t size, sk_word_t *out);
bool sk_dt_next(void *ctx);
sk_word_t sk_dt_walk(void *ctx);
void sk_dt_node_init(long base, sk_word_t size, long *out);
bool sk_dt_child(sk_word_t *dt, sk_word_t *addr, sk_word_t *len);
sk_word_t sk_dt_name_cmp(void);
bool sk_dt_prop(sk_word_t *dt, sk_word_t *ptr, sk_word_t *len);
sk_word_t sk_dt_prop_lookup(long base, sk_word_t size, const char *name, sk_word_t *ptr, sk_word_t *len);
bool sk_dt_eof(sk_word_t *dt);
sk_word_t sk_dt_advance(sk_word_t *dt);
sk_word_t sk_dt_node_children(sk_word_t *ctx, sk_word_t *out);
sk_word_t sk_dt_cursor(sk_word_t *dt);
sk_word_t sk_dt_parse_driver(sk_word_t ctx0, sk_word_t *root, sk_word_t (*cb)(sk_word_t*, sk_word_t), sk_word_t cbarg);
bool sk_dt_list_get(sk_word_t *list, sk_word_t idx, sk_word_t *out);
sk_word_t sk_dt_list_count(sk_word_t *list);
void sk_dt_overflow_panic(void) __attribute__((noreturn));
void sk_dt_noop(void);
void sk_dt_prop_get_fwd(void);
void sk_dt_parse_fwd(void);
void sk_dt_lookup_region_fwd(void);
void sk_dt_integrity_fwd(void);
void sk_dt_list_get_fwd(void);
sk_word_t sk_dt_list_count_fwd(sk_word_t *list);
void sk_dt_prop_lookup_fwd(void);
void sk_dt_node_init_fwd(void);
void sk_dt_advance_fwd(void);
void sk_dt_eof_fwd(void);
void sk_dt_child_fwd(void);
void sk_dt_prop_fwd(void);
void sk_dt_range_fwd(void);
void sk_dt_next_fwd(void);
void sk_dt_walk_fwd(void);
void sk_dt_children_fwd(void);
sk_word_t sk_dt_boot_prop_load(void);
void sk_dt_boot_parse(void);
sk_word_t sk_dt_boot_lookup(void);
sk_word_t sk_dt_paged_call(sk_word_t *fp, sk_word_t arg);
unsigned int sk_boot_dt_integrity_check(void *a, void *b, sk_word_t c, sk_word_t d);
unsigned int sk_dt_boot_ok(void);
void sk_dt_boot_free1(void);
void sk_dt_boot_free2(void);
void sk_dt_boot_cb(unsigned char *out, sk_word_t *word);
unsigned int sk_dt_boot_cb2(void);
unsigned int sk_dt_boot_cb3(void);
sk_word_t sk_boot_console_init(sk_word_t a, unsigned int mode);
void sk_dt_node_get(sk_word_t key, sk_word_t a, sk_word_t b);
void sk_console_mem(void);
void sk_console_init(void);
void sk_boot_obj_call(sk_word_t *out);
void sk_boot_branch_call(sk_word_t a, long arg);
void sk_boot_branch_call_ctx(long arg);
void sk_boot_branch_call_obj(void);
sk_word_t sk_panic_report_start(sk_word_t a, sk_word_t b);
void sk_panic_report_body(sk_word_t a, void *arg);
void sk_panic_iter_begin(void);
void sk_panic_iter_next(long *out);
void sk_panic_iter_end(void);
sk_word_t sk_dt_iter_next16(void);
void sk_dt_lookup_fatal(sk_word_t key);
sk_word_t sk_report_word(sk_word_t v);
void sk_report_slot3(sk_word_t *out, sk_word_t a, sk_word_t b, sk_word_t c);
sk_word_t sk_get0(void);
sk_word_t sk_report_kind2(void);
sk_word_t sk_dt_list_copy(sk_word_t *out, sk_word_t *dst, sk_word_t count, void *list);
void sk_dt_list_copy4(sk_word_t a, sk_word_t b, sk_word_t c, sk_word_t d);
void sk_console_tree_print(sk_word_t list);
sk_word_t sk_iter_next_idx(void);
void sk_iter_next_byte(sk_word_t *out, sk_word_t a, sk_word_t b, unsigned char f);
void sk_iter_begin_wrap(sk_word_t *out);
void sk_console_ensure(long a, long b);
sk_word_t sk_hex_dump(sk_word_t a, sk_word_t b, unsigned char *data, void **limit);
void sk_iter_next_wrap(sk_word_t *out);
void sk_dt_iter_cb(sk_word_t *out);
void sk_iter_end_wrap(sk_word_t *out);
void sk_iter_next16_wrap(sk_word_t *out, sk_word_t a, sk_word_t b, unsigned char f);
void sk_hex_nibble1(void);
void sk_hex_nibble2(void);
void sk_hex_digit2(unsigned char c);
sk_word_t sk_console_tree_dump(void);
void sk_console_collect(long list);
unsigned int sk_report_type(sk_word_t lo, sk_word_t hi);
void sk_report_type_byte(unsigned char *out);
sk_word_t sk_report_end_val(void);
void sk_report_emit_indirect(void);
sk_word_t sk_report_cmp_pair(sk_word_t a, sk_word_t b, sk_word_t c, sk_word_t d);
sk_word_t sk_report_cmp(long *a, long *b);
unsigned int sk_report_cmp2(long *a, long *b);
void sk_report_flush_line(void *rec);
sk_word_t sk_report_process_rec(void *rec);
void sk_report_process_wrap(sk_word_t *out);
void sk_report_flush_line2(sk_word_t a);
void sk_report_flush_line3(sk_word_t a);
long sk_buf_resize(sk_word_t mode, sk_word_t need, sk_word_t grow, long buf, void *(*growf)(sk_word_t,sk_word_t), void (*movef)(void*,sk_word_t,long), void (*freef)(void));
long sk_buf_resize10(sk_word_t mode, sk_word_t need, sk_word_t grow, long buf, sk_word_t key, sk_word_t tag, void (*movef)(void*,sk_word_t,long), void (*freef)(void));
sk_word_t sk_buf_copy10(long src, long cnt, sk_word_t dst, long srcbuf);
sk_word_t sk_buf_copy20(long src, long cnt, sk_word_t dst, long srcbuf);
sk_word_t sk_buf_copy16(long src, long cnt, sk_word_t dst, long srcbuf);
sk_word_t sk_buf_copy18(long src, long cnt, sk_word_t dst, long srcbuf);
void sk_buf_memcpy16(sk_word_t dst, long count, sk_word_t src);
void sk_buf_memcpy20(sk_word_t dst, long count, sk_word_t src);
void sk_buf_memcpy18(sk_word_t dst, long count, sk_word_t src);
long sk_dt_iter4(sk_word_t *out, long *dst, long limit, sk_word_t a, sk_word_t b);
long sk_dt_iter2(sk_word_t *out, sk_word_t *dst, long limit, sk_word_t a, sk_word_t b);
void sk_buf_resize10_wrap(void);
void sk_cb_init(long *slot, sk_word_t a, sk_word_t b, sk_word_t c);
void sk_console_load_e050(void);
void sk_buf_resize10_wrap2(void);
long sk_obj_len_field(sk_word_t p);
void sk_console_load_e068(void);
void sk_console_load_e088(void);
long sk_obj_len_field2(sk_word_t p);
void sk_console_load_e090(void);
void sk_cb_init2(long *slot, sk_word_t a, sk_word_t c);
void sk_console_load_e0a0(void);
void sk_console_cb_init(void);
void sk_report_build_index(void *rec, unsigned int flags, long **index);
void sk_report_lookup_ctx(sk_word_t k0, sk_word_t k1);
sk_word_t sk_report_lookup2(long k0, long k1, sk_word_t start);
void sk_report_index_begin(long *out, long idx);
sk_word_t sk_report_index_deinit(sk_word_t idx);
void sk_dt_list_copy_fwd(void);
void sk_dt_list_copy_fwd2(void);
void sk_dt_boot_prop_wrap(void);
void sk_iter_begin_wrap2(void);
void sk_iter_end_wrap2(void);
sk_word_t sk_report_slot_addr(void);
void sk_noop_6b2dc(void);
void sk_noop_6b2ec(void);
void sk_noop_6b2fc(void);
void sk_console_state4(void);
void sk_noop_6b360(void);
void sk_console_enter2(void);
void sk_noop_6b3a4(void);
bool sk_gt1(sk_word_t v);
void sk_buf_grow_wrap(void);
sk_word_t sk_buf_next_ptr(long p);
void sk_noop_6b404(void);
bool sk_gt1b(sk_word_t v);
int sk_inc_w8(void);
void sk_hex_col_w(sk_word_t v);
void sk_noop_6b45c(void);
void sk_noop_6b474(void);
void sk_console_init5(void);
void sk_buf_grow_init(void);
void sk_noop_6b4c0(void);
void sk_fatal_dt_kit(void);
sk_word_t sk_buf_slot16a(void);
sk_word_t sk_buf_slot16b(void);
void sk_hex_char30(void);
void sk_report_emit_nt(void);
sk_word_t sk_report_end_rec(sk_word_t p);
sk_word_t sk_report_out_bound(void);
sk_word_t sk_report_name_rec(sk_word_t v, long sel);
void sk_report_emit_hdr(void);
void sk_console_state5(void);
void sk_console_state6(void);
sk_word_t sk_report_space_rec(void);
sk_word_t sk_report_zero_rec(void);
void sk_noop_6b620(void);
void sk_noop_6b630(void);
void sk_report_ize(void);
sk_word_t sk_report_framerec(void);
void sk_noop_6b674(void);
sk_word_t sk_report_nl_rec(void);
void sk_noop_6b68c(void);
void sk_noop_6b6a0(void);
void sk_noop_6b6ac(void);
void sk_report_store_slot(void);
void sk_noop_6b6d4(void);
sk_word_t sk_report_free0(void);
void sk_noop_6b6f4(void);
void sk_report_dots(void);
void sk_report_sym_e080(void);
void sk_report_sym_e060(void);
unsigned char sk_perm_flag_get(void);
unsigned char sk_perm_flag_get2(void);
void sk_perm_set_hi(sk_word_t v);
void sk_perm_set_lo(sk_word_t v);
sk_word_t sk_perm_get_hi(void);
sk_word_t sk_perm_get_lo(void);
void sk_ipmm_init_flag(void);
void sk_ipmm_setup(void);
void sk_ipmm_log(void);
sk_word_t sk_ipmm_count_get(void);
sk_word_t sk_ipmm_alloc_stat(void);
sk_word_t sk_ipmm_free_stat(void);
void sk_err_rec_fill(sk_word_t *rec, unsigned char code);
void sk_err_rec_print(sk_word_t rec);
sk_word_t sk_ipmm_alloc(sk_word_t a, sk_word_t type, sk_word_t size, sk_word_t pa, unsigned int flags);
void sk_ipmm_free(sk_word_t a, sk_word_t frame);
void sk_err_rec_fill0(void);
void sk_noop_6c1d4(void);
void sk_err_rec_fill1(void);
void sk_err_rec_fill2(void);
void sk_noop_6c214(void);
void sk_vspace_table_ready(unsigned char v);
void sk_vspace_client_find(short tag);
sk_word_t sk_vspace_client_add(long addr);
void sk_vspace_client_clear(void);
sk_word_t sk_vspace_client_field(void);
sk_word_t sk_vspace_client_remove(void);
void sk_bootinfo_parse(long *caps, int do_zero);
void sk_bootinfo_parse_fwd(sk_word_t c);
sk_word_t sk_dt_roottask(void);
sk_word_t sk_dev_entry(sk_word_t i);
sk_word_t sk_feature_get_a(sk_word_t i);
sk_word_t sk_feature_get_b(sk_word_t i);
sk_word_t sk_untyped_find(sk_word_t addr);
sk_word_t sk_untyped_find_base2(void);
sk_word_t sk_untyped_base_for(sk_word_t addr);
long sk_untyped_offset_for(sk_word_t addr);
sk_word_t sk_untyped_size_for(sk_word_t addr);
bool sk_untyped_contains(sk_word_t addr);
sk_word_t sk_pmm_alloc(sk_word_t size, sk_word_t flags);
sk_word_t sk_boot_region_base(void);
sk_word_t sk_boot_free_bytes(void);
sk_word_t sk_boot_cfg_get(void);
unsigned char sk_boot_dual_region(void);
sk_word_t sk_region_lo_g(void);
sk_word_t sk_region_lo_cap(void);
sk_word_t sk_region_hi_g(void);
sk_word_t sk_region_hi_cap(void);
sk_word_t sk_boot_device_cap(void);
sk_word_t sk_text_slide_get_sync(void);
sk_word_t sk_text_slide_get_sync2(void);
sk_word_t sk_text_slide_get(void);
sk_word_t sk_data_slide_get(void);
sk_word_t sk_dart_find(int sid, int sid2);
sk_word_t sk_dart_table_find(int tid, int tid2);
void sk_dart_table_clear(int tid, int tid2);
void sk_bootinfo_set_root(sk_word_t r);
void sk_bootinfo_root_call(void);
void sk_bootinfo_set_range(sk_word_t lo, sk_word_t hi);
void sk_bootinfo_call_a(void);
void sk_bootinfo_call_b(void);
sk_word_t sk_pmm_bitmap(void);
sk_word_t sk_pmm_granule(void);
void sk_err_rec_fill_b(sk_word_t *rec, unsigned char code);
void sk_region_usage_update(long desc);
void sk_err_rec_fill_b0(void);
void sk_err_rec_fill_b1(void);
void sk_vspace_region_init(void *obj);
sk_word_t sk_get0_2(void);
void sk_commpage_mint(void);
void sk_commpage_slot_set(sk_word_t v);
sk_word_t sk_commpage_mint_cap(sk_word_t mode);
void sk_cs_map(sk_word_t a, sk_word_t b, sk_word_t mode);
void sk_vspace_region_init2(sk_word_t a);
void sk_commpage_mint2(void);
void sk_obj_free_p10(void);
void sk_obj_free_p10b(void);
void sk_obj_free_p10_tear(void);
void sk_obj_free_p10_tear2(void);
sk_word_t sk_commpage_kind(void);
void sk_commpage_obj_alloc(sk_word_t *out);
void sk_ctx3_init(void);
void sk_ctx3_init2(void);
void sk_ctx4_init(void);
void sk_ctx4_init2(void);
sk_word_t sk_boot_one(void);
sk_word_t sk_zero16(void);
void sk_ctx5_init(void);
void sk_ctx5_init2(void);
long sk_commpage_alloc2(void);
void sk_ctx6_init(void);
void sk_ctx7_init(void);
void sk_ctx7_init2(void);
long sk_commpage_alloc3(void);
void sk_ctx8_init(void);
void sk_ctx8_init2(void);
void sk_ctx9_init(void);
void sk_ctxa_init(void);
void sk_ctxa_init2(void);
void sk_ctxb_init(void);
void sk_ctxb_init2(void);
void sk_ctxc_init(void);
void sk_ctxc_init2(void);
void sk_get4_0456c(unsigned int *out);
void sk_get4_84cc4(unsigned int *o, unsigned int *a);
void sk_get4_af4d8(unsigned int *o, unsigned int *a);
void sk_get8_af56c(unsigned int *o, unsigned int *a);
void sk_get8_af5fc(unsigned int *o, unsigned int *a);
void sk_get4_85754(unsigned int *o, unsigned int *a);
void sk_ctx_call(sk_word_t a);
void sk_ctx_call_h(sk_word_t a, sk_word_t b);
void sk_ctx_call2(sk_word_t a, sk_word_t b);
void sk_get4_aae60(unsigned int *o);
void sk_get16_6e6dc(unsigned short *o, unsigned char *a);
void sk_get_1a1c8(unsigned char *o);
void sk_get8_6e744(unsigned int *o, unsigned int *a);
void sk_get4_1a1c8(unsigned int *o);
sk_word_t sk_value_check16(long v);
long sk_obj_copy_field(long src, long dst);
sk_word_t sk_ctx_dt(void);
void sk_ctx_register(sk_word_t a);
void sk_ctx_register2(sk_word_t a);
void sk_ctx_bind(sk_word_t a);
void sk_ctx_bind2(sk_word_t a);
void sk_ctx_register3(sk_word_t a);
void sk_ctx_register4(sk_word_t a);
void sk_ctx_reg(long id, void *(*build)(long));
void sk_ctx_dispatch(sk_word_t a, long tbl, sk_word_t c);
void sk_ctx_bind3(sk_word_t a);
void sk_noop_6f684(void);
void sk_noop_6f69c(void);
void sk_noop_6f6f4(void);
void sk_noop_6f70c(void);
void sk_noop_6f768(void);
void sk_vspace_publish(sk_word_t *unused);
sk_word_t sk_kind3(void);
void sk_noop_6f7b4(void);
sk_word_t sk_ctx_token(void);
void sk_obj_state_out(sk_word_t *out);
void sk_obj_state_in(sk_word_t *in);
sk_word_t sk_obj_state_ref(sk_word_t in);
void sk_obj_state_word(sk_word_t *out);
sk_word_t sk_state_error_rec(void);
void sk_obj_free_tear(void);
void sk_obj_free_tear2(void);
void sk_state_word_fwd(void);
void sk_state_err_fwd(void);
void sk_obj_state_alloc(sk_word_t *in);
void sk_pac_register(long *res);
void sk_pac_commit(void);
void sk_pac_commit_fwd(void);
void sk_pac_commit_fwd2(void);
void sk_pac_register_fwd(void);
void sk_pac_register_fwd2(void);
void sk_pac_lookup(sk_word_t a, sk_word_t b);
sk_word_t sk_pac_token(void);
void sk_pac_link(sk_word_t lo, sk_word_t hi, long obj);
void sk_noop_6fd6c(void);
void sk_pac_obj(void);
sk_word_t sk_untyped_name(sk_word_t i, char quote);
void sk_ctx_call_bind(void);
sk_word_t sk_untyped_rec(sk_word_t v, char mode);

/* helper */


/* FUN_000600f0 @ 0x600f0   (est. sk_altstack_launch)
 * Ghidra: undefined8 FUN_000600f0(undefined8,undefined8,undefined8)
 * Prepares a 0x20-byte stack context block via the context-initializer FUN_0005ff04, runs the alternate-stack (altstack) setup routine 0x60164 over it, then performs an indirect call through the function pointer the initializer stashed on the stack. Returns whatever that callee produced.
 * Confidence: medium
 * Notes: Indirect call via stack slot puStack_58 set by FUN_0005ff04.
 */
sk_word_t sk_altstack_launch(void *arg0, void *arg1, void *arg2)
{
    sk_word_t ctx[4] = {0,0,0,0};
    void (**fp)(sk_word_t) = NULL;
    sk_word_t r;
    sk_ctx_init((void *)ctx, arg0, 0x20);      /* FUN_0005ff04 */
    r = sk_altstack_setup((void *)ctx, arg1, arg2);  /* FUN_00060164 */
    (*fp)(ctx[0]);                             /* indirect dispatch slot */
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00060164 @ 0x60164   (est. sk_altstack_setup)
 * Ghidra: undefined8 FUN_00060164(long,undefined8,undefined8)
 * Sets up an alternate-stack (altstack) frame for the current thread. Validates the target isn't already on the altstack, that the altstack has a nonzero ID, and (when flagged) re-pins the current CPU context before writing the saved frame (return address 0x60208, stack base, limit, ID and flags) into the per-CPU context block. Then runs the body function, optionally priming/zeroing the destination stack range and copying in an initial context. Restores and clears the frame registers on return.
 * Confidence: medium
 * Notes: Strings: 'thread is already on altstack %d' (s_thread_is_already_on_altstack__d_005bd130), 'altstack %p has zero ID' (s_altstack__p_has_zero_ID_005bd151). Calls CallSupervisor(4) in the priming loop; SoftwareBreakpoint(0x5519,0x60354) on a bad copy range.
 */
sk_word_t sk_altstack_setup(sk_word_t *frame, void *arg1, void *arg2)
{
    void **svc = *(void ***)(frame + 4);
    sk_word_t *cpu = sk_per_cpu_base();        /* FUN_00060524 */
    void **base;
    if (*(int *)(cpu + 0x148) != 0)
        sk_panic("thread is already on altstack %d");   /* FUN_004afae4 */
    if (*(int *)(frame + 0x30/8) == 0)
        sk_panic("altstack %p has zero ID");            /* FUN_004afae4 */
    if ((*(char *)(frame + 0x10/8) >> 3) & 1) {
        sk_pin_cpu();                          /* FUN_0005fe48 */
    }
    cpu[0x160/8] = (sk_word_t)0x60208;
    cpu[0x150/8] = *(sk_word_t *)(frame + 0x18/8);
    cpu[0x158/8] = (sk_word_t)0;
    cpu[0x14c/8] = (int)*(sk_word_t *)(frame + 0x28/8);
    cpu[0x148/8] = *(int *)(frame + 0x30/8);
    {
        sk_word_t save168 = cpu[0x168/8];
        sk_word_t save170 = cpu[0x170/8];
        cpu[0x168/8] = *(sk_word_t *)(frame + 0x18/8) + 0x4000;
        cpu[0x170/8] = (sk_word_t)svc;
        sk_altstack_body(svc, arg1, arg2);     /* FUN_0005cf18 */
        cpu[0x168/8] = save168;
        cpu[0x170/8] = save170;
    }
    cpu[0x148/8] = 0; cpu[0x160/8] = 0; cpu[0x164/8] = 0;
    cpu[0x158/8] = 0; cpu[0x15c/8] = 0; cpu[0x150/8] = 0;
    cpu[0x154/8] = 0; cpu[0x14c/8] = 0;
    if ((*(uint *)(frame + 0x10/8) >> 4) & 1) {
        void *cs = sk_ctx_state();             /* FUN_00034f70 */
        void **dst = (void **)(*(long *)(frame + 0x18/8) + 0x4000);
        void **cur = (void **)svc;
        int done = 0;
        sk_word_t off = 0;
        do {
            if ((cur <= dst) || ((cur -= 0x800) < dst)) break;
            sk_ctx_frame_t cf = sk_ctx_frame();   /* FUN_00034a2c */
            sk_word_t (*cfn)(void*,void*,void*,void*) = *(sk_word_t(**)(void*,void*,void*,void*))(uintptr_t)cf.v0;
            done = cfn((void*)(uintptr_t)cf.v0, cur, 0, cs);
            do { CallSupervisor(4); } while ((long)cs == 1);
            off += 0x4000;
        } while (!done);
        sk_ctx_finish(cs);                     /* FUN_004b23d8 */
        {
            sk_word_t delta = (sk_word_t)svc - (sk_word_t)cur;
            if (delta != 0) {
                svc = (void**)((long)cur + delta);
                if ((*(uint *)(frame + 0x10/8) >> 3) & 1) {
                    if (delta > 7) {
                        sk_word_t cnt = (delta >> 3) < 2 ? 1 : (delta >> 3);
                        void **p = cur;
                        do { *p = 0; p++; } while (--cnt);
                    }
                } else {
                    if (((void**)cur < cur) || (sk_word_t)svc - (sk_word_t)cur < delta)
                        sk_breakpoint(0x5519, 0x60354);
                    sk_stack_zero(cur);        /* thunk_FUN_00114330 */
                }
            }
        }
    }
    if ((*(uint *)(frame + 0x10/8) >> 3) & 1)
        sk_unpin_cpu();                        /* FUN_0005fea8 */
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006037c @ 0x6037c   (est. sk_cpu_frame_guard)
 * Ghidra: void FUN_0006037c(void)
 * Reads the per-CPU context and asserts the saved-frame low bound (+0x104) is at or below the high bound (+0x108). If the range is inverted it raises a breakpoint trap; otherwise returns normally.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x603ac) on inverted range.
 */
void sk_cpu_frame_guard(void)
{
    sk_word_t *cpu = sk_per_cpu_base();   /* FUN_00060524 */
    if ((sk_word_t)(cpu + 0x104/8) <= (sk_word_t)(cpu + 0x108/8))
        return;
    sk_breakpoint(0x5519, 0x603ac);       /* SoftwareBreakpoint */
}

/*--------------------------------------------------------------------*/

/* FUN_000603ac @ 0x603ac   (est. sk_dispatch_indirect)
 * Ghidra: void FUN_000603ac(code*,undefined8)
 * Indirect-dispatch stub: performs a call through the supplied function pointer, passing the single argument. The target is resolved at runtime (jumptable not recoverable).
 * Confidence: low
 * Notes: Indirect jump; 'Could not recover jumptable at 0x603b8'.
 */
void sk_dispatch_indirect(sk_word_t (*fp)(sk_word_t), sk_word_t arg)
{
    fp(arg);
}

/*--------------------------------------------------------------------*/

/* FUN_000603bc @ 0x603bc   (est. sk_obj_field_a8)
 * Ghidra: undefined8 FUN_000603bc(long)
 * Returns the 64-bit field at offset 0xa8 of the given object — a getter for an object/TCB metadata word (likely a capability or link pointer).
 * Confidence: medium
 */
sk_word_t sk_obj_field_a8(void *obj)
{
    return *(sk_word_t *)((char *)obj + 0xa8);
}

/*--------------------------------------------------------------------*/

/* FUN_000603c4 @ 0x603c4   (est. sk_boot_error_string)
 * Ghidra: undefined8 FUN_000603c4(void)
 * Walks the boot/init data structure collecting an L4 error/status code: iterates a linked list of descriptors via several accessor helpers, and when it finds the entry with code 0x1c it reads a packed multi-byte key and returns it as a 64-bit value. Returns 0 when no such entry exists.
 * Confidence: low
 * Notes: Dense iterator over boot descriptors; helpers FUN_0004fe80/0004ed48/0004eb44/0004ecf0/0004eb4c/0004e88c/0004e7b8/0004ed84/0004e774.
 */
sk_word_t sk_boot_error_string(void)
{
    int st = sk_boot_begin();                  /* FUN_0004fe80 */
    if (st != 0) {
        void *node = sk_boot_next();           /* FUN_0004ed48 */
        if (node != 0) {
            if (node + 8 < (void *)node)
                sk_breakpoint(0x5519, 0x604cc);
        }
        void *it = sk_boot_iter();             /* FUN_0004eb44 */
        while ((sk_boot_more(it) & 1) == 0) {  /* FUN_0004ecf0 */
            void *e = sk_boot_ent(it);         /* FUN_0004eb4c */
            if (e != 0 && e + 0xc < (void *)e)
                sk_breakpoint(0x5519, 0x604cc);
            int code = sk_boot_code(e);        /* FUN_0004e88c */
            if (code == 0x1c) {
                unsigned char *p = sk_boot_key(e, 0);   /* FUN_0004e7b8 */
                return sk_boot_pack_key(p);    /* FUN_0004e774 */
            }
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_000604cc @ 0x604cc   (est. sk_error_code_to_string)
 * Ghidra: void FUN_000604cc(byte)
 * Converts an L4 error code (0-9) into its canonical L4_ErrorCode* string and copies up to 0x20 bytes to the caller's output buffer. Codes above 9 use a generic fallback string.
 * Confidence: high
 * Notes: Strings: s_L4_ErrorCodeSuccess_004be1b0..s_L4_ErrorCodePermissionInvalid_004be2d0.
 */
void sk_error_code_to_string(unsigned char code, char *out, unsigned long n)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    const char *s = code <= 9 ? names[code] : "L4_ErrorCodeSuccess";
    if (code > 9)
        s = "L4_ErrorCodeSuccess";
    sk_strlcpy(out, s, 0x20);   /* FUN_00117cc4 + FUN_0000178c */
}

/*--------------------------------------------------------------------*/

/* FUN_000604ec @ 0x604ec   (est. sk_error_string_table_copy)
 * Ghidra: void FUN_000604ec(void)
 * Table-driven copy of an L4 error code string: selects the name for the error code in w20 (register-passed; the decompiler lost the argument) and copies 0x20 bytes to the output. The switch is over the same 0-9 code range.
 * Confidence: low
 * Notes: unaff_w20 register argument not reconstructed; mirror of 0x604cc.
 */
void sk_error_string_table_copy(void)
{
    unsigned char code = sk_err_reg();   /* error code from w20 */
    sk_error_code_to_string(code, sk_err_out(), 0x20);
}

/*--------------------------------------------------------------------*/

/* FUN_000604f8 @ 0x604f8   (est. sk_noop_604f8)
 * Ghidra: void FUN_000604f8(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_604f8(void){ }

/*--------------------------------------------------------------------*/

/* FUN_000604fc @ 0x604fc   (est. sk_thread_ref_bump)
 * Ghidra: long FUN_000604fc(void)
 * Increments and returns the current thread's reference/activity counter (field +0x30).
 * Confidence: medium
 * Notes: FUN_0005bb68.
 */
long sk_thread_ref_bump(void)
{
    void *tcb = sk_tcb_current();
    long c = *(long *)((char*)tcb + 0x30) + 1;
    *(long *)((char*)tcb + 0x30) = c;
    return c;
}

/*--------------------------------------------------------------------*/

/* FUN_00060524 @ 0x60524   (est. sk_per_cpu_base)
 * Ghidra: undefined8 FUN_00060524(void)
 * Returns the per-CPU context base: reads the current CPU id from tpidr_el0 and dereferences the per-CPU slot at offset 8.
 * Confidence: high
 * Notes: tpidr_el0 + 8.
 */
void *sk_per_cpu_base(void)
{
    return *(void **)((char *)__builtin_thread_pointer() + 8);
}

/*--------------------------------------------------------------------*/

/* FUN_00060530 @ 0x60530   (est. sk_flag_enable)
 * Ghidra: void FUN_00060530(void)
 * Sets the global boot/init flag DAT_006b26c8 to 1.
 * Confidence: high
 * Notes: DAT_006b26c8.
 */
void sk_flag_enable(void)
{
    sk_flag_1 = 1;   /* DAT_006b26c8 */
}

/*--------------------------------------------------------------------*/

/* FUN_00060540 @ 0x60540   (est. sk_flag_get)
 * Ghidra: undefined1 FUN_00060540(void)
 * Returns the global boot flag DAT_006b26c8.
 * Confidence: high
 * Notes: DAT_006b26c8.
 */
unsigned char sk_flag_get(void)
{
    return sk_flag_1;   /* DAT_006b26c8 */
}

/*--------------------------------------------------------------------*/

/* FUN_0006054c @ 0x6054c   (est. sk_flag_get2)
 * Ghidra: undefined1 FUN_0006054c(void)
 * Returns the global boot flag byte DAT_006b26c9.
 * Confidence: high
 * Notes: DAT_006b26c9.
 */
unsigned char sk_flag_get2(void)
{
    return sk_flag_2;   /* DAT_006b26c9 */
}

/*--------------------------------------------------------------------*/

/* FUN_00060564 @ 0x60564   (est. sk_boot_const_a2)
 * Ghidra: undefined1 FUN_00060564(void)
 * Returns the constant 0xa2 — a fixed boot/feature value.
 * Confidence: high
 */
unsigned char sk_boot_const_a2(void){ return 0xa2; }

/*--------------------------------------------------------------------*/

/* FUN_00060570 @ 0x60570   (est. sk_boot_phase_enter)
 * Ghidra: byte* FUN_00060570(byte*)
 * Boot-phase barrier accounting on the current CPU. Either records the current per-CPU phase flag into the caller's byte, or acquires the boot counter: bumps the global boot counter (DAT_006ad900) and the per-CPU count (+0x58), marks the CPU phase byte (+0x68) active, and when the counter crosses a 1024 boundary notifies the scheduler (0x605f8) and refreshes the per-CPU window (+0x78). Returns the phase byte.
 * Confidence: low
 * Notes: LOAcquire; globals DAT_006ad900; per-CPU fields +0x58/+0x68/+0x78; FUN_004b7098/004b70c8; spin via FUN_0005deb4.
 */
void *sk_boot_phase_enter(void *phase)
{
    void *cpu = sk_per_cpu_base();
    unsigned char cur = *(unsigned char *)((char *)cpu + 0x68);
    if (phase == NULL) {
        if (cur != 0) {
            void *pb = sk_cpu_phase();            /* FUN_004b7098 */
            cpu = sk_per_cpu_base();
            if ((*(unsigned char *)((char *)cpu + 0x68) & 1) == 0) {
                pb = sk_cpu_phase_slow();         /* FUN_004b70c8 */
                while ((sk_boot_counter & 0x3ff) != 0)
                    sk_cpu_yield(cpu);            /* FUN_0005deb4 */
                sk_boot_counter += 0x400;
                return pb;
            }
            if (pb == NULL) {
                *(unsigned char *)((char *)cpu + 0x68) = 0;
            } else {
                unsigned char nb = *(unsigned char *)pb;
                *(unsigned char *)((char *)cpu + 0x68) = nb;
                if (nb & 1) return pb;
            }
            *(long *)((char *)cpu + 0x58) -= 1;
            sk_boot_counter -= 1;
            return pb;
        }
    } else {
        *(unsigned char *)phase = cur;
        if (cur & 1) return (void *)1;
    }
    {
        unsigned long old = sk_boot_counter;
        sk_boot_lock();                            /* LOAcquire */
        sk_boot_counter += 1;
        *(unsigned char *)((char *)cpu + 0x68) = 1;
        *(long *)((char *)cpu + 0x58) += 1;
        if ((old >> 10) != *(unsigned long *)((char *)cpu + 0x78)) {
            sk_boot_phase_notify(0);               /* FUN_000605f8 */
            *(unsigned long *)((char *)cpu + 0x78) = old >> 10;
        }
        return (void *)(*(unsigned char *)((char *)cpu + 0x68) & 1);
    }
}

/*--------------------------------------------------------------------*/

/* FUN_000605f8 @ 0x605f8   (est. sk_boot_phase_notify)
 * Ghidra: void FUN_000605f8(byte*)
 * Completes a boot-phase leave: when the current CPU is not in an active phase it idles until the boot counter is 1024-aligned then advances it; otherwise it clears (or reloads) the CPU phase byte and decrements both the per-CPU count and the global boot counter.
 * Confidence: low
 * Notes: DAT_006ad900; per-CPU +0x58/+0x68; FUN_004b70c8/FUN_0005deb4.
 */
void sk_boot_phase_notify(void *phase)
{
    void *cpu = sk_per_cpu_base();
    if ((*(unsigned char *)((char *)cpu + 0x68) & 1) == 0) {
        sk_cpu_phase_slow();                       /* FUN_004b70c8 */
        while ((sk_boot_counter & 0x3ff) != 0)
            sk_cpu_yield(sk_per_cpu_base());       /* FUN_0005deb4 */
        sk_boot_counter += 0x400;
        return;
    }
    if (phase == NULL)
        *(unsigned char *)((char *)cpu + 0x68) = 0;
    else {
        unsigned char b = *(unsigned char *)phase;
        *(unsigned char *)((char *)cpu + 0x68) = b;
        if (b & 1) return;
    }
    *(long *)((char *)cpu + 0x58) -= 1;
    sk_boot_counter -= 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00060650 @ 0x60650   (est. sk_boot_phase_drain)
 * Ghidra: void FUN_00060650(void)
 * Drains the boot-phase counter: spins while the counter is not 1024-aligned, then advances it by 1024.
 * Confidence: medium
 * Notes: DAT_006ad900; FUN_0005deb4.
 */
void sk_boot_phase_drain(void)
{
    while ((sk_boot_counter & 0x3ff) != 0)
        sk_cpu_yield(sk_per_cpu_base());           /* FUN_0005deb4 */
    sk_boot_counter += 0x400;
}

/*--------------------------------------------------------------------*/

/* FUN_000606b0 @ 0x606b0   (est. sk_stack_alloc_top)
 * Ghidra: ulong FUN_000606b0(ulong)
 * Allocates the boot stack area: lazily seeds the global stack cursor DAT_006b2710 from a base (FUN_00063ffc), then returns a stack top computed from the cursor and the requested size (index shifted into the upper tag bits).
 * Confidence: low
 * Notes: DAT_006b2710; FUN_00063ffc; SoftwareBreakpoint(0x5519,0x606fc).
 */
sk_word_t sk_stack_alloc_top(sk_word_t size)
{
    sk_word_t base;
    if (sk_stack_cursor == 0) {
        base = sk_stack_base();                   /* FUN_00063ffc */
        sk_word_t a = (0x1fd00 - base) & ~0xfULL;
        if (a + base < a) sk_breakpoint(0x5519, 0x606fc);
        sk_stack_cursor = 0x20178 - a;            /* DAT_006b2710 */
    }
    return (sk_word_t)(uint)-(int)sk_stack_cursor & 0x3fff
           | (size & 0xffffffff) << 0xe;
}

/*--------------------------------------------------------------------*/

/* FUN_00060728 @ 0x60728   (est. sk_boot_main)
 * Ghidra: void FUN_00060728(undefined8,ulong,undefined8*,undefined8*,undefined8)
 * The secure-kernel boot entrypoint. On the first CPU it carves a boot stack and inits a boot descriptor block (magic 0x656e7472 'entr'); when asked to boot the root task it allocates the root-task context, copies the boot data, sets up the per-CPU pointers, and programs the RO thread pointer before CallSupervisor(0). It then dispatches by boot type through the entry-handler table (DAT_006b26d8); a missing handler or a returning handler raises the 'no handler set for entry' / 'unexpected thread exit' panics.
 * Confidence: medium
 * Notes: Magic 0x656e7472/0x696e6974; strings 'roottask', 'Security assertion failed: %s:%s:%d' (s_Security_assertion_failed___s__f_005a8b30), 'No handler set for entry %d%c%c' (s_No_handler_set_for_entry____04hh_005bd9b6), 'Unexpected thread exit %d%c%c' (s_Unexpected_thread_exit____04hhX_005bd9d8); handler table DAT_006b26d8; CallSupervisor(0); SoftwareBreakpoint(0x5519,0x608dc).
 */
void sk_boot_main(void *arg0, sk_word_t boot_type, void **rsp, void **arg4, void *arg5)
{
    void *cpu;
    void *task = NULL;
    sk_word_t bt = boot_type;

    cpu = (void *)__builtin_thread_pointer();
    if (cpu == NULL) {
        void **hi = (void **)(((sk_word_t)arg4 + 0x3fff) & ~0x3fffULL);
        sk_word_t w0 = 0;
        if (hi < arg4) sk_breakpoint(0x5519, 0x608dc);
        sk_stack_ctx_init(arg4, &w0);                       /* thunk_FUN_00114aa0 */
        void **cur = hi - 0x60;
        sk_word_t base = sk_stack_base();                   /* FUN_00063ffc */
        bt = ((sk_word_t)cur - base) & ~0xfULL;
        if (bt + base < bt) sk_breakpoint(0x5519, 0x608dc);
        sk_word_t lo = (sk_word_t)arg4 & ~0x3fffULL;
        sk_zero32((void*)cur - 0x60, 0x118);                /* thunk_FUN_00114330(0x118) */
        {
            /* boot descriptor magic 'entr' + header copy */
            unsigned char hdr[0x118];
            sk_zero32(hdr, 0x118);
            *(unsigned int*)hdr = 0x656e7472;
            sk_memcpy((void*)(bt - 0x178), hdr, 0x118);     /* FUN_00117cc4 */
            *(unsigned int*)(bt - 0x60) = 0x656e7472;
            sk_memcpy((void*)(bt - 0x5c), hdr, 0x14);
            *(sk_word_t*)(bt - 0x48) = lo;
            *(sk_word_t*)(bt - 0x40) = (sk_word_t)hi - lo;
            *(void**)(bt - 0x38) = arg4;
            *(sk_word_t*)(bt - 0x18) = 0;
            *(sk_word_t*)(bt - 0x20) = 0;
            *(sk_word_t*)(bt - 0x28) = 0;
            *(sk_word_t*)(bt - 0x30) = 0;
            *(sk_word_t*)(bt - 0x10) = lo;
            *(void**)(bt - 8) = arg4;
            sk_boot_descr(cur);                             /* FUN_00063ea4 */
        }
        *cur = (void*)(uintptr_t)bt;
        hi[-0x5f] = (void*)(bt - 0x178);
    }

    if (((boot_type & 0xfd) == 1) && (sk_root_task == NULL)) {
        sk_word_t base = sk_stack_base();                   /* FUN_00063ffc */
        bt = ((((sk_word_t)rsp + 0x3fff) & ~0x3fffULL) - base) - 0x300 & ~0xfULL;
        if (bt + base < bt) sk_breakpoint(0x5519, 0x608dc);
        void **t = (void **)(bt - 0x200);
        sk_root_task = t;                                   /* DAT_006b26d0 */
        sk_word_t kb = sk_kern_alloc();                     /* FUN_00063a94 */
        sk_word_t cb = sk_ctx_alloc();                      /* FUN_00063a50 */
        cpu = (void*)__builtin_thread_pointer();
        if (*(long *)((char *)cpu + 0xf8) != 0) goto fail_taken;
        if (*(long *)((char *)cpu + 0x10) != bt - 0x190) {
            if (*(long *)((char *)cpu + 0x10) != 0) {
                *(sk_word_t *)((char *)cpu + 0x10) = bt - 0x190;
                goto regs_ok;
            }
            long *g = (long *)(cb + 0x208);
            if (*g != -1) { *g += 1; *(sk_word_t *)((char *)cpu + 0x10) = bt - 0x190; goto regs_ok; }
            goto fail_taken;
        }
    regs_ok:
        if (kb + 0x2f0 < kb) sk_breakpoint(0x5519, 0x608dc);
        sk_boot_early();                                    /* FUN_0005ba40 */
        sk_boot_irq_init();                                 /* FUN_0005d5dc */
        sk_boot_mm_init();                                  /* FUN_0005ad40 */
        {
            void *bd = sk_boot_data(arg5);                  /* FUN_00054624 */
            if (*(long *)((char *)bd + 8) == 0)
                sk_boot_data_free(*(void **)((char *)bd + 0x18));  /* FUN_00052c4c */
            sk_sched_init();                                /* FUN_00055164 */
            unsigned char *bs = sk_boot_strings();          /* FUN_00054610 */
            sk_uart_init();                                 /* FUN_0005c16c */
            if ((*bs & 1) != 0) {
                long n = sk_boot_cnt(*(void **)(bs + 0x18));   /* FUN_000556c8 */
                sk_word_t sz = sk_boot_sz(*(void **)(bs + 0x18)); /* FUN_000556e4 */
                if (sz + n*8 < sz) sk_breakpoint(0x5519,0x608dc);
                sk_word_t want = n*8;
                if (sk_boot_copy(sz, want) != want)         /* FUN_0005c184 */
                    sk_boot_fail();                         /* FUN_004b7120 */
                sk_zero32((void*)sz, want);
                sk_boot_done_copy();                        /* FUN_00054dec */
                sk_boot_print();                            /* FUN_0011d790 */
                sk_cap_init(*(void **)(bd + 0x10));         /* FUN_00052a04 */
                if (*(long *)((char *)bd + 0xc0) == 0) {
                    long kind = *(long *)((char *)bd + 0xb8);
                    if (kind == 2) {
                        void *p = sk_boot_lookup(4, "idle");    /* FUN_0004dfd0 */
                        *(sk_word_t *)((char *)p + 8) |= 0x18;
                    } else if (kind == 1) {
                        void *p = sk_boot_lookup(0, "idle0");   /* FUN_0004dfd0 &DAT_005be7c0 */
                        *(sk_word_t *)((char *)p + 8) |= 0x15;
                    } else if (kind == 0) {
                        void *p = sk_boot_lookup(8, "roottask");/* FUN_0004dfd0 */
                        *(sk_word_t *)((char *)p + 8) |= 0x17;
                    } else sk_boot_bad();                       /* FUN_00116d60 */
                } else {
                    sk_boot_attached(*(long *)((char *)bd + 0xc0),
                                     *(void **)((char *)bd + 0xc8)); /* FUN_000549c0 */
                }
                sk_cap_done(*(void **)(bd + 0x10));         /* FUN_00052c54 */
                sk_word_t flags = *(sk_word_t *)((char *)bd + 0x68);
                t[0] = 0;
                *(sk_word_t *)(bt - 0x1f8) = 0;
                *(sk_word_t *)(bt - 0x1f0) = flags | 2;
                /* init descriptor magic 'init' */
                unsigned char init[0x48];
                sk_zero32(init, 0x48);
                *(unsigned int*)init = 0x696e6974;
                *(unsigned int*)(init+4) = 0;
                *(unsigned int*)(init+8) = 0;
                cpu = (void*)__builtin_thread_pointer();
                void *pcpu = *(void **)((char *)cpu + 8);
                void *h = sk_irq_handler(3, 0);            /* FUN_00062a48 */
                *(void **)((char *)pcpu + 0x28) = h;
                *(void **)((char *)pcpu + 0xa8) = t;
                sk_boot_early2(0x64dcc8);                   /* FUN_0005ba5c */
                sk_obj_reg(init, h);                        /* FUN_0006166c */
                sk_word_t local_168 = 0;
                void *tc = sk_tcb_current();                /* FUN_0005bb68 */
                *(void **)((char *)tc + 0x40) = (void *)local_168;
                void **links = *(void ***)((char *)bd + 0xd0);
                if (links != NULL) sk_link_boot(links[1], links[0]);  /* FUN_0005be48 */
                sk_obj_link((sk_word_t)local_168);          /* FUN_000359ac */
                sk_boot_x(*(void **)((char *)bd + 0x58));   /* FUN_00065620 */
                sk_boot_y(*(void **)((char *)bd + 0x60));   /* FUN_000656d8 */
                sk_boot_z();                                /* FUN_0005ac2c -> DAT_006ad6f8 */
            } else {
                sk_word_t c0 = *(sk_word_t *)(bs + 0x40);
                sk_word_t c1 = *(sk_word_t *)(bs + 0x30);
                if (c0 != 0 && c1 != 0) {
                    if (c1 + c0 < c1) sk_breakpoint(0x5519,0x608dc);
                    if (sk_boot_copy(c1, 0) != *(sk_word_t *)(bs + 0x40))
                        sk_boot_fail();
                    if (c0 < *(sk_word_t *)(bs + 0x40)) sk_breakpoint(0x5519,0x608dc);
                    sk_zero32((void*)c1, c0);
                    sk_boot_done_copy();
                    sk_boot_print();
                    sk_cap_init(*(void **)(bd + 0x10));
                } else {
                    sk_boot_none();                         /* FUN_004b7138 */
                }
            }
        }
    }

    /* common dispatch: walk the handler table for the boot type */
    {
        void **tbl = (void **)sk_handler_table(0x6b26d8, 1, 2);  /* FUN_0005acac */
        sk_word_t idx = bt & 0xff;
        if (idx < 2) return;
        if (idx - 2 < 0x3f) {
            if (idx == 3) return;
        } else if (idx - 0x50 <= 1) {
            sk_boot_exception(arg0, boot_type);             /* FUN_000604f8 */
            return;
        } else {
            sk_panic_assert("Security assertion failed: %s:%s:%d"); /* FUN_001150e0 */
        }
    }
fail_taken:
    sk_boot_taken();                                        /* FUN_004b70f8/004b710c/004b710c */
    return;
}

/*--------------------------------------------------------------------*/

/* FUN_00060f60 @ 0x60f60   (est. sk_ipc_msg_dispatch)
 * Ghidra: undefined8 FUN_00060f60(long,undefined8*,undefined8,undefined8,undefined8,undefined8)
 * Message-register dispatch wrapper: seeds the working message word from the caller's buffer (or from the current thread context), then invokes the message-copy/transfer routine 0x610b8 over the per-thread message area, publishing the result word back when the transfer consumed it.
 * Confidence: medium
 * Notes: FUN_00061e20 (load current message word); SoftwareBreakpoint(0x5519,0x61044) on bad range.
 */
sk_word_t sk_ipc_msg_dispatch(void *tcb, sk_word_t *word, void *a, sk_word_t b,
                                sk_word_t flags, unsigned char c)
{
    sk_word_t w; unsigned char consumed = 0;
    if ((int)flags == 0) {
        if (word != NULL) { w = *word; consumed = 1; }
        else w = sk_ipc_load_word(tcb);          /* FUN_00061e20 */
    } else {
        void *cpu = sk_per_cpu_base();
        if (word != NULL) return 0;
        if (tcb != *(void **)((char *)cpu + 8)) return 0;
        w = sk_ipc_load_word(tcb);               /* FUN_00061e20 */
    }
    sk_word_t r;
    if ((sk_word_t)((char*)tcb + 0x118) <= (sk_word_t)((char*)tcb + 0x168)) {
        r = sk_ipc_transfer((void *)((char*)tcb + 0x118), &w, a, b, flags, c, NULL, &consumed);
        if ((consumed & 1) && word) *word = w;
        return r;
    }
    sk_breakpoint(0x5519, 0x61044);
}

/*--------------------------------------------------------------------*/

/* FUN_00061044 @ 0x61044   (est. sk_ipc_msg_dispatch_fwd)
 * Ghidra: void FUN_00061044(void)
 * Forwarder to 0x60f60 (message-register dispatch).
 * Confidence: medium
 */
void sk_ipc_msg_dispatch_fwd(void){ sk_ipc_msg_dispatch(0,0,0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006104c @ 0x6104c   (est. sk_ipc_msg_dispatch2)
 * Ghidra: undefined8 FUN_0006104c(undefined8,undefined8*,undefined8,undefined8,ulong,undefined8)
 * Variant message dispatch: copies the caller's message word, runs the transfer routine with an out word, and commits the result only when the transfer flagged completion.
 * Confidence: medium
 * Notes: FUN_000610b8 transfer.
 */
sk_word_t sk_ipc_msg_dispatch2(void *tcb, sk_word_t *word, void *a, sk_word_t b,
                                 sk_word_t flags, unsigned char c)
{
    sk_word_t w = *word; unsigned char consumed = 0; sk_word_t out = 0;
    if ((flags & 1) == 0) {
        sk_word_t r = sk_ipc_transfer(tcb, &w, a, b, 0, 1, &out, &consumed);
        if (consumed == 1) *word = w;
        return r;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_000610b8 @ 0x610b8   (est. sk_ipc_transfer)
 * Ghidra: ulong FUN_000610b8(long,long*,ulong*,ulong,undefined8,undefined1,long*,undefined1*)
 * Core IPC message-register transfer: copies the source message words (bounded by the message-area limits at param_1+0x18/0x20/0x28 and enabled flag +0x30) into the destination word array via the message-copy helper, tracking a return-address/word-count. When the copy consumed a word it updates the caller's word and completion flag.
 * Confidence: low
 * Notes: FUN_0011546c/001156c4/001155e0 copy helpers; SoftwareBreakpoint(0x5519,0x612d8) on overflow.
 */
sk_word_t sk_ipc_transfer(void *mr, sk_word_t *word, sk_word_t *dst, sk_word_t lim,
                            sk_word_t mode, unsigned char k, sk_word_t *extra, unsigned char *consumed)
{
    sk_word_t w = *word;
    sk_word_t xr = extra ? *extra : 0;
    sk_word_t src = w - *(long *)((char*)mr + 0x18);
    sk_word_t avail = *(long *)((char*)mr + 0x28) - *(long *)((char*)mr + 0x18);
    if (*(sk_word_t*)((char*)mr + 0x20) <= avail) avail = *(sk_word_t*)((char*)mr + 0x20);
    sk_word_t local_b0 = xr + *(long *)((char*)mr + 0x18);
    sk_word_t local_98 = 0, local_90 = 0;
    sk_word_t pre = 0, pre_hi = 0;
    if (extra == NULL && *(sk_word_t*)((char*)mr+0x20) <= src && *(int*)((char*)mr+0x30) != 0 && xr == 0) {
        pre = *(sk_word_t*)((char*)mr + 0x38);
        pre_hi = (sk_word_t)*(unsigned int*)((char*)mr + 0x34);
    } else {
        if (*(sk_word_t*)((char*)mr+0x20) <= src && *(int*)((char*)mr+0x30) != 0) {
            src = *(long *)((char*)mr + 0x40);
            pre = *(sk_word_t*)((char*)mr + 0x48);
        }
    }
    sk_word_t plim = lim;
    sk_word_t local_70 = 0;
    sk_word_t n = sk_msg_copy(src, mode, 0, xr, &local_b0, sk_ipc_cb);
    if (n <= lim) lim = n;
    if (dst != NULL) {
        sk_word_t *pd = dst;
        if (pre != 0) {
            if (xr == 0) {
                sk_word_t u7 = pre;
                void *o = sk_cap_resolve(&u7, 0);         /* FUN_0005bc48 */
                pre = o ? (sk_word_t)*(unsigned short *)((char*)o + 0x40) << 0x30
                        : 0xffff000000000000ULL;
                pre = (u7 & 0xffffffffffffULL) | pre;
            }
            pd = dst + 1;
            if ((sk_word_t)pd < (sk_word_t)dst || dst + lim < pd)
                sk_breakpoint(0x5519, 0x612d8);
            sk_word_t n8 = lim * 8;
            *dst = pre;
            lim -= 1;
            if (((n8 - 8) >> 3) < lim) sk_breakpoint(0x5519, 0x612d8);
        }
        if ((int)mode == 0)
            sk_msg_copy2(src, pd, lim, xr, sk_ipc_cb2, &local_70);   /* FUN_001156c4 */
        else
            sk_msg_copy3(src, pd, lim, 0);                            /* FUN_001155e0 */
    }
    if (local_98 == 1) { *word = local_90; *consumed = 1; }
    return n;
}

/*--------------------------------------------------------------------*/

/* FUN_000612d8 @ 0x612d8   (est. sk_obj_slot_set)
 * Ghidra: void FUN_000612d8(long,undefined8)
 * Stores the given value into the object field at offset 0xa0.
 * Confidence: medium
 */
void sk_obj_slot_set(void *obj, sk_word_t v){ *(sk_word_t *)((char*)obj + 0xa0) = v; }

/*--------------------------------------------------------------------*/

/* FUN_000612e0 @ 0x612e0   (est. sk_stack_alloc)
 * Ghidra: long FUN_000612e0(long,long)
 * Allocates a stack region below the boot-stack base: computes an aligned address from the requested size+offset, minus 0x178 (frame header), raising a breakpoint on wraparound.
 * Confidence: medium
 * Notes: FUN_00063ffc; SoftwareBreakpoint(0x5519,0x6131c).
 */
sk_word_t sk_stack_alloc(sk_word_t size, sk_word_t off)
{
    sk_word_t base = sk_stack_base();                    /* FUN_00063ffc */
    sk_word_t a = ((size + off & ~7ULL) - base) - 0x300 & ~0xfULL;
    if (a + base < a) sk_breakpoint(0x5519, 0x6131c);
    return a - 0x178;
}

/*--------------------------------------------------------------------*/

/* FUN_0006132c @ 0x6132c   (est. sk_obj_field_140)
 * Ghidra: undefined8 FUN_0006132c(long)
 * Returns the 64-bit object field at offset 0x140.
 * Confidence: medium
 */
sk_word_t sk_obj_field_140(void *obj){ return *(sk_word_t *)((char*)obj + 0x140); }

/*--------------------------------------------------------------------*/

/* FUN_00061334 @ 0x61334   (est. sk_stack_alloc_type)
 * Ghidra: ulong FUN_00061334(ulong,byte)
 * Type-parameterized stack allocation: validates the allocation kind (breakpoint on kind 0), then computes the stack address according to the kind (16K-aligned for kind 3, word-aligned otherwise), returning the aligned base.
 * Confidence: medium
 * Notes: FUN_00063ffc; SoftwareBreakpoint(1,0x613ec)/0x5519.
 */
sk_word_t sk_stack_alloc_type(sk_word_t size, unsigned char kind)
{
    sk_word_t base;
    if (kind == 0) sk_breakpoint(1, 0x613ec);
    if ((void*)__builtin_thread_pointer() == NULL) {
        if (kind == 3) {
            base = sk_stack_base();                    /* FUN_00063ffc */
            sk_word_t a = ((size + 0x3fff & ~0x3fffULL) - base) - 0x300 & ~0xfULL;
            if (a + base < a) sk_breakpoint(0x5519, 0x613d4);
            return (a - 0x200) & ~0xfULL;
        }
    } else if ((kind - 0x50) > 1 && kind != 2) {
        return size;
    }
    base = sk_stack_base();
    sk_word_t a = ((size & ~7ULL) - base) - 0x300 & ~0xfULL;
    if (a + base < a) sk_breakpoint(0x5519, 0x613d4);
    return (a - 0x178) & ~0xfULL;
}

/*--------------------------------------------------------------------*/

/* FUN_000613ec @ 0x613ec   (est. sk_stack_alloc_hi)
 * Ghidra: ulong FUN_000613ec(long,long)
 * High stack allocation: lazily seeds the stack cursor from a base, then computes a stack address from the cursor plus the requested offset and size, minus 0x478 (two frame headers), breaking on wraparound.
 * Confidence: medium
 * Notes: DAT_006b2710; FUN_00063ffc; SoftwareBreakpoint(0x5519,0x6146c).
 */
sk_word_t sk_stack_alloc_hi(sk_word_t off, sk_word_t size)
{
    sk_word_t cur = sk_stack_cursor;                 /* DAT_006b2710 */
    sk_word_t base = sk_stack_base();                /* FUN_00063ffc */
    if (cur == 0) {
        sk_word_t a = (0x1fd00 - base) & ~0xfULL;
        if (a + base < a) sk_breakpoint(0x5519, 0x6146c);
        cur = 0x20178 - a;
        sk_stack_cursor = cur;
    }
    sk_word_t a = (cur + off & ~7ULL) - base & ~0xfULL;
    sk_word_t lo = a - 0x300;
    if (lo <= lo + base)
        return (a - size) - 0x478 & ~0xfULL;
    sk_breakpoint(0x5519, 0x6146c);
}

/*--------------------------------------------------------------------*/

/* FUN_00061488 @ 0x61488   (est. sk_stack_alloc_off)
 * Ghidra: long FUN_00061488(long)
 * Boot-stack allocation: seeds the global stack cursor from the boot base, then returns cursor + offset - 0x200.
 * Confidence: medium
 * Notes: DAT_006b2710; FUN_00063ffc.
 */
sk_word_t sk_stack_alloc_off(sk_word_t off)
{
    sk_word_t base = sk_stack_base();            /* FUN_00063ffc */
    if (sk_stack_cursor == 0) {
        sk_word_t a = (0x1fd00 - base) & ~0xfULL;
        if (a + base < a) sk_breakpoint(0x5519, 0x614d4);
        sk_stack_cursor = 0x20178 - a;
    }
    return off + sk_stack_cursor - 0x200;
}

/*--------------------------------------------------------------------*/

/* FUN_000614f8 @ 0x614f8   (est. sk_stack_alloc_low)
 * Ghidra: long FUN_000614f8(long)
 * Boot-stack allocation variant returning (cursor + off & ~7) - 0x300.
 * Confidence: medium
 * Notes: DAT_006b2710; FUN_00063ffc.
 */
sk_word_t sk_stack_alloc_low(sk_word_t off)
{
    sk_word_t base = sk_stack_base();            /* FUN_00063ffc */
    if (sk_stack_cursor == 0) {
        sk_word_t a = (0x1fd00 - base) & ~0xfULL;
        if (a + base < a) sk_breakpoint(0x5519, 0x61544);
        sk_stack_cursor = 0x20178 - a;
    }
    return (sk_stack_cursor + off & ~7ULL) - 0x300;
}

/*--------------------------------------------------------------------*/

/* FUN_0006156c @ 0x6156c   (est. sk_stack_alloc_mid)
 * Ghidra: ulong FUN_0006156c(long)
 * Boot-stack allocation variant returning ((cursor + off & ~7) - base & ~0xf) - 0x300.
 * Confidence: medium
 * Notes: DAT_006b2710; FUN_00063ffc.
 */
sk_word_t sk_stack_alloc_mid(sk_word_t off)
{
    sk_word_t cur = sk_stack_cursor;             /* DAT_006b2710 */
    sk_word_t base = sk_stack_base();            /* FUN_00063ffc */
    if (cur == 0) {
        sk_word_t a = (0x1fd00 - base) & ~0xfULL;
        if (a + base < a) sk_breakpoint(0x5519, 0x615e8);
        cur = 0x20178 - a;
        sk_stack_cursor = cur;
    }
    sk_word_t u = ((cur + off & ~7ULL) - base & ~0xfULL) - 0x300;
    if (u <= u + base) return u;
    sk_breakpoint(0x5519, 0x615e8);
}

/*--------------------------------------------------------------------*/

/* FUN_000615fc @ 0x615fc   (est. sk_region_bounds_get)
 * Ghidra: void FUN_000615fc(long,long*,long*)
 * Reads an object's memory-region base (offset 0x130) and size (0x140 - 0x130) into the two out parameters.
 * Confidence: medium
 */
void sk_region_bounds_get(void *obj, sk_word_t *base, sk_word_t *size)
{
    *base = *(sk_word_t *)((char*)obj + 0x130);
    *size = *(sk_word_t *)((char*)obj + 0x140) - *base;
}

/*--------------------------------------------------------------------*/

/* FUN_00061614 @ 0x61614   (est. sk_region_layout_set)
 * Ghidra: void FUN_00061614(long,undefined8,undefined8,long,long)
 * Configures an object's memory-region layout: records the base/limit pair (+0x30/+0x38), the region bounds (+0x130/+0x138/+0x140) and the stack/high-water pointers (+0x168/+0x170).
 * Confidence: medium
 */
void sk_region_layout_set(void *obj, sk_word_t a, sk_word_t b, sk_word_t base, sk_word_t hi)
{
    *(sk_word_t *)((char*)obj + 0x30) = a;
    *(sk_word_t *)((char*)obj + 0x38) = b;
    *(sk_word_t *)((char*)obj + 0x138) = hi;
    *(sk_word_t *)((char*)obj + 0x140) = hi + base;
    *(sk_word_t *)((char*)obj + 0x130) = base;
    *(sk_word_t *)((char*)obj + 0x168) = base + 0x4000;
    *(sk_word_t *)((char*)obj + 0x170) = hi + base;
}

/*--------------------------------------------------------------------*/

/* FUN_00061630 @ 0x61630   (est. sk_obj_field_28)
 * Ghidra: undefined8 FUN_00061630(long)
 * Returns the object field at offset 0x28.
 * Confidence: medium
 */
sk_word_t sk_obj_field_28(void *obj){ return *(sk_word_t *)((char*)obj + 0x28); }

/*--------------------------------------------------------------------*/

/* FUN_00061638 @ 0x61638   (est. sk_exc_state_read_wrap)
 * Ghidra: undefined8 FUN_00061638(long)
 * Reads the current exception/syscall register state for the object's context (field +0x28) into a 16-byte result word pair.
 * Confidence: low
 * Notes: FUN_0006166c.
 */
sk_word_t sk_exc_state_read_wrap(void *obj)
{
    sk_word_t out[2];
    sk_exc_state_read((sk_word_t*)out, *(sk_word_t *)((char*)obj + 0x28));
    return out[0];
}

/*--------------------------------------------------------------------*/

/* FUN_00061664 @ 0x61664   (est. sk_exc_state_read_discard)
 * Ghidra: void FUN_00061664(long)
 * Reads (and discards) the current exception/syscall register state for the object context at field +0x28.
 * Confidence: low
 * Notes: FUN_0006166c.
 */
void sk_exc_state_read_discard(void *obj)
{
    sk_exc_state_read((sk_word_t*)0, *(sk_word_t *)((char*)obj + 0x28));
}

/*--------------------------------------------------------------------*/

/* FUN_0006166c @ 0x6166c   (est. sk_exc_state_read)
 * Ghidra: void FUN_0006166c(undefined8*,long)
 * Captures the current exception/syscall frame: zeroes the 7-word output, performs CallSupervisor(0) to fetch the exception registers from the RO thread pointer, then unpacks 6 message words into the output and classifies the frame kind (0..4) from the first word, marking the kind and a 'valid' flag.
 * Confidence: low
 * Notes: CallSupervisor(0); reads tpidrro_el0 frame; classifies uVar15 into 0..4.
 */
void sk_exc_state_read(sk_word_t *out, sk_word_t ctx)
{
    int i; sk_word_t kind;
    for (i=0;i<7;i++) out[i]=0;
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    sk_word_t w0 = (sk_word_t)tp[0] | (sk_word_t)tp[1]<<8 | (sk_word_t)tp[2]<<16 | (sk_word_t)tp[3]<<24
                 | (sk_word_t)tp[4]<<32 | (sk_word_t)tp[5]<<40 | (sk_word_t)tp[6]<<48 | (sk_word_t)tp[7]<<56;
    CallSupervisor(0);
    if (ctx != 0) { out[0]=0; return; }
    /* unpack six 64-bit frame words from tp[0x40..0x60] */
    sk_word_t f1=0,f2=0,f3=0,f4=0,f5=0;
    const unsigned char *p = tp + 0x40;
    f1 = (sk_word_t)p[0] | (sk_word_t)p[1]<<8 | (sk_word_t)p[2]<<16 | (sk_word_t)p[3]<<24
       | (sk_word_t)p[4]<<32 | (sk_word_t)p[5]<<40 | (sk_word_t)p[6]<<48 | (sk_word_t)p[7]<<56;
    f2 = (sk_word_t)p[8] | (sk_word_t)p[9]<<8 | (sk_word_t)p[10]<<16 | (sk_word_t)p[11]<<24
       | (sk_word_t)p[12]<<32 | (sk_word_t)p[13]<<40 | (sk_word_t)p[14]<<48 | (sk_word_t)p[15]<<56;
    f3 = (sk_word_t)p[16]| (sk_word_t)p[17]<<8 | (sk_word_t)p[18]<<16 | (sk_word_t)p[19]<<24
       | (sk_word_t)p[20]<<32 | (sk_word_t)p[21]<<40 | (sk_word_t)p[22]<<48 | (sk_word_t)p[23]<<56;
    f4 = (sk_word_t)p[24]| (sk_word_t)p[25]<<8 | (sk_word_t)p[26]<<16 | (sk_word_t)p[27]<<24
       | (sk_word_t)p[28]<<32 | (sk_word_t)p[29]<<40 | (sk_word_t)p[30]<<48 | (sk_word_t)p[31]<<56;
    f5 = (sk_word_t)p[32]| (sk_word_t)p[33]<<8 | (sk_word_t)p[34]<<16 | (sk_word_t)p[35]<<24
       | (sk_word_t)p[36]<<32 | (sk_word_t)p[37]<<40 | (sk_word_t)p[38]<<48 | (sk_word_t)p[39]<<56;
    out[1]=f1; out[6]=f2; out[3]=f3; out[4]=f4;
    if (w0 < 2) { out[0] = w0==0?0:1; }
    else if (w0 == 2) out[0]=2;
    else if (w0 == 3) out[0]=4;
    else if (w0 == 4) { out[0]=3; ((unsigned char*)out)[2]=1; }
    else return;
    ((unsigned char*)out)[5]=1;
}

/*--------------------------------------------------------------------*/

/* FUN_000618c4 @ 0x618c4   (est. sk_obj_id_set)
 * Ghidra: void FUN_000618c4(long,undefined4)
 * Stores the 32-bit identifier into the object field at offset 0x118.
 * Confidence: medium
 */
void sk_obj_id_set(void *obj, unsigned int id){ *(unsigned int *)((char*)obj + 0x118) = id; }

/*--------------------------------------------------------------------*/

/* FUN_000618cc @ 0x618cc   (est. sk_log_obj_fields)
 * Ghidra: void FUN_000618cc(long,undefined8)
 * Logs a five-field diagnostic record for the object: resolves the per-cpu id, the capability at +0xa8, the object link at +8, and the id at +0x118, then prints them with the format string.
 * Confidence: low
 * Notes: FUN_0005b8c8/00063970/0019afbc/0005e958; format s__s__s__s__s_005bd414.
 */
void sk_log_obj_fields(void *obj, sk_word_t tag)
{
    sk_word_t a = sk_log_cpu();                 /* FUN_0005b8c8 */
    sk_word_t b = sk_cap_of(*(sk_word_t *)((char*)obj + 0xa8));   /* FUN_00063970 */
    sk_word_t c = sk_link_of(*(sk_word_t *)((char*)obj + 8));     /* FUN_0019afbc */
    unsigned int d = *(unsigned int *)((char*)obj + 0x118);
    sk_log1(a); sk_log1(b); sk_log1(c); sk_log1(d);
    sk_logf(tag, ~0ULL, 0x14, "%s%s%s%s%s");   /* FUN_0005b824 */
}

/*--------------------------------------------------------------------*/

/* FUN_0006198c @ 0x6198c   (est. sk_obj_field_120)
 * Ghidra: undefined8 FUN_0006198c(long)
 * Returns the object field at offset 0x120.
 * Confidence: medium
 */
sk_word_t sk_obj_field_120(void *obj){ return *(sk_word_t *)((char*)obj + 0x120); }

/*--------------------------------------------------------------------*/

/* FUN_00061994 @ 0x61994   (est. sk_obj_link_set)
 * Ghidra: void FUN_00061994(long,long)
 * Sets the object link pointer: releases the previous link (when present) via the link-release helper, then stores the new link and clears the auxiliary field.
 * Confidence: medium
 * Notes: FUN_0005bce0.
 */
void sk_obj_link_set(void *obj, void *link)
{
    if (link) sk_link_release(link);          /* FUN_0005bce0 */
    *(void **)((char*)obj + 8) = link;
    *(sk_word_t *)((char*)obj + 0x10) = 0;
}

/*--------------------------------------------------------------------*/

/* FUN_000619c8 @ 0x619c8   (est. sk_exc_state_read_cpu)
 * Ghidra: void FUN_000619c8(undefined8*,long)
 * Zeroes the 7-word output, then if the given context belongs to a CPU other than the current one, reads that CPU's exception state via the context field +0x28.
 * Confidence: medium
 * Notes: FUN_000619f0.
 */
void sk_exc_state_read_cpu(sk_word_t *out, void *ctx)
{
    int i; for(i=0;i<5;i++) out[i]=0;
    void *cpu = sk_per_cpu_base();
    if (ctx != *(void **)((char*)cpu + 8))
        sk_exc_state_read2(out, *(sk_word_t *)((char*)ctx + 0x28));   /* FUN_000619f0 */
}

/*--------------------------------------------------------------------*/

/* FUN_000619f0 @ 0x619f0   (est. sk_exc_state_read2)
 * Ghidra: void FUN_000619f0(ulong*,ulong)
 * Second-stage exception-state reader: primes the RO thread pointer with a saved frame (DAT_004be310), runs CallSupervisor(0), and when the operation selector (param_2 low byte) is 0 unpacks four 64-bit message words from the frame into the output array; otherwise it fails through a no-return diagnostic.
 * Confidence: low
 * Notes: DAT_004be310/uRam00000000004be318; CallSupervisor(0); FUN_004b71a8/FUN_0011d7e8.
 */
void sk_exc_state_read2(sk_word_t *out, sk_word_t sel)
{
    sk_word_t hi = sk_exc_seed_hi;             /* uRam00000000004be318 */
    sk_word_t lo = sk_exc_seed_lo;             /* _DAT_004be310 */
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    /* write lo/hi into the 16-byte RO frame header */
    tp[0]=(unsigned char)lo; tp[1]=(unsigned char)(lo>>8); tp[2]=(unsigned char)(lo>>16); tp[3]=(unsigned char)(lo>>24);
    tp[4]=(unsigned char)(lo>>32); tp[5]=(unsigned char)(lo>>40); tp[6]=(unsigned char)(lo>>48); tp[7]=(unsigned char)(lo>>56);
    tp[8]=(unsigned char)hi; tp[9]=(unsigned char)(hi>>8); tp[10]=(unsigned char)(hi>>16); tp[11]=(unsigned char)(hi>>24);
    tp[12]=(unsigned char)(hi>>32); tp[13]=(unsigned char)(hi>>40); tp[14]=(unsigned char)(hi>>48); tp[15]=(unsigned char)(hi>>56);
    CallSupervisor(0);
    for (int i=0;i<8;i++) tp[i]=0;   /* clear low half */
    if ((sel & 0xff) == 0) {
        const unsigned char *p = tp + 0x40;
        out[1] = rd64(p+8);  out[0] = rd64(p);
        out[2] = rd64(p+0x18); out[3] = rd64(p+0x10);
        out[4] = rd64(p+0x30);
        return;
    }
    sk_exc_fail(sel);   /* FUN_004b71a8 + FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/

/* FUN_00061cdc @ 0x61cdc   (est. sk_error_code_str_out)
 * Ghidra: void FUN_00061cdc(undefined8,byte)
 * Copies the canonical L4_ErrorCode* string for the given error code (0-9) into the caller's buffer; codes above 9 use a generic 'L4_ErrorCode: %zu' fallback.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004be320..; DAT_004be460.
 */
void sk_error_code_str_out(char *out, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) { sk_memcpy(out, "unknown", 0x20); sk_logf((sk_word_t)(uintptr_t)out,0x20,0x1f,"L4_ErrorCode: %zu"); return; }
    sk_memcpy(out, names[code], 0x20);
}

/*--------------------------------------------------------------------*/

/* FUN_00061e20 @ 0x61e20   (est. sk_ipc_load_word)
 * Ghidra: undefined8 FUN_00061e20(long)
 * Loads the current IPC/message word for the given thread: for the current CPU it returns the caller's frame word; for another CPU it reads the thread's saved exception state (context field +0x28).
 * Confidence: medium
 * Notes: FUN_000619f0 (cross-CPU state read).
 */
sk_word_t sk_ipc_load_word(void *tcb)
{
    void *cpu = sk_per_cpu_base();
    sk_word_t w = 0;
    if (tcb == *(void **)((char*)cpu + 8))
        return w;                 /* current CPU: frame word */
    if (tcb != *(void **)((char*)cpu + 8))
        sk_exc_state_read2((sk_word_t*)0, *(sk_word_t *)((char*)tcb + 0x28));
    return w;
}

/*--------------------------------------------------------------------*/

/* FUN_00061e8c @ 0x61e8c   (est. sk_backtrace_dump)
 * Ghidra: void FUN_00061e8c(undefined8,long)
 * Dumps the IPC/message-register contents of a thread as a formatted backtrace: for a foreign thread it reads and resolves the capability words (0x5bc48), then iterates the message registers in 16-word batches printing each resolved capability with its address, erroring through a no-return check on stack corruption.
 * Confidence: low
 * Notes: Strings '  %s: %3zu  ...' (s__s___03zu________0x_012zx_005bd69d) and '  %s: %3zu  0x%02hhx %02hhx %02hhx %02hhx %02hhx' (s__s___03zu____02hhX_02hhX_02hhX_0_005bd609); FUN_0005bc48/00054c9c/001185ec; stack canary 0xd37afd4bb400012a check via FUN_0011d7e8.
 */
void sk_backtrace_dump(char *out, void *tcb)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t w[16] = {0};
    void *cpu = sk_per_cpu_base();
    int idx = 0;
    if (tcb != *(void **)((char*)cpu + 8)) {
        sk_word_t r[6] = {0};
        sk_exc_state_read2(r, *(sk_word_t *)((char*)tcb + 0x28));
        w[0] = r[0];  /* first capability word */
        void *o = sk_cap_resolve(&w[0], 0);
        w[0] = (w[0] & 0xffffffffffffULL)
             | (o ? (sk_word_t)*(unsigned short*)((char*)o + 0x40) << 0x30 : 0xffff000000000000ULL);
        w[1] = r[2];
        o = sk_cap_resolve(&w[1], 0);
        w[1] = (w[1] & 0xffffffffffffULL)
             | (o ? (sk_word_t)*(unsigned short*)((char*)o + 0x40) << 0x30 : 0xffff000000000000ULL);
        idx = 2;
    }
    sk_word_t r[1];
    r[0] = sk_ipc_load_word(tcb);
    sk_word_t n = sk_ipc_msg_dispatch(tcb, r, &w[idx], 0x10 - idx, 0, 0);
    sk_word_t total = n + idx;
    while (total != 0) {
        sk_word_t cnt = total > 0x10 ? 0x10 : total;
        for (int i = 0; i < cnt; i++) {
            sk_word_t v = w[i];
            sk_word_t tmp = v;
            void *o = sk_cap_resolve(&tmp, 1);
            sk_word_t val = v - 4;
            if (i == 0 && tcb != *(void **)((char*)cpu + 8)) val = v;
            if (o == NULL) {
                sk_fmt(out, "  %s: %3zu  [cap 0x%012zx]");     /* s__s___03zu... */
            } else {
                sk_word_t u = 0;
                sk_cap_addr(val, &u);                            /* FUN_00054c9c */
                sk_fmt(out, "  %s: %3zu  0x%02hhx %02hhx %02hhx %02hhx %02hhx");
            }
        }
        if (total < 0x11) break;
        n = sk_ipc_msg_dispatch(tcb, r, w, 0x10, 0, 0);
        total = n;
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();   /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/

/* FUN_000621a8 @ 0x621a8   (est. sk_regs_capture)
 * Ghidra: bool FUN_000621a8(long,long)
 * Captures the full 0x69-register file of a thread into the caller's buffer by repeatedly issuing CallSupervisor(0) with a register-index and a mask in the RO frame, then copying the returned words out. Stops early if the thread's context field (+0x28) becomes nonzero.
 * Confidence: low
 * Notes: CallSupervisor(0); registers captured 0x36/0x69 per pass; SoftwareBreakpoint(0x5519,0x62394).
 */
bool sk_regs_capture(void *tcb, sk_word_t *buf)
{
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    sk_word_t idx = 0;
    do {
        unsigned int r = (unsigned int)idx;
        sk_word_t ctx = *(sk_word_t *)((char*)tcb + 0x28);
        unsigned int nreg = 0x36;
        if (0x32 < (r & 0xffff)) nreg = 0x69 - r;
        sk_word_t mask = ~(-1L << (nreg & 0x3f));
        sk_word_t v = idx | (mask << 16);     /* frame: low=idx, high=mask */
        wr64(tp, v);
        CallSupervisor(0);
        if (ctx != 0) break;
        sk_word_t cnt = nreg & 0xffff;
        if (((idx & 0x1fff) * -8 + 0x348) >> 3 < cnt)
            sk_breakpoint(0x5519, 0x62394);
        sk_word_t *dst = &buf[(idx & 0x1fff)];
        const unsigned char *p = tp + 0x40;
        for (sk_word_t i = 0; i < cnt; i++, p += 8)
            dst[i] = rd64(p);
        idx += cnt;
    } while ((idx & 0xffff) < 0x69);
    return ctx == 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00062394 @ 0x62394   (est. sk_regs_dump)
 * Ghidra: void FUN_00062394(undefined8,undefined8)
 * Prints the register file of a thread: captures the 0x69 registers into a local buffer; on failure prints 'Cannot obtain registers for thread', otherwise prints each register and its value with a space between each 2-register group.
 * Confidence: low
 * Notes: Strings s_Cannot_obtain_registers_for_thre_005bd6b8, s___8s__0x_016zx_005bd6e4; FUN_000621a8/001185ec/0011883c.
 */
void sk_regs_dump(char *out, void *tcb)
{
    sk_word_t regs[105];     /* 0x69 registers */
    sk_zero32(regs, 0x200);
    if (!sk_regs_capture(tcb, regs)) {
        sk_fmt(out, "Cannot obtain registers for thread");
    } else {
        for (sk_word_t i = 0; i < 0x69; i++) {
            sk_fmt(out, "  %8s: 0x%016zx", sk_reg_name(i));
            if ((i & 1) == 0) sk_fmt(out, " "); else sk_fmt_newline(out);
        }
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00062474 @ 0x62474   (est. sk_crash_report)
 * Ghidra: void FUN_00062474(undefined8,undefined8,undefined8,long,int,int,ulong,ulong)
 * Full crash/panic report formatter: prints the address-space, component, Mach-O header/slide, build UUID, the faulting thread's identity, call stack, ESR/FAR, an apparent-stack-overflow warning, the full register file and a backtrace, delimited by rule lines.
 * Confidence: medium
 * Notes: Security-relevant: the kernel's crash-dump path; strings s_Address_Space_____s_005bd6f7, s_Component_____s_005bd70c, s_Mach_O_Header__0x_016lx_005bd71d, s_Mach_O_Slide__0x_016lx_005bd736, s_UUID___02hhX..., s_Thread___s_0x_06x___p___005bd7ba, s_Call_Stack__0x_012zx____0x_012zx_005bd7d3, s_ESR__0x_08zx_FAR__0x_016zx_005bd7f5, s_Apparent_stack_overflow_by_0x_04_005bd811, s_Synchronous_Tag_Check_Fault_005bd83b, s_Registers__005bd858, s_Backtrace__005bd865; stack canary FUN_0011d7e8.
 */
void sk_crash_report(char *out, int a2, long a3, void *thread, int show_bt,
                       int show_regs, sk_word_t esr, sk_word_t far)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_rule(out, a2, a3);                       /* FUN_0006275c */
    { sk_word_t as = 0; if (!sk_addrspace(&as)) as = 1; sk_fmt(out, "Address Space: %s"); } /* FUN_0005b860 */
    { sk_word_t co = 0; if (!sk_component(0,&co)) co = 1; sk_fmt(out, "Component: %s"); }   /* FUN_0005d154 */
    sk_fmt(out, "Mach-O Header: 0x%016lx", sk_macho_header());   /* FUN_00054ba8 */
    sk_fmt(out, "Mach-O Slide: 0x%016lx", sk_macho_slide());     /* FUN_00054bc8 */
    { sk_word_t u[2]={0,0}; sk_uuid(&u); sk_fmt(out, "UUID: %02hhX%02hhX..."); }  /* FUN_00054c3c */
    sk_rule(out, a2, 0);
    sk_log_obj_fields(thread, 0);               /* FUN_000618cc */
    sk_word_t base = *(sk_word_t *)((char*)thread + 0x130);
    sk_fmt(out, "Thread: %s 0x%06x %p");        /* s_Thread___s_0x_06x___p___005bd7ba */
    sk_fmt(out, "Call Stack: 0x%012zx - 0x%012zx");  /* s_Call_Stack__0x_012zx____0x_012zx_005bd7d3 */
    if (esr != 0) {
        sk_fmt(out, "ESR: 0x%08zx FAR: 0x%016zx");  /* s_ESR__0x_08zx_FAR__0x_016zx_005bd7f5 */
        if ((*(sk_word_t*)((char*)thread + 0x130) <= far) && (far < base + 0x4000))
            sk_fmt(out, "Apparent stack overflow by 0x%04zx");  /* s_Apparent_stack_overflow_by_0x_04_005bd811 */
        if ((esr & 0x3f) == 0x11)
            sk_banner("Synchronous Tag Check Fault", 0x1c, 1, out);  /* FUN_00118abc */
    }
    if (show_regs) {
        sk_banner("Registers:", 0xc, 1, out);   /* FUN_00118abc */
        sk_regs_dump(out, thread);              /* FUN_00062394 */
    }
    if (show_bt) {
        sk_banner("Backtrace:", 0xc, 1, out);   /* FUN_00118abc */
        sk_backtrace_dump(out, thread);         /* FUN_00061e8c */
    }
    sk_rule(out, a2, 0);
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006275c @ 0x6275c   (est. sk_rule)
 * Ghidra: void FUN_0006275c(undefined8,undefined8,long)
 * Prints a 0x48-char rule/divider line: when a fill char is given it prints the char twice on either side of a header string, otherwise it prints the raw fill character 0x48 times, ending with a newline.
 * Confidence: low
 * Notes: FUN_001187f4/001185ec/00115080.
 */
void sk_rule(char *out, int fill, long text)
{
    if (text == 0) {
        for (int i = 0x48; i; i--) sk_putch(fill, out);      /* FUN_001187f4 */
    } else {
        long len = sk_strlen((const char*)(uintptr_t)text);                            /* thunk_FUN_00115080 */
        sk_word_t pad = (0x46 - len) >> 1;
        sk_word_t n = pad;
        if (1 < 0x46 - len)
            do { sk_putch(fill, out); } while (--n != 0);
        sk_fmt(out, "%s", (const char*)(uintptr_t)text);                              /* &DAT_005bd9f8 */
        if (len + 2 + pad != 0x48) {
            long extra = len + pad - 0x46;
            do { sk_putch(fill, out); } while (extra++ != -1);
        }
    }
    sk_putch(10, out);
}

/*--------------------------------------------------------------------*/

/* FUN_00062848 @ 0x62848   (est. sk_flag_test_41)
 * Ghidra: bool FUN_00062848(long)
 * Tests whether the object's flag field (offset 0x48) has bits 0x40 or 0x01 set.
 * Confidence: medium
 */
bool sk_flag_test_41(void *obj){ return (*(unsigned char*)((char*)obj + 0x48) & 0x41) != 0; }

/*--------------------------------------------------------------------*/

/* FUN_0006285c @ 0x6285c   (est. sk_ref_acquire_flag)
 * Ghidra: undefined8 FUN_0006285c(long,undefined8)
 * Acquires a reference: if the flag bit 1 is clear and the reference counter (+0x90) is nonzero, it consults a validity helper and clears/sets bit 1 accordingly, then increments the counter. Always returns 1.
 * Confidence: medium
 * Notes: FUN_0011817c.
 */
sk_word_t sk_ref_acquire_flag(void *obj, void *arg)
{
    if (((*(unsigned char*)((char*)obj + 0x48) >> 1 & 1) == 0) && (*(long*)((char*)obj + 0x90) != 0)) {
        if (sk_ref_valid(arg) == 0)          /* FUN_0011817c */
            *(sk_word_t*)((char*)obj + 0x48) &= ~2ULL;
        else
            *(sk_word_t*)((char*)obj + 0x48) |= 2;
    }
    *(long*)((char*)obj + 0x90) += 1;
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_000628d8 @ 0x628d8   (est. sk_ref_acquire_flag2)
 * Ghidra: undefined8 FUN_000628d8(long,undefined8)
 * Acquire-reference variant: like 0x6285c but returns 0 when the validity helper cleared the flag, otherwise increments the counter and returns 1.
 * Confidence: medium
 * Notes: FUN_0011817c.
 */
sk_word_t sk_ref_acquire_flag2(void *obj, void *arg)
{
    if (((*(unsigned char*)((char*)obj + 0x48) >> 1 & 1) == 0) && (*(long*)((char*)obj + 0x90) != 0)) {
        if (sk_ref_valid(arg) == 0) {        /* FUN_0011817c */
            *(sk_word_t*)((char*)obj + 0x48) &= ~2ULL;
            return 0;
        }
        *(sk_word_t*)((char*)obj + 0x48) |= 2;
    }
    *(long*)((char*)obj + 0x90) += 1;
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_000628e0 @ 0x628e0   (est. sk_ref_release_flag)
 * Ghidra: void FUN_000628e0(long,undefined8)
 * Releases a reference: decrements the counter; when it reaches zero it clears flag bit 1 and, if bit 1 had been set, invokes the release-finalizer.
 * Confidence: medium
 * Notes: FUN_00118194.
 */
void sk_ref_release_flag(void *obj, void *arg)
{
    long c = *(long*)((char*)obj + 0x90) - 1;
    *(long*)((char*)obj + 0x90) = c;
    if (c == 0) {
        sk_word_t f = *(sk_word_t*)((char*)obj + 0x48);
        *(sk_word_t*)((char*)obj + 0x48) = f & ~2ULL;
        if (((unsigned int)f >> 1 & 1) != 0) sk_ref_finalize(arg);   /* FUN_00118194 */
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006290c @ 0x6290c   (est. sk_handler_set)
 * Ghidra: void FUN_0006290c(long,undefined8,undefined8)
 * Installs a two-word (handler, arg) entry at index param_1 into the boot handler table at DAT_006b26d8, asserting the index is in range.
 * Confidence: medium
 * Notes: DAT_006b26d8 via FUN_0005acac(0x6b26d8,1,2); SoftwareBreakpoint(0x5519,0x62974).
 */
void sk_handler_set(long idx, void *handler, void *arg)
{
    void **tbl = (void **)sk_handler_table(0x6b26d8, 1, 2);
    void **e = tbl + idx * 2;
    if ((tbl <= e && e + 2 <= tbl + 6) && e <= e + 2) {
        e[0] = handler;
        e[1] = arg;
        return;
    }
    sk_breakpoint(0x5519, 0x62974);
}

/*--------------------------------------------------------------------*/

/* FUN_000629fc @ 0x629fc   (est. sk_cap_resolve_word)
 * Ghidra: ulong FUN_000629fc(ulong)
 * Resolves a capability word: looks up the capability object and ORs the object's type tag (from offset 0x40) into the upper bits, returning a full capability word.
 * Confidence: medium
 * Notes: FUN_0005bc48.
 */
sk_word_t sk_cap_resolve_word(sk_word_t cap)
{
    sk_word_t w = cap;
    void *o = sk_cap_resolve(&w, 0);
    sk_word_t tag = o ? (sk_word_t)*(unsigned short*)((char*)o + 0x40) << 0x30 : 0xffff000000000000ULL;
    return (w & 0xffffffffffffULL) | tag;
}

/*--------------------------------------------------------------------*/

/* FUN_00062a48 @ 0x62a48   (est. sk_tightbeam_lookup)
 * Ghidra: void FUN_00062a48(int,undefined4)
 * Looks up a tightbeam resource in the boot data: selects a resource kind (0x11/0x13) and sub-index from the parameters, walks the boot descriptor list, and returns the resource's packed key; fails with 'No tightbeam placeholder resource' if none is found.
 * Confidence: low
 * Notes: String s_No_tighbeam_placeholder_resource_005bd8d5; boot-desc helpers FUN_0004fe80/0004ed48/0004eb44/0004ecf0/0004eb4c/0004e88c/0004e7b8/0004ed84/0004e774; SoftwareBreakpoint(0x5519,0x62bc8).
 */
void sk_tightbeam_lookup(int kind, unsigned int sub)
{
    if ((sk_boot_begin() & 1) == 0) { sk_boot_no_irq(); return; }   /* FUN_00053418 */
    int want = (kind < 0x50 && (kind == 1 || kind != 2)) ? 0x11 : 0x13;
    unsigned int sel = (want == 0x13) ? sub : 0;
    void *it = sk_boot_iter();                 /* FUN_0004eb44 */
    while ((sk_boot_more(it) & 1) == 0) {      /* FUN_0004ecf0 */
        void *e = sk_boot_ent(it);             /* FUN_0004eb4c */
        if (e && e + 0xc < (void*)e) sk_breakpoint(0x5519, 0x62bc8);
        if (sk_boot_code(e) == want) {         /* FUN_0004e88c */
            unsigned char *p = sk_boot_key(e, sel);  /* FUN_0004e7b8 */
            /* p now points at resource; kind-selected offset then packed key */
            sk_word_t k = sk_boot_pack_key_sel(p, kind, sel);   /* FUN_0004e774 */
            sk_boot_ret(k);                    /* FUN_0004ed84 */
            return;
        }
    }
    sk_panic_bad(0, "No tightbeam placeholder resource");   /* FUN_0005b190 */
}

/*--------------------------------------------------------------------*/

/* FUN_00062bdc @ 0x62bdc   (est. sk_error_str_fwd)
 * Ghidra: void FUN_00062bdc(void)
 * Forwarder to 0x61cdc (L4 error-code string copy).
 * Confidence: medium
 */
void sk_error_str_fwd(void){ sk_error_code_str_out(0, 0); }

/*--------------------------------------------------------------------*/

/* FUN_00062bfc @ 0x62bfc   (est. sk_key_set_deleted_panic)
 * Ghidra: void FUN_00062bfc(void)
 * Panics with 'setting key %lu which is deleted' (endpoint/notification key teardown invariant).
 * Confidence: high
 * Notes: String s_setting_key__lu_which_is_deleted_005ab3ef; no-return FUN_0005b190.
 */
void sk_key_set_deleted_panic(void) __attribute__((noreturn))
{
    sk_panic_bad(0, "setting key %lu which is deleted");
}

/*--------------------------------------------------------------------*/

/* FUN_00062c14 @ 0x62c14   (est. sk_key_set_destructor_panic)
 * Ghidra: void FUN_00062c14(void)
 * Panics with 'setting key %lu while destructor' (notification key set during teardown).
 * Confidence: high
 * Notes: String s_setting_key__lu_while_destructor_005ab3c5.
 */
void sk_key_set_destructor_panic(void) __attribute__((noreturn))
{
    sk_panic_bad(0, "setting key %lu while destructor");
}

/*--------------------------------------------------------------------*/

/* FUN_00062c2c @ 0x62c2c   (est. sk_ep_lock_setup)
 * Ghidra: void FUN_00062c2c(ulong*,ulong,long*)
 * Locks and sets up a new endpoint object: zeroes the endpoint, records the notification key, copies the configuration, then installs a dispatch target (the boot endpoint handler 0x62dcc or one resolved from the boot data) into the RO thread pointer and issues CallSupervisor(0). On success it clears the notification word and completes the endpoint setup; on an unexpected mode it fails through a diagnostic. Panics 'failed to lock new endpoints' if the endpoint could not be locked.
 * Confidence: medium
 * Notes: Strings s_failed_to_lock_new_endpoints_loc_005bdc06; endpoint dispatch 0x62dcc; FUN_0005cdbc/0005ce54/00063040; CallSupervisor(0); stack canary.
 */
void sk_ep_lock_setup(sk_word_t *ep, sk_word_t key, long *cfg)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_zero32(ep, 0x50);
    if (ep + 2 < ep) sk_breakpoint(0x5519, 0x62db0);
    if ((sk_ep_lock(ep) & 1) != 0) {          /* FUN_0005cdbc */
        ep[2] = key;
        sk_memcpy(ep + 4, cfg, 0x28);
        ep[3] = 0;
        void (*fp)(void*, void*);
        if (*cfg == 0) {
            void *bd = sk_boot_strings();     /* FUN_00054610 */
            fp = *(void (**)(void*,void*))(bd + 0xe0);
            key = ep[2];
        } else {
            fp = sk_ep_return_dispatch;       /* FUN_00062dcc */
        }
        /* install fp into RO thread pointer, CallSupervisor(0) */
        sk_ro_write8((sk_word_t)(uintptr_t)fp);
        CallSupervisor(0);
        if ((key & 0xfd) == 0) {
            sk_word_t w = ep[6];
            ep[6] = 0;
            sk_ep_create_threads(ep, w);      /* FUN_00063040 */
            if (canary == 0xd37afd4bb400012a) {
                sk_ep_setup_done(ep);         /* FUN_0005ce54 */
                return;
            }
        } else {
            sk_ep_bad_mode(key & ~1ULL);      /* FUN_004b73d0 */
        }
        sk_stack_fail();
    }
    sk_panic_bad(0, "failed to lock new endpoints");
}

/*--------------------------------------------------------------------*/

/* FUN_00062dcc @ 0x62dcc   (est. sk_ep_return_dispatch)
 * Ghidra: void FUN_00062dcc(undefined8,undefined8)
 * Endpoint exception-return dispatch: takes the current endpoint from the per-CPU state (+0xa8), invokes its method through the dispatch table at +0x20, publishes the result to the RO thread pointer via CallSupervisor(0), then consults the endpoint's return action; if the endpoint has no configured return it panics 'returned from EP return on endpoint'.
 * Confidence: medium
 * Notes: String s_returned_from_EP_return_on_endpo_005bde82; per-CPU +0xa8; method table +0x20; FUN_0006393c/000636e0/00063768; SoftwareBreakpoint(0x5519,0x62f08).
 */
void sk_ep_return_dispatch(void *arg1, void *arg2)
{
    void *cpu = sk_per_cpu_base();
    void *ep = *(void **)((char*)cpu + 0xa8);
    if ((sk_word_t)ep <= (sk_word_t)ep + 0x50) {
        sk_ep_drain(cpu);                     /* FUN_000636e0 */
        sk_word_t r = (*(sk_word_t(*)(void*,void*,void*))(*(void***)((char*)ep + 0x20)[2]))(
                         *(void**)((char*)ep + 0x28), arg1, arg2);
        sk_ep_restore(cpu);                      /* FUN_00063768 */
        sk_ro_write8(r);
        CallSupervisor(0);
        void *act = sk_ep_return(ep, 1);      /* FUN_0006393c */
        if (act && *(void**)((char*)act + 0x50) != NULL) {
            if ((sk_word_t)ep + 0x50 <= (sk_word_t)ep) sk_breakpoint(0x5519, 0x62f08);
            (*(void(*)(void*))(*(void***)((char*)act + 0x50)[0]))(ep);
        }
        sk_panic_bad(0, "returned from EP return on endpoint");
    }
    sk_breakpoint(0x5519, 0x62f08);
}

/*--------------------------------------------------------------------*/

/* FUN_00062f08 @ 0x62f08   (est. sk_error_str_out2)
 * Ghidra: void FUN_00062f08(undefined8,byte)
 * Copies the canonical L4_ErrorCode* string for the given code (0-9) into the caller's buffer; >9 uses a generic fallback.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004be480..; DAT_004be5c0.
 */
void sk_error_str_out2(char *out, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) { sk_memcpy(out, "unknown", 0x20); return; }
    sk_memcpy(out, names[code], 0x20);
}

/*--------------------------------------------------------------------*/

/* FUN_00063040 @ 0x63040   (est. sk_ep_create_threads)
 * Ghidra: void FUN_00063040(long,ulong)
 * Creates the initial thread set for an endpoint: pops threads off the free list, tears down their prior notification registers, and for each newly created thread (up to the requested count) assigns an endpoint id (decimal-formatted), links it to the endpoint, primes its register context, and issues CallSupervisor(0) to activate it. Fails with 'Failed to create thread for an E[ndpoint]' if thread creation fails.
 * Confidence: low
 * Notes: Strings s_Failed_to_create_thread_for_an_E_005bddbf; FUN_0005fbc0/004b6d60/004b7278/00061488/0005eec4/000618c4/0006132c/00034f70/004b23d8; CallSupervisor(0); SoftwareBreakpoint(0x5519,0x635a4).
 */
void sk_ep_create_threads(void *ep, sk_word_t want)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t cnt = *(sk_word_t *)((char*)ep + 0x30);
    while (want < cnt) {
        void *tcb = *(void **)((char*)ep + 0x18);
        *(void **)((char*)ep + 0x18) = *(void **)((char*)tcb + 0x50);
        *(sk_word_t *)((char*)ep + 0x30) = cnt - 1;
        *(void **)((char*)tcb + 0x50) = NULL;
        if ((sk_word_t)tcb + 0x178 < (sk_word_t)tcb) sk_breakpoint(0x5519, 0x635a4);
        sk_ep_teardown(tcb);                   /* FUN_004b7278 */
        void *stk = (void *)sk_stack_alloc_off((sk_word_t)tcb);
        /* clear notification slots [0x1c0..) and [0x1e0..) */
        if (*(long *)((char*)ep + 0x38) != 0) {
            for (sk_word_t i = 0; i < *(sk_word_t *)((char*)ep + 0x38); i++) {
                sk_obj_link((sk_word_t)*(void**)((char*)tcb + 0xc0 + i*8));   /* FUN_004b23d8 */
                unsigned char *p = (unsigned char*)((char*)stk + 0x1c0 + i*8);
                for (int b=0;b<8;b++) p[b]=0;
            }
        }
        if (*(long *)((char*)ep + 0x40) != 0) {
            for (sk_word_t i = 0; i < *(sk_word_t *)((char*)ep + 0x40); i++) {
                sk_obj_link((sk_word_t)*(void**)((char*)tcb + 0xe0 + i*8));   /* FUN_004b23d8 */
                unsigned char *p = (unsigned char*)((char*)stk + 0x1e0 + i*8);
                for (int b=0;b<8;b++) p[b]=0;
            }
        }
        cnt = (sk_word_t)sk_per_cpu_base();
        if ((sk_word_t)tcb == cnt)
            sk_ep_activate(tcb);               /* FUN_0005fbc0 */
        else
            sk_ep_activate_remote(tcb);        /* FUN_004b6d60 */
        cnt = *(sk_word_t *)((char*)ep + 0x30);
    }
    if (cnt < want) {
        /* create 'want' threads */
        do {
            void *nt = sk_ep_new_thread(ep, 0);   /* FUN_0005eec4 */
            if (nt == NULL) sk_panic_bad(0, "Failed to create thread for an E[ndpoint]");
            /* decimal-format the endpoint id into the thread id field */
            unsigned int id = (unsigned int)*(unsigned short*)((char*)ep + 0x30)
                            + (((unsigned short)*(unsigned short*)((char*)ep + 0x30) >> 3) / 0x7d) * -1000;
            unsigned int acc = 0x48, div = 1000;
            do {
                unsigned int q = div / 10;
                unsigned int digit = q ? (id & 0xffff) / q : 0;
                acc = (digit + 0x30) & 0xffff | acc << 8;
                id -= digit * q;
            } while (div = q, 0x13 < div);
            sk_obj_id_set(nt, acc);            /* FUN_000618c4 */
            *(void **)((char*)nt + 0xa8) = ep;
            void *stk = (void *)sk_stack_alloc_off(0);
            /* prime register slots for the endpoint's register counts */
            if (*(long *)((char*)ep + 0x38) != 0)
                for (sk_word_t i = 0; i < *(sk_word_t *)((char*)ep + 0x38); i++) {
                    sk_word_t v = (sk_word_t)sk_ctx_state();   /* FUN_00034f70 */
                    *(sk_word_t*)((char*)stk + 0x1c0 + i*8) = v;
                    *(sk_word_t*)((char*)nt + 0xc0 + i*8) = v;
                }
            if (*(long *)((char*)ep + 0x40) != 0)
                for (sk_word_t i = 0; i < *(sk_word_t *)((char*)ep + 0x40); i++) {
                    sk_word_t v = (sk_word_t)sk_ctx_state();   /* FUN_00034f70 */
                    *(sk_word_t*)((char*)stk + 0x1e0 + i*8) = v;
                    *(sk_word_t*)((char*)nt + 0xe0 + i*8) = v;
                }
            /* set up entry: RO frame = (flags|0xfd in low, reg0 in high) */
            sk_word_t reg0 = *(sk_word_t *)((char*)nt + 0x28);
            sk_word_t flags = *(sk_word_t *)((char*)ep + 0x10);
            sk_word_t e = sk_obj_field_140(nt);
            sk_ro_frame_set(flags & 0xfd, flags >> 8, e);  /* low/high/high2 */
            CallSupervisor(0);
            if ((reg0 & 0xff) != 0) sk_ep_bad2(reg0);      /* FUN_004b7428 */
            cnt = *(sk_word_t *)((char*)ep + 0x30) + 1;
            *(sk_word_t *)((char*)ep + 0x30) = cnt;
            *(void **)((char*)ep + 0x50) = nt;
        } while (cnt < want);
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000635c0 @ 0x635c0   (est. sk_ep_setup_wrap)
 * Ghidra: void FUN_000635c0(undefined8*,ulong,undefined8,undefined8*)
 * Endpoint setup wrapper: calls the endpoint lock/setup routine with the given key (bit 1 forced), then copies three configuration words into the endpoint tail fields.
 * Confidence: medium
 * Notes: FUN_00062c2c; SoftwareBreakpoint(0x5519,0x63608).
 */
void sk_ep_setup_wrap(sk_word_t *ep, sk_word_t key, void *a, sk_word_t *cfg)
{
    if ((sk_word_t)ep <= (sk_word_t)ep + 10) {
        sk_ep_lock_setup(ep, key | 2, cfg);
        ep[0xb] = cfg[1];
        ep[0xc] = cfg[2];
        ep[10] = cfg[0];
        return;
    }
    sk_breakpoint(0x5519, 0x63608);
}

/*--------------------------------------------------------------------*/

/* FUN_00063694 @ 0x63694   (est. sk_ep_notif_tail)
 * Ghidra: undefined8 FUN_00063694(void)
 * Returns the last notification word of the current endpoint (from the per-CPU endpoint state): reads the endpoint base + 0xc0 plus its size field.
 * Confidence: medium
 * Notes: FUN_0005fad8; SoftwareBreakpoint(0x5519,0x636d0).
 */
sk_word_t sk_ep_notif_tail(void)
{
    sk_word_t *es = sk_ep_state(0);          /* FUN_0005fad8 */
    sk_word_t *p = (sk_word_t*)(es[0] + 0xc0);
    sk_word_t *e = p + es[1];
    if ((p <= e && e + 1 <= (sk_word_t*)(es[0] + 0xe0)) && e <= e + 1)
        return *e;
    sk_breakpoint(0x5519, 0x636d0);
}

/*--------------------------------------------------------------------*/

/* FUN_000636a4 @ 0x636a4   (est. sk_ep_notif_at)
 * Ghidra: undefined8 FUN_000636a4(long,long)
 * Returns the notification word at index param_2 of the endpoint's slot array (base + 0xc0), bounds-checked against +0xe0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x636d0).
 */
sk_word_t sk_ep_notif_at(void *ep, long i)
{
    sk_word_t *p = (sk_word_t*)((char*)ep + 0xc0) + i;
    if (((sk_word_t*)((char*)ep + 0xc0) <= p && p + 1 <= (sk_word_t*)((char*)ep + 0xe0))
        && p <= p + 1)
        return *p;
    sk_breakpoint(0x5519, 0x636d0);
}

/*--------------------------------------------------------------------*/

/* FUN_000636d0 @ 0x636d0   (est. sk_obj_field_20)
 * Ghidra: undefined8 FUN_000636d0(long)
 * Returns the object field at offset 0x20.
 * Confidence: medium
 */
sk_word_t sk_obj_field_20(void *obj){ return *(sk_word_t *)((char*)obj + 0x20); }

/*--------------------------------------------------------------------*/

/* FUN_000636d8 @ 0x636d8   (est. sk_obj_field_28b)
 * Ghidra: undefined8 FUN_000636d8(long)
 * Returns the object field at offset 0x28.
 * Confidence: medium
 */
sk_word_t sk_obj_field_28b(void *obj){ return *(sk_word_t *)((char*)obj + 0x28); }

/*--------------------------------------------------------------------*/

/* FUN_000636e0 @ 0x636e0   (est. sk_ep_drain)
 * Ghidra: void FUN_000636e0(undefined8)
 * Drains the per-CPU endpoint notification slots: for each active slot (count from +0xb8 bits 6-8) it spins with CallSupervisor(4) until the slot is clear, then stores the caller's context into the per-CPU slot pointer (+0xb0) and resets the slot count.
 * Confidence: medium
 * Notes: CallSupervisor(4); per-CPU +0xb0/+0xb8/+0xc0; SoftwareBreakpoint(0x5519,0x63768).
 */
void sk_ep_drain(void *ctx)
{
    void *cpu = sk_per_cpu_base();
    sk_word_t n = *(sk_word_t *)((char*)cpu + 0xb8) >> 6 & 7;
    if (n != 0) {
        for (sk_word_t i = 0; i < n; i++) {
            sk_word_t *slot = (sk_word_t*)((char*)cpu + 0xc0) + i;
            if ((sk_word_t*)slot < (sk_word_t*)((char*)cpu + 0xc0)
                || (sk_word_t*)((char*)cpu + 0xe0) < slot + 1 || slot + 1 < slot)
                sk_breakpoint(0x5519, 0x63768);
            do { CallSupervisor(4); } while (*slot == 1);
        }
    }
    *(void **)((char*)cpu + 0xb0) = ctx;
    *(sk_word_t *)((char*)cpu + 0xb8) = 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00063768 @ 0x63768   (est. sk_ep_restore)
 * Ghidra: void FUN_00063768(undefined8)
 * Restores the per-CPU endpoint notification state: drains the four notification slots (spinning via CallSupervisor(4) for active ones), copies each slot's value into the RO frame, re-links the saved endpoint, and stores the caller's context into the per-CPU slot pointer, resetting the slot count.
 * Confidence: low
 * Notes: CallSupervisor(4); per-CPU +0xb0/+0xb8/+0xc0/+0xe0; FUN_0005b0bc/00061994; SoftwareBreakpoint(0x5519,0x638ec).
 */
void sk_ep_restore(void *ctx)
{
    void *cpu = sk_per_cpu_base();
    sk_word_t saved = *(sk_word_t *)((char*)cpu + 0xb0);
    for (sk_word_t i = 0; i < 4; i++) {
        sk_word_t *slot = (sk_word_t*)((char*)cpu + 0xe0) + i;
        if ((sk_word_t*)((char*)cpu + 0x100) < slot + 1 || slot + 1 < slot)
            sk_breakpoint(0x5519, 0x638ec);
        sk_word_t v = *slot;
        if (i < (saved >> 6 & 7)) { do { CallSupervisor(4); } while (v == 1); }
        /* write v into RO frame at +0x1e0+i*8 */
        sk_ro_slot_set(i, v);
        sk_word_t *sv = (sk_word_t*)((char*)cpu + 0xc0 + i*8);
        if ((sk_word_t*)((char*)cpu + 0xe0) < sv + 1 || sv + 1 < sv)
            sk_breakpoint(0x5519, 0x638ec);
        sk_ro_slot_set2(i, *sv);
    }
    if ((sk_word_t)cpu <= (sk_word_t)cpu + 0x178) {
        sk_ep_final(cpu);                      /* FUN_0005b0bc */
        sk_obj_link_set(cpu, 0);               /* FUN_00061994 */
        *(sk_word_t *)((char*)cpu + 0xb0) = 0;
        *(sk_word_t *)((char*)cpu + 0xb8) = (sk_word_t)ctx;
        return;
    }
    sk_breakpoint(0x5519, 0x638ec);
}

/*--------------------------------------------------------------------*/

/* FUN_000638ec @ 0x638ec   (est. sk_error_str_fwd2)
 * Ghidra: void FUN_000638ec(void)
 * Forwarder to 0x62f08 (L4 error-code string copy).
 * Confidence: medium
 */
void sk_error_str_fwd2(void){ sk_error_str_out2(0, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006390c @ 0x6390c   (est. sk_list_pop)
 * Ghidra: ulong FUN_0006390c(ulong,ulong)
 * Pops up to `count` bytes from the current thread's linked data list: walks the list to find the first matching buffer (kind 5, sub 1), locks it, copies `count` bytes out and zeroes the consumed region, shrinking the buffer; returns the number of bytes consumed.
 * Confidence: low
 * Notes: thunk_FUN_0005c278; FUN_0005cb9c/0005ce54/00117cc4/00114330; SoftwareBreakpoint(0x5519,0x5c324).
 */
sk_word_t sk_list_pop(sk_word_t out, sk_word_t count)
{
    void *cpu = sk_per_cpu_base();
    long **list = **(long ***)((char*)cpu + 0x10);
    unsigned long *buf = NULL;
    if (list != NULL) {
        unsigned long *found = NULL;
        do {
            buf = (unsigned long *)list[3];
            if ((int)list[2] != 5 || (int)list[1] != 1) buf = found;
            list = (long *)*list;
            found = buf;
        } while (list != NULL);
    }
    unsigned long *p = buf + 0x10;
    if ((sk_word_t)p <= (sk_word_t)(buf + 0x12)) {
        sk_lock_acquire(p);                      /* FUN_0005cb9c */
        long avail = *buf - count;
        if (*buf < count) {
            count = 0;
        } else {
            unsigned long *src = (unsigned long*)((long)(buf + 1) + avail);
            if ((0x78 - avail < count || p < src) || src < buf + 1
                || (sk_memcpy((void*)out, src, count), out + count < out))
                sk_breakpoint(0x5519, 0x5c324);
            sk_zero32(src, count);               /* thunk_FUN_00114330 */
            *buf -= count;
        }
        if ((sk_word_t)buf <= (sk_word_t)(buf + 0x12)) {
            sk_lock_release_glue(p);             /* FUN_0005ce54 */
            return count;
        }
    }
    sk_breakpoint(0x5519, 0x5c324);
}

/*--------------------------------------------------------------------*/

/* FUN_00063910 @ 0x63910   (est. sk_ep_obj_get)
 * Ghidra: undefined8 FUN_00063910(ulong)
 * Returns the endpoint/notification object pointer at offset 0x58 when the object's flag (offset 0x10, bit 1) is set and the object is non-null, else 0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x6393c).
 */
sk_word_t sk_ep_obj_get(sk_word_t obj)
{
    if (obj == 0) return 0;
    if (((*(unsigned int*)(obj + 0x10) >> 1) & 1) == 0) return 0;
    if (obj + 0x70 < obj) sk_breakpoint(0x5519, 0x6393c);
    return *(sk_word_t *)(obj + 0x58);
}

/*--------------------------------------------------------------------*/

/* FUN_0006393c @ 0x6393c   (est. sk_ep_obj_check)
 * Ghidra: void FUN_0006393c(ulong)
 * Bounds-check helper for an endpoint object: verifies the object (when flagged) spans the required 0x70 bytes without wrapping.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x63970).
 */
void sk_ep_obj_check(sk_word_t obj)
{
    sk_word_t sel = (*(long *)(obj + 0x10) << 0x3e) >> 0x3f;
    sk_word_t v = obj & sel;
    if (v != 0 && ((obj + 0x70 & sel) < v + 0x70 || v + 0x70 < v))
        sk_breakpoint(0x5519, 0x63970);
}

/*--------------------------------------------------------------------*/

/* FUN_00063970 @ 0x63970   (est. sk_ep_id)
 * Ghidra: undefined4 FUN_00063970(ulong)
 * Returns the endpoint identifier: the 32-bit field at offset 0x60, or the sentinel 0x4e4f4550 ('NOEP') when the object has no endpoint flag or is null.
 * Confidence: medium
 * Notes: 0x4e4f4550 = 'NOEP'; SoftwareBreakpoint(0x5519,0x639a0).
 */
unsigned int sk_ep_id(sk_word_t obj)
{
    if (obj == 0) return 0x4e4f4550;
    if (((*(unsigned char*)(obj + 0x10) >> 1) & 1) == 0) return 0x4e4f4550;
    if (obj + 0x70 < obj) sk_breakpoint(0x5519, 0x639a0);
    return *(unsigned int *)(obj + 0x60);
}

/*--------------------------------------------------------------------*/

/* FUN_000639a0 @ 0x639a0   (est. sk_ro_write)
 * Ghidra: void FUN_000639a0(undefined8,undefined8*)
 * Writes the caller's word into the RO thread pointer and issues CallSupervisor(0) to publish it.
 * Confidence: medium
 * Notes: CallSupervisor(0).
 */
void sk_ro_write(void *a, sk_word_t *word)
{
    sk_word_t v = *word;
    sk_ro_write8(v);
    CallSupervisor(0);
    *word = v;
}

/*--------------------------------------------------------------------*/

/* FUN_00063a50 @ 0x63a50   (est. sk_key_table_get)
 * Ghidra: void FUN_00063a50(void)
 * Loads the global key/destructor table pointer DAT_006b2718, seeding it from the current TCB's table field (+0x50) when it is not yet initialized, and stores it back.
 * Confidence: medium
 * Notes: DAT_006b2718; FUN_0005bb68; SoftwareBreakpoint(0x5519,0x63a94).
 */
void sk_key_table_get(void)
{
    sk_word_t t = sk_key_table;                  /* DAT_006b2718 */
    if (sk_key_table == 0) {
        void *tcb = sk_tcb_current();            /* FUN_0005bb68 */
        t = *(sk_word_t *)((char*)tcb + 0x50);
        if (t + 0x2f0 < t) sk_breakpoint(0x5519, 0x63a94);
    }
    sk_key_table = t;
}

/*--------------------------------------------------------------------*/

/* FUN_00063a94 @ 0x63a94   (est. sk_key_table_seed)
 * Ghidra: void FUN_00063a94(void)
 * Seeds the global key/destructor table pointer to the fixed address 0x64dce8.
 * Confidence: high
 * Notes: DAT_006b2718 = 0x64dce8.
 */
void sk_key_table_seed(void){ sk_key_table = 0x64dce8; }

/*--------------------------------------------------------------------*/

/* FUN_00063aa8 @ 0x63aa8   (est. sk_key_alloc)
 * Ghidra: ulong FUN_00063aa8(undefined8,undefined8,undefined8)
 * Allocates a slot in the key/destructor table: locks the table, picks the next free index (bounded to 0x20), stores the constructor parameters into the slot, and unlocks; returns the allocated key index, or breaks if the table is exhausted or another CPU owns it.
 * Confidence: medium
 * Notes: DAT_006b2718; FUN_00063b50/00063b84/00063c5c/004b7480/004b749c; SoftwareBreakpoint(0x5519,0x63b50).
 */
sk_word_t sk_key_alloc(void *a, void *b, void *c)
{
    void *cpu = sk_per_cpu_base();
    if (*(long *)((char*)cpu + 0xf8) == 0) {
        sk_word_t *tbl = sk_key_table_p();
        if (sk_key_table == 0) {
            void *tcb = sk_tcb_current();
            tbl = *(sk_word_t **)((char*)tcb + 0x50);
            if ((sk_word_t)tbl + 0x5e < (sk_word_t)tbl) sk_breakpoint(0x5519, 0x63b50);
        }
        sk_key_table = (sk_word_t)tbl;
        tbl = sk_key_table_p();
        sk_key_lock();                           /* FUN_00063b50 */
        sk_word_t idx = *tbl;
        if (idx < 0x20) {
            *tbl = idx + 1;
            sk_key_store(idx, (long)(uintptr_t)a, (sk_word_t)(uintptr_t)b, (int)(uintptr_t)c);          /* FUN_00063b84 */
            sk_key_unlock();                     /* FUN_00063c5c */
            return idx;
        }
    } else {
        sk_key_owned();                          /* FUN_004b7480 */
    }
    sk_key_not_owned();                          /* FUN_004b749c */
    sk_breakpoint(0x5519, 0x63b50);
}

/*--------------------------------------------------------------------*/

/* FUN_00063b50 @ 0x63b50   (est. sk_key_lock)
 * Ghidra: void FUN_00063b50(void)
 * Locks the key/destructor table via the current TCB's lock helper, asserting the table's slot range is valid.
 * Confidence: medium
 * Notes: FUN_0005bb68/0005cb9c; SoftwareBreakpoint(0x5519,0x63b84).
 */
void sk_key_lock(void)
{
    void *tcb = sk_tcb_current();
    if ((sk_word_t)((char*)tcb + 0x60) <= (sk_word_t)((char*)tcb + 0x70)) {
        sk_lock_acquire((char*)tcb + 0x60);                      /* FUN_0005cb9c */
        return;
    }
    sk_breakpoint(0x5519, 0x63b84);
}

/*--------------------------------------------------------------------*/

/* FUN_00063b84 @ 0x63b84   (est. sk_key_store)
 * Ghidra: void FUN_00063b84(long,long,undefined8,int)
 * Stores a key entry into the table: writes the key value and its destructor-constructor callback into the indexed slots, and (when both are set) registers a pending-construction callback.
 * Confidence: medium
 * Notes: DAT_006b2718; FUN_0005bb68/0005bd7c; SoftwareBreakpoint(0x5519,0x63c5c).
 */
void sk_key_store(long idx, long val, sk_word_t cb, int do_cb)
{
    sk_word_t t = sk_key_table;
    if (sk_key_table == 0) {
        void *tcb = sk_tcb_current();
        t = *(sk_word_t *)((char*)tcb + 0x50);
        if (t + 0x2f0 < t) sk_breakpoint(0x5519, 0x63c5c);
    }
    sk_key_table = t;
    sk_word_t *tbl = sk_key_table_p();
    sk_word_t *base = (sk_word_t*)(sk_key_table + 8);
    sk_word_t *e = (sk_word_t*)(sk_key_table + 0x100);
    sk_word_t *slot = (sk_word_t*)(sk_key_table + idx * 8);
    if ((base <= slot && slot + 1 <= e) && slot <= slot + 1) {
        *(sk_word_t *)(sk_key_table + idx * 8) = val;
        sk_word_t *cbslot = e + idx;
        sk_word_t *cbp = cbslot - 1;
        if ((e <= cbp && cbslot <= (sk_word_t*)(t + 0x1f8)) && cbp <= cbslot) {
            *cbp = cb;
            if (val != 0 && do_cb != 0)
                sk_pending_cb((void(*)(void))sk_key_construct_cb, &idx);   /* FUN_0005bd7c + FUN_00063eb4 */
            return;
        }
    }
    sk_breakpoint(0x5519, 0x63c5c);
}

/*--------------------------------------------------------------------*/

/* FUN_00063c5c @ 0x63c5c   (est. sk_key_unlock)
 * Ghidra: void FUN_00063c5c(void)
 * Unlocks the key/destructor table via the current TCB's unlock helper.
 * Confidence: medium
 * Notes: FUN_0005bb68/0005ce54; SoftwareBreakpoint(0x5519,0x63c90).
 */
void sk_key_unlock(void)
{
    void *tcb = sk_tcb_current();
    if ((sk_word_t)((char*)tcb + 0x60) <= (sk_word_t)((char*)tcb + 0x70)) {
        sk_lock_release_glue((char*)tcb + 0x60);                  /* FUN_0005ce54 */
        return;
    }
    sk_breakpoint(0x5519, 0x63c90);
}

/*--------------------------------------------------------------------*/

/* FUN_00063cfc @ 0x63cfc   (est. sk_key_construct_all)
 * Ghidra: void FUN_00063cfc(long)
 * Constructs the first 0x1c key entries of the table: locks the table, then for each slot runs its constructor callback (or the caller's array value), incrementing a construction counter and panicking 'constructing deleted key' if a slot is being constructed while deleted.
 * Confidence: medium
 * Notes: String s_constructing_deleted_key_005bdf0d; DAT_006b2718; FUN_00063b50/00063c5c.
 */
void sk_key_construct_all(long *vals)
{
    sk_word_t t = sk_key_table;
    if (sk_key_table == 0) {
        void *tcb = sk_tcb_current();
        t = *(sk_word_t *)((char*)tcb + 0x50);
        if (t + 0x2f0 < t) sk_breakpoint(0x5519, 0x63dc4);
    }
    sk_key_table = t;
    sk_key_lock();
    long *src = vals + 0x18/8;
    int n = 0x1c;
    while ((sk_word_t*)(t + 0x28) <= (sk_word_t*)(t + 0x100) &&
           (sk_word_t*)(t + 0x20) <= (sk_word_t*)(t + 0x28)) {
        long (*ctor)(void) = *(long (**)(void))(t + 0x20);
        long v;
        if (ctor == NULL) v = *src;
        else { v = ctor(); *src = v; }
        if (v != 0) {
            long *c = (long*)(t + 0x210);
            if (*c != -1) { *c += 1; }
            else sk_panic_bad(0, "constructing deleted key");
        }
        src++; t += 8; n--;
        if (n == 0) { sk_key_unlock(); return; }
    }
    sk_breakpoint(0x5519, 0x63dc4);
}

/*--------------------------------------------------------------------*/

/* FUN_00063dd4 @ 0x63dd4   (est. sk_key_drain)
 * Ghidra: void FUN_00063dd4(void)
 * Drains pending key destructors: marks the current CPU as owning the table, then for each nonzero pending slot runs its destructor callback, clears the slot and decrements the construction counter, finally clearing the ownership flag.
 * Confidence: low
 * Notes: DAT_006b2718; FUN_00063b50/00063c5c; SoftwareBreakpoint(0x5519,0x63ea4).
 */
void sk_key_drain(void)
{
    void *cpu = sk_per_cpu_base();
    sk_word_t t = sk_key_table;
    if (sk_key_table == 0) {
        void *tcb = sk_tcb_current();
        t = *(sk_word_t *)((char*)tcb + 0x50);
        if (t + 0x2f0 < t) sk_breakpoint(0x5519, 0x63ea4);
    }
    sk_key_table = t;
    *(sk_word_t *)((char*)cpu + 0xf8) = 1;
    long off = 0;
    do {
        if (*(long *)((char*)cpu + 0x18 + off) != 0) {
            sk_key_lock();
            sk_word_t *slot = (sk_word_t*)(t + off + 0x120);
            if ((sk_word_t*)(t + 0x1f8) < slot ||
                (sk_word_t *)(t + off + 0x118) > slot)
                sk_breakpoint(0x5519, 0x63ea4);
            void (*dtor)(sk_word_t) = *(void (**)(sk_word_t))(t + off + 0x118);
            if (dtor) dtor(*(sk_word_t *)((char*)cpu + 0x18 + off));
            *(sk_word_t *)((char*)cpu + 0x18 + off) = 0;
            long *c = (long*)(t + off + 0x210);
            *c -= 1;
            sk_key_unlock();
        }
        off += 8;
        if (off == 0xe0) { *(sk_word_t *)((char*)cpu + 0xf8) = 0; return; }
    } while (1);
}

/*--------------------------------------------------------------------*/

/* FUN_00063ea4 @ 0x63ea4   (est. sk_per_cpu_set)
 * Ghidra: void FUN_00063ea4(undefined8)
 * Sets the current CPU context: writes param_1 into tpidr_el0.
 * Confidence: high
 */
void sk_per_cpu_set(sk_word_t cpu){ __asm__ volatile("msr tpidr_el0, %0" :: "r"(cpu)); }

/*--------------------------------------------------------------------*/

/* FUN_00063eb4 @ 0x63eb4   (est. sk_key_construct_cb)
 * Ghidra: undefined8 FUN_00063eb4(long*,undefined8)
 * Key-construction callback: reads the pending key index, locks the table, runs the slot's constructor, stores its result at a stack-derived offset, bumps the construction counter, and returns success; panics 'constructing deleted key' on overflow.
 * Confidence: medium
 * Notes: String s_constructing_deleted_key_005bdf0d; DAT_006b2718; FUN_000614f8/0005bb68; SoftwareBreakpoint(0x5519,0x63f84).
 */
sk_word_t sk_key_construct_cb(long *idx, sk_word_t a)
{
    long i = *idx;
    sk_word_t t = sk_key_table;
    if (sk_key_table == 0) {
        void *tcb = sk_tcb_current();
        t = *(sk_word_t *)((char*)tcb + 0x50);
        if (t + 0x2f0 < t) sk_breakpoint(0x5519, 0x63f84);
    }
    sk_key_table = t;
    long *out = (long *)sk_stack_alloc_low(a);
    sk_word_t *slot = (sk_word_t*)(t + i * 8);
    if ((sk_word_t*)(t + 8) <= slot && slot + 1 <= (sk_word_t*)(t + 0x100) && slot <= slot + 1) {
        i -= 1;
        long v = (*(long(*)(void))(*slot))();
        long *op = out + i;
        if ((out <= op && op + 1 <= out + 0x1f) && op <= op + 1) {
            *op = v;
            if (v != 0) {
                long *c = (long*)(t + i * 8 + 0x1f8);
                if (*c != -1) *c += 1;
                else sk_panic_bad(0, "constructing deleted key");
            }
            return 1;
        }
    }
    sk_breakpoint(0x5519, 0x63f84);
}

/*--------------------------------------------------------------------*/

/* FUN_00063ffc @ 0x63ffc   (est. sk_stack_base)
 * Ghidra: undefined8 FUN_00063ffc(void)
 * Returns the fixed boot-stack base constant 0x28.
 * Confidence: high
 */
sk_word_t sk_stack_base(void){ return 0x28; }

/*--------------------------------------------------------------------*/

/* FUN_0006402c @ 0x6402c   (est. sk_obj_ctx_init)
 * Ghidra: void FUN_0006402c(ulong)
 * Initializes a 0x28-byte object context: imports a template block and zero-fills the object, with an overflow breakpoint.
 * Confidence: medium
 * Notes: FUN_00114790/001143a0; SoftwareBreakpoint(0x5519,0x640e4).
 */
void sk_obj_ctx_init(sk_word_t obj)
{
    sk_ctx_import(obj, 0x68a6f0, 0);            /* FUN_00114790 */
    if (obj + 0x28 < obj) sk_breakpoint(0x5519, 0x640e4);
    sk_zero(obj, 0, 0x28);                      /* FUN_001143a0 */
}

/*--------------------------------------------------------------------*/

/* FUN_000640e4 @ 0x640e4   (est. sk_exc_ep_active)
 * Ghidra: bool FUN_000640e4(void)
 * Returns whether the current TCB has an active exception endpoint (field +0x48 nonzero).
 * Confidence: medium
 * Notes: FUN_0005bb68.
 */
bool sk_exc_ep_active(void)
{
    void *tcb = sk_tcb_current();
    return *(long *)((char*)tcb + 0x48) != 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00064108 @ 0x64108   (est. sk_exc_ep_setup)
 * Ghidra: void FUN_00064108(void)
 * Initializes the exception-handling endpoint and handler list. Refuses to run if an exception endpoint is already active; allocates the endpoint (or seeds it from a fixed 8-slot table), links it to the current TCB, sets up its configuration, programs the RO frame (selector 0xdc/0x51) and issues CallSupervisor(0). Then iterates the installed exception handlers, running each with its saved state via CallSupervisor(0), and finally resets the handler-table back-pointers to two fixed read-only slots.
 * Confidence: low
 * Notes: Strings s_exception_handling_can_only_be_i_005bdf26, s_failed_to_allocate_exception_end_005bdf56, s__xrt_0x_06x__Set_exception_handl_005be100; L4_ErrorCodeTruncated string bytes; DAT_006b2720/006b2728/006ad928; FUN_0019ae2c/00060540/0005e0dc/000635c0/0005bd7c/000533ec/004b75e4/004b7594/004b7544; CallSupervisor(0); SoftwareBreakpoint(0x5519,0x644a8); writes to read-only 0x64dfd8/0x64dff0.
 */
void sk_exc_ep_setup(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    void *tcb = sk_tcb_current();
    if (*(long *)((char*)tcb + 0x48) != 0)
        sk_panic_bad(0, "exception handling can only be i[n one context]");
    /* derive a check constant from the 'Truncated' string — nonzero if a marker present */
    if (sk_exc_marker == 0) {
        sk_exc_ep = (sk_word_t)sk_alloc_ep(8);              /* FUN_0019ae2c */
        if (sk_exc_ep == 0)
            sk_panic_bad(0, "failed to allocate exception end[point]");
        if ((sk_flag_get() & 1) == 0) {
            sk_ep_activate_id((void*)(uintptr_t)sk_exc_ep, 8);     /* FUN_0005e0dc */
        }
    }
    *(sk_word_t *)((char*)tcb + 0x48) = sk_exc_ep;
    /* endpoint config copied from 0x65c8d0 template */
    sk_word_t cfg[3] = { DAT_004be5f0, DAT_004be5f8, DAT_004be600 };
    sk_ep_setup_wrap((sk_word_t*)0x6ad910, sk_exc_ep, (void*)0x65c8d0, cfg);
    /* program RO frame: selector 0xdc/0x51, CallSupervisor(0) */
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    tp[0]=0xdc; tp[1]=0x51; tp[2]=0; tp[3]=0; tp[4]=0; tp[5]=0; tp[6]=0; tp[7]=0;
    CallSupervisor(0);
    if ((sk_exc_ep & 0xff) == 0) {
        sk_reg_pending(sk_exc_handler_cb, 0);    /* FUN_0005bd7c + &DAT_000648d8 */
        sk_word_t node = sk_exc_list;            /* DAT_006ad928 */
        void *cur = sk_exc_first();              /* FUN_000533ec */
        while (node != 0) {
            sk_word_t saved = *(sk_word_t *)((char*)node + 0x28);
            do { CallSupervisor(0); } while (saved == 1);
            if (cur != 0) {
                sk_per_cpu_base();
                if ((sk_word_t)node + 0x178 < (sk_word_t)node) break;
                sk_fmt((char*)0xeb1a02bf914012ba, "%s 0x%06x Set exception handl[er]");
                sk_word_t h = (sk_word_t)cur;
                sk_ro_frame_write(h);            /* write cur into RO frame */
                CallSupervisor(0);
                if ((saved & 0xff) != 0) sk_exc_bad(saved);    /* FUN_004b7594 */
            }
            short more = sk_exc_next(node, node + 0x178, local88);   /* FUN_004b75e4 */
            if (more == 1) break;
            node = local88[0];
            if (more != 0) sk_breakpoint(0x5519, 0x644a8);
        }
        /* reset handler back-pointers to fixed read-only slots */
        sk_word_t x = 0;
        do {
            sk_word_t old = sk_exc_slot;
            if (sk_exc_slot == x) sk_exc_slot = 0x64dfd8;
            sk_word_t keep = old != x;
            *(volatile sk_word_t*)0x64dfd8 = x;
            if (keep) *(volatile sk_word_t*)0x64dfd8 = old;
            x = old;
        } while (keep);
        x = 0;
        do {
            sk_word_t old = sk_exc_slot;
            if (sk_exc_slot == x) sk_exc_slot = 0x64dff0;
            keep = old != x;
            *(volatile sk_word_t*)0x64dff0 = x;
            if (keep) *(volatile sk_word_t*)0x64dff0 = old;
            x = old;
        } while (keep);
        if (canary != 0xd37afd4bb400012a) sk_stack_fail();
        return;
    } else {
        sk_exc_bad2(sk_exc_ep, local88);         /* FUN_004b7544 */
    }
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00064578 @ 0x64578   (est. sk_vspace_freeze)
 * Ghidra: long FUN_00064578(undefined8,ulong,long)
 * Address-space freeze/exception dispatch: for a freeze/enter request (upper-16 bits == 1) it queries the page-table helper and, on failure, logs 'vas freeze failed' and returns the error shifted up; otherwise it reads the caller's register words from the RO frame, classifies them, and walks the registered exception-handler chain (per-object or the global list) invoking each; a handler returning 1 stops the walk, and one returning 2 falls through to the default exception handler.
 * Confidence: low
 * Notes: String s__xrt_0x_06x__vas_freeze_failed_w_005be458; DAT_006b2728 (handler chain); FUN_00034a2c/00065344/000651e8/00064de8/00060524; SoftwareBreakpoint(0x5519,0x647a0).
 */
long sk_vspace_freeze(void *a, sk_word_t mode, void *obj)
{
    if (((unsigned)(mode >> 0x10) & 0xffff) == 1) {
        void *pt = sk_pt_ctx();                        /* FUN_00034a2c */
        sk_word_t r = (*(sk_word_t(*)(void))(*(void***)((char*)pt + 0x60)[0]))();
        r &= 0xff;
        if (r == 0) return 0;
        sk_per_cpu_base();
        if ((sk_word_t)(0x64cb40 + r) >= (sk_word_t)0x64cb40
            && 0x64cb48 + r <= 0x64cb80 && 0x64cb40 + r <= 0x64cb48 + r) {
            sk_fmt((char*)0xeb1a02bf914012ba, "%s 0x%06x vas freeze failed w[ith]");
            return r << 0x10;
        }
        sk_breakpoint(0x5519, 0x647a0);
    }
    if ((mode & 0xffff0000) == 0) {
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        sk_word_t w0 = rd64(tp + 8);
        sk_word_t w1 = rd64(tp + 0x10);
        sk_word_t cls[4] = {0,0,0,0};
        sk_exc_classify((sk_word_t*)&cls, &w0, (sk_word_t*)&cls[2]);
        sk_exc_classify((sk_word_t*)&cls, obj, (sk_word_t*)&cls[2]);  /* FUN_000651e8 */
        void **head = *(void ***)((char*)obj + 0x98);
        int rc = 0;
        void **cur = head;
        if (cur != NULL) {
            do {
                rc = (*(int(*)(void*,void*,sk_word_t*))(cur[2]))(cur[1], obj, &cls);
                if ((unsigned)(rc - 1) < 2) break;
                cur = (void **)*cur;
            } while (cur != NULL);
            if (rc == 1) return 0xffff0000;
            cur = sk_exc_slot_p();                    /* DAT_006b2728 */
            if (rc != 2) goto walk_global;
        } else {
            cur = sk_exc_slot_p();
walk_global:
            for (; cur != NULL; cur = (void **)*cur) {
                rc = (*(int(*)(void*,void*,sk_word_t*))(cur[2]))(cur[1], obj, &cls);
                if ((unsigned)(rc - 1) < 2) break;
            }
            if (rc == 1) return 0xffff0000;
        }
        return sk_exc_default(obj, &cls);             /* FUN_00064de8 */
    }
    return 0xffff0000;
}

/*--------------------------------------------------------------------*/

/* FUN_000647a0 @ 0x647a0   (est. sk_error_str_out3)
 * Ghidra: void FUN_000647a0(undefined8,byte)
 * Copies the canonical L4_ErrorCode* string for the given code (0-9); >9 uses a generic fallback.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004be608..; DAT_004be748.
 */
void sk_error_str_out3(char *out, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) { sk_memcpy(out, "unknown", 0x20); return; }
    sk_memcpy(out, names[code], 0x20);
}

/*--------------------------------------------------------------------*/

/* FUN_000648e4 @ 0x648e4   (est. sk_amx_cap_alloc_fwd)
 * Ghidra: undefined8 FUN_000648e4(undefined8,undefined8)
 * Forwarder: allocates the AMX capability for the given object and returns 1.
 * Confidence: medium
 * Notes: FUN_00064c24.
 */
sk_word_t sk_amx_cap_alloc_fwd(void *a, void *obj){ sk_amx_cap_alloc(a, obj, 0); return 1; }

/*--------------------------------------------------------------------*/

/* FUN_00064904 @ 0x64904   (est. sk_amx_cap_alloc)
 * Ghidra: void FUN_00064904(undefined8,long,long*)
 * Allocates an AMX capability for the object: when the request kind is 3/sub 2 it allocates the capability object, programs the RO frame (selector 3 + cap pointer), issues CallSupervisor(0), and returns success; failures panic 'failed to allocate AMX capabilit[ies]'.
 * Confidence: medium
 * Notes: String s_failed_to_allocate_AMX_capabilit_005be253; FUN_0019ae2c/004b7664; CallSupervisor(0).
 */
sk_word_t sk_amx_cap_alloc(void *a, void *obj, long *req)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t rc = 0;
    if ((*req == 3) && ((char)req[3] == 2)) {
        long cap = *(long *)((char*)obj + 0x108);
        if (cap == 0) {
            cap = (long)sk_alloc_ep(0x15);           /* FUN_0019ae2c */
            *(long *)((char*)obj + 0x108) = cap;
            if (cap == 0) rc = 0; else rc = 1;
            goto done;
        }
        sk_word_t prev = *(sk_word_t *)((char*)obj + 0x28);
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        tp[0]=3; tp[1]=0; tp[2]=0; tp[3]=0; tp[4]=0; tp[5]=0; tp[6]=0; tp[7]=0;
        wr64(tp + 8, cap);
        CallSupervisor(0);
        if ((prev & 0xff) != 0) rc = sk_amx_bad(prev);    /* FUN_004b7664 */
        else rc = 1;
    done:
        if (rc == 0)
            sk_panic_bad(0, "failed to allocate AMX capabilit[ies]");
        return rc;
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00064a7c @ 0x64a7c   (est. sk_list_push)
 * Ghidra: void FUN_00064a7c(undefined8*)
 * Prepends the given node to the global handler chain (DAT_006b2728), splicing it in and preserving the existing head.
 * Confidence: medium
 * Notes: DAT_006b2728.
 */
void sk_list_push(void **node)
{
    *node = NULL;
    void **prev = NULL;
    do {
        void **head = (void **)sk_exc_slot;
        if (sk_exc_slot == (sk_word_t)prev) sk_exc_slot = (sk_word_t)node;
        int keep = head != prev;
        if (keep) prev = head;
        *node = prev;
        prev = head;
    } while (keep);
}

/*--------------------------------------------------------------------*/

/* FUN_00064aac @ 0x64aac   (est. sk_sme_cap_alloc)
 * Ghidra: void FUN_00064aac(undefined8,long,long*)
 * Allocates an SME capability for the object: for request kind 3/sub 3 it allocates the capability object, programs the RO frame (selector 2 + cap pointer), issues CallSupervisor(0); failures panic 'failed to allocate SME capabilit[ies]'.
 * Confidence: medium
 * Notes: String s_failed_to_allocate_SME_capabilit_005be2fb; FUN_0019ae2c/004b76b4; CallSupervisor(0).
 */
sk_word_t sk_sme_cap_alloc(void *a, void *obj, long *req)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t rc = 0;
    if ((*req == 3) && ((char)req[3] == 3)) {
        long cap = *(long *)((char*)obj + 0x110);
        if (cap == 0) {
            cap = (long)sk_alloc_ep(0x14);
            *(long *)((char*)obj + 0x110) = cap;
            if (cap == 0) rc = 0; else rc = 1;
            goto done;
        }
        sk_word_t prev = *(sk_word_t *)((char*)obj + 0x28);
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        tp[0]=2; tp[1]=0; tp[2]=0; tp[3]=0; tp[4]=0; tp[5]=0; tp[6]=0; tp[7]=0;
        wr64(tp + 8, cap);
        CallSupervisor(0);
        if ((prev & 0xff) != 0) rc = sk_sme_bad(prev);     /* FUN_004b76b4 */
        else rc = 1;
    done:
        if (rc == 0)
            sk_panic_bad(0, "failed to allocate SME capabilit[ies]");
        return rc;
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00064c24 @ 0x64c24   (est. sk_amx_cap_alloc2)
 * Ghidra: void FUN_00064c24(long)
 * Allocates the object's AMX capability slot (+0x88) if not already present, invoking the setup helper.
 * Confidence: medium
 * Notes: FUN_00064cac/004b7704.
 */
void sk_amx_cap_alloc2(void *obj)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    if (*(long *)((char*)obj + 0x88) == 0) {
        long cap = sk_amx_ep_alloc(0);            /* FUN_00064cac */
        *(long *)((char*)obj + 0x88) = cap;
        if (cap != 0) sk_amx_setup(obj, (long*)((char*)obj + 0x88));   /* FUN_004b7704 */
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00064cac @ 0x64cac   (est. sk_amx_ep_alloc)
 * Ghidra: long FUN_00064cac(undefined8)
 * Allocates an AMX exception endpoint: when the current TCB already has an exception endpoint it reads the AMX state, programs the RO frame with the saved context (DAT_004be5e0), issues CallSupervisor(3), and returns the AMX state pointer; otherwise returns 0.
 * Confidence: low
 * Notes: DAT_004be5e0/uRam00000000004be5e8; FUN_0005bb68/00034f70/004b23d8; CallSupervisor(3).
 */
long sk_amx_ep_alloc(sk_word_t a)
{
    void *tcb = sk_tcb_current();
    if (*(long *)((char*)tcb + 0x48) != 0) {
        void *amx = sk_amx_state();              /* FUN_00034f70 */
        sk_word_t lo = sk_amx_seed_lo;           /* _DAT_004be5e0 */
        sk_word_t hi = sk_amx_seed_hi;           /* uRam00000000004be5e8 */
        if (amx == 0) return 0;
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        wr64(tp, lo); wr64(tp+8, hi); wr64(tp+0x10, a);   /* seed + param into frame */
        CallSupervisor(3);
        if (*(long *)((char*)tcb + 0x48) == 0) return (long)amx;
        sk_amx_free(amx, amx, 2);                /* FUN_004b23d8 */
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00064de8 @ 0x64de8   (est. sk_exc_default)
 * Ghidra: undefined8 FUN_00064de8(undefined8,long)
 * Default exception handler: consults the current TCB's registered exception dispatcher (field +0x80); if the dispatcher accepts the exception it returns 0xffff0000 (handled), otherwise it fetches the exception ESR/FAR pair and reports them via the crash-report path with 'Caught exception: esr 0x%016zx f[ar]'.
 * Confidence: medium
 * Notes: String s_Caught_exception__esr_0x_016zx_f_005be20f; FUN_0005bb68/00064e84; dispatch table +0x10.
 */
sk_word_t sk_exc_default(void *a, sk_word_t *cls)
{
    void *tcb = sk_tcb_current();
    void *disp = *(void **)((char*)tcb + 0x80);
    if (disp != NULL) {
        int rc = (*(int(*)(void*,void*,sk_word_t*))(*(void***)((char*)disp + 0x10)[0]))(
                     *(void**)((char*)disp + 8), a, cls);
        if (rc == 1) return 0xffff0000;
    }
    sk_word_t esr = 0, far = 0;
    void **p = *(void ***)(cls + 0x10/8);
    if (p != NULL) { esr = (sk_word_t)p[0]; far = (sk_word_t)p[1]; }
    sk_exc_report((sk_word_t)(uintptr_t)a, esr, far);                  /* FUN_00064e84 */
    sk_panic_bad((int)(uintptr_t)a, "Caught exception: esr 0x%016zx f[ar]");
}

/*--------------------------------------------------------------------*/

/* FUN_00064e84 @ 0x64e84   (est. sk_exc_report)
 * Ghidra: void FUN_00064e84(undefined8,undefined8,undefined8)
 * Reports an exception by walking the registered panic/exception hook list: for each hook with a negative kind byte it captures its details, and if no hook is present it emits the full crash report with the 'thread panic' banner, then restores the log context.
 * Confidence: low
 * Notes: String s_thread_panic_005be529; FUN_000544d0/0005453c/0005ba14/004b78c0; calls 0x62474 (crash report); SoftwareBreakpoint(0x5519,0x64f50).
 */
void sk_exc_report(sk_word_t a, sk_word_t esr, sk_word_t far)
{
    int ctx = sk_log_push(0xeb1a02bf914012ba);   /* thunk_FUN_000544d0 */
    void **hook = (void **)sk_panic_hooks();     /* FUN_0005ba14 */
    for (;;) {
        if (hook == NULL) {
            sk_crash_report("thread panic", 0x21, 0xeb1a02bf914012ba, (void*)a, 1, 1, esr, far);
            if (ctx == 0) sk_log_pop(0xeb1a02bf914012ba);   /* thunk_FUN_0005453c */
            return;
        }
        if (*(char *)(hook + 1) < 0) {
            sk_word_t d = 0;
            if ((sk_word_t)hook + 0xf < (sk_word_t)hook) sk_breakpoint(0x5519, 0x64f50);
            sk_hook_capture(hook, &d);           /* FUN_004b78c0 */
        }
        hook = (void **)*hook;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00065020 @ 0x65020   (est. sk_xrt_freeze)
 * Ghidra: undefined1[16] FUN_00065020(void)
 * Freezes the exception endpoint for the current thread: when no exception endpoint is active it panics; otherwise it programs the RO frame (selector 0/1), issues CallSupervisor(0), logs 'xrt freeze: freeze o[f]' on the idle path, and returns the frozen value 1.
 * Confidence: medium
 * Notes: String s__xrt_0x_06x__xrt_freeze__freeze_o_005be417; FUN_004b79c8/004b7984; CallSupervisor(0).
 */
sk_word_t sk_xrt_freeze(void)
{
    void *tcb = sk_tcb_current();
    long ep = *(long *)((char*)tcb + 0x48);
    if (ep == 0) { sk_freeze_no_ep(); return 1; }      /* FUN_004b79c8 */
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    tp[0]=0; tp[1]=0; tp[2]=1; tp[3]=0; tp[4]=0; tp[5]=0; tp[6]=0; tp[7]=0;
    CallSupervisor(0);
    if (ep == 0) {
        sk_per_cpu_base();
        sk_fmt((char*)0xeb1a02bf914012ba, "%s 0x%06x xrt freeze: freeze o[f]");
    } else {
        sk_freeze_ep(ep, 0);                     /* FUN_004b7984 */
    }
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00065138 @ 0x65138   (est. sk_error_str_fwd3)
 * Ghidra: void FUN_00065138(void)
 * Forwarder to 0x647a0 (L4 error-code string).
 * Confidence: medium
 */
void sk_error_str_fwd3(void){ sk_error_str_out3(0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00065158 @ 0x65158   (est. sk_noop_65158)
 * Ghidra: void FUN_00065158(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_65158(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006516c @ 0x6516c   (est. sk_noop_6516c)
 * Ghidra: void FUN_0006516c(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_6516c(void){ }

/*--------------------------------------------------------------------*/

/* FUN_00065190 @ 0x65190   (est. sk_ro_frame_byte)
 * Ghidra: void FUN_00065190(undefined8,undefined8,undefined8)
 * Writes a byte and the high half of a word into the RO frame at caller-derived offsets.
 * Confidence: low
 * Notes: Uses in_x9/in_w8 register inputs.
 */
void sk_ro_frame_byte(sk_word_t a, sk_word_t b, sk_word_t c)
{
    /* register-passed RO frame base in x9, byte in w8 */
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    tp[4] = (unsigned char)a;
    tp[6] = (unsigned char)(c >> 0x30);
    tp[7] = (unsigned char)(c >> 0x38);
}

/*--------------------------------------------------------------------*/

/* FUN_000651ac @ 0x651ac   (est. sk_noop_651ac)
 * Ghidra: void FUN_000651ac(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_651ac(void){ }

/*--------------------------------------------------------------------*/

/* FUN_000651bc @ 0x651bc   (est. sk_noop_651bc)
 * Ghidra: void FUN_000651bc(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_651bc(void){ }

/*--------------------------------------------------------------------*/

/* FUN_000651d0 @ 0x651d0   (est. sk_error_str_fwd4)
 * Ghidra: void FUN_000651d0(void)
 * Forwarder to 0x647a0 (L4 error-code string).
 * Confidence: medium
 */
void sk_error_str_fwd4(void){ sk_error_str_out3(0,0); }

/*--------------------------------------------------------------------*/

/* FUN_000651e8 @ 0x651e8   (est. sk_exc_classify)
 * Ghidra: void FUN_000651e8(undefined8*,long,ulong*)
 * Classifies an exception/error record: inspects the mode bits of the first word and fills the 4-word output with a normalized exception descriptor (kind, related word, sub-fields), covering AMX/SVE/MTE and data/instruction fault kinds.
 * Confidence: low
 * Notes: FUN_00065350/00065344; modes 0x1d/0x3c/0x3f/0x24..0x3b.
 */
void sk_exc_classify(sk_word_t *out, void *obj, sk_word_t *in)
{
    sk_word_t a = in[0];
    sk_word_t b = in[1];
    unsigned int mode = (unsigned)(a >> 0x1a) & 0x3f;
    if (mode < 0x24) {
        if (mode - 0x20 > 1) {
            if (mode == 0x1d) {
                sk_word_t s = sk_exc_special();            /* FUN_00065350 */
                out[0]=0; out[1]=s; out[2]=0; out[3]=0;
                if ((a & 0xffffff) != 0) return;
                out[0]=3; out[3]=3; return;
            }
            out[2]=0; out[3]=0; out[0]=0; out[1]=0; return;
        }
        out[2]=0; out[3]=0; out[0]=0; out[1]=0;
        if ((a & 0x3c) != 4) return;
        out[0]=1; out[1]=b; ((char*)out)[0x19]=2;
    } else {
        if (mode - 0x24 > 1) {
            if (mode != 0x3f) {
                if (mode == 0x3c && obj != 0) {
                    sk_word_t s = sk_exc_special();
                    out[0]=2; out[1]=s; out[2]=0; out[3]=a & 0xffff;
                    return;
                }
                out[2]=0; out[3]=0; out[0]=0; out[1]=0; return;
            }
            if (obj == 0) { out[2]=0; out[3]=0; out[0]=0; out[1]=0; return; }
            sk_word_t s = sk_exc_special();
            out[0]=0; out[1]=s; out[2]=0; out[3]=0;
            if ((a & 0xffffff) != 3) return;
            out[0]=3; ((char*)out)[3]=2; return;
        }
        unsigned int lo = (unsigned)a & 0x3f;
        out[2]=0; out[3]=0; out[0]=0; out[1]=0;
        if (0x11 < lo) return;
        if ((1u << ((unsigned)a & 0x1f) & 0xf0f0u) == 0) {
            if (lo != 0x11) return;
            out[0]=4; out[1]=b; out[3]=(a & 0x40) >> 6;
            return;
        }
        out[0]=1; out[1]=b; ((char*)out)[0x19]=(char)((a & 0x40) >> 6);
    }
    ((unsigned char*)out)[3] = (unsigned char)a & 3;
}

/*--------------------------------------------------------------------*/

/* FUN_00065344 @ 0x65344   (est. sk_exc_16_copy)
 * Ghidra: undefined1[16] FUN_00065344(undefined1(*)[16])
 * Copies the 16-byte exception/context block back to the caller.
 * Confidence: medium
 */
void sk_exc_16_copy(void *dst, const void *src){ sk_memcpy(dst, src, 16); }

/*--------------------------------------------------------------------*/

/* FUN_00065350 @ 0x65350   (est. sk_exc_special)
 * Ghidra: ulong FUN_00065350(void)
 * Fetches a special exception value: seeds the RO frame with a saved context (DAT_004be770), issues CallSupervisor(0), and returns the 64-bit result word read back from the frame; fails through a diagnostic on error.
 * Confidence: low
 * Notes: DAT_004be770/uRam00000000004be778; FUN_00061630; CallSupervisor(0); FUN_004b7ac8.
 */
sk_word_t sk_exc_special(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t prev = sk_obj_field_28(NULL);      /* FUN_00061630 */
    sk_word_t lo = sk_exc_seed_lo;               /* _DAT_004be770 */
    sk_word_t hi = sk_exc_seed_hi;               /* uRam00000000004be778 */
    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
    wr64(tp, lo); wr64(tp+8, hi);
    CallSupervisor(0);
    if ((prev & 0xff) == 0) {
        if (canary != 0xd37afd4bb400012a) sk_stack_fail();
        return rd64(tp + 0x10);
    }
    sk_exc_special_bad(prev);                    /* FUN_004b7ac8 */
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000654e8 @ 0x654e8   (est. sk_error_str_out4)
 * Ghidra: void FUN_000654e8(undefined8,byte)
 * Copies the canonical L4_ErrorCode* string for the given code (0-9); >9 uses a generic fallback.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004be780..; DAT_004be8c0.
 */
void sk_error_str_out4(char *out, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) { sk_memcpy(out, "unknown", 0x20); return; }
    sk_memcpy(out, names[code], 0x20);
}

/*--------------------------------------------------------------------*/

/* FUN_00065620 @ 0x65620   (est. sk_dt_table_set)
 * Ghidra: void FUN_00065620(undefined8)
 * Sets the global device-tree table pointer (DAT_006b2730).
 * Confidence: high
 * Notes: DAT_006b2730.
 */
void sk_dt_table_set(sk_word_t t){ sk_dt_table = t; }

/*--------------------------------------------------------------------*/

/* FUN_0006562c @ 0x6562c   (est. sk_dt_lookup_global)
 * Ghidra: void FUN_0006562c(undefined8,undefined8)
 * Performs a device-tree string lookup against the global table.
 * Confidence: medium
 * Notes: FUN_00065640.
 */
void sk_dt_lookup_global(sk_word_t a, void *b){ sk_dt_lookup((long*)(uintptr_t)sk_dt_table, a, b); }

/*--------------------------------------------------------------------*/

/* FUN_00065640 @ 0x65640   (est. sk_dt_lookup)
 * Ghidra: long FUN_00065640(long*,undefined8,long*)
 * Searches a device-tree table for an entry whose string matches the key: walks the table entries (each a string followed by a value), comparing via the string helper; returns the value pointer (and optionally the stored entry) or 0.
 * Confidence: medium
 * Notes: thunk_FUN_00115080/00114d10.
 */
long sk_dt_lookup(long *tbl, sk_word_t key, long *out)
{
    for (;;) {
        if (tbl == NULL) return 0;
        const char *name = (const char*)(tbl + 2);
        long val = (long)((sk_word_t)name + sk_strlen(name) + 8) & ~7ULL;
        if (sk_strcmp((const char*)name, (const char*)key) == 0) break;  /* thunk_FUN_00114d10 */
        if (tbl[1] == 0) return 0;
        tbl = (long*)((val + *tbl + 7U) & ~7ULL);
    }
    if (out) *out = *tbl;
    return val;
}

/*--------------------------------------------------------------------*/

/* FUN_000656d8 @ 0x656d8   (est. sk_dt_table_set2)
 * Ghidra: void FUN_000656d8(undefined8)
 * Sets the secondary device-tree table pointer (DAT_006b2738).
 * Confidence: high
 * Notes: DAT_006b2738.
 */
void sk_dt_table_set2(sk_word_t t){ sk_dt_table2 = t; }

/*--------------------------------------------------------------------*/

/* FUN_000656e4 @ 0x656e4   (est. sk_dt_lookup_global2)
 * Ghidra: void FUN_000656e4(undefined8,undefined8)
 * Device-tree string lookup against the secondary global table.
 * Confidence: medium
 * Notes: FUN_00065640.
 */
void sk_dt_lookup_global2(sk_word_t a, void *b){ sk_dt_lookup((long*)(uintptr_t)sk_dt_table2, a, b); }

/*--------------------------------------------------------------------*/

/* FUN_000656f8 @ 0x656f8   (est. sk_dt_property_get)
 * Ghidra: undefined8 FUN_000656f8(undefined8*)
 * Fetches a cached device-tree property range: if already loaded it returns the cached base/length; otherwise it validates the property bounds against the device-tree and caches the resolved (base, length) pair, returning success.
 * Confidence: medium
 * Notes: ___DEVICETREE; L4_ErrorCodeOperationInvalid string offset; DAT_006b2740/006b2748/006b2750; FUN_000657ac; SoftwareBreakpoint(0x5519,0x6576c).
 */
sk_word_t sk_dt_property_get(sk_word_t *out)
{
    sk_word_t base = sk_dt_prop_base;            /* _DAT_006b2748 */
    if (sk_dt_prop_ready == 1) {                 /* DAT_006b2740 */
        out[1] = sk_dt_prop_hi;                  /* uRam00000000006b2750 */
        out[0] = base;
        return 1;
    }
    if (sk_dt_prop_size == 0) { sk_word_t lo=0,hi=0; out[0]=lo; out[1]=hi; return 0; }
    sk_word_t lo = 0, hi = 0;
    if ((sk_word_t)(0 + sk_dt_prop_size) < (sk_word_t)0) sk_breakpoint(0x5519, 0x6576c);
    sk_word_t r = sk_dt_parse(0, sk_dt_prop_size, &lo);   /* FUN_000657ac */
    if ((int)r != 0) {
        sk_dt_prop_hi = hi;                      /* uRam00000000006b2750 */
        sk_dt_prop_base = lo;                    /* _DAT_006b2748 */
        sk_dt_prop_ready = 1;
        out[1] = hi;
        out[0] = lo;
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_000657ac @ 0x657ac   (est. sk_dt_parse)
 * Ghidra: void FUN_000657ac(undefined8,undefined8,undefined8*)
 * Parses a device-tree sub-region: looks up the region, and when valid runs the integrity parse callback over it, recording the resulting (base, size) into the output.
 * Confidence: medium
 * Notes: FUN_00065838/000658c4/000658f0.
 */
sk_word_t sk_dt_parse(sk_word_t base, sk_word_t size, sk_word_t *out)
{
    sk_word_t got[2] = {0,0};
    if (sk_dt_lookup_region(base, size, &got) != 0) {   /* FUN_00065838 */
        sk_word_t rec[2] = { got[0], got[1] };
        sk_dt_integrity_parse(got[0], got[1], sk_dt_parse_cb, (sk_word_t)(uintptr_t)&rec);   /* FUN_000658c4 + 000658f0 */
        if (rec[0] == 0x1) {
            out[0] = base;
            out[1] = size;
            return 1;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00065838 @ 0x65838   (est. sk_dt_lookup_region)
 * Ghidra: undefined8 FUN_00065838(undefined8,ulong,undefined8*)
 * Looks up a device-tree region, iterating the node chain and validating that the region size is within bounds; on success records (base, size) into the output.
 * Confidence: medium
 * Notes: FUN_00065a3c/00065ad0/00065af0.
 */
sk_word_t sk_dt_lookup_region(sk_word_t base, sk_word_t size, sk_word_t *out)
{
    sk_word_t ctx[4] = {0,0,0,0};
    sk_word_t r = sk_dt_validate_range(base, size, &ctx);   /* FUN_00065a3c */
    if ((int)r != 0) {
        while (!(sk_dt_next(&ctx) & 1)) sk_dt_walk(&ctx);   /* FUN_00065ad0/00065af0 */
        if (size < ctx[3]) r = 0;
        else { out[0] = base; out[1] = ctx[3]; r = 1; }
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_000658c4 @ 0x658c4   (est. sk_dt_integrity_parse)
 * Ghidra: void FUN_000658c4(undefined8,undefined8)
 * Runs the device-tree integrity parser over the given region, forwarding to the shared parse driver.
 * Confidence: medium
 * Notes: FUN_000660bc.
 */
void sk_dt_integrity_parse(sk_word_t a, sk_word_t b, sk_word_t (*cb)(sk_word_t*, sk_word_t), sk_word_t cbarg)
{
    sk_word_t ctx[2] = { a, b };
    sk_dt_parse_driver(0, ctx, cb, cbarg);               /* FUN_000660bc */
}

/*--------------------------------------------------------------------*/

/* FUN_000658f0 @ 0x658f0   (est. sk_dt_parse_cb)
 * Ghidra: undefined8 FUN_000658f0(ulong*,undefined8)
 * Device-tree integrity-parse callback: validates the parse context (panicking on NULL with 'device_tree_integrity_parse_call'), resolves the child region, and walks the DT node/property entries, checking each node's bounds and advancing the cursor; returns success/failure of the walk.
 * Confidence: medium
 * Notes: Strings s_context____NULL_005be787, s__AppleInternal_Library_BuildRoot_005be68f, s_device_tree_integrity_parse_call_005be797; FUN_00066178/00065e90/00065bc4/00065d98/00065ec0/00066204; DT globals DAT_004be8e0/uRam00000000004be8e8.
 */
sk_word_t sk_dt_parse_cb(sk_word_t *ctx, sk_word_t p2)
{
    if (ctx == NULL)
        sk_panic_dbg(s_context____NULL, s__AppleInternal_Library_BuildRoot, s_device_tree_integrity_parse_call, 0x90);
    sk_word_t base = 0, size = 0;
    sk_word_t r = sk_dt_resolve(p2, 0, &base);      /* FUN_00066178 */
    if (r & 1 && base != 0 && size != 0 && size > 7) {
        sk_word_t dt[2] = { base, size };
        if (*ctx == base) {
            if (base > 0xfffffffffffffff7ULL - 8) sk_dt_fail();   /* FUN_00066204 */
            *ctx = base + 8;
            for (;;) {
                r = sk_dt_eof(dt);                  /* FUN_00065e90 */
                if (r & 1) return 0;
                sk_word_t c0 = 0, c1 = 0;
                int ok = sk_dt_child(dt, &c0, &c1); /* FUN_00065bc4 */
                if (!ok || *ctx != c0) break;
                if (c0 > 0xffffffffffffffdbULL - 0x24) sk_dt_fail();
                *ctx = c0 + 0x24;
                sk_word_t p0 = 0, p1 = 0;
                ok = sk_dt_prop(dt, &p0, &p1);      /* FUN_00065d98 */
                if (!ok || *ctx != p0) break;
                sk_word_t end = (p1 + 3) & ~3ULL;
                if (end + p0 < end) sk_dt_fail();
                *ctx = end + p0;
                sk_dt_advance(dt);                  /* FUN_00065ec0 */
            }
        }
    }
    ((unsigned char*)ctx)[1] = 0;
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00065a3c @ 0x65a3c   (est. sk_dt_validate_range)
 * Ghidra: undefined8 FUN_00065a3c(long,ulong,long*)
 * Validates a device-tree sub-range: confirms the base/size are sane (size > 7), walks the DT nodes, and records the effective (base, size, offset, limit) into the output when the range is within the DT.
 * Confidence: medium
 * Notes: DT globals DAT_004be8e0/uRam00000000004be8e8; FUN_00065e90/00065ec0.
 */
sk_word_t sk_dt_validate_range(long base, sk_word_t size, sk_word_t *out)
{
    if ((base != 0 && size != 0) && size > 7) {
        sk_word_t dt[2] = { (sk_word_t)base, size };
        while (!(sk_dt_eof(&dt) & 1)) sk_dt_advance(&dt);
        if (sk_dt_lim <= size) {   /* uStack_38 = uRam00000000004be8e8 */
            out[0] = base;
            out[1] = size;
            out[2] = 0;
            out[3] = sk_dt_lim;
            return 1;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00065ad0 @ 0x65ad0   (est. sk_dt_next)
 * Ghidra: bool FUN_00065ad0(void)
 * Device-tree iterator 'at end' test: returns true when the DT walk is exhausted.
 * Confidence: medium
 * Notes: FUN_00066030.
 */
bool sk_dt_next(void *ctx){ return sk_dt_walk_end() == 0; }

/*--------------------------------------------------------------------*/

/* FUN_00065af0 @ 0x65af0   (est. sk_dt_walk)
 * Ghidra: undefined8 FUN_00065af0(long)
 * Recursive device-tree walk: resolves the next node, and when valid accumulates its size into the walk context and increments the node counter.
 * Confidence: medium
 * Notes: FUN_00065f48/00065a3c/00065ad0/00066204.
 */
sk_word_t sk_dt_walk(void *ctx)
{
    sk_word_t base = 0, size = 0;
    if (sk_dt_node((sk_word_t)(uintptr_t)ctx, &base) == 0) return 1;    /* FUN_00065f48 */
    sk_word_t c[4] = {0,0,0,0};
    sk_word_t r = sk_dt_validate_range(base, size, &c);
    if ((int)r != 0) {
        while (!(sk_dt_next(&c) & 1)) sk_dt_walk(&c);
        if (c[2] + *(sk_word_t*)((char*)ctx + 0x18) < c[2]) sk_dt_fail();
        *(sk_word_t *)((char*)ctx + 0x18) = c[2] + *(sk_word_t *)((char*)ctx + 0x18);
        if (*(sk_word_t*)((char*)ctx + 0x10) > 0xfffffffffffffffeULL) sk_dt_fail();
        *(sk_word_t *)((char*)ctx + 0x10) += 1;
        r = sk_dt_next(ctx);
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00065b94 @ 0x65b94   (est. sk_dt_node_init)
 * Ghidra: void FUN_00065b94(long,ulong,long*)
 * Initializes a device-tree node record: sets (base, size) and the DT limits into the output.
 * Confidence: medium
 * Notes: DAT_004be8e0/uRam00000000004be8e8.
 */
void sk_dt_node_init(long base, sk_word_t size, long *out)
{
    if ((base != 0 && size != 0) && size > 7) {
        out[0] = base;
        out[1] = size;
        out[3] = sk_dt_lim;   /* lRam00000000004be8e8 */
        out[2] = sk_dt_base;  /* _DAT_004be8e0 */
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00065bc4 @ 0x65bc4   (est. sk_dt_child)
 * Ghidra: bool FUN_00065bc4(undefined8,ulong*,ulong*)
 * Reads the next device-tree child node header: fetches the node address and its name length, returning them (and whether a child is present).
 * Confidence: medium
 * Notes: FUN_00065c30; SoftwareBreakpoint(0x5519,0x65c30).
 */
bool sk_dt_child(sk_word_t *dt, sk_word_t *addr, sk_word_t *len)
{
    sk_word_t node = (sk_word_t)sk_dt_node_hdr(dt);          /* FUN_00065c30 */
    if (node != 0) {
        if ((node + 0x24 < node) || (0x20 < thunk_len(node, 0x20)))
            sk_breakpoint(0x5519, 0x65c30);
        *len = thunk_len(node, 0x20);
        *addr = node;
    }
    return node != 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00065c30 @ 0x65c30   (est. sk_dt_node_hdr)
 * Ghidra: uint* FUN_00065c30(undefined8*)
 * Advances to and returns the next device-tree node header (segment_command-sized 0x24-byte record), bounds-validating the node against the region and its declared size.
 * Confidence: medium
 * Notes: segment_command_00000020; FUN_00066204; SoftwareBreakpoint(0x5519,0x65d10).
 */
unsigned int *sk_dt_node_hdr(sk_word_t *dt)
{
    unsigned int *node = (unsigned int *)*dt;
    if (node != NULL && (sk_word_t)(dt[1]) != 0) {
        if ((sk_word_t)((char*)node + dt[1]) < (sk_word_t)(node + 2) || (sk_word_t)(node+2) < (sk_word_t)node)
            sk_breakpoint(0x5519, 0x65d10);
        if ((sk_word_t)dt[2] < (sk_word_t)*node) {
            sk_word_t off = dt[3];
            if (off > 0xffffffffffffffdbULL) sk_dt_fail();
            if (off + 0x24 <= dt[1]) {
                unsigned int *p = (unsigned int *)((char*)node + off);
                if (p == NULL) {
                    ; /* null node */
                } else if (((sk_word_t)(p+9) < (sk_word_t)p || (sk_word_t)p < (sk_word_t)node)
                    || (sk_word_t)((char*)node + dt[1]) < (sk_word_t)(p + 9)
                    || ((sk_word_t)(dt[1] - off) - 0x24 < ((sk_word_t)p[8] & 0x7fffffff)))
                    sk_breakpoint(0x5519, 0x65d10);
                sk_word_t sz = (unsigned)((int)((sk_word_t)p[8] & 0x7fffffff) + 0x27) & ~3ULL;
                if (sz + off < sz) sk_dt_fail();
                if (p == NULL) return NULL;
                if (dt[1] < sz + off) return NULL;
                if ((sk_word_t)p <= (sk_word_t)(p + 9)) return p;
                sk_breakpoint(0x5519, 0x65d10);
            }
        }
    }
    return NULL;
}

/*--------------------------------------------------------------------*/

/* FUN_00065d18 @ 0x65d18   (est. sk_dt_name_cmp)
 * Ghidra: ulong FUN_00065d18(void)
 * Compares the current device-tree node name against a caller-provided name string, returning whether they match.
 * Confidence: medium
 * Notes: FUN_00066210/00065bc4.
 */
sk_word_t sk_dt_name_cmp(void)
{
    sk_dt_begin();                                /* FUN_00066210 */
    sk_word_t dt[2] = { 0, 0 }, c0 = 0, c1 = 0;
    sk_word_t r = sk_dt_child(dt, &c0, &c1);      /* FUN_00065bc4 */
    if ((int)r != 0) {
        const char *a = (const char*)unaff_x19;
        const char *b = (const char*)local_30;
        sk_word_t i = 0;
        while (a[i] != ' ' && i < uStack_28) {
            if (a[i] != b[i]) return 0;
            i++;
        }
        return b[i] == ' ';
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00065d98 @ 0x65d98   (est. sk_dt_prop)
 * Ghidra: bool FUN_00065d98(undefined8,ulong*,ulong*)
 * Reads the current device-tree node's property list: returns the property data pointer (node + 0x24) and its length (masked to 31 bits).
 * Confidence: medium
 * Notes: FUN_00065c30; SoftwareBreakpoint(0x5519,0x65dec).
 */
bool sk_dt_prop(sk_word_t *dt, sk_word_t *ptr, sk_word_t *len)
{
    sk_word_t node = (sk_word_t)sk_dt_node_hdr(dt);
    if (node != 0) {
        if (node + 0x24 < node) sk_breakpoint(0x5519, 0x65dec);
        unsigned int l = *(unsigned int *)(node + 0x20);
        *ptr = node + 0x24;
        *len = (sk_word_t)l & 0x7fffffff;
    }
    return node != 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00065dec @ 0x65dec   (est. sk_dt_prop_lookup)
 * Ghidra: undefined8 FUN_00065dec(long,ulong,undefined8,undefined8,undefined8)
 * Searches the device-tree nodes for one whose name matches, then returns its property data and length.
 * Confidence: medium
 * Notes: DT walk helpers FUN_00065e90/00065d18/00065d98/00065ec0.
 */
sk_word_t sk_dt_prop_lookup(long base, sk_word_t size, const char *name, sk_word_t *ptr, sk_word_t *len)
{
    if ((base != 0 && size != 0) && size > 7) {
        sk_word_t dt[4] = { (sk_word_t)base, size, 0, sk_dt_lim };
        while (!(sk_dt_eof(&dt) & 1)) {
            if (sk_dt_node_name_is(&dt, name) != 0)     /* FUN_00065d18 */
                return sk_dt_prop(&dt, ptr, len);
            sk_dt_advance(&dt);
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00065e90 @ 0x65e90   (est. sk_dt_eof)
 * Ghidra: bool FUN_00065e90(void)
 * Device-tree 'end of nodes' test: true when there are no more node headers.
 * Confidence: medium
 * Notes: FUN_00065c30; SoftwareBreakpoint(0x5519,0x65ec0).
 */
bool sk_dt_eof(sk_word_t *dt)
{
    sk_word_t node = (sk_word_t)sk_dt_node_hdr(dt);
    if (node <= node + 0x24) return node == 0;
    sk_breakpoint(0x5519, 0x65ec0);
}

/*--------------------------------------------------------------------*/

/* FUN_00065ec0 @ 0x65ec0   (est. sk_dt_advance)
 * Ghidra: undefined8 FUN_00065ec0(long)
 * Advances the device-tree walk past the current node: adds the node's padded size to the cursor and increments the node counter, returning 'at end'.
 * Confidence: medium
 * Notes: FUN_00065c30/00065e90/00066204; SoftwareBreakpoint(0x5519,0x65f40).
 */
sk_word_t sk_dt_advance(sk_word_t *dt)
{
    sk_word_t node = (sk_word_t)sk_dt_node_hdr(dt);
    if (node == 0) return 1;
    if (node + 0x24 < node) sk_breakpoint(0x5519, 0x65f40);
    sk_word_t sz = ((*(unsigned int *)(node + 0x20) & 0x7fffffff) + 0x27) & ~3ULL;
    if (dt[3] + sz < dt[3]) sk_dt_fail();
    dt[3] += sz;
    if (*(long *)(dt + 2) != -1) {
        *(long *)(dt + 2) += 1;
        return sk_dt_eof(dt);
    }
    sk_dt_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00065f48 @ 0x65f48   (est. sk_dt_node_children)
 * Ghidra: undefined8 FUN_00065f48(long,ulong*)
 * Iterates a device-tree node's children: validates the child range, walks the sub-nodes, and returns the (base, size) of the children region, panicking on a bad iterator state.
 * Confidence: low
 * Notes: Strings s_iterator_>node_size_>__iterator__005be667, s__AppleInternal_Library_BuildRoot_005be68f, s_device_tree_node_children_iterat_005be75f; FUN_00066030/00065a3c/00065ad0/00065af0; SoftwareBreakpoint(0x5519,0x66030).
 */
sk_word_t sk_dt_node_children(sk_word_t *ctx, sk_word_t *out)
{
    sk_word_t node = sk_dt_cursor(ctx);          /* FUN_00066030 */
    sk_word_t r = 0;
    if (node != 0) {
        sk_word_t sz = *(sk_word_t *)((char*)ctx + 8) - *(sk_word_t *)((char*)ctx + 0x18);
        if (*(sk_word_t *)((char*)ctx + 8) < *(sk_word_t *)((char*)ctx + 0x18))
            sk_panic_dbg(s_iterator_gt_node_size, s__AppleInternal_Library_BuildRoot,
                         s_device_tree_node_children_iterat, 0x239);
        if (node + sz < node) sk_breakpoint(0x5519, 0x66030);
        *out = node;
        out[1] = sz;
        sk_word_t c[4] = {0,0,0,0};
        r = sk_dt_validate_range(node, sz, &c);
        if ((int)r != 0) {
            while (!(sk_dt_next(&c) & 1)) sk_dt_walk(&c);
            if ((sk_word_t)(*(long *)((char*)ctx + 8) - *(long *)((char*)ctx + 0x18)) < c[3])
                r = 0;
            else {
                if (node + c[3] < node) sk_breakpoint(0x5519, 0x66030);
                *out = node;
                out[1] = c[3];
                r = 1;
            }
        }
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00066030 @ 0x66030   (est. sk_dt_cursor)
 * Ghidra: ulong FUN_00066030(ulong*)
 * Returns the current device-tree node pointer, bounds-checked against the region.
 * Confidence: medium
 * Notes: FUN_00066204; SoftwareBreakpoint(0x5519,0x660ac).
 */
sk_word_t sk_dt_cursor(sk_word_t *dt)
{
    sk_word_t base = *dt;
    if (base == 0 || (sk_word_t)(dt[1]) == 0) return 0;
    if (base + dt[1] < base + 8 || base + 8 < base) sk_breakpoint(0x5519, 0x660ac);
    if (dt[2] < (sk_word_t)*(unsigned int *)(base + 4)) {
        sk_word_t off = dt[3];
        if (off > 0xfffffffffffffff7ULL) sk_dt_fail();
        if (off + 8 <= dt[1]) {
            sk_word_t p = base + off;
            if (p == 0) return 0;
            if ((base <= p && p + 8 <= base + dt[1]) && p <= p + 8) return p;
            sk_breakpoint(0x5519, 0x660ac);
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_000660bc @ 0x660bc   (est. sk_dt_parse_driver)
 * Ghidra: ulong FUN_000660bc(undefined8,undefined8*,code*,undefined8)
 * Recursive device-tree walk driver: calls the callback on the current region, then recurses into each child region, invoking the callback on each; returns success/failure.
 * Confidence: low
 * Notes: FUN_00065a3c/00065ad0/00065af0/00065f48.
 */
sk_word_t sk_dt_parse_driver(sk_word_t ctx0, sk_word_t *root, sk_word_t (*cb)(sk_word_t*, sk_word_t), sk_word_t cbarg)
{
    sk_word_t local_40 = ctx0;
    sk_word_t r = cb(&local_40, cbarg);
    if ((r & 1) == 0) {
        sk_word_t c[4] = {0,0,0,0};
        r = sk_dt_validate_range(*root, root[1], &c);
        if ((int)r != 0) {
            unsigned int more;
            while ((more = sk_dt_next(&c)) & 1) ;  /* first check */
            /* iterate children */
            do {
                sk_word_t ch[2] = {0,0};
                r = sk_dt_node_children(&c, &ch);
                if ((int)r == 0) return r;
                r = sk_dt_parse_driver(local_40, &ch, cb, cbarg);
                if ((r & 1) != 0) break;
                sk_dt_walk(&c);
                more = sk_dt_next(&c);
            } while (!(more & 1));
            r = (sk_word_t)(more ^ 1);
        }
    } else {
        r = 1;
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00066178 @ 0x66178   (est. sk_dt_list_get)
 * Ghidra: bool FUN_00066178(long*,ulong,undefined8*)
 * Fetches the value at the given index of a linked device-tree list, returning it via the output.
 * Confidence: medium
 * Notes: FUN_00066204.
 */
bool sk_dt_list_get(sk_word_t *list, sk_word_t idx, sk_word_t *out)
{
    sk_word_t i = 0;
    for (;;) {
        if (list == NULL) return list != NULL;
        if (idx == i) {
            out[0] = *(sk_word_t *)list[1];
            out[1] = ((sk_word_t*)list[1])[1];
            return list != NULL;
        }
        if (i > 0xfffffffffffffffeULL) sk_dt_fail();
        list = (long *)*list;
        i++;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_000661cc @ 0x661cc   (est. sk_dt_list_count)
 * Ghidra: ulong FUN_000661cc(long*)
 * Counts the number of nodes in a linked device-tree list.
 * Confidence: medium
 * Notes: FUN_00066204.
 */
sk_word_t sk_dt_list_count(sk_word_t *list)
{
    sk_word_t n = 0;
    for (;;) {
        if (list == NULL) return n;
        if (n > 0xfffffffffffffffeULL) sk_dt_fail();
        list = (long *)*list;
        n++;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00066204 @ 0x66204   (est. sk_dt_overflow_panic)
 * Ghidra: void FUN_00066204(void)
 * Panics with 'integer overflow' (device-tree parse invariant).
 * Confidence: high
 * Notes: String s_integer_overflow_005bb5bd; no-return FUN_001150e0.
 */
void sk_dt_overflow_panic(void) __attribute__((noreturn))
{
    sk_panic_assert("integer overflow");
}

/*--------------------------------------------------------------------*/

/* FUN_00066210 @ 0x66210   (est. sk_dt_noop)
 * Ghidra: void FUN_00066210(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_dt_noop(void){ }

/*--------------------------------------------------------------------*/

/* FUN_00066224 @ 0x66224   (est. sk_dt_prop_get_fwd)
 * Ghidra: void FUN_00066224(void)
 * Forwarder to 0x656f8 (device-tree property get).
 * Confidence: medium
 */
void sk_dt_prop_get_fwd(void){ sk_dt_property_get(0); }

/*--------------------------------------------------------------------*/

/* FUN_0006623c @ 0x6623c   (est. sk_dt_parse_fwd)
 * Ghidra: void FUN_0006623c(void)
 * Forwarder to 0x657ac (device-tree parse).
 * Confidence: medium
 */
void sk_dt_parse_fwd(void){ sk_dt_parse(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066254 @ 0x66254   (est. sk_dt_lookup_region_fwd)
 * Ghidra: void FUN_00066254(void)
 * Forwarder to 0x65838 (device-tree region lookup).
 * Confidence: medium
 */
void sk_dt_lookup_region_fwd(void){ sk_dt_lookup_region(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006626c @ 0x6626c   (est. sk_dt_integrity_fwd)
 * Ghidra: void FUN_0006626c(void)
 * Forwarder to 0x658c4 (device-tree integrity parse).
 * Confidence: medium
 */
void sk_dt_integrity_fwd(void){ sk_dt_integrity_parse(0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066284 @ 0x66284   (est. sk_dt_list_get_fwd)
 * Ghidra: void FUN_00066284(void)
 * Forwarder to 0x66178 (device-tree list get).
 * Confidence: medium
 */
void sk_dt_list_get_fwd(void){ sk_dt_list_get(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006629c @ 0x6629c   (est. sk_dt_list_count_fwd)
 * Ghidra: ulong FUN_0006629c(long*)
 * Counts the nodes in a linked device-tree list (thunk to 0x661cc).
 * Confidence: medium
 * Notes: thunk_FUN_000661cc; FUN_00066204.
 */
sk_word_t sk_dt_list_count_fwd(sk_word_t *list)
{
    sk_word_t n = 0;
    for (;;) {
        if (list == NULL) return n;
        if (n > 0xfffffffffffffffeULL) sk_dt_overflow_panic();
        list = (long *)*list;
        n++;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_000662a0 @ 0x662a0   (est. sk_dt_prop_lookup_fwd)
 * Ghidra: void FUN_000662a0(void)
 * Forwarder to 0x65dec (device-tree property lookup).
 * Confidence: medium
 */
void sk_dt_prop_lookup_fwd(void){ sk_dt_prop_lookup(0,0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_000662b8 @ 0x662b8   (est. sk_dt_node_init_fwd)
 * Ghidra: void FUN_000662b8(void)
 * Forwarder to 0x65b94 (device-tree node init).
 * Confidence: medium
 */
void sk_dt_node_init_fwd(void){ sk_dt_node_init(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_000662d0 @ 0x662d0   (est. sk_dt_advance_fwd)
 * Ghidra: void FUN_000662d0(void)
 * Forwarder to 0x65ec0 (device-tree advance).
 * Confidence: medium
 */
void sk_dt_advance_fwd(void){ sk_dt_advance(0); }

/*--------------------------------------------------------------------*/

/* FUN_000662e8 @ 0x662e8   (est. sk_dt_eof_fwd)
 * Ghidra: void FUN_000662e8(void)
 * Forwarder to 0x65e90 (device-tree eof test).
 * Confidence: medium
 */
void sk_dt_eof_fwd(void){ sk_dt_eof(0); }

/*--------------------------------------------------------------------*/

/* FUN_00066300 @ 0x66300   (est. sk_dt_child_fwd)
 * Ghidra: void FUN_00066300(void)
 * Forwarder to 0x65bc4 (device-tree child).
 * Confidence: medium
 */
void sk_dt_child_fwd(void){ sk_dt_child(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066318 @ 0x66318   (est. sk_dt_prop_fwd)
 * Ghidra: void FUN_00066318(void)
 * Forwarder to 0x65d98 (device-tree property).
 * Confidence: medium
 */
void sk_dt_prop_fwd(void){ sk_dt_prop(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066330 @ 0x66330   (est. sk_dt_range_fwd)
 * Ghidra: void FUN_00066330(void)
 * Forwarder to 0x65a3c (device-tree range validate).
 * Confidence: medium
 */
void sk_dt_range_fwd(void){ sk_dt_validate_range(0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066348 @ 0x66348   (est. sk_dt_next_fwd)
 * Ghidra: void FUN_00066348(void)
 * Forwarder to 0x65ad0 (device-tree next).
 * Confidence: medium
 */
void sk_dt_next_fwd(void){ sk_dt_next(0); }

/*--------------------------------------------------------------------*/

/* FUN_00066360 @ 0x66360   (est. sk_dt_walk_fwd)
 * Ghidra: void FUN_00066360(void)
 * Forwarder to 0x65af0 (device-tree walk).
 * Confidence: medium
 */
void sk_dt_walk_fwd(void){ sk_dt_walk(0); }

/*--------------------------------------------------------------------*/

/* FUN_00066378 @ 0x66378   (est. sk_dt_children_fwd)
 * Ghidra: void FUN_00066378(void)
 * Forwarder to 0x65f48 (device-tree node children).
 * Confidence: medium
 */
void sk_dt_children_fwd(void){ sk_dt_node_children(0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00066390 @ 0x66390   (est. sk_dt_boot_prop_load)
 * Ghidra: undefined8 FUN_00066390(void)
 * Boot-time device-tree property loader: fetches the global property range, stores it into the boot table, and returns; on failure it faults through a no-return diagnostic.
 * Confidence: low
 * Notes: FUN_0006b2ec/0006b360/000651bc; FUN_00066224; stack canary FUN_0011d7e8.
 */
sk_word_t sk_dt_boot_prop_load(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_dt_boot_enter();                          /* FUN_0006b2ec */
    sk_log1(0);                                  /* FUN_000651bc */
    if (!canary) sk_stack_fail();
    sk_dt_boot_enter();
    sk_word_t out[2] = {0,0};
    sk_word_t r = sk_dt_property_get(&out);
    sk_word_t v0 = (r & 1) == 0 ? 0 : out[0];
    sk_word_t v1 = (r & 1) == 0 ? 0 : out[1];
    sk_dt_boot_store(v0, r, v1);                 /* FUN_0006b360 */
    if ((r & 1) == 0) sk_stack_fail();
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00066424 @ 0x66424   (est. sk_dt_boot_parse)
 * Ghidra: void FUN_00066424(void)
 * Boot-time device-tree parse: computes the region span and runs the DT parser over it, publishing the result.
 * Confidence: low
 * Notes: FUN_0006b2ec/0006623c/000651bc; stack canary FUN_0011d7e8.
 */
void sk_dt_boot_parse(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t *w = sk_dt_boot_enter();         /* FUN_0006b2ec */
    sk_word_t base = w[0];
    if (base == 0) {
        sk_dt_boot_publish();
        return;
    }
    sk_word_t out[2] = {0,0};
    sk_word_t r = sk_dt_parse(base, w[1] - base, &out);
    sk_word_t v0 = (r & 1) == 0 ? 0 : out[0];
    sk_word_t v1 = (r & 1) == 0 ? 0 : out[1];
    sk_dt_boot_publish();               /* FUN_000651bc */
    if ((r & 1) != 0) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006649c @ 0x6649c   (est. sk_dt_boot_lookup)
 * Ghidra: undefined8 FUN_0006649c(void)
 * Boot-time device-tree region lookup: resolves the region and stores the result.
 * Confidence: low
 * Notes: FUN_0006b2ec/00066254/0006b360; stack canary FUN_0011d7e8.
 */
sk_word_t sk_dt_boot_lookup(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t *w = sk_dt_boot_enter();         /* FUN_0006b2ec */
    sk_word_t out[2] = {0,0};
    sk_word_t r = sk_dt_lookup_region(w[0], w[1], &out);
    sk_word_t v0 = (r & 1) == 0 ? 0 : out[0];
    sk_word_t v1 = (r & 1) == 0 ? 0 : out[1];
    sk_dt_boot_store(v0, r, v1);                 /* FUN_0006b360 */
    if ((r & 1) != 0) return 0;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000664f8 @ 0x664f8   (est. sk_dt_paged_call)
 * Ghidra: undefined1 FUN_000664f8(undefined8*,undefined8)
 * Calls a device-tree helper through a function pointer: allocates paged memory for the argument, runs the callback, frees the memory, and returns the result.
 * Confidence: medium
 * Notes: FUN_0036b270/0036b118.
 */
sk_word_t sk_dt_paged_call(sk_word_t *fp, sk_word_t arg)
{
    if (fp != NULL) {
        void (*cb)(sk_word_t*, sk_word_t*) = (void(*)(sk_word_t*,sk_word_t*))fp[0];
        sk_word_t sz = fp[1];
        sk_word_t out = 0;
        void *mem = sk_alloc_pages(sz, 0);       /* FUN_0036b270 */
        cb(&out, &arg);
        sk_free(mem);                            /* FUN_0036b118 */
        return out;
    }
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00066558 @ 0x66558   (est. sk_boot_dt_integrity_check)
 * Ghidra: uint FUN_00066558(undefined8,undefined8,undefined8,undefined8)
 * Boot integrity check over the device tree: allocates two 0x20-byte dispatch objects (tags 0x65c908/0x65c930), wires their method pointers, pages the first object, and runs the DT integrity parse with the callback, then verifies a feature flag; panics (breakpoint 1) on failure.
 * Confidence: low
 * Notes: FUN_0036a940/0036b270/0036b118/003a26e8; callback FUN_00066720; SoftwareBreakpoint(1,0x6667c).
 */
unsigned int sk_boot_dt_integrity_check(void *a, void *b, sk_word_t c, sk_word_t d)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_dt_boot_enter();
    void *o1 = sk_alloc_obj(0x65c908, 0x20, 7);      /* FUN_0036a940 */
    *(void **)((char*)o1 + 0x10) = a;
    *(void **)((char*)o1 + 0x18) = b;
    void *o2 = sk_alloc_obj(0x65c930, 0x20, 7);
    *(void (**)(void))(o2 + 0x10) = (void(*)(void))sk_dt_boot_ok;   /* FUN_00066690 */
    *(long *)((char*)o2 + 0x18) = (long)o1;
    sk_word_t (*cb)(sk_word_t*, sk_word_t) = sk_dt_paged_call;
    sk_alloc_pages((sk_word_t)o1, 0);
    unsigned int r = sk_dt_integrity_parse(c, d, (sk_word_t(*)(sk_word_t*, sk_word_t))sk_dt_boot_cb, (sk_word_t)(uintptr_t)&cb);  /* FUN_0006626c */
    sk_free(o2);
    sk_word_t f = sk_boot_feature(o1, 0x5be7c0, 0xd3, 0x5d, 9, 0);     /* FUN_003a26e8 */
    sk_free(o1);
    if ((f & 1) != 0) sk_breakpoint(1, 0x6667c);
    sk_log1(canary);
    if (canary) return r & 1;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00066690 @ 0x66690   (est. sk_dt_boot_ok)
 * Ghidra: uint FUN_00066690(void)
 * Invokes the method at unaff_x20+0x10 and returns its low bit.
 * Confidence: low
 */
unsigned int sk_dt_boot_ok(void)
{
    return (*(unsigned int(*)(void))(*(void***)unaff_x20[0x10/8]))() & 1;
}

/*--------------------------------------------------------------------*/

/* FUN_000666bc @ 0x666bc   (est. sk_dt_boot_free1)
 * Ghidra: void FUN_000666bc(void)
 * Frees the object at unaff_x20+0x18 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b21c.
 */
void sk_dt_boot_free1(void){ sk_free(*(void**)((char*)unaff_x20 + 0x18)); sk_alloc_teardown(); }

/*--------------------------------------------------------------------*/

/* FUN_000666c0 @ 0x666c0   (est. sk_dt_boot_free2)
 * Ghidra: void FUN_000666c0(void)
 * Frees the object at unaff_x20+0x18 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b21c.
 */
void sk_dt_boot_free2(void){ sk_free(*(void**)((char*)unaff_x20 + 0x18)); sk_alloc_teardown(); }

/*--------------------------------------------------------------------*/

/* FUN_000666e8 @ 0x666e8   (est. sk_dt_boot_cb)
 * Ghidra: void FUN_000666e8(byte*,undefined8*)
 * Device-tree boot callback: invokes the method at unaff_x20+0x10 with the parsed word and stores its low bit into the output byte.
 * Confidence: low
 */
void sk_dt_boot_cb(unsigned char *out, sk_word_t *word)
{
    unsigned int r = (*(unsigned int(*)(sk_word_t))(*(void***)unaff_x20[0x10/8]))(*word);
    *out = r & 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00066720 @ 0x66720   (est. sk_dt_boot_cb2)
 * Ghidra: uint FUN_00066720(void)
 * Forwards to the paged DT call helper and returns its low bit.
 * Confidence: low
 * Notes: FUN_000664f8.
 */
unsigned int sk_dt_boot_cb2(void){ return sk_dt_paged_call(0,0) & 1; }

/*--------------------------------------------------------------------*/

/* FUN_00066724 @ 0x66724   (est. sk_dt_boot_cb3)
 * Ghidra: uint FUN_00066724(void)
 * Forwards to the paged DT call helper and returns its low bit.
 * Confidence: low
 * Notes: FUN_000664f8.
 */
unsigned int sk_dt_boot_cb3(void){ return sk_dt_paged_call(0,0) & 1; }

/*--------------------------------------------------------------------*/

/* FUN_0006673c @ 0x6673c   (est. sk_boot_console_init)
 * Ghidra: undefined8 FUN_0006673c(undefined8,uint)
 * Boot console/device-tree initialization: looks up a DT node, and unless the mode byte is 1 runs the console setup sequence (memory/feature init then publish); returns the resulting console base, breaking if the setup did not complete.
 * Confidence: low
 * Notes: FUN_00066804/0006b374/000668a0/00066950/0006b330; SoftwareBreakpoint(1,0x667bc/0x66804).
 */
sk_word_t sk_boot_console_init(sk_word_t a, unsigned int mode)
{
    sk_word_t r = sk_dt_node_get(&DAT_005c99ee, a);   /* FUN_00066804 */
    if ((mode & 0xff) == 1) return 0;
    sk_console_enter();                          /* FUN_0006b374 */
    sk_console_mem();                            /* FUN_000668a0 */
    sk_console_init();                           /* FUN_00066950 */
    sk_word_t *w = sk_console_state();         /* FUN_0006b330 */
    if (w[1] == 0) sk_breakpoint(1, 0x667bc);
    return w[0];
}

/*--------------------------------------------------------------------*/

/* FUN_00066804 @ 0x66804   (est. sk_dt_node_get)
 * Ghidra: void FUN_00066804(undefined8,undefined8,undefined8)
 * Resolves a device-tree node/range and publishes the resulting (base, size, status) via the log helper; breaks on an inconsistent size.
 * Confidence: low
 * Notes: FUN_0006b2dc/000662a0/000651bc; SoftwareBreakpoint(1,0x66858/0x6689c).
 */
void sk_dt_node_get(sk_word_t key, sk_word_t a, sk_word_t b)
{
    sk_dt_boot_enter2(key);                      /* FUN_0006b2dc */
    sk_word_t base = 0, size = 0;
    sk_word_t ok = sk_dt_prop_lookup(key, b, 0, &base, &size);   /* FUN_000662a0 */
    long v0, v1; sk_word_t st;
    if ((ok & 1) == 0) { v0 = 0; v1 = 0; st = 1; }
    else {
        if (size < 0) sk_breakpoint(1, 0x6689c);
        v0 = base;
        if (size == 0) {
            if (base == 0) { v1 = 0; st = 0; }
        } else if (base == 0) {
            sk_breakpoint(1, 0x66858);
        }
        st = 0;
        v1 = size + base;
    }
    sk_dt_boot_publish();           /* FUN_000651bc */
    if (canary) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000668a0 @ 0x668a0   (est. sk_console_mem)
 * Ghidra: void FUN_000668a0(void)
 * Loads a fixed memory/console register value into the slot at 0x64e010.
 * Confidence: medium
 * Notes: uRam000000000064e010 = 0x910d6108b0000348.
 */
void sk_console_mem(void){ *(volatile sk_word_t*)0x64e010 = 0x910d6108b0000348; }

/*--------------------------------------------------------------------*/

/* FUN_00066950 @ 0x66950   (est. sk_console_init)
 * Ghidra: void FUN_00066950(void)
 * Loads a fixed init value into the slot at 0x64e028.
 * Confidence: medium
 * Notes: uRam000000000064e028 = 0xd42aa320d65f0fff.
 */
void sk_console_init(void){ *(volatile sk_word_t*)0x64e028 = 0xd42aa320d65f0fff; }

/*--------------------------------------------------------------------*/

/* FUN_000669a4 @ 0x669a4   (est. sk_boot_obj_call)
 * Ghidra: void FUN_000669a4(undefined8*)
 * Calls the boot object helper (FUN_0001a1c8) with the caller's word and stores the result.
 * Confidence: low
 * Notes: FUN_0001a1c8.
 */
void sk_boot_obj_call(sk_word_t *out){ *out = sk_boot_obj_helper(*unaff_x20); }

/*--------------------------------------------------------------------*/

/* FUN_000669e8 @ 0x669e8   (est. sk_boot_branch_call)
 * Ghidra: void FUN_000669e8(undefined8,long)
 * Calls the boot helper with an enabled/disabled selector based on the argument, passing the argument when nonzero.
 * Confidence: medium
 * Notes: FUN_00229a3c/thunk_FUN_002298d4.
 */
void sk_boot_branch_call(sk_word_t a, long arg)
{
    if (arg == 0) sk_boot_helper(0);
    else { sk_boot_helper(1); sk_boot_helper2(arg); }
}

/*--------------------------------------------------------------------*/

/* FUN_00066a2c @ 0x66a2c   (est. sk_boot_branch_call_ctx)
 * Ghidra: void FUN_00066a2c(long)
 * Saves the boot context, then performs the conditional boot-helper call and restores the context.
 * Confidence: medium
 * Notes: FUN_001a84f4/00229a3c/002298d4/001a8564.
 */
void sk_boot_branch_call_ctx(long arg)
{
    sk_ctx_save(0);                              /* FUN_001a84f4 */
    sk_boot_branch_call(0, arg);
    sk_ctx_restore();                            /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/

/* FUN_00066aa0 @ 0x66aa0   (est. sk_boot_branch_call_obj)
 * Ghidra: void FUN_00066aa0(void)
 * Saves the boot context, runs the conditional boot-helper call with the object's word, and restores the context.
 * Confidence: low
 * Notes: FUN_001a84f4/000669e8/001a8564.
 */
void sk_boot_branch_call_obj(void)
{
    sk_word_t v = *unaff_x20;
    sk_ctx_save(0);
    sk_boot_branch_call(0, v);
    sk_ctx_restore();
}

/*--------------------------------------------------------------------*/

/* FUN_00066ae4 @ 0x66ae4   (est. sk_panic_report_start)
 * Ghidra: undefined1[16] FUN_00066ae4(undefined8,undefined8)
 * Starts the panic-report sequence: acquires the report lock, runs console init, and prints the 'report iese' header line, then forwards the parameters to the report printer and releases the lock.
 * Confidence: low
 * Notes: String 0x747265706f727020/0xeb00000000736569 = 'report iese'; FUN_0006673c/00069bdc/0006b584/0006b550; thunk_FUN_002acbb8; FUN_003a25d4.
 */
sk_word_t sk_panic_report_start(sk_word_t a, sk_word_t b)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_report_lock(0x12);                        /* FUN_002a4ab4 */
    sk_boot_console_init(a, b);                  /* FUN_0006673c */
    sk_word_t *w = sk_report_state();          /* FUN_0006b584 */
    sk_word_t v = canary ? w[1] : 0xe900000000000029;
    sk_report_emit(w[0], v);                     /* thunk_FUN_002acbb8 */
    sk_report_free(v);                           /* FUN_003a25d4 */
    sk_report_emit(0x202d20, 0xe300000000000000);
    sk_panic_report_body(a, b);                  /* FUN_00069bdc */
    sk_free(0);
    sk_panic_reset();                            /* FUN_0001df60 */
    sk_report_end();                             /* FUN_0006b550 */
    sk_panic_halt();                             /* FUN_001ba7d4 */
    sk_report_emit(0x747265706f727020, 0xeb00000000736569);  /* 'report iese' */
    return 0xe000000000000000;
}

/*--------------------------------------------------------------------*/

/* FUN_00066be4 @ 0x66be4   (est. sk_panic_report_body)
 * Ghidra: void FUN_00066be4(undefined8,undefined*)
 * Full panic-report body printer: initializes the report stream, iterates the device-tree node list printing each node's name/property pair into the report buffer, then emits the assembled 'report iese' record with the node list and its length.
 * Confidence: low
 * Notes: Format templates 0x65cd58/0x65cb50/0x6753a0; DT iter FUN_00067444/0006749c/000675e8; allocators FUN_0036b270/0036b118/0029fa0c; FUN_0006b584/0006b388/002a3e64/002060d4/00066348/00066378/00066360/001b798c; SoftwareBreakpoint(1,0x67438..0x67440); strings '| ', ' +-', '|'.
 */
void sk_panic_report_body(sk_word_t a, void *arg)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_dt_boot_enter();
    sk_word_t n = 0;
    sk_word_t buf[2] = {0, 0xe000000000000000};
    sk_boot_console_init(0, 0);                  /* FUN_0006673c */
    sk_word_t *w = sk_report_state();
    sk_word_t v = canary ? w[1] : 0xe900000000000029;
    sk_report_emit(w[0], v);
    sk_report_free(v);
    void *list = &DAT_00657778;
    sk_panic_iter_begin(&n, a, arg);
    while (!(sk_panic_iter_next(&list), *(char*)&list == 1)) {
        sk_word_t dv[4] = { list[0], list[1], list[2], list[3] };
        sk_word_t sep[2] = { 0x2020207c20, 0xe500000000000000 };   /* '  | ' */
        /* print node name+value via format template 0x65cd58 */
        sk_word_t r = sk_report_buf();            /* FUN_0006b388 */
        sk_format(r, &sep, 0x65cd58, 0x6753a0);   /* FUN_002060d4 */
        sk_report_emit(sep[0], sep[1]);
        sk_report_free(sep[1]);
        /* grow the node list buffer as needed */
        sk_word_t cap = sk_buf_cap(list);         /* FUN_003a261c */
        if ((cap & 1) == 0) {
            sk_buf_free(*(void**)((char*)list + 0x10));
            list = sk_buf_new();                  /* FUN_0006b3e0 */
        }
        sk_word_t len = *(sk_word_t *)((char*)list + 0x10);
        if (*(sk_word_t *)((char*)list + 0x18) >> 1 <= len)
            list = sk_buf_grow(list);             /* FUN_0006b42c + FUN_0006b6d4 + FUN_0006b3e0 */
        *(sk_word_t *)((char*)list + 0x10) = len + 1;
        *(sk_word_t*)((char*)list + 0x20 + len*0x10) = dv[1];
        *(sk_word_t*)((char*)list + 0x28 + len*0x10) = dv[0];
    }
    sk_panic_iter_end(&n, a, arg);
    /* second pass: emit each node's formatted entry with ' +-' separators */
    sk_word_t done = (*(char*)&list == 1);
    void *ln = arg;
    if (done) {
        /* finalize: emit list header + entries */
        sk_report_emit(0x747265706f727020, 0xeb00000000736569);  /* 'report iese' */
        sk_word_t c1 = sk_boot_enter();           /* FUN_00002534 */
        sk_word_t r = sk_report_slot();           /* FUN_0006b2bc */
        sk_word_t r2 = sk_rep2(r);                /* FUN_0006a3cc */
        sk_word_t *wr = sk_report_state2();     /* FUN_0006b680 */
        sk_word_t *out = sk_report_cat(wr[0], wr[1], c1, r2);  /* FUN_001bc440 */
        sk_report_emit(out[0], out[1]);
        sk_report_free(out[1]);
        /* iterate list entries, emit each */
        sk_word_t i = *(sk_word_t *)((char*)list + 0x10);
        sk_word_t *p = (sk_word_t*)((char*)list + 0x58);
        while (i > 1) {
            sk_word_t v0 = p[-1], v1 = p[0];
            sk_word_t sepm[2] = { 0x7c20, 0xe200000000000000 };   /* '| ' */
            sk_report_emit(sepm[0], sepm[1]);
            sk_report_free(sepm[1]);
            sk_word_t *wr2 = sk_report_state2();
            sk_word_t *out2 = sk_report_cat(wr2[0], wr2[1], v0, v1);
            sk_report_emit(out2[0], out2[1]);
            p += 4; i--;
        }
        sk_free(list);
        sk_dt_boot_publish2();
        if (canary) return;
        sk_stack_fail();
        return;
    }
    /* ... (iterative path elided; equivalent to the loop above) ... */
    sk_free(list);
    sk_dt_boot_publish2();
    if (canary) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00067444 @ 0x67444   (est. sk_panic_iter_begin)
 * Ghidra: void FUN_00067444(void)
 * Begins the panic-report device-tree iteration, running the node-init step under the boot context guard.
 * Confidence: low
 * Notes: FUN_0006b2dc/00068700/000662b8; canary FUN_0011d7e8.
 */
void sk_panic_iter_begin(void)
{
    sk_word_t *w = sk_dt_boot_enter3();        /* FUN_0006b2dc */
    if (canary == 0xd37afd4bb400012a)
        sk_dt_iter_init(w[0], w[1], sk_dt_node_init_fwd);  /* FUN_00068700 */
    else sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006749c @ 0x6749c   (est. sk_panic_iter_next)
 * Ghidra: void FUN_0006749c(long*)
 * Advances the panic-report device-tree iterator one node: when already done it emits the end marker; otherwise it reads the next node's name length, data pointer and length, bounds-validating each, and returns the four fields plus a done flag.
 * Confidence: low
 * Notes: DT walk helpers FUN_000662e8/00066300/00066318/000662d0; SoftwareBreakpoint(1,0x675d8..0x675e4).
 */
void sk_panic_iter_next(long *out)
{
    sk_dt_boot_enter();
    if (*(char*)(unaff_x20 + 4) == 1) {          /* already done */
        out[0]=0; out[1]=0; out[2]=0; out[3]=0; ((char*)out)[4]=1; return;
    }
    sk_word_t sv[4] = { unaff_x20[0], unaff_x20[1], unaff_x20[2], unaff_x20[3] };
    if (!(sk_dt_eof(&sv) & 1)) {
        sk_word_t nl = 0, dp = 0;
        if ((sk_dt_child(&sv, &dp, &nl) & 1) == 0) goto done;
        if (nl > 0x1f) sk_breakpoint(1, 0x675d8);
        sk_word_t sz = 0, dl = 0;
        if ((sk_dt_prop(&sv, &sz, &dl) & 1) == 0) goto done;
        if (dp == 0) goto done_empty;
        if (sz == 0) { dp = 0; goto done_empty; }
        sk_word_t nl1 = nl + 1;
        if (nl1 < 0) sk_breakpoint(1, 0x675e0);
        if (dl < 0) sk_breakpoint(1, 0x675e4);
        out[0] = dp; out[1] = nl1; out[2] = sz; out[3] = dl + sz;
        sk_dt_advance(&sv);
        ((char*)out)[4] = 0;
        goto commit;
    }
done:
    out[0]=0; out[2]=0; out[1]=0; out[3]=0; ((char*)out)[4]=1;
    goto commit;
done_empty:
    out[0]=dp; out[2]=0; out[1]=0; out[3]=0; ((char*)out)[4]=1;
commit:
    unaff_x20[0]=sv[0]; unaff_x20[1]=sv[1]; unaff_x20[2]=sv[2]; unaff_x20[3]=sv[3];
    *(char*)(unaff_x20 + 4) = 0;
    sk_dt_boot_publish2();
    if (canary) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000675e8 @ 0x675e8   (est. sk_panic_iter_end)
 * Ghidra: void FUN_000675e8(void)
 * Ends the panic-report device-tree iteration, running the range-validate step under the boot-context guard.
 * Confidence: low
 * Notes: FUN_0006b2dc/00068700/00066330; canary FUN_0011d7e8.
 */
void sk_panic_iter_end(void)
{
    sk_word_t *w = sk_dt_boot_enter3();        /* FUN_0006b2dc */
    if (canary == 0xd37afd4bb400012a)
        sk_dt_iter_init(w[0], w[1], sk_dt_range_fwd);  /* FUN_00068700 */
    else sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00067640 @ 0x67640   (est. sk_dt_iter_next16)
 * Ghidra: undefined1[16] FUN_00067640(void)
 * Advances a device-tree iterator one step, returning the (next, done) pair; when exhausted it returns the done marker.
 * Confidence: low
 * Notes: DT walk FUN_00066348/00066378/00066360; canary FUN_0011d7e8.
 */
sk_word_t sk_dt_iter_next16(void)
{
    sk_dt_boot_enter();
    if (*(char*)(unaff_x20 + 4) == 1) { return (sk_word_t)1; }
    sk_word_t sv[4] = { unaff_x20[0], unaff_x20[1], unaff_x20[2], unaff_x20[3] };
    sk_word_t r = sk_dt_next(&sv);
    if ((r & 1) == 0) {
        sk_word_t p0=0,p1=0;
        if ((sk_dt_node_children(&sv, &p0) & 1) == 0) { p0=0; p1=0; }
        sk_dt_walk(&sv);
        unaff_x20[0]=sv[0]; unaff_x20[1]=sv[1]; unaff_x20[2]=sv[2]; unaff_x20[3]=sv[3];
        *(char*)(unaff_x20+4)=0;
        sk_dt_boot_publish2();
        return p0 | ((sk_word_t)1 << 40);
    }
    sk_dt_boot_publish2();
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_00067704 @ 0x67704   (est. sk_dt_lookup_fatal)
 * Ghidra: void FUN_00067704(undefined8)
 * Device-tree lookup that, on failure, runs the fatal-error path (report lock, 'Fatal error' halt) before breaking.
 * Confidence: low
 * Notes: Strings s_Fatal_error_005accd0, s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0; FUN_00066284/000651bc; SoftwareBreakpoint(1,0x677c4).
 */
void sk_dt_lookup_fatal(sk_word_t key)
{
    sk_dt_boot_enter();
    sk_word_t out[2] = {0,0};
    sk_word_t r = sk_dt_list_get(0, key, &out);
    if ((r & 1) == 0) {
        sk_report_lock(0x16);
        sk_report_free(0xe000000000000000);
        sk_report_end2();
        sk_panic_reset();
        sk_report_end();
        sk_panic_halt();
        sk_report_emit(0, 0);
        sk_report_free(0);
        sk_report_flush();
        sk_breakpoint(1, 0x677c4);
    }
    sk_dt_boot_publish();
    if (canary) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_000677c8 @ 0x677c8   (est. sk_report_word)
 * Ghidra: undefined1[16] FUN_000677c8(ulong)
 * Returns a {value, 0} word pair for the given value.
 * Confidence: medium
 * Notes: thunk_FUN_000661cc.
 */
sk_word_t sk_report_word(sk_word_t v){ return v; }

/*--------------------------------------------------------------------*/

/* FUN_000677f8 @ 0x677f8   (est. sk_report_slot3)
 * Ghidra: void FUN_000677f8(undefined8*,undefined8,undefined8,undefined8)
 * Builds a three-word report record: value from the caller object, zero, and the fourth parameter.
 * Confidence: low
 * Notes: FUN_000677c8.
 */
void sk_report_slot3(sk_word_t *out, sk_word_t a, sk_word_t b, sk_word_t c)
{
    out[0] = sk_report_word(*unaff_x20);
    out[1] = 0;
    out[2] = c;
}

/*--------------------------------------------------------------------*/

/* FUN_00067828 @ 0x67828   (est. sk_get0)
 * Ghidra: undefined8 FUN_00067828(void)
 * Returns 0 (thunk to 0x19850).
 * Confidence: medium
 * Notes: thunk_FUN_00019850.
 */
sk_word_t sk_get0(void){ return 0; }

/*--------------------------------------------------------------------*/

/* FUN_0006782c @ 0x6782c   (est. sk_report_kind2)
 * Ghidra: undefined8 FUN_0006782c(void)
 * Returns the report record kind constant 2.
 * Confidence: high
 */
sk_word_t sk_report_kind2(void){ return 2; }

/*--------------------------------------------------------------------*/

/* FUN_00067850 @ 0x67850   (est. sk_dt_list_copy)
 * Ghidra: ulong FUN_00067850(undefined8*,long,ulong,undefined8)
 * Copies up to `count` entries from a linked device-tree list into the caller's array, recording (list, copied, total) into the output; on a mid-copy failure it runs the fatal 'found no bound' report path.
 * Confidence: low
 * Notes: Strings 0x20666f2074756f20/0xee0073646e756f62 = 'out bound', s_Fatal_error_005accd0; thunk_FUN_000661cc/00066284; SoftwareBreakpoint(1,0x67938).
 */
sk_word_t sk_dt_list_copy(sk_word_t *out, sk_word_t *dst, sk_word_t count, void *list)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t total = sk_dt_list_count(list);
    sk_word_t copied = 0;
    if (dst == 0) copied = 0;
    else {
        if ((long)count < 0) sk_breakpoint(1, 0x67938);
        copied = count;
        if (count != 0) {
            sk_word_t n = 0;
            sk_word_t limit = total & ((long)total >> 0x3f ^ 0xffffffffffffffffULL);
            do {
                if (limit == n) break;
                sk_word_t e[2] = {0,0};
                copied = sk_dt_list_get(list, n, &e);
                if ((copied & 1) == 0) {
                    sk_report_lock(0x16);
                    sk_report_free(0xe000000000000000);
                    sk_panic_reset();
                    sk_panic_halt(0x677880);
                    sk_report_emit(0, 0);
                    sk_report_free(0);
                    sk_report_emit(0x20666f2074756f20, 0xee0073646e756f62); /* 'out bound' */
                    sk_fatal(s_Fatal_error, 0xb, 2, 0x207865646e49, 0xe600000000000000,
                             s_DeviceTreeKit_DeviceTreeKit_swif, 0x21, 2, 0xa6, 0);  /* FUN_001afa84 */
                }
                dst[n*2] = e[0];
                dst[n*2+1] = e[1];
                n++;
                copied = count;
            } while (count != n);
        }
    }
    out[0] = (sk_word_t)list;
    out[1] = copied;
    out[2] = total;
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return copied;
}

/*--------------------------------------------------------------------*/

/* FUN_00067a04 @ 0x67a04   (est. sk_dt_list_copy4)
 * Ghidra: void FUN_00067a04(undefined8,undefined8,undefined8,undefined8)
 * Forwards to the list-copy helper with reordered arguments.
 * Confidence: low
 * Notes: FUN_001b58b0.
 */
void sk_dt_list_copy4(sk_word_t a, sk_word_t b, sk_word_t c, sk_word_t d){ sk_dt_list_copy4x(a, b, d, c); }

/*--------------------------------------------------------------------*/

/* FUN_00067a28 @ 0x67a28   (est. sk_console_tree_print)
 * Ghidra: void FUN_00067a28(undefined8)
 * Prints the device-tree node tree to the console: iterates the node list, resolves each node's DT range and prints it with '/' separators, growing the output buffer as needed.
 * Confidence: low
 * Notes: FUN_00066284/000662a0/0006a374/0006b6f4/001bc440/0006b5c0; strings '/'; SoftwareBreakpoint(1,0x67be4/0x67ca0..0x67d10).
 */
void sk_console_tree_print(sk_word_t list)
{
    sk_dt_boot_enter();
    sk_word_t n = 0;
    sk_word_t sep[2] = { 0x2f, 0xe100000000000000 };   /* '/' */
    void *out = &DAT_00657778;
    sk_console_enter();
    sk_word_t total = sk_dt_list_count(list);
    sk_word_t i = 0;
    for (;;) {
        if ((total & ((long)total >> 0x3f ^ 0xffffffffffffffffULL)) == i) {
            /* finalize: emit '/' + record */
            sk_report_cat(0x2f, 0xe100000000000000, sk_boot_enter(), sk_rep2(sk_report_slot()));
            sk_free(out);
            sk_dt_boot_publish2();
            if (canary) return;
            sk_stack_fail();
        }
        sk_word_t node[2] = {0,0};
        sk_word_t ok = sk_dt_list_get(list, i, &node);
        if ((ok & 1) == 0) {
            sk_report_lock(0x16);
            sk_report_free(0xe000000000000000);
            sk_report_end2(); sk_panic_reset(); sk_report_end(); sk_panic_halt();
            sk_breakpoint(1, 0x67d10);
        }
        sk_word_t name[2] = {0,0};
        ok = sk_dt_prop_lookup(node[0], node[1], &DAT_005c99ee, &name[0], &name[1]);
        sk_word_t rec[2];
        if ((ok & 1) == 0) { rec[0]=0x656d616e206f6e28; rec[1]=0xe900000000000029; }  /* '(name' */
        else {
            if (name[1] < 0) sk_breakpoint(1, 0x67ca0);
            if (name[1] == 0) {
                if (name[0] == 0) {
                    /* empty name: console default */
                    sk_console_init_seq();
                    sk_word_t *w = sk_console_state2();   /* FUN_0006b5c0 */
                    if (w[1] == 0) sk_breakpoint(1, 0x67be4);
                    rec[0]=w[0]; rec[1]=0;
                }
            } else if (name[0] == 0) {
                sk_breakpoint(1, 0x67ca8);
            }
            sk_console_init_seq();
            sk_word_t *w = sk_console_state2();
            if (w[1] == 0) sk_breakpoint(1, 0x67ca4);
            rec[0]=name[0]; rec[1]=name[1];
        }
        sk_word_t len = *(sk_word_t *)((char*)out + 0x10);
        if (*(sk_word_t *)((char*)out + 0x18) >> 1 <= len)
            out = sk_buf_grow(out);
        *(sk_word_t *)((char*)out + 0x10) = len + 1;
        *(sk_word_t*)((char*)out + 0x20 + len*0x10) = rec[0];
        *(sk_word_t*)((char*)out + 0x28 + len*0x10) = rec[1];
        i++;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00067d4c @ 0x67d4c   (est. sk_iter_next_idx)
 * Ghidra: undefined8 FUN_00067d4c(void)
 * Iterator next: when the current index is below the limit, resolves the next entry via 0x67704 and increments the index; otherwise returns 0.
 * Confidence: low
 * Notes: FUN_00067704.
 */
sk_word_t sk_iter_next_idx(void)
{
    long i = unaff_x20[1];
    if (i < (long)unaff_x20[2]) {
        sk_word_t r = sk_dt_lookup_fatal(i, *unaff_x20);
        unaff_x20[1] = i + 1;
        return r;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00067d9c @ 0x67d9c   (est. sk_iter_next_byte)
 * Ghidra: void FUN_00067d9c(undefined1(*)[16],undefined8,undefined8,undefined1)
 * Iterator next producing a 16-byte result plus a byte flag.
 * Confidence: low
 * Notes: FUN_00067d4c.
 */
void sk_iter_next_byte(sk_word_t *out, sk_word_t a, sk_word_t b, unsigned char f)
{
    *out = sk_iter_next_idx();
    ((char*)out)[1] = f;
}

/*--------------------------------------------------------------------*/

/* FUN_00067dc8 @ 0x67dc8   (est. sk_iter_begin_wrap)
 * Ghidra: void FUN_00067dc8(undefined8*)
 * Wraps the panic-iterator begin (0x67444), copying the 5-word iterator state out.
 * Confidence: low
 * Notes: FUN_00067444.
 */
void sk_iter_begin_wrap(sk_word_t *out)
{
    sk_word_t st[5];
    sk_panic_iter_begin(&st[0], *unaff_x20, unaff_x20[1]);
    out[0]=st[0]; out[1]=st[1]; out[2]=st[2]; out[3]=st[3]; ((char*)out)[4]=st[4];
}

/*--------------------------------------------------------------------*/

/* FUN_00067e2c @ 0x67e2c   (est. sk_console_ensure)
 * Ghidra: void FUN_00067e2c(long,long)
 * Ensures the console is initialized: runs the console-init sequence and confirms the console state is present, breaking otherwise.
 * Confidence: low
 * Notes: FUN_0006b374/000668a0/00066950/0006b330; SoftwareBreakpoint(1,0x67e80/0x67ec8/0x67ecc).
 */
void sk_console_ensure(long a, long b)
{
    if (a == 0) {
        sk_console_init_seq();
        if (sk_console_state()[1] == 0) sk_breakpoint(1, 0x67ecc);
    } else {
        if (b < 0) sk_breakpoint(1, 0x67ec8);
        sk_console_init_seq();
        if (sk_console_state()[1] == 0) sk_breakpoint(1, 0x67e80);
    }
}

/*--------------------------------------------------------------------*/

/* FUN_00067edc @ 0x67edc   (est. sk_hex_dump)
 * Ghidra: undefined1[16] FUN_00067edc(undefined8,undefined8,byte*,undefined8**)
 * Formats a byte array as a console hex dump: converts each byte to a hex-digit pair (with '.' for non-printable), accumulates the 8-byte columns into a report record, and emits the formatted '] ... : ...' line with separators.
 * Confidence: low
 * Notes: FUN_00067e2c/0006b630/0006b4ac/00115448/0006b2fc/0006b440/0006b5a0/0006b2bc/0006a3cc/0006b610/001bc440/0006b674/0006b540/0006b700/0006b4c0/0006b528/0006b514/001ebfb0/0006b600; SoftwareBreakpoint(1,0x6866c..0x68678); chars '|', '.', ' ', ']', ':'.
 */
sk_word_t sk_hex_dump(sk_word_t a, sk_word_t b, unsigned char *data, void **limit)
{
    sk_word_t frame = sk_console_ensure(0, 0);
    sk_word_t count;
    void *line;
    if (data == NULL) {
        sk_console_flush();
        line = &DAT_00657778;
    } else {
        count = (sk_word_t)(limit - data);
        if ((sk_word_t)(&__thread_bss.flags) < count) {
            sk_console_flush();
            line = sk_hex_buf();
            sk_hex_line_begin();
            /* first 8 bytes -> hex columns */
            for (int i = 0; i < 8; i++) {
                sk_word_t hv;
                if (sk_isprint(data[i]) == 0) { hv = 0x2e; }  /* '.' */
                else hv = sk_hex_digit(data[i]);
                sk_hex_col(hv);                  /* FUN_0006b2fc + 0006b440 */
                line = sk_hex_push(line, hv);
            }
            sk_hex_emit(0, count, 0);            /* FUN_0006b5a0 */
            sk_hex_col2(count, 0);
            sk_hex_cat(sk_hex_emit2(), count, 0);  /* FUN_0006b610 + 001bc440 */
            /* second 8 bytes */
            for (int i = 0; i < 8; i++) {
                sk_word_t hv;
                if (sk_isprint(data[count-1-i]) == 0) hv = 0x2e;
                else hv = sk_hex_digit(data[count-1-i]);
                sk_hex_col(hv);
                line = sk_hex_push(line, hv);
            }
            sk_hex_emit(0, count, 0);
            sk_hex_cat(sk_hex_emit2(), count, 0);
            sk_hex_emit('|', 0xe100000000000000);   /* '|' */
            /* printable char column */
            for (int i = 0; i < 8; i++) {
                sk_word_t hv = data[i] < 0x10 ? sk_hex_digit(data[i]) : data[i];
                sk_hex_col(hv);
                line = sk_hex_push(line, hv);
            }
            sk_hex_cat(sk_hex_emit2(), count, 0);
            sk_hex_emit(' ', 0xe100000000000000);
            sk_hex_emit(a, b);                    /* trailing pair */
            sk_hex_emit(']', 0xe100000000000000);
            sk_hex_emit(':', 0xe200000000000000);
            sk_hex_emit(a, b);
            sk_hex_done();
            line = count;
        } else {
            sk_console_flush();
            line = &DAT_00657778;
            sk_hex_line_begin();
            sk_word_t idx = 0;
            do {
                sk_word_t hv;
                if (sk_isprint(data[idx]) == 0) hv = 0x2e;
                else hv = sk_hex_digit(data[idx]);
                sk_hex_col(hv);
                line = sk_hex_push(line, hv);
                idx++;
            } while ((void*)idx != limit);
            sk_hex_emit(0, count, 0);
            sk_hex_cat(sk_hex_emit2(), count, 0);
        }
    }
    sk_hex_flush(line);
    return frame;
}

/*--------------------------------------------------------------------*/

/* FUN_0006869c @ 0x6869c   (est. sk_hex_hook_get)
 * Ghidra: code* FUN_0006869c(void)
 * Returns the hex-dump helper function pointer (FUN_0001a1c8).
 * Confidence: low
 * Notes: FUN_0001a1c8.
 */
void *sk_hex_hook_get(void){ return (void*)sk_boot_obj_helper; }

/*--------------------------------------------------------------------*/

/* FUN_000686bc @ 0x686bc   (est. sk_iter_next_wrap)
 * Ghidra: void FUN_000686bc(undefined8*)
 * Wraps the panic-iterator next (0x6749c), copying the 5-word iterator state out.
 * Confidence: low
 * Notes: FUN_0006749c.
 */
void sk_iter_next_wrap(sk_word_t *out)
{
    sk_word_t st[5];
    sk_panic_iter_next(&st[0]);
    out[0]=st[0]; out[1]=st[1]; out[2]=st[2]; out[3]=st[3]; ((char*)out)[4]=st[4];
}

/*--------------------------------------------------------------------*/

/* FUN_00068700 @ 0x68700   (est. sk_dt_iter_cb)
 * Ghidra: void FUN_00068700(undefined8*)
 * Device-tree iteration callback: runs the supplied DT callback over the boot context and copies the (masked) result word-pair into the output, plus a done flag.
 * Confidence: low
 * Notes: FUN_0006b2ec/000651bc; indirect call via extraout_x9.
 */
void sk_dt_iter_cb(sk_word_t *out)
{
    sk_word_t ctx[4] = {0,0,0,0};
    sk_word_t r = (*(sk_word_t(*)(sk_word_t,sk_word_t,sk_word_t*))dt_cb)(sk_boot_enter(), 0, &ctx);
    sk_word_t done = (r & 1) == 0;
    sk_word_t mask = done ? 0 : ~0ULL;
    out[0] = ctx[0] & mask;
    out[1] = ctx[1] & mask;
    out[2] = ctx[2] & mask;
    out[3] = ctx[3] & mask;
    ((char*)out)[4] = (r ^ 0xff) & 1;
    sk_dt_boot_publish2();
    if (done) return;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00068780 @ 0x68780   (est. sk_iter_end_wrap)
 * Ghidra: void FUN_00068780(undefined8*)
 * Wraps the panic-iterator end (0x675e8), copying the iterator state out.
 * Confidence: low
 * Notes: FUN_000675e8.
 */
void sk_iter_end_wrap(sk_word_t *out)
{
    sk_word_t st[5];
    sk_panic_iter_end(&st[0], *unaff_x20, unaff_x20[1]);
    out[0]=st[0]; out[1]=st[1]; out[2]=st[2]; out[3]=st[3]; ((char*)out)[4]=st[4];
}

/*--------------------------------------------------------------------*/

/* FUN_00068800 @ 0x68800   (est. sk_iter_next16_wrap)
 * Ghidra: void FUN_00068800(undefined1(*)[16],undefined8,undefined8,undefined1)
 * Wraps the 16-byte iterator next (0x67640) with a trailing byte flag.
 * Confidence: low
 * Notes: FUN_00067640.
 */
void sk_iter_next16_wrap(sk_word_t *out, sk_word_t a, sk_word_t b, unsigned char f)
{
    *out = sk_dt_iter_next16();
    ((char*)out)[1] = f;
}

/*--------------------------------------------------------------------*/

/* FUN_00068838 @ 0x68838   (est. sk_hex_nibble1)
 * Ghidra: void FUN_00068838(void)
 * Calls the hex nibble helper with the caller's byte.
 * Confidence: low
 * Notes: FUN_0001cba4.
 */
void sk_hex_nibble1(void){ sk_hex_nibble(*unaff_x20); }

/*--------------------------------------------------------------------*/

/* FUN_0006883c @ 0x6883c   (est. sk_hex_nibble2)
 * Ghidra: void FUN_0006883c(void)
 * Calls the hex nibble helper with the caller's byte.
 * Confidence: low
 * Notes: FUN_0001cba4.
 */
void sk_hex_nibble2(void){ sk_hex_nibble(*unaff_x20); }

/*--------------------------------------------------------------------*/

/* FUN_0006887c @ 0x6887c   (est. sk_hex_digit)
 * Ghidra: void FUN_0006887c(undefined1)
 * Converts a byte to its hex digit via the shared formatter.
 * Confidence: low
 * Notes: FUN_00369efc.
 */
void sk_hex_digit2(unsigned char c){ sk_hex_fmt(&c, 0x65d290, &DAT_004bee78); }

/*--------------------------------------------------------------------*/

/* FUN_000688cc @ 0x688cc   (est. sk_console_tree_dump)
 * Ghidra: undefined1[16] FUN_000688cc(void)
 * Recursively dumps the device-tree node tree to the console: iterates nodes, copying each node's name string into a buffer and collecting the resulting report records, recursing into children; returns the collected record count and buffer.
 * Confidence: low
 * Notes: FUN_00067444/0006749c/000675e8/0006b48c/000668a0/00066950/0006b5e0/0006b2ec/0006a468/0006b42c/0006b6a0/000695e4/001fac04/00002534/00117cc4/00068c40; DAT_00657778/00657788/00657790/00657798; SoftwareBreakpoint(1,0x68c30..0x68c3c).
 */
sk_word_t sk_console_tree_dump(void)
{
    sk_dt_boot_enter();
    sk_panic_iter_begin(0);
    void *list = &DAT_00657778;
    while (!(sk_panic_iter_next(&list), *(char*)&list == 1)) {
        sk_word_t base = list[0];
        sk_word_t size = list[2];
        sk_word_t name[2];
        if (base == 0) {
            name[0]=0; name[1]=0;
            sk_console_init3();
            if (sk_console_state3()[1] == 0) sk_breakpoint(1, 0x68c3c);
        } else {
            if (size < 0) sk_breakpoint(1, 0x68c30);
            name[0]=base; name[1]=size;
            sk_console_init3();
            if (sk_console_state3()[1] == 0) sk_breakpoint(1, 0x68c38);
        }
        void *str = &DAT_00657778;
        if (name[1] != 0 && name[1] - (long)name[0] != 0) {
            /* copy the name string */
            sk_word_t len = name[1];
            str = sk_alloc_obj(sk_boot_enter(), len + 0x20, 7);   /* FUN_0036a940 */
            long extra = sk_len2();                              /* thunk_FUN_000126e8 */
            *(long *)((char*)str + 0x10) = len;
            *(long *)((char*)str + 0x18) = extra*2 - 0x40;
            sk_memcpy((char*)str + 0x20, (void*)name[0], len);   /* FUN_00117cc4 */
        }
        sk_word_t cap = sk_buf_cap(list);
        if ((cap & 1) == 0) {
            sk_buf_free(*(void**)((char*)list + 0x10));
            list = sk_buf_new();
        }
        sk_word_t cnt = *(sk_word_t *)((char*)list + 0x10);
        if (*(sk_word_t *)((char*)list + 0x18) >> 1 <= cnt)
            list = sk_buf_grow(list);
        *(sk_word_t *)((char*)list + 0x10) = cnt + 1;
        *(void **)((char*)list + 0x20 + cnt*0x18) = name;
        *(void **)((char*)list + 0x30 + cnt*0x18) = str;
    }
    sk_word_t count = sk_console_collect(list);   /* FUN_00068c40 */
    sk_console_init4(0,0,0);                       /* FUN_0006a468 */
    sk_panic_iter_end(0);
    if (*(char*)&list == 1) {
        /* recurse into children */
        while (!(sk_dt_next(&list) & 1)) {
            sk_word_t ch[2] = {0,0};
            if ((sk_dt_node_children(&list, &ch) & 1) == 0) break;
            sk_dt_walk(&list);
            sk_word_t rec = sk_console_tree_dump();   /* recursion */
            if (rec == 0) {
                sk_free(&DAT_00657778);
                sk_report_free(count);
                count = 0;
                break;
            }
            sk_word_t idx = DAT_00657788;
            if (DAT_00657790 >> 1 <= DAT_00657788)
                sk_console_grow(idx + 1);
            DAT_00657788 = idx + 1;
            *(sk_word_t*)(0x6798 + idx*2) = rec;
        }
    }
    sk_dt_boot_publish2();
    if (*(char*)&list == 1) return count;
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_00068c40 @ 0x68c40   (est. sk_console_collect)
 * Ghidra: void FUN_00068c40(long)
 * Collects the console node records: allocates (or reuses) the node-name table for the recorded count, then stores it into the global report list.
 * Confidence: low
 * Notes: FUN_00002534/001fac04/0006abac.
 */
void sk_console_collect(long list)
{
    long n = *(long *)((char*)list + 0x10);
    sk_word_t *tbl;
    if (n == 0) tbl = &DAT_00657798;
    else {
        sk_word_t key = sk_boot_enter();
        tbl = (sk_word_t *)sk_alloc_names(n, key);   /* FUN_001fac04 */
    }
    sk_console_names(list, 1, &tbl);               /* FUN_0006abac */
    if (unaff_x21 != 0) sk_free(tbl);
}

/*--------------------------------------------------------------------*/

/* FUN_00068cd0 @ 0x68cd0   (est. sk_report_type)
 * Ghidra: undefined4 FUN_00068cd0(long,long)
 * Classifies a report record by its (lo,hi) magic: returns 0 for the 'report iese' record, 1 for the 'childrend' record, and 2 for an unknown record.
 * Confidence: high
 * Notes: 0x69747265706f7270 = 'report iese', 0x6e6572646c696863 = 'childrend'; FUN_002a0cf8/003a25d4.
 */
unsigned int sk_report_type(sk_word_t lo, sk_word_t hi)
{
    if ((lo == 0x69747265706f7270 && hi == (sk_word_t)-0x15ffffffffff8c9b)
        || (sk_cmp_tag(0x69747265706f7270, 0xea00000000007365, lo, hi, 0) & 1)) {
        sk_report_free(hi);
        return 0;
    }
    if (lo == 0x6e6572646c696863 && hi == (sk_word_t)-0x1800000000000000) {
        sk_report_free(hi);
        return 1;
    }
    sk_word_t r = sk_cmp_tag(0x6e6572646c696863, 0xe800000000000000, lo, hi, 0);
    sk_report_free(hi);
    return (r & 1) ? 1 : 2;
}

/*--------------------------------------------------------------------*/

/* FUN_00068de8 @ 0x68de8   (est. sk_report_type_byte)
 * Ghidra: void FUN_00068de8(undefined1*)
 * Stores the report-record type classification into a byte.
 * Confidence: low
 * Notes: FUN_00068cd0.
 */
void sk_report_type_byte(unsigned char *out){ *out = sk_report_type(0,0); }

/*--------------------------------------------------------------------*/

/* FUN_00068e14 @ 0x68e14   (est. sk_report_end_val)
 * Ghidra: undefined1[16] FUN_00068e14(void)
 * Returns the report end-marker value (1 in the high word).
 * Confidence: high
 */
sk_word_t sk_report_end_val(void){ return (sk_word_t)1 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_00068e4c @ 0x68e4c   (est. sk_report_emit_indirect)
 * Ghidra: void FUN_00068e4c(void)
 * Performs an indirect report emit through the resolved helper, passing the report template and data.
 * Confidence: low
 * Notes: FUN_00027724.
 */
void sk_report_emit_indirect(void)
{
    void (*fp)(sk_word_t, void*) = (void(*)(sk_word_t,void*))sk_boot_obj_helper2(&DAT_004bed40);  /* FUN_00027724 */
    fp(0x65d200, &DAT_004bed40);
}

/*--------------------------------------------------------------------*/

/* FUN_00068eac @ 0x68eac   (est. sk_report_cmp_pair)
 * Ghidra: undefined8 FUN_00068eac(undefined8,undefined8,undefined8,undefined8)
 * Compares two report records: first validates the first pair via 0x68ef8, then the second via 0x690f0, returning success only if both match.
 * Confidence: low
 * Notes: FUN_00068ef8/000690f0.
 */
sk_word_t sk_report_cmp_pair(sk_word_t a, sk_word_t b, sk_word_t c, sk_word_t d)
{
    if ((sk_report_cmp(a, c) & 1) != 0)   /* FUN_00068ef8 */
        return sk_report_cmp2(b, d);      /* FUN_000690f0 */
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00068ef8 @ 0x68ef8   (est. sk_report_cmp)
 * Ghidra: undefined8 FUN_00068ef8(long,long)
 * Compares two report records (each a {name,len} pair plus associated data) for equality: walks the records' entry bitmaps (bit-reversed) comparing each entry's key and string payload; returns 1 when all match.
 * Confidence: low
 * Notes: FUN_0006afb4/0006ae9c/0006afec/0036b270/003a25e0/0036b118; bit-reverse walk; SoftwareBreakpoint(1,0x690f0).
 */
sk_word_t sk_report_cmp(long *a, long *b)
{
    if (a == b) return 1;
    if (*(long *)((char*)a + 0x10) != *(long *)((char*)b + 0x10)) return 0;
    sk_word_t ctx[4];
    sk_report_iter_init(&ctx, a);              /* FUN_0006afb4 */
    sk_report_ref(a, 2);                       /* FUN_003a25e0 */
    sk_alloc_pages(b, 0);
    sk_word_t idx = ctx[2], bitmap = ctx[3];
    while (bitmap != 0) {
        /* pop lowest set bit (bit-reversed) -> entry */
        sk_word_t rev = bitrev(bitmap);
        bitmap &= bitmap - 1;
        sk_word_t entry = LZCOUNT(rev) | idx << 6;
        sk_word_t *pe = *(sk_word_t **)(*(long *)(ctx[0] + 0x30) + entry * 0x10);
        sk_word_t v0 = pe[0], v1 = pe[1];
        long other = *(long *)(*(long *)((char*)b + 0x38) + entry * 8);
        sk_word_t w0 = v0, w1 = v1;
        sk_alloc_pages(w1, 0);
        sk_alloc_pages(other, 0);
        sk_word_t *r2 = sk_report_lookup(v0, w1);   /* FUN_0006ae9c */
        sk_report_free(w1);
        if ((r2[1] & 1) == 0) { sk_report_unref(&ctx); break; }
        long other2 = *(long *)(*(long *)((char*)b + 0x38) + r2[0] * 8);
        if (*(long *)((char*)other2 + 0x10) != *(long *)((char*)other + 0x10)) {
            sk_free(other); sk_report_unref(&ctx); break;
        }
        /* compare strings */
        long n = *(long *)((char*)other2 + 0x10);
        if (n != 0 && other2 != other) {
            for (long i = 0x20; i < 0x20 + n; i++)
                if (*(char*)((char*)other2 + i) != *(char*)((char*)other + i)) {
                    sk_alloc_pages(other2,0); sk_report_unref(&ctx); sk_free(other2);
                    sk_free(other); break;
                }
        }
        sk_free(other);
        if (bitmap == 0) break;
    }
    do {
        idx += 1;
        bitmap = *(sk_word_t *)(ctx[1] + idx * 8);
    } while (bitmap == 0);
    sk_report_free(b);
    sk_report_free(a);
    return 1;
}

/*--------------------------------------------------------------------*/

/* FUN_000690f0 @ 0x690f0   (est. sk_report_cmp2)
 * Ghidra: uint FUN_000690f0(long,long)
 * Compares two report record lists element by element (each element a nested pair), recursing into 0x68ef8 for the name half and 0x690f0 for the value half; returns 1 when all elements match.
 * Confidence: low
 * Notes: FUN_00068ef8/0036b270/0036b118/003a25d4.
 */
unsigned int sk_report_cmp2(long *a, long *b)
{
    long n = *(long *)((char*)a + 0x10);
    if (n == *(long *)((char*)b + 0x10)) {
        if (n == 0 || a == b) return 1;
        sk_word_t *pa = (sk_word_t*)((char*)a + 0x28);
        sk_word_t *pb = (sk_word_t*)((char*)b + 0x28);
        while (n-- != 0) {
            sk_word_t a0 = pa[-1], a1 = *pa;
            sk_word_t b0 = pb[-1], b1 = *pb;
            sk_alloc_pages(a0,0); sk_alloc_pages(a1,0); sk_alloc_pages(b0,0); sk_alloc_pages(b1,0);
            if ((sk_report_cmp3(a0, b0) & 1) == 0) {
                sk_free(a1); sk_report_free(a0); sk_free(b1); sk_report_free(b0);
                return 0;
            }
            unsigned int r = sk_report_cmp2(a1, b1);
            sk_free(a1); sk_report_free(a0); sk_free(b1); sk_report_free(b0);
            if ((r & 1) == 0) break;
            pa += 2; pb += 2;
        }
        return 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_00069214 @ 0x69214   (est. sk_report_flush_line)
 * Ghidra: void FUN_00069214(long)
 * Flushes a report line: processes the record's data pointers, emits the report via the indirect callback, and (when the secondary flag is clear) repeats the flush with the alternate path, finally freeing the result.
 * Confidence: low
 * Notes: FUN_0006a4c0/0006a4f0/0006b404/0006b728/0006a520/0006b65c/001bdb28/0006b714/0006a5e4/0036b118/00002534.
 */
void sk_report_flush_line(void *rec)
{
    sk_word_t extra = *(sk_word_t *)((char*)rec + 0x20);
    sk_report_proc(rec, *(void **)((char*)rec + 0x18));   /* FUN_0006a4c0 */
    sk_report_proc2(extra);                               /* FUN_0006a4f0 */
    sk_report_emit2();                                    /* FUN_0006b404 */
    sk_word_t r = sk_report_cb();                         /* indirect extraout_x8 */
    sk_boot_enter();
    sk_report_flush2();                                   /* FUN_0006b728 */
    sk_report_proc3();                                    /* FUN_0006a520 */
    sk_report_lock2();                                    /* FUN_0006b65c */
    sk_panic_halt2();                                     /* FUN_001bdb28 */
    if (unaff_x21 == 0) {
        sk_report_flush3();                               /* FUN_0006b714 */
        sk_report_proc4();                                /* FUN_0006a5e4 */
        sk_report_lock2();
        sk_panic_halt2();
    }
    sk_free(r);
}

/*--------------------------------------------------------------------*/

/* FUN_00069300 @ 0x69300   (est. sk_report_process_rec)
 * Ghidra: undefined1[16] FUN_00069300(long)
 * Processes a report record: runs the record's data through the processing pipeline and returns the (result, status) pair, freeing the intermediate buffer when complete.
 * Confidence: low
 * Notes: FUN_0006a4c0/0006a668/0006b404/0006b728/0006a698/0006b3a4/001bea18/0006b714/0006a7c8/0036b118/000026e8.
 */
sk_word_t sk_report_process_rec(void *rec)
{
    sk_word_t d0 = *(sk_word_t *)((char*)rec + 0x18);
    sk_word_t d1 = *(sk_word_t *)((char*)rec + 0x20);
    sk_report_proc(rec, d0);
    sk_report_proc5(d1);                                   /* FUN_0006a668 */
    sk_report_emit2();
    sk_word_t r = sk_report_cb();
    if (unaff_x21 == 0) {
        sk_word_t a = sk_report_flush2();
        sk_report_proc6();                                 /* FUN_0006a698 */
        sk_report_lock3();                                 /* FUN_0006b3a4 */
        sk_report_cat2(a, 0, r);                           /* FUN_001bea18 */
        sk_word_t b = sk_report_flush3();
        sk_report_proc7();                                 /* FUN_0006a7c8 */
        sk_report_lock3();
        sk_report_cat2(b, 0, r);
        sk_free(r);
        sk_report_finish(rec);                             /* FUN_000026e8 */
        return (sk_word_t)unaff_x21 << 40 | (sk_word_t)local_38;
    }
    sk_report_finish(rec);
    local_38 = d0;
    return (sk_word_t)unaff_x21 << 40 | (sk_word_t)local_38;
}

/*--------------------------------------------------------------------*/

/* FUN_00069428 @ 0x69428   (est. sk_report_process_wrap)
 * Ghidra: void FUN_00069428(undefined1(*)[16])
 * Wraps the report record processing, storing the result pair when complete.
 * Confidence: low
 * Notes: FUN_00069300.
 */
void sk_report_process_wrap(sk_word_t *out)
{
    sk_word_t r = sk_report_process_rec(0);
    if (unaff_x21 == 0) *out = r;
}

/*--------------------------------------------------------------------*/

/* FUN_00069454 @ 0x69454   (est. sk_report_flush_line2)
 * Ghidra: void FUN_00069454(undefined8)
 * Wraps 0x69214 with the caller-object arguments.
 * Confidence: low
 * Notes: FUN_00069214.
 */
void sk_report_flush_line2(sk_word_t a){ sk_report_flush_line(a); }

/*--------------------------------------------------------------------*/

/* FUN_00069458 @ 0x69458   (est. sk_report_flush_line3)
 * Ghidra: void FUN_00069458(undefined8)
 * Wraps 0x69214 with the caller-object arguments.
 * Confidence: low
 * Notes: FUN_00069214.
 */
void sk_report_flush_line3(sk_word_t a){ sk_report_flush_line(a); }

/*--------------------------------------------------------------------*/

/* FUN_00069470 @ 0x69470   (est. sk_buf_alloc20)
 * Ghidra: undefined* FUN_00069470(long,long)
 * Allocates a report buffer holding `max(count, min)` 0x20-byte records (plus a 0x20-byte header), recording the count and capacity.
 * Confidence: low
 * Notes: FUN_00002534/0036a940/000126e8.
 */
void *sk_buf_alloc20(long min, long count)
{
    if (count <= min) count = min;
    if (count == 0) return &DAT_00657778;
    sk_word_t key = sk_boot_enter();
    void *b = sk_alloc_obj(key, count*0x20 + 0x20, 7);     /* FUN_0036a940 */
    long sz = sk_len2();
    *(long *)((char*)b + 0x10) = min;
    *(long *)((char*)b + 0x18) = (sz - 0x20) / 0x20 << 1;
    return b;
}

/*--------------------------------------------------------------------*/

/* FUN_000694ec @ 0x694ec   (est. sk_buf_alloc10)
 * Ghidra: undefined* FUN_000694ec(long,long,undefined8,undefined8)
 * Allocates a report buffer holding `max(count, min)` 0x10-byte records, recording count and capacity.
 * Confidence: low
 * Notes: FUN_00002534/0036a940/000126e8.
 */
void *sk_buf_alloc10(long min, long count, sk_word_t key, sk_word_t tag)
{
    if (count <= min) count = min;
    if (count == 0) return &DAT_00657778;
    void *b = sk_alloc_obj(sk_boot_enter(), count*0x10 + 0x20, 7);
    long sz = sk_len2();
    *(long *)((char*)b + 0x10) = min;
    *(long *)((char*)b + 0x18) = (sz - 0x20) / 0x10 << 1;
    return b;
}

/*--------------------------------------------------------------------*/

/* FUN_00069560 @ 0x69560   (est. sk_buf_alloc18)
 * Ghidra: undefined* FUN_00069560(long,long)
 * Allocates a report buffer holding `max(count, min)` 0x18-byte records, recording count and capacity.
 * Confidence: low
 * Notes: FUN_00002534/0036a940/000126e8.
 */
void *sk_buf_alloc18(long min, long count)
{
    if (count <= min) count = min;
    if (count == 0) return &DAT_00657778;
    void *b = sk_alloc_obj(sk_boot_enter(), count*0x18 + 0x20, 7);
    long sz = sk_len2();
    *(long *)((char*)b + 0x10) = min;
    *(long *)((char*)b + 0x18) = (sz - 0x20) / 0x18 << 1;
    return b;
}

/*--------------------------------------------------------------------*/

/* FUN_000695e4 @ 0x695e4   (est. sk_buf_resize)
 * Ghidra: long FUN_000695e4(ulong,ulong,ulong,long,code*,code*,code*)
 * Resizes a report buffer: computes the new capacity (doubling when the grow flag is set and the current capacity is too small), reallocates via the supplied grow callback, and either frees the old buffer (free path) or moves its data into the new buffer (move path).
 * Confidence: low
 * Notes: Indirect callbacks; FUN_0006b6e0/0036b118; SoftwareBreakpoint(1,0x696a8).
 */
long sk_buf_resize(sk_word_t mode, sk_word_t need, sk_word_t grow, long buf,
                     void *(*growf)(sk_word_t,sk_word_t), void (*movef)(void*,sk_word_t,long),
                     void (*freef)(void))
{
    sk_word_t cap = need;
    if ((grow & 1) != 0) {
        cap = *(sk_word_t *)((char*)buf + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0) sk_breakpoint(1, 0x696a8);
            cap = *(sk_word_t *)((char*)buf + 0x18) & 0xfffffffffffffffeULL;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    sk_word_t cur = *(sk_word_t *)((char*)buf + 0x10);
    long r = growf(cur, cap);
    if ((mode & 1) == 0) {
        sk_buf_free2();                                 /* FUN_0006b6e0 */
        freef();
    } else {
        movef((char*)buf + 0x20, cur, r + 0x20);
        *(sk_word_t *)((char*)buf + 0x10) = 0;
        sk_free(buf);
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_000696a8 @ 0x696a8   (est. sk_buf_resize10)
 * Ghidra: long FUN_000696a8(ulong,ulong,ulong,long,undefined8,undefined8,code*,code*)
 * Resizes a report buffer using the 0x10-byte-record allocator, either freeing or moving the old buffer.
 * Confidence: low
 * Notes: FUN_000694ec/0006b6e0/0036b118; SoftwareBreakpoint(1,0x69770).
 */
long sk_buf_resize10(sk_word_t mode, sk_word_t need, sk_word_t grow, long buf,
                       sk_word_t key, sk_word_t tag, void (*movef)(void*,sk_word_t,long),
                       void (*freef)(void))
{
    sk_word_t cap = need;
    if ((grow & 1) != 0) {
        cap = *(sk_word_t *)((char*)buf + 0x18) >> 1;
        if ((long)cap < (long)need) {
            if ((long)(cap + 0x4000000000000000) < 0) sk_breakpoint(1, 0x69770);
            cap = *(sk_word_t *)((char*)buf + 0x18) & 0xfffffffffffffffeULL;
            if ((long)cap <= (long)need) cap = need;
        }
    }
    sk_word_t cur = *(sk_word_t *)((char*)buf + 0x10);
    long r = sk_buf_alloc10(cur, cap, key, tag);
    if ((mode & 1) == 0) { sk_buf_free2(); freef(); }
    else {
        movef((char*)buf + 0x20, cur, r + 0x20);
        *(sk_word_t *)((char*)buf + 0x10) = 0;
        sk_free(buf);
    }
    return r;
}

/*--------------------------------------------------------------------*/

/* FUN_00069770 @ 0x69770   (est. sk_buf_copy10)
 * Ghidra: ulong FUN_00069770(long,long,ulong,long)
 * Copies a range of 0x10-byte records from one buffer to another, bounds-checking for overlap, then frees the source buffer.
 * Confidence: low
 * Notes: FUN_0035b67c/0036b118; SoftwareBreakpoint(1,0x697dc..0x697e4).
 */
sk_word_t sk_buf_copy10(long src, long cnt, sk_word_t dst, long srcbuf)
{
    long n = cnt - src;
    if (cnt < src) sk_breakpoint(1, 0x697dc);
    if (n >= 0) {
        sk_word_t from = (sk_word_t)srcbuf + src*0x10 + 0x20;
        sk_word_t to = dst + n*0x10;
        if (to <= from || from + n*0x10 <= dst) {
            sk_buf_memcpy(dst, from, n, 0x6753a0);   /* FUN_0035b67c */
            sk_free(srcbuf);
            return to;
        }
        sk_breakpoint(1, 0x697e4);
    }
    sk_breakpoint(1, 0x697e0);
}

/*--------------------------------------------------------------------*/

/* FUN_000697e4 @ 0x697e4   (est. sk_buf_copy20)
 * Ghidra: ulong FUN_000697e4(long,long,ulong,long)
 * Copies a range of 0x20-byte records between buffers and frees the source.
 * Confidence: low
 * Notes: FUN_0035b67c/0036b118; SoftwareBreakpoint(1,0x69850..0x69858).
 */
sk_word_t sk_buf_copy20(long src, long cnt, sk_word_t dst, long srcbuf)
{
    long n = cnt - src;
    if (cnt < src) sk_breakpoint(1, 0x69850);
    if (n >= 0) {
        sk_word_t from = (sk_word_t)srcbuf + src*0x20 + 0x20;
        sk_word_t to = dst + n*0x20;
        if (to <= from || from + n*0x20 <= dst) {
            sk_buf_memcpy(dst, from, n, 0x675c68);
            sk_free(srcbuf);
            return to;
        }
        sk_breakpoint(1, 0x69858);
    }
    sk_breakpoint(1, 0x69854);
}

/*--------------------------------------------------------------------*/

/* FUN_00069858 @ 0x69858   (est. sk_buf_copy16)
 * Ghidra: ulong FUN_00069858(long,long,ulong,long)
 * Copies a range of 0x10-byte records between buffers and frees the source.
 * Confidence: low
 * Notes: FUN_0035b67c/0036b118; SoftwareBreakpoint(1,0x698c4..0x698cc).
 */
sk_word_t sk_buf_copy16(long src, long cnt, sk_word_t dst, long srcbuf)
{
    long n = cnt - src;
    if (cnt < src) sk_breakpoint(1, 0x698c4);
    if (n >= 0) {
        sk_word_t from = (sk_word_t)srcbuf + src*0x10 + 0x20;
        sk_word_t to = dst + n*0x10;
        if (to <= from || from + n*0x10 <= dst) {
            sk_buf_memcpy(dst, from, n, 0x65cf58);
            sk_free(srcbuf);
            return to;
        }
        sk_breakpoint(1, 0x698cc);
    }
    sk_breakpoint(1, 0x698c8);
}

/*--------------------------------------------------------------------*/

/* FUN_000698cc @ 0x698cc   (est. sk_buf_copy18)
 * Ghidra: ulong FUN_000698cc(long,long,ulong,long)
 * Copies a range of 0x18-byte records between buffers and frees the source.
 * Confidence: low
 * Notes: FUN_0035b67c/0036b118/00002534; SoftwareBreakpoint(1,0x69968..0x69970).
 */
sk_word_t sk_buf_copy18(long src, long cnt, sk_word_t dst, long srcbuf)
{
    long n = cnt - src;
    if (cnt < src) sk_breakpoint(1, 0x69968);
    if (n >= 0) {
        sk_word_t from = (sk_word_t)srcbuf + src*0x18 + 0x20;
        sk_word_t to = dst + n*0x18;
        if (to <= from || from + n*0x18 <= dst) {
            sk_word_t key = sk_boot_enter();
            sk_buf_memcpy(dst, from, n, key);
            sk_free(srcbuf);
            return to;
        }
        sk_breakpoint(1, 0x69970);
    }
    sk_breakpoint(1, 0x6996c);
}

/*--------------------------------------------------------------------*/

/* FUN_00069970 @ 0x69970   (est. sk_buf_memcpy16)
 * Ghidra: void FUN_00069970(ulong,long,ulong)
 * Copies `count` 0x10-byte records from source to destination (memmove semantics), breaking on a negative count.
 * Confidence: medium
 * Notes: FUN_00117d14; SoftwareBreakpoint(1,0x699a4).
 */
void sk_buf_memcpy16(sk_word_t dst, long count, sk_word_t src)
{
    if (count < 0) sk_breakpoint(1, 0x699a4);
    if (src != dst || dst + count*0x10 <= src)
        sk_memmove((void*)dst, (void*)src, count << 4);
}

/*--------------------------------------------------------------------*/

/* FUN_000699a4 @ 0x699a4   (est. sk_buf_memcpy20)
 * Ghidra: void FUN_000699a4(ulong,long,ulong)
 * Copies `count` 0x20-byte records from source to destination (memmove semantics).
 * Confidence: medium
 * Notes: FUN_00117d14; SoftwareBreakpoint(1,0x699d8).
 */
void sk_buf_memcpy20(sk_word_t dst, long count, sk_word_t src)
{
    if (count < 0) sk_breakpoint(1, 0x699d8);
    if (src != dst || dst + count*0x20 <= src)
        sk_memmove((void*)dst, (void*)src, count << 5);
}

/*--------------------------------------------------------------------*/

/* FUN_000699d8 @ 0x699d8   (est. sk_buf_memcpy18)
 * Ghidra: void FUN_000699d8(ulong,long,ulong)
 * Copies `count` 0x18-byte records from source to destination (memmove semantics).
 * Confidence: medium
 * Notes: FUN_00117d14; SoftwareBreakpoint(1,0x69a14).
 */
void sk_buf_memcpy18(sk_word_t dst, long count, sk_word_t src)
{
    if (count < 0) sk_breakpoint(1, 0x69a14);
    if (src != dst || dst + count*0x18 <= src)
        sk_memmove((void*)dst, (void*)src, count * 0x18);
}

/*--------------------------------------------------------------------*/

/* FUN_00069a14 @ 0x69a14   (est. sk_report_nodes16)
 * Ghidra: undefined* FUN_00069a14(void)
 * Builds a report record array from the device-tree nodes: walks the node chain (via the shared DT iterator) collecting each node's (base,size) into a grown 0x10-byte-record buffer, and returns the populated buffer.
 * Confidence: low
 * Notes: FUN_000675e8/00066348/00066378/00066360/0036a940/0036b118/00117d14/00002534; SoftwareBreakpoint(1,0x69bd0..0x69bd8).
 */
void *sk_report_nodes16(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_panic_iter_end(0);
    long idx = 0;
    void *out = &DAT_00657778;
    sk_word_t *dst = &DAT_00657798;
    if (*(char*)&local_90 != 1) {
        while (!(sk_dt_next(&local_b0) & 1)) {
            sk_word_t p0=0, p1=0;
            if ((sk_dt_node_children(&local_b0, &p0) & 1) == 0) break;
            sk_dt_walk(&local_b0);
            void *prev = out;
            if (idx == 0) {
                sk_word_t cap = *(sk_word_t *)((char*)out + 0x18);
                if ((long)((cap>>1) + 0x4000000000000000) < 0) sk_breakpoint(1, 0x69bd4);
                sk_word_t ncap = cap & 0xfffffffffffffffeULL;
                if ((long)cap < 2) ncap = 1;
                out = sk_alloc_obj(sk_boot_enter(), ncap*0x10 + 0x20, 7);
                long sz = sk_len2();
                *(sk_word_t *)((char*)out + 0x10) = ncap;
                *(sk_word_t *)((char*)out + 0x18) = ((sz - 0x20) / 0x10) << 1;
                sk_word_t old = *(sk_word_t *)((char*)prev + 0x18);
                sk_word_t oc = old >> 1;
                if (*(long *)((char*)prev + 0x10) != 0) {
                    if (out != prev || prev + 0x20 + oc*0x10 <= (void*)((char*)out+0x20))
                        sk_memmove((char*)out + 0x20, (char*)prev + 0x20, oc << 4);
                    *(sk_word_t *)((char*)prev + 0x10) = 0;
                }
                dst = (sk_word_t*)((char*)out + 0x20) + oc;
                idx = (((sz - 0x20)/0x10) & 0x7fffffffffffffff) - (old >> 1);
                sk_free(prev);
            }
            if (--idx < 0) sk_breakpoint(1, 0x69bd0);
            dst[0] = p0;
            dst[1] = p1;
            out = prev_after(idx, out);
            dst += 2;
        }
    }
    if (1 < *(sk_word_t *)((char*)out + 0x18)) {
        sk_word_t cap = *(sk_word_t *)((char*)out + 0x18) >> 1;
        if (cap - idx < cap) sk_breakpoint(1, 0x69bd8);
        *(sk_word_t *)((char*)out + 0x10) = cap - idx;
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return out;
}

/*--------------------------------------------------------------------*/

/* FUN_00069bdc @ 0x69bdc   (est. sk_report_nodes20)
 * Ghidra: undefined* FUN_00069bdc(void)
 * Builds a report record array from the device-tree nodes into a grown 0x20-byte-record buffer: each entry holds (name-ptr, name-len+1, data-ptr, data-end), returning the populated buffer.
 * Confidence: low
 * Notes: FUN_00067444/000662e8/00066300/00066318/000662d0/0036a940/0036b118/00117d14/00002534; SoftwareBreakpoint(1,0x69df4..0x69e0c).
 */
void *sk_report_nodes20(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_panic_iter_begin(0);
    long idx = 0;
    void *out = &DAT_00657778;
    long *dst = &DAT_00657798;
    if (*(char*)&local_90 != 1) {
        while (!(sk_dt_eof(&local_b0) & 1)) {
            sk_word_t nl=0, dp=0;
            if ((sk_dt_child(&local_b0, &dp, &nl) & 1) == 0) break;
            if (nl > 0x1f) sk_breakpoint(1, 0x69df4);
            sk_word_t sz=0, dl=0;
            if ((sk_dt_prop(&local_b0, &sz, &dl) & 1) == 0) break;
            if (dp == 0 || sz == 0) break;
            sk_word_t nl1 = nl + 1;
            if (nl1 < 0) sk_breakpoint(1, 0x69dfc);
            if (dl < 0) sk_breakpoint(1, 0x69e00);
            sk_dt_advance(&local_b0);
            void *prev = out;
            if (idx == 0) {
                sk_word_t cap = *(sk_word_t *)((char*)out + 0x18);
                if ((long)((cap>>1) + 0x4000000000000000) < 0) sk_breakpoint(1, 0x69e08);
                sk_word_t ncap = cap & 0xfffffffffffffffeULL;
                if ((long)cap < 2) ncap = 1;
                out = sk_alloc_obj(sk_boot_enter(), ncap*0x20 + 0x20, 7);
                long szz = sk_len2();
                *(sk_word_t *)((char*)out + 0x10) = ncap;
                *(sk_word_t *)((char*)out + 0x18) = ((szz - 0x20) / 0x20) << 1;
                sk_word_t old = *(sk_word_t *)((char*)prev + 0x18);
                sk_word_t oc = old >> 1;
                if (*(long *)((char*)prev + 0x10) != 0) {
                    if (out != prev || prev + 0x20 + oc*0x20 <= (void*)((char*)out+0x20))
                        sk_memmove((char*)out + 0x20, (char*)prev + 0x20, oc << 5);
                    *(sk_word_t *)((char*)prev + 0x10) = 0;
                }
                dst = (long*)((char*)out + 0x20) + oc*2;
                idx = (((szz - 0x20)/0x20) & 0x7fffffffffffffff) - (old >> 1);
                sk_free(prev);
            }
            if (--idx < 0) sk_breakpoint(1, 0x69e04);
            dst[0] = dp; dst[1] = nl1; dst[2] = sz; dst[3] = dl + sz;
            out = prev_after(idx, out);
            dst += 4;
        }
    }
    if (1 < *(sk_word_t *)((char*)out + 0x18)) {
        sk_word_t cap = *(sk_word_t *)((char*)out + 0x18) >> 1;
        if (cap - idx < cap) sk_breakpoint(1, 0x69e0c);
        *(sk_word_t *)((char*)out + 0x10) = cap - idx;
    }
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return out;
}

/*--------------------------------------------------------------------*/

/* FUN_00069e10 @ 0x69e10   (est. sk_report_list16)
 * Ghidra: undefined* FUN_00069e10(undefined8)
 * Builds a report record array from a linked list: iterates the list, resolving each entry into the grown 0x10-byte-record buffer, and returns it; on a mid-iteration failure it runs the fatal 'out bound' report path.
 * Confidence: low
 * Notes: Strings 0x20666f2074756f20/0xee0073646e756f62, s_Fatal_error_005accd0, s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0; thunk_FUN_000661cc/00066284/0036a940/0036b118/00117d14/00002534; SoftwareBreakpoint(1,0x69fac..0x69fb4).
 */
void *sk_report_list16(sk_word_t list)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t total = sk_dt_list_count(list);
    long idx = 0;
    sk_word_t i = 0;
    void *out = &DAT_00657778;
    sk_word_t *dst = &DAT_00657798;
    for (;;) {
        if ((total & ((long)total >> 0x3f ^ 0xffffffffffffffffULL)) == i) {
            if (1 < *(sk_word_t *)((char*)out + 0x18)) {
                sk_word_t cap = *(sk_word_t *)((char*)out + 0x18) >> 1;
                if (cap - idx < cap) sk_breakpoint(1, 0x69fb4);
                *(sk_word_t *)((char*)out + 0x10) = cap - idx;
            }
            if (canary != 0xd37afd4bb400012a) sk_stack_fail();
            return out;
        }
        sk_word_t e[2] = {0,0};
        sk_word_t ok = sk_dt_list_get(list, i, &e);
        if ((ok & 1) == 0) {
            sk_report_lock(0x16);
            sk_report_free(0xe000000000000000);
            sk_panic_reset();
            sk_panic_halt(0x677880);
            sk_report_emit(0, 0);
            sk_report_free(0);
            sk_report_emit(0x20666f2074756f20, 0xee0073646e756f62);
            sk_fatal(s_Fatal_error, 0xb, 2, 0x207865646e49, 0xe600000000000000,
                     s_DeviceTreeKit_DeviceTreeKit_swif, 0x21, 2, 0xa6, 0);
        }
        void *prev = out;
        if (idx == 0) {
            sk_word_t cap = *(sk_word_t *)((char*)out + 0x18);
            if ((long)((cap>>1) + 0x4000000000000000) < 0) sk_breakpoint(1, 0x69fb0);
            sk_word_t ncap = cap & 0xfffffffffffffffeULL;
            if ((long)cap < 2) ncap = 1;
            out = sk_alloc_obj(sk_boot_enter(), ncap*0x10 + 0x20, 7);
            long sz = sk_len2();
            *(sk_word_t *)((char*)out + 0x10) = ncap;
            *(sk_word_t *)((char*)out + 0x18) = ((sz - 0x20) / 0x10) << 1;
            sk_word_t old = *(sk_word_t *)((char*)prev + 0x18);
            sk_word_t oc = old >> 1;
            if (*(long *)((char*)prev + 0x10) != 0) {
                if (out != prev || prev + 0x20 + oc*0x10 <= (void*)((char*)out+0x20))
                    sk_memmove((char*)out + 0x20, (char*)prev + 0x20, oc << 4);
                *(sk_word_t *)((char*)prev + 0x10) = 0;
            }
            dst = (sk_word_t*)((char*)out + 0x20) + oc;
            idx = (((sz - 0x20)/0x10) & 0x7fffffffffffffff) - (old >> 1);
            sk_free(prev);
        }
        if (--idx < 0) sk_breakpoint(1, 0x69fac);
        dst[0] = e[0];
        dst[1] = e[1];
        i++;
        out = prev_after(idx, out);
        dst += 2;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006a078 @ 0x6a078   (est. sk_dt_iter4)
 * Ghidra: long FUN_0006a078(undefined8*,long*,long,undefined8,undefined8)
 * Iterates up to `limit` device-tree nodes, storing each node's (name-ptr, name-len+1, data-ptr, data-end) into the caller's 4-word records, and returns the number consumed; the first word holds the iterator state and done flag.
 * Confidence: low
 * Notes: DT helpers FUN_000662b8/000662e8/00066300/00066318/000662d0; SoftwareBreakpoint(1,0x6a210..0x6a220).
 */
long sk_dt_iter4(sk_word_t *out, long *dst, long limit, sk_word_t a, sk_word_t b)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t st[4] = {0,0,0,0};
    sk_word_t ok = sk_dt_node_init2(a, b, &st);         /* FUN_000662b8 */
    sk_word_t done = ok ^ 1;
    long i = 0;
    if (dst == NULL) limit = 0;
    else {
        if (limit < 0) sk_breakpoint(1, 0x6a220);
        if (limit != 0) {
            long n = 0;
            do {
                if ((done & 1) != 0) { limit = n; goto finish; }
                if (sk_dt_eof(&st) & 1) { done = 0; limit = n; goto finish; }
                sk_word_t nl=0, dp=0;
                if ((sk_dt_child(&st, &dp, &nl) & 1) == 0) goto done_exit;
                if (nl > 0x1f) sk_breakpoint(1, 0x6a210);
                sk_word_t sz=0, dl=0;
                if ((sk_dt_prop(&st, &sz, &dl) & 1) == 0) goto done_exit;
                if (dp == 0 || sz == 0) goto done_exit;
                sk_word_t nl1 = nl + 1;
                if (nl1 < 0) sk_breakpoint(1, 0x6a218);
                if (dl < 0) sk_breakpoint(1, 0x6a21c);
                n++;
                sk_dt_advance(&st);
                done = 0;
                dst[0]=dp; dst[1]=nl1; dst[2]=sz; dst[3]=dl+sz;
                dst += 4;
            } while (limit != n);
            done = 0;
        }
    }
done_exit:
    done = 0;
    limit = i;
finish:
    out[0]=st[0]; out[1]=st[1]; out[2]=st[2]; out[3]=st[3];
    ((char*)out)[4] = (unsigned char)done;
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return limit;
}

/*--------------------------------------------------------------------*/

/* FUN_0006a224 @ 0x6a224   (est. sk_dt_iter2)
 * Ghidra: long FUN_0006a224(undefined8*,undefined8*,long,undefined8,undefined8)
 * Iterates up to `limit` device-tree nodes, storing each node's (base,size) into the caller's 2-word records, returning the count consumed and the iterator state.
 * Confidence: low
 * Notes: DT helpers FUN_00066330/00066348/00066378/00066360; SoftwareBreakpoint(1,0x6a370).
 */
long sk_dt_iter2(sk_word_t *out, sk_word_t *dst, long limit, sk_word_t a, sk_word_t b)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t st[4] = {0,0,0,0};
    sk_word_t ok = sk_dt_validate_range(a, b, &st);     /* FUN_00066330 */
    sk_word_t done = (ok & 1) == 0;
    if (done) { st[0]=0; st[1]=0; st[2]=0; st[3]=0; }
    if (dst == NULL) limit = 0;
    else {
        if (limit < 0) sk_breakpoint(1, 0x6a370);
        if (limit != 0) {
            long n = 0;
            ok ^= 1;
            do {
                if ((ok & 1) != 0) { limit = n; goto fin; }
                if (sk_dt_next(&st) & 1) { done = 0; limit = n; goto fin; }
                sk_word_t p0=0,p1=0;
                if ((sk_dt_node_children(&st, &p0) & 1) == 0) { done = 0; limit = n; goto fin; }
                n++;
                sk_dt_walk(&st);
                ok = 0;
                dst[0]=p0; dst[1]=p1;
                dst += 2;
            } while (limit != n);
            done = 0;
        }
    }
fin:
    out[0]=st[0]; out[1]=st[1]; out[2]=st[2]; out[3]=st[3];
    *(bool*)(out + 4) = done;
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
    return limit;
}

/*--------------------------------------------------------------------*/

/* FUN_0006a374 @ 0x6a374   (est. sk_buf_resize10_wrap)
 * Ghidra: void FUN_0006a374(void)
 * Resizes the report buffer via 0x696a8 and stores the result back.
 * Confidence: low
 * Notes: FUN_000696a8.
 */
void sk_buf_resize10_wrap(void){ *unaff_x20 = sk_buf_resize10(0,0,0,0,0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006a3cc @ 0x6a3cc   (est. sk_cb_init)
 * Ghidra: void FUN_0006a3cc(long*,undefined8,undefined8,undefined8)
 * Initializes a callback slot: resolves the symbol and stores the resolved function pointer if the slot is empty.
 * Confidence: low
 * Notes: FUN_00027614/00376820.
 */
void sk_cb_init(long *slot, sk_word_t a, sk_word_t b, sk_word_t c)
{
    if (*slot == 0) {
        sk_word_t sym = sk_sym_resolve(a, b);     /* FUN_00027614 */
        *slot = sk_cb_bind(c, sym);               /* FUN_00376820 */
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006a414 @ 0x6a414   (est. sk_console_load_e050)
 * Ghidra: void FUN_0006a414(void)
 * Loads a fixed console/memory value into the slot at 0x64e050.
 * Confidence: medium
 * Notes: uRam000000000064e050 = 0xf9462d0890000588.
 */
void sk_console_load_e050(void){ *(volatile sk_word_t*)0x64e050 = 0xf9462d0890000588; }

/*--------------------------------------------------------------------*/

/* FUN_0006a468 @ 0x6a468   (est. sk_buf_resize10_wrap2)
 * Ghidra: void FUN_0006a468(void)
 * Resizes the report buffer via 0x696a8 and stores the result back.
 * Confidence: low
 * Notes: FUN_000696a8.
 */
void sk_buf_resize10_wrap2(void){ *unaff_x20 = sk_buf_resize10(0,0,0,0,0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006a4c0 @ 0x6a4c0   (est. sk_alloc_align_adjust)
 * Ghidra: long* FUN_0006a4c0(long*,long)
 * Adjusts an allocation pointer based on the owning allocation's flags: when the high flag (bit 17) is set, aligns the pointer up by the recorded size.
 * Confidence: low
 * Notes: Reads *(param_2-8)+0x50.
 */
long *sk_alloc_align_adjust(long *p, long alloc)
{
    unsigned int flags = *(unsigned int *)(*(long *)((char*)alloc - 8) + 0x50);
    if ((flags >> 0x11 & 1) != 0) {
        sk_word_t sz = flags & 0xff;
        p = (long *)(*p + (sz + 0x10 & ~sz));
    }
    return p;
}

/*--------------------------------------------------------------------*/

/* FUN_0006a4f0 @ 0x6a4f0   (est. sk_obj_len_field)
 * Ghidra: long FUN_0006a4f0(ulong)
 * Reads an object's length field: follows the tagged pointer (clear low bit), then returns base+0xc + *(int*)(base+0xc).
 * Confidence: low
 */
long sk_obj_len_field(sk_word_t p)
{
    if ((p & 1) != 0) p = *(sk_word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/*--------------------------------------------------------------------*/

/* FUN_0006a520 @ 0x6a520   (est. sk_console_load_e068)
 * Ghidra: void FUN_0006a520(void)
 * Loads a fixed console/memory value into the slot at 0x64e068.
 * Confidence: medium
 * Notes: uRam000000000064e068 = 0xa8c17bfda9000500.
 */
void sk_console_load_e068(void){ *(volatile sk_word_t*)0x64e068 = 0xa8c17bfda9000500; }

/*--------------------------------------------------------------------*/

/* FUN_0006a5e4 @ 0x6a5e4   (est. sk_console_load_e088)
 * Ghidra: void FUN_0006a5e4(void)
 * Loads a fixed console/memory value into the slot at 0x64e088.
 * Confidence: medium
 * Notes: uRam000000000064e088 = 0x90000593910043fd.
 */
void sk_console_load_e088(void){ *(volatile sk_word_t*)0x64e088 = 0x90000593910043fd; }

/*--------------------------------------------------------------------*/

/* FUN_0006a668 @ 0x6a668   (est. sk_obj_len_field2)
 * Ghidra: long FUN_0006a668(ulong)
 * Reads an object's length field (tagged-pointer aware), returning base+0xc + *(int*)(base+0xc).
 * Confidence: low
 */
long sk_obj_len_field2(sk_word_t p)
{
    if ((p & 1) != 0) p = *(sk_word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/*--------------------------------------------------------------------*/

/* FUN_0006a698 @ 0x6a698   (est. sk_console_load_e090)
 * Ghidra: void FUN_0006a698(void)
 * Loads a fixed console/memory value into the slot at 0x64e090.
 * Confidence: medium
 * Notes: uRam000000000064e090 = 0xb5000101f9462e61.
 */
void sk_console_load_e090(void){ *(volatile sk_word_t*)0x64e090 = 0xb5000101f9462e61; }

/*--------------------------------------------------------------------*/

/* FUN_0006a75c @ 0x6a75c   (est. sk_cb_init2)
 * Ghidra: void FUN_0006a75c(long*,undefined8,undefined8)
 * Initializes a callback slot with an additional context word.
 * Confidence: low
 * Notes: FUN_00027614/00376820.
 */
void sk_cb_init2(long *slot, sk_word_t a, sk_word_t c)
{
    if (*slot == 0) {
        sk_word_t sym = sk_sym_resolve(0x64e078, &DAT_005a4b80);
        sk_word_t ctx = a;
        *slot = sk_cb_bind2(c, sym, &ctx);
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006a7c8 @ 0x6a7c8   (est. sk_console_load_e0a0)
 * Ghidra: void FUN_0006a7c8(void)
 * Loads a fixed console/memory value into the slot at 0x64e0a0.
 * Confidence: medium
 * Notes: uRam000000000064e0a0 = 0xd0000321f9400100.
 */
void sk_console_load_e0a0(void){ *(volatile sk_word_t*)0x64e0a0 = 0xd0000321f9400100; }

/*--------------------------------------------------------------------*/

/* FUN_0006a860 @ 0x6a860   (est. sk_console_cb_init)
 * Ghidra: void FUN_0006a860(void)
 * Initializes a console callback slot at 0x64e0a8 with the resolved symbol and a context pointer.
 * Confidence: low
 * Notes: FUN_00027614/00376820; writes to read-only 0x64e0a8.
 */
void sk_console_cb_init(void)
{
    sk_word_t sym = sk_sym_resolve(0x64e0b0, &DAT_004be938);
    sk_word_t ctx = 0x66ee00;
    *(volatile sk_word_t*)0x64e0a8 = sk_cb_bind2(&DAT_004ea504, sym, &ctx);
}

/*--------------------------------------------------------------------*/

/* FUN_0006abac @ 0x6abac   (est. sk_report_build_index)
 * Ghidra: void FUN_0006abac(long,uint,long*)
 * Builds the report hash index: walks the source record array, resolving each key into a slot via the hash lookup, setting the bitmap and key/value slots; on a duplicate key it emits a 'Fatal error' from 'Swift/NativeDictionary.swift'.
 * Confidence: low
 * Notes: Strings s_Fatal_error_005accd0, s_Swift_NativeDictionary_swift_005be800; FUN_0006ae9c/00258c60/0036993c/0036986c/00365b6c/00002534/002591b4; SoftwareBreakpoint(1,0x6adcc..0x6add4).
 */
void sk_report_build_index(void *rec, unsigned int flags, long **index)
{
    sk_word_t i = 0;
    sk_word_t count = *(sk_word_t *)((char*)rec + 0x10);
    sk_word_t *p = (sk_word_t*)((char*)rec + 0x30);
    for (;;) {
        if (count == i) { sk_free(rec); return; }
        if (*(sk_word_t *)((char*)rec + 0x10) <= i) sk_breakpoint(1, 0x6adcc);
        sk_word_t k0 = p[-2], k1 = p[-1];
        sk_word_t v = *p;
        long *tbl = *index;
        sk_alloc_pages(k1, 0);
        sk_alloc_pages(v, 0);
        sk_word_t *r = sk_report_lookup(k0, k1);       /* FUN_0006ae9c */
        sk_word_t slot = r[0];
        long idxlen = *(long *)((char*)tbl + 0x10);
        sk_word_t found = ~r[1] & 1;
        if (idxlen + found < idxlen) sk_breakpoint(1, 0x6add0);
        sk_word_t key = sk_boot_enter();
        sk_word_t ins = sk_hash_insert(flags & 1, idxlen + found, key);  /* FUN_00258c60 */
        if ((ins & 1) != 0) {
            sk_word_t *r2 = sk_report_lookup(k0, k1);
            if ((r[1] & 1) != (r2[1] & 1))
                sk_hash_mismatch(0x6753a0);              /* FUN_002591b4 */
        }
        if ((r[1] & 1) != 0) {
            /* duplicate key -> fatal from NativeDictionary */
            sk_word_t *w = sk_hash_fail2();            /* FUN_0036993c */
            *w[1] = 0;
            sk_hash_fail3();                             /* FUN_0036986c */
            sk_alloc_pages(w[0], 0);
            sk_word_t k2 = sk_boot_enter();
            sk_word_t r3 = sk_hash_emit(k2, &w[0], k2, 0x672fa0, 0);   /* FUN_00365b6c */
            if ((r3 & 1) == 0) {
                sk_free(rec);
                sk_report_free(k1);
                sk_free(v);
                sk_free(w[0]);
                return;
            }
            sk_report_lock(0x1e);
            sk_report_emit(0xd00000000000001b, 0x80000000005be800);
            sk_word_t pair[2] = { k0, k1 };
            sk_format2(&pair, &pair[0], 0x6753a0, 0x6756a8, 0x66e1b8);  /* FUN_00205844 */
            sk_report_emit(0x27, 0xe100000000000000);
            sk_fatal(s_Fatal_error, 0xb, 2, 0, 0xe000000000000000,
                     s_Swift_NativeDictionary_swift, 0x1c, 2, 0x318, 0);
        }
        long *dst = *index;
        long base = *dst;
        *(sk_word_t *)(base + (slot >> 6) * 8) |= 1ULL << (slot & 0x3f);
        sk_word_t *ks = (sk_word_t*)(*(long*)(base + 0x30) + slot*0x10);
        ks[0] = k0; ks[1] = k1;
        *(sk_word_t *)(*(long*)(base + 0x38) + slot*8) = v;
        if (*(long *)(base + 0x10) + 1 < *(long *)(base + 0x10)) sk_breakpoint(1, 0x6add4);
        *(long *)(base + 0x10) += 1;
        p += 3;
        i++;
        flags = 1;
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006ae9c @ 0x6ae9c   (est. sk_report_lookup_ctx)
 * Ghidra: void FUN_0006ae9c(undefined8,undefined8)
 * Looks up a report key with context: saves the current report context, performs the key lookup, then restores the context and returns the result.
 * Confidence: low
 * Notes: FUN_001a84f4/001b9084/001a8564/0006af08.
 */
void sk_report_lookup_ctx(sk_word_t k0, sk_word_t k1)
{
    sk_word_t ctx = *(sk_word_t *)((char*)unaff_x20 + 0x28);
    sk_ctx_save(ctx);
    sk_report_lookup_save(k0, k1);               /* FUN_001b9084 */
    sk_word_t r = sk_ctx_restore();
    sk_report_lookup2(k0, k1, r);                /* FUN_0006af08 */
}

/*--------------------------------------------------------------------*/

/* FUN_0006af08 @ 0x6af08   (est. sk_report_lookup2)
 * Ghidra: undefined1[16] FUN_0006af08(long,long,ulong)
 * Hash lookup in a report index: scans the bitmap from the starting slot (masked to the table's bit width), comparing keys; returns the found slot and whether the key was found.
 * Confidence: low
 * Notes: FUN_002a0cf8.
 */
sk_word_t sk_report_lookup2(long k0, long k1, sk_word_t start)
{
    unsigned char width = *(unsigned char *)((char*)unaff_x20 + 0x20);
    for (;;) {
        start &= ~(-1L << (width & 0x3f));
        sk_word_t bit = 1ULL << (start & 0x3f)
                      & *(sk_word_t *)((char*)unaff_x20 + 0x40 + (start >> 6) * 8);
        if (bit == 0) break;
        long *e = (long*)(*(long*)((char*)unaff_x20 + 0x30) + start * 0x10);
        long a0 = e[0], a1 = e[1];
        if ((a0 == k0 && a1 == k1)
            || (sk_cmp_tag(a0, a1, k0, k1, 0) & 1)) break;
        start += 1;
    }
    return (bit != 0) << 40 | (start & 0xffffffffffffff);
}

/*--------------------------------------------------------------------*/

/* FUN_0006afb4 @ 0x6afb4   (est. sk_report_index_begin)
 * Ghidra: void FUN_0006afb4(long*,long)
 * Initializes a report index iterator: records the table pointer, its data/bitmap bases, the slot bit-width mask, and the first bitmap word.
 * Confidence: low
 */
void sk_report_index_begin(long *out, long idx)
{
    sk_word_t width = *(unsigned char *)((char*)idx + 0x20);
    sk_word_t lowmask = ~(-1L << (width & 0x3f));
    *out = idx;
    sk_word_t bm = *(sk_word_t *)((char*)idx + 0x40);
    sk_word_t neg = -lowmask;
    sk_word_t mask = 0xffffffffffffffffULL;
    if (neg < 0x40) mask = ~(-1L << (neg & 0x3f));
    out[1] = idx + 0x40;
    out[2] = ~lowmask;
    out[3] = 0;
    out[4] = mask & bm;
}

/*--------------------------------------------------------------------*/

/* FUN_0006afec @ 0x6afec   (est. sk_report_index_deinit)
 * Ghidra: undefined8 FUN_0006afec(undefined8)
 * Deinitializes a report index via the resolved symbol's deallocator, then returns the argument.
 * Confidence: low
 * Notes: FUN_00002534; indirect call.
 */
sk_word_t sk_report_index_deinit(sk_word_t idx)
{
    sk_word_t sym = sk_boot_enter();
    (*(void(**)(sk_word_t,sk_word_t))(*(long*)(sym - 8) + 8))(idx, sym);
    return idx;
}

/*--------------------------------------------------------------------*/

/* FUN_0006b1d0 @ 0x6b1d0   (est. sk_dt_list_copy_fwd)
 * Ghidra: void FUN_0006b1d0(void)
 * Forwarder to 0x67a04 (DT list copy).
 * Confidence: medium
 */
void sk_dt_list_copy_fwd(void){ sk_dt_list_copy4(0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006b1d4 @ 0x6b1d4   (est. sk_dt_list_copy_fwd2)
 * Ghidra: void FUN_0006b1d4(void)
 * Forwarder to 0x67a04 (DT list copy).
 * Confidence: medium
 */
void sk_dt_list_copy_fwd2(void){ sk_dt_list_copy4(0,0,0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006b1ec @ 0x6b1ec   (est. sk_dt_boot_prop_wrap)
 * Ghidra: void FUN_0006b1ec(void)
 * Boot-context device-tree property load wrapper: enters the boot context, publishes the result, and runs the property loader.
 * Confidence: low
 * Notes: FUN_0006b2ec/000651bc/00066390; canary FUN_0011d7e8.
 */
void sk_dt_boot_prop_wrap(void)
{
    sk_dt_boot_enter();
    sk_dt_boot_publish2();
    if (canary) { sk_dt_boot_prop_load(); return; }
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006b23c @ 0x6b23c   (est. sk_iter_begin_wrap2)
 * Ghidra: void FUN_0006b23c(void)
 * Boot-context panic-iterator begin wrapper.
 * Confidence: low
 * Notes: FUN_0006b2dc/0006b360/00067444; canary FUN_0011d7e8.
 */
void sk_iter_begin_wrap2(void)
{
    sk_dt_boot_enter2(0);
    sk_dt_boot_store(0,0,0);
    if (canary) { sk_panic_iter_begin(0); return; }
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006b274 @ 0x6b274   (est. sk_iter_end_wrap2)
 * Ghidra: void FUN_0006b274(void)
 * Boot-context panic-iterator end wrapper.
 * Confidence: low
 * Notes: FUN_0006b2dc/0006b360/000675e8; canary FUN_0011d7e8.
 */
void sk_iter_end_wrap2(void)
{
    sk_dt_boot_enter2(0);
    sk_dt_boot_store(0,0,0);
    if (canary) { sk_panic_iter_end(0,0,0); return; }
    sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006b2bc @ 0x6b2bc   (est. sk_report_slot_addr)
 * Ghidra: undefined8 FUN_0006b2bc(void)
 * Returns the report slot base address 0x64e038.
 * Confidence: medium
 */
sk_word_t sk_report_slot_addr(void){ return 0x64e038; }

/*--------------------------------------------------------------------*/

/* FUN_0006b2dc @ 0x6b2dc   (est. sk_noop_6b2dc)
 * Ghidra: void FUN_0006b2dc(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b2dc(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b2ec @ 0x6b2ec   (est. sk_noop_6b2ec)
 * Ghidra: void FUN_0006b2ec(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b2ec(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b2fc @ 0x6b2fc   (est. sk_noop_6b2fc)
 * Ghidra: void FUN_0006b2fc(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b2fc(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b330 @ 0x6b330   (est. sk_console_state4)
 * Ghidra: void FUN_0006b330(void)
 * Reads console state via the shared state reader.
 * Confidence: medium
 * Notes: FUN_001eb088.
 */
void sk_console_state4(void){ sk_console_read_state(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b360 @ 0x6b360   (est. sk_noop_6b360)
 * Ghidra: void FUN_0006b360(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b360(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b374 @ 0x6b374   (est. sk_console_enter2)
 * Ghidra: void FUN_0006b374(void)
 * Resolves the console entry symbol via the boot symbol helper.
 * Confidence: medium
 * Notes: FUN_00002534.
 */
void sk_console_enter2(void){ sk_boot_enter(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b388 @ 0x6b388   (est. sk_report_buf_ptr)
 * Ghidra: undefined1* FUN_0006b388(void)
 * Returns a pointer into the caller's stack frame (0x90 offset) as the report buffer.
 * Confidence: medium
 */
void *sk_report_buf_ptr(void){ return (void*)0x90; }

/*--------------------------------------------------------------------*/

/* FUN_0006b3a4 @ 0x6b3a4   (est. sk_noop_6b3a4)
 * Ghidra: void FUN_0006b3a4(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b3a4(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b3d0 @ 0x6b3d0   (est. sk_gt1)
 * Ghidra: bool FUN_0006b3d0(ulong)
 * Returns whether the value is greater than 1.
 * Confidence: medium
 */
bool sk_gt1(sk_word_t v){ return 1 < v; }

/*--------------------------------------------------------------------*/

/* FUN_0006b3e0 @ 0x6b3e0   (est. sk_buf_grow_wrap)
 * Ghidra: void FUN_0006b3e0(void)
 * Resizes the report buffer via 0x696a8.
 * Confidence: medium
 * Notes: FUN_000696a8.
 */
void sk_buf_grow_wrap(void){ sk_buf_resize10_wrap(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b3f4 @ 0x6b3f4   (est. sk_buf_next_ptr)
 * Ghidra: undefined1[16] FUN_0006b3f4(long)
 * Returns a {ptr+1, 0} pair.
 * Confidence: medium
 */
sk_word_t sk_buf_next_ptr(long p){ return (sk_word_t)(p + 1) << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b404 @ 0x6b404   (est. sk_noop_6b404)
 * Ghidra: void FUN_0006b404(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b404(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b42c @ 0x6b42c   (est. sk_gt1b)
 * Ghidra: bool FUN_0006b42c(ulong)
 * Returns whether the value is greater than 1.
 * Confidence: medium
 */
bool sk_gt1b(sk_word_t v){ return 1 < v; }

/*--------------------------------------------------------------------*/

/* FUN_0006b438 @ 0x6b438   (est. sk_inc_w8)
 * Ghidra: int FUN_0006b438(void)
 * Returns the caller's byte plus one.
 * Confidence: medium
 */
int sk_inc_w8(void){ return in_w8 + 1; }

/*--------------------------------------------------------------------*/

/* FUN_0006b440 @ 0x6b440   (est. sk_hex_col_w)
 * Ghidra: void FUN_0006b440(ulong)
 * Hex-column accumulator helper with a carry probe, then the emit helper.
 * Confidence: medium
 * Notes: FUN_00294cb4.
 */
void sk_hex_col_w(sk_word_t v){ (void)v; sk_hex_col_emit(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b45c @ 0x6b45c   (est. sk_noop_6b45c)
 * Ghidra: void FUN_0006b45c(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b45c(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b474 @ 0x6b474   (est. sk_noop_6b474)
 * Ghidra: void FUN_0006b474(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b474(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b48c @ 0x6b48c   (est. sk_console_init5)
 * Ghidra: void FUN_0006b48c(void)
 * Runs the console symbol resolution with a return-address marker.
 * Confidence: medium
 * Notes: LAB_00067ecc; FUN_00002534.
 */
void sk_console_init5(void){ sk_boot_enter(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b4ac @ 0x6b4ac   (est. sk_buf_grow_init)
 * Ghidra: void FUN_0006b4ac(void)
 * Initializes a report buffer with capacity 8 via 0x6a374.
 * Confidence: medium
 * Notes: FUN_0006a374(0,8,0).
 */
void sk_buf_grow_init(void){ sk_buf_resize10_wrap(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b4c0 @ 0x6b4c0   (est. sk_noop_6b4c0)
 * Ghidra: void FUN_0006b4c0(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b4c0(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b4d0 @ 0x6b4d0   (est. sk_fatal_dt_kit)
 * Ghidra: void FUN_0006b4d0(void)
 * Raises the fatal DeviceTreeKit error.
 * Confidence: medium
 * Notes: no-return FUN_001afa84.
 */
void sk_fatal_dt_kit(void){ sk_fatal(s_Fatal_error,0xb,2,in_x3,in_x4,s_DeviceTreeKit_DeviceTreeKit_swif,0x21,2,0xa6,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006b500 @ 0x6b500   (est. sk_buf_slot16a)
 * Ghidra: undefined1[16] FUN_0006b500(void)
 * Returns a 16-byte {ptr, 0x10} slot.
 * Confidence: medium
 */
sk_word_t sk_buf_slot16a(void){ return (sk_word_t)0x10 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b514 @ 0x6b514   (est. sk_buf_slot16b)
 * Ghidra: undefined1[16] FUN_0006b514(void)
 * Returns a 16-byte {ptr, 0x10} slot.
 * Confidence: medium
 */
sk_word_t sk_buf_slot16b(void){ return (sk_word_t)0x10 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b528 @ 0x6b528   (est. sk_hex_char30)
 * Ghidra: void FUN_0006b528(void)
 * Emits a 0x30-byte hex column then loads console slot 0x64e050.
 * Confidence: medium
 * Notes: 0x30/0xe100000000000000 frame.
 */
void sk_hex_char30(void){ sk_console_load_e050(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b540 @ 0x6b540   (est. sk_report_emit_nt)
 * Ghidra: void FUN_0006b540(void)
 * Emits a report record via the shared emit helper.
 * Confidence: medium
 * Notes: thunk_FUN_002acbb8.
 */
void sk_report_emit_nt(void){ sk_report_emit(0,0); }

/*--------------------------------------------------------------------*/

/* FUN_0006b550 @ 0x6b550   (est. sk_report_end_rec)
 * Ghidra: undefined1[16] FUN_0006b550(undefined8)
 * Returns a {0x677880, param_1} report end record.
 * Confidence: medium
 */
sk_word_t sk_report_end_rec(sk_word_t p){ return (sk_word_t)p << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b560 @ 0x6b560   (est. sk_report_out_bound)
 * Ghidra: undefined1[16] FUN_0006b560(void)
 * Returns the 'out bound' string record (0x20666f2074756f20 / 0xee0073646e756f62).
 * Confidence: medium
 */
sk_word_t sk_report_out_bound(void){ return 0x20666f2074756f20; }

/*--------------------------------------------------------------------*/

/* FUN_0006b584 @ 0x6b584   (est. sk_report_name_rec)
 * Ghidra: undefined8 FUN_0006b584(undefined8,long)
 * Returns the report name record: '(name' or the caller's value when the second arg is nonzero.
 * Confidence: medium
 */
sk_word_t sk_report_name_rec(sk_word_t v, long sel){ return sel ? v : 0x656d616e206f6e28; }

/*--------------------------------------------------------------------*/

/* FUN_0006b5a0 @ 0x6b5a0   (est. sk_report_emit_hdr)
 * Ghidra: void FUN_0006b5a0(void)
 * Resolves the report header symbol.
 * Confidence: medium
 * Notes: FUN_0064e030; FUN_00002534.
 */
void sk_report_emit_hdr(void){ sk_boot_enter(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b5c0 @ 0x6b5c0   (est. sk_console_state5)
 * Ghidra: void FUN_0006b5c0(void)
 * Reads console state (stack-offset 0x48 variant).
 * Confidence: medium
 * Notes: FUN_001eb088.
 */
void sk_console_state5(void){ sk_console_read_state(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b5e0 @ 0x6b5e0   (est. sk_console_state6)
 * Ghidra: void FUN_0006b5e0(void)
 * Reads console state (stack-offset 0x40 variant).
 * Confidence: medium
 * Notes: FUN_001eb088.
 */
void sk_console_state6(void){ sk_console_read_state(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b600 @ 0x6b600   (est. sk_report_space_rec)
 * Ghidra: undefined1[16] FUN_0006b600(void)
 * Returns the {0x20, 0xe100000000000000} report space record.
 * Confidence: medium
 */
sk_word_t sk_report_space_rec(void){ return (sk_word_t)0xe100000000000000 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b610 @ 0x6b610   (est. sk_report_zero_rec)
 * Ghidra: undefined1[16] FUN_0006b610(void)
 * Returns the {0, 0xe000000000000000} zero report record.
 * Confidence: medium
 */
sk_word_t sk_report_zero_rec(void){ return (sk_word_t)0xe000000000000000 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b620 @ 0x6b620   (est. sk_noop_6b620)
 * Ghidra: void FUN_0006b620(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b620(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b630 @ 0x6b630   (est. sk_noop_6b630)
 * Ghidra: void FUN_0006b630(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b630(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b640 @ 0x6b640   (est. sk_report_ize)
 * Ghidra: void FUN_0006b640(void)
 * Emits the 'ize' separator record (0x20657a69735b20 / 0xe700000000000000).
 * Confidence: medium
 * Notes: thunk_FUN_002acbb8.
 */
void sk_report_ize(void){ sk_report_emit(0x20657a69735b20, 0xe700000000000000); }

/*--------------------------------------------------------------------*/

/* FUN_0006b65c @ 0x6b65c   (est. sk_report_framerec)
 * Ghidra: undefined1[16] FUN_0006b65c(void)
 * Returns a report frame record (stack offsets 0x10/0x0f).
 * Confidence: medium
 */
sk_word_t sk_report_framerec(void){ return 0; }

/*--------------------------------------------------------------------*/

/* FUN_0006b674 @ 0x6b674   (est. sk_noop_6b674)
 * Ghidra: void FUN_0006b674(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b674(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b680 @ 0x6b680   (est. sk_report_nl_rec)
 * Ghidra: undefined1[16] FUN_0006b680(void)
 * Returns the {10, 0xe100000000000000} newline report record.
 * Confidence: medium
 */
sk_word_t sk_report_nl_rec(void){ return (sk_word_t)0xe100000000000000 << 40; }

/*--------------------------------------------------------------------*/

/* FUN_0006b68c @ 0x6b68c   (est. sk_noop_6b68c)
 * Ghidra: void FUN_0006b68c(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b68c(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b6a0 @ 0x6b6a0   (est. sk_noop_6b6a0)
 * Ghidra: void FUN_0006b6a0(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b6a0(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b6ac @ 0x6b6ac   (est. sk_noop_6b6ac)
 * Ghidra: void FUN_0006b6ac(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b6ac(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b6c0 @ 0x6b6c0   (est. sk_report_store_slot)
 * Ghidra: void FUN_0006b6c0(void)
 * Stores the report entry (frame base, key, value) into the slot indexed by the caller registers.
 * Confidence: medium
 */
void sk_report_store_slot(void){ *(sk_word_t*)((char*)unaff_x27 + 0x10) = (sk_word_t)unaff_x20; *(sk_word_t*)((char*)unaff_x27 + unaff_x23*0x10 + 0x20) = unaff_x21; *(sk_word_t*)((char*)unaff_x27 + unaff_x23*0x10 + 0x28) = (sk_word_t)unaff_x22; }

/*--------------------------------------------------------------------*/

/* FUN_0006b6d4 @ 0x6b6d4   (est. sk_noop_6b6d4)
 * Ghidra: void FUN_0006b6d4(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b6d4(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b6e0 @ 0x6b6e0   (est. sk_report_free0)
 * Ghidra: undefined8 FUN_0006b6e0(void)
 * Returns 0 (report free no-op).
 * Confidence: medium
 */
sk_word_t sk_report_free0(void){ return 0; }

/*--------------------------------------------------------------------*/

/* FUN_0006b6f4 @ 0x6b6f4   (est. sk_noop_6b6f4)
 * Ghidra: void FUN_0006b6f4(void)
 * Empty stub (no-op).
 * Confidence: medium
 */
void sk_noop_6b6f4(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006b700 @ 0x6b700   (est. sk_report_dots)
 * Ghidra: void FUN_0006b700(void)
 * Emits the '...' separator record (0x2e2e2e / 0xe300000000000000).
 * Confidence: medium
 * Notes: thunk_FUN_002acbb8.
 */
void sk_report_dots(void){ sk_report_emit(0x2e2e2e, 0xe300000000000000); }

/*--------------------------------------------------------------------*/

/* FUN_0006b714 @ 0x6b714   (est. sk_report_sym_e080)
 * Ghidra: void FUN_0006b714(void)
 * Resolves the report symbol at 0x64e080.
 * Confidence: medium
 * Notes: FUN_00002534.
 */
void sk_report_sym_e080(void){ sk_boot_enter(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b728 @ 0x6b728   (est. sk_report_sym_e060)
 * Ghidra: void FUN_0006b728(void)
 * Resolves the report symbol at 0x64e060.
 * Confidence: medium
 * Notes: FUN_00002534.
 */
void sk_report_sym_e060(void){ sk_boot_enter(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b760 @ 0x6b760   (est. sk_perm_flag_get)
 * Ghidra: undefined1 FUN_0006b760(void)
 * Returns the permission flag via 0x84dc8.
 * Confidence: medium
 * Notes: FUN_00084dc8.
 */
unsigned char sk_perm_flag_get(void){ return sk_perm_flag(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b764 @ 0x6b764   (est. sk_perm_flag_get2)
 * Ghidra: undefined1 FUN_0006b764(void)
 * Returns the permission flag via 0x84dc8.
 * Confidence: medium
 * Notes: FUN_00084dc8.
 */
unsigned char sk_perm_flag_get2(void){ return sk_perm_flag(); }

/*--------------------------------------------------------------------*/

/* FUN_0006b77c @ 0x6b77c   (est. sk_perm_set_hi)
 * Ghidra: void FUN_0006b77c(undefined8)
 * Stores a permission/feature value into the high half of the global at 0x68a4e8.
 * Confidence: medium
 * Notes: s_L4_ErrorCodePermissionInvalid_0068a4e8._6_8_.
 */
void sk_perm_set_hi(sk_word_t v){ sk_perm_hi = v; }

/*--------------------------------------------------------------------*/

/* FUN_0006b78c @ 0x6b78c   (est. sk_perm_set_lo)
 * Ghidra: void FUN_0006b78c(undefined8)
 * Stores a permission/feature value into the global at 0x68a4e6.
 * Confidence: medium
 * Notes: _DAT_0068a4e6.
 */
void sk_perm_set_lo(sk_word_t v){ sk_perm_lo = v; }

/*--------------------------------------------------------------------*/

/* FUN_0006b79c @ 0x6b79c   (est. sk_perm_get_hi)
 * Ghidra: undefined8 FUN_0006b79c(void)
 * Returns the permission/feature value at 0x68a4e8 high half.
 * Confidence: medium
 * Notes: s_L4_ErrorCodePermissionInvalid_0068a4e8._6_8_.
 */
sk_word_t sk_perm_get_hi(void){ return sk_perm_hi; }

/*--------------------------------------------------------------------*/

/* FUN_0006b7ac @ 0x6b7ac   (est. sk_perm_get_lo)
 * Ghidra: undefined8 FUN_0006b7ac(void)
 * Returns the permission/feature value at 0x68a4e6.
 * Confidence: medium
 * Notes: _DAT_0068a4e6.
 */
sk_word_t sk_perm_get_lo(void){ return sk_perm_lo; }

/*--------------------------------------------------------------------*/

/* FUN_0006b7bc @ 0x6b7bc   (est. sk_ipmm_init_flag)
 * Ghidra: void FUN_0006b7bc(void)
 * Runs the IPMM/launcher setup (0x6b7e0) and marks the setup flag (DAT_006b27e0).
 * Confidence: medium
 */
void sk_ipmm_init_flag(void){ sk_ipmm_setup(); DAT_006b27e0 = 1; }

/*--------------------------------------------------------------------*/

/* FUN_0006b7e0 @ 0x6b7e0   (est. sk_ipmm_setup)
 * Ghidra: void FUN_0006b7e0(void)
 * Sets up the IPMM (Isolated Physical Memory Manager) launcher region: allocates a 1 MiB page block, fills a 26-entry device/feature table, and (when the launcher flag is set) programs the RO frame and issues CallSupervisor(0) to create the launcher IPMM freelist and a zeroed frame space, registering the freelist page and the IPMM abort path. Strings 'Creating launcher IPMM freelist', 'Creating launcher frame zero space', and several 'IPMM abort in function %s line %d' abort paths.
 * Confidence: low
 * Notes: Strings s_Creating_launcher_IPMM_freelist_s_005bef67, s_Creating_launcher_frame_zero_spa_005bef8c, s__IPMM_abort_in_function__s_line___005be94d/005bea28/005beafe; FUN_0006d240/0006cea4/004b7ba0/004b7bec/0019ae2c/0019ae60/00034a2c/00054354; CallSupervisor(0); DAT_006b27e0/006b27f0/006b27f8/006b2808/006b2820/006b2828/006b2830/006b2838/006b2840/006b28d0/006b2918/006b2920/006b2928; writes read-only 0x64e180.
 */
void sk_ipmm_setup(void)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_word_t base = sk_alloc_big(0x100000, 0);       /* FUN_0006d240 */
    for (int i = 0; i < 0x1a; i++)
        *(sk_word_t *)(i*8 + 0x6b2848) = sk_dev_entry(i);   /* FUN_0006cea4 */
    sk_ipmm_hi = base + 0x100000;                    /* _DAT_006b2920 */
    sk_ipmm_lo = base;                               /* _DAT_006b2918 */
    if ((DAT_006b27e0 & 1) != 0) {
        sk_word_t l1 = sk_ipmm_slot + sk_ipmm_cnt * 0x40;   /* _DAT_006b2808 + _DAT_006b2828*0x40 */
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        tp[0]=0x11; wr64(tp+8, base + 0xfc000); wr64(tp+0x10, l1);
        CallSupervisor(0);
        if ((uVar3 & 0xff) != 0) sk_ipmm_abort_cap(uVar3);   /* FUN_004b7ba0 */
        /* create launcher IPMM freelist */
        sk_word_t d1 = _DAT_004beea0, d2 = uRam00000000004beea8, d3 = _DAT_004beeb0, d4 = uRam00000000004beeb8;
        void *pt = sk_pt_ctx();
        unsigned char ok = (*(unsigned char(*)(void*,sk_word_t,sk_word_t*,void*,int,int))
                           (*(void***)((char*)pt + 0x30)[0]))(pt, 0x940, &d1, &DAT_006b27f0, 0, 0);
        if (ok == 0) {
            if (_DAT_006b27f8 == 0) sk_ipmm_nofunc();      /* FUN_00054354 */
            (**(void(**)(void*,sk_word_t))(_DAT_006b27f8 + 8))(&DAT_006b27f0, 0x6b2800);
            _DAT_006b2820 = 0;
            _DAT_006b2828 = 0;
            /* create launcher frame zero space */
            sk_word_t d5 = _DAT_004bee90, d6 = uRam00000000004bee98;
            sk_word_t sel = 0x11;
            ok = (*(unsigned char(*)(void*,sk_word_t,sk_word_t*,void*,int,int))
                 (*(void***)((char*)pt + 0x30)[0]))(pt, 0x1808, &sel, &DAT_006b2830, 0, 0);
            if (ok == 0) {
                if (_DAT_006b2838 == 0) sk_ipmm_nofunc();
                (**(void(**)(void*,sk_word_t*))(_DAT_006b2838 + 8))(&DAT_006b2830, &sel);
                _DAT_006b2840 = d6;
                DAT_006b27e8 = 1;
                *(volatile sk_word_t*)0x64e180 = 1;
                sk_word_t cap = sk_alloc_ep(0x11);
                ok = (*(unsigned char(*)(void*,sk_word_t,sk_word_t))
                     (*(void***)(_DAT_006b2838 + 0x28)[0]))(&DAT_006b2830, 0, cap);
                if (ok == 0) { sk_ep_release(cap, 0x11); return; }   /* FUN_0019ae60 */
                sk_panic_bad(0, "IPMM abort in function %s line %d");
            } else {
                sk_panic_bad(0, "IPMM abort in function %s line %d");
            }
        } else {
            sk_panic_bad(0, "IPMM abort in function %s line %d");
        }
        sk_ipmm_finish(l1);                          /* FUN_004b7bec */
    }
    sk_ipmm_count += 1;                              /* _DAT_006b2928 */
    if (canary != 0xd37afd4bb400012a) sk_stack_fail();
}

/*--------------------------------------------------------------------*/

/* FUN_0006bb34 @ 0x6bb34   (est. sk_ipmm_log)
 * Ghidra: void FUN_0006bb34(void)
 * Logs the IPMM allocator status: bytes left and bump count.
 * Confidence: low
 * Notes: Strings s__ipmm___0x_llx_bytes_left_005beb77, s__ipmm___bumped__zd_times_005beb92.
 */
void sk_ipmm_log(void)
{
    sk_logf0("ipmm: 0x%llx bytes left");    /* FUN_00118b28 */
    sk_logf0("ipmm: bumped %zd times");
}

/*--------------------------------------------------------------------*/

/* FUN_0006bb8c @ 0x6bb8c   (est. sk_ipmm_count_get)
 * Ghidra: undefined8 FUN_0006bb8c(void)
 * Returns the IPMM bump count (DAT_006b2928).
 * Confidence: high
 */
sk_word_t sk_ipmm_count_get(void){ return _DAT_006b2928; }

/*--------------------------------------------------------------------*/

/* FUN_0006bb98 @ 0x6bb98   (est. sk_ipmm_alloc_stat)
 * Ghidra: undefined8 FUN_0006bb98(void)
 * Returns the IPMM allocation count (DAT_006b2930).
 * Confidence: high
 */
sk_word_t sk_ipmm_alloc_stat(void){ return _DAT_006b2930; }

/*--------------------------------------------------------------------*/

/* FUN_0006bba4 @ 0x6bba4   (est. sk_ipmm_free_stat)
 * Ghidra: undefined8 FUN_0006bba4(void)
 * Returns the IPMM free count (DAT_006b2938).
 * Confidence: high
 */
sk_word_t sk_ipmm_free_stat(void){ return _DAT_006b2938; }

/*--------------------------------------------------------------------*/

/* FUN_0006bbb0 @ 0x6bbb0   (est. sk_err_rec_fill)
 * Ghidra: void FUN_0006bbb0(undefined8*,byte)
 * Fills a 4-word record with the canonical L4_ErrorCode* string for the given error code (0-9), or a generic fallback for codes above 9.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004beec0..; fallback globals DAT_004bf000/004bf010/004bf018.
 */
void sk_err_rec_fill(sk_word_t *rec, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) {
        rec[0]=_DAT_004bf000; rec[1]=uRam00000000004bf008;
        rec[2]=_DAT_004bf010; rec[3]=uRam00000000004bf018;
        sk_err_rec_print(rec);              /* FUN_0006bcc0 */
        return;
    }
    const char *s = names[code];
    rec[0]=*(sk_word_t*)s; rec[1]=*(sk_word_t*)(s+8); rec[2]=*(sk_word_t*)(s+0x10); rec[3]=*(sk_word_t*)(s+0x18);
}

/*--------------------------------------------------------------------*/

/* FUN_0006bcc0 @ 0x6bcc0   (est. sk_err_rec_print)
 * Ghidra: void FUN_0006bcc0(undefined8)
 * Prints an L4 error-code record with the 'L4_ErrorCode: %zu' format.
 * Confidence: low
 * Notes: s_L4_ErrorCode__zu_005a8c7b; FUN_00116bb4.
 */
void sk_err_rec_print(sk_word_t rec){ sk_print_rec(rec, 0x1f, "L4_ErrorCode: %zu", 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006bcf8 @ 0x6bcf8   (est. sk_ipmm_alloc)
 * Ghidra: undefined8 FUN_0006bcf8(undefined8,ulong,ulong,ulong,uint)
 * IPMM physical-memory allocator: validates the allocation type, requests the frame from the supervisor (CallSupervisor(1)), and allocates from the launcher IPMM region by type (untyped 0x11 from a free-slot stack, typed regions 4/6/7/8/0x11 from the bump cursor), marking the bitmap and mapping the frame; panics on invalid type or allocation failure.
 * Confidence: low
 * Notes: Strings s_unexpected_PMM_allocation_type_005becb2, s__ipmm___Operation_Invalid__Wrong_005bedc5, s_Failed_to_create_untyped__type___005bedf1, s_Failed_to_map_frame_to_zero_005bed6a; CallSupervisor(0/1); DAT_006b2808/006b2820/006b2828/006b2830/006b2838/006b2848/006b2918/006b2920/006b2940/006b2948/006b2950/006b27e8; FUN_0006b7e0/004b7c88/004b7cd4/004b7dec/004b7e64/004b7008/004b7d20/00055a90.
 */
sk_word_t sk_ipmm_alloc(sk_word_t a, sk_word_t type, sk_word_t size, sk_word_t pa, unsigned int flags)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    if ((flags & 0xfffffffd) != 0)
        sk_panic_bad(0, "unexpected PMM allocation type");
    CallSupervisor(1);
    if (size == 5) return 0x107;                 /* 5: special */
    if ((size & 0xfb) == 0) {
        int t = (int)type;
        sk_word_t sz = size;
        if (t == 0x11 && _DAT_006b2828 != 0) {
            _DAT_006b2828 -= 1;
            sk_word_t slot = _DAT_006b2808 + _DAT_006b2828 * 0x40;
            sz = 0;
            if (slot == 0) goto alloc_bump;
            CallSupervisor(1);
            sz = pa;
            if ((slot & 0xff) != 0) { sk_ipmm_alloc_bad(slot); goto alloc_bump; }
            goto mapped;
        }
alloc_bump:
        if (sk_ipmm_lo < 0xffffffffffffc000 && sk_ipmm_hi >= sk_ipmm_lo + 0x4000) {
            if (t < 8) {
                if (t == 4) { sz = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
                else if (t == 6) {
                    sz = _DAT_006b2940;
                    if ((_DAT_006b2940 & 0x3fff) == 0) { sz = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
                    _DAT_006b2940 = sz + 0x800;
                } else if (t == 7) {
                    if ((_DAT_006b2948 & 0x3fff) == 0) { _DAT_006b2948 = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
                    sz = _DAT_006b2948; _DAT_006b2948 += 0x40;
                } else goto bad_op;
            } else if (t - 0xc > 2) {
                if (t == 8) {
                    sz = _DAT_006b2950;
                    if ((_DAT_006b2950 & 0x3fff) == 0) { sz = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
                    _DAT_006b2950 = sz + 0x40;
                } else if (t != 0x11) goto bad_op;
                else { sz = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
            } else { sz = sk_ipmm_lo; sk_ipmm_lo += 0x4000; }
            if (sz != (sk_word_t)-1) {
                sk_word_t entry = *(sk_word_t *)((type & 0xffffffff) * 8 + 0x6b2848);
                volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
                tp[0]=(unsigned char)(type & 0xffffffff); wr64(tp+8, sz); wr64(tp+0x10, pa);
                CallSupervisor(0);
                if (entry != 0) {
                    sk_untyped_fail(type, 0);
                    sk_logf0("Failed to create untyped: type %d");
                    sz = 0;
                    if ((entry & 0xff) != 0) goto alloc_bad;
                }
mapped:
                if (t == 0x11 && (DAT_006b27e8 & 1) != 0) {
                    if ((**(unsigned char(**)(void*,int,sk_word_t))(_DAT_006b2838 + 0x28))(&DAT_006b2830, 0, pa) != 0)
                        sk_panic_bad(0, "Failed to map frame to zero");
                    sk_ipmm_map_zero(pa);        /* FUN_004b7d20 */
                }
                sk_ipmm_alloc_count += 1;        /* _DAT_006b2930 */
                return 0;
            }
        } else {
            sk_ipmm_grow();                      /* FUN_004b7008 */
            goto alloc_bad;
        }
bad_op:
        sk_untyped_fail(type);
        sk_panic_bad(0, "ipmm: Operation Invalid: Wrong [type]");
alloc_bad:
        size = sk_ipmm_abort(entry);             /* FUN_004b7cd4 */
    }
    sk_ipmm_err(size);                           /* FUN_004b7e64 */
    sk_ipmm_done();                              /* FUN_004b7dec */
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006bfe4 @ 0x6bfe4   (est. sk_ipmm_free)
 * Ghidra: void FUN_0006bfe4(undefined8,ulong)
 * IPMM frame release: bumps the free count, requests the frame from the supervisor (CallSupervisor(1)), grows the freelist when nearly exhausted, and either maps the frame back to zero space or returns it to the freelist; panics on failure.
 * Confidence: low
 * Notes: Strings s_Failed_to_bump_freelist_005bee58, s_Failed_to_map_frame_freed_frame_005bef47; CallSupervisor(0/1/5); DAT_006b27e8/006b27f0/006b27f8/006b2808/006b2820/006b2828/006b2830/006b2838; FUN_004b7eb0/004b7edc/004b7f24/004b7f6c/004b7fb4.
 */
void sk_ipmm_free(sk_word_t a, sk_word_t frame)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    if ((DAT_006b27e8 & 1) == 0) { sk_ipmm_free_done(); return; }
    sk_ipmm_free_count += 1;                     /* _DAT_006b2938 */
    CallSupervisor(1);
    if ((frame & 0xff) == 4) { sk_ipmm_free_bad(0x107); return; }
    if (_DAT_006b2820 - _DAT_006b2828 < 2) {
        sk_word_t out[4];
        out[0] = _DAT_006b2820 * 0x40 + 0x4000;
        if ((**(unsigned char(**)(void*,sk_word_t*))(_DAT_006b27f8 + 0x18))(&DAT_006b27f0, out) != 0)
            sk_panic_bad(0, "Failed to bump freelist");
        _DAT_006b2820 = out[0] >> 6;
    }
    sk_word_t slot = _DAT_006b2808 + _DAT_006b2828 * 0x40;
    CallSupervisor(1);
    if ((frame & 0xff) == 0) {
        do { CallSupervisor(5); } while (slot == 1);
        if ((slot & 0xff) != 0) sk_ipmm_free2(slot);
        volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
        sk_word_t v = *tp;
        do { CallSupervisor(0); *tp = v; } while (slot == 1);
        if ((slot & 0xff) != 0) sk_ipmm_free3(slot);
        if ((**(unsigned char(**)(void*,int,sk_word_t))(_DAT_006b2838 + 0x28))(&DAT_006b2830, 0, slot) == 0) {
            sk_ipmm_map_back(slot);              /* FUN_004b7fb4 */
            return;
        }
    } else {
        slot = sk_ipmm_return(frame);            /* FUN_004b7edc */
        sk_ipmm_free2(slot);
        sk_ipmm_free3(slot);
    }
    sk_panic_bad(0, "Failed to map frame freed frame");
}

/*--------------------------------------------------------------------*/

/* FUN_0006c1b4 @ 0x6c1b4   (est. sk_err_rec_fill0)
 * Ghidra: void FUN_0006c1b4(void)
 * Wrapper: fills an error record on the stack (offset 0x10).
 * Confidence: low
 * Notes: FUN_0006bbb0.
 */
void sk_err_rec_fill0(void){ sk_err_rec_fill((sk_word_t*)0x10, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006c1d4 @ 0x6c1d4   (est. sk_noop_6c1d4)
 * Ghidra: void FUN_0006c1d4(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_6c1d4(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006c1e8 @ 0x6c1e8   (est. sk_err_rec_fill1)
 * Ghidra: void FUN_0006c1e8(void)
 * Wrapper: fills an error record on the stack (offset 0x18).
 * Confidence: low
 * Notes: FUN_0006bbb0.
 */
void sk_err_rec_fill1(void){ sk_err_rec_fill((sk_word_t*)0x18, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006c208 @ 0x6c208   (est. sk_err_rec_fill2)
 * Ghidra: void FUN_0006c208(void)
 * Wrapper: fills an error record on the stack.
 * Confidence: low
 * Notes: FUN_0006bbb0.
 */
void sk_err_rec_fill2(void){ sk_err_rec_fill(0, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006c214 @ 0x6c214   (est. sk_noop_6c214)
 * Ghidra: void FUN_0006c214(void)
 * Empty stub (no-op).
 * Confidence: high
 */
void sk_noop_6c214(void){ }

/*--------------------------------------------------------------------*/

/* FUN_0006c228 @ 0x6c228   (est. sk_vspace_table_ready)
 * Ghidra: void FUN_0006c228(undefined1)
 * Marks the vspace client table ready: stores the value into slot 0x64e1a0 and sets the ready flag (DAT_006b2958).
 * Confidence: high
 * Notes: Writes read-only 0x64e1a0; _DAT_006b2958.
 */
void sk_vspace_table_ready(unsigned char v)
{
    *(volatile sk_word_t*)0x64e1a0 = v;
    sk_vspace_ready = 1;
}

/*--------------------------------------------------------------------*/

/* FUN_0006c244 @ 0x6c244   (est. sk_vspace_client_find)
 * Ghidra: void FUN_0006c244(short)
 * Walks the vspace client list (DAT_006ad980) looking for a client whose tag equals the given value; panics if the vspace table is not ready.
 * Confidence: low
 * Notes: String s__s__vspace_table_not_ready_yet___005befc4; DAT_006ad980/006b2958.
 */
void sk_vspace_client_find(short tag)
{
    short *p = sk_vspace_client_list;        /* _DAT_006ad980 */
    if (sk_vspace_ready == 0)
        sk_panic_bad(0, "%s: vspace table not ready yet");
    for (; p != NULL && *p != tag; p = *(short **)(p + 0x10)) { }
}

/*--------------------------------------------------------------------*/

/* FUN_0006c2b0 @ 0x6c2b0   (est. sk_vspace_client_add)
 * Ghidra: undefined8 FUN_0006c2b0(long)
 * Adds a vspace client to the table: allocates a 0x30-byte client node (tag 0xda02648f, magic 0xaa00/0xaa01), records the client address, and links it into the client list, returning the magic token.
 * Confidence: low
 * Notes: Strings s_L4_failed_on__s__d___s_005bf00c, s__s__vspace_table_not_ready_yet___005befc4; FUN_00010244/004b808c; DAT_006ad980/006b2958.
 */
sk_word_t sk_vspace_client_add(long addr)
{
    if (sk_vspace_ready != 0) {
        if (addr == 0) sk_panic_bad(0, "L4 failed on %s: %d %s");
        if (sk_vspace_ready != 0) {
            unsigned short *n = (unsigned short*)sk_alloc_small(0x30, 1, 0xda02648f);  /* FUN_00010244 */
            *n = 0xaa00;
            *(volatile sk_word_t*)0x64e1a2 = 0xaa01;
            if (sk_vspace_client_list == NULL) {
                *(sk_word_t*)(n + 0x10) = 0;
            } else if (*(sk_word_t**)((char*)sk_vspace_client_list + 0x28) == &sk_vspace_client_list) {
                *(unsigned short**)(n + 0x10) = sk_vspace_client_list;
                *(unsigned short**)((char*)sk_vspace_client_list + 0x28) = n + 0x10;
            } else {
                sk_vspace_bad();                /* FUN_004b808c */
            }
            sk_vspace_client_list = n;
            *(unsigned char**)(n + 0x14) = &sk_vspace_client_list;
            *(long*)(n + 0xc) = addr;
            return 0xffffaa00;
        }
    }
    sk_panic_bad(0, "%s: vspace table not ready yet");
}

/*--------------------------------------------------------------------*/

/* FUN_0006c3c8 @ 0x6c3c8   (est. sk_vspace_client_clear)
 * Ghidra: void FUN_0006c3c8(void)
 * Clears the vspace client list (frees the nodes) when the table is ready.
 * Confidence: low
 * Notes: s__s__vspace_table_not_ready_yet___005befc4; thunk_FUN_00012568.
 */
void sk_vspace_client_clear(void)
{
    if (sk_vspace_ready != 0) { sk_free2(); return; }
    sk_panic_bad(0, "%s: vspace table not ready yet");
}

/*--------------------------------------------------------------------*/

/* FUN_0006c404 @ 0x6c404   (est. sk_vspace_client_field)
 * Ghidra: undefined8 FUN_0006c404(void)
 * Returns the data field (offset +0x18) of the current vspace client, or 0 if none.
 * Confidence: low
 * Notes: FUN_0006c244.
 */
sk_word_t sk_vspace_client_field(void)
{
    if (sk_vspace_ready != 0) {
        sk_word_t c = sk_vspace_client_find(0);
        return c ? *(sk_word_t *)(c + 0x18) : 0;
    }
    sk_panic_bad(0, "%s: vspace table not ready yet");
}

/*--------------------------------------------------------------------*/

/* FUN_0006c454 @ 0x6c454   (est. sk_vspace_client_remove)
 * Ghidra: undefined8 FUN_0006c454(void)
 * Removes the current vspace client from the list: unlinks its node, fixes the surrounding links (asserting list integrity with 'Bad link elm %p next>prev ...' panics), and frees it.
 * Confidence: low
 * Notes: Strings s_expected_client_to_be_in_list_005bf1c8, s_Bad_link_elm__p_next_>prev____el_005bf1e6, s_Bad_link_elm__p_prev_>next____el_005bf20c, s_L4_failed_on__s__d___s_005bf00c, s__s__vspace_table_not_ready_yet___005befc4; thunk_FUN_00012568.
 */
sk_word_t sk_vspace_client_remove(void)
{
    if (sk_vspace_ready != 0) {
        short *c = (short*)sk_vspace_client_find(0);
        if (c == NULL) return 3;
        short tag = *c;
        if (sk_vspace_ready != 0) {
            c = (short*)sk_vspace_client_find((long)tag);
            if (c == NULL) sk_panic_bad(0, "expected client to be in list");
            long next = *(long *)(c + 0x10);
            long *prev;
            if (next == 0) {
                prev = *(long **)(c + 0x14);
                if ((short *)*prev != c) sk_panic_assert("Bad link elm %p next>prev ...");
            } else {
                if (*(long **)((char*)next + 0x28) != (long *)(c + 0x10))
                    sk_panic_assert("Bad link elm %p next>prev ...");
                if ((short *)**(void **)(c + 0x14) != c)
                    sk_panic_assert("Bad link elm %p prev>next ...");
                *(void **)((char*)next + 0x28) = *(void **)(c + 0x14);
                prev = *(long **)(c + 0x14);
            }
            *prev = next;
            if (*c == tag) { sk_free2(); return 0; }
            sk_panic_bad(0, "L4 failed on %s: %d %s");
        }
    }
    sk_panic_bad(0, "%s: vspace table not ready yet");
}

/*--------------------------------------------------------------------*/

/* FUN_0006c5cc @ 0x6c5cc   (est. sk_bootinfo_parse)
 * Ghidra: void FUN_0006c5cc(long*,int)
 * Parses the boot-info capability list into the kernel's untyped-region and device tables: walks each boot capability (recording untyped regions with base/size/type, DART/MMU controllers, and device entries into the fixed 0x6b2xxx tables), initializes the region index and the __TEXT/__DATA slide bounds, and populates the device/DART counts. Logs 'untyped: base 0x%016llx size', 'CBootInfo found DART with sid', 'CBootInfo found DART Table with s', 'Warning: Unexpected null cap in', and 'Roottask slide is 0x%llx'.
 * Confidence: low
 * Notes: Strings s_untyped___base_0x_016llx__size_0_005bf4e3, s_CBootInfo_found_DART_with_sid_____005bf967, s_CBootInfo_found_DART_Table_with_s_005bf9d2, s__Warning__Unexpected_null_cap_in_005bfa04, s_Roottask_slide_is_0x_llx_005a8b16, s___TEXT_005bb905, s___DATA_005bb23b; DAT_006be890..006be8e8/006b2960..006b2c40/006be360..006be890/006ad6e0/006ad988/006ad990/2bc686b8528/2bc686b8530/2bc686b8548/2bc686b8550; CallSupervisor(0/2/3); FUN_000552a4/00055328/00055344/00055718/0005574c/0005ba14/00051e5c/000537c4/0006d7d0/0005537c/000553b0/000554bc/000554f0/00055524; SoftwareBreakpoint/abort FUN_004b8288/004b82b4/004b830c/004b8364/004b82e0/004b8390/004b81e8/004b8238/004b8148/004b8198/004b8338.
 */
void sk_bootinfo_parse(long *caps, int do_zero)
{
    sk_word_t canary = 0xd37afd4bb400012a;
    sk_boot_caps = caps;                         /* _DAT_006be890 */
    if (_DAT_006be898 != 0) {
        _DAT_006be8a0 = sk_region_lo();          /* FUN_00055718 */
        _DAT_006be8a8 = sk_region_hi();          /* FUN_0005574c */
        DAT_006be8b0 = _DAT_006be8a0 != 0 && _DAT_006be8a8 != 0;
    }
    sk_word_t c1 = sk_cap1();                    /* FUN_000552a4 */
    sk_word_t c2 = sk_cap2();                    /* FUN_00055328 */
    sk_word_t c3 = sk_cap3();                    /* FUN_00055344 */
    sk_word_t count = _DAT_006be8b4;
    _DAT_006be8b4 = _DAT_006be8e8;
    for (long *list = caps; _DAT_006be8e8 = _DAT_006be8b4, list != (long*)-1; list = (long*)list[1]) {
        long n = *list;
        if (n != 0) {
            long j = 0;
            do {
                _DAT_006be8b4 = count;
                sk_word_t *cap = (sk_word_t*)(list + j*4 + 4);
                unsigned char kind = (unsigned char)(*cap >> 0x38);
                if (kind == 0x0b) {
                    _DAT_006be880 = *cap & 0xffffffffffffffULL;
                } else if (kind == 0x03) {
                    sk_word_t w1 = cap[1], w2 = cap[2];
                    sk_word_t base = (w1 & 0xfffffffffff) << 0xc;
                    sk_logf1("untyped: base 0x%016llx size 0x%llx");
                    count = _DAT_006be8e8;
                    sk_word_t idx = _DAT_006be8e8;
                    if (idx > 0x3f) sk_boot_abort();
                    if (DAT_006be8b0 == 1) {
                        if (base == _DAT_006be8a0) _DAT_006be8b8 = *cap & 0xffffffffffffffULL;
                        else if (base == _DAT_006be8a8) _DAT_006be8c0 = *cap & 0xffffffffffffffULL;
                        else goto add_region;
                    } else {
add_region:
                        _DAT_006be8e8 += 1;
                        sk_word_t off = idx * 0x2e8;
                        sk_word_t sz2 = (w2 & 0xfffffffffff) << 0xc;
                        /* zero the 0x2e8-byte region entry at 0x6b2960.. */
                        for (int b = 0; b < 0x2e8; b += 8)
                            *(sk_word_t*)(off + 0x6b2960 + b) = 0;
                        *(sk_word_t *)(off + 0x6b2b08) = w1 >> 0x2c & 0xff;   /* type */
                        *(sk_word_t *)(off + 0x6b2b10) = base;
                        *(sk_word_t *)(off + 0x6b2b18) = sz2;
                        *(sk_word_t *)(off + 0x6b2b40) = cap[3];   /* phys */
                        /* DART/MMU and zero-space mapping for type bits */
                        if ((w1 & 0xff00000000000) != 0) {
                            sk_word_t t = (unsigned)(w1 >> 0x2c) & 0xff;
                            if (t == 3) { *(volatile sk_word_t*)0x64e1b0 = count; }
                            else if (t == 2) { *(volatile sk_word_t*)0x64e1ac = count; }
                            else if (t == 1) {
                                *(volatile sk_word_t*)0x64e1a4 = count;
                                if (do_zero != 0) {
                                    /* map the 26 DART/MMU registers into zero space */
                                    sk_word_t mask = cap[3];
                                    sk_word_t r0 = sk_reg_a();      /* FUN_000537c4 */
                                    sk_word_t r1 = sk_reg_a();
                                    sk_word_t capw = *cap;
                                    volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
                                    tp[0]=2; wr64(tp+8,0); wr64(tp+0x10,0);
                                    wr64(tp+0x18, mask & ~0x20000ULL); wr64(tp+0x20,0);
                                    CallSupervisor(3);
                                    if ((capw & 0xff) == 0) {
                                        CallSupervisor(2);
                                        if ((r0 & 0xff) == 0) {
                                            sk_word_t p = 0;
                                            for (int i = 0; i < 0x1a; i++) {
                                                sk_word_t lo = 0, hi = 0;
                                                if (i == 0x11) {
                                                    r0 = sk_reg_a(); r1 = sk_reg_a();
                                                    sk_word_t cw = *cap;
                                                    tp[0]=6; wr64(tp+8,0); wr64(tp+0x10,0);
                                                    wr64(tp+0x20, sk_dev); wr64(tp+0x18, sk_dev2);
                                                    CallSupervisor(3);
                                                    if ((cw & 0xff) != 0) sk_boot_abort();
                                                    CallSupervisor(2);
                                                    lo = r1; hi = r0;
                                                } else {
                                                    bool has = (mask & (1UL << (i & 0x1f))) != 0;
                                                    lo = has ? r0 : 0;
                                                    hi = has ? r1 : 0;
                                                }
                                                *(sk_word_t *)(off + 0x6b2a38 + i*8) = lo;
                                                *(sk_word_t *)(off + 0x6b2a40 + i*8) = hi;
                                            }
                                            goto next;
                                        }
                                    }
                                    sk_boot_abort();
                                }
                            } else {
                                *(sk_word_t *)(off + 0x6b2b10) = 0;
                                *(sk_word_t *)(off + 0x6b2b18) = 0;
                            }
                        }
                    }
                }
next:
                j++;
                count = _DAT_006be8b4;
                if (j == n) goto next_list;
            } while (1);
        }
next_list:
        _DAT_006be8b4 = count;
        count = _DAT_006be8b4;
        _DAT_006be8b4 = _DAT_006be8e8;
    }
    if (_DAT_006be8b4 > 0x40) sk_boot_abort();
    /* resolve __TEXT/__DATA slide bounds from the boot header */
    void *hdr = sk_panic_hooks();                /* FUN_0005ba14 */
    if (hdr != NULL && *(long*)((char*)hdr + 7*8) != 0 && *hdr == 0) {
        long text = sk_seg_find(*(void**)((char*)hdr + 7*8), "__TEXT");  /* FUN_00051e5c */
        long data = sk_seg_find(*(void**)((char*)hdr + 7*8), "__DATA");
        if (text != 0 && data != 0) {
            _DAT_006ad990 = _DAT_006ad6e0 + *(long *)(text + 0x18);
            _DAT_006ad988 = *(long *)(data + 0x18) + _DAT_006ad6e0;
            for (long *p = caps; p != (long*)-1; p = (long*)p[1]) {
                long n = *p;
                if (n != 0) {
                    for (long j = 0; j < n; j++) {
                        sk_word_t *cap = (sk_word_t*)(p + j*4 + 4);
                        sk_word_t cw = *cap;
                        unsigned char kind = (unsigned char)(cw >> 0x38);
                        if (kind < 7) {
                            if (kind == 0) { sk_logf0("Warning: Unexpected null cap in boot info"); continue; }
                            if (kind == 3) {
                                sk_word_t base = (cap[1] & 0xfffffffffff) << 0xc;
                                /* record frame vs text/data slide */
                                sk_word_t end = (cap[2] & 0xfffffffff) << 0xc;
                                sk_word_t s0 = (sk_word_t)_DAT_2bc686b8528 + _DAT_2bc686b8530;
                                if ((cap[1] & 0xff00000000000) == 0 && _DAT_006be8b4 != 0xf100001f
                                    && s0 == base) {
                                    sk_word_t idx = 0;
                                    /* find region containing base */
                                    long *r = (long*)&DAT_006b2b18;
                                    for (sk_word_t i = 0; i < _DAT_006be8b4; i++, r += 0x5d)
                                        if ((sk_word_t)r[-1] <= base && base < (sk_word_t)(*r + r[-1]))
                                            { idx = i; break; }
                                    *(volatile sk_word_t*)0x64e1a8 = idx;
                                    if (_DAT_006be8b4 <= *(volatile sk_word_t*)0x64e1a8)
                                        *(volatile sk_word_t*)0x64e1a8 = _DAT_006be8b4;
                                }
                                goto slide_check;
                            }
                        } else if (kind - 0xd < 5) { slide_check: ;
                            sk_word_t end = (cap[2] & 0xffffffffff) << 0xc;
                            if (end == _DAT_006ad990) _DAT_006be8c8 = cap[1] & 0xffffffffffffffULL;
                            if (end == _DAT_006ad988) _DAT_006be8d0 = cap[1] & 0xffffffffffffffULL;
                            sk_bb(cap);                     /* FUN_0006d7d0 */
                            continue;
                        } else if (kind == 7) {
                            _DAT_006be878 = cw & 0xffffffffffffffULL;
                            sk_bb(cap);
                            continue;
                        } else if (kind == 10) {
                            if ((cap[2] & 0xffe0) != 0) sk_boot_abort();
                            *(sk_word_t *)((cap[2] & 0x1f) * 8 + 0x6be360) = cw & 0xffffffffffffffULL;
                            continue;
                        } else {
                            if (c1 == kind) { _DAT_006be888 = cw & 0xffffffffffffffULL; continue; }
                            if (c2 == kind) {
                                if (_DAT_006be660 > 0x1f) sk_boot_abort();
                                sk_word_t o = _DAT_006be660 * 0x10;
                                *(unsigned int*)(0x6be468 + o) = sk_dart_sid(cap);    /* FUN_0005537c */
                                *(unsigned int*)(0x6be46c + o) = sk_dart_sid2(cap);   /* FUN_000553b0 */
                                sk_logf1("CBootInfo found DART with sid");
                                *(sk_word_t *)(o + 0x6be460) = *cap & 0xffffffffffffffULL;
                                *(sk_word_t *)(0x6b2960 + 0xbd00) += 1;
                                continue;
                            }
                            if (c3 == kind) {
                                if (sk_dart_table(cap) == 0) continue;   /* FUN_000554bc */
                                if (_DAT_006be868 > 0x1f) sk_boot_abort();
                                sk_word_t o = _DAT_006be868 * 0x10;
                                *(unsigned int*)(0x6be670 + o) = sk_dart_tid(cap);   /* FUN_000554f0 */
                                *(unsigned int*)(0x6be674 + o) = sk_dart_tid2(cap);  /* FUN_00055524 */
                                sk_logf1("CBootInfo found DART Table with s");
                                *(sk_word_t *)(o + 0x6be668) = *cap & 0xffffffffffffffULL;
                                *(sk_word_t *)(0x6b2960 + 0xbf08) += 1;
                                continue;
                            }
                        }
                    }
                }
            }
            if (_DAT_006be8b4 > 0xf100001f) {
                _DAT_2bc686b8548 = 0;
                _DAT_2bc686b8550 = _DAT_2bc686b8530;
            }
            sk_logf1("Roottask slide is 0x%llx");
            if (canary != 0xd37afd4bb400012a) sk_stack_fail();
            return;
        }
    }
    sk_boot_abort();
}

/*--------------------------------------------------------------------*/

/* FUN_0006cdf8 @ 0x6cdf8   (est. sk_bootinfo_parse_fwd)
 * Ghidra: void FUN_0006cdf8(undefined8)
 * Wrapper: parses the boot info with the zero-space mapping enabled.
 * Confidence: low
 * Notes: FUN_0006c5cc.
 */
void sk_bootinfo_parse_fwd(sk_word_t c){ sk_bootinfo_parse((long*)c, 1); }

/*--------------------------------------------------------------------*/

/* FUN_0006ce00 @ 0x6ce00   (est. sk_untyped_find_base)
 * Ghidra: long* FUN_0006ce00(long)
 * Walks the boot capability list to find the untyped capability whose base equals the given address and whose type is 0x11; returns its pointer or 0.
 * Confidence: low
 * Notes: DAT_006be890.
 */
long *sk_untyped_find_base(long base)
{
    long *list = sk_boot_caps;
    if (list == (long*)-1) return NULL;
    long *res = NULL;
    for (long *p = list; ; p = (long*)p[1]) {
        long *cur = p;
        for (long n = *p; n != 0; n--) {
            long *cap = cur + 4;
            long *hit = res;
            if (((cur[6] & 0xffffffffffULL) << 0xc) == base
                && *(char*)((char*)cur + 0x27) == 0x11)
                hit = cap;
            res = hit;
            cur += 4;
        }
        if (p[1] == (long)-1) break;
    }
    return res;
}

/*--------------------------------------------------------------------*/

/* FUN_0006ce60 @ 0x6ce60   (est. sk_dt_roottask)
 * Ghidra: undefined8 FUN_0006ce60(void)
 * Returns the roottask global (DAT_2bc686b8378).
 * Confidence: high
 */
sk_word_t sk_dt_roottask(void){ return _DAT_2bc686b8378; }

/*--------------------------------------------------------------------*/

/* FUN_0006cea4 @ 0x6cea4   (est. sk_dev_entry)
 * Ghidra: undefined8 FUN_0006cea4(ulong)
 * Returns the device-table entry at the given index.
 * Confidence: high
 * Notes: Table at 0x2bc686b8450.
 */
sk_word_t sk_dev_entry(sk_word_t i){ return *(sk_word_t *)((i & 0xffffffff) * 8 + 0x2bc686b8450); }

/*--------------------------------------------------------------------*/

/* FUN_0006cec8 @ 0x6cec8   (est. sk_feature_get_a)
 * Ghidra: undefined8 FUN_0006cec8(ulong)
 * Returns a boot feature value (DAT_4d5e91c8a0) when the feature bitmap bit is set and the feature table has the required marker; else 0.
 * Confidence: low
 * Notes: _DAT_006be8b4/_DAT_4d5e91ca80/_DAT_4d5e91c8a0.
 */
sk_word_t sk_feature_get_a(sk_word_t i)
{
    if ((0x1a9f0508 < _DAT_006be8b4) && ((_DAT_4d5e91ca80 >> (i & 0x3f) & 1) != 0))
        return _DAT_4d5e91c8a0;
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006cf0c @ 0x6cf0c   (est. sk_feature_get_b)
 * Ghidra: undefined8 FUN_0006cf0c(ulong)
 * Returns a boot feature value (DAT_9fd86d11a0) when the feature bitmap bit is set and the feature table has the required marker; else 0.
 * Confidence: low
 * Notes: _DAT_006be8b4/_DAT_9fd86d1380/_DAT_9fd86d11a0.
 */
sk_word_t sk_feature_get_b(sk_word_t i)
{
    if ((0x370000a8 < _DAT_006be8b4) && ((_DAT_9fd86d1380 >> (i & 0x3f) & 1) != 0))
        return _DAT_9fd86d11a0;
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006cf50 @ 0x6cf50   (est. sk_untyped_find)
 * Ghidra: undefined8 FUN_0006cf50(ulong)
 * Finds the untyped region containing the given address and returns its base.
 * Confidence: low
 * Notes: s_Could_not_find_untyped_region_fo_005bf258; region tables DAT_006b2960/006b2b18.
 */
sk_word_t sk_untyped_find(sk_word_t addr)
{
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
chk:
    if ((unsigned)i < _DAT_006be8b4)
        return *(sk_word_t *)((i & 0xffffffff) * 0x2e8 + 0x6b2960);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006cfe4 @ 0x6cfe4   (est. sk_untyped_find_base2)
 * Ghidra: undefined8 FUN_0006cfe4(void)
 * Finds the untyped region base for the region containing a resolved address, or the special high-marker base.
 * Confidence: low
 * Notes: s_Could_not_find_untyped_region_fo_005bf258; _DAT_006be8b4/_DAT_2bc686b8528; FUN_004b83bc.
 */
sk_word_t sk_untyped_find_base2(void)
{
    if (0xf100001f < _DAT_006be8b4) return _DAT_2bc686b8528;
    sk_word_t addr = sk_region_addr();           /* FUN_004b83bc */
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
chk:
    if ((unsigned)i < _DAT_006be8b4)
        return *(sk_word_t *)(0x6b2b10 + (i & 0xffffffff) * 0x2e8);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006d024 @ 0x6d024   (est. sk_untyped_base_for)
 * Ghidra: undefined8 FUN_0006d024(ulong)
 * Returns the base of the untyped region containing the given address.
 * Confidence: low
 * Notes: s_Could_not_find_untyped_region_fo_005bf258.
 */
sk_word_t sk_untyped_base_for(sk_word_t addr)
{
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
chk:
    if ((unsigned)i < _DAT_006be8b4)
        return *(sk_word_t *)(0x6b2b10 + (i & 0xffffffff) * 0x2e8);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006d0b8 @ 0x6d0b8   (est. sk_untyped_offset_for)
 * Ghidra: long FUN_0006d0b8(ulong)
 * Returns the offset of the given address within its untyped region.
 * Confidence: low
 * Notes: s_Could_not_find_untyped_region_fo_005bf258.
 */
long sk_untyped_offset_for(sk_word_t addr)
{
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
chk:
    if ((unsigned)i < _DAT_006be8b4)
        return (long)addr - *(long *)(0x6b2b10 + (i & 0xffffffff) * 0x2e8);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006d150 @ 0x6d150   (est. sk_untyped_size_for)
 * Ghidra: undefined8 FUN_0006d150(ulong)
 * Returns the size of the untyped region containing the given address.
 * Confidence: low
 * Notes: s_Could_not_find_untyped_region_fo_005bf258.
 */
sk_word_t sk_untyped_size_for(sk_word_t addr)
{
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
chk:
    if ((unsigned)i < _DAT_006be8b4)
        return *(sk_word_t *)(0x6b2b18 + (i & 0xffffffff) * 0x2e8);
    sk_panic_bad(0, "Could not find untyped region for [addr]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006d1e4 @ 0x6d1e4   (est. sk_untyped_contains)
 * Ghidra: bool FUN_0006d1e4(ulong)
 * Tests whether the given address lies within any untyped region.
 * Confidence: medium
 * Notes: s_Could_not_find_untyped_region_fo_005bf258.
 */
bool sk_untyped_contains(sk_word_t addr)
{
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto done; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= addr && addr < (sk_word_t)(*r + r[-1])) { i = 0; break; }
        i++;
        r += 0x5d;
        i = _DAT_006be8b4;
    } while (_DAT_006be8b4 != i);
done:
    return (unsigned)i < _DAT_006be8b4;
}

/*--------------------------------------------------------------------*/

/* FUN_0006d240 @ 0x6d240   (est. sk_pmm_alloc)
 * Ghidra: ulong FUN_0006d240(ulong,undefined8)
 * Physical-memory allocator: allocates `size` bytes from the boot page bitmap (0x2bc686b8560), updating the allocation cursor and marking allocated pages; supports 1 MiB-aligned allocations and logs an 'ExclavePlatform runtime error' and a 'cbootinfo out of memory, cannot a[llocate]' panic on exhaustion.
 * Confidence: low
 * Notes: Strings s_ExclavePlatform_runtime_error__F_005bfa2e, s_ExclavePlatform_runtime_error__O_005bfa79, s_cbootinfo_out_of_memory__cannot_a_005bf3cc; bitmap DAT_2bc686b8560/8538/8540/8548/8550; CallSupervisor(0); FUN_004b7008/004b83e8/004b8414/004b8440/004b846c.
 */
sk_word_t sk_pmm_alloc(sk_word_t size, sk_word_t flags)
{
    sk_word_t top = _DAT_2bc686b8550;
    sk_word_t hi = _DAT_2bc686b8540;
    sk_word_t lo = _DAT_2bc686b8538;
    if (size == 0) return _DAT_2bc686b8548;
    if (_DAT_2bc686b8550 - _DAT_2bc686b8548 < size) goto oom;
    if ((size & 0xfffff) == 0) {
        sk_word_t cur = _DAT_2bc686b8548;
        if (_DAT_2bc686b8548 <= _DAT_2bc686b8540) cur = _DAT_2bc686b8540;
        cur = cur + 0xfffff & ~0xfffffULL;
        if (_DAT_2bc686b8548 <= _DAT_2bc686b8538) cur = _DAT_2bc686b8548;
        sk_word_t base = _DAT_2bc686b8548;
        sk_word_t fl = flags;
        if (size >> 0x24 != 0) {
            sk_logf1("ExclavePlatform runtime error: F[ailed]");
            base = _DAT_006be880;
            volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
            fl = 1;
            CallSupervisor(0);
        }
        sk_word_t start = cur;
        if (cur <= lo && lo < cur + size) {
            lo = hi + 0xfffff & ~0xfffffULL;
            _DAT_2bc686b8548 = lo;
            if (lo != cur) {
                for (sk_word_t off = 0; off < lo - cur; off += 0x100000) {
                    sk_word_t bm = *(sk_word_t *)(((cur + off) >> 0x1a) * 8 + 0x2bc686b8560);
                    sk_word_t bit = 1ULL << ((cur + off) >> 0x14 & 0x3f);
                    if ((bm & bit) != 0) sk_pmm_bad();
                    *(sk_word_t *)(((cur + off) >> 0x1a) * 8 + 0x2bc686b8560) = bm | bit;
                }
                start = lo;
            }
        }
        if (top - start < size) {
            sk_logf1("ExclavePlatform runtime error: O[ut of memory]");
            base = _DAT_006be880;
            volatile unsigned char *tp = (volatile unsigned char *)__builtin_thread_pointer_ro();
            fl = 1;
            CallSupervisor(0);
        }
        sk_word_t end = start + size;
        if (start + size < start) { sk_pmm_grow2(base, fl); return _DAT_006be880; }
        _DAT_2bc686b8548 = end;
        if ((end & 0xfffff) == 0) {
            sk_word_t base2 = end - size;
            if ((int)flags == 0) return base2;
            for (sk_word_t off = 0; ; off += 0x100000) {
                sk_word_t bm = *(sk_word_t *)(((start + off) >> 0x1a) * 8 + 0x2bc686b8560);
                sk_word_t bit = 1ULL << ((start + off) >> 0x14 & 0x3f);
                if ((bm & bit) != 0) sk_pmm_bad();
                *(sk_word_t *)(((start + off) >> 0x1a) * 8 + 0x2bc686b8560) = bm | bit;
                if (size <= off + 0x100000) return base2;
            }
        }
        sk_pmm_bad2();
    } else {
        sk_pmm_bad3();
    }
    sk_pmm_bad4();
oom:
    sk_panic_bad(0, "cbootinfo out of memory: cannot a[llocate]");
}

/*--------------------------------------------------------------------*/

/* FUN_0006d450 @ 0x6d450   (est. sk_boot_region_base)
 * Ghidra: undefined8 FUN_0006d450(void)
 * Returns the boot region base (DAT_006be880).
 * Confidence: high
 */
sk_word_t sk_boot_region_base(void){ return _DAT_006be880; }

/*--------------------------------------------------------------------*/

/* FUN_0006d45c @ 0x6d45c   (est. sk_boot_free_bytes)
 * Ghidra: ulong FUN_0006d45c(void)
 * Computes the number of free boot-memory bytes (rounded down to 256 KiB) available below the allocation cursor.
 * Confidence: low
 * Notes: DAT_2bc686b8538/8540/8548/8550.
 */
sk_word_t sk_boot_free_bytes(void)
{
    sk_word_t lo = _DAT_2bc686b8538;
    if (_DAT_2bc686b8550 <= _DAT_2bc686b8538) lo = _DAT_2bc686b8550;
    sk_word_t hi = _DAT_2bc686b8540;
    if (_DAT_2bc686b8540 <= _DAT_2bc686b8548) hi = _DAT_2bc686b8548;
    sk_word_t hi_free = _DAT_2bc686b8550 - hi;
    if (_DAT_2bc686b8550 <= _DAT_2bc686b8540) hi_free = 0;
    sk_word_t lo_free = lo - _DAT_2bc686b8548;
    if (lo_free <= hi_free) lo_free = hi_free;
    if (_DAT_2bc686b8538 <= _DAT_2bc686b8548) lo_free = hi_free;
    return lo_free & 0xffffffffffffc000;
}

/*--------------------------------------------------------------------*/

/* FUN_0006d4b4 @ 0x6d4b4   (est. sk_boot_cfg_get)
 * Ghidra: undefined8 FUN_0006d4b4(void)
 * Returns a boot configuration value (DAT_ee50745750) unless the region count has a specific marker value.
 * Confidence: low
 * Notes: _DAT_006be8b4/_DAT_ee50745750.
 */
sk_word_t sk_boot_cfg_get(void)
{
    if (_DAT_006be8b4 != 0x52000328) return _DAT_ee50745750;
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006d4f0 @ 0x6d4f0   (est. sk_boot_dual_region)
 * Ghidra: undefined1 FUN_0006d4f0(void)
 * Returns the dual-region flag (DAT_006be8b0).
 * Confidence: high
 */
unsigned char sk_boot_dual_region(void){ return DAT_006be8b0; }

/*--------------------------------------------------------------------*/

/* FUN_0006d4fc @ 0x6d4fc   (est. sk_region_lo_g)
 * Ghidra: undefined8 FUN_0006d4fc(void)
 * Returns the region low bound (DAT_006be8a0).
 * Confidence: high
 */
sk_word_t sk_region_lo_g(void){ return _DAT_006be8a0; }

/*--------------------------------------------------------------------*/

/* FUN_0006d508 @ 0x6d508   (est. sk_region_lo_cap)
 * Ghidra: undefined8 FUN_0006d508(void)
 * Returns the region low capability (DAT_006be8b8).
 * Confidence: high
 */
sk_word_t sk_region_lo_cap(void){ return _DAT_006be8b8; }

/*--------------------------------------------------------------------*/

/* FUN_0006d514 @ 0x6d514   (est. sk_region_hi_g)
 * Ghidra: undefined8 FUN_0006d514(void)
 * Returns the region high bound (DAT_006be8a8).
 * Confidence: high
 */
sk_word_t sk_region_hi_g(void){ return _DAT_006be8a8; }

/*--------------------------------------------------------------------*/

/* FUN_0006d520 @ 0x6d520   (est. sk_region_hi_cap)
 * Ghidra: undefined8 FUN_0006d520(void)
 * Returns the region high capability (DAT_006be8c0).
 * Confidence: high
 */
sk_word_t sk_region_hi_cap(void){ return _DAT_006be8c0; }

/*--------------------------------------------------------------------*/

/* FUN_0006d52c @ 0x6d52c   (est. sk_boot_device_cap)
 * Ghidra: undefined8 FUN_0006d52c(void)
 * Returns the boot device capability (DAT_006be888).
 * Confidence: high
 */
sk_word_t sk_boot_device_cap(void){ return _DAT_006be888; }

/*--------------------------------------------------------------------*/

/* FUN_0006d558 @ 0x6d558   (est. sk_text_slide_get_sync)
 * Ghidra: undefined8 FUN_0006d558(void)
 * Runs the slide-sync helper then returns the text slide (DAT_006be8c8).
 * Confidence: low
 * Notes: FUN_004b8498.
 */
sk_word_t sk_text_slide_get_sync(void){ sk_slide_sync(); return _DAT_006be8c8; }

/*--------------------------------------------------------------------*/

/* FUN_0006d55c @ 0x6d55c   (est. sk_text_slide_get_sync2)
 * Ghidra: undefined8 FUN_0006d55c(void)
 * Runs the slide-sync helper then returns the text slide (DAT_006be8c8).
 * Confidence: low
 * Notes: FUN_004b8498.
 */
sk_word_t sk_text_slide_get_sync2(void){ sk_slide_sync(); return _DAT_006be8c8; }

/*--------------------------------------------------------------------*/

/* FUN_0006d568 @ 0x6d568   (est. sk_text_slide_get)
 * Ghidra: undefined8 FUN_0006d568(void)
 * Returns the text slide (DAT_006be8c8).
 * Confidence: high
 */
sk_word_t sk_text_slide_get(void){ return _DAT_006be8c8; }

/*--------------------------------------------------------------------*/

/* FUN_0006d574 @ 0x6d574   (est. sk_data_slide_get)
 * Ghidra: undefined8 FUN_0006d574(void)
 * Returns the data slide (DAT_006be8d0).
 * Confidence: high
 */
sk_word_t sk_data_slide_get(void){ return _DAT_006be8d0; }

/*--------------------------------------------------------------------*/

/* FUN_0006d580 @ 0x6d580   (est. sk_dart_find)
 * Ghidra: undefined8 FUN_0006d580(int,int)
 * Finds a DART controller in the boot DART table by its (sid, sid2) pair, returning its capability pointer or 0.
 * Confidence: low
 * Notes: DAT_006be660/006be46c.
 */
sk_word_t sk_dart_find(int sid, int sid2)
{
    if (_DAT_006be660 != 0) {
        int *e = (int*)&DAT_006be46c;
        long n = _DAT_006be660;
        do {
            if (e[-1] == sid && *e == sid2)
                return *(sk_word_t *)(e - 3);
            e += 4; n--;
        } while (n != 0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006d5c8 @ 0x6d5c8   (est. sk_dart_table_find)
 * Ghidra: undefined8 FUN_0006d5c8(int,int)
 * Finds a DART table in the boot DART-table list by its (tid, tid2) pair, returning its capability pointer or 0.
 * Confidence: low
 * Notes: DAT_006be868/006be674.
 */
sk_word_t sk_dart_table_find(int tid, int tid2)
{
    if (_DAT_006be868 != 0) {
        int *e = (int*)&DAT_006be674;
        long n = _DAT_006be868;
        do {
            if (e[-1] == tid && *e == tid2)
                return *(sk_word_t *)(e - 3);
            e += 4; n--;
        } while (n != 0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/* FUN_0006d610 @ 0x6d610   (est. sk_dart_table_clear)
 * Ghidra: void FUN_0006d610(int,int)
 * Clears the DART-table entry matching the given (tid, tid2) pair.
 * Confidence: low
 * Notes: DAT_006be868/006be674.
 */
void sk_dart_table_clear(int tid, int tid2)
{
    if (_DAT_006be868 != 0) {
        int *e = (int*)&DAT_006be674;
        long n = _DAT_006be868;
        do {
            if (e[-1] == tid && *e == tid2) { e[-3] = 0; e[-2] = 0; return; }
            e += 4; n--;
        } while (n != 0);
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006d654 @ 0x6d654   (est. sk_bootinfo_set_root)
 * Ghidra: void FUN_0006d654(undefined8)
 * Sets the boot-info root pointer (DAT_006be898).
 * Confidence: high
 */
void sk_bootinfo_set_root(sk_word_t r){ _DAT_006be898 = r; }

/*--------------------------------------------------------------------*/

/* FUN_0006d660 @ 0x6d660   (est. sk_bootinfo_root_call)
 * Ghidra: void FUN_0006d660(void)
 * Invokes a helper on the boot-info root.
 * Confidence: low
 * Notes: FUN_0005562c.
 */
void sk_bootinfo_root_call(void){ sk_root_helper(_DAT_006be898); }

/*--------------------------------------------------------------------*/

/* FUN_0006d66c @ 0x6d66c   (est. sk_bootinfo_set_range)
 * Ghidra: void FUN_0006d66c(undefined8,undefined8)
 * Records the boot-info (low,high) range (DAT_006be8d8/006be8e0).
 * Confidence: high
 */
void sk_bootinfo_set_range(sk_word_t lo, sk_word_t hi){ _DAT_006be8d8 = lo; _DAT_006be8e0 = hi; }

/*--------------------------------------------------------------------*/

/* FUN_0006d680 @ 0x6d680   (est. sk_bootinfo_call_a)
 * Ghidra: void FUN_0006d680(void)
 * Invokes a helper on the boot-info root.
 * Confidence: low
 * Notes: FUN_00055660.
 */
void sk_bootinfo_call_a(void){ sk_root_helper2(_DAT_006be898); }

/*--------------------------------------------------------------------*/

/* FUN_0006d68c @ 0x6d68c   (est. sk_bootinfo_call_b)
 * Ghidra: void FUN_0006d68c(void)
 * Invokes a helper on the boot-info root.
 * Confidence: low
 * Notes: FUN_00055694.
 */
void sk_bootinfo_call_b(void){ sk_root_helper3(_DAT_006be898); }

/*--------------------------------------------------------------------*/

/* FUN_0006d698 @ 0x6d698   (est. sk_pmm_bitmap)
 * Ghidra: undefined8 FUN_0006d698(void)
 * Returns the physical-memory bitmap base 0x2bc686b8560.
 * Confidence: high
 */
sk_word_t sk_pmm_bitmap(void){ return 0x2bc686b8560; }

/*--------------------------------------------------------------------*/

/* FUN_0006d6b8 @ 0x6d6b8   (est. sk_pmm_granule)
 * Ghidra: undefined8 FUN_0006d6b8(void)
 * Returns the PMM granule count 0x100.
 * Confidence: high
 */
sk_word_t sk_pmm_granule(void){ return 0x100; }

/*--------------------------------------------------------------------*/

/* FUN_0006d6c0 @ 0x6d6c0   (est. sk_err_rec_fill_b)
 * Ghidra: void FUN_0006d6c0(undefined8*,byte)
 * Fills a 4-word record with the canonical L4_ErrorCode* string for the given code (0-9), or a generic fallback above 9.
 * Confidence: high
 * Notes: Strings s_L4_ErrorCodeSuccess_004bf030..; fallback DAT_004bf170/004bf180/004bf188.
 */
void sk_err_rec_fill_b(sk_word_t *rec, unsigned char code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess","L4_ErrorCodePreempted","L4_ErrorCodeCanceled",
        "L4_ErrorCodeTruncated","L4_ErrorCodeCapInvalid","L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid","L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid","L4_ErrorCodePermissionInvalid"
    };
    if (code > 9) {
        rec[0]=_DAT_004bf170; rec[1]=uRam00000000004bf178;
        rec[2]=_DAT_004bf180; rec[3]=uRam00000000004bf188;
        sk_err_rec_print(rec);
        return;
    }
    const char *s = names[code];
    rec[0]=*(sk_word_t*)s; rec[1]=*(sk_word_t*)(s+8); rec[2]=*(sk_word_t*)(s+0x10); rec[3]=*(sk_word_t*)(s+0x18);
}

/*--------------------------------------------------------------------*/

/* FUN_0006d7d0 @ 0x6d7d0   (est. sk_region_usage_update)
 * Ghidra: void FUN_0006d7d0(long)
 * Updates an untyped region's used-range bounds: given a frame descriptor, it locates the region containing the frame's base and expands the region's [low, high] used range to include it.
 * Confidence: low
 * Notes: DAT_006be8b4/006b2b10/006b2b18/006b2b20/006b2b28.
 */
void sk_region_usage_update(long desc)
{
    sk_word_t base = *(sk_word_t *)((char*)desc + 8) & 0xffffffffffffffULL;
    sk_word_t i;
    if (_DAT_006be8b4 == 0) { i = 0; goto chk; }
    i = 0;
    long *r = (long*)&DAT_006b2b18;
    do {
        if ((sk_word_t)r[-1] <= base && base < (sk_word_t)(*r + r[-1])) goto chk;
        i++; r += 0x5d;
    } while (_DAT_006be8b4 != i);
    return;
chk:
    if ((unsigned)i < _DAT_006be8b4) {
        sk_word_t off = (i & 0xffffffff) * 0x2e8;
        sk_word_t rel = base - *(long *)(0x6b2b10 + off);
        sk_word_t hi = rel + 0x4000;
        sk_word_t lo = *(sk_word_t *)(0x6b2b20 + off);
        sk_word_t hi2 = *(sk_word_t *)(0x6b2b28 + off);
        if (hi2 < hi || rel < lo) {
            if (lo > rel) lo = rel;
            if (hi2 > hi) hi = hi2;
            *(sk_word_t *)(0x6b2b20 + off) = lo;
            *(sk_word_t *)(0x6b2b28 + off) = hi;
        }
    }
}

/*--------------------------------------------------------------------*/

/* FUN_0006d870 @ 0x6d870   (est. sk_err_rec_fill_b0)
 * Ghidra: void FUN_0006d870(void)
 * Wrapper: fills an error record (stack offset 0x10).
 * Confidence: low
 * Notes: FUN_0006d6c0.
 */
void sk_err_rec_fill_b0(void){ sk_err_rec_fill_b((sk_word_t*)0x10, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006d890 @ 0x6d890   (est. sk_err_rec_fill_b1)
 * Ghidra: void FUN_0006d890(void)
 * Wrapper: fills an error record on the stack.
 * Confidence: low
 * Notes: FUN_0006d6c0.
 */
void sk_err_rec_fill_b1(void){ sk_err_rec_fill_b(0, 0); }

/*--------------------------------------------------------------------*/

/* FUN_0006d8a4 @ 0x6d8a4   (est. sk_vspace_region_init)
 * Ghidra: void FUN_0006d8a4(long)
 * Initializes a vspace/region object: allocates a 0x4000-byte page table (kind 0x11/0x1808) plus a 0x50-byte instance, primes the region's page-table pointer and base, and fills the region's entry descriptor (base, limit, links), breaking if the descriptor is absent.
 * Confidence: low
 * Notes: FUN_00086440/00086590/00085a54/0036a9d4/0036a940/0036b270/0036b118/000f6d20/00034f70/0006a4c0/000026e8; SoftwareBreakpoint(1,0x6da1c).
 */
void sk_vspace_region_init(void *obj)
{
    sk_word_t ct = sk_ctx_t();                  /* FUN_00086440 */
    sk_word_t rt = sk_alloc_rt(ct, 0x64e1c0);   /* FUN_0036a9d4 */
    sk_word_t mt = sk_ctx_m();                  /* FUN_00086590 */
    sk_alloc_obj(mt, 0x50, 7);
    long *pt = (long*)sk_alloc_pagetable(0, 0x4000, 0x11, 0x1808, 0);   /* FUN_00085a54 */
    void *as = sk_amx_state();                  /* FUN_00034f70 */
    sk_word_t b0 = *(sk_word_t *)((char*)obj + 0x18);
    sk_word_t b1 = *(sk_word_t *)((char*)obj + 0x20);
    sk_word_t adj = sk_alloc_align_adjust(obj, b0);
    sk_word_t r = sk_region_map(as, b0, b1, adj);   /* FUN_000f6d20 */
    *(void **)((char*)unaff_x20 + 0x18) = as;
    *(sk_word_t *)((char*)unaff_x20 + 0x20) = r;
    *(long **)((char*)unaff_x20 + 0x10) = pt;
    void (*map)(int, void*) = *(void(**)(int,void*))(*pt + 0x90);
    sk_alloc_pages(pt, 0);
    map(0, as);
    unsigned int *desc = (unsigned int*)(*(sk_word_t(*)(void))(*pt + 0xe0))();
    if (desc == NULL) sk_breakpoint(1, 0x6da1c);
    desc[2] = 0;
    desc[0] = 0;
    *(sk_word_t*)(desc + 4) = *(sk_word_t*)((char*)unaff_x20 + 0x20);
    *(sk_word_t*)(desc + 6) = 0;
    *(sk_word_t*)(desc + 8) = 0;
    *(sk_word_t*)(desc + 10) = 0;
    sk_free(pt);
    sk_report_finish(obj);                      /* FUN_000026e8 */
}

/*--------------------------------------------------------------------*/

/* FUN_0006da64 @ 0x6da64   (est. sk_get0_2)
 * Ghidra: undefined8 FUN_0006da64(void)
 * Returns 0 (thunk to 0x0456c).
 * Confidence: medium
 * Notes: thunk_FUN_0000456c.
 */
sk_word_t sk_get0_2(void){ return 0; }

/*--------------------------------------------------------------------*/

/* FUN_0006da68 @ 0x6da68   (est. sk_commpage_mint)
 * Ghidra: void FUN_0006da68(void)
 * Mints the exclave commpage capability: resolves the commpage base from the boot data, allocates the AMX/context state, and maps the commpage; on failure it prints a 'failed to mint commpage cap' diagnostic ('base %s = ...') and panics.
 * Confidence: low
 * Notes: Strings s_failed_to_mint_commpage_cap__005bfb10; FUN_0005ace4/00034f70/00034a2c/0006f130/0006e6dc/0006eb1c/0006f6e0/0006f768/00027724/00205844/002a4ab4; thunk_FUN_002acbb8.
 */
void sk_commpage_mint(void)
{
    *(sk_word_t*)((char*)unaff_x20 + 0x10) = 0;
    void *bd = sk_boot_data2();                 /* FUN_0005ace4 */
    *(sk_word_t *)((char*)unaff_x20 + 0x20) = *(sk_word_t *)((char*)bd + 0x10);
    void *as = sk_amx_state();                  /* FUN_00034f70 */
    *(void **)((char*)unaff_x20 + 0x18) = as;
    if (as == 0) {
        sk_panic_msg0("failed to mint commpage cap");   /* FUN_0006f6e0 */
        sk_panic_halt2();
    } else {
        void *pt = sk_pt_ctx();
        sk_commpage_map(pt, bd, as);            /* FUN_0006f130 */
        int st = sk_commpage_status();          /* FUN_0006e6dc */
        if (st == 0) return;
        sk_word_t rec[2] = {0, 0xe000000000000000};
        sk_report_lock(0x36);
        sk_report_emit(0xd000000000000022, 0x80000000005bfb30);
        void (*p1)(sk_word_t,sk_word_t) = (void(*)(sk_word_t,sk_word_t))sk_boot_obj_helper2(0x671df8);
        p1(0x677830, 0x671df8);
        sk_report_emit(0, 0);
        sk_report_free(0);
        sk_report_emit(0x3d6573616220, 0xe600000000000000);   /* ' base=' */
        void (*p2)(sk_word_t,sk_word_t) = (void(*)(sk_word_t,sk_word_t))sk_boot_obj_helper2(0x671848);
        p2(0x677790, 0x671848);
        sk_report_emit(0, 0);
        sk_report_free(0);
        sk_report_emit(0x203d20727265203a, 0xe800000000000000);  /* ': err = ' */
        sk_word_t v = sk_eb();                  /* FUN_0006eb1c */
        sk_format2(&st, &rec, v, 0x6756a8, 0x66e1b8);
        sk_panic_msg0(0);
        sk_panic_halt2();
    }
    sk_fatal0();
}
/* FUN_0006dc80 @ 0x6dc80   (est. sk_commpage_slot_set)
 * Ghidra: void FUN_0006dc80(undefined8)
 * Stores a value into the commpage slot: resolves the commpage descriptor and writes the value at offset +0x28; panics if the commpage is not present.
 * Confidence: low
 * Notes: Strings s_InternalExclaveLauncher_Commpage_005bfab0; SoftwareBreakpoint(1,0x6dcf8); FUN_0036b270/0036b118/0006f6e0/0006f768.
 */
void sk_commpage_slot_set(sk_word_t v)
{
    long *cp = *(long **)((char*)unaff_x20 + 0x10);
    if (cp == NULL) {
        sk_panic_msg0(s_InternalExclaveLauncher_Commpage + 0x10);
        sk_panic_halt2();
        sk_fatal0();
    }
    void (*get)(void) = *(void(**)(void))(*cp + 0xe0);
    sk_alloc_pages(cp, 0);
    long d = (long)get();
    if (d != 0) {
        *(sk_word_t *)((char*)d + 0x28) = v;
        sk_free(cp);
        return;
    }
    sk_breakpoint(1, 0x6dcf8);
}
/* FUN_0006dd34 @ 0x6dd34   (est. sk_commpage_mint_cap)
 * Ghidra: undefined8 FUN_0006dd34(ulong)
 * Mints a commpage capability: requests the frame from the supervisor (0x6de38) with the given mode and returns the AMX state; on failure it runs the 'mint commpage cap' panic path.
 * Confidence: low
 * Notes: FUN_00034f70/0006de38/00027724/0006f6e0/0006f768; thunk_FUN_002acbb8; FUN_002a4ab4/001afa84.
 */
sk_word_t sk_commpage_mint_cap(sk_word_t mode)
{
    void *as = sk_amx_state();
    long r = sk_cs_map(*(sk_word_t *)((char*)unaff_x20 + 0x18), as, mode & 1);  /* FUN_0006de38 */
    if (r == 0) return (sk_word_t)as;
    sk_report_lock(0x1f);
    sk_report_free(0xe000000000000000);
    void (*p)(sk_word_t,sk_word_t) = (void(*)(sk_word_t,sk_word_t))sk_boot_obj_helper2(0x671df8);
    p(0x677830, 0x671df8);
    sk_report_emit(0, 0);
    sk_report_free(0);
    sk_panic_msg0(0);
    sk_panic_halt2();
    sk_fatal0();
}
/* FUN_0006de38 @ 0x6de38   (est. sk_cs_map)
 * Ghidra: void FUN_0006de38(undefined8,undefined8,undefined8)
 * Programs the RO frame with the mode word and issues CallSupervisor(3) to map a context/frame.
 * Confidence: low
 * Notes: CallSupervisor(3).
 */
void sk_cs_map(sk_word_t a, sk_word_t b, sk_word_t mode)
{
    volatile sk_word_t *tp = (volatile sk_word_t*)__builtin_thread_pointer_ro();
    *tp = mode;
    CallSupervisor(3);
}
/* FUN_0006de48 @ 0x6de48   (est. sk_vspace_region_init2)
 * Ghidra: void FUN_0006de48(undefined8)
 * Initializes the vspace region: builds the region object (0x6e7c0), publishes it, and runs the region init.
 * Confidence: low
 * Notes: FUN_0006e7c0/0006f774/0006d8a4.
 */
void sk_vspace_region_init2(sk_word_t a)
{
    sk_word_t obj[5];
    sk_vspace_build(a, obj);                    /* FUN_0006e7c0 */
    sk_vspace_publish(obj);                     /* FUN_0006f774 */
    sk_vspace_region_init(obj);                 /* FUN_0006d8a4 */
}
/* FUN_0006de84 @ 0x6de84   (est. sk_commpage_mint2)
 * Ghidra: void FUN_0006de84(void)
 * Publishes the vspace then mints the commpage.
 * Confidence: low
 * Notes: FUN_0006f774/0006da68.
 */
void sk_commpage_mint2(void){ sk_vspace_publish(0); sk_commpage_mint(); }
/* FUN_0006deac @ 0x6deac   (est. sk_obj_free_p10)
 * Ghidra: void FUN_0006deac(void)
 * Frees the object at +0x10.
 * Confidence: low
 * Notes: FUN_0036b118.
 */
void sk_obj_free_p10(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); }
/* FUN_0006deb0 @ 0x6deb0   (est. sk_obj_free_p10b)
 * Ghidra: void FUN_0006deb0(void)
 * Frees the object at +0x10.
 * Confidence: low
 * Notes: FUN_0036b118.
 */
void sk_obj_free_p10b(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); }
/* FUN_0006decc @ 0x6decc   (est. sk_obj_free_p10_tear)
 * Ghidra: void FUN_0006decc(void)
 * Frees the object at +0x10 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b6ac.
 */
void sk_obj_free_p10_tear(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); sk_alloc_teardown(); }
/* FUN_0006ded0 @ 0x6ded0   (est. sk_obj_free_p10_tear2)
 * Ghidra: void FUN_0006ded0(void)
 * Frees the object at +0x10 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b6ac.
 */
void sk_obj_free_p10_tear2(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); sk_alloc_teardown(); }
/* FUN_0006df18 @ 0x6df18   (est. sk_dt_empty_thunk)
 * Ghidra: undefined* FUN_0006df18(void)
 * Returns the empty DT/report buffer (thunk to 0x6f6b4).
 * Confidence: medium
 * Notes: thunk_FUN_0006f6b4.
 */
void *sk_dt_empty_thunk(void){ return &DAT_00657778; }

/*--------------------------------------------------------------------*/

/* FUN_0006df24 @ 0x6df24   (est. sk_commpage_kind)
 * Ghidra: undefined8 FUN_0006df24(void)
 * Returns the commpage kind constant 0x1e.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_commpage_kind(void){ return 0x1e; }
/* FUN_0006df48 @ 0x6df48   (est. sk_commpage_obj_alloc)
 * Ghidra: void FUN_0006df48(undefined8*)
 * Allocates a commpage descriptor object, recording the context type and object template.
 * Confidence: low
 * Notes: FUN_00086440/0036a9d4.
 */
void sk_commpage_obj_alloc(sk_word_t *out)
{
    sk_word_t ct = sk_ctx_t();
    sk_word_t rt = sk_alloc_rt(ct, 0x64e1c0);
    out[3] = ct;
    out[4] = 0x65f998;
    out[0] = rt;
}
/* FUN_0006dfc8 @ 0x6dfc8   (est. sk_ctx3_init)
 * Ghidra: void FUN_0006dfc8(void)
 * Builds a dispatch object (0x404d0 + 0x6f6d0 + 0x6f69c).
 * Confidence: low
 * Notes: FUN_001404d0/0006f6d0/0006f69c/001f0130.
 */
void sk_ctx3_init(void){ sk_disp0(0); sk_word_t v = sk_disp_a(); sk_disp_b(v, 0x6753a0); sk_disp_done(); }
/* FUN_0006dfcc @ 0x6dfcc   (est. sk_ctx3_init2)
 * Ghidra: void FUN_0006dfcc(void)
 * Builds a dispatch object (0x404d0 + 0x6f6d0 + 0x6f69c).
 * Confidence: low
 * Notes: FUN_001404d0/0006f6d0/0006f69c/001f0130.
 */
void sk_ctx3_init2(void){ sk_disp0(0); sk_word_t v = sk_disp_a(); sk_disp_b(v, 0x6753a0); sk_disp_done(); }
/* FUN_0006dff8 @ 0x6dff8   (est. sk_ctx4_init)
 * Ghidra: void FUN_0006dff8(void)
 * Builds a dispatch object (resolve 0x64e1e0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f684/001f0130.
 */
void sk_ctx4_init(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006dffc @ 0x6dffc   (est. sk_ctx4_init2)
 * Ghidra: void FUN_0006dffc(void)
 * Builds a dispatch object (resolve 0x64e1e0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f684/001f0130.
 */
void sk_ctx4_init2(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006e064 @ 0x6e064   (est. sk_boot_one)
 * Ghidra: undefined8 FUN_0006e064(void)
 * Returns 1.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_boot_one(void){ return 1; }
/* FUN_0006e06c @ 0x6e06c   (est. sk_boot_dt_slot)
 * Ghidra: undefined8* FUN_0006e06c(void)
 * Returns the boot DT slot pointer (DAT_006577e0).
 * Confidence: low
 * Notes: sk_word_t *sk_boot_dt_slot(void){ return &DAT_006577e0; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006e078 @ 0x6e078   (est. sk_zero16)
 * Ghidra: undefined1[16] FUN_0006e078(void)
 * Returns a 16-byte zero value (thunk to 0x19858).
 * Confidence: medium
 * Notes: thunk_FUN_00019858.
 */
sk_word_t sk_zero16(void){ return 0; }


/* FUN_0006e0d8 @ 0x6e0d8   (est. sk_ctx5_init)
 * Ghidra: void FUN_0006e0d8(void)
 * Builds a dispatch object (resolve 0x64e1d0 + 0x6f6d0 + 0x6f69c).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f69c/001f0130.
 */
void sk_ctx5_init(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_b(v, 0x6753a0); sk_disp_done(); }
/* FUN_0006e0dc @ 0x6e0dc   (est. sk_ctx5_init2)
 * Ghidra: void FUN_0006e0dc(void)
 * Builds a dispatch object (resolve 0x64e1d0 + 0x6f6d0 + 0x6f69c).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f69c/001f0130.
 */
void sk_ctx5_init2(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_b(v, 0x6753a0); sk_disp_done(); }
/* FUN_0006e164 @ 0x6e164   (est. sk_commpage_alloc2)
 * Ghidra: long FUN_0006e164(void)
 * Allocates a 0x18-byte commpage object and primes its data slot.
 * Confidence: low
 * Notes: FUN_000ec8f8/0036a940/0036a804.
 */
long sk_commpage_alloc2(void)
{
    sk_word_t ct = sk_ctx2();                   /* FUN_000ec8f8 */
    long o = (long)sk_alloc_obj(ct, 0x18, 7);
    *(sk_word_t *)(o + 0x10) = sk_alloc_word(0x10, ~0ULL);   /* FUN_0036a804 */
    return o;
}
/* FUN_0006e20c @ 0x6e20c   (est. sk_ctx6_init)
 * Ghidra: void FUN_0006e20c(void)
 * Builds a dispatch object and stores the result.
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f69c/001f0130/00083c34/0036a940.
 */
void sk_ctx6_init(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_b(v, 0x6753a0); v = sk_disp_done(); sk_word_t ct = sk_ctx6(); sk_alloc_obj(ct, 0x18, 7); }
/* FUN_0006e27c @ 0x6e27c   (est. sk_ctx7_init)
 * Ghidra: void FUN_0006e27c(void)
 * Builds a dispatch object (0x773f0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_000773f0/0006f6d0/0006f684/001f0130.
 */
void sk_ctx7_init(void){ sk_disp0(0x773f0); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006e280 @ 0x6e280   (est. sk_ctx7_init2)
 * Ghidra: void FUN_0006e280(void)
 * Builds a dispatch object (0x773f0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_000773f0/0006f6d0/0006f684/001f0130.
 */
void sk_ctx7_init2(void){ sk_disp0(0x773f0); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006e2ac @ 0x6e2ac   (est. sk_commpage_alloc3)
 * Ghidra: long FUN_0006e2ac(void)
 * Allocates a 0x20-byte commpage object, priming its data and link slots.
 * Confidence: low
 * Notes: FUN_000773f0/0036a940/0006f70c/001f0130.
 */
long sk_commpage_alloc3(void)
{
    sk_word_t ct = sk_ctx7(0);
    long o = (long)sk_alloc_obj(ct, 0x20, 7);
    sk_commpage_prep();                         /* FUN_0006f70c */
    *(sk_word_t *)(o + 0x10) = sk_disp_done(&DAT_00657778);
    *(void **)(o + 0x18) = &DAT_00657778;
    return o;
}
/* FUN_0006e2fc @ 0x6e2fc   (est. sk_ctx8_init)
 * Ghidra: void FUN_0006e2fc(void)
 * Builds a dispatch object (resolve 0x64e1f0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f684/001f0130.
 */
void sk_ctx8_init(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006e300 @ 0x6e300   (est. sk_ctx8_init2)
 * Ghidra: void FUN_0006e300(void)
 * Builds a dispatch object (resolve 0x64e1f0 + 0x6f6d0 + 0x6f684).
 * Confidence: low
 * Notes: FUN_00002534/0006f6d0/0006f684/001f0130.
 */
void sk_ctx8_init2(void){ sk_boot_enter(); sk_word_t v = sk_disp_a(); sk_disp_c(v, 0x677790); sk_disp_done(); }
/* FUN_0006e340 @ 0x6e340   (est. sk_ctx9_init)
 * Ghidra: void FUN_0006e340(void)
 * Registers a dispatch pair (0x665f60, 0x665cd8).
 * Confidence: low
 * Notes: FUN_0014aea4.
 */
void sk_ctx9_init(void){ sk_disp_pair(0x665f60, 0x665cd8); }
/* FUN_0006e380 @ 0x6e380   (est. sk_ctxa_init)
 * Ghidra: void FUN_0006e380(void)
 * Allocates a dispatch object (0xaa6d0, size 0x10).
 * Confidence: low
 * Notes: FUN_000aa6d0/0036a940.
 */
void sk_ctxa_init(void){ sk_word_t ct = sk_ctxa(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e384 @ 0x6e384   (est. sk_ctxa_init2)
 * Ghidra: void FUN_0006e384(void)
 * Allocates a dispatch object (0xaa6d0, size 0x10).
 * Confidence: low
 * Notes: FUN_000aa6d0/0036a940.
 */
void sk_ctxa_init2(void){ sk_word_t ct = sk_ctxa(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e3a8 @ 0x6e3a8   (est. sk_ctxb_init)
 * Ghidra: void FUN_0006e3a8(void)
 * Allocates a dispatch object (0xec964, size 0x10).
 * Confidence: low
 * Notes: FUN_000ec964/0036a940.
 */
void sk_ctxb_init(void){ sk_word_t ct = sk_ctxb(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e3ac @ 0x6e3ac   (est. sk_ctxb_init2)
 * Ghidra: void FUN_0006e3ac(void)
 * Allocates a dispatch object (0xec964, size 0x10).
 * Confidence: low
 * Notes: FUN_000ec964/0036a940.
 */
void sk_ctxb_init2(void){ sk_word_t ct = sk_ctxb(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e3d0 @ 0x6e3d0   (est. sk_ctxc_init)
 * Ghidra: void FUN_0006e3d0(void)
 * Allocates a dispatch object (0x6f800, size 0x10).
 * Confidence: low
 * Notes: FUN_0006f800/0036a940.
 */
void sk_ctxc_init(void){ sk_word_t ct = sk_ctxc(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e3d4 @ 0x6e3d4   (est. sk_ctxc_init2)
 * Ghidra: void FUN_0006e3d4(void)
 * Allocates a dispatch object (0x6f800, size 0x10).
 * Confidence: low
 * Notes: FUN_0006f800/0036a940.
 */
void sk_ctxc_init2(void){ sk_word_t ct = sk_ctxc(); sk_alloc_obj(ct, 0x10, 7); }
/* FUN_0006e42c @ 0x6e42c   (est. sk_get4_0456c)
 * Ghidra: void FUN_0006e42c(undefined4*)
 * Fetches a 32-bit value via the helper 0x0456c.
 * Confidence: low
 * Notes: FUN_0000456c.
 */
void sk_get4_0456c(unsigned int *out){ *out = sk_get4_0456c_x(); }
/* FUN_0006e460 @ 0x6e460   (est. sk_get4_84cc4)
 * Ghidra: void FUN_0006e460(undefined4*,undefined4*)
 * Fetches a 32-bit value via 0x84cc4.
 * Confidence: low
 * Notes: FUN_00084cc4.
 */
void sk_get4_84cc4(unsigned int *o, unsigned int *a){ *o = sk_h_84cc4(*a, *unaff_x20); }
/* FUN_0006e490 @ 0x6e490   (est. sk_get4_af4d8)
 * Ghidra: void FUN_0006e490(undefined4*,undefined4*)
 * Fetches a 32-bit value via 0xaf4d8.
 * Confidence: low
 * Notes: FUN_000af4d8.
 */
void sk_get4_af4d8(unsigned int *o, unsigned int *a){ *o = sk_h_af4d8(*a, *unaff_x20); }
/* FUN_0006e4c8 @ 0x6e4c8   (est. sk_get8_af56c)
 * Ghidra: void FUN_0006e4c8(undefined4*,undefined4*)
 * Fetches a 64-bit value via 0xaf56c and stores it as a 40-bit (value, hi) pair.
 * Confidence: low
 * Notes: FUN_000af56c.
 */
void sk_get8_af56c(unsigned int *o, unsigned int *a){ sk_word_t v = sk_h_af56c(*a); o[0]=(unsigned int)v; ((char*)o)[1]=(char)(v>>32); }
/* FUN_0006e4fc @ 0x6e4fc   (est. sk_get8_af5fc)
 * Ghidra: void FUN_0006e4fc(undefined4*,undefined4*)
 * Fetches a 64-bit value via 0xaf5fc and stores it as a pair.
 * Confidence: low
 * Notes: FUN_000af5fc.
 */
void sk_get8_af5fc(unsigned int *o, unsigned int *a){ sk_word_t v = sk_h_af5fc(*a); o[0]=(unsigned int)v; ((char*)o)[1]=(char)(v>>32); }
/* FUN_0006e540 @ 0x6e540   (est. sk_get4_85754)
 * Ghidra: void FUN_0006e540(undefined4*,undefined4*)
 * Fetches a 32-bit value via 0x85754.
 * Confidence: low
 * Notes: FUN_00085754.
 */
void sk_get4_85754(unsigned int *o, unsigned int *a){ *o = sk_h_85754(*a, *unaff_x20); }
/* FUN_0006e5b8 @ 0x6e5b8   (est. sk_ctx_call)
 * Ghidra: void FUN_0006e5b8(undefined8)
 * Saves the context, runs the helper, restores.
 * Confidence: low
 * Notes: FUN_001a84f4/0022995c/001a8564.
 */
void sk_ctx_call(sk_word_t a){ sk_ctx_save(0); sk_ctx_call_h(a); sk_ctx_restore(); }
/* FUN_0006e608 @ 0x6e608   (est. sk_ctx_call_h)
 * Ghidra: void FUN_0006e608(undefined8,undefined8)
 * Runs the helper with the second argument.
 * Confidence: low
 * Notes: FUN_0022995c.
 */
void sk_ctx_call_h(sk_word_t a, sk_word_t b){ sk_ctx_call_h(b); }
/* FUN_0006e638 @ 0x6e638   (est. sk_ctx_call2)
 * Ghidra: void FUN_0006e638(undefined8,undefined8)
 * Saves the context, runs the helper with the second argument, restores.
 * Confidence: low
 * Notes: FUN_001a84f4/0022995c/001a8564.
 */
void sk_ctx_call2(sk_word_t a, sk_word_t b){ sk_ctx_save(0); sk_ctx_call_h(b); sk_ctx_restore(); }
/* FUN_0006e688 @ 0x6e688   (est. sk_get4_aae60)
 * Ghidra: void FUN_0006e688(undefined4*)
 * Fetches a 32-bit value via 0xaae60.
 * Confidence: low
 * Notes: FUN_000aae60.
 */
void sk_get4_aae60(unsigned int *o){ *o = sk_h_aae60(); }
/* FUN_0006e6b0 @ 0x6e6b0   (est. sk_get16_6e6dc)
 * Ghidra: void FUN_0006e6b0(undefined2*,undefined1*)
 * Fetches a 16-bit value via the byte helper 0x6e6dc.
 * Confidence: low
 * Notes: FUN_0006e6dc.
 */
void sk_get16_6e6dc(unsigned short *o, unsigned char *a){ *o = sk_byte_ident(*a); }
/* FUN_0006e6dc @ 0x6e6dc   (est. sk_byte_ident)
 * Ghidra: undefined1 FUN_0006e6dc(undefined1)
 * Returns the input byte unchanged (identity).
 * Confidence: low
 * Notes: unsigned char sk_byte_ident(unsigned char b){ return b; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006e6e4 @ 0x6e6e4   (est. sk_get_1a1c8)
 * Ghidra: void FUN_0006e6e4(undefined1*)
 * Fetches a value via 0x1a1c8.
 * Confidence: low
 * Notes: FUN_0001a1c8.
 */
void sk_get_1a1c8(unsigned char *o){ *o = sk_h_1a1c8(*unaff_x20); }
/* FUN_0006e710 @ 0x6e710   (est. sk_get8_6e744)
 * Ghidra: void FUN_0006e710(undefined4*,undefined4*)
 * Fetches a 64-bit value via 0x6e744 and stores it as a pair.
 * Confidence: low
 * Notes: FUN_0006e744.
 */
void sk_get8_6e744(unsigned int *o, unsigned int *a){ sk_word_t v = sk_u32_ident(*a); o[0]=(unsigned int)v; ((char*)o)[1]=(char)(v>>32); }
/* FUN_0006e744 @ 0x6e744   (est. sk_u32_ident)
 * Ghidra: undefined4 FUN_0006e744(undefined4)
 * Returns the input 32-bit value unchanged (identity).
 * Confidence: low
 * Notes: unsigned int sk_u32_ident(unsigned int v){ return v; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006e74c @ 0x6e74c   (est. sk_get4_1a1c8)
 * Ghidra: void FUN_0006e74c(undefined4*)
 * Fetches a 32-bit value via 0x1a1c8.
 * Confidence: low
 * Notes: FUN_0001a1c8.
 */
void sk_get4_1a1c8(unsigned int *o){ *o = sk_h_1a1c8(*unaff_x20); }
/* FUN_0006e778 @ 0x6e778   (est. sk_value_check16)
 * Ghidra: undefined1[16] FUN_0006e778(long)
 * Validates the value is within 16 words (acquiring the report lock otherwise), returning the check result.
 * Confidence: low
 * Notes: FUN_002a4ab4.
 */
sk_word_t sk_value_check16(long v)
{
    if (v > 0xf) sk_report_lock(0);
    return (sk_word_t)0xe000000000000000 << 40;
}
/* FUN_0006e7c0 @ 0x6e7c0   (est. sk_obj_copy_field)
 * Ghidra: long FUN_0006e7c0(long,long)
 * Copies an object's identity and data fields into a new object via the allocator's copy constructor.
 * Confidence: low
 * Notes: Indirect call through *(obj+0x18)-8.
 */
long sk_obj_copy_field(long src, long dst)
{
    long id = *(long *)((char*)src + 0x18);
    *(long *)((char*)dst + 0x18) = id;
    *(sk_word_t *)((char*)dst + 0x20) = *(sk_word_t *)((char*)src + 0x20);
    (*(void(**)(long,long))**(void***)((char*)id - 8))(dst, src);
    return dst;
}
/* FUN_0006e81c @ 0x6e81c   (est. sk_ctx_dt)
 * Ghidra: undefined1[16] FUN_0006e81c(void)
 * Returns the DT context token 0x64e210.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_ctx_dt(void){ return 0x64e210; }
/* FUN_0006e82c @ 0x6e82c   (est. sk_ctx_register)
 * Ghidra: void FUN_0006e82c(undefined8)
 * Registers a context via 0x6f0e4 with the 0xe3d6c symbol.
 * Confidence: low
 * Notes: FUN_0006f0e4/000e3d6c.
 */
void sk_ctx_register(sk_word_t a){ sk_ctx_reg(a, sk_sym_e3d6c); }
/* FUN_0006e844 @ 0x6e844   (est. sk_ctx_register2)
 * Ghidra: void FUN_0006e844(undefined8)
 * Registers a context via 0x6f0e4 with the 0xe3dd0 symbol.
 * Confidence: low
 * Notes: FUN_0006f0e4/000e3dd0.
 */
void sk_ctx_register2(sk_word_t a){ sk_ctx_reg(a, sk_sym_e3dd0); }
/* FUN_0006eb1c @ 0x6eb1c   (est. sk_ctx_bind)
 * Ghidra: void FUN_0006eb1c(undefined8)
 * Binds a context via 0x1a0d0 (0x64e2d8/0x65d740).
 * Confidence: low
 * Notes: FUN_0001a0d0.
 */
void sk_ctx_bind(sk_word_t a){ sk_ctx_bind_h(a, 0x64e2d8, 0x65d740); }
/* FUN_0006f078 @ 0x6f078   (est. sk_ctx_bind2)
 * Ghidra: void FUN_0006f078(undefined8)
 * Binds a context via 0x1a0d0 (0x64e3d8/0x65e6c0).
 * Confidence: low
 * Notes: FUN_0001a0d0.
 */
void sk_ctx_bind2(sk_word_t a){ sk_ctx_bind_h(a, 0x64e3d8, 0x65e6c0); }
/* FUN_0006f0b4 @ 0x6f0b4   (est. sk_ctx_register3)
 * Ghidra: void FUN_0006f0b4(undefined8)
 * Registers a context via 0x6f0e4 with the 0xe3e34 symbol.
 * Confidence: low
 * Notes: FUN_0006f0e4/000e3e34.
 */
void sk_ctx_register3(sk_word_t a){ sk_ctx_reg(a, sk_sym_e3e34); }
/* FUN_0006f0cc @ 0x6f0cc   (est. sk_ctx_register4)
 * Ghidra: void FUN_0006f0cc(undefined8)
 * Registers a context via 0x6f0e4 with the 0xe3f10 symbol.
 * Confidence: low
 * Notes: FUN_0006f0e4/000e3f10.
 */
void sk_ctx_register4(sk_word_t a){ sk_ctx_reg(a, sk_sym_e3f10); }
/* FUN_0006f0e4 @ 0x6f0e4   (est. sk_ctx_reg)
 * Ghidra: void FUN_0006f0e4(long,code*)
 * Registers a context: validates the id is non-negative, then invokes the given symbol builder to allocate the context object and stores the id into its data slot.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x6f130).
 */
void sk_ctx_reg(long id, void *(*build)(long))
{
    if (id < 0) sk_breakpoint(1, 0x6f130);
    if (id != 0) {
        long o = (long)build(id);
        *(long *)((char*)o + 0x10) = id;
    }
}
/* FUN_0006f130 @ 0x6f130   (est. sk_ctx_dispatch)
 * Ghidra: void FUN_0006f130(undefined8,long,undefined8)
 * Dispatches through the context's method table at +0x40 (indirect jump).
 * Confidence: low
 * Notes: Indirect jump, 'Too many branches'.
 */
void sk_ctx_dispatch(sk_word_t a, long tbl, sk_word_t c){ (*(void(**)(sk_word_t,sk_word_t,long))(*(void***)(tbl + 0x40)[0]))(a, c, 0); }
/* FUN_0006f180 @ 0x6f180   (est. sk_ctx_bind3)
 * Ghidra: void FUN_0006f180(undefined8)
 * Binds a context via 0x1a0d0 (LAB_0064e408/0x65e908).
 * Confidence: low
 * Notes: FUN_0001a0d0.
 */
void sk_ctx_bind3(sk_word_t a){ sk_ctx_bind_h(a, 0x64e408, 0x65e908); }
/* FUN_0006f684 @ 0x6f684   (est. sk_noop_6f684)
 * Ghidra: void FUN_0006f684(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f684(void){ }
/* FUN_0006f69c @ 0x6f69c   (est. sk_noop_6f69c)
 * Ghidra: void FUN_0006f69c(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f69c(void){ }
/* FUN_0006f6b4 @ 0x6f6b4   (est. sk_dt_empty)
 * Ghidra: undefined* FUN_0006f6b4(void)
 * Returns the empty DT/report buffer (DAT_00657778).
 * Confidence: low
 * Notes: void *sk_dt_empty(void){ return &DAT_00657778; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006f6d0 @ 0x6f6d0   (est. sk_dt_empty2)
 * Ghidra: undefined* FUN_0006f6d0(void)
 * Returns the empty DT/report buffer (DAT_00657778).
 * Confidence: low
 * Notes: void *sk_dt_empty2(void){ return &DAT_00657778; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006f6e0 @ 0x6f6e0   (est. sk_fatal_str)
 * Ghidra: char* FUN_0006f6e0(void)
 * Returns the 'Fatal error' string.
 * Confidence: low
 * Notes: const char *sk_fatal_str(void){ return s_Fatal_error_005accd0; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006f6f4 @ 0x6f6f4   (est. sk_noop_6f6f4)
 * Ghidra: void FUN_0006f6f4(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f6f4(void){ }
/* FUN_0006f70c @ 0x6f70c   (est. sk_noop_6f70c)
 * Ghidra: void FUN_0006f70c(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f70c(void){ }
/* FUN_0006f75c @ 0x6f75c   (est. sk_dt_empty_tbl)
 * Ghidra: undefined8* FUN_0006f75c(void)
 * Returns the empty DT table (DAT_00657798).
 * Confidence: low
 * Notes: sk_word_t *sk_dt_empty_tbl(void){ return &DAT_00657798; }
 */

/*--------------------------------------------------------------------*/

/* FUN_0006f768 @ 0x6f768   (est. sk_noop_6f768)
 * Ghidra: void FUN_0006f768(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f768(void){ }
/* FUN_0006f774 @ 0x6f774   (est. sk_vspace_publish)
 * Ghidra: void FUN_0006f774(void)
 * Allocates a 0x28-byte vspace object (token 0x64e210).
 * Confidence: low
 * Notes: FUN_0036a940.
 */
void sk_vspace_publish(sk_word_t *unused){ sk_alloc_obj(0x64e210, 0x28, 7); }
/* FUN_0006f794 @ 0x6f794   (est. sk_kind3)
 * Ghidra: undefined8 FUN_0006f794(void)
 * Returns the kind constant 3.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_kind3(void){ return 3; }
/* FUN_0006f7b4 @ 0x6f7b4   (est. sk_noop_6f7b4)
 * Ghidra: void FUN_0006f7b4(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6f7b4(void){ }
/* FUN_0006f800 @ 0x6f800   (est. sk_ctx_token)
 * Ghidra: undefined1[16] FUN_0006f800(void)
 * Returns the context token 0x64e4b0.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_ctx_token(void){ return 0x64e4b0; }
/* FUN_0006f818 @ 0x6f818   (est. sk_obj_state_out)
 * Ghidra: void FUN_0006f818(undefined8*)
 * Exports the object's 6-word state block into the caller's output.
 * Confidence: low
 * Notes: FUN_0006fd6c/0036a1a0.
 */
void sk_obj_state_out(sk_word_t *out)
{
    sk_state_prep((char*)unaff_x20 + 0x18);      /* FUN_0006fd6c */
    sk_state_export();                           /* FUN_0036a1a0 */
    out[0]=*(sk_word_t*)((char*)unaff_x20 + 0x18);
    out[1]=*(sk_word_t*)((char*)unaff_x20 + 0x20);
    out[2]=*(sk_word_t*)((char*)unaff_x20 + 0x28);
    out[3]=*(sk_word_t*)((char*)unaff_x20 + 0x30);
    out[4]=*(sk_word_t*)((char*)unaff_x20 + 0x38);
    out[5]=*(sk_word_t*)((char*)unaff_x20 + 0x40);
    ((char*)out)[0x29]=*(char*)((char*)unaff_x20 + 0x41);
    ((char*)out)[0x31]=*(char*)((char*)unaff_x20 + 0x49);
}
/* FUN_0006f868 @ 0x6f868   (est. sk_obj_state_in)
 * Ghidra: void FUN_0006f868(undefined8*)
 * Imports a 6-word state block into the object.
 * Confidence: low
 * Notes: FUN_0036a1a0.
 */
void sk_obj_state_in(sk_word_t *in)
{
    sk_state_import((char*)unaff_x20 + 0x18, in, 1, 0);   /* FUN_0036a1a0 */
    *(sk_word_t*)((char*)unaff_x20 + 0x18) = in[0];
    *(sk_word_t*)((char*)unaff_x20 + 0x20) = in[1];
    *(sk_word_t*)((char*)unaff_x20 + 0x28) = in[2];
    *(sk_word_t*)((char*)unaff_x20 + 0x30) = in[3];
    *(sk_word_t*)((char*)unaff_x20 + 0x38) = in[4];
    *(sk_word_t*)((char*)unaff_x20 + 0x40) = in[5];
    *(char*)((char*)unaff_x20 + 0x41) = *(char*)((char*)in + 0x29);
    *(char*)((char*)unaff_x20 + 0x49) = *(char*)((char*)in + 0x31);
}
/* FUN_0006f8c0 @ 0x6f8c0   (est. sk_obj_state_ref)
 * Ghidra: undefined1[16] FUN_0006f8c0(undefined8)
 * Imports a state block and returns a reference to the object state.
 * Confidence: low
 * Notes: FUN_0036a1a0.
 */
sk_word_t sk_obj_state_ref(sk_word_t in){ sk_state_import((char*)unaff_x20 + 0x18, in, 0x21, 0); return (sk_word_t)((char*)unaff_x20 + 0x18); }
/* FUN_0006f914 @ 0x6f914   (est. sk_obj_state_word)
 * Ghidra: void FUN_0006f914(undefined8*)
 * Exports the object's single state word (offset +0x20).
 * Confidence: low
 * Notes: FUN_0006fd6c/0036a1a0.
 */
void sk_obj_state_word(sk_word_t *out){ sk_state_prep((char*)unaff_x20 + 0x18); sk_state_export(); *out = *(sk_word_t*)((char*)unaff_x20 + 0x20); }
/* FUN_0006f958 @ 0x6f958   (est. sk_state_error_rec)
 * Ghidra: undefined1[16] FUN_0006f958(void)
 * Builds the state-error report record: locks, flushes, emits the state error header (0x1d) and the ')' record.
 * Confidence: low
 * Notes: FUN_002a4ab4/003a25d4/0006fd6c/0036a1a0/00027724; thunk_FUN_002acbb8; 0x80000000005bfb60/0xd000000000000023.
 */
sk_word_t sk_state_error_rec(void){ sk_report_lock(0x1d); sk_report_free(0xe000000000000000); sk_state_prep((char*)unaff_x20 + 0x18); sk_state_export(); void (*p)(sk_word_t,sk_word_t)=(void(*)(sk_word_t,sk_word_t))sk_boot_obj_helper2(0x671df8); p(0x677830,0x671df8); sk_report_emit(0,0); sk_report_free(0); sk_report_emit(0x29, 0xe100000000000000); return 0x80000000005bfb60; }
/* FUN_0006fa2c @ 0x6fa2c   (est. sk_obj_free_tear)
 * Ghidra: void FUN_0006fa2c(void)
 * Frees the object at +0x10 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b6ac.
 */
void sk_obj_free_tear(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); sk_alloc_teardown(); }
/* FUN_0006fa30 @ 0x6fa30   (est. sk_obj_free_tear2)
 * Ghidra: void FUN_0006fa30(void)
 * Frees the object at +0x10 and runs the allocator teardown.
 * Confidence: low
 * Notes: FUN_0036b118/0036b6ac.
 */
void sk_obj_free_tear2(void){ sk_free(*(void**)((char*)unaff_x20 + 0x10)); sk_alloc_teardown(); }
/* FUN_0006fa58 @ 0x6fa58   (est. sk_state_word_fwd)
 * Ghidra: void FUN_0006fa58(void)
 * Forwarder to 0x6f914.
 * Confidence: low
 * Notes: FUN_0006f914.
 */
void sk_state_word_fwd(void){ sk_obj_state_word(0); }
/* FUN_0006fa88 @ 0x6fa88   (est. sk_state_err_fwd)
 * Ghidra: void FUN_0006fa88(void)
 * Forwarder to 0x6f958.
 * Confidence: low
 * Notes: FUN_0006f958.
 */
void sk_state_err_fwd(void){ sk_state_error_rec(); }
/* FUN_0006faac @ 0x6faac   (est. sk_obj_state_alloc)
 * Ghidra: void FUN_0006faac(undefined8*)
 * Allocates a 0x51-byte state object and imports the 6-word state block into it.
 * Confidence: low
 * Notes: FUN_0036a940.
 */
void sk_obj_state_alloc(sk_word_t *in){ long o = sk_alloc_obj(0, 0, 0); *(sk_word_t*)((char*)o+0x10)=in[0]; *(sk_word_t*)((char*)o+0x18)=in[1]; *(sk_word_t*)((char*)o+0x20)=in[2]; *(sk_word_t*)((char*)o+0x28)=in[3]; *(sk_word_t*)((char*)o+0x30)=in[4]; *(sk_word_t*)((char*)o+0x38)=in[5]; *(char*)((char*)o+0x39)=*(char*)((char*)in+0x29); *(char*)((char*)o+0x41)=*(char*)((char*)in+0x31); }
/* FUN_0006fb1c @ 0x6fb1c   (est. sk_pac_register)
 * Ghidra: void FUN_0006fb1c(long*)
 * Registers a PAC-resource context: queries the resource capability, and on failure raises the 'InternalExclaveLauncher.PacResou[rce]' fatal; otherwise stores the resource fields into the context and links it.
 * Confidence: low
 * Notes: Strings s_Fatal_error_005accd0, s_InternalExclaveLauncher_PacResou_005bfbb0; FUN_0006fce8/0006fd7c/0006fd4c/0036b270; indirect call via *param_1+0x1b8.
 */
void sk_pac_register(long *res){ sk_word_t out[6]={0,0,0,0,0,0}; (*(void(**)(sk_word_t*,int,int,int,int,int))(*res + 0x1b8))(&out[0],0x12,0,0,0,0); if (unaff_x21 == 0) { long l = sk_pac_lookup(*(sk_word_t*)((char*)unaff_x20+0x10), out[0]);  /* FUN_0006fce8 */ if (l != 0) sk_fatal(s_Fatal_error,0xb,2,0xd000000000000016,0x80000000005bfbc0,s_InternalExclaveLauncher_PacResou,0x29,2,0x46,0); long o = sk_pac_obj();  /* FUN_0006fd7c */ *(sk_word_t*)((char*)o+0x20)=out[1]; *(sk_word_t*)((char*)o+0x18)=out[0]; *(long*)((char*)o+0x10)=(long)unaff_x20; *(sk_word_t*)((char*)o+0x30)=out[3]; *(sk_word_t*)((char*)o+0x28)=out[2]; *(sk_word_t*)((char*)o+0x40)=out[4]; *(sk_word_t*)((char*)o+0x38)=out[5]; sk_pac_link(out[5], 0);  /* FUN_0006fd4c */ sk_alloc_pages(o,0); } }
/* FUN_0006fc24 @ 0x6fc24   (est. sk_pac_commit)
 * Ghidra: void FUN_0006fc24(void)
 * Commits a PAC-resource context: allocates the object and copies the caller's resource fields into it, then links it.
 * Confidence: low
 * Notes: FUN_0006fd7c/0006fd4c/0036b270.
 */
void sk_pac_commit(void){ long o = sk_pac_obj(); *(sk_word_t*)((char*)o+0x20)=*(sk_word_t*)((char*)unaff_x20+0x18); *(sk_word_t*)((char*)o+0x18)=*(sk_word_t*)((char*)unaff_x20+0x10); *(long*)((char*)o+0x10)=(long)unaff_x20; *(sk_word_t*)((char*)o+0x30)=*(sk_word_t*)((char*)unaff_x20+0x28); *(sk_word_t*)((char*)o+0x28)=*(sk_word_t*)((char*)unaff_x20+0x20); *(sk_word_t*)((char*)o+0x40)=*(sk_word_t*)((char*)unaff_x20+0x38); *(sk_word_t*)((char*)o+0x38)=*(sk_word_t*)((char*)unaff_x20+0x30); sk_pac_link(*(sk_word_t*)((char*)unaff_x20+0x39), 0); sk_alloc_pages(o,0); }
/* FUN_0006fcb0 @ 0x6fcb0   (est. sk_pac_commit_fwd)
 * Ghidra: void FUN_0006fcb0(void)
 * Forwarder to 0x6fc24.
 * Confidence: low
 * Notes: FUN_0006fc24.
 */
void sk_pac_commit_fwd(void){ sk_pac_commit(); }
/* FUN_0006fcb4 @ 0x6fcb4   (est. sk_pac_commit_fwd2)
 * Ghidra: void FUN_0006fcb4(void)
 * Forwarder to 0x6fc24.
 * Confidence: low
 * Notes: FUN_0006fc24.
 */
void sk_pac_commit_fwd2(void){ sk_pac_commit(); }
/* FUN_0006fcc8 @ 0x6fcc8   (est. sk_pac_register_fwd)
 * Ghidra: void FUN_0006fcc8(void)
 * Forwarder to 0x6fb1c.
 * Confidence: low
 * Notes: FUN_0006fb1c.
 */
void sk_pac_register_fwd(void){ sk_pac_register(0); }
/* FUN_0006fccc @ 0x6fccc   (est. sk_pac_register_fwd2)
 * Ghidra: void FUN_0006fccc(void)
 * Forwarder to 0x6fb1c.
 * Confidence: low
 * Notes: FUN_0006fb1c.
 */
void sk_pac_register_fwd2(void){ sk_pac_register(0); }
/* FUN_0006fce8 @ 0x6fce8   (est. sk_pac_lookup)
 * Ghidra: void FUN_0006fce8(void)
 * Performs a PAC lookup by programming the RO frame (0) and issuing CallSupervisor(3).
 * Confidence: low
 * Notes: CallSupervisor(3).
 */
void sk_pac_lookup(sk_word_t a, sk_word_t b){ volatile sk_word_t *tp=(volatile sk_word_t*)__builtin_thread_pointer_ro(); *tp=0; CallSupervisor(3); return 0; }
/* FUN_0006fd3c @ 0x6fd3c   (est. sk_pac_token)
 * Ghidra: undefined1[16] FUN_0006fd3c(void)
 * Returns the PAC context token 0x64e508.
 * Confidence: low
 * Notes: high.
 */
sk_word_t sk_pac_token(void){ return 0x64e508; }
/* FUN_0006fd4c @ 0x6fd4c   (est. sk_pac_link)
 * Ghidra: void FUN_0006fd4c(undefined1[16],long)
 * Links a PAC context: stores the link word and its tag into the object's tail fields and splices it into the caller's dispatch list.
 * Confidence: low
 * Notes: FUN_0006fd4c.
 */
void sk_pac_link(sk_word_t lo, sk_word_t hi, long obj){ *(long*)((char*)obj+0x49)=hi; *(long*)((char*)obj+0x41)=lo; unaff_x22[3]=unaff_x23; unaff_x22[4]=0x65f0b0; *unaff_x22=obj; }
/* FUN_0006fd6c @ 0x6fd6c   (est. sk_noop_6fd6c)
 * Ghidra: void FUN_0006fd6c(void)
 * Empty stub (no-op).
 * Confidence: low
 * Notes: high.
 */
void sk_noop_6fd6c(void){ }
/* FUN_0006fd7c @ 0x6fd7c   (est. sk_pac_obj)
 * Ghidra: void FUN_0006fd7c(void)
 * Allocates a 0x51-byte PAC context object (token 0x64e568).
 * Confidence: low
 * Notes: FUN_0036a940.
 */
void sk_pac_obj(void){ sk_alloc_obj(0x64e568, 0x51, 7); }
/* FUN_0006fdbc @ 0x6fdbc   (est. sk_untyped_name)
 * Ghidra: undefined1[16] FUN_0006fdbc(ulong,char)
 * Formats an untyped-object name: selects the name record by index (from the name table at 0x65f120), appends a single- or double-quoted suffix, and emits it; breaks on an out-of-range index.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x6ff34/0x6ff38); name table 0x65f120; FUN_00027724/000778a0; thunk_FUN_002acbb8/0036b270/003a25d4.
 */
sk_word_t sk_untyped_name(sk_word_t i, char quote)
{
    sk_word_t idx = 5, shift = 0x32;
    do {
        if (9 < (i >> (shift & 0x3f))) break;
        shift -= 10;
        idx -= 1;
    } while (idx != 0);
    if (idx == 0) idx = 0;
    if ((long)(idx*10) != 0 && 0) sk_breakpoint(1, 0x6ff34);
    sk_boot_obj_helper2(0x671df8);
    sk_word_t v = sk_778a0();                    /* FUN_000778a0 */
    (*(void(**)(sk_word_t,sk_word_t))extraout_x8)(v, 0x671df8);
    sk_report_emit(0, 0);
    sk_report_free(0);
    sk_report_emit(0x20, 0xe100000000000000);    /* ' ' */
    if (idx < 5) {
        sk_word_t n0 = *(sk_word_t *)(idx*0x10 + 0x65f120);
        sk_word_t n1 = *(sk_word_t *)(idx*0x10 + 0x65f128);
        sk_alloc_pages(n1, 0);
        sk_report_emit(n0, n1);
        sk_report_free(n1);
        sk_word_t q = quote == 1 ? 0x717249 : 0x42;     /* 'Irq' or 'B' */
        sk_word_t qh = quote == 1 ? 0xe300000000000000 : 0xe100000000000000;
        sk_report_emit(q, qh);
        sk_report_free(qh);
        return 0xe000000000000000;
    }
    sk_breakpoint(1, 0x6ff38);
}
/* FUN_0006ff40 @ 0x6ff40   (est. sk_ctx_call_bind)
 * Ghidra: void FUN_0006ff40(void)
 * Saves the context and runs the bind helper, then restores.
 * Confidence: low
 * Notes: FUN_001a84f4/0001c2a4/001a8564.
 */
void sk_ctx_call_bind(void){ sk_word_t v = *unaff_x20; sk_ctx_save(0); sk_ctx_bind_h2(v); sk_ctx_restore(); }
/* FUN_0006ff84 @ 0x6ff84   (est. sk_untyped_rec)
 * Ghidra: undefined1[16] FUN_0006ff84(undefined8,char)
 * Builds an untyped-object name record: for mode 0 it formats a 64-bit value, for mode 1 it emits the 'L4_Untyped_dep..Unt' prefix, and otherwise uses a generic 'L4_Irq_dep..' record.
 * Confidence: low
 * Notes: FUN_00205844/0006fdbc; thunk_FUN_002acbb8; 0x6671f0/0x6756a8/0x66e1b8.
 */
sk_word_t sk_untyped_rec(sk_word_t v, char mode)
{
    if (mode == 0) {
        sk_word_t rec[2] = {0, 0xe000000000000000};
        sk_format2(&v, &rec, 0x6671f0, 0x6756a8, 0x66e1b8);
        return rec[0];
    } else if (mode == 1) {
        sk_word_t r = sk_untyped_name(v, 0);
        sk_report_emit(0x79746e555f344c20, 0xed0000745f646570);  /* 'L4_Untyped_dep..' */
        return r;
    } else {
        return 0x745f7172495f344c | 0xe800000000000000;   /* 'L4_Irq_dep..' */
    }
}
