/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 14: 0x6a468-0x6d52c — the cbootinfo / IPMM (launcher IP Memory
 * Manager) bootstrap region.
 *
 * This region contains: the launcher IPMM physical-memory manager (freelist
 * construction, frame allocation by type, freed-frame recycling, zero-frame
 * mapping), the cbootinfo bootstrap parser (walking the boot capability
 * array, DART/TEXT/DATA/untyped-region discovery, launcher roottask slide),
 * the cbootinfo allocation arena, the vspace-table client registry, the
 * cL4 L4_ErrorCode string tables, and a block of Swift runtime thunks
 * (DeviceTreeKit, Swift.NativeDictionary) that are linked into the kernel.
 *
 * Names use seL4/cL4 vocabulary (cap, CNode, untyped region, launcher, vspace,
 * DART, roottask). All names are estimates unless string/header-matched.
 * Ghidra FUN_ identifiers are retained as the C symbol names (matching the
 * manifest ghidra_name); the estimated meaning lives in the header comment.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit value used for Ghidra's `undefined1[16]` returns (lo = bytes 0-7,
 * hi = bytes 8-15). */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;

/* Fatal path: Ghidra renders `pc = (code*)SoftwareBreakpoint(1,<addr>); (*pc)();`
 * as the kernel's abort/assert trap. */
#define SK_FATAL() __builtin_trap()

/* Stack canary value observed at the top of the large functions
 * (Ghidra local_38 = -0x2c8502b44bfffed6). */
#define SK_CANARY 0x2c8502b44bfffed6ull

/* ------------------------------------------------------------------ *
 * Out-of-region cL4 helpers referenced by this slice (FUN_ address in
 * the comment; bodies reconstructed by the sibling SK range workers that
 * own them). Signatures reflect the observed register usage.
 * ------------------------------------------------------------------ */
extern uint64_t CallSupervisor(uint64_t num);        /* SVC into cL4 (arg block at tpidrro_el0) */
extern uint64_t FUN_00002534(uint64_t obj, uint64_t meta);   /* Swift runtime object init */
extern void    *FUN_00010244(uint64_t size, uint64_t n, uint64_t tag); /* zone alloc */
extern uint64_t FUN_00027614(uint64_t obj, uint64_t meta);   /* Swift runtime object init */
extern sk_u128_t FUN_00034a2c(void);                 /* object+metaclass pair fetch */
extern uint64_t FUN_00051e5c(uint64_t image, const char *seg); /* mach segment lookup */
extern uint64_t FUN_000537c4(void);                  /* capability word build */
extern void    FUN_00054354(void);                   /* launcher fatal (noreturn) */
extern uint64_t FUN_000552a4(void);                  /* cap-type id fetch */
extern uint64_t FUN_00055328(void);                  /* cap-type id fetch */
extern uint64_t FUN_00055344(void);                  /* cap-type id fetch */
extern uint32_t FUN_0005537c(uint64_t *cap);         /* DART sid decode */
extern uint32_t FUN_000553b0(uint64_t *cap);         /* DART sid decode */
extern int      FUN_000554bc(uint64_t *cap);         /* DART-table cap predicate */
extern uint32_t FUN_000554f0(uint64_t *cap);         /* DART-table sid decode */
extern uint32_t FUN_00055524(uint64_t *cap);         /* DART-table sid decode */
extern uint64_t FUN_00055718(void);                  /* phys hint A */
extern uint64_t FUN_0005574c(uint64_t hint);         /* phys hint B */
extern void    FUN_00055a90(uint64_t type, uint64_t extra); /* untyped-create failure log */
extern void    FUN_0005b190(uint64_t code, const char *msg) __attribute__((noreturn)); /* kernel panic+abort */
extern uint64_t FUN_0005ba14(void);                  /* mach-header load-command list */
extern void    FUN_000651bc(uint64_t);               /* vspace op */
extern void    FUN_00066390(void);                   /* success path */
extern void    FUN_00067444(void);                   /* success path */
extern void    FUN_000675e8(void);                   /* success path */
extern void    FUN_00067a04(void);                   /* helper */
extern uint64_t FUN_000696a8(void);                  /* launcher/init helper */
extern void    FUN_0006a374(uint64_t, uint64_t, uint64_t);
extern void    FUN_0006a414(void);
extern uint8_t  FUN_00084dc8(void);                  /* byte getter */
extern void    FUN_001150e0(const char *msg) __attribute__((noreturn)); /* link-integrity panic */
extern void    FUN_00116bb4(uint64_t out, uint64_t, const char *fmt, void *); /* error-code print */
extern void    FUN_00118b28(const char *fmt, ...);   /* console log */
extern void    FUN_00118b94(const char *fmt, ...);   /* console log */
extern void    FUN_0011d7e8() __attribute__((noreturn)); /* stack-canary failure */
extern uint64_t FUN_0019ae2c(uint64_t);              /* zero-frame lookup */
extern void    FUN_0019ae60(uint64_t, uint64_t);     /* zero-frame release */
extern void    FUN_001a84f4(void *dst, uint64_t);    /* pair init */
extern uint64_t FUN_001a8564(void);                  /* pair build */
extern void    FUN_001afa84(const char *msg, uint64_t, uint64_t, ...) __attribute__((noreturn)); /* Swift "Fatal error" */
extern void    FUN_001b9084(void *dst, uint64_t, uint64_t); /* pair init */
extern void    FUN_001eb088(void *);                 /* protocol witness thunk */
extern void    FUN_00205844(void *, void *, uint64_t, uint64_t, uint64_t); /* Swift metadata set */
extern uint64_t FUN_00258c60(uint64_t, uint64_t, uint64_t); /* dict slot test (0/1) */
extern void    FUN_002591b4(uint64_t) __attribute__((noreturn)); /* Swift assert */
extern void    FUN_00294cb4(void *);                 /* value witness */
extern uint64_t FUN_002a0cf8(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t); /* key equality */
extern void    FUN_002a4ab4(uint64_t);               /* runtime gate */
extern void    FUN_002acbb8(uint64_t, uint64_t);     /* string emit thunk */
extern uint64_t FUN_00365b6c(uint64_t, void *, uint64_t, uint64_t, uint64_t); /* dict insert */
extern void    FUN_0036986c(void);                   /* runtime cleanup */
extern sk_u128_t FUN_0036993c(uint64_t, uint64_t, uint64_t, uint64_t); /* dict arena */
extern void    FUN_0036b118(uint64_t);               /* cL4 ref release */
extern uint64_t FUN_0036b270(uint64_t);              /* cL4 ref retain (returns obj) */
extern uint64_t FUN_00376820(uint64_t, uint64_t, void *); /* Swift metadata init */
extern void    FUN_003a25d4(uint64_t);               /* token release */
extern void    FUN_00012568(void);                   /* vspace table flush */
extern void    FUN_0006d7d0(uint64_t *cap);          /* cap post-process */

/* Out-of-region IPMM / error-funnel helpers (FUN_004b7xxx / FUN_004b8xxx). */
extern void    FUN_004b7008(uint64_t, uint64_t);     /* error funnel */
extern void    FUN_004b7ba0(uint64_t, void *);       /* page-obj build */
extern void    FUN_004b7bec(uint64_t);               /* freelist obj build */
extern sk_u128_t FUN_004b7c88(uint64_t, void *);     /* page-obj open */
extern uint64_t FUN_004b7cd4(uint64_t, void *);      /* error funnel */
extern void    FUN_004b7d20(uint64_t, void *);       /* zero-frame release */
extern void    FUN_004b7dec(void *);                 /* error funnel */
extern void    FUN_004b7e64(uint64_t, void *);       /* error funnel */
extern uint64_t FUN_004b7eb0(void);                  /* launcher alloc getter */
extern uint64_t FUN_004b7edc(uint64_t, void *);      /* frame map */
extern uint64_t FUN_004b7f24(uint64_t, void *);      /* error funnel */
extern void    FUN_004b7f6c(uint64_t, void *);       /* error funnel */
extern void    FUN_004b7fb4(uint64_t, void *);       /* zero-frame map */
extern void    FUN_004b808c(void);                   /* list integrity abort */
extern uint64_t FUN_004b8148(uint64_t, void *);      /* error funnel */
extern void    FUN_004b8198(uint64_t, void *);       /* error funnel (noreturn) */
extern uint64_t FUN_004b81e8(uint64_t, void *);      /* error funnel */
extern uint64_t FUN_004b8238(uint64_t, void *);      /* error funnel */
extern void    FUN_004b8288(void);                   /* error funnel */
extern void    FUN_004b82b4(void);                   /* error funnel */
extern void    FUN_004b82e0(void);                   /* error funnel */
extern void    FUN_004b830c(void);                   /* error funnel */
extern uint64_t FUN_004b8338(void);                  /* error funnel */
extern void    FUN_004b8364(void);                   /* error funnel */
extern void    FUN_004b8390(void);                   /* error funnel */
extern uint64_t FUN_004b83bc(void);                  /* cbootinfo getter */
extern void    FUN_004b83e8(void);                   /* error funnel */
extern void    FUN_004b8414(void);                   /* error funnel */
extern void    FUN_004b8440(void);                   /* error funnel */
extern void    FUN_004b846c(uint64_t);               /* error funnel */

/* ------------------------------------------------------------------ *
 * In-region global state (Ghidra DAT_/uRam name in the comment). These
 * are the launcher IPMM freelist, cbootinfo arena, vspace table, and
 * untyped-region registry. Declared extern here; the region-global file
 * (owned by the cbootinfo worker) provides the storage.
 * ------------------------------------------------------------------ */
extern uint8_t  g_ipmm_ready;            /* DAT_006b27e0 */
extern uint8_t  g_zero_frames_active;    /* DAT_006b27e8 */
extern uint64_t g_freelist_handle;       /* DAT_006b27f0 */
extern uint64_t g_freelist_vtable;       /* DAT_006b27f8 */
extern uint64_t g_freelist_base;         /* DAT_006b2808 */
extern uint64_t g_freelist_count;        /* DAT_006b2820 */
extern uint64_t g_freelist_used;         /* DAT_006b2828 */
extern uint64_t g_zero_handle;           /* DAT_006b2830 */
extern uint64_t g_zero_vtable;           /* DAT_006b2838 */
extern uint64_t g_zero_frame_size;       /* DAT_006b2840 */
extern uint64_t g_ipmm_unknown_28d0;     /* DAT_006b28d0 */
extern uint64_t g_cboot_alloc_base;      /* DAT_006b2918 */
extern uint64_t g_cboot_alloc_limit;     /* DAT_006b2920 */
extern uint64_t g_ipmm_bump_count;       /* DAT_006b2928 */
extern uint64_t g_ipmm_alloc_count;      /* DAT_006b2930 */
extern uint64_t g_ipmm_freed_count;      /* DAT_006b2938 */
extern uint64_t g_alloc_cursor_small;    /* DAT_006b2940 */
extern uint64_t g_alloc_cursor_32b;      /* DAT_006b2948 */
extern uint64_t g_alloc_cursor_32b2;     /* DAT_006b2950 */
extern uint8_t  g_vspace_table_ready;    /* DAT_006b2958 */
extern uint16_t g_l4_err_msg;            /* uRam0064e180 */
extern uint64_t g_slot_64e068;           /* uRam0064e068 (Swift slot) */
extern uint64_t g_slot_64e088;           /* uRam0064e088 (Swift slot) */
extern uint64_t g_slot_64e090;           /* uRam0064e090 (Swift slot) */
extern uint64_t g_slot_64e0a0;           /* uRam0064e0a0 (Swift slot) */
extern uint64_t g_slot_64e0a8;           /* uRam0064e0a8 (Swift slot) */
extern uint8_t  g_slot_64e1a0;           /* uRam0064e1a0 */
extern uint16_t g_slot_64e1a2;           /* uRam0064e1a2 */
extern uint8_t  g_slot_64e1a4;           /* uRam0064e1a4 */
extern uint8_t  g_slot_64e1a8;           /* uRam0064e1a8 */
extern uint8_t  g_slot_64e1ac;           /* uRam0064e1ac */
extern uint8_t  g_slot_64e1b0;           /* uRam0064e1b0 */
extern uint16_t *g_vspace_head;          /* DAT_006ad980 (short-list head) */
extern uint64_t g_image_base;            /* DAT_006ad6e0 */
extern uint64_t g_seg_data_end;          /* DAT_006ad988 */
extern uint64_t g_seg_text_end;          /* DAT_006ad990 */
extern uint64_t g_rt_slide;              /* DAT_2bc686b8378 */
extern uint64_t g_rt_slot_array[];       /* DAT_2bc686b8450[] */
extern uint64_t g_cboot_pte_bitmap[];    /* DAT_2bc686b8560[] (bitmap) */
extern uint64_t g_cboot_heap;            /* DAT_2bc686b8530 */
extern uint64_t g_cboot_heap_size;       /* DAT_2bc686b8528 */
extern uint64_t g_cboot_low;             /* DAT_2bc686b8538 */
extern uint64_t g_cboot_high;            /* DAT_2bc686b8540 */
extern uint64_t g_cboot_cursor;          /* DAT_2bc686b8548 */
extern uint64_t g_cboot_end;             /* DAT_2bc686b8550 */
extern uint64_t DAT_4d5e91c8a0;          /* decompiler high-VA artifact */
extern uint64_t DAT_4d5e91ca80;          /* decompiler high-VA artifact */
extern uint64_t DAT_9fd86d11a0;          /* decompiler high-VA artifact */
extern uint64_t DAT_9fd86d1380;          /* decompiler high-VA artifact */
extern uint64_t DAT_ee50745750;          /* decompiler high-VA artifact */
extern uint64_t g_untyped_count;         /* DAT_006be8b4 */
extern uint64_t g_untyped_base[];        /* DAT_006b2b10[] stride 0x2e8 */
extern uint64_t g_untyped_size[];        /* DAT_006b2b18[] stride 0x2e8 */
extern uint64_t g_untyped_tab[];         /* DAT_006b2960[] stride 0x2e8 */
extern uint64_t g_cboot_chain_head;      /* DAT_006be890 */
extern uint64_t g_cboot_unknown_898;     /* DAT_006be898 */
extern uint64_t g_phys_hint_a;           /* DAT_006be8a0 */
extern uint64_t g_phys_hint_b;           /* DAT_006be8a8 */
extern uint8_t  g_phys_hints_valid;      /* DAT_006be8b0 */
extern uint64_t g_phys_hint_a_cap;       /* DAT_006be8b8 */
extern uint64_t g_phys_hint_b_cap;       /* DAT_006be8c0 */
extern uint64_t g_seg_text_cap;          /* DAT_006be8c8 */
extern uint64_t g_seg_data_cap;          /* DAT_006be8d0 */
extern uint64_t g_untyped_scan_idx;      /* DAT_006be8e8 */
extern uint64_t g_cboot_alloc_base2;     /* DAT_006be880 */
extern uint64_t g_dart_count;            /* DAT_006be660 */
extern uint64_t g_dart_cap[];            /* DAT_006be668[] stride 0x10 */
extern uint32_t g_dart_sid[];            /* DAT_006be46c[] stride 0x10 */
extern uint64_t g_dart_table_count;      /* DAT_006be868 */
extern uint64_t g_dart_table_cap[];      /* DAT_006be670[] stride 0x10 */
extern uint32_t g_dart_table_sid[];      /* DAT_006be674[] stride 0x10 */
extern uint64_t g_cboot_cap_kind6;       /* DAT_006be870 */
extern uint64_t g_cboot_cap_kind7;       /* DAT_006be878 */
extern uint64_t g_cboot_cap_found;       /* DAT_006be888 */

/* ------------------------------------------------------------------ *
 * cL4 L4_ErrorCode string table (data-region owned; names kept verbatim).
 * ------------------------------------------------------------------ */
extern const char s_L4_ErrorCodeSuccess_004beec0[];
extern const char s_L4_ErrorCodePreempted_004beee0[];
extern const char s_L4_ErrorCodeCanceled_004bef00[];
extern const char s_L4_ErrorCodeTruncated_004bef20[];
extern const char s_L4_ErrorCodeCapInvalid_004bef40[];
extern const char s_L4_ErrorCodeSlotInvalid_004bef60[];
extern const char s_L4_ErrorCodeMethodInvalid_004bef80[];
extern const char s_L4_ErrorCodeArgumentInvalid_004befa0[];
extern const char s_L4_ErrorCodeOperationInvalid_004befc0[];
extern const char s_L4_ErrorCodePermissionInvalid_004befe0[];
extern const char s_L4_ErrorCode__zu_005a8c7b[];
extern const char s_Fatal_error_005accd0[];
extern const char s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0[];
extern const char s_Swift_NativeDictionary_swift_005be800[];
extern const char s_Creating_launcher_IPMM_freelist_s_005bef67[];
extern const char s_Creating_launcher_frame_zero_spa_005bef8c[];
extern const char s__ipmm_abort_in_function__s_line_005be94d[];
extern const char s__ipmm_abort_in_function__s_line_005bea28[];
extern const char s__ipmm_abort_in_function__s_line_005beafe[];
extern const char s__ipmm___0x_llx_bytes_left_005beb77[];
extern const char s__ipmm___bumped__zd_times_005beb92[];
extern const char s_unexpected_PMM_allocation_type_005becb2[];
extern const char s_Failed_to_map_frame_to_zero_005bed6a[];
extern const char s_Failed_to_create_untyped__type_005bedf1[];
extern const char s__ipmm___Operation_Invalid__Wrong_005bedc5[];
extern const char s_Failed_to_bump_freelist_005bee58[];
extern const char s_Failed_to_map_frame_freed_frame_005bef47[];
extern const char s___s__vspace_table_not_ready_yet_005befc4[];
extern const char s_L4_failed_on__s__d___s_005bf00c[];
extern const char s_expected_client_to_be_in_list_005bf1c8[];
extern const char s_Bad_link_elm__p_next_005bf1e6[];
extern const char s_Bad_link_elm__p_prev_005bf20c[];
extern const char s_Could_not_find_untyped_region_fo_005bf258[];
extern const char s_untyped___base_0x_016llx__size_0_005bf4e3[];
extern const char s_CBootInfo_found_DART_with_sid_005bf967[];
extern const char s_CBootInfo_found_DART_Table_with_s_005bf9d2[];
extern const char s___Warning__Unexpected_null_cap_in_005bfa04[];
extern const char s_ExclavePlatform_runtime_error__F_005bfa2e[];
extern const char s_ExclavePlatform_runtime_error__O_005bfa79[];
extern const char s_cbootinfo_out_of_memory__cannot_a_005bf3cc[];
extern const char s_Roottask_slide_is_0x_llx_005a8b16[];
extern const char s___TEXT_005bb905[];
extern const char s___DATA_005bb23b[];

/* Swift runtime type-metadata / data-region references (owned by the
 * data-region worker; addressed via &DAT_xxx[0]). */
extern const uint8_t DAT_005a4b80[];
extern const uint8_t DAT_004be938[];
extern const uint8_t DAT_004ea504[];
extern const uint8_t DAT_004bede8[];
extern const uint8_t DAT_004bee78[];
extern const uint8_t DAT_0064c260[];
extern const uint8_t DAT_004bbc30[];
extern const uint8_t DAT_004be8f0[];
extern const uint8_t DAT_004be900[];
extern const uint8_t DAT_004be920[];
extern const uint8_t DAT_004be930[];
extern const uint8_t DAT_004bedc0[];
extern const uint8_t UINT_0065d290[];

/* L4 error-message string storage (overlapping 8-byte window at 0x68a4e6/0x68a4e8). */
extern uint8_t DAT_0068a4e6[];
extern uint8_t DAT_0068a4e8[];

/* Generic L4 error descriptor words (fallback when code > 9). */
extern uint64_t DAT_004bf000;
extern uint64_t DAT_004bf008;
extern uint64_t DAT_004bf010;
extern uint64_t DAT_004bf018;

/* Forward declarations for in-region functions referenced before
 * their definitions (address-order). */
void FUN_0006a468(uint64_t *out);
long FUN_0006a4f0(unsigned long param_1);
void FUN_0006a520(void);
void FUN_0006a5e4(void);
long FUN_0006a668(unsigned long param_1);
void FUN_0006a698(void);
void FUN_0006a75c(long *param_1, uint64_t param_2, uint64_t param_3);
void FUN_0006a7c8(void);
void FUN_0006a860(void);
void FUN_0006abac(uint64_t param_1, uint32_t param_2, long *param_3);
sk_u128_t FUN_0006ae9c(uint64_t param_1, uint64_t param_2);
sk_u128_t FUN_0006af08(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_0006afb4(long *param_1, long param_2);
uint64_t FUN_0006afec(uint64_t param_1);
void FUN_0006b1d0(void);
void FUN_0006b1d4(void);
void FUN_0006b1ec(void);
void FUN_0006b23c(void);
void FUN_0006b274(void);
uint64_t FUN_0006b2bc(void);
void FUN_0006b2dc(void);
void FUN_0006b2ec(void);
void FUN_0006b2fc(void);
void FUN_0006b330(void);
void FUN_0006b360(void);
void FUN_0006b374(void);
void FUN_0006b3a4(void);
bool FUN_0006b3d0(uint64_t param_1);
void FUN_0006b3e0(void);
sk_u128_t FUN_0006b3f4(long param_1);
void FUN_0006b404(void);
bool FUN_0006b42c(uint64_t param_1);
int FUN_0006b438(void);
void FUN_0006b440(uint64_t param_1);
void FUN_0006b45c(void);
void FUN_0006b474(void);
void FUN_0006b48c(void);
void FUN_0006b4ac(void);
void FUN_0006b4c0(void);
void FUN_0006b4d0(void);
sk_u128_t FUN_0006b500(void);
sk_u128_t FUN_0006b514(void);
void FUN_0006b528(void);
void FUN_0006b540(void);
sk_u128_t FUN_0006b550(uint64_t param_1);
sk_u128_t FUN_0006b560(void);
uint64_t FUN_0006b584(uint64_t param_1, long param_2);
void FUN_0006b5a0(void);
void FUN_0006b5c0(void);
void FUN_0006b5e0(void);
sk_u128_t FUN_0006b600(void);
sk_u128_t FUN_0006b610(void);
void FUN_0006b620(void);
void FUN_0006b630(void);
void FUN_0006b640(void);
sk_u128_t FUN_0006b65c(void);
void FUN_0006b674(void);
sk_u128_t FUN_0006b680(void);
void FUN_0006b68c(void);
void FUN_0006b6a0(void);
void FUN_0006b6ac(void);
void FUN_0006b6c0(uint64_t base, uint64_t index, uint64_t a, uint64_t b, uint64_t c);
void FUN_0006b6d4(void);
uint64_t FUN_0006b6e0(void);
void FUN_0006b6f4(void);
void FUN_0006b700(void);
void FUN_0006b714(void);
void FUN_0006b728(void);
uint8_t FUN_0006b760(void);
uint8_t FUN_0006b764(void);
void FUN_0006b77c(uint64_t param_1);
void FUN_0006b78c(uint64_t param_1);
uint64_t FUN_0006b79c(void);
uint64_t FUN_0006b7ac(void);
void FUN_0006b7bc(void);
void FUN_0006b7e0(void);
void FUN_0006bb34(void);
uint64_t FUN_0006bb8c(void);
uint64_t FUN_0006bb98(void);
uint64_t FUN_0006bba4(void);
void FUN_0006bbb0(uint64_t *param_1, uint8_t param_2);
void FUN_0006bcc0(uint64_t param_1);
uint64_t FUN_0006bcf8(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                      uint64_t param_4, uint32_t param_5);
void FUN_0006bfe4(uint64_t param_1, uint64_t param_2);
void FUN_0006c1b4(void);
void FUN_0006c1d4(void);
void FUN_0006c1e8(void);
void FUN_0006c208(void);
void FUN_0006c214(void);
void FUN_0006c228(uint8_t param_1);
uint64_t FUN_0006c2b0(long param_1);
void FUN_0006c3c8(void);
uint64_t FUN_0006c404(void);
uint64_t FUN_0006c454(void);
void FUN_0006c5cc(long *param_1, int param_2);
void FUN_0006cdf8(uint64_t param_1);
uint64_t FUN_0006ce60(void);
uint64_t FUN_0006cea4(uint64_t param_1);
uint64_t FUN_0006cec8(uint64_t param_1);
uint64_t FUN_0006cf0c(uint64_t param_1);
uint64_t FUN_0006cf50(uint64_t param_1);
uint64_t FUN_0006cfe4(void);
uint64_t FUN_0006d024(uint64_t param_1);
long FUN_0006d0b8(uint64_t param_1);
uint64_t FUN_0006d150(uint64_t param_1);
bool FUN_0006d1e4(uint64_t param_1);
uint64_t FUN_0006d240(uint64_t param_1, uint64_t param_2);
uint64_t FUN_0006d450(void);
uint64_t FUN_0006d45c(void);
uint64_t FUN_0006d4b4(void);
uint8_t FUN_0006d4f0(void);
uint64_t FUN_0006d4fc(void);
uint64_t FUN_0006d508(void);
uint64_t FUN_0006d514(void);
uint64_t FUN_0006d520(void);
long *FUN_0006a4c0(long *param_1, long param_2);
uint8_t *FUN_0006b388(void);
uint16_t *FUN_0006c244(uint16_t param_1);
long *FUN_0006ce00(long param_1);
uint64_t FUN_0006d52c(void);

/* ================================================================== *
 * Function bodies (address order as in the SK14 wave batch).
 * ================================================================== */

/* FUN_0006a468 @ 0x0006a468   (est. sk_ipmm_launcher_record_init)
 * Ghidra: void FUN_0006a468(void)
 * Fetches the launcher-bootstrap value from FUN_000696a8 and stores it into
 * the sink pointed to by the register-captured x20 (the caller's `this`/out
 * slot). A one-line initializer thunk.
 * Confidence: low
 * Notes: unaff_x20 is the not-modelled first argument (Swift/register ABI). */
void FUN_0006a468(uint64_t *out)
{
    *out = FUN_000696a8();
}

/* FUN_0006a4c0 @ 0x0006a4c0   (est. sk_swift_field0x50_accessor)
 * Ghidra: long * FUN_0006a4c0(long *param_1, long param_2)
 * Swift runtime metadata accessor: reads the 32-bit flags word at
 * metadata(param_2)->+0x50; if bit 0x11 (bit 17) is set, rebases param_1 by
 * AND-ing the low byte with the complement of (lowbyte+0x10). Classic
 * indirect-enum payload projection.
 * Confidence: low
 * Notes: metadata is at *(param_2-8); offset 0x50 flags; bit 0x11 tag. */
long *FUN_0006a4c0(long *param_1, long param_2)
{
    uint32_t flags = *(uint32_t *)(*(long *)(param_2 - 8) + 0x50);
    if ((flags >> 0x11 & 1) != 0) {
        uint64_t low = (uint64_t)flags & 0xff;
        param_1 = (long *)(*param_1 + (low + 0x10 & (low ^ 0xffffffffffffffffull)));
    }
    return param_1;
}

/* FUN_0006a4f0 @ 0x0006a4f0   (est. sk_swift_buf_relocated_end)
 * Ghidra: long FUN_0006a4f0(ulong param_1)
 * Swift heap-buffer projection: if the low bit (tag) is set, follow the
 * pointer at param_1&~1; then return param_1+0xc plus the 32-bit length at
 * param_1+0xc. Yields the buffer's end address from a tagged/relocated
 * reference.
 * Confidence: low */
long FUN_0006a4f0(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffeull);
    return (long)(param_1 + 0xc) + (long)*(int *)(param_1 + 0xc);
}

/* FUN_0006a520 @ 0x0006a520   (est. sk_indirect_branch_thunk)
 * Ghidra: void FUN_0006a520(void)
 * Decompiler artifact: Ghidra removed an unreachable block (0x6a534) and kept
 * only the first instruction of an indirect-branch stub written into a dead
 * slot. The real body is an out-of-line branch; kept verbatim for fidelity.
 * Confidence: low
 * Notes: uRam000000000064e068 = 0xa8c17bfda9000500 (prologue insn); unreachable
 *   block 0x6a534 removed. */
void FUN_0006a520(void)
{
    g_slot_64e068 = 0xa8c17bfda9000500ull;
}

/* FUN_0006a5e4 @ 0x0006a5e4   (est. sk_indirect_branch_thunk)
 * Ghidra: void FUN_0006a5e4(void)
 * Decompiler artifact (unreachable block 0x6a5f8 removed); same shape as
 * FUN_0006a520 — a branch stub whose body Ghidra dropped.
 * Confidence: low
 * Notes: uRam000000000064e088 = 0x90000593910043fd (prologue insn). */
void FUN_0006a5e4(void)
{
    g_slot_64e088 = 0x90000593910043fdull;
}

/* FUN_0006a668 @ 0x0006a668   (est. sk_swift_buf_relocated_end)
 * Ghidra: long FUN_0006a668(ulong param_1)
 * Identical to FUN_0006a4f0: tagged heap-buffer end projection.
 * Confidence: low */
long FUN_0006a668(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffeull);
    return (long)(param_1 + 0xc) + (long)*(int *)(param_1 + 0xc);
}

/* FUN_0006a698 @ 0x0006a698   (est. sk_indirect_branch_thunk)
 * Ghidra: void FUN_0006a698(void)
 * Decompiler artifact (unreachable block 0x6a6ac removed); branch stub.
 * Confidence: low
 * Notes: uRam000000000064e090 = 0xb5000101f9462e61 (prologue insn). */
void FUN_0006a698(void)
{
    g_slot_64e090 = 0xb5000101f9462e61ull;
}

/* FUN_0006a75c @ 0x0006a75c   (est. sk_swift_object_lazy_init)
 * Ghidra: void FUN_0006a75c(long *param_1, undefined8 param_2, undefined8 param_3)
 * Lazily initialises the global Swift object *param_1: if it is still null,
 * runs the runtime object-init (FUN_00027614 with type metadata DAT_005a4b80)
 * and stores the result of the metadata constructor FUN_00376820.
 * Confidence: medium
 * Notes: object slot 0x64e078; type metadata DAT_005a4b80. */
void FUN_0006a75c(long *param_1, uint64_t param_2, uint64_t param_3)
{
    if (*param_1 == 0) {
        uint64_t meta = FUN_00027614(0x64e078, (uint64_t)&DAT_005a4b80[0]);
        uint64_t local = param_2;
        *param_1 = FUN_00376820(param_3, meta, &local);
    }
}

/* FUN_0006a7c8 @ 0x0006a7c8   (est. sk_indirect_branch_thunk)
 * Ghidra: void FUN_0006a7c8(void)
 * Decompiler artifact (unreachable block 0x6a7dc removed); branch stub.
 * Confidence: low
 * Notes: uRam000000000064e0a0 = 0xd0000321f9400100 (prologue insn). */
void FUN_0006a7c8(void)
{
    g_slot_64e0a0 = 0xd0000321f9400100ull;
}

/* FUN_0006a860 @ 0x0006a860   (est. sk_swift_global_singleton_init)
 * Ghidra: void FUN_0006a860(void)
 * Initialises the global Swift object at 0x64e0a8: builds runtime metadata for
 * DAT_004be938, then stores the constructed singleton from FUN_00376820 into
 * the 0x64e0a8 slot. Writes the object slot (read-only address warning).
 * Confidence: medium
 * Notes: uRam000000000064e0a8 written; type metadata DAT_004be938. */
void FUN_0006a860(void)
{
    uint64_t meta = FUN_00027614(0x64e0b0, (uint64_t)&DAT_004be938[0]);
    uint64_t local = 0x66ee00;
    g_slot_64e0a8 = FUN_00376820((uint64_t)&DAT_004ea504[0], meta, &local);
}

/* FUN_0006abac @ 0x0006abac   (est. sk_native_dictionary_build)
 * Ghidra: void FUN_0006abac(long param_1, uint param_2, long *param_3)
 * Swift.NativeDictionary construction. Iterates the source storage at
 * param_1 (+0x10 count, +0x30 element triplets), retaining each element
 * (FUN_0036b270), and inserting it into the destination dictionary param_3
 * (a raw-bitset table: +0x40 occupancy bitmap, +0x30 key array, +0x38 value
 * array, +0x10 count). The pair builder FUN_0006ae9c returns (key, flags) as
 * a 128-bit value: lo = key, hi bit0 = found, hi bit0-of-low32 = collision.
 * On success re-opens the shared dictionary arena (FUN_0036993c) and commits;
 * a failed commit emits a Swift "Fatal error" for NativeDictionary (noreturn).
 * Keeps element retains balanced with releases on the failure path.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x6adcc/0x6add0/0x6add4) bounds traps;
 *   s_Swift_NativeDictionary_swift_005be800 fatal string. */
void FUN_0006abac(uint64_t param_1, uint32_t param_2, long *param_3)
{
    uint64_t idx = 0;
    uint64_t count = *(uint64_t *)(param_1 + 0x10);
    uint64_t *src = (uint64_t *)(param_1 + 0x30);
    uint64_t k0 = 0, k1 = 0, v = 0;

    for (;;) {
        if (count == idx) {
            FUN_0036b118(param_1);
            return;
        }
        if (*(uint64_t *)(param_1 + 0x10) <= idx)
            SK_FATAL();                       /* SoftwareBreakpoint(1,0x6adcc) */
        k0 = src[-2];
        k1 = src[-1];
        v  = src[0];
        uint64_t table = *(uint64_t *)param_3;
        FUN_0036b270(k1);
        FUN_0036b270(v);
        sk_u128_t pair = FUN_0006ae9c(k0, k1);
        uint64_t key = pair.lo;
        uint64_t tcount = *(uint64_t *)(table + 0x10);
        uint64_t off = (uint64_t)~((uint32_t)pair.hi) & 1;  /* collision flag */
        if (tcount + off < tcount)
            SK_FATAL();                       /* SCARRY8(0x6add0) */
        uint64_t m = FUN_00002534(0x64e108, (uint64_t)&DAT_004bede8[0]);
        uint64_t found = FUN_00258c60(param_2 & 1, tcount + off, m);
        if ((found & 1) != 0) {
            sk_u128_t pair2 = FUN_0006ae9c(k0, k1);
            key = pair2.lo;
            if (((uint32_t)pair.hi & 1) != ((uint32_t)pair2.hi & 1))
                FUN_002591b4(0x6753a0);       /* Swift assert, noreturn */
        }
        if ((pair.hi & 1) != 0)
            break;
        uint64_t tbl = *(uint64_t *)param_3;
        *(uint64_t *)(tbl + (key >> 6) * 8 + 0x40) |= 1ull << (key & 0x3f);
        uint64_t *ks = (uint64_t *)(*(uint64_t *)(tbl + 0x30) + key * 0x10);
        ks[0] = k0;
        ks[1] = k1;
        *(uint64_t *)(*(uint64_t *)(tbl + 0x38) + key * 8) = v;
        if (*(uint64_t *)(tbl + 0x10) + 1 < *(uint64_t *)(tbl + 0x10))
            SK_FATAL();                       /* SCARRY8(0x6add4) */
        *(uint64_t *)(tbl + 0x10) += 1;
        src += 3;
        idx += 1;
        param_2 = 1;
    }

    /* Re-open the shared arena and commit the dictionary. */
    sk_u128_t arena = FUN_0036993c((uint64_t)&UINT_0065d290[0],
                                   (uint64_t)&DAT_004bee78[0], 0, 0);
    *(uint64_t *)arena.hi = 0;
    FUN_0036986c();
    uint64_t local58 = arena.lo;
    FUN_0036b270(arena.lo);
    uint64_t t = FUN_00002534((uint64_t)&DAT_0064c260[0], (uint64_t)&DAT_004bbc30[0]);
    uint64_t rc = FUN_00365b6c(t, &local58, t, 0x672fa0, 0);
    if ((rc & 1) == 0) {
        FUN_0036b118(param_1);
        FUN_003a25d4(k1);
        FUN_0036b118(v);
        FUN_0036b118(local58);
        return;
    }
    uint64_t meta64 = 0;
    uint64_t meta_hi = 0xe000000000000000ull;
    FUN_002a4ab4(0x1e);
    FUN_002acbb8(0xd00000000000001bull, 0x80000000005be800ull);
    uint64_t pr[2] = { k0, k1 };
    FUN_00205844(pr, &meta64, 0x6753a0, 0x6756a8, 0x66e1b8);
    FUN_002acbb8(0x27, 0xe100000000000000ull);
    FUN_001afa84(s_Fatal_error_005accd0, 0xb, 2, meta64, meta_hi,
                 s_Swift_NativeDictionary_swift_005be800, 0x1c, 2, 0x318, 0);
}

/* FUN_0006ae9c @ 0x0006ae9c   (est. sk_tagged_pair_build)
 * Ghidra: void FUN_0006ae9c(undefined8 param_1, undefined8 param_2)
 * Builds a 128-bit (key,flags) pair for the dictionary layer. Runs the pair
 * object-init sequence (FUN_001a84f4 / FUN_001b9084) against the caller's
 * context `self` (+0x28 slot), derives the hash index from FUN_001a8564, then
 * delegates the actual lookup to FUN_0006af08. The 16-byte result is returned
 * in the register pair (Ghidra's `void` signature drops it).
 * Confidence: medium
 * Notes: unaff_x20 = self; 16-byte return not modelled by Ghidra. */
/* Context pointer passed in register (unaff_x20), not modelled by Ghidra;
 * shared module slot so the pair-builder and its probe agree. */
static uint64_t g_pair_self;

sk_u128_t FUN_0006ae9c(uint64_t param_1, uint64_t param_2)
{
    uint64_t self = g_pair_self;
    uint8_t buf[72];
    FUN_001a84f4(buf, *(uint64_t *)(self + 0x28));
    FUN_001b9084(buf, param_1, param_2);
    uint64_t idx = FUN_001a8564();
    return FUN_0006af08(param_1, param_2, idx);
}

/* FUN_0006af08 @ 0x0006af08   (est. sk_hash_table_probe)
 * Ghidra: undefined1 [16] FUN_0006af08(long param_1,long param_2,ulong param_3)
 * Probes a raw-bitset hash table at `self`: table size (in bits) is the byte at
 * self+0x20, the occupancy bitmap starts at self+0x40, and the key array
 * (16-byte entries) at self+0x30. Starting from index param_3, scans forward
 * (wrapping through the size mask) for either a matching (param_1,param_2) key
 * or an empty slot. Returns {lo = slot index, hi = found flag}.
 * Confidence: high
 * Notes: 16-byte return as sk_u128_t; FUN_002a0cf8 = key equality helper. */
sk_u128_t FUN_0006af08(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t self = g_pair_self;
    uint8_t width = *(uint8_t *)(self + 0x20);
    uint64_t bit;
    for (;;) {
        param_3 = param_3 & ~(~0ull << ((uint64_t)width & 0x3f));
        bit = 1ull << (param_3 & 0x3f)
              & *(uint64_t *)(self + 0x40 + (param_3 >> 6) * 8);
        if (bit == 0)
            break;
        long *entry = (long *)(*(long *)(self + 0x30) + param_3 * 0x10);
        long k0 = *entry;
        long k1 = entry[1];
        if ((k0 == (long)param_1 && k1 == (long)param_2) ||
            (FUN_002a0cf8(k0, k1, param_1, param_2, 0) & 1) != 0)
            break;
        param_3 = param_3 + 1;
    }
    sk_u128_t r = { param_3, bit != 0 };
    return r;
}

/* FUN_0006afb4 @ 0x0006afb4   (est. sk_bitmap_range_descriptor)
 * Ghidra: void FUN_0006afb4(long *param_1, long param_2)
 * Builds a 5-word range descriptor for a raw-bitset table (param_2): word 0 =
 * table base, word 1 = table+0x40 (bitmap), word 2 = low-size mask
 * (~(-1<<width)), word 3 = 0, word 4 = partial first-bitmap-word mask AND the
 * first bitmap word. Used to bound linear scans over a hash table.
 * Confidence: medium
 * Notes: width byte at param_2+0x20; bitmap at param_2+0x40. */
void FUN_0006afb4(long *param_1, long param_2)
{
    uint64_t hi_mask = ~0ull << ((uint64_t)*(uint8_t *)(param_2 + 0x20) & 0x3f);
    param_1[0] = param_2;
    uint64_t w = *(uint64_t *)(param_2 + 0x40);
    uint64_t count = -hi_mask;               /* == 1 << width */
    uint64_t partial = ~0ull;
    if (count < 0x40)
        partial = ~(~0ull << (count & 0x3f));
    param_1[1] = param_2 + 0x40;
    param_1[2] = ~hi_mask;
    param_1[3] = 0;
    param_1[4] = partial & w;
}

/* FUN_0006afec @ 0x0006afec   (est. sk_protocol_witness_thunk)
 * Ghidra: undefined8 FUN_0006afec(undefined8 param_1)
 * Swift protocol-witness thunk: builds the runtime object for metadata
 * DAT_004bedc0 (slot 0x64e0e0) then dispatches param_1 through the second
 * entry (offset +8) of the witness table at (obj-8). Returns param_1.
 * Confidence: low
 * Notes: vtable pointer is *(obj-8); +8 = witness method 1. */
uint64_t FUN_0006afec(uint64_t param_1)
{
    uint64_t obj = FUN_00002534(0x64e0e0, (uint64_t)&DAT_004bedc0[0]);
    (*(uint64_t (*)(uint64_t, uint64_t))(*(long *)(obj - 8) + 8))(param_1, obj);
    return param_1;
}

/* FUN_0006b1d0 @ 0x0006b1d0   (est. sk_helper_tailcall)
 * Ghidra: void FUN_0006b1d0(void)
 * Tail-call forwarder into FUN_00067a04.
 * Confidence: low */
void FUN_0006b1d0(void)
{
    FUN_00067a04();
}

/* FUN_0006b1d4 @ 0x0006b1d4   (est. sk_helper_tailcall)
 * Ghidra: void FUN_0006b1d4(void)
 * Tail-call forwarder into FUN_00067a04 (duplicate of FUN_0006b1d0).
 * Confidence: low */
void FUN_0006b1d4(void)
{
    FUN_00067a04();
}

/* FUN_0006b1ec @ 0x0006b1ec   (est. sk_runtime_init_check)
 * Ghidra: void FUN_0006b1ec(void)
 * Runs the init pair FUN_0006b2ec/FUN_000651bc; on the carried zero-flag
 * (success) takes the FUN_00066390 path, otherwise the stack-canary failure
 * trap FUN_0011d7e8 (noreturn).
 * Confidence: low
 * Notes: in_ZR / extraout_x8 are NZCV+register artifacts of the tail-call. */
void FUN_0006b1ec(void)
{
    FUN_0006b2ec();
    FUN_000651bc(0);                 /* extraout_x8 not modelled */
    if (/* in_ZR (zero flag) */ 1) {
        FUN_00066390();
        return;
    }
    FUN_0011d7e8();
}

/* FUN_0006b23c @ 0x0006b23c   (est. sk_runtime_init_check)
 * Ghidra: void FUN_0006b23c(void)
 * Runs the init pair FUN_0006b2dc/FUN_0006b360; success path FUN_00067444,
 * else the stack-canary trap FUN_0011d7e8.
 * Confidence: low
 * Notes: in_ZR flag artifact. */
void FUN_0006b23c(void)
{
    FUN_0006b2dc();
    FUN_0006b360();
    if (/* in_ZR (zero flag) */ 1) {
        FUN_00067444();
        return;
    }
    FUN_0011d7e8();
}

/* FUN_0006b274 @ 0x0006b274   (est. sk_runtime_init_check)
 * Ghidra: void FUN_0006b274(void)
 * Same shape as FUN_0006b23c but the success path is FUN_000675e8.
 * Confidence: low
 * Notes: in_ZR flag artifact. */
void FUN_0006b274(void)
{
    FUN_0006b2dc();
    FUN_0006b360();
    if (/* in_ZR (zero flag) */ 1) {
        FUN_000675e8();
        return;
    }
    FUN_0011d7e8();
}

/* FUN_0006b2bc @ 0x0006b2bc   (est. sk_singleton_slot_addr)
 * Ghidra: undefined8 FUN_0006b2bc(void)
 * Returns the fixed global object-slot address 0x64e038.
 * Confidence: low */
uint64_t FUN_0006b2bc(void)
{
    return 0x64e038;
}

/* FUN_0006b2dc @ 0x0006b2dc   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b2dc(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b2dc(void)
{
}

/* FUN_0006b2ec @ 0x0006b2ec   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b2ec(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b2ec(void)
{
}

/* FUN_0006b2fc @ 0x0006b2fc   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b2fc(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b2fc(void)
{
}

/* FUN_0006b330 @ 0x0006b330   (est. sk_swift_thunk_tailcall)
 * Ghidra: void FUN_0006b330(void)
 * Tail-call forwarder into FUN_001eb088 (Swift protocol witness).
 * Confidence: low */
void FUN_0006b330(void)
{
    FUN_001eb088(0);
}

/* FUN_0006b360 @ 0x0006b360   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b360(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b360(void)
{
}

/* FUN_0006b374 @ 0x0006b374   (est. sk_swift_global_init)
 * Ghidra: void FUN_0006b374(void)
 * Runs Swift runtime object-init for slot 0x64e008 with metadata DAT_004be8f0.
 * Confidence: low */
void FUN_0006b374(void)
{
    FUN_00002534(0x64e008, (uint64_t)&DAT_004be8f0[0]);
}

/* FUN_0006b388 @ 0x0006b388   (est. sk_frame_pointer_proj)
 * Ghidra: undefined1 * FUN_0006b388(void)
 * Returns a pointer into the caller's stack frame (Ghidra &stack0x90). A
 * Swift frame-relative value projection.
 * Confidence: low
 * Notes: return value is a stack-relative pointer; reproduced as a local. */
uint8_t *FUN_0006b388(void)
{
    uint8_t frame[0x90];
    return frame;
}

/* FUN_0006b3a4 @ 0x0006b3a4   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b3a4(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b3a4(void)
{
}

/* FUN_0006b3d0 @ 0x0006b3d0   (est. sk_gt_one)
 * Ghidra: bool FUN_0006b3d0(ulong param_1)
 * Returns (param_1 > 1) — a count upper-bound predicate.
 * Confidence: high */
bool FUN_0006b3d0(uint64_t param_1)
{
    return 1 < param_1;
}

/* FUN_0006b3e0 @ 0x0006b3e0   (est. sk_launcher_helper_tailcall)
 * Ghidra: void FUN_0006b3e0(void)
 * Tail-call forwarder into FUN_000696a8.
 * Confidence: low */
void FUN_0006b3e0(void)
{
    FUN_000696a8();
}

/* FUN_0006b3f4 @ 0x0006b3f4   (est. sk_index_plus_one)
 * Ghidra: undefined1 [16] FUN_0006b3f4(long param_1)
 * Returns the 128-bit value {lo=0, hi=param_1+1} (Ghidra `_0_8_=param_1+1;
 * _8_8_=0; return << 0x40`).
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b3f4(long param_1)
{
    sk_u128_t r = { 0, (uint64_t)(param_1 + 1) };
    return r;
}

/* FUN_0006b404 @ 0x0006b404   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b404(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b404(void)
{
}

/* FUN_0006b42c @ 0x0006b42c   (est. sk_gt_one)
 * Ghidra: bool FUN_0006b42c(ulong param_1)
 * Returns (param_1 > 1) — a count upper-bound predicate (dup of 6b3d0).
 * Confidence: high */
bool FUN_0006b42c(uint64_t param_1)
{
    return 1 < param_1;
}

/* FUN_0006b438 @ 0x0006b438   (est. sk_flag_increment)
 * Ghidra: int FUN_0006b438(void)
 * Returns in_w8 + 1 where in_w8 is a not-modelled flag/register carry.
 * Confidence: low
 * Notes: in_w8 (w8 register) not modelled; rendered as +1 of the carried value. */
int FUN_0006b438(void)
{
    return 0 + 1;                       /* in_w8 not modelled */
}

/* FUN_0006b440 @ 0x0006b440   (est. sk_value_witness_byte_count)
 * Ghidra: void FUN_0006b440(ulong param_1)
 * Computes the Swift value-witness size word from param_1 (SWAR byte-count
 * idiom: `(x & 0xffffffff) + 0xfefefefefefeff & ~in_x9`) and passes it to the
 * value-witness helper FUN_00294cb4.
 * Confidence: low
 * Notes: in_x9 (unmodelled) makes the final AND term unknown. */
void FUN_0006b440(uint64_t param_1)
{
    uint64_t mask = /* in_x9 (unmodelled) */ 0xffffffffffffffffull;
    uint64_t buf = (param_1 & 0xffffffff) + 0xfefefefefefeffull
                   & (mask ^ 0xffffffffffffffffull);
    FUN_00294cb4(&buf);
}

/* FUN_0006b45c @ 0x0006b45c   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b45c(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b45c(void)
{
}

/* FUN_0006b474 @ 0x0006b474   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b474(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b474(void)
{
}

/* FUN_0006b48c @ 0x0006b48c   (est. sk_swift_closure_setup)
 * Ghidra: void FUN_0006b48c(void)
 * Sets up a 2-word closure (return-address 0x67ecc + value 0) and invokes the
 * Swift runtime object-init FUN_00002534 (Ghidra dropped the arguments).
 * Confidence: low
 * Notes: LAB_00067ecc return address; FUN_00002534 called with no args. */
void FUN_0006b48c(void)
{
    uint64_t closure[2] = { 0x67ecc, 0 };
    FUN_00002534(0, 0);                 /* args dropped by decompiler */
}

/* FUN_0006b4ac @ 0x0006b4ac   (est. sk_range_init)
 * Ghidra: void FUN_0006b4ac(void)
 * Calls FUN_0006a374(0, 8, 0) — a (start,count,flags) range initializer.
 * Confidence: low */
void FUN_0006b4ac(void)
{
    FUN_0006a374(0, 8, 0);
}

/* FUN_0006b4c0 @ 0x0006b4c0   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b4c0(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b4c0(void)
{
}

/* FUN_0006b4d0 @ 0x0006b4d0   (est. sk_devicetreekit_fatal)
 * Ghidra: void FUN_0006b4d0(void)
 * Swift "Fatal error" trap attributed to DeviceTreeKit.swift (noreturn).
 * Arguments in_x3/in_x4 are unmodelled register values.
 * Confidence: low
 * Notes: s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0; in_x3/in_x4 not modelled. */
void FUN_0006b4d0(void)
{
    FUN_001afa84(s_Fatal_error_005accd0, 0xb, 2,
                 /* in_x3 */ 0, /* in_x4 */ 0,
                 s_DeviceTreeKit_DeviceTreeKit_swif_005be7d0, 0x21, 2);
}

/* FUN_0006b500 @ 0x0006b500   (est. sk_buf_descriptor_16)
 * Ghidra: undefined1 [16] FUN_0006b500(void)
 * Returns the 128-bit buffer descriptor {lo = &stackbuf, hi = 0x10}.
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b500(void)
{
    uint8_t buf[0x10];
    sk_u128_t r = { (uint64_t)(uintptr_t)buf, 0x10 };
    return r;
}

/* FUN_0006b514 @ 0x0006b514   (est. sk_buf_descriptor_16)
 * Ghidra: undefined1 [16] FUN_0006b514(void)
 * Returns the 128-bit buffer descriptor {lo = &stackbuf, hi = 0x10}.
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b514(void)
{
    uint8_t buf[0x10];
    sk_u128_t r = { (uint64_t)(uintptr_t)buf, 0x10 };
    return r;
}

/* FUN_0006b528 @ 0x0006b528   (est. sk_swift_value_setup)
 * Ghidra: void FUN_0006b528(void)
 * Sets up two stack words (0x30, 0xe100000000000000) then calls FUN_0006a414.
 * Confidence: low */
void FUN_0006b528(void)
{
    uint64_t w0 = 0x30;
    uint64_t w1 = 0xe100000000000000ull;
    FUN_0006a414();
}

/* FUN_0006b540 @ 0x0006b540   (est. sk_string_emit_thunk)
 * Ghidra: void FUN_0006b540(void)
 * Tail-call into the string-emit thunk FUN_002acbb8 (args dropped).
 * Confidence: low */
void FUN_0006b540(void)
{
    FUN_002acbb8(0, 0);
}

/* FUN_0006b550 @ 0x0006b550   (est. sk_string_desc_emit)
 * Ghidra: undefined1 [16] FUN_0006b550(undefined8 param_1)
 * Returns the 128-bit {lo = 0x677880 (string-table offset), hi = param_1}.
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b550(uint64_t param_1)
{
    sk_u128_t r = { 0x677880, param_1 };
    return r;
}

/* FUN_0006b560 @ 0x0006b560   (est. sk_literal_string_emit)
 * Ghidra: undefined1 [16] FUN_0006b560(void)
 * Returns the 128-bit literal "out of bouns\0xee" packed into two words
 * (little-endian): lo = 0x20666f2074756f20 ("out of "), hi = 0xee0073646e756f62.
 * Confidence: low
 * Notes: string-literal thunk. */
sk_u128_t FUN_0006b560(void)
{
    sk_u128_t r = { 0x20666f2074756f20ull, 0xee0073646e756f62ull };
    return r;
}

/* FUN_0006b584 @ 0x0006b584   (est. sk_name_or_default)
 * Ghidra: undefined8 FUN_0006b584(undefined8 param_1,long param_2)
 * Returns param_1 if param_2 != 0, else the packed literal "no nam"/
 * (0x656d616e206f6e28). A default-name selector.
 * Confidence: low */
uint64_t FUN_0006b584(uint64_t param_1, long param_2)
{
    if (param_2 != 0)
        return param_1;
    return 0x656d616e206f6e28ull;
}

/* FUN_0006b5a0 @ 0x0006b5a0   (est. sk_swift_global_init)
 * Ghidra: void FUN_0006b5a0(void)
 * Runs Swift runtime object-init for the object at 0x64e030 with metadata
 * DAT_004be900.
 * Confidence: low
 * Notes: FUN_0064e030 is a data symbol Ghidra demoted to a code ref. */
void FUN_0006b5a0(void)
{
    FUN_00002534(0x64e030, (uint64_t)&DAT_004be900[0]);
}

/* FUN_0006b5c0 @ 0x0006b5c0   (est. sk_swift_thunk_stackbuf)
 * Ghidra: void FUN_0006b5c0(void)
 * Calls the protocol-witness FUN_001eb088 with a stack buffer pointer.
 * Confidence: low */
void FUN_0006b5c0(void)
{
    uint8_t buf[0x10];
    FUN_001eb088(buf);
}

/* FUN_0006b5e0 @ 0x0006b5e0   (est. sk_swift_thunk_stackbuf)
 * Ghidra: void FUN_0006b5e0(void)
 * Calls the protocol-witness FUN_001eb088 with a stack buffer pointer (dup).
 * Confidence: low */
void FUN_0006b5e0(void)
{
    uint8_t buf[0x10];
    FUN_001eb088(buf);
}

/* FUN_0006b600 @ 0x0006b600   (est. sk_buf_descriptor_pair)
 * Ghidra: undefined1 [16] FUN_0006b600(void)
 * Returns {lo = 0x20, hi = 0xe100000000000000} (a Swift value + tag).
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b600(void)
{
    sk_u128_t r = { 0x20, 0xe100000000000000ull };
    return r;
}

/* FUN_0006b610 @ 0x0006b610   (est. sk_zero_hi_word)
 * Ghidra: undefined1 [16] FUN_0006b610(void)
 * Returns {lo = 0, hi = 0xe000000000000000} (ZEXT816 << 0x40).
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b610(void)
{
    sk_u128_t r = { 0, 0xe000000000000000ull };
    return r;
}

/* FUN_0006b620 @ 0x0006b620   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b620(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b620(void)
{
}

/* FUN_0006b630 @ 0x0006b630   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b630(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b630(void)
{
}

/* FUN_0006b640 @ 0x0006b640   (est. sk_string_emit_thunk)
 * Ghidra: void FUN_0006b640(void)
 * Emits the packed literal 0x20657a69735b20 (" sizez e") with tag
 * 0xe700000000000000 via FUN_002acbb8.
 * Confidence: low */
void FUN_0006b640(void)
{
    FUN_002acbb8(0x20657a69735b20ull, 0xe700000000000000ull);
}

/* FUN_0006b65c @ 0x0006b65c   (est. sk_stack_pair_descriptor)
 * Ghidra: undefined1 [16] FUN_0006b65c(void)
 * Returns {lo = &stack0x10, hi = &stack0x0f} (two stack-relative pointers).
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b65c(void)
{
    uint8_t buf[0x10];
    sk_u128_t r = { (uint64_t)(uintptr_t)(buf + 0), (uint64_t)(uintptr_t)(buf - 1) };
    return r;
}

/* FUN_0006b674 @ 0x0006b674   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b674(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b674(void)
{
}

/* FUN_0006b680 @ 0x0006b680   (est. sk_buf_descriptor_pair)
 * Ghidra: undefined1 [16] FUN_0006b680(void)
 * Returns {lo = 10, hi = 0xe100000000000000} (a Swift value + tag).
 * Confidence: low
 * Notes: 16-byte return as sk_u128_t. */
sk_u128_t FUN_0006b680(void)
{
    sk_u128_t r = { 10, 0xe100000000000000ull };
    return r;
}

/* FUN_0006b68c @ 0x0006b68c   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b68c(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b68c(void)
{
}

/* FUN_0006b6a0 @ 0x0006b6a0   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b6a0(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b6a0(void)
{
}

/* FUN_0006b6ac @ 0x0006b6ac   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b6ac(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b6ac(void)
{
}

/* FUN_0006b6c0 @ 0x0006b6c0   (est. sk_tuple_element_store)
 * Ghidra: void FUN_0006b6c0(void)
 * Stores a 3-tuple into an element array: base = x27 (this), index = x23;
 * writes x20 at base+0x10 and x21/x22 at base + index*0x10 + 0x20/0x28.
 * Confidence: low
 * Notes: unaff_x20/x21/x22/x23/x27 are not-modelled registers. */
void FUN_0006b6c0(uint64_t base, uint64_t index, uint64_t a, uint64_t b, uint64_t c)
{
    *(uint64_t *)(base + 0x10) = a;
    uint64_t elem = base + index * 0x10;
    *(uint64_t *)(elem + 0x20) = b;
    *(uint64_t *)(elem + 0x28) = c;
}

/* FUN_0006b6d4 @ 0x0006b6d4   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b6d4(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b6d4(void)
{
}

/* FUN_0006b6e0 @ 0x0006b6e0   (est. sk_const_zero)
 * Ghidra: undefined8 FUN_0006b6e0(void)
 * Returns the constant 0.
 * Confidence: high */
uint64_t FUN_0006b6e0(void)
{
    return 0;
}

/* FUN_0006b6f4 @ 0x0006b6f4   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006b6f4(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006b6f4(void)
{
}

/* FUN_0006b700 @ 0x0006b700   (est. sk_string_emit_thunk)
 * Ghidra: void FUN_0006b700(void)
 * Emits the packed literal 0x2e2e2e ("...") with tag 0xe300000000000000.
 * Confidence: low */
void FUN_0006b700(void)
{
    FUN_002acbb8(0x2e2e2e, 0xe300000000000000ull);
}

/* FUN_0006b714 @ 0x0006b714   (est. sk_swift_global_init)
 * Ghidra: void FUN_0006b714(void)
 * Swift object-init for slot 0x64e080 with metadata DAT_004be930.
 * Confidence: low */
void FUN_0006b714(void)
{
    FUN_00002534(0x64e080, (uint64_t)&DAT_004be930[0]);
}

/* FUN_0006b728 @ 0x0006b728   (est. sk_swift_global_init)
 * Ghidra: void FUN_0006b728(void)
 * Swift object-init for slot 0x64e060 with metadata DAT_004be920.
 * Confidence: low */
void FUN_0006b728(void)
{
    FUN_00002534(0x64e060, (uint64_t)&DAT_004be920[0]);
}

/* FUN_0006b760 @ 0x0006b760   (est. sk_byte_getter)
 * Ghidra: undefined1 FUN_0006b760(void)
 * Returns the byte from FUN_00084dc8.
 * Confidence: low */
uint8_t FUN_0006b760(void)
{
    return FUN_00084dc8();
}

/* FUN_0006b764 @ 0x0006b764   (est. sk_byte_getter)
 * Ghidra: undefined1 FUN_0006b764(void)
 * Returns the byte from FUN_00084dc8 (dup of 6b760).
 * Confidence: low */
uint8_t FUN_0006b764(void)
{
    return FUN_00084dc8();
}

/* FUN_0006b77c @ 0x0006b77c   (est. sk_l4_err_msg_set)
 * Ghidra: void FUN_0006b77c(undefined8 param_1)
 * Stores param_1 into the 8 bytes at offset 6 of the L4 error-message string
 * at 0x68a4e8 (Ghidra `_6_8_` overlap write).
 * Confidence: low
 * Notes: string at DAT_0068a4e8; overlap-write artifact. */
void FUN_0006b77c(uint64_t param_1)
{
    *(uint64_t *)(DAT_0068a4e8 + 6) = param_1;
}

/* FUN_0006b78c @ 0x0006b78c   (est. sk_l4_err_msg_set)
 * Ghidra: void FUN_0006b78c(undefined8 param_1)
 * Stores param_1 into the 8 bytes at 0x68a4e6 (DAT_0068a4e6).
 * Confidence: low
 * Notes: overlapping smaller symbol DAT_0068a4e6. */
void FUN_0006b78c(uint64_t param_1)
{
    *(uint64_t *)DAT_0068a4e6 = param_1;
}

/* FUN_0006b79c @ 0x0006b79c   (est. sk_l4_err_msg_get)
 * Ghidra: undefined8 FUN_0006b79c(void)
 * Reads the 8 bytes at offset 6 of the L4 error-message string (0x68a4e8).
 * Confidence: low */
uint64_t FUN_0006b79c(void)
{
    return *(uint64_t *)(DAT_0068a4e8 + 6);
}

/* FUN_0006b7ac @ 0x0006b7ac   (est. sk_l4_err_msg_get)
 * Ghidra: undefined8 FUN_0006b7ac(void)
 * Reads the 8 bytes at 0x68a4e6 (DAT_0068a4e6).
 * Confidence: low */
uint64_t FUN_0006b7ac(void)
{
    return *(uint64_t *)DAT_0068a4e6;
}

/* FUN_0006b7bc @ 0x0006b7bc   (est. sk_ipmm_ready_mark)
 * Ghidra: void FUN_0006b7bc(void)
 * Runs the IPMM freelist init (FUN_0006b7e0) and sets the ready flag
 * DAT_006b27e0.
 * Confidence: medium */
void FUN_0006b7bc(void)
{
    FUN_0006b7e0();
    g_ipmm_ready = 1;
}

/* FUN_0006b7e0 @ 0x0006b7e0   (est. sk_ipmm_freelist_init)
 * Ghidra: void FUN_0006b7e0(void)
 * Initialises the launcher IPMM physical-memory manager. Allocates a 1 MB
 * cbootinfo arena (FUN_0006d240), snapshots the 26-entry launcher capability
 * table (FUN_0006cea4) into the freelist table at 0x6b2848, and records the
 * arena base/limit. On a re-entry (ipmm_ready already set) it re-arms the
 * freelist SVC frame (tpidrro_el0 block) and, if a leftover freelist pointer
 * exists, creates the launcher IPMM freelist cap and the zero-frame cap via
 * the cap-create IPC dispatch (selector 0x940 / 0x1808), mapping frames to
 * zero. Any failure aborts through FUN_0005b190 with an "IPMM abort in
 * function" message; on success bumps the bump-counter.
 * Confidence: high
 * Notes: tpidrro_el0 SVC frame; s_Creating_launcher_IPMM_freelist / zero_spa
 *   logs; SoftwareBreakpoint-free; canary local_38. */
void FUN_0006b7e0(void)
{
    long canary = SK_CANARY;
    uint64_t base = FUN_0006d240(0x100000, 0);
    uint64_t idx = 0;
    do {
        uint64_t v = FUN_0006cea4(idx);
        *(uint64_t *)(idx * 8 + 0x6b2848) = v;
        idx += 1;
    } while (idx != 0x1a);

    g_cboot_alloc_limit = base + 0x100000;
    g_cboot_alloc_base = base;

    if ((g_ipmm_ready & 1) != 0) {
        uint64_t frame = g_freelist_base + g_freelist_used * 0x40;
        /* SVC 0 with a 3-word block staged in the tpidrro_el0 frame
         * {0x11, base+0xfc000, frame}; the frame itself is not modelled. */
        CallSupervisor(0);
        uint64_t leftover = g_ipmm_unknown_28d0;
        if ((leftover & 0xff) != 0) {
            uint8_t stk[32];
            FUN_004b7ba0(leftover, stk);
            FUN_00118b94(s_Creating_launcher_IPMM_freelist_s_005bef67);
            /* Build the freelist cap-create message from the globals. */
            uint64_t msg[4];
            msg[0] = /* DAT_004beea0 */ 0;
            msg[1] = /* uRam004beea8 */ 0;
            msg[2] = /* DAT_004beeb0 */ 0;
            msg[3] = /* uRam004beeb8 */ 0;
            sk_u128_t arena = FUN_00034a2c();
            uint64_t (*op)(uint64_t, uint64_t, void *, void *, uint64_t, uint64_t) =
                (uint64_t (*)(uint64_t, uint64_t, void *, void *, uint64_t, uint64_t))(arena.hi + 0x30);
            char rc = (char)op(arena.lo, 0x940, msg, &g_freelist_handle, 0, 0);
            if (rc == 0) {
                if (g_freelist_vtable == 0)
                    FUN_00054354();
                (*(uint64_t (*)(uint64_t, uint64_t))(g_freelist_vtable + 8))(
                    g_freelist_handle, 0x6b2800);
                g_freelist_count = 0;
                g_freelist_used = 0;
                FUN_00118b94(s_Creating_launcher_frame_zero_spa_005bef8c);
                uint64_t msg2[4];
                msg2[0] = 0x11;
                msg2[1] = /* uRam004bee98 */ 0;
                msg2[2] = /* DAT_004bee90 */ 0;
                msg2[3] = 10;
                sk_u128_t arena2 = FUN_00034a2c();
                uint64_t (*op2)(uint64_t, uint64_t, void *, void *, uint64_t, uint64_t) =
                    (uint64_t (*)(uint64_t, uint64_t, void *, void *, uint64_t, uint64_t))(arena2.hi + 0x30);
                rc = (char)op2(arena2.lo, 0x1808, msg2, &g_zero_handle, 0, 0);
                if (rc == 0) {
                    if (g_zero_vtable == 0)
                        FUN_00054354();
                    (*(uint64_t (*)(uint64_t, void *))(g_zero_vtable + 8))(
                        g_zero_handle, msg2);
                    g_zero_frame_size = /* uStack_98 */ 0;
                    g_zero_frames_active = 1;
                    g_l4_err_msg = 1;
                    uint64_t frame_cap = FUN_0019ae2c(0x11);
                    rc = (char)(*(uint64_t (*)(uint64_t, uint64_t, uint64_t))(
                        g_zero_vtable + 0x28))(g_zero_handle, 0, frame_cap);
                    if (rc == 0) {
                        FUN_0019ae60(frame_cap, 0x11);
                        if (canary == SK_CANARY)
                            return;
                        FUN_0011d7e8();
                    }
                    FUN_0005b190(0, s__ipmm_abort_in_function__s_line_005beafe);
                }
                FUN_0005b190(0, s__ipmm_abort_in_function__s_line_005bea28);
            }
            FUN_0005b190(0, s__ipmm_abort_in_function__s_line_005be94d);
        }
        FUN_004b7bec(frame);
    }
    g_ipmm_bump_count += 1;
    if (canary == SK_CANARY)
        return;
    FUN_0011d7e8();
}

/* FUN_0006bb34 @ 0x0006bb34   (est. sk_ipmm_stats_log)
 * Ghidra: void FUN_0006bb34(void)
 * Logs two IPMM diagnostic strings: "ipmm: 0x.. bytes left" and
 * "ipmm: bumped %zu times".
 * Confidence: medium
 * Notes: s__ipmm___0x_llx_bytes_left / s__ipmm___bumped__zd_times. */
void FUN_0006bb34(void)
{
    FUN_00118b28(s__ipmm___0x_llx_bytes_left_005beb77);
    FUN_00118b28(s__ipmm___bumped__zd_times_005beb92);
}

/* FUN_0006bb8c @ 0x0006bb8c   (est. sk_ipmm_bump_count_get)
 * Ghidra: undefined8 FUN_0006bb8c(void)
 * Returns the IPMM bump counter (DAT_006b2928).
 * Confidence: high */
uint64_t FUN_0006bb8c(void)
{
    return g_ipmm_bump_count;
}

/* FUN_0006bb98 @ 0x0006bb98   (est. sk_ipmm_alloc_count_get)
 * Ghidra: undefined8 FUN_0006bb98(void)
 * Returns the IPMM frame-allocation counter (DAT_006b2930).
 * Confidence: high */
uint64_t FUN_0006bb98(void)
{
    return g_ipmm_alloc_count;
}

/* FUN_0006bba4 @ 0x0006bba4   (est. sk_ipmm_freed_count_get)
 * Ghidra: undefined8 FUN_0006bba4(void)
 * Returns the IPMM freed-frame counter (DAT_006b2938).
 * Confidence: high */
uint64_t FUN_0006bba4(void)
{
    return g_ipmm_freed_count;
}

/* FUN_0006bbb0 @ 0x0006bbb0   (est. sk_l4_error_descriptor_fill)
 * Ghidra: void FUN_0006bbb0(undefined8 *param_1, byte param_2)
 * Fills a 4-word L4_ErrorCode descriptor from the per-code string/struct
 * table for codes 0..9 (each a 32-byte record at offsets 0/8/0x10/0x18). For
 * codes above 9 it copies the generic words DAT_004bf000/008/010/018 and
 * formats an "L4_ErrorCode: %zu" message via FUN_0006bcc0.
 * Confidence: medium
 * Notes: s_L4_ErrorCode*_004be* string table. */
void FUN_0006bbb0(uint64_t *param_1, uint8_t param_2)
{
    const char *pc;
    if (9 < param_2) {
        param_1[0] = DAT_004bf000;
        param_1[1] = DAT_004bf008;
        param_1[2] = DAT_004bf010;
        param_1[3] = DAT_004bf018;
        FUN_0006bcc0((uint64_t)param_1);
        return;
    }
    switch (param_2) {
    case 0: pc = s_L4_ErrorCodeSuccess_004beec0; break;
    case 1: pc = s_L4_ErrorCodePreempted_004beee0; break;
    case 2: pc = s_L4_ErrorCodeCanceled_004bef00; break;
    case 3: pc = s_L4_ErrorCodeTruncated_004bef20; break;
    case 4: pc = s_L4_ErrorCodeCapInvalid_004bef40; break;
    case 5: pc = s_L4_ErrorCodeSlotInvalid_004bef60; break;
    case 6: pc = s_L4_ErrorCodeMethodInvalid_004bef80; break;
    case 7: pc = s_L4_ErrorCodeArgumentInvalid_004befa0; break;
    case 8: pc = s_L4_ErrorCodeOperationInvalid_004befc0; break;
    default: pc = s_L4_ErrorCodePermissionInvalid_004befe0; break;
    }
    param_1[0] = *(uint64_t *)(pc + 0);
    param_1[1] = *(uint64_t *)(pc + 8);
    param_1[2] = *(uint64_t *)(pc + 0x10);
    param_1[3] = *(uint64_t *)(pc + 0x18);
}

/* FUN_0006bcc0 @ 0x0006bcc0   (est. sk_l4_error_unknown_format)
 * Ghidra: void FUN_0006bcc0(undefined8 param_1)
 * Formats the "L4_ErrorCode: %zu" message for an out-of-range code via
 * FUN_00116bb4.
 * Confidence: medium
 * Notes: s_L4_ErrorCode__zu_005a8c7b. */
void FUN_0006bcc0(uint64_t param_1)
{
    uint64_t buf = 0;
    FUN_00116bb4(param_1, 0x1f, s_L4_ErrorCode__zu_005a8c7b, &buf);
}

/* FUN_0006bcf8 @ 0x0006bcf8   (est. sk_ipmm_frame_alloc)
 * Ghidra: undefined8 FUN_0006bcf8(param_1,param_2,param_3,param_4,param_5)
 * Allocates a physical frame from the launcher IPMM arena. Flags (param_5)
 * must be 0 or 2. Type param_3==5 returns 0x107. For memory type param_2
 * 0x11 with a non-empty freelist, pops a recycled frame; otherwise bumps the
 * 0x4000-granule cbootinfo arena (per-type cursors: 6→+0x800, 7→+0x40,
 * 8→+0x40, 4/0x11→full granule) and creates the untyped frame via SVC 0
 * (with the frame,type staged in the tpidrro_el0 block). If type 0x11 and
 * zero-frames are active, maps the frame to zero. Invalid type or exhausted
 * arena aborts with an "ipmm: Operation Invalid / unexpected PMM allocation"
 * panic; smaller errors funnel through FUN_004b7cd4/FUN_004b7e64/FUN_004b7dec
 * returning 0.
 * Confidence: medium
 * Notes: s_unexpected_PMM_allocation_type / s_Failed_to_map_frame_to_zero /
 *   s_Failed_to_create_untyped / s__ipmm___Operation_Invalid__Wrong. */
uint64_t FUN_0006bcf8(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                      uint64_t param_4, uint32_t param_5)
{
    long canary = SK_CANARY;
    uint64_t uVar4;
    uint64_t uVar5;
    const char *pcVar6;
    uint8_t stk[32];

    if ((param_5 & 0xfffffffd) != 0) {
        pcVar6 = s_unexpected_PMM_allocation_type_005becb2;
        goto abort_panic;
    }
    CallSupervisor(1);
    if (param_3 == 5) {
        uVar4 = 0x107;
        uVar5 = 5;
        goto check_canary;
    }
    if ((param_3 & 0xfb) == 0) {
        int mtype = (int)param_2;
        uVar5 = param_3;
        /* Recycle a freed frame when the freelist is non-empty. */
        if ((mtype == 0x11) && (g_freelist_used != 0)) {
            g_freelist_used -= 1;
            uint64_t frame = g_freelist_base + g_freelist_used * 0x40;
            uVar5 = 0;
            if (frame == 0)
                goto arena_alloc;
            CallSupervisor(1);
            uVar5 = param_4;
            if ((frame & 0xff) != 0) {
                sk_u128_t page = FUN_004b7c88(frame, stk);
                param_3 = page.hi;
                uVar5 = page.lo;
                goto arena_alloc;
            }
zero_map:
            if ((mtype == 0x11) && ((g_zero_frames_active & 1) != 0)) {
                char rc = (char)(*(uint64_t (*)(uint64_t, uint64_t, uint64_t))(
                    g_zero_vtable + 0x28))(g_zero_handle, 0, param_4);
                if (rc != 0) {
                    pcVar6 = s_Failed_to_map_frame_to_zero_005bed6a;
                    goto abort_panic;
                }
                FUN_004b7d20(param_4, stk);
                uVar5 = 0;                /* extraout_x1_00 */
            }
            uVar4 = 0;
            g_ipmm_alloc_count += 1;
check_canary:
            if (canary == SK_CANARY)
                return uVar4;
            FUN_0011d7e8(uVar4, uVar5);
        }
arena_alloc:
        uint64_t uVar8 = 0x6b2000;
        uint64_t uVar1 = g_cboot_alloc_base + 0x4000;
        if (g_cboot_alloc_base < 0xffffffffffffc000ull) {
            if (g_cboot_alloc_limit < uVar1) {
                FUN_0006b7e0();
                if (g_cboot_alloc_limit < uVar1)
                    goto funnel_end;
            }
            if (mtype < 8) {
                if (mtype == 4)
                    goto full_granule;
                if (mtype == 6) {
                    uVar5 = g_alloc_cursor_small;
                    if ((g_alloc_cursor_small & 0x3fff) == 0) {
                        uVar5 = g_cboot_alloc_base;
                        g_cboot_alloc_base += 0x4000;
                    }
                    g_alloc_cursor_small = uVar5 + 0x800;
                    goto do_svc;
                }
                if (mtype == 7) {
                    if ((g_alloc_cursor_32b & 0x3fff) == 0) {
                        g_alloc_cursor_32b = g_cboot_alloc_base;
                        g_cboot_alloc_base += 0x4000;
                    }
                    uVar5 = g_alloc_cursor_32b;
                    g_alloc_cursor_32b += 0x40;
                    goto do_svc;
                }
            } else {
                if (2 < (unsigned)(mtype - 0xc)) {
                    if (mtype == 8) {
                        uVar5 = g_alloc_cursor_32b2;
                        if ((g_alloc_cursor_32b2 & 0x3fff) == 0) {
                            uVar5 = g_cboot_alloc_base;
                            g_cboot_alloc_base += 0x4000;
                        }
                        g_alloc_cursor_32b2 = uVar5 + 0x40;
                        goto do_svc;
                    }
                    if (mtype != 0x11)
                        goto op_invalid;
                }
full_granule:
                uVar5 = g_cboot_alloc_base;
                g_cboot_alloc_base += 0x4000;
do_svc:
                if (uVar5 != 0xffffffffffffffffull) {
                    uVar8 = *(uint64_t *)((param_2 & 0xffffffff) * 8 + 0x6b2848);
                    /* SVC 0: create untyped frame; {type, frame, param_4}
                     * staged in tpidrro_el0 block. */
                    CallSupervisor(0);
                    if (uVar8 != 0) {
                        FUN_00055a90(param_2, 0);
                        FUN_00118b28(s_Failed_to_create_untyped__type_005bedf1);
                        if ((uVar8 & 0xff) != 0)
                            goto funnel_cd4;
                    }
                    goto zero_map;
                }
            }
op_invalid:
            FUN_00055a90(param_2, 0);
            pcVar6 = s__ipmm___Operation_Invalid__Wrong_005bedc5;
abort_panic:
            FUN_0005b190(0, pcVar6);    /* noreturn */
        }
        FUN_004b7008(uVar5, param_3);
funnel_cd4:
        param_3 = FUN_004b7cd4(uVar8, stk);
    }
    FUN_004b7e64(param_3, stk);
funnel_end:
    FUN_004b7dec(stk);
    return 0;
}

/* FUN_0006bfe4 @ 0x0006bfe4   (est. sk_ipmm_freed_frame_map)
 * Ghidra: void FUN_0006bfe4(undefined8 param_1, ulong param_2)
 * Maps a freed frame back into the launcher. If zero-frames are not active,
 * falls back to the launcher-alloc getter (FUN_004b7eb0) and aborts. Counts
 * the freed frame, bumps the freelist when fewer than 2 slots remain, then
 * re-arms the SVC frame for the next freed frame. Type param_2==4 returns
 * 0x107. For type 0, maps the frame to zero (SVC 0 + zero-frame cap) and
 * succeeds; otherwise routes through the frame-map funnels FUN_004b7edc/
 * FUN_004b7f24/FUN_004b7f6c. Any failure aborts with a "Failed to map frame
 * freed frame" panic.
 * Confidence: medium
 * Notes: s_Failed_to_bump_freelist / s_Failed_to_map_frame_freed_frame. */
void FUN_0006bfe4(uint64_t param_1, uint64_t param_2)
{
    long canary = SK_CANARY;
    uint64_t uVar3;
    uint64_t uVar4;
    const char *pcVar5;
    uint64_t local_48[4];

    if ((g_zero_frames_active & 1) == 0) {
        uVar3 = FUN_004b7eb0();
        FUN_0011d7e8(uVar3);
    }
    g_ipmm_freed_count += 1;
    CallSupervisor(1);
    if ((param_2 & 0xff) == 4) {
        uVar3 = 0x107;
        if (canary == SK_CANARY)
            return;
        FUN_0011d7e8(uVar3);
    }
    if (g_freelist_count - g_freelist_used < 2) {
        local_48[0] = g_freelist_count * 0x40 + 0x4000;
        char rc = (char)(*(uint64_t (*)(uint64_t, void *))(g_freelist_vtable + 0x18))(
            g_freelist_handle, local_48);
        if (rc != 0) {
            pcVar5 = s_Failed_to_bump_freelist_005bee58;
            goto abort_panic;
        }
        g_freelist_count = local_48[0] >> 6;
    }
    uVar4 = g_freelist_base + g_freelist_used * 0x40;
    CallSupervisor(1);
    if ((param_2 & 0xff) == 0) {
        do {
            CallSupervisor(5);
        } while (uVar4 == 1);
        if ((uVar4 & 0xff) != 0)
            goto funnel_f24;
        /* SVC 0: map the freed frame to zero. */
        CallSupervisor(0);
        if ((uVar4 & 0xff) != 0)
            goto funnel_f6c;
        char rc = (char)(*(uint64_t (*)(uint64_t, uint64_t, uint64_t))(
            g_zero_vtable + 0x28))(g_zero_handle, 0, uVar4);
        if (rc == 0) {
            FUN_004b7fb4(uVar4, local_48);
            uVar3 = 0;
            if (canary == SK_CANARY)
                return;
            FUN_0011d7e8(uVar3);
        }
    } else {
        uVar4 = FUN_004b7edc(param_2, local_48);
funnel_f24:
        uVar4 = FUN_004b7f24(uVar4, local_48);
funnel_f6c:
        FUN_004b7f6c(uVar4, local_48);
    }
    pcVar5 = s_Failed_to_map_frame_freed_frame_005bef47;
abort_panic:
    FUN_0005b190(0, pcVar5);            /* noreturn */
}

/* FUN_0006c1b4 @ 0x0006c1b4   (est. sk_l4_error_desc_tail)
 * Ghidra: void FUN_0006c1b4(void)
 * Fills an L4 error descriptor at a stack buffer (param_2 register-passed).
 * Confidence: low
 * Notes: param_2 (register) not modelled; passed as 0. */
void FUN_0006c1b4(void)
{
    uint64_t buf[4] = { 0 };
    FUN_0006bbb0(buf, 0);
}

/* FUN_0006c1d4 @ 0x0006c1d4   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006c1d4(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006c1d4(void)
{
}

/* FUN_0006c1e8 @ 0x0006c1e8   (est. sk_l4_error_desc_tail)
 * Ghidra: void FUN_0006c1e8(void)
 * Fills an L4 error descriptor at a stack buffer (param_2 register-passed).
 * Confidence: low
 * Notes: param_2 (register) not modelled; passed as 0. */
void FUN_0006c1e8(void)
{
    uint64_t buf[4] = { 0 };
    FUN_0006bbb0(buf, 0);
}

/* FUN_0006c208 @ 0x0006c208   (est. sk_l4_error_desc_tail)
 * Ghidra: void FUN_0006c208(void)
 * Fills an L4 error descriptor at a stack buffer (param_2 register-passed).
 * Confidence: low
 * Notes: param_2 (register) not modelled; passed as 0. */
void FUN_0006c208(void)
{
    uint64_t buf[4] = { 0 };
    FUN_0006bbb0(buf, 0);
}

/* FUN_0006c214 @ 0x0006c214   (est. sk_noop_thunk)
 * Ghidra: void FUN_0006c214(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void FUN_0006c214(void)
{
}

/* FUN_0006c228 @ 0x0006c228   (est. sk_vspace_table_arm)
 * Ghidra: void FUN_0006c228(undefined1 param_1)
 * Stores the client id byte into slot 0x64e1a0 and marks the vspace table
 * ready (DAT_006b2958 = 1).
 * Confidence: medium */
void FUN_0006c228(uint8_t param_1)
{
    g_slot_64e1a0 = param_1;
    g_vspace_table_ready = 1;
}

/* FUN_0006c244 @ 0x0006c244   (est. sk_vspace_table_find)
 * Ghidra: void FUN_0006c244(short param_1)
 * Searches the vspace-table client list (DAT_006ad980 head, 16-byte nodes,
 * next pointer at +0x10) for a node whose leading short equals param_1.
 * Aborts with "vspace table not ready yet" if the table is not armed.
 * Confidence: medium
 * Notes: s___s__vspace_table_not_ready_yet_005befc4. */
uint16_t *FUN_0006c244(uint16_t param_1)
{
    if (g_vspace_table_ready == 0)
        FUN_0005b190(0, s___s__vspace_table_not_ready_yet_005befc4);
    uint16_t *node = g_vspace_head;
    for (; node != NULL && *node != param_1; node = *(uint16_t **)(node + 0x10)) {
    }
    return node;
}

/* FUN_0006c2b0 @ 0x0006c2b0   (est. sk_vspace_table_insert)
 * Ghidra: undefined8 FUN_0006c2b0(long param_1)
 * Inserts a new vspace-table node keyed by param_1 into the singly/doubly
 * linked client list (DAT_006ad980). Allocates a 0x30-byte node
 * (FUN_00010244, tag 0xda02648f), seeds its 16-bit key fields (0xaa00 /
 * 0xaa01 markers), and links it at the head (or after the head when the list
 * is non-empty via the +0x28 back-link). Returns the node marker
 * 0xffffaa00 on success; aborts "vspace table not ready yet" if unarmed.
 * Confidence: medium
 * Notes: FUN_004b808c on list-integrity failure; s_L4_failed_on__s__d___s. */
uint64_t FUN_0006c2b0(long param_1)
{
    if (g_vspace_table_ready != 0) {
        if (param_1 == 0)
            FUN_0005b190(0, s_L4_failed_on__s__d___s_005bf00c);
        uint16_t *node = (uint16_t *)FUN_00010244(0x30, 1, 0xda02648f);
        node[0] = 0xaa00;
        g_slot_64e1a2 = 0xaa01;
        if (g_vspace_head == NULL) {
            *(uint16_t **)((uint8_t *)node + 0x20) = NULL;      /* next @ +0x20 */
            g_vspace_head = node;
            *(uint16_t ***)((uint8_t *)node + 0x28) = &g_vspace_head; /* prevp @ +0x28 */
            *(long *)((uint8_t *)node + 0x18) = param_1;        /* key @ +0x18 */
            return 0xffffaa00;
        }
        if (*(uint16_t ***)((uint8_t *)g_vspace_head + 0x28) == &g_vspace_head) {
            *(uint16_t **)((uint8_t *)node + 0x20) = g_vspace_head;
            *(uint16_t ***)((uint8_t *)g_vspace_head + 0x28) =
                (uint16_t **)((uint8_t *)node + 0x20);
            g_vspace_head = node;
            *(uint16_t ***)((uint8_t *)node + 0x28) = &g_vspace_head;
            *(long *)((uint8_t *)node + 0x18) = param_1;
            return 0xffffaa00;
        }
        FUN_004b808c();
    }
    FUN_0005b190(0, s___s__vspace_table_not_ready_yet_005befc4);
}

/* FUN_0006c3c8 @ 0x0006c3c8   (est. sk_vspace_table_ensure_ready)
 * Ghidra: void FUN_0006c3c8(void)
 * If the vspace table is armed, runs the flush thunk FUN_00012568; otherwise
 * aborts "vspace table not ready yet".
 * Confidence: medium */
void FUN_0006c3c8(void)
{
    if (g_vspace_table_ready != 0) {
        FUN_00012568();
        return;
    }
    FUN_0005b190(0, s___s__vspace_table_not_ready_yet_005befc4);
}

/* FUN_0006c404 @ 0x0006c404   (est. sk_vspace_table_client_get)
 * Ghidra: undefined8 FUN_0006c404(void)
 * Looks up the current client in the vspace table (FUN_0006c244) and returns
 * its +0x18 field, or 0 if absent. Aborts if the table is not armed.
 * Confidence: medium */
uint64_t FUN_0006c404(void)
{
    if (g_vspace_table_ready != 0) {
        uint16_t *node = FUN_0006c244(0);
        if (node != NULL)
            return *(uint64_t *)((uint8_t *)node + 0x18);
        return 0;
    }
    FUN_0005b190(0, s___s__vspace_table_not_ready_yet_005befc4);
}

/* FUN_0006c454 @ 0x0006c454   (est. sk_vspace_table_remove)
 * Ghidra: undefined8 FUN_0006c454(void)
 * Removes the current client node from the vspace-table list. Locates the
 * node via FUN_0006c244, validates the doubly-linked list integrity
 * (FUN_001150e0 "Bad link" panics), unlinks it, and if it was the head calls
 * the flush thunk FUN_00012568 and returns 0. Returns 3 if the node was not
 * found; aborts on list corruption or an unarmed table.
 * Confidence: medium
 * Notes: s_expected_client_to_be_in_list / s_Bad_link_elm. */
uint64_t FUN_0006c454(void)
{
    if (g_vspace_table_ready != 0) {
        uint16_t *node = FUN_0006c244(0);
        if (node == NULL)
            return 3;
        uint16_t key = *node;
        uint16_t *p = FUN_0006c244(key);
        if (p == NULL)
            FUN_0005b190(0, s_expected_client_to_be_in_list_005bf1c8);
        uint64_t next = *(uint64_t *)((uint8_t *)p + 0x20);   /* next @ +0x20 */
        uint64_t *prevp;
        if (next == 0) {
            prevp = *(uint64_t **)((uint8_t *)p + 0x28);      /* prevp @ +0x28 */
            if ((uint16_t *)*prevp != p)
                FUN_001150e0(s_Bad_link_elm__p_prev_005bf20c);
        } else {
            if (*(uint64_t **)(next + 0x28) != (uint64_t *)((uint8_t *)p + 0x20))
                FUN_001150e0(s_Bad_link_elm__p_next_005bf1e6);
            if ((uint16_t *)**(uint64_t **)((uint8_t *)p + 0x28) != p)
                FUN_001150e0(s_Bad_link_elm__p_prev_005bf20c);
            *(uint64_t **)(next + 0x28) = *(uint64_t **)((uint8_t *)p + 0x28);
            prevp = *(uint64_t **)((uint8_t *)p + 0x28);
        }
        *prevp = next;
        if (*node == key) {                     /* removed the head */
            FUN_00012568();
            return 0;
        }
        FUN_0005b190(0, s_L4_failed_on__s__d___s_005bf00c);
    }
    FUN_0005b190(0, s___s__vspace_table_not_ready_yet_005befc4);
}

/* FUN_0006c5cc @ 0x0006c5cc   (est. sk_cbootinfo_parse)
 * Ghidra: void FUN_0006c5cc(long *param_1, int param_2)
 * Parses the launcher's cbootinfo capability array (a linked list of pages
 * anchored at param_1) into the global untyped-region / DART / segment /
 * roottask tables. For each page and each cap it dispatches on the cap type
 * tag (high byte): untyped (3), frame (7), NULL (0), DART (via type-id
 * matches to FUN_000552a4/55328/55344), TEXT/DATA segment (10), and records
 * phys-hints and the roottask slide. It also maps the __TEXT/__DATA Mach-O
 * segments (FUN_00051e5c) to compute the roottask data/text bounds, then
 * builds the untyped-region registry (stride 0x2e8 at DAT_006b2960). A
 * 1 GB-range roottask-slice gate updates the high globals. On success logs
 * "Roottask slide is 0x..". Numerous bounds/integrity failures route to the
 * FUN_004b8xxx error funnel and abort.
 * Confidence: medium
 * Notes: s_CBootInfo_found_DART / s_CBootInfo_found_DART_Table /
 *   s___Warning__Unexpected_null_cap_in / s_Roottask_slide_is_0x_llx. */
void FUN_0006c5cc(long *param_1, int param_2)
{
    long canary = SK_CANARY;
    uint32_t uVar9, uVar10, uVar11, uVar24, uVar23;
    uint64_t uVar15 = 0, uVar17, uVar19, uVar22;
    uint8_t stk[32];

    g_cboot_chain_head = (uint64_t)param_1;
    if (g_cboot_unknown_898 != 0) {
        g_phys_hint_a = FUN_00055718();
        g_phys_hint_b = FUN_0005574c(g_cboot_unknown_898);
        g_phys_hints_valid = g_phys_hint_a != 0 && g_phys_hint_b != 0;
    }
    uVar9 = (uint32_t)FUN_000552a4();
    uVar10 = (uint32_t)FUN_00055328();
    uVar11 = (uint32_t)FUN_00055344();
    uVar24 = (uint32_t)g_untyped_count;
    g_untyped_count = g_untyped_scan_idx;   /* _DAT_006be8b4 = _DAT_006be8e8 */

    for (long *page = param_1; g_untyped_scan_idx = g_untyped_count,
         page != (long *)0xffffffffffffffffull; page = (long *)page[1]) {
        uint64_t ncap = *page;
        if (ncap != 0) {
            uint64_t c = 0;
            for (;;) {
                g_untyped_count = uVar24;
                uint64_t *cap = (uint64_t *)(page + c * 4 + 4);
                uint8_t tag = (uint8_t)(*cap >> 0x38);
                if (tag == 0xb) {
                    /* kind 11: some frame/region marker */
                    g_slot_64e1b0 = (uint8_t)(*cap & 0xffffffffffffffull);
                } else if (tag == 0x3) {
                    /* untyped region cap */
                    uint64_t szbits = cap[1];
                    uint64_t phys  = cap[2];
                    uint64_t base  = (szbits & 0xfffffffffff) << 0xc;
                    FUN_00118b28(s_untyped___base_0x_016llx__size_0_005bf4e3, uVar15);
                    uVar24 = (uint32_t)g_untyped_scan_idx;
                    uint64_t ri = (uint64_t)g_untyped_scan_idx;
                    if (0x3f < g_untyped_scan_idx) {
                        FUN_004b8288();
                        goto err_funnel_a;
                    }
                    uVar15 = 0;
                    if (g_phys_hints_valid == 1) {
                        if (base == g_phys_hint_a)
                            g_phys_hint_a_cap = *cap & 0xffffffffffffffull;
                        else if (base == g_phys_hint_b)
                            g_phys_hint_b_cap = *cap & 0xffffffffffffffull;
                    }
                    g_untyped_scan_idx += 1;
                    uint64_t off = ri * 0x2e8;
                    uint64_t *rt = (uint64_t *)(off + 0x6b2960);      /* region rec */
                    *rt = *cap & 0xffffffffffffffull;
                    /* zero the ~0x100-byte region record */
                    for (int k = 1; k <= 0x5c; k++) rt[k] = 0;
                    rt[0x5c] = szbits >> 0x2c & 0xff;                  /* type */
                    *(uint64_t *)(off + 0x6b2b10) = base;             /* base */
                    *(uint64_t *)(off + 0x6b2b18) = (phys & 0xfffffffffff) << 0xc; /* size */
                    *(uint64_t *)(off + 0x6b2b38) = cap[3];
                    if ((szbits & 0xff00000000000) != 0) {
                        uVar23 = (uint32_t)(cap[1] >> 0x2c) & 0xff;
                        if (uVar23 == 3) {
                            g_slot_64e1b0 = (uint8_t)uVar24;
                        } else if (uVar23 == 2) {
                            g_slot_64e1ac = (uint8_t)uVar24;
                        } else if (uVar23 == 1) {
                            g_slot_64e1a4 = (uint8_t)uVar24;
                            if (param_2 != 0) {
                                /* replicate untyped pages via SVC 3/2 */
                                uint64_t p3 = cap[3];
                                uint64_t p1 = FUN_000537c4();
                                uint64_t p2 = FUN_000537c4();
                                uint64_t p0 = *cap;
                                CallSupervisor(3);
                                if ((*cap & 0xff) == 0) {
                                    CallSupervisor(2);
                                    if ((p1 & 0xff) == 0) {
                                        uint64_t pi = 0;
                                        uint64_t x0 = 0, x1 = 0;
                                        uint64_t *dst = (uint64_t *)(off + 0x6b2a38);
                                        do {
                                            if (pi == 0x11) {
                                                x0 = FUN_000537c4();
                                                x1 = FUN_000537c4();
                                                uint64_t c0 = *cap;
                                                CallSupervisor(3);
                                                if ((c0 & 0xff) != 0) goto err_funnel_b;
                                                CallSupervisor(2);
                                                if ((x0 & 0xff) != 0) goto err_funnel_c;
                                            } else {
                                                bool b = (p3 & 0xfffffffffffdffffull
                                                          & (uint64_t)(1u << ((uint32_t)pi & 0x1f))) != 0;
                                                x0 = b ? p1 : 0;
                                                x1 = b ? p2 : 0;
                                            }
                                            dst[-0x1a] = x0;
                                            *dst = x1;
                                            pi += 1;
                                            dst += 1;
                                        } while (pi != 0x1a);
                                        goto next_cap;
                                    }
                                    goto err_funnel_d;
                                }
                                goto err_funnel_e;
                            }
                        }
                        /* clear base/size for non-replicated kinds */
                        *(uint64_t *)(off + 0x6b2b10) = 0;
                        *(uint64_t *)(off + 0x6b2b18) = 0;
                    }
                }
next_cap:
                c += 1;
                uVar24 = (uint32_t)g_untyped_count;
                if (c == ncap)
                    break;
            }
            g_untyped_count = uVar24;
            uVar24 = (uint32_t)g_untyped_count;
            g_untyped_count = g_untyped_scan_idx;
        }
    }

    if (0x40 < g_untyped_count)
        goto err_funnel_f;
    long *lc = (long *)FUN_0005ba14();
    if ((lc == NULL) || (lc[7] == 0) || (*lc != 0))
        goto err_funnel_g;
    uint64_t text = FUN_00051e5c(lc[7], s___TEXT_005bb905);
    uint64_t data = FUN_00051e5c(lc[7], s___DATA_005bb23b);
    if ((text != 0) && (data != 0)) {
        g_seg_text_end = g_image_base + *(long *)(text + 0x18);
        g_seg_data_end = *(long *)(data + 0x18) + g_image_base;
        for (long *page = param_1; page != (long *)0xffffffffffffffffull;
             page = (long *)page[1]) {
            uint64_t ncap = *page;
            if (ncap != 0) {
                uint64_t c = 0;
                do {
                    uint64_t *cap = (uint64_t *)(page + c * 4 + 4);
                    uint64_t w = *cap;
                    uint8_t tag = (uint8_t)(w >> 0x38);
                    uint32_t t = (uint32_t)tag;
                    if (tag < 7) {
                        if (tag == 0) {
                            FUN_00118b94(s___Warning__Unexpected_null_cap_in_005bfa04);
                            continue;
                        }
                        if (t != 3) {
                            if (t != 6)
                                goto cap_done;
                            g_cboot_cap_kind6 = w & 0xffffffffffffffull;
                            goto cap_done;
                        }
                        /* untyped region already recorded */
                        if ((((cap[1] & 0xff00000000000) == 0) &&
                             (g_untyped_count != 0xf100001f))) {
                            uint64_t base = (cap[1] & 0xfffffffffff) << 0xc;
                            if (g_cboot_heap + g_cboot_heap_size == base) {
                            if (g_untyped_count == 0)
                                uVar17 = 0;
                            else {
                                uint64_t i2 = 0;
                                long *sz = (long *)&g_untyped_size[0];
                                do {
                                    if (((uint64_t)sz[-1] <= base) &&
                                        (uVar17 = i2, base < (uint64_t)(*sz + sz[-1])))
                                        break;
                                    i2 += 1;
                                    sz += 0x5d;
                                    uVar17 = (uint64_t)g_untyped_count;
                                } while (g_untyped_count != i2);
                            }
                            g_slot_64e1a8 = (uint8_t)uVar17;
                            if (g_untyped_count <= g_slot_64e1a8)
                                g_slot_64e1a8 = (uint8_t)g_untyped_count;
                            }
                        }
cap_done:
                        uint64_t seg = (cap[2] & 0xffffffffff) << 0xc;
                        if (seg == g_seg_text_end)
                            g_seg_text_cap = cap[1] & 0xffffffffffffffull;
                        if (seg == g_seg_data_end)
                            g_seg_data_cap = cap[1] & 0xffffffffffffffull;
                    } else {
                        if (t - 0xd < 5)
                            goto cap_done;
                        if (tag == 7) {
                            g_cboot_cap_kind7 = w & 0xffffffffffffffull;
                            goto cap_done;
                        }
                        if (tag == 10) {
                            if ((cap[2] & 0xffe0) != 0)
                                goto err_funnel_a;
                            *(uint64_t *)((cap[2] & 0x1f) * 8 + 0x6be360) =
                                w & 0xffffffffffffffull;
                            goto cap_done;
                        }
                        if (uVar9 == t) {
                            g_cboot_cap_found = w & 0xffffffffffffffull;
                            goto cap_done;
                        }
                        if (uVar10 == t) {
                            if (0x1f < g_dart_count)
                                goto err_funnel_h;
                            uint64_t off = g_dart_count * 0x10;
                            g_dart_sid[g_dart_count * 4 + 1] = FUN_0005537c(cap);
                            g_dart_sid[g_dart_count * 4 + 2] = FUN_000553b0(cap);
                            FUN_00118b28(s_CBootInfo_found_DART_with_sid_005bf967);
                            g_dart_cap[g_dart_count * 2] = *cap & 0xffffffffffffffull;
                            g_dart_count += 1;
                            /* bump the DART record counter (0x6b2960+0xbd00) */
                            *(uint64_t *)((uint8_t *)&g_untyped_tab[0] + 0xbd00) += 1;
                            goto cap_done;
                        }
                        if ((uVar11 == t) && (FUN_000554bc(cap) != 0)) {
                            if (0x1f < g_dart_table_count)
                                goto err_funnel_i;
                            uint64_t off = g_dart_table_count * 0x10;
                            g_dart_table_sid[g_dart_table_count * 4 + 1] = FUN_000554f0(cap);
                            g_dart_table_sid[g_dart_table_count * 4 + 2] = FUN_00055524(cap);
                            FUN_00118b28(s_CBootInfo_found_DART_Table_with_s_005bf9d2);
                            g_dart_table_cap[g_dart_table_count * 2] = *cap & 0xffffffffffffffull;
                            g_dart_table_count += 1;
                            /* bump the DART-table record counter (0x6b2960+0xbf08) */
                            *(uint64_t *)((uint8_t *)&g_untyped_tab[0] + 0xbf08) += 1;
                        }
                    }
cap_done2:
                    c += 1;
                } while (c != ncap);
            }
        }
        if (0xf100001f < g_untyped_count) {
            g_cboot_heap = 0;
            g_cboot_heap_size = g_cboot_heap_size + 0;   /* _DAT_2bc686b8550 = _DAT_2bc686b8530 */
        }
        FUN_00118b28(s_Roottask_slide_is_0x_llx_005a8b16);
        if (canary == SK_CANARY)
            return;
        goto canary_fail;
    }
    uVar17 = FUN_004b8338();
err_funnel_e:
    uVar22 = FUN_004b81e8(uVar17, stk);
err_funnel_d:
    uVar22 = FUN_004b8238(uVar22, stk);
err_funnel_c:
    uVar17 = FUN_004b8148(uVar22, stk);
err_funnel_b:
    FUN_004b8198(uVar17, stk);
canary_fail:
    FUN_0011d7e8();
err_funnel_a:
    FUN_004b82b4();
err_funnel_h:
    FUN_004b830c();
err_funnel_g:
    FUN_004b8364();
err_funnel_i:
    FUN_004b82e0();
    uVar24 = (uint32_t)g_untyped_count;
err_funnel_f:
    g_untyped_count = uVar24;
    FUN_004b8390();
    goto err_funnel_e;
}

/* FUN_0006cdf8 @ 0x0006cdf8   (est. sk_cbootinfo_parse_single)
 * Ghidra: void FUN_0006cdf8(undefined8 param_1)
 * Runs FUN_0006c5cc with param_2 = 1 (untyped replication enabled).
 * Confidence: medium */
void FUN_0006cdf8(uint64_t param_1)
{
    FUN_0006c5cc((long *)param_1, 1);
}

/* FUN_0006ce00 @ 0x0006ce00   (est. sk_cbootinfo_find_by_base)
 * Ghidra: long * FUN_0006ce00(long param_1)
 * Walks the cbootinfo cap-array chain and returns a pointer to the first cap
 * whose (cap[2] & 0xffffffffff) << 0xc equals param_1 and whose type byte at
 * +0x27 is 0x11; otherwise NULL.
 * Confidence: medium */
long *FUN_0006ce00(long param_1)
{
    long *result = NULL;
    if (g_cboot_chain_head == 0xffffffffffffffffull)
        return NULL;
    long *page = (long *)g_cboot_chain_head;
    do {
        long *p2 = page;
        for (long n = *page; n != 0; n -= 1) {
            long *cand = p2 + 4;
            if ((p2[6] & 0xffffffffffull) << 0xc != (uint64_t)param_1 ||
                *(char *)((long)p2 + 0x27) != '\x11')
                cand = result;
            result = cand;
            p2 += 4;
        }
        page = (long *)page[1];
    } while (page != (long *)0xffffffffffffffffull);
    return result;
}

/* FUN_0006ce60 @ 0x0006ce60   (est. sk_root_slide_get)
 * Ghidra: undefined8 FUN_0006ce60(void)
 * Returns the launcher roottask slide (DAT_2bc686b8378).
 * Confidence: high */
uint64_t FUN_0006ce60(void)
{
    return g_rt_slide;
}

/* FUN_0006cea4 @ 0x0006cea4   (est. sk_launcher_cap_table_get)
 * Ghidra: undefined8 FUN_0006cea4(ulong param_1)
 * Returns the entry at index (param_1 & 0xffffffff) of the launcher capability
 * table (DAT_2bc686b8450[]).
 * Confidence: high */
uint64_t FUN_0006cea4(uint64_t param_1)
{
    return g_rt_slot_array[param_1 & 0xffffffff];
}

/* FUN_0006cec8 @ 0x0006cec8   (est. sk_count_gated_value)
 * Ghidra: undefined8 FUN_0006cec8(ulong param_1)
 * If the untyped count exceeds 0x1a9f0508 and bit (param_1 & 0x3f) of
 * DAT_4d5e91ca80 is set, returns DAT_4d5e91c8a0; else 0. A high-VA gated
 * constant lookup (decompiler ADRP artifact).
 * Confidence: low
 * Notes: high-VA artifact globals DAT_4d5e91c8a0 / DAT_4d5e91ca80. */
uint64_t FUN_0006cec8(uint64_t param_1)
{
    if ((0x1a9f0508 < g_untyped_count) &&
        ((DAT_4d5e91ca80 >> (param_1 & 0x3f) & 1) != 0))
        return DAT_4d5e91c8a0;
    return 0;
}

/* FUN_0006cf0c @ 0x0006cf0c   (est. sk_count_gated_value)
 * Ghidra: undefined8 FUN_0006cf0c(ulong param_1)
 * Same shape as FUN_0006cec8 but gated on threshold 0x370000a8 and the
 * DAT_9fd86d1380 bitmask, returning DAT_9fd86d11a0.
 * Confidence: low
 * Notes: high-VA artifact globals DAT_9fd86d11a0 / DAT_9fd86d1380. */
uint64_t FUN_0006cf0c(uint64_t param_1)
{
    if ((0x370000a8 < g_untyped_count) &&
        ((DAT_9fd86d1380 >> (param_1 & 0x3f) & 1) != 0))
        return DAT_9fd86d11a0;
    return 0;
}

/* FUN_0006cf50 @ 0x0006cf50   (est. sk_untyped_region_find)
 * Ghidra: undefined8 FUN_0006cf50(ulong param_1)
 * Finds the untyped region containing address param_1 by linear scan of the
 * (base,size) table (stride 0x2e8 at DAT_006b2b10/DAT_006b2b18) and returns
 * the matching region record (DAT_006b2960, stride 0x2e8). Aborts with
 * "Could not find untyped region" if none matches.
 * Confidence: medium
 * Notes: s_Could_not_find_untyped_region_fo_005bf258. */
uint64_t FUN_0006cf50(uint64_t param_1)
{
    uint64_t uVar1 = 0;
    if (g_untyped_count == 0) {
        if ((uint32_t)uVar1 < (uint32_t)g_untyped_count)
            return g_untyped_tab[(uint32_t)uVar1];
    } else {
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= param_1 &&
                param_1 < (uint64_t)(r[0] + r[-1]))
                goto found;
            uVar1 += 1;
            r += 0x5d;                 /* stride 0x2e8 bytes */
        } while (g_untyped_count != uVar1);
    }
    FUN_0005b190(0, s_Could_not_find_untyped_region_fo_005bf258);
found:
    return g_untyped_tab[(uint32_t)uVar1];
}

/* FUN_0006cfe4 @ 0x0006cfe4   (est. sk_untyped_region_base_find)
 * Ghidra: undefined8 FUN_0006cfe4(void)
 * Returns the cbootinfo heap base (DAT_2bc686b8528) when the region count
 * exceeds 0xf100001f, otherwise finds the region for the address from
 * FUN_004b83bc and returns its base field (DAT_006b2b10).
 * Confidence: medium */
uint64_t FUN_0006cfe4(void)
{
    uint64_t uVar2;
    if (0xf100001f < g_untyped_count)
        return g_cboot_heap_size;
    uint64_t addr = FUN_004b83bc();
    if (g_untyped_count == 0) {
        uVar2 = 0;
        if ((uint32_t)uVar2 < (uint32_t)g_untyped_count)
            return g_untyped_base[(uint32_t)uVar2 * 0x5d];
    } else {
        uVar2 = 0;
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= addr && addr < (uint64_t)(r[0] + r[-1]))
                goto found;
            uVar2 += 1;
            r += 0x5d;
        } while (g_untyped_count != uVar2);
    }
    FUN_0005b190(0, s_Could_not_find_untyped_region_fo_005bf258);
found:
    return g_untyped_base[(uint32_t)uVar2 * 0x5d];
}

/* FUN_0006d024 @ 0x0006d024   (est. sk_untyped_region_base_find)
 * Ghidra: undefined8 FUN_0006d024(ulong param_1)
 * Finds the untyped region for address param_1 and returns its base
 * (DAT_006b2b10, stride 0x2e8).
 * Confidence: medium */
uint64_t FUN_0006d024(uint64_t param_1)
{
    uint64_t uVar1 = 0;
    if (g_untyped_count == 0) {
        if ((uint32_t)uVar1 < (uint32_t)g_untyped_count)
            return g_untyped_base[(uint32_t)uVar1 * 0x5d];
    } else {
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= param_1 && param_1 < (uint64_t)(r[0] + r[-1]))
                goto found;
            uVar1 += 1;
            r += 0x5d;
        } while (g_untyped_count != uVar1);
    }
    FUN_0005b190(0, s_Could_not_find_untyped_region_fo_005bf258);
found:
    return g_untyped_base[(uint32_t)uVar1 * 0x5d];
}

/* FUN_0006d0b8 @ 0x0006d0b8   (est. sk_untyped_region_offset)
 * Ghidra: long FUN_0006d0b8(ulong param_1)
 * Finds the untyped region for param_1 and returns param_1 minus the region
 * base (the offset within the region).
 * Confidence: medium */
long FUN_0006d0b8(uint64_t param_1)
{
    uint64_t uVar1 = 0;
    if (g_untyped_count == 0) {
        if ((uint32_t)uVar1 < (uint32_t)g_untyped_count)
            return (long)(param_1 - g_untyped_base[(uint32_t)uVar1 * 0x5d]);
    } else {
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= param_1 && param_1 < (uint64_t)(r[0] + r[-1]))
                goto found;
            uVar1 += 1;
            r += 0x5d;
        } while (g_untyped_count != uVar1);
    }
    FUN_0005b190(0, s_Could_not_find_untyped_region_fo_005bf258);
found:
    return (long)(param_1 - g_untyped_base[(uint32_t)uVar1 * 0x5d]);
}

/* FUN_0006d150 @ 0x0006d150   (est. sk_untyped_region_size)
 * Ghidra: undefined8 FUN_0006d150(ulong param_1)
 * Finds the untyped region for param_1 and returns its size
 * (DAT_006b2b18, stride 0x2e8).
 * Confidence: medium */
uint64_t FUN_0006d150(uint64_t param_1)
{
    uint64_t uVar1 = 0;
    if (g_untyped_count == 0) {
        if ((uint32_t)uVar1 < (uint32_t)g_untyped_count)
            return g_untyped_size[(uint32_t)uVar1 * 0x5d];
    } else {
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= param_1 && param_1 < (uint64_t)(r[0] + r[-1]))
                goto found;
            uVar1 += 1;
            r += 0x5d;
        } while (g_untyped_count != uVar1);
    }
    FUN_0005b190(0, s_Could_not_find_untyped_region_fo_005bf258);
found:
    return g_untyped_size[(uint32_t)uVar1 * 0x5d];
}

/* FUN_0006d1e4 @ 0x0006d1e4   (est. sk_untyped_region_contains)
 * Ghidra: bool FUN_0006d1e4(ulong param_1)
 * Returns whether param_1 lies within any untyped region.
 * Confidence: medium */
bool FUN_0006d1e4(uint64_t param_1)
{
    uint64_t uVar2 = 0;
    if (g_untyped_count == 0) {
        uVar2 = 0;
    } else {
        uint64_t i = 0;
        uint64_t *r = (uint64_t *)&g_untyped_size[0];
        do {
            if ((uint64_t)r[-1] <= param_1 &&
                (uVar2 = i, param_1 < (uint64_t)(r[0] + r[-1])))
                break;
            i += 1;
            r += 0x5d;
            uVar2 = (uint64_t)g_untyped_count;
        } while (g_untyped_count != i);
    }
    return (uint32_t)uVar2 < (uint32_t)g_untyped_count;
}

/* FUN_0006d240 @ 0x0006d240   (est. sk_cbootinfo_alloc)
 * Ghidra: ulong FUN_0006d240(ulong param_1, undefined8 param_2)
 * Allocates param_1 bytes from the cbootinfo arena with a 1 MB-granule
 * occupancy bitmap (DAT_2bc686b8560). Alignment to the next 1 MB boundary,
 * rejection of regions overlapping the low watermark, and 1 GB-size
 * "ExclavePlatform runtime error" handling on the large-path. Marks the
 * granules (bitmap) when param_2 != 0 and returns the allocation start;
 * returns the cursor when param_1 == 0. On overflow/exhaustion funnels to
 * FUN_004b7008 / the error chain and aborts "cbootinfo out of memory".
 * Confidence: medium
 * Notes: s_ExclavePlatform_runtime_error__F/_O; s_cbootinfo_out_of_memory. */
uint64_t FUN_0006d240(uint64_t param_1, uint64_t param_2)
{
    long lVar1;
    long lVar2 = (long)g_cboot_end;
    uint64_t high = g_cboot_high;
    uint64_t low = g_cboot_low;
    uint64_t uVar5, uVar6, uVar7, uVar8, uVar9, uVar10;

    if (param_1 == 0)
        return g_cboot_cursor;
    if ((uint64_t)g_cboot_end - g_cboot_cursor < param_1)
        goto out_of_memory;
    if ((param_1 & 0xfffff) == 0) {
        uVar7 = g_cboot_cursor;
        if (g_cboot_cursor <= g_cboot_high)
            uVar7 = g_cboot_high;
        uVar7 = uVar7 + 0xfffff & 0xfffffffffff00000ull;   /* align to 1 MB */
        if (g_cboot_cursor <= g_cboot_low)
            uVar7 = g_cboot_cursor;
        uVar8 = g_cboot_cursor;
        uint64_t uVar4 = param_2;
        if (param_1 >> 0x24 != 0) {                 /* > 1 GB */
            FUN_00118b94(s_ExclavePlatform_runtime_error__F_005bfa2e);
            uVar8 = g_cboot_alloc_base2;
            uVar4 = 1;
            CallSupervisor(0);                      /* abort SVC */
        }
        uVar9 = uVar7;
        if (uVar7 <= low && low < uVar7 + param_1) {
            low = high + 0xfffff & 0xfffffffffff00000ull;   /* align high */
            g_cboot_cursor = low;
            if (low != uVar7) {
                uVar6 = 0;
                do {
                    lVar1 = (long)(((uVar7 + uVar6) >> 0x1a) * 8);
                    uVar9 = g_cboot_pte_bitmap[(uint64_t)lVar1 / 8];
                    uVar10 = 1ull << (((uVar7 + uVar6) >> 0x14) & 0x3f);
                    if ((uVar9 & uVar10) != 0)
                        goto bitmap_conflict;
                    g_cboot_pte_bitmap[(uint64_t)lVar1 / 8] = uVar9 | uVar10;
                    uVar6 += 0x100000;
                    uVar9 = low;
                } while (uVar6 < low - uVar7);
            }
        }
        if ((uint64_t)lVar2 - uVar9 < param_1) {
            FUN_00118b94(s_ExclavePlatform_runtime_error__O_005bfa79, uVar4);
            uVar8 = g_cboot_alloc_base2;
            uVar4 = 1;
            CallSupervisor(0);                      /* abort SVC */
        }
        uVar5 = uVar9 + param_1;
        if (uVar5 < uVar9) {                        /* CARRY8 overflow */
            FUN_004b7008(uVar8, uVar4);
            return g_cboot_alloc_base2;
        }
        g_cboot_cursor = uVar5;
        if ((uVar5 & 0xfffff) == 0) {
            uVar6 = uVar5 - param_1;                /* allocation start */
            if ((int)param_2 == 0)
                return uVar6;
            uVar5 = 0;
            for (;;) {
                lVar1 = (long)(((uVar9 + uVar5) >> 0x1a) * 8);
                uVar7 = g_cboot_pte_bitmap[(uint64_t)lVar1 / 8];
                uVar8 = 1ull << (((uVar9 + uVar5) >> 0x14) & 0x3f);
                if ((uVar7 & uVar8) != 0)
                    break;                          /* conflict */
                g_cboot_pte_bitmap[(uint64_t)lVar1 / 8] = uVar7 | uVar8;
                uVar5 += 0x100000;
                if (param_1 <= uVar5)
                    return uVar6;
            }
            FUN_004b846c(uVar6);
bitmap_conflict:
            FUN_004b8414();
            goto err_funnel_e8;
        }
    } else {
err_funnel_e8:
        FUN_004b83e8();
    }
    FUN_004b8440();
out_of_memory:
    FUN_0005b190(0, s_cbootinfo_out_of_memory__cannot_a_005bf3cc);
}

/* FUN_0006d450 @ 0x0006d450   (est. sk_cbootinfo_alloc_base_get)
 * Ghidra: undefined8 FUN_0006d450(void)
 * Returns the cbootinfo allocation base (DAT_006be880).
 * Confidence: high */
uint64_t FUN_0006d450(void)
{
    return g_cboot_alloc_base2;
}

/* FUN_0006d45c @ 0x0006d45c   (est. sk_cbootinfo_bytes_free)
 * Ghidra: ulong FUN_0006d45c(void)
 * Computes the number of 16 KB-aligned free bytes remaining in the cbootinfo
 * arena, as the max of the low/high gaps masked to 16 KB.
 * Confidence: medium */
uint64_t FUN_0006d45c(void)
{
    uint64_t uVar1 = g_cboot_low;
    if (g_cboot_end <= g_cboot_low)
        uVar1 = g_cboot_end;
    uint64_t uVar3 = g_cboot_high;
    if (g_cboot_high <= g_cboot_cursor)
        uVar3 = g_cboot_cursor;
    uVar3 = g_cboot_end - uVar3;
    if (g_cboot_end <= g_cboot_high)
        uVar3 = 0;
    uint64_t uVar2 = uVar1 - g_cboot_cursor;
    if (uVar1 - g_cboot_cursor <= uVar3)
        uVar2 = uVar3;
    if (g_cboot_low <= g_cboot_cursor)
        uVar2 = uVar3;
    return uVar2 & 0xffffffffffffc000ull;
}

/* FUN_0006d4b4 @ 0x0006d4b4   (est. sk_untyped_magic_get)
 * Ghidra: undefined8 FUN_0006d4b4(void)
 * Returns DAT_ee50745750 when the untyped count differs from the magic
 * 0x52000328, else 0. A decompiler high-VA artifact check.
 * Confidence: low
 * Notes: high-VA artifact globals DAT_ee50745750. */
uint64_t FUN_0006d4b4(void)
{
    if (g_untyped_count != 0x52000328)
        return DAT_ee50745750;
    return 0;
}

/* FUN_0006d4f0 @ 0x0006d4f0   (est. sk_phys_hints_valid_get)
 * Ghidra: undefined1 FUN_0006d4f0(void)
 * Returns the phys-hints-valid byte (DAT_006be8b0).
 * Confidence: high */
uint8_t FUN_0006d4f0(void)
{
    return g_phys_hints_valid;
}

/* FUN_0006d4fc @ 0x0006d4fc   (est. sk_phys_hint_a_get)
 * Ghidra: undefined8 FUN_0006d4fc(void)
 * Returns phys hint A (DAT_006be8a0).
 * Confidence: high */
uint64_t FUN_0006d4fc(void)
{
    return g_phys_hint_a;
}

/* FUN_0006d508 @ 0x0006d508   (est. sk_phys_hint_a_cap_get)
 * Ghidra: undefined8 FUN_0006d508(void)
 * Returns the phys-hint-A capability (DAT_006be8b8).
 * Confidence: high */
uint64_t FUN_0006d508(void)
{
    return g_phys_hint_a_cap;
}

/* FUN_0006d514 @ 0x0006d514   (est. sk_phys_hint_b_get)
 * Ghidra: undefined8 FUN_0006d514(void)
 * Returns phys hint B (DAT_006be8a8).
 * Confidence: high */
uint64_t FUN_0006d514(void)
{
    return g_phys_hint_b;
}

/* FUN_0006d520 @ 0x0006d520   (est. sk_phys_hint_b_cap_get)
 * Ghidra: undefined8 FUN_0006d520(void)
 * Returns the phys-hint-B capability (DAT_006be8c0).
 * Confidence: high */
uint64_t FUN_0006d520(void)
{
    return g_phys_hint_b_cap;
}

/* FUN_0006d52c @ 0x0006d52c   (est. sk_cboot_cap_found_get)
 * Ghidra: undefined8 FUN_0006d52c(void)
 * Returns the last matching cbootinfo capability (DAT_006be888).
 * Confidence: high */
uint64_t FUN_0006d52c(void)
{
    return g_cboot_cap_found;
}
