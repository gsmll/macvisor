/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched. This file covers the 0x1f0000
 * sub-range (scheduler / thread / preemption machinery). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ---------------- external dependencies (other sub-ranges / earlier regions) ---------------- */
typedef uint64_t word_t;
typedef uint64_t cap_t;
typedef uint64_t vptr_t;
typedef uint64_t pptr_t;

/* Ghidra decompiler primitive type aliases (compile-fix typedefs). */
typedef uint64_t ulong;
typedef uint64_t undefined;
typedef uint64_t undefined8;
typedef uint8_t  undefined1;
typedef uint8_t  byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef unsigned __int128 uint128_t;

/* 16-byte object descriptor {data ptr, method table}; 8-byte find result. */
typedef struct { word_t lo; word_t hi; } cl4_desc_t;
typedef struct { word_t index; ulong found; } cl4_find_t;

/* Ghidra pseudocode primitives rendered in C (decompiler artifacts). */
#define SCARRY8(a,b)        (__builtin_add_overflow((a),(b),(unsigned long[1]){0}))
#define SBORROW8(a,b)       (__builtin_sub_overflow((a),(b),(unsigned long[1]){0}))
#define LZCOUNT(x)          ((unsigned)__builtin_clzll((unsigned long long)(x)))
#define ABS(x)              ((x) < 0 ? -(x) : (x))
#define ZEXT816(x)          ((cl4_find_t){ .index = 0, .found = (x) })
static inline word_t bitrev_word(word_t x) {
    x = (x & 0xaaaaaaaaaaaaaaaa) >> 1 | (x & 0x5555555555555555) << 1;
    x = (x & 0xcccccccccccccccc) >> 2 | (x & 0x3333333333333333) << 2;
    x = (x & 0xf0f0f0f0f0f0f0f0) >> 4 | (x & 0xf0f0f0f0f0f0f0f) << 4;
    x = (x & 0xff00ff00ff00ff00) >> 8 | (x & 0xff00ff00ff00ff) << 8;
    x = (x & 0xffff0000ffff0000) >> 0x10 | (x & 0xffff0000ffff) << 0x10;
    return (x >> 0x20 | x << 0x20);
}
/* Ghidra `code *` = pointer to a void(void) function. */
typedef void code(void);

/* Fallback decompile helpers shared across the range (Ghidra FUN_ addresses). */
extern word_t FUN_0006b6f4(word_t);            /* 0x6b6f4 */
extern word_t FUN_00084024(word_t);            /* 0x84024 */
extern word_t FUN_0008e518(void);              /* 0x8e518 */
extern word_t FUN_00310d98(word_t, word_t);    /* 0x310d98 */
extern word_t FUN_0031a29c(word_t, word_t, word_t, word_t); /* 0x31a29c */
extern word_t FUN_0031b560(void);              /* 0x31b560 */
extern void   FUN_001f99f4(word_t, word_t, word_t); /* 0x1f99f4 (this range) */
extern void   FUN_001f0700(void);              /* 0x1f0700 (this range) */

/* FUN_001f00ac @ 0x001f00ac   (est. cl4_thread_free_cb)
 * Ghidra: void FUN_001f00ac(long *param_1)
 * Releases a thread-control structure: dispatches through the object's method
 * vector (offsets 0x58/0x48/0x50/0x60) to drop associated resources, then
 * frees two backing allocations. Called from completion callbacks in this range.
 * Confidence: low
 * Notes: indirect method-table dispatch; FUN_0006b6f4/FUN_0035354c callees. */
void cl4_thread_free_cb(long *obj)
{
    code *finish_cb = *(code **)(*obj + 0x58);
    long   inner   = *(long *)(*obj + 0x48);
    word_t inner2  = *(word_t *)(*obj + 0x50);

    (**(code **)(*obj + 0x60))(*obj + 0x20, 0);      /* drop hook */
    FUN_0006b6f4(*(word_t *)(inner + 8));
    finish_cb();
    FUN_0035354c();
    finish_cb();
    cl4_obj_release(inner2);                          /* thunk_FUN_00012568 */
    cl4_obj_release(*obj);                            /* thunk_FUN_00012568 */
}

/* FUN_001f0130 @ 0x001f0130   (est. cl4_sched_run_queue_drain)
 * Ghidra: void FUN_001f0130(void)
 * Drains a run/ready queue: iterates the queue anchored at the per-cpu sched
 * context (offset 0x10 = count), pulling and running each entry, then tears
 * down the context. Entry loop invokes the shared run-dispatch and the
 * preemption/requeue hooks.
 * Confidence: low
 * Notes: decompiler-mangled register-passed state (extraout_x*); FUN_001f0700
 *   requeues, FUN_001f99f4 dispatches; SoftwareBreakpoint(1) overflow check. */
void cl4_sched_run_queue_drain(void)
{
    FUN_0008e518();
    long ctx = FUN_0034cf24();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348f38();
    FUN_00349b3c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_00348f50();
    FUN_003515b4(0);
    long rq = FUN_003722e4();
    FUN_0034ab20();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0d4();
    FUN_00077894(*(word_t *)(ctx + 0x10));
    FUN_001ee140();
    if (*(long *)(ctx + 0x10) != 0) {
        long n = 0;
        int stride = *(int *)(rq + 0x30);
        do {
            word_t ent = FUN_003534f8();
            FUN_0019ea20(ent, extraout_x9, rq);
            long next = n + 1;
            if (SCARRY8(n, 1)) {          /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f031c);
            }
            FUN_00357170();
            FUN_0035190c();
            (*(code **)(extraout_x16 + 0x20))(unaff_x24, unaff_x27 + stride, unaff_x21);
            FUN_001f99f4(auVar8._0_8_, auVar8._8_8_, unaff_x20);
            if ((extraout_x1 & 1) != 0) { /* entry completed -> requeue path */
                FUN_00350410();
                FUN_003488bc();
                FUN_0006f768();
                FUN_0035110c();           /* WARNING: subroutine does not return */
                FUN_001afe4c();
            }
            FUN_003513a8();
            FUN_001f0700();
            n = n + 1;
            ctx = extraout_x9;
        } while (next != *(long *)(extraout_x9 + 0x10));
    }
    FUN_0036b118(ctx);
    word_t uVar6 = FUN_003548b8();
    FUN_0008e500(uVar6, in_stack_00000018);
}

/* FUN_001f0370 @ 0x001f0370   (est. cl4_sched_bitmap_insert_slot8)
 * Ghidra: void FUN_001f0370(ulong param_1, undefined8 *param_2, undefined8 param_3, long param_4)
 * Inserts an 8-word (0x28-byte) entry into a slot array at index param_1: sets
 * the owning bit in the 64-bit bitmap (base+0x40), copies 5 words of payload,
 * installs a per-slot side entry (0x20-byte stride) and bumps the count at +0x10.
 * Confidence: low
 * Notes: FUN_00310d98 installs the side entry; SoftwareBreakpoint overflow. */
void cl4_sched_bitmap_insert_slot8(ulong idx, word_t *payload, word_t side, long arr)
{
    long bits = arr + (idx >> 6) * 8;
    *(ulong *)(bits + 0x40) |= 1L << (idx & 0x3f);
    word_t *slot = (word_t *)(*(long *)(arr + 0x30) + idx * 0x28);
    slot[1] = payload[1];
    slot[0] = payload[0];
    slot[3] = payload[3];
    slot[2] = payload[2];
    slot[4] = payload[4];
    FUN_00310d98(side, *(long *)(arr + 0x38) + idx * 0x20);
    if (!SCARRY8(*(long *)(arr + 0x10), 1)) {
        *(long *)(arr + 0x10) += 1;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f03ec);
}

/* FUN_001f0448 @ 0x001f0448   (est. cl4_sched_bitmap_insert_slot2)
 * Ghidra: void FUN_001f0448(ulong param_1, undefined8 param_2, undefined8 param_3,
 *   undefined8 param_4, long param_5)
 * Inserts a 2-word (0x10-byte) entry into a slot array at index param_1: sets
 * the bitmap bit, stores two payload words, installs a 0x20-byte side entry and
 * bumps the count at +0x10.
 * Confidence: low
 * Notes: mirror of FUN_001f0370 with a smaller slot; FUN_00310d98 side entry. */
void cl4_sched_bitmap_insert_slot2(ulong idx, word_t a, word_t b, word_t side, long arr)
{
    long bits = arr + (idx >> 6) * 8;
    *(ulong *)(bits + 0x40) |= 1L << (idx & 0x3f);
    word_t *slot = (word_t *)(*(long *)(arr + 0x30) + idx * 0x10);
    slot[0] = a;
    slot[1] = b;
    FUN_00310d98(side, *(long *)(arr + 0x38) + idx * 0x20);
    if (!SCARRY8(*(long *)(arr + 0x10), 1)) {
        *(long *)(arr + 0x10) += 1;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f04b4);
}

/* FUN_001f05b8 @ 0x001f05b8   (est. cl4_sched_bitmap_insert_find_free)
 * Ghidra: void FUN_001f05b8(ulong param_1, undefined8 param_2, undefined8 param_3,
 *   undefined8 param_4, long param_5)
 * Inserts a 2-word entry at the first free slot located by FUN_00084024 (bitmap
 * search over the base-array): stores the searched index word + payload word and
 * installs the side entry, then updates the count at +0x10.
 * Confidence: low
 * Notes: uses bitmap search FUN_00084024 rather than an explicit index. */
void cl4_sched_bitmap_insert_find_free(ulong key, word_t val, word_t side, word_t extra, long arr)
{
    long base = arr;
    uint128_t r = FUN_00084024(arr + (key >> 6) * 8);
    word_t *slot = (word_t *)(*(long *)(base + 0x30) + r_lo * 0x10);
    slot[0] = r_hi;
    slot[1] = val;
    FUN_00310d98(side, *(long *)(base + 0x38) + r_lo * 0x20);
    FUN_00359d58();
    if (!(bool)in_OV) {
        *(word_t *)(arr + 0x10) = extraout_x8;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f0610);
}

/* FUN_001f0668 @ 0x001f0668   (est. cl4_sched_bitmap_insert_find)
 * Ghidra: void FUN_001f0668(ulong param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Looks up the free index for param_1 via bitmap search, maps it through the
 * element map FUN_0035ab38, installs a 0x20-byte side entry and bumps the count.
 * Confidence: low
 * Notes: FUN_00084024 + FUN_0035ab38 index translation. */
void cl4_sched_bitmap_insert_find(ulong key, word_t a, word_t side, long arr)
{
    long base = arr;
    FUN_00084024(arr + (key >> 6) * 8);
    long idx = FUN_0035ab38(*(word_t *)(base + 0x30));
    FUN_00310d98(side, *(long *)(base + 0x38) + idx * 0x20);
    FUN_00359d58();
    if (!(bool)in_OV) {
        *(word_t *)(arr + 0x10) = extraout_x8;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f06bc);
}

/* FUN_001f06bc @ 0x001f06bc   (est. cl4_sched_bitmap_insert_word)
 * Ghidra: void FUN_001f06bc(ulong param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Inserts a single word entry at the free slot found by bitmap search: stores
 * the index word in the value array and param_3 in the side array, bumps count.
 * Confidence: low
 * Notes: 8-byte slot variant of the insert helpers. */
void cl4_sched_bitmap_insert_word(ulong key, word_t val, word_t side, long arr)
{
    uint128_t r = FUN_00084024(arr + (key >> 6) * 8);
    *(long *)(*(long *)(arr + 0x30) + r_lo * 8) = r_hi;
    *(word_t *)(*(long *)(arr + 0x38) + r_lo * 8) = side;
    if (!SCARRY8(*(long *)(arr + 0x10), 1)) {
        *(long *)(arr + 0x10) += 1;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f0700);
}

/* FUN_001f0700 @ 0x001f0700   (est. cl4_sched_bitmap_requeue)
 * Ghidra: void FUN_001f0700(void)
 * Requeues the current entry: finds its index via the sched key, dispatches the
 * queue head operation through the owner method table (offset +0x20) with the
 * per-queue stride, and bumps the count. Shared requeue tail of this range.
 * Confidence: low
 * Notes: FUN_00350a10 key, FUN_00084024 index, method-table dispatch. */
void cl4_sched_bitmap_requeue(void)
{
    ulong key = FUN_00350a10();
    uint128_t r = FUN_00084024(in_x3 + (key >> 6) * 8);
    (**(code **)(*(long *)(in_x4 + -8) + 0x20))
        (*(long *)(in_x3 + 0x30) + *(long *)(*(long *)(in_x4 + -8) + 0x48) * r_lo, r_hi, in_x4);
    FUN_003511b4();
    (**(code **)(extraout_x16 + 0x20))
        (*(long *)(unaff_x19 + 0x38) + *(long *)(extraout_x16 + 0x48) * key);
    FUN_00359d58();
    if (!(bool)in_OV) {
        *(word_t *)(unaff_x19 + 0x10) = extraout_x8;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f07ac);
}

/* FUN_001f07ac @ 0x001f07ac   (est. cl4_sched_entry_wrapper)
 * Ghidra: void FUN_001f07ac(undefined8 *param_1, undefined8 param_2, long param_3)
 * Thin wrapper: forwards three fields of param_3 (offsets 0x10/0x18/0x20) into
 * FUN_001f0130 and stores the result in *param_1.
 * Confidence: low
 * Notes: trampoline; result of FUN_001f0130 saved through out-param. */
void cl4_sched_entry_wrapper(word_t *out, word_t a, long src)
{
    *out = FUN_001f0130(a, *(word_t *)(src + 0x10), *(word_t *)(src + 0x18), *(word_t *)(src + 0x20));
}

/* FUN_001f07e0 @ 0x001f07e0   (est. cl4_sched_notify_scan)
 * Ghidra: void FUN_001f07e0(void)
 * Scans notification/schedule state: runs the context walk (queue at +0x10),
 * and on non-empty dispatches the queue drain thunk and the shared completion
 * check; finalizes with the epilogue helpers and the pending-exception path.
 * Confidence: low
 * Notes: register-passed state; FUN_001f99f4, FUN_0036b118, FUN_00350774. */
void cl4_sched_notify_scan(void)
{
    FUN_0008e518();
    FUN_00358f78();
    FUN_003548d0();
    FUN_00310d68();
    FUN_00348d4c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348a18();
    (*DAT_00658c00)();
    FUN_0034ba68();
    if (*(long *)(in_x3 + 0x10) != 0) {
        thunk_FUN_0036b270(in_x3);
        uint128_t r = FUN_003504c4();
        FUN_001f99f4(r_lo, r_hi, in_x6);
        if ((extraout_x1_00 & 1) == 0) {
            FUN_0036b118(in_x3);
        } else {
            FUN_00350bcc();
            (**(code **)(extraout_x16 + 0x10))();
            FUN_0036b118(in_x3);
        }
    }
    FUN_00350774();
    FUN_000839d8();
    FUN_000aa46c();
    FUN_00351ab0();
    (*(code **)extraout_x9)();
    FUN_00349f3c();
    if ((bool)in_ZR) {
        (*(code **)extraout_x1)();
        FUN_0034c9f8();
        (*(code **)extraout_x8_00)();
    } else {
        FUN_00350bcc();
        (**(code **)(extraout_x16_00 + 0x20))();
    }
    FUN_0008e500(unaff_x30);
}

/* FUN_001f0968 @ 0x001f0968   (est. cl4_sched_alloc_and_insert)
 * Ghidra: void FUN_001f0968(undefined8 param_1, undefined8 param_2, code *param_3,
 *   undefined8 param_4, long param_5)
 * Allocates a two-word capability slot pair (zone tag 0x1535 each), reserves
 * the caller's CNode with a sentinel (-0x8000000000000000), inserts the entry
 * via the bitmap helper FUN_001fbb74, and on success runs the completion hook
 * and requeues; finalizes by freeing the reservation.
 * Confidence: low
 * Notes: FUN_0036a908 zone alloc; FUN_001fbb74 insert; FUN_003a261c CNode. */
void cl4_sched_alloc_and_insert(word_t a, word_t b, code *cb, word_t c, long sched)
{
    uint128_t r0 = FUN_0035193c();
    word_t v0 = *(word_t *)(sched + 0x10);
    FUN_00349734();
    word_t w0 = FUN_0036a908(*(word_t *)(extraout_x8 + 0x40), 0x1535);
    r0_lo = w0;
    FUN_0034a688();
    word_t w1 = FUN_0036a908(*(word_t *)(extraout_x8_00 + 0x40), 0x1535);
    r0_lo[1] = w1;
    word_t cn = FUN_003a261c(*unaff_x20);
    long save = *unaff_x20;
    *unaff_x20 = -0x8000000000000000;
    FUN_003502e8();
    FUN_00359ba4();
    uint128_t ins = FUN_001fbb74(r0_hi, cn);
    FUN_00351900();
    FUN_001fb194();
    FUN_0036b118(save);
    long save2 = *unaff_x20;
    thunk_FUN_0036b270(save2);
    if ((ins_hi & 1) == 0) {
        (*cb)(w1);
        (**(code **)(extraout_x16 + 0x10))(w0, r0_hi, v0);
        FUN_00350ea4();
        FUN_00352ae4();
        FUN_00356a08();
        FUN_001f0700();
    }
    long tail = *(long *)(save2 + 0x38);
    FUN_0036b118(save2);
    FUN_00351774(FUN_001f0afc, tail + *(long *)(extraout_x16_00 + 0x48) * ins_lo, unaff_x30);
}

/* FUN_001f0afc @ 0x001f0afc   (est. cl4_sched_slot_release)
 * Ghidra: void FUN_001f0afc(undefined8 *param_1)
 * Releases the two-word capability slot: frees both words via the object
 * release thunk. Used as the deferred cleanup callback of FUN_001f0968.
 * Confidence: low
 * Notes: thunk_FUN_00012568 twice. */
void cl4_sched_slot_release(word_t *slot)
{
    word_t w0 = slot[0];
    cl4_obj_release(slot[1]);   /* thunk_FUN_00012568 */
    cl4_obj_release(w0);        /* thunk_FUN_00012568 */
}

/* FUN_001f0b2c @ 0x001f0b2c   (est. cl4_sched_insert_compact)
 * Ghidra: void FUN_001f0b2c(void)
 * Compact insert path: reserves the caller CNode with the sentinel, inserts via
 * FUN_001fbb74, restores the reservation and runs the tail completion.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fbb74 insert; FUN_003544c8 tail. */
void cl4_sched_insert_compact(void)
{
    FUN_00354744();
    FUN_0035098c();
    FUN_003a261c(*unaff_x20);
    FUN_003589fc();
    FUN_0034f2e4();
    FUN_0034d3e4();
    FUN_00359ba4();
    FUN_00355458();
    uint128_t r = FUN_001fbb74();
    FUN_003552a0();
    FUN_0034f3b4();
    FUN_001fb194();
    FUN_0036b118(in_stack_00000008);
    FUN_003544c8(r_lo, r_hi & 1, unaff_x30);
}

/* FUN_001f0bb4 @ 0x001f0bb4   (est. cl4_sched_get_field_38)
 * Ghidra: undefined8 FUN_001f0bb4(long param_1)
 * Accessor: returns the word at offset 0x38 of the scheduler context.
 * Confidence: low
 * Notes: trivial 8-byte load. */
word_t cl4_sched_get_field_38(long ctx)
{
    return *(word_t *)(ctx + 0x38);
}

/* FUN_001f0bbc @ 0x001f0bbc   (est. cl4_sched_insert_without_alloc)
 * Ghidra: void FUN_001f0bbc(undefined8 param_1, undefined8 param_2, code *param_3,
 *   undefined8 param_4, long param_5)
 * Inserts a pre-existing entry into the sched slot array: reserves the CNode,
 * runs the insert helper FUN_001fbb74; on success runs the callback + requeue,
 * otherwise falls back to the error method table entry.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fbb74 insert; dual completion/error path. */
void cl4_sched_insert_without_alloc(word_t a, word_t b, code *cb, word_t c, long sched)
{
    uint128_t r0 = FUN_0008e518();
    word_t v0 = *(word_t *)(sched + 0x18);
    FUN_003494e8();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_0034947c();
    word_t cn = FUN_003a261c(*unaff_x20);
    long save = *unaff_x20;
    FUN_00359aec();
    FUN_0034d014();
    FUN_00359ba4();
    uint128_t ins = FUN_001fbb74(r0_hi, cn);
    FUN_003518a0();
    FUN_001fb194();
    FUN_0036b118(save);
    long save2 = *unaff_x20;
    if ((ins_hi & 1) == 0) {
        thunk_FUN_0036b270(save2);
        (*cb)();
        FUN_0008e388();
        FUN_00351dcc();
        FUN_001f0700();
    } else {
        FUN_0034f384();
        code *err = *(code **)(extraout_x16_00 + 8);
        thunk_FUN_0036b270(save2);
        FUN_003511a8();
        (*err)();
    }
    long tail = *(long *)(save2 + 0x38);
    FUN_0036b118(save2);
    (**(code **)(extraout_x16 + 0x28))
        (tail + *(long *)(extraout_x16 + 0x48) * ins_lo, r0_lo, v0);
    FUN_0008e500(unaff_x30);
}

/* FUN_001f0d34 @ 0x001f0d34   (est. cl4_sched_op_a) */
/* Ghidra: void FUN_001f0d34(void) — alias of FUN_001f0d4c. Confidence: low */
void cl4_sched_op_a(void) { cl4_sched_op_c(); }

/* FUN_001f0d38 @ 0x001f0d38   (est. cl4_sched_op_b) */
/* Ghidra: void FUN_001f0d38(void) — alias of FUN_001f0d4c. Confidence: low */
void cl4_sched_op_b(void) { cl4_sched_op_c(); }

/* FUN_001f0d4c @ 0x001f0d4c   (est. cl4_sched_op_c)
 * Ghidra: void FUN_001f0d4c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Shared scheduler operation: takes the caller context (param_3) through the
 * state-machine helpers, performs the range-local op FUN_001fca74, and finishes
 * with the release/epilogue functions. Two aliases at 0x1f0d34/0x1f0d38.
 * Confidence: low
 * Notes: thunk_FUN_0036b270 take; FUN_001fca74 core op; FUN_0036b118 release. */
void cl4_sched_op_c(word_t a, word_t b, word_t ctx)
{
    FUN_00358fb4();
    FUN_00356188();
    FUN_0034d2b4();
    FUN_00353e50();
    thunk_FUN_0036b270(ctx);
    FUN_000a6e14();
    FUN_0034ef08();
    word_t r = FUN_001fca74();
    FUN_0036b118();
    FUN_00358fc8(r, unaff_x30);
}

/* FUN_001f0db8 @ 0x001f0db8   (est. cl4_sched_dispatch_builder)
 * Ghidra: undefined8 FUN_001f0db8(...7 args)
 * Builds a scheduler dispatch/entry structure: computes two object offsets from
 * the inputs, then invokes FUN_001f1150 to assemble a 16-byte descriptor into a
 * caller buffer, returning its first word.
 * Confidence: low
 * Notes: FUN_0031a29c/FUN_0031b560 offset computation; FUN_001f1150 builder;
 *   constant 0x66ba10. */
word_t cl4_sched_dispatch_builder(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f, word_t g)
{
    word_t local_48 = c;
    uint128_t r0 = FUN_0035869c();
    word_t local_80 = d, uStack_78 = e, local_70 = f, uStack_68 = g;
    uint128_t r1 = FUN_003516cc();
    word_t o1 = FUN_0031a29c(r1_lo, r1_hi, e, g);
    FUN_0034d3f4();
    word_t o2 = FUN_0031b560();
    return FUN_001f1150(&local_38, auStack_50, FUN_0031b5b8, auStack_90, o1, o2, 0x66ba10);
}

/* FUN_001f0e80 @ 0x001f0e80   (est. cl4_sched_teardown_entry)
 * Ghidra: void FUN_001f0e80(undefined8 param_1, long param_2, code *param_3, ...)
 * Tears down a scheduler entry via the method vectors: computes stack-relative
 * object frames, invokes the callback (param_3) over the layout, and routes to
 * the per-type destructor (single-frame vs two-frame) methods.
 * Confidence: low
 * Notes: method-table dispatch at +0x08/+0x10/+0x20; FUN_000839f8 scan. */
void cl4_sched_teardown_entry(word_t p1, long p2, code *cb, word_t p4, word_t p5, long p6, long p7, word_t p8)
{
    long l4 = FUN_003722e4(0, p5, p6, s_key_value_005cea2a, 0);
    long f1 = *(long *)(l4 + -8);
    (*DAT_00658c00)(*(long *)(f1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    long l10 = (long)&local_a0 - extraout_x8;
    long l5 = FUN_00310d68(0, p7);
    long f2 = *(long *)(l5 + -8);
    (*DAT_00658c00)(*(long *)(f2 + 0x40) + 0xfU & 0xfffffffffffffff0);
    long l9 = l10 - extraout_x8_00;
    long f3 = *(long *)(p7 + -8);
    long l7 = p7;
    (*DAT_00658c00)(*(word_t *)(f3 + 0x40));
    long l8 = l9 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
    (*cb)(l9, p2 + *(int *)(l4 + 0x30));
    if (unaff_x21 == 0) {
        int r = FUN_000839f8(l9, 1, l7);
        if (r == 1) {
            (**(code **)(f2 + 8))(l9, l5);
        } else {
            (**(code **)(f3 + 0x20))(l8, l9, l7);
            (**(code **)(f1 + 0x10))(l10, p2, l4);
            int stride = *(int *)(l4 + 0x30);
            word_t u = FUN_0031b560(0, local_98, l7, uStack_90);
            FUN_001f1104(l10, l8, u);
            (**(code **)(*(long *)(local_88 + -8) + 8))(l10 + stride);
        }
    }
}

/* FUN_001f1104 @ 0x001f1104   (est. cl4_sched_layout_dispatch)
 * Ghidra: void FUN_001f1104(void)
 * Builds a scheduler entry descriptor: computes an offset via FUN_00258c60,
 * forwards three caller-context fields into FUN_00100efc and finishes with the
 * teardown/requeue helper FUN_001f7be0.
 * Confidence: low
 * Notes: FUN_00258c60 index; FUN_00100efc dispatch; FUN_001f7be0 tail. */
void cl4_sched_layout_dispatch(void)
{
    FUN_000867ec();
    FUN_00353c48();
    uint128_t r = FUN_00258c60(1, extraout_x8 + 1);
    FUN_00100efc(r_lo, r_hi, *unaff_x20,
                 *(word_t *)(unaff_x19 + 0x10),
                 *(word_t *)(unaff_x19 + 0x18),
                 *(word_t *)(unaff_x19 + 0x20));
    FUN_001f7be0();
}

/* FUN_001f1150 @ 0x001f1150   (est. cl4_sched_dispatch_loop)
 * Ghidra: void FUN_001f1150(void)
 * Scheduler dispatch loop: acquires the shared context, walks the run queue
 * (FUN_00377824), invokes the per-entry method at +0x20, and loops through the
 * dequeue/requeue helpers until the queue is drained, then runs the epilogue.
 * Confidence: low
 * Notes: long method-vector chain (extraout_x8_*); loop exits when unaff_x19==0;
 *   DAT_00658c00 callback table. */
void cl4_sched_dispatch_loop(void)
{
    FUN_00353cfc();
    uint128_t r3 = FUN_00355e68();
    word_t out2_hi = in_x4;
    word_t out2_lo = extraout_x8;
    word_t u = in_x3;
    FUN_0035454c();
    uint128_t r4 = FUN_003548d0();
    FUN_00377824(r4_lo, r4_hi, u);
    FUN_00348e60();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0d4();
    FUN_003508e4();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034af20();
    FUN_00349c70();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003491ec();
    FUN_0034c920();
    FUN_00377824();
    FUN_00348d64();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b460();
    (**(code **)(*(long *)(in_x4 + -8) + 0x20))(extraout_x8, r3_lo);
    word_t u2 = FUN_00352e24();
    (*extraout_x8_01)(u2, in_stack_00000008, in_x3);
    FUN_00352680(in_x5);
    FUN_00350618();
    (*extraout_x9)();
    FUN_0034b278();
    FUN_000dbd0c();
    u2 = FUN_00377bec();
    code *next = (code *)FUN_000a68f4();
    do {
        (*next)(unaff_x23, u2);
        FUN_00352560();
        FUN_00350884();
        if ((bool)in_ZR) {
            uint128_t r5 = FUN_0034ed28();
            next = extraout_x8_06;
            goto done;
        }
        FUN_00350944(*(word_t *)(extraout_x16 + 0x20));
        (*extraout_x8_02)();
        (*r3_hi)(extraout_x8);
        FUN_00350914(*(word_t *)(extraout_x16 + 8));
        (*extraout_x8_03)();
    } while (unaff_x19 == 0);
    FUN_0034ed28();
    (*extraout_x8_04)();
    FUN_00353154();
    next = extraout_x8_05;
done:
    (*next)(r5_lo, r5_hi);
    FUN_00351348();
    FUN_00353d14(unaff_x23);
}

/* FUN_001f13e4 @ 0x001f13e4   (est. cl4_sched_entry_setup)
 * Ghidra: void FUN_001f13e4(undefined8 param_1, undefined8 param_2, long param_3)
 * Sets up a scheduler entry: computes the dispatch key from three fields of
 * param_3 (offsets 0x10/0x18/0x20) via FUN_0031a2b4 and pushes it through
 * FUN_0034ffb8, then falls to the common op FUN_001f142c.
 * Confidence: low
 * Notes: FUN_0031a2b4 key derivation; FUN_001f142c shared tail. */
void cl4_sched_entry_setup(word_t a, word_t b, long src)
{
    FUN_0034c084();
    uint128_t r = FUN_0031a2b4(0, *(word_t *)(src + 0x10), *(word_t *)(src + 0x18), *(word_t *)(src + 0x20));
    FUN_0034ffb8(r_lo, r_hi, r_lo);
    FUN_001f142c();
}

/* FUN_001f142c @ 0x001f142c   (est. cl4_sched_common_op)
 * Ghidra: void FUN_001f142c(void)
 * Shared scheduler operation tail: takes the caller CNode (FUN_003a261c),
 * derives the offset (FUN_0031b560), runs the range-local op FUN_001fc3b4, and
 * finishes with the restore/epilogue helpers.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fc3b4 core; FUN_0036b118 release. */
void cl4_sched_common_op(void)
{
    FUN_00077698();
    FUN_0034ba18();
    word_t cn = FUN_003a261c(*unaff_x20);
    FUN_0034f2e4(*unaff_x20);
    FUN_0034d404();
    FUN_0031b560();
    FUN_00357a84();
    uint128_t r = FUN_0034cdd8();
    FUN_001fc3b4(r_lo, r_hi, cn);
    FUN_003552a0();
    FUN_00351cd0();
    FUN_001fb194();
    FUN_0007767c(in_stack_00000008, unaff_x30);
    FUN_0036b118();
}

/* FUN_001f14b4 @ 0x001f14b4   (est. cl4_sched_op_prepare)
 * Ghidra: void FUN_001f14b4(void)
 * Prepares a scheduler operation: derives the dispatch key from three fields of
 * the caller context (offsets 0x10/0x18/0x20) and routes through the setup
 * helpers to the shared op FUN_001f1514.
 * Confidence: low
 * Notes: FUN_0031a2b4 key; FUN_001f1514 tail. */
void cl4_sched_op_prepare(void)
{
    FUN_003585e8();
    FUN_00352fd4();
    FUN_0031a2b4(0, *(word_t *)(in_x3 + 0x10), *(word_t *)(in_x3 + 0x18), *(word_t *)(in_x3 + 0x20));
    FUN_0034f444();
    FUN_00356170();
    FUN_001f1514();
}

/* FUN_001f1514 @ 0x001f1514   (est. cl4_sched_op_commit)
 * Ghidra: void FUN_001f1514(void)
 * Commits the scheduler op: takes the caller CNode, derives the offset, runs
 * FUN_001ee3b8 and the commit helper FUN_001fb194, then releases the CNode and
 * runs the completion callback.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001ee3b8/FUN_001fb194 core; FUN_0036b118. */
void cl4_sched_op_commit(void)
{
    FUN_0035acfc();
    FUN_00353e50();
    FUN_003a261c(*unaff_x20);
    word_t u = *unaff_x20;
    FUN_00352414();
    FUN_0034ac8c();
    FUN_0031b560();
    FUN_003569e4();
    FUN_001ee3b8();
    FUN_003511f0();
    FUN_001fb194();
    FUN_0036b118(u);
    FUN_0035841c(unaff_x30);
}

/* FUN_001f15c8 @ 0x001f15c8   (est. cl4_sched_entry_construct)
 * Ghidra: void FUN_001f15c8(undefined8 param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Constructs a scheduler entry pair: allocates the primary (tag 0x66aa38) and a
 * side table (0x66aa60/0x38/7), copies three context words (0x10/0x18/0x20) into
 * both, wires the method table & back-pointer, then commits via FUN_001f1514.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; method table &DAT_0031b5d4; FUN_001f1878 tail. */
void cl4_sched_entry_construct(word_t a, word_t b, word_t c, long src)
{
    uint128_t r = FUN_003563c4();
    in_stack_00000058 = r_lo;
    thunk_FUN_00200b38(&stack0x00000030, src);
    FUN_003a25d4(r_lo);
    FUN_00359018(0x66aa38);
    long p = FUN_0036a940();
    word_t w10 = *(word_t *)(src + 0x10);
    *(word_t *)(p + 0x18) = *(word_t *)(src + 0x18);
    *(word_t *)(p + 0x10) = w10;
    long s = FUN_0036a940(0x66aa60, 0x38, 7);
    *(word_t *)(s + 0x10) = w10;
    word_t w20 = *(word_t *)(src + 0x20);
    w10 = *(word_t *)(src + 0x18);
    *(word_t *)(p + 0x20) = *(word_t *)(src + 0x20);
    *(word_t *)(s + 0x20) = w20;
    *(word_t *)(s + 0x18) = w10;
    *(word_t **)(s + 0x28) = &DAT_0031b5d4;
    *(long *)(s + 0x30) = p;
    FUN_00319320(0, src, 0x66ba10);
    FUN_00350308(w10);
    FUN_003515b4();
    FUN_003722e4();
    FUN_00351190(&stack0x00000038, &LAB_0031b604);
    FUN_001f1878();
    FUN_0036b118(s);
    FUN_003a25d4(in_stack_00000030);
    FUN_00350308();
    w10 = FUN_0031a2b4();
    FUN_0034f5f4();
    FUN_00319338();
    FUN_003545f4();
    FUN_001f1514(&stack0x00000038, r_hi, c, w10);
    FUN_003563a8(unaff_x30);
}

/* FUN_001f1750 @ 0x001f1750   (est. cl4_sched_cross_dispatch)
 * Ghidra: void FUN_001f1750(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *   undefined8 param_4, long param_5, long param_6)
 * Cross-dispatches two scheduler objects: forwards (param_1,param_3) through the
 * method vector of param_5 and (param_2,param_4) through that of param_6.
 * Confidence: low
 * Notes: two method-table calls at +0x10; jumptable recovery warning. */
void cl4_sched_cross_dispatch(word_t a, word_t b, word_t c, word_t d, long o1, long o2)
{
    (**(code **)(*(long *)(o1 + -8) + 0x10))(a, c, o1);
    /* WARNING: could not recover jumptable at 0x1f17d0; indirect jump as call */
    (**(code **)(*(long *)(o2 + -8) + 0x10))(b, d, o2);
}

/* FUN_001f17d4 @ 0x001f17d4   (est. cl4_sched_apply_layout)
 * Ghidra: void FUN_001f17d4(long param_1, long param_2, code *param_3, undefined8 param_4,
 *   undefined8 param_5, undefined8 param_6)
 * Applies a layout transform: computes two object strides (via FUN_003722e4 with
 * the key/value tags) and invokes param_3 over the two offset-adjusted frames.
 * Confidence: low
 * Notes: FUN_003722e4 stride lookups (tag 0x5cea2a); callback over pair. */
void cl4_sched_apply_layout(long a, long b, code *cb, word_t c, word_t d, word_t e)
{
    long l1 = FUN_003722e4(0, d, e, s_key_value_005cea2a, 0);
    int s1 = *(int *)(l1 + 0x30);
    long l2 = FUN_003722e4(0, d, e, 0, 0);
    (*cb)(a, a + *(int *)(l2 + 0x30), b, b + s1);
}

/* FUN_001f1878 @ 0x001f1878   (est. cl4_sched_commit_scan)
 * Ghidra: void FUN_001f1878(void)
 * Commit/scan phase of the scheduler: walks the run queue (FUN_00377824) and the
 * pending helper chain, then runs the release/epilogue (FUN_0036b270/FUN_0008e500).
 * Confidence: low
 * Notes: FUN_00377824 queue walk; DAT_00658c00; FUN_0036b270 release. */
void cl4_sched_commit_scan(void)
{
    FUN_0008e518();
    FUN_00352c10();
    FUN_003562c8();
    FUN_00350488();
    FUN_00377824();
    FUN_00349e10();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034af20();
    FUN_000a68c4(in_x4);
    word_t u = FUN_0034d434();
    (*extraout_x9)(u, in_x4);
    FUN_0034f544();
    FUN_00377bec();
    FUN_0034f374();
    FUN_002522c4();
    FUN_0036b270();
    FUN_0008e500(unaff_x30);
}

/* FUN_001f1940 @ 0x001f1940   (est. cl4_sched_op_finish)
 * Ghidra: void FUN_001f1940(void)
 * Finalizes a scheduler op: derives the key, commits via FUN_001f1514, releases
 * the caller CNode if present and runs the completion callback.
 * Confidence: low
 * Notes: FUN_0031a2b4 key; FUN_001f1514 commit; FUN_003a25d4 conditional free. */
void cl4_sched_op_finish(void)
{
    FUN_00358fb4();
    FUN_0034e4ec();
    FUN_00350328();
    FUN_0031a2b4();
    FUN_00357a84();
    FUN_0034e55c();
    FUN_001f1514();
    if (unaff_x21 != 0) {
        in_x3 = FUN_003a25d4(in_x3);
    }
    FUN_00358fc8(in_x3, extraout_x8);
}

/* FUN_001f19b8 @ 0x001f19b8   (est. cl4_sched_op_entry)
 * Ghidra: void FUN_001f19b8(void)
 * Entry phase of a scheduler op: derives the key, prepares the shared context
 * and constructs the entry via FUN_001f15c8, freeing the CNode if present.
 * Confidence: low
 * Notes: FUN_0031a29c key; FUN_001f15c8 construct; FUN_003a25d4 conditional free. */
void cl4_sched_op_entry(void)
{
    FUN_0034c59c();
    FUN_00350328();
    FUN_0031a29c();
    FUN_00357a84();
    FUN_00077708();
    FUN_001f15c8();
    if (unaff_x21 != 0) {
        FUN_003a25d4(in_x3);
    }
}

/* FUN_001f1a20 @ 0x001f1a20   (est. cl4_sched_op_select)
 * Ghidra: void FUN_001f1a20(void)
 * Scheduler op selection: derives the key, checks the caller CNode bit, and if
 * clear runs the shared insert path (FUN_001fc0f4); then validates the priority
 * class and, on match, runs the priority requeue path (FUN_001fc840), otherwise
 * panics via the no-return failure helper.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fc0f4/FUN_001fc840 op; noreturn panic. */
void cl4_sched_op_select(void)
{
    FUN_0034b318();
    FUN_0031a2b4(0, *(word_t *)(in_x4 + 0x10), *(word_t *)(in_x4 + 0x18), *(word_t *)(in_x4 + 0x20));
    FUN_0034b508();
    FUN_00351e20();
    in_stack_00000078 = unaff_x30;
    FUN_0034b318();
    ulong cn = FUN_003a261c(*unaff_x20);
    if ((cn & 1) == 0) {
        in_stack_00000018 = *unaff_x20;
        FUN_00352414();
        FUN_003508e4();
        FUN_00354ca8();
        FUN_0031b560();
        FUN_001fc0f4();
        FUN_00353c30(unaff_x20, &stack0x00000018);
        FUN_001fb194();
        FUN_0036b118(in_stack_00000018);
    }
    if ((((-1 < (long)unaff_x21) && (unaff_x21 >> ((ulong)*(byte *)(*unaff_x20 + 0x20) & 0x3f) == 0))
        && (FUN_00359a10(), (extraout_x9 & 1) != 0)) && (in_w3 == *(int *)(extraout_x8 + 0x24))) {
        in_stack_00000018 = extraout_x8;
        FUN_00352414();
        FUN_0034d8f4();
        FUN_0031b560();
        FUN_0034b508();
        FUN_001fc840();
        FUN_00353a6c(unaff_x20, &stack0x00000018);
        FUN_001fb194();
        FUN_00351d30(in_stack_00000018, in_stack_00000078);
        FUN_0036b118();
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001f1b84 @ 0x001f1b84   (est. cl4_sched_read_caps)
 * Ghidra: undefined8 FUN_001f1b84(void)
 * Reads a capability pair for the scheduler op: on the fast path returns a
 * stored value (FUN_00019858); otherwise derives the CNode, builds the entry and
 * returns it through FUN_001fc840.
 * Confidence: low
 * Notes: FUN_001f98e8 check; FUN_003a261c CNode; FUN_001fc840 build. */
word_t cl4_sched_read_caps(void)
{
    FUN_0035a010();
    uint128_t r = FUN_001f98e8();
    if ((r_hi & 1) == 0) {
        local_58[0] = FUN_00019858();
    } else {
        FUN_003a261c(*unaff_x19);
        FUN_003589fc();
        local_48 = extraout_x8;
        FUN_00352414();
        FUN_00356f30();
        FUN_001fc840(auStack_40, local_58, r_lo);
        FUN_003a25d4(local_38);
        *unaff_x19 = local_48;
    }
    return local_58[0];
}

/* FUN_001f1c10 @ 0x001f1c10   (est. cl4_sched_read_5word)
 * Ghidra: void FUN_001f1c10(void)
 * Reads a 5-word capability tuple: on the fast path zeroes the output tuple,
 * otherwise derives the CNode and fills it via FUN_001fc840.
 * Confidence: low
 * Notes: FUN_001f98e8 check; FUN_003a261c CNode; zero-init branch. */
void cl4_sched_read_5word(void)
{
    FUN_00357ca0();
    FUN_00358094();
    FUN_001f98e8();
    if ((extraout_w1 & 1) == 0) {
        unaff_x21[4] = 0;
        unaff_x21[1] = 0;
        unaff_x21[0] = 0;
        unaff_x21[3] = 0;
        unaff_x21[2] = 0;
    } else {
        FUN_003a261c(*unaff_x19);
        FUN_00358930();
        FUN_0034f2e4();
        FUN_00356f1c();
        FUN_0035732c();
        FUN_003511d8();
        FUN_001fc840();
        FUN_003a25d4(in_stack_00000018);
        *unaff_x19 = in_stack_00000008;
    }
    FUN_00357c44(unaff_x30);
}

/* FUN_001f1c94 @ 0x001f1c94   (est. cl4_sched_read_4word)
 * Ghidra: void FUN_001f1c94(void)
 * Reads a 4-word capability tuple (variant of FUN_001f1c10 with a different
 * build helper FUN_00356f08); zeroes output on fast path.
 * Confidence: low
 * Notes: mirror of FUN_001f1c10. */
void cl4_sched_read_4word(void)
{
    FUN_00357ca0();
    FUN_00358094();
    FUN_001f98e8();
    if ((extraout_w1 & 1) == 0) {
        unaff_x21[1] = 0;
        unaff_x21[0] = 0;
        unaff_x21[3] = 0;
        unaff_x21[2] = 0;
    } else {
        FUN_003a261c(*unaff_x19);
        FUN_00358930();
        FUN_0034f2e4();
        FUN_00356f08();
        FUN_0035732c();
        FUN_003511d8();
        FUN_001fc840();
        FUN_003a25d4(in_stack_00000018);
        *unaff_x19 = in_stack_00000008;
    }
    FUN_00357c44(unaff_x30);
}

/* FUN_001f1d14 @ 0x001f1d14   (est. cl4_sched_read_4word_b)
 * Ghidra: void FUN_001f1d14(void)
 * Reads a 4-word capability tuple via FUN_001f9964 check and FUN_00356ee0
 * builder; zeroes output on fast path.
 * Confidence: low
 * Notes: mirrors FUN_001f1c94 with FUN_001f9964 check. */
void cl4_sched_read_4word_b(void)
{
    FUN_00041138();
    FUN_00358094();
    FUN_001f9964();
    if ((extraout_x1_00 & 1) == 0) {
        unaff_x21[1] = 0;
        unaff_x21[0] = 0;
        unaff_x21[3] = 0;
        unaff_x21[2] = 0;
    } else {
        FUN_003a261c(*unaff_x19);
        FUN_00358930();
        FUN_00352414();
        FUN_00356ee0();
        FUN_003511d8(&stack0x00000008);
        FUN_001fc840();
        FUN_003199ac(&stack0x00000008);
        *unaff_x19 = extraout_x8;
    }
    FUN_0035847c(extraout_x1);
}

/* FUN_001f1d9c @ 0x001f1d9c   (est. cl4_sched_read_2word)
 * Ghidra: undefined8 FUN_001f1d9c(void)
 * Reads a 2-word capability pair via FUN_001f9964 check and FUN_00356ef4
 * builder; returns stored value on fast path.
 * Confidence: low
 * Notes: mirror of FUN_001f1b84 with FUN_001f9964 check. */
word_t cl4_sched_read_2word(void)
{
    FUN_0035a010();
    uint128_t r = FUN_001f9964();
    if ((r_hi & 1) == 0) {
        local_70[0] = FUN_00019858();
    } else {
        FUN_003a261c(*unaff_x19);
        FUN_003589fc();
        local_60 = extraout_x8;
        FUN_00352414();
        FUN_00356ef4();
        FUN_001fc840(auStack_58, local_70, r_lo);
        FUN_003199ac(auStack_58);
        *unaff_x19 = local_60;
    }
    return local_70[0];
}

/* FUN_001f1e28 @ 0x001f1e28   (est. cl4_sched_op_scan)
 * Ghidra: void FUN_001f1e28(void)
 * Scans and dispatches a scheduler operation: takes the caller context, checks
 * the insert result (FUN_001f99f4), and on completion runs the CNode-write and
 * requeue path; otherwise the drain epilogue.
 * Confidence: low
 * Notes: FUN_001f99f4 check; FUN_003a261c CNode; FUN_001fc840; two exits. */
void cl4_sched_op_scan(void)
{
    FUN_0008e518();
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00349068();
    word_t ctx = *unaff_x20;
    word_t v = *(word_t *)(extraout_x1 + 0x20);
    thunk_FUN_0036b270(ctx);
    uint128_t r = FUN_003508b4();
    FUN_001f99f4(r_lo, r_hi, v);
    FUN_0036b118(ctx);
    if ((extraout_x1_00 & 1) != 0) {
        FUN_003a261c(*unaff_x20);
        *unaff_x20 = 0x8000000000000000;
        FUN_0034b7b8();
        FUN_0031b560();
        FUN_0034ee18();
        FUN_001fc840();
        FUN_0035084c(*(word_t *)(extraout_x16 + 8));
        (*extraout_x8_00)();
        FUN_003511f0();
        FUN_001fb194();
        FUN_0036b118(ctx);
        FUN_0034ba48();
        FUN_000839d8();
        FUN_0008e500(unaff_x30);
        return;
    }
    FUN_0034c6c4();
    FUN_0008e500();
    FUN_000839d8();
}

/* FUN_001f1f70 @ 0x001f1f70   (est. cl4_sched_op_forward)
 * Ghidra: void FUN_001f1f70(undefined8 param_1, long param_2)
 * Forwards a scheduler op: derives the key from three fields of param_2 and
 * dispatches the pair through FUN_001f1fac.
 * Confidence: low
 * Notes: FUN_003524bc forward; FUN_0031a2b4 key; FUN_001f1fac tail. */
void cl4_sched_op_forward(word_t a, long src)
{
    FUN_003524bc(*(word_t *)(src + 0x10), a, src, *(word_t *)(src + 0x18), *(word_t *)(src + 0x20));
    word_t k = FUN_0031a2b4();
    FUN_001f1fac(a, k);
}

/* FUN_001f1fac @ 0x001f1fac   (est. cl4_sched_op_requeue)
 * Ghidra: void FUN_001f1fac(void)
 * Requeue/commit phase: on the fast path releases the caller context; otherwise
 * if the queue is non-empty derives the CNode and runs the requeue build
 * FUN_001fc908, finishing with the epilogue.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fc908 requeue; FUN_0036b118 release. */
void cl4_sched_op_requeue(void)
{
    FUN_00357cb4();
    ulong f = FUN_0035a010();
    if ((f & 1) == 0) {
        FUN_003a25d4();
        FUN_0035869c();
        *unaff_x19 = extraout_x8;
    } else if (*(long *)(unaff_x20 + 0x10) != 0) {
        word_t cn = FUN_003a261c();
        FUN_00352414();
        FUN_0034d3f4();
        FUN_0031b560();
        FUN_00355c28();
        FUN_001fc908(cn);
        FUN_003552a0();
        FUN_00351e3c();
        FUN_001fb194();
        FUN_0036b118(unaff_x20);
    }
    FUN_00357c74(unaff_x30);
}

/* FUN_001f2048 @ 0x001f2048   (est. cl4_sched_entry_alloc_desc)
 * Ghidra: undefined1 [16] FUN_001f2048(void)
 * Allocates a 5-word scheduler descriptor (zone 0xfef3), fills it with the
 * caller context fields (offsets 0x10/0x18/0x20) and a sentinel, then builds the
 * dispatch key and returns a 16-byte descriptor (data ptr + method table).
 * Confidence: low
 * Notes: FUN_0036a908 alloc tag &DAT_0000fef3; sentinel 0x8000000000000000;
 *   method table &DAT_001f20d8. */
cl4_desc_t cl4_sched_entry_alloc_desc(void)
{
    FUN_0008409c();
    word_t *p = (word_t *)FUN_0036a908(0x28, &DAT_0000fef3);
    *unaff_x21 = p;
    p[1] = unaff_x20;
    p[2] = *(word_t *)(unaff_x19 + 0x10);
    p[3] = *(word_t *)(unaff_x19 + 0x18);
    p[4] = *(word_t *)(unaff_x19 + 0x20);
    p[0] = 0x8000000000000000;
    uint128_t r = FUN_0031a2b4(0);
    FUN_003509bc(r_lo, r_hi, r_lo);
    FUN_001f2104();
    cl4_desc_t out;
    out.hi = p;
    out.lo = &DAT_001f20d8;
    return out;
}

/* FUN_001f2104 @ 0x001f2104   (est. cl4_sched_dispatch_step)
 * Ghidra: void FUN_001f2104(void)
 * Runs one scheduler dispatch step: acquires the shared context and invokes the
 * method at +0x20 three times around intermediate helper calls.
 * Confidence: low
 * Notes: DAT_00658c00; method +0x20 thrice; FUN_0011aa70 helper. */
void cl4_sched_dispatch_step(void)
{
    FUN_0034b430();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003490ec();
    code *m = *(code **)(extraout_x16 + 0x20);
    FUN_00350560();
    (*m)();
    FUN_0011aa70();
    (*m)();
    FUN_0034f594();
    (*m)();
}

/* FUN_001f21a8 @ 0x001f21a8   (est. cl4_sched_swap_ctx)
 * Ghidra: void FUN_001f21a8(undefined8 *param_1, undefined8 *param_2)
 * Swaps two caller-context words: takes param_2, takes a reference on it, stores
 * into param_1, then releases the previous param_1 value.
 * Confidence: low
 * Notes: thunk_FUN_0036b270 take; FUN_003a25d4 release. */
void cl4_sched_swap_ctx(word_t *dst, word_t *src)
{
    word_t v = *src;
    word_t old = *dst;
    *dst = v;
    thunk_FUN_0036b270(v);
    FUN_003a25d4(old);
}

/* FUN_001f21e0 @ 0x001f21e0   (est. cl4_sched_op_restart)
 * Ghidra: void FUN_001f21e0(void)
 * Restarts a scheduler op: takes the caller context, resets it to the sentinel,
 * builds a fresh descriptor via FUN_001f2104, frees the old one, and swaps the
 * contexts through FUN_001f21a8.
 * Confidence: low
 * Notes: sentinel 0x8000000000000000; FUN_003a25d4 frees; FUN_001f21a8 swap. */
void cl4_sched_op_restart(void)
{
    word_t v = FUN_00357cb4();
    in_stack_00000008 = 0x8000000000000000;
    FUN_0034c444(0);
    FUN_0031a2b4();
    FUN_001f2104(&stack0x00000008);
    FUN_003a25d4(in_stack_00000008);
    in_stack_00000008 = v;
    FUN_003511cc();
    FUN_001f21a8();
    FUN_003a25d4(v);
    FUN_00357c74(unaff_x30);
}

/* FUN_001f2268 @ 0x001f2268   (est. cl4_sched_store_ctx)
 * Ghidra: void FUN_001f2268(void)
 * Stores a context: frees the previous caller context (FUN_003a25d4) and writes
 * the new value into the caller slot.
 * Confidence: low
 * Notes: FUN_00356988; FUN_003a25d4 free; store. */
void cl4_sched_store_ctx(void)
{
    FUN_00356988();
    FUN_003a25d4();
    *unaff_x20 = unaff_x19;
}

/* FUN_001f2648 @ 0x001f2648   (est. cl4_sched_wait_condition)
 * Ghidra: bool FUN_001f2648(uint param_1, undefined8 param_2, undefined8 param_3)
 * Holds a reference on param_3 and spins in FUN_002b0c84 until the condition
 * matches param_1 (low 16 bits) or the flag 0x10000 in the upper byte appears;
 * releases param_3 and returns whether the flag (not the match) was seen.
 * Confidence: low
 * Notes: spin loop with FUN_002b0c84 status; thunk take / FUN_003a25d4 release. */
bool cl4_sched_wait_condition(uint cond, word_t a, word_t ctx)
{
    thunk_FUN_0036b270(ctx);
    uint s;
    do {
        s = FUN_002b0c84();
    } while ((s & 0xff0000) != 0x10000 && (cond & 0xffff) != (s & 0xffff));
    FUN_003a25d4(ctx);
    return (s & 0xff0000) != 0x10000;
}

/* FUN_001f26cc @ 0x001f26cc   (est. cl4_sched_try_op)
 * Ghidra: uint FUN_001f26cc(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *   undefined8 param_4)
 * Attempts a scheduler op with preemption checking: derives the state, runs the
 * preempt-safe stub, and on the taken branch stashes the caller state into the
 * preemption frame and runs FUN_0035063c; returns success bit.
 * Confidence: low
 * Notes: FUN_0031b62c state; FUN_0035063c(FUN_003465d4) preempt hook. */
uint cl4_sched_try_op(word_t a, word_t b, word_t c, word_t d)
{
    word_t s = FUN_00350b54();
    word_t st = FUN_0031b62c(c);
    FUN_0034edc8(st);
    (*extraout_x8)();
    uint r = FUN_00354a6c();
    if ((bool)in_ZR) {
        (*DAT_00658c00)();
        FUN_003539e4();
        *(word_t *)(extraout_x8_00 + -0x20) = unaff_x21;
        *(word_t *)(extraout_x8_00 + -0x18) = unaff_x19;
        *(word_t *)(extraout_x8_00 + -0x10) = d;
        *(word_t *)(extraout_x8_00 + -8) = s;
        FUN_0035063c(FUN_003465d4);
        r = FUN_00286c10();
    }
    return r & 1;
}

/* FUN_001f2790 @ 0x001f2790   (est. cl4_sched_park_flush)
 * Ghidra: void FUN_001f2790(void)
 * Park/flush helper: runs the state machine prep then the shared thunk and the
 * post hook.
 * Confidence: low
 * Notes: FUN_00356c18; thunk_FUN_00355354; FUN_00357670. */
void cl4_sched_park_flush(void)
{
    FUN_00356c18();
    thunk_FUN_00355354();
    FUN_00357670();
}

/* FUN_001f27b8 @ 0x001f27b8   (est. cl4_sched_desc_alloc_fill)
 * Ghidra: undefined * FUN_001f27b8(long *param_1, undefined8 *param_2, long param_3)
 * Allocates a 5-word descriptor (zone 0xe44f), fills it via FUN_001f283c with
 * the caller caps + context fields, and returns the method table &DAT_001f2838.
 * Confidence: low
 * Notes: FUN_0036a908 alloc; FUN_001f283c fill; method table &DAT_001f2838. */
word_t *cl4_sched_desc_alloc_fill(long *out, word_t *caps, long ctx)
{
    long d = FUN_0036a908(0x28, 0xe44f);
    *out = d;
    word_t v = FUN_001f283c(d, *caps, *(uint *)(caps + 1), *unaff_x20,
                            *(word_t *)(ctx + 0x10), *(word_t *)(ctx + 0x18), *(word_t *)(ctx + 0x20));
    *(word_t *)(d + 0x20) = v;
    return &DAT_001f2838;
}

/* FUN_001f283c @ 0x001f283c   (est. cl4_sched_desc_init)
 * Ghidra: undefined1 [16] FUN_001f283c(long *param_1, ...5 args)
 * Initializes a scheduler descriptor: records the caller object and its method
 * vector, allocates the inner state (zone 0x7516) and fills it via FUN_001f2298;
 * returns a 16-byte descriptor (data + method table &DAT_001f28f0).
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0x7516; FUN_001f2298 fill; &DAT_001f28f0. */
cl4_desc_t cl4_sched_desc_init(long *out, word_t a, word_t b, word_t c, long src)
{
    long mv = *(long *)(src + -8);
    out[0] = src;
    out[1] = mv;
    long st = FUN_0036a908(*(word_t *)(mv + 0x40), 0x7516);
    out[2] = st;
    FUN_001f2298(st, a, b, c, src);
    cl4_desc_t r;
    r.hi = st;
    r.lo = &DAT_001f28f0;
    return r;
}

/* FUN_001f2908 @ 0x001f2908   (est. cl4_sched_set_result)
 * Ghidra: void FUN_001f2908(void)
 * Records a scheduler op result: derives the caps, runs the op (FUN_001fb26c),
 * writes the status word (split high/low into bytes + int) and the owner into
 * the caller's result tuple.
 * Confidence: low
 * Notes: FUN_001fb26c op; result split into byte/word fields at +0xc/+4. */
void cl4_sched_set_result(void)
{
    FUN_00351cc4();
    word_t v0 = *unaff_x20;
    word_t v1 = *(word_t *)(extraout_x1 + 0x10);
    word_t v2 = *(word_t *)(extraout_x1 + 0x20);
    thunk_FUN_0036b270(v0);
    uint128_t r = FUN_0009461c();
    FUN_001fb26c(r_lo, r_hi, v1, in_x3, v2);
    FUN_00353918();
    FUN_0036b118(v0);
    *unaff_x21 = unaff_x19;
    *(char *)((long)unaff_x21 + 0xc) = (char)((ulong)v1 >> 0x20);
    *(int *)(unaff_x21 + 1) = (int)v1;
    *(uint8_t *)((long)unaff_x21 + 0xd) = 0;
}

/* FUN_001f29e8 @ 0x001f29e8   (est. cl4_sched_empty_check)
 * Ghidra: uint FUN_001f29e8(undefined8 param_1, long param_2)
 * Returns whether the scheduler queue is non-empty: if the queue at param_2+0x10
 * is empty returns 0, otherwise takes the context, runs the check FUN_001f99f4
 * and returns its low bit.
 * Confidence: low
 * Notes: queue-length short-circuit; FUN_001f99f4 check. */
uint cl4_sched_empty_check(word_t a, long sched)
{
    long ctx = *unaff_x20;
    if (*(long *)(ctx + 0x10) == 0) {
        return 0;
    }
    word_t v2 = *(word_t *)(sched + 0x20);
    word_t v1 = *(word_t *)(sched + 0x10);
    thunk_FUN_0036b270(ctx);
    FUN_001f99f4(a, v1, v2);
    FUN_0036b118(ctx);
    return extraout_w1 & 1;
}

/* FUN_001f2a6c @ 0x001f2a6c   (est. cl4_sched_index_dispatch)
 * Ghidra: void FUN_001f2a6c(undefined8 param_1, ulong param_2, int param_3, long param_4,
 *   undefined8 param_5, long param_6)
 * Dispatches a scheduler slot by index: validates that param_2 is in range and
 * the slot bit is set and the class matches, then invokes the owner method at
 * +0x10 with the slot pointer; else panics.
 * Confidence: low
 * Notes: bitmap range check; method dispatch +0x10; noreturn panic. */
void cl4_sched_index_dispatch(word_t a, ulong idx, int cls, long sched, word_t c, long owner)
{
    if ((((-1 < (long)idx) && (idx >> ((ulong)*(byte *)(sched + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(sched + (idx >> 6) * 8 + 0x40) >> (idx & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(sched + 0x24))) {
        /* WARNING: could not recover jumptable at 0x1fb530; indirect jump as call */
        (**(code **)(*(long *)(owner + -8) + 0x10))
            (a, *(long *)(sched + 0x38) + *(long *)(*(long *)(owner + -8) + 0x48) * idx, owner);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001f2a70 @ 0x001f2a70   (est. cl4_sched_requeue_class)
 * Ghidra: void FUN_001f2a70(undefined8 param_1, undefined8 param_2, int param_3, long param_4)
 * Requeues a scheduler entry by class: takes the caller CNode, on the fast path
 * runs the insert op FUN_001fc0f4; validates the class and runs the class hook
 * FUN_00354ef8(FUN_0001a1c8, slot) else panics.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fc0f4 insert; FUN_00354ef8 class hook. */
void cl4_sched_requeue_class(word_t a, word_t b, int cls, long sched)
{
    FUN_00354a34();
    FUN_00351a38();
    long l3 = *(long *)(sched + 0x18);
    ulong cn = FUN_003a261c(*unaff_x20);
    if ((cn & 1) == 0) {
        long ctx = *unaff_x20;
        *unaff_x20 = -0x8000000000000000;
        FUN_003508e4();
        FUN_00352a58();
        FUN_0031b560();
        FUN_001fc0f4();
        FUN_00351c70();
        FUN_001fb194();
        FUN_0036b118(ctx);
    }
    if ((((-1 < (long)unaff_x21) && (unaff_x21 >> ((ulong)*(byte *)(*unaff_x20 + 0x20) & 0x3f) == 0))
        && (FUN_00359a10(), (extraout_x9 & 1) != 0)) && (cls == *(int *)(extraout_x8 + 0x24))) {
        FUN_00354ef8(FUN_0001a1c8,
                     *(long *)(extraout_x8 + 0x38) + *(long *)(*(long *)(l3 + -8) + 0x48) * unaff_x21,
                     unaff_x30);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001f2bf4 @ 0x001f2bf4   (est. cl4_sched_class_dispatch)
 * Ghidra: void FUN_001f2bf4(undefined8 param_1, undefined8 param_2, int param_3)
 * Dispatches a scheduler entry by class: takes the CNode, on fast path runs the
 * insert op; validates the slot bit and class, then runs the class hook
 * FUN_00354d2c and method dispatch at +0x28; else panics.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fc0f4 insert; +0x28 dispatch; noreturn panic. */
void cl4_sched_class_dispatch(word_t a, word_t b, int cls)
{
    FUN_00354a34();
    FUN_0035316c();
    ulong cn = FUN_003a261c(*unaff_x20);
    if ((cn & 1) == 0) {
        long ctx = *unaff_x20;
        *unaff_x20 = -0x8000000000000000;
        FUN_0034d014();
        FUN_0031b560();
        FUN_001fc0f4();
        FUN_003518a0();
        FUN_001fb194();
        FUN_0036b118(ctx);
    }
    if ((((-1 < (long)unaff_x22) &&
         (long l2 = *unaff_x20, unaff_x22 >> ((ulong)*(byte *)(l2 + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(l2 + (unaff_x22 >> 6) * 8 + 0x40) >> (unaff_x22 & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(l2 + 0x24))) {
        FUN_00354d2c(*(word_t *)(l2 + 0x38));
        /* WARNING: could not recover jumptable at 0x1f2cf0; indirect jump as call */
        (**(code **)(extraout_x16 + 0x28))(extraout_x8 + *(long *)(extraout_x16 + 0x48) * unaff_x22);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001f2ec4 @ 0x001f2ec4   (est. cl4_sched_get_cnode)
 * Ghidra: void FUN_001f2ec4(void)
 * Returns the caller's CNode word.
 * Confidence: low
 * Notes: trivial accessor. */
void cl4_sched_get_cnode(void)
{
    FUN_003a261c(*unaff_x20);
}

/* FUN_001f2ee0 @ 0x001f2ee0   (est. cl4_sched_desc_alloc_pair)
 * Ghidra: undefined * FUN_001f2ee0(void)
 * Allocates a 5-word descriptor (zone 0xd5f1), fills it with the caller context
 * fields and returns its method table &DAT_001f2f54.
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0xd5f1; method table &DAT_001f2f54. */
word_t *cl4_sched_desc_alloc_pair(void)
{
    FUN_0008409c();
    word_t *p = (word_t *)FUN_0036a908(0x28, 0xd5f1);
    *unaff_x21 = (long)p;
    p[1] = unaff_x20;
    word_t v2 = *unaff_x20;
    word_t v3 = *(word_t *)(unaff_x19 + 0x10);
    p[3] = *(word_t *)(unaff_x19 + 0x18);
    p[2] = v3;
    p[4] = *(word_t *)(unaff_x19 + 0x20);
    p[0] = v2;
    FUN_00359aec(p, p);
    return &DAT_001f2f54;
}

/* FUN_001f2f80 @ 0x001f2f80   (est. cl4_sched_desc_release_cb)
 * Ghidra: void FUN_001f2f80(undefined8 *param_1, undefined8 param_2, code *param_3, code *param_4)
 * Release callback for a scheduler descriptor: invokes param_3 over the five
 * payload words, calls param_4 with the first word, and releases the descriptor.
 * Confidence: low
 * Notes: callback over payload; thunk_FUN_00012568 release. */
void cl4_sched_desc_release_cb(word_t *desc, word_t a, code *cb, code *cb2)
{
    word_t *p = (word_t *)*desc;
    (*cb)(p[1], p, p[2], p[3], p[4]);
    (*cb2)(*p);
    cl4_obj_release(p);   /* thunk_FUN_00012568 */
}

/* FUN_001f2fd0 @ 0x001f2fd0   (est. cl4_sched_cross_apply)
 * Ghidra: void FUN_001f2fd0(undefined8 param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Cross-applies a transform over two scheduler regions: computes both index
 * strides and invokes the owner methods to copy one slot region to another.
 * Confidence: low
 * Notes: FUN_00258c60 index; method +0x20; FUN_0019ce60 copy. */
void cl4_sched_cross_apply(word_t a, word_t b, word_t c, long sched)
{
    FUN_00084220();
    FUN_0008409c();
    word_t v4 = *(word_t *)(sched + 0x18);
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348f38();
    word_t i1 = FUN_00258c60(c, *(word_t *)(*unaff_x20 + 0x18), sched);
    long ctx = *unaff_x20;
    code *m = *(code **)(extraout_x16 + 0x20);
    long stride = *(long *)(extraout_x16 + 0x48);
    long off1 = stride * unaff_x21;
    FUN_00353c24(i1, *(long *)(ctx + 0x38) + off1);
    (*m)();
    long off2 = stride * unaff_x19;
    FUN_0019ce60(*(long *)(ctx + 0x38) + off2, 1, *(long *)(ctx + 0x38) + off1, v4);
    FUN_0035139c(*(long *)(ctx + 0x38) + off2);
    (*m)();
    FUN_00084234(unaff_x30);
}

/* FUN_001f30b4 @ 0x001f30b4   (est. cl4_sched_dict_access)
 * Ghidra: void FUN_001f30b4(undefined8 param_1, ulong *param_2, long param_3)
 * Dictionary-style scheduler slot access: validates the key/class, and on the
 * fast path inserts (FUN_001fc0f4) then dispatches the slot via +0x28; else
 * panics with a Swift NativeDictionary fatal error (multiple string refs).
 * Confidence: low
 * Notes: strings s_Fatal_error / s_Attempting_to_access_Dictionary / s_Swift_
 *   NativeDictionary confirm a dictionary-backed slot table; noreturn panic. */
void cl4_sched_dict_access(word_t a, ulong *kv, long sched)
{
    ulong key = *kv;
    ulong cls = kv[1];
    word_t v1 = *(word_t *)(sched + 0x10);
    long v2 = *(long *)(sched + 0x18);
    word_t v6 = *(word_t *)(sched + 0x20);
    ulong cn = FUN_001f2ec4();
    if ((cn & 1) == 0) {
        long ctx = *unaff_x20;
        *unaff_x20 = -0x8000000000000000;
        FUN_0031b560(0, v1, v2, v6);
        FUN_001fc0f4();
        FUN_001fb194();
        FUN_0036b118(ctx);
    }
    if ((((-1 < (long)key) &&
         (long l5 = *unaff_x20, key >> ((ulong)*(byte *)(l5 + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(l5 + (key >> 6) * 8 + 0x40) >> (key & 0x3f) & 1) != 0)) &&
        ((int)cls == *(int *)(l5 + 0x24))) {
        long l5 = FUN_001f0bb4();
        (**(code **)(*(long *)(v2 + -8) + 0x28))
            (l5 + *(long *)(*(long *)(v2 + -8) + 0x48) * key, a, v2);
        FUN_0001a1c8();
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, s_Attempting_to_access_Dictionary_e_005cf210, 0x3f, 2,
                 s_Swift_NativeDictionary_swift_005be800, 0x1c, 2, 0x120, 1);
}

/* FUN_001f3220 @ 0x001f3220   (est. cl4_sched_alloc_fill_requeue)
 * Ghidra: undefined1 * FUN_001f3220(long *param_1, undefined8 *param_2, undefined8 param_3)
 * Allocates a 5-word descriptor (zone 0x874e) and fills it through
 * FUN_001f2a70 with the caller caps + context; returns the method table &LAB_001f3298.
 * Confidence: low
 * Notes: FUN_0036a908 alloc; FUN_001f2a70 requeue fill; &LAB_001f3298. */
word_t *cl4_sched_alloc_fill_requeue(long *out, word_t *caps, word_t ctx)
{
    long d = FUN_0036a908(0x28, 0x874e);
    *out = d;
    word_t v = FUN_001f2a70(d, *caps, *(uint *)(caps + 1), ctx);
    *(word_t *)(d + 0x20) = v;
    return &LAB_001f3298;
}

/* FUN_001f329c @ 0x001f329c   (est. cl4_sched_syscall_prep)
 * Ghidra: void FUN_001f329c(undefined8 param_1, undefined8 *param_2, undefined8 param_3,
 *   undefined8 param_4)
 * Prepares a scheduler syscall: packs the caller capability words into a local
 * tuple and forwards through FUN_00256f34 with the dispatch table.
 * Confidence: low
 * Notes: DAT_0060e208/DAT_0060e230/LAB_0060e218 dispatch table. */
void cl4_sched_syscall_prep(word_t a, word_t *caps, word_t c, word_t d)
{
    word_t local_30 = *caps;
    uint local_28 = *(uint *)(caps + 1);
    word_t local_20 = caps[2];
    uint local_18 = *(uint *)(caps + 3);
    FUN_00256f34(a, &local_30, c, d, &DAT_0060e208, &DAT_0060e230, &LAB_0060e218);
}

/* FUN_001f32f8 @ 0x001f32f8   (est. cl4_sched_syscall_desc_alloc)
 * Ghidra: undefined1 [16] FUN_001f32f8(long *param_1, undefined8 *param_2, undefined8 param_3,
 *   undefined8 param_4)
 * Allocates a 0x88-byte syscall descriptor (zone 0x5da0), fills it with the
 * caller caps/context, and returns a 16-byte descriptor with method
 * FUN_001f33b8.
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0x5da0; FUN_00256b80 fill; method FUN_001f33b8. */
cl4_desc_t cl4_sched_syscall_desc_alloc(long *out, word_t *caps, word_t c, word_t d)
{
    long s = FUN_0036a908(0x88, 0x5da0);
    *out = s;
    *(word_t *)(s + 0x78) = c;
    *(word_t *)(s + 0x80) = d;
    *(word_t *)(s + 0x70) = unaff_x20;
    uint w1 = *(uint *)(caps + 1);
    word_t w2 = caps[2];
    uint w3 = *(uint *)(caps + 3);
    *(word_t *)(s + 0x50) = *caps;
    *(uint *)(s + 0x58) = w1;
    *(word_t *)(s + 0x60) = w2;
    *(uint *)(s + 0x68) = w3;
    FUN_00256b80(s, caps, c, d, &DAT_0060e208, &DAT_0060e230, &LAB_0060e218);
    cl4_desc_t r;
    r.hi = s;
    r.lo = FUN_001f33b8;
    return r;
}

/* FUN_001f33b8 @ 0x001f33b8   (est. cl4_sched_syscall_desc_release)
 * Ghidra: void FUN_001f33b8(undefined8 *param_1, uint param_2)
 * Releases a syscall descriptor: on the non-teardown path calls the two teardown
 * hooks; otherwise repacks the payload into a stack tuple, runs the shared
 * release path and frees the inner state, then releases the descriptor.
 * Confidence: low
 * Notes: param_2 bit selects teardown; FUN_00256f34/FUN_00356710 hooks;
 *   thunk_FUN_00012568 final release. */
void cl4_sched_syscall_desc_release(word_t *desc, uint mode)
{
    word_t *p = (word_t *)*desc;
    if ((mode & 1) == 0) {
        FUN_00356710(desc, mode, p[0xf], p[0x10]);
        FUN_00256f34(p);
    } else {
        p[5] = *p;
        *(uint *)(p + 6) = *(uint *)(p + 1);
        p[7] = p[2];
        *(uint *)(p + 8) = *(uint *)(p + 3);
        p[9] = p[4];
        thunk_FUN_0036b270();
        FUN_00356710();
        FUN_003511f0(p + 5);
        FUN_00256f34();
        FUN_003a25d4(p[4]);
    }
    cl4_obj_release(p);   /* thunk_FUN_00012568 */
}

/* FUN_001f345c @ 0x001f345c   (est. cl4_sched_op_a2) */
/* Ghidra: void FUN_001f345c(void) — alias of FUN_001d9b00. Confidence: low */
void cl4_sched_op_a2(void) { FUN_001d9b00(); }

/* FUN_001f3460 @ 0x001f3460   (est. cl4_sched_op_b2) */
/* Ghidra: void FUN_001f3460(void) — alias of FUN_001d9b00. Confidence: low */
void cl4_sched_op_b2(void) { FUN_001d9b00(); }

/* FUN_001f3494 @ 0x001f3494   (est. cl4_sched_cb_dispatch)
 * Ghidra: void FUN_001f3494(long param_1, undefined8 param_2, code *param_3)
 * Dispatches a callback over three context fields of param_1 plus the caller
 * slot, then runs the post hook FUN_00357670.
 * Confidence: low
 * Notes: (*param_3)(slot, f0x10, f0x18, f0x20); FUN_00357670 tail. */
void cl4_sched_cb_dispatch(long src, word_t a, code *cb)
{
    (*cb)(*unaff_x20, *(word_t *)(src + 0x10), *(word_t *)(src + 0x18), *(word_t *)(src + 0x20));
    FUN_00357670();
}

/* FUN_001f34d4 @ 0x001f34d4   (est. cl4_sched_alloc_fill_dispatch)
 * Ghidra: undefined * FUN_001f34d4(long *param_1, undefined8 *param_2, long param_3)
 * Allocates a 5-word descriptor (zone 0x6f75) and fills it via FUN_001f3554 with
 * the caller caps + context fields; returns method table &DAT_003471a4.
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0x6f75; FUN_001f3554 fill; &DAT_003471a4. */
word_t *cl4_sched_alloc_fill_dispatch(long *out, word_t *caps, long ctx)
{
    long d = FUN_0036a908(0x28, 0x6f75);
    *out = d;
    word_t v = FUN_001f3554(d, *caps, *(uint *)(caps + 1), *unaff_x20,
                            *(word_t *)(ctx + 0x10), *(word_t *)(ctx + 0x18), *(word_t *)(ctx + 0x20));
    *(word_t *)(d + 0x20) = v;
    return &DAT_003471a4;
}

/* FUN_001f3554 @ 0x001f3554   (est. cl4_sched_desc_init_dispatch)
 * Ghidra: undefined1 [16] FUN_001f3554(long *param_1, ...6 args)
 * Initializes a dispatch descriptor: records the caller object + method vector,
 * allocates inner state (zone 0x278c), fills it via FUN_001f2a6c and returns the
 * 16-byte descriptor (data + &DAT_003471a8).
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0x278c; FUN_001f2a6c fill; &DAT_003471a8. */
cl4_desc_t cl4_sched_desc_init_dispatch(long *out, word_t a, word_t b, word_t c, word_t d, long src)
{
    long mv = *(long *)(src + -8);
    out[0] = src;
    out[1] = mv;
    long st = FUN_0036a908(*(word_t *)(mv + 0x40), 0x278c);
    out[2] = st;
    FUN_001f2a6c(st, a, b, c);
    cl4_desc_t r;
    r.hi = st;
    r.lo = &DAT_003471a8;
    return r;
}

/* FUN_001f3608 @ 0x001f3608   (est. cl4_sched_syscall_forward)
 * Ghidra: void FUN_001f3608(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Forwards a scheduler syscall: resolves the target object (FUN_00376820 on a
 * global table) and dispatches through FUN_00256b80.
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004e90b0); FUN_00256b80 dispatch. */
void cl4_sched_syscall_forward(word_t a, word_t b, word_t c)
{
    word_t tgt = FUN_00376820(&DAT_004e90b0);
    FUN_00256b80(a, b, c, tgt, &DAT_0060e208, &DAT_0060e230, &LAB_0060e218);
}

/* FUN_001f367c @ 0x001f367c   (est. cl4_sched_cb6_dispatch)
 * Ghidra: void FUN_001f367c(undefined8 *param_1, long param_2, undefined8 param_3, code *param_4)
 * Dispatches a callback over the caller caps + context fields then runs the post
 * hook FUN_00357670.
 * Confidence: low
 * Notes: (*param_4)(cap0, cap1, slot, f0x10, f0x18, f0x20); FUN_00357670. */
void cl4_sched_cb6_dispatch(word_t *caps, long ctx, word_t c, code *cb)
{
    (*cb)(*caps, *(uint *)(caps + 1), *unaff_x20,
          *(word_t *)(ctx + 0x10), *(word_t *)(ctx + 0x18), *(word_t *)(ctx + 0x20));
    FUN_00357670();
}

/* FUN_001f36c8 @ 0x001f36c8   (est. cl4_sched_read5_fill)
 * Ghidra: void FUN_001f36c8(undefined8 *param_1)
 * Reads a 5-word capability tuple: builds the descriptor via thunk_FUN_001fca54,
 * expands it through FUN_003510c4 + FUN_001f6b30 and stores into param_1.
 * Confidence: low
 * Notes: thunk_FUN_001fca54; FUN_003510c4; FUN_001f6b30. */
void cl4_sched_read5_fill(word_t *out)
{
    thunk_FUN_001fca54(auStack_88, *unaff_x20);
    FUN_003510c4(&local_60, auStack_88);
    FUN_001f6b30();
    out[1] = uStack_58;
    out[0] = local_60;
    out[3] = uStack_48;
    out[2] = uStack_50;
    out[4] = local_40;
}

/* FUN_001f3734 @ 0x001f3734   (est. cl4_sched_read5_fill_b)
 * Ghidra: void FUN_001f3734(void)
 * Reads a 5-word capability tuple into the caller frame (variant of FUN_001f36c8
 * with FUN_0034b788 instead of FUN_003510c4).
 * Confidence: low
 * Notes: mirror of FUN_001f36c8. */
void cl4_sched_read5_fill_b(void)
{
    FUN_0034b85c();
    thunk_FUN_001fca54(auStack_88);
    FUN_0034b788(&local_60, auStack_88);
    FUN_001f6b30();
    extraout_x8[1] = uStack_58;
    extraout_x8[0] = local_60;
    extraout_x8[3] = uStack_48;
    extraout_x8[2] = uStack_50;
    extraout_x8[4] = local_40;
}

/* FUN_001f388c @ 0x001f388c   (est. cl4_sched_op_dispatch5)
 * Ghidra: void FUN_001f388c(void)
 * Runs a 5-argument scheduler op: preps the state, invokes the callback, then
 * the dispatch and teardown helpers.
 * Confidence: low
 * Notes: FUN_00357f84/FUN_00352ddc prep; (*in_x4) callback; FUN_001a6ab8 tail. */
void cl4_sched_op_dispatch5(void)
{
    FUN_00357f84();
    FUN_00352ddc();
    (*in_x4)();
    FUN_000776c0();
    FUN_00100efc();
    FUN_001a6ab8();
}

/* FUN_001f38d8 @ 0x001f38d8   (est. cl4_sched_op_trace)
 * Ghidra: void FUN_001f38d8(void)
 * Traces a scheduler op: derives the state (FUN_0031b65c) and invokes the shared
 * op FUN_001a6ab8 with a descriptor pointer and two constants.
 * Confidence: low
 * Notes: constants 0xd000000000000011 / 0x80000000005cf260 / 0x66bb78. */
void cl4_sched_op_trace(void)
{
    word_t st = FUN_0031b65c(0);
    FUN_001a6ab8(0xd000000000000011, 0x80000000005cf260, st, 0x66bb78);
}

/* FUN_001f3988 @ 0x001f3988   (est. cl4_sched_find_set_bit)
 * Ghidra: void FUN_001f3988(undefined8 param_1, long param_2)
 * Scans the scheduler slot bitmap for the next set bit (bit-reverse + LZCOUNT),
 * dispatches the found slot through the owner method at +0x10, and advances the
 * cursor. The 5-word iterator state lives in unaff_x20.
 * Confidence: low
 * Notes: LZCOUNT bit scan; SoftwareBreakpoint overflow; method +0x10 dispatch. */
void cl4_sched_find_set_bit(word_t a, long sched)
{
    word_t w1 = unaff_x20[1], w0 = unaff_x20[0];
    long l1 = unaff_x20[2], l9 = unaff_x20[3];
    ulong u6 = unaff_x20[4];
    if (u6 == 0) {
        long l8 = l9;
        do {
            l9 = l8 + 1;
            if (SCARRY8(l8, 1)) {     /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f3ac8);
            }
            if ((long)(l1 + 0x40U >> 6) <= l9) {
                FUN_000839d8(a, 1, 1, *(word_t *)(sched + 0x10));
                u6 = 0;
                goto store;
            }
            u6 = *(ulong *)(unaff_x20[1] + l9 * 8);
            l8 = l8 + 1;
        } while (u6 == 0);
    }
    ulong u3 = bitrev_word(u6);       /* full 64-bit bit reversal (see body) */
    u6 = u6 - 1 & u6;
    long l8 = *(long *)(sched + 0x10);
    word_t u2 = *(word_t *)(sched + 0x18);
    word_t u7 = *(word_t *)(sched + 0x20);
    long l5 = FUN_001f7d28(w0);
    (**(code **)(*(long *)(l8 + -8) + 0x10))
        (a, l5 + *(long *)(*(long *)(l8 + -8) + 0x48) * (LZCOUNT(u3 >> 0x20 | u3 << 0x20) | l9 << 6), l8);
    FUN_0001a1c8(w0, l8, u2, u7);
    FUN_000839d8(a, 0, 1, l8);
    l8 = l9;
store:
    unaff_x20[1] = w1;
    unaff_x20[0] = w0;
    unaff_x20[2] = l1;
    unaff_x20[3] = l8;
    unaff_x20[4] = u6;
}

/* FUN_001f3acc @ 0x001f3acc   (est. cl4_sched_iter_next)
 * Ghidra: void FUN_001f3acc(void)
 * Advances a scheduler iterator: skips empty bitmap words, dispatches the next
 * set slot through the owner method at +0x10, and finalizes with the drain tail.
 * Confidence: low
 * Notes: SoftwareBreakpoint overflow; method +0x10; FUN_000839d8 drain. */
void cl4_sched_iter_next(void)
{
    FUN_00357cb4();
    FUN_00358f18();
    if (extraout_x9 == 0) {
        long l2;
        do {
            l2 = unaff_x23 + 1;
            if (SCARRY8(unaff_x23, 1)) {  /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f3ba0);
            }
            if ((long)(unaff_x22 + 0x40U >> 6) <= l2) {
                FUN_0034c6c4();
                FUN_000839d8();
                goto done;
            }
            unaff_x23 = unaff_x23 + 1;
        } while (*(long *)(*(long *)(unaff_x20 + 8) + l2 * 8) == 0);
    }
    l2 = FUN_0034f264();
    (**(code **)(*(long *)(*(long *)(l2 + 0x18) + -8) + 0x10))();
    FUN_0034aed0();
    FUN_000839d8();
done:
    FUN_003596e4();
    FUN_00357c74(extraout_x1);
}

/* FUN_001f3ba0 @ 0x001f3ba0   (est. cl4_sched_iter_dispatch)
 * Ghidra: void FUN_001f3ba0(undefined8 param_1)
 * Dispatches the next set slot from the scheduler iterator (two cursor paths:
 * loaded bitmap word vs fresh scan), invoking the owner method at +0x10 and
 * draining with FUN_000839d8.
 * Confidence: low
 * Notes: SoftwareBreakpoint overflow; two bit-scan paths; method +0x10. */
void cl4_sched_iter_dispatch(word_t a)
{
    long l2, l4;
    ulong u3;
    if (unaff_x20[4] == 0) {
        FUN_00357ee4();
        l2 = extraout_x8_00;
        l4 = extraout_x10;
        do {
            if (SCARRY8(l2, 1)) {     /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f3c4c);
            }
            if (l4 <= l2 + 1) {
                FUN_0034c6c4();
                goto drain;
            }
            FUN_00353664();
            l2 = extraout_x8_01;
            l4 = extraout_x10_00;
        } while (extraout_x11 == 0);
        l2 = FUN_0035364c();
        u3 = extraout_x8_02 | extraout_x9_00 << 6;
    } else {
        l2 = FUN_0035229c();
        u3 = extraout_x9 | extraout_x8 << 6;
    }
    l4 = *(long *)(*(long *)(l2 + 0x18) + -8);
    (**(code **)(l4 + 0x10))
        (a, *(long *)(*unaff_x20 + 0x38) + *(long *)(l4 + 0x48) * u3, *(long *)(l2 + 0x18));
    FUN_0034b744();
drain:
    FUN_000839d8();
}

/* FUN_001f3c4c @ 0x001f3c4c   (est. cl4_sched_find_set_bit_b)
 * Ghidra: void FUN_001f3c4c(undefined8 param_1, long param_2)
 * Bitmap slot find/dispatch variant of FUN_001f3988 (uses FUN_001f0bb4 for the
 * base pointer and param_2+0x18 for the drain target).
 * Confidence: low
 * Notes: LZCOUNT bit scan; method +0x10; SoftwareBreakpoint overflow. */
void cl4_sched_find_set_bit_b(word_t a, long sched)
{
    word_t w1 = unaff_x20[1], w0 = unaff_x20[0];
    long l1 = unaff_x20[2], l9 = unaff_x20[3];
    ulong u6 = unaff_x20[4];
    if (u6 == 0) {
        long l8 = l9;
        do {
            l9 = l8 + 1;
            if (SCARRY8(l8, 1)) {     /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f3d8c);
            }
            if ((long)(l1 + 0x40U >> 6) <= l9) {
                FUN_000839d8(a, 1, 1, *(word_t *)(sched + 0x18));
                u6 = 0;
                goto store;
            }
            u6 = *(ulong *)(unaff_x20[1] + l9 * 8);
            l8 = l8 + 1;
        } while (u6 == 0);
    }
    ulong u3 = bitrev_word(u6);
    u6 = u6 - 1 & u6;
    word_t u2 = *(word_t *)(sched + 0x10);
    long l8 = *(long *)(sched + 0x18);
    word_t u7 = *(word_t *)(sched + 0x20);
    long l5 = FUN_001f0bb4(w0);
    (**(code **)(*(long *)(l8 + -8) + 0x10))
        (a, l5 + *(long *)(*(long *)(l8 + -8) + 0x48) * (LZCOUNT(u3 >> 0x20 | u3 << 0x20) | l9 << 6), l8);
    FUN_0001a1c8(w0, u2, l8, u7);
    FUN_000839d8(a, 0, 1, l8);
    l8 = l9;
store:
    unaff_x20[1] = w1;
    unaff_x20[0] = w0;
    unaff_x20[2] = l1;
    unaff_x20[3] = l8;
    unaff_x20[4] = u6;
}

/* FUN_001f3d8c @ 0x001f3d8c   (est. cl4_sched_iter_equals)
 * Ghidra: bool FUN_001f3d8c(long param_1, long param_2)
 * Compares two scheduler slot iterators for equality: walks both slot sets
 * (bit-reverse bit scan), compares each 5-word payload via the shared compare
 * FUN_0031997c, and returns true if all slots match. Handles the identical-
 * object short-circuit.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_0006a4c0/FUN_0008e5d8 compare; SoftwareBreakpoint
 *   overflow; failure tail FUN_00344e54. */
bool cl4_sched_iter_equals(long a, long b)
{
    if (a == b) {
        return true;
    }
    if (*(long *)(a + 0x10) == *(long *)(b + 0x10)) {
        FUN_001fca54(&local_98, a);
        thunk_FUN_0036b270(a);
        long l8 = lStack_80;
        ulong u9 = local_78;
        if (local_78 == 0) goto scan_advance;
scan:
        ulong u7 = bitrev_word(u9);
        u9 = u9 - 1 & u9;
        u7 = LZCOUNT(u7 >> 0x20 | u7 << 0x20) | lStack_80 << 6;
        for (;;) {
            FUN_0031996c(*(long *)(local_98 + 0x30) + u7 * 0x28, &local_130);
            FUN_0031996c(*(long *)(local_98 + 0x38) + u7 * 0x28, &local_108);
            l8 = lStack_80;
            for (;;) {
                if (lStack_118 == 0) goto fail_ret;
                uint128_t r = FUN_001f9964(&local_130);
                FUN_003199ac(&local_130);
                if ((r_hi & 1) == 0) {
                    FUN_00344e54(&local_98, &DAT_00657590, &DAT_004f1920);
                    FUN_003199ac(&local_160);
                    return bVar5;
                }
                FUN_0031996c(*(long *)(b + 0x38) + r_lo * 0x28, auStack_188);
                word_t u2 = uStack_168, u1 = local_170;
                FUN_0006a4c0(auStack_188, local_170);
                code *c = (code *)FUN_0008e5d8(u2);
                (*c)(auStack_1b0, u1, u2);
                u2 = uStack_190;
                u1 = local_198;
                FUN_0006a4c0(auStack_1b0, local_198);
                FUN_0006a4c0(&local_160, uStack_148);
                code *c2 = (code *)FUN_0008e5d8(uStack_148);
                (*c2)(auStack_1d8, uStack_148, uStack_148);
                code *c3 = (code *)FUN_0031997c(u2);
                u7 = (*c3)(auStack_1d8, u1, u2);
                FUN_000026e8(auStack_1d8);
                FUN_000026e8(auStack_1b0);
                FUN_003199ac(auStack_188);
                FUN_003199ac(&local_160);
                if ((u7 & 1) == 0) goto fail_ret;
                lStack_80 = l8;
                if (u9 != 0) goto scan;
            }
        }
scan_advance:
        for (;;) {
            lStack_80 = l8 + 1;
            if (SCARRY8(l8, 1)) {     /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f4084);
            }
            if ((long)(local_88 + 0x40U >> 6) <= lStack_80) break;
            u9 = *(ulong *)(lStack_90 + lStack_80 * 8);
            l8 = l8 + 1;
            if (u9 != 0) {
                ulong u7 = bitrev_word(u9);
                u9 = u9 - 1 & u9;
                u7 = LZCOUNT(u7 >> 0x20 | u7 << 0x20) | lStack_80 * 0x40;
                goto scan_body;
            }
        }
        u9 = 0;
        /* zero the whole iterator */
        local_f8 = 0; uStack_100 = 0; local_e8 = 0; uStack_f0 = 0; lStack_118 = 0;
        local_120 = 0; local_108 = 0; local_110 = 0; uStack_128 = 0; local_130 = 0;
    }
fail_ret:
    FUN_00344e54(&local_98, &DAT_00657590, &DAT_004f1920);
    return false;
}

/* FUN_001f4084 @ 0x001f4084   (est. cl4_sched_iter_member)
 * Ghidra: undefined8 FUN_001f4084(long param_1, long param_2)
 * Membership test on the scheduler slot set: walks param_1's bitmap and checks
 * whether every payload slot also appears in param_2 (via FUN_001f98a8 key match
 * against the value array); returns 1 on full containment, 0 otherwise.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f98a8 key; SoftwareBreakpoint overflow. */
word_t cl4_sched_iter_member(long a, long b)
{
    if (a == b) {
        return 1;
    }
    if (*(long *)(a + 0x10) != *(long *)(b + 0x10)) {
        return 0;
    }
    FUN_001fca54(&local_78, a);
    ulong u5 = local_58;
    do {
        if (u5 == 0) {
            long l4;
            do {
                l4 = lStack_60 + 1;
                if (SCARRY8(lStack_60, 1)) {  /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1f41b4);
                }
                if ((long)(local_68 + 0x40U >> 6) <= l4) {
                    thunk_FUN_0036b270(a);
                    FUN_00344e54(&local_78, &DAT_00657650, &DAT_004f2130);
                    return 1;
                }
                u5 = *(ulong *)(lStack_70 + l4 * 8);
                lStack_60 = lStack_60 + 1;
            } while (u5 == 0);
            uVar2 = bitrev_word(u5);
            u5 = u5 - 1 & u5;
        } else {
            uVar2 = bitrev_word(u5);
            u5 = u5 - 1 & u5;
            l4 = lStack_60;
        }
        uVar2 = LZCOUNT(uVar2) | l4 << 6;
        long l6 = *(long *)(*(long *)(local_78 + 0x38) + uVar2 * 8);
        uint128_t r = FUN_001f98a8(*(word_t *)(*(long *)(local_78 + 0x30) + uVar2 * 8));
    } while (((r_hi & 1) != 0) &&
             (lStack_60 = l4, *(long *)(*(long *)(b + 0x38) + r_lo * 8) == l6));
    thunk_FUN_0036b270(a);
    FUN_00344e54(&local_78, &DAT_00657650, &DAT_004f2130);
    return 0;
}

/* FUN_001f41b4 @ 0x001f41b4   (est. cl4_sched_walk_and_apply)
 * Ghidra: void FUN_001f41b4(...6 args)
 * Walks a scheduler slot set and applies an op to each element: iterates the
 * bitmap (bit-reverse scan), dispatches each slot through the owner methods,
 * checks the completion (FUN_001f99f4), and on success runs the apply hook and
 * advances; on the mismatch/empty path drains the queue.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f99f4 completion; SoftwareBreakpoint overflow;
 *   long method-vector chain. */
void cl4_sched_walk_and_apply(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f)
{
    uint128_t r = FUN_0008e518();
    long l6 = r_hi, l9 = r_lo;
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003493c4();
    FUN_0034d5a8();
    (*DAT_00658c00)();
    FUN_0034c074();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    FUN_00351ce8();
    word_t u4 = FUN_0035361c();
    FUN_00356fe8(u4, c);
    FUN_0034f554();
    u4 = FUN_00310d68();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_00348a34();
    (*DAT_00658c00)();
    uint8_t same = (l9 == l6);
    if ((bool)same) {
        u4 = 1;
        goto out;
    }
    FUN_00359a04(*(word_t *)(l9 + 0x10));
    if ((bool)same) {
        thunk_FUN_001fca54(local_30, l9);
        FUN_00354128(uStack_28);
        FUN_00353360(local_20 + 0x40U >> 6);
        FUN_00359cb0(extraout_x16_00 + 0x10);
        FUN_00352f88();
        thunk_FUN_0036b270(l9);
        thunk_FUN_0036b270(l6);
        FUN_0036b270(l9);
        ulong u8 = local_10;
        l9 = lStack_18;
        do {
            if (u8 == 0) {
                long l1;
                do {
                    l1 = l9 + 1;
                    if (SCARRY8(l9, 1)) {  /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1f4690);
                    }
                    same = (l1 == local_d8);
                    if (local_d8 <= l1) {
                        u8 = 0;
                        u7 = 1;
                        goto apply;
                    }
                    l9 = l9 + 1;
                } while (*(long *)(local_d0 + l1 * 8) == 0);
                FUN_0034f264();
                u8 = extraout_x11 & extraout_x9;
                l9 = extraout_x8_02;
            } else {
                u8 = u8 - 1 & u8;
            }
            FUN_0035463c();
            FUN_00350cf4(*(word_t *)(unaff_x21 + 0x30));
            FUN_00353e2c(unaff_x28, extraout_x1, c);
            (*extraout_x8_03)();
            FUN_00352038((long)*(int *)(unaff_x24 + 0x30));
            (*extraout_x9_00)(local_50, unaff_x28 + extraout_x8_04, extraout_x1_00, d);
            u7 = 0;
apply:
            FUN_00355be8(unaff_x28, u7);
            FUN_000839d8();
            FUN_00358dac();
            r = FUN_003510dc();
            (*extraout_x8_05)(r_lo, r_hi, u4);
            FUN_0034c4bc(extraout_x10);
            if ((bool)same) {
                FUN_0036b118(l6);
                FUN_0035505c();
                FUN_0036b118();
                FUN_00355ad0(0);
                FUN_0031b674();
                FUN_0034bf0c();
                (**(code **)(extraout_x16_01 + 8))(local_30);
                u4 = 1;
                goto out;
            }
            int i2 = *(int *)(unaff_x24 + 0x30);
            FUN_00354d50();
            r = FUN_003508f0();
            (*extraout_x8_06)(r_lo, r_hi, c);
            u7 = FUN_00355eec();
            FUN_00353474(u7, extraout_x10 + i2);
            (*extraout_x8_07)();
            r = FUN_00350914();
            r = FUN_001f99f4(r_lo, r_hi, e);
            FUN_0034d688();
            FUN_00350914();
            u7 = (*extraout_x8_08)();
            if ((r_hi & 1) == 0) {
                FUN_00355ad0(0);
                FUN_0031b674();
                FUN_000841a0();
                (**(code **)(extraout_x16_02 + 8))(local_30);
                FUN_0036b118(l6);
                FUN_0035505c();
                FUN_0036b118();
                FUN_00355224();
                FUN_003514e8();
                (*extraout_x8_11)();
                u4 = 0;
                goto out;
            }
            FUN_00353aec(*(word_t *)(extraout_x16 + 0x10), u7,
                         *(long *)(l6 + 0x38) + *(long *)(extraout_x16 + 0x48) * r_lo);
            (*extraout_x8_09)();
            FUN_00350adc(f);
            FUN_0035072c();
            FUN_00352e60();
            u5 = (*extraout_x8_10)();
            code *pc = *(code **)(extraout_x16 + 8);
            (*pc)(local_78, d);
            FUN_003514e8();
            (*pc)();
            unaff_x21 = l6;
        } while ((u5 & 1) != 0);
        FUN_0036b118(l6);
        FUN_0035505c();
        FUN_0036b118();
        FUN_00355ad0(0);
        FUN_0031b674();
        FUN_0034bf0c();
        (**(code **)(extraout_x16_03 + 8))(local_30);
    }
    u4 = 0;
out:
    FUN_0008e500(u4, unaff_x30);
}

/* FUN_001f4690 @ 0x001f4690   (est. cl4_sched_walk_and_apply_b)
 * Ghidra: void FUN_001f4690(...6 args)
 * Walk-and-apply variant of FUN_001f41b4 (uses FUN_00358960 for the apply hook
 * and a different dispatcher chain).
 * Confidence: low
 * Notes: mirror of FUN_001f41b4. */
void cl4_sched_walk_and_apply_b(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f)
{
    FUN_0008e518();
    FUN_00351a80();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003493c4();
    FUN_0034d5a8();
    (*DAT_00658c00)();
    FUN_0034c074();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    FUN_00351ce8();
    word_t u4 = FUN_0035361c();
    FUN_003722e4(u4, c, d);
    FUN_0034da88();
    u4 = FUN_00310d68();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_00348bbc();
    (*DAT_00658c00)();
    FUN_0034b3d8();
    if (unaff_x20 == unaff_x22) {
        u4 = 1;
        goto out;
    }
    uint8_t same = *(long *)(unaff_x20 + 0x10) == *(long *)(unaff_x22 + 0x10);
    if ((bool)same) {
        thunk_FUN_001fca54(&local_30);
        FUN_00353360(uStack_28);
        FUN_00353b64(local_20 + 0x40U >> 6);
        FUN_00359cb0(extraout_x16_00 + 0x10);
        FUN_00352f88();
        FUN_0036b270();
        FUN_003573cc();
        long l8 = lStack_18;
        ulong u9 = local_10;
        do {
            if (u9 == 0) {
                long l1;
                do {
                    l1 = l8 + 1;
                    if (SCARRY8(l8, 1)) {  /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1f4b1c);
                    }
                    same = (l1 == local_e0);
                    if (local_e0 <= l1) {
                        u9 = 0;
                        u6 = 1;
                        goto apply;
                    }
                    l8 = l8 + 1;
                } while (*(long *)(local_d8 + l1 * 8) == 0);
                FUN_0034f264();
                u9 = extraout_x11 & extraout_x9;
                l8 = extraout_x8_02;
            } else {
                FUN_0034c194();
            }
            FUN_00350cf4(*(word_t *)(local_30 + 0x30));
            FUN_00354b80(unaff_x23, extraout_x1, c);
            (*extraout_x8_03)();
            FUN_00352038((long)*(int *)(unaff_x19 + 0x30));
            (*extraout_x9_00)(local_50, unaff_x23 + extraout_x8_04, extraout_x1_00, d);
            u6 = 0;
apply:
            FUN_00350774(unaff_x23, u6);
            FUN_000839d8();
            FUN_00354b14();
            r = FUN_00351274();
            (*extraout_x8_05)(r_lo, r_hi, u4);
            FUN_00349f3c(unaff_x25);
            if ((bool)same) {
                FUN_0031b674(0, c, d, e);
                FUN_0034bf0c();
                (**(code **)(extraout_x16_01 + 8))(&local_30);
                u4 = 1;
                goto out;
            }
            int i2 = *(int *)(unaff_x19 + 0x30);
            FUN_00354d50();
            r = FUN_003509e0();
            (*extraout_x8_06)(r_lo, r_hi, c);
            FUN_00355eec();
            (*extraout_x8_07)(unaff_x21, unaff_x25 + i2, d);
            r = FUN_00084174();
            r = FUN_001f99f4(r_lo, r_hi, e);
            FUN_0034d688();
            FUN_00084174();
            u6 = (*extraout_x8_08)();
            if ((r_hi & 1) == 0) {
                FUN_0031b674(0, c, d, e);
                FUN_000841a0();
                (**(code **)(extraout_x16_02 + 8))(&local_30);
                FUN_00355224();
                FUN_00350c38();
                (*extraout_x8_11)();
                u4 = 0;
                goto out;
            }
            r = FUN_00358960(*(word_t *)(extraout_x16 + 0x10), u6,
                             *(long *)(unaff_x22 + 0x38) + *(long *)(extraout_x16 + 0x48) * r_lo);
            (*extraout_x8_09)(r_lo, r_hi, d);
            u6 = FUN_0034d49c(f);
            FUN_003512cc(u6, unaff_x21);
            u5 = (*extraout_x8_10)();
            code *pc = *(code **)(extraout_x16 + 8);
            FUN_00350618();
            (*pc)();
            FUN_00350c38();
            (*pc)();
            unaff_x23 = local_c0;
        } while ((u5 & 1) != 0);
        FUN_0031b674(0, c, d, e);
        FUN_0034bf0c();
        (**(code **)(extraout_x16_03 + 8))(&local_30);
    }
    u4 = 0;
out:
    FUN_0008e500(u4, unaff_x30);
}

/* FUN_001f4b3c @ 0x001f4b3c   (est. cl4_sched_hash_all)
 * Ghidra: void FUN_001f4b3c(undefined8 param_1, long param_2)
 * Computes a running hash (XOR) over every set slot of the scheduler set: for
 * each payload slot, hashes the two words via FUN_00117cc4/FUN_00343a30 and
 * XORs the per-slot hash into the accumulator. Uses the set cardinality mask to
 * bound the scan.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001a8564 per-slot hash; XOR accumulation;
 *   SoftwareBreakpoint overflow. */
void cl4_sched_hash_all(word_t a, long sched)
{
    ulong u6 = 1L << ((ulong)*(byte *)(sched + 0x20) & 0x3f);
    ulong u7 = 0xffffffffffffffff;
    if ((*(byte *)(sched + 0x20) & 0x3f) < 6) {
        u7 = ~(-1L << (u6 & 0x3f));
    }
    u7 = u7 & *(ulong *)(sched + 0x40);
    thunk_FUN_0036b270(sched);
    ulong u8 = 0;
    long l9 = 0;
    do {
        while (u7 != 0) {
            ulong u5 = bitrev_word(u7);
            u7 = u7 - 1 & u7;
            u5 = LZCOUNT(u5 >> 0x20 | u5 << 0x20) | l9 << 6;
            FUN_0031996c(*(long *)(sched + 0x30) + u5 * 0x28, &local_110);
            FUN_0031996c(*(long *)(sched + 0x38) + u5 * 0x28, &local_e8);
            for (;;) {
                word_t u2 = uStack_f0;
                long l1 = lStack_f8;
                if (lStack_f8 == 0) {
                    FUN_0036b118(sched);
                    thunk_FUN_002298d4(u8);
                    return;
                }
                FUN_00117cc4(&local_110, a, 0x48);
                FUN_0006a4c0(&local_140, l1);
                code *c = (code *)FUN_0008e5d8(u2);
                (*c)(auStack_198, l1, u2);
                code *c2 = (code *)FUN_00343a30(uStack_178);
                (*c2)(&local_110, local_180, uStack_178);
                FUN_000026e8(auStack_198);
                FUN_003199ac(&local_140);
                FUN_0006a4c0(&local_170, local_158);
                code *c3 = (code *)FUN_0008e5d8(local_150);
                (*c3)(auStack_198, local_158, local_150);
                code *c4 = (code *)FUN_00343a30(uStack_178);
                (*c4)(&local_110, local_180, uStack_178);
                FUN_000026e8(auStack_198);
                FUN_003199ac(&local_170);
                u8 = FUN_001a8564() ^ u8;
                break;
            }
        }
        long l1 = l9 + 1;
        if (SCARRY8(l9, 1)) {   /* WARNING: does not return */
            SoftwareBreakpoint(1, 0x1f4dc4);
        }
        if ((long)(u6 + 0x3f >> 6) <= l1) {
            u7 = 0;
            /* zero iterator */
            local_d8 = 0; uStack_e0 = 0; local_c8 = 0; uStack_d0 = 0; lStack_f8 = 0;
            local_100 = 0; local_e8 = 0; uStack_f0 = 0; uStack_108 = 0; local_110 = 0;
            continue;
        }
        u7 = ((ulong *)(sched + 0x40))[l1];
        l9 = l1;
    } while (true);
}

/* FUN_001f4dc4 @ 0x001f4dc4   (est. cl4_sched_hash_walk)
 * Ghidra: void FUN_001f4dc4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Walks a scheduler set and computes the running hash over each slot payload:
 * iterates the bitmap, dispatches each slot through the owner methods, hashes
 * the two payload words via FUN_00117cc4/FUN_00350810/FUN_00350b48 and XORs the
 * per-slot hash (FUN_001a8564) into the accumulator.
 * Confidence: low
 * Notes: LZCOUNT bit scan; SoftwareBreakpoint overflow; thunk_FUN_002298d4 tail. */
void cl4_sched_hash_walk(word_t a, word_t b, word_t c)
{
    FUN_0008e518();
    FUN_00353274();
    FUN_00355fb8();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003497b4();
    FUN_003509a4();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    FUN_003509a4();
    word_t u6 = FUN_0035361c();
    FUN_003722e4(u6, c);
    FUN_0034e57c();
    FUN_00310d68();
    FUN_003490b8(&stack0x00000038);
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003489c0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_003509a4();
    thunk_FUN_001fca54(auStack_58, extraout_x1);
    FUN_0035780c();
    FUN_000bd3a4();
    FUN_001f6b30();
    FUN_00357540(local_20);
    FUN_00354b44(extraout_x16_00 + 0x10);
    FUN_00354128(extraout_x16_01 + 0x20);
    FUN_00354570(extraout_x16_00 + 0x20);
    FUN_00355dc0(extraout_x16 + 0x20);
    FUN_00355f40(extraout_x16_00 + 8);
    FUN_00355db4(extraout_x16 + 8);
    thunk_FUN_0036b270(extraout_x1);
    ulong u8 = 0;
    long l3 = lStack_18;
    long l4 = local_10;
    do {
        while (l4 != 0) {
            FUN_0034f884(l3);
            FUN_00350cf4(*(word_t *)(local_30 + 0x30));
            (*extraout_x8_02)(unaff_x27, extraout_x1_00, unaff_x23);
            FUN_00352038((long)*(int *)(unaff_x25 + 0x30));
            FUN_0035a718(unaff_x27 + extraout_x8_03, extraout_x1_01, unaff_x22);
            (*extraout_x9)();
            u6 = 0;
            for (;;) {
                FUN_000839d8(unaff_x27, u6, 1, unaff_x25);
                u6 = FUN_0034f9ec(&stack0x00000030);
                (*extraout_x8_04)(u6, unaff_x27, local_c8);
                FUN_0034e1b0(local_b8);
                if ((bool)in_ZR) {
                    FUN_0036b118(local_30);
                    FUN_003573c0(u8);
                    thunk_FUN_002298d4();
                    FUN_0008e500(unaff_x30);
                    return;
                }
                int i2 = *(int *)(unaff_x25 + 0x30);
                FUN_003510d0(&stack0x00000000);
                r = FUN_0006b6f4();
                (*extraout_x8_05)(r_lo, r_hi, unaff_x23);
                u6 = FUN_003510d0(auStack_8);
                r = FUN_00355e50(u6, local_b8 + i2);
                (*extraout_x8_06)(r_lo, r_hi, unaff_x22);
                FUN_00117cc4(auStack_a0, local_c0, 0x48);
                FUN_00352698(&stack0x00000020);
                u6 = FUN_0031945c();
                FUN_00350810(u6, auStack_a0);
                (*extraout_x8_07)();
                FUN_003510d0(&local_10);
                FUN_0007c1c4();
                (*extraout_x8_08)();
                FUN_00352698(&stack0x00000028);
                u6 = FUN_0031945c();
                FUN_00350b48(u6, auStack_a0);
                (*extraout_x8_09)();
                FUN_003510d0(&lStack_18);
                (*extraout_x8_10)(unaff_x25, unaff_x22);
                u8 = FUN_001a8564() ^ u8;
                break;
            }
        }
        long l1 = l3 + 1;
        if (SCARRY8(l3, 1)) {   /* WARNING: does not return */
            SoftwareBreakpoint(1, 0x1f51c8);
        }
        if (unaff_x22 <= l1) {
            FUN_00359760();
            u6 = extraout_x1_02;
            goto body_again;
        }
        l3 = l1;
        l4 = *(long *)(lStack_28 + l1 * 8);
    } while (true);
}

/* FUN_001f51d8 @ 0x001f51d8   (est. cl4_sched_hash_dispatch)
 * Ghidra: void FUN_001f51d8(void)
 * Dispatches the set-hash op: reads a key byte, XORs it with a reversed string
 * constant, runs the hash walk FUN_001f4dc4 and finalizes with FUN_001a8564.
 * Confidence: low
 * Notes: s_uespemos... string; FUN_0034d264 key mix; FUN_001f4dc4 walk. */
void cl4_sched_hash_dispatch(void)
{
    FUN_00355684();
    byte b = FUN_00348c48();
    FUN_0034d264(b, s_uespemosmodnarodarenegylsetybdet_004e7a30._16_8_,
                 b ^ (byte)s_uespemosmodnarodarenegylsetybdet_004e7a30._0_8_);
    FUN_001f4dc4();
    FUN_001a8564();
}

/* FUN_001f5268 @ 0x001f5268   (est. cl4_sched_hash_forward)
 * Ghidra: void FUN_001f5268(undefined8 param_1, long param_2, ulong param_3)
 * Forwards the set-hash op: resolves the method vector for param_3, builds the
 * descriptor (FUN_001a84f4) and runs the hash walk FUN_001f4dc4.
 * Confidence: low
 * Notes: FUN_001a84f4 build; FUN_001f4dc4 walk; FUN_001a8564 finalize. */
void cl4_sched_hash_forward(word_t a, long sched, ulong p3)
{
    word_t mv = *(word_t *)((p3 & 0xfffffffffffffffe) - 8);
    FUN_001a84f4(auStack_78);
    FUN_001f4dc4(auStack_78, *unaff_x20, *(word_t *)(sched + 0x10), *(word_t *)(sched + 0x18),
                 *(word_t *)(sched + 0x20), mv);
    FUN_001a8564();
}

/* FUN_001f52c8 @ 0x001f52c8   (est. cl4_sched_result_commit)
 * Ghidra: void FUN_001f52c8(void)
 * Commits a scheduler result: runs the op prep, builds the result tuple (two
 * fields + a table pointer &DAT_004f1840) and dispatches the completion hook.
 * Confidence: low
 * Notes: FUN_0031b68c value; &DAT_004f1840; FUN_00354ef8 completion. */
void cl4_sched_result_commit(void)
{
    FUN_00354a34();
    FUN_0034b13c();
    FUN_001f5324();
    FUN_000778b4();
    FUN_0035990c();
    word_t v = FUN_0031b68c();
    extraout_x8[3] = v;
    extraout_x8[4] = &DAT_004f1840;
    extraout_x8[0] = unaff_x24;
    extraout_x8[1] = unaff_x25;
    FUN_00354ef8(unaff_x30);
}

/* FUN_001f5324 @ 0x001f5324   (est. cl4_sched_result_prep)
 * Ghidra: void FUN_001f5324(void)
 * Prepares the scheduler result: runs FUN_001f5998 then FUN_00353a30.
 * Confidence: low
 * Notes: trivial two-call helper. */
void cl4_sched_result_prep(void)
{
    FUN_001f5998();
    FUN_00353a30();
}

/* FUN_001f538c @ 0x001f538c   (est. cl4_sched_copy_set)
 * Ghidra: undefined8 * FUN_001f538c(long param_1)
 * Copies a scheduler slot set into a fresh set object (FUN_001fa1a0 or the empty
 * singleton &DAT_00657798 if source empty), walking the source bitmap and
 * copying each slot payload via FUN_001f7488.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f7488 copy; SoftwareBreakpoint overflow. */
word_t *cl4_sched_copy_set(long src)
{
    word_t *dst;
    if (*(long *)(src + 0x10) == 0) {
        dst = &DAT_00657798;
    } else {
        word_t v = FUN_001fab14();
        dst = (word_t *)FUN_001fa1a0(v, 0x100000000, 0, 1);
    }
    FUN_001fca54(&local_88, src);
    FUN_0036b270(dst);
    thunk_FUN_0036b270(src);
    long l2 = lStack_70;
    ulong u7 = local_68;
    for (;;) {
        for (; u7 != 0; u7 = u7 - 1 & u7) {
            ulong u6 = bitrev_word(u7);
            u6 = LZCOUNT(u6 >> 0x20 | u6 << 0x20) | l2 << 6;
            FUN_0031996c(*(long *)(local_88 + 0x30) + u6 * 0x28, &local_d8);
            FUN_0031996c(*(long *)(local_88 + 0x38) + u6 * 0x28, &local_b0);
            FUN_001f7488(&local_100, &local_130, dst);
        }
        long l1 = l2 + 1;
        if (SCARRY8(l2, 1)) break;   /* WARNING: does not return */
        if ((long)(local_78 + 0x40U >> 6) <= l1) {
            FUN_0036b118(dst);
            FUN_0036b118(local_88);
            return dst;
        }
        l2 = l1;
        u7 = *(ulong *)(lStack_80 + l1 * 8);
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f54e4);
}

/* FUN_001f54e4 @ 0x001f54e4   (est. cl4_sched_copy_set_insert)
 * Ghidra: undefined8 * FUN_001f54e4(long param_1)
 * Copies a scheduler set into a pre-sized destination: walks the source bitmap
 * and inserts each slot's two-word key into the destination set (bitmap + value
 * + side arrays), growing checks against the destination capacity.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f98e8 key lookup; SoftwareBreakpoint overflow;
 *   noreturn panic on capacity/empty-slot violations. */
word_t *cl4_sched_copy_set_insert(long src)
{
    word_t *dst;
    if (*(long *)(src + 0x10) == 0) {
        dst = &DAT_00657798;
    } else {
        FUN_001fab14();
        FUN_0034c988();
        dst = (word_t *)FUN_001fa57c();
    }
    FUN_001fca54(&local_90, src);
    FUN_00357540(local_80);
    FUN_0036b270(dst);
    thunk_FUN_0036b270(src);
    ulong u10 = local_70;
    long l4 = lStack_78;
    for (;;) {
        while (u10 == 0) {
            long l1 = l4 + 1;
            if (SCARRY8(l4, 1)) {   /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f571c);
            }
            if (unaff_x22 <= l1) {
                FUN_0036b118(dst);
                FUN_0036b118(local_90);
                return dst;
            }
            l4 = l1;
            u10 = *(ulong *)(lStack_88 + l1 * 8);
        }
        FUN_003598ec();
        ulong u8 = extraout_x8 | l4 << 6;
        word_t *slot = (word_t *)(*(long *)(local_90 + 0x30) + u8 * 0x10);
        word_t u3 = *slot;
        long l1 = slot[1];
        FUN_0031996c(*(long *)(local_90 + 0x38) + u8 * 0x28, auStack_b8);
        FUN_0031996c(auStack_b8, auStack_170);
        FUN_003a25e0(l1, 2);
        FUN_00351f34(auStack_138, auStack_170);
        FUN_003598cc();
        FUN_00365b6c();
        FUN_00344e54(&local_c8, 0x6561b8, &DAT_004e8018);
        if (local_140 == 0) {
            FUN_0036b118(local_90);
            FUN_00344e54(&local_148, 0x6561c0, &DAT_004e8020);
            FUN_0036b118(dst);
            FUN_00348898(1);
            FUN_0034a2f8();
            /* WARNING: subroutine does not return */
            FUN_001afe4c();
        }
        u10 = u10 - 1 & u10;
        FUN_00310d98(auStack_138, auStack_108);
        FUN_00310d98(auStack_108, auStack_e8);
        FUN_000dbd0c();
        uint128_t r = FUN_001f98e8();
        u8 = r_lo;
        if ((r_hi & 1) == 0) {
            if ((ulong)dst[3] <= (ulong)dst[2]) {
                FUN_0035047c();
                FUN_003486b8(0x206);
                FUN_0034975c();
                /* WARNING: subroutine does not return */
                FUN_001afe4c();
            }
            ulong u9 = u8 >> 3 & 0x1ffffffffffffff8;
            *(ulong *)((long)dst + u9 + 0x40) |= 1L << (u8 & 0x3f);
            word_t *d = (word_t *)(dst[6] + u8 * 0x10);
            d[0] = u3;
            d[1] = l1;
            FUN_00310d98(auStack_e8, dst[7] + u8 * 0x20);
            if (SCARRY8(dst[2], 1)) break;  /* WARNING: does not return */
            dst[2] = dst[2] + 1;
        } else {
            word_t *d = (word_t *)(dst[6] + u8 * 0x10);
            word_t old = d[1];
            d[0] = u3;
            d[1] = l1;
            FUN_003a25d4(old);
            long l2 = dst[7] + u8 * 0x20;
            FUN_000026e8(l2);
            FUN_00310d98(auStack_e8, l2);
        }
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1f5740);
}

/* FUN_001f5998 @ 0x001f5998   (est. cl4_sched_accessor_5998) */
/* Ghidra: void FUN_001f5998(void) — alias of FUN_001f814c. Confidence: low */
void cl4_sched_accessor_5998(void) { FUN_001f814c(); }

/* FUN_001f59a0 @ 0x001f59a0   (est. cl4_sched_op_prep3)
 * Ghidra: void FUN_001f59a0(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Three-argument scheduler op prep: forwards (param_1, param_3), derives the
 * key and takes the caller context.
 * Confidence: low
 * Notes: FUN_0034ed08 forward; FUN_0031a29c key; thunk take. */
void cl4_sched_op_prep3(word_t a, word_t b, word_t c)
{
    FUN_0034ed08(a, c);
    FUN_00352578();
    FUN_0031a29c();
    FUN_00357f24();
    thunk_FUN_0036b270();
}

/* FUN_001f59d4 @ 0x001f59d4   (est. cl4_sched_desc_setup)
 * Ghidra: void FUN_001f59d4(undefined8 *param_1, undefined8 param_2, undefined8 param_3)
 * Sets up a scheduler descriptor: copies the source set (FUN_001f538c), fills
 * the result tuple (value + table &DAT_004f1840 + source) into param_1.
 * Confidence: low
 * Notes: FUN_001f538c copy; FUN_0035a880 value; &DAT_004f1840. */
void cl4_sched_desc_setup(word_t *out, word_t a, word_t src)
{
    thunk_FUN_0036b270(src);
    word_t v1 = FUN_001f538c(src);
    word_t v2 = FUN_0035a880();
    out[3] = v2;
    out[4] = &DAT_004f1840;
    out[0] = src;
    out[1] = v1;
}

/* FUN_001f5a30 @ 0x001f5a30   (est. cl4_sched_equals_op)
 * Ghidra: uint FUN_001f5a30(undefined8 param_1)
 * Set-equality op: builds the descriptor, resolves the pair and, if non-empty,
 * compares the two sets via FUN_001f3d8c; returns 2 on empty, else the
 * comparison result bit.
 * Confidence: low
 * Notes: FUN_00356fcc resolve; FUN_001f3d8c compare; FUN_003a25d4 releases. */
uint cl4_sched_equals_op(word_t a)
{
    FUN_00344d4c(a, auStack_58);
    FUN_003519c0();
    FUN_0035a880();
    int i1 = FUN_00356fcc(&local_68, auStack_58);
    if (i1 == 0) {
        return 2;
    }
    FUN_0009461c();
    uint u = FUN_001f3d8c();
    FUN_003a25d4(uStack_60);
    FUN_003a25d4(local_68);
    return u & 1;
}

/* FUN_001f5ab4 @ 0x001f5ab4   (est. cl4_sched_hash_op_entry)
 * Ghidra: void FUN_001f5ab4(void)
 * Entry of the set-hash op: mixes a key byte with a reversed string constant
 * then runs the hash walk FUN_001f4b3c and finalizes.
 * Confidence: low
 * Notes: s_uespemos... string; FUN_0034d264 key mix; FUN_001f4b3c walk. */
void cl4_sched_hash_op_entry(void)
{
    byte b = FUN_00348c48();
    FUN_0034d264(b, s_uespemosmodnarodarenegylsetybdet_004e7a30._16_8_,
                 b ^ (byte)s_uespemosmodnarodarenegylsetybdet_004e7a30._0_8_);
    FUN_001f4b3c();
    FUN_001a8564();
}

/* FUN_001f5b08 @ 0x001f5b08   (est. cl4_sched_hash_entry2)
 * Ghidra: void FUN_001f5b08(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Alternate entry of the set-hash op: preps (param_1, param_3), builds the frame
 * and runs the hash walk FUN_001f4b3c, finalizing with FUN_001a8564.
 * Confidence: low
 * Notes: FUN_00349d14 prep; FUN_001f4b3c walk. */
void cl4_sched_hash_entry2(word_t a, word_t b, word_t c)
{
    FUN_00349d14(a, c);
    FUN_00351624();
    FUN_00348f68();
    FUN_001f4b3c(auStack_68);
    FUN_001a8564();
}

/* FUN_001f5b4c @ 0x001f5b4c   (est. cl4_sched_op_prep6)
 * Ghidra: void FUN_001f5b4c(...6 args)
 * Six-argument scheduler op prep: forwards (param_1,param_3), derives the key,
 * takes the context and runs the teardown + drain helpers.
 * Confidence: low
 * Notes: FUN_0031a29c key; FUN_00365b6c/ FUN_0034dba8 drain. */
void cl4_sched_op_prep6(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f)
{
    FUN_003530e8(a, c);
    uint128_t r = FUN_00352ddc();
    FUN_0031a29c(r_lo, r_hi, d, f);
    FUN_00356b5c();
    thunk_FUN_0036b270();
    FUN_003515fc();
    word_t v = FUN_00365b6c();
    FUN_0034dba8(v, (uint)v ^ 1);
    FUN_000839d8();
}

/* FUN_001f5bbc @ 0x001f5bbc   (est. cl4_sched_op_dispatch_pair)
 * Ghidra: void FUN_001f5bbc(void)
 * Dispatches a scheduler pair op: acquires the context, takes the caller slot,
 * runs the state check (FUN_00365b6c) and on non-zero dispatches both entries
 * via the method at +0x20, otherwise drains the queue.
 * Confidence: low
 * Notes: DAT_00658c00; FUN_00365b6c check; method +0x20 twice. */
void cl4_sched_op_dispatch_pair(void)
{
    uint128_t r = FUN_0008e518();
    FUN_003548d0();
    FUN_00310d68();
    FUN_00348e00();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034924c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348f50();
    FUN_0035113c();
    FUN_00351f40();
    FUN_0031a29c();
    thunk_FUN_0036b270(r_hi);
    FUN_0035992c();
    FUN_003518a0();
    int c = FUN_00365b6c();
    if (c == 0) {
        FUN_0034bd00();
        (*extraout_x8_00)();
    } else {
        FUN_0034bc94();
        FUN_000839d8();
        code *m = *(code **)(extraout_x16 + 0x20);
        FUN_0034dfc4();
        (*m)();
        FUN_003508c0(r_lo);
        (*m)();
    }
    word_t v = FUN_00359920();
    FUN_0008e500(v, in_stack_00000048);
}

/* FUN_001f5d68 @ 0x001f5d68   (est. cl4_sched_dispatch_main_loop)
 * Ghidra: void FUN_001f5d68(void)
 * Main scheduler dispatch loop: acquires the shared context, validates the
 * preemption/refcount state of each queued entry (PAC-authenticated object
 * handling), dispatches each slot through the owner method vectors, hashes and
 * finalizes the descriptor, then requeues; loops until the queue is empty.
 * Confidence: low
 * Notes: very large (0x1f5d68-0x1f66b0); heavy PAC (0x48d8...) pointer-tag
 *   checks (bits 61/29), FUN_00349bfc refcount, FUN_003a25d4 free paths,
 *   __thread_bss.magic; decompiler removed some unreachable blocks. */
void cl4_sched_dispatch_main_loop(void)
{
    word_t u2 = FUN_0008e518();
    code *cb = in_x4;
    FUN_0007c028(u2, in_x3);
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003497b4();
    FUN_003509a4();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    FUN_003509a4();
    uint128_t r = FUN_0035361c();
    ulong u11 = r_hi;
    FUN_003722e4(r_lo, u11, cb);
    FUN_00352efc();
    FUN_00310d68();
    FUN_003490b8(auStack_30);
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_00354b44();
    FUN_00349618();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
    FUN_00348f50();
    FUN_0035125c(in_x5);
    FUN_00349444();
    FUN_003505c4();
    FUN_00377824();
    FUN_00348e00();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_003192a8(in_x5);
    word_t v3 = FUN_003505d0();
    ulong v4 = (*extraout_x8_03)(v3, in_x5);
    if ((v4 & 1) != 0) {
        FUN_003538b0(&DAT_005d3c8f);
        FUN_0008e500();
        FUN_001a89a8();
        return;
    }
    FUN_00359ab0();
    code *tag = (code *)((long)&__thread_bss.magic + 1);
    FUN_00350744();
    local_18._0_16_ = FUN_001a89a8();
    FUN_00350ed0(*(word_t *)(extraout_x16_01 + 0x10));
    (*extraout_x8_04)();
    FUN_003506b0();
    FUN_003504c4();
    (*extraout_x9)();
    FUN_003553b8();
    FUN_0034c6b4();
    word_t v5 = FUN_00377bec();
    code *next = (code *)FUN_000a68f4();
    FUN_00355430();
    FUN_00354ac8(extraout_x8_05 + 0x20);
    FUN_00352bbc();
    FUN_00354570(extraout_x8_06 + 0x20);
    word_t w1 = uRam00000000004baeb8;
    word_t w3 = _DAT_004baeb0;
    code *dpcb = unaff_x21;
    do {
        FUN_003526b8(auStack_38);
        (*next)(unaff_x21, v5);
        FUN_003510d0(auStack_58);
        r = FUN_00100efc();
        (*extraout_x8_07)(r_lo, r_hi, local_130);
        FUN_00351bac();
        FUN_0034d480();
        if ((bool)in_ZR) {
            FUN_00350bc0(auStack_78);
            FUN_000e72b0();
            (*extraout_x8_18)();
            FUN_00350744(&DAT_005d32c2);
            FUN_001a89a8();
            FUN_00352c80();
            v4 = FUN_00349bfc();
            if ((extraout_x8_19 == 0) && (((v4 & (extraout_x1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(extraout_x1);
            } else {
                if ((extraout_x1 >> 0x3d & 1) == 0) {
                    FUN_0034a798();
                }
                FUN_0034c0a4();
                FUN_002a4c98();
                FUN_003a25d4(tag);
            }
            r = FUN_00084180();
            FUN_0008e500(r_lo, r_hi, u2);
            return;
        }
        v4 = (ulong)*(int *)(extraout_x1 + 0x30);
        FUN_00355430();
        code *m1 = (code *)*extraout_x8_08;
        (*m1)(local_f0, local_140, u11);
        FUN_00352bbc();
        (*(code *)*extraout_x8_09)(local_e8, local_140 + v4, in_x4);
        if ((int)tag == 0) {
            FUN_003536bc();
            FUN_00353918();
            uVar7 = FUN_00349bfc();
            if ((extraout_x8_10 == 0) && (((uVar7 & (v4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(v4);
                local_18._8_8_ = local_140;
                local_18._0_8_ = tag;
            } else {
                dpcb = (code *)((ulong)local_140 >> 0x38 & 0xf);
                if ((v4 >> 0x3d & 1) == 0) {
                    in_ZR = ((ulong)local_140 & 0x2000000000000000) == 0;
                    if (!(bool)in_ZR) {
                        tag = dpcb;
                    }
                } else if (((ulong)local_140 >> 0x3d & 1) != 0) {
                    FUN_00350624();
                    FUN_0034a148();
                    tag = dpcb;
                    if (!(bool)in_ZR) {
                        FUN_003517c0();
                        FUN_003a25d4(v4);
                        FUN_003a25d4(local_140);
                        local_18._0_8_ = unaff_x21;
                        local_18._8_8_ = unaff_x24;
                        goto build;
                    }
                }
                FUN_003504ac();
                FUN_00356cd4();
                FUN_003a25d4(local_140);
                dpcb = tag;
            }
        }
build:
        v4 = extraout_x16_00 & 0xffffffffffff | 0x48d8000000000000;
        uVar8 = FUN_0008e0d4();
        unaff_x24 = (code *)FUN_0036a9a0(uVar8, auStack_58);
        *(word_t *)(unaff_x24 + 0x18) = w1;
        *(word_t *)(unaff_x24 + 0x10) = w3;
        *(ulong *)(unaff_x24 + 0x38) = u11;
        uVar8 = FUN_00319a4c(unaff_x24 + 0x20);
        (*m1)(uVar8, local_f0, u11);
        FUN_00359a54();
        FUN_003509f8(v4);
        FUN_001a89a8();
        FUN_00351f28();
        FUN_0034f030();
        FUN_003509f8(v4);
        r = FUN_001a89a8();
        code *pc10 = r_hi;
        tag = r_lo;
        FUN_00319808(unaff_x24 + 0x20, auStack_78);
        FUN_00310d98(auStack_78, auStack_98);
        v4 = FUN_00349bfc();
        if ((extraout_x8_11 == 0) && (((v4 & (u11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(u11);
        } else {
            dpcb = (code *)((ulong)pc10 >> 0x38 & 0xf);
            if ((u11 >> 0x3d & 1) == 0) {
                in_ZR = ((ulong)pc10 & 0x2000000000000000) == 0;
                code *pc9 = (code *)((ulong)tag & 0xffffffffffff);
                if (!(bool)in_ZR) {
                    pc9 = dpcb;
                }
            } else if (((ulong)pc10 >> 0x3d & 1) == 0) {
                code *pc9 = (code *)((ulong)tag & 0xffffffffffff);
            } else {
                FUN_00350624();
                FUN_0034b7c8();
                if (!(bool)in_ZR) {
                    FUN_00358d70();
                    FUN_003a25d4(u11);
                    FUN_003a25d4(pc10);
                    local_18._0_8_ = in_x4;
                    local_18._8_8_ = m1;
                    FUN_00357250();
                    r_hi = local_18._8_8_;
                    r_lo = local_18._0_8_;
                    goto commit;
                }
                FUN_00357250();
                code *pc9 = dpcb;
            }
            thunk_FUN_0036b270(pc10);
            FUN_00351324();
            FUN_00356cd4();
            FUN_003a2610(pc10, 2);
            r_hi = local_18._8_8_;
            r_lo = local_18._0_8_;
            dpcb = pc9;
        }
commit:
        local_18._0_16_ = r;
        FUN_0034895c();
        FUN_0034d274(auStack_98, local_18);
        FUN_00353d64();
        FUN_002060d4();
        FUN_000026e8(auStack_98);
        FUN_0036b588(unaff_x24);
        FUN_00002688();
        FUN_00002834();
        FUN_0036b6ac();
        FUN_003a25d4(extraout_x1_00);
        v4 = FUN_00349bfc();
        code *pc9 = unaff_x24;
        if ((extraout_x8_12 == 0) &&
            (((v4 & ((ulong)unaff_x24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(unaff_x24);
            local_18._8_8_ = local_140;
            local_18._0_8_ = unaff_x21;
        } else {
            tag = (code *)((ulong)local_140 >> 0x38 & 0xf);
            if (((ulong)unaff_x24 >> 0x3d & 1) == 0) {
                in_ZR = ((ulong)local_140 & 0x2000000000000000) == 0;
                code *pc13 = (code *)((ulong)unaff_x21 & 0xffffffffffff);
                if (!(bool)in_ZR) {
                    pc13 = tag;
                }
            } else if (((ulong)local_140 >> 0x3d & 1) == 0) {
                code *pc13 = (code *)((ulong)unaff_x21 & 0xffffffffffff);
            } else {
                FUN_003497c8(v4, unaff_x24);
                code *pc13 = tag;
                if (!(bool)in_ZR) {
                    FUN_00356508();
                    FUN_003a25d4(local_140);
                    local_18._0_8_ = dpcb;
                    local_18._8_8_ = unaff_x24;
                    goto free2;
                }
            }
            thunk_FUN_0036b270(local_140);
            FUN_0034c5bc();
            FUN_002a4c98();
            FUN_003593a8();
            tag = pc13;
            pc9 = (code *)local_18;
        }
free2:
        FUN_00354ae8();
        FUN_00353918();
        v4 = FUN_00349bfc();
        if ((extraout_x8_13 == 0) && (((v4 & ((ulong)pc9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            uVar8 = FUN_003a25d4(pc9);
            local_18._8_8_ = local_140;
            local_18._0_8_ = tag;
        } else {
            dpcb = (code *)((ulong)local_140 >> 0x38 & 0xf);
            if (((ulong)pc9 >> 0x3d & 1) == 0) {
                in_ZR = ((ulong)local_140 & 0x2000000000000000) == 0;
                tag = (code *)((ulong)tag & 0xffffffffffff);
                if (!(bool)in_ZR) {
                    tag = dpcb;
                }
            } else if (((ulong)local_140 >> 0x3d & 1) == 0) {
                tag = (code *)((ulong)tag & 0xffffffffffff);
            } else {
                FUN_00350624();
                FUN_0034a148();
                tag = dpcb;
                if (!(bool)in_ZR) {
                    FUN_003517c0();
                    FUN_003a25d4(pc9);
                    uVar8 = FUN_003a25d4(local_140);
                    local_18._0_8_ = unaff_x21;
                    local_18._8_8_ = unaff_x24;
                    goto build2;
                }
            }
            pc9 = (code *)local_18;
            FUN_003504ac();
            FUN_00356cd4();
            uVar8 = FUN_003a25d4(local_140);
            dpcb = tag;
        }
build2:
        code *pc13 = (code *)(extraout_x16 & 0xffffffffffff | 0x48d8000000000000);
        FUN_00358ac8(uVar8, auStack_d8);
        tag = (code *)FUN_0036a9a0();
        *(word_t *)(tag + 0x18) = w1;
        *(word_t *)(tag + 0x10) = w3;
        *(code **)(tag + 0x38) = in_x4;
        uVar8 = FUN_00319a4c(tag + 0x20);
        FUN_003570f0(uVar8, local_e8, in_x4);
        (*extraout_x8_14)();
        FUN_00359a54();
        FUN_003509f8(pc13);
        FUN_001a89a8();
        FUN_00354858();
        FUN_0034f030();
        FUN_003531fc();
        FUN_003509f8();
        FUN_001a89a8();
        FUN_0035785c();
        FUN_00319808(tag + 0x20, auStack_78);
        FUN_00310d98(auStack_78, auStack_98);
        v4 = FUN_00349bfc();
        if ((extraout_x8_15 == 0) && (((v4 & ((ulong)pc9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(pc9);
            local_18._0_8_ = pc13;
            local_18._8_8_ = extraout_x1_00;
        } else {
            dpcb = (code *)((ulong)extraout_x1_00 >> 0x38 & 0xf);
            if (((ulong)pc9 >> 0x3d & 1) == 0) {
                FUN_00357374();
                code *pc9b = extraout_x8_16;
                if (!(bool)in_ZR) {
                    pc9b = dpcb;
                }
            } else {
                code *pc9b = (code *)(extraout_x16 & 0xffffffffffff);
                if (((ulong)extraout_x1_00 >> 0x3d & 1) != 0) {
                    FUN_00350624();
                    code *pc9b = (code *)FUN_0034c51c();
                    if (!(bool)in_ZR) {
                        FUN_003542c4();
                        FUN_003a25d4();
                        FUN_003a25d4(extraout_x1_00);
                        local_18._0_8_ = pc9b;
                        local_18._8_8_ = pc10;
                        FUN_00357250();
                        in_x4 = pc9b;
                        goto commit2;
                    }
                    FUN_00357250();
                    code *pc9b = dpcb;
                }
            }
            thunk_FUN_0036b270(extraout_x1_00);
            FUN_003508fc();
            FUN_00356cd4();
            FUN_0035900c();
            dpcb = pc9b;
        }
commit2:
        FUN_0034895c();
        FUN_0034d274(auStack_98, local_18);
        FUN_00353d64();
        FUN_002060d4();
        FUN_000026e8(auStack_98);
        FUN_0036b588(tag);
        FUN_00002688();
        FUN_00002834();
        FUN_0036b6ac();
        FUN_003a25d4(unaff_x24);
        v4 = FUN_00349bfc();
        if ((extraout_x8_17 == 0) &&
            (((v4 & ((ulong)tag ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(tag);
            local_18._0_8_ = local_140;
            local_18._8_8_ = m1;
        } else {
            if (((ulong)tag >> 0x3d & 1) == 0) {
                in_ZR = ((ulong)m1 & 0x2000000000000000) == 0;
            } else if (((ulong)m1 >> 0x3d & 1) != 0) {
                FUN_000dbe70();
                code *pc10b = (code *)FUN_0034b7c8();
                if (!(bool)in_ZR) {
                    FUN_00354954();
                    FUN_003a25d4();
                    FUN_003a25d4(m1);
                    dpcb = pc10b;
                    local_18._0_8_ = pc10b;
                    local_18._8_8_ = tag;
                    goto free3;
                }
            }
            thunk_FUN_0036b270(m1);
            FUN_0009e234();
            FUN_00352cc8();
            FUN_002a4c98();
            FUN_00357a00();
            FUN_003a2610();
        }
free3:
        tag = (code *)0x0;
    } while (true);
}

/* FUN_001f66c8 @ 0x001f66c8   (est. thunk_FUN_001f66cc) */
/* Ghidra: void thunk_FUN_001f66cc(void) — alias of FUN_001f66cc. Confidence: low */
void thunk_FUN_001f66cc(void) { FUN_001f66cc(); }

/* FUN_001f66cc @ 0x001f66cc   (est. cl4_sched_dispatch_enter)
 * Ghidra: void FUN_001f66cc(void)
 * Enters the scheduler dispatch loop: derives the key, runs the dispatch hook
 * (FUN_00352920 with tag 0x66ba38) and jumps into the main loop FUN_001f5d68.
 * Confidence: low
 * Notes: FUN_0031a29c key; FUN_00352920 tag 0x66ba38; FUN_001f5d68 loop. */
void cl4_sched_dispatch_enter(void)
{
    FUN_00350b54();
    FUN_00352ddc();
    uint128_t r = FUN_0031a29c();
    FUN_00352920(r_lo, r_hi, r_lo, in_x3, in_x4, 0x66ba38);
    FUN_001f5d68();
}

/* FUN_001f673c @ 0x001f673c   (est. cl4_sched_teardown)
 * Ghidra: void FUN_001f673c(void)
 * Scheduler teardown: runs FUN_003517b4 then the shared destroy thunk.
 * Confidence: low
 * Notes: FUN_003517b4; thunk_FUN_002298d4. */
void cl4_sched_teardown(void)
{
    FUN_003517b4();
    thunk_FUN_002298d4();
}

/* FUN_001f67e8 @ 0x001f67e8   (est. cl4_sched_init_a) */
/* Ghidra: void FUN_001f67e8(void) — alias of FUN_001f67ec. Confidence: low */
void cl4_sched_init_a(void) { FUN_001f67ec(); }

/* FUN_001f67ec @ 0x001f67ec   (est. cl4_sched_init)
 * Ghidra: void FUN_001f67ec(void)
 * Initializes the scheduler: derives the context (FUN_0035a7e8), resolves it via
 * FUN_003625e4 and registers with FUN_00208418.
 * Confidence: low
 * Notes: FUN_0035a7e8/FUN_003625e4 context; FUN_00208418 register. */
void cl4_sched_init(void)
{
    uint128_t r = FUN_0035a7e8();
    word_t v = FUN_003625e4(r_lo, r_hi, 0);
    FUN_00208418(v, 1);
}

/* FUN_001f6874 @ 0x001f6874   (est. cl4_sched_trace_op)
 * Ghidra: void FUN_001f6874(undefined1 param_1, undefined8 param_2, undefined8 param_3)
 * Scheduler trace op: packs three fields and forwards through FUN_00369efc with
 * two trace tags.
 * Confidence: low
 * Notes: tags 0x676690/0x66efa0; FUN_00369efc trace. */
void cl4_sched_trace_op(uint8_t a, word_t b, word_t c)
{
    uint8_t local_28[8]; local_28[0] = a;
    word_t local_20 = b;
    word_t uStack_18 = c;
    FUN_00369efc(local_28, 0x676690, 0x66efa0);
}

/* FUN_001f68bc @ 0x001f68bc   (est. cl4_sched_trace_flush)
 * Ghidra: void FUN_001f68bc(void)
 * Flushes the scheduler trace: runs FUN_00358fa8 then the trace hook.
 * Confidence: low
 * Notes: FUN_00358fa8; FUN_00369efc. */
void cl4_sched_trace_flush(void)
{
    FUN_00358fa8();
    FUN_00369efc();
}

/* FUN_001f68f8 @ 0x001f68f8   (est. cl4_sched_fail)
 * Ghidra: void FUN_001f68f8(void)
 * Scheduler failure/panic path: signals the failure (FUN_003488bc) and panics
 * via the no-return helper.
 * Confidence: low
 * Notes: FUN_003488bc(1); noreturn FUN_001afe4c. */
void cl4_sched_fail(void)
{
    FUN_003488bc(1);
    FUN_0034a3ec();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001f6960 @ 0x001f6960   (est. cl4_sched_fail_b)
 * Ghidra: void FUN_001f6960(void)
 * Scheduler failure/panic path (duplicate of FUN_001f68f8).
 * Confidence: low
 * Notes: FUN_003488bc(1); noreturn FUN_001afe4c. */
void cl4_sched_fail_b(void)
{
    FUN_003488bc(1);
    FUN_0034a3ec();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001f69b4 @ 0x001f69b4   (est. cl4_sched_destroy)
 * Ghidra: void FUN_001f69b4(void)
 * Scheduler destroy: runs FUN_003528cc then the shared destroy thunk.
 * Confidence: low
 * Notes: FUN_003528cc; thunk_FUN_002298d4. */
void cl4_sched_destroy(void)
{
    FUN_003528cc();
    thunk_FUN_002298d4();
}

/* FUN_001f69e0 @ 0x001f69e0   (est. cl4_sched_destroy_forward)
 * Ghidra: void FUN_001f69e0(void)
 * Forwards the scheduler destroy op: builds the descriptor (FUN_001a84f4) and
 * runs FUN_001f69b4, finalizing with FUN_001a8564.
 * Confidence: low
 * Notes: FUN_001a84f4 build; FUN_001f69b4 destroy. */
void cl4_sched_destroy_forward(void)
{
    FUN_001a84f4(auStack_68);
    FUN_001f69b4(auStack_68, *unaff_x20);
    FUN_001a8564();
}

/* FUN_001f6a20 @ 0x001f6a20   (est. cl4_sched_op_forward2)
 * Ghidra: void FUN_001f6a20(undefined8 param_1, long param_2)
 * Forwards a scheduler op: derives the key from three fields of param_2 and
 * invokes the method at +0x10 with param_1.
 * Confidence: low
 * Notes: FUN_0031b6a4 key; method +0x10; jumptable warning. */
void cl4_sched_op_forward2(word_t a, long src)
{
    FUN_0031b6a4(0, *(word_t *)(src + 0x10), *(word_t *)(src + 0x18), *(word_t *)(src + 0x20));
    FUN_00350404();
    /* WARNING: could not recover jumptable at 0x1f6a74; indirect jump as call */
    (**(code **)(extraout_x16 + 0x10))(a);
}

/* FUN_001f6a78 @ 0x001f6a78   (est. cl4_sched_ctx_commit)
 * Ghidra: void FUN_001f6a78(void)
 * Commits the scheduler context: derives the key, dispatches through the method
 * at +0x20 and stores the result field into the caller slot at +0x20.
 * Confidence: low
 * Notes: FUN_0031b6a4 key; method +0x20; store at +0x20. */
void cl4_sched_ctx_commit(void)
{
    FUN_00358c50();
    FUN_003524bc();
    FUN_0031b6a4();
    FUN_00349530();
    (**(code **)(extraout_x16 + 0x20))(auStack_50);
    FUN_0035a960();
    FUN_00359804();
    *(word_t *)(unaff_x20 + 0x20) = unaff_x19;
}

/* FUN_001f6ad8 @ 0x001f6ad8   (est. cl4_sched_ctx_commit_b)
 * Ghidra: void FUN_001f6ad8(void)
 * Commits the scheduler context (variant of FUN_001f6a78 using FUN_0034ed08
 * prep and FUN_00359804 result).
 * Confidence: low
 * Notes: mirror of FUN_001f6a78. */
void cl4_sched_ctx_commit_b(void)
{
    FUN_0034ed08();
    FUN_0031b6a4();
    FUN_00349530();
    (**(code **)(extraout_x16 + 0x20))(auStack_50);
    FUN_00359804(local_30);
    *(word_t *)(unaff_x20 + 0x20) = extraout_x8;
}

/* FUN_001f6b30 @ 0x001f6b30   (est. cl4_sched_ctx_commit_c)
 * Ghidra: void FUN_001f6b30(void)
 * Commits the scheduler context (third variant): prep + FUN_001f6ad8 then store
 * the result into the caller slot at +0x20.
 * Confidence: low
 * Notes: FUN_001f6ad8 core; store at +0x20. */
void cl4_sched_ctx_commit_c(void)
{
    FUN_00356bf8();
    FUN_001f6ad8();
    FUN_003551f8();
    *(word_t *)(unaff_x19 + 0x20) = local_58;
}

/* FUN_001f6b68 @ 0x001f6b68   (est. cl4_sched_alloc_state)
 * Ghidra: void FUN_001f6b68(void)
 * Allocates a scheduler state object (zone 0xcebb), takes a reference and runs
 * the init hook.
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0xcebb; FUN_0036b270 take; FUN_003507e0 init. */
void cl4_sched_alloc_state(void)
{
    FUN_0036a908(0x38, 0xcebb);
    FUN_003548f4();
    FUN_0036b270();
    FUN_003507e0();
}

/* FUN_001f6bc4 @ 0x001f6bc4   (est. cl4_sched_iter_dispatch2)
 * Ghidra: void FUN_001f6bc4(long param_1)
 * Dispatches both value and side slot of the next set entry from the iterator:
 * scans the bitmap, invokes the two owner methods (+0x10 each) over the value
 * and side arrays, and drains the queue.
 * Confidence: low
 * Notes: LZCOUNT bit scan; two +0x10 dispatches; SoftwareBreakpoint overflow. */
void cl4_sched_iter_dispatch2(word_t a)
{
    long l3, l4;
    ulong u6;
    if (unaff_x20[4] == 0) {
        l3 = FUN_00357ee4();
        lVar3 = extraout_x8_00;
        l4 = extraout_x10;
        do {
            if (SCARRY8(lVar3, 1)) {  /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f6cd8);
            }
            if (l4 <= lVar3 + 1) {
                FUN_00352048(l3, *(word_t *)(l3 + 0x10), *(word_t *)(l3 + 0x18));
                FUN_003722e4();
                FUN_0034b690();
                goto drain;
            }
            l3 = FUN_00353664();
            lVar3 = extraout_x8_01;
            l4 = extraout_x10_00;
        } while (extraout_x11 == 0);
        lVar3 = FUN_0035364c();
        u6 = extraout_x8_02 | extraout_x9_00 << 6;
    } else {
        lVar3 = FUN_0035229c();
        u6 = extraout_x9 | extraout_x8 << 6;
    }
    long l7 = *unaff_x20;
    word_t u1 = *(word_t *)(lVar3 + 0x10);
    long l3b = *(long *)(lVar3 + 0x18);
    FUN_003511b4();
    (**(code **)(extraout_x16 + 0x10))
        (a, *(long *)(l7 + 0x30) + *(long *)(extraout_x16 + 0x48) * u6, u1);
    FUN_0034d904();
    long l4b = FUN_003722e4();
    long l5 = *(long *)(l3b + -8);
    (**(code **)(l5 + 0x10))
        (a + *(int *)(l4b + 0x30), *(long *)(l7 + 0x38) + *(long *)(l5 + 0x48) * u6, l3b);
    FUN_0034b744();
drain:
    FUN_000839d8();
}

/* FUN_001f6cd8 @ 0x001f6cd8   (est. cl4_sched_find_set_bit2)
 * Ghidra: void FUN_001f6cd8(long param_1, long param_2)
 * Bitmap slot find/dispatch for the value+side pair (mirror of FUN_001f6bc4):
 * scans for the next set bit and dispatches both arrays via +0x10.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f7d28 base; two +0x10 dispatches. */
void cl4_sched_find_set_bit2(word_t a, long sched)
{
    word_t w1 = unaff_x20[1], w0 = unaff_x20[0];
    long l1 = unaff_x20[2], l11 = unaff_x20[3];
    ulong u7 = unaff_x20[4];
    if (u7 == 0) {
        long l10 = l11;
        do {
            l11 = l10 + 1;
            if (SCARRY8(l10, 1)) {   /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f6eb0);
            }
            if ((long)(l1 + 0x40U >> 6) <= l11) {
                word_t u8 = FUN_003722e4(0, *(word_t *)(sched + 0x10), *(word_t *)(sched + 0x18),
                                         s_key_value_005cea2a, 0);
                FUN_000839d8(a, 1, 1, u8);
                u7 = 0;
                goto store;
            }
            u7 = *(ulong *)(unaff_x20[1] + l11 * 8);
            l10 = l10 + 1;
        } while (u7 == 0);
    }
    ulong u9 = bitrev_word(u7);
    u7 = u7 - 1 & u7;
    u9 = LZCOUNT(u9 >> 0x20 | u9 << 0x20) | l11 << 6;
    long l10 = *(long *)(sched + 0x10);
    long l2 = *(long *)(sched + 0x18);
    word_t u8 = *(word_t *)(sched + 0x20);
    long l5 = FUN_001f7d28(w0);
    (**(code **)(*(long *)(l10 + -8) + 0x10))
        (a, l5 + *(long *)(*(long *)(l10 + -8) + 0x48) * u9, l10);
    FUN_0001a1c8(w0, l10, l2, u8);
    long l5b = FUN_003722e4(0, l10, l2, s_key_value_005cea2a, 0);
    int i3 = *(int *)(l5b + 0x30);
    long l6 = FUN_001f0bb4(w0);
    (**(code **)(*(long *)(l2 + -8) + 0x10))
        (a + i3, l6 + *(long *)(*(long *)(l2 + -8) + 0x48) * u9, l2);
    FUN_0001a1c8(w0, l10, l2, u8);
    FUN_000839d8(a, 0, 1, l5b);
    l10 = l11;
store:
    unaff_x20[1] = w1;
    unaff_x20[0] = w0;
    unaff_x20[2] = l1;
    unaff_x20[3] = l10;
    unaff_x20[4] = u7;
}

/* FUN_001f6eb0 @ 0x001f6eb0   (est. cl4_sched_iter_snapshot)
 * Ghidra: void FUN_001f6eb0(void)
 * Snapshots the current scheduler iterator state into a 5-word descriptor: reads
 * the caller's iterator, derives the key (FUN_0031b6a4) and dispatches through
 * the method at +0x10 into a snapshot buffer.
 * Confidence: low
 * Notes: FUN_0031b6a4 key; method +0x10; FUN_001f6fac tail. */
void cl4_sched_iter_snapshot(void)
{
    FUN_00353aa0();
    uStack_c8 = unaff_x20[1];
    local_d0 = *unaff_x20;
    uStack_b8 = unaff_x20[3];
    uStack_c0 = unaff_x20[2];
    local_b0 = unaff_x20[4];
    FUN_00350470();
    FUN_00002534();
    FUN_00353dd0();
    FUN_003513b4();
    FUN_00327e08();
    word_t v = FUN_0031b6a4(0, unaff_x20[2], unaff_x20[3], unaff_x20[4]);
    FUN_0035295c();
    FUN_00350b84(auStack_78);
    (*extraout_x9)();
    (**(code **)(extraout_x16 + 0x10))(auStack_a8, auStack_78, v);
    FUN_0034d5ec(auStack_a8, &local_d0);
    FUN_001f6fac();
    FUN_00358888();
}

/* FUN_001f6fac @ 0x001f6fac   (est. cl4_sched_result_build)
 * Ghidra: void FUN_001f6fac(...8 args)
 * Builds a scheduler result tuple: resolves the state (FUN_00365b6c), packs the
 * caller args + status into the result frame and returns.
 * Confidence: low
 * Notes: FUN_00365b6c check; FUN_003508d8/FUN_003588b8 status; DAT_00658c00. */
void cl4_sched_result_build(word_t a, word_t b, uint8_t c, word_t d, word_t e, word_t f, word_t g, word_t h)
{
    FUN_0008e518();
    FUN_00359b24();
    FUN_0007c028();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_00348f38();
    FUN_00353178();
    uint128_t r4 = FUN_002db6b8();
    FUN_00350914();
    FUN_00319350();
    uint128_t r5 = FUN_00350720();
    FUN_003193f4(r5_lo, r5_hi, h);
    FUN_00352b74();
    word_t v2 = FUN_0020c1bc();
    FUN_0034e464(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_01)();
    FUN_0034f9b4();
    FUN_003508d8(auStack_28);
    int i1 = FUN_00365b6c();
    uint8_t u3;
    if (i1 == 0) {
        u3 = 0;
    } else {
        FUN_003588b8(auStack_28);
        u3 = extraout_w8;
    }
    extraout_x8[0] = f;
    extraout_x8[1] = v2;
    *(uint8_t *)(extraout_x8 + 2) = c;
    *(uint8_t (*)[16])(extraout_x8 + 3) = r4;
    *(uint8_t *)(extraout_x8 + 5) = u3;
    FUN_0008e500(extraout_x9);
}

/* FUN_001f70c8 @ 0x001f70c8   (est. cl4_sched_iter_snapshot_fill)
 * Ghidra: void FUN_001f70c8(undefined8 *param_1)
 * Fills a caller buffer with the current iterator snapshot (via FUN_001f6eb0),
 * storing the 5-word iterator state into param_1.
 * Confidence: low
 * Notes: FUN_001f6eb0 snapshot; byte/word packing at +0x19/+0x21. */
void cl4_sched_iter_snapshot_fill(word_t *out)
{
    uStack_48 = unaff_x20[1];
    local_50 = *unaff_x20;
    uStack_38 = unaff_x20[3];
    uStack_40 = unaff_x20[2];
    local_30 = unaff_x20[4];
    FUN_001f6eb0(&local_80);
    out[1] = uStack_78;
    out[0] = local_80;
    out[3] = CONCAT71(local_67, uStack_68);
    out[2] = uStack_70;
    *(word_t *)((long)out + 0x21) = uStack_5f;
    *(ulong *)((long)out + 0x19) = CONCAT17(uStack_60, local_67);
}

/* FUN_001f711c @ 0x001f711c   (est. cl4_sched_cap_setup)
 * Ghidra: void FUN_001f711c(void)
 * Sets up a scheduler capability: derives the key, resolves the object, takes a
 * double reference and runs the cap-register helpers.
 * Confidence: low
 * Notes: FUN_0031a29c key; FUN_00354924 object; FUN_003a25e0 double-take. */
void cl4_sched_cap_setup(void)
{
    FUN_00352800();
    FUN_0031a29c(0);
    word_t v = FUN_00354924();
    FUN_003a25e0(v, 2);
    uint128_t r = FUN_00357f14();
    FUN_003515b4(r_lo, r_hi, 6);
    FUN_001a67bc();
    FUN_0035a1d4();
}

/* FUN_001f7194 @ 0x001f7194   (est. cl4_sched_cap_setup_fill)
 * Ghidra: void FUN_001f7194(undefined8 *param_1, long param_2)
 * Sets up a scheduler cap and fills a caller buffer with the result descriptor
 * (via FUN_001f711c).
 * Confidence: low
 * Notes: FUN_001f711c setup; byte/word packing at +0x19/+0x21. */
void cl4_sched_cap_setup_fill(word_t *out, long src)
{
    FUN_001f711c(&local_50, *unaff_x20, *(word_t *)(src + 0x10), *(word_t *)(src + 0x18),
                 *(word_t *)(src + 0x20));
    out[1] = uStack_48;
    out[0] = local_50;
    out[3] = CONCAT71(local_37, uStack_38);
    out[2] = uStack_40;
    *(word_t *)((long)out + 0x21) = uStack_2f;
    *(ulong *)((long)out + 0x19) = CONCAT17(uStack_30, local_37);
}

/* FUN_001f71e4 @ 0x001f71e4   (est. cl4_sched_run_entry)
 * Ghidra: void FUN_001f71e4(long param_1, long param_2)
 * Runs a scheduler entry: checks whether the queue at +0x10 is non-empty, and if
 * so dispatches the pair through FUN_001f1a20; then runs the drain tail.
 * Confidence: low
 * Notes: FUN_001fb1cc key; FUN_001f1a20 dispatch; FUN_00351548 tail. */
void cl4_sched_run_entry(word_t a, long sched)
{
    long ctx = *unaff_x20;
    long l5 = *(long *)(ctx + 0x10);
    FUN_00352048(sched, *(word_t *)(sched + 0x10), *(word_t *)(sched + 0x18));
    long l3 = FUN_003722e4();
    bool empty = (l5 == 0);
    if (!empty) {
        int i2 = *(int *)(l3 + 0x30);
        uint128_t r = FUN_001fb1cc(ctx);
        FUN_001f1a20(a, a + i2, r_lo, r_hi, sched);
    }
    FUN_00351548(a, empty);
    FUN_000839d8();
}

/* FUN_001f7274 @ 0x001f7274   (est. cl4_sched_op_prep4)
 * Ghidra: void FUN_001f7274(void)
 * Scheduler op prep: derives the key and runs the shared tail FUN_001f72a8.
 * Confidence: low
 * Notes: FUN_0031a2b4 key; FUN_001f72a8 tail. */
void cl4_sched_op_prep4(void)
{
    FUN_00358c50();
    FUN_003524bc();
    FUN_0031a2b4();
    FUN_00353a30();
    FUN_001f72a8();
}

/* FUN_001f72a8 @ 0x001f72a8   (est. cl4_sched_op_tail)
 * Ghidra: void FUN_001f72a8(void)
 * Shared scheduler op tail: takes the CNode, derives the offset, runs the insert
 * and restore helpers, then the completion.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fb194 insert; FUN_003544c8 completion. */
void cl4_sched_op_tail(void)
{
    FUN_00354744();
    FUN_0035098c();
    FUN_003a261c(*unaff_x20);
    FUN_003589fc();
    FUN_0034f2e4();
    FUN_0034d3e4();
    FUN_0031b560();
    FUN_000776c0();
    FUN_00258c60();
    FUN_003552a0();
    FUN_0034f3b4();
    FUN_001fb194();
    FUN_003544c8(in_stack_00000008, unaff_x30);
    FUN_0036b118();
}

/* FUN_001f7324 @ 0x001f7324   (est. cl4_sched_hook_7324) */
/* Ghidra: void FUN_001f7324(void) — alias of FUN_001ee140. Confidence: low */
void cl4_sched_hook_7324(void) { FUN_001ee140(); }

/* FUN_001f734c @ 0x001f734c   (est. cl4_sched_guard_insert)
 * Ghidra: void FUN_001f734c(undefined8 param_1, undefined8 param_2, long param_3)
 * Guards a scheduler insert: if the queue count (+0x10) is below the capacity
 * (unaff_x20[1]) it runs the insert dispatch path; otherwise panics.
 * Confidence: low
 * Notes: capacity check; noreturn panic on overflow. */
void cl4_sched_guard_insert(word_t a, word_t b, long sched)
{
    word_t u1 = FUN_0008e518();
    FUN_003494e8(u1, u1);
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003490ec();
    word_t v1 = *(word_t *)(sched + 0x10);
    FUN_0034b7e4();
    (*DAT_00658c00)(extraout_x16_00);
    FUN_0034d3b4();
    if (*(long *)(*unaff_x20 + 0x10) < unaff_x20[1]) {
        uint128_t r = FUN_00351984();
        (*extraout_x9)(r_lo, r_hi, v1);
        FUN_0034edc8(*(word_t *)(extraout_x16 + 0x10));
        (*extraout_x8_00)();
        FUN_0034ff88();
        FUN_003558fc();
        FUN_001f7be0();
        FUN_0008e500(unaff_x30);
        return;
    }
    FUN_00350410();
    FUN_003488bc();
    FUN_0034bbdc();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001f7488 @ 0x001f7488   (est. cl4_sched_set_insert5)
 * Ghidra: void FUN_001f7488(undefined8 *param_1, undefined8 *param_2, long param_3)
 * Inserts a 5-word key+value pair into a scheduler set: hashes the key, finds
 * the free slot via FUN_001f9a68, copies both 5-word payloads into the value and
 * side arrays and bumps the count.
 * Confidence: low
 * Notes: FUN_001f9a68 slot; two 0x28-byte copies; noreturn FUN_002591b4 on
 *   overflow (tag 0x673a80). */
void cl4_sched_set_insert5(word_t *key, word_t *side, long set)
{
    word_t u6 = *(word_t *)(set + 0x28);
    word_t u4 = key[3], u7 = key[4];
    FUN_0006a4c0(key, u4);
    code *c = (code *)FUN_0008e5d8(u7);
    (*c)(auStack_78, u4, u7);
    FUN_0006a4c0(auStack_78, local_60);
    code *c2 = (code *)FUN_0031993c(uStack_58);
    u4 = (*c2)(u6, local_60, uStack_58);
    FUN_000026e8(auStack_78);
    uint128_t r = FUN_001f9a68(key, u4);
    ulong u5 = r_lo;
    if ((r_hi & 1) == 0) {
        long b = set + (u5 >> 6) * 8;
        *(ulong *)(b + 0x40) |= 1L << (u5 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u5 * 0x28);
        v[4] = key[4];
        v[1] = key[1];
        v[0] = key[0];
        v[3] = key[3];
        v[2] = key[2];
        word_t *s = (word_t *)(*(long *)(set + 0x38) + u5 * 0x28);
        s[1] = side[1];
        s[0] = side[0];
        s[3] = side[3];
        s[2] = side[2];
        s[4] = side[4];
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x673a80);
}

/* FUN_001f75c0 @ 0x001f75c0   (est. cl4_sched_set_insert_pair)
 * Ghidra: void FUN_001f75c0(undefined8 *param_1, undefined8 param_2, undefined8 param_3,
 *   long param_4)
 * Inserts a 5-word key + 2-word side into a scheduler set (0x10-byte side slot).
 * Confidence: low
 * Notes: FUN_001f9a68 slot; 0x28-byte value + 0x10-byte side; noreturn overflow. */
void cl4_sched_set_insert_pair(word_t *key, word_t a, word_t b, long set)
{
    word_t u6 = *(word_t *)(set + 0x28);
    word_t u3 = key[3], u7 = key[4];
    FUN_0006a4c0(key, u3);
    code *c = (code *)FUN_0008e5d8(u7);
    (*c)(auStack_78, u3, u7);
    FUN_0006a4c0(auStack_78, local_60);
    code *c2 = (code *)FUN_0031993c(uStack_58);
    u3 = (*c2)(u6, local_60, uStack_58);
    FUN_000026e8(auStack_78);
    uint128_t r = FUN_001f9a68(key, u3);
    ulong u4 = r_lo;
    if ((r_hi & 1) == 0) {
        long b2 = set + (u4 >> 6) * 8;
        *(ulong *)(b2 + 0x40) |= 1L << (u4 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u4 * 0x28);
        v[4] = key[4];
        v[1] = key[1];
        v[0] = key[0];
        v[3] = key[3];
        v[2] = key[2];
        word_t *s = (word_t *)(*(long *)(set + 0x38) + u4 * 0x10);
        s[0] = a;
        s[1] = b;
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x673a80);
}

/* FUN_001f76f0 @ 0x001f76f0   (est. cl4_sched_set_insert_side20)
 * Ghidra: void FUN_001f76f0(undefined8 *param_1, undefined8 param_2, long param_3)
 * Inserts a 5-word key with a 0x20-byte side (via FUN_00310d98) into a set.
 * Confidence: low
 * Notes: FUN_001f9a68 slot; FUN_00310d98 side; noreturn overflow. */
void cl4_sched_set_insert_side20(word_t *key, word_t side, long set)
{
    word_t u6 = *(word_t *)(set + 0x28);
    word_t u3 = key[3], u7 = key[4];
    FUN_0006a4c0(key, u3);
    code *c = (code *)FUN_0008e5d8(u7);
    (*c)(auStack_78, u3, u7);
    FUN_0006a4c0(auStack_78, local_60);
    code *c2 = (code *)FUN_0031993c(uStack_58);
    u3 = (*c2)(u6, local_60, uStack_58);
    FUN_000026e8(auStack_78);
    uint128_t r = FUN_001f9a68(key, u3);
    ulong u4 = r_lo;
    if ((r_hi & 1) == 0) {
        long b = set + (u4 >> 6) * 8;
        *(ulong *)(b + 0x40) |= 1L << (u4 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u4 * 0x28);
        v[4] = key[4];
        v[1] = key[1];
        v[0] = key[0];
        v[3] = key[3];
        v[2] = key[2];
        FUN_00310d98(side, *(long *)(set + 0x38) + u4 * 0x20);
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x673a80);
}

/* FUN_001f7820 @ 0x001f7820   (est. cl4_sched_set_insert2_obfuscated)
 * Ghidra: void FUN_001f7820(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *   long param_4)
 * Inserts a 2-word key into a set using an obfuscated (XOR-keyed string)
 * hashing path: builds a descriptor with a masked type string, hashes via
 * FUN_0006af08 and inserts the key + side.
 * Confidence: low
 * Notes: obfuscated string constants ("aresetybdet", "random..." XOR with
 *   _DAT_006adf10/_DAT_006adf18); FUN_0006af08 hash; noreturn overflow. */
void cl4_sched_set_insert2_obfuscated(word_t a, word_t b, word_t side, long set)
{
    uStack_80 = _DAT_006adf10 ^ *(ulong *)(set + 0x28);
    local_68 = _DAT_006adf18 ^ 0x7465646279746573;
    uStack_58 = 0;
    local_60 = 0;
    uStack_48 = 0;
    uStack_50 = 0;
    uStack_70 = uStack_80 ^ 0x6c7967656e657261;
    local_78 = _DAT_006adf18 ^ 0x646f72616e646f6d;
    uStack_80 = uStack_80 ^ 0x736f6d6570736575;
    local_88 = 0;
    FUN_001b9084(&local_88, a, b);
    word_t h = FUN_001a8564();
    uint128_t r = FUN_0006af08(a, b, h);
    ulong u4 = r_lo;
    if ((r_hi & 1) == 0) {
        long b2 = set + (u4 >> 6) * 8;
        *(ulong *)(b2 + 0x40) |= 1L << (u4 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u4 * 0x10);
        v[0] = a;
        v[1] = b;
        FUN_00310d98(side, *(long *)(set + 0x38) + u4 * 0x20);
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x6753a0);
}

/* FUN_001f795c @ 0x001f795c   (est. cl4_sched_set_insert2_side5)
 * Ghidra: void FUN_001f795c(undefined8 param_1, undefined8 param_2, undefined8 *param_3,
 *   long param_4)
 * Inserts a 2-word key + 5-word side into a set via the obfuscated hash path.
 * Confidence: low
 * Notes: mirror of FUN_001f7820 with a 0x28-byte side slot. */
void cl4_sched_set_insert2_side5(word_t a, word_t b, word_t *side, long set)
{
    uStack_80 = _DAT_006adf10 ^ *(ulong *)(set + 0x28);
    local_68 = _DAT_006adf18 ^ 0x7465646279746573;
    uStack_58 = 0;
    local_60 = 0;
    uStack_48 = 0;
    uStack_50 = 0;
    uStack_70 = uStack_80 ^ 0x6c7967656e657261;
    local_78 = _DAT_006adf18 ^ 0x646f72616e646f6d;
    uStack_80 = uStack_80 ^ 0x736f6d6570736575;
    local_88 = 0;
    FUN_001b9084(&local_88, a, b);
    word_t h = FUN_001a8564();
    uint128_t r = FUN_0006af08(a, b, h);
    ulong u3 = r_lo;
    if ((r_hi & 1) == 0) {
        long b2 = set + (u3 >> 6) * 8;
        *(ulong *)(b2 + 0x40) |= 1L << (u3 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u3 * 0x10);
        v[0] = a;
        v[1] = b;
        word_t *s = (word_t *)(*(long *)(set + 0x38) + u3 * 0x28);
        s[1] = side[1];
        s[0] = side[0];
        s[3] = side[3];
        s[2] = side[2];
        s[4] = side[4];
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x6753a0);
}

/* FUN_001f7aa4 @ 0x001f7aa4   (est. cl4_sched_set_insert2_pair)
 * Ghidra: void FUN_001f7aa4(...5 args)
 * Inserts a 2-word key + 2-word side into a set via the obfuscated hash path.
 * Confidence: low
 * Notes: mirror of FUN_001f7820 with a 0x10-byte side slot. */
void cl4_sched_set_insert2_pair(word_t a, word_t b, word_t c, word_t d, long set)
{
    uStack_80 = _DAT_006adf10 ^ *(ulong *)(set + 0x28);
    uStack_58 = 0;
    local_60 = 0;
    uStack_48 = 0;
    uStack_50 = 0;
    local_68 = _DAT_006adf18 ^ 0x7465646279746573;
    uStack_70 = uStack_80 ^ 0x6c7967656e657261;
    uStack_80 = uStack_80 ^ 0x736f6d6570736575;
    local_88 = 0;
    local_78 = _DAT_006adf18 ^ 0x646f72616e646f6d;
    FUN_001b9084(&local_88, a, b);
    word_t h = FUN_001a8564();
    uint128_t r = FUN_0006af08(a, b, h);
    ulong u4 = r_lo;
    if ((r_hi & 1) == 0) {
        long b2 = set + (u4 >> 6) * 8;
        *(ulong *)(b2 + 0x40) |= 1L << (u4 & 0x3f);
        word_t *v = (word_t *)(*(long *)(set + 0x30) + u4 * 0x10);
        v[0] = a;
        v[1] = b;
        word_t *s = (word_t *)(*(long *)(set + 0x38) + u4 * 0x10);
        s[0] = c;
        s[1] = d;
        *(long *)(set + 0x10) += 1;
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(0x6753a0);
}

/* FUN_001f7be0 @ 0x001f7be0   (est. cl4_sched_set_insert_requeue)
 * Ghidra: void FUN_001f7be0(void)
 * Inserts and requeues a scheduler slot: finds the free index via
 * FUN_001f9dbc, dispatches through the owner methods and bumps the count.
 * Confidence: low
 * Notes: FUN_001f9dbc index; two +0x20 dispatches; noreturn overflow. */
void cl4_sched_set_insert_requeue(void)
{
    FUN_00084220();
    word_t v1 = FUN_00353430();
    FUN_00350678(in_x5);
    FUN_0035136c();
    (*extraout_x8)();
    FUN_00356b8c();
    FUN_00351c58();
    uint128_t r = FUN_001f9dbc();
    if ((r_hi & 1) == 0) {
        long i = FUN_00084024(unaff_x19 + (r_lo >> 6) * 8);
        (**(code **)(*(long *)(in_x3 + -8) + 0x20))
            (*(long *)(unaff_x19 + 0x30) + *(long *)(*(long *)(in_x3 + -8) + 0x48) * i, v1, in_x3);
        FUN_003511e4();
        (**(code **)(extraout_x16 + 0x20))
            (*(long *)(unaff_x19 + 0x38) + *(long *)(extraout_x16 + 0x48) * r_lo);
        *(long *)(unaff_x19 + 0x10) += 1;
        FUN_00084234(unaff_x30);
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_002591b4(in_x3);
}

/* FUN_001f7ce8 @ 0x001f7ce8   (est. cl4_sched_fail_c)
 * Ghidra: void FUN_001f7ce8(void)
 * Scheduler failure path: signals and panics.
 * Confidence: low
 * Notes: FUN_003488bc(1); FUN_0006f768; noreturn FUN_001afe4c. */
void cl4_sched_fail_c(void)
{
    FUN_003488bc(1);
    FUN_0006f768();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001f7d28 @ 0x001f7d28   (est. cl4_sched_get_base_30)
 * Ghidra: undefined8 FUN_001f7d28(long param_1)
 * Accessor: returns the value array base at offset 0x30.
 * Confidence: low
 * Notes: trivial 8-byte load. */
word_t cl4_sched_get_base_30(long sched)
{
    return *(word_t *)(sched + 0x30);
}

/* FUN_001f7d54 @ 0x001f7d54   (est. cl4_sched_clear_two_slots)
 * Ghidra: void FUN_001f7d54(void)
 * Clears two scheduler slots: resolves both indices and zeroes the value+side
 * entries via FUN_0035bc70.
 * Confidence: low
 * Notes: FUN_0034fbc4 index; FUN_0035bc70 clear x2. */
void cl4_sched_clear_two_slots(void)
{
    FUN_0034ee78();
    long i1 = FUN_0034fbc4(*(word_t *)(extraout_x1 + 0x30));
    FUN_0035bc70(extraout_x8 + *(long *)(extraout_x16 + 0x48) * i1, 1);
    FUN_003522b8(*(word_t *)(unaff_x20 + 0x38));
    FUN_0035bc70(extraout_x8_00 + *(long *)(extraout_x16_00 + 0x48) * unaff_x21, 1);
}

/* FUN_001f7dc0 @ 0x001f7dc0   (est. cl4_sched_bit_or)
 * Ghidra: void FUN_001f7dc0(void)
 * ORs a bitmask into a scheduler slot word.
 * Confidence: low
 * Notes: FUN_0035acc8; bitwise OR store. */
void cl4_sched_bit_or(void)
{
    FUN_0035acc8();
    *(ulong *)(extraout_x1 + extraout_x8) |= extraout_x9;
}

/* FUN_001f7de4 @ 0x001f7de4   (est. cl4_sched_state_set)
 * Ghidra: void FUN_001f7de4(void)
 * Sets scheduler state: resolves the value (FUN_0031948c) and runs the state
 * write hook.
 * Confidence: low
 * Notes: FUN_0031948c resolve; FUN_0034b778 write. */
void cl4_sched_state_set(void)
{
    word_t v = FUN_0031948c(in_x4);
    FUN_0034b778(v);
    (*extraout_x8)();
}

/* FUN_001f7e30 @ 0x001f7e30   (est. cl4_sched_bit_set)
 * Ghidra: void FUN_001f7e30(ulong param_1, long param_2, ulong param_3)
 * Sets a masked bit in a scheduler slot: masks (param_3 & param_1), resolves the
 * slot and ORs the mask in.
 * Confidence: low
 * Notes: FUN_0022b130 mask; FUN_0035acc8; OR store. */
void cl4_sched_bit_set(ulong a, long sched, ulong c)
{
    FUN_0022b130(c & a);
    FUN_0035acc8();
    *(ulong *)(sched + extraout_x8) |= extraout_x9;
}

/* FUN_001f7e68 @ 0x001f7e68   (est. cl4_sched_swap_slots)
 * Ghidra: void FUN_001f7e68(...5 args)
 * Swaps two scheduler slot pairs: resolves both indices and copies the entries
 * via FUN_0019ce60.
 * Confidence: low
 * Notes: FUN_00354010 index; FUN_0019ce60 copy x2. */
void cl4_sched_swap_slots(word_t a, word_t b, long sched, word_t d, word_t e)
{
    FUN_0034ba88();
    uint128_t r = FUN_00354010(*(word_t *)(sched + 0x30));
    FUN_0019ce60(extraout_x8 + *(long *)(extraout_x16 + 0x48) * r_lo, 1,
                 extraout_x8 + *(long *)(extraout_x16 + 0x48) * r_hi);
    FUN_003522b8(*(word_t *)(unaff_x20 + 0x38));
    FUN_0019ce60(extraout_x8_00 + *(long *)(extraout_x16_00 + 0x48) * unaff_x22, 1,
                 extraout_x8_00 + *(long *)(extraout_x16_00 + 0x48) * unaff_x21, e);
}

/* FUN_001f7ee4 @ 0x001f7ee4   (est. cl4_sched_swap_slots_b)
 * Ghidra: void FUN_001f7ee4(...5 args)
 * Swaps two scheduler slot pairs (variant using FUN_001f2104 for the copy).
 * Confidence: low
 * Notes: mirror of FUN_001f7e68 with FUN_001f2104 copy. */
void cl4_sched_swap_slots_b(word_t a, word_t b, long sched, word_t d, word_t e)
{
    FUN_0034ba88();
    uint128_t r = FUN_00354010(*(word_t *)(sched + 0x30));
    FUN_001f2104(extraout_x8 + *(long *)(extraout_x16 + 0x48) * r_lo,
                 extraout_x8 + *(long *)(extraout_x16 + 0x48) * r_hi, d);
    FUN_003522b8(*(word_t *)(unaff_x20 + 0x38));
    FUN_001f2104(extraout_x8_00 + *(long *)(extraout_x16_00 + 0x48) * unaff_x22,
                 extraout_x8_00 + *(long *)(extraout_x16_00 + 0x48) * unaff_x21, e);
}

/* FUN_001f7f5c @ 0x001f7f5c   (est. cl4_sched_dict_lookup)
 * Ghidra: void FUN_001f7f5c(undefined8 param_1, undefined8 param_2, long param_3)
 * Dictionary-style slot lookup: checks the entry (FUN_001f99f4) and if present
 * dispatches value+side through the +0x28 methods; otherwise if capacity allows
 * inserts via FUN_001f0700, else panics with a NativeDictionary fatal error.
 * Confidence: low
 * Notes: strings s_Fatal_error / s_Swift_NativeDictionary confirm a dictionary;
 *   FUN_001f99f4 lookup; noreturn panic. */
void cl4_sched_dict_lookup(word_t a, word_t b, long sched)
{
    long ctx = *unaff_x20;
    long l3 = *(long *)(sched + 0x10);
    uint128_t r = FUN_001f99f4(a, l3, *(word_t *)(sched + 0x20));
    long i1 = r_lo;
    if ((r_hi & 1) != 0) {
        long l4 = *(long *)(sched + 0x18);
        (**(code **)(*(long *)(l3 + -8) + 0x28))
            (*(long *)(ctx + 0x30) + *(long *)(*(long *)(l3 + -8) + 0x48) * i1, a, l3);
        long l3b = *(long *)(l4 + -8);
        /* WARNING: could not recover jumptable at 0x1f8020; indirect jump as call */
        (**(code **)(l3b + 0x28))
            (*(long *)(ctx + 0x38) + *(long *)(l3b + 0x48) * i1, b, l4);
        return;
    }
    if (*(ulong *)(ctx + 0x10) < *(ulong *)(ctx + 0x18)) {
        FUN_001f0700(i1, a, b, ctx, l3, *(word_t *)(sched + 0x18));
        return;
    }
    /* WARNING: subroutine does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, &DAT_005be7c0, 0, 2,
                 s_Swift_NativeDictionary_swift_005be800, 0x1c, 2, 0x206, 1);
}

/* FUN_001f80ac @ 0x001f80ac   (est. cl4_sched_op_dispatch6)
 * Ghidra: void FUN_001f80ac(void)
 * Six-argument scheduler op dispatch: takes the caller context, derives the key,
 * dispatches through the method at +0x20 and runs the completion.
 * Confidence: low
 * Notes: thunk take; FUN_0031a29c key; method +0x20; FUN_003544c8. */
void cl4_sched_op_dispatch6(void)
{
    FUN_00354744();
    uint128_t r = FUN_0034d2b4();
    thunk_FUN_0036b270(*r_lo);
    FUN_00350018();
    FUN_001f8144();
    FUN_0035159c();
    FUN_003a25d4();
    in_stack_00000008 = in_x6;
    FUN_0034b358(0);
    FUN_0031a29c();
    FUN_00349530();
    (**(code **)(extraout_x16 + 0x20))(r_hi, &stack0x00000008);
    FUN_003544c8(extraout_x8);
}

/* FUN_001f8144 @ 0x001f8144   (est. cl4_sched_accessor_8144) */
/* Ghidra: void FUN_001f8144(void) — alias of FUN_001f814c. Confidence: low */
void cl4_sched_accessor_8144(void) { FUN_001f814c(); }

/* FUN_001f814c @ 0x001f814c   (est. cl4_sched_scan_apply_main)
 * Ghidra: void FUN_001f814c(void)
 * Main scheduler scan-and-apply: walks the slot bitmap (bit-reverse scan) and
 * applies the pair op to each entry through the owner method vectors, checking
 * per-entry completion and requeueing; two walk variants (normal + compact).
 * Confidence: low
 * Notes: LZCOUNT bit scan; large (0x1f814c-0x1f8978); SoftwareBreakpoint
 *   overflow; noreturn panic; string constant 0x6753a0 marker. */
void cl4_sched_scan_apply_main(void)
{
    FUN_0008e518();
    word_t u5 = in_x4;
    uint128_t r = FUN_00358da0();
    long l8 = r_hi, l15 = r_lo;
    r = FUN_00353160();
    FUN_003722e4(r_lo, r_hi, u5, s_key_value_005cea2a, 0);
    FUN_00352efc();
    FUN_00310d68();
    FUN_003490b8(auStack_40);
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_00354028();
    r = FUN_00350720();
    FUN_003515b4(r_lo, r_hi, in_x4);
    FUN_003722e4();
    FUN_00349c44(&stack0x00000028);
    (*DAT_00658c00)(*(word_t *)(extraout_x16 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_003509a4();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_003509a4();
    FUN_00349c70();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_0034c754();
    FUN_00351118();
    long l4 = FUN_003722e4();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_03 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_0034ba68();
    FUN_00351a20(*(word_t *)(l15 + 0x10));
    u5 = FUN_001ee140();
    FUN_00352b98(unaff_x24 + -8);
    FUN_00352554(extraout_x16_02 + 8);
    FUN_00353b64(extraout_x16_01 + 0x20);
    word_t u6 = FUN_00353b70(extraout_x16_00 + 0x20);
    uint8_t u3 = (unaff_x25 == 0x6753a0);
    if (!(bool)u3) {
        thunk_FUN_001fca54(auStack_58, l15);
        word_t u7 = FUN_0035780c();
        FUN_00352ae4(u7, l8);
        FUN_001f6b30();
        local_78 = local_30;
        ulong u12 = (local_20 + 0x40U >> 6);
        FUN_0036b270(u5);
        thunk_FUN_0036b270(l15);
        ulong u13 = uStack_18, u14 = local_10[0];
        code *pc10 = pcStack_28;
        for (;;) {
            for (; u14 != 0; u14 = u14 - 1 & u14) {
                ulong u11 = bitrev_word(u14);
                u11 = LZCOUNT(u11 >> 0x20 | u11 << 0x20) | u13 << 6;
                (**(code **)(*(long *)(l8 + -8) + 0x10))
                    (local_100, *(long *)(local_30 + 0x30) + *(long *)(*(long *)(l8 + -8) + 0x48) * u11, l8);
                l15 = (long)*(int *)(l4 + 0x30);
                u5 = (**(code **)(*(long *)(unaff_x24 + -8) + 0x10))
                    (local_100 + l15, *(long *)(local_30 + 0x38) +
                     *(long *)(*(long *)(unaff_x24 + -8) + 0x48) * u11, unaff_x24);
                FUN_003519b4(&stack0x00000008, u5, local_100 + l15);
                FUN_00353bc4(local_100, extraout_x1_00, l8);
                FUN_001f8978();
                FUN_003510d0(&stack0x00000040);
                FUN_0006b6f4();
                (*extraout_x8_04)();
                FUN_00352888();
                FUN_0034bffc();
                if ((bool)u3) goto panic;
                int i1 = *(int *)(extraout_x1 + 0x30);
                FUN_0035675c();
                int i2 = *(int *)(l4 + 0x30);
                code *pc9 = (code *)*local_e0;
                FUN_003510ac();
                (*extraout_x8_05)();
                pc10 = (code *)*local_e8;
                (*pc10)(local_108 + i2, l15 + i1, in_x4);
                i1 = *(int *)(l4 + 0x30);
                FUN_00355ea4();
                FUN_00084180();
                u5 = (*pc9)();
                r = FUN_00352584(local_10, u5, local_108 + i1);
                (*pc10)(r_lo, r_hi, in_x4);
                FUN_00084180();
                FUN_00351768();
                FUN_001f7be0();
                FUN_00359f60();
                u5 = u6;
            }
            u14 = u13 + 1;
            if (SCARRY8(u13, 1)) {  /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f890c);
            }
            u3 = (u14 == u12);
            if ((long)u12 <= (long)u14) goto done;
            u13 = u14;
            u14 = *(ulong *)(pc10 + u14 * 8);
        }
    }
    /* compact walk variant */
    thunk_FUN_001fca54(auStack_58, l15);
    FUN_0035780c();
    FUN_00351118();
    FUN_001f6b30();
    local_78 = local_30;
    u12 = local_20 + 0x40U >> 6;
    FUN_0036b270(u5);
    thunk_FUN_0036b270(l15);
    u13 = local_10[0];
    u14 = uStack_18;
    for (;;) {
        for (; u13 != 0; u13 = u13 - 1 & u13) {
            FUN_00359894();
            ulong u11 = extraout_x8_06 | u14 << 6;
            (**(code **)(*(long *)(l8 + -8) + 0x10))
                (unaff_x27, *(long *)(local_30 + 0x30) + *(long *)(*(long *)(l8 + -8) + 0x48) * u11, l8);
            int i1 = *(int *)(l4 + 0x30);
            u5 = (**(code **)(*(long *)(unaff_x24 + -8) + 0x10))
                ((long)unaff_x27 + (long)i1, *(long *)(local_30 + 0x38) +
                 *(long *)(*(long *)(unaff_x24 + -8) + 0x48) * u11, unaff_x24);
            r = FUN_003547f8(u5, (long)unaff_x27 + (long)i1);
            FUN_00352c40(r_lo, r_hi, l8);
            FUN_001f8978();
            FUN_003510d0(&stack0x00000040);
            FUN_003508a8();
            (*extraout_x8_07)();
            FUN_00351330();
            FUN_0034d480();
            in_stack_ffffffffffffff08 = local_90;
            if ((bool)u3) goto panic;
            int i1b = *(int *)(extraout_x1 + 0x30);
            int i2 = *(int *)(local_d8 + 0x30);
            FUN_00354064();
            code *pc9 = (code *)*unaff_x27;
            r = FUN_00084180();
            (*pc9)(r_lo, r_hi, 0x6753a0);
            pc10 = (code *)*local_e8;
            (*pc10)(local_120 + i2, local_90 + i1b, in_x4);
            i1 = *(int *)(local_d8 + 0x30);
            FUN_0034f5b4();
            u5 = (*pc9)();
            r = FUN_00352d64(&pcStack_28, u5, local_120 + i1);
            (*pc10)(r_lo, r_hi, in_x4);
            r = FUN_00350720();
            FUN_00359ba4(r_lo, r_hi, in_x4, in_x6);
            FUN_00351130();
            FUN_001f7f5c();
        }
        u11 = u14 + 1;
        if (SCARRY8(u14, 1)) {  /* WARNING: does not return */
            SoftwareBreakpoint(1, 0x1f8910);
        }
        u3 = (u11 == u12);
        u5 = u6;
        if ((long)u12 <= (long)u11) break;
        u13 = *(ulong *)(pcStack_28 + u11 * 8);
        u14 = u11;
    }
done:
    FUN_0036b118(local_78);
    FUN_0036b118(u5);
    FUN_0008e500(u5, extraout_x8);
    return;
panic:
    FUN_0036b118(local_78);
    FUN_00350bc0(auStack_48);
    (*extraout_x8_08)(in_stack_ffffffffffffff08, local_140);
    FUN_0036b118(u6);
    FUN_0034b348();
    FUN_003489dc(in_x7);
    FUN_0034a2f8();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001f8978 @ 0x001f8978   (est. cl4_sched_entry_apply)
 * Ghidra: void FUN_001f8978(void)
 * Applies a scheduler op to the current entry: acquires the context, dispatches
 * the entry through the method vector and runs the completion/drain helpers.
 * Confidence: low
 * Notes: DAT_00658c00; FUN_00365b6c check; FUN_00354d68 dispatch; FUN_000839d8. */
void cl4_sched_entry_apply(void)
{
    FUN_0008e518();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_00349068();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_00349178();
    FUN_00350328();
    long l2 = FUN_003722e4();
    int i1 = *(int *)(l2 + 0x30);
    (**(code **)(extraout_x16_00 + 0x10))();
    FUN_003504ac();
    FUN_0035359c();
    FUN_00365b6c();
    uint128_t r = FUN_00354d68(*(word_t *)(extraout_x16 + 0x10));
    (*extraout_x8_02)(r_lo, r_hi, in_x3);
    FUN_00351720(extraout_x8 + i1);
    FUN_00365b6c();
    FUN_0034ba48();
    FUN_000839d8();
    FUN_0008e500(unaff_x30);
}

/* FUN_001f8abc @ 0x001f8abc   (est. cl4_sched_op_forward3)
 * Ghidra: void FUN_001f8abc(void)
 * Forwards a scheduler op: takes the caller context, resolves the entry
 * (FUN_001f8b64) and on success dispatches through the method at +0x20, then
 * runs the completion.
 * Confidence: low
 * Notes: thunk take; FUN_001f8b64 resolve; method +0x20; FUN_003544c8. */
void cl4_sched_op_forward3(void)
{
    FUN_00354744();
    uint128_t r = FUN_00352068();
    word_t ctx = *r_lo;
    thunk_FUN_0036b270(ctx);
    FUN_00351300();
    FUN_00356a2c();
    long found = FUN_001f8b64();
    FUN_003a25d4(ctx);
    word_t v = extraout_x1;
    if (found != 0) {
        in_stack_00000008 = found;
        FUN_0034f5e4();
        FUN_0031a29c();
        FUN_00349530();
        (**(code **)(extraout_x16 + 0x20))(r_hi, &stack0x00000008);
        v = extraout_x1_00;
    }
    FUN_003544c8(found != 0, v, extraout_x8);
}

/* FUN_001f8b64 @ 0x001f8b64   (est. cl4_sched_resolve_entry)
 * Ghidra: void FUN_001f8b64(void)
 * Resolves the next scheduler entry to run: walks the slot bitmap, dispatches
 * value+side through the two owner methods (+0x10), applies the pair op
 * (FUN_001f9324) and checks completion; two walk variants.
 * Confidence: low
 * Notes: LZCOUNT bit scan; two +0x10 dispatches; FUN_001f9324 apply;
 *   SoftwareBreakpoint overflow; noreturn panic. */
void cl4_sched_resolve_entry(void)
{
    FUN_0008e518();
    word_t u9 = in_x4;
    uint128_t r = FUN_00353e88();
    code *m1 = r_hi;
    long l6 = r_lo;
    r = FUN_00353160();
    long l7 = FUN_003722e4(r_lo, r_hi, u9, s_key_value_005cea2a, 0);
    FUN_00310d68(0, l7);
    FUN_003490b8(&lStack_28);
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_0034c754();
    FUN_003515b4();
    FUN_003722e4();
    FUN_00349c44(&stack0x00000038);
    (*DAT_00658c00)(*(word_t *)(extraout_x16 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_0034b8bc();
    FUN_0007c028();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_003509a4();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_0034c2c8();
    FUN_00350720();
    FUN_00351b78();
    long l8 = FUN_003722e4();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_0034ba68();
    u9 = FUN_001ee140(*(word_t *)(l6 + 0x10));
    FUN_00352b98(extraout_x16_02 + 8);
    FUN_00354128(extraout_x16_01 + 0x20);
    FUN_00353360(extraout_x16_00 + 0x20);
    uint8_t u5 = (unaff_x20 == 0x6753a0);
    if (!(bool)u5) {
        thunk_FUN_001fca54(auStack_58, l6);
        word_t u10 = FUN_0035780c();
        FUN_001f6b30(u10, m1, unaff_x22, in_x5);
        local_80 = local_30;
        FUN_00357540(local_20);
        thunk_FUN_0036b270(l6);
        word_t *pu3 = puStack_18;
        ulong u12 = local_10;
        for (;;) {
            for (; u12 != 0; u12 = u12 - 1 & u12) {
                ulong u13 = bitrev_word(u12);
                u13 = LZCOUNT(u13 >> 0x20 | u13 << 0x20) | (long)pu3 << 6;
                (**(code **)(*(long *)(m1 + -8) + 0x10))
                    (in_stack_ffffffffffffff08, local_30[6] + *(long *)(*(long *)(m1 + -8) + 0x48) * u13, m1);
                int i2 = *(int *)(l8 + 0x30);
                u10 = (**(code **)(unaff_x22[-1] + 0x10))
                    (in_stack_ffffffffffffff08 + i2, local_30[7] + *(long *)(unaff_x22[-1] + 0x48) * u13, unaff_x22);
                FUN_00351e48(&stack0x00000010, u10, in_stack_ffffffffffffff08 + i2);
                FUN_003531e4(in_stack_ffffffffffffff08);
                FUN_001f9324();
                FUN_0034d688();
                FUN_00350bf0();
                (*extraout_x8_03)();
                FUN_00352290();
                FUN_0034bffc();
                if ((bool)u5) goto panic;
                FUN_00353b64((long)*(int *)(l7 + 0x30));
                FUN_003553d8();
                i2 = *(int *)(m1 + 0x30);
                FUN_0035735c();
                code *pc11 = (code *)*unaff_x22;
                r = FUN_00100c38();
                (*pc11)(r_lo, r_hi, unaff_x20);
                code *pc14 = (code *)*local_d8;
                u10 = FUN_00357068(local_30, in_stack_ffffffffffffff00 + i2);
                (*pc14)(u10, extraout_x8_04 + extraout_x9, in_x4);
                i2 = *(int *)(m1 + 0x30);
                FUN_00350fec();
                u10 = (*pc11)();
                FUN_00352584(auStack_8, u10, in_stack_ffffffffffffff00 + i2, in_x4);
                (*pc14)();
                r = FUN_0007c1c4();
                FUN_001f7be0(r_lo, r_hi, u9, unaff_x20, in_x4, in_x6);
            }
            word_t *pu1 = (word_t *)((long)pu3 + 1);
            if (SCARRY8((long)pu3, 1)) {  /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f9320);
            }
            u5 = (pu1 == unaff_x22);
            if ((long)unaff_x22 <= (long)pu1) goto done;
            pu3 = pu1;
            u12 = *(ulong *)(lStack_28 + (long)pu1 * 8);
        }
    }
    /* compact walk variant */
    thunk_FUN_001fca54(auStack_58, l6);
    u9 = FUN_0035780c();
    FUN_001f6b30(u9, m1, unaff_x22, in_x5);
    local_80 = local_30;
    FUN_00357540(local_20);
    thunk_FUN_0036b270(l6);
    u12 = local_10;
    pu3 = puStack_18;
    for (;;) {
        for (; u12 != 0; u12 = u12 - 1 & u12) {
            FUN_003598ec();
            ulong u13 = extraout_x8_05 | (long)pu3 << 6;
            (**(code **)(*(long *)(m1 + -8) + 0x10))
                (unaff_x27, local_30[6] + *(long *)(*(long *)(m1 + -8) + 0x48) * u13, m1);
            int i2 = *(int *)(l8 + 0x30);
            u9 = (**(code **)(unaff_x22[-1] + 0x10))
                ((long)unaff_x27 + (long)i2, local_30[7] + *(long *)(unaff_x22[-1] + 0x48) * u13, unaff_x22);
            FUN_003524e0(&stack0x00000020, u9, (long)unaff_x27 + (long)i2);
            FUN_00352bec(unaff_x27);
            FUN_001f9324();
            FUN_0034d688();
            FUN_003508a8();
            (*extraout_x8_06)();
            FUN_00351330();
            r = FUN_0034d480();
            if ((bool)u5) {
                FUN_0036b118(local_30);
                FUN_00350bc0(&local_30);
                local_30 = local_e0;
                goto panic;
            }
            i2 = *(int *)(l7 + 0x30);
            FUN_00354058(r_lo, r_hi, 0x6753a0);
            FUN_0035735c();
            code *pc4 = (code *)*unaff_x27;
            FUN_00100c38();
            (*pc4)();
            FUN_0035460c();
            code *pc11 = (code *)*local_30;
            FUN_00353e38();
            (*pc11)(unaff_x24 + extraout_x8_07, (long)i2 + 0x6753a0, in_x4);
            i2 = *(int *)(local_c8 + 0x30);
            FUN_00351130();
            FUN_003540ac();
            (*pc4)();
            u9 = FUN_0035738c();
            r = FUN_00353124(&puStack_18, u9, unaff_x24 + i2);
            (*pc11)(r_lo, r_hi, in_x4);
            FUN_00359ba4(0, 0x6753a0, in_x4, in_x6);
            FUN_00350c2c();
            FUN_001f7f5c();
        }
        word_t *pu1 = (word_t *)((long)pu3 + 1);
        if (SCARRY8((long)pu3, 1)) {  /* WARNING: does not return */
            SoftwareBreakpoint(1, 0x1f9324);
        }
        u5 = (pu1 == unaff_x22);
        if ((long)unaff_x22 <= (long)pu1) break;
        u12 = *(ulong *)(lStack_28 + (long)pu1 * 8);
        pu3 = pu1;
    }
done:
    FUN_0036b118(local_80);
    word_t u9 = FUN_00355e38();
    FUN_0008e500(u9, unaff_x30);
    return;
panic:
    FUN_0036b118(local_30);
    FUN_00350bc0(&local_30);
    FUN_00357be0(local_30);
    (*extraout_x8_08)();
    FUN_00355e38();
    FUN_0036b118();
    u9 = FUN_00355e38();
    FUN_0008e500(u9, unaff_x30);
}

/* FUN_001f9324 @ 0x001f9324   (est. cl4_sched_pair_apply)
 * Ghidra: void FUN_001f9324(long param_1, code *param_2, ...7 args)
 * Applies a pair op over a scheduler slot: computes the two frame offsets, runs
 * the check (FUN_00365b6c) and routes each frame through its destructor/apply
 * methods, updating the shared key-value layout.
 * Confidence: low
 * Notes: stack-frame object construction (DAT_00658c00); FUN_00365b6c check;
 *   method +0x10/+0x20/+8; FUN_000839d8 drain. */
void cl4_sched_pair_apply(long a, code *cb, word_t c, long d, long e, long f, long g)
{
    local_88 = c;
    local_70 = cb;
    local_68 = a;
    lStack_98 = FUN_00310d68(0, g);
    long f1 = *(long *)(lStack_98 + -8);
    (*DAT_00658c00)(*(long *)(f1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    local_90 = *(long *)(e + -8);
    local_80 = e;
    local_78 = (long)&local_b0 - extraout_x8;
    (*DAT_00658c00)(*(word_t *)(local_90 + 0x40));
    long l8 = ((long)&local_b0 - extraout_x8) - (extraout_x8_00 + 0xfU & 0xfffffffffffffff0);
    local_a8 = *(long *)(g + -8);
    (*DAT_00658c00)(*(word_t *)(local_a8 + 0x40));
    long l5 = l8 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
    local_b0 = l5;
    long l2 = FUN_00310d68(0, f);
    long l6 = *(long *)(l2 + -8);
    (*DAT_00658c00)(*(long *)(l6 + 0x40) + 0xfU & 0xfffffffffffffff0);
    l5 = l5 - extraout_x8_02;
    (*DAT_00658c00)(*(word_t *)(*(long *)(d + -8) + 0x40));
    long l9 = l5 - (extraout_x8_03 + 0xfU & 0xfffffffffffffff0);
    long l7 = *(long *)(f + -8);
    (*DAT_00658c00)(*(word_t *)(l7 + 0x40));
    long l10 = l9 - (extraout_x8_04 + 0xfU & 0xfffffffffffffff0);
    (**(code **)(extraout_x12 + 0x10))(l9, cb, d);
    ulong u3 = FUN_00365b6c(l5, l9, d, f, 6);
    if ((u3 & 1) == 0) {
        FUN_000839d8(l5, 1, 1, f);
        (**(code **)(l6 + 8))(l5, l2);
    } else {
        FUN_000839d8(l5, 0, 1, f);
        code *pc11 = *(code **)(l7 + 0x20);
        (*pc11)(l10, l5, f);
        long l2b = local_80;
        (**(code **)(local_90 + 0x10))(l8, local_88, local_80);
        l5 = local_78;
        u3 = FUN_00365b6c(local_78, l8, l2b, g, 6);
        if ((u3 & 1) != 0) {
            FUN_000839d8(l5, 0, 1, g);
            long l6b = local_b0;
            code *pc12 = *(code **)(local_a8 + 0x20);
            local_70 = pc11;
            (*pc12)(local_b0, l5, g);
            l5 = FUN_003722e4(0, f, g, s_key_value_005cea2a, 0);
            long l2c = local_68;
            int i1 = *(int *)(l5 + 0x30);
            (*local_70)(local_68, l10, f);
            (*pc12)(l2c + i1, l6b, g);
            u4 = 0;
            goto out;
        }
        FUN_000839d8(l5, 1, 1, g);
        (**(code **)(l7 + 8))(l10, f);
        (**(code **)(local_a0 + 8))(l5, lStack_98);
    }
    l5 = FUN_003722e4(0, f, g, s_key_value_005cea2a, 0);
    u4 = 1;
    long l2 = local_68;
out:
    FUN_000839d8(l2, u4, 1, l5);
}

/* FUN_001f98a8 @ 0x001f98a8   (est. cl4_sched_hash_key)
 * Ghidra: void FUN_001f98a8(undefined8 param_1)
 * Hashes a scheduler key: runs the key hash (thunk_FUN_00229ebc on the set salt)
 * and mixes it via FUN_00072a30.
 * Confidence: low
 * Notes: thunk_FUN_00229ebc hash; FUN_00072a30 mix. */
void cl4_sched_hash_key(word_t key)
{
    word_t h = thunk_FUN_00229ebc(*(word_t *)(unaff_x20 + 0x28), key);
    FUN_00072a30(key, h);
}

/* FUN_001f98e8 @ 0x001f98e8   (est. cl4_sched_lookup_find)
 * Ghidra: void FUN_001f98e8(void)
 * Finds a scheduler entry: builds the key descriptor (obfuscated hash path),
 * hashes it (FUN_001a8564) and runs the lookup (FUN_00100efc/FUN_0006af08).
 * Confidence: low
 * Notes: obfuscated-string descriptor; FUN_001a8564 hash; FUN_0006af08 lookup. */
void cl4_sched_lookup_find(void)
{
    FUN_003509ec();
    FUN_00349bc4(*(word_t *)(unaff_x20 + 0x28));
    FUN_00351624();
    FUN_0034a5dc();
    FUN_0034af48();
    FUN_00355334();
    FUN_00077894();
    FUN_001b9084();
    uint128_t r = FUN_001a8564();
    FUN_00100efc(r_lo, r_hi, r_lo);
    FUN_0006af08();
}

/* FUN_001f9964 @ 0x001f9964   (est. cl4_sched_key_exists)
 * Ghidra: void FUN_001f9964(void)
 * Checks whether a scheduler key exists: builds the key, runs the lookup
 * (FUN_001f9a68) and returns the found-bit.
 * Confidence: low
 * Notes: FUN_001f9a68 lookup; FUN_0035847c result. */
void cl4_sched_key_exists(void)
{
    FUN_00041138();
    FUN_0034b440();
    FUN_0008e5d8();
    FUN_00351660();
    FUN_00350470();
    (*extraout_x9)();
    word_t v = in_stack_00000028;
    FUN_0034b440(&stack0x00000008);
    FUN_0031993c();
    uint128_t r = FUN_0034c5cc();
    (*extraout_x8)(r_lo, r_hi, v);
    FUN_000026e8(&stack0x00000008);
    FUN_000b43d0();
    uint128_t r2 = FUN_001f9a68();
    FUN_0035847c(r2_lo, r2_hi & 1, extraout_x1);
}

/* FUN_001f99f4 @ 0x001f99f4   (est. cl4_sched_lookup_key)
 * Ghidra: void FUN_001f99f4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Looks up a scheduler key in the set: resolves the compare function for param_3,
 * runs the key match (FUN_0031948c) and dispatches the result through
 * FUN_001f9dbc.
 * Confidence: low
 * Notes: FUN_0031948c compare; FUN_001f9dbc dispatch. */
void cl4_sched_lookup_key(word_t a, word_t b, word_t c)
{
    word_t salt = *(word_t *)(unaff_x20 + 0x28);
    code *cmp = (code *)FUN_0031948c(c);
    word_t h = (*cmp)(salt, b, c);
    FUN_001f9dbc(a, h, b, c);
}

/* FUN_001f9a68 @ 0x001f9a68   (est. cl4_sched_find_slot)
 * Ghidra: undefined1 [16] FUN_001f9a68(long param_1, ulong param_2)
 * Finds the slot for a scheduler key: computes the masked index, and if the bit
 * is set, probes the value array comparing the key (FUN_0031997c) until it finds
 * a match or an empty slot; returns {index, found}.
 * Confidence: low
 * Notes: LZCOUNT/probing; FUN_0031997c compare; FUN_003199ac cleanup. */
cl4_find_t cl4_sched_find_slot(long key, ulong idx)
{
    ulong u7 = -1L << ((ulong)*(byte *)(unaff_x20 + 0x20) & 0x3f);
    idx = idx & (u7 ^ 0xffffffffffffffff);
    uint found = 0;
    if ((*(ulong *)(unaff_x20 + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0) {
        do {
            FUN_0031996c(*(long *)(unaff_x20 + 0x30) + idx * 0x28, auStack_88);
            word_t u2 = uStack_68, u1 = local_70;
            FUN_0006a4c0(auStack_88, local_70);
            code *c = (code *)FUN_0008e5d8(u2);
            (*c)(auStack_b0, u1, u2);
            word_t u4 = uStack_90, u3 = local_98;
            FUN_0006a4c0(auStack_b0, local_98);
            word_t u1b = *(word_t *)(key + 0x18);
            word_t u2b = *(word_t *)(key + 0x20);
            FUN_0006a4c0(key, u1b);
            code *c2 = (code *)FUN_0008e5d8(u2b);
            (*c2)(auStack_d8, u1b, u2b);
            code *c3 = (code *)FUN_0031997c(u4);
            found = (*c3)(auStack_d8, u3, u4);
            FUN_000026e8(auStack_d8);
            FUN_000026e8(auStack_b0);
            FUN_003199ac(auStack_88);
            if ((found & 1) != 0) break;
            idx = idx + 1 & ~u7;
        } while ((*(ulong *)(unaff_x20 + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0);
    }
    cl4_find_t r;
    r.found = found & 1;
    r.index = idx;
    return r;
}

/* FUN_001f9be0 @ 0x001f9be0   (est. cl4_sched_probe_slot)
 * Ghidra: void FUN_001f9be0(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Probes the scheduler slot set for a matching key: walks from param_3, checking
 * the 2-word value against (param_2, param_1), with a preemption-escape check
 * (FUN_0035063c/FUN_002a0d50); returns {final_index, found}.
 * Confidence: low
 * Notes: key match at slot +0x10; preemption check bit 0x6000...; FUN_0008e500. */
void cl4_sched_probe_slot(word_t a, word_t b, ulong idx)
{
    FUN_0008e518();
    FUN_0008409c();
    FUN_00354948(*(uint8_t *)(unaff_x20 + 0x20));
    for (;;) {
        idx = idx & ~extraout_x8;
        ulong u2 = 1L << (idx & 0x3f) & *(ulong *)(unaff_x20 + 0x40 + (idx >> 6) * 8);
        if ((u2 == 0) ||
            (long *pl = (long *)(*(long *)(unaff_x20 + 0x30) + idx * 0x10),
             bool b3 = (*pl == unaff_x21 && pl[1] == unaff_x19), b3)) break;
        FUN_00359d70();
        if (!b3 || (extraout_x1 & 0x6000000000000000) != 0x6000000000000000) {
            FUN_0035063c();
            ulong u4 = FUN_002a0d50();
            if ((u4 & 1) != 0) break;
        }
        idx = idx + 1;
    }
    FUN_0008e500(idx, u2 != 0, unaff_x30);
}

/* FUN_001f9c8c @ 0x001f9c8c   (est. cl4_sched_probe_find)
 * Ghidra: void FUN_001f9c8c(void)
 * Probes the scheduler set for the current key: computes the masked index, and
 * if set, compares the 5-word key via FUN_0031997c; returns {index, found}.
 * Confidence: low
 * Notes: key compare FUN_0031997c; FUN_00356f80 result. */
void cl4_sched_probe_find(void)
{
    FUN_00356f9c();
    uint128_t r = FUN_00354948(*(uint8_t *)(unaff_x20 + 0x20));
    ulong u4 = r_hi & (extraout_x8 ^ 0xffffffffffffffff);
    uint found = 0;
    if ((*(ulong *)(unaff_x20 + 0x40 + (u4 >> 6) * 8) >> (u4 & 0x3f) & 1) != 0) {
        do {
            FUN_0031996c(*(long *)(unaff_x20 + 0x30) + u4 * 0x28, &stack0x00000058);
            FUN_0034b440(&stack0x00000058);
            FUN_00353b1c();
            FUN_00350470(&stack0x00000030);
            (*extraout_x9)();
            word_t u2 = in_stack_00000050;
            FUN_0006a4c0(&stack0x00000030, in_stack_00000048);
            word_t u1 = *(word_t *)(r_lo + 0x20);
            FUN_00350b78();
            FUN_000dbcc8();
            FUN_0008e5d8(u1);
            FUN_00351660();
            FUN_00350a04();
            (*extraout_x9_00)();
            FUN_0031997c(u2);
            FUN_00357b20();
            FUN_003513b4();
            found = (*extraout_x8_00)();
            FUN_000026e8(&stack0x00000008);
            FUN_000026e8(&stack0x00000030);
            FUN_003199ac(&stack0x00000058);
            if ((found & 1) != 0) break;
            u4 = u4 + 1 & ~extraout_x8;
        } while ((*(ulong *)(unaff_x20 + 0x40 + (u4 >> 6) * 8) >> (u4 & 0x3f) & 1) != 0);
    }
    FUN_00356f80(u4, found & 1, unaff_x30);
}

/* FUN_001f9dbc @ 0x001f9dbc   (est. cl4_sched_find_index)
 * Ghidra: undefined1 [16] FUN_001f9dbc(undefined8 param_1, undefined8 param_2, long param_3,
 *   undefined8 param_4)
 * Finds the index of a scheduler key in the set: walks from the hash index,
 * dispatching each slot through the owner +0x10 method and comparing via
 * FUN_0014ae44; returns {index, found}.
 * Confidence: low
 * Notes: method +0x10 dispatch; FUN_0014ae44 compare; FUN_00027754 key. */
cl4_find_t cl4_sched_find_index(word_t a, word_t b, long owner, word_t key)
{
    long l6 = *(long *)(owner + -8);
    local_80 = a;
    local_78 = key;
    (*DAT_00658c00)(*(word_t *)(l6 + 0x40));
    long l7 = (long)&local_80 - (extraout_x8 + 0xfU & 0xfffffffffffffff0);
    byte b2 = *(byte *)(unaff_x20 + 0x20);
    ulong u8 = extraout_x1;
    for (;;) {
        u8 = u8 & ~(-1L << ((ulong)b2 & 0x3f));
        ulong u1 = 1L << (u8 & 0x3f) & *(ulong *)(unaff_x20 + 0x40 + (u8 >> 6) * 8);
        if (u1 == 0) break;
        (**(code **)(l6 + 0x10))
            (l7, *(long *)(unaff_x20 + 0x30) + *(long *)(l6 + 0x48) * u8, owner);
        word_t u3 = FUN_00027754(local_78);
        code *c = (code *)FUN_0014ae44();
        ulong u5 = (*c)(l7, local_80, owner, u3);
        (**(code **)(l6 + 8))(l7, owner);
        if ((u5 & 1) != 0) break;
        u8 = u8 + 1;
    }
    cl4_find_t r;
    r.found = (u1 != 0);
    r.index = u8;
    return r;
}

/* FUN_001f9f40 @ 0x001f9f40   (est. cl4_sched_set_clear_all)
 * Ghidra: void FUN_001f9f40(void)
 * Clears a scheduler set: walks both the value and side bitmap arrays, zeroing
 * each set entry (FUN_0035bc70 / FUN_003590cc) until the set is empty, then
 * resets the count at +0x10.
 * Confidence: low
 * Notes: LZCOUNT bit scan; two clear passes; SoftwareBreakpoint overflow. */
void cl4_sched_set_clear_all(void)
{
    FUN_0008e518();
    long l4 = *unaff_x20;
    if (0 < unaff_x20[2]) {
        long l6 = *(long *)(l4 + 0x90);
        long l5 = *(long *)(l6 + -8);
        if ((*(byte *)(l5 + 0x52) & 1) != 0) {
            long v6 = unaff_x20[6];
            FUN_0034a340(unaff_x20[8]);
            ulong u8 = extraout_x11;
            if (extraout_w10 < 6) {
                u8 = ~(extraout_x11 << (extraout_x9 & 0x3f));
            }
            u8 = u8 & extraout_x8;
            ulong u26 = (extraout_x9 + 0x3f >> 6);
            long l2 = 0;
            for (;;) {
                if (u8 == 0) {
                    long l7;
                    do {
                        l7 = l2 + 1;
                        if (SCARRY8(l2, 1)) {  /* WARNING: does not return */
                            SoftwareBreakpoint(1, 0x1fa0bc);
                        }
                        if ((long)u26 <= l7) goto next;
                        FUN_0035713c();
                        l2 = extraout_x8_01;
                    } while (extraout_x9_00 == 0);
                    FUN_0034bdbc();
                    u8 = extraout_x10 & extraout_x9_01;
                    u3 = extraout_x8_02;
                } else {
                    FUN_0034e938();
                    u3 = extraout_x8_00;
                    l7 = l2;
                }
                FUN_0035bc70(v6 + *(long *)(l5 + 0x48) * (u3 | l7 << 6), 1, l6);
                l2 = l7;
            }
        }
next:
        if ((*(byte *)(*(long *)(*(long *)(l4 + 0x98) + -8) + 0x52) & 1) != 0) {
            FUN_0034a340(unaff_x20[8]);
            FUN_0035516c();
            long l4b = 0;
            for (;;) {
                if (u26 == 0) {
                    long l5b;
                    do {
                        l5b = l4b + 1;
                        if (SCARRY8(l4b, 1)) {  /* WARNING: does not return */
                            SoftwareBreakpoint(1, 0x1fa0c0);
                        }
                        if (unaff_x25 <= l5b) goto done;
                        FUN_00356688();
                        l4b = extraout_x8_03;
                    } while (extraout_x9_02 == 0);
                    FUN_0034bdbc();
                    u26 = extraout_x10_00 & extraout_x9_03;
                } else {
                    FUN_0034c194();
                    l5b = l4b;
                }
                FUN_003590cc();
                l4b = l5b;
            }
        }
done:
        unaff_x20[2] = 0;
    }
    FUN_0008e500();
}

/* FUN_001fa168 @ 0x001fa168   (est. cl4_sched_set_release_a) */
/* Ghidra: void FUN_001fa168(void) — alias of FUN_001fa16c. Confidence: low */
void cl4_sched_set_release_a(void) { FUN_001fa16c(); }

/* FUN_001fa16c @ 0x001fa16c   (est. cl4_sched_set_release)
 * Ghidra: void FUN_001fa16c(void)
 * Releases a scheduler set: clears all slots (FUN_001f9f40) then runs the two
 * teardown hooks.
 * Confidence: low
 * Notes: FUN_001f9f40 clear; FUN_00002850/FUN_0036b6ac teardown. */
void cl4_sched_set_release(void)
{
    FUN_001f9f40();
    FUN_00002850();
    FUN_0036b6ac();
}

/* FUN_001fa18c @ 0x001fa18c   (est. cl4_sched_set_reconfigure)
 * Ghidra: void FUN_001fa18c(long param_1)
 * Reconfigures a scheduler set from its header fields (bits/class/salt) via
 * FUN_001fa958.
 * Confidence: low
 * Notes: FUN_001fa958(shift, class, salt, 0). */
void cl4_sched_set_reconfigure(long set)
{
    FUN_001fa958(*(uint8_t *)(set + 0x20), *(uint *)(set + 0x24), *(word_t *)(set + 0x28), 0);
}

/* FUN_001fa1a0 @ 0x001fa1a0   (est. cl4_sched_set_alloc_28)
 * Ghidra: ulong FUN_001fa1a0(undefined8 param_1, ulong param_2, ulong param_3, char param_4)
 * Allocates a scheduler set with 0x28-byte value slots: computes capacity from
 * the shift bits, allocates the backing (FUN_0036a940), fills the header
 * (salt/class/method table) and initializes the empty bitmap.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; FUN_001fb05c method; thunk_FUN_00229ebc salt; the
 *   value/side arrays at +0x30/+0x38; empty bitmap = -1L<<bits. */
word_t cl4_sched_set_alloc_28(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u7 = (ulong)(char)shift;
    ulong u6 = 1L << (u7 & 0x3f);
    ulong u5 = (u6 + 0x3f >> 6);
    word_t u2 = FUN_00002534(&DAT_00657598, &DAT_004f1928);
    long l4 = 0x28L << (u7 & 0x3f);
    word_t u3 = FUN_0036a940(u2, (l4 + u5 * 8 + 0x47 & 0xfffffffffffffff8) + l4, 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u7 = u3;
    }
    if (internal != '\x01') {
        u7 = seed;
    }
    *(ulong *)(u3 + 0x28) = u7;
    *(long **)(u3 + 0x30) = pl + u5;
    *(long **)(u3 + 0x38) = pl + u5 + u6 * 5;
    if ((long)u6 < 0x40) {
        *pl = -1L << (u6 & 0x3f);
    } else {
        FUN_001b5474(0, u5, pl);
    }
    return u3;
}

/* FUN_001fa2e4 @ 0x001fa2e4   (est. cl4_sched_set_alloc_10)
 * Ghidra: ulong FUN_001fa2e4(undefined8 param_1, ulong param_2, ulong param_3, char param_4)
 * Allocates a scheduler set with 0x10-byte value slots (variant of FUN_001fa1a0).
 * Confidence: low
 * Notes: mirror of FUN_001fa1a0 with 0x10-byte slots; &DAT_006576d0. */
word_t cl4_sched_set_alloc_10(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u6 = (ulong)(char)shift;
    ulong u5 = 1L << (u6 & 0x3f);
    ulong u4 = (u5 + 0x3f >> 6);
    word_t u2 = FUN_00002534(&DAT_006576d0, &DAT_004f21d8);
    word_t u3 = FUN_0036a940(u2, ((0x28L << (u6 & 0x3f)) + u4 * 8 + 0x47 & 0xfffffffffffffff8) +
                              (0x10L << (u6 & 0x3f)), 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u6 = u3;
    }
    if (internal != '\x01') {
        u6 = seed;
    }
    *(ulong *)(u3 + 0x28) = u6;
    *(long **)(u3 + 0x30) = pl + u4;
    *(long **)(u3 + 0x38) = pl + u4 + u5 * 5;
    if ((long)u5 < 0x40) {
        *pl = -1L << (u5 & 0x3f);
    } else {
        FUN_001b5474(0, u4, pl);
    }
    return u3;
}

/* FUN_001fa430 @ 0x001fa430   (est. cl4_sched_set_alloc_20)
 * Ghidra: ulong FUN_001fa430(undefined8 param_1, ulong param_2, ulong param_3, char param_4)
 * Allocates a scheduler set with 0x20-byte value slots (variant of FUN_001fa1a0).
 * Confidence: low
 * Notes: mirror with 0x20-byte slots; &LAB_006576e0. */
word_t cl4_sched_set_alloc_20(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u6 = (ulong)(char)shift;
    ulong u5 = 1L << (u6 & 0x3f);
    ulong u4 = (u5 + 0x3f >> 6);
    word_t u2 = FUN_00002534(&LAB_006576e0, &DAT_004f21f0);
    word_t u3 = FUN_0036a940(u2, ((0x28L << (u6 & 0x3f)) + u4 * 8 + 0x47 & 0xfffffffffffffff8) +
                              (0x20L << (u6 & 0x3f)), 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u6 = u3;
    }
    if (internal != '\x01') {
        u6 = seed;
    }
    *(ulong *)(u3 + 0x28) = u6;
    *(long **)(u3 + 0x30) = pl + u4;
    *(long **)(u3 + 0x38) = pl + u4 + u5 * 5;
    if ((long)u5 < 0x40) {
        *pl = -1L << (u5 & 0x3f);
    } else {
        FUN_001b5474(0, u4, pl);
    }
    return u3;
}

/* FUN_001fa57c @ 0x001fa57c   (est. cl4_sched_set_alloc_20x10)
 * Ghidra: ulong FUN_001fa57c(undefined8 param_1, ulong param_2, ulong param_3, char param_4)
 * Allocates a scheduler set with 0x10-byte value + 0x20-byte side (variant).
 * Confidence: low
 * Notes: mirror with different side offset; &DAT_006576e8. */
word_t cl4_sched_set_alloc_20x10(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u6 = (ulong)(char)shift;
    ulong u5 = 1L << (u6 & 0x3f);
    ulong u4 = (u5 + 0x3f >> 6);
    word_t u2 = FUN_00002534(&DAT_006576e8, &DAT_004f21f8);
    word_t u3 = FUN_0036a940(u2, ((0x10L << (u6 & 0x3f)) + u4 * 8 + 0x47 & 0xfffffffffffffff8) +
                              (0x20L << (u6 & 0x3f)), 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u6 = u3;
    }
    if (internal != '\x01') {
        u6 = seed;
    }
    *(ulong *)(u3 + 0x28) = u6;
    *(long **)(u3 + 0x30) = pl + u4;
    *(long **)(u3 + 0x38) = pl + u4 + u5 * 2;
    if ((long)u5 < 0x40) {
        *pl = -1L << (u5 & 0x3f);
    } else {
        FUN_001b5474(0, u4, pl);
    }
    return u3;
}

/* FUN_001fa6c8 @ 0x001fa6c8   (est. cl4_sched_set_alloc_10x28)
 * Ghidra: ulong FUN_001fa6c8(...4 args)
 * Allocates a scheduler set with 0x10-byte value + 0x28-byte side (variant).
 * Confidence: low
 * Notes: mirror of FUN_001fa1a0; &LAB_006576d8. */
word_t cl4_sched_set_alloc_10x28(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u6 = (ulong)(char)shift;
    ulong u5 = 1L << (u6 & 0x3f);
    ulong u4 = (u5 + 0x3f >> 6);
    word_t u2 = FUN_00002534(&LAB_006576d8, &DAT_004f21e0);
    word_t u3 = FUN_0036a940(u2, ((0x10L << (u6 & 0x3f)) + u4 * 8 + 0x47 & 0xfffffffffffffff8) +
                              (0x28L << (u6 & 0x3f)), 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u6 = u3;
    }
    if (internal != '\x01') {
        u6 = seed;
    }
    *(ulong *)(u3 + 0x28) = u6;
    *(long **)(u3 + 0x30) = pl + u4;
    *(long **)(u3 + 0x38) = pl + u4 + u5 * 2;
    if ((long)u5 < 0x40) {
        *pl = -1L << (u5 & 0x3f);
    } else {
        FUN_001b5474(0, u4, pl);
    }
    return u3;
}

/* FUN_001fa814 @ 0x001fa814   (est. cl4_sched_set_alloc_10)
 * Ghidra: ulong FUN_001fa814(...4 args)
 * Allocates a scheduler set with 0x10-byte value + 0x10-byte side (variant).
 * Confidence: low
 * Notes: mirror of FUN_001fa1a0; &DAT_004e2080. */
word_t cl4_sched_set_alloc_10b(word_t shift, ulong cap, ulong seed, char internal)
{
    ulong u7 = (ulong)(char)shift;
    ulong u6 = 1L << (u7 & 0x3f);
    ulong u5 = (u6 + 0x3f >> 6);
    word_t u2 = FUN_00002534(0x653860, &DAT_004e2080);
    long l4 = 0x10L << (u7 & 0x3f);
    word_t u3 = FUN_0036a940(u2, (l4 + u5 * 8 + 0x47 & 0xfffffffffffffff8) + l4, 7);
    long *pl = (long *)(u3 + 0x40);
    *(word_t *)(u3 + 0x10) = 0;
    u2 = FUN_001fb05c(shift);
    *(word_t *)(u3 + 0x18) = u2;
    *(char *)(u3 + 0x20) = (char)shift;
    *(uint8_t *)(u3 + 0x21) = 0;
    *(uint16_t *)(u3 + 0x22) = 0;
    if ((cap & 0xff00000000) == 0x100000000) {
        cap = thunk_FUN_00229ebc(0, u3);
    }
    *(int *)(u3 + 0x24) = (int)cap;
    if (DAT_006adf20 == '\0') {
        u7 = u3;
    }
    if (internal != '\x01') {
        u7 = seed;
    }
    *(ulong *)(u3 + 0x28) = u7;
    *(long **)(u3 + 0x30) = pl + u5;
    *(long **)(u3 + 0x38) = pl + u5 + u6 * 2;
    if ((long)u6 < 0x40) {
        *pl = -1L << (u6 & 0x3f);
    } else {
        FUN_001b5474(0, u5, pl);
    }
    return u3;
}

/* FUN_001fa958 @ 0x001fa958   (est. cl4_sched_set_resize)
 * Ghidra: void FUN_001fa958(undefined8 param_1, undefined8 param_2, ulong param_3, uint param_4)
 * Resizes/reconfigures a scheduler set: computes the new capacity from the shift
 * bits and array strides, allocates the new backing (FUN_0036a940), fills the
 * header (method/salt/class) and initializes the empty bitmap.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; FUN_001fb05c method; thunk_FUN_00229ebc salt;
 *   empty bitmap -1L<<bits. */
void cl4_sched_set_resize(word_t shift, word_t cls, ulong seed, uint internal)
{
    uint128_t r = FUN_00351e20();
    word_t u7 = r_hi;
    ulong u12 = (ulong)r[0];
    ulong u11 = 1L << (u12 & 0x3f);
    FUN_0034b7e4();
    ulong u9 = (ulong)*(byte *)(extraout_x16 + 0x50);
    long l2 = u9 + extraout_x11 * 8;
    long l8 = *(long *)(*(long *)(extraout_x8 + 0x98) + -8);
    byte b4 = *(byte *)(l8 + 0x50);
    ulong u10 = (ulong)b4;
    long l3 = (*(long *)(extraout_x9 + 0x48) << (u12 & 0x3f)) + u10;
    ulong u5 = FUN_0036a940(extraout_x8,
        ((l2 + 0x40U & (u9 ^ 0xffffffffffffffff)) + l3 & (u10 ^ 0xffffffffffffffff)) +
        (*(long *)(l8 + 0x48) << (u12 & 0x3f)), *(byte *)(extraout_x16 + 0x50) | b4 | 7);
    long *pl = (long *)(u5 + 0x40);
    u9 = l2 + (long)pl & (u9 ^ 0xffffffffffffffff);
    *(word_t *)(u5 + 0x10) = 0;
    word_t u6 = FUN_001fb05c(r_lo);
    *(word_t *)(u5 + 0x18) = u6;
    *(char *)(u5 + 0x20) = r[0];
    *(uint8_t *)(u5 + 0x21) = 0;
    *(uint16_t *)(u5 + 0x22) = 0;
    if ((u7 & 0xff00000000) == 0x100000000) {
        FUN_00350500();
        u7 = thunk_FUN_00229ebc();
    }
    *(int *)(u5 + 0x24) = (int)u7;
    if (DAT_006adf20 == '\0') {
        u12 = u5;
    }
    if ((internal & 0xff) != 1) {
        u12 = seed;
    }
    *(ulong *)(u5 + 0x28) = u12;
    *(ulong *)(u5 + 0x30) = u9;
    *(ulong *)(u5 + 0x38) = u9 + l3 & (u10 ^ 0xffffffffffffffff);
    if ((long)u11 < 0x40) {
        *pl = -1L << (u11 & 0x3f);
    } else {
        FUN_001b5474(0, extraout_x11, pl);
    }
    FUN_00351d30(u5, unaff_x30);
}

/* FUN_001faaf0 @ 0x001faaf0   (est. cl4_sched_set_realloc)
 * Ghidra: void FUN_001faaf0(undefined8 param_1, undefined8 param_2)
 * Reallocates a scheduler set: computes the new size (FUN_001fab14), reconfigures
 * and resizes via FUN_001fa958.
 * Confidence: low
 * Notes: FUN_001fab14 sizing; FUN_0034c988; FUN_001fa958 resize. */
void cl4_sched_set_realloc(word_t a, word_t b)
{
    FUN_001fab14(b);
    FUN_0034c988();
    FUN_001fa958();
}

/* FUN_001fab14 @ 0x001fab14   (est. cl4_sched_grow_capacity)
 * Ghidra: long FUN_001fab14(ulong param_1)
 * Computes the grown capacity for a scheduler set: clamps to >=1, divides by the
 * load factor 0.75 (double arithmetic), validates against bounds and rounds up
 * to a power of two; panics on invalid input.
 * Confidence: low
 * Notes: load factor 0.75; double math; FUN_0022aaec pow2 round; SoftwareBreakpoint
 *   overflow; noreturn panic on bounds failure. */
long cl4_sched_grow_capacity(ulong n)
{
    if ((long)n < 2) {
        n = 1;
    }
    double d = (double)(long)((double)n / 0.75);
    if ((d == INFINITY) || (NAN(d))) {
        FUN_003488bc(1);
        FUN_003493d8();
    } else {
        bool b2 = d < DAT_004e7cd0;
        if (d <= DAT_004e7cd0) {
            FUN_003488bc(1);
            FUN_003493d8();
        } else {
            d = (double)FUN_003590ac();
            if (b2) {
                if (SCARRY8(extraout_x8, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1fac00);
                }
                long l3 = extraout_x8 + 1;
                if (extraout_x8 + 1 <= (long)d) {
                    l3 = (long)d;
                }
                l3 = FUN_0022aaec(l3 + -1);
                if (!SCARRY8(l3, 1)) {
                    return l3 + 1;
                }
                /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1fac04);
            }
            FUN_003488bc(1);
            FUN_003493d8();
        }
    }
    FUN_00351be0();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001fac04 @ 0x001fac04   (est. cl4_sched_set_realloc_b)
 * Ghidra: void FUN_001fac04(void)
 * Reallocates a scheduler set (variant of FUN_001faaf0).
 * Confidence: low
 * Notes: mirror of FUN_001faaf0. */
void cl4_sched_set_realloc_b(void)
{
    FUN_001fab14();
    FUN_0034c988();
    FUN_001fa958();
}

/* FUN_001fac24 @ 0x001fac24   (est. cl4_sched_priority_dispatch)
 * Ghidra: void FUN_001fac24(void)
 * Priority scheduler dispatch: acquires the two priority queues, compares their
 * heads (via the shared run check) and picks the higher-priority entry to run,
 * dispatching through the method vectors; several branch paths for empty/equal
 * queues. Heavy method-vector chain.
 * Confidence: low
 * Notes: FUN_00377824 queue heads; priority comparison; many method +0x10/+0x20
 *   dispatches; DAT_00658c00. */
void cl4_sched_priority_dispatch(void)
{
    FUN_0008e518();
    FUN_0034e8a4();
    FUN_00357748();
    FUN_00349684(in_x5);
    FUN_003513fc();
    word_t u2 = FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aab0();
    FUN_0034a774();
    FUN_003523fc();
    word_t u3 = FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_00350428();
    FUN_0034911c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003497b4();
    FUN_00349080();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003497b4();
    FUN_003531b4();
    FUN_003564a4();
    FUN_0034b4a0();
    (*unaff_x22)();
    FUN_003577e4();
    FUN_0034acd0();
    uint u1 = (*extraout_x8_03)();
    if (((unaff_w28 ^ u1) & 1) == 0) {
        FUN_00310a44();
        FUN_0034ae6c();
        (*extraout_x8_07)();
        FUN_00354864();
        FUN_00310a44();
        FUN_0034bfa4();
        long l5 = (*extraout_x8_08)();
        if (l5 <= (long)unaff_x22) {
            FUN_0034eaac();
            (*extraout_x8_13)();
            FUN_0034cee8();
            FUN_00353a84();
            FUN_00349f74();
            (*extraout_x9_00)();
            FUN_00348c84();
            goto merge;
        }
        FUN_0034de24();
        FUN_00351720();
        (*extraout_x8_09)();
        FUN_0034d1fc();
        FUN_00352200();
        FUN_00349f8c();
        (*extraout_x9)();
        FUN_00348e78();
        FUN_0034e51c();
        (*extraout_x8_10)();
        u7 = FUN_0034cd04();
        pc8 = extraout_x8_11;
    } else {
        FUN_0034b4a0();
        word_t u4 = (*unaff_x22)();
        FUN_0034c0d0();
        FUN_0034c9a8();
        long l5 = (*extraout_x8_04)();
        FUN_0034c368();
        FUN_0034f504();
        long l6 = (*extraout_x8_05)();
        if ((u4 & 1) == 0) {
            if (l5 < l6) {
                FUN_0034de24();
                FUN_00358ba8();
                (*extraout_x8_12)();
                goto tail;
            }
            FUN_0034ad00();
            FUN_0034d364();
            FUN_00377bec();
            FUN_003493ec();
            FUN_0034abd8();
            (*extraout_x9_04)();
            FUN_0034c384();
            FUN_00352e3c();
            FUN_0034c674();
            (*extraout_x9_05)();
            FUN_0034c480();
            FUN_00310b08();
            FUN_0034eae8();
            FUN_00350a1c();
            (*extraout_x8_15)();
            FUN_0034c888();
            (*extraout_x9_06)();
            if ((u2 & 1) == 0) goto done;
            FUN_0034cf94(*(word_t *)(l5 + 0x10));
            (*extraout_x8_16)();
        } else {
            if (l5 <= l6) {
                FUN_0034ad00();
                FUN_0034c694();
                FUN_00377bec();
                FUN_003493ec();
                FUN_0034abd8();
                (*extraout_x9_01)();
                FUN_0034c384();
                uint128_t r = FUN_0034d2f4(extraout_x8_02);
                (*extraout_x9_02)(r_lo, r_hi, extraout_x1);
                FUN_003496e8();
                FUN_0034fa1c();
                (*extraout_x8_14)();
                FUN_0034c870();
                (*extraout_x9_03)();
                if ((u3 & 1) != 0) goto done;
                FUN_0034cfb4(*(word_t *)(l5 + 0x10));
                (*extraout_x8_19)();
tail:
                FUN_0034d1fc();
                FUN_00352e30();
                FUN_00349f8c();
                (*extraout_x9_08)();
                FUN_00348e78();
                FUN_0034f434();
                (*extraout_x8_20)();
                FUN_0034d820();
                u7 = extraout_x8_00;
                pc8 = extraout_x8_21;
                goto fire;
            }
            FUN_0034e94c();
            (*extraout_x8_06)();
        }
        FUN_0034cee8();
        FUN_00352a64();
        FUN_00349f74();
        (*extraout_x9_07)();
        FUN_00348c84();
merge:
        FUN_0034e034();
        (*extraout_x8_17)();
        u7 = FUN_0034e33c();
        pc8 = extraout_x8_18;
    }
fire:
    (*pc8)(u7);
done:
    u7 = FUN_00352980();
    FUN_0008e500(u7, extraout_x8_00);
}

/* FUN_001fb05c @ 0x001fb05c   (est. cl4_sched_compute_bucket_count)
 * Ghidra: long FUN_001fb05c(ulong param_1)
 * Computes the number of buckets for a set of given shift bits: (1<<bits)*0.75,
 * validated against bounds via double math; panics on failure.
 * Confidence: low
 * Notes: load factor 0.75; double math; noreturn panic. */
long cl4_sched_compute_bucket_count(ulong bits)
{
    double d = (double)(1L << (bits & 0x3f)) * 0.75;
    if ((ulong)ABS(d) < 0x7ff0000000000000) {
        bool b1 = d < DAT_004e7cd0;
        if (d <= DAT_004e7cd0) {
            FUN_003488bc(1);
            FUN_003493d8();
        } else {
            d = (double)FUN_00354588(0x43e0000000000000);
            if (b1) {
                return (long)d;
            }
            FUN_003488bc(1);
            FUN_003493d8();
        }
    } else {
        FUN_00348c18();
        FUN_003493d8();
    }
    FUN_00351be0();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001fb140 @ 0x001fb140   (est. cl4_sched_hash_salt)
 * Ghidra: void FUN_001fb140(void)
 * Hashes a scheduler salt: runs the state prep then the key hash thunk.
 * Confidence: low
 * Notes: FUN_00352efc; thunk_FUN_00229ebc. */
void cl4_sched_hash_salt(void)
{
    FUN_00352efc();
    thunk_FUN_00229ebc();
}

/* FUN_001fb194 @ 0x001fb194   (est. cl4_sched_swap_store)
 * Ghidra: void FUN_001fb194(undefined8 *param_1, undefined8 *param_2)
 * Swaps two scheduler slots: takes param_2's value, stores into param_1 and
 * releases the old param_1 value.
 * Confidence: low
 * Notes: FUN_0036b270 take; FUN_003a25d4 release. */
void cl4_sched_swap_store(word_t *dst, word_t *src)
{
    word_t v = *src;
    word_t old = *dst;
    *dst = v;
    FUN_0036b270(v);
    FUN_003a25d4(old);
}

/* FUN_001fb1cc @ 0x001fb1cc   (est. cl4_sched_mask_bitmap)
 * Ghidra: void FUN_001fb1cc(long param_1)
 * Masks the scheduler bitmap to the valid capacity range (via FUN_00354948 +
 * FUN_0022b040).
 * Confidence: low
 * Notes: FUN_00354948; FUN_0022b040 mask. */
void cl4_sched_mask_bitmap(long set)
{
    long l = FUN_00354948(*(uint8_t *)(set + 0x20));
    FUN_0022b040(l + 0x40, ~extraout_x8);
}

/* FUN_001fb204 @ 0x001fb204   (est. cl4_sched_slot_clear)
 * Ghidra: void FUN_001fb204(long param_1, undefined8 param_2, long param_3)
 * Clears a scheduler slot after validating its index/class, else panics.
 * Confidence: low
 * Notes: FUN_003535f4/FUN_00357e24 validation; FUN_0022afd8 clear; noreturn panic. */
void cl4_sched_slot_clear(word_t a, word_t b, long set)
{
    if ((((-1 < a) && (uint128_t r1 = FUN_003535f4(), !(bool)in_CY)) &&
        (uint128_t r2 = FUN_00357e24(r1_lo, set + 0x40), (extraout_x9 & 1) != 0)) &&
        (r1_hi == *(int *)(set + 0x24))) {
        FUN_0022afd8(r2_lo, r2_hi, ~extraout_x8);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001fb26c @ 0x001fb26c   (est. cl4_sched_find_or_empty)
 * Ghidra: undefined1 [16] FUN_001fb26c(undefined8 param_1, long param_2)
 * Returns the slot for a scheduler key, or an empty-marker: if the set is
 * non-empty, finds the slot via FUN_003577cc; returns {index, class}.
 * Confidence: low
 * Notes: empty set -> class 0x100000000; FUN_003577cc lookup. */
cl4_find_t cl4_sched_find_or_empty(word_t a, long set)
{
    if (*(long *)(set + 0x10) != 0) {
        uint128_t r = FUN_003577cc();
        word_t u1 = r_lo;
        cl4_find_t out;
        if ((r_hi & 1) == 0) {
            out.index = 0;
            out.found = 0x100000000;
        } else {
            out.found = (ulong)*(uint *)(unaff_x20 + 0x24);
            out.index = u1;
        }
        return out;
    }
    return ZEXT816(0x100000000) << 0x40;
}

/* FUN_001fb2f0 @ 0x001fb2f0   (est. cl4_sched_requeue_found)
 * Ghidra: void FUN_001fb2f0(...5 args)
 * Requeues a found scheduler slot: if the set is non-empty and the key matches,
 * dispatches the slot through the +0x10 method, then runs the drain tail.
 * Confidence: low
 * Notes: FUN_003577cc lookup; method +0x10; FUN_0034dba8/FUN_000839d8. */
void cl4_sched_requeue_found(word_t a, word_t b, long set, word_t d, word_t e)
{
    if ((*(long *)(set + 0x10) == 0) ||
        (uint128_t r = FUN_003577cc(), b = r_lo, (r_hi & 1) == 0)) {
        u2 = 1;
    } else {
        long l1 = FUN_00350bcc();
        b = (**(code **)(extraout_x16 + 0x10))
            (a, *(long *)(unaff_x20 + 0x38) + *(long *)(extraout_x16 + 0x48) * l1, e);
        u2 = 0;
    }
    FUN_0034dba8(b, u2);
    FUN_000839d8();
}

/* FUN_001fb370 @ 0x001fb370   (est. cl4_sched_class_dispatch2)
 * Ghidra: void FUN_001fb370(...7 args)
 * Dispatches both value and side slots for a validated index/class.
 * Confidence: low
 * Notes: bitmap+class validation; two +0x10 dispatches; noreturn panic. */
void cl4_sched_class_dispatch2(word_t a, word_t b, ulong idx, int cls, long set, long o1, word_t o2)
{
    if ((((-1 < (long)idx) && (idx >> ((ulong)*(byte *)(set + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(set + (idx >> 6) * 8 + 0x40) >> (idx & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(set + 0x24))) {
        (**(code **)(*(long *)(o1 + -8) + 0x10))
            (a, *(long *)(set + 0x30) + *(long *)(*(long *)(o1 + -8) + 0x48) * idx, o1);
        FUN_00354d2c(*(word_t *)(set + 0x38));
        /* WARNING: could not recover jumptable at 0x1fb438; indirect jump as call */
        (**(code **)(extraout_x16 + 0x10))
            (b, extraout_x8 + *(long *)(extraout_x16 + 0x48) * idx, o2);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001fb44c @ 0x001fb44c   (est. cl4_sched_value_dispatch)
 * Ghidra: void FUN_001fb44c(...5 args)
 * Dispatches a validated scheduler value slot via +0x10; else panics.
 * Confidence: low
 * Notes: bitmap+class validation; method +0x10; noreturn panic. */
void cl4_sched_value_dispatch(word_t a, ulong idx, int cls, long set, long owner)
{
    if ((((-1 < (long)idx) && (idx >> ((ulong)*(byte *)(set + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(set + (idx >> 6) * 8 + 0x40) >> (idx & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(set + 0x24))) {
        /* WARNING: could not recover jumptable at 0x1fb4ac; indirect jump as call */
        (**(code **)(*(long *)(owner + -8) + 0x10))
            (a, *(long *)(set + 0x30) + *(long *)(*(long *)(owner + -8) + 0x48) * idx, owner);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001fb4d0 @ 0x001fb4d0   (est. cl4_sched_side_dispatch)
 * Ghidra: void FUN_001fb4d0(...6 args)
 * Dispatches a validated scheduler side slot via +0x10; else panics.
 * Confidence: low
 * Notes: bitmap+class validation; method +0x10; noreturn panic. */
void cl4_sched_side_dispatch(word_t a, ulong idx, int cls, long set, word_t c, long owner)
{
    if ((((-1 < (long)idx) && (idx >> ((ulong)*(byte *)(set + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(set + (idx >> 6) * 8 + 0x40) >> (idx & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(set + 0x24))) {
        /* WARNING: could not recover jumptable at 0x1fb530; indirect jump as call */
        (**(code **)(*(long *)(owner + -8) + 0x10))
            (a, *(long *)(set + 0x38) + *(long *)(*(long *)(owner + -8) + 0x48) * idx, owner);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001fb554 @ 0x001fb554   (est. cl4_sched_found_dispatch)
 * Ghidra: void FUN_001fb554(...5 args)
 * Dispatches a found scheduler slot if present: looks up via FUN_001f99f4 and
 * dispatches the side through +0x10; runs the drain tail.
 * Confidence: low
 * Notes: FUN_001f99f4 lookup; method +0x10; FUN_00350774/FUN_000839d8. */
void cl4_sched_found_dispatch(word_t a, word_t b, long set, word_t d, word_t e)
{
    bool found;
    if (*(long *)(set + 0x10) == 0) {
        found = true;
    } else {
        FUN_003561a0();
        thunk_FUN_0036b270(extraout_x1);
        FUN_00077708();
        FUN_001f99f4();
        found = (extraout_x1_00 & 1) == 0;
        if (!found) {
            long l1 = FUN_00350bcc();
            (**(code **)(extraout_x16 + 0x10))
                (a, *(long *)(unaff_x20 + 0x38) + *(long *)(extraout_x16 + 0x48) * l1, e);
        }
        FUN_0036b118();
    }
    FUN_00350774(a, found);
    FUN_000839d8();
}

/* FUN_001fb60c @ 0x001fb60c   (est. cl4_sched_op_build_dispatch)
 * Ghidra: void FUN_001fb60c(...4 args)
 * Builds a scheduler op descriptor and dispatches it: allocates the state
 * (zones 0x6bb9), fills via FUN_001fbb74 and runs the value dispatch, then the
 * completion.
 * Confidence: low
 * Notes: FUN_0036a908 alloc 0x6bb9; FUN_001fbb74; FUN_00351548; FUN_00084234. */
void cl4_sched_op_build_dispatch(word_t a, word_t b, word_t c, long set)
{
    uint128_t r = FUN_00084220();
    word_t *p = (word_t *)FUN_0036a908(0x48, 0x6bb9);
    *r_lo = (long)p;
    p[1] = set;
    p[2] = unaff_x20;
    p[0] = r_hi;
    long l4 = *(long *)(set + 0x18);
    p[3] = l4;
    FUN_00350530();
    word_t u3 = FUN_00310d68();
    p[4] = u3;
    FUN_00352018();
    p[5] = extraout_x16;
    u3 = FUN_0036a908(*(word_t *)(extraout_x8 + 0x40), 0x6bb9);
    p[6] = u3;
    uint128_t r2 = FUN_001fbb74(r_hi, c, set);
    p[7] = r2_lo;
    *(byte *)(p + 8) = r2[8] & 1;
    bool absent = (r2_hi & 1) == 0;
    if (!absent) {
        (**(code **)(*(long *)(l4 + -8) + 0x20))
            (u3, *(long *)(*unaff_x20 + 0x38) + *(long *)(*(long *)(l4 + -8) + 0x48) * r2_lo, l4);
    }
    FUN_00351548(u3, absent);
    FUN_000839d8();
    FUN_00084234(FUN_001fb738, u3, unaff_x30);
}

/* FUN_001fb738 @ 0x001fb738   (est. cl4_sched_op_release_cb)
 * Ghidra: void FUN_001fb738(undefined8 *param_1)
 * Release callback for a scheduler op descriptor: forwards the state through
 * FUN_00258d9c, releases the inner object and the descriptor.
 * Confidence: low
 * Notes: FUN_00258d9c; FUN_0006b6f4; thunk_FUN_00012568 x2. */
void cl4_sched_op_release_cb(word_t *desc)
{
    word_t *p = (word_t *)*desc;
    word_t u1 = p[6];
    long l2 = p[5];
    FUN_00258d9c(u1, *(uint8_t *)(p + 8), p[2], p[7], *p,
                 *(word_t *)(p[1] + 0x10), p[3], *(word_t *)(p[1] + 0x20));
    FUN_0006b6f4(*(word_t *)(l2 + 8));
    (*extraout_x8)();
    cl4_obj_release(u1);   /* thunk_FUN_00012568 */
    cl4_obj_release(p);    /* thunk_FUN_00012568 */
}

/* FUN_001fb7a8 @ 0x001fb7a8   (est. cl4_sched_op_insert_forward)
 * Ghidra: void FUN_001fb7a8(...3 args)
 * Inserts a scheduler op: takes the caller CNode, runs the insert helper
 * FUN_001fbb74, dispatches the value through +0x20, and finalizes with the
 * release/epilogue helpers.
 * Confidence: low
 * Notes: FUN_003a261c CNode; FUN_001fbb74 insert; FUN_001fb194/FUN_0036b118. */
void cl4_sched_op_insert_forward(word_t a, word_t b, long set)
{
    FUN_0008e518();
    long l3 = *(long *)(set + 0x18);
    FUN_00350530();
    word_t u1 = FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0034998c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_0034947c();
    FUN_003a261c(*unaff_x20);
    FUN_0035478c();
    FUN_00350b48();
    (*extraout_x9)();
    local_8 = *unaff_x20;
    FUN_00359aec();
    FUN_0034f5e4();
    FUN_00359ba4();
    FUN_001fbb74();
    if ((extraout_x1 & 1) != 0) {
        (**(code **)(*(long *)(l3 + -8) + 0x20))();
    }
    FUN_00351548();
    FUN_000839d8();
    code *pc2 = *(code **)(extraout_x16 + 8);
    (*pc2)();
    uint128_t r = FUN_00356ae8(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_00)(r_lo, r_hi, u1);
    FUN_0035a134();
    FUN_00258d9c();
    FUN_00350618();
    (*pc2)();
    FUN_00351414(*(word_t *)(extraout_x16_00 + 8));
    (*extraout_x8_01)();
    FUN_00351584(unaff_x20, &local_8);
    FUN_001fb194();
    FUN_0036b118(local_8);
    FUN_0008e500(unaff_x30);
}

/* FUN_001fb9e0 @ 0x001fb9e0   (est. cl4_sched_op_cmp)
 * Ghidra: void FUN_001fb9e0(undefined8 param_1, undefined8 param_2, uint param_3)
 * Scheduler comparison op: looks up the key (FUN_001f98e8), and on a change
 * re-verifies (FUN_00258c60) panic-ing on inconsistency; returns the key+flag.
 * Confidence: low
 * Notes: FUN_001f98e8 lookup; SoftwareBreakpoint overflow; noreturn on mismatch. */
void cl4_sched_op_cmp(word_t a, word_t b, uint mode)
{
    FUN_0008e518();
    FUN_00359b24();
    FUN_00355d9c();
    FUN_001f98e8();
    uint128_t r4 = FUN_000775b8();
    word_t u3 = r4_lo;
    if (SCARRY8(extraout_x8, extraout_x9)) {   /* WARNING: does not return */
        SoftwareBreakpoint(1, 0x1fba80);
    }
    FUN_00350914();
    uint128_t r6 = FUN_00002534();
    FUN_00356ad0(mode & 1, r6_hi, r6_lo);
    ulong u2 = FUN_00258c60();
    if ((u2 & 1) != 0) {
        FUN_00351384();
        uint128_t r5 = FUN_001f98e8();
        u3 = r5_lo;
        if ((r4_hi & 1) != (r5_hi & 1)) {
            FUN_003593dc();
            /* WARNING: subroutine does not return */
            FUN_002591b4();
        }
    }
    FUN_0008e500(u3, r4_hi & 1, unaff_x30);
}

/* FUN_001fbac4 @ 0x001fbac4   (est. cl4_sched_op_cmp_b)
 * Ghidra: void FUN_001fbac4(void)
 * Scheduler comparison op (variant using FUN_001f9964 and FUN_00084220).
 * Confidence: low
 * Notes: mirror of FUN_001fb9e0. */
void cl4_sched_op_cmp_b(void)
{
    uint128_t r4 = FUN_00084220();
    FUN_001f9964();
    uint128_t r5 = FUN_000775b8();
    word_t u3 = r5_lo;
    if (SCARRY8(extraout_x8, extraout_x9)) {   /* WARNING: does not return */
        SoftwareBreakpoint(1, 0x1fbb68);
    }
    FUN_000a6e14();
    uint128_t r6 = FUN_00002534();
    FUN_00356ad0(r4_hi & 1, r6_hi, r6_lo);
    ulong u2 = FUN_00258c60();
    if ((u2 & 1) != 0) {
        r4 = FUN_001f9964(r4_lo);
        u3 = r4_lo;
        if ((r5_hi & 1) != (r4_hi & 1)) {
            /* WARNING: subroutine does not return */
            FUN_002591b4(0x673a80);
        }
    }
    FUN_00084234(u3, r5_hi & 1, unaff_x30);
}

/* FUN_001fbb74 @ 0x001fbb74   (est. cl4_sched_insert_helper)
 * Ghidra: void FUN_001fbb74(undefined8 param_1, undefined8 param_2, long param_3)
 * Insert helper for a scheduler op: looks up the key (FUN_001f99f4), and on a
 * change re-verifies via FUN_00258c60, panic-ing on inconsistency; returns the
 * slot+flag.
 * Confidence: low
 * Notes: FUN_001f99f4 lookup; SoftwareBreakpoint overflow; noreturn mismatch. */
void cl4_sched_insert_helper(word_t a, word_t b, long set)
{
    FUN_0008e518();
    word_t u4 = *(word_t *)(set + 0x10);
    FUN_00350c8c();
    FUN_001f99f4();
    word_t u2 = FUN_000775b8();
    if (SCARRY8(extraout_x8, extraout_x9)) {   /* WARNING: does not return */
        SoftwareBreakpoint(1, 0x1fbc18);
    }
    ulong u3 = FUN_00258c60(extraout_w1 & 1, extraout_x8 + extraout_x9, set);
    if ((u3 & 1) != 0) {
        FUN_0034ed78();
        uint128_t r5 = FUN_001f99f4();
        u2 = r5_lo;
        if ((extraout_w1_00 & 1) != (r5_hi & 1)) {
            /* WARNING: subroutine does not return */
            FUN_002591b4(u4);
        }
    }
    FUN_0008e500(u2, extraout_w1_00 & 1, unaff_x30);
}

/* FUN_001fbd10 @ 0x001fbd10   (est. cl4_sched_set_copy_28)
 * Ghidra: void FUN_001fbd10(void)
 * Copies a scheduler set into a freshly allocated 0x28-byte-slot set: allocates
 * (FUN_001fa6c8), walks the source bitmap and copies each value+side payload.
 * Confidence: low
 * Notes: FUN_001fa6c8 alloc; LZCOUNT bit scan; SoftwareBreakpoint overflow. */
void cl4_sched_set_copy_28(void)
{
    word_t u4 = FUN_0035193c();
    FUN_0034b930();
    FUN_001fa6c8();
    FUN_00353584();
    if (extraout_x8 == 0) {
        FUN_0036b118();
        *unaff_x20 = unaff_x21;
        FUN_00351774(u4);
        return;
    }
    ulong u5 = FUN_0034a7e0();
    if (!(bool)in_ZR || extraout_x9 <= u5) {
        FUN_00358404();
    }
    long l6 = 0;
    *(word_t *)(unaff_x21 + 0x10) = *(word_t *)(unaff_x19 + 0x10);
    FUN_0034a604();
    FUN_0034f804();
    FUN_00357df4();
    if (unaff_x26 == 0) goto advance;
    for (;;) {
        FUN_0034c194();
        for (;;) {
            FUN_00359574();
            FUN_0031996c(extraout_x9_01 + unaff_x27 * 0x28, &stack0x00000008);
            word_t *v = (word_t *)(*(long *)(unaff_x21 + 0x30) + unaff_x27 * 0x10);
            v[0] = unaff_x28;
            v[1] = unaff_x23;
            word_t *s = (word_t *)(*(long *)(unaff_x21 + 0x38) + unaff_x27 * 0x28);
            s[1] = in_stack_00000010;
            s[0] = in_stack_00000008;
            s[3] = in_stack_00000020;
            s[2] = in_stack_00000018;
            s[4] = in_stack_00000028;
            thunk_FUN_0036b270();
            if (unaff_x26 != 0) break;
advance:
            do {
                long l1 = l6 + 1;
                if (SCARRY8(l6, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1fbe20);
                }
                if (unaff_x25 <= l1) {
                    FUN_0036b118();
                    *unaff_x20 = unaff_x21;
                    FUN_00351774(u4);
                    return;
                }
                l6 = l6 + 1;
            } while (*(long *)(unaff_x22 + l1 * 8) == 0);
            FUN_0034bdbc();
            unaff_x26 = extraout_x10 & extraout_x9_00;
            l6 = l1;
        }
    }
}

/* FUN_001fbe20 @ 0x001fbe20   (est. cl4_sched_set_copy_20x10)
 * Ghidra: void FUN_001fbe20(void)
 * Copies a scheduler set into a 0x20x10-byte-slot set (variant of FUN_001fbd10).
 * Confidence: low
 * Notes: mirror of FUN_001fbd10; FUN_001fa57c alloc. */
void cl4_sched_set_copy_20x10(void)
{
    word_t u4 = FUN_00351e20();
    FUN_0034b930();
    FUN_001fa57c();
    FUN_00353584();
    if (extraout_x8 != 0) {
        ulong u5 = FUN_0034a7e0();
        if (!(bool)in_ZR || extraout_x9 <= u5) {
            FUN_00358404();
        }
        long l6 = 0;
        *(word_t *)(unaff_x21 + 0x10) = *(word_t *)(unaff_x19 + 0x10);
        FUN_0034a604();
        FUN_0034f804();
        FUN_00357df4();
        if (unaff_x26 == 0) goto advance;
        for (;;) {
            FUN_0034c194();
            for (;;) {
                FUN_00359574();
                FUN_00319808(extraout_x9_01 + unaff_x27 * 0x20);
                word_t *v = (word_t *)(*(long *)(unaff_x21 + 0x30) + unaff_x27 * 0x10);
                v[0] = unaff_x28;
                v[1] = unaff_x23;
                FUN_00310d98();
                thunk_FUN_0036b270();
                if (unaff_x26 != 0) break;
advance:
                do {
                    long l1 = l6 + 1;
                    if (SCARRY8(l6, 1)) {   /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1fbf08);
                    }
                    if (unaff_x25 <= l1) goto done;
                    l6 = l6 + 1;
                } while (*(long *)(unaff_x22 + l1 * 8) == 0);
                FUN_0034bdbc();
                unaff_x26 = extraout_x10 & extraout_x9_00;
                l6 = l1;
            }
        }
    }
done:
    FUN_0036b118();
    *unaff_x20 = unaff_x21;
    FUN_00351d30(u4);
}

/* FUN_001fbf08 @ 0x001fbf08   (est. cl4_sched_set_copy_10)
 * Ghidra: void FUN_001fbf08(void)
 * Copies a scheduler set into a 0x10-byte-slot set (variant of FUN_001fbd10).
 * Confidence: low
 * Notes: mirror; FUN_001fa2e4 alloc. */
void cl4_sched_set_copy_10(void)
{
    word_t u5 = FUN_0035193c();
    FUN_0034b930();
    FUN_001fa2e4();
    FUN_00353584();
    if (extraout_x8 != 0) {
        ulong u6 = FUN_0034a7e0();
        if (!(bool)in_ZR || extraout_x9 <= u6) {
            FUN_00358404();
        }
        long l8 = 0;
        *(word_t *)(unaff_x21 + 0x10) = *(word_t *)(unaff_x19 + 0x10);
        FUN_0034a604();
        FUN_0034f804();
        FUN_00355080();
        if (unaff_x25 == 0) goto advance;
        for (;;) {
            FUN_0034cb24();
            for (;;) {
                word_t u7 = FUN_0035974c();
                FUN_0031996c(u7, &stack0x00000008);
                word_t *sv = (word_t *)(*(long *)(unaff_x19 + 0x38) + unaff_x26 * 0x10);
                word_t sv0 = *sv, sv1 = sv[1];
                word_t *v = (word_t *)(*(long *)(unaff_x21 + 0x30) + unaff_x27 * 8);
                v[1] = in_stack_00000010;
                v[0] = in_stack_00000008;
                v[3] = in_stack_00000020;
                v[2] = in_stack_00000018;
                v[4] = in_stack_00000028;
                word_t *s = (word_t *)(*(long *)(unaff_x21 + 0x38) + unaff_x26 * 0x10);
                s[0] = sv0;
                s[1] = sv1;
                thunk_FUN_0036b270();
                if (unaff_x25 != 0) break;
advance:
                do {
                    long l1 = l8 + 1;
                    if (SCARRY8(l8, 1)) {   /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1fbffc);
                    }
                    if (unaff_x24 <= l1) goto done;
                    FUN_00356688();
                    l8 = extraout_x8_00;
                } while (extraout_x9_00 == 0);
                FUN_0034bdbc();
                unaff_x25 = extraout_x10 & extraout_x9_01;
                l8 = l1;
            }
        }
    }
done:
    FUN_0036b118();
    *unaff_x20 = unaff_x21;
    FUN_00351774(u5);
}

/* FUN_001fbffc @ 0x001fbffc   (est. cl4_sched_set_copy_20)
 * Ghidra: void FUN_001fbffc(void)
 * Copies a scheduler set into a 0x20-byte-slot set (variant of FUN_001fbd10).
 * Confidence: low
 * Notes: mirror; FUN_001fa430 alloc. */
void cl4_sched_set_copy_20(void)
{
    word_t u4 = FUN_000b4594();
    FUN_0034b930();
    FUN_001fa430();
    FUN_00353584();
    if (extraout_x8 != 0) {
        ulong u5 = FUN_0034a7e0();
        if (!(bool)in_ZR || extraout_x9 <= u5) {
            FUN_00358404();
        }
        long l7 = 0;
        *(word_t *)(unaff_x21 + 0x10) = *(word_t *)(unaff_x19 + 0x10);
        FUN_0034a604();
        FUN_0034f804();
        FUN_00355080();
        if (unaff_x25 == 0) goto advance;
        for (;;) {
            FUN_0034cb24();
            for (;;) {
                word_t u6 = FUN_0035974c();
                FUN_0031996c(u6, &stack0x00000028);
                FUN_00319808(*(long *)(unaff_x19 + 0x38) + unaff_x26 * 0x20, &stack0x00000008);
                word_t *v = (word_t *)(*(long *)(unaff_x21 + 0x30) + unaff_x27 * 8);
                v[4] = in_stack_00000048;
                v[1] = in_stack_00000030;
                v[0] = in_stack_00000028;
                v[3] = in_stack_00000040;
                v[2] = in_stack_00000038;
                FUN_00310d98(&stack0x00000008, *(long *)(unaff_x21 + 0x38) + unaff_x26 * 0x20);
                if (unaff_x25 != 0) break;
advance:
                do {
                    long l1 = l7 + 1;
                    if (SCARRY8(l7, 1)) {   /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1fc0f4);
                    }
                    if (unaff_x24 <= l1) goto done;
                    FUN_00356688();
                    l7 = extraout_x8_00;
                } while (extraout_x9_00 == 0);
                FUN_0034bdbc();
                unaff_x25 = extraout_x10 & extraout_x9_01;
                l7 = l1;
            }
        }
    }
done:
    FUN_0036b118();
    *unaff_x20 = unaff_x21;
    FUN_000b45b0(u4);
}

/* FUN_001fc0f4 @ 0x001fc0f4   (est. cl4_sched_set_grow)
 * Ghidra: void FUN_001fc0f4(void)
 * Grows/rehashes a scheduler set: if non-empty, allocates a new set
 * (FUN_001fa18c), copies the bitmap, then re-inserts every slot via the owner
 * method vectors (rehash); releases the old set.
 * Confidence: low
 * Notes: FUN_001fa18c alloc; LZCOUNT bit scan; rehash via +0x10/+0x20 methods;
 *   SoftwareBreakpoint overflow. */
void cl4_sched_set_grow(void)
{
    FUN_0008e518();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    long l3 = FUN_003497b4();
    FUN_00349b3c(l3, *(word_t *)(l3 + 0x10));
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    FUN_0031b524(0);
    long l7 = *unaff_x20;
    l3 = FUN_001fa18c(l7);
    if (*(long *)(l7 + 0x10) == 0) {
        FUN_0036b118(l7);
        *unaff_x20 = l3;
        FUN_0008e500(extraout_x1);
        return;
    }
    long l1 = l7 + 0x40;
    ulong u5 = (1L << ((ulong)*(byte *)(l3 + 0x20) & 0x3f)) + 0x3fU >> 6;
    if (l3 != l7 || l1 + u5 * 8 <= l3 + 0x40U) {
        FUN_00117d14(l3 + 0x40U, l1, u5 << 3);
    }
    long l6 = 0;
    *(word_t *)(l3 + 0x10) = *(word_t *)(l7 + 0x10);
    FUN_0034c6f4(*(uint8_t *)(l7 + 0x20));
    local_8 = 0xffffffffffffffff;
    if (extraout_w9 < 6) {
        local_8 = ~(-1L << (extraout_x8_02 & 0x3f));
    }
    local_8 = local_8 & *(ulong *)(l7 + 0x40);
    if (local_8 == 0) goto advance;
    for (;;) {
        ulong u5b = bitrev_word(local_8);
        local_8 = local_8 - 1 & local_8;
        for (;;) {
            u5b = u5b | l6 << 6;
            long l8 = *(long *)(extraout_x16_00 + 0x48) * u5b;
            word_t u4 = (**(code **)(extraout_x16_00 + 0x10))
                (extraout_x16_00 + 0x10, extraout_x8_01, *(long *)(l7 + 0x30) + l8, extraout_x1_00);
            long l9 = *(long *)(extraout_x16 + 0x48) * u5b;
            FUN_00358f54(u4, *(long *)(l7 + 0x38) + l9);
            (*extraout_x9_00)(extraout_x16 + 0x10);
            FUN_00351b60(*(long *)(l3 + 0x30) + l8);
            (*extraout_x9_01)(extraout_x16_00 + 0x20);
            FUN_000dbe70(*(long *)(l3 + 0x38) + l9);
            (*extraout_x9_02)(extraout_x16 + 0x20);
            if (local_8 != 0) break;
advance:
            do {
                long l8 = l6 + 1;
                if (SCARRY8(l6, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1fc3b4);
                }
                if ((long)(extraout_x8_02 + 0x3f >> 6) <= l8) {
                    FUN_0036b118(l7);
                    *unaff_x20 = l3;
                    FUN_0008e500(extraout_x1);
                    return;
                }
                l6 = l6 + 1;
            } while (*(long *)(l1 + l8 * 8) == 0);
            FUN_0034bdbc();
            local_8 = extraout_x10 & extraout_x9;
            u5b = extraout_x8_03;
            l6 = l8;
        }
    }
}

/* FUN_001fc3b4 @ 0x001fc3b4   (est. cl4_sched_op_insert_check)
 * Ghidra: void FUN_001fc3b4(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *   long param_4)
 * Insert-check op for a scheduler set: looks up via FUN_001fbb74; if present
 * dispatches value+side through +0x20, otherwise runs the insert requeue path.
 * Confidence: low
 * Notes: FUN_001fbb74 lookup; +0x20 dispatch; FUN_001f0700 requeue; FUN_000839d8. */
void cl4_sched_op_insert_check(word_t a, word_t b, word_t c, long set)
{
    FUN_0008e518();
    long l2 = set;
    FUN_00353b10();
    word_t u3 = *(word_t *)(l2 + 0x10);
    FUN_0034998c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003493ac();
    uint128_t r = FUN_001fbb74(extraout_x1, c, l2);
    l2 = *unaff_x20;
    if ((r_hi & 1) != 0) {
        long l1 = *(long *)(*(long *)(set + 0x18) + -8);
        code *pc = *(code **)(l1 + 0x20);
        long l1b = *(long *)(l1 + 0x48);
        (*pc)();
        FUN_003511d8(*(long *)(l2 + 0x38) + l1b * r_lo);
        (*pc)();
        FUN_0034ba48();
        FUN_0008e500();
        FUN_000839d8();
        return;
    }
    r = FUN_00350a34(*(word_t *)(extraout_x16 + 0x10));
    (*extraout_x8_00)(r_lo, r_hi, u3);
    FUN_00350a04();
    FUN_003523fc();
    FUN_00356170();
    FUN_001f0700();
    FUN_0034c6c4();
    FUN_000839d8();
    FUN_0008e500(unaff_x30);
}

/* FUN_001fc500 @ 0x001fc500   (est. cl4_sched_op_lookup_dispatch)
 * Ghidra: void FUN_001fc500(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *   long param_4)
 * Lookup-dispatch op: looks up via FUN_001fbb74; if present dispatches side via
 * +0x28, otherwise runs the insert requeue path.
 * Confidence: low
 * Notes: FUN_001fbb74 lookup; +0x28 dispatch; FUN_001f0700 requeue. */
void cl4_sched_op_lookup_dispatch(word_t a, word_t b, word_t c, long set)
{
    FUN_0008e518();
    long l1 = set;
    FUN_00352798();
    FUN_00349734();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348f50();
    uint128_t r = FUN_001fbb74(extraout_x1, c, l1);
    if ((r_hi & 1) != 0) {
        long l1b = *(long *)(*(long *)(set + 0x18) + -8);
        /* WARNING: could not recover jumptable at 0x1fc5cc; indirect jump as call */
        (**(code **)(l1b + 0x28))
            (*(long *)(*unaff_x20 + 0x38) + *(long *)(l1b + 0x48) * r_lo);
        return;
    }
    FUN_0034c9d8(*(word_t *)(extraout_x16 + 0x10));
    (*extraout_x8_00)();
    FUN_003508c0(r_lo);
    FUN_001f0700();
    FUN_0008e500(unaff_x30);
}

/* FUN_001fc614 @ 0x001fc614   (est. cl4_sched_read2_fill)
 * Ghidra: void FUN_001fc614(void)
 * Reads a 2-word scheduler tuple: resolves the slot and copies both words into
 * the caller buffer.
 * Confidence: low
 * Notes: FUN_0034f7c0 resolve; 2-word copy. */
void cl4_sched_read2_fill(void)
{
    FUN_0034f7c0();
    FUN_00356f30();
    FUN_00357898();
    FUN_003598f8();
    word_t *p = (word_t *)(extraout_x9 + unaff_x21 * 0x10);
    word_t v = p[1];
    *unaff_x22 = *p;
    unaff_x22[1] = v;
    FUN_003540ac();
    FUN_0034e280();
    FUN_00259954();
    FUN_0009461c();
}

/* FUN_001fc674 @ 0x001fc674   (est. cl4_sched_read2_fill_b)
 * Ghidra: void FUN_001fc674(void)
 * Reads a 2-word scheduler tuple (variant using FUN_003585ac(0x28)).
 * Confidence: low
 * Notes: mirror of FUN_001fc614. */
void cl4_sched_read2_fill_b(void)
{
    FUN_0034f7c0();
    FUN_00356f1c();
    FUN_00357898();
    FUN_003598f8();
    FUN_003585ac(0x28);
    FUN_003540ac();
    FUN_0034e280();
    FUN_00259954();
    FUN_0009461c();
}

/* FUN_001fc6d4 @ 0x001fc6d4   (est. cl4_sched_read_side20)
 * Ghidra: void FUN_001fc6d4(void)
 * Reads a 0x20-byte side tuple into the caller buffer.
 * Confidence: low
 * Notes: FUN_00310d98 copy; FUN_00351f34. */
void cl4_sched_read_side20(void)
{
    FUN_0034f7c0();
    FUN_00356f08();
    FUN_00357898();
    FUN_00310d98(*(long *)(*unaff_x20 + 0x38) + unaff_x21 * 0x20);
    FUN_00351f34();
    FUN_003540ac();
    FUN_0034e280();
    FUN_00084180();
    FUN_00259954();
    FUN_00351450();
}

/* FUN_001fc744 @ 0x001fc744   (est. cl4_sched_read_side28)
 * Ghidra: void FUN_001fc744(void)
 * Reads a 0x28-byte side tuple into the caller buffer.
 * Confidence: low
 * Notes: FUN_003585ac(0x28) copy. */
void cl4_sched_read_side28(void)
{
    FUN_0034f7c0();
    FUN_00356ef4();
    FUN_00357898();
    FUN_003585ac(0x28);
    FUN_003598cc();
    FUN_00353d64();
    FUN_0034e2b8();
    FUN_00259954();
    FUN_0009461c();
}

/* FUN_001fc7ac @ 0x001fc7ac   (est. cl4_sched_read5_fill)
 * Ghidra: void FUN_001fc7ac(void)
 * Reads a 5-word scheduler tuple: resolves the slot and copies the 5-word value
 * plus the 0x20-byte side into the caller buffers.
 * Confidence: low
 * Notes: FUN_00258c60 index; 0x28-byte value + 0x20-byte side copy. */
void cl4_sched_read5_fill(void)
{
    FUN_0034b318();
    word_t u4 = *(word_t *)(*unaff_x20 + 0x18);
    word_t u2 = FUN_00356ee0();
    FUN_00258c60(in_x3, u4, u2);
    long l1 = *(long *)(*unaff_x20 + 0x38);
    word_t *p = (word_t *)(*(long *)(*unaff_x20 + 0x30) + unaff_x21 * 0x28);
    word_t v0 = *p, v3 = p[3], v2 = p[2];
    unaff_x23[1] = p[1];
    unaff_x23[0] = v0;
    unaff_x23[3] = v3;
    unaff_x23[2] = v2;
    unaff_x23[4] = p[4];
    FUN_00310d98(l1 + unaff_x21 * 0x20);
    FUN_00351f34();
    FUN_003598cc();
    FUN_0034e2b8();
    FUN_00084180();
    FUN_00259954();
}

/* FUN_001fc840 @ 0x001fc840   (est. cl4_sched_read_dispatch)
 * Ghidra: void FUN_001fc840(void)
 * Reads and dispatches a scheduler entry: resolves the index and invokes the two
 * owner methods (+0x20) to fill the value+side.
 * Confidence: low
 * Notes: FUN_00258c60 index; two +0x20 dispatches; FUN_00259954. */
void cl4_sched_read_dispatch(void)
{
    FUN_00084220();
    long l1 = in_x4;
    FUN_0034b318();
    FUN_00258c60(in_x3, *(word_t *)(*unaff_x20 + 0x18), l1);
    l1 = *(long *)(in_x4 + 0x18);
    FUN_00352d10();
    (**(code **)(extraout_x16 + 0x20))();
    (**(code **)(*(long *)(l1 + -8) + 0x20))();
    FUN_000b43d0();
    FUN_00351aec();
    FUN_00084234();
    FUN_00259954();
}

/* FUN_001fc908 @ 0x001fc908   (est. cl4_sched_set_rehash)
 * Ghidra: void FUN_001fc908(void)
 * Rehashes a scheduler set: on the shrink path reallocates (FUN_001fa958);
 * otherwise walks the bitmap and clears both value and side slots via
 * FUN_0035bc70, then resets the bitmap and count.
 * Confidence: low
 * Notes: FUN_001fa958 realloc; LZCOUNT bit scan; FUN_0035bc70 clear; overflow. */
void cl4_sched_set_rehash(void)
{
    uint128_t r = FUN_00084220();
    long l5 = r_hi;
    long l6 = *unaff_x20;
    if ((r_lo & 1) == 0) {
        uint8_t u3 = *(uint8_t *)(l6 + 0x20);
        l5 = FUN_0031b524(0, *(word_t *)(l5 + 0x10), *(word_t *)(l5 + 0x18), *(word_t *)(l5 + 0x20));
        FUN_0034c988(u3);
        FUN_001fa958();
        FUN_00351d18();
        FUN_0036b118();
        *unaff_x20 = l5;
        FUN_00084234(unaff_x30);
        return;
    }
    long l8 = 0;
    word_t *pv = (word_t *)(l6 + 0x40);
    FUN_00077724(*pv);
    ulong u9 = extraout_x10 & extraout_x8;
    if (u9 == 0) goto advance;
    for (;;) {
        r = FUN_0034cb24();
        ulong u10 = extraout_x8_00;
        for (;;) {
            u10 = u10 | l8 << 6;
            word_t u2 = *(word_t *)(l5 + 0x18);
            FUN_0034fbc4(*(word_t *)(l6 + 0x30), r_lo, r_hi, *(word_t *)(l5 + 0x10));
            FUN_0035bc70(extraout_x8_02 + *(long *)(extraout_x16 + 0x48) * u10, 1);
            FUN_003537c4(*(word_t *)(l6 + 0x38));
            FUN_0035bc70(extraout_x8_03 + *(long *)(extraout_x16_00 + 0x48) * u10, 1, u2);
            if (u9 != 0) break;
advance:
            do {
                long l1 = l8 + 1;
                if (SCARRY8(l8, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1fca54);
                }
                if ((long)(extraout_x9 + 0x3fU >> 6) <= l1) {
                    FUN_0034a604();
                    if (extraout_w9 < 6) {
                        FUN_00354948();
                        *pv = extraout_x8_04;
                    } else {
                        r = FUN_0034e298();
                        FUN_001b5474(r_lo, r_hi, pv);
                    }
                    *(word_t *)(l6 + 0x10) = 0;
                    FUN_00357da4();
                    FUN_00084234(unaff_x30);
                    return;
                }
                l8 = l8 + 1;
            } while (pv[l1] == 0);
            r = FUN_0034bdbc();
            u9 = extraout_x10_00 & extraout_x9_00;
            u10 = extraout_x8_01;
            l8 = l1;
        }
    }
}

/* FUN_001fca54 @ 0x001fca54   (est. cl4_sched_ctx_init)
 * Ghidra: void FUN_001fca54(undefined8 *param_1, undefined8 param_2)
 * Initializes a scheduler context: stores param_2 into *param_1 and runs the
 * init hook FUN_0034e830.
 * Confidence: low
 * Notes: store + FUN_0034e830. */
void cl4_sched_ctx_init(word_t *out, word_t v)
{
    *out = v;
    FUN_0034e830();
}

/* FUN_001fca70 @ 0x001fca70   (est. thunk_FUN_001fca54) */
/* Ghidra: void thunk_FUN_001fca54(undefined8 *param_1, undefined8 param_2) — alias of
 *   FUN_001fca54. Confidence: low */
void thunk_FUN_001fca54(word_t *out, word_t v)
{
    *out = v;
    FUN_0034e830();
}

/* FUN_001fca74 @ 0x001fca74   (est. cl4_sched_dispatch_all)
 * Ghidra: void FUN_001fca74(...7 args)
 * Dispatches every slot in a scheduler set: walks the bitmap and applies the op
 * to each entry via the owner methods, checking the preemption flag
 * (unaff_x21) to break early, then finalizes.
 * Confidence: low
 * Notes: LZCOUNT bit scan; method +0x10/+0x20; SoftwareBreakpoint overflow;
 *   preemption break on unaff_x21. */
void cl4_sched_dispatch_all(word_t a, word_t b, long set, word_t d, word_t e, word_t f, word_t g)
{
    FUN_00353cfc();
    FUN_003509c8(f);
    (*DAT_00658c00)(*(word_t *)(extraout_x16 + 0x40));
    FUN_000aa4ec();
    FUN_0035196c();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003490ec();
    FUN_0007c028();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_00348f38();
    uint128_t r = FUN_003516cc();
    FUN_0031b524(r_lo, r_hi, f, g);
    FUN_003515a8();
    word_t u2 = FUN_001fa18c();
    FUN_00077724(*(word_t *)(set + 0x40));
    local_8 = extraout_x10 & extraout_x8_01;
    long l4 = 0;
    for (;;) {
        if (local_8 == 0) {
            long l6;
            do {
                l6 = l4 + 1;
                if (SCARRY8(l4, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1fccf0);
                }
                if ((long)(extraout_x9 + 0x3fU >> 6) <= l6) goto done;
                l4 = l4 + 1;
            } while (((word_t *)(set + 0x40))[l6] == 0);
            word_t u3 = FUN_0034bdbc();
            local_8 = extraout_x10_01 & extraout_x9_00;
            u5 = extraout_x8_03;
        } else {
            word_t u3 = FUN_00354ff4();
            u5 = extraout_x8_02;
            l6 = l4;
            local_8 = extraout_x10_00;
        }
        FUN_00353c24(*(word_t *)(extraout_x16_01 + 0x10), u3,
                     *(long *)(set + 0x38) + *(long *)(extraout_x16_01 + 0x48) * (u5 | l6 << 6));
        (*extraout_x8_04)();
        r = FUN_00350aa0(*(word_t *)(extraout_x16_00 + 0x10));
        (*extraout_x8_05)(r_lo, r_hi, d);
        FUN_00356248();
        (*extraout_x9_01)();
        if (unaff_x21 != 0) break;   /* preemption break */
        FUN_003578b4();
        FUN_00351384();
        (*extraout_x8_06)();
        FUN_0034db68();
        FUN_001f0700();
        l4 = l6;
    }
    FUN_0036b118(u2);
    FUN_00351924();
    FUN_003511a8();
    (*extraout_x8_07)();
    FUN_003578b4();
    FUN_00351384();
    (*extraout_x8_08)();
done:
    word_t u3 = FUN_003567d4(u2);
    FUN_00353d14(u3, u2);
}

/* FUN_001fccf8 @ 0x001fccf8   (est. cl4_sched_set_state_field)
 * Ghidra: void FUN_001fccf8(void)
 * Sets a scheduler state field: resolves the context, dispatches through the
 * method at +0x20 and writes unaff_x21 into the field at +0x24 of the resolved
 * layout.
 * Confidence: low
 * Notes: FUN_0031b6bc layout; method +0x20; store at +0x24. */
void cl4_sched_set_state_field(void)
{
    word_t u1 = FUN_0034b85c();
    FUN_0034b07c(u1, u1);
    (**(code **)(extraout_x16 + 0x20))(extraout_x8);
    FUN_0034e70c();
    long l2 = FUN_0031b6bc();
    *(word_t *)(extraout_x8 + *(int *)(l2 + 0x24)) = unaff_x21;
}

/* FUN_001fcd54 @ 0x001fcd54   (est. cl4_sched_get_state_flag)
 * Ghidra: uint FUN_001fcd54(void)
 * Returns the low bit of the scheduler state flag (via FUN_001fcefc).
 * Confidence: low
 * Notes: FUN_0031b6bc; FUN_001fcefc flag. */
uint cl4_sched_get_state_flag(void)
{
    FUN_0035098c();
    FUN_0034d024();
    FUN_0031b6bc();
    return FUN_001fcefc() & 1;
}

/* FUN_001fcdbc @ 0x001fcdbc   (est. cl4_sched_buffer_compare)
 * Ghidra: bool FUN_001fcdbc(long param_1, char *param_2, char *param_3)
 * Compares a byte buffer (param_2..param_3) against the string stored in the
 * scheduler object (bytes at +0x20, count at +0x10); Swift-style bounds-checked
 * element comparison; panics on invalid buffer ranges.
 * Confidence: low
 * Notes: strings s_Index_out_of_range / s_Swift_ContiguousArrayBuffer /
 *   s_Swift_UnsafeRawBufferPointer; noreturn panic on bounds errors. */
bool cl4_sched_buffer_compare(long obj, char *a, char *b)
{
    ulong i = 0;
    do {
        char ca; bool at_end;
        if (a == (char *)0x0) {
            ca = '\0';
            at_end = true;
        } else {
            if (b == (char *)0x0) {
                FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, &DAT_005be7c0, 0, 2,
                             s_Swift_UnsafeRawBufferPointer_swi_005cde40, 0x22, 2, 0x4f9, 1);
            }
            if (a == b) {
                ca = '\0';
                at_end = true;
                a = b;
            } else {
                if (b <= a) {
                    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, &DAT_005be7c0, 0, 2,
                                 s_Swift_UnsafeRawBufferPointer_swi_005cde40, 0x22, 2, 0x4fc, 1);
                }
                at_end = false;
                ca = *a;
                a = a + 1;
            }
        }
        ulong u6 = *(ulong *)(obj + 0x10);
        char cb; ulong i2;
        if (i == u6) {
            cb = '\0';
            i2 = i;
        } else {
            if (u6 <= i) {
                FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, s_Index_out_of_range_005cd940, 0x12, 2,
                             s_Swift_ContiguousArrayBuffer_swif_005cd960, 0x21, 2, 0x2b4, 1);
            }
            cb = *(char *)(obj + 0x20 + i);
            i2 = i + 1;
        }
        bool eq = (i == u6);
        if (at_end) {
            return eq;
        }
        i = i2;
        if (eq || ca != cb) {
            return false;
        }
    } while (true);
}

/* FUN_001fcefc @ 0x001fcefc   (est. cl4_sched_flag_cefc) */
/* Ghidra: void FUN_001fcefc(void) — alias of FUN_00286b20. Confidence: low */
void cl4_sched_flag_cefc(void) { FUN_00286b20(); }

/* FUN_001fcf3c @ 0x001fcf3c   (est. cl4_sched_run_queue_drain2)
 * Ghidra: void FUN_001fcf3c(void)
 * Drains a scheduler run queue: acquires the queue, dispatches each entry via
 * the owner methods, and runs the per-entry teardown/hash/requeue loop until the
 * queue is empty.
 * Confidence: low
 * Notes: DAT_00658c00; FUN_001fd1c0; thunk_FUN_002298d4; loop with FUN_001fd568
 *   check + FUN_001fff64/FUN_001ffc20 per-entry steps. */
void cl4_sched_run_queue_drain2(void)
{
    FUN_0008e518();
    FUN_0008409c();
    word_t u3 = *(word_t *)(extraout_x1 + 0x10);
    long l1 = *(long *)(extraout_x1 + 0x18);
    FUN_0034e0d4();
    FUN_0031b704();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    uint128_t r = FUN_00348b94(l1);
    FUN_00377824(r_lo, r_hi, u3);
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    r = FUN_0034a760();
    FUN_003504e8(r_lo, r_hi, 0x66bdd0);
    FUN_0031090c();
    FUN_00348d64();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b460();
    FUN_001fd1c0();
    thunk_FUN_002298d4();
    FUN_0034b3e8();
    (**(code **)(extraout_x16_00 + 0x10))(l1);
    long l4 = (long)*(int *)(unaff_x23 + 0x24);
    FUN_001fe7cc(l1 + l4);
    for (;;) {
        FUN_001fe9a8(unaff_x19);
        ulong u2 = FUN_001fd568(l1 + l4);
        code *pc = *(code **)(extraout_x16 + 8);
        FUN_00356ac4();
        u3 = (*pc)();
        if ((u2 & 1) != 0) break;
        FUN_001fff64(local_40, l1 + l4, unaff_x19);
        FUN_003567ec();
        (*extraout_x8)();
        FUN_00350ea4(l1 + l4);
        FUN_001ffc20();
        FUN_003505e8();
        (*pc)();
        FUN_00352c8c();
        u3 = FUN_0031945c();
        FUN_00350c20(u3, unaff_x21);
        (*extraout_x8_00)();
        FUN_00353bf4();
        FUN_003508cc();
        (*extraout_x8_01)();
    }
    FUN_00351630(u3, unaff_x23);
    (*extraout_x8_02)();
    FUN_0008e500(unaff_x30);
}

/* FUN_001fd1c0 @ 0x001fd1c0   (est. cl4_sched_queue_walk_dispatch)
 * Ghidra: void FUN_001fd1c0(...3 args)
 * Walks a scheduler queue and dispatches each entry: takes the queue object,
 * iterates until empty, running the per-entry op (FUN_001fea40) and the teardown
 * hooks, with a SoftwareBreakpoint overflow guard.
 * Confidence: low
 * Notes: FUN_00377824 queue; SoftwareBreakpoint overflow; method +8/+0x10. */
void cl4_sched_queue_walk_dispatch(word_t a, word_t b, word_t c)
{
    long l2 = FUN_0008e518();
    word_t u6 = *(word_t *)(l2 + 0x18);
    FUN_0034c920();
    FUN_00377824();
    FUN_00348e00();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aab0();
    FUN_00349c70();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003497b4();
    FUN_00350b18(0xff);
    word_t u3 = FUN_00377824();
    FUN_000dbd0c();
    FUN_003511f0();
    FUN_00377bec();
    word_t u4 = FUN_00350c98();
    u4 = FUN_00310e08(u4, u3);
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b460();
    long l12 = *(long *)(unaff_x20 + *(int *)(l2 + 0x24));
    long l11 = *(long *)(l12 + 0x10);
    FUN_0036b270(l12);
    if (l11 != 0) {
        code *pc5 = (code *)FUN_00319628(u6);
        FUN_0034c258();
        u6 = FUN_00377bec();
        code *pc7 = (code *)FUN_00027788();
        long l11 = 0;
        do {
            uint128_t r = FUN_00351648(u3);
            FUN_001fea40(r_lo, r_hi, u3, c);
            FUN_0034ef88();
            word_t u8 = FUN_0031b71c();
            word_t u9 = FUN_00348a50();
            FUN_00376820(u9, u8);
            FUN_0034887c();
            u9 = FUN_00355958();
            FUN_001e7664(u9, u8);
            FUN_003545a0();
            thunk_FUN_0026c274(l2);
            FUN_00357b54(local_30);
            FUN_00351300();
            (*pc5)();
            FUN_00354ab0();
            FUN_003507c8();
            (*extraout_x8_01)();
            u8 = FUN_00352fe8();
            (*extraout_x8_02)(u8, u4);
            long l10 = (*pc7)(unaff_x21, u6);
            FUN_003507d4(*(word_t *)(extraout_x16 + 8));
            (*extraout_x8_03)();
            bool overflow = SCARRY8(l11, l10);
            l11 = l11 + l10;
            if (overflow) {   /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1fd478);
            }
        } while (*(long *)(l12 + 0x10) != 0);
    }
    FUN_0036b118(l12);
    word_t u6b = FUN_00353100();
    FUN_0008e500(u6b, *(word_t *)(extraout_x8_00 + 0x58));
}

/* FUN_001fd4f4 @ 0x001fd4f4   (est. cl4_sched_dispatch_frame)
 * Ghidra: void FUN_001fd4f4(void)
 * Dispatches a scheduler frame: stores the context, resolves the layout and
 * invokes the method at +0x20 over the frame.
 * Confidence: low
 * Notes: FUN_0031b704 layout; method +0x20; jumptable warning. */
void cl4_sched_dispatch_frame(void)
{
    word_t u2 = FUN_0034b85c();
    *extraout_x8 = u2;
    FUN_0034d024();
    long l3 = FUN_0031b704();
    int i1 = *(int *)(l3 + 0x24);
    FUN_00348d94();
    FUN_00350968();
    FUN_00377824();
    FUN_0034ad10();
    /* WARNING: could not recover jumptable at 0x1fd564; indirect jump as call */
    (**(code **)(extraout_x16 + 0x20))((long)extraout_x8 + (long)i1);
}

/* FUN_001fd568 @ 0x001fd568   (est. cl4_sched_empty_or_drain)
 * Ghidra: void FUN_001fd568(void)
 * Returns whether a scheduler queue is empty/drained: resolves the layout and
 * compares the two queue heads via FUN_0034cfd4; returns the low bit.
 * Confidence: low
 * Notes: FUN_0031b704 layout; FUN_0034cfd4 compare. */
void cl4_sched_empty_or_drain(void)
{
    FUN_00084220();
    FUN_00349fcc();
    word_t u3 = FUN_0034c108();
    FUN_00377824(u3, in_x3);
    FUN_0034e70c();
    long l4 = FUN_0031b704();
    int i1 = *(int *)(l4 + 0x24);
    FUN_0034ff3c();
    FUN_00377bec();
    FUN_00349fe0();
    FUN_0034cfd4(unaff_x22 + i1, unaff_x21 + i1);
    uint u2 = (*extraout_x8)();
    FUN_00084234(u2 & 1, unaff_x30);
}

/* FUN_001fd5f0 @ 0x001fd5f0   (est. cl4_sched_op_prep5)
 * Ghidra: void FUN_001fd5f0(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Five-arg scheduler op prep: resolves the op (FUN_0031945c), forwards two
 * context fields and runs the queue hook.
 * Confidence: low
 * Notes: FUN_0031945c; FUN_00377824; FUN_00351c88. */
void cl4_sched_op_prep5(word_t a, word_t b, word_t c)
{
    FUN_000867ec();
    code *pc = (code *)FUN_0031945c(c);
    FUN_00349748(pc, *(word_t *)(unaff_x21 + 0x18), *(word_t *)(unaff_x21 + 0x10));
    word_t u2 = FUN_00377824();
    FUN_00351c88(u2, u2);
    (*pc)();
}

/* FUN_001fd668 @ 0x001fd668   (est. cl4_sched_hash_mix)
 * Ghidra: void FUN_001fd668(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Scheduler hash mix: preps param_3, mixes a key byte with a reversed string
 * constant and finalizes the hash.
 * Confidence: low
 * Notes: s_uespemos... string; FUN_0034d264 key mix; FUN_001a8564. */
void cl4_sched_hash_mix(word_t a, word_t b, word_t c)
{
    FUN_0034a4a4(c);
    byte b1 = FUN_003552f0();
    FUN_0034d264(b1, s_uespemosmodnarodarenegylsetybdet_004e7a30._16_8_,
                 b1 ^ (byte)s_uespemosmodnarodarenegylsetybdet_004e7a30._0_8_);
    (*extraout_x8)();
    FUN_001a8564();
}

/* FUN_001fd6f0 @ 0x001fd6f0   (est. cl4_sched_empty_or_drain_b)
 * Ghidra: void FUN_001fd6f0(void)
 * Empty/drain check variant of FUN_001fd568 (uses FUN_0035044c).
 * Confidence: low
 * Notes: mirror of FUN_001fd568. */
void cl4_sched_empty_or_drain_b(void)
{
    FUN_00084220();
    FUN_00349fcc();
    word_t u3 = FUN_0034c108();
    FUN_00377824(u3, in_x3);
    FUN_0034e70c();
    long l4 = FUN_0031b704();
    int i1 = *(int *)(l4 + 0x24);
    FUN_0034ff3c();
    FUN_00377bec();
    FUN_0035044c();
    FUN_0034cfd4(unaff_x22 + i1, unaff_x21 + i1);
    uint u2 = (*extraout_x8)();
    FUN_00084234(u2 & 1, unaff_x30);
}

/* FUN_001fd77c @ 0x001fd77c   (est. cl4_sched_debug_string)
 * Ghidra: void FUN_001fd77c(void)
 * Builds and releases a scheduler debug string (Swift-style string construction
 * with "<base:" and "rangeOffset" substrings), handling PAC-tagged buffer
 * objects (bits 61/29) and freeing each intermediate through FUN_003a25d4.
 * Confidence: low
 * Notes: strings s_<base:_005cf420 / s___rangeOffset__005cf428; heavy PAC
 *   pointer-tag checks; FUN_003a25d4 frees; large. */
void cl4_sched_debug_string(void)
{
    uint128_t r7 = FUN_0008e518();
    void ***p5 = r7_lo;
    FUN_00349748(p5, p5[3], p5[2]);
    FUN_00377824();
    FUN_00348ce8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0006e778(0x1b);
    uint128_t r8 = FUN_0035a354();
    local_10 = r8_lo;
    FUN_00353e14(s_<base:_005cf420);
    uint128_t r9 = FUN_001a89a8();
    ulong u3 = r9_hi;
    FUN_0034b824(unaff_x28 & 0xffffffffffff);
    void ***p4 = unaff_x20;
    if ((extraout_x8 == 0) &&
        (((unaff_x28 & ((ulong)unaff_x20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        u2 = FUN_003a25d4();
    } else {
        if (((ulong)unaff_x20 >> 0x3d & 1) == 0) {
            in_ZR = (u3 & 0x2000000000000000) == 0;
        } else if ((u3 >> 0x3d & 1) != 0) {
            FUN_00351e90();
            FUN_00351b2c();
            r9 = FUN_0034b7c8();
            if (!(bool)in_ZR) {
                FUN_003a25d4();
                u2 = FUN_003a25d4(u3);
                goto s1;
            }
        }
        FUN_000e72b0();
        FUN_00354b98();
        FUN_002a4c98();
        u2 = FUN_003a25d4(u3);
        r9_hi = r8_hi;
        r9_lo = local_10;
        p4 = &local_10;
    }
s1:
    void ***p10 = r9_hi;
    local_10 = r9_lo;
    void **pp = local_10;
    FUN_00356260(u2, (long)unaff_x20 + (long)*(int *)((long)p5 + 0x24));
    (*extraout_x9)();
    FUN_00350630();
    FUN_001c050c();
    FUN_00356e28();
    FUN_0034eb74((ulong)pp & 0xffffffffffff);
    if ((extraout_x8_00 == 0) &&
        ((((ulong)pp & ((ulong)p10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(p10);
        local_10 = (void ***)(extraout_x16 + 0x10);
    } else {
        p5 = (void ***)((ulong)unaff_x22 >> 0x38 & 0xf);
        if (((ulong)p10 >> 0x3d & 1) == 0) {
            FUN_00356798();
            void ***p6 = extraout_x8_01;
            if (!(bool)in_ZR) {
                p6 = p5;
            }
        } else if (((ulong)unaff_x22 >> 0x3d & 1) == 0) {
            void ***p6 = (void ***)((ulong)(extraout_x16 + 0x10) & 0xffffffffffff);
        } else {
            FUN_0034fec0();
            FUN_0034a148();
            void ***p6 = p5;
            if (!(bool)in_ZR) {
                FUN_00351e08();
                FUN_003a25d4(p10);
                FUN_003a25d4();
                local_10 = p4;
                unaff_x22 = unaff_x20;
                goto s2;
            }
        }
        p4 = &local_10;
        FUN_0034fd5c();
        FUN_002a4c98();
        FUN_003a25d4();
        p5 = p6;
        unaff_x22 = p10;
    }
s2:
    pp = local_10;
    FUN_001a89a8(s___rangeOffset__005cf428, 0xf, 1);
    FUN_00352c74();
    FUN_0034c094((ulong)pp & 0xffffffffffff);
    if ((extraout_x8_02 == 0) &&
        ((((ulong)pp & ((ulong)unaff_x22 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        r9 = FUN_003a25d4(unaff_x22);
        local_10 = p10;
    } else {
        if (((ulong)unaff_x22 >> 0x3d & 1) == 0) {
            FUN_0034a618();
        } else if (((ulong)p5 >> 0x3d & 1) != 0) {
            FUN_00351384();
            FUN_00349c98();
            if (!(bool)in_ZR) {
                FUN_00351e08();
                FUN_003a25d4(unaff_x22);
                r9 = FUN_003a25d4(p5);
                local_10 = p4;
                p5 = unaff_x20;
                goto s3;
            }
        }
        p4 = &local_10;
        FUN_0034c9c8();
        FUN_002a4c98();
        r9 = FUN_003a25d4(p5);
        p5 = unaff_x22;
    }
s3:
    pp = local_10;
    FUN_00356340(r9_lo, r9_hi, *unaff_x20);
    FUN_002364dc();
    FUN_00354a00();
    FUN_0034b18c();
    if ((extraout_x8_03 == 0) &&
        ((((ulong)pp & ((ulong)p5 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(p5);
        local_10 = unaff_x22;
    } else {
        if (((ulong)p5 >> 0x3d & 1) == 0) {
            FUN_0034c3a0();
        } else if (((ulong)unaff_x20 >> 0x3d & 1) != 0) {
            FUN_0034e52c();
            FUN_0034a390();
            if (!(bool)in_ZR) {
                FUN_00352c58();
                FUN_003a25d4(unaff_x20);
                unaff_x20 = (void ***)pp;
                local_10 = p4;
                goto s4;
            }
        }
        FUN_0034ef38();
        FUN_002a4c98();
        FUN_003a25d4(unaff_x20);
        unaff_x20 = p5;
    }
s4:
    pp = local_10;
    FUN_00350744(&DAT_005cf438);
    FUN_001a89a8();
    FUN_00349dcc();
    if ((extraout_x8_04 == 0) &&
        ((((ulong)pp & ((ulong)unaff_x20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(unaff_x20);
    } else {
        if (((ulong)unaff_x20 >> 0x3d & 1) == 0) {
            FUN_0034a618();
        } else if (((ulong)p5 >> 0x3d & 1) != 0) {
            FUN_003510b8();
            FUN_00349c98();
            if (!(bool)in_ZR) {
                FUN_0034eb54();
                FUN_003a25d4();
                FUN_003a25d4(p5);
                goto s5;
            }
        }
        FUN_0034c9c8();
        FUN_002a4c98();
        FUN_003a25d4(p5);
    }
s5:
    r9 = FUN_00350560();
    FUN_0008e500(r9_lo, r9_hi, r7_hi);
}

/* FUN_001fdb5c @ 0x001fdb5c   (est. cl4_sched_desc_build)
 * Ghidra: undefined1 FUN_001fdb5c(void)
 * Builds a scheduler descriptor: resolves the context fields, runs the layout
 * prep and constructs a byte descriptor via FUN_001d88fc.
 * Confidence: low
 * Notes: FUN_0031b704 layout; FUN_001fdc74; FUN_001d88fc build. */
uint8_t cl4_sched_desc_build(void)
{
    FUN_0008409c();
    word_t u3 = *(word_t *)(extraout_x1 + 0x18);
    word_t u2 = *(word_t *)(extraout_x1 + 0x10);
    word_t u1 = FUN_0031b704(0xff, u2, *(word_t *)(extraout_x1 + 0x18));
    FUN_00310d68(0xff, u1);
    FUN_00352efc();
    FUN_00310d68();
    FUN_00348ce8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_00084180();
    FUN_001fdc74();
    local_60 = u2;
    uStack_58 = u3;
    FUN_0035401c();
    FUN_001d88fc(&local_41, FUN_0031b734, auStack_70);
    FUN_00351384(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8)();
    return local_41;
}

/* FUN_001fdc74 @ 0x001fdc74   (est. cl4_sched_queue_run_loop)
 * Ghidra: void FUN_001fdc74(void)
 * Runs the scheduler queue loop: walks the queue and dispatches each entry
 * through the owner methods, checking the drain condition (FUN_003524b0/
 * FUN_00350884) and requeueing or finalizing per-entry.
 * Confidence: low
 * Notes: heavy DAT_00658c00 chain; method +0x20; FUN_00377bec; loop with
 *   SoftwareBreakpoint-safe structure. */
void cl4_sched_queue_run_loop(void)
{
    uint128_t r = FUN_0008e518();
    FUN_00353b70();
    long l1 = *(long *)(extraout_x1 + 0x10);
    word_t u7 = *(word_t *)(extraout_x1 + 0x18);
    FUN_0034cae8();
    FUN_00350878();
    FUN_00377824();
    FUN_00348d64();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_00350428();
    FUN_003509a4();
    FUN_0034ce98();
    word_t u3 = FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034d888();
    FUN_0035298c();
    FUN_00310d68();
    FUN_0034f554();
    FUN_00310d68();
    FUN_003490b8(&stack0x00000010);
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_003499c8();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_003509a4();
    FUN_003507e0();
    FUN_00351e3c();
    FUN_00377bec();
    FUN_0034e6fc();
    word_t *pv = (word_t *)FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_00350428();
    FUN_0035041c();
    FUN_003594bc();
    FUN_003722e4(0xff);
    FUN_0034e130();
    word_t u5 = FUN_00310d68();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_00348b5c();
    (*DAT_00658c00)();
    FUN_0034b87c();
    word_t u9 = *(word_t *)(unaff_x20 + *(int *)(r_hi + 0x24));
    FUN_0036b270(u9);
    FUN_00350768(0);
    word_t u6 = FUN_0031b71c();
    thunk_FUN_00200b38(auStack_28);
    FUN_0036b118(u9);
    FUN_0031b760(0, u6, 0x66d5d8);
    FUN_00200bd0(local_20);
    uint128_t r2 = FUN_003504e8();
    u6 = FUN_0031b778(r2_lo, r2_hi, 0x66d5d8);
    FUN_00354128(extraout_x16 + 0x20);
    FUN_00353360(extraout_x16 + 8);
    FUN_00353130();
    FUN_00354ac8(extraout_x8_02 + 8);
    bool b2 = true;
    for (;;) {
        FUN_00200bf4(uStack_50, u6);
        FUN_003561ac();
        r2 = FUN_003505e8();
        (*extraout_x8_03)(r2_lo, r2_hi, u5);
        FUN_0034aa54();
        if ((bool)in_ZR) {
            FUN_0036b118(local_20[0]);
            if (b2) {
                FUN_0031b704(0, l1, u7);
                FUN_00351d24();
                FUN_00350774();
                FUN_000839d8();
                FUN_003504e8();
                FUN_00356e34();
                r = FUN_00352c68();
            } else {
                FUN_0031b704(0xff, l1, u7);
                FUN_00352efc();
                FUN_00356e34();
                u7 = FUN_00355e38();
                r_hi = 1;
                r_lo = u7;
            }
            FUN_000839d8(r_lo, r_hi, 1);
            FUN_0008e500(unaff_x30);
            return;
        }
        (**(code **)(extraout_x16_00 + 0x20))(extraout_x8_00, unaff_x26 + *(int *)(l1 + 0x30), pv);
        FUN_00352eb4(u7);
        FUN_0035242c();
        FUN_003517cc();
        (*extraout_x9)();
        FUN_00354d50();
        FUN_003514e8();
        (*extraout_x8_04)();
        FUN_0034de8c();
        r2 = FUN_00350630();
        FUN_00377bec(r2_lo, r2_hi, u3);
        FUN_0031b0bc();
        FUN_00351f7c();
        FUN_003517cc(r_lo);
        (*extraout_x9_00)();
        FUN_00355eec();
        FUN_003504c4();
        (*extraout_x8_05)();
        r2 = FUN_003524b0();
        FUN_00350884(r2_lo, r2_hi, unaff_x24);
        if (!(bool)in_ZR) {
            FUN_00356768();
            code *pc = (code *)*pv;
            FUN_00353e44();
            FUN_0034edd8();
            (*pc)();
            FUN_0035463c();
            FUN_0034ef78();
            (*pc)();
            r2 = FUN_003524b0();
            FUN_00350884(r2_lo, r2_hi, unaff_x23);
            if (!(bool)in_ZR) {
                FUN_0036b118(local_20[0]);
                FUN_0035748c(&stack0x00000000);
                r = FUN_003507e0();
                (*extraout_x8_08)(r_lo, r_hi, unaff_x23);
                FUN_00357338(&stack0x00000018);
                FUN_003508cc();
                FUN_0035063c();
                FUN_001fd4f4();
                FUN_0034bec4();
                FUN_0031b704();
                FUN_00352c68();
                FUN_00350774();
                FUN_000839d8();
                FUN_003504e8();
                FUN_00356e34();
                r = FUN_00352c68();
                FUN_000839d8(r_lo, r_hi, 1);
                FUN_0008e500(unaff_x30);
                return;
            }
            u9 = FUN_0034f9ec(&stack0x00000028);
            (*extraout_x8_06)(u9, unaff_x24);
            continue;
        }
        FUN_003510d0(&stack0x00000008);
        (*extraout_x8_07)(unaff_x25, local_f0);
        b2 = false;
    }
}

/* FUN_001fe218 @ 0x001fe218   (est. cl4_sched_op_guard_check)
 * Ghidra: void FUN_001fe218(...3 args)
 * Guard/validation op for a scheduler entry: resolves the layout, checks the
 * entry state (FUN_001fd568), and on mismatch runs the teardown+requeue path,
 * else the drain tail; returns the success bit.
 * Confidence: low
 * Notes: FUN_0031b704 layout; FUN_001fd568 check; method +0x10; FUN_0034ad40. */
void cl4_sched_op_guard_check(word_t a, word_t b, word_t c)
{
    FUN_0008e518();
    word_t u2 = FUN_0031b704(0);
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b6f4();
    word_t u3 = FUN_00310d68(0xff, u2);
    FUN_0034ce88();
    FUN_003515b4();
    FUN_003722e4();
    FUN_00348fd8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0034998c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_00348a80();
    (*DAT_00658c00)();
    FUN_0034c2d8();
    FUN_0034e68c();
    FUN_000839d8();
    long l5 = (long)*(int *)(unaff_x28 + 0x30);
    code *pc = *(code **)(extraout_x16_00 + 0x10);
    FUN_003539c8();
    (*pc)();
    FUN_0035478c();
    FUN_003505c4(unaff_x25 + l5);
    (*extraout_x9)();
    FUN_0034ad40();
    if ((bool)in_ZR) {
        FUN_0034ad40(unaff_x25 + l5);
        if ((bool)in_ZR) {
            FUN_00351274(*(word_t *)(extraout_x16_00 + 8));
            (*extraout_x8_01)();
            byte b1 = 0;
            goto out;
        }
    } else {
        uint128_t r = FUN_000dbd0c();
        (*pc)(r_lo, r_hi, u3);
        FUN_0034ad40(unaff_x25 + l5);
        if (!(bool)in_ZR) {
            FUN_00354810();
            (*extraout_x9_00)(local_38, unaff_x25 + l5, u2);
            r = FUN_00351354();
            byte b1 = FUN_001fd568(r_lo, r_hi, extraout_x1, c);
            pc = *(code **)(extraout_x16 + 8);
            FUN_00351ec0();
            (*pc)();
            FUN_00351714();
            (*pc)();
            FUN_00351274(*(word_t *)(extraout_x16_00 + 8));
            (*extraout_x8_04)();
            b1 = b1 ^ 1;
            goto out;
        }
        FUN_00351e54();
        FUN_00351714();
        (*extraout_x8_02)();
    }
    FUN_00352420();
    FUN_003510dc();
    (*extraout_x8_03)();
    byte b1 = 1;
out:
    *extraout_x8 = b1 & 1;
    FUN_0008e500(unaff_x30);
}

/* FUN_001fe480 @ 0x001fe480   (est. cl4_sched_queue_walk_apply)
 * Ghidra: void FUN_001fe480(...3 args)
 * Walks a scheduler queue and applies an op to each entry: iterates until empty,
 * running the per-entry op (FUN_001fea40) and the teardown hooks, tracking a
 * running counter through FUN_001e7664.
 * Confidence: low
 * Notes: FUN_00377824 queue; SoftwareBreakpoint-free loop; thunk_FUN_0026c274;
 *   method +8. */
void cl4_sched_queue_walk_apply(word_t a, word_t b, word_t c)
{
    long l2 = FUN_0008e518();
    word_t u10 = *(word_t *)(l2 + 0x10);
    word_t u1 = *(word_t *)(l2 + 0x18);
    FUN_00350798();
    FUN_00354388();
    word_t u3 = FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0d4();
    FUN_0034998c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    FUN_00348f38();
    FUN_00350ed0(0xff);
    word_t u4 = FUN_00377824();
    FUN_0034f594();
    FUN_00377bec();
    word_t u5 = FUN_00350c98();
    u5 = FUN_00310e08(u5, u4);
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b250();
    uint128_t r = FUN_00348b94(u1);
    word_t u6 = FUN_00377824(r_lo, r_hi, u10);
    FUN_00350798();
    word_t u7 = FUN_001a0414();
    local_8 = FUN_001dd1ec(u7, u6);
    long l11 = *(long *)(unaff_x20 + *(int *)(l2 + 0x24));
    local_18 = 0;
    long l12 = *(long *)(l11 + 0x10);
    local_10 = l11;
    FUN_0036b270(l11);
    if (l12 == 0) {
        FUN_0036b118(l11);
    } else {
        code *pc = (code *)FUN_00319628(u1);
        long l12 = 0;
        do {
            r = FUN_0007c1c4(local_78);
            FUN_001fea40(r_lo, r_hi, u4, c);
            local_20 = l12;
            r = FUN_00350720();
            u7 = FUN_0031b71c(r_lo, r_hi, c);
            word_t u9 = FUN_00348a50();
            FUN_00376820(u9, u7);
            FUN_0034887c();
            FUN_001e7664(&local_18, &local_20, u7);
            thunk_FUN_0026c274(l2);
            u7 = FUN_00352a64();
            (*pc)(u7, u10, u1);
            FUN_00356a70();
            FUN_00350518();
            (*extraout_x8_00)();
            FUN_00354ab0();
            (*extraout_x8_01)(local_78, u5);
            FUN_00310d80(0, u6);
            FUN_00350600(u1);
            FUN_00377bec();
            FUN_00356bb0();
            r = FUN_0009e234();
            FUN_001de04c(r_lo, r_hi, u3);
            l12 = local_18;
        } while (local_18 != *(long *)(l11 + 0x10));
        FUN_0036b118(l11);
    }
    FUN_0034dfe4();
    (**(code **)(extraout_x16 + 8))(unaff_x20, l2);
    u10 = FUN_003548b8();
    FUN_0008e500(u10, u1);
}

/* FUN_001fe7cc @ 0x001fe7cc   (est. cl4_sched_op_dispatch7)
 * Ghidra: void FUN_001fe7cc(void)
 * Seven-argument scheduler op dispatch: acquires the queue, checks the empty
 * condition (FUN_001fe95c), and on non-empty runs the per-entry op
 * (FUN_001fea40) and dispatch frame; else drains the queue.
 * Confidence: low
 * Notes: DAT_00658c00; FUN_001fe95c check; FUN_001fea40 op; FUN_001fd4f4 frame. */
void cl4_sched_op_dispatch7(void)
{
    uint128_t r7 = FUN_0008e518();
    long l2 = r7_lo;
    word_t u5 = *(word_t *)(l2 + 0x10);
    word_t u1 = *(word_t *)(l2 + 0x18);
    FUN_0034c54c();
    FUN_00350798();
    FUN_00351220();
    FUN_00377824();
    FUN_00348ce8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b2f8();
    FUN_0035139c(u1);
    word_t u3 = FUN_00377bec();
    uint128_t r8 = FUN_00350488();
    FUN_00310e08(r8_lo, r8_hi, u3);
    FUN_00348cd0();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    word_t u6 = *(word_t *)(unaff_x20 + *(int *)(l2 + 0x24));
    r8 = FUN_003504ac();
    ulong u4 = FUN_001fe95c(r8_lo, r8_hi, u3);
    if ((u4 & 1) != 0) {
        u5 = FUN_00359920(extraout_x8);
        FUN_0008e500(u5, in_stack_00000038);
        FUN_001fe9a8();
        return;
    }
    FUN_0036b270(u6);
    FUN_0034f604(u5);
    FUN_001fea40();
    FUN_0036b118(u6);
    FUN_00350470(*(word_t *)(extraout_x16 + 0x10));
    (*extraout_x8_00)();
    FUN_00351354(*(word_t *)(extraout_x16_00 + 8));
    (*extraout_x8_01)();
    r8 = FUN_00350500(extraout_x8);
    FUN_001fd4f4(r8_lo, r8_hi, u5, u1);
    FUN_0008e500(r7_hi);
}

/* FUN_001fe95c @ 0x001fe95c   (est. cl4_sched_op_empty_check)
 * Ghidra: uint FUN_001fe95c(void)
 * Returns whether the scheduler op is empty: derives the key (FUN_0031b71c),
 * runs the check (FUN_00376820) and returns the low bit of FUN_0019fd10.
 * Confidence: low
 * Notes: FUN_0031b71c key; FUN_0019fd10 check. */
uint cl4_sched_op_empty_check(void)
{
    FUN_00352ddc();
    word_t u2 = FUN_0031b71c();
    word_t u3 = FUN_00348c30();
    FUN_00376820(u3, u2);
    FUN_00355c28();
    return FUN_0019fd10(u2) & 1;
}

/* FUN_001fe9a8 @ 0x001fe9a8   (est. cl4_sched_drain_epilogue)
 * Ghidra: void FUN_001fe9a8(void)
 * Scheduler drain epilogue: resolves the context and runs the queue + dispatch
 * frame helpers to finalize a drain.
 * Confidence: low
 * Notes: FUN_00377824 queue; FUN_001fd4f4 frame; DAT_00658c00. */
void cl4_sched_drain_epilogue(void)
{
    long l2 = FUN_00351cc4();
    word_t u1 = *(word_t *)(l2 + 0x18);
    FUN_00349748();
    FUN_003505c4();
    FUN_00377824();
    FUN_00351f10();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_00351750(u1);
    FUN_0034c2a4();
    (*extraout_x9)();
    FUN_00353c18();
    FUN_00350018();
    FUN_001fd4f4();
}

/* FUN_001fea40 @ 0x001fea40   (est. cl4_sched_per_entry_op)
 * Ghidra: void FUN_001fea40(void)
 * Per-entry scheduler op: resolves the entry, forwards it through the dispatch
 * hook and runs the teardown helper.
 * Confidence: low
 * Notes: FUN_00310e08 resolve; FUN_0007c1c4; FUN_001dc430. */
void cl4_sched_per_entry_op(void)
{
    FUN_003503d0();
    FUN_0034d024();
    uint128_t r = FUN_00310e08();
    FUN_0007c1c4(r_lo, r_hi, r_lo);
    FUN_001dc430();
}

/* FUN_001fea80 @ 0x001fea80   (est. cl4_sched_op_prep7)
 * Ghidra: void FUN_001fea80(long param_1)
 * Seven-arg op prep: resolves the context field and runs the queue + empty-check
 * helpers.
 * Confidence: low
 * Notes: FUN_00377824 queue; FUN_001fe95c check. */
void cl4_sched_op_prep7(long src)
{
    word_t u1 = *(word_t *)(src + 0x18);
    FUN_0034cae8();
    FUN_003510c4();
    FUN_00377824();
    FUN_003513a8(u1);
    uint128_t r = FUN_00377bec();
    FUN_00084174(r_lo, r_hi, r_lo);
    FUN_001fe95c();
}

/* FUN_001feaec @ 0x001feaec   (est. cl4_sched_batch_apply)
 * Ghidra: void FUN_001feaec(...3 args)
 * Batch-applies an op to a scheduler queue: takes the queue pair, and depending
 * on the batch state (FUN_0019c9cc count) either resets (FUN_001ff258) or runs
 * the full per-entry apply loop with counting (FUN_001ff52c/FUN_001ff8fc), with
 * SoftwareBreakpoint overflow guards.
 * Confidence: low
 * Notes: FUN_0031b704 layout; FUN_001ff258/FUN_001ff52c; SoftwareBreakpoint
 *   overflow (0x1ff160/0x1ff174/0x1ff064); noreturn panic. */
void cl4_sched_batch_apply(word_t a, word_t b, long src)
{
    FUN_0008e518();
    long *pv = (long *)FUN_0035a2d0();
    word_t u13 = *(word_t *)(src + 0x18);
    word_t u18 = *(word_t *)(src + 0x18);
    word_t u17 = *(word_t *)(src + 0x10);
    FUN_0034e6ec();
    FUN_00377824();
    FUN_00348e60();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034d89c();
    FUN_003513a8(0xff);
    FUN_00377824();
    FUN_0008e388();
    FUN_003531e4();
    word_t u5 = FUN_00377bec();
    FUN_00350ed0(0xff);
    long l6 = FUN_00310e08();
    FUN_00350920();
    FUN_0034d464();
    (*DAT_00658c00)(*(word_t *)(extraout_x16_00 + 0x40));
    FUN_003493c4();
    FUN_0034acf0();
    (*DAT_00658c00)();
    FUN_0034c074();
    long *pl15 = (long *)(l6 + -8);
    long l11 = *pl15;
    (*DAT_00658c00)(*(word_t *)(l11 + 0x40));
    FUN_003489c0();
    (*DAT_00658c00)();
    FUN_0034a9d4();
    (*DAT_00658c00)();
    FUN_0034dc9c();
    word_t u12 = *(word_t *)(unaff_x20 + *(int *)(unaff_x19 + 0x24));
    FUN_0036b270(u12);
    if (*unaff_x24 < *pv) {
        FUN_00350410();
        FUN_003484e4();
        FUN_003499dc();
    } else {
        local_58 = *pv;
        lStack_50 = *unaff_x24;
        local_40 = u12;
        uint128_t r = FUN_00350798();
        u5 = FUN_0031b71c(r_lo, r_hi, u5);
        FUN_00002534(0x6561e0, &DAT_004e8038);
        word_t u7 = FUN_00348c30();
        FUN_00376820(u7, u5);
        FUN_00351df0(local_20, &local_58);
        FUN_001d9890();
        FUN_0036b118(u12);
        FUN_0034d3e4();
        u12 = FUN_0031b080();
        FUN_0034878c();
        long l8 = FUN_0019c9cc();
        uint8_t u3 = (l8 == 2);
        if (l8 < 2) {
            local_58 = 0;
            FUN_001ff258(pl15, &local_58, u12);
            FUN_0036b118(local_10);
            FUN_00357274();
            FUN_00352eb4();
            FUN_003504a0(local_a8, pl15);
            u5 = (*extraout_x9_01)();
            FUN_00351a98(u5, l6);
            (*extraout_x8_01)();
            FUN_0034bec4();
            l6 = FUN_0031b704();
            int i1 = *(int *)(l6 + 0x24);
            FUN_0034de8c();
            FUN_003507e0();
            FUN_00377bec();
            FUN_0035647c();
            FUN_003518a0((long)pv + (long)i1, (long)unaff_x24 + (long)i1);
            (*extraout_x8_02)();
            FUN_00350bc0(&stack0x00000048);
            FUN_00350b78();
            (*extraout_x8_03)();
            goto out;
        }
        FUN_0034878c();
        FUN_001aeab4(u13, u12);
        FUN_003524b0();
        FUN_0034bffc();
        if ((bool)u3) {
            u5 = 0xa2;
        } else {
            code *pc16 = *(code **)(l11 + 0x20);
            FUN_003567a4();
            FUN_0034b778();
            (*pc16)();
            FUN_000ec044();
            FUN_00355430();
            u7 = FUN_0034e268();
            local_28 = FUN_00376820(u7, u5);
            u5 = FUN_00348990();
            FUN_00376820(u5, u12, &local_28);
            FUN_00358e7c();
            FUN_003526b8(&stack0x00000038);
            FUN_001b3c0c(u12);
            FUN_00349f3c(u13);
            if (!(bool)u3) {
                FUN_003504a0(local_88);
                (*pc16)();
                FUN_00352abc();
                FUN_003553cc();
                FUN_00352d28();
                FUN_003510a0();
                (*extraout_x9)();
                FUN_0034e0c4();
                l8 = FUN_0031b704();
                int i1 = *(int *)(l8 + 0x24);
                int i2 = *(int *)(l6 + 0x24);
                FUN_0034de8c();
                FUN_00350c2c();
                FUN_00377bec();
                pc16 = (code *)FUN_00310cd4();
                FUN_00353c30((long)pv + (long)i1, local_10 + i2);
                long l9 = (*pc16)();
                code *pc14 = *(code **)(extraout_x16 + 8);
                FUN_00350738();
                (*pc14)();
                FUN_003510a0(local_a8, local_88);
                FUN_00353e2c();
                (*extraout_x9_00)();
                FUN_00353bac();
                FUN_00351dcc(local_88, (long)unaff_x24 + (long)*(int *)(extraout_x8 + 0x24));
                long l10 = (*pc16)();
                FUN_003510dc();
                (*pc14)();
                FUN_0022b584(&local_58, u12);
                long l8b = local_58 + -1;
                if (SBORROW8(local_58, 1)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1ff160);
                }
                if (l8b < 1) {
                    FUN_00347d60();
                    /* noreturn */
                }
                pc16 = *(code **)(l11 + 8);
                (*pc16)(local_88, l6);
                u5 = FUN_00359ad4();
                (*pc16)(u5, l6);
                local_40 = 1;
                lStack_38 = l8b;
                FUN_001ff52c(&local_58, &local_40, u12);
                FUN_0036b118(local_10);
                (*DAT_00658c00)();
                u5 = FUN_00355b38();
                *(word_t *)(extraout_x8_00 + -0x18) = u18;
                *(word_t *)(extraout_x8_00 + -0x20) = u17;
                *(long *)(extraout_x8_00 + -0x10) = unaff_x20;
                FUN_0035a1e8(u5, FUN_0031b790);
                FUN_001ff8fc();
                FUN_0036b118(local_48);
                if (SCARRY8(l9, local_30)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1ff174);
                }
                if (SCARRY8(l9 + local_30, l10)) {   /* WARNING: does not return */
                    SoftwareBreakpoint(1, 0x1ff064);
                }
                goto out;
            }
            u5 = 0xa3;
        }
        FUN_003489dc(u5);
        FUN_0034a2f8();
    }
out:
    u5 = FUN_00353100();
    FUN_0008e500(u5, extraout_x16);
    /* noreturn fallthrough in panic path */
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001ff1a4 @ 0x001ff1a4   (est. cl4_sched_buffer_index)
 * Ghidra: undefined1 FUN_001ff1a4(long param_1, long param_2, long param_3, long param_4,
 *   long param_5)
 * Swift UnsafeBufferPointer bounds-checked element access: returns the byte at
 * param_4[param_1] after validating param_1 against the buffer bounds; panics
 * with the appropriate Swift fatal error on out-of-range.
 * Confidence: low
 * Notes: strings s_Swift_UnsafeBufferPointer_swift_005cdc10; noreturn panic
 *   (0x77d/0x75d/0x75e/0x77e codes). */
uint8_t cl4_sched_buffer_index(long i, long lo, long hi, char *base, long len)
{
    word_t code;
    if (i < lo) {
        code = 0x77d;
    } else if (i < hi) {
        if (i < 0) {
            code = 0x75d;
        } else {
            if (i < len) {
                return *(uint8_t *)(base + i);
            }
            code = 0x75e;
        }
    } else {
        code = 0x77e;
    }
    /* WARNING: subroutine does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, &DAT_005be7c0, 0, 2,
                 s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, code, 1);
}

/* FUN_001ff258 @ 0x001ff258   (est. cl4_sched_queue_reset)
 * Ghidra: void FUN_001ff258(void)
 * Resets a scheduler queue: clears the queue state and dispatches the reset
 * through the owner method vectors, then finalizes.
 * Confidence: low
 * Notes: FUN_00377824 queue; method +0x10/+0x20/+8; FUN_0008e500. */
void cl4_sched_queue_reset(void)
{
    uint128_t r9 = FUN_0008e518();
    long l6 = r9_hi;
    long l1 = *(long *)(l6 + 0x10);
    word_t u4 = *(word_t *)(l6 + 0x18);
    word_t u3 = FUN_0034a3c4();
    FUN_003515fc(u3, u4);
    u4 = FUN_00377824();
    FUN_0034b0b4();
    FUN_00355adc();
    FUN_003722e4();
    FUN_00348e60();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003489c0();
    (*DAT_00658c00)();
    FUN_0034c074();
    FUN_0034d130();
    FUN_00377bec();
    FUN_0034e414();
    long l5 = FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b460();
    FUN_003597b4();
    code *pc7 = *(code **)(extraout_x16_00 + 0x10);
    uint128_t r10 = FUN_000b43d0();
    (*pc7)(r10_lo, r10_hi, u4);
    FUN_00359594();
    (*pc7)();
    FUN_0035399c();
    FUN_003508a8();
    FUN_00351f4c();
    (*extraout_x9)();
    int i2 = *(int *)(unaff_x26 + 0x30);
    code *pc8 = *(code **)(extraout_x16_00 + 0x20);
    r10 = FUN_00350c80();
    (*pc8)(r10_lo, r10_hi, u4);
    pc7 = *(code **)(extraout_x16_00 + 8);
    (*pc7)(unaff_x27 + i2, u4);
    FUN_0035a190(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_01)();
    (*pc8)(l1 + *(int *)(l5 + 0x24), unaff_x27 + *(int *)(unaff_x20 + 0x30), u4);
    FUN_003508f0();
    (*pc7)();
    r10 = FUN_003504c4();
    FUN_0028c7d8(r10_lo, r10_hi, l6);
    FUN_00353154();
    FUN_00350b78();
    (*extraout_x8_02)();
    i2 = *(int *)(l6 + 0x28);
    FUN_00356810();
    FUN_00352ecc();
    u4 = FUN_0035949c();
    FUN_00351e3c(u4, r9_lo);
    (*extraout_x8_03)();
    FUN_00350df4();
    r9 = FUN_00348b94();
    FUN_00377824(r9_lo, r9_hi, l1);
    FUN_00349530();
    (**(code **)(extraout_x16_01 + 0x10))(extraout_x8, (code *)(long)i2 + unaff_x20);
    FUN_00351d00();
    (*(code *)(long)i2)();
    FUN_0008e500(unaff_x30);
}

/* FUN_001ff4e0 @ 0x001ff4e0   (est. cl4_sched_bounds_check)
 * Ghidra: void FUN_001ff4e0(long param_1, long param_2, long param_3, long param_4)
 * Bounds check for a scheduler range; panics on out-of-range.
 * Confidence: low
 * Notes: FUN_0035047c/FUN_00354828; noreturn FUN_001afe4c. */
void cl4_sched_bounds_check(long a, long b, long c, long d)
{
    if (a < c) {
        FUN_0035047c();
    } else {
        if (b <= d) {
            FUN_00354828();
            return;
        }
        FUN_0035047c();
    }
    FUN_003480ac();
    /* WARNING: subroutine does not return */
    FUN_001afe4c();
}

/* FUN_001ff52c @ 0x001ff52c   (est. cl4_sched_batch_step)
 * Ghidra: void FUN_001ff52c(void)
 * Steps a scheduler batch: dispatches the batch through the owner method vectors
 * (value + side) and finalizes with the drain hooks.
 * Confidence: low
 * Notes: FUN_00377824 queue; method +0x10/+0x20/+8; FUN_0028c7f0; FUN_0008e500. */
void cl4_sched_batch_step(void)
{
    FUN_0008e518();
    word_t u8 = *(word_t *)(extraout_x1 + 0x10);
    FUN_003499c8();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003497b4();
    word_t u7 = *(word_t *)(extraout_x1_00 + 0x18);
    word_t u2 = FUN_0034c158();
    long l3 = FUN_00377824(u2, u7, u8);
    FUN_0034b0b4();
    FUN_00359398();
    long l4 = FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003490d0();
    (*DAT_00658c00)();
    FUN_0034c2c8();
    FUN_00350470();
    FUN_00352438();
    FUN_00377bec();
    FUN_0034c55c();
    long l5 = FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    int i1 = *(int *)(extraout_x1_00 + 0x24);
    long l6 = *(long *)(l3 + -8);
    code *pc9 = *(code **)(l6 + 0x10);
    uint128_t r = FUN_0009461c();
    (*pc9)(r_lo, r_hi, l3);
    (*pc9)(unaff_x19 + *(int *)(l4 + 0x30), unaff_x20 + i1, l3);
    FUN_00351c4c();
    FUN_003501a8();
    (*extraout_x9)();
    i1 = *(int *)(l4 + 0x30);
    pc9 = *(code **)(l6 + 0x20);
    r = FUN_0035084c();
    (*pc9)(r_lo, r_hi, l3);
    code *pc10 = *(code **)(l6 + 8);
    (*pc10)(unaff_x22 + i1, l3);
    (**(code **)(extraout_x16 + 0x20))();
    (*pc9)(unaff_x26 + *(int *)(l5 + 0x24), unaff_x22 + *(int *)(l4 + 0x30), l3);
    FUN_00350c80();
    (*pc10)();
    r = FUN_00351130();
    FUN_0028c7f0(r_lo, r_hi, extraout_x1_00);
    FUN_00352870();
    FUN_00350ea4();
    (*extraout_x9_00)();
    FUN_00355dd8();
    (*extraout_x9_01)();
    r = FUN_003507d4(*(word_t *)(extraout_x16_00 + 0x10));
    (*extraout_x8_02)(r_lo, r_hi, l5);
    FUN_00350c68(extraout_x8, unaff_x20);
    FUN_001d3fd0();
    FUN_0008e500(unaff_x30);
}

/* FUN_001ff7ec @ 0x001ff7ec   (est. cl4_sched_count_op)
 * Ghidra: void FUN_001ff7ec(void)
 * Counts scheduler entries: acquires the queue, accumulates the count via
 * FUN_00027788 and stores it into the caller slot; SoftwareBreakpoint overflow.
 * Confidence: low
 * Notes: FUN_00377824 queue; SoftwareBreakpoint overflow (0x1ff8fc). */
void cl4_sched_count_op(void)
{
    FUN_0008e518();
    long *pv = (long *)FUN_00352ce0();
    uint128_t r = FUN_00350488();
    FUN_00377824(r_lo, r_hi, in_x3, &DAT_0060e208);
    FUN_00348e00();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034af20();
    long l4 = *pv;
    FUN_00319628();
    FUN_00351184();
    FUN_00077708();
    (*extraout_x9)();
    FUN_0034c6b4();
    FUN_00377bec();
    FUN_00027788();
    FUN_00351ac8();
    FUN_000b4390();
    long l3 = (*extraout_x8_00)();
    FUN_003515cc(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_01)();
    if (!SCARRY8(l4, l3)) {
        *extraout_x8 = l4 + l3;
        FUN_0008e500(unaff_x30);
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x1ff8fc);
}

/* FUN_001ff8fc @ 0x001ff8fc   (est. cl4_sched_run_loop)
 * Ghidra: void FUN_001ff8fc(void)
 * Scheduler run loop: acquires the queue and dispatches each entry through the
 * owner methods, checking the drain condition (FUN_00350884) and breaking early
 * on the preemption flag (unaff_x21); finalizes with the epilogue.
 * Confidence: low
 * Notes: FUN_00377824 queue; method +0x10/+0x20/+8; FUN_00350884 drain check. */
void cl4_sched_run_loop(void)
{
    uint128_t r3 = FUN_00353cfc();
    word_t u1 = in_x3;
    FUN_0007c028();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003493ac();
    FUN_00351fb0();
    uint128_t r4 = FUN_003548d0();
    FUN_00377824(r4_lo, r4_hi, u1);
    FUN_00348fd8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034eb2c();
    FUN_0035113c();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b71c();
    FUN_00349c70();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_00349068();
    FUN_0034c920();
    FUN_00377824();
    FUN_00348d64();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034d3c4();
    (**(code **)(extraout_x16 + 0x10))(extraout_x8, r3_lo, in_x4);
    r4 = FUN_00354d68(*(word_t *)(extraout_x16_01 + 0x10));
    (*extraout_x8_02)(r4_lo, r4_hi, in_x3);
    FUN_00352680(in_x5);
    FUN_00350618();
    (*extraout_x9)();
    FUN_0034b278();
    FUN_000dbd0c();
    u1 = FUN_00377bec();
    code *next = (code *)FUN_000a68f4();
    do {
        (*next)(uStack_28, unaff_x23, u1);
        r4 = FUN_00351330();
        FUN_00350884(r4_lo, r4_hi, unaff_x28);
        if ((bool)in_ZR) {
            FUN_0035336c();
            (*extraout_x8_05)(unaff_x20, unaff_x23);
            goto done;
        }
        FUN_00350e64(*(word_t *)(extraout_x16_00 + 0x20));
        (*extraout_x8_03)();
        FUN_00350a34(unaff_x27);
        (*r3_hi)();
        (**(code **)(extraout_x16_00 + 8))(local_50, unaff_x28);
        if (unaff_x21 != 0) {   /* preemption break */
            FUN_0035336c();
            (*extraout_x8_06)(unaff_x20, unaff_x23);
            (**(code **)(extraout_x16 + 8))(extraout_x8, in_x4);
            goto done;
        }
        (**(code **)(extraout_x16 + 8))(extraout_x8, in_x4);
        r4 = FUN_00350944(*(word_t *)(extraout_x16 + 0x20));
        (*extraout_x8_04)(r4_lo, r4_hi, in_x4);
    } while (true);
done:
    FUN_003567d4();
    FUN_00353d14(unaff_x23);
}

/* FUN_001ffc20 @ 0x001ffc20   (est. cl4_sched_batch_advance)
 * Ghidra: void FUN_001ffc20(void)
 * Advances a scheduler batch: runs the per-entry op (FUN_001fea40), checks the
 * remaining count, and either dispatches the next entry (FUN_001fd4f4) or runs
 * the drain epilogue.
 * Confidence: low
 * Notes: FUN_001fea40 op; SoftwareBreakpoint overflow (0x1fff64); FUN_001fd4f4;
 *   FUN_001fe9a8 drain. */
void cl4_sched_batch_advance(void)
{
    FUN_0008e518();
    FUN_00353a0c();
    word_t u1 = *(word_t *)(extraout_x1 + 0x10);
    word_t u2 = *(word_t *)(extraout_x1 + 0x18);
    FUN_0034c454();
    FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aab0();
    FUN_0034c454();
    FUN_00377824();
    FUN_00348d7c();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_003493c4();
    FUN_0034d244();
    (*DAT_00658c00)();
    FUN_0034ac3c();
    FUN_0034ed78();
    word_t u4 = FUN_00377bec();
    uint128_t r10 = FUN_00350720();
    FUN_00310e08(r10_lo, r10_hi, u4);
    FUN_00348fd8();
    (*DAT_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
    FUN_003493c4();
    FUN_0034cde8();
    (*DAT_00658c00)();
    FUN_0034b87c();
    long l8 = *(long *)(unaff_x20 + *(int *)(unaff_x21 + 0x24));
    FUN_0036b270(l8);
    long l5 = *unaff_x23;
    FUN_00351178();
    FUN_001fea40();
    FUN_0036b118(l8);
    FUN_00352eb4(u2);
    FUN_00352a64();
    FUN_00350c20();
    (*extraout_x9)();
    r10 = FUN_003504e8();
    long l6 = FUN_0031b704(r10_lo, r10_hi, u2);
    int i3 = *(int *)(l6 + 0x24);
    FUN_0034de8c();
    FUN_00358684(u2, u1);
    FUN_00377bec();
    FUN_00353d94();
    FUN_00350878(local_20, (long)unaff_x23 + (long)i3);
    (*extraout_x9_00)();
    FUN_003508cc(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_02)();
    i3 = *(int *)(unaff_x28 + 0x24);
    FUN_0035044c(u4);
    FUN_00351c94(local_20, unaff_x26 + i3);
    ulong u7 = (*extraout_x8_03)();
    code *pc9 = *(code **)(extraout_x16_01 + 8);
    (*pc9)();
    if ((u7 & 1) == 0) {
        FUN_00356224();
        FUN_003507c8();
        (*extraout_x9_01)();
        if (SCARRY8(l5, 1)) {   /* WARNING: does not return */
            SoftwareBreakpoint(1, 0x1fff64);
        }
        if (*(long *)(l8 + 0x10) <= l5 + 1) {
            FUN_001fe9a8(extraout_x8, unaff_x21);
            goto out;
        }
        FUN_0036b270(l8);
        FUN_003545e8();
        FUN_0035136c(l5 + 1);
        FUN_001fea40();
        FUN_0036b118(l8);
        FUN_0034fe80(*(word_t *)(extraout_x16_00 + 0x10));
        (*extraout_x8_04)();
        FUN_0035620c();
        (*pc9)();
        r10 = FUN_00351450(extraout_x8);
        local_20 = r10_hi;
        l5 = r10_lo;
    }
    FUN_001fd4f4(l5, local_20, u1, u2);
out:
    FUN_0008e500(unaff_x30);
}

/* FUN_001fff64 @ 0x001fff64   (est. cl4_sched_batch_advance_b)
 * Ghidra: void FUN_001fff64(void)
 * Batch-advance variant of FUN_001ffc20 (uses FUN_00350518 and a different
 * dispatch hook).
 * Confidence: low
 * Notes: mirror of FUN_001ffc20. */
void cl4_sched_batch_advance_b(void)
{
    FUN_0008e518();
    FUN_00359f48();
    word_t u1 = *(word_t *)(extraout_x1 + 0x10);
    word_t u2 = *(word_t *)(extraout_x1 + 0x18);
    FUN_003525cc();
    FUN_0034df64();
    FUN_00377824();
    word_t u4 = FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034a760();
    FUN_00352f54();
    FUN_0034df64();
    FUN_00377824();
    FUN_0034db68();
    word_t u5 = FUN_00377bec();
    uint128_t r8 = FUN_003504e8();
    FUN_00310e08(r8_lo, r8_hi, u5);
    FUN_00348ce8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    u5 = *(word_t *)(unaff_x20 + *(int *)(unaff_x28 + 0x24));
    FUN_0036b270(u5);
    FUN_00351298(*unaff_x27);
    FUN_001fea40();
    FUN_0036b118(u5);
    FUN_00352eb4(u2);
    r8 = FUN_00350518(local_40);
    (*extraout_x9)(r8_lo, r8_hi, u2);
    FUN_00351384(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_00)();
    FUN_00350318();
    long l6 = FUN_0031b704();
    int i3 = *(int *)(l6 + 0x24);
    FUN_0034de8c();
    r8 = FUN_00351274();
    code *pc7 = (code *)FUN_00377bec(r8_lo, r8_hi, u4);
    FUN_00352ecc();
    u4 = FUN_0035949c();
    FUN_003515fc(u4, (long)unaff_x27 + (long)i3);
    (*extraout_x8_01)();
    FUN_00351a50();
    r8 = FUN_00348b94(u2);
    FUN_00377824(r8_lo, r8_hi, u1);
    FUN_00349530();
    (**(code **)(extraout_x16_00 + 0x10))(extraout_x8, local_40);
    FUN_00351d00();
    (*pc7)();
    FUN_0035313c();
    FUN_0035084c();
    (*extraout_x8_02)();
    FUN_0008e500(unaff_x30);
}

/* FUN_001f2264 @ 0x001f2264   (est. thunk_FUN_0036b270)
 * Ghidra: ulong thunk_FUN_0036b270(ulong param_1)
 * Scheduler object take/retain thunk: for positive refcounts, CAS-increments the
 * reference at *(ptr+8) with the 0x200000000 increment, handling the overflow/
 * negative path via FUN_0039f9e8. Returns the object pointer.
 * Confidence: low
 * Notes: CAS loop on refcount at +8; retain step 0x200000000; FUN_0039f9e8. */
ulong thunk_FUN_0036b270(ulong obj)
{
    if (0 < (long)obj) {
        ulong base = obj & 0xffffffffffffff8;
        long *slot = (long *)(base + 8);
        long cur = *(long *)(base + 8);
        do {
            long next = cur + 0x200000000;
            if (next < 0) {
                if ((int)cur == -1) {
                    return base;
                }
                return FUN_0039f9e8(slot, cur, 1);
            }
            bool changed = (*slot != cur);
            cur = *slot;
        } while (changed);
        *slot = next;
    }
    return obj;
}

/* FUN_001f2290 @ 0x001f2290   (est. thunk_FUN_00355354)
 * Ghidra: undefined1 [16] thunk_FUN_00355354(long param_1)
 * Returns the scheduler set header as a 16-byte descriptor: {1<<bits, class}.
 * Confidence: low
 * Notes: auVar1 = {1L << (byte@+0x20 & 0x3f), uint@+0x24}. */
cl4_desc_t thunk_FUN_00355354(long set)
{
    cl4_desc_t r;
    r.hi = 1L << ((ulong)*(byte *)(set + 0x20) & 0x3f);
    r.lo = *(uint *)(set + 0x24);
    return r;
}

/* FUN_001f2298 @ 0x001f2298   (est. cl4_sched_slot_dispatch_v)
 * Ghidra: void FUN_001f2298(undefined8 param_1, ulong param_2, int param_3, long param_4,
 *   long param_5)
 * Dispatches a validated scheduler value slot via +0x10 (mirror of FUN_001fb44c);
 * panics on invalid index/class.
 * Confidence: low
 * Notes: bitmap+class validation; method +0x10; noreturn panic. */
void cl4_sched_slot_dispatch_v(word_t a, ulong idx, int cls, long set, long owner)
{
    if ((((-1 < (long)idx) && (idx >> ((ulong)*(byte *)(set + 0x20) & 0x3f) == 0)) &&
        ((*(ulong *)(set + (idx >> 6) * 8 + 0x40) >> (idx & 0x3f) & 1) != 0)) &&
        (cls == *(int *)(set + 0x24))) {
        /* WARNING: could not recover jumptable at 0x1fb4ac; indirect jump as call */
        (**(code **)(*(long *)(owner + -8) + 0x10))
            (a, *(long *)(set + 0x30) + *(long *)(*(long *)(owner + -8) + 0x48) * idx, owner);
        return;
    }
    FUN_003488bc(1);
    /* WARNING: subroutine does not return */
    FUN_0034a238();
}

/* FUN_001f22a8 @ 0x001f22a8   (est. cl4_sched_nonempty_check)
 * Ghidra: uint FUN_001f22a8(undefined8 param_1, long param_2)
 * Returns whether the scheduler queue is non-empty: short-circuits on empty,
 * otherwise takes the context, checks via FUN_001f99f4 and returns its low bit.
 * Confidence: low
 * Notes: queue-length short-circuit; FUN_001f99f4 check. */
uint cl4_sched_nonempty_check(word_t a, long sched)
{
    if (*(long *)(sched + 0x10) == 0) {
        return 0;
    }
    FUN_0034c798();
    thunk_FUN_0036b270(extraout_x1);
    FUN_0034b778();
    FUN_001f99f4();
    FUN_0036b118();
    return extraout_w1 & 1;
}

/* FUN_001f2308 @ 0x001f2308   (est. cl4_sched_dispatch_frame2)
 * Ghidra: void FUN_001f2308(void)
 * Dispatches a scheduler frame: resolves the context, invokes the method at
 * +0x20 over the frame, then runs the drain tail.
 * Confidence: low
 * Notes: FUN_00356c6c/FUN_0034b3e8 prep; method +0x20; FUN_0034bc94/FUN_000839d8. */
void cl4_sched_dispatch_frame2(void)
{
    FUN_00356c6c();
    FUN_0034b3e8();
    (**(code **)(extraout_x16 + 0x20))(extraout_x8);
    FUN_0034bc94(extraout_x8);
    FUN_000839d8();
}

/* FUN_001f2358 @ 0x001f2358   (est. cl4_sched_desc_caps)
 * Ghidra: undefined1 [16] FUN_001f2358(void)
 * Builds a scheduler capability descriptor: takes the context, resolves via
 * FUN_001fb26c and returns {slot, caps-masked}.
 * Confidence: low
 * Notes: thunk take; FUN_001fb26c resolve; caps masked & 0xffffffffff. */
cl4_desc_t cl4_sched_desc_caps(void)
{
    FUN_0034ba88();
    thunk_FUN_0036b270(extraout_x1);
    FUN_0034b768();
    FUN_001fb26c();
    FUN_00351a50();
    FUN_0036b118();
    cl4_desc_t r;
    r.hi = in_x4;
    r.lo = unaff_x20 & 0xffffffffff;
    return r;
}

/* FUN_001f23ac @ 0x001f23ac   (est. cl4_sched_scan_apply_pair)
 * Ghidra: void FUN_001f23ac(...5 args)
 * Scans and applies a pair op to a scheduler set: walks the bitmap, dispatches
 * each slot through the owner methods, runs the per-entry check (FUN_001f26cc)
 * and repeats until the set is drained; returns success bit.
 * Confidence: low
 * Notes: LZCOUNT bit scan; FUN_001f26cc check; SoftwareBreakpoint overflow. */
void cl4_sched_scan_apply_pair(word_t a, word_t b, word_t c, word_t d, word_t e)
{
    FUN_0008e518();
    FUN_00356900();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(extraout_x8 + 0x40));
    uint128_t r8 = FUN_00348f38();
    bool same = (r8_lo == r8_hi);
    if (same) {
        u6 = 1;
    } else {
        FUN_00359a04(*(word_t *)(unaff_x20 + 0x10));
        if (same) {
            thunk_FUN_001fca54(auStack_50);
            FUN_001f6b30(local_28, auStack_50, c, d, e);
            FUN_00359d38(local_18);
            thunk_FUN_0036b270();
            long l2 = local_8, l3 = lStack_10;
            do {
                while (l2 == 0) {
                    long l1 = l3 + 1;
                    if (SCARRY8(l3, 1)) {   /* WARNING: does not return */
                        SoftwareBreakpoint(1, 0x1f256c);
                    }
                    if (unaff_x25 <= l1) {
                        u6 = 1;
                        goto out;
                    }
                    l3 = l1;
                    l2 = *(long *)(lStack_20 + l1 * 8);
                }
                u6 = FUN_00359db0();
                FUN_00353c24(*(word_t *)(extraout_x16 + 0x10), u6,
                             *(long *)(extraout_x9 + 0x30) +
                             *(long *)(extraout_x16 + 0x48) * (extraout_x8_00 | l3 << 6));
                (*extraout_x8_01)();
                r8 = FUN_00350488();
                FUN_0031b614(r8_lo, r8_hi, d, e);
                r8 = FUN_00356bb0(e);
                FUN_00351360(r8_lo, r8_hi, 0x66bb20);
                uVar7 = FUN_001f26cc();
                FUN_00351384(*(word_t *)(extraout_x16 + 8));
                (*extraout_x8_02)();
            } while ((uVar7 & 1) != 0);
            u6 = 0;
out:
            FUN_0036b118(extraout_x9);
        } else {
            u6 = 0;
        }
    }
    FUN_0008e500(u6, unaff_x30);
}

/* FUN_001f2574 @ 0x001f2574   (est. cl4_sched_iter_next_b)
 * Ghidra: void FUN_001f2574(void)
 * Advances a scheduler iterator (mirror of FUN_001f3acc): skips empty words,
 * dispatches the next set slot via +0x10 and drains.
 * Confidence: low
 * Notes: LZCOUNT bit scan; method +0x10; SoftwareBreakpoint overflow. */
void cl4_sched_iter_next_b(void)
{
    FUN_00357cb4();
    FUN_00358f18();
    if (extraout_x9 == 0) {
        long l2;
        do {
            l2 = unaff_x23 + 1;
            if (SCARRY8(unaff_x23, 1)) {   /* WARNING: does not return */
                SoftwareBreakpoint(1, 0x1f2648);
            }
            if ((long)(unaff_x22 + 0x40U >> 6) <= l2) {
                FUN_0034c6c4();
                FUN_000839d8();
                goto done;
            }
            unaff_x23 = unaff_x23 + 1;
        } while (*(long *)(*(long *)(unaff_x20 + 8) + l2 * 8) == 0);
    }
    l2 = FUN_0034f264();
    (**(code **)(*(long *)(*(long *)(l2 + 0x10) + -8) + 0x10))();
    FUN_0034aed0();
    FUN_000839d8();
done:
    FUN_003596e4();
    FUN_00357c74(extraout_x1);
}
