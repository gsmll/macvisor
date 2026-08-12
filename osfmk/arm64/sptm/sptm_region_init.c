/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM device-tree (DT) parsing/iteration helpers and the
 * boot-time region-init / handoff helpers that consume them: the flattened DT
 * walker (sptm_dt_*), boot-region lookup, bootstrap-fixup and stage
 * announcements, TXM/SK kernelcache region setup, and the per-level
 * (TXM/SK) bootstrap context construction.
 */
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ */
/* Extern kernel / SPTM helper deps (addresses in comments; other trees) */
/* ------------------------------------------------------------------ */

/* noreturn diagnostics. FUN_000f8834 is the no-argument "bad device-tree"
 * panic; FUN_000f8804 is the printf-style panic printer; FUN_000ae44c is the
 * stack-cookie check failure. */
extern __attribute__((noreturn)) void sptm_panic_bad_dt(void);        /* FUN_000f8834 */
extern __attribute__((noreturn)) void sptm_panic(const char *fmt, ...);/* FUN_000f8804 */
extern __attribute__((noreturn)) void sptm_stack_chk_fail(void);      /* FUN_000ae44c */

/* Sysreg / barrier intrinsics (arm64). */
extern uint64_t sptm_sysreg_read(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2);
extern void sptm_sysreg_write(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2, uint64_t val);
extern void sptm_sysop_write(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2, uint64_t val);  /* SysOp_W */
extern void sptm_dsb(unsigned int level, unsigned int a, unsigned int b); /* DSB */
extern void sptm_isb(void);                                               /* ISB */
extern void sptm_membar_release(void);                                    /* LORelease() release barrier */
extern uintptr_t tpidr_el2;                                               /* per-CPU base */

/* EL1/EL2 system registers rendered as globals by Ghidra. */
extern uint64_t tcr_el1;              /* TCR_EL1 */
extern uint64_t ttbr0_el1;            /* TTBR0_EL1 */
extern uint64_t sctlr_el1;            /* SCTLR_EL1 */
extern uint64_t vbar_el1;             /* VBAR_EL1 */
extern uint64_t midr_el1;             /* MIDR_EL1 */
extern uint64_t currentel;            /* CurrentEL */
extern uint64_t id_aa64pfr0_el1;      /* ID_AA64PFR0_EL1 */
extern uint64_t id_aa64pfr1_el1;      /* ID_AA64PFR1_EL1 */
extern uint64_t id_aa64isar0_el1;     /* ID_AA64ISAR0_EL1 */
extern uint64_t id_aa64isar1_el1;     /* ID_AA64ISAR1_EL1 */

/* Memory/format helpers (other trees). */
extern int sptm_snprintf(void *buf, uint64_t size, uint64_t unused,
    uint64_t limit, const char *fmt, void *ap);                          /* FUN_000ad278 */
extern void sptm_bzero(void *dst, uint64_t n);                            /* FUN_000abb60 */
extern void sptm_save_late_const(uintptr_t pc);                           /* thunk_FUN_000abeb0 */
extern void sptm_install_boot_vectors(uintptr_t base);                    /* thunk_FUN_000abb60 */
extern void sptm_el2_enable(uint64_t selector, uintptr_t ctx);            /* FUN_000ab8dc */
extern void sptm_memmap_available(const char *name, uint32_t a,
    uint32_t b);                                                          /* FUN_000d9be8 */
extern void sptm_hib_teardown_a(uint64_t val);                            /* FUN_000c1b70 */
extern void sptm_hib_teardown_b(void);                                    /* FUN_000c1cc4 */
extern void sptm_txm_handoff(uint8_t *out, uintptr_t *in);                /* FUN_000d8a58 */
extern uintptr_t sptm_va_lookup(uintptr_t pa);                            /* FUN_000e40ec */

/* Claimed by other trees (addresses in comments; names to confirm on link).
 * FUN_000b2620 is the SPTM->TXM guarded call stub; FUN_000bf298 registers a
 * protected region {tag, begin, end}; FUN_000bf4bc commits that region into
 * the page table. */
extern void sptm_txm_enter(uintptr_t fn);                                 /* FUN_000b2620 */
extern void sptm_region_register(uint32_t tag, uintptr_t begin,
    uintptr_t end, uintptr_t *a, uintptr_t *b);                           /* FUN_000bf298 */
extern void sptm_region_commit(uintptr_t *a, uintptr_t *b, uintptr_t *c); /* FUN_000bf4bc */

/* ------------------------------------------------------------------ */
/* SPTM bootstrap globals (DAT_* = bss; see per-field comments)         */
/* ------------------------------------------------------------------ */

/* DAT_00094ab8 — device-tree iteration state: [0]=blob base, [1]=blob size.
 * (defined in sptm_init.c) */
extern uintptr_t sptm_dt_state[2];

/* DAT_001012d8 — SPTM bootstrap-stage bitmask (defined in sptm_init.c). */
extern uint64_t sptm_boot_stages;

/* DAT_00094938 — pointer to the root DT node of the /chosen memory-map
 * ("memory-map") node discovered by sptm_boot_fixups. */
extern uintptr_t sptm_dt_memory_map;

/* DAT_00094500 / DAT_000944f8 — the DT blob's end / base addresses. */
extern uintptr_t sptm_dt_blob_end;   /* DAT_00094500 */
extern uintptr_t sptm_dt_blob_base;  /* DAT_000944f8 */

/* DAT_00094358 — maximum "die-id" seen while iterating /cpus (init_sched). */
extern uint32_t sptm_max_die_id;

/* DAT_00094360..000943a8 — SK bootstrap region globals (sptm_start_sk). */
extern uint64_t sptm_sk_boot0;      /* DAT_00094360 */
extern uint64_t sptm_sk_boot1;      /* DAT_00094368 */
extern uint64_t sptm_sk_boot2;      /* DAT_00094370 */
extern uint64_t sptm_sk_rx;         /* DAT_00094378 */
extern uint64_t sptm_sk_ro;         /* DAT_00094380 */
extern uint64_t sptm_sk_rw;         /* DAT_00094388 */
extern uint64_t sptm_sk_le;         /* DAT_00094390 */
extern uint64_t sptm_dt_devicetree; /* DAT_00094398 */
extern uint64_t sptm_sk_dt_end;     /* DAT_000943a0 */
extern uint64_t sptm_sk_handoff;    /* DAT_000943a8 */

/* Boot flag / memory-attribute constants. */
extern uint32_t sptm_boot_flag_0;   /* DAT_00094480 */
extern uint32_t sptm_boot_flag_1;   /* DAT_00094481 */
extern uint32_t sptm_boot_attr_0;   /* DAT_00094482 */
extern uint32_t sptm_boot_attr_1;   /* DAT_00094483 */

/* Misc region/table bases used to derive handoff VAs. */
extern uint64_t sptm_ro_base;       /* DAT_000944a8 */
extern uint64_t sptm_ro_end;        /* DAT_000944b0 */
extern uint64_t sptm_nc_begin;      /* DAT_00094a50 */
extern uint64_t sptm_nc_end;        /* DAT_00094a58 */
extern uint64_t sptm_nc2_begin;     /* DAT_00094a60 */
extern uint64_t sptm_nc2_end;       /* DAT_00094a68 */
extern uint64_t sptm_nc3_begin;     /* DAT_00094a70 */
extern uint64_t sptm_nc3_end;       /* DAT_00094a78 */
extern uint64_t sptm_nc4_begin;     /* DAT_00094a80 */
extern uint64_t sptm_nc4_end;       /* DAT_00094a88 */
extern uint64_t sptm_nc5_begin;     /* DAT_00094a90 */
extern uint64_t sptm_nc5_end;       /* DAT_00094a98 */
extern uint64_t sptm_nc6_begin;     /* DAT_00094aa0 */
extern uint64_t sptm_nc6_end;       /* DAT_00094aa8 */

/* DT/boot tables and per-CPU records (opaque byte arrays; addresses taken). */
extern uint8_t sptm_boot_root_ft[];   /* DAT_00095d48 — bootstrap root FTE */
extern uint8_t sptm_boot_va_table[];  /* DAT_00095280 */
extern uint8_t sptm_region_table[];   /* DAT_00095d50 */
extern uint8_t sptm_region_a[];       /* DAT_00095d18 */
extern uint8_t sptm_region_b[];       /* DAT_00095d20 */
extern uint8_t sptm_frame_table_a[];  /* DAT_00095118 */
extern uint8_t sptm_frame_table_b[];  /* DAT_00095108 */
extern uint8_t sptm_frame_table_c[];  /* DAT_00095110 */
extern uint8_t sptm_frame_table_d[];  /* DAT_00095178 */
extern uint8_t sptm_frame_table_e[];  /* DAT_00095270 */
extern uint8_t sptm_frame_table_f[];  /* DAT_000950d0 */
extern uint8_t sptm_frame_table_g[];  /* DAT_000950d8 */
extern uint8_t sptm_frame_table_h[];  /* DAT_000950c0 */
extern uint8_t sptm_frame_table_i[];  /* DAT_000950c8 */
extern uint8_t sptm_boot_table_a[];   /* DAT_000952d0 */
extern uint8_t sptm_boot_table_b[];   /* DAT_000952d8 */
extern uint8_t sptm_boot_table_c[];   /* DAT_000952e0 */
extern uint8_t sptm_boot_table_d[];   /* DAT_00095220 */
extern uint8_t sptm_boot_table_e[];   /* DAT_00095180 */
extern uint8_t sptm_boot_table_f[];   /* DAT_000951d0 */
extern uint8_t sptm_percpu_table_a[]; /* DAT_00095440 */
extern uint8_t sptm_percpu_table_b[]; /* DAT_00095444 */
extern uint8_t sptm_percpu_table_c[]; /* DAT_00095448 */
extern uint8_t sptm_percpu_table_d[]; /* DAT_00095450 */
extern uint8_t sptm_percpu_table_e[]; /* DAT_00095460 */
extern uint8_t sptm_boot_fte_alt[];   /* DAT_00095d10 */
extern uint8_t sptm_boot_fte_alt2[];  /* DAT_00095d3c */
extern uint8_t sptm_handoff_region[]; /* DAT_00101ac8: count, then 24-byte entries */
extern uint8_t sptm_cursor_end[];     /* DAT_00101f80 — end cursor */
extern uint8_t sptm_common;           /* __common */
extern uint8_t sptm_debug_a[];        /* DAT_0010000c */
extern uint8_t sptm_debug_b[];        /* DAT_0010000e */
extern uint8_t sptm_hw_table[];       /* DAT_000a5000 */
extern uint8_t sptm_const_table[];    /* DAT_00019c68 */
extern uint8_t sptm_phase_table[];    /* DAT_00012f30 */
extern uint8_t sptm_kc_end[];         /* DAT_00094504 */

/* Per-cpu / bootstrap-state globals. */
extern uintptr_t sptm_cpu_count;      /* DAT_00100728 */
extern uint64_t sptm_dbg_flag;        /* DAT_00100db8 */
extern uint64_t sptm_hib_state;       /* DAT_00100e00 */
extern uint64_t sptm_boot_flag_cfg;   /* DAT_00100df8 */
extern uintptr_t sptm_dt_end_cur;     /* DAT_001012e8 */
extern uintptr_t sptm_percpu_frames;  /* DAT_00095168 (via frame base) */
extern uintptr_t sptm_fte_end;        /* DAT_00095cf8 */
extern uint32_t sptm_hib_opt;         /* DAT_000950dc */

/* Trace / HIB setup scratch. */
extern uintptr_t sptm_trace_r0;       /* DAT_00100f50 */
extern uintptr_t sptm_trace_r1;       /* DAT_00100f58 */
extern uintptr_t sptm_trace_r2;       /* DAT_00100f60 */
extern uintptr_t sptm_trace_r3;       /* DAT_00100f68 */
extern uintptr_t sptm_trace_r4;       /* DAT_00100f70 */
extern uintptr_t sptm_trace_r5;       /* DAT_00100f78 */
extern uintptr_t sptm_trace_buf;      /* DAT_00100fe0 */
extern uintptr_t sptm_trace_cpu;      /* DAT_00100c50 */
extern uintptr_t sptm_trace_cpu1;     /* DAT_00100c58 */
extern uintptr_t sptm_trace_cpu2;     /* DAT_00100c60 */
extern uintptr_t sptm_trace_cpu3;     /* DAT_00100c68 */
extern uintptr_t sptm_trace_cpu4;     /* DAT_00100c70 */
extern uintptr_t sptm_trace_cpu5;     /* DAT_00100c78 */
extern uintptr_t sptm_trace_tbl;      /* DAT_00100fb0 */
extern uintptr_t sptm_trace_cfg;      /* DAT_00100e08 */
extern uintptr_t sptm_obj;            /* DAT_00104120 (driver object w/ vtable) */
extern uintptr_t sptm_obj_args;       /* DAT_001040b0 */
extern uintptr_t sptm_kc_r0;          /* DAT_00101010 */
extern uintptr_t sptm_kc_r1;          /* DAT_00101018 */
extern uintptr_t sptm_kc_r2;          /* DAT_00101020 */
extern uintptr_t sptm_kc_r3;          /* DAT_00101028 */
extern uintptr_t sptm_kc_r4;          /* DAT_00101030 */
extern uintptr_t sptm_kc_r5;          /* DAT_00101038 */
extern uintptr_t sptm_kc_c0;          /* DAT_00100c80 */
extern uintptr_t sptm_kc_c1;          /* DAT_00100c88 */
extern uintptr_t sptm_kc_c2;          /* DAT_00100c90 */
extern uintptr_t sptm_kc_c3;          /* DAT_00100c98 */
extern uintptr_t sptm_kc_c4;          /* DAT_00100ca0 */
extern uintptr_t sptm_kc_c5;          /* DAT_00100ca8 */

/* ------------------------------------------------------------------ */
/* TXM / SK handoff context blocks (opaque bootstrap structs).         */
/* ------------------------------------------------------------------ */

/* TXM bootstrap context (base DAT_00100100). Fields written by sptm_start_txm. */
typedef struct {
    uint64_t reserved_000;      /* +0x000 (DAT_00100100) */
    uint64_t dispatch_fn;       /* +0x008 (DAT_00100108) — per-CPU +0xa58 */
    uint64_t count;             /* +0x010 (DAT_00100110) */
    uint32_t fte_class;         /* +0x014 (DAT_00100114) */
    uint32_t pad_018;
    uint64_t dt_begin;          /* +0x018 (DAT_00100118) */
    uint64_t dt_end;            /* +0x020 (DAT_00100120) */
    uint64_t id_pfr0;           /* +0x028 (DAT_00100128) */
    uint64_t id_pfr1;           /* +0x030 (DAT_00100130) */
    uint64_t num_cpus;          /* +0x038 (DAT_00100138) */
    uint64_t root_ft;           /* +0x040 (DAT_00100140) */
    uint64_t va_table;          /* +0x048 (DAT_00100148) */
    uint64_t phase;             /* +0x050 (DAT_00100150) */
    uint64_t reserved_058;      /* +0x058 (DAT_00100158) */
    uint64_t kc_end;            /* +0x060 (DAT_00100160) */
    uint64_t common;            /* +0x068 (DAT_00100168) */
    uint64_t count2;            /* +0x070 (DAT_00100170) */
    uint64_t region_count;      /* +0x078 (DAT_00100178) */
    uint64_t region_base;       /* +0x080 (DAT_00100180) */
    uint64_t region_a;          /* +0x088 (DAT_00100188) */
    uint64_t region_b;          /* +0x090 (DAT_00100190) */
    uint64_t frame_table;       /* +0x098 (DAT_00100198) */
    uint64_t cursor_end;        /* +0x0a0 (DAT_001001a0) */
    uint64_t root_ft2;          /* +0x0a8 (DAT_001001a8) */
    uint64_t percpu_table;      /* +0x0b0 (DAT_001001b0) */
    uint64_t fte_class_tbl;     /* +0x0b8 (DAT_001001b8) */
    uint64_t const_table;       /* +0x0c0 (DAT_001001c0) */
    uint64_t flags_c8;          /* +0x0c8 (DAT_001001c8) */
    uint64_t percpu_a;          /* +0x0d0 (DAT_001001d0) */
    uint64_t percpu_b;          /* +0x0d8 (DAT_001001d8) */
    uint64_t boot_a;            /* +0x0e0 (DAT_001001e0) */
    uint64_t boot_b;            /* +0x0e8 (DAT_001001e8) */
    uint64_t debug_a;           /* +0x0f0 (DAT_001001f0) */
    uint64_t boot_table;        /* +0x100 (DAT_00100200) */
    uint64_t boot_table_cnt;    /* +0x108 (DAT_00100208) */
    uint64_t boot_table_ptr;    /* +0x110 (DAT_00100210) */
    uint64_t flags_118;         /* +0x118 (DAT_00100218) */
    uint64_t percpu_c;          /* +0x120 (DAT_00100220) */
    uint64_t percpu_d;          /* +0x128 (DAT_00100228) */
    uint64_t frame_f;           /* +0x130 (DAT_00100230) */
    uint64_t frame_g;           /* +0x138 (DAT_00100238) */
    uint64_t debug_b;           /* +0x140 (DAT_00100240) */
    uint64_t boot_table_e;      /* +0x148 (DAT_00100248) */
    uint64_t id_isar0;          /* +0x1a8 (DAT_001002a8) */
    uint64_t id_isar1;          /* +0x1b0 (DAT_001002b0) */
    uint64_t cache_line;        /* +0x1b8 (DAT_001002b8) */
    uint64_t hib_opt;           /* +0x4d0 (DAT_001005d0) */
} sptm_txm_context_t;
extern sptm_txm_context_t sptm_txm_context;   /* base DAT_00100100 */

/* SK bootstrap context (base DAT_001002c0). Fields written by sptm_start_sk_ctx. */
typedef struct {
    uint64_t handoff_magic;     /* +0x000 (DAT_001002c0) — per-CPU +0x15b0 */
    uint64_t frame_table;       /* +0x008 (DAT_001002c8) */
    uint64_t dt_begin;          /* +0x010 (DAT_001002d0) */
    uint64_t num_cpus;          /* +0x018 (DAT_001002d8) */
    uint64_t va_base;           /* +0x020 (DAT_001002e0) — translated DT base */
    uint64_t txm_ro_va;         /* +0x028 (DAT_001002e8) */
    uint64_t va_table;          /* +0x030 (DAT_001002f0) */
    uint64_t count;             /* +0x038 (DAT_001002f8) */
    uint64_t frame_d;           /* +0x040 (DAT_00100300) */
    uint64_t frame_e;           /* +0x048 (DAT_00100308) */
    uint64_t bootkc_ro_va;      /* +0x050 (DAT_00100310) */
    uint64_t bootkc_le_va;      /* +0x058 (DAT_00100318) */
    uint64_t hw_table;          /* +0x060 (DAT_00100320) */
    uint64_t fte_class;         /* +0x068 (DAT_00100328) */
    uint64_t kc_rw_va;          /* +0x2e8 (DAT_001005a8) */
    uint64_t kc_ro_va;          /* +0x2f0 (DAT_001005b0) */
    uint64_t kc_le_va;          /* +0x2f8 (DAT_001005b8) */
    uint64_t hib_state_ptr;     /* +0x318 (DAT_001005d8) */
    uint64_t mem_map;           /* +0x320 (DAT_001005e0) */
    uint64_t frame_f;           /* +0x328 (DAT_001005e8) */
    uint64_t frame_g;           /* +0x330 (DAT_001005f0) */
    uint64_t frame_h;           /* +0x338 (DAT_001005f8) */
    uint64_t frame_i;           /* +0x340 (DAT_00100600) */
    uint64_t boot_flag;         /* +0x180 (DAT_00100440) */
    uint64_t count2;            /* +0x1a0 (DAT_00100460) */
    uint64_t region_count;      /* +0x1a8 (DAT_00100468) */
    uint64_t region_base;       /* +0x1b0 (DAT_00100470) */
    uint64_t region_a;          /* +0x1b8 (DAT_00100478) */
    uint64_t region_b;          /* +0x1c0 (DAT_00100480) */
    uint64_t frame_table2;      /* +0x1c8 (DAT_00100488) */
    uint64_t cursor_end;        /* +0x1d0 (DAT_00100490) */
    uint64_t root_ft;           /* +0x1d8 (DAT_00100498) */
    uint64_t percpu_table;      /* +0x1e0 (DAT_001004a0) */
    uint64_t fte_class_tbl;     /* +0x1e8 (DAT_001004a8) */
    uint64_t const_table;       /* +0x1f0 (DAT_001004b0) */
    uint64_t flags_1f8;         /* +0x1f8 (DAT_001004b8) */
    uint64_t percpu_a;          /* +0x200 (DAT_001004c0) */
    uint64_t percpu_b;          /* +0x208 (DAT_001004c8) */
    uint64_t boot_a;            /* +0x210 (DAT_001004d0) */
    uint64_t boot_b;            /* +0x218 (DAT_001004d8) */
    uint64_t debug_a;           /* +0x220 (DAT_001004e0) */
    uint64_t boot_table;        /* +0x230 (DAT_001004f0) */
    uint64_t boot_table_cnt;    /* +0x238 (DAT_001004f8) */
    uint64_t boot_table_ptr;    /* +0x240 (DAT_00100500) */
    uint64_t flags_248;         /* +0x248 (DAT_00100508) */
    uint64_t percpu_c;          /* +0x250 (DAT_00100510) */
    uint64_t percpu_d;          /* +0x258 (DAT_00100518) */
    uint64_t frame_f2;          /* +0x260 (DAT_00100520) */
    uint64_t frame_g2;          /* +0x268 (DAT_00100528) */
    uint64_t debug_b;           /* +0x270 (DAT_00100530) */
    uint64_t boot_table_e;      /* +0x278 (DAT_00100538) */
    uint64_t common;            /* +0x198 (DAT_00100458) */
    uint64_t boot_a2;           /* +0x2d8 (DAT_00100598) */
    uint64_t boot_b2;           /* +0x2e0 (DAT_001005a0) */
    uint64_t hib_opt;           /* +0x308 (DAT_001005c8) */
    uint64_t flags_348;         /* +0x348 (DAT_00100608) */
} sptm_sk_context_t;
extern sptm_sk_context_t sptm_sk_context;    /* base DAT_001002c0 */

/* ------------------------------------------------------------------ */
/* DT node / property format                                           */
/*                                                                     */
/* A flattened DT blob is {base, size}. A node is:                     */
/*   u32 num_props; u32 num_children;                                  */
/*   prop_t props[num_props];                                          */
/*   node_t  children[num_children];                                   */
/* where prop_t = { char name[32]; u32 size; u8 value[size]; }         */
/*   aligned up to 4 (entry stride = align4(36 + size)).               */
/* The child area begins immediately after the last property.          */
/* ------------------------------------------------------------------ */

/* Advance a property cursor to the next property in the node. */
static inline uint8_t *
sptm_dt_prop_next(uint8_t *prop)
{
    uint32_t size = *(uint32_t *)(prop + 32);
    return (uint8_t *)(((uintptr_t)prop + size + 0x27) & ~(uintptr_t)3);
}

/* ------------------------------------------------------------------ */
/* sptm_dt_get_prop                                                    */
/* ------------------------------------------------------------------ */
/* FUN_000b7c04 @ 0x000b7c04   (sptm_dt_get_prop)
 * Ghidra: int * FUN_000b7c04(int *node, char *name, ulong *out_val,
 *        uint *out_size, int *base, long size)
 * Search a DT node's property array for a property named `name`; on a match
 * store the value pointer into *out_val and its byte size into *out_size.
 * Returns 1 on match, -1 if the node has no properties / no match, and panics
 * (sptm_panic_bad_dt) on any out-of-bounds walk of the blob.
 * Confidence: high
 * Notes: property layout {name[32]; u32 size; value[]}; bound-checks every
 *   step against the blob {base,size} window before dereference. */
int
sptm_dt_get_prop(uintptr_t node, const char *name, uintptr_t *out_val,
    uint32_t *out_size, uintptr_t blob_base, uintptr_t blob_end)
{
    uint8_t *base = (uint8_t *)blob_base;
    uint8_t *end = (uint8_t *)blob_end;
    uint8_t *prop;
    uint32_t num_props, i;
    uint32_t size;
    uint8_t *val;
    const uint8_t *p, *q;

    if (node == 0)
        return -1;
    prop = (uint8_t *)node + 8;
    if (prop < base || end < prop)
        sptm_panic_bad_dt();
    num_props = *(uint32_t *)node;
    if (num_props == 0)
        return -1;
    for (i = 0; ; i++) {
        if (prop < base || end < prop || prop + 36 < base || end < prop + 36)
            sptm_panic_bad_dt();
        val = prop + 36;
        size = *(uint32_t *)(prop + 32);
        /* compare the property name field against `name` */
        for (p = prop, q = (const uint8_t *)name; ; p++, q++) {
            uint8_t c = *p;
            if (c != *q)
                break;
            if (c == '\0') {
                *out_val = (uintptr_t)val;
                *out_size = size;
                return 1;
            }
        }
        /* value range must lie inside the blob, else this is a malformed DT */
        if ((uintptr_t)val + size < blob_base || blob_end < (uintptr_t)val + size)
            sptm_panic_bad_dt();
        prop = sptm_dt_prop_next(prop);
        if (i + 1 == num_props)
            return -1;
    }
}

/* ------------------------------------------------------------------ */
/* sptm_dt_next_sibling                                                */
/* ------------------------------------------------------------------ */
/* FUN_000b7cfc @ 0x000b7cfc   (sptm_dt_next_sibling)
 * Ghidra: int * FUN_000b7cfc(ulong *root, int *node)
 * Return the address just past `node`'s entire subtree (properties plus all
 * child subtrees) — i.e. the pointer to `node`'s next sibling in a DT blob.
 * Returns 0 for an empty node. Panics on an out-of-bounds walk.
 * Confidence: high
 * Notes: recurses once per child to skip each child subtree; node[0]=num_props
 *   and node[1]=num_children drive the walk. */
uintptr_t
sptm_dt_next_sibling(uintptr_t root, uintptr_t node_arg)
{
    uint8_t *base = (uint8_t *)root;
    uint8_t *end = base + ((uint64_t *)root)[1];
    uint8_t *node = (uint8_t *)node_arg;
    uint8_t *p = node + 8;
    uint32_t num_props, num_children, i;

    if (p < base || end < p)
        sptm_panic_bad_dt();
    if (node == 0 || *(uint32_t *)node == 0)
        return 0;
    num_props = *(uint32_t *)node;
    for (i = 0; i < num_props; i++)
        p = sptm_dt_prop_next(p);
    num_children = *(uint32_t *)(node + 4);
    if (num_children != 0) {
        for (i = 0; i < num_children; i++)
            p = (uint8_t *)sptm_dt_next_sibling(root, (uintptr_t)p);
    }
    return (uintptr_t)p;
}

/* ------------------------------------------------------------------ */
/* sptm_dt_iterate                                                     */
/* ------------------------------------------------------------------ */
/* FUN_000b7dc8 @ 0x000b7dc8   (sptm_dt_iterate)
 * Ghidra: undefined8 FUN_000b7dc8(ulong *root, long iter, undefined8 *out)
 * Depth-first iterator over the children of the node recorded in `iter`.
 * `iter` holds { +0x08: parent node, +0x10: current node, +0x20: index }.
 * Yields one child node per call into *out; returns 1 while children remain,
 * 0 when exhausted. Panics on an out-of-bounds child pointer.
 * Confidence: high
 * Notes: index 0 walks the parent's properties to find the first child;
 *   subsequent calls advance via sptm_dt_next_sibling. */
typedef struct {
    uintptr_t parent;   /* +0x08 */
    uintptr_t current;  /* +0x10 */
    uint32_t  index;    /* +0x20 */
} sptm_dt_iter_t;

int
sptm_dt_iterate(uintptr_t root, sptm_dt_iter_t *iter, uintptr_t *out_node)
{
    uint8_t *base = (uint8_t *)root;
    uint8_t *end = base + ((uint64_t *)root)[1];
    uint32_t idx = iter->index;
    uint8_t *parent = (uint8_t *)iter->parent;
    uint8_t *node;
    uint32_t num_children = *(uint32_t *)(parent + 4);

    if (idx < num_children) {
        iter->index = idx + 1;
        if (idx == 0) {
            uint32_t num_props = *(uint32_t *)parent;
            if (num_props == 0) {
                iter->current = 0;
            } else {
                uint8_t *p = parent + 8;
                uint32_t i;
                for (i = 0; i < num_props; i++)
                    p = sptm_dt_prop_next(p);
                iter->current = (uintptr_t)p;
            }
            node = (uint8_t *)iter->current;
        } else {
            node = (uint8_t *)sptm_dt_next_sibling(root, iter->current);
            iter->current = (uintptr_t)node;
        }
        if (node < base || end < node)
            sptm_panic_bad_dt();
        *out_node = (uintptr_t)node;
        return 1;
    }
    *out_node = 0;
    return 0;
}

/* ------------------------------------------------------------------ */
/* sptm_dt_find_node                                                   */
/* ------------------------------------------------------------------ */
/* FUN_000b79e8 @ 0x000b79e8   (sptm_dt_find_node)
 * Ghidra: undefined FUN_000b79e8(ulong *root, int *parent, char *path,
 *        ulong *out)
 * Resolve a slash-separated path of node names relative to `parent` (or the
 * blob root if parent is null) against the DT. Each component is matched
 * against the children's "name" property. "/" returns `parent` itself.
 * Writes the resolved node pointer to *out; returns 1 on success, -1 on
 * failure. Panics on an out-of-bounds walk.
 * Confidence: high
 * Notes: component buffer is 64 bytes (truncated at 0x3f); child discovery
 *   uses sptm_dt_get_prop(child, "name") + sptm_dt_next_sibling. */
int
sptm_dt_find_node(uintptr_t root, uintptr_t parent, const char *path,
    uintptr_t *out)
{
    uint8_t *base = (uint8_t *)root;
    uint8_t *end = base + ((uint64_t *)root)[1];
    uint8_t *node = (uint8_t *)parent;
    const char *p = path;
    uint8_t component[64];

    if (root == 0)
        return -1;
    if (node == 0)
        node = base;
    if (node < base || end < node)
        sptm_panic_bad_dt();
    if (*p == '/') {
        p++;
        if (*p == '\0') {
            *out = (uintptr_t)node;
            return 1;
        }
    }
    for (;;) {
        uint8_t *dst = component;
        uint32_t num_children, num_props, i;

        /* parse the next path component (up to 63 bytes) */
        for (;;) {
            char c = *p;
            if (c == '\0')
                break;
            if (c == '/') {
                p++;
                break;
            }
            if (dst - component == 0x3f) {
                dst = component;
                break;
            }
            *dst++ = (uint8_t)c;
            p++;
        }
        *dst = '\0';
        if (component[0] == '\0') {
            if (*p == '\0') {
                *out = (uintptr_t)node;
                return 1;
            }
            return -1;
        }
        num_children = *(uint32_t *)(node + 4);
        if (num_children != 0) {
            uint8_t *child;
            uintptr_t name_val = 0;
            uint32_t name_size = 0;
            int rc;

            /* first child = end of this node's property array */
            num_props = *(uint32_t *)node;
            child = node + 8;
            if (child < base || end < child)
                sptm_panic_bad_dt();
            for (i = 0; i < num_props; i++)
                child = sptm_dt_prop_next(child);

            for (i = 1; ; i++) {
                rc = sptm_dt_get_prop((uintptr_t)child, "name", &name_val,
                    &name_size, (uintptr_t)base, (uintptr_t)end);
                if (rc == 1 &&
                    strcmp((const char *)name_val, (const char *)component) == 0) {
                    node = child;
                    if (child == 0)
                        return -1;
                    break;          /* descend into this child, next component */
                }
                if (num_children <= i)
                    return -1;
                child = (uint8_t *)sptm_dt_next_sibling(root, (uintptr_t)child);
            }
        } else {
            return -1;
        }
    }
}

/* ------------------------------------------------------------------ */
/* sptm_dt_find_by_name_recursive                                      */
/* ------------------------------------------------------------------ */
/* FUN_000b7898 @ 0x000b7898   (sptm_dt_find_by_name_recursive)
 * Ghidra: undefined8 FUN_000b7898(ulong *root, ulong *parent, ulong *out)
 * Recursive depth-first search over a DT subtree for a node whose "name"
 * property value equals "arm-io". `parent` is a cursor (its [0] holds the
 * current parent node and is advanced as the walk descends). On a hit writes
 * the matching node to *out and returns 1, else returns -1. Panics on an
 * out-of-bounds walk.
 * Confidence: medium
 * Notes: the match test is property name == "name" && value == "arm-io"
 *   (DAT_00007790 / DAT_0000e72c). */
int
sptm_dt_find_by_name_recursive(uintptr_t root, uintptr_t *parent_ptr,
    uintptr_t *out_node)
{
    uint8_t *base = (uint8_t *)root;
    uint8_t *end = base + ((uint64_t *)root)[1];
    uint8_t *parent = (uint8_t *)*parent_ptr;
    uint8_t *p = parent + 8;
    uint32_t num_props, num_children, i;
    int rc;

    if (p < base || end < p)
        sptm_panic_bad_dt();
    num_props = *(uint32_t *)parent;
    if (num_props != 0) {
        *parent_ptr = (uintptr_t)p;
        for (i = 0; ; i++) {
            uint32_t size;
            uint8_t *next;
            if (p < base || end < p)
                sptm_panic_bad_dt();
            size = *(uint32_t *)(p + 32);
            next = p + 36 + ((size + 3) & ~3u);
            *parent_ptr = (uintptr_t)next;
            /* property named "name"? */
            if (strcmp((const char *)p, "name") == 0 &&
                strcmp((const char *)(p + 36), "arm-io") == 0) {
                if (parent < base || end < parent)
                    sptm_panic_bad_dt();
                *out_node = (uintptr_t)parent;
                return 1;
            }
            p = next;
            if (i + 1 == num_props)
                break;
        }
        num_children = *(uint32_t *)(parent + 4);
        if (num_children != 0) {
            for (i = 0; i < num_children; i++) {
                rc = sptm_dt_find_by_name_recursive(root, parent_ptr, out_node);
                if (rc == 1)
                    return rc;
            }
            return -1;
        }
    }
    return -1;
}

/* ------------------------------------------------------------------ */
/* sptm_dt_snprintf                                                    */
/* ------------------------------------------------------------------ */
/* FUN_000b7748 @ 0x000b7748   (sptm_dt_snprintf)
 * Ghidra: void FUN_000b7748(undefined8 buf, undefined8 a, undefined8 b,
 *        undefined8 fmt)
 * Thin snprintf wrapper: formats `fmt` into `buf` with a hard 0x20-byte size
 * and limit guard. Arguments `a`/`b` are unused (only the 0x20 literals are
 * forwarded). Used to build fixed-size DT node-name strings.
 * Confidence: low
 * Notes: forwards to sptm_snprintf(FUN_000ad278) with size=limit=0x20; the
 *   vararg tail is passed through from the caller. */
int
sptm_dt_snprintf(char *buf, uint64_t a, uint64_t b, const char *fmt, ...)
{
    va_list ap;
    int n;
    (void)a;
    (void)b;
    va_start(ap, fmt);
    n = sptm_snprintf(buf, 0x20, 0, 0x20, fmt, (void *)ap);
    va_end(ap);
    return n;
}

/* ------------------------------------------------------------------ */
/* sptm_dt_gpu_iouat_present                                           */
/* ------------------------------------------------------------------ */
/* FUN_000b7784 @ 0x000b7784   (sptm_dt_gpu_iouat_present)
 * Ghidra: undefined8 FUN_000b7784(void)
 * Report whether the GPU IO unified-address-table (iouat) is enabled per the
 * device tree: the "/arm-io/sgx" node must exist and the /chosen "gpu-iouat"
 * property must be a nonzero 32-bit value. Returns 1 when present, else 0.
 * Panics if /chosen is missing or "gpu-iouat" is the wrong size.
 * Confidence: medium
 * Notes: pure DT probe with no side effects (leaf function, no callers). */
int
sptm_dt_gpu_iouat_present(void)
{
    uintptr_t node = 0;
    uintptr_t chosen = 0;
    uint32_t *val = 0;
    uint32_t size = 0;
    int rc;

    if (sptm_dt_state[0] == 0)
        sptm_panic("Could not get devicetree");
    rc = sptm_dt_find_node(sptm_dt_state[0], 0, "/arm-io/sgx", &node);
    if (rc == -1)
        return 0;
    rc = sptm_dt_find_node(sptm_dt_state[0], 0, "/chosen", &chosen);
    if (rc != 1)
        sptm_panic("The /chosen devicetree node was not found");
    rc = sptm_dt_get_prop(chosen, "gpu-iouat", (uintptr_t *)&val, &size,
        sptm_dt_state[0], sptm_dt_state[1]);
    if (rc == 1) {
        if (size != 4)
            sptm_panic("The /gpu-iouat property should be 4 bytes");
        if (*val == 0)
            return 0;
    }
    return 1;
}

/* ------------------------------------------------------------------ */
/* sptm_boot_region                                                    */
/* ------------------------------------------------------------------ */
/* FUN_000b807c @ 0x000b807c   (sptm_boot_region)
 * Ghidra: undefined8 FUN_000b807c(undefined8 name, int required)
 * Look up a named boot region in the /chosen memory-map node and return its
 * value pointer ({base,size} pair). When `required` is nonzero, a missing
 * property panics; otherwise a missing property returns 0. A present property
 * whose size is not 0x10 (a {base,size} pair) panics.
 * Confidence: medium
 * Notes: reads via sptm_dt_get_prop against DAT_00094938 (memory-map root). */
long *
sptm_boot_region(const char *name, int required)
{
    uintptr_t val = 0;
    uint32_t size = 0;
    int rc;

    if (sptm_dt_memory_map == 0)
        sptm_panic("DT memory map is NULL");
    rc = sptm_dt_get_prop(sptm_dt_memory_map, name, &val, &size,
        sptm_dt_state[0], sptm_dt_state[1]);
    if (required && rc != 1)
        sptm_panic("error: %d looking up image region %s", rc, name);
    if (rc == 1) {
        if (size != 0x10)
            sptm_panic("DT property %s has illegal size", name);
        return (long *)val;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* sptm_boot_fixups                                                    */
/* ------------------------------------------------------------------ */
/* FUN_000b8154 @ 0x000b8154   (sptm_boot_fixups)
 * Ghidra: void FUN_000b8154(void)
 * Announce the device-tree blob {DAT_000944f8, DAT_00094500} into the DT
 * state, resolve the /chosen "memory-map" node into DAT_00094938, and
 * advance the bootstrap-stage bitmask by the "DT ready" bit (bit 1). The
 * release barrier (LORelease) orders the writes before the stage check; a
 * re-announce of the same stage panics.
 * Confidence: medium
 * Notes: stage bits = DAT_001012d8; the re-announce panic is
 *   "Attempted to announce bootstrap stage twice". */
void
sptm_boot_fixups(void)
{
    uint64_t prev;
    uintptr_t node = 0;
    int rc;

    if (sptm_dt_state[0] + (uintptr_t)sptm_dt_blob_end < sptm_dt_blob_base)
        sptm_panic_bad_dt();
    sptm_dt_state[0] = sptm_dt_blob_base;
    sptm_dt_state[1] = sptm_dt_blob_end;
    rc = sptm_dt_find_node(sptm_dt_state[0], 0, "/chosen/memory-map", &node);
    if (rc != 1)
        sptm_panic("error: %d looking up /chosen memory-map", rc);
    if (node == 0)
        sptm_panic("DT memory map is NULL");
    sptm_dt_memory_map = node;
    prev = sptm_boot_stages;
    sptm_boot_stages = sptm_boot_stages | ((sptm_boot_stages & 2) + 2);
    sptm_membar_release();
    if ((prev & 2) != 0)
        sptm_panic("Attempted to announce bootstrap stage twice");
}

/* ------------------------------------------------------------------ */
/* sptm_dispatch_engine_init                                           */
/* ------------------------------------------------------------------ */
/* FUN_000b8230 @ 0x000b8230   (sptm_dispatch_engine_init)
 * Ghidra: void FUN_000b8230(void)
 * Register the SPTM_ro and DeviceTree memory ranges, tear down the HIB region,
 * and (guarded by the DT-backed enable flag) initialize the trace/HIB driver
 * object and the GCM region before announcing the dispatch-engine bootstrap
 * stage (bit 0x2000). Panics if the expected prior stages are absent or the
 * stage is re-announced.
 * Confidence: medium
 * Notes: driver-object vtable call at DAT_00104120+0x38; region tag
 *   FUN_000bf298(0x5350544d="SPTM", ...) then FUN_000bf4bc; stage check
 *   requires bits 0x180000 already set. */
void
sptm_dispatch_engine_init(void)
{
    uint64_t prev;
    uintptr_t args0 = 0, args1 = 0, args2 = 0, args3 = 0;

    sptm_memmap_available("SPTM_ro", 2, 3);
    sptm_memmap_available("DeviceTree", 2, 0x23);
    sptm_hib_teardown_a(0);
    if (((uint32_t)sptm_boot_stages >> 0xd & 1) != 0)
        sptm_panic("Unexpected bootstrap stages reached");
    if ((~(uint32_t)sptm_boot_stages & 0x180000) == 0) {
        if ((sptm_hib_state & 1) != 0) {
            sptm_trace_r1 = 0;
            sptm_trace_r0 = 0;
            sptm_trace_r3 = 0;
            sptm_trace_r2 = 0;
            sptm_trace_r5 = 0;
            sptm_trace_r4 = 0;
            sptm_region_register(0x5350544d, sptm_nc_begin, sptm_nc_end,
                &sptm_trace_buf, &sptm_trace_cpu);
            sptm_trace_r2 = sptm_nc_begin;
            sptm_trace_r3 = sptm_nc_end;
            if ((sptm_boot_flag_cfg & 1) == 0) {
                sptm_trace_r4 = sptm_nc2_begin;
                sptm_trace_r5 = sptm_nc2_end;
            }
            /* driver-object setup: GCM flush/chunk barriers then a vtable
             * call (+0x38) and region commit. */
            sptm_gcm_flush_barr(sptm_obj, sptm_obj_args);
            sptm_gcm_chunk_barr(sptm_obj, sptm_obj_args, 0x1a8, &sptm_trace_cfg);
            args0 = 0;
            args1 = 0;
            args2 = 0;
            args3 = 0;
            (*(void (**)(uintptr_t, uintptr_t, uintptr_t *))(sptm_obj + 0x38))(
                sptm_obj, sptm_obj_args, &args0);
            sptm_region_commit(&sptm_trace_cpu, &args0, &sptm_trace_tbl);
            sptm_trace_cpu1 = 0;
            sptm_trace_cpu = 0;
            sptm_trace_cpu3 = 0;
            sptm_trace_cpu2 = 0;
            sptm_trace_cpu5 = 0;
            sptm_trace_cpu4 = 0;
        }
        prev = sptm_boot_stages;
        sptm_boot_stages = sptm_boot_stages | 0x2000;
        sptm_membar_release();
        if (((uint32_t)prev >> 0xd & 1) == 0)
            return;
        sptm_panic("Attempted to announce bootstrap stage twice");
    }
    sptm_panic("Expected bootstrap stages not reached");
}

/* ------------------------------------------------------------------ */
/* sptm_init_kc_regions                                                */
/* ------------------------------------------------------------------ */
/* FUN_000b8470 @ 0x000b8470   (sptm_init_kc_regions)
 * Ghidra: void FUN_000b8470(void)
 * TXM/kernelcache region setup: enter TXM with the per-CPU dispatch endpoint
 * (+0xa58), register the TXM_ro / BootKC_ro / BootKC_rs memory ranges, then
 * conditionally register AuxKC_ro/rx when the /chosen "AuxKC_ro" property is
 * present with a nonzero first word. Tear down HIB and announce the KC
 * bootstrap stage (bit 0x20000).
 * Confidence: medium
 * Notes: per-CPU base read via the sptm_sysreg_read(3,6,0xf,8,0) idiom; stage
 *   bit is 0x20000 (bit 17); "AuxKC_ro" property must be 0x10 bytes. */
void
sptm_init_kc_regions(void)
{
    uint64_t prev;
    uintptr_t cpu = 0;
    long *val = 0;
    uint32_t size = 0;
    int rc;

    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        cpu = tpidr_el2;
    else
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
    sptm_txm_enter(*(uintptr_t *)(cpu + 0xa58));
    sptm_memmap_available("TXM_ro", 0x2b, 0x2a);
    sptm_memmap_available("BootKC_ro", 0x23, sptm_boot_attr_1);
    sptm_memmap_available("BootKC_rs", 2, 3);
    if (sptm_dt_memory_map == 0)
        sptm_panic("DT memory map is NULL");
    rc = sptm_dt_get_prop(sptm_dt_memory_map, "AuxKC_ro", (uintptr_t *)&val,
        &size, sptm_dt_state[0], sptm_dt_state[1]);
    if (rc == 1) {
        if (size != 0x10)
            sptm_panic("DT property %s has illegal size", "AuxKC_ro");
        if (val != 0 && (uint64_t)*val - 1 < 0xfffffffffffffffe) {
            sptm_memmap_available("AuxKC_ro", 0x23, sptm_boot_attr_1);
            sptm_memmap_available("AuxKC_rx", 0x23, sptm_boot_attr_0);
        }
    }
    sptm_hib_teardown_b();
    if ((~(uint32_t)sptm_boot_stages & 0x180000) == 0) {
        if (((uint32_t)sptm_boot_stages >> 0x11 & 1) != 0)
            sptm_panic("Unexpected bootstrap stages reached");
        if ((sptm_hib_state & 1) != 0) {
            if ((sptm_boot_flag_cfg & 1) == 0) {
                sptm_region_register(0x4b45524e, sptm_nc2_begin, sptm_nc2_end,
                    &sptm_kc_r0, &sptm_kc_c0);
            } else {
                sptm_kc_r4 = 0;
                sptm_kc_r5 = 0;
                sptm_kc_r2 = 0;
                sptm_kc_r3 = 0;
                sptm_kc_r0 = 0;
                sptm_kc_r1 = 0;
            }
            sptm_kc_c4 = 0;
            sptm_kc_c5 = 0;
            sptm_kc_c2 = 0;
            sptm_kc_c3 = 0;
            sptm_kc_c0 = 0;
            sptm_kc_c1 = 0;
        }
        prev = sptm_boot_stages;
        sptm_boot_stages = sptm_boot_stages | 0x20000;
        sptm_membar_release();
        if (((uint32_t)prev >> 0x11 & 1) == 0)
            return;
        sptm_panic("Attempted to announce bootstrap stage twice");
    }
    sptm_panic("Expected bootstrap stages not reached");
}

/* ------------------------------------------------------------------ */
/* sptm_get_random                                                     */
/* ------------------------------------------------------------------ */
/* FUN_000ba950 @ 0x000ba950   (sptm_get_random)
 * Ghidra: ulong FUN_000ba950(undefined8 name, ulong len, undefined8 out)
 * Read the /chosen node property named by `name` (the random-seed / SK
 * entropy source), copy its bytes into `out` and return the length. The value
 * is both copied (sptm_save_late_const) and re-fixed-up (sptm_install_boot_
 * vectors). A missing property or a size larger than `len` panics.
 * Confidence: high
 * Notes: /chosen lookup via sptm_dt_find_node; property fetch via
 *   sptm_dt_get_prop. */
uintptr_t
sptm_get_random(const char *name, uintptr_t len, uintptr_t out)
{
    uintptr_t node = 0;
    uintptr_t val = 0;
    uint32_t size = 0;
    int rc;

    rc = sptm_dt_find_node(sptm_dt_state[0], 0, "/chosen", &node);
    if (rc != 1)
        sptm_panic("Error looking up /chosen");
    rc = sptm_dt_get_prop(node, name, &val, &size,
        sptm_dt_state[0], sptm_dt_state[1]);
    if (rc == 1) {
        if (val != 0 && size != 0 && (uintptr_t)size <= len) {
            sptm_save_late_const(out);
            sptm_save_late_const(val);
            sptm_install_boot_vectors(val);
            sptm_install_boot_vectors(size);
            return size;
        }
        sptm_panic("random_seed %p size mismatch", (void *)val);
    }
    sptm_panic("Error looking up /chosen %s", name);
    return 0;
}

/* ------------------------------------------------------------------ */
/* sptm_start_sk                                                       */
/* ------------------------------------------------------------------ */
/* FUN_000bb51c @ 0x000bb51c   (sptm_start_sk)
 * Ghidra: void FUN_000bb51c(void)
 * Populate the SK bootstrap region globals (DAT_00094360..000943a8) from the
 * CL4_* and DeviceTree boot regions, then perform the TXM handoff
 * (sptm_txm_handoff) and record the per-CPU sysreg (3,3,0xe,0,6). Uses
 * sptm_boot_region for each region lookup.
 * Confidence: medium
 * Notes: reads DAT_000944a8/000944b0/00094500/00094504/00100728/00094950/
 *   00094960 as the source region globals. */
void
sptm_start_sk(void)
{
    long *region;

    sptm_sk_boot1 = sptm_ro_end;      /* DAT_00094368 = DAT_000944b0 */
    sptm_sk_boot0 = sptm_ro_base;     /* DAT_00094360 = DAT_000944a8 */
    sptm_sk_boot2 = sptm_cpu_count;   /* DAT_00094370 = DAT_00100728 */
    region = sptm_boot_region("CL4_rx", 1);
    sptm_sk_rx = (uintptr_t)*region;
    region = sptm_boot_region("CL4_ro", 1);
    sptm_sk_ro = (uintptr_t)*region;
    region = sptm_boot_region("CL4_rw", 1);
    sptm_sk_rw = (uintptr_t)*region;
    region = sptm_boot_region("CL4_le", 1);
    sptm_sk_le = (uintptr_t)*region;
    sptm_sk_handoff = sptm_txm_handoff(&sptm_kc_end[0], &sptm_common);
    region = sptm_boot_region("DeviceTree", 1);
    sptm_dt_devicetree = (uintptr_t)*region;
    sptm_sk_dt_end = sptm_dt_blob_end;
    sptm_sk_boot0 = sptm_region_a[0];  /* DAT_00094470 = DAT_00094950 */
    sptm_sk_boot1 = sptm_region_a[1];  /* DAT_00094478 = DAT_00094960 */
    sptm_sk_boot2 = sptm_sysreg_read(3, 3, 0xe, 0, 6);
}

/* ------------------------------------------------------------------ */
/* sptm_start_txm                                                      */
/* ------------------------------------------------------------------ */
/* FUN_000bb61c @ 0x000bb61c   (sptm_start_txm)
 * Ghidra: void FUN_000bb61c(void)
 * Build the TXM bootstrap handoff context (DAT_00100100 block) from per-CPU
 * state and the DT/frame-table globals, and record the per-CPU sysreg
 * (3,3,0xe,0,6). The context records the TXM dispatch endpoint, DT bounds,
 * ID registers, and the frame/region tables used by the TXM level.
 * Confidence: medium
 * Notes: per-CPU base via the sptm_sysreg_read(3,6,0xf,8,0) idiom; +0xa58 is
 *   the TXM dispatch endpoint; ID regs read as raw globals. */
void
sptm_start_txm(void)
{
    uintptr_t cpu = 0;

    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        cpu = tpidr_el2;
    else
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
    sptm_txm_context.dispatch_fn = *(uintptr_t *)(cpu + 0xa58);
    sptm_txm_context.count = 10;
    sptm_txm_context.fte_class = (uint32_t)sptm_region_table[0];
    sptm_txm_context.dt_begin = sptm_dt_blob_base;
    sptm_txm_context.dt_end = sptm_dt_blob_end;
    sptm_txm_context.id_pfr0 = id_aa64pfr0_el1;
    sptm_txm_context.id_pfr1 = id_aa64pfr1_el1;
    sptm_txm_context.num_cpus = sptm_cpu_count;
    sptm_txm_context.root_ft = (uint64_t)sptm_boot_root_ft;
    sptm_txm_context.va_table = (uint64_t)sptm_boot_va_table;
    sptm_txm_context.phase = (uint64_t)sptm_phase_table;
    sptm_txm_context.reserved_058 = 0;
    sptm_txm_context.kc_end = (uint64_t)sptm_kc_end;
    sptm_txm_context.common = (uint64_t)&sptm_common;
    sptm_txm_context.id_isar0 = id_aa64isar0_el1;
    sptm_txm_context.id_isar1 = id_aa64isar1_el1;
    sptm_txm_context.cache_line = sptm_sysreg_read(3, 0, 0, 6, 2);
    sptm_txm_context.count2 = 10;
    sptm_txm_context.region_count = (uint64_t)sptm_handoff_region;
    sptm_txm_context.region_base = (uint64_t)sptm_handoff_region;
    sptm_txm_context.region_a = (uint64_t)sptm_region_a;
    sptm_txm_context.region_b = (uint64_t)sptm_region_b;
    sptm_txm_context.frame_table = (uint64_t)sptm_frame_table_a;
    sptm_txm_context.cursor_end = (uint64_t)sptm_cursor_end;
    sptm_txm_context.root_ft2 = (uint64_t)sptm_boot_root_ft;
    sptm_txm_context.percpu_table = (uint64_t)sptm_percpu_table_e;
    sptm_txm_context.fte_class_tbl = (uint64_t)sptm_region_table;
    sptm_txm_context.const_table = (uint64_t)sptm_const_table;
    sptm_txm_context.percpu_a = (uint64_t)sptm_percpu_table_a;
    sptm_txm_context.percpu_b = (uint64_t)sptm_percpu_table_c;
    if ((sptm_boot_flag_1 & 1) == 0) {
        sptm_txm_context.flags_118 |= 1;
        sptm_txm_context.boot_a = (uint64_t)sptm_boot_table_b;
        sptm_txm_context.boot_b = (uint64_t)sptm_boot_table_c;
    }
    sptm_txm_context.debug_a = (uint64_t)sptm_debug_a;
    sptm_txm_context.flags_c8 = 0;
    sptm_txm_context.boot_table = (uint64_t)sptm_boot_table_e;
    sptm_txm_context.boot_table_cnt = 10;
    sptm_txm_context.boot_table_ptr = (uint64_t)sptm_boot_table_d;
    sptm_txm_context.flags_118 |= 8;
    sptm_txm_context.percpu_c = (uint64_t)sptm_percpu_table_d;
    sptm_txm_context.percpu_d = (uint64_t)sptm_percpu_table_b;
    sptm_txm_context.frame_f = (uint64_t)sptm_frame_table_f;
    sptm_txm_context.frame_g = (uint64_t)sptm_frame_table_g;
    sptm_txm_context.debug_b = (uint64_t)sptm_debug_b;
    sptm_txm_context.boot_table_e = (uint64_t)sptm_boot_table_f;
    sptm_txm_context.hib_opt = sptm_sysreg_read(3, 3, 0xe, 0, 6);
}

/* ------------------------------------------------------------------ */
/* sptm_start_sk_ctx                                                   */
/* ------------------------------------------------------------------ */
/* FUN_000bb9f0 @ 0x000bb9f0   (sptm_start_sk_ctx)
 * Ghidra: void FUN_000bb9f0(void)
 * Build the SK bootstrap context (DAT_001002c0 and DAT_00100440 blocks):
 * translate the DT base and the TXM_ro / BootKC_ro / BootKC_le / AuxKC_*
 * boot-region bases into their runtime VAs (via the region table when the
 * stage bit 0x100 is set, else the frame base), then fill the region/frame
 * table fields, and finally set the SK runtime flag (DAT_00100608 |= 0x10).
 * Confidence: medium
 * Notes: VA translation helper: base + (region_pa - DAT_00095d18) + DAT_00095110
 *   when stage bit 0x100 clear; otherwise a per-entry scan of DAT_00101ac8
 *   (count) / DAT_00101ad0 (24-byte entries), else sptm_va_lookup. */
void
sptm_start_sk_ctx(void)
{
    uintptr_t cpu = 0;
    uintptr_t pa, va;
    uint64_t entries;
    uintptr_t *entry;
    int rc;
    uintptr_t aux = 0;
    uint32_t aux_size = 0;
    long *region;

    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        cpu = tpidr_el2;
    else
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
    sptm_sk_context.handoff_magic = *(uintptr_t *)(cpu + 0x15b0);
    sptm_sk_context.frame_table = (uint64_t)sptm_frame_table_a;
    sptm_sk_context.dt_begin = sptm_dt_end_cur + (uintptr_t)sptm_frame_table_b[0] * 0x4000;
    sptm_sk_context.num_cpus = sptm_cpu_count;
    sptm_sk_context.hw_table = (uint64_t)sptm_hw_table;

    /* translate the DT base to its runtime VA */
    if (((uint32_t)sptm_boot_stages >> 8 & 1) == 0) {
        sptm_sk_context.va_base = (sptm_dt_blob_base - (uintptr_t)sptm_region_a[0]) +
            (uintptr_t)sptm_frame_table_c[0];
    } else {
        va = 0;
        entries = (uint64_t)sptm_handoff_region[0];
        if (entries != 0) {
            entry = (uintptr_t *)&sptm_handoff_region[1];
            do {
                if (entry[0] <= sptm_dt_blob_base &&
                    sptm_dt_blob_base < entry[0] + (uintptr_t)entry[2] * 0x4000) {
                    va = (sptm_dt_blob_base - entry[0]) + entry[1];
                    break;
                }
                entry += 3;
                entries--;
            } while (entries != 0);
        }
        if (va == 0)
            va = sptm_va_lookup(sptm_dt_blob_base);
        sptm_sk_context.va_base = va;
    }

    region = sptm_boot_region("TXM_ro", 1);
    sptm_sk_context.txm_ro_va =
        ((uintptr_t)*region - sptm_ro_base + 0x3fff) & ~(uintptr_t)0x3fff;
    sptm_sk_context.va_table = (uint64_t)sptm_boot_va_table;
    sptm_sk_context.count = 10;
    sptm_sk_context.frame_d = (uint64_t)sptm_frame_table_d;
    sptm_sk_context.frame_e = (uint64_t)sptm_frame_table_e;

    pa = (uintptr_t)*sptm_boot_region("BootKC_ro", 1);
    sptm_sk_context.bootkc_ro_va = sptm_region_va_translate(pa);
    pa = (uintptr_t)*sptm_boot_region("BootKC_le", 1);
    sptm_sk_context.bootkc_le_va = sptm_region_va_translate(pa);

    sptm_sk_context.boot_flag = sptm_boot_flag_0 & 1;
    sptm_sk_context.fte_class = (uint64_t)sptm_region_table[0];
    sptm_sk_context.common = (uint64_t)&sptm_common;
    sptm_sk_context.boot_a2 = (uint64_t)sptm_boot_table_a;
    sptm_sk_context.boot_b2 = (uint64_t)sptm_boot_table_b;
    sptm_sk_context.flags_1f8 = 0;

    /* AuxKC_rw / AuxKC_ro / AuxKC_le present only when /chosen AuxKC_rw */
    if (sptm_dt_memory_map == 0)
        sptm_panic("DT memory map is NULL");
    rc = sptm_dt_get_prop(sptm_dt_memory_map, "AuxKC_rw", &aux, &aux_size,
        sptm_dt_state[0], sptm_dt_state[1]);
    if (rc == 1) {
        if (aux_size != 0x10)
            sptm_panic("DT property %s has illegal size", "AuxKC_rw");
        if (aux != 0 && (uint64_t)*(long *)aux - 1 < 0xfffffffffffffffe) {
            pa = (uintptr_t)*sptm_boot_region("AuxKC_rw", 1);
            sptm_sk_context.kc_rw_va = sptm_region_va_translate(pa);
            pa = (uintptr_t)*sptm_boot_region("AuxKC_ro", 1);
            sptm_sk_context.kc_ro_va = sptm_region_va_translate(pa);
            region = sptm_boot_region("AuxKC_le", 1);
            pa = (uintptr_t)region[1] + (uintptr_t)region[0];
            sptm_sk_context.kc_le_va = sptm_region_va_translate(pa);
        } else {
            sptm_sk_context.kc_le_va = 0;
            sptm_sk_context.kc_rw_va = 0;
            sptm_sk_context.kc_ro_va = 0;
        }
    }

    sptm_sk_context.hib_state_ptr = (uint64_t)&sptm_hib_state;
    sptm_sk_context.mem_map = sptm_dt_memory_map;
    sptm_sk_context.frame_f = (uint64_t)sptm_frame_table_f;
    sptm_sk_context.frame_g = (uint64_t)sptm_frame_table_g;
    sptm_sk_context.frame_h = (uint64_t)sptm_frame_table_h;
    sptm_sk_context.frame_i = (uint64_t)sptm_frame_table_i;
    sptm_sk_context.count2 = 10;
    sptm_sk_context.region_count = (uint64_t)sptm_handoff_region;
    sptm_sk_context.region_base = (uint64_t)sptm_handoff_region;
    sptm_sk_context.region_a = (uint64_t)sptm_region_a;
    sptm_sk_context.region_b = (uint64_t)sptm_region_b;
    sptm_sk_context.frame_table2 = (uint64_t)sptm_frame_table_a;
    sptm_sk_context.cursor_end = (uint64_t)sptm_cursor_end;
    sptm_sk_context.root_ft = (uint64_t)sptm_boot_root_ft;
    sptm_sk_context.percpu_table = (uint64_t)sptm_percpu_table_e;
    sptm_sk_context.fte_class_tbl = (uint64_t)sptm_region_table;
    sptm_sk_context.const_table = (uint64_t)sptm_const_table;
    sptm_sk_context.percpu_a = (uint64_t)sptm_percpu_table_a;
    sptm_sk_context.percpu_b = (uint64_t)sptm_percpu_table_c;
    if ((sptm_boot_flag_1 & 1) == 0) {
        sptm_sk_context.flags_248 |= 1;
        sptm_sk_context.boot_a = (uint64_t)sptm_boot_table_b;
        sptm_sk_context.boot_b = (uint64_t)sptm_boot_table_c;
    }
    sptm_sk_context.debug_a = (uint64_t)sptm_debug_a;
    sptm_sk_context.boot_table = (uint64_t)sptm_boot_table_e;
    sptm_sk_context.flags_1f8 = 0;
    sptm_sk_context.boot_table_cnt = 10;
    sptm_sk_context.boot_table_ptr = (uint64_t)sptm_boot_table_d;
    sptm_sk_context.flags_248 |= 8;
    sptm_sk_context.percpu_c = (uint64_t)sptm_percpu_table_d;
    sptm_sk_context.percpu_d = (uint64_t)sptm_percpu_table_b;
    sptm_sk_context.frame_f2 = (uint64_t)sptm_frame_table_f;
    sptm_sk_context.frame_g2 = (uint64_t)sptm_frame_table_g;
    sptm_sk_context.debug_b = (uint64_t)sptm_debug_b;
    sptm_sk_context.boot_table_e = (uint64_t)sptm_boot_table_f;
    sptm_sk_context.hib_opt = sptm_sysreg_read(3, 3, 0xe, 0, 6);
    sptm_sk_context.flags_348 |= 0x10;
}

/* ------------------------------------------------------------------ */
/* sptm_init_sched                                                     */
/* ------------------------------------------------------------------ */
/* FUN_000baa60 @ 0x000baa60   (sptm_init_sched)
 * Ghidra: void FUN_000baa60(long param_1)
 * Full per-CPU EL2/EL1 bootstrap: install the EL1 MMU (TCR/TTBR0), set
 * tpidr_el2 to the per-CPU state, choose VBAR/SCTLR, scan /cpus for the
 * largest die-id, validate the six CTRR (Core Trace Register) core/cluster
 * regions against the expected bounds, and finally call sptm_el2_enable with
 * the computed EL2 configuration selector. Panics on any region mismatch.
 * Confidence: medium
 * Notes: per-CPU "micro_magic" short at +0x1438 selects the EL2
 *   configuration selector (0x8000000000000010/0x11); /cpus iteration uses
 *   sptm_dt_iterate; the CTRR register encodings are read via
 *   sptm_sysreg_read(3,0,0xb,..)/(3,4,0xf,..). */
void
sptm_init_sched(uintptr_t param_1)
{
    uint64_t prev;
    uintptr_t cpu;
    uint16_t micro_magic;
    uint64_t sel;
    int rc;

    sptm_sysreg_write(3, 1, 0xf, 1, 5, 3);
    sptm_sysreg_write(3, 4, 0xf, 0xe, 6, 3);
    sptm_isb();
    if ((sptm_dbg_flag & 1) == 0) {
        cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
        if (cpu == 0) {
            cpu = tpidr_el2;
            if (*(uint16_t *)(cpu + 0x1438) == 0)
                goto check_init_flag;
            goto install_mmu;
        }
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
        if (*(uint16_t *)(cpu + 0x1438) != 0)
            goto install_mmu;
check_init_flag:
        if ((*(uint8_t *)(param_1 + 1) & 1) != 0)
            goto install_mmu;
    } else {
install_mmu:
        tcr_el1 = 0x310800336511a511;
        sptm_dsb(2, 3, 0);
        if (ttbr0_el1 != (sptm_boot_fte_alt[0] & 0xfffffffffffe)) {
            ttbr0_el1 = sptm_boot_fte_alt[0] & 0xfffffffffffe;
        }
        sptm_isb();
        sptm_sysop_write(0, 9, 7, 0, 0);
        sptm_dsb(1, 3, 1);
        sptm_isb();
    }
    tpidr_el2 = param_1;
    if (((uint32_t)sptm_boot_stages >> 0x11 & 1) != 0)
        vbar_el1 = sptm_fte_end[0];
    if ((sptm_boot_flag_1 & 1) == 0) {
        sctlr_el1 = sctlr_el1 | 0xd4000000000;
        sptm_isb();
    }
    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        cpu = tpidr_el2;
    else
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
    /* second per-cpu read for micro_magic */
    {
        uintptr_t cpu2 = sptm_sysreg_read(3, 6, 0xf, 8, 0);
        if (cpu2 == 0)
            micro_magic = *(uint16_t *)(tpidr_el2 + 0x1438);
        else
            micro_magic = *(uint16_t *)(sptm_sysreg_read(3, 6, 0xf, 0xb, 1) + 0x1438);
    }
    if (micro_magic == 0 && (*(uint8_t *)(cpu + 1) & 1) == 0) {
        sptm_dt_iter_t iter;
        uintptr_t node = 0;
        uintptr_t cpus = 0;
        uint32_t die_id;

        rc = sptm_dt_find_node(sptm_dt_state[0], 0, "/cpus", &cpus);
        if (rc != 1)
            sptm_panic("Error looking up /cpus");
        if (sptm_dt_state[0] == 0)
            sptm_panic("Error initializing DT iterator");
        memset(&iter, 0, sizeof(iter));
        iter.parent = cpus != 0 ? cpus : sptm_dt_state[0];
        while (sptm_dt_iterate(sptm_dt_state[0], &iter, &node) != 0) {
            uint32_t *val = 0;
            uint32_t sz = 0;
            rc = sptm_dt_get_prop(node, "die-id", (uintptr_t *)&val, &sz,
                sptm_dt_state[0], sptm_dt_state[1]);
            if (rc == 1 && *val > sptm_max_die_id)
                sptm_max_die_id = *val;
        }
    }
    if ((*(uint8_t *)(param_1 + 1) & 1) == 0) {
        sel = 0x30300;
        if ((sptm_hib_opt & 1) == 0)
            sel = 0x3030000ffff00;
        sptm_sysreg_write(3, 6, 0xf, 8, 5, sel);
        sptm_sysreg_write(3, 1, 0xf, 8, 2, sel);
    }
    /* validate the six CTRR region {begin,end} pairs */
    sptm_validate_ctrr_region(sptm_nc_begin, sptm_nc_end, "nc");
    sptm_validate_ctrr_region(sptm_nc2_begin, sptm_nc2_end, "nc2");
    sptm_validate_ctrr_region(sptm_nc3_begin, sptm_nc3_end, "nc3");
    sptm_validate_ctrr_region(sptm_nc4_begin, sptm_nc4_end, "nc4");
    sptm_validate_ctrr_region(sptm_nc5_begin, sptm_nc5_end, "nc5");
    sptm_validate_ctrr_region(sptm_nc6_begin, sptm_nc6_end, "nc6");
    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        micro_magic = *(uint16_t *)(tpidr_el2 + 0x1438);
    else
        micro_magic = *(uint16_t *)(sptm_sysreg_read(3, 6, 0xf, 0xb, 1) + 0x1438);
    if (micro_magic != 0)
        sptm_validate_ctrr_registers();
    sptm_isb();
    cpu = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (cpu == 0)
        cpu = tpidr_el2;
    else
        cpu = sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
    sel = 0x8000000000000010;
    if (*(uint16_t *)(cpu + 0x1438) != 0)
        sel = 0x8000000000000011;
    sptm_sysreg_write(3, 4, 0xf, 1, 2, sel);
    sptm_isb();
    sptm_el2_enable(sel, *(uintptr_t *)(param_1 + 0xa50));
}

/* Validate that a CTRR region begin/end pair is sane (begin > 1, end > 1,
 * begin <= end). On failure panics. */
static void
sptm_validate_ctrr_region(uint64_t begin, uint64_t end, const char *name)
{
    (void)name;
    if (0xfffffffffffffffd < begin - 1)
        sptm_panic("CTRR %s begin invalid: %llx", name, begin);
    if (0xfffffffffffffffd < end - 1)
        sptm_panic("CTRR %s end invalid: %llx", name, end);
    if (end < begin)
        sptm_panic("CTRR %s begin > end: %llx > %llx", name, begin, end);
}

/* Read and cross-check the per-core/per-cluster CTRR registers against the
 * expected configuration and region bounds. Panics on any mismatch. */
static void
sptm_validate_ctrr_registers(void)
{
    uint64_t v;
    uintptr_t cpu;

    /* per-core CTRR */
    v = sptm_sysreg_read(3, 0, 0xb, 1, 4);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 0, 0xb, 1, 4);
        sptm_panic("CTRR_A per core register not set");
    }
    v = sptm_sysreg_read(3, 0, 0xb, 1, 5);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 0, 0xb, 1, 5);
        sptm_panic("CTRR_B per core register not set");
    }
    /* per-cluster CTRR */
    v = sptm_sysreg_read(3, 0, 0xb, 5, 2);
    if (v != 0xc0000000aa01999a) {
        sptm_sysreg_read(3, 0, 0xb, 5, 2);
        sptm_panic("CTRR_A per cluster register not set");
    }
    v = sptm_sysreg_read(3, 0, 0xb, 5, 3);
    if (v != 0xc0000000aa028aaa) {
        sptm_sysreg_read(3, 0, 0xb, 5, 3);
        sptm_panic("CTRR_B per cluster register not set");
    }
    v = sptm_sysreg_read(3, 0, 0xb, 5, 4);
    if (v != 0xc0000000aa026a6a) {
        sptm_sysreg_read(3, 0, 0xb, 5, 4);
        sptm_panic("CTRR_A per cluster register not set");
    }
    v = sptm_sysreg_read(3, 0, 0xb, 5, 5);
    if (v != 0xc0000000aa026aaa) {
        sptm_sysreg_read(3, 0, 0xb, 5, 5);
        sptm_panic("CTRR_B per cluster register not set");
    }
    /* per-core / per-cluster CTRR present at EL2 */
    v = sptm_sysreg_read(3, 4, 0xf, 2, 5);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 4, 0xf, 2, 5);
        sptm_panic("CTRR_A per core register not set");
    }
    v = sptm_sysreg_read(3, 4, 0xf, 2, 2);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 4, 0xf, 2, 2);
        sptm_panic("CTRR_B per core register not set");
    }
    v = sptm_sysreg_read(3, 4, 0xf, 0xb, 4);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 4, 0xf, 0xb, 4);
        sptm_panic("CTRR_A per cluster register not set");
    }
    v = sptm_sysreg_read(3, 4, 0xf, 0xb, 5);
    if (v != 0x8000000000000001) {
        sptm_sysreg_read(3, 4, 0xf, 0xb, 5);
        sptm_panic("CTRR_B per cluster register not set");
    }
    (void)cpu;
}
