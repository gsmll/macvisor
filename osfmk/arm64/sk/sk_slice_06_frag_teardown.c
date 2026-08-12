/* Recreated from the cL4 Secure Kernel VAS-subsystem slice (region
 * 0x0002ee90-0x00038184). Ground truth: Ghidra FUN_ names + addresses. All
 * names are estimates unless string/header matched. */
#include "sk_slice_06_shared.h"

/* Cross-slice helpers used by this fragment (not declared in the shared
 * header — local externs, ground-truth address in comment). */
extern void sk_vas_drain_table(uint64_t vas, uint64_t region);   /* FUN_0002b0cc */
extern void sk_vas_free_range(uint64_t block);                   /* thunk_FUN_00012568 */
extern uint32_t sk_vas_build_key_a;                              /* DAT_004bc1f8 */
extern uint32_t sk_vas_build_key_b;                              /* DAT_004bc1fc */

/* cL4 error codes returned by sk_vas_build. */
#define SK_VAS_BUILD_ERR_BADARG  0x10a0007UL   /* bad argument (vas/out null) */
#define SK_VAS_BUILD_ERR_MISS    0x1150002UL   /* first lookup miss */
#define SK_VAS_BUILD_ERR_INCOMPL 0x11d0002UL   /* second lookup miss, rolled back */

/* FUN_0002f94c @ 0x0002f94c  (est. sk_vas_teardown)
 * Ghidra: void FUN_0002f94c(long param_1)
 * Tears down a VAS object: first drains any pending table entries while the
 * pending count is non-zero, then releases the slot-manager array and finally
 * walks a teardown-callback table invoking each entry's destructor on its
 * argument before freeing the table itself. Leaves the object's count fields
 * cleared.
 * Confidence: medium
 * Notes: Bounds assertions render as SoftwareBreakpoint(0x5519,0x2fa34). The
 *   first check folded both operands to vas+const (0x1d8 vs 0x400), so it is a
 *   constant comparison — preserved as decompiled. Each callback-table entry
 *   is 0x58 bytes; entry[+0x10] is the argument and entry[+0x18] points to a
 *   vtable whose slot [0] is the destructor. */
static void sk_vas_teardown(uint64_t vas)
{
    uint64_t pending_count;
    uint64_t slot_base;
    uint64_t entry_base;
    uint64_t entry_count;
    uint64_t idx;
    uint64_t entry;
    uint64_t *arg_slot;
    void (**fn)(uint64_t);

    /* Drain pending table work while the pending count is non-zero. */
    pending_count = *(uint64_t *)(vas + 0x188);
    if (pending_count != 0) {
        /* Bounds assertion on the drain region (decompiler folded both sides
         * to vas+const; kept verbatim). */
        if (vas + 0x1d8 < vas + 0x400)
            SK_ASRT_PANIC(0x2fa34);
        do {
            sk_vas_drain_table(vas, vas + 0x400);
            pending_count = *(uint64_t *)(vas + 0x188);
        } while (pending_count != 0);
    }

    /* Release the slot-manager array (base at +0x170) and clear base/capacity. */
    slot_base = *(uint64_t *)(vas + 0x170);
    if (slot_base != 0) {
        sk_vas_free_range(slot_base);
        *(uint64_t *)(vas + 0x170) = 0;
        *(uint64_t *)(vas + 0x160) = 0;
    }
    *(uint64_t *)(vas + 0x168) = 0;

    /* Walk the teardown-callback table (entries at +0x1e8, count at +0x1e0,
     * each 0x58 bytes): call each entry's destructor on its argument, then
     * free the table and clear its base/stride fields. */
    entry_base = *(uint64_t *)(vas + 0x1e8);
    if (entry_base != 0) {
        entry_count = *(uint64_t *)(vas + 0x1e0);
        if (entry_count != 0) {
            idx = 0;
            do {
                entry = entry_base + idx * 0x58;
                /* Bounds/overflow assertion on the current entry pointer. */
                if (entry < entry_base ||
                    entry_base + entry_count * 0x58 < entry + 0x58 ||
                    entry + 0x58 < entry)
                    SK_ASRT_PANIC(0x2fa34);
                arg_slot = (uint64_t *)(entry + 0x10);
                fn = *(void (***)(uint64_t))(entry + 0x18);
                (*fn)(*arg_slot);
                idx++;
            } while (idx < entry_count);
            entry_base = *(uint64_t *)(vas + 0x1e8);
        }
        sk_vas_free_range(entry_base);
        *(uint64_t *)(vas + 0x1e8) = 0;
        *(uint64_t *)(vas + 0x1d8) = 0;
    }
    *(uint64_t *)(vas + 0x1e0) = 0;
}

/* FUN_0002fa34 @ 0x0002fa34  (est. sk_vas_slot_lookup)
 * Ghidra: long * FUN_0002fa34(long param_1, long param_2)
 * Linearly scans the VAS slot-manager array (base at +0x170, capacity at
 * +0x160) for the first slot holding the given key, checking at most the
 * count at +0x168 entries. Returns the matching slot pointer, or NULL if the
 * key is not present or the array is empty.
 * Confidence: high
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x2fa84). */
static uint64_t *sk_vas_slot_lookup(uint64_t vas, uint64_t key)
{
    uint64_t count;
    uint64_t capacity;
    uint64_t *base;
    uint64_t *slot;

    count = *(uint64_t *)(vas + 0x168);
    if (count != 0) {
        base = (uint64_t *)*(uint64_t *)(vas + 0x170);
        capacity = *(uint64_t *)(vas + 0x160);
        slot = base;
        do {
            /* Bounds/overflow assertion on the current slot pointer. */
            if (base + capacity < slot + 1 || slot + 1 < slot || slot < base)
                SK_ASRT_PANIC(0x2fa84);
            if (*slot == key)
                return slot;
            slot++;
            count--;
        } while (count != 0);
    }
    return NULL;
}

/* FUN_0002fa84 @ 0x0002fa84  (est. sk_vas_build)
 * Ghidra: undefined1 [16] FUN_0002fa84(long param_1, long *param_2)
 * Builds a VAS reference pair into the caller-supplied out buffer: stores the
 * VAS handle at out[0], then uses the VAS object's vtable to look up a first
 * object by key A into out[1] and, on success, a second object by key B into
 * out[6]; on failure the earlier acquisition is released or rolled back.
 * Returns a lock token whose flags field holds the cL4 result code (0 on
 * success) and whose counter is zero.
 * Confidence: medium
 * Notes: vtable slots at vas+0x10 (lookup), vas+0x18 (release), vas+0x20
 *   (rollback). Keys come from DAT_004bc1f8 / DAT_004bc1fc. Return modeled as
 *   the 16-byte pair {flags=code, counter=0}. */
static sk_vas_lock_tok_t sk_vas_build(uint64_t vas, uint64_t *out)
{
    uint64_t code;
    uint32_t tag;
    uint64_t (*lookup)(uint64_t key, uint64_t *slot);
    void (*release)(uint64_t *obj, uint32_t tag);
    void (*rollback)(uint64_t *obj);

    code = SK_VAS_BUILD_ERR_BADARG;
    if (vas != 0 && out != NULL) {
        out[0] = vas;
        out[0xe] = 0;
        out[0xd] = 0;
        out[0x10] = 0;
        out[0xf] = 0;

        lookup = *(uint64_t (**)(uint64_t, uint64_t *))(vas + 0x10);
        tag = sk_vas_build_key_a;   /* DAT_004bc1f8 */
        lookup(tag, &out[1]);
        if (out[1] == 0) {
            code = SK_VAS_BUILD_ERR_MISS;
        } else {
            release = *(void (**)(uint64_t *, uint32_t))(vas + 0x18);
            release(&out[1], tag);
            tag = sk_vas_build_key_b;   /* DAT_004bc1fc */
            lookup(tag, &out[6]);
            if (out[6] == 0) {
                rollback = *(void (**)(uint64_t *))(vas + 0x20);
                rollback(&out[1]);
                code = SK_VAS_BUILD_ERR_INCOMPL;
            } else {
                release(&out[6], tag);
                code = 0;
                out[0xb] = 0;
                out[0xc] = 0;
            }
        }
    }
    return (sk_vas_lock_tok_t){ .flags = code, .counter = 0 };
}
