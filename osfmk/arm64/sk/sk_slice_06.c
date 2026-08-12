/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. All names are estimates unless a
 * string/header matches.
 *
 * SLICE 06: VAS (virtual address space) subsystem, region 0x0002ee90-0x00038184.
 * This is the cL4 address-space layer: the VAS op-dispatch wrappers, the
 * capability-slot encoding/decoding helpers, the page-pool (freelist)
 * allocators, the "Freezer" span allocator (0x37fb8+), and the global VAS
 * registry. Function bodies are defined in the fragment files
 * sk_slice_06_frag_*.c included below. */
#include "sk_slice_06_shared.h"

/* ------------------------------------------------------------------ *
 * Shared helper implementations.
 * ------------------------------------------------------------------ */

/* Validate the slot-manager region lies within the VAS allocation and return
 * the slots pointer. (Dead 0x208/0x1f0 clause in the Ghidra bounds check is
 * elided.) */
static sk_vas_slots_t *sk_vas_slots(uint64_t vas)
{
    uint64_t slots = *(uint64_t *)(vas + 0x20);
    uint64_t end = slots + 0x210;
    if (*(uint64_t *)(vas + 0x28) < end || end < slots || slots < *(uint64_t *)(vas + 0x30))
        SK_ASRT_PANIC(0);
    return (sk_vas_slots_t *)slots;
}

/* Reserve the next 6-word (0x30-byte) slot in the ring; NULL if ring empty. */
static uint64_t *sk_vas_slot_reserve(sk_vas_slots_t *slots)
{
    uint64_t count = slots->count;
    if (count == 0)
        return NULL;
    uint64_t idx = slots->write_idx + 1;
    slots->write_idx = idx;
    uint64_t slot_idx = count ? idx % count : 0;
    uint64_t *ring = slots->ring;
    uint64_t *slot = ring + slot_idx * 6;
    if (slot < ring || ring + count * 6 < slot + 6 || slot + 6 < slot)
        SK_ASRT_PANIC(0);
    return slot;
}

/* Store a result code into a VAS slot's result fields. */
static void slot_res_store(uint64_t *slot, uint64_t code)
{
    *(char *)((char *)slot + 1) = (char)code;
    *(uint16_t *)((char *)slot + 2) = (uint16_t)(code >> 16);
    *(uint8_t *)((char *)slot + 4) = 0;
}

static void sk_vas_res_set(sk_vas_res_t *r, uint32_t code) { r->present = 1; r->code = code; }
static void sk_vas_res_clear(sk_vas_res_t *r)              { r->present = 0; }

/* Invoke the completion callback (ctx+0x10)(ctx, CONCAT24(hi16, lo32)). */
static void sk_vas_done(void *ctx, uint32_t hi16, uint32_t lo32)
{
    void (*fn)(void *, uint64_t) = *(void (**)(void *, uint64_t))((char *)ctx + 0x10);
    fn(ctx, ((uint64_t)hi16 << 32) | lo32);
}

/* Sanity-check a VAS op result code: 1..5 valid, else panic. */
static void sk_vas_check_result(uint64_t code)
{
    if (5 < (uint32_t)(code & 0xff) - 1)
        sk_vas_abort("unknown vas return code 0x%x", (unsigned)code);
}

/* Fragment bodies (function-by-function, English-first). */
#include "sk_slice_06_frag_opdispatch.c"
#include "sk_slice_06_frag_teardown.c"
#include "sk_slice_06_frag_capsplit.c"
#include "sk_slice_06_frag_spanmap.c"
#include "sk_slice_06_frag_pagetable.c"
#include "sk_slice_06_frag_desc.c"
#include "sk_slice_06_frag_rebuild.c"
#include "sk_slice_06_frag_vasinit.c"
#include "sk_slice_06_frag_pool.c"
#include "sk_slice_06_frag_heap.c"
#include "sk_slice_06_frag_lock.c"
#include "sk_slice_06_frag_slots.c"
#include "sk_slice_06_frag_cap.c"
#include "sk_slice_06_frag_span.c"
#include "sk_slice_06_frag_freezer.c"

/* End of slice 06. */
