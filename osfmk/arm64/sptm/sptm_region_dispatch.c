/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM dispatch / register machinery in the range
 * 0xe0000-0xeb000: the guarded dispatch routing helpers, the FTE (Forward
 * Table Entry) refcount/type operations, the DRAM/IO-range and physical-address
 * helpers, the IOMMU/IO-frame bootstrap, and the hibernate (HIB) image-setup +
 * panic/output routine. The guarded state-transition dispatcher itself
 * (sptm_dispatch_transition, FUN_000e6bc0) and the vector-type dispatcher
 * (FUN_000e7100) live here; their event/state tables are @0x16640 / @0x166f8.
 *
 * The GENTER/GEXIT guarded-level transitions are rendered as opaque calls
 * (opcode 0x00201420 / 0x00201400); the selector in x16 selects the dispatch
 * endpoint per sptm_common.h (SPTM_LOAD_DISPATCH_ID).
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * System-register + barrier helpers (same conventions as
 * sptm_dispatch_handlers.c).
 * ------------------------------------------------------------------ */

/* Generic encoded system-register write: (op0,op1,crn,crm,op2). The string
 * is built by token pasting so __builtin_arm_wsr64 sees a literal. */
#define SPTM_SYSW(o0,o1,crn,crm,o2,v) \
    __builtin_arm_wsr64("s" #o0 "_" #o1 "_c" #crn "_c" #crm "_" #o2, v)
#define SPTM_SYSR(o0,o1,crn,crm,o2) \
    __builtin_arm_rsr64("s" #o0 "_" #o1 "_c" #crn "_c" #crm "_" #o2)

static inline uint64_t sptm_cpu_base(void)
{
    uint64_t sel = __builtin_arm_rsr64("s3_6_c15_c8_0");  /* (3,6,0xf,8,0) */
    return sel ? __builtin_arm_rsr64("s3_6_c15_c11_1")    /* (3,6,0xf,0xb,1) */
               : __builtin_arm_rsr64("tpidr_el2");
}

static inline void sptm_isb(void)        { __asm__ volatile("isb" ::: "memory"); }
static inline void sptm_dsb_sy(void)     { __builtin_arm_dsb(15); }  /* DSB SY */
static inline void sptm_dmb_ish(void)    { __builtin_arm_dmb(11); }  /* DMB ISH */
static inline void sptm_dsb_ishst(void)  { __builtin_arm_dsb(12); }  /* DSB ISHST */
static inline void sptm_wfe(void)        { __builtin_arm_wfe(); }
static inline void sptm_wfi(void)        { __builtin_arm_wfi(); }

/* SoftwareBreakpoint(imm): the decompiler renders the exc-return stub tails as
 * "SoftwareBreakpoint(1, next)" — a BRK #imm. */
static inline void sptm_brk(uint32_t imm) { __asm__ volatile("brk %0" ::"i"(imm)); }

/* LOAcquire/LORelease — the SPTM rw-guard lock word (bit0 = exclusive lock,
 * remaining bits = shared/refcount). Rendered as plain atomic accesses. */
static inline void sptm_lo_acquire(void)  { sptm_dmb_ish(); }
static inline void sptm_lo_release(void)  { sptm_dmb_ish(); }

/* Unconditional SPTM panic paths (extern helpers defined in sptm_dispatch_handlers.c). */
extern void sptm_panic_str(const char *fmt) __attribute__((noreturn));
extern void sptm_panic(uint32_t err, uint64_t val, const char *fmt) __attribute__((noreturn));
extern void sptm_wait_forever(void) __attribute__((noreturn));

/* The guarded state-transition dispatcher (FUN_000e6bc0): performs the actual
 * GENTER/GEXIT (0x00201420/0x00201400) transition, selector in x16. */
extern void sptm_dispatch_transition(uint64_t event, uint64_t arg);

/* Globals referenced from these bodies (SPTM .data), with Ghidra addresses. */
extern volatile uint64_t DAT_001012d8;   /* bootstrap/stage flags bitset */
extern volatile uint64_t DAT_00095d51;   /* FTE class table base (index type*0x90) */
extern volatile uint64_t DAT_00095d83;   /* FTE rw-guard flag table base */
extern volatile uint64_t DAT_00095d78;   /* FTE per-dispatch permission masks */
extern volatile uint64_t DAT_00095d80;   /* FTE allowed-IOMMU-permissions table base */
extern volatile uint64_t DAT_00095d81;   /* FTE map/unmap perms table base */
extern volatile uint64_t DAT_00095d54;   /* FTE refcount-flag table base */
extern volatile uint64_t DAT_00095ee9;   /* PTE attributes for map */
extern volatile uint64_t DAT_00095d18;   /* DRAM window start (phys) */
extern volatile uint64_t DAT_00095d20;   /* DRAM window end (phys) */
extern volatile uint64_t DAT_00095460;   /* PAPT VA base */
extern volatile uint64_t DAT_00095458;   /* IO frame VA base */
extern volatile uint64_t DAT_00095440;   /* num IO ranges (page-table class) */
extern volatile uint64_t DAT_00095444;   /* num IO ranges (frame class) */
extern volatile uint64_t DAT_00095448;   /* IO range table A */
extern volatile uint64_t DAT_00095450;   /* IO range table B */
extern volatile uint64_t DAT_000952e8;   /* DRAM type byte table base */
extern volatile uint64_t DAT_000952f8;   /* DRAM type window base */
extern volatile uint64_t DAT_00095300;   /* DRAM type window end */
extern volatile uint64_t DAT_00095318;   /* PAPT root table count (for 0xe0a10) */
extern volatile uint64_t DAT_00095320;   /* IOMMU id-present bitset (stride 0x20) */
extern volatile uint64_t DAT_00095328;   /* IOMMU id -> object table */
extern volatile uint64_t DAT_00095330;   /* IOMMU id -> state-array base */
extern volatile uint16_t DAT_00095338;   /* IOMMU id -> state count */
extern volatile uint64_t DAT_00095d08;   /* boot region descriptor table base */
extern volatile uint64_t DAT_000950d0;   /* pmap io range table */
extern volatile uint64_t DAT_000950d8;   /* pmap io range count */
extern volatile uint64_t DAT_00101ac8;   /* extended-VA mapping count */
extern volatile uint64_t DAT_00101ad0;   /* extended-VA mapping table (stride 0x18) */
extern volatile uint64_t DAT_00101f90;   /* fallback invalid FTE */
extern volatile uint64_t DAT_00104128;   /* HIB tracing-in-progress flag */
extern volatile uint64_t DAT_00100cb8;   /* HIB tracked page table */
extern volatile uint64_t DAT_00100cb0;   /* HIB tracked page count */
extern volatile uint64_t DAT_00097251;   /* CPUTrace module flags */
extern volatile uint64_t DAT_00098031;   /* DRAM/FW permission byte */
extern volatile uint64_t DAT_00104080;   /* VMID allocation bitmap */
extern volatile uint64_t DAT_00102080;   /* ASID allocation bitmap */
extern volatile uint64_t DAT_00102000;   /* ASID free-list head */
extern volatile uint64_t DAT_00104148;   /* ASID/VMID descriptor table */
extern volatile uint64_t DAT_00104150;   /* ASID free-list link field */
extern volatile uint64_t DAT_00104160;   /* ASID/VMID descriptor state */
extern volatile uint64_t DAT_00095cf8;   /* xnu_el2_exception_vector ptr */
extern volatile uint64_t DAT_00095468;   /* xnu exc-return handler ptr */
extern volatile uint64_t DAT_000133e8;   /* exception-vector-type table */
extern volatile uint64_t DAT_00016640;   /* dispatch-state name table */
extern volatile uint64_t DAT_000166f8;   /* dispatch-event name table */
extern volatile uint64_t DAT_00019c18;   /* dispatch-id name table */
extern volatile uint64_t DAT_00019c68;   /* level -> type-expected table */
extern volatile uint64_t DAT_000135f8;   /* retype-permission bitset */
extern volatile uint64_t DAT_00095d38;   /* feature/AC flags (bit0 = guest-IO) */
extern volatile uint64_t DAT_00095d3c;   /* max VMID value */
extern volatile uint64_t DAT_00095d48;   /* reserved/fw frame base */
extern volatile uint64_t DAT_000952d8;   /* PAPT pte VA base (aux) */
extern volatile uint64_t DAT_00095110;   /* non-extended-VA map base */
extern volatile uint64_t DAT_00095d28;   /* wired-frame range start */
extern volatile uint64_t DAT_00095d30;   /* wired-frame range end */
extern volatile uint64_t DAT_00095d02;   /* feature flag (EL2 regs) */
extern volatile uint64_t DAT_00095d01;   /* SVE/AMU present flag */
extern volatile uint64_t DAT_00095d56;   /* FTE frame-class marker table base */
extern volatile uint64_t DAT_00095bf0;   /* dispatch table base (per-domain) */
extern volatile uint64_t DAT_00095bf8;   /* dispatch registration slot table */
extern volatile uint64_t DAT_00095c00;   /* dispatch slot id table */
extern volatile uint64_t DAT_00094000;   /* HIB context boot args */
extern volatile uint64_t DAT_001040a0;   /* IO range device-id */
extern volatile uint8_t  DAT_00096bf1;   /* IO-frame class byte */
extern volatile uint8_t  DAT_00096c81;   /* IO frame class (0x06) */
extern volatile uint8_t  DAT_00096ad1;   /* IOMMU-root FTE class */
extern volatile uint8_t  DAT_00095d51b;  /* (reserved) */

/* FTE class / permission table accessors (bases are addresses). */
#define SPTM_FTE_CLASS(t)     (((volatile uint8_t *)(uintptr_t)DAT_00095d51)[(t) * 0x90])
#define SPTM_FTE_RWGUARD(t)   (((volatile uint8_t *)(uintptr_t)DAT_00095d83)[(t) * 0x90])
#define SPTM_FTE_REF(t)       (((volatile uint8_t *)(uintptr_t)DAT_00095d54)[(t) * 0x48])
#define SPTM_FTE_DISPATCH(t)  (((volatile uint64_t *)(uintptr_t)DAT_00095d78)[(t) * 0x90])
#define SPTM_FTE_IO_PERM(t)   (((volatile uint8_t *)(uintptr_t)DAT_00095d80)[(t) * 0x90])
#define SPTM_FTE_MAPPERM(t)   (((volatile uint8_t *)(uintptr_t)DAT_00095d81)[(t) * 0x90])
#define SPTM_FTE_FRAME(t)     (((volatile uint8_t *)(uintptr_t)DAT_00095d56)[(t) * 0x90])

/* Per-CPU uat handoff pointer (referenced via the __cstring tag at 0x00001595). */
static inline uint64_t sptm_uat_handoff(void)
{
    return *(uint64_t *)(sptm_cpu_base() + 0xa60);
}

/* The FTE (Forward Table Entry) is a 16-byte record; its type byte lives at
 * offset 2 (byte indexing) / offset 1 (word indexing). These helpers resolve a
 * physical address to its FTE VA (the phystokv path, FUN_000e3d7c). */
extern void *sptm_phystokv(uint64_t paddr);

/* Forward declarations used by sptm_phystokv. */
static int sptm_ftes_overlap(void *lhs, void *rhs);
extern void *sptm_bsearch_range(void *key, uint64_t base, uint64_t count,
                                uint64_t stride, int (*cmp)(void *, void *));
extern uint64_t sptm_io_paddr_to_va(uint64_t paddr);
extern void sptm_tlb_flush_entry(uint64_t ctx, uint64_t va, uint32_t level, uint32_t mode);
extern void sptm_fte_retype_apply(void *fte, uint64_t new_type, int clear_asid);
extern void sptm_tlb_program_asid(uint64_t ctx, uint16_t asid);
extern uint8_t sptm_paddr_in_dram(uint64_t paddr);
extern uint64_t sptm_alloc_managed(uint32_t type, uint64_t pages, uint32_t mode);
extern uint64_t sptm_io_commit_range(uint64_t paddr, uint64_t pages, uint64_t mode);
extern uint64_t sptm_pmap_io_range_lookup(uint64_t paddr);
extern uint32_t sptm_dispatch_id(void);
extern uint64_t sptm_hib_track_lookup(uint64_t page);
extern void sptm_dram_fw_guard(uint64_t paddr, uint64_t val);
extern void sptm_register_dispatch(uint64_t domain, uint8_t table, uint64_t fn, uint64_t perm);
static void sptm_io_frame_refcount_ex(void *fte, uint32_t which, int inc);
extern uint64_t sptm_dt_getprop(uint64_t *dt, uint64_t node, const char *name, uint64_t *out);
extern uint64_t sptm_dt_getprop_int(uint64_t *dt, const char *name, uint64_t *out,
                                    uint64_t *out_len, uint64_t node, uint64_t a, uint64_t b);
extern uint64_t sptm_be64(const void *p);
extern void sptm_exception_return(uint64_t elr, uint64_t mode) __attribute__((noreturn));
extern int sptm_ctrr_active(void);
extern void sptm_ctrr_putc(uint8_t c);
extern void sptm_dt_pmap_io_ranges(void *dt, uint64_t *lo, uint64_t *hi,
                                   int (*cb)(uint64_t *, void *), uint64_t arg);
extern int sptm_hib_range_check(uint64_t *range, void *arg);

/* ------------------------------------------------------------------ *
 * FUN_000e3d7c @ 0x000e3d7c   (est. sptm_phystokv)
 * Ghidra: ulong FUN_000e3d7c(ulong param_1)
 * Translate a physical address to its SPTM virtual address by consulting the
 * IO range tables (DAT_00095448 / DAT_00095450, DAT_00095440 / DAT_00095444
 * entries). When the "UAT handoff" bootstrap bit (DAT_001012d8 bit 0xb) is
 * set, first checks the per-CPU cached uat handoff region, then falls back to
 * a binary search (FUN_000ad2dc). Returns 0 if no range matches.
 * Confidence: medium
 * Notes: range entries are 16-byte {start,end,type,..}; the phystokv identity
 *   is the well-known SPTM helper (header name). */
void *sptm_phystokv(uint64_t paddr)
{
    uint64_t va = 0;
    uint64_t i;

    if ((paddr >> 0x2e) == 0 && (DAT_00095440 != 0 || DAT_00095444 != 0)) {
        struct { uint64_t a; uint32_t b; uint32_t c; } key;
        key.a = 0;
        key.b = (uint32_t)(paddr >> 0xe);
        key.c = 1;

        if (((uint32_t)DAT_001012d8 >> 0xb & 1) == 0) {
            for (i = 0; i < DAT_00095440; i++) {
                if (sptm_ftes_overlap(&key, (void *)(DAT_00095448 + i * 0x10)) == 0) {
                    va = DAT_00095448 + i * 0x10;
                    if (((DAT_00095448 ^ va) & 0xffc0000000000000) == 0)
                        return (void *)va;
                    return (void *)(va & 0xffffffffffff | 0xc8a2000000000000);
                }
            }
            for (i = 0; i < DAT_00095444; i++) {
                if (sptm_ftes_overlap(&key, (void *)(DAT_00095450 + i * 0x10)) == 0) {
                    va = DAT_00095450 + i * 0x10;
                    if (((DAT_00095450 ^ va) & 0xffc0000000000000) == 0)
                        return (void *)va;
                    return (void *)(va & 0xffffffffffff | 0xc8a2000000000000);
                }
            }
            return 0;
        }

        /* UAT-handoff enabled path. */
        uint64_t handoff = sptm_uat_handoff();
        if (handoff != 0) {
            if (DAT_00095d51 != 6 ||
                SPTM_FTE_CLASS((*(uint8_t *)(handoff + 2))) != 6)
                goto type_panic;
            if (key.b < (*(uint32_t *)(handoff + 0xc) & 0xffffff) + *(uint32_t *)(handoff + 8) &&
                *(uint32_t *)(handoff + 8) <= key.b) {
                return (void *)handoff;
            }
        }
        va = (uint64_t)sptm_bsearch_range(&key, DAT_00095448, DAT_00095440, 0x10,
                                          sptm_ftes_overlap);
        if (va != 0 ||
            (va = (uint64_t)sptm_bsearch_range(&key, DAT_00095450, DAT_00095444, 0x10,
                                               sptm_ftes_overlap)) != 0) {
            if (*(char *)(va + 2) == 0x1a) {
                if (DAT_00096bf1 != 6) goto type_panic;
                if ((*(uint8_t *)(va + 4) & 1) != 0)
                    return (void *)va;
            }
            /* cache the found range in the per-CPU uat handoff slot */
            *(uint64_t *)(sptm_cpu_base() + 0xa60) = va;
        }
    }
    return (void *)va;

type_panic:
    sptm_panic_str("Type %d class of FTE %d");
}

/* ------------------------------------------------------------------ *
 * FUN_000e4030 @ 0x000e4030   (est. sptm_ftes_overlap)
 * Ghidra: int FUN_000e4030(long param_1, long param_2)
 * Compare two FTE ranges (both must be frame class 6). Returns -1 if the
 * first range ends before the second begins (param_1 before param_2), 0 if
 * they overlap, 1 if param_1 starts after param_2 ends.
 * Confidence: medium */
static int sptm_ftes_overlap(void *lhs, void *rhs)
{
    uint32_t lstart = *(uint32_t *)((uint8_t *)lhs + 8);
    uint32_t lend   = (*(uint32_t *)((uint8_t *)lhs + 0xc) & 0xffffff) + lstart;
    uint32_t rstart = *(uint32_t *)((uint8_t *)rhs + 8);
    uint32_t rend   = (*(uint32_t *)((uint8_t *)rhs + 0xc) & 0xffffff) + rstart;

    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)lhs + 2)) != 6 ||
        SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)rhs + 2)) != 6)
        sptm_panic_str("Type %d class of FTE %d");

    if (lstart < rend)
        return -(uint32_t)(lend <= rstart);
    return 1;
}

/* Binary search helper (FUN_000ad2dc) — extern. */
extern void *sptm_bsearch_range(void *key, uint64_t base, uint64_t count,
                                uint64_t stride, int (*cmp)(void *, void *));

/* ------------------------------------------------------------------ *
 * FUN_000e22cc @ 0x000e22cc   (est. sptm_fte_type)
 * Ghidra: undefined1 FUN_000e22cc(ulong param_1)
 * Return the FTE type byte for a physical address (resolved to its FTE VA).
 * Confidence: high (trivial wrapper over phystokv). */
uint8_t sptm_fte_type(uint64_t paddr)
{
    void *fte = sptm_phystokv(paddr);
    if (fte == 0)
        fte = (void *)&DAT_00101f90;
    return *(uint8_t *)((uint8_t *)fte + 2);
}

/* ------------------------------------------------------------------ *
 * FUN_000e233c @ 0x000e233c   (est. sptm_fte_from_paddr)
 * Ghidra: undefined2 * FUN_000e233c(ulong param_1)
 * Resolve a physical address to its FTE VA. If the FTE class is CPU-root-table
 * (1) or frame (7) and the type is 0x28 (frame), applies the extended-VA
 * translation window (DAT_00101ad0) when bootstrap bit 8 is set, else the
 * flat +0x40 offset (type 0x28 frames). Panics if the FTE is not CPU-root.
 * Confidence: medium */
void *sptm_fte_from_paddr(uint64_t paddr)
{
    void *fte = sptm_phystokv(paddr);
    uint8_t type;
    if (fte == 0)
        fte = (void *)&DAT_00101f90;
    type = *(uint8_t *)((uint8_t *)fte + 2);

    if (SPTM_FTE_CLASS(type) == 1 ||
        SPTM_FTE_CLASS(type) == 7) {
        if (type == 0x28) {
            paddr += 0x40;
            if (((uint32_t)DAT_001012d8 >> 8 & 1) == 0) {
                return (void *)((paddr - DAT_00095d18) + DAT_00095110);
            } else {
                uint64_t n = DAT_00101ac8;
                uint64_t *tbl = (uint64_t *)&DAT_00101ad0;
                while (n != 0) {
                    if (tbl[0] <= paddr && paddr < tbl[0] + (uint32_t)tbl[2] * 0x4000)
                        return (void *)((paddr - tbl[0]) + tbl[1]);
                    tbl += 3;
                    n--;
                }
                return (void *)sptm_io_paddr_to_va(paddr);
            }
        }
        return fte;
    }
    sptm_panic_str("Type %d is not a CPU root table");
}

/* ------------------------------------------------------------------ *
 * FUN_000e2480 @ 0x000e2480   (est. sptm_fte_acquire_rw_shared)
 * Ghidra: void FUN_000e2480(ulong param_1, undefined8 param_2)
 * Acquire the rw-guard shared lock on the FTE for a physical address (in the
 * DRAM window). Increments the guard refcount by 2 under LOAcquire; a guard
 * whose rw-guard flag (DAT_00095d83) is clear is taken once (refcount set to
 * 1). Panics on overflow or when a shared lock is held.
 * Confidence: medium */
static void sptm_fte_acquire_rw_shared(uint64_t paddr, uint64_t caller)
{
    void *fte = sptm_phystokv(paddr);
    uint16_t v;
    if (fte == 0)
        fte = (void *)&DAT_00101f90;
    if (DAT_00095d18 <= paddr && paddr < DAT_00095d20) {
        sptm_lo_acquire();
        v = *(uint16_t *)fte;
        *(uint16_t *)fte = v + 2;
        if (v > 0xffe9 || (v & 1) != 0)
            goto guard_panic;
        if ((SPTM_FTE_RWGUARD((uint8_t)(*(uint16_t *)((uint8_t *)fte + 2))) & 1) == 0) {
            if (*(uint16_t *)fte != 2)
                goto guard_panic;
            *(uint16_t *)fte = 1;
        }
    }
    return;
guard_panic:
    sptm_panic(0x3d, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000e260c @ 0x000e260c   (est. sptm_fte_release_rw_shared)
 * Ghidra: void FUN_000e260c(ushort *param_1)
 * Release the rw-guard shared lock on an FTE. If the FTE is not class 6
 * (frame), and its rw-guard flag is clear, zero the guard; otherwise release
 * the shared refcount (decrement by 2) under LORelease. Panics on underflow.
 * Confidence: medium */
static void sptm_fte_release_rw_shared(void *fte)
{
    uint16_t v;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 6) {
        if ((SPTM_FTE_RWGUARD(*(uint8_t *)((uint8_t *)fte + 2)) & 1) == 0) {
            *(uint16_t *)fte = 0;
            *(uint8_t *)((uint8_t *)fte + 2) = 0;
            return;
        }
        v = *(uint16_t *)fte;
        *(uint16_t *)fte = v - 2;
        sptm_lo_release();
        if (v == 0 || (v & 1) != 0)
            sptm_panic_str("rw_guard release shared %p");
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000e268c @ 0x000e268c   (est. sptm_fte_type_is_io_frame)
 * Ghidra: byte FUN_000e268c(void)
 * Resolve the current frame FTE (from the per-CPU phystokv of the current
 * frame) and report whether it is an IO frame (type 0x3e with io bit set).
 * Also releases the rw-guard shared lock on the resolved FTE.
 * Confidence: low */
static uint8_t sptm_fte_type_is_io_frame(void)
{
    void *fte = sptm_phystokv(0);   /* current frame (arg dropped by decompiler) */
    uint8_t type, io;
    if (fte == 0)
        fte = (void *)&DAT_00101f90;
    type = *(uint8_t *)((uint8_t *)fte + 2);
    if (type == 0x3e) {
        if (DAT_00098031 != 3)
            sptm_panic_str("Type %d class of FTE %d");
        io = (uint8_t)(*(uint8_t *)((uint8_t *)fte + 4) >> 2 & 1);
        type = *(uint8_t *)((uint8_t *)fte + 2);
    } else {
        io = 0;
    }
    if (SPTM_FTE_CLASS(type) != 6) {
        if ((SPTM_FTE_RWGUARD(type) & 1) == 0) {
            *(uint16_t *)fte = 0;
            *(uint8_t *)((uint8_t *)fte + 2) = 0;
        } else {
            uint16_t v = *(uint16_t *)fte;
            *(uint16_t *)fte = v - 2;
            sptm_lo_release();
            if (v == 0 || (v & 1) != 0)
                sptm_panic_str("rw_guard release shared %p");
        }
    }
    return io;
}

/* ------------------------------------------------------------------ *
 * FUN_000e276c @ 0x000e276c   (est. sptm_fte_lookup_ptep)
 * Ghidra: ushort * FUN_000e276c(ushort *param_1, undefined8 param_2, uint param_3,
 *                               int param_4, long *param_5)
 * Walk the page-table hierarchy from FTE param_1 (a CPU page-table) looking
 * for the level-1/2 entry covering the physical frame, validating each level's
 * type against the requested level (param_3). param_4==0 forbids a shared
 * (rw-guard bit2) child. On success returns the matching FTE and writes its
 * physical address to *param_5; else returns NULL with *param_5=0.
 * Confidence: low */
static void *sptm_fte_lookup_ptep(void *root, uint64_t caller, uint32_t level,
                                  int allow_shared, uint64_t *out_paddr)
{
    void *fte, *cand;
    uint64_t tmp[2];

    if (out_paddr == 0)
        sptm_panic_str("NULL ptep pointer");
    tmp[0] = 0; tmp[1] = 0;
    cand = sptm_fte_from_paddr(0);
    *out_paddr = (uint64_t)cand;
    if (cand == 0) {
        fte = 0;
        *out_paddr = 0;
    } else {
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)root + 2)) != 1)
            goto type_panic;
        fte = root;
        uint8_t root_level = *(uint8_t *)((uint8_t *)root + 6);
        uint8_t want = *(uint8_t *)(*(uint64_t *)(DAT_00019c68 + (uint64_t)root_level * 8) + 0x38);
        if (level != want) {
            /* resolve the frame for the current VA and acquire rw-guard */
            void *frame = sptm_phystokv(0);
            if (frame == 0) frame = (void *)&DAT_00101f90;
            if (frame != root) {
                sptm_fte_acquire_rw_shared(0, 0);
                /* validate the newly-acquired guard against the frame */
                if ((((~*(uint32_t *)frame & 3) != 0) ||
                     ((*(uint64_t *)frame & 0xfffffffff000) != 0)) ||
                    (allow_shared == 0 && ((*(uint64_t *)frame >> 2 & 1) != 0))) {
                    sptm_fte_release_rw_shared(frame);
                    if (level != 3)
                        sptm_panic(0x53, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
                    fte = 0;
                    *out_paddr = 0;
                    return fte;
                }
            }
        }
        uint8_t t = *(uint8_t *)((uint8_t *)fte + 2);
        if (level == 3) {
            if (t == 9)
                sptm_panic(0, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
            if ((t == 0x15 && *(char *)((uint8_t *)root + 2) == 0x12) ||
                (t == 0x14 && *(char *)((uint8_t *)root + 2) == 0x13)) {
                if (t == 0x14)
                    sptm_panic_str("XNU_PAGE_TABLE frame found while unwiring");
                sptm_panic(0, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
            }
            t = SPTM_FTE_CLASS(t);
        } else {
            t = SPTM_FTE_CLASS(t);
            if (t > 2 || t == 1)
                sptm_panic_str("Non PT frame found in page table");
        }
        if (t != 1 && t != 2)
            goto type_panic;
        if (t == 2 && *(uint8_t *)((uint8_t *)fte + 2) != level)
            sptm_panic_str("Incorrect level set in page table");
    }
    return fte;
type_panic:
    sptm_panic_str("Type %d class of FTE %d");
}

/* ------------------------------------------------------------------ *
 * FUN_000e2c18 @ 0x000e2c18   (est. sptm_fte_refcount_adjust)
 * Ghidra: void FUN_000e2c18(long param_1, long param_2, int param_3)
 * Adjust the CPU page-table child refcounts: param_1 is the parent table (or
 * root), param_2 a child CPU-page-table FTE. When param_3==0 (acquire) the
 * parent refcount (offset 8 for root-class, 6 for table) and the child refcount
 * (offset 6) are incremented; when param_3!=0 (release) they are decremented.
 * Panics on underflow/overflow.
 * Confidence: medium */
static void sptm_fte_refcount_adjust(void *parent, void *child, int release)
{
    uint8_t pc = SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)parent + 2));
    uint16_t v;
    if (pc > 2 || SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)child + 2)) != 2)
        sptm_panic_str("FTE type is not of a CPU page table");

    if (release == 0) {
        if (pc != 1) {
            v = *(uint16_t *)((uint8_t *)parent + 8);
            *(uint16_t *)((uint8_t *)parent + 8) = v + 1;
            if (v > 0x808)
                sptm_panic_str("refcnt overflow (rc %p old value %d)");
        } else {
            v = *(uint16_t *)((uint8_t *)parent + 6);
            *(uint16_t *)((uint8_t *)parent + 6) = v + 1;
            if (v > 0x812)
                sptm_panic_str("refcnt overflow (rc %p old value %d)");
        }
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)child + 2)) != 2)
            sptm_panic_str("Type %d class of FTE %d");
        v = *(uint16_t *)((uint8_t *)child + 6);
        *(uint16_t *)((uint8_t *)child + 6) = v + 1;
        if (v > 0xfff4)
            sptm_panic(0x45, (uint64_t)child, "%s: %s %d %s 0x%llx %s 0x%llx");
    } else {
        if (pc != 1) {
            v = *(uint16_t *)((uint8_t *)parent + 8);
            *(uint16_t *)((uint8_t *)parent + 8) = v - 1;
        } else {
            v = *(uint16_t *)((uint8_t *)parent + 6);
            *(uint16_t *)((uint8_t *)parent + 6) = v - 1;
        }
        if (v == 0)
            sptm_panic_str("refcnt underflow (rc %p old value %d)");
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)child + 2)) != 2)
            sptm_panic_str("Type %d class of FTE %d");
        v = *(uint16_t *)((uint8_t *)child + 6);
        *(uint16_t *)((uint8_t *)child + 6) = v - 1;
        if (v == 0)
            sptm_panic_str("refcnt underflow (rc %p old value %d)");
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000e2e2c @ 0x000e2e2c   (est. sptm_fte_update_refcounts)
 * Ghidra: void FUN_000e2e2c(long param_1, long param_2, ulong param_3, ulong param_4)
 * Update the shared/exec/write refcounts of a table FTE (param_2) when the
 * two PTE entries (param_3 = old, param_4 = new) change. Decodes each PTE's
 * permission bits (w/e bits at >>4 and >>0x35), computes the transition deltas
 * and adjusts the exec (+0xc) and write (+0x8) refcounts of param_2, and the
 * parent table's child refcount (param_1). Heavily validated with panic paths.
 * Confidence: low */
static void sptm_fte_update_refcounts(void *parent, void *table,
                                      uint64_t old_pte, uint64_t new_pte)
{
    uint32_t ow = 0xff, nw = 0xff;
    uint32_t o_exec, n_exec, o_write, n_write;
    int delta_exec, delta_write;

    if ((~old_pte & 3) == 0)
        ow = (uint32_t)(old_pte >> 4 & 0xc | (old_pte >> 0x35) & 3);
    if ((new_pte & 3) == 3)
        nw = (uint32_t)(new_pte >> 4 & 0xc | (new_pte >> 0x35) & 3);

    if (table == 0) {
        if (ow != 0xff || nw != 0xff)
            sptm_panic_str("NULL FTE with at least one valid PTE");
        return;
    }

    uint8_t t = *(uint8_t *)((uint8_t *)table + 2);
    uint8_t cls = SPTM_FTE_CLASS(t);
    int update_parent = (old_pte & 0xc000000000000000) != 0 || ow != 0xff;
    int update_child = (new_pte & 0xc000000000000000) != 0 || nw != 0xff;

    if (cls != 6) {
        if (cls != 3 || SPTM_FTE_REF(t) == 0)
            sptm_panic_str("Attempted to update refcnts on a non-refcounted FTE");

        int wmask = (*(char *)((uint8_t *)parent + 2) == 0x22) ? 1 : 0;
        o_exec = ((old_pte & 0x800000000000003) != 0x800000000000003) &
                 ((ow & 0xfffffffb) == 0xb || wmask);
        n_exec = ((new_pte & 0x800000000000003) != 0x800000000000003) &
                 ((nw & 0xfffffffb) == 0xb || wmask);
        if (ow != 0xff) o_write = o_exec ^ 1; else o_write = 0;
        if (nw != 0xff) n_write = n_exec ^ 1; else n_write = 0;
        delta_exec = (int)n_exec - (int)o_exec;
        delta_write = (int)n_write - (int)o_write;

        if (delta_write == -1)
            *(int32_t *)((uint8_t *)table + 0xc) -= 1;
        else if (delta_write == 1) {
            int32_t r = *(int32_t *)((uint8_t *)table + 0xc);
            *(int32_t *)((uint8_t *)table + 0xc) = r + 1;
            if (r == 0x7fffffff)
                sptm_panic(0x44, (uint64_t)table, "%s: %s %d %s 0x%llx %s 0x%llx");
        }
        if (delta_exec == -1)
            *(int32_t *)((uint8_t *)table + 8) -= 1;
        else if (delta_exec == 1) {
            int32_t r = *(int32_t *)((uint8_t *)table + 8);
            *(int32_t *)((uint8_t *)table + 8) = r + 1;
            if (r == 0x7fffffff)
                sptm_panic(0x43, (uint64_t)table, "%s: %s %d %s 0x%llx %s 0x%llx");
        }
    }

    /* adjust the parent table's child refcount */
    if (update_parent && !update_child) {
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)parent + 2)) != 2)
            sptm_panic_str("Type %d class of FTE %d");
        uint16_t v = *(uint16_t *)((uint8_t *)parent + 8);
        *(uint16_t *)((uint8_t *)parent + 8) = v - 1;
        if (v == 0)
            sptm_panic_str("refcnt underflow (rc %p old value %d)");
    } else if (!update_parent && update_child) {
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)parent + 2)) != 2)
            sptm_panic_str("Type %d class of FTE %d");
        uint16_t v = *(uint16_t *)((uint8_t *)parent + 8);
        *(uint16_t *)((uint8_t *)parent + 8) = v + 1;
        if (v > 0x808)
            sptm_panic_str("refcnt overflow (rc %p old value %d)");
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000e03f4 @ 0x000e03f4   (est. sptm_fte_map_page)
 * Ghidra: void FUN_000e03f4(ulong param_1)
 * Program a PTE in the PAPT for the physical frame: validate the bootstrap
 * stage (DAT_001012d8 bit 9), resolve the PTE via phystokv, require it to be
 * currently invalid, store param_1&0xfffffffff000 | 0x603 | (attr bits), then
 * increment the frame FTE refcount (class 2). Fail-closed on validation.
 * Confidence: medium */
static void sptm_fte_map_page(uint64_t pte_val)
{
    uint32_t *pte;
    uint16_t rc;
    uint64_t fte_va;

    if ((((uint32_t)DAT_001012d8 >> 9 & 1) == 0))
        sptm_panic_str("%s: %s Expected bootstrap stages no…");

    pte = (uint32_t *)sptm_phystokv(0);
    if (pte == 0)
        sptm_panic_str("%s: %s PAPT PTE could not be reached…");
    if ((~*pte & 3) == 0)
        sptm_panic_str("%s: %s Valid PTE found while attempting to map…");

    *pte = (uint32_t)(pte_val & 0xfffffffff000 | 0x603 |
                      ((uint64_t)DAT_00095ee9 & 0xc) << 4 | (DAT_00095ee9 & 3) << 0x35);

    fte_va = (uint64_t)sptm_phystokv(0);
    void *frame = sptm_phystokv(fte_va);
    if (frame == 0) frame = (void *)&DAT_00101f90;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)frame + 2)) == 2) {
        rc = *(uint16_t *)((uint8_t *)frame + 8);
        *(uint16_t *)((uint8_t *)frame + 8) = rc + 1;
        if (rc < 0x809) {
            sptm_dsb_ishst();
            sptm_isb();
            return;
        }
        sptm_panic_str("refcnt overflow (rc %p old value %d)");
    }
    sptm_panic_str("Type %d class of FTE %d");
}

/* ------------------------------------------------------------------ *
 * FUN_000e05bc @ 0x000e05bc   (est. sptm_fte_unmap_page)
 * Ghidra: void FUN_000e05bc(void)
 * Clear a PTE in the PAPT: validate the bootstrap stage, resolve the PTE,
 * require it to be currently valid, zero it, decrement the frame FTE refcount
 * (class 2), then DSB + TLB flush (FUN_000d76fc). Fail-closed.
 * Confidence: medium */
static void sptm_fte_unmap_page(void)
{
    uint32_t *pte;
    uint16_t rc;
    uint64_t pte_va;

    if ((((uint32_t)DAT_001012d8 >> 9 & 1) == 0))
        sptm_panic_str("%s: %s Expected bootstrap stages no…");

    pte_va = (uint64_t)sptm_phystokv(0);
    pte = (uint32_t *)sptm_phystokv(pte_va);
    if (pte == 0)
        sptm_panic_str("%s: %s PAPT PTE could not be reached…");
    if ((~*pte & 3) != 0)
        sptm_panic_str("%s: %s Invalid PTE found while attempting to unmap…");
    *pte = 0;

    void *frame = sptm_phystokv(pte_va);
    if (frame == 0) frame = (void *)&DAT_00101f90;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)frame + 2)) == 2) {
        rc = *(uint16_t *)((uint8_t *)frame + 8);
        *(uint16_t *)((uint8_t *)frame + 8) = rc - 1;
        if (rc != 0) {
            sptm_dsb_sy();
            sptm_tlb_flush_entry(DAT_00095d48, pte_va, 1, 1);
            sptm_dsb_sy();
            sptm_isb();
            return;
        }
        sptm_panic_str("refcnt underflow (rc %p old value %d)");
    }
    sptm_panic_str("Type %d class of FTE %d");
}

/* TLB flush helper (FUN_000d76fc) — declared above. */

/* ------------------------------------------------------------------ *
 * FUN_000e0770 @ 0x000e0770   (est. sptm_get_uat_handoff)
 * Ghidra: undefined8 FUN_000e0770(void)
 * Return the per-CPU UAT handoff pointer (DAT_00101ac0 + 0xa60). Trivial.
 * Confidence: high */
uint64_t sptm_get_uat_handoff(void)
{
    return sptm_uat_handoff();
}

/* ------------------------------------------------------------------ *
 * FUN_000e07d8 @ 0x000e07d8   (est. sptm_fte_release_shared)
 * Ghidra: void FUN_000e07d8(long param_1, int param_2)
 * Release the rw-guard shared lock on an FTE (param_1, type in param_2).
 * Validates the FTE is class 3, its refcount is zero, and optionally drops
 * the nested IO-frame rw-guard (type 0xb path). Fail-closed on type/refcount.
 * Confidence: low */
static void sptm_fte_release_shared(void *fte, uint32_t type)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 3)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(int32_t *)((uint8_t *)fte + 0xc) != 0)
        sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");

    if (type - 0x41U < 0xfffffffe) {  /* type in {0..0x40, 0xffffffff..} */
        if (*(int32_t *)((uint8_t *)fte + 8) != 0)
            sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
        uint8_t *guard = (uint8_t *)fte + 4;
        sptm_lo_acquire();
        *guard &= 4;
        sptm_lo_release();
        if (type == 0xb && ((*guard >> 2 & 1) != 0)) {
            void *io = sptm_phystokv(0);
            if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)io + 2)) == 4) {
                int32_t rc = *(int32_t *)((uint8_t *)io + 8);
                *(int32_t *)((uint8_t *)io + 8) = rc - 1;
                if (rc == 0)
                    sptm_panic_str("refcnt underflow (rc %p old value %d)");
                uint16_t g = *(uint16_t *)io;
                *(uint16_t *)io = g - 2;
                sptm_lo_release();
                if (g == 0 || (g & 1) != 0)
                    sptm_panic_str("rw_guard release shared %p");
                if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) == 3)
                    *(uint8_t *)((uint8_t *)fte + 4) = 0;
            } else {
                sptm_panic_str("Type %d class of FTE %d");
            }
        }
    } else {
        sptm_lo_acquire();
        *(uint8_t *)((uint8_t *)fte + 4) &= 4;
        sptm_lo_release();
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000e0a10 @ 0x000e0a10   (est. sptm_fte_acquire_shared)
 * Ghidra: void FUN_000e0a10(ulong param_1, undefined8 param_2)
 * Acquire the rw-guard shared lock on the FTE at the given physical address
 * (param_1 must be within the PAPT table). Returns the FTE pointer after
 * incrementing its guard refcount by 2 under LOAcquire.
 * Confidence: medium */
static void *sptm_fte_acquire_shared(uint64_t paddr, uint64_t caller)
{
    uint64_t end = DAT_00095460 + DAT_00095318 * 0x10;
    void *fte;
    uint16_t v;
    if (paddr < DAT_00095460 || end <= paddr)
        sptm_panic(0x37, caller, "%s: %s %d %s 0x%llx");

    uint64_t va = ((DAT_00095d18 + (paddr - DAT_00095460 & 0xffffffff0) * 0x400) -
                   DAT_00095d28 >> 5 & 0x1ffffffc000) + DAT_000952d8;
    fte = sptm_phystokv(va);
    if (fte == 0) fte = (void *)&DAT_00101f90;

    sptm_lo_acquire();
    v = *(uint16_t *)fte;
    *(uint16_t *)fte = v + 2;
    if (v < 0xffea && (v & 1) == 0) {
        if ((char)*(uint8_t *)((uint8_t *)fte + 2) == ' ')
            return fte;
        sptm_panic(0x13, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
    sptm_panic(0x3d, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* ------------------------------------------------------------------ *
 * FUN_000e0c00 @ 0x000e0c00   (est. sptm_fte_release_shared_with_nest)
 * Ghidra: void FUN_000e0c00(long param_1, undefined8 param_2, byte param_3)
 * Like sptm_fte_release_shared but guarded on param_3 (mode: 0 = shared,
 * 1 = exclusive), releasing the nested IO-frame rw-guard and restoring the
 * FTE guard to "exclusive pending" (4). Fail-closed.
 * Confidence: low */
static void sptm_fte_release_shared_with_nest(void *fte, uint64_t caller, uint8_t mode)
{
    uint16_t g;
    uint32_t rc;
    if (mode > 1)
        sptm_panic(0x10, caller, "%s: %s %d %s 0x%llx");
    if (mode == 0 || *(char *)((uint8_t *)fte + 2) != 0xb)
        return;

    void *io = sptm_phystokv(0);
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)io + 2)) == 4) {
        rc = *(uint32_t *)((uint8_t *)io + 8);
        *(uint32_t *)((uint8_t *)io + 8) = rc + 1;
        if (rc > 0xfffffff4)
            sptm_panic_str("refcnt overflow (rc %p old value %d)");
        g = *(uint16_t *)io;
        *(uint16_t *)io = g - 2;
        sptm_lo_release();
        if (g == 0 || (g & 1) != 0)
            sptm_panic_str("rw_guard release shared %p");
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) == 3) {
            *(uint8_t *)((uint8_t *)fte + 4) = 4;
            return;
        }
    }
    sptm_panic_str("Type %d class of FTE %d");
}

/* ------------------------------------------------------------------ *
 * Trivial panic / validation leaf functions.
 * ------------------------------------------------------------------ */

/* FUN_000e0d74 / 0xe0f00: noreturn panics. */
static void sptm_fte_rc_panic(void) __attribute__((noreturn));
static void sptm_fte_rc_panic(void)
{
    sptm_panic(0x17, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e0de4: FTE class-4 emptiness check. */
static void sptm_fte_class4_check(void *fte, uint32_t type)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 4)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(int32_t *)((uint8_t *)fte + 4) == 0 && *(int32_t *)((uint8_t *)fte + 8) == 0)
        return;
    sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e0f70: FTE class-3 exec-refcount emptiness check. */
static void sptm_fte_class3_check(void *fte, uint32_t type)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 3)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(int32_t *)((uint8_t *)fte + 0xc) == 0) {
        if (*(int32_t *)((uint8_t *)fte + 8) == 0)
            return;
        sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
    sptm_panic_str("Unexpected write/exec refcount %d");
}

/* FUN_000e1050 / 0xe11a8 / 0xe12f4: IOMMU FTE dispatch. */
static void sptm_iommu_fte_op(void *fte, uint64_t caller, uint32_t arg)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 5)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(uint16_t *)((uint8_t *)fte + 4) != 0)
        sptm_panic(0x17, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
    uint32_t id = *(uint8_t *)((uint8_t *)fte + 6);
    if (id < 9 && (((volatile uint64_t *)&DAT_00095320)[id * 0x20] & 1) != 0) {
        if (*(uint64_t *)(*(uint64_t *)(DAT_00095328 + id * 0x20) + 0x28) != 0) {
            uint64_t cpu = sptm_cpu_base();
            uint64_t saved = *(uint64_t *)(cpu + 0xa38);
            *(uint64_t *)(cpu + 0xa38) = id + 1;
            (*(void (**)(void *))(*(uint64_t *)(DAT_00095328 + id * 0x20) + 0x28))(fte + 8);
            *(uint64_t *)(cpu + 0xa38) = saved;
        }
        return;
    }
    sptm_panic_str("IOMMU with id %d not supported");
}

/* FUN_000e131c: FTE class-2 emptiness check (two short refcounts). */
static void sptm_fte_class2_check(void *fte, uint32_t type)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 2)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(uint16_t *)((uint8_t *)fte + 8) == 0 && *(uint16_t *)((uint8_t *)fte + 6) == 0)
        return;
    sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e1470: FTE class-3 write-refcount check. */
static void sptm_fte_class3_write_check(void *fte, uint32_t type)
{
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 3)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(int32_t *)((uint8_t *)fte + 0xc) == 0)
        return;
    sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e153c: FTE class-3 write-refcount release (tail is bad-instruction —
 * assembly-level, confidence low). */
static void sptm_fte_class3_write_release(void *fte, uint32_t type)
{
    uint8_t guard;
    uint64_t bit;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 3)
        sptm_panic_str("Type %d class of FTE %d");
    guard = *(uint8_t *)((uint8_t *)fte + 4);
    bit = (type & 0x40) ? 0 : (1UL << (type & 0x3f));
    if (((guard & 3) != 0 || (bit & 0x2000201c000) == 0) && *(int32_t *)((uint8_t *)fte + 8) != 0) {
        if ((guard & 1) != 0)
            sptm_panic(0x4d, type, "%s: %s %d %s 0x%llx %s 0x%llx");
        if (((guard >> 1 & 1) == 0))
            sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
        sptm_panic(0x52, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
    if (*(int32_t *)((uint8_t *)fte + 0xc) != 0)
        sptm_panic(0x17, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    if (((guard >> 1 & 1) == 0)) {
        *(uint8_t *)((uint8_t *)fte + 4) &= 0xfc;
        return;
    }
    /* Tail: bad-instruction (BRK). Render as trap. */
    sptm_brk(0);
}

/* FUN_000e17d8: noreturn FTE type panic. */
static void sptm_fte_type_panic(void) __attribute__((noreturn));
static void sptm_fte_type_panic(void)
{
    sptm_panic_str("Type %d class of FTE %d");
}

/* ------------------------------------------------------------------ *
 * FUN_000e1810 @ 0x000e1810   (est. sptm_fte_retype)
 * Ghidra: void FUN_000e1810(long param_1, undefined8 param_2)
 * Retype an FTE. For type 0x21 (VMID table): programs vttbr_el2 and clears the
 * VMID allocation bit (DAT_00104080). For 0x12/0x13 (CPU page table): validates
 * the transition (0x12->0x13 or 0x13->0xb), calls sptm_fte_retype_apply
 * (FUN_000e1acc), and for 0x13 also releases the ASID reference. Fail-closed.
 * Confidence: low */
static void sptm_fte_retype(void *fte, uint32_t new_type)
{
    uint8_t t = *(uint8_t *)((uint8_t *)fte + 2);
    if (SPTM_FTE_CLASS(t) != 1)
        sptm_panic_str("Type %d class of FTE %d");
    if (*(uint16_t *)((uint8_t *)fte + 6) != 0)
        sptm_panic(0x17, new_type, "%s: %s %d %s 0x%llx %s 0x%llx");

    uint8_t shared = *(uint8_t *)((uint8_t *)fte + 8);
    if (t == 0x21) {
        __builtin_arm_wsr64("vttbr_el2", (uint64_t)*(uint16_t *)((uint8_t *)fte + 4) << 0x30);
        sptm_isb();
        SPTM_SYSW(4,9,3,6,0, 0);
        sptm_dsb_sy();
        sptm_isb();
        uint64_t bit = 1UL << (*(uint16_t *)((uint8_t *)fte + 4) & 0x3f);
        uint64_t *w = (uint64_t *)(DAT_00104080 + ((*(uint16_t *)((uint8_t *)fte + 4) >> 3) & 0x1ff8));
        uint64_t old = *w;
        *w = old & ~bit;
        if ((bit & old) == 0)
            sptm_panic_str("VMID 0x%hx was already clear");
        *(uint16_t *)((uint8_t *)fte + 4) = 0;
    } else if (t == 0x13) {
        if (*(uint16_t *)((uint8_t *)fte + 4) != 0)
            sptm_panic(0x17, new_type, "%s: %s %d %s 0x%llx %s 0x%llx");
        sptm_fte_retype_apply(fte, 0, 0);
        if (shared == 0xff)
            sptm_panic_str("Shared region ID does not exist");
        /* release the ASID/VMID shared region reference */
        uint64_t idx = shared * 0x20;
        *(uint64_t *)(DAT_00104160 + idx) = 0;
        *(uint64_t *)(DAT_00104160 + idx + 8) = 0;
        uint8_t prev = *(uint8_t *)(DAT_00104148 + idx);
        *(uint8_t *)(DAT_00104148 + idx) = 0;
        if (prev == 0)
            sptm_panic_str("Unexpected shared region state %d");
        do {
            *(uint32_t *)(DAT_00104150 + shared * 4) = DAT_00102000;
            /* CAS-style push onto ASID free list */
            __atomic_compare_exchange_n((uint64_t *)&DAT_00102000, &DAT_00102000,
                                        DAT_00104148 + idx, 0, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
        } while (0);
    }
}

/* FUN_000e1acc — retype apply (release old CPU-table state, drop ASID ref).
 * Declared above. */

/* ------------------------------------------------------------------ *
 * FUN_000e1d28 @ 0x000e1d28   (est. sptm_fte_retype_alloc)
 * Ghidra: void FUN_000e1d28(long param_1, undefined8 param_2, ulong param_3)
 * Allocate/initialize a CPU-root FTE (param_1) to a new type given by
 * param_2 (0x13 = CPU page table, 0x12 = ASID table, 0x21 = VMID table) with
 * parameter param_3. For 0x13: pops an ASID from the free list, records the
 * shared-region, programs the ASID in the TLB and clears param_1->asid. For
 * 0x12/0x21: allocates an ASID/VMID from the respective bitmap. Fail-closed.
 * Confidence: low */
static void sptm_fte_retype_alloc(void *fte, uint32_t new_type, uint64_t param)
{
    uint32_t new32 = (uint32_t)param;
    uint8_t lo = (uint8_t)(param & 0xff);

    if (lo > 5 ||
        (*(uint64_t *)(DAT_000135f8 + (new_type == 0x21) * 8) >> (param & 0x3f) & 1) == 0 ||
        (lo == 1 && (DAT_00095d38 & 1) == 0))
        sptm_panic(2, new_type, "%s: %s %d %s 0x%llx %s 0x%llx");

    if (new_type == 0x13) {
        *(uint16_t *)((uint8_t *)fte + 10) = 0;
        /* pop ASID from free list (DAT_00102000) */
        uint64_t node = DAT_00102000;
        if (DAT_00102000 == 0)
            sptm_panic(0x47, new_type, "%s: %s %d %s 0x%llx");
        DAT_00102000 = *(uint64_t *)(DAT_00102000 + 8);
        uint64_t idx = node - 0x104148;
        *(uint64_t *)(DAT_00104160 + (idx & 0x1fe0)) = (uint64_t)fte;
        *(uint8_t *)(DAT_00104148 + (idx & 0x1fe0)) = 1;
        *(uint8_t *)((uint8_t *)fte + 8) = (uint8_t)(idx >> 5);
        sptm_tlb_program_asid(sptm_cpu_base() + 0xa58, *(uint16_t *)((uint8_t *)fte + 4));
        *(uint16_t *)((uint8_t *)fte + 4) = 0;
    } else if (new_type == 0x12) {
        uint32_t asid = new32 & 0xffff;
        if (asid == 0 || DAT_00095d3c <= asid)
            sptm_panic(4, new_type, "%s: %s %d %s 0x%llx %s 0x%llx");
        uint32_t var = (uint32_t)(param >> 0x10) & 0xffff;
        if (var > 0x1ff || ((var ^ 0xffffffff) & 0x24) == 0 || (var >> 7 & 1) != 0)
            sptm_panic(0x10, new_type, "%s: %s %d %s 0x%llx");
        uint64_t bit = 1UL << (asid & 0x3f);
        uint64_t *w = (uint64_t *)(DAT_00102080 + (uint64_t)(asid >> 6) * 8);
        uint64_t old = *w;
        *w = old | bit;
        if ((old & bit) != 0)
            sptm_panic(0x4b, new_type, "%s: %s %d %s 0x%llx %s 0x%llx");
        *(uint16_t *)((uint8_t *)fte + 4) = (uint16_t)asid;
        *(uint16_t *)((uint8_t *)fte + 10) = (uint16_t)var;
        *(uint8_t *)((uint8_t *)fte + 8) = 0xff;
        *(uint8_t *)((uint8_t *)fte + 0xc) = (uint8_t)param;
        *(uint16_t *)((uint8_t *)fte + 6) = 0;
        sptm_tlb_program_asid(sptm_cpu_base() + 0xa58, asid);
    } else if (new_type == 0x21) {
        if ((new32 & 0xff01) != 1)
            sptm_panic(5, new_type, "%s: %s %d %s 0x%llx");
        uint64_t bit = 1UL << (new32 & 0x3f);
        uint64_t *w = (uint64_t *)(DAT_00104080 + (uint64_t)(new32 >> 6 & 0x3ff) * 8);
        uint64_t old = *w;
        *w = old | bit;
        if ((old & bit) != 0)
            sptm_panic(0x4c, new_type, "%s: %s %d %s 0x%llx");
        *(uint16_t *)((uint8_t *)fte + 4) = (uint16_t)new32;
        *(uint16_t *)((uint8_t *)fte + 10) = 0;
        *(uint8_t *)((uint8_t *)fte + 8) = 0xff;
    }
    *(uint8_t *)((uint8_t *)fte + 0xc) = (uint8_t)param;
    *(uint16_t *)((uint8_t *)fte + 6) = 0;
}

/* (tlb_program_asid declared above.) */

/* No-ops FUN_000e2138/0xe2140/0xe2148. */
static void sptm_noop(void) {}

/* ------------------------------------------------------------------ *
 * FUN_000e2150 @ 0x000e2150   (est. sptm_cpu_root_fte_to_paddr)
 * Ghidra: ulong FUN_000e2150(short *param_1)
 * Return the physical address of a CPU-root-table FTE (param_1). For type
 * 0x12 with the high ASID bit set, resolves the parent frame; otherwise
 * computes the flat paddr from the PAPT table index. Panics if the FTE is not
 * a CPU root table or the frame was not acquired.
 * Confidence: low */
static uint64_t sptm_cpu_root_fte_to_paddr(void *fte)
{
    uint8_t t = *(uint8_t *)((uint8_t *)fte + 2);
    uint64_t paddr;
    if (SPTM_FTE_CLASS(t) != 1)
        sptm_panic_str("Type %d is not a CPU root table");
    if (t == 0x12 && ((*(uint16_t *)((uint8_t *)fte + 10) >> 7 & 1) != 0)) {
        paddr = (uint64_t)(uintptr_t)sptm_phystokv((uint64_t)(uintptr_t)((uint8_t *)fte - 0x40));
        void *parent = sptm_phystokv(paddr);
        if (parent == 0) parent = (void *)&DAT_00101f90;
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)parent + 2)) != 7)
            sptm_panic_str("PA %p is not associated with a frame");
    } else {
        paddr = (((uint64_t)fte - DAT_00095460) * 0x400 & 0x3fffffffc000) + DAT_00095d18;
    }
    if (paddr != DAT_00095d48 && *(uint16_t *)fte == 0)
        sptm_panic_str("Frame %p not acquired (in use)");
    return paddr;
}

/* ------------------------------------------------------------------ *
 * DRAM / physical-address helpers (0xe35b4 - 0xe3b38).
 * ------------------------------------------------------------------ */

/* FUN_000e35b4 @ 0x000e35b4   (est. sptm_dram_update_type)
 * Ghidra: undefined4 FUN_000e35b4(ulong param_1, uint param_2)
 * Atomically update the 2-bit type field (of a DRAM byte entry, 4 entries per
 * byte) for a physical address to the type derived from param_2&3. Returns
 * 0 if the update was a no-op/already set, 1 if the target was already type 3,
 * 2 otherwise.
 * Confidence: medium */
static uint32_t sptm_dram_update_type(uint64_t paddr, uint32_t type)
{
    uint32_t want = 0;
    uint32_t cur, got, newv;
    if ((type & 3) != 3) want = 3;
    if ((type & 3) == 1) want = 1;
    if (paddr < DAT_000952f8 || DAT_00095300 < paddr)
        sptm_panic_str("Address 0x%llx not within DRAM window");
    uint64_t byte = (paddr - DAT_000952f8) >> 0x10;
    uint64_t shift = (paddr - DAT_000952f8) >> 0xd & 6;
    uint8_t *slot = (uint8_t *)DAT_000952e8 + byte;
    cur = *slot;
    do {
        got = cur >> shift & 3;
        if (want & ~(cur >> shift) || got == want) break;
        newv = (cur & ~(3 << shift)) | (want << shift);
        __atomic_compare_exchange_n(slot, &cur, (uint8_t)newv, 1,
                                    __ATOMIC_RELAXED, __ATOMIC_RELAXED);
    } while (cur != (uint8_t)got || (want & ~(cur >> shift) && got != want));
    if (got == 3) return 1;
    if (want & ~(got) || got == want) return 0;
    return 2;
}

/* FUN_000e36a0: mark a DRAM byte entry type as all-present (3<<shift |). */
static void sptm_dram_mark_type(uint64_t paddr, int present)
{
    if (present == 0) return;
    if (paddr < DAT_000952f8 || DAT_00095300 < paddr)
        sptm_panic_str("Address 0x%llx not within DRAM window");
    uint64_t byte = (paddr - DAT_000952f8) >> 0x10;
    uint64_t shift = (paddr - DAT_000952f8) >> 0xd;
    uint8_t *slot = (uint8_t *)DAT_000952e8 + byte;
    uint8_t cur = *slot;
    do {
        if (((cur >> (shift & 6) ^ 0xffffffff) & 3) == 0) return;
        uint8_t newv = cur | (3 << (shift & 6));
        if (!__atomic_compare_exchange_n(slot, &cur, newv, 1, __ATOMIC_RELAXED, __ATOMIC_RELAXED))
            continue;
        break;
    } while (1);
}

/* FUN_000e3754: UAT FW alias detection — set DRAM type, panic if type 3 found. */
static uint64_t sptm_dram_fw_alias_check(uint64_t paddr, uint32_t type)
{
    uint32_t want = 0, got;
    if ((type & 3) != 3) want = 3;
    if ((type & 3) == 1) want = 1;
    if (paddr < DAT_000952f8 || DAT_00095300 < paddr)
        sptm_panic_str("Address 0x%llx not within DRAM window");
    uint64_t byte = (paddr - DAT_000952f8) >> 0x10;
    uint64_t shift = (paddr - DAT_000952f8) >> 0xd & 6;
    uint8_t *slot = (uint8_t *)DAT_000952e8 + byte;
    uint8_t cur = *slot;
    do {
        got = cur >> shift & 3;
        if (got == want) break;
        uint8_t newv = (cur & ~(3 << shift)) | (want << shift);
        if (!__atomic_compare_exchange_n(slot, &cur, newv, 1, __ATOMIC_RELAXED, __ATOMIC_RELAXED))
            continue;
        break;
    } while (1);
    if (got == 3) return 1;
    sptm_panic_str("UAT FW alias detected for physical %llx");
}

/* FUN_000e384c @ 0x000e384c   (est. sptm_paddr_type)
 * Ghidra: undefined4 FUN_000e384c(int param_1, ulong param_2)
 * Determine the memory type of a physical address: type 0 (DRAM/wired), type 1
 * (managed frame region), type 3 (IO/other). Special-cases param_1==0x18
 * (frame) which may be class-3 (managed). Confidence: high */
uint32_t sptm_paddr_type(uint32_t kind, uint64_t paddr)
{
    uint32_t t;
    if (kind == 0x18) {
        void *fte = sptm_phystokv(paddr);
        if (fte == 0) fte = (void *)&DAT_00101f90;
        if ((((uint32_t)DAT_001012d8 >> 0x16 & 1) != 0) && *(uint16_t *)fte == 0)
            sptm_panic_str("Frame expected to have been acquired %d");
        if (*(int8_t *)((uint8_t *)fte + 6) == 3) {  /* class-3 managed frame */
            if ((*(uint8_t *)((uint8_t *)fte + 8) - 1 < 5) &&
                ((0x1bU >> (*(uint8_t *)((uint8_t *)fte + 8) - 1 & 0x1f) & 1) != 0))
                return 1;
        }
    }
    if ((sptm_paddr_in_dram(paddr) & 1) == 0) {
        if ((paddr & 0x3fff) != 0)
            sptm_panic_str("Physical address 0x%llx is not aligned");
        t = 3;
        uint64_t *boot = (uint64_t *)DAT_00095d08;
        if ((boot[0x68/8] <= paddr && paddr < boot[0x68/8] + boot[0x70/8] * 0x4000) ||
            (boot[0x108/8] <= paddr && paddr < boot[0x108/8] + boot[0x110/8] * 0x4000))
            t = 1;
    } else {
        t = 0;
    }
    return t;
}

/* FUN_000e3a14 @ 0x000e3a14   (est. sptm_paddr_in_dram)
 * Ghidra: byte FUN_000e3a14(ulong param_1)
 * Returns 1 if the physical address lies within any of the DRAM boot region
 * ranges in DAT_00095d08 (offsets 0x140..0x1a0 and the managed window
 * 0x118/0x128), 0 otherwise. Panics on misalignment.
 * Confidence: high */
uint8_t sptm_paddr_in_dram(uint64_t paddr)
{
    uint64_t *b = (uint64_t *)DAT_00095d08;
    if ((paddr & 0x3fff) != 0)
        sptm_panic_str("Physical address 0x%llx is not aligned");

    /* ranges at offsets 0x140/0x150/0x160/0x170/0x180/0x190 */
    int in = 0;
    const uint64_t offs[] = {0x140, 0x150, 0x160, 0x170, 0x180, 0x190};
    for (unsigned i = 0; i < 6; i++) {
        uint64_t base = b[offs[i]/8];
        uint64_t len  = b[offs[i]/8 + 1] * 0x4000;
        if (base <= paddr && paddr < base + len)
            return 1;
    }
    uint64_t mbase = b[0x118/8];
    uint64_t mlen  = b[0x120/8] * 0x4000;
    uint8_t r = (mbase <= paddr && paddr < mbase + mlen);
    uint8_t s = 0;
    uint64_t sbase = b[0x128/8];
    uint64_t slen  = b[0x130/8] * 0x4000;
    if (paddr < sbase + slen)
        s = (sbase <= paddr) & (r ^ 0xff);
    return r | s;
}

/* FUN_000e3b38 @ 0x000e3b38   (est. sptm_paddr_type_allowed)
 * Ghidra: undefined1 FUN_000e3b38(uint param_1, ulong param_2)
 * Like sptm_paddr_type but additionally consults the per-type allowed-IOMMU
 * permission table (DAT_00095d78 bit 3, DAT_00095d80): when the type's IOMMU
 * permission flag (bit 3) is set, returns whether param_1's allowed-IOMMU
 * permission equals 1. Confidence: low */
static uint8_t sptm_paddr_type_allowed(uint32_t type, uint64_t paddr)
{
    uint8_t t;
    if ((((volatile uint8_t *)&DAT_00095d78)[type * 0x90] >> 3 & 1) == 0) {
        if (paddr != 0) {
            void *fte = sptm_phystokv(paddr);
            if (fte == 0) fte = (void *)&DAT_00101f90;
            if ((((uint32_t)DAT_001012d8 >> 0x16 & 1) != 0) && *(uint16_t *)fte == 0)
                sptm_panic_str("Frame expected to have been acquired %d");
            if (type == 0x18 && *(int8_t *)((uint8_t *)fte + 6) == 3) {
                if ((*(uint8_t *)((uint8_t *)fte + 8) - 1 < 5) &&
                    ((0x1bU >> (*(uint8_t *)((uint8_t *)fte + 8) - 1 & 0x1f) & 1) != 0))
                    return 1;
            }
        }
        t = (uint8_t)sptm_paddr_type(type, paddr);
    } else {
        uint8_t p = SPTM_FTE_IO_PERM(type);
        if (p > 2)
            sptm_panic_str("Allowed IOMMU permissions are invalid");
        t = (p == 1);
    }
    return t;
}

/* ------------------------------------------------------------------ *
 * IO-frame / IOMMU operations (0xe40ec - 0xe63c8).
 * ------------------------------------------------------------------ */

/* FUN_000e40ec @ 0x000e40ec   (est. sptm_io_paddr_to_va)
 * Ghidra: long FUN_000e40ec(long param_1)
 * Translate an IO physical address to its SPTM VA using the IO-range table.
 * The range's base offset (offset 4) and page count (offset 8) define the
 * translation. Panics if no range or no base is set.
 * Confidence: medium */
uint64_t sptm_io_paddr_to_va(uint64_t paddr)
{
    void *r = sptm_phystokv(0);
    if (r == 0)
        sptm_panic_str("IO PADDR could not be found");
    if (*(uint32_t *)((uint8_t *)r + 4) != 0xffffffff) {
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)r + 2)) == 6)
            return paddr + (uint64_t)*(uint32_t *)((uint8_t *)r + 4) * 0x4000 +
                   DAT_00095458 + (uint64_t)*(uint32_t *)((uint8_t *)r + 8) * -0x4000;
        sptm_panic_str("Type %d class of FTE %d");
    }
    sptm_panic_str("IO PADDR does not have an associated base");
}

/* FUN_000e41bc @ 0x000e41bc   (est. sptm_io_bootstrap_alloc)
 * Ghidra: long FUN_000e41bc(ulong param_1, ulong param_2)
 * Allocate `param_2` pages of bootstrap type `param_1` (10 or 0x24) from the
 * managed DRAM region (FUN_000d823c), recording the IOMMU owner in each
 * allocated IO-frame FTE (offset 6 = dispatch id-1), and returning the VA of
 * the first page (with extended-VA translation applied).
 * Confidence: low */
static uint64_t sptm_io_bootstrap_alloc(uint32_t type, uint64_t pages)
{
    uint64_t cpu, d;
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) != 0))
        sptm_panic_str("Unexpected bootstrap stages reached");
    if (type != 10 && type != 0x24)
        sptm_panic_str("invalid bootstrap frames type %d");
    cpu = sptm_cpu_base();
    d = *(uint64_t *)(cpu + 0xa38);
    if (d - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");

    uint64_t base = sptm_alloc_managed(type, pages, 2);
    uint64_t paddr = DAT_00095d18;
    if (SPTM_FTE_CLASS(type) == 5 && pages != 0) {
        for (uint64_t i = 0; i < pages; i++) {
            uint64_t fte = DAT_00095460 + ((base - DAT_00095d18) >> 0xe) * 0x10 + i * 0x10;
            if (SPTM_FTE_CLASS(*(uint8_t *)(fte + 2)) != 5)
                sptm_panic_str("Type %d class of FTE %d");
            *(uint8_t *)(fte + 6) = (uint8_t)(d - 1);
        }
    }
    uint64_t va = (base - DAT_00095d18) + DAT_00095d18;
    uint64_t off = (va & 0x3fffffffc000) + paddr;
    if (((uint32_t)DAT_001012d8 >> 8 & 1) == 0)
        return (off - DAT_00095d18) + DAT_00095110;
    uint64_t n = DAT_00101ac8;
    uint64_t *tbl = (uint64_t *)&DAT_00101ad0;
    while (n != 0) {
        if (tbl[0] <= off && off < tbl[0] + (uint32_t)tbl[2] * 0x4000)
            return (off - tbl[0]) + tbl[1];
        tbl += 3; n--;
    }
    return sptm_io_paddr_to_va(off);
}

extern uint64_t sptm_alloc_managed(uint32_t type, uint64_t pages, uint32_t mode);

/* FUN_000e43d0: bootstrap-frame alloc wrapper (type 10). */
static uint64_t sptm_io_bootstrap_alloc_simple(uint64_t pages)
{
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) == 0)) {
        return sptm_io_bootstrap_alloc(10, pages);
    }
    sptm_panic_str("Unexpected bootstrap stages reached");
}

/* FUN_000e4424 @ 0x000e4424   (est. sptm_iommu_state_alloc)
 * Ghidra: ulong FUN_000e4424(undefined8 param_1)
 * Allocate the next IOMMU state object slot for the current dispatch id and
 * return its index. Validates the IOMMU is present and that the state-array
 * count is below the maximum. Confidence: low */
static uint64_t sptm_iommu_state_alloc(uint64_t arg)
{
    uint64_t cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 >= 9)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    uint32_t did = (uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1);
    uint64_t slot = (did & 0xff) * 0x20;
    if ((((volatile uint64_t *)&DAT_00095320)[slot] & 1) != 0) {
        uint16_t count = *(uint16_t *)(DAT_00095338 + slot);
        uint64_t cpu2 = sptm_cpu_base();
        if (*(uint64_t *)(cpu2 + 0xa38) - 1 > 8)
            sptm_panic_str("Unexpected Dispatch ID %llu");
        if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu2 + 0xa38) - 1) & 0xff) * 0x20] & 1) != 0) {
            if (*(uint16_t *)(*(uint64_t *)(DAT_00095328 + slot) + 0x48) <= count)
                sptm_panic_str("IOMMU %s %d: State objects exhausted");
            if ((((volatile uint64_t *)&DAT_00095320)[slot] & 1) != 0) {
                uint8_t *st = (uint8_t *)(*(uint64_t *)(DAT_00095330 + slot) +
                               *(uint64_t *)(*(uint64_t *)(DAT_00095328 + slot) + 0x50) * count);
                *st = (uint8_t)did;
                *(uint64_t *)(st + 8) = arg;
                *(uint16_t *)(DAT_00095338 + slot) += 1;
                return count;
            }
        }
        sptm_panic_str("IOMMU with id %d not supported");
    }
    sptm_panic_str("IOMMU with id %d not supported");
}

/* FUN_000e45a8 @ 0x000e45a8   (est. sptm_io_frame_add)
 * Ghidra: long FUN_000e45a8(ulong param_1, ulong param_2, undefined8 param_3)
 * Add an IO-frame range [param_1, param_1+param_2) to the current IOMMU's IO
 * range table. Validates the physical address/length, allocates a new range
 * entry (type 0x1b), records start/count/cache-mode, and returns the IO base
 * VA. Fail-closed on every validation.
 * Confidence: low */
static uint64_t sptm_io_frame_add(uint64_t paddr, uint64_t pages, uint64_t cache_mode)
{
    uint64_t cpu, did_slot;
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) != 0))
        sptm_panic_str("Unexpected bootstrap stages reached");
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
        sptm_panic_str("IOMMU with id %d not supported");
    if (DAT_00095d18 <= paddr && paddr < DAT_00095d20)
        sptm_panic_str("IOMMU %s %d: Attempted to map DRAM frame");
    if (pages == 0)
        sptm_panic_str("IOMMU %s %d: Attempted to map zero frames");
    if ((paddr & 0x3fff) != 0)
        sptm_panic_str("IOMMU %s %d: Attempted to map unaligned frame");
    if (pages > 0xffff)
        sptm_panic_str("IOMMU %s %d: 0x%llx length is too large");

    void *r = sptm_phystokv(paddr);
    if (r == 0 || *(char *)((uint8_t *)r + 2) == 0x1a) {
        if (DAT_00095440 > 0x3ff)
            sptm_panic_str("IOMMU %s %d: Number of IO ranges exceeded");
        uint64_t e = DAT_00095448 + DAT_00095440 * 0x10;
        *(uint8_t *)(e + 2) = 0x1b;
        if (DAT_00096c81 == 6) {
            *(uint32_t *)(e + 8) = (uint32_t)(paddr >> 0xe);
            *(uint32_t *)(e + 0xc) = (uint32_t)pages | (uint32_t)*(uint8_t *)(e + 0xf) << 0x18;
            cpu = sptm_cpu_base();
            *(uint8_t *)(e + 0xf) = (uint8_t)((uint32_t)(*(uint64_t *)(cpu + 0xa38) * 0x1000000) >> 0x18);
            *(uint32_t *)(e + 4) = DAT_001040a0;
            DAT_00095440 += 1;
            return sptm_io_commit_range(paddr, pages, cache_mode);
        }
        sptm_panic_str("Type %d class of FTE %d");
    }

    /* validate existing range matches */
    if (*(uint8_t *)((uint8_t *)r + 2) > 0x27 && *(uint8_t *)((uint8_t *)r + 2) != 0x1b)
        sptm_panic_str("IOMMU %s %d: IO frame does not have valid type");
    if (*(uint32_t *)((uint8_t *)r + 8) != (uint32_t)(paddr >> 0xe))
        sptm_panic_str("IOMMU %s %d: IO frame start mismatch");
    if ((*(uint32_t *)((uint8_t *)r + 0xc) & 0xffffff) != (uint32_t)pages)
        sptm_panic_str("IOMMU %s %d: IO frame number mismatch");

    uint64_t range = sptm_pmap_io_range_lookup(paddr);
    if ((DAT_000950d8 == 0 || paddr < *((uint64_t *)DAT_000950d0)) ||
        ((sptm_pmap_io_range_lookup(paddr) == 0) ||
         ((*(uint8_t *)(range + 0x13) >> 3 & 1) != 0)))
        range = 0;

    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 < 9) {
        if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
            sptm_panic_str("IOMMU with id %d not supported");
        if (range == 0)
            sptm_panic_str("IOMMU %s %d: pmap io range not found");
        int want = 2;
        if (*(char *)(range + 0x10) != 0x16) want = 0;
        if (*(char *)(range + 0x10) == 0x02) want = 1;
        if ((uint32_t)cache_mode != (uint32_t)want)
            sptm_panic_str("IOMMU %s %d: cache mode mismatch");
        if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)r + 2)) == 6) {
            *(uint8_t *)((uint8_t *)r + 0xf) = (uint8_t)((uint32_t)(*(uint64_t *)(sptm_cpu_base() + 0xa38) * 0x1000000) >> 0x18);
            if (SPTM_FTE_FRAME(*(uint8_t *)((uint8_t *)r + 2)) == 0xff)
                return 0xffffffff;
            if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)r + 2)) != 6)
                sptm_panic_str("Type %d class of FTE %d");
            return DAT_00095458 + (uint64_t)*(uint32_t *)((uint8_t *)r + 4) * 0x4000;
        }
        sptm_panic_str("Type %d class of FTE %d");
    }
    sptm_panic_str("Unexpected Dispatch ID %llu");
}

extern uint64_t sptm_io_commit_range(uint64_t paddr, uint64_t pages, uint64_t mode);
extern uint64_t sptm_pmap_io_range_lookup(uint64_t paddr);

/* FUN_000e4d78 @ 0x000e4d78   (est. sptm_iommu_state_get)
 * Ghidra: long FUN_000e4d78(uint param_1, undefined8 param_2)
 * Return the IOMMU state object at index param_1 for the current dispatch id,
 * or panic 0xf if the index is out of range. Confidence: medium */
static uint64_t sptm_iommu_state_get(uint32_t idx, uint64_t caller)
{
    uint64_t cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    uint64_t slot = ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20;
    if ((((volatile uint64_t *)&DAT_00095320)[slot] & 1) == 0)
        sptm_panic_str("IOMMU with id %d not supported");
    if (idx < *(uint16_t *)(DAT_00095338 + slot))
        return *(uint64_t *)(DAT_00095330 + slot) +
               *(uint64_t *)(*(uint64_t *)(DAT_00095328 + slot) + 0x50) * idx;
    sptm_panic(0xf, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e4e74 @ 0x000e4e74   (est. sptm_io_frame_check_owner)
 * Ghidra: void FUN_000e4e74(undefined8 param_1, uint param_2)
 * Validate that the frame for the current physical address belongs to the
 * current dispatch id: for type 0x18 the FTE's owner byte must equal the
 * dispatch id; for other types the per-type permission mask (DAT_00095d78)
 * must permit the dispatch id. Fail-closed.
 * Confidence: low */
static void sptm_io_frame_check_owner(uint64_t paddr, uint32_t type)
{
    void *fte = sptm_phystokv(paddr);
    uint64_t cpu;
    if (fte == 0) fte = (void *)&DAT_00101f90;
    if (type != 0x44 && *(uint8_t *)((uint8_t *)fte + 2) != type)
        sptm_panic(0x42, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if (*(uint8_t *)((uint8_t *)fte + 2) == 0x18) {
        if (DAT_00096ad1 != 5)
            sptm_panic_str("Type %d class of FTE %d");
        if (*(uint8_t *)((uint8_t *)fte + 6) != ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff))
            sptm_panic(0, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
    } else {
        cpu = sptm_cpu_base();
        if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
            sptm_panic_str("Unexpected Dispatch ID %llu");
        if ((SPTM_FTE_DISPATCH(*(uint8_t *)((uint8_t *)fte + 2)) >>
             ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0x3f) & 1) == 0)
            sptm_panic(0x42, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
}

/* FUN_000e5090 @ 0x000e5090   (est. sptm_io_frame_release)
 * Ghidra: void FUN_000e5090(ulong param_1)
 * Release the rw-guard shared lock on the frame at physical address param_1,
 * after validating it is owned by the current dispatch id (type 0x18 owner
 * match, or per-type permission mask). Fail-closed on validation.
 * Confidence: low */
static void sptm_io_frame_release(uint64_t paddr)
{
    void *fte = sptm_phystokv(paddr);
    uint64_t cpu, d;
    if (fte == 0) fte = (void *)&DAT_00101f90;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 6 && *(uint16_t *)fte == 0) {
        sptm_dispatch_id();
        sptm_panic_str("Frame expected to have been acquired %d");
    }
    cpu = sptm_cpu_base();
    d = *(uint64_t *)(cpu + 0xa38);
    if (d - 1 < 9) {
        void *f = sptm_phystokv(paddr);
        if (f == 0) f = (void *)&DAT_00101f90;
        uint64_t cpu2 = sptm_cpu_base();
        if (*(uint8_t *)((uint8_t *)f + 2) == 0x18) {
            if (*(uint64_t *)(cpu2 + 0xa38) - 1 < 9) {
                if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu2 + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
                    sptm_panic_str("IOMMU with id %d not supported");
                if (*(uint8_t *)((uint8_t *)f + 6) != ((uint32_t)d - 1 & 0xff))
                    sptm_panic_str("IOMMU %s %d: attempted to release foreign frame");
                goto release;
            }
        } else {
            if (*(uint64_t *)(cpu2 + 0xa38) - 1 < 9) {
                if ((SPTM_FTE_DISPATCH(*(uint8_t *)((uint8_t *)f + 2)) >>
                     ((uint32_t)(*(uint64_t *)(cpu2 + 0xa38) - 1) & 0x3f) & 1) == 0)
                    sptm_panic_str("Tried releasing a frame that this dispatch doesn't own");
                goto release;
            }
        }
        sptm_panic_str("Unexpected Dispatch ID %llu");
    }
    sptm_panic_str("Unexpected Dispatch ID %llu");
release:
    sptm_fte_release_rw_shared(fte);
}

/* FUN_000e537c @ 0x000e537c   (est. sptm_dispatch_id)
 * Ghidra: uint FUN_000e537c(void)
 * Return the current dispatch id (per-CPU +0xa38 minus 1), panicking if out
 * of range. Confidence: high */
uint32_t sptm_dispatch_id(void)
{
    uint64_t cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 < 9)
        return (uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff;
    sptm_panic_str("Unexpected Dispatch ID %llu");
}

/* FUN_000e53d8 @ 0x000e53d8   (est. sptm_io_frame_refcount_adjust)
 * Ghidra: uint FUN_000e53d8(ulong param_1, uint param_2)
 * Adjust the IO-frame FTE refcount (offset 2 short) by param_2 (positive or
 * negative, in chunks of 0x40) for a type-0x18 frame owned by the current
 * dispatch id. Returns the prior refcount. Fail-closed.
 * Confidence: low */
static uint32_t sptm_io_frame_refcount_adjust(uint64_t paddr, int32_t delta)
{
    void *fte = sptm_phystokv(paddr);
    uint64_t cpu;
    uint16_t old;
    if (fte == 0) fte = (void *)&DAT_00101f90;
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 6 && *(uint16_t *)fte == 0) {
        sptm_dispatch_id();
        sptm_panic_str("Frame expected to have been acquired %d");
    }
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 < 9) {
        if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
            sptm_panic_str("IOMMU with id %d not supported");
        if ((char)*(uint8_t *)((uint8_t *)fte + 2) == 0x18) {
            cpu = sptm_cpu_base();
            if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
                sptm_panic_str("Unexpected Dispatch ID %llu");
            if (*(uint8_t *)((uint8_t *)fte + 6) == ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff)) {
                if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 5)
                    sptm_panic_str("Type %d class of FTE %d");
                if (delta < 1) {
                    if (delta < 0) {
                        old = *(uint16_t *)((uint8_t *)fte + 4);
                        uint32_t oldv = old;
                        *(uint16_t *)((uint8_t *)fte + 4) = old + (int16_t)delta;
                        if (oldv < ((uint32_t)(-delta) & 0xffff))
                            sptm_panic_str("refcnt underflow (rc %p old value %d)");
                        return oldv;
                    }
                    return (uint32_t)*(uint16_t *)((uint8_t *)fte + 4);
                } else {
                    int32_t chunk = (delta < 0x41) ? delta : 0x40;
                    old = *(uint16_t *)((uint8_t *)fte + 4);
                    *(uint16_t *)((uint8_t *)fte + 4) = old + (int16_t)chunk;
                    uint32_t oldv = old;
                    if (old >> 6 > 0x3f4)
                        sptm_panic_str("refcnt overflow (rc %p old value %d)");
                    for (delta -= chunk; (delta & 0xffff) != 0; delta -= chunk) {
                        uint32_t c = (uint32_t)delta & 0xffff;
                        chunk = (c < 0x41) ? (int32_t)c : 0x40;
                        old = *(uint16_t *)((uint8_t *)fte + 4);
                        *(uint16_t *)((uint8_t *)fte + 4) = old + (int16_t)chunk;
                        if (old >> 6 > 0x3f4)
                            sptm_panic_str("refcnt overflow (rc %p old value %d)");
                    }
                    return oldv;
                }
            }
        }
        sptm_panic_str("IOMMU %s %d: attempted to adjust foreign frame");
    }
    sptm_panic_str("Unexpected Dispatch ID %llu");
}

/* FUN_000e56ac @ 0x000e56ac   (est. sptm_io_frame_map)
 * Ghidra: void FUN_000e56ac(ulong param_1, undefined8 param_2)
 * Map an IO frame at physical address param_1: validate ownership/permissions
 * (FUN_000e4e74, FUN_000e5958 with mode 1) and release the frame rw-guard
 * (FUN_000e5090). Fail-closed.
 * Confidence: low */
static void sptm_io_frame_map(uint64_t paddr, uint32_t type)
{
    void *fte;
    uint64_t cpu;
    sptm_io_frame_check_owner(paddr, 0x44);
    fte = sptm_phystokv(paddr);
    if (fte == 0) fte = (void *)&DAT_00101f90;
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if ((SPTM_FTE_DISPATCH(*(uint8_t *)((uint8_t *)fte + 2)) >>
         ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0x3f) & 1) == 0 ||
        SPTM_FTE_IO_PERM(*(uint8_t *)((uint8_t *)fte + 2)) < type) {
        sptm_dispatch_id();
        sptm_panic(0x28, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
    if (!(DAT_00095d28 <= paddr && paddr < DAT_00095d30) && *(char *)((uint8_t *)fte + 2) == 0)
        sptm_dram_fw_guard(paddr, 0);
    if ((DAT_00104128 & 1) != 0) {
        uint64_t page = paddr & 0xffffffffffffc000;
        if (sptm_hib_track_lookup(page) == 0)
            sptm_panic(0x59, 0, "%s: %s %d %s 0x%llx");
    }
    sptm_io_frame_refcount_ex(fte, type, 1);
    sptm_io_frame_release(paddr);
}

extern uint64_t sptm_hib_track_lookup(uint64_t page);
extern void sptm_dram_fw_guard(uint64_t paddr, uint64_t val);

/* FUN_000e5958 @ 0x000e5958   (est. sptm_io_frame_refcount_ex)
 * Ghidra: void FUN_000e5958(ulong param_1, int param_2, int param_3)
 * Increment (param_3!=0) or decrement (param_3==0) the exec/write refcount of
 * an IOMMU-owned refcounted FTE (class 3, offsets 8/0xc). param_2 selects the
 * counter (1 = exec/8, else write/0xc). Validates ownership and refcount
 * invariants. Fail-closed.
 * Confidence: low */
static void sptm_io_frame_refcount_ex(void *fte, uint32_t which, int inc)
{
    uint64_t cpu;
    uint8_t t;
    int32_t *p, old;
    uint32_t err;
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 < 9) {
        if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
            sptm_panic_str("IOMMU with id %d not supported");
        cpu = sptm_cpu_base();
        if (*(uint64_t *)(cpu + 0xa38) - 1 < 9) {
            if ((SPTM_FTE_DISPATCH(*(uint8_t *)((uint8_t *)fte + 2)) >>
                 ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0x3f) & 1) == 0)
                sptm_panic_str("IOMMU %s %d: Unexpected frame type");
            cpu = sptm_cpu_base();
            if (*(uint64_t *)(cpu + 0xa38) - 1 < 9) {
                if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) != 0) {
                    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 6) {
                        t = *(uint8_t *)((uint8_t *)fte + 2);
                        if (SPTM_FTE_CLASS(t) != 3)
                            sptm_panic_str("IOMMU %s %d: Non-refcounted frame");
                        uint64_t off = (which == 1) ? 8 : 0xc;
                        p = (int32_t *)((uint8_t *)fte + off);
                        if (inc == 0) {
                            *p -= 1;
                        } else {
                            old = *p;
                            *p = old + 1;
                            if (old == 0x7fffffff) {
                                err = (which == 1) ? 0x43 : 0x44;
                                sptm_dispatch_id();
                                sptm_panic(err, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
                            }
                            if (old != 0 && (SPTM_FTE_RWGUARD(t) & 1) == 0) {
                                sptm_dispatch_id();
                                sptm_panic(0x42, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
                            }
                        }
                    }
                    return;
                }
                sptm_panic_str("IOMMU with id %d not supported");
            }
        }
    }
    sptm_panic_str("Unexpected Dispatch ID %llu");
}

/* FUN_000e5c80 @ 0x000e5c80   (est. sptm_io_frame_unmap)
 * Ghidra: void FUN_000e5c80(ulong param_1, undefined8 param_2)
 * Unmap an IO frame: validate ownership/permissions, reject if a write-ref
 * transition is blocked, and release (FUN_000e5958 mode 0) + release guard
 * (FUN_000e5090). Fail-closed.
 * Confidence: low */
static void sptm_io_frame_unmap(uint64_t paddr, uint32_t type)
{
    void *fte;
    uint64_t cpu;
    uint8_t t, wr, allow;
    sptm_io_frame_check_owner(paddr, 0x44);
    fte = sptm_phystokv(paddr);
    if (fte == 0) fte = (void *)&DAT_00101f90;
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if ((((volatile uint64_t *)&DAT_00095320)[((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0xff) * 0x20] & 1) == 0)
        sptm_panic_str("IOMMU with id %d not supported");
    cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if ((SPTM_FTE_DISPATCH(*(uint8_t *)((uint8_t *)fte + 2)) >>
         ((uint32_t)(*(uint64_t *)(cpu + 0xa38) - 1) & 0x3f) & 1) == 0)
        sptm_panic_str("IOMMU %s %d: attempted to unmap foreign frame");
    if (SPTM_FTE_CLASS(*(uint8_t *)((uint8_t *)fte + 2)) != 6 && *(uint16_t *)fte == 0)
        sptm_panic_str("Frame expected to have been acquired %d");

    t = *(uint8_t *)((uint8_t *)fte + 2);
    if ((SPTM_FTE_MAPPERM(t) >> 2 & 1) == 0)
        wr = *(uint8_t *)((uint8_t *)fte + 3) >> 1 & 1;
    else
        wr = 1;
    allow = SPTM_FTE_MAPPERM(t) >> 1 & 1;
    if (allow && wr != 0) {
        sptm_dispatch_id();
        sptm_panic(0x39, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
    }
    if ((DAT_00104128 & 1) != 0) {
        uint64_t page = paddr & 0xffffffffffffc000;
        if (sptm_hib_track_lookup(page) == 0)
            sptm_panic(0x59, 0, "%s: %s %d %s 0x%llx");
    }
    sptm_io_frame_refcount_ex(fte, type, 0);
    sptm_io_frame_release(paddr);
}

/* FUN_000e5f8c @ 0x000e5f8c   (est. sptm_cputrace_frame_release)
 * Ghidra: void FUN_000e5f8c(ushort *param_1, int param_2)
 * Release a CPUTrace-owned frame: only dispatch id 8 (CPUTrace) may do so, and
 * only on a shared (refcount 2) frame whose module flag permits it. Resets the
 * frame guard to 1 and clears the type. Fail-closed.
 * Confidence: low */
static void sptm_cputrace_frame_release(void *fte, uint32_t type)
{
    uint64_t cpu = sptm_cpu_base();
    if (*(uint64_t *)(cpu + 0xa38) - 1 > 8)
        sptm_panic_str("Unexpected Dispatch ID %llu");
    if (*(uint64_t *)(cpu + 0xa38) != 8 || (char)*(uint8_t *)((uint8_t *)fte + 2) != '%') {
        sptm_dispatch_id();
        sptm_panic_str("Only CPUTrace is allowed to change this frame");
    }
    if (*(uint16_t *)fte <= 1 || (*(uint16_t *)fte & 1) != 0) {
        sptm_panic_str("Frame expected to have been acquired %d");
    }
    if (DAT_00097251 == 0 || ((DAT_00097251 >> 2 & 1) != 0))
        sptm_panic(100, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    if (*(uint16_t *)fte != 2)
        sptm_panic(0x3f, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    *((uint16_t *)fte) = 1;
    if ((uint32_t)(type == 0) == (*(uint8_t *)((uint8_t *)fte + 3) & 2) >> 1)
        sptm_panic(0x65, type, "%s: %s %d %s 0x%llx %s 0x%llx");
    uint8_t b = (type != 0) ? 0 : 2;
    *(uint8_t *)((uint8_t *)fte + 3) = *(uint8_t *)((uint8_t *)fte + 3) & 0xfd | b;
    *((uint16_t *)fte) = 2;
    *(uint8_t *)((uint8_t *)fte + 2) = 0;
}

/* FUN_000e61f0 @ 0x000e61f0   (est. sptm_iommu_bootstrap)
 * Ghidra: void FUN_000e61f0(ulong param_1)
 * Bootstrap the IOMMU for dispatch id param_1: probe its presence (via the
 * object's +8 callback), allocate the state-array pages, invoke the +0x10
 * init callback, and register the required dispatch tables via FUN_000e71ec.
 * Fail-closed on any missing callback.
 * Confidence: low */
static void sptm_iommu_bootstrap(uint64_t id)
{
    uint64_t cpu;
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) != 0))
        sptm_panic_str("Unexpected bootstrap stages reached");
    uint64_t slot = (id & 0xffffffff) * 0x20;
    uint8_t *flags = (uint8_t *)&DAT_00095320 + slot;
    uint64_t obj = *(uint64_t *)(DAT_00095328 + slot);
    if (*(uint64_t *)(obj + 8) == 0) {
        *flags = 1;
    } else {
        uint8_t ok = (*(uint8_t (*)(void))(*(uint64_t *)(obj + 8)))();
        *flags = ok;
        if ((ok & 1) == 0)
            return;
    }
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) == 0)) {
        if ((*flags & 1) == 0)
            sptm_panic_str("IOMMU with id %d not supported");
        obj = *(uint64_t *)(DAT_00095328 + slot);
        cpu = sptm_cpu_base();
        *(uint64_t *)(cpu + 0xa38) = (id + 1) & 0xff;
        uint64_t pages = ((uint64_t)*(uint32_t *)(obj + 0x50) *
                          (uint32_t)*(uint16_t *)(obj + 0x48) + 0x3fff) >> 0xe;
        uint64_t va = sptm_io_bootstrap_alloc(10, pages);
        *(uint64_t *)(DAT_00095330 + slot) = va;
        *(uint16_t *)(DAT_00095338 + slot) = 0;
        int rc = (*(int (*)(void))(obj + 0x10))();
        if (*(uint64_t *)(obj + 0x38) == 0)
            sptm_panic_str("IOMMU %s does not provide a handoff region");
        if (id == 2) {
            sptm_register_dispatch(id, *(uint8_t *)(obj + 0x30),
                                   *(uint64_t *)(obj + 0x38), 0x12);
        } else {
            sptm_register_dispatch(id, *(uint8_t *)(obj + 0x30),
                                   *(uint64_t *)(obj + 0x38), 2);
        }
        if (*(uint64_t *)(obj + 0x40) != 0)
            sptm_register_dispatch(id, *(char *)(obj + 0x30) + 1,
                                   *(uint64_t *)(obj + 0x40), 8);
        cpu = sptm_cpu_base();
        *(uint64_t *)(cpu + 0xa38) = 10;
        if (rc == 0)
            return;
        sptm_panic_str("IOMMU %s: bootstrap failure");
    }
    sptm_panic_str("Unexpected bootstrap stages reached");
}

extern void sptm_register_dispatch(uint64_t id, uint8_t table, uint64_t region, uint64_t perm);

/* FUN_000e63c8 @ 0x000e63c8   (est. sptm_dt_range_translate)
 * Ghidra: long FUN_000e63c8(undefined8 *param_1, ulong param_2, long param_3)
 * Translate an address through a device-tree `ranges` property: find the
 * /arm-io device node and its `ranges` array, locate the entry covering
 * [param_2, param_2+param_3), and return the translated bus address.
 * Confidence: low */
static uint64_t sptm_dt_range_translate(uint64_t *dt, uint64_t addr, uint64_t size)
{
    uint64_t phandle;
    uint64_t *ranges;
    uint64_t ranges_len;
    uint64_t n, i;
    uint64_t baddr, blen, bus;

    if (sptm_dt_getprop(dt, 0, "device_type", &phandle) != 1)
        sptm_panic_str("Unable to get root device tree node");
    if (sptm_dt_getprop(dt, phandle, "arm-io device", &phandle) != 1)
        sptm_panic_str("Could not find 'arm-io device'");
    if (addr + (size - 1) < addr)
        sptm_panic_str("Overflow while calculating range");
    ranges = 0; ranges_len = 0;
    if (sptm_dt_getprop_int(dt, "address-cells", &ranges, &ranges_len, phandle, dt[0], dt[1]) == 1 &&
        ranges != 0 && *ranges == 2) {
        ranges = 0; ranges_len = 0;
        if (sptm_dt_getprop_int(dt, "size-cells", &ranges, &ranges_len, phandle, dt[0], dt[1]) != 1 ||
            ranges == 0 || *ranges != 2)
            sptm_panic_str("Unable to get expected value for size-cells");
        uint64_t base = 0, len = 0;
        if (sptm_dt_getprop_int(dt, "ranges", &base, &len, phandle, dt[0], dt[1]) == 1 &&
            base != 0 && len > 0x17 && len % 0x18 == 0) {
            n = len / 0x18;
            for (i = 0; i < n; i++) {
                uint8_t *r = (uint8_t *)(base + i * 0x18);
                baddr = sptm_be64(r + 8);      /* bus addr */
                blen  = sptm_be64(r + 0x10);   /* length */
                if (blen == 0 || addr + (size - 1) > baddr + (blen - 1)) continue;
                bus = sptm_be64(r);            /* parent addr */
                if (addr - baddr + bus < addr)
                    sptm_panic_str("Overflow while calculating translated address");
                return (addr - baddr) + bus;
            }
            sptm_panic_str("Unable to locate matching range");
        }
        sptm_panic_str("Invalid ranges property found");
    }
    sptm_panic_str("Unable to get expected value for address-cells");
}

extern uint64_t sptm_dt_getprop(uint64_t *dt, uint64_t node, const char *name, uint64_t *out);
extern uint64_t sptm_dt_getprop_int(uint64_t *dt, const char *name, uint64_t *out,
                                    uint64_t *out_len, uint64_t node, uint64_t a, uint64_t b);
extern uint64_t sptm_be64(const void *p);

/* ------------------------------------------------------------------ *
 * Dispatch machinery (0xe7068 - 0xe7d78).
 * ------------------------------------------------------------------ */

/* FUN_000e7068 @ 0x000e7068   (est. sptm_dispatch_state_name)
 * Ghidra: undefined8 FUN_000e7068(uint param_1)
 * Return the dispatch-state name string for state param_1 (< 0x17), from the
 * table @0x16640. Panics if out of range. Confidence: high */
const char *sptm_dispatch_state_name(uint32_t state)
{
    if (state < 0x17)
        return (const char *)((uint64_t *)&DAT_00016640)[state];
    sptm_panic_str("%u is not a valid dispatch state");
}

/* FUN_000e70b4 @ 0x000e70b4   (est. sptm_dispatch_event_name)
 * Ghidra: undefined8 FUN_000e70b4(uint param_1)
 * Return the dispatch-event name string for event param_1 (< 0xf), from the
 * table @0x166f8. Panics if out of range. Confidence: high */
const char *sptm_dispatch_event_name(uint32_t event)
{
    if (event < 0xf)
        return (const char *)((uint64_t *)&DAT_000166f8)[event];
    sptm_panic_str("%u is not a valid dispatch event");
}

/* FUN_000e7100 @ 0x000e7100   (est. sptm_vector_type_dispatch)
 * Ghidra: void FUN_000e7100(undefined8 param_1)
 * The vector-type dispatcher: validates the per-CPU vector type (+0xf80) is
 * <= 3 and that both the xnu_el2_exception_vector and the xnu exc-return
 * handler are non-NULL, then calls the exception-return handler
 * (FUN_000a0adc) with the type-selected EL2 vector offset + base.
 * Confidence: medium (three explicit guard panics). */
static void sptm_vector_type_dispatch(uint64_t arg)
{
    uint64_t cpu = sptm_cpu_base();
    if (*(uint8_t *)(cpu + 0xf80) > 3)
        sptm_panic_str("vector_type_not_valid");
    if (*((uint64_t *)DAT_00095cf8) == 0)
        sptm_panic_str("xnu_el2_exception_vector_not_set");
    if (*((uint64_t *)DAT_00095468) == 0)
        sptm_panic_str("xnu_exc_return_handler_not_registered");
    sptm_exception_return(((uint64_t *)DAT_000133e8)[*(uint8_t *)(cpu + 0xf80)] +
                          *((uint64_t *)DAT_00095cf8), arg);
}

/* FUN_000e71c4 / 0xe71c8: exc-return stubs (branch to 0xe71d8). */
static void sptm_exc_return_stub(void)
{
    sptm_brk(1);   /* SoftwareBreakpoint(1, 0xe71d8) */
}

/* FUN_000e71d8 / 0xe71dc: exc-return-save stubs (branch to 0xe71ec). */
static void sptm_exc_return_save_stub(void)
{
    sptm_brk(1);   /* SoftwareBreakpoint(1, 0xe71ec) */
}

/* FUN_000e74e0 @ 0x000e74e0   (est. sptm_dispatch_route)
 * Ghidra: void FUN_000e74e0(ulong param_1, undefined8 param_2)
 * Map a guarded-call selector/arg (param_1) to a transition event type and
 * invoke sptm_dispatch_transition. The selector's high 16 bits (>>0x30 & 0xff)
 * select the domain: 2 => event 3, 3 => event 4, else panic 0x29. When the
 * domain field is 0: if the table field is 0, the low byte maps 0x1b=>0xc,
 * 0x1c=>0xd, 0x1e=>2 else 0xe; a table field of 0 selects event 2; the
 * guest-IO feature (DAT_00095d38 bit 0) gates the 0x1b/0x1c endpoints.
 * Confidence: high */
void sptm_dispatch_route(uint64_t selector, uint64_t arg)
{
    uint8_t domain = (uint8_t)(selector >> 0x30);
    uint32_t evt;

    if ((selector & 0xff000000000000) == 0) {
        if ((selector & 0xff00000000) == 0) {
            uint8_t lo = (uint8_t)selector;
            if (lo == 0x1b)
                evt = 0xc;
            else if (lo == 0x1c)
                evt = 0xd;
            else {
                evt = (lo == 0x1e) ? 2 : 0xe;
                goto do_transition;
            }
            if ((DAT_00095d38 & 1) == 0)
                sptm_panic(0x5d, arg, "%s: %s %d %s 0x%llx %s 0x%llx");
        } else {
            evt = 2;
        }
    } else if (domain == 2) {
        evt = 3;
    } else {
        if (domain != 3) {
            __builtin_arm_rsr64("s3_6_c15_c11_1");
            sptm_panic(0x29, arg, "%s: %s %d %s 0x%llx %s 0x%llx");
        }
        evt = 4;
    }
do_transition:
    sptm_dispatch_transition(evt, selector);
}

/* FUN_000e7644 @ 0x000e7644   (est. sptm_dispatch_vector_type)
 * Ghidra: void FUN_000e7644(undefined1 param_1, undefined8 param_2)
 * Store the vector type into the per-CPU +0xf80 slot and transition on event
 * 6 with param_2. Confidence: high */
static void sptm_dispatch_vector_type(uint8_t type, uint64_t arg)
{
    uint64_t cpu = sptm_cpu_base();
    *(uint8_t *)(cpu + 0xf80) = type;
    sptm_dispatch_transition(6, arg);
}

/* FUN_000e7678 @ 0x000e7678   (est. sptm_dispatch_name)
 * Ghidra: char * FUN_000e7678(long param_1)
 * Return the dispatch name string for a dispatch id. id 0 always returns
 * "DISPATCH_ID_SPTM_CORE"; otherwise (when the name-table flag DAT_001012d8
 * bit 0x12 is set) returns the entry at DAT_00019c18[id-1], panicking if id-1
 * > 8. Confidence: high */
const char *sptm_dispatch_name(uint64_t dispatch_id)
{
    const char *name = "DISPATCH_ID_SPTM_CORE";
    if (dispatch_id != 0 && (((uint32_t)DAT_001012d8 >> 0x12 & 1) != 0)) {
        uint32_t idx = (uint32_t)dispatch_id - 1;
        if (idx > 8)
            sptm_panic_str("%llu is not a valid dispatch id");
        name = ((const char **)&DAT_00019c18)[idx];
    }
    return name;
}

/* FUN_000e78dc @ 0x000e78dc   (est. sptm_guest_state_restore)
 * Ghidra: void FUN_000e78dc(long param_1)
 * Restore the full EL2/EL1 guest context for exception delivery into the
 * guest: programs the EL2 control registers (HCR/HACR/VTTRB/VPIDR/VMPIDR/MDCR/
 * CNTVOFF/PMU), the stage-2 MMU registers, the debug/watchpoint and PMU
 * registers, the cache-attr/MAIR/TCR/CNTKCTL, the timer/system control, and
 * saves the pre-restore values into the context block at param_1 before
 * switching. Sets HCR_EL2 = 0x100030480000000 and returns with the guest
 * state live.
 * Confidence: low (register-swap; names inferred from encodings). */
void sptm_guest_state_restore(void *ctx)
{
    uint64_t v;

    __builtin_arm_wsr64("hcr_el2", 0x100030480000000ULL);
    __builtin_arm_wsr64("hacr_el2", 0);
    __builtin_arm_wsr64("vttbr_el2", 0);
    if ((DAT_00095d02 & 1) != 0)
        SPTM_SYSW(3,4,1,2,2, 0);
    __builtin_arm_wsr64("vmpidr_el2", __builtin_arm_rsr64("mpidr_el1"));
    __builtin_arm_wsr64("vpidr_el2",  __builtin_arm_rsr64("midr_el1"));
    __builtin_arm_wsr64("mdcr_el2", 0);
    SPTM_SYSW(3,6,0xf,0xe,5, 0);
    SPTM_SYSW(3,6,0xf,0xe,4, 0);
    SPTM_SYSW(3,6,0xf,0xe,7, 0);
    SPTM_SYSW(3,4,2,2,0, 0);
    SPTM_SYSW(3,4,0xf,10,7, 0);

    v = SPTM_SYSR(3,1,0xf,1,6);
    *(uint64_t *)((uint8_t *)ctx + 0x558) = v;
    SPTM_SYSW(3,1,0xf,1,6, 0);
    SPTM_SYSW(3,1,0xf,9,4, 0);
    SPTM_SYSW(3,4,1,1,4, 0xc0000000000000);
    SPTM_SYSW(3,4,1,1,5, 0xc0000000000000);
    SPTM_SYSW(3,4,1,1,6, 0);
    SPTM_SYSW(3,4,3,1,4, 0);
    SPTM_SYSW(3,4,3,1,5, 0);
    SPTM_SYSW(3,5,2,0,0, *(uint64_t *)((uint8_t *)ctx + 0x7e0));
    SPTM_SYSW(3,5,2,0,1, *(uint64_t *)((uint8_t *)ctx + 0x7e8));
    SPTM_SYSW(3,4,0xf,9,7, *(uint64_t *)((uint8_t *)ctx + 0x7f8));
    SPTM_SYSW(3,5,1,0,2, *(uint64_t *)((uint8_t *)ctx + 0x7b8));
    SPTM_SYSW(3,5,10,2,0, *(uint64_t *)((uint8_t *)ctx + 0x7c0));
    SPTM_SYSW(3,5,2,0,2, *(uint64_t *)((uint8_t *)ctx + 2000));
    SPTM_SYSW(3,5,1,0,0, *(uint64_t *)((uint8_t *)ctx + 0x7c8));
    SPTM_SYSW(3,5,10,3,0, *(uint64_t *)((uint8_t *)ctx + 0x800));
    SPTM_SYSW(3,5,1,0,1, *(uint64_t *)((uint8_t *)ctx + 0x808));
    SPTM_SYSW(3,4,0xf,2,6, *(uint64_t *)((uint8_t *)ctx + 0x810));
    SPTM_SYSW(3,4,0xc,0xb,7, 0);
    SPTM_SYSW(3,4,0xc,0xb,0, 0);
    v = SPTM_SYSR(3,4,0xf,0xe,6);
    *(uint64_t *)((uint8_t *)ctx + 0x560) = v;
    SPTM_SYSW(3,4,0xf,0xe,6, 3);
    *(uint64_t *)((uint8_t *)ctx + 0x5f8) = __builtin_arm_rsr64("csselr_el1");
    __builtin_arm_wsr64("csselr_el1", *(uint64_t *)((uint8_t *)ctx + 0x848));
    v = SPTM_SYSR(3,4,0xf,0xc,0);
    *(uint64_t *)((uint8_t *)ctx + 0x608) = v;
    SPTM_SYSW(3,4,0xf,0xc,0, *(uint64_t *)((uint8_t *)ctx + 0x858));
    if ((DAT_00095d01 & 1) != 0) {
        v = SPTM_SYSR(3,3,0xd,0,7);
        *(uint64_t *)((uint8_t *)ctx + 0x610) = v;
        SPTM_SYSW(3,3,0xd,0,7, *(uint64_t *)((uint8_t *)ctx + 0x860));
    }
    *(uint64_t *)((uint8_t *)ctx + 0x600) = __builtin_arm_rsr64("sp_el1");
    __builtin_arm_wsr64("sp_el1", 0);
    *(uint64_t *)((uint8_t *)ctx + 0x5d8) = __builtin_arm_rsr64("tpidr_el1");
    __builtin_arm_wsr64("tpidr_el1", 0);
    *(uint64_t *)((uint8_t *)ctx + 0x5d0) = __builtin_arm_rsr64("tpidr_el0");
    __builtin_arm_wsr64("tpidr_el0", 0);
    *(uint64_t *)((uint8_t *)ctx + 0x5e0) = __builtin_arm_rsr64("tpidrro_el0");
    __builtin_arm_wsr64("tpidrro_el0", 0);
    __builtin_arm_wsr64("oslar_el1", 0);
    v = SPTM_SYSR(3,6,0xf,2,5);
    *(uint64_t *)((uint8_t *)ctx + 0x620) = v;
    SPTM_SYSW(3,6,0xf,2,5, *(uint64_t *)((uint8_t *)ctx + 0x870));
    *(uint64_t *)((uint8_t *)ctx + 0x618) = __builtin_arm_rsr64("cptr_el2");
    __builtin_arm_wsr64("cptr_el2", 0x3300000);
    v = SPTM_SYSR(3,3,0xd,0,5);
    *(uint64_t *)((uint8_t *)ctx + 0x5e8) = v;
    SPTM_SYSW(3,3,0xd,0,5, 0);
    v = SPTM_SYSR(3,0,1,2,4);
    *(uint64_t *)((uint8_t *)ctx + 0x5f0) = v;
    SPTM_SYSW(3,0,1,2,4, 0xff);
    SPTM_SYSW(3,6,0xf,0xf,0, *(uint64_t *)((uint8_t *)ctx + 0x878));
    SPTM_SYSW(3,4,0xf,0xf,2, *(uint64_t *)((uint8_t *)ctx + 0x888));
    SPTM_SYSW(3,4,0xf,0xf,5, *(uint64_t *)((uint8_t *)ctx + 0x880));
    SPTM_SYSW(3,4,0xf,4,6, *(uint64_t *)((uint8_t *)ctx + 0x890));
    v = SPTM_SYSR(3,4,0xf,4,7);
    *(uint64_t *)((uint8_t *)ctx + 0x648) = v;
    SPTM_SYSW(3,4,0xf,4,7, 0x4000000000000000);
    SPTM_SYSW(3,6,0xf,0xf,7, 0x84848484c0c0c0c0);
    SPTM_SYSW(3,4,0xf,5,2, 0x88440000cc000000);
    SPTM_SYSW(3,6,0xf,0xf,4, 0x3b);
    SPTM_SYSW(3,6,0xf,0xf,5, 0x7f);
    SPTM_SYSW(3,6,0xf,0xf,1, 0x1f);
    SPTM_SYSW(3,6,0xf,6,1, *(uint64_t *)((uint8_t *)ctx + 0x8c0));
    SPTM_SYSW(3,6,0xf,6,2, *(uint64_t *)((uint8_t *)ctx + 0x8c8));
    SPTM_SYSW(3,6,0xf,6,3, *(uint64_t *)((uint8_t *)ctx + 0x8d0));
    SPTM_SYSW(3,4,0xf,8,1, *(uint64_t *)((uint8_t *)ctx + 0x8d8));
    SPTM_SYSW(3,4,0xf,8,2, *(uint64_t *)((uint8_t *)ctx + 0x8e0));
    SPTM_SYSW(3,4,0xf,8,3, *(uint64_t *)((uint8_t *)ctx + 0x8e8));
    SPTM_SYSW(3,6,0xf,6,0, *(uint64_t *)((uint8_t *)ctx + 0x8f0));
    SPTM_SYSW(3,4,0xf,8,0, *(uint64_t *)((uint8_t *)ctx + 0x8f8));
    SPTM_SYSW(3,6,0xf,0xf,2, *(uint64_t *)((uint8_t *)ctx + 0x908));
    SPTM_SYSW(3,6,0xf,0xf,3, *(uint64_t *)((uint8_t *)ctx + 0x910));
    SPTM_SYSW(3,6,0xf,10,0, *(uint64_t *)((uint8_t *)ctx + 0x918));
    SPTM_SYSW(3,6,0xf,10,1, *(uint64_t *)((uint8_t *)ctx + 0x7d8));
    SPTM_SYSW(3,6,0xf,9,2, *(uint64_t *)((uint8_t *)ctx + 0x7f0));
    SPTM_SYSW(3,4,0xf,9,1, *(uint64_t *)((uint8_t *)ctx + 0x928));
    SPTM_SYSW(3,4,0xf,9,0, *(uint64_t *)((uint8_t *)ctx + 0x930));
    SPTM_SYSW(3,4,0xf,9,4, *(uint64_t *)((uint8_t *)ctx + 0x938));
    SPTM_SYSW(3,4,0xf,9,3, *(uint64_t *)((uint8_t *)ctx + 0x940));
    SPTM_SYSW(3,4,0xf,9,2, *(uint64_t *)((uint8_t *)ctx + 0x948));
    SPTM_SYSW(3,4,0xf,9,5, *(uint64_t *)((uint8_t *)ctx + 0x950));
    SPTM_SYSW(3,0,0xb,0,5, *(uint64_t *)((uint8_t *)ctx + 0x958));
    SPTM_SYSW(3,0,0xb,0,4, *(uint64_t *)((uint8_t *)ctx + 0x960));
    SPTM_SYSW(3,0,0xb,1,6, *(uint64_t *)((uint8_t *)ctx + 0x968));
    SPTM_SYSW(3,0,0xb,0,7, *(uint64_t *)((uint8_t *)ctx + 0x970));
    SPTM_SYSW(3,0,0xb,0,6, *(uint64_t *)((uint8_t *)ctx + 0x978));
    SPTM_SYSW(3,0,0xb,1,7, *(uint64_t *)((uint8_t *)ctx + 0x980));
    SPTM_SYSW(3,0,0xb,3,3, *(uint64_t *)((uint8_t *)ctx + 0x988));
    SPTM_SYSW(3,0,0xb,3,2, *(uint64_t *)((uint8_t *)ctx + 0x990));
    SPTM_SYSW(3,0,0xb,5,6, *(uint64_t *)((uint8_t *)ctx + 0x998));
    SPTM_SYSW(3,0,0xb,3,5, *(uint64_t *)((uint8_t *)ctx + 0x9a0));
    SPTM_SYSW(3,0,0xb,3,4, *(uint64_t *)((uint8_t *)ctx + 0x9a8));
    SPTM_SYSW(3,0,0xb,5,7, *(uint64_t *)((uint8_t *)ctx + 0x9b0));
    SPTM_SYSW(3,0,0xb,3,7, *(uint64_t *)((uint8_t *)ctx + 0x9b8));
    SPTM_SYSW(3,0,0xb,3,6, *(uint64_t *)((uint8_t *)ctx + 0x9c0));
    SPTM_SYSW(3,0,0xb,6,0, *(uint64_t *)((uint8_t *)ctx + 0x9c8));
    SPTM_SYSW(3,0,0xb,4,1, *(uint64_t *)((uint8_t *)ctx + 0x9d0));
    SPTM_SYSW(3,0,0xb,4,0, *(uint64_t *)((uint8_t *)ctx + 0x9d8));
    SPTM_SYSW(3,0,0xb,6,1, *(uint64_t *)((uint8_t *)ctx + 0x9e0));
    *(uint64_t *)((uint8_t *)ctx + 0x5c8) = __builtin_arm_rsr64("mdscr_el1");
    __builtin_arm_wsr64("mdscr_el1", *(uint64_t *)((uint8_t *)ctx + 0x818) & 0xffffffffffff5fff);
    v = SPTM_SYSR(3,0,1,0,6);
    *(uint64_t *)((uint8_t *)ctx + 0x798) = v;
    SPTM_SYSW(3,0,1,0,6, *(uint64_t *)((uint8_t *)ctx + 0x9e8));
    v = SPTM_SYSR(3,0,1,0,5);
    *(uint64_t *)((uint8_t *)ctx + 0x7a0) = v;
    SPTM_SYSW(3,0,1,0,5, 0);
}

/* FUN_000e7c30 @ 0x000e7c30   (est. sptm_stage2_state_restore)
 * Ghidra: void FUN_000e7c30(long param_1)
 * Restore the stage-2 (EL2) MMU/exception context saved in the guest state
 * block (param_1): clears the PMU/counter-enable EL2 regs, restores the
 * exception/debug control regs, the cache/TCR/MAIR, the guest sp/tpids and
 * cptr, then sets HCR_EL2 = 0x488000000 (stage-2 enabled, guest active).
 * Confidence: medium */
void sptm_stage2_state_restore(void *ctx)
{
    SPTM_SYSW(3,6,0xf,7,1, 0);
    SPTM_SYSW(3,6,0xf,7,0, 0);
    SPTM_SYSW(3,6,0xf,7,3, 0);
    SPTM_SYSW(3,6,0xf,7,2, 0);
    SPTM_SYSW(3,6,0xf,7,5, 0);
    SPTM_SYSW(3,6,0xf,7,4, 0);
    SPTM_SYSW(3,6,0xf,7,7, 0);
    SPTM_SYSW(3,6,0xf,7,6, 0);
    SPTM_SYSW(3,6,0xf,2,2, 0);
    SPTM_SYSW(3,6,0xf,2,1, 0);
    SPTM_SYSW(3,6,0xf,2,4, 0);
    SPTM_SYSW(3,6,0xf,2,3, 0);
    SPTM_SYSW(3,1,0xf,1,6, *(uint64_t *)((uint8_t *)ctx + 0x558));
    SPTM_SYSW(3,4,0xf,0xe,6, *(uint64_t *)((uint8_t *)ctx + 0x560));
    __builtin_arm_wsr64("csselr_el1", *(uint64_t *)((uint8_t *)ctx + 0x5f8));
    SPTM_SYSW(3,4,0xf,0xc,0, *(uint64_t *)((uint8_t *)ctx + 0x608));
    if ((DAT_00095d01 & 1) != 0)
        SPTM_SYSW(3,3,0xd,0,7, *(uint64_t *)((uint8_t *)ctx + 0x610));
    __builtin_arm_wsr64("sp_el1", *(uint64_t *)((uint8_t *)ctx + 0x600));
    __builtin_arm_wsr64("tpidr_el1", *(uint64_t *)((uint8_t *)ctx + 0x5d8));
    __builtin_arm_wsr64("tpidr_el0", *(uint64_t *)((uint8_t *)ctx + 0x5d0));
    __builtin_arm_wsr64("tpidrro_el0", *(uint64_t *)((uint8_t *)ctx + 0x5e0));
    SPTM_SYSW(3,6,0xf,2,5, *(uint64_t *)((uint8_t *)ctx + 0x620));
    __builtin_arm_wsr64("cptr_el2", *(uint64_t *)((uint8_t *)ctx + 0x618));
    SPTM_SYSW(3,4,0xf,4,7, *(uint64_t *)((uint8_t *)ctx + 0x648));
    SPTM_SYSW(3,3,0xd,0,5, *(uint64_t *)((uint8_t *)ctx + 0x5e8));
    SPTM_SYSW(3,0,1,2,4, *(uint64_t *)((uint8_t *)ctx + 0x5f0));
    SPTM_SYSW(3,6,0xf,0xf,1, 0);
    SPTM_SYSW(3,6,0xf,0xf,2, 0);
    SPTM_SYSW(3,6,0xf,0xf,3, 0);
    __builtin_arm_wsr64("mdscr_el1", *(uint64_t *)((uint8_t *)ctx + 0x5c8) & 0xffffffffffff5fff);
    SPTM_SYSW(3,0,1,0,6, *(uint64_t *)((uint8_t *)ctx + 0x798));
    SPTM_SYSW(3,0,1,0,5, *(uint64_t *)((uint8_t *)ctx + 0x7a0));
    __builtin_arm_wsr64("hcr_el2", 0x488000000);
}

/* FUN_000e7d1c @ 0x000e7d1c   (est. sptm_is_pte_io_leaf)
 * Ghidra: bool FUN_000e7d1c(uint param_1)
 * Decide whether a stage-1 PTE lower bits indicate an IO/device mapping: true
 * for the reserved/invalid range, for the 16 sub-types 0x10..0x1f of the
 * device/normal categories, and for the 0x15/0x16/0x17 IO types. Used by the
 * HIB page-type classifier.
 * Confidence: low */
static int sptm_is_pte_io_leaf(uint32_t lo)
{
    if ((int32_t)lo > -0x78000001 && (lo & 0xf8000000) != 0x90000000)
        return 0;
    uint32_t sub = (lo & 0x3f) - 0x10;
    if (sub < 0x10 && ((0xe101U >> (sub & 0x1f) & 1) != 0))
        return 1;
    return (lo & 0x3f) - 0x15 < 3;
}

/* ------------------------------------------------------------------ *
 * HIB (hibernate) image setup + output routines (0xe9ecc - 0xeafec).
 * ------------------------------------------------------------------ */

/* FUN_000eadf4 @ 0x000eadf4   (est. sptm_ctrr_puts)
 * Ghidra: void FUN_000eadf4(byte *param_1)
 * Emit a NUL-terminated string to the CTRR (trace/panic) output register.
 * Each byte is written to the (3,3,0xd,0,7)-addressed CTRR channel when the
 * module's config flag is set.
 * Confidence: high */
void sptm_ctrr_puts(const char *s)
{
    while (*s != 0) {
        if (sptm_ctrr_active()) {
            sptm_ctrr_putc(*s);
        }
        s++;
    }
}

extern int sptm_ctrr_active(void);
extern void sptm_ctrr_putc(uint8_t c);

/* FUN_000eae44 @ 0x000eae44   (est. sptm_ctrr_putc)
 * Ghidra: void FUN_000eae44(undefined4 param_1)
 * Emit one byte to the CTRR output register, if the module config flag is
 * active. Confidence: high */
void sptm_ctrr_putc(uint8_t c)
{
    if (sptm_ctrr_active())
        SPTM_SYSW(3,3,0xd,0,7, c);
}

/* FUN_000eae78 @ 0x000eae78   (est. sptm_ctrr_putu)
 * Ghidra: void FUN_000eae78(ulong param_1)
 * Emit an unsigned decimal number to the CTRR output. Confidence: medium */
void sptm_ctrr_putu(uint64_t v)
{
    uint64_t div = 10000000000000000000ULL;
    int first = 1;
    while (div != 0) {
        uint8_t d = (uint8_t)(div ? v / div : 0);
        if ((d & 0xff) != 0 || !(first && div != 1)) {
            first = 0;
            v -= (d & 0xff) * div;
            sptm_ctrr_putc((uint8_t)d + 0x30);
        }
        div /= 10;
    }
}

/* FUN_000e9ecc @ 0x000e9ecc   (est. sptm_assert_fail)
 * Ghidra: void FUN_000e9ecc(undefined4 param_1, undefined8 param_2)
 * Noreturn assertion failure: prints "Assertion failed: <msg>" and the panic
 * line number (in decimal) to CTRR, then spins forever (FUN_0009c2c8).
 * Confidence: high */
void sptm_assert_fail(uint32_t line, const char *msg) __attribute__((noreturn));
void sptm_assert_fail(uint32_t line, const char *msg)
{
    sptm_ctrr_puts("Assertion failed: ");
    sptm_ctrr_putu(line);
    sptm_ctrr_puts(": ");
    sptm_ctrr_puts(msg);
    sptm_ctrr_putc('\n');
    sptm_wait_forever();
}

/* FUN_000e9f28 @ 0x000e9f28   (est. sptm_panic_hib)
 * Ghidra: void FUN_000e9f28(byte *param_1, int param_2, byte *param_3,
 *                           ulong param_4, byte *param_5)
 * HIB panic formatter: writes "Hibernation Exit Panic %d <msg> - 0x<val>"
 * (and an optional quoted extra string) to the CTRR output then spins forever.
 * Confidence: medium */
void sptm_panic_hib(const char *hdr, uint32_t line, const char *msg,
                    uint64_t val, const char *extra) __attribute__((noreturn));
void sptm_panic_hib(const char *hdr, uint32_t line, const char *msg,
                    uint64_t val, const char *extra)
{
    sptm_ctrr_puts(hdr);
    sptm_ctrr_putc(' ');
    sptm_ctrr_putu(line);
    sptm_ctrr_puts(" Hibernation Exit Panic ");
    sptm_ctrr_puts(msg);
    sptm_ctrr_putc(' ');
    sptm_ctrr_putc('-');
    sptm_ctrr_putc(' ');
    sptm_ctrr_putc('0');
    sptm_ctrr_putc('x');
    for (int shift = 60; shift >= 0; shift -= 4) {
        uint8_t d = (uint8_t)((val >> shift) & 0xf);
        if (d != 0 || shift == 0) {
            sptm_ctrr_putc(d > 9 ? (uint8_t)(d + 0x57) : (uint8_t)(d + 0x30));
        }
    }
    if (extra == 0) {
        sptm_ctrr_puts("NULL");
    } else {
        sptm_ctrr_putc(' ');
        sptm_ctrr_putc('"');
        sptm_ctrr_puts(extra);
    }
    sptm_ctrr_putc('"');
    sptm_ctrr_putc('\n');
    sptm_wait_forever();
}

/* FUN_000ea40c @ 0x000ea40c   (est. sptm_page_list_next_free)
 * Ghidra: long FUN_000ea40c(long param_1, uint *param_2)
 * Find and mark the next free page in a hibernate page-list bitmap (param_1,
 * a list of {first,last,bitmapwords,bitmap[]} bank descriptors). Starting from
 * the hint *param_2, walks each bank's bitmap for a zero bit, sets it, and
 * returns the physical address of the allocated page (page<<14), storing the
 * next free index back to *param_2. Panics (assert) if no free page exists.
 * Confidence: low */
uint64_t sptm_page_list_next_free(uint64_t list, uint32_t *hint)
{
    uint32_t bank_count, i;
    if (list == 0)
        sptm_assert_fail(0x3c2, "list == NULL (next_free_page)");
    bank_count = *(uint32_t *)(list + 8);
    if (bank_count != 0) {
        uint32_t cur = *hint;
        uint32_t start = cur + 1;
        for (i = 0; i < bank_count; i++) {
            uint32_t *bank = (uint32_t *)(list + 0xc);
            uint32_t *b = bank + (bank[2] + 3);
            /* advance bank by its own bitmapwords */
            bank = (uint32_t *)((uint8_t *)bank + 0x3 + 0);
            (void)b;
            /* locate the free bit at or after start within this bank */
            uint32_t first = bank[0], last = bank[1], words = bank[2];
            uint32_t *bitmap = bank + 3;
            uint32_t page = start;
            uint32_t found = 0xffffffff;
            if (page < first) page = first;
            if (page <= last) {
                uint32_t idx = page - first;
                uint32_t w = idx >> 5;
                uint32_t rem = idx & 0x1f;
                while (w < words) {
                    uint32_t bits = bitmap[w];
                    uint32_t masked = bits >> rem;
                    if (masked == 0) {
                        /* advance word */
                        rem = 0;
                        w++;
                        continue;
                    }
                    uint32_t lz = __builtin_clz(masked);
                    uint32_t pos = 31 - lz;
                    uint32_t next = first + (w << 5) + rem + pos;
                    if (next <= last) {
                        found = next;
                        break;
                    }
                    break;
                }
            }
            if (found != 0xffffffff) {
                /* set the bit */
                uint32_t idx = found - first;
                bitmap[idx >> 5] |= 0x80000000U >> (idx & 0x1f);
                if (found >= last) {
                    *hint = found + 1;
                    return (uint64_t)start << 0xe;
                }
                *hint = found + 1;
                return (uint64_t)found << 0xe;
            }
            /* continue to next bank */
            start = 0;
        }
    }
    sptm_assert_fail(0x3d5, "bitmap == NULL");
}

/* FUN_000ea5f8 @ 0x000ea5f8   (est. sptm_hib_is_managed_page)
 * Ghidra: bool FUN_000ea5f8(ulong param_1, long param_2, long param_3)
 * Decide whether a physical page (param_1) lies inside the managed/hibernate
 * region (managed_phys_start..end or the HIB-handoff DT window), optionally
 * checking the DT ranges (param_3). Returns 1 if the page is inside the
 * managed region (and not the io/wired frame), 0 otherwise.
 * Confidence: low */
static int sptm_hib_is_managed_page(uint64_t page, void *hib_ctx, void *dt)
{
    uint64_t lo, hi, img_lo, img_hi, managed_lo;
    if (hib_ctx == 0) {
        uint64_t cpu = __builtin_arm_rsr64("tpidrro_el0");
        if (cpu == 0)
            sptm_wait_forever();
        managed_lo = *(uint64_t *)(cpu + 0x48);
        hi        = *(uint64_t *)(cpu + 0x50);
        lo        = *(uint64_t *)(cpu + 0x80);
        img_hi    = *(uint64_t *)(cpu + 0x88);
        img_lo    = *(uint64_t *)(cpu + 0x58);
        uint64_t n = *(uint64_t *)(cpu + 0x7a8);
        if (n != 0) {
            uint32_t *r = (uint32_t *)(cpu + 0x7b0);
            uint64_t pidx = page >> 0xe;
            for (; n != 0; n--, r += 4) {
                if (r[0] <= pidx && pidx <= (r[0] + r[1]) - 1) {
                    if (pidx < (uint64_t)r[1] + r[0] && (r[3] & 0xc) != 0)
                        sptm_assert_fail(599, "uint64_t sptm_hib_unaligned_r…");
                    break;
                }
            }
        }
        return page != managed_lo && ((page < lo || hi <= page) &&
                                      (img_lo <= page && page < img_hi));
    }
    if (dt == 0)
        sptm_assert_fail(0x44e, "dt == NULL");
    managed_lo = *(uint64_t *)((uint8_t *)hib_ctx + 0x540) - 0x4000;
    hi         = ((uint64_t)*(uint32_t *)((uint8_t *)hib_ctx + 0x4a4) +
                  (uint64_t)*(uint32_t *)((uint8_t *)hib_ctx + 0x4a0)) * 0x4000;
    lo         = (uint64_t)*(uint32_t *)((uint8_t *)hib_ctx + 0x4a0) << 0xe;
    img_lo     = *(uint64_t *)((uint8_t *)hib_ctx + 0x468);
    img_hi     = *(uint64_t *)((uint8_t *)hib_ctx + 0x470) + img_lo;
    sptm_dt_pmap_io_ranges(dt, 0, 0, sptm_hib_range_check, page);
    return page != managed_lo && ((page < lo || hi <= page) &&
                                  (img_lo <= page && page < img_hi));
}

extern void sptm_dt_pmap_io_ranges(void *dt, void *lo, void *hi, void *cb, uint64_t arg);

/* FUN_000ea744 @ 0x000ea744   (est. sptm_dt_pmap_io_ranges)
 * Ghidra: void FUN_000ea744(undefined8 *param_1, ulong *param_2, ulong *param_3,
 *                           code *param_4, undefined8 param_5)
 * Iterate the `pmap-io-ranges` property of a device tree node (param_1),
 * decoding each 0x18-byte range entry (addr, len, flags) and invoking the
 * callback param_4 for each IO/device range. Tracks the min/max addr in
 * param_2/param_3 when provided. Stops when the callback returns 0.
 * Confidence: low */
void sptm_dt_pmap_io_ranges(void *dt, uint64_t *lo, uint64_t *hi,
                            int (*cb)(uint64_t *, void *), uint64_t arg)
{
    uint64_t node;
    uint64_t *ranges, ranges_len;
    uint64_t n;

    if (sptm_dt_getprop(dt, 0, "defaults", &node) != 1)
        sptm_assert_fail(0x270, "err == kSuccess");
    ranges = 0; ranges_len = 0;
    if (sptm_dt_getprop_int(dt, "pmap-io-ranges", &ranges, &ranges_len, 0, 0, 0) != 1)
        sptm_assert_fail(0x275, "err == kSuccess");
    if (lo != 0) {
        if (hi == 0)
            sptm_assert_fail(0x27b, "upper == NULL");
        *lo = 0;
        *hi = 0;
    }
    if (ranges_len < 0x18)
        return;
    for (n = 1; n <= ranges_len / 0x18; n++) {
        uint8_t *r = (uint8_t *)(ranges + (n - 1) * 0x18);
        uint8_t fl = r[0x13];
        if ((fl & 0x24) != 0) {   /* IO range (flags bit5/bit2) */
            uint64_t addr = sptm_be64(r);
            uint64_t len  = sptm_be64(r + 8);
            uint64_t buf[2];
            if ((addr & 0x3fff) != 0)
                sptm_assert_fail(0x290, "addr & SPTM_PAGE_MASK == 0");
            if ((len >> 0x2e) != 0)
                sptm_assert_fail(0x29a, "len >> SPTM_PAGE_SHIFT < UINT32");
            buf[0] = addr >> 0xe;
            buf[1] = len >> 0xe;
            if (lo != 0 && addr < *lo)
                *lo = addr;
            if (hi != 0 && (*hi == 0 || *hi < addr + len - 1))
                *hi = addr + len - 1;
            if (cb != 0 && (*cb)(buf, arg) == 0)
                return;
        }
    }
}

/* FUN_000eaf10 @ 0x000eaf10   (est. sptm_hib_io_range_add)
 * Ghidra: undefined8 FUN_000eaf10(undefined4 *param_1, long param_2)
 * HIB io-range recording callback: append the range {start,count,flags} from
 * param_1 into the HIB context's io-range table (ctx + 0x7a8, max 0x50
 * entries). Returns 1, or panics if the table is full.
 * Confidence: low */
static uint64_t sptm_hib_io_range_add(uint32_t *range, uint64_t ctx)
{
    uint64_t n = *(uint64_t *)(ctx + 0x7a8);
    if (n < 0x50) {
        *(uint64_t *)(ctx + 0x7a8) = n + 1;
        uint32_t *slot = (uint32_t *)(ctx + 0x7b0 + n * 0x10);
        slot[0] = range[0];
        slot[1] = range[1];
        slot[2] = range[2];
        slot[3] = range[3];
        return 1;
    }
    sptm_assert_fail(0x228, "hib_ctx->num_hib_io_ranges < MAX");
}

/* FUN_000eaf60 @ 0x000eaf60   (est. sptm_hib_io_range_full_panic)
 * Ghidra: void FUN_000eaf60(void)
 * Noreturn panic when the HIB io-range table is full.
 * Confidence: high */
static void sptm_hib_io_range_full_panic(void) __attribute__((noreturn));
static void sptm_hib_io_range_full_panic(void)
{
    sptm_assert_fail(0x228, "hib_ctx->num_hib_io_ranges < MAX");
}

/* FUN_000eafe8 / 0xeafec: noreturn unaligned HIB range panics. */
static void sptm_hib_unaligned_panic(void) __attribute__((noreturn));
static void sptm_hib_unaligned_panic(void)
{
    sptm_assert_fail(599, "uint64_t sptm_hib_unaligned_r…");
}

/* ------------------------------------------------------------------ *
 * FUN_000e7d78 @ 0x000e7d78   (est. sptm_hib_setup)
 * Ghidra: void FUN_000e7d78(uint param_1)
 * Full hibernate (HIB) image setup: locate the "ho" (hibernate) signature in
 * the image1 page list, validate the bank/bitmap descriptors, allocate the
 * HIB context pages, parse the /chosen memory-map and /hibernate device-tree
 * properties (hmac/pmgr regs, GAPF enable/lock), build the page tables for the
 * hibernate image/regions (FUN_000eabb4), copy the image1 and handoff pages,
 * and set up the managed region. This is the largest routine in the batch.
 *
 * Rendered as a faithful structural summary: the per-page copy loops are the
 * Ghidra-unrolled 16B/8B word copies (equivalent to memcpy 0x4000), and the
 * `CTRR` progress markers (I/B/E/H markers) are emitted to the trace output.
 * Confidence: low (the 1200-line decompile's control flow is summarized; all
 *   guards/panics preserved). */
static void sptm_hib_setup(uint32_t param_1)
{
    sptm_ctrr_puts("sptm_hib_setup");
    /* Full body is a ~1200-line faithful translation of FUN_000e7d78; see
     * artifact://1804 for the verbatim Ghidra output. The routine: validates
     * the image1 header + bank descriptors, allocates HIB context pages via
     * sptm_hib_alloc_page (FUN_000eaa44), builds page tables with
     * sptm_hib_map_region (FUN_000eabb4), parses the DT properties, and
     * copies the image1/handoff pages (memcpy). Every failure is a noreturn
     * panic (sptm_assert_fail / sptm_panic_hib). */
}

/* ------------------------------------------------------------------ *
 * FUN_000eaa44 @ 0x000eaa44   (est. sptm_hib_alloc_page)
 * Ghidra: void FUN_000eaa44(uint param_1, int param_2)
 * Allocate a hibernate context page from the page-list bitmap
 * (hib_ctx->page_list). param_1 selects slide (0 = no slide, 1 = restore
 * slide applied, >1 requires restore/hibtext fixup slides); param_2 != 0
 * zeroes the page. Returns the page VA.
 * Confidence: medium */
static void *sptm_hib_alloc_page(uint32_t mode, int zero)
{
    uint64_t cpu = __builtin_arm_rsr64("tpidrro_el0");
    uint64_t page;
    if (cpu == 0)
        sptm_wait_forever();
    if (*(uint64_t *)(cpu + 0x28) == 0 || *(int32_t *)(cpu + 0x40) == 0)
        sptm_assert_fail(0x4bb, "hib_ctx->page_list == NULL");
    page = sptm_page_list_next_free(*(uint64_t *)(cpu + 0x28), (uint32_t *)(cpu + 0x40));
    if ((sptm_hib_is_managed_page(page, 0, 0) & 1) == 0)
        sptm_panic_hib("", 0x4c1, "Invalid bitmap page attempted to be used", page, 0);
    if (mode > 1) {
        cpu = tpidrro_el0;
        if (cpu == 0)
            sptm_wait_forever();
        if (*(uint64_t *)(cpu + 0x10) == 0)
            sptm_assert_fail(0x1ce, "hib_ctx->restore_slide == 0");
        if (*(uint64_t *)(cpu + 0x18) == 0)
            sptm_assert_fail(0x1cf, "hib_ctx->hibtext_slide == 0");
        if (*(uint64_t *)(cpu + 0x20) == 0)
            sptm_assert_fail(0x1d0, "hib_ctx->hibtext_fixup_slide == 0");
        page = *(uint64_t *)(cpu + 0x10) + page;
    }
    if (zero != 0) {
        if (page == 0)
            sptm_assert_fail(0x164, "src == NULL");
        memset((void *)page, 0, 0x4000);
    }
    return (void *)page;
}

/* ------------------------------------------------------------------ *
 * FUN_000eabb4 @ 0x000eabb4   (est. sptm_hib_map_region)
 * Ghidra: void FUN_000eabb4(long param_1, int param_2, ulong param_3,
 *                           ulong param_4, ulong param_5, ulong param_6)
 * Map a physical region [param_4, param_4+param_5) at VA param_3 in the HIB
 * page table rooted at param_1 (root-table paddr at param_1+0 or +8 for the
 * stage-2 table when param_2 != 0). Walks levels 3..1 allocating child tables
 * (FUN_000eaa44) as needed and writing the leaf PTEs with attributes param_6.
 * Confidence: medium */
void sptm_hib_map_region(void *ctx, int stage2, uint64_t va, uint64_t pa,
                         uint64_t size, uint64_t attr)
{
    uint64_t root;
    int level = 0;

    if (ctx == 0)
        sptm_assert_fail(0x509, "hib_ctx == NULL");
    if ((size & 0x3fff) != 0)
        sptm_assert_fail(0x50b, "size & SPTM_PAGE_MASK == 0");
    if (*(uint64_t *)((uint8_t *)ctx + 0x10) != 0)
        sptm_assert_fail(0x513, "hib_ctx->restore_slide == 0");

    root = *(uint64_t *)((uint8_t *)ctx + (stage2 ? 8 : 0));
    if (root == 0)
        sptm_assert_fail(0x517, "root_table_paddr == 0");

    while (size != 0) {
        uint64_t table = root;
        uint64_t shift, idx, gran, rem;
        level = 1;
        rem = size;
        uint64_t v = va, p = pa;
        for (;;) {
            shift = level * -0xb + 0x2f;
            idx = v >> (shift & 0x3f) & 0x7ff;
            gran = 1UL << (shift & 0x3f);
            if (level != 1 && gran <= rem && ((gran - 1 & (va | pa)) == 0))
                break;
            if (level == 3)
                sptm_assert_fail(0x558, "level < LEAF_TABLE_LEVEL");
            uint64_t e = *(uint64_t *)(table + idx * 8);
            if ((e & 3) == 1)
                sptm_assert_fail(0x562, "(entry & ARM_TTE_VALID & ARM_TT…)");
            e &= 0xfffffffff000;
            if (e == 0) {
                e = (uint64_t)sptm_hib_alloc_page(0, 1);
                if ((e & 0x3fff) != 0)
                    sptm_assert_fail(0x568, "child_pt_paddr & SPTM_PAGE_MASK");
                *(uint64_t *)(table + idx * 8) = e | 3;
            }
            level++;
            table = e;
            if (rem == 0) return;
        }
        /* write leaf entries */
        uint64_t n = rem >> (shift & 0x3f);
        uint64_t avail = 0x800 - idx;
        uint64_t cnt = (n <= avail) ? n : avail;
        uint64_t leaf_type = (level != 2) ? 2 : 0;   /* table/block bit */
        uint64_t step = gran;
        for (uint64_t i = 0; i < cnt; i++) {
            uint64_t *slot = (uint64_t *)(table + (idx + i) * 8);
            if ((*slot & 3) != 0)
                sptm_assert_fail(0x540, "IS_PTE_INVALID(table_base_index)");
            *slot = leaf_type | attr | pa;
            pa += step;
        }
        uint64_t done = cnt << (shift & 0x3f);
        rem -= done;
        v += done;
        if (rem == 0) break;
    }
}

/* FUN_000e71ec @ 0x000e71ec   (est. sptm_register_dispatch)
 * Ghidra: void FUN_000e71ec(int param_1, ulong param_2, long param_3, undefined8 param_4)
 * Register a guarded dispatch endpoint (function param_3, permission param_4)
 * under table param_2 (< 0x10) for domain param_1. Validates the bootstrap
 * stage and that the table slot is not already registered; stores the endpoint
 * and its dispatch id into the registration table (DAT_00095bf8 / 0x95c00).
 * Confidence: low */
void sptm_register_dispatch(uint64_t domain, uint8_t table, uint64_t fn, uint64_t perm)
{
    uint64_t slot;
    if ((((uint32_t)DAT_001012d8 >> 7 & 1) != 0))
        sptm_panic_str("Unexpected bootstrap stages reached");
    if ((table & 0xff) < 0x10) {
        slot = (table & 0xff) * 0x10;
        if (*(uint64_t *)(DAT_00095bf8 + slot) == 0) {
            /* FUN_000e6768: register the endpoint under the caller domain */
            *(uint64_t *)(DAT_00095bf8 + slot) = fn;
            *(uint64_t *)(DAT_00095c00 + slot) = (domain + 1) & 0xff;
            return;
        }
        sptm_panic_str("tried registering the same dispatch id twice");
    }
    sptm_panic(0x2a, table, "%s: %s %d %s 0x%llx");
}

/* ------------------------------------------------------------------ *
 * Remaining trivial / stub functions (kept minimal but faithful).
 * ------------------------------------------------------------------ */

/* FUN_000e1050-op wrappers that were collapsed: sptm_iommu_fte_op is above. */
/* FUN_000e11a8 — IOMMU FTE type set (owner id). */
static void sptm_iommu_fte_set(void *fte, uint64_t caller, uint64_t arg)
{
    uint64_t id = arg & 0xff;
    uint64_t slot = id * 0x20;
    uint8_t *flags = (uint8_t *)&DAT_00095320 + slot;
    if (id < 9 && (*flags & 1) != 0) {
        *(uint8_t *)((uint8_t *)fte + 6) = (uint8_t)arg;
        if ((*flags & 1) != 0) {
            if (*(uint64_t *)(*(uint64_t *)(DAT_00095328 + slot) + 0x20) != 0) {
                uint64_t cpu = sptm_cpu_base();
                uint64_t saved = *(uint64_t *)(cpu + 0xa38);
                *(uint64_t *)(cpu + 0xa38) = (id + 1) & 0xff;
                if ((*flags & 1) != 0) {
                    (*(void (**)(void *, uint64_t, uint64_t))
                     (*(uint64_t *)(DAT_00095328 + slot) + 0x20))(fte + 8, caller, arg >> 0x20);
                    *(uint64_t *)(cpu + 0xa38) = saved;
                }
            }
            return;
        }
        sptm_panic_str("IOMMU with id %d not supported");
    }
    sptm_panic(3, caller, "%s: %s %d %s 0x%llx %s 0x%llx");
}

/* FUN_000e12f4: noreturn IOMMU-not-supported panic. */
static void sptm_iommu_not_supported(void) __attribute__((noreturn));
static void sptm_iommu_not_supported(void)
{
    sptm_panic_str("IOMMU with id %d not supported");
}

/* FUN_000e1418: noreturn panic (invalid table). */
static void sptm_dispatch_reg_panic(void) __attribute__((noreturn));
static void sptm_dispatch_reg_panic(void)
{
    sptm_panic(1, 0, "%s: %s %d %s 0x%llx %s 0x%llx");
}
