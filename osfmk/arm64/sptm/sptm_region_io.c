/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file reconstructs the SPTM bootstrap / IO-space region (0xd0000-0xe0000):
 * the T8110 DART (IOMMU) driver, the PAPT (physical address page table)
 * frame allocator and page-table walk/install primitives, the boot-region
 * mapping/retype machinery, the copy-to-scratch (phystokv) helpers, and the
 * two large bootstrap stages (memory/PAPT early setup + IO-range/filter and
 * hibernation setup). Most functions here are calibrated on the FTE class-6
 * (managed IO) / class-1 (SPTM) / class-2 (page table) frame-type tables.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ */
/* Shared noreturn diagnostics (other trees)                          */
/* ------------------------------------------------------------------ */
extern __attribute__((noreturn)) void sptm_panic(const char *fmt, ...);        /* FUN_000f8804 */
extern __attribute__((noreturn)) void sptm_panic_code(unsigned int code,
    uintptr_t arg, const char *fmt, ...);                                      /* FUN_000f8844 */
extern __attribute__((noreturn)) void sptm_stack_chk_fail(void);              /* FUN_000ae44c */

/* ------------------------------------------------------------------ */
/* 16-byte return convention: Ghidra models several helpers as         */
/* returning {x0,x1}. .lo = low 64 bits (x0), .hi = high (x1).        */
/* ------------------------------------------------------------------ */
typedef struct sptm_ret16 { uint64_t lo; uint64_t hi; } sptm_ret16_t;

/* ------------------------------------------------------------------ */
/* Device-tree helpers (FUN_000b79e8 / 000b7c04 / 000b7dc8;            */
/* declared in sptm_internal.h) and the local name formatter          */
/* FUN_000b7748 (fills a property-name buffer from a template).       */
/* ------------------------------------------------------------------ */
extern int sptm_dt_find_node(uintptr_t iter, uintptr_t parent,
    const char *name, uintptr_t *out);                                        /* FUN_000b79e8 */
extern int sptm_dt_iterate(uintptr_t iter, uintptr_t *current,
    uintptr_t *next);                                                         /* FUN_000b7dc8 */
extern int sptm_dt_get_prop(uintptr_t node, const char *name,
    uintptr_t *out_val, uint32_t *out_size, uintptr_t iter, uintptr_t ctx);   /* FUN_000b7c04 */
extern int sptm_dt_prop_u32(uintptr_t node, const char *name, uint32_t v);    /* thunk_FUN_000ac290 */
extern int sptm_dt_cmp_prop(uintptr_t node, const char *name);                /* thunk_FUN_000ac190 */
extern void sptm_dt_prop_name(uintptr_t out);                                 /* FUN_000b7748 */

/* Boot region lookup: FUN_000b807c returns a {base,size} pair. */
extern long *sptm_boot_region(const char *name, int required);                /* FUN_000b807c */

/* ------------------------------------------------------------------ */
/* Frame / page helpers (other trees)                                  */
/* ------------------------------------------------------------------ */
extern uintptr_t sptm_percpu_dart_state(void);                                /* FUN_000e4d78 */
extern uintptr_t sptm_boot_alloc(uint32_t kind);                              /* FUN_000e43d0 */
extern sptm_ret16_t sptm_frame_alloc(uint64_t va, uint64_t pages,
    uint32_t type);                                                           /* FUN_000e45a8 */
extern sptm_ret16_t sptm_frame_translate(uintptr_t dart_regs, uint64_t pa,
    uint64_t size);                                                           /* FUN_000e63c8 */
extern sptm_ret16_t sptm_frame_va(uint64_t pa);                               /* FUN_000e3d7c */
extern uint64_t sptm_va_translate_slow(uint64_t pa);                          /* FUN_000e40ec */
extern sptm_ret16_t sptm_fte_info(uint64_t pa);                               /* FUN_000e2150 */
extern sptm_ret16_t sptm_frame_metadata(uint64_t pa, uint64_t arg);           /* FUN_000f8714 */
extern sptm_ret16_t sptm_bsearch(void *key, void *base, uint64_t n,
    uint64_t size, void *cmp);                                                /* FUN_000ad2dc */
extern void sptm_register_cpu(uint16_t hwid);                                 /* FUN_000b86bc */
extern void sptm_boot_skip_unmap(uint32_t mode);                              /* FUN_000dce04 */
extern void sptm_dt_root(void);                                               /* FUN_000b8154 */
extern void sptm_clock_protection_op(uintptr_t regs, uint32_t mode);          /* FUN_000c786c */
extern void sptm_enable_iommu(uint32_t id);                                   /* FUN_000e61f0 */
extern void sptm_flush_slices(void);                                          /* FUN_000c44ac */
extern uint64_t sptm_ret16_lo(sptm_ret16_t r);                                /* helper */
extern void sptm_slice_tlbi_flush(uint64_t va, uint64_t pages);               /* FUN_000ab994 */
extern void sptm_slice_tlbi_single(uint64_t va, uint64_t pages);              /* FUN_000d7dc0 */
extern void sptm_slice_update(uint64_t va, uint64_t pages, uint64_t mode,
    uint64_t flags);                                                          /* FUN_000d76fc */
extern void sptm_memcpy_bulk(uintptr_t dst, uintptr_t src, uint64_t n);       /* thunk_FUN_000abeb0 */
extern void sptm_bzero_chk(uintptr_t dst, uint64_t n, uint64_t fill);         /* FUN_000ae3e0 */
extern void sptm_qsort(void *base, uint64_t n, uint64_t size, void *cmp);     /* FUN_000ad3b0 */
extern uint64_t sptm_dart_state(uintptr_t regs);                              /* FUN_000e4424 */
extern uint64_t sptm_dart_write_gate(uintptr_t dart_regs, uint32_t sel);      /* FUN_000c9364 */
extern uint64_t sptm_dart_write_gate_slow(uintptr_t dart_regs,
    uint32_t sel);                                                            /* FUN_000c92e8 */
extern void sptm_io_range_sort(void *base, uint64_t n, uint64_t size,
    void *cmp);                                                               /* FUN_000e4030 */
extern void sptm_retype_slice_arm(uint32_t a);                                /* FUN_000b2584 */
extern void sptm_panic_assert_fmt(const char *fmt, uintptr_t a, uintptr_t b); /* FUN_000f84b4 */

/* ------------------------------------------------------------------ */
/* Central globals (addresses in comments; image base 0)               */
/* ------------------------------------------------------------------ */
/* DT root node pointer set by boot. */
extern uintptr_t g_dt_root;                     /* DAT_00094ab8 */

/* Bootstrap stages bitset (DAT_001012d8): bit8 = PAPT live, bit11 =
 * ranges allocated, bit9 = IO boot, bit7 = boot regions registered,
 * bit10 = va mappings, bit17 = post-boot. */
extern uint64_t g_bootstrap_stages;             /* DAT_001012d8 */

/* Boot-frame allocator: allocation cursor + base. */
extern uintptr_t g_boot_alloc_base;             /* DAT_001012a0 */
extern uint64_t  g_boot_alloc_off;              /* DAT_001012a8 */

/* Papt (physical) window: [g_mem_phys_base, g_mem_phys_end). */
extern uint64_t g_mem_phys_base;                /* DAT_00095d18 */
extern uint64_t g_mem_phys_end;                 /* DAT_00095d20 */

/* Papt VA base for the identity window. */
extern uint64_t g_papt_va_base;                 /* DAT_00095110 */

/* Root page-table paddr + VA. */
extern uint64_t g_papt_root_pa;                 /* DAT_00095d48 */
extern uint64_t g_papt_root_va;                 /* DAT_00095458 */

/* Frame-type table (type -> {class, flags}) and frame class table. */
extern uint8_t  g_fte_class[];                  /* DAT_00095d51, stride 0x90 */
extern uint8_t  g_fte_class2[];                 /* DAT_00095d56 */
extern uint8_t  g_fte_class3[];                 /* DAT_00095d54 */
extern uint8_t  g_fte_class4[];                 /* DAT_00095dc9 */
extern int8_t   g_type_state[];                 /* DAT_00095d58, stride 0x90 */

/* Boot PAPT range table (name, type, va_base, pages, flags), count. */
extern uint32_t g_papt_range_count;             /* DAT_001012f0 */
extern uintptr_t g_papt_range_name[];           /* DAT_001012f8, stride 0x28 */
extern uint8_t  g_papt_range_type[];            /* DAT_00101300 */
extern uintptr_t g_papt_range_va[];             /* DAT_00101308 */
extern uint32_t g_papt_range_pages[];           /* DAT_00101310 */
extern uint32_t g_papt_range_flags[];           /* DAT_00101318 */

/* Committed (sorted/coalesced) PAPT ranges. */
extern uint32_t g_committed_range_count;        /* DAT_00101ac8 */
extern uintptr_t g_committed_range_base[];      /* DAT_00101ad0, stride 0x18 */
extern uintptr_t g_committed_range_va[];        /* DAT_00101ad8 */
extern uint32_t g_committed_range_pages[];      /* DAT_00101ae0 */

/* Managed (DRAM) window. */
extern uint64_t g_dram_base;                    /* DAT_00095d28 */
extern uint64_t g_dram_end;                     /* DAT_00095d30 */

/* Frame allocator: index counters for the PAPT/root/meta regions. */
extern uint32_t g_fa_counter[];                 /* DAT_000950e4 (e4,e8,ec,f0,f4,f8) */

/* IO range table (registered IO ranges). */
extern uint32_t g_io_range_count;               /* DAT_00095444 */
extern uintptr_t g_io_range_table;              /* DAT_00095450 */
extern uintptr_t g_io_range_fte;                /* DAT_00095448 */

/* pmap_io_ranges (from /defaults). */
extern uint32_t g_pmap_io_range_count;          /* DAT_000950d8 */
extern uintptr_t *g_pmap_io_ranges;             /* DAT_000950d0 */

/* pmap_io_filters (from /defaults). */
extern uint32_t g_io_filter_count;              /* DAT_000950c8 */
extern uint32_t *g_io_filter_table;             /* DAT_000950c0 */

/* Mapping enforcement mode (io mapping_enforcement_mode). */
extern uint64_t g_io_mapping_enforcement;       /* DAT_00095278 */

/* Current IO mapping window: allocated VA cursor + count. */
extern uint64_t g_mapping_va_cursor;            /* DAT_001012e8 */
extern uint64_t g_mapping_count;                /* DAT_001012e0 */

/* max mappings ceiling and per-region counts. */
extern uint64_t g_max_mappings;                 /* DAT_00095108 */
extern uint64_t g_mapping_region_count;         /* DAT_001040a0 */

/* xnu exception-return / dispatch table globals (rebased in bootstrap). */
extern uintptr_t g_xnu_el2_exception_vector;    /* DAT_00095cf8 */
extern uintptr_t g_xnu_exc_return_handler;      /* DAT_00095468 */
extern uintptr_t g_dispatch_table;              /* DAT_00095bf0 */
extern uintptr_t g_el2_dispatch;                /* DAT_000944f8 */

/* T8110 DART id -> per-cpu dart-state index table (u16, 0xffff = absent). */
extern uint16_t g_dart_id_table[];              /* DAT_00094ec0 */

/* DART driver config flags (parsed from DT in FUN_000d0c98). */
extern uint8_t  g_debug_enabled;                /* DAT_001012b0 */
extern uint8_t  g_gapf_mode;                    /* DAT_001012c2 */
extern uint8_t  g_ps_wr_dis_mode;               /* DAT_001012c1 */
extern uint8_t  g_ps_wr_dis_unused;             /* DAT_001012c0 */
extern uint32_t g_ps_wr_dis_entry_count;        /* DAT_001012b4 */
extern uintptr_t g_ps_wr_dis_entries;           /* DAT_001012b8 */
extern uint32_t g_gapf_ungang_count;            /* DAT_001012c4 */
extern uintptr_t g_gapf_ungang_entries;         /* DAT_001012c8 */

/* Region carve-out for phys->VA mappings (SAPT / PIOGW). */
extern uint64_t g_carveout_lo;                  /* DAT_00095140 */
extern uint64_t g_carveout_hi;                  /* DAT_00095148 */

/* IORange window extents for SPTM / TXM (DAT_00095120/128/130/138). */
extern uint64_t g_io_win[];                     /* DAT_00095120,4 */

/* Current contiguous PAPT range table (DAT_001012d0, stride 0x14). */
extern uint8_t g_contig_range[];                /* DAT_001012d0 */

/* "boot" VA allocation base and last VA (DAT_00101f80/88). */
extern uint64_t g_va_alloc_cur;                 /* DAT_00101f80 */
extern uint64_t g_va_alloc_last;                /* DAT_00101f88 */

/* Per-CPU structure base (tpidr_el2 = 0x106180). */
extern uintptr_t g_percpu_base;                 /* DAT_00106180 */

/* Execution-mode bitsets (which exception levels are supported). */
extern uint64_t g_exec_mode_enabled[];          /* DAT_00094d00,8 */
extern uint64_t g_exec_mode_dispatch[];         /* DAT_00094d78, stride 0x30 */

/* AMCC/ACC carve-out paddr window. */
extern uint64_t g_amcc_win;                     /* DAT_00094a50 */
extern uint64_t g_amcc_acc_win;                 /* DAT_00094a60 */

/* Hibernation segment table. */
extern uint32_t g_hib_seg_count;                /* DAT_00094968 */
extern uint32_t g_hib_seg_table[];              /* DAT_00100e08 */
extern uint8_t  g_hib_segs_present;             /* DAT_00100e00 */

/* Exclave (managed-region) registration table for SK. */
extern uint32_t g_managed_region_count;         /* DAT_00094970 */
extern uint32_t g_managed_region_table[];       /* DAT_00100730, stride 0x10 */
extern uintptr_t g_managed_region_ptr;          /* DAT_00101040 */

/* Defaults-derived PMAP max ASID count. */
extern uint32_t g_pmap_max_asids;               /* DAT_00095d3c */

/* UAT memory-region handoff descriptors (DAT_00101068..). */
extern uint32_t g_uat_region_count;             /* DAT_00101068 */
extern uint32_t g_uat_region_stride;            /* DAT_0010106c */
extern uint32_t g_uat_region_count2;            /* DAT_00101070 */
extern uint32_t g_uat_region_stride2;           /* DAT_00101074 */
extern uintptr_t g_uat_region_va[];             /* DAT_00101078 */
extern uintptr_t g_uat_region_mapped[];         /* DAT_00101220 */

/* AArch64 intrinsics (barriers / membar). */
static inline void sptm_dmb(uint32_t a, uint32_t b) { __asm__ volatile("dmb %0" ::"i"(a) : "memory"); }
static inline void sptm_dsb(uint32_t a, uint32_t b, uint32_t c) { __asm__ volatile("dsb %0" ::"i"(a) : "memory"); }
static inline void sptm_isb(void) { __asm__ volatile("isb" ::: "memory"); }
static inline void sptm_lrelease(void) { __asm__ volatile("stlr xzr, [sp, #-8]!" ::: "memory"); }
static inline void sptm_lacquire(void) { __asm__ volatile("ldar xzr, [sp, #8]!" ::: "memory"); }

/* tpidr_el2 value; the uat handoff-region pointer is read through the
 * per-cpu state at offset 0x1b (see the helper macros used at call sites). */
static inline uintptr_t sptm_percpu_state(void)
{
    uintptr_t p;
    __asm__ volatile("mrs %0, tpidr_el2" : "=r"(p));
    return p;
}

/* ------------------------------------------------------------------ */
/* Small builtin shims + forward declarations for helpers defined in   */
/* this file but used before their definition (page-table recursion).  */
/* ------------------------------------------------------------------ */
static inline uint32_t popcount(uint64_t x) { return (uint32_t)__builtin_popcountll(x); }
static inline uint64_t clz64(uint64_t x) { return (uint64_t)__builtin_clzll(x); }
static inline uint64_t bitreverse64(uint64_t x) { return __builtin_bitreverse64(x); }

uintptr_t sptm_pa_to_va(uint64_t paddr);
uintptr_t sptm_va_to_pa(uintptr_t va);
uint64_t *sptm_papt_walk(uintptr_t root, uint64_t va, uint32_t level,
    uint64_t *table_out, uint64_t *va_out);
uintptr_t sptm_papt_leaf_pte(uint64_t va);
void sptm_papt_unmap_leaf(uintptr_t va);
void sptm_papt_update_root_pte(uintptr_t va, uint32_t type);
uintptr_t sptm_alloc_frames(uint32_t type, uint64_t num_frames, int pool);
void sptm_retype_frames(uintptr_t base_pa, uint64_t num_frames, uint32_t old_type,
    uint32_t new_type);
void sptm_papt_install_leaf(uintptr_t va, uintptr_t paddr, uint32_t count,
    uint32_t type, uint32_t prot, uint32_t flags);
uintptr_t sptm_phystokv(uintptr_t pa, uint64_t num_pages, uint32_t flags);
void sptm_dart_sid_alloc(uintptr_t dart, uint32_t sid, uint8_t type);
void sptm_dart_sid_setup(uintptr_t dart, uint64_t sid, uintptr_t *dt,
    uintptr_t node, uint32_t vm_align, int vm_align_rem, uint32_t flag);
void sptm_dart_sid_property_set(uintptr_t dart, uintptr_t iter, uintptr_t ctx,
    uintptr_t node, uint64_t *bitset, const char *prop_name);
void sptm_dart_check_vm_reserve_size(uintptr_t dart, int size);
void sptm_dart_register(uintptr_t *dt, uintptr_t node, uint64_t sr_region);
uint32_t sptm_io_range_cmp(uintptr_t a, uintptr_t b);
uint32_t sptm_io_filter_cmp(uint32_t *a, uint32_t *b);
void sptm_papt_commit(void);
void sptm_map_boot_region(const char *name, uint32_t type, uintptr_t va_base,
    int num_pages, uint32_t flags);
void sptm_retype_boot_range(const char *name, uint32_t old_type, uint32_t new_type);
void sptm_papt_unmap_range(uintptr_t va, uint64_t num_pages);
uintptr_t sptm_copy_phys_to_scratch(uintptr_t pa, uint64_t ele_size,
    uint64_t num_ele, uintptr_t scratch_off);
uintptr_t sptm_copy_phys_to_scratch_checked(uintptr_t pa, uint64_t ele_size,
    uint64_t num_ele, uintptr_t scratch_off);
extern void sptm_dt_parse_io_space(uintptr_t node);   /* FUN_000d6860 */
void sptm_bootstrap_early(uintptr_t virt_base, uintptr_t phys_base,
    uintptr_t first_avail, uintptr_t mem_size, uintptr_t *dt);
void sptm_io_bootstrap(uintptr_t mem_start, uintptr_t mem_size, uintptr_t *dt);

/* ------------------------------------------------------------------ */
/* 000d056c  sptm_dart_lookup_gate                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d056c @ 0x000d056c   (est. sptm_dart_lookup_gate)
 * Ghidra: char FUN_000d056c(byte param_1, undefined8 param_2)
 * Looks up a T8110 DART by index in g_dart_id_table; if absent, panics
 * with code 0x6000006. In gapf mode it clears the per-CPU dart's
 * "ungate" byte (offset 0xbf5 of the dart register block). Returns the
 * gapf-mode flag so callers can branch on the DART's gating mode.
 * Confidence: medium
 * Notes: array DAT_00094ec0 indexed by param_1; per-CPU dart regs via
 *   FUN_000e4d78 -> *(state+0x10) + 0xbf5. */
uint8_t sptm_dart_lookup_gate(uint8_t dart_id, uintptr_t caller)
{
    uint8_t gapf = g_gapf_mode;

    if (g_dart_id_table[dart_id] != 0xffff) {
        if (g_gapf_mode == 0x01) {
            uintptr_t state = sptm_percpu_dart_state();
            *(uint8_t *)(*(uintptr_t *)(state + 0x10) + 0xbf5) = 0;
        }
        return gapf;
    }
    sptm_panic_code(0x6000006, caller, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d0610  sptm_dart_lookup_active                                   */
/* ------------------------------------------------------------------ */
/* FUN_000d0610 @ 0x000d0610   (est. sptm_dart_lookup_active)
 * Ghidra: undefined8 FUN_000d0610(byte param_1, undefined8 param_2)
 * Looks up a DART by index (panic 0x6000006 if absent). In gapf mode,
 * resolves the dart register block and reports whether its clock-
 * protection slice state byte (+0xbe0) is 0x03 (gapf-armed); on yes it
 * sets the ungate byte (+0xbf5) to 1 and returns 1, else returns 0.
 * Confidence: medium
 * Notes: per-CPU state via FUN_000e4d78; the +0xbe0/+0xbf5 offsets are
 *   the clock-protection slice state / ungate control bytes. */
uint64_t sptm_dart_lookup_active(uint8_t dart_id, uintptr_t caller)
{
    if (g_dart_id_table[dart_id] == 0xffff) {
        sptm_panic_code(0x6000006, caller, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if (g_gapf_mode == 0x01) {
        uintptr_t state = sptm_percpu_dart_state();
        if (*(uint8_t *)(*(uintptr_t *)(state + 0x10) + 0xbe0) == 0x03) {
            *(uint8_t *)(*(uintptr_t *)(state + 0x10) + 0xbf5) = 1;
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* 000d06c0  sptm_dart_clock_protection_setup                          */
/* ------------------------------------------------------------------ */
/* FUN_000d06c0 @ 0x000d06c0   (est. sptm_dart_clock_protection_setup)
 * Ghidra: void FUN_000d06c0(byte param_1, undefined8 param_2)
 * Looks up a DART by index (panic 0x6000006 if absent) and invokes the
 * clock-protection setup routine FUN_000c786c on its register block
 * with mode 1. No return value.
 * Confidence: medium */
void sptm_dart_clock_protection_setup(uint8_t dart_id, uintptr_t caller)
{
    if (g_dart_id_table[dart_id] != 0xffff) {
        uintptr_t state = sptm_percpu_dart_state();
        sptm_clock_protection_op(*(uintptr_t *)(state + 0x10), 1);
        return;
    }
    sptm_panic_code(0x6000006, caller, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d074c  sptm_dart_clock_protection_configure                      */
/* ------------------------------------------------------------------ */
/* FUN_000d074c @ 0x000d074c   (est. sptm_dart_clock_protection_configure)
 * Ghidra: void FUN_000d074c(byte param_1,undefined8 param_2,uint param_3,
 *                           uint param_4,uint param_5)
 * Looks up a DART (panic 0x6000006 if absent), then writes a 0x18-byte
 * clock-protection command block through the per-dart write gate
 * (FUN_000c9364 or the slow FUN_000c92e8 when APF-SID-remap is off).
 * The block encodes: type (low byte of param_2), slice base (param_3),
 * slice end (param_4) and command flags (param_5). Validation: the gate
 * must succeed (panic 0x6000009), the slice range must be ordered
 * (panic 0x600000f when the end-before-start bit is set), the type must
 * be <= 2 (panic 0x6000020), and the write is serialized with a
 * per-dart busylock (offset +0xc2c). In gapf mode the whole command is
 * skipped.
 * Confidence: medium
 * Notes: FUN_000c786c not called here; the command goes directly through
 *   the write gate into the dart's command queue (thunk_FUN_000abeb0). */
void sptm_dart_clock_protection_configure(uint8_t dart_id, uintptr_t cmd_type,
    uint32_t slice_lo, uint32_t slice_hi, uint32_t flags)
{
    if (g_dart_id_table[dart_id] != 0xffff) {
        uintptr_t state = sptm_percpu_dart_state();
        uintptr_t dart = *(uintptr_t *)(state + 0x10);
        uint8_t block[0x18] = {0};
        uint64_t (*gate)(uintptr_t, uint32_t) = sptm_dart_write_gate;

        if ((*(uint8_t *)(dart + 0xbf1) & 1) == 0) {
            gate = sptm_dart_write_gate_slow;
        }
        uint64_t status = gate(dart, flags & 0xff);
        if ((status & 1) == 0) {
            sptm_panic_code(0x6000009, status, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
        }
        uint32_t cmd_flags = flags;
        if (((flags >> 0xe) & 1) != 0 && slice_hi < slice_lo) {
            sptm_panic_code(0x600000f, status, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
        }
        block[0] = (uint8_t)(slice_lo);        /* lo slice base */
        block[4] = (uint8_t)(slice_hi);        /* lo slice end */
        if (((uint32_t)cmd_type & 0xff) > 2) {
            sptm_panic_code(0x6000020, status, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
        }
        block[2] = (uint8_t)cmd_type;          /* command type byte */
        if (*(uint16_t *)(dart + 0xbdc) > 0x201) {
            cmd_flags |= 0x8000;
        }
        if (*(int8_t *)(dart + 0xbe0) != 0x02) {
            sptm_lacquire();
            uint16_t lock = *(uint16_t *)(dart + 0xc2c);
            *(uint16_t *)(dart + 0xc2c) = lock | 2;
            sptm_lrelease();
            if ((lock >> 1) & 1) {
                sptm_panic("%s: %s dart %p %s %u ... Not seriali...", 0, 0, 0, 0, 0);
            }
            sptm_memcpy_bulk(dart + 0xc14, (uintptr_t)block, 0x18);
        }
        if (g_dart_id_table[dart_id] != 0xffff) {
            uintptr_t state2 = sptm_percpu_dart_state();
            sptm_clock_protection_op(*(uintptr_t *)(state2 + 0x10), 1);
            return;
        }
    }
    sptm_panic_code(0x6000006, 0, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d0a14  sptm_dart_read_config                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d0a14 @ 0x000d0a14   (est. sptm_dart_read_config)
 * Ghidra: void FUN_000d0a14(undefined1 *param_1, undefined8 param_2,
 *                           uint param_3, undefined1 *param_4)
 * Reads a 0x18-byte DART configuration through the per-dart write gate.
 * param_2 must be 0x18 (panic 0x6000002). param_3 packs: low byte = dart
 * id (index into g_dart_id_table, panic 0x6000007 if absent), bits 8-15 =
 * register selector, bits 16-23 = request type (< 4). The read is
 * validated: if the write gate succeeds and the register selector is a
 * legal APF/IOMMU register (< 4), it writes the low 3 bytes of param_3 to
 * param_1 and, when the real-time or SID-remap feature bit is set, sets
 * param_4's two bytes to 1 (NULL param_4 panics). Violations panic
 * 0x6000004 / 0x600000a.
 * Confidence: medium
 * Notes: register feature mask at dart+0x238/0xa58 (per-SID bitset). */
void sptm_dart_read_config(uint8_t *out, uintptr_t size, uint32_t packed,
    uint8_t *flags)
{
    if ((int32_t)size != 0x18) {
        sptm_panic_code(0x6000002, size, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if (g_dart_id_table[packed & 0xff] != 0xffff) {
        uintptr_t state = sptm_percpu_dart_state();
        uintptr_t dart = *(uintptr_t *)(state + 0x10);
        uint64_t (*gate)(uintptr_t, uint32_t) = sptm_dart_write_gate;
        if ((*(uint8_t *)(dart + 0xbf1) & 1) == 0) {
            gate = sptm_dart_write_gate_slow;
        }
        uint32_t sel = (packed >> 8) & 0xff;
        uint64_t status = gate(dart, sel);
        if ((status & 1) != 0) {
            if (((packed >> 0x10) & 0xff) < 4 &&
                ((uint32_t)((*(uint8_t *)(*(uintptr_t *)(dart + (uint64_t)sel * 8 + 0x238) + 0x18) & 8) == 0)
                 <= ((packed >> 0x10) & 0xff))) {
                out[0] = (uint8_t)packed;
                out[1] = (uint8_t)(packed >> 8);
                out[2] = (uint8_t)(packed >> 0x10);
                if (((*(uint8_t *)(dart + 0xbe7) & 1) != 0) ||
                    (*(uint64_t *)(dart + ((uint64_t)(sel >> 3) & 0x18) + 0xa58) &
                     (1ULL << (sel & 0x3f))) != 0) {
                    if (flags == NULL) {
                        sptm_panic("%s: %s dart %s %s %d %s ... NULL", 0, 0, 0, 0, 0, 0);
                    }
                    flags[0] = 1;
                    flags[1] = 1;
                }
                return;
            }
            sptm_panic_code(0x6000004, status, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
        }
        sptm_panic_code(0x600000a, status, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    sptm_panic_code(0x6000007, size, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d0c98  sptm_dart_t8110_init                                      */
/* ------------------------------------------------------------------ */
/* FUN_000d0c98 @ 0x000d0c98   (est. sptm_dart_t8110_init)
 * Ghidra: void FUN_000d0c98(void)
 * Cold-boot DART driver init. Resets the DART id table (all entries
 * 0xffff), then reads /chosen DT props: "debug_enabled", and either the
 * "dart_clock_protection"/"dart_ps_wr_dis_entries" pair or the
 * "dart_clock_gapf_ungang_count"/"dart_gapf_sr_region"/
 * "dart_clock_gapf_ungang_entries" (gapf) set, populating the driver
 * config globals and copying the PS-WR-DIS / gapf entry tables into
 * boot-allocated buffers. Finally iterates the DT tree looking for nodes
 * whose "compatible" property equals "dart-t8110" and registers each via
 * sptm_dart_register (FUN_000d1b2c).
 * Confidence: medium
 * Notes: string refs s_dart_ps_wr_dis_entries 0x7026, s_dart_t8110
 *   0x71a3, s_compatible 0x7198, node name 0xe72c. */
void sptm_dart_t8110_init(void)
{
    uintptr_t iter = g_dt_root;
    uint64_t sr_region = 0;

    for (uint32_t i = 0; i < 0x100; i++) {
        g_dart_id_table[i] = 0xffff;
    }
    if (g_dt_root == 0) {
        sptm_panic("%s: %s %s %s %d ... error getting ...", 0, 0, 0, 0, 0);
    }
    uintptr_t chosen = 0;
    if (sptm_dt_find_node(g_dt_root, 0, "chosen", &chosen) != 1) {
        goto bad_lookup;
    }
    uintptr_t *val = NULL;
    uint32_t size = 0;
    if (sptm_dt_get_prop(chosen, "debug_enabled", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8)) == 1) {
        if (size < 4) {
            sptm_panic("%s: %s %s %s %d ... unexpected si...", 0, 0, 0, 0, 0);
        }
        g_debug_enabled = *val & 1;
    }

    /* Either the PS-WR-DIS table path (clock protection) or the gapf path. */
    val = NULL; size = 0;
    int rc = sptm_dt_get_prop(chosen, "dart_clock_protection", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8));
    if (rc == 1) {
        rc = sptm_dt_get_prop(chosen, "dart_ps_wr_dis_entries", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8));
        if (rc == 1) {
            if (size == 0 || (size / 6) * -6 != -(int32_t)size) {
                sptm_panic("%s: %s %s %s %d ... unexpected si...", 0, 0, 0, 0, 0);
            }
            g_ps_wr_dis_entry_count = size / 6;
            if (size < 6) goto alloc_too_small;
            if (size > 0x4001) goto alloc_too_large;
            uint64_t total = (uint64_t)g_ps_wr_dis_entry_count * 6;
            if (g_boot_alloc_base == 0 || g_boot_alloc_off + total > 0x4000) {
                g_boot_alloc_base = sptm_boot_alloc(1);
                g_boot_alloc_off = 0;
            }
            g_ps_wr_dis_entries = g_boot_alloc_base + g_boot_alloc_off;
            g_boot_alloc_off += (uint32_t)total;
            sptm_memcpy_bulk(g_ps_wr_dis_entries, (uintptr_t)val, total);
            g_ps_wr_dis_unused = 0;
            g_ps_wr_dis_mode = 1;
        } else {
            /* gapf path */
            g_gapf_mode = 1;
            uint32_t cnt = 0;
            if (sptm_dt_get_prop(chosen, "dart_clock_gapf_ungang_count", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8)) == 1) {
                if (size < 4) {
                    sptm_panic("%s: %s %s %s %d ... unexpected si...", 0, 0, 0, 0, 0);
                }
                g_gapf_ungang_count = *val;
            }
            uint64_t sr_region = 0;
            if (sptm_dt_get_prop(chosen, "dart_gapf_sr_region", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8)) == 1) {
                if (size != 8) {
                    sptm_panic("%s: %s %s %s %d ... unexpected si...", 0, 0, 0, 0, 0);
                }
                sr_region = sptm_frame_alloc(val[0], 1, 0).lo;
            }
            val = NULL; size = 0;
            rc = sptm_dt_get_prop(chosen, "dart_clock_gapf_ungang_entries", &val, &size, g_dt_root, *(uintptr_t *)(g_dt_root + 8));
            if (rc == 1) {
                uint64_t need = (uint64_t)g_gapf_ungang_count * 0x10;
                if (need - size != 0) {
                    sptm_panic("%s: %s %s %s %d ... unexpected si...", 0, 0, 0, 0, 0);
                }
                if (g_gapf_ungang_count == 0) goto alloc_too_small;
                if (g_gapf_ungang_count > 0x400) goto alloc_too_large;
                if (g_boot_alloc_base == 0 || g_boot_alloc_off + need > 0x4000) {
                    g_gapf_ungang_entries = sptm_boot_alloc(1);
                    g_boot_alloc_base = g_gapf_ungang_entries;
                    g_boot_alloc_off = (uint32_t)need;
                    if (g_gapf_ungang_count == 0) goto done_gapf;
                } else {
                    g_gapf_ungang_entries = g_boot_alloc_base + g_boot_alloc_off;
                    g_boot_alloc_off += (uint32_t)need;
                }
                uint32_t *src = val + 2;   /* skip the {pa,size} region header */
                uint64_t *dst = (uint64_t *)g_gapf_ungang_entries;
                for (uint32_t i = 0; i < g_gapf_ungang_count; i++) {
                    dst[i * 2] = ((uint64_t)src[i * 2 + 0]);
                    dst[i * 2 + 1] = ((uint64_t)src[i * 2 + 1]);
                }
            }
        }
    }

done_gapf:
    /* Iterate the DT scanning for compatible == "dart-t8110" nodes. */
    uintptr_t cur = 0;
    int rc2 = sptm_dt_find_node(g_dt_root, 0, (const char *)0xe72c, &cur);
    if (rc2 == 1) {
        uintptr_t parent = (cur == 0) ? g_dt_root : cur;
        uintptr_t node = 0;
        uintptr_t next = 0;
        (void)parent;
        while (sptm_dt_iterate(g_dt_root, &node, &next) != 0) {
            uintptr_t n = next;
            uintptr_t *comp = NULL;
            uint32_t csize = 0;
            if (sptm_dt_get_prop(n, "compatible", &comp, &csize, g_dt_root, *(uintptr_t *)(g_dt_root + 8)) == 1 &&
                sptm_dt_cmp_prop((uintptr_t)comp, "dart-t8110") == 0) {
                sptm_dart_register((uintptr_t *)&g_dt_root, n, sr_region);
            }
        }
        return;
    }
bad_lookup:
    sptm_panic("%s: %s %s %s %d ... error: %d look...", 0, 0, 0, 0, 0);
alloc_too_small:
    sptm_panic("%s: %s %s %s %d ... alloc_size_mu...", 0, 0, 0, 0, 0);
alloc_too_large:
    sptm_panic("%s: %s %s %s %d ... allocation_re...", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d4d30  sptm_dart_check_vm_reserve_size                           */
/* ------------------------------------------------------------------ */
/* FUN_000d4d30 @ 0x000d4d30   (est. sptm_dart_check_vm_reserve_size)
 * Ghidra: void FUN_000d4d30(long param_1,int param_2)
 * Validates that a DART VM-reserve DT property is exactly 0x10 bytes;
 * anything else panics ("state %p %s"). NULL dart panics. Used for the
 * "vm_reserve" DT property size check.
 * Confidence: high */
void sptm_dart_check_vm_reserve_size(uintptr_t dart, int size)
{
    if (dart == 0) {
        sptm_panic("%s: %s %s %s %d %s ... NULL", 0, 0, 0, 0, 0, 0);
    }
    if (size == 0x10) {
        return;
    }
    sptm_panic("%s: %s %s %s %d ... state %p %s...", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d4dd4  sptm_dart_sid_property_set                                */
/* ------------------------------------------------------------------ */
/* FUN_000d4dd4 @ 0x000d4dd4   (est. sptm_dart_sid_property_set)
 * Ghidra: void FUN_000d4dd4(long param_1,undefined8 param_2,undefined8
 *                           param_3,undefined8 param_4,long param_5,
 *                           undefined8 param_6)
 * Parses a per-DART SID-list DT property named param_6 (e.g. "sid-trace",
 * "sid-mcw", "sid-ocla", "sid-lft") into a per-SID bitset at param_5.
 * Zeros the 0x20-byte bitset first, then for each 32-bit SID in the
 * property (<= 0x403 entries, panic "Number of ...") sets bit sid of
 * param_5 (each SID must be < the SID-count at param_1+0xb98, else panic
 * "%s %u must be less than ...").
 * Confidence: high */
void sptm_dart_sid_property_set(uintptr_t dart, uintptr_t iter, uintptr_t ctx,
    uintptr_t node, uint64_t *bitset, const char *prop_name)
{
    uint32_t *val = NULL;
    uint32_t size = 0;
    int rc = sptm_dt_get_prop(node, prop_name, (uintptr_t *)&val, &size, iter, ctx);
    sptm_bzero_chk((uintptr_t)bitset, 0x20, 0xffffffffffffffffULL);
    if (rc == 1) {
        uint64_t n = size >> 2;
        if (size > 0x403) {
            sptm_panic("%s: %s %s %s %u ... Number of ...", 0, 0, 0, 0, 0);
        }
        if (size > 3) {
            for (uint64_t i = 0; i < n; i++) {
                uint32_t sid = val[i];
                if (*(uint32_t *)(dart + 0xb98) <= sid) {
                    sptm_panic("%s: %s %s %s %u ... %s %u mus...", 0, 0, 0, 0, 0, 0);
                }
                uint64_t *p = (uint64_t *)((uintptr_t)bitset + ((uint64_t)(sid >> 3) & 0x1ffffff8));
                *p |= 1ULL << (sid & 0x3f);
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/* 000d4efc  sptm_dart_sid_setup                                       */
/* ------------------------------------------------------------------ */
/* FUN_000d4efc @ 0x000d4efc   (est. sptm_dart_sid_setup)
 * Ghidra: void FUN_000d4efc(long param_1,ulong param_2,undefined8 *param_3,
 *                           undefined8 param_4,uint param_5,int param_6,
 *                           uint param_7)
 * Configures one SID (param_2) of a DART (param_1). Validates the SID
 * (must be < dart SID count 0xb98; SID 0 is rejected when APF-mode is
 * on), allocates a SID entry via sptm_dart_sid_alloc (FUN_000d5a40),
 * then reads the per-SID "vm-base"/"vm-size" DT props (optionally
 * overriding with an 8-byte region) and programs the SID's VM window
 * into its entry, resolves the PT-region ("pt-region") and optionally
 * programs a carveout paddr (checking the global carveout table
 * DAT_000950d0), and installs the leaf PTE with the correct APF/type
 * bits. Marks the SID entry present and in-use, and triggers the
 * TLB/PTE-region setup via sptm_dart_sid_walk_teardown
 * (FUN_000d5bd8) when the PT region resolves.
 * Confidence: low
 * Notes: heavy use of the per-SID entry array at param_1+0x238
 *   (stride 8) and the per-SID VM window globals (0xb7c/0xb78). */
void sptm_dart_sid_setup(uintptr_t dart, uint64_t sid, uintptr_t *iter,
    uintptr_t node, uint32_t vm_align, int vm_align_rem, uint32_t flag)
{
    uint32_t sid32 = (uint32_t)sid;
    if (*(uint32_t *)(dart + 0xb98) <= sid32) {
        sptm_panic("%s: %s %s %s %u ... SID %u is g...", 0, 0, 0, 0, 0);
    }
    if ((sid32 == 0) && (*(uint8_t *)(dart + 0xbe6) & 1)) {
        sptm_panic("%s: %s %s %s %u ... SID 0 is in...", 0, 0, 0, 0, 0);
    }
    sptm_dart_sid_alloc(dart, sid, 0);

    /* Per-SID VM window: read "vm-base"/"vm-size" (optionally overridden by
     * a single 8-byte "pt-region" style property). */
    uint64_t *val = NULL;
    uint32_t size = 0;
    uint32_t ignored = 0;
    sptm_dt_prop_name((uintptr_t)&ignored);
    int rc = sptm_dt_get_prop(node, (const char *)&ignored, (uintptr_t *)&val, &size, iter[0], iter[1]);
    uint32_t vm_start = 0, vm_size = 0;
    if ((rc == 1) && size != 0) goto bad_sid_size;
    if (val != NULL) {
        if (*(uint8_t *)(dart + 0xbe6) & 1) {
            sptm_panic("%s: %s %s %s %u ... APF bypass a...", 0, 0, 0, 0, 0);
        }
        *(uint32_t *)(*(uintptr_t *)(dart + sid32 * 8 + 0x238) + 0x18) |= 4;
    }
    uint64_t e = *(uintptr_t *)(dart + 0x238 + sid32 * 8);
    vm_start = *(uint32_t *)(dart + 0xb7c);
    *(uint32_t *)(e + 0x14) = vm_start;
    uint32_t top = *(uint32_t *)(dart + 0xb78);
    *(uint32_t *)(e + 0x10) = top;
    uint32_t end = top - vm_start;
    if (top < vm_start) goto overflow;

    /* vm-base override */
    sptm_dt_prop_name((uintptr_t)&ignored);
    rc = sptm_dt_get_prop(node, (const char *)&ignored, (uintptr_t *)&val, &size, iter[0], iter[1]);
    if ((rc == 1) && size != 0) {
        if (size != 8) goto bad_sid_size;
        if (val != NULL) vm_start = (uint32_t)(*val >> 0xe);
    } else if (val != NULL) {
        sptm_panic("%s: %s %s %s %u ... vm_base %u m...", 0, 0, 0, 0, 0);
    }
    /* vm-size override */
    sptm_dt_prop_name((uintptr_t)&ignored);
    rc = sptm_dt_get_prop(node, (const char *)&ignored, (uintptr_t *)&val, &size, iter[0], iter[1]);
    if ((rc == 1) && size != 0) {
        if (size != 8) goto bad_sid_size;
        if (val != NULL) end = (uint32_t)(*val >> 0xe);
    } else if (val != NULL) {
        sptm_panic("%s: %s %s %s %u ... vm_size %u m...", 0, 0, 0, 0, 0);
    }
    if ((uint64_t)vm_start + end < (uint64_t)vm_start) goto overflow;
    {
        uint32_t base2 = *(uint32_t *)(dart + 0xb7c);
        uint32_t range = *(uint32_t *)(dart + 0xb78) - base2;
        if (*(uint32_t *)(dart + 0xb78) < base2) goto overflow;
        if (vm_start == base2 && end == range) {
            end = *(uint32_t *)(*(uintptr_t *)(dart + 0x238 + sid32 * 8) + 0x10);
        } else {
            if ((flag & 1) == 0) {
                sptm_panic("%s: %s %s %s %u ... %hu Per SI...", 0, 0, 0, 0, 0);
            }
            if (*(uint8_t *)(dart + 0xbe6) & 1) {
                sptm_panic("%s: %s %s %s %u ... SID %u per...", 0, 0, 0, 0, 0);
            }
            if (vm_start < base2 || range < end || range + base2 < vm_start + end) {
                sptm_panic("%s: %s %s %s %u ... Per SID %u ...", 0, 0, 0, 0, 0);
            }
            if (end - 0x40 > 0xbffffc0) {
                sptm_panic("%s: %s %s %s %u ... Per SID %u ...", 0, 0, 0, 0, 0);
            }
            int adj = (vm_align_rem == 0 || vm_align < 2) ? 0 : vm_align_rem - (int32_t)vm_align;
            end = vm_start + (uint32_t)adj + end;
            *(uint32_t *)(e + 0x10) = end;
            *(uint32_t *)(e + 0x14) = vm_start;
        }
    }
    /* SID end-page bound. */
    {
        uint32_t base2 = *(uint32_t *)(dart + 0xb7c);
        uint32_t bound = (base2 >> 0x1a == 0) ? 0x400000 : 0x10000000;
        if (bound < end) {
            sptm_panic("%s: %s %s %s %u ... SID %u end p...", 0, 0, 0, 0, 0);
        }
    }
    /* PT-region resolution + carveout. */
    sptm_dt_prop_name((uintptr_t)&ignored);
    rc = sptm_dt_get_prop(node, (const char *)&ignored, (uintptr_t *)&val, &size, iter[0], iter[1]);
    if (rc == 1) {
        if (val == NULL) goto no_pt_region;
        /* pt-region present: 8-byte {pa, len} pair selects carveout path */
        {
            uintptr_t entry = *(uintptr_t *)(dart + 0x238 + sid32 * 8);
            if ((*(uint32_t *)(entry + 0x18) >> 7) & 1) {
                sptm_panic("%s: %s %s %s %u ... SID %u rem...", 0, 0, 0, 0, 0);
            }
            uint32_t perm = 8;
            if (*(uint32_t *)(entry + 0x10) < 0x4400001) perm = 0;
            *(uint32_t *)(entry + 0x18) = perm | (*(uint32_t *)(entry + 0x18) & 0xffffff77);
        }
        goto after_pt;
no_pt_region:
        *(uint8_t *)(*(uintptr_t *)(dart + 0x238 + sid32 * 8) + 0x1e) = 0;
        goto after_pt;
    } else {
        if (val != NULL) {
            sptm_panic("%s: %s %s %s %u ... pt_region ...", 0, 0, 0, 0, 0);
        }
        uintptr_t entry = *(uintptr_t *)(dart + 0x238 + sid32 * 8);
        uint32_t fl = *(uint32_t *)(entry + 0x18);
        if ((fl >> 7) & 1) {
            sptm_panic("%s: %s %s %s %u ... SID %u rem...", 0, 0, 0, 0, 0);
        }
        *(uint32_t *)(entry + 0x18) = fl & 0xffffff7e;
        *(uint32_t *)(entry + 0x18) = *(uint32_t *)(entry + 0x18) & 0xfffffff7;
        *(uint32_t *)(entry + 0x18) = *(uint32_t *)(entry + 0x18) | 2;
        uintptr_t *pe = (uintptr_t *)(entry + 0x10);
        *(uint32_t *)(pe + 1) = 0;
    }
after_pt:
    /* Record the SID in the per-dart bitsets and raise the max-SID cursor. */
    sptm_dt_prop_name((uintptr_t)&ignored);
    rc = sptm_dt_get_prop(node, (const char *)&ignored, (uintptr_t *)&val, &size, iter[0], iter[1]);
    uint64_t bit = 1ULL << (sid & 0x3f);
    if (rc != 1 || size == 0) {
        if (val == NULL) {
            bit = 1ULL << (sid & 0x3f);
        } else {
            if (*(uint8_t *)(dart + 0xbe7) & 1) {
                sptm_panic("%s: %s %s %s %u ... Cannot spec...", 0, 0, 0, 0, 0);
            }
            uintptr_t b = dart + (sid32 >> 6) * 8;
            *(uint64_t *)(b + 0xa58) |= bit;
        }
        uintptr_t b2 = dart + (sid32 >> 6) * 8;
        *(uint64_t *)(b2 + 0xa38) |= bit;
        if (*(uint32_t *)(dart + 0xba0) < sid32) {
            *(uint32_t *)(dart + 0xba0) = sid32;
        }
        return;
    }
bad_sid_size:
    sptm_panic("%s: %s %s %s %d ... invalid %s si...", 0, 0, 0, 0, 0);
overflow:
    sptm_panic("%s: %s %s %s %u ... overflow...", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d5a40  sptm_dart_sid_alloc                                       */
/* ------------------------------------------------------------------ */
/* FUN_000d5a40 @ 0x000d5a40   (est. sptm_dart_sid_alloc)
 * Ghidra: void FUN_000d5a40(long param_1,uint param_2,undefined1 param_3)
 * Allocates a per-SID entry descriptor for SID param_2 of DART param_1
 * (SID must be < the dart SID count 0xb98; "invalid_SID" panic). If the
 * SID entry is already present or in-use (high bit of +0x18 set), panics
 * "SID %u alre...". Otherwise a 0x20-byte entry is boot-allocated, its
 * VM-window fields initialized from dart+0xb78, the type/flags byte set
 * from param_3, the entry stored at dart+0x238 + sid*8, the SID bitset at
 * dart+0xa38 marked, and the max-SID cursor (dart+0xba0) raised.
 * Confidence: high */
void sptm_dart_sid_alloc(uintptr_t dart, uint32_t sid, uint8_t type)
{
    if (*(uint32_t *)(dart + 0xb98) <= sid) {
        sptm_panic("%s: %s %s %s %u ... invalid SID...", 0, 0, 0, 0, 0);
    }
    uintptr_t entry = *(uintptr_t *)(dart + 0x238 + (uint64_t)sid * 8);
    if (entry == 0 || (*(int8_t *)(entry + 0x18) < 0)) {
        uint64_t *bits = (uint64_t *)(dart + 0xa38);
        uint64_t bit = 1ULL << (sid & 0x3f);
        if ((*(uint64_t *)(bits + (uint64_t)(sid >> 6) * 8) & bit) == 0) {
            if (g_boot_alloc_base == 0 || g_boot_alloc_off - 0x3fe1 > 0xffffffffffffbfff) {
                g_boot_alloc_base = sptm_boot_alloc(1);
                g_boot_alloc_off = 0;
            }
            uint64_t *e = (uint64_t *)(g_boot_alloc_base + g_boot_alloc_off);
            g_boot_alloc_off += 0x20;
            e[0] = 0;
            uint64_t vm = *(uint64_t *)(dart + 0xb78);
            e[2] = vm;
            uint32_t flags = 9;
            if ((uint32_t)vm < 0x4400001) flags = 1;
            *(uint32_t *)(e + 3) = flags | (*(uint32_t *)(e + 3) & 0xfffffff6);
            *(uint8_t *)((uintptr_t)e + 0x1c) = type;
            *(uint8_t *)((uintptr_t)e + 0x1f) = 0;
            *(uintptr_t *)(dart + 0x238 + (uint64_t)sid * 8) = (uintptr_t)e;
            *(uint64_t *)(bits + (uint64_t)(sid >> 6) * 8) |= bit;
            if (*(uint32_t *)(dart + 0xba0) < sid) {
                *(uint32_t *)(dart + 0xba0) = sid;
            }
            return;
        }
    }
    sptm_panic("%s: %s %s %s %u ... SID %u alre...", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d5bd8  sptm_dart_sid_walk_teardown                               */
/* ------------------------------------------------------------------ */
/* FUN_000d5bd8 @ 0x000d5bd8   (est. sptm_dart_sid_walk_teardown)
 * Ghidra: void FUN_000d5bd8(long param_1,ulong param_2,ulong param_3,
 *                           uint param_4)
 * Recursively walks and tears down the page-table subtree for one SID of
 * a DART, level by level (param_4 = current level, called with
 * param_4+1 on recursion). For each present table/leaf entry it validates
 * the entry against the TZ-domain config (per-level TZ-D enable/disable
 * windows in dart+0xb00..0xb1c), refuses to free an entry when the SID is
 * a remap target (dart+0xb28) or when the entry's carveout does not fall
 * in a legal SPTM/IO carveout range, and recurses into child tables.
 * The level-3 leaves are released with the IO frame allocator
 * (FUN_000e56ac) when in the trusted carveout.
 * Confidence: low
 * Notes: the per-level TZ-D range tables are DAT_000130d8/DAT_000130f8;
 *   recursion depth 4, 0x800 leaves max per table. */
void sptm_dart_sid_walk_teardown(uintptr_t dart, uint64_t sid, uint64_t va,
    uint32_t level)
{
    uintptr_t entry = *(uintptr_t *)(dart + 0x238 + (sid & 0xffffffff) * 8);
    uint64_t *table = *(uint64_t **)(entry + 8);
    if (table == NULL || va < table[0] || table[1] <= va) {
        sptm_panic("%s: %s %s %s %u ... SID %u leve...", 0, 0, 0, 0, 0);
    }
    uint64_t table_va = table[2];
    if (table_va == 0 || (((uint32_t)sid < *(uint32_t *)(dart + 0xb98)) &&
        (*(uint8_t *)(entry + 0x1d) & 1))) {
        sptm_panic("%s: %s %s %s %u ... Unable to c...", 0, 0, 0, 0, 0);
    }
    for (uint64_t i = 0; i < 0x800; i++) {
        uint64_t pte = *(uint64_t *)((va - table[0]) + table_va + i * 8);
        if (pte & 1) {
            uint64_t paddr = (pte & 0x3ffffffc00) << 4;
            if (*(uintptr_t *)(dart + 0xb28) != 0 && va != *(uintptr_t *)(dart + 0xb28)) {
                /* Not the live SID; validate TZ-D windows before freeing. */
                if (level == 3) {
                    if (g_pmap_io_range_count != 0 && *g_pmap_io_ranges <= paddr) {
                        uint64_t *last = g_pmap_io_ranges + (g_pmap_io_range_count - 1) * 3;
                        if (paddr < last[1] + last[0]) {
                            sptm_frame_translate(dart, paddr, 0x4000);
                        }
                    }
                    sptm_frame_alloc(paddr, 2, 0);
                }
            } else {
                /* Live SID: validate the TZ-D config for this level. */
                uint32_t tzcfg = *(uint32_t *)(dart + 0xafc);
                uint32_t lvl = level;
                uint64_t lo, hi;
                if (lvl == 1) { lo = 0; hi = 0; }
                else {
                    lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                        (*(uint32_t *)(dart + 0xb00 + (lvl - 1) * 0xc) >> 2)) & 0x3fffff) >>
                        (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                    hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                        (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                        (*(uint32_t *)(dart + 0xb04 + (lvl - 1) * 0xc) >> 2) & 0x3fffff)) >>
                        (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                }
                if ((tzcfg & 1) == 0) {
                    if ((tzcfg >> 1) & 1) {
                        if (lvl == 1) { lo = 0; hi = 0; }
                        else {
                            lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (*(uint32_t *)(dart + 0xb0c) >> 2)) & 0x3fffff) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                            hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                                (*(uint32_t *)(dart + 0xb10) >> 2) & 0x3fffff)) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                        }
                        if (i <= hi && lo <= i) goto free_entry;
                    }
                    if ((tzcfg >> 2) & 1) {
                        if (lvl == 1) { lo = 0; hi = 0; }
                        else {
                            lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (*(uint32_t *)(dart + 0xb18) >> 2)) & 0x3fffff) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                            hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                                (*(uint32_t *)(dart + 0xb1c) >> 2) & 0x3fffff)) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                        }
                        if (i < lo || hi < i) {
                            sptm_panic("%s: %s %s %s %u ... SID %u TZ-D...", 0, 0, 0, 0, 0);
                        }
                        goto free_entry;
                    }
                    sptm_panic("%s: %s %s %s %u ... SID %u TZ-D...", 0, 0, 0, 0, 0);
free_entry:
                    if ((pte & 0xffffffc0000003fe) != 0) {
                        sptm_panic("%s: %s %s %s %u ... SID %u leaf...", 0, 0, 0, 0, 0);
                    }
                    sptm_dart_sid_walk_teardown(dart, sid, paddr, (level + 1) & 0xff);
                } else {
                    if (lvl == 1) { lo = 0; hi = 0; }
                    else {
                        lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                            (*(uint32_t *)(dart + 0xb00) >> 2)) & 0x3fffff) >>
                            (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                        hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                            (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                            (*(uint32_t *)(dart + 0xb04) >> 2) & 0x3fffff)) >>
                            (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                    }
                    if (i < lo || hi < i) goto tzdis_check;
                    goto free_entry;
tzdis_check:
                    if ((tzcfg >> 1) & 1) {
                        if (lvl == 1) { lo = 0; hi = 0; }
                        else {
                            lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (*(uint32_t *)(dart + 0xb0c) >> 2)) & 0x3fffff) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                            hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                                (*(uint32_t *)(dart + 0xb10) >> 2) & 0x3fffff)) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                        }
                        if (i <= hi && lo <= i) goto free_entry;
                    }
                    if ((tzcfg >> 2) & 1) {
                        if (lvl == 1) { lo = 0; hi = 0; }
                        else {
                            lo = ((uint64_t)((uint32_t)*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (*(uint32_t *)(dart + 0xb18) >> 2)) & 0x3fffff) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                            hi = (*(uint64_t *)(0x130d8 + (uint64_t)lvl * 8) &
                                (uint64_t)((*(uint8_t *)(dart + 0xbf4) & 1) +
                                (*(uint32_t *)(dart + 0xb1c) >> 2) & 0x3fffff)) >>
                                (*(uint32_t *)(0x130f8 + (uint64_t)lvl * 4) & 0x3f);
                        }
                        if (i < lo || hi < i) {
                            sptm_panic("%s: %s %s %s %u ... SID %u TZ-D...", 0, 0, 0, 0, 0);
                        }
                        goto free_entry;
                    }
                    sptm_panic("%s: %s %s %s %u ... SID %u TZ-D...", 0, 0, 0, 0, 0);
                }
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/* 000d603c  sptm_type_id_lookup                                       */
/* ------------------------------------------------------------------ */
/* FUN_000d603c @ 0x000d603c   (est. sptm_type_id_lookup)
 * Ghidra: undefined8 FUN_000d603c(uint param_1)
 * Indexes the type-id table at DAT_00015578 (stride 8). param_1 must be
 * < 0x42 (64 entries), else panics "%u is not a valid type ID ...".
 * Confidence: high */
uint64_t sptm_type_id_lookup(uint32_t id)
{
    if (id < 0x42) {
        return *(uint64_t *)(0x15578 + (uint64_t)id * 8);
    }
    sptm_panic("%s: %u is not a valid type ID ...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d6088  sptm_iommu_lookup                                         */
/* ------------------------------------------------------------------ */
/* FUN_000d6088 @ 0x000d6088   (est. sptm_iommu_lookup)
 * Ghidra: undefined8 FUN_000d6088(ulong param_1)
 * Looks up an IOMMU dispatch entry keyed by param_1: the low 24 bits are
 * a type id and, when bit 24 is set, the upper byte (<<24) is an IOMMU id.
 * With IOMMU id 0 the lookup uses the global type table DAT_00015788;
 * with id 0xff the SPTM table DAT_00015ae8; otherwise it indexes the
 * per-IOMMU dispatch table at DAT_00095320 (id 0-8) and reads entry
 * [+0x58 + type*8]. A non-zero unknown id panics "IOMMU with id %d not
 * supported...".
 * Confidence: medium */
uint64_t sptm_iommu_lookup(uint64_t key)
{
    uint32_t iommu_id = (uint32_t)(key >> 0x18) & 0xff;
    uint64_t type = (uint32_t)key & 0xffffff;

    if ((key & 0xff000000) == 0) {
        return *(uint64_t *)(0x15788 + type * 8);
    }
    if (iommu_id != 0xff) {
        uint32_t id = iommu_id - 1;
        if ((id & 0xff) < 9) {
            uint64_t off = ((uint64_t)id & 0xff) * 0x20;
            if ((*(uint64_t *)(0x95320 + off) & 1) != 0) {
                return *(uint64_t *)(*(uintptr_t *)(0x95328 + off) + type * 8 + 0x58);
            }
        }
        sptm_panic("%s: IOMMU with id %d not support...", 0, 0, 0);
    }
    return *(uint64_t *)(0x15ae8 + type * 8);
}

/* ------------------------------------------------------------------ */
/* 000d6124  sptm_copy_phys_to_scratch_checked                         */
/* ------------------------------------------------------------------ */
/* FUN_000d6124 @ 0x000d6124   (est. sptm_copy_phys_to_scratch_checked)
 * Ghidra: long FUN_000d6124(long param_1,undefined8 param_2,undefined8
 *                           param_3,long param_4)
 * Translates a physical address (param_1) to a readable VA and copies
 * `num_ele * ele_size` bytes into the per-CPU scratch page at offset
 * param_4, under a per-frame rw-guard refcount. Gated: unless the
 * io-mapping-enforcement mode (bit param_1&3 of DAT_00095278) AND the
 * debug-enforce bit (DAT_001012d8 bit 0x12) are both set, it simply
 * returns param_1 without copying. When active it takes the frame's
 * rw-guard (+2 refcount), validates the frame is managed (class 1),
 * bounds the copy to the 0x4000 frame (panics 0xb/0x3d), resolves the
 * source VA (identity or via the committed-range table / slow path),
 * memcpys into the scratch, releases the guard, and returns the scratch
 * VA (or panics if the guard underflows).
 * NOTE: this is a copy-to-scratch helper, NOT a panic formatter as an
 * earlier sptm_internal.h extern guess labelled it (that guess is wrong;
 * the true noreturn panics are FUN_000f8804/FUN_000f8844).
 * Confidence: high */
uintptr_t sptm_copy_phys_to_scratch_checked(uintptr_t pa, uint64_t ele_size,
    uint64_t num_ele, uintptr_t scratch_off)
{
    if (((g_io_mapping_enforcement >> (pa & 3)) & 1) == 0 ||
        ((g_bootstrap_stages >> 0x12) & 1) == 0) {
        return pa;
    }
    sptm_ret16_t md = sptm_frame_metadata(pa, 0);
    uintptr_t err = md.hi;
    uint64_t frame = md.lo;
    if (err == 0 || scratch_off == 0) {
        sptm_panic("%s: Invalid element size num_ele...", 0, 0, 0);
    }
    uint16_t *guard;
    uintptr_t guard_err;
    if (frame < g_mem_phys_base || g_mem_phys_end <= frame) {
        sptm_ret16_t g = sptm_frame_va(frame);
        guard_err = g.hi;
        guard = (uint16_t *)((g.lo != 0) ? g.lo : 0x101f90);
    } else {
        guard = (uint16_t *)(0x95460 + ((frame - g_mem_phys_base) >> 10) * 8);
        guard_err = err;
    }
    sptm_lacquire();
    uint16_t rc = *guard;
    *guard = rc + 2;
    if (rc > 0xffe9 || (rc & 1) != 0) {
        sptm_panic_code(0x3d, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if ((g_fte_class[(uint64_t)guard[1] * 0x90] & 1) == 0) {
        sptm_panic_code(9, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    uint64_t nbytes = num_ele * ele_size;
    if (nbytes > 0x4000 || (frame & 0x3fff) + nbytes > 0x4000) {
        sptm_panic_code(0xb, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if (nbytes + scratch_off > 0x4000) {
        sptm_panic("%s: Offset into scratch page cro...", 0, 0, 0);
    }
    uintptr_t cpu = sptm_percpu_state();
    uintptr_t uat = *(uintptr_t *)(cpu + 0x1b);
    uintptr_t src;
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        src = (frame - g_mem_phys_base) + g_papt_va_base;
    } else {
        uintptr_t src_va = 0;
        if (g_committed_range_count != 0) {
            uintptr_t *r = g_committed_range_base;
            for (uint64_t i = 0; i < g_committed_range_count; i++) {
                if (r[0] <= frame && frame < r[0] + (uint64_t)r[2] * 0x4000) {
                    src_va = (frame - r[0]) + r[1];
                    goto src_found;
                }
                r += 3;
            }
        }
        src_va = sptm_va_translate_slow(frame);
src_found:
        src = src_va;
    }
    sptm_memcpy_bulk(uat + scratch_off, src, nbytes);
    uint16_t rc2 = *guard;
    *guard = rc2 - 2;
    sptm_lrelease();
    if (rc2 != 0 && (rc2 & 1) == 0) {
        return uat + scratch_off;
    }
    sptm_panic("%s: rw_guard_release_shared ... %p...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d617c  sptm_copy_phys_to_scratch                                 */
/* ------------------------------------------------------------------ */
/* FUN_000d617c @ 0x000d617c   (est. sptm_copy_phys_to_scratch)
 * Ghidra: long FUN_000d617c(ulong param_1,long param_2,long param_3,
 *                           long param_4)
 * Same translate-and-copy-to-scratch helper as sptm_copy_phys_to_scratch_
 * checked (000d6124) but ungated: always performs the guarded copy of
 * param_2*param_3 bytes from paddr param_1 into the scratch page at
 * offset param_4. ele_size (param_2) and num_ele (param_3) must be
 * non-zero (panic "Invalid element size num_ele"). Returns the scratch
 * VA, or panics on guard underflow.
 * Confidence: high */
uintptr_t sptm_copy_phys_to_scratch(uintptr_t pa, uint64_t ele_size,
    uint64_t num_ele, uintptr_t scratch_off)
{
    if (ele_size == 0 || num_ele == 0) {
        sptm_panic("%s: Invalid element size num_ele...", 0, 0, 0);
    }
    uint16_t *guard;
    uintptr_t guard_err;
    if (pa < g_mem_phys_base || g_mem_phys_end <= pa) {
        sptm_ret16_t g = sptm_frame_va(pa);
        guard_err = g.hi;
        guard = (uint16_t *)((g.lo != 0) ? g.lo : 0x101f90);
    } else {
        guard = (uint16_t *)(0x95460 + ((pa - g_mem_phys_base) >> 10) * 8);
        guard_err = ele_size;
    }
    sptm_lacquire();
    uint16_t rc = *guard;
    *guard = rc + 2;
    if (rc > 0xffe9 || (rc & 1) != 0) {
        sptm_panic_code(0x3d, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if ((g_fte_class[(uint64_t)guard[1] * 0x90] & 1) == 0) {
        sptm_panic_code(9, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    uint64_t nbytes = num_ele * ele_size;
    if (nbytes > 0x4000 || (pa & 0x3fff) + nbytes > 0x4000) {
        sptm_panic_code(0xb, guard_err, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
    }
    if (nbytes + scratch_off > 0x4000) {
        sptm_panic("%s: Offset into scratch page cro...", 0, 0, 0);
    }
    uintptr_t cpu = sptm_percpu_state();
    uintptr_t uat = *(uintptr_t *)(cpu + 0x1b);
    uintptr_t src;
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        src = (pa - g_mem_phys_base) + g_papt_va_base;
    } else {
        uintptr_t src_va = 0;
        if (g_committed_range_count != 0) {
            uintptr_t *r = g_committed_range_base;
            for (uint64_t i = 0; i < g_committed_range_count; i++) {
                if (r[0] <= pa && pa < r[0] + (uint64_t)r[2] * 0x4000) {
                    src_va = (pa - r[0]) + r[1];
                    goto src_found2;
                }
                r += 3;
            }
        }
        src_va = sptm_va_translate_slow(pa);
src_found2:
        src = src_va;
    }
    sptm_memcpy_bulk(uat + scratch_off, src, nbytes);
    uint16_t rc2 = *guard;
    *guard = rc2 - 2;
    sptm_lrelease();
    if (rc2 != 0 && (rc2 & 1) == 0) {
        return uat + scratch_off;
    }
    sptm_panic("%s: rw_guard_release_shared ... %p...", 0, 0, 0);
}


/* ------------------------------------------------------------------ */
/* 000d64d0  sptm_io_filter_cmp                                        */
/* ------------------------------------------------------------------ */
/* FUN_000d64d0 @ 0x000d64d0   (est. sptm_io_filter_cmp)
 * Ghidra: uint FUN_000d64d0(uint *param_1,uint *param_2)
 * Comparator for 8-byte io-filter entries {u32 base; u16 offset; u16 len}.
 * Orders by base; on a base tie returns 1 if entry2's [offset,offset+len)
 * range fits at/under entry1's limit, else -1. Used by qsort over
 * g_io_filter_table and by the overlap scan.
 * Confidence: high */
uint32_t sptm_io_filter_cmp(uint32_t *a, uint32_t *b)
{
    uint32_t abase = *a, bbase = *b;
    if (bbase < abase) return 0xffffffff;
    if (abase < bbase) return 0;
    uint16_t boff = (uint16_t)b[1];
    uint16_t blen = (uint16_t)((uintptr_t)b + 6);
    if ((uint32_t)blen + (uint32_t)boff <= (uint32_t)(uint16_t)a[1]) {
        return 1;
    }
    uint32_t alim = (uint32_t)(uint16_t)((uintptr_t)a + 6) + (uint32_t)(uint16_t)a[1];
    return -(uint32_t)(alim < (uint32_t)boff || alim == (uint32_t)boff);
}

/* ------------------------------------------------------------------ */
/* 000d6e64  sptm_io_range_cmp                                         */
/* ------------------------------------------------------------------ */
/* FUN_000d6e64 @ 0x000d6e64   (est. sptm_io_range_cmp)
 * Ghidra: uint FUN_000d6e64(long param_1,long param_2)
 * Comparator for the IO-range table entries (each a 0x10-byte row whose
 * byte 2 holds the FTE class). Requires both entries to be class 6
 * (managed IO) else panics "Type %d class of FTE %p %d"; orders by the
 * stored page index at offset +8.
 * Confidence: high */
uint32_t sptm_io_range_cmp(uintptr_t a, uintptr_t b)
{
    if (g_fte_class[(uint64_t)*(uint8_t *)(a + 2) * 0x90] == 0x06 &&
        g_fte_class[(uint64_t)*(uint8_t *)(b + 2) * 0x90] == 0x06) {
        uint32_t ar = *(uint32_t *)(a + 8);
        uint32_t br = *(uint32_t *)(b + 8);
        if (br < ar) return 0xffffffff;
        if (ar < br) return 0;
        return 0;
    }
    sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d6f00  sptm_papt_walk                                            */
/* ------------------------------------------------------------------ */
/* FUN_000d6f00 @ 0x000d6f00   (est. sptm_papt_walk)
 * Ghidra: ulong * FUN_000d6f00(long param_1,ulong param_2,uint param_3,
 *                              ulong *param_4,ulong *param_5)
 * Walks the PAPT from the root FTE descriptor param_1 down to the entry
 * for virtual address param_2 at the requested level param_3 (0..3).
 * The root must be class 1 (SPTM). Each level indexes the table by the
 * per-level shift/mask from the level table (plVar10, DAT_00019c68) and
 * descends through child table frames (class 2 validated with the
 * "Found non page table frame" and level-set panics). The intermediate
 * table paddr is written to *param_4 when the walk passes level
 * param_3-1, and the final (target-level) VA is stored to *param_5.
 * Returns the PTE pointer (or NULL when a level is missing).
 * Confidence: high */
uint64_t *sptm_papt_walk(uintptr_t root, uint64_t va, uint32_t level,
    uint64_t *table_out, uint64_t *va_out)
{
    if (g_fte_class[(uint64_t)*(uint8_t *)(root + 2) * 0x90] != 0x01) {
        sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
    }
    uint64_t *leveltab = *(uint64_t **)(0x19c68 + (uint64_t)*(uint8_t *)(root + 0xc) * 8);
    uint32_t conf = (uint32_t)leveltab[7];
    sptm_ret16_t r = sptm_fte_info(root);
    uint64_t table_va = r.lo;
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        table_va = (table_va - g_mem_phys_base) + g_papt_va_base;
    } else {
        uint64_t *ranges = g_committed_range_base;
        if (g_committed_range_count != 0) {
            for (uint64_t i = 0; i < g_committed_range_count; i++) {
                if (ranges[0] <= table_va && table_va < ranges[0] + (uint64_t)ranges[2] * 0x4000) {
                    table_va = (table_va - ranges[0]) + ranges[1];
                    goto root_resolved;
                }
                ranges += 3;
            }
        }
        table_va = sptm_va_translate_slow(table_va);
root_resolved:
        ;
    }
    uint32_t cur = conf & 3;
    uint64_t entry_va = table_va;
    uint64_t *pte = (uint64_t *)(entry_va +
        ((leveltab[0xc] & va & *(uint64_t *)((uintptr_t)leveltab + cur * 0x38 + 0x18)) >>
         (*(uint64_t *)((uintptr_t)leveltab + cur * 0x38 + 0x10) & 0x3f) & 0xffffffff) * 8);
    uint64_t val = *pte;
    uint64_t next_pa = 0;
    if (cur != level) {
        for (;;) {
            if (table_out != NULL && level - 1 == cur) {
                *table_out = (uint64_t)pte;
            }
            if ((~(uint32_t)val & 3) != 0) {
                if (table_out != NULL) {
                    *table_out = (uint64_t)pte;
                }
                return NULL;
            }
            uint64_t next_pa = val & 0xfffffffff000;
            uint16_t *guard;
            if (next_pa < g_mem_phys_base || g_mem_phys_end <= next_pa) {
                sptm_ret16_t g = sptm_frame_va(next_pa);
                guard = (uint16_t *)((g.lo != 0) ? g.lo : 0x101f90);
            } else {
                guard = (uint16_t *)(0x95460 + ((next_pa - g_mem_phys_base) >> 10) * 8);
            }
            if (g_fte_class[(uint64_t)guard[1] * 0x90] != 0x02) {
                sptm_panic("%s: Found non page table frame d...", 0, 0, 0, 0);
            }
            if ((next_pa & (uint64_t)~(-1 << (*(uint32_t *)(leveltab + 10) & 0x1f))) != 0) {
                sptm_panic_code(0x53, 0, "%s: %s: %d: ... %s: 0x%llx, ... %s: 0x%llx", 0, 0, 0, 0, 0);
            }
            if ((int)cur + 1 != (uint32_t)guard[2]) {
                sptm_panic("%s: Incorrect level set in page t...", 0, 0, 0, 0);
            }
            /* translate child table paddr -> VA */
            if (((g_bootstrap_stages >> 8) & 1) == 0) {
                entry_va = (next_pa - g_mem_phys_base) + g_papt_va_base;
            } else {
                uint64_t *ranges = g_committed_range_base;
                uint64_t found = 0;
                if (g_committed_range_count != 0) {
                    for (uint64_t i = 0; i < g_committed_range_count; i++) {
                        if (ranges[0] <= next_pa && next_pa < ranges[0] + (uint64_t)ranges[2] * 0x4000) {
                            entry_va = (next_pa - ranges[0]) + ranges[1];
                            found = 1;
                            break;
                        }
                        ranges += 3;
                    }
                }
                if (!found) entry_va = sptm_va_translate_slow(next_pa);
            }
            cur++;
            if (cur == 4) return NULL;
            pte = (uint64_t *)(entry_va +
                ((leveltab[0xc] & va & *(uint64_t *)((uintptr_t)leveltab + cur * 0x38 + 0x18)) >>
                 (*(uint64_t *)((uintptr_t)leveltab + cur * 0x38 + 0x10) & 0x3f) & 0xffffffff) * 8);
            val = *pte;
            if (cur == level) break;
        }
    }
    if (va_out != NULL) {
        *va_out = next_pa;
    }
    return pte;
}

/* ------------------------------------------------------------------ */
/* 000d7348  sptm_update_papt_pte                                      */
/* ------------------------------------------------------------------ */
/* FUN_000d7348 @ 0x000d7348   (est. sptm_update_papt_pte)
 * Ghidra: undefined8 FUN_000d7348(ulong param_1,uint param_2,ulong param_3,
 *                                 uint param_4)
 * Updates the PAPT leaf PTE covering paddr param_1. Validates the paddr
 * is managed (panic "paddr isn't managed"), the flag set param_4 is legal
 * (bits 2-5 only, else "invalid flag"), and that when the leaf-update bit
 * is set the guard is present. Resolves the PTE via a walk to level 3,
 * then recomputes the entry value: type (param_2) is folded in (special
 * handling for types 10/3 that read the frame-type table for the AP bits),
 * cache attribute (param_3) is encoded into bits 2-6 when the attr bit is
 * set, and the paddr is re-encoded. Finally the cache/TLB maintenance is
 * issued (sptm_slice_update / DSB / ISB / DMB) and, when the TLB-flush bit
 * is set, a TLB invalidate is done. Returns 5 on a deferred-flush path,
 * else 0.
 * Confidence: medium
 * Notes: the pte value paddr encoding uses 0x603 present leaf bits. */
uint64_t sptm_update_papt_pte(uintptr_t paddr, uint32_t type, uint64_t attr,
    uint32_t flags)
{
    if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
        sptm_panic("%s: paddr isn't managed %llx...", 0, 0, 0);
    }
    if (flags == 0 || (flags & 0x3c) != 0) {
        sptm_panic("%s: invalid flag found while upd...", 0, 0, 0);
    }
    if ((flags & 1) && ((*(uint16_t *)(0x95460 + ((paddr - g_mem_phys_base) >> 10) * 8) & 1) == 0)) {
        sptm_panic("%s: Attempted to update PAPT per...", 0, 0, 0);
    }
    uintptr_t pte_va;
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        pte_va = (paddr - g_mem_phys_base) + g_papt_va_base;
    } else {
        uintptr_t *ranges = g_committed_range_base;
        uintptr_t found = 0;
        if (g_committed_range_count != 0) {
            for (uint64_t i = 0; i < g_committed_range_count; i++) {
                if (ranges[0] <= paddr && paddr < ranges[0] + (uint64_t)ranges[2] * 0x4000) {
                    pte_va = (paddr - ranges[0]) + ranges[1];
                    found = 1;
                    break;
                }
                ranges += 3;
            }
        }
        if (!found) pte_va = sptm_va_translate_slow(paddr);
    }
    uint16_t *root_guard;
    if (g_papt_root_pa < g_mem_phys_base || g_mem_phys_end <= g_papt_root_pa) {
        root_guard = (uint16_t *)sptm_frame_va(g_papt_root_pa).lo;
    } else {
        root_guard = (uint16_t *)(0x95460 + ((g_papt_root_pa - g_mem_phys_base) >> 10) * 8);
    }
    uint64_t *pte = sptm_papt_walk((uintptr_t)root_guard, pte_va, 3, NULL, NULL);
    uint64_t old = *pte;
    uint64_t val = old;
    if (flags & 1) {
        if (type == 0xff) {
            val = 0;
            goto write_pte;
        }
        val = old & 0xff9fffffffffff3f;
        if ((old & 3) != 3) {
            val = (paddr & 0xfffffffff000) | 0x603;
        }
        uint16_t *guard;
        if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
            guard = (uint16_t *)sptm_frame_va(paddr).lo;
        } else {
            guard = (uint16_t *)(0x95460 + ((paddr - g_mem_phys_base) >> 10) * 8);
        }
        if ((type & 0xf) == 10 || (type & 0xf) == 3) {
            uint8_t ap = g_fte_class4[(uint64_t)guard[1] * 0x90];
            val |= ((uint64_t)(ap & 0xc) << 4) | ((uint64_t)(ap & 3) << 0x35);
        } else {
            val |= ((uint64_t)(type & 3) << 0x35) | ((uint64_t)((type & 0xc) << 4));
        }
    }
    if (((flags >> 1) & 1) && (val & 3) == 3) {
        if (attr > 7) {
            sptm_panic("%s: invalid cache attribute inde...", 0, 0, 0);
        }
        val = val & 0xffffffffffffffe3 | (attr & 0x3f) << 2;
    }
write_pte:
    *pte = val;
    {
        uint64_t a = old & 0x14;
        if (((~(uint32_t)val & 0x14) == 0 || a != 0x14) && ((int8_t)flags < 0)) {
            return 5;   /* deferred flush path */
        }
        if ((old & 3) == 3) {
            sptm_dsb(2, 2, 0);
            uint64_t mode = 5;
            if (a == 0x14) mode = 1;
            sptm_slice_update(g_papt_root_pa, pte_va, 1, mode);
            if (a == 0x14) {
                sptm_dsb(2, 3, 0);
            } else {
                sptm_dsb(2, 3, 1);
            }
        } else {
            sptm_dmb(2, 3);
        }
        sptm_isb();
    }
    if ((flags >> 6) & 1) {
        sptm_slice_tlbi_flush(pte_va, 0x4000);
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* 000d7cf8  sptm_build_table_desc                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d7cf8 @ 0x000d7cf8   (est. sptm_build_table_desc)
 * Ghidra: ulong FUN_000d7cf8(long param_1,long param_2,ulong param_3,
 *                            ulong param_4)
 * Builds a page-table (interior) descriptor word for the given level.
 * param_1 is the number of pages below this level (must be < 0x200000,
 * else panic "expected %llx < npages < ..."), param_2 the child table
 * paddr, param_3 the VA being covered and param_4 the level bit offset.
 * The resulting descriptor packs: level bits, child table paddr, the
 * low-index bits of param_3, and a page-count-derived next-level offset.
 * Confidence: medium
 * Notes: pure bit-packing; returns the 64-bit table descriptor. */
uint64_t sptm_build_table_desc(uint64_t npages, uint64_t child_pa,
    uint64_t va, uint64_t level_shift)
{
    if (npages - 2 < 0x1fffff) {
        uint64_t level = 0;
        if (clz64(npages - 1) != 0x3f) {
            level = (0x3e - (uint64_t)clz64(npages - 1)) / 5;
        }
        uint64_t bits = level * 5 + 1;
        int32_t i = 1 << (bits & 0x1f);
        uint64_t page_ct = ((npages + (uint64_t)i - 1) & ~((uint64_t)i - 1)) >> (bits & 0x3f);
        return ((va >> (level_shift & 0x3f)) & 0x1fffffffff) |
               (child_pa << 0x30) |
               (((level_shift >> 1) << 0x2e) + 0xfffec00000000000) |
               (level << 0x2c) |
               (page_ct << 0x27) - 0x8000000000;
    }
    sptm_panic("%s: expected %llx < npages < ...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d7f80  sptm_announce_bootstrap_feature                           */
/* ------------------------------------------------------------------ */
/* FUN_000d7f80 @ 0x000d7f80   (est. sptm_announce_bootstrap_feature)
 * Ghidra: void FUN_000d7f80(ulong param_1)
 * Sets the given bootstrap-stage/feature bit in g_bootstrap_stages (with
 * a release barrier); panics "Attempted to announce bootstrap..." if the
 * bit was already set (i.e. each stage may only be entered once).
 * Confidence: high */
void sptm_announce_bootstrap_feature(uint64_t bit)
{
    uint64_t old = g_bootstrap_stages;
    g_bootstrap_stages = g_bootstrap_stages | bit;
    sptm_lrelease();
    if ((old & bit) == 0) {
        return;
    }
    sptm_panic("%s: Attempted to announce bootst...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d1b2c  sptm_dart_register                                        */
/* ------------------------------------------------------------------ */
/* FUN_000d1b2c @ 0x000d1b2c   (est. sptm_dart_register)
 * Ghidra: void FUN_000d1b2c(undefined8 *param_1,long param_2,
 *                           undefined8 param_3)
 * Registers one "dart-t8110" device-tree node as a DART instance. Reads
 * the node's DT properties and fills a 0xc48-byte DART state block
 * (boot-allocated, stored at per-CPU state +0x10, and cross-linked into
 * the DART id table at g_dart_id_table): dart-id, sep, txm-secure-channel,
 * allow-vm-reserve/vm-reserve, dart-options, retention/no-sleep, perf
 * counters, ioa-parent, real-time, mixed-bypass, flush-by-dva, dead
 * mappings, clamp-tlimits, vm-size/vm-base/vm-alignment, ignore-secondary,
 * allow-apf-sid-remap, TZ config (DAT_000064e4 block), sid-count, the
 * sid-trace/mcw/ocla/lft bitsets, ignore-sid-count-mismatch, remap pairs,
 * the sid table, exclave-sid, instance list (DART/SMMU/APF/GAPF/PIOGW/
 * PSWR/MUU instances), allow-pte-remap, dual-VC carveouts, APF slices,
 * clock-protection (slice-index + gapf/ps-wr-dis) and PIOGW PS protection.
 * Every step is bounds-validated with a distinct panic string; the APF
 * slice and PIOGW configuration in particular are gated on the pmap
 * range/carveout tables. This is the crown of the T8110 DART driver.
 * Confidence: low
 * Notes: heavy 0xc8a2000000000000-tagged pointer math; the instance tag
 *   list distinguishes "DART"(0x44515254),"SMMU"(0x534d4d55),
 *   "APF"(0x44415046),"GAPF"(0x47415046),"PGW "(0x20574750),
 *   "PSWR"(0x50535752). */
void sptm_dart_register(uintptr_t *dt, uintptr_t node, uint64_t sr_region)
{
    if (node == 0) {
        sptm_panic("%s: %s %s %s %d %s ... NULL", 0, 0, 0, 0, 0, 0);
    }
    uintptr_t *val = NULL;
    uint32_t vsize = 0;
    int rc = sptm_dt_get_prop(node, "dart-id", (uintptr_t *)&val, &vsize, dt[0], dt[1]);
    if (rc != 1) sptm_panic("%s: %s %s %s %d ... error: %d gett...", 0, 0, 0, 0, 0);
    if (vsize != 4) sptm_panic("%s: %s %s %s %d ... expected size...", 0, 0, 0, 0, 0);
    uint32_t dart_id = (uint32_t)*val;
    if (dart_id > 0xff) sptm_panic("%s: %s %s %s %d ... error: %d inva...", 0, 0, 0, 0, 0);
    if (g_dart_id_table[dart_id] != 0xffff) {
        sptm_panic("%s: %s %s %s %d ... DART_ID %u us...", 0, 0, 0, 0, 0);
    }
    rc = sptm_dt_get_prop(node, (const char *)0x7790, (uintptr_t *)&val, &vsize, dt[0], dt[1]);
    uintptr_t regs = (uintptr_t)val;
    if (rc != 1) sptm_panic("%s: %s %s %s %d ... error: %d gett...", 0, 0, 0, 0, 0);
    g_dart_id_table[dart_id] = (uint16_t)sptm_dart_state(regs);

    if (g_boot_alloc_base == 0 || g_boot_alloc_off - 0x33b9 > 0xffffffffffffbfff) {
        g_boot_alloc_base = sptm_boot_alloc(1);
        g_boot_alloc_off = 0;
    }
    uint64_t *dart = (uint64_t *)(g_boot_alloc_base + g_boot_alloc_off);
    g_boot_alloc_off += 0xc48;
    uintptr_t pcs = sptm_percpu_dart_state();
    *(uintptr_t *)(pcs + 0x10) = (uintptr_t)dart;
    dart[0x187] = sr_region;             /* exclave SID state ptr */
    dart[0] = regs;                      /* register base */

    uint8_t is_sep = (sptm_dt_prop_u32(regs, "dart-sep", 8) == 0);
    *(uint8_t *)((uintptr_t)dart + 0xbf6) = is_sep;
    uint8_t *val8 = NULL; uint32_t s8 = 0;
    uint8_t has_txm = 0;
    if (sptm_dt_get_prop(node, "txm-secure-channel-base", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1 &&
        sptm_dt_get_prop(node, "txm-secure-channel-size", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1) {
        has_txm = *(uint8_t *)((uintptr_t)dart + 0xbf6);
    }
    *(uint8_t *)((uintptr_t)dart + 0xbf9) = has_txm & 1;
    *(uint8_t *)((uintptr_t)dart + 0xbfa) =
        sptm_dt_get_prop(node, "allow-vm-reserve-mapping", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    uint64_t *rval = NULL; uint32_t rsize = 0;
    rc = sptm_dt_get_prop(node, "vm-reserve", (uintptr_t *)&rval, &rsize, dt[0], dt[1]);
    if (rc == 1 && (*(uint8_t *)((uintptr_t)dart + 0xbfa) & 1)) {
        sptm_dart_check_vm_reserve_size((uintptr_t)dart, rsize);
        uint64_t rs = rval[0], re = rval[1];
        dart[0x171] = rs;
        dart[0x172] = re;
        if (re <= rs) sptm_panic("%s: %s dart %p %s %u ... Start of th...", 0, 0, 0, 0, 0);
    } else {
        dart[0x171] = 0;
        dart[0x172] = 0;
    }
    *(uint8_t *)((uintptr_t)dart + 0xbde) = (uint8_t)dart_id;
    *(uint8_t *)((uintptr_t)dart + 0xbdf) = 0;
    uint32_t *oval = NULL; uint32_t osize = 0;
    rc = sptm_dt_get_prop(node, "dart-options", (uintptr_t *)&oval, &osize, dt[0], dt[1]);
    uint8_t options_bit = 0;
    if (rc == -1) {
        options_bit = 0;
    } else {
        if (osize != 4) goto bad_state;
        options_bit = (*oval >> 4) & 1;   /* bit4 = strict/no-apf mode */
    }
    *(uint8_t *)((uintptr_t)dart + 0xbe6) = options_bit;
    int retention = sptm_dt_get_prop(node, "retention", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    *(uint8_t *)((uintptr_t)dart + 0xbe3) = retention;
    int no_sleep = sptm_dt_get_prop(node, "no-sleep", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    *(uint8_t *)((uintptr_t)dart + 0xbe4) = no_sleep;
    if (no_sleep && retention) {
        sptm_panic("%s: %s dart %p %s %u ... %s and %s a...", 0, 0, 0, 0, 0);
    }
    uint8_t perf = 0;
    if (g_debug_enabled & 1) {
        perf = sptm_dt_get_prop(node, "enable-perf-counters", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    }
    *(uint8_t *)((uintptr_t)dart + 0xbe5) = perf;
    rc = sptm_dt_get_prop(node, "ioa-parent", (uintptr_t *)&rval, &rsize, dt[0], dt[1]);
    if (rc == 1) {
        if (rsize != 0x10) goto bad_state;
        dart[0x166] = rval[0];
    }
    *(uint8_t *)((uintptr_t)dart + 0xbe7) = sptm_dt_get_prop(node, "real-time", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    *(uint8_t *)((uintptr_t)dart + 0xbe9) = sptm_dt_get_prop(node, "allow-mixed-bypass-mode", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    rc = sptm_dt_get_prop(node, "flush-by-dva", (uintptr_t *)&oval, &osize, dt[0], dt[1]);
    uint8_t flush_present = 0;
    if (rc == 1) {
        if (osize != 4) goto bad_state;
        *(uint8_t *)((uintptr_t)dart + 0xbeb) = (*oval != 0);
        flush_present = 1;
    }
    *(uint8_t *)((uintptr_t)dart + 0xbea) = flush_present;
    *(uint8_t *)((uintptr_t)dart + 0xbec) = sptm_dt_get_prop(node, "noncompliant-dead-mappings", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    *(uint8_t *)((uintptr_t)dart + 0xbee) = sptm_dt_get_prop(node, "clamp-tlimits", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;

    rc = sptm_dt_get_prop(node, "vm-size", (uintptr_t *)&rval, &rsize, dt[0], dt[1]);
    if (rc != 1) goto missing_prop;
    if (rsize != 8) goto bad_state;
    uint64_t vm_size = rval[0];
    if (vm_size == 0) sptm_panic("%s: %s dart %p %s %u ... vm_size mus...", 0, 0, 0, 0, 0);
    if (vm_size >> 0x14 == 0) sptm_panic("%s: %s dart %p %s %u ... invalid vm...", 0, 0, 0, 0, 0);
    rc = sptm_dt_get_prop(node, "vm-base", (uintptr_t *)&rval, &rsize, dt[0], dt[1]);
    if (rc != 1) goto missing_prop;
    if (rsize != 8) goto bad_state;
    uint64_t vm_base = rval[0];
    uint64_t base_bits = vm_base >> 0x28;
    uint64_t hi_bound = (base_bits == 0) ? 0x1000000000 : 0x30000000000;
    uint64_t vm_bound = (base_bits == 0) ? 0x1000000000 : 0x40000000000;
    if (vm_bound <= vm_base) sptm_panic("%s: %s dart %p %s %u ... vm_base %llx l...", 0, 0, 0, 0, 0);
    if (hi_bound < vm_size) sptm_panic("%s: %s dart %p %s %u ... vm_size %llx l...", 0, 0, 0, 0, 0);
    if (vm_bound < vm_base + vm_size) sptm_panic("%s: %s dart %p %s %u ... end of vm r...", 0, 0, 0, 0, 0);
    *(uint32_t *)((uintptr_t)dart + 0xb7c) = (uint32_t)(vm_base >> 0xe);
    *(uint32_t *)(dart + 0x16f) = (uint32_t)((vm_base + vm_size) >> 0xe);
    uint32_t vm_align = 0;
    int vm_align_rem = 0;
    rc = sptm_dt_get_prop(node, "vm-alignment", (uintptr_t *)&oval, &osize, dt[0], dt[1]);
    if (rc == 1) {
        if (osize - 4 > 8) sptm_panic("%s: %s dart %p %s %u ... invalid siz...", 0, 0, 0, 0, 0);
        vm_align = *oval;
        if (vm_align - 1 > 0x3f || popcount(vm_align) > 1) {
            sptm_panic("%s: %s dart %p %s %u ... invalid vm...", 0, 0, 0, 0, 0);
        }
        if (vm_align < 2) {
            vm_align = 1;
            vm_align_rem = 0;
        } else {
            uint32_t base2 = *(uint32_t *)((uintptr_t)dart + 0xb7c);
            vm_align_rem = base2 - (base2 / vm_align) * vm_align;
            if (vm_align_rem != 0) {
                *(uint32_t *)((uintptr_t)dart + 0xb7c) = (vm_align - vm_align_rem) + base2;
                *(uint32_t *)(dart + 0x16f) = *(int32_t *)(dart + 0x16f) - (vm_align - vm_align_rem);
            }
        }
    }
    *(uint8_t *)((uintptr_t)dart + 0xbf3) = sptm_dt_get_prop(node, "ignore-secondary", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    *(uint8_t *)((uintptr_t)dart + 0xbf1) = sptm_dt_get_prop(node, "allow-apf-sid-remap", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;

    val8 = NULL; s8 = 0;
    rc = sptm_dt_get_prop(node, (const char *)0x64e4, (uintptr_t *)&val8, &s8, dt[0], dt[1]);
    if (rc == 1) {
        if (s8 != 0x38) goto bad_state;
        sptm_memcpy_bulk((uintptr_t)(dart + 0x15f), (uintptr_t)val8, 0x38);
        *(uint8_t *)((uintptr_t)dart + 0xbf4) = sptm_dt_get_prop(node, "inclusive-tz-range", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    }
    if (*(uint32_t *)(dart + 0x15f) > 1) sptm_panic("%s: %s dart %p %s %u ... TZ_select_g...", 0, 0, 0, 0, 0);
    uint32_t tzcfg = *(uint32_t *)((uintptr_t)dart + 0xafc);
    if (tzcfg > 7) sptm_panic("%s: %s dart %p %s %u ... TZ_config_g...", 0, 0, 0, 0, 0);
    for (uint32_t lvl = 0; lvl < 3; lvl++) {
        uint32_t en_lo = *(uint32_t *)(dart + 0x160 + lvl);
        uint32_t en_hi = *(uint32_t *)((uintptr_t)dart + 0xb04 + lvl * 0xc);
        uint32_t tzbit = 1u << lvl;
        if ((tzcfg & tzbit) == 0) {
            if (en_lo != 0 || en_hi != 0) sptm_panic("%s: %s dart %p %s %u ... Disabled_TZ...", 0, 0, 0, 0, 0);
        } else if (en_lo == 0 || en_hi == 0 ||
                   en_hi + (*(uint8_t *)((uintptr_t)dart + 0xbf4) & 1) <= en_lo) {
            sptm_panic("%s: %s dart %p %s %u ... Enabled_TZT...", 0, 0, 0, 0, 0);
        }
    }

    uint32_t *sidc = NULL; uint32_t scsize = 0;
    rc = sptm_dt_get_prop(node, "sid-count", (uintptr_t *)&sidc, &scsize, dt[0], dt[1]);
    if (rc == 1) {
        if (scsize != 4) goto bad_state;
        uint32_t sid_count = *sidc;
        *(uint32_t *)(dart + 0x173) = sid_count;
        if (sid_count > 0x100) sptm_panic("%s: %s dart %p %s %u ... sid_count ...", 0, 0, 0, 0, 0);
    } else {
        *(uint32_t *)(dart + 0x173) = 0x10;
    }
    sptm_dart_sid_property_set((uintptr_t)dart, dt[0], dt[1], node, (uint64_t *)(dart + 0x14f), "sid-trace");
    sptm_dart_sid_property_set((uintptr_t)dart, dt[0], dt[1], node, (uint64_t *)(dart + 0x153), "sid-mcw");
    sptm_dart_sid_property_set((uintptr_t)dart, dt[0], dt[1], node, (uint64_t *)(dart + 0x157), "sid-ocla");
    sptm_dart_sid_property_set((uintptr_t)dart, dt[0], dt[1], node, (uint64_t *)(dart + 0x15b), "sid-lft");
    *(uint8_t *)(dart + 0x17f) = sptm_dt_get_prop(node, "ignore-sid-count-mismatch", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
    uint32_t *mm = NULL; uint32_t msz = 0;
    if (sptm_dt_get_prop(node, "max-sids-in-mismatch", (uintptr_t *)&mm, &msz, dt[0], dt[1]) == 1) {
        *(uint32_t *)(dart + 0x17b) = *mm;
    } else {
        *(uint32_t *)(dart + 0x17b) = 0;
    }

    /* SID remap pairs. */
    uint32_t *remap = NULL; uint32_t remsz = 0;
    rc = sptm_dt_get_prop(node, "remap", (uintptr_t *)&remap, &remsz, dt[0], dt[1]);
    if (rc == 1) {
        if (*(uint8_t *)((uintptr_t)dart + 0xbe6) & 1) sptm_panic("%s: %s dart %p %s %u ... SID Remap i...", 0, 0, 0, 0, 0);
        if ((remsz & 3) != 0) sptm_panic("%s: %s dart %p %s %u ... Malformed ...", 0, 0, 0, 0, 0);
        for (uint32_t i = 0; i + 1 < remsz; i += 2) {
            uint8_t src = (uint8_t)remap[i];
            uint8_t dst = (uint8_t)(remap[i] >> 8);
            if (src != 0 || dst != 0) {
                uint32_t cnt = *(uint32_t *)(dart + 0x173);
                if ((cnt < src || cnt == src || cnt <= dst) &&
                    ((*(uint8_t *)(dart + 0x17f) & 1) == 0 ||
                     (*(uint32_t *)(dart + 0x17b) <= src ||
                      (*(uint32_t *)(dart + 0x17b) < dst || *(uint32_t *)(dart + 0x17b) == dst)))) {
                    sptm_panic("%s: %s dart %p %s %u ... remap %u >...", 0, 0, 0, 0, 0);
                }
                if (dart[src + 0x47] != 0) sptm_panic("%s: %s dart %p %s %u ... Remap_src_S...", 0, 0, 0, 0, 0);
                if (dart[dst + 0x47] != 0) sptm_panic("%s: %s dart %p %s %u ... Remap_dst_S...", 0, 0, 0, 0, 0);
                if (src == dst) sptm_panic("%s: %s dart %p %s %u ... SID %u SID...", 0, 0, 0, 0, 0);
                if (g_boot_alloc_base == 0 || g_boot_alloc_off - 0x3fe1 > 0xffffffffffffbfff) {
                    g_boot_alloc_base = sptm_boot_alloc(1);
                    g_boot_alloc_off = 0;
                }
                uint64_t *e = (uint64_t *)(g_boot_alloc_base + g_boot_alloc_off);
                g_boot_alloc_off += 0x20;
                *(uint32_t *)((uintptr_t)e + 0x18) = (*(uint32_t *)((uintptr_t)e + 0x18) & 0xffff007f) |
                    ((uint32_t)dst << 8) | 0x80;
                dart[src + 0x47] = (uintptr_t)e;
                uint64_t *bits = (uint64_t *)((uintptr_t)dart + ((uint64_t)(src >> 3) & 0x18) + 0xa38);
                *bits |= 1ULL << (src & 0x3f);
            }
        }
    }

    /* SID table (DAT_000063ea). */
    uint32_t *sidtab = NULL; uint32_t stsz = 0;
    rc = sptm_dt_get_prop(node, (const char *)0x63ea, (uintptr_t *)&sidtab, &stsz, dt[0], dt[1]);
    if (rc != 1 && (*(uint8_t *)((uintptr_t)dart + 0xbe6) & 1) == 0) goto missing_prop;
    uint64_t n_sids = stsz >> 2;
    if (stsz > 0x403) sptm_panic("%s: %s dart %p %s %u ... sid_count ...", 0, 0, 0, 0, 0);
    if (stsz < 4 && (*(uint8_t *)((uintptr_t)dart + 0xbe6) & 1) == 0) sptm_panic("%s: %s dart %p %s %u ... SID_count ...", 0, 0, 0, 0, 0);
    if ((stsz & 3) != 0) sptm_panic("%s: %s dart %p %s %u ... malformed ...", 0, 0, 0, 0, 0);
    if (*(uint32_t *)(dart + 0x173) < n_sids) sptm_panic("%s: %s dart %p %s %u ... mismatch_be...", 0, 0, 0, 0, 0);
    for (uint64_t i = 0; i < n_sids; i++) {
        sptm_dart_sid_setup((uintptr_t)dart, (uint8_t)sidtab[i], dt, node, vm_align, vm_align_rem,
            (vm_base & 0xffffff0000000000) != 0);
    }
    if ((*(uint8_t *)((uintptr_t)dart + 0xbe6) & 1) && *(uint32_t *)(dart + 0x173) > 1) {
        for (uint32_t i = 1; i < *(uint32_t *)(dart + 0x173); i++) {
            if (((dart[(i >> 6) + 0x147] >> (i & 0x3f)) & 1) == 0) {
                sptm_dart_sid_alloc((uintptr_t)dart, i & 0xff, 1);
            }
        }
    }
    uint32_t *xsid = NULL; uint32_t xsz = 0;
    rc = sptm_dt_get_prop(node, "exclave-sid", (uintptr_t *)&xsid, &xsz, dt[0], dt[1]);
    if (rc == 1) {
        uint64_t xn = xsz >> 2;
        if (xsz > 0x403) sptm_panic("%s: %s dart %p %s %u ... exclave_sid...", 0, 0, 0, 0, 0);
        for (uint64_t i = 0; i < xn; i++) {
            uint8_t sid = (uint8_t)xsid[i];
            sptm_dart_sid_setup((uintptr_t)dart, sid, dt, node, vm_align, vm_align_rem,
                (vm_base & 0xffffff0000000000) != 0);
            *(uint8_t *)(dart[sid + 0x47] + 0x1d) = 1;
        }
    }

    /* instance list */
    int32_t *inst = NULL; uint32_t isz = 0;
    sptm_dt_get_prop(node, "instance", (uintptr_t *)&inst, &isz, dt[0], dt[1]);
    if (isz == 0 || (isz & 0xf) != 0) sptm_panic("%s: %s dart %p %s %u ... malformed ...", 0, 0, 0, 0, 0);
    uint32_t n_inst = isz >> 4;
    if (isz > 0x12f) sptm_panic("%s: %s dart %p %s %u ... invalid %in...", 0, 0, 0, 0, 0);
    uint32_t n_dart = 0, n_pgw = 0, n_pswr = 0, n_muu = 0, n_apf = 0, n_gapf = 0;
    uint32_t inst_tags[14] = {0};
    for (uint32_t i = 0; i < n_inst; i++) {
        uint32_t tag = (uint32_t)inst[i];
        switch (tag) {
        case 0x44415046: if (n_apf > 3) goto too_many_inst; inst_tags[n_apf + 6] = i; n_apf++; break;
        case 0x44415254: if (n_dart > 3) goto too_many_inst; inst_tags[n_dart] = i; n_dart++; break;
        case 0x47415046: if (n_gapf > 1) goto too_many_inst; inst_tags[n_gapf + 4] = i; n_gapf++; break;
        case 0x50475720: if (n_pgw > 1) goto too_many_inst; inst_tags[n_pgw + 2] = i; n_pgw++; break;
        case 0x50535752: if (n_pswr > 1) goto too_many_inst; inst_tags[n_pswr] = i; n_pswr++; break;
        case 0x534d4d55: if (n_muu > 3) goto too_many_inst; inst_tags[n_muu + 10] = i; n_muu++; break;
        default: sptm_panic("%s: %s dart %p %s %u ... invalid_ins...", 0, 0, 0, 0, 0);
        }
    }
    *(int32_t *)((uintptr_t)dart + 0xba4) = (int32_t)n_dart;
    *(int32_t *)(dart + 0x175) = (int32_t)n_gapf;
    *(int32_t *)((uintptr_t)dart + 0xbac) = (int32_t)n_muu;
    *(int32_t *)(dart + 0x176) = (int32_t)n_pgw;
    *(int32_t *)(dart + 0x177) = (int32_t)n_pswr;

    rc = sptm_dt_get_prop(node, (const char *)0xd09e, (uintptr_t *)&inst, &isz, dt[0], dt[1]);
    if (rc == 1) {
        if ((isz & 0xf) != 0) sptm_panic("%s: %s dart %p %s %u ... incorrect s...", 0, 0, 0, 0, 0);
        if (n_inst != isz >> 4) sptm_panic("%s: %s dart %p %s %u ... %instance ...", 0, 0, 0, 0, 0);
        for (uint32_t i = 0; i < n_dart; i++) {
            uint64_t idx = inst_tags[i];
            uint64_t *blk = (uint64_t *)((uintptr_t)inst + idx * 0x10);
            if ((blk[1] & 0x3fff) != 0 || (blk[0] & 0x3fff) != 0) sptm_panic("%s: %s dart %p %s %u ... mis_aligned...", 0, 0, 0, 0, 0);
            sptm_ret16_t t = sptm_frame_translate(dt[0], blk[0], blk[1]);
            uint64_t pa = *(uint64_t *)((uintptr_t)inst + idx * 0x10 + 0x10);
            if (pa >> 0x2a != 0) goto too_high_pa;
            uint64_t base = sptm_frame_alloc(t.lo, pa >> 0xe, 0).lo;
            uint64_t *slot = dart + 1 + i * 0xf;
            *slot = base;
            if (base == 0xffffffff) goto invalid_alloc;
            uint8_t propbuf[0x40] = {0};
            sptm_dt_prop_name((uintptr_t)propbuf);
            uint64_t *r2 = NULL; uint32_t r2s = 0;
            rc = sptm_dt_get_prop(node, (const char *)propbuf, (uintptr_t *)&r2, &r2s, dt[0], dt[1]);
            if (rc == 1 && r2s != 0) {
                if ((r2s & 3) != 0) sptm_panic("%s: %s dart %p %s %u ... Malformed d...", 0, 0, 0, 0, 0);
                if (g_boot_alloc_base == 0 || g_boot_alloc_off - 0x3ff1 > 0xffffffffffffbfff) {
                    g_boot_alloc_base = sptm_boot_alloc(1);
                    g_boot_alloc_off = 0;
                }
                uint64_t alloc_off = g_boot_alloc_off;
                uint64_t *copy = (uint64_t *)(g_boot_alloc_base + alloc_off);
                g_boot_alloc_off += 0x10;
                slot[3] = (uintptr_t)copy;
                uint64_t entries = r2s / 0x18;
                if (entries * 0x18 - r2s != 0) sptm_panic("%s: %s dart %p %s %u ... Malformed d...", 0, 0, 0, 0, 0);
                if (r2s < 0x18) goto alloc_too_small;
                if ((r2s >> 4) > 0x800) goto alloc_too_large;
                uint64_t need = entries * 0xc;
                if (alloc_off == 0 || alloc_off + need > 0x4000) {
                    g_boot_alloc_base = sptm_boot_alloc(1);
                    alloc_off = 0;
                    copy = (uint64_t *)slot[3];
                    g_boot_alloc_off = 0;
                }
                g_boot_alloc_off = alloc_off + need;
                *(uint64_t *)(copy + 2) = g_boot_alloc_base + alloc_off;
                for (uint64_t j = 0; j < entries; j++) {
                    uint32_t *out = (uint32_t *)(g_boot_alloc_base + alloc_off + j * 0xc + 4);
                    out[-1] = (uint32_t)r2[j * 3];
                    out[0] = (uint32_t)r2[j * 3 + 1];
                    out[1] = (uint32_t)r2[j * 3 + 2];
                }
            }
        }
        for (uint32_t i = 0; i < n_muu; i++) {
            uint32_t idx = inst_tags[i + 10];
            uint64_t *blk = (uint64_t *)((uintptr_t)inst + idx * 0x10);
            uint64_t *slot = dart + 1 + (uint64_t)(uint32_t)blk[1] * 0xf;
            if (slot[0] == 0) sptm_panic("%s: %s dart %p %s %u ... Invalid DAR...", 0, 0, 0, 0, 0);
            uint64_t *e = (uint64_t *)((uintptr_t)inst + idx * 0x10);
            if (e[1] != 0x4000 || (e[0] & 0x3fff) != 0) sptm_panic("%s: %s dart %p %s %u ... smmu_instan...", 0, 0, 0, 0, 0);
            sptm_ret16_t t = sptm_frame_translate(dt[0], e[0], 0x4000);
            uint64_t pa = *(uint64_t *)((uintptr_t)inst + idx * 0x10 + 0x10);
            if (pa >> 0x2a != 0) goto too_high_pa;
            uint64_t base = sptm_frame_alloc(t.lo, pa >> 0xe, 0).lo;
            slot[1] = base;
            if (base == 0xffffffff) goto invalid_alloc;
        }
        *(uint8_t *)((uintptr_t)dart + 0xbef) = sptm_dt_get_prop(node, "allow-pte-remap", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
        if (*(uint8_t *)((uintptr_t)dart + 0xbef) && *(int32_t *)((uintptr_t)dart + 0xbac) == 0) {
            sptm_panic("%s: %s dart %p %s %u ... PTE_remap_n...", 0, 0, 0, 0, 0);
        }
        *(uint8_t *)(dart + 0x17e) = sptm_dt_get_prop(node, "pte-remap-carveout-only", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
        if (*(uint8_t *)(dart + 0x17e) && (*(uint8_t *)((uintptr_t)dart + 0xbef) & 1) == 0) {
            sptm_panic("%s: %s dart %p %s %u ... PTE_remap_f...", 0, 0, 0, 0, 0);
        }
        uint64_t carveout_base = g_mem_phys_base & 0xffffffffe0000000;
        if (carveout_base != 0x800000000 && carveout_base != 0x10000000000) {
            sptm_panic("%s: %s dart %p %s %u ... unexpected d...", 0, 0, 0, 0, 0);
        }
        for (uint32_t i = 0; i < n_apf; i++) {
            uint32_t idx = inst_tags[i + 6];
            if (*(uint8_t *)((uintptr_t)dart + 0xbe6) & 1) sptm_panic("%s: %s dart %p %s %u ... APF_is_inco...", 0, 0, 0, 0, 0);
            uint32_t dart_slot = (uint32_t)((int32_t *)((uintptr_t)inst + idx * 0x10))[1];
            uint8_t propbuf[0x40] = {0};
            sptm_dt_prop_name((uintptr_t)propbuf);
            uint64_t *dv = NULL; uint32_t dvs = 0;
            if (sptm_dt_get_prop(node, (const char *)propbuf, (uintptr_t *)&dv, &dvs, dt[0], dt[1]) == 1) {
                if (*(uint32_t *)(dart + 0x16e) != 0) sptm_panic("%s: %s dart %p %s %u ... Multiple_in...", 0, 0, 0, 0, 0);
                if ((dvs & 0xf) != 0) sptm_panic("%s: %s dart %p %s %u ... invalid_dua...", 0, 0, 0, 0, 0);
                if (dvs > 0x2f) sptm_panic("%s: %s dart %p %s %u ... num_dual_vc...", 0, 0, 0, 0, 0);
                *(uint32_t *)(dart + 0x16e) = dvs >> 4;
                *(uint32_t *)((uintptr_t)dart + 0xb74) = dart_slot;
                if (dvs != 0) {
                    dart[0x168] = dv[1];
                    dart[0x167] = dv[0];
                    if ((dv[0] & 0x3fff) != 0 || dv[0] < carveout_base || dv[0] == 0 ||
                        dv[1] <= dv[0] || (dv[1] & 0x3fff) != 0) goto bad_dualvc;
                    if (dvs != 0x10) {
                        dart[0x16a] = dv[3];
                        dart[0x169] = dv[2];
                        if ((dv[2] & 0x3fff) != 0 || dv[2] < carveout_base ||
                            dv[2] == 0 || dv[3] <= dv[2] || (dv[3] & 0x3fff) != 0) goto bad_dualvc;
                    }
                }
            }
            uint8_t pb[0x40] = {0};
            sptm_dt_prop_name((uintptr_t)pb);
            uint64_t *av = NULL; uint32_t avs = 0;
            if (sptm_dt_get_prop(node, (const char *)pb, (uintptr_t *)&av, &avs, dt[0], dt[1]) == 1) {
                uint64_t n_apfs = avs / 0x34;
                if (n_apfs * 0x34 - avs != 0) sptm_panic("%s: %s dart %p %s %u ... malformed_d...", 0, 0, 0, 0, 0);
                if (avs < 0x34) sptm_panic("%s: %s dart %p %s %u ... dapf_instan...", 0, 0, 0, 0, 0);
                if (avs > 0xd33) sptm_panic("%s: %s dart %p %s %u ... number_of_a...", 0, 0, 0, 0, 0);
                uint64_t *slot = dart + 1 + (uint64_t)dart_slot * 0xf;
                if (slot[0] == 0) sptm_panic("%s: %s dart %p %s %u ... Invalid_DAR...", 0, 0, 0, 0, 0);
                if (g_boot_alloc_base == 0 || g_boot_alloc_off - 0x3fe9 > 0xffffffffffffbfff) {
                    g_boot_alloc_base = sptm_boot_alloc(1);
                    g_boot_alloc_off = 0;
                }
                uint64_t *meta = (uint64_t *)(g_boot_alloc_base + g_boot_alloc_off);
                g_boot_alloc_off += 0x18;
                slot[2] = (uintptr_t)meta;
                uint64_t *e = (uint64_t *)((uintptr_t)inst + idx * 0x10);
                if (e[1] != 0x4000 || (e[0] & 0x3fff) != 0) sptm_panic("%s: %s dart %p %s %u ... apf_instanc...", 0, 0, 0, 0, 0);
                sptm_ret16_t t = sptm_frame_translate(dt[0], e[0], 0x4000);
                uint64_t apf_pa = *(uint64_t *)((uintptr_t)inst + idx * 0x10 + 0x10);
                if (apf_pa >> 0x2a != 0) goto too_high_pa;
                *(uint32_t *)(meta + 1) = (uint32_t)(avs / 0x34);
                uint64_t base = sptm_frame_alloc(t.lo, apf_pa >> 0xe, 0).lo;
                meta[0] = base;
                if (base == 0xffffffff) goto invalid_alloc;
                uint8_t pb2[0x40] = {0};
                sptm_dt_prop_name((uintptr_t)pb2);
                uint64_t *table2;
                if (g_boot_alloc_base == 0 || g_boot_alloc_off + n_apfs * 0x40 > 0x4000) {
                    g_boot_alloc_base = sptm_boot_alloc(1);
                    g_boot_alloc_off = 0;
                }
                table2 = (uint64_t *)(g_boot_alloc_base + g_boot_alloc_off);
                g_boot_alloc_off += n_apfs * 0x40;
                meta[2] = (uintptr_t)table2;
                uint64_t *ad = NULL; uint32_t ads = 0;
                if (sptm_dt_get_prop(node, (const char *)pb2, (uintptr_t *)&ad, &ads, dt[0], dt[1]) == 1) {
                    if ((ads & 3) != 0 || ads < 4) sptm_panic("%s: %s dart %p %s %u ... malformed_a...", 0, 0, 0, 0, 0);
                    for (uint32_t k = 0; k < ads / 4; k++) {
                        uint32_t apf_idx = ad[k];
                        if ((uint32_t)(avs / 0x34) <= apf_idx) sptm_panic("%s: %s dart %p %s %u ... allow_dram...", 0, 0, 0, 0, 0);
                        *(uint8_t *)((uintptr_t)table2 + (uint64_t)apf_idx * 0x40 + 0x38) = 1;
                    }
                }
                for (uint32_t k = 0; k < n_apfs; k++) {
                    uint8_t *src = (uint8_t *)((uintptr_t)av + k * 0x34);
                    uint32_t *dst = (uint32_t *)((uintptr_t)table2 + k * 0x40);
                    uint32_t flags = (src[0x19] & 3);
                    dst[0] = (dst[0] & 0xfffffffc) | flags;
                    flags = (dst[0] & 0xc) | flags | ((src[0x31] & 1) << 4);
                    dst[0] = (dst[0] & 0xffffffe0) | flags;
                    flags = flags | ((src[0x31] >> 1 & 1) << 5);
                    dst[0] = (dst[0] & 0xffffffc0) | flags;
                    dst[0] = (dst[0] & 0xfffffc00) | (dst[0] & 0xc0) | flags | ((src[0x18] & 3) << 8);
                    uint64_t lo = ((uint64_t)src[1] << 0x10) | ((uint64_t)src[3] << 0x18) | (uint64_t)src[0] |
                        (((uint64_t)src[3] << 0x10) | ((uint64_t)src[7] << 0x18) | (uint64_t)src[2]) << 0x20;
                    uint64_t hi = ((uint64_t)src[5] << 0x10) | ((uint64_t)src[0xb] << 0x18) | (uint64_t)src[4] |
                        (((uint64_t)src[7] << 0x10) | ((uint64_t)src[0xf] << 0x18) | (uint64_t)src[6]) << 0x20;
                    *(uint64_t *)(dst + 2) = lo;
                    *(uint64_t *)(dst + 4) = hi;
                    uint64_t lo2 = ((uint64_t)src[9] << 0x10) | ((uint64_t)src[0x13] << 0x18) | (uint64_t)src[8] |
                        (((uint64_t)src[0xb] << 0x10) | ((uint64_t)src[0x17] << 0x18) | (uint64_t)src[10]) << 0x20;
                    uint64_t hi2 = ((uint64_t)src[0xd] << 0x10) | ((uint64_t)src[0x1b] << 0x18) | (uint64_t)src[0xc] |
                        (((uint64_t)src[0xf] << 0x10) | ((uint64_t)src[0x1f] << 0x18) | (uint64_t)src[0xe]) << 0x20;
                    *(uint64_t *)(dst + 6) = lo2;
                    *(uint64_t *)(dst + 8) = hi2;
                    uint64_t lo3 = ((uint64_t)src[0x11] << 0x10) | ((uint64_t)src[0x23] << 0x18) | (uint64_t)src[0x10] |
                        (((uint64_t)src[0x13] << 0x10) | ((uint64_t)src[0x27] << 0x18) | (uint64_t)src[0x12]) << 0x20;
                    uint64_t hi3 = ((uint64_t)src[0x15] << 0x10) | ((uint64_t)src[0x2b] << 0x18) | (uint64_t)src[0x14] |
                        (((uint64_t)src[0x17] << 0x10) | ((uint64_t)src[0x2f] << 0x18) | (uint64_t)src[0x16]) << 0x20;
                    *(uint64_t *)(dst + 0xa) = lo3;
                    *(uint64_t *)(dst + 0xc) = hi3;
                    if (hi2 < lo2) sptm_panic("%s: %s dart %p %s %u ... end %llx <%...", 0, 0, 0, 0, 0);
                    uint32_t a4 = ((uint32_t)src[3] << 0x10) | ((uint32_t)src[7] << 0x18) | (uint32_t)src[2];
                    uint32_t b4 = ((uint32_t)src[7] << 0x10) | ((uint32_t)src[0xf] << 0x18) | (uint32_t)src[6];
                    uint64_t win0 = ((uint64_t)src[1] << 0x10) | ((uint64_t)src[3] << 0x18) | (uint64_t)src[0] | ((uint64_t)a4 << 0x20);
                    uint64_t win1 = ((uint64_t)src[5] << 0x10) | ((uint64_t)src[0xb] << 0x18) | (uint64_t)src[4] | ((uint64_t)b4 << 0x20);
                    if ((win0 < carveout_base && win1 < carveout_base)) {
                        if (dst[0xe] & 1) sptm_panic("%s: %s dart %p %s %u ... APF_slice...", 0, 0, 0, 0, 0);
                    } else {
                        for (uint64_t va = win1; win0 <= va; va -= 0x4000) {
                            if (g_mem_phys_base <= va && va < g_mem_phys_end) sptm_panic("%s: %s dart %p %s %u ... APF_slice...", 0, 0, 0, 0, 0);
                        }
                        uint32_t n_dvc = *(uint32_t *)(dart + 0x16e);
                        uint64_t *dvc = dart + 0x168;
                        uint64_t wl = win0 + 0x3fff & ~0x3fffULL;
                        uint64_t wh = win1 + 0x3fff & ~0x3fffULL;
                        int matched = 0;
                        for (uint32_t d = 0; d < n_dvc; d++) {
                            if (dvc[-1 + d * 2] == wl && dvc[d * 2] == wh) {
                                if (dst[0xe] & 1) sptm_panic("%s: %s dart %p %s %u ... APF_slice...", 0, 0, 0, 0, 0);
                                matched = 1;
                                break;
                            }
                        }
                        if (!matched) {
                            if ((dst[0xe] & 1) == 0) sptm_panic("%s: %s dart %p %s %u ... Invalid_lim...", 0, 0, 0, 0, 0);
                            if ((b4 >> 10) != 0 || (a4 >> 10) != 0) goto too_high_pa;
                            sptm_frame_alloc(win0, ((int)(win1 >> 0xe) - (int)(win0 >> 0xe)) + 1, 0);
                        }
                    }
                }
            }
        }
        if (n_gapf == 0) {
            if (g_gapf_mode != 0) {
missing_clock:
                sptm_panic("%s: %s dart %p %s %u ... %s clock_pr...", 0, 0, 0, 0, 0);
            }
            uint8_t pb[0x40] = {0};
            sptm_dt_prop_name((uintptr_t)pb);
            if (sptm_dt_get_prop(node, (const char *)pb, (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1) {
                sptm_panic("%s: %s dart %p %s %u ... %s proper...", 0, 0, 0, 0, 0);
            }
        } else {
            if ((g_gapf_mode & 1) == 0) goto missing_clock;
            *(uint8_t *)((uintptr_t)dart + 0xbf7) = sptm_dt_get_prop(node, "dart-ungang-shared-ps", (uintptr_t *)&val8, &s8, dt[0], dt[1]) == 1;
            uint32_t *sidx = NULL; uint32_t sidsz = 0;
            rc = sptm_dt_get_prop(node, "clock-protection-slice-index", (uintptr_t *)&sidx, &sidsz, dt[0], dt[1]);
            if (rc != 1) goto missing_clock2;
            if (sidsz != (uint32_t)(*(int32_t *)((uintptr_t)dart + 0xba4) * n_gapf * 4)) goto bad_state;
            for (uint32_t i = 0; i < n_gapf; i++) {
                uint32_t idx = inst_tags[i + 4];
                uint64_t *e = (uint64_t *)((uintptr_t)inst + idx * 0x10);
                if (e[1] != 0x4000 || (e[0] & 0x3fff) != 0) sptm_panic("%s: %s dart %p %s %u ... GAPF_instan...", 0, 0, 0, 0, 0);
                sptm_ret16_t t = sptm_frame_translate(dt[0], e[0], 0x4000);
                uint64_t pa = *(uint64_t *)((uintptr_t)inst + idx * 0x10 + 0x10);
                if (pa >> 0x2a != 0) goto too_high_pa;
                uint64_t *base = (uint64_t *)sptm_frame_alloc(t.lo, pa >> 0xe, 0).lo;
                uint64_t *slot = dart + 0x3d + i * 2;
                *slot = (uintptr_t)base;
                if (base == (uint64_t *)0xffffffff) goto invalid_alloc;
                if (*(uint32_t *)(dart + 0x175) <= i) goto invalid_gapf;
                if (base == NULL) goto null_check;
                if (base[8] != 1) sptm_panic("%s: %s dart %p %s %u ... Invalid GAP...", 0, 0, 0, 0, 0);
                if (base[9] != 0) sptm_panic("%s: %s dart %p %s %u ... Invalid GAP...", 0, 0, 0, 0, 0);
                *(uint32_t *)(slot + 1) = base[0] & 0x1ff;
                uint32_t n_d = *(uint32_t *)((uintptr_t)dart + 0xba4);
                for (uint32_t k = 0; k < n_d; k++) {
                    uint32_t sid = sidx[k + (uint32_t)n_d * i];
                    if (sid == 0) goto invalid_sid;
                    if (*(uint32_t *)(slot + 1) <= sid) sptm_panic("%s: %s dart %p %s %u ... Invalid %s...", 0, 0, 0, 0, 0);
                    if (i == 0 && (*(uint8_t *)((uintptr_t)dart + 0xbf7) & 1) && g_gapf_ungang_count != 0) {
                        for (uint32_t g = 0; g < g_gapf_ungang_count; g++) {
                            uint64_t *ge = (uint64_t *)(g_gapf_ungang_entries + (uint64_t)g * 0x10);
                            if (ge[0] == t.lo && ge[1] == sid) {
                                *(uint16_t *)((uintptr_t)ge + 0xc) += 1;
                                *(uint8_t *)((uintptr_t)dart + 0xbfb) = (uint8_t)g;
                                break;
                            }
                        }
                    }
                    *(uint32_t *)((uintptr_t)dart + (uint64_t)k * 0x78 + i * 4 + 0x28) = sid;
                    if (*(uint32_t *)(dart + 0x175) <= i) goto invalid_gapf;
                    uint64_t g = *slot;
                    if (g == 0) goto null_check;
                    uint32_t off = sid * 0x40;
                    if ((*(uint32_t *)(g + off + 0x100) & 0xffffffef) != 2) goto invalid_sid;
                    if (*(int32_t *)(g + off + 0x118) - *(int32_t *)(g + off + 0x110) != 3) {
                        sptm_panic("%s: %s dart %p %s %u ... Invalid sli...", 0, 0, 0, 0, 0);
                    }
                    if (dart[0x187] != 0) {
                        *(uint32_t *)(dart[0x187] + (uint64_t)sid * 4) = 2;
                        sptm_dmb(2, 3);
                    }
                }
            }
        }
        if (n_pgw != 0) {
            uint32_t *pio = NULL; uint32_t psz = 0;
            rc = sptm_dt_get_prop(node, "piogw-ps-protection", (uintptr_t *)&pio, &psz, dt[0], dt[1]);
            if (rc != 1 || psz - 1 > 0x22 || psz % 0xc != 0) sptm_panic("%s: %s dart %p %s %u ... Invalid %pi...", 0, 0, 0, 0, 0);
            *(int32_t *)((uintptr_t)dart + 0xbb4) = (int32_t)(((uint64_t)psz & 0xffffffff) * 0x15555556 >> 0x20);
            if (psz > 0xb) {
                uint32_t x1 = ((uint32_t)((uint8_t *)pio)[6] << 0x10) | ((uint32_t)((uint8_t *)pio)[7] << 0x18) |
                              (uint32_t)*(uint16_t *)((uintptr_t)pio + 2);
                uint32_t y1 = ((uint32_t)((uint8_t *)pio)[10] << 0x10) | ((uint32_t)((uint8_t *)pio)[0xb] << 0x18) |
                              (uint32_t)*(uint16_t *)((uintptr_t)pio + 4);
                *(uint32_t *)(dart + 0x16c) = y1;
                *(uint32_t *)((uintptr_t)dart + 0xb5c) = x1;
                uint32_t p0 = ((uint32_t)((uint8_t *)pio)[2] << 0x10) | ((uint32_t)((uint8_t *)pio)[3] << 0x18) |
                              (uint32_t)*(uint16_t *)pio;
                *(uint32_t *)(dart + 0x16b) = p0;
                if (p0 - 1 > 8 || (x1 == 0 && y1 == 0)) goto bad_pio;
                if (psz - 0xc > 0xb) {
                    uint32_t x2 = ((uint32_t)((uint8_t *)pio)[0x12] << 0x10) | ((uint32_t)((uint8_t *)pio)[0x13] << 0x18) |
                                  (uint32_t)*(uint16_t *)((uintptr_t)pio + 8);
                    uint32_t y2 = ((uint32_t)((uint8_t *)pio)[0x16] << 0x10) | ((uint32_t)((uint8_t *)pio)[0x17] << 0x18) |
                                  (uint32_t)*(uint16_t *)((uintptr_t)pio + 10);
                    *(uint32_t *)((uintptr_t)dart + 0xb6c) = y2;
                    *(uint32_t *)(dart + 0x16d) = x2;
                    uint32_t p1 = ((uint32_t)((uint8_t *)pio)[0xe] << 0x10) | ((uint32_t)((uint8_t *)pio)[0xf] << 0x18) |
                                  (uint32_t)*(uint16_t *)((uintptr_t)pio + 6);
                    *(uint32_t *)((uintptr_t)dart + 0xb64) = p1;
                    if (p1 - 1 > 8 || (x2 == 0 && y2 == 0)) goto bad_pio;
                }
            }
            uint64_t *pio_slot = dart + 0x41;
            for (uint32_t i = 0; i < n_pgw; i++) {
                uint32_t idx = inst_tags[i + 2];
                uint64_t *blk = (uint64_t *)((uintptr_t)inst + idx * 0x10);
                sptm_ret16_t t = sptm_frame_translate(dt[0], blk[0], blk[2]);
                if (blk[2] >> 0x2a != 0) goto too_high_pa;
                *pio_slot = sptm_frame_alloc(t.lo, blk[2] >> 0xe, 0).lo;
                pio_slot += 2;
            }
        }
        if (g_ps_wr_dis_mode != 0x01) {
            uint32_t cnt = *(uint32_t *)(dart + 0x173);
            for (uint32_t i = 0; i < cnt; i++) {
                if (dart[i + 0x47] != 0 && (*(uint8_t *)(dart[i + 0x47] + 0x1d) & 1) &&
                    *(int32_t *)((uintptr_t)dart + 0xba4) != 0) {
                    uint32_t *mask = (uint32_t *)((uintptr_t)dart + (i >> 5) * 4 + 0x34);
                    for (uint32_t d = 0; d < *(uint32_t *)((uintptr_t)dart + 0xba4); d++) {
                        *mask |= 1u << (i & 0x1f);
                        mask += 0x1e;
                    }
                }
            }
            return;
        }
        uint32_t *wrdis = NULL; uint32_t wrsz = 0;
        rc = sptm_dt_get_prop(node, "clock-protection-wr-dis-id", (uintptr_t *)&wrdis, &wrsz, dt[0], dt[1]);
        if (rc == 1 && wrsz == (uint32_t)(*(int32_t *)((uintptr_t)dart + 0xba4) * 2)) {
            uint32_t *dstate = NULL; uint32_t dsz = 0;
            rc = sptm_dt_get_prop(node, "clock-protection-dart-state", (uintptr_t *)&dstate, &dsz, dt[0], dt[1]);
            if (rc != 1) goto missing_clock2;
            if (dsz == (uint32_t)(*(int32_t *)((uintptr_t)dart + 0xba4))) {
                for (uint32_t i = 0; i < dsz; i++) {
                    uint8_t *dst = (uint8_t *)((uintptr_t)dart + 0x32 + i * 0x78);
                    dst[0] = ((uint8_t *)wrdis)[i];
                    dst[2] = ((uint8_t *)wrdis)[dsz + i];
                }
                for (uint32_t i = 0; i < n_pswr; i++) {
                    uint32_t idx = inst_tags[i];
                    uint64_t *blk = (uint64_t *)((uintptr_t)inst + idx * 0x10);
                    sptm_ret16_t t = sptm_frame_translate(dt[0], blk[0], blk[2]);
                    uint64_t *slot = dart + 0x45 + i;
                    *slot = sptm_frame_alloc(t.lo, 1, 0).lo;
                }
            }
        }
    }
missing_clock2:
    sptm_panic("%s: %s dart %p %s %u ... missing %s...", 0, 0, 0, 0, 0);
bad_state:
    sptm_panic("%s: %s %s %s %d ... state %p %s...", 0, 0, 0, 0, 0);
missing_prop:
    sptm_panic("%s: %s dart %p %s %u ... missing %s p...", 0, 0, 0, 0, 0);
too_many_inst:
    sptm_panic("%s: %s dart %p %s %u ... max %s inst...", 0, 0, 0, 0, 0);
too_high_pa:
    sptm_panic_code(0x6000021, 0, "%s: %s: %d: ... %s: 0x%llx", 0, 0, 0, 0, 0);
invalid_alloc:
    sptm_panic("%s: %s dart %p %s %u ... %s invalid...", 0, 0, 0, 0, 0);
alloc_too_small:
    sptm_panic("%s: %s %s %s %d ... alloc_size_mu...", 0, 0, 0, 0, 0);
alloc_too_large:
    sptm_panic("%s: %s %s %s %d ... allocation_re...", 0, 0, 0, 0, 0);
bad_dualvc:
    sptm_panic("%s: %s dart %p %s %u ... dual_VC_LLT...", 0, 0, 0, 0, 0);
invalid_sid:
    sptm_panic("%s: %s dart %p %s %u ... Invalid %s...", 0, 0, 0, 0, 0);
invalid_gapf:
    sptm_panic("%s: %s dart %p %s %u ... Invalid GAP...", 0, 0, 0, 0, 0);
null_check:
    sptm_panic("%s: %s dart %s %s %d %s ... NULL", 0, 0, 0, 0, 0, 0);
bad_pio:
    sptm_panic("%s: %s dart %p %s %u ... Invalid PIO...", 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d7fe4  sptm_papt_leaf_pte                                       */
/* ------------------------------------------------------------------ */
/* FUN_000d7fe4 @ 0x000d7fe4   (est. sptm_papt_leaf_pte)
 * Ghidra: long FUN_000d7fe4(ulong param_1)
 * Walks the PAPT from the root table (g_papt_root_pa) for virtual
 * address param_1 down to the level-3 (leaf) PTE. Translates each table
 * paddr to a VA using the identity window or the committed-range table,
 * and indexes by (va>>0x24 & 0x7ff), (va>>0x19 & 0x7ff) and
 * (va>>0xe & 0x7ff). Returns the leaf PTE pointer, or 0 if a level is
 * absent.
 * Confidence: high */
uintptr_t sptm_papt_leaf_pte(uint64_t va)
{
    uintptr_t table_va;
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        table_va = (g_papt_root_pa - g_mem_phys_base) + g_papt_va_base;
    } else {
        uintptr_t *r = g_committed_range_base;
        uintptr_t found = 0;
        if (g_committed_range_count != 0) {
            for (uint64_t i = 0; i < g_committed_range_count; i++) {
                if (r[0] <= g_papt_root_pa && g_papt_root_pa < r[0] + (uint64_t)r[2] * 0x4000) {
                    table_va = (g_papt_root_pa - r[0]) + r[1];
                    found = 1;
                    break;
                }
                r += 3;
            }
        }
        if (!found) table_va = sptm_va_translate_slow(g_papt_root_pa);
    }
    uint64_t e0 = *(uint64_t *)(table_va + (va >> 0x24 & 0x7ff) * 8);
    if ((~(uint32_t)e0 & 3) == 0) {
        uint64_t t1 = e0 & 0xfffffffff000;
        if (((g_bootstrap_stages >> 8) & 1) == 0) {
            table_va = (t1 - g_mem_phys_base) + g_papt_va_base;
        } else {
            uintptr_t *r = g_committed_range_base;
            uintptr_t found = 0;
            if (g_committed_range_count != 0) {
                for (uint64_t i = 0; i < g_committed_range_count; i++) {
                    if (r[0] <= t1 && t1 < r[0] + (uint64_t)r[2] * 0x4000) {
                        table_va = (t1 - r[0]) + r[1];
                        found = 1;
                        break;
                    }
                    r += 3;
                }
            }
            if (!found) table_va = sptm_va_translate_slow(t1);
        }
        uint64_t e1 = *(uint64_t *)(table_va + (va >> 0x19 & 0x7ff) * 8);
        if ((~(uint32_t)e1 & 3) == 0) {
            uint64_t t2 = e1 & 0xfffffffff000;
            if (((g_bootstrap_stages >> 8) & 1) == 0) {
                table_va = (t2 - g_mem_phys_base) + g_papt_va_base;
            } else {
                uintptr_t *r = g_committed_range_base;
                uintptr_t found = 0;
                if (g_committed_range_count != 0) {
                    for (uint64_t i = 0; i < g_committed_range_count; i++) {
                        if (r[0] <= t2 && t2 < r[0] + (uint64_t)r[2] * 0x4000) {
                            table_va = (t2 - r[0]) + r[1];
                            found = 1;
                            break;
                        }
                        r += 3;
                    }
                }
                if (!found) table_va = sptm_va_translate_slow(t2);
            }
            return table_va + (va >> 0xe & 0x7ff) * 8;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* 000d81bc  sptm_pa_to_va                                            */
/* ------------------------------------------------------------------ */
/* FUN_000d81bc @ 0x000d81bc   (est. sptm_pa_to_va)
 * Ghidra: long FUN_000d81bc(ulong param_1)
 * Pure paddr->PAPT VA translation. In the identity-window build
 * (g_bootstrap_stages bit 8 clear) returns (paddr - g_mem_phys_base) +
 * g_papt_va_base. Otherwise scans the committed-range table for a range
 * covering paddr and returns the range-relative VA, falling back to the
 * slow per-frame translator FUN_000e40ec.
 * Confidence: high */
uintptr_t sptm_pa_to_va(uint64_t paddr)
{
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        return (paddr - g_mem_phys_base) + g_papt_va_base;
    }
    uintptr_t *r = g_committed_range_base;
    if (g_committed_range_count != 0) {
        for (uint64_t i = 0; i < g_committed_range_count; i++) {
            if (r[0] <= paddr && paddr < r[0] + (uint64_t)r[2] * 0x4000) {
                return (paddr - r[0]) + r[1];
            }
            r += 3;
        }
    }
    return sptm_va_translate_slow(paddr);
}

/* ------------------------------------------------------------------ */
/* 000d823c  sptm_alloc_frames                                         */
/* ------------------------------------------------------------------ */
/* FUN_000d823c @ 0x000d823c   (est. sptm_alloc_frames)
 * Ghidra: long FUN_000d823c(uint param_1,ulong param_2,int param_3)
 * Allocates `param_2` contiguous 16K frames of type param_1 from one of
 * the three frame pools selected by param_3 (0 = PAPT/root pool at
 * g_fa_counter[2]/[3] bounded by 0x94000, 1 = pool at [4]/[5] bounded by
 * 0x95100, else the DAT_000950e4 pool). Advances the pool cursor, panics
 * "Exceeded available number of ..." on overflow, then for each frame:
 * writes its type into the frame-table entry (+2), zeroes the 16K frame
 * (sptm_bzero_chk) and re-tags it via the root-PTE type helpers
 * (sptm_papt_clear_type FUN_000d8914 or sptm_papt_update_root_pte
 * FUN_000d8784 depending on the frame-type table). Finally, if the root
 * is an 0x08-class table, it performs the DSB/TLB/ISB maintenance over
 * the whole run. Returns the base paddr of the allocation.
 * Confidence: medium */
uintptr_t sptm_alloc_frames(uint32_t type, uint64_t num_frames, int pool)
{
    if (((g_bootstrap_stages >> 0xb) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    int32_t n = (int32_t)num_frames;
    uint32_t base_idx;
    uint32_t *cursor;
    uint64_t limit;
    uintptr_t base_pa;
    if (pool == 0) {
        base_idx = g_fa_counter[2] + g_fa_counter[3];
        base_pa = g_mem_phys_base + (uint64_t)((n + (int32_t)base_idx) - 1) * 0x4000;
        base_pa = sptm_pa_to_va(base_pa);
        if (base_pa > 0x93fff) {
            sptm_panic("%s: Exceeded available number of...", 0, 0, 0);
        }
        cursor = &g_fa_counter[2];
    } else if (pool == 1) {
        base_idx = g_fa_counter[4] + g_fa_counter[5];
        base_pa = g_mem_phys_base + (uint64_t)((n + (int32_t)base_idx) - 1) * 0x4000;
        base_pa = sptm_pa_to_va(base_pa);
        if (base_pa >= 0x95100) {
            sptm_panic("%s: Exceeded available number of...", 0, 0, 0);
        }
        cursor = &g_fa_counter[4];
    } else {
        cursor = &g_fa_counter[0];
        base_idx = g_fa_counter[0] + g_fa_counter[1];
    }
    *cursor += (uint32_t)n;
    for (uint32_t idx = base_idx; idx < base_idx + (uint32_t)n; idx++) {
        uintptr_t fte = 0x95460 + idx * 0x10;
        *(uint8_t *)(fte + 2) = (uint8_t)type;
        uintptr_t pa = g_mem_phys_base + (uint64_t)idx * 0x4000;
        uintptr_t va = sptm_pa_to_va(pa);
        sptm_bzero_chk(va, 0x4000, 0xffffffffffffffffULL);
        if (((g_bootstrap_stages >> 8) & 1) != 0) {
            if (g_type_state[(uint64_t)type * 0x90] == -1) {
                sptm_papt_unmap_leaf(sptm_pa_to_va(pa));
            } else {
                sptm_papt_update_root_pte(sptm_pa_to_va(pa), g_type_state[(uint64_t)type * 0x90]);
            }
        }
    }
    uintptr_t va = sptm_pa_to_va(g_mem_phys_base + (uint64_t)base_idx * 0x4000);
    uint16_t *root_guard;
    if (g_papt_root_pa < g_mem_phys_base || g_mem_phys_end <= g_papt_root_pa) {
        root_guard = (uint16_t *)sptm_frame_va(g_papt_root_pa).lo;
    } else {
        root_guard = (uint16_t *)(0x95460 + ((g_papt_root_pa - g_mem_phys_base) >> 10) * 8);
    }
    if (*(uint8_t *)(root_guard + 1) == 0x08) {
        sptm_dsb(2, 2, 0);
        sptm_slice_tlbi_single(va, num_frames);
        sptm_dsb(1, 3, 1);
        sptm_isb();
    }
    return g_mem_phys_base + (uint64_t)base_idx * 0x4000;
}

/* ------------------------------------------------------------------ */
/* 000d8784  sptm_papt_update_root_pte                                */
/* ------------------------------------------------------------------ */
/* FUN_000d8784 @ 0x000d8784   (est. sptm_papt_update_root_pte)
 * Ghidra: void FUN_000d8784(undefined8 param_1,uint param_2)
 * Re-stamps the root PTE for the frame at VA param_1 with a new type
 * (param_2). Requires the post-PAPT build (bit 8 set) and pre-final
 * (bit 0x11 clear). Walks the leaf PTE; if present, clears the type/AP
 * bits and re-encodes param_2 (with frame-type-table-derived AP bits for
 * types 10/3).
 * Confidence: medium */
void sptm_papt_update_root_pte(uintptr_t va, uint32_t type)
{
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        sptm_panic("%s: Expected bootstrap stages no...", 0, 0, 0);
    }
    if (((g_bootstrap_stages >> 0x11) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    uint64_t *pte = (uint64_t *)sptm_papt_leaf_pte(va);
    if (pte != NULL && (~(uint32_t)*pte & 3) == 0) {
        uint64_t val = *pte;
        uint64_t pa = val & 0xfffffffff000;
        uint16_t *guard;
        if (pa < g_mem_phys_base || g_mem_phys_end <= pa) {
            guard = (uint16_t *)sptm_frame_va(pa).lo;
        } else {
            guard = (uint16_t *)(0x95460 + ((pa - g_mem_phys_base) >> 10) * 8);
        }
        val = val & 0xff9fffffffffff23;
        if ((type & 0xf) == 10 || (type & 0xf) == 3) {
            uint8_t ap = g_fte_class4[(uint64_t)guard[1] * 0x90];
            val |= ((uint64_t)(ap & 0xc) << 4) | ((uint64_t)(ap & 3) << 0x35);
        } else {
            val |= ((uint64_t)(type & 3) << 0x35) | ((uint64_t)((type & 0xc) << 4));
        }
        *pte = val;
    }
}

/* ------------------------------------------------------------------ */
/* 000d8914  sptm_papt_unmap_leaf                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d8914 @ 0x000d8914   (est. sptm_papt_unmap_leaf)
 * Ghidra: void FUN_000d8914(void)
 * Clears (unmaps) the PAPT leaf PTE for the current VA (from the stack
 * argument FUN_000d7fe4 consumes, i.e. the translated frame VA). Panics
 * "PAPT PTE could not be reached" if no leaf and "Invalid PTE found
 * while attem..." if the entry is not present. On a present entry the
 * PTE is zeroed and the frame-table refcount (offset +8 of the FTE,
 * class-2) decremented, panicking on underflow.
 * Confidence: high */
void sptm_papt_unmap_leaf(uintptr_t va)
{
    uint64_t *pte = (uint64_t *)sptm_papt_leaf_pte(va);
    if (pte == NULL) {
        sptm_panic("%s: PAPT PTE could not be reache...", 0, 0, 0);
    }
    if ((~(uint32_t)*pte & 3) == 0) {
        *pte = 0;
        uint64_t pa = sptm_va_to_pa(va);
        uint16_t *guard;
        if (pa < g_mem_phys_base || g_mem_phys_end <= pa) {
            guard = (uint16_t *)sptm_frame_va(pa).lo;
        } else {
            guard = (uint16_t *)(0x95460 + ((pa - g_mem_phys_base) >> 10) * 8);
        }
        if (g_fte_class[(uint64_t)guard[1] * 0x90] == 0x02) {
            uint16_t rc = guard[4];
            guard[4] = rc - 1;
            if (rc != 0) {
                return;
            }
            sptm_panic("%s: refcnt_underflow rc %p old...", 0, 0, 0);
        }
        sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
    }
    sptm_panic("%s: Invalid PTE found while atte...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d8a58  sptm_va_to_pa                                            */
/* ------------------------------------------------------------------ */
/* FUN_000d8a58 @ 0x000d8a58   (est. sptm_va_to_pa)
 * Ghidra: long FUN_000d8a58(ulong param_1)
 * Inverse of sptm_pa_to_va: translates a PAPT VA back to the physical
 * address. In the identity window returns (va - g_papt_va_base) +
 * g_mem_phys_base. Otherwise scans the committed-range table for a
 * covering range (returning range-relative paddr) or, if none, walks the
 * root to a level-3 leaf PTE and recombines the leaf paddr with the VA
 * low bits. Panics on a zero argument, a missing leaf table, or an
 * unmapped/unmanaged VA.
 * Confidence: high */
uintptr_t sptm_va_to_pa(uintptr_t va)
{
    if (va == 0) {
        sptm_panic("%s: papt_to_phys 0 encountered...", 0, 0, 0);
    }
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        return (va - g_papt_va_base) + g_mem_phys_base;
    }
    uintptr_t *r = g_committed_range_base;
    if (g_committed_range_count != 0) {
        for (uint64_t i = 0; i < g_committed_range_count; i++) {
            if (r[1] <= va && va < r[1] + (uint64_t)r[2] * 0x4000) {
                return (va - r[1]) + r[0];
            }
            r += 3;
        }
    }
    uint16_t *root_guard;
    if (g_papt_root_pa < g_mem_phys_base || g_mem_phys_end <= g_papt_root_pa) {
        root_guard = (uint16_t *)sptm_frame_va(g_papt_root_pa).lo;
    } else {
        root_guard = (uint16_t *)(0x95460 + ((g_papt_root_pa - g_mem_phys_base) >> 10) * 8);
    }
    uint64_t *pte = sptm_papt_walk((uintptr_t)root_guard, va, 3, NULL, NULL);
    if (pte == NULL) {
        sptm_panic("%s: %s No leaf table present fo...", 0, 0, 0);
    }
    if ((~(uint32_t)*pte & 3) != 0 && (va < 0x95140 || 0x95148 <= va)) {
        sptm_panic("%s: No valid PAPT mapping found w...", 0, 0, 0);
    }
    return (*pte & 0xfffffffff000) + (va & 0x3fff);
}

/* ------------------------------------------------------------------ */
/* 000d8bf8  sptm_retype_frames                                        */
/* ------------------------------------------------------------------ */
/* FUN_000d8bf8 @ 0x000d8bf8   (est. sptm_retype_frames)
 * Ghidra: void FUN_000d8bf8(ulong param_1,undefined8 param_2,uint param_3,
 *                           uint param_4)
 * Retypes a contiguous run of `param_2` frames starting at paddr
 * param_1 from type filter param_3 to type param_4. Requires post-PAPT
 * build; num_frames must be non-zero. Every frame in [param_1, +n*0x4000)
 * that is in the managed window and currently has FTE type param_3 (or
 * matches the wildcard 0x44) has its FTE type rewritten to param_4 and
 * its root PTE re-stamped. Finally, if the root is an 0x08 table, the
 * DSB/TLB/ISB maintenance is issued over the run. A frame outside the
 * managed window panics "Attempted to retype a non-ma...".
 * Confidence: high */
void sptm_retype_frames(uintptr_t base_pa, uint64_t num_frames, uint32_t old_type,
    uint32_t new_type)
{
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        sptm_panic("%s: Expected bootstrap stages no...", 0, 0, 0);
    }
    if ((int32_t)num_frames == 0) {
        sptm_panic("%s: Called with num_frames of ze...", 0, 0, 0);
    }
    uint64_t rel = base_pa - g_mem_phys_base;
    if (!(g_mem_phys_base <= base_pa && base_pa < g_mem_phys_end)) {
        sptm_panic("%s: Attempted to retype a non-ma...", 0, 0, 0);
    }
    uint64_t last_pa = base_pa + (uint64_t)((int32_t)num_frames - 1) * 0x4000;
    if ((g_mem_phys_base <= last_pa && last_pa < g_mem_phys_end) &&
        (uint64_t)base_pa + (uint64_t)(num_frames - 1) * 0x4000 >= base_pa) {
        uint32_t idx = (uint32_t)(rel >> 0xe);
        uint32_t end = (uint32_t)num_frames + idx;
        for (; idx < end; idx++) {
            uintptr_t fte = 0x95460 + (uint64_t)idx * 0x10;
            if (old_type == 0x44 || *(uint8_t *)(fte + 2) == (uint8_t)old_type) {
                *(uint8_t *)(fte + 2) = (uint8_t)new_type;
                uintptr_t pa = g_mem_phys_base + (uint64_t)idx * 0x4000;
                if (g_type_state[(uint64_t)new_type * 0x90] == -1) {
                    sptm_papt_unmap_leaf(sptm_pa_to_va(pa));
                } else {
                    sptm_papt_update_root_pte(sptm_pa_to_va(pa), g_type_state[(uint64_t)new_type * 0x90]);
                }
            }
        }
        uintptr_t va = sptm_pa_to_va(base_pa & 0x3fffffffc000);
        uint16_t *root_guard;
        if (g_papt_root_pa < g_mem_phys_base || g_mem_phys_end <= g_papt_root_pa) {
            root_guard = (uint16_t *)sptm_frame_va(g_papt_root_pa).lo;
        } else {
            root_guard = (uint16_t *)(0x95460 + ((g_papt_root_pa - g_mem_phys_base) >> 10) * 8);
        }
        if (*(uint8_t *)(root_guard + 1) == 0x08) {
            sptm_dsb(2, 2, 0);
            sptm_slice_tlbi_single(va, num_frames);
            sptm_dsb(1, 3, 1);
            sptm_isb();
        }
        return;
    }
    sptm_panic("%s: Attempted to retype a non-ma...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d8f94  sptm_papt_walk_alloc                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d8f94 @ 0x000d8f94   (est. sptm_papt_walk_alloc)
 * Ghidra: void FUN_000d8f94(ulong param_1,int param_2,int param_3,
 *                           int param_4,ulong param_5,int param_6)
 * Walks the PAPT for virtual address param_1 allocating the missing page
 * tables as it descends (up to param_5 levels). param_2 is the starting
 * level config (0 = SPTM table), param_4 the leaf frame type (9 or
 * 0x14), param_3 the intermediate table type and param_6 selects the
 * table-descriptor present bits (0 = 3, else 0x800000000000003). Each
 * missing interior entry is filled with a freshly allocated (via
 * sptm_alloc_frames) class-2 table whose descriptor, level set and FTE
 * refcounts are installed; the leaf-level frames get their FTE type set
 * via sptm_retype_frames. The root table must be class 1.
 * Confidence: low
 * Notes: per-level shift/mask from the 0x13158/0x13160 level tables. */
void sptm_papt_walk_alloc(uintptr_t va, int start_type, int table_type,
    int leaf_type, uint64_t levels, int present)
{
    if (start_type == 0 && leaf_type != 9) {
        sptm_panic("%s: wrong frame type for SPTM CT...", 0, 0, 0);
    }
    if (leaf_type != 9 && leaf_type != 0x14) {
        sptm_panic("%s: wrong frame type for page ta...", 0, 0, 0);
    }
    uintptr_t table_va = sptm_pa_to_va(g_papt_root_pa);
    uint64_t desc = (present == 0) ? 3 : 0x800000000000003;
    for (uint64_t level = 1; level < levels; level++) {
        uint64_t *pte = (uint64_t *)(table_va +
            ((va & 0x7fffffffffff & *(uint64_t *)(level * 0x38 + 0x13160)) >>
             (*(uint64_t *)(level * 0x38 + 0x13158) & 0x3f) & 0xffffffff) * 8);
        table_va = *pte;
        if ((~(uint32_t)table_va & 3) != 0) {
            if (((g_bootstrap_stages >> 0xb) & 1) != 0) {
                sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
            }
            int itype = (level != 1) ? 0 : table_type;
            int ltype = (level != 2) ? itype : table_type;
            uintptr_t new_pa = sptm_alloc_frames(9, 1, ltype);
            uintptr_t fte = 0x95460 + ((new_pa - g_mem_phys_base) >> 0xe & 0xffffffff) * 0x10;
            if (g_fte_class[(uint64_t)*(uint8_t *)(fte + 2) * 0x90] != 0x02) {
                sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
            }
            uint64_t idx = (new_pa - g_mem_phys_base) >> 0xe & 0xffffffff;
            *(uint8_t *)(fte + 4) = (uint8_t)level + 1;
            uint64_t val = desc | (idx * 0x4000) + g_mem_phys_base;
            *pte = val;
            uintptr_t fte2 = 0x95460 + idx * 0x10;
            if (g_fte_class[(uint64_t)*(uint8_t *)(fte2 + 2) * 0x90] != 0x02) {
                sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
            }
            uint16_t rc = *(uint16_t *)(fte2 + 6);
            *(uint16_t *)(fte2 + 6) = rc + 1;
            if (rc > 0xfff4) {
                sptm_panic("%s: refcnt_overflow rc %p old v...", 0, 0, 0);
            }
            uint64_t parent_pa = sptm_va_to_pa((uintptr_t)pte);
            uint16_t *pguard;
            if (parent_pa < g_mem_phys_base || g_mem_phys_end <= parent_pa) {
                pguard = (uint16_t *)sptm_frame_va(parent_pa).lo;
            } else {
                pguard = (uint16_t *)(0x95460 + ((parent_pa - g_mem_phys_base) >> 10) * 8);
            }
            if (g_fte_class[(uint64_t)pguard[1] * 0x90] == 0x01) {
                uint16_t rc2 = pguard[3];
                pguard[3] = rc2 + 1;
                if (rc2 > 0x812) {
                    sptm_panic("%s: refcnt_overflow rc %p old v...", 0, 0, 0);
                }
            } else if (g_fte_class[(uint64_t)pguard[1] * 0x90] == 0x02) {
                uint16_t rc2 = pguard[4];
                pguard[4] = rc2 + 1;
                if (rc2 > 0x808) {
                    sptm_panic("%s: refcnt_overflow rc %p old v...", 0, 0, 0);
                }
            } else {
                sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
            }
            if (((g_bootstrap_stages >> 8) & 1) != 0) {
                int ftype = (level != 2) ? leaf_type : 9;
                sptm_retype_frames(g_mem_phys_base + idx * 0x4000, 1, 0x44, ftype);
            }
        }
        table_va = table_va & 0xfffffffff000;
        table_va = sptm_pa_to_va(table_va);
    }
}

/* ------------------------------------------------------------------ */
/* 000d941c  sptm_papt_install_leaf                                   */
/* ------------------------------------------------------------------ */
/* FUN_000d941c @ 0x000d941c   (est. sptm_papt_install_leaf)
 * Ghidra: void FUN_000d941c(long param_1,ulong param_2,uint param_3,
 *                           uint param_4,uint param_5,uint param_6)
 * Installs leaf PTEs for `param_3` consecutive 16K pages: VA param_1,
 * paddr param_2, type param_4 (or the frame-type table-derived type when
 * param_4 == 0xfe), with prot bits param_5 and flags param_6. For each
 * page the leaf PTE (via sptm_papt_leaf_pte) must be absent ("Valid PTE
 * found while attemp..."); it is filled with the paddr, AP bits from the
 * type, present 0x603, and the prot/flags. The frame-table refcount
 * (+8, class 2) is incremented. Ends with DMB + ISB.
 * Confidence: high */
void sptm_papt_install_leaf(uintptr_t va, uintptr_t paddr, uint32_t count,
    uint32_t type, uint32_t prot, uint32_t flags)
{
    if (((g_bootstrap_stages >> 0x11) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    for (uint32_t i = 0; i < count; i++) {
        uint32_t eff_type = type;
        if (type != 0xfe) goto do_install;
        {
            uintptr_t fte = 0x95460 + ((paddr - g_mem_phys_base) >> 10) * 8;
            if (g_type_state[(uint64_t)*(uint8_t *)(fte + 2) * 0x90] == -1) continue;
        }
do_install:
        uint64_t *pte = (uint64_t *)sptm_papt_leaf_pte(va);
        if (pte == NULL) {
            sptm_panic("%s: PAPT PTE could not be reache...", 0, 0, 0);
        }
        if ((~(uint32_t)*pte & 3) == 0) {
            sptm_panic("%s: Valid PTE found while attemp...", 0, 0, 0);
        }
        if (eff_type == 0xfe) {
            uintptr_t fte = 0x95460 + ((paddr - g_mem_phys_base) >> 10) * 8;
            eff_type = (uint32_t)g_type_state[(uint64_t)*(uint8_t *)(fte + 2) * 0x90];
        }
        uint16_t *guard;
        if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
            guard = (uint16_t *)sptm_frame_va(paddr).lo;
        } else {
            guard = (uint16_t *)(0x95460 + ((paddr - g_mem_phys_base) >> 10) * 8);
        }
        uint64_t val = paddr & 0xfffffffff000 | (uint64_t)(eff_type & 3) << 0x35 |
                       (uint64_t)((eff_type & 0xc) << 4) | 0x603;
        if ((eff_type & 0xf) == 10 || (eff_type & 0xf) == 3) {
            uint8_t ap = g_fte_class4[(uint64_t)guard[1] * 0x90];
            val = ((uint64_t)(ap & 0xc) << 4) | ((uint64_t)(ap & 3) << 0x35) | (val & 0xfffffffff603);
        }
        *pte = (uint64_t)((prot & 7) << 2) | (uint64_t)((flags & 0x100) >> 8) << 0x32 | val;
        uint64_t pa2 = sptm_va_to_pa(va);
        uint16_t *g2;
        if (pa2 < g_mem_phys_base || g_mem_phys_end <= pa2) {
            g2 = (uint16_t *)sptm_frame_va(pa2).lo;
        } else {
            g2 = (uint16_t *)(0x95460 + ((pa2 - g_mem_phys_base) >> 10) * 8);
        }
        if (g_fte_class[(uint64_t)g2[1] * 0x90] != 0x02) {
            sptm_panic("%s: Type %d class of FTE %p %d...", 0, 0, 0, 0);
        }
        uint16_t rc = g2[4];
        g2[4] = rc + 1;
        if (rc > 0x808) {
            sptm_panic("%s: refcnt_overflow rc %p old v...", 0, 0, 0);
        }
        paddr += 0x4000;
        va += 0x4000;
    }
    sptm_dmb(2, 3);
    sptm_isb();
}

/* ------------------------------------------------------------------ */
/* 000d977c  sptm_papt_unmap_range                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d977c @ 0x000d977c   (est. sptm_papt_unmap_range)
 * Ghidra: void FUN_000d977c(long param_1,ulong param_2)
 * Unmaps `param_2` pages starting at VA param_1, releasing each leaf PTE
 * (only for frames whose type maps to a real type, else skipped), then
 * issues the DSB/TLB/ISB maintenance when the root is an 0x08 table.
 * Requires post-PAPT build and pre-final stage.
 * Confidence: high */
void sptm_papt_unmap_range(uintptr_t va, uint64_t num_pages)
{
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        sptm_panic("%s: Expected bootstrap stages no...", 0, 0, 0);
    }
    if (((g_bootstrap_stages >> 0x11) & 1) == 0) {
        if ((int32_t)num_pages != 0) {
            uintptr_t v = va;
            for (uint64_t i = 0; i < (num_pages & 0xffffffff); i++) {
                uintptr_t pa = sptm_va_to_pa(v);
                uint16_t *guard;
                if (pa < g_mem_phys_base || g_mem_phys_end <= pa) {
                    guard = (uint16_t *)sptm_frame_va(pa).lo;
                } else {
                    guard = (uint16_t *)(0x95460 + ((pa - g_mem_phys_base) >> 10) * 8);
                }
                if (g_type_state[(uint64_t)guard[1] * 0x90] != -1) {
                    sptm_papt_unmap_leaf(v);
                }
                v += 0x4000;
            }
        }
        uint16_t *root_guard;
        if (g_papt_root_pa < g_mem_phys_base || g_mem_phys_end <= g_papt_root_pa) {
            root_guard = (uint16_t *)sptm_frame_va(g_papt_root_pa).lo;
        } else {
            root_guard = (uint16_t *)(0x95460 + ((g_papt_root_pa - g_mem_phys_base) >> 10) * 8);
        }
        if (*(uint8_t *)(root_guard + 1) == 0x08) {
            sptm_dsb(2, 2, 0);
            sptm_slice_tlbi_single(va, num_pages);
            sptm_dsb(1, 3, 1);
            sptm_isb();
        }
        return;
    }
    sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d9940  sptm_phystokv                                            */
/* ------------------------------------------------------------------ */
/* FUN_000d9940 @ 0x000d9940   (est. sptm_phystokv; called sptm_phystokv
 *                              in sptm_register_cpu)
 * Ghidra: ulong FUN_000d9940(undefined8 param_1,ulong param_2,uint param_3)
 * Maps a physical region (param_1) of param_2 16K pages into the PAPT VA
 * space and returns the VA base. The mapping count (g_mapping_count) is
 * validated against g_max_mappings ("request for %u mappings exce...")
 * and incremented; the region is carved from the g_mapping_va_cursor.
 * Each page is given the page-table structure via sptm_papt_walk_alloc
 * (level 3, leaf type 9) and the leaf PTEs installed via
 * sptm_papt_install_leaf with the AP/type derived from param_3. Returns
 * the base VA of the mapping.
 * NOTE: named sptm_phystokv per the register-cpu call site (the task
 * note); this is a map+return-VA helper, not a pure translation.
 * Confidence: high */
uintptr_t sptm_phystokv(uintptr_t pa, uint64_t num_pages, uint32_t flags)
{
    if (((g_bootstrap_stages >> 0x11) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    uint64_t count = g_mapping_count;
    if ((((g_bootstrap_stages >> 10) & 1) != 0) &&
        (count = g_mapping_count + (int32_t)num_pages, g_max_mappings < count)) {
        sptm_panic("%s: request for %u mappings exce...", 0, 0, 0);
    }
    g_mapping_count = count;
    uint64_t len = (num_pages & 0xffffffff) * 0x4000;
    uintptr_t base_va = g_mapping_va_cursor;
    uint64_t cur = g_mapping_va_cursor;
    for (uintptr_t v = g_mapping_va_cursor; cur = g_mapping_va_cursor, v < g_mapping_va_cursor + len; v += 0x4000) {
        sptm_papt_walk_alloc(v, 2, 0, 9, 3, 1);
    }
    sptm_papt_install_leaf(base_va, pa, num_pages, 3, 0x10003 >> ((flags & 3) << 3) & 3, 0);
    g_mapping_va_cursor += len;
    g_mapping_region_count += (int32_t)num_pages;
    return base_va;
}

/* ------------------------------------------------------------------ */
/* 000d9aa8  sptm_map_boot_region                                     */
/* ------------------------------------------------------------------ */
/* FUN_000d9aa8 @ 0x000d9aa8   (est. sptm_map_boot_region; declared in
 *                              sptm_internal.h)
 * Ghidra: void FUN_000d9aa8(long param_1,uint param_2,undefined8 param_3,
 *                           int param_4,uint param_5)
 * Registers a named boot PAPT range (name param_1, type param_2, VA base
 * param_3, page count param_4, flags param_5) into the boot-range table
 * g_papt_range_name/type/va/pages/flags. Requires pre-boot-regions
 * (bit 7 clear). For a required range (param_4 != 0): type must be
 * <= 0x41, the table capacity (0x32) must not be exceeded, and the
 * PAPT_RANGE_ALLOC flag must not be combined with any other bits (panic
 * on violation). A non-required range (param_4 == 0) only requires the
 * optional bit in param_5.
 * Confidence: high */
void sptm_map_boot_region(const char *name, uint32_t type, uintptr_t va_base,
    int num_pages, uint32_t flags)
{
    if (((g_bootstrap_stages >> 7) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    if (name == NULL) {
        sptm_panic("%s: Name is NULL...", 0, 0, 0);
    }
    if (num_pages == 0) {
        if ((flags >> 1) & 1) {
            return;
        }
        sptm_panic("%s: %s range %s Required PAPT ra...", 0, 0, 0, 0);
    }
    if (type > 0x41) {
        sptm_panic("%s: %s range %s Invalid bootstra...", 0, 0, 0, 0);
    }
    uint64_t idx = g_papt_range_count;
    if (g_papt_range_count > 0x31) {
        sptm_panic("%s: %s range %s Attempted to go o...", 0, 0, 0, 0);
    }
    if (((flags >> 7) & 1) && (flags & 0x17f) != 0) {
        sptm_panic("%s: %s range %s PAPT_RANGE_ALLOC...", 0, 0, 0, 0);
    }
    g_papt_range_count += 1;
    g_papt_range_name[idx] = (uintptr_t)name;
    g_papt_range_type[idx] = (uint8_t)type;
    g_papt_range_va[idx] = va_base;
    g_papt_range_pages[idx] = (uint32_t)num_pages;
    g_papt_range_flags[idx] = flags;
}

/* ------------------------------------------------------------------ */
/* 000d9be8  sptm_retype_boot_range                                   */
/* ------------------------------------------------------------------ */
/* FUN_000d9be8 @ 0x000d9be8   (est. sptm_retype_boot_range)
 * Ghidra: void FUN_000d9be8(long param_1,undefined8 param_2,undefined8 param_3)
 * Finds a registered boot PAPT range by name (param_1) and retypes all
 * of its pages from type param_2 to type param_3 via
 * sptm_retype_frames. Requires post-PAPT build, pre-final stage, a
 * non-NULL name, and param_3 < 0x42. Panics "Unable to find requested
 * ran..." if the name is not in the table, and "Invalid new type %u..."
 * if param_3 >= 0x42.
 * Confidence: high */
void sptm_retype_boot_range(const char *name, uint32_t old_type, uint32_t new_type)
{
    if (((g_bootstrap_stages >> 8) & 1) == 0) {
        sptm_panic("%s: Expected bootstrap stages no...", 0, 0, 0);
    }
    if (((g_bootstrap_stages >> 0x11) & 1) != 0) {
        sptm_panic("%s: Unexpected bootstrap stages r...", 0, 0, 0);
    }
    if (name == NULL) {
        sptm_panic("%s: Name is NULL...", 0, 0, 0);
    }
    if ((uint32_t)new_type < 0x42) {
        uintptr_t match = 0;
        for (uint64_t i = 0; i < g_papt_range_count; i++) {
            uintptr_t cand = (sptm_dt_cmp_prop((uintptr_t)name, (const char *)g_papt_range_name[i]) == 0) ? (uintptr_t)&g_papt_range_name[i] : 0;
            if (cand != 0) match = cand;
        }
        if (match != 0) {
            uint64_t *ent = (uint64_t *)match;
            sptm_retype_frames(ent[2], *(uint32_t *)(ent + 4), old_type, new_type);
            return;
        }
        sptm_panic("%s: Unable to find requested ran...", 0, 0, 0);
    }
    sptm_panic("%s: Invalid new type %u...", 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* 000d9d44  sptm_papt_commit                                         */
/* ------------------------------------------------------------------ */
/* FUN_000d9d44 @ 0x000d9d44   (est. sptm_papt_commit; declared in
 *                              sptm_internal.h)
 * Ghidra: void FUN_000d9d44(void)
 * Commits the boot PAPT ranges: coalesces adjacent/contiguous ranges
 * into the committed table (g_committed_range_base/va/pages) and sorts
 * it. Panics "No PAPT ranges have been r..." if none were registered.
 * The committed table is the runtime PA<->VA translation source used by
 * sptm_pa_to_va / sptm_va_to_pa.
 * Confidence: high */
void sptm_papt_commit(void)
{
    if (g_papt_range_count == 0) {
        sptm_panic("%s: ... No PAPT ranges have been r...", 0, 0, 0);
    }
    /* Boot ranges are identity-mapped, so each range's stored "va" is also
     * its physical base. Coalesce contiguous ranges into the committed
     * {base, va, pages} translation table used by sptm_pa_to_va /
     * sptm_va_to_pa. */
    uint64_t n = 0;
    for (uint64_t i = 0; i < g_papt_range_count; i++) {
        uint32_t pages = g_papt_range_pages[i];
        if (pages == 0 || ((g_papt_range_flags[i] >> 2) & 1) != 0) {
            continue;   /* absent or non-contiguous flag */
        }
        uintptr_t base = g_papt_range_va[i];
        uintptr_t va = g_papt_range_va[i];
        if (n > 0 &&
            base == g_committed_range_base[n - 1] + (uint64_t)g_committed_range_pages[n - 1] * 0x4000 &&
            va == g_committed_range_va[n - 1] + (uint64_t)g_committed_range_pages[n - 1] * 0x4000) {
            g_committed_range_pages[n - 1] += pages;
            continue;
        }
        g_committed_range_base[n] = base;
        g_committed_range_va[n] = va;
        g_committed_range_pages[n] = pages;
        n++;
    }
    g_committed_range_count = (uint32_t)n;
    sptm_qsort(g_committed_range_base, g_committed_range_count, 0x18, (void *)sptm_io_range_cmp);
}
