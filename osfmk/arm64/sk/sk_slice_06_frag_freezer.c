/* sk_slice_06_frag_freezer.c — VAS freezer span allocator (0x37e9c-0x38184). */
#include "sk_slice_06_shared.h"

/* ---- Backing-span backend fatal helpers (ground truth: Ghidra FUN_). ---- */
extern void sk_freezer_panic_invalid(void) __attribute__((noreturn));   /* FUN_004b27f0 */
extern void sk_freezer_panic_no_backing(void) __attribute__((noreturn));/* FUN_004b2808 */

/* VAS error-string table at DAT_0064cb40. True when a status byte indexes a
 * recognized VAS error code (i.e. the table slot 0x64cb40+8*code and its
 * successor lie within the 0x40-byte table ending at 0x64cb80). The allocator
 * and freezer backends return this on failure to select the abort message. */
static bool sk_err_valid(uint64_t code)
{
    const uint64_t base = 0x64cb40;   /* DAT_0064cb40 */
    uint64_t idx = base + 8 * code;
    return (idx >= base) && (idx + 8 <= base + 0x40) && (idx <= idx + 8);
}

/* Fetch the error-string pointer for a status code from the VAS error table. */
static const char *sk_err_string(uint64_t code)
{
    return *(const char **)(0x64cb40UL + 8 * code);   /* DAT_0064cb40 */
}

/* FUN_00037e9c @ 0x00037e9c  (est. sk_vas_span_free)
 * Ghidra: void FUN_00037e9c(ulong *param_1, code *param_2)
 * Recursively releases a VAS span: a span descriptor is an array of 64-bit
 * slots; slots with tag (slot & 3) == 1 are indirect references whose upper
 * bits (slot >> 0x1c) point to a child span. If the head slot carries the
 * 0xc tag there are no children and the optional callback is invoked for each
 * indirect slot (cb(span)); otherwise each child span is freed depth-first.
 * Finally the capability slot itself is released. A null or non-canonical
 * span pointer aborts.
 * Confidence: medium
 * Notes: two near-identical child-span range guards (from an expanded bounds
 *   macro); recursion loop over-reads slot index 7 (offset 0x38) which acts
 *   as a zero terminator; sk_capslot_free = FUN_0003481c. */
static void sk_vas_span_free(uint64_t *slots, void (*cb)(uint64_t))
{
    uint64_t *end = (slots != NULL) ? slots + 8 : NULL;

    /* Null span (or a wrapped, non-canonical span pointer) aborts. */
    if (slots == NULL || end < slots + 1)
        SK_ASRT_PANIC(0x37fb0);

    if ((slots[0] & 0x3c) == 0xc) {
        /* Leaf/head span: no child spans. Invoke cb for every indirect slot
         * (slots[0]..slots[6], 0x38 bytes), passing each child span. */
        for (uint64_t off = 0; off != 0x38; off += 8) {
            uint64_t s = *(uint64_t *)((char *)slots + off);
            if (cb != NULL && (s & 3) == 1)
                cb(s >> 0x1c);
        }
    } else {
        /* Internal span: free each child span depth-first. */
        uint64_t slot = slots[0];
        uint64_t idx = 0;
        for (;;) {
            if ((slot & 3) == 1) {
                uint64_t child = slot >> 0x1c;
                /* Child-span bounds sanity: child..child+0x40 must be in
                 * range and the span at least 0x39 bytes. */
                uint64_t lim = child + 0x40;
                if (lim < child || (child != 0 && (lim - child) < 0x39))
                    SK_ASRT_PANIC(0x37fb0);
                uint64_t v = (child != 0) ? lim : 0;
                if (v < child || (child != 0 && (v - child) < 0x39))
                    SK_ASRT_PANIC(0x37fb0);
                sk_vas_span_free((uint64_t *)child, cb);
                /* Child fully released: the reference bits are now clear. */
                if ((slots[idx] & 0xfffffc0) == 0)
                    goto release;
            }
            if (idx > 6)
                goto release;
            idx++;
            slot = slots[idx];   /* index 7 reads the zero terminator at 0x38 */
        }
    }
release:
    sk_capslot_free((uint64_t)slots);   /* FUN_0003481c */
}

/* Request descriptor for the span allocator (used as both `in` and `stk`).
 * The allocator reads kind/size and, on success, stores the chosen base in
 * the +8 field (stk output slot 1). */
struct sk_freezer_req {
    uint8_t  kind;    /* +0x00: 0x11 = freezer span region */
    uint8_t  pad[7];  /* +0x01 */
    uint64_t base;    /* +0x08: requested start (0); allocator returns base */
    uint64_t size;    /* +0x10: request size, rounded up to 16 KiB */
    uint16_t flags;   /* +0x18: 0xfd */
    uint8_t  extra;   /* +0x1a: 0xe */
    uint32_t zero;    /* +0x1b */
    uint8_t  zero2;   /* +0x1f */
};

/* FUN_00037fb8 @ 0x00037fb8  (est. sk_freezer_alloc)
 * Ghidra: void FUN_00037fb8(ulong param_1, ulong *param_2)
 * Allocates a backing span for a freezer: requests a 0x11-kind span region of
 * `size` bytes rounded up to a 16 KiB boundary via sk_trap_alloc_region
 * (FUN_0003c510, selector 0x148), then fills the 5-word freezer descriptor:
 * out[0]=base, out[1]=capacity, out[2]=0 (bump offset), out[3]=region handle,
 * out[4]=0x65b648 marker. The base+size pair must not wrap. A nonzero
 * allocator status is reported as "Freezer failed to allocate span".
 * Confidence: medium
 * Notes: abort code field is (return >> 16) in the assembly; narrowed to the
 *   status byte by the uint8_t prototype. */
static void sk_freezer_alloc(uint64_t size, uint64_t *out)
{
    struct sk_freezer_req req = { 0 };
    sk_vas_lock_tok_t tok = { 0, 0 };   /* out: {region handle, 0x65b648} */
    uint8_t status;

    req.kind  = 0x11;
    req.size  = (size & ~(uint64_t)0x3fff) + ((size & 0x3fff) ? 0x4000 : 0);
    req.flags = 0xfd;
    req.extra = 0xe;

    status = sk_trap_alloc_region(0x148, &req, &tok, 0, &req);   /* FUN_0003c510 */
    if (status == 0) {
        uint64_t base = req.base;
        /* base + size must not wrap; an empty (base == 0) region is allowed. */
        if (base <= base + size && (base == 0 || size <= (base + size) - base)) {
            out[0] = base;          /* backing region base */
            out[1] = size;          /* reserved capacity */
            out[2] = 0;             /* current bump offset */
            out[3] = tok.flags;     /* backing region handle */
            out[4] = tok.counter;   /* 0x65b648 span marker */
            return;
        }
    } else if (sk_err_valid(status)) {
        sk_vas_abort("Freezer failed to allocate span (size=%zu, %s (0x%04hx))\n",
                     size, sk_err_string(status), (uint16_t)status);
    }
    SK_ASRT_PANIC(0x380b4);
}

/* FUN_000380b4 @ 0x000380b4  (est. sk_freezer_bump)
 * Ghidra: void FUN_000380b4(long *param_1, ulong param_2)
 * Extends the active allocation inside a freezer: the request size must fit
 * within the reserved capacity (fz[1]) and be larger than the current bump
 * offset (fz[2]); it is then handed to the backing grow op (ops table entry
 * +0x18) as (fz[3], &size), which may return a grown size that becomes the new
 * offset. Invalid freezers, oversized requests, and failed grows all abort.
 * Confidence: medium
 * Notes: vtable call is blraa x8,#0xb528; abort code field = rc >> 16. */
static void sk_freezer_bump(uint64_t *fz, uint64_t size)
{
    if (fz == NULL || fz[0] == 0)
        sk_freezer_panic_invalid();   /* FUN_004b27f0 (noreturn) */

    if (size <= fz[1]) {
        if (fz[2] < size) {
            uint64_t new_size = size;
            /* grow op: table[fz[4]] +0x18, called (backend=fz[3], &size). */
            uint32_t (*grow)(uint64_t, uint64_t *) =
                *(uint32_t (**)(uint64_t, uint64_t *))(fz[4] + 0x18);
            uint32_t rc = grow(fz[3], &new_size);
            uint8_t status = rc & 0xff;
            if (status != 0) {
                if (sk_err_valid(status))
                    sk_vas_abort("Freezer failed to bump span (size=%zu, %s (0x%04hx))\n",
                                 size, sk_err_string(status), (uint16_t)(rc >> 16));
                SK_ASRT_PANIC(0x38184);
            }
            fz[2] = new_size;   /* advance the bump offset */
        }
        return;
    }

    sk_vas_abort("Freezer bump size %zu exceeds reserved size %zu\n", size, fz[1]);
}

/* FUN_00038184 @ 0x00038184  (est. sk_freezer_destroy)
 * Ghidra: void FUN_00038184(long *param_1)
 * Destroys a freezer's backing span: invokes the backing destroy op (vtable
 * entry +0x00, no args) with the backend handle fz[3]; on success the freezer
 * is marked uninitialized (fz[0]=fz[1]=0). A freezer with no backend handle
 * or a failed destroy aborts.
 * Confidence: medium
 * Notes: vtable call is blraa x8,#0x9659; abort code field = rc >> 16. */
static void sk_freezer_destroy(uint64_t *fz)
{
    if (fz == NULL || fz[0] == 0)
        return;

    if (fz[3] == 0)
        sk_freezer_panic_no_backing();   /* FUN_004b2808 (noreturn) */

    /* destroy op: table[fz[4]] +0x00, no arguments. */
    uint32_t (*destroy_op)(void) = *(uint32_t (**)(void))fz[4];
    uint32_t rc = destroy_op();
    uint8_t status = rc & 0xff;
    if (status == 0) {
        fz[0] = 0;   /* uninitialized */
        fz[1] = 0;
        return;
    }

    if (sk_err_valid(status))
        sk_vas_abort("Freezer failed to destroy a backing span (%s (0x%04hx))\n",
                     sk_err_string(status), (uint16_t)(rc >> 16));
    SK_ASRT_PANIC(0x38220);
}
