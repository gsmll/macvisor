/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the bootstrap-stage announcement / handoff helpers (the
 * "SK bootstrap complete" / BootKC_rx / TXM_rx stage transitions that publish
 * the XNU exception vector and per-stage PAPT mappings), the CPU-trace
 * carve-out configuration, the device-tree key reader used by hibernation,
 * and the memory/crypto helpers (memmove, DT key copy, SHA-2 page-range
 * hashing, and the crypto-engine digest finalize) that underpin the
 * hibernation integrity gate.
 *
 * GENTER/GEXIT are opaque (opcode 0x00201420 / 0x00201400); the guard-level
 * caller selects the dispatch endpoint via x16 (SPTM_LOAD_DISPATCH_ID).
 * Ghidra FUN_ names are retained in comments; no code-level Ghidra
 * identifiers remain in the bodies.
 */

#include <stdint.h>
#include <string.h>

#include "sptm_internal.h"

/* ============================================================================
 * Shared SPTM primitives (declared extern; ground-truth FUN_ addresses).
 * ==========================================================================*/

/* noreturn panic. code = SPTM panic code; fmt = one of the panic format
 * strings whose leading %s/%s/%d are resolved from the caller's return
 * address by the panic machinery. FUN_000f8844 */
__attribute__((noreturn)) void sptm_panic(uint32_t code, uint64_t arg, const char *fmt, ...);
/* noreturn assertion panic (fixed "%s: %s %s at pc 0x%016llx lr ..." tail).
 * FUN_000f8804 */
__attribute__((noreturn)) void sptm_panic_assert(const char *msg);

/* Return the SPTM per-CPU context pointer for the current CPU. Inline pattern:
 * read s3_6_c15_c8_0; if 0 use tpidr_el2, else read s3_6_c15_c11_1. */
uint64_t sptm_per_cpu_state(void);

/* EL3 IMP-DEF system register access used for the CPU trace unit control. */
uint64_t sptm_sysreg_read(unsigned op0, unsigned op1, unsigned crn, unsigned crm, unsigned op2);
void    sptm_sysreg_write(unsigned op0, unsigned op1, unsigned crn, unsigned crm, unsigned op2, uint64_t value);
uint64_t read_tpidr_el2(void);
uint64_t read_vbar_el1(void);

/* Guard / rw-lock primitives. FUN_000e2480 / FUN_000e5f8c. */
void sptm_guard_op(uint16_t *guard, int op);
void sptm_lo_release(void);

/* Debug print ("[%s] ..." console writer). FUN_000c15b4 */
void sptm_dbg_print(const char *fmt, ...);
/* Debug init (probe the debug/output path). FUN_000c172c */
void sptm_dbg_init(void);

/* Dispatch-engine init. FUN_000b8230 */
void sptm_dispatch_engine_init(void);
/* TXM entry dispatch (context-save + guarded hop). FUN_000a10e0 */
void sptm_txm_entry(void *state);
/* Early SK entry dispatch. FUN_000a11e0 */
void sptm_sk_entry_early(void);
/* Enter the guarded dispatch domain with the given selector. FUN_000a121c */
void sptm_enter_domain(uintptr_t selector, uintptr_t *ctx, uintptr_t *out,
                       uintptr_t *arg4, uintptr_t arg5);

/* Per-CPU bootstrap. FUN_000dce04 (index) / FUN_000baa60 (state). */
void sptm_cpu_init(uint32_t cpu);
void sptm_init_sched(uint8_t *state);
/* TXM handoff (translate a TXM-owned PA to SPTM VA). FUN_000d8a58 */
uintptr_t sptm_txm_handoff(void);

/* Boot-image region announce/map. FUN_000d9be8 maps a named region type. */
void sptm_memmap_available(const char *name, uint32_t a, uint32_t b);
/* String compare on a PAPT range name. thunk_FUN_000ac190 */
int  sptm_strcmp(const char *a, const char *b);

/* PAPT range table: count at 0x10012f0, entries (stride 5 words) at 0x10012f8.
 * Each entry: {name, ?, ?, va_base, page_count}. */
extern uint64_t g_papt_count;    /* DAT_001012f0 */
extern const uint64_t g_papt[];  /* DAT_001012f8, stride 5 */
/* XNU EL2 exception vector slot. DAT_00095cf8 */
extern uint64_t *sptm_xnu_el2_exception_vector;
/* Bootstrap-stage feature bitmask. DAT_001012d8 */
extern uint64_t g_feature_flags;
/* Hibernation enable bit (DAT_00100e00 bit0). */
extern uint8_t sptm_hib_enabled;

/* Device-tree helpers. FUN_000b79e8 / FUN_000b7c04 / FUN_000e9f28. */
extern int sptm_dt_find_node(uintptr_t iter, uintptr_t parent, const char *name,
                             uintptr_t *out);
extern int sptm_dt_get_prop(uintptr_t node, const char *name, uintptr_t *out_val,
                            uint32_t *out_size, uintptr_t iter, uintptr_t ctx);
__attribute__((noreturn)) void sptm_panic_hib(const char *file, int line,
                                              const char *msg, uint64_t arg,
                                              uint64_t key);   /* FUN_000e9f28 */

/* Per-CPU DART driver state. FUN_000e4d78 */
void *sptm_percpu_base(uint64_t hint, uint64_t *dbg_out);
/* Allocate `count` elements of `size` bytes (returns VA). FUN_000e41bc */
void *sptm_alloc_elements(uint64_t count, uint64_t size);
/* Register/track a named SPTM subsystem (string arg). FUN_000e4424 */
void sptm_subsys_register(const char *name);

/* Frame descriptor lookup / PA->VA resolution. FUN_000e3d7c / FUN_000e40ec. */
uint16_t *sptm_frame_lookup(uint64_t va);
uintptr_t sptm_va_lookup(uintptr_t pa);
/* Zero a scratch region. thunk_FUN_000abb60 */
void sptm_scratch_zero(void *dst, uint64_t len);
/* Bounded block fill (wraps __memset_s_chk). FUN_000b2584 */
void sptm_bzero_block(size_t n, void *dst);

/* Stack-check (canary) failure is noreturn. FUN_000ae44c */
__attribute__((noreturn)) void sptm_stack_check(void);

/* SHA-2 hash object (DAT_00104120) and helpers (FUN_000ae8b4 / FUN_000aeaa4).
 * The crypto-engine finalize (FUN_000bf874) is defined in this file. */
typedef struct sptm_sha_obj {
    uint64_t len_bytes;          /* +0x08 context working length */
    uint8_t  pad0[0x28 - 0x10];
    uint64_t iv_ptr;             /* +0x28 */
    void (*finalize)(struct sptm_sha_obj *, void *ctx, void *out);  /* +0x38 */
} sptm_sha_obj_t;
void sptm_sha_reset(sptm_sha_obj_t *obj, void *ctx);
void sptm_sha_update(sptm_sha_obj_t *obj, void *ctx, uint64_t len, const void *data);
extern sptm_sha_obj_t *g_sha_obj;       /* DAT_00104120 (ptr) */
extern uint8_t  g_sha_ctx[];            /* DAT_001040b0 */
extern uint8_t  g_hib_state;            /* DAT_001040a8 */
extern uint8_t  g_sk_hib_started;       /* DAT_00104128 */
extern uint16_t g_sk_hib_percpu;        /* DAT_0010412a */
extern uint32_t g_hibseg_cpu;           /* DAT_00100cb0 */
extern uint64_t g_dram_start;           /* DAT_00095d18 */
extern uint64_t g_dram_end;             /* DAT_00095d20 */
extern uint64_t g_linear_offset;        /* DAT_00095110 */
extern uint32_t g_reloc_count;          /* DAT_00101ac8 */
extern const uint64_t g_reloc_table[];  /* DAT_00101ad0 */
/* Page metadata (PTE descriptor) base table. DAT_00095460 */
extern const uint8_t g_page_desc[];
/* FTE type -> class / per-FTE refcount tables. */
extern const uint8_t g_ftype_class[];   /* DAT_00095d56 (byte, stride 0x90) */
extern const uint8_t g_ftype_class2[];  /* DAT_00095d51 (byte, stride 0x90) */
/* Zero-page / scratch VA providers used by the hashing paths. */
extern uint64_t sptm_zero_page_begin(void);  /* FUN_000e03f4 */
extern uint64_t sptm_zero_page_addr(void);   /* FUN_000e0770 */
extern void     sptm_zero_page_release(void);/* FUN_000e05bc */
/* fallback descriptor used when a page has no descriptor. DAT_00101f90 */
extern const uint16_t g_fallback_desc;

/* Crypto-engine (ACE) context / helpers for digest finalize. */
void *sptm_crypto_ctx(void);                       /* FUN_000b25b0 */
void  sptm_gcm_update_barr(uint64_t *ctx, uint64_t *buf, size_t len, const uint8_t *data); /* FUN_000b07bc */
void  sptm_gcm_finalize_barr(uint64_t *ctx, uint64_t *out, uint64_t tag);                  /* FUN_000b0504 */
/* SK entry for HIB patchup. FUN_000b2608 */
int   sptm_sk_hib_patchup(void);

/* Produces the final protected digest from a SHA digest (FUN_000bf4bc),
 * defined later in this file. */
void sptm_crypto_finalize(void *ace_ctx, const uint8_t *digest, uint8_t *out);
/* Crypto-engine (ACE) finalize producing the image digest (FUN_000bf874),
 * defined later in this file. */
void sptm_ace_finalize(uint64_t ace_ctx, const void *digest_in, void *out);

/* Handoff-page list (DAT_00094000 count, DAT_00094004 entries). */
extern uint32_t g_handoff_count;       /* DAT_00094000 */
extern const uint32_t g_handoff_pages[]; /* DAT_00094004 */

/* Bootstrap-stage globals used by the SK/TXM stage-announce helpers. */
extern uint64_t g_slide;               /* DAT_00100448 (SLID=param_1-DAT_00094370) */
extern uint64_t g_kern_base;           /* DAT_00094370 */
extern uint64_t g_boot_va;             /* DAT_00100728 */
extern uint64_t g_dt_handoff_key;      /* DAT_00094482 */
extern uint64_t g_dt_handoff_flag;     /* DAT_00094480 */
/* per-CPU state selectors written by the handoff helpers. */
#define PERCPU_OFF_A30   0xa30
#define PERCPU_OFF_A60   0xa60
#define PERCPU_OFF_A68   0xa68
/* UAT handoff-region magic offset used by the boot stages (0x142e base). */
#define UAT_HANDOFF_MAGIC 0x142e

/* Memory-mapping helpers used by the SK->TXM handoff. */
void  sptm_teardown_el2_alloc(uint64_t n);        /* FUN_000d7f80 */
void  sptm_map_handoff(uint64_t va, uint64_t pages, uint64_t a, uint64_t b); /* FUN_000d8bf8 */

/* ============================================================================
 * FUN_000bc19c  sptm_boot_stage_bootkc
 * Ghidra: void FUN_000bc19c(void)
 * Announces the BootKC bootstrap stage: maps the BootKC_rx boot region, reads
 * vbar_el1 and publishes it into the XNU EL2 exception-vector slot
 * (DAT_00095cf8) only if it lies within the BootKC_rx PAPT range, then sets
 * the bootstrap-stage bit 0x10 and enables EL1 (SCTLR_EL1 bit0). Refuses to
 * run if the stage was already announced. Confidence: medium. Notes: PAPT
 *   range table at DAT_001012f8 (stride 5 words {name,?,?,va_base,page_count});
 *   a missing BootKC_rx PAPT range panics. */
void
sptm_boot_stage_bootkc(void)
{
    uint64_t vbar, page_count, i;
    const uint64_t *range;

    if (((uint32_t)g_feature_flags >> 0x10 & 1) != 0) {
        sptm_panic_assert("Unexpected bootstrap stages r");
    }
    sptm_memmap_available("BootKC_rx", 0x23, (uint32_t)g_dt_handoff_key);
    vbar = read_vbar_el1();

    if (g_papt_count != 0) {
        range = g_papt;                      /* stride 5 words */
        for (i = 0; i < g_papt_count; i++) {
            if (sptm_strcmp((const char *)range[0], "BootKC_rx") == 0) {
                page_count = (uint64_t)*(uint32_t *)(range + 4) * 0x4000;
                if (vbar < range[3] || range[3] + page_count <= vbar) {
                    sptm_panic(0x2c, 0, "s %s %s %d %s %llx %s %llx");
                }
                *sptm_xnu_el2_exception_vector = vbar;
                __asm__ volatile("isb" ::: "memory");
                sptm_sysreg_write(3, 4, 0xf, 1, 2,
                    sptm_sysreg_read(3, 4, 0xf, 1, 2) | 1);   /* SCTLR_EL1 */
                __asm__ volatile("isb" ::: "memory");
                g_feature_flags |= 0x10000;
                sptm_lo_release();
                if (((uint32_t)g_feature_flags >> 0x10 & 1) == 0) {
                    return;
                }
                sptm_panic_assert("Attempted to announce bootstrap stage twice");
            }
            range += 5;
        }
    }
    sptm_panic_assert("s %s %s: PAPT range not found");
}

/* ============================================================================
 * FUN_000bc338  sptm_boot_stage_txm
 * Ghidra: void FUN_000bc338(void)
 * Announces the TXM bootstrap stage: maps the TXM_rx boot region and sets the
 * bootstrap-stage bit 0xe (0x4000). Refuses to run if already announced.
 * Confidence: medium. */
void
sptm_boot_stage_txm(void)
{
    uint64_t old;

    if (((uint32_t)g_feature_flags >> 0xe & 1) != 0) {
        sptm_panic_assert("Unexpected bootstrap stages r");
    }
    sptm_memmap_available("TXM_rx", 0x2b, 5);
    old = g_feature_flags;
    g_feature_flags |= 0x4000;
    sptm_lo_release();
    if (((uint32_t)old >> 0xe & 1) == 0) {
        return;
    }
    sptm_panic_assert("Attempted to announce bootstrap stage twice");
}

/* ============================================================================
 * FUN_000bc084  sptm_sk_bootstrap_complete
 * Ghidra: void FUN_000bc084(long param_1)
 * Runs at the SK bootstrap-complete transition: records the slide, verifies
 * the UAT handoff-region magic, and when present configures the current
 * per-CPU state (0xa30=5, 0xa68=0, 0xa60=5) and enters dispatch domain 1
 * (TXM). Otherwise tears down the EL2 allocation, maps the remainder of the
 * handoff pages, re-inits the dispatch engine, prints "Starting TXM" and
 * dispatches into TXM. Confidence: medium. Notes: per-CPU state via
 *   sptm_per_cpu_state(); UAT handoff magic at 0x142e + percpu + 10. */
void
sptm_sk_bootstrap_complete(uint64_t param_1)
{
    uint64_t percpu, aligned, n_pages;
    int16_t handoff_magic;

    sptm_dbg_print("SK bootstrap complete");
    g_slide = param_1 - g_kern_base;

    percpu = sptm_per_cpu_state();
    handoff_magic = *(int16_t *)(UAT_HANDOFF_MAGIC + percpu + 10);

    if (handoff_magic != 0) {
        percpu = sptm_per_cpu_state();
        *(uint8_t *)(percpu + PERCPU_OFF_A30) = 5;
        percpu = sptm_per_cpu_state();
        *(uint64_t *)(percpu + PERCPU_OFF_A68) = 0;
        percpu = sptm_per_cpu_state();
        *(uint8_t *)(percpu + PERCPU_OFF_A60) = 5;
        sptm_enter_domain(1, (uintptr_t *)0x94498, (uintptr_t *)0x1002c0, 0, 0);
        sptm_panic_assert("SK bootstrap complete -> TXM never returns");
    }

    sptm_teardown_el2_alloc(0x1000);
    aligned = param_1 + 0x3fff & 0xffffffffffffc000;
    n_pages = (aligned - g_boot_va) >> 0xe;
    sptm_map_handoff(g_boot_va, n_pages, 0, 0x3e);
    g_boot_va = aligned;
    sptm_dispatch_engine_init();
    sptm_dbg_print("Starting TXM");
    sptm_txm_entry((void *)0x100108);
    sptm_panic_assert("sptm_start_txm never returns");
}

/* ============================================================================
 * FUN_000bc3d0  sptm_boot_stage_sk_handoff
 * Ghidra: void FUN_000bc3d0(long param_1)
 * Per-CPU bootstrap-handoff completion: requires bootstrap-stage bit 0x11,
 * runs per-CPU init for the handoff magic CPU, sets up the scheduler state,
 * marks the CPU ready, and if the DT handoff flag (DAT_00094480 bit0) is set
 * performs the TXM handoff and early SK entry. Then configures the current
 * per-CPU state (0xa30=5, 0xa68=0, 0xa60=5) and enters dispatch domain 1.
 * Confidence: medium. */
void
sptm_boot_stage_sk_handoff(uint64_t param_1)
{
    uint64_t percpu;

    if (((uint32_t)g_feature_flags >> 0x11 & 1) == 0) {
        sptm_panic_assert("Expected bootstrap stages not met");
    }
    sptm_cpu_init((uint32_t)*(int16_t *)(UAT_HANDOFF_MAGIC + param_1 + 10));
    sptm_init_sched((uint8_t *)param_1);
    *(uint8_t *)(param_1 + 1) = 1;
    if ((g_dt_handoff_flag & 1) != 0) {
        sptm_txm_handoff();
        sptm_sk_entry_early();
    }

    percpu = sptm_per_cpu_state();
    *(uint8_t *)(percpu + PERCPU_OFF_A30) = 5;
    percpu = sptm_per_cpu_state();
    *(uint64_t *)(percpu + PERCPU_OFF_A68) = 0;
    percpu = sptm_per_cpu_state();
    *(uint8_t *)(percpu + PERCPU_OFF_A60) = 5;
    sptm_enter_domain(1, (uintptr_t *)0x94498, (uintptr_t *)0x1002c0, 0, 0);
    sptm_panic_assert("boot stage SK handoff never returns");
}

/* ============================================================================
 * FUN_000bf5d0  sptm_nvram (SK-HIB begin; name inherited from sptm_init.c)
 * Ghidra: void FUN_000bf5d0(void)
 * Begins the SK hibernation hashing phase. Sets g_hib_state (DAT_001040a8) to
 * 8 then re-absorbs the phase salt (0x12f70) into a fresh SHA context, sets
 * g_sha_phase=5 (via the combined 16-bit store), clears the SK-hib flags, and
 * drains the per-CPU callback FTE refcounts (decrementing each descriptor's
 * refcnt with underflow panic). Zeroes the per-CPU callback list and per-CPU
 * state (0xa30=4, 0xa68=1, 0xa60=0xc), then runs the SK HIB patchup if
 * enabled (feature bit 0xc). Confidence: medium. Notes: despite the
 *   sptm_nvram name (a legacy label in sptm_init.c), the body is the SK-HIB
 *   begin; FTE class table at DAT_00095d51 (stride 0x90), refcnt at desc+6. */
void
sptm_nvram(void)
{
    uint64_t percpu, i, pa, stride;
    const uint16_t *desc;
    int32_t refcnt;

    g_hib_state = 8;
    sptm_sha_reset(g_sha_obj, g_sha_ctx);
    sptm_sha_update(g_sha_obj, g_sha_ctx, 4, (const void *)0x12f70);
    *(uint16_t *)&g_hib_state = (5 << 8) | g_hib_state;  /* phase=5, state=8 */
    g_sk_hib_started = 0;
    g_sk_hib_percpu = 0xffff;

    if (g_hibseg_cpu != 0) {
        for (i = 0; i < g_hibseg_cpu; i++) {
            pa = ((uint64_t *)0x100cb8)[i];           /* DAT_00100cb8 */
            if (pa < g_dram_start || g_dram_end <= pa) {
                desc = sptm_frame_lookup(pa);
                if (desc == 0) {
                    desc = &g_fallback_desc;
                }
            } else {
                desc = (const uint16_t *)(g_page_desc +
                            (((pa - g_dram_start) >> 10) & ~0xfU));
            }
            if (g_ftype_class2[(uint64_t)(*(uint8_t *)((const uint8_t *)desc + 1)) * 0x90] != 3) {
                sptm_panic_assert("Type %d class of FTE %p %d");
            }
            refcnt = *(int32_t *)((const uint8_t *)desc + 6);
            *(int32_t *)((uint8_t *)desc + 6) = refcnt - 1;
            if (refcnt == 0) {
                sptm_panic_assert("refcnt_underflow (rc=%p old=%d)");
            }
        }
    }
    sptm_scratch_zero((void *)0x100cb8, 0x100);
    g_hibseg_cpu = 0;

    percpu = sptm_per_cpu_state();
    *(uint8_t *)(percpu + PERCPU_OFF_A30) = 4;
    percpu = sptm_per_cpu_state();
    *(uint64_t *)(percpu + PERCPU_OFF_A68) = 1;
    percpu = sptm_per_cpu_state();
    *(uint8_t *)(percpu + PERCPU_OFF_A60) = 0xc;

    /* zero per-CPU hib scratch banks at DAT_00094ab0. */
    {
        uint8_t *h = (uint8_t *)0x94ab0;
        if (*(int32_t *)(h + 0x10) == 0) {
            stride = 0;
        } else {
            stride = 0;
            for (i = 0; i < (uint32_t)*(int32_t *)(h + 0x10); i++) {
                *(uint8_t *)(h + i + 0x19) = 0;
                *(uint16_t *)(h + i * 2 + 0x140) = 0;
                sptm_scratch_zero(*(void **)(h + 0x120) + stride, 0x80);
                sptm_scratch_zero(*(void **)(h + 0x128) + stride, 0x80);
                stride += 0x80;
            }
            stride = (uint64_t)*(uint32_t *)(h + 0x10) << 0xb;
        }
        sptm_scratch_zero(*(void **)(h + 0x758), stride);
    }

    if (((uint32_t)g_feature_flags >> 0xc & 1) != 0 && sptm_sk_hib_patchup() != 0) {
        sptm_panic_assert("SK HIB patchup returned error");
    }
}

/* CPU-trace carve-out state pointer (DAT_00095d40 holds a global POINTER set
 * by sptm_cputrace_carveout_init from sptm_percpu_base's return). The target
 * mirrors sptm_cputrace_state_t from sptm_trace_hib.c: +0x10 available,
 * +0x11 active, +0x18 carveout_start, +0x20 carveout_size. */
extern uint8_t *sptm_cputrace_state;   /* DAT_00095d40 */

/* ============================================================================
 * FUN_000bdd34  sptm_cputrace_carveout_start
 * Ghidra: undefined8 FUN_000bdd34(void)
 * Returns the physical start of the CPU-trace carve-out range
 * (*(DAT_00095d40 + 0x18)), used by the trace-window programming path to
 * bound the accepted trace PA window. Confidence: medium.
 * Notes: trivial getter; the value is set by sptm_cputrace_carveout_init. */
uint64_t
sptm_cputrace_carveout_start(void)
{
    return *(uint64_t *)(SPTM_CPUTRACE_STATE + 0x18);
}

/* ============================================================================
 * FUN_000bddd0  sptm_cputrace_carveout_init
 * Ghidra: undefined8 FUN_000bddd0(void)
 * Initializes the CPU-trace carve-out: reads the /chosen/apt_carveout_size_mb
 * device-tree property (in MiB), and if nonzero allocates 0x24-class frames
 * for it, records carveout_start/carveout_size in the CPU-trace state
 * (DAT_00095d40) and marks the carve-out present (available=1) / absent
 * (active=1 when no carve-out). Confidence: medium.
 * Notes: property read via the SecureDT root (DAT_00094ab8); a missing
 *   SecureDT panics. size checked to fit in 26 bits (panic on overflow). */
uint64_t
sptm_cputrace_carveout_init(void)
{
    uint64_t *secure_dt;
    uint64_t carveout_bytes;
    uintptr_t node;
    uint32_t *prop_val;
    uint32_t prop_size;
    uint8_t *st;
    uint64_t base;

    sptm_subsys_register("CPUTRACE");
    st = (uint8_t *)sptm_percpu_base(0, 0);
    /* The carve-out state is stored in the per-CPU DART driver state's
     * dedicated region (DAT_00095d40). */
    secure_dt = (uint64_t *)0x94ab8;                 /* DAT_00094ab8 */
    if (secure_dt == 0) {
        sptm_panic_assert("Error getting SecureDT");
    }
    carveout_bytes = 0;
    node = 0;
    if (sptm_dt_find_node((uintptr_t)secure_dt, 0, "chosen", &node) == 1) {
        prop_val = 0;
        prop_size = 0;
        if (sptm_dt_get_prop(node, "apt-carveout-size-mb", (uintptr_t *)&prop_val,
                             &prop_size, (uintptr_t)secure_dt[0], secure_dt[1]) == 1 &&
            prop_val != 0 && prop_size == 4) {
            carveout_bytes = (uint64_t)*prop_val;
        }
    }

    st = (uint8_t *)0x95d40;                          /* DAT_00095d40 */
    *(uint64_t *)(st + 0x20) = 0;
    *(uint64_t *)(st + 0x18) = 0;
    *(uint8_t *)(st + 0x28) = 0;
    *(uint8_t *)(st + 0x2c) = 0;
    *(uint8_t *)(st + 0x2b) = 0;
    *(uint8_t *)(st + 0x2a) = 0;
    *(uint8_t *)(st + 0x29) = 0;
    *(uint64_t *)(st + 0x40) = 0;
    *(uint64_t *)(st + 0x38) = 0;
    *(uint32_t *)(st + 0x48) = 0;

    if (carveout_bytes != 0) {
        if ((carveout_bytes >> 0x1a) != 0) {
            sptm_panic_assert("carveout_nb_frames %llx > limit");
        }
        sptm_alloc_elements(0x24, 0);
        base = (uint64_t)sptm_txm_handoff();          /* resolve a VA for the carve-out */
        st = (uint8_t *)0x95d40;
        *(uint64_t *)(st + 0x18) = base;
        *(uint64_t *)(st + 0x20) = carveout_bytes << 0x14;   /* MiB -> bytes */
    }
    *(uint8_t *)(st + 0x10) = carveout_bytes != 0;    /* available */
    *(uint8_t *)(st + 0x11) = carveout_bytes == 0;    /* active */
    return 0;
}

/* ============================================================================
 * FUN_000bdf54  sptm_trace_region_add
 * Ghidra: void FUN_000bdf54(ulong address, ulong size)
 * Registers a CPU-trace (or hibernation) region into the fixed-size region
 * table at DAT_000949b0 (stride 2 words: {base>>14, size>>14}), count at
 * DAT_00094978. Refuses to run during an unexpected bootstrap stage, and
 * refuses more than 10 regions; each entry must be 16 KiB aligned. Confidence:
 * medium. Notes: stage bit 0x14 must be clear; the region is only added when
 *   stage bit 0x13 is set OR hibernation is disabled (DAT_00100e00 bit0). */
void
sptm_trace_region_add(uint64_t address, uint64_t size)
{
    uint32_t *entry;
    uint32_t count;

    if (((uint32_t)g_feature_flags >> 0x14 & 1) != 0) {
        sptm_panic_assert("Unexpected bootstrap stages r");
    }
    if ((((uint32_t)g_feature_flags >> 0x13 & 1) == 0) ||
        (sptm_hib_enabled & 1) != 0) {
        if (((size | address) & 0x3fff) != 0) {
            sptm_panic_assert("address %llx or size %zu not 16K aligned");
        }
        if (9 < *(uint64_t *)0x94978) {               /* DAT_00094978 */
            sptm_panic_assert("Reached the maximum number of regions");
        }
        entry = (uint32_t *)0x949b0 + (*(uint64_t *)0x94978) * 4; /* DAT_000949b0 */
        if (((uint64_t)entry & 0xffc0000000000000) != 0) {
            entry = (uint32_t *)((uint64_t)entry & 0xffffffffffff |
                                 0xc8a2000000000000);
        }
        *entry = (uint32_t)(address >> 0xe);
        entry[1] = (uint32_t)(size >> 0xe);
        *(uint64_t *)0x94978 = *(uint64_t *)0x94978 + 1;
    }
}

/* ============================================================================
 * FUN_000be044  sptm_dt_key_read
 * Ghidra: long FUN_000be044(undefined8 *root, undefined8 key, ulong exp_size,
 *                          code *on_error)
 * Reads a named byte-string property from the /chosen/hibernation node and
 * returns a pointer to its value, or 0 when the node/property is absent.
 * `exp_size` is the expected value size; a size mismatch is reported through
 * the caller-supplied error callback. Confidence: medium. Notes: node lookup
 *   via sptm_dt_find_node("/chosen/hibernation"); property via
 *   sptm_dt_get_prop with the root iter/ctx (root[0], root[1]). */
uintptr_t
sptm_dt_key_read(uint64_t *root, uint64_t key, uint64_t exp_size,
                 void (*on_error)(const char *, int, const char *, uint64_t, uint64_t))
{
    uintptr_t node;
    uintptr_t prop_val;
    uint32_t prop_size;
    int found;

    node = 0;
    found = sptm_dt_find_node((uintptr_t)root, 0, "chosen/hibernation", &node);
    if (found != 1) {
        on_error("AppleInternal-Library/BuildRoot", 0x1cb,
                 "chosen/hibernation node not found", 0, key);
    }
    prop_val = 0;
    prop_size = 0;
    found = sptm_dt_get_prop(node, (const char *)key, &prop_val, &prop_size,
                             root[0], root[1]);
    if (found == 1) {
        if (exp_size != (uint64_t)prop_size) {
            on_error("AppleInternal-Library/BuildRoot", 0x1d6,
                     "key has unexpected size", (uint64_t)prop_size, key);
        }
        if (prop_val != 0) {
            return prop_val;
        }
        on_error("AppleInternal-Library/BuildRoot", 0x1da,
                 "key property found but key is NULL", 0, key);
    }
    return 0;
}

/* ============================================================================
 * FUN_000be150  sptm_memmove
 * Ghidra: void FUN_000be150(ulong dst, ulong src, ulong n)
 * Overlap-aware byte copy (memmove). When `src` precedes `dst` the copy runs
 * backwards from the end; when `dst` precedes `src` it runs forward from the
 * start. Both directions use a 32-byte wide loop for large, sufficiently
 * separated transfers, then 8-byte and 1-byte tails. Confidence: high.
 * Notes: classic memmove; the source/dest are raw ulongs in the decompile. */
void
sptm_memmove(uint8_t *dst, const uint8_t *src, uint64_t n)
{
    uint64_t i, chunks;

    if ((uint64_t)src <= (uint64_t)dst || (uint64_t)dst + n <= (uint64_t)src) {
        /* src at or before dst: copy backward from the end. */
        if (n > 7 && (uint64_t)src - (uint64_t)dst > 0x3f) {
            if (n >= 0x40) {
                chunks = n & ~0x3fU;
                i = 0;
                while (i < chunks) {
                    /* copy a 0x40-byte block in two 32-byte halves, moving
                     * from the end towards the start. */
                    memcpy(dst + n - 0x40 - i, src + n - 0x40 - i, 0x40);
                    i += 0x40;
                }
                if (n == chunks) {
                    return;
                }
                if ((n & 0x38) == 0) {
                    n &= 0x3f;
                    goto tail_back;
                }
            }
            i = n - (n & ~0x3fU);
            while (i != 0) {
                dst[n - 8 - (i - 8)] = src[n - 8 - (i - 8)];
                i -= 8;
            }
            if (n == (n & ~7U)) {
                return;
            }
            n &= 7;
        }
tail_back:
        while (n != 0) {
            dst[n - 1] = src[n - 1];
            n -= 1;
        }
        return;
    }

    /* dst before src: copy forward from the start. */
    if (n > 7 && (uint64_t)dst - (uint64_t)src > 0x3f) {
        if (n >= 0x40) {
            chunks = n & ~0x3fU;
            i = 0;
            while (i < chunks) {
                memcpy(dst + i, src + i, 0x40);
                i += 0x40;
            }
            if (n == chunks) {
                return;
            }
            if ((n & 0x38) == 0) {
                n &= 0x3f;
                goto tail_fwd;
            }
        }
        i = n & ~7U;
        while (i != 0) {
            memcpy(dst + (i - 8), src + (i - 8), 8);
            i -= 8;
        }
        if (n == (n & ~7U)) {
            return;
        }
        n &= 7;
    }
tail_fwd:
    while (n != 0) {
        *dst = *src;
        dst += 1;
        src += 1;
        n -= 1;
    }
}

/* ============================================================================
 * FUN_000becd0  sptm_dt_key_copy
 * Ghidra: void FUN_000becd0(undefined8 root, undefined1 *out, undefined8 key,
 *                           ulong exp_size)
 * Reads a named key from /chosen/hibernation via sptm_dt_key_read and copies
 * exactly `exp_size` bytes into `out`. Rejects an all-zero key value. A
 * missing/oversized/all-zero key is escalated through the DT error callback
 * (sptm_panic_hib). Confidence: medium. Notes: the copy is overlap-aware
 * (memmove-style); a trailing region of the output is zeroed via
 *   sptm_bzero_block. */
void
sptm_dt_key_copy(uint64_t *root, uint8_t *out, uint64_t key, uint64_t exp_size)
{
    const uint8_t *val;
    uint64_t i;

    val = (const uint8_t *)sptm_dt_key_read(root, key, exp_size, sptm_panic_hib);
    if (val == 0) {
        sptm_panic_hib("AppleInternal-Library/BuildRoot", 0x217,
                       "key not found in DT", 0, key);
    }

    i = 0;
    while (i < exp_size) {
        if (val[i] != '\0') {
            break;
        }
        i += 1;
    }
    if (i == exp_size) {
        sptm_panic_hib("AppleInternal-Library/BuildRoot", 0x229,
                       "key is all zero", 0, key);
    }

    /* overlap-aware copy of the key value into `out`. */
    sptm_memmove(out, val, exp_size);
    sptm_bzero_block(exp_size, out);   /* FUN_000b2584: trailing zeroing */
}

/* ============================================================================
 * FUN_000bf298  sptm_sha_hash_range
 * Ghidra: void FUN_000bf298(undefined4 tag, ulong start, ulong end,
 *                           undefined8 out, undefined8 ace_ctx)
 * Hashes the contiguous physical range [start, end) in 16 KiB steps into the
 * global SHA-2 object (g_sha_obj / g_sha_ctx), first absorbing a 4-byte
 * `tag`. Each 16 KiB page is resolved to its descriptor; a page whose FTE
 * class is the zero-page class is hashed from a zeroed scratch buffer, while
 * a normal page is hashed from its translated VA (linear offset or
 * relocation-table lookup). Finalizes the digest and produces the protected
 * output via sptm_crypto_finalize(ace_ctx, digest, out). Confidence: medium.
 * Notes: out-of-DRAM pages use sptm_frame_lookup; the FTE class table is
 *   indexed by descriptor byte at g_ftype_class (DAT_00095d56, stride 0x90). */
void
sptm_sha_hash_range(uint32_t tag, uint64_t start, uint64_t end,
                    void *out, void *ace_ctx)
{
    const uint16_t *desc;
    uint8_t *page_va;
    uint64_t pa;
    uint8_t digest[0x20];
    uint8_t scratch[0x4000];
    uint32_t tag32 = tag;

    sptm_sha_reset(g_sha_obj, g_sha_ctx);
    sptm_sha_update(g_sha_obj, g_sha_ctx, 4, &tag32);

    for (pa = start; pa < end; pa += 0x4000) {
        if (pa < g_dram_start || g_dram_end <= pa) {
            /* out-of-DRAM page: resolve through the frame descriptor. */
            desc = (const uint16_t *)sptm_frame_lookup(pa);
            if (desc != 0) {
                page_va = (uint8_t *)desc;
            } else {
                page_va = (uint8_t *)&g_fallback_desc;
            }
        } else {
            page_va = (uint8_t *)(g_page_desc +
                                  (((pa - g_dram_start) >> 10) & ~0xfU));
        }
        /* FTE class (stride 0x90 table) == 0xff -> zero page. */
        if (g_ftype_class[(uint64_t)(*(uint8_t *)(page_va + 1)) * 0x90] == 0xff) {
            sptm_zero_page_begin();                     /* FUN_000e03f4 */
            page_va = (uint8_t *)sptm_zero_page_addr(); /* FUN_000e0770 */
            sptm_sha_update(g_sha_obj, g_sha_ctx, 0x4000, page_va);
            sptm_zero_page_release();                   /* FUN_000e05bc */
        } else {
            if (((uint32_t)g_feature_flags >> 8 & 1) == 0) {
                page_va = (uint8_t *)((pa - g_dram_start) + g_linear_offset);
            } else {
                page_va = (uint8_t *)sptm_va_lookup(pa);  /* FUN_000e40ec */
            }
            sptm_sha_update(g_sha_obj, g_sha_ctx, 0x4000, page_va);
        }
    }

    /* finalize the SHA digest, then protect it via the crypto engine. */
    memset(digest, 0, sizeof(digest));
    g_sha_obj->finalize(g_sha_obj, g_sha_ctx, digest);
    sptm_crypto_finalize(ace_ctx, digest, out);
}

/* ============================================================================
 * FUN_000bf4bc  sptm_crypto_finalize
 * Ghidra: void FUN_000bf4bc(undefined8 ace_ctx, undefined8 digest,
 *                           undefined8 out)
 * Produces the final protected digest: obtains the crypto-engine context,
 * absorbs the 0x20-byte SHA digest plus a 0x20-byte input block, then
 * finalizes the GCM output into `out`. Confidence: low-medium. Notes: uses
 *   sptm_gcm_update_barr (FUN_000b07bc) + sptm_sha_update + sptm_gcm_finalize_barr
 *   (FUN_000b0504); intermediate scratch is zeroed via sptm_bzero_block. */
void
sptm_crypto_finalize(void *ace_ctx, const uint8_t *digest, uint8_t *out)
{
    uint64_t *gctx = (uint64_t *)sptm_crypto_ctx();   /* FUN_000b25b0 */
    uint8_t scratch[0x100];

    sptm_scratch_zero(scratch, sizeof(scratch));
    /* gcm update with the 0x30-byte header (digest length fields), then the
     * 0x20-byte digest block, then GCM finalize producing `out`. */
    sptm_gcm_update_barr(gctx, (uint64_t *)scratch, 0x30, ace_ctx);
    sptm_sha_update((sptm_sha_obj_t *)gctx, scratch, 0x20, digest);
    sptm_gcm_finalize_barr(gctx, (uint64_t *)out, 0);
    sptm_bzero_block(0x20, scratch);
}

/* ============================================================================
 * FUN_000bf874  sptm_ace_finalize
 * Ghidra: void FUN_000bf874(long ace_ctx, undefined4 *digest_in,
 *                           undefined4 *out)
 * Finalizes the crypto-engine (ACE) operation that produces the hibernation
 * image digest. Programs the ACE context (DAT_00104120's crypto engine):
 * validates that the seed/keys are installed (else panics), writes the
 * 0x20-byte input digest to the context input window (+0x200), waits for the
 * busy bit, and copies the 0x30-byte result from +0x100 to `out`. Confidence:
 * high. Notes: `digest_in` is 8 words, `out` is 12 words. This is the
 *   "Crypto-engine (ACE) finalize producing the image digest" referenced by
 *   sptm_trace_hib.c. */
void
sptm_ace_finalize(uint64_t ace_ctx, const void *digest_in, void *out)
{
    const uint32_t *din = (const uint32_t *)digest_in;
    uint32_t *dout = (uint32_t *)out;
    uint32_t *ctx = (uint32_t *)ace_ctx;

    ctx[0x14 / 4] = 0xffffffff;                       /* +0x14 status */
    if (((ctx[0x34 / 4] ^ 0xffffffff) & 0x1800) != 0) {
        sptm_panic_assert("SPTM HIB: Seed and Keys for key schedule not set");
    }
    ctx[8 / 4] = 0x45;                                /* +0x08 control */
    ctx[0x1c / 4] = 0x20;                             /* +0x1c length */
    ctx[8 / 4] |= 2;
    while ((ctx[0xc / 4] & 1) != 0) { /* wait until not busy */ }

    ctx[0x200 / 4] = din[0];
    ctx[0x204 / 4] = din[1];
    ctx[0x208 / 4] = din[2];
    ctx[0x20c / 4] = din[3];
    ctx[0x210 / 4] = din[4];
    ctx[0x214 / 4] = din[5];
    ctx[0x218 / 4] = din[6];
    ctx[0x21c / 4] = din[7];
    ctx[0xc / 4] |= 1;                                /* +0x0c kick */
    while (((ctx[8 / 4] >> 1) & 1) != 0) { /* wait for done */ }

    if ((ctx[0x14 / 4] & 0xfffffffe) == 2) {
        dout[0]  = ctx[0x100 / 4];
        dout[1]  = ctx[0x104 / 4];
        dout[2]  = ctx[0x108 / 4];
        dout[3]  = ctx[0x10c / 4];
        dout[4]  = ctx[0x110 / 4];
        dout[5]  = ctx[0x114 / 4];
        dout[6]  = ctx[0x118 / 4];
        dout[7]  = ctx[0x11c / 4];
        dout[8]  = ctx[0x120 / 4];
        dout[9]  = ctx[0x124 / 4];
        dout[10] = ctx[0x128 / 4];
        dout[11] = ctx[0x12c / 4];
        return;
    }
    sptm_panic_assert("SPTM HIB: Error occurred while finalizing image");
}
