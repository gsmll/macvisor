/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched. Slice 12: 0x277be4-0x27ffd8, vspace/MMU layer. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (shared runtime library outside
 * the 0x200000-0x280000 vspace slice; bodies owned by other range workers).
 * ------------------------------------------------------------------ */
extern uint64_t FUN_0008e518(void);          /* out of slice */
extern uint64_t FUN_00358a74(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00356900(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00349720(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00348f50(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0034d024(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00310e08(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00348cd0(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0007c1a4(void);          /* out of slice */
extern uint64_t FUN_0034b0c4(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00350920(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00310d80(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0036b270(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00349234(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00376820(uint64_t, uint64_t); /* out of slice (runtime lib) */
extern uint64_t FUN_0035a4ec(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00355ca4(uint64_t, void *);  /* out of slice (runtime lib) */
extern uint64_t FUN_001db6b0(void);          /* out of slice */
extern uint64_t FUN_0036b118(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00352840(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_001dc430(void);          /* out of slice */
extern uint64_t FUN_00352bb0(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00350618(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00351354(uint64_t);      /* out of slice (runtime lib) */
extern uint64_t FUN_00310e20(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_003505f4(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0034df34(uint64_t, uint64_t); /* out of slice (runtime lib) */
extern uint64_t FUN_00357af8(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0035060c(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_00352980(void);          /* out of slice (runtime lib) */
extern uint64_t FUN_0008e500(uint64_t, uint64_t, uint64_t); /* out of slice */

/* DAT_00658c00 : indirect call target (function pointer table). */
extern uint64_t (*DAT_00658c00)(uint64_t);   /* out of slice (global fnptr) */

/* ------------------------------------------------------------------ *
 * Slice 12 bodies (0x277be4-0x27ffd8).
 * ------------------------------------------------------------------ */

/* FUN_00277be4 @ 0x00277be4   (est. vspace_subsystem_setup)
 * Ghidra: void FUN_00277be4(void)
 * Top-level vspace/MMU subsystem initialisation. Sequences a long chain of
 * runtime-library setup calls (per-CPU state, timer/irq registration, address
 * space table install, cache/TLB helpers) and finishes with a canary check
 * against the saved stack guard, calling the panic path on mismatch. The
 * tail registers a variable-argument trampoline (FUN_00352980) and forwards
 * its register pair plus the incoming stack word into a shared entry helper.
 * Confidence: medium
 * Notes: huge call chain of out-of-range FUN_003xxxxx runtime helpers;
 *   stack canary read from unaff_x26+0x10; DAT_00658c00 indirect calls. */
void vspace_subsystem_setup(void)
{
    uint64_t a, b, lo, hi;

    FUN_0008e518();
    FUN_00358a74();
    FUN_00356900();
    FUN_00349720();
    (*DAT_00658c00)(*(uint64_t *)0x40);   /* indirect init call */
    FUN_00348f50();
    FUN_0034d024();
    FUN_00310e08();
    FUN_00348cd0();
    FUN_0007c1a4();
    (*DAT_00658c00)(0);
    FUN_0034b0c4();
    FUN_00350920();
    a = FUN_00310d80();
    FUN_0036b270();
    b = FUN_00349234();
    FUN_00376820(b, a);
    a = FUN_0035a4ec();
    FUN_00355ca4(a, 0);
    FUN_001db6b0();
    FUN_0036b118();
    if (/* local_8 */ 0 != /* saved canary */ 0) {
        FUN_00352840();
        FUN_001dc430();
        FUN_00352bb0();
        FUN_00350618();
        /* (*extraout_x9)(); */
        FUN_00351354(0);
        /* (*extraout_x8_00)(); */
        FUN_00310e20();
        a = FUN_003505f4();
        FUN_0034df34(a, 0);
        /* (*extraout_x8_01)(); */
        FUN_00357af8();
        FUN_0035060c();
        /* (*extraout_x8_02)(); */
    }
    lo = FUN_00352980();
    FUN_0008e500(lo, lo >> 32, 0);   /* register pair + stack word */
    return;
}

/* FUN_00277d80 @ 0x00277d80   (est. vspace_tlb_flush_guarded)
 * Ghidra: void FUN_00277d80(void)
 * Guarded TLB/address-space flush entry. Runs the per-CPU runtime init,
 * then checks a per-CPU readiness flag (FUN_001e3048) and returns early if
 * the current CPU is not yet up; otherwise re-inits and drives the flush
 * work through vspace_tlb_flush_work (FUN_00277de0). Returns void.
 * Confidence: medium
 * Notes: mirror-image guard to FUN_002782a4; FUN_001e3048 & 1 is a
 *   per-cpu "is this cpu initialised" probe. */
void vspace_tlb_flush_guarded(void)
{
    FUN_0034d1b0();          /* per-cpu runtime init */
    FUN_00310e08();
    if ((FUN_001e3048() & 1) != 0) {
        return;
    }
    FUN_0034d1b0();
    FUN_0031b71c();
    FUN_0035a7e8();
    vspace_tlb_flush_work();
    return;
}

