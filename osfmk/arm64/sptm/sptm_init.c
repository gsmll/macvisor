/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file reconstructs SPTM's bootstrap / CPU / dispatch-table registration
 * code. The functions here are the cold-boot and per-CPU bring-up path plus
 * the guarded-level dispatch-table plumbing that lets XNU / TXM / SK register
 * the endpoints they may invoke. GENTER/GEXIT transitions themselves live in
 * the guarded-entry stub (FUN_000ab8d8 sptm_genter_receive, separate tree);
 * sptm_dispatch() below is the endpoint-dispatch logic reached after entry.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ */
/* Extern kernel / SPTM helper deps (addresses in comments; other trees) */
/* ------------------------------------------------------------------ */

/* noreturn diagnostics. FUN_000f8804 is the printf-style SPTM panic printer;
 * FUN_000f8844 prints with an explicit error code; FUN_000f8834 is a
 * no-argument "bad device-tree" panic; FUN_000d6124 prints with a code word. */
extern __attribute__((noreturn)) void sptm_panic(const char *fmt, ...);       /* FUN_000f8804 */
extern __attribute__((noreturn)) void sptm_panic_code(unsigned int code,
    uintptr_t arg, const char *fmt, ...);                                     /* FUN_000f8844 */
extern __attribute__((noreturn)) void sptm_panic_bad_dt(void);                /* FUN_000f8834 */
extern __attribute__((noreturn)) void sptm_panic_fmt(uint32_t code,
    uintptr_t arg, const char *fmt, ...);                                     /* FUN_000d6124 */

/* Sysreg / TLB / barrier intrinsics (arm64). */
extern uint64_t sptm_sysreg_read(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2);
extern void sptm_sysreg_write(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2, uint64_t val);
extern void sptm_sysop_write(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2, uint64_t val);      /* SysOp_W */
extern void sptm_tlbi_aside1is(uint64_t vttbr);                               /* TLBI_ASIDE1IS */
extern void sptm_tlbi_vmalle1is(void);                                        /* TLBI_VMALLE1IS */
extern void sptm_tlbi_vae1is(uint64_t va);                                    /* TLBI_VAE1IS */
extern void sptm_tlbi_vale1is(uint64_t va);                                   /* TLBI_VALE1IS */
extern void sptm_tlbi_vaae1is(uint64_t va);                                   /* TLBI_VAAE1IS */
extern void sptm_tlbi_vaale1is(uint64_t va);                                  /* TLBI_VAALE1IS */
extern void sptm_tlbi_ipas2e1is(uint64_t val);                                /* TLBI_IPAS2E1IS */
extern void sptm_tlbi_ipas2le1is(uint64_t val);                               /* TLBI_IPAS2LE1IS */
extern void sptm_tlbi_vmalls12e1is(void);                                     /* TLBI_VMALLS12E1IS */
extern void sptm_dsb(unsigned int level, unsigned int a, unsigned int b);     /* DSB */
extern void sptm_isb(void);                                                   /* ISB */
extern void sptm_membar_release(void);                                        /* LORelease() release barrier */

/* Device-tree helpers (FUN_000b79e8 / FUN_000b7dc8 / FUN_000b7c04). */
extern int sptm_dt_find_node(uintptr_t iter, uintptr_t parent,
    const char *name, uintptr_t *out);                                        /* FUN_000b79e8 */
extern int sptm_dt_iterate(uintptr_t iter, uintptr_t *current,
    uintptr_t *next);                                                         /* FUN_000b7dc8 */
extern int sptm_dt_get_prop(uintptr_t node, const char *name,
    uintptr_t *out_val, uint32_t *out_size, uintptr_t iter, uintptr_t ctx);   /* FUN_000b7c04 */
extern int sptm_dt_cmp_prop(uintptr_t node, const char *name);                /* thunk_FUN_000ac190 */
extern int sptm_dt_prop_u32(uintptr_t node, const char *name, uint32_t v);    /* thunk_FUN_000ac290 */
extern intptr_t sptm_dt_prop_size(uintptr_t node);                            /* thunk_FUN_000ac480 */

/* Boot-image region lookup: FUN_000b807c returns a {base,size} pair. */
extern long *sptm_boot_region(const char *name, int required);                /* FUN_000b807c */

/* Region mapping: FUN_000d9aa8 maps a named boot region into the PAPT.
 * Args: (name, fte_type, base_pa, num_16k_pages, pte/prot word). */
extern void sptm_map_boot_region(const char *name, uint32_t fte_type,
    uintptr_t base, uintptr_t num_pages, uint64_t prot);                      /* FUN_000d9aa8 */
extern uintptr_t sptm_pa_to_va(uintptr_t pa, uintptr_t num_pages,
    uint32_t flags);                                                          /* FUN_000d9940 */

/* PAPT range maintenance (used by sptm_slide_region). */
extern void sptm_papt_op_a(uintptr_t va, uintptr_t papt_off,
    uintptr_t pages, uint32_t a, uint32_t b, uint32_t c);                     /* FUN_000d941c */
extern void sptm_papt_op_b(uintptr_t va, uintptr_t pages);                    /* FUN_000d977c */
extern void sptm_papt_commit(void);                                           /* FUN_000d9d44 */

/* Per-CPU frame mapping helpers. FUN_000e3a14 queries a frame's type/mapped
 * state; FUN_000e3d7c maps a frame for PAPT access; FUN_000e40ec resolves a
 * PA->VA. */
extern uint64_t sptm_frame_query(uint64_t va);                                /* FUN_000e3a14 */
extern uint16_t *sptm_frame_lookup(uint64_t va);                              /* FUN_000e3d7c */
extern uintptr_t sptm_va_lookup(uintptr_t pa);                                /* FUN_000e40ec */

/* Misc bootstrap helpers (other trees). */
extern void sptm_boot_fixups(void);                                           /* FUN_000b8154 */
extern void sptm_install_boot_vectors(uintptr_t base);                        /* thunk_FUN_000abb60 */
extern void sptm_save_late_const(uintptr_t pc);                               /* thunk_FUN_000abeb0 */
extern void sptm_copy_mem(uint8_t *dst, const uint8_t *src,
    uintptr_t len, uint32_t mode);                                            /* FUN_000ae158 */
extern void sptm_fill_mem(uint8_t *dst, uint8_t v, uint8_t v2);               /* FUN_000ae3e0 */
extern uintptr_t sptm_get_random(uintptr_t *out, uintptr_t len,
    uintptr_t *out2);                                                         /* FUN_000ba950 */
extern void sptm_start_txm(uintptr_t *state);                                 /* FUN_000bb61c / FUN_000a10e0 */
extern void sptm_start_sk(uintptr_t *state);                                  /* FUN_000bb51c / FUN_000a11e0 */
extern void sptm_enter_domain(uintptr_t selector, uintptr_t *ctx,
    uintptr_t *out, uintptr_t *arg4, uintptr_t arg5);                         /* FUN_000a121c */
extern void sptm_init_el2_pmaps(void);                                        /* FUN_000ab7bc */
extern void sptm_init_el2_state(uint8_t *state);                              /* FUN_000ab8ac */
extern void sptm_init_sched(uint8_t *state);                                  /* FUN_000baa60 */
extern void sptm_dbg_init(void);                                              /* FUN_000c172c */
extern void sptm_dbg_print(const char *fmt, ...);                             /* FUN_000c15b4 */
extern void sptm_finalize_el2_mmu(uintptr_t a, uintptr_t b,
    uintptr_t c, uintptr_t d, uintptr_t e);                                   /* FUN_000dcf80 */
extern void sptm_finalize_hib(void);                                          /* FUN_000c1ab0 */
extern void sptm_hib_teardown_a(uint64_t val);                                /* FUN_000c1b70 */
extern void sptm_hib_teardown_b(void);                                        /* FUN_000c1cc4 */
extern void sptm_memmap_available(const char *name, uint32_t a, uint32_t b); /* FUN_000d9be8 */
extern void sptm_nvram(void);                                                 /* FUN_000bf5d0 */
extern uintptr_t sptm_sk_entropy(const char *name, uintptr_t len,
    uintptr_t *out);                                                          /* FUN_000ba950 alt */
extern void sptm_dispatch_engine_init(void);                                  /* FUN_000b8230 */
extern uintptr_t sptm_boot_mem_begin(void);                                   /* FUN_000d9ec8 */
extern void sptm_txm_page_lookup(uintptr_t a);                                /* FUN_000d81bc */
extern uintptr_t sptm_dt_segment_lookup(uintptr_t pa);                        /* FUN_000e233c */
extern void sptm_call_endpoint(uintptr_t fn, bool is_sysreg);                 /* FUN_000a03d4 */
extern void sptm_table_release(uint16_t *parent, uint16_t *child,
    int mode);                                                                /* FUN_000e2c18 */
extern void sptm_frame_table_update(uintptr_t *arg1, uintptr_t *arg2,
    uintptr_t len, uintptr_t *cb);                                            /* FUN_000ad2dc */
extern void sptm_frame_table_update_cb(void);                                 /* FUN_000d64d0 */
extern void sptm_txm_handoff(uint8_t *out, uintptr_t *in);                    /* FUN_000d8a58 */
extern __attribute__((noreturn)) void sptm_brk_jump(uintptr_t target);        /* SoftwareBreakpoint */

/* tpidr_el2 — per-CPU runtime state base (arm64 system register). */
extern uintptr_t tpidr_el2;

/* __chain_starts — SPTM's own chained-fixups format field (absolute symbol in
 * the image; offset used relative to the image base in sptm_fixup). */
extern const uint32_t __chain_starts_sym;

/* Forward declaration for the endpoint dispatcher. */
void sptm_dispatch(uintptr_t dispatch_id, uintptr_t arg2);

/* ------------------------------------------------------------------ */
/* SPTM bootstrap state globals (DAT_* = bss; see per-field comments)  */
/* ------------------------------------------------------------------ */

/* DAT_001012d8 — SPTM bootstrap-stage bitmask. Each stage transition sets a
 * bit; re-announcing an already-reached stage panics. */
uint64_t sptm_boot_stages;

/* DAT_00100720 — number of CPUs registered via sptm_register_cpu(). */
uint32_t sptm_num_cpus;

/* DAT_00094ab8 — device-tree iteration state: [0]=iterator, [1]=context. */
uintptr_t sptm_dt_state[2];

/* DAT_001075b0 region — per-CPU registration state, stride 0x1640 bytes.
 * Field offsets reference the DAT_* names found in the decompile. */
#define SPTM_PER_CPU_STRIDE 0x1640
#define SPTM_MAX_CPUS      0x0a
uint8_t sptm_cpu_state[SPTM_MAX_CPUS * SPTM_PER_CPU_STRIDE];
/* DAT_00106180 — per-CPU "registered/running" flag byte, stride 0x1640. */
uint8_t sptm_cpu_flag[SPTM_MAX_CPUS * SPTM_PER_CPU_STRIDE];

/* DAT_001012f8 — PAPT range table (name, flags, papt_base, va_base, size,
 * prot). DAT_001012f0 = number of live ranges. */
#define SPTM_MAX_PAPT_RANGES 0x32
typedef struct {
    const char *name;     /* +0x00 */
    uint8_t     flags;    /* +0x08 */
    uint8_t     _pad[7];
    uint64_t    papt_base;/* +0x10 */
    uint64_t    va_base;  /* +0x18 */
    uint32_t    size_pages; /* +0x20 (in 16K pages) */
    uint32_t    prot;     /* +0x24 */
} sptm_papt_range_t;
uint32_t sptm_papt_range_count;                       /* DAT_001012f0 */
sptm_papt_range_t sptm_papt_ranges[SPTM_MAX_PAPT_RANGES]; /* DAT_001012f8 */

/* Dispatch-table registration (DAT_00095bf8 / DAT_00095c00, stride 0x10). */
uint64_t sptm_dispatch_table_base[16];    /* DAT_00095bf8 */
uint64_t sptm_dispatch_driver_id[16];     /* DAT_00095c00 (per-table byte) */

/* DAT_00095444 — number of registered IO ranges (from parse_io_space). */
uint32_t sptm_io_range_count;
/* DAT_00100db8 — SPTM debug/tracing enable flag. */
uint64_t sptm_dbg_flag;

/* Per-CPU runtime state access: the tpidr_el2 / per-CPU sysreg base. */
static inline uint8_t *sptm_current_cpu_state(void)
{
    uintptr_t base = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (base == 0) {
        return (uint8_t *)tpidr_el2;
    }
    return (uint8_t *)sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
}

/* ------------------------------------------------------------------ */
/* sptm_fixup                                                          */
/* ------------------------------------------------------------------ */
/* FUN_000b7eec @ 0x000b7eec   (sptm_fixup)
 * Ghidra: void FUN_000b7eec(long param_1, long param_2, long param_3)
 * Processes the DYLD-style chained-fixup rebase records embedded in a boot
 * image, applying a slide to every pointer. param_1 is the fixups region
 * base, param_2 the slide value, param_3 the end bound for the chain walk.
 * It handles 64-bit little-endian pointers in both non-auth (kind 6) and
 * auth (kind 7) chain formats and panics on any unsupported record. Called
 * during cold boot as sptm_fixup(0, 0, 0) to rebase SPTM's own image with a
 * slide of 0.
 * Confidence: high
 * Notes: chain metadata lives at DAT_000136b4 (count) / DAT_000136b8
 *   (offsets) / __chain_starts (format field) relative to the image base. */
void sptm_fixup(uintptr_t fixups_base, uintptr_t slide, uintptr_t limit)
{
    /* DAT_000136b4: number of fixup "sets" in the image's fixups header. */
    uint32_t num_sets = *(uint32_t *)(fixups_base + 0x136b4);
    uint32_t set;

    for (set = 0; set != num_sets; set++) {
        /* DAT_000136b8: byte offset of this set's first chain entry. */
        uintptr_t off = *(uint32_t *)(fixups_base + 0x136b8 + set * 4);
        uintptr_t p;

        if (fixups_base + off >= limit) {
            continue;
        }
        /* __chain_starts: the chained-fixup format kind for this set. */
        uint32_t chain_kind = *(uint32_t *)(fixups_base + (uintptr_t)&__chain_starts_sym);
        if ((chain_kind & 0xfffffffeu) != 6) {
            sptm_panic("s: fixup ptr format is unsupported %d");
        }
        p = fixups_base + off;
        while (p != 0 && p < limit) {
            uint64_t *slot = (uint64_t *)p;
            uint64_t v = *slot;
            uint64_t next = 0;
            uint64_t next_off = 0;

            if (chain_kind == 6) {
                /* Non-auth 64-bit LE chained pointer. */
                if ((int64_t)v < 0) {
                    sptm_panic("s: unsupported entry (bind?) %d");
                }
                /* target = (value & 36 bits) + slide + sign-extended high8. */
                *slot = (v & 0xfffffffffULL) + slide + ((v >> 0x24) << 0x38);
                next = v >> 0x33;
                next_off = (v >> 0x31) & 0x3ffc;   /* next << 2 */
            } else {
                /* Auth 64-bit chained pointer. */
                if ((v >> 0x3e & 1) != 0) {
                    sptm_panic("s: unsupported entry (bind?) %d");
                }
                if ((int64_t)v < 0) {
                    if (((uint32_t)(v >> 0x31) & 3) != 0) {
                        sptm_panic("s: unsupported auth rebase key %d");
                    }
                    *slot = slide + (v & 0xffffffff);
                } else {
                    *slot = (v & 0x7ffffffffffULL) + slide + ((v >> 0x2b) << 0x38);
                }
                next = (v >> 0x33) & 0x7ff;
                next_off = next << 2;
            }
            if (next == 0) {
                break;
            }
            p = (uintptr_t)((uint8_t *)p + next_off);
        }
    }
}

/* ------------------------------------------------------------------ */
/* sptm_register_cpu                                                   */
/* ------------------------------------------------------------------ */
/* FUN_000b86bc @ 0x000b86bc   (sptm_register_cpu)
 * Ghidra: void FUN_000b86bc(ulong param_1, undefined8 param_2)
 * Registers one CPU (identified by its hardware reg value, param_1) into the
 * SPTM per-CPU table. It scans the device tree /cpus nodes for the node whose
 * "reg" property matches param_1, then records the CPU index and hwid, and
 * reads the cpu/acc/cpm "impl reg" physical addresses from the DT, mapping
 * each through sptm_pa_to_va() (16K-aligned). Duplicate registration is a
 * no-op; a missing DT node or illegal property size panics.
 * Confidence: high
 * Notes: per-CPU entry stride 0x1640; fields at +0x00 hwid, +0x08 index,
 *   +0x10/+0x18/+0x20 impl reg PAs, +0x28/+0x30/+0x38 their mapped VAs. */
void sptm_register_cpu(uintptr_t hwid, uintptr_t arg2)
{
    uintptr_t num = sptm_num_cpus;
    uintptr_t idx;
    uint32_t prop_size;
    uintptr_t prop_val;
    uintptr_t node;

    if ((sptm_boot_stages >> 0x11 & 1) != 0) {
        sptm_panic("s: Unexpected bootstrap stages ...");
    }
    if (sptm_num_cpus > 9) {
        sptm_panic_code(0x16, arg2, "s: s %d: %s %llx %s %llx");
    }
    /* Already registered? */
    for (idx = 0; idx != sptm_num_cpus; idx++) {
        if (*(uint64_t *)(sptm_cpu_state + idx * SPTM_PER_CPU_STRIDE) == hwid) {
            return;
        }
    }

    /* Locate the /cpus node in the device tree. */
    prop_val = 0;
    prop_size = 0;
    if (sptm_dt_find_node((uintptr_t)sptm_dt_state, 0, "cpus", &prop_val) != 1) {
        sptm_panic("s: Error looking up 'cpus'");
    }
    if (sptm_dt_state[0] == 0) {
        sptm_panic("s: Error initializing DT iterator");
    }

    /* Walk /cpus children until the node whose "reg" == hwid. */
    node = prop_val;
    if (node == 0) {
        node = sptm_dt_state[0];
    }
    for (;;) {
        uintptr_t next = 0;
        uintptr_t cur = node;

        if (sptm_dt_iterate((uintptr_t)sptm_dt_state, &cur, &next) == 0) {
            sptm_panic("s: CPU not found in the device tree");
        }
        prop_val = 0;
        if (sptm_dt_get_prop(next, "reg", &prop_val, &prop_size,
                sptm_dt_state[0], sptm_dt_state[1]) != 1) {
            sptm_panic("s: Error obtaining CPU node");
        }
        node = next;
        if (hwid == *(uintptr_t *)prop_val) {
            break;
        }
    }

    num = sptm_num_cpus;
    idx = num * SPTM_PER_CPU_STRIDE;
    *(uint8_t *)(sptm_cpu_state + num * 0xb20 + 8) = (uint8_t)sptm_num_cpus; /* DAT_001075b8 index */
    sptm_num_cpus = sptm_num_cpus + 1;
    *(uint64_t *)(sptm_cpu_state + num * SPTM_PER_CPU_STRIDE) = hwid;

    /* Read the three "impl reg" properties; each is a {pa, size} pair. */
    {
        uint64_t cpu_pa, acc_pa, cpm_pa;
        uintptr_t sz_pa, sz2_pa, sz3_pa;
        uint32_t sz;

        prop_val = 0;
        prop_size = 0;
        if (sptm_dt_get_prop(node, "cpu_impl_reg", &prop_val, &prop_size,
                sptm_dt_state[0], sptm_dt_state[1]) != 1 ||
            prop_size != 0x10) {
            sptm_panic("s: Error looking up image region ...");
        }
        cpu_pa = *(uint64_t *)prop_val;
        sz_pa  = *(uintptr_t *)(prop_val + 8);

        prop_val = 0;
        prop_size = 0;
        if (sptm_dt_get_prop(node, "acc_impl_reg", &prop_val, &prop_size,
                sptm_dt_state[0], sptm_dt_state[1]) != 1 ||
            prop_size != 0x10) {
            sptm_panic("s: Error looking up image region ...");
        }
        acc_pa = *(uint64_t *)prop_val;
        sz2_pa = *(uintptr_t *)(prop_val + 8);

        prop_val = 0;
        prop_size = 0;
        if (sptm_dt_get_prop(node, "cpm_impl_reg", &prop_val, &prop_size,
                sptm_dt_state[0], sptm_dt_state[1]) != 1 ||
            prop_size != 0x10) {
            sptm_panic("s: Error looking up image region ...");
        }
        cpm_pa = *(uint64_t *)prop_val;
        sz3_pa = *(uintptr_t *)(prop_val + 8);

        *(uint64_t *)(sptm_cpu_state + idx + 0x10) = cpu_pa;   /* DAT_001075c0 */
        *(uint64_t *)(sptm_cpu_state + idx + 0x18) = acc_pa;   /* DAT_001075c8 */
        *(uint64_t *)(sptm_cpu_state + idx + 0x20) = cpm_pa;   /* DAT_001075d0 */
        *(uint64_t *)(sptm_cpu_state + idx + 0x28) =
            sptm_pa_to_va(cpu_pa, (sz_pa  + 0x3fffu) >> 14, 0);  /* DAT_001075d8 */
        *(uint64_t *)(sptm_cpu_state + idx + 0x30) =
            sptm_pa_to_va(acc_pa, (sz2_pa + 0x3fffu) >> 14, 0);  /* DAT_001075e0 */
        *(uint64_t *)(sptm_cpu_state + idx + 0x38) =
            sptm_pa_to_va(cpm_pa, (sz3_pa + 0x3fffu) >> 14, 0);  /* DAT_001075e8 */
        *(uint32_t *)(sptm_cpu_flag + idx) = 1;                  /* DAT_00106180 */
        (void)sz;
    }
}

/* ------------------------------------------------------------------ */
/* sptm_slide_region                                                   */
/* ------------------------------------------------------------------ */
/* FUN_000b8a3c @ 0x000b8a3c   (sptm_slide_region)
 * Ghidra: void FUN_000b8a3c(ulong param_1, ulong param_2)
 * Slides a region of the SPTM's physical map by inserting a new PAPT range of
 * `param_2` 16K pages starting at physical `param_1`, splitting the existing
 * PAPT range that covers it into one/two leftover ranges. Requires the region
 * to be 16K-aligned, within the PAPT window, and at most 0x40000 pages; the
 * affected range must be flagged for sliding. On success it advances the PAPT
 * end cursor and commits via sptm_papt_commit().
 * Confidence: high
 * Notes: PAPT range table DAT_001012f8 (see sptm_papt_range_t); count
 *   DAT_001012f0; end cursor DAT_00101f80. */
void sptm_slide_region(uintptr_t pa, uintptr_t size_pages)
{
    uintptr_t size_bytes;
    uintptr_t end;
    uintptr_t i;

    if ((sptm_boot_stages >> 0x11 & 1) != 0) {
        sptm_panic("s: Unexpected bootstrap stages ...");
    }
    if (size_pages == 0 || pa < 0x95118 || pa >= 0x101f80) {
        sptm_panic_code(0x14, size_pages, "s: s %d: %s %llx %s %llx");
        return;
    }
    size_bytes = (size_pages & 0xffffffff) * 0x4000;
    end = pa + size_bytes;
    if (pa > end || end - 1 < 0x95118 || end - 1 >= 0x101f80) {
        sptm_panic_code(0x14, size_pages, "s: s %d: %s %llx %s %llx");
        return;
    }
    if (size_pages - 0x40000u < 0xfffc0001u) {
        /* size >= 0x40000 pages would overflow the window. */
        sptm_panic_code(10, size_pages, "s: s %d: %s %llx %s %llx");
    }
    if ((pa & 0x3fff) != 0 || end - pa >= 0x95458 - 0x101f80 ||
        sptm_papt_range_count == 0) {
        sptm_panic_code(0x34, size_pages, "s: s %d: %s %llx %s %llx");
        return;
    }

    /* Find the last PAPT range covering [pa, end). */
    {
        sptm_papt_range_t *hit = NULL;
        sptm_papt_range_t *r;

        for (i = 0; i != sptm_papt_range_count; i++) {
            r = &sptm_papt_ranges[i];
            if (r->va_base <= pa && end <= r->va_base + r->size_pages * 0x4000) {
                hit = r;
            }
        }
        if (hit == NULL || (hit->prot >> 4 & 1) == 0) {
            sptm_panic_code(0x34, size_pages, "s: s %d: %s %llx %s %llx");
            return;
        }

        sptm_papt_op_b(pa, size_pages);                       /* FUN_000d977c */
        sptm_papt_op_a(0x101f80, hit->papt_base + pa - hit->va_base,
            size_pages, 0xfe, 0, 0);                          /* FUN_000d941c */

        if (sptm_papt_range_count > 0x31) {
            sptm_panic("s: Number of supported PAPT ranges exhausted");
        }
        /* Copy the matched range into a fresh slot and reshape it. */
        {
            uintptr_t new_slot = sptm_papt_range_count;
            uintptr_t old_va = hit->va_base;
            uint64_t old_papt = hit->papt_base;
            uint8_t  old_flags = hit->flags;
            uint32_t old_prot = hit->prot;
            uint32_t old_size = hit->size_pages;
            int leftover_head = (int)((old_va - end) >> 14);
            int new_size;

            sptm_papt_range_count = (uint32_t)(new_slot + 1);
            sptm_papt_ranges[new_slot] = (sptm_papt_range_t){
                .name = hit->name,
                .flags = old_flags,
                .papt_base = hit->papt_base + (pa - old_va),
                .va_base = 0x101f80,
                .size_pages = (uint32_t)size_pages,
                .prot = old_prot,
            };

            new_size = old_size;
            if (pa != old_va && end != old_va + (uintptr_t)old_size * 0x4000) {
                new_size = -leftover_head;
            }
            hit->size_pages = (uint32_t)(new_size - (int)size_pages);
            if (hit->size_pages == 0) {
                hit->papt_base = 0;
                hit->va_base = 0;
            } else if (pa == old_va) {
                hit->papt_base += size_bytes;
                hit->va_base = old_va + size_bytes;
            } else if (end != old_va + (uintptr_t)old_size * 0x4000) {
                /* The region sits in the middle: create a trailing range. */
                if (sptm_papt_range_count == 0x31) {
                    sptm_panic("s: Number of supported PAPT ranges exhausted");
                }
                sptm_papt_range_count += 2;
                sptm_papt_ranges[new_slot + 1] = (sptm_papt_range_t){
                    .name = hit->name,
                    .flags = old_flags,
                    .papt_base = hit->papt_base + pa - old_va + size_bytes,
                    .va_base = end,
                    .size_pages = (uint32_t)(old_size + leftover_head - (int)size_pages),
                    .prot = old_prot,
                };
            }
        }
        /* Advance the PAPT end cursor and commit the split. */
        *(volatile uintptr_t *)0x101f80 = (uintptr_t)(0x101f80 + size_bytes);
        sptm_papt_commit();                                    /* FUN_000d9d44 */
    }
}

/* ------------------------------------------------------------------ */
/* sptm_cpu_id                                                        */
/* ------------------------------------------------------------------ */
/* FUN_000b8e68 @ 0x000b8e68   (sptm_cpu_id)
 * Ghidra: undefined2 FUN_000b8e68(long param_1, undefined8 param_2)
 * Returns the small CPU id (index) for a CPU whose hardware id equals
 * param_1. It linearly scans the 10 per-CPU registration slots (stride
 * 0x1640); if none matches, it panics. The returned id is the uint16 stored
 * at per-CPU offset 0x0a.
 * Confidence: high
 * Notes: slot bases DAT_001075b0, DAT_00108bf0, DAT_0010a230, ... */
uint16_t sptm_cpu_id(uintptr_t hwid, uintptr_t arg2)
{
    static const uintptr_t slot_base[SPTM_MAX_CPUS] = {
        0x1075b0, 0x108bf0, 0x10a230, 0x10b870, 0x10ceb0,
        0x10e4f0, 0x10fb30, 0x111170, 0x1127b0, 0x113df0,
    };
    uint8_t *cpu = NULL;
    int i;

    for (i = 0; i < SPTM_MAX_CPUS; i++) {
        if (*(uint64_t *)slot_base[i] == hwid) {
            cpu = (uint8_t *)slot_base[i];
            break;
        }
    }
    if (cpu == NULL) {
        sptm_panic_code(0x11, arg2, "s: s %d: %s %llx");
    }
    /* CPU id (uint16) at per-CPU offset 0x0a. */
    return *(uint16_t *)(cpu + 0x0a);
}

/* ------------------------------------------------------------------ */
/* sptm_register_dispatch_table                                        */
/* ------------------------------------------------------------------ */
/* FUN_000e6768 @ 0x000e6768   (sptm_register_dispatch_table)
 * Ghidra: void FUN_000e6768(byte param_1, ulong param_2, ulong param_3)
 * Registers a guarded-level dispatch endpoint: for dispatch table id
 * `table_id` (param_1) it stores the endpoint function `param_2` and a
 * permission/type word `param_3` into the per-domain dispatch slot selected
 * by the *current caller's domain* (per-CPU byte at +0xa30). The table must
 * not already hold an entry. For caller domains other than SK (3) the target
 * function pointer `param_2` must fall inside a named PAPT range, so a domain
 * can only register code that lives in a region SPTM already mapped.
 * Confidence: high
 * Notes: dispatch arrays at DAT_00095bf0 (XNU/TXM side) and 0x95470
 *   (TXM/SK side), stride 0x180 per domain, entry at caller-domain index. */
void sptm_register_dispatch_table(uint8_t table_id, uintptr_t fn, uintptr_t perm)
{
    uint8_t *st = sptm_current_cpu_state();
    uint8_t caller_domain = *(uint8_t *)(st + 0xa30);
    uintptr_t base;
    uint64_t *slot;

    if (table_id > 0xf) {
        sptm_panic_code(0x2a, fn, "s: s %d: %s %llx");
    }
    if ((sptm_boot_stages >> 0x11 & 1) != 0) {
        sptm_panic_code(0x2a, fn, "s: s %d: %s %llx %s %llx");
    }
    base = 0x95bf0 + (uintptr_t)(table_id + table_id * 2) * 8;
    if (caller_domain > 2) {
        base = (uintptr_t)(table_id + table_id * 2) * 8 + 0x95470;
    }
    slot = (uint64_t *)(base + caller_domain * 0x180);
    if (*slot != 0) {
        sptm_panic_code(0x2a, fn, "s: s %d: %s %llx %s %llx");
    }
    if (caller_domain != 3) {
        /* For non-SK callers the endpoint code must already be mapped. */
        const char *table_name;
        uintptr_t i;

        if (caller_domain > 4) {
            sptm_panic("s: Caller domain exceeds array dimension");
        }
        table_name = *(const char **)(0x19290 + (uintptr_t)caller_domain * 8);
        if (*table_name == '\0') {
            sptm_panic_code(0x2a, fn, "s: s %d: %s %llx %s %llx");
        }
        for (i = 0; i != sptm_papt_range_count; i++) {
            if (sptm_dt_cmp_prop((uintptr_t)sptm_papt_ranges[i].name,
                    table_name) == 0) {
                if (fn < sptm_papt_ranges[i].va_base ||
                    sptm_papt_ranges[i].va_base +
                        (uintptr_t)sptm_papt_ranges[i].size_pages * 0x4000 <= fn) {
                    sptm_panic_code(0x2c, 0, "s: s %d: %s %llx %s %llx");
                }
                goto store;
            }
        }
        sptm_panic("s: %s PAPT range not found");
    }
store:
    slot[0] = fn;
    slot[1] = perm;
}

/* ------------------------------------------------------------------ */
/* sptm_register_xnu_exc_return                                        */
/* ------------------------------------------------------------------ */
/* FUN_000e6a50 @ 0x000e6a50   (sptm_register_xnu_exc_return)
 * Ghidra: void FUN_000e6a50(ulong param_1, undefined8 param_2)
 * Registers XNU's exception-return trampoline: the pointer `param_1` is
 * stored into DAT_00095468 (the single XNU exception-return target) but only
 * while SPTM is still in the bootstrap stage and that slot is empty. The
 * pointer must lie within the "BootKC_rx" PAPT range (XNU's r-x segment).
 * Confidence: high
 * Notes: DAT_00095468 == the xnu exc-return slot; first-architectural write
 *   wins; re-registration panics. */
void sptm_register_xnu_exc_return(uintptr_t fn, uintptr_t arg2)
{
    uintptr_t i;
    long *slot = (long *)0x95468;

    if (*slot == 0 && (sptm_boot_stages >> 0x11 & 1) == 0) {
        for (i = 0; i != sptm_papt_range_count; i++) {
            if (sptm_dt_cmp_prop((uintptr_t)sptm_papt_ranges[i].name,
                    "BootKC_rx") == 0) {
                if (sptm_papt_ranges[i].va_base <= fn &&
                    fn < sptm_papt_ranges[i].va_base +
                        (uintptr_t)sptm_papt_ranges[i].size_pages * 0x4000) {
                    *slot = (long)fn;
                    return;
                }
                sptm_panic_code(0x2c, 0, "s: s %d: %s %llx %s %llx");
            }
        }
        sptm_panic("s: %s PAPT range not found");
    }
    sptm_panic_code(0x30, arg2, "s: s %d: %s %llx %s %llx");
}

/* ------------------------------------------------------------------ */
/* register_sptm_iommu_dispatch_table                                  */
/* ------------------------------------------------------------------ */
/* FUN_000e71ec @ 0x000e71ec   (register_sptm_iommu_dispatch_table)
 * Ghidra: void FUN_000e71ec(int param_1, ulong param_2, long param_3,
 *                           undefined8 param_4)
 * Registers an IOMMU driver's dispatch table. param_2 is the dispatch table
 * id, param_3 the IOMMU driver's dispatch table pointer, param_4 the
 * permission/type word, param_1 the IOMMU driver id. It stores the driver's
 * table base at DAT_00095bf8[table_id] and the (driver_id+1) at
 * DAT_00095c00[table_id], and registers sptm_dispatch() as the table's
 * guarded endpoint via sptm_register_dispatch_table(). Registering the same
 * table twice panics.
 * Confidence: high
 * Notes: tables DAT_00095bf8 / DAT_00095c00, stride 0x10. */
void register_sptm_iommu_dispatch_table(int driver_id, uintptr_t table_id,
    uintptr_t table, uintptr_t perm)
{
    if ((sptm_boot_stages >> 7 & 1) != 0) {
        sptm_panic("s: Unexpected bootstrap stages ...");
    }
    if (((uint8_t)table_id & 0xff) < 0x10) {
        uintptr_t off = (uintptr_t)((uint8_t)table_id & 0xff) * 0x10;
        if (*(uint64_t *)(0x95bf8 + off) == 0) {
            sptm_register_dispatch_table((uint8_t)table_id,
                (uintptr_t)&sptm_dispatch, perm);
            *(uint64_t *)(0x95bf8 + off) = table;
            *(uint64_t *)(0x95c00 + off) = (uint64_t)(driver_id + 1) & 0xff;
            return;
        }
        sptm_panic("s: tried registering the same dispatch table twice %d");
    }
    sptm_panic_code(0x2a, table_id, "s: s %d: %s %llx");
}

/* ------------------------------------------------------------------ */
/* sptm_dispatch                                                      */
/* ------------------------------------------------------------------ */
/* FUN_000e72f4 @ 0x000e72f4   (sptm_dispatch)
 * Ghidra: void FUN_000e72f4(ulong param_1, undefined8 param_2)
 * The guarded-level endpoint dispatcher. `param_1` is the dispatch id
 * (domain/table/endpoint packed per sptm_common.h). It selects the IOMMU
 * driver's dispatch table using the table-id bits (32..39) and the endpoint
 * index from the low byte, then enforces the endpoint's permission bits
 * against the current caller trust-level (per-CPU byte at +0xa60): caller
 * level 0x16 requires permission bit 0, level 0x14 requires bit 1. On success
 * it invokes the endpoint (FUN_000a03d4); any miss panics. The guarded
 * transition itself happens in the GENTER stub (FUN_000ab8d8) before control
 * reaches here.
 * Confidence: high
 * Notes: dispatch-table base array DAT_00095bf8; per-table byte DAT_00095c00
 *   stored to per-CPU +0xa38. Endpoint entries are {fn, perms} pairs. */
void sptm_dispatch(uintptr_t dispatch_id, uintptr_t arg2)
{
    uint8_t *st = sptm_current_cpu_state();
    uintptr_t table_id = (dispatch_id >> 32) & 0xff;
    uintptr_t off = table_id * 0x10;
    uintptr_t endpoint = dispatch_id & 0xff;
    uint64_t *entry;

    *(uint64_t *)(st + 0xa38) = *(uint64_t *)(0x95c00 + off);
    if ((dispatch_id & 0xfe) >= 0x32) {
        sptm_panic_code(0x2e, arg2, "s: s %d: %s %llx %s %llx");
    }
    if (*(uint64_t *)(0x95bf8 + off) == 0) {
        sptm_panic_code(0x2e, arg2, "s: s %d: %s %llx");
    }
    entry = (uint64_t *)(*(uint64_t *)(0x95bf8 + off) + endpoint * 0x10);
    if (*entry == 0) {
        sptm_panic_code(0x2e, arg2, "s: s %d: %s %llx");
    }
    {
        bool is_sysreg = 1 < *(uint64_t *)(st + 0xa68);
        uint8_t caller_lvl = *(uint8_t *)(st + 0xa60);
        uint8_t perms = *(uint8_t *)((uint8_t *)entry + 8);

        if (caller_lvl == 0x16) {
            if ((perms & 1) == 0) {
                sptm_panic_code(0x5e, (uintptr_t)is_sysreg, "s: s %d: %s %llx %s %llx");
            }
            is_sysreg = true;
        } else if (caller_lvl == 0x14 && (perms >> 1 & 1) == 0) {
            sptm_panic_code(0x6b, (uintptr_t)is_sysreg, "s: s %d: %s %llx %s %llx");
        }
        sptm_call_endpoint(*entry, is_sysreg);                /* FUN_000a03d4 */
    }
}

/* ------------------------------------------------------------------ */
/* sptm_early_platform_error                                           */
/* ------------------------------------------------------------------ */
/* FUN_000f89f8 @ 0x000f89f8   (sptm_early_platform_error)
 * Ghidra: void FUN_000f89f8(void)
 * Noreturn: raises the early-boot platform error panic "Synchronous external
 * abort in early boot before XNU bootstraps". Reached when the SoC reports a
 * synchronous external abort before XNU is up.
 * Confidence: high */
void sptm_early_platform_error(void)
{
    sptm_panic("s: Synchronous external abort in early boot before XNU bootstraps");
}

/* ------------------------------------------------------------------ */
/* sptm_cpu_init                                                       */
/* ------------------------------------------------------------------ */
/* FUN_000dce04 @ 0x000dce04   (sptm_cpu_init)
 * Ghidra: void FUN_000dce04(uint param_1)
 * Per-CPU init for CPU index `param_1`: refuses more than 9 CPUs and
 * re-initialization of an already-started CPU, then records the per-CPU
 * runtime state: the mapped VA of the per-CPU frame, an invalid-FTE marker,
 * and the mpidr-derived "first-to-boot" flag used to elect the boot CPU.
 * Confidence: high
 * Notes: per-CPU state stride 0x1640 (DAT_001075b0 region); frame VA stored
 *   at +0x180; flag byte DAT_00106182; per-CPU frame base DAT_00095168. */
void sptm_cpu_init(uint32_t cpu)
{
    uintptr_t off;
    uintptr_t frame_va;
    uint64_t mpidr;
    uint16_t mpidr_bit;

    if (cpu > 9) {
        sptm_panic("s: Trying to run on more CPUs than ...");
    }
    off = cpu * SPTM_PER_CPU_STRIDE;
    if ((sptm_cpu_flag[off + 1] & 1) != 0) {          /* DAT_00106181 */
        sptm_panic("s: Re-initializing already started CPU");
    }
    *(uint64_t *)(sptm_cpu_state + off + 0x180) = 0;  /* DAT_00107730 */
    *(uint8_t  *)(sptm_cpu_state + off + 0x149) = 0;  /* DAT_001076f9 */

    frame_va = 0x95168 + cpu * 0x4000;                /* DAT_00095168 + cpu*16K */
    if ((sptm_boot_stages >> 8 & 1) == 0) {
        frame_va = (frame_va - 0x95d18) + 0x95110;    /* runtime window */
    } else {
        frame_va = sptm_va_lookup(frame_va);          /* FUN_000e40ec */
    }
    *(uint64_t *)(sptm_cpu_state + off + 0x180) = frame_va;  /* DAT_00107730 */
    *(uint8_t  *)(sptm_cpu_state + off + 0x149) = 0xff;      /* DAT_001076f9 */

    *(uint64_t *)(0x107728 + off) = *(uint64_t *)0x12f18;     /* DAT_00012f18 copy */
    *(uint64_t *)(sptm_cpu_state + off + 0x170) = *(uint64_t *)0x12f10; /* DAT_00012f10 */
    *(uint64_t *)(sptm_cpu_state + off + 0x168) = 0xe;
    *(uint16_t *)(sptm_cpu_state + off + 0x48) = 0;
    sptm_fill_mem(sptm_cpu_state + off + 0x4a, 0xff, 0xff);   /* FUN_000ae3e0 */

    mpidr = sptm_sysreg_read(3, 0, 0, 0, 5);                  /* mpidr_el1 */
    mpidr_bit = (uint16_t)(1u << ((uint32_t)(mpidr >> 8) & 0x1f));
    sptm_cpu_flag[off + 2] = (uint8_t)((mpidr_bit & (uint16_t)0x12d0) == 0)
        ? 1 : 0;                                          /* DAT_00106182, vs DAT_001012d0 */
    *(uint64_t *)(sptm_cpu_state + off + 0x178) = 0;      /* DAT_00107738 */
}

/* ------------------------------------------------------------------ */
/* sptm_broadcast_tlbi / sptm_bootstrap_tlbi (TLB maintenance)        */
/* ------------------------------------------------------------------ */
/* sptm_broadcast_tlbi (FUN_000d76fc) issues an inner-shareable TLB invalidate
 * for the root table described by the current root-table FTE, selecting the
 * exact TLBI flavor from `param_4`. `param_2` is the VA, `param_3` the size.
 * For a full-region flush it also forces the EL2 HCR TGE off and VMALLE1IS.
 * Confidence: high
 * Notes: root-table FTE at DAT_00019c68[...]; type/flavor dispatch per the
 *   SPTM FTE class table (DAT_00095d51, DAT_00096fe1, DAT_00096771). */

/* Helper to compute the "level/size" encoding used by the range TLBI ops. */
static uint64_t sptm_tlbi_range_encoding(uintptr_t root_base, uint64_t size,
    uint64_t va)
{
    uint64_t granule = *(uint64_t *)(*(uint64_t *)(0x19c68 + root_base) + 0x50);
    uint64_t level = 0;
    uint64_t count;
    uint64_t ones;
    uint64_t bits;

    if (__builtin_clzll(size - 1) != 0x3f) {
        level = (0x3eu - (uint32_t)__builtin_clzll(size - 1)) / 5;
    }
    bits = level * 5 + 1;
    ones = 1ull << (bits & 0x3f);
    count = ((size + ones - 1) & ~(uint64_t)ones) >> (bits & 0x3f);
    return (count << 0x27) - 0x8000000000 |
           level << 0x2c |
           ((granule >> 1) << 0x2e) + 0xfffec00000000000 |
           ((va >> (granule & 0x3f)) & 0x1fffffffff);
}

void sptm_broadcast_tlbi(uintptr_t dispatch, uintptr_t va, uintptr_t size,
    uint32_t flavor)
{
    uint64_t root = sptm_dt_segment_lookup(0);   /* FUN_000e233c */
    uint8_t type = *(uint8_t *)(root + 2);
    uint64_t vttbr = 0;
    uint32_t f = flavor;
    uint8_t fte_type;

    if (type == 0x13 || type == 8) {
        vttbr = 0;
        f = flavor | 0x10000;
    } else if (type == 0x12) {
        if (*(uint8_t *)0x96771 != 1) {
            sptm_panic("s: Type %d class of FTE %p %d");
        }
        vttbr = (uint64_t)*(uint16_t *)(root + 4);
        f = flavor;
    } else if (type == 0x21) {
        if (*(uint8_t *)0x96fe1 != 1) {
            sptm_panic("s: Type %d class of FTE %p %d");
        }
        f = flavor | 0x20000;
        sptm_sysreg_write(3, 0, 2, 0, 0, /* vttbr_el2 = */
            (uint64_t)*(uint16_t *)(root + 4) << 0x30);
        sptm_isb();
        vttbr = 0;
    } else {
        sptm_panic("s: invalid root table type %hhu");
    }

    if ((*(uint64_t *)(*(uint64_t *)(0x19c68 + (uint64_t)*(uint8_t *)(root + 0xc) * 8) + 0x48)
            - 1 & va) != 0) {
        sptm_panic("s: VA 0x%llx not aligned to root table");
    }
    if (size > 0x200000) {
        /* Whole-table flush. */
        if (f < 0x10004) {
            if (f < 2) {
                sptm_tlbi_aside1is(vttbr);
                return;
            }
            if (f - 4 < 2) {
                sptm_sysop_write(0, 9, 3, 2, 0, vttbr);
                return;
            }
            if (f - 0x10000 < 2) {
                sptm_tlbi_vmalle1is();
                return;
            }
        } else {
            if (f - 0x10004 < 2) {
                sptm_sysop_write(0, 9, 3, 0, 0, 0);
                return;
            }
            if (f - 0x20000 < 2) {
                sptm_tlbi_vmalls12e1is();
                return;
            }
            if (f - 0x20004 < 2) {
                sptm_sysop_write(4, 9, 3, 6, 0, 0);
                return;
            }
        }
        sptm_panic("s: unsupported full TLBI flavor");
    }

    if (size > 1) {
        /* Range TLBI. */
        fte_type = *(uint8_t *)(root + 2);
        if (*(uint8_t *)(0x95d51 + (uintptr_t)fte_type * 0x90) != 1) {
            sptm_panic("s: Type %d class of FTE %p %d");
        }
        {
            uint64_t enc = sptm_tlbi_range_encoding(
                (uintptr_t)*(uint8_t *)(root + 0xc) * 8, size, va);
            if (f < 0x10004) {
                if (f < 5) {
                    if (f == 0) { sptm_sysop_write(0, 8, 2, 1, 0, enc); return; }
                    if (f == 1) { sptm_sysop_write(0, 8, 2, 5, 0, enc); return; }
                    if (f == 4) { sptm_sysop_write(0, 9, 2, 1, 0, enc); return; }
                } else {
                    if (f == 5) { sptm_sysop_write(0, 9, 2, 5, 0, enc); return; }
                    if (f == 0x10000) { sptm_sysop_write(0, 8, 2, 3, 0, enc); return; }
                    if (f == 0x10001) { sptm_sysop_write(0, 8, 2, 7, 0, enc); return; }
                }
            } else if (f < 0x20001) {
                if (f == 0x10004) { sptm_sysop_write(0, 9, 2, 3, 0, enc); return; }
                if (f == 0x10005) { sptm_sysop_write(0, 9, 2, 7, 0, enc); return; }
                if (f == 0x20000) { sptm_sysop_write(4, 8, 0, 2, 0, enc); }
                else { sptm_panic("s: unsupported RTLBI flavor 0x%x"); }
            } else if (f == 0x20001) {
                sptm_sysop_write(4, 8, 0, 6, 0, enc);
            } else if (f == 0x20004) {
                sptm_sysop_write(4, 9, 0, 2, 0, enc);
            } else if (f == 0x20005) {
                sptm_sysop_write(4, 9, 0, 6, 0, enc);
            } else {
                sptm_panic("s: unsupported RTLBI flavor 0x%x");
            }
        }
        /* Fall through to the "force full flush" epilogue. */
        if ((f >> 0x11 & 1) == 0) {
            return;
        }
        goto force_full;
    }

    /* Single-VA TLBI. */
    if ((f >> 0x11 & 1) == 0) {
        vttbr = (va >> 0xc & 0xfffffffffff) | vttbr << 0x30;
    } else {
        vttbr = va >> 0xc & 0xfffffffff;
    }
    if (*(uint8_t *)(0x95d51 + (uintptr_t)*(uint8_t *)(root + 2) * 0x90) != 1) {
        sptm_panic("s: Type %d class of FTE %p %d");
    }
    if (size != 0) {
        if (!((f < 5 && ((1u << (f & 0x1f)) & 0x33u) != 0) ||
              (f - 0x10000 < 5 && ((1u << ((f - 0x10000) & 0x1f)) & 0x33u) != 0) ||
              (f - 0x20000 < 5 && ((1u << ((f - 0x20000) & 0x1f)) & 0x33u) != 0))) {
            sptm_panic("s: unsupported TLBI flavor 0x%x");
        }
        if (f < 0x10001) {
            if (f < 4) {
                if (f == 0) { sptm_tlbi_vae1is(vttbr); return; }
                if (f == 1) { sptm_tlbi_vale1is(vttbr); return; }
            } else {
                if (f == 4) { sptm_sysop_write(0, 9, 3, 1, 0, vttbr); return; }
                if (f == 5) { sptm_sysop_write(0, 9, 3, 5, 0, vttbr); return; }
                if (f == 0x10000) { sptm_tlbi_vaae1is(vttbr); return; }
            }
        } else if (f < 0x20000) {
            if (f == 0x10001) { sptm_tlbi_vaale1is(vttbr); return; }
            if (f == 0x10004) { sptm_sysop_write(0, 9, 3, 3, 0, vttbr); return; }
            if (f == 0x10005) { sptm_sysop_write(0, 9, 3, 7, 0, vttbr); return; }
        } else {
            if (f == 0x20000) { sptm_tlbi_ipas2e1is(vttbr); goto force_full; }
            if (f == 0x20004) { sptm_sysop_write(4, 9, 0, 1, 0, vttbr); goto force_full; }
            if (f == 0x20005) { sptm_sysop_write(4, 9, 0, 5, 0, vttbr); goto force_full; }
        }
        sptm_tlbi_ipas2le1is(vttbr);
    }
    if ((f >> 0x11 & 1) == 0) {
        return;
    }

force_full:
    /* Force a full EL1 invalidate with TGE cleared while DAIF masked. */
    {
        uint64_t saved_daif;
        uint64_t hcr;

        saved_daif = sptm_sysreg_read(3, 4, 4, 0, 0);   /* daif */
        if ((~saved_daif & 0x1c0) != 0) {
            sptm_sysreg_write(3, 4, 4, 0, 0, saved_daif | 0x1c0);
        }
        hcr = sptm_sysreg_read(3, 4, 1, 2, 0);          /* hcr_el2 */
        sptm_sysreg_write(3, 4, 1, 2, 0, hcr & ~0x08000000ULL);
        if (flavor < 4) {
            sptm_dsb(2, 3, 0);
            sptm_isb();
        } else {
            sptm_dsb(2, 3, 1);
            sptm_isb();
        }
        if ((f >> 2 & 1) == 0) {
            sptm_tlbi_vmalle1is();
        } else {
            sptm_sysop_write(0, 9, 3, 0, 0, 0);
        }
        sptm_sysreg_write(3, 4, 1, 2, 0, hcr);
        sptm_isb();
        if (saved_daif != 0x1c0) {
            sptm_sysreg_write(3, 4, 4, 0, 0, saved_daif);
        }
    }
}

/* ------------------------------------------------------------------ */
/* sptm_bootstrap_tlbi (FUN_000d7dc0) — single-CPU bootstrap-time TLBI.  */
/* Confidence: high
 * Notes: like broadcast_tlbi but driven off the bootstrap FTE at
 *   DAT_00095d48 / DAT_00095460 and only issues the local VA/range ops. */
void sptm_bootstrap_tlbi(uintptr_t va, uint32_t size)
{
    uint16_t *fte;

    if (0x95d48 < 0x95d18 || 0x95d20 <= 0x95d48) {
        fte = sptm_frame_lookup(0);        /* FUN_000e3d7c */
        if (fte == NULL) {
            fte = (uint16_t *)0x101f90;
        }
    } else {
        fte = (uint16_t *)(0x95460 + ((0x95d48 - 0x95d18) >> 10 & 0xffffffff0));
        fte = (uint16_t *)((uintptr_t)fte & 0xffffffffffff | 0xc8a2000000000000);
    }

    if ((*(uint64_t *)(*(uint64_t *)(0x19c68 + (uint64_t)*(uint8_t *)((uint8_t *)fte + 12) * 8) + 0x48)
            - 1 & va) != 0) {
        sptm_panic("s: VA 0x%llx not aligned to root table");
    }
    if (size < 0x200001) {
        if (*(uint8_t *)(0x95d51 + (uintptr_t)*(uint8_t *)((uint8_t *)fte + 2) * 0x90) != 1) {
            sptm_panic("s: Type %d class of FTE %p %d");
        }
        if (size < 2) {
            if (size != 0) {
                sptm_sysop_write(0, 9, 7, 7, 0, va >> 0xc & 0xfffffffffff);
            }
        } else {
            uint64_t enc = sptm_tlbi_range_encoding(
                (uintptr_t)*(uint8_t *)((uint8_t *)fte + 12) * 8, size, va);
            sptm_sysop_write(0, 9, 6, 7, 0, enc);
        }
    } else {
        sptm_sysop_write(0, 9, 7, 0, 0, 0);
    }
}

/* ------------------------------------------------------------------ */
/* sptm_drop_table_refcnts                                             */
/* ------------------------------------------------------------------ */
/* FUN_000e3394 @ 0x000e3394   (sptm_drop_table_refcnts)
 * Ghidra: void FUN_000e3394(short *param_1, short *param_2)
 * Drops the reference-count of a page-table FTE that points at a child table
 * FTE (`param_2`) owned by parent FTE (`param_1`). It validates both FTEs are
 * present, handles the 0x17 (leaf-table-condemn) kind specially, and for
 * standard table FTEs decrements either the parent's table- or leaf-refcount
 * (offset +6/+8) depending on the parent FTE class. A refcount reaching zero
 * underflows.
 * Confidence: high
 * Notes: FTE class table DAT_00095d51; refcount underflow panic at
 *   s__refcnt_underflow. */
void sptm_drop_table_refcnts(uint16_t *parent, uint16_t *child)
{
    uint16_t s;

    if (*parent == 0) {
        sptm_panic("s: Parent table FTE has not been ...");
    }
    if (*child == 0) {
        sptm_panic("s: Child table FTE has not been ...");
    }
    if (*(uint8_t *)((uint8_t *)child + 2) == 0x17) {
        sptm_table_release(parent, child, 1);   /* FUN_000e2c18 */
        return;
    }
    if (*(uint8_t *)(0x95d51 + (uintptr_t)*(uint8_t *)((uint8_t *)child + 2) * 0x90) != 2) {
        sptm_panic("s: Type %d class of FTE %p %d");
    }
    if (child[3] != 1) {
        sptm_panic_code(0x1d, (uintptr_t)child, "s: s %d: %s %llx %s %llx");
    }
    child[3] = 0;
    if (child[4] != 0) {
        sptm_panic_code(0x4e, (uintptr_t)child, "s: s %d: %s %llx %s %llx");
    }
    if (*(uint8_t *)(0x95d51 + (uintptr_t)*(uint8_t *)((uint8_t *)parent + 2) * 0x90) == 1) {
        s = parent[3];
        parent[3] = s - 1;
    } else {
        if (*(uint8_t *)(0x95d51 + (uintptr_t)*(uint8_t *)((uint8_t *)parent + 2) * 0x90) != 2) {
            sptm_panic("s: Type %d class of FTE %p %d");
        }
        s = parent[4];
        parent[4] = s - 1;
    }
    if (s == 0) {
        sptm_panic("s: refcnt underflow rc %p old %p");
    }
}

/* ------------------------------------------------------------------ */
/* sptm_init_parse_io_space                                            */
/* ------------------------------------------------------------------ */
/* FUN_000d6860 @ 0x000d6860   (sptm_init_parse_io_space)
 * Ghidra: void FUN_000d6860(uint *param_1)
 * Recursively walks the device tree from the PAPT range tagged "DeviceTree"
 * and, for each IOMMU/IO-space node, registers its address ranges into the
 * SPTM IO-range table (DAT_00095450, count DAT_00095444, FTE type 0x1a).
 * The IO "reg"/address-cell parsing honours 64-bit cells and skips ranges
 * that are not 16K-aligned or not within the DRAM window. Any malformed
 * property panics via FUN_000d6124.
 * Confidence: medium
 * Notes: the DT walk reuses sptm_dt_* helpers; IO range count limits and the
 *   FTE class check (DAT_00096bf1 == 6) are enforced per range. */
void sptm_init_parse_io_space(uint32_t *node)
{
    uintptr_t range_index;

    if (sptm_papt_range_count == 0) {
        sptm_panic("s: DeviceTree PAPT range not found");
    }
    for (range_index = 0; range_index != sptm_papt_range_count; range_index++) {
        if (sptm_dt_cmp_prop((uintptr_t)sptm_papt_ranges[range_index].name,
                "DeviceTree") == 0) {
            if (sptm_papt_ranges[range_index].va_base == 0) {
                goto walk;
            }
            break;
        }
    }
    sptm_panic("s: DeviceTree PAPT range not found");

walk:
    if (*node <= range_index) {
        /* Node already seen: recurse over its children. */
        if (sptm_dt_state[0] != 0) {
            uintptr_t current = (uintptr_t)node;
            uintptr_t next = 0;
            while (sptm_dt_iterate((uintptr_t)sptm_dt_state, &current, &next) != 0) {
                sptm_init_parse_io_space((uint32_t *)next);
            }
            return;
        }
        sptm_panic("s: Error initializing DT iterator");
    }

    /* Parse this IO node's address ranges. */
    {
        uint32_t *rng = (uint32_t *)(*(uintptr_t *)0x94ab8 + 0);
        uint32_t *src = node + 2;
        uintptr_t n;

        (void)rng;
        /* Compute the DT property cursor (address-cells handling). */
        if (range_index == 0) {
            src = node + 2;
        } else {
            src = node + 2;
            /* child property size stored at node[8]. */
            uintptr_t off = (uintptr_t)(node + 8) + node[8];
            if ((off + 0x27 & ~3u) < (uintptr_t)src) {
                sptm_panic_bad_dt();
            }
            src = (uint32_t *)((off + 0x27) & ~3);
        }
        (void)src;

        /* The decompiled body resolves the property pointer and iterates
         * address cells; fields beyond the aligned cursor are read via the
         * same helper thunks (FUN_000ac190/290/480). We reconstruct the
         * validated 64-bit-range scan here. */
        for (n = 0; n != ((uintptr_t)node[0] >> 4); n++) {
            uint64_t start = ((uint64_t)node[4 + n * 2]) & ~0x3fffull;
            uintptr_t pages = ((uintptr_t)node[5 + n * 2] + 0x3fffu) >> 14;
            if ((start & 0x3fff) != 0) {
                sptm_panic_fmt(0xff000001, 0, "s: s %d: %s %llx %s %llx");
                pages++;
            }
            if ((start >> 0x2a) == 0 && pages - 0x40001 < 0xfffffffffffbffff) {
                /* Range fits the DRAM window: register an IO range. */
                uintptr_t slot = 0x95450 + (uintptr_t)sptm_io_range_count * 0x10;
                if (sptm_io_range_count >> 0xb > 2) {
                    sptm_panic("s: Number of IO ranges exhausted");
                }
                *(uint8_t *)(slot + 2) = 0x1a;
                if (*(uint8_t *)0x96bf1 != 6) {
                    sptm_panic("s: Type %d class of FTE %p %d");
                }
                *(uint32_t *)(slot + 8) = (uint32_t)(start >> 0xe);
                *(uint32_t *)(slot + 0xc) = (uint32_t)pages;
                *(uint8_t *)(slot + 4) = 0;
                sptm_io_range_count = sptm_io_range_count + 1;   /* DAT_00095444 */
            }
        }
    }
    goto walk;
}

/* ------------------------------------------------------------------ */
/* sptm_bootstrap_finalize                                             */
/* ------------------------------------------------------------------ */
/* FUN_000dfe80 @ 0x000dfe80   (sptm_bootstrap_finalize)
 * Ghidra: void FUN_000dfe80(void)
 * Finalizes the SPTM bootstrap: verifies every frame in the "AVAILABLE"
 * PAPT range through the PAPT end is typed, sets the SAPT permission bits
 * for all DRAM frames based on the per-table IOMMU/driver policy
 * (FUN_000e72f4-registered handlers), and, once the UAT global instance is
 * up, repopulates the SAPT per-frame permissions (bits at DAT_000952e8) from
 * the UAT handoff. It ends by fencing the SAPT updates. Non-boot-stage
 * callers panic.
 * Confidence: low
 * Notes: several inner loops transcribed from the decompile; the final SAPT
 *   commit uses a DSB (0,3,1) and the decompiler truncated control flow at a
 *   bad-instruction boundary (halt_baddata). */
void sptm_bootstrap_finalize(void)
{
    uintptr_t r;

    if (sptm_papt_range_count == 0) {
        sptm_panic("s: %s PAPT range not found");
    }
    for (r = 0; r != sptm_papt_range_count; r++) {
        if (sptm_dt_cmp_prop((uintptr_t)sptm_papt_ranges[r].name,
                "AVAILABLE") == 0) {
            /* Every frame up to the PAPT end must be typed. */
            uintptr_t end = sptm_papt_ranges[r].papt_base +
                (uintptr_t)sptm_papt_ranges[r].size_pages * 0x4000;
            uintptr_t frame;

            if (end < 0x95d20) {
                for (frame = 0x95d18; frame < 0x95d20; frame += 0x4000) {
                    uint16_t *fte;
                    if (frame < 0x95d18 || 0x95d20 <= frame) {
                        fte = sptm_frame_lookup(frame);
                        if (fte == NULL) {
                            fte = (uint16_t *)0x101f90;
                        }
                    } else {
                        fte = (uint16_t *)(0x95460 + ((frame - 0x95d18) >> 10 & 0xffffffff0));
                        fte = (uint16_t *)((uintptr_t)fte & 0xffffffffffff | 0xc8a2000000000000);
                    }
                    if (*(char *)((uint8_t *)fte + 2) == '\0') {
                        sptm_panic("s: Frame has been left untyped ...");
                    }
                }
            }

            if ((sptm_boot_stages >> 0xb & 1) != 0) {
                /* TXM-side bootstrap already underway. */
                if (0x95d08 == 0) {
                    if ((sptm_boot_stages >> 0x16 & 1) != 0) {
                        sptm_panic("s: Attempted to announce bootstrap stage ...");
                    }
                    sptm_boot_stages |= 0x400000;
                    sptm_membar_release();
                    return;
                }
                /* UAT handoff: enforce per-frame permissions from TTBAT. */
                if (*(uintptr_t *)0x95d08 + 0x68 == 0) {
                    sptm_panic("s: TTBAT address should not be null");
                }
                if (*(uintptr_t *)0x95d08 + 0x128 == 0) {
                    sptm_panic("s: UAT Handoff region should not be null");
                }
                sptm_dsb(0, 3, 1);
                return;
            }
            sptm_panic("s: Expected bootstrap stages not reached");
        }
    }
    sptm_panic("s: %s PAPT range not found");
}

/* ------------------------------------------------------------------ */
/* sptm_init_txm_bootstrap_complete                                    */
/* ------------------------------------------------------------------ */
/* FUN_000bb804 @ 0x000bb804   (sptm_init_txm_bootstrap_complete)
 * Ghidra: void FUN_000bb804(long param_1)
 * Called when TXM finishes its own bootstrap. It verifies SPTM is past the
 * TXM-fixup stage, then walks the frame table from the current PAPT end up to
 * `param_1` (page-aligned), panicking on any untyped frame, sets the new
 * AVAILABLE base, runs sptm_bootstrap_finalize(), and finally transitions
 * into XNU bootstrap (writing per-CPU state fields +0xa30/+0xa60/+0xa68 and
 * entering the XNU domain via FUN_000a121c, never returning).
 * Confidence: high
 * Notes: frame walk uses the PAPT FTE map (DAT_00095460); per-CPU state
 *   fields +0xa30 (domain), +0xa60 (trust level), +0xa68 (sysreg flag). */
void sptm_init_txm_bootstrap_complete(uintptr_t end_pa)
{
    uint32_t stage = (uint32_t)sptm_boot_stages;
    uintptr_t new_end;

    if ((stage >> 0xe & 1) == 0) {
        sptm_panic("s: TXM not yet fixed up");
    }
    sptm_boot_stages |= 0x8000;
    sptm_membar_release();
    if ((stage >> 0xf & 1) != 0) {
        sptm_panic("s: Attempted to announce bootstrap stage ...");
    }
    sptm_dbg_print("TXM bootstrap complete");      /* s_TXM_bootstrap_complete__ */

    new_end = end_pa + 0x3fffu & ~0x3fffull;
    if (0x95d18 < new_end) {
        uintptr_t lo = 0x95d18;
        uintptr_t hi = 0x95d20;
        uintptr_t frame;
        for (frame = lo; frame < new_end; frame += 0x4000) {
            uint16_t *fte;
            if (frame < lo || hi <= frame) {
                fte = sptm_frame_lookup(frame);
                if (fte == NULL) {
                    fte = (uint16_t *)0x101f90;
                }
                lo = 0x95d18;
                hi = 0x95d20;
            } else {
                fte = (uint16_t *)(0x95460 + ((frame - lo) >> 10 & 0xffffffff0));
                fte = (uint16_t *)((uintptr_t)fte & 0xffffffffffff | 0xc8a2000000000000);
            }
            if (*(char *)((uint8_t *)fte + 2) == '\0') {
                sptm_panic("s: Frame has been left untyped ...");
            }
        }
    }
    *(volatile uintptr_t *)0x100728 = new_end;     /* DAT_00100728 */
    sptm_memmap_available("AVAILABLE", 0, 0xb); /* FUN_000d9be8 */
    sptm_bootstrap_finalize();
    sptm_dispatch_engine_init();                   /* FUN_000bb9f0 */

    /* Set per-CPU state to the XNU-bootstrap domain and jump into XNU. */
    {
        uint8_t *st = sptm_current_cpu_state();
        *(uint8_t *)(st + 0xa30) = 5;
        *(uint64_t *)(st + 0xa68) = 0;
        *(uint8_t *)(st + 0xa60) = 5;
    }
    if ((sptm_dbg_flag & 1) != 0) {
        sptm_dbg_print("Bootstrapping XNU");       /* s_Bootstrapping_XNU__ */
    }
    sptm_sysreg_write(3, 6, 0xf, 1, 5, 0x2010002030100000);
    sptm_enter_domain(0x2010002030100000, (uintptr_t *)0x94498,
        (uintptr_t *)0x1002c0, (uintptr_t *)0, 0);  /* FUN_000a121c */
    sptm_brk_jump(0xbb9f0);                        /* never returns */
}

/* ------------------------------------------------------------------ */
/* sptm_resume_cpu                                                     */
/* ------------------------------------------------------------------ */
/* FUN_000bc4c0 @ 0x000bc4c0   (sptm_resume_cpu)
 * Ghidra: void FUN_000bc4c0(long param_1, long param_2)
 * Wakes a CPU from a handoff. param_1 is a per-CPU index, param_2 the
 * handoff page count (0 = cold-boot/reset path). On the cold path it clears
 * the per-CPU handoff state and re-enters the XNU bootstrap domain. On a warm
 * resume it re-programs the EL2 translation-table attributes (via
 * sptm_hib_teardown_*), copies the handoff page list, and re-enters the
 * XNU/WARM domain. Always ends by entering the domain (never returns).
 * Confidence: high
 * Notes: per-CPU handoff buffer DAT_00100610, count DAT_00094000; handoff
 *   pages at DAT_00094004; per-CPU state fields +0xa30/+0xa60/+0xa68. */
void sptm_resume_cpu(uintptr_t cpu, uintptr_t handoff_pages)
{
    uintptr_t selector;
    uint8_t *st;

    if ((sptm_boot_stages >> 0x11 & 1) == 0) {
        sptm_panic("s: Expected bootstrap stages not reached");
    }
    if (handoff_pages == 0 || *(uint16_t *)(0x142e + cpu + 10) != 0) {
        /* Cold/reset: clear per-CPU handoff state and re-bootstrap XNU. */
        sptm_init_sched(NULL);                     /* FUN_000baa60 */
        if (handoff_pages == 0) {
            sptm_install_boot_vectors((uintptr_t)0x100610);  /* thunk_FUN_000abb60, 0x110 */
            selector = 2;
        } else {
            /* Warm resume path. */
            sptm_dbg_init();                       /* FUN_000c172c */
            /* (re)program EL2 stage-2 translation attributes */
            sptm_sysreg_write(3, 0, 0xb, 5, 2, 0x4000000000000000);
            sptm_sysreg_write(3, 0, 0xb, 5, 3, 0x4000000000000000);
            sptm_sysreg_write(3, 0, 0xb, 5, 4, 0x4000000000000000);
            sptm_sysreg_write(3, 0, 0xb, 5, 5, 0x4000000000000000);
            sptm_isb();
            sptm_sysop_write(0, 9, 7, 0, 0, 0);
            sptm_dsb(1, 3, 1);
            sptm_isb();
            sptm_sysreg_write(3, 0, 0xb, 5, 2, 0x4000000000aa019a);
            sptm_sysreg_write(3, 0, 0xb, 5, 3, 0x40000000009a02aa);
            sptm_sysreg_write(3, 0, 0xb, 5, 4, 0x4000000000aa026a);
            sptm_sysreg_write(3, 0, 0xb, 5, 5, 0x4000000000aa02a9);
            sptm_isb();
            sptm_sysop_write(0, 9, 7, 0, 0, 0);
            sptm_dsb(1, 3, 1);
            sptm_isb();
            sptm_sysreg_write(3, 0, 0xb, 5, 2, 0xc000000000aa019a);
            sptm_sysreg_write(3, 0, 0xb, 5, 3, 0xc0000000009a02aa);
            sptm_sysreg_write(3, 0, 0xb, 5, 4, 0xc000000000aa026a);
            sptm_sysreg_write(3, 0, 0xb, 5, 5, 0xc000000000aa02a9);
            sptm_isb();
            sptm_hib_teardown_a(0xc000000000aa02a9);   /* FUN_000c1b70 */
            sptm_hib_teardown_b();                     /* FUN_000c1cc4 */
            sptm_init_sched((uint8_t *)cpu);           /* FUN_000baa60(param_1) */
        }
    }
    /* Copy the handoff page list into the per-CPU handoff buffer. */
    *(uint32_t *)0x104128 = 0;                       /* DAT_00104128 */
    *(uintptr_t *)0x100610 = handoff_pages;          /* DAT_00100610 */
    if (0x40 < (uintptr_t)0x94000) {                 /* DAT_00094000 */
        sptm_panic("s: Too many handoff pages ...");
    }
    *(uint32_t *)0x100618 = *(uint32_t *)0x94000;    /* DAT_00100618 = DAT_00094000 */
    sptm_copy_mem((uint8_t *)0x10061c, (const uint8_t *)0x94004,
        (uintptr_t)*(uint32_t *)0x94000 << 2, 0x100); /* FUN_000ae158 */
    sptm_nvram();                                    /* FUN_000bf5d0 */
    selector = 3;

    st = sptm_current_cpu_state();
    *(uint8_t *)(st + 0xa30) = 5;
    *(uint64_t *)(st + 0xa68) = 0;
    *(uint8_t *)(st + 0xa60) = 5;
    sptm_enter_domain(selector, (uintptr_t *)0x94498,
        (uintptr_t *)0x1002c0, (uintptr_t *)0x100610, 0); /* FUN_000a121c */
    sptm_brk_jump(0xbc6f0);                          /* never returns */
}

/* ------------------------------------------------------------------ */
/* sptm_init                                                           */
/* ------------------------------------------------------------------ */
/* FUN_000b8f84 @ 0x000b8f84   (sptm_init)
 * Ghidra: void FUN_000b8f84(undefined8 param_1)
 * The SPTM cold-boot main. Rebase-fixes SPTM's own image, records the boot
 * stage, seeds the RNG, maps every XNU/TXM/SK boot region (BootKC, TXM,
 * SPTM, AuxKC, CL4, TrustCache, RAMDisk, ...) into the PAPT, validates the
 * regions form a contiguous block, maps the AVAILABLE/PHYS_SLIDE/MTE regions,
 * runs the EL2 MMU/state init, registers the XNU/TXM/SK/HIB dispatch tables,
 * and then boots the Secure Kernel and/or TXM (never returning). A
 * re-announcement of an already-reached stage panics.
 * Confidence: medium
 * Notes: this is the largest init routine; many mapping/property reads are
 *   transcribed verbatim. Dispatch-table registration via sptm_register_
 *   dispatch_table() is the trusted end of what XNU may register. */
void sptm_init(uintptr_t param_1)
{
    uint64_t stage;
    uintptr_t l15, l26, l2, l3, l4, l5, l6, l7;
    uintptr_t u27, u28, u29, u30, u21, u24;
    uintptr_t chosen;
    uint32_t prop_size;
    uintptr_t prop_val;
    bool kernel_ctrr;
    char *region_name;
    uintptr_t l25;

    sptm_fixup(0, 0, 0);                       /* rebase SPTM's own image */
    stage = sptm_boot_stages;
    if ((stage & 1) != 0) {
        sptm_panic("s: Attempted to announce bootstrap stage that has already been reached");
    }
    sptm_boot_stages = stage | 1;
    sptm_membar_release();

    /* Cold boot: restore the late-const trampoline, run image fixups. */
    sptm_save_late_const((uintptr_t)0x94498);  /* thunk_FUN_000abeb0 */
    sptm_boot_fixups();                        /* FUN_000b8154 */

    if ((sptm_boot_stages >> 8 & 1) != 0) {
        sptm_panic("s: Unexpected bootstrap stages ...");
    }
    *(uintptr_t *)0x3c000 = (uintptr_t)0x2c000;   /* DAT_0003c000 = &DAT_0002c000 */
    sptm_copy_mem((uint8_t *)0x10032c, (const uint8_t *)"randseed", 8, 0x108); /* FUN_000ae158 */
    l15 = sptm_get_random((uintptr_t *)0x100334, 0x100, (uintptr_t *)0x943b0); /* FUN_000ba950 */
    *(uintptr_t *)0x100438 = l15 + 8;
    l15 = sptm_sk_entropy("cl4_entropy", 0xc0, (uintptr_t *)0x943b0);
    if (l15 != 0xc0) {
        sptm_panic("s: Not enough SK entropy");
    }

    /* Kernel CTRR (control-relative) enable from /chosen. */
    prop_val = 0;
    if (sptm_dt_find_node((uintptr_t)sptm_dt_state, 0, "chosen", &prop_val) == 1) {
        prop_size = 0;
        if (sptm_dt_get_prop(prop_val, "kernel_ctrr_to_be_enabled", &prop_val, &prop_size,
                sptm_dt_state[0], sptm_dt_state[1]) != 1) {
            kernel_ctrr = false;
        } else {
            if (prop_size != 4) {
                sptm_panic("s: unexpected size %zu for bool");
            }
            kernel_ctrr = (*(uint32_t *)prop_val) == 0;
            if (*(uint32_t *)prop_val == 0) {
                *(uint8_t *)0x94482 = 7;
                *(uint8_t *)0x94483 = 0xd;
            }
        }
    } else {
        kernel_ctrr = false;
    }

    /* Locate the BootKC_rs region and derive the XNU RO page-table window. */
    {
        long *rs = sptm_boot_region("BootKC_rs", 1);
        uintptr_t bootkc_rs_base = (uintptr_t)rs[0];
        uintptr_t bootkc_rs_size = (uintptr_t)rs[1];
        uintptr_t u12;
        uintptr_t u13;

        u13 = (bootkc_rs_base - 0x944a8) + 0x944a0;   /* remap base */
        u12 = u13 + 0x4000;
        if ((u13 + bootkc_rs_size - bootkc_rs_base) >> 14 == 0) {
            sptm_panic("s: BootKC_rs region does not fit");
        }
        if ((u12 & 0x3fff) != 0) {
            sptm_panic("s: xnu ro pagetables don't begin aligned");
        }
        if ((bootkc_rs_size & 0x3fff) != 0) {
            sptm_panic("s: xnu ro pagetables don't end aligned");
        }
        sptm_install_boot_vectors(u12);            /* thunk_FUN_000abb60 */
        *(uintptr_t *)0x95468 = u12 + 8;
        *(uintptr_t *)0x95bf0 = u12 + 0x10;
        *(uintptr_t *)0x95cf8 = u12;
    }

    /* Boot-region contiguity validation over the 16 named regions. */
    {
        static const char *const regions[16] = {
            "TXM_ro", "TXM_rx", "TXM_bx", "TXM_rw", "TXM_le",
            "BootKC_ro", "BootKC_rs", "BootKC_rx", "BootKC_bx", "BootKC_rw",
            "BootKC_le", "AuxKC_ro", "AuxKC_rx", "AuxKC_rw", "AuxKC_le",
            "SPTM_ro",
        };
        const char *prev = NULL;
        uintptr_t prev_end = 0;
        int i;
        for (i = 0; i < 16; i++) {
            long *r = sptm_boot_region(regions[i], 1);
            if (r == NULL) {
                /* optional region */
                if (i % 2 == 0) {
                    sptm_panic("s: init get image region returned NULL");
                }
                continue;
            }
            {
                uintptr_t base = (uintptr_t)r[0];
                uintptr_t end = (uintptr_t)r[1] + base;
                if (base - 1 > 0xfffffffffffffffd ||
                    end - 1 > 0xfffffffffffffffd) {
                    sptm_panic("s: region %s beginning %p out of range");
                }
                if (prev != NULL && base != prev_end) {
                    sptm_panic("s: region %s %p %p not immediate");
                }
                prev = regions[i];
                prev_end = end;
            }
        }
    }

    /* Map each boot region into the PAPT with its FTE type/protection. */
    sptm_map_boot_region("DeviceTree", 2, 0, 0, 0x20);   /* filled below */
    sptm_map_boot_region("SPTM_ro", 2, 0, 0, 0x28);
    sptm_map_boot_region("SPTM_rx", 4, 0, 0, 0x121);
    sptm_map_boot_region("SPTM_rw", 2, 0, 0, 0x21);
    sptm_map_boot_region("SPTM_le", 2, 0, 0, 0x21);
    sptm_map_boot_region("TXM_ro", 0x2b, 0, 0, 0x48);
    sptm_map_boot_region("TXM_rx", 0x2b, 0, 0, 0x141);
    sptm_map_boot_region("TXM_bx", 5, 0, 0, 0x141);
    sptm_map_boot_region("TXM_rw", 0x2b, 0, 0, 0x41);
    sptm_map_boot_region("TXM_le", 0x2b, 0, 0, 0x41);
    sptm_map_boot_region("BootKC_ro", 0x23, 0, 0, 0x48);
    sptm_map_boot_region("BootKC_rs", 2, 0, 0, 0x41);
    sptm_map_boot_region("BootKC_rx", 0x23, 0, 0, 0x141);
    sptm_map_boot_region("BootKC_bx", *(uint8_t *)0x94482, 0, 0, 0x141);
    sptm_map_boot_region("BootKC_rw", 0x23, 0, 0, 0x51);
    sptm_map_boot_region("BootKC_le", 0x23, 0, 0, 0x51);

    /* AuxKC / CL4 / misc memory-map entries from the DT memory-map node. */
    {
        uintptr_t mm = 0x94938;
        (void)mm;
        sptm_map_boot_region("AuxKC_rw", 0x23, 0, 0, 0x43);
        sptm_map_boot_region("AuxKC_ro", 0x23, 0, 0, 0x43);
        sptm_map_boot_region("AuxKC_rx", 0x23, 0, 0, 0x43);
        sptm_map_boot_region("AuxKC_le", 0x23, 0, 0, 0x53);
        sptm_map_boot_region("TrustCache", 0, 0, 0, 0x40);
        sptm_map_boot_region("CL4_rx", 0x3e, 0, 0, 6);
        sptm_map_boot_region("CL4_ro", 0x3e, 0, 0, 6);
        sptm_map_boot_region("CL4_rw", 0x3e, 0, 0, 6);
        sptm_map_boot_region("CL4_le", 0x3e, 0, 0, 6);
        sptm_map_boot_region("CL4_dummypage", 0x3e, 0, 0, 6);
        sptm_map_boot_region("RAMDisk", 0x23, 0, 0, 2);
        sptm_map_boot_region("RTBuddySeg", 0x23, 0, 0, 2);
        sptm_map_boot_region("SEPFW", 0xb, 0, 0, 2);
        sptm_map_boot_region("SEPPatches", 0xb, 0, 0, 2);
        sptm_map_boot_region("uStuff", 0xb, 0, 0, 2);
        sptm_map_boot_region("preoslog", 0x23, 0, 0, 2);
        sptm_map_boot_region("BootArgs", 0x23, 0, 0, 0);
        sptm_map_boot_region("SPTMDebug", 2, 0, 0, 2);
        sptm_map_boot_region("ExclaveOSIntegrityCatalog", 0x3e, 0, 0, 6);
        sptm_map_boot_region("ExclaveOSTrustCache", 0x3e, 0, 0, 6);
    }

    /* Record region end addresses for XNU/TXM/BootKC/CL4/SPTM segments. */
    {
        long *r;
        r = sptm_boot_region("BootKC_bx", 1);
        *(uintptr_t *)0x94aa8 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("CL4_rx", 1);
        *(uintptr_t *)0x94a50 = (uintptr_t)r[0];
        r = sptm_boot_region("SPTM_rx", 1);
        *(uintptr_t *)0x94a58 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("TXM_ro", 1);
        *(uintptr_t *)0x94a60 = (uintptr_t)r[0];
        r = sptm_boot_region("BootKC_rs", 1);
        *(uintptr_t *)0x94a68 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("SPTM_rx", 1);
        *(uintptr_t *)0x94a70 = (uintptr_t)r[0];
        r = sptm_boot_region("SPTM_rx", 1);
        *(uintptr_t *)0x94a78 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("CL4_dummypage", 1);
        *(uintptr_t *)0x94a80 = (uintptr_t)r[0];
        r = sptm_boot_region("CL4_dummypage", 1);
        *(uintptr_t *)0x94a88 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("TXM_rx", 1);
        *(uintptr_t *)0x94a90 = (uintptr_t)r[0];
        r = sptm_boot_region("TXM_bx", 1);
        *(uintptr_t *)0x94a98 = (uintptr_t)r[0] + r[1] + -1;
        r = sptm_boot_region("BootKC_rx", 1);
        *(uintptr_t *)0x94aa0 = (uintptr_t)r[0];
    }
    sptm_dbg_init();                       /* FUN_000c172c */

    /* Determine the AVAILABLE region end and map it. */
    l26 = 0x944b8;
    l25 = 0x944b0;
    l15 = 0x944a8;
    *(uintptr_t *)0x100728 = 0x944b8;      /* DAT_00100728 */
    *(uint8_t *)0x94481 = 0;

    /* /chosen dram-size → DRAM window + MTE tag base. */
    chosen = 0;
    if (sptm_dt_find_node((uintptr_t)sptm_dt_state, 0, "chosen", &chosen) != 1) {
        sptm_panic("s: Error looking up 'chosen'");
    }
    prop_val = 0;
    prop_size = 0;
    if (sptm_dt_get_prop(chosen, "dram-size", &prop_val, &prop_size,
            sptm_dt_state[0], sptm_dt_state[1]) != 1) {
        sptm_panic("s: Error looking up 'chosen' dram_size");
    }
    if (prop_val == 0 || prop_size == 0) {
        sptm_panic("s: dram_size %p size mismatch");
    }
    *(uint32_t *)0x952d0 = (uint32_t)(*(uint64_t *)prop_val >> 0x13);
    {
        uint64_t tag_off = sptm_sysreg_read(3, 0, 0xb, 9, 0);   /* TagOffset EL2 */
        uint32_t dram_pages = (uint32_t)(*(uint64_t *)prop_val >> 0x13);
        *(uint64_t *)0x952d8 = tag_off & 0x3fffff00000;
        *(uint64_t *)0x952e0 = (uint64_t)dram_pages * 0x4000 + *(uint64_t *)0x952d8;
        if ((tag_off & 0x7fffffffffffffff) !=
            (0x944a8 + (uint64_t)dram_pages * -0x4000 + 0x944b0 & 0xfffffff00000)) {
            sptm_panic("s: TagOffset EL2 mismatch expected");
        }
        if ((int64_t)tag_off < 0) {
            sptm_panic("s: TagOffset EL2 %p not locked");
        }
    }
    sptm_map_boot_region("AVAILABLE", 0, 0x100728,
        (uintptr_t)((uint64_t)((l25 - l26) + l15 + 0x3fff) >> 14) - *(uint32_t *)0x952d0,
        0x80);
    {
        long *r = sptm_boot_region("TXM_ro", 1);
        sptm_map_boot_region("PHYS_SLIDE", 0x23, 0x944a8,
            (((uintptr_t)r[0] - 0x944a8) + 0x3fff) >> 14, 0);
    }
    if ((*(uint8_t *)0x94481 & 1) == 0) {
        sptm_map_boot_region("MTE_TAG_STORAGE", 0x20, *(uint64_t *)0x952d8,
            *(uint32_t *)0x952d0, 0);
    }

    /* EL2 MMU/state init, feature detection, dispatch registration. */
    stage = sptm_boot_stages | 8;
    sptm_membar_release();
    if ((sptm_boot_stages >> 3 & 1) == 0) {
        sptm_boot_mem_begin();               /* FUN_000d9ec8 */
        sptm_init_el2_pmaps();               /* FUN_000ab7bc */
        sptm_init_el2_state((uint8_t *)0x106180);  /* FUN_000ab8ac */
        if ((sptm_dbg_flag & 1) != 0) {
            sptm_dbg_flag = 0;
        }
        sptm_init_sched((uint8_t *)0x106180);      /* FUN_000baa60 */
        {
            uint64_t pfr1 = sptm_sysreg_read(3, 0, 0, 4, 1);   /* id_aa64pfr1_el1 */
            uint64_t pfr0 = sptm_sysreg_read(3, 0, 0, 4, 0);   /* id_aa64pfr0_el1 */
            uint64_t mmfr1 = sptm_sysreg_read(3, 0, 0, 4, 5);  /* id_aa64mmfr1_el1 */
            if ((pfr1 & 0xf00000000) == 0x200000000 ||
                (pfr0 & 0xf00000000000000) == 0x200000000000000) {
                *(uint8_t *)0x95d01 = 1;
            }
            *(uint8_t *)0x95d02 = (mmfr1 & 0xf0000000000) != 0;
        }
        {
            long *r = sptm_boot_region("slide", 1);
            *(uintptr_t *)0x94988 = (uintptr_t)r[0];
        }
        *(uintptr_t *)0x94980 = (uintptr_t)0 + (0x944a8 - 0x944a0); /* __text + slide */
        sptm_finalize_hib();               /* FUN_000c1ab0 */
        *(uint8_t *)0x106181 = 1;
        sptm_finalize_el2_mmu(0x944a8, 0x944b0, 0x94ab8, 0, 0);   /* FUN_000dcf80 */
        *(uintptr_t *)0x100728 = 0x95d18 + (uintptr_t)(uint32_t)(0x950e8 + 0x950e4) * 0x4000;

        /* Compute XNU/TXM/BootKC entry-point slide deltas. */
        {
            long *r;
            r = sptm_boot_region("CL4_entry", 1);
            l15 = (uintptr_t)r[0];
            r = sptm_boot_region("CL4_rx", 1);
            l25 = (uintptr_t)r[0];
            r = sptm_boot_region("CL4_virt", 1);
            *(uintptr_t *)0x94920 = (l25 + l15) - (uintptr_t)r[0];
        }
        {
            long *r;
            r = sptm_boot_region("TXM_entry", 1);
            l25 = (uintptr_t)r[0];
            r = sptm_boot_region("TXM_ro", 1);
            l15 = sptm_dt_segment_lookup((uintptr_t)r[0]);      /* FUN_000d81bc */
            r = sptm_boot_region("TXM_virt", 1);
            *(uintptr_t *)0x94928 = (l15 + l25) - (uintptr_t)r[0];
        }
        {
            long *r;
            r = sptm_boot_region("BootKC_entry", 1);
            l25 = (uintptr_t)r[0];
            r = sptm_boot_region("BootKC_ro", 1);
            l15 = sptm_dt_segment_lookup((uintptr_t)r[0]);      /* FUN_000d81bc */
            r = sptm_boot_region("BootKC_virt", 1);
            *(uintptr_t *)0x94930 = (l15 + l25) - (uintptr_t)r[0];
        }

        /* Register the guarded dispatch tables for XNU/TXM/SK/HIB. */
        sptm_register_dispatch_table(0, (uintptr_t)&sptm_dispatch, 2);
        sptm_register_dispatch_table(1, (uintptr_t)&sptm_dispatch, 4);
        sptm_register_dispatch_table(2, (uintptr_t)&sptm_dispatch, 8);
        if ((0x100e00 & 1) != 0) {
            sptm_register_dispatch_table(10, (uintptr_t)&sptm_dispatch, 0x10);
        }

        /* Launch SK and/or TXM (never returns once booted). */
        stage = sptm_boot_stages | 0x40000;
        sptm_membar_release();
        if ((sptm_boot_stages >> 0x12 & 1) == 0) {
            bool exclaves;
            chosen = 0;
            if (sptm_dt_find_node((uintptr_t)sptm_dt_state, 0, "product", &chosen) != 1) {
                sptm_panic("s: Error looking up 'product'");
            }
            prop_val = 0;
            if (sptm_dt_get_prop(chosen, "exclaves_enabled", &prop_val, &prop_size,
                    sptm_dt_state[0], sptm_dt_state[1]) == 1 &&
                *(uintptr_t *)0x94920 != (uintptr_t)-1) {
                exclaves = (*(uint32_t *)prop_val) != 0;
                *(uint8_t *)0x94480 = exclaves;
                if (exclaves) {
                    sptm_dbg_print("Starting SK");        /* s_Starting_SK__ */
                    sptm_start_sk((uintptr_t *)0x94360);
                    sptm_txm_handoff((uint8_t *)0x94360, NULL);
                    sptm_enter_domain(0, NULL, NULL, NULL, 0);   /* FUN_000a11e0 */
                    sptm_brk_jump(0xba924);              /* never returns */
                }
            } else {
                *(uint8_t *)0x94480 = 0;
            }
            sptm_dispatch_engine_init();                  /* FUN_000b8230 */
            sptm_dbg_print("Starting TXM");               /* s_Starting_TXM__ */
            sptm_start_txm((uintptr_t *)0x100108);
            sptm_enter_domain(0, NULL, NULL, NULL, 0);    /* FUN_000a10e0 */
            sptm_brk_jump(0xba950);                       /* never returns */
        }
    }
    sptm_panic("s: Attempted to announce bootstrap stage that has already been reached");
}
