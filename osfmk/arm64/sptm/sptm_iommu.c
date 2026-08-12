/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * sptm_iommu.c — the SPTM IOMMU layer: the UAT (Unified Address Translator)
 * DMA window management, the NVMe BAR configuration, and the T8110 DART
 * (device address resolution table) programming. These functions gate DMA:
 * they translate guest physical addresses, enable/disable IOMMU translation,
 * and manage clock-protection register writes. */
#include <stdint.h>
#include <stddef.h>
#include "sptm_internal.h"

/* =====================================================================
 * Shared SPTM helpers (owned by other workers; declared extern here).
 * Ghidra FUN_ address kept in each comment.
 * ===================================================================== */

/* FUN_000f8844 — noreturn formatted panic (code, arg, format-string). */
extern __attribute__((noreturn)) void sptm_panic(uint32_t code, uint64_t arg, const char *fmt);
/* FUN_000f8804 — noreturn assert failure (message string). */
extern __attribute__((noreturn)) void sptm_assert_fail(const char *msg);

/* FUN_000c5248 — begin a UAT object transaction. Returns the UAT object (x0)
 * and, via *dbg_out, the debug tag (x1). */
extern void *sptm_uat_begin(uint64_t ctx, uint32_t expected_state, uint8_t mask,
                            uint64_t *dbg_out);
/* FUN_000b32d0 — finalize a UAT operation (TLB flush + state transition). */
extern uint64_t sptm_uat_end(uint64_t ctx);

/* Kernel/phys page refcount + translation helpers. */
extern void sptm_kernel_ref(uint64_t addr, uint32_t type);        /* FUN_000e4e74 */
extern void sptm_kernel_unref(uint64_t addr);                     /* FUN_000e5090 */
extern void sptm_kernel_ref_add(uint64_t addr, int64_t count);    /* FUN_000e53d8 */
extern void sptm_phys_lock(uint64_t paddr, uint32_t type);        /* FUN_000e56ac */
extern void sptm_phys_unlock(uint64_t paddr, uint32_t type);      /* FUN_000e5c80 */
extern uint64_t sptm_guest_to_phys(uint64_t paddr);               /* FUN_000e40ec */
extern void *sptm_phys_lookup(uint64_t paddr, uint64_t *dbg_out); /* FUN_000e3d7c */
extern uint16_t *sptm_fte_ptr(uint64_t paddr);                    /* FUN_000e2480 */
extern uint64_t sptm_guest_range_validate(uint64_t vaddr, uint64_t size, void *obj,
                                          uint64_t *out);         /* FUN_000c5784 */
extern void sptm_guest_page_release(uint64_t addr);               /* FUN_000c5550 */
extern uint64_t sptm_callback(uint64_t arg);                      /* FUN_000d8a58 */

/* DART programming helpers. */
extern uint32_t *sptm_dart_pte_lookup(uint64_t paddr, uint32_t type, int a, int b); /* FUN_000d617c */
extern void *sptm_percpu_base(uint64_t hint, uint64_t *dbg_out);  /* FUN_000e4d78 */
extern void sptm_dart_clear_error(void *ctrl);                    /* FUN_000c76ac */
extern void sptm_dart_flush(void *ctrl, uint32_t idx, int a, int b); /* FUN_000c7bac */
extern int sptm_dart_poll(void *ctrl, int a);                     /* FUN_000c786c */
extern uint64_t sptm_dart_lock(void *ctrl, uint32_t idx);         /* FUN_000caa9c */
extern void sptm_dart_lock_set(void *ctrl, uint32_t dart, uint64_t idx); /* FUN_000cabb4 */
extern void sptm_dart_save(void *ctrl, uint32_t idx);             /* FUN_000c8a14 */
extern void sptm_dart_ps_refcount(void *ctrl, uint8_t ps, int inc); /* FUN_000cc2bc */
extern void *sptm_dart_tt_lookup(void *ctrl, uint32_t idx, uint64_t vaddr,
                                 uint64_t *out);                  /* FUN_000cd970 */
extern void sptm_dart_tlb_flush(void *ctrl, uint32_t idx, uint64_t start, uint64_t end,
                                int a);                           /* FUN_000cdd0c */
/* DART lock-acquire variants (return status in x0, debug tag via out). */
extern uint64_t sptm_dart_acquire_v2(void *ctrl, uint32_t idx, uint64_t *dbg_out); /* FUN_000c9364 */
extern uint64_t sptm_dart_acquire_v1(void *ctrl, uint32_t idx, uint64_t *dbg_out); /* FUN_000c92e8 */
/* DART register write helpers. */
extern void sptm_dart_write_reg_v2(void *ctrl, uint32_t idx, uint64_t reg, uint64_t val); /* FUN_000cc540 */
extern void sptm_dart_write_reg_v1(void *ctrl, uint32_t idx, uint64_t reg, uint64_t val); /* FUN_000c7e5c */
extern void sptm_dart_write_field_v2(void *ctrl, uint32_t idx, uint64_t reg, uint64_t val,
                                     uint64_t mask);             /* FUN_000cc490 */
extern void sptm_dart_write_field_v1(void *ctrl, uint32_t idx, uint64_t reg, uint64_t val,
                                     uint64_t mask);             /* FUN_000cc3f8 */

/* Copy/memset + lock primitives. */
extern void *sptm_memcpy(void *dst, const void *src, size_t n);  /* thunk_FUN_000abeb0 */
extern void sptm_memset(void *dst, int c, size_t n);             /* thunk_FUN_000abb60 */
extern void sptm_lock_acquire(void);   /* LOAcquire() */
extern void sptm_lock_release(void);   /* LORelease() */

/* =====================================================================
 * Shared SPTM globals (Ghidra DAT_ names in comments).
 * ===================================================================== */
extern const uint64_t sptm_guest_mem_start;   /* DAT_00095d18 */
extern const uint64_t sptm_guest_mem_end;     /* DAT_00095d20 */
extern uint64_t sptm_global_cfg[];            /* DAT_00095d08 (struct base) */
extern uint32_t sptm_debug_flags;             /* DAT_00094319 */
extern uint8_t sptm_sapt_bootstrapped;        /* DAT_000952e8 */
extern uint64_t sptm_feature_flags;           /* DAT_001012d8 */
extern uint64_t sptm_phys_map_base;           /* DAT_00095110 */
extern uint64_t sptm_phys_table_count;        /* DAT_00101ac8 */
extern uint64_t sptm_phys_table[];            /* DAT_00101ad0 (stride 3 u64: start, physbase, pages) */
extern uint8_t *sptm_guest_meta_base;         /* DAT_00095460 */
extern void *sptm_phys_meta_default;          /* DAT_00101f90 */
extern uint8_t sptm_boot_stage;               /* DAT_00095310 */
extern void (*sptm_boot_dispatch[])(uint64_t, uint32_t); /* DAT_00015d80 (stride 0x28) */
extern uint8_t sptm_boot_stage_table[];       /* DAT_00015d90 (stride 0x28) */
extern uint64_t sptm_boot_region_lo;          /* DAT_000952f8 */
extern uint64_t sptm_boot_region_hi;          /* DAT_00095300 */
extern uint8_t sptm_iommu_dart_info[];        /* DAT_00095d84 (stride 0x90) */
extern uint8_t sptm_iommu_dart_type[];        /* DAT_00095d51 (stride 0x90) */
extern uint8_t sptm_iommu_dart_attr[];        /* DAT_00095d83 (stride 0x90) */
extern uint32_t sptm_dispatch_ids[];          /* DAT_00095320 (stride 0x20) */
extern uint8_t sptm_uat_nvme_state[];         /* DAT_00094ab0 (struct base) */
extern int16_t sptm_dart_id_map[];            /* DAT_00094ec0 (indexed by dart id) */
extern uint8_t sptm_apf_enable;               /* DAT_001012b0 (&1) */
extern uint8_t sptm_ps_wr_max;                /* DAT_001012b4 */
extern char *sptm_ps_wr_table;                /* DAT_001012b8 (stride 6) */
extern uint8_t sptm_ps_wr_guard;              /* DAT_001012c0 */
extern uint8_t sptm_ps_wr_mode;               /* DAT_001012c1 (== 1) */
extern uint8_t sptm_alt_dart_mode;            /* DAT_001012c2 (&1) */
extern uint8_t *sptm_dart_slice_table;        /* DAT_001012c8 */
extern uint64_t sptm_apf_mask_hi;             /* DAT_00012f38 */
extern uint64_t sptm_apf_mask_lo[];           /* DAT_00012f00 / DAT_00012ef0 / DAT_00012ef8 */
extern uint8_t sptm_memattr_table[];          /* DAT_00012f20 */

/* =====================================================================
 * Inline helpers.
 * ===================================================================== */

/* Current CPU base register (EL2 thread/percpu pointer). Ghidra reads it via
 * UnkSytemRegRead(3,6,0xf,8,0) with tpidr_el2 fallback, then
 * UnkSytemRegRead(3,6,0xf,0xb,1). */
static inline uint64_t sptm_cpu_base(void) {
    uint64_t v;
    __asm__ volatile("mrs %0, tpidr_el2" : "=r"(v));
    return v;
}

/* Per-CPU "power state" guard value, derived from a byte in the percpu block.
 * Ghidra: s_uat_instance_>handoff_region_>mi_0000142e[cpu_base + 10] << 1 | 1 */
static inline uint8_t sptm_uat_guard(uint64_t cpu_base) {
    return ((uint8_t)((const uint8_t *)cpu_base)[10] << 1) | 1;
}

/* Barriers. Ghidra: DataSynchronizationBarrier(scope,domain,share) /
 * DataMemoryBarrier(scope,domain); rendered as full-system barriers. */
static inline void sptm_dsb(int scope, int domain, int share) { (void)scope; (void)domain; (void)share; __asm__ volatile("dsb sy" ::: "memory"); }
static inline void sptm_dmb(int scope, int domain) { (void)scope; (void)domain; __asm__ volatile("dmb sy" ::: "memory"); }

#define LZCOUNT(x) __builtin_clz((uint32_t)(x))
#define POPCOUNT(x) __builtin_popcount((uint32_t)(x))
static inline void sptm_halt(void) { __asm__ volatile("hlt #0"); }

/* NVMe controller state field accessors (DAT_00094ab0). */
#define NVME_PAGES     (*(uint32_t *)(sptm_uat_nvme_state + 0x10))
#define NVME_REGS      (*(uint64_t *)(sptm_uat_nvme_state + 0x778))
#define NVME_BAR_BASE  (*(uint64_t *)(sptm_uat_nvme_state + 0x760))
#define NVME_BAR_SIZE  (*(uint64_t *)(sptm_uat_nvme_state + 0x768))
#define NVME_FLAGS     (*(uint32_t *)(sptm_uat_nvme_state + 0x14))

/* Per-DART control block accessors. sptm_percpu_base returns {percpu=x0,
 * dbg=x1}; the DART ctrl struct lives at percpu+0x10. */
#define DART_CTRL()  ((uint8_t *)((uint8_t *)sptm_percpu_base(0, NULL) + 0x10))
#define DART_ID_CHECK(id) \
    do { if (sptm_dart_id_map[(id)] == -1) \
             sptm_panic(0x6000006, 0, "__s__s__d_____s___llx__00011410"); } while (0)
#define DART_MAX_IDX(c)  (*(uint32_t *)((c) + 0xba4))
#define DART_VERSION(c)  (*(uint16_t *)((c) + 0xbdc))
#define DART_STATE(c)    (*(uint8_t *)((c) + 0xbe0))
#define DART_GUARD(c)    ((c) + 0xbdf)
#define DART_INST(c, i)  (*(uint8_t **)((c) + 8 + (uint64_t)(i) * 0x78))

/* The stream-allocation bitmap lives at ctrl+0xa38. */
static inline uint64_t *bitmap_ctrl(uint8_t *ctrl);

/* =====================================================================
 * UAT — Unified Address Translator DMA window management
 * ===================================================================== */

/* FUN_000b4068 @ 0x000b4068   (est. sptm_uat_unmap_begin)
 * Ghidra: undefined FUN_000b4068(undefined8 param_1, ulong param_2, ulong param_3)
 * Begins an unmap of a UAT DMA window: validates the guest physical address
 * (16 KiB aligned, within the SPTM guest region), locks the page, snapshots
 * the PTE array into the UAT object, and arms the object for the unmap flow.
 * param_1 = guest context, param_2 = guest physical start, param_3 = segment
 * count.
 * Confidence: high
 * Notes: sptm_uat_begin(2,0xf); copies param_3*16 bytes of PTEs from
 *   sptm_guest_to_phys(param_2) into obj+0x250; guard 1 -> 5. */
void sptm_uat_unmap_begin(uint64_t ctx, uint64_t guest_paddr, uint64_t seg_count)
{
    uint8_t *uat_obj;
    uint64_t dbg;
    uint64_t src_phys;
    uint64_t idx, n;

    uat_obj = (uint8_t *)sptm_uat_begin(ctx, 2, 0xf, &dbg); /* the true debug tag is consumed by sptm_uat_begin */

    if ((sptm_debug_flags & 1) == 0 &&
        (*(uint64_t *)(sptm_global_cfg[0x138 / 8] + 8) != 0x4b1d000000000002)) {
        sptm_panic(0x4000020, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((guest_paddr & 0x3fff) != 0) {
        sptm_panic(0x4000009, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr) {
        sptm_panic(6, dbg, "__s__s__d_____s___llx__00011410");
    }
    sptm_kernel_ref(guest_paddr, 0xb);
    if (seg_count == 0 || sptm_global_cfg[0x1b0 / 8] < seg_count) {
        sptm_panic(0x4000010, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (0x4000 < seg_count * 0x10 + ((uint64_t)(uat_obj + 0x250) & 0x3fff)) {
        sptm_assert_fail("__s__Copying_segments_into__p_wil_00001e4b");
    }

    if (((sptm_feature_flags >> 8) & 1) == 0) {
        src_phys = (guest_paddr - sptm_guest_mem_start) + sptm_phys_map_base;
    } else {
        n = sptm_phys_table_count;
        if (n != 0) {
            uint64_t *t = sptm_phys_table;
            for (idx = 0; idx < n; idx++, t += 3) {
                if (t[0] <= guest_paddr && guest_paddr < t[0] + (uint64_t)(uint32_t)t[2] * 0x4000) {
                    src_phys = (guest_paddr - t[0]) + t[1];
                    goto found;
                }
            }
        }
        src_phys = sptm_guest_to_phys(guest_paddr);
    found: ;
    }

    sptm_memcpy(uat_obj + 0x250, (void *)src_phys, seg_count * 0x10);
    sptm_kernel_unref(guest_paddr);

    uat_obj[0x20] = 1;
    uat_obj[0x30] = 0; uat_obj[0x31] = 0; uat_obj[0x32] = 0; uat_obj[0x33] = 0;
    uat_obj[0x34] = 0; uat_obj[0x35] = 0; uat_obj[0x36] = 0; uat_obj[0x37] = 0;
    uat_obj[0x38] = 0; uat_obj[0x39] = 0; uat_obj[0x3a] = 0; uat_obj[0x3b] = 0;
    uat_obj[0x3c] = 0; uat_obj[0x3d] = 0; uat_obj[0x3e] = 0; uat_obj[0x3f] = 0;
    *(uint64_t *)(uat_obj + 0x28) = seg_count;
    uat_obj[0x40] = 0;
    uat_obj[0x248] = 0; uat_obj[0x249] = 0; uat_obj[0x24a] = 0; uat_obj[0x24b] = 0;
    uat_obj[0x24c] = 0; uat_obj[0x24d] = 0; uat_obj[0x24e] = 0; uat_obj[0x24f] = 0;

    if (uat_obj[0x1a] != 1) {
        sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
    }
    uat_obj[0x1a] = 5;
    if ((uat_obj[0] & 5) != 0) {
        sptm_callback(0);
        sptm_kernel_unref(0);
    }
    sptm_uat_end(ctx);
}

/* FUN_000b4374 @ 0x000b4374   (est. sptm_uat_prepare_fw_unmap_continue)
 * Ghidra: undefined8 FUN_000b4374(undefined8 param_1, undefined8 param_2)
 * Continues a firmware (FW) unmap: walks the remaining 16 KiB pages of the
 * region, clearing the "valid" bit (PTE bit 3) on each entry until the batch
 * limit is reached, then registers the flush window in the per-DART context
 * table. Returns 0/1/2 to indicate progress/state.
 * Confidence: high
 * Notes: PTE lookup via FUN_000b3adc + FUN_000b3b34; DSB(0,2,0)/DSB(0,3,1). */
uint64_t sptm_uat_prepare_fw_unmap_continue(uint64_t ctx, uint64_t param_2)
{
    uint8_t *uat_obj;
    uint64_t total_segs, progress;
    uint64_t pte_addr;
    uint64_t *pte;
    uint32_t w1, w4;
    uint64_t region_start;
    uint64_t result;
    int finish_state;
    uint64_t dbg;

    (void)param_2;
    if ((sptm_debug_flags & 1) != 0) {
        sptm_panic(0x400001c, 0, "__s__s__d_____s___llx__00011410");
    }
    uat_obj = (uint8_t *)sptm_uat_begin(ctx, 4, 0xf, &dbg);

    progress = *(uint64_t *)(uat_obj + 0x28);
    total_segs = *(uint64_t *)(uat_obj + 0x30);
    if (total_segs <= progress) {
        sptm_assert_fail("__s__Corrupted_prepare_fw_unmap_d_000014bb");
    }
    pte = NULL;
    region_start = *(uint64_t *)(uat_obj + 0x20);
    uint64_t cur_seg = progress + 1;
    pte_addr = region_start + progress * 0x4000;
    progress = 1;

    do {
        if (((uint64_t)pte & 0x3fff) == 0) {
            /* FUN_000b3adc(obj, (pte_addr>>shift)&1) + FUN_000b3b34(...) yield
             * the PTE pointer; rendered as a guest-to-phys translation. */
            pte = (uint64_t *)sptm_guest_to_phys(pte_addr);
        }
        uint64_t entry = *pte;
        if ((~(uint32_t)entry & 3) == 0) {
            w1 = (uint32_t)entry >> 4 & 0xc;
            w4 = (uint32_t)(entry >> 0x35);
            if (((entry & 0x1c) == 0) && ((w1 | w4 & 2) == 2 || (w1 | w4 & 3) - 5 < 3)) {
                *pte = entry | 8;      /* clear the present/valid bit (bit 3) */
                uat_obj[0x38] = 1;     /* dirty */
            }
        }
        if ((cur_seg != total_segs) && (sptm_global_cfg[0x1b8 / 8] <= progress)) {
            *(uint64_t *)(uat_obj + 0x28) = cur_seg;
            finish_state = 4;
            goto flush_path;
        }
        pte++;
        cur_seg++;
        pte_addr += 0x4000;
        progress++;
    } while (cur_seg - total_segs != 1);

    if ((uat_obj[0x38] & 1) == 0) {
        result = 0;
        goto out;
    }
    sptm_dsb(0, 2, 0);
    sptm_dart_tlb_flush(uat_obj, 0, region_start, total_segs << 0xe, 1);
    uint16_t ctx_id = *(uint16_t *)(uat_obj + 0x18);
    if ((uint64_t)ctx_id < 0x41) {
        uint64_t ctx_base = sptm_global_cfg[0x138 / 8];
        uint8_t *row = (uint8_t *)ctx_base + (uint64_t)ctx_id * 0x18;
        if (*(int *)(row + 0x20) != 0) {
            sptm_panic(0x4000014, 0, "__s__s__d_____s___llx____s___llx__00011452");
        }
        *(uint64_t *)(row + 0x28) = region_start;
        *(uint64_t *)(row + 0x30) = total_segs << 0xe;
        if ((*(uint8_t *)(ctx_base + 0x638) & 1) == 0) {
            result = 2;
            finish_state = 1;
            if (((uat_obj[0] & 5) != 0) && (*(uint32_t *)(ctx_base + 0x18) != (uint32_t)ctx_id)) {
                goto mark_dead;
            }
        } else {
        mark_dead:
            result = 0;
            *(uint64_t *)(row + 0x28) = (*(uint64_t *)(row + 0x28) & 0xffffffffffff) | 0xdead000000000000;
            finish_state = 2;
        }
        *(int *)(row + 0x20) = finish_state;
    } else {
        result = 0;
    }
    sptm_dsb(0, 3, 1);
out:
    finish_state = 2;
flush_path:
    if (uat_obj[0x1a] != 1) {
        sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
    }
    uat_obj[0x1a] = (uint8_t)finish_state;
    if ((uat_obj[0] & 5) != 0) {
        sptm_callback(0);
        sptm_kernel_unref(0);
    }
    return result;
}

/* FUN_000b46bc @ 0x000b46bc   (est. sptm_uat_prepare_fw_unmap_begin)
 * Ghidra: undefined8 FUN_000b46bc(undefined8 param_1, undefined8 param_2, long param_3)
 * Begins a firmware unmap: resolves the guest physical region into the UAT
 * object, then defers to sptm_uat_prepare_fw_unmap_continue. Returns that
 * function's status.
 * Confidence: high
 * Notes: validates state 0x4b1d000000000002 and param_3 (page count) upper
 *   bound, then sptm_guest_range_validate; guard 1 -> 4. */
uint64_t sptm_uat_prepare_fw_unmap_begin(uint64_t ctx, uint64_t guest_paddr, uint64_t page_count)
{
    uint8_t *uat_obj;
    uint64_t phys, local;
    uint64_t dbg;

    if ((sptm_debug_flags & 1) == 0) {
        uat_obj = (uint8_t *)sptm_uat_begin(ctx, 2, 0xf, &dbg);
        if (*(uint64_t *)(sptm_global_cfg[0x138 / 8] + 8) != 0x4b1d000000000002) {
            sptm_panic(0x4000020, 0, "__s__s__d_____s___llx____s___llx__00011690");
        }
        if (page_count + 0xfffc000000000000U < 0xfffc000000000001) {
            sptm_panic(0x12, 0, "__s__s__d_____s___llx____s___llx__00011690");
        }
        local = 0;
        phys = sptm_guest_range_validate(guest_paddr, page_count << 0xe, uat_obj, &local);
        *(uint64_t *)(uat_obj + 0x20) = local;
        (void)phys;
        uat_obj[0x28] = 0; uat_obj[0x29] = 0; uat_obj[0x2a] = 0; uat_obj[0x2b] = 0;
        uat_obj[0x2c] = 0; uat_obj[0x2d] = 0; uat_obj[0x2e] = 0; uat_obj[0x2f] = 0;
        *(uint64_t *)(uat_obj + 0x30) = page_count;
        uat_obj[0x38] = 0;
        if (uat_obj[0x1a] != 1) {
            sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
        }
        uat_obj[0x1a] = 4;
        if ((uat_obj[0] & 5) != 0) {
            sptm_callback(0);
            sptm_kernel_unref(0);
        }
        return sptm_uat_prepare_fw_unmap_continue(ctx, 0);
    }
    return 0;
}

/* FUN_000b486c @ 0x000b486c   (est. sptm_uat_map_continue)
 * Ghidra: undefined8 FUN_000b486c(undefined8 param_1)
 * Continues a DMA map: programs the guest physical -> device address mappings
 * for each pending segment into the stage-1 page tables, applying the mapping
 * attributes (memattr/type bits), until the batch limit is reached. Writes the
 * resulting PTE values and updates the object progress fields. Returns 1.
 * Confidence: high
 * Notes: segment descriptors at obj+0x48 (stride 0x10); PTE assembly mirrors
 *   sptm_uat_unmap_begin; IOMMU presence checks via sptm_boot_dispatch +
 *   sptm_iommu_dart_info. */
uint64_t sptm_uat_map_continue(uint64_t ctx)
{
    uint8_t *uat_obj;
    uint64_t cur_seg, seg_idx;
    uint64_t cur_off, map_base;
    uint64_t *seg_desc, *pte;
    uint64_t seg_pages, seg_vaddr, size_bytes;
    uint64_t limit, n_map, done;
    uint64_t va, pa, pte_addr;
    uint64_t dbg;
    uint32_t flags, att_val;
    uint8_t obj_state;
    int seg_done, last_seg;

    uat_obj = (uint8_t *)sptm_uat_begin(ctx, 3, 0xf, &dbg);

    cur_seg = *(uint64_t *)(uat_obj + 0x28);
    seg_idx = *(uint64_t *)(uat_obj + 0x30);
    if (cur_seg <= seg_idx) {
        sptm_assert_fail("__s__Corrupted_map_data__current_s_0000136c");
    }
    done = 0;
    cur_off = *(uint64_t *)(uat_obj + 0x38);
    map_base = *(uint64_t *)(uat_obj + 0x20);
    limit = sptm_global_cfg[0x1b8 / 8];

    do {
        if (cur_seg <= seg_idx) {
            if (sptm_sapt_bootstrapped == 0) {
                sptm_assert_fail("__s__SAPT_not_bootstrapped__0000db8a");
            }
            if (uat_obj[0x44] != 0 && (sptm_dsb(0, 3, 1), uat_obj[0x44] != 1)) {
                sptm_halt();
            }
            sptm_dmb(0, 3);
            if (uat_obj[0x1a] != 1) goto bad_guard;
            uat_obj[0x1a] = 2;
            obj_state = 0;
            goto done_cleanup;
        }

        seg_desc = (uint64_t *)(uat_obj + 0x48 + seg_idx * 0x10);
        seg_pages = seg_desc[1];
        if (seg_pages <= cur_off) {
            sptm_assert_fail("__s__Invalid_cur_seg_offset__zu___000013d5");
        }
        if (cur_off == 0) {
            size_bytes = seg_pages * 0x4000;
            if (seg_pages >> 0x32 != 0) {
                sptm_panic(0x4000013, size_bytes, "__s__s__d_____s___llx____s___llx__00011254");
            }
            seg_vaddr = seg_desc[0];
            if (__builtin_add_overflow(seg_vaddr, size_bytes, &seg_vaddr)) {
                sptm_panic(0x4000011, size_bytes, "__s__s__d_____s___llx____s___llx__000111dc");
            }
            if ((seg_vaddr & 0x3fff) != 0) {
                sptm_panic(0x4000009, size_bytes, "__s__s__d_____s___llx__00011410");
            }
            flags = *(uint32_t *)(uat_obj + 0x40) & 0x300;
            if (((seg_vaddr >> 0x28 != 1 && flags != 0) ||
                 ((uint32_t)seg_vaddr >> 0x2a != 0 && (*(uint32_t *)(uat_obj + 0x40) & 3) != 0)) ||
                (((seg_vaddr + size_bytes) >> 0x28 != 1 && flags != 0)) ||
                ((seg_vaddr + size_bytes) >> 0x2a != 0 && (*(uint32_t *)(uat_obj + 0x40) & 3) != 0)) {
                sptm_panic(0x4000009, size_bytes, "__s__s__d_____s___llx____s___llx__000111dc");
            }
            sptm_guest_range_validate(map_base, size_bytes, uat_obj, NULL);
            seg_pages = seg_desc[1];
        }

        uint64_t rem_seg = seg_pages - cur_off;
        n_map = rem_seg <= limit - done ? rem_seg : limit - done;
        uint64_t local = 0;
        if (n_map != 0) {
            pte = NULL;
            va = seg_vaddr + cur_off * 0x4000;
            pa = map_base;
            uint64_t rem = n_map;
            do {
                if (((uint64_t)pte & 0x3fff) == 0) {
                    /* FUN_000b3b34(...) — fetch enclosing table + PTE pointer. */
                    pte = (uint64_t *)sptm_guest_to_phys(pa);
                }
                uint64_t old = *pte;
                if ((~(uint32_t)old & 3) == 0) {
                    sptm_panic(0x400000d, dbg, "__s__s__d_____s___llx____s___llx__000111dc");
                }
                flags = *(uint32_t *)(uat_obj + 0x40);
                uint64_t mt = (uint64_t)((flags >> 8 & 2) | (flags & 3) << 2 | flags >> 8 & 1);
                if ((1ULL << mt & 0x4ac0U) != 0) {
                    sptm_panic(0x400001f, dbg, "__s__s__d_____s___llx____s___llx__00011254");
                }
                uint64_t pa_page = va & 0xfffffffff000;
                uint8_t att = sptm_memattr_table[mt];
                uint64_t ap = 3;
                if ((flags & 8) != 0) ap = 0xb;
                if ((flags & 4) != 0) ap = 7;
                uint64_t sh = 0x800;
                if ((uat_obj[0] & 10) != 0) sh = 0;

                uint32_t a = (uint32_t)att & 0xf;
                int t2 = (a & 0xe) == 2, t3 = a - 5 < 3, t9 = a - 9 < 2;
                uint32_t locktype = 1;
                if (t2 || t3 || t9) locktype = 2;
                uint64_t base = sptm_global_cfg[0x68 / 8];
                if (pa_page == base && (t2 || t3 || t9)) {
                    sptm_panic(0x4000012, dbg, "__s__s__d_____s___llx____s___llx__00011452");
                }
                if (((flags & 0xc) == 0) && ((sptm_debug_flags & (t2 || t3)) != 0)) {
                    uint16_t *fte = sptm_fte_ptr(pa_page);
                    uint64_t cb = sptm_cpu_base();
                    uint64_t d = *(uint64_t *)(cb + 0xa38);
                    if (8 < d - 1U) {
                        sptm_assert_fail("__s__Unexpected_Dispatch_ID__llu_0000e9fb");
                    }
                    if ((sptm_dispatch_ids[(((int)d - 1) & 0xff) * 0x20] & 1) == 0) {
                        sptm_assert_fail("__s__IOMMU_with_id__d_not_support_0000e9a1");
                    }
                    uint64_t io_id = (uint8_t)fte[1];
                    if ((sptm_iommu_dart_info[io_id * 0x90] & 1) == 0) {
                        sptm_assert_fail("__s__IOMMU__s___d___attempted_to_r_0000e618");
                    }
                    if (sptm_iommu_dart_type[io_id * 0x90] != 3) {
                        sptm_assert_fail("__s__Type___d__class_of_FTE___p__d_00012b43");
                    }
                    fte[2] = (uint16_t)(fte[2] | 2);
                    if (sptm_iommu_dart_type[io_id * 0x90] != 6) {
                        if ((sptm_iommu_dart_attr[io_id * 0x90] & 1) == 0) {
                            fte[0] = 0; fte[1] = 0;
                        } else {
                            uint16_t r = *fte;
                            *fte = (uint16_t)(r - 2);
                            sptm_lock_release();
                            if (r == 0 || (r & 1) != 0) {
                                sptm_assert_fail("__s__rw_guard_release_shared___p_000115f3");
                            }
                        }
                    }
                }
                if (pa_page != base) {
                    sptm_phys_lock(pa_page, locktype);
                }
                sptm_kernel_ref(local, 0x18);
                sptm_kernel_ref_add(local, 1);
                sptm_kernel_unref(local);
                if (sptm_sapt_bootstrapped == 0) {
                    sptm_assert_fail("__s__SAPT_not_bootstrapped__0000db8a");
                }
                if (((sptm_feature_flags >> 0xb) & 1) == 0) {
                    sptm_assert_fail("__s__Expected_bootstrap_stages_no_0000c42c");
                }
                uint32_t apf = 0;
                if (sptm_boot_region_lo <= pa_page && pa_page <= sptm_boot_region_hi &&
                    sptm_boot_dispatch[(uint64_t)sptm_boot_stage * 0x28] != NULL) {
                    apf = ((uint32_t (*)(uint64_t, uint32_t))
                           sptm_boot_dispatch[(uint64_t)sptm_boot_stage * 0x28])(pa_page, flags);
                    if (uat_obj[0x44] < (uint8_t)apf) uat_obj[0x44] = (uint8_t)apf;
                }
                *pte = sh | ((uint64_t)att & 3) << 0x35 | pa_page |
                       ap | ((uint64_t)(att >> 2) & 3) << 6 | 0x80000000000400;
                pte++;
                va += 0x4000;
                pa += 0x4000;
                rem--;
            } while (rem != 0);
        }
        map_base += n_map * 0x4000;
        last_seg = (seg_idx == cur_seg - 1);
        cur_off += n_map;
        seg_done = (cur_off == seg_pages);
        if (seg_done) { seg_idx++; cur_off = 0; }
        done += n_map;
    } while ((done < limit) || (seg_done && last_seg));

    *(uint64_t *)(uat_obj + 0x20) = map_base;
    *(uint64_t *)(uat_obj + 0x30) = seg_idx;
    *(uint64_t *)(uat_obj + 0x38) = cur_off;
bad_guard:
    if (uat_obj[0x1a] != 1) {
        sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
    }
    uat_obj[0x1a] = 3;
    obj_state = 1;
done_cleanup:
    if ((obj_state & 5) != 0) {
        sptm_callback(0);
        sptm_kernel_unref(0);
    }
    return 1;
}

/* =====================================================================
 * NVMe — controller BAR / queue register programming
 * ===================================================================== */

/* FUN_000c1e94 @ 0x000c1e94   (est. sptm_nvme_ans_sha_reg)
 * Ghidra: void FUN_000c1e94(ulong param_1, ulong param_2, uint param_3)
 * Programs the ANS (address/attribute) SHA register: validates the region is
 * within the NVMe BAR, records the guest physical base + attribute in the
 * NVMe register block, and locks the pages. param_1 = base, param_3 = attr.
 * Confidence: high
 * Notes: guard byte at +0x7b8; base stored at +0x9f0 as {base>>14, attr}. */
void sptm_nvme_ans_sha_reg(uint64_t guest_paddr, uint64_t dbg, uint32_t attr)
{
    if (((NVME_FLAGS >> 8) & 1) == 0) {
        sptm_panic(0x3000005, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((sptm_uat_nvme_state[0x9ea] & 1) == 0) {
        sptm_assert_fail("__s__ANS_SHA_flag_was_not_set_00004666");
    }
    if (sptm_uat_nvme_state[0x7b8] != 0) {
        sptm_panic(0x3000007, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    sptm_uat_nvme_state[0x7b8] = 1;

    uint32_t size = NVME_PAGES << 0xe;
    if (guest_paddr != size) {
        sptm_panic(0x300000e, dbg, "__s__s__d_____s___llx__00011410");
    }
    uint64_t prev = *(uint64_t *)(sptm_uat_nvme_state + 0x9f8);
    if (prev != 0xffffffffffffffffULL && guest_paddr != prev) {
        goto mismatch;
    }

    if (size == 0) {
        if (prev != 0xffffffffffffffffULL) goto skip_lock;
    } else {
        uint64_t n = (uint32_t)NVME_PAGES & 0x3ffff;
        uint64_t a = guest_paddr;
        uint64_t i = n;
        do {
            if (((a < NVME_BAR_BASE) || NVME_BAR_BASE + NVME_BAR_SIZE <= a) &&
                (a < sptm_guest_mem_start || sptm_guest_mem_end <= a)) {
                sptm_panic(6, dbg, "__s__s__d_____s___llx__00011410");
            }
            if ((guest_paddr & 0xfff) != 0) {
                sptm_panic(0x3000003, dbg, "__s__s__d_____s___llx__00011410");
            }
            if ((guest_paddr & 0x3000) != 0) goto mismatch;
            a += 0x4000;
            i--;
        } while (i != 0);
        a = guest_paddr;
        if (prev != 0xffffffffffffffffULL) goto skip_lock;
        do {
            sptm_phys_lock(a, 2);
            n--;
            a += 0x4000;
        } while (n != 0);
    }
    *(uint64_t *)(sptm_uat_nvme_state + 0x9f8) = guest_paddr;
skip_lock:
    {
    uint32_t cur = *(uint32_t *)(sptm_uat_nvme_state + 0xa00);
    if (cur != 0xffffffff && (attr & 3) != cur) {
        sptm_panic(0x300000d, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (cur == 0xffffffff) {
        *(uint32_t *)(sptm_uat_nvme_state + 0xa00) = attr & 3;
    }
    uint32_t *base = *(uint32_t **)(sptm_uat_nvme_state + 0x9f0);
    *base = (uint32_t)(guest_paddr >> 0xe);
    base[1] = *(uint32_t *)(sptm_uat_nvme_state + 0xa00);
    if (sptm_uat_nvme_state[0x7b8] == 1) {
        sptm_uat_nvme_state[0x7b8] = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
mismatch:
    sptm_panic(0x300000c, dbg, "__s__s__d_____s___llx__00011410");
}

/* FUN_000c2248 @ 0x000c2248   (est. sptm_nvme_bar_iocq_reg)
 * Ghidra: void FUN_000c2248(ulong param_1, undefined8 param_2)
 * Registers the I/O completion queue BAR: validates the address, stores its
 * low/high dwords in the NVMe register block, and sets the feature bit.
 * Confidence: high */
void sptm_nvme_bar_iocq_reg(uint64_t guest_paddr, uint64_t dbg)
{
    if (((NVME_FLAGS >> 7) & 1) == 0) {
        sptm_panic(0x3000005, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (sptm_uat_nvme_state[0x7b7] != 0) {
        sptm_panic(0x3000007, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    sptm_uat_nvme_state[0x7b7] = 1;
    uint64_t prev = *(uint64_t *)(sptm_uat_nvme_state + 0x7a8);
    if (prev != 0xffffffffffffffffULL && guest_paddr != prev) {
        sptm_panic(0x3000008, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (((guest_paddr < NVME_BAR_BASE) || NVME_BAR_BASE + NVME_BAR_SIZE <= guest_paddr) &&
        (guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr)) {
        sptm_panic(6, dbg, "__s__s__d_____s___llx__00011410");
    }
    if ((guest_paddr & 0xfff) != 0) {
        sptm_panic(0x3000003, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (prev == 0xffffffffffffffffULL) {
        *(uint64_t *)(sptm_uat_nvme_state + 0x7a8) = guest_paddr;
        sptm_phys_lock(guest_paddr, 2);
    }
    uint64_t regs = NVME_REGS;
    /* Low dword at (regs + 0x11), high dword at (regs + 0x14). Ghidra rendered
     * these relative to the s_sptm_uat_init_state string symbol (0x11f7/0x120c). */
    *(uint32_t *)(regs + 0x11) = (uint32_t)guest_paddr;
    *(uint32_t *)(regs + 0x14) = (uint32_t)(guest_paddr >> 0x20);
    if ((sptm_uat_nvme_state[0x771] & 1) != 0) {
        NVME_FLAGS = NVME_FLAGS | 0x40;
    }
    if (sptm_uat_nvme_state[0x7b7] == 1) {
        sptm_uat_nvme_state[0x7b7] = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000c24c8 @ 0x000c24c8   (est. sptm_nvme_bar_iosq_reg)
 * Ghidra: void FUN_000c24c8(ulong param_1, undefined8 param_2)
 * Registers the I/O submission queue BAR. Analogous to iocq. Confidence: high */
void sptm_nvme_bar_iosq_reg(uint64_t guest_paddr, uint64_t dbg)
{
    if (((NVME_FLAGS >> 6) & 1) == 0) {
        sptm_panic(0x3000005, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (sptm_uat_nvme_state[0x7b6] != 0) {
        sptm_panic(0x3000007, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    sptm_uat_nvme_state[0x7b6] = 1;
    uint64_t prev = *(uint64_t *)(sptm_uat_nvme_state + 0x7a0);
    if (prev != 0xffffffffffffffffULL && guest_paddr != prev) {
        sptm_panic(0x3000008, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (((guest_paddr < NVME_BAR_BASE) || NVME_BAR_BASE + NVME_BAR_SIZE <= guest_paddr) &&
        (guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr)) {
        sptm_panic(6, dbg, "__s__s__d_____s___llx__00011410");
    }
    if ((guest_paddr & 0xfff) != 0) {
        sptm_panic(0x3000003, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (prev == 0xffffffffffffffffULL) {
        *(uint64_t *)(sptm_uat_nvme_state + 0x7a0) = guest_paddr;
        sptm_phys_lock(guest_paddr, 2);
    }
    uint64_t regs = NVME_REGS;
    /* Low dword at (regs + 9), high dword at (regs + 0xd). Ghidra symbol artifact. */
    *(uint32_t *)(regs + 9) = (uint32_t)guest_paddr;
    *(uint32_t *)(regs + 0xd) = (uint32_t)(guest_paddr >> 0x20);
    if (sptm_uat_nvme_state[0x7b6] == 1) {
        sptm_uat_nvme_state[0x7b6] = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000c2734 @ 0x000c2734   (est. sptm_nvme_bar_ioqa_reg)
 * Ghidra: void FUN_000c2734(uint param_1, uint param_2)
 * Registers the I/O queue attributes (IOQA) register: packs the queue-depth
 * attributes into a single dword and stores it. param_1/param_2 = attributes.
 * Confidence: high */
void sptm_nvme_bar_ioqa_reg(uint32_t attr_a, uint32_t attr_b)
{
    uint32_t dbg = attr_b;
    if (((NVME_FLAGS >> 5) & 1) == 0) {
        sptm_panic(0x3000005, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (sptm_uat_nvme_state[0x7b5] != 0) {
        sptm_panic(0x3000007, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    sptm_uat_nvme_state[0x7b5] = 1;
    uint32_t pages = NVME_PAGES;
    if (pages < attr_a || pages < attr_b) {
        sptm_panic(0x3000009, dbg, "__s__s__d_____s___llx__00011410");
    }
    uint32_t combined = attr_a | attr_b << 0x10;
    if (*(uint32_t *)(sptm_uat_nvme_state + 0x798) != 0xffffffff &&
        combined != *(uint32_t *)(sptm_uat_nvme_state + 0x798)) {
        sptm_assert_fail("__s__IOQA_doesnt_match_the_previo_000045c8");
    }
    *(uint32_t *)(sptm_uat_nvme_state + 0x798) = combined;
    *(uint32_t *)(NVME_REGS + 0x18) = combined;   /* Ghidra: &DAT_00001210 + regs */
    if ((sptm_uat_nvme_state[0x771] & 1) != 0) {
        NVME_FLAGS = NVME_FLAGS | 0x80;
    }
    if (sptm_uat_nvme_state[0x7b5] == 1) {
        sptm_uat_nvme_state[0x7b5] = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000c2908 @ 0x000c2908   (est. sptm_nvme_bar_admin_queue_regs)
 * Ghidra: void FUN_000c2908(ulong param_1, undefined8 param_2, ulong param_3, uint param_4)
 * Registers the admin submission/completion queue BARs and the AQA attributes:
 * validates both addresses, locks the pages, and stores the queue-base dwords
 * plus the AQA combined value in the NVMe register block.
 * Confidence: high */
void sptm_nvme_bar_admin_queue_regs(uint64_t sq_paddr, uint64_t dbg, uint64_t cq_paddr,
                                    uint32_t aqa)
{
    if (((NVME_FLAGS >> 4) & 1) == 0) {
        sptm_panic(0x3000005, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (sptm_uat_nvme_state[0x7b4] != 0) {
        sptm_panic(0x3000007, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    sptm_uat_nvme_state[0x7b4] = 1;
    if ((0xffe < (uint32_t)dbg) || (0xffe < aqa)) {
        sptm_panic(0x3000009, dbg, "__s__s__d_____s___llx__00011410");
    }
    uint32_t combined = (uint32_t)dbg | aqa << 0x10;
    if (*(uint32_t *)(sptm_uat_nvme_state + 0x780) != 0xffffffff &&
        combined != *(uint32_t *)(sptm_uat_nvme_state + 0x780)) {
        sptm_assert_fail("__s__AQA_doesnt_match_the_previou_00004560");
    }
    *(uint32_t *)(sptm_uat_nvme_state + 0x780) = combined;
    uint64_t regs = NVME_REGS;
    *(uint32_t *)(regs + 0x24) = combined;
    uint64_t prev_sq = *(uint64_t *)(sptm_uat_nvme_state + 0x788);
    if (prev_sq != 0xffffffffffffffffULL && sq_paddr != prev_sq) {
        goto mismatch;
    }
    if (((sq_paddr < NVME_BAR_BASE) || NVME_BAR_BASE + NVME_BAR_SIZE <= sq_paddr) &&
        (sq_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= sq_paddr)) {
        goto bad_range;
    }
    if ((sq_paddr & 0xfff) == 0) {
        if (prev_sq == 0xffffffffffffffffULL) {
            *(uint64_t *)(sptm_uat_nvme_state + 0x788) = sq_paddr;
            sptm_phys_lock(sq_paddr, 2);
            regs = NVME_REGS;
        }
        *(uint32_t *)(regs + 0x28) = (uint32_t)sq_paddr;
        *(uint32_t *)(regs + 0x2c) = (uint32_t)(sq_paddr >> 0x20);
        uint64_t prev_cq = *(uint64_t *)(sptm_uat_nvme_state + 0x790);
        if (prev_cq != 0xffffffffffffffffULL && cq_paddr != prev_cq) goto mismatch;
        if (((cq_paddr < NVME_BAR_BASE) || NVME_BAR_BASE + NVME_BAR_SIZE <= cq_paddr) &&
            (cq_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= cq_paddr)) goto bad_range;
        if ((cq_paddr & 0xfff) == 0) {
            if (prev_cq == 0xffffffffffffffffULL) {
                *(uint64_t *)(sptm_uat_nvme_state + 0x790) = cq_paddr;
                sptm_phys_lock(cq_paddr, 2);
                regs = NVME_REGS;
            }
            *(uint32_t *)(regs + 0x30) = (uint32_t)cq_paddr;
            *(uint32_t *)(regs + 0x34) = (uint32_t)(cq_paddr >> 0x20);
            NVME_FLAGS = NVME_FLAGS | 0x26;
            if (sptm_uat_nvme_state[0x7b4] != 1) {
                sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
            }
            sptm_uat_nvme_state[0x7b4] = 0;
            return;
        }
    }
    sptm_panic(0x3000003, dbg, "__s__s__d_____s___llx__00011410");
mismatch:
    sptm_panic(0x3000008, dbg, "__s__s__d_____s___llx__00011410");
bad_range:
    sptm_panic(6, dbg, "__s__s__d_____s___llx__00011410");
}

/* =====================================================================
 * T8110 DART — device address resolution table
 * ===================================================================== */

/* FUN_000c7424 @ 0x000c7424   (est. sptm_t8110dart_clear_exception)
 * Ghidra: void FUN_000c7424(byte param_1, ulong param_2)
 * Clears a recorded DART exception/error: for each DART instance matching the
 * translated window, writes back the exception payload and, when needed,
 * re-arms the DART error path via sptm_dart_clear_error.
 * Confidence: high */
void sptm_t8110dart_clear_exception(uint8_t dart_id, uint64_t guest_paddr)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, guest_paddr, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    if (DART_VERSION(ctrl) < 0x202) {
        sptm_panic(0x6000018, dbg, "__s__s__d_____s___llx__00011410");
    }
    if ((guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr) ||
        (guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr)) {
        sptm_panic(6, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    uint32_t *w = sptm_dart_pte_lookup(guest_paddr, 0x24, 1, 0);
    uint32_t dart_index = *w;
    uint16_t ver = DART_VERSION(ctrl);
    uint32_t ndart = *(uint32_t *)(ctrl + 0xbd4);
    if (ndart != 0) {
        uint32_t i = 0;
        uint8_t *inst = *(uint8_t **)(ctrl + 8 + (uint64_t)dart_index * 0x78);
        uint32_t off = 0x3ffc;
        do {
            off += 4;
            if (w[i + 1] != 0) {
                if (*(uint32_t *)(ctrl + 0xba4) <= dart_index) goto invalid_dar;
                *(uint32_t *)(inst + off) = w[i + 1];
                ndart = *(uint32_t *)(ctrl + 0xbd4);
            }
            i++;
        } while (i < ndart);
    }
    if (dart_index < *(uint32_t *)(ctrl + 0xba4)) {
        if (((ver & 0xfffe) != 0x100) &&
            ((*(uint32_t *)(*(uint8_t **)(ctrl + 8 + (uint64_t)dart_index * 0x78) + 0x210) >> 1 & 1) != 0)) {
            sptm_dart_clear_error(ctrl);
            return;
        }
        return;
    }
invalid_dar:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
}

/* FUN_000c7efc @ 0x000c7efc   (est. sptm_t8110dart_clamp_tlimits)
 * Ghidra: void FUN_000c7efc(byte param_1, undefined8 param_2)
 * Clamps/restores the DART translation limits: under a per-CPU guard, clears
 * the per-instance limit registers for every DART instance when the
 * in-progress state allows it.
 * Confidence: high
 * Notes: guard at +0xbdf; per-instance limit regs at +0x228/+0x22c. */
void sptm_t8110dart_clamp_tlimits(uint8_t dart_id, uint64_t dbg_in)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, dbg_in, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);
    if ((*(uint8_t *)(ctrl + 0xbee) & 1) == 0) {
        sptm_panic(0x600001d, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (*(uint8_t *)(ctrl + 0xbe0) != 0) {
        if (*(uint32_t *)(ctrl + 0xba4) != 0) {
            uint32_t i = 0;
            uint64_t off = 8;
            do {
                uint8_t *inst = *(uint8_t **)(ctrl + off);
                *(uint32_t *)(inst + 0x22c) = 0;
                if (*(uint32_t *)(ctrl + 0xba4) <= i) {
                    sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
                }
                *(uint32_t *)(inst + 0x228) = 0;
                i++;
                off += 0x78;
            } while (i < *(uint32_t *)(ctrl + 0xba4));
        }
        cb = sptm_cpu_base();
        if (*DART_GUARD(ctrl) != sptm_uat_guard(cb)) {
            sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
        }
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_panic(0x6000016, dbg, "__s__s__d_____s___llx____s___llx__00011690");
}

/* FUN_000c8174 @ 0x000c8174   (est. sptm_t8110dart_read_smmu_stt_index)
 * Ghidra: void FUN_000c8174(byte param_1, undefined8 param_2)
 * Writes the SMMU STT (stream table) index into every DART instance's
 * register (inst+0x80) and flushes the affected DARTs.
 * Confidence: high */
void sptm_t8110dart_read_smmu_stt_index(uint8_t dart_id, uint32_t stt_index)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, stt_index, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    if ((DART_VERSION(ctrl) & 0xfffe) == 0x100) {
        sptm_panic(0x6000018, dbg, "__s__s__d_____s___llx__00011410");
    }
    if (*(uint32_t *)(ctrl + 0xbbc) == 0) {
        sptm_panic(0x600001a, dbg, "__s__s__d_____s___llx__00011410");
    }
    if ((uint32_t)stt_index < *(uint32_t *)(ctrl + 0xbbc)) {
        uint32_t ndart = *(uint32_t *)(ctrl + 0xba4);
        if (ndart != 0) {
            uint32_t i = 0;
            uint64_t off = 0x10;
            do {
                uint8_t *inst = *(uint8_t **)(ctrl + off);
                if (inst != NULL) {
                    *(uint32_t *)(inst + 0x80) = (uint32_t)stt_index & 0xffff;
                    ndart = *(uint32_t *)(ctrl + 0xba4);
                }
                i++;
                off += 0x78;
            } while (i < ndart);
            if (ndart != 0) {
                uint32_t j = 0;
                uint64_t off2 = 0x10;
                do {
                    uint8_t *inst = *(uint8_t **)(ctrl + off2);
                    if (inst != NULL) {
                        sptm_dart_flush(ctrl, j, 2, 0);
                        ndart = *(uint32_t *)(ctrl + 0xba4);
                    }
                    j++;
                    off2 += 0x78;
                } while (j < ndart);
            }
        }
        return;
    }
    sptm_panic(0x600001b, dbg, "__s__s__d_____s___llx____s___llx__00011690");
}

/* FUN_000c8384 @ 0x000c8384   (est. sptm_t8110dart_set_smmu_window)
 * Ghidra: void FUN_000c8384(byte param_1, ulong param_2, uint param_3)
 * Sets the SMMU window size for a DART instance: writes the window size into
 * instance register +0x20 after validating it fits within the instance's
 * address range.
 * Confidence: high */
void sptm_t8110dart_set_smmu_window(uint8_t dart_id, uint32_t inst_idx, uint32_t size)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, inst_idx, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    if ((DART_VERSION(ctrl) & 0xfffe) == 0x100) {
        if (inst_idx < *(uint32_t *)(ctrl + 0xba4)) {
            uint32_t *inst = *(uint32_t **)(ctrl + (uint64_t)inst_idx * 0x78 + 0x10);
            if (inst != NULL) {
                if (size < ((*inst & 0x1ffff) + 0x7ff) >> 0xb) {
                    inst[0x20] = size;
                    return;
                }
                sptm_panic(0x6000019, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
            }
        }
        sptm_panic(0x6000015, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    sptm_panic(0x6000018, dbg, "__s__s__d_____s___llx__00011410");
}

/* FUN_000c8554 @ 0x000c8554   (est. sptm_t8110dart_query_tlb)
 * Ghidra: void FUN_000c8554(byte param_1, ulong param_2, ulong param_3,
 *                           ulong param_4, ulong param_5)
 * Queries the DART TLB for an instance: builds a TLB-lookup descriptor from
 * the address/attrs, serializes access, polls the DART, and writes the TLB
 * result into the per-CPU result block.
 * Confidence: high */
void sptm_t8110dart_query_tlb(uint8_t dart_id, uint32_t inst_idx, uint32_t addr_lo,
                              uint32_t addr_hi, uint32_t attr)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, inst_idx, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(sptm_dart_id_map[dart_id], &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint32_t idx = inst_idx;
    if (*(uint32_t *)(ctrl + 0xba4) <= idx) {
        sptm_panic(0x6000015, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    uint8_t *inst = *(uint8_t **)(ctrl + 8 + (uint64_t)idx * 0x78);
    uint32_t tcfg = *(uint32_t *)inst;
    uint32_t tinfo = ((uint32_t *)inst)[1];
    if (((1ULL << ((tcfg >> 0x10) & 0xf)) + (tcfg & 0xfff) +
         (1ULL << ((tcfg >> 0xc) & 0xf)) <= (addr_lo & 0xffff)) ||
        ((addr_hi & 0xffff) >> ((tinfo >> 0x1c) & 7) != 0 ||
         (attr & 0xffff) >> ((tcfg >> 0x14) & 7) != 0)) {
        sptm_panic(0x6000025, dbg, "__s__s__d_____s___llx____s___llx__000111dc");
    }
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);

    uint32_t q[6];
    q[0] = 0; q[1] = 0; q[5] = 0x200;
    q[2] = idx;
    q[3] = ((uint32_t)addr_hi & 0xf) << 4 | ((addr_lo & 0xffff) & 0x3fff) << 8 | attr & 7;
    q[4] = 0;
    if (*(uint8_t *)(ctrl + 0xbe0) != 2) {
        sptm_lock_acquire();
        uint16_t s = *(uint16_t *)(ctrl + 0xc2c);
        *(uint16_t *)(ctrl + 0xc2c) = (uint16_t)(s | 1);
        sptm_lock_release();
        if ((s & 1) != 0) {
            sptm_assert_fail("__s__dart__p___s__u___Not_seriali_0000a5ac");
        }
        sptm_memcpy(ctrl + 0xbfc, q, 0x18);
    }
    int rc;
    do { rc = sptm_dart_poll(ctrl, 0); } while (rc == 0);

    cb = sptm_cpu_base();
    uint64_t *result = (uint64_t *)((uint8_t *)cb + 0x1b);   /* Ghidra: s_uat...po_00001595 + cb + 0x1b */
    uint64_t tbl;
    if ((DART_VERSION(ctrl) & 0xfffe) == 0x100) {
        tbl = (uint64_t)*(uint32_t *)(inst + 0x88);
    } else {
        tbl = *(uint64_t *)(inst + 0x88);
    }
    result[0] = tbl;
    result[1] = *(uint64_t *)(inst + 0x90);
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) == sptm_uat_guard(cb)) {
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000c8d04 @ 0x000c8d04   (est. sptm_t8110dart_clear_err)
 * Ghidra: void FUN_000c8d04(byte param_1, ulong param_2, uint param_3)
 * Clears a DART error bit: writes the single error flag into the instance's
 * error register (+0x100), and re-arms the error path on non-2.0 DARTs.
 * Confidence: high */
void sptm_t8110dart_clear_err(uint8_t dart_id, uint32_t inst_idx, uint32_t errbit)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, inst_idx, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint32_t idx = inst_idx;
    if (*(uint32_t *)(ctrl + 0xba4) <= idx) {
        sptm_panic(0x6000015, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (0x201 < DART_VERSION(ctrl)) {
        sptm_panic(0x6000018, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    uint8_t *inst = *(uint8_t **)(ctrl + 8 + (uint64_t)idx * 0x78);
    if ((*(uint32_t *)(inst + 0x100) >> 0x13 & 1) != 0) {
        if ((*(uint8_t *)(ctrl + 0xbf3) & 1) == 0) {
            sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000747c");
        }
        *(uint32_t *)(inst + 0x1c0) = *(uint32_t *)(inst + 0x1c0);
    }
    uint32_t mask = 0x7fd;
    if ((DART_VERSION(ctrl) & 0xfffe) != 0x100) {
        mask = 0x7fff;
    }
    if (POPCOUNT(mask & errbit) != 1) {
        sptm_panic(0x6000017, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((*(uint32_t *)(ctrl + 0xba4) <= idx) ||
        (*(uint32_t *)(inst + 0x100) = mask & errbit, *(uint32_t *)(ctrl + 0xba4) <= idx)) {
        sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
    }
    if (((DART_VERSION(ctrl) & 0xfffe) != 0x100) && ((*(uint32_t *)(inst + 0x210) >> 1 & 1) != 0)) {
        sptm_dart_clear_error(0);
        return;
    }
    return;
}

/* FUN_000c8fb8 @ 0x000c8fb8   (est. sptm_t8110dart_enable_translation)
 * Ghidra: void FUN_000c8fb8(byte param_1, ulong param_2)
 * Enables IOMMU translation for a DART stream: sets the per-stream enable bit
 * (stream enable register +0xc00) on every DART instance that is enabled.
 * SECURITY: this is what turns DMA translation ON for a stream.
 * Confidence: high */
void sptm_t8110dart_enable_translation(uint8_t dart_id, uint32_t stream)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, stream, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);

    uint32_t st = stream & 0xff;
    uint64_t ok;
    if ((*(uint8_t *)(ctrl + 0xbf1) & 1) != 0) {
        ok = sptm_dart_acquire_v2(ctrl, st, &dbg);
    } else {
        ok = sptm_dart_acquire_v1(ctrl, st, &dbg);
    }
    if ((ok & 1) == 0) {
        sptm_panic(0x6000009, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((st < *(uint32_t *)(ctrl + 0xb98)) &&
        (cb = (uint64_t)*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238), cb != 0) &&
        ((*(uint8_t *)(cb + 0x1d) & 1) != 0)) {
        sptm_panic(0x600001f, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    uint32_t ndart = *(uint32_t *)(ctrl + 0xba4);
    if (ndart != 0) {
        uint32_t i = 0;
        uint8_t *slice = *(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238);
        uint8_t **inst = (uint8_t **)(ctrl + 8);
        do {
            if ((*(uint8_t *)(slice + 0x18) & 1) != 0) {
                if (*(uint8_t *)(ctrl + 0xbe0) == 2) {
                    sptm_panic(0x6000016, dbg, "__s__s__d_____s___llx__00011410");
                }
                *(uint32_t *)(*inst + (uint64_t)(st >> 5) * 4 + 0xc00) = 1 << (st & 0x1f);
                ndart = *(uint32_t *)(ctrl + 0xba4);
            }
            i++;
            inst += 0xf;   /* 0x78/8 = 0xf u64 slots */
        } while (i < ndart);
    }
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != sptm_uat_guard(cb)) {
        sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
    }
    *DART_GUARD(ctrl) = 0;
}

/* FUN_000c93d8 @ 0x000c93d8   (est. sptm_t8110dart_disable_translation)
 * Ghidra: void FUN_000c93d8(byte param_1, ulong param_2)
 * Disables IOMMU translation for a DART stream: sets the per-stream disable
 * bit (stream disable register +0xc20) on every enabled instance.
 * SECURITY: the inverse of enable; both must be strictly ordered.
 * Confidence: high */
void sptm_t8110dart_disable_translation(uint8_t dart_id, uint32_t stream)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, stream, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);

    uint32_t st = stream & 0xff;
    uint64_t ok;
    if ((*(uint8_t *)(ctrl + 0xbf1) & 1) != 0) {
        ok = sptm_dart_acquire_v2(ctrl, st, &dbg);
    } else {
        ok = sptm_dart_acquire_v1(ctrl, st, &dbg);
    }
    if ((ok & 1) == 0) {
        sptm_panic(0x6000009, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((st < *(uint32_t *)(ctrl + 0xb98)) &&
        (cb = (uint64_t)*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238), cb != 0) &&
        ((*(uint8_t *)(cb + 0x1d) & 1) != 0)) {
        sptm_panic(0x600001f, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (((*(uint8_t *)(ctrl + 0xbe3) & 1) == 0) && (*(uint32_t *)(ctrl + 0xba4) != 0)) {
        uint32_t i = 0;
        uint64_t off = 8;
        do {
            sptm_dsb(3, 3, 0);
            uint32_t ndart = *(uint32_t *)(ctrl + 0xba4);
            uint8_t *slice = *(uint8_t **)(ctrl + 0x238 + (uint64_t)st * 8);
            if ((*(uint8_t *)(slice + 0x18) & 1) != 0) {
                if (ndart <= i) goto invalid_dar;
                *(uint32_t *)(*(uint8_t **)(ctrl + off) + (uint64_t)(st >> 5) * 4 + 0xc20) =
                    1 << (st & 0x1f);
                ndart = *(uint32_t *)(ctrl + 0xba4);
                if (ndart <= i) goto invalid_dar;
            }
            i++;
            off += 0x78;
        } while (i < ndart);
    }
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) == sptm_uat_guard(cb)) {
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
invalid_dar:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
}

/* Reverse the bit order of a 64-bit value (the decompiled DART stream-bitmap
 * scans use this to find the first free stream). */
static inline uint64_t sptm_bitrev64(uint64_t x)
{
    x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1) | ((x & 0x5555555555555555ULL) << 1);
    x = ((x & 0xccccccccccccccccULL) >> 2) | ((x & 0x3333333333333333ULL) << 2);
    x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4) | ((x & 0x0f0f0f0f0f0f0f0fULL) << 4);
    x = ((x & 0xff00ff00ff00ff00ULL) >> 8) | ((x & 0x00ff00ff00ff00ffULL) << 8);
    x = ((x & 0xffff0000ffff0000ULL) >> 16) | ((x & 0x0000ffff0000ffffULL) << 16);
    x = (x >> 32) | (x << 32);
    return x;
}

/* Advance a stream index to the next free stream in the 4-word allocation
 * bitmap (mirrors the decompiler's LZCOUNT-based scan). Returns the index or
 * a value >= max when none remains. */
static inline int sptm_next_stream(uint64_t *bitmap, int start, int max)
{
    uint64_t w = bitmap[start >> 6] & (~0ULL << (start & 0x3f));
    if (w == 0) {
        int wi = start >> 6;
        while (wi <= 3) {
            if (++wi > 3) return max;
            w = bitmap[wi];
            if (w) return LZCOUNT((uint32_t)(w >> 32 | w << 32)) + wi * 64;
        }
        return max;
    }
    return LZCOUNT((uint32_t)(w >> 32 | w << 32)) + (start & 0x1c0);
}

/* FUN_000c9728 @ 0x000c9728   (est. sptm_t8110dart_init)
 * Ghidra: void FUN_000c9728(byte param_1, undefined8 param_2)
 * Initializes the T8110 DART: under a per-CPU guard, validates every DART
 * instance's version/config, checks the per-instance translation tables
 * (consistency, APF slices, limits), and loads the instance control registers.
 * SECURITY: validates that the stream/PTE configuration is consistent before
 *   any translation is enabled; rejects mismatched PTE types and out-of-range
 *   window/limit sizes.
 * Confidence: high
 * Notes: reads instance version/type at inst+4/+8/+0xc; verifies window sizes
 *   against +0xb78/+0xb7c; per-stream allocation bitmaps at ctrl+0xa38. */
void sptm_t8110dart_init(uint8_t dart_id, uint64_t dbg_in)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, dbg_in, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);

    /* 128-bit APF window-mask constants (DAT_00012ef0/_ef8/_12f00/_12f38). */
    uint64_t m_hi = sptm_apf_mask_hi;
    uint64_t m_w0 = sptm_apf_mask_lo[0];
    uint64_t m_w1 = sptm_apf_mask_lo[1];
    uint64_t m_w2 = sptm_apf_mask_lo[2];

    if (*(uint8_t *)(ctrl + 0xbe0) != 0) {
        sptm_panic(0x6000016, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }

    uint32_t ndart = *(uint32_t *)(ctrl + 0xba4);
    if (ndart != 0) {
        uint32_t i = 0;
        uint64_t stream_off = 0x238;
        uint64_t *bitmap = (uint64_t *)(ctrl + 0xa38);
        do {
            uint8_t *inst = *(uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78);
            uint32_t t3 = *(uint32_t *)(inst + 4);
            uint32_t t4 = *(uint32_t *)(inst + 8);
            uint32_t t5 = *(uint32_t *)(inst + 0xc);
            uint32_t ver16 = t4 & 0xffff;
            if (((4 < ver16 - 0x200) && (1 < ver16 - 0x100)) && (ver16 != 0x300)) {
                sptm_assert_fail("__s__dart__p___s__u___DART_instan_000090d2");
            }
            if (DART_VERSION(ctrl) == 0) {
                *(uint64_t *)(ctrl + 0xb80) = 1ULL << ((t4 >> 0x18) & 0x3f);
                if (0x2a < (t4 >> 0x18 & 0x3f)) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_000091b9");
                }
            } else {
                if ((uint32_t)DART_VERSION(ctrl) != ver16) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000911c");
                }
                if ((1ULL << ((t4 >> 0x18) & 0x3f)) != *(uint64_t *)(ctrl + 0xb80)) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009163");
                }
            }
            DART_VERSION(ctrl) = (uint16_t)t4;

            uint32_t window_shift, granule_shift;
            if ((t4 & 0xfffe) == 0x100) {
                if (((*(uint8_t *)(ctrl + 0xbeb) & 1) != 0) ||
                    ((*(uint8_t *)(ctrl + 0xbea) & 1) != 0)) {
                    sptm_assert_fail("__s__dart__p___s__u___flush_by_dv_000091f7");
                }
                if ((*(uint8_t *)(ctrl + 0xbec) & 1) != 0) {
                    sptm_assert_fail("__s__dart__p___s__u___Non_complia_00009227");
                }
                window_shift = 0;
                granule_shift = 0x400000;
            } else {
                if (((*(uint8_t *)(ctrl + 0xbea) & 1) == 0) &&
                    (*(uint32_t *)(ctrl + 0xbac) != 0)) {
                    *(uint8_t *)(ctrl + 0xbeb) = 1;
                }
                if ((t3 >> 4 & 1) != 0) {
                    *(uint8_t *)(ctrl + 0xbed) = 1;
                }
                granule_shift = 0x10000000;
                window_shift = 0x4000000;
            }
            if ((uint32_t)((1ULL << ((t4 >> 0x10) & 0x3f)) >> 0xe) <= window_shift) {
                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000926a");
            }
            uint32_t n_streams = t5 & 0x1ff;
            if ((n_streams < *(uint32_t *)(ctrl + 0xba0)) ||
                (n_streams < *(uint32_t *)(ctrl + 0xb98))) {
                sptm_assert_fail("__s__dart__p___s__u___DART_instan_000092c7");
            }
            *(uint32_t *)(ctrl + 0xb9c) = n_streams;
            uint32_t nwords = (n_streams + 0x1f) >> 5;
            *(uint32_t *)(ctrl + 0xbd4) = nwords;

            /* Load the 128-bit APF window mask selection (Ghidra auVar32/auVar33). */
            uint64_t sel = ((uint64_t)(uint32_t)t4 << 32 | (uint64_t)(uint32_t)t4) & 0xffff0000ffffULL;
            uint32_t lo = (uint32_t)sel, hi = (uint32_t)(sel >> 32);
            int32_t sgn_lo = -(int16_t)(uint16_t)(lo < (uint32_t)m_hi ? (uint16_t)((uint32_t)lo < (uint32_t)(uint32_t)m_hi) : 0);
            (void)sgn_lo;
            /* Masking helper — apply the per-window constant selection. */
            uint64_t w_mask[2];
            w_mask[0] = m_w0; w_mask[1] = m_w1;
            if (hi < (uint32_t)(m_hi >> 32)) { w_mask[0] = m_w0; w_mask[1] = m_w1; }
            else if (hi == (uint32_t)(m_hi >> 32)) {
                if (lo < (uint32_t)m_hi) { w_mask[0] = m_w0; w_mask[1] = m_w1; }
                else { w_mask[0] = m_w2; w_mask[1] = m_w2; }
            } else { w_mask[0] = m_w2; w_mask[1] = m_w2; }
            (void)w_mask;
            /* The four APF limit-register offsets are stored at +0xbc4/0xbc8/
             * 0xbcc/0xbd0. The selection mask above gates which constant set. */
            *(uint32_t *)(ctrl + 0xbcc) = (uint32_t)m_hi;
            *(uint32_t *)(ctrl + 0xbd0) = (uint32_t)(m_hi >> 32);
            *(uint32_t *)(ctrl + 0xbc4) = (uint32_t)m_w0;
            *(uint32_t *)(ctrl + 0xbc8) = (uint32_t)(m_w0 >> 32);

            if ((*(uint32_t *)(ctrl + 0xb7c) < window_shift) ||
                (granule_shift < *(uint32_t *)(ctrl + 0xb78))) {
                sptm_assert_fail("__s__dart__p___s__u___DART_instan_000092fc");
            }

            /* Verify each stream's PTE against its slice descriptor. */
            if ((*(uint8_t *)(ctrl + 0xbe8) & 1) != 0) {
                uint64_t lock_ok = sptm_dart_lock(ctrl, i);
                if (((lock_ok & 1) == 0) && ((sptm_apf_enable & 1) == 0)) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000969e");
                }
                if (n_streams != 0) {
                    uint32_t s = 0;
                    uint32_t *pte = (uint32_t *)(*(uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78) + 0x1000);
                    do {
                        uint32_t e = *pte;
                        uint64_t *slice = *(uint64_t **)(stream_off + (uint64_t)s * 8);
                        if (slice == NULL) {
                            if (s != 0xe) {
                                if (s < *(uint32_t *)(ctrl + 0xb98)) {
                                    uint64_t w = s >> 6;
                                    uint64_t bit = 1ULL << (s & 0x3f);
                                    if ((((*(uint64_t *)(ctrl + 0xa78 + w * 8) & bit) != 0) ||
                                         ((*(uint64_t *)(ctrl + 0xad8 + w * 8) & bit) != 0)) ||
                                        ((*(uint64_t *)(ctrl + 0xa98 + w * 8) & bit) != 0) ||
                                        ((*(uint64_t *)(ctrl + 0xab8 + w * 8) & bit) != 0)) {
                                        goto next_stream;
                                    }
                                }
                                if ((e & 0xffff00ff) != 1) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_000096fb");
                                }
                            }
                        } else if ((*(uint8_t *)((uint8_t *)slice + 0x1e) & 1) != 0) {
                            uint32_t sl = (uint32_t)slice[3];
                            uint32_t sl_ste = e >> 7 & 1;
                            if (sl_ste != (sl >> 7 & 1)) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009757");
                            }
                            uint32_t e_hi = pte[0x100];
                            if (sl_ste == 0) {
                                if ((e & 1) != (sl & 1)) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000989d");
                                }
                                if ((e & 1) == 0) {
                                    if ((e_hi & 1) != 0) {
                                        sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000997d");
                                    }
                                    if ((*(uint8_t *)(ctrl + 0xbe9) & 1) == 0) {
                                        if ((e >> 1 & 1) == 0) {
                                            if (slice[0] != 0) {
                                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009a4c");
                                            }
                                        } else if (slice[0] != 0) {
                                            sptm_assert_fail("__s__dart__p___s__u___DART_instan_000099ef");
                                        }
                                    }
                                } else if (((e_hi & 1) == 0) ||
                                           ((e_hi >> 2 & 0xfffffff) !=
                                            ((uint32_t)(slice[0] >> 10) & 0xfffffff))) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009912");
                                }
                            } else {
                                if (((sl ^ e) & 0xff00) != 0) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_000097c6");
                                }
                                if (slice[0] != 0) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000982e");
                                }
                            }
                            if ((DART_VERSION(ctrl) < 0x202) && (((sl ^ e) >> 2 & 1) != 0)) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009aa7");
                            }
                        }
next_stream:
                        s++;
                        pte++;
                    } while (n_streams != s);
                }
            }

            /* Validate the stream window/limit geometry via the first free stream. */
            uint64_t guest_base = sptm_guest_mem_start & 0xffffffffe0000000ULL;
            int st = sptm_next_stream(bitmap, 0, *(uint32_t *)(ctrl + 0xb98));
            if (st < (int)*(uint32_t *)(ctrl + 0xb98)) {
                do {
                    uint8_t *slice = *(uint8_t **)(stream_off + (uint64_t)st * 8);
                    if (slice == NULL) {
                        sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009344");
                    }
                    uint32_t u6 = *(uint32_t *)(slice + 0x18);
                    if ((u6 >> 7 & 1) == 0) {
                        if ((u6 >> 1 & 1) == 0) {
                            if ((u6 & 1) == 0) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009417");
                            }
                            if (*(uint32_t *)(slice + 0x10) == 0) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000945a");
                            }
                            if (granule_shift < *(uint32_t *)(slice + 0x10) ||
                                *(uint32_t *)(slice + 0x14) < window_shift) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_000094a7");
                            }
                            if ((((u6 >> 3 & 1) != 0) &&
                                 ((DART_VERSION(ctrl) & 0xfffe) == 0x100)) &&
                                ((t4 >> 0x10 & 0x3f) != 0x2a)) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000950f");
                            }
                        } else {
                            sptm_dart_lock_set(ctrl, i, (uint32_t)st & 0xff);
                            uint64_t sl0 = **(uint64_t **)(stream_off + (uint64_t)st * 8);
                            uint64_t sl_window = sl0 & 0x3ffffffc00;
                            uint64_t sl_size = sl_window << 4;
                            if ((t3 & 1) == 0) {
                                if ((sl_size >> ((t4 >> 0x18) & 0x3f) != 0 ||
                                     (sl0 & 0x3ffffffc00) >> 0x1d == 0) ||
                                    guest_base <= sl_size) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_000093c7");
                                }
                            } else if (((*(uint8_t *)(ctrl + 0xbe9) & 1) == 0) &&
                                       (sl_window != 0)) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000937a");
                            }
                        }
                    }
                    if (0xfe < st) break;
                    st = sptm_next_stream(bitmap, st + 1, *(uint32_t *)(ctrl + 0xb98));
                } while (st < (int)*(uint32_t *)(ctrl + 0xb98));
            }

            /* Record the SMMU window size for this instance. */
            uint8_t *inst1 = *(uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78);
            uint8_t **instp = (uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78);
            if (instp[1] != NULL) {
                uint32_t win;
                if (DART_VERSION(ctrl) < 0x201) {
                    win = *(uint32_t *)(*(uint32_t **)(ctrl + 0x10 + (uint64_t)i * 0x78)) & 0x1ffff;
                } else {
                    win = *(uint32_t *)(inst1 + 0x18) & 0xffff;
                }
                if (*(uint32_t *)(ctrl + 0xbbc) < win) {
                    *(uint32_t *)(ctrl + 0xbbc) = win;
                }
            }

            /* Validate the APF slice table. */
            uint32_t nsl = (t3 >> 8) & 0xff;
            if (nsl == 0) {
                if ((*(uint32_t *)(ctrl + 0xb70) != 0) && (i == *(uint32_t *)(ctrl + 0xb74))) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009563");
                }
            } else {
                uint64_t *apf = (uint64_t *)instp[2];
                if ((apf != NULL) && (nsl < (uint32_t)apf[1])) {
                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_000095b5");
                }
                uint64_t *apf_active = apf;
                if ((*(uint8_t *)(ctrl + 0xbe8) & 1) != 0) {
                    if ((((*(uint32_t *)(inst1 + 0x208) & *(uint32_t *)(inst1 + 0x200)) >> 2 & 1) == 0) &&
                        ((sptm_apf_enable & 1) == 0)) {
                        sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009b75");
                    }
                    apf_active = *(uint64_t **)(ctrl + 0x18 + (uint64_t)i * 0x78);
                    if (apf_active != NULL) {
                        /* Verify each APF slice's page-size/limit fields. */
                        uint64_t n = 0;
                        uint64_t ntotal = apf_active[1];
                        (void)ntotal;
                        uint8_t *wbase = (uint8_t *)apf_active[0];
                        uint32_t nw = *(uint32_t *)(ctrl + 0xbd4);
                        (void)nw;
                        while (n < (uint64_t)nsl) {
                            uint32_t *s1 = (uint32_t *)(apf_active[2] + n * 0x40);
                            uint32_t *s2 = (uint32_t *)((uint8_t *)apf_active[0] + n * 0x40);
                            if ((((s2[2] & 0xfffffffc) != (s1[2] & 0xfffffffc)) ||
                                 ((s2[3] & 0xf) != ((uint32_t)(s1[2] >> 32) & 0xf))) ||
                                ((s2[4] & 0xfffffffc) != (s1[4] & 0xfffffffc)) ||
                                ((s2[5] & 0xf) != ((uint32_t)(s1[4] >> 32) & 0xf))) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000769d");
                            }
                            if ((s2[0] & 0x333) != (s1[0] & 0x333)) {
                                sptm_assert_fail("__s__dart__p___s__u___DART_instan_0000769d");
                            }
                            n++;
                        }
                    }
                }
                if (apf != NULL) {
                    /* Program the APF slice window/limit registers. */
                    uint32_t nsl_used = (uint32_t)apf_active[1];
                    (void)nsl_used;
                    uint32_t apf_max = *(uint32_t *)(ctrl + 0xb98);
                    uint32_t k = 0;
                    uint64_t a0 = apf_active[0];
                    while (k < nsl) {
                        uint64_t waddr = apf_active[2] + (uint64_t)k * 0x40;
                        uint64_t lo = *(uint64_t *)(waddr + 8);
                        uint64_t hi = *(uint64_t *)(waddr + 0x10);
                        if (lo < guest_base && hi < guest_base) {
                            if ((*(uint8_t *)(waddr + 0x38) & 1) != 0) {
                                sptm_assert_fail("__s__dart__p___s__u___APF_slice___000089e7");
                            }
                        } else {
                            /* APF window must be a registered region. */
                            uint32_t napf = *(uint32_t *)(ctrl + 0xb70);
                            uint64_t *ar = (uint64_t *)(ctrl + 0xb40);
                            int found_apf = 0;
                            if (napf != 0) {
                                uint32_t m = 0;
                                do {
                                    if ((ar[-1] == (lo + 0x3fff & 0xffffffffffffc000)) &&
                                        (ar[0] == (hi + 0x3fff & 0xffffffffffffc000))) {
                                        if ((*(uint8_t *)(waddr + 0x38) & 1) != 0) {
                                            sptm_assert_fail("__s__dart__p___s__u___APF_slice___0000891a");
                                        }
                                        found_apf = 1;
                                        break;
                                    }
                                    ar += 2;
                                    m++;
                                } while (m < napf);
                            }
                            if (!found_apf) {
                                if ((*(uint8_t *)(waddr + 0x38) & 1) == 0) {
                                    sptm_assert_fail("__s__dart__p___s__u___Invalid_lim_00008997");
                                }
                                hi = *(uint64_t *)(waddr + 0x10);
                            }
                        }
                        if (hi < lo) {
                            sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009606");
                        }
                        k++;
                    }
                }
            }
            i++;
        } while (i < ndart);
    }
    *(uint8_t *)(ctrl + 0xbe0) = 1;
    *(uint32_t *)(ctrl + 0xc2e) = 0;
    *(uint32_t *)(ctrl + 0xc2c) = 0;
    *(uint32_t *)(ctrl + 0xbe2) = 0;
    *(uint8_t *)(ctrl + 0xbe1) = 0;
    sptm_memset(ctrl + 0xbfc, 0, 0x30);
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) == sptm_uat_guard(cb)) {
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000cacd0 @ 0x000cacd0   (est. sptm_t8110dart_skip_enable_clock_protection_write;
 *   also aliased sptm_t8110dart_enable_clock_protection / sptm_t8110dart_powerup)
 * Ghidra: void FUN_000cacd0(byte param_1, undefined8 param_2)
 * Enables DART clock protection (powerup): pushes the per-stream page-size
 * (ps_wr) reference count, configures the translation-window page-size
 * registers for every instance, and drives the stream's page-size changes
 * into the DART registers.
 * SECURITY: clock-protection/PS writes gate DMA; a per-CPU guard serializes
 *   access and the ps_wr refcount table prevents underflow/overflow.
 * Confidence: high
 * Notes: ps_wr refcount table DAT_001012b8 (stride 6); guard DAT_001012c0;
 *   register writes via sptm_dart_write_reg_v1/v2 + sptm_dart_write_field_v1/v2. */
void sptm_t8110dart_skip_enable_clock_protection_write(uint8_t dart_id, uint64_t dbg_in)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, dbg_in, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);
    if (*(uint8_t *)(ctrl + 0xbe0) == 0) {
        sptm_panic(0x6000016, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }

    /* Configure the PIO (per-instance-override) descriptors. */
    uint32_t npio = *(uint32_t *)(ctrl + 0xbb0);
    if (npio != 0) {
        uint32_t k = 0;
        do {
            uint8_t *pio = *(uint8_t **)(ctrl + 0x208 + (uint64_t)k * 0x10);
            if (pio == NULL) goto null_ptr;
            if ((*(uint32_t *)(pio + 0x10) == 0) && (*(uint32_t *)(pio + 0xc) == 0)) {
                /* Initialize the PIO descriptor (Ghidra: writes into pio+0x24..0x37). */
                pio[0x28] = 0; pio[0x29] = 0; pio[0x2a] = 0; pio[0x2b] = 0;
                if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                pio[0x2c] = 0; pio[0x2d] = 0; pio[0x2e] = 0; pio[0x2f] = 0;
                if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                pio[0x30] = 0xff; pio[0x31] = 0xff; pio[0x32] = 0xff; pio[0x33] = 0xff;
                if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                pio[0x34] = 0xff; pio[0x35] = 0xff; pio[0x36] = 0xff; pio[0x37] = 0xff;
                if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                pio[0x24] = 3;
                if (*(uint32_t *)(ctrl + 0xbb4) != 0) {
                    uint32_t m = 0;
                    uint64_t r = 0xb5c;
                    do {
                        uint32_t kk = k;
                        if (*(uint32_t *)(ctrl + 0xbb0) <= kk) goto invalid_pio;
                        uint32_t rlo = *(uint32_t *)(ctrl + r - 4) * 0x20;
                        uint64_t rhi = *(uint64_t *)(ctrl + r);
                        uint32_t rhi_lo = *(uint32_t *)(ctrl + r + 4);
                        (void)rhi_lo;
                        *(uint32_t *)(pio + (uint64_t)(rlo + 0x1124)) = (uint32_t)*(uint64_t *)(ctrl + r);
                        if (*(uint32_t *)(ctrl + 0xbb0) <= kk) goto invalid_pio;
                        *(uint32_t *)(pio + (uint64_t)(rlo + 0x1128)) = rhi_lo;
                        if (*(uint32_t *)(ctrl + 0xbb0) <= kk) goto invalid_pio;
                        *(uint32_t *)(pio + (uint64_t)(rlo + 0x112c)) = (uint32_t)(rhi + 3);
                        if (*(uint32_t *)(ctrl + 0xbb0) <= kk) goto invalid_pio;
                        *(uint32_t *)(pio + (uint64_t)(rlo + 0x1130)) = (uint32_t)((rhi + 3) >> 0x20);
                        if (*(uint32_t *)(ctrl + 0xbb0) <= kk) goto invalid_pio;
                        *(uint32_t *)(pio + (uint64_t)(rlo + 0x1120)) = 6;
                        m++;
                        r += 0xc;
                    } while (m < *(uint32_t *)(ctrl + 0xbb4));
                }
                if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                *(uint32_t *)(pio + 4) = *(uint32_t *)(pio + 4) | 1;
                npio = *(uint32_t *)(ctrl + 0xbb0);
            }
            k++;
        } while (k < npio);
    }

    /* Push per-instance page-size refcounts and drive register changes. */
    if (*(uint32_t *)(ctrl + 0xba4) != 0) {
        uint32_t i = 0;
        do {
            if (sptm_ps_wr_mode == 1) {
                uint8_t *instrow = ctrl + 8 + (uint64_t)i * 0x78;
                uint8_t old_guard = sptm_ps_wr_guard;
                uint8_t ps_idx = *(uint8_t *)(instrow + 0x28);
                if (*(uint8_t *)(instrow + 0x2a) == 0) {
                    if (ps_idx != 0xff) {
                        cb = sptm_cpu_base();
                        uint8_t g = sptm_uat_guard(cb);
                        if (sptm_ps_wr_guard != 0) goto guard_conflict;
                        sptm_ps_wr_guard = g;
                        if (sptm_ps_wr_table == NULL) goto null_ptr;
                        if (sptm_ps_wr_max < ps_idx || sptm_ps_wr_max == ps_idx) goto invalid_ps_wr;
                        char c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                        if (c == 0) {
                            sptm_dart_ps_refcount(ctrl, ps_idx, 1);
                            c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                        } else if (c == -1) {
                            goto ps_overflow;
                        }
                        sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4] = (char)(c + 1);
                        cb = sptm_cpu_base();
                        if (sptm_ps_wr_guard != sptm_uat_guard(cb)) goto guard_mismatch;
                        sptm_ps_wr_guard = 0;
                    }
                    ps_idx = *(uint8_t *)(instrow + 0x29);
                    if (ps_idx != 0xff) {
                        cb = sptm_cpu_base();
                        uint8_t g = sptm_uat_guard(cb);
                        if (sptm_ps_wr_guard != 0) goto guard_conflict;
                        sptm_ps_wr_guard = g;
                        if (sptm_ps_wr_table == NULL) goto null_ptr;
                        if (sptm_ps_wr_max < ps_idx || sptm_ps_wr_max == ps_idx) goto invalid_ps_wr;
                        char c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                        if (c == 0) {
                            sptm_dart_ps_refcount(ctrl, ps_idx, 1);
                            c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                        } else if (c == -1) {
                            goto ps_overflow;
                        }
                        sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4] = (char)(c + 1);
                        cb = sptm_cpu_base();
                        if (sptm_ps_wr_guard != sptm_uat_guard(cb)) goto guard_mismatch;
                    }
                }
                sptm_ps_wr_guard = old_guard;
                *(uint8_t *)(ctrl + 0x32 + (uint64_t)i * 0x78) = 1;
            } else if ((sptm_alt_dart_mode & 1) == 0) {
                if (*(uint64_t *)(ctrl + 0x1e8) != 0) {
                    sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009dad");
                }
            } else {
                if ((*(uint8_t *)(ctrl + 0xbf7) & 1) != 0) {
                    uint8_t *sl = sptm_dart_slice_table + (uint64_t)*(uint8_t *)(ctrl + 0xbfb) * 0x10;
                    int16_t n = *(int16_t *)(sl + 0xe);
                    *(uint16_t *)(sl + 0xe) = (uint16_t)(n + 1);
                    if (*(uint16_t *)(sl + 0xc) < (uint16_t)(n + 1)) {
                        sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009ff1");
                    }
                    if (n != 0) goto skip_alt;
                }
                if (*(uint32_t *)(ctrl + 0xba8) != 0) {
                    uint32_t m = 0;
                    uint64_t pio_off = 0x1f0;
                    do {
                        uint32_t pio_idx = *(uint32_t *)(ctrl + 0x28 + (uint64_t)i * 0x78 + m * 4);
                        if ((pio_idx == 0) || (*(uint32_t *)(ctrl + pio_off) <= pio_idx)) {
                            sptm_assert_fail("__s__dart__p___s__u___Invalid___s_00008bbc");
                        }
                        uint8_t *pio2 = *(uint8_t **)(ctrl + pio_off - 8);
                        if (pio2 == NULL) goto null_ptr;
                        uint32_t woff = (pio_idx * 0x40 + 0x100) >> 2;
                        uint32_t w = *(uint32_t *)(pio2 + (uint64_t)woff * 4);
                        if ((w >> 1 & 1) == 0) {
                            sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009e21");
                        }
                        if ((((*(uint8_t *)(ctrl + 0xbe8) & 1) == 0) && ((w >> 4 & 1) != 0)) &&
                            ((*(uint8_t *)(ctrl + 0xbe4) & 1) == 0)) {
                            sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009e6e");
                        }
                        *(uint32_t *)(pio2 + (uint64_t)woff * 4) = w | 0x10;
                        if (*(uint64_t *)(ctrl + 0xc38) != 0) {
                            *(uint32_t *)(*(uint64_t *)(ctrl + 0xc38) +
                                          (uint64_t)*(uint32_t *)(ctrl + 0x28 + (uint64_t)i * 0x78) * 4) = w | 0x10;
                            sptm_dmb(2, 3);
                        }
                        m++;
                        pio_off += 0x10;
                    } while (m < *(uint32_t *)(ctrl + 0xba8));
                }
            }
skip_alt:
            /* Select the register-write variants for this instance. */
            uint64_t lockstat = sptm_dart_lock(ctrl, i);
            uint8_t **instp = (uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78);
            uint32_t *hw = (uint32_t *)*instp;
            void (*wreg)(void *, uint32_t, uint64_t, uint64_t);
            void (*wfield)(void *, uint32_t, uint64_t, uint64_t, uint64_t);
            if (lockstat == 0) wreg = sptm_dart_write_reg_v1;
            else wreg = sptm_dart_write_reg_v2;
            if (((hw[0x82] & hw[0x80]) >> 2 & 1) == 0) wfield = sptm_dart_write_field_v1;
            else wfield = sptm_dart_write_field_v2;
            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
            hw[0x84] = *(uint32_t *)(ctrl + 0xbc0);

            if ((hw[1] >> 2 & 1) == 0) {
                if (*(uint64_t *)(ctrl + 0xb28) != 0) {
                    sptm_assert_fail("__s__dart__p___s__u___TZ_Dead_Pag_0000a252");
                }
            } else {
                if (((sptm_apf_enable & 1) == 0) && ((hw[0x82] & 0x18) != 0x18)) {
                    sptm_assert_fail("__s__dart__p___s__u___instance__u_0000a035");
                }
                if ((hw[0x80] & 0x18) != 0x18) {
                    sptm_assert_fail("__s__dart__p___s__u___instance__u_0000a0ab");
                }
                if (((((hw[0x141] & 1) != *(uint32_t *)(ctrl + 0xaf8)) ||
                      ((hw[0x140] & 7) != *(uint32_t *)(ctrl + 0xafc))) ||
                     ((hw[0x142] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb00))) ||
                    (((hw[0x144] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb04) ||
                      (hw[0x146] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb08))) ||
                    ((hw[0x148] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb0c)) ||
                    (((hw[0x14a] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb10) ||
                      (hw[0x14c] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb14))) ||
                    ((hw[0x14e] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb18) ||
                     ((hw[0x150] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb1c) ||
                      (hw[0x152] & 0x3ffffffc) != *(uint32_t *)(ctrl + 0xb20)))) {
                    sptm_assert_fail("__s__dart__p___s__u___instance__u_0000a100");
                }
                if ((*(uint64_t *)(ctrl + 0xb28) != 0) &&
                    ((DART_VERSION(ctrl) & 0xfffe) != 0x100)) {
                    sptm_assert_fail("__s__dart__p___s__u___TZ_Dead_Pag_0000a20a");
                }
            }

            /* Client partition table. */
            uint32_t *clients = (uint32_t *)instp[3];
            uint32_t hw0 = *hw;
            uint32_t hw3 = hw[3];
            if ((clients != NULL) && (clients[0] != 0)) {
                uint32_t nc = clients[0];
                uint32_t m = 0;
                uint64_t coff = 0;
                do {
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    uint32_t *cl = (uint32_t *)(*(uint64_t *)(clients + 2) + coff);
                    uint32_t reg = *cl, mask = cl[1], want = cl[2];
                    uint32_t cur = *(uint32_t *)(*instp + (uint64_t)(reg >> 2) * 4);
                    if ((cur & mask) != (want & mask)) {
                        if ((0x7ff < reg && reg < (hw3 >> 0xe & 0x7fc | 0x800)) &&
                            (hw0 & 0x20000000) == 0) {
                            sptm_assert_fail("__s__dart__p___s__u___Client_part_00009c5a");
                        }
                        wreg(ctrl, i, reg, cur & (mask ^ 0xffffffff) | want & mask);
                        nc = clients[0];
                    }
                    m++;
                    coff += 0xc;
                } while (m < nc);
            }

            /* Configure per-stream page-size registers. */
            uint16_t ver = DART_VERSION(ctrl);
            uint32_t keep = (ver < 0x204) ? 0xffffffff : 0xfffffffd;
            int st = sptm_next_stream(bitmap_ctrl(ctrl), 0, *(uint32_t *)(ctrl + 0xb98));
            if (st < (int)*(uint32_t *)(ctrl + 0xb98)) {
                do {
                    sptm_dart_lock_set(ctrl, i, (uint32_t)st & 0xff);
                    uint8_t *slice = *(uint8_t **)(ctrl + 0x238 + (uint64_t)(st & 0xff) * 8);
                    if ((*(uint32_t *)(ctrl + 0xb98) <= (st & 0xff)) || (slice == NULL) ||
                        ((*(uint8_t *)(slice + 0x1d) & 1) == 0)) {
                        cb = sptm_cpu_base();
                        uint8_t *sguard = slice + 0x1f;
                        uint8_t g = *sguard;
                        if (g == 0) {
                            *sguard = sptm_uat_guard(cb);
                        }
                        if (g != 0) {
                            sptm_panic(0x6000001, 0, "__s__s__d_____s___llx____s___llx__000112f5");
                        }
                        uint64_t sl = *(uint64_t *)slice;
                        uint64_t pg = (sl >> 8) & 0x3ffffffc | sl & 1;
                        int is_v1 = (lockstat == 0);
                        if (is_v1) {
                            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                            uint32_t *dst = (uint32_t *)(*instp + (uint64_t)(st & 0xff) * 4);
                            dst[0x1000] = (uint32_t)slice[3];
                            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                            dst[0x1002] = (uint32_t)pg;
                        } else {
                            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                            uint32_t *dst = (uint32_t *)(*instp + (uint64_t)(st & 0xff) * 4);
                            uint32_t u8 = dst[0x1000];
                            uint32_t u10 = dst[0x1002];
                            if ((u8 >> 7 & 1) == 0) {
                                if ((u8 & 0xffff007f) != ((uint32_t)slice[3] & keep)) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009caa");
                                }
                                if (((sl & 1) != 0 || (u10 & 1) != 0) && u10 != pg) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009d57");
                                }
                            } else {
                                if (u8 != ((uint32_t)slice[3] & keep)) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009caa");
                                }
                                if ((u10 & 1) != 0) {
                                    sptm_assert_fail("__s__dart__p___s__u___DART_instan_00009d06");
                                }
                            }
                        }
                        cb = sptm_cpu_base();
                        uint8_t *sp = *(uint8_t **)(ctrl + 0x238 + (uint64_t)(st & 0xff) * 8) + 0x1f;
                        if (*sp != sptm_uat_guard(cb)) goto guard_mismatch;
                        *sp = 0;
                    }
                    if (0xfe < st) break;
                    st = sptm_next_stream(bitmap_ctrl(ctrl), st + 1, *(uint32_t *)(ctrl + 0xb98));
                } while (st < (int)*(uint32_t *)(ctrl + 0xb98));
            }

            /* Flush + restore instance control registers. */
            if (ver < 0x204) {
                uint64_t fdesc[3];
                fdesc[0] = 0;
                if (0x201 < ver) { fdesc[2] = 0x800000000000; }
                else { fdesc[2] = 0; }
                fdesc[1] = 0;
                if (*(uint8_t *)(ctrl + 0xbe0) != 2) {
                    sptm_lock_acquire();
                    uint16_t s = *(uint16_t *)(ctrl + 0xc2c);
                    *(uint16_t *)(ctrl + 0xc2c) = (uint16_t)(s | 1);
                    sptm_lock_release();
                    if ((s & 1) != 0) {
                        sptm_assert_fail("__s__dart__p___s__u___Not_seriali_0000a5ac");
                    }
                    sptm_memcpy(ctrl + 0xbfc, fdesc, 0x18);
                }
                int rc;
                do { rc = sptm_dart_poll(ctrl, 0); } while (rc == 0);
                if (ver > 0x203) goto flush_done;
                if (*(uint8_t *)(ctrl + 0xbe0) == 1) {
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    *(uint32_t *)(*instp + 0x228) = *(uint32_t *)(*instp + 0x228);
                    *(uint32_t *)(*instp + 0x22c) = *(uint32_t *)(*instp + 0x22c);
                    goto flush_done;
                }
                wreg(ctrl, i, 0x228, *(uint32_t *)(*instp + 0x228));
                wreg(ctrl, i, 0x22c, *(uint32_t *)(*instp + 0x22c));
            }
flush_done:
            uint8_t **apf = (uint8_t **)instp[2];
            if ((apf != NULL) && (apf[0] != NULL) && (*(uint32_t *)apf[1] != 0)) {
                uint32_t na = *(uint32_t *)(apf[1]);
                uint32_t k = 0;
                uint64_t abase = apf[2];
                uint32_t ireg = 0x20;
                do {
                    uint32_t *ap = (uint32_t *)(abase + (uint64_t)k * 0x40);
                    wfield(ctrl, i, k << 6 | 8, ap[2], 0xfffffffc);
                    wfield(ctrl, i, k << 6 | 0xc, ap[3], 0xf);
                    wfield(ctrl, i, k << 6 | 0x10, ap[4], 0xfffffffc);
                    wfield(ctrl, i, k << 6 | 0x14, ap[5], 0xf);
                    uint32_t nw = (*(uint32_t *)(ctrl + 0xb98) + 0x1f) >> 5;
                    uint32_t w2 = 0;
                    uint64_t wi = 0;
                    uint32_t i2 = ireg;
                    do {
                        wfield(ctrl, i, i2,
                               *(uint64_t *)(ap + (wi & 0x3ffffffffffffffe) + 6) >> (w2 & 0x20),
                               0xffff);
                        w2 += 1; wi += 0x20; i2 += 4;
                    } while (w2 < nw);
                    wfield(ctrl, i, k << 6, ap[0], 0x333);
                    k++;
                    ireg += 0x40;
                } while (k < na);
            }

            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
            uint8_t *hw2 = *instp;
            *(uint32_t *)(hw2 + (*(uint32_t *)(ctrl + 0xbc4) & 0xfffffffc)) = 0;
            if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
            if ((*(uint8_t *)(ctrl + 0xbe5) & 1) != 0) {
                *(uint32_t *)(hw2 + 0x760) = *(uint32_t *)(instp[0xb]);
                if ((*(uint32_t *)(ctrl + 0xba4) <= i) ||
                    (*(uint32_t *)(hw2 + 0x764) = *(uint32_t *)(instp + 0x5c),
                     *(uint32_t *)(ctrl + 0xba4) <= i)) goto invalid_dar;
                *(uint32_t *)(hw2 + 0x768) = *(uint32_t *)(instp + 0x54);
                if ((*(uint32_t *)(ctrl + 0xba4) <= i) ||
                    ((*(uint32_t *)(hw2 + 0x770) = *(uint32_t *)(instp + 0x64),
                      *(uint32_t *)(ctrl + 0xba4) <= i))) goto invalid_dar;
                *(uint32_t *)(hw2 + 0x774) = *(uint32_t *)(instp[0xd]);
                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                *(uint32_t *)(hw2 + 0x778) = *(uint32_t *)(instp[0xc]);
                if ((DART_VERSION(ctrl) & 0xfffe) != 0x100) {
                    if ((*(uint32_t *)(ctrl + 0xba4) <= i) ||
                        (*(uint32_t *)(hw2 + 0x780) = *(uint32_t *)(instp[0xe]),
                         *(uint32_t *)(ctrl + 0xba4) <= i)) goto invalid_dar;
                    *(uint32_t *)(hw2 + 0x784) = *(uint32_t *)(instp + 0x74);
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    *(uint32_t *)(hw2 + 0x788) = *(uint32_t *)(instp + 0x6c);
                }
                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                *(uint32_t *)(hw2 + (*(uint32_t *)(ctrl + 0xbc8) & 0xfffffffc)) = 0xffffffff;
                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                *(uint32_t *)(hw2 + (*(uint32_t *)(ctrl + 0xbcc) & 0xfffffffc)) = 0xffffffff;
                uint32_t off = *(uint32_t *)(ctrl + 0xbd0);
                uint32_t *src = (uint32_t *)(ctrl + 0xa38);
                do {
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    *(uint32_t *)(hw2 + (off & 0xfffffffc)) = *src;
                    off += 4;
                    src++;
                } while (src < (uint32_t *)(ctrl + 0xa38 + ((*(uint32_t *)(ctrl + 0xba0) >> 3) & 0x1ffffffc)));
            }
            if (*(uint32_t *)(ctrl + 0xb98) != 0) {
                uint32_t k = 0;
                do {
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    *(uint32_t *)(hw2 + 0xc00 + (uint64_t)k * 4) = *(uint32_t *)(ctrl + 0x34 + (uint64_t)k * 4);
                    k++;
                } while (k < ((*(uint32_t *)(ctrl + 0xb98) + 0x1f) >> 5));
            }
            i++;
        } while (i < *(uint32_t *)(ctrl + 0xba4));
    }
    *(uint8_t *)(ctrl + 0xbe0) = 3;
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) == sptm_uat_guard(cb)) {
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");

invalid_dar:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
invalid_pio:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_PIO_00009beb");
null_ptr:
    sptm_assert_fail("__s__dart__s__s__d___s____NULL_000063ee");
guard_conflict:
    sptm_panic(0x6000026, 0, "__s__s__d_____s___llx____s___llx__000112f5");
invalid_ps_wr:
    sptm_assert_fail("__s__dart__s__s__d__Invalid_ps_wr_00009efd");
ps_overflow:
    sptm_assert_fail("__s__dart__s__s__d__ps_refcount_o_00009f25");
guard_mismatch:
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* The stream-allocation bitmap is at ctrl+0xa38. */
static inline uint64_t *bitmap_ctrl(uint8_t *ctrl) { return (uint64_t *)(ctrl + 0xa38); }

/* FUN_000cc5e8 @ 0x000cc5e8   (est. sptm_t8110dart_disable_clock_protection;
 *   also aliased sptm_t8110dart_powerdown)
 * Ghidra: void FUN_000cc5e8(byte param_1, ulong param_2)
 * Disables DART clock protection (powerdown): pops the per-stream page-size
 * reference counts, clears the translation-window page-size registers, and
 * restores the instance state. Guarded by the same per-CPU mechanism as
 * enable, mirrored (increment vs decrement). param_2 bit0 selects whether the
 * per-instance translation is also disabled.
 * SECURITY: mirrors enable; the ps_wr refcount must reach exactly 0.
 * Confidence: high */
void sptm_t8110dart_disable_clock_protection(uint8_t dart_id, uint64_t flags)
{
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, flags, "__s__s__d_____s___llx__00011410");
    }
    uint64_t dbg;
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(sptm_dart_id_map[dart_id], &dbg);
    uint8_t *ctrl = percpu + 0x10;
    uint64_t cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) != 0) {
        sptm_panic(0x6000000, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *DART_GUARD(ctrl) = sptm_uat_guard(cb);

    if (*(uint8_t *)(ctrl + 0xbe0) == 3) {
        if ((*(uint8_t *)(ctrl + 0xbf5) & 1) != 0) {
            sptm_assert_fail("__s__dart__p___s__u___power_down_n_00007399");
        }
        if (*(uint32_t *)(ctrl + 0xba4) != 0) {
            uint32_t i = 0;
            uint64_t save_off = 0x34;   /* ctrl + 0x34 stream-enable staging */
            uint64_t pio_arr = 0x28;
            uint64_t *bitmap = (uint64_t *)(ctrl + 0xa38);
            do {
                uint8_t **instp = (uint8_t **)(ctrl + 8 + (uint64_t)i * 0x78);
                uint8_t *hw = *instp;
                *(uint32_t *)(hw + (*(uint32_t *)(ctrl + 0xbc4) & 0xfffffffc)) = 0xffffffff;
                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                sptm_dart_save(ctrl, i);
                if ((*(uint8_t *)(ctrl + 0xbe5) & 1) != 0) {
                    if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                    *(uint32_t *)(instp[0xb]) = *(uint32_t *)(hw + 0x760);
                    *(uint32_t *)(instp + 0x5c) = *(uint32_t *)(hw + 0x764);
                    *(uint32_t *)(instp + 0x54) = *(uint32_t *)(hw + 0x768);
                    *(uint32_t *)(instp + 0x64) = *(uint32_t *)(hw + 0x770);
                    *(uint32_t *)(instp[0xd]) = *(uint32_t *)(hw + 0x774);
                    *(uint32_t *)(instp[0xc]) = *(uint32_t *)(hw + 0x778);
                    if ((DART_VERSION(ctrl) & 0xfffe) != 0x100) {
                        *(uint32_t *)(instp[0xe]) = *(uint32_t *)(hw + 0x780);
                        *(uint32_t *)(instp + 0x74) = *(uint32_t *)(hw + 0x784);
                        *(uint32_t *)(instp + 0x6c) = *(uint32_t *)(hw + 0x788);
                    }
                    *(uint32_t *)(hw + (*(uint32_t *)(ctrl + 0xbcc) & 0xfffffffc)) = 0;
                }
                uint32_t nword = 0, stream_en;
                uint8_t be3, be4;
                if (*(uint32_t *)(ctrl + 0xb98) == 0) {
                    nword = 0; stream_en = 0;
                    if ((flags & 1) == 0) {
                        be4 = 0; be3 = *(uint8_t *)(ctrl + 0xbe3);
                        goto disable_streams;
                    }
                    be4 = *(uint8_t *)(ctrl + 0xbe4);
                    be3 = *(uint8_t *)(ctrl + 0xbe3);
                    nword = stream_en;
                } else {
                    uint64_t w = 0;
                    do {
                        if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                        *(uint32_t *)(ctrl + 0x34 + w * 4) = *(uint32_t *)(hw + w * 4 + 0xc00);
                        w++;
                        stream_en = *(uint32_t *)(ctrl + 0xb98);
                    } while (w < ((uint64_t)stream_en + 0x1f) >> 5);
                    nword = stream_en;
                    if ((flags & 1) != 0) {
                        be4 = *(uint8_t *)(ctrl + 0xbe4);
                        be3 = *(uint8_t *)(ctrl + 0xbe3);
                    } else {
disable_streams:
                        be3 = *(uint8_t *)(ctrl + 0xbe3);
                        be4 = 0;
                    }
                }
                (void)nword;
                if (((be3 & 1) == 0) && ((be4 & 1) == 0)) {
                    /* Disable translation on every active stream of this instance. */
                    int st = sptm_next_stream(bitmap, 0, *(uint32_t *)(ctrl + 0xb98));
                    if (st < (int)stream_en) {
                        do {
                            sptm_dsb(3, 3, 0);
                            uint8_t *slice = *(uint8_t **)(ctrl + 0x238 + (uint64_t)(st & 0xff) * 8);
                            if ((*(uint8_t *)(slice + 0x18) & 1) != 0) {
                                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                                *(uint32_t *)(hw + (uint64_t)(st >> 5 & 7) * 4 + 0xc20) = 1 << (st & 0x1f);
                                if (*(uint32_t *)(ctrl + 0xba4) <= i) goto invalid_dar;
                            }
                            if (0xfe < st) goto flush;
                            st = sptm_next_stream(bitmap, st + 1, stream_en);
                        } while (st < (int)stream_en);
                    }
                }
flush:
                /* Flush the DART. */
                uint64_t fdesc[3];
                fdesc[0] = 0; fdesc[1] = 0;
                fdesc[2] = (DART_VERSION(ctrl) < 0x202) ? 0x2000 : 0xa000;
                if (*(uint8_t *)(ctrl + 0xbe0) != 2) {
                    sptm_lock_acquire();
                    uint16_t s = *(uint16_t *)(ctrl + 0xc2c);
                    *(uint16_t *)(ctrl + 0xc2c) = (uint16_t)(s | 1);
                    sptm_lock_release();
                    if ((s & 1) != 0) {
                        sptm_assert_fail("__s__dart__p___s__u___Not_seriali_0000a5ac");
                    }
                    sptm_memcpy(ctrl + 0xbfc, fdesc, 0x18);
                }
                int rc;
                do { rc = sptm_dart_poll(ctrl, 0); } while (rc == 0);

                if ((be3 & 1) == 0) {
                    if (sptm_ps_wr_mode == 1) {
                        uint8_t old_guard = sptm_ps_wr_guard;
                        uint8_t ps_idx;
                        if (*(uint8_t *)(instp + 0x2a / 8 + 0) == 0 && 0) { }
                        /* Pop ps_wr refcount (field A at instrow+0x28). */
                        uint8_t *instrow = ctrl + 8 + (uint64_t)i * 0x78;
                        ps_idx = *(uint8_t *)(instrow + 0x28);
                        if (*(uint8_t *)(instrow + 0x2a) != 0) { /* skip */ }
                        else if (ps_idx != 0xff) {
                            cb = sptm_cpu_base();
                            uint8_t g = sptm_uat_guard(cb);
                            if (sptm_ps_wr_guard != 0) goto guard_conflict;
                            sptm_ps_wr_guard = g;
                            if (sptm_ps_wr_table == NULL) goto null_ptr;
                            if (sptm_ps_wr_max < ps_idx || sptm_ps_wr_max == ps_idx) goto invalid_ps_wr;
                            char c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                            if (c == 0) goto ps_underflow;
                            sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4] = (char)(c - 1);
                            if (c == 1) {
                                sptm_dart_ps_refcount(ctrl, ps_idx, 0);
                            }
                            cb = sptm_cpu_base();
                            if (sptm_ps_wr_guard != sptm_uat_guard(cb)) goto guard_mismatch;
                            sptm_ps_wr_guard = 0;
                            if (*(uint8_t *)(instrow + 0x2a) == 0) goto done_pop_a;
                        }
                        /* Pop ps_wr refcount (field B at instrow+0x29). */
                        ps_idx = *(uint8_t *)(instrow + 0x29);
                        if (ps_idx != 0xff) {
                            cb = sptm_cpu_base();
                            uint8_t g = sptm_uat_guard(cb);
                            if (sptm_ps_wr_guard != 0) goto guard_conflict;
                            sptm_ps_wr_guard = g;
                            if (sptm_ps_wr_table == NULL) goto null_ptr;
                            if (sptm_ps_wr_max < ps_idx || sptm_ps_wr_max == ps_idx) goto invalid_ps_wr;
                            char c = sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4];
                            if (c == 0) goto ps_underflow;
                            sptm_ps_wr_table[(uint64_t)ps_idx * 6 + 4] = (char)(c - 1);
                            if (c == 1) {
                                sptm_dart_ps_refcount(ctrl, ps_idx, 0);
                            }
                            cb = sptm_cpu_base();
                            if (sptm_ps_wr_guard != sptm_uat_guard(cb)) goto guard_mismatch;
                        }
done_pop_a:
                        sptm_ps_wr_guard = old_guard;
                        *(uint8_t *)(ctrl + 0x32 + (uint64_t)i * 0x78) = 0;
                    } else if ((sptm_alt_dart_mode & 1) == 0) {
                        if (*(uint64_t *)(ctrl + 0x1e8) != 0) {
                            sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009dad");
                        }
                    } else {
                        /* Alt mode: pop the PIO region refcount. */
                        if (((*(uint8_t *)(ctrl + 0xbf7) & 1) == 0) ||
                            (*(int16_t *)(sptm_dart_slice_table +
                                          (uint64_t)*(uint8_t *)(ctrl + 0xbfb) * 0x10 + 0xe) - 1 == 0)) {
                            if (*(uint32_t *)(ctrl + 0xba8) != 0) {
                                uint32_t m = 0;
                                uint64_t poff = 0x1f0;
                                do {
                                    uint32_t pio_idx = *(uint32_t *)(ctrl + pio_arr + (uint64_t)i * 0x78 + m * 4);
                                    if ((pio_idx == 0) || (*(uint32_t *)(ctrl + poff) <= pio_idx)) {
                                        sptm_assert_fail("__s__dart__p___s__u___Invalid___s_00008bbc");
                                    }
                                    uint8_t *pio2 = *(uint8_t **)(ctrl + poff - 8);
                                    if (pio2 == NULL) goto null_ptr;
                                    uint32_t woff = (pio_idx * 0x40 + 0x100) >> 2;
                                    uint32_t w = *(uint32_t *)(pio2 + (uint64_t)woff * 4);
                                    if (((w >> 1 & 1) == 0) || ((w >> 4 & 1) == 0)) {
                                        sptm_assert_fail("__s__dart__p___s__u___Inconsisten_00009e6e");
                                    }
                                    *(uint32_t *)(pio2 + (uint64_t)woff * 4) = w & 0xffffffef;
                                    if (*(uint64_t *)(ctrl + 0xc38) != 0) {
                                        *(uint32_t *)(*(uint64_t *)(ctrl + 0xc38) +
                                                      (uint64_t)*(uint32_t *)(ctrl + 0x28 + (uint64_t)i * 0x78) * 4) = w & 0xffffffef;
                                        sptm_dmb(2, 3);
                                    }
                                    m++;
                                    poff += 0x10;
                                } while (m < *(uint32_t *)(ctrl + 0xba8));
                            }
                        }
                    }
                }
                i++;
                save_off += 0x78;
                pio_arr += 0x78;
            } while (i < *(uint32_t *)(ctrl + 0xba4));
        }
        if (((*(uint8_t *)(ctrl + 0xbe3) & 1) == 0) &&
            (((flags & 1) == 0) || ((*(uint8_t *)(ctrl + 0xbe4) & 1) == 0))) {
            /* Finalize the PIO descriptors. */
            uint32_t npio = *(uint32_t *)(ctrl + 0xbb0);
            if (npio != 0) {
                uint32_t k = 0;
                do {
                    uint8_t *pio = *(uint8_t **)(ctrl + 0x208 + (uint64_t)k * 0x10);
                    if (pio == NULL) goto null_ptr;
                    if ((*(uint32_t *)(pio + 0x10) == 0 && *(uint32_t *)(pio + 0xc) == 0) &&
                        (*(uint32_t *)(ctrl + 0xbb4) != 0)) {
                        uint32_t m = 0;
                        uint64_t r = 0xb58;
                        do {
                            if (*(uint32_t *)(ctrl + 0xbb0) <= k) goto invalid_pio;
                            *(uint32_t *)(pio + ((uint32_t)(*(int32_t *)(ctrl + r)) * 0x20 + 0x1120)) = 0;
                            m++;
                            r += 0xc;
                        } while (m < *(uint32_t *)(ctrl + 0xbb4));
                        npio = *(uint32_t *)(ctrl + 0xbb0);
                    }
                    k++;
                } while (k < npio);
            }
            *(uint8_t *)(ctrl + 0xbe0) = 2;
        }
    }
    cb = sptm_cpu_base();
    if (*DART_GUARD(ctrl) == sptm_uat_guard(cb)) {
        *DART_GUARD(ctrl) = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");

invalid_dar:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_DAR_00007544");
invalid_pio:
    sptm_assert_fail("__s__dart__p___s__u___Invalid_PIO_00009beb");
null_ptr:
    sptm_assert_fail("__s__dart__s__s__d___s____NULL_000063ee");
guard_conflict:
    sptm_panic(0x6000026, 0, "__s__s__d_____s___llx____s___llx__000112f5");
invalid_ps_wr:
    sptm_assert_fail("__s__dart__s__s__d__Invalid_ps_wr_00009efd");
ps_underflow:
    sptm_assert_fail("__s__dart__s__s__d__ps_refcount_u_0000a303");
guard_mismatch:
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
}

/* FUN_000ce144 @ 0x000ce144   (est. sptm_t8110dart_map)
 * Ghidra: void FUN_000ce144(byte param_1, ulong param_2, ulong param_3,
 *                           ulong param_4, ulong param_5, ulong param_6)
 * Maps a guest physical range into the DART: validates the IO virtual address
 * range and attributes, then programs the translation-table entries for each
 * 16 KiB page, locking the backing pages. param_2 = stream, param_3 = iova,
 * param_4 = guest paddr, param_5 = size, param_6 = memattr.
 * SECURITY: rejects out-of-range / non-canonical iova and mismatched PTE
 *   attributes; verifies the backing page type is consistent with the IO
 *   window before locking.
 * Confidence: high */
void sptm_t8110dart_map(uint8_t dart_id, uint64_t stream, uint64_t iova,
                        uint64_t guest_paddr, uint64_t size, uint64_t memattr)
{
    uint64_t dbg;
    if (sptm_dart_id_map[dart_id] == -1) {
        sptm_panic(0x6000006, 0, "__s__s__d_____s___llx__00011410");
    }
    uint8_t *percpu = (uint8_t *)sptm_percpu_base(0, &dbg);
    uint8_t *ctrl = percpu + 0x10;
    if (0xf < memattr) {
        sptm_panic(0x600000d, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (*(uint8_t *)(ctrl + 0xbe0) == 0) {
        sptm_panic(0x6000016, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    uint32_t st = (uint32_t)stream & 0xff;
    uint64_t ok;
    if ((*(uint8_t *)(ctrl + 0xbf1) & 1) != 0) {
        ok = sptm_dart_acquire_v2(ctrl, st, &dbg);
    } else {
        ok = sptm_dart_acquire_v1(ctrl, st, &dbg);
    }
    if ((ok & 1) == 0) {
        sptm_panic(0x6000009, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if ((st < *(uint32_t *)(ctrl + 0xb98)) &&
        ((uint64_t)slice = (uint64_t)*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238), slice != 0) &&
        ((*(uint8_t *)(slice + 0x1d) & 1) != 0)) {
        sptm_panic(0x600001f, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    if (0x2000000 < size) {
        sptm_panic(0x600000c, dbg, "__s__s__d_____s___llx__00011410");
    }
    if ((7 < memattr) && ((*(uint8_t *)(ctrl + 0xbef) & 1) == 0)) {
        sptm_panic(0x6000013, dbg, "__s__s__d_____s___llx____s___llx__00011690");
    }
    uint64_t cb = sptm_cpu_base();
    uint8_t *guard = (uint8_t *)(*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238) + 0x1f);
    if (*guard != 0) {
        sptm_panic(0x6000001, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    *guard = sptm_uat_guard(cb);

    if (iova >> 0x2a != 0) {
        sptm_panic(0x6000021, dbg, "__s__s__d_____s___llx__00011410");
    }
    uint8_t *slice = *(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238);
    uint32_t pg = (uint32_t)(iova >> 0xe);
    if (((pg < *(uint32_t *)(slice + 0x14)) || (*(uint32_t *)(slice + 0x10) <= pg)) &&
        ((*(uint8_t *)(ctrl + 0xbec) & 1) == 0)) {
        sptm_panic(0x600000e, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    uint64_t end = iova + size;
    if (end >> 0x2a != 0) {
        sptm_panic(0x6000021, dbg, "__s__s__d_____s___llx__00011410");
    }
    uint32_t pg_end = (uint32_t)(end >> 0xe);
    if (((pg_end < *(uint32_t *)(slice + 0x14)) || (*(uint32_t *)(slice + 0x10) <= pg_end)) &&
        ((*(uint8_t *)(ctrl + 0xbec) & 1) == 0)) {
        sptm_panic(0x600000e, dbg, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    if ((iova & 0x3fffe000000) + 0x2000000 < end) {
        sptm_panic(0x600000f, dbg, "__s__s__d_____s___llx____s___llx__000111dc");
    }
    uint32_t scratch = ((uint32_t)size + 0x3fff + ((uint32_t)iova & 0x3fff)) >> 0xb & 0x1fff8;
    if (0x4000 < scratch) {
        sptm_assert_fail("__s__dart__p___s__u___The_scratch_0000728c");
    }
    if ((guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr) ||
        (guest_paddr < sptm_guest_mem_start || sptm_guest_mem_end <= guest_paddr)) {
        sptm_panic(6, scratch, "__s__s__d_____s___llx____s___llx__000112f5");
    }
    uint64_t *win = (uint64_t *)sptm_dart_pte_lookup(guest_paddr, scratch, 1, 0);

    uint64_t local = 0;
    uint64_t tt_dbg;
    uint8_t *tt = (uint8_t *)sptm_dart_tt_lookup(ctrl, st, iova, &local);
    tt_dbg = 0;

    uint64_t *range = *(uint64_t **)(*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238) + 8);
    if ((range == NULL) || (local < range[0]) || (range[1] <= local)) {
        sptm_kernel_ref(local, 0x44);
    }

    int sp_count = 0;
    if (iova < end) {
        uint32_t tmp = ((uint32_t)memattr & 0xaaaaaaaa) >> 1 | ((uint32_t)memattr & 0x55555555) << 1;
        uint32_t att = ((tmp & 0xcccccccc) >> 2 | (tmp & 0x33333333) << 2) & 0xf;
        uint32_t prev_attr = 0xffffffff;
        int mapped = 0;
        int changed = 0;
        uint64_t cur_iova = iova;
        uint64_t *w = win;
        do {
            uint64_t pa = *w;
            uint16_t *meta;
            if (pa < sptm_guest_mem_start || sptm_guest_mem_end <= pa) {
                uint64_t d2;
                meta = (uint16_t *)sptm_phys_lookup(pa, &d2);
            } else {
                meta = (uint16_t *)(sptm_guest_meta_base + ((pa - sptm_guest_mem_start) >> 10 & 0xffffffff0));
            }
            char ptype = *(char *)(meta + 1);

            int in_dart = (*(uint64_t *)(ctrl + 0xb88) <= cur_iova) && (cur_iova < *(uint64_t *)(ctrl + 0xb90));
            if (ptype == '=') {
                if ((*(uint8_t *)(ctrl + 0xbf6) & 1) == 0) goto bad_type;
            }
            if (in_dart && ((*(uint8_t *)(ctrl + 0xbfa) & 1) == 0)) goto bad_type;
            if (ptype == '=') {
                if ((!in_dart) && ((*(uint8_t *)(ctrl + 0xbf9) & 1) != 0)) goto bad_type;
                if (7 < memattr) {
                    sptm_panic(0x6000013, dbg, "__s__s__d_____s___llx____s___llx__00011690");
                }
            } else if (in_dart && ((*(uint8_t *)(ctrl + 0xbf9) & 1) != 0)) {
                goto bad_type;
            }

            if (*(uint64_t *)(ctrl + 0xb80) == 0) {
                if (0x3ffffffffff < pa) goto bad_va;
            } else if (*(uint64_t *)(ctrl + 0xb80) <= pa) {
bad_va:
                sptm_panic(0x6000021, dbg, "__s__s__d_____s___llx__00011410");
            }
            uint64_t idx = (cur_iova >> 0xe) & 0x7ff;
            uint64_t newpte = (uint64_t)att | (cur_iova >> 2) << 0x34 | (pa >> 4) & 0x3ffffffc00;
            uint64_t chunk = 0x4000 - (cur_iova & 0x3fff);
            uint64_t rem = end - cur_iova;
            if (chunk + cur_iova <= end) { rem = chunk; }
            uint64_t entry = newpte | 0xfff0000000001;
            if (rem >> 0xe == 0) {
                entry = ((uint64_t)((int32_t)((int32_t)rem + (int32_t)cur_iova) << 0x26) +
                         0xfffc000000000 & 0xfff0000000000) | newpte | 1;
            }
            uint64_t old = *(uint64_t *)(tt + idx * 8);
            if ((old & 1) == 0) {
                sp_count++;
                uint32_t pa_attr = prev_attr;
lock_same:
                uint32_t t = 1;
                if ((entry & 4) == 0) t = 2;
                sptm_phys_lock(pa, t);
                prev_attr = pa_attr;
            } else {
                if (((old ^ entry) & 0x3ffffffc00) != 0) {
                    if ((memattr < 8) || (((uint32_t)old >> 2 & 1) == 0)) goto attr_mismatch;
                    uint64_t oldpa = (old & 0x3ffffffc00) * 0x10;
                    if ((*(uint8_t *)(ctrl + 0xbf0) & 1) != 0) {
                        uint16_t *m2;
                        if (oldpa < sptm_guest_mem_start || sptm_guest_mem_end <= oldpa) {
                            uint64_t d3;
                            m2 = (uint16_t *)sptm_phys_lookup(oldpa, &d3);
                        } else {
                            m2 = (uint16_t *)(sptm_guest_meta_base + ((oldpa - sptm_guest_mem_start) >> 10 & 0xfffffff0));
                        }
                        if (*(char *)(m2 + 1) != 0x1a) goto attr_mismatch;
                    }
                    win[mapped] = oldpa;
                    uint32_t old_t = (uint32_t)(*(uint64_t *)(tt + idx * 8) >> 2) & 1;
                    mapped++;
                    if ((prev_attr != 0xffffffff) && (prev_attr != old_t)) {
                        sptm_panic(0x6000014, dbg, "__s__s__d_____s___llx____s___llx__00011254");
                    }
                    goto lock_same;
                }
                if (entry != old) {
attr_mismatch:
                    sptm_panic(0x6000023, dbg, "__s__s__d_____s___llx____s___llx__00011452");
                }
            }
            changed |= (entry != old);
            *(uint64_t *)(tt + idx * 8) = entry;
            cur_iova = rem + cur_iova;
            w++;
        } while (cur_iova < end);

        uint32_t t = 1;
        if (prev_attr == 0) t = 2;
        sptm_dsb(3, 3, 0);
        if (!(7 < memattr || (changed ^ 1) == 0)) {
            if (((end + 0x3fff >> 0x2a & 1) != 0)) {
                sptm_panic(0x6000021, dbg, "__s__s__d_____s___llx__00011410");
            }
            sptm_dart_tlb_flush(ctrl, st, iova >> 0xe, (uint32_t)(end + 0x3fff >> 0xe) - 1, 0);
        }
        for (; mapped != 0; mapped--) {
            sptm_phys_unlock(*win, t);
            win++;
        }
    } else {
        sptm_dsb(3, 3, 0);
    }

    /* Release the per-range refcount once all pages are processed. */
    uint64_t *range2 = *(uint64_t **)(*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238) + 8);
    if ((range2 == NULL) || (local < range2[0]) || (range2[1] <= local)) {
        sptm_kernel_ref_add(local, sp_count);
        range2 = *(uint64_t **)(*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238) + 8);
        if (range2 != NULL && range2[0] <= local && local < range2[1]) {
            goto guard_release;
        }
    }
    sptm_kernel_unref(local);
guard_release:
    cb = sptm_cpu_base();
    guard = (uint8_t *)(*(uint8_t **)(ctrl + (uint64_t)st * 8 + 0x238) + 0x1f);
    if (*guard == sptm_uat_guard(cb)) {
        *guard = 0;
        return;
    }
    sptm_assert_fail("__s__state_guard_release_____llx__0000720b");
bad_type:
    sptm_panic(0x6000023, dbg, "__s__s__d_____s___llx____s___llx__000111dc");
}

