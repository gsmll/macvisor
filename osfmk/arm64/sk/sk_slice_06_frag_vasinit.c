/* Recreated from the cL4 Secure Kernel VAS subsystem (slice 06, region
 * 0x0002ee90-0x00038184). Ground truth: Ghidra FUN_ names + addresses. All
 * names are estimates unless string/header matched. */
#include "sk_slice_06_shared.h"

/* ------------------------------------------------------------------ *
 * Local data structures (offsets derived from the decompiles).  These
 * describe the VAS object layout shared by the constructors/teardown
 * below.  The 0xd0-byte "body" at +0x60 and the page-descriptor groups
 * chained from +0x148 are opaque to this fragment but are walked by
 * sk_vas_teardown2.
 * ------------------------------------------------------------------ */

/* A VAS page descriptor (referenced from group slots). */
typedef struct {
    uint64_t    entries;    /* +0x00 pointer to the mapping-entry array   */
    uint64_t    target;     /* +0x08 token compared against entries       */
    uint64_t    field10;    /* +0x10                                      */
    uint64_t   *sub;        /* +0x18 3-qword sub-buffer (cleared on free) */
    uint64_t    field20;    /* +0x20                                      */
    void       *field28;    /* +0x28 buffer zeroed on free                */
    uint64_t    field30;    /* +0x30                                      */
    uint64_t    field38;    /* +0x38                                      */
    uint8_t     pad40[2];   /* +0x40                                      */
    uint8_t     size;       /* +0x42 byte-count (<<3 used for zeroing)    */
} sk_vas06_page_t;

/* A group of 7 page-descriptor slots; the first group is embedded in the
 * VAS object at +0x148, subsequent groups are chained through ->next. */
typedef struct {
    uint64_t           next;   /* +0x00 chain link                       */
    uint64_t           slotA[7];/* +0x08 companion slot array            */
    uint64_t           zero;   /* +0x40 always cleared                    */
    sk_vas06_page_t   *slotB[7];/* +0x48 the page descriptors            */
} sk_vas06_group_t;             /* total 0x80 bytes                       */

/* ------------------------------------------------------------------ *
 * Cross-slice / kernel helpers not declared with usable signatures in the
 * shared header.  The Ghidra FUN_ address is ground truth; names here are
 * local aliases chosen to keep call sites faithful (the header declares a
 * few of these with simplified/void signatures).
 * ------------------------------------------------------------------ */
extern uint64_t *sk_vas_pool_obj_alloc(void);                 /* FUN_000332b8 (header: sk_pool_alloc_1) */
extern void sk_vas_oom_panic(void) __attribute__((noreturn)); /* FUN_004b20ac */
extern sk_vas_lock_tok_t sk_vas_tok_derive(uint8_t kind, uint64_t a); /* FUN_000411dc */
extern void sk_vas_body_init(uint64_t base, uint8_t kind, uint64_t b, uint64_t c,
                             uint64_t tlo, uint64_t thi, uint64_t x, uint64_t y,
                             uint64_t flags);                 /* FUN_00041fbc */
extern void sk_vas_body_link(uint64_t vas, uint64_t tlo, uint64_t thi); /* FUN_0003c0e4 */
extern void sk_vas_state_hook(uint64_t vas);                  /* FUN_000459d4 */
extern void sk_vas_meta_teardown(uint64_t base);              /* FUN_0003c32c */
extern void sk_vas_body_teardown(uint64_t base);              /* FUN_00042808 */
extern void sk_vas_iter_panic(void) __attribute__((noreturn));/* FUN_00054354 */
extern void sk_vas_vspace_panic(void) __attribute__((noreturn));/* FUN_004b20e8 */
extern void sk_error_string_default(uint64_t *out, uint64_t n); /* FUN_0000178c */
/* Lock helpers: the header declares sk_vm_lock_acquire/release as (void),
 * but they take a lock address (FUN_00118164 / FUN_00118194). */
extern int sk_vas_lock_take(uint64_t lock);                   /* FUN_00118164 */
extern int sk_vas_lock_give(uint64_t lock);                   /* FUN_00118194 */
/* Opaque teardown iterator (PAC'd indirect seed). */
extern sk_vas_lock_tok_t sk_vas_iter_start(void);             /* SUB_dac10230d29ed7b1 */

/* Copy a zero-padded 32-byte L4 ErrorCode string into a 4-qword buffer. */
static void vas06_err_copy(uint64_t *out, const char *s)
{
    int i, j;
    for (i = 0; i < 4; i++) {
        uint64_t w = 0;
        for (j = 0; j < 8 && *s; j++)
            w |= (uint64_t)(uint8_t)*s++ << (8 * j);
        out[i] = w;
    }
}

/* ------------------------------------------------------------------ *
 * Functions (FUN_ address = ground truth).
 * ------------------------------------------------------------------ */

/* FUN_00032514 @ 0x00032514  (est. sk_vas_registry)
 * Ghidra: undefined8 * FUN_00032514(void)
 * Returns the address of the global VAS registry head pointer (the slot
 * DAT_0064c3f0).  The registry is a singly linked list threaded through
 * each VAS object's link field at +0x00.
 * Confidence: high
 * Notes: DAT_0064c3f0 global head slot. */
static uint64_t *sk_vas_registry(void)
{
    return (uint64_t *)0x64c3f0;   /* &DAT_0064c3f0 */
}

/* FUN_00032520 @ 0x00032520  (est. sk_vas_new)
 * Ghidra: undefined8 * FUN_00032520(char *param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Allocates a fresh VAS object from the VAS object pool, initializes it
 * from the 32-byte descriptor at p, and prepends it to the global VAS
 * registry under the registry lock.  Returns the new VAS object.  Any
 * failure path is a fatal abort.
 * Confidence: high
 * Notes: FUN_000332b8 pool alloc; FUN_004b20ac OOM panic; registry lock
 *   0x6ad2b0 (FUN_00118164/194). */
static uint64_t *sk_vas_new(char *p, uint64_t a2, uint64_t a3, uint64_t a4)
{
    uint64_t *vas = sk_vas_pool_obj_alloc();            /* FUN_000332b8 */
    if (vas == 0)
        sk_vas_oom_panic();                             /* FUN_004b20ac, noreturn */
    if (vas + 0x54 < vas)                               /* address-wrap guard */
        SK_ASRT_PANIC(0x325e0);

    /* 32-byte descriptor handed to the initializer. */
    uint64_t desc[4];
    desc[0] = *(uint64_t *)(p + 0);
    desc[1] = *(uint64_t *)(p + 8);
    desc[2] = *(uint64_t *)(p + 0x10);
    desc[3] = *(uint64_t *)(p + 0x18);
    sk_vas_init((uint64_t)vas, desc, a2, a3, a4);

    if (*p == '\0')
        sk_vas_check_inc();                             /* FUN_00034a5c */

    uint64_t *head = sk_vas_registry();                 /* &DAT_0064c3f0 */
    if (sk_vas_lock_take(0x6ad2b0) == 0) {              /* FUN_00118164 */
        vas[0] = *head;
        *head = (uint64_t)vas;
        if (sk_vas_lock_give(0x6ad2b0) == 0)            /* FUN_00118194 */
            return vas;
    }
    sk_vas_abort("VAS abort in function %s at line %d", "sk_vas_new", 0x5aed68);
}

/* FUN_0003264c @ 0x0003264c  (est. sk_vas_init)
 * Ghidra: void FUN_0003264c(long param_1, undefined8 *param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5)
 * Initializes a VAS object at `vas` from the 4-qword descriptor at p.
 * Populates the identity fields (+0x08..+0x20), derives an object token,
 * builds the +0x60 body sub-object, links the +0x138 list head, initializes
 * the +0x1f0 mutex, attaches the body, and runs the state hook.  Any
 * structural/bounds or mutex failure is fatal.
 * Confidence: medium
 * Notes: FUN_000411dc token derive; FUN_00041fbc body init; FUN_0003c0e4
 *   body link; FUN_000459d4 state hook; FUN_00118148 mutex init; the packed
 *   flags argument's high dword comes from an extra stack argument that
 *   callers omit (zero here), leaving bit9 of p[0]. */
static void sk_vas_init(uint64_t vas, uint64_t *p, uint64_t a3, uint64_t a4, uint64_t a5)
{
    uint8_t *v = (uint8_t *)vas;
    uint8_t kind = (uint8_t)p[0];
    sk_vas_lock_tok_t tok = sk_vas_tok_derive(kind, a3);   /* FUN_000411dc */

    *(uint64_t *)(v + 0x08) = p[0];
    *(uint64_t *)(v + 0x10) = p[1];
    *(uint64_t *)(v + 0x18) = p[2];
    *(uint64_t *)(v + 0x20) = p[3];

    if (v + 0x60 <= v + 0x130) {
        /* body sub-object at +0x60 (0xd0 bytes). */
        sk_vas_body_init(vas + 0x60, kind, p[1], p[2], tok.flags, tok.counter,
                         a4, a5, (p[0] >> 9) & 1);        /* FUN_00041fbc */
        *(uint64_t *)(v + 0x58) = 0;
        *(uint64_t *)(v + 0x138) = 0;
        if (v + 0x138 <= v + 0x140) {
            *(uint64_t *)(v + 0x140) = vas + 0x138;        /* list head self-link */
            if (v + 0x1f0 <= v + 0x200) {
                if (sk_mutex_init(v + 0x1f0, 0) != 0)      /* FUN_00118148 */
                    sk_vas_abort("VAS abort in function %s at line %d",
                                 "sk_vas_init", 0x5aed68);
                *(uint64_t *)(v + 0x200) = 0;
                sk_vas_body_link(vas, tok.flags, tok.counter);  /* FUN_0003c0e4 */
                sk_vas_state_hook(vas);                          /* FUN_000459d4 */
                return;
            }
        }
    }
    SK_ASRT_PANIC(0x32740);
}

/* FUN_00032774 @ 0x00032774  (est. sk_vas_destroy)
 * Ghidra: void FUN_00032774(undefined8 *param_1)
 * Tears down a VAS object (sk_vas_teardown2), unlinks it from the global
 * registry under the registry lock, decrements the live-object check
 * counter, and returns the object to its pool.  Aborts if the object is not
 * found in the registry.
 * Confidence: high
 * Notes: FUN_00032888 teardown; registry lock 0x6ad2b0; FUN_00034ad0 check
 *   dec; FUN_00033304 pool free; "unable to find vas" string 005af5d3. */
static void sk_vas_destroy(uint64_t *vas)
{
    sk_vas_teardown2((uint64_t)vas);
    if (sk_vas_lock_take(0x6ad2b0) != 0)                  /* FUN_00118164 */
        sk_vas_abort("VAS abort in function %s at line %d", "sk_vas_destroy", 0x5aed68);

    uint64_t *prev = sk_vas_registry();                   /* &DAT_0064c3f0 */
    for (;;) {
        uint64_t *node = (uint64_t *)*prev;
        if (node == vas) {
            *prev = vas[0];
            vas[0] = 0;
            if (sk_vas_lock_give(0x6ad2b0) != 0)          /* FUN_00118194 */
                sk_vas_abort("VAS abort in function %s at line %d",
                             "sk_vas_destroy", 0x5aed68);
            if (((uint8_t *)vas)[8] == 0)
                sk_vas_check_dec();                       /* FUN_00034ad0 */
            sk_pool_free_1((uint64_t)vas);                /* FUN_00033304 */
            return;
        }
        if (node == 0)
            break;
        prev = node;
        if (node + 1 < node)                              /* address-wrap guard */
            SK_ASRT_PANIC(0x327d0);
    }
    sk_vas_abort("unable to find vas %p on next_va list", (void *)vas); /* 005af5d3 */
}

/* FUN_00032888 @ 0x00032888  (est. sk_vas_teardown2)
 * Ghidra: void FUN_00032888(long param_1)
 * Full teardown of a VAS object: first drains any pending deferred
 * operations via an opaque iterator, then resets the state field, runs the
 * state hook and the +0x58 meta teardown, and finally walks the page-
 * descriptor group list (from +0x148).  Each page descriptor is detached,
 * its owning vspace (re)built and released, and the descriptor freed either
 * to the region pool or the heap depending on flag bit0 at +0x09.  Chained
 * groups (after the embedded first one) are returned to the pool.  Ends by
 * tearing down the +0x60 body sub-object.
 * Confidence: low
 * Notes: SUB_dac10230d29ed7b1 PAC'd iterator seed (vtable calls at +8/+0x30);
 *   FUN_000459d4 state hook; FUN_0003c32c meta teardown; sk_vspace_alloc
 *   out-slot 0x6af010; sk_vm_lock at vspace+0xb0; FUN_00033e00 region free;
 *   FUN_000341f4 heap free; FUN_000333f4 group free; FUN_00042808 body
 *   teardown; FUN_00054354 / FUN_004b20e8 noreturn panics. */
static void sk_vas_teardown2(uint64_t vas)
{
    uint8_t *v = (uint8_t *)vas;

    /* ---- drain pending deferred operations (opaque iterator). ---- */
    {
        sk_vas_lock_tok_t it = sk_vas_iter_start();   /* SUB_dac10230d29ed7b1 */
        if (it.flags != 0) {
            uint64_t status = 0;
            do {
                /* advance: call the method pointer stored at [it.counter]. */
                sk_vas_lock_tok_t elt =
                    ((sk_vas_lock_tok_t (*)(sk_vas_lock_tok_t))
                     (((uint64_t *)it.counter)[0]))(it);
                uint64_t vtab = elt.counter;
                uint64_t obj  = elt.flags;
                if (obj != 0) {
                    uint64_t c0 = 0, c1 = 0, c2 = 0, c3 = 0; /* local_90/88/80/78 */
                    if (vtab == 0)
                        sk_vas_iter_panic();            /* FUN_00054354, noreturn */
                    ((void (*)(uint64_t, void *))(((uint64_t *)vtab)[1]))(obj, &c0); /* vtab+8 */
                    sk_vas_check_result(status);
                    uint64_t o1 = 0, o2 = c2;
                    status = ((uint64_t (*)(uint64_t, uint64_t *, uint64_t *))
                              (((uint64_t *)vtab)[6]))(obj, &o1, &o2); /* vtab+0x30 */
                    sk_vas_check_result(status);
                }
            } while (it.flags != 0);
        }
    }

    *(uint64_t *)(v + 0x130) = 0;
    sk_vas_state_hook(vas);                             /* FUN_000459d4 */
    sk_vas_meta_teardown(vas + 0x58);                   /* FUN_0003c32c */
    uint8_t use_heap = ((uint8_t *)vas)[9] & 1;         /* flag bit0 at +0x09 */
    *(uint64_t *)(v + 0x138) = 0;
    *(uint64_t *)(v + 0x140) = vas + 0x138;             /* list head self-link */

    /* ---- release every page-descriptor group chained from +0x148. ---- */
    sk_vas06_group_t *first = (sk_vas06_group_t *)(v + 0x148);
    sk_vas06_group_t *grp = first;
    for (;;) {
        int i;
        grp->zero = 0;
        for (i = 0; i < 7; i++) {
            sk_vas06_page_t *page = grp->slotB[i];
            grp->slotB[i] = 0;
            grp->slotA[i] = 0;
            if (page == 0)
                continue;

            page->field38 = 0;
            page->field10 = 0;
            if (page->sub != 0) { page->sub[0] = 0; page->sub[1] = 0; page->sub[2] = 0; }
            *(uint16_t *)((uint8_t *)page->target + 6) = 0;
            sk_mem_zero(page->field28, 0, (uint64_t)page->size << 3); /* FUN_001143a0 */

            /* (re)build the backing vspace and detach this mapping. */
            uint64_t vspace = 0;
            sk_vspace_alloc(&vspace, 4, 10);            /* FUN_0005acac (out-slot 0x6af010) */
            uint64_t lock = vspace + 0xb0;
            if (vspace + 0xc0 < vspace + 0xb0)
                SK_ASRT_PANIC(0x32c60);
            if (sk_vas_lock_take(lock) != 0)            /* FUN_00118164 */
                sk_vas_abort("VAS abort in function %s at line %d",
                             "sk_vas_teardown2", 0x5aed68);
            {
                uint64_t *entries = (uint64_t *)page->entries;
                int idx;
                for (idx = 0; idx < 0x80; idx += 8) {
                    uint64_t *e  = (uint64_t *)((uint8_t *)entries + idx + 0x20);
                    uint64_t *e2 = (uint64_t *)((uint8_t *)entries + idx + 0x28);
                    if ((uint8_t *)entries + 0xa0 < (uint8_t *)e2 || e2 < e)
                        SK_ASRT_PANIC(0x32c60);
                    if (*e == page->target) {
                        uint8_t cnt = ((uint8_t *)entries)[0x1a];
                        if (cnt == 0)
                            sk_vas_vspace_panic();      /* FUN_004b20e8, noreturn */
                        cnt--;
                        ((uint8_t *)entries)[0x1a] = cnt;
                        uint64_t *last = (uint64_t *)((uint8_t *)entries + 0x20) + cnt;
                        if ((uint8_t *)entries + 0x20 > (uint8_t *)last ||
                            (uint8_t *)entries + 0xa0 < (uint8_t *)(last + 1) ||
                            last + 1 < last)
                            SK_ASRT_PANIC(0x32c60);
                        *e = *last;                     /* compact: last into slot */
                        *last = 0;
                        break;
                    }
                }
                page->entries = 0;
                if (*(uint64_t *)((uint8_t *)vspace + 0xa0) != (uint64_t)entries)
                    *(uint64_t *)((uint8_t *)vspace + 0xa0) = vspace;
            }
            if (sk_vas_lock_give(lock) != 0)            /* FUN_00118194 */
                sk_vas_abort("VAS abort in function %s at line %d",
                             "sk_vas_teardown2", 0x5aed68);
            if (!use_heap)
                sk_vas_region_free((uint64_t)page);     /* FUN_00033e00 */
            else
                sk_vas_heap_free((uint64_t)page);       /* FUN_000341f4 */
        }

        sk_vas06_group_t *next = (sk_vas06_group_t *)grp->next;
        if (grp != first)
            sk_pool_free_3((uint64_t)grp);              /* FUN_000333f4 */
        grp = next;
        if (next == 0) {
            *(uint16_t *)(v + 0x1d0) = 0;
            *(uint64_t *)(v + 0x1c8) = 0;
            sk_vas_body_teardown(vas + 0x60);           /* FUN_00042808 */
            return;
        }
    }
}

/* FUN_00032c68 @ 0x00032c68  (est. sk_vas_reinit)
 * Ghidra: void FUN_00032c68(long param_1, undefined8 param_2, undefined8 param_3)
 * Saves the VAS object's identity fields (+0x08..+0x30) into a local
 * descriptor, fully tears the object down (sk_vas_teardown2), then
 * re-initializes it from the saved descriptor, passing the saved +0x28/+0x30
 * pair plus the two call arguments to the initializer.
 * Confidence: high
 * Notes: FUN_00032888 teardown; FUN_0003264c init. */
static void sk_vas_reinit(uint64_t vas, uint64_t a2, uint64_t a3)
{
    uint64_t desc[4];
    uint64_t pair[2];
    desc[0] = *(uint64_t *)((uint8_t *)vas + 0x08);
    desc[1] = *(uint64_t *)((uint8_t *)vas + 0x10);
    desc[2] = *(uint64_t *)((uint8_t *)vas + 0x18);
    desc[3] = *(uint64_t *)((uint8_t *)vas + 0x20);
    pair[0] = *(uint64_t *)((uint8_t *)vas + 0x28);
    pair[1] = *(uint64_t *)((uint8_t *)vas + 0x30);
    sk_vas_teardown2(vas);
    sk_vas_init(vas, desc, (uint64_t)pair, a2, a3);
}

/* FUN_00032cd0 @ 0x00032cd0  (est. sk_vas_chk_bounds0)
 * Ghidra: void FUN_00032cd0(long param_1)
 * Bounds check: the +0x60 body must lie at or below +0x130 within the VAS
 * object; otherwise it is an internal consistency failure (assert).
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x32cec). */
static void sk_vas_chk_bounds0(uint64_t vas)
{
    if ((uint8_t *)vas + 0x60 <= (uint8_t *)vas + 0x130)
        return;
    SK_ASRT_PANIC(0x32cec);
}

/* FUN_00032cec @ 0x00032cec  (est. sk_vas_chk_bounds1)
 * Ghidra: void FUN_00032cec(long param_1)
 * Bounds check: the +0x58 meta field must lie at or below +0x60 within the
 * VAS object; otherwise it is an internal consistency failure (assert).
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x32d08). */
static void sk_vas_chk_bounds1(uint64_t vas)
{
    if ((uint8_t *)vas + 0x58 <= (uint8_t *)vas + 0x60)
        return;
    SK_ASRT_PANIC(0x32d08);
}

/* FUN_00032d08 @ 0x00032d08  (est. sk_vas_error_string)
 * Ghidra: void FUN_00032d08(undefined8 *param_1, byte param_2)
 * Fills the 32-byte buffer at `out` with the printable L4 ErrorCode name
 * selected by `code` (0..9).  Codes above 9 use a generic unknown-code
 * template finalized by a helper (FUN_0000178c).  Strings are copied as four
 * 8-byte words.
 * Confidence: high
 * Notes: error-name table at DAT_004bc048..004bc168; unknown template
 *   DAT_004bc188; FUN_0000178c finalize. */
static void sk_vas_error_string(uint64_t *out, uint8_t code)
{
    static const char *const names[10] = {
        "L4_ErrorCodeSuccess",       "L4_ErrorCodePreempted",
        "L4_ErrorCodeCanceled",      "L4_ErrorCodeTruncated",
        "L4_ErrorCodeCapInvalid",    "L4_ErrorCodeSlotInvalid",
        "L4_ErrorCodeMethodInvalid", "L4_ErrorCodeArgumentInvalid",
        "L4_ErrorCodeOperationInvalid", "L4_ErrorCodePermissionInvalid",
    };
    if (code > 9) {
        /* Unknown code: load the 32-byte generic template, then finalize. */
        static const uint8_t unknown[32] = "L4_ErrorCodeUnknown"; /* DAT_004bc188 */
        int i;
        for (i = 0; i < 4; i++)
            out[i] = ((const uint64_t *)unknown)[i];
        sk_error_string_default(out, 0x20);             /* FUN_0000178c */
        return;
    }
    vas06_err_copy(out, names[code]);
}

/* FUN_00032e1c @ 0x00032e1c  (est. sk_vas_abort0)
 * Ghidra: void FUN_00032e1c(undefined8 param_1)
 * Fatal abort variant: stores its argument (caller context) then invokes the
 * noreturn VAS abort with the standard "VAS abort in function %s at line %d"
 * template.
 * Confidence: high
 * Notes: noreturn; string 005af31e; FUN_004afae4. */
static void sk_vas_abort0(uint64_t a) __attribute__((noreturn));
static void sk_vas_abort0(uint64_t a)
{
    (void)a;
    sk_vas_abort("VAS abort in function %s at line %d", "sk_vas_abort0", 0x5af31e);
}

/* FUN_00032e30 @ 0x00032e30  (est. sk_vas_abort1)
 * Ghidra: void FUN_00032e30(undefined8 param_1)
 * Fatal abort variant: stores its argument (caller context) then invokes the
 * noreturn VAS abort with the standard "VAS abort in function %s at line %d"
 * template.
 * Confidence: high
 * Notes: noreturn; string 005af480; FUN_004afae4. */
static void sk_vas_abort1(uint64_t a) __attribute__((noreturn));
static void sk_vas_abort1(uint64_t a)
{
    (void)a;
    sk_vas_abort("VAS abort in function %s at line %d", "sk_vas_abort1", 0x5af480);
}
