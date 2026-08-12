/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 * Region 06: 0x1e0000-0x1f0000. Scheduler/thread + Swift runtime glue. This sub-range is dominated
 * by Swift runtime helper code (fatal-error/range/collection checks and the "Fatal error" string
 * table at s_Fatal_error_005accd0) mixed with cL4 scheduler/dispatch entry points. Confidence is
 * medium unless a Swift module string matches (high). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Cross-range cL4 kernel helpers (declared extern with FUN_ address;
 * reconstructed by sibling SK range workers). Names are estimates.
 * ------------------------------------------------------------------ */
extern void sk_cpu_get(void);                            /* FUN_0008e518 */
extern void sk_obj_methods_table(void);                  /* FUN_00377824 / DAT_00658c00 obj-method table */
extern void sk_lock_ref(unsigned long);                  /* FUN_00377bec */
extern void sk_lock_release(void);                       /* FUN_00377dcc */
extern void sk_alloc(unsigned long, unsigned long);      /* FUN_0036a908 */
extern void sk_alloc_sized(unsigned long, unsigned long, unsigned long); /* FUN_0036a940 */
extern void sk_alloc_pages(unsigned long, unsigned long);/* FUN_0036b270 */
extern void sk_free(void *);                             /* FUN_0036b118 */
extern void sk_obj_method(uint64_t);                     /* FUN_00310e20 */
extern void sk_obj_method2(uint64_t);                    /* FUN_00310954 */
extern void sk_obj_method3(uint64_t);                    /* FUN_00310f04 */
extern void sk_fatal_error(void);                        /* FUN_001afe4c (Swift fatal, noreturn) */
extern void sk_fatal_swift(void);                        /* FUN_001afa84 (Swift precondition noreturn) */
extern void sk_sched_dispatch(void);                     /* FUN_0008412c */
extern void sk_sched_yield(void);                        /* FUN_001e638c (in-range) */
extern void sk_swift_fatal(void);                        /* FUN_00068e14 */

/* Out-of-range Swift runtime entry points referenced throughout this region. */
extern unsigned long sk_swift_strlen(unsigned long);              /* FUN_002a200c */
extern void sk_swift_hash_seed(unsigned long, unsigned long);     /* FUN_00002534 */
extern unsigned long sk_swift_bridge_objc(unsigned long, unsigned long); /* FUN_002110f8 */
extern void sk_swift_metadata_resolve(void);                      /* FUN_0001a1c8 */
extern void sk_objc_msgSend(void);                                /* FUN_003a25d4 */
extern void sk_swift_retain(void *);                              /* FUN_00012568 (thunk) */
extern void sk_swift_collection_insert(void);                     /* FUN_0026bdc4 */
extern void sk_swift_collection_append(void);                     /* FUN_001dffa0 */
extern void sk_memcpy(void *, const void *, unsigned long);       /* FUN_00117d14 */

/* ------------------------------------------------------------------ *
 * FUN_001e0414 @ 0x001e0414   (est. sk_sched_flag_check)
 * Ghidra: uint FUN_001e0414(void)
 * Enters the scheduler/obj lock, reads a flag word at (tcb+0x18), and returns whether a
 * guarded check succeeded. On success it runs two more obj-dispatch helpers and returns 1.
 * Confidence: medium (no string match).
 */
uint sk_sched_flag_check(void)
{
    /* FUN_00354708 / FUN_00352d70(obj+0x18) / FUN_0008412c / FUN_0034f014 / FUN_0035053c */
    sk_cpu_get();
    sk_lock_ref(*(uint64_t *)(/* extraout_x1 */0 + 0x18));
    sk_sched_dispatch();
    if ((/* r8 */0 & 1) == 0) {
        return 0;
    }
    sk_obj_method(0);       /* FUN_0034f014 */
    sk_obj_method(0);       /* FUN_0035053c */
    return 1;
}

/* ------------------------------------------------------------------ *
 * FUN_001e04a0 @ 0x001e04a0   (est. sk_obj_method_dispatch_2)
 * Ghidra: uint FUN_001e04a0(undefined8 param_1,long param_2)
 * Loads a vtable pair from (param_2+0x10)/(param_2+0x18), performs the first method on param_1,
 * and if that succeeds performs a second method selected from (param_2+0x24) with 4 args.
 * Confidence: medium.
 */
uint sk_obj_method_dispatch_2(uint64_t param_1, long param_2)
{
    uint64_t m1 = *(uint64_t *)(param_2 + 0x10);
    uint64_t m2 = *(uint64_t *)(param_2 + 0x18);
    if ((sk_obj_method2(m2)(param_1) & 1) == 0) {
        return 0;
    }
    int off = *(int *)(param_2 + 0x24);
    return sk_obj_method(m2)(param_1, /* x20 */0 + off, m1, m2) & 1;
}

/* ------------------------------------------------------------------ *
 * FUN_001e059c @ 0x001e059c   (est. sk_obj_method_dispatch_3)
 * Ghidra: uint FUN_001e059c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Locked obj-method dispatch: acquires lock, calls method on param_3, and if the guard passes
 * performs a second call. Returns boolean result of the final call.
 * Confidence: medium.
 */
uint sk_obj_method_dispatch_3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* FUN_0035316c / FUN_003514b8(p3) / FUN_00310e20 / FUN_0034bf1c */
    sk_lock_ref(0);
    sk_obj_method(0);
    if ((/* r8 */0 & 1) == 0) {
        return 0;
    }
    sk_obj_method(0);       /* FUN_00351378 */
    return 1;
}

/* ------------------------------------------------------------------ *
 * FUN_001e0648 / FUN_001e064c   (est. sk_sched_bind_timer_a) — alias pair
 * Ghidra: void FUN_001e0648(undefined8,undefined8)  /  FUN_001e064c same
 * Forwarders to FUN_001a2bec(param1,param2,FUN_00312b54).
 * Confidence: medium.
 */
void sk_sched_bind_timer_a(uint64_t a, uint64_t b) { /* FUN_001a2bec(a,b,FUN_00312b54) */ }
void sk_sched_bind_timer_a2(uint64_t a, uint64_t b) { /* FUN_001a2bec(a,b,FUN_00312b54) */ }

/* ------------------------------------------------------------------ *
 * FUN_001e0674 / FUN_001e0678   (est. sk_sched_bind_timer_b) — alias pair
 * Ghidra: void FUN_001e0674(undefined8,undefined8)  /  FUN_001e0678 same
 * Forwarders to FUN_001a2bec(param1,param2,FUN_00316518).
 * Confidence: medium.
 */
void sk_sched_bind_timer_b(uint64_t a, uint64_t b) { /* FUN_001a2bec(a,b,FUN_00316518) */ }
void sk_sched_bind_timer_b2(uint64_t a, uint64_t b) { /* FUN_001a2bec(a,b,FUN_00316518) */ }

/* ------------------------------------------------------------------ *
 * FUN_001e06b8 / FUN_001e06bc   (est. sk_sched_tick_forward) — alias pair
 * Ghidra: void FUN_001e06b8(void)  /  FUN_001e06bc same
 * Forwarders to FUN_001a3dc4 (scheduler tick).
 * Confidence: medium.
 */
void sk_sched_tick_forward(void) { /* FUN_001a3dc4() */ }
void sk_sched_tick_forward2(void) { /* FUN_001a3dc4() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e06e8   (est. sk_sched_deadline_check)
 * Ghidra: undefined8 FUN_001e06e8(void)
 * Wraps FUN_001a3728 then tails through objc msgSend with in_x3.
 * Confidence: medium.
 */
uint64_t sk_sched_deadline_check(void)
{
    uint64_t r = /* FUN_001a3728() */0;
    /* FUN_003a25d4(in_x3) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e071c   (est. sk_sched_window_check)
 * Ghidra: undefined8 FUN_001e071c(void)
 * Wraps FUN_001a3918 then tails through objc msgSend.
 * Confidence: medium.
 */
uint64_t sk_sched_window_check(void)
{
    uint64_t r = /* FUN_001a3918() */0;
    /* FUN_003a25d4(in_x3) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e0750   (est. sk_sched_budget_check)
 * Ghidra: undefined8 FUN_001e0750(void)
 * Wraps FUN_0001d648 then tails through objc msgSend.
 * Confidence: medium.
 */
uint64_t sk_sched_budget_check(void)
{
    uint64_t r = /* FUN_0001d648() */0;
    /* FUN_003a25d4(in_x3) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e0784   (est. sk_sched_capacity_check)
 * Ghidra: undefined8 FUN_001e0784(void)
 * Wraps FUN_001a3b90 then tails through objc msgSend.
 * Confidence: medium.
 */
uint64_t sk_sched_capacity_check(void)
{
    uint64_t r = /* FUN_001a3b90() */0;
    /* FUN_003a25d4(in_x3) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e07bc   (est. sk_sched_bind_check)
 * Ghidra: undefined8 FUN_001e07bc(undefined8,undefined8)
 * Wraps FUN_001a3e10 then tails through objc msgSend with param_2.
 * Confidence: medium.
 */
uint64_t sk_sched_bind_check(uint64_t a, uint64_t b)
{
    uint64_t r = /* FUN_001a3e10() */0;
    /* FUN_003a25d4(b) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e07f0   (est. sk_sched_unbind_check)
 * Ghidra: undefined8 FUN_001e07f0(undefined8,undefined8)
 * Wraps FUN_001a3fbc then tails through objc msgSend with param_2.
 * Confidence: medium.
 */
uint64_t sk_sched_unbind_check(uint64_t a, uint64_t b)
{
    uint64_t r = /* FUN_001a3fbc() */0;
    /* FUN_003a25d4(b) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e0824   (est. sk_sched_epoch_check)
 * Ghidra: undefined8 FUN_001e0824(undefined8,undefined8)
 * Wraps FUN_00083450 then tails through objc msgSend with param_2.
 * Confidence: medium.
 */
uint64_t sk_sched_epoch_check(uint64_t a, uint64_t b)
{
    uint64_t r = /* FUN_00083450() */0;
    /* FUN_003a25d4(b) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e0858   (est. sk_sched_phase_check)
 * Ghidra: undefined8 FUN_001e0858(undefined8,undefined8)
 * Wraps FUN_001a4154 then tails through objc msgSend with param_2.
 * Confidence: medium.
 */
uint64_t sk_sched_phase_check(uint64_t a, uint64_t b)
{
    uint64_t r = /* FUN_001a4154() */0;
    /* FUN_003a25d4(b) */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e088c   (est. sk_sched_period_check)
 * Ghidra: undefined8 FUN_001e088c(void)
 * Locked scheduler helper: obj-method setup, reads current obj, runs FUN_001a4554, then invokes
 * the obj method at (x16+8) and returns the accumulator.
 * Confidence: medium.
 */
uint64_t sk_sched_period_check(void)
{
    /* FUN_00353ed8 / FUN_0007c1c4 */
    uint64_t r = /* FUN_001a4554() */0;
    /* FUN_0034b3e8; (**(x16+8))() */
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_001e08e8 @ 0x001e08e8   (est. sk_sched_cpu_queue_push)
 * Ghidra: void FUN_001e08e8(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Full scheduler enqueue: grabs current CPU obj, runs a sequence of obj-dispatch/lock helpers,
 * picks the run-queue length field at (obj+0x30), and either pushes param_4 onto the run queue
 * (via FUN_003579e8) or, on an underflow/error path, releases via FUN_0034ec88. Returns the
 * boolean success via FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_cpu_queue_push(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_cpu_get();
    /* FUN_00349720; (*DAT_00658c00)(x8+0x40); FUN_003497b4; FUN_0034d024; FUN_0031b274;
     * FUN_00348e18; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4; FUN_0034d414;
     * FUN_003515b4; FUN_003722e4; FUN_00348fd8; FUN_0007c1a4; (*DAT_00658c00)() */
    long rq = /* FUN_0034b2f8() */0;
    int off = *(int *)(rq + 0x30);
    /* pcVar5 = *(x16_00+0x10); FUN_0034db38; (*pcVar5)(); FUN_0035745c(x23+off); (*pcVar5)();
     * FUN_0034ad40() */
    /* if (Z) { success=1; ... } else { FUN_0034cf94; ... FUN_003579e8(r, x23+off); ... } */
    uint r = 0;
    /* FUN_00350524(*(lVar2+8)); (*x8_02)(); FUN_0008e500(r&1, x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e0b00 @ 0x001e0b00   (est. sk_sched_cpu_queue_pop)
 * Ghidra: void FUN_001e0b00(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Scheduler dequeue mirror of FUN_001e08e8: pop from run queue at (obj+0x30), with error paths
 * via FUN_0034ec88/FUN_00354810 and result published via FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_cpu_queue_pop(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_cpu_get();
    /* FUN_00349720; (*DAT_00658c00)(x8+0x40); FUN_003497b4; FUN_0034d024; FUN_0031b274;
     * FUN_00348d4c; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4; FUN_0035050c; FUN_003515b4;
     * FUN_003722e4; FUN_00348e18; FUN_0007c1a4; (*DAT_00658c00)() */
    long rq = /* FUN_0034b05c() */0;
    int off = *(int *)(rq + 0x30);
    /* pcVar5 = *(x16_00+0x10); FUN_003510dc; (*pcVar5)(); (*pcVar5)(x25+off, x1); FUN_0034ad40() */
    uint r = 0;
    /* FUN_00350618(*(lVar4+8)); (*x8_02)(); FUN_0008e500(r&1, x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e0d24 / FUN_001e0d28   (est. sk_sched_ready_check_a) — alias pair
 * Ghidra: uint FUN_001e0d24(void)  /  FUN_001e0d28 same
 * Returns FUN_001b89a4() & 1.
 * Confidence: medium.
 */
uint sk_sched_ready_check_a(void)  { return /* FUN_001b89a4() */0 & 1; }
uint sk_sched_ready_check_a2(void) { return /* FUN_001b89a4() */0 & 1; }

/* ------------------------------------------------------------------ *
 * FUN_001e0d40 / FUN_001e0d44   (est. sk_sched_ready_check_b) — alias pair
 * Ghidra: uint FUN_001e0d40(void)  /  FUN_001e0d44 same
 * Returns FUN_001b8cf4() & 1.
 * Confidence: medium.
 */
uint sk_sched_ready_check_b(void)  { return /* FUN_001b8cf4() */0 & 1; }
uint sk_sched_ready_check_b2(void) { return /* FUN_001b8cf4() */0 & 1; }

/* ------------------------------------------------------------------ *
 * FUN_001e0d5c / FUN_001e0d60   (est. sk_sched_ready_check_c) — alias pair
 * Ghidra: uint FUN_001e0d5c(void)  /  FUN_001e0d60 same
 * Returns FUN_001b9040() & 1.
 * Confidence: medium.
 */
uint sk_sched_ready_check_c(void)  { return /* FUN_001b9040() */0 & 1; }
uint sk_sched_ready_check_c2(void) { return /* FUN_001b9040() */0 & 1; }

/* ------------------------------------------------------------------ *
 * FUN_001e0d88   (est. sk_sched_yield_svc)
 * Ghidra: void FUN_001e0d88(undefined8 p1,undefined8 p2,undefined8 p3)
 * Scheduler yield service: locks the scheduler, and depending on a flag either calls
 * FUN_00229a3c() (yield path) or builds an error tuple via FUN_00350470 and runs a fuller
 * yield sequence ending in FUN_00350878 + obj-dispatch.
 * Confidence: medium.
 */
void sk_sched_yield_svc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* FUN_0035a080; uVar1 = *(x1+0x10); FUN_003499b4; (*DAT_00658c00)(); FUN_0034c8e0;
     * FUN_0034b7e4; (*DAT_00658c00)(); FUN_003501b8; (**x12+0x10)(); FUN_00349f3c() */
    if (/* Z */1) {
        /* FUN_00229a3c() */
    } else {
        /* FUN_00354810; auVar2 = FUN_00350470(); (*x9)(...); FUN_00229a3c(0);
         * FUN_0031945c(p3); FUN_00351318; FUN_00350878; (*x8)(); FUN_0034da48; (*x8_00)() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e0f04   (est. sk_sched_obj_method_enter)
 * Ghidra: void FUN_001e0f04(undefined8 p1,long p2)
 * Runs an obj method: loads the vtable at (p2+0x10), invokes (x16+0x10)(p1,x1,uVar1), then
 * FUN_0034b744 + FUN_000839d8.
 * Confidence: medium.
 */
void sk_sched_obj_method_enter(uint64_t p1, long p2)
{
    uint64_t m = *(uint64_t *)(p2 + 0x10);
    /* FUN_0034b518; (**x16+0x10)(p1, x1, m); FUN_0034b744; FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e0f54   (est. sk_sched_obj_method_enter2)
 * Ghidra: void FUN_001e0f54(undefined8 p1,long p2,undefined8 p3,undefined8 p4)
 * Forwards to FUN_00350744(p1,p3,p4,*(p2+0x10)) then FUN_000839d8.
 * Confidence: medium.
 */
void sk_sched_obj_method_enter2(uint64_t p1, long p2, uint64_t p3, uint64_t p4)
{
    /* FUN_00350744(p1,p3,p4,*(p2+0x10)); FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e0f74 @ 0x001e0f74   (est. sk_sched_charge_svc)
 * Ghidra: void FUN_001e0f74(void)
 * Full scheduler-charge service: CPU obj, double lock, dispatches to run queue; on an error
 * (0xe9) it panics via FUN_001afe4c; otherwise it runs a budget/charge sequence and publishes
 * via FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_charge_svc(void)
{
    sk_cpu_get();
    /* FUN_00353e88; FUN_00350a64; FUN_00351654; FUN_00377824(); FUN_00348d64; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b71c; FUN_0034c5fc; FUN_00377bec(); FUN_00027754; FUN_0008f6f4;
     * FUN_00349dfc; FUN_003511c0; uVar2 = FUN_00377824(); FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_003494b4; (*DAT_00658c00)(x8_00+0x40); FUN_0034947c; FUN_0034f604;
     * auVar4 = FUN_0031b274(); FUN_000a6f88(...); FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034d3c4;
     * (**x12+0x10)(); FUN_00349f3c() */
    if (/* Z */1) {
        /* FUN_00348b7c(0xe9); FUN_0034abb0; FUN_00352be0; FUN_001afe4c() -- panic */
    }
    /* FUN_0035478c; FUN_00350624; (*x9)(); FUN_00027754; FUN_0034a30c; FUN_0034beec;
     * uVar3 = (*x8_01)(); if 0 -> FUN_0034ad00; auVar4=FUN_00350a70(); FUN_00377bec(...);
     * uVar2=FUN_0034bc04(); FUN_00350f3c(uVar2,0x200); ... */
    /* FUN_003509d4(*(x16+8)); (*x8_03)(); FUN_00350774(x8,!bVar1); FUN_000839d8();
     * FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e1f58 @ 0x001e1f58   (est. sk_sched_wake_svc)
 * Ghidra: void FUN_001e1f58(void)
 * Large scheduler wake service: CPU obj, double lock, run-queue compare of two lengths
 * (lVar5/lVar6), then a long priority/bitmap selection between the two run queues, and finally
 * publishes via FUN_003581a4 + FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_wake_svc(void)
{
    sk_cpu_get();
    /* auVar9 = FUN_0034e8a4(); FUN_00349684(in_x4); FUN_003523fc; uVar2=FUN_00377824();
     * FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aab0; FUN_0034a774; FUN_003513fc;
     * uVar3=FUN_00377824(); FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428;
     * FUN_00349080; (*DAT_00658c00)(x8+0x40); FUN_003497b4; FUN_0034911c; (*DAT_00658c00)(x8_01+0x40);
     * FUN_003497b4; FUN_003557a8; FUN_003564a4; FUN_0034ba08; (*unaff_x22)(); FUN_00354cc0;
     * FUN_0035305c; FUN_0034b4a0; uVar1=(*x8_02)() */
    if (/* (w28^uVar1)&1 == 0 */1) {
        /* FUN_0034c368; FUN_0035072c; lVar5=(*x8_06)(); FUN_0034a588; lVar6=(*x8_07)();
         * if (lVar6 <= lVar5) -> FUN_0034eaac; ... goto LAB_001e2310 */
    } else {
        /* FUN_0034ba08; uVar4=(*unaff_x22)(); FUN_0034c368; FUN_0035072c; lVar5=(*x8_03)();
         * FUN_0034c0d0; FUN_0034e064; lVar6=(*x8_04)(); ... two-way selection ... */
    }
    /* uVar7 = FUN_003581a4(); FUN_0008e500(uVar7, x8_00) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e23b0   (est. sk_swift_int_overflow_check)
 * Ghidra: void FUN_001e23b0(ulong param_1)
 * Swift "Fatal error" overflow guard: for a signed value, if it is negative emits
 * "Negative value is not representable" (0xcf8, str 0x005ce190), else if >= 0x100 emits
 * "Not enough bits to represent the passed value" (0xcfc, str 0x005cd650) — both via the
 * Swift _FatalError with module "Swift/Integers" (str 0x005cd680).
 * Confidence: high (string-matched).
 */
void sk_swift_int_overflow_check(unsigned long v)
{
    if ((long)v < 0) {
        /* FUN_001afe4c(s_Fatal_error,0xb,2,s_Negative_value_005ce190,0x23,2,
         *              s_Swift_Integers_005cd680,0x14,2,0xcf8,1) */
    } else if (v >= 0x100) {
        /* FUN_001afe4c(..., s_Not_enough_bits_005cd650,0x2d,2, s_Swift_Integers,0x14,2,0xcfc,1) */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e2460   (est. sk_swift_hash_seed_fini)
 * Ghidra: void FUN_001e2460(void)
 * Small Swift runtime finalizer: obj-method setup on the hash seed then several helpers.
 * Confidence: medium.
 */
void sk_swift_hash_seed_fini(void)
{
    /* FUN_0034b13c; FUN_0035a5f0; FUN_003499f0; (*DAT_00658c00)(x8+0x40); FUN_00348f38;
     * FUN_00353c24(*(x12+0x10)); (*x8_00)(); FUN_0016796c; FUN_0035133c; FUN_00350bb4;
     * FUN_0034fe38; (*x9)() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e2508   (est. sk_sched_sleep_svc)
 * Ghidra: void FUN_001e2508(void)
 * Large scheduler sleep service mirroring FUN_001e1f58: CPU obj, double lock, run-queue
 * length selection, and publishing via FUN_00352980 + FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_sleep_svc(void)
{
    sk_cpu_get();
    /* FUN_0034e8a4; FUN_00357748; FUN_00349684(in_x5); FUN_003513fc; uVar2=FUN_00377824();
     * FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aab0; FUN_0034a774; FUN_003523fc;
     * uVar3=FUN_00377824(); FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428;
     * FUN_0034911c; (*DAT_00658c00)(x8+0x40); FUN_003497b4; FUN_00349080; (*DAT_00658c00)(x8_01+0x40);
     * FUN_003497b4; FUN_003531b4; FUN_003564a4; FUN_0034b4a0; (*unaff_x22)(); FUN_003577e4;
     * FUN_0034acd0; uVar1=(*x8_03)() */
    if (/* (w28^uVar1)&1 == 0 */1) {
        /* FUN_00310a44; FUN_0034ae6c; (*x8_07)(); FUN_00354864; FUN_00310a44; FUN_0034bfa4;
         * lVar5=(*x8_08)() ... */
    } else {
        /* FUN_0034b4a0; uVar4=(*unaff_x22)(); FUN_0034c0d0; FUN_0034c9a8; lVar5=(*x8_04)();
         * FUN_0034c368; FUN_0034f504; lVar6=(*x8_05)(); ... */
    }
    /* uVar7 = FUN_00352980(); FUN_0008e500(uVar7, x8_00) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e2948 @ 0x001e2948   (est. sk_sched_dispatch_svc)
 * Ghidra: void FUN_001e2948(undefined8 p1,undefined8 p2,long p3,undefined8 p4,undefined8 p5)
 * Complex scheduler dispatch service. Takes a sched-context object (param_3); reads vtable at
 * (param_3+0x10) and flag at (param_3+0x24); double-locks; compares two object entries
 * (iVar1/iVar2 via FUN_000839f8) and takes one of three dispatch branches that run a full
 * obj-method chain (priority/bitmap selection, budget accounting), finally publishing local_8
 * via FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_dispatch_svc(uint64_t p1, uint64_t p2, long p3, uint64_t p4, uint64_t p5)
{
    /* auVar10 = FUN_0008e518(); uVar9 = *(p3+0x10); FUN_00355858; FUN_00353160; FUN_00351220;
     * lVar3 = FUN_00377824(); FUN_00100c38; FUN_0035053c; FUN_00377bec; uVar4 = FUN_00027754();
     * FUN_00351684; auVar11 = FUN_00349dfc(); FUN_00377824(...); FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034aa9c; FUN_00350798; FUN_00377dcc; uVar5 = FUN_000a6f88();
     * (*DAT_00658c00)(x8+0x40); FUN_00348b5c; (*DAT_00658c00)(); FUN_00349f5c; (*DAT_00658c00)();
     * FUN_0034bc58; FUN_003499c8; (*DAT_00658c00)(x8_00+0x40); FUN_00348a34; (*DAT_00658c00)();
     * FUN_0034ba68; FUN_00351dfc(0xff); FUN_0031b274; FUN_0034e57c; FUN_003515b4; FUN_003722e4;
     * FUN_00351f10; FUN_0007c1a4; (*DAT_00658c00)(); lVar6 = FUN_0034d3c4(); lVar6 = *(int*)(lVar6+0x38);
     * FUN_0034dfe4; pcVar8 = *(x16_01+0x10); (*pcVar8)(lVar3,auVar10._0_8_);
     * (*pcVar8)(lVar3+lVar6,auVar10._8_8_); auVar10 = FUN_00351d24();
     * iVar1 = FUN_000839f8(auVar10._0_8_,auVar10._8_8_,uVar9);
     * iVar2 = FUN_000839f8(lVar3+lVar6,1,uVar9) */
    uint64_t out = 0;
    /* three-way branch on iVar1/iVar2 ... FUN_0008e500(out, x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e2e18   (est. sk_swift_buffer_init)
 * Ghidra: void FUN_001e2e18(undefined8 param_1)
 * Swift buffer initializer: builds a buffer via FUN_0031b274/FUN_000a6f88, and either calls the
 * owning method (x16+0x20) on param_1, or panics via FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_buffer_init(uint64_t param_1)
{
    /* FUN_003504e8; auVar1 = FUN_0031b274(); FUN_000a6f88(...); FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034cff4; FUN_000b4390(*(x12+0x10)); (*x8)(); FUN_00349f3c() */
    if (!/* Z */0) {
        /* FUN_0034b3e8; (**x16+0x20)(param_1) */
    } else {
        /* FUN_003489fc; FUN_00349de8; FUN_001afe4c() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e2f48   (est. sk_sched_obj_bind_svc)
 * Ghidra: void FUN_001e2f48(undefined8 p1,undefined8 p2,undefined8 p3)
 * Binds a scheduler object: reads vtable at (obj+0x10), does two guarded method calls, and on
 * success runs a full bind sequence (obj-method invoke + publish), else falls to FUN_000dbe70.
 * Confidence: medium.
 */
void sk_sched_obj_bind_svc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_get();
    /* auVar4 = FUN_0035199c(); uVar3 = *(auVar4._8_8_+0x10); FUN_00351ad4(p3);
     * pcVar1 = FUN_00310e20(); FUN_0034d2e4(); uVar2 = (*pcVar1)() */
    if (/* (uVar2&1)!=0 */1) {
        /* FUN_00352c28(auVar4._0_8_, x20 + *(int*)(auVar4._8_8_+0x24)); uVar2 = (*pcVar1)() */
        if (/* (uVar2&1)!=0 */1) {
            /* FUN_0034b518; (**x16+0x10)(x8,auVar4._0_8_,uVar3); FUN_0034b744; FUN_000839d8;
             * FUN_0034e0d4; FUN_0031b274; FUN_0034b744; FUN_000839d8; goto LAB_001e301c */
        }
    }
    /* FUN_000dbe70(0xff); FUN_0031b274() */
    /* FUN_00350798; FUN_00356e34; auVar4 = FUN_003507e0();
     * FUN_0008e500(auVar4._0_8_,auVar4._8_8_,1); FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3048   (est. sk_obj_check_flag)
 * Ghidra: uint FUN_001e3048(long param_1)
 * Reads the flag at (param_1+0x18) and returns its low bit after an obj-dispatch guard.
 * Confidence: medium.
 */
uint sk_obj_check_flag(long param_1)
{
    /* FUN_0034a30c(*(param_1+0x18)); FUN_0034beec(); uVar1 = (*x8)() */
    return 0 & 1;
}

/* ------------------------------------------------------------------ *
 * FUN_001e3094 / FUN_001e3098   (est. sk_sched_enter_forward) — alias pair
 * Ghidra: void FUN_001e3094(void) / FUN_001e3098 same — forward to FUN_001e0f54.
 * Confidence: medium.
 */
void sk_sched_enter_forward(void)  { /* FUN_001e0f54() */ }
void sk_sched_enter_forward2(void) { /* FUN_001e0f54() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e30ac   (est. sk_dict_bucket_create)
 * Ghidra: undefined * FUN_001e30ac(long *param_1,undefined8 p2,undefined8 p3,ulong p4)
 * Allocates a 0x28 dictionary-bucket object (tag 0x7135), stores it, then calls FUN_001e312c to
 * fill key/value metadata, stores the result at +0x20, and returns a vtable pointer.
 * Confidence: medium.
 */
void *sk_dict_bucket_create(long *out, uint64_t p2, uint64_t p3, unsigned long p4)
{
    long b = /* FUN_0036a908(0x28,0x7135) */0;
    *out = b;
    uint64_t r = sk_dict_bucket_init(b, p2, p3,
                                     *(uint64_t *)((p4 & 0xfffffffffffffffe) - 8),
                                     *(uint64_t *)((p4 & 0xfffffffffffffffe) - 0x10));
    *(uint64_t *)(b + 0x20) = r;
    return &/* DAT_003471a4 */0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e312c   (est. sk_dict_bucket_init)
 * Ghidra: undefined1[16] FUN_001e312c(long *param_1,undefined8 p2,long p3,undefined8 p4,undefined8 p5)
 * Initializes a dictionary bucket: stores the element-type word from (p3+0x10), the value-type
 * metadata pointer from (type+0x40), allocates the element buffer (tag 0xb78e), and runs
 * sk_swift_buffer_init. Returns a (vtable, buffer) pair.
 * Confidence: medium.
 */
uint64_t sk_dict_bucket_init(long *out, uint64_t p2, long p3, uint64_t p4, uint64_t p5)
{
    long t = *(long *)(p3 + 0x10);
    *out = t;
    long vt = *(long *)(t + -8);
    out[1] = vt;
    long buf = /* FUN_0036a908(*(vt+0x40), 0xb78e) */0;
    out[2] = buf;
    sk_swift_buffer_init(buf);   /* FUN_001e2e18 */
    return /* (buf, &DAT_003471a8) */buf;
}

/* ------------------------------------------------------------------ *
 * FUN_001e3210   (est. sk_swift_range_checked_copy)
 * Ghidra: void FUN_001e3210(undefined8 p1,undefined8 p2,long p3,undefined8 p4,undefined8 p5,code* param_6)
 * Range-checked copy helper: calls a stride-transform callback twice, computes (p3 - x22), and
 * on an out-of-range value either runs FUN_0008412c + sk_sched_yield (FUN_001e638c) or the
 * Swift "fatal" path FUN_00068e14. SoftwareBreakpoint(1) at 0x1e32a8 on overflow.
 * Confidence: medium (Swift range-check pattern).
 */
void sk_swift_range_checked_copy(uint64_t p1, uint64_t p2, long p3, uint64_t p4, uint64_t p5,
                                 void (*cb)(void))
{
    /* FUN_00351da8; FUN_003509ec; FUN_00352b38; (*cb)(); FUN_00352b38(p3); (*cb)() */
    /* uVar1 = p3 - x22; SBORROW8 -> SoftwareBreakpoint(1,0x1e32a8) */
    if (/* in-range */1) {
        /* FUN_0008412c(); FUN_001e638c() */
    } else {
        /* FUN_00068e14() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e32a8   (est. sk_swift_range_checked_index)
 * Ghidra: undefined1[16] FUN_001e32a8(undefined8 p1,ulong p2,undefined8 p3,undefined8 p4)
 * Range-checked index helper: computes the distance via FUN_001e67d8, and if out of range
 * returns (FUN_001e63c4 result, 0) else (0,1) — a (index, inRange) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_range_checked_index(uint64_t p1, unsigned long p2, uint64_t p3, uint64_t p4)
{
    unsigned long dist = sk_swift_str_distance(p1, p3, p4);   /* FUN_001e67d8 */
    if (/* out of range */1) {
        return /* (FUN_001e63c4(p1,p2,p4), 0) */0;
    }
    return /* (0, 1) */1;
}

/* ------------------------------------------------------------------ *
 * FUN_001e3324   (est. sk_swift_range_checked_index2)
 * Ghidra: undefined1[16] FUN_001e3324(long p1,ulong p2,long p3,uint p4)
 * Range-checked index helper computing a width from param_4 (byte-width via Swift strided
 * logic), bounds-checking (p3-p1) against param_2, and returning a (ptr, inRange) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_range_checked_index2(long p1, unsigned long p2, long p3, uint p4)
{
    /* uVar4 = width-select on p4 (1/2/3/4 bytes); FUN_001dff60(0,w); FUN_0019fe7c(p1,...);
     * FUN_0019fe7c(p3,...); uVar2 = p3-p1; SBORROW8 -> SoftwareBreakpoint(1,0x1e342c) */
    if (/* in-range */1) {
        long end = p1 + p2;   /* SCARRY8 -> SoftwareBreakpoint(1,0x1e3430) */
        /* FUN_001dff60(0,w); FUN_0019fe7c(end,...); return (0, end) */
    }
    return /* (1, 0) */0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e3430   (est. sk_swift_range_checked_buf)
 * Ghidra: undefined1[16] FUN_001e3430(long p1,ulong p2,long p3)
 * Range-checked buffer helper: stamps two bounds words with width 2, checks (p3-p1) vs p2,
 * returns (ptr, inRange) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_range_checked_buf(long p1, unsigned long p2, long p3)
{
    /* FUN_0019fe7c(p1,0,2); FUN_0019fe7c(p3,0,2); uVar1 = p3-p1; SBORROW8 -> SBP 0x1e34d4 */
    if (/* in-range */1) {
        long end = p1 + p2;  /* SCARRY8 -> SBP 0x1e34d8 */
        /* FUN_0019fe7c(end,0,2); return (0,end) */
    }
    return /* (1,0) */0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e34d8   (est. sk_swift_range_check_loop)
 * Ghidra: void FUN_001e34d8(void)
 * Range-check loop via a stride callback (in_x4): calls the callback twice, computes
 * (x23 - x21), and on out-of-range runs FUN_0011aa70 + FUN_001e655c or FUN_00068e14.
 * SBP at 0x1e3568.
 * Confidence: medium.
 */
void sk_swift_range_check_loop(void)
{
    /* pcVar2 = in_x4; FUN_00355bb8; FUN_0034cbec; (*pcVar2)(); FUN_003509f8; (*in_x4)();
     * uVar1 = x23 - x21; SBORROW8 -> SBP 0x1e3568 */
    if (/* in-range */1) {
        /* FUN_0011aa70(); FUN_001e655c() */
    } else {
        /* FUN_00068e14() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e3568   (est. sk_swift_range_checked_copy2)
 * Ghidra: void FUN_001e3568(undefined8 p1,undefined8 p2,long p3,undefined8 p4,code* param_5)
 * Range-checked copy: stride callback twice, (p3 - x21) vs x20, on in-range calls
 * FUN_000b43d0 + FUN_001e655c, else FUN_00068e14. SBP at 0x1e3600.
 * Confidence: medium.
 */
void sk_swift_range_checked_copy2(uint64_t p1, uint64_t p2, long p3, uint64_t p4, void (*cb)(void))
{
    /* pcVar2 = param_5; FUN_0034cbec; (*pcVar2)(); FUN_003509f8(p3); (*cb)();
     * uVar1 = p3 - x21; SBORROW8 -> SBP 0x1e3600 */
    if (/* in-range */1) {
        /* auVar3 = FUN_000b43d0(); FUN_001e655c(auVar3._0_8_,auVar3._8_8_,p4) */
    } else {
        /* FUN_00068e14() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e3600 / FUN_001e3698  (est. sk_swift_range_checked_copy3) — near-identical
 * Ghidra: void FUN_001e3600(...,code* param_5) / FUN_001e3698 same
 * Same shape as FUN_001e3568 (SBP at 0x1e3698 / 0x1e3730 respectively).
 * Confidence: medium.
 */
void sk_swift_range_checked_copy3(uint64_t p1, uint64_t p2, long p3, uint64_t p4, void (*cb)(void))
{
    /* identical body to FUN_001e3568; SBP 0x1e3698 */
    if (/* in-range */1) {
        /* auVar3 = FUN_000b43d0(); FUN_001e655c(auVar3._0_8_,auVar3._8_8_,p4) */
    } else {
        /* FUN_00068e14() */
    }
}
void sk_swift_range_checked_copy4(uint64_t p1, uint64_t p2, long p3, uint64_t p4, void (*cb)(void))
{
    /* identical; SBP 0x1e3730 */
    if (/* in-range */1) {
        /* auVar3 = FUN_000b43d0(); FUN_001e655c(auVar3._0_8_,auVar3._8_8_,p4) */
    } else {
        /* FUN_00068e14() */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_001e3730   (est. sk_swift_valid_utf8_fatal)
 * Ghidra: ulong FUN_001e3730(undefined8 p1,ulong p2,undefined8 p3,undefined8 p4)
 * Swift "Fatal error" for valid-UTF8 buffer manipulation: computes bit-widths via
 * FUN_002c8c2c and LZCOUNT shifts, and on any invalid configuration panics with the module
 * "Swift/ValidUTF8Buffer" (str 0x005d08c0) and codes 0x82/0x83/0x8e/0x8f.
 * Confidence: high (string-matched module).
 */
unsigned long sk_swift_valid_utf8_fatal(uint64_t p1, unsigned long p2, uint64_t p3, uint64_t p4)
{
    unsigned long r = /* FUN_002c8c2c(p1,p4) */0;
    if (/* (r&1)!=0 */1) {
        r = /* FUN_002c8c2c(p3,p4) */0;
        if (/* (r&1)==0 */1) {
            /* panic 0x83 */
        }
        /* uVar4 = (LZCOUNT((int)p1) - LZCOUNT((int)p3)) >> 3; if in-range return 0x100000000;
         * uVar4 = FUN_002c8c2c(p4,p4); ... */
    }
    /* FUN_001afe4c(s_Fatal_error,0xb,2,&DAT_005be7c0,0,2,s_Swift_ValidUTF8Buffer,0x1b,2,0x82,1) */
    return 0x100000000ull;
}

/* ------------------------------------------------------------------ *
 * FUN_001e387c   (est. sk_swift_range_checked_buf2)
 * Ghidra: undefined1[16] FUN_001e387c(long p1,ulong p2,long p3,undefined8 p4,ulong p5)
 * Range-checked buffer with a width taken from (p5>>0x38 & 0xf): stamps bounds, checks
 * (p3-p1) vs p2, returns (ptr, inRange) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_range_checked_buf2(long p1, unsigned long p2, long p3, uint64_t p4,
                                     unsigned long p5)
{
    uint64_t w = (p5 >> 0x38) & 0xf;
    /* FUN_001dff60(0,w); FUN_0019fe7c(p1,...); FUN_001dff60(0,w); FUN_0019fe7c(p3,...);
     * uVar1 = p3-p1; SBORROW8 -> SBP 0x1e3964 */
    if (/* in-range */1) {
        long end = p1 + p2;  /* SCARRY8 -> SBP 0x1e3968 */
        /* FUN_001dff60(0,w); FUN_0019fe7c(end,...); return (0,end) */
    }
    return /* (1,0) */0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e3968   (est. sk_swift_range_checked_copy5)
 * Ghidra: void FUN_001e3968(undefined8 p1,undefined8 p2,long p3,long p4,long p5,code* param_6)
 * Range-checked copy with stride-transform: computes (p5-p4) into a first slot, then (p3-x22)
 * bounds check, and publishes an (index,0) pair via FUN_00084234.
 * Confidence: medium.
 */
void sk_swift_range_checked_copy5(uint64_t p1, uint64_t p2, long p3, long p4, long p5,
                                  void (*cb)(void))
{
    /* FUN_00084220; FUN_00351da8; FUN_003509ec; FUN_00350720(p5-p4); FUN_001dff60;
     * FUN_00351790; FUN_00351488; (*cb)(); FUN_00350720(); FUN_001dff60; FUN_00351790;
     * FUN_00351488(p3); (*cb)(); uVar2 = p3 - x22; SBORROW8 -> SBP 0x1e3a28 */
    if (/* in-range */1) {
        /* FUN_0008412c(); uVar2 = FUN_001e6608(); auVar3 = (uVar2, 0) */
    } else {
        /* auVar3 = FUN_00068e14() */
    }
    /* FUN_00084234(auVar3._0_8_, auVar3._8_8_, x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3a28   (est. sk_swift_array_get_index)
 * Ghidra: void FUN_001e3a28(void)
 * Swift array element access with bounds check: computes an index, on out-of-range it clears
 * the element slot via FUN_0031b1c4 + helpers, then publishes the element + flag.
 * Confidence: medium.
 */
void sk_swift_array_get_index(void)
{
    /* FUN_00084220; uVar2 = in_x4; FUN_00351a68; FUN_0031b28c(uVar2); FUN_0034a428;
     * uVar1 = (*x8)(); if out-of-range -> LAB_001e3ab4 */
    /* FUN_00027754(in_x4); FUN_00350bd8; auVar3 = FUN_00349748(); FUN_00377824(...);
     * auVar3 = FUN_0009461c(); FUN_00084234(auVar3._0_8_,auVar3._8_8_,1); FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3af0 / FUN_001e3af4   (est. sk_sched_notify_a) — alias pair
 * Ghidra: void FUN_001e3af0(void) / FUN_001e3af4 same — forward to FUN_001d2df0.
 * Confidence: medium.
 */
void sk_sched_notify_a(void)  { /* FUN_001d2df0() */ }
void sk_sched_notify_a2(void) { /* FUN_001d2df0() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e3b08 / FUN_001e3b0c   (est. sk_sched_notify_b) — alias pair
 * Ghidra: void FUN_001e3b08(void) / FUN_001e3b0c same — forward to FUN_001d2f94.
 * Confidence: medium.
 */
void sk_sched_notify_b(void)  { /* FUN_001d2f94() */ }
void sk_sched_notify_b2(void) { /* FUN_001d2f94() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e3b68   (est. sk_sched_yield_tail)
 * Ghidra: void FUN_001e3b68(void)
 * Scheduler yield tail: CPU obj, obj-method chain, dispatches the running method (x19) and
 * returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_yield_tail(void)
{
    sk_cpu_get();
    /* FUN_00350858; FUN_00356834; FUN_00350bfc; FUN_0031b274; FUN_00348d7c; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b0d4; FUN_0035478c; FUN_003508b4; (*x9)(); FUN_003508a8;
     * FUN_00350bfc; (*unaff_x19)(); FUN_003508f0(*(x16+8)); (*x8)(); FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3c88   (est. sk_sched_timer_cancel)
 * Ghidra: void FUN_001e3c88(void)
 * Scheduler timer-cancel service: CPU obj, dispatch, and on the armed path cancels the timer at
 * (x24+0x30) via a method chain; on the not-armed path panics with in_x6 code via FUN_001afe4c.
 * Confidence: medium.
 */
void sk_sched_timer_cancel(void)
{
    sk_cpu_get();
    /* FUN_00077888; FUN_0034b0b4; FUN_00359000; FUN_00348d4c; (*DAT_00658c00)(x8_00+0x40);
     * FUN_00348bbc; (*DAT_00658c00)(); FUN_0034ba68; FUN_00310e20; FUN_0034e60c;
     * uVar2 = (*x8_01)() */
    if (/* (uVar2&1)!=0 */1) {
        /* FUN_00349b00; pcVar4 = *(x8_02+0x10); (*pcVar4)(); FUN_00351b38(x27+*(int*)(x24+0x30));
         * (*pcVar4)(); FUN_00352a40; FUN_003518b8; (*x9_00)(); ... (cancel the timer) ... */
        /* FUN_0008e500(x9); return */
    }
    /* FUN_0034b348; FUN_00348b7c(in_x6); FUN_003499dc; FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3efc   (est. sk_sched_timer_arm)
 * Ghidra: void FUN_001e3efc(void)
 * Scheduler timer-arm service: dispatches the arm method through FUN_003511d8 with a stack
 * frame then FUN_001a8564.
 * Confidence: medium.
 */
void sk_sched_timer_arm(void)
{
    /* FUN_00354f10; FUN_00359134; FUN_003511d8(auStack_78); (*unaff_x19)(); FUN_001a8564() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e3f70   (est. sk_swift_optional_store)
 * Ghidra: void FUN_001e3f70(void)
 * Swift optional storage helper: computes an optional value via FUN_0034f064, and either stores
 * nil (alloc pages thunk) or a non-nil payload through the obj-copy chain; ends with
 * FUN_00084180.
 * Confidence: medium.
 */
void sk_swift_optional_store(void)
{
    /* FUN_00350a10(); uVar1 = FUN_0034f064(); if (x8==0 && ((uVar1 & ~x1)>>0x3d & 1)==0) {
     *   thunk_FUN_0036b270(); } else { ... FUN_0034c0a4(); FUN_002a4c98(); } FUN_00084180() */
}

/* ------------------------------------------------------------------ *
 * thunk_FUN_0026e7e4 @ 0x001e4018   (est. sk_dict_rehash)
 * Ghidra: void thunk_FUN_0026e7e4(void)
 * Dictionary rehash: allocates a 0x80-key buffer (tag 7), builds key/value header words
 * ("lowerBound"/"upperBound" strings at 0x756f427265776f6c = "lowerBo"..., 0x...646e = "nd\0"),
 * runs FUN_00319a4c twice, invokes the obj method, and finally calls FUN_001e4348 + FUN_00358804.
 * Confidence: medium (string words indicate Dictionary bound labels).
 */
void sk_dict_rehash(void)
{
    sk_cpu_get();
    /* FUN_00353aa0; FUN_000a6f88; (*DAT_00658c00)(x8+0x40); FUN_00349178; FUN_0034b768(*(x12+0x10));
     * (*x8_00)(); uVar2 = FUN_003519d4(); lVar3 = FUN_0036a940(uVar2,0x80,7);
     * *(lVar3+0x10) = _DAT_004c2450; *(lVar3+0x18) = uRam_004c2458;
     * *(lVar3+0x20) = 0x756f427265776f6c; *(lVar3+0x28) = 0xea0000000000646e;  // "lowerBound"
     * uVar4 = *(x20+0x10); *(lVar3+0x48) = uVar4; FUN_00319a4c(lVar3+0x30); FUN_0034d140;
     * pcVar5 = *(x16+0x10); (*pcVar5)(); *(lVar3+0x50) = 0x756f427265707075; *(lVar3+0x58) = 0xea0000000000646e;
     * // "upperBound" ; iVar1 = *(int*)(x20+0x24); *(lVar3+0x78) = uVar4; uVar2 = FUN_00319a4c(lVar3+0x60);
     * (*pcVar5)(uVar2,x20+iVar1,uVar4); FUN_000e15d8(auStack_30); FUN_0034d5ec; FUN_001e4348();
     * FUN_00358804(); FUN_0008e500(in_stack) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e401c   (est. sk_dict_init_swift)
 * Ghidra: void FUN_001e401c(undefined8 *param_1,undefined8 *param_2,undefined8 p3,undefined1 p4,
 *                           undefined8 p5,undefined8 p6)
 * Swift Dictionary initializer: unpacks the key/value metadata (param_2), builds a native
 * storage word ("Po" = 0x676f50), allocates 0x48 bytes (tag 7), registers an element transform
 * FUN_002db8e0, and validates layout via FUN_00365b6c. Returns the populated Dictionary.
 * Confidence: medium.
 */
void sk_dict_init_swift(uint64_t *out, uint64_t *meta, uint64_t p3, uint8_t p4,
                        uint64_t p5, uint64_t p6)
{
    /* local_90 = *meta; uStack_88 = meta[1]; ... auVar4 = FUN_002db6b8(&local_90,p5,p6,0x676f50);
     * FUN_00319350(p5,p6); uVar2 = FUN_00002534(0x656150,&DAT_004e7fa0); FUN_0036a940(uVar2,0x48,7);
     * uVar2 = FUN_002110f8(p3,FUN_002db8e0,0); ... iVar1 = FUN_00365b6c(auStack_e8,&local_c0,0x676f50,uVar3,6);
     * if (iVar1) FUN_000026e8(auStack_e8); *out=0x676f50; out[1]=uVar2; *(out+2)=p4; *(out+3)=auVar4;
     * *(out+5)= (iVar1!=0) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4164   (est. sk_dict_init_swift2)
 * Ghidra: void FUN_001e4164(undefined8 *param_1,undefined8 *param_2,undefined8 p3,undefined1 p4,
 *                           undefined8 p5,undefined8 p6)
 * Dictionary initializer variant with a different metadata tag (0x673a80); same shape as
 * FUN_001e401c.
 * Confidence: medium.
 */
void sk_dict_init_swift2(uint64_t *out, uint64_t *meta, uint64_t p3, uint8_t p4,
                         uint64_t p5, uint64_t p6)
{
    /* auVar4 = FUN_002db6b8(param_2,p5,p6,0x673a80); FUN_00319350(p5,p6);
     * uVar2 = FUN_00002534(0x656150,&DAT_004e7fa0); FUN_0036a940(uVar2,0x48,7);
     * uVar2 = FUN_002110f8(p3,FUN_002db8e0,0); ... FUN_00365b6c(auStack_b8,&local_90,0x673a80,uVar3,6);
     * ... same finalization */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4298   (est. sk_swift_dict_metadata)
 * Ghidra: void FUN_001e4298(void)
 * Swift Dictionary metadata initializer: chains several metadata/type-layout helpers and
 * validates via FUN_00356ff4; on failure runs FUN_003588b8.
 * Confidence: medium.
 */
void sk_swift_dict_metadata(void)
{
    /* FUN_0035300c; FUN_00352e54; in_stack_38 = FUN_003537fc(); FUN_00353178(&stack_38);
     * FUN_002db6b8(); FUN_003517c0; FUN_003512c0; FUN_00319350(); uVar2 = FUN_0035a974();
     * FUN_0036a940(uVar2,0x48,7); FUN_003546cc; FUN_002110f8(); FUN_0034f9b4; FUN_003582b8;
     * iVar1 = FUN_00356ff4(); if (iVar1) FUN_003588b8(&stack_8); FUN_00359b3c; FUN_00353238(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4348   (est. sk_dict_rebuild_storage)
 * Ghidra: void FUN_001e4348(undefined8 p1,undefined8 p2,undefined1 p3,undefined8 p4,
 *                           undefined8 p5,undefined8 p6)
 * Rebuilds Dictionary native storage: allocates 0x48 (tag 7), registers element transform,
 * validates layout, and writes the new Dictionary word into the obj method out-slot.
 * Confidence: medium.
 */
void sk_dict_rebuild_storage(uint64_t p1, uint64_t p2, uint8_t p3, uint64_t p4, uint64_t p5,
                             uint64_t p6)
{
    sk_cpu_get();
    /* FUN_0007c028; (*DAT_00658c00)(x8_00+0x40); FUN_00349068; FUN_00353178; FUN_002db6b8;
     * FUN_003517c0; FUN_00350bf0; FUN_00319350; uVar2 = FUN_0035a974(); FUN_0036a940(uVar2,0x48,7);
     * FUN_003546cc; uVar2 = FUN_002110f8(x1,x1_00,0); FUN_003508c0(*(x16+0x20)); (*x8_01)();
     * FUN_0034f9b4; FUN_00350c68(auStack_28); iVar1 = FUN_00365b6c(); if (iVar1==0) uVar3=0;
     * else { FUN_003588b8(auStack_28); uVar3 = extraout_w8; } *x8 = p6; x8[1] = uVar2; *(x8+2)=p3;
     * x8[3] = x23; x8[4] = x24; *(x8+5)=uVar3; FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4474   (est. sk_dict_build_swift)
 * Ghidra: void FUN_001e4474(void)
 * Dictionary builder: FUN_00356bec then the rehash thunk then FUN_0034a224.
 * Confidence: medium.
 */
void sk_dict_build_swift(void)
{
    /* FUN_00356bec(); thunk_FUN_0026e7e4(); FUN_0034a224() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e44a8 @ 0x001e44a8   (est. sk_dict_insert_svc)
 * Ghidra: void FUN_001e44a8(undefined8 p1,undefined8 p2,undefined8 p3)
 * Dictionary insert service: double lock, checks the object flag (FUN_001e3048); if clear it
 * runs a full key-insert chain (hash, probe, bucket write) and publishes; if the flag is set it
 * panics via FUN_001afe4c.
 * Confidence: medium.
 */
void sk_dict_insert_svc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_get();
    /* FUN_0008409c; auVar9 = FUN_0034b0b4(); FUN_003722e4(...); lVar2 = FUN_000a6f88();
     * (*DAT_00658c00)(x8+0x40); FUN_003493c4; FUN_0034d294; (*DAT_00658c00)(); FUN_0034b758;
     * FUN_0034d014; FUN_00377824(); FUN_00348d4c; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034a760;
     * FUN_003505e8; FUN_00353a78; FUN_00377bec(); FUN_00027754; FUN_003564d0; FUN_00350488;
     * FUN_00351aec; FUN_00377824(); FUN_0034a37c; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b0c4;
     * FUN_003494e8; (*DAT_00658c00)(x8_00+0x40); FUN_003493c4; FUN_0034c684; (*DAT_00658c00)();
     * FUN_0034ae58; FUN_00027754(p3); FUN_0034fce4; FUN_00310e08; uVar3 = FUN_001e3048() */
    if (/* (uVar3&1)==0 */1) {
        /* uVar4 = FUN_003549c0(p3); FUN_003504e8; lVar5 = FUN_00310e08(); iVar1 = *(int*)(lVar5+0x24);
         * FUN_00352314; FUN_00377bec; FUN_0034d4b8; uVar6 = FUN_00357754(); FUN_003518ac(uVar6,0x101);
         * (*x9)(); FUN_0034cea8; FUN_00353378; FUN_0035139c; (*x9_00)(); FUN_00354f4c(p3);
         * FUN_00356b74(iVar1); auVar9 = FUN_00350524(); (*x9_01)(...,p3); ... (probe + write bucket) ...
         * FUN_0008e500(x30); return */
    }
    /* FUN_00350410; FUN_003488bc; FUN_0034a96c; FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4900   (est. sk_dict_contains_key)
 * Ghidra: uint FUN_001e4900(void)
 * Dict contains-key helper: runs several metadata checks then FUN_001e4938.
 * Confidence: medium.
 */
uint sk_dict_contains_key(void)
{
    /* FUN_00358c50; FUN_003524bc; FUN_00310e08; FUN_0035a7e8 */
    return sk_dict_contains_key_impl() & 1;   /* FUN_001e4938 */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4938   (est. sk_dict_contains_key_impl)
 * Ghidra: uint FUN_001e4938(void)
 * Implements contains-key: reads a vtable (x1+0x18), two guarded method calls on key1/key2
 * buckets, and if neither matches runs the flag check FUN_001e3048 (inverted). Returns boolean.
 * Confidence: medium.
 */
uint sk_dict_contains_key_impl(void)
{
    /* FUN_00353a0c; uVar1 = *(x1+0x18); FUN_0034e0d4; lVar4 = FUN_00310f04(); iVar2 = *(int*)(lVar4+0x24);
     * FUN_0035044c(uVar1); FUN_00350968(x23+iVar2); uVar5 = (*x8)() */
    if (/* (uVar5&1)==0 */1) {
        /* iVar2 = *(int*)(x21+0x24); FUN_0035166c(uVar1); FUN_00351100(x20+iVar2); uVar5 = (*x8_00)() */
        if (/* (uVar5&1)==0 */1) {
            /* FUN_00353abc; uVar3 = FUN_001e3048(); return (uVar3 ^ 1) & 1 */
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e49d8 / FUN_001e49dc   (est. sk_dict_remove_forward) — alias pair
 * Ghidra: void FUN_001e49d8(void) / FUN_001e49dc same — forward to FUN_0026ea04.
 * Confidence: medium.
 */
void sk_dict_remove_forward(void)  { /* FUN_0026ea04() */ }
void sk_dict_remove_forward2(void) { /* FUN_0026ea04() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e4a04 / FUN_001e4a08   (est. sk_dict_clear_forward) — alias pair
 * Ghidra: void FUN_001e4a04(void) / FUN_001e4a08 same — forward to FUN_00270ab4.
 * Confidence: medium.
 */
void sk_dict_clear_forward(void)  { /* FUN_00270ab4() */ }
void sk_dict_clear_forward2(void) { /* FUN_00270ab4() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e4a30   (est. sk_dict_remove_key)
 * Ghidra: void FUN_001e4a30(void)
 * Dictionary remove-key: forward to FUN_0026f164.
 * Confidence: medium.
 */
void sk_dict_remove_key(void) { /* FUN_0026f164() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e4a48   (est. sk_dict_remove_key_swift)
 * Ghidra: void FUN_001e4a48(undefined8 p1,undefined8 p2,ulong p3)
 * Swift remove-value wrapper: calls FUN_001e4a30 with the key from (p3&~1)-8.
 * Confidence: medium.
 */
void sk_dict_remove_key_swift(uint64_t p1, uint64_t p2, unsigned long p3)
{
    /* FUN_001e4a30(p1,p2, *((p3 & 0xfffffffffffffffe) - 8)) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4a68   (est. sk_swift_buffer_tail)
 * Ghidra: long FUN_001e4a68(void)
 * Returns the buffer data pointer + 8 after FUN_00359024.
 * Confidence: medium.
 */
long sk_swift_buffer_tail(void)
{
    /* FUN_00359024(); return extraout_x8 + 8 */
    return 8;
}

/* ------------------------------------------------------------------ *
 * FUN_001e4aa0   (est. sk_swift_static_array_fatal)
 * Ghidra: void FUN_001e4aa0(void)
 * Swift static-array fatal: builds a "_StaticArrayStorage/st...Element" message (str 0x005cefc0)
 * and panics via FUN_001afa84.
 * Confidence: high (string-matched _StaticArrayStorage).
 */
void sk_swift_static_array_fatal(void)
{
    /* uVar1 = FUN_0035ac70(s___StaticArrayStorage_staticEleme_005cefc0); FUN_003593c0(uVar1,uVar1);
     * FUN_0006f768(); FUN_001afa84() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4b00   (est. sk_swift_buffer_fini)
 * Ghidra: void FUN_001e4b00(void)
 * Finalizes a Swift buffer: FUN_0035bc70(x20+0x20, *(x20+0x10), 0x6753a0).
 * Confidence: medium.
 */
void sk_swift_buffer_fini(void)
{
    /* FUN_0035bc70(x20+0x20, *(x20+0x10), 0x6753a0) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4b2c   (est. sk_swift_string_utf16_from)
 * Ghidra: void FUN_001e4b2c(void)
 * Builds a Swift string from UTF-16: calls FUN_001e4b70 for the source, then FUN_0035147c to
 * encode and FUN_0019cb68 to append.
 * Confidence: medium.
 */
void sk_swift_string_utf16_from(void)
{
    /* uVar1 = FUN_001e4b70(); auVar2 = FUN_0035147c(*(x20+0x10),uVar1);
     * FUN_0019cb68(auVar2._0_8_,auVar2._8_8_,*(x16+0x60)) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4b70   (est. sk_swift_string_bridge)
 * Ghidra: void FUN_001e4b70(void)
 * Bridges a Swift string: FUN_000027e8, FUN_003509c8(*(x16+0x60),...), FUN_00357c20, FUN_00359360.
 * Confidence: medium.
 */
void sk_swift_string_bridge(void)
{
    /* uVar1 = FUN_000027e8(); uVar1 = FUN_003509c8(*(x16+0x60),uVar1);
     * FUN_00357c20(*(x16_00+0x50),uVar1); FUN_00359360() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4bc8 / FUN_001e4bcc   (est. sk_swift_string_release) — alias pair
 * Ghidra: void FUN_001e4bc8(void) / FUN_001e4bcc same
 * String release: FUN_001e4b2c, FUN_00002834, FUN_0036b6ac.
 * Confidence: medium.
 */
void sk_swift_string_release(void)  { /* FUN_001e4b2c(); FUN_00002834(); FUN_0036b6ac() */ }
void sk_swift_string_release2(void) { /* FUN_001e4b2c(); FUN_00002834(); FUN_0036b6ac() */ }

/* ------------------------------------------------------------------ *
 * FUN_001e4bec   (est. sk_swift_string_get_buffer)
 * Ghidra: undefined8 FUN_001e4bec(void)
 * Returns the string buffer pointer from the obj-method slot (x16+0x60) after FUN_000027e8.
 * Confidence: medium.
 */
uint64_t sk_swift_string_get_buffer(void)
{
    /* FUN_000027e8(); return *(x16+0x60) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e4c10 / FUN_001e4c14   (est. sk_swift_string_fatal_release) — alias pair
 * Ghidra: void FUN_001e4c10(void) / FUN_001e4c14 same
 * Fatal release: FUN_00002834, FUN_0036a940, FUN_0036b118, then SoftwareBreakpoint(1,0x1e4c38).
 * Confidence: medium.
 */
void sk_swift_string_fatal_release(void)
{
    /* FUN_00002834(); FUN_0036a940(); FUN_0036b118(); SoftwareBreakpoint(1,0x1e4c38) */
}
void sk_swift_string_fatal_release2(void)
{
    /* FUN_00002834(); FUN_0036a940(); FUN_0036b118(); SoftwareBreakpoint(1,0x1e4c38) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4c38 / FUN_001e4c3c   (est. sk_swift_fatal_dealloc) — alias pair
 * Ghidra: void FUN_001e4c38(void) / FUN_001e4c3c same
 * Dealloc fatal: FUN_0036b118 then SoftwareBreakpoint(1,0x1e4c50).
 * Confidence: medium.
 */
void sk_swift_fatal_dealloc(void)
{
    /* FUN_0036b118(); SoftwareBreakpoint(1,0x1e4c50) */
}
void sk_swift_fatal_dealloc2(void)
{
    /* FUN_0036b118(); SoftwareBreakpoint(1,0x1e4c50) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4c5c   (est. sk_swift_string_append)
 * Ghidra: void FUN_001e4c5c(undefined8 p1,undefined8 p2,long p3)
 * String append: obj-method setup then FUN_001e4cbc(p3+x8, *(p3+0x10)) and dispatch.
 * Confidence: medium.
 */
void sk_swift_string_append(uint64_t p1, uint64_t p2, long p3)
{
    /* FUN_00351468; FUN_0035a028; FUN_00357c20(*(x16+0x50)); FUN_001e4cbc(p3+x8, *(p3+0x10));
     * (*unaff_x22)() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4cbc   (est. sk_swift_string_bounds_check)
 * Ghidra: void FUN_001e4cbc(long p1,long p2)
 * Swift string/array bounds check: if p2 < 0 or (p2==0 ? p1!=0), panics via FUN_00348548 /
 * FUN_003488bc + FUN_00349a04 + FUN_003524c8 + FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_string_bounds_check(long p1, long p2)
{
    if (p2 < 0) {
        /* FUN_00348548() */
    } else {
        if ((p2 == 0) || (p1 != 0)) {
            return;
        }
        /* FUN_003488bc(1); FUN_00349a04() */
    }
    /* FUN_003524c8(); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4d10   (est. sk_swift_string_utf8_append2)
 * Ghidra: void FUN_001e4d10(undefined8 p1,undefined8 p2,long p3)
 * UTF-8 append helper: computes a byte offset from the type metadata (*(*(p3+0x10)-8)+0x50) and
 * appends via FUN_001a26e0.
 * Confidence: medium.
 */
void sk_swift_string_utf8_append2(uint64_t p1, uint64_t p2, long p3)
{
    /* FUN_0034bb84; uVar1 = *(byte*)(*(*(p3+0x10)+-8)+0x50);
     * FUN_001a26e0(*x20 + ((uVar1+0x20)&~uVar1), *(*x20+0x10)); FUN_003522d4; (*x23)() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4d7c   (est. sk_swift_array_append_callout)
 * Ghidra: void FUN_001e4d7c(undefined8 p1,code* param_2,undefined8 p3,long p4,undefined8 p5,
 *                           long p6,undefined8 p7,undefined8 p8)
 * Array append callout: computes element offset via type metadata, runs a native append through
 * FUN_001a26e0, and conditionally calls the owning method (lVar1+0x20).
 * Confidence: medium.
 */
void sk_swift_array_append_callout(uint64_t p1, void (*cb)(void), uint64_t p3, long p4,
                                   uint64_t p5, long p6, uint64_t p7, uint64_t p8)
{
    long t = *(long *)(p6 + -8);
    /* (*DAT_00658c00)(*(t+0x40)); uVar2 = *(byte*)(*(*(p4+0x10)+-8)+0x50);
     * auVar3 = FUN_001a26e0(*x20 + ((uVar2+0x20)&~uVar2), *(*x20+0x10)); (*cb)(p1,...);
     * if (x21 != 0) (**t+0x20)(p8, stack, p6) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e4e94   (est. sk_swift_array_reserve)
 * Ghidra: undefined8 FUN_001e4e94(void)
 * Swift array reserve: if capacity check passes (FUN_003a261c) and the array length exceeds
 * half capacity, allocates pages via FUN_0036b270 and returns it, else 0.
 * Confidence: medium.
 */
uint64_t sk_swift_array_reserve(void)
{
    /* FUN_00356988(); iVar1 = FUN_003a261c(); if (iVar1 && x19 <= (*(ulong*)(*x20+0x18) >> 1)) {
     *   uVar2 = FUN_0036b270(); return uVar2; } return 0 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e5048   (est. sk_swift_array_buffer_create)
 * Ghidra: void FUN_001e5048(void)
 * Creates a 0x58 Swift ArrayBuffer: allocates storage (tag 0xc940), fills element/stride
 * metadata, allocates three backing buffers, and publishes a bound pointer via FUN_00084234.
 * Confidence: medium.
 */
void sk_swift_array_buffer_create(void)
{
    /* FUN_00084220; plVar2 = FUN_0034cf24(); plVar3 = FUN_0036a908(0x58,0xc940); *plVar2 = plVar3;
     * plVar3[1]=x21; plVar3[2]=x20; *plVar3=x22; lVar4 = FUN_00349b00(); *(lVar4+0x18)=x8;
     * *(lVar4+0x20)=x16; uVar7 = *(x8+0x40); lVar4 = FUN_0036a908(uVar7,0xc940); plVar3[5]=lVar4;
     * lVar4 = FUN_0036a908(uVar7,0xc940); plVar3[6]=lVar4; lVar4 = FUN_0036a908(uVar7,0xc940); plVar3[7]=lVar4;
     * pcVar5 = *(x16+0x10); bVar1 = *(x16+0x50); lVar6 = *(x16+0x48); plVar3[8]=lVar6; plVar3[9]=pcVar5;
     * plVar3[10]= ((x16+0x10)&0xffffffffffff | 0xe3ba000000000000); (*pcVar5)(lVar4, x21 + ((bVar1+0x20)&~bVar1) + lVar6*x22);
     * auVar8 = FUN_00353978(); FUN_00084234(auVar8._0_8_,auVar8._8_8_,x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5148   (est. sk_swift_array_buffer_release)
 * Ghidra: void FUN_001e5148(void)
 * Releases a Swift ArrayBuffer: loads the element type and releases its native/metadata
 * references via thunk_FUN_00012568 and obj-method chains.
 * Confidence: medium.
 */
void sk_swift_array_buffer_release(void)
{
    /* auVar9 = FUN_0035193c(); lVar6 = *auVar9._0_8_; lVar1 = *(lVar6+0x20); uVar4 = *(lVar6+0x28);
     * uVar2 = *(lVar6+0x38); uVar7 = *(lVar6+0x30); uVar3 = *(lVar6+0x10); lVar5 = *(lVar6+0x18);
     * lVar10 = *(lVar6+0x28) * *(lVar6+0x38); if ((auVar9._8_8_&1)==0) { ...obj-method chain... }
     * else { ... } thunk_FUN_00012568(uVar2); thunk_FUN_00012568(uVar7); thunk_FUN_00012568(uVar4);
     * FUN_00351774(lVar6,x30); thunk_FUN_00012568() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5320   (est. sk_swift_array_copy_range)
 * Ghidra: long FUN_001e5320(long p1,long p2,undefined8 p3,long p4,undefined8 p5)
 * Copies a range of a Swift array: computes the element offset via stride, calls
 * FUN_0019dadc, frees the source, and returns the destination end pointer.
 * SBP at 0x1e53a8 on (p2-p1) underflow.
 * Confidence: medium.
 */
long sk_swift_array_copy_range(long p1, long p2, uint64_t p3, long p4, uint64_t p5)
{
    /* if (!SBORROW8(p2,p1)) { FUN_00356048; lVar2 = FUN_0034e34c(); lVar3 = *(x8+0x48);
     * FUN_0019dadc(p4 + ((*(x16+0x50)+0x20)&~(*(x16+0x50))) + lVar3*lVar2, p2-p1, p3, p5);
     * FUN_0036b118(); return x19 + lVar3*(p2-p1); } SoftwareBreakpoint(1,0x1e53a8) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e53a8   (est. sk_swift_array_copy_range2)
 * Ghidra: void FUN_001e53a8(long p1,ulong p2,long p3)
 * Range copy with element count: clamps p2 to the array capacity, runs FUN_0019dadc, else
 * panics via FUN_00348898/FUN_00349ee0/FUN_00351a8c/FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_array_copy_range2(long p1, unsigned long p2, long p3)
{
    /* if (0 < (long)p2) { if (p1==0) { FUN_00348898(1,0,p2,0); FUN_00349ee0(); FUN_00351a8c();
     *     FUN_001afe4c(); } if (*(ulong*)(p3+0x10) <= p2) p2 = *(ulong*)(p3+0x10);
     *   FUN_0035a01c(); FUN_00357c20(*(x16+0x50)); FUN_0019dadc(p3+x8,p2); } FUN_0009461c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5438   (est. sk_swift_int_nonnegative_check)
 * Ghidra: void FUN_001e5438(void)
 * If in_x3 < 0, panics via FUN_003482c4/FUN_003523f0/FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_int_nonnegative_check(void)
{
    /* if (-1 < in_x3) return; FUN_003482c4(); FUN_003523f0(); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5464   (est. sk_swift_string_fatal_precondition)
 * Ghidra: void FUN_001e5464(void)
 * Precondition failure (code 0x315) then Swift fatal FUN_001afa84.
 * Confidence: high (precondition pattern).
 */
void sk_swift_string_fatal_precondition(void)
{
    /* FUN_00350d94(0x315); FUN_0006f768(); FUN_001afa84() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e54cc   (est. sk_swift_string_utf16_alloc)
 * Ghidra: void FUN_001e54cc(void)
 * Allocates a 0x40 UTF-16 buffer (tag 0x9ce4), encodes via FUN_00100efc/FUN_0019ec24, runs
 * FUN_00357694 + FUN_00353c54.
 * Confidence: medium.
 */
void sk_swift_string_utf16_alloc(void)
{
    /* FUN_00349a18; FUN_0036a908(0x40,0x9ce4); auVar1 = FUN_003501fc();
     * FUN_00100efc(auVar1._0_8_,auVar1._8_8_,*x20,*(x19+0x10)); FUN_0019ec24(); FUN_00357694();
     * FUN_00353c54() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5538 / FUN_001e553c   (est. sk_swift_string_utf16_append_alloc) — alias pair
 * Ghidra: uint FUN_001e5538(void) / FUN_001e553c same
 * Calls FUN_00359054/FUN_002dcb54 then the obj method at (*x1+0x50); returns low bit.
 * Confidence: medium.
 */
uint sk_swift_string_utf16_append_alloc(void)
{
    /* FUN_00359054(); FUN_002dcb54(); uVar1 = (**(code **)(*x1 + 0x50))(); return uVar1 & 1 */
    return 0;
}
uint sk_swift_string_utf16_append_alloc2(void)
{
    /* identical */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e5594   (est. sk_swift_array_append_loop)
 * Ghidra: void FUN_001e5594(void)
 * Swift array append loop: acquires the obj method at (*x1+0x58), converts via FUN_00362c34,
 * and iterates appending elements until FUN_00365b6c reports the collection is done, then
 * frees the temp buffer. Returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_array_append_loop(void)
{
    /* uVar3 = FUN_0008e518(); FUN_00351cf4; FUN_00349a68; (*DAT_00658c00)(x8+0x40); FUN_003490ec;
     * FUN_00349720; (*DAT_00658c00)(x8_00+0x40); FUN_00348abc; (*DAT_00658c00)(); FUN_0034c074;
     * uVar4 = (**x1+0x58)(); auVar6 = FUN_00362c34(uVar4,in_x3); uVar4 = auVar6._8_8_;
     * if (auVar6._0_8_ == 0) { FUN_0036b270(); while (true) { bVar1 = *(x19+0x10) == 0; if (bVar1) break;
     *   ... FUN_00365b6c(); if (==0) break; ... } FUN_0036b118(x19); uVar4 = x1_00; }
     * FUN_0008e500(bVar1,uVar4,uVar3) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5794 / FUN_001e5798   (est. sk_swift_array_pop_last) — alias pair
 * Ghidra: void FUN_001e5794(void) / FUN_001e5798 same — forward to FUN_0019c078.
 * Confidence: medium.
 */
void sk_swift_array_pop_last(void)  { /* FUN_0019c078() */ }
void sk_swift_array_pop_last2(void) { /* FUN_0019c078() */ }

/* ------------------------------------------------------------------ *
 * thunk_FUN_001f2ec4 @ 0x001e57c0   (est. sk_swift_collection_count)
 * Ghidra: void thunk_FUN_001f2ec4(void)
 * Calls FUN_003a261c(*x20) (collection refcount/count check).
 * Confidence: medium.
 */
void sk_swift_collection_count(void)
{
    /* FUN_003a261c(*unaff_x20) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e57ec   (est. sk_swift_dictionary_bridge_init)
 * Ghidra: void FUN_001e57ec(undefined8 p1,...,long p5)
 * Dictionary-bridge initializer: builds a native Dictionary word (0x676f50 via &DAT_0064c260)
 * through FUN_001a76fc with the element transform FUN_0034675c.
 * Confidence: medium.
 */
void sk_swift_dictionary_bridge_init(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, long p5)
{
    /* uVar3 = *(p5+0x10); uVar2 = *x20; local_60 = uVar3; uStack_58 = p4; local_50 = p2; local_48 = p3;
     * uVar1 = FUN_00002534(&DAT_0064c260,&DAT_004bbc30);
     * FUN_001a76fc(p1,FUN_0034675c,auStack_70,uVar2,uVar3,p4,uVar1,0x66c1c8,local_38) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e58a4   (est. sk_swift_dictionary_bridge_init2)
 * Ghidra: void FUN_001e58a4(void)
 * Dictionary-bridge init variant using FUN_001a76fc with the current obj method; conditional
 * owning-method call.
 * Confidence: medium.
 */
void sk_swift_dictionary_bridge_init2(void)
{
    /* lVar1 = *(in_x3 + -8); auVar2 = (*DAT_00658c00)();
     * FUN_001a76fc(auVar2._0_8_,auVar2._8_8_,*x20,*(in_x6+0x10));
     * if (x21 != 0) (**lVar1+0x20)(in_x5, stack, in_x3) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5970   (est. sk_swift_dictionary_bridge_init3)
 * Ghidra: void FUN_001e5970(undefined8 p1,...,long p5)
 * Dictionary-bridge init: FUN_001e4d7c with the transform FUN_0034678c.
 * Confidence: medium.
 */
void sk_swift_dictionary_bridge_init3(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, long p5)
{
    /* local_60 = *(p5+0x10); uStack_58 = p4; local_50 = p2; uStack_48 = p3;
     * uVar1 = FUN_00002534(&DAT_0064c260,&DAT_004bbc30);
     * FUN_001e4d7c(p1,FUN_0034678c,auStack_70,p5,p4,uVar1,0x66c1c8,local_38) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5a1c   (est. sk_swift_dictionary_bridge_init4)
 * Ghidra: void FUN_001e5a1c(void)
 * Dictionary-bridge init variant via FUN_001e4d7c; conditional owning-method call.
 * Confidence: medium.
 */
void sk_swift_dictionary_bridge_init4(void)
{
    /* lVar1 = *(in_x3 + -8); auVar2 = (*DAT_00658c00)(); FUN_001e4d7c(auVar2._0_8_,auVar2._8_8_,in_x6);
     * if (x21 != 0) (**lVar1+0x20)(in_x5, stack, in_x3) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5ae8   (est. sk_swift_dict_storage_create)
 * Ghidra: undefined1[16] FUN_001e5ae8(undefined8 *param_1,long p2)
 * Creates dictionary storage: stores the obj/type refs and the type word from
 * thunk_FUN_0001612c; returns a (vtable, storage) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_dict_storage_create(uint64_t *out, long p2)
{
    /* uVar1 = *(p2+0x10); out[1] = *x20; out[2] = uVar1; uVar1 = thunk_FUN_0001612c(); *out = uVar1;
     * return (out, &LAB_001e5b38) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e5b44   (est. sk_swift_dict_storage_copy)
 * Ghidra: void FUN_001e5b44(undefined8 p1,undefined8 p2,long p3)
 * Copies dictionary storage: computes element offsets and invokes the type's copy methods
 * (stride + value copy) at (type+0x10/8/0x28).
 * Confidence: medium.
 */
void sk_swift_dict_storage_copy(uint64_t p1, uint64_t p2, long p3)
{
    /* lVar2 = *(p3+0x10); lVar4 = *(lVar2 + -8); (*DAT_00658c00)(p1); puVar5 = stack - align;
     * (*DAT_00658c00)(); lVar6 = puVar5 - x13; lVar7 = *x1; uVar3 = *x20; pcVar8 = *(lVar4+0x20);
     * (*pcVar8)(lVar6,x8,lVar2); (*pcVar8)(puVar5,lVar6,lVar2); lVar1 = thunk_FUN_001dc3b8(uVar3,lVar2);
     * lVar1 += *(lVar4+0x48) * lVar7; (**lVar4+0x10)(lVar6,lVar1,lVar2); (**lVar4+8)(lVar6,lVar2);
     * (**lVar4+0x28)(lVar1,puVar5,lVar2) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5cc0   (est. sk_swift_array_buffer_init)
 * Ghidra: undefined1[16] FUN_001e5cc0(long *param_1,long *param_2,long p3)
 * Initializes a 0x50 ArrayBuffer (tag 0x57b7): fills type/stride metadata, allocates three
 * backing buffers, and invokes the element-init method; returns a (vtable, buffer) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_array_buffer_init(long *out, long *src, long p3)
{
    /* plVar2 = FUN_0036a908(0x50,0x57b7); *out = plVar2; lVar9 = *(p3+0x10); *plVar2 = lVar9;
     * lVar4 = *(lVar9 + -8); plVar2[1] = lVar4; uVar10 = *(lVar4+0x40); lVar3 = FUN_0036a908(uVar10,0x57b7);
     * plVar2[2] = lVar3; lVar3 = FUN_0036a908(uVar10,0x57b7); plVar2[3] = lVar3; lVar3 = FUN_0036a908(uVar10,0x57b7);
     * lVar5 = *param_2; plVar2[4] = lVar3; plVar2[5] = lVar5; lVar6 = *x20; plVar2[6] = lVar6;
     * pcVar7 = *(lVar4+0x10); bVar1 = *(lVar4+0x50); lVar8 = *(lVar4+0x48); plVar2[7]=lVar8; plVar2[8]=pcVar7;
     * plVar2[9]= ((lVar4+0x10)&0xffffffffffff | 0xe3ba000000000000);
     * (*pcVar7)(lVar3, lVar6 + ((bVar1+0x20)&~bVar1) + lVar8*lVar5, lVar9); return (lVar3, FUN_001e5de8) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e5de8   (est. sk_swift_array_buffer_release2)
 * Ghidra: void FUN_001e5de8(void)
 * Releases an ArrayBuffer: loads element type + stride, runs the obj-method release chain, and
 * frees the referenced values via thunk_FUN_00012568.
 * Confidence: medium.
 */
void sk_swift_array_buffer_release2(void)
{
    /* auVar11 = FUN_00351e20(); lVar7 = *auVar11._0_8_; lVar4 = *(lVar7+8); pcVar8 = *(lVar7+0x40);
     * uVar5 = *(lVar7+0x48); lVar1 = *(lVar7+0x30); uVar2 = *(lVar7+0x20); uVar3 = *(lVar7+0x10);
     * uVar6 = *(lVar7+0x18); lVar10 = *(lVar7+0x28) * *(lVar7+0x38);
     * if ((auVar11._8_8_&1)==0) { ...obj-method chain... } else { ... }
     * thunk_FUN_00012568(uVar2); thunk_FUN_00012568(uVar6); thunk_FUN_00012568(uVar3);
     * FUN_00351d30(lVar7,x30); thunk_FUN_00012568() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e5f4c / FUN_001e5f50   (est. sk_swift_dict_bucket_alloc) — alias pair
 * Ghidra: undefined1[16] FUN_001e5f4c(undefined8 p1,undefined8 p2,long p3)
 * Allocates a 0x40 dict bucket (tag 0xcbcd) via FUN_001e5464, fills key/value slots, and
 * returns a (vtable, bucket) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_dict_bucket_alloc(uint64_t p1, uint64_t p2, long p3)
{
    /* auVar4 = FUN_001e5464(); pauVar1 = FUN_0036a908(0x40,0xcbcd); *auVar4._0_8_ = pauVar1;
     * *(pauVar1[2]) = x20; *(pauVar1[2]+8) = p3; uVar2 = auVar4._8_8_[1]; *(pauVar1[3]) = *auVar4._8_8_;
     * *(pauVar1[3]+8) = uVar2; uVar2 = *x20; uVar3 = *(p3+0x10); auVar4 = FUN_0019ec24(); *pauVar1 = auVar4;
     * *(pauVar1[1]) = uVar2; *(pauVar1[1]+8) = uVar3; return (pauVar1, FUN_001e5538) */
    return 0;
}
uint64_t sk_swift_dict_bucket_alloc2(uint64_t p1, uint64_t p2, long p3)
{
    /* identical; return (pauVar1, FUN_001e5538) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e5fe4   (est. sk_swift_dictionary_bridge_convert)
 * Ghidra: void FUN_001e5fe4(undefined8 p1,...,undefined8 p5)
 * Converts via FUN_00376820(&DAT_004e8f80,p4) then FUN_0019f1ec.
 * Confidence: medium.
 */
void sk_swift_dictionary_bridge_convert(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                                        uint64_t p5)
{
    /* uVar1 = FUN_00376820(&DAT_004e8f80,p4); FUN_0019f1ec(p1,p2,p3,p4,uVar1,p5) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6064   (est. sk_swift_array_reserve_capacity)
 * Ghidra: void FUN_001e6064(undefined8 p1,undefined8 p2,long p3,undefined8 p4,undefined8 p5)
 * Swift array reserve-capacity: computes required capacity, reallocates the backing buffer via
 * FUN_0019c44c if needed, migrates elements, and publishes. Panics (0x411) on failure.
 * Confidence: medium.
 */
void sk_swift_array_reserve_capacity(uint64_t p1, uint64_t p2, long p3, uint64_t p4, uint64_t p5)
{
    sk_cpu_get();
    /* FUN_0034ee78; FUN_00310d68(0,p3); uVar1 = FUN_000a6f88(); FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034b0d4; FUN_00350bd8(p5); FUN_00349830; FUN_00377824(); FUN_00348d7c; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034af20; lVar9 = *x21; lVar8 = *(lVar9+0x10);
     * pcVar2 = FUN_00027788(p5); FUN_003504ac(); lVar3 = (*pcVar2)(); lVar4 = lVar8 + lVar3;
     * SCARRY8 -> SBP 0x1e6290; uVar6 = *(ulong*)(lVar9+0x18) >> 1;
     * if ((long)uVar6 < lVar4) { realloc path: SBP 0x1e638c on overflow; lVar4 = FUN_0019c44c(...);
     *   migrate elements; *(lVar9+0x10)=0; FUN_0036b118(lVar9); *x21 = lVar4; ... }
     * else { inline grow; *(lVar9+0x10) = lVar4; } */
    /* if (w28==1) { if (lVar4==lVar3) { return via FUN_0008e500; } FUN_00350410; FUN_003488bc; FUN_00349ee0; }
     * else { FUN_00348b7c(0x411); FUN_00349ee0; } FUN_00351a8c(); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e638c   (est. sk_sched_yield)
 * Ghidra: void FUN_001e638c(long p1,long p2)
 * Overflow guard used by array helpers: SCARRY8 -> SBP 0x1e63c4; if (p1+p2) > 2 then
 * FUN_00348384(1) + FUN_001afe4c.
 * Confidence: medium.
 */
void sk_sched_yield(long p1, long p2)
{
    /* if (SCARRY8(p1,p2)) SoftwareBreakpoint(1,0x1e63c4); if (2 < (ulong)(p1+p2)) { FUN_00348384(1);
     *   FUN_001afe4c(); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001e63c4   (est. sk_swift_collection_bounds_check)
 * Ghidra: void FUN_001e63c4(long p1,long p2,uint p3)
 * Swift Collection bounds check: for a width from p3 (>=0x10000 checks <3 else <2), panics with
 * "Index out of bounds" (0x2d2) in module "Swift/Collection".
 * Confidence: high (string-matched).
 */
void sk_swift_collection_bounds_check(long p1, long p2, uint p3)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e6444;
     * if (p3 < 0x10000) { if ((ulong)(p1+p2) < 2) return; } else if ((ulong)(p1+p2) < 3) return;
     * FUN_001afe4c(s_Fatal_error,0xb,2,s_Index_out_of_bounds_005cdab0,0x13,2,s_Swift_Collection_005cdad0,0x16,2,0x2d2,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6444   (est. sk_swift_string_bounds_check2)
 * Ghidra: void FUN_001e6444(long p1,long p2,uint p3)
 * Swift string bounds check with UTF-8 width: (p1+p2) vs p3-derived width, panic "Index out of
 * bounds" (0x2d2) in "Swift/Collection".
 * Confidence: high (string-matched).
 */
void sk_swift_string_bounds_check2(long p1, long p2, uint p3)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e64ec; uVar1 = p1+p2; if (p3<0x80) { w=1; } else { if (0x7ff<p3) {
     *   if (p3>>0x10==0) { if (uVar1<4) return; } else if (uVar1<5) return; panic; } w=2; }
     * if (uVar1 <= w) return; FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2d2,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e64ec   (est. sk_swift_collection_bounds_check2)
 * Ghidra: void FUN_001e64ec(long p1,long p2)
 * Bounds check: (p1+p2) <= 2 else panic 0x2d2.
 * Confidence: high (string-matched).
 */
void sk_swift_collection_bounds_check2(long p1, long p2)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e655c; if (2 < (ulong)(p1+p2))
     *   FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2d2,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e655c   (est. sk_swift_collection_bounds_check3)
 * Ghidra: void FUN_001e655c(long p1,long p2)
 * Bounds check: (p1+p2) <= 1 else FUN_00348384(1) + FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_collection_bounds_check3(long p1, long p2)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e6594; if (1 < (ulong)(p1+p2)) { FUN_00348384(1); FUN_001afe4c(); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6594   (est. sk_swift_utf8_bounds_check)
 * Ghidra: void FUN_001e6594(long p1,long p2,undefined8 p3,ulong p4)
 * UTF-8 bounds check using the width from (p4>>0x38 & 0xf); panic 0x2d2.
 * Confidence: high (string-matched).
 */
void sk_swift_utf8_bounds_check(long p1, long p2, uint64_t p3, unsigned long p4)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e6608; if ((p4>>0x38 & 0xf) < (ulong)(p1+p2))
     *   FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2d2,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6608   (est. sk_swift_buffer_slice_bounds)
 * Ghidra: void FUN_001e6608(long p1,long p2,long p3,long p4)
 * Bounds check for a buffer slice: (p1+p2) must fit within [p3,p4) else FUN_00348384(1)+fatal.
 * Confidence: medium.
 */
void sk_swift_buffer_slice_bounds(long p1, long p2, long p3, long p4)
{
    /* if (SCARRY8(p1,p2)) SBP 0x1e664c; if (p3==0) { if (p1+p2==0) return; } else if
     *   ((ulong)(p1+p2) <= (ulong)(p4-p3)) return; FUN_00348384(1); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e664c   (est. sk_swift_string_from_utf8)
 * Ghidra: void FUN_001e664c(void)
 * Builds a Swift string from UTF-8: computes string length, runs the append/encode chain, and
 * publishes a result via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_string_from_utf8(void)
{
    sk_cpu_get();
    /* FUN_00350a28; FUN_00027754(in_x3); FUN_003514b8; FUN_00349748; FUN_00350768;
     * uVar1 = FUN_00377824(); FUN_0034ab20; (*DAT_00658c00)(x16+0x40); FUN_003489c0; (*DAT_00658c00)();
     * FUN_0034c2d8; uVar2 = FUN_003549c0(in_x4); FUN_0035050c; FUN_00310f04; FUN_000a6f88;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4; FUN_00354f4c(in_x4); FUN_00350b18(x8,&stack);
     * (*x9)(); FUN_0034fe64; FUN_00084174; (*x9_00)(); FUN_00310924; FUN_0035102c; FUN_00084174;
     * (*x9_01)(); auVar3 = FUN_00350c80(); FUN_001dffa0(auVar3._0_8_,auVar3._8_8_,uVar1,uVar2);
     * FUN_0031b2bc; FUN_00350804; FUN_00350c68; (*x8_00)(); (**x16_00+8)(); FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e67d8   (est. sk_swift_str_distance)
 * Ghidra: long FUN_001e67d8(long p1,long p2,uint p3)
 * Distance helper: computes p2-p1, stamping both with a width selected from p3; SBP 0x1e6864.
 * Confidence: medium.
 */
long sk_swift_str_distance(long p1, long p2, uint p3)
{
    /* uVar1 = (p3>0xffff) ? 2 : 1; FUN_001dff60(0,uVar1); FUN_0019fe7c(p1,...);
     * FUN_001dff60(0,uVar1); FUN_0019fe7c(p2,...); if (!SBORROW8(p2,p1)) return p2-p1;
     * SoftwareBreakpoint(1,0x1e6864) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e6864   (est. sk_swift_str_distance2)
 * Ghidra: long FUN_001e6864(long p1,long p2,uint p3)
 * Distance helper with width 1/2/3/4 selection from p3; SBP 0x1e6908.
 * Confidence: medium.
 */
long sk_swift_str_distance2(long p1, long p2, uint p3)
{
    /* uVar1 = 3; if (0xffff<p3) uVar1 = 4; uVar2 = 2; if (0x7ff<p3) uVar2 = uVar1; uVar1 = 1;
     * if (0x7f<p3) uVar1 = uVar2; FUN_001dff60(0,uVar1); FUN_0019fe7c(p1,...); FUN_001dff60(0,uVar1);
     * FUN_0019fe7c(p2,...); if (!SBORROW8(p2,p1)) return p2-p1; SoftwareBreakpoint(1,0x1e6908) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e6908   (est. sk_swift_str_distance3)
 * Ghidra: long FUN_001e6908(void)
 * Distance via stride callback (in_x4) twice; returns (x20-x21); SBP 0x1e695c.
 * Confidence: medium.
 */
long sk_swift_str_distance3(void)
{
    /* pcVar1 = in_x4; FUN_0035098c; FUN_00352b38; (*pcVar1)(); FUN_00352b38; (*in_x4)();
     * if (!SBORROW8(x20,x21)) return x20 - x21; SoftwareBreakpoint(1,0x1e695c) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e695c   (est. sk_swift_str_distance4)
 * Ghidra: long FUN_001e695c(long p1,long p2)
 * Distance stamping both with width 2; SBP 0x1e69a8.
 * Confidence: medium.
 */
long sk_swift_str_distance4(long p1, long p2)
{
    /* FUN_0019fe7c(p1,0,2); FUN_0019fe7c(p2,0,2); if (!SBORROW8(p2,p1)) return p2-p1;
     * SoftwareBreakpoint(1,0x1e69a8) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e69a8 / FUN_001e69f8 / FUN_001e6a48 / FUN_001e6b1c   (est. sk_swift_str_dist_cb_*) — alias group
 * Ghidra: long FUN_001e69a8(void) etc.
 * Distance via callback (in_x3) twice; returns (x20-x21); SBPs 0x1e69f8/0x1e6a48/0x1e6a98/0x1e6b6c.
 * Confidence: medium.
 */
long sk_swift_str_dist_cb_0(void)
{
    /* pcVar1 = in_x3; FUN_0034cbec; (*pcVar1)(); FUN_003509f8; (*in_x3)(); if (!SBORROW8(x20,x21))
     *   return x20-x21; SBP 0x1e69f8 */
    return 0;
}
long sk_swift_str_dist_cb_1(void)
{
    /* identical; SBP 0x1e6a48 */
    return 0;
}
long sk_swift_str_dist_cb_2(void)
{
    /* identical; SBP 0x1e6a98 */
    return 0;
}
long sk_swift_str_dist_cb_3(void)
{
    /* identical; SBP 0x1e6b6c */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e6a98   (est. sk_swift_str_distance_utf8)
 * Ghidra: long FUN_001e6a98(long p1,long p2,undefined8 p3,ulong p4)
 * Distance with UTF-8 width from (p4>>0x38 & 0xf); SBP 0x1e6b1c.
 * Confidence: medium.
 */
long sk_swift_str_distance_utf8(long p1, long p2, uint64_t p3, unsigned long p4)
{
    /* uVar2 = p4 >> 0x38 & 0xf; FUN_001dff60(0,uVar2); FUN_0019fe7c(p1,...); FUN_001dff60(0,uVar2);
     * FUN_0019fe7c(p2,...); if (!SBORROW8(p2,p1)) return p2-p1; SBP 0x1e6b1c */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e6b6c   (est. sk_swift_str_dist_checked_cb)
 * Ghidra: long FUN_001e6b6c(undefined8 p1,undefined8 p2,long p3,long p4,code* param_5)
 * Distance via callback with a (p4-p3) element-count transform; SBP 0x1e6be8.
 * Confidence: medium.
 */
long sk_swift_str_dist_checked_cb(uint64_t p1, uint64_t p2, long p3, long p4, void (*cb)(void))
{
    /* FUN_0035098c; FUN_00350488(p4-p3); FUN_001dff60; FUN_00351790; FUN_00351488; (*cb)();
     * FUN_00350488(); FUN_001dff60; FUN_00351790; FUN_00351488; (*cb)();
     * if (!SBORROW8(x20,x21)) return x20-x21; SBP 0x1e6be8 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e6be8   (est. sk_swift_string_from_utf8_repair)
 * Ghidra: void FUN_001e6be8(void)
 * Repairs a Swift UTF-8 string: locks, runs the append/encode chain with a replacement scalar,
 * and publishes via FUN_0035a560 + FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_string_from_utf8_repair(void)
{
    /* auVar7 = FUN_0008e518(); FUN_00027754(in_x3); FUN_00351bec; FUN_00349748; FUN_00350ad0;
     * uVar1 = FUN_00377824(); FUN_0034ab20; (*DAT_00658c00)(x16+0x40); FUN_00348a18; (*DAT_00658c00)();
     * FUN_0034b4c0; FUN_00352894(in_x4); FUN_00350530; uVar2 = FUN_00310f04(); FUN_000a6f88;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034bdfc; pcVar3 = FUN_0035156c(); FUN_003507c8; (*x9)();
     * pcVar4 = FUN_00310924(); FUN_003507c8; (*pcVar4)(); FUN_00350ab8(in_x4); FUN_00352d40; FUN_001dffa0;
     * pcVar5 = FUN_0031b2bc(); FUN_00350810(pcVar5,auVar7._0_8_); (*x8)(); pcVar6 = *(x16_00+8);
     * (*pcVar6)(in_x4,uVar2); FUN_003507c8; (*pcVar3)(); FUN_003507c8; (*pcVar4)(); auVar8 = FUN_00350ab8(in_x4);
     * FUN_001dffa0(auVar8._0_8_,auVar8._8_8_,uVar1,unaff_x24); FUN_0034c5fc; (*pcVar5)(); FUN_0035072c;
     * (*pcVar6)(); FUN_00319538(in_x4); FUN_00350c68(auStack_8,auVar7._8_8_); (*x9_00)();
     * uVar1 = FUN_0035a560(); FUN_0008e500(uVar1,in_stack_00000008) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6df0   (est. sk_swift_string_utf16_from_utf8)
 * Ghidra: void FUN_001e6df0(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-16-from-UTF-8: FUN_00376820(&DAT_004e8f64) then FUN_001e7038.
 * Confidence: medium.
 */
void sk_swift_string_utf16_from_utf8(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* uVar1 = FUN_00376820(&DAT_004e8f64); FUN_001e7038(p1,p2,p3,uVar1,0x6720e8) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6e60   (est. sk_swift_collection_last_index_check)
 * Ghidra: void FUN_001e6e60(long p1,uint p2)
 * Checks last-index bounds for a width from p2; panic 0x2ca in "Swift/Collection".
 * Confidence: high (string-matched).
 */
void sk_swift_collection_last_index_check(long p1, uint p2)
{
    /* if (SBORROW8(p1,1)) SBP 0x1e6edc;
     * if (p2 < 0x10000) { if (p1 == 1) return; } else if ((p1-1U) < 2) return;
     * FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2ca,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6edc   (est. sk_swift_string_last_index_check)
 * Ghidra: void FUN_001e6edc(long p1,uint p2)
 * String last-index check with UTF-8 width; panic 0x2ca.
 * Confidence: high (string-matched).
 */
void sk_swift_string_last_index_check(long p1, uint p2)
{
    /* if (SBORROW8(p1,1)) SBP 0x1e6f84; uVar1 = p1 - 1; if (p2<0x80) { w=1; } else { if (0x7ff<p2) {
     *   if (p2>>0x10==0) { if (uVar1<3) return; } else if (uVar1<4) return; panic; } w=2; }
     * if (uVar1 < w) return; FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2ca,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6f84   (est. sk_swift_utf8_last_index_check)
 * Ghidra: void FUN_001e6f84(long p1,undefined8 p2,ulong p3)
 * UTF-8 last-index check with width from (p3>>0x38 & 0xf); panic 0x2ca.
 * Confidence: high (string-matched).
 */
void sk_swift_utf8_last_index_check(long p1, uint64_t p2, unsigned long p3)
{
    /* if (SBORROW8(p1,1)) SBP 0x1e6ff8; if ((p3>>0x38 & 0xf) <= p1-1U)
     *   FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2ca,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e6ff8   (est. sk_swift_buffer_slice_last_check)
 * Ghidra: void FUN_001e6ff8(long p1,long p2,long p3)
 * Slice last-index check: (p1-1) vs (p3-p2); else FUN_00348384(1)+fatal.
 * Confidence: medium.
 */
void sk_swift_buffer_slice_last_check(long p1, long p2, long p3)
{
    /* if (SBORROW8(p1,1)) SBP 0x1e7038; if ((p2!=0) && (p1-1U < (ulong)(p3-p2))) return;
     * FUN_00348384(1); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e7038   (est. sk_swift_string_utf16_encode)
 * Ghidra: void FUN_001e7038(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * UTF-16 encode: locks, computes string length, runs the UTF-16 append/encode chain, publishes.
 * Confidence: medium.
 */
void sk_swift_string_utf16_encode(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_cpu_get();
    /* FUN_00027754(p3); FUN_003514b8; FUN_00349748; FUN_00350600; uVar1 = FUN_00377824(); FUN_0034ab20;
     * (*DAT_00658c00)(x16+0x40); FUN_003489c0; (*DAT_00658c00)(); FUN_0034c2d8; uVar2 = FUN_003549c0(p4);
     * FUN_0035050c; FUN_00310e08; FUN_000a6f88; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4; FUN_00354cf0;
     * FUN_00354f4c(p4); FUN_00350b18(x8,auStack_8); (*x9)(); FUN_0034fe64; FUN_0008e388; (*x9_00)();
     * FUN_00310924; FUN_0035102c; FUN_0008e388; (*x9_01)(); auVar3 = FUN_00350c80();
     * FUN_0026bdc4(auVar3._0_8_,auVar3._8_8_,uVar1,uVar2); uVar1 = FUN_0031b2ec(); FUN_003508fc(uVar1);
     * FUN_003513f0; (*x8_00)(); (**x16_00+8)(); FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e71f0   (est. sk_swift_string_utf8_append_call)
 * Ghidra: void FUN_001e71f0(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-8 append call: FUN_0034b5d0/FUN_00376820 then FUN_001e664c.
 * Confidence: medium.
 */
void sk_swift_string_utf8_append_call(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* FUN_00349ef4; uVar1 = FUN_0034b5d0(); FUN_00376820(uVar1,p3); FUN_003486fc; FUN_0034b128;
     * FUN_001e664c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e7238   (est. sk_swift_string_utf8_from_scalar)
 * Ghidra: void FUN_001e7238(void)
 * UTF-8 from a scalar: FUN_0034b5d0/FUN_00376820 then FUN_001e3a28.
 * Confidence: medium.
 */
void sk_swift_string_utf8_from_scalar(void)
{
    /* FUN_00349944; uVar1 = FUN_0034b5d0(); FUN_00376820(uVar1,in_x3); FUN_003498a8; FUN_001e3a28() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e727c   (est. sk_swift_string_utf8_from_tcb)
 * Ghidra: void FUN_001e727c(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-8 from a TCB string: sk_cpu_get, FUN_0034b5d0/FUN_00376820 then FUN_001e6be8.
 * Confidence: medium.
 */
void sk_swift_string_utf8_from_tcb(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* FUN_000867ec(); uVar1 = FUN_0034b5d0(); FUN_00376820(uVar1,p3); FUN_003486fc; FUN_0034b778;
     * FUN_001e6be8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e72bc   (est. sk_swift_string_utf16_create)
 * Ghidra: undefined * FUN_001e72bc(long *param_1,undefined8 *param_2,long p3)
 * Creates a UTF-16 string: allocates 0x28 (tag 0x365c), calls FUN_001e7334 for the metadata,
 * stores at +0x20, returns a vtable.
 * Confidence: medium.
 */
void *sk_swift_string_utf16_create(long *out, uint64_t *meta, long p3)
{
    /* lVar1 = FUN_0036a908(0x28,0x365c); *out = lVar1; uVar2 = FUN_001e7334(lVar1,*meta,*x20,*(p3+0x10));
     * *(lVar1+0x20) = uVar2; return &DAT_003471a4 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e7334   (est. sk_swift_string_utf16_storage)
 * Ghidra: undefined1[16] FUN_001e7334(undefined8 p1,long p2,long p3,long p4)
 * Computes UTF-16 storage: the element pointer at offset from the type metadata; returns
 * (FUN_0001a1c8, ptr).
 * Confidence: medium.
 */
uint64_t sk_swift_string_utf16_storage(uint64_t p1, long p2, long p3, long p4)
{
    /* uVar1 = *(byte*)(*(p4+-8)+0x50); return (FUN_0001a1c8, p3 + ((uVar1+0x20)&~uVar1) + *(*(p4+-8)+0x48)*p2) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e7390   (est. sk_swift_string_utf16_wrap)
 * Ghidra: void FUN_001e7390(undefined1 (*param_1)[16],undefined8 *param_2,long p3)
 * Wraps a UTF-16 buffer: FUN_0019ec24 then fills the native string word.
 * Confidence: medium.
 */
void sk_swift_string_utf16_wrap(uint8_t (*out)[16], uint64_t *src, long p3)
{
    /* uVar1 = *x20; uVar2 = *(p3+0x10); auVar3 = FUN_0019ec24(*src,src[1]); *out = auVar3;
     * *(out[1]) = uVar1; *(out[1]+8) = uVar2 */
}

/* ------------------------------------------------------------------ *
 * FUN_001e73d0   (est. sk_swift_string_utf8_from_utf16)
 * Ghidra: void FUN_001e73d0(undefined8 p1,undefined8 p2)
 * UTF-8 from UTF-16: FUN_00376820(&DAT_004e8f64,p2) then FUN_0019fa60.
 * Confidence: medium.
 */
void sk_swift_string_utf8_from_utf16(uint64_t p1, uint64_t p2)
{
    /* uVar1 = FUN_00376820(&DAT_004e8f64,p2); FUN_0019fa60(p1,p2,uVar1,0x6720e8) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e743c   (est. sk_swift_string_utf8_encode)
 * Ghidra: void FUN_001e743c(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-8 encode: FUN_00376820(&DAT_004e8f64) then FUN_001e7664.
 * Confidence: medium.
 */
void sk_swift_string_utf8_encode(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* uVar1 = FUN_00376820(&DAT_004e8f64); FUN_001e7664(p1,p2,p3,uVar1,0x6720e8) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e74ac   (est. sk_swift_collection_advance_index)
 * Ghidra: long FUN_001e74ac(ulong p1,uint p2)
 * Advances a collection index (p1+1) with bounds check by width from p2; panic 0x2ca.
 * Confidence: high (string-matched).
 */
long sk_swift_collection_advance_index(unsigned long p1, uint p2)
{
    /* if (p2 < 0x10000) { if (p1 == 0) return p1+1; } else if (p1 < 2) return p1+1;
     * FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2ca,1) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e7520   (est. sk_swift_string_advance_index)
 * Ghidra: long FUN_001e7520(ulong p1,uint p2)
 * Advances a UTF-8 string index with width selection; panic 0x2ca.
 * Confidence: high (string-matched).
 */
long sk_swift_string_advance_index(unsigned long p1, uint p2)
{
    /* if (p2<0x80) { w=1; } else { if (0x7ff<p2) { if (p2>>0x10!=0) { if (3<p1) panic; return p1+1; }
     *   if (p1<3) return p1+1; panic; } w=2; } if (p1<w) return p1+1; panic 0x2ca */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e75c0   (est. sk_swift_utf8_advance_index)
 * Ghidra: long FUN_001e75c0(ulong p1,undefined8 p2,ulong p3)
 * Advances a UTF-8 index with width from (p3>>0x38 & 0xf); panic 0x2ca.
 * Confidence: high (string-matched).
 */
long sk_swift_utf8_advance_index(unsigned long p1, uint64_t p2, unsigned long p3)
{
    /* if ((p3>>0x38 & 0xf) <= p1) FUN_001afe4c(...,s_Index_out_of_bounds,0x13,2,s_Swift_Collection,0x16,2,0x2ca,1);
     * return p1+1 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e762c   (est. sk_swift_buffer_advance_index)
 * Ghidra: long FUN_001e762c(ulong p1,long p2,long p3)
 * Advances a buffer index within [p2,p3); else fatal.
 * Confidence: medium.
 */
long sk_swift_buffer_advance_index(unsigned long p1, long p2, long p3)
{
    /* if ((p2!=0) && (p1 < (ulong)(p3-p2))) return p1+1; FUN_00348384(1); FUN_001afe4c() */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e7664   (est. sk_swift_string_utf8_encode2)
 * Ghidra: void FUN_001e7664(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * UTF-8 encode (full): locks, computes string length, encodes via FUN_0026bdc4, publishes a
 * completion flag via FUN_003508d8 and returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_string_utf8_encode2(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_cpu_get();
    /* FUN_00027754(p3); FUN_00351bec; FUN_00349748; FUN_00350ad0; FUN_00377824(); FUN_0034ab20;
     * (*DAT_00658c00)(x16+0x40); FUN_003489c0; (*DAT_00658c00)(); FUN_0034c2d8; FUN_00350950(p4);
     * FUN_0034e0c4; FUN_00310e08; FUN_00348e60; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034bdfc;
     * FUN_000277b8; FUN_00351250; FUN_003507c8; (*x9)(); FUN_00310924; FUN_0035102c; FUN_003507c8;
     * (*x9_00)(); FUN_00350c80(p4); FUN_003528ac; FUN_0026bdc4(); uVar1 = FUN_0031b2ec(); FUN_0034ca28(uVar1);
     * (*x8_00)(); FUN_003508fc(*(x16_00+8)); (*x8_01)(); local_8 = 1; FUN_00354f4c(p4);
     * FUN_003508d8(x8,&local_8); (*x9_01)(); FUN_0008e500(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e7818   (est. sk_swift_string_utf8_last)
 * Ghidra: void FUN_001e7818(undefined8 p1)
 * UTF-8 last scalar: FUN_00376820(&DAT_004e8f9c,p1) then FUN_001a0194.
 * Confidence: medium.
 */
void sk_swift_string_utf8_last(uint64_t p1)
{
    /* uVar1 = FUN_00376820(&DAT_004e8f9c,p1); FUN_001a0194(p1,uVar1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e7878   (est. sk_swift_optional_bind)
 * Ghidra: undefined8 FUN_001e7878(undefined8 p1,...,code* param_6)
 * Binds an optional: runs the callback and stores its result into the out-slot; returns p3.
 * Confidence: medium.
 */
uint64_t sk_swift_optional_bind(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5,
                                uint64_t (*cb)(void))
{
    /* FUN_0035776c(); auVar1 = (*cb)(); *unaff_x19 = auVar1; return p3 */
    return p3;
}

/* ------------------------------------------------------------------ *
 * FUN_001e78a8 @ 0x001e78a8   (est. sk_swift_string_split)
 * Ghidra: undefined * FUN_001e78a8(ulong *param_1)
 * Swift String.split(separator:) — splits a string on newline/CR/8-bit set separators, using
 * Swift UTF8/UTF16/UnicodeScalar iteration, growing a result array of substrings. Panics with
 * module strings "Swift/ContiguousArrayBuffer" (0x005cd960), "Swift/Range" (0x005cda30),
 * "Swift/UnsafeBufferPointer" (0x005cdc10), "Swift/Optional" (0x005ce1f0) on errors.
 * Confidence: high (string-matched Swift String.split machinery).
 */
void *sk_swift_string_split(unsigned long *param_1)
{
    /* lVar11 = FUN_002e4358(); // separator length
     * if (lVar11==0) puVar13 = &DAT_00657778; else { build native storage of lVar11*0x18+0x20 (tag 7),
     *   copy separator; }
     * uVar29 = *(puVar13+0x18); ... iterate the input string (param_1), scanning for separator
     *   (newline 0xa0d / 0x8080), computing substring ranges, and appending each split substring
     *   as (offset,length,bits) 3-word records into a growing array; grow via FUN_00117d14 memcpy. */
    /* On nil/range error panics with s_Unexpectedly_found_nil_while_unw_005cd7d0 / 0x441,
     *   s_unsafelyUnwrapped_of_nil_optiona_005ce1c0 / 0x179, s_UnsafeBufferPointer_* , s_Index_out_of_range,
     *   s_Range_requires_lowerBound_<__upp_005cda00 / 0x2f9 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e8374   (est. sk_swift_string_split_codepoints)
 * Ghidra: undefined * FUN_001e8374(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Swift scalar-splitting variant: iterates Unicode scalars via FUN_00263360/FUN_00264068 and
 * appends code points to a result array of Ints (element size 4). Panics on nil (0x584 / 0x35)
 * in "Swift/UnsafeBufferPointer".
 * Confidence: high (string-matched).
 */
void *sk_swift_string_split_codepoints(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    /* local_80[0]=1; local_78=&DAT_00657778; local_6c=0x1000000000000;
     * while (true) { uVar5 = FUN_00263360(&local_80,&local_a8); if ((uVar5&0xff000000000000)==0x1000000000000 &&
     *   (uVar5 = FUN_00264068(), (uVar5&0xff000000000000)==0x1000000000000)) { return puVar10; }
     *   ... grow Int array (elem size 4) via FUN_00117d14, append (int)uVar5 ... }
     * panics: s_unsafelyUnwrapped / 0x584 / 0x35 (s_UnsafeBufferPointer_has_a_nil_st_005cf020) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e851c   (est. sk_swift_string_split_scalars)
 * Ghidra: undefined * FUN_001e851c(undefined8 p1,undefined8 p2,ulong p3,ulong p4)
 * Swift scalar split: iterates Unicode scalars (FUN_00263e20/FUN_00262e9c/FUN_0026398c),
 * maintaining a small stack of pending scalars, building a result Int array. Panics with
 * "Swift/ContiguousArrayBuffer", "Swift/Array", "Swift/RangeReplaceableCollection" strings.
 * Confidence: high (string-matched).
 */
void *sk_swift_string_split_scalars(uint64_t p1, uint64_t p2, unsigned long p3, unsigned long p4)
{
    /* uVar9 = p3; if ((p4&0x2000000000000000)!=0) uVar9 = p4; // inline string fast path
     * local_9e = (uVar9>>0x3e)&1; ... do { (*DAT_00658c00)(); if (pending==1) {...} else { decode scalar;
     *   if valid scalar -> push into local stack; pop via FUN_0019e644 into result array; ...}
     *   ... grow the result Int array ... } while (true);
     * panics: s_Can_t_remove_last_element_from_a_005d03a0 / 0x32, s_Can_t_removeLast_from_an_empty_A_005cdc70 / 0x24,
     *   s_Index_out_of_range, s_UnsafeBufferPointer */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e8980   (est. sk_swift_uint_to_string)
 * Ghidra: undefined * FUN_001e8980(uint param_1)
 * Converts an unsigned int to a decimal string: emits least-significant digit-first bytes into a
 * growing byte array (elem size 1), then reverses via the standard (param_1>>8) loop. Returns
 * the native String storage.
 * Confidence: medium.
 */
void *sk_swift_uint_to_string(uint param_1)
{
    /* puVar5 = &DAT_00657778; if (param_1 != 0) { do { grow byte array; *pcVar10 = (char)param_1 - 1;
     *   param_1 >>= 8; } while (param_1 > 0xff); } trim; return puVar5 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e8ac8   (est. sk_swift_bits_to_string)
 * Ghidra: undefined * FUN_001e8ac8(ulong *param_1,long param_2)
 * Converts a bitset (array of words, param_2 entries) into a compact index string: for each set
 * bit (via the bit-twiddle reverse/popcount idiom) emits a (index<<6 | bitpos) record into a
 * growing array of 8-byte entries. Panics on nil/range.
 * Confidence: medium.
 */
void *sk_swift_bits_to_string(unsigned long *param_1, long param_2)
{
    /* uVar4 = FUN_001b5564(); puVar6 = &DAT_00657778; ... for each word, reverse bits and clear
     *   lowest set bit (uVar15 = uVar15 - 1 & uVar15); grow array; *puVar14 = LZCOUNT(uVar10) | lVar7<<6;
     *   ... panics s_Range_requires_lowerBound (0x2f9), s_Unexpectedly_found_nil (0x441) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e8e18   (est. sk_swift_bitset_indices)
 * Ghidra: undefined * FUN_001e8e18(ulong param_1)
 * Computes the sorted list of set-bit indices of a 64-bit value: counts bits via POPCOUNT,
 * allocates an index array, emits LZCOUNT of each reversed bit. Returns the array.
 * Confidence: medium.
 */
void *sk_swift_bitset_indices(unsigned long param_1)
{
    /* cVar15..cVar21 = POPCOUNT of each byte; lVar9 = total popcount;
     * if (param_1==0) puVar6=&DAT_00657778; else { alloc lVar9*8+0x20; copy; }
     * for each set bit: uVar12 = param_1 - 1 & param_1; uVar10 = reverse-bits(param_1);
     *   *plVar13 = LZCOUNT(uVar10 >> 0x20 | uVar10 << 0x20); ... grow ... */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e90a0   (est. sk_swift_bitset_prefix)
 * Ghidra: undefined * FUN_001e90a0(ulong *param_1,long param_2)
 * Computes the set-bit indices of the low (param_2+1) bits of the first word of a bitset array;
 * grows an index array. Panics on nil.
 * Confidence: medium.
 */
void *sk_swift_bitset_prefix(unsigned long *param_1, long param_2)
{
    /* lVar15 = 0; uVar16 = ~(-1L << ((param_2+1) & 0x3f)); uVar16 = *param_1 & uVar16;
     * for each set bit: reverse; grow array; *puVar13 = LZCOUNT(uVar8) | lVar15<<6;
     *   ... until (param_2+0x40U>>6) entries or uVar16==0 ... */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e9264   (est. sk_swift_byte_buffer_to_string)
 * Ghidra: undefined * FUN_001e9264(undefined1 *param_1,undefined1 *param_2)
 * Builds a byte string from [param_1,param_2): grows a byte array appending each byte.
 * Panics on nil.
 * Confidence: medium.
 */
void *sk_swift_byte_buffer_to_string(uint8_t *begin, uint8_t *end)
{
    /* puVar9 = &DAT_00657778; if (begin != NULL) { if (end == NULL) panic 0x4f9; for (; begin!=end;
     *   ++begin) { if (end <= begin) panic 0x4fc; grow; *puVar12 = *begin; } } trim; return puVar9 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e9414 @ 0x001e9414   (est. sk_swift_array_map_convert)
 * Ghidra: void FUN_001e9414(undefined8 p1,undefined8 p2,undefined8 p3)
 * Array map/convert: double lock, computes the input array length, allocates the output buffer,
 * and maps each element through a converter, growing the output. Returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_array_map_convert(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_get();
    /* FUN_00356900; FUN_00350a64; FUN_003529b0; FUN_00377824(); FUN_00348e18; (*DAT_00658c00)(x8+0x40);
     * FUN_003489c0; (*DAT_00658c00)(); FUN_0034bc80; FUN_003504e8; FUN_00310d68; FUN_00348d64;
     * (*DAT_00658c00)(x8_00+0x40); FUN_00348b5c; (*DAT_00658c00)(); FUN_0034c2d8; FUN_0034a5c8;
     * (*DAT_00658c00)(x8_01+0x40); FUN_003497b4; FUN_0034d404; uVar3 = FUN_00377824(); FUN_000a6f88;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428; FUN_003531b4; FUN_00354f34;
     * lVar4 = (*x8_04)(); if (lVar4==0) puVar5=&DAT_00657778; else { FUN_00357970(lVar4); puVar5 = FUN_0019c44c(); }
     * bVar1 = *(x16+0x50); uVar12 = *(puVar5+0x18); (**x16_00+0x10)(x8_02,x20); FUN_00352680(p3);
     * FUN_00351360(x8_03); (*x9)(); if (lVar4<0) panic; uVar10 = ((bVar1+0x20)&~bVar1);
     * uVar12 >>= 1; puVar8 = puVar5 + uVar10; ... loop mapping elements (FUN_00358ec4 / convert) ... */
    /* on overflow/error -> FUN_00350410/FUN_00348898/FUN_00349ee0/FUN_00351a8c/FUN_001afe4c */
}

/* ------------------------------------------------------------------ *
 * FUN_001e98c4   (est. sk_swift_array_buffer_reserve)
 * Ghidra: undefined1[16] FUN_001e98c4(long p1,long p2)
 * Reserves an array buffer of capacity p1: allocates via FUN_0019c44c (or empty if p1==0),
 * returns (buffer, data-ptr) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_array_buffer_reserve(long p1, long p2)
{
    /* if (p1==0) { FUN_000a6fe0(); } else { x19 = FUN_0019c44c(p1,0,p2); } FUN_0036b270(x19);
     * uVar1 = *(byte*)(*(p2+-8)+0x50); FUN_0036b118();
     * return (x19, x19 + ((uVar1+0x20)&~uVar1)) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001e9940   (est. sk_swift_array_pop_back)
 * Ghidra: void FUN_001e9940(undefined8 p1,long p2)
 * Pops the last element of an array: decrements the count, invokes the element-init method, and
 * advances the data pointer by stride. SBP 0x1e9a14 on underflow.
 * Confidence: medium.
 */
void sk_swift_array_pop_back(uint64_t p1, long p2)
{
    /* uVar2 = *(p2+0x10); FUN_003499b4(p1); (*DAT_00658c00)(); FUN_0034d3b4();
     * if (!SBORROW8(*(x20+0x10),1)) { *(x20+0x10) -= 1; lVar3 = *(x20+8);
     *   (**x16+0x10)(x9-x10, x8, uVar2); FUN_0034db38(*(x16+0x20)); (*x8_00)(); *(x20+8) = lVar3 + *(x16+0x48); return; }
     * SoftwareBreakpoint(1,0x1e9a14) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9a14   (est. sk_swift_array_remove_last)
 * Ghidra: void FUN_001e9a14(void)
 * Swift array removeLast: if the backing buffer has no spare capacity it grows it (FUN_0019c44c),
 * then decrements count and releases the last element. Returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_array_remove_last(void)
{
    sk_cpu_get();
    /* uVar7 = *(x1+0x10); FUN_00349734; (*DAT_00658c00)(x8+0x40); FUN_00348f38; lVar9 = x20[2];
     * if (lVar9==0) { lVar8 = *x20; if overflow panic; uVar6 = *(lVar8+0x18)&~1; if (uVar6==0) uVar6=1;
     *   lVar2 = FUN_0019c44c(uVar6,0,uVar7); lVar3 = FUN_00357c20(*(x16+0x50)); x20[1] = lVar3 + x8_00 +
     *     (*(ulong*)(lVar8+0x18)>>1) * *(x16+0x48); lVar9 = (*(ulong*)(lVar3+0x18)>>1) - (*(ulong*)(lVar8+0x18)>>1);
     *   x20[2] = lVar9; ... migrate elements ...; FUN_0036b118(lVar8); *x20 = lVar2; }
     * if (!SBORROW8(lVar9,1)) { x20[2] = lVar9-1; lVar9 = x20[1]; FUN_0034c26c(x16); (*x9)();
     *   FUN_003510a0(*(x16+0x20),lVar9); (*x8_01)(); x20[1] = lVar9 + *(x16+0x48); FUN_0008e500(x30); return; }
     * SoftwareBreakpoint(1,0x1e9b9c) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9c00   (est. sk_swift_strtod_parse)
 * Ghidra: void FUN_001e9c00(void)
 * Parses a double from a string: thunk_FUN_00115080 (string length), FUN_002a218c (parsing),
 * and on the sign bit runs FUN_002a2698 / FUN_002a2748.
 * Confidence: medium.
 */
void sk_swift_strtod_parse(void)
{
    /* thunk_FUN_00115080(); if (extraout_var < 0) { FUN_0034846c(); FUN_001afe4c(); } FUN_0009461c();
     * lVar1 = FUN_002a218c(); if (-1 < lVar1) { FUN_0009461c((uint)lVar1, x1, (uint)lVar1 & 1);
     *   thunk_FUN_002a2698(); return; } FUN_00353b4c(); FUN_0009461c(); FUN_00352578(); FUN_002a2748() */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9c78   (est. sk_swift_strtod_parse2)
 * Ghidra: void FUN_001e9c78(void)
 * Parsing variant returning a (value, ok) pair via FUN_002a218c/FUN_002a2748/FUN_002a2698.
 * Confidence: medium.
 */
void sk_swift_strtod_parse2(void)
{
    /* FUN_0035098c; auVar1 = FUN_002a218c(); if (auVar1._0_8_ < 0) { FUN_00353b4c(); FUN_000b43d0();
     *   FUN_00352578(); FUN_002a2748(); } else { FUN_000b43d0(auVar1._0_8_,auVar1._8_8_,auVar1._0_4_&1);
     *   thunk_FUN_002a2698(); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9cd0   (est. sk_swift_string_is_ascii)
 * Ghidra: void FUN_001e9cd0(ulong p1,ulong p2,undefined8 p3,code* param_4)
 * Checks whether a Swift string is ASCII: inspects the first byte (inline fast path or callback),
 * and if the first scalar is not a low ASCII value runs FUN_002a43e0. Publishes via FUN_0035396c.
 * Confidence: medium.
 */
void sk_swift_string_is_ascii(unsigned long p1, unsigned long p2, uint64_t p3, void (*cb)(void))
{
    /* puVar2 = &local_30; if ((p2>>0x3c&1)==0) { ...decode first scalar... } else { uVar4 = FUN_002a43e0(); }
     * FUN_0035396c(uVar4) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9d8c   (est. sk_swift_string_utf8_validate)
 * Ghidra: void FUN_001e9d8c(undefined8 p1,undefined8 p2,ulong p3,ulong p4)
 * Validates/repairs a UTF-8 string: fast path for inline/native strings, slow path decodes each
 * scalar, and runs the repair chain (FUN_00291d70). Returns via FUN_00358fc8.
 * Confidence: medium.
 */
void sk_swift_string_utf8_validate(uint64_t p1, uint64_t p2, unsigned long p3, unsigned long p4)
{
    /* FUN_00358fb4; FUN_003585f4; FUN_00355bdc; if (((p4>>0x3c&1)==0) && ((p4&0x2000000000000000)!=0 ||
     *   (p3&0x1000000000000000)!=0)) { ...fast path... FUN_00355c94; FUN_003519e8; ... FUN_00291d70(); }
     *   else { FUN_00350470(x8); FUN_002a4468(); } FUN_00358fc8(x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001e9f14   (est. sk_swift_uint64_to_string)
 * Ghidra: void FUN_001e9f14(void)
 * Converts a 64-bit unsigned value to decimal: handles 0, <0x10 (single digit), and larger via
 * FUN_002a4b90. Returns via FUN_00354f64.
 * Confidence: medium.
 */
void sk_swift_uint64_to_string(void)
{
    /* uVar3 = thunk_FUN_00115080(); if ((long)uVar3 < 0) { FUN_0034846c(); FUN_001afe4c(); }
     * FUN_0007c1c4(); lVar4 = FUN_002a218c(); if (lVar4 < 0) FUN_00019858(); else if (uVar3==0)
     *   FUN_0011e71c(); else if (uVar3<0x10) { single-digit decode via FUN_00356134; FUN_00354f64(uVar3|uVar5); }
     *   else { auVar6 = FUN_0007c1c4(); FUN_002a4b90(...); FUN_00355c10(); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001ea018   (est. sk_swift_strtod_parse3)
 * Ghidra: void FUN_001ea018(void)
 * Parse variant: FUN_003504d0 + FUN_002a218c; on success FUN_0034f9fc + thunk_FUN_002a2698.
 * Confidence: medium.
 */
void sk_swift_strtod_parse3(void)
{
    /* FUN_003504d0(); lVar1 = FUN_002a218c(); if (lVar1 < 0) FUN_00019858(); else { FUN_0034f9fc();
     *   thunk_FUN_002a2698(); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001ea050   (est. sk_swift_cstring_to_string)
 * Ghidra: undefined8 FUN_001ea050(short *param_1,undefined8 p2,uint p3)
 * Builds a Swift string from a null-terminated UTF-16 (short) C string: walks to the NUL,
 * then FUN_001eafa8 to convert. Returns the string or 0.
 * Confidence: medium.
 */
uint64_t sk_swift_cstring_to_string(short *s, uint64_t p2, uint p3)
{
    /* if (s != NULL) { walk to NUL; auVar4 = FUN_001eafa8(s, len/2, p2, p3&1); if (auVar4._8_8_!=0)
     *   return auVar4._0_8_; } return 0 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ea118   (est. sk_swift_cstring_to_string8)
 * Ghidra: undefined8 FUN_001ea118(long p1,undefined8 p2,ulong p3)
 * Builds a string from an 8-bit C string: FUN_002a218c length, then converts via FUN_002a2698 /
 * FUN_002a2748. Returns the string or 0.
 * Confidence: medium.
 */
uint64_t sk_swift_cstring_to_string8(long p1, uint64_t p2, unsigned long p3)
{
    /* if (p1 != 0) { lVar1 = thunk_FUN_00115080(); if (lVar1 < 0) panic 0x582; auVar4 = FUN_002a218c(p1,lVar1);
     *   if ((p3&1)!=0) { if (-1 < auVar4._0_8_) return thunk_FUN_002a2698(p1,lVar1,auVar4._0_4_&1);
     *     return FUN_002a2748(p1,lVar1,auVar4._8_8_,uVar3); } if (-1 < auVar4._0_8_)
     *   return thunk_FUN_002a2698(p1,lVar1,auVar4._0_4_&1); } return 0 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ea218 @ 0x001ea218   (est. sk_swift_string_init_from_cstring)
 * Ghidra: void FUN_001ea218(undefined8 p1,undefined8 p2,ulong p3,undefined8 p4)
 * Full Swift String.init(cString:) initializer: locks, dispatches on the metadata tag at
 * (x23) (0x6768d0 -> 8-bit path via FUN_001ea118; NULL -> empty via FUN_00019858; else the
 * generic CString path which decodes UTF-8, validating against a 0x40/0x41 split, growing the
 * output). Returns via FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_string_init_from_cstring(uint64_t p1, uint64_t p2, unsigned long p3, uint64_t p4)
{
    sk_cpu_get();
    /* auVar16 = FUN_00352ce0(); lVar5 = auVar16._8_8_; pcVar2 = auVar16._0_8_; auVar16 = FUN_00351930();
     * uVar4 = FUN_00377824(auVar16._0_8_,auVar16._8_8_,p4,&DAT_00612b58); FUN_000e15d8; FUN_0035053c;
     * FUN_00377bec; FUN_00350780; FUN_0034be54; auVar16 = FUN_00349dfc(); FUN_00377824(...); FUN_0034ab20;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b6e0; FUN_00350798; FUN_00377dcc; FUN_000a6f88;
     * (*DAT_00658c00)(x8+0x40); FUN_00349db0; (*DAT_00658c00)(); FUN_0034b3d8; auVar17 = FUN_00354040();
     * uVar15 = (uint)p3; if (x23 == x8_00) { FUN_003516e4(auVar17._0_8_,auVar17._8_8_,uVar15&1);
     *   auVar16 = FUN_001ea118(); } else if (x23 == 0x6768d0) { auVar16 = FUN_001ea050(pcVar2,lVar5,uVar15&1); }
     *   else if (pcVar2==0) { auVar16 = FUN_00019858(); } else if (lVar5 != x8_00) { ...UTF-8 decode loop
     *   via FUN_00310a14/FUN_00310a74, FUN_00365b6c count, append each scalar... } else { ... }
     * FUN_0008e500(auVar16._0_8_,auVar16._8_8_) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ea880   (est. sk_swift_string_utf8_append_impl)
 * Ghidra: void FUN_001ea880(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-8 append impl: dispatches via an unrecovered jumptable after FUN_00310fc4.
 * Confidence: low (unrecovered jumptable).
 */
void sk_swift_string_utf8_append_impl(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* uVar1 = FUN_00350980(); FUN_00310f94(p3); FUN_0034c404(); (*x8_00)(); FUN_00353528();
     * UNRECOVERED_JUMPTABLE = FUN_00310fc4(); FUN_00077894(x8,uVar1); (*UNRECOVERED_JUMPTABLE)() */
}

/* ------------------------------------------------------------------ *
 * thunk_FUN_002a2f60 @ 0x001ead30   (est. sk_swift_unicode_escape)
 * Ghidra: void thunk_FUN_002a2f60(void)
 * Unicode scalar escape-encoding: iterates the scalar array (from auVar13._0_8_+0x20), and for
 * each valid scalar appends its UTF-8 (or the replacement 0xbec0f0) bytes to an output buffer,
 * growing it via FUN_001a0870. Finalizes via FUN_0006b6f4.
 * Confidence: medium.
 */
void sk_swift_unicode_escape(void)
{
    /* auVar13 = FUN_0008e518(); lVar8 = *(auVar13._0_8_+0x10); uVar6 = FUN_0034fdf8();
     * lVar7 = FUN_001a0870(uVar6,lVar8,0); for each scalar (uVar11) { if valid scalar:
     *   compute UTF-8 width uVar12; append bytes; else append 0xbec0f0; }
     * if (!(auVar13._8_8_&1) && bVar4) { FUN_0036b118(lVar7); FUN_003557c8(); }
     * else { FUN_00353724; FUN_00359244; FUN_00356164(lVar7+0x20); thunk_FUN_002a2698(); ... }
     * FUN_0006b6f4(); FUN_0008e500() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ead34   (est. sk_swift_string_utf16_is_ascii)
 * Ghidra: void FUN_001ead34(long p1,undefined8 p2,uint p3)
 * Checks a UTF-16 string (param_1) for ASCII: FUN_002a200c on the data; if ASCII uses
 * FUN_002a3268 else FUN_002a20cc.
 * Confidence: medium.
 */
void sk_swift_string_utf16_is_ascii(long p1, uint64_t p2, uint p3)
{
    /* uVar2 = *(p1+0x10); uVar1 = FUN_002a200c(p1+0x20,uVar2); if ((uVar1&1)==0) FUN_002a3268(p1,p3&1);
     *   else FUN_002a20cc(p1+0x20,uVar2) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ead94   (est. sk_swift_string_utf16_from_cstring)
 * Ghidra: void FUN_001ead94(long p1,long p2,undefined8 p3,uint p4)
 * UTF-16 string from a C buffer: validates [p1,p1+p2), computes bounds via FUN_001e4cbc, and
 * converts via FUN_002a3134 / FUN_002a20cc.
 * Confidence: medium.
 */
void sk_swift_string_utf16_from_cstring(long p1, long p2, uint64_t p3, uint p4)
{
    /* if (p2 < 0) panic 0x4c1 (s_UnsafeRawBufferPointer_with_nega_005cdef0); if (p2==0) { if (p1==0) {0,0}
     *   } else if (p1==0) panic 0x4c2 (nil); lVar6 = p2+p1; lVar3 = p1; auVar7 = FUN_001e4cbc(lVar3, lVar6-p1);
     *   uVar2 = FUN_002a200c(); if ((uVar2&1)==0) FUN_002a3134(p1,p2,p4&1); else FUN_002a20cc(auVar7._0_8_,auVar7._8_8_) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eaec4   (est. sk_swift_string_utf16_init)
 * Ghidra: void FUN_001eaec4(undefined8 p1,undefined8 p2,uint p3)
 * UTF-16 string init: registers three type metadata words then FUN_002a339c(p1,p2,p3&1).
 * Confidence: medium.
 */
void sk_swift_string_utf16_init(uint64_t p1, uint64_t p2, uint p3)
{
    /* FUN_00002534(&LAB_00657698,&DAT_004f2180); FUN_00002534(0x64e020,&DAT_004e4750);
     * FUN_00002534(0x64e078,&DAT_005a4b80); FUN_002a339c(p1,p2,p3&1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eafa8   (est. sk_swift_cstring_to_string_dispatch)
 * Ghidra: void FUN_001eafa8(undefined8 p1,undefined8 p2,long p3,uint p4)
 * Dispatches C-string conversion by type metadata tag: if p3 == 0x6726a8 and the metadata
 * matches &DAT_004f2180 uses FUN_001ead94; if it matches &DAT_005a4b80 uses FUN_001ead34; else
 * FUN_002a339c.
 * Confidence: medium.
 */
void sk_swift_cstring_to_string_dispatch(uint64_t p1, uint64_t p2, long p3, uint p4)
{
    /* lVar1 = FUN_00002534(&LAB_00657698,&DAT_004f2180); lVar2 = FUN_00002534(0x64e020,&DAT_004e4750);
     * if (lVar1==lVar2 && p3==0x6726a8) FUN_001ead94(p1,p2,0x6726a8,p4&1); else {
     *   lVar2 = FUN_00002534(0x64e078,&DAT_005a4b80); if (lVar1==lVar2 && p3==0x6726a8)
     *     FUN_001ead34(p1,0x6726a8,p4&1); else FUN_002a339c(p1,p2,p4&1); } */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb088 @ 0x001eb088   (est. sk_swift_string_bridge_objc)
 * Ghidra: void FUN_001eb088(undefined8 p1,...,undefined8 p7)
 * Bridges a Swift string to/from an Objective-C (NSString) object: dispatches on the metadata
 * tag; for the native path converts via FUN_001ead94/FUN_001ead34; for the CF path builds an
 * NSString through the obj-method chain and returns it.
 * Confidence: medium.
 */
void sk_swift_string_bridge_objc(uint64_t p1, uint64_t p2, uint64_t *p3, uint64_t p4, uint64_t p5,
                                 uint64_t p6, uint64_t p7)
{
    sk_cpu_get();
    /* local_60 = p6; FUN_00356c84; puVar4 = p3; FUN_00356c78; FUN_00349a68; (*DAT_00658c00)(x8+0x40);
     * FUN_003489c0; (*DAT_00658c00)(); FUN_00358248; lVar1 = FUN_0035a94c();
     * if (x24 == lVar1 && x23 == 0x6726a8) { FUN_001ead94(*x26, x26[1]); } else {
     *   local_64 = (uint)p3; lVar1 = FUN_00002534(0x64e078,&DAT_005a4b80);
     *   if (x24 == lVar1 && x23 == 0x6726a8) { x19 = (void*)(local_64&1); FUN_001ead34(*x26); }
     *   else if (x19 == (void*)0x6726a8) { ...build NSString via obj-method chain (FUN_00365b6c layout
     *     check, FUN_00358cf8, FUN_002a3d9c/FUN_002a3d30, FUN_001de8a8)... }
     *   else { FUN_00352ae4(); FUN_002a376c(); x19 = puVar4; } }
     * auVar6 = FUN_0009461c(); FUN_0008e500(auVar6._0_8_,auVar6._8_8_,x19,x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb460   (est. sk_swift_string_append_meta)
 * Ghidra: void FUN_001eb460(long p1,...,undefined8 p8)
 * String-append meta: if p1 == 0x676518 runs FUN_00352578(FUN_0031b4cc) + FUN_001e9d8c, else
 * FUN_0029b1e0.
 * Confidence: medium.
 */
void sk_swift_string_append_meta(long p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5,
                                 uint64_t p6, uint64_t p7, uint64_t p8)
{
    /* if (p1 == 0x676518) { (*DAT_00658c00)(); local_50 = p6; uStack_48 = p7; local_40 = p8;
     *   uStack_38 = x1; local_30 = p3; FUN_00352578(FUN_0031b4cc,auStack_60); FUN_001e9d8c(); }
     *   else FUN_0029b1e0() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb4f0   (est. sk_swift_string_init_cstring_dispatch)
 * Ghidra: void FUN_001eb4f0(short *param_1,long p2,undefined8 p3)
 * String.init(cString:) dispatch: if p2==0x676518 converts via FUN_002a218c/FUN_002a2698/
 * FUN_002a2748; else walks the UTF-16 C string and calls FUN_001eafa8. Panics on nil (0x1e3,
 * "Swift/CString").
 * Confidence: high (string-matched Swift/CString).
 */
void sk_swift_string_init_cstring_dispatch(short *s, long p2, uint64_t p3)
{
    /* if (p2 == 0x676518) { if (s != NULL) { lVar3 = thunk_FUN_00115080(s); if (-1 < lVar3) {
     *     auVar5 = FUN_002a218c(s,lVar3); if (auVar5._0_8_ < 0) { FUN_002a2748(s,lVar3,auVar5._8_8_,p3); return; }
     *     thunk_FUN_002a2698(s,lVar3,auVar5._0_4_&1); return; } panic 0x582; } }
     *   else { walk to NUL; if (len < -1) panic 0x582; FUN_001eafa8(s, len/2, p2, 1); if (x1 != 0) return; }
     * FUN_001afe4c(...,s_Unexpectedly_found_nil_while_unw,0x39,2,s_Swift_CString_005cf0e0,0x13,2,0x1e3,1) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb674   (est. sk_swift_string_from_cstring8)
 * Ghidra: void FUN_001eb674(undefined8 p1,undefined8 p2,undefined8 p3)
 * Converts an 8-bit C string: FUN_002a218c then FUN_002a2698/FUN_002a2748.
 * Confidence: medium.
 */
void sk_swift_string_from_cstring8(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* lVar1 = thunk_FUN_00115080(); if (lVar1 < 0) panic 0x582; auVar2 = FUN_002a218c(p1,lVar1);
     * if (-1 < auVar2._0_8_) { thunk_FUN_002a2698(p1,lVar1,auVar2._0_4_&1); return; }
     * FUN_002a2748(p1,lVar1,auVar2._8_8_,p3) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb73c   (est. sk_swift_string_from_cstring_dispatch)
 * Ghidra: void FUN_001eb73c(undefined8 p1,undefined8 p2,long p3)
 * C-string conversion dispatch on the tag p3: if matching the current obj tag uses
 * FUN_001eb674; else if matching a second tag uses FUN_001ea218; else FUN_001eb4f0.
 * Confidence: medium.
 */
void sk_swift_string_from_cstring_dispatch(uint64_t p1, uint64_t p2, long p3)
{
    /* FUN_00354040(); bVar1 = (p3 == x8); if (bVar1) { FUN_001eb674(); return; }
     * auVar2 = FUN_00354fc0(); if (!bVar1) { FUN_001ea218(auVar2._0_8_,auVar2._8_8_,1); if (x1 != 0) return;
     *   FUN_003489dc(0x1e3); FUN_0034a2f8(); FUN_001afe4c(); } FUN_001eb4f0() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb7d4   (est. sk_swift_mangle_obfuscate)
 * Ghidra: void FUN_001eb7d4(void)
 * XOR-obfuscates a string against a key byte (s_uespemosmodnarodarenegylsetybdet_004e7a30 =
 * reversed "the types and operands", a mangling-encoding key), then thunk_FUN_002298d4.
 * Confidence: medium.
 */
void sk_swift_mangle_obfuscate(void)
{
    /* bVar1 = FUN_00348c48(); FUN_0034ec48(bVar1, s_..._004e7a30._16_8_, bVar1 ^ s_..._004e7a30._0_8_);
     * thunk_FUN_002298d4(); FUN_001a8564() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb828   (est. sk_swift_mangle_start)
 * Ghidra: void FUN_001eb828(void)
 * Starts the mangling decode: FUN_001a84f4 then thunk_FUN_002298d4(*x20).
 * Confidence: medium.
 */
void sk_swift_mangle_start(void)
{
    /* uVar1 = *x20; FUN_001a84f4(auStack_68); thunk_FUN_002298d4(uVar1); FUN_001a8564() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb870   (est. sk_swift_utf8_print)
 * Ghidra: void FUN_001eb870(void)
 * Prints an 8-byte UTF-8 scalar to an output buffer: grows the buffer, encodes the scalar via
 * a per-byte helper (FUN_0034f064/FUN_003495a8 branch), pads, and finalizes via FUN_0006b6f4.
 * Confidence: medium.
 */
void sk_swift_utf8_print(void)
{
    /* auVar7 = FUN_003565a8(); FUN_0023560c(auVar7._0_8_,0x10,0); FUN_00352c80();
     * if ((x1>>0x3c&1)==0) { if ((x19&0x2000000000000000)!=0) x21 = x19>>0x38 & 0xf; FUN_003504a0(x21<<0x10|7); lVar5 = FUN_002af74c(); }
     *   else { FUN_00084180(); lVar5 = FUN_0029b9a8(); } lVar1 = 0x10 - lVar5; if (SBORROW8(0x10,lVar5)) SBP 0x1eb9e0;
     * if (-1 < lVar1) { if (lVar1 != 0) { for (lVar5 = lVar5 - 0x10; lVar5 != -1; ++lVar5) { ...encode one byte of the scalar...
     *     FUN_00350744(&DAT_005cf0f4); FUN_001a89a8(); ... } } FUN_0035063c(0x7830,0xe200000000000000); FUN_001e3f70();
     *   FUN_0034bd90(); FUN_003a25d4(); auVar8 = FUN_0006b6f4(); FUN_00356590(auVar8._0_8_,auVar8._8_8_,auVar7._8_8_); return; }
     * FUN_00347da8(); FUN_003504b8(); FUN_001afe4c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eb9f0   (est. sk_swift_string_equal_check)
 * Ghidra: void FUN_001eb9f0(void)
 * Swift string equality helper: if the length is nonzero, runs the compare chain and publishes
 * the result; else the empty compare.
 * Confidence: medium.
 */
void sk_swift_string_equal_check(void)
{
    /* FUN_00084220; FUN_00351cf4; FUN_00358ef4; FUN_0034ece8; uVar2 = *(x16+0x40); (*DAT_00658c00)();
     * lVar1 = FUN_00355b28(); if (lVar1 != 0) { FUN_00310fc4(); FUN_00350b30(); FUN_0034ed88(); (*x9)();
     *   auVar3 = FUN_00350494(); FUN_00117cc4(auVar3._0_8_,auVar3._8_8_,uVar2); FUN_0034bc94(); FUN_000839d8();
     *   FUN_00084234(x30); return; } FUN_0034c3f4(); FUN_00084234(); FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ebab4   (est. sk_swift_string_hash)
 * Ghidra: void FUN_001ebab4(void)
 * Swift string hash: locks, computes the hash value, and either stores it or runs the hash
 * chain; publishes via FUN_00084234.
 * Confidence: medium.
 */
void sk_swift_string_hash(void)
{
    /* FUN_00084220; FUN_00350b54; uVar1 = FUN_00310d68(0); FUN_000a6f88; FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034b2f8; FUN_0034b3c8; uVar2 = *(x16_00+0x40); (*DAT_00658c00)(); FUN_00358278; FUN_00354810;
     * auVar3 = FUN_003511a8(); (*x9)(auVar3._0_8_,auVar3._8_8_,uVar1); FUN_0034aa54();
     * if (Z) { FUN_00350aa0(*(x16+8)); (*x8)(); uVar1 = 0; } else { auVar3 = FUN_00350518();
     *   FUN_00117cc4(auVar3._0_8_,auVar3._8_8_,uVar2); FUN_00310f94(); FUN_0034b814(); uVar1 = (*x8_00)(); }
     * FUN_00084234(uVar1,x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ebbc8   (est. sk_swift_string_utf8_emit)
 * Ghidra: void FUN_001ebbc8(void)
 * Emits UTF-8: FUN_0034f664/FUN_00310f94/FUN_0034bcf0 then FUN_001eb870.
 * Confidence: medium.
 */
void sk_swift_string_utf8_emit(void)
{
    /* FUN_0034f664(); FUN_00310f94(); FUN_0034bcf0(); (*x8)(); FUN_001eb870() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ebc5c   (est. sk_swift_string_has_prefix)
 * Ghidra: uint FUN_001ebc5c(undefined8 p1,undefined8 p2)
 * Swift hasPrefix: parses both strings into native storage, and compares the leading runs;
 * returns boolean.
 * Confidence: medium.
 */
uint sk_swift_string_has_prefix(uint64_t p1, uint64_t p2)
{
    /* FUN_00350aac(p1,auStack_80); FUN_00344ca8(); FUN_00350aac(p2,&local_58); FUN_00344ca8();
     * if (local_68 == 0) { if (lStack_40 == 0) { FUN_003555a0(); FUN_00344e54(auStack_80); return 1; } }
     *   else { FUN_00344ca8(auStack_80,auStack_a8,0x656170,&DAT_004e7fc8); if (lStack_40 != 0) {
     *     uVar1 = FUN_002291a4(auStack_a8,&local_d0); ...; return uVar1 & 1; } FUN_003199ac(auStack_a8); }
     * FUN_00344e54(auStack_80,0x656178,&DAT_004e7fd0); return 0 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ebd70   (est. sk_sched_wakeup_svc)
 * Ghidra: void FUN_001ebd70(undefined8 p1,undefined8 p2,undefined8 p3)
 * Scheduler wakeup service: CPU obj, lock, run-queue length at (obj+0x30), and on the armed
 * path builds a wakeup tuple and dispatches; on error releases via FUN_0034ec88. Returns via
 * FUN_0008e500.
 * Confidence: medium.
 */
void sk_sched_wakeup_svc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_cpu_get();
    /* uVar4 = p3; FUN_00349720; (*DAT_00658c00)(x8+0x40); FUN_003497b4; uVar2 = FUN_00350908();
     * FUN_00310d68(uVar2,uVar4); FUN_00348e18; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4; FUN_0034d414;
     * FUN_003515b4; FUN_003722e4; FUN_00348fd8; FUN_0007c1a4; (*DAT_00658c00)(); lVar3 = FUN_0034b0c4();
     * lVar5 = *(int*)(lVar3+0x30); pcVar6 = *(x16_00+0x10); FUN_0034d758; (*pcVar6)(); FUN_0035745c(x24+lVar5);
     * (*pcVar6)(); FUN_0034ad40(); lVar3 = x16_00;
     * if (Z) { r=1; FUN_0034ad40(x24+lVar5); if (Z) goto done; }
     * else { FUN_00100c38(); (*pcVar6)(); FUN_0034ad40(x24+lVar5); if (!Z) { uVar4 = FUN_003567e0();
     *     auVar7 = FUN_00356af4(uVar4,x24+lVar5); (*x9)(auVar7._0_8_,auVar7._8_8_,p3); ...; goto done; }
     *   uVar4 = FUN_0034ec88(); (*x8_00)(uVar4,p3); } r = 0; lVar3 = x16_01;
     * done: FUN_003514e8(*(lVar3+8)); (*x8_02)(); FUN_0008e500(r&1,x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ebf88   (est. sk_swift_release_return)
 * Ghidra: undefined8 FUN_001ebf88(undefined8 param_1)
 * Frees via FUN_0036b118 and returns param_1 unchanged.
 * Confidence: medium.
 */
uint64_t sk_swift_release_return(uint64_t param_1)
{
    /* FUN_0036b118(); return param_1 */
    return param_1;
}

/* ------------------------------------------------------------------ *
 * FUN_001ebfb0   (est. sk_swift_string_utf8_dispatch)
 * Ghidra: void FUN_001ebfb0(undefined8 p1,undefined8 p2,undefined8 p3)
 * UTF-8 string dispatch: FUN_003528cc/FUN_00352578 then the obj-method chain.
 * Confidence: medium.
 */
void sk_swift_string_utf8_dispatch(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* uVar1 = FUN_003528cc(); FUN_00352578(uVar1,p3); FUN_00237f7c(); FUN_000b43e8(); FUN_0034b3e8();
     * (**x16+8)(); FUN_000b4390() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ec010   (est. sk_swift_tree_count)
 * Ghidra: long FUN_001ec010(long param_1)
 * Recursively counts the nodes of a Swift tree: invokes (param_1+0x18) to read the children
 * container, recurses on each child, sums the node counts. SBP 0x1ec0c4 on overflow.
 * Confidence: medium.
 */
long sk_swift_tree_count(long param_1)
{
    /* (**param_1+0x18)(&local_90); if (local_90==0) lVar2=0; else { local_60 = local_90; ...
     *   lVar2 = FUN_001ec010(&local_60); FUN_00359d44(); FUN_00344e54(&local_90); }
     * FUN_000027e8(); lVar3 = (**x16+0x128)(); if (!SCARRY8(lVar2,lVar3)) return lVar2+lVar3;
     * SoftwareBreakpoint(1,0x1ec0c4) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ec0c4   (est. sk_swift_tree_children)
 * Ghidra: void FUN_001ec0c4(void)
 * Reads a Swift tree's children container via (x20+0x18).
 * Confidence: medium.
 */
void sk_swift_tree_children(void)
{
    /* (**x20+0x18)(auStack_50); FUN_0034a224() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ec104 @ 0x001ec104   (est. sk_swift_string_codepoint_count)
 * Ghidra: void FUN_001ec104(undefined8 p1,...,undefined8 *param_8)
 * Very large Swift string-length/character-count service. Counts UTF-8 characters with grapheme
 * handling: recursively descends a tree of substring segments (via FUN_001ec010), then iterates
 * the UTF-8 bytes, classifying each character (ASCII/latin/2/3/4-byte) with a "1 element",
 * "elements" pluralization table (s_elements_005d3c41, s_1_element_005d3c4b) and emits a count.
 * Multiple decompiler "unreachable block" warnings. Confidence: low (extremely complex, many
 * unrecovered control-flow edges).
 */
void sk_swift_string_codepoint_count(uint64_t p1, uint64_t p2, uint64_t *p3, uint64_t *p4,
                                     long p5, long p6, uint64_t *p7, uint64_t *p8)
{
    /* auVar31 = FUN_0008e518(); lVar15 = auVar31._8_8_; lVar18 = *in_stack_00000068;
     * if (lVar18 < 1) goto done; if (((p7&1)==0) && ((p8&0xff)==0)) {
     *   uVar6 = FUN_0021398c(...); if ((uVar6&1) && (*(char*)(lVar15+0x10) != 1 && (**lVar15+0x18)(&local_110), local_110 != 0)) {
     *     lVar19 = FUN_001ec010(&local_b0); ... if (lVar19 < 1) goto done; } }
     * *in_stack_00000068 = lVar18 - 1; ... allocate count buffer ... 
     * -- then a long switch on the char-class byte (auVar26) with 8 cases, each running a UTF-8
     *    decode + pluralization + count-append chain; the count string is built and returned. */
    /* Multiple "Removing unreachable block" warnings: control flow at 0x001ec54c/0x001ec560/0x001ec840/
     *   0x001ed030/0x001ed03c/0x001ed28c/0x001ed034; large switch reconstructed partially. */
}

/* ------------------------------------------------------------------ *
 * FUN_001ed960   (est. sk_swift_array_init_repeat)
 * Ghidra: void FUN_001ed960(undefined8 p1,undefined8 p2,ulong p3)
 * Swift array init(repeating:count:): if count < 2, emits an empty/repeat-1 array; else
 * allocates count*stride storage and initializes each element, growing the buffer. Ends with
 * FUN_00084180 + FUN_00356590.
 * Confidence: medium.
 */
void sk_swift_array_init_repeat(uint64_t p1, uint64_t p2, unsigned long p3)
{
    /* FUN_003565a8(); if ((long)p3 < 0) panic; FUN_0034f414(); if (p3 < 2) { if (x22==0) { ...empty... } }
     *   else { uVar4 = (x21&0xffffffffffff) * x22; (with inline-string width via x19>>0x38 & 0xf);
     *     if (uVar4 > 0xf) FUN_002a4a2c()/FUN_002a4ab4(); do { FUN_00349cbc / copy one element;
     *       ... } while (--x22 != 0); FUN_003a25d4(); }
     * auVar5 = FUN_00084180(); FUN_00356590(auVar5._0_8_,auVar5._8_8_,x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001edad0   (est. sk_swift_string_append_char)
 * Ghidra: void FUN_001edad0(void) — forward to FUN_00355484.
 * Confidence: medium.
 */
void sk_swift_string_append_char(void) { /* FUN_00355484() */ }

/* ------------------------------------------------------------------ *
 * FUN_001edaf0   (est. sk_swift_string_next_char)
 * Ghidra: void FUN_001edaf0(void)
 * Advances to the next char: FUN_0007c198 then (x16+0x48)().
 * Confidence: medium.
 */
void sk_swift_string_next_char(void)
{
    /* FUN_0007c198(); (**x16+0x48)() */
}

/* ------------------------------------------------------------------ *
 * FUN_001edb28   (est. sk_swift_string_parse_partition)
 * Ghidra: void FUN_001edb28(void)
 * Parses a Swift string partition: reads a value, and on layout-valid branches either returns
 * an empty/default value or the parsed partition; publishes via FUN_00359bf8.
 * Confidence: medium.
 */
void sk_swift_string_parse_partition(void)
{
    /* uVar1 = FUN_00353aa0(); FUN_00319808(uVar1,auStack_c0); FUN_00354bf8; FUN_00351f34;
     * FUN_00358b54(&local_70); uVar2 = FUN_00365b6c();
     * if ((uVar2&1)==0) { clear local_70; FUN_003554ec(); FUN_00344e54(&local_70); ...; FUN_0027c85c(auStack_a0); }
     *   else { FUN_000026e8(); FUN_00077070(&local_70,auStack_a0); FUN_0034d9ac(auStack_a0); FUN_0031b4f4();
     *     puVar3 = &local_70; FUN_000b4390(&local_70); (*x9)(); FUN_000026e8(auStack_a0); }
     * FUN_00359bf8(*(puVar3+5), *puVar3, puVar3[3]) */
}

/* ------------------------------------------------------------------ *
 * FUN_001edc20   (est. sk_swift_string_partition_dispatch)
 * Ghidra: undefined1[16] FUN_001edc20(undefined8 p1)
 * Dispatch for string partitioning: calls FUN_001edb28 then FUN_001ec104 (the character-count
 * service) and returns the count tuple.
 * Confidence: medium.
 */
uint64_t sk_swift_string_partition_dispatch(uint64_t p1)
{
    /* local_58 = 0x7fffffffffffffff; uVar2 = FUN_00359874(); local_70 = 0; uStack_68 = 0xe000000000000000;
     * local_60 = x8; FUN_00319808(uVar2,auStack_90); FUN_00319808(p1,local_b0); FUN_001edb28(auStack_50,local_b0);
     * FUN_003515b4(auStack_90,auStack_50,0); FUN_001ec104(); ... FUN_0034cc24(); FUN_00344e54(auStack_90);
     * FUN_003a25d4(local_60); return (local_70, uStack_68) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001edce8   (est. sk_swift_string_type_of)
 * Ghidra: void FUN_001edce8(undefined8 p1,undefined8 p2,ulong p3)
 * Swift _type(of:) / metatype resolution: resolves a type name from a mangled string, and on
 * failure panics "type not found for mangled name" (s_type_not_found_for_mangled_name__005cf150)
 * or "invalid pointer" (s_invalid_pointer_005cf139). Publishes via FUN_000bd3a4.
 * Confidence: high (string-matched).
 */
void sk_swift_string_type_of(uint64_t p1, uint64_t p2, unsigned long p3)
{
    /* auVar1._0_8_ = x21; auVar1._8_8_ = x19; lVar3 = FUN_0035300c();
     * if (lVar3 == 0) { FUN_001a89a8(s_invalid_pointer_005cf139,0xf,1); FUN_00351f28(); }
     *   else { FUN_0034c034(); uVar11 = x1 & 0xffffffffffff; uVar10 = p3>>0x38 & 0xf; uVar4 = (p3&0x2000000000000000)!=0 ? uVar10 : uVar11;
     *     uVar8 = (x1>>0x3b)&1; if ((p3&0x1000000000000000)==0) uVar8 = 1; uVar7 = (uVar8==0) ? 0xb : 7;
     *     FUN_0035063c(0xf, uVar7 | uVar4<<0x10); lVar3 = FUN_0029e8dc(); if (lVar3 < 0) panic;
     *     FUN_00084180(); uVar4 = FUN_00268540(); FUN_000867a8(uVar4+0x20,lVar3); lVar3 = FUN_00389b4c(); FUN_0036b118(uVar4);
     *     if (lVar3 != 0) { ...resolve the type... } else { FUN_001a89a8(s_type_not_found_for_mangled_name__005cf150,0x21,1);
     *       ...error path... } }
     * FUN_000bd3a4(uVar6); FUN_00353238() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee018   (est. sk_swift_type_lookup)
 * Ghidra: void FUN_001ee018(undefined8 p1,undefined8 p2)
 * Forwards to FUN_001ee030(p1,p2,FUN_0029e8dc).
 * Confidence: medium.
 */
void sk_swift_type_lookup(uint64_t p1, uint64_t p2) { /* FUN_001ee030(p1,p2,FUN_0029e8dc) */ }

/* ------------------------------------------------------------------ *
 * FUN_001ee030   (est. sk_swift_type_lookup_impl)
 * Ghidra: void FUN_001ee030(ulong p1,ulong p2,code *UNRECOVERED_JUMPTABLE)
 * Type lookup impl: computes a width/hint word and tails into the (unrecovered) demangler
 * dispatch table.
 * Confidence: low (unrecovered jumptable).
 */
void sk_swift_type_lookup_impl(unsigned long p1, unsigned long p2, void (*jt)(void))
{
    /* uVar1 = p1; if ((p2&0x2000000000000000)!=0) uVar1 = p2>>0x38 & 0xf;
     * uVar3 = (p1>>0x3b)&1; if ((p2&0x1000000000000000)==0) uVar3 = 1; uVar2 = (uVar3==0) ? 0xb : 7;
     * (*UNRECOVERED_JUMPTABLE)(0xf, uVar2 | uVar1<<0x10, p1, p2) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee0c8   (est. sk_swift_unaligned_load4)
 * Ghidra: undefined4 FUN_001ee0c8(long p1,long p2)
 * 4-byte aligned load: returns *(param_2+param_1) if 4-aligned, else panics via
 * FUN_003488bc/FUN_00349eb8.
 * Confidence: medium.
 */
uint32_t sk_swift_unaligned_load4(long p1, long p2)
{
    /* if (((ulong)(p2+p1) & 3) == 0) return *(uint32_t*)(p2+p1); FUN_003488bc(1); FUN_00349eb8() */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ee0fc   (est. sk_swift_unaligned_load8)
 * Ghidra: undefined8 FUN_001ee0fc(long p1,long p2)
 * 8-byte aligned load: returns *(param_2+param_1) if 8-aligned, else panics.
 * Confidence: medium.
 */
uint64_t sk_swift_unaligned_load8(long p1, long p2)
{
    /* if (((ulong)(p2+p1) & 7) == 0) return *(uint64_t*)(p2+p1); FUN_003488bc(1); FUN_00349eb8() */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ee130   (est. sk_swift_type_demangle_forward)
 * Ghidra: void FUN_001ee130(void) — forward to FUN_0022a4b0.
 * Confidence: medium.
 */
void sk_swift_type_demangle_forward(void) { /* FUN_0022a4b0() */ }

/* ------------------------------------------------------------------ *
 * FUN_001ee140   (est. sk_swift_type_demangle)
 * Ghidra: void FUN_001ee140(long param_1)
 * If param_1 != 0, runs the demangler chain (FUN_00351894/FUN_0031b524/FUN_00351d18/FUN_001fac04);
 * else FUN_0006f75c.
 * Confidence: medium.
 */
void sk_swift_type_demangle(long param_1)
{
    /* if (param_1 != 0) { FUN_00351894(); FUN_0031b524(); FUN_00351d18(); FUN_001fac04(); return; }
     * FUN_0006f75c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee174   (est. sk_swift_type_demangle_init)
 * Ghidra: void FUN_001ee174(undefined8 p1,...,undefined8 p6)
 * Demangler initializer: locks, invokes the demangle method, and either runs the full
 * demangle-result build (FUN_001ee3b8) or returns empty. Publishes via FUN_003548b8/FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_type_demangle_init(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5,
                                 uint64_t p6)
{
    sk_cpu_get();
    /* uVar3 = p4; FUN_00349a68; (*DAT_00658c00)(x8+0x40); FUN_003493c4; FUN_0034d698; (*DAT_00658c00)();
     * FUN_00358248; pcVar4 = *(x16+0x10); auVar5 = FUN_00350af4(); (*pcVar4)(auVar5._0_8_,auVar5._8_8_,uVar3);
     * FUN_00350920; FUN_003516d8; FUN_0031a29c; FUN_00350624(&local_8); uVar2 = FUN_00365b6c();
     * if ((uVar2&1)==0) { ...run demangle + build via FUN_001ee3b8(local_18,1,FUN_0031b53c,auStack_60,uVar3,p4,p6)...;
     *   ppuVar1 = local_20; } else { (*x8_00)(); ppuVar1 = &local_20; }
     * uVar3 = FUN_003548b8(); FUN_0008e500(uVar3, *(ppuVar1+0x58)) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee364   (est. sk_swift_type_dealloc)
 * Ghidra: void FUN_001ee364(void)
 * Deallocs a type: FUN_0036993c(0x672fa0,0x66bca0,0,0) then FUN_0036986c.
 * Confidence: medium.
 */
void sk_swift_type_dealloc(void)
{
    /* FUN_0036993c(0x672fa0,0x66bca0,0,0); FUN_0036986c() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee3b8   (est. sk_swift_type_build_demangled)
 * Ghidra: void FUN_001ee3b8(undefined8 p1,...,long p10)
 * Large demangler result builder: runs the demangle loop, appending demangled tokens; handles
 * the "1 element"/"elements" pluralization and a fatal error path (0x318, module "Swift").
 * Multiple unreachable-block warnings. Confidence: low (complex, partial reconstruction).
 */
void sk_swift_type_build_demangled(uint64_t p1, uint64_t p2, void (*cb)(void), uint64_t p4,
                                   long p5, uint64_t p6, uint64_t p7, uint64_t p8, uint64_t p9,
                                   long p10)
{
    /* FUN_00353cfc(); auVar11 = FUN_003553cc(); uVar5 = *(p5+0x18); FUN_0007c028(auVar11._0_8_,auVar11._8_8_,uVar5);
     * (*DAT_00658c00)(x8+0x40); FUN_003493c4; FUN_0034d944; (*DAT_00658c00)(); FUN_0034a1c8; (*DAT_00658c00)();
     * FUN_0034ac50; uVar9 = *(p5+0x10); FUN_0034a688; (*DAT_00658c00)(x8_00+0x40); FUN_00348f38;
     * FUN_003515b4(0xff,uVar9); FUN_003722e4(); FUN_00352efc; FUN_0034d464; FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034b05c; FUN_0007c028; (*DAT_00658c00)(x8_01+0x40); FUN_00348dd8; FUN_00351df0; FUN_00377824();
     * FUN_00348e60; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b460; FUN_00353148; (**x8_02+0x10)();
     * FUN_00352680(p7); FUN_00351414; (*x9)(); FUN_0034b278; lVar2 = FUN_00377bec(p7,p6);
     * pcVar3 = FUN_000a68f4(); FUN_00352554(x16+0x28);
     * do { (*pcVar3)(x25,x26,lVar2); FUN_003517a8; FUN_003586e4; FUN_00350884;
     *   if (Z) { FUN_0034f9d8(&stack_30); (*x8_06)(uVar7,p6); FUN_00350bc0(&stack_10); (*x8_07)(x22,x26);
     *     FUN_00352df4; FUN_00353d14(local_98); return; }
     *   iVar1 = *(int*)(x22+0x30); FUN_003561ac(); auVar11 = FUN_000dbd0c(); (*x8_03)(...,uVar9);
     *   FUN_00356a70; (*x8_04)(local_48,x25+iVar1,uVar5); auVar11 = FUN_001fbb74(x24,(uint)uVar7&1,p5);
     *   lVar6 = *x20; if ((auVar11._8_8_&1)==0) { FUN_00350f1c(); FUN_001f0700(); uVar7 = 1; continue; }
     *   lVar10 = *(x16+0x48) * auVar11._0_8_; ... append token ...; if (x21 != 0) { ...fatal-error path
     *     FUN_00350d94(0x318); FUN_0006f768(); FUN_00351c64(); FUN_001afa84(); } ... } while (true) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ee9f4   (est. sk_swift_type_symbol_lookup)
 * Ghidra: void FUN_001ee9f4(void)
 * Swift symbol/type lookup with a fatal-error path (0x30, module string at 0x005cf1b0) after a
 * runtime check; ends with FUN_0006f768 + FUN_001afa84.
 * Confidence: medium.
 */
void sk_swift_type_symbol_lookup(void)
{
    /* FUN_0035300c(); uVar3 = FUN_00350b54(); auVar7 = FUN_0006e778(0x32); uVar9 = auVar7._8_8_;
     * ... optional-check FUN_0034f064; on nil build 0xd000000000000030 error via FUN_003a25d4/FUN_002a4c98;
     *   on present path run FUN_0034a210/FUN_00353d64/FUN_0034895c/FUN_002060d4; then
     *   FUN_0034d044 / FUN_00351500 / FUN_0034b7c8 ... ;
     * FUN_0006f768(s_Fatal_error_005accd0); FUN_001afa84() */
}

/* ------------------------------------------------------------------ *
 * FUN_001eecdc   (est. sk_swift_type_demangle_full)
 * Ghidra: void FUN_001eecdc(void)
 * Full demangle: FUN_0035ace8/FUN_00358bfc/FUN_000a6894 then the demangle chain
 * (FUN_001ee140/FUN_001ee3b8), freeing via FUN_0036b118 and publishing via FUN_0035a7a4.
 * Confidence: medium.
 */
void sk_swift_type_demangle_full(void)
{
    /* FUN_0035ace8(); FUN_00358bfc(); uVar1 = FUN_000a6894(in_x7); FUN_00351384(uVar1); (*x8_00)();
     * FUN_003515d8(); uVar1 = FUN_001ee140(); FUN_003508e4(); FUN_0035359c(); FUN_0031b560();
     * FUN_00351330(); FUN_00351dcc(); FUN_001ee3b8(); if (x21 != 0) uVar1 = FUN_0036b118(uVar1);
     * FUN_0035a7a4(uVar1, x8) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eed8c   (est. sk_swift_type_build_finalize)
 * Ghidra: void FUN_001eed8c(void)
 * Finalizes a demangled type: runs the token-append loop, and on each iteration either appends a
 * scalar or resolves a reference (FUN_001fbb74/FUN_001a894c/FUN_001a0534), growing the output
 * buffer. Returns via FUN_00354b5c/FUN_00353d14.
 * Confidence: medium.
 */
void sk_swift_type_build_finalize(void)
{
    /* FUN_00353cfc(); uVar2 = in_x6; FUN_00349a68; (*DAT_00658c00)(x8+0x40); FUN_003493ac; uVar1 = FUN_0034f860();
     * FUN_003559bc(uVar1,uVar2); FUN_00377824(); FUN_00348fd8; FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428;
     * FUN_00350908; FUN_0034d464; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034c330; FUN_003504e8; FUN_003559bc();
     * FUN_00377824(); FUN_00348e60; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034d3c4; FUN_0035113c; uVar2 = FUN_00310d34();
     * FUN_0035869c; FUN_00352680(in_x6); FUN_0035060c; (*x9)(); FUN_0034b278; FUN_003509e0; uVar1 = FUN_00377bec();
     * pcVar3 = FUN_000a68f4(); lVar4 = x8_01;
     * do { (*pcVar3)(local_88,x26,uVar1); FUN_003517a8; FUN_00350884; if (Z) { FUN_00353118(); (*x8_03)(x20,x26);
     *     uVar2 = FUN_00354b5c(lVar4); FUN_00353d14(uVar2,uVar1); return; }
     *   pcVar8 = *(x16+0x20); (*pcVar8)(x8_00,local_88); (*x1)(x27,x8_00); if (x21 != 0) { ...free and return... }
     *   auVar9 = FUN_00350500(); auVar9 = FUN_0031b560(auVar9._0_8_,auVar9._8_8_,uVar2,in_x5); FUN_00352888(...);
     *   FUN_001fbb74(); if ((x1_00&1)==0) { lVar4 = FUN_001a894c(); ...FUN_001a0534; FUN_001f0700(); }
     *   else { FUN_0035457c(); FUN_00350a70(); (*x8_02)(); FUN_0035684c(*(x8_01+0x38)); FUN_001a1854(); lVar4 = x8_01; }
     * } while (true) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef104   (est. sk_swift_string_release_full)
 * Ghidra: void FUN_001ef104(void)
 * Releases a full Swift string: FUN_0034b85c + thunk_FUN_001fca54 + FUN_0034b788 + FUN_001f6b30,
 * writes the string word.
 * Confidence: medium.
 */
void sk_swift_string_release_full(void)
{
    /* FUN_0034b85c(); thunk_FUN_001fca54(auStack_80); FUN_0034b788(&local_58,auStack_80); FUN_001f6b30();
     * x8[1] = uStack_50; *x8 = local_58; x8[3] = uStack_40; x8[2] = local_48; x8[4] = local_38 */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef164   (est. sk_swift_string_get_parts)
 * Ghidra: void FUN_001ef164(undefined8 *param_1,long p2)
 * Reads the parts (grapheme/cluster segments) of a Swift string from (p2+0x10/0x18/0x20) via
 * thunk_FUN_001fca54 + FUN_001f6b30; writes the 5-word result.
 * Confidence: medium.
 */
void sk_swift_string_get_parts(uint64_t *out, long p2)
{
    /* uVar1 = *(p2+0x10); uVar2 = *(p2+0x18); uVar3 = *(p2+0x20); thunk_FUN_001fca54(auStack_80,*x20);
     * FUN_001f6b30(&local_58,auStack_80,uVar1,uVar2,uVar3); out[1] = uStack_50; *out = local_58;
     * out[3] = uStack_40; out[2] = local_48; out[4] = local_38 */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef208   (est. sk_swift_string_release_ret)
 * Ghidra: undefined8 FUN_001ef208(undefined8 p1,undefined8 p2,undefined8 p3)
 * Calls FUN_001ef24c then frees p3; returns the result.
 * Confidence: medium.
 */
uint64_t sk_swift_string_release_ret(uint64_t p1, uint64_t p2, uint64_t p3)
{
    /* uVar1 = FUN_001ef24c(); FUN_0036b118(p3); return uVar1 */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ef24c   (est. sk_swift_string_make_unique)
 * Ghidra: void FUN_001ef24c(undefined8 p1,undefined8 p2,long p3,undefined8 p4,undefined8 p5,undefined8 p6)
 * Makes a Swift string's storage unique (copy-on-write): computes a bit-width from the element
 * type at (p3+0x20), and either allocates inline stack storage or a heap buffer (FUN_0036a804),
 * then runs the buffer-init chain (FUN_002b82f0 with FUN_00347348) and finalizes with a canary
 * check (0x2c8502b44bfffed6).
 * Confidence: medium.
 */
void sk_swift_string_make_unique(uint64_t p1, uint64_t p2, long p3, uint64_t p4, uint64_t p5,
                                 uint64_t p6)
{
    /* local_58 = 0xd37afd4bb400012a; bVar1 = *(p3+0x20); uVar6 = (1L<<(bVar1&0x3f)) + 0x3f >> 6;
     * local_a0 = p4; uStack_98 = p5; local_90 = p6; lStack_88 = p3; local_80 = p1; uStack_78 = p2;
     * uVar2 = FUN_0031b560(0,p4,p5,p6); lVar7 = uVar6*8;
     * if (((bVar1&0x3f) < 0xe) || (uVar3 = FUN_003d31f8(lVar7,8), (uVar3&1)!=0)) {
     *   (*DAT_00658c00)(); lVar7 = -(lVar7 + 0xf & 0x3ffffffffffffff0); ...FUN_002b82f0(auStack_68, local_120+lVar7, uVar6, 0x6727f0, FUN_00347348, auStack_110, 0x6727f0, uVar2, uVar4); }
     *   else { uVar4 = FUN_0036a804(lVar7, ~0ull); ...FUN_002b82f0(auStack_68, uVar4, uVar6, 0x6727f0, FUN_00347348, auStack_110, 0x6727f0, uVar2, uVar5); thunk_FUN_00012568(uVar4,...); }
     * uVar4 = FUN_00027614(&DAT_0064c260,&DAT_004bbc30); uVar2 = FUN_0031dc0c(0,uVar2,uVar4,0x66c1c8);
     * uVar2 = FUN_0027ed7c(&local_118,uVar2,local_120); if (x21 != 0) local_118 = uVar2;
     * if (local_58 != 0xd37afd4bb400012a) FUN_0011d7e8(local_118) */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef4e4   (est. sk_swift_type_descriptor_fini)
 * Ghidra: void FUN_001ef4e4(void)
 * Type-descriptor finalize: FUN_00352194 + FUN_001fb204(*(x19+8)) then FUN_00357670.
 * Confidence: medium.
 */
void sk_swift_type_descriptor_fini(void)
{
    /* uVar1 = FUN_00352194(); FUN_001fb204(uVar1, *(uint32_t*)(x19+8)); FUN_00357670() */
}

/* ------------------------------------------------------------------ *
 * thunk_FUN_001fb370 @ 0x001ef510   (est. sk_swift_dict_storage_set)
 * Ghidra: void thunk_FUN_001fb370(undefined8 p1,...,long p7)
 * Dictionary storage set/insert: checks the key bounds and the key match (param_4 vs the
 * stored key word at (p5+0x24)); on success invokes the key/value set methods (at (p6-8)+0x10)
 * and (x16+0x10); else panics via FUN_003488bc/FUN_0034a238.
 * Confidence: medium.
 */
void sk_swift_dict_storage_set(uint64_t p1, uint64_t p2, unsigned long p3, int p4, long p5,
                               long p6, uint64_t p7)
{
    /* if ((((-1 < (long)p3) && (p3 >> (*(p5+0x20)&0x3f) == 0)) &&
     *       ((*(ulong*)(p5 + (p3>>6)*8 + 0x40) >> (p3&0x3f) & 1) != 0)) && (p4 == *(int*)(p5+0x24))) {
     *   (**((p6-8))+0x10)(p1, *(p5+0x30) + *(*(p6-8)+0x48)*p3, p6); FUN_00354d2c(*(p5+0x38));
     *   (**x16+0x10)(p2, x8 + *(x16+0x48)*p3, p7); return; }
     * FUN_003488bc(1); FUN_0034a238() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef52c   (est. sk_swift_dict_allocate)
 * Ghidra: undefined1[16] FUN_001ef52c(long *param_1,undefined8 *param_2,long p3)
 * Allocates a 0x40 dictionary (tag 0xf7be): builds key/value type words via FUN_003722e4
 * ("key/value" string s_key_value_005cea2a), allocates backing buffers, calls FUN_001ef690 to
 * fill, and returns a (vtable, dict) pair.
 * Confidence: medium.
 */
uint64_t sk_swift_dict_allocate(long *out, uint64_t *meta, long p3)
{
    /* lVar3 = FUN_0036a908(0x40,0xf7be); *out = lVar3; lVar1 = *(p3+0x10); lVar2 = *(p3+0x18);
     * lVar4 = FUN_003722e4(0,lVar1,lVar2,s_key_value_005cea2a,0); *(lVar3+0x20) = lVar4;
     * lVar6 = *(lVar4 + -8); *(lVar3+0x28) = lVar6; lVar6 = FUN_0036a908(*(lVar6+0x40),0xf7be);
     * *(lVar3+0x30) = lVar6; uVar5 = *(uint32_t*)(meta+1);
     * auVar7 = FUN_001ef690(lVar3, *meta, uVar5, *x20, lVar1, lVar2, *(p3+0x20)); *(lVar3+0x38) = auVar7._0_8_;
     * (**((lVar1-8))+0x10)(lVar6, auVar7._8_8_, lVar1); (**((lVar2-8))+0x10)(lVar6 + *(int*)(lVar4+0x30), uVar5, lVar2);
     * return (lVar6, &DAT_001ef68c) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ef690   (est. sk_swift_dict_storage_init)
 * Ghidra: undefined1[16] FUN_001ef690(long *param_1,undefined8 p2,undefined8 p3,undefined8 p4,
 *                                     undefined8 p5,undefined8 p6)
 * Dictionary storage init: builds key/value words ("key/value" string), allocates the backing
 * buffer (tag 0xb32a), and calls thunk_FUN_001fb370 to insert. Returns (buffer, vtable).
 * Confidence: medium.
 */
uint64_t sk_swift_dict_storage_init(long *out, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5,
                                    uint64_t p6)
{
    /* lVar1 = FUN_003722e4(0,p5,p6,s_key_value_005cea2a,0); *out = lVar1; lVar2 = *(lVar1 + -8);
     * out[1] = lVar2; lVar2 = FUN_0036a908(*(lVar2+0x40),0xb32a); out[2] = lVar2;
     * thunk_FUN_001fb370(lVar2, lVar2 + *(int*)(lVar1+0x30), p2, p3, p4, p5, p6);
     * return (lVar2, &DAT_003471a8) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ef7ac   (est. sk_swift_dict_subscript_get)
 * Ghidra: undefined1[16] FUN_001ef7ac(undefined8 p1,long p2)
 * Dictionary subscript get: if the dictionary is non-empty, looks up the key (FUN_001f98a8) and
 * returns (value, found) from the bucket at (p2+0x38); else returns (0, notFound).
 * Confidence: medium.
 */
uint64_t sk_swift_dict_subscript_get(uint64_t p1, long p2)
{
    /* if (*(long*)(p2+0x10) != 0) { auVar3 = FUN_001f98a8(); bVar1 = (auVar3._8_8_&1)==0; if (bVar1)
     *   uVar2 = 0; else uVar2 = *(uint64_t*)(*(p2+0x38) + auVar3._0_8_*8); return (uVar2, bVar1); }
     * return (0, 1) */
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_001ef804   (est. sk_swift_dict_subscript_set)
 * Ghidra: void FUN_001ef804(undefined8 p1,undefined8 p2,long p3,undefined8 p4,undefined8 p5)
 * Dictionary subscript set: if the dictionary is non-empty, computes the bucket (FUN_001f99f4 +
 * FUN_001fbb74) and writes the value into the bucket via the element method; publishes
 * via FUN_00350774.
 * Confidence: medium.
 */
void sk_swift_dict_subscript_set(uint64_t p1, uint64_t p2, long p3, uint64_t p4, uint64_t p5)
{
    /* if (*(long*)(p3+0x10) == 0) { bVar2 = true; } else { FUN_003561a0(); thunk_FUN_0036b270(x1);
     *   FUN_00077708(); FUN_001f99f4(); bVar2 = (x1_00&1)==0; if (!bVar2) { lVar1 = FUN_00350bcc();
     *     (**x16+0x10)(p1, *(x20+0x38) + *(x16+0x48)*lVar1, p5); } FUN_0036b118(); }
     * FUN_00350774(p1,bVar2); FUN_000839d8() */
}

/* ------------------------------------------------------------------ *
 * FUN_001ef808   (est. sk_swift_dict_update_value)
 * Ghidra: void FUN_001ef808(undefined8 p1,undefined8 p2)
 * Dictionary updateValue(forKey:): acquires the dict, looks up the key (FUN_001f98a8), and
 * either writes the new value into the existing bucket (write path) or inserts a new element
 * (FUN_001f06bc); restores the dict word. Panics 0x674278 on key-state mismatch.
 * Confidence: medium.
 */
void sk_swift_dict_update_value(uint64_t p1, uint64_t p2)
{
    /* uVar2 = FUN_003a261c(*x20); lVar6 = *x20; *x20 = 0x8000000000000000;
     * auVar8 = FUN_001f98a8(p2); lVar7 = auVar8._0_8_; lVar4 = *(lVar6+0x10); uVar5 = ~auVar8._8_4_ & 1;
     * if (SCARRY8(lVar4,uVar5)) SBP 0x1ef90c; uVar3 = FUN_00002534(&DAT_006576c8,&DAT_004f21d0);
     * uVar5 = FUN_00258c60(uVar2, lVar4+uVar5, uVar3); if ((uVar5&1)!=0) { auVar9 = FUN_001f98a8(p2);
     *   lVar7 = auVar9._0_8_; if ((auVar8._8_4_&1) != (auVar9._8_4_&1)) FUN_002591b4(0x674278); }
     * if ((auVar8._8_8_&1)==0) FUN_001f06bc(lVar7,p2,p1,lVar6); else *(*(lVar6+0x38) + lVar7*8) = p1;
     * *x20 = lVar6 */
}

/* ------------------------------------------------------------------ *
 * FUN_001efdc4   (est. sk_swift_dict_release_all)
 * Ghidra: void FUN_001efdc4(void)
 * Releases all dictionary entries: runs the teardown chain (FUN_00358930/FUN_0034f2e4/
 * FUN_0034c920/FUN_0031b560/FUN_00357a84/FUN_00100efc/FUN_001fc500/FUN_003552a0/FUN_001fb194)
 * then frees via FUN_0036b118.
 * Confidence: medium.
 */
void sk_swift_dict_release_all(void)
{
    /* FUN_00354744(); FUN_0034ba88(); FUN_003a261c(*x20); FUN_00358930(); FUN_0034f2e4(); FUN_0034c920();
     * FUN_0031b560(); FUN_00357a84(); FUN_00100efc(); FUN_001fc500(); FUN_003552a0(); FUN_00351aec();
     * FUN_001fb194(); FUN_003544c8(in_stack_8, x30); FUN_0036b118() */
}

/* ------------------------------------------------------------------ *
 * FUN_001efe44   (est. sk_swift_set_init)
 * Ghidra: void FUN_001efe44(void)
 * Swift Set initializer: reads a Set's storage, calls FUN_003524bc then FUN_0031a2b4/
 * FUN_00353c18 and FUN_001f1e28.
 * Confidence: medium.
 */
void sk_swift_set_init(void)
{
    /* auVar3 = FUN_00351cc4(); lVar2 = auVar3._8_8_; FUN_003524bc(*(lVar2+0x10),auVar3._0_8_,lVar2,
     *   *(lVar2+0x18), *(lVar2+0x20)); uVar1 = FUN_0031a2b4(); FUN_00353c18(uVar1,uVar1); FUN_001f1e28() */
}

/* ------------------------------------------------------------------ *
 * FUN_001efe88   (est. sk_swift_set_buffer_alloc)
 * Ghidra: void FUN_001efe88(void)
 * Allocates a Set buffer (tag 0xab9): fills the element type, allocates the backing buffer,
 * runs the element-init method, and publishes a (FUN_001eff54, vtable) via FUN_00084234.
 * Confidence: medium.
 */
void sk_swift_set_buffer_alloc(void)
{
    /* FUN_00084220(); FUN_00350980(); uVar1 = FUN_00358c2c(); lVar2 = FUN_0036a908(uVar1,0xab9); *x19 = lVar2;
     * *(lVar2+0x20) = *(x21+0x10); lVar3 = FUN_003499c8(); *(lVar3+0x28) = x16; uVar1 = FUN_0036a908(*(x8+0x40),0xab9);
     * *(lVar2+0x30) = uVar1; FUN_00350b84(*(x16+0x10)); auVar4 = (*x8_00)(); FUN_0035050c(auVar4._0_8_,auVar4._8_8_,
     *   *(x21+0x18), *(x21+0x20)); auVar4 = FUN_0031a2b4(); FUN_003511a8(auVar4._0_8_,auVar4._8_8_,auVar4._0_8_);
     * auVar4 = FUN_001effb8(); *(lVar2+0x38) = auVar4._0_8_; FUN_00084234(FUN_001eff54, auVar4._8_8_, x30) */
}

/* ------------------------------------------------------------------ *
 * FUN_001eff54   (est. sk_swift_set_buffer_release)
 * Ghidra: void FUN_001eff54(long *param_1)
 * Releases a Set buffer: reads the backing buffer, runs the teardown chain, and releases the
 * element type refs via thunk_FUN_00012568.
 * Confidence: medium.
 */
void sk_swift_set_buffer_release(long *param_1)
{
    /* lVar3 = *param_1; uVar1 = *(lVar3+0x30); lVar2 = *(lVar3+0x28); FUN_0035354c(*(lVar3+0x38));
     * (*x8)(); FUN_0006b6f4(*(lVar2+8)); (*x8_00)(); thunk_FUN_00012568(uVar1); thunk_FUN_00012568(lVar3) */
}

/* ------------------------------------------------------------------ *
 * FUN_001effb8   (est. sk_swift_set_bucket_alloc)
 * Ghidra: void FUN_001effb8(void)
 * Allocates a Set bucket (tag 0x939c): fills the element type, allocates the backing buffer,
 * runs FUN_001f2ee0 for the hash storage and FUN_001fb60c for the bucket, publishes via
 * FUN_0008e500.
 * Confidence: medium.
 */
void sk_swift_set_bucket_alloc(void)
{
    sk_cpu_get();
    /* plVar1 = FUN_0035128c(); lVar2 = FUN_0036a908(0x68,0x939c); *plVar1 = lVar2; *(lVar2+0x40) = *(x22+0x10);
     * lVar3 = FUN_003499c8(); *(lVar3+0x48) = x16; uVar4 = FUN_0036a908(*(x8+0x40),0x939c); *(lVar2+0x50) = uVar4;
     * uVar5 = FUN_003a261c(*x20); FUN_0034fec0(*(x16+0x10)); (*x8_00)(); FUN_000b4390(); auVar7 = FUN_001f2ee0();
     * *(lVar2+0x58) = auVar7._0_8_; FUN_0035050c(auVar7._0_8_,auVar7._8_8_,*(x22+0x18),*(x22+0x20));
     * uVar6 = FUN_0031b560(); auVar7 = FUN_001fb60c(lVar2+0x20,uVar4,uVar5,uVar6); *(lVar2+0x60) = auVar7._0_8_;
     * FUN_0008e500(FUN_001f00ac, auVar7._8_8_, x30) */
}
