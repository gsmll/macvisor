/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
/* hv_glue_audit_sys.c — kernel touch-set recreation (tree hv-deps, FULL-AUDIT). */

#include <stdint.h>
#include <stddef.h>

typedef unsigned char byte_t;

/* kernel_trace_core is called by the kernel_trace wrapper before its
 * definition; forward-declare it here. */
void kernel_trace_core(uint64_t event, uint64_t a2, uint64_t a3, uint64_t a4,
                       uint64_t a5, uint64_t a6, uint32_t flags);

/*
 * hv_glue_audit_sys.c — the kernel per-CPU / MMU / trace / device-tree touch-set
 * the hypervisor calls directly (category Sys), recreated per the FULL-AUDIT
 * rule in AGENTS.md. Each body is transcribed faithfully from a fresh Ghidra
 * decompile of kernelcache.arm64.kc (image base fffffe0007004000).
 *
 * The FUN_ names are the Ghidra ground truth; the English names are estimates.
 *   per_cpu_base          @ 0xfffffe000b866ec4 — per-CPU struct getter (PAC'd;
 *                         decompiler collapses to panic stub; disassembly
 *                         reconstruction below, confidence LOW).
 *   kernel_tlb_flush      @ 0xfffffe000b96c6d4 — EL1 TLB invalidate dispatch.
 *   kernel_page_validate  @ 0xfffffe000c0d7b94 — paddr window lookup.
 *   kernel_paddr_type     @ 0xfffffe000c0d7c20 — physical-address type lookup.
 *   kernel_memattr_resolve@ 0xfffffe000b94abbc — memory-attribute resolution.
 *   kernel_preempt_dec    @ 0xfffffe000b94172c — preemption-counter decrement.
 *   kernel_trace          @ 0xfffffe000bd30528 — thin wrapper over the trace
 *                         core (kernel_trace_core @ 0xfffffe000bd310e8), which
 *                         is transcribed in full below.
 *   kernel_boot_arg_get   @ 0xfffffe000c09cbf0 — boot-args parser.
 *   kernel_dt_node_lookup @ 0xfffffe000c09c084 — device-tree path walk.
 *   kernel_dt_prop_get    @ 0xfffffe000c09c31c — device-tree property getter.
 *
 * Callees 2+ levels into XNU stay stubbed externs (FUN_/DAT_ kept in
 * comments) — the FULL-AUDIT boundary. Ghidra pseudo-artifacts (PAC pointer
 * tags, EL2 sysreg reads, NEON umaxv, CARRY8) are reproduced with local
 * helpers / inline expressions so the bodies compile.
 */

/* ------------------------------------------------------------------ *
 * Ghidra decompiler pseudo-artifacts used by the bodies below.
 * ------------------------------------------------------------------ */
#define CARRY8(a, b)    ((uint64_t)((a) + (b)) < (uint64_t)(a))

/* Ghidra models PAC/pointer-auth as or-ing a tag into the address; the
 * decompiler emits the same repair at every site that dereferences an
 * un-authenticated pointer. Reproduce faithfully. */
static uint64_t hv_glue_pac_2bad(uint64_t p)   /* tag 0x2bad: 32-bit truncation repair */
{
    if ((uint64_t)(long)(int)p != p) {
        p = (p & 0xffffffffffffULL) | 0x2bad000000000000ULL;
    }
    return p;
}
static uint64_t hv_glue_pac_c8a2(uint64_t base, uint64_t ptr) /* tag 0xc8a2: top-bit repair */
{
    if (((base ^ ptr) & 0xffc0000000000000ULL) != 0) {
        ptr = (ptr & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
    }
    return ptr;
}

/* Reproduce NEON_umaxv (reduce 4 S-lanes to the unsigned max), which Ghidra
 * renders for the trace-core debug-event check. Returns the max 32-bit lane. */
static uint32_t hv_glue_umaxv_u32(uint32_t lanes[4])
{
    uint32_t m = 0;
    for (int i = 0; i < 4; i++) {
        m = (m < lanes[i]) ? lanes[i] : m;
    }
    return m;
}

/* ------------------------------------------------------------------ *
 * Shared kernel globals (naming table in hv_internal.h; DAT_ kept here).
 * ------------------------------------------------------------------ */
extern uint64_t tpidr_el1;            /* per-CPU data base (raw register value) */
extern uint64_t daif;                 /* DAIF system register (pseudo-global)  */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);

/* page-validate / paddr-type tables (DAT_fffffe0007e9e470..) */
extern uint64_t hv_glue_pv_ready;          /* DAT_fffffe0007e9e470 : PV init flag (bit 0) */
extern uint64_t hv_glue_pv_count;          /* DAT_fffffe0007e9e478 : PV entry count (value) */
extern uint64_t hv_glue_pv_table;          /* DAT_fffffe0007e9e480 : PV range table base   */
extern uint64_t hv_glue_dram_lo;           /* DAT_fffffe0007e9e488 : paddr-type main window lo */
extern uint64_t hv_glue_dram_hi;           /* DAT_fffffe0007e9e490 : paddr-type main window hi */
extern uint64_t hv_glue_region_count;      /* DAT_fffffe0007e9e4d0 : secondary region count */
extern uint64_t hv_glue_region_tbl;        /* DAT_fffffe0007e9e4d8 : secondary region table  */
extern uint64_t hv_glue_type_tbl;          /* DAT_fffffe0007e9e4b0 : paddr type-byte table  */

/* memattr-resolve tables */
extern uint64_t hv_mem_window_lo;          /* DAT_fffffe0007e0c050 : DRAM window lower bound */
extern uint64_t hv_mem_window_hi;          /* DAT_fffffe0007e0c058 : DRAM window upper bound */
extern uint16_t hv_memattr_granule[];      /* DAT_fffffe0007d82e20 : per-attr granule table */
extern uint8_t  hv_memattr_table[];        /* DAT_fffffe000c5ec610 : resolved-attr output table */
extern uint64_t hv_memattr_aux;            /* DAT_fffffe000c5ece18 : attr aux table (base)  */
extern uint64_t hv_special_owner_block;    /* DAT_fffffe000c62b698 : special owner/pmap block */
extern char    *s_hw_lock_bit;             /* PTR_s_hw_lock_bit_t_fffffe0007d82e88 */
extern void    *kernel_lock_panic_ctx;     /* DAT_fffffe000c68af18 : lock panic context */
extern void    *kernel_lock_cb_data;       /* DAT_fffffe0007d82d90 : lock callback data */

/* trace globals */
extern uint32_t hv_trace_level;            /* DAT_fffffe000c5c55ac : trace level/type */
extern uint64_t hv_trace_flag;             /* DAT_fffffe000c68ac90 : trace-enable flag (bit 0) */
extern uint8_t  hv_trace_event_filter[];   /* DAT_fffffe000c72bbe0 : per-event filter bitmap */
extern uint64_t hv_trace_id_lo;            /* DAT_fffffe000c648e00 : event id window lo */
extern uint64_t hv_trace_id_hi;            /* DAT_fffffe000c648e04 : event id window hi */
extern uint64_t hv_trace_id_a;             /* DAT_fffffe000c648e08 : id A */
extern uint64_t hv_trace_id_b;             /* DAT_fffffe000c648e0c : id B */
extern uint64_t hv_trace_id_c;             /* DAT_fffffe000c648e10 : id C */
extern uint64_t hv_trace_id_d;             /* DAT_fffffe000c648e14 : id D */
extern uint32_t hv_trace_procfilt;         /* DAT_fffffe000c5c55a8 : proc-filter flags */
extern uint32_t hv_trace_mode;             /* DAT_fffffe000c5c558c : trace mode (bit 0) */
extern uint64_t hv_trace_cpu_buf;          /* DAT_fffffe000c648de8 : per-cpu buffer table base */
extern uint32_t hv_trace_lock;             /* DAT_fffffe000c5c5588 : trace lock word */
extern uint64_t hv_trace_bufmeta;          /* DAT_fffffe000c648dd8 : buffer meta */
extern uint64_t hv_trace_buf_table;        /* DAT_fffffe000c648df0 : buffer segment table */
extern uint32_t hv_trace_bufmax;           /* DAT_fffffe000c5c5590 : max in-flight entries */
extern uint64_t hv_trace_tick_base;        /* DAT_fffffe000c62bc70 : timebase */
extern uint32_t hv_trace_post;             /* DAT_fffffe000c648e34 : post-trace flag */
extern uint32_t hv_trace_debug_on;         /* DAT_fffffe000c72bc20 : debug-exceptions flag (bit 0) */
extern uint64_t hv_trace_debug_thr;        /* DAT_fffffe000c648de0 : debug event threshold */
extern uint64_t hv_trace_debug_ctr;        /* DAT_fffffe000c5c55c0 : debug event counter */
extern uint32_t hv_trace_debug_lock;       /* DAT_fffffe000c72bbb8 : debug lock word */
extern uint64_t hv_trace_debug_sink;       /* DAT_fffffe000c756760 : debug sink */

/* device-tree globals */
extern uint64_t hv_dt_lo;                  /* DAT_fffffe0007e9d260 : DT region lo */
extern uint64_t hv_dt_hi;                  /* DAT_fffffe0007e9d270 : DT region hi */
extern uint64_t hv_dt_present;             /* DAT_fffffe0007e9d278 : DT present flag */
extern uint64_t hv_stack_canary;           /* DAT_fffffe000c5f0000 : stack canary */
extern char     hv_dt_name_prop[];         /* DAT_fffffe00070f10a7 : "name" property string */
extern char     hv_bootarg_default[];      /* DAT_fffffe00070f1714 : default boot-arg value */

/* per-cpu flags / counters reached through tpidr_el1 */
#define HV_PCPU_SUB        0x1b8   /* pointer to a per-cpu sub-struct   */
#define HV_PCPU_FLUSH_FLAG 0x4c    /* byte, bit 2 = tlb-flush needed    */
#define HV_PCPU_PREEMPT    0x1c0   /* int preemption counter            */
#define HV_PCPU_OFF       0x1b0    /* per-cpu offset (>> 16)            */
#define HV_PCPU_STATE     0x418    /* per-cpu state struct ptr          */
#define HV_PCPU_STATE_DATA 0x28    /* per-cpu data ptr within state     */

/* ------------------------------------------------------------------ *
 * Kernel panics / asserts (all noreturn; 2+ levels in XNU).
 * ------------------------------------------------------------------ */
extern void kernel_panic_assert(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0e11ec */
extern void kernel_panic_a(void) __attribute__((noreturn));          /* FUN_fffffe000c0f1874 (preempt underflow) */
extern void kernel_panic_cpu_ro(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0eae44 zone_require_ro */
extern void kernel_panic_cpu_tro(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0eb104 tro check */
extern void kernel_stack_check_fail(uint64_t) __attribute__((noreturn)); /* FUN_fffffe000c0e0620 */

/* ------------------------------------------------------------------ *
 * Stubbed kernel callees (audit boundary — internals are 2+ levels in).
 * ------------------------------------------------------------------ */
extern void kernel_tlb_flush_core(void);                     /* FUN_fffffe000b7a56d4 */
extern int  kernel_lock_bit_wait(uint64_t, int, void **, void **); /* FUN_fffffe000b7f8ce0 (0 = busy) */
extern void kernel_lock_bit_release(uint64_t, int);          /* FUN_fffffe000b7f8ed0 */
extern void kernel_preempt_adjust(void *, int, int);         /* FUN_fffffe000b815288 */
extern void kernel_thread_preempt_dec(void *);               /* FUN_fffffe000b83f58c */
extern void kernel_preempt_deferred_cb(void);                /* FUN_fffffe000b944b00 (callback) */
extern int  kernel_pv_lookup(void *, uint64_t *);            /* FUN_fffffe000c0fb940 */
extern void kernel_paddr_trace_commit(uint64_t, uint64_t, uint64_t, uint32_t); /* FUN_fffffe000c0d84b0 */
extern int  kernel_strncmp(const char *, const char *, uint64_t);  /* FUN_fffffe000b760950 */
extern uint64_t kernel_strlen(const char *);                 /* FUN_fffffe000b7608d0 */
extern int  kernel_strcmp(const char *, const char *);       /* FUN_fffffe000b923854 */
extern void kernel_bootarg_memfill(void *, uint32_t);        /* FUN_fffffe000c09d008 */
extern int  kernel_bootarg_parse_value(char *, uint64_t *, int (*)(uint64_t), int); /* FUN_fffffe000c09d080 (0 = ok) */
extern int  kernel_bootarg_isdigit(uint64_t);                /* FUN_fffffe000c09d2b0 */
extern void *kernel_dt_next_prop(int *);                     /* FUN_fffffe000c09c4b8 */
extern uint64_t kernel_trace_buffer_acquire(uint32_t *, uint64_t, uint64_t); /* FUN_fffffe000bd2d774 */
extern int  kernel_trace_lock_acquire(void *);               /* FUN_fffffe000b7f89cc */
extern void kernel_trace_lock_release(void *);               /* FUN_fffffe000b7f8a60 */
extern void kernel_trace_restore_preempt(int);               /* FUN_fffffe000b968948 */
extern void kernel_trace_emit(uint64_t, void *);             /* FUN_fffffe000b9257c4 */
extern void kernel_trace_reg_write(void *, void *, int, int, uint32_t); /* FUN_fffffe000b8563f8 */

/* ======================================================================== *
 * kernel_tlb_flush
 * ======================================================================== */
/* FUN_fffffe000b96c6d4 @ 0xfffffe000b96c6d4   (est. kernel_tlb_flush)
 * Ghidra: void FUN_fffffe000b96c6d4(void)
 * Dispatches an EL1 TLB invalidate. If IRQs are currently unmasked it saves
 * DAIF, masks async/IRQ/FIQ (0x1c0), checks the per-CPU tlb-flush-needed flag
 * and, if set, calls the flush core (b7a56d4); DAIF is restored either way.
 * No arguments, no return; only side effect is the invalidate.
 * Confidence: high
 * Notes: daif/tpidr_el1 register reads; flag = per-cpu sub (+0x1b8) byte
 *   +0x4c bit 2; flush core FUN_fffffe000b7a56d4 left stubbed (2+ levels in).
 * Kernel code recreated for audit (hv-deps). */
void kernel_tlb_flush(void)
{
    uint64_t saved_daif = daif;

    if (((uint32_t)saved_daif >> 7 & 1) == 0) {     /* I bit clear => IRQs enabled */
        daif = daif | 0x1c0;                        /* mask A/F/I */
        uint64_t percpu = tpidr_el1;
        uint64_t sub = *(uint64_t *)(percpu + HV_PCPU_SUB);
        if ((*(uint8_t *)(sub + HV_PCPU_FLUSH_FLAG) >> 2 & 1) != 0) {
            kernel_tlb_flush_core();                /* FUN_fffffe000b7a56d4 */
        }
        daif = saved_daif;
    }
}

/* ======================================================================== *
 * kernel_page_validate
 * ======================================================================== */
/* FUN_fffffe000c0d7b94 @ 0xfffffe000c0d7b94   (est. kernel_page_validate)
 * Ghidra: undefined8 FUN_fffffe000c0d7b94(ulong param_1, long *param_2)
 * Validates that a page-aligned PTE (param_1 & ~0xfff) falls inside one of
 * the wired page-window ranges described by the PV table, translating it to
 * the corresponding physical block written to *out. Returns 0 on success
 * (out holds the validated block), 1 if the PV tables are uninitialized,
 * 2 if out is NULL, 4 if no window matches or the translation is zero.
 * Confidence: high
 * Notes: reads DAT_fffffe0007e9e470 (ready), *DAT_fffffe0007e9e478 (count),
 *   DAT_fffffe0007e9e480 (table); each entry = 3 longs (range start,
 *   map base, count) with 0x4000-granule stride.
 * Kernel code recreated for audit (hv-deps). */
uint64_t kernel_page_validate(uint64_t pte, uint64_t *out)
{
    if ((hv_glue_pv_ready & 1) == 0) {
        return 1;
    }
    if (out != 0) {
        uint64_t count = hv_glue_pv_count;
        if (hv_glue_pv_count != 0) {
            long *entry = (long *)(hv_glue_pv_table + 8);
            do {
                uint64_t range_start = entry[-1];           /* plVar3[-1] */
                if ((range_start <= pte) &&
                    (pte < range_start + (uint64_t)*(uint32_t *)(entry + 1) * 0x4000)) {
                    long translated = *entry + (pte - range_start);   /* lVar1 */
                    if (translated == 0) {
                        return 4;
                    }
                    *out = (uint64_t)translated;
                    return 0;
                }
                entry += 3;
                count--;
            } while (count != 0);
        }
        return 4;
    }
    return 2;
}

/* ======================================================================== *
 * kernel_paddr_type
 * ======================================================================== */
/* FUN_fffffe000c0d7c20 @ 0xfffffe000c0d7c20   (est. kernel_paddr_type)
 * Ghidra: undefined8 FUN_fffffe000c0d7c20(ulong param_1, undefined1 *param_2)
 * Looks up the memory type of a physical address and stores it in *out.
 * Addresses in the main DRAM window (DAT_fffffe0007e9e488..490) index the
 * type-byte table (DAT_fffffe0007e9e4b0); addresses outside are found by a
 * binary search over the secondary region table (DAT_fffffe0007e9e4d8), with
 * a default type of 0x1a when nothing matches. Returns 0 on success, 1 if
 * uninitialized, 2 if out is NULL.
 * Confidence: high
 * Notes: PAC pointer tag on the table index (0xc8a2); the DRAM default type
 *   constant is 0x1a per this decompile (task brief said 0x1b).
 * Kernel code recreated for audit (hv-deps). */
uint64_t kernel_paddr_type(uint64_t paddr, uint8_t *out)
{
    uint64_t tbl;
    uint8_t  type;

    if ((hv_glue_pv_ready & 1) == 0) {
        return 1;
    }
    if (out == 0) {
        return 2;
    }
    if (paddr < hv_glue_dram_lo || hv_glue_dram_hi <= paddr) {
        /* Outside the main window: binary search the secondary region table. */
        if (hv_glue_region_count == 0) {
            type = 0x1a;
            goto store_type;
        }
        uint32_t hi_idx = (uint32_t)hv_glue_region_count - 1;   /* uVar3 */
        uint32_t mid   = hi_idx >> 1;                           /* uVar5 */
        tbl = hv_glue_region_tbl + (uint64_t)mid * 0x10;        /* uVar6 (found region entry) */
        uint32_t reg_hi = (*(uint32_t *)(tbl + 0xc) & 0xffffff) + *(uint32_t *)(tbl + 8);
        uint32_t page  = (uint32_t)(paddr >> 0xe);              /* uVar4 */
        if (page < *(uint32_t *)(tbl + 8) || reg_hi <= page) {
            uint32_t lo_idx = 0;                                /* uVar7 */
            do {
                if (lo_idx == hi_idx) {
                    type = 0x1a;
                    goto store_type;
                }
                if (reg_hi <= page) {
                    lo_idx = mid + 1;
                    mid = hi_idx;
                }
                hi_idx = mid;
                mid = (hi_idx + lo_idx) >> 1;
                tbl = hv_glue_region_tbl + (uint64_t)mid * 0x10;
                reg_hi = (*(uint32_t *)(tbl + 0xc) & 0xffffff) + *(uint32_t *)(tbl + 8);
            } while (page < *(uint32_t *)(tbl + 8) || reg_hi <= page);
        }
    }
    else {
        /* In the main window: index the type-byte table (16 bytes/entry). */
        uint64_t off = (paddr - hv_glue_dram_lo) >> 0xa;
        tbl = hv_glue_type_tbl + (off & 0x3ffffffffffff0ULL);
        tbl = hv_glue_pac_c8a2(hv_glue_type_tbl, tbl);
        if (hv_glue_type_tbl == 0) {
            type = 0x1a;
            goto store_type;
        }
    }
    type = *(uint8_t *)(tbl + 2);
store_type:
    *out = type;
    return 0;
}

/* ======================================================================== *
 * kernel_preempt_dec
 * ======================================================================== */
/* FUN_fffffe000b94172c @ 0xfffffe000b94172c   (est. kernel_preempt_dec)
 * Ghidra: void FUN_fffffe000b94172c(ulong *param_1)
 * Decrements a preemption counter described by param_1[2] (an 8-byte scaled
 * offset into the per-CPU lock word). Fast path: when bit 54 of the target
 * word is clear, cheaply merge the caller's word and release the lock bit.
 * Slow path: acquire the hw lock-bit (spin on b7f8ce0), set the word, call
 * the counter-adjust helper (b815288), release the bit, and decrement the
 * thread preemption counter (b83f58c). Clears *param_1 before returning.
 * Confidence: high
 * Notes: lock bit 0x1d on PTR_s_hw_lock_bit_t_fffffe0007d82e88; deferred
 *   panic context DAT_fffffe000c68af18 / callback data DAT_fffffe0007d82d90.
 * Kernel code recreated for audit (hv-deps). */
void kernel_preempt_dec(uint64_t *param_1)
{
    uint64_t off  = (uint64_t)(uint32_t)param_1[2] * 8;  /* uVar7 */
    long     s32  = (long)(int)off;                      /* iVar6 */
    uint64_t *target = (uint64_t *)(long)s32;

    if (off - (uint64_t)(long)s32 != 0) {
        target = (uint64_t *)hv_glue_pac_2bad(off);
    }
    if ((*target >> 0x36 & 1) == 0) {
        /* Fast path: no preemption pending. */
        if (((*param_1 ^ *target) & 0xdfbfffffffffffffULL) != 0) {
            *target = (*param_1 & 0xffbfffffffffffffULL) | 0x2000000000000000ULL;
        }
        uint64_t p = (uint64_t)(long)s32;
        if (off - (uint64_t)(long)s32 != 0) {
            p = hv_glue_pac_2bad(off);
        }
        kernel_lock_bit_release(p + 4, 0x1d);           /* FUN_fffffe000b7f8ed0 */
    }
    else {
        /* Slow path: serialize, then decrement. */
        uint64_t percpu = tpidr_el1;
        uint8_t  need_restore;
        if (*(int *)(percpu + HV_PCPU_PREEMPT) == 0) {
            need_restore = ((~(uint32_t)daif & 0x1c0) != 0);   /* local_38 (set, never re-read) */
        }
        else {
            need_restore = 0;
        }
        (void)need_restore;
        /* Panic-defer struct built in the caller frame (local_58..local_40). */
        void *panic_defer[4];
        panic_defer[0] = kernel_lock_panic_ctx;        /* local_58 = &DAT_fffffe000c68af18 */
        panic_defer[1] = (void *)0x40000000;           /* local_50 */
        panic_defer[2] = (void *)kernel_preempt_deferred_cb; /* local_48 = FUN_fffffe000b944b00 */
        panic_defer[3] = kernel_lock_cb_data;          /* local_40 = &DAT_fffffe0007d82d90 */
        int rc;
        do {
            uint64_t p = (uint64_t)(long)s32;
            if (off - (uint64_t)(long)s32 != 0) {
                p = hv_glue_pac_2bad(off);
            }
            rc = kernel_lock_bit_wait(p + 4, 0x1d, (void **)&s_hw_lock_bit, (void **)&panic_defer[0]);
        } while (rc == 0);

        target = (uint64_t *)(long)s32;
        if (off - (uint64_t)(long)s32 != 0) {
            target = (uint64_t *)hv_glue_pac_2bad(off);
        }
        *target = (*param_1 & 0xffbfffffffffffffULL) | 0x2000000000000000ULL;
        uint64_t p = (uint64_t)(long)s32;
        if (off - (uint64_t)(long)s32 != 0) {
            p = hv_glue_pac_2bad(off);
        }
        kernel_preempt_adjust((void *)p, 0, 0);         /* FUN_fffffe000b815288 */
        uint64_t q = (uint64_t)(long)s32;
        if (off - (uint64_t)(long)s32 != 0) {
            q = hv_glue_pac_2bad(off);
        }
        kernel_lock_bit_release(q + 4, 0x1d);           /* FUN_fffffe000b7f8ed0 */
        kernel_thread_preempt_dec(param_1 + 1);         /* FUN_fffffe000b83f58c */
    }
    *param_1 = 0;
}

/* ======================================================================== *
 * kernel_memattr_resolve
 * ======================================================================== */
/* FUN_fffffe000b94abbc @ 0xfffffe000b94abbc   (est. kernel_memattr_resolve)
 * Ghidra: undefined8 FUN_fffffe000b94abbc(ulong, uint, ulong, ulong *, ushort)
 * Resolves the memory attributes of a page (entry >> 0xe) given a protection
 * mask (prot), a physical-memory token (token), an output leaf pointer and an
 * "upgrade" mask (upg). For each PV in the token list it derives the
 * writable/executable memory attributes and stores a resolved descriptor in
 * the per-attr table (DAT_fffffe000c5ec610), returning nonzero once at least
 * one leaf resolved. It holds the preemption counter during the walk and
 * issues a TLB flush when the counter returns to 0. Returns 0/1.
 * Confidence: high
 * Notes: EL2 sysreg read UnkSytemRegRead(3,6,0xf,3,0) for the MAIR attribute;
 *   panics (c0e11ec) on an invalid PV head; PAC tag 0x2bad on table indices;
 *   calls kernel_tlb_flush (b96c6d4, sibling) at the tail.
 * Kernel code recreated for audit (hv-deps). */
uint64_t kernel_memattr_resolve(uint64_t entry, uint32_t prot, uint64_t token,
                                uint64_t *leaf, uint16_t upg)
{
    uint64_t paddr    = (entry & 0xffffffff) * 0x4000;   /* uVar5 */
    uint64_t result   = 0;                               /* uVar25 */
    uint64_t *pv_head = 0;                               /* puVar28 */
    uint32_t walk_state = 0;                             /* uVar22 */
    uint32_t pv_index   = 0;                             /* uVar24 */
    uint32_t skip_count = 0;                             /* iVar27 */
    uint16_t memattr_bits = 0;                           /* uVar26 */
    int      has_head;
    uint64_t percpu;

    if (paddr < hv_mem_window_lo || hv_mem_window_hi <= paddr) {
        result = 0;
    }
    else {
        if (leaf == 0) {
            uint32_t tag = token & 3;
            if (tag < 2) {
                pv_head = (tag == 1)
                          ? (uint64_t *)((token & 0xfffffffffffffffcULL) | 0x74c0000000000000ULL)
                          : 0;
                leaf = 0;
            }
            else {
                if (tag != 2) {
                    kernel_panic_assert("%s: invalid PV head 0x%llx for PA 0x%llx @%s:%d");
                }
                pv_head = 0;
                leaf = (uint64_t *)((token & 0xfffffffffffffffcULL) | 0x74c0000000000000ULL);
            }
        }
        else {
            pv_head = 0;
        }

        percpu = tpidr_el1;
        *(int *)(percpu + HV_PCPU_PREEMPT) = *(int *)(percpu + HV_PCPU_PREEMPT) + 1;
        has_head = (pv_head != 0);
        if (pv_head == 0 && leaf == 0) {
            result = 0;
            memattr_bits = 0;
        }
        else {
            result = 0;
            pv_index = 0;
            walk_state = 0;
            memattr_bits = 0;
            long percpu_off = *(long *)(percpu + HV_PCPU_OFF) >> 0x10;

            do {
                if (has_head) {
                    leaf = (uint64_t *)(pv_head[walk_state + 1] & 0xfffffffffffffffcULL);
                    if (leaf == 0) {
                        if ((int)pv_index + skip_count == 0x40) break;
                    }
                }
                if (!has_head || leaf != 0) {
                    if (((uint32_t)(uintptr_t)leaf >> 2 & 1) == 0) {
                        /* ---- resolve this PV leaf ---- */
                        uint64_t pte_word = *leaf;           /* uVar23 */
                        uint64_t *pv_ptr;
                        uint64_t *obj;
                        long     *pv;
                        uint64_t  tmp = 0;
                        uint16_t  abits = 0;
                        int       do_write = 0;
                        if ((~(uint32_t)pte_word & 3) != 0) goto skip_leaf;

                        {
                            uint64_t pv_phys = 0;
                            int lookup_rc = kernel_pv_lookup(leaf, &pv_phys); /* FUN_fffffe000c0fb940 */
                            if (lookup_rc != 0) {
                                pv_phys = 0;
                            }
                            tmp = ((pv_phys - hv_mem_window_lo) >> 0xb) & 0x7fffffff8ULL;
                            pv_ptr = (uint64_t *)(long)(int)tmp;
                            if (tmp != (uint64_t)(long)(int)tmp) {
                                pv_ptr = (uint64_t *)hv_glue_pac_2bad(tmp);
                            }
                        }
                        if ((~(uint32_t)*pv_ptr & 3) != 0) {
                            kernel_panic_assert("%s: invalid PV head 0x%llx for PA 0x%llx @%s:%d");
                        }
                        pv  = (long *)((*pv_ptr & 0x8b3ffffffffffffcULL) | 0x74c0000000000000ULL); /* plVar12 */
                        obj = (uint64_t *)*pv;               /* puVar10 */

                        if (((prot >> 1 & 1) == 0) || ((pte_word >> 0x3b & 1) == 0)) {
                            /* ---- ro/rw path ---- */
                            if (((prot & 1) != 0) && (((uint32_t)pte_word >> 10 & 1) == 0)) {
                                /* writable: set attribute + new pte */
                                tmp = pte_word | 0x400;
                                if ((*(uint8_t *)(obj[4] + 0x4c) & 1) == 0) {
                                    uint64_t shift = pte_word >> 4 & 0xc;
                                    uint64_t mair = UnkSytemRegRead(3, 6, 0xf, 3, 0);
                                    uint64_t oac  = pte_word >> 0x35;
                                    abits = 0x40;
                                    if (((mair >> ((shift | (oac & 3)) << 1) & 3) != 0) ||
                                        ((shift | (oac & 3)) < 10 &&
                                         (((1L << (shift | (oac & 3))) & 0x203U) != 0))) {
                                        abits = 0x40;
                                        if ((pte_word & 0x800000000000000ULL) != 0) {
                                            abits = 0xc0;
                                            tmp = (pte_word & 0xf7ffffffffffffffULL) | 0x400;
                                        }
                                    }
                                }
                                else {
                                    abits = 0x40;
                                }
                                do_write = 1;
                            }
                            /* non-writable, non-exec: no attribute is emitted */
                        }
                        else {
                            /* ---- exec path ---- */
                            if ((*(uint8_t *)(obj[4] + 0x4c) & 1) == 0) {
                                uint64_t shift = pte_word >> 4 & 0xc;
                                uint64_t mair = UnkSytemRegRead(3, 6, 0xf, 3, 0);
                                tmp = pte_word >> 0x35;
                                if (((mair >> ((shift | (tmp & 3)) << 1) & 3) == 0) &&
                                    ((9 < (shift | (tmp & 3)) ||
                                      (((1L << (shift | (tmp & 3))) & 0x203U) == 0)))) {
                                    pte_word = pte_word & 0xffffffffffffff3fULL;
                                    if (obj != &hv_special_owner_block) {
                                        pte_word = *(uint64_t *)(obj[4] + 0x18) | pte_word;
                                    }
                                }
                            }
                            else {
                                pte_word = pte_word & 0xffffffffffffff3fULL;
                                if (obj != &hv_special_owner_block) {
                                    pte_word = *(uint64_t *)(obj[4] + 0x18) | pte_word;
                                }
                            }
                            abits = 0xc0;
                            tmp = (pte_word & 0xf7ffffffffffffffULL) | 0x400;
                            do_write = 1;
                        }

                        if (do_write) {
                            /* write the resolved attribute descriptor */
                            long      pv_phys = pv[1];        /* lVar3 */
                            uint64_t  buf_base = **(uint64_t **)(*pv + 0x20); /* lVar18 */
                            uint32_t  elem_count = *(uint32_t *)(*(long **)(*pv + 0x20) + 9); /* uVar4 */
                            uint64_t  off2 = (uint64_t)elem_count * 0x38;
                            uint64_t  off3 = off2 + 0x10;
                            uint64_t *p1 = (uint64_t *)(buf_base + (int)off3);
                            if (off3 != (uint64_t)(long)(int)off3) {
                                p1 = (uint64_t *)hv_glue_pac_2bad(buf_base + off3);
                            }
                            memattr_bits = (uint16_t)(memattr_bits | abits);
                            uint64_t w1 = *p1;                 /* uVar23 reuse */
                            uint64_t off4 = (uint64_t)(elem_count - 1) * 0x38;
                            long *pv2 = (long *)(buf_base + (int)off4);
                            if (off4 - (long)(int)off4 != 0) {
                                pv2 = (long *)hv_glue_pac_2bad(buf_base + off4);
                            }
                            uint64_t off5 = off2 + 8;
                            uint64_t *p2 = (uint64_t *)(buf_base + (int)off5);
                            if (off5 != (uint64_t)(long)(int)off5) {
                                p2 = (uint64_t *)hv_glue_pac_2bad(buf_base + off5);
                            }
                            uint64_t w2 = *pv2;                /* lVar19 */
                            uint64_t w3 = *p2;                 /* uVar20 */
                            uint64_t off6 = (uint64_t)pv_index * 0x18;
                            uint8_t *out_desc = hv_memattr_table + (uint64_t)(int)off6 + (uint64_t)percpu_off; /* puVar2 */
                            if (off6 != (uint64_t)(long)(int)off6) {
                                out_desc = (uint8_t *)hv_glue_pac_2bad((uint64_t)(uintptr_t)hv_memattr_table +
                                                                       off6 + (uint64_t)percpu_off);
                            }
                            *(uint64_t *)out_desc = obj[1];     /* puVar10[1] */
                            {
                                uint64_t mask = (uint64_t)(uintptr_t)leaf;
                                uint64_t sh   = w1 & 0x3f;
                                uint64_t val  = (((w3 & mask) >> 3) << sh) +
                                                pv_phys +
                                                w2 * (uint64_t)((uint32_t)(mask >> sh) &
                                                                (~(uint32_t)0 << (0xeU - (uint32_t)sh & 0x1f)));
                                *(uint64_t *)(out_desc + 8) = val;
                            }
                            *(uint64_t *)(out_desc + 0x10) = tmp;   /* new_pte */
                            pv_index = (uint32_t)((int)pv_index + 1);
                            result = 1;
                        }
                    }
                    else {
                    skip_leaf:
                        skip_count = skip_count + 1;
                    }
                    if ((int)pv_index + skip_count == 0x40 || !has_head) break;
                }
                if (walk_state == 1) {
                    pv_head = (uint64_t *)*pv_head;
                }
                walk_state = (uint32_t)(walk_state != 1);
                leaf = 0;
                has_head = 1;
            } while (pv_head != 0);

            if ((int)pv_index != 0) {
                kernel_paddr_trace_commit(paddr, *(uint64_t *)(hv_memattr_aux + (uint64_t)percpu_off),
                                          pv_index, 0x80a);      /* FUN_fffffe000c0d84b0 */
            }
        }

        if (memattr_bits != 0 || upg != 0) {
            long off7 = (((paddr - hv_mem_window_lo) >> 0xe) & 0xffffffff) * 2;
            uint16_t *gp = (uint16_t *)(hv_memattr_granule + (uint64_t)(int)off7);
            if (off7 != (long)(int)off7) {
                gp = (uint16_t *)hv_glue_pac_2bad((uint64_t)(uintptr_t)hv_memattr_granule + off7);
            }
            uint16_t old = *gp;
            uint16_t newv;
            do {
                newv = old & ~upg;
                uint16_t *gp2 = (uint16_t *)(hv_memattr_granule + off7);
                gp2 = (uint16_t *)hv_glue_pac_c8a2((uint64_t)(uintptr_t)hv_memattr_granule,
                                                   (uint64_t)(uintptr_t)gp2);
                if (*gp2 == old) break;              /* unchanged -> commit */
                old = *gp2;
            } while (1);
            *gp = newv | memattr_bits;
        }
        if (*(int *)(percpu + HV_PCPU_PREEMPT) == 0) {
            kernel_panic_a();                                    /* FUN_fffffe000c0f1874 */
        }
        int n = *(int *)(percpu + HV_PCPU_PREEMPT) - 1;
        *(int *)(percpu + HV_PCPU_PREEMPT) = n;
        if (n == 0) {
            uint64_t sub = *(uint64_t *)(percpu + HV_PCPU_SUB);
            if ((*(uint8_t *)(sub + HV_PCPU_FLUSH_FLAG) >> 2 & 1) != 0) {
                kernel_tlb_flush();                              /* b96c6d4 — sibling */
            }
        }
    }
    return result;
}

/* ======================================================================== *
 * kernel_trace (wrapper) + kernel_trace_core
 * ======================================================================== */
/* FUN_fffffe000bd30528 @ 0xfffffe000bd30528   (est. kernel_trace)
 * Ghidra: void FUN_fffffe000bd30528(void)
 * Thin wrapper over the trace core (FUN_fffffe000bd310e8): reads the per-CPU
 * base and unconditionally calls the core (both branches are identical). The
 * task brief expected a huge body; the actual wrapper is trivial and the real
 * trace logic lives in kernel_trace_core below, which is transcribed in full.
 * Confidence: high (wrapper); note the header's variadic kernel_trace(int, ...)
 *   corresponds to the 7-arg core, not this no-arg wrapper.
 * Notes: tpidr_el1 read; both paths tail-call FUN_fffffe000bd310e8.
 * Kernel code recreated for audit (hv-deps). */
void kernel_trace(void)
{
    uint64_t percpu = tpidr_el1;
    if (percpu != 0) {
        kernel_trace_core(0, 0, 0, 0, 0, 0, 0);                 /* FUN_fffffe000bd310e8 (args indeterminate) */
        return;
    }
    kernel_trace_core(0, 0, 0, 0, 0, 0, 0);                     /* FUN_fffffe000bd310e8 */
    return;
}

/* FUN_fffffe000bd310e8 @ 0xfffffe000bd310e8   (est. kernel_trace_core)
 * Ghidra: void FUN_fffffe000bd310e8(ulong,long,long,long,long,long,uint)
 * The kernel trace/log core: filters the event id (param_1) against the
 * current trace level (DAT_fffffe000c5c55ac) and, when enabled, appends a
 * trace record to the per-CPU kdebug buffer under the preemption counter.
 * It also emits a debug-exception warning when one of a handful of sensitive
 * event ids fires while debug exceptions are enabled. No return value.
 * Confidence: high
 * Notes: event filter bitmap DAT_fffffe000c72bbe0; per-cpu buffer chain
 *   DAT_fffffe000c648de8/df0; timestamp via UnkSytemRegRead(3,4,0xf,10,6)
 *   (CNTPCT_EL0); NEON_umaxv reproduced by hv_glue_umaxv_u32; panics c0e11ec
 *   / c0f1874; calls kernel_tlb_flush (b96c6d4) when the preempt counter
 *   returns to 0. All callees (bd2d774, b7f89cc, b7f8a60, b968948, b9257c4,
 *   b8563f8) left stubbed (2+ levels in).
 * Kernel code recreated for audit (hv-deps). */
void kernel_trace_core(uint64_t event, uint64_t a2, uint64_t a3, uint64_t a4,
                       uint64_t a5, uint64_t a6, uint32_t flags)
{
    uint32_t eid = (uint32_t)event;                            /* uVar19 */
    uint64_t percpu = tpidr_el1;
    uint64_t lv;

    /* ---- event filtering ---- */
    if (hv_trace_level == 0 || hv_trace_flag == 0) goto done;
    if (hv_trace_level < 3) {
        if (hv_trace_level == 1) {
            if ((flags & 1) != 0) goto done;
        }
        else if ((hv_trace_level != 2) ||
                 ((*(uint8_t *)(hv_trace_event_filter + ((event & 0xffffffff) >> 0x13)) >>
                   (eid >> 0x10 & 7) & 1) == 0)) goto done;
    }
    else if (hv_trace_level == 3) {
        if (eid < hv_trace_id_lo || hv_trace_id_hi < eid) goto done;
    }
    else if (hv_trace_level != 4 ||
             ((((eid & 0xfffffffc) != hv_trace_id_a &&
                (eid & 0xfffffffc) != hv_trace_id_b) &&
               (eid & 0xfffffffc) != hv_trace_id_c) &&
              (eid & 0xfffffffc) != hv_trace_id_d)) goto done;

    /* ---- preemption / proc-filter check ---- */
    {
        uint64_t d = daif;
        uint8_t is_idle;
        if ((~(uint32_t)d & 0x1c0) == 0) {
            uint64_t pc = tpidr_el1;
            is_idle = (*(uint64_t *)(*(uint64_t *)(pc + HV_PCPU_SUB) + 0xd0) == 0);
        }
        else {
            is_idle = 1;
        }
        uint32_t pf = hv_trace_procfilt & 0x50;
        if (((flags >> 1 & 1) == 0) && is_idle &&
            (pf != 0 &&
             ((eid >> 0x10 != 0x140 && (eid & 0xff000000) != 0x7000000)))) {
            percpu = tpidr_el1;
            uint64_t cur = *(uint64_t *)(*(uint64_t *)(percpu + 0x418) + 0x18);
            if (cur != 0) {
                if (pf == 0x40) {
                    if (*(char *)(cur + 0x66) != '\0') goto done;
                }
                else {
                    if (pf != 0x10) {
                        kernel_panic_assert("kdebug: invalid procfilt flags %x @%s:%d");
                    }
                    if (*(char *)(cur + 0x66) == '\0') goto done;
                }
            }
        }
    }

    /* ---- increment preemption counter, emit record ---- */
    percpu = tpidr_el1;
    *(int *)(percpu + HV_PCPU_PREEMPT) = *(int *)(percpu + HV_PCPU_PREEMPT) + 1;
    if ((hv_trace_mode & 1) == 0) {
        if (*(int *)(percpu + HV_PCPU_PREEMPT) == 0) goto preempt_panic;
        lv = *(int *)(percpu + HV_PCPU_PREEMPT) - 1;
        *(int *)(percpu + HV_PCPU_PREEMPT) = (int)lv;
        if (lv == 0) {
            uint64_t sub = *(uint64_t *)(percpu + HV_PCPU_SUB);
            if ((*(uint8_t *)(sub + HV_PCPU_FLUSH_FLAG) >> 2 & 1) != 0) {
                kernel_tlb_flush();
            }
        }
    }
    else {
        uint16_t cpu_idx = *(uint16_t *)(percpu + HV_PCPU_OFF);
        uint8_t *buf = (uint8_t *)(hv_trace_cpu_buf + (uint64_t)cpu_idx * 0x80);
        uint64_t seg;
        uint32_t slot;
        uint32_t cur;
        uint64_t timestamp;
        uint64_t timestamp_base;

        do {
            while (1) {
                slot = *(uint32_t *)(buf + 4);
                if (slot != 0xffffffff) break;
            retry_acquire:
                if ((kernel_trace_buffer_acquire(&hv_trace_lock, hv_trace_bufmeta,
                                                 (uint64_t)cpu_idx) & 1) == 0) {
                    goto trace_done;
                }
            }
            seg = *(uint64_t *)(hv_trace_buf_table + ((uint64_t)slot & 0x1fffff) * 0x10) +
                  (uint64_t)(slot >> 0x15) * 0x20020;
            cur = *(uint32_t *)(seg + 4);
            if (hv_trace_bufmax <= cur) goto retry_acquire;
            if ((hv_trace_procfilt >> 1 & 1) == 0) {
                uint64_t base;
                base = *(uint64_t *)(*(uint64_t *)(percpu + HV_PCPU_SUB) + 0x58);
                do {
                    timestamp_base = base;
                    timestamp = UnkSytemRegRead(3, 4, 0xf, 10, 6);   /* CNTPCT_EL0 */
                    base = *(uint64_t *)(*(uint64_t *)(percpu + HV_PCPU_SUB) + 0x58);
                } while (base != timestamp_base);
            }
            else {
                timestamp_base = UnkSytemRegRead(3, 4, 0xf, 10, 6);
                timestamp = hv_trace_tick_base;
            }
        } while (*(uint32_t *)(seg + 4) != cur);
        *(uint32_t *)(seg + 4) = cur + 1;
        *(int *)(seg + 8) = *(int *)(seg + 8) + 1;
        {
            uint64_t slot_off = (uint64_t)cur * 0x40;
            uint64_t *rec = (uint64_t *)(seg + 0x20 + (uint64_t)(long)(int)slot_off);
            if (slot_off != (uint64_t)(long)(int)slot_off) {
                rec = (uint64_t *)hv_glue_pac_2bad(seg + 0x20 + slot_off);
            }
            rec[0] = timestamp_base + timestamp;
            rec[1] = a2;
            rec[2] = a3;
            rec[3] = a4;
            rec[4] = a5;
            rec[5] = a6;
            *(uint32_t *)(rec + 6) = eid;
            *(uint32_t *)((uint8_t *)rec + 0x34) = (uint32_t)cpu_idx;
        }
    trace_done:
        if (*(int *)(percpu + HV_PCPU_PREEMPT) == 0) goto preempt_panic;
        lv = *(int *)(percpu + HV_PCPU_PREEMPT) - 1;
        *(int *)(percpu + HV_PCPU_PREEMPT) = (int)lv;
        if (lv == 0) {
            uint64_t sub = *(uint64_t *)(percpu + HV_PCPU_SUB);
            if ((*(uint8_t *)(sub + HV_PCPU_FLUSH_FLAG) >> 2 & 1) != 0) {
                kernel_tlb_flush();
            }
        }
        if (hv_trace_post != 0) {
            kernel_trace_emit(event, &event);                  /* FUN_fffffe000b9257c4 */
        }
    }

done:
    /* ---- debug-exception warning for sensitive event ids ---- */
    if (((hv_trace_debug_on & 1) != 0) && (hv_trace_debug_thr <= hv_trace_debug_ctr)) {
        uint32_t lanes[4];
        int is_40c  = -(int)((int16_t)(event >> 0x10) == 0x40c);
        int is_130  = -(int)((eid & 0xfffffffc) == 0x1300008);
        int is_10c  = -(int)((int16_t)(event >> 0x10) == 0x10c);
        int is_105  = -(int)((eid & 0xfffffffc) == 0x1050000);
        lanes[0] = (uint32_t)is_105;
        lanes[1] = (uint32_t)is_40c;
        lanes[2] = (uint32_t)is_130;
        lanes[3] = (uint32_t)is_10c;
        if ((hv_glue_umaxv_u32(lanes) & 1) != 0) {
            uint64_t d = daif;
            if (((uint32_t)d >> 9 & 1) == 0) {
                kernel_panic_assert("%s: debug exceptions enabled in kernel mode @%s:%d");
            }
            d &= 0x1c0;
            if (d != 0x1c0) {
                daif = daif | 0x1c0;
            }
            int locked = kernel_trace_lock_acquire(&hv_trace_debug_lock); /* FUN_fffffe000b7f89cc */
            if (locked != 0) {
                if (((hv_trace_debug_on & 1) != 0) && (hv_trace_debug_thr <= hv_trace_debug_ctr)) {
                    hv_trace_debug_on = 0;
                    kernel_trace_lock_release(&hv_trace_debug_lock);      /* FUN_fffffe000b7f8a60 */
                    kernel_trace_restore_preempt(d != 0x1c0);             /* FUN_fffffe000b968948 */
                    kernel_trace_reg_write(&hv_trace_debug_sink, &hv_trace_debug_on,
                                           0, 0, 0xffffffff);             /* FUN_fffffe000b8563f8 */
                    return;
                }
                kernel_trace_lock_release(&hv_trace_debug_lock);          /* FUN_fffffe000b7f8a60 */
            }
            kernel_trace_restore_preempt(d != 0x1c0);                     /* FUN_fffffe000b968948 */
            return;
        }
    }
    return;

preempt_panic:
    kernel_panic_a();                                           /* FUN_fffffe000c0f1874 */
}

/* ======================================================================== *
 * kernel_boot_arg_get
 * ======================================================================== */
/* FUN_fffffe000c09cbf0 @ 0xfffffe000c09cbf0   (est. kernel_boot_arg_get)
 * Ghidra: undefined4 FUN_fffffe000c09cbf0(byte*, char*, uint*, uint, int)
 * Parses a boot-arguments string (args; the caller passes table+0x6c) looking
 * for the named key (name) and stores its value into *out up to size bytes.
 * Handles whitespace separators, '=' values, numeric sizes (1/2/3/4/8 bytes),
 * string values and a "-"-prefixed default. Returns nonzero (1) on success,
 * 0 otherwise — note the task brief said "returns 0 on success", but the
 * decompile returns 1 on a successful parse.
 * Confidence: high
 * Notes: strncmp b760950 / strlen b7608d0 / parse-value b09d080 /
 *   isdigit callback b09d2b0 / memfill b09d008; default value string
 *   DAT_fffffe00070f1714; whitespace/break masks 0x2000000100000201 /
 *   0x100000201.
 * Kernel code recreated for audit (hv-deps). */
int kernel_boot_arg_get(byte_t *args, char *name, uint32_t *out, uint32_t size, int flag)
{
    int      result = 0;                          /* uVar9 */
    uint64_t parsed = 0;                          /* local_68 */
    uint32_t rem;
    byte_t   c;
    byte_t  *token;
    uint64_t cv;

    if ((size != 0xffffffff) && (*args != 0)) {
        /* skip leading whitespace */
        c = *args;
        while (c == 9 || c == 0x20) {
            args++;
            c = *args;
        }
        if (c == 0) {
            result = 0;
        }
        else {
            result = 0;
            token = args;
            cv = (uint64_t)c;
            do {
                /* scan to next token boundary */
                while ((uint32_t)cv > 0x3d ||
                       ((1L << (cv & 0x3f) & 0x2000000100000201ULL) == 0)) {
                    cv = (uint64_t)token[1];
                    token++;
                }
                if ((kernel_strncmp((char *)args, name, (uint64_t)(token - args)) == 0) &&
                    ((uint64_t)(token - args) == kernel_strlen(name))) {
                    if ((int)cv == 0x2d) {
                        /* token begins with '-': use default value */
                        if (0 < (int)size) {
                            if (flag != 0) {
                                token = (byte_t *)hv_bootarg_default;
                                rem = size;
                                while (1) {
                                    c = *token;
                                    if ((c < 0x21 && (1L << ((uint64_t)c & 0x3f) & 0x100000201ULL) != 0) ||
                                        rem == 0) break;
                                    *(byte_t *)out = c;
                                    rem--;
                                    token++;
                                    out = (uint32_t *)((uint8_t *)out + 1);
                                }
                                *(uint8_t *)out = 0;
                                return 1;
                            }
                            kernel_bootarg_memfill(out, size);
                            return 1;
                        }
                        if (size != 0) return result;
                        return 1;
                    }
                    {
                        /* skip spaces after the key */
                        for (; (c = *token, c == 9 || c == 0x20); token++) {}
                        if (((c == 0) || ((uint32_t)cv == 0x3d)) || (c != 0x3d)) {
                            if (*name == '_') {
                                if (0 < (int)size) {
                                    int n = (0x10 < size) * (int)size + (uint32_t)(0x10 >= size) * 0x11;
                                    while (1) {
                                        n--;
                                        token++;
                                        c = *token;
                                        if ((c < 0x21 && (1L << ((uint64_t)c & 0x3f) & 0x100000201ULL) != 0) ||
                                            n == 0) break;
                                        *(byte_t *)out = c;
                                        out = (uint32_t *)((uint8_t *)out + 1);
                                    }
                                    *(uint8_t *)out = 0;
                                    return 1;
                                }
                                if (size != 0) return result;
                                return 1;
                            }
                            if (flag == 0) {
                                if (kernel_bootarg_parse_value((char *)token, &parsed,
                                                               kernel_bootarg_isdigit, 0) == 0) {
                                    /* store parsed numeric value per size */
                                    if ((int)size < 1) {
                                        if (size == 0) result = 1;
                                    }
                                    else if ((int)size < 3) {
                                        if (size == 1) {
                                            *(char *)out = (char)parsed;
                                            result = 1;
                                        }
                                        else {
                                            if (size != 2) goto store_u32;
                                            *(int16_t *)out = (int16_t)parsed;
                                            result = 1;
                                        }
                                    }
                                    else if (size == 3) {
                                        *out = ((uint32_t)parsed & 0xffffff) |
                                               ((uint32_t)*(uint8_t *)((uint8_t *)out + 3) << 0x18);
                                        result = 1;
                                    }
                                    else if ((size == 4) || (size != 8)) {
                                    store_u32:
                                        *out = (uint32_t)parsed;
                                        result = 1;
                                    }
                                    else {
                                        *(uint64_t *)out = parsed;
                                        result = 1;
                                    }
                                    goto advance_token;
                                }
                                c = *token;
                            }
                            if (c == 0x3d) {
                                uint32_t *dst = out;
                                uint32_t r = size;
                                if ((int)size < 1) {
                                    if (size == 0) result = 1;
                                }
                                else {
                                    while (1) {
                                        token++;
                                        c = *token;
                                        if ((c < 0x21 && (1L << ((uint64_t)c & 0x3f) & 0x100000201ULL) != 0) ||
                                            r - 1 == 0) break;
                                        *(byte_t *)dst = c;
                                        dst = (uint32_t *)((uint8_t *)dst + 1);
                                        r--;
                                    }
                                    *(uint8_t *)dst = 0;
                                    result = 1;
                                }
                            }
                            else {
                                uint32_t *dst = out;
                                byte_t   *src = (byte_t *)hv_bootarg_default;
                                uint32_t r = size;
                                if ((int)size >= 1) {
                                    while (1) {
                                        c = *src;
                                        if ((c < 0x21 && (1L << ((uint64_t)c & 0x3f) & 0x100000201ULL) != 0) ||
                                            r == 0) break;
                                        *(byte_t *)dst = c;
                                        r--;
                                        dst = (uint32_t *)((uint8_t *)dst + 1);
                                        src++;
                                    }
                                    *(uint8_t *)dst = 0;
                                    result = 1;
                                }
                            }
                        }
                        else {
                            args = token + 1;
                        }
                    }
                }
            advance_token:
                /* skip to start of next token */
                for (; cv = (uint64_t)*args,
                       (uint8_t)*args > 0x20 ||
                       ((1L << (cv & 0x3f) & 0x100000201ULL) == 0); args++) {}
                while ((int32_t)cv == 9 || (int32_t)cv == 0x20) {
                    args++;
                    cv = (uint64_t)*args;
                }
                token = args;
            } while ((int32_t)cv != 0);
        }
    }
    return result;
}

/* ======================================================================== *
 * kernel_dt_prop_get
 * ======================================================================== */
/* FUN_fffffe000c09c31c @ 0xfffffe000c09c31c   (est. kernel_dt_prop_get)
 * Ghidra: undefined8 FUN_fffffe000c09c31c(uint*, undefined8, ulong*, uint*)
 * Searches the property list of a device-tree node for a property named
 * (param_2); on a match stores the property data pointer into *val and its
 * length into *size and returns 1; otherwise returns 0xffffffff (-1). The
 * node format: [nprops][child0..] then aligned 0x28-byte property records of
 * the form [name... | len | data...].
 * Confidence: high
 * Notes: bounds-checked against DAT_fffffe0007e9d260/270 (DT region);
 *   property-overflow panic (c0e11ec); strcmp b923854.
 * Kernel code recreated for audit (hv-deps). */
uint64_t kernel_dt_prop_get(uint32_t *node, uint64_t prop_name, uint64_t *val, uint32_t *size)
{
    uint64_t lo = hv_dt_lo;                    /* puVar4 */
    uint64_t hi = hv_dt_hi;                    /* puVar5 */
    uint64_t u;

    if (node != 0) {
        uint32_t *prop = node + 2;             /* puVar7 */
        if ((uint64_t)(uintptr_t)prop < lo || hi < (uint64_t)(uintptr_t)prop) goto bounds_panic;
        if (*node != 0) {
            uint32_t count = 0;                /* uVar8 */
            do {
                uint64_t pp = (uint64_t)(uintptr_t)prop;
                if ((pp < lo || hi < pp) || hi < pp + 9 * 4) goto bounds_panic;
                uint32_t *data = prop + 9;     /* puVar1 */
                uint64_t len  = prop[8];       /* puVar7[8] */
                uint64_t end  = len + (uint64_t)(uintptr_t)data;   /* puVar2 */
                if ((uint64_t)0xffffffffffffffdb < (uint64_t)(uintptr_t)prop ||
                    CARRY8(len, (uint64_t)(uintptr_t)data)) goto overflow_panic;
                if (end < lo || hi < end) goto bounds_panic;
                if (kernel_strcmp((char *)prop, (char *)prop_name) == 0) {
                    *val = (uint64_t)(uintptr_t)data;
                    *size = prop[8];
                    return 1;
                }
                u = (uint64_t)(uintptr_t)prop + prop[8];
                if (CARRY8((uint64_t)(uintptr_t)prop, (uint64_t)prop[8]) ||
                    0xffffffffffffffd8 < u) goto overflow_panic;
                prop = (uint32_t *)((u + 0x27) & 0xfffffffffffffffcULL);
                count++;
            } while (count < *node);
        }
    }
    return 0xffffffff;

bounds_panic:
    kernel_panic_assert("Device tree pointer outside of device tree region: pointer %p, DTEnd %lx @%s:%d");
overflow_panic:
    kernel_panic_assert("Device tree property overflow: prop %p, length 0x%x @%s:%d");
}

/* ======================================================================== *
 * kernel_dt_node_lookup
 * ======================================================================== */
/* FUN_fffffe000c09c084 @ 0xfffffe000c09c084   (est. kernel_dt_node_lookup)
 * Ghidra: void FUN_fffffe000c09c084(int*, char*, ulong*)
 * Walks a device-tree path (path) from node (param_1, or the DT root when 0)
 * resolving each '/'-separated component to a child node by matching its
 * "name" property (kernel_dt_prop_get + strcmp). On success stores the node
 * pointer into *out and returns 1; otherwise returns 0xffffffff (-1).
 * Confidence: high
 * Notes: component buffer capped at 0x40 bytes; DT region bounds checks with
 *   panics (c0e11ec); stack canary check via c0e0620; calls the sibling
 *   kernel_dt_prop_get (c09c31c) and kernel_dt_next_prop (c09c4b8).
 * Kernel code recreated for audit (hv-deps). */
uint64_t kernel_dt_node_lookup(int *node, char *path, uint64_t *out)
{
    char     comp[72];                         /* local_b0 */
    uint64_t canary = hv_stack_canary;         /* local_68 */
    int     *cur    = (int *)hv_dt_lo;         /* piVar7 */
    uint64_t result = 0xffffffff;              /* uVar3 */
    int      rc;
    char     c;

    if (hv_dt_present == 0) goto out;

    for (int i = 0; i < 72; i++) comp[i] = '\0';

    if (node != 0) cur = node;
    if ((uint64_t)(uintptr_t)cur < hv_dt_lo || hv_dt_hi < (uint64_t)(uintptr_t)cur) {
        kernel_panic_assert("Device tree pointer outside of device tree region: pointer %p, DTEnd %lx @%s:%d");
    }
    if ((*path == '/') && (path++, *path == '\0')) {
        /* root path */
        *out = (uint64_t)(uintptr_t)cur;
        result = 1;
    }
    else {
        do {
            int len = 0;
            char *dst;
            while (1) {
                dst = comp + len;
                c = *path;
                if (c == '\0') break;
                if (c == '/') { path++; break; }
                if (len == 0x3f) { dst = comp; break; }
                dst = comp + len;
                len++;
                path++;
                *dst = c;
            }
            *dst = '\0';
            if (comp[0] == '\0') {
                if (*path == '\0') {
                    *out = (uint64_t)(uintptr_t)cur;
                    result = 1;
                }
                else {
                    result = 0xffffffff;
                }
                goto out;
            }
            {
                int *child = cur + 2;           /* piVar6 */
                if ((uint64_t)(uintptr_t)child < hv_dt_lo || hv_dt_hi < (uint64_t)(uintptr_t)child)
                    goto bounds_panic;
                if (cur[1] == 0) { result = 0xffffffff; goto out; }
                uint64_t name_len = 0;          /* local_b8 */
                uint32_t type     = 0;          /* local_bc */
                int nprops = *cur;              /* iVar2 */
                int *prop  = 0;
                if (nprops != 0) {
                    do {
                        if ((uint64_t)(uintptr_t)child + 9 < hv_dt_lo ||
                            hv_dt_hi < (uint64_t)(uintptr_t)(child + 9)) goto bounds_panic;
                        {
                            uint64_t next = (uint64_t)(uintptr_t)child + (uint64_t)(uint32_t)child[8];
                            if (CARRY8((uint64_t)(uintptr_t)child, (uint64_t)(uint32_t)child[8]) ||
                                0xffffffffffffffd8 < next)
                                goto overflow_panic;
                            child = (int *)((next + 0x27) & 0xfffffffffffffffcULL);
                        }
                        nprops--;
                    } while (nprops != 0);
                    if ((uint64_t)(uintptr_t)child < hv_dt_lo || hv_dt_hi < (uint64_t)(uintptr_t)child)
                        goto bounds_panic;
                }
                {
                    uint64_t count = 1;         /* uVar8 */
                    while (1) {
                        rc = (int)kernel_dt_prop_get((uint32_t *)prop, (uint64_t)(uintptr_t)hv_dt_name_prop,
                                                     &name_len, &type);
                        if (rc != 1) { result = 0xffffffff; goto out; }
                        if (kernel_strcmp((char *)name_len, comp) == 0) break;
                        if ((uint32_t)cur[1] <= count) { result = 0xffffffff; goto out; }
                        prop = (int *)kernel_dt_next_prop(prop);   /* FUN_fffffe000c09c4b8 */
                        count++;
                    }
                    result = 0xffffffff;
                    cur = prop;
                    if (prop == 0) break;
                }
            }
        } while (1);
    }
out:
    if (hv_stack_canary != canary) {
        kernel_stack_check_fail(result);        /* FUN_fffffe000c0e0620 */
    }
    return result;

bounds_panic:
    kernel_panic_assert("Device tree pointer outside of device tree region: pointer %p, DTEnd %lx @%s:%d");
overflow_panic:
    kernel_panic_assert("Device tree property overflow: prop %p, length 0x%x @%s:%d");
}

/* ======================================================================== *
 * per_cpu_base  — disassembly reconstruction (decompiler collapsed to panic)
 * ======================================================================== */
/* FUN_fffffe000b866ec4 @ 0xfffffe000b866ec4   (est. per_cpu_base)
 * Ghidra: void FUN_fffffe000b866ec4(void)   [decompiler collapsed body]
 * Per-CPU struct getter (direct callee of the vmapple code). The decompiler
 * collapses the body to a single noreturn panic c0eae44(3) because the real
 * body's PAC'd/unreachable blocks (b866ef0/f10/f34/f40/f54) are removed; this
 * is a disassembly-level reconstruction instead (fallback per AGENTS.md).
 *
 * From the raw instruction stream: load the per-cpu state pointer from
 * [cpu + 0x418], sign/PAC-extend it, validate it against a read-only-zone
 * bound (DAT_fffffe0007d7c988/990), apply a count*offset product check
 * (DAT_fffffe0007d82dc8) and a table-entry == 3 check
 * (DAT_fffffe0007d7c9e8 + ((state>>10)&~0xf)), verify [state] == cpu, then
 * return the per-CPU data pointer [state + 0x28]. Any validation failure
 * panics ("zone_require_ro failed" / "tro ..."). 
 * Confidence: low (assembly reconstruction; addresses from decoded ADRP).
 * Notes: panic callees c0eae44 (zone_require_ro) and c0eb104 (tro).
 * Kernel code recreated for audit (hv-deps). */
void *per_cpu_base(uint64_t cpu)
{
    uint64_t state = *(uint64_t *)(cpu + HV_PCPU_STATE);            /* ldr x1,[x0,#0x418] */
    uint64_t sp    = state | 0x0f00000000000000ULL;                 /* orr x8,x1,#0xf00000000000000 */
    uint64_t lo    = *(uint64_t *)0xfffffe0007d7c988;               /* ldp x10,[x9]  bound lo */
    uint64_t hi    = *(uint64_t *)0xfffffe0007d7c990;               /* ldp ,x9,[x9]  bound hi */
    uint32_t count, prod, w9;

    /* cmp x8,x10 ; ccmp x8,x9,#0x2,cs ; b.cs -> panic(3):
     * panic iff (sp >= lo) && (sp >= hi). */
    if (sp >= lo && sp >= hi) {
        kernel_panic_cpu_ro("zone_require_ro failed: address not in a ro zone (addr: %p) @%s:%d");
    }
    count = *(uint32_t *)0xfffffe0007d82dc8;                        /* ldr w8,[..+#0xdc8] */
    w9    = (uint32_t)(state & 0x3fff);                             /* and w9,w1,#0x3fff */
    prod  = count * (0x4000 - w9);                                  /* sub; mul w9,w8,w9 */
    if ((uint32_t)prod >= count) {                                  /* cmp w9,w8 ; b.cs */
        kernel_panic_cpu_ro("zone_require_ro failed: address not in a ro zone (addr: %p) @%s:%d");
    }
    {
        uint64_t table = *(uint64_t *)0xfffffe0007d7c9e8;           /* ldr x8,[..+#0x9e8] */
        uint64_t idx   = (state >> 0xa) & 0xffffffff0ULL;           /* lsr; and #~0xf */
        uint16_t entry = *(uint16_t *)(table + idx);                /* ldrh w8,[x8] */
        if ((entry & 0x3ff) != 3) {                                 /* and #0x3ff; cmp #3; b.ne */
            kernel_panic_cpu_ro("zone_require_ro failed: address not in a ro zone (addr: %p) @%s:%d");
        }
    }
    if (*(uint64_t *)(state + 0) != cpu) {                          /* ldr x8,[x1]; cmp x8,x0; b.ne */
        kernel_panic_cpu_tro("tro %p points back to %p instead of %p @%s:%d");
    }
    return (void *)*(uint64_t *)(state + HV_PCPU_STATE_DATA);       /* ldr x0,[x1,#0x28]; retab */
}
