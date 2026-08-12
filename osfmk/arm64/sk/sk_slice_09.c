/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0004ed84-0x00055420 (worker SK09): the "tbplaceholder" resource layer
 * (boot descriptor encode/decode, name lookup, subgraph mapping), the Mach-O
 * segment/section scanner, the CNode range collector (cna), the cL4 platform
 * fault/init hooks, and the region relocation bind helpers.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
#define DC_GVA(a) __asm__ volatile("dc cvau, %0" : : "r"((uint64_t)(a)))
#define GENTER() __asm__ volatile(".inst 0x00201420")
#define GEXIT()  __asm__ volatile(".inst 0x00201400")
static inline void sk_callsup(uint64_t kind)
{ __asm__ volatile("svc %0" : : "i"(0)); (void)kind; }
#define CallSupervisor(k) sk_callsup((uint64_t)(k))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
#define SK_CANARY (-0x2c8502b44bfffed6LL)

static uint8_t sk_tpidr_area[0x100] __attribute__((aligned(16)));
#define tpidr_el0    ((uint8_t *)sk_tpidr_area)
#define tpidrro_el0  ((uint8_t *)sk_tpidr_area)

/* ------------------------------------------------------------------ *
 * Shared globals referenced by this slice (image-base addresses are the
 * Ghidra ground truth).
 * ------------------------------------------------------------------ */
extern uint64_t sk_global_cfg;          /* FUN_00054610 */
extern uint64_t sk_phys_base;           /* DAT_006ad6e0 */
extern uint8_t  sk_boot_debug_flag;     /* DAT_006ad6e8 */
extern uint8_t  sk_boot_dump_flag;      /* DAT_006ad6e9 */
extern uint8_t  sk_rebase_dump_flag;    /* DAT_006ad6ea */
extern uint64_t sk_cnode_owner;         /* DAT_006af888 */
extern uint64_t sk_cnode_owner2;        /* DAT_006af890 */
extern uint64_t sk_cnode_list;          /* DAT_006af898 */
extern uint64_t sk_cnode_base;          /* DAT_006af8b0 */
extern uint64_t sk_cnode_len;           /* DAT_006af8b8 */
extern uint64_t sk_plat_init_flag;      /* DAT_006af8c8 */
extern uint32_t sk_plat_init_done;      /* DAT_006af8d0 */
extern uint64_t sk_config_obj;          /* DAT_006b0340 */
extern uint64_t sk_tbplace_res_tbl;     /* 0x65bf78 */
extern uint64_t sk_tbplace_res_ptr;     /* 0x65bf80 */
extern uint64_t sk_tbplace_res_dsp;     /* 0x65bf88/0x65bf90 */

/* ------------------------------------------------------------------ *
 * Shared helpers reconstructed by other slice workers.
 * FUN_ address is ground truth; names are estimates.
 * ------------------------------------------------------------------ */
typedef union {
    struct { uint64_t lo, hi; };
    struct { void *object, *vtable; };
    struct { uint64_t base, end; };
} sk_ep_pair_t;
extern unsigned long sk_x_00001378();   /* FUN_00001378 */
extern unsigned long sk_x_0000178c();   /* FUN_0000178C */
extern unsigned long sk_x_00011d7c();   /* FUN_00011D7C */
extern sk_ep_pair_t sk_ep_obj_get();   /* FUN_00034a2c: {object, vtable} pair */
extern unsigned long sk_x_00034f70();   /* FUN_00034F70 */
extern unsigned long sk_x_00035a78();   /* FUN_00035A78 */
extern unsigned long sk_x_0004ba18();   /* FUN_0004BA18 */
extern unsigned long sk_boot_string();  /* FUN_0004cdc0 */
extern unsigned long sk_ptr_fixup();    /* FUN_0004d150 */
extern unsigned long sk_reloc_init();   /* FUN_0004d39c */
extern unsigned long sk_vas_init_fh();  /* FUN_0004d8ec */
extern unsigned long sk_fh_register();  /* FUN_0004dfd0 */
extern unsigned long sk_tb_ph_resolve(); /* FUN_0004e7b8 */
extern unsigned long sk_tb_ph_kind();   /* FUN_0004e88c */
extern unsigned long sk_tb_ph_count();  /* FUN_0004e8b0 */
extern unsigned long sk_tb_ph_find();   /* FUN_0004e95c */
extern unsigned long sk_tb_ph_iter_init(); /* FUN_0004eb44 */
extern unsigned long sk_tb_ph_iter_next(); /* FUN_0004eb4c */
extern unsigned long sk_tb_ph_avail();  /* FUN_0004ed48 */
extern unsigned long sk_x_00055780();   /* FUN_00055780 */
extern unsigned long sk_x_00055858();   /* FUN_00055858 */
extern unsigned long sk_x_00055948();   /* FUN_00055948 */
extern unsigned long sk_x_00055b44();   /* FUN_00055b44 */
extern unsigned long sk_x_00055b7c();   /* FUN_00055b7c */
extern unsigned long sk_x_00056098();   /* FUN_00056098 */
extern unsigned long sk_x_0005680c();   /* FUN_0005680c */
extern unsigned long sk_x_00056f84();   /* FUN_00056f84 */
extern unsigned long sk_x_00057708();   /* FUN_00057708 */
extern unsigned long sk_x_00057e8c();   /* FUN_00057e8c */
extern unsigned long sk_x_0005860c();   /* FUN_0005860c */
extern unsigned long sk_x_00058d8c();   /* FUN_00058d8c */
extern unsigned long sk_x_0005950c();   /* FUN_0005950c */
extern unsigned long sk_x_00059c8c();   /* FUN_00059c8c */
extern unsigned long sk_x_0005a40c();   /* FUN_0005a40c */
extern unsigned long sk_x_0005ab94();   /* FUN_0005ab94 */
extern unsigned long sk_percpu_tbl();   /* FUN_0005acac */
extern unsigned long sk_x_0005b0bc();   /* FUN_0005b0bc */
extern unsigned long sk_panic_brk();    /* FUN_0005b190 */
extern unsigned long sk_x_0005b1b0();   /* FUN_0005b1b0 */
extern unsigned long sk_x_0005b860();   /* FUN_0005b860 */
extern unsigned long sk_x_0005b89c();   /* FUN_0005b89c */
extern unsigned long sk_x_0005ba14();   /* FUN_0005ba14 */
extern unsigned long sk_x_0005ba5c();   /* FUN_0005ba5c */
extern unsigned long sk_x_0005baac();   /* FUN_0005baac */
extern unsigned long sk_x_0005baf0();   /* FUN_0005baf0 */
extern unsigned long sk_x_0005bb7c();   /* FUN_0005bb7c */
extern unsigned long sk_x_0005bc48();   /* FUN_0005bc48 */
extern unsigned long sk_x_0005c278();   /* FUN_0005c278 */
extern unsigned long sk_x_0005c650();   /* FUN_0005c650 */
extern unsigned long sk_x_0005c924();   /* FUN_0005c924 */
extern unsigned long sk_x_0005cb18();   /* FUN_0005cb18 */
extern unsigned long sk_x_0005cb9c();   /* FUN_0005cb9c */
extern unsigned long sk_x_0005cdbc();   /* FUN_0005cdbc */
extern unsigned long sk_x_0005ce54();   /* FUN_0005ce54 */
extern unsigned long sk_x_0005cf08();   /* FUN_0005cf08 */
extern unsigned long sk_x_0005cf4c();   /* FUN_0005cf4c */
extern unsigned long sk_x_0005d154();   /* FUN_0005d154 */
extern unsigned long sk_x_0005d38c();   /* FUN_0005d38c */
extern unsigned long sk_x_0005d394();   /* FUN_0005d394 */
extern unsigned long sk_x_0005d470();   /* FUN_0005d470 */
extern unsigned long sk_x_0005ee7c();   /* FUN_0005ee7c */
extern unsigned long sk_x_000600f0();   /* FUN_000600f0 */
extern unsigned long sk_errno_ptr();    /* thunk_FUN_0006037c */
extern unsigned long sk_x_00060524();   /* FUN_00060524 */
extern unsigned long sk_x_00060564();   /* FUN_00060564 */
extern unsigned long sk_x_00061630();   /* FUN_00061630 */
extern unsigned long sk_x_00062474();   /* FUN_00062474 */
extern unsigned long sk_x_00062848();   /* FUN_00062848 */
extern unsigned long sk_x_0006285c();   /* FUN_0006285c */
extern unsigned long sk_x_000628d8();   /* FUN_000628d8 */
extern unsigned long sk_x_000628e0();   /* FUN_000628e0 */
extern unsigned long sk_x_00063aa8();   /* FUN_00063aa8 */
extern unsigned long sk_x_000640e4();   /* FUN_000640e4 */
extern unsigned long sk_x_00065020();   /* FUN_00065020 */
extern unsigned long sk_x_0006562c();   /* FUN_0006562c */
extern unsigned long sk_x_000656e4();   /* FUN_000656e4 */
extern unsigned long sk_memset0();      /* thunk_FUN_00114330 */
extern unsigned long sk_x_001144a0();   /* FUN_001144a0 */
extern unsigned long sk_memcmp();       /* thunk_FUN_00114e50 */
extern unsigned long sk_x_00114fe0();   /* FUN_00114fe0 */
extern unsigned long sk_fatal_printf(); /* FUN_001150e0 */
extern unsigned long sk_x_00116c20();   /* FUN_00116c20 */
extern unsigned long sk_memcpy();       /* FUN_00117cc4 */
extern unsigned long sk_string_set();   /* FUN_00117e68 */
extern unsigned long sk_mtx_init();     /* FUN_00118148 */
extern unsigned long sk_mtx_lock();     /* FUN_00118164 */
extern unsigned long sk_mtx_try();      /* FUN_0011817c */
extern unsigned long sk_mtx_unlock();   /* FUN_00118194 */
extern unsigned long sk_x_001187f4();   /* FUN_001187f4 */
extern unsigned long sk_x_0011883c();   /* FUN_0011883c */
extern unsigned long sk_x_00118abc();   /* FUN_00118abc */
extern unsigned long sk_printf();       /* FUN_00118b28 */
extern unsigned long sk_printf2();      /* FUN_00118b94 */
extern unsigned long sk_x_00118c38();   /* FUN_00118c38 */
extern unsigned long sk_x_001190fc();   /* FUN_001190fc */
extern unsigned long sk_stack_chk_fail(); /* FUN_0011d7e8 */
extern unsigned long sk_x_004afae4();   /* FUN_004afae4 */
extern unsigned long sk_x_004b23d8();   /* FUN_004b23d8 */
extern unsigned long sk_x_004b5e20();   /* FUN_004b5e20 */
extern unsigned long sk_x_004b5e30();   /* FUN_004b5e30 */
extern unsigned long sk_x_004b5e48();   /* FUN_004b5e48 */
extern unsigned long sk_x_004b5e60();   /* FUN_004b5e60 */
extern unsigned long sk_x_004b5e78();   /* FUN_004b5e78 */
extern unsigned long sk_x_004b5e9c();   /* FUN_004b5e9c */
extern unsigned long sk_x_004b5ee0();   /* FUN_004b5ee0 */
extern unsigned long sk_x_004b5ef8();   /* FUN_004b5ef8 */
extern unsigned long sk_x_004b5f30();   /* FUN_004b5f30 */
extern unsigned long sk_x_004b5fa8();   /* FUN_004b5fa8 */

/* String literals referenced by this slice (Ghidra s_* names in comments). */
extern const char sk_str_unknown_tbplace[];      /* s_unknown_tbplaceholder_resource_t_005bb75b */
extern const char sk_str_integer_overflow[];     /* s_integer_overflow_005bb5bd */
extern const char sk_str_text[];                 /* s___TEXT_005bb905 */
extern const char sk_str_linkedit[];             /* s___LINKEDIT_005bb90c */
extern const char sk_str_data[];                 /* s___DATA_005bb23b */
extern const char sk_str_data_const[];           /* s___DATA_CONST_005bb242 */
extern const char sk_str_pdata[];                /* s___PDATA_005bb7ae */
extern const char sk_str_pagezero[];             /* s___PAGEZERO_005bb8fa */
extern const char sk_str_rebasechains_dumped[];  /* s_rebasechains_dumped_005bb917 */
extern const char sk_str_componentname[];        /* s___COMPONENTNAME_005bba0f */
extern const char sk_str_userspace_inited[];     /* s_Userspace____04hx__is_inited__Wa_005bb99f */
extern const char sk_str_exclave_scheduled[];    /* s_exclave_is_scheduled_after_suspe_005bb9d8 */
extern const char sk_str_xrt_init_failed[];      /* s_xrt_init_failed_with___d_005bb986 */
extern const char sk_str_xrt_entry[];            /* s__xrt__liblibc_plat_cl4_entry_xrt_005bba8a */
extern const char sk_str_subgraphs_warning[];    /* s__s__warning__found__zu_subgraphs_005bb874 */
extern const char sk_str_failed_map_subgraph[];  /* s_Failed_to_map_memory_for_subgrap_005bb8ca */
extern const char sk_str_failed_frame[];         /* s_Failed_to_create_frame__zu_from_u_005bb7ca */
extern const char sk_str_failed_map_frame[];     /* s_Failed_to_map_the_frame_idx___zu_005bb805 */
extern const char sk_str_failed_dt_sparse[];     /* s_failed_to_create_device_tree_spa_005bb844 */
extern const char sk_str_abort[];                /* s_abort___called_005bbede */
extern const char sk_str_cna_state[];            /* s_cna__p__expected_state__d__was___005bbd35 */
extern const char sk_str_non_contig_cnodes[];    /* s_non_contiguous_cnodes_found_at___005bbbc5 */
extern const char sk_str_cnode_range_1[];        /* s_cnode_range____zx____zx__must_co_005bbc81 */
extern const char sk_str_expected_free[];        /* s_expected__zd_free_slots__only__z_005bbcc3 */
extern const char sk_str_cnode_range_2[];        /* s_cnode_range____zx____zx__and_boo_005bbc29 */
extern const char sk_str_err_success[];          /* s_L4_ErrorCodeSuccess_004bcb80 */
extern const char sk_str_err_preempted[];        /* s_L4_ErrorCodePreempted_004bcba0 */
extern const char sk_str_err_canceled[];         /* s_L4_ErrorCodeCanceled_004bcbc0 */
extern const char sk_str_err_truncated[];        /* s_L4_ErrorCodeTruncated_004bcbe0 */
extern const char sk_str_err_cap_invalid[];      /* s_L4_ErrorCodeCapInvalid_004bcc00 */
extern const char sk_str_err_slot_invalid[];     /* s_L4_ErrorCodeSlotInvalid_004bcc20 */
extern const char sk_str_err_method_invalid[];   /* s_L4_ErrorCodeMethodInvalid_004bcc40 */
extern const char sk_str_err_arg_invalid[];      /* s_L4_ErrorCodeArgumentInvalid_004bcc60 */
extern const char sk_str_err_op_invalid[];       /* s_L4_ErrorCodeOperationInvalid_004bcc80 */
extern const char sk_str_err_perm_invalid[];     /* s_L4_ErrorCodePermissionInvalid_004bcca0 */

/* ------------------------------------------------------------------ *
 * Forward declarations of all functions defined in this slice (dense
 * cross-links). Signatures mirror the definitions below.
 * ------------------------------------------------------------------ */
static sk_ep_pair_t sk_tb_ph_range2(void);
static void sk_tb_ph_name(uint64_t name, uint64_t len, uint64_t cb, uint64_t arg);
static uint32_t sk_tb_cmp3(uint64_t a, uint64_t b);
static uint32_t sk_tb_cmp4(uint64_t a, uint64_t b);
static uint64_t sk_tb_ph_dump(uint64_t p, uint64_t ph, uint64_t region, uint64_t dst, uint64_t len);
static uint64_t sk_tb_ph_dump2(uint64_t p, uint64_t ph, uint64_t arg, uint64_t dst, uint64_t len);
static void sk_tb_ph_name2(uint64_t name, uint64_t len, uint64_t cb, uint64_t arg);
static uint32_t sk_tb_cmp(uint64_t a, uint64_t b);
static uint32_t sk_tb_cmp2(uint64_t a, uint64_t b);
static uint64_t sk_tb_ph_dump3(uint64_t p, uint64_t ph, uint64_t arg, uint64_t dst, uint64_t len);
static bool sk_tb_ph_one8(uint64_t in, long size, uint64_t cb, uint64_t arg);
static uint64_t sk_tb_ph_addr2(uint64_t p, long sel, uint64_t region, uint64_t ph, uint64_t len);
static uint64_t sk_tb_ph_dt(uint64_t p, uint64_t ph, uint64_t region, uint64_t dst, uint64_t len);
static bool sk_tb_ph_ready(void);
static void sk_tb_ph_reloc(uint64_t p, uint64_t ph, uint64_t arg, uint64_t seg, long off, uint64_t name);
static void sk_tb_ph_scan(int do_pdata, uint32_t flags);
static void sk_tb_ph_reloc_all(int a, int b);
static void sk_tb_ph_dump_res(uint64_t arg);
static uint64_t sk_tb_ph_lookup(uint64_t p, uint64_t key);
static uint64_t sk_tb_ph_get(long *out, uint64_t *a, uint64_t *b);
static void sk_tb_ph_map_subgraph(long *out);
static uint64_t sk_strnlen(uint64_t arg1, long arg2);
static uint64_t sk_ipc_msg_write(uint64_t arg1, uint64_t arg2, uint64_t arg3);
static void sk_region_map_frames(uint64_t region, uint64_t arg, uint64_t cb, uint64_t len);
static void sk_err_str_fill(uint64_t out, uint8_t code);
static void sk_tb_ph_encode_elem(uint64_t region, uint64_t ph, uint64_t dst);
static uint64_t sk_reloc_bind(uint64_t region, uint64_t va, uint64_t target);
static uint8_t sk_region_bitset_test(uint64_t region, uint64_t va);
static uint64_t sk_region_find(uint64_t region, uint64_t size);
static void sk_region_init(uint32_t *base, uint64_t size);
static uint64_t sk_macho_pagezero_min(uint64_t mh);
static uint64_t sk_macho_pagezero_max(uint64_t mh);
static uint64_t sk_macho_seg_find(uint64_t mh);
static uint64_t sk_macho_seg_named(uint64_t mh, uint64_t name);
static uint64_t sk_macho_seg_named2(uint64_t mh, uint64_t name);
static uint64_t sk_macho_first_pageseg(uint64_t mh);
static void sk_macho_linkedit(uint64_t mh, uint64_t *count, uint64_t *off, uint64_t *base);
static uint64_t sk_macho_bind_search(uint64_t sel, uint64_t *out, long n, long base, long slide);
static void sk_rebase_dump(void);
static uint64_t sk_region_bitset2(long region, uint64_t va);
static uint64_t sk_region_fault(long region, uint64_t va, long target);
static void sk_xrt_init(uint64_t flag);
static void sk_plat_log(int a, uint64_t b);
static void sk_entry_init(void);
static void sk_xrt_log(void);
static void sk_suspend(void);
static void sk_suspend2(void);
static void sk_suspend3(void);
static void sk_suspend4(uint64_t *out, uint64_t arg);
static uint64_t sk_suspend_get(uint64_t arg);
static void sk_cnode_init(uint64_t base);
static uint64_t sk_cnode_get0(uint64_t *p);
static void sk_cnode_scan(void);
static uint64_t sk_cnode_fault(void);
static uint64_t sk_cnode_get_288(void);
static uint64_t sk_cnode_get_2a8(void);
static void sk_cnode_bootmem(void);
static uint64_t sk_cnode_get_298(long arg);
static uint64_t sk_cnode_get_628(void);
static uint64_t sk_cnode_get_slot(long idx, uint64_t *a, uint8_t *b);
static uint64_t sk_cnode_first(void);
static uint64_t sk_cnode_ptr(long which);
static void sk_cnode_finalize(uint64_t *a, long *b, uint64_t *c);
static void sk_cnode_teardown(void);
static uint64_t *sk_cnode_alloc(void);
static void sk_cnode_advance(long p);
static int sk_parse_dec(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static bool sk_eq(long a, long b);
static uint64_t sk_free_page(uint64_t p);
static void sk_free_page2(uint64_t p);
static uint64_t sk_zero2(uint64_t *p);
static uint64_t sk_alloc_page(uint64_t p);
static uint32_t sk_try_map(uint64_t a, uint64_t b);
static void sk_noop(void);
static uint64_t sk_zero2b(uint64_t *p, uint32_t flags);
static void sk_cb(uint64_t p);
static uint32_t sk_try3(uint64_t p);
static uint64_t sk_cb2(uint64_t p);
static uint64_t sk_mmap(uint64_t *out, uint64_t addr, uint32_t len, int prot, long *extra,
                        uint64_t flags, uint32_t o);
static bool sk_mmap_err(int code);
static uint64_t sk_munmap(long a, long b, uint8_t (*frame)[16]);
static uint64_t sk_mprotect(uint64_t a, uint64_t b, uint8_t (*frame)[16], uint32_t prot);
static void sk_abort(void);
static void sk_log_abort(uint64_t a);
static void sk_panic2(uint64_t a, uint64_t b);
static void sk_prng_fill(long dst, uint64_t n);
static uint64_t sk_ptr_tag(uint64_t p);
static void sk_lock_release(long p);
static uint64_t sk_lock_try(long p);
static void sk_lock_acquire(long p);
static void sk_lock_init(int flag);
static uint64_t sk_global_cfg_get(void);
static uint8_t *sk_cfg_init(long params);
static void sk_register_handler(uint64_t p);
static uint64_t sk_get_handler(void);
static void sk_handler_iter(uint64_t base, long n);
static void sk_handler_install(long rec, uint64_t a, long b, uint64_t c, uint64_t d, uint64_t e);
static void sk_obj_init(uint64_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e,
                        uint64_t f, uint64_t g, uint64_t h, uint64_t i);
static uint64_t sk_obj_get38(void);
static uint64_t sk_obj_get20(void);
static void sk_sync(void);
static void sk_copy16(uint64_t p);
static void sk_map_sym(uint64_t a, uint64_t b);
static uint64_t sk_get_tbplace(void);
static uint64_t sk_noop0(void);
static void sk_read(void);
static long sk_putc(long fd, char *buf, long n);
static void sk_handler_check(uint64_t p);
static uint64_t sk_h_get8(void);
static uint64_t sk_h_get10(void);
static uint8_t sk_h_get20(void);
static void sk_h_call28(uint64_t a, uint64_t b, uint64_t c);
static uint8_t sk_h_get30(void);
static uint8_t sk_h_get38(void);
static uint8_t sk_h_get39(void);
static uint8_t sk_h_get3a(void);
static void sk_h_call40(uint64_t a);
static void sk_h_call48(uint64_t a);
static void sk_h_call50(uint64_t a, uint64_t b);
static void sk_h_call58(uint64_t a);

/* ------------------------------------------------------------------ *
 * Alias macros: subagents referenced helpers/strings by their Ghidra
 * address or full s_* name; map them onto the canonical names declared
 * above / defined in this slice.
 * ------------------------------------------------------------------ */
#define sk_x_00054610  sk_global_cfg_get
#define sk_x_00050c88  sk_strnlen
#define sk_x_00050ce8  sk_ipc_msg_write
#define sk_x_000510e4  sk_region_map_frames
#define sk_x_00051488  sk_tb_ph_encode_elem
#define sk_x_00054354  sk_abort
#define sk_str_unknown_tbplaceholder_resource_t_005bb75b  sk_str_unknown_tbplace
#define sk_str_integer_overflow_005bb5bd                  sk_str_integer_overflow
#define sk_str_failed_to_create_device_tree_spa_005bb844  sk_str_failed_dt_sparse
#define sk_str___PDATA_005bb7ae  sk_str_pdata
#define sk_str___DATA_005bb23b  sk_str_data
#define sk_x_00051e5c  sk_macho_seg_named
#define sk_x_00051ee4  sk_macho_seg_named2
#define sk_x_00051fbc  sk_macho_first_pageseg
#define sk_x_00051ff4  sk_macho_linkedit
#define sk_x_000520f0  sk_macho_bind_search
#define sk_x_00052248  sk_rebase_dump
#define sk_x_0005228c  sk_region_bitset2
#define sk_x_0005236c  sk_region_fault
#define sk_x_00051920  sk_region_bitset_test
#define sk_x_000519c8  sk_region_find
#define sk_x_00051ab8  sk_region_init
#define sk_x_00051d3c  sk_macho_pagezero_min
#define sk_x_00051dc0  sk_macho_pagezero_max
#define sk_x_00051e0c  sk_macho_seg_find
#define sk_x_00050ce8  sk_ipc_msg_write
#define sk_str_failed_to_map_memory_for_subgrap_005bb8ca  sk_str_failed_map_subgraph
#define sk_str___COMPONENTNAME_005bba0f  sk_str_componentname

/* ------------------------------------------------------------------ *
 * Type/name compatibility aliases emitted by the transcription workers
 * (they used Ghidra-ish scalar type names and addr-based helper names).
 * ------------------------------------------------------------------ */
typedef unsigned int  uint;
typedef unsigned long ulong;
typedef unsigned char byte;
#define sk_x_0004ed84  sk_tb_ph_range2
#define sk_x_0004edc8  sk_tb_ph_name
#define sk_x_0004ee90  sk_tb_cmp3
#define sk_x_0004ee94  sk_tb_cmp4
#define sk_x_0004eec0  sk_tb_ph_dump
#define sk_x_0004f258  sk_tb_ph_dump2
#define sk_x_0004f480  sk_tb_ph_name2
#define sk_x_0004f544  sk_tb_cmp
#define sk_x_0004f548  sk_tb_cmp2
#define sk_x_0004f56c  sk_tb_ph_dump3
#define sk_x_0004f794  sk_tb_ph_one8
#define sk_x_0004f890  sk_tb_ph_addr2
#define sk_x_0004fb08  sk_tb_ph_dt
#define sk_x_0004fe80  sk_tb_ph_ready
#define sk_x_0004fed0  sk_tb_ph_reloc
#define sk_x_0004ffd0  sk_tb_ph_scan
#define sk_x_000501cc  sk_tb_ph_reloc_all
#define sk_x_00050444  sk_tb_ph_dump_res
#define sk_x_00050654  sk_tb_ph_lookup
#define sk_x_00050838  sk_tb_ph_get
#define sk_x_000508e8  sk_tb_ph_map_subgraph
#define sk_x_00050c88  sk_strnlen
#define sk_x_00050ce8  sk_ipc_msg_write
#define sk_x_000510e4  sk_region_map_frames
#define sk_x_00051350  sk_err_str_fill
#define sk_x_00051488  sk_tb_ph_encode_elem
#define sk_x_00051740  sk_reloc_bind
#define sk_x_00051920  sk_region_bitset_test
#define sk_x_000519c8  sk_region_find
#define sk_x_00051ab8  sk_region_init
#define sk_x_00051d3c  sk_macho_pagezero_min
#define sk_x_00051dc0  sk_macho_pagezero_max
#define sk_x_00051e0c  sk_macho_seg_find
#define sk_x_00051e5c  sk_macho_seg_named
#define sk_x_00051ee4  sk_macho_seg_named2
#define sk_x_00051fbc  sk_macho_first_pageseg
#define sk_x_00051ff4  sk_macho_linkedit
#define sk_x_000520f0  sk_macho_bind_search
#define sk_x_00052248  sk_rebase_dump
#define sk_x_0005228c  sk_region_bitset2
#define sk_x_0005236c  sk_region_fault
#define sk_x_00052718  sk_xrt_init
#define sk_x_000528c4  sk_plat_log
#define sk_x_00052940  sk_entry_init
#define sk_x_0005295c  sk_xrt_log
#define sk_x_00052968  sk_suspend
#define sk_x_0005296c  sk_suspend2
#define sk_x_00052994  sk_suspend3
#define sk_x_000529a0  sk_suspend4
#define sk_x_000529d4  sk_suspend_get
#define sk_x_00052a04  sk_cnode_init
#define sk_x_00052c4c  sk_cnode_get0
#define sk_x_00052c54  sk_cnode_scan
#define sk_x_000533ec  sk_cnode_fault
#define sk_x_00053418  sk_cnode_get_288
#define sk_x_00053444  sk_cnode_get_2a8
#define sk_x_00053470  sk_cnode_bootmem
#define sk_x_00053484  sk_cnode_get_298
#define sk_x_000534c0  sk_cnode_get_628
#define sk_x_000534ec  sk_cnode_get_slot
#define sk_x_00053568  sk_cnode_first
#define sk_x_00053598  sk_cnode_ptr
#define sk_x_00053634  sk_cnode_finalize
#define sk_x_0005371c  sk_cnode_teardown
#define sk_x_000537c4  sk_cnode_alloc
#define sk_x_00053858  sk_cnode_advance
#define sk_x_000538c8  sk_parse_dec
#define sk_x_000539c0  sk_eq
#define sk_x_000539cc  sk_free_page
#define sk_x_000539fc  sk_free_page2
#define sk_x_00053a14  sk_zero2
#define sk_x_00053a30  sk_alloc_page
#define sk_x_00053a60  sk_try_map
#define sk_x_00053aa0  sk_noop
#define sk_x_00053aa4  sk_zero2b
#define sk_x_00053ae0  sk_cb
#define sk_x_00053af4  sk_try3
#define sk_x_00053b28  sk_cb2
#define sk_x_00053db8  sk_mmap
#define sk_x_00054034  sk_mmap_err
#define sk_x_00054094  sk_munmap
#define sk_x_0005417c  sk_mprotect
#define sk_x_00054354  sk_abort
#define sk_x_000543c4  sk_log_abort
#define sk_x_000543f4  sk_panic2
#define sk_x_00054414  sk_prng_fill
#define sk_x_00054418  sk_ptr_tag
#define sk_x_00054464  sk_lock_release
#define sk_x_000544d0  sk_lock_try
#define sk_x_0005453c  sk_lock_acquire
#define sk_x_000545a8  sk_lock_init
#define sk_x_00054610  sk_global_cfg_get
#define sk_x_00054624  sk_cfg_init
#define sk_x_00054960  sk_register_handler
#define sk_x_000549ac  sk_get_handler
#define sk_x_000549c0  sk_handler_iter
#define sk_x_00054a4c  sk_handler_install
#define sk_x_00054b44  sk_obj_init
#define sk_x_00054ba8  sk_obj_get38
#define sk_x_00054bc8  sk_obj_get20
#define sk_x_00054be8  sk_sync
#define sk_x_00054c3c  sk_copy16
#define sk_x_00054c9c  sk_map_sym
#define sk_x_00054cfc  sk_get_tbplace
#define sk_x_00054de4  sk_noop0
#define sk_x_00054dec  sk_read
#define sk_x_00054e54  sk_putc
#define sk_x_00055164  sk_handler_check
#define sk_x_0005526c  sk_h_get8
#define sk_x_00055288  sk_h_get10
#define sk_x_000552a4  sk_h_get20
#define sk_x_000552c0  sk_h_call28
#define sk_x_0005530c  sk_h_get30
#define sk_x_00055328  sk_h_get38
#define sk_x_00055344  sk_h_get39
#define sk_x_00055360  sk_h_get3a
#define sk_x_0005537c  sk_h_call40
#define sk_x_000553b0  sk_h_call48
#define sk_x_000553e4  sk_h_call50
#define sk_x_00055420  sk_h_call58
#define sk_x_4ed84  sk_tb_ph_range2
#define sk_x_4edc8  sk_tb_ph_name
#define sk_x_4ee90  sk_tb_cmp3
#define sk_x_4ee94  sk_tb_cmp4
#define sk_x_4eec0  sk_tb_ph_dump
#define sk_x_4f258  sk_tb_ph_dump2
#define sk_x_4f480  sk_tb_ph_name2
#define sk_x_4f544  sk_tb_cmp
#define sk_x_4f548  sk_tb_cmp2
#define sk_x_4f56c  sk_tb_ph_dump3
#define sk_x_4f794  sk_tb_ph_one8
#define sk_x_4f890  sk_tb_ph_addr2
#define sk_x_4fb08  sk_tb_ph_dt
#define sk_x_4fe80  sk_tb_ph_ready
#define sk_x_4fed0  sk_tb_ph_reloc
#define sk_x_4ffd0  sk_tb_ph_scan
#define sk_x_501cc  sk_tb_ph_reloc_all
#define sk_x_50444  sk_tb_ph_dump_res
#define sk_x_50654  sk_tb_ph_lookup
#define sk_x_50838  sk_tb_ph_get
#define sk_x_508e8  sk_tb_ph_map_subgraph
#define sk_x_50c88  sk_strnlen
#define sk_x_50ce8  sk_ipc_msg_write
#define sk_x_510e4  sk_region_map_frames
#define sk_x_51350  sk_err_str_fill
#define sk_x_51488  sk_tb_ph_encode_elem
#define sk_x_51740  sk_reloc_bind
#define sk_x_51920  sk_region_bitset_test
#define sk_x_519c8  sk_region_find
#define sk_x_51ab8  sk_region_init
#define sk_x_51d3c  sk_macho_pagezero_min
#define sk_x_51dc0  sk_macho_pagezero_max
#define sk_x_51e0c  sk_macho_seg_find
#define sk_x_51e5c  sk_macho_seg_named
#define sk_x_51ee4  sk_macho_seg_named2
#define sk_x_51fbc  sk_macho_first_pageseg
#define sk_x_51ff4  sk_macho_linkedit
#define sk_x_520f0  sk_macho_bind_search
#define sk_x_52248  sk_rebase_dump
#define sk_x_5228c  sk_region_bitset2
#define sk_x_5236c  sk_region_fault
#define sk_x_52718  sk_xrt_init
#define sk_x_528c4  sk_plat_log
#define sk_x_52940  sk_entry_init
#define sk_x_5295c  sk_xrt_log
#define sk_x_52968  sk_suspend
#define sk_x_5296c  sk_suspend2
#define sk_x_52994  sk_suspend3
#define sk_x_529a0  sk_suspend4
#define sk_x_529d4  sk_suspend_get
#define sk_x_52a04  sk_cnode_init
#define sk_x_52c4c  sk_cnode_get0
#define sk_x_52c54  sk_cnode_scan
#define sk_x_533ec  sk_cnode_fault
#define sk_x_53418  sk_cnode_get_288
#define sk_x_53444  sk_cnode_get_2a8
#define sk_x_53470  sk_cnode_bootmem
#define sk_x_53484  sk_cnode_get_298
#define sk_x_534c0  sk_cnode_get_628
#define sk_x_534ec  sk_cnode_get_slot
#define sk_x_53568  sk_cnode_first
#define sk_x_53598  sk_cnode_ptr
#define sk_x_53634  sk_cnode_finalize
#define sk_x_5371c  sk_cnode_teardown
#define sk_x_537c4  sk_cnode_alloc
#define sk_x_53858  sk_cnode_advance
#define sk_x_538c8  sk_parse_dec
#define sk_x_539c0  sk_eq
#define sk_x_539cc  sk_free_page
#define sk_x_539fc  sk_free_page2
#define sk_x_53a14  sk_zero2
#define sk_x_53a30  sk_alloc_page
#define sk_x_53a60  sk_try_map
#define sk_x_53aa0  sk_noop
#define sk_x_53aa4  sk_zero2b
#define sk_x_53ae0  sk_cb
#define sk_x_53af4  sk_try3
#define sk_x_53b28  sk_cb2
#define sk_x_53db8  sk_mmap
#define sk_x_54034  sk_mmap_err
#define sk_x_54094  sk_munmap
#define sk_x_5417c  sk_mprotect
#define sk_x_54354  sk_abort
#define sk_x_543c4  sk_log_abort
#define sk_x_543f4  sk_panic2
#define sk_x_54414  sk_prng_fill
#define sk_x_54418  sk_ptr_tag
#define sk_x_54464  sk_lock_release
#define sk_x_544d0  sk_lock_try
#define sk_x_5453c  sk_lock_acquire
#define sk_x_545a8  sk_lock_init
#define sk_x_54610  sk_global_cfg_get
#define sk_x_54624  sk_cfg_init
#define sk_x_54960  sk_register_handler
#define sk_x_549ac  sk_get_handler
#define sk_x_549c0  sk_handler_iter
#define sk_x_54a4c  sk_handler_install
#define sk_x_54b44  sk_obj_init
#define sk_x_54ba8  sk_obj_get38
#define sk_x_54bc8  sk_obj_get20
#define sk_x_54be8  sk_sync
#define sk_x_54c3c  sk_copy16
#define sk_x_54c9c  sk_map_sym
#define sk_x_54cfc  sk_get_tbplace
#define sk_x_54de4  sk_noop0
#define sk_x_54dec  sk_read
#define sk_x_54e54  sk_putc
#define sk_x_55164  sk_handler_check
#define sk_x_5526c  sk_h_get8
#define sk_x_55288  sk_h_get10
#define sk_x_552a4  sk_h_get20
#define sk_x_552c0  sk_h_call28
#define sk_x_5530c  sk_h_get30
#define sk_x_55328  sk_h_get38
#define sk_x_55344  sk_h_get39
#define sk_x_55360  sk_h_get3a
#define sk_x_5537c  sk_h_call40
#define sk_x_553b0  sk_h_call48
#define sk_x_553e4  sk_h_call50
#define sk_x_55420  sk_h_call58
#define sk_x_0064cb40  sk_g_0064cb40
#define sk_x_0064cb48  sk_g_0064cb48
#define sk_x_0064cb80  sk_g_0064cb80
#define sk_x_004bccc0  sk_g_004bccc0
#define sk_x_00052930  sk_g_00052930
#define sk_str_warning_found_zu_subgraphs  sk_str_subgraphs_warning
#define sk_str_Failed_to_map_memory_for_subgraph  sk_str_failed_map_subgraph
#define sk_str_Failed_to_create_frame  sk_str_failed_frame
#define sk_str_Failed_to_map_the_frame_idx  sk_str_failed_map_frame
#define sk_str___TEXT  sk_str_text
#define sk_str___LINKEDIT  sk_str_linkedit
#define sk_str___DATA  sk_str_data
#define sk_str___DATA_CONST  sk_str_data_const
#define sk_str___PAGEZERO  sk_str_pagezero
#define sk_str___CAPABILITY_ONLY___  sk_str_data
#define sk_str_abort___called_005bbede  sk_str_abort
#define sk_str_005bbd35  sk_str_cna_state
#define sk_str_005bbbc5  sk_str_non_contig_cnodes
#define sk_str_005bbc81  sk_str_cnode_range_1
#define sk_str_005bbcc3  sk_str_expected_free
#define sk_str_005bbc29  sk_str_cnode_range_2
#define sk_str_005bba8a  sk_str_xrt_entry
#define sk_str_005bba0f  sk_str_componentname
#define sk_str_005bb9d8  sk_str_exclave_scheduled
#define sk_str_005bb99f  sk_str_userspace_inited
#define sk_str_005bb986  sk_str_xrt_init_failed
#define sk_str_005bb917  sk_str_rebasechains_dumped
#define sk_str_L4ErrorCodeSuccess        sk_str_err_success
#define sk_str_L4ErrorCodePreempted      sk_str_err_preempted
#define sk_str_L4ErrorCodeCanceled       sk_str_err_canceled
#define sk_str_L4ErrorCodeTruncated      sk_str_err_truncated
#define sk_str_L4ErrorCodeCapInvalid     sk_str_err_cap_invalid
#define sk_str_L4ErrorCodeSlotInvalid    sk_str_err_slot_invalid
#define sk_str_L4ErrorCodeMethodInvalid  sk_str_err_method_invalid
#define sk_str_L4ErrorCodeArgumentInvalid sk_str_err_arg_invalid
#define sk_str_L4ErrorCodeOperationInvalid sk_str_err_op_invalid
#define sk_str_L4ErrorCodePermissionInvalid sk_str_err_perm_invalid
#define sk_x_00118148  sk_mtx_init
#define sk_x_00118164  sk_mtx_lock
#define sk_x_0011817c  sk_mtx_try
#define sk_x_00118194  sk_mtx_unlock
#define sk_x_0005acac  sk_percpu_tbl
#define sk_x_0004ed48  sk_tb_ph_avail
#define sk_x_0004eb4c  sk_tb_ph_iter_next
#define sk_x_0004eb44  sk_tb_ph_iter_init
#define sk_x_0004e88c  sk_tb_ph_kind
#define sk_x_0004e7b8  sk_tb_ph_resolve
#define sk_x_0004dfd0  sk_fh_register
#define sk_x_0004d8ec  sk_vas_init_fh
#define sk_x_0004d39c  sk_reloc_init
#define sk_x_0004cdc0  sk_boot_string
#define sk_str_cna__p__expected_state__d__was___005bbd35  sk_str_cna_state
#define sk_x_0004fe80  sk_tb_ph_ready
#define sk_x_00054de4  sk_noop0

/* Global data objects referenced by the transcription workers (image-base
 * addresses in comments). */
extern uint32_t sk_g_0064cb40;   /* L4 error-code string table (FUN_00051350) */
extern uint32_t sk_g_0064cb48;
extern uint32_t sk_g_0064cb80;
extern uint32_t sk_g_004bccc0;
extern uint32_t sk_g_00052930;
extern uint32_t sk_g_0064ccd0;   /* global config base (DAT_0064ccd0) */
extern uint32_t sk_g_0064ccf0;
extern uint32_t sk_g_0064cd10;
extern uint32_t sk_g_0064cd88;
extern uint32_t sk_g_0064cee8;
/* FUN_0004ed84 @ 0x0004ed84   (est. sk_tb_ph_range2)
 * Ghidra: void FUN_0004ed84(void)
 * Validates and returns the TB placeholder range: reads the per-cpu global
 * config, checks that the config block (+0x160) and the range {base,size}
 * (fields +0xa8, +0xb0) do not wrap, and returns the {base, size} pair. On an
 * overflow the range is unusable and the fatal breakpoint fires.
 * Confidence: medium
 * Notes: Ghidra types the return as void but callers consume a 16-byte pair
 *   (base at .lo, size at .hi); sk_x_00054610 is the per-cpu config getter. */
static sk_ep_pair_t sk_tb_ph_range2(void)
{
    sk_ep_pair_t r;
    uint64_t cfg;

    cfg = sk_x_00054610();
    if ((cfg <= cfg + 0x160) &&
        (*(uint64_t *)(cfg + 0xa8) <= *(uint64_t *)(cfg + 0xa8) + *(long *)(cfg + 0xb0))) {
        r.lo = *(uint64_t *)(cfg + 0xa8);
        r.hi = *(long *)(cfg + 0xb0);
        return r;
    }
    SoftwareBreakpoint(0x5519, 0x4edc0);
    r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0004edc8 @ 0x0004edc8   (est. sk_tb_ph_name)
 * Ghidra: void FUN_0004edc8(undefined8 param_1,ulong param_2,code *param_3,undefined8 param_4)
 * Looks up a TB placeholder by name: zeroes a 0x110-byte work buffer, resolves
 * the name, copies the resolved name into the buffer (0x108 bytes), and invokes
 * the caller callback with (arg, buffer). If the name is not found nothing is
 * emitted. Returns void; the "found" flag is only used by the stack guard.
 * Confidence: high
 * Notes: sk_x_00050c88 is the name->placeholder resolver; the callback is
 *   invoked only when the lookup succeeds. Stack canary protected. */
static void sk_tb_ph_name(uint64_t name, uint64_t len, uint64_t cb, uint64_t arg)
{
    uint8_t buf[0x110];               /* auStack_158 / auStack_150 region */
    uint64_t canary = 0xd37afd4bb400012aULL;   /* local_48 */
    long found;

    sk_memset0(buf, 0x110);
    found = sk_x_00050c88(name, len);
    if (found != 0) {
        if (0xff < len) len = 0x100;
        sk_string_set(buf, found, len, 0x108);
        ((void (*)(uint64_t, void *))cb)(arg, buf);
    }
    if (canary == 0xd37afd4bb400012aULL) return;
    sk_stack_chk_fail(found != 0);
}

/* FUN_0004ee90 @ 0x0004ee90   (est. sk_tb_cmp3)
 * Ghidra: uint FUN_0004ee90(long param_1,long param_2)
 * Lexicographic 3-way comparison of two TB placeholders' name fields, skipping
 * each descriptor's 8-byte header. Returns 1 if a>b, 0xffffffff if a<b, else 0.
 * Confidence: high */
static uint32_t sk_tb_cmp3(uint64_t a, uint64_t b)
{
    int r;

    r = sk_memcmp(a + 8, b + 8, 0x100);
    if (r > 0) return 1;
    if (r < 0) return 0xffffffff;
    return 0;
}

/* FUN_0004ee94 @ 0x0004ee94   (est. sk_tb_cmp4)
 * Ghidra: uint FUN_0004ee94(long param_1,long param_2)
 * Identical 3-way comparison of two TB placeholders' name fields past the
 * 8-byte header. Returns 1 / 0xffffffff / 0.
 * Confidence: high */
static uint32_t sk_tb_cmp4(uint64_t a, uint64_t b)
{
    int r;

    r = sk_memcmp(a + 8, b + 8, 0x100);
    if (r > 0) return 1;
    if (r < 0) return 0xffffffff;
    return 0;
}

/* FUN_0004eec0 @ 0x0004eec0   (est. sk_tb_ph_dump)
 * Ghidra: long FUN_0004eec0(undefined8 param_1,ushort *param_2,long *param_3,undefined1 *param_4,ulong param_5)
 * Serializes a TB placeholder array into a destination buffer of 0x107-byte
 * records. For each record slot it either walks the placeholder entries by
 * index (fallback table absent) or resolves by payload match through the
 * registered match callback; on a match it computes the element's physical
 * address from the region {base,limit} and writes the 8-byte address into the
 * record. Returns the number of records written.
 * Confidence: high
 * Notes: kind table at 0x65bf70/0x65bf78/0x65bf80; panics with
 *   s_unknown_tbplaceholder_resource_t_005bb75b on kind > 0x1c and
 *   s_integer_overflow_005bb5bd on a bad offset field. Bounds violations hit
 *   SoftwareBreakpoint(0x5519,0x4f22c). */
static uint64_t sk_tb_ph_dump(uint64_t p, uint64_t ph, uint64_t region, uint64_t dst, uint64_t len)
{
    const uint8_t *phb = (const uint8_t *)ph;
    uint64_t kind, count, stride, i, tbl_a, tbl_b;
    uint64_t dst_end, out;
    uint64_t idx, found, off, val, r, ent;
    int resolved;

    (void)p;
    kind = (uint64_t)phb[0] | (uint64_t)phb[1] << 8 | (uint64_t)phb[2] << 16 | (uint64_t)phb[3] << 24;
    if (0x1c < (uint32_t)kind) {
        sk_panic_brk(0, (uint64_t)sk_str_unknown_tbplaceholder_resource_t_005bb75b);
    }
    if (len < 0x107) return 0;
    count = 0;
    i = 0;
    dst_end = dst + len;
    stride = len / 0x107;
    if (stride < 2) stride = 1;
    tbl_a = *(uint64_t *)(kind * 0x30 + 0x65bf80);
    tbl_b = *(uint64_t *)(kind * 0x30 + 0x65bf78);
    do {
        out = dst + i * 0x107;
        if (tbl_a == 0 || tbl_b == 0) {
            idx = 0;
            while ((ent = sk_tb_ph_resolve(ph, idx)) != 0) {
                if (out < dst || dst_end < out + 0x107) goto trap;
                if (sk_memcmp(ent + 8, out + 8, 0xff) == 0) {
                    if (out + 0x107 < out) goto trap;
                    off = (uint64_t)*(uint8_t *)(ent + 0x10a) << 0x10 |
                          (uint64_t)*(uint8_t *)(ent + 0x10b) << 0x18 |
                          (uint64_t)*(uint16_t *)(ent + 0x108) |
                          ((uint64_t)*(uint8_t *)(ent + 0x10e) << 0x10 |
                           (uint64_t)*(uint8_t *)(ent + 0x10f) << 0x18 |
                           (uint64_t)*(uint16_t *)(ent + 0x10c)) << 0x20;
                    val = 0;
                    if (off != 0) {
                        if ((*(uint8_t *)(ent + 0x10f) >> 2) != 0)
                            sk_fatal_printf((uint64_t)sk_str_integer_overflow_005bb5bd);
                        off = off * 0x40;
                        val = (off < *(uint64_t *)(region + 8)) ? off + *(uint64_t *)region : 0;
                    }
                    *(uint8_t *)(out + 0) = (uint8_t)val;
                    *(uint8_t *)(out + 5) = (uint8_t)(val >> 0x28);
                    *(uint8_t *)(out + 3) = (uint8_t)(val >> 0x18);
                    *(uint8_t *)(out + 2) = (uint8_t)(val >> 0x10);
                    *(uint8_t *)(out + 4) = (uint8_t)(val >> 0x20);
                    *(uint8_t *)(out + 1) = (uint8_t)(val >> 8);
                    *(uint8_t *)(out + 7) = (uint8_t)(val >> 0x38);
                    *(uint8_t *)(out + 6) = (uint8_t)(val >> 0x30);
                    count++;
                }
                idx++;
            }
        } else {
            found = 0;
            resolved = 0;
            if (out < dst || dst_end < out + 0x107) goto trap;
            if (ph == 0) {
                r = sk_tb_ph_find(0, out + 8, 0xff, &found);
                if (r != 0) resolved = 1;
            } else {
                r = sk_tb_ph_find(ph, out + 8, 0xff, &found);
                if ((r & 1) != 0) resolved = 1;
            }
            if (resolved) {
                ent = sk_tb_ph_resolve(ph, found);
                if (ent != 0 && sk_memcmp(ent + 8, out + 8, 0xff) == 0) {
                    if (out + 0x107 < out) goto trap;
                    off = (uint64_t)*(uint8_t *)(ent + 0x10a) << 0x10 |
                          (uint64_t)*(uint8_t *)(ent + 0x10b) << 0x18 |
                          (uint64_t)*(uint16_t *)(ent + 0x108) |
                          ((uint64_t)*(uint8_t *)(ent + 0x10e) << 0x10 |
                           (uint64_t)*(uint8_t *)(ent + 0x10f) << 0x18 |
                           (uint64_t)*(uint16_t *)(ent + 0x10c)) << 0x20;
                    val = 0;
                    if (off != 0) {
                        if ((*(uint8_t *)(ent + 0x10f) >> 2) != 0)
                            sk_fatal_printf((uint64_t)sk_str_integer_overflow_005bb5bd);
                        off = off * 0x40;
                        val = (off < *(uint64_t *)(region + 8)) ? off + *(uint64_t *)region : 0;
                    }
                    *(uint8_t *)(out + 0) = (uint8_t)val;
                    *(uint8_t *)(out + 5) = (uint8_t)(val >> 0x28);
                    *(uint8_t *)(out + 3) = (uint8_t)(val >> 0x18);
                    *(uint8_t *)(out + 2) = (uint8_t)(val >> 0x10);
                    *(uint8_t *)(out + 4) = (uint8_t)(val >> 0x20);
                    *(uint8_t *)(out + 1) = (uint8_t)(val >> 8);
                    *(uint8_t *)(out + 7) = (uint8_t)(val >> 0x38);
                    *(uint8_t *)(out + 6) = (uint8_t)(val >> 0x30);
                    count++;
                }
            }
        }
        i++;
    } while (i != stride);
    return count;
trap:
    SoftwareBreakpoint(0x5519, 0x4f22c);
    return count;
}

/* FUN_0004f258 @ 0x0004f258   (est. sk_tb_ph_dump2)
 * Ghidra: long FUN_0004f258(undefined8 param_1,ushort *param_2,undefined8 param_3,ulong param_4,ulong param_5)
 * Serializes a TB placeholder array into a destination buffer of 0x287-byte
 * records. For each record it resolves the matching placeholder element (by
 * index or by payload match) and invokes the per-element serializer
 * sk_x_00050ce8(arg, ent, out), accumulating the low 32 bits of its return.
 * Returns the number of records written.
 * Confidence: high
 * Notes: kind table at 0x65bf70 region; on kind > 0x1c panics with
 *   s_unknown_tbplaceholder_resource_t_005bb75b. Bounds violations hit
 *   SoftwareBreakpoint(0x5519,0x4f46c). */
static uint64_t sk_tb_ph_dump2(uint64_t p, uint64_t ph, uint64_t arg, uint64_t dst, uint64_t len)
{
    const uint8_t *phb = (const uint8_t *)ph;
    uint64_t kind, count, stride, i, tbl_a, tbl_b;
    uint64_t dst_end, out, found, r, ent;
    int resolved;

    (void)p;
    kind = (uint64_t)phb[0] | (uint64_t)phb[1] << 8 | (uint64_t)phb[2] << 16 | (uint64_t)phb[3] << 24;
    if (0x1c < (uint32_t)kind) {
        sk_panic_brk(0, (uint64_t)sk_str_unknown_tbplaceholder_resource_t_005bb75b);
    }
    if (len < 0x287) return 0;
    count = 0;
    i = 0;
    dst_end = dst + len;
    stride = len / 0x287;
    if (stride < 2) stride = 1;
    tbl_a = *(uint64_t *)(kind * 0x30 + 0x65bf80);
    tbl_b = *(uint64_t *)(kind * 0x30 + 0x65bf78);
    do {
        out = dst + i * 0x287;
        if (tbl_a == 0 || tbl_b == 0) {
            uint64_t j = 0;
            while ((ent = sk_tb_ph_resolve(ph, j)) != 0) {
                if (out < dst || dst_end < out + 0x287) goto trap;
                if (sk_memcmp(ent, out + 0x188, 0xff) == 0) {
                    if (out + 0x287 < out) goto trap;
                    count += sk_x_00050ce8(arg, ent, out) & 0xffffffff;
                }
                j++;
            }
        } else {
            found = 0;
            resolved = 0;
            if (out < dst || dst_end < out + 0x287) goto trap;
            if (ph == 0) {
                r = sk_tb_ph_find(0, out + 0x188, 0xff, &found);
                if (r != 0) resolved = 1;
            } else {
                r = sk_tb_ph_find(ph, out + 0x188, 0xff, &found);
                if ((r & 1) != 0) resolved = 1;
            }
            if (resolved) {
                ent = sk_tb_ph_resolve(ph, found);
                if (ent != 0 && sk_memcmp(ent, out + 0x188, 0xff) == 0) {
                    if (out + 0x287 < out) goto trap;
                    count += sk_x_00050ce8(arg, ent, out) & 0xffffffff;
                }
            }
        }
        i++;
    } while (i != stride);
    return count;
trap:
    SoftwareBreakpoint(0x5519, 0x4f46c);
    return count;
}

/* FUN_0004f480 @ 0x0004f480   (est. sk_tb_ph_name2)
 * Ghidra: void FUN_0004f480(undefined8 param_1,ulong param_2,code *param_3,undefined8 param_4)
 * Looks up a TB placeholder by name into a larger (0x120-byte) work buffer:
 * zeroes the buffer, resolves the name, copies it (0x120 max), and invokes the
 * caller callback with (arg, buffer) when found. Returns void.
 * Confidence: high
 * Notes: variant of sk_tb_ph_name with a bigger buffer; sk_x_00050c88 is the
 *   name resolver. Stack canary protected. */
static void sk_tb_ph_name2(uint64_t name, uint64_t len, uint64_t cb, uint64_t arg)
{
    uint8_t buf[0x120];               /* auStack_168 */
    uint64_t canary = 0xd37afd4bb400012aULL;   /* local_48 */
    long found;

    sk_memset0(buf, 0x120);
    found = sk_x_00050c88(name, len);
    if (found != 0) {
        if (0xff < len) len = 0x100;
        sk_string_set(buf, found, len, 0x120);
        ((void (*)(uint64_t, void *))cb)(arg, buf);
    }
    if (canary == 0xd37afd4bb400012aULL) return;
    sk_stack_chk_fail(found != 0);
}

/* FUN_0004f544 @ 0x0004f544   (est. sk_tb_cmp)
 * Ghidra: uint FUN_0004f544(undefined8 param_1,undefined8 param_2)
 * Lexicographic 3-way comparison of two TB placeholders by their full 0x100-byte
 * name fields. Returns 1 if a>b, 0xffffffff if a<b, else 0.
 * Confidence: high */
static uint32_t sk_tb_cmp(uint64_t a, uint64_t b)
{
    int r;

    r = sk_memcmp(a, b, 0x100);
    if (r > 0) return 1;
    if (r < 0) return 0xffffffff;
    return 0;
}

/* FUN_0004f548 @ 0x0004f548   (est. sk_tb_cmp2)
 * Ghidra: uint FUN_0004f548(undefined8 param_1,undefined8 param_2)
 * Identical 3-way comparison of two TB placeholders' full 0x100-byte name
 * fields. Returns 1 / 0xffffffff / 0.
 * Confidence: high */
static uint32_t sk_tb_cmp2(uint64_t a, uint64_t b)
{
    int r;

    r = sk_memcmp(a, b, 0x100);
    if (r > 0) return 1;
    if (r < 0) return 0xffffffff;
    return 0;
}

/* FUN_0004f56c @ 0x0004f56c   (est. sk_tb_ph_dump3)
 * Ghidra: long FUN_0004f56c(undefined8 param_1,ushort *param_2,undefined8 param_3,ulong param_4,ulong param_5)
 * Serializes a TB placeholder array into a destination buffer of 0x107-byte
 * records. For each record it resolves the matching placeholder element and
 * invokes the per-element serializer sk_x_00051488(arg, ent, out) when the
 * payload bytes (0xe0) match, counting each write. Returns the record count.
 * Confidence: high
 * Notes: kind table at 0x65bf70 region; kind > 0x1c panics with
 *   s_unknown_tbplaceholder_resource_t_005bb75b. Bounds violations hit
 *   SoftwareBreakpoint(0x5519,0x4f780). */
static uint64_t sk_tb_ph_dump3(uint64_t p, uint64_t ph, uint64_t arg, uint64_t dst, uint64_t len)
{
    const uint8_t *phb = (const uint8_t *)ph;
    uint64_t kind, count, stride, i, tbl_a, tbl_b;
    uint64_t dst_end, out, found, r, ent;
    int resolved;

    (void)p;
    kind = (uint64_t)phb[0] | (uint64_t)phb[1] << 8 | (uint64_t)phb[2] << 16 | (uint64_t)phb[3] << 24;
    if (0x1c < (uint32_t)kind) {
        sk_panic_brk(0, (uint64_t)sk_str_unknown_tbplaceholder_resource_t_005bb75b);
    }
    if (len < 0x107) return 0;
    count = 0;
    i = 0;
    dst_end = dst + len;
    stride = len / 0x107;
    if (stride < 2) stride = 1;
    tbl_a = *(uint64_t *)(kind * 0x30 + 0x65bf80);
    tbl_b = *(uint64_t *)(kind * 0x30 + 0x65bf78);
    do {
        out = dst + i * 0x107;
        if (tbl_a == 0 || tbl_b == 0) {
            uint64_t j = 0;
            while ((ent = sk_tb_ph_resolve(ph, j)) != 0) {
                if (out < dst || dst_end < out + 0x107) goto trap;
                if (sk_memcmp(ent, out + 8, 0xe0) == 0) {
                    if (out + 0x107 < out) goto trap;
                    sk_x_00051488(arg, ent, out);
                    count++;
                }
                j++;
            }
        } else {
            found = 0;
            resolved = 0;
            if (out < dst || dst_end < out + 0x107) goto trap;
            if (ph == 0) {
                r = sk_tb_ph_find(0, out + 8, 0xe0, &found);
                if (r != 0) resolved = 1;
            } else {
                r = sk_tb_ph_find(ph, out + 8, 0xe0, &found);
                if ((r & 1) != 0) resolved = 1;
            }
            if (resolved) {
                ent = sk_tb_ph_resolve(ph, found);
                if (ent != 0 && sk_memcmp(ent, out + 8, 0xe0) == 0) {
                    if (out + 0x107 < out) goto trap;
                    sk_x_00051488(arg, ent, out);
                    count++;
                }
            }
        }
        i++;
    } while (i != stride);
    return count;
trap:
    SoftwareBreakpoint(0x5519, 0x4f780);
    return count;
}

/* FUN_0004f794 @ 0x0004f794   (est. sk_tb_ph_one8)
 * Ghidra: bool FUN_0004f794(undefined8 *param_1,long param_2,code *param_3,undefined8 param_4)
 * Serializes a single 8-byte TB placeholder element: if the element size is 8,
 * reads the 8-byte word at `in` and invokes the callback with (arg, &word).
 * Returns whether the element size is 8.
 * Confidence: high
 * Notes: bounds violation on the source pointer hits
 *   SoftwareBreakpoint(0x5519,0x4f7f8). */
static bool sk_tb_ph_one8(uint64_t in, long size, uint64_t cb, uint64_t arg)
{
    uint64_t w;

    if (size == 8) {
        if (in + 8 < in) {
            SoftwareBreakpoint(0x5519, 0x4f7f8);
            return size == 8;
        }
        w = *(uint64_t *)in;
        ((void (*)(uint64_t, uint64_t *))cb)(arg, &w);
    }
    return size == 8;
}

/* FUN_0004f890 @ 0x0004f890   (est. sk_tb_ph_addr2)
 * Ghidra: long FUN_0004f890(undefined8 param_1,long param_2,long *param_3,ushort *param_4,ulong param_5)
 * Resolves the physical addresses of a TB placeholder array stored as 16-byte
 * records: for each record it reads the 8-byte key, finds the matching
 * placeholder element (by key match through the find callback), and writes the
 * element's resolved physical address (offset*0x40 past the region base, or 0
 * if out of range) back into the record at +8. Returns the count resolved.
 * Confidence: high
 * Notes: panics with s_integer_overflow_005bb5bd on a bad offset field;
 *   bounds violations hit SoftwareBreakpoint(0x5519,0x4fafc). */
static uint64_t sk_tb_ph_addr2(uint64_t p, long sel, uint64_t region, uint64_t ph, uint64_t len)
{
    uint64_t count, iters, cur, found, key, off, val, r, ent;
    int resolved;

    (void)p;
    if (len < 0x10) return 0;
    count = 0;
    iters = len >> 4;
    cur = ph;
    do {
        found = 0;
        if (cur < ph || ph + len < cur + 8) {
            SoftwareBreakpoint(0x5519, 0x4fafc);
            return count;
        }
        key = *(uint64_t *)cur;
        resolved = 0;
        if (sel == 0) {
            r = sk_tb_ph_find(0, cur, 8, &found);
            if (r != 0) resolved = 1;
        } else {
            r = sk_tb_ph_find(sel, cur, 8, &found);
            if ((r & 1) != 0) resolved = 1;
        }
        if (resolved) {
            ent = sk_tb_ph_resolve(sel, found);
            if (ent != 0 && *(uint64_t *)ent == key) {
                if ((*(uint8_t *)(ent + 0xf) >> 2) != 0)
                    sk_fatal_printf((uint64_t)sk_str_integer_overflow_005bb5bd);
                off = *(uint64_t *)(ent + 8) * 0x40;
                if (off < *(uint64_t *)(region + 8)) val = off + *(uint64_t *)region;
                else val = 0;
                *(uint64_t *)(cur + 8) = val;
                count++;
            }
        }
        cur += 8;
        iters--;
    } while (iters != 0);
    return count;
}

/* FUN_0004fb08 @ 0x0004fb08   (est. sk_tb_ph_dt)
 * Ghidra: long FUN_0004fb08(undefined8 param_1,long param_2,long *param_3,undefined1 *param_4,ulong param_5)
 * Builds a device-tree space mapping from a TB placeholder into a destination
 * buffer of 0x18-byte records. For each record it resolves the placeholder's
 * element count and first element, computes the element's physical address
 * (offset*0x40 past the region base), allocates a 0x1800-byte device-tree span
 * through the ep object vtable, maps the frame, and writes a 24-byte record
 * carrying the resolved span (bytes 8..15 of the descriptor) plus the element's
 * key and payload. Returns the number of records built.
 * Confidence: medium
 * Notes: vtable calls through sk_ep_obj_get() (+0x30 alloc, +8 on the frame);
 *   panics with s_failed_to_create_device_tree_spa_005bb844 and falls to
 *   SoftwareBreakpoint(0x5519,0x4fe70) on alloc failure; sk_x_00054354 is
 *   noreturn when the frame is null. The 0x64cb40 range check is a decompiler
 *   string-region probe on the error code. Ghidra also emits dead stores to a
 *   9-byte zeroed local (local_68=9, local_67..61=0) that are unused. */
static uint64_t sk_tb_ph_dt(uint64_t p, uint64_t ph, uint64_t region, uint64_t dst, uint64_t len)
{
    uint64_t count, iters, out, cnt, off, val, u20, err, ent;
    uint8_t l80[16];
    uint64_t l90, l88;
    sk_ep_pair_t ep;

    (void)p;
    if (len < 0x18) return 0;
    count = 0;
    iters = len / 0x18;
    out = dst;
    do {
        cnt = sk_tb_ph_count(ph == 0 ? 0 : ph);
        if (cnt != 0) {
            ent = sk_tb_ph_resolve(ph, 0);
            if (ent != 0) {
                if ((*(uint8_t *)(ent + 0x17) >> 2) != 0)
                    sk_fatal_printf((uint64_t)sk_str_integer_overflow_005bb5bd);
                off = (uint64_t)*(uint8_t *)(ent + 0x12) << 0x10 |
                      (uint64_t)*(uint8_t *)(ent + 0x13) << 0x18 |
                      (uint64_t)*(uint16_t *)(ent + 0x10) |
                      ((uint64_t)*(uint8_t *)(ent + 0x16) << 0x10 |
                       (uint64_t)*(uint8_t *)(ent + 0x17) << 0x18 |
                       (uint64_t)*(uint16_t *)(ent + 0x14)) << 0x20;
                off = off * 0x40;
                if (off < *(uint64_t *)(region + 8)) val = off + *(uint64_t *)region;
                else val = 0;
                u20 = (*(uint64_t *)(ent + 8) + 0x3fff) & 0xffffffffffffc000;
                l80[0] = 0x11;
                sk_memset0(l80 + 1, 0xf);
                l90 = 0;
                l88 = 0;
                ep = sk_ep_obj_get();
                err = (*(uint64_t (**)(uint64_t, uint64_t, uint8_t *, uint64_t *, uint64_t, uint64_t))
                        (ep.hi + 0x30))(ep.lo, 0x1800, l80, &l90, 0, 0);
                err = err & 0xff;
                if (err != 0) {
                    if (((uint64_t *)0x64cb3f < (uint64_t *)0x64cb40 + err) &&
                        ((uint64_t *)0x64cb48 + err < (uint64_t *)0x64cb81) &&
                        ((uint64_t *)0x64cb40 + err <= (uint64_t *)0x64cb48 + err)) {
                        sk_panic_brk(0, (uint64_t)sk_str_failed_to_create_device_tree_spa_005bb844);
                    }
                    SoftwareBreakpoint(0x5519, 0x4fe70);
                    return count;
                }
                sk_x_000510e4(val, l90, l88, u20);
                if (l88 == 0) sk_x_00054354();
                (*(void (**)(uint64_t, uint8_t *))(l88 + 8))(l90, l80);
                if (out < dst || dst + len < out + 0x18) {
                    SoftwareBreakpoint(0x5519, 0x4fe70);
                    return count;
                }
                /* record[0..8) = descriptor bytes 8..15 */
                *(uint8_t *)(out + 0) = l80[8];
                *(uint8_t *)(out + 1) = l80[9];
                *(uint8_t *)(out + 2) = l80[10];
                *(uint8_t *)(out + 3) = l80[11];
                *(uint8_t *)(out + 4) = l80[12];
                *(uint8_t *)(out + 5) = l80[13];
                *(uint8_t *)(out + 6) = l80[14];
                *(uint8_t *)(out + 7) = l80[15];
                /* record[8..16) = element key (bytes 8..15) */
                *(uint8_t *)(out + 0xd) = *(uint8_t *)(ent + 0xd);
                *(uint8_t *)(out + 8) = *(uint8_t *)(ent + 8);
                *(uint8_t *)(out + 0xb) = *(uint8_t *)(ent + 0xb);
                *(uint8_t *)(out + 10) = *(uint8_t *)(ent + 10);
                *(uint8_t *)(out + 9) = *(uint8_t *)(ent + 9);
                *(uint8_t *)(out + 0xc) = *(uint8_t *)(ent + 0xc);
                *(uint8_t *)(out + 0xf) = *(uint8_t *)(ent + 0xf);
                *(uint8_t *)(out + 0xe) = *(uint8_t *)(ent + 0xe);
                /* record[16..24) = element payload (bytes 0..7) */
                *(uint8_t *)(out + 0x15) = *(uint8_t *)(ent + 5);
                *(uint8_t *)(out + 0x11) = *(uint8_t *)(ent + 1);
                *(uint8_t *)(out + 0x10) = *(uint8_t *)(ent + 0);
                *(uint8_t *)(out + 0x13) = *(uint8_t *)(ent + 3);
                *(uint8_t *)(out + 0x12) = *(uint8_t *)(ent + 2);
                *(uint8_t *)(out + 0x14) = *(uint8_t *)(ent + 4);
                *(uint8_t *)(out + 0x17) = *(uint8_t *)(ent + 7);
                *(uint8_t *)(out + 0x16) = *(uint8_t *)(ent + 6);
                count++;
            }
        }
        out += 0x18;
        iters--;
    } while (iters != 0);
    return count;
}

/* FUN_0004fe80 @ 0x0004fe80   (est. sk_tb_ph_ready)
 * Ghidra: bool FUN_0004fe80(void)
 * Returns whether the TB placeholder resources are ready: reads the per-cpu
 * global config, and reports true only if the region list (+0x78) and range
 * base (+0xa8) are nonzero and the range length (+0xb0) is nonzero. On a config
 * overflow the fatal breakpoint fires.
 * Confidence: high
 * Notes: sk_x_00054610 is the per-cpu config getter. */
static bool sk_tb_ph_ready(void)
{
    uint64_t cfg;

    cfg = sk_x_00054610();
    if (cfg <= cfg + 0x160) {
        if (*(long *)(cfg + 0x78) == 0 || *(long *)(cfg + 0xa8) == 0) return false;
        return *(long *)(cfg + 0xb0) != 0;
    }
    SoftwareBreakpoint(0x5519, 0x4fed0);
    return false;
}

/* FUN_0004fed0 @ 0x0004fed0   (est. sk_tb_ph_reloc)
 * Ghidra: void FUN_0004fed0(undefined8 param_1,ushort *param_2,undefined8 param_3,
 *   undefined8 param_4, long param_5, undefined8 param_6)
 * Applies a relocation to a TB placeholder segment: looks up the segment by
 * (seg, name), and if the placeholder's kind has a relocation callback
 * registered (+0x65bf90 with a nonzero table entry +0x65bf88), resolves the
 * segment base, adds the offset, validates the range does not wrap, and invokes
 * the callback with (p, ph, arg).
 * Confidence: medium
 * Notes: sk_x_00051e5c is the segment lookup, sk_x_00051ee4 the segment-base
 *   resolver; the callback is an indirect call (Ghidra: "could not recover
 *   jumptable"). Kind > 0x1c panics with
 *   s_unknown_tbplaceholder_resource_t_005bb75b; overflow hits
 *   SoftwareBreakpoint(0x5519,0x4ff80). */
static void sk_tb_ph_reloc(uint64_t p, uint64_t ph, uint64_t arg, uint64_t seg, long off, uint64_t name)
{
    const uint8_t *phb = (const uint8_t *)ph;
    uint64_t kind, seg2, cb, base, addr, end;

    seg2 = sk_x_00051e5c(seg, name);
    kind = (uint64_t)phb[0] | (uint64_t)phb[1] << 8 | (uint64_t)phb[2] << 16 | (uint64_t)phb[3] << 24;
    if (0x1c < (uint32_t)kind) {
        sk_panic_brk(0, (uint64_t)sk_str_unknown_tbplaceholder_resource_t_005bb75b);
    }
    cb = *(uint64_t *)(kind * 0x30 + 0x65bf90);
    if ((cb != 0) && (*(long *)(kind * 0x30 + 0x65bf88) != 0 && seg2 != 0)) {
        base = sk_x_00051ee4(seg, name);
        if (base != 0) {
            addr = *(long *)(base + 0x20) + off;
            end = addr + *(uint64_t *)(base + 0x28);
            if (end < addr || end - addr < *(uint64_t *)(base + 0x28)) {
                SoftwareBreakpoint(0x5519, 0x4ff80);
                return;
            }
            ((void (*)(uint64_t, uint64_t, uint64_t))cb)(p, ph, arg);
        }
    }
}

/* FUN_0004ffd0 @ 0x0004ffd0   (est. sk_tb_ph_scan)
 * Ghidra: void FUN_0004ffd0(int param_1,uint param_2)
 * Scans every loaded image in the boot list, and for each image that is a
 * "live" placeholder segment walks its TB placeholder entries via the iterator
 * and applies relocations: __PDATA when do_pdata is set, and __DATA unless
 * flag bit 0 is set. Skips placeholder descriptors whose first word is nonzero.
 * Confidence: medium
 * Notes: sk_x_0005ba14 is the image list head, sk_tb_ph_avail the base getter,
 *   sk_tb_ph_iter_next walks entries, sk_tb_ph_range2 provides the arg. Bounds
 *   violations hit SoftwareBreakpoint(0x5519,0x501cc). */
static void sk_tb_ph_scan(int do_pdata, uint32_t flags)
{
    long *img;
    uint64_t u, base, key, key2;
    sk_ep_pair_t r;
    uint64_t it[2];
    uint64_t ph;
    const uint8_t *pb;

    img = (long *)sk_x_0005ba14();
    u = sk_tb_ph_avail();
    if (u != 0 && u + 8 < u) {
        SoftwareBreakpoint(0x5519, 0x501cc);
        return;
    }
    r = sk_tb_ph_range2();
    while (img != 0) {
        if (*(char *)(img + 1) < '\0') {
            base = (uint64_t)img[7];
            it[0] = u;
            it[1] = 0;
            ph = sk_tb_ph_iter_next((uint64_t)it);
            while (ph != 0) {
                pb = (const uint8_t *)ph;
                if ((uint16_t *)(uint64_t)pb + 6 < (uint16_t *)(uint64_t)pb) goto trap;
                if (((uint8_t)pb[2] == 0 && *(uint8_t *)(pb + 3) == 0) && *(uint16_t *)(pb + 0) == 0) {
                    key = (uint64_t)pb[3] << 0x10 | (uint64_t)pb[7] << 0x18 |
                          (uint64_t)*(uint16_t *)(pb + 4) |
                          ((uint64_t)pb[5] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    key2 = (uint64_t)pb[3] << 0x10 | (uint64_t)pb[7] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 4) |
                           ((uint64_t)pb[5] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                            (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    if (do_pdata != 0) {
                        if (base + 0x20 < base) goto trap;
                        sk_tb_ph_reloc(u, ph, r.lo, base, (long)img[4],
                                       (uint64_t)sk_str___PDATA_005bb7ae);
                    }
                    if ((flags & 1) == 0) {
                        if (key < key2 || base + 0x20 < base) goto trap;
                        sk_tb_ph_reloc(u, ph, r.lo, base, (long)img[4],
                                       (uint64_t)sk_str___DATA_005bb23b);
                    }
                }
                ph = sk_tb_ph_iter_next((uint64_t)it);
            }
        }
        img = (long *)*img;
    }
    return;
trap:
    SoftwareBreakpoint(0x5519, 0x501cc);
}

/* FUN_000501cc @ 0x000501cc   (est. sk_tb_ph_reloc_all)
 * Ghidra: void FUN_000501cc(int param_1,int param_2)
 * Relocates every loaded image's TB placeholder segments: for each live segment
 * walks its placeholder entries, applying __DATA relocations when param_2 is
 * nonzero and the entry kind is 0, and __PDATA (param_1 set) plus __DATA for
 * every nonzero-kind entry. Bounds violations abort to the fatal breakpoint.
 * Confidence: medium
 * Notes: sk_x_0005ba14 image list head, sk_tb_ph_avail base, sk_tb_ph_range2
 *   arg; Bounds violations hit SoftwareBreakpoint(0x5519,0x50444). */
static void sk_tb_ph_reloc_all(int a, int b)
{
    long *img;
    uint64_t u, base, key, key2, u1;
    sk_ep_pair_t r;
    uint64_t it[2];
    uint64_t ph;
    const uint8_t *pb;
    uint32_t kind;

    img = (long *)sk_x_0005ba14();
    u = sk_tb_ph_avail();
    if (u != 0 && u + 8 < u) {
        SoftwareBreakpoint(0x5519, 0x50444);
        return;
    }
    r = sk_tb_ph_range2();
    while (img != 0) {
        if (*(char *)(img + 1) < '\0') {
            base = (uint64_t)img[7];
            it[0] = u;
            it[1] = 0;
            ph = sk_tb_ph_iter_next((uint64_t)it);
            if (ph != 0) {
                u1 = base + 0x20;
                do {
                    pb = (const uint8_t *)ph;
                    if ((uint16_t *)(uint64_t)pb + 6 < (uint16_t *)(uint64_t)pb) goto trap;
                    key = (uint64_t)pb[3] << 0x10 | (uint64_t)pb[7] << 0x18 |
                          (uint64_t)*(uint16_t *)(pb + 4) |
                          ((uint64_t)pb[5] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    key2 = (uint64_t)pb[3] << 0x10 | (uint64_t)pb[7] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 4) |
                           ((uint64_t)pb[5] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                            (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    kind = (uint32_t)pb[1] << 0x10 | (uint32_t)pb[3] << 0x18 |
                           (uint32_t)*(uint16_t *)(pb + 0);
                    if ((b != 0) && (kind == 0)) {
                        if (u1 < base) goto trap;
                        sk_tb_ph_reloc(u, ph, r.lo, base, (long)img[4],
                                       (uint64_t)sk_str___DATA_005bb23b);
                        if (key < key2 || u1 < base) goto trap;
                        kind = (uint32_t)pb[1] << 0x10 | (uint32_t)pb[3] << 0x18 |
                               (uint32_t)*(uint16_t *)(pb + 0);
                    }
                    if (kind != 0) {
                        if (a != 0) {
                            if (u1 < base) goto trap;
                            sk_tb_ph_reloc(u, ph, r.lo, base, (long)img[4],
                                           (uint64_t)sk_str___PDATA_005bb7ae);
                        }
                        if (key < key2 || u1 < base) goto trap;
                        sk_tb_ph_reloc(u, ph, r.lo, base, (long)img[4],
                                       (uint64_t)sk_str___DATA_005bb23b);
                    }
                    ph = sk_tb_ph_iter_next((uint64_t)it);
                } while (ph != 0);
            }
        }
        img = (long *)*img;
    }
    return;
trap:
    SoftwareBreakpoint(0x5519, 0x50444);
}

/* FUN_00050444 @ 0x00050444   (est. sk_tb_ph_dump_res)
 * Ghidra: void FUN_00050444(undefined8 param_1)
 * Dumps the resource entries of a TB placeholder of kind 0xb: walks every
 * placeholder descriptor, and for a kind-0xb placeholder iterates its elements
 * and emits each element's 8-byte key via sk_x_0005cf4c. If no kind-0xb
 * placeholder is found, emits the literal tag 0x706c6174 ("plat").
 * Confidence: medium
 * Notes: sk_x_0005cf4c is the emit helper; sk_tb_ph_avail base, iterator next,
 *   count and resolve walk the placeholders. Bounds violations hit
 *   SoftwareBreakpoint(0x5519,0x50654). */
static void sk_tb_ph_dump_res(uint64_t arg)
{
    uint64_t u;
    uint64_t it[2];
    uint64_t ph, ent;
    const uint8_t *pb, *eb;
    uint64_t cnt, i, key, key2;
    int found;

    u = sk_tb_ph_avail();
    if (u != 0 && u + 8 < u) {
        SoftwareBreakpoint(0x5519, 0x50654);
        return;
    }
    it[0] = u;
    it[1] = 0;
    ph = sk_tb_ph_iter_next((uint64_t)it);
    if (ph != 0) {
        found = 0;
        do {
            pb = (const uint8_t *)ph;
            if ((uint16_t *)(uint64_t)pb + 6 < (uint16_t *)(uint64_t)pb) goto trap;
            if (((uint32_t)pb[1] << 0x10 | (uint32_t)pb[3] << 0x18 |
                 (uint32_t)*(uint16_t *)(pb + 0)) == 0xb) {
                cnt = sk_tb_ph_count(ph);
                if (cnt != 0) {
                    key = (uint64_t)pb[6] << 0x10 | (uint64_t)pb[7] << 0x18 |
                          (uint64_t)*(uint16_t *)(pb + 4) |
                          ((uint64_t)pb[10] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    key2 = (uint64_t)pb[6] << 0x10 | (uint64_t)pb[7] << 0x18 |
                           (uint64_t)*(uint16_t *)(pb + 4) |
                           ((uint64_t)pb[10] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                            (uint64_t)*(uint16_t *)(pb + 8)) << 0x20;
                    i = 0;
                    do {
                        if (key < key2) goto trap;
                        ent = sk_tb_ph_resolve(ph, i);
                        eb = (const uint8_t *)ent;
                        sk_x_0005cf4c((uint64_t)eb[1] << 0x10 | (uint64_t)eb[3] << 0x18 |
                                      (uint64_t)*(uint16_t *)(eb + 0) |
                                      ((uint64_t)eb[3] << 0x10 | (uint64_t)eb[7] << 0x18 |
                                       (uint64_t)*(uint16_t *)(eb + 2)) << 0x20,
                                     arg);
                        i++;
                    } while (cnt != i);
                }
                found = 1;
            }
            ph = sk_tb_ph_iter_next((uint64_t)it);
        } while (ph != 0);
        if (found) return;
    }
    sk_x_0005cf4c(0x706c6174, arg);
    return;
trap:
    SoftwareBreakpoint(0x5519, 0x50654);
}

/* FUN_00050654 @ 0x00050654   (est. sk_tb_ph_lookup)
 * Ghidra: long FUN_00050654(undefined8 param_1,ulong param_2)
 * Looks up a TB placeholder element by key: iterates the placeholder descriptors
 * anchored at `p`, and for a descriptor whose first word is zero and payload
 * span exceeds 0x10f, scans its elements (0x110 bytes each) for a matching
 * 8-byte key. On a match returns the element's physical address (offset*0x40
 * past the range base) when it fits within the range, else 0.
 * Confidence: medium
 * Notes: panics with s_integer_overflow_005bb5bd on a bad offset field; bounds
 *   violations hit SoftwareBreakpoint(0x5519,0x5082c). */
static uint64_t sk_tb_ph_lookup(uint64_t p, uint64_t key)
{
    sk_ep_pair_t r;
    uint64_t it[2];
    uint64_t ph, ent;
    const uint8_t *pb, *eb;
    uint64_t n, i, off;

    r = sk_tb_ph_range2();
    it[0] = p;
    it[1] = 0;
    ph = sk_tb_ph_iter_next((uint64_t)it);
    do {
        if (ph == 0) return 0;
        pb = (const uint8_t *)ph;
        if ((uint16_t *)(uint64_t)pb + 6 < (uint16_t *)(uint64_t)pb) {
            SoftwareBreakpoint(0x5519, 0x5082c);
            return 0;
        }
        if ((((uint8_t)pb[2] == 0 && *(uint8_t *)(pb + 3) == 0) && *(uint16_t *)(pb + 0) == 0) &&
            (n = (uint64_t)pb[3] << 0x10 | (uint64_t)pb[7] << 0x18 |
                 (uint64_t)*(uint16_t *)(pb + 4) |
                 ((uint64_t)pb[5] << 0x10 | (uint64_t)pb[0xb] << 0x18 |
                  (uint64_t)*(uint16_t *)(pb + 8)) << 0x20,
             0x10f < n)) {
            i = 0;
            do {
                ent = sk_tb_ph_resolve(ph, i);
                eb = (const uint8_t *)ent;
                if ((uint64_t)eb[1] << 0x10 | (uint64_t)eb[3] << 0x18 |
                    (uint64_t)*(uint16_t *)(eb + 0) |
                    ((uint64_t)eb[3] << 0x10 | (uint64_t)eb[7] << 0x18 |
                     (uint64_t)*(uint16_t *)(eb + 2)) << 0x20 == key) {
                    if ((*(uint8_t *)(eb + 0x10f) >> 2) != 0)
                        sk_fatal_printf((uint64_t)sk_str_integer_overflow_005bb5bd);
                    off = (uint64_t)eb[0x10a] << 0x10 | (uint64_t)eb[0x10b] << 0x18 |
                          (uint64_t)*(uint16_t *)(eb + 0x108) |
                          ((uint64_t)eb[0x10e] << 0x10 | (uint64_t)eb[0x10f] << 0x18 |
                           (uint64_t)*(uint16_t *)(eb + 0x10c)) << 0x20;
                    if (off << 6 < r.hi) return r.lo + off * 0x40;
                    return 0;
                }
                i++;
            } while (i < n / 0x110);
        }
        ph = sk_tb_ph_iter_next((uint64_t)it);
    } while (1);
}

/* FUN_00050838 @ 0x00050838   (est. sk_tb_ph_get)
 * Ghidra: undefined8 FUN_00050838(long *param_1,undefined8 *param_2,ulong *param_3)
 * Publishes the current TB placeholder descriptor triplet (base at 0x6af868,
 * value at 0x6af870, limit at 0x6af878) after (re)initializing it via
 * sk_x_0005d470. If the base or limit is null returns 0; otherwise writes the
 * three fields through the out params and returns 1.
 * Confidence: medium
 * Notes: reads the globals DAT_006af868/870/878; sk_x_0005d470 is the
 *   initializer, sk_x_000508e8 the callback. Overflow on the limit field hits
 *   SoftwareBreakpoint(0x5519,0x508e8). */
static uint64_t sk_tb_ph_get(long *out, uint64_t *a, uint64_t *b)
{
    uint64_t *g;
    uint64_t v;

    g = (uint64_t *)0x6af868;
    sk_x_0005d470(0x6af880, (uint64_t)sk_x_000508e8, (uint64_t)&g);
    v = *(uint64_t *)0x6af870;
    if (*(uint64_t *)0x6af868 == 0 || *(uint64_t *)0x6af878 == 0) {
        return 0;
    }
    *out = (long)*(uint64_t *)0x6af868;
    *a = v;
    if ((*(uint64_t *)0x6af878 != 0 && *(uint64_t *)0x6af878 + 8 <= *(uint64_t *)0x6af878) &&
        (*(uint64_t *)0x6af878 == 0 || *(uint64_t *)0x6af878 != *(uint64_t *)0x6af878 + 8)) {
        SoftwareBreakpoint(0x5519, 0x508e8);
        return 1;
    }
    *b = *(uint64_t *)0x6af878;
    return 1;
}
/* File-local state backing Ghidra globals DAT_006af888..006af8b8 and
 * DAT_006ad6e8/ea (the shared region table and tb live/debug flags). */
static uint8_t   sk_region_table_ready;   /* DAT_006af888  */
static uint32_t *sk_region_table;         /* _DAT_006af890 */
static uint32_t *sk_region_count_ptr;     /* _DAT_006af898 */
static uintptr_t  sk_region_lo;           /* _DAT_006af8b0 */
static uintptr_t  sk_region_hi;           /* _DAT_006af8b8 */
static uintptr_t  sk_region_list_a;       /* _DAT_006af8a0 */
static uintptr_t  sk_region_list_b;       /* _DAT_006af8a8 */
static uint8_t    sk_tb_live_flag;        /* DAT_006ad6e8 */
static uint8_t    sk_tb_debug_flag;       /* DAT_006ad6ea */

/* FUN_000508e8 @ 0x000508e8   (sk_tb_ph_map_subgraph)
 * Ghidra: void FUN_000508e8(long *param_1)
 * Walks every page-hierarchy subgraph element in the current tb_ph range and
 * maps each into a freshly allocated frame region, chaining cumulative
 * offsets into the caller's *out list (an array of ulong entries). Fatal on a
 * corrupted iterator, an out-of-range region index, or a failed allocation.
 * Confidence: medium
 * Notes: sk_tb_ph_range2 / sk_tb_ph_get / sk_tb_ph_iter_* helpers; the 16-byte
 * pair returns of sk_tb_ph_range2 and sk_ep_obj_get are modeled as structs;
 * string refs 0x5bb874 / 0x5bb8ca; SoftwareBreakpoint 0x5519 @ 0x50c84. */
static void sk_tb_ph_map_subgraph(long *out)
{
    typedef sk_ep_pair_t sk_range_t;
    typedef sk_ep_pair_t sk_obj_t;
    uint16_t *elem;
    uint64_t total, size, out_off;
    uint64_t cursor[2];

    if (out == 0) {
        return;
    }
    long t_out = 0; uint64_t t_a = 0, t_b = 0;
    sk_range_t rng = sk_tb_ph_range2();
    (void)sk_tb_ph_get(&t_out, &t_a, &t_b);
    total = (uint64_t)t_out;
    if ((total == 0) || (total <= total + 8)) {
        cursor[0] = total;
        cursor[1] = 0;
        do {
            elem = (uint16_t *)sk_tb_ph_iter_next(cursor);
            if (elem == 0) {
                return;
            }
            if (elem + 6 < elem) {
                goto corrupt;
            }
        } while (((uint)(uint8_t)elem[1] << 0x10 | (uint)*(uint8_t *)((long)elem + 3) << 0x18 |
                  (uint)*elem) != 10);
        if (0x17 < ((uint64_t)(uint8_t)elem[3] << 0x10 | (uint64_t)*(uint8_t *)((long)elem + 7) << 0x18 |
                    (uint64_t)elem[2] |
                    (uint64_t)((uint)(uint8_t)elem[5] << 0x10 |
                               (uint)*(uint8_t *)((long)elem + 0xb) << 0x18 | (uint)elem[4]) << 0x20) - 0x18) {
            sk_printf(sk_str_warning_found_zu_subgraphs);
        }
        elem = (uint16_t *)sk_tb_ph_iter_init(elem, 0);
        {
            uint16_t u6 = elem[8];
            uint16_t u5 = elem[10];
            uint8_t  b2 = *(uint8_t *)((long)elem + 0x17);
            uint16_t u7 = elem[0xb];
            if (b2 >> 2 != 0) {
                sk_fatal_printf(sk_str_integer_overflow);
            }
            uint8_t  u3 = *(uint8_t *)((long)elem + 0x11);
            uint8_t  b4 = *(uint8_t *)((long)elem + 0x13);
            uint8_t  u8 = (uint8_t)elem[9];
            size = ((uint64_t)(uint8_t)elem[1] << 0x10 | (uint64_t)*(uint8_t *)((long)elem + 3) << 0x18 |
                    (uint64_t)*elem |
                    (uint64_t)((uint)(uint8_t)elem[3] << 0x10 |
                               (uint)*(uint8_t *)((long)elem + 7) << 0x18 | (uint)elem[2]) << 0x20) + 0x3fff +
                   ((uint64_t)(uint8_t)elem[5] << 0x10 | (uint64_t)*(uint8_t *)((long)elem + 0xb) << 0x18 |
                    (uint64_t)elem[4] |
                    (uint64_t)((uint)(uint8_t)elem[7] << 0x10 |
                               (uint)*(uint8_t *)((long)elem + 0xf) << 0x18 | (uint)elem[6]) << 0x20) &
                   0xffffffffffffc000ULL;
            {
                uint8_t kind[8] = { 0x11, 0, 0, 0, 0, 0, 0, 0 };
                uint64_t block = 0;
                long owner = 0;
                sk_memset0((uint64_t)(uintptr_t)kind | 1, 0xf);
                sk_obj_t ep = sk_ep_obj_get();
                uint8_t err = (uint8_t)((uint64_t(*)(void *, unsigned long, void *, void **,
                                                     unsigned long, unsigned long))
                            (*(void **)((char *)ep.vtable + 0x30)))(ep.object, 0x1800, kind, &block, 0, 0) & 0xff;
                if (err == 0) {
                    uint64_t idx = (uint64_t)(uint8_t)u8 << 0x10 | (uint64_t)b4 << 0x18 |
                                   (uint64_t)(uint16_t)((uint8_t)u6 | (uint8_t)u3 << 8) |
                                   (uint64_t)((uint)(uint8_t)u7 << 0x10 | (uint)b2 << 0x18 | (uint)u5) << 0x20;
                    long region = rng.base + idx * 0x40;
                    if (rng.end <= idx << 6) {
                        region = 0;
                    }
                    sk_region_map_frames(region, block, owner, size);
                    if (owner == 0) {
                        sk_x_00054354();
                    }
                    ((void (*)(void *, void *))(*(void **)(owner + 8)))((void *)block, kind);
                    {
                        uint64_t add = (uint64_t)(uint8_t)elem[1] << 0x10 |
                                       (uint64_t)*(uint8_t *)((long)elem + 3) << 0x18 | (uint64_t)*elem |
                                       (uint64_t)((uint)(uint8_t)elem[3] << 0x10 |
                                                  (uint)*(uint8_t *)((long)elem + 7) << 0x18 |
                                                  (uint)elem[2]) << 0x20;
                        if (out_off <= out_off + add) {
                            uint64_t *dst = (uint64_t *)*out;
                            *dst = out_off;
                            out[1] = add;
                            out_off = out_off + add;
                            if ((out_off == 0) || (out_off <= out_off + 8)) {
                                out[2] = out_off;
                                return;
                            }
                        }
                    }
                } else if ((uintptr_t)0x64cb3f < (uintptr_t)sk_x_0064cb40 + err &&
                           (uintptr_t)sk_x_0064cb48 + err < (uintptr_t)0x64cb81 &&
                           (uintptr_t)sk_x_0064cb40 + err <= (uintptr_t)sk_x_0064cb48 + err) {
                    sk_panic_brk(0, sk_str_Failed_to_map_memory_for_subgraph);
                }
            }
        }
    }
corrupt:
    SoftwareBreakpoint(0x5519, 0x50c84);
}

/* FUN_00050c88 @ 0x00050c88   (sk_strnlen)
 * Ghidra: char *FUN_00050c88(char *param_1, long param_2)
 * Bounded string length probe: scans up to arg2 bytes for a NUL terminator and
 * returns the original pointer on success, NULL when the probe length equals
 * arg2 (no terminator within the window). Fatal if arg2 is zero or the window
 * overruns.
 * Confidence: high
 * Notes: SoftwareBreakpoint 0x5519 @ 0x50ce8; helper sk_x_00114fe0. */
static uint64_t sk_strnlen(uint64_t arg1, long arg2)
{
    long probe;
    char c;
    char *p;

    probe = sk_x_00114fe0();
    if (probe == arg2) {
        arg1 = 0;
    } else {
        if (arg2 == 0) {
            SoftwareBreakpoint(0x5519, 0x50ce8);
        }
        p = (char *)arg1;
        do {
            if ((uint64_t)arg1 + arg2 < (uint64_t)(p + 1)) {
                SoftwareBreakpoint(0x5519, 0x50ce8);
            }
            c = *p;
            p = p + 1;
        } while (c != '\0');
    }
    return arg1;
}

/* FUN_00050ce8 @ 0x00050ce8   (sk_ipc_msg_write)
 * Ghidra: undefined8 FUN_00050ce8(long *param_1, long param_2, ushort *param_3)
 * Writes an IPC message into the caller's message buffer (arg1 = {base,size})
 * and appends a 12-byte descriptor to the IPC descriptor array in arg3
 * (arg3+0xc0 holds the descriptor count). If the target thread (arg2) is
 * capability-only the buffer is first mapped through a fresh frame region.
 * Returns 1 on success, 0 on allocation failure. Fatal on overflow or on a
 * descriptor write outside the bounded array.
 * Confidence: medium
 * Notes: string s___CAPABILITY_ONLY___ 0x5bb7b6; overflow check 0x117;
 * SoftwareBreakpoint 0x5519 @ 0x510d4; local_88 is a register-aliasing
 * artifact kept as scratch. */
static uint64_t sk_ipc_msg_write(uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    long *msg_base = (long *)arg1;
    uint16_t *dst = (uint16_t *)arg3;
    typedef sk_ep_pair_t sk_obj_t;
    uint16_t *desc;
    uint16_t *slot;
    long buf;
    long msg_scratch = 0;
    uint64_t id, sz, idx, n;
    uint8_t *d, *c;
    uint8_t t_100, t_101, t_102, t_103, t_104, t_105, t_106, t_107;
    uint8_t t_10a, t_10b, t_10e, t_10f, d_183, d_185, d_187;
    uint16_t t_108, t_10c, d_c0, d_c1, d_c2, d_c3;

    if (*(uint8_t *)(arg2 + 0x117) >> 2 != 0) {
        sk_fatal_printf(sk_str_integer_overflow);
    }
    desc = dst + 0xc0;
    d_c2 = dst[0xc2];
    t_104 = *(uint8_t *)(arg2 + 0x104);
    t_108 = *(uint16_t *)(arg2 + 0x108);
    t_10b = *(uint8_t *)(arg2 + 0x10b);
    t_10a = *(uint8_t *)(arg2 + 0x10a);
    t_10c = *(uint16_t *)(arg2 + 0x10c);
    t_10f = *(uint8_t *)(arg2 + 0x10f);
    t_10e = *(uint8_t *)(arg2 + 0x10e);
    id = (uint64_t)t_10a << 0x10 | (uint64_t)t_10b << 0x18 | (uint64_t)t_108 |
         (uint64_t)((uint)t_10e << 0x10 | (uint)t_10f << 0x18 | (uint)t_10c) << 0x20;
    sz = ((uint64_t)*(uint8_t *)(arg2 + 0x112) << 0x10 |
          (uint64_t)*(uint8_t *)(arg2 + 0x113) << 0x18 |
          (uint64_t)*(uint16_t *)(arg2 + 0x110) |
          (uint64_t)((uint)*(uint8_t *)(arg2 + 0x116) << 0x10 |
                     (uint)*(uint8_t *)(arg2 + 0x117) << 0x18 | (uint)*(uint16_t *)(arg2 + 0x114)) << 0x20) * 0x40;
    if (sz < (uint64_t)msg_base[1]) {
        buf = sz + msg_base[0];
    } else {
        buf = 0;
    }
    t_102 = *(uint8_t *)(arg2 + 0x102);
    t_106 = *(uint8_t *)(arg2 + 0x106);
    d_c1 = dst[0xc1];
    d_c3 = dst[0xc3];
    t_101 = *(uint8_t *)(arg2 + 0x101);
    t_100 = *(uint8_t *)(arg2 + 0x100);
    t_103 = *(uint8_t *)(arg2 + 0x103);
    t_105 = *(uint8_t *)(arg2 + 0x105);
    t_107 = *(uint8_t *)(arg2 + 0x107);
    d_c0 = dst[0xc0];
    d_183 = *(uint8_t *)((long)dst + 0x183);
    d_185 = *(uint8_t *)((long)dst + 0x185);
    d_187 = *(uint8_t *)((long)dst + 0x187);
    if (sk_memcmp((uint64_t)arg2, (uint64_t)sk_str___CAPABILITY_ONLY___, 0x100) != 0) {
        uint64_t block = 0;
        long owner = 0;
        uint8_t kind[8] = { 0x11, 0, 0, 0, 0, 0, 0, 0 };
        uint8_t st;
        sk_memset0((uint64_t)(uintptr_t)kind | 1, 0xf);
        sk_obj_t ep = sk_ep_obj_get();
        st = (uint8_t)((uint64_t(*)(void *, unsigned long, void *, void **,
                                    unsigned long, unsigned long))
               (*(void **)((char *)ep.vtable + 0x30)))(ep.object, 0x1a08, kind, &block, 0, 0);
        if (st != 0) {
            return 0;
        }
        sk_region_map_frames(buf, block, owner, id);
        if (owner == 0) {
            sk_x_00054354();
        }
        ((void (*)(void *, void *))(*(void **)(owner + 8)))((void *)block, kind);
        buf = msg_scratch;
    }
    idx = (uint64_t)(uint8_t)d_c2 | (uint64_t)d_185 << 8 |
          (uint64_t)(uint8_t)d_c1 << 0x10 | (uint64_t)d_183 << 0x18 |
          (uint64_t)(uint8_t)d_c0 << 0x20 | (uint64_t)(uint8_t)d_c3 << 0x28 |
          (uint64_t)d_187 << 0x30;
    slot = dst + idx * 0xc;
    if (((dst <= slot) && (slot + 0xc <= desc)) && (slot <= slot + 0xc)) {
        d = (uint8_t *)slot;
        d[0x15] = (uint8_t)((uint64_t)buf >> 0x28);
        d[0x10] = (uint8_t)buf;
        d[0x13] = (uint8_t)((uint64_t)buf >> 0x18);
        d[0x12] = (uint8_t)((uint64_t)buf >> 0x10);
        d[0x11] = (uint8_t)((uint64_t)buf >> 8);
        d[0x14] = (uint8_t)((uint64_t)buf >> 0x20);
        d[0x17] = (uint8_t)((uint64_t)buf >> 0x38);
        d[0x16] = (uint8_t)((uint64_t)buf >> 0x30);
        d[0xd] = (uint8_t)(t_10c >> 8);
        d[0x8] = (uint8_t)t_108;
        d[0xb] = t_10b;
        d[0xa] = t_10a;
        d[0x9] = (uint8_t)(t_108 >> 8);
        d[0xc] = (uint8_t)t_10c;
        d[0xf] = t_10f;
        d[0xe] = t_10e;
        d[0x0] = t_100;
        d[0x5] = t_105;
        d[0x3] = t_103;
        d[0x2] = t_102;
        d[0x1] = t_101;
        d[0x4] = t_104;
        d[0x7] = t_107;
        d[0x6] = t_106;
        n = ((uint64_t)(uint8_t)dst[0xc1] << 0x10 | (uint64_t)*(uint8_t *)((long)dst + 0x183) << 0x18 |
             (uint64_t)*desc |
             (uint64_t)((uint)(uint8_t)dst[0xc3] << 0x10 |
                        (uint)*(uint8_t *)((long)dst + 0x187) << 0x18 | (uint)dst[0xc2]) << 0x20) + 1;
        c = (uint8_t *)desc;
        c[0x0] = (uint8_t)n;
        c[0x6] = (uint8_t)(n >> 0x30);
        c[0xc7] = (uint8_t)(n >> 0x38);
        c[0x4] = (uint8_t)(n >> 0x20);
        c[0xc5] = (uint8_t)(n >> 0x28);
        c[0x2] = (uint8_t)(n >> 0x10);
        c[0xc3] = (uint8_t)(n >> 0x18);
        c[0xc1] = (uint8_t)(n >> 8);
        return 1;
    }
    SoftwareBreakpoint(0x5519, 0x510d4);
    return 1;
}

/* FUN_000510e4 @ 0x000510e4   (sk_region_map_frames)
 * Ghidra: void FUN_000510e4(long param_1, undefined8 param_2, long param_3, ulong param_4)
 * Maps len bytes worth of 0x4000-byte frames, one at a time, into the target
 * region via the frame-mapping supervisor call, invoking the cb callback
 * (param_3 + 0x28) with (arg, frame_index<<14, base). Panics on a failed
 * frame create/map. Stack canary checked on exit.
 * Confidence: medium
 * Notes: reads tpidrro_el0 for the per-CPU frame descriptor; CallSupervisor
 * 0/4; error-string table 0x64cb40/48/80; strings 0x5bb7ca / 0x5bb805;
 * SoftwareBreakpoint 0x5519 @ 0x51350; helper sk_x_00034f70 / sk_x_004b23d8. */
static void sk_region_map_frames(uint64_t region, uint64_t arg, uint64_t cb, uint64_t len)
{
    uint8_t *frame;
    uint8_t scratch[32];
    uint64_t idx = 0;
    long base;
    long canary = -0x2c8502b44bfffed6;

    base = sk_x_00034f70();
    if (0x3fff < len) {
        do {
            asm volatile("mrs %0, tpidrro_el0" : "=r"(frame));
            frame[4] = 0;
            frame[1] = 0;
            frame[5] = 0;
            frame[2] = 0;
            frame[3] = 0;
            *frame = 0x11;
            frame[6] = 0;
            frame[7] = 0;
            frame[0xd] = (uint8_t)(idx >> 0x1a);
            frame[8] = 0;
            frame[9] = (uint8_t)(idx << 6);
            frame[0xb] = (uint8_t)(idx >> 10);
            frame[10] = (uint8_t)(idx >> 2);
            frame[0xc] = (uint8_t)(idx >> 0x12);
            {
                uint32_t hi = (uint32_t)(idx >> 0x20);
                frame[0xf] = (uint8_t)(hi >> 10);
                frame[0xe] = (uint8_t)(hi >> 2);
            }
            frame[0x15] = (uint8_t)((uint64_t)base >> 0x28);
            frame[0x10] = (uint8_t)base;
            frame[0x13] = (uint8_t)((uint64_t)base >> 0x18);
            frame[0x12] = (uint8_t)((uint64_t)base >> 0x10);
            frame[0x11] = (uint8_t)((uint64_t)base >> 8);
            frame[0x14] = (uint8_t)((uint64_t)base >> 0x20);
            frame[0x17] = (uint8_t)((uint64_t)base >> 0x38);
            frame[0x16] = (uint8_t)((uint64_t)base >> 0x30);
            CallSupervisor(0);
            frame[7] = 0;
            frame[6] = 0;
            frame[5] = 0;
            frame[4] = 0;
            frame[3] = 0;
            frame[2] = 0;
            *frame = 0x11;
            frame[1] = 0;
            if (region != 0) {
                sk_err_str_fill((uint64_t)(uintptr_t)scratch, (uint8_t)region);
                sk_panic_brk(0, sk_str_Failed_to_create_frame);
            }
            {
                uint8_t st = (uint8_t)((uint64_t(*)(uint64_t, uint64_t, long))
                            (*(void **)(cb + 0x28)))(arg, idx << 0xe, base) & 0xff;
                if (st != 0) {
                    if ((uintptr_t)sk_x_0064cb40 + st < (uintptr_t)sk_x_0064cb40 ||
                        (uintptr_t)sk_x_0064cb80 < (uintptr_t)sk_x_0064cb48 + st ||
                        (uintptr_t)sk_x_0064cb48 + st < (uintptr_t)sk_x_0064cb40 + st) {
                        SoftwareBreakpoint(0x5519, 0x51350);
                    }
                    sk_panic_brk(0, sk_str_Failed_to_map_the_frame_idx);
                }
            }
            do {
                CallSupervisor(4);
            } while (base == 1);
            idx = idx + 1;
        } while (idx != len >> 0xe);
    }
    if (canary == -0x2c8502b44bfffed6) {
        sk_x_004b23d8(base);
        return;
    }
    sk_stack_chk_fail();
}

/* FUN_00051350 @ 0x00051350   (sk_err_str_fill)
 * Ghidra: void FUN_00051350(undefined8 param_1, byte param_2)
 * Fills the 0x20-byte buffer at out with the 0x20-byte error-code string for
 * code (0..9), or with the generic unknown-code blob for out-of-range codes.
 * No return value.
 * Confidence: high
 * Notes: L4_ErrorCode* strings 0x4bcb80..0x4bcca0; unknown blob DAT_004bccc0;
 * helper sk_x_0000178c. */
static void sk_err_str_fill(uint64_t out, uint8_t code)
{
    char *msg;

    if (9 < code) {
        sk_memcpy(out, (uint64_t)sk_x_004bccc0, 0x20);
        sk_x_0000178c(out, 0x20);
        return;
    }
    switch (code) {
    default:
        msg = sk_str_L4ErrorCodeSuccess;
        break;
    case 1:
        msg = sk_str_L4ErrorCodePreempted;
        break;
    case 2:
        msg = sk_str_L4ErrorCodeCanceled;
        break;
    case 3:
        msg = sk_str_L4ErrorCodeTruncated;
        break;
    case 4:
        msg = sk_str_L4ErrorCodeCapInvalid;
        break;
    case 5:
        msg = sk_str_L4ErrorCodeSlotInvalid;
        break;
    case 6:
        msg = sk_str_L4ErrorCodeMethodInvalid;
        break;
    case 7:
        msg = sk_str_L4ErrorCodeArgumentInvalid;
        break;
    case 8:
        msg = sk_str_L4ErrorCodeOperationInvalid;
        break;
    case 9:
        msg = sk_str_L4ErrorCodePermissionInvalid;
        break;
    }
    sk_memcpy(out, (uint64_t)msg, 0x20);
}

/* FUN_00051488 @ 0x00051488   (sk_tb_ph_encode_elem)
 * Ghidra: void FUN_00051488(long *param_1, long param_2, undefined1 *param_3)
 * Encodes one page-hierarchy element into the 0x100-byte output at dst: the
 * element's page range (param_2+0x100) resolves to a buffer offset pair in
 * region (param_1={base,size}) stored at dst+0 and dst+0xe8, and the 16-byte
 * capability bitfield at param_2+0x110 is copied to dst+0xf0.
 * Confidence: high
 * Notes: overflow checks at 0x107 / 0x10f. */
static void sk_tb_ph_encode_elem(uint64_t region, uint64_t ph, uint64_t dst)
{
    long *reg = (long *)region;
    uint8_t *out = (uint8_t *)dst;
    uint64_t off, cnt;
    long p1, p2;
    uint16_t u9, u10, u11, u12;
    uint8_t u1, u2, u3, u4, u5, u6, u7, u8;

    if (*(uint8_t *)(ph + 0x107) >> 2 != 0) {
        sk_fatal_printf(sk_str_integer_overflow);
    }
    off = ((uint64_t)*(uint8_t *)(ph + 0x102) << 0x10 |
           (uint64_t)*(uint8_t *)(ph + 0x103) << 0x18 |
           (uint64_t)*(uint16_t *)(ph + 0x100) |
           (uint64_t)((uint)*(uint8_t *)(ph + 0x106) << 0x10 |
                      (uint)*(uint8_t *)(ph + 0x107) << 0x18 | (uint)*(uint16_t *)(ph + 0x104)) << 0x20) * 0x40;
    if (off < (uint64_t)reg[1]) {
        p1 = off + reg[0];
    } else {
        p1 = 0;
    }
    cnt = (uint64_t)*(uint8_t *)(ph + 0x10a) << 0x10 |
          (uint64_t)*(uint8_t *)(ph + 0x10b) << 0x18 |
          (uint64_t)*(uint16_t *)(ph + 0x108) |
          (uint64_t)((uint)*(uint8_t *)(ph + 0x10e) << 0x10 |
                     (uint)*(uint8_t *)(ph + 0x10f) << 0x18 | (uint)*(uint16_t *)(ph + 0x10c)) << 0x20;
    if (cnt != 0) {
        if (*(uint8_t *)(ph + 0x10f) >> 2 != 0) {
            sk_fatal_printf(sk_str_integer_overflow);
        }
        cnt = cnt * 0x40;
        if (cnt < (uint64_t)reg[1]) {
            p2 = cnt + reg[0];
            goto have_p2;
        }
    }
    p2 = 0;
have_p2:
    out[0] = (uint8_t)p1;
    out[5] = (uint8_t)((uint64_t)p1 >> 0x28);
    out[3] = (uint8_t)((uint64_t)p1 >> 0x18);
    out[2] = (uint8_t)((uint64_t)p1 >> 0x10);
    out[1] = (uint8_t)((uint64_t)p1 >> 8);
    out[4] = (uint8_t)((uint64_t)p1 >> 0x20);
    out[7] = (uint8_t)((uint64_t)p1 >> 0x38);
    out[6] = (uint8_t)((uint64_t)p1 >> 0x30);
    out[0xed] = (uint8_t)((uint64_t)p2 >> 0x28);
    out[0xe8] = (uint8_t)p2;
    out[0xeb] = (uint8_t)((uint64_t)p2 >> 0x18);
    out[0xea] = (uint8_t)((uint64_t)p2 >> 0x10);
    out[0xe9] = (uint8_t)((uint64_t)p2 >> 8);
    out[0xec] = (uint8_t)((uint64_t)p2 >> 0x20);
    out[0xef] = (uint8_t)((uint64_t)p2 >> 0x38);
    out[0xee] = (uint8_t)((uint64_t)p2 >> 0x30);
    u9 = *(uint16_t *)(ph + 0x110);
    u1 = *(uint8_t *)(ph + 0x113);
    u2 = *(uint8_t *)(ph + 0x112);
    u10 = *(uint16_t *)(ph + 0x114);
    u3 = *(uint8_t *)(ph + 0x117);
    u4 = *(uint8_t *)(ph + 0x116);
    u11 = *(uint16_t *)(ph + 0x118);
    u5 = *(uint8_t *)(ph + 0x11b);
    u6 = *(uint8_t *)(ph + 0x11a);
    u12 = *(uint16_t *)(ph + 0x11c);
    u7 = *(uint8_t *)(ph + 0x11f);
    u8 = *(uint8_t *)(ph + 0x11e);
    out[0xf0] = (uint8_t)u9;
    out[0xfd] = (uint8_t)(u12 >> 8);
    out[0xf9] = (uint8_t)(u11 >> 8);
    out[0xf5] = (uint8_t)(u10 >> 8);
    out[0xf3] = u1;
    out[0xf2] = u2;
    out[0xf1] = (uint8_t)(u9 >> 8);
    out[0xf8] = (uint8_t)u11;
    out[0xfb] = u5;
    out[0xf4] = (uint8_t)u10;
    out[0xfa] = u6;
    out[0xf7] = u3;
    out[0xf6] = u4;
    out[0xfc] = (uint8_t)u12;
    out[0xff] = u7;
    out[0xfe] = u8;
}

/* FUN_00051740 @ 0x00051740   (sk_reloc_bind)
 * Ghidra: undefined8 FUN_00051740(long param_1, ulong param_2, long param_3)
 * Walks the relocation bitset chains of the region starting at va and rewrites
 * each 0x4000-aligned relocation chain in the target buffer, translating
 * in-region offsets into resolved pointers. Returns 1 when any relocation was
 * applied, 0 otherwise. Fatal on an unaligned va, an out-of-range chain slot,
 * or an unknown relocation kind.
 * Confidence: high
 * Notes: bitset at region+0x16, stride region+4, chain count region+0x14,
 * kind region+6 (7 or 0xc); SoftwareBreakpoint 0x5519 @ 0x5191c. */
static uint64_t sk_reloc_bind(uint64_t region, uint64_t va, uint64_t target)
{
    uint64_t result = 0;
    uint64_t end;
    uint64_t stride, r9;
    uint16_t count;
    short kind;
    uint16_t *slot;
    long l10;
    long reloc_va;
    ulong *next;

    if (region != 0) {
        if ((va & 0x3fff) != 0) {
            SoftwareBreakpoint(1, 0x51920);
        }
        if (va < 0xffffffffffffc000ULL) {
            end = va + 0x4000;
            l10 = 0;
            reloc_va = va + (long)(stride = (uint64_t)*(uint16_t *)(region + 4));
            count = *(uint16_t *)(region + 0x14);
            do {
                r9 = 0;
                if (stride != 0) {
                    r9 = (va - (uint64_t)*(long *)(region + 8)) / stride;
                }
                if (count <= r9) {
                    return result;
                }
                slot = (uint16_t *)(region + 0x16 + r9 * 2);
                if (slot + 1 < slot ||
                    (uint16_t *)(region + 0x16 + (uint64_t)count * 2) < slot + 1) {
                    SoftwareBreakpoint(0x5519, 0x5191c);
                }
                r9 = (uint64_t)*slot;
                if (r9 != 0xffff) {
                    kind = *(short *)(region + 6);
                    if ((kind != 0xc) && (kind != 7)) {
                        SoftwareBreakpoint(0x5519, 0x5191c);
                    }
                    {
                        ulong *p = (ulong *)(l10 + target);
                        ulong *q = (ulong *)((long)p + r9);
                        if (q != 0) {
                            int shift = (kind != 7) ? 3 : 2;
                            do {
                                uint64_t val = *q;
                                uint64_t f = (val >> 0x33) & 0x7ff;
                                long delta = (long)(f << shift);
                                if (f == 0) {
                                    next = 0;
                                    if ((long)val >= 0) {
                                        val = val & 0x7ffffffffffULL | (val >> 0x2b) << 0x38;
                                    } else {
                                        val = val & 0xffffffff;
                                    }
                                } else {
                                    next = (ulong *)((long)p + (r9 & 0xffff) + delta);
                                    if (next != 0 && (next < p ||
                                        (ulong *)((long)p + stride) < next + 1 || next + 1 < next)) {
                                        SoftwareBreakpoint(0x5519, 0x5191c);
                                    }
                                    if ((long)val >= 0) {
                                        val = val & 0x7ffffffffffULL | (val >> 0x2b) << 0x38;
                                    } else {
                                        val = val & 0xffffffff;
                                    }
                                }
                                r9 = (uint64_t)(uint)((int)r9 + (int)delta);
                                *q = val;
                                q = next;
                            } while (next != 0);
                        }
                    }
                    result = 1;
                }
                va = (uint64_t)(l10 + reloc_va);
                l10 = l10 + (long)stride;
                if (end <= va) {
                    return result;
                }
            } while (1);
        }
    }
    return 0;
}

/* FUN_00051920 @ 0x00051920   (sk_region_bitset_test)
 * Ghidra: byte FUN_00051920(long param_1, ulong param_2)
 * ORs together the low bits of every relocation bitset slot covered by the
 * 0x4000-aligned window starting at va, returning nonzero if any slot is
 * present. Fatal on an unaligned va or an out-of-range slot.
 * Confidence: high
 * Notes: SoftwareBreakpoint 0x5519 @ 0x519c4 / 0x519c8. */
static uint8_t sk_region_bitset_test(uint64_t region, uint64_t va)
{
    uint64_t end, stride, r3;
    uint8_t result = 0;
    short *slot;

    if (region != 0) {
        if ((va & 0x3fff) != 0) {
            SoftwareBreakpoint(1, 0x519c8);
        }
        if (va < 0xffffffffffffc000ULL) {
            end = va + 0x4000;
            stride = (uint64_t)*(uint16_t *)(region + 4);
            do {
                r3 = 0;
                if (stride != 0) {
                    r3 = (va - (uint64_t)*(long *)(region + 8)) / stride;
                }
                if (*(uint16_t *)(region + 0x14) <= r3) {
                    return result;
                }
                slot = (short *)(region + 0x16 + r3 * 2);
                if (slot + 1 < slot ||
                    (short *)(region + 0x16 + (uint64_t)*(uint16_t *)(region + 0x14) * 2) < slot + 1) {
                    SoftwareBreakpoint(0x5519, 0x519c4);
                }
                result = (*slot != -1) | result;
                va = va + stride;
            } while (va < end);
            return result;
        }
    }
    return 0;
}

/* FUN_000519c8 @ 0x000519c8   (sk_region_find)
 * Ghidra: ulong FUN_000519c8(long param_1, ulong param_2)
 * Scans the shared region table for an entry whose owner equals region and
 * whose covered range fits size, returning its address. Fatal on a corrupt
 * entry or an overfull slot.
 * Confidence: medium
 * Notes: uses the file-local region table set by sk_region_init; the bounds
 * check reproduces the decompiler's overlapping-symbol (_DAT_006af8xx)
 * range/overflow arithmetic. */
static uint64_t sk_region_find(uint64_t region, uint64_t size)
{
    uint32_t *cur, *endp;
    uintptr_t slot, slot_end, window_end;
    uint64_t remaining;
    uint32_t idx;
    uint64_t n;
    int bad;

    if ((sk_region_table_ready != 0) && (n = (uint64_t)*sk_region_count_ptr,
                                         *sk_region_count_ptr != 0)) {
        cur = sk_region_count_ptr + 1;
        endp = cur + n;
        window_end = sk_region_lo + sk_region_hi;
        do {
            if (endp < cur + 1 || cur + 1 < cur) {
                SoftwareBreakpoint(0x5519, 0x51ab8);
            }
            idx = *cur;
            if (idx != 0) {
                slot = sk_region_lo + sk_region_table[4] + (uint64_t)idx;
                if (slot != 0) {
                    slot_end = slot + 0x18;
                    bad = (slot_end < slot || slot < sk_region_lo) || window_end < slot_end;
                    remaining = (uint64_t)((long)((sk_region_hi - (idx + sk_region_table[4])) - 0x16) >> 1);
                    if ((bad || window_end <= slot + 0x16) &&
                        (bad || slot + 0x16 != window_end) ||
                        remaining < (uint64_t)*(uint16_t *)(slot + 0x14)) {
                        SoftwareBreakpoint(0x5519, 0x51ab8);
                    }
                }
                if (*(long *)(slot + 8) == region) {
                    if ((uint64_t)*(uint16_t *)(slot + 0x14) * (uint64_t)*(uint16_t *)(slot + 4) <= size) {
                        return slot;
                    }
                    SoftwareBreakpoint(1, 0x51ab4);
                }
            }
            cur = cur + 1;
            n = n - 1;
        } while (n != 0);
    }
    return 0;
}

/* FUN_00051ab8 @ 0x00051ab8   (sk_region_init)
 * Ghidra: void FUN_00051ab8(uint *param_1, ulong param_2)
 * Initializes the shared region table from the descriptor array at base and
 * registers each nonzero region entry: under live mode it links entries into
 * the __DATA / __DATA_CONST head lists, otherwise it runs relocation binding
 * over every 0x4000 chain. Fatal on a too-small area or a corrupt entry.
 * Confidence: medium
 * Notes: DAT_006ad6e0 is sk_phys_base; strings 0x5bb23b / 0x5bb242; sets
 * globals DAT_006af888..006af8b8; SoftwareBreakpoint 0x5519 @ 0x51b28. */
static void sk_region_init(uint32_t *base, uint64_t size)
{
    long phys_base = sk_phys_base;
    uint32_t *limit, *count_ptr, *ent, *p, *p6;
    uint64_t count = 0, i, k;
    uint32_t off;
    uintptr_t slot;
    long addr;
    long data_seg, data_const;
    ulong *head;
    int bad;

    if (size < 0x1c) {
        SoftwareBreakpoint(1, 0x51d3c);
    }
    limit = (uint32_t *)((long)base + size);
    count_ptr = (uint32_t *)((long)base + (uint64_t)base[1]);
    if (count_ptr == 0) {
        count = 0;
    } else if ((count_ptr + 1 < count_ptr || count_ptr < base) || limit < count_ptr + 1 ||
               (count = (uint64_t)*count_ptr,
                (uint64_t)((long)((size - base[1]) + -4) >> 2) < count)) {
        SoftwareBreakpoint(0x5519, 0x51b28);
    }
    sk_region_table_ready = 1;
    sk_region_table = base;
    sk_region_count_ptr = count_ptr;
    sk_region_lo = (uintptr_t)base;
    sk_region_hi = size;
    data_seg = sk_macho_seg_named(0, (uint64_t)sk_str___DATA);
    data_const = sk_macho_seg_named(0, (uint64_t)sk_str___DATA_CONST);
    if ((int)count != 0) {
        i = 0;
        ent = count_ptr + 1;
        do {
            p = ent + i;
            if ((p < ent || p + 1 < p) || ent + *count_ptr < p + 1) {
                SoftwareBreakpoint(0x5519, 0x51b28);
            }
            off = *p;
            if (off != 0) {
                p = (uint32_t *)((long)base + (uint64_t)off + (uint64_t)base[1]);
                if (p != 0) {
                    p6 = p + 6;
                    bad = (p6 < p || p < base) || limit < p6;
                    slot = (uintptr_t)((long)p + 0x16);
                    if ((bad || limit <= (uint32_t *)slot) &&
                        (bad || (uint32_t *)slot != limit) ||
                        (uint64_t)((long)((size - 0x16) - ((uint64_t)off + (uint64_t)base[1])) >> 1) <
                        (uint64_t)(uint16_t)p[5]) {
                        SoftwareBreakpoint(0x5519, 0x51b28);
                    }
                }
                addr = *(long *)(p + 2);
                if (sk_tb_live_flag == 1) {
                    if (data_seg == 0 ||
                        *(uint64_t *)(data_seg + 0x20) <=
                        (uint64_t)(addr - (phys_base + *(long *)(data_seg + 0x18)))) {
                        if (data_const == 0 ||
                            *(uint64_t *)(data_const + 0x20) <=
                            (uint64_t)(addr - (phys_base + *(long *)(data_const + 0x18)))) {
                            goto reloc_chain;
                        }
                        if (p != 0 && (p + 6 < p ||
                            (uint32_t *)((long)p + (uint64_t)(uint16_t)p[5] * 2 + 0x16) < p + 6)) {
                            SoftwareBreakpoint(0x5519, 0x51b28);
                        }
                        head = &sk_region_list_b;
                    } else {
                        if (p != 0 && (p + 6 < p ||
                            (uint32_t *)((long)p + (uint64_t)(uint16_t)p[5] * 2 + 0x16) < p + 6)) {
                            SoftwareBreakpoint(0x5519, 0x51b28);
                        }
                        head = &sk_region_list_a;
                    }
                    *head = (ulong)(uintptr_t)p;
                } else {
reloc_chain:
                    if ((short)p[5] != 0) {
                        k = 0;
                        do {
                            sk_reloc_bind((long)(uintptr_t)p, (uint64_t)addr, (long)addr);
                            k = k + 1;
                            addr = addr + 0x4000;
                        } while (k < (uint16_t)p[5]);
                    }
                }
            }
            i = i + 1;
        } while (i != count);
    }
}

/* FUN_00051d3c @ 0x00051d3c   (sk_macho_pagezero_min)
 * Ghidra: ulong FUN_00051d3c(long param_1)
 * Returns the smallest vmaddr among the __PAGEZERO segments of the Mach-O
 * header, or 0xffffffffffffffff when none match. Reproduces the decompile's
 * name-compare and min-selection exactly.
 * Confidence: low
 * Notes: string 0x5bb8fa; segment type 0x19. */
static uint64_t sk_macho_pagezero_min(uint64_t mh)
{
    uint32_t ncmds;
    uint64_t best = 0xffffffffffffffffULL, cur;
    int *cmd;

    ncmds = *(uint32_t *)(mh + 0x10);
    if (ncmds == 0) {
        return best;
    }
    cmd = (int *)(mh + 0x20);
    cur = 0xffffffffffffffffULL;
    do {
        uint64_t v = cur;
        if (*cmd == 0x19 &&
            sk_memcmp((uint64_t)(cmd + 2), (uint64_t)sk_str___PAGEZERO, 0x10) != 0 &&
            (v = *(uint64_t *)(cmd + 6), cur <= *(uint64_t *)(cmd + 6))) {
            v = cur;
        }
        cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
        ncmds = ncmds - 1;
        cur = v;
    } while (ncmds != 0);
    return cur;
}

/* FUN_00051dc0 @ 0x00051dc0   (sk_macho_pagezero_max)
 * Ghidra: ulong FUN_00051dc0(long param_1)
 * Returns the largest (vmaddr + vmsize) end address among the __PAGEZERO
 * segments of the Mach-O header, or 0 when none match.
 * Confidence: high
 * Notes: segment type 0x19. */
static uint64_t sk_macho_pagezero_max(uint64_t mh)
{
    uint32_t ncmds;
    uint64_t best = 0, v;
    int *cmd;

    ncmds = *(uint32_t *)(mh + 0x10);
    if (ncmds == 0) {
        return 0;
    }
    cmd = (int *)(mh + 0x20);
    do {
        v = best;
        if (*cmd == 0x19 &&
            (v = (uint64_t)(*(long *)(cmd + 8) + *(long *)(cmd + 6)),
             (uint64_t)(*(long *)(cmd + 8) + *(long *)(cmd + 6)) <= best)) {
            v = best;
        }
        cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
        ncmds = ncmds - 1;
        best = v;
    } while (ncmds != 0);
    return best;
}

/* FUN_00051e0c @ 0x00051e0c   (sk_macho_seg_find)
 * Ghidra: int *FUN_00051e0c(long param_1, int *param_2)
 * Returns the first 64-bit segment command (LC_SEGMENT_64, type 0x19) of the
 * Mach-O header, or NULL when there is none. The decompile's second argument
 * is a cursor for iterator-style calls; the contract signature drops it, so it
 * is modeled here as a local (always NULL on entry), yielding "find first".
 * Confidence: medium
 * Notes: the cursor parameter was dropped from the contract signature; the
 * caller sk_macho_seg_named inlines the iteration (see its Notes). */
static uint64_t sk_macho_seg_find(uint64_t mh)
{
    uint32_t ncmds;
    int *cmd;
    int *prev;

    ncmds = *(uint32_t *)(mh + 0x10);
    prev = 0;
    if (ncmds != 0) {
        cmd = (int *)(mh + 0x20);
        do {
            int *p = prev;
            if (*cmd == 0x19) {
                if (prev == 0) {
                    if (cmd + 0x12 < cmd) {
                        SoftwareBreakpoint(0x5519, 0x51e5c);
                    }
                    return (uint64_t)cmd;
                }
                p = 0;
                if (prev != cmd) {
                    p = prev;
                }
            }
            cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
            ncmds = ncmds - 1;
            prev = p;
        } while (ncmds != 0);
    }
    return 0;
}

/* FUN_00051e5c @ 0x00051e5c   (sk_macho_seg_named)
 * Ghidra: ulong FUN_00051e5c(undefined8 param_1, undefined8 param_2)
 * Scans the Mach-O header's segment commands and returns the address of the
 * first 64-bit segment (type 0x19) whose 16-byte name matches name, or 0 if
 * none matches. Fatal on an overrun while walking the list.
 * Confidence: medium
 * Notes: the decompile drives the walk with sk_macho_seg_find(mh, cursor);
 * because the contract signature of sk_macho_seg_find drops its cursor, the
 * segment walk is inlined here so the by-name lookup still terminates. */
static uint64_t sk_macho_seg_named(uint64_t mh, uint64_t name)
{
    uint32_t ncmds;
    int *cmd;

    ncmds = *(uint32_t *)(mh + 0x10);
    cmd = (int *)(mh + 0x20);
    while (ncmds != 0) {
        if (*cmd == 0x19 && sk_memcmp((uint64_t)name, (uint64_t)(cmd + 2), 0x10) == 0) {
            return (uint64_t)(uintptr_t)cmd;
        }
        cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
        ncmds = ncmds - 1;
    }
    return 0;
}

/* FUN_00051ee4 @ 0x00051ee4   (sk_macho_seg_named2)
 * Ghidra: ulong FUN_00051ee4(long param_1, undefined8 param_2)
 * Alternative by-name segment lookup that walks 0x50-byte entries starting at
 * mh+0x48 (count at mh+0x40) and returns the entry whose 16-byte name matches,
 * or 0 if none. Fatal on an out-of-range entry walk.
 * Confidence: high
 * Notes: SoftwareBreakpoint 0x5519 @ 0x51fa0. */
static uint64_t sk_macho_seg_named2(uint64_t mh, uint64_t name)
{
    uint64_t entry = 0, bound = 0;
    uintptr_t first = (uintptr_t)(mh + 0x48);

    do {
        if (entry == 0) {
            if (*(int *)(mh + 0x40) == 0) {
                return 0;
            }
            entry = first;
            if ((uintptr_t)(mh + 0x98U) < first) {
                goto fatal;
            }
        } else {
            if (bound < entry + 0x50 || entry + 0x50 < entry) {
                goto fatal;
            }
            if (*(uint32_t *)(mh + 0x40) == 0) {
                return 0;
            }
            if (entry < first) {
                return 0;
            }
            if ((uintptr_t)(mh - 8 + (uint64_t)*(uint32_t *)(mh + 0x40) * 0x50) <= entry) {
                return 0;
            }
            entry = entry + 0x50;
        }
        if (entry == 0) {
            return 0;
        }
        bound = entry + 0x50;
    } while (sk_memcmp((uint64_t)name, entry, 0x10) != 0);
    if (entry <= bound) {
        return entry;
    }
fatal:
    SoftwareBreakpoint(0x5519, 0x51fa0);
    return 0;
}

/* FUN_00051fbc @ 0x00051fbc   (sk_macho_first_pageseg)
 * Ghidra: int *FUN_00051fbc(long param_1)
 * Returns the segname field (cmd + 8) of the first command whose type is 0x1b
 * in the Mach-O header, or NULL when there is none.
 * Confidence: high
 * Notes: command type 0x1b. */
static uint64_t sk_macho_first_pageseg(uint64_t mh)
{
    uint32_t ncmds;
    int *cmd;

    ncmds = *(uint32_t *)(mh + 0x10);
    if (ncmds != 0) {
        cmd = (int *)(mh + 0x20);
        do {
            if (*cmd == 0x1b) {
                return (uint64_t)(cmd + 2);
            }
            cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
            ncmds = ncmds - 1;
        } while (ncmds != 0);
    }
    return 0;
}

/* FUN_00051ff4 @ 0x00051ff4   (sk_macho_linkedit)
 * Ghidra: void FUN_00051ff4(long param_1, ulong *param_2, ulong *param_3, long *param_4)
 * Locates the LC_SYMTAB command and reports the linkedit base (param_4),
 * symbol count (*count) and symbol-table offset (*off) relative to the
 * __LINKEDIT segment. Falls back to zeroed outputs when no symbol table is
 * present. Fatal on an overflowed symbol range.
 * Confidence: medium
 * Notes: strings 0x5bb905 / 0x5bb90c; SoftwareBreakpoint 0x5519 @ 0x520f0. */
static void sk_macho_linkedit(uint64_t mh, uint64_t *count, uint64_t *off, uint64_t *base)
{
    long text_seg, linkedit_seg, result;
    uint32_t ncmds, sizefield;
    uint64_t nsyms, start, end;
    long text_base, link_base;
    int *cmd;

    text_seg = sk_macho_seg_named(mh, (uint64_t)sk_str___TEXT);
    ncmds = *(uint32_t *)(mh + 0x10);
    result = *(long *)(text_seg + 0x18);
    if (ncmds != 0) {
        text_base = *(long *)(text_seg + 0x18);
        cmd = (int *)(mh + 0x20);
        do {
            if (*cmd == 2) {
                linkedit_seg = sk_macho_seg_named(mh, (uint64_t)sk_str___LINKEDIT);
                if ((linkedit_seg == 0) || (nsyms = (uint64_t)(uint32_t)cmd[3], cmd[3] == 0)) {
                    goto fail;
                }
                link_base = *(long *)(linkedit_seg + 0x28);
                result = *(long *)(linkedit_seg + 0x18) + (mh - text_base);
                start = (uint64_t)(result - link_base) + (uint64_t)(uint32_t)cmd[2];
                end = start + nsyms * 0x10;
                if ((end < start) || ((uint64_t)((long)(end - start) >> 4) < nsyms)) {
                    SoftwareBreakpoint(0x5519, 0x520f0);
                }
                sizefield = (uint32_t)cmd[4];
                *count = nsyms;
                *off = start;
                result = ((uint64_t)sizefield - link_base) + result;
                goto done;
            }
            cmd = (int *)((long)cmd + (uint64_t)(uint32_t)cmd[1]);
            ncmds = ncmds - 1;
        } while (ncmds != 0);
    }
    sk_macho_seg_named(mh, (uint64_t)sk_str___LINKEDIT);
fail:
    result = 0;
    *count = 0;
    *off = 0;
done:
    *base = result;
}

/* FUN_000520f0 @ 0x000520f0   (sk_macho_bind_search)
 * Ghidra: long FUN_000520f0(ulong param_1, long *param_2, long param_3, long param_4, long param_5)
 * Searches n bind entries (each 16 bytes) for the one whose value is the
 * greatest address <= sel, and reports its value through out; returns the
 * entry's name/symbol offset plus the slide. Returns 0 and reports 0 when no
 * entry qualifies.
 * Confidence: high
 * Notes: entry flag byte (offset -4) must satisfy (b & 0xee) == 0xe. */
static uint64_t sk_macho_bind_search(uint64_t sel, uint64_t *out, long n, long base, long slide)
{
    long best = 0, best_va = 0;
    long *ent;
    long va;

    if (n == 0) {
        best = 0;
        best_va = 0;
    } else {
        best = 0;
        best_va = 0;
        ent = (long *)(base + 8);
        do {
            if (((*(uint8_t *)((long)ent + -4) & 0xee) == 0xe) && (va = *ent, va - 1U < sel) &&
                (sel - (uint64_t)va < sel - (uint64_t)best_va)) {
                best = (uint64_t)*(uint32_t *)(ent + -1) + slide;
                best_va = va;
            }
            ent = ent + 2;
            n = n - 1;
        } while (n != 0);
    }
    *out = best_va;
    return best;
}

/* FUN_00052248 @ 0x00052248   (sk_rebase_dump)
 * Ghidra: void FUN_00052248(void)
 * Dumps the rebase chains: when the tb debug flag is set it walks the region
 * table via sk_region_find, otherwise it emits the "rebasechains_dumped"
 * notification. No return value.
 * Confidence: medium
 * Notes: DAT_006ad6ea; string 0x5bb917; helper sk_x_000656e4. */
static void sk_rebase_dump(void)
{
    uint64_t arg = 0;

    if (sk_tb_debug_flag == 1) {
        (void)sk_region_find(0, 0);
        return;
    }
    sk_x_000656e4(sk_str_rebasechains_dumped, &arg);
}

/* FUN_0005228c @ 0x0005228c   (sk_region_bitset2)
 * Ghidra: ulong FUN_0005228c(long param_1, ulong param_2)
 * Region bitset probe used for a single va: when the tb debug flag is set it
 * defers to sk_region_bitset_test; otherwise it computes the slot for va
 * against the region's packed base and returns whether that slot is present.
 * Fatal on an out-of-range slot or a malformed region window.
 * Confidence: medium
 * Notes: DAT_006ad6ea + sk_phys_base; SoftwareBreakpoint 0x5519 @ 0x5236c. */
static uint64_t sk_region_bitset2(long region, uint64_t va)
{
    short *start, *end, *slot;
    uint64_t base, present;

    if (sk_tb_debug_flag == 1) {
        return sk_region_bitset_test(region, va);
    }
    start = (short *)(region + 0x18);
    end = (short *)(region + ((uint64_t)*(uint8_t *)(region + 0x16) << 2 |
                              (uint64_t)*(uint8_t *)(region + 0x17) << 10) +
                    (uint64_t)*(uint16_t *)(region + 0x14) * 2 + 0x18);
    if (start <= end) {
        base = ((uint64_t)*(uint8_t *)(region + 0xe) << 0x10 |
                (uint64_t)*(uint8_t *)(region + 0xf) << 0x18 |
                (uint64_t)*(uint16_t *)(region + 0xc) |
                (uint64_t)((uint)*(uint8_t *)(region + 0x12) << 0x10 |
                           (uint)*(uint8_t *)(region + 0x13) << 0x18 |
                           (uint)*(uint16_t *)(region + 0x10)) << 0x20) + sk_phys_base;
        if (va < base || base + (uint64_t)*(uint16_t *)(region + 0x14) * 0x4000 <= va) {
            return 0;
        }
        slot = start + ((va - base) >> 0xe);
        if ((start <= slot && slot + 1 <= end) && slot <= slot + 1) {
            present = (uint64_t)(*slot != -1);
            return present;
        }
    }
    SoftwareBreakpoint(0x5519, 0x5236c);
    return 0;
}
/* FUN_0005236c @ 0x0005236c   (est. sk_region_fault)
 * Ghidra: undefined8 FUN_0005236c(long param_1, ulong param_2, long param_3)
 * Resolves a faulting virtual address within a region. First tries a fast
 * hook (sk_x_00051740) and, if that already handled the fault, returns 1.
 * Otherwise it walks the region's slot descriptors (param_1+0x18 area) and
 * fixes up the physical mapping (sk_ptr_fixup) for the faulting 16KiB slot,
 * with a special 0xfffe indirection slot. A slot of 0xffff, an out-of-range
 * address, or a descriptor overflow falls into the fatal first-fault/suspend
 * setup path. Returns 1 when the fault is handled; traps otherwise.
 * Confidence: medium
 * Notes: reads DAT_006ad6ea (fast-path flag), _DAT_006ad6e0 (phys base),
 *   DAT_006af8d0 (init flag), _DAT_006af8c8 (suspend hook); tpidr_el0 read
 *   collapsed to 0 per repo convention; string sk_str_005bba0f. */
static uint64_t sk_region_fault(long region, uint64_t va, long target)
{
    uint16_t *slots, *slots_end, *p;
    uint16_t slotval;
    uint64_t idx, pagebase, base, bound, slot_idx;
    unsigned long v;
    int i;

    if (*(uint8_t *)0x6ad6ea == 0x01) {
        v = sk_x_00051740(region, va, target);
        if ((v & 1) != 0) return 1;
        sk_x_004b5e20();
    }

    slots = (uint16_t *)(region + 0x18);
    idx = (uint64_t)(uint16_t)*(uint16_t *)(region + 0x16);
    slots_end = (uint16_t *)(region + idx * 4 + (uint64_t)*(uint16_t *)(region + 0x14) * 2 + 0x18);

    if (slots <= slots_end) {
        pagebase = (uint64_t)*(uint8_t *)(region + 0xe) << 0x10
                 | (uint64_t)*(uint8_t *)(region + 0xf) << 0x18
                 | (uint64_t)*(uint16_t *)(region + 0xc)
                 | (uint64_t)((uint32_t)*(uint8_t *)(region + 0x12) << 0x10
                             | (uint32_t)*(uint8_t *)(region + 0x13) << 0x18
                             | (uint32_t)*(uint16_t *)(region + 0x10)) << 0x20;
        base = *(uint64_t *)0x6ad6e0;
        bound = pagebase + base;
        if (va < bound ||
            base + (uint64_t)*(uint16_t *)(region + 0x14) * 0x4000 + pagebase <= va)
            goto panic;

        slot_idx = (va - bound) >> 0xe;
        p = slots + slot_idx;
        if ((slots <= p && p + 1 <= slots_end) && p <= p + 1) {
            slotval = *p;
            if (slotval == 0xfffe) {
                if (*(uint16_t *)(region + 0x16) != 0) {
                    unsigned long k = 0;
                    long basep = region;
                    do {
                        long e = basep + (uint64_t)*(uint16_t *)(region + 0x14) * 2;
                        uint16_t *a = (uint16_t *)(e + 0x18);
                        uint16_t *b = (uint16_t *)(e + 0x1a);
                        uint16_t *c = (uint16_t *)(e + 0x1c);
                        int wrapA = a < slots;
                        /* Faithful pointer-range guard; traps on wrap. */
                        int A = (wrapA || slots_end < b) || (b < a) || (slots_end <= c);
                        int B = (wrapA || slots_end < b) || (b < a) || (c != slots_end);
                        if (A && (B || (c <= b)) && (A || (b != c))) goto bad;
                        if (slot_idx == *a) {
                            sk_ptr_fixup(target + (uint64_t)*b, va & 0xffffffffffffc000,
                                         *(uint16_t *)(region + 2), -*(uint64_t *)0x6ad6e0,
                                         *(uint64_t *)0x6ad6e0);
                            idx = (uint64_t)*(uint16_t *)(region + 0x16);
                        }
                        k++;
                        basep += 4;
                    } while (k < idx);
                }
            } else {
                if (slotval == 0xffff) goto panic;
                sk_ptr_fixup(target + (uint64_t)slotval, va & 0xffffffffffffc000,
                             *(uint16_t *)(region + 2), -*(uint64_t *)0x6ad6e0,
                             *(uint64_t *)0x6ad6e0);
            }
            return 1;
        }
    }
bad:
    SoftwareBreakpoint(0x5519, 0x52570);
panic:
    /* LAB_00052570: fatal first-fault / suspend setup path. */
    v = sk_x_004b5e20();
    if ((*(uint64_t *)0x6af8d0 & 1) == 0) {
        uint64_t *thread_ptr = 0;            /* tpidr_el0 */
        uint64_t *slot, *prev;
        uint64_t u, n, r2;
        byte *tcb;
        unsigned char blob[16];
        uint8_t hi8, lo8;

        tcb = (byte *)sk_x_00054610();
        if ((*tcb & 1) == 0) {
            n = 0;
            r2 = sk_x_0006562c((uint64_t)sk_str_005bba0f, &n);
            if (*(long *)(tcb + 0xc0) == 0) sk_x_0004dfd0(n, r2);
        }
        hi8 = *(uint8_t *)0x6ad6e9;
        lo8 = *(uint8_t *)0x6ad6e8;
        *(uint64_t *)0x6ad6f0 = sk_x_00063aa8((uint64_t)sk_suspend, 0x52988, 0);
        u = (uint64_t)sk_x_000537c4();
        slot = thread_ptr + *(uint64_t *)0x6ad6f0;
        prev = slot - 1;
        if ((prev < thread_ptr || thread_ptr + 0x1f < slot) || slot < prev)
            SoftwareBreakpoint(0x5519, 0x52718);
        *prev = u;
        i = sk_x_0004fe80();
        if (i != 0) sk_x_0004ffd0(hi8, lo8);
        {
            uint64_t a = 0, b = 0, c = 0;
            sk_x_00053634(&a, &b, &c);
            sk_x_00035a78(a, b, c);
        }
        sk_x_0005371c();
        sk_x_0004d39c();
        sk_x_0004d8ec();
        if (*(uint64_t *)0x6af8c8 != 0)
            ((void (*)(void))*(uint64_t *)0x6af8c8)();
        sk_x_0005ee7c();
        i = sk_x_0004fe80();
        if (i != 0) sk_x_000501cc(hi8, lo8);
        sk_x_00060524();
        u = sk_x_00061630();
        /* sk_x_0004ba18 returns 16 bytes in x0:x1 (auVar22). */
        sk_x_0004ba18(blob);
        {
            uint64_t lo, hi;
            lo = *(uint64_t *)&blob[0];
            hi = *(uint64_t *)&blob[8];
            ((void (*)(uint64_t, uint64_t))*(uint64_t *)(hi + 0x20))(u, lo);
        }
        sk_x_00011d7c(0);
        sk_x_001190fc();
        u = sk_x_0005cb18(0);
        *(uint64_t *)0x6af8d0 = 1;
    }
    return v;
}

/* FUN_00052718 @ 0x00052718   (est. sk_xrt_init)
 * Ghidra: void FUN_00052718(undefined8 param_1)
 * Initialises the XRT run-time: records the suspend hook in _DAT_006af8c8 on
 * first call and returns; on re-entry it checks whether a suspended / failed
 * image is present (sk_x_004b5e30), sets up the platform log, then either
 * resumes via the suspend/schedule path or, on a clean boot, zeroes the
 * per-thread area (tpidrro_el0) and traps into the supervisor before fatally
 * logging "exclave is scheduled after suspend". Failure terminates with a
 * fatal "xrt_init failed with %d" message. No return value.
 * Confidence: medium
 * Notes: string refs sk_str_005bb99f / sk_str_005bb9d8 / sk_str_005bb986;
 *   tpidrro_el0 via sk_tpidrro(); trap path via CallSupervisor(0). */
static void sk_xrt_init(uint64_t flag)
{
    long r;
    byte *tcb;
    byte *th;
    int rc;

    if (*(uint64_t *)0x6af8c8 == 0) {
        *(uint64_t *)0x6af8c8 = flag;
        return;
    }
    r = sk_x_004b5e30();
    tcb = (byte *)sk_x_00054610();
    sk_x_000545a8(*(byte *)(tcb + 0xd8) & 1);
    sk_plat_log(r != 0, 1);
    sk_plat_log(r != 0, 0);
    if (r == 0 && (rc = sk_x_00060564(), rc != 0)) {
        rc = sk_x_000600f0(0x40000, (uint64_t)sk_x_00052930, tcb);
    } else {
        sk_xrt_log();
        rc = sk_x_00001378();
    }
    if (rc == 0) {
        sk_x_00060524();
        sk_x_0005b0bc();
        if (r != 0) return;
        sk_x_0005b89c();
        sk_printf((uint64_t)sk_str_005bb99f);
        rc = sk_x_0005ab94(1, 2);
        if (rc == 1) sk_x_00065020();
        th = (byte *)tpidrro_el0;
        th[1] = 0; *th = 0; th[4] = 0; th[2] = 0; th[5] = 0; th[3] = 0; th[6] = 0; th[7] = 0;
        CallSupervisor(0);
        *th = 0; th[7] = 0; th[6] = 0; th[5] = 0; th[4] = 0; th[3] = 0; th[2] = 0; th[1] = 0;
        sk_fatal_printf((uint64_t)sk_str_005bb9d8, 1);   /* noreturn */
    }
    sk_x_004afae4((uint64_t)sk_str_005bb986);            /* noreturn */
}

/* FUN_000528c4 @ 0x000528c4   (est. sk_plat_log)
 * Ghidra: void FUN_000528c4(int param_1, undefined8 param_2)
 * Emits a platform log record. It tags the log with the 'plat' prefix and,
 * unless the log is disabled, emits a 'root' record when param_1 is
 * non-zero. Returns nothing.
 * Confidence: high
 * Notes: log tags 'plat' (0x706c6174) and 'root' (0x726f6f74); delegates to
 *   sk_x_0005cf4c / sk_x_00050444. */
static void sk_plat_log(int a, uint64_t b)
{
    sk_x_0005cf4c(0x706c6174);
    if (sk_x_0004fe80() != 0) {
        sk_x_00050444(b);
        return;
    }
    if (a != 0) {
        sk_x_0005cf4c(0x726f6f74, b);
        return;
    }
}

/* FUN_00052940 @ 0x00052940   (est. sk_entry_init)
 * Ghidra: void FUN_00052940(void)
 * Entry-point initialisation: emits the XRT entry log line and runs the
 * low-level entry bootstrap (sk_x_00001378). Returns nothing.
 * Confidence: high
 * Notes: wraps sk_xrt_log() + sk_x_00001378(). */
static void sk_entry_init(void)
{
    sk_xrt_log();
    sk_x_00001378();
}

/* FUN_0005295c @ 0x0005295c   (est. sk_xrt_log)
 * Ghidra: void FUN_0005295c(void)
 * Logs the XRT entry banner string via the variadic printf2 path. Returns
 * nothing.
 * Confidence: high
 * Notes: string sk_str_005bba8a. */
static void sk_xrt_log(void)
{
    sk_printf2((uint64_t)sk_str_005bba8a);
}

/* FUN_00052968 @ 0x00052968   (est. sk_suspend)
 * Ghidra: void FUN_00052968(void)
 * Suspends the current context: bails if a suspend guard (sk_x_00034f70)
 * or an in-flight suspend flag (sk_x_004b5e48) is set (the latter also
 * invoking sk_x_004b23d8), otherwise reads the current state
 * (sk_x_004b5e60) and, after normalising state 6 to 3, drives the power /
 * suspend transition via sk_x_0005c650 (state 4 maps to 2). Returns
 * nothing.
 * Confidence: medium
 * Notes: default branch writes to a decompiler 'extraout_x8' return artifact,
 *   dropped since the signature is void. */
static void sk_suspend(void)
{
    int state;
    uint64_t s;

    if (sk_x_00034f70() != 0) return;
    if (sk_x_004b5e48() != 0) { sk_x_004b23d8(); return; }
    s = sk_x_004b5e60();
    state = (int)s;
    if (state != 1) {
        if (state != 6) {
            if (state == 4) { sk_x_0005c650(2); return; }
            return;
        }
        s = 3;
    }
    sk_x_0005c650(s);
}

/* FUN_0005296c @ 0x0005296c   (est. sk_suspend2)
 * Ghidra: void FUN_0005296c(void)
 * Suspend-variant with the same state-machine as sk_suspend: early-returns
 * on the suspend guard / in-flight flag, normalises state 6 to 3, maps state
 * 4 to 2, and drives sk_x_0005c650 otherwise. Returns nothing.
 * Confidence: medium
 * Notes: identical body to sk_suspend; 'extraout_x8' return artifact dropped
 *   for the void signature. */
static void sk_suspend2(void)
{
    int state;
    uint64_t s;

    if (sk_x_00034f70() != 0) return;
    if (sk_x_004b5e48() != 0) { sk_x_004b23d8(); return; }
    s = sk_x_004b5e60();
    state = (int)s;
    if (state != 1) {
        if (state != 6) {
            if (state == 4) { sk_x_0005c650(2); return; }
            return;
        }
        s = 3;
    }
    sk_x_0005c650(s);
}

/* FUN_00052994 @ 0x00052994   (est. sk_suspend3)
 * Ghidra: void FUN_00052994(void)
 * Suspend-variant without the guard/in-flight checks: reads the state
 * (sk_x_004b5e60), normalises state 6 to 3 and state 4 to 2, and drives the
 * suspend transition via sk_x_0005c650. Returns nothing.
 * Confidence: high
 * Notes: 'extraout_x8' return artifact dropped for the void signature. */
static void sk_suspend3(void)
{
    int state;
    uint64_t s;

    s = sk_x_004b5e60();
    state = (int)s;
    if (state != 1) {
        if (state != 6) {
            if (state == 4) { sk_x_0005c650(2); return; }
            return;
        }
        s = 3;
    }
    sk_x_0005c650(s);
}

/* FUN_000529a0 @ 0x000529a0   (est. sk_suspend4)
 * Ghidra: void FUN_000529a0(undefined8 *param_1, undefined8 param_2)
 * Suspend-variant that takes a state code (arg): normalises state 6 to 3 and
 * state 4 to 2 and drives sk_x_0005c650; on an unrecognised state it zeroes
 * the caller's three-word out buffer (*out, out[1], out[2]) and returns.
 * Returns nothing.
 * Confidence: high
 * Notes: out words are the extraout_x8 store that is meaningful here. */
static void sk_suspend4(uint64_t *out, uint64_t arg)
{
    int state;

    state = (int)arg;
    if (state != 1) {
        if (state != 6) {
            if (state == 4) { sk_x_0005c650(2); return; }
            out[1] = 0; out[2] = 0; *out = 0;
            return;
        }
        arg = 3;
    }
    sk_x_0005c650(arg);
}

/* FUN_000529d4 @ 0x000529d4   (est. sk_suspend_get)
 * Ghidra: undefined8 FUN_000529d4(undefined8 param_1)
 * Reads back the suspend-related state counter for a given state code via
 * sk_x_0005c924, normalising state 6 to 3 and state 4 to 2. For an
 * unrecognised state it returns 0xffffffffffffffff. Returns the counter
 * value.
 * Confidence: high
 * Notes: none. */
static uint64_t sk_suspend_get(uint64_t arg)
{
    int state;
    uint64_t v;

    state = (int)arg;
    if (state != 1) {
        if (state != 6) {
            if (state == 4) {
                v = sk_x_0005c924(2);
                return v;
            }
            return 0xffffffffffffffff;
        }
        arg = 3;
    }
    v = sk_x_0005c924(arg);
    return v;
}

/* FUN_00052a04 @ 0x00052a04   (est. sk_cnode_init)
 * Ghidra: void FUN_00052a04(ulong param_1)
 * Initialises the capability-node (cnode) allocator: stores the base address
 * in the 0x64cc60 slot, links the 0x64cc80 slot to the 0x6af8e0 list, then
 * walks the bootmem descriptor list (0x6aff18) filling cnode records in the
 * 0x6af8d8 object. For each valid descriptor entry with a '\v' (0xb) tag it
 * records the object address at offset 0x2a0 of the cnode object. Traps on
 * base overflow or descriptor-range violations.
 * Confidence: low
 * Notes: raw data slots 0x64cc60 / 0x64cc80 / 0x6aff18 / 0x6af8d8; uint3
 *   reads expressed as byte loads; trap 0x52c4c. */
static void sk_cnode_init(uint64_t base)
{
    uint16_t *node, *p, *n;
    unsigned long k, count;
    uint64_t t3;
    long res;

    if (base <= base + 0x4000) {
        res = sk_x_0005baac(4, 4);
        if (res == 0) {
            *(uint64_t *)0x64cc60 = base;
            sk_x_0005ba5c();
            *(uint64_t *)0x64cc80 = 0x6af8e0;
            sk_x_0005ba5c();
            for (node = (uint16_t *)sk_x_0005acac(0x6aff18, 2, 4);
                 node != (uint16_t *)-1; node = n) {
                if (node + 0x2000 < node) goto bad;
                count = (uint64_t)(uint8_t)node[1] << 0x10
                      | (uint64_t)*(uint8_t *)((long)node + 3) << 0x18
                      | (uint64_t)node[0]
                      | (uint64_t)((uint32_t)(uint8_t)node[3] << 0x10
                                  | (uint32_t)*(uint8_t *)((long)node + 7) << 0x18
                                  | (uint32_t)node[2]) << 0x20;
                if (count != 0 &&
                    (((uint8_t)node[1] != 0 || *(uint8_t *)((long)node + 3) != 0) ||
                     node[0] != 0)) {
                    k = 0;
                    p = node + 0x10;
                    do {
                        if (p != (uint16_t *)0 &&
                            ((p < node + 0x10 || node + 0x2000 < p + 0x10) ||
                             p + 0x10 < p)) goto bad;
                        t3 = (uint64_t)*(uint8_t *)((long)p + 4)
                           | (uint64_t)*(uint8_t *)((long)p + 5) << 8
                           | (uint64_t)*(uint8_t *)((long)p + 6) << 16;
                        if (*(char *)((long)p + 7) == '\v') {
                            uint16_t w0, w1;
                            uint8_t b1;
                            if (p + 0x10 < p) goto bad;
                            w0 = p[0];
                            b1 = *(uint8_t *)((long)p + 3);
                            w1 = p[1];
                            res = sk_x_0005acac(0x6af8d8, 2, 5);
                            *(uint64_t *)(res + 0x2a0) =
                                 (uint64_t)(uint8_t)w1 << 0x10 | (uint64_t)b1 << 0x18
                               | (uint64_t)w0 | t3 << 0x20;
                        }
                        k++;
                        p += 0x10;
                    } while (k < count);
                }
                n = (uint16_t *)((uint64_t)(uint8_t)node[5] << 0x10
                       | (uint64_t)*(uint8_t *)((long)node + 0xb) << 0x18
                       | (uint64_t)node[4]
                       | (uint64_t)((uint32_t)(uint8_t)node[7] << 0x10
                                   | (uint32_t)*(uint8_t *)((long)node + 0xf) << 0x18
                                   | (uint32_t)node[6]) << 0x20);
            }
        }
        return;
    }
bad:
    SoftwareBreakpoint(0x5519, 0x52c4c);
}

/* FUN_00052c4c @ 0x00052c4c   (est. sk_cnode_get0)
 * Ghidra: undefined8 FUN_00052c4c(undefined8 *param_1)
 * Returns the first word of the given cnode record. No side effects.
 * Confidence: high
 * Notes: trivial dereference of *p. */
static uint64_t sk_cnode_get0(uint64_t *p)
{
    return *p;
}

/* FUN_00052c54 @ 0x00052c54   (est. sk_cnode_scan)
 * Ghidra: void FUN_00052c54(void)
 * Scans the bootmem descriptor list (0x6aff18) and the cnode object
 * (0x6af8d8) to coalesce capability-node ranges. It reads three type codes
 * (sk_x_000552a4 / sk_x_00055780 / sk_x_00055858) and, unless the scan is
 * already complete (bit 0 at +0x630), walks every descriptor, tracking the
 * contiguous cnode start/end at +0x248/+0x250 and filling per-type fields
 * (+0x288/+0x290/+0x298/+0x2a0/+0x2a8, the slot table at +0x2c8, and the
 * region bounds at +0x18/+0x20 or +8/+0x10). Finalises a free-slot window
 * at +0x258..+0x270 when the range closes. Fatally aborts on inconsistent
 * or non-contiguous ranges. Traps on descriptor-range violations.
 * Confidence: low
 * Notes: complex multi-type scan; string refs sk_str_005bbd35/005bbbc5/
 *   005bbc81/005bbcc3/005bbc29; uint3 reads as byte loads; global
 *   _DAT_006aff20; trap 0x532f4. */
static void sk_cnode_scan(void)
{
    uint16_t *node, *p, *next;
    unsigned long count, k;
    uint64_t v, u16v;
    uint32_t tag;
    uint32_t type9, type10, type11;
    long obj;
    uint64_t free_end, free_start, slot_count;

    type9 = sk_x_000552a4();
    type10 = sk_x_00055780();
    type11 = sk_x_00055858();
    node = (uint16_t *)sk_x_0005acac(0x6aff18, 2, 4);
    obj = sk_x_0005acac(0x6af8d8, 2, 5);
    if ((*(uint8_t *)(obj + 0x630) & 1) != 0) return;

    for (;;) {
        if (node == (uint16_t *)-1) {
            if (*(char *)(obj + 0x278) != '\0') {
                *(uint8_t *)(obj + 0x279) = 0;
                sk_x_004afae4((uint64_t)sk_str_005bbd35);   /* noreturn */
            }
            if (*(char *)(obj + 0x27a) == '\x01') {
                sk_x_004afae4((uint64_t)sk_str_005bbbc5);   /* noreturn */
            }
            free_end = *(uint64_t *)(obj + 0x240);
            if (*(uint64_t *)(obj + 0x238) == free_end) {
                sk_x_004b5e78();
            } else {
                free_start = *(uint64_t *)(obj + 0x250);
                if (*(uint64_t *)(obj + 0x238) == *(uint64_t *)(obj + 0x248)) {
                    if (free_end < free_start) {
                        sk_x_004afae4((uint64_t)sk_str_005bbc81);   /* noreturn */
                    }
                    if (0x3ff < free_end - free_start) {
                        *(uint64_t *)(obj + 0x258) = free_start;
                        slot_count = (free_end - free_start & 0xffffffffffffffc0) + free_start;
                        *(long *)(obj + 0x260) = slot_count - 0x400;
                        *(long *)(obj + 0x268) = slot_count - 0x400;
                        *(long *)(obj + 0x270) = slot_count;
                        *(uint8_t *)(obj + 0x278) = 1;
                        *(uint8_t *)(obj + 0x630) = 1;
                        return;
                    }
                    sk_x_004afae4((uint64_t)sk_str_005bbcc3);   /* noreturn */
                }
            }
            sk_x_004afae4((uint64_t)sk_str_005bbc29);   /* noreturn */
        }
        if (node + 0x2000 < node) break;
        count = (uint64_t)(uint8_t)node[1] << 0x10
              | (uint64_t)*(uint8_t *)((long)node + 3) << 0x18
              | (uint64_t)node[0]
              | (uint64_t)((uint32_t)(uint8_t)node[3] << 0x10
                          | (uint32_t)*(uint8_t *)((long)node + 7) << 0x18
                          | (uint32_t)node[2]) << 0x20;
        if (count != 0 &&
            (((uint8_t)node[1] != 0 || *(uint8_t *)((long)node + 3) != 0) ||
             node[0] != 0)) {
            k = 0;
            p = node + 0x10;
            do {
                uint16_t *q;
                if (p != (uint16_t *)0 &&
                    ((p < node + 0x10 || node + 0x2000 < p + 0x10) ||
                     p + 0x10 < p)) goto bad;
                tag = (uint32_t)*(uint8_t *)((long)p + 7);
                v = (uint64_t)(uint8_t)p[1] << 0x10
                  | (uint64_t)*(uint8_t *)((long)p + 3) << 0x18
                  | (uint64_t)p[0]
                  | (uint64_t)((uint32_t)*(uint8_t *)((long)p + 4)
                             | (uint32_t)*(uint8_t *)((long)p + 5) << 8
                             | (uint32_t)*(uint8_t *)((long)p + 6) << 16) << 0x20;
                if (*(uint64_t *)(obj + 0x248) == 0 && *(long *)(obj + 0x250) == 0) {
                    *(uint64_t *)(obj + 0x248) = v;
                    *(uint64_t *)(obj + 0x250) = v + 0x40;
                } else {
                    if (v < *(uint64_t *)(obj + 0x248))
                        *(uint64_t *)(obj + 0x248) = v;
                    if (*(uint64_t *)(obj + 0x250) < v + 0x40)
                        *(uint64_t *)(obj + 0x250) = v + 0x40;
                }
                q = p + 0x10;
                if (tag < 0x12) {
                    switch (tag) {
                    case 1: case 2: case 3: case 5: case 8: case 9: case 0xf: case 0x10:
                        goto tagdispatch;
                    case 4:
                        if (p <= q) {
                            uint16_t a0 = p[8];
                            uint8_t a1 = *(uint8_t *)((long)p + 0x13);
                            uint16_t a2 = p[9];
                            uint16_t a3 = p[10];
                            long o2 = sk_x_0005acac(0x6af8d8, 2, 5);
                            if (o2 + 0x238 <= o2 + 0x288) {
                                if (*(char *)(o2 + 0x278) != '\0') {
                                    *(uint8_t *)(o2 + 0x279) = 0;
                                    sk_x_004afae4((uint64_t)sk_str_005bbd35);   /* noreturn */
                                }
                                v = ((uint64_t)(uint8_t)a2 << 0x10 | (uint64_t)a1 << 0x18
                                     | (uint64_t)a0) << 0xc | (uint64_t)(uint8_t)a3 << 0x2c;
                                if (*(long *)(o2 + 0x238) == 0 && *(uint64_t *)(o2 + 0x240) == 0) {
                                    *(uint64_t *)(o2 + 0x238) = v;
                                    *(uint64_t *)(o2 + 0x240) = v + 0x4000;
                                } else if (*(uint64_t *)(o2 + 0x240) == v) {
                                    *(uint64_t *)(o2 + 0x240) = v + 0x4000;
                                } else if ((*(uint8_t *)(o2 + 0x27a) & 1) == 0) {
                                    *(uint8_t *)(o2 + 0x27a) = 1;
                                    *(uint64_t *)(o2 + 0x280) = v;
                                }
                                goto dofill;
                            }
                        }
                        goto bad;
                    case 6:
                        if (q < p) goto bad;
                        *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x288) = v;
                        break;
                    case 7:
                        if (q < p) goto bad;
                        *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x290) = v;
                        break;
                    case 10:
                        if (q < p) goto bad;
                        {
                            uint64_t *slot = (uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x38)
                                           + *(uint64_t *)0x6aff20 * 2;
                            uint16_t w8;
                            if (slot < (uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x38) ||
                                (uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x238) < slot + 2 ||
                                slot + 2 < slot) goto bad;
                            w8 = p[8];
                            *slot = v;
                            *(uint16_t *)(slot + 1) =
                                (uint16_t)((uint16_t)*(uint8_t *)((long)p + 0x11) << 8
                                           | (uint8_t)w8);
                            *(uint64_t *)0x6aff20 = *(uint64_t *)0x6aff20 + 1;
                        }
                        break;
                    case 0xb:
                        if (q < p) goto bad;
                        *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x2a0) = v;
                        break;
                    case 0xc:
                        *(uint64_t *)(obj + 0x28) = v;
                        *(uint64_t *)(obj + 0x30) = 0;
                        break;
                    case 0xd:
                        u16v = ((uint64_t)(uint8_t)p[9] << 0x10
                              | (uint64_t)*(uint8_t *)((long)p + 0x13) << 0x18
                              | (uint64_t)p[8]) << 0xc | (uint64_t)(uint8_t)p[10] << 0x2c;
                        if (*(uint64_t *)(obj + 0x20) <= u16v) {
                            *(uint64_t *)(obj + 0x18) = v;
                            *(uint64_t *)(obj + 0x20) = u16v;
                        }
                        break;
                    case 0xe:
                        u16v = ((uint64_t)(uint8_t)p[9] << 0x10
                              | (uint64_t)*(uint8_t *)((long)p + 0x13) << 0x18
                              | (uint64_t)p[8]) << 0xc | (uint64_t)(uint8_t)p[10] << 0x2c;
                        if (*(uint64_t *)(obj + 0x10) <= u16v) {
                            *(uint64_t *)(obj + 8) = v;
                            *(uint64_t *)(obj + 0x10) = u16v;
                        }
                        break;
                    case 0x11:
                        if (q < p) goto bad;
dofill:
                        sk_x_00053858((long)p);
                        break;
                    }
                } else {
tagdispatch:
                    if (type9 == tag) {
                        if (q < p) goto bad;
                        *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x2a8) = v;
                    } else if (type10 == tag) {
                        if (q < p) goto bad;
                        *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x298) = v;
                    } else if (type11 == tag) {
                        if (q < p) goto bad;
                        sk_x_00055948(p);
                        {
                            uint64_t *slot = (uint64_t *)sk_x_00053598(0);
                            if (slot + 1 < slot) goto bad;
                            *slot = (uint64_t)(uint8_t)p[1] << 0x10
                                  | (uint64_t)*(uint8_t *)((long)p + 3) << 0x18
                                  | (uint64_t)p[0]
                                  | (uint64_t)((uint32_t)*(uint8_t *)((long)p + 4)
                                             | (uint32_t)*(uint8_t *)((long)p + 5) << 8
                                             | (uint32_t)*(uint8_t *)((long)p + 6) << 16) << 0x20;
                        }
                    } else {
                        if (tag != 5) goto bottom;
                        if (q < p) goto bad;
                        {
                            long o3 = sk_x_0005acac(0x6af8d8, 2, 5);
                            long cnt = *(long *)(o3 + 0x628);
                            uint64_t *slot = (uint64_t *)(o3 + 0x2c8) + cnt * 3;
                            uint32_t t3;
                            uint16_t *pp;
                            if (slot < (uint64_t *)(o3 + 0x2c8)) goto bad;
                            if ((uint64_t *)(o3 + 0x628) < slot + 3 || slot + 3 < slot) goto bad;
                            t3 = (uint32_t)*(uint8_t *)((long)p + 16)
                               | (uint32_t)*(uint8_t *)((long)p + 17) << 8
                               | (uint32_t)*(uint8_t *)((long)p + 18) << 16;
                            *slot = v;
                            slot[1] = (uint64_t)t3;
                            pp = p + 0xc;
                            if (q < pp || pp < p) goto bad;
                            *(uint8_t *)(slot + 2) = *(uint8_t *)pp & 1;
                            *(uint64_t *)(o3 + 0x628) = cnt + 1;
                        }
                    }
                }
bottom:
                k++;
                p += 0x10;
            } while (k < count);
        }
        node = (uint16_t *)((uint64_t)(uint8_t)node[5] << 0x10
                 | (uint64_t)*(uint8_t *)((long)node + 0xb) << 0x18
                 | (uint64_t)node[4]
                 | (uint64_t)((uint32_t)(uint8_t)node[7] << 0x10
                             | (uint32_t)*(uint8_t *)((long)node + 0xf) << 0x18
                             | (uint32_t)node[6]) << 0x20);
    }
bad:
    SoftwareBreakpoint(0x5519, 0x532f4);
}

/* FUN_000533ec @ 0x000533ec   (est. sk_cnode_fault)
 * Ghidra: undefined8 FUN_000533ec(void)
 * Returns the cnode object's fault-handler word (offset 0x2a0). No side
 * effects.
 * Confidence: high
 * Notes: reads 0x6af8d8 + 0x2a0. */
static uint64_t sk_cnode_fault(void)
{
    return *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x2a0);
}

/* FUN_00053418 @ 0x00053418   (est. sk_cnode_get_288)
 * Ghidra: undefined8 FUN_00053418(void)
 * Returns the cnode object's word at offset 0x288. No side effects.
 * Confidence: high
 * Notes: reads 0x6af8d8 + 0x288. */
static uint64_t sk_cnode_get_288(void)
{
    return *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x288);
}

/* FUN_00053444 @ 0x00053444   (est. sk_cnode_get_2a8)
 * Ghidra: undefined8 FUN_00053444(void)
 * Returns the cnode object's word at offset 0x2a8. No side effects.
 * Confidence: high
 * Notes: reads 0x6af8d8 + 0x2a8. */
static uint64_t sk_cnode_get_2a8(void)
{
    return *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x2a8);
}

/* FUN_00053470 @ 0x00053470   (est. sk_cnode_bootmem)
 * Ghidra: void FUN_00053470(void)
 * Touches (walks) the bootmem descriptor list head at 0x6aff18. Returns
 * nothing.
 * Confidence: high
 * Notes: single call to sk_x_0005acac(0x6aff18,2,4). */
static void sk_cnode_bootmem(void)
{
    sk_x_0005acac(0x6aff18, 2, 4);
}

/* FUN_00053484 @ 0x00053484   (est. sk_cnode_get_298)
 * Ghidra: undefined8 FUN_00053484(long param_1)
 * Returns the cnode object's word at offset 0x298, but only when the guard
 * argument is zero; otherwise returns 0. No side effects.
 * Confidence: high
 * Notes: reads 0x6af8d8 + 0x298. */
static uint64_t sk_cnode_get_298(long arg)
{
    if (arg != 0) return 0;
    return *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x298);
}

/* FUN_000534c0 @ 0x000534c0   (est. sk_cnode_get_628)
 * Ghidra: undefined8 FUN_000534c0(void)
 * Returns the cnode object's slot-table count word at offset 0x628. No side
 * effects.
 * Confidence: high
 * Notes: reads 0x6af8d8 + 0x628. */
static uint64_t sk_cnode_get_628(void)
{
    return *(uint64_t *)(sk_x_0005acac(0x6af8d8, 2, 5) + 0x628);
}

/* FUN_000534ec @ 0x000534ec   (est. sk_cnode_get_slot)
 * Ghidra: undefined8 FUN_000534ec(long param_1, undefined8 *param_2, undefined1 *param_3)
 * Reads the idx-th entry of the cnode slot table (three words at
 * 0x6af8d8+0x2c8 + idx*3): returns the entry's second word and stores the
 * first and third words through the out parameters (*a, *b). Traps when idx
 * is out of the slot-table range.
 * Confidence: high
 * Notes: slot-table bounds 0x2c8..0x628; trap 0x53568. */
static uint64_t sk_cnode_get_slot(long idx, uint64_t *a, uint8_t *b)
{
    uint64_t *slot;
    uint64_t v;
    long obj;

    obj = sk_x_0005acac(0x6af8d8, 2, 5);
    slot = (uint64_t *)(obj + 0x2c8) + idx * 3;
    if ((uint64_t *)(obj + 0x2c8) <= slot && slot + 3 <= (uint64_t *)(obj + 0x628) &&
        slot <= slot + 3) {
        v = slot[1];
        *a = slot[0];
        *b = *(uint8_t *)(slot + 2);
        return v;
    }
    SoftwareBreakpoint(0x5519, 0x53568);
}
/* FUN_00053568 @ 0x00053568   (sk_cnode_first)
 * Ghidra: undefined8 FUN_00053568(void)
 * Returns the first capability-node (cnode) slot of the current cnode object. It
 * resolves the cnode pointer via sk_cnode_ptr and, after an overflow sanity check
 * (slot + 8 must not wrap), returns the first 8-byte word stored at that slot.
 * Returns 0 when no cnode is available.
 * Confidence: high
 * Notes: decompile shows sk_cnode_ptr() called with no explicit argument
 * (register-held); reconstructed as 0. */
static uint64_t sk_cnode_first(void)
{
    uint64_t *cnode;
    uint64_t result;

    cnode = (uint64_t *)sk_cnode_ptr(0);
    result = 0;
    if (cnode != (uint64_t *)0x0) {
        if (cnode + 1 < cnode) {
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x53598);
        }
        result = *cnode;
    }
    return result;
}

/* FUN_00053598 @ 0x00053598   (sk_cnode_ptr)
 * Ghidra: ulong FUN_00053598(long param_1)
 * Returns a pointer to one of the capability-node (cnode) regions embedded in the
 * per-CPU object at the shared slot address 0x6af8d8. which selects the region:
 * 1 -> offset 0x2b8, 2 -> dynamic region at +0x2c0 (bounds-checked against
 * +0x2b0..+0x2c8), 3 -> offset 0x2b0; any other value yields 0. The object is
 * fetched via sk_x_0005acac(0x6af8d8,2,5).
 * Confidence: high
 * Notes: for which==2 the overflow check on the pointer arithmetic is fatal
 * (SoftwareBreakpoint). */
static uint64_t sk_cnode_ptr(long which)
{
    uint64_t base;
    uint64_t cnode;

    if (which == 1) {
        base = 0x2b8;
    }
    else {
        if (which == 2) {
            base = sk_x_0005acac(0x6af8d8, 2, 5);
            cnode = base + 0x2c0;
            if (cnode == 0) {
                return 0;
            }
            if ((cnode <= base + 0x2c8U) && (base + 0x2b0U <= cnode)) {
                return cnode;
            }
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x53604);
        }
        if (which != 3) {
            return 0;
        }
        base = 0x2b0;
    }
    return sk_x_0005acac(0x6af8d8, 2, 5) + base;
}

/* FUN_00053634 @ 0x00053634   (sk_cnode_finalize)
 * Ghidra: void FUN_00053634(ulong *param_1,long *param_2,ulong *param_3)
 * Finalizes the current cnode object: validates that it is in the "building"
 * state (state byte at +0x278 == 1), sets it to state 2 ("finalized"), and
 * exports the final slot range. Outputs the cnode base (a), the current slot
 * pointer (b) and the slot count (c = (end - current) >> 6). The range must be
 * 0x4000-aligned with base within [start,end] and end equal to the object's end
 * field, else sk_x_004b5e9c aborts. A bad state panics via sk_x_004afae4.
 * Confidence: high
 * Notes: string s_cna__p__expected_state__d__was___005bbd35 is the panic format. */
static void sk_cnode_finalize(uint64_t *a, long *b, uint64_t *c)
{
    long obj;
    uint64_t start;
    uint64_t end;
    long current;
    long end_slot;

    obj = sk_x_0005acac(0x6af8d8, 2, 5);
    if (obj + 0x238U <= obj + 0x288U) {
        if (*(char *)(obj + 0x278) != '\x01') {
            *(char *)(obj + 0x279) = 1;
            /* WARNING: Subroutine does not return */
            sk_x_004afae4((uint64_t)sk_str_cna__p__expected_state__d__was___005bbd35);
        }
        *(char *)(obj + 0x278) = 2;
        start = *(uint64_t *)(obj + 0x238);
        end = *(uint64_t *)(obj + 0x240);
        if ((((((uint32_t)start | (uint32_t)end) & 0x3fff) == 0) && (end == *(uint64_t *)(obj + 0x270))) &&
            (start <= *(uint64_t *)(obj + 0x268) && *(uint64_t *)(obj + 0x268) <= end)) {
            *a = start;
            current = *(long *)(obj + 0x268);
            *b = current;
            end_slot = *(long *)(obj + 0x270);
            *c = (uint64_t)(end_slot - current) >> 6;
            return;
        }
        sk_x_004b5e9c();
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x536f8);
}

/* FUN_0005371c @ 0x0005371c   (sk_cnode_teardown)
 * Ghidra: void FUN_0005371c(void)
 * Tears down the current cnode object. When the object is in the "finalized"
 * state (state byte at +0x278 == 2) it is moved to state 3 and every slot from
 * the start pointer (offset 600) up to the end pointer (+0x260), stepping by
 * 0x40 (64 bytes), is released via sk_x_004b23d8. Any other state panics with the
 * "expected state" message through sk_x_004afae4.
 * Confidence: high
 * Notes: string s_cna__p__expected_state__d__was___005bbd35 is the panic format. */
static void sk_cnode_teardown(void)
{
    long obj;
    uint64_t slot;

    obj = sk_x_0005acac(0x6af8d8, 2, 5);
    if (obj + 0x288U < obj + 0x238U) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x537a0);
    }
    if (*(char *)(obj + 0x278) == '\x02') {
        *(char *)(obj + 0x278) = 3;
        for (slot = *(uint64_t *)(obj + 600); slot < *(uint64_t *)(obj + 0x260); slot = slot + 0x40) {
            sk_x_004b23d8(slot);
        }
        return;
    }
    *(char *)(obj + 0x279) = 2;
    /* WARNING: Subroutine does not return */
    sk_x_004afae4((uint64_t)sk_str_cna__p__expected_state__d__was___005bbd35);
}

/* FUN_000537c4 @ 0x000537c4   (sk_cnode_alloc)
 * Ghidra: ulong * FUN_000537c4(void)
 * Allocates the next capability-node (cnode) slot from the current cnode object
 * when it is in the "building" state (state byte at +0x278 == 1): it bumps the
 * free pointer at +0x268 by one slot (8 words) and returns the previous slot.
 * When the free pool is exhausted it expands the object: computes a new limit
 * from packed fields at +0x10..+0x14 (+0x4000 slack) and raises the shared
 * object's capacity field at 0x6af8d8 to match, returning that object pointer.
 * A non-building state panics via sk_x_004afae4.
 * Confidence: high
 * Notes: sk_x_004b5ee0 supplies the object whose fields drive the expansion. */
static uint64_t *sk_cnode_alloc(void)
{
    uint64_t *slot;
    long obj;
    uint64_t limit;

    obj = sk_x_0005acac(0x6af8d8, 2, 5);
    if (obj + 0x288U < obj + 0x238U) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x53830);
    }
    if (*(char *)(obj + 0x278) == '\x01') {
        slot = *(uint64_t **)(obj + 0x268);
        if (slot < *(uint64_t **)(obj + 0x270)) {
            *(uint64_t **)(obj + 0x268) = slot + 8;
            return slot;
        }
        obj = sk_x_004b5ee0();
        limit = ((((uint64_t)*(uint8_t *)(obj + 0x12) << 0x10 |
                   (uint64_t)*(uint8_t *)(obj + 0x13) << 0x18 |
                   (uint64_t)*(uint16_t *)(obj + 0x10)) << 0xc |
                  (uint64_t)*(uint8_t *)(obj + 0x14) << 0x2c)) + 0x4000;
        slot = (uint64_t *)sk_x_0005acac(0x6af8d8, 2, 5);
        if (*slot < limit) {
            *slot = limit;
        }
        return slot;
    }
    *(char *)(obj + 0x279) = 1;
    /* WARNING: Subroutine does not return */
    sk_x_004afae4((uint64_t)sk_str_cna__p__expected_state__d__was___005bbd35);
}

/* FUN_00053858 @ 0x00053858   (sk_cnode_advance)
 * Ghidra: void FUN_00053858(long param_1)
 * Advances the cnode capacity: computes a new limit from the packed fields at
 * p+0x10..+0x14 (a byte-shifted extent) plus 0x4000 slack, and raises the shared
 * object's capacity field at 0x6af8d8 to that limit if it is currently smaller.
 * Confidence: high
 * Notes: identical limit computation to sk_cnode_alloc's expansion path. */
static void sk_cnode_advance(long p)
{
    uint64_t limit;
    uint64_t *slot;

    limit = ((((uint64_t)*(uint8_t *)(p + 0x12) << 0x10 |
               (uint64_t)*(uint8_t *)(p + 0x13) << 0x18 |
               (uint64_t)*(uint16_t *)(p + 0x10)) << 0xc |
              (uint64_t)*(uint8_t *)(p + 0x14) << 0x2c)) + 0x4000;
    slot = (uint64_t *)sk_x_0005acac(0x6af8d8, 2, 5);
    if (*slot < limit) {
        *slot = limit;
    }
    return;
}

/* FUN_000538c8 @ 0x000538c8   (sk_parse_dec)
 * Ghidra: int FUN_000538c8(undefined8 param_1,ulong param_2,ulong param_3,undefined8 param_4)
 * Parses a sequence of decimal numbers out of the buffer at b (with a maximum
 * length c) and returns their running sum. Each token is located by scanning for
 * a newline (0x0a) via sk_x_001144a0, converted with sk_x_00118abc, and the
 * separator checked with sk_x_001187f4; sk_x_0011883c advances the scanner.
 * Returns early (partial sum) on exhaustion, on a short token, or on a -1
 * separator result. A malformed buffer layout trips the fatal breakpoint.
 * Confidence: medium
 * Notes: sk_x_001144a0 is called with 2 and 3 arguments (variadic helper);
 * a/d are opaque context handles threaded to the parser helpers. */
static int sk_parse_dec(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    long end;
    uint64_t remaining;
    uint64_t seg_len;
    uint64_t digit;
    int sum;
    long sep;
    uint64_t next;
    bool wrapped;

    end = sk_x_001144a0(b, 0);
    remaining = c;
    if ((end == 0) || (remaining = end - b, remaining <= c)) {
        sum = 0;
        while (true) {
            if (remaining == 0) {
                return sum;
            }
            sk_x_0011883c(a, d);
            end = sk_x_001144a0(b, 10, remaining);
            seg_len = remaining;
            if (end != 0) {
                seg_len = end - b;
            }
            if (remaining < seg_len) break;
            digit = sk_x_00118abc(b, seg_len, 1, d);
            sum = sum + (int)digit;
            if (digit < seg_len) {
                return sum;
            }
            sep = sk_x_001187f4(10, d);
            if (sep == -1) {
                return sum;
            }
            next = b + seg_len + 1;
            if ((b + remaining < next) ||
                (remaining = remaining - (seg_len + 1), wrapped = next < b, b = next, wrapped)) break;
        }
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x539a4);
}

/* FUN_000539c0 @ 0x000539c0   (sk_eq)
 * Ghidra: bool FUN_000539c0(long param_1,long param_2)
 * Returns whether a and b are equal.
 * Confidence: high */
static bool sk_eq(long a, long b)
{
    return a == b;
}

/* FUN_000539cc @ 0x000539cc   (sk_free_page)
 * Ghidra: undefined8 FUN_000539cc(ulong param_1)
 * Releases a single page: after an overflow sanity check (p+0x10 must not wrap)
 * it hands p to sk_x_0005d394 with the free flag set (1) and returns 0. On
 * overflow the fatal breakpoint fires.
 * Confidence: high */
static uint64_t sk_free_page(uint64_t p)
{
    if (p <= p + 0x10) {
        sk_x_0005d394(p, 1);
        return 0;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x539fc);
}

/* FUN_000539fc @ 0x000539fc   (sk_free_page2)
 * Ghidra: void FUN_000539fc(ulong param_1)
 * Releases a single page (void variant): after an overflow sanity check
 * (p+0x10 must not wrap) it hands p to sk_x_0005d394 with the free flag set (1).
 * On overflow the fatal breakpoint fires.
 * Confidence: high */
static void sk_free_page2(uint64_t p)
{
    if (p <= p + 0x10) {
        sk_x_0005d394(p, 1);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53a14);
}

/* FUN_00053a14 @ 0x00053a14   (sk_zero2)
 * Ghidra: undefined8 FUN_00053a14(undefined8 *param_1)
 * Zeroes two 8-byte words at p (p[0] and p[1]) after an overflow sanity check
 * (p+2 must not wrap) and returns 0. On overflow the fatal breakpoint fires.
 * Confidence: high */
static uint64_t sk_zero2(uint64_t *p)
{
    if (p <= p + 2) {
        p[0] = 0;
        p[1] = 0;
        return 0;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53a30);
}

/* FUN_00053a30 @ 0x00053a30   (sk_alloc_page)
 * Ghidra: undefined8 FUN_00053a30(ulong param_1)
 * Allocates a single page: after an overflow sanity check (p+0x10 must not wrap)
 * it hands p to sk_x_0005d394 with the alloc flag clear (0) and returns 0. On
 * overflow the fatal breakpoint fires.
 * Confidence: high */
static uint64_t sk_alloc_page(uint64_t p)
{
    if (p <= p + 0x10) {
        sk_x_0005d394(p, 0);
        return 0;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53a60);
}

/* FUN_00053a60 @ 0x00053a60   (sk_try_map)
 * Ghidra: undefined4 FUN_00053a60(ulong param_1,ulong param_2)
 * Attempts to map a pair of ranges: after overflow sanity checks on both a and b
 * (each +0x10 must not wrap) it asks sk_x_0005d38c whether the operation is
 * allowed, returning 4 when it fails (i.e. the operation was not permitted) and
 * 0 on success. On overflow the fatal breakpoint fires.
 * Confidence: high */
static uint32_t sk_try_map(uint64_t a, uint64_t b)
{
    int allowed;
    uint32_t result;

    if ((a <= a + 0x10) && (b <= b + 0x10)) {
        allowed = sk_x_0005d38c();
        result = 0;
        if (allowed == 0) {
            result = 4;
        }
        return result;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53aa0);
}

/* FUN_00053aa0 @ 0x00053aa0   (sk_noop)
 * Ghidra: void FUN_00053aa0(void)
 * A no-op stub; returns immediately.
 * Confidence: high */
static void sk_noop(void)
{
    return;
}

/* FUN_00053aa4 @ 0x00053aa4   (sk_zero2b)
 * Ghidra: undefined8 FUN_00053aa4(undefined8 *param_1,uint param_2)
 * Zeroes two 8-byte words at p (p[0] and p[1]) after an overflow sanity check
 * (p+2 must not wrap) and returns 0. When flags bit 1 is set (flags>>1 & 1), it
 * additionally notifies sk_x_0005cf08 with a 0x100-sized range. On overflow the
 * fatal breakpoint fires.
 * Confidence: high */
static uint64_t sk_zero2b(uint64_t *p, uint32_t flags)
{
    if (p <= p + 2) {
        p[0] = 0;
        p[1] = 0;
        if ((flags >> 1 & 1) != 0) {
            sk_x_0005cf08(p, 0x100);
        }
        return 0;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53ae0);
}

/* FUN_00053ae0 @ 0x00053ae0   (sk_cb)
 * Ghidra: void FUN_00053ae0(ulong param_1)
 * Callback wrapper: after an overflow sanity check (p+0x10 must not wrap) it
 * invokes sk_x_0005cb9c (no arguments) and returns. On overflow the fatal
 * breakpoint fires.
 * Confidence: high */
static void sk_cb(uint64_t p)
{
    if (p <= p + 0x10) {
        sk_x_0005cb9c();
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53af4);
}

/* FUN_00053af4 @ 0x00053af4   (sk_try3)
 * Ghidra: undefined4 FUN_00053af4(ulong param_1)
 * Attempts a three-way operation: after an overflow sanity check (p+0x10 must
 * not wrap) it asks sk_x_0005cdbc whether the operation is allowed, returning 3
 * when it fails (i.e. not permitted) and 0 on success. On overflow the fatal
 * breakpoint fires.
 * Confidence: high */
static uint32_t sk_try3(uint64_t p)
{
    int allowed;
    uint32_t result;

    if (p <= p + 0x10) {
        allowed = sk_x_0005cdbc();
        result = 0;
        if (allowed == 0) {
            result = 3;
        }
        return result;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53b28);
}

/* FUN_00053b28 @ 0x00053b28   (sk_cb2)
 * Ghidra: undefined8 FUN_00053b28(ulong param_1)
 * Callback wrapper: after an overflow sanity check (p+0x10 must not wrap) it
 * invokes sk_x_0005ce54 (no arguments) and returns 0. On overflow the fatal
 * breakpoint fires.
 * Confidence: high */
static uint64_t sk_cb2(uint64_t p)
{
    if (p <= p + 0x10) {
        sk_x_0005ce54();
        return 0;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x53b54);
}

/* FUN_00053db8 @ 0x00053db8   (sk_mmap)
 * Ghidra: undefined8 FUN_00053db8(ulong *param_1,ulong param_2,uint param_3,int param_4,
 *                                long *param_5,ulong param_6,uint param_7)
 * Maps a guest range of len bytes at addr. Validates extra (a {block, callback}
 * pair whose block must be 0 on entry), len <= 0x3e, a non-null out pointer and
 * flags bit 0 set, then builds a mapping attribute descriptor from prot (via a
 * per-prot table DAT_004bcce0), len and flags. Depending on the o flag bits it
 * either reuses the page supplied in *out or obtains a backing page from the
 * shared endpoint object (sk_ep_obj_get) and caches it in the global at
 * 0x6b0340. The endpoint "invoke" entry (vtable+0x30) performs the actual map;
 * on failure the status is translated through sk_mmap_err. On success the
 * callback in extra[1] is invoked, *out is set to the page, errno is cleared and
 * 1 is returned. Errors set errno (0x16 EINVAL) and return 0.
 * Confidence: medium
 * Notes: DAT_004bcce0 is the per-prot attribute table; DAT_0064cb40/48 with the
 * 0x64cb3f/0x64cb81 bounds delimit the endpoint monitor region checked before
 * sk_x_004b5ef8. The sk_ep_obj_get return is treated as a 16-byte descriptor
 * {ctx, vtable} filled into a local. sk_x_00054354(0) is noreturn. */
static uint64_t sk_mmap(uint64_t *out, uint64_t addr, uint32_t len, int prot, long *extra, uint64_t flags, uint32_t o)
{
    uint64_t page;                              /* uStack_88: backing page / result */
    uint64_t attrs;                             /* local_78: mapping attribute descriptor */
    uint64_t req;                               /* local_90: request descriptor */
    uint64_t rq2;                               /* local_70 */
    uint64_t lo;                                /* local_68 */
    uint64_t hi;                                /* local_60 */
    uint64_t stk;                               /* uStack_58 */
    uint8_t prot_byte;                          /* uVar11 */
    uint16_t saved16;                           /* uVar3 */
    uint32_t attr_hi;                           /* uVar2 */
    uint32_t acc;                               /* uVar13 */
    uint32_t extra_bits;                        /* uVar12 */
    uint64_t ep[2];                             /* auVar14: {ctx, vtable} from sk_ep_obj_get */
    uint64_t (*invoke)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
    uint8_t *b;
    uint64_t v;                                 /* uVar6 */
    uint64_t u8;                                /* uVar8 */
    uint8_t ok;                                 /* cVar5 */
    int *errno_ptr;

    page = 0;
    req = 0;
    rq2 = 0;
    hi = 0;
    lo = 0;
    stk = 0;
    attrs = 0;
    if ((((extra == (long *)0x0) || (0x3e < len)) || (out == (uint64_t *)0x0)) || ((flags & 1) == 0)) {
        goto fail_einval;
    }
    if (extra + 2 < extra) {
        goto overflow_brk;
    }
    if (*extra != 0) {
        goto fail_einval;
    }
    req = 0x11;
    if (prot - 1U < 6) {
        prot_byte = (uint8_t)*(uint32_t *)(0x4bcce0 + (uint64_t)(prot - 1U) * 4);
    }
    else {
        prot_byte = 2;
    }
    /* build attrs: 0x20000000 | (len & 0xff) << 16 | prot_byte */
    attrs = 0x20000000 | ((uint64_t)(len & 0xff) << 16) | (uint64_t)prot_byte;
    saved16 = (uint16_t)(attrs & 0xffff);       /* == prot_byte */
    /* local_80 = addr (kept) */

    if ((o >> 3 & 1) == 0) {
        acc = 0;
        attr_hi = (uint32_t)((attrs >> 16) & 0xffffff);
        attrs = ((uint64_t)attr_hi << 16) | ((uint64_t)(((o & 0x10) == 0) ? 1 : 0) << 8) | (uint64_t)prot_byte;
        if ((addr >> 0x1e == 0) && ((o & 0x10) == 0)) {
            attrs = ((uint64_t)attr_hi << 16) | (uint64_t)saved16;
            if (*(uint64_t *)0x6b0340 == 0) {
                hi = 0x4000;
                stk = 0x2000000102;
                rq2 = 0x11;
                lo = 0;
                { sk_ep_pair_t _p = sk_ep_obj_get(); ep[0]=_p.lo; ep[1]=_p.hi; }
                invoke = *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))(ep[1] + 0x30);
                v = invoke(ep[0], 8, (uint64_t)&rq2, 0x6b0330, 0, (uint64_t)&rq2);
                v = v & 0xff;
                if (v != 0) {
                    if ((((uint64_t)0x64cb3f < (uint64_t)0x64cb40 + v) &&
                         ((uint64_t)0x64cb48 + v < (uint64_t)0x64cb81)) &&
                        ((uint64_t)0x64cb40 + v <= (uint64_t)0x64cb48 + v)) {
                        sk_x_004b5ef8();
                    }
                    goto overflow_brk;
                }
                *(uint64_t *)0x6b0340 = lo;
            }
            acc = 0x20000;
            page = *(uint64_t *)0x6b0340;
        }
    }
    else {
        page = *out;
        acc = 1;
    }

    v = page;
    if ((o & 1) == 0) {
        goto fail_einval;
    }
    acc = (((uint32_t)flags & 2 | (uint32_t)(flags >> 2) & 1) << 3) | acc;
    if ((o >> 1 & 1) == 0) {
        acc = acc | 0x20;
    }
    else {
        if ((o >> 5 & 1) == 0) {
            extra_bits = 0x2010000;
        }
        else {
            b = (uint8_t *)sk_x_00054610();
            if (((*b & 1) == 0) && (u8 = sk_x_000640e4(), (u8 & 1) != 0)) {
                acc = acc | 0x10000;
                goto do_map;
            }
            extra_bits = 0x10020;
        }
        acc = acc | extra_bits;
    }
do_map:
    if (addr <= UINT64_MAX - v) {               /* !CARRY8(v, addr) */
        { sk_ep_pair_t _p = sk_ep_obj_get(); ep[0]=_p.lo; ep[1]=_p.hi; }
        invoke = *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))(ep[1] + 0x30);
        ok = (uint8_t)invoke(ep[0], acc | ((o & 4) << 0x14), (uint64_t)&req, (uint64_t)extra, 0, 0);
        if (ok != '\0') {
            return sk_mmap_err((int)ok);
        }
        if (extra[1] != 0) {
            ((void (*)(uint64_t, uint64_t))(extra[1] + 8))(*extra, (uint64_t)&req);
            *out = page;
            errno_ptr = (int *)sk_errno_ptr();
            *errno_ptr = 0;
            return 1;
        }
        /* WARNING: Subroutine does not return */
        sk_abort();
    }
fail_einval:
    errno_ptr = (int *)sk_errno_ptr();
    *errno_ptr = 0x16;
    return 0;
overflow_brk:
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x54030);
}

/* FUN_00054034 @ 0x00054034   (sk_mmap_err)
 * Ghidra: bool FUN_00054034(int param_1)
 * Translates a mapping error code into an errno value and stores it into the
 * current errno slot (sk_errno_ptr). The stored errno is 0x2d (ENOTSUP) when the
 * code is not 5 (EFAULT-like), 0x16 (EINVAL) otherwise; a zero code stores 0x0c
 * (EAGAIN-like). Returns whether the code was a "greater than 1" unsigned value
 * and zero, i.e. the caller-retry condition.
 * Confidence: medium
 * Notes: uVar1/uVar4/bVar2 track the errno selection; the unsigned 2U compare
 * drives the final predicate. */
static bool sk_mmap_err(int code)
{
    int err;        /* uVar4 */
    int v1;         /* uVar1 */
    bool gt1;       /* bVar2 */
    int *errno_ptr;

    err = 0x2d;
    if (code != 5) {
        err = 0x16;
    }
    v1 = 0;
    if (code != 0) {
        v1 = err;
    }
    gt1 = 1 < code - 2U;
    err = 0xc;
    if (gt1) {
        err = v1;
    }
    errno_ptr = (int *)sk_errno_ptr();
    *errno_ptr = err;
    return gt1 && code == 0;
}
/* FUN_00054094 @ 0x00054094   (sk_munmap)
 * Ghidra: undefined8 FUN_00054094(long param_1,long param_2,undefined1 (*param_3)[16])
 * Unmaps the memory range [a, a+b). Resolves the 16-byte (object, vtable)
 * descriptor covering 'a' from the current ep object (when no frame is
 * supplied) or from the caller's frame, then asks the region for its
 * described base/size via vtable[1]. If that range exactly matches the
 * requested range, it validates through vtable[0] and, on success, hands off
 * to the shared munmap core; on a clean validation it clears errno and
 * returns 1. When no region matches it returns 0 with errno set to 0x16
 * (EINVAL). A null vtable is fatal.
 * Confidence: high
 * Notes: FUN_00034a2c = sk_ep_obj_get (16-byte frame); thunk_FUN_0006037c =
 * sk_errno_ptr; FUN_00054354 = sk_abort (noreturn); FUN_00054034 is the
 * shared munmap core (external). */
static uint64_t sk_munmap(long a, long b, uint8_t (*frame)[16])
{
    typedef sk_ep_pair_t frame_t;
    frame_t f;
    uint64_t vtable;
    uint64_t obj;
    uint64_t reg[4];   /* region descriptor: base@[1], size@[2] */
    char ok;

    if (frame == 0) {
        f = sk_ep_obj_get();
        f = ((frame_t (*)(uint64_t, long, long, long))((char *)f.hi + 0x38))(f.lo, a, 0, 0);
    } else {
        f.lo = ((uint64_t *)frame)[0];
        f.hi = ((uint64_t *)frame)[1];
    }
    vtable = f.hi;
    obj = f.lo;
    reg[0] = 0;
    reg[1] = 0;
    reg[2] = 0;
    reg[3] = 0;

    if (obj != 0) {
        if (vtable == 0) {
            sk_abort();   /* noreturn */
        }
        ((void (*)(uint64_t, uint64_t *))((uint64_t *)vtable)[1])(obj, reg);
        if (reg[1] == (uint64_t)a && reg[2] == (uint64_t)b) {
            ok = ((char (*)(uint64_t))((uint64_t *)vtable)[0])(obj);
            if (ok != 0) {
                return sk_mmap_err(0);
            }
            *((int *)sk_errno_ptr()) = 0;
            return 1;
        }
    }
    *((int *)sk_errno_ptr()) = 0x16;
    return 0;
}

/* FUN_0005417c @ 0x0005417c   (sk_mprotect)
 * Ghidra: undefined8 FUN_0005417c(ulong param_1,ulong param_2,undefined1 (*param_3)[16],uint param_4)
 * Changes the protection of the range [a, a+b) on the region covering 'a'.
 * Resolves the 16-byte (object, vtable) descriptor from the current ep object
 * (or the caller's frame), reads the region base/size via vtable[1], and
 * rejects a request that is not contained in the region (errno 0x16) or a
 * cache-mode change the region does not support (errno 0x2d). With no cache
 * bits it applies the plain protection update through vtable+0x20/0x30,
 * verifying the updated offset/size match; with cache bits it first performs
 * the cache-mode transition through vtable+0x50 (gated on the global config
 * enabled flag and a supporting decision), then applies the plain update.
 * The result is forwarded to the shared mprotect core. A null vtable or a
 * partial plain update is fatal.
 * Confidence: medium
 * Notes: FUN_00034a2c = sk_ep_obj_get; thunk_FUN_0006037c = sk_errno_ptr;
 * FUN_00054610 = sk_global_cfg_get (config base; byte0 = enabled flag);
 * FUN_00054034 = shared mprotect core (external); FUN_004b5f30 and
 * FUN_00054354 (sk_abort) are noreturn; type propagation not settling. */
static uint64_t sk_mprotect(uint64_t a, uint64_t b, uint8_t (*frame)[16], uint32_t prot)
{
    typedef sk_ep_pair_t frame_t;
    frame_t f;
    uint64_t vtable;
    uint64_t obj;
    uint64_t st;        /* region-get status */
    uint64_t locals[5]; /* [0]=update offset in/out, [1..4]=region descriptor */
    uint64_t size_out;
    char ok;
    int d;              /* cache-mode support decision */
    uint64_t off;       /* aligned offset of range within region */
    uint64_t len;       /* aligned length of range */

    if (frame == 0) {
        f = sk_ep_obj_get();
        f = ((frame_t (*)(uint64_t, uint64_t, long, long))((char *)f.hi + 0x38))(f.lo, a, 0, 0);
    } else {
        f.lo = ((uint64_t *)frame)[0];
        f.hi = ((uint64_t *)frame)[1];
    }
    vtable = f.hi;
    obj = f.lo;
    locals[1] = 0;
    locals[2] = 0;
    locals[3] = 0;
    locals[4] = 0;

    if (obj == 0) {
        *((int *)sk_errno_ptr()) = 0x16;
        return 0;
    }
    if (vtable == 0) {
        sk_abort();   /* noreturn */
    }
    st = ((uint64_t (*)(uint64_t, uint64_t *))((uint64_t *)vtable)[1])(obj, &locals[1]);
    if ((a < locals[2]) || (locals[3] < b) ||
        (locals[3] + locals[2] <= a) || (locals[3] + locals[2] < b + a)) {
        *((int *)sk_errno_ptr()) = 0x16;
        return 0;
    }
    {
        off = (a - locals[2]) & 0xffffffffffffc000;
        len = ((b + 0x3fff + (a - locals[2])) & 0xffffffffffffc000) - off;
        if ((prot & 0xc) == 0) {
            goto plain_update;
        }
        if (((st >> 0x10) & 1) == 0) {
            *((int *)sk_errno_ptr()) = 0x2d;
            return 0;
        }
        ok = ((char (*)(uint64_t, uint64_t, uint64_t, uint64_t))
              ((uint64_t *)vtable)[0x50 >> 3])(obj, (prot >> 1) & 4, off, len);
        if ((*(uint8_t *)sk_global_cfg_get() & 1) == 0) {
            d = sk_x_000640e4();
        } else {
            d = 0;
        }
        if (ok == 0) {
            if ((prot & 4) == 0) {
                d = 1;
            }
            if (d == 0) {
                prot = 2;
            }
            goto plain_update;
        }
        return sk_x_00054034(ok);
    }
plain_update:
    if ((prot & 3) == 0) {
        ok = 0;
    } else {
        uint64_t vofs = (prot & 1) ? 0x30 : 0x20;
        locals[0] = off;
        size_out = len;
        ok = ((char (*)(uint64_t, uint64_t *, uint64_t *))
              ((uint64_t *)vtable)[vofs >> 3])(obj, &locals[0], &size_out);
        if (locals[0] != off || size_out != len) {
            sk_x_004b5f30();
            sk_abort();   /* noreturn */
        }
    }
    return sk_x_00054034(ok);
}

/* FUN_00054354 @ 0x00054354   (sk_abort)
 * Ghidra: void FUN_00054354(void)
 * Fatal abort: tries to take the lock identified by the magic value
 * 0xeb1a02bf914012ba, logs the "abort() called" message (0x3d) with the
 * current context, re-acquires the lock if it was not already held, and
 * raises the fatal breakpoint via sk_panic_brk. Never returns.
 * Confidence: high
 * Notes: thunk_FUN_000544d0 = sk_lock_try, thunk_FUN_0005453c =
 * sk_lock_acquire (both in this chunk); FUN_0005b190 = sk_panic_brk (noreturn);
 * string s_abort___called_005bbede. */
static void sk_abort(void)
{
    int held;
    uint64_t ctx;

    held = sk_lock_try(0xeb1a02bf914012ba);
    ctx = sk_x_00060524();
    sk_x_00062474(sk_str_abort___called_005bbede, 0x3d, 0xeb1a02bf914012ba, ctx, 1, 0, 0, 0);
    if (held == 0) {
        sk_lock_acquire(0xeb1a02bf914012ba);
    }
    sk_panic_brk(ctx, sk_str_abort___called_005bbede);   /* noreturn */
}

/* FUN_000543c4 @ 0x000543c4   (sk_log_abort)
 * Ghidra: void FUN_000543c4(undefined8 param_1)
 * Logs the abort condition for the value a against the magic lock identifier,
 * passing the caller's stack pointer, then performs the fatal abort. Never
 * returns.
 * Confidence: high
 * Notes: FUN_00118c38 is the logging helper (external); FUN_00054354 =
 * sk_abort (noreturn). */
static void sk_log_abort(uint64_t a)
{
    uint64_t dummy;

    sk_x_00118c38(0xeb1a02bf914012ba, a, &dummy);
    sk_abort();   /* noreturn */
}

/* FUN_000543f4 @ 0x000543f4   (sk_panic2)
 * Ghidra: void FUN_000543f4(undefined8 param_1,undefined8 param_2)
 * Two-argument fatal panic: raises the panic with the two values a and b.
 * Never returns.
 * Confidence: high
 * Notes: FUN_0005b1b0 = sk_x_0005b1b0 (noreturn panic helper). */
static void sk_panic2(uint64_t a, uint64_t b)
{
    sk_x_0005b1b0(0, a, b);   /* noreturn */
}

/* FUN_00054414 @ 0x00054414   (sk_prng_fill)
 * Ghidra: void FUN_00054414(long param_1,ulong param_2)
 * Fills n bytes at dst from the 128-bit xorshift PRNG state, emitting up to 8
 * bytes per step derived from the old first state word. The two state words
 * are advanced with a xorshift/xorshift64 mixed update on every step. When
 * all n bytes are written it verifies the stack canary and returns; a
 * destination-address wrap (overflow) is fatal and aborts via software
 * breakpoint. Persistent state lives in two function-local statics (the
 * global _DAT_006bf5b0 / _DAT_006bf5b8 words).
 * Confidence: high
 * Notes: FUN_00117cc4 = sk_memcpy, FUN_0011d7e8 = sk_stack_chk_fail;
 * canary -0x2c8502b44bfffed6; SoftwareBreakpoint(0x5519,0x116d5c) is noreturn. */
static void sk_prng_fill(long dst, uint64_t n)
{
    static uint64_t prng_a = 0;  /* _DAT_006bf5b0 */
    static uint64_t prng_b = 0;  /* _DAT_006bf5b8 */
    uint64_t off;    /* accumulated offset into dst (uVar5) */
    uint64_t chunk;  /* bytes to write this iteration (uVar2) */
    uint64_t mul5;
    uint64_t mul640;
    uint64_t out;
    uint64_t base;
    uint64_t canary;

    canary = -0x2c8502b44bfffed6;
    off = 0;
    for (;;) {
        chunk = n - off;
        if (n < off || chunk == 0) {
            if (canary == -0x2c8502b44bfffed6) {
                return;
            }
            sk_stack_chk_fail();   /* noreturn */
        }
        mul5 = prng_a * 5;
        mul640 = prng_a * 0x280;
        prng_b = prng_b ^ prng_a;
        prng_a = (prng_a >> 0x28 | prng_a << 0x18) ^ (prng_b << 0x10) ^ prng_b;
        prng_b = prng_b >> 0x1b | prng_b << 0x25;
        out = (mul5 >> 0x39 | mul640) * 9;
        if (chunk > 7) {
            chunk = 8;
        }
        base = (uint64_t)dst + off;
        sk_memcpy(base, &out, chunk);
        if (base + chunk < base) {
            break;
        }
        off = chunk + off;
    }
    SoftwareBreakpoint(0x5519, 0x116d5c); /* noreturn */
}

/* FUN_00054418 @ 0x00054418   (sk_ptr_tag)
 * Ghidra: ulong FUN_00054418(ulong param_1)
 * Reconstructs a tagged pointer for p: resolves the symbol whose address
 * matches p (the resolved address is returned in the in/out local), and forms
 * the high 16 tag bits from the symbol's tag field at +0x40 (or the all-ones
 * tag 0xffff when the symbol is not found). The low 48 bits of the returned
 * pointer come from the resolved address, preserving the address's tag.
 * Confidence: high
 * Notes: FUN_0005bc48 = sk_x_0005bc48 (symbol lookup, in/out address). */
static uint64_t sk_ptr_tag(uint64_t p)
{
    uint64_t addr;
    uint64_t sym;
    uint64_t tag;

    addr = p;
    sym = sk_x_0005bc48(&addr, 0);
    if (sym == 0) {
        tag = 0xffff000000000000;
    } else {
        tag = (uint64_t)*(uint16_t *)(sym + 0x40) << 0x30;
    }
    return (addr & 0xffffffffffff) | tag;
}

/* FUN_00054464 @ 0x00054464   (sk_lock_release)
 * Ghidra: void FUN_00054464(long param_1)
 * Releases the lock descriptor p. For the two special magic lock identifiers
 * it uses the privileged release path (when the magic lock is active),
 * otherwise the ordinary release path, both operating on the underlying lock
 * stored at p+0x58. No return value.
 * Confidence: high
 * Notes: magics -0x14e5fd406ebfed46 / -0x55e9fc042d7fffe4; FUN_00060524 is
 * the current-context getter. */
static void sk_lock_release(long p)
{
    uint64_t ctx;

    ctx = sk_x_00060524();
    if ((p == -0x14e5fd406ebfed46 || p == -0x55e9fc042d7fffe4) &&
        (sk_x_00062848() != 0)) {
        sk_x_0006285c(ctx, *(uint64_t *)(p + 0x58));
        return;
    }
    sk_x_00118164(*(uint64_t *)(p + 0x58));
    return;
}

/* FUN_000544d0 @ 0x000544d0   (sk_lock_try)
 * Ghidra: ulong FUN_000544d0(long param_1)
 * Attempts a non-blocking acquire of the lock descriptor p. For the two
 * special magic lock identifiers it uses the privileged try path when the
 * magic lock is active; otherwise the ordinary try path. Returns nonzero when
 * the lock was acquired, zero otherwise.
 * Confidence: high
 * Notes: magics -0x14e5fd406ebfed46 / -0x55e9fc042d7fffe4; FUN_00060524 is
 * the current-context getter. */
static uint64_t sk_lock_try(long p)
{
    uint64_t ctx;
    uint64_t r;

    ctx = sk_x_00060524();
    if ((p == -0x14e5fd406ebfed46 || p == -0x55e9fc042d7fffe4) &&
        (sk_x_00062848() != 0)) {
        r = sk_x_000628d8(ctx, *(uint64_t *)(p + 0x58));
    } else {
        r = (uint64_t)(sk_x_0011817c(*(uint64_t *)(p + 0x58)) != 0);
    }
    return r;
}

/* FUN_0005453c @ 0x0005453c   (sk_lock_acquire)
 * Ghidra: void FUN_0005453c(long param_1)
 * Acquires the lock descriptor p, blocking as needed. For the two special
 * magic lock identifiers it uses the privileged acquire path when the magic
 * lock is active; otherwise the ordinary acquire path. No return value.
 * Confidence: high
 * Notes: magics -0x14e5fd406ebfed46 / -0x55e9fc042d7fffe4; FUN_00060524 is
 * the current-context getter. */
static void sk_lock_acquire(long p)
{
    uint64_t ctx;

    ctx = sk_x_00060524();
    if ((p == -0x14e5fd406ebfed46 || p == -0x55e9fc042d7fffe4) &&
        (sk_x_00062848() != 0)) {
        sk_x_000628e0(ctx, *(uint64_t *)(p + 0x58));
        return;
    }
    sk_x_00118194(*(uint64_t *)(p + 0x58));
    return;
}

/* FUN_000545a8 @ 0x000545a8   (sk_lock_init)
 * Ghidra: void FUN_000545a8(int param_1)
 * Initializes the four lock tables at 0x6ad700/0x6ad710/0x6ad720/0x6ad730
 * with a size of 2 entries each. When the flag is nonzero it first clears the
 * two lock-state globals at 0x64cd88 and 0x64cee8. No return value.
 * Confidence: high
 * Notes: FUN_00118148 is the lock-table initializer; the two cleared globals
 * are read-only image addresses (uRam000000000064cd88/64cee8). */
static void sk_lock_init(int flag)
{
    if (flag != 0) {
        sk_g_0064cd88 = 0;   /* data global @ 0x64cd88 */
        sk_g_0064cee8 = 0;   /* data global @ 0x64cee8 */
    }
    sk_x_00118148(0x6ad700, 2);
    sk_x_00118148(0x6ad710, 2);
    sk_x_00118148(0x6ad720, 2);
    sk_x_00118148(0x6ad730, 2);
    return;
}

/* FUN_00054610 @ 0x00054610   (sk_global_cfg_get)
 * Ghidra: void FUN_00054610(void)
 * Returns the base pointer of the global configuration structure by reading
 * the configuration-pointer slot at 0x6b04a8 through the shared getter.
 * (The decompiler reports a void return; the value is delivered in x0 and
 * used as a pointer by callers, so it is returned here per the contract.)
 * Confidence: high
 * Notes: FUN_0005acac = sk_x_0005acac (global getter, kind 2). */
static uint64_t sk_global_cfg_get(void)
{
    return sk_x_0005acac(0x6b04a8, 2, 2);
}

/* FUN_00054624 @ 0x00054624   (sk_cfg_init)
 * Ghidra: undefined1 * FUN_00054624(long param_1)
 * Parses the boot-time configuration parameter table at 'params' (a packed
 * array of 16-byte (tag, value) records up to 0x400 bytes) into the global
 * configuration structure (base from sk_global_cfg_get; DAT_006b0348 is the
 * first field). Each tag stores its value at a fixed config offset; unknown or
 * reserved tags are skipped; tag 0x16 captures the handler-table address, and
 * tag 0x17 seeds the per-record count used in the wrap check. After the loop
 * it records the params source, validates that the handler table does not
 * wrap (fatal otherwise), publishes the params and self pointers to the two
 * global slots, and returns the config base.
 * Confidence: medium
 * Notes: reads/writes the DAT_006b03xx config fields via the
 * sk_global_cfg_get() base; sk_g_0064ccd0/sk_g_0064ccf0 are the published
 * global slots; FUN_0005ba5c = sk_x_0005ba5c; SoftwareBreakpoint(0x5519,
 * 0x548b4) is noreturn. */
static uint8_t *sk_cfg_init(long params)
{
    uint64_t *cfg;       /* config base = &DAT_006b0348 */
    uint64_t handlers;   /* tag 0x16: handler-table address */
    long idx;
    long tag;
    uint64_t val;

    idx = 0;
    handlers = 0;
    cfg = (uint64_t *)sk_global_cfg_get();
    cfg[0xc8 / 8] = 0;          /* _DAT_006b0410 @ +0xc8 */
    cfg[0x100 / 8] = 0x400;     /* _DAT_006b0448 @ +0x100 */
    do {
        tag = *(long *)(params + idx);
        if ((uint64_t)(tag - 1) < 0x2b) {
            val = ((long *)(params + idx))[1];
            switch (tag) {
            default:
                cfg[0x8 / 8] = val;              /* +0x8  */
                break;
            case 2:
                cfg[0x10 / 8] = val;             /* +0x10 */
                break;
            case 3:
                cfg[0x18 / 8] = val;             /* +0x18 */
                break;
            case 4:
            case 5:
            case 6:
            case 10:
            case 0xb:
            case 0xd:
            case 0x19:
                break;
            case 7:
                cfg[0x58 / 8] = val;             /* +0x58 */
                break;
            case 8:
                cfg[0x60 / 8] = val;             /* +0x60 */
                break;
            case 9:
                cfg[0x68 / 8] = val;             /* +0x68 */
                break;
            case 0xc:
                cfg[0x70 / 8] = val;             /* +0x70 */
                break;
            case 0xe:
                cfg[0x90 / 8] = val;             /* +0x90 */
                break;
            case 0xf:
                cfg[0x98 / 8] = val;             /* +0x98 */
                break;
            case 0x10:
                cfg[0xa0 / 8] = val;             /* +0xa0 */
                break;
            case 0x11:
                cfg[0xa8 / 8] = val;             /* +0xa8 */
                break;
            case 0x12:
                cfg[0xb0 / 8] = val;             /* +0xb0 */
                break;
            case 0x13:
                cfg[0x78 / 8] = val;             /* +0x78 */
                break;
            case 0x14:
                cfg[0x80 / 8] = val;             /* +0x80 */
                break;
            case 0x15:
                cfg[0] = (val == 0);             /* +0   (bool) */
                cfg[0xb8 / 8] = val;             /* +0xb8 */
                break;
            case 0x16:
                handlers = val;
                break;
            case 0x17:
                cfg[0xc8 / 8] = val;             /* +0xc8 */
                break;
            case 0x18:
                *((uint8_t *)cfg + 0xd8) = (uint8_t)val;  /* +0xd8 (byte) */
                break;
            case 0x1a:
                cfg[0xe0 / 8] = val;             /* +0xe0 */
                break;
            case 0x1b:
                cfg[0xe8 / 8] = val;             /* +0xe8 */
                break;
            case 0x1c:
                cfg[0xf0 / 8] = val;             /* +0xf0 */
                break;
            case 0x1d:
                cfg[0x108 / 8] = val;            /* +0x108 (fallthrough) */
            case 0x1e:
                cfg[0x110 / 8] = val;            /* +0x110 */
                break;
            case 0x1f:
                cfg[0x118 / 8] = val;            /* +0x118 */
                break;
            case 0x20:
                cfg[0x88 / 8] = val;             /* +0x88 */
                break;
            case 0x21:
                cfg[0x120 / 8] = val;            /* +0x120 */
                break;
            case 0x22:
                cfg[0x128 / 8] = val;            /* +0x128 */
                break;
            case 0x23:
                cfg[0x130 / 8] = val;            /* +0x130 */
                break;
            case 0x24:
                cfg[0x138 / 8] = val;            /* +0x138 */
                break;
            case 0x25:
                cfg[0x140 / 8] = val;            /* +0x140 */
                break;
            case 0x26:
                cfg[0x148 / 8] = val;            /* +0x148 */
                break;
            case 0x27:
                cfg[0xd0 / 8] = val;             /* +0xd0 */
                break;
            case 0x28:
                cfg[0x30 / 8] = val;             /* +0x30 */
                break;
            case 0x29:
                cfg[0x40 / 8] = val;             /* +0x40 */
                break;
            case 0x2a:
                cfg[0x150 / 8] = val;            /* +0x150 */
                break;
            case 0x2b:
                cfg[0x158 / 8] = val;            /* +0x158 */
                break;
            }
        }
        idx += 0x10;
    } while (idx != 0x400);

    cfg[0xf8 / 8] = (uint64_t)params;           /* _DAT_006b0440 @ +0xf8 */
    if (handlers != 0 &&
        (handlers + cfg[0xc8 / 8] * 0x78 < handlers + 0x78 ||
         handlers + 0x78 < handlers)) {
        SoftwareBreakpoint(0x5519, 0x548b4); /* noreturn */
    }
    sk_g_0064ccd0 = (uint64_t)params;           /* data global @ 0x64ccd0 */
    cfg[0xc0 / 8] = handlers;                   /* _DAT_006b0408 @ +0xc0 */
    sk_x_0005ba5c(0x64ccb8);
    sk_g_0064ccf0 = (uint64_t)cfg;              /* data global @ 0x64ccf0 */
    sk_x_0005ba5c();
    return (uint8_t *)cfg;
}

/* FUN_00054960 @ 0x00054960   (sk_register_handler)
 * Ghidra: void FUN_00054960(undefined8 param_1)
 * Registers the handler described by p: unless the registration is already
 * present (sk_x_0005baac returns nonzero), it publishes p to the handler
 * global slot at 0x64cd10 and commits via sk_x_0005ba5c. No return value.
 * Confidence: high
 * Notes: sk_g_0064cd10 is the published global slot. */
static void sk_register_handler(uint64_t p)
{
    if (sk_x_0005baac(2, 6) != 0) {
        return;
    }
    sk_g_0064cd10 = p;   /* data global @ 0x64cd10 */
    sk_x_0005ba5c();
    return;
}

/* FUN_000549ac @ 0x000549ac   (sk_get_handler)
 * Ghidra: void FUN_000549ac(void)
 * Returns the current handler record base by reading the handler slot at
 * 0x6b04b0 through the shared getter. (The decompiler reports a void return;
 * the value is delivered in x0 and used as a pointer by callers, so it is
 * returned here per the contract.)
 * Confidence: high
 * Notes: FUN_0005acac = sk_x_0005acac (global getter, kind 2). */
static uint64_t sk_get_handler(void)
{
    return sk_x_0005acac(0x6b04b0, 2, 6);
}

/* FUN_000549c0 @ 0x000549c0   (sk_handler_iter)
 * Ghidra: void FUN_000549c0(ulong param_1,long param_2)
 * Iterates n handler records starting at base (each 0x78 bytes). For each
 * record whose flag word at +8 has bit 7 set it installs the record through
 * sk_handler_install with the fields from +0x38/+0x20/+0x50/+0x48, then
 * advances the shared cursor with sk_x_0005baf0. A record that falls outside
 * the [base, base+n*0x78) range (or wraps) is fatal.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x54a4c) is noreturn; the decompile shows
 * sk_handler_install called with 5 args (the 6th, stored at +8, is a stale
 * register here). */
static void sk_handler_iter(uint64_t base, long n)
{
    uint64_t p;

    if (n != 0) {
        p = base;
        do {
            if (p < base || base + (uint64_t)n * 0x78 < p + 0x78 || p + 0x78 < p) {
                SoftwareBreakpoint(0x5519, 0x54a4c); /* noreturn */
            }
            if (((*(uint64_t *)(p + 8) >> 7) & 1) != 0) {
                sk_handler_install((long)p, *(uint64_t *)(p + 0x38),
                                   (long)*(uint64_t *)(p + 0x20),
                                   *(uint64_t *)(p + 0x50), *(uint64_t *)(p + 0x48), 0);
            }
            sk_x_0005baf0(p);
            p += 0x78;
            n -= 1;
        } while (n != 0);
    }
    return;
}

/* FUN_00054a4c @ 0x00054a4c   (sk_handler_install)
 * Ghidra: void FUN_00054a4c(long param_1,undefined8 param_2,long param_3,
 *                           undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Fills the handler record 'rec' (0x78 bytes) from the handler descriptor
 * 'a': computes the symbol extent of a via sk_x_00051d3c/sk_x_00051dc0 and
 * decodes three fields via sk_x_00051ff4, then writes the record fields
 * (offsets +0x20..+0x70 and the flag at +8). The record's 16-byte payload at
 * +0x10 is copied from the descriptor's decoded extra region when present,
 * or zero-filled when absent; an out-of-range copy is fatal.
 * Confidence: high
 * Notes: FUN_00051d3c/FUN_00051dc0/FUN_00051ff4/FUN_00051fbc are external;
 * thunk_FUN_00114330 = sk_memset0, FUN_00117cc4 = sk_memcpy;
 * SoftwareBreakpoint(0x5519,0x54b1c) is noreturn. */
static void sk_handler_install(long rec, uint64_t a, long b, uint64_t c, uint64_t d, uint64_t e)
{
    long s0;
    long s1;
    uint64_t v0;
    uint64_t v1;
    long n0;
    uint64_t extra;

    s0 = sk_x_00051d3c(a);
    s1 = sk_x_00051dc0(a);
    v0 = 0;
    n0 = 0;
    v1 = 0;
    sk_x_00051ff4(a, &n0, &v0, &v1);
    *(uint64_t *)(rec + 0x48) = d;
    *(uint64_t *)(rec + 0x50) = c;
    *(long *)(rec + 0x20) = b;
    *(long *)(rec + 0x28) = s0 + b;
    *(long *)(rec + 0x30) = s1 - s0;
    *(uint64_t *)(rec + 0x38) = a;
    *(long *)(rec + 0x58) = n0;
    *(long *)(rec + 0x60) = n0 << 4;
    *(uint64_t *)(rec + 0x68) = v0;
    *(uint64_t *)(rec + 0x70) = v1;
    *(uint64_t *)(rec + 8) = e;
    extra = sk_x_00051fbc(a);
    if (extra == 0) {
        sk_memset0(rec + 0x10, 0x10);
    } else if (extra + 0x10 < extra ||
               (sk_memcpy(rec + 0x10, extra, 0x10), rec + 0x20 < rec + 0x10)) {
        SoftwareBreakpoint(0x5519, 0x54b1c); /* noreturn */
    }
    return;
}

/* FUN_00054b44 @ 0x00054b44   (sk_obj_init)
 * Ghidra: void FUN_00054b44(undefined8 *param_1,undefined8 param_2,undefined8 param_3,
 *                           undefined8 param_4,undefined8 param_5,undefined8 param_6,
 *                           undefined8 param_7,undefined8 param_8,undefined8 param_9)
 * Initializes the 15-element object at 'out' from the given fields: zeroes
 * the fixed slots, stores the value/type fields at their offsets, and copies
 * the 16-byte key/identity (a) into out[2..3]. A destination that does not
 * wrap past out[4] is a valid completion; otherwise it is fatal.
 * Confidence: medium
 * Notes: FUN_00117cc4 = sk_memcpy; SoftwareBreakpoint(0x5519,0x54ba8) is
 * noreturn. The contract signature carries one extra trailing parameter (i)
 * beyond the nine the decompile exposes; it is unused by the body. */
static void sk_obj_init(uint64_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                        uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t i)
{
    uint64_t *tmp;

    out[0] = 0;
    out[1] = h;
    out[3] = 0;
    out[5] = c;
    out[6] = d;
    out[7] = b;
    out[8] = 0;
    out[9] = g;
    out[10] = f;
    out[0xb] = 0;
    out[0xc] = 0;
    out[0xd] = 0;
    out[0xe] = 0;
    tmp = out + 2;
    tmp[0] = 0;
    out[4] = e;
    sk_memcpy(tmp, a, 0x10);
    if (tmp <= out + 4) {
        return;
    }
    SoftwareBreakpoint(0x5519, 0x54ba8); /* noreturn */
}

/* FUN_00054ba8 @ 0x00054ba8   (sk_obj_get38)
 * Ghidra: undefined8 FUN_00054ba8(void)
 * Returns the 8-byte field at offset +0x38 of the current object (sk_x_0005bb7c),
 * or 0 when there is no current object.
 * Confidence: high
 * Notes: FUN_0005bb7c = sk_x_0005bb7c (current object getter). */
static uint64_t sk_obj_get38(void)
{
    uint64_t rec;
    uint64_t v;

    rec = sk_x_0005bb7c();
    v = 0;
    if (rec != 0) {
        v = *(uint64_t *)(rec + 0x38);
    }
    return v;
}

/* FUN_00054bc8 @ 0x00054bc8   (sk_obj_get20)
 * Ghidra: undefined8 FUN_00054bc8(void)
 * Returns the 8-byte field at offset +0x20 of the current object (sk_x_0005bb7c),
 * or 0 when there is no current object.
 * Confidence: high
 * Notes: FUN_0005bb7c = sk_x_0005bb7c (current object getter). */
static uint64_t sk_obj_get20(void)
{
    uint64_t rec;
    uint64_t v;

    rec = sk_x_0005bb7c();
    v = 0;
    if (rec != 0) {
        v = *(uint64_t *)(rec + 0x20);
    }
    return v;
}
/* FUN_00054be8 @ 0x00054be8   (sk_sync)
 * Ghidra: void FUN_00054be8(void)
 * Serializes/fences outstanding state: acquires the memory range lock via
 * sk_x_0005b860 into a local and then releases/revalidates it through
 * sk_x_0005d154. If either step reports failure, or the returned range wraps
 * (unsigned overflow), it is a fatal condition and the sync aborts with a
 * software breakpoint (0x5519 at 0x54c2c). No inputs, no return value.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x54c2c) is noreturn. */
static void sk_sync(void)
{
    uint64_t lock;
    uint64_t st;

    lock = 0;
    st = sk_x_0005b860(&lock);
    if (((st != 0) ||
         (st = sk_x_0005d154(0, &lock), st != 0)) &&
        (st + lock < st || (st + lock) - st < lock)) {
        SoftwareBreakpoint(0x5519, 0x54c2c); /* noreturn */
    }
    return;
}

/* FUN_00054c3c @ 0x00054c3c   (sk_copy16)
 * Ghidra: void FUN_00054c3c(ulong param_1)
 * Copies 16 bytes into the location given by p. If the shared buffer handle
 * is null it zero-fills the destination with 16 bytes; otherwise it copies
 * the 16 bytes immediately following the handle. An out-of-range destination
 * (address-space wrap) is fatal and aborts via software breakpoint.
 * Confidence: high
 * Notes: thunk_FUN_00114330 = sk_memset0, FUN_00117cc4 = sk_memcpy;
 * SoftwareBreakpoint(0x5519,0x54c9c) is noreturn. */
static void sk_copy16(uint64_t p)
{
    uint64_t buf;

    buf = sk_x_0005bb7c();
    if (buf == 0) {
        sk_memset0(p, 0x10);
        return;
    }
    sk_memcpy(p, buf + 0x10, 0x10);
    if (p <= p + 0x10) {
        return;
    }
    SoftwareBreakpoint(0x5519, 0x54c9c); /* noreturn */
}

/* FUN_00054c9c @ 0x00054c9c   (sk_map_sym)
 * Ghidra: void FUN_00054c9c(undefined8 param_1,undefined8 param_2)
 * Maps a symbol by name: records the symbol name (a) into a local, looks it
 * up via sk_x_0005bc48, and if found invokes the mapping routine
 * sk_x_000520f0 with the resolved name, target (b), and the symbol's size
 * and value fields read from the lookup result. If the lookup fails
 * completely (result null, or the name-capacity field at +0x58 is below the
 * used field at +0x60>>4), the condition is fatal and aborts via breakpoint.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x54cfc) is noreturn. */
static void sk_map_sym(uint64_t a, uint64_t b)
{
    uint64_t sym_name;
    uint64_t sym;

    sym_name = a;
    sym = sk_x_0005bc48(&sym_name, 1);
    if (sym != 0) {
        if (*(uint64_t *)(sym + 0x60) >> 4 < *(uint64_t *)(sym + 0x58)) {
            SoftwareBreakpoint(0x5519, 0x54cfc); /* noreturn */
        }
        sk_x_000520f0(sym_name, (uint64_t *)b, *(uint64_t *)(sym + 0x58),
                      *(uint64_t *)(sym + 0x68), *(uint64_t *)(sym + 0x70));
    }
    return;
}

/* FUN_00054cfc @ 0x00054cfc   (sk_get_tbplace)
 * Ghidra: ulong FUN_00054cfc(void)
 * Returns the "tbplace" (trace/table place) value for the current processor
 * context, or 0 if none is present. It checks the per-cpu idle flag via
 * sk_x_0004fe80 and a global via sk_x_0004ed48; then iterates the place
 * table using sk_x_0004eb44/sk_x_0004eb4c, and for the entry whose type is
 * 0x19 (0x4e88c) extracts the 8-byte place token from the entry's payload
 * (via sk_x_0004e7b8) and returns it packed little-endian. A wrapping
 * address in the global or the entry is fatal (software breakpoint).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x54de4) is noreturn. */
static uint64_t sk_get_tbplace(void)
{
    uint64_t place;
    uint64_t entry;
    uint8_t *payload;
    uint8_t place_buf[16];

    if (sk_x_0004fe80() != 0) {
        place = sk_x_0004ed48();
        if ((place != 0) && (place + 8 < place)) {
            SoftwareBreakpoint(0x5519, 0x54de4); /* noreturn */
        }
        sk_x_0004eb44(place_buf);
        entry = sk_x_0004eb4c(place_buf);
        while (entry != 0) {
            if (entry + 0xc < entry) {
                SoftwareBreakpoint(0x5519, 0x54de4); /* noreturn */
            }
            if (sk_x_0004e88c(entry) == 0x19) {
                payload = (uint8_t *)sk_x_0004e7b8(entry, 0);
                if (payload != (uint8_t *)0x0) {
                    return (uint64_t)payload[0] |
                           (uint64_t)payload[1] << 8 |
                           (uint64_t)payload[2] << 0x10 |
                           (uint64_t)payload[3] << 0x18 |
                           (uint64_t)payload[4] << 0x20 |
                           (uint64_t)payload[5] << 0x28 |
                           (uint64_t)payload[6] << 0x30 |
                           (uint64_t)payload[14] << 0x38;
                }
            }
            entry = sk_x_0004eb4c(place_buf);
        }
    }
    return 0;
}

/* FUN_00054de4 @ 0x00054de4   (sk_noop0)
 * Ghidra: undefined8 FUN_00054de4(void)
 * Trivial no-op that always returns 0. Present as a placeholder handler.
 * Confidence: high
 * Notes: none. */
static uint64_t sk_noop0(void)
{
    return 0;
}

/* FUN_00054dec @ 0x00054dec   (sk_read)
 * Ghidra: void FUN_00054dec(void)
 * Reads a 16-byte record from the transport: on success it passes the two
 * 8-byte halves to sk_x_00116c20 and returns once the stack canary is
 * verified intact; on a short read it calls the fatal-error helper
 * sk_x_004b5fa8. A corrupted stack canary trips sk_stack_chk_fail.
 * Confidence: high
 * Notes: FUN_0011d7e8 = sk_stack_chk_fail (noreturn); canary
 * -0x2c8502b44bfffed6. */
static void sk_read(void)
{
    uint64_t lo;
    uint64_t hi;
    uint64_t canary;

    canary = -0x2c8502b44bfffed6;
    if (sk_x_0005c278(&lo, 0x10) == 0x10) {
        sk_x_00116c20(lo, hi);
        if (canary == -0x2c8502b44bfffed6) {
            return;
        }
    }
    else {
        sk_x_004b5fa8();
    }
    sk_stack_chk_fail(); /* noreturn */
}

/* FUN_00054e54 @ 0x00054e54   (sk_putc)
 * Ghidra: long FUN_00054e54(long param_1,char *param_2,long param_3)
 * Writes n bytes from buf to the target stream identified by fd. When the
 * stream is the special 0x64d038 register file and per-char flush (via
 * sk_x_00055b44) succeeds, the byte is loaded into the caller-saved
 * TPIDRRO_EL0 register block (8-byte value plus extension bytes) and a
 * supervisor call flushes it; otherwise the register block is zeroed before
 * the supervisor flush. All other streams are written to the 0x64cd78
 * sink. Returns n.
 * Confidence: medium
 * Notes: tpidrro_el0 holds a per-cpu register block; CallSupervisor(0)
 * performs the flush; SoftwareBreakpoint(0x5519,0x55164) is noreturn. */
static long sk_putc(long fd, char *buf, long n)
{
    uint8_t *regs;
    uint8_t *src;
    uint8_t v;
    uint8_t sign;
    uint8_t saved_b, saved_9, saved_bx, saved_ax, saved_f, saved_e;
    uint16_t saved_ef;
    uint64_t flusher;
    long flush_lo;
    long i;
    long fl;
    struct { uint64_t lo; uint64_t hi; } fc;

    if ((fd != 0x64cd78) || (fl = sk_x_0004cdc0(buf, n), fl != 0)) {
        fc.lo = sk_x_000533ec();
        fc.hi = 0;
        flusher = fc.hi;
        flush_lo = fc.lo;
        regs = (uint8_t *)tpidrro_el0;
        saved_9 = regs[9];
        saved_b = regs[8];
        saved_bx = regs[0xb];
        saved_ax = regs[10];
        saved_ef = *(uint16_t *)(regs + 0xc);
        saved_f = regs[0xf];
        saved_e = regs[0xe];
        if (n != 0) {
            i = 0;
            do {
                if ((fd == 0x64d038) && (fl = sk_x_00055b44(flush_lo, flusher), fl != 0)) {
                    flusher = sk_x_00055b44();
                    src = buf + i;
                    if ((buf + n <= src) || (src < buf)) {
                        SoftwareBreakpoint(0x5519, 0x55164); /* noreturn */
                    }
                    v = *src;
                    regs[0] = (uint8_t)flusher;
                    regs[5] = (uint8_t)((uint64_t)flusher >> 0x28);
                    regs[3] = (uint8_t)((uint64_t)flusher >> 0x18);
                    regs[2] = (uint8_t)((uint64_t)flusher >> 0x10);
                    regs[1] = (uint8_t)((uint64_t)flusher >> 8);
                    regs[4] = (uint8_t)((uint64_t)flusher >> 0x20);
                    regs[7] = (uint8_t)((uint64_t)flusher >> 0x38);
                    regs[6] = (uint8_t)((uint64_t)flusher >> 0x30);
                    sign = (uint8_t)(v >> 7);
                    regs[0xd] = sign;
                    regs[8] = v;
                    regs[0xb] = sign;
                    regs[10] = sign;
                    regs[9] = sign;
                    regs[0xc] = sign;
                    regs[0xf] = (uint8_t)(v >> 7);
                    regs[0xe] = sign;
                    do {
                        CallSupervisor(0);
                        regs[0] = (uint8_t)flusher;
                        regs[5] = (uint8_t)((uint64_t)flusher >> 0x28);
                        regs[3] = (uint8_t)((uint64_t)flusher >> 0x18);
                        regs[2] = (uint8_t)((uint64_t)flusher >> 0x10);
                        regs[1] = (uint8_t)((uint64_t)flusher >> 8);
                        regs[4] = (uint8_t)((uint64_t)flusher >> 0x20);
                        regs[7] = (uint8_t)((uint64_t)flusher >> 0x38);
                        regs[6] = (uint8_t)((uint64_t)flusher >> 0x30);
                    } while (flush_lo == 1);
                }
                else {
                    src = buf + i;
                    if ((buf + n <= src) || (src < buf)) {
                        SoftwareBreakpoint(0x5519, 0x55164); /* noreturn */
                    }
                    v = *src;
                    regs[5] = 0;
                    regs[3] = 0;
                    regs[2] = 0;
                    regs[1] = 0;
                    regs[4] = 0;
                    regs[0] = 0;
                    regs[7] = 0;
                    regs[6] = 0;
                    sign = (uint8_t)(v >> 7);
                    regs[0xd] = sign;
                    regs[8] = v;
                    regs[0xb] = sign;
                    regs[10] = sign;
                    regs[9] = sign;
                    regs[0xc] = sign;
                    regs[0xf] = (uint8_t)(v >> 7);
                    regs[0xe] = sign;
                    do {
                        CallSupervisor(0);
                        regs[0] = 0;
                        regs[5] = 0;
                        regs[3] = 0;
                        regs[2] = 0;
                        regs[1] = 0;
                        regs[4] = 0;
                        regs[7] = 0;
                        regs[6] = 0;
                    } while (flush_lo == 1);
                }
                flusher = 0;
                i = i + 1;
            } while (i != n);
        }
        regs[8] = saved_b;
        regs[0xd] = (uint8_t)((uint16_t)saved_ef >> 8);
        regs[0xb] = saved_bx;
        regs[10] = saved_ax;
        regs[9] = saved_9;
        regs[0xc] = (uint8_t)saved_ef;
        regs[0xf] = saved_f;
        regs[0xe] = saved_e;
    }
    return n;
}

/* FUN_00055164 @ 0x00055164   (sk_handler_check)
 * Ghidra: void FUN_00055164(undefined8 param_1)
 * Validates that the given handler (p) is registered for every opcode in the
 * 0x6ad740 dispatch table by checking, for each of the 11 opcode ranges
 * (sk_x_00055b7c, sk_x_00056098, sk_x_0005680c, sk_x_00056f84, sk_x_00057708,
 * sk_x_00057e8c, sk_x_0005860c, sk_x_00058d8c, sk_x_0005950c, sk_x_00059c8c,
 * sk_x_0005a40c), that the low bit of the returned status is clear. If any
 * check fails it is a fatal misconfiguration (software breakpoint). On
 * success it tears down the table with sk_x_00054960.
 * Confidence: high
 * Notes: SoftwareBreakpoint(1,0x5526c) is noreturn; each check returns a
 * status whose bit 0 marks failure. */
static void sk_handler_check(uint64_t p)
{
    uint64_t st;

    st = sk_x_00055b7c(p, 0x6ad740);
    if (((((((st & 1) == 0) && (st = sk_x_00056098(p, 0x6ad740), (st & 1) == 0)) &&
          (st = sk_x_0005680c(p, 0x6ad740), (st & 1) == 0)) &&
         ((st = sk_x_00056f84(p, 0x6ad740), (st & 1) == 0 &&
          (st = sk_x_00057708(p, 0x6ad740), (st & 1) == 0)))) &&
        ((st = sk_x_00057e8c(p, 0x6ad740), (st & 1) == 0 &&
         ((st = sk_x_0005860c(p, 0x6ad740), (st & 1) == 0 &&
          (st = sk_x_00058d8c(p, 0x6ad740), (st & 1) == 0)))))) &&
       ((st = sk_x_0005950c(p, 0x6ad740), (st & 1) == 0 &&
        ((st = sk_x_00059c8c(p, 0x6ad740), (st & 1) == 0 &&
         (st = sk_x_0005a40c(p, 0x6ad740), (st & 1) == 0)))))) {
        SoftwareBreakpoint(1, 0x5526c); /* noreturn */
    }
    sk_x_00054960(0x6ad740);
    return;
}

/* FUN_0005526c @ 0x0005526c   (sk_h_get8)
 * Ghidra: undefined8 FUN_0005526c(void)
 * Reads the 8-byte value at offset +8 of the current handler record
 * (sk_x_000549ac).
 * Confidence: high
 * Notes: none. */
static uint64_t sk_h_get8(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint64_t *)(rec + 8);
}

/* FUN_00055288 @ 0x00055288   (sk_h_get10)
 * Ghidra: undefined8 FUN_00055288(void)
 * Reads the 8-byte value at offset +0x10 of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint64_t sk_h_get10(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint64_t *)(rec + 0x10);
}

/* FUN_000552a4 @ 0x000552a4   (sk_h_get20)
 * Ghidra: undefined1 FUN_000552a4(void)
 * Reads the byte at offset +0x20 of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint8_t sk_h_get20(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint8_t *)(rec + 0x20);
}

/* FUN_000552c0 @ 0x000552c0   (sk_h_call28)
 * Ghidra: void FUN_000552c0(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Invokes the handler callback stored at offset +0x28 of the current handler
 * record, passing a, b, c through.
 * Confidence: high
 * Notes: decompiler could not recover the indirect-jump table at 0x55308. */
static void sk_h_call28(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    (*(void (**)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(rec + 0x28)))(a, b, c);
    return;
}

/* FUN_0005530c @ 0x0005530c   (sk_h_get30)
 * Ghidra: undefined1 FUN_0005530c(void)
 * Reads the byte at offset +0x30 of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint8_t sk_h_get30(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint8_t *)(rec + 0x30);
}

/* FUN_00055328 @ 0x00055328   (sk_h_get38)
 * Ghidra: undefined1 FUN_00055328(void)
 * Reads the byte at offset +0x38 of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint8_t sk_h_get38(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint8_t *)(rec + 0x38);
}

/* FUN_00055344 @ 0x00055344   (sk_h_get39)
 * Ghidra: undefined1 FUN_00055344(void)
 * Reads the byte at offset +0x39 of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint8_t sk_h_get39(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint8_t *)(rec + 0x39);
}

/* FUN_00055360 @ 0x00055360   (sk_h_get3a)
 * Ghidra: undefined1 FUN_00055360(void)
 * Reads the byte at offset +0x3a of the current handler record.
 * Confidence: high
 * Notes: none. */
static uint8_t sk_h_get3a(void)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    return *(uint8_t *)(rec + 0x3a);
}

/* FUN_0005537c @ 0x0005537c   (sk_h_call40)
 * Ghidra: void FUN_0005537c(undefined8 param_1)
 * Invokes the handler callback stored at offset +0x40 of the current handler
 * record, passing a through.
 * Confidence: high
 * Notes: decompiler could not recover the indirect-jump table at 0x553ac. */
static void sk_h_call40(uint64_t a)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    (*(void (**)(uint64_t))(*(uint64_t *)(rec + 0x40)))(a);
    return;
}

/* FUN_000553b0 @ 0x000553b0   (sk_h_call48)
 * Ghidra: void FUN_000553b0(undefined8 param_1)
 * Invokes the handler callback stored at offset +0x48 of the current handler
 * record, passing a through.
 * Confidence: high
 * Notes: decompiler could not recover the indirect-jump table at 0x553e0. */
static void sk_h_call48(uint64_t a)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    (*(void (**)(uint64_t))(*(uint64_t *)(rec + 0x48)))(a);
    return;
}

/* FUN_000553e4 @ 0x000553e4   (sk_h_call50)
 * Ghidra: void FUN_000553e4(undefined8 param_1,undefined8 param_2)
 * Invokes the handler callback stored at offset +0x50 of the current handler
 * record, passing a and b through.
 * Confidence: high
 * Notes: decompiler could not recover the indirect-jump table at 0x5541c. */
static void sk_h_call50(uint64_t a, uint64_t b)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    (*(void (**)(uint64_t, uint64_t))(*(uint64_t *)(rec + 0x50)))(a, b);
    return;
}

/* FUN_00055420 @ 0x00055420   (sk_h_call58)
 * Ghidra: void FUN_00055420(undefined8 param_1)
 * Invokes the handler callback stored at offset +0x58 of the current handler
 * record, passing a through.
 * Confidence: high
 * Notes: decompiler could not recover the indirect-jump table at 0x55450. */
static void sk_h_call58(uint64_t a)
{
    uint64_t rec;

    rec = sk_x_000549ac();
    (*(void (**)(uint64_t))(*(uint64_t *)(rec + 0x58)))(a);
    return;
}
