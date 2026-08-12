/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers two subsystems:
 *  1. CPU-trace (SPTM_CPUTRACE) — the guarded-level driver for the SoC CPU
 *     trace unit (address-comparator based VA/PA trace window programming,
 *     trace-unit power/programming via EL3 IMP-DEF system registers, and
 *     per-frame locking of a 16 KiB-aligned VA trace window).
 *  2. Hibernation integrity (SPTM_HIB_DOMAIN) — the SHA-2 based hashing of the
 *     hibernation image (hibseg pages + all non-wired pages) and its
 *     verification on resume. The non-wired hash check is the hibernation
 *     integrity gate.
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
uint64_t read_mpidr_el1(void);
uint64_t read_cntpct(void);   /* s3_3_c14_0_6 counter */
uint64_t read_cntfrq_el0(void);

/* Current cputrace state code (FUN_000bc75c). */
uint8_t sptm_cputrace_state_code(void);

/* Guard / rw-lock primitives.
 * sptm_guard_get returns {guard_ptr, other} from a resource handle. FUN_000e2480 */
struct sptm_guard_pair { uintptr_t guard; uint64_t other; };
struct sptm_guard_pair sptm_guard_get(uint64_t handle);
/* Acquire (op 0) / release (op 1) a resource rw-guard. FUN_000e5f8c */
void sptm_guard_op(uint16_t *guard, int op);
/* Lightweight object release (ARC-style). FUN_000ae5e8 counterpart on xnu. */
void sptm_lo_release(void);

/* Validate a SPTM trace request into a {base, other} descriptor pair.
 * FUN_000f7d60 */
struct sptm_region_desc { uint64_t base; uint64_t other; };
struct sptm_region_desc sptm_validate_trace_request(uint64_t request);

/* Region lock / lookup returning an opaque handle; used by the VA trace
 * frame lock/unlock to pin the frame within the SPTM region window.
 * FUN_000d8a58 */
uint64_t sptm_region_handle(uint64_t paddr);

/* Resource-type metadata table. at 0x00095d50, stride 0x90.
 *  +0  type code (0x03 = SK-owned, 0x04 = MTE tag page)
 *  +1  subtype / guard class (guard objects use offset 1 as their type)
 *  +2  flags (bit0 = active / hash-capable)
 *  +6  marker (0xFF = uninitialized/unknown type) */
extern const uint8_t sptm_res_type_table[];   /* DAT_00095d50 */
#define RES_TYPE(t, off)     (sptm_res_type_table[(t) * 0x90 + (off)])

/* Re-sign an SPTM-internal pointer that has been PAC-stripped: if the high
 * address bits do not match the expected tag, drop to 48 bits and re-apply
 * the 0xc8a2 address tag. */
static uintptr_t
sptm_pac_resign(uintptr_t p)
{
    if ((p & 0xffc0000000000000ULL) != 0) {
        p = (p & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
    }
    return p;
}

/* ============================================================================
 * CPU-trace global state (DAT_00095d40).
 * ==========================================================================*/
/* The trace unit has two independently-programmable address windows ("VA"
 * and "PA") and per-cluster instance registers. Layout below is the observed
 * byte layout of the DAT_00095d40 state struct. */
typedef struct sptm_cputrace_state {
    uint8_t  pad0[0x0a];        /* 0x00 */
    uint8_t  cpu0_present;      /* 0x0a  per-cpu instance-present byte (cluster 0) */
    uint8_t  pad1;              /* 0x0b */
    uint8_t  pad2;              /* 0x0c */
    uint8_t  cpu1_present;      /* 0x0e  per-cpu instance-present byte (cluster 1) */
    uint8_t  pad3;              /* 0x0f */
    uint8_t  available;         /* 0x10  cputrace available (mode 0) */
    uint8_t  active;            /* 0x11  cputrace active (mode 1) */
    uint8_t  pad4[0x18 - 0x12]; /* 0x12 */
    uint64_t carveout_start;    /* 0x18  trace carve-out physical range start */
    uint64_t carveout_size;     /* 0x20  trace carve-out size */
    uint8_t  state_guard;       /* 0x28  reentrancy / state guard byte */
    uint8_t  cpu0_active0;      /* 0x29  cluster0 window0 active flag */
    uint8_t  cpu0_index0;       /* 0x2a  cluster0 window0 index */
    uint8_t  cpu0_active1;      /* 0x2b  cluster0 window1 active flag */
    uint8_t  cpu0_index1;       /* 0x2c  cluster0 window1 index */
    uint8_t  cpu1_active0;      /* 0x2d  cluster1 window0 active flag */
    uint8_t  cpu1_index0;       /* 0x2e  cluster1 window0 index */
    uint8_t  cpu1_active1;      /* 0x2f  cluster1 window1 active flag */
    uint8_t  cpu1_index1;       /* 0x30  cluster1 window1 index */
    uint8_t  pad5[0x38 - 0x31]; /* 0x31 */
    uint64_t region_start;      /* 0x38  VA trace frame window start */
    uint64_t region_size;       /* 0x40  VA trace frame window size */
    /* 0x48  region reference-count array, stride 0x18 (only the first int of
     * each 24-byte entry is used). */
} sptm_cputrace_state_t;

#define SPTM_CPUTRACE_STATE ((sptm_cputrace_state_t *)0x00095d40)

/* per-cpu trace entry = state + (cluster)*4; cluster = (mpidr>>8)&1 */
static uint8_t *
sptm_cputrace_cpu_entry(void)
{
    uint64_t mpidr = read_mpidr_el1();
    return (uint8_t *)SPTM_CPUTRACE_STATE + ((mpidr >> 8) & 1) * 4;
}

/* value written into the state guard when entering a cputrace critical
 * section; derived from the per-cpu instance-present byte. */
static uint8_t
sptm_cputrace_guard_value(uint64_t percpu)
{
    return (uint8_t)((*(uint8_t *)(percpu + 10) << 1) | 1);
}

static void
sptm_cputrace_release_guard(void)
{
    uint64_t percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != sptm_cputrace_guard_value(percpu)) {
        sptm_panic_assert("state guard release failed 0x%llx");
    }
    SPTM_CPUTRACE_STATE->state_guard = 0;
}

/* ref-count entry for VA trace window usage, stride 0x18 at +0x48 */
static int32_t *
sptm_cputrace_refcnt(unsigned index)
{
    return (int32_t *)((uint8_t *)SPTM_CPUTRACE_STATE + 0x48 + index * 0x18);
}

/* ----------------------------------------------------------------------------
 * FUN_000bc6f0  sptm_cputrace_va_stop
 * Ghidra: void FUN_000bc6f0(void)
 * Stops the VA CPU-trace window: writes 0 to the trace VA stop/start control
 * register (s3_5_c15_c11_2). If tracing is not active, panics. Confidence:
 * high. Notes: register op0=3 op1=5 CRn=0xf CRm=0xb op2=2, value 0. */
void
sptm_cputrace_va_stop(void)
{
    if (SPTM_CPUTRACE_STATE->active != 0) {
        /* stop VA trace window */
        sptm_sysreg_write(3, 5, 0xf, 0xb, 2, 0);
        return;
    }
    sptm_cputrace_state_code();
    sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bc78c  sptm_cputrace_va_start
 * Ghidra: void FUN_000bc78c(void)
 * Starts the VA CPU-trace window: writes 1 to the trace VA stop/start control
 * register (s3_5_c15_c11_2). If tracing is not active, panics. Confidence:
 * high. Notes: same register as sptm_cputrace_va_stop, value 1. */
void
sptm_cputrace_va_start(void)
{
    if (SPTM_CPUTRACE_STATE->active != 0) {
        /* start VA trace window */
        sptm_sysreg_write(3, 5, 0xf, 0xb, 2, 1);
        return;
    }
    sptm_cputrace_state_code();
    sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bc7fc  sptm_cputrace_va_set_base
 * Ghidra: void FUN_000bc7fc(char, ulong, ulong, byte)
 * Programs the VA trace address window into one of the two per-window
 * comparator registers (s3_5_c15_c3_6 for window 0, s3_5_c15_c3_7 for
 * window 1). The VA base must be 16 KiB aligned, the size 128 KiB aligned
 * and within the currently-locked frame region window (+0x38/+0x40). Packs
 * value = (size << 24) | (base >> 14) | 0x8000000000000000. Maintains a
 * per-window refcount (+0x48) and active/index flags. Confidence: high.
 * Notes: `reject` (param_1) nonzero is a caller error; index (param_4) > 1
 *   is rejected; base>>0x3e must be >= 3 (kernel VA space). */
void
sptm_cputrace_va_set_base(int reject, uint64_t va_base, uint64_t size, uint8_t index)
{
    uint64_t value;
    uint64_t mpidr, percpu;
    uint8_t *cpu_entry;
    uint8_t old_active, old_index;

    if (SPTM_CPUTRACE_STATE->active == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    if (reject != 0) {
        sptm_panic(0x8000003, va_base, "%s(%s:%d)");
    }
    if (index > 1) {
        sptm_panic(0x8000001, va_base, "%s(%s:%d)");
    }
    percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != 0) {
        sptm_panic(0x8000008, va_base,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    SPTM_CPUTRACE_STATE->state_guard = sptm_cputrace_guard_value(percpu);

    if (va_base == 0 && size == 0) {
        value = 0;      /* disable the window */
    } else {
        if (size == 0 || (va_base + size < va_base) || (va_base & 0x3fff) != 0 ||
            (size & 0x1ffff) != 0 || (va_base >> 0x3e) < 3) {
            /* misaligned, overflowed, or non-kernel-VA window */
            sptm_panic(0x8000005, va_base, "%s(%s:%d)");
        }
        /* the window must lie inside the locked frame region */
        if ((SPTM_CPUTRACE_STATE->region_start + SPTM_CPUTRACE_STATE->region_size <
             SPTM_CPUTRACE_STATE->region_start) ||
            va_base < SPTM_CPUTRACE_STATE->region_start ||
            (SPTM_CPUTRACE_STATE->region_start + SPTM_CPUTRACE_STATE->region_size) <
                va_base + size) {
            sptm_panic(0x8000005, va_base, "%s(%s:%d)");
        }
        if ((size >> 0x11) == 0) {
            sptm_panic_assert("nb_units failed");
        }
        if (((size & 0xffffffffff) >> 0x27) != 0) {
            sptm_panic_assert("size_limit >> PROD_TRACE");
        }
        value = (size << 0x18) | ((va_base >> 0xe) & 0x3ffffffff) | 0x8000000000000000ULL;
    }

    mpidr = read_mpidr_el1();
    if ((mpidr & 0xfe00) != 0) {
        sptm_panic_assert("cluster_id < MAX_CPUS");
    }
    cpu_entry = (uint8_t *)SPTM_CPUTRACE_STATE + ((mpidr >> 8) & 1) * 4;

    if (index == 0) {
        old_active = cpu_entry[0x29];
        old_index  = cpu_entry[0x2a];
        sptm_sysreg_write(3, 5, 0xf, 3, 6, value);
        cpu_entry[0x29] = (value != 0);
        cpu_entry[0x2a] = 0;
    } else {
        old_active = cpu_entry[0x2b];
        old_index  = cpu_entry[0x2c];
        sptm_sysreg_write(3, 5, 0xf, 3, 7, value);
        cpu_entry[0x2b] = (value != 0);
        cpu_entry[0x2c] = 0;
    }

    /* release the old window's refcount */
    if ((old_active & 1) != 0) {
        int32_t *rc = sptm_cputrace_refcnt(old_index);
        if (*rc == 0) {
            sptm_panic_assert("region->active_refcnt");
        }
        *rc -= 1;
    }
    /* take a refcount for the newly programmed window */
    if (value != 0) {
        int32_t *rc = sptm_cputrace_refcnt(0);
        int32_t old = *rc;
        *rc = old + 1;
        if (old == -1) {
            sptm_panic_assert("region->active_refcnt");
        }
    }

    sptm_cputrace_release_guard();
}

/* ----------------------------------------------------------------------------
 * FUN_000bcbb0  sptm_cputrace_va_deinit
 * Ghidra: void FUN_000bcbb0(undefined8, undefined8)
 * Powers down the CPU trace unit for the current CPU cluster: clears both VA
 * window bases, disables the trace (clears status bit 1), waits for the
 * trace to drain (status bits[23:16]==0), re-arms bit 2, waits for the
 * programmed bit (bit 36), clears the control register and the 
 * s3_5_c15_c11_1 register, then clears status bit 0. Only valid when neither
 * window is active. Confidence: high. Notes: 1 ms poll timeout using
 * CNTPCT/CNTFRQ, WFE-backed. */
void
sptm_cputrace_va_deinit(uint64_t arg1, uint64_t arg2)
{
    uint64_t percpu, mpidr, status, start, frq, now;
    uint8_t *cpu_entry;

    if (SPTM_CPUTRACE_STATE->active == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != 0) {
        sptm_panic(0x8000008, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    SPTM_CPUTRACE_STATE->state_guard = sptm_cputrace_guard_value(percpu);

    mpidr = read_mpidr_el1();
    if ((mpidr & 0xfe00) != 0) {
        sptm_panic_assert("cluster_id < MAX_CPUS");
    }
    cpu_entry = (uint8_t *)SPTM_CPUTRACE_STATE + ((mpidr >> 8) & 1) * 4;

    if (((cpu_entry[0x29] & 1) == 0) && ((cpu_entry[0x2b] & 1) == 0)) {
        /* neither VA window active: safe to power down */
        sptm_sysreg_write(3, 5, 0xf, 3, 6, 0);
        sptm_sysreg_write(3, 5, 0xf, 3, 7, 0);
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        sptm_sysreg_write(3, 5, 0xf, 5, 7, status & ~2ULL);   /* clear bit1 = stop */
        __asm__ volatile("dsb sy" ::: "memory");
        start = read_cntpct();
        frq   = read_cntfrq_el0();
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        while ((status & 0xff00000) != 0) {                   /* drain until bits[23:16] clear */
            __asm__ volatile("dsb sy" ::: "memory");
            now = read_cntpct();
            if ((frq & 0xfffffff8) / 1000 + start <= now) {
                sptm_panic_assert("CPUTrace condition: cputrace failed to drain");
            }
            __asm__ volatile("wfe");
            status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        }
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        sptm_sysreg_write(3, 5, 0xf, 5, 7, status | 4);       /* set bit2 */
        __asm__ volatile("dsb sy" ::: "memory");
        start = read_cntpct();
        frq   = read_cntfrq_el0();
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        while (((status >> 0x24) & 1) == 0) {                 /* wait programmed bit 36 */
            __asm__ volatile("dsb sy" ::: "memory");
            now = read_cntpct();
            if ((frq & 0xfffffff8) / 1000 + start <= now) {
                sptm_panic_assert("CPUTrace condition: cputrace failed to program");
            }
            __asm__ volatile("wfe");
            status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        }
        sptm_sysreg_write(3, 5, 0xf, 4, 7, 0);                /* clear control reg */
        sptm_sysreg_write(3, 5, 0xf, 0xb, 1, 0);
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        sptm_sysreg_write(3, 5, 0xf, 5, 7, status & ~1ULL);   /* clear bit0 = disable */
        sptm_cputrace_release_guard();
        return;
    }
    /* a window is still active: cannot deinit */
    sptm_panic(0x8000009, arg2,
        "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bcea0  sptm_cputrace_va_init
 * Ghidra: void FUN_000bcea0(undefined8, undefined8)
 * Powers up the CPU trace unit for the current CPU cluster: clears both VA
 * window bases, sets the control register to 0xff (all windows enabled),
 * sets status to 4, waits for the programmed bit (bit 36), then sets status
 * to 3 (start). Only valid when neither window is active. Confidence: high.
 * Notes: 1 ms poll timeout via CNTPCT/CNTFRQ, WFE-backed. */
void
sptm_cputrace_va_init(uint64_t arg1, uint64_t arg2)
{
    uint64_t percpu, mpidr, status, start, frq, now;
    uint8_t *cpu_entry;

    if (SPTM_CPUTRACE_STATE->active == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != 0) {
        sptm_panic(0x8000008, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    SPTM_CPUTRACE_STATE->state_guard = sptm_cputrace_guard_value(percpu);

    mpidr = read_mpidr_el1();
    if ((mpidr & 0xfe00) != 0) {
        sptm_panic_assert("cluster_id < MAX_CPUS");
    }
    cpu_entry = (uint8_t *)SPTM_CPUTRACE_STATE + ((mpidr >> 8) & 1) * 4;

    if (((cpu_entry[0x29] & 1) == 0) && ((cpu_entry[0x2b] & 1) == 0)) {
        /* neither VA window active: safe to power up */
        sptm_sysreg_write(3, 5, 0xf, 3, 6, 0);
        sptm_sysreg_write(3, 5, 0xf, 3, 7, 0);
        sptm_sysreg_write(3, 5, 0xf, 4, 7, 0xff);            /* enable all windows */
        sptm_sysreg_write(3, 5, 0xf, 5, 7, 4);               /* set bit2 */
        __asm__ volatile("dsb sy" ::: "memory");
        start = read_cntpct();
        frq   = read_cntfrq_el0();
        status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        while (((status >> 0x24) & 1) == 0) {                /* wait programmed bit 36 */
            __asm__ volatile("dsb sy" ::: "memory");
            now = read_cntpct();
            if ((frq & 0xfffffff8) / 1000 + start <= now) {
                sptm_panic_assert("CPUTrace condition: cputrace failed to program");
            }
            __asm__ volatile("wfe");
            status = sptm_sysreg_read(3, 5, 0xf, 5, 7);
        }
        sptm_sysreg_write(3, 5, 0xf, 5, 7, 3);               /* bits 0|1 = start */
        sptm_cputrace_release_guard();
        return;
    }
    /* a window is still active: cannot init */
    sptm_panic(0x8000009, arg2,
        "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bd57c  sptm_cputrace_va_frame_lock
 * Ghidra: void FUN_000bd57c(char, undefined8)
 * Locks a trace frame (the 16 KiB page at the validated request base) into
 * the VA trace frame window, growing the window by one frame so that it
 * always ends exactly at frame_base + 0x4000. Validates the request region,
 * takes the region guard and an rw-guard on the frame, and detects TOCTOU
 * region changes between two lookups. Confidence: medium.
 * Notes: window is empty (start==size==0) => window becomes [base, base+16K];
 *   otherwise the window end must equal base. */
void
sptm_cputrace_va_frame_lock(int reject, uint64_t trace_request)
{
    struct sptm_region_desc desc;
    struct sptm_guard_pair gp;
    uint16_t *guard;
    uint64_t base, start, size, new_start, new_size, handle1, handle2;
    uint64_t percpu;

    if (reject != 0) {
        sptm_panic(0x8000003, trace_request, "%s(%s:%d)");
    }
    desc = sptm_validate_trace_request(trace_request);
    base = desc.base;

    if (SPTM_CPUTRACE_STATE->active == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != 0) {
        sptm_panic(0x8000008, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    SPTM_CPUTRACE_STATE->state_guard = sptm_cputrace_guard_value(percpu);

    if (*sptm_cputrace_refcnt(0) != 0) {
        /* region already locked by another frame */
        sptm_panic(0x8000009, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
    }

    handle1 = sptm_region_handle(base);
    gp = sptm_guard_get(0);
    guard = (uint16_t *)gp.guard;
    if ((char)guard[1] != '%') {
        sptm_panic(0x8000006, gp.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    sptm_guard_op(guard, 0);                     /* acquire */
    if (RES_TYPE(guard[1], 1) != 6) {            /* guard type 6 = always-exclusive */
        if ((RES_TYPE(guard[1], 0x33) & 1) == 0) {
            guard[0] = 0;
            guard[1] = 0;
        } else {
            uint16_t old = guard[0];
            guard[0] = (uint16_t)(old - 2);
            sptm_lo_release();
            if (old == 0 || (old & 1) != 0) {
                sptm_panic_assert("rw_guard_release_shared failed");
            }
        }
    }

    handle2 = sptm_region_handle(base);
    if (handle1 != handle2) {
        /* region changed between the two lookups (TOCTOU) */
        sptm_panic(0x8000007, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }

    start = SPTM_CPUTRACE_STATE->region_start;
    size  = SPTM_CPUTRACE_STATE->region_size;
    if ((start == 0) == (size != 0)) {
        sptm_panic_assert("region_start/size consistency failed");
    }
    if ((start & 0x3fff) != 0) {
        sptm_panic_assert("region_start not SPTM_PAGE aligned");
    }
    if ((size & 0x3fff) == 0) {
        if (start == 0) {
            /* empty window: seed it around the requested frame */
            new_start = base;
            new_size  = 0x4000;
        } else {
            if (start + size < start) {
                sptm_panic_assert("__builtin_add_overflow failed");
            }
            if (start + size != base) {
                /* frame must be adjacent to the current window end */
                sptm_panic(0x8000004, desc.other,
                    "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
            }
            new_size = size + 0x4000;
            if (size > 0xffffffffffffbfff) {
                sptm_panic_assert("__builtin_add_overflow failed");
            }
        }
        if ((new_start & 0x3fff) != 0) {
            sptm_panic_assert("region_start not SPTM_PAGE aligned");
        }
        if ((new_size & 0x3fff) == 0) {
            if (new_start + new_size < new_start) {
                sptm_panic_assert("__builtin_add_overflow failed");
            }
            SPTM_CPUTRACE_STATE->region_start = new_start;
            SPTM_CPUTRACE_STATE->region_size  = new_size;
            sptm_cputrace_release_guard();
            return;
        }
    }
    sptm_panic_assert("region_size not SPTM_PAGE aligned");
}

/* ----------------------------------------------------------------------------
 * FUN_000bd120  sptm_cputrace_va_frame_unlock
 * Ghidra: void FUN_000bd120(char, undefined8)
 * Removes the most-recently locked trace frame from the VA trace frame
 * window, shrinking it by one frame (16 KiB). The window must currently end
 * exactly at frame_base + 0x4000. Releases the frame region and its
 * rw-guard. Confidence: medium. */
void
sptm_cputrace_va_frame_unlock(int reject, uint64_t trace_request)
{
    struct sptm_region_desc desc;
    struct sptm_guard_pair gp;
    uint16_t *guard;
    uint64_t start, size, new_start, new_size, percpu;

    if (reject != 0) {
        sptm_panic(0x8000003, trace_request, "%s(%s:%d)");
    }
    desc = sptm_validate_trace_request(trace_request);

    if (SPTM_CPUTRACE_STATE->active == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    percpu = sptm_per_cpu_state();
    if (SPTM_CPUTRACE_STATE->state_guard != 0) {
        sptm_panic(0x8000008, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    SPTM_CPUTRACE_STATE->state_guard = sptm_cputrace_guard_value(percpu);

    if (*sptm_cputrace_refcnt(0) != 0) {
        sptm_panic(0x8000009, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
    }

    start = SPTM_CPUTRACE_STATE->region_start;
    size  = SPTM_CPUTRACE_STATE->region_size;
    if ((start != 0) == (size == 0)) {
        sptm_panic_assert("region_start/size consistency failed");
    }
    if ((start & 0x3fff) != 0) {
        sptm_panic_assert("region_start not SPTM_PAGE aligned");
    }
    if ((size & 0x3fff) != 0) {
        sptm_panic_assert("region_size not SPTM_PAGE aligned");
    }
    if (size == 0) {
        /* nothing to unlock */
        sptm_panic(0x8000004, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    if (start + size < start) {
        sptm_panic_assert("__builtin_add_overflow failed");
    }
    if (start + size != desc.base + 0x4000) {
        /* window end must match the frame end exactly */
        sptm_panic(0x8000004, desc.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    if ((size >> 0xe) == 0) {
        sptm_panic_assert("region_size > SPTM_PAGE_SIZE");
    }
    new_size = size - 0x4000;
    new_start = (new_size != 0) ? start : 0;   /* collapse to empty when last frame */
    if (new_start + new_size < new_start) {
        sptm_panic_assert("__builtin_add_overflow failed");
    }
    SPTM_CPUTRACE_STATE->region_start = new_start;
    SPTM_CPUTRACE_STATE->region_size  = new_size;

    sptm_region_handle(desc.base);             /* release the frame region */

    gp = sptm_guard_get(0);
    guard = (uint16_t *)gp.guard;
    if ((char)guard[1] != '%') {
        sptm_panic(0x8000006, gp.other,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    sptm_guard_op(guard, 1);                   /* release */
    if (RES_TYPE(guard[1], 1) != 6) {
        if ((RES_TYPE(guard[1], 0x33) & 1) == 0) {
            guard[0] = 0;
            guard[1] = 0;
        } else {
            uint16_t old = guard[0];
            guard[0] = (uint16_t)(old - 2);
            sptm_lo_release();
            if (old == 0 || (old & 1) != 0) {
                sptm_panic_assert("rw_guard_release_shared failed");
            }
        }
    }

    sptm_cputrace_release_guard();
}

/* ----------------------------------------------------------------------------
 * FUN_000bda44  sptm_cputrace_stop
 * Ghidra: void FUN_000bda44(void)
 * NOTE: In this build the global (non-VA) cputrace stop endpoint is an
 * unconditional panic — SPTM does not implement a global stop; the VA/PA
 * window programming functions are used instead. Confidence: high. */
void
sptm_cputrace_stop(void)
{
    sptm_cputrace_state_code();
    sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bdab4  sptm_cputrace_start
 * Ghidra: void FUN_000bdab4(void)
 * NOTE: Same as sptm_cputrace_stop — the global cputrace start endpoint
 * unconditionally panics in this build. Confidence: high. */
void
sptm_cputrace_start(void)
{
    sptm_cputrace_state_code();
    sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000bdb04  sptm_cputrace_set_base
 * Ghidra: void FUN_000bdb04(ulong, ulong, byte)
 * Programs the physical-address trace window into one of the two per-window
 * comparator registers (s3_5_c15_c3_6 / c3_7). Unlike the VA variant, this
 * programs a physical address window that must lie within the trace
 * carve-out (+0x18/+0x20). Packs value = (size << 24) | (base >> 7) |
 * 0x8000000000000000. base must be 128-byte aligned, size 128 KiB aligned.
 * Confidence: high. Notes: requires cputrace available (mode 0), not merely
 * active. */
void
sptm_cputrace_set_base(uint64_t pa_base, uint64_t size, uint8_t index)
{
    uint64_t value, start, end;

    if (SPTM_CPUTRACE_STATE->available == 0) {
        sptm_cputrace_state_code();
        sptm_panic(0x8000000, 0, "%s(%s:%d) - %s(%#llx)\n");
    }
    if (index > 1) {
        sptm_panic(0x8000001, size, "%s(%s:%d)");
    }
    start = SPTM_CPUTRACE_STATE->carveout_start;
    if (start == 0) {
        sptm_panic_assert("carveout_start_paddr not set");
    }
    end = SPTM_CPUTRACE_STATE->carveout_size;
    if (end != 0) {
        if (start + end < start) {
            sptm_panic_assert("__builtin_add_overflow failed");
        }
        if (pa_base == 0 && size == 0) {
            value = 0;      /* disable the PA window */
        } else {
            if (pa_base == 0 || size == 0 || (pa_base + size < pa_base) ||
                (pa_base & 0x7f) != 0 || (size & 0x1ffff) != 0 ||
                pa_base < start || (start + end) < (pa_base + size)) {
                /* misaligned, overflowed, or outside the carve-out */
                sptm_panic(0x8000002, size, "%s(%s:%d)");
            }
            if ((size >> 0x11) == 0) {
                sptm_panic_assert("nb_units failed");
            }
            if (((size & 0xffffffffff) >> 0x27) != 0) {
                sptm_panic_assert("size_limit >> PROD_TRACE");
            }
            if ((pa_base >> 0x2a) != 0) {
                sptm_panic_assert("paddr >> PROD_TRACE_CARVEOUT");
            }
            value = (size << 0x18) | (pa_base >> 7) | 0x8000000000000000ULL;
        }
        sptm_sysreg_write(3, 5, 0xf, 5, 7, 0);          /* halt trace before reprogramming */
        if (index == 0) {
            sptm_sysreg_write(3, 5, 0xf, 3, 6, value);
        } else {
            sptm_sysreg_write(3, 5, 0xf, 3, 7, value);
        }
        return;
    }
    sptm_panic_assert("carveout_size not set");
}

/* ----------------------------------------------------------------------------
 * FUN_000bdd48  validate_sptm_cputrace_mode
 * Ghidra: bool FUN_000bdd48(byte, undefined8)
 * Returns whether the requested cputrace mode is available:
 *   mode 0 -> trace available flag (+0x10)
 *   mode 1 -> trace active flag (+0x11)
 *   modes 2/3 -> false. Panics (0x8000000) if mode > 3. Confidence: high. */
int
validate_sptm_cputrace_mode(uint8_t mode, uint64_t arg)
{
    if (mode > 3) {
        sptm_panic(0x8000000, arg, "%s(%s:%d)");
    }
    if (mode == 1) {
        return SPTM_CPUTRACE_STATE->active != 0;
    }
    if (mode == 0) {
        return SPTM_CPUTRACE_STATE->available != 0;
    }
    return 0;
}

/* ============================================================================
 * Hibernation integrity (SPTM_HIB_DOMAIN)
 * ==========================================================================*/

/* Hibernation state machine (DAT_001040a8). */
enum {
    HIB_STATE_IDLE          = 0,
    HIB_STATE_BUSY          = 1,   /* guard held / operation in progress */
    HIB_STATE_HIBSEG        = 2,   /* hashing hibseg pages */
    HIB_STATE_NONWIRED      = 3,   /* hashing non-wired pages (pre non-wired finalize) */
    HIB_STATE_NONWIRED2     = 4,   /* hashing non-wired pages (post non-wired finalize) */
    HIB_STATE_FINALIZE_SK   = 5,   /* finalizing SK hash segment */
    HIB_STATE_FINALIZE_IMG  = 6,   /* finalizing image hash */
    HIB_STATE_IMAGE_DONE    = 7,   /* image finalized */
    HIB_STATE_VERIFY        = 8,   /* verifying non-wired hash */
};

/* SHA phase (DAT_001040a9). */
enum {
    SHA_PHASE_IDLE      = 0,
    SHA_PHASE_INIT      = 1,   /* after hib_begin init */
    SHA_PHASE_HIBSEG    = 2,   /* hibseg hash finalized */
    SHA_PHASE_NONWIRED  = 3,   /* hashing non-wired pages */
    SHA_PHASE_IMAGE     = 4,   /* image hash being finalized */
    SHA_PHASE_VERIFY    = 5,   /* verifying */
};

/* SHA-2 hash object (DAT_00104120) and its method table. */
typedef struct sptm_sha_obj {
    uint64_t len_bytes;          /* +0x08 context working length */
    uint8_t  pad0[0x28 - 0x10];
    uint64_t iv_ptr;             /* +0x28 */
    void (*finalize)(struct sptm_sha_obj *, void *ctx, void *out);  /* +0x38 */
} sptm_sha_obj_t;

/* Reset a SHA context. FUN_000ae8b4 */
void sptm_sha_reset(sptm_sha_obj_t *obj, void *ctx);
/* Absorb `len` bytes into the SHA context. FUN_000aeaa4 */
void sptm_sha_update(sptm_sha_obj_t *obj, void *ctx, uint64_t len, const void *data);
/* Crypto-engine (ACE) finalize producing the image digest. FUN_000bf874 */
void sptm_ace_finalize(uint64_t ace_ctx, const void *digest_in, void *out);

/* Hibernation globals (see manifest notes for addresses). */
extern uint8_t  sptm_hib_enabled;       /* DAT_00100e00 bit0 */
extern uint8_t  g_hib_state;            /* DAT_001040a8 */
extern uint8_t  g_sha_phase;            /* DAT_001040a9 */
extern sptm_sha_obj_t *g_sha_obj;       /* DAT_00104120 (ptr) */
extern uint8_t  g_sha_ctx[];            /* DAT_001040b0 */
extern uint64_t g_ace_ctx;              /* DAT_00104130 */
extern uint64_t g_hibseg_idx;           /* DAT_00104138 current hibseg segment index */
extern uint32_t g_hibseg_off;           /* DAT_00104140 current page index within segment */
extern uint32_t g_hibseg_cpu;           /* DAT_00100cb0 current callback cpu */
extern uint8_t  g_sk_hib_started;       /* DAT_00104128 */
extern uint16_t g_sk_hib_percpu;        /* DAT_0010412a */

extern uint64_t g_n_hibseg;             /* DAT_00094968 number of hibseg segments */
extern uint8_t  g_scratch_page[];       /* DAT_00094948 scratch/digest buffer */
extern uint64_t g_sk_scratch;           /* DAT_00094958 */
extern uint32_t g_reloc_hash_count;     /* DAT_00094970 relocation/hash-tracking count */
extern uint8_t  g_ftetype_class;        /* DAT_00096381 FTE type-table class (fixed type-11 entry) */
extern uint8_t  g_ftetype_flags;        /* DAT_000963b3 FTE type-table flags (bit0) */

extern uint64_t g_dram_start;           /* DAT_00095d18 */
extern uint64_t g_dram_end;             /* DAT_00095d20 */
extern uint64_t g_immutable_start;      /* DAT_00094990 */
extern uint64_t g_immutable_end;        /* DAT_00094998 */
extern uint64_t g_immutable_hi1;        /* DAT_000949a0 */
extern uint64_t g_immutable_hi2;        /* DAT_000949a8 */
extern uint64_t g_dram_lo;              /* DAT_00095d28 */
extern uint64_t g_dram_hi;              /* DAT_00095d30 */
extern uint64_t g_linear_offset;        /* DAT_00095110 */
extern uint64_t g_feature_flags;        /* DAT_001012d8 */

extern uint32_t g_reloc_count;          /* DAT_00101ac8 */
/* large-memory VA->PA relocation entries, stride 3*8: {va, pa, count} */
extern const uint64_t g_reloc_table[];  /* DAT_00101ad0 */
/* relocation/hash-tracking entries, stride 4*4: {index, count, last_hashed, flags} */
extern uint32_t g_hash_track[];         /* DAT_00100730 */

/* hibseg page descriptor array, stride 16: {pad, start_page, page_count, flags} */
typedef struct sptm_hibseg_desc {
    uint32_t pad;
    uint32_t start_page;
    uint32_t page_count;
    uint32_t flags;
} sptm_hibseg_desc_t;
extern sptm_hibseg_desc_t g_hibseg_desc[];   /* DAT_00100e08 */

/* Page metadata (PTE descriptor) base table. DAT_00095460 */
extern const uint8_t g_page_desc[];      /* stride 0x10 */

/* Internal helpers for the hib state machine. */
void     sptm_hib_setup(uint64_t paddr, uint64_t len, uint32_t cpu, uint64_t flags);  /* FUN_000d617c */
void     sptm_hib_register_callback(uint64_t ctx, uint32_t cpu, uint64_t len, void *fn);  /* FUN_000ad3b0 */
void     sptm_hib_begin_callback_tail(void *out, uint64_t ctx, uint64_t len, uint64_t page); /* FUN_000ae158 */
uint64_t sptm_sk_hib_start(void);          /* FUN_000b25c0 */
uint64_t sptm_sk_hib_finish(void);         /* FUN_000b25f0 */
uint64_t sptm_sk_hib_encrypt(uint64_t paddr);  /* FUN_000b25d8 */
void     sptm_copy_mem(void *dst, const void *src, uint64_t len);  /* thunk_FUN_000abeb0 (page/scratch copy) */
void     sptm_scratch_zero(void *dst, uint64_t len);               /* thunk_FUN_000abb60 */
void     sptm_stack_check(void);           /* FUN_000ae44c */
uint64_t sptm_large_mem_translate(uint64_t paddr);  /* FUN_000e40ec */
uintptr_t sptm_external_desc_lookup(uint64_t paddr);  /* FUN_000e3d7c, returns desc or 0 */

/* ----------------------------------------------------------------------------
 * FUN_000bc75c  sptm_cputrace_state_code
 * Ghidra: undefined1 FUN_000bc75c(void)
 * Returns the current cputrace state code used as the panic arg when a trace
 * operation is requested while tracing is not available/active:
 *   active? (available? 3 : 2) : (available? 1 : 0). Confidence: high. */
uint8_t
sptm_cputrace_state_code(void)
{
    uint8_t avail = SPTM_CPUTRACE_STATE->available != 0;
    uint8_t active = SPTM_CPUTRACE_STATE->active != 0;

    if (active) {
        return avail ? 3 : 2;
    }
    return avail ? 1 : 0;
}

/* ----------------------------------------------------------------------------
 * FUN_000c02bc  sptm_hib_hash_page_internal
 * Ghidra: undefined8 FUN_000c02bc(ulong paddr, int include_index)
 * Core hibernation page-hash engine shared by the hibseg, non-wired and
 * verify paths. Resolves the 16 KiB page at `paddr` to its metadata
 * descriptor, classifies it (zero page, SK-owned, MTE-tag, normal),
 * materializes the page content into the scratch buffer (zeroing for zero
 * pages, SK_HIB_encrypt for SK-owned pages, direct copy for
 * remapped/encrypted relocation entries), and feeds the optional 4-byte page
 * index plus the 16 KiB page into the SHA context. Tracks in-flight hashed
 * pages to reject double-hashing. Returns 1 if the page was hashed from the
 * SK-encrypted scratch, else 0. Confidence: medium.
 * Notes: this is the hibernation integrity gate's per-page operation; it
 *   selects content to hash and asserts single-hashing. */
uint64_t
sptm_hib_hash_page_internal(uint64_t paddr, int include_index)
{
    const uint8_t *desc;
    uint8_t type;
    uint64_t src, page_idx, count;
    int zero_page, sk_path;
    uint64_t ret = 0;

    /* resolve the page descriptor (in-DRAM via the PTE table, else external) */
    if (paddr < g_dram_start || g_dram_end <= paddr) {
        uintptr_t d = sptm_external_desc_lookup(paddr);
        desc = (d != 0) ? (const uint8_t *)d : (const uint8_t *)0x00101f90;
    } else {
        desc = (const uint8_t *)sptm_pac_resign(
            (uintptr_t)g_page_desc + (((paddr - g_dram_start) >> 10) & 0xffffffff0));
    }

    type = desc[1];
    zero_page = 0;
    sk_path = 0;

    if (RES_TYPE(type, 6) == 0xff) {
        /* uninitialized/unknown page type */
        if (RES_TYPE(type, 0) == 3) {
            /* SK-owned memory */
            if (g_sha_phase != SHA_PHASE_HIBSEG) {
                sptm_panic_assert("Found SK owned memory in non-SK-hash phase");
            }
            if (((g_feature_flags >> 12) & 1) != 0) {
                if (sptm_sk_hib_encrypt(paddr) != 0) {
                    sptm_panic_assert("SK_HIB_encrypt(0x%llu) returned error");
                }
                zero_page = 0;
                ret = 1;
                src = g_sk_scratch;
                goto hash_common;
            }
        }
        /* zero page path */
        zero_page = 1;
        sptm_scratch_zero(g_scratch_page, 0x4000);   /* FUN_000e03f4 + zero fill */
        src = (uint64_t)g_scratch_page;
        sk_path = 1;
    } else {
        if (RES_TYPE(type, 0) == 3) {
            if (g_sha_phase != SHA_PHASE_HIBSEG) {
                sptm_panic_assert("Found SK owned memory in non-SK-hash phase");
            }
        } else {
            if (type == 0) {
                zero_page = 1;
                sptm_scratch_zero(g_scratch_page, 0x4000);
                src = (uint64_t)g_scratch_page;
                sk_path = 1;
                goto hash_common;
            }
            if (RES_TYPE(type, 1) == 4 && *(const uint32_t *)(desc + 4) != 0) {
                sptm_panic_assert("MTE tag page containing SK-tagged memory");
            }
        }
        /* translate the page to its physical backing */
        if (((g_feature_flags >> 8) & 1) == 0) {
            src = (paddr - g_dram_start) + g_linear_offset;
        } else {
            /* large-memory: walk the relocation table */
            uint64_t n = g_reloc_count;
            if (n != 0) {
                const uint64_t *e = g_reloc_table;
                do {
                    uint64_t va = e[0];
                    if (va <= paddr && paddr < va + (uint64_t)(uint32_t)e[2] * 0x4000) {
                        src = (paddr - va) + e[1];
                        goto hash_common;
                    }
                    e += 3;
                    n--;
                } while (n != 0);
            }
            src = sptm_large_mem_translate(paddr);
        }
    }

hash_common:
    page_idx = paddr >> 0xe;
    if (src == (uint64_t)g_scratch_page) {
        sptm_scratch_zero(g_scratch_page, 0x4000);
    } else {
        /* copy the page into the scratch buffer (or direct for remapped
         * encrypted relocation entries) */
        uint32_t n = g_reloc_hash_count;
        const uint32_t *e = g_hash_track;
        int did_copy = 0;
        while (n != 0) {
            uint32_t start = e[0];
            if (page_idx < start || (start + e[1]) - 1 < page_idx) {
                goto next_entry;
            }
            if (((e[3] >> 2) & 1) != 0) {
                /* remapped/encrypted: direct copy */
                memcpy(g_scratch_page, (void *)src, 0x4000);
                did_copy = 1;
                break;
            }
next_entry:
            e += 4;
            n--;
        }
        if (!did_copy) {
            sptm_copy_mem(g_scratch_page, (const void *)src, 0x4000);
        }
    }

    if (include_index != 0) {
        uint32_t idx32 = (uint32_t)page_idx;
        sptm_sha_update(g_sha_obj, g_sha_ctx, 4, &idx32);
    }
    sptm_sha_update(g_sha_obj, g_sha_ctx, 0x4000, g_scratch_page);

    if (sk_path) {
        sptm_scratch_zero(g_scratch_page, 0x4000);   /* FUN_000e05bc: release zero page */
    }

    /* track hashed pages to reject double-hashing */
    if (g_sha_phase - 1 < 2) {   /* SHA_PHASE_HIBSEG or NONWIRED */
        if (paddr < g_dram_start || g_dram_end <= paddr) {
            uint32_t n = g_reloc_hash_count;
            uint32_t *e = g_hash_track;
            while (n != 0) {
                if (e[0] <= page_idx && page_idx <= (e[0] + e[1]) - 1) {
                    if (e[2] != page_idx) {
                        return ret;
                    }
                    e[2] = (uint32_t)page_idx + 1;
                    return ret;
                }
                e += 4;
                n--;
            }
        } else {
            uintptr_t d = sptm_pac_resign(
                (uintptr_t)g_page_desc + (((paddr - g_dram_start) >> 10) & 0xffffffff0));
            uint8_t *flags = (uint8_t *)(d + 3);
            if ((RES_TYPE(((const uint8_t *)d)[2], 2) & 1) != 0) {
                uint8_t old = *flags;
                *flags = (uint8_t)(old | 1);
                if ((old & 1) != 0) {
                    /* page already hashed */
                    sptm_panic(0x5a, (uint64_t)old, "%s(%s:%d) - %s(%#llx)\n");
                }
            }
        }
    }
    return ret;
}

/* ----------------------------------------------------------------------------
 * FUN_000bf9dc  sptm_hib_begin
 * Ghidra: void FUN_000bf9dc(ulong, ulong)
 * Begins hibernation hashing. Validates the global enable flag, interrupt
 * masking, the DRAM scrub page paddr (16 KiB aligned, in DRAM) and the
 * scratch/callback count, registers the per-CPU callback, clears the
 * hashed-bit on every DRAM page, compacts the relocation hash-tracking
 * array, then initializes the SHA context with the domain salt
 * "GESH1GAP2GAPFFUB" + the hibseg descriptor array. If any hibseg segments
 * exist, transitions to HIB_STATE_HIBSEG (2); else panics. Confidence:
 * high. Notes: first 4 bytes hashed are the ASCII salt at 0x12f60; the 0xa0
 * bytes of hibseg descriptors follow; the callback cpu = param_2&0xffffffff
 * must be in [0x21, 0x20]-range else panic 10. */
void
sptm_hib_begin(uint64_t scrub_paddr, uint64_t cpu_arg)
{
    uint64_t percpu, ctx, i, count, n;
    uint32_t cpu;

    if ((sptm_hib_enabled & 1) == 0) {
        /* irq state check is in the caller; panic code 0x57 */
        sptm_panic(0x57, cpu_arg,
            "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
    }
    if (g_hib_state != HIB_STATE_IDLE) {
        sptm_panic(0x58, cpu_arg,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if ((scrub_paddr & 0x3fff) != 0 || scrub_paddr < g_dram_start || g_dram_end <= scrub_paddr) {
        sptm_panic(6, cpu_arg,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    if ((int)cpu_arg - 0x21U < 0xffffffe0) {
        sptm_panic(10, cpu_arg,
            "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
    }
    cpu = (uint32_t)cpu_arg;
    g_hibseg_cpu = cpu;

    sptm_hib_setup(scrub_paddr, 8, cpu, 0);

    percpu = sptm_per_cpu_state();
    ctx = *(uint64_t *)(0x1595 + percpu + 0x1b);   /* per-cpu hib callback context */
    sptm_hib_register_callback(ctx, cpu, 8, (void *)0x000bf9c0);

    /* increment refcount on each callback resource */
    count = g_hibseg_cpu;
    if (count != 0) {
        for (i = 0; i < count; i++) {
            struct sptm_guard_pair gp =
                sptm_guard_get(*(uint64_t *)(ctx + i * 8));
            uint16_t *guard = (uint16_t *)gp.guard;
            if ((char)guard[1] != '\v') {
                sptm_panic(0x59, gp.other,
                    "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
            }
            if (g_ftetype_class != 3) {
                sptm_panic_assert("Type %d class of FTE is %d");
            }
            uint32_t rc = *(uint32_t *)(guard + 6);   /* refcount at guard+6 */
            *(uint32_t *)(guard + 6) = rc + 1;
            if (rc > 0xfffffff4) {
                sptm_panic_assert("refcnt_overflow: rc=%d old value");
            }
            if (g_ftetype_class != 6) {
                if ((g_ftetype_flags & 1) == 0) {
                    guard[0] = 0;
                    guard[1] = 0;
                } else {
                    uint16_t old = guard[0];
                    guard[0] = (uint16_t)(old - 2);
                    sptm_lo_release();
                    if (old == 0 || (old & 1) != 0) {
                        sptm_panic_assert("rw_guard_release_shared failed");
                    }
                }
            }
        }
    }
    sptm_hib_begin_callback_tail(&g_hibseg_cpu, ctx, (uint64_t)g_hibseg_cpu << 3, 0x100);

    /* clear the hashed-bit on every in-DRAM page */
    if (((g_dram_end - g_dram_start) & 0x3fffffffc000) != 0) {
        n = ((g_dram_end - g_dram_start) >> 0xe) & 0xffffffff;
        for (uint64_t off = 0; n != 0; off += 0x10, n--) {
            const uint8_t *d = g_page_desc + off;
            if ((RES_TYPE(d[2], 2) & 1) != 0) {
                ((uint8_t *)d)[3] &= 0xfe;   /* clear hashed bit */
            }
        }
    }

    /* compact the relocation hash-tracking array (drop paired entries) */
    if (g_reloc_hash_count != 0) {
        uint32_t n4 = g_reloc_hash_count & 0xfffffffffffffffc;
        uint32_t *dst = (uint32_t *)((uint8_t *)g_hash_track + 0x20);
        uint32_t k = n4;
        while (k != 0) {
            dst[-6] = dst[-8];
            dst[-2] = dst[-4];
            dst[2]  = dst[0];
            dst[6]  = dst[4];
            dst += 0x10;
            k -= 4;
        }
        if (g_reloc_hash_count != n4) {
            uint32_t left = g_reloc_hash_count - n4;
            uint32_t *e = (uint32_t *)((uint8_t *)g_hash_track + 8) + n4 * 4;
            while (left != 0) {
                *e = e[-2];
                left--;
                e += 4;
            }
        }
    }

    if (g_sha_phase != SHA_PHASE_IDLE) {
        sptm_panic_assert("Unexpected current SHA context");
    }
    sptm_sha_reset(g_sha_obj, g_sha_ctx);
    /* hash the first 4-byte domain salt chunk "GESH" (0x12f60) */
    sptm_sha_update(g_sha_obj, g_sha_ctx, 4, (const void *)0x00012f60);
    g_sha_phase = SHA_PHASE_INIT;
    /* hash the hibseg descriptor array (0xa0 bytes = 10 segments) */
    sptm_sha_update(g_sha_obj, g_sha_ctx, 0xa0, g_hibseg_desc);

    if (g_n_hibseg != 0) {
        g_hibseg_idx = 0;
        g_hibseg_off = g_hibseg_desc[0].start_page;
        percpu = sptm_per_cpu_state();
        g_sk_hib_percpu = *(uint16_t *)(0x142e + percpu + 10);
        g_sk_hib_started = 1;
        if ((((g_feature_flags >> 12) & 1) != 0) && sptm_sk_hib_start() != 0) {
            sptm_panic_assert("SK_HIB_start returned error (0x%llu)");
        }
        if (g_hib_state != HIB_STATE_BUSY) {
            sptm_panic_assert("state guard release failed");
        }
        g_hib_state = HIB_STATE_HIBSEG;
        return;
    }
    sptm_panic_assert("Hibernation is supported but there's no hibernation segments.");
}

/* ----------------------------------------------------------------------------
 * FUN_000bffc8  sptm_hib_hash_hibseg_page
 * Ghidra: void FUN_000bffc8(undefined8, undefined8)
 * Hashes the next hibseg page. Walks the current hibseg segment descriptor,
 * bounds-checks the page index, verifies the page is in the DRAM hib range
 * (else "Found non DRAM hibernation segment"), hashes it (without index),
 * and advances the segment/page cursors. When all segments are consumed it
 * finalizes the hibseg digest, re-seeds the SHA context with the second salt
 * (0x12f64) and moves the SHA phase to HIBSEG(2) and hib state to
 * NONWIRED(3). Confidence: high. */
void
sptm_hib_hash_hibseg_page(uint64_t arg1, uint64_t arg2)
{
    uint64_t digest[4];
    sptm_hibseg_desc_t *seg;
    uint32_t start_page, last_page, page;
    uint64_t paddr;

    if (g_hib_state != HIB_STATE_HIBSEG) {
        sptm_panic(0x58, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (g_n_hibseg < g_hibseg_idx) {
        sptm_panic_assert("Invalid current hibseg index %zu");
    }
    if (g_hibseg_idx == g_n_hibseg) {
        /* all segments consumed: finalize the hibseg digest */
        digest[0] = 0; digest[1] = 0; digest[2] = 0; digest[3] = 0;
        g_sha_obj->finalize(g_sha_obj, g_sha_ctx, digest);
        sptm_ace_finalize(g_ace_ctx, digest, g_scratch_page);
        if (g_sha_phase != SHA_PHASE_INIT) {
            sptm_panic_assert("Unexpected current SHA context");
        }
        sptm_sha_reset(g_sha_obj, g_sha_ctx);
        /* re-seed with the second salt (0x12f64) */
        sptm_sha_update(g_sha_obj, g_sha_ctx, 4, (const void *)0x00012f64);
        g_sha_phase = SHA_PHASE_HIBSEG;
        if (g_hib_state == HIB_STATE_BUSY) {
            g_hib_state = HIB_STATE_NONWIRED;
        }
        sptm_stack_check();
        return;
    }

    seg = &g_hibseg_desc[g_hibseg_idx];
    start_page = seg->start_page;
    last_page = (start_page + seg->page_count) - 1;
    page = g_hibseg_off;
    if (page < start_page || last_page < page) {
        sptm_panic_assert("The current hibseg page is out of the bounds of the hibernation segment");
    }
    paddr = (uint64_t)page << 0xe;
    if (paddr < g_dram_lo || g_dram_hi <= paddr) {
        sptm_panic_assert("Found non DRAM hibernation segment");
    }
    sptm_hib_hash_page_internal(paddr, 0);

    if (page == last_page) {
        g_hibseg_idx++;
        if (g_hibseg_idx < g_n_hibseg) {
            g_hibseg_off = g_hibseg_desc[g_hibseg_idx].start_page;
        } else {
            g_hibseg_off = 0;
        }
    } else {
        g_hibseg_off = page + 1;
    }

    if (g_hib_state == HIB_STATE_BUSY) {
        g_hib_state = HIB_STATE_HIBSEG;
        sptm_stack_check();
        return;
    }
    sptm_panic_assert("state guard release failed");
}

/* ----------------------------------------------------------------------------
 * FUN_000c06ec  sptm_hib_hash_page
 * Ghidra: void FUN_000c06ec(ulong, undefined8)
 * Hashes a single non-wired 16 KiB page (with its page index) into the
 * hibernation image. The expected hib state is 3 while the SHA phase is
 * HIBSEG (hashing non-wired pages), or 4 otherwise. Rejects a zero or
 * misaligned paddr, and panics if the page is in the immutable range
 * [immutable_start, immutable_end). Confidence: high. */
void
sptm_hib_hash_page(uint64_t paddr, uint64_t arg2)
{
    uint8_t expected;

    expected = (g_sha_phase == SHA_PHASE_HIBSEG) ? HIB_STATE_NONWIRED : HIB_STATE_NONWIRED2;
    if (g_hib_state != expected) {
        sptm_panic(0x58, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (paddr == 0 || (paddr & 0x3fff) != 0) {
        sptm_panic(6, arg2, "%s(%s:%d) - %s(%#llx)\n");
    }
    if ((g_immutable_start <= paddr && paddr < g_immutable_end) &&
        paddr < g_immutable_hi1 && paddr < g_immutable_hi2) {
        sptm_panic_assert("attempting to hibernate immutable page %p");
    }
    sptm_hib_hash_page_internal(paddr, 1);

    if (g_hib_state == HIB_STATE_BUSY) {
        g_hib_state = expected;
        return;
    }
    sptm_panic_assert("state guard release failed");
}

/* ----------------------------------------------------------------------------
 * FUN_000c0cec  sptm_hib_finalize_sk
 * Ghidra: void FUN_000c0cec(undefined8, undefined8)
 * Finalizes the Secure-Kernel hash segment: invokes SK_HIB_finish, copies
 * the SK scratch out, then closes the current SHA context (a9: 3 -> 4) and
 * moves the hib state to FINALIZE_IMG(6). Requires SK hibernation enabled.
 * Confidence: high. */
void
sptm_hib_finalize_sk(uint64_t arg1, uint64_t arg2)
{
    uint64_t err;

    if (g_hib_state != HIB_STATE_FINALIZE_SK) {
        sptm_panic(0x58, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (((g_feature_flags >> 12) & 1) != 0) {
        err = sptm_sk_hib_finish();
        if (err != 0) {
            sptm_panic_assert("SK_HIB_finish returned error (0x%llu)");
        }
        sptm_copy_mem((void *)0x00100c30, (const void *)g_sk_scratch, 0x1c);
    }

    if (g_sha_phase != SHA_PHASE_NONWIRED) {
        sptm_panic_assert("Unexpected current SHA context");
    }
    sptm_sha_reset(g_sha_obj, g_sha_ctx);
    sptm_sha_update(g_sha_obj, g_sha_ctx, 4, (const void *)0x00012f6c);
    g_sha_phase = SHA_PHASE_IMAGE;

    if (g_hib_state != HIB_STATE_BUSY) {
        sptm_panic_assert("state guard release failed");
    }
    g_hib_state = HIB_STATE_FINALIZE_IMG;
}

/* ----------------------------------------------------------------------------
 * FUN_000c0e64  sptm_hib_finalize_image
 * Ghidra: void FUN_000c0e64(ulong, long)
 * Finalizes the full hibernation image: absorbs `len` bytes (the compressed
 * image) from the translated physical backing of `paddr` (via the linear
 * offset or the large-memory relocation table), computes the final SHA
 * digest via the hash object finalize + crypto engine, then stores the
 * digest at DAT_00094948. Requires SHA phase IMAGE(4); hib state
 * FINALIZE_IMG(6); paddr 16 KiB aligned in DRAM; len in [0x4001, ...].
 * Confidence: high. */
void
sptm_hib_finalize_image(uint64_t paddr, uint64_t len)
{
    uint64_t src, digest[4];

    if (g_hib_state != HIB_STATE_FINALIZE_IMG) {
        sptm_panic(0x58, len,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (g_sha_phase != SHA_PHASE_IMAGE) {
        sptm_panic_assert("Finalizing the image but the SHA context is wrong");
    }
    if ((paddr & 0x3fff) != 0 || paddr < g_dram_start || g_dram_end <= paddr) {
        sptm_panic(6, len,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    if (len - 0x4001U < 0xffffffffffffc000) {
        sptm_panic(0x12, len,
            "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
    }

    if (((g_feature_flags >> 8) & 1) == 0) {
        src = (paddr - g_dram_start) + g_linear_offset;
    } else {
        /* large-memory: walk the relocation table */
        uint64_t n = g_reloc_count;
        src = 0;
        if (n != 0) {
            const uint64_t *e = g_reloc_table;
            do {
                uint64_t va = e[0];
                if (va <= paddr && paddr < va + (uint64_t)(uint32_t)e[2] * 0x4000) {
                    src = (paddr - va) + e[1];
                    goto found;
                }
                e += 3;
                n--;
            } while (n != 0);
        }
        src = sptm_large_mem_translate(paddr);
    }
found:
    sptm_sha_update(g_sha_obj, g_sha_ctx, len, (void *)src);

    digest[0] = 0; digest[1] = 0; digest[2] = 0; digest[3] = 0;
    g_sha_obj->finalize(g_sha_obj, g_sha_ctx, digest);
    sptm_ace_finalize(g_ace_ctx, digest, g_scratch_page);

    if (g_hib_state != HIB_STATE_BUSY) {
        sptm_panic_assert("state guard release failed");
    }
    g_hib_state = HIB_STATE_IMAGE_DONE;
    sptm_stack_check();
}

/* ----------------------------------------------------------------------------
 * FUN_000c1128  sptm_hib_verify_hash_non_wired_page
 * Ghidra: void FUN_000c1128(ulong, undefined8)
 * Resume-time verification: hashes a single non-wired page (with its page
 * index) exactly as during hibernation and asserts single-hashing. Requires
 * hib state VERIFY(8) and SHA phase VERIFY(5). Confidence: high. */
void
sptm_hib_verify_hash_non_wired_page(uint64_t paddr, uint64_t arg2)
{
    if ((sptm_hib_enabled & 1) == 0) {
        sptm_panic(0x57, arg2, "%s(%s:%d)");
    }
    if (g_hib_state != HIB_STATE_VERIFY) {
        sptm_panic(0x58, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (g_sha_phase != SHA_PHASE_VERIFY) {
        sptm_panic_assert("Somehow we're in the verify path with the wrong SHA context");
    }
    if (paddr != 0 && (paddr & 0x3fff) == 0) {
        sptm_hib_hash_page_internal(paddr, 1);
        if (g_hib_state != HIB_STATE_BUSY) {
            sptm_panic_assert("state guard release failed");
        }
        g_hib_state = HIB_STATE_VERIFY;
        return;
    }
    sptm_panic(6, arg2, "%s(%s:%d) - %s(%#llx)\n");
}

/* ----------------------------------------------------------------------------
 * FUN_000c12a4  sptm_hib_verify_finalize_non_wired_hash
 * Ghidra: void FUN_000c12a4(undefined8, undefined8)
 * Finalizes the resume-time verification: computes the SHA digest of the
 * re-hashed non-wired pages and stores it at DAT_00094948. Requires hib
 * state VERIFY(8) and SHA phase VERIFY(5); returns the hib state to IDLE(0)
 * and the SHA phase to IDLE(0). This is the completion of the hibernation
 * integrity gate — the resulting digest is compared against the value
 * produced at hibernation time by the caller (kernel). Confidence: high. */
void
sptm_hib_verify_finalize_non_wired_hash(uint64_t arg1, uint64_t arg2)
{
    uint64_t digest[4];

    if ((sptm_hib_enabled & 1) == 0) {
        sptm_panic(0x57, arg2, "%s(%s:%d)");
    }
    if (g_hib_state != HIB_STATE_VERIFY) {
        sptm_panic(0x58, arg2,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
    }
    g_hib_state = HIB_STATE_BUSY;

    if (g_sha_phase != SHA_PHASE_VERIFY) {
        sptm_panic_assert("Somehow we're in the verify path with the wrong SHA context");
    }
    digest[0] = 0; digest[1] = 0; digest[2] = 0; digest[3] = 0;
    g_sha_obj->finalize(g_sha_obj, g_sha_ctx, digest);
    sptm_ace_finalize(g_ace_ctx, digest, g_scratch_page);
    g_sha_phase = SHA_PHASE_IDLE;

    if (g_hib_state != HIB_STATE_BUSY) {
        sptm_panic_assert("state guard release failed");
    }
    g_hib_state = HIB_STATE_IDLE;
    sptm_stack_check();
}

/* ----------------------------------------------------------------------------
 * FUN_000f84b4  hib_sptm_panic_func
 * Ghidra: void FUN_000f84b4(void)
 * The hibernation panic reporting function: always panics with the format
 * "%s: %s:%u: %s (%#llx/%s)" (0x3418) using the caller's source location
 * and the memory-region type name. Installed as the hib domain's panic
 * handler. Confidence: high. */
__attribute__((noreturn)) void
hib_sptm_panic_func(void)
{
    sptm_panic_assert("%s: %s:%u: %s (%#llx/%s)");
}
