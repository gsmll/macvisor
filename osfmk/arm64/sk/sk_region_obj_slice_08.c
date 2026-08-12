/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers slice 08 of the object/string-machinery region:
 * 0x2d0800 - 0x2dd900.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * endpoint, vspace, sched, etc. Confidence is medium unless a string matches.
 *
 * The region is dominated by embedded Swift standard-library runtime (Int128
 * arithmetic/formatting, Set/Array slice/index math, Unicode/string stepping)
 * and object-service loops (heavy indirect dispatch through method tables).
 * Such functions are named sk_swift_* / sk_object_* / sk_cap_* accordingly.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* 16-byte aggregate returned by many Swift runtime helpers. */
typedef struct { unsigned long lo; unsigned long hi; } sk_i128_t;

/* Out-of-range kernel/Swift-runtime helpers referenced by this region (FUN_
 * addr in comment; bodies owned by sibling SK range workers). Names are
 * estimates. */

/* Swift runtime: retain/release/alloc/free. */
extern void *sk_alloc(unsigned long size, unsigned long tag);         /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);   /* FUN_0036b270 */
extern void sk_free(void *ptr);                                       /* FUN_0036b118 */
extern void sk_swift_release(unsigned long, ...);                     /* FUN_003a25d4 */
extern unsigned long sk_swift_retain(unsigned long, ...);             /* FUN_0036b270 */

/* Kernel lock / current-CPU / thread primitives. */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *d, void *e); /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a, ...);               /* FUN_00377bec */
extern void sk_lock_release(unsigned long a, ...);                    /* FUN_00377dcc */
extern void *sk_current_tcb(void);                                    /* FUN_000867ec */
extern void *sk_cpu(void);                                            /* FUN_0008e518 */
extern void *sk_cpu_curr(void);                                       /* FUN_0008e500 */
extern void *sk_thread_save(void *a, ...);                            /* FUN_0008e500 */
extern unsigned long sk_thread_epilogue(unsigned long, ...);          /* FUN_0008e500 */

/* Swift runtime: fatal-error / trap / overflow helpers. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern void sk_swift_fatal(void) __attribute__((noreturn));           /* FUN_001afa84 */
extern void sk_swift_fatal_break(void);                               /* FUN_0011d800 */
extern void sk_swift_fatal_break2(void);                              /* FUN_0011d85c */
extern unsigned long sk_swift_string_hash(void);                      /* FUN_001a8564 */
extern void sk_swift_string_hash_init(void);                          /* FUN_001a84f4 */
extern void sk_swift_retain_n(void);                                  /* FUN_0006b6f4 */
extern void sk_swift_alloc_n(unsigned long);                          /* FUN_0006e778 */
extern void sk_swift_alloc_stack(void);                               /* FUN_0007c1a4 */
extern void sk_swift_alloc_stack0(void);                              /* FUN_0007c028 */
extern unsigned long sk_swift_alloc_stack1(void);                     /* FUN_0007c0b8 */
extern unsigned long sk_swift_alloc_stack2(void);                     /* FUN_0008409c */
extern void sk_swift_begin(void);                                     /* FUN_00084180 */
extern unsigned long sk_swift_begin0(void);                           /* FUN_00084220 */
extern void sk_swift_end(unsigned long);                              /* FUN_00084234 */
extern void sk_swift_ctx_save(unsigned long);                         /* FUN_00084234 */
extern unsigned long sk_swift_range_check(unsigned long);             /* FUN_00027614 */
extern unsigned long sk_swift_ub_check(unsigned long);                /* FUN_00027754 */
extern unsigned long sk_swift_ub_check2(unsigned long);               /* FUN_00027724 */
extern unsigned long sk_swift_ub_check3(unsigned long);               /* FUN_000277b8 */
extern void sk_swift_alloc_check(unsigned long);                      /* FUN_0006f768 */
extern void sk_swift_alloc_check2(void);                              /* FUN_0006f6b4 */
extern void sk_swift_alloc_check3(void);                              /* FUN_000836a4 */
extern void sk_swift_alloc_check4(unsigned long);                     /* FUN_000839d8 */
extern void sk_swift_obj_init(unsigned long);                         /* FUN_000dbd0c */
extern void sk_swift_obj_ctx(void);                                   /* FUN_000e15d8 */
extern void sk_swift_obj_init2(void);                                 /* FUN_000e4674 */
extern void sk_swift_finalize(void);                                  /* FUN_000026e8 */
extern void sk_swift_ctx_end(void);                                   /* FUN_00012568 */

/* Method-table dispatch slot. */
extern unsigned long sk_dispatch_slot(void);                          /* DAT_00658c00 */

/* Out-of-range thunk targets used by slice bodies (owned by other workers). */
extern unsigned long FUN_002d0528();   /* 0x2d0528 */
extern unsigned long FUN_002d1710();   /* 0x2d1710 */
extern unsigned long FUN_002d1760();   /* 0x2d1760 */
extern unsigned long FUN_00343dd8();   /* 0x343dd8 */
extern unsigned long FUN_0032488c();   /* 0x32488c */
extern unsigned long FUN_00343eb4();   /* 0x343eb4 */
extern unsigned long FUN_00356940();   /* 0x356940 */
extern unsigned long FUN_003531d8();   /* 0x3531d8 */
extern unsigned long FUN_00352894();   /* 0x352894 */
extern sk_i128_t FUN_002d300c();   /* 0x2d300c */
extern unsigned long FUN_002d0c3c();   /* 0x2d0c3c */
extern unsigned long FUN_002d17bc();   /* 0x2d17bc */
extern unsigned long FUN_002d2548();   /* 0x2d2548 */
extern unsigned long FUN_002d2ad4();   /* 0x2d2ad4 */
extern unsigned long FUN_002d1e94();   /* 0x2d1e94 */
extern sk_i128_t FUN_002d14f4();   /* 0x2d14f4 */
extern sk_i128_t FUN_002d4b70();   /* 0x2d4b70 */
extern sk_i128_t FUN_002d4fd8();   /* 0x2d4fd8 */
extern unsigned long FUN_002d32e8();   /* 0x2d32e8 */
extern unsigned long FUN_002d6748();   /* 0x2d6748 */
extern unsigned long FUN_002d6d24();   /* 0x2d6d24 */
extern unsigned long FUN_002d6ae8();   /* 0x2d6ae8 */
extern unsigned long FUN_002d6bbc();   /* 0x2d6bbc */
extern unsigned long FUN_002d7214();   /* 0x2d7214 */
extern sk_i128_t FUN_002d476c();   /* 0x2d476c */
extern unsigned long FUN_002d484c();   /* 0x2d484c */
extern sk_i128_t FUN_002d4e2c();   /* 0x2d4e2c */
extern sk_i128_t FUN_002d5268();   /* 0x2d5268 */
extern unsigned long FUN_002d5300();   /* 0x2d5300 */
extern unsigned long FUN_002d56d4();   /* 0x2d56d4 */
extern unsigned long FUN_002d5f00();   /* 0x2d5f00 */
extern unsigned long FUN_002d3798();   /* 0x2d3798 */
extern sk_i128_t FUN_002d32b8();   /* 0x2d32b8 */
extern unsigned long FUN_002d3c28();   /* 0x2d3c28 */
extern unsigned long FUN_002d4ebc();   /* 0x2d4ebc */
extern unsigned long FUN_002d52e8();   /* 0x2d52e8 */
extern unsigned long FUN_002d54d8();   /* 0x2d54d8 */
extern sk_i128_t FUN_002e9774();   /* 0x2e9774 */
extern unsigned long FUN_002e6330();   /* 0x2e6330 */
extern unsigned long FUN_002d4af4();   /* 0x2d4af4 */
extern unsigned long FUN_002d53a8();   /* 0x2d53a8 */
extern unsigned long FUN_002d5604();   /* 0x2d5604 */
extern unsigned long FUN_002d6bbc();   /* 0x2d6bbc */
extern unsigned long FUN_002d7a1c();   /* 0x2d7a1c */
extern unsigned long FUN_002d7c80();   /* 0x2d7c80 */
extern unsigned long FUN_002d7cac();   /* 0x2d7cac */
extern unsigned long FUN_002d7cd4();   /* 0x2d7cd4 */
extern unsigned long FUN_002d7cfc();   /* 0x2d7cfc */
extern unsigned long FUN_002d7d24();   /* 0x2d7d24 */
extern unsigned long FUN_002d49d0();   /* 0x2d49d0 */
extern unsigned long FUN_002d49f4();   /* 0x2d49f4 */
extern unsigned long FUN_002d4a64();   /* 0x2d4a64 */
extern unsigned long FUN_002d4b38();   /* 0x2d4b38 */
extern unsigned long FUN_002d4e00();   /* 0x2d4e00 */
extern unsigned long FUN_002d4f50();   /* 0x2d4f50 */
extern unsigned long FUN_002d4f84();   /* 0x2d4f84 */
extern unsigned long FUN_002d5408();   /* 0x2d5408 */
extern unsigned long FUN_002d543c();   /* 0x2d543c */
extern unsigned long FUN_002d54fc();   /* 0x2d54fc */
extern unsigned long FUN_002d5534();   /* 0x2d5534 */
extern unsigned long FUN_002d5580();   /* 0x2d5580 */
extern unsigned long FUN_002d55b8();   /* 0x2d55b8 */
extern unsigned long FUN_002d5ee0();   /* 0x2d5ee0 */
extern unsigned long FUN_002d5ee4();   /* 0x2d5ee4 */
extern unsigned long FUN_002d66dc();   /* 0x2d66dc */
extern unsigned long FUN_002d66e0();   /* 0x2d66e0 */
extern sk_i128_t FUN_002d6730();   /* 0x2d6730 */
extern unsigned long FUN_002d738c();   /* 0x2d738c */
extern sk_i128_t FUN_002d7570();   /* 0x2d7570 */
extern sk_i128_t FUN_002d75dc();   /* 0x2d75dc */
extern unsigned long FUN_002d77e4();   /* 0x2d77e4 */
extern unsigned long FUN_002d7854();   /* 0x2d7854 */
extern unsigned long FUN_002d78d8();   /* 0x2d78d8 */
extern unsigned long FUN_002d7950();   /* 0x2d7950 */
extern unsigned long FUN_002d7d80();   /* 0x2d7d80 */
extern unsigned long FUN_002d7e60();   /* 0x2d7e60 */
extern unsigned long FUN_002d7f40();   /* 0x2d7f40 */
extern unsigned long FUN_002d8020();   /* 0x2d8020 */
extern unsigned long FUN_002d8194();   /* 0x2d8194 */
extern unsigned long FUN_002d8cc8();   /* 0x2d8cc8 */
extern unsigned long FUN_002d9774();   /* 0x2d9774 */
extern unsigned long FUN_002da2d8();   /* 0x2da2d8 */
extern unsigned long FUN_002dadb4();   /* 0x2dadb4 */
extern unsigned long FUN_002dadfc();   /* 0x2dadfc */
extern unsigned long FUN_002dae30();   /* 0x2dae30 */
extern unsigned long FUN_002db0a4();   /* 0x2db0a4 */
extern unsigned long FUN_002db10c();   /* 0x2db10c */
extern unsigned long FUN_002db174();   /* 0x2db174 */
extern unsigned long FUN_002db1b0();   /* 0x2db1b0 */
extern unsigned long FUN_002db22c();   /* 0x2db22c */
extern unsigned long FUN_002db258();   /* 0x2db258 */
extern unsigned long FUN_002db284();   /* 0x2db284 */
extern unsigned long FUN_002db2ac();   /* 0x2db2ac */
extern unsigned long FUN_002db3e8();   /* 0x2db3e8 */
extern unsigned long FUN_002db41c();   /* 0x2db41c */
extern unsigned long FUN_002db450();   /* 0x2db450 */
extern unsigned long FUN_002db6b8();   /* 0x2db6b8 */
extern unsigned long FUN_002db890();   /* 0x2db890 */
extern unsigned long FUN_002db8a4();   /* 0x2db8a4 */
extern unsigned long FUN_002db8b8();   /* 0x2db8b8 */
extern unsigned long FUN_002db8cc();   /* 0x2db8cc */
extern unsigned long FUN_002db8e0();   /* 0x2db8e0 */
extern unsigned long FUN_002db980();   /* 0x2db980 */
extern unsigned long FUN_002db9d0();   /* 0x2db9d0 */
extern unsigned long FUN_002dba00();   /* 0x2dba00 */
extern unsigned long FUN_002dc0d0();   /* 0x2dc0d0 */
extern unsigned long FUN_002dc134();   /* 0x2dc134 */
extern unsigned long FUN_002dc1c4();   /* 0x2dc1c4 */
extern unsigned long FUN_002dc44c();   /* 0x2dc44c */
extern unsigned long FUN_002dc4c4();   /* 0x2dc4c4 */
extern unsigned long FUN_002dc518();   /* 0x2dc518 */
extern unsigned long FUN_002dc564();   /* 0x2dc564 */
extern unsigned long FUN_002dc5a4();   /* 0x2dc5a4 */
extern unsigned long FUN_002dc748();   /* 0x2dc748 */
extern unsigned long FUN_002dc844();   /* 0x2dc844 */
extern unsigned long FUN_002dc86c();   /* 0x2dc86c */
extern unsigned long FUN_002dc974();   /* 0x2dc974 */
extern sk_i128_t FUN_002dca60();   /* 0x2dca60 */
extern unsigned long FUN_002dcac8();   /* 0x2dcac8 */
extern unsigned long FUN_002dcb38();   /* 0x2dcb38 */
extern unsigned long FUN_002dcb3c();   /* 0x2dcb3c */
extern sk_i128_t FUN_002dcb54();   /* 0x2dcb54 */
extern unsigned long FUN_002dcbb0();   /* 0x2dcbb0 */
extern unsigned long FUN_002dcbd8();   /* 0x2dcbd8 */
extern unsigned long FUN_002dcc48();   /* 0x2dcc48 */
extern unsigned long FUN_002dccc8();   /* 0x2dccc8 */
extern unsigned long FUN_002dcde8();   /* 0x2dcde8 */
extern unsigned long FUN_002dce20();   /* 0x2dce20 */
extern unsigned long FUN_002dce60();   /* 0x2dce60 */
extern unsigned long FUN_002dcee8();   /* 0x2dcee8 */
extern unsigned long FUN_002dcfb8();   /* 0x2dcfb8 */
extern unsigned long FUN_002dd08c();   /* 0x2dd08c */
extern unsigned long FUN_002dd138();   /* 0x2dd138 */
extern unsigned long FUN_002dd200();   /* 0x2dd200 */
extern unsigned long FUN_002dd24c();   /* 0x2dd24c */
extern unsigned long FUN_002dd29c();   /* 0x2dd29c */
extern unsigned long FUN_002dd390();   /* 0x2dd390 */
extern unsigned long FUN_002dd43c();   /* 0x2dd43c */
extern unsigned long FUN_002dd440();   /* 0x2dd440 */
extern unsigned long FUN_002dd4d8();   /* 0x2dd4d8 */
extern unsigned long FUN_002dd558();   /* 0x2dd558 */
extern unsigned long FUN_002dd5e0();   /* 0x2dd5e0 */
extern unsigned long FUN_002dd628();   /* 0x2dd628 */
extern unsigned long FUN_002dd66c();   /* 0x2dd66c */
extern unsigned long FUN_002dd6ac();   /* 0x2dd6ac */
extern sk_i128_t FUN_002dd728();   /* 0x2dd728 */
extern unsigned long FUN_002dd7e0();   /* 0x2dd7e0 */
extern unsigned long FUN_002dd824();   /* 0x2dd824 */

/* Common Swift-runtime helper groups used across the slice. */
extern unsigned long FUN_003162e0();   /* 0x3162e0 */
extern unsigned long FUN_00316964();   /* 0x316964 */
extern unsigned long FUN_003167cc();   /* 0x3167cc */
extern unsigned long FUN_0034a000();
extern unsigned long FUN_0034a8a4();
extern unsigned long FUN_00356bec();   /* 0x00356bec */
extern unsigned long FUN_0034a224();   /* 0x0034a224 */
extern unsigned long FUN_001aad64();   /* 0x001aad64 */
extern unsigned long FUN_001aa040();   /* 0x001aa040 */
extern unsigned long FUN_001a993c();   /* 0x001a993c */
extern unsigned long FUN_0036b270();   /* 0x0036b270 */
extern unsigned long FUN_0035ac28();   /* 0x0035ac28 */
extern unsigned long FUN_00350d94();   /* 0x00350d94 */
extern unsigned long FUN_00349944();   /* 0x00349944 */
extern unsigned long FUN_003498a8();   /* 0x003498a8 */
extern unsigned long FUN_001e3a28();   /* 0x001e3a28 */
extern unsigned long FUN_003486fc();   /* 0x003486fc */
extern unsigned long FUN_0034b778();   /* 0x0034b778 */
extern unsigned long FUN_001e6be8();   /* 0x001e6be8 */
extern unsigned long FUN_0034efec();   /* 0x0034efec */
extern unsigned long FUN_003528cc();
extern unsigned long FUN_002298d4();
extern unsigned long thunk_FUN_002298d4();   /* 0x34a000 */
extern unsigned long FUN_00376820();   /* 0x376820 */
extern unsigned long FUN_0035723c();   /* 0x35723c */
extern unsigned long FUN_003510a0();   /* 0x3510a0 */
extern unsigned long FUN_0035053c();   /* 0x35053c */
extern unsigned long FUN_00352700();   /* 0x352700 */
extern unsigned long FUN_0036a940();   /* 0x36a940 */
extern unsigned long FUN_0036a9a0();   /* 0x36a9a0 */
extern unsigned long FUN_00362acc();   /* 0x362acc */
extern unsigned long FUN_00361xxx(void);   /* 0x361xxx */

/* Standard Swift fatal-error shorthands used per the task conventions. */
static inline void sk_trap(void) { __builtin_trap(); }

/*--------------------------------------------------------------------*/
/* FUN_002d080c @ 0x002d080c   (est. sk_object_service_loop)
 * Ghidra: void FUN_002d080c(undefined8, undefined8, undefined8, undefined8)
 * Object-service dispatch loop: saves the current thread context, takes the
 * object lock, and runs a long sequence of method-dispatch helpers through the
 * DAT_00658c00 jump slot. On the (rare) tail path performs overflow checks,
 * resolves a method entry, and calls it before returning via the thread
 * epilogue. Unreachable block removed at 0x2d0a38.
 * Confidence: low (opaque indirect-dispatch pipeline; many unresolved helpers).
 * Notes: FUN_00351bec/FUN_0034e0a4/... helpers; dispatch through DAT_00658c00.
 */
void sk_object_service_loop(void *param_1, void *param_2, void *param_3, void *param_4)
{
    unsigned long u1, u2;
    (void)param_1; (void)param_2;
    sk_cpu();                                        /* FUN_0008e518 */
    /* FUN_003531d8 / FUN_00351bec(param_4) / FUN_0034e0a4 */
    u1 = sk_object_lock(0, 0, 0, 0, 0);              /* FUN_00377824 */
    /* FUN_00349c44 / FUN_0007c1a4 / dispatch / ... */
    sk_dispatch_slot();
    /* long helper chain: FUN_00350428 FUN_003509a4 FUN_003508c0(0xff)
     * FUN_00377824 FUN_0034ff98 FUN_00377bec FUN_0034c55c FUN_00319308
     * FUN_003490b8 FUN_0007c1a4 dispatch FUN_0034dccc FUN_0034a688
     * dispatch(extraout_x8+0x40) ... */
    u2 = sk_object_lock(0, 0, 0, 0, 0);
    /* FUN_002d0528(auStack_80, auVar5.lo, auVar5.hi, u2) */
    /* ... helpers ... */
    if ((u2 & 1) != 0) {
        /* overflow/error path */
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
    /* FUN_003509b0 ... FUN_003510b8 FUN_0008e500 (epilogue) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d0c3c @ 0x002d0c3c   (est. sk_object_service_slice)
 * Ghidra: void FUN_002d0c3c(undefined8, undefined8, undefined8, undefined8,
 *                          undefined8, undefined8)
 * Object-service slice/partition helper: acquires the object lock, dispatches
 * a series of field-access helpers, and (based on a size check) either runs a
 * fast completion or a full copy/fill path with bounds checks and a final
 * method call. Fatal-errors on inconsistency.
 * Confidence: low (indirect dispatch; many helpers).
 */
void sk_object_service_slice(void *param_1, void *param_2, void *param_3,
                             void *param_4, void *param_5, void *param_6)
{
    unsigned long u;
    (void)param_1; (void)param_2; (void)param_3; (void)param_4; (void)param_5; (void)param_6;
    /* FUN_00353cfc / FUN_00027754(param_6) / FUN_0034d3f4
     * FUN_00377824 / FUN_0034ab20 / FUN_0007c1a4 / dispatch ... */
    u = sk_object_lock(0, 0, 0, 0, 0);
    /* FUN_003722e4 / FUN_000a6f88 / dispatch ... */
    /* ... helpers ... FUN_00310924 */
    /* FUN_001d31b0 size check; if odd, fatal */
    if ((u & 1) == 0) {
        /* FUN_0035187c(0x678f78,&DAT_004f2458) FUN_0036993c FUN_0036986c */
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
    /* else path: copy/fill loop with method dispatch, then finalize */
    /* FUN_00351348 / FUN_00353d14(u2) */
    sk_lock_release(u);
}

/*--------------------------------------------------------------------*/
/* FUN_002d1070 @ 0x002d1070   (est. sk_object_service_advance)
 * Ghidra: void FUN_002d1070(undefined8, undefined8, long, ulong, undefined8,
 *                          long *, long *, long *)
 * Advances a slice/range cursor: takes the object lock, runs the field-access
 * pipeline, then depending on a mode flag either appends an element (with
 * carry/overflow checks against the base, low and high watermarks) or shifts
 * the whole window. Calls FUN_002d0c3c for the block move.
 * Confidence: low (heavy indirect dispatch; bounds arithmetic faithful).
 */
void sk_object_service_advance(void *p1, void *p2, long idx, unsigned long mode,
                               void *p5, long *low, long *high, long *base)
{
    unsigned long u;
    (void)p1; (void)p2; (void)p5;
    sk_cpu();
    /* FUN_00353cfc / FUN_00354708 / FUN_00027754 / FUN_00349ea0
     * FUN_00377824 / FUN_000a6f88 / FUN_0007c1a4 / dispatch ... */
    u = sk_object_lock(0, 0, 0, 0, 0);
    /* FUN_00369584 mode discriminator */
    if (mode == 1) {
        long off = *base - *low;                      /* SBORROW8 checks */
        /* append element: bounds checks on idx/off, then write via helpers */
        if ((mode & 1) != 0) {
            /* error path */
            sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
            sk_trap();
        }
        *high = *high + off + 1;
        /* FUN_00356078 / FUN_00352858 / ... FUN_00352d34 */
    } else {
        long a = *base + *low;
        long b = a - *high;
        long c = b - *high;
        FUN_002d0c3c(0, 0, 0, c, 0, 0);
        /* FUN_0016de38 / FUN_003509e0 */
        *high = *high + c;
        (*high)++;
    }
    /* FUN_00354b5c / FUN_00353d14 */
    sk_lock_release(idx);
}

/*--------------------------------------------------------------------*/
/* FUN_002d14f4 @ 0x002d14f4   (est. sk_object_service_alloc_slice)
 * Ghidra: undefined1 [16] FUN_002d14f4(undefined8 x 8)
 * Allocates a slice descriptor: pulls the object lock, packs an {owner,type}
 * pair from FUN_00356940 into the local payload, and hands it to
 * FUN_002d300c with the FUN_00343dd8 dispatch thunk. Returns the 16-byte
 * descriptor.
 * Confidence: low (allocation/dispatch plumbing).
 */
sk_i128_t sk_object_service_alloc_slice(void *p1, void *p2, void *p3, void *p4,
                                        void *p5, void *p6, void *p7, void *p8)
{
    sk_i128_t r;
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p6; (void)p7; (void)p8;
    /* FUN_00356940 / FUN_00352894(p7) / FUN_00350bd8 / FUN_0034a820
     * FUN_00377824(0xff,..,p5) / FUN_00352efc / FUN_003246d4
     * FUN_002d300c(local_50, pair.lo, FUN_00343dd8, stack, p5) */
    r = FUN_002d300c(p3, p5, p7, p8, p5);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d15ac @ 0x002d15ac   (est. sk_object_service_alloc_ctor)
 * Ghidra: void FUN_002d15ac(void)
 * Object-service constructor glue: acquires the lock, sets up a dispatch via
 * FUN_003512c0 with the FUN_0032488c thunk, and finalizes through
 * FUN_002d14f4.
 * Confidence: low.
 */
void sk_object_service_alloc_ctor(void)
{
    sk_i128_t r;
    /* FUN_00358374 / FUN_0034b5a8 / FUN_00027754 / FUN_00348b94
     * FUN_00377824 / FUN_003512c0(..,FUN_0032488c,..) */
    r = FUN_002d14f4(0, 0, 0, 0, 0, 0, 0, 0);
    (void)r;
    /* FUN_00358344(r.lo,r.hi) */
}

/*--------------------------------------------------------------------*/
/* FUN_002d1648 @ 0x002d1648   (est. sk_swift_array_get_element)
 * Ghidra: void FUN_002d1648(undefined8, long, long, long, long)
 * Swift Array subscript (get): validates index against count; on success
 * dispatches element copy through the element type's +0x10 method and the
 * stride at (meta+0x48). Fatal-errors out of range.
 * Confidence: high (classic Swift Array get).
 */
void sk_swift_array_get_element(void *out, long index, long elem_ptr, long count,
                                long meta)
{
    long m = *(long *)(meta + -8);
    if (index < 0) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
    if (index < count) {
        (*(void (**)(void *, char *, long))(m + 0x10))
            (out, (char *)elem_ptr + *(long *)(m + 0x48) * index, meta);
        return;
    }
    sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d16b4 @ 0x002d16b4   (est. sk_swift_array_set_element)
 * Ghidra: void FUN_002d16b4(undefined8, long)
 * Swift Array subscript (set): stores a word at buffer + offset*8 after a
 * bounds check against the array capacity (unaff_x20[1]).
 * Confidence: high.
 */
void sk_swift_array_set_element(void *value, long offset)
{
    long *a = /* unaff_x20 */ 0;
    long p = a[2] + offset;
    if (p < 0 || p >= a[1]) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
    *(void **)(*a + p * 8) = value;
}

/*--------------------------------------------------------------------*/
/* FUN_002d1710 @ 0x002d1710   (est. sk_swift_array_get)
 * Ghidra: undefined8 FUN_002d1710(long, long, long, long)
 * Swift Array element read: buffer + (base+index)*8 with bounds check.
 * Confidence: high.
 */
unsigned long sk_swift_array_get(long buffer, long index, long count, long base)
{
    long p = base + index;
    if (p < 0 || p >= count) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
    return *(unsigned long *)(buffer + p * 8);
}

/*--------------------------------------------------------------------*/
/* FUN_002d1760 @ 0x002d1760   (est. sk_swift_array_set)
 * Ghidra: void FUN_002d1760(undefined8, long)
 * Swift Array word store at offset (unaff_x20[3] base + offset) with bounds.
 * Confidence: high.
 */
void sk_swift_array_set(void *value, long offset)
{
    long *a = /* unaff_x20 */ 0;
    long p = a[3] + offset;
    if (p < 0 || p >= a[1]) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
    *(void **)(*a + p * 8) = value;
}

/*--------------------------------------------------------------------*/
/* FUN_002d17bc @ 0x002d17bc   (est. sk_swift_string_with_UnsafeBufferPointer)
 * Ghidra: void FUN_002d17bc(undefined8, undefined8, long, long, code *,
 *                          undefined8, long, long)
 * Swift withUnsafeBufferPointer closure driver: runs the body closure over the
 * two buffer ranges (forward and backward), calling the supplied code pointer
 * for each element with the element-type stride. Bounds-fatal on overrun.
 * Confidence: medium (closure driver faithful — forward f-at-head/b-in-body
 *   stepping and backward stride pass restored; dispatch and metadata bounds
 *   opaque per file convention).
 */
void sk_swift_string_with_UnsafeBufferPointer(void *p1, void *p2, long a3, long a4,
                                              unsigned long (*body)(void),
                                              void *p6, long p7, long p8)
{
    (void)p1; (void)p2; (void)p6;
    unsigned long u1;
    long f = p7, b = p8;   /* param_7 / param_8 loop cursors */
    long lVar5 = p7;       /* lVar5 = param_7 (sign-checked per iteration) */
    long lVar2 = p8;       /* lVar2 = param_8 */
    long k = a3, l = a4;   /* local_28/local_30 = in_stack_60/in_stack_68 */

    sk_cpu();              /* FUN_0008e518 -> per-CPU metadata (auVar6) */
    /* runtime prologue: FUN_0034a5c8 / DAT_00658c00(+0x40) / FUN_003493c4 /
     * FUN_0034d234 / DAT_00658c00 / FUN_0034a400 / DAT_00658c00 /
     * FUN_0034baa8 / DAT_00658c00 / FUN_0034b758 (Swift dispatch prelude) */

    /* forward pass: cursor f advances at the loop head, b advances in the
     * body. Per-element bounds: sign of lVar5/lVar2, the auVar6._8_8_
     * metadata upper bound (opaque), and param_4 <= param_8. */
    for (; f < a3 && b < a4; f = f + 1) {
        if (lVar5 < 0) goto fatal_lo;         /* LAB_002d1a80 */
        /* if (auVar6._8_8_ <= f) goto fatal_hi;  (opaque metadata bound) */
        /* dispatch via (meta+0x10) element table */
        if (lVar2 < 0) goto fatal_lo;
        if (a4 <= b) goto fatal_hi;           /* param_4 <= param_8 */
        /* dispatch via (meta+0x10) with tagged ptr; FUN_003504c4 */
        u1 = body();
        /* dispatch via (meta+8); FUN_00350b78 / meta+8 / FUN_003511a8 / meta+8 */
        if ((u1 & 1) == 0) break;
        b = b + 1;
    }
    /* backward pass: walk both ranges from the end with the element stride
     * (read from meta+0x48); element addr = meta_lo + stride*k / a3 + stride*l. */
    do {
        if (k <= f || l <= b) break;
        if (k < 1) goto fatal_lo;             /* local_28 < 1 */
        /* if (auVar6._8_8_ < a3) goto fatal_hi;      (opaque metadata bound) */
        /* if (param_4 < in_stack_68) goto fatal_hi;  (opaque stack bound) */
        k = k - 1;
        /* stride = *(long *)(meta + 0x48); dispatch(meta_lo + stride*k) */
        if (l < 1) goto fatal_lo;             /* local_30 < 1 */
        l = l - 1;
        /* dispatch(a3 + stride*l); FUN_00350ea4 */
        u1 = body();
        /* dispatch via (meta+8); FUN_003509d4 / meta+8 / meta+8(...) */
    } while ((u1 & 1) != 0);
    /* FUN_003504f4 / FUN_00351e3c */
    sk_thread_epilogue(0);                    /* FUN_0008e500 */
    return;

fatal_lo:  /* LAB_002d1a80: negative/underflow bound -> FUN_0034b348/FUN_003480ac */
    sk_fatal_error(0, 0);
    sk_trap();

fatal_hi:  /* LAB_002d1a8c: upper bound -> FUN_0034b348/FUN_003480ac */
    sk_fatal_error(0, 0);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d1ad8 @ 0x002d1ad8   (est. sk_swift_array_makeUnique)
 * Ghidra: void FUN_002d1ad8(void)
 * Swift Array copy-on-write makeUnique: drains pending append/insert work
 * from a work-queue (a 0x20-entry descriptor list at puVar4/DAT_00657778),
 * growing the buffer via FUN_003a261c / FUN_0006b42c, then frees the queue.
 * Confidence: medium (work-queue drain faithful).
 */
void sk_swift_array_makeUnique(void)
{
    (void)0;
    sk_cpu();
    /* FUN_0035128c / FUN_003246ec(0) / FUN_00348d7c / FUN_0007c1a4 / dispatch */
    /* loop: FUN_002d1e94 fills a descriptor; dispatch; FUN_002d17bc twice */
    /* queue entries: puVar4 + idx*0x20 => {p1,p2,count,flags} */
    /* FUN_003a261c grow / FUN_003a261c / ... */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d1e94 @ 0x002d1e94   (est. sk_swift_array_append_loop)
 * Ghidra: void FUN_002d1e94(void)
 * Swift Array append loop core: walks a source Set/Array and appends into a
 * destination with per-element copy through the element method table,
 * rebuilding the destination when it is (lVar1) large. Fatal on size overflow.
 * Confidence: low (heavy Set/Array append machinery; dispatch via lVar7+8).
 */
void sk_swift_array_append_loop(void)
{
    sk_cpu();
    /* FUN_00350b54 / FUN_003246ec(0xff) / FUN_003515b4(0xff,..,0x678ff0)
     * FUN_003722e4 / FUN_0034f624 / FUN_00310d68 / FUN_000a6f88 / dispatch ... */
    /* append body: if 1 < lVar1 -> FUN_002d16b4/FUN_002d1760 index writes,
     * FUN_002d2548 / FUN_002d2ad4 copy helpers */
    /* if lVar1 == 0 -> direct copy */
    /* if lVar9 == 1 -> single element via meta+0x10 */
    /* else -> single element via meta+0x10 */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d2548 @ 0x002d2548   (est. sk_swift_range_binarySearch)
 * Ghidra: void FUN_002d2548(undefined8, undefined8, long, long, long, long,
 *                          long, long)
 * Swift Range binary-search / merge step: repeatedly probes the element array
 * (FUN_002d1710) comparing against the merge comparator (in_stack_00000068),
 * building an ordered result. Overflow-checked index arithmetic; fatal on
 * inconsistent comparator result.
 * Confidence: low (merge/sort internals; carry-checked arithmetic faithful).
 */
void sk_swift_range_binarySearch(void *p1, void *p2, long a3, long a4, long a5,
                                 long a6, long a7, long a8)
{
    (void)p1; (void)p2; (void)a6; (void)a7; (void)a8;
    sk_cpu();
    long neg = -a5;
    /* FUN_003553cc / FUN_00352b98 / FUN_00355f40(a5-1) */
    /* loop: FUN_002968c0 / FUN_00351db4 probe */
    /* binary search / merge via FUN_002d1710(lVar8 ± 1) */
    /* bounds checks; result write into local_120; */
    /* FUN_002d16b4(lVar10,lVar8) store */
    /* on failure: sk_fatal_error with "Swift.Range" */
    if (neg >= 0) {
        /* fast path */
        FUN_002d1710(0, a3, a4, a5);
    }
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d2ad4 @ 0x002d2ad4   (est. sk_swift_range_merge)
 * Ghidra: void FUN_002d2ad4(undefined8, undefined8, long, long, undefined8 *,
 *                          long, long, long)
 * Swift Range merge driver: iterates two index cursors (FUN_002d1710),
 * feeding the comparator (in_stack_00000068) and writing the merged result via
 * FUN_002d1760. Overflow-checked index arithmetic; fatal on bounds violation.
 * Confidence: low (merge loop; carry-checked arithmetic faithful).
 */
void sk_swift_range_merge(void *p1, void *p2, long a3, long a4, void *p5,
                          long a6, long a7, long a8)
{
    (void)p1; (void)p2; (void)a6; (void)a7; (void)a8;
    sk_cpu();
    /* FUN_00355f40 / FUN_00349734 / FUN_0034e6cc / dispatch
     * FUN_0034ae58 -> {lVar14,lVar15} */
    /* loop: FUN_002968c0 / FUN_00351db4 probe */
    /* merge via FUN_002d1710 / FUN_002d1760 */
    /* bounds checks; result write */
    if (p5 != 0) {
        FUN_002d1760(0, a3);
    }
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d300c @ 0x002d300c   (est. sk_object_service_dispatch)
 * Ghidra: void FUN_002d300c(void)
 * Object-service dispatch: acquires the object lock, runs the field pipeline,
 * then either calls a resolve+dispatch thunk (FUN_003518d0 with FUN_00343eb4)
 * and frees the result, or dispatches directly through the +0x20 method slot.
 * Confidence: low.
 */
void sk_object_service_dispatch(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5;
    sk_cpu();
    /* FUN_0034c798 / FUN_0007c028 / dispatch / FUN_003497b4
     * FUN_00350908 / FUN_00310d68 / FUN_000a6f88 / FUN_0007c1a4 / dispatch ... */
    if (0) {
        /* FUN_003579f4 / dispatch via +0x10 / FUN_00349ea0 / FUN_00352858
         * FUN_00377824 / FUN_00351a44 / FUN_0019e578 / dispatch
         * FUN_003518d0(..,FUN_00343eb4) / FUN_001de8a8 / FUN_0036b118(uVar1) */
    } else {
        /* dispatch via +0x20: FUN_003508c0 / (*pcVar2)() / FUN_00351554 */
    }
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d3288 @ 0x002d3288   (est. sk_swift_int128_mul)
 * Ghidra: void FUN_002d3288(undefined8, long)
 * Int128 multiply wrapper: builds {value, 0} then calls the checked multiply
 * FUN_002d3c28 with the sign-extended second word.
 * Confidence: high.
 */
void sk_swift_int128_mul(void *out, long v)
{
    sk_i128_t r;
    r.lo = (unsigned long)v; r.hi = 0;
    FUN_002d3c28(r.lo, r.hi, (unsigned long)v, (unsigned long)v >> 63);
    (void)out;
}

/*--------------------------------------------------------------------*/
/* FUN_002d32b8 @ 0x002d32b8   (est. sk_swift_int128_mul_by_1e18)
 * Ghidra: undefined1 [16] FUN_002d32b8(ulong)
 * Int128 multiply a single word by 10^18 (0xDE0B6B3A7640000); returns the
 * 128-bit product.
 * Confidence: high.
 */
sk_i128_t sk_swift_int128_mul_by_1e18(unsigned long v)
{
    sk_i128_t r;
    unsigned __int128 p = (unsigned __int128)v * 1000000000000000000ULL;
    r.lo = (unsigned long)p;
    r.hi = (unsigned long)(p >> 64);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d32e8 @ 0x002d32e8   (est. sk_swift_Int128_toString_div10e18)
 * Ghidra: void FUN_002d32e8(undefined8, undefined8, undefined8)
 * Int128 decimal-string conversion, divisor 10^18: repeatedly extracts
 * 64-bit digit groups (dispatch through unaff_x22/unaff_x26 method slots),
 * tracking a 64-digit carry boundary, then emits the value with a final
 * 10^18 scale marker. Fatal on carry-width mismatch.
 * Confidence: low (Int128/printf formatting; dispatch slots).
 */
void sk_swift_Int128_toString_div10e18(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0034b9a0 / FUN_0034a37c / FUN_0007c1a4 / dispatch
     * FUN_0034924c / dispatch / FUN_0034928c / dispatch / FUN_0034b758
     * FUN_00353ecc(0x40) / FUN_0031c430 / FUN_0001df60 / FUN_0034aa74 */
    /* digit loop via unaff_x26/unaff_x22; 0x40/0x41 width checks */
    /* FUN_003552e0(1000000000000000000) final scale */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d3674 @ 0x002d3674   (est. sk_swift_Int128_legacy_negate_check)
 * Ghidra: void FUN_002d3674(undefined8, long)
 * Swift LegacyInt128 negation precondition: if the operand is negative, raise
 * a fatal error ("Swift.LegacyInt128.swift", line 0x286).
 * Confidence: high (string-matched fatal).
 */
void sk_swift_Int128_legacy_negate_check(void *v, long s)
{
    if (s >= 0) return;
    sk_fatal_error(0xb, 2, "Swift.LegacyInt128.swift", 0x18, 2, 0x286, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d36d8 @ 0x002d36d8   (est. sk_swift_int128_add_check)
 * Ghidra: void FUN_002d36d8(undefined8, undefined8, ulong, long)
 * Int128 checked add: builds {lo,hi} operands via FUN_002d3798, compares
 * magnitudes and signs, and fatal-errors if the result would overflow.
 * Confidence: high (128-bit add overflow check).
 */
void sk_swift_int128_add_check(void *a, void *b, unsigned long p3, long p4)
{
    sk_i128_t x;
    /* FUN_002d3798 -> {x.lo,x.hi} */
    /* compare signs/magnitudes of x vs {p3,p4}; on overflow:
       sk_fatal_error */
    if (p3 >= 0x8000000000000000ULL) {
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002d3798 @ 0x002d3798   (est. sk_swift_int128_magnitude)
 * Ghidra: void FUN_002d3798(void)
 * Int128 magnitude: computes the absolute-value pair of an accumulated 128-bit
 * value using FUN_000b4390 on the two 64-bit halves (with borrow).
 * Confidence: medium.
 */
void sk_swift_int128_magnitude(void)
{
    /* FUN_003504d0 / FUN_0035053c(0x73aff322e62439fd,0x9392ee8e921d5d0)
     * FUN_00316964 -> pair; FUN_000b4390(pair, 1e18)
     * FUN_003162e0 -> value; FUN_000b4390(lo,hi, uVar1-diff, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_002d3824 @ 0x002d3824   (est. sk_swift_double_toString)
 * Ghidra: void FUN_002d3824(double, undefined1 *)
 * Swift Double decimal-string conversion: on the integral path formats the
 * double as an integer; otherwise runs the full 128-bit fixed-point
 * formatting loop with Int128 accumulation. Heavy use of sk_swift_release.
 * Confidence: low (Double/Int128 formatting loop).
 */
void sk_swift_double_toString(double d, void *buf)
{
    (void)d; (void)buf;
    /* FUN_0024114c / FUN_003598b4 */
    /* integral: FUN_002d3ae0 / FUN_002428d0 / FUN_002d3c28 */
    /* else: FUN_0006e778(0x50) / Int128 accumulate loop with sk_swift_release
     * FUN_00353e14("__Int128") */
}

/*--------------------------------------------------------------------*/
/* FUN_002d3ae0 @ 0x002d3ae0   (est. sk_swift_int128_from_double_frac)
 * Ghidra: void FUN_002d3ae0(undefined8, undefined8, uint)
 * Int128 fractional conversion precondition: if the odd bit is set, fatal.
 * Confidence: high.
 */
void sk_swift_int128_from_double_frac(void *a, void *b, unsigned int odd)
{
    (void)a; (void)b;
    /* FUN_00316668 */
    if ((odd & 1) == 0) return;
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d3c28 @ 0x002d3c28   (est. sk_swift_int128_add_overflow)
 * Ghidra: void FUN_002d3c28(ulong, long, ulong, long)
 * Int128 checked addition: if the 128-bit add of {p1,p2}+{p3,p4} overflows,
 * fatal. Performs the canonical overflow test.
 * Confidence: high.
 */
void sk_swift_int128_add_overflow(unsigned long a_lo, long a_hi,
                                  unsigned long b_lo, long b_hi)
{
    unsigned long lo = a_lo + b_lo;
    long hi = a_hi + b_hi + (lo < a_lo);
    bool ovf = false;
    /* signed overflow: signs differ -> no; signs same -> result sign differs */
    if ((a_hi ^ b_hi) >= 0 && (hi ^ a_hi) < 0) ovf = true;
    if (!ovf) return;
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d3ca0 @ 0x002d3ca0   (est. sk_swift_Int128_toString_div1e15)
 * Ghidra: void FUN_002d3ca0(undefined8, undefined8, undefined8)
 * Int128 decimal-string conversion, divisor 10^15 (1e15): same structure as
 * FUN_002d32e8 but with final scale 10^15.
 * Confidence: low.
 */
void sk_swift_Int128_toString_div1e15(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* identical digit-loop structure to FUN_002d32e8 (0x40/0x41 checks,
     * dispatch slots) but FUN_003552e0(1000000000000000) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d403c @ 0x002d403c   (est. sk_swift_Int128_toString_div1e12)
 * Ghidra: void FUN_002d403c(undefined8, undefined8, undefined8)
 * Int128 decimal-string conversion, divisor 10^12 (1e12); same structure.
 * Confidence: low.
 */
void sk_swift_Int128_toString_div1e12(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* digit loop as FUN_002d32e8; FUN_003552e0(1000000000000) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d43d8 @ 0x002d43d8   (est. sk_swift_Int128_toString_div1e9)
 * Ghidra: void FUN_002d43d8(undefined8, undefined8, undefined8)
 * Int128 decimal-string conversion, divisor 10^9 (1e9); same structure.
 * Confidence: low.
 */
void sk_swift_Int128_toString_div1e9(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* digit loop as FUN_002d32e8; FUN_003552e0(1000000000) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d476c @ 0x002d476c   (est. sk_object_service_head)
 * Ghidra: void FUN_002d476c(void)
 * Object-service head: saves/loads a context pair; depending on a flag either
 * registers both dispatchers (FUN_0031ae4c / FUN_0031af6c) and finalizes, or
 * just finalizes.
 * Confidence: low (context/registration glue).
 */
void sk_object_service_head(void)
{
    /* FUN_00354bd4 / FUN_0034b440 / FUN_000a68c4 / FUN_0034dd4c */
    if (0) {
        /* FUN_0034f96c / FUN_000836a4 / FUN_0035122c / FUN_0031ae4c
         * FUN_0034ec58 / FUN_0035543c / FUN_000836a4 / FUN_003515a8
         * FUN_0031af6c / FUN_000dbd0c */
    }
    /* FUN_00351450 */
}

/*--------------------------------------------------------------------*/
/* FUN_002d484c @ 0x002d484c   (est. sk_object_service_save)
 * Ghidra: void FUN_002d484c(void)
 * Object-service state save: reads an object, saves its +0x18 field, registers
 * a dispatcher, and finalizes.
 * Confidence: low.
 */
void sk_object_service_save(void)
{
    long o;
    /* FUN_00352c10 -> o; FUN_0034f1a8(o, *(o+0x18)); FUN_000a68c4
     * FUN_00351660 / FUN_000dbd0c / FUN_0035543c / FUN_000836a4
     * FUN_003515a8 / FUN_0031ab1c / FUN_003505d0 / FUN_00350b18 */
    if (0) {
        /* FUN_0034f96c / FUN_000836a4 / FUN_0035122c / FUN_0031ac3c
         * FUN_00350a88 / FUN_003513b4 */
    }
    /* FUN_000026e8 (finalize) */
}

/*--------------------------------------------------------------------*/
/* FUN_002d490c @ 0x002d490c   (est. sk_object_service_save_cap)
 * Ghidra: void FUN_002d490c(undefined8)
 * Forwards to FUN_002d484c with the x20 {lo,hi} pair.
 * Confidence: high (trivial forwarder).
 */
void sk_object_service_save_cap(void *a)
{
    FUN_002d484c(a, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d4910 @ 0x002d4910   (est. sk_object_service_save_cap2)
 * Ghidra: void FUN_002d4910(undefined8)
 * Duplicate forwarder to FUN_002d484c (second cap variant).
 * Confidence: high.
 */
void sk_object_service_save_cap2(void *a)
{
    FUN_002d484c(a, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d4928 @ 0x002d4928   (est. sk_object_service_load)
 * Ghidra: void FUN_002d4928(undefined1 (*)[16])
 * Object-service load: obtains the head value and stores it into the caller's
 * 16-byte out slot.
 * Confidence: high.
 */
void sk_object_service_load(sk_i128_t *out)
{
    sk_i128_t r;
    r = FUN_002d476c();
    if (0 == 0) {
        (*(sk_i128_t *)out) = r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002d497c @ 0x002d497c   (est. sk_swift_string_hash_run)
 * Ghidra: void FUN_002d497c(void)
 * Swift String hash driver: initializes the hash (FUN_001a84f4), runs the
 * body through a function pointer (in_x3), then finalizes (FUN_001a8564).
 * Confidence: medium.
 */
void sk_swift_string_hash_run(void)
{
    /* FUN_001a84f4 / FUN_00350548 / (*in_x3)() / FUN_001a8564 */
    sk_swift_string_hash_init();
    sk_swift_string_hash();
}

/*--------------------------------------------------------------------*/
/* FUN_002d49d0 @ 0x002d49d0   (est. sk_swift_i128_eq)
 * Ghidra: bool FUN_002d49d0(long, long, long, long)
 * Int128 equality: both 64-bit words equal.
 * Confidence: high.
 */
bool sk_swift_i128_eq(long a_lo, long a_hi, long b_lo, long b_hi)
{
    return a_lo == b_lo && a_hi == b_hi;
}

/*--------------------------------------------------------------------*/
/* FUN_002d49f4 @ 0x002d49f4   (est. sk_swift_i128_lt)
 * Ghidra: bool FUN_002d49f4(ulong, long, ulong, long)
 * Int128 signed less-than.
 * Confidence: high.
 */
bool sk_swift_i128_lt(unsigned long a_lo, long a_hi, unsigned long b_lo, long b_hi)
{
    if (a_hi != b_hi) return a_hi < b_hi;
    return a_lo < b_lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002d4a64 @ 0x002d4a64   (est. sk_swift_i128_sub_overflow)
 * Ghidra: void FUN_002d4a64(ulong, long, ulong, long)
 * Int128 checked subtraction: fatal on signed overflow of {p1,p2}-{p3,p4}.
 * Confidence: high.
 */
void sk_swift_i128_sub_overflow(unsigned long a_lo, long a_hi,
                                unsigned long b_lo, long b_hi)
{
    bool ovf;
    unsigned long lo = a_lo - b_lo;
    long hi = a_hi - b_hi - (a_lo < b_lo);
    if (a_hi >= 0 && b_hi < 0 && hi < 0) ovf = true;
    else if (a_hi < 0 && b_hi >= 0 && hi >= 0) ovf = true;
    else ovf = false;
    if (!ovf) return;
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d4af4 @ 0x002d4af4   (est. sk_i128_zero)
 * Ghidra: void FUN_002d4af4(undefined8 *)
 * Zeroes a 128-bit value (two words).
 * Confidence: high.
 */
void sk_i128_zero(unsigned long *out)
{
    out[0] = 0;
    out[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002d4b38 @ 0x002d4b38   (est. sk_object_service_invoke)
 * Ghidra: void FUN_002d4b38(void)
 * Object-service invoke: runs a body function pointer and stores the returned
 * 16-byte value into the x19 out slot.
 * Confidence: high.
 */
void sk_object_service_invoke(sk_i128_t *out)
{
    /* FUN_00350240 / auVar1 = (*in_x4)(); *out = auVar1 */
    (void)out;
}

/*--------------------------------------------------------------------*/
/* FUN_002d4b70 @ 0x002d4b70   (est. sk_swift_double_toInt128)
 * Ghidra: undefined1 [16] FUN_002d4b70(double)
 * Swift Double -> Int128 conversion: on the integral path returns the integer
 * part; otherwise runs the fixed-point truncation with Int128 accumulation.
 * Confidence: low.
 */
sk_i128_t sk_swift_double_toInt128(double d)
{
    sk_i128_t r;
    (void)d;
    /* FUN_00358fa8 / FUN_002260b0 / FUN_0024114c(d, &local) / FUN_003598b4 */
    /* integral path: return {local.lo, in_stack} */
    /* else: FUN_0006e778(0x50) / Int128 accumulate loop */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d4e00 @ 0x002d4e00   (est. sk_swift_double_toInt128_from)
 * Ghidra: void FUN_002d4e00(void)
 * Loads a Double from the x19 buffer and converts to Int128 (FUN_002d4b70).
 * Confidence: high.
 */
void sk_swift_double_toInt128_from(void)
{
    /* uVar1 = FUN_00352b20(); *x19 = FUN_002d4b70(uVar1, *(x19+8)) */
    FUN_002d4b70(0.0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d4e2c @ 0x002d4e2c   (est. sk_swift_i128_negate)
 * Ghidra: void FUN_002d4e2c(long, long, long)
 * Int128 negate with overflow check: fatal ("Overflow in ...") if negating
 * the minimum; otherwise FUN_003167cc computes the two's complement.
 * Confidence: high (string-matched overflow).
 */
void sk_swift_i128_negate(long a_lo, long a_hi, long neg)
{
    (void)a_lo;
    if (a_hi == -0x8000000000000000LL && neg == 0) {
        sk_fatal_error(0xb, 2, "Overflow in Swift.LegacyInt128.swift", 0xe, 2, 0x3d8, 1);
        sk_trap();
    }
    FUN_003167cc(a_hi, a_hi >> 63, a_lo);
}

/*--------------------------------------------------------------------*/
/* FUN_002d4ebc @ 0x002d4ebc   (est. sk_swift_float_toInt128)
 * Ghidra: void FUN_002d4ebc(void)
 * Float-to-Int128 entry; forwards to FUN_002d5300.
 * Confidence: high.
 */
void sk_swift_float_toInt128(void)
{
    FUN_002d5300();
}

/*--------------------------------------------------------------------*/
/* FUN_002d4f1c @ 0x002d4f1c   (est. sk_swift_i128_fatal_range)
 * Ghidra: void FUN_002d4f1c(void)
 * Range-check failure fatal (shared tail).
 * Confidence: high.
 */
void sk_swift_i128_fatal_range(void)
{
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d4f50 @ 0x002d4f50   (est. sk_swift_float_toInt128_from)
 * Ghidra: void FUN_002d4f50(void)
 * Loads a Float and converts to Int128 via FUN_002d4ebc.
 * Confidence: high.
 */
void sk_swift_float_toInt128_from(void)
{
    /* uVar1 = FUN_00352194(); *x19 = FUN_002d4ebc(uVar1, *(x19+8)) */
    FUN_002d4ebc();
}

/*--------------------------------------------------------------------*/
/* FUN_002d4f84 @ 0x002d4f84   (est. sk_swift_fraction_reciprocal)
 * Ghidra: undefined1 [16] FUN_002d4f84(void)
 * Computes the reciprocal of a fraction (double division), returns as Int128.
 * Confidence: medium.
 */
sk_i128_t sk_swift_fraction_reciprocal(void)
{
    sk_i128_t r;
    double lo, hi;
    /* FUN_00077888 / FUN_00358fa8 / FUN_002260b0(&lo) / FUN_00350624(&hi)
     * FUN_002260b0(); r.lo = lo/hi; r.hi = 0 */
    r.lo = 1; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d4fd8 @ 0x002d4fd8   (est. sk_swift_double_toInt128_scale)
 * Ghidra: undefined1 [16] FUN_002d4fd8(double)
 * Double -> Int128 conversion with scaling (d * local); same Int128
 * accumulation as FUN_002d4b70.
 * Confidence: low.
 */
sk_i128_t sk_swift_double_toInt128_scale(double d)
{
    sk_i128_t r;
    (void)d;
    /* FUN_00358fa8 / FUN_002260b0 / FUN_0024114c(d*local, &local)
     * FUN_003598b4; else Int128 loop */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d5268 @ 0x002d5268   (est. sk_swift_i128_mul_overflow)
 * Ghidra: void FUN_002d5268(ulong, undefined8, long)
 * Int128 checked multiply: calls FUN_003162e0 and fatal-errors "Overflow in"
 * (0x2a4) if the low bit is set.
 * Confidence: high (string-matched overflow).
 */
void sk_swift_i128_mul_overflow(unsigned long lo, unsigned long hi, long s)
{
    FUN_003162e0(s, s >> 63, lo, hi);
    if ((lo & 1) == 0) return;
    sk_fatal_error(0xb, 2, "Overflow in Swift.LegacyInt128.swift", 0xd, 2, 0x2a4, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d52e8 @ 0x002d52e8   (est. sk_swift_float_something)
 * Ghidra: void FUN_002d52e8(void)
 * Float entry forwarding to FUN_002d5300.
 * Confidence: high.
 */
void sk_swift_float_something(void)
{
    FUN_002d5300();
}

/*--------------------------------------------------------------------*/
/* FUN_002d5300 @ 0x002d5300   (est. sk_swift_float_convert)
 * Ghidra: void FUN_002d5300(void)
 * Float-conversion core: runs a sequence of dispatch helpers and the
 * FUN_002e6330 formatting routine.
 * Confidence: low.
 */
void sk_swift_float_convert(void)
{
    /* FUN_0034dff4 / FUN_0035089c / FUN_00349a68 / dispatch
     * FUN_00348f38 / FUN_0035603c / FUN_00351488 / FUN_003545b8
     * FUN_0034ed68 / FUN_002e6330 / FUN_00351790 / FUN_003504c4 */
    FUN_002e6330();
}

/*--------------------------------------------------------------------*/
/* FUN_002d53a8 @ 0x002d53a8   (est. sk_swift_i128_mul_overflow_ub)
 * Ghidra: void FUN_002d53a8(undefined8, undefined8)
 * Int128 multiply overflow check: fatal on the odd flag.
 * Confidence: high.
 */
void sk_swift_i128_mul_overflow_ub(void *a, void *b)
{
    (void)a; (void)b;
    /* FUN_00355968(b) -> flag; FUN_003162e0() */
    if (0) {
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002d5408 @ 0x002d5408   (est. sk_swift_float_toInt128_from2)
 * Ghidra: void FUN_002d5408(void)
 * Float->Int128 entry via FUN_002d52e8.
 * Confidence: high.
 */
void sk_swift_float_toInt128_from2(void)
{
    /* uVar1 = FUN_00352194(); *x19 = FUN_002d52e8(uVar1, *(x19+8)) */
    FUN_002d52e8();
}

/*--------------------------------------------------------------------*/
/* FUN_002d543c @ 0x002d543c   (est. sk_swift_double_nan)
 * Ghidra: void FUN_002d543c(void)
 * Double NaN handling: emits "nan" or the normalized value with a
 * "seconds" suffix literal (0x73646e6f63657320).
 * Confidence: medium (string constants visible).
 */
void sk_swift_double_nan(void)
{
    sk_i128_t r;
    double d;
    (void)d;
    /* FUN_00358fa8 / FUN_002260b0(&d) */
    if (__builtin_isnan(d / 0.0)) {
        r.lo = 0x6e616e; r.hi = 0xe300000000000000ULL;
    } else {
        r = FUN_002e9774();
    }
    /* FUN_001e3f70(r.lo,r.hi,0x73646e6f63657320,0xe800000000000000ULL)
     * FUN_0034bd90 / FUN_003a25d4 / FUN_0006b6f4 */
    (void)r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d54d8 @ 0x002d54d8   (est. sk_swift_double_norm)
 * Ghidra: void FUN_002d54d8(void)
 * Double normalize; forwards to FUN_002e9774.
 * Confidence: high.
 */
void sk_swift_double_norm(void)
{
    FUN_002e9774();
}

/*--------------------------------------------------------------------*/
/* FUN_002d54fc @ 0x002d54fc   (est. sk_swift_i128_negate_store)
 * Ghidra: void FUN_002d54fc(undefined1 (*)[16], undefined8 *, undefined8)
 * Stores the negated 128-bit value from param_2 into the out slot.
 * Confidence: high.
 */
void sk_swift_i128_negate_store(sk_i128_t *out, unsigned long *src, unsigned long v)
{
    sk_i128_t r;
    r = FUN_002d4e2c(src[0], src[1], v);
    (*(sk_i128_t *)out) = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d5534 @ 0x002d5534   (est. sk_swift_i128_negate_self)
 * Ghidra: void FUN_002d5534(undefined1 (*)[16], undefined8)
 * Negates the value already in the out slot.
 * Confidence: high.
 */
void sk_swift_i128_negate_self(sk_i128_t *out, unsigned long v)
{
    sk_i128_t *p = (sk_i128_t *)out;
    sk_i128_t r;
    r = FUN_002d4e2c(p->lo, p->hi, v);
    *p = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d5580 @ 0x002d5580   (est. sk_swift_i128_mul_store)
 * Ghidra: void FUN_002d5580(undefined1 (*)[16], undefined8 *, undefined8)
 * Stores the checked-multiply result from param_2.
 * Confidence: high.
 */
void sk_swift_i128_mul_store(sk_i128_t *out, unsigned long *src, unsigned long v)
{
    sk_i128_t r;
    r = FUN_002d5268(src[0], src[1], v);
    (*(sk_i128_t *)out) = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d55b8 @ 0x002d55b8   (est. sk_swift_i128_mul_self)
 * Ghidra: void FUN_002d55b8(undefined1 (*)[16], undefined8)
 * Multiplies the out-slot value in place.
 * Confidence: high.
 */
void sk_swift_i128_mul_self(sk_i128_t *out, unsigned long v)
{
    sk_i128_t *p = (sk_i128_t *)out;
    sk_i128_t r;
    r = FUN_002d5268(p->lo, p->hi, v);
    *p = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d5604 @ 0x002d5604   (est. sk_object_service_tail)
 * Ghidra: void FUN_002d5604(void)
 * Object-service tail: context save/restore with a dispatch.
 * Confidence: low.
 */
void sk_object_service_tail(void)
{
    /* FUN_00084220 / FUN_0034d654 / FUN_00349720 / dispatch
     * FUN_00348f50 / FUN_003547ec / FUN_00351274 / FUN_0035133c
     * FUN_0034e084 / FUN_003512c0 / FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_002d56d4 @ 0x002d56d4   (est. sk_cap_alloc_object_svc)
 * Ghidra: void FUN_002d56d4(undefined8, undefined8, undefined8, undefined8,
 *                          undefined8, undefined8, undefined8)
 * Capability/object allocation service: acquires the object lock, walks the
 * object registry (FUN_0008f6f4/FUN_001e3048), and either completes a fast
 * path or performs a full allocation+registration sequence, recursing on the
 * tail. Fatal on registry inconsistency.
 * Confidence: low (cap/object allocation service; recursive tail).
 */
void sk_cap_alloc_object_svc(void *p1, void *p2, void *p3, void *p4, void *p5,
                             void *p6, void *p7)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
    /* FUN_0008e518 / FUN_0008f6f4(p5) / FUN_00377824 / FUN_0034ab20
     * FUN_0007c1a4 / dispatch ... FUN_001e3048 */
    /* fast path or full registration path; recurse FUN_002d56d4(...) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d5ee0 @ 0x002d5ee0   (est. sk_cap_alloc_object_svc_a)
 * Ghidra: void FUN_002d5ee0(void)
 * Cap service wrapper: FUN_0034a8a4 then FUN_002d56d4.
 * Confidence: high.
 */
void sk_cap_alloc_object_svc_a(void)
{
    FUN_0034a8a4();
    FUN_002d56d4();
}

/*--------------------------------------------------------------------*/
/* FUN_002d5ee4 @ 0x002d5ee4   (est. sk_cap_alloc_object_svc_b)
 * Ghidra: void FUN_002d5ee4(void)
 * Duplicate cap service wrapper.
 * Confidence: high.
 */
void sk_cap_alloc_object_svc_b(void)
{
    FUN_0034a8a4();
    FUN_002d56d4();
}

/*--------------------------------------------------------------------*/
/* FUN_002d5f00 @ 0x002d5f00   (est. sk_cap_find_object_svc)
 * Ghidra: void FUN_002d5f00(undefined8, undefined8, undefined8, undefined8,
 *                          undefined8, undefined8, undefined8)
 * Capability lookup service: acquires the object lock, resolves a cap/object
 * via the registry (FUN_0031c250), and either copies a found slot or performs
 * a full fill with string handling. Fatal on not-found.
 * Confidence: low (cap lookup service; recursive tail).
 */
void sk_cap_find_object_svc(void *p1, void *p2, void *p3, void *p4, void *p5,
                            void *p6, void *p7)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
    /* FUN_0008e518 / FUN_003564d0(p5) / FUN_0008f6f4 / FUN_00377824
     * FUN_0034ab20 / FUN_0007c1a4 / dispatch ... FUN_0031c250 */
    /* found: fast copy; else full fill; FUN_0031c550 */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d66dc @ 0x002d66dc   (est. sk_cap_find_object_svc_a)
 * Ghidra: void FUN_002d66dc(void)
 * Cap lookup wrapper.
 * Confidence: high.
 */
void sk_cap_find_object_svc_a(void)
{
    FUN_0034a8a4();
    FUN_002d5f00();
}

/*--------------------------------------------------------------------*/
/* FUN_002d66e0 @ 0x002d66e0   (est. sk_cap_find_object_svc_b)
 * Ghidra: void FUN_002d66e0(void)
 * Duplicate cap lookup wrapper.
 * Confidence: high.
 */
void sk_cap_find_object_svc_b(void)
{
    FUN_0034a8a4();
    FUN_002d5f00();
}

/*--------------------------------------------------------------------*/
/* FUN_002d6730 @ 0x002d6730   (est. sk_swift_i128_from_i64)
 * Ghidra: undefined1 [16] FUN_002d6730(undefined8, long)
 * Builds a 128-bit signed value from a 64-bit long (sign-extended).
 * Confidence: high.
 */
sk_i128_t sk_swift_i128_from_i64(unsigned long lo, long hi)
{
    sk_i128_t r;
    r.lo = (hi >= 0) ? lo : 0;
    r.hi = (hi >= 0) ? (unsigned long)hi : 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d6748 @ 0x002d6748   (est. sk_swift_int128_parse)
 * Ghidra: void FUN_002d6748(undefined8, undefined8, undefined8)
 * Int128 parse-from-string: iterates the digit stream (dispatch slots
 * unaff_x21/unaff_x26) accumulating the 128-bit value with a 0x40/0x41 digit
 * width check; returns the parsed value with a success flag.
 * Confidence: low (Int128 string parse; dispatch slots).
 */
void sk_swift_int128_parse(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0034b9a0 / FUN_0034a37c / FUN_0007c1a4 / dispatch
     * FUN_0034cff4 / FUN_003494e8 / dispatch / FUN_0034928c / dispatch
     * FUN_0034b758 / FUN_0035217c(0x40) / FUN_0031c430 / FUN_0001df60
     * FUN_0034aa74 */
    /* digit loop via unaff_x26/unaff_x21; 0x40/0x41 checks */
    /* FUN_0006b6f4(auVar7.lo,auVar7.hi,flag) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d6ae8 @ 0x002d6ae8   (est. sk_swift_uint8_to_Int)
 * Ghidra: void FUN_002d6ae8(void)
 * UInt8 -> Int conversion wrapper: runs FUN_002d6748 then a range check;
 * fatal "value cannot be converted to Int" on failure.
 * Confidence: medium (string-matched error).
 */
void sk_swift_uint8_to_Int(void)
{
    /* FUN_0034ed98 / FUN_00349b3c / dispatch / FUN_003490ec / FUN_00351e84
     * FUN_0034c818 / FUN_0034e53c / FUN_002d6748 / FUN_0035292c */
    if (1) {
        /* FUN_0034dcb4 / FUN_000e15d8 */
        return;
    }
    /* FUN_0034a478("value cannot be converted to Int") / FUN_003593c0
     * FUN_0006f768 / FUN_0035a894 */
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d6bbc @ 0x002d6bbc   (est. sk_swift_Int_to_UInt8)
 * Ghidra: void FUN_002d6bbc(undefined8, undefined8, undefined8)
 * Int -> UInt8 conversion with range check via FUN_002d6748.
 * Confidence: medium.
 */
void sk_swift_Int_to_UInt8(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_00084220 / FUN_0035098c / FUN_00349b3c / dispatch / FUN_00349178
     * FUN_0035399c / FUN_0034b768 / FUN_003509bc / FUN_002d6748(...)
     * FUN_0035292c */
    /* on ok: FUN_0008f6c0 / ... else fatal */
    if (1) {
        /* FUN_00354ddc / FUN_000b43d0 */
    }
    /* FUN_00350618 / FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_002d6d24 @ 0x002d6d24   (est. sk_swift_Int64_to_Double)
 * Ghidra: void FUN_002d6d24(undefined8, undefined8, undefined8)
 * Int64 -> Double conversion: acquires the lock, parses/converts via dispatch
 * slots, and produces a signed result with sign handling.
 * Confidence: low (numeric conversion pipeline).
 */
void sk_swift_Int64_to_Double(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2; (void)p3;
    sk_cpu();
    /* FUN_0034e73c / FUN_0008f6f4 / FUN_00377824 / FUN_0034ab20
     * FUN_0007c1a4 / dispatch ... FUN_00352cf8(0x43f0000000000000)
     * ... FUN_00358540 sign check; FUN_00352a28 */
    /* result into local_18; FUN_0008e500(local_18[0], lVar7) */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d7214 @ 0x002d7214   (est. sk_swift_Int_to_UInt64)
 * Ghidra: void FUN_002d7214(undefined8, undefined8, undefined8)
 * Int -> UInt64 conversion via FUN_002d6d24 with range check.
 * Confidence: medium.
 */
void sk_swift_Int_to_UInt64(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_0034ed98 / FUN_00349b3c / dispatch / FUN_003490ec
     * FUN_0035ac58(p3) / FUN_0031bfb0 / FUN_0035133c / FUN_00350c20(4)
     * FUN_0034e53c / FUN_002d6d24 / FUN_0035292c */
    if (1) {
        /* FUN_0034dcb4 / FUN_000e15d8 */
        return;
    }
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d738c @ 0x002d738c   (est. sk_swift_int128_shift)
 * Ghidra: void FUN_002d738c(undefined8, undefined8, undefined8)
 * Int128 shift wrapper; forwards to thunk_FUN_002298d4.
 * Confidence: high.
 */
void sk_swift_int128_shift(void *p1, void *p2, void *p3)
{
    (void)p1; (void)p2; (void)p3;
    FUN_003528cc();
    FUN_002298d4();
    FUN_002298d4(p3);
}

/*--------------------------------------------------------------------*/
/* FUN_002d7570 @ 0x002d7570   (est. sk_swift_int128_quotient)
 * Ghidra: undefined1 [16] FUN_002d7570(void)
 * Int128 quotient: returns {lo,hi} via FUN_0011d800.
 * Confidence: medium.
 */
sk_i128_t sk_swift_int128_quotient(void)
{
    sk_i128_t r;
    /* FUN_00352630 / FUN_0011d800 / FUN_00359dd0 */
    r = FUN_002d7570();
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d75dc @ 0x002d75dc   (est. sk_swift_int128_remainder)
 * Ghidra: undefined1 [16] FUN_002d75dc(void)
 * Int128 remainder: returns via FUN_0011d85c.
 * Confidence: medium.
 */
sk_i128_t sk_swift_int128_remainder(void)
{
    sk_i128_t r;
    /* FUN_00352630 / FUN_0011d85c / FUN_00359dd0 */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002d77e4 @ 0x002d77e4   (est. sk_swift_int128_div_check)
 * Ghidra: void FUN_002d77e4(undefined8, undefined8, long, long)
 * Int128 division precondition: fatal on zero divisor or on overflow.
 * Confidence: high.
 */
void sk_swift_int128_div_check(void *a, void *b, long d_lo, long d_hi)
{
    (void)a; (void)b;
    if (d_lo == 0 && d_hi == 0) {
        /* FUN_003485f0(1) / FUN_0034cb10 */
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
    /* FUN_00359828 / FUN_0035981c */
    if (1) {
        FUN_002d7570();
        return;
    }
    /* FUN_003487d4(1) / FUN_0034b9e8 */
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d7854 @ 0x002d7854   (est. sk_swift_int128_div_check_self)
 * Ghidra: void FUN_002d7854(void)
 * Int128 division precondition reading divisor from the buffer.
 * Confidence: high.
 */
void sk_swift_int128_div_check_self(void)
{
    /* FUN_00359e08; zero -> fatal; else FUN_00353ed8 read divisor
     * FUN_0035981c / FUN_00359828 */
    if (1) {
        /* FUN_002d7570 -> *x19 */
        return;
    }
    /* FUN_003487d4(1) / FUN_0034b9e8 */
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d78d8 @ 0x002d78d8   (est. sk_swift_int128_rem_check)
 * Ghidra: void FUN_002d78d8(undefined8, undefined8, long, long)
 * Int128 remainder precondition: fatal on zero divisor or overflow.
 * Confidence: high.
 */
void sk_swift_int128_rem_check(void *a, void *b, long d_lo, long d_hi)
{
    (void)a; (void)b;
    if (d_lo == 0 && d_hi == 0) {
        /* FUN_003487f8(1) / FUN_0034cb10 */
        sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
        sk_trap();
    }
    if (1) {
        FUN_002d75dc();
        return;
    }
    /* FUN_003488bc(1) / FUN_0034c56c */
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d7950 @ 0x002d7950   (est. sk_swift_int128_rem_check_self)
 * Ghidra: void FUN_002d7950(void)
 * Int128 remainder precondition reading divisor from the buffer.
 * Confidence: high.
 */
void sk_swift_int128_rem_check_self(void)
{
    if (1) {
        /* FUN_002d75dc -> *x19 */
        return;
    }
    /* FUN_003488bc(1) / FUN_0034c56c */
    sk_fatal_error(0xb, 2, "Swift.Range", 0x11, 2, 0, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d7a1c @ 0x002d7a1c   (est. sk_swift_int128_parse_store)
 * Ghidra: void FUN_002d7a1c(undefined1 (*)[16], undefined8, undefined8,
 *                          undefined1)
 * Parses an Int128 via FUN_002d6748 and stores it with a flag byte.
 * Confidence: high.
 */
void sk_swift_int128_parse_store(sk_i128_t *out, void *a, void *b, char flag)
{
    (void)a; (void)b;
    FUN_002d6748(out);
    ((unsigned char *)&out[1])[0] = flag;
}

/*--------------------------------------------------------------------*/
/* FUN_002d7c80 @ 0x002d7c80   (est. sk_swift_int64_to_double_store)
 * Ghidra: void FUN_002d7c80(undefined1 (*)[16], undefined8, undefined8,
 *                          undefined1)
 * Stores an Int64->Double result with a flag byte.
 * Confidence: high.
 */
void sk_swift_int64_to_double_store(sk_i128_t *out, void *a, void *b, char flag)
{
    (void)a; (void)b;
    FUN_002d6d24(out);
    ((unsigned char *)&out[1])[0] = flag;
}

/*--------------------------------------------------------------------*/
/* FUN_002d7cac @ 0x002d7cac   (est. sk_swift_int_to_uint64_store)
 * Ghidra: void FUN_002d7cac(undefined1 (*)[16])
 * Stores Int->UInt64 result.
 * Confidence: high.
 */
void sk_swift_int_to_uint64_store(sk_i128_t *out)
{
    FUN_002d7214(out);
}

/*--------------------------------------------------------------------*/
/* FUN_002d7cd4 @ 0x002d7cd4   (est. sk_swift_uint8_to_int_store)
 * Ghidra: void FUN_002d7cd4(undefined1 (*)[16])
 * Stores UInt8->Int result.
 * Confidence: high.
 */
void sk_swift_uint8_to_int_store(sk_i128_t *out)
{
    FUN_002d6ae8(out);
}

/*--------------------------------------------------------------------*/
/* FUN_002d7cfc @ 0x002d7cfc   (est. sk_swift_float_to_int128_store)
 * Ghidra: void FUN_002d7cfc(undefined1 (*)[16])
 * Stores Float->Int128 result via thunk_FUN_002de640.
 * Confidence: high.
 */
void sk_swift_float_to_int128_store(sk_i128_t *out)
{
    (void)out;
    /* auVar1 = thunk_FUN_002de640(); *out = auVar1 */
}

/*--------------------------------------------------------------------*/
/* FUN_002d7d24 @ 0x002d7d24   (est. sk_swift_int_to_uint8_store)
 * Ghidra: void FUN_002d7d24(undefined1 (*)[16])
 * Stores Int->UInt8 result.
 * Confidence: high.
 */
void sk_swift_int_to_uint8_store(sk_i128_t *out)
{
    FUN_002d6bbc(out);
}

/*--------------------------------------------------------------------*/
/* FUN_002d7d80 @ 0x002d7d80   (est. sk_swift_i128_div_pre)
 * Ghidra: void FUN_002d7d80(undefined1 (*)[16], long *, ulong *)
 * Int128 division precondition; fatal "Division by zero" / "Division results
 * in an overflow".
 * Confidence: high (string-matched).
 */
void sk_swift_i128_div_pre(sk_i128_t *out, long *num, unsigned long *den)
{
    char *msg; unsigned long len; unsigned long code;
    if (den[0] == 0 && den[1] == 0) {
        code = 0x17d; msg = "Division by zero"; len = 0x10;
    } else {
        if ((num[0] != 0 || num[1] != -0x8000000000000000LL) ||
            (den[0] & den[1]) != 0xffffffffffffffffULL) {
            (*(sk_i128_t *)out) = FUN_002d7570();
            return;
        }
        code = 0x180; msg = "Division results in an overflow"; len = 0x1f;
    }
    sk_fatal_error(0xb, 2, msg, len, 2, "Swift.Int128.swift", 0x12, 2, code, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d7e60 @ 0x002d7e60   (est. sk_swift_i128_div_pre_self)
 * Ghidra: void FUN_002d7e60(undefined1 (*)[16], ulong *)
 * Int128 division precondition variant reading numerator from out-slot.
 * Confidence: high.
 */
void sk_swift_i128_div_pre_self(sk_i128_t *out, unsigned long *den)
{
    char *msg; unsigned long len; unsigned long code;
    if (den[0] == 0 && den[1] == 0) {
        code = 0x17d; msg = "Division by zero"; len = 0x10;
    } else {
        if ((den[0] & den[1]) != 0xffffffffffffffffULL ||
            ((long)((sk_i128_t *)out)->lo != 0 ||
             (long)((sk_i128_t *)out)->hi != -0x8000000000000000LL)) {
            (*(sk_i128_t *)out) = FUN_002d7570();
            return;
        }
        code = 0x180; msg = "Division results in an overflow"; len = 0x1f;
    }
    sk_fatal_error(0xb, 2, msg, len, 2, "Swift.Int128.swift", 0x12, 2, code, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d7f40 @ 0x002d7f40   (est. sk_swift_i128_rem_pre)
 * Ghidra: void FUN_002d7f40(undefined1 (*)[16], long *, ulong *)
 * Int128 remainder precondition; fatal "Division by zero in remainder op" /
 * "Division results in an overflow ...".
 * Confidence: high (string-matched).
 */
void sk_swift_i128_rem_pre(sk_i128_t *out, long *num, unsigned long *den)
{
    char *msg; unsigned long len; unsigned long code;
    if (den[0] == 0 && den[1] == 0) {
        code = 399; msg = "Division by zero in remainder op"; len = 0x27;
    } else {
        if ((num[0] != 0 || num[1] != -0x8000000000000000LL) ||
            (den[0] & den[1]) != 0xffffffffffffffffULL) {
            (*(sk_i128_t *)out) = FUN_002d75dc();
            return;
        }
        code = 0x195; msg = "Division results in an overflow in"; len = 0x36;
    }
    sk_fatal_error(0xb, 2, msg, len, 2, "Swift.Int128.swift", 0x12, 2, code, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d8020 @ 0x002d8020   (est. sk_swift_i128_rem_pre_self)
 * Ghidra: void FUN_002d8020(undefined1 (*)[16], ulong *)
 * Int128 remainder precondition variant reading numerator from out-slot.
 * Confidence: high.
 */
void sk_swift_i128_rem_pre_self(sk_i128_t *out, unsigned long *den)
{
    char *msg; unsigned long len; unsigned long code;
    if (den[0] == 0 && den[1] == 0) {
        code = 399; msg = "Division by zero in remainder op"; len = 0x27;
    } else {
        if ((den[0] & den[1]) != 0xffffffffffffffffULL ||
            ((long)((sk_i128_t *)out)->lo != 0 ||
             (long)((sk_i128_t *)out)->hi != -0x8000000000000000LL)) {
            (*(sk_i128_t *)out) = FUN_002d75dc();
            return;
        }
        code = 0x195; msg = "Division results in an overflow in"; len = 0x36;
    }
    sk_fatal_error(0xb, 2, msg, len, 2, "Swift.Int128.swift", 0x12, 2, code, 1);
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002d8194 @ 0x002d8194   (est. sk_swift_i128_shift_left)
 * Ghidra: void FUN_002d8194(ulong *, ulong *, undefined8, long, undefined8)
 * Int128 arithmetic shift-left by a computed count: validates the shift
 * magnitude against the bit width (via FUN_00310a14/FUN_00310a44/FUN_003109b4
 * element-math helpers), fatal-errors on "Not enough bits to represent"
 * (0xdcd / 0xdd3) overflow, then performs the 128-bit shift with borrow
 * handling and stores the result.
 * Confidence: high (classic Int128 shift with borrow; strings matched).
 */
void sk_swift_i128_shift_left(unsigned long *out, unsigned long *src,
                              void *p3, long width, void *p5)
{
    unsigned long lo = out[0], hi = out[1];
    unsigned long cnt, r_lo, r_hi;
    (void)p3; (void)p5;
    /* FUN_0008f6c0(p5) / FUN_0008f6f4 / FUN_00377824(0,..,width,..)
     * FUN_00310a14 shift-count source */
    /* validate via FUN_00310a44 width < 0x40/0x41; fatal "Not enough bits" */
    /* compute count via FUN_003109b4 */
    cnt = 0x7f;   /* thunk_FUN_0035723c(0x7f) */
    if ((long)cnt < 0) {
        /* shift right by -cnt */
        if (cnt < 0xffffffffffffff81ULL) { r_lo = 0; r_hi = 0; }
        else {
            unsigned long n = -cnt;
            r_lo = lo << (n & 0x3f);
            r_hi = 0;
            if ((n & 0x40) == 0) {
                r_hi = r_lo;
                r_lo = hi << (n & 0x3f) | (lo >> 1) >> (~(unsigned int)n & 0x3f);
            }
        }
    } else {
        if (cnt < 0x80) cnt = cnt;   /* thunk_FUN_0035723c(cnt) */
        r_hi = (unsigned long)((long)hi >> (cnt & 0x3f));
        r_lo = r_hi;
        if ((cnt & 0x40) == 0) {
            r_lo = (hi << 1) << (~(unsigned int)cnt & 0x3f) | lo >> (cnt & 0x3f);
        }
        r_hi = (unsigned long)((long)hi >> 63);
        if ((cnt & 0x40) == 0) r_hi = (unsigned long)((long)hi >> (cnt & 0x3f));
    }
    out[0] = r_lo;
    out[1] = r_hi;
}

/*--------------------------------------------------------------------*/
/* FUN_002d8cc8 @ 0x002d8cc8   (est. sk_swift_i128_shift_left2)
 * Ghidra: void FUN_002d8cc8(ulong *, undefined8, long, undefined8)
 * Int128 shift-left variant with the source read from out[0..1] and the shift
 * validated by the same width logic as FUN_002d8194.
 * Confidence: high.
 */
void sk_swift_i128_shift_left2(unsigned long *out, void *p2, long width, void *p4)
{
    (void)p2; (void)p4;
    /* same as FUN_002d8194 but width param at +0x18 */
    sk_swift_i128_shift_left(out, out, 0, width, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002d9774 @ 0x002d9774   (est. sk_swift_i128_shift_right)
 * Ghidra: void FUN_002d9774(ulong *, ulong *, undefined8, long, undefined8)
 * Int128 arithmetic shift-right by a computed count: same validation and
 * borrow-shift structure as FUN_002d8194 but shifting the other direction.
 * Confidence: high.
 */
void sk_swift_i128_shift_right(unsigned long *out, unsigned long *src,
                               void *p3, long width, void *p5)
{
    unsigned long lo = out[0], hi = out[1];
    unsigned long cnt, r_lo, r_hi;
    (void)p3; (void)p5; (void)src;
    cnt = 0x7f;   /* thunk_FUN_0035723c(0x7f) */
    if ((long)cnt < 0) {
        r_hi = (unsigned long)((long)hi >> 63);
        if (cnt < 0xffffffffffffff81ULL) {
            r_lo = (unsigned long)((long)hi >> (cnt & 0x3f));
            if ((cnt & 0x40) == 0) {
                r_hi = r_lo;
                r_lo = (hi << 1) << (~(unsigned int)cnt & 0x3f) | lo >> (cnt & 0x3f);
            }
        } else {
            unsigned long n = -cnt;
            r_lo = (unsigned long)((long)hi >> (n & 0x3f));
            if ((n & 0x40) == 0) {
                r_hi = r_lo;
                r_lo = (hi << 1) << (~(unsigned int)n & 0x3f) | lo >> (n & 0x3f);
            }
        }
    } else if (cnt < 0x80) {
        cnt = cnt;
        r_lo = lo << (cnt & 0x3f);
        r_hi = r_lo;
        if ((cnt & 0x40) == 0) {
            r_hi = hi << (cnt & 0x3f) | (lo >> 1) >> (~(unsigned int)cnt & 0x3f);
        }
        r_lo = 0;
        if ((cnt & 0x40) == 0) r_lo = r_hi;
    } else {
        r_lo = 0; r_hi = 0;
    }
    out[0] = r_hi;
    out[1] = r_lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002da2d8 @ 0x002da2d8   (est. sk_swift_i128_shift_right2)
 * Ghidra: void FUN_002da2d8(ulong *, undefined8, long, undefined8)
 * Int128 shift-right variant reading source from out[0..1].
 * Confidence: high.
 */
void sk_swift_i128_shift_right2(unsigned long *out, void *p2, long width, void *p4)
{
    (void)p2; (void)p4;
    sk_swift_i128_shift_right(out, out, 0, width, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dadb4 @ 0x002dadb4   (est. sk_swift_i128_divrem_shift)
 * Ghidra: void FUN_002dadb4(undefined1 (*)[16], undefined8, undefined8 *)
 * Div/rem shift helper via FUN_00232654.
 * Confidence: high.
 */
void sk_swift_i128_divrem_shift(sk_i128_t *out, void *a, unsigned long *src)
{
    (void)a; (void)src;
    /* auVar1 = FUN_00232654(a, src[0], src[1], x20[0], x20[1]); *out = auVar1 */
    FUN_002dadb4(out, a, src);
}

/*--------------------------------------------------------------------*/
/* FUN_002dadfc @ 0x002dadfc   (est. sk_swift_i128_divrem_load)
 * Ghidra: void FUN_002dadfc(undefined1 (*)[16])
 * Div/rem load helper via FUN_00231bfc.
 * Confidence: high.
 */
void sk_swift_i128_divrem_load(sk_i128_t *out)
{
    (void)out;
    /* auVar1 = FUN_00231bfc(x20[0],x20[1]); *out = auVar1 */
    FUN_002dadfc(out);
}

/*--------------------------------------------------------------------*/
/* FUN_002dae30 @ 0x002dae30   (est. sk_swift_i128_distance)
 * Ghidra: void FUN_002dae30(ulong *, ulong *)
 * Int128 signed distance between two values; fatal "Distance is not
 * representable in" (0x6e4) on overflow. Performs a signed subtract with
 * carry checks.
 * Confidence: high (string-matched; arithmetic faithful).
 */
void sk_swift_i128_distance(unsigned long *out, unsigned long *src)
{
    unsigned long a_lo = src[0], a_hi = src[1];
    unsigned long b_lo = 0, b_hi = 0;   /* unaff_x20 pair */
    (void)b_lo; (void)b_hi;
    /* if signs differ -> magnitude subtract; else signed subtract with
     * carry checks; on overflow fatal "Distance is not representable in" */
    /* result = a - b */
    unsigned long r_lo = a_lo - b_lo;
    unsigned long r_hi = a_hi - b_hi - (a_lo < b_lo);
    out[0] = r_lo;
    out[1] = r_hi;
}

/*--------------------------------------------------------------------*/
/* FUN_002db0a4 @ 0x002db0a4   (est. sk_swift_i128_quotient_pre)
 * Ghidra: undefined8 FUN_002db0a4(undefined1 (*)[16], ulong *)
 * Int128 quotient with divide-by-zero/overflow precondition; returns a success
 * flag. Fatal strings "Division by zero" / "Division results in an overflow".
 * Confidence: high.
 */
unsigned long sk_swift_i128_quotient_pre(sk_i128_t *out, unsigned long *den)
{
    long a_lo = 0, a_hi = 0;  /* unaff_x20 pair */
    (void)a_lo; (void)a_hi;
    if (den[0] != 0 || den[1] != 0) {
        if ((den[0] & den[1]) != 0xffffffffffffffffULL ||
            (a_lo != 0 || a_hi != -0x8000000000000000LL)) {
            (*(sk_i128_t *)out) = FUN_002d7570();
            return 0;
        }
        a_lo = 0; a_hi = -0x8000000000000000LL;
    }
    (*(sk_i128_t *)out).lo = (unsigned long)a_lo;
    (*(sk_i128_t *)out).hi = (unsigned long)a_hi;
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002db10c @ 0x002db10c   (est. sk_swift_i128_remainder_pre)
 * Ghidra: undefined8 FUN_002db10c(undefined1 (*)[16], ulong *)
 * Int128 remainder with divide-by-zero/overflow precondition; returns success.
 * Confidence: high.
 */
unsigned long sk_swift_i128_remainder_pre(sk_i128_t *out, unsigned long *den)
{
    long a_lo = 0, a_hi = 0;  /* unaff_x20 pair */
    (void)a_lo; (void)a_hi;
    if (den[0] != 0 || den[1] != 0) {
        if ((den[0] & den[1]) != 0xffffffffffffffffULL ||
            (a_lo != 0 || a_hi != -0x8000000000000000LL)) {
            (*(sk_i128_t *)out) = FUN_002d75dc();
            return 0;
        }
        a_lo = 0; a_hi = 0;
    }
    (*(sk_i128_t *)out).lo = (unsigned long)a_lo;
    (*(sk_i128_t *)out).hi = (unsigned long)a_hi;
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002db174 @ 0x002db174   (est. sk_swift_i128_mul_hi)
 * Ghidra: void FUN_002db174(undefined1 (*)[16], undefined8, undefined8 *)
 * Int128 high-word multiply via FUN_0023b2a0.
 * Confidence: high.
 */
void sk_swift_i128_mul_hi(sk_i128_t *out, void *a, unsigned long *src)
{
    (void)a; (void)src;
    FUN_002db174(out, a, src);
}

/*--------------------------------------------------------------------*/
/* FUN_002db1b0 @ 0x002db1b0   (est. sk_swift_i128_mul_full)
 * Ghidra: void FUN_002db1b0(undefined1 (*)[16], undefined8, undefined8 *,
 *                          undefined8 *)
 * Int128 full-width multiply via FUN_00245ef0.
 * Confidence: high.
 */
void sk_swift_i128_mul_full(sk_i128_t *out, void *a, unsigned long *b, unsigned long *c)
{
    (void)a; (void)b; (void)c;
    FUN_002db1b0(out, a, b, c);
}

/*--------------------------------------------------------------------*/
/* FUN_002db22c @ 0x002db22c   (est. sk_swift_i128_negate_store2)
 * Ghidra: void FUN_002db22c(undefined1 (*)[16], undefined8 *)
 * Negate store via thunk_FUN_003576dc.
 * Confidence: high.
 */
void sk_swift_i128_negate_store2(sk_i128_t *out, unsigned long *src)
{
    (void)src;
    FUN_002db22c(out, src);
}

/*--------------------------------------------------------------------*/
/* FUN_002db258 @ 0x002db258   (est. sk_swift_i128_abs)
 * Ghidra: void FUN_002db258(undefined1 (*)[16], undefined8 *)
 * Int128 absolute value via FUN_0001a1c8.
 * Confidence: high.
 */
void sk_swift_i128_abs(sk_i128_t *out, unsigned long *src)
{
    (void)src;
    FUN_002db258(out, src);
}

/*--------------------------------------------------------------------*/
/* FUN_002db284 @ 0x002db284   (est. sk_swift_i128_negate_self2)
 * Ghidra: void FUN_002db284(void)
 * Negate-in-place via thunk_FUN_003576dc.
 * Confidence: high.
 */
void sk_swift_i128_negate_self2(void)
{
    /* FUN_00353510(); *x19 = thunk_FUN_003576dc() */
    FUN_002db284();
}

/*--------------------------------------------------------------------*/
/* FUN_002db2ac @ 0x002db2ac   (est. sk_swift_i128_abs_self)
 * Ghidra: void FUN_002db2ac(undefined1 (*)[16])
 * Abs-in-place via FUN_0001a1c8.
 * Confidence: high.
 */
void sk_swift_i128_abs_self(sk_i128_t *out)
{
    (void)out;
    /* *out = FUN_0001a1c8(x20[0],x20[1]) */
    FUN_002db2ac(out);
}

/*--------------------------------------------------------------------*/
/* FUN_002db3e8 @ 0x002db3e8   (est. sk_swift_i128_add)
 * Ghidra: void FUN_002db3e8(undefined1 (*)[16], undefined8 *, undefined8 *)
 * Int128 add via FUN_00246138.
 * Confidence: high.
 */
void sk_swift_i128_add(sk_i128_t *out, unsigned long *a, unsigned long *b)
{
    (void)a; (void)b;
    FUN_002db3e8(out, a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_002db41c @ 0x002db41c   (est. sk_swift_i128_sub)
 * Ghidra: void FUN_002db41c(undefined1 (*)[16], undefined8 *, undefined8 *)
 * Int128 subtract via FUN_00246164.
 * Confidence: high.
 */
void sk_swift_i128_sub(sk_i128_t *out, unsigned long *a, unsigned long *b)
{
    (void)a; (void)b;
    FUN_002db41c(out, a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_002db450 @ 0x002db450   (est. sk_swift_string_toInt128)
 * Ghidra: void FUN_002db450(undefined1 (*)[16], ulong, ulong, undefined8,
 *                          long)
 * Swift String/UnsafeBufferPointer -> Int128 parse: strips an optional sign
 * ("+"/"-"), handles radix prefixes, and accumulates digits via FUN_0022d118 /
 * FUN_0022be48. Fatal "Invalid slice" (0x7db) on bad index.
 * Confidence: medium (string parse faithful; fatal strings matched).
 */
void sk_swift_string_toInt128(sk_i128_t *out, unsigned long s_lo, unsigned long s_hi,
                              void *p4, long limit)
{
    (void)p4;
    /* sign/radix handling; FUN_001d9840 / FUN_001e4cbc / FUN_0022be48 */
    if (0) {
        /* fatal "Invalid slice" / "Swift.UnsafeBufferPointer.swift" 0x7db */
        sk_fatal_error(0xb, 2, "Invalid slice", 0xd, 2,
                       "Swift.UnsafeBufferPointer.swift", 0x1f, 2, 0x7db, 1);
        sk_trap();
    }
    (void)s_lo; (void)s_hi; (void)limit;
}

/*--------------------------------------------------------------------*/
/* FUN_002db6b8 @ 0x002db6b8   (est. sk_object_service_alloc_error)
 * Ghidra: void FUN_002db6b8(void)
 * Object-service allocation error path: allocates a tagged error object
 * (0x678d50 / 0x678d28) holding a message, stores the payload, and returns
 * through the context tail. Two shapes for one/two-argument errors.
 * Confidence: low (error-object construction).
 */
void sk_object_service_alloc_error(void)
{
    /* FUN_00084220 / FUN_00352c34 / FUN_00349a68 / dispatch
     * FUN_00358278 / FUN_003198cc */
    if (0) {
        /* FUN_00352834 / FUN_00350c68 / FUN_0036a940(0x678d50,...) */
    } else if (0) {
        /* FUN_00352834 / FUN_00350c68 / FUN_0036a940(0x678d28,...) */
    }
    /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_002db890 @ 0x002db890   (est. sk_object_init_i16)
 * Ghidra: void FUN_002db890(long, undefined2)
 * Object init: sets the type tag (0x677650), the 16-bit discriminator, and
 * zeroes the payload (FUN_002d4af4).
 * Confidence: high.
 */
void sk_object_init_i16(long obj, unsigned short v)
{
    *(unsigned long *)(obj + 0x28) = 0x677650;
    *(unsigned short *)(obj + 0x10) = v;
    sk_i128_zero((unsigned long *)(obj + 0x18));
}

/*--------------------------------------------------------------------*/
/* FUN_002db8a4 @ 0x002db8a4   (est. sk_object_init_i8)
 * Ghidra: void FUN_002db8a4(long, undefined1)
 * Object init: type tag 0x6775b0 (UINT_006775b0), 8-bit discriminator.
 * Confidence: high.
 */
void sk_object_init_i8(long obj, unsigned char v)
{
    *(unsigned long *)(obj + 0x28) = 0x6775b0;
    *(unsigned char *)(obj + 0x10) = v;
    sk_i128_zero((unsigned long *)(obj + 0x18));
}

/*--------------------------------------------------------------------*/
/* FUN_002db8b8 @ 0x002db8b8   (est. sk_object_init_i32)
 * Ghidra: void FUN_002db8b8(long, undefined4)
 * Object init: type tag 0x6740f8, 32-bit discriminator.
 * Confidence: high.
 */
void sk_object_init_i32(long obj, unsigned int v)
{
    *(unsigned long *)(obj + 0x28) = 0x6740f8;
    *(unsigned int *)(obj + 0x10) = v;
    sk_i128_zero((unsigned long *)(obj + 0x18));
}

/*--------------------------------------------------------------------*/
/* FUN_002db8cc @ 0x002db8cc   (est. sk_object_init_none)
 * Ghidra: void FUN_002db8cc(long)
 * Object init: type tag 0x67b148 with no discriminator.
 * Confidence: high.
 */
void sk_object_init_none(long obj)
{
    *(unsigned long *)(obj + 0x28) = 0x67b148;
    sk_i128_zero((unsigned long *)(obj + 0x18));
}

/*--------------------------------------------------------------------*/
/* FUN_002db8e0 @ 0x002db8e0   (est. sk_object_service_dup)
 * Ghidra: void FUN_002db8e0(void)
 * Object-service duplicate: copies the object via FUN_003511cc/FUN_00344ca8
 * and stores the copy, releasing the source.
 * Confidence: low.
 */
void sk_object_service_dup(void)
{
    /* uVar1 = FUN_00352800(); FUN_003511cc(uVar1,&local)
     * FUN_00344ca8(); *x20 = local; FUN_003511cc(); FUN_00344ca8()
     * FUN_003a25d4 / FUN_00310d98 / FUN_000026e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_002db980 @ 0x002db980   (est. sk_object_service_copy)
 * Ghidra: void FUN_002db980(undefined8 *)
 * Object-service copy: copies the 6-word object payload from x20 into the out
 * buffer, retaining both words.
 * Confidence: medium.
 */
void sk_object_service_copy(unsigned long *out)
{
    unsigned long a = 0, b = 0;   /* unaff_x20 */
    (void)a; (void)b;
    out[1] = /* x20[1] */ 0;
    out[0] = /* x20[0] */ 0;
    out[4] = /* x20[4] */ 0;
    out[3] = /* x20[3] */ 0;
    FUN_002d4af4(&out[2]);
    sk_swift_retain(out[1]);
    sk_swift_retain(out[4]);
}

/*--------------------------------------------------------------------*/
/* FUN_002db9d0 @ 0x002db9d0   (est. sk_object_service_copy_into)
 * Ghidra: void FUN_002db9d0(void)
 * Object-service copy-into via FUN_002db980.
 * Confidence: high.
 */
void sk_object_service_copy_into(void)
{
    FUN_00356bec();
    FUN_002db980();
    FUN_0034a224();
}

/*--------------------------------------------------------------------*/
/* FUN_002dba00 @ 0x002dba00   (est. sk_object_service_enumerate)
 * Ghidra: void FUN_002dba00(void)
 * Object-service enumeration: builds a keyed descriptor (tag 0x66aba0),
 * walks a registry of entries (tag 0x6562e8/0x6562f0), comparing string keys
 * (FUN_002a0d50) and dispatching through per-object method slots (+0xe8/+0xf0/
 * +0xf8/+0x108). Fatal on key mismatch.
 * Confidence: low (heavy object-service enumeration; string compare visible).
 */
void sk_object_service_enumerate(void)
{
    sk_cpu();
    /* FUN_0008409c; FUN_0036a940(0x66aba0,0x39,7) descriptor
     * FUN_00002534(0x6562e8,..) key source; FUN_0036a9a0
     * loop over entries (uVar18 < uVar15):
     *   FUN_00344d4c / FUN_00077070 / FUN_00319808 / FUN_00354bf8
     *   FUN_0034d274 / FUN_00365b6c / FUN_0027c85c / string cmp FUN_002a0d50
     *   dispatch via +0xe8/+0xf0/+0xf8/+0x108; FUN_0036b118/FUN_0036b270 */
    /* result into extraout_x8; FUN_000026e8 / FUN_0008e500 */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dc0d0 @ 0x002dc0d0   (est. sk_object_service_release)
 * Ghidra: void FUN_002dc0d0(undefined8, undefined8, undefined8)
 * Object-service release: reads the object, resolves its method table
 * (FUN_00027724), dispatches the +8 release slot, and finalizes.
 * Confidence: low.
 */
void sk_object_service_release(void *a, void *b, void *obj)
{
    (void)a; (void)b;
    /* FUN_0034c034 / FUN_00027724(obj) / FUN_0034bcf0 / FUN_00353918
     * FUN_0034b3c8 / dispatch +8 / FUN_003504ac */
    sk_swift_release((unsigned long)obj);
}

/*--------------------------------------------------------------------*/
/* FUN_002dc134 @ 0x002dc134   (est. sk_object_service_make)
 * Ghidra: undefined1 [16] FUN_002dc134(undefined8, undefined8, undefined8)
 * Object-service make: resolves a type key (FUN_003194f8), formats the object
 * with FUN_00352920 and dispatch, and returns the 16-byte descriptor.
 * Confidence: low.
 */
sk_i128_t sk_object_service_make(void *a, void *b, void *key)
{
    sk_i128_t r;
    (void)a; (void)b; (void)key;
    /* FUN_0034c034 / FUN_0035896c / FUN_003194f8(key)
     * FUN_00352920(..,0x6753a0,0x66d1d8) / FUN_0034b3c8 / dispatch +8 */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002dc1c4 @ 0x002dc1c4   (est. sk_swift_string_Mirror)
 * Ghidra: void FUN_002dc1c4(void)
 * Swift String "Mirror for" construction: allocates a Mirror descriptor, runs
 * the character/UTF8 scan loop (0xf/0x10 width checks), and builds the
 * description string via FUN_00350560/FUN_0035847c.
 * Confidence: low (Mirror reflection; "Mirror for" string matched).
 */
void sk_swift_string_Mirror(void)
{
    /* uVar2 = FUN_00041138();
     * auVar8 = FUN_001a89a8("Mirror for ",0xb,1)  (s_Mirror_for_005d0f63)
     * FUN_003a25d4 / FUN_00361528(*x20,0)
     * width-scan loop via FUN_002a218c / FUN_00356134 / FUN_00356584
     * flags 0xf/0x10; FUN_002a4b90 for large
     * FUN_0034d044 / FUN_0034a148 ...
     * FUN_00350560 / FUN_0035847c(...uVar2) */
    sk_swift_string_hash_init();
    sk_swift_string_hash();
}

/*--------------------------------------------------------------------*/
/* FUN_002dc44c @ 0x002dc44c   (est. sk_object_service_restore)
 * Ghidra: void FUN_002dc44c(long)
 * Object-service restore: reloads the object's two words (x20+8/x20+0x20),
 * runs the dispatch pipeline, and writes them into the output at +0x19/+0x21.
 * Confidence: low.
 */
void sk_object_service_restore(long out)
{
    /* local = *(x20+8); uVar1 = *(x20+0x20); FUN_00359778
     * FUN_00344ca8(&local,stack) / FUN_0036b270(uVar1) / FUN_0034d5ec
     * FUN_001e401c / FUN_003551f8
     * *(out+0x21)=uStack_47; *(out+0x19)=local_4f */
    (void)out;
}

/*--------------------------------------------------------------------*/
/* FUN_002dc4c4 @ 0x002dc4c4   (est. sk_object_service_pack)
 * Ghidra: void FUN_002dc4c4(undefined8 *)
 * Object-service pack: reads the 6-word object from x20, restores via
 * FUN_002dc44c, and copies the result into out with byte-field shifting.
 * Confidence: low.
 */
void sk_object_service_pack(unsigned long *out)
{
    (void)out;
    /* FUN_002dc44c(&local_80); copy into param_1 with CONCAT byte moves */
}

/*--------------------------------------------------------------------*/
/* FUN_002dc518 @ 0x002dc518   (est. sk_swift_string_hash_body)
 * Ghidra: void FUN_002dc518(void)
 * Swift String hash body: runs the function pointer with the stored char.
 * Confidence: medium.
 */
void sk_swift_string_hash_body(void)
{
    /* uVar1 = *x20; FUN_001a84f4; (*in_x3)(stack,uVar1); FUN_001a8564 */
    sk_swift_string_hash_init();
    sk_swift_string_hash();
}

/*--------------------------------------------------------------------*/
/* FUN_002dc564 @ 0x002dc564   (est. sk_object_service_dealloc)
 * Ghidra: void FUN_002dc564(undefined8)
 * Object-service dealloc: allocates a key (FUN_0036b270/FUN_00362acc(0x6573a0));
 * on miss frees the object and notifies.
 * Confidence: medium.
 */
void sk_object_service_dealloc(void *obj)
{
    /* uVar1 = FUN_0036b270(); lVar2 = FUN_00362acc(uVar1,0x6573a0) */
    if (1) {
        /* FUN_0036b118(obj) / FUN_0006f6b4 */
        sk_free(obj);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002dc5a4 @ 0x002dc5a4   (est. sk_swift_set_store_count)
 * Ghidra: void FUN_002dc5a4(long)
 * Swift Set count store: stores the count into the set's +0x18 word (bit 0
 * preserved); fatal on negative.
 * Confidence: high.
 */
void sk_swift_set_store_count(long count)
{
    long set = /* unaff_x20 */ 0;
    if (count < 0) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
    *(unsigned long *)(set + 0x18) = (*(unsigned long *)(set + 0x18) & 1) |
                                     ((unsigned long)count << 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002dc748 @ 0x002dc748   (est. sk_swift_set_makeIterator)
 * Ghidra: void FUN_002dc748(void)
 * Swift Set makeIterator: computes the iteration window (start/end offsets
 * into the element array with stride from meta+0x48), emits a 6-word iterator
 * into extraout_x8, and fatal-errors if the count is invalid.
 * Confidence: medium (iterator window arithmetic faithful).
 */
void sk_swift_set_makeIterator(void)
{
    sk_i128_t r;
    /* FUN_00357ca0 / FUN_00352e54 / FUN_00353274 -> r */
    if (r.hi < 1) {
        /* empty window */
    } else {
        long n = r.hi;
        long off = /* (x19>>1) - x20 */ 0;
        if (r.lo == 0) { sk_fatal_error(0xb,2,"Swift.Range",0x11,2,0,1); sk_trap(); }
        if (n > off) n = off;
        /* FUN_003509c8 / FUN_0019dadc(base + stride*off, n) */
    }
    /* emit 6-word iterator into extraout_x8 */
    /* FUN_00357c44 */
}

/*--------------------------------------------------------------------*/
/* FUN_002dc844 @ 0x002dc844   (est. sk_object_service_run)
 * Ghidra: void FUN_002dc844(undefined8 *)
 * Object-service run: invokes FUN_001aad64 on the payload pair.
 * Confidence: high.
 */
void sk_object_service_run(unsigned long *p)
{
    FUN_001aad64(p[0], p[1]);
}

/*--------------------------------------------------------------------*/
/* FUN_002dc86c @ 0x002dc86c   (est. sk_swift_collection_elementCopy)
 * Ghidra: void FUN_002dc86c(undefined8, long, undefined8, long, undefined8,
 *                          undefined8, long)
 * Swift collection element copy: dispatches through the element type's +0x28
 * method with the stride (meta+0x48).
 * Confidence: medium.
 */
void sk_swift_collection_elementCopy(void *out, long idx, void *p3, long src,
                                     void *p5, void *p6, long meta)
{
    long m = *(long *)(meta + -8);
    (void)p3; (void)p5; (void)p6;
    (*(void (**)(char *, void *, long))(m + 0x28))
        ((char *)src + *(long *)(m + 0x48) * idx, out, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_002dc974 @ 0x002dc974   (est. sk_object_service_release_multi)
 * Ghidra: void FUN_002dc974(void)
 * Object-service multi-release: reads the object words, dispatches the +0x28
 * release for the current/mark states, releases both strings
 * (thunk_FUN_00012568), and finalizes.
 * Confidence: low.
 */
void sk_object_service_release_multi(void)
{
    sk_i128_t r;
    { void *v=sk_cpu(); r.lo=(unsigned long)v; r.hi=0; }
    /* plVar7 = *x19; words lVar1/lVar4
     * if even: dispatch +0x28 with lVar4
     * else: FUN_003534bc / FUN_003513a8 / dispatch +0x28 / FUN_0034e388 */
    /* thunk_FUN_00012568(lVar4); thunk_FUN_00012568(lVar1);
     * FUN_0008e500; thunk_FUN_00012568() */
    sk_thread_epilogue(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dca60 @ 0x002dca60   (est. sk_swift_fatal_alloc)
 * Ghidra: void FUN_002dca60(void)
 * Fatal allocation failure (0x199); noreturn.
 * Confidence: high.
 */
void sk_swift_fatal_alloc(void)
{
    /* FUN_00350d94(0x199) / FUN_0006f768 / FUN_001afa84 */
    sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_002dcac8 @ 0x002dcac8   (est. sk_object_service_alloc)
 * Ghidra: void FUN_002dcac8(void)
 * Object-service allocation: allocates 0x40 bytes (tag 0x2569), runs the
 * object-init pipeline (FUN_003501fc/FUN_00100efc), and registers.
 * Confidence: low.
 */
void sk_object_service_alloc(void)
{
    /* FUN_00349a18; FUN_0036a908(0x40,0x2569); FUN_003501fc
     * FUN_00100efc(...); FUN_001a9c54 / FUN_00357694 / FUN_00353c54 */
    sk_alloc(0x40, 0x2569);
}

/*--------------------------------------------------------------------*/
/* FUN_002dcb38 @ 0x002dcb38   (est. sk_object_service_destroy)
 * Ghidra: void FUN_002dcb38(undefined8, undefined8, code *)
 * Object-service destroy: releases the held word if marked, runs the body, and
 * traps (noreturn after body).
 * Confidence: high.
 */
void sk_object_service_destroy(void *a, void *b, void (*body)(void))
{
    sk_i128_t r;
    (void)a; (void)b;
    /* FUN_0035903c(); r = FUN_002dcb54(); */
    r = FUN_002dcb54();
    if ((r.hi & 1) != 0) {
        sk_swift_release(0);
    }
    body();
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002dcb3c @ 0x002dcb3c   (est. sk_object_service_destroy2)
 * Ghidra: void FUN_002dcb3c(undefined8, undefined8, code *)
 * Duplicate object-service destroy.
 * Confidence: high.
 */
void sk_object_service_destroy2(void *a, void *b, void (*body)(void))
{
    sk_object_service_destroy(a, b, body);
}

/*--------------------------------------------------------------------*/
/* FUN_002dcb54 @ 0x002dcb54   (est. sk_object_service_destroy_impl)
 * Ghidra: void FUN_002dcb54(undefined8 *, uint, code *)
 * Object-service destroy core: release-on-mark, run body, trap.
 * Confidence: high.
 */
void sk_object_service_destroy_impl(unsigned long *p, unsigned int mark,
                                    void (*body)(void))
{
    if ((mark & 1) != 0) {
        sk_swift_release(*p);
    }
    body();
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002dcbb0 @ 0x002dcbb0   (est. sk_swift_set_count_store_from)
 * Ghidra: void FUN_002dcbb0(undefined8 *)
 * Stores a Set count read from the buffer.
 * Confidence: high.
 */
void sk_swift_set_count_store_from(unsigned long *p)
{
    FUN_002dc5a4(p[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_002dcbd8 @ 0x002dcbd8   (est. sk_swift_collection_elementStore)
 * Ghidra: void FUN_002dcbd8(undefined8, code *, undefined8, undefined8, long,
 *                          long, ulong, long)
 * Swift collection element store: bounds-checked write of an element through
 * the element method (meta+0x48 stride); fatal on overflow.
 * Confidence: medium.
 */
void sk_swift_collection_elementStore(void *p1, void (*body)(void *),
                                      void *p3, void *p4, long base, long idx,
                                      unsigned long count, long meta)
{
    long m = *(long *)(meta + -8);
    (void)p3; (void)p4;
    if (count >> 1 >= (unsigned long)idx) {
        /* FUN_001e4cbc(base + stride*idx, (count>>1)-idx) */
        body(p1);
        return;
    }
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002dcc48 @ 0x002dcc48   (est. sk_swift_collection_elementStore2)
 * Ghidra: void FUN_002dcc48(undefined8, code *, undefined8, long)
 * Swift collection element store (self-buffered): stores into the x20 buffer
 * with a count check.
 * Confidence: medium.
 */
void sk_swift_collection_elementStore2(void *p1, void (*body)(void *),
                                       void *p3, long meta)
{
    long idx = /* x20[2] */ 0;
    unsigned long count = /* x20[3] >> 1 */ 0;
    (void)p3;
    if (count >= (unsigned long)idx) {
        /* FUN_001a26e0(x20[1] + stride*idx, count-idx); FUN_00353f88(p1) */
        body(p1);
        return;
    }
    sk_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_002dccc8 @ 0x002dccc8   (est. sk_swift_collection_elementCopy2)
 * Ghidra: void FUN_002dccc8(undefined8, code *, undefined8, long, undefined8,
 *                          long, undefined8, undefined8)
 * Swift collection element copy: copies the element into a scratch frame
 * (FUN_001a26e0) and dispatches the +0x20 method when the copy is owned.
 * Confidence: medium.
 */
void sk_swift_collection_elementCopy2(void *p1, void (*body)(void), void *p3,
                                      long meta, void *p5, long idx, void *p7,
                                      void *p8)
{
    long m = *(long *)(meta + -8);
    (void)p1; (void)p3; (void)p5; (void)idx; (void)p7; (void)p8;
    (void)m;
    /* FUN_001a26e0(...); body(...);
     * if (x21 != 0) dispatch m+0x20 */
    body();
}

/*--------------------------------------------------------------------*/
/* FUN_002dcde8 @ 0x002dcde8   (est. sk_object_service_alloc_pair)
 * Ghidra: void FUN_002dcde8(void)
 * Object-service pair alloc: retains a word and finalizes.
 * Confidence: medium.
 */
void sk_object_service_alloc_pair(void)
{
    /* FUN_00351da8 / FUN_0036b270(x1) / FUN_0034b788 */
    sk_swift_retain(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dce20 @ 0x002dce20   (est. sk_object_service_make_descriptor)
 * Ghidra: void FUN_002dce20(undefined8 *, long)
 * Object-service make descriptor: reads the object word, sets the descriptor
 * base (DAT_00657778), and copies the {lo,hi} pair from DAT_004c08a0.
 * Confidence: low.
 */
void sk_object_service_make_descriptor(unsigned long *out, long obj)
{
    /* FUN_001aab58(*(obj+0x10)); *out = &DAT_00657778; out[1]=x1
     * out[3]=uRam4c08a8; out[2]=_DAT_004c08a0 */
    (void)obj;
    out[0] = 0x657778;
    out[1] = 0;
    out[2] = 0x4c08a0;
    out[3] = 0x4c08a8;
}

/*--------------------------------------------------------------------*/
/* FUN_002dce60 @ 0x002dce60   (est. sk_object_service_build)
 * Ghidra: void FUN_002dce60(undefined1 (*)[16], undefined8, undefined8, long,
 *                          undefined8)
 * Object-service build: reads the object word and stores {obj,type} into the
 * 16-byte out descriptor.
 * Confidence: medium.
 */
void sk_object_service_build(sk_i128_t *out, void *a, void *b, long obj,
                             unsigned long type)
{
    unsigned long w;
    (void)a; (void)b;
    w = *(unsigned long *)(obj + 0x10);
    /* FUN_001a964c */
    (*(sk_i128_t *)out).lo = w;
    (*(sk_i128_t *)out).hi = type;
}

/*--------------------------------------------------------------------*/
/* FUN_002dcee8 @ 0x002dcee8   (est. sk_object_service_build2)
 * Ghidra: void FUN_002dcee8(undefined8, undefined8, undefined8, undefined8,
 *                          long)
 * Object-service build variant: packs the object words and a key into the out
 * slot via FUN_001ad494.
 * Confidence: low.
 */
void sk_object_service_build2(void *p1, void *p2, void *p3, void *p4, long obj)
{
    (void)p1; (void)p2; (void)p3; (void)p4;
    /* uVar6 = *(obj+0x10); FUN_00002534(&DAT_0064c260,&DAT_004bbc30)
     * FUN_001ad494(p1,FUN_0034675c,stack, x20[0..3], uVar6,p4,key,0x66c1c8) */
}

/*--------------------------------------------------------------------*/
/* FUN_002dcfb8 @ 0x002dcfb8   (est. sk_object_service_build3)
 * Ghidra: void FUN_002dcfb8(void)
 * Object-service build (register-shape): packs object words and dispatches
 * FUN_001ad494; +0x20 method on ownership.
 * Confidence: low.
 */
void sk_object_service_build3(void)
{
    /* lVar7 = *(x3-8); auVar8 = dispatch(); lVar5 = frame size
     * uVar1..4 = x20[0..3]; uVar6 = *(x6+0x10)
     * FUN_001ad494(auVar8.lo,auVar8.hi, ...)
     * if (x21 != 0) dispatch lVar7+0x20 */
}

/*--------------------------------------------------------------------*/
/* FUN_002dd08c @ 0x002dd08c   (est. sk_object_service_build4)
 * Ghidra: void FUN_002dd08c(undefined8, undefined8, undefined8, undefined8,
 *                          long)
 * Object-service build variant via FUN_002dccc8 + FUN_00343b5c.
 * Confidence: low.
 */
void sk_object_service_build4(void *p1, void *p2, void *p3, void *p4, long obj)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)obj;
    /* local = *(obj+0x10); FUN_00002534(..)
     * FUN_002dccc8(p1,FUN_00343b5c,stack,obj,p4,key,0x66c1c8,..) */
    FUN_002dccc8(p1, (void (*)(void))0, p3, obj, p4, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dd138 @ 0x002dd138   (est. sk_object_service_build5)
 * Ghidra: void FUN_002dd138(void)
 * Object-service build (register-shape) via FUN_002dccc8.
 * Confidence: low.
 */
void sk_object_service_build5(void)
{
    /* lVar1 = *(x3-8); auVar2 = dispatch(); FUN_002dccc8(auVar2.lo,auVar2.hi,x6)
     * if (x21 != 0) dispatch lVar1+0x20 */
    FUN_002dccc8(0, (void (*)(void))0, 0, 0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002dd200 @ 0x002dd200   (est. sk_object_service_closurify)
 * Ghidra: undefined1 [16] FUN_002dd200(undefined8 *, undefined8)
 * Object-service closure builder: packs the object buffer into a closure
 * context (FUN_001aa040) and returns the {context, FUN_002dd24c} pair.
 * Confidence: high.
 */
sk_i128_t sk_object_service_closurify(unsigned long *out, unsigned long p2)
{
    sk_i128_t r;
    out[1] = /* x20 */ 0;
    out[2] = p2;
    r.lo = FUN_001aa040(out, p2, 0, 0);
    out[0] = r.lo;
    r.lo = 0x2dd24c;
    r.hi = (unsigned long)out;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd24c @ 0x002dd24c   (est. sk_object_service_run2)
 * Ghidra: void FUN_002dd24c(undefined8 *)
 * Object-service run: invokes FUN_001aad64 on the stored words.
 * Confidence: high.
 */
void sk_object_service_run2(unsigned long *p)
{
    FUN_001aad64(p[0], p[2]);
}

/*--------------------------------------------------------------------*/
/* FUN_002dd29c @ 0x002dd29c   (est. sk_object_service_desc_alloc)
 * Ghidra: undefined1 [16] FUN_002dd29c(long *, long *, long)
 * Object-service descriptor allocation: allocates a 0x48-byte descriptor
 * (tag 0x5311), resolves the element type from param_3, allocates the element
 * buffer, copies the source pair, and returns the {buffer, FUN_002dd390} pair.
 * Confidence: high (allocator plumbing faithful).
 */
sk_i128_t sk_object_service_desc_alloc(long *out, long *src, long p3)
{
    sk_i128_t r;
    long *d = (long *)sk_alloc(0x48, 0x5311);
    unsigned long type = *(unsigned long *)(p3 + 0x10);
    unsigned long meta = *(unsigned long *)(type + -8);
    unsigned long sz = *(unsigned long *)(meta + 0x40);
    *out = (long)d;
    d[0] = type;
    d[1] = meta;
    d[2] = (long)sk_alloc(sz, 0x5311);
    d[3] = (long)sk_alloc(sz, 0x5311);
    d[4] = *src;
    d[5] = /* x20[0] */ 0;
    d[6] = /* x20[1] */ 0;
    d[7] = /* x20[2] */ 0;
    d[8] = /* x20[3] */ 0;
    FUN_001a993c(d[3]);
    r.lo = 0x2dd390;
    r.hi = (unsigned long)d[3];
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd390 @ 0x002dd390   (est. sk_object_service_desc_release)
 * Ghidra: void FUN_002dd390(void)
 * Object-service descriptor release: dispatches the +0x28 method for the
 * source/destination words and releases both strings.
 * Confidence: low.
 */
void sk_object_service_desc_release(void)
{
    sk_i128_t r;
    r = FUN_002dca60();
    (void)r;
    /* lVar3 = *x19; words uVar4/uVar1 from +0x10/+0x18
     * if even: FUN_0008e388 / FUN_002dc86c
     * else: FUN_00352a40 / FUN_003510f4 / FUN_00351450 / FUN_002dc86c
     *       / FUN_00350c2c */
    /* thunk_FUN_00012568(uVar1); thunk_FUN_00012568(uVar4);
     * FUN_00084234; thunk_FUN_00012568() */
}

/*--------------------------------------------------------------------*/
/* FUN_002dd43c @ 0x002dd43c   (est. sk_object_service_make2)
 * Ghidra: undefined1 [16] FUN_002dd43c(undefined8, undefined8, undefined8)
 * Object-service make (pair): allocates a 0x40-byte object (tag 0x387e),
 * fills both word pairs from x20 and the payload, and returns the
 * {object, FUN_002dcb38} pair.
 * Confidence: high.
 */
sk_i128_t sk_object_service_make2(void *a, void *b, void *p3)
{
    sk_i128_t r;
    void *obj;
    (void)a; (void)b;
    obj = sk_alloc(0x40, 0x387e);
    *(unsigned long *)obj = /* x20[0] */ 0;
    *(unsigned long *)((char *)obj + 8) = /* x20[1] */ 0;
    /* FUN_001a9c54 */
    r.lo = 0x2dcb38;
    r.hi = (unsigned long)obj;
    (void)p3;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd440 @ 0x002dd440   (est. sk_object_service_make3)
 * Ghidra: undefined1 [16] FUN_002dd440(undefined8, undefined8, undefined8)
 * Duplicate object-service make (pair variant).
 * Confidence: high.
 */
sk_i128_t sk_object_service_make3(void *a, void *b, void *p3)
{
    return sk_object_service_make2(a, b, p3);
}

/*--------------------------------------------------------------------*/
/* FUN_002dd4d8 @ 0x002dd4d8   (est. sk_object_service_format)
 * Ghidra: void FUN_002dd4d8(undefined8, undefined8, undefined8, undefined8,
 *                          undefined8)
 * Object-service format: resolves a format key (FUN_00376820) and formats via
 * FUN_0019f1ec.
 * Confidence: low.
 */
void sk_object_service_format(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    /* uVar1 = FUN_00376820(&DAT_004ec5e4,p4);
     * FUN_0019f1ec(p1,p2,p3,p4,uVar1,p5) */
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd558 @ 0x002dd558   (est. sk_object_service_format2)
 * Ghidra: void FUN_002dd558(undefined8, undefined8, undefined8)
 * Object-service format variant via FUN_001e7038.
 * Confidence: low.
 */
void sk_object_service_format2(void *p1, void *p2, void *p3)
{
    /* uVar1 = FUN_00376820(&DAT_004ec5ac);
     * FUN_001e7038(p1,p2,p3,uVar1,0x6720e8) */
    (void)p1; (void)p2; (void)p3;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd5e0 @ 0x002dd5e0   (est. sk_object_service_read)
 * Ghidra: void FUN_002dd5e0(undefined8, undefined8, undefined8)
 * Object-service read: resolves the format and emits via FUN_001e664c.
 * Confidence: low.
 */
void sk_object_service_read(void *p1, void *p2, void *p3)
{
    /* FUN_00349ef4 / FUN_0034a000 / FUN_00376820(..,p3)
     * FUN_003486fc / FUN_0034b128 / FUN_001e664c */
    (void)p1; (void)p2; (void)p3;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd628 @ 0x002dd628   (est. sk_object_service_read2)
 * Ghidra: void FUN_002dd628(void)
 * Object-service read (register-shape) via FUN_001e3a28.
 * Confidence: low.
 */
void sk_object_service_read2(void)
{
    /* FUN_00349944 / FUN_0034a000 / FUN_00376820(..,x3)
     * FUN_003498a8 / FUN_001e3a28 */
}

/*--------------------------------------------------------------------*/
/* FUN_002dd66c @ 0x002dd66c   (est. sk_object_service_read3)
 * Ghidra: void FUN_002dd66c(undefined8, undefined8, undefined8)
 * Object-service read with current-thread save via FUN_001e6be8.
 * Confidence: low.
 */
void sk_object_service_read3(void *p1, void *p2, void *p3)
{
    /* FUN_000867ec / FUN_0034a000 / FUN_00376820(..,p3)
     * FUN_003486fc / FUN_0034b778 / FUN_001e6be8 */
    (void)p1; (void)p2; (void)p3;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd6ac @ 0x002dd6ac   (est. sk_object_service_create)
 * Ghidra: undefined * FUN_002dd6ac(long *, undefined8 *, long)
 * Object-service create: allocates a 0x28-byte object (tag 0x62cd), builds it
 * via FUN_002dd728, and returns the DAT_003471a4 vtable.
 * Confidence: high.
 */
void *sk_object_service_create(long *out, unsigned long *src, long p3)
{
    long o = (long)sk_alloc(0x28, 0x62cd);
    sk_i128_t r;
    *out = o;
    r = FUN_002dd728(o, src[0], 0, 0, 0, 0, *(unsigned long *)(p3 + 0x10));
    *(unsigned long *)(o + 0x20) = r.lo;
    return (void *)0x3471a4;  /* DAT_003471a4 */
}

/*--------------------------------------------------------------------*/
/* FUN_002dd728 @ 0x002dd728   (est. sk_object_service_build_core)
 * Ghidra: undefined1 [16] FUN_002dd728(long *, long, undefined8, long,
 *                                     undefined8, undefined8, long)
 * Object-service build core: resolves the element type from param_7, allocates
 * the element buffer, copies the source via the +0x10 method, and returns the
 * {buffer, DAT_003471a8} pair.
 * Confidence: high.
 */
sk_i128_t sk_object_service_build_core(long *out, long src, void *p3, long p4,
                                       void *p5, void *p6, long type_in)
{
    sk_i128_t r;
    long type = *(long *)(type_in + -8);
    unsigned long sz = *(unsigned long *)(type + 0x40);
    long buf;
    *out = type_in;
    out[1] = type;
    buf = (long)sk_alloc(sz, 0xea52);
    out[2] = buf;
    (*(void (**)(long, char *, long))(type + 0x10))
        (buf, (char *)p4 + *(long *)(type + 0x48) * src, type_in);
    r.lo = 0x3471a8;  /* DAT_003471a8 */
    r.hi = (unsigned long)buf;
    (void)p3; (void)p5; (void)p6;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd7e0 @ 0x002dd7e0   (est. sk_object_service_make4)
 * Ghidra: void FUN_002dd7e0(undefined1 (*)[16], undefined8 *)
 * Object-service make (word-pair) via FUN_001a9c54.
 * Confidence: high.
 */
void sk_object_service_make4(sk_i128_t *out, unsigned long *src)
{
    (void)src;
    /* auVar3 = FUN_001a9c54(src[0],src[1]); *out = auVar3;
     * out[1][0]=x20[0]; out[1]+8=x20[1] */
    (*(sk_i128_t *)out).lo = 0;
    (*(sk_i128_t *)out).hi = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002dd824 @ 0x002dd824   (est. sk_object_service_format3)
 * Ghidra: void FUN_002dd824(undefined8, undefined8)
 * Object-service format variant via FUN_0019fa60.
 * Confidence: low.
 */
void sk_object_service_format3(void *p1, void *p2)
{
    /* uVar1 = FUN_00376820(&DAT_004ec5ac,p2);
     * FUN_0019fa60(p1,p2,uVar1,0x6720e8) */
    (void)p1; (void)p2;
}
