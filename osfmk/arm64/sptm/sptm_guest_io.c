/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM guest VCPU dispatch path (sptm_guest_enter,
 * sptm_guest_exit, sptm_guest_dispatch, sptm_guest_va_to_ipa,
 * sptm_guest_stage1_tlb_op) and the IOMMU drivers (NVMe TCB mapping,
 * SART region unmapping, T8110 DART table management, and the UAT
 * unification table driver).
 *
 * The GENTER/GEXIT guarded-level transitions are rendered as opaque calls
 * (opcode 0x00201420 / 0x00201400); the selector in x16 selects the dispatch
 * endpoint per sptm_common.h (SPTM_LOAD_DISPATCH_ID).
 *
 * Shared SPTM-internal helpers called from these bodies are declared extern
 * with a one-line note giving their Ghidra address and estimated purpose.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * Shared helper declarations (SPTM-internal, outside this batch).
 * Each carries its Ghidra FUN_ address and an estimated role.
 * ------------------------------------------------------------------ */

/* FUN_000f8844 — noreturn SPTM panic: panic(err, val, fmt). */
extern void sptm_panic(uint32_t err, uint64_t val, const char *fmt) __attribute__((noreturn));
/* FUN_000f8804 — noreturn SPTM panic taking only a format string. */
extern void sptm_panic_str(const char *fmt) __attribute__((noreturn));

/* FUN_000f61c0 — acquire (LO refcount) the per-CPU guest VCPU state FTE,
 * returning its virtual address. */
extern void *sptm_guest_state_acquire(void);

/* FUN_000e3d7c — translate a physical address to its SPTM virtual address. */
extern void *sptm_phystokv(uint64_t paddr);
/* FUN_000e2480 — look up and acquire (LO ref) the FTE for a physical
 * address, validating it is shared. */
extern void *sptm_fte_acquire(uint64_t paddr);
/* FUN_000e260c — release an FTE reference (acquired by sptm_fte_acquire). */
extern void sptm_fte_release(void *fte);
/* FUN_000d81bc — translate an SPTM virtual address to physical. */
extern uint64_t sptm_va_to_pa(const void *va);
/* DAT_00096381 — global current-context type indicator (UAT ctx type). */
extern uint8_t sptm_ctx_global_type; /* DAT_00096381 */
/* FUN_000d8a58 — reverse translation: physical address of an SPTM-owned VA. */
extern uint64_t sptm_kvtophys(const void *va);
/* FUN_000e40ec — translate a physical address to VA when it is outside the
 * linear EL2 window (page-table-walk lookup). */
extern void *sptm_phystokv_outside_window(uint64_t paddr);

/* FUN_000d617c — validate a physical range (elem_size * num_elems) is within
 * a scratch page and copy it into the per-CPU handoff scratch region at
 * `offset`; returns the scratch VA. */
extern void *sptm_copy_to_scratch(uint64_t paddr, long elem_size, long num_elems, long offset);

/* FUN_000e53d8 — paddr refcount adjust: count==1 acquire, count==0xffffffff
 * release; returns 0 on success. */
extern int sptm_paddr_ref(uint64_t paddr, uint32_t count);
/* FUN_000e5090 — release/LO-unref a physical address (with refcount). */
extern void sptm_paddr_release(uint64_t paddr);
/* FUN_000e4e74 — validate a physical address + length, returning its FTE/VA
 * (faults if not mappable). */
extern void *sptm_paddr_validate(uint64_t paddr, uint64_t size);

/* FUN_000e56ac — take an IOMMU page reference for `type` (1=4KB, 2=2MB). */
extern void sptm_iommu_page_ref(uint64_t paddr, uint32_t type);
/* FUN_000e5c80 — release an IOMMU page reference for `type`. */
extern void sptm_iommu_page_unref(uint64_t paddr, uint32_t type);

/* FUN_000abeb0 (thunk) — memcpy. */
extern void sptm_memcpy(void *dst, const void *src, uint64_t n);
/* FUN_000ae3e0 — memset. */
extern void sptm_memset(void *dst, uint64_t n, uint64_t value);
/* FUN_000ab9e0 — data-cache clean/invalidate of a range. */
extern void sptm_dcache_clean_invalidate(uint64_t va, uint64_t size);
/* FUN_000ae44c — stack canary / BTI check on function exit. */
extern void sptm_stack_check(void);

/* FUN_000a28fc — clear the per-CPU handoff region (guest_dispatch epilogue). */
extern void sptm_handoff_clear(void *handoff, int flag);

/* --- SART driver helpers --- */
/* FUN_000c60e4 — validate/unpack a SART region request (paddr,size → va). */
extern void sptm_sart_validate_region(uint64_t paddr, uint64_t size,
                                      uint64_t *out_va, uint64_t *out_paddr);
/* FUN_000c6364 — look up a SART region by id, returning its offsets. */
extern void sptm_sart_region_lookup(uint32_t id, uint32_t *out0, int *out1, int *out2);

/* --- T8110 DART driver helpers --- */
/* FUN_000e4d78 — get the per-CPU DART driver state (returns state, err in x1). */
extern void *sptm_dart_state_get(void);
/* FUN_000c9364 / FUN_000c92e8 — look up a DART client instance by id. */
extern void *sptm_dart_instance_lookup(void *state, uint8_t instance);
/* FUN_000cf7a8 — update a DART PTE reference for a client. */
extern void sptm_dart_pte_ref_update(void *state, uint8_t instance, uint64_t paddr, int count);
/* FUN_000cd970 — walk DART tables for a VA; returns leaf-pte ptr + leaf paddr. */
extern void *sptm_dart_va_to_pte(void *state, uint8_t instance, uint64_t va, uint64_t *out_paddr);
/* FUN_000cdd0c — DART TLB/table invalidate over a VA range. */
extern void sptm_dart_tlb_invalidate(void *state, uint8_t instance,
                                     uint64_t va_start_shift14, int va_end_shift14, int clear);
/* FUN_000c7bac — DART per-client TLB invalidate. */
extern void sptm_dart_client_tlb_invalidate(void *state, uint8_t client, int a, int b);

/* --- UAT driver helpers --- */
/* FUN_000c5248 — get/acquire the UAT state by id (mode 0/2/5, mask). */
extern void *sptm_uat_state_get(uint64_t id, int mode, int mask);
/* FUN_000c55cc — validate/translate a UAT table physical address (type). */
extern uint64_t sptm_uat_table_translate(uint64_t paddr, int type);
/* FUN_000c5784 — walk UAT tables for a VA, returning its offset and count. */
extern void sptm_uat_va_walk(uint64_t va, uint64_t size, uint8_t *state, uint64_t *out_off);
/* FUN_000b3b34 — UAT walk returning the leaf table entry ptr for a VA. */
extern void *sptm_uat_walk_entry(uint64_t root_paddr, uint64_t va, char level, long *out_entry_va);
/* FUN_000b2d40 — UAT TLB invalidate / flush over a range. */
extern void sptm_uat_tlb_invalidate(uint8_t *state, uint64_t va, uint64_t size, int flag);
/* FUN_000b3adc — UAT table teardown/cleanup helper. */
extern void sptm_uat_cleanup(uint8_t *state, int flag);
/* FUN_000b3600 — UAT unmap walker (walks a table releasing entries). */
extern uint64_t sptm_uat_unmap_walk(uint8_t *state, long *out, void *callback);
/* FUN_000b37fc / FUN_000b3d90 — UAT unmap callback for leaf/table entries. */
extern void sptm_uat_unmap_cb_table(void);
extern void sptm_uat_unmap_cb_leaf(void);

/* --- Misc hardware accessors inlined below --- */
#define LOAcquire()   /* opaque SPTM lock acquire primitive */
#define LORelease()   /* opaque SPTM lock release primitive */

#define SPTM_CPU_REG()         __builtin_arm_rsr64("tpidr_el2")
#define SPTM_CPU_ID_ALT()      __builtin_arm_rsr64("tpidr_el2")

/* ------------------------------------------------------------------ *
 * Shared SPTM global state (Ghidra DAT_ symbols; addresses in comments).
 * ------------------------------------------------------------------ */

/* DAT_00095d18 / DAT_00095d20 — SPTM physical memory window [low, high). */
extern uint64_t sptm_mem_low;    /* DAT_00095d18 */
extern uint64_t sptm_mem_high;   /* DAT_00095d20 */
/* DAT_00095460 — base of the SPTM EL2 linear virtual window over physical mem. */
extern uint64_t sptm_window_base; /* DAT_00095460 */
/* DAT_00095110 — SPTM direct-map virtual base (paddr - mem_low + base). */
extern uint64_t sptm_direct_map_base; /* DAT_00095110 */
/* DAT_00101f90 — fixed "invalid FTE" virtual address. */
extern uint8_t sptm_invalid_fte[]; /* DAT_00101f90 */
/* DAT_00095d51 — per-FTE-class validity/type table (indexed by FTE type*0x90). */
extern uint8_t sptm_fte_class[];   /* DAT_00095d51 */
/* DAT_00095d83 / DAT_00095d84 — FTE shared/owned flag tables. */
extern uint8_t sptm_fte_shared[];  /* DAT_00095d83 */
extern uint8_t sptm_fte_shared2[]; /* DAT_00095d84 */
/* DAT_00095d00 / DAT_00095d02 — SPTM feature/config flags. */
extern uint64_t sptm_cfg_flags0;   /* DAT_00095d00 */
extern uint64_t sptm_cfg_flags1;   /* DAT_00095d02 */
/* DAT_00019c68 — per-CPU guest state array. */
extern uint64_t sptm_per_cpu_guest[]; /* DAT_00019c68 */

/* Per-CPU handoff region base (string anchor s_uat_instance_>handoff_region_). */
extern uint8_t sptm_handoff_region[]; /* s_uat_instance_>handoff_region_... */
/* Per-CPU "last VNCR / AVNCR physical address" slots
 * (s_sptm_uat_set_ctx_id_ anchor). */
extern uint8_t sptm_per_cpu_last_vncr[];  /* s_sptm_uat_set_ctx_id_... */

/* UAT driver state base (DAT_00095d08). */
extern uint8_t sptm_uat_driver_state[];   /* DAT_00095d08 */
/* NVMe driver state base (DAT_00094ab0). */
extern uint8_t sptm_nvme_state[];         /* DAT_00094ab0 */
/* SART driver state base (DAT_00094cc8). */
extern uint32_t sptm_sart_state[];        /* DAT_00094cc8 */
/* T8110 DART instance-validation table (DAT_00094ec0). */
extern uint8_t sptm_dart_valid_instances[]; /* DAT_00094ec0 */

/* DAT_001012d8 / DAT_00101ac8 / DAT_00101ad0 — memory-map feature and
 * translation descriptor table used when the EL2 window is not linear. */
extern uint32_t sptm_mem_feature;        /* DAT_001012d8 */
extern uint64_t sptm_region_count;       /* DAT_00101ac8 */
extern uint64_t sptm_regions[];          /* DAT_00101ad0 (3 words per region) */
/* DAT_000130d8 / DAT_000130f8 — per-level VA<->index shift/mask tables. */
extern uint64_t sptm_pt_shifts[];        /* DAT_000130d8 */
extern uint32_t sptm_pt_shifts_lo[];     /* DAT_000130f8 */
/* DAT_00095310 / DAT_00015d90 / DAT_00094319 / DAT_000952e8 — boot config. */
extern uint8_t sptm_boot_thing;          /* DAT_00094319 */
extern uint8_t sptm_sapt_bootstrapped;   /* DAT_000952e8 */
extern uint64_t sptm_boot_stage;         /* DAT_00095310 */
extern uint8_t sptm_boot_config_table[]; /* DAT_00015d90 (indexed by stage*0x28) */

/* ------------------------------------------------------------------ *
 * Per-CPU / handoff region offsets
 * ------------------------------------------------------------------ */

/* sptm_handoff_region + cpu + 0x1b  -> per-CPU handoff pointer (word). */
#define SPTM_HANDOFF_PTR_OFF 0x1b
/* sptm_per_cpu_last_vncr + cpu + 0x1  -> last VNCR paddr slot. */
#define SPTM_LAST_VNCR_OFF 0x1
/* sptm_per_cpu_last_vncr + cpu + 0x9  -> last AVNCR paddr slot. */
#define SPTM_LAST_AVNCR_OFF 0x9
/* sptm_uat_driver_state + 0x60 -> per-CPU UAT "ctx id in use" guard byte. */
#define SPTM_UAT_CTXID_GUARD 0x60

/* CPU id selector: reads the per-CPU id; tpidr_el2 is the fallback. This is
 * the (3,6,0xf,8,0)/(3,6,0xf,0xb,1)/tpidr_el2 pattern the decompiler shows. */
static inline uint64_t sptm_cpu_id(void) {
    uint64_t id = SPTM_CPU_REG();
    return (id != 0) ? id : SPTM_CPU_ID_ALT();
}

/* Translate a physical address to its SPTM virtual address, following the
 * decompiler's repeated pattern: in-window paddr -> direct map (or region
 * table when mem_feature bit 8 set); out-of-window paddr -> phystokv, falling
 * back to the fixed "invalid FTE" VA. */
static inline uint16_t *sptm_paddr_to_va(uint64_t p)
{
    if (p < sptm_mem_low || sptm_mem_high <= p) {
        void *rv = sptm_phystokv(p);
        return rv ? (uint16_t *)rv : (uint16_t *)sptm_invalid_fte;
    }
    if (((uint32_t)sptm_mem_feature >> 8 & 1) == 0) {
        return (uint16_t *)((p - sptm_mem_low) + sptm_direct_map_base);
    }
    uint64_t cnt = sptm_region_count;
    if (cnt != 0) {
        uint64_t *rg = sptm_regions;
        do {
            uint64_t base = rg[0];
            if (base <= p && p < base + (uint32_t)rg[2] * 0x4000) {
                return (uint16_t *)((p - base) + rg[1]);
            }
            cnt--;
            rg += 3;
        } while (cnt != 0);
    }
    return (uint16_t *)sptm_phystokv_outside_window(p);
}

/* ------------------------------------------------------------------ *
 * Per-CPU handoff / guest-state accessors
 * ------------------------------------------------------------------ */

/* Per-CPU handoff-region pointer (word at handoff_region + cpu + 0x1b). */
static inline uint64_t *sptm_handoff_ptr(void) {
    return *(uint64_t **)(sptm_handoff_region + sptm_cpu_id() + SPTM_HANDOFF_PTR_OFF);
}

/* Opaque SPTM sysreg accesses (decompiler's UnkSytemRegRead/Write). Rendered
 * with their (op0,op1,CRn,CRm,op2) encodings; register identities unknown. */
static inline uint64_t sptm_reg_read(uint64_t op0, uint64_t op1, uint64_t crn,
                                     uint64_t crm, uint64_t op2) {
    (void)op0; (void)op1; (void)crn; (void)crm; (void)op2;
    return 0; /* opaque SPTM sysreg read */
}
static inline void sptm_reg_write(uint64_t op0, uint64_t op1, uint64_t crn,
                                  uint64_t crm, uint64_t op2, uint64_t val) {
    (void)op0; (void)op1; (void)crn; (void)crm; (void)op2; (void)val;
    /* opaque SPTM sysreg write */
}

/* HCR/HACR/VTCR/VTTBR/TLBI are standard EL2 system registers. */
static inline void sptm_write_vtcr_el2(uint64_t v) { __builtin_arm_wsr64("vtcr_el2", v); }
static inline uint64_t sptm_read_vtcr_el2(void)      { return __builtin_arm_rsr64("vtcr_el2"); }
static inline void sptm_write_vttbr_el2(uint64_t v) { __builtin_arm_wsr64("vttbr_el2", v); }
static inline uint64_t sptm_read_vttbr_el2(void)    { return __builtin_arm_rsr64("vttbr_el2"); }
static inline void sptm_write_hcr_el2(uint64_t v)   { __builtin_arm_wsr64("hcr_el2", v); }
static inline uint64_t sptm_read_hcr_el2(void)      { return __builtin_arm_rsr64("hcr_el2"); }
static inline void sptm_write_hacr_el2(uint64_t v)  { __builtin_arm_wsr64("hacr_el2", v); }
static inline uint64_t sptm_read_par_el1(void)      { return __builtin_arm_rsr64("par_el1"); }
static inline void sptm_write_par_el1(uint64_t v)   { __builtin_arm_wsr64("par_el1", v); }

static inline void sptm_isb(void)  { __asm__ volatile("isb" ::: "memory"); }
static inline void sptm_dsb_sy(void) { __asm__ volatile("dsb sy" ::: "memory"); }
static inline void sptm_dmb_ish(void) { __asm__ volatile("dmb ish" ::: "memory"); }
static inline void sptm_dsb_ish(void) { __asm__ volatile("dsb ish" ::: "memory"); }
static inline void sptm_dmb_sy(void) { __asm__ volatile("dmb sy" ::: "memory"); }

/* ------------------------------------------------------------------ *
 * FUN_000f6368 @ 0x000f6368   (est. sptm_guest_enter)
 * Ghidra: undefined FUN_000f6368(void)
 * Program the EL2 translation registers and enter the guest VCPU. Validates
 * that interrupts are masked and the per-CPU guest state FTE is a valid
 * shared guest type; sets HCR_EL2/HACR_EL2/VTCR_EL2/VTTBR_EL2 from the state
 * and the caller-supplied configuration, bumps the nested-state refcount,
 * then releases the shared reference on the state (and, for a nested 0x12
 * state, its backing page). param_1 (dispatch_flags) is unused in the body.
 * Confidence: medium
 * Notes: hcr_el2 = (param_2 & 0xfffffffff7ffffff) | 0x400480000001; vttbr from
 *   (state_paddr - window_base)*0x400 | mem_low | vmid<<0x30. Refcount-overflow
 *   guard at 0x812. Opaque sysreg write (3,4,1,2,2) when cfg_flags1 bit 0 set.
 */
void sptm_guest_enter(uint64_t dispatch_flags, uint64_t hcr_flags, uint64_t sysreg_val,
                      uint64_t hacr_bits, uint64_t unused_word3)
{
    (void)dispatch_flags; (void)unused_word3;
    uint64_t daif_val = 0; /* DAIF: interrupts must be masked */

    /* (1) Require all interrupts masked (DAIF bits 0x1c0). */
    if ((~(uint32_t)daif_val & 0x1c0) != 0) {
        sptm_panic(0x54, hcr_flags, "interrupts must be disabled before %s");
    }

    uint16_t *st = (uint16_t *)sptm_guest_state_acquire();
    uint8_t type = (uint8_t)st[1];

    /* (2) The state FTE must be a live shared guest object. */
    if (sptm_fte_class[type * 0x90] != 1) {
        sptm_panic_str("Type %d class of FTE %p ...");
    }

    /* (3) Optional sysreg programming (opaque). */
    if ((sptm_cfg_flags1 & 1) != 0) {
        sptm_reg_write(3, 4, 1, 2, 2, sysreg_val);
    }

    /* (4) HACR_EL2: feature-dependent base OR'd with caller bits. */
    uint64_t hacr = (sptm_cfg_flags0 & 1) ? 0x41f000000000000ULL
                                          : 0x61f000061002000ULL;
    sptm_write_hacr_el2(hacr | hacr_bits);
    sptm_dsb_sy();

    /* (5) VTCR_EL2: use the per-CPU guest config's VTCR (state[6] = cpu id). */
    uint64_t vtcr = sptm_read_vtcr_el2();
    uint64_t *guest_cfg = (uint64_t *)sptm_per_cpu_guest[(uint8_t)st[6] * 8];
    if (*(uint64_t *)((uint8_t *)guest_cfg + 0x40) != vtcr) {
        sptm_write_vtcr_el2(*(uint64_t *)((uint8_t *)guest_cfg + 0x40));
    }

    /* (6) VTTBR_EL2 from the state FTE paddr + vmid. */
    uint64_t state_paddr = sptm_kvtophys(st);
    uint64_t vttbr = (((state_paddr - sptm_window_base) * 0x400 & 0x3fffffffc000ULL)
                      + sptm_mem_low) & 0xfffffffffffeULL;
    vttbr |= (uint64_t)st[2] << 0x30;
    sptm_write_vttbr_el2(vttbr);

    /* (7) HCR_EL2: caller flags with VM bit set and a fixed mask. */
    sptm_write_hcr_el2((hcr_flags & 0xfffffffff7ffffffULL) | 0x400480000001ULL);
    sptm_isb();

    /* (8) Bump the nested-state reference count. */
    uint16_t nested = st[3];
    st[3] = (uint16_t)(nested + 1);
    if (nested > 0x812) {
        sptm_panic_str("refcnt overflow rc %p old %d");
    }

    /* (9) Release the shared reference on the state FTE. */
    uint16_t u = *st;
    *st = (uint16_t)(u - 2);
    LORelease();
    int valid = (u & 1) == 0;

    if (type == 0x13 || type != 0x12) {
        if (valid && u != 0) {
            return;
        }
    } else if (valid && u != 0) {
        /* Nested (0x12) guest: also release the backing page. */
        if (sptm_fte_class[type * 0x90] == 1) {
            if ((st[5] >> 7 & 1) != 0) {
                uint64_t backing = sptm_kvtophys(st);
                uint16_t *bv;
                if (backing < sptm_mem_low || sptm_mem_high <= backing) {
                    void *rv = sptm_phystokv(backing);
                    bv = rv ? (uint16_t *)rv : (uint16_t *)sptm_invalid_fte;
                } else {
                    bv = (uint16_t *)(sptm_window_base +
                                      ((backing - sptm_mem_low) >> 10 & 0xffffffff0ULL));
                    if ((sptm_window_base ^ (uintptr_t)bv) & 0xffc0000000000000ULL) {
                        bv = (uint16_t *)((uintptr_t)bv & 0xffffffffffffULL |
                                          0xc8a2000000000000ULL);
                    }
                }
                u = *bv;
                *bv = (uint16_t)(u - 2);
                LORelease();
                if (u == 0 || (u & 1) != 0) {
                    goto rw_guard_panic;
                }
            }
            return;
        }
        sptm_panic_str("Type %d class of FTE %p ...");
    }

rw_guard_panic:
    sptm_panic_str("rw_guard_release_shared %p ...");
}

/* ------------------------------------------------------------------ *
 * FUN_000f6634 @ 0x000f6634   (est. sptm_guest_exit)
 * Ghidra: undefined FUN_000f6634(void)
 * Leave the guest VCPU after the guest exit path has run. Validates that the
 * current VTTBR_EL2 still matches the per-CPU guest state (faulting
 * otherwise), and if HCR_EL2 bit 29 (guest stage-1/VNCR) is set, re-reads the
 * VNCR/AVNCR physical addresses from the per-CPU slots, drops the UAT ctx-id
 * references on both, zeroes the per-CPU VNCR/AVNCR paddr slots, clears the
 * VNCR sysregs, then resets HCR_EL2 (bit 29 off | 0x8000000) and VTTBR_EL2=0.
 * Finally releases the shared state reference.
 * Confidence: medium
 * Notes: VNCR/AVNCR paddr slots live at sptm_per_cpu_last_vncr + cpu + 1/+9;
 *   both are validated to be UAT ctx type 3 (0x90-class table). Refcount
 *   underflow guard on state[3].
 */
void sptm_guest_exit(void)
{
    uint16_t *st = (uint16_t *)sptm_guest_state_acquire();
    uint8_t type = (uint8_t)st[1];

    if (sptm_fte_class[type * 0x90] != 1) {
        sptm_panic_str("Type %d class of FTE %p ...");
    }

    /* (1) VTTBR_EL2 must still correspond to this state. */
    uint64_t vttbr = sptm_read_vttbr_el2();
    uint64_t state_paddr = sptm_kvtophys(st);
    uint64_t expected = (((state_paddr - sptm_window_base) * 0x400 & 0x3fffffffc000ULL)
                         + sptm_mem_low) & 0xfffffffffffeULL;
    if ((vttbr >> 0x30 != (uint64_t)st[2]) || (expected != (vttbr & 0xfffffffffffeULL))) {
        sptm_panic(0x5d, 0, "vttbr mismatch: %s %s %llx %llx");
    }
    sptm_dsb_sy();

    uint64_t hcr = sptm_read_hcr_el2();
    if ((hcr >> 0x2d & 1) != 0) {
        /* Guest stage-1 VNCR path active: tear down the UAT ctx references. */
        uint64_t vncr = sptm_reg_read(3, 4, 2, 2, 0);
        uint64_t avncr = sptm_reg_read(3, 4, 0xf, 10, 7);
        uint64_t vncr_pa = sptm_kvtophys((void *)vncr);
        uint64_t avncr_pa = sptm_kvtophys((void *)avncr);

        uint64_t cpu1 = sptm_cpu_id();
        uint64_t cpu2 = sptm_cpu_id();
        if (*(uint64_t *)(sptm_per_cpu_last_vncr + cpu1 + SPTM_LAST_VNCR_OFF) != vncr_pa ||
            *(uint64_t *)(sptm_per_cpu_last_vncr + cpu2 + SPTM_LAST_AVNCR_OFF) != avncr_pa) {
            sptm_panic(0x56, 0, "per-cpu last vncr/avncr mismatch %llx %llx");
        }

        uint16_t *vst = (uint16_t *)sptm_fte_acquire(vncr_pa);
        uint16_t *ast = (uint16_t *)sptm_fte_acquire(avncr_pa);
        if (sptm_fte_class[(uint8_t)vst[1] * 0x90] != 3 ||
            sptm_fte_class[(uint8_t)ast[1] * 0x90] != 3) {
            sptm_panic_str("Type %d class of FTE %p ...");
        }

        int vrc = *(int *)(vst + 6);
        *(int *)(vst + 6) = vrc - 1;
        int arc = *(int *)(ast + 6);
        *(int *)(ast + 6) = arc - 1;
        if (vrc == 0 || arc == 0) {
            goto refcnt_underflow_panic;
        }

        /* Release (or invalidate) the UAT ctx entries. */
        if (sptm_fte_class[(uint8_t)vst[1] * 0x90] != 6) {
            if ((sptm_fte_shared[(uint8_t)vst[1] * 0x90] & 1) == 0) {
                vst[0] = 0; vst[1] = 0;
            } else {
                uint16_t v = *vst;
                *vst = (uint16_t)(v - 2);
                LORelease();
                if (v == 0 || (v & 1) != 0) goto rw_guard_panic;
            }
        }
        if (sptm_fte_class[(uint8_t)ast[1] * 0x90] == 6) {
            goto clear_vncr_slots;
        }
        if ((sptm_fte_shared[(uint8_t)ast[1] * 0x90] & 1) != 0) {
            uint16_t a = *ast;
            *ast = (uint16_t)(a - 2);
            LORelease();
            if (a == 0 || (a & 1) != 0) goto rw_guard_panic;
            goto clear_vncr_slots;
        }
        ast[0] = 0; ast[1] = 0;

clear_vncr_slots:;
        /* Zero the per-CPU last-VNCR/AVNCR paddr slots. */
        uint64_t cpu = sptm_cpu_id();
        uint64_t *s1 = (uint64_t *)(sptm_per_cpu_last_vncr + cpu + SPTM_LAST_VNCR_OFF);
        s1[0] = 0;
        uint64_t cpu2b = sptm_cpu_id();
        uint64_t *s2 = (uint64_t *)(sptm_per_cpu_last_vncr + cpu2b + SPTM_LAST_AVNCR_OFF);
        s2[0] = 0;
        sptm_reg_write(3, 4, 2, 2, 0, 0);
        sptm_reg_write(3, 4, 0xf, 10, 7, 0);
        hcr &= 0xffffdfffffffffffULL;
    }

    /* (2) Reset HCR_EL2 (bit 29 cleared, bit 27 set) and VTTBR_EL2 = 0. */
    sptm_write_hcr_el2(hcr | 0x8000000ULL);
    sptm_write_vttbr_el2(0);
    sptm_isb();

    /* (3) Release the nested-state reference. */
    uint16_t nested = st[3];
    st[3] = (uint16_t)(nested - 1);
    if (nested == 0) {
        goto refcnt_underflow_panic;
    }

    /* (4) Release the shared state reference (same epilogue as guest_enter). */
    uint16_t u = *st;
    *st = (uint16_t)(u - 2);
    LORelease();
    int valid = (u & 1) == 0;
    if (type == 0x13 || type != 0x12) {
        if (valid && u != 0) {
            return;
        }
    } else if (valid && u != 0) {
        if (sptm_fte_class[type * 0x90] != 1) {
            sptm_panic_str("Type %d class of FTE %p ...");
        }
        if ((st[5] >> 7 & 1) != 0) {
            uint64_t backing = sptm_kvtophys(st);
            uint16_t *bv;
            if (backing < sptm_mem_low || sptm_mem_high <= backing) {
                void *rv = sptm_phystokv(backing);
                bv = rv ? (uint16_t *)rv : (uint16_t *)sptm_invalid_fte;
            } else {
                bv = (uint16_t *)(sptm_window_base +
                                  ((backing - sptm_mem_low) >> 10 & 0xffffffff0ULL));
                if ((sptm_window_base ^ (uintptr_t)bv) & 0xffc0000000000000ULL) {
                    bv = (uint16_t *)((uintptr_t)bv & 0xffffffffffffULL |
                                      0xc8a2000000000000ULL);
                }
            }
            u = *bv;
            *bv = (uint16_t)(u - 2);
            LORelease();
            if (u == 0 || (u & 1) != 0) goto rw_guard_panic;
        }
        return;
    }

rw_guard_panic:
    sptm_panic_str("rw_guard_release_shared %p ...");
refcnt_underflow_panic:
    sptm_panic_str("refcnt underflow rc %p old %d");
}

/* Opaque TLBI / AT instruction wrapper. */
static inline void sptm_tlbi(uint64_t op1, uint64_t crn, uint64_t crm,
                             uint64_t op2, uint64_t val) {
    (void)op1; (void)crn; (void)crm; (void)op2; (void)val;
    /* opaque TLBI instruction */
}
static inline uint64_t sptm_at_s1e1r(uint64_t va) {
    (void)va;
    return 0; /* AT S1E1R: PAR_EL1 result */
}

/* ------------------------------------------------------------------ *
 * FUN_000f7924 @ 0x000f7924   (est. sptm_guest_dispatch)
 * Ghidra: undefined FUN_000f7924(void)
 * Top-level guest VCPU dispatch. Requires masked interrupts; copies the
 * caller's guest state block (0xa60 bytes) into the per-CPU handoff scratch,
 * and if the handoff context-switch flag (byte +0x15, bit 5) is set,
 * programs the VNCR/AVNCR registers from two physical addresses carried in
 * the handoff (words +0x28/+0x30): validates both are 0x0b-type (context
 * table) FTEs page-aligned, bumps their ctx refcounts (overflow guard at
 * 0xfffffff4), records them in the per-CPU last-VNCR/AVNCR slots, and writes
 * their physical addresses to the VNCR sysregs. Then clears a config bit if
 * the feature is off and enters the guest (sptm_guest_enter), optionally
 * broadcasting a TLB flush, and clears the handoff.
 * Confidence: medium
 * Notes: handoff word +0xa50 bit0 cleared when cfg_flags0 bit0 clear; byte
 *   +0xa58 bit0 triggers a full TLBI (0,9,7,0,0) + DSB ISH + ISB after entry.
 *   VNCR/AVNCR physical addresses translated via sptm_va_to_pa (FUN_000d81bc).
 */
void sptm_guest_dispatch(uint64_t guest_state_paddr, uint64_t unused_param2)
{
    (void)unused_param2;
    uint64_t daif_val = 0;
    if ((~(uint32_t)daif_val & 0x1c0) != 0) {
        sptm_panic(0x54, 0, "interrupts must be disabled before %s");
    }

    /* (1) The guest state block must be a valid SPTM physical address. */
    if (guest_state_paddr < sptm_mem_low || sptm_mem_high <= guest_state_paddr) {
        sptm_panic(6, 0, "invalid physical address %llx");
    }
    sptm_copy_to_scratch(guest_state_paddr, 0xa60, 1, 0);

    uint64_t *h = sptm_handoff_ptr();

    /* (2) Program the VNCR/AVNCR context if a context switch is pending. */
    if ((*(uint8_t *)((uint8_t *)h + 0x15) >> 5 & 1) != 0) {
        uint64_t vncr = h[5];
        uint64_t avncr = h[6];
        if ((vncr < sptm_mem_low || sptm_mem_high <= vncr) ||
            (avncr < sptm_mem_low || sptm_mem_high <= avncr)) {
            sptm_panic(6, 0, "invalid physical address %llx");
        }
        uint16_t *vst = (uint16_t *)sptm_fte_acquire(vncr);
        uint16_t *ast = (uint16_t *)sptm_fte_acquire(avncr);
        if ((*(int8_t *)((uint8_t *)vst + 2) != 0x0b) ||
            (((uint32_t)avncr | (uint32_t)vncr) & 0xfff) != 0 ||
            *(int8_t *)((uint8_t *)ast + 2) != 0x0b) {
            sptm_panic(0x56, 0, "invalid VNCR/AVNCR paddr %llx %llx");
        }
        if (sptm_ctx_global_type != 0x03) {
            sptm_panic_str("Type %d class of FTE %p ...");
        }
        uint32_t vrc = *(uint32_t *)((uint8_t *)vst + 0xc);
        *(uint32_t *)((uint8_t *)vst + 0xc) = vrc + 1;
        uint32_t arc = *(uint32_t *)((uint8_t *)ast + 0xc);
        *(uint32_t *)((uint8_t *)ast + 0xc) = arc + 1;
        if (vrc > 0xfffffff4 || arc > 0xfffffff4) {
            sptm_panic_str("refcnt overflow rc %p old %d");
        }

        uint64_t c1 = sptm_cpu_id();
        uint64_t c2 = sptm_cpu_id();
        if (*(uint64_t *)(sptm_per_cpu_last_vncr + c1 + SPTM_LAST_VNCR_OFF) != 0) {
            sptm_panic_str("per_cpu_last_vncr_paddr already set");
        }
        uint64_t c2b = sptm_cpu_id();
        if (*(uint64_t *)(sptm_per_cpu_last_vncr + c2 + SPTM_LAST_AVNCR_OFF) != 0) {
            sptm_panic_str("per_cpu_last_avncr_paddr already set");
        }
        uint64_t c3 = sptm_cpu_id();
        *(uint64_t *)(sptm_per_cpu_last_vncr + c3 + SPTM_LAST_VNCR_OFF) = vncr;
        uint64_t c4 = sptm_cpu_id();
        *(uint64_t *)(sptm_per_cpu_last_vncr + c4 + SPTM_LAST_AVNCR_OFF) = avncr;

        sptm_reg_write(3, 4, 2, 2, 0, sptm_va_to_pa((void *)vncr));
        sptm_reg_write(3, 4, 0xf, 10, 7, sptm_va_to_pa((void *)avncr));
        sptm_fte_release(vst);
        sptm_fte_release(ast);
    }

    /* (3) Clear a config bit when the corresponding feature is disabled. */
    uint64_t cfg = sptm_cfg_flags0;
    if ((sptm_cfg_flags0 & 1) == 0) {
        h[0x14a] &= ~0x1ULL;
        uint64_t v = sptm_reg_read(3, 6, 0xf, 0xf, 1) & ~0x1ULL;
        sptm_reg_write(3, 6, 0xf, 0xf, 1, v);
    }

    /* (4) Enter the guest with the handoff-carried config. */
    sptm_guest_enter(cfg, h[0], h[2], h[4], h[3]);

    /* (5) Optional TLB broadcast after entry. */
    if ((*(uint8_t *)((uint8_t *)h + 0x14b * 8) & 1) != 0) {
        sptm_tlbi(9, 7, 0, 0, 0); /* TLBI all (0,9,7,0,0) */
        sptm_dsb_ish();
        sptm_isb();
    }

    /* (6) Clear the per-CPU post-entry slot and the handoff. */
    uint64_t cpu = sptm_cpu_id();
    *(uint64_t *)((uint8_t *)cpu + 0xa68) = 0;
    sptm_handoff_clear(h, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000f7cc0 @ 0x000f7cc0   (est. sptm_guest_va_to_ipa)
 * Ghidra: ulong FUN_000f7cc0(undefined8, ulong)
 * Translate a guest virtual address to IPA while in guest context: saves a
 * scratch sysreg, installs the AT-walk marker value, issues AT S1E1R, reads
 * PAR_EL1, and returns the translated IPA (or 0xffffffffffffffff on fault).
 * Restores the scratch sysreg and exits the guest.
 * Confidence: high (API name header-matched; logic straightforward)
 * Notes: AT S1E1R result read from PAR_EL1; low 12 bits of the VA preserved;
 *   PAR_EL1 bit 0 set => translation fault => returns all-ones.
 */
uint64_t sptm_guest_va_to_ipa(uint64_t guest_paddr, uint64_t va)
{
    uint64_t daif_val = 0;
    if ((~(uint32_t)daif_val & 0x1c0) == 0) {
        sptm_guest_enter(guest_paddr, 0, 0, 0, 0);
        uint64_t saved = sptm_reg_read(3, 6, 0xf, 0xf, 7);
        sptm_reg_write(3, 6, 0xf, 0xf, 7, 0xaaaaaaaaaaaaaaaaULL);
        sptm_isb();
        uint64_t at = sptm_at_s1e1r(va);
        sptm_write_par_el1(at);
        sptm_isb();
        uint64_t par = sptm_read_par_el1();
        uint64_t out = (par & 0xfffffffff000ULL) | (va & 0xfff);
        if ((par & 1) != 0) {
            out = 0xffffffffffffffffULL;
        }
        sptm_reg_write(3, 6, 0xf, 0xf, 7, saved);
        sptm_guest_exit();
        return out;
    }
    sptm_panic_str("interrupts must be disabled before %s");
}

/* ------------------------------------------------------------------ *
 * FUN_000f5f2c @ 0x000f5f2c   (est. sptm_guest_stage1_tlb_op)
 * Ghidra: undefined FUN_000f5f2c(undefined8, uint, undefined8)
 * Perform a stage-1 TLB maintenance operation on the guest while in guest
 * context. op (param_2) selects the TLBI operation (0=ASIDE1IS, 1=VAE1IS,
 * 2=VAAE1IS, 3=VAALE1IS, 4=VALE1IS, 5=VMALLE1IS, 6-9 = additional TLBI
 * encodings); the operand (param_3) carries the VA/asid. Enters and exits
 * the guest around the operation and releases the shared state reference.
 * Confidence: medium
 * Notes: op 6-9 encoded as system ops (0,8,2,{1,3,7,5}); op>9 faults (0x55).
 */
void sptm_guest_stage1_tlb_op(uint64_t guest_paddr, uint32_t op, uint64_t operand)
{
    uint16_t *st = (uint16_t *)sptm_guest_state_acquire();
    uint8_t type = (uint8_t)st[1];

    sptm_guest_enter(guest_paddr, 0, 0, 0, 0);
    if (op > 9) {
        sptm_panic(0x55, 0, "invalid TLBI op %llx");
    }

    switch (op) {
    default: /* 0 */
        sptm_tlbi(8, 2, 0, 3, operand); /* TLBI ASIDE1IS */
        break;
    case 1: sptm_tlbi(8, 2, 1, 3, operand); break; /* VAE1IS */
    case 2: sptm_tlbi(8, 2, 1, 7, operand); break; /* VAAE1IS */
    case 3: sptm_tlbi(8, 2, 1, 1, operand); break; /* VAALE1IS */
    case 4: sptm_tlbi(8, 2, 1, 2, operand); break; /* VALE1IS */
    case 5: sptm_tlbi(8, 2, 0, 5, 0);       break; /* VMALLE1IS */
    case 6: sptm_tlbi(8, 2, 1, 0, operand); break; /* (0,8,2,1) */
    case 7: sptm_tlbi(8, 2, 3, 0, operand); break; /* (0,8,2,3) */
    case 8: sptm_tlbi(8, 2, 7, 0, operand); break; /* (0,8,2,7) */
    case 9: sptm_tlbi(8, 2, 5, 0, operand); break; /* (0,8,2,5) */
    }
    sptm_guest_exit();

    /* Release the shared state reference (same epilogue as guest_enter). */
    uint16_t u = *st;
    *st = (uint16_t)(u - 2);
    LORelease();
    int valid = (u & 1) == 0;
    if (type == 0x13 || type != 0x12) {
        if (valid && u != 0) {
            return;
        }
    } else if (valid && u != 0) {
        if (sptm_fte_class[type * 0x90] != 1) {
            sptm_panic_str("Type %d class of FTE %p ...");
        }
        if ((st[5] >> 7 & 1) != 0) {
            uint64_t backing = sptm_kvtophys(st);
            uint16_t *bv;
            if (backing < sptm_mem_low || sptm_mem_high <= backing) {
                void *rv = sptm_phystokv(backing);
                bv = rv ? (uint16_t *)rv : (uint16_t *)sptm_invalid_fte;
            } else {
                bv = (uint16_t *)(sptm_window_base +
                                  ((backing - sptm_mem_low) >> 10 & 0xffffffff0ULL));
                if ((sptm_window_base ^ (uintptr_t)bv) & 0xffc0000000000000ULL) {
                    bv = (uint16_t *)((uintptr_t)bv & 0xffffffffffffULL |
                                      0xc8a2000000000000ULL);
                }
            }
            u = *bv;
            *bv = (uint16_t)(u - 2);
            LORelease();
            if (u == 0 || (u & 1) != 0) goto rw_guard_panic_s1;
        }
        return;
    }

rw_guard_panic_s1:
    sptm_panic_str("rw_guard_release_shared %p ...");
}

/* ------------------------------------------------------------------ *
 * NVMe IOMMU driver (dispatch table 6)
 * ------------------------------------------------------------------ */

static inline uint64_t sptm_cntpct(void)  { return sptm_reg_read(3, 3, 0xe, 0, 6); }
static inline uint64_t sptm_cntfrq(void)  { return __builtin_arm_rsr64("cntfrq_el0"); }
static inline void sptm_wfe(void)         { __builtin_arm_wfe(); }

/* ------------------------------------------------------------------ *
 * FUN_000c3434 @ 0x000c3434   (est. sptm_nvme_map_pages)
 * Ghidra: undefined FUN_000c3434(uint, ulong, ulong, ulong, uint)
 * Map a contiguous run of physical pages into an NVMe TCB entry so the NVMe
 * controller can DMA to/from them. Validates: the NVMe feature is enabled
 * (state+0x14 bit1), the domain is 0/1, the entry id is in range, the page
 * count <= 0x101, and both the TCB structure (0x80 bytes) and the page-list
 * (count*8 bytes) are SPTM-managed physical addresses. Copies both into the
 * per-CPU scratch, enforces that the TCB WR-permission bits are not both set,
 * takes an IOMMU page reference on every page (4KB or 2MB depending on the
 * 0x100 permission bit), writes the published TCB, cleans the page array to
 * DRAM if enabled, and flips the entry state guard.
 * Confidence: medium
 * Notes: TCB pointer table at state+0x130 (or +0x120 when state+0x18 bit0
 *   clear); page array at state[0x758] + entry*0x800; perms stored at
 *   state+0x140+entry*2 (masked 0x1f00). Page refs via sptm_iommu_page_ref.
 *   Security-relevant: the "Both WR bits are set" check rejects TCBs with
 *   both host-to-IP and IP-to-host write bits (0x300) set.
 */
void sptm_nvme_map_pages(uint32_t domain, uint64_t entry_id, uint64_t tcb_paddr,
                         uint64_t page_list_paddr, uint32_t num_pages)
{
    /* (0) Feature / argument validation. */
    if ((*(uint32_t *)(sptm_nvme_state + 0x14) >> 1 & 1) == 0) {
        sptm_panic(0x3000005, tcb_paddr, "feature disabled %llx");
    }
    if (domain > 1) {
        sptm_panic(0x3000000, tcb_paddr, "invalid domain %llx");
    }
    if (*(uint32_t *)(sptm_nvme_state + 0x10) <= (uint32_t)entry_id) {
        sptm_panic(0x3000001, tcb_paddr, "invalid entry id %llx");
    }
    if (num_pages > 0x101) {
        sptm_panic(0x3000002, tcb_paddr, "too many pages %llx");
    }
    if (tcb_paddr < sptm_mem_low || sptm_mem_high <= tcb_paddr) {
        sptm_panic(6, tcb_paddr, "invalid physical address %llx");
    }

    /* (1) Copy the TCB (0x80 bytes) and the page list into per-CPU scratch. */
    uint16_t *tcb = (uint16_t *)sptm_copy_to_scratch(tcb_paddr, 0x80, 1, 0);
    uint64_t *pages = NULL;
    uint64_t errval = tcb_paddr;
    if (num_pages == 0) {
        pages = NULL;
    } else {
        if (page_list_paddr < sptm_mem_low || sptm_mem_high <= page_list_paddr) {
            sptm_panic(6, tcb_paddr, "invalid physical address %llx");
        }
        pages = (uint64_t *)sptm_copy_to_scratch(page_list_paddr, num_pages * 8, 1, 0x80);
        errval = tcb_paddr;
    }

    uint64_t idx = entry_id & 0xffff;

    /* (2) The entry's state guard must be free. */
    uint8_t *guard = (uint8_t *)(sptm_nvme_state + idx + 0x19);
    if (*guard != 0) {
        sptm_panic(0x3000006, errval, "entry busy %llx");
    }
    *guard = 1;

    /* (3) Locate the TCB slot in the active pointer table. */
    uint64_t tbl_off = 0x130;
    if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0) {
        tbl_off = 0x120;
    }
    uint16_t *slot = (uint16_t *)(*(uint64_t *)(sptm_nvme_state + tbl_off + domain * 8)
                                  + idx * 0x80);

    if (*slot != 0) {
        sptm_panic_str("TCB entry %d is not invalid");
    }
    if (slot[2] != 0) {
        sptm_panic_str("TCB entry %d NLB is not zero");
    }

    /* (4) Store the WR-permission bits (masked 0x1f00) into the perms slot. */
    uint64_t perms_slot = (uint64_t)(uintptr_t)(sptm_nvme_state + 0x140 + idx * 2);
    *(uint16_t *)(uintptr_t)perms_slot = *tcb & 0x1f00;

    /* Security: reject TCBs that set both WR directions. */
    if ((*(uint8_t *)(sptm_nvme_state + 0x7b9) & 1) != 0 &&
        (((*tcb ^ 0xffff) & 0x300) == 0)) {
        sptm_panic_str("Both WR bits are set");
    }

    /* (5) Clear the TCB's page/ref fields and the header word. */
    tcb[0xc] = 0; tcb[0xd] = 0; tcb[0xe] = 0; tcb[0xf] = 0;
    tcb[0x10] = 0; tcb[0x11] = 0; tcb[0x12] = 0; tcb[0x13] = 0;
    *tcb = 0;

    uint64_t *page_array = (uint64_t *)(*(uint64_t *)(sptm_nvme_state + 0x758)
                                        + idx * 0x800);

    if (num_pages != 0) {
        /* (6) Validate + ref each page; publish into the TCB/page array. */
        uint64_t low = *(uint64_t *)(sptm_nvme_state + 0x760);
        uint64_t hi = *(uint64_t *)(sptm_nvme_state + 0x768) + low;
        uint64_t p0 = *pages;
        int align;
        if ((p0 & 0xfff) == 0) {
            align = -1;
        } else {
            if (num_pages == 1) {
                sptm_panic(0x300000f, errval, "unaligned page %llx");
            }
            align = -2;
        }
        if (num_pages + align != (uint32_t)tcb[2]) {
            goto count_mismatch;
        }
        if (((p0 < low || hi <= p0)) && (p0 < sptm_mem_low || sptm_mem_high <= p0)) {
            sptm_panic(6, errval, "invalid physical address %llx");
        }
        uint32_t ptype = 1;
        if ((*(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) & 0x100) != 0) {
            ptype = 2;
        }
        sptm_iommu_page_ref(p0, ptype);
        *(uint64_t *)(tcb + 0xc) = p0;

        if (num_pages != 1) {
            /* second page */
            uint64_t p1 = pages[1];
            if (((p1 < low || hi <= p1)) && (p1 < sptm_mem_low || sptm_mem_high <= p1)) {
                sptm_panic(6, errval, "invalid physical address %llx");
            }
            if ((p1 & 0xfff) != 0) {
                sptm_panic(0x3000003, errval, "unaligned page %llx");
            }
            ptype = 1;
            if ((*(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) & 0x100) != 0) {
                ptype = 2;
            }
            sptm_iommu_page_ref(p1, ptype);

            if (num_pages == 2) {
                *(uint64_t *)(tcb + 0x10) = p1;
            } else {
                /* multi-page: remaining pages go into the page array. */
                uint64_t arr_va = *(uint64_t *)(sptm_nvme_state + 0x750) + idx * 0x800;
                *(uint64_t *)(tcb + 0x10) = arr_va;
                *page_array = p1;
                uint64_t left = (uint64_t)num_pages - 2;
                uint64_t *src = pages + 2;
                uint64_t *dst = page_array + 1;
                do {
                    uint64_t p = *src;
                    if (((p < low || hi <= p)) && (p < sptm_mem_low || sptm_mem_high <= p)) {
                        sptm_panic(6, errval, "invalid physical address %llx");
                    }
                    if ((p & 0xfff) != 0) {
                        sptm_panic(0x3000003, errval, "unaligned page %llx");
                    }
                    ptype = 1;
                    if ((*(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) & 0x100) != 0) {
                        ptype = 2;
                    }
                    sptm_iommu_page_ref(p, ptype);
                    *dst = p;
                    src++; dst++;
                    left--;
                } while (left != 0);
            }
        }
    }

    /* (7) Publish the TCB and the NLB. */
    *(uint32_t *)(sptm_nvme_state + idx * 4 + 0x344) = num_pages;
    sptm_memcpy(slot, tcb, 0x80);
    slot[1] = (uint16_t)entry_id;

    uint8_t next_guard = 2;
    if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0) {
        sptm_dmb_ish();
        *slot = *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140);
        next_guard = 3;
    }

    if (num_pages > 0x10 && (*(uint8_t *)(sptm_nvme_state + 0x770) & 1) != 0) {
        sptm_dmb_sy();
        uint64_t len = 0x1000;
        if (num_pages < 0x100) {
            len = (num_pages * 8 + 0x7f) & 0x1f80;
        }
        sptm_dcache_clean_invalidate((uintptr_t)page_array, len);
    }

    /* (8) Release the entry state guard. */
    if (*guard == 1) {
        *guard = next_guard | (uint8_t)(domain << 4);
        return;
    }
    sptm_panic_str("state_guard_release %llx");

count_mismatch:
    sptm_panic(0x3000004, errval, "page count mismatch %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000c2dec @ 0x000c2dec   (est. sptm_nvme_unmap_pages)
 * Ghidra: undefined8 FUN_000c2dec(uint, ulong, byte)
 * Unmap the pages previously mapped into an NVMe TCB entry, releasing the
 * IOMMU page references and zeroing the TCB/page array. `direction` bit 0
 * selects the direction (0 = host-to-IP / f2h with guard value |3, 1 =
 * IP-to-host / h2f with guard value |4). When the ANS auto-signaling state
 * machine is enabled (state+0x7b9 bit0), waits for the controller to
 * acknowledge the invalidation with a bounded poll + WFE timeout, then resets
 * the per-entry registers. Releases every referenced page (first page from
 * TCB+0xc, remaining from TCB+0x10 / the page array), zeroes the TCB and
 * page array, clears the perms slot, and releases the entry state guard.
 * Returns 1 on the normal completion path, 0 on the ANS timeout path.
 * Confidence: medium
 * Notes: ANS invalidation ring at state[0x7c0]/+0x7d8/+0x7dc; per-entry regs
 *   at state[0x7c8] (+4/+0xc) and state[2000](+4). Direction state byte at
 *   state+0x19+entry holds domain<<4 | {3,4}. Page refs released via
 *   sptm_iommu_page_unref (type from 0x100 perms bit).
 */
uint64_t sptm_nvme_unmap_pages(uint32_t domain, uint64_t entry_id, uint8_t direction)
{
    /* (0) Feature / argument validation. */
    if ((*(uint32_t *)(sptm_nvme_state + 0x14) >> 2 & 1) == 0) {
        sptm_panic(0x3000005, entry_id, "feature disabled %llx");
    }
    if (domain > 1) {
        sptm_panic(0x3000000, entry_id, "invalid domain %llx");
    }
    uint32_t e32 = (uint32_t)entry_id;
    if (*(uint32_t *)(sptm_nvme_state + 0x10) <= e32) {
        sptm_panic(0x3000001, entry_id, "invalid entry id %llx");
    }

    uint8_t dshift = (uint8_t)(domain << 4);
    uint64_t idx = entry_id & 0xffff;
    uint8_t *guard = (uint8_t *)(sptm_nvme_state + 0x19 + idx);

    /* (1) Match + clear the direction-specific state guard. */
    if ((direction & 1) == 0) {
        /* host-to-IP: guard == domain<<4 | 3 */
        uint8_t g = *guard;
        if (g == (dshift | 3)) {
            *guard = 1;
        }
        uint64_t tbl_off = 0x130;
        if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0) {
            tbl_off = 0x120;
        }
        uint16_t *slot = (uint16_t *)(*(uint64_t *)(sptm_nvme_state + tbl_off + domain * 8)
                                      + idx * 0x80);
        if (g != (dshift | 3)) {
            goto direction_mismatch;
        }
        *slot = 0;

        /* f2h/h2f bit conflict check. */
        if ((*(uint8_t *)(sptm_nvme_state + 0x9e8) & 1) != 0 &&
            (*(uint32_t *)(*(uint64_t *)(sptm_nvme_state + 0x9e0) + idx * 0x20) & 0x300) != 0) {
            sptm_panic_str("f2h and h2f bits are set");
        }

        /* ANS invalidation request. */
        sptm_dmb_ish();
        uint64_t regs = *(uint64_t *)(sptm_nvme_state + 0x748);
        *(uint32_t *)(regs + 0x118) = (uint32_t)idx;
        uint32_t w = *(uint32_t *)(regs + (e32 >> 2 & 0x3fff) * 4);
        if ((w >> (e32 & 3 | (e32 & 3) << 2) & 0xf) != 0) {
            sptm_panic_str("ANS invalidation failed with outstanding refs");
        }
    } else {
        /* IP-to-host: guard == domain<<4 | 4 */
        uint8_t g = *guard;
        if (g == (dshift | 4)) {
            *guard = 1;
        }
        if (g != (dshift | 4)) {
            goto direction_mismatch;
        }
        uint64_t tbl_off = 0x130;
        if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0) {
            tbl_off = 0x120;
        }
        uint16_t *slot = (uint16_t *)(*(uint64_t *)(sptm_nvme_state + tbl_off + domain * 8)
                                      + idx * 0x80);
        /* (fall through to shared invalidation path) */
        *slot = 0;
    }

    /* (2) If the ANS wait-for-ack state machine is enabled, wait for it. */
    if ((*(uint8_t *)(sptm_nvme_state + 0x7b9) & 1) != 0) {
        uint16_t perms = *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140);
        uint64_t state = (uintptr_t)sptm_nvme_state;
        if ((direction & 1) == 0) {
            int big = (perms & 0x100) != 0;
            uint32_t v = big ? 0x800000 : 0x80;
            uint32_t u = big ? 0x400000 : 0x40;
            uint64_t r = *(uint64_t *)(state + 0x7c8);
            *(uint32_t *)(r + 4) = v;
            *(uint32_t *)(r + 0xc) = v;
            *(uint32_t *)(*(uint64_t *)(state + 2000) + 4) = u;
            *(uint16_t *)(state + idx * 2 + 0x7dc) = 0;
        }

        /* Bounded poll of the ANS completion counters. */
        sptm_dsb_sy();
        uint64_t t0 = sptm_cntpct();
        uint64_t freq = sptm_cntfrq();
        uint64_t t1 = freq;
        for (;;) {
            uint32_t pending = *(uint32_t *)(sptm_nvme_state + 0x7d8);
            uint32_t done = 0;
            if (pending != 0) {
                uint32_t i = 0;
                uint64_t off = 0;
                uint16_t bm = *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x7dc);
                do {
                    uint64_t bit = 1ULL << (i & 0x3f);
                    if ((bit & bm) != 0) {
                        done++;
                    } else {
                        uint32_t v = *(uint32_t *)(*(uint64_t *)(sptm_nvme_state + 0x7c0) + off);
                        if ((perms >> 8 & 1) == 0) {
                            v = (v ^ 0xffffffff) & 0x7f0000;
                        } else {
                            v = (v ^ 0xffffffff) & 0xff;
                        }
                        if (v == 0) {
                            bm |= (uint16_t)(bit & 0xffff);
                            *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x7dc) = bm;
                            done++;
                        }
                    }
                    i++;
                    off += 0x10000;
                } while (pending != i);
            }
            if (done == pending) {
                /* all acknowledged: reset per-entry regs and finish. */
                uint64_t r = *(uint64_t *)(sptm_nvme_state + 0x7c8);
                *(uint32_t *)(r + 4) = 0x800080;
                *(uint32_t *)(r + 0xc) = 0x800080;
                *(uint32_t *)(*(uint64_t *)(sptm_nvme_state + 2000) + 4) = 0x400040;
                *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x7dc) = 0;
                goto ans_done;
            }
            sptm_dsb_sy();
            uint64_t now = sptm_cntpct();
            if ((t1 & 0xffffffe0) / 100000 < (now - t0)) {
                /* long-timeout fallback: wait for completion with WFE. */
                sptm_dsb_sy();
                uint64_t w0 = sptm_cntpct();
                uint64_t wf = sptm_cntfrq();
                for (;;) {
                    sptm_dsb_sy();
                    uint64_t wn = sptm_cntpct();
                    if ((wf & 0xffffff80) / 10000000 <= (wn - w0)) {
                        break;
                    }
                    sptm_wfe();
                }
            }
            if ((now - t0) >= (freq & 0xffffffe0) / 4000) {
                break; /* hard timeout */
            }
        }
        /* Timeout path: leave the guard marked h2f and return 0. */
        if (*guard == 1) {
            *guard = dshift | 4;
            return 0;
        }
        sptm_panic_str("state_guard_release %llx");
    }

ans_done:;
    /* (3) Release the mapped pages. */
    uint64_t state = (uintptr_t)sptm_nvme_state;
    uint32_t tbl_off = 0x130;
    if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0) {
        tbl_off = 0x120;
    }
    uint16_t *slot = (uint16_t *)(*(uint64_t *)(sptm_nvme_state + tbl_off + domain * 8)
                                  + idx * 0x80);

    uint32_t nlb = *(uint32_t *)(sptm_nvme_state + idx * 4 + 0x344);
    *(uint32_t *)(sptm_nvme_state + idx * 4 + 0x344) = 0;
    uint64_t *page_array = (uint64_t *)(*(uint64_t *)(sptm_nvme_state + 0x758) + idx * 0x800);

    if (nlb != 0) {
        uint32_t ptype = 1;
        if ((*(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) & 0x100) != 0) {
            ptype = 2;
        }
        if (*(uint64_t *)(slot + 0xc) != 0) {
            sptm_iommu_page_unref(*(uint64_t *)(slot + 0xc), ptype);
        }
        if (nlb != 1) {
            uint64_t i = 0;
            uint64_t left = (uint64_t)nlb - 1;
            do {
                uint64_t *pa = (uint64_t *)(page_array + i);
                uint64_t *src = (nlb == 2) ? (uint64_t *)(slot + 0x10) : pa;
                if (*src != 0) {
                    ptype = 1;
                    if ((*(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) & 0x100) != 0) {
                        ptype = 2;
                    }
                    sptm_iommu_page_unref(*src, ptype);
                }
                i++;
                left--;
            } while (left != 0);
            if (nlb > 2) {
                sptm_memset(page_array, ((uint64_t)nlb - 1) * 8, 0xffffffffffffffffULL);
            }
        }
    }

    /* (4) Zero the TCB, clear the perms, and release the state guard. */
    sptm_memset(slot, 0x80, 0xffffffffffffffffULL);
    *(uint16_t *)(sptm_nvme_state + idx * 2 + 0x140) = 0;

    if ((nlb > 0xff) && (*(uint8_t *)(sptm_nvme_state + 0x770) & 1) != 0) {
        sptm_dmb_sy();
        sptm_dcache_clean_invalidate((uintptr_t)(page_array + 0x800 / 8), 0x800);
    }

    if (*guard == 1) {
        *guard = 0;
        return 1;
    }
    sptm_panic_str("state_guard_release %llx");

direction_mismatch:
    sptm_panic(0x3000006, entry_id, "direction/state mismatch %llx");
}

/* ------------------------------------------------------------------ *
 * SART IOMMU driver (dispatch table 5)
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * FUN_000c5a28 @ 0x000c5a28   (est. sptm_sart_unmap_region)
 * Ghidra: undefined8 FUN_000c5a28(undefined8, undefined8)
 * Unmap and tear down a SART region covering [paddr, paddr+size). Validates
 * the request, takes the per-CPU region guard (state+0x24a), finds the region
 * entry whose [start>>12, end>>12) matches, and for a single-page region
 * (flags word +16 == 1) zeroes its three parallel SART table entries and
 * restores permissions from the saved perm table; for a multi-page region
 * performs a deeper lookup. Then frees the 20-byte region entry, releases the
 * per-16KB-granule IOMMU page references for large regions, decrements the
 * region count, and releases the region guard. Returns 1 if a power-gate TLB
 * flush is required, else 0.
 * Confidence: low
 * Notes: region table base at state+0x238 (count byte at +4); region data
 *   table at state+0x1f8; three parallel offset arrays described by
 *   (base,stride) pairs at +8/+0xc, +0x20/+0x24, +0x14/+0x18. Sub-entry
 *   offsets are relative to state[0x82] and bounded by state[0x200]. Power
 *   canary: magic -0x54012113 at state[0x84][state[0x87]], count state[0x88].
 *   Security-relevant: unmapped region table entries are zeroed and their
 *   permission bits validated before/after, preventing stale DMA permissions.
 */
uint64_t sptm_sart_unmap_region(uint64_t paddr, uint64_t size)
{
    uint64_t va = 0, sz = 0;
    uint64_t rv = 0;
    uint32_t ptype = 1;
    uint32_t *rentry = NULL;
    uint8_t guard_cpu = 0;

    sptm_sart_validate_region(paddr, size, &va, &sz);

    uint32_t *st = sptm_sart_state;
    uint8_t *base = (uint8_t *)st;

    /* (1) Take the per-CPU region guard. */
    if (*(uint8_t *)(base + 0x24a) != 0) {
        sptm_panic(0x200000a, 0, "region guard busy %llx");
    }
    uint8_t *mi = sptm_handoff_region;
    *(uint8_t *)(base + 0x24a) = (uint8_t)(mi[sptm_cpu_id() + 10] << 1 | 1);

    /* (2) Region table: base at +0x238, count byte at +4. */
    uint8_t *rtbl = *(uint8_t **)(base + 0x238);
    uint64_t nreg = *(uint8_t *)(rtbl + 4);

    if (nreg != 0) {
        uint64_t id = 0;
        uint32_t *r = st + 4;
        for (;;) {
            /* Match region by [start>>12, end>>12). */
            if ((va >> 0xc == (uint64_t)r[4]) && (sz >> 0xc == (uint64_t)r[5])) {
                ptype = 1;
                if (r[3] == 1) {
                    ptype = 2;
                }
                rentry = r;
                if (r[4] == 1) {
                    /* ---- single-page region ---- */
                    if (nreg <= id) {
                        sptm_panic_str("Invalid Region ID %d");
                    }
                    uint32_t *datatbl = *(uint32_t **)(base + 0x1f8);

                    uint32_t i8 = (uint32_t)*(uint8_t *)(rtbl + 0xc) * (uint32_t)id;
                    uint32_t o1 = i8 + *(uint32_t *)(rtbl + 8);
                    if ((o1 & 3) != 0 || st[0x80] <= o1) goto invalid_sart_offset;
                    *(uint32_t *)((uint8_t *)datatbl + o1) = 0;

                    uint32_t i9 = (uint32_t)*(uint8_t *)(rtbl + 0x24) * (uint32_t)id;
                    uint32_t o2 = i9 + *(uint32_t *)(rtbl + 0x20);
                    if ((o2 & 3) != 0 || st[0x80] <= o2) goto invalid_sart_offset;
                    *(uint32_t *)((uint8_t *)datatbl + o2) = 0;

                    uint32_t i15 = (uint32_t)*(uint8_t *)(rtbl + 0x18) * (uint32_t)id;
                    uint32_t o3 = i15 + *(uint32_t *)(rtbl + 0x14);
                    if ((o3 & 3) != 0 || st[0x80] <= o3) goto invalid_sart_offset;
                    *(uint32_t *)((uint8_t *)datatbl + o3) = 0;

                    /* Re-read the three offsets; require them all zeroed. */
                    uint32_t a1 = *(uint32_t *)(rtbl + 8) + i8;
                    uint32_t a2 = *(uint32_t *)(rtbl + 0x20) + i9;
                    uint32_t a3 = *(uint32_t *)(rtbl + 0x14) + i15;
                    if ((a1 & 3) != 0 || (a2 & 3) != 0 || (a3 & 3) != 0) goto invalid_sart_offset;
                    if (st[0x80] <= a1 || st[0x80] <= a2 || st[0x80] <= a3) goto invalid_sart_offset;
                    if (*(uint32_t *)((uint8_t *)datatbl + a2) != 0 ||
                        *(uint32_t *)((uint8_t *)datatbl + a1) != 0 ||
                        *(uint32_t *)((uint8_t *)datatbl + a3) != 0) {
                        sptm_panic_str("could not zero sart region");
                    }

                    /* Iterate the region's sub-entries (from +0x240 array). */
                    uint8_t *sub = *(uint8_t **)(base + 0x240);
                    uint64_t nsub = *sub;
                    if (nsub == 0) goto no_subentries;
                    uint8_t *p = sub + 0x18;
                    uint64_t left = nsub;
                    while (left != 0) {
                        uint32_t off = *(uint32_t *)p + st[0x82];
                        if ((off & 3) != 0 || st[0x80] <= off) goto invalid_sart_offset;
                        *(uint32_t *)((uint8_t *)datatbl + off) = 0;
                        left--;
                        p += 4;
                    }

                    /* Permission-restore bookkeeping. */
                    int b1 = 0;
                    left = nsub;
                    p = sub + 8;
                    do {
                        uint32_t off = *(uint32_t *)p + st[0x82];
                        if ((off & 3) != 0 || st[0x80] <= off) goto invalid_sart_offset;
                        b1 |= (*(uint32_t *)((uint8_t *)datatbl + off) &
                               *(uint32_t *)(sub + 0x28)) != 0;
                        left--;
                        p += 4;
                    } while (left != 0);

                    int b5 = 0;
                    left = nsub;
                    p = sub + 8;
                    do {
                        uint32_t off = *(uint32_t *)p + st[0x82];
                        if (st[0x80] <= off || (off & 3) != 0) goto invalid_sart_offset;
                        b5 |= (*(uint32_t *)((uint8_t *)datatbl + off) & 0x1010000) != 0;
                        left--;
                        p += 4;
                    } while (left != 0);

                    if ((!b1) || b5) {
                        /* Restore permissions from the saved perm table. */
                        p = sub + 0x18;
                        uint32_t *src = st + 0x8a;
                        left = nsub;
                        do {
                            uint32_t off = *(uint32_t *)p + st[0x82];
                            if ((off & 3) != 0 || st[0x80] <= off) goto invalid_sart_offset;
                            *(uint32_t *)((uint8_t *)datatbl + off) = *src;
                            left--;
                            p += 4;
                            src++;
                        } while (left != 0);
                    }

                    if (b1) {
                        /* Something was power-gated: flush + return 1. */
                        rv = 1;
                        guard_cpu = mi[sptm_cpu_id() + 10];
                        goto guard_release;
                    }
no_subentries:
                    /* ---- power canary check ---- */
                    if ((st[0x89] & 1) != 0) {
                        if (st[0x88] == 0) {
                            sptm_panic_str("power canary underflow");
                        }
                        if (*(int32_t *)(*(uint64_t *)((uint8_t *)st + 0x210) + st[0x87]) !=
                            -0x54012113) {
                            sptm_panic(0x200000c, 0, "power canary magic mismatch %llx");
                        }
                        st[0x88]--;
                    }
                    if (st[0x7c] == 0) goto region_underflow_panic;
                    st[0x7c]--;
                    goto free_entry;
                } else {
                    /* ---- multi-page region: deeper lookup ---- */
                    uint32_t lo = 0, lc = 0;
                    sptm_sart_region_lookup((uint32_t)id, &lo, (int *)&lc, (int *)&lo);
                    if (lo == 0 && lc < 2) {
                        if (st[0x7c] == 0) goto region_underflow_panic;
                        st[0x7c]--;
                        goto free_entry;
                    }
                    break; /* region not found → panic below */
                }
            }
            id++;
            r += 5;
            if (nreg == id) {
                break; /* not found */
            }
        }
    }

    sptm_panic(0x2000009, 0, "region not found %llx");

free_entry:
    /* Zero the 20-byte region entry, release large-region page refs. */
    sptm_memset(rentry, 0x14, 0xffffffffffffffffULL);
    if (0x3fff < sz) {
        uint64_t i = 1;
        uint64_t n = sz >> 0xe;
        while (i < n) {
            sptm_iommu_page_unref(va + i * 0x4000, ptype);
            i++;
        }
    }
    guard_cpu = mi[sptm_cpu_id() + 10];
    rv = 0;

guard_release:;
    /* (3) Release the region guard. */
    uint8_t g = *(uint8_t *)(base + 0x24a);
    if (g == (uint8_t)(guard_cpu << 1 | 1)) {
        *(uint8_t *)(base + 0x24a) = 0;
        return rv;
    }
    sptm_panic_str("state_guard_release %llx");

invalid_sart_offset:
    sptm_panic_str("Invalid SART offset x%x");
region_underflow_panic:
    sptm_panic_str("n_region_underflow");
}

/* ------------------------------------------------------------------ *
 * T8110 DART IOMMU driver (dispatch tables 3/4)
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * FUN_000cfaec @ 0x000cfaec   (est. sptm_t8110dart_map_table)
 * Ghidra: undefined FUN_000cfaec(byte, ulong, ulong, byte, ulong)
 * Map a page-table entry for a T8110 DART client: program `paddr` as the
 * table/leaf at `va` at the requested `level`. Validates the DART instance,
 * resolves the client, and for a not-yet-active client acquires its guard,
 * validates the VA range and that `paddr`'s FTE belongs to the same
 * instance/client/level, then walks the DART tables down to `level`
 * (allocating+retaining intermediate table pages as needed), programs the
 * leaf PTE (paddr>>4 & 0x3ffffffc00 | 1), and finishes with a DSB plus an
 * optional per-client TLB broadcast. The `level < no-2MB` case takes the
 * flush-only terminal path (no leaf write), per the decompile.
 * Confidence: low
 * Notes: client root table is the client struct page (entries at client[0..]);
 *   per-level VA index via sptm_pt_shifts/sptm_pt_shifts_lo; the terminal DSB
 *   block is shared by the small and the walk paths (LAB_000cff88).
 *   Security-relevant: paddr range checks (dart+0xb80 / 0x3ffffffffff) and the
 *   per-client guard protocol serialize all table edits.
 */
void sptm_t8110dart_map_table(uint8_t instance, uint64_t client_id, uint64_t va,
                              uint8_t level, uint64_t paddr)
{
    uint8_t *dart;
    uint64_t err = 0;
    uint8_t *client = NULL;
    uint8_t *guard = NULL;
    uint16_t *ptbl = NULL;
    uint64_t child_paddr = 0;
    uint32_t idx = 0;
    int small = 0;
    uint64_t cl_idx = client_id & 0xff;

    if (sptm_dart_valid_instances[instance] == 0xff) {
        sptm_panic(0x6000006, client_id, "invalid instance %llx");
    }

    void *dsg = sptm_dart_state_get();
    dart = *(uint8_t **)((uint8_t *)dsg + 0x10);

    if (*(int8_t *)(dart + 0xbe0) == 0) {
        sptm_panic(0x6000016, err, "dart disabled %llx");
    }

    /* (1) Resolve the client instance. */
    void *found = sptm_dart_instance_lookup(dart, (uint8_t)cl_idx);
    if (((uintptr_t)found & 1) == 0) {
        sptm_panic(0x6000009, err, "client not found %llx");
    }
    (void)found;

    /* (2) If the client's table is not yet active, set it up. */
    if (*(uint32_t *)(dart + 0xb98) <= cl_idx ||
        *(uint64_t *)(dart + cl_idx * 8 + 0x238) == 0 ||
        (*(uint8_t *)(*(uint64_t *)(dart + cl_idx * 8 + 0x238) + 0x1d) & 1) == 0) {

        client = *(uint8_t **)(dart + cl_idx * 8 + 0x238);
        guard = client + 0x1f;
        if (*guard != 0) {
            sptm_panic(0x6000001, err, "client guard busy %llx");
        }
        *guard = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);

        if (va >> 0x2a != 0) {
            sptm_panic(0x6000021, err, "va out of range %llx");
        }
        uint32_t vidx = (uint32_t)(va >> 0xe);
        if ((vidx < *(uint32_t *)(client + 0x14) || *(uint32_t *)(client + 0x10) <= vidx) &&
            (*(uint8_t *)(dart + 0xbec) & 1) == 0) {
            sptm_panic(0x600000e, err, "va out of range %llx");
        }

        if (level < 3 && (level != 0 || (*(uint8_t *)(client + 0x18) & 8) != 0)) {
            /* (3) Validate the leaf physical address's FTE. */
            sptm_paddr_validate(paddr, 0x18);
            uint16_t *pv = (uint16_t *)(sptm_window_base +
                                        ((paddr - sptm_mem_low) >> 10 & 0xffffffff0ULL));
            if ((sptm_window_base ^ (uintptr_t)pv) & 0xffc0000000000000ULL) {
                pv = (uint16_t *)((uintptr_t)pv & 0xffffffffffffULL | 0xc8a2000000000000ULL);
            }
            if (*(uint8_t *)((uint8_t *)pv + 4) != instance) {
                sptm_panic(0x6000008, err, "instance mismatch %llx");
            }
            if (*(uint8_t *)((uint8_t *)pv + 9) != (uint8_t)cl_idx) {
                sptm_panic(0x600000b, err, "client id mismatch %llx");
            }
            if (*(uint8_t *)((uint8_t *)pv + 5) != level) {
                sptm_panic(0x6000005, err, "level mismatch %llx");
            }

            ptbl = (uint16_t *)client;   /* root table = client page */
            small = (*(uint32_t *)(client + 0x18) & 8) == 0;

            if (level < (uint8_t)small) {
                goto dart_terminal;   /* flush-only path (no leaf write) */
            }

            /* (4) Walk down to the target level. */
            child_paddr = 0;
            uint64_t lvl = (uint64_t)small;
            for (;;) {
                uint8_t *cl = *(uint8_t **)(dart + cl_idx * 8 + 0x238);
                if (lvl == ((*(uint8_t *)(cl + 0x18) & 8) == 0)) {
                    idx = 0;
                } else {
                    idx = (uint32_t)((sptm_pt_shifts[lvl] & va >> 0xe) >>
                                     (sptm_pt_shifts_lo[lvl] & 0x3f));
                }
                uint64_t pte = *(uint64_t *)((uint8_t *)ptbl + (uint64_t)idx * 8);

                if (lvl == level) {
                    /* Target level: program the leaf PTE. */
                    if (pte != 0) {
                        sptm_panic(0x6000011, err, "entry already mapped %llx");
                    }
                    if (small == level) {
                        sptm_dart_pte_ref_update(dart, (uint8_t)cl_idx, paddr, 1);
                    } else {
                        /* Allocate + retain an intermediate table page. */
                        uint64_t *ar = *(uint64_t **)(cl + 8);
                        if (!(ar == NULL || child_paddr < *ar || ar[1] <= child_paddr)) {
                            goto in_range;
                        }
                        sptm_paddr_validate(child_paddr, 0x44);
                        ar = *(uint64_t **)(cl + 8);
                        if (ar != NULL) {
                            child_paddr = *ar;
                            goto in_range;
                        }
                        sptm_paddr_ref(child_paddr, 1);
                    }
                in_range:
                    /* Range-check the leaf paddr against the DART limit. */
                    if (*(uint64_t *)(dart + 0xb80) == 0) {
                        if (paddr > 0x3ffffffffffULL) {
                            sptm_panic(0x6000021, err, "paddr out of range %llx");
                        }
                    } else if (*(uint64_t *)(dart + 0xb80) <= paddr) {
                        sptm_panic(0x6000021, err, "paddr out of range %llx");
                    }
                    sptm_dmb_sy();
                    uint64_t *ar = *(uint64_t **)(cl + 8);
                    if ((ar == NULL || paddr < *ar || ar[1] <= paddr) &&
                        sptm_paddr_ref(paddr, 1) != 0) {
                        sptm_panic(0x600001e, err, "paddr validation failed %llx");
                    }
                    *(uint64_t *)((uint8_t *)ptbl + (uint64_t)idx * 8) =
                        (paddr >> 4 & 0x3ffffffc00ULL) | 1;
                    idx = idx & 0x3f;
                    goto dart_terminal;
                }

                /* Descend: current entry must point at a valid table. */
                if ((pte & 1) == 0 || (pte & 0x3ffffffc00) == 0) {
                    sptm_panic(0x6000012, err, "invalid intermediate table %llx");
                }
                child_paddr = (pte & 0x3ffffffc00) * 0x10;
                if (((uint32_t)sptm_mem_feature >> 8 & 1) == 0) {
                    ptbl = (uint16_t *)((child_paddr - sptm_mem_low) + sptm_direct_map_base);
                } else {
                    uint64_t cnt = sptm_region_count;
                    int found = 0;
                    if (cnt != 0) {
                        uint64_t *rg = sptm_regions;
                        do {
                            uint64_t b = rg[0];
                            if (b <= child_paddr && child_paddr < b + (uint32_t)rg[2] * 0x4000) {
                                ptbl = (uint16_t *)((child_paddr - b) + rg[1]);
                                found = 1;
                                break;
                            }
                            cnt--;
                            rg += 3;
                        } while (cnt != 0);
                    }
                    if (!found) {
                        ptbl = (uint16_t *)sptm_phystokv_outside_window(child_paddr);
                    }
                }
                lvl++;
            }
        }
        sptm_panic(0x6000003, err, "invalid level %llx");
    }

    sptm_panic(0x600001f, err, "client already active %llx");

dart_terminal:
    /* Shared terminal block: DSB, optional TLB broadcast, ref release. */
    sptm_dsb_sy();
    if (level == 1 &&
        (*(uint8_t *)(client + 0x18) >> 3 & 1) != 0 &&
        (*(uint8_t *)(dart + 0xbed) & 1) != 0 &&
        *(uint32_t *)(dart + 0xba4) != 0) {
        uint64_t n = *(uint32_t *)(dart + 0xba4);
        uint64_t off = 0;
        for (uint64_t i = 0; i < n; i++, off += 0x78) {
            *(uint32_t *)(*(uint64_t *)(dart + i * 8) + 0x600) =
                (uint32_t)((cl_idx << 24) | (idx << 12) | idx);
        }
        if (n != 0) {
            for (uint32_t i = 0; i < n; i++) {
                sptm_dart_client_tlb_invalidate(dart, i, 1, 0);
            }
        }
    }
    if (small != level && child_paddr != 0) {
        uint64_t *ar = *(uint64_t **)(client + 8);
        if (ar == NULL || child_paddr < *ar || ar[1] <= child_paddr) {
            sptm_paddr_release(child_paddr);
        }
    }
    sptm_paddr_release(paddr);

    uint8_t *g2 = *(uint8_t **)(dart + cl_idx * 8 + 0x238) + 0x1f;
    uint8_t expect = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);
    if (*g2 == expect) {
        *g2 = 0;
        return;
    }
    sptm_panic_str("state_guard_release %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000cef24 @ 0x000cef24   (est. sptm_t8110dart_unmap_table)
 * Ghidra: undefined FUN_000cef24(byte, ulong, ulong, ulong)
 * Unmap (release) the page-table entry at `va`/`level` for a T8110 DART
 * client. Validates the instance/client, and for an inactive client takes
 * its guard, validates the VA range and level, walks down to the target
 * level collecting each level's entry pointer, releases the leaf entry's
 * physical page reference, clears the leaf entry, issues the DART TLB
 * invalidate for the block (FUN_000cdd0c), and releases the leaf/root page
 * references.
 * Confidence: low
 * Notes: level 0 special case (leaf == root) invokes FUN_000cf7a8(dart, cl,
 *   0, 0); block size for the TLB invalidate is 1 << ((3-level)*0xb + 0xe).
 *   Parent page release path balances the intermediate-table retention.
 */
void sptm_t8110dart_unmap_table(uint8_t instance, uint64_t client_id, uint64_t va,
                                uint64_t level)
{
    uint8_t *dart;
    uint64_t err = 0;
    uint8_t *client;
    uint64_t cl_idx = client_id & 0xff;
    uint64_t *entries[4] = { NULL, NULL, NULL, NULL };

    if (sptm_dart_valid_instances[instance] == 0xff) {
        sptm_panic(0x6000006, client_id, "invalid instance %llx");
    }

    void *dsg = sptm_dart_state_get();
    dart = *(uint8_t **)((uint8_t *)dsg + 0x10);

    if (*(int8_t *)(dart + 0xbe0) == 0) {
        sptm_panic(0x6000016, err, "dart disabled %llx");
    }

    void *found = sptm_dart_instance_lookup(dart, (uint8_t)cl_idx);
    if (((uintptr_t)found & 1) == 0) {
        sptm_panic(0x6000009, err, "client not found %llx");
    }
    (void)found;

    /* An active client's table cannot be unmapped. */
    if (cl_idx < *(uint32_t *)(dart + 0xb98) &&
        *(uint64_t *)(dart + cl_idx * 8 + 0x238) != 0 &&
        (*(uint8_t *)(*(uint64_t *)(dart + cl_idx * 8 + 0x238) + 0x1d) & 1) != 0) {
        sptm_panic(0x600001f, err, "client already active %llx");
    }

    client = *(uint8_t **)(dart + cl_idx * 8 + 0x238);
    uint8_t *guard = client + 0x1f;
    if (*guard != 0) {
        sptm_panic(0x6000001, err, "client guard busy %llx");
    }
    *guard = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);

    if (va >> 0x2a != 0) {
        sptm_panic(0x6000021, err, "va out of range %llx");
    }
    uint32_t vidx = (uint32_t)(va >> 0xe);
    if ((vidx < *(uint32_t *)(client + 0x14) || *(uint32_t *)(client + 0x10) <= vidx) &&
        (*(uint8_t *)(dart + 0xbec) & 1) == 0) {
        sptm_panic(0x600000e, err, "va out of range %llx");
    }

    uint32_t flags = *(uint32_t *)(client + 0x18);
    uint8_t lvl8 = (uint8_t)level;
    if (lvl8 > 2 || (lvl8 == 0 && (flags & 8) == 0)) {
        sptm_panic(0x6000003, err, "invalid level %llx");
    }
    int small = (flags & 8) == 0;

    uint16_t *ptbl = (uint16_t *)client;
    if ((uint32_t)small <= lvl8) {
        /* Walk down to the target level, recording each entry pointer. */
        uint64_t lvl = (uint64_t)small;
        do {
            uint32_t idx;
            if (lvl == ((*(uint8_t *)(client + 0x18) & 8) == 0)) {
                idx = 0;
            } else {
                idx = (uint32_t)((sptm_pt_shifts[lvl] & va >> 0xe) >>
                                 (sptm_pt_shifts_lo[lvl] & 0x3f));
            }
            uint64_t *ep = (uint64_t *)((uint8_t *)ptbl + (uint64_t)idx * 8);
            entries[lvl] = ep;
            uint64_t v = *ep;
            if ((v & 1) == 0 || (v & 0x3ffffffc00) == 0) {
                sptm_panic(0x6000012, err, "invalid intermediate table %llx");
            }
            uint64_t cp = (v & 0x3ffffffc00) * 0x10;
            if (((uint32_t)sptm_mem_feature >> 8 & 1) == 0) {
                ptbl = (uint16_t *)((cp - sptm_mem_low) + sptm_direct_map_base);
            } else {
                uint64_t cnt = sptm_region_count;
                int found = 0;
                if (cnt != 0) {
                    uint64_t *rg = sptm_regions;
                    do {
                        uint64_t b = rg[0];
                        if (b <= cp && cp < b + (uint32_t)rg[2] * 0x4000) {
                            ptbl = (uint16_t *)((cp - b) + rg[1]);
                            found = 1;
                            break;
                        }
                        cnt--;
                        rg += 3;
                    } while (cnt != 0);
                }
                if (!found) {
                    ptbl = (uint16_t *)sptm_phystokv_outside_window(cp);
                }
            }
            lvl++;
        } while (((uint32_t)lvl & 0xff) != ((uint32_t)(lvl8 + 1) & 0xff));
    }

    /* (Leaf entry = the one at the target level.) */
    uint64_t *leaf = entries[lvl8];
    uint64_t leaf_paddr = (*leaf & 0x3ffffffc00) << 4;

    uint64_t *ar = *(uint64_t **)(client + 8);
    if ((ar != NULL && *ar <= leaf_paddr) && (leaf_paddr < ar[1])) {
        goto leaf_in_range;
    }
    sptm_paddr_validate(leaf_paddr, 0x44);
    /* parent paddr: the entry above the target level (or none at root). */
    uint64_t parent_paddr;
    if ((uint32_t)small == lvl8) {
        parent_paddr = 0;
    } else {
        uint64_t *parent = entries[lvl8 - 1];
        parent_paddr = (*parent & 0x3ffffffc00) << 4;
        ar = *(uint64_t **)(client + 8);
        if ((ar == NULL || parent_paddr < *ar) || (ar[1] <= parent_paddr)) {
            sptm_paddr_validate(parent_paddr, 0x44);
        }
    }

    ar = *(uint64_t **)(client + 8);
    if (((ar != NULL && *ar <= leaf_paddr) && (leaf_paddr < ar[1])) ||
        sptm_paddr_ref(leaf_paddr, 0xffffffff) != 1) {
        sptm_panic(0x600001c, err, "leaf release failed %llx");
    }
leaf_in_range:
    *leaf = 0;

    if ((uint32_t)small == lvl8) {
        /* Leaf is the root table: reset the client's table ref. */
        sptm_dart_pte_ref_update(dart, (uint8_t)cl_idx, 0, 0);
    } else {
        /* Issue the DART TLB invalidate for the block. */
        sptm_dsb_sy();
        uint64_t block = 1ULL << (((3 - lvl8) * 0xb + 0xe) & 0x3f);
        uint64_t va0 = va & ~(block - 1);
        uint64_t va1 = va0 + block;
        if (va1 >> 0x2a != 0) {
            sptm_panic(0x6000021, err, "va out of range %llx");
        }
        sptm_dart_tlb_invalidate(dart, (uint8_t)cl_idx, va0 >> 0xe,
                                 (int)(va1 >> 0xe) - 1, 1);
        ar = *(uint64_t **)(client + 8);
        if ((ar == NULL || parent_paddr < *ar) || (ar[1] <= parent_paddr)) {
            sptm_paddr_ref(parent_paddr, 0xffffffff);
            ar = *(uint64_t **)(client + 8);
            if (ar != NULL && *ar <= parent_paddr && parent_paddr < ar[1]) {
                goto parent_ok;
            }
            sptm_paddr_release(parent_paddr);
        }
    }
parent_ok:
    ar = *(uint64_t **)(client + 8);
    if ((ar == NULL || leaf_paddr < *ar) || (ar[1] <= leaf_paddr)) {
        sptm_paddr_release(leaf_paddr);
    }

    /* Release the client guard. */
    uint8_t *g2 = *(uint8_t **)(dart + cl_idx * 8 + 0x238) + 0x1f;
    uint8_t expect = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);
    if (*g2 == expect) {
        *g2 = 0;
        sptm_stack_check();
        return;
    }
    sptm_panic_str("state_guard_release %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000cd0bc @ 0x000cd0bc   (est. sptm_t8110dart_unmap)
 * Ghidra: undefined FUN_000cd0bc(byte, ulong, ulong, ulong, uint)
 * Unmap a range [va, va+size) of DART entries for a T8110 DART client.
 * Validates the instance/client/size, takes the client guard, walks the
 * 16KB-granule blocks in the range clearing each present entry (rejecting a
 * mix of WR directions, and rejecting absent blocks unless flag bit 1 is
 * set), collects the released physical pages into the handoff, issues the
 * DART TLB invalidate, then releases the IOMMU page references for the
 * collected blocks and the leaf table page.
 * Confidence: low
 * Notes: each present block's page type (4KB/2MB) is derived from PTE bit 2;
 *   the "= block-present" check rejects a stale block via FTE type byte +1;
 *   size limit 0x2000000; flag bit 0 requires dart+0xbef (permission config).
 */
void sptm_t8110dart_unmap(uint8_t instance, uint64_t client_id, uint64_t va,
                          uint64_t size, uint32_t flags)
{
    uint8_t *dart;
    uint64_t err = 0;
    uint64_t cl_idx = client_id & 0xff;

    if (sptm_dart_valid_instances[instance] == 0xff) {
        sptm_panic(0x6000006, client_id, "invalid instance %llx");
    }

    void *dsg = sptm_dart_state_get();
    dart = *(uint8_t **)((uint8_t *)dsg + 0x10);

    if (*(int8_t *)(dart + 0xbe0) == 0) {
        sptm_panic(0x6000016, err, "dart disabled %llx");
    }

    void *found = sptm_dart_instance_lookup(dart, (uint8_t)cl_idx);
    if (((uintptr_t)found & 1) == 0) {
        sptm_panic(0x6000009, err, "client not found %llx");
    }
    (void)found;

    if (cl_idx < *(uint32_t *)(dart + 0xb98) &&
        *(uint64_t *)(dart + cl_idx * 8 + 0x238) != 0 &&
        (*(uint8_t *)(*(uint64_t *)(dart + cl_idx * 8 + 0x238) + 0x1d) & 1) != 0) {
        sptm_panic(0x600001f, err, "client already active %llx");
    }
    if (size > 0x2000000) {
        sptm_panic(0x600000c, client_id, "size too large %llx");
    }
    if ((*(uint8_t *)(dart + 0xbef) & 1) == 0 && (flags & 1) != 0) {
        sptm_panic(0x6000013, err, "clear-not-allowed %llx");
    }

    uint8_t *client = *(uint8_t **)(dart + cl_idx * 8 + 0x238);
    uint8_t *guard = client + 0x1f;
    if (*guard != 0) {
        sptm_panic(0x6000001, err, "client guard busy %llx");
    }
    *guard = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);

    if (va >> 0x2a != 0) {
        sptm_panic(0x6000021, err, "va out of range %llx");
    }
    uint32_t s_idx = (uint32_t)(va >> 0xe);
    if ((s_idx < *(uint32_t *)(client + 0x14) || *(uint32_t *)(client + 0x10) <= s_idx) &&
        (*(uint8_t *)(dart + 0xbec) & 1) == 0) {
        sptm_panic(0x600000e, err, "va out of range %llx");
    }

    uint64_t end = va + size;
    if (end >> 0x2a != 0) {
        sptm_panic(0x6000021, err, "va out of range %llx");
    }
    uint32_t e_idx = (uint32_t)(end >> 0xe);
    if ((e_idx < *(uint32_t *)(client + 0x14) || *(uint32_t *)(client + 0x10) <= e_idx) &&
        (*(uint8_t *)(dart + 0xbec) & 1) == 0) {
        sptm_panic(0x600000e, err, "va out of range %llx");
    }
    if ((va & 0x3fffe000000ULL) + 0x2000000 < end) {
        sptm_panic(0x600000f, err, "range too wide %llx");
    }

    /* (1) Walk to the leaf table for the start VA. */
    uint64_t leaf_paddr = 0;
    uint16_t *ptbl = (uint16_t *)sptm_dart_va_to_pte(dart, (uint8_t)cl_idx, va, &leaf_paddr);
    uint64_t *ar = *(uint64_t **)(client + 8);
    if ((ar == NULL || leaf_paddr < *ar) || (ar[1] <= leaf_paddr)) {
        sptm_paddr_validate(leaf_paddr, 0x44);
    }

    uint64_t *handoff = sptm_handoff_ptr();
    uint64_t ncollected = 0;
    uint32_t ptype = 1;

    if (va < end) {
        uint32_t prev_wr = 0xffffffff;
        do {
            uint32_t bi = (uint32_t)(va >> 0xe & 0x7ff);
            uint64_t pte = *(uint64_t *)((uint8_t *)ptbl + (uint64_t)bi * 8);
            if ((pte & 1) == 0) {
                /* Absent block: must be permitted by flag bit 1. */
                if ((flags >> 1 & 1) == 0) {
                    sptm_panic(0x6000022, err, "block not present %llx");
                }
            } else {
                uint64_t bp = (pte & 0x3ffffffc00) * 0x10;
                uint16_t *bv = sptm_paddr_to_va(bp);
                if (*(int8_t *)((uint8_t *)bv + 1) == '=') {
                    sptm_panic(0x6000024, err, "block FTE stale %llx");
                }
                handoff[ncollected] = bp;
                uint32_t wr = (uint32_t)(pte >> 2 & 1);
                if (prev_wr != 0xffffffff && prev_wr != wr) {
                    sptm_panic(0x6000014, err, "mixed WR directions %llx");
                }
                *(uint64_t *)((uint8_t *)ptbl + (uint64_t)bi * 8) = 0;
                ncollected++;
                prev_wr = wr;
            }
            va = (va & 0x3ffffffc000ULL) + 0x4000;
        } while (va < end);
        ptype = (prev_wr == 0) ? 2 : 1;
    }

    /* (2) TLB invalidate the range. */
    sptm_dsb_sy();
    if (((end + 0x3fff) >> 0x2a & 1) != 0) {
        sptm_panic(0x6000021, err, "va out of range %llx");
    }
    sptm_dart_tlb_invalidate(dart, (uint8_t)cl_idx, s_idx,
                             (int)((end + 0x3fff) >> 0xe) - 1, 0);

    /* (3) Release the collected block pages. */
    if (ncollected != 0) {
        uint64_t left = ncollected;
        do {
            sptm_iommu_page_unref(*handoff, ptype);
            left--;
            handoff++;
        } while (left != 0);
    }

    /* (4) Release the leaf table page. */
    ar = *(uint64_t **)(client + 8);
    if ((ar == NULL || leaf_paddr < *ar) || (ar[1] <= leaf_paddr)) {
        sptm_paddr_ref(leaf_paddr, (uint32_t)(-(int64_t)ncollected));
        ar = *(uint64_t **)(client + 8);
        if (ar != NULL && *ar <= leaf_paddr && leaf_paddr < ar[1]) {
            goto leaf_ok;
        }
        sptm_paddr_release(leaf_paddr);
    }
leaf_ok:
    ar = *(uint64_t **)(client + 8);
    if ((ar == NULL || leaf_paddr < *ar) || (ar[1] <= leaf_paddr)) {
        sptm_paddr_release(leaf_paddr);
    }

    /* (5) Release the client guard. */
    uint8_t *g2 = *(uint8_t **)(dart + cl_idx * 8 + 0x238) + 0x1f;
    uint8_t expect = (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);
    if (*g2 != expect) {
        sptm_panic_str("state_guard_release %llx");
    }
    *g2 = 0;
}

/* ------------------------------------------------------------------ *
 * UAT unification-table driver (dispatch table 7)
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * FUN_000b5fd0 @ 0x000b5fd0   (est. sptm_uat_init_state)
 * Ghidra: undefined FUN_000b5fd0(undefined8, undefined8, long)
 * Initialize a UAT state with one or two root tables. Validates the state is
 * not already live (panic 0x4000003 if type 1 and a second root given), marks
 * the root-table FTEs "in setup" (type 2), then for an unset root installs
 * the root paddr(s), takes references on the state and roots, and releases
 * the temporary references. Falls to the cleanup path if a root is already
 * present.
 * Confidence: low
 * Notes: state types: 1/4 carry one/two roots; second-root FTE is validated
 *   to type 1 too. State guard at +0x1a transitions 1 -> 2.
 */
void sptm_uat_init_state(uint64_t state_id, uint64_t root1_paddr, uint64_t root2_paddr)
{
    uint8_t *st = sptm_uat_state_get(state_id, 0, 5);

    if (*st == 1 && root2_paddr != 0xffffffffffffffffULL) {
        sptm_panic(0x4000003, 0, "already initialized %llx");
    }

    /* Validate + mark the first root table FTE. */
    uint64_t root1 = sptm_uat_table_translate(root1_paddr, 1);
    uint64_t root2 = 0xffffffffffffffffULL;
    if (*st == 4) {
        root2 = sptm_uat_table_translate(root2_paddr, 1);
    }

    uint16_t *r1v = sptm_paddr_to_va(root1);
    if (*(uint8_t *)((uint8_t *)r1v + 4) != 1) {
        sptm_panic(0x4000000, 0, "root not available %llx");
    }
    *(uint8_t *)((uint8_t *)r1v + 4) = 2;

    uint8_t b = *st;
    if (b == 4) {
        uint16_t *r2v = sptm_paddr_to_va(root2);
        if (*(uint8_t *)((uint8_t *)r2v + 4) != 1) {
            sptm_panic(0x4000000, 0, "root not available %llx");
        }
        *(uint8_t *)((uint8_t *)r2v + 4) = 2;
        b = *st;
    }
    if ((b & 5) == 0) {
        sptm_panic_str("%d is not a valid UAT state");
    }

    if (*(uint64_t *)(st + 8) == 0xffffffffffffffffULL) {
        /* Install the root table(s). */
        if (b == 4) {
            if (*(uint64_t *)(st + 0x10) != 0xffffffffffffffffULL) {
                goto non_zero_root_panic;
            }
            *(uint64_t *)(st + 8) = root1;
            *(uint64_t *)(st + 0x10) = root2;
        } else {
            *(uint64_t *)(st + 8) = root1;
        }
        sptm_paddr_ref(state_id, 1);
        sptm_paddr_ref(root1, 1);
        if (*st == 4) {
            sptm_paddr_ref(root2, 1);
        }
        if (st[0x1a] != 1) {
            sptm_panic_str("state_guard_release %llx");
        }
        st[0x1a] = 2;
        if ((*st & 5) != 0) {
            sptm_kvtophys(st);
            sptm_paddr_release(0);
        }
        sptm_paddr_release(root1);
        if (*st == 4) {
            sptm_paddr_release(root2);
        }
        return;
    }

    sptm_uat_cleanup(st, 0);

non_zero_root_panic:
    sptm_panic_str("Non-zero root table paddr in %s");
}

/* ------------------------------------------------------------------ *
 * FUN_000b5be0 @ 0x000b5be0   (est. sptm_uat_destroy_state)
 * Ghidra: undefined FUN_000b5be0(undefined8)
 * Destroy a UAT state: validate its root table FTEs are "in setup" (type 2),
 * mark them "destroying" (type 3), require the ctx id be unset (-1), release
 * the references on the state id and roots, and zero the root fields.
 * Confidence: low
 * Notes: root fields (+8 / +0x10) reset to 0xffffffff00000000; the ctx id at
 *   +0x18 must be -1 (0x4000006 otherwise); state guard +0x1a 1 -> 0.
 */
void sptm_uat_destroy_state(uint64_t state_id)
{
    uint8_t *st = sptm_uat_state_get(state_id, 2, 5);

    if ((*st & 5) != 0) {
        uint64_t root1 = *(uint64_t *)(st + 8);
        sptm_paddr_validate(root1, 0x18);
        uint64_t root2;
        if (*st == 4) {
            root2 = *(uint64_t *)(st + 0x10);
            sptm_paddr_validate(root2, 0x18);
        } else {
            root2 = 0xffffffffffffffffULL;
        }

        int r1 = sptm_paddr_ref(root1, 0xffffffff);
        if (r1 != 1 || (*st == 4 && sptm_paddr_ref(root2, 0xffffffff) != 1)) {
            sptm_panic(0x4000007, 0, "root release failed %llx");
        }

        uint16_t *r1v = sptm_paddr_to_va(root1);
        if (*(uint8_t *)((uint8_t *)r1v + 4) != 2) {
            sptm_panic(0x4000000, 0, "root not in setup %llx");
        }
        *(uint8_t *)((uint8_t *)r1v + 4) = 3;
        uint8_t b = *st;
        if (b == 4) {
            uint16_t *r2v = sptm_paddr_to_va(root2);
            if (*(uint8_t *)((uint8_t *)r2v + 4) != 2) {
                sptm_panic(0x4000000, 0, "root not in setup %llx");
            }
            *(uint8_t *)((uint8_t *)r2v + 4) = 3;
            b = *st;
        }

        if ((b & 5) != 0) {
            /* Reset the root paddr fields to 0xffffffff00000000. */
            uint64_t *r = (uint64_t *)(st + 8);
            r[0] = 0xffffffff00000000ULL;
            if (b == 4) {
                r[1] = 0xffffffff00000000ULL;
            }
            if (*(uint16_t *)(st + 0x18) != 0xffff) {
                sptm_panic(0x4000006, 0, "ctx id still set %llx");
            }
            sptm_paddr_ref(state_id, 0xffffffff);
            sptm_paddr_release(root1);
            if (*st == 4) {
                sptm_paddr_release(root2);
            }
            if (st[0x1a] != 1) {
                sptm_panic_str("state_guard_release %llx");
            }
            st[0x1a] = 0;
            if ((*st & 5) == 0) {
                return;
            }
            sptm_kvtophys(st);
            sptm_paddr_release(0);
            return;
        }
    }
    sptm_panic_str("%d is not a valid UAT state");
}

/* ------------------------------------------------------------------ *
 * FUN_000b5904 @ 0x000b5904   (est. sptm_uat_map_table)
 * Ghidra: undefined FUN_000b5904(undefined8, undefined8, char, undefined8)
 * Map a page-table entry at `va` (level 1/2) for a UAT state, pointing at
 * `table_paddr`. Validates the level, walks to the target entry (via the
 * per-state root), and programs it with (table_paddr>>12 & mask) | 3.
 * Confidence: low
 * Notes: table type is 4 (level 1) or 5 (level 2) via sptm_uat_table_translate;
 *   root selected by the level of `va` (offset bit test against uat+0x1a1);
 *   state must be type 5 or 0xe. Entry write is (paddr & 0x1fffffff000) | 3.
 */
void sptm_uat_map_table(uint64_t state_id, uint64_t va, uint8_t level, uint64_t table_paddr)
{
    uint8_t *st = sptm_uat_state_get(state_id, 2, 0xf);
    uint64_t off = 0;
    sptm_uat_va_walk(va, 0x4000, st, &off);

    if ((uint8_t)(level - 3) < 0xfe) {
        sptm_panic(0x400000a, 0, "invalid level %llx");
    }
    int tbltype = (level == 1) ? 4 : 5;
    uint64_t tp = sptm_uat_table_translate(table_paddr, tbltype);

    long entry_va = 0;
    uint64_t off_shift = off >> (sptm_uat_driver_state[0x1a1] & 0x3f);
    uint8_t state_mask = ((off_shift & 1) != 0) ? 0xe : 5;
    if ((state_mask & *st) == 0) {
        sptm_panic_str("%d is not a valid UAT state");
    }

    uint64_t *root = (uint64_t *)(st + ((off_shift & 1) * 8) + 8);
    uint64_t *entry = sptm_uat_walk_entry(*root, va, (char)level, &entry_va);

    if ((*entry & 3) == 0) {
        sptm_panic(0x400000c, 0, "entry not free %llx");
    }

    long ep = entry_va;
    if (entry_va != *(long *)(sptm_uat_driver_state + 0x108)) {
        sptm_paddr_validate((uint64_t)entry_va, 0x18);
        sptm_paddr_ref((uint64_t)ep, 1);
        sptm_paddr_release((uint64_t)ep);
    }

    if (sptm_paddr_ref(tp, 1) != 0) {
        sptm_panic(0x400000f, 0, "table ref failed %llx");
    }
    sptm_dmb_sy();
    *entry = (tp & 0x1fffffff000ULL) | 3;
    sptm_paddr_release(tp);

    if (st[0x1a] != 1) {
        sptm_panic_str("state_guard_release %llx");
    }
    st[0x1a] = 2;
    if ((*st & 5) != 0) {
        sptm_kvtophys(st);
        sptm_paddr_release(0);
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000b5608 @ 0x000b5608   (est. sptm_uat_unmap_table)
 * Ghidra: undefined FUN_000b5608(undefined8, undefined8, char)
 * Unmap the page-table entry at `va` (level 1/2) for a UAT state: clear the
 * entry, TLB-invalidate the 16KB block, and release the table page and (if
 * non-root) the parent table page references.
 * Confidence: low
 * Notes: entry must be present (0x400000c otherwise); the parent-table
 *   release path panics "Parent_page_table_has_a_zero" if its ref is 0.
 */
void sptm_uat_unmap_table(uint64_t state_id, uint64_t va, uint8_t level)
{
    uint8_t *st = sptm_uat_state_get(state_id, 2, 0xf);
    uint64_t off = 0;
    sptm_uat_va_walk(va, 0x4000, st, &off);

    if ((uint8_t)(level - 3) < 0xfe) {
        sptm_panic(0x400000a, 0, "invalid level %llx");
    }

    long entry_va = 0;
    uint64_t off_shift = off >> (sptm_uat_driver_state[0x1a1] & 0x3f);
    uint8_t state_mask = ((off_shift & 1) != 0) ? 0xe : 5;
    if ((state_mask & *st) == 0) {
        sptm_panic_str("%d is not a valid UAT state");
    }

    uint64_t *root = (uint64_t *)(st + ((off_shift & 1) * 8) + 8);
    uint64_t *entry = sptm_uat_walk_entry(*root, va, (char)level, &entry_va);
    uint64_t pte = *entry;
    if ((pte & 3) == 0) {
        sptm_panic(0x400000c, 0, "entry not present %llx");
    }

    uint64_t tbl_paddr = pte & 0xfffffffff000ULL;
    sptm_paddr_validate(tbl_paddr, 0x18);
    *entry = 0;

    sptm_dsb_sy();
    sptm_uat_tlb_invalidate(st, off, 0x4000, 0);
    long ep = entry_va;
    sptm_dsb_ish();

    if (entry_va != *(long *)(sptm_uat_driver_state + 0x108)) {
        sptm_paddr_validate((uint64_t)entry_va, 0x18);
        if (sptm_paddr_ref((uint64_t)ep, 0xffffffff) == 0) {
            sptm_panic_str("Parent page table has a zero %s");
        }
        sptm_paddr_release((uint64_t)ep);
    }

    if (sptm_paddr_ref(tbl_paddr, 0xffffffff) != 1) {
        sptm_panic(0x400000f, 0, "table release failed %llx");
    }
    sptm_paddr_release(tbl_paddr);

    if (st[0x1a] != 1) {
        sptm_panic_str("state_guard_release %llx");
    }
    st[0x1a] = 2;
    if ((*st & 5) != 0) {
        sptm_kvtophys(st);
        sptm_paddr_release(0);
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000b32d0 @ 0x000b32d0   (est. sptm_uat_unmap_continue)
 * Ghidra: undefined8 FUN_000b32d0(undefined8)
 * Continue an in-progress UAT unmap. A state machine driven by the unmap
 * phase byte at state+0x20: phase 1 runs the leaf-unmap walker
 * (sptm_uat_unmap_walk with the leaf callback); phase 2 TLB-invalidates the
 * pending tables and transitions to phase 3/4; phase 3 clears the context-id
 * in the per-cpu UAT table and transitions to phase 4; phase 4 runs the
 * table-unmap walker (table callback) and finishes. Returns 1 when the unmap
 * is complete, else 0.
 * Confidence: low
 * Notes: pending-table list at state+600 (pairs of paddr/length<<0xe, count at
 *   +0x28); boot-stage check against sptm_boot_stage / sptm_boot_config_table
 *   with halt_baddata on invalid stage; phase 3 clears entry at
 *   uat[0x138] + ctx*0x18 + 0x20 when not global.
 */
uint64_t sptm_uat_unmap_continue(uint64_t state_id)
{
    uint8_t *st = sptm_uat_state_get(state_id, 5, 0xf);
    uint64_t ret = 0;
    long walk_out = 0;

    uint8_t phase = st[0x20];

    if (phase == 2) {
        /* ---- phase 2: TLB-invalidate pending tables ---- */
        long npend = *(long *)(st + 0x28);
        sptm_dsb_sy();
        if (npend != 0) {
            uint8_t *p = st + 600;
            do {
                sptm_uat_tlb_invalidate(st, *(uint64_t *)(p - 8),
                                        *(uint64_t *)p << 0xe, 1);
                p += 0x10;
                npend--;
            } while (npend != 0);
        }
        if (sptm_sapt_bootstrapped == 0) {
            sptm_panic_str("SAPT not bootstrapped");
        }
        if (((uint32_t)sptm_mem_feature >> 0xb & 1) == 0) {
            sptm_panic_str("Expected bootstrap stages not reached");
        }
        if (sptm_boot_config_table[sptm_boot_stage * 0x28] > 1) {
            if (*(uint64_t *)(st + 0x248) > 0x3f) {
                __builtin_trap(); /* halt_baddata */
            }
            if (*(uint64_t *)(st + 0x248) != 0) {
                __builtin_trap(); /* halt_baddata */
            }
        }
        /* zero the 8-byte boot-stage marker at +0x248 */
        *(uint64_t *)(st + 0x248) = 0;
        sptm_dsb_ish();

        phase = (uint8_t)((sptm_boot_thing & 1) + 3);
        if ((st[0x40] & 1) == 0) {
            phase = 4;
        }
        st[0x20] = phase;
    }

    if (phase == 1) {
        /* ---- phase 1: leaf-unmap walker ---- */
        uint64_t r = sptm_uat_unmap_walk(st, &walk_out, (void *)sptm_uat_unmap_cb_leaf);
        ret = r;
        if ((r & 1) != 0) {
            /* walker finished: return 1 */
            phase = 5;
            ret = 1;
            goto guard_release;
        }
        /* not done: move to phase 2 unless at a table boundary */
        st[0x20] = 2;
        if (walk_out == *(long *)(sptm_uat_driver_state + 0x1b8)) {
            goto guard_release; /* table boundary reached */
        }
        goto phase2_from_leaf;
    }

phase2_from_leaf:
    /* (re-enter phase 2 body) */
    {
        long npend = *(long *)(st + 0x28);
        sptm_dsb_sy();
        if (npend != 0) {
            uint8_t *p = st + 600;
            do {
                sptm_uat_tlb_invalidate(st, *(uint64_t *)(p - 8),
                                        *(uint64_t *)p << 0xe, 1);
                p += 0x10;
                npend--;
            } while (npend != 0);
        }
        if (sptm_sapt_bootstrapped == 0) {
            sptm_panic_str("SAPT not bootstrapped");
        }
        if (((uint32_t)sptm_mem_feature >> 0xb & 1) == 0) {
            sptm_panic_str("Expected bootstrap stages not reached");
        }
        if (sptm_boot_config_table[sptm_boot_stage * 0x28] > 1) {
            if (*(uint64_t *)(st + 0x248) > 0x3f) {
                __builtin_trap();
            }
            if (*(uint64_t *)(st + 0x248) != 0) {
                __builtin_trap();
            }
        }
        *(uint64_t *)(st + 0x248) = 0;
        sptm_dsb_ish();
        phase = (uint8_t)((sptm_boot_thing & 1) + 3);
        if ((st[0x40] & 1) == 0) {
            phase = 4;
        }
        st[0x20] = phase;
    }

    if (phase == 4) {
        uint64_t r = sptm_uat_unmap_walk(st, &walk_out, (void *)sptm_uat_unmap_cb_table);
        if ((r & 1) != 0) {
            phase = 5;
            ret = 1;
            goto guard_release;
        }
        st[0x20] = 0;
        ret = 0;
        phase = 2;
        goto guard_release;
    } else if (phase == 3) {
        /* ---- phase 3: clear the context-id entry ---- */
        if (*(uint16_t *)(st + 0x18) > 0x40) {
            sptm_panic_str("Context ID not set despite ctx table");
        }
        uint64_t ctx = *(uint16_t *)(st + 0x18);
        int32_t *ent = (int32_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x138) +
                                   ctx * 0x18 + 0x20);
        if ((*(uint8_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x138) + 0x638) & 1) == 0 &&
            *ent == 1) {
            sptm_panic(0x4000016, 0, "ctx entry in use %llx");
        }
        *ent = 0;
        sptm_dmb_sy();
        st[0x20] = 4;
        goto phase4;
    }

    /* bVar4 not 1/2/3/4: fall through with ret=0, phase=2 */
    ret = 0;
    phase = 2;
    goto guard_release;

phase4:
    {
        uint64_t r = sptm_uat_unmap_walk(st, &walk_out, (void *)sptm_uat_unmap_cb_table);
        if ((r & 1) != 0) {
            phase = 5;
            ret = 1;
            goto guard_release;
        }
        st[0x20] = 0;
        ret = 0;
        phase = 2;
        goto guard_release;
    }

guard_release:
    if (st[0x1a] == 1) {
        st[0x1a] = phase;
        if ((*st & 5) != 0) {
            sptm_kvtophys(st);
            sptm_paddr_release(0);
        }
        return ret;
    }
    sptm_panic_str("state_guard_release %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000b2f54 @ 0x000b2f54   (est. sptm_uat_set_ctx_id)
 * Ghidra: undefined FUN_000b2f54(undefined8, ushort)
 * Bind a UAT state to a hardware context id (0-63): take the per-CPU UAT
 * ctx-id guard (uat+0x60), set the state's ctx id, and program the two
 * VTTBR entries (uat[0x78] + ctx*0x10) with the state's root-table paddr
 * (shared-mode-aware), publishing them with a DMB.
 * Confidence: low
 * Notes: ctx entries carry the present bit in both words; the vttbr0 word
 *   uses the state root (+8) and vttbr1 the shared root (+0x10); uat+0x10
 *   distinguishes shared mode; state types 1/5 (mask 5) and 2/... (mask 0xe).
 */
void sptm_uat_set_ctx_id(uint64_t state_id, uint16_t ctx_id)
{
    uint8_t *st = sptm_uat_state_get(state_id, 2, 5);
    if (ctx_id > 0x3f) {
        sptm_panic(0x4000017, 0, "invalid ctx id %llx");
    }

    if (*(uint16_t *)(st + 0x18) == 0xffff) {
        /* No ctx id bound yet. */
        if (*(uint8_t *)(sptm_uat_driver_state + 0x60) != 0) {
            sptm_panic(0x400001a, 0, "ctx guard busy %llx");
        }
        *(uint8_t *)(sptm_uat_driver_state + 0x60) =
            (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);
        *(uint16_t *)(st + 0x18) = ctx_id;

        uint64_t *ttb = (uint64_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x78) +
                                     (uint64_t)ctx_id * 0x10);
        uint64_t ci = ctx_id;

        if (((ttb[0] | ttb[1]) & 1) == 0) {
            /* ctx entry free: program vttbr0/vttbr1. */
            uint8_t b = *st;
            if ((b & 5) != 0) {
                uint8_t *src = st;
                if (b == 1) {
                    if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 0) {
                        sptm_panic_str("Accessing Shared Mode global");
                    }
                    src = *(uint8_t **)(sptm_uat_driver_state + 0x18);
                }
                if ((*src & 0xe) != 0) {
                    uint64_t shared = *(uint64_t *)(src + 0x10);
                    ttb[0] = (*(uint64_t *)(st + 8) & 0x3ffffffc000ULL) |
                             ((ci & 0x7fff) << 0x30) | 1;
                    ttb[1] = (ci << 0x30) | (shared & 0x3ffffffc000ULL) | 1;
                    sptm_dmb_sy();

                    if (*(uint8_t *)(sptm_uat_driver_state + 0x60) ==
                        (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1)) {
                        *(uint8_t *)(sptm_uat_driver_state + 0x60) = 0;
                        if (st[0x1a] == 1) {
                            st[0x1a] = 2;
                            if ((*st & 5) == 0) {
                                return;
                            }
                            sptm_kvtophys(st);
                            sptm_paddr_release(0);
                            return;
                        }
                    }
                    sptm_panic_str("state_guard_release %llx");
                }
            }
            sptm_panic_str("%d is not a valid UAT state");
        }
        sptm_panic(0x4000018, 0, "ctx id in use %llx");
    }
    sptm_panic(0x4000018, 0, "ctx id already set %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000b2928 @ 0x000b2928   (est. sptm_uat_remove_ctx_id)
 * Ghidra: undefined FUN_000b2928(undefined8)
 * Unbind a UAT state from its context id: validate the ctx entry is live,
 * clear the present bits in both VTTBR words, bump the invalidate/completion
 * counters, issue the per-ctx TLB invalidate (or a full UAT flush when the
 * stage flag uat+0x1a0 is set), clear the state's ctx id, and release the
 * per-CPU guard.
 * Confidence: low
 * Notes: ctx entry present bits cleared in both words; TLBI (0,9,1,2) with
 *   ctx<<0x30; counters at uat + ctx*2 + 0x82 (start) / +0x83 (done) gated on
 *   uat+0x80; the current-ctx check at uat[0x138]+0x18 faults 0x400001d.
 */
void sptm_uat_remove_ctx_id(uint64_t state_id)
{
    uint8_t *st = sptm_uat_state_get(state_id, 2, 5);
    uint16_t ctx = *(uint16_t *)(st + 0x18);
    if (ctx > 0x3f) {
        sptm_panic(0x4000019, 0, "invalid ctx id %llx");
    }

    if ((sptm_boot_thing & 1) == 0 &&
        *(int32_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x138) +
                     (uint32_t)ctx * 0x18 + 0x20) != 0) {
        sptm_panic(0x4000016, 0, "ctx in use %llx");
    }

    if (*(uint8_t *)(sptm_uat_driver_state + 0x60) != 0) {
        sptm_panic(0x400001a, 0, "ctx guard busy %llx");
    }
    *(uint8_t *)(sptm_uat_driver_state + 0x60) =
        (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1);

    uint64_t *ttb = (uint64_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x78) +
                                 (uint64_t)ctx * 0x10);
    if ((ttb[0] & 1) == 0 || (ttb[1] & 1) == 0) {
        sptm_panic_str("Valid context ID but the TTB entry is invalid");
    }
    ttb[1] &= ~1ULL;
    ttb[0] &= ~1ULL;

    if ((*(uint8_t *)(sptm_uat_driver_state + 0x80) & 1) != 0) {
        uint8_t *c = sptm_uat_driver_state + ctx * 2 + 0x82;
        *c = (uint8_t)(*c + 1);
    }
    sptm_dsb_sy();

    uint16_t c2 = *(uint16_t *)(st + 0x18);
    if (c2 != 0xffff) {
        if ((*st & 5) == 0) {
            sptm_panic_str("Attempted a TLB Invalidate before set_ctx_id");
        }
        if ((*(uint8_t *)(sptm_uat_driver_state + 0x1a0) & 1) == 0) {
            if (c2 > 0x3f) {
                sptm_panic_str("invalid context ID %p %d");
            }
            sptm_tlbi(9, 1, 2, 0, (uint64_t)c2 << 0x30);
        } else {
            sptm_uat_tlb_invalidate(st, 0x1000000000, 0x6000000000, 0);
        }
    }
    sptm_dsb_ish();

    if ((*(uint8_t *)(sptm_uat_driver_state + 0x80) & 1) != 0) {
        uint8_t *c = sptm_uat_driver_state + ctx * 2 + 0x83;
        *c = (uint8_t)(*c + 1);
    }
    if ((sptm_boot_thing & 1) == 0 &&
        *(uint32_t *)(*(uint64_t *)(sptm_uat_driver_state + 0x138) + 0x18) == ctx) {
        sptm_panic(0x400001d, 0, "cannot remove current ctx %llx");
    }

    st[0x18] = 0xff;
    st[0x19] = 0xff;

    if (*(uint8_t *)(sptm_uat_driver_state + 0x60) ==
        (uint8_t)(sptm_handoff_region[sptm_cpu_id() + 10] << 1 | 1)) {
        *(uint8_t *)(sptm_uat_driver_state + 0x60) = 0;
        if (st[0x1a] == 1) {
            st[0x1a] = 2;
            if ((*st & 5) == 0) {
                return;
            }
            sptm_kvtophys(st);
            sptm_paddr_release(0);
            return;
        }
    }
    sptm_panic_str("state_guard_release %llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000b26b0 @ 0x000b26b0   (est. sptm_uat_get_info)
 * Ghidra: ulong FUN_000b26b0(byte, undefined8)
 * Query UAT driver information by `query` (0-9): 0 = shared-mode base,
 * 1/2 = root table physical address (mode-dependent), 3 = root shift, 4/5/8 =
 * driver configuration words, 6 = fixed 0x1000000000, 7 = fixed 0x7000000000,
 * 9 = root table virtual address (translated). Faults (0x400001b) on an
 * invalid query or a shared-mode mismatch.
 * Confidence: medium
 * Notes: query 9 applies the direct-map / region-table translation to the
 *   root VA stored at uat+0x108. Query 1/2 go through sptm_kvtophys on the
 *   shared-mode root.
 */
uint64_t sptm_uat_get_info(uint8_t query, uint64_t unused)
{
    (void)unused;
    if (query > 9) {
        sptm_panic(0x400001b, 0, "invalid query %llx");
    }

    uint64_t v = 0x1000000000ULL;
    switch (query) {
    default: /* 0 */
        v = *(uint64_t *)(sptm_uat_driver_state + 0x10);
        break;
    case 1:
        if (*(uint64_t *)(sptm_uat_driver_state + 0x10) == 0) {
            return sptm_kvtophys(*(void **)(sptm_uat_driver_state + 0x18));
        }
        goto bad_query;
    case 2:
        if (*(uint64_t *)(sptm_uat_driver_state + 0x10) == 1) {
            return sptm_kvtophys(*(void **)(sptm_uat_driver_state + 0x18));
        }
bad_query:
        sptm_panic(0x400001b, 0, "invalid query %llx");
    case 3:
        v = *(uint8_t *)(sptm_uat_driver_state + 0x1a1);
        break;
    case 4:
        v = *(uint64_t *)(sptm_uat_driver_state + 0x1a8);
        break;
    case 5:
        v = *(uint64_t *)(sptm_uat_driver_state + 0x1b0);
        break;
    case 6:
        break; /* fixed 0x1000000000 */
    case 7:
        v = 0x7000000000ULL;
        break;
    case 8:
        v = *(uint64_t *)(sptm_uat_driver_state + 0x1c0);
        break;
    case 9:
        v = *(uint64_t *)(sptm_uat_driver_state + 0x108);
        if (((uint32_t)sptm_mem_feature >> 8 & 1) != 0) {
            uint64_t cnt = sptm_region_count;
            if (cnt != 0) {
                uint64_t *rg = sptm_regions;
                do {
                    uint64_t b = rg[0];
                    if (b <= v && v < b + (uint32_t)rg[2] * 0x4000) {
                        return (v - b) + rg[1];
                    }
                    cnt--;
                    rg += 3;
                } while (cnt != 0);
            }
            return (uint64_t)sptm_phystokv_outside_window(v);
        }
        v = (v - sptm_mem_low) + sptm_direct_map_base;
    }
    return v;
}
