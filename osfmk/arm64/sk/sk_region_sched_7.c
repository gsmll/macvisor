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
