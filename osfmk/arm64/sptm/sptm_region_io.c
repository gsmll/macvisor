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
extern void sptm_dart_state(void);                                            /* FUN_000e4424 */
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
extern uint32_t  g_boot_alloc_off;              /* DAT_001012a8 */

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
        uintptr_t state = sptm_percpu_dart_state(g_dart_id_table[dart_id]);
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
        uintptr_t state = sptm_percpu_dart_state(g_dart_id_table[dart_id]);
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

    for (size_t i = 0; i < sizeof(g_dart_id_table) / sizeof(g_dart_id_table[0]); i++) {
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
            if (*(uintptr_t *)(dart + 0xb28) != 0 && va != *(uintptr_t *)(dart + 0xb28)) {
                /* Not the live SID; validate TZ-D windows before freeing. */
                uint64_t paddr = (pte & 0x3ffffffc00) << 4;
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

