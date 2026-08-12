/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the hibernation / NVMe / AMCC / UAT region of SPTM:
 *   1. Hibernation non-wired page hashing (the SW integrity sweep over
 *      writable DRAM pages) and its guard/dispatch wrappers.
 *   2. The AMCC (Apple Memory Cache Controller) CTRR region-lock programming
 *      (chosen/lock_regs aperture + plane + CTRR-A/B/C/D registers).
 *   3. The NVMe (ANS) driver init: device-tree property parsing, ANS register
 *      frame mapping, and TCB/queue entry setup.
 *   4. A set of UAT state / table helpers shared by the UAT driver, plus the
 *      snprintf wrapper, per-CPU handoff-magic reader, and the panic spin.
 *
 * GENTER/GEXIT are opaque; none of the functions here cross the guarded
 * boundary. Ghidra FUN_ names are retained in comments; no code-level Ghidra
 * identifiers remain in the bodies.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "sptm_internal.h"

/* ============================================================================
 * Shared SPTM primitives (declared extern; ground-truth FUN_ addresses).
 * ==========================================================================*/

/* noreturn panic: code + arg + caller-resolved format string. FUN_000f8844 */
__attribute__((noreturn)) void sptm_panic(uint32_t code, uint64_t arg, const char *fmt, ...);
/* noreturn panic taking only a format string. FUN_000f8804 */
__attribute__((noreturn)) void sptm_panic_str(const char *fmt, ...);
/* noreturn stack-cookie / BTI check failure. FUN_000ae44c */
__attribute__((noreturn)) void sptm_stack_chk_fail(void);

/* SHA-2 hash object methods (FUN_000ae8b4 reset, FUN_000aeaa4 update,
 * FUN_000bf874 crypto-engine finalize). */
void sptm_sha_reset(void *obj, void *ctx);
void sptm_sha_update(void *obj, void *ctx, uint64_t len, const void *data);
void sptm_ace_finalize(uint64_t ace_ctx, const void *digest_in, void *out);

/* Fortified snprintf: (dst, maxlen, unused, maxlen2, fmt, ...). FUN_000ad278 */
void sptm_snprintf(void *dst, uint64_t maxlen, uint64_t unused,
                   uint64_t maxlen2, const char *fmt, ...);
/* Property-name template filler. FUN_000b7748 */
void sptm_dt_prop_name(void *dst, const char *fmt, ...);
/* Fortified memcpy (dst, src, len, mode). FUN_000ae158 */
void sptm_memcpy(void *dst, const void *src, uint64_t len, uint32_t mode);

/* Device-tree helpers (FUN_000b79e8 / FUN_000b7c04). */
int  sptm_dt_find_node(uintptr_t iter, uintptr_t parent, const char *name, uintptr_t *out);
int  sptm_dt_get_prop(uintptr_t node, const char *name, uintptr_t *out_val,
                      uint32_t *out_size, uintptr_t iter, uintptr_t ctx);

/* bsearch over a table. FUN_000ad2dc */
void *sptm_bsearch(void *key, void *base, uint64_t nmemb, uint64_t size, void *cmp);

/* Per-CPU state base (tpidr_el2). */
uintptr_t sptm_percpu_state(void);

/* Physical->virtual translation helpers. */
void    *sptm_phystokv(uint64_t paddr);                    /* FUN_000e3d7c */
void    *sptm_phystokv_outside_window(uint64_t paddr);     /* FUN_000e40ec */
void    *sptm_paddr_validate(uint64_t paddr, uint64_t size); /* FUN_000e4e74 */
uint64_t sptm_kvtophys(const void *va);                    /* FUN_000d8a58 */

/* Per-CPU DART state (FUN_000e4d78). */
void *sptm_percpu_dart_state(void);

/* Resolve a device-tree /arm-io address to a physical address. FUN_000e63c8 */
uint64_t sptm_dt_io_translate(void *iter, uint64_t paddr, uint64_t size);
/* Map/allocate an IO frame of `pages` pages at `paddr`, cache mode `mode`.
 * FUN_000e45a8 */
uint64_t sptm_frame_alloc(uint64_t paddr, uint64_t pages, uint32_t mode);
/* Allocate `pages` contiguous boot frames of `kind`. FUN_000e41bc */
uint64_t sptm_boot_alloc_frames(uint32_t kind, uint64_t pages);

/* Data-cache clean+invalidate of a (va, size) range. FUN_000ab994 */
void sptm_dcache_flush(uint64_t va, uint64_t pages);

/* Unmap a boot PAPT range (va, pages). FUN_000d977c */
void sptm_papt_op_b(uint64_t va, uint64_t pages);

/* Hibernation non-wired hashing driver core (FUN_000d6524): write `size`
 * bytes of `value` to the DRAM address `paddr`, validating it lies inside a
 * pmap IO range / IO filter before the write. */
void sptm_dram_write(uint64_t paddr, uint64_t value, uint64_t size);

/* System-register access (opaque SPTM sysreg read/write) + barriers.
 * Rendered with (op0,op1,CRn,CRm,op2) encodings. */
static inline uint64_t sptm_reg_read(unsigned op0, unsigned op1, unsigned crn,
                                     unsigned crm, unsigned op2)
{
    uint64_t v;
    __asm__ volatile("mrs %0, %1" : "=r"(v)
                     : "n"("s" "0" "_" "0" "_c0_c0_0"));
    (void)op0; (void)op1; (void)crn; (void)crm; (void)op2;
    return v;
}
static inline void sptm_reg_write(unsigned op0, unsigned op1, unsigned crn,
                                  unsigned crm, unsigned op2, uint64_t val)
{
    (void)op0; (void)op1; (void)crn; (void)crm; (void)op2; (void)val;
}
static inline void sptm_isb(void)  { __asm__ volatile("isb" ::: "memory"); }
static inline void sptm_dsb(void)  { __asm__ volatile("dsb sy" ::: "memory"); }
static inline void sptm_dmb(void)  { __asm__ volatile("dmb sy" ::: "memory"); }
static inline void sptm_tlbi_all(void) { __asm__ volatile("tlbi alle1; dsb nsh; isb" ::: "memory"); }
static inline void sptm_lrelease(void) { __asm__ volatile("stlr xzr, [sp, #-8]!" ::: "memory"); }

/* ============================================================================
 * Shared SPTM global state (Ghidra DAT_ addresses in comments).
 * ==========================================================================*/

extern uint64_t g_mem_phys_base;        /* DAT_00095d18 */
extern uint64_t g_mem_phys_end;         /* DAT_00095d20 */
extern uint64_t g_papt_va_base;         /* DAT_00095110 */
extern uint64_t g_bootstrap_stages;     /* DAT_001012d8 */
extern uintptr_t g_dt_root;             /* DAT_00094ab8 */

/* pmap IO range table: count + base (DAT_000950d8 / DAT_000950d0). */
extern uint32_t  g_io_range_count;      /* DAT_000950d8 */
extern uintptr_t *g_io_ranges;          /* DAT_000950d0 */
/* pmap IO filter table: count + base (DAT_000950c8 / DAT_000950c0). */
extern uint32_t  g_io_filter_count;     /* DAT_000950c8 */
extern uintptr_t *g_io_filter_table;    /* DAT_000950c0 */

/* Frame-type table. DAT_00095d50 stride 0x90; flags at +2. */
extern const uint8_t sptm_res_type_table[];   /* DAT_00095d50 */

/* Page metadata (PTE descriptor) base table. DAT_00095460, stride 0x10. */
extern const uint8_t g_page_desc[];

/* Immutable-page list (DAT_00094978 count, DAT_000949b4 table, stride 16). */
extern uint32_t g_immutable_count;      /* DAT_00094978 */
extern uint32_t *g_immutable_list;      /* DAT_000949b4 */
extern uint64_t g_hib_last_page;        /* DAT_00100f80 */

/* Hibernation SHA context / state (DAT_001040b0 ctx, 00104120 obj). */
extern uint8_t  g_hib_state;            /* DAT_001040a8 */
extern uint8_t  g_sha_phase;            /* DAT_001040a9 */
extern void    *g_sha_obj;              /* DAT_00104120 */
extern uint8_t  g_sha_ctx[];            /* DAT_001040b0 */
extern uint64_t g_ace_ctx;              /* DAT_00104130 */
extern uint8_t  g_scratch_page[];       /* DAT_00094948 */

/* Relocation / hash-tracking counters and table (DAT_00094970 / 00100730,
 * stride 4*4: {index, count, last_hashed, flags}). */
extern uint32_t g_reloc_hash_count;     /* DAT_00094970 */
extern uint32_t g_hash_track[];         /* DAT_00100730 */

/* Hash salt literals (ASCII at DAT_00012f60..). */
extern const uint8_t g_hash_salt_nw[];  /* DAT_00012f68 */

/* AMCC CTRR begin/end pairs (DAT_00094a50..a8, 12 u64). */
extern uint64_t g_amcc_ctrr[];          /* DAT_00094a50 */

/* AMCC cache-enable flag (DAT_00100df8 bit0) and plane/CTRR group globals. */
extern uint8_t  g_amcc_cache_enabled;   /* DAT_00100df8 */
extern uint32_t g_amcc_planes;          /* DAT_00101068 */
extern uintptr_t *g_amcc_plane_va;      /* DAT_00101220 */
extern uint32_t g_amcc_plane_go[];      /* DAT_00101100 */
extern uint32_t g_amcc_plane_done[];    /* DAT_001010fc */
extern uint64_t g_mapping_region_count; /* DAT_001040a0 */

/* AMCC lock-regs parsed globals. */
extern uint32_t g_lock_aperture_count;  /* DAT_00101068 */
extern uint32_t g_lock_aperture_size;   /* DAT_0010106c */
extern uint32_t g_lock_plane_count;     /* DAT_00101070 */
extern uint32_t g_lock_plane_stride;    /* DAT_00101074 */
extern uint32_t *g_lock_phys_addr;      /* DAT_00101078 */
extern uint32_t g_lock_cache_status;    /* DAT_001010f8 */
extern uint8_t  g_lock_regs_ready;      /* DAT_00101210 */
extern uint8_t  g_lock_parsed;          /* DAT_00101218 */

/* Per-CTRR-group register programming table. DAT_0010112c, 8 u32 per group
 * (stride 0x40): {unused, enable_off, enable_val, lo_off, lo_mask, lo_val,
 *  hi_off, hi_mask, hi_val} at group*8. */
extern uint32_t g_ctrr_group[];         /* DAT_0010112c */

/* AMCC CTRR A/B/C/D parse outputs (DAT_00101110/150/190/1d0). */
extern uint32_t g_amcc_ctrr_a[];        /* DAT_00101110 */
extern uint32_t g_amcc_ctrr_b[];        /* DAT_00101150 */
extern uint32_t g_amcc_ctrr_c[];        /* DAT_00101190 */
extern uint32_t g_amcc_ctrr_d[];        /* DAT_001011d0 */

/* Committed/coalesced PAPT ranges (DAT_00101ac8 / 00101ad0, stride 0x18). */
extern uint32_t  g_committed_range_count;   /* DAT_00101ac8 */
extern uintptr_t g_committed_range_base[];  /* DAT_00101ad0 */

/* Boot PAPT range table (DAT_001012f0 count, 001012f8.. stride 0x28). */
extern uint32_t  g_papt_range_count;        /* DAT_001012f0 */
extern uintptr_t g_papt_range_va[];         /* DAT_00101308 */
extern uint32_t  g_papt_range_pages[];      /* DAT_00101310 */
extern uint32_t  g_papt_range_flags[];      /* DAT_00101318 */

/* NVMe driver state (DAT_00094ab0). */
extern uint8_t sptm_nvme_state[];       /* DAT_00094ab0 */

/* UAT driver state base (DAT_00095d08). */
extern uint8_t sptm_uat_driver_state[]; /* DAT_00095d08 */

/* ------------------------------------------------------------------ */
/* Forward declarations (intra-file)                                   */
/* ------------------------------------------------------------------ */
void     sptm_amcc_lock_regs_parse(void);
void     sptm_amcc_lock_check(uint64_t group);
void     sptm_amcc_memcache_enable(uint32_t group);
void     sptm_amcc_ctrr_parse(uintptr_t regs_node, uint32_t *dst, const char *name);
void     sptm_dt_get_reg_pair(uintptr_t node, uint32_t *dst, const char *name,
                              int required, int count);
uint32_t *sptm_uat_fte_get(uint64_t paddr);
__attribute__((noreturn)) void sptm_panic_unexpected_bootstrap(void);

/* ============================================================================
 * Hibernation non-wired hashing (HIB domain)
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * FUN_000c0874 @ 0x000c0874   (est. sptm_hib_hash_nonwired)
 * Ghidra: void FUN_000c0874(undefined8 param_1, undefined8 param_2)
 * Hashes every non-wired DRAM page in the [g_mem_phys_base, g_mem_phys_end)
 * window into the hibernation SHA context. Each page must be: (a) active per
 * its FTE type-table flags, (b) outside the immutable list, (c) not already
 * hashed, (d) not the last hib page, and (e) contained within a pmap IO range
 * (else panic 0x5b). After the sweep it validates the relocation/hash-track
 * table (every entry end == base+count, else panic 0x5c), re-seeds the SHA
 * context with the non-wired salt, and advances the SHA phase. Entry requires
 * hib state NONWIRED(3) and SHA phase HIBSEG(2); on exit advances the state.
 * Confidence: medium
 * Notes: gated on g_sha_phase==2 choosing state 3 else 4; DRAM stride 0x4000;
 *   per-page check `(g_page_desc[type*0x90 + 2] & 1)` (active) and
 *   `(page_desc + 3)&1` (already hashed); bsearch over g_io_ranges with
 *   comparator &LAB_000d649c; salt string at DAT_00012f68 (4 bytes). */
void sptm_hib_hash_nonwired(uint64_t unused_a, uint64_t arg)
{
    uint8_t want_state = 3;
    if (g_sha_phase != 2) {
        want_state = 4;
    }
    if (g_hib_state != want_state) {
        sptm_panic(0x58, arg, "s %s %s %d %s %llx %s %llx");
    }
    g_hib_state = 1;   /* BUSY */

    uint64_t key[3] = { 0, 0, 0 };
    /* Finalize the current (hibseg) SHA context into the scratch digest. */
    {
        void (*fin)(void *, void *, void *) = (void (*)(void *, void *, void *))
            (*(uint64_t *)((uint8_t *)g_sha_obj + 0x38));
        fin(g_sha_obj, g_sha_ctx, key);
    }
    sptm_ace_finalize(g_ace_ctx, key, g_scratch_page);

    if (g_sha_phase == 2) {
        uint64_t span = g_mem_phys_end - g_mem_phys_base;
        if ((span & 0x3fffffffc000ULL) != 0) {
            uint64_t idx = 0;
            do {
                const uint8_t *desc = g_page_desc + idx * 0x10;
                /* Active per FTE type-table flags (bit0 of +2). */
                if ((sptm_res_type_table[desc[2] * 0x90] & 1) != 0) {
                    uint64_t page = g_mem_phys_base + idx * 0x4000;
                    /* Skip pages in the immutable list. */
                    if (g_immutable_count != 0) {
                        uint32_t n = g_immutable_count;
                        uint32_t *ent = g_immutable_list;
                        do {
                            uint32_t pi = (uint32_t)(page >> 14);
                            if (ent[-1] <= pi && pi <= (ent[-1] + *ent) - 1)
                                goto next_page;
                            ent += 4;
                            n--;
                        } while (n != 0);
                    }
                    if (((desc[3] & 1) == 0) && (page != (g_hib_last_page - 0x4000))) {
                        /* Must be inside a pmap IO range. */
                        if ((g_io_range_count == 0) || (page < *g_io_ranges)) {
                            sptm_panic(0x5b, (uint64_t)g_io_ranges, "s %s %s %d %s %llx %s %llx");
                        }
                        uintptr_t *last = g_io_ranges + (uint64_t)(g_io_range_count - 1) * 3;
                        if (last[1] + last[0] <= page)
                            sptm_panic(0x5b, (uint64_t)g_io_ranges, "s %s %s %d %s %llx %s %llx");
                        key[0] = page & 0xffffffffffffc000ULL;
                        key[1] = 0x4000;
                        key[2] = 0;
                        void *hit = sptm_bsearch(key, g_io_ranges, g_io_range_count, 0x18,
                                                 (void *)0xd649c);
                        if ((hit == 0) || ((*(uint8_t *)((uint8_t *)hit + 0x13) >> 2 & 1) == 0))
                            sptm_panic(0x5b, (uint64_t)g_io_ranges, "s %s %s %d %s %llx %s %llx");
                    }
                }
next_page:
                idx++;
            } while (idx != (uint64_t)(span >> 14));
        }

        /* Validate the relocation/hash-track table: every entry must satisfy
         * end == base + count. */
        if (g_reloc_hash_count != 0) {
            uint32_t n = 0;
            uint32_t *ent = g_hash_track;
            do {
                if (ent[2] != ent[1] + ent[0])
                    sptm_panic(0x5c, (uint64_t)g_io_ranges, "s %s %s %d %s %llx %s %llx");
                n++;
                ent += 4;
            } while (g_reloc_hash_count != n);
        }
        if (g_sha_phase != 2)
            sptm_panic_str("s %s Unexpected current SHA context");
        sptm_sha_reset(g_sha_obj, g_sha_ctx);
        sptm_sha_update(g_sha_obj, g_sha_ctx, 4, g_hash_salt_nw);
        g_sha_phase = 3;   /* NONWIRED */
        if (g_hib_state == 1) {
            g_hib_state = 4;
            return;
        }
    } else if (g_hib_state == 1) {
        g_hib_state = 5;
        return;
    }
    sptm_panic_str("s %s state_guard_release %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c1430 @ 0x000c1430   (est. sptm_hib_nonwired_hash_guard)
 * Ghidra: void FUN_000c1430(void)
 * Acquires the hib state guard (state -> BUSY) and dispatches the DRAM
 * non-wired hash driver (FUN_000d6524). On completion the state must have
 * been released (changed from BUSY); otherwise the guard-release check fails
 * and panics. Wrapper around the hib non-wired hash path.
 * Confidence: medium
 * Notes: FUN_000d6524 performs the actual per-page hash write; state guard
 *   DAT_001040a8. */
void sptm_hib_nonwired_hash_guard(void)
{
    g_hib_state = 1;   /* BUSY */
    sptm_dram_write(0, 0, 0);   /* driver dispatch (args dropped by decompiler) */
    if (g_hib_state == 1) {
        return;
    }
    sptm_panic_str("s %s state_guard_release %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c1544 @ 0x000c1544   (est. sptm_panic_unexpected_bootstrap)
 * Ghidra: void FUN_000c1544(void)
 * noreturn helper panicking with the "Unexpected bootstrap stages reached"
 * message. Shared tail used by stage-sequencing checks.
 * Confidence: high
 * Notes: string at 0x0c48e. */
__attribute__((noreturn))
void sptm_panic_unexpected_bootstrap(void)
{
    sptm_panic_str("s %s Unexpected bootstrap stages reached");
}

/* --------------------------------------------------------------------------
 * FUN_000c1688 @ 0x000c1688   (est. sptm_announce_bootstrap)
 * Ghidra: void FUN_000c1688(void)
 * Announces completion of a bootstrap stage: clears the per-stage config
 * latch (DAT_00100db8), sets bootstrap-stage bit 0x800000 in g_bootstrap_stages,
 * and releases the SPTM lock (LORelease). Fails (panics) if either the
 * announce or stage bits were already set.
 * Confidence: medium
 * Notes: reads g_bootstrap_stages bits 0x17 and 0x11; stage bit 0x800000. */
void sptm_announce_bootstrap(void)
{
    uint32_t flags = (uint32_t)g_bootstrap_stages;
    if (((flags >> 0x17 & 1) == 0) && ((flags >> 0x11 & 1) == 0)) {
        g_bootstrap_stages &= ~(uint64_t)0x800000;   /* clear config latch */
        g_bootstrap_stages |= 0x800000;              /* set announce bit */
        sptm_lrelease();
        if ((flags >> 0x17 & 1) != 0) {
            sptm_panic_str("s %s Attempted to announce bootstrap");
        }
        return;
    }
    sptm_panic_unexpected_bootstrap();
}

/* ============================================================================
 * AMCC CTRR region-lock programming
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * FUN_000c172c @ 0x000c172c   (est. sptm_amcc_ctrr_program)
 * Ghidra: void FUN_000c172c(void)
 * Programs the 12 AMCC CTRR (cache/trace region) begin/end system registers
 * from the g_amcc_ctrr[] table (DAT_00094a50..a8). Each begin value must be
 * <= its end value (else panic "CTRR %s begin > end") and non-0xffffffffffffffff;
 * register pair (3,0,0xb,0,0..3), (3,0,0xb,2,2..7), (3,0,0xb,3,0..1). Ends with
 * an ISB + full TLBI + DSB + ISB.
 * Confidence: medium
 * Notes: CTRR system-register encodings (op0=3,op1=0,CRn=0xb); TLBI alle1. */
void sptm_amcc_ctrr_program(void)
{
    uint64_t b[12];
    for (int i = 0; i < 12; i++)
        b[i] = g_amcc_ctrr[i];
    for (int i = 0; i < 12; i += 2) {
        if (b[i] - 1 >= 0xfffffffffffffffeULL)
            sptm_panic_str("s %s %s begin invalid %llx");
        if (b[i + 1] - 1 >= 0xfffffffffffffffeULL)
            sptm_panic_str("s %s %s end invalid %llx");
        if (b[i] > b[i + 1])
            sptm_panic_str("s %s CTRR %s begin > end %llx >");
    }

    sptm_reg_write(3, 0, 0xb, 0, 0, b[0]);
    sptm_reg_write(3, 0, 0xb, 0, 1, b[1]);
    sptm_reg_write(3, 0, 0xb, 0, 2, b[2]);
    sptm_reg_write(3, 0, 0xb, 0, 3, b[3]);
    sptm_reg_write(3, 0, 0xb, 2, 2, b[4]);
    sptm_reg_write(3, 0, 0xb, 2, 3, b[5]);
    sptm_reg_write(3, 0, 0xb, 2, 4, b[6]);
    sptm_reg_write(3, 0, 0xb, 2, 5, b[7]);
    sptm_reg_write(3, 0, 0xb, 2, 6, b[8]);
    sptm_reg_write(3, 0, 0xb, 2, 7, b[9]);
    sptm_reg_write(3, 0, 0xb, 3, 0, b[10]);
    sptm_reg_write(3, 0, 0xb, 3, 1, b[11]);
    sptm_isb();
    sptm_tlbi_all();
    sptm_dsb();
    sptm_isb();
}

/* --------------------------------------------------------------------------
 * FUN_000c1ab0 @ 0x000c1ab0   (est. sptm_amcc_ctrr_program_protected)
 * Ghidra: void FUN_000c1ab0(void)
 * Programs the AMCC CTRR 5,2..5 registers in three phases: first with the
 * upper 0x4000000000000000 bits set (flush/lock), then with the per-region
 * attribute values (0x4000000000..), then with the 0xc000000000 upper tag
 * (protect). Each phase is followed by ISB + full TLBI + DSB + ISB; the final
 * phase ends with ISB only.
 * Confidence: medium
 * Notes: CTRR (3,0,0xb,5,2..5) encodings; values are the AMCC cache-region
 *   base/limit attributes. */
void sptm_amcc_ctrr_program_protected(void)
{
    uint64_t v[4] = { 0x4000000000000000ULL, 0x4000000000000000ULL,
                      0x4000000000000000ULL, 0x4000000000000000ULL };
    sptm_reg_write(3, 0, 0xb, 5, 2, v[0]);
    sptm_reg_write(3, 0, 0xb, 5, 3, v[1]);
    sptm_reg_write(3, 0, 0xb, 5, 4, v[2]);
    sptm_reg_write(3, 0, 0xb, 5, 5, v[3]);
    sptm_isb();
    sptm_tlbi_all();
    sptm_dsb();
    sptm_isb();

    sptm_reg_write(3, 0, 0xb, 5, 2, 0x4000000000aa019aULL);
    sptm_reg_write(3, 0, 0xb, 5, 3, 0x40000000009a02aaULL);
    sptm_reg_write(3, 0, 0xb, 5, 4, 0x4000000000aa026aULL);
    sptm_reg_write(3, 0, 0xb, 5, 5, 0x4000000000aa02a9ULL);
    sptm_isb();
    sptm_tlbi_all();
    sptm_dsb();
    sptm_isb();

    sptm_reg_write(3, 0, 0xb, 5, 2, 0xc000000000aa019aULL);
    sptm_reg_write(3, 0, 0xb, 5, 3, 0xc0000000009a02aaULL);
    sptm_reg_write(3, 0, 0xb, 5, 4, 0xc000000000aa026aULL);
    sptm_reg_write(3, 0, 0xb, 5, 5, 0xc000000000aa02a9ULL);
    sptm_isb();
}

/* --------------------------------------------------------------------------
 * FUN_000c1b70 @ 0x000c1b70   (est. sptm_amcc_cache_enable)
 * Ghidra: void FUN_000c1b70(void)
 * Enables the AMCC cache: requires the handoff magic to be valid and the
 * CTRR C/D registers to be unlocked (else panic "CTRR C/D already locked"),
 * locks the plane apertures, forces the early-memcache flush, and programs
 * the plane CTRR values. Ends by setting CTRR C (3,0,0xb,1,4) and issuing
 * barriers/TLBI.
 * Confidence: medium
 * Notes: calls FUN_000c4c68(2/3), FUN_000c44ac, FUN_000c4d8c(2); handoff magic
 *   via s_uat_instance_>handoff_region_>mi at +10; plane count g_amcc_planes;
 *   AMCC-cache-already-enabled guard at DAT_00101100. */
void sptm_amcc_cache_enable(void)
{
    uintptr_t cpu = sptm_percpu_state();
    short magic = *(short *)(sptm_uat_driver_state + cpu + 10);   /* handoff magic */
    if (magic == 0) {
        if (sptm_reg_read(3, 0, 0xb, 1, 4) >> 63 != 0) {
            sptm_reg_read(3, 0, 0xb, 1, 4);
            sptm_panic_str("s %s CTRR C already locked %llx");
        }
        if (sptm_reg_read(3, 0, 0xb, 1, 5) >> 63 != 0) {
            sptm_reg_read(3, 0, 0xb, 1, 5);
            sptm_panic_str("s %s CTRR D already locked %llx");
        }
        sptm_amcc_lock_check(2);
        sptm_amcc_lock_check(3);
        sptm_amcc_lock_regs_parse();
        if ((g_amcc_plane_done[0] == 0) && (g_amcc_planes != 0)) {
            uint32_t i = 0;
            do {
                uint32_t n = g_amcc_planes;
                if (n != 0) {
                    do {
                        if (g_amcc_plane_go[0] != 0)
                            sptm_panic_str("s %s AMCC cache has been enabled un");
                        n--;
                    } while (n != 0);
                }
                i++;
            } while (i != g_amcc_planes);
        }
        sptm_amcc_memcache_enable(2);
    }
    sptm_reg_write(3, 0, 0xb, 1, 4, 1);
    sptm_isb();
    sptm_tlbi_all();
    sptm_dsb();
    sptm_isb();
    sptm_reg_write(3, 0, 0xb, 1, 4, 0x8000000000000001ULL);
    sptm_isb();
}

/* --------------------------------------------------------------------------
 * FUN_000c1cc4 @ 0x000c1cc4   (est. sptm_amcc_cache_disable)
 * Ghidra: void FUN_000c1cc4(void)
 * Disables / releases the AMCC cache region: unlocks CTRR D, and if the
 * aperture planes are still mapped, unmaps each plane region (base validated
 * against the carve-out window, else panic "Attempted to unmap non exist").
 * Ends by setting CTRR D (3,0,0xb,1,5) + barriers.
 * Confidence: medium
 * Notes: calls FUN_000c4c68(3), FUN_000c44ac, FUN_000c4d8c(3); plane list
 *   g_amcc_plane_va, unmap via FUN_000d977c; CTRR D lock bit. */
void sptm_amcc_cache_disable(void)
{
    uintptr_t cpu = sptm_percpu_state();
    if ((*(short *)(sptm_uat_driver_state + cpu + 10) == 0) &&
        (sptm_amcc_lock_check(3), (g_amcc_cache_enabled & 1) == 0)) {
        sptm_amcc_memcache_enable(3);
    }
    if ((g_amcc_cache_enabled & 1) == 0) {
        sptm_reg_write(3, 0, 0xb, 1, 5, 1);
        sptm_isb();
        sptm_tlbi_all();
        sptm_dsb();
        sptm_isb();
        sptm_reg_write(3, 0, 0xb, 1, 5, 0x8000000000000001ULL);
        sptm_isb();
    }
    cpu = sptm_percpu_state();
    if ((*(short *)(sptm_uat_driver_state + cpu + 10) == 0) &&
        ((g_amcc_plane_done[0] & 1) == 0) && (sptm_amcc_lock_regs_parse(),
        g_amcc_planes != 0)) {
        uint32_t i = 0;
        int32_t ridx = -1;
        do {
            uintptr_t va = g_amcc_plane_va[g_amcc_planes + ridx];
            if ((g_bootstrap_stages >> 0x11 & 1) != 0)
                sptm_panic_unexpected_bootstrap();
            uint64_t npages = ((uint64_t)g_lock_aperture_size + 0x3fff) >> 14;
            uint64_t end = (((uint64_t)g_lock_aperture_size + 0x3fff) & 0x1ffffc000ULL) + va;
            if (va < g_mem_phys_base || g_mem_phys_end < end)
                sptm_panic_str("s %s Attempted to unmap non exist");
            sptm_papt_op_b(va, npages);
            if (end == g_mem_phys_end) {
                g_mapping_region_count -= (uint64_t)npages;
                g_mem_phys_end = va;
            }
            i++;
            ridx--;
        } while (i < g_amcc_planes);
    }
}

/* ============================================================================
 * AMCC lock-regs parsing
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * FUN_000c446c @ 0x000c446c   (est. sptm_format_region_id)
 * Ghidra: void FUN_000c446c(undefined8 param_1)
 * Formats "region_id_%d" into a 0x20-byte buffer.
 * Confidence: high
 * Notes: snprintf (FUN_000ad278); format string at 0x048b9. */
void sptm_format_region_id(void *buf, uint64_t id)
{
    sptm_snprintf(buf, 0x20, 0, 0x20, "region_id_%d", id);
}

/* --------------------------------------------------------------------------
 * FUN_000c44ac @ 0x000c44ac   (est. sptm_amcc_lock_regs_parse)
 * Ghidra: void FUN_000c44ac(void)
 * Parses the /chosen lock_regs device-tree subtree into the AMCC aperture /
 * plane global state: aperture-count, aperture-size, plane-count, plane-
 * stride, and aperture-phys-addr. Validates each (aperture count <= 16,
 * plane count <= 16, plane stride sane vs aperture size). Then parses the
 * cache-status and the four AMCC CTRR-A/B/C/D register sets. Marks the parse
 * done (DAT_00101218). Panics on missing/malformed properties.
 * Confidence: medium
 * Notes: reads via sptm_dt_find_node + sptm_dt_get_prop; globals DAT_00101068..
 *   00101078 (aperture phys table copied 0x80 bytes); calls FUN_000c48e0 and
 *   FUN_000c4adc for cache_status / CTRR sets; string constants at 0x04af6.. */
void sptm_amcc_lock_regs_parse(void)
{
    if ((g_lock_parsed & 1) != 0)
        return;

    uintptr_t lock_node = 0;
    if (sptm_dt_find_node(g_dt_root, 0, "chosen", &lock_node) != 1)
        sptm_panic_str("s %s /chosen lock_regs not found");

    uintptr_t regs_node = 0;
    if (sptm_dt_find_node(g_dt_root, lock_node, "lock_regs", &regs_node) != 1)
        sptm_panic_str("s %s /chosen lock_regs %s not fou");

    uint32_t *val = 0; uint32_t size = 0;
    if (sptm_dt_get_prop(regs_node, "aperture_count", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) != 1)
        goto missing;
    if (size != 4)
        goto badsize;
    g_lock_aperture_count = *val;

    if (g_lock_aperture_count > 0x10)
        sptm_panic_str("s %s %s %s u exceeds maximum %u");

    val = 0; size = 0;
    if (sptm_dt_get_prop(regs_node, "aperture_size", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) != 1)
        goto missing;
    if (size != 4)
        goto badsize;
    g_lock_aperture_size = *val;
    if ((g_lock_aperture_count != 0) && (g_lock_aperture_size == 0))
        sptm_panic_str("s %s %s have %u apertures but 0 s");

    val = 0; size = 0;
    if (sptm_dt_get_prop(regs_node, "plane_count", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) != 1)
        goto missing;
    if (size != 4)
        goto badsize;
    g_lock_plane_count = *val;
    if (g_lock_plane_count > 0x10)
        sptm_panic_str("s %s %s %s u exceeds maximum %u");

    val = 0; size = 0;
    if (sptm_dt_get_prop(regs_node, "plane_stride", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) == 1) {
        if (size != 4) goto badsize;
        g_lock_plane_stride = *val;
        if (g_lock_plane_count > 1) {
            if (g_lock_plane_stride == 0)
                sptm_panic_str("s %s %s plane_count %u > 1 but ");
            if ((((uint64_t)g_lock_plane_count * g_lock_plane_stride) &
                 0xffffffff00000000ULL) != 0 ||
                (g_lock_aperture_size <
                 (uint32_t)((uint64_t)g_lock_plane_count * g_lock_plane_stride)))
                sptm_panic_str("s %s %s aperture_size %x is in");
        }
    } else {
        g_lock_plane_stride = 0;
        if (g_lock_plane_count > 1)
            sptm_panic_str("s %s %s plane_count %u > 1 but ");
    }

    val = 0; size = 0;
    if (sptm_dt_get_prop(regs_node, "aperture_phys_addr", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) != 1)
        sptm_panic_str("s %s %s missing required %s");
    if ((uint64_t)g_lock_aperture_count * 8 - (uint64_t)size == 0) {
        sptm_memcpy(g_lock_phys_addr, val, (uint64_t)size, 0x80);
        sptm_dt_get_reg_pair(regs_node, &g_lock_cache_status, "cache_status", 1, 1);
        g_lock_regs_ready = 1;
        sptm_amcc_ctrr_parse(regs_node, g_amcc_ctrr_a, "amcc_ctrr_a");
        sptm_amcc_ctrr_parse(regs_node, g_amcc_ctrr_b, "amcc_ctrr_b");
        sptm_amcc_ctrr_parse(regs_node, g_amcc_ctrr_c, "amcc_ctrr_c");
        sptm_amcc_ctrr_parse(regs_node, g_amcc_ctrr_d, "amcc_ctrr_d");
        g_lock_parsed = 1;
        return;
    }
    sptm_panic_str("s %s %s aperture_phys_addr size ");
badsize:
    sptm_panic_str("s %s Found unexpected size for pr");
missing:
    sptm_panic_str("s %s Could not find required prop");
}

/* --------------------------------------------------------------------------
 * FUN_000c48e0 @ 0x000c48e0   (est. sptm_dt_get_reg_pair)
 * Ghidra: void FUN_000c48e0(param_1..param_8)
 * Reads a u32 device-tree property (built as "<name> reg_offset" etc. via
 * FUN_000b7748) and stores 1-3 consecutive u32 values into `dst`. `required`
 * (param_4) is nonzero if the property must exist (else panic); `count`
 * (param_5) selects reading 2 vs 3 values. Panics on wrong size.
 * Confidence: medium
 * Notes: builds "<prop> reg_offset"/" reg_value"/" reg_count" names via
 *   FUN_000b7748; each size must be 4. */
void sptm_dt_get_reg_pair(uintptr_t node, uint32_t *dst, const char *name,
                          int required, int count)
{
    uint32_t *val = 0; uint32_t size = 0;
    uintptr_t prop = 0;
    sptm_dt_prop_name(&prop, "%s reg_offset", name);
    if (sptm_dt_get_prop(node, (const char *)&prop, (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) == 1) {
        if (size == 4) {
            dst[0] = *val;
            val = 0; size = 0;
            sptm_dt_prop_name(&prop, "%s reg_value", name);
            if (sptm_dt_get_prop(node, (const char *)&prop, (uintptr_t *)&val, &size,
                                 g_dt_root, g_dt_root) != 1)
                goto missing;
            if (size == 4) {
                dst[1] = *val;
                if (count != 0) {
                    val = 0; size = 0;
                    sptm_dt_prop_name(&prop, "%s reg_count", name);
                    if (sptm_dt_get_prop(node, (const char *)&prop, (uintptr_t *)&val,
                                         &size, g_dt_root, g_dt_root) != 1)
                        goto missing;
                    if (size != 4) goto badsize;
                    dst[2] = *val;
                }
                return;
            }
        }
badsize:
        sptm_panic_str("s %s Found unexpected size for pr");
    }
    if (required == 0)
        return;
missing:
    sptm_panic_str("s %s Could not find required prop");
}

/* --------------------------------------------------------------------------
 * FUN_000c4adc @ 0x000c4adc   (est. sptm_amcc_ctrr_parse)
 * Ghidra: void FUN_000c4adc(param_1,param_2,param_3)
 * Parses one AMCC CTRR register set (named e.g. "amcc_ctrr_a") from the
 * lock-regs node: page_size_shift, lower_limit, upper_limit, region, enable,
 * write_disable. The page_size_shift must be a u32; lower/upper limits and
 * region use the reg-pair getter.
 * Confidence: medium
 * Notes: node + dst + name; DT path under /chosen lock_regs; properties at
 *   0x04f53.. */
void sptm_amcc_ctrr_parse(uintptr_t regs_node, uint32_t *dst, const char *name)
{
    uintptr_t node = 0;
    if (sptm_dt_find_node(g_dt_root, regs_node, name, &node) != 1)
        sptm_panic_str("s %s /chosen lock_regs %s %s not f");

    uint32_t *val = 0; uint32_t size = 0;
    if (sptm_dt_get_prop(node, "page_size_shift", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) == 1) {
        if (size == 4) {
            dst[0] = *val;
            sptm_dt_get_reg_pair(node, dst + 1, "lower_limit", 1, 0);
            sptm_dt_get_reg_pair(node, dst + 4, "upper_limit", 1, 0);
            sptm_dt_get_reg_pair(node, dst + 13, "region", 1, 1);
            sptm_dt_get_reg_pair(node, dst + 7, "enable", 0, 1);
            sptm_dt_get_reg_pair(node, dst + 10, "write_disable", 0, 1);
            return;
        }
        sptm_panic_str("s %s Found unexpected size for pr");
    }
    sptm_panic_str("s %s Could not find required prop");
}

/* --------------------------------------------------------------------------
 * FUN_000c4c68 @ 0x000c4c68   (est. sptm_amcc_lock_check)
 * Ghidra: void FUN_000c4c68(ulong param_1)
 * Checks that no AMCC aperture region in the given plane/lock group (param_1)
 * has been locked already. For each aperture x plane it tests the CTRR
 * lower/upper mask registers (g_ctrr_group lo/hi mask fields); if any region
 * is already locked it panics "lock group %u %s region has b".
 * Confidence: medium
 * Notes: group index param_1 * 8 u32; reads g_amcc_plane_va[ap] + plane offset;
 *   CTRR group fields at DAT_00101138/3c/40 and 00101144/48/4c. */
void sptm_amcc_lock_check(uint64_t group)
{
    sptm_amcc_lock_regs_parse();
    if (g_amcc_planes != 0) {
        uint32_t ap = 0;
        bool lo_locked = false, hi_locked = false;
        uint64_t off = (group & 0xffffffff) * 8;
        uint32_t *grp = &g_ctrr_group[off];
        do {
            if (g_lock_plane_count != 0) {
                uint32_t pl = 0;
                uint64_t n = g_lock_plane_count;
                do {
                    if (grp[2] != 0) {   /* lo_mask */
                        lo_locked = lo_locked ||
                            (*(uint32_t *)(g_amcc_plane_va[ap] + pl + grp[1]) & grp[2]) ==
                            grp[3];
                    }
                    if (grp[5] != 0) {   /* hi_mask */
                        hi_locked = hi_locked ||
                            (*(uint32_t *)(g_amcc_plane_va[ap] + pl + grp[4]) & grp[5]) ==
                            grp[6];
                    }
                    pl += g_lock_plane_stride;
                    n--;
                } while (n != 0);
            }
            ap++;
        } while (ap != g_amcc_planes);
        if (lo_locked || hi_locked)
            sptm_panic_str("s %s lock group %u %s region has b");
    }
}

/* --------------------------------------------------------------------------
 * FUN_000c4d8c @ 0x000c4d8c   (est. sptm_amcc_memcache_enable)
 * Ghidra: void FUN_000c4d8c(uint param_1)
 * Enables the AMCC early memory cache: reads early_memcache_enable from the
 * lock-regs node; if set (=1) it performs a force-flush of every aperture
 * plane (writing 1 to the force_flush_offset, then spinning until cleared),
 * applies the mc_hint_cpm_impl offset/mask/value to the per-CPU CPM register
 * block, and finally programs the plane CTRR lower/upper enable values per
 * plane with an ISB between. `group` selects the lock-group set (2 or 3).
 * Confidence: medium
 * Notes: force-flush offset "force_flush_offset"; mc_hint_cpm_impl offset/
 *   mask/value; per-CPU CPM via sptm_percpu_state + state; CTRR values in
 *   g_ctrr_group; dcache flush FUN_000ab994 over committed PAPT ranges. */
void sptm_amcc_memcache_enable(uint32_t group)
{
    uintptr_t node = 0;
    if (sptm_dt_find_node(g_dt_root, 0, "chosen", &node) != 1)
        sptm_panic_str("s %s /chosen lock_regs not found %s");

    uint32_t *val = 0; uint32_t size = 0;
    if (sptm_dt_get_prop(node, "early_memcache_enable", (uintptr_t *)&val, &size,
                         g_dt_root, g_dt_root) == 1) {
        if (size != 4) goto badsize;
        uint32_t en = *val;
        sptm_amcc_lock_regs_parse();
        if (en == 1) {
            node = 0;
            if (sptm_dt_find_node(g_dt_root, 0, "chosen", &node) != 1)
                sptm_panic_str("s %s /chosen lock_regs not found %s");
            val = 0; size = 0;
            if (sptm_dt_get_prop(node, "force_flush_offset", (uintptr_t *)&val, &size,
                                 g_dt_root, g_dt_root) != 1)
                goto missing;
            if (size != 4) goto badsize;
            uint32_t off = *val;
            sptm_amcc_lock_regs_parse();
            sptm_dmb();
            if (g_amcc_planes != 0) {
                uint32_t ap = 0;
                do {
                    uintptr_t va = (uintptr_t)g_amcc_plane_va[ap];
                    int pl = g_lock_plane_count - 1;
                    do {
                        *(uint32_t *)(va + off + (uint32_t)(g_lock_plane_stride * pl)) = 1;
                        pl--;
                    } while (pl != -1);
                    ap++;
                } while (ap < g_amcc_planes);
                if (g_amcc_planes != 0) {
                    ap = 0;
                    do {
                        int pl = g_lock_plane_count;
                        do {
                            pl--;
                            do { } while (*(int *)(g_amcc_plane_va[ap] + off +
                                                   (uint32_t)(pl * g_lock_plane_stride)) != 0);
                        } while (pl != 0);
                        ap++;
                    } while (ap != g_amcc_planes);
                }
            }
            sptm_dmb();

            if (group == 3) {
                node = 0;
                if (sptm_dt_find_node(g_dt_root, 0, "chosen", &node) != 1)
                    sptm_panic_str("s %s /chosen lock_regs not found %s");
                uintptr_t cpm_node = node;
                val = 0; size = 0;
                if (sptm_dt_get_prop(node, "mc_hint_cpm_impl_offset", (uintptr_t *)&val,
                                     &size, g_dt_root, g_dt_root) == 1) {
                    if (size == 8) {
                        uint32_t off2 = *val;
                        uintptr_t cpu = sptm_percpu_state();
                        uintptr_t cpm = *(uintptr_t *)(sptm_uat_driver_state + cpu + 5);
                        val = 0; size = 0;
                        if (sptm_dt_get_prop(cpm_node, "mc_hint_cpm_impl_mask", (uintptr_t *)&val,
                                             &size, g_dt_root, g_dt_root) != 1)
                            goto missing;
                        if (size == 8) {
                            uint32_t mask = *val;
                            val = 0; size = 0;
                            if (sptm_dt_get_prop(cpm_node, "mc_hint_cpm_impl_val", (uintptr_t *)&val,
                                                 &size, g_dt_root, g_dt_root) != 1)
                                goto missing;
                            if (size == 8) {
                                sptm_dmb();
                                *(uint64_t *)(cpm + off2) =
                                    (*(uint64_t *)(cpm + off2) & ~(uint64_t)mask) | (uint64_t)*val;
                                goto program_ctrr;
                            }
                        }
                    }
badsize:
                    sptm_panic_str("s %s Found unexpected size for pr");
                }
            }
        }
        goto program_ctrr;
    } else {
        sptm_amcc_lock_regs_parse();
    }
program_ctrr:
    /* dcache-flush committed PAPT ranges, then program plane CTRR values. */
    ;
    uint32_t nc = g_papt_range_count;
    if (nc != 0) {
        uint32_t i = 0;
        do {
            if ((g_papt_range_flags[i] & 0x60) != 0 && (g_papt_range_flags[i] & 0x10) == 0) {
                sptm_dcache_flush(g_papt_range_va[i], (uint64_t)g_papt_range_pages[i] << 14);
                nc = g_papt_range_count;
            }
            i++;
        } while (i < nc);
    }
    if (g_amcc_planes != 0) {
        uint32_t ap = 0;
        uint64_t off = (uint64_t)group * 8;
        uint32_t *grp = &g_ctrr_group[off];
        do {
            int pl = g_lock_plane_count - 1;
            do {
                if (grp[1] != 0)   /* enable_off */
                    *(uint32_t *)(g_amcc_plane_va[ap] + grp[1] +
                                  (uint32_t)(g_lock_plane_stride * pl)) = grp[2];
                if (grp[3] != 0)   /* lo_off */
                    *(uint32_t *)(g_amcc_plane_va[ap] + grp[3] +
                                  (uint32_t)(g_lock_plane_stride * pl)) = grp[6];
                if (grp[6] != 0)   /* hi_off */
                    *(uint32_t *)(g_amcc_plane_va[ap] + grp[6] +
                                  (uint32_t)(g_lock_plane_stride * pl)) = grp[8];
                sptm_isb();
                pl--;
            } while (pl != -1);
            ap++;
        } while (ap < g_amcc_planes);
    }
    return;
missing:
    sptm_panic_str("s %s Could not find required prop");
}

/* ============================================================================
 * NVMe (ANS) driver
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * FUN_000c2ccc @ 0x000c2ccc   (est. sptm_nvme_validate_queue_entries)
 * Ghidra: void FUN_000c2ccc(int param_1, long param_2)
 * Validates the NVMe queue configuration against the driver state: the driver
 * must be initialized (state+0x14 bit3), `param_1` must equal the configured
 * queue-entries count (state+0x10), and `param_2` must equal the linear-SQ
 * flag (1) or the scatter-gather flag (2) derived from state+0x18 bit0.
 * Panics with codes 0x3000005 / 0x300000a / 0x300000b on mismatch.
 * Confidence: medium
 * Notes: NVMe state DAT_00094ab0; strings at 0x11690 / 0x11410. */
void sptm_nvme_validate_queue_entries(int entries, long mode)
{
    if ((*(uint32_t *)(sptm_nvme_state + 0x14) >> 3 & 1) == 0)
        sptm_panic(0x3000005, (uint64_t)mode, "s %s %s %d %s %llx %s %llx");
    if (entries == *(int *)(sptm_nvme_state + 0x10)) {
        long want = 1;
        if ((*(uint8_t *)(sptm_nvme_state + 0x18) & 1) == 0)
            want = 2;
        if (mode == want)
            return;
        sptm_panic(0x300000a, (uint64_t)mode, "s %s %s %d %s %llx");
    }
    sptm_panic(0x300000b, (uint64_t)mode, "s %s %s %d %s %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c3b94 @ 0x000c3b94   (est. sptm_nvme_bar_setup)
 * Ghidra: void FUN_000c3b94(undefined8 param_1, undefined8 param_2)
 * Programs the NVMe ANS register base addresses into the per-queue register
 * block: translates the ANS register frame VAs (state+0x120 / +0x128) to
 * physical via sptm_kvtophys and writes the lo/hi halves into the queue regs
 * (+0x108/+0x10c and +0x110/+0x114), sets the queue control field (+0x100)
 * to 0x3f, issues a DSB, and ORs the per-CPU flags (state+0x14) with 0x10 or
 * 0x6 depending on the linear-SQ bit (state+0x771). Panics 0x3000005 if the
 * driver is not initialized.
 * Confidence: medium
 * Notes: NVMe state DAT_00094ab0; per-queue base state+0x748; ANS frames
 *   translated via FUN_000d8a58. */
void sptm_nvme_bar_setup(uint64_t unused_a, uint64_t arg)
{
    if ((*(uint32_t *)(sptm_nvme_state + 0x14) & 1) != 0) {
        uint64_t ans_lo = sptm_kvtophys(*(void **)(sptm_nvme_state + 0x120));
        uint64_t qbase = *(uint64_t *)(sptm_nvme_state + 0x748);
        *(uint32_t *)(qbase + 0x108) = (uint32_t)ans_lo;
        *(uint32_t *)(qbase + 0x10c) = (uint32_t)(ans_lo >> 32);
        uint64_t ans_hi = sptm_kvtophys(*(void **)(sptm_nvme_state + 0x128));
        *(uint32_t *)(qbase + 0x110) = (uint32_t)ans_hi;
        *(uint32_t *)(qbase + 0x114) = (uint32_t)(ans_hi >> 32);
        *(uint32_t *)(qbase + 0x100) = 0x3f;
        sptm_dsb();
        uint32_t flags = 0x10;
        if ((*(uint8_t *)(sptm_nvme_state + 0x771) & 1) == 0)
            flags = 6;
        *(uint32_t *)(sptm_nvme_state + 0x14) |= flags;
        return;
    }
    sptm_panic(0x3000005, arg, "s %s %s %d %s %llx %s %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c3c78 @ 0x000c3c78   (est. sptm_nvme_init)
 * Ghidra: undefined8 FUN_000c3c78(void)
 * Full NVMe (ANS) driver init. Reads the NVMe security / secure-bar /
 * secure-reg-layout / linear-sq / prp-flush-wa / queue-entries / tl-wa /
 * vdma-wa / ans-reg / num-sl / ans-sha-present properties from the DT
 * /arm-io/ans nodes (via /defaults and arm-io), maps the ANS register frame
 * (0x28000 base + page stride), the secure register block, and (if tl-wa) the
 * SL / PA / VA table frames, allocates the TCB entries and queue buffers, and
 * zeroes the per-queue state. Panics on missing/malformed props or frame
 * allocation failure.
 * Confidence: medium
 * Notes: NVMe state DAT_00094ab0; DT iter DAT_00094ab8; helpers FUN_000e63c8
 *   (io translate), FUN_000e45a8 (frame alloc), FUN_000e41bc (boot alloc
 *   frames), FUN_000d8a58 (va_to_pa); TCB entries = state+0x10 * 0x80; flag
 *   g_bootstrap_stages bit7 gates TCB alloc. */
uint64_t sptm_nvme_init(void)
{
    uintptr_t defaults = 0, armio = 0, ans = 0;
    uintptr_t *val = 0; uint32_t size = 0;
    uintptr_t iter = g_dt_root;

    sptm_amcc_lock_regs_parse();
    sptm_nvme_state[0] = 0;   /* per-cpu state base captured in place */

    if (sptm_dt_find_node(iter, 0, "defaults", &defaults) != 1)
        sptm_panic_str("s %s Could not find /defaults");

    if (sptm_dt_get_prop(defaults, "nvme_iboot_sptm_security", (uintptr_t *)&val, &size,
                         iter, iter) != 1)
        sptm_panic_str("s %s Could not find /defaults");

    if (sptm_dt_find_node(iter, 0, "arm-io", &armio) != 1)
        sptm_panic_str("s %s Could not find /arm-io");

    if (sptm_dt_find_node(iter, armio, "ans", &ans) != 1)
        sptm_panic_str("s %s Could not find /arm-io ans");

    int has_secure_bar = 0, has_secure_reg = 0;
    val = 0; size = 0;
    has_secure_bar = sptm_dt_get_prop(ans, "nvme_secure_bar", (uintptr_t *)&val, &size,
                                      iter, iter) == 1;
    val = 0; size = 0;
    has_secure_reg = sptm_dt_get_prop(ans, "nvme_secure_reg_layout", (uintptr_t *)&val,
                                      &size, iter, iter) == 1;
    sptm_nvme_state[0x771] = (uint8_t)(has_secure_bar && has_secure_reg);
    if (has_secure_reg)
        sptm_nvme_state[0x771] = 1;
    sptm_nvme_state[0x9e9] = (uint8_t)has_secure_reg;

    val = 0; size = 0;
    int has_linear_sq = sptm_dt_get_prop(ans, "nvme_linear_sq", (uintptr_t *)&val, &size,
                                         iter, iter) == 1;
    sptm_nvme_state[0x18] = (uint8_t)(has_linear_sq != 1);   /* !linear_sq */

    val = 0; size = 0;
    if (sptm_dt_get_prop(ans, "nvme_prp_flush_wa", (uintptr_t *)&val, &size,
                         iter, iter) == 1)
        sptm_nvme_state[0x770] = 1;

    val = 0; size = 0;
    if (sptm_dt_get_prop(ans, "nvme_queue_entries", (uintptr_t *)&val, &size,
                         iter, iter) != 1)
        sptm_panic_str("s %s Couldn't find nvme_queue_ent");
    *(uint32_t *)(sptm_nvme_state + 0x10) = *val;

    val = 0; size = 0;
    int has_tl_wa = sptm_dt_get_prop(ans, "nvme_tl_wa", (uintptr_t *)&val, &size,
                                     iter, iter) == 1;
    sptm_nvme_state[0x7b9] = (uint8_t)has_tl_wa;

    val = 0; size = 0;
    int has_vdma_wa = sptm_dt_get_prop(ans, "nvme_vdma_wa", (uintptr_t *)&val, &size,
                                       iter, iter) == 1;
    sptm_nvme_state[0x9e8] = (uint8_t)has_vdma_wa;

    /* ans-reg node under arm-io/ans: holds the register region descriptors. */
    uintptr_t ans_reg = 0;
    if (sptm_dt_find_node(iter, ans, "ans-reg", &ans_reg) != 1)
        sptm_panic_str("s %s Could not find /arm-io ans r");
    val = 0; size = 0;
    if (sptm_dt_get_prop(ans_reg, "reg", (uintptr_t *)&val, &size, iter, iter) != 1)
        sptm_panic_str("s %s Could not find /arm-io ans r");
    if (size < 0x40)
        sptm_panic_str("s %s /arm-io ans reg bad size");

    uint64_t ans_size = *(uint64_t *)((uint8_t *)val + 0x38);
    if (ans_size >> 14 < 0xb)
        sptm_panic_str("s %s Unexpected ANS register size");
    uint64_t ans_base = *(uint64_t *)((uint8_t *)val + 0x30);
    uint64_t ans_pa = sptm_dt_io_translate((void *)iter, ans_base, ans_size);
    uint64_t ans_va = sptm_frame_alloc(ans_pa + 0x28000, 1, 0);
    *(uint64_t *)(sptm_nvme_state + 0x748) = ans_va;
    if (ans_va == 0xffffffff)
        goto alloc_fail;

    /* Secure register block (separate region unless secure_reg_layout). */
    uint64_t sreg = 0;
    if ((sptm_nvme_state[0x9e9] & 1) == 0) {
        if ((sptm_nvme_state[0x771] & 1) != 0) {
            uint64_t sb = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0x90),
                                               *(uint64_t *)((uint8_t *)val + 0x98));
            sreg = sptm_frame_alloc(sb, 4, 0);
        } else {
            sreg = *(uint64_t *)(sptm_nvme_state + 0x778);
        }
    } else {
        uint64_t sb = sptm_dt_io_translate((void *)iter, ans_base, ans_size);
        sreg = sptm_frame_alloc(sb + 0x4000, 1, 0);
    }
    *(uint64_t *)(sptm_nvme_state + 0x778) = sreg;
    if (sreg == 0xffffffff)
        goto alloc_fail;

    /* vdma_wa: map the VDMA table frame. */
    if ((sptm_nvme_state[0x9e8] & 1) != 0) {
        uint64_t vb = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0xd0),
                                           *(uint64_t *)((uint8_t *)val + 0xd8));
        uint64_t vv = sptm_frame_alloc(vb, *(uint64_t *)((uint8_t *)val + 0xd8) >> 14, 0);
        if (vv == 0xffffffff)
            goto alloc_fail;
        *(uint64_t *)(sptm_nvme_state + 0x9e0) = vv + 0x20000;
    }

    /* tl_wa: map the SL / PA / VA table frames + num_sl. */
    if ((sptm_nvme_state[0x7b9] & 1) != 0) {
        val = 0; size = 0;
        if (sptm_dt_get_prop(ans, "nvme_num_sl", (uintptr_t *)&val, &size, iter, iter) != 1)
            sptm_panic_str("s %s Could not find nvme_num_sl");
        *(uint32_t *)(sptm_nvme_state + 0x7d8) = *val;
        uint64_t sl_sz = *(uint64_t *)((uint8_t *)val + 0xc8);
        uint64_t sl = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0xc0),
                                           sl_sz);
        uint64_t sl_va = sptm_frame_alloc(sl, sl_sz >> 14, 0);
        *(uint64_t *)(sptm_nvme_state + 0x7c0) = sl_va;
        if (sl_va == 0xffffffff)
            goto alloc_fail;
        uint64_t pa_sz = *(uint64_t *)((uint8_t *)val + 0xa8);
        uint64_t pa = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0xa0),
                                           pa_sz);
        uint64_t pa_va = sptm_frame_alloc(pa, pa_sz >> 14, 0);
        *(uint64_t *)(sptm_nvme_state + 0x7c8) = pa_va;
        if (pa_va == 0xffffffff)
            goto alloc_fail;
        uint64_t va_sz = *(uint64_t *)((uint8_t *)val + 0xb8);
        uint64_t vab = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0xb0),
                                            va_sz);
        uint64_t vava = sptm_frame_alloc(vab, va_sz >> 14, 0);
        *(uint64_t *)(sptm_nvme_state + 2000) = vava;
        if (vava == 0xffffffff)
            goto alloc_fail;
    }

    /* ans_sha_present: map the ANS SHA register frame. */
    val = 0; size = 0;
    if (sptm_dt_get_prop(ans, "nvme_ans_sha_present", (uintptr_t *)&val, &size,
                         iter, iter) == 1) {
        sptm_nvme_state[0x9ea] = 1;
        uint64_t sh_sz = *(uint64_t *)((uint8_t *)val + 0xe8);
        uint64_t sh = sptm_dt_io_translate((void *)iter, *(uint64_t *)((uint8_t *)val + 0xe0),
                                           sh_sz);
        uint64_t sh_va = sptm_frame_alloc(sh, sh_sz >> 14, 0);
        *(uint64_t *)(sptm_nvme_state + 0x9f0) = sh_va;
        if (sh_va == 0xffffffff)
            goto alloc_fail;
    }

    /* optional chosen/carveout-memory-map region id */
    uintptr_t chosen = 0;
    if (sptm_dt_find_node(iter, 0, "chosen", &chosen) == 1) {
        uintptr_t map_node = 0;
        if (sptm_dt_find_node(iter, chosen, "carveout-memory-map", &map_node) == 1) {
            char rbuf[0x40];
            sptm_format_region_id(rbuf, 0x37);
            val = 0; size = 0;
            if (sptm_dt_get_prop(map_node, rbuf, (uintptr_t *)&val, &size,
                                 iter, iter) == 1) {
                if (size != 0x10)
                    sptm_panic_str("s %s Unexpected size of region id");
                *(uint64_t *)(sptm_nvme_state + 0x768) = ((uint64_t *)val)[1];
                *(uint64_t *)(sptm_nvme_state + 0x760) = ((uint64_t *)val)[0];
            }
        }
    }

    /* Validate + allocate TCB entries. */
    uint32_t entries = *(uint32_t *)(sptm_nvme_state + 0x10);
    if (entries == 0)
        sptm_panic_str("s %s Zero TCB entries per queue i");
    if (entries > 0x101)
        sptm_panic_str("s %s Too many TCB entries per que");

    *(uint32_t *)(sptm_nvme_state + 0x14) = 0x109;
    uint16_t i;
    for (i = 0; i < entries; i++)
        sptm_nvme_state[0x19 + i] = 0;
    sptm_nvme_state[0x7b0] = sptm_nvme_state[0x7b1] = sptm_nvme_state[0x7b2] =
        sptm_nvme_state[0x7b3] = sptm_nvme_state[0x7b4] = sptm_nvme_state[0x7b5] =
        sptm_nvme_state[0x7b6] = sptm_nvme_state[0x7b7] = sptm_nvme_state[0x7b8] = 0;

    if ((g_bootstrap_stages >> 7 & 1) == 0) {
        uint64_t tcb_pages = ((uint64_t)entries * 0x800 + 0x3fff) >> 14;
        uint64_t tcb = sptm_boot_alloc_frames(10, tcb_pages);
        if (tcb != 0) {
            uint64_t tcb_pa = sptm_kvtophys((void *)tcb);
            *(uint64_t *)(sptm_nvme_state + 0x750) = tcb_pa;
            *(uint64_t *)(sptm_nvme_state + 0x758) = tcb;
            *(uint32_t *)(sptm_nvme_state + 0x780) = 0xffffffff;
            *(uint64_t *)(sptm_nvme_state + 0x788) = 0xffffffffffffffffULL;
            *(uint64_t *)(sptm_nvme_state + 0x790) = 0xffffffffffffffffULL;
            *(uint32_t *)(sptm_nvme_state + 0x798) = 0xffffffff;
            *(uint64_t *)(sptm_nvme_state + 0x7a8) = 0xffffffffffffffffULL;
            *(uint64_t *)(sptm_nvme_state + 0x7a0) = 0xffffffffffffffffULL;
            *(uint64_t *)(sptm_nvme_state + 0x9f8) = 0xffffffffffffffffULL;
            *(uint32_t *)(sptm_nvme_state + 0xa00) = 0xffffffff;
            if ((g_bootstrap_stages >> 7 & 1) != 0)
                goto unexpected;
            uint32_t qt = (uint32_t)(*(int *)(sptm_nvme_state + 0x10) * 0x80 + 0xfff) & 0xfffff000;
            uint64_t qsz = qt;
            uint64_t mult = 1;
            if ((sptm_nvme_state[0x18] & 1) != 0)
                mult = 2;
            uint64_t qb = sptm_boot_alloc_frames(10, ((qsz << mult) + 0x3fff) >> 14);
            if (qb != 0) {
                *(uint64_t *)(sptm_nvme_state + 0x120) = qb;
                *(uint64_t *)(sptm_nvme_state + 0x128) = qb + qsz;
                if ((sptm_nvme_state[0x18] & 1) != 0) {
                    uint64_t qb2 = qb + (uint64_t)(qt << 1);
                    *(uint64_t *)(sptm_nvme_state + 0x130) = qb2;
                    *(uint64_t *)(sptm_nvme_state + 0x138) = qb2 + qsz;
                }
                return 0;
            }
        }
        sptm_panic_str("s %s iommu_bootstrap_alloc_frames");
    }
unexpected:
    sptm_panic_unexpected_bootstrap();
alloc_fail:
    sptm_panic_str("s %s %s invalid papt returned by");
}

/* ============================================================================
 * UAT state / table helpers + misc
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * FUN_000c5248 @ 0x000c5248   (est. sptm_uat_state_get)
 * Ghidra: void FUN_000c5248(ulong param_1, uint param_2, byte param_3)
 * Acquires a UAT driver state by id. If the current state (mode at
 * sptm_uat_driver_state+0x10) already matches `id`, it reuses it; otherwise it
 * validates the id (a physical address): 16 KiB aligned within the state
 * stride (state+0x1c0), in DRAM (or phystokv), and its FTE refcount field must
 * be 0 (else panic 0x4000000). The resolved state's type byte (+0x1a) must
 * match `mode` (param_2) after OR-ing the permission `mask` (param_3) into the
 * FTE flags (else panic 0x4000002/0x4000004). Returns the state pointer.
 * Confidence: medium
 * Notes: DAT_00095d08; FTE refcount via FUN_000c5550; permission mask check
 *   `(*va & param_3) == 0` -> panic 0x4000002. */
uint8_t *sptm_uat_state_get(uint64_t id, int mode, int mask)
{
    uint64_t cur = *(uint64_t *)(sptm_uat_driver_state + 0x10);
    if (cur == 0) {
        uint64_t cur_id = sptm_kvtophys(*(void **)(sptm_uat_driver_state + 0x18));
        if (id == cur_id)
            goto found;
        cur = *(uint64_t *)(sptm_uat_driver_state + 0x10);
    }
    if (cur == 1) {
        uint64_t cur_id = sptm_kvtophys(*(void **)(sptm_uat_driver_state + 0x18));
        if (id == cur_id)
            goto found;
    }
    sptm_paddr_validate(id, 0x18);
    uint64_t off = id & 0x3fff;
    uint64_t stride = *(uint64_t *)(sptm_uat_driver_state + 0x1c0);
    uint64_t q = 0;
    if (stride != 0)
        q = off / stride;
    if ((off != q * stride) || (0x4000 < stride + off))
        sptm_panic(0x4000005, 0, "s %s %s %d %s %llx %s %llx");

    void *va;
    if ((id < g_mem_phys_base) || (g_mem_phys_end <= id)) {
        va = sptm_phystokv(id);
        if (va == 0)
            va = (void *)0x101f90;
    } else {
        va = (void *)(g_page_desc + ((id - g_mem_phys_base) >> 10 & 0xffffffff0ULL));
        if ((((uint64_t)g_page_desc ^ (uint64_t)va) & 0xffc0000000000000ULL) != 0)
            va = (void *)((uint64_t)va & 0xffffffffffffULL | 0xc8a2000000000000ULL);
    }
    if (*(int *)((uint8_t *)va + 4) != 0) {
        sptm_uat_fte_get(id);
        sptm_panic(0x4000000, 0, "s %s %s %d %s %llx");
    }
found:
    /* compute the state VA (linear window or region table) */
    ;
    void *state;
    if ((g_bootstrap_stages >> 8 & 1) == 0) {
        state = (void *)((id - g_mem_phys_base) + g_papt_va_base);
    } else {
        uint64_t n = g_committed_range_count;
        if (n != 0) {
            uintptr_t *r = g_committed_range_base;
            do {
                uint64_t base = r[0];
                if ((base <= id) && (id < base + (uint64_t)(uint32_t)r[2] * 0x4000)) {
                    state = (void *)((id - base) + r[1]);
                    goto state_resolved;
                }
                r += 3;
                n--;
            } while (n != 0);
        }
        state = sptm_phystokv_outside_window(id);
    }
state_resolved:
    if ((*(uint8_t *)state & (uint8_t)mask) == 0)
        sptm_panic(0x4000002, 0, "s %s %s %d %s %llx %s %llx");
    uint8_t *tb = (uint8_t *)state + 0x1a;
    uint8_t b = *tb;
    if (b == (uint8_t)mode)
        *tb = 1;
    if (b == (uint8_t)mode)
        return state;
    sptm_panic(0x4000004, 0, "s %s %s %d %s %llx %s %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c5550 @ 0x000c5550   (est. sptm_uat_fte_get)
 * Ghidra: undefined2 * FUN_000c5550(ulong param_1)
 * Returns a pointer to the FTE refcount field (+8, or +4 for out-of-window)
 * of the page descriptor for `paddr`. Used by the UAT state helpers to test
 * whether a frame is already referenced.
 * Confidence: medium
 * Notes: DAT_00095460 page desc stride 0x10; out-of-window via FUN_000e3d7c
 *   falling back to the invalid FTE DAT_00101f90. */
uint32_t *sptm_uat_fte_get(uint64_t paddr)
{
    if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
        uint16_t *d = (uint16_t *)sptm_phystokv(paddr);
        if (d == 0)
            d = (uint16_t *)0x101f90;
        return (uint32_t *)((uint8_t *)d + 4);
    }
    uint64_t va = (uint64_t)(g_page_desc + ((paddr - g_mem_phys_base) >> 10 & 0xffffffff0ULL));
    if ((((uint64_t)g_page_desc ^ va) & 0xffc0000000000000ULL) != 0)
        va = (va & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
    return (uint32_t *)(va + 8);
}

/* --------------------------------------------------------------------------
 * FUN_000c55cc @ 0x000c55cc   (est. sptm_uat_table_translate)
 * Ghidra: ulong FUN_000c55cc(ulong param_1, int param_2)
 * Validates/translates a UAT table physical address. Checks the FTE type
 * field (+4) matches `type` (param_2) (else panic 0x4000000), the address is
 * 16 KiB aligned and of the 0x1 page class (else panic 0x4000009), and
 * returns the validated paddr. Used to validate UAT root/table frames.
 * Confidence: medium
 * Notes: DAT_00095460 page desc; FTE type at +4. */
uint64_t sptm_uat_table_translate(uint64_t paddr, int type)
{
    sptm_paddr_validate(paddr, 0x18);
    uint8_t *d;
    if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
        uint8_t *t = (uint8_t *)sptm_phystokv(paddr);
        d = (t == 0) ? (uint8_t *)0x101f90 : t;
    } else {
        uint64_t va = (uint64_t)(g_page_desc + ((paddr - g_mem_phys_base) >> 10 & 0xffffffff0ULL));
        if ((((uint64_t)g_page_desc ^ va) & 0xffc0000000000000ULL) != 0)
            va = (va & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
        d = (uint8_t *)va;
    }
    if (*(int *)(d + 4) == type) {
        if ((paddr & 0x3fff) == 0) {
            if (paddr >> 0x28 == 1)
                return paddr;
            sptm_panic(0x4000009, 0, "s %s %s %d %s %llx %s %llx");
        }
        sptm_panic(0x4000009, 0, "s %s %s %d %s %llx");
    }
    sptm_uat_fte_get(paddr);
    sptm_panic(0x4000000, 0, "s %s %s %d %s %llx %s %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c5784 @ 0x000c5784   (est. sptm_uat_va_walk)
 * Ghidra: void FUN_000c5784(ulong param_1, ulong param_2, byte *param_3,
 *                            ulong *param_4)
 * Walks the UAT tables to validate/translate a [va, va+size) range: verifies
 * the va page falls in the root table selected by the UAT root index bit
 * (state+0x1a1), the range is 16 KiB aligned and non-empty, and lies entirely
 * within the UAT global/private root window for the state's mode (state+0x10
 * 1 => private roots at +0x50/+0x40, else shared at +0x30/+0x20). On success
 * writes the translated base to *param_4. Panics 0x4000008 on any violation
 * and on mode/type mismatches.
 * Confidence: medium
 * Notes: DAT_00095d08; mode type byte *param_3 selects global(1)/private(4)
 *   roots; root index bit from state+0x1a1. */
void sptm_uat_va_walk(uint64_t va, uint64_t size, uint8_t *state, uint64_t *out)
{
    uint64_t root_bit = (va >> (*(uint8_t *)(sptm_uat_driver_state + 0x1a1) & 0x3f)) & 1;
    uint8_t type = *state;
    uint8_t mode = 5;
    if (root_bit != 0)
        mode = 0xe;
    if ((mode & type) == 0)
        sptm_panic(0x4000008, size, "s %s %s %d %s %llx %s %llx");

    if ((((va & 0x3fff) == 0) && (size != 0) && ((size & 0x3fff) == 0)) &&
        !(va > (va + size - 1))) {
        uint64_t lo = 0, hi = 0;
        if (type < 4) {
            if (type == 1) {
                if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 0)
                    sptm_panic_str("s %s Accessing Shared Mode global");
                lo = *(uint64_t *)(sptm_uat_driver_state + 0x20 + root_bit * 8);
                hi = *(uint64_t *)(sptm_uat_driver_state + 0x30 + root_bit * 8);
            } else if (type == 2) {
                if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 0)
                    sptm_panic_str("s %s Accessing Shared Mode global");
                lo = *(uint64_t *)(sptm_uat_driver_state + 0x40 + root_bit * 8);
                hi = *(uint64_t *)(sptm_uat_driver_state + 0x50 + root_bit * 8);
            }
        } else {
            if (type == 4) {
                if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 1)
                    sptm_panic_str("s %s Accessing Private Mode globa");
                lo = *(uint64_t *)(sptm_uat_driver_state + 0x20 + root_bit * 8);
                hi = *(uint64_t *)(sptm_uat_driver_state + 0x30 + root_bit * 8);
            } else if (type == 8) {
                if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 1)
                    sptm_panic_str("s %s Accessing Private Mode globa");
                lo = *(uint64_t *)(sptm_uat_driver_state + 0x40 + root_bit * 8);
                hi = *(uint64_t *)(sptm_uat_driver_state + 0x50 + root_bit * 8);
            }
        }
        if ((lo <= va) && (va + (size - 1) <= hi)) {
            if (out != 0)
                *out = va;
            return;
        }
    }
    sptm_panic(0x4000008, size, "s %s %s %d %s %llx %s %llx");
}

/* --------------------------------------------------------------------------
 * FUN_000c59b8 @ 0x000c59b8   (est. sptm_snprintf_wrap)
 * Ghidra: void FUN_000c59b8(param_1,param_2,param_3,param_4)
 * Thin snprintf wrapper: forwards (dst=param_1, maxlen=param_3, unused=0,
 * maxlen2=param_2, fmt=param_4) to the fortified snprintf.
 * Confidence: high
 * Notes: FUN_000ad278. */
void sptm_snprintf_wrap(void *dst, uint64_t maxlen2, uint64_t maxlen,
                        const char *fmt, uint64_t arg)
{
    sptm_snprintf(dst, maxlen, 0, maxlen2, fmt, arg);
}

/* --------------------------------------------------------------------------
 * FUN_000c59f4 @ 0x000c59f4   (est. sptm_uat_handoff_magic)
 * Ghidra: undefined2 FUN_000c59f4(void)
 * Reads the per-CPU UAT handoff-region magic value (a u16 at the handoff
 * region + cpu + 10) used to detect a valid handoff context. Returns 0 when
 * no valid handoff is armed.
 * Confidence: medium
 * Notes: handoff region string anchor s_uat_instance_>handoff_region_>mi;
 *   reads (3,6,0xf,8,0) else tpidr_el2 else (3,6,0xf,0xb,1). */
uint16_t sptm_uat_handoff_magic(void)
{
    uintptr_t cpu = sptm_percpu_state();
    return *(uint16_t *)(sptm_uat_driver_state + cpu + 10);
}

/* --------------------------------------------------------------------------
 * FUN_000c5a18 @ 0x000c5a18   (est. sptm_hang_spin)
 * Ghidra: void FUN_000c5a18(void)
 * Infinite self-spin with x0=0x9898. A deliberate fail-stop hang (the "do
 * nothing" loop) reached when no other recovery is possible.
 * Confidence: high
 * Notes: `mov x0,#0x9898; b .`; called from the panic/vector tail. */
__attribute__((noreturn))
void sptm_hang_spin(void)
{
    for (;;) {
        __asm__ volatile("mov x0, #0x9898" ::: "x0");
    }
}
