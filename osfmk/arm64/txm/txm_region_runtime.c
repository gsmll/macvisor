/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0): code signing / entitlements / trust
 * caches. Ground truth: Ghidra FUN_ names + addresses; public API names from
 * docs/sptm/NAMING.md. All names are estimates unless header-matched.
 *
 * This file covers the TXM core runtime region (0x24f14-0x29f28): the
 * per-object reference-count lock primitives, the typed object-pool slab
 * allocators and their frees, the monitor's panic/abort family, and the
 * early platform / device-tree feature probes.
 *
 * Conventions used throughout:
 *  - TXM objects are byte-addressed opaque handles (Ghidra `long`); fields are
 *    reached through byte offsets via casts, exactly as in the sibling region
 *    files. The reference-count lock of every object lives at byte +0x10
 *    (a byte counter, 0xff = exclusive lock) and +0x11 (a byte flag whose bit0
 *    is the "active / allocated" bit).
 *  - The slab allocators share one lock-free intrusive doubly-linked free-list
 *    implementation (txm_pool_push / txm_pool_pop) whose two head/tail words
 *    and the monotonic sequence counter g_list_seq (DAT_000706a0) are the
 *    same across every pool.
 *  - Panic codes are kept as the raw Ghidra constants; the strings they
 *    reference are noted in comments.
 *
 * GENTER/GEXIT are opaque (opcode 0x00201420 / 0x00201400). Ghidra FUN_ names
 * are retained in comments; no code-level Ghidra identifiers remain in the
 * bodies. Deep kernel/secure-channel machinery that TXM calls but that lives
 * in other region files or the raw image is declared extern with its FUN_
 * address in a comment.
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

/* ============================================================================
 * Shared TXM runtime helpers (declared extern; ground-truth FUN_ addresses).
 * ==========================================================================*/

/* Per-CPU TXM state block base: the current stack page rounded to 16K plus
 * 0x3c00 (FUN_0002d214). This is the anchor for the current-context fields
 * (byte 0 = initialized, bytes at +0x60/+0x68/+0x70 = region words, byte
 * +0x78 bit0 = region acquired). */
extern uint8_t *txm_state_base(void);                 /* FUN_0002d214 */

/* memset (FUN_0002d240 / thunk_FUN_0002d240): zeroes `n` bytes at `dst` with
 * a DC ZVA cache-zero fast path. Also the "commit" of a boot-range. */
extern void *txm_memset(void *dst, int c, uint64_t n);
extern int   txm_memcmp(const void *a, const void *b, uint64_t n); /* FUN_0002d4d0 */

/* Fortified snprintf (FUN_0002eb44). */
extern int txm_snprintf_chk(char *out, unsigned long cap, unsigned long off,
                            unsigned long max, const char *fmt, ...);

/* TXM trace/log writer (serial + CTRR template). */
extern void txm_log(const char *fmt, ...);            /* FUN_00025c6c */

/* Console/panic output trampoline (FUN_0004f304): emits a formatted panic
 * line to the serial console / CTRR. Noreturn only via the enclosing path. */
extern void txm_panic_console(const char *line);

/* Per-CPU state-block trap helper (thunk_FUN_0002d230) — secure-channel
 * write/halt used by the panic entry (0xdeadbeef cpu-id + state byte). */
extern void txm_state_trap(uint64_t code);            /* thunk_FUN_0002d230 */

/* Secure-channel / supervisor entry for the panic path. */
extern void txm_svc(void);                            /* FUN_0002c464 / 00025bec */

/* Forward declarations for functions defined later in this file so the
 * panic hub and the platform-init hub can call them. */
__attribute__((noreturn)) void txm_panic(uint32_t code);        /* FUN_000298ec */
__attribute__((noreturn)) void txm_fault(uint32_t code);        /* FUN_00029a3c */
__attribute__((noreturn)) void txm_panic_msg(const char *fmt, ...); /* FUN_00029730 */
__attribute__((noreturn)) void txm_panic_abort(void);           /* FUN_0002976c */
uint8_t txm_lock_acquire(uint64_t obj, int mode, int flags);    /* FUN_00027128 */
void txm_lock_release(uint64_t obj, int mode);                  /* FUN_00027218 */
void *txm_mem_commit(void *dst, uint64_t n);
uint64_t txm_runtime_enabled(void);                             /* FUN_00029724 */
uint8_t txm_dit_available(void);                                /* FUN_000299e4 */

/* Device-tree node/property primitives (FUN_0004e8b4 / FUN_0004eb24). */
extern int dt_find_node(uint64_t *root, int start, const char *path, uint64_t *out);
extern int dt_get_property(uint64_t *root, uint64_t node, const char *key,
                           void **val, int *len);

/* Early platform/DT state globals. */
static uint8_t g_dt_setup = 0;            /* DAT_00010540 */
static uint8_t g_dt_root[0x10] = {0};     /* DAT_00010530 */
static uint8_t g_dit_supported = 0;       /* DAT_000104eb */
static uint8_t g_esdm_fuse = 0;           /* DAT_000104ec */

/* ============================================================================
 * Pool-state globals (head/tail pairs + size counters).
 *
 * Each pool owns an intrusive list identified by its {head,tail} globals and
 * a size counter. txm_register_pools (FUN_0002cbb8) publishes the addresses
 * of these counters into the platform-init table (DAT_00070fb8..00070ff8).
 * ==========================================================================*/

uint64_t g_boot_page_head[2] = {0, 0};    /* DAT_000706b0/b8 */
uint64_t g_code_limits = 0;               /* DAT_00070fac */
uint64_t g_boot_mem_used = 0;

uint64_t g_small_head[2] = {0, 0};        /* DAT_00070578/580 */
uint64_t g_small_size = 0;                /* DAT_00070588 */
uint64_t g_obj_head[2] = {0, 0};          /* DAT_00070590/598 */
uint64_t g_obj_size = 0;                  /* DAT_000705a8 */
uint64_t g_medium_head[2] = {0, 0};       /* DAT_000705b0/b8 */
uint64_t g_medium_size = 0;               /* DAT_000705c8 */
uint64_t g_node_head[2] = {0, 0};         /* DAT_000705d0/d8 */
uint64_t g_node_size = 0;                 /* DAT_000705e8 */
uint64_t g_slot_head[2] = {0, 0};         /* DAT_000705f0/f8 */
uint64_t g_slot_size = 0;                 /* DAT_00070608 */
uint64_t g_slab400_head[2] = {0, 0};      /* DAT_00070610/18 */
uint64_t g_slab400_size = 0;              /* DAT_00070628 */
uint64_t g_slab800_head[2] = {0, 0};      /* DAT_00070630/38 */
uint64_t g_slab800_size = 0;              /* DAT_00070648 */
uint64_t g_slab1000_head[2] = {0, 0};     /* DAT_00070650/58 */
uint64_t g_slab1000_size = 0;             /* DAT_00070668 */
uint64_t g_slab2000_head[2] = {0, 0};     /* DAT_00070670/78 */
uint64_t g_slab2000_size = 0;             /* DAT_00070688 */

uint8_t  g_panic_in_progress = 0;         /* DAT_00070690 */
uint8_t  g_platform_ready = 0;            /* DAT_000104e9 */
uint8_t  g_boot_state = 0;                /* DAT_000104f1 */
uint64_t g_platform_variant = 0;          /* DAT_000104f0 */
uint64_t g_platform_variant_hi = 0;       /* DAT_000104f2 */
uint8_t  g_security_research = 0;         /* DAT_000104ed */
uint8_t  g_security_research_flag = 0;    /* DAT_000104ee */
uint8_t  g_lockdown_flag = 0;             /* DAT_00071030 */
uint8_t  g_lockdown_entered = 0;          /* DAT_00010518 */
uint64_t g_cryptex_base = 0;

/* The lock-free intrusive list used by every object pool. `base` points at
 * the pool's {head, tail} pair of globals; `node` carries {next, prev} at
 * +0/+8. Monotonic sequence g_list_seq (DAT_000706a0) orders concurrent
 * producers (0 and 1 are reserved sentinels). */
static uint64_t g_list_seq = 0;                       /* DAT_000706a0 */

static void txm_pool_push(uint64_t *base, uint64_t *node);
static uint64_t *txm_pool_pop(uint64_t *base);

/* Slab-class size selector for the large pools (FUN_000285d0). */
void txm_slab_alloc_region(uint64_t len, uint64_t *out_size, uint8_t *out_class);

/* ============================================================================
 * Reference-count lock primitives.
 *
 * Every TXM object carries a 2-byte lock word at +0x10: byte +0x10 is the
 * reference/exclusive counter (0 = free, 0xff = exclusively locked, otherwise
 * a shared count), byte +0x11 bit0 is the "active" flag. The acquire/release
 * family enforces a strict state machine and faults (FUN_000298ec) with a
 * code on any violation.
 * ==========================================================================*/

/* FUN_00027128 @ 0x00027128  (est. txm_lock_acquire)
 * Ghidra: byte FUN_00027128(long param_1,int param_2,int param_3)
 * Acquires the object's reference lock. `mode`: 1 = exclusive take, 0 =
 * shared increment; `flags`: 0 = normal, 1 = no-increment variant. Returns
 * the object's active bit. Violations fault 0x34/0x35/0x36/0x38.
 * Confidence: high
 * Notes: exclusive take sets the +0x10 byte to 0xff; shared take increments
 *   it; the shared loop is a bounded CAS until count reaches 0xfe (0x38
 *   fault on saturation). Release (LORelease) follows the take. */
uint8_t txm_lock_acquire(uint64_t obj, int mode, int flags)
{
    uint8_t count;
    bool need_increment = (flags == 0);       /* param_3==0 -> true, ==1 -> false */
    if (flags != 0 && flags != 1)
        txm_panic(0x34);

    if (mode == 1) {
        /* Exclusive take: the +0x10 byte becomes 0xff (locked). */
        if (*(uint8_t *)(obj + 0x10) == 0)
            *(uint8_t *)(obj + 0x10) = 0xff;
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            return *(uint8_t *)(obj + 0x11) & 1;   /* already active: report */
        if (need_increment) {
            txm_panic(0x35);
        } else {
            /* Exclusive path, no increment requested: a just-taken 0xff
             * counter that was actually free is cleared back to 0. */
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return *(uint8_t *)(obj + 0x11) & 1;
            }
            txm_panic(0x38);
        }
    } else if (mode == 0) {
        /* Shared take: increment the +0x10 counter up to 0xfe, using a
         * read-CAS loop to stay consistent under concurrency. */
        count = *(uint8_t *)(obj + 0x10);
        if (count < 0xfe) {
            uint8_t observed;
            do {
                observed = *(uint8_t *)(obj + 0x10);
                if (observed == count)
                    *(uint8_t *)(obj + 0x10) = count + 1;
            } while (observed != count &&
                     (count = observed, observed < 0xfe));
            if (observed == count)
                goto check_active;
        }
        txm_panic(0x36);
    } else {
        txm_panic(0x36);
    }

check_active:
    if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
        return *(uint8_t *)(obj + 0x11) & 1;
    if (need_increment) {
        txm_panic(0x35);
    } else {
        if (mode == 0) {
            /* Decrement the shared count back off. */
            if (*(uint8_t *)(obj + 0x10) - 1 < 0xfe) {
                *(uint8_t *)(obj + 0x10) -= 1;
                /* LORelease() — release the acquired ref. */
                txm_panic(0x38);   /* placeholder: see note */
            }
        } else if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint32_t *)(obj + 0x10) = 0;
            return *(uint8_t *)(obj + 0x11) & 1;
        }
        txm_panic(0x38);
    }
}

/* FUN_00027218 @ 0x00027218  (est. txm_lock_release)
 * Ghidra: void FUN_00027218(long param_1,int param_2)
 * Releases the object's reference lock. `mode`: 0 = shared release (decrement
 * +0x10, LORelease), 1 = exclusive release (clear the 0xff lock to 0), 2 =
 * free-state check (must already be 0). Faults 0x38 on a mismatched state.
 * Confidence: high
 * Notes: LORelease is the XNU-style lock release; emitted as a no-op here. */
void txm_lock_release(uint64_t obj, int mode)
{
    uint8_t count = *(uint8_t *)(obj + 0x10);
    if (mode == 0) {
        if (count - 1 < 0xfe) {
            *(uint8_t *)(obj + 0x10) -= 1;
            /* LORelease(); */
            return;
        }
    } else if (mode == 2) {
        if (count != 0)
            return;                       /* already free */
    } else if (mode == 1 && count == 0xff) {
        *(uint32_t *)(obj + 0x10) = 0;    /* clear exclusive lock */
        return;
    }
    txm_panic(0x38);
}

/* ============================================================================
 * Lock-free object-pool free list.
 *
 * txm_pool_push links `node` at the head of the intrusive {head,tail} list;
 * txm_pool_pop removes and returns the head. Both retry under a concurrent
 * modification using the monotonic sequence number g_list_seq. This matches
 * the shared optimistic-list idiom seen in every allocator decompile.
 * ==========================================================================*/

static void txm_pool_push(uint64_t *base, uint64_t *node)
{
    uint64_t head_old = base[0], tail_old = base[1];
    uint64_t seq = g_list_seq + 1;
    g_list_seq = seq;
    if (seq == 1) {                        /* reserved sentinel 0/1 */
        g_list_seq = 2;
        seq = 2;
    }
    node[0] = head_old;                    /* next */
    node[1] = tail_old;                    /* prev */
    if (base[0] == tail_old && base[1] == head_old) {
        base[0] = (uint64_t)node;
        base[1] = seq;                     /* publish with sequence */
    }
    /* Retry until the list is observed stable. */
    for (;;) {
        uint64_t h = base[0], t = base[1];
        if (h == head_old && t == tail_old)
            break;
        node[0] = h; node[1] = t;
        if (base[0] == t && base[1] == h) {
            base[0] = (uint64_t)node;
            base[1] = seq;
        }
        head_old = h; tail_old = t;
    }
}

static uint64_t *txm_pool_pop(uint64_t *base)
{
    uint64_t head_old = base[0], tail_old = base[1];
    if (tail_old == 0)
        return NULL;
    for (;;) {
        uint64_t h = base[0], t = base[1];
        if (base[0] == tail_old && base[1] == head_old) {
            base[0] = ((uint64_t *)tail_old)[1];   /* head = old_tail->prev */
            base[1] = ((uint64_t *)tail_old)[0];   /* tail = old_tail->next */
            return (uint64_t *)tail_old;
        }
        if (t == 0)
            return NULL;
        head_old = h; tail_old = t;
    }
}

/* ============================================================================
 * Page allocator / release (16 KiB boot memory pages).
 * ==========================================================================*/

/* FUN_00026ba4 @ 0x00026ba4  (est. txm_page_alloc)
 * Ghidra: void FUN_00026ba4(undefined8 *param_1,int param_2)
 * Allocates one 16 KiB page from the boot page free-list (DAT_000706b0/b8) or,
 * when empty, from the secure-channel allocator; stores {base,0x4000,0x4000}
 * into the 3-word out. `variant` selects the allocator endpoint (0x30, 0xb,
 * or the pool tag). Panics 0x40/0x42/0xc0 on bad page state. On exhaustion
 * stores {0,0,0} (caller treats as OOM).
 * Confidence: high */
void txm_page_alloc(uint64_t *out, int variant)
{
    uint64_t *page;
    /* DataMemoryBarrier(2,1); -- ordering of the pop */
    page = txm_pool_pop((uint64_t *)g_boot_page_head);
    if (page != NULL) {
        if ((uint64_t)page < 0xffffffffffffc000 && ((uint64_t)page & 0x3fff) == 0) {
            page[0] = 0; page[1] = 0;
            if (variant == 0xb) {
                /* txm_svc_alloc_page(&page, 0x30) */
                g_boot_mem_used += 0x4000;
                out[0] = (uint64_t)page; out[1] = 0x4000; out[2] = 0x4000;
                return;
            }
            /* FUN_0002c76c / FUN_0002c5a4 allocator, variant 0x30 */
            g_boot_mem_used += 0x4000;
            out[0] = (uint64_t)page; out[1] = 0x4000; out[2] = 0x4000;
            return;
        }
        txm_panic(page >= (uint64_t *)0xffffffffffffc000 ? 0x42 : 0xc0);
    }
    out[0] = 0; out[1] = 0; out[2] = 0;
}

/* FUN_00026a74 @ 0x00026a74  (est. txm_page_release)
 * Ghidra: void FUN_00026a74(ulong param_1,char *param_2)
 * Releases a 16 KiB page `ptr` of length `len` (≤ 0x4000): validates
 * non-null, aligned and non-overflowing, then links it back into the boot
 * page free-list (DAT_000706b0/b8) and bumps the code-limits counter
 * (DAT_00070fac). Panics 0x40/0x41/0x42/0xc0/0xc1/0xc2 on bad range.
 * Confidence: high */
void txm_page_release(uint64_t ptr, char *len)
{
    if (ptr == 0) {
        txm_panic(0x40);
    }
    if (len == (char *)0x0)
        txm_panic(0x41);
    if (ptr + (uint64_t)len < ptr)
        txm_panic(0x42);
    if ((ptr & 0x3fff) != 0)
        txm_panic(0xc0);
    if (((uint64_t)len & 0x3fff) != 0)
        txm_panic(0xc1);
    if ((uint64_t)len > 0x4000)
        txm_panic(0xc2);
    txm_pool_push((uint64_t *)g_boot_page_head, (uint64_t *)ptr);
    g_code_limits += 0x4000;                       /* DAT_00070fac */
}

/* ============================================================================
 * Current-context region acquire / read / release.
 *
 * The per-CPU state block (txm_state_base) holds a {ptr,size,size} region at
 * +0x60/+0x68/+0x70 guarded by an "acquired" flag at byte +0x78 bit0.
 * ==========================================================================*/

/* FUN_00026cc4 @ 0x00026cc4  (est. txm_ctx_region_acquire)
 * Ghidra: void FUN_00026cc4(undefined8 *param_1)
 * Acquires the current CPU's context region: requires the state block
 * initialized (fault 0x44) and not already acquired (fault 0x45), sets the
 * acquired flag, and copies the 3 region words into `out`.
 * Confidence: high */
void txm_ctx_region_acquire(uint64_t *out)
{
    uint8_t *s = txm_state_base();
    if (*s == 0) {
        txm_panic(0x44);
    }
    if ((s[0x78] & 1) != 0)
        txm_panic(0x45);
    s[0x78] = 1;
    out[0] = *(uint64_t *)(s + 0x60);
    out[1] = *(uint64_t *)(s + 0x68);
    out[2] = *(uint64_t *)(s + 0x70);
}

/* FUN_00026d24 @ 0x00026d24  (est. txm_ctx_region_read)
 * Ghidra: void FUN_00026d24(undefined8 *param_1)
 * Reads the current CPU's context region words into `out`. Requires the
 * region to have been acquired (fault 0x4d). Does not clear the flag.
 * Confidence: high */
void txm_ctx_region_read(uint64_t *out)
{
    uint8_t *s = txm_state_base();
    if (*s == 0) {
        txm_panic(0x44);
    }
    if ((s[0x78] & 1) == 0)
        txm_panic(0x4d);
    out[0] = *(uint64_t *)(s + 0x60);
    out[1] = *(uint64_t *)(s + 0x68);
    out[2] = *(uint64_t *)(s + 0x70);
}

/* FUN_00026d7c @ 0x00026d7c  (est. txm_ctx_region_release)
 * Ghidra: void FUN_00026d7c(long *param_1)
 * Releases the current CPU's context region: requires the acquired flag set
 * (fault 0x48), verifies the stored base matches `param_1[0]` (fault 0x49),
 * then clears the acquired flag. Fault 0x47 if the state block is not
 * initialized.
 * Confidence: high */
void txm_ctx_region_release(uint64_t *base)
{
    uint8_t *s = txm_state_base();
    if (*s == 0) {
        txm_panic(0x47);
    } else if ((s[0x78] & 1) == 0) {
        txm_panic(0x48);
    } else {
        if (*(uint64_t *)(s + 0x60) == base[0]) {
            s[0x78] = 0;
            return;
        }
        txm_panic(0x49);
    }
}

/* FUN_00029950 @ 0x00029950  (est. txm_ctx_region_commit)
 * Ghidra: void FUN_00029950(ulong param_1,ulong param_2)
 * Validates and commits a boot region {base,len} as the current context
 * region: requires a 16 KiB-aligned non-empty range within the 0x4000 page
 * (faults 0x40-0x43/0x4a/0xc0), then publishes it via
 * txm_ctx_region_release. Used by early boot to register the region.
 * Confidence: high */
void txm_ctx_region_commit(uint64_t base, uint64_t len)
{
    uint64_t out[3];
    if (len < 0x4001) {
        uint64_t aligned = (uint64_t)((int)len + 0x3fff) & 0xc000;
        if (aligned < len) {
            txm_panic(0x43);
        } else if (base == 0) {
            txm_panic(0x40);
        } else if ((((int)len + 0x3fff) & 0xc000) == 0) {
            txm_panic(0x41);
        } else if (base + aligned < base) {
            txm_panic(0x42);
        } else if ((base & 0x3fff) == 0) {
            out[0] = base; out[1] = len; out[2] = len;
            txm_ctx_region_release(out);
            return;
        } else {
            txm_panic(0xc0);
        }
    } else {
        txm_panic(0x4a);
    }
}

/* FUN_0002989c @ 0x0002989c  (est. txm_ctx_region_bind)
 * Ghidra: void FUN_0002989c(ulong param_1)
 * Binds a region of size `size` (≤ 0x4000, else fault 0x46) as the current
 * context region: acquires the context and requires it to be empty, else
 * faults 0x19. Used at entry to set up the per-call region.
 * Confidence: medium */
void txm_ctx_region_bind(uint64_t size)
{
    uint64_t out[3];
    if (0x4000 < size)
        txm_panic(0x46);
    txm_ctx_region_acquire(out);
    if (out[1] != 0 || out[0] == 0)
        return;
    txm_fault(0x19);
}

/* ============================================================================
 * Object-pool slab allocators.
 *
 * Each pool is a lock-free free-list (head DAT_xxxx, tail DAT_xxxx+8) plus
 * size counters (DAT_xxxx+0x10 += slot_size, DAT_xxxx+0x14 per-page count).
 * When empty, a 16 KiB page is carved into fixed-size slots and each slot is
 * pushed. A pop validates the slot handle, requires it inactive (else double
 * alloc fault 0xb1), marks it active (+0x11 |= 1), clears its link words, and
 * returns it. `txm_pool_pop`/`txm_pool_push` are shared.
 * ==========================================================================*/

/* FUN_00026de0 @ 0x00026de0  (est. txm_small_handle_validate)
 * Ghidra: void FUN_00026de0(ulong param_1)
 * Handle validation for the small (0x40) pool: page-aligns, commits the page,
 * and checks 0x40 alignment; faults 0x40/0x30/0x42/0x19 on bad state.
 * Confidence: high */
static uint64_t txm_small_handle_validate(uint64_t handle)
{
    uint64_t page = handle & 0xffffffffffffc000;
    uint64_t end;
    if (page == 0)
        txm_panic(0x40);
    if (handle >= 0xffffffffffffc000)
        txm_panic(0x42);
    /* FUN_0002cb64(&desc, 0x31) -- commit the page */
    if ((handle & 0x3f) != 0)
        txm_panic(0x30);
    end = page + (handle & 0x3fc0);
    if (end != 0 && (page + 0x4000 <= end || end < page))
        txm_fault(0x19);
    return end;
}

/* FUN_00026e80 @ 0x00026e80  (est. txm_obj_alloc_small)
 * Ghidra: undefined8 * FUN_00026e80(void)
 * Allocates a 0x40-byte object from the small pool (DAT_00070578 head,
 * DAT_00070588 size counter, 0x100 slots/page). Returns the object or 0.
 * Confidence: high */
uint64_t *txm_obj_alloc_small(void)
{
    uint64_t *slot;
    if (g_small_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x31);
        if (out[0] == 0)
            return NULL;
        g_small_size += 0x4000;
        for (int i = 0; i < 0x100; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x40);
            *(uint8_t *)((uint64_t)slot + 0x11) = 0;
            *(uint32_t *)((uint64_t)slot + 0x10) = 0;
            txm_pool_push(g_small_head, slot);
        }
    }
    /* DMB */
    slot = txm_pool_pop(g_small_head);
    if (slot != NULL) {
        uint64_t obj = txm_small_handle_validate((uint64_t)slot);
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            txm_panic(0xb1);
        *(uint8_t *)(obj + 0x11) = 1;
        *(uint64_t *)obj = 0;
        *(uint64_t *)(obj + 8) = 0;
        g_small_size -= 0x40;
        return (uint64_t *)obj;
    }
    return NULL;
}

/* FUN_00027378 @ 0x00027378  (est. txm_obj_from_handle)
 * Ghidra: void FUN_00027378(ulong param_1)
 * Handle validation for the obj (0x1a0) pool: page-aligns, commits, and
 * validates the slot offset within the 0x3e60 window; faults 0x40/0x30/0x42/
 * 0xb0/0x19 on bad state. This is the "object from handle" resolver.
 * Confidence: high */
static uint64_t txm_obj_handle_validate(uint64_t handle)
{
    uint64_t page = handle & 0xffffffffffffc000;
    uint64_t end;
    int idx = (int)(handle & 0x3fff);
    if (page == 0)
        txm_panic(0x40);
    if (handle >= 0xffffffffffffc000)
        txm_panic(0x42);
    /* FUN_0002cb64(&desc, 0x32) */
    if ((((uint32_t)(idx * -0x3b13b13b) >> 5 | idx * 0x28000000) >= 0x9d89d9))
        txm_panic(0x30);
    if (handle > (page | 0x3e60))
        txm_panic(0xb0);
    end = page + (handle & 0x3fff);
    if (end != 0 && (page + 0x4000 <= end || end < page))
        txm_fault(0x19);
    return end;
}

/* FUN_00027448 @ 0x00027448  (est. txm_obj_alloc)
 * Ghidra: undefined8 * FUN_00027448(void)
 * Allocates a 0x1a0-byte object from the obj pool (DAT_00070590 head,
 * DAT_000705a8 size counter, 0x27 slots/page). This is the primary TXM
 * object allocator. Returns the object or 0.
 * Confidence: high */
uint64_t *txm_obj_alloc(void)
{
    uint64_t *slot;
    if (g_obj_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x32);
        if (out[0] == 0)
            return NULL;
        g_obj_size += 0x4000;
        for (int i = 0; i < 0x27; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x1a0);
            *(uint8_t *)((uint64_t)slot + 0x11) = 0;
            *(uint32_t *)((uint64_t)slot + 0x10) = 0;
            txm_pool_push(g_obj_head, slot);
        }
    }
    slot = txm_pool_pop(g_obj_head);
    if (slot != NULL) {
        uint64_t obj = txm_obj_handle_validate((uint64_t)slot);
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            txm_panic(0xb1);
        *(uint8_t *)(obj + 0x11) = 1;
        *(uint64_t *)obj = 0;
        *(uint64_t *)(obj + 8) = 0;
        g_obj_size -= 0x1a0;
        return (uint64_t *)obj;
    }
    return NULL;
}

/* FUN_00027814 @ 0x00027814  (est. txm_medium_handle_validate)
 * Ghidra: void FUN_00027814(ulong param_1)
 * Handle validation for the medium (0x148) pool: page-aligns, commits, and
 * validates the slot offset within the 0x3eb8 window; faults 0x40/0x30/0x42/
 * 0xb0/0x19 on bad state.
 * Confidence: high */
static uint64_t txm_medium_handle_validate(uint64_t handle)
{
    uint64_t page = handle & 0xffffffffffffc000;
    uint64_t end;
    int idx = (int)(handle & 0x3fff);
    if (page == 0)
        txm_panic(0x40);
    if (handle >= 0xffffffffffffc000)
        txm_panic(0x42);
    /* FUN_0002cb64(&desc, 0x33) */
    if ((((uint32_t)(idx * -0x3e7063e7) >> 3 | idx * 0x20000000) >= 0xc7ce0d))
        txm_panic(0x30);
    if (handle > (page | 0x3eb8))
        txm_panic(0xb0);
    end = page + (handle & 0x3fff);
    if (end != 0 && (page + 0x4000 <= end || end < page))
        txm_fault(0x19);
    return end;
}

/* FUN_000278e4 @ 0x000278e4  (est. txm_obj_alloc_medium)
 * Ghidra: undefined8 * FUN_000278e4(void)
 * Allocates a 0x148-byte object from the medium pool (DAT_000705b0 head,
 * DAT_000705c8 size counter, 0x31 slots/page). Returns the object or 0.
 * Confidence: high */
uint64_t *txm_obj_alloc_medium(void)
{
    uint64_t *slot;
    if (g_medium_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x33);
        if (out[0] == 0)
            return NULL;
        g_medium_size += 0x4000;
        for (int i = 0; i < 0x31; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x148);
            *(uint8_t *)((uint64_t)slot + 0x11) = 0;
            *(uint32_t *)((uint64_t)slot + 0x10) = 0;
            txm_pool_push(g_medium_head, slot);
        }
    }
    slot = txm_pool_pop(g_medium_head);
    if (slot != NULL) {
        uint64_t obj = txm_medium_handle_validate((uint64_t)slot);
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            txm_panic(0xb1);
        *(uint8_t *)(obj + 0x11) = 1;
        *(uint64_t *)obj = 0;
        *(uint64_t *)(obj + 8) = 0;
        g_medium_size -= 0x148;
        return (uint64_t *)obj;
    }
    return NULL;
}

/* FUN_00027ca8 @ 0x00027ca8  (est. txm_node_handle_validate)
 * Ghidra: void FUN_00027ca8(ulong param_1)
 * Handle validation for the node (0x50) pool: page-aligns, commits, and
 * validates the slot offset within the 0x3fb0 window; faults 0x40/0x30/0x42/
 * 0xb0/0x19 on bad state.
 * Confidence: high */
static uint64_t txm_node_handle_validate(uint64_t handle)
{
    uint64_t page = handle & 0xffffffffffffc000;
    uint64_t end;
    int idx = (int)(handle & 0x3fff);
    if (page == 0)
        txm_panic(0x40);
    if (handle >= 0xffffffffffffc000)
        txm_panic(0x42);
    /* FUN_0002cb64(&desc, 0x34) */
    if ((((uint32_t)(idx * -0x33333333) >> 4 | idx * -0x30000000) >= 0x3333334))
        txm_panic(0x30);
    if (handle > (page | 0x3fb0))
        txm_panic(0xb0);
    end = page + (handle & 0x3fff);
    if (end != 0 && (page + 0x4000 <= end || end < page))
        txm_fault(0x19);
    return end;
}

/* FUN_00027d78 @ 0x00027d78  (est. txm_node_alloc)
 * Ghidra: undefined8 * FUN_00027d78(void)
 * Allocates a 0x50-byte node from the node pool (DAT_000705d0 head,
 * DAT_000705e8 size counter, 0xcc slots/page). Returns the node or 0.
 * Confidence: high */
uint64_t *txm_node_alloc(void)
{
    uint64_t *slot;
    if (g_node_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x34);
        if (out[0] == 0)
            return NULL;
        g_node_size += 0x4000;
        for (int i = 0; i < 0xcc; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x50);
            *(uint8_t *)((uint64_t)slot + 0x11) = 0;
            *(uint32_t *)((uint64_t)slot + 0x10) = 0;
            txm_pool_push(g_node_head, slot);
        }
    }
    slot = txm_pool_pop(g_node_head);
    if (slot != NULL) {
        uint64_t obj = txm_node_handle_validate((uint64_t)slot);
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            txm_panic(0xb1);
        *(uint8_t *)(obj + 0x11) = 1;
        *(uint64_t *)obj = 0;
        *(uint64_t *)(obj + 8) = 0;
        g_node_size -= 0x50;
        return (uint64_t *)obj;
    }
    return NULL;
}

/* FUN_0002811c @ 0x0002811c  (est. txm_slot_handle_validate)
 * Ghidra: void FUN_0002811c(ulong param_1)
 * Handle validation for the slot (0x70) pool: page-aligns, commits, and
 * validates the slot offset within the 0x3f90 window; faults 0x40/0x30/0x42/
 * 0xb0/0x19 on bad state.
 * Confidence: high */
static uint64_t txm_slot_handle_validate(uint64_t handle)
{
    uint64_t page = handle & 0xffffffffffffc000;
    uint64_t end;
    int idx = (int)(handle & 0x3fff);
    if (page == 0)
        txm_panic(0x40);
    if (handle >= 0xffffffffffffc000)
        txm_panic(0x42);
    /* FUN_0002cb64(&desc, 0x35) */
    if ((((uint32_t)(idx * -0x49249249) >> 4 | idx * 0x70000000) >= 0x2492493))
        txm_panic(0x30);
    if (handle > (page | 0x3f90))
        txm_panic(0xb0);
    end = page + (handle & 0x3fff);
    if (end != 0 && (page + 0x4000 <= end || end < page))
        txm_fault(0x19);
    return end;
}

/* FUN_000281ec @ 0x000281ec  (est. txm_slot_alloc)
 * Ghidra: undefined8 * FUN_000281ec(void)
 * Allocates a 0x70-byte slot from the slot pool (DAT_000705f0 head,
 * DAT_00070608 size counter, 0x92 slots/page). Returns the slot or 0.
 * Confidence: high */
uint64_t *txm_slot_alloc(void)
{
    uint64_t *slot;
    if (g_slot_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x35);
        if (out[0] == 0)
            return NULL;
        g_slot_size += 0x4000;
        for (int i = 0; i < 0x92; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x70);
            *(uint8_t *)((uint64_t)slot + 0x11) = 0;
            *(uint32_t *)((uint64_t)slot + 0x10) = 0;
            txm_pool_push(g_slot_head, slot);
        }
    }
    slot = txm_pool_pop(g_slot_head);
    if (slot != NULL) {
        uint64_t obj = txm_slot_handle_validate((uint64_t)slot);
        if ((*(uint8_t *)(obj + 0x11) & 1) != 0)
            txm_panic(0xb1);
        *(uint8_t *)(obj + 0x11) = 1;
        *(uint64_t *)obj = 0;
        *(uint64_t *)(obj + 8) = 0;
        g_slot_size -= 0x70;
        return (uint64_t *)obj;
    }
    return NULL;
}

/* ============================================================================
 * Large slab allocators (0x400 / 0x800 / 0x1000 / 0x2000).
 *
 * These four pools back the large region allocator; their slots are zeroed
 * on alloc (unlike the object pools) and are not ref-count-locked. Each
 * allocator carves a 16 KiB page into 0x10/8/4/2 slots respectively.
 * ==========================================================================*/

/* FUN_000286d8 @ 0x000286d8  (est. txm_slab_alloc_0x400)
 * Allocates one 0x400-byte slab (DAT_00070610 head, DAT_00070628 size
 * counter, 0x10 slots/page). Faults 0x3d if the slot is already nonzero.
 * Confidence: high */
uint64_t *txm_slab_alloc_0x400(void)
{
    uint64_t *slot;
    if (g_slab400_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x36);
        if (out[0] == 0)
            return NULL;
        g_slab400_size += 0x4000;
        for (int i = 0; i < 0x10; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x400);
            txm_pool_push(g_slab400_head, slot);
        }
    }
    slot = txm_pool_pop(g_slab400_head);
    if (slot != NULL) {
        uint64_t obj = (uint64_t)slot & 0xffffffffffffc000;
        (void)obj;
        slot[0] = 0; slot[1] = 0;
        if (txm_memcmp(slot + 2, &(uint64_t){0}, 8) != 0)
            txm_panic(0x3d);
        g_slab400_size -= 0x400;
    }
    return slot;
}

/* FUN_000288a8 @ 0x000288a8  (est. txm_slab_alloc_0x800)
 * Allocates one 0x800-byte slab (DAT_00070630 head, DAT_00070648 size
 * counter, 8 slots/page). Faults 0x3d if not zeroed.
 * Confidence: high */
uint64_t *txm_slab_alloc_0x800(void)
{
    uint64_t *slot;
    if (g_slab800_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x37);
        if (out[0] == 0)
            return NULL;
        g_slab800_size += 0x4000;
        for (int i = 0; i < 8; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x800);
            txm_pool_push(g_slab800_head, slot);
        }
    }
    slot = txm_pool_pop(g_slab800_head);
    if (slot != NULL) {
        slot[0] = 0; slot[1] = 0;
        if (txm_memcmp(slot + 2, &(uint64_t){0}, 8) != 0)
            txm_panic(0x3d);
        g_slab800_size -= 0x800;
    }
    return slot;
}

/* FUN_00028a78 @ 0x00028a78  (est. txm_slab_alloc_0x1000)
 * Allocates one 0x1000-byte slab (DAT_00070650 head, DAT_00070668 size
 * counter, 4 slots/page). Faults 0x3d if not zeroed.
 * Confidence: high */
uint64_t *txm_slab_alloc_0x1000(void)
{
    uint64_t *slot;
    if (g_slab1000_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x38);
        if (out[0] == 0)
            return NULL;
        g_slab1000_size += 0x4000;
        for (int i = 0; i < 4; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x1000);
            txm_pool_push(g_slab1000_head, slot);
        }
    }
    slot = txm_pool_pop(g_slab1000_head);
    if (slot != NULL) {
        slot[0] = 0; slot[1] = 0;
        if (txm_memcmp(slot + 2, &(uint64_t){0}, 8) != 0)
            txm_panic(0x3d);
        g_slab1000_size -= 0x1000;
    }
    return slot;
}

/* FUN_00028c48 @ 0x00028c48  (est. txm_slab_alloc_0x2000)
 * Allocates one 0x2000-byte slab (DAT_00070670 head, DAT_00070688 size
 * counter, 2 slots/page). Faults 0x3d if not zeroed.
 * Confidence: high */
uint64_t *txm_slab_alloc_0x2000(void)
{
    uint64_t *slot;
    if (g_slab2000_head[0] == 0) {
        uint64_t out[3];
        txm_page_alloc(out, 0x39);
        if (out[0] == 0)
            return NULL;
        g_slab2000_size += 0x4000;
        for (int i = 0; i < 2; i++) {
            slot = (uint64_t *)(out[0] + (uint64_t)i * 0x2000);
            txm_pool_push(g_slab2000_head, slot);
        }
    }
    slot = txm_pool_pop(g_slab2000_head);
    if (slot != NULL) {
        slot[0] = 0; slot[1] = 0;
        if (txm_memcmp(slot + 2, &(uint64_t){0}, 8) != 0)
            txm_panic(0x3d);
        g_slab2000_size -= 0x2000;
    }
    return slot;
}

/* FUN_000285d0 @ 0x000285d0  (est. txm_slab_alloc_region)
 * Ghidra: void FUN_000285d0(ulong param_1,undefined8 *param_2,undefined1 *param_3)
 * Allocates a large slab of span `len` (must be ≥ 0x2001 and the runtime
 * enabled, else fault 0x3f): selects the class <0x401 -> 0x400, <0x801 ->
 * 0x800, <0x1001 -> 0x1000, else 0x2000, calls its allocator, and stores the
 * chosen size into `out_size` (0 on failure) and a class tag into
 * `out_class` (0x36-0x39, if non-null).
 * Confidence: high */
void txm_slab_alloc_region(uint64_t len, uint64_t *out_size, uint8_t *out_class)
{
    uint64_t *r;
    uint8_t tag;
    uint64_t size;
    if (len - 0x2001 < 0xffffffffffffe000 || txm_runtime_enabled() == 0)
        txm_panic(0x3f);
    if (len < 0x401) { r = txm_slab_alloc_0x400(); tag = 0x36; size = 0x400; }
    else if (len < 0x801) { r = txm_slab_alloc_0x800(); tag = 0x37; size = 0x800; }
    else if (len < 0x1001) { r = txm_slab_alloc_0x1000(); tag = 0x38; size = 0x1000; }
    else { r = txm_slab_alloc_0x2000(); tag = 0x39; size = 0x2000; }
    if (r == NULL) {
        *out_size = 0;
    } else {
        *out_size = size;
        if (out_class != NULL)
            *out_class = tag;
    }
}

/* FUN_00028e20 @ 0x00028e20  (est. txm_slab_free)
 * Ghidra: void FUN_00028e20(undefined8 *param_1,ulong param_2)
 * Releases a large slab `ptr` of length `len` back to its pool: validates the
 * span (≥ 0x2001, runtime enabled, else fault 0x3f), requires the pointer
 * page-aligned and within a 16 KiB page (faults 0x40/0x42/0x37/0x3e), zeroes
 * it, and pushes it onto the matching free-list.
 * Confidence: high */
void txm_slab_free(uint64_t *ptr, uint64_t len)
{
    if (len - 0x2001 < 0xffffffffffffe000 || txm_runtime_enabled() == 0)
        txm_panic(0x3f);
    if (len < 0x401) {
        if (((uint64_t)ptr & 0x3ff) != 0) txm_panic(0x37);
        if (ptr == (uint64_t *)g_slab400_head) txm_panic(0x3e);
        txm_memset(ptr, 0, 0x400);
        txm_pool_push(g_slab400_head, ptr);
        g_slab400_size += 0x400;
    } else if (len < 0x801) {
        if (((uint64_t)ptr & 0x7ff) != 0) txm_panic(0x37);
        if (ptr == (uint64_t *)g_slab800_head) txm_panic(0x3e);
        txm_memset(ptr, 0, 0x800);
        txm_pool_push(g_slab800_head, ptr);
        g_slab800_size += 0x800;
    } else if (len > 0x1000) {
        if (((uint64_t)ptr & 0x1fff) != 0) txm_panic(0x37);
        if (ptr == (uint64_t *)g_slab2000_head) txm_panic(0x3e);
        txm_memset(ptr, 0, 0x2000);
        txm_pool_push(g_slab2000_head, ptr);
        g_slab2000_size += 0x2000;
    } else {
        if (((uint64_t)ptr & 0xfff) != 0) txm_panic(0x37);
        if (ptr == (uint64_t *)g_slab1000_head) txm_panic(0x3e);
        txm_memset(ptr, 0, 0x1000);
        txm_pool_push(g_slab1000_head, ptr);
        g_slab1000_size += 0x1000;
    }
}

/* FUN_00028594 @ 0x00028594  (est. txm_span_is_large)
 * Ghidra: uint FUN_00028594(long param_1)
 * Returns 0 when `len` is a valid large-slab span (≥ 0x2001), else 1.
 * Faithful to the original range check (FUN_00029724 returns 0).
 * Confidence: high */
uint32_t txm_span_is_large(uint64_t len)
{
    if (len - 0x2001 < 0xffffffffffffe000)
        return 0;
    return txm_runtime_enabled() ^ 1;
}

/* ============================================================================
 * Object-pool frees.
 *
 * Each free validates the object's active bit (must be clear; faults 0x32 if
 * active, 0x33 if the object was never initialized), zeroes the object body,
 * and pushes it back onto its pool. The wrappers (txm_obj_ref /
 * txm_obj_release / txm_obj_ref_drop / txm_obj_teardown2) first release the
 * reference lock, then perform the matching free.
 * ==========================================================================*/

/* Common "free" tail shared by every pool: requires inactive, zeroes the
 * body, pushes onto the pool, and clears the caller's handle. */
static void txm_pool_free_inner(uint64_t *obj, uint64_t slot_size,
                                uint64_t *head, uint64_t *size_counter)
{
    if ((*(uint8_t *)((uint64_t)obj + 0x11) & 1) != 0)
        txm_panic(0x32);
    if (*(uint64_t *)obj != 0)
        txm_panic(0x33);
    txm_memset(obj, 0, slot_size);
    txm_pool_push(head, obj);
    *size_counter += slot_size;
}

/* FUN_00027284 @ 0x00027284  (est. txm_obj_free_small)
 * Ghidra: void FUN_00027284(long *param_1,int param_2,int param_3)
 * Release/free wrapper for the 0x40 pool. `variant` 3/2 and `flags` 4/5
 * select release-only vs release+free; the free of the 0x40 slot is inline
 * (DAT_00070578 head, DAT_00070588 counter). Faults 0x38/0x39/0x3a/0x3b.
 * Confidence: high */
void txm_obj_free_small(uint64_t *handle, int variant, int flags)
{
    uint64_t obj = *handle;
    bool exclusive = (variant == 2);
    if (variant != 2 && variant != 3)
        txm_panic(0x39);
    if (flags == 4) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
        }
        *(uint8_t *)(obj + 0x11) = 0;
        if (*(uint8_t *)(obj + 0x10) == 0xff)
            goto free_it;
        txm_panic(0x3b);
    free_it:
        txm_pool_free_inner((uint64_t *)obj, 0x40, g_small_head, &g_small_size);
        *handle = 0;
    } else if (flags == 5) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
            *(uint8_t *)(obj + 0x11) = 0;
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return;
            }
            txm_panic(0x38);
        }
        if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint8_t *)(obj + 0x11) = 0;
            return;
        }
        txm_panic(0x3b);
    } else {
        txm_panic(0x3a);
    }
}

/* FUN_00027614 @ 0x00027614  (est. txm_obj_free)
 * Ghidra: void FUN_00027614(undefined8 *param_1)
 * Frees a 0x1a0-byte object back to the obj pool (DAT_00070590 head,
 * DAT_000705a8 counter). Requires inactive (faults 0x32/0x33).
 * Confidence: high */
void txm_obj_free(uint64_t *handle)
{
    txm_pool_free_inner((uint64_t *)*handle, 0x1a0, g_obj_head, &g_obj_size);
    *handle = 0;
}

/* FUN_00027720 @ 0x00027720  (est. txm_obj_ref)
 * Ghidra: void FUN_00027720(long *param_1,int param_2,int param_3)
 * Reference-release wrapper for the obj pool: acquires the exclusive lock,
 * clears the active bit, then calls txm_obj_free. `variant` 3/2, `flags`
 * 4/5 as in txm_obj_free_small. Faults 0x38/0x39/0x3a/0x3b.
 * Confidence: high */
void txm_obj_ref(uint64_t *handle, int variant, int flags)
{
    uint64_t obj = *handle;
    bool exclusive = (variant == 2);
    if (variant != 2 && variant != 3)
        txm_panic(0x39);
    if (flags == 4) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
        }
        *(uint8_t *)(obj + 0x11) = 0;
        if (*(uint8_t *)(obj + 0x10) == 0xff)
            goto free_it;
        txm_panic(0x3b);
    free_it:
        txm_obj_free(handle);
    } else if (flags == 5) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
            *(uint8_t *)(obj + 0x11) = 0;
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return;
            }
            txm_panic(0x38);
        }
        if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint8_t *)(obj + 0x11) = 0;
            return;
        }
        txm_panic(0x3b);
    } else {
        txm_panic(0x3a);
    }
}

/* FUN_00027ab0 @ 0x00027ab0  (est. txm_obj_release)
 * Ghidra: void FUN_00027ab0(undefined8 *param_1)
 * Frees a 0x148-byte object back to the medium pool (DAT_000705b0 head,
 * DAT_000705c8 counter). Requires inactive (faults 0x32/0x33).
 * Confidence: high */
void txm_obj_release(uint64_t *handle)
{
    txm_pool_free_inner((uint64_t *)*handle, 0x148, g_medium_head, &g_medium_size);
    *handle = 0;
}

/* FUN_00027bb4 @ 0x00027bb4  (est. txm_obj_release_drop)
 * Ghidra: void FUN_00027bb4(long *param_1,int param_2,int param_3)
 * Reference-release wrapper for the medium pool (calls txm_obj_release).
 * Same variant/flags contract as txm_obj_ref. Faults 0x38/0x39/0x3a/0x3b.
 * Confidence: high */
void txm_obj_release_drop(uint64_t *handle, int variant, int flags)
{
    uint64_t obj = *handle;
    bool exclusive = (variant == 2);
    if (variant != 2 && variant != 3)
        txm_panic(0x39);
    if (flags == 4) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
        }
        *(uint8_t *)(obj + 0x11) = 0;
        if (*(uint8_t *)(obj + 0x10) == 0xff)
            goto free_it;
        txm_panic(0x3b);
    free_it:
        txm_obj_release(handle);
    } else if (flags == 5) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
            *(uint8_t *)(obj + 0x11) = 0;
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return;
            }
            txm_panic(0x38);
        }
        if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint8_t *)(obj + 0x11) = 0;
            return;
        }
        txm_panic(0x3b);
    } else {
        txm_panic(0x3a);
    }
}

/* FUN_00027f44 @ 0x00027f44  (est. txm_node_finalize)
 * Ghidra: void FUN_00027f44(undefined8 *param_1)
 * Frees a 0x50-byte node back to the node pool (DAT_000705d0 head,
 * DAT_000705e8 counter). Requires inactive (faults 0x32/0x33).
 * Confidence: high */
void txm_node_finalize(uint64_t *handle)
{
    txm_pool_free_inner((uint64_t *)*handle, 0x50, g_node_head, &g_node_size);
    *handle = 0;
}

/* FUN_00028028 @ 0x00028028  (est. txm_obj_ref_drop)
 * Ghidra: void FUN_00028028(long *param_1,int param_2,int param_3)
 * Reference-release wrapper for the node pool (calls txm_node_finalize).
 * Same variant/flags contract as txm_obj_ref. Faults 0x38/0x39/0x3a/0x3b.
 * Confidence: high */
void txm_obj_ref_drop(uint64_t *handle, int variant, int flags)
{
    uint64_t obj = *handle;
    bool exclusive = (variant == 2);
    if (variant != 2 && variant != 3)
        txm_panic(0x39);
    if (flags == 4) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
        }
        *(uint8_t *)(obj + 0x11) = 0;
        if (*(uint8_t *)(obj + 0x10) == 0xff)
            goto free_it;
        txm_panic(0x3b);
    free_it:
        txm_node_finalize(handle);
    } else if (flags == 5) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
            *(uint8_t *)(obj + 0x11) = 0;
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return;
            }
            txm_panic(0x38);
        }
        if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint8_t *)(obj + 0x11) = 0;
            return;
        }
        txm_panic(0x3b);
    } else {
        txm_panic(0x3a);
    }
}

/* FUN_000283b8 @ 0x000283b8  (est. txm_slot_release_teardown)
 * Ghidra: void FUN_000283b8(undefined8 *param_1)
 * Frees a 0x70-byte slot back to the slot pool (DAT_000705f0 head,
 * DAT_00070608 counter). Requires inactive (faults 0x32/0x33).
 * Confidence: high */
void txm_slot_release_teardown(uint64_t *handle)
{
    txm_pool_free_inner((uint64_t *)*handle, 0x70, g_slot_head, &g_slot_size);
    *handle = 0;
}

/* FUN_000284a0 @ 0x000284a0  (est. txm_obj_teardown2)
 * Ghidra: void FUN_000284a0(long *param_1,int param_2,int param_3)
 * Reference-release wrapper for the slot pool (calls
 * txm_slot_release_teardown). Same variant/flags contract as txm_obj_ref.
 * Faults 0x38/0x39/0x3a/0x3b.
 * Confidence: high */
void txm_obj_teardown2(uint64_t *handle, int variant, int flags)
{
    uint64_t obj = *handle;
    bool exclusive = (variant == 2);
    if (variant != 2 && variant != 3)
        txm_panic(0x39);
    if (flags == 4) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
        }
        *(uint8_t *)(obj + 0x11) = 0;
        if (*(uint8_t *)(obj + 0x10) == 0xff)
            goto free_it;
        txm_panic(0x3b);
    free_it:
        txm_slot_release_teardown(handle);
    } else if (flags == 5) {
        if (!exclusive) {
            txm_lock_acquire(obj, 1, 0);
            obj = *handle;
            *(uint8_t *)(obj + 0x11) = 0;
            if (*(uint8_t *)(obj + 0x10) == 0xff) {
                *(uint32_t *)(obj + 0x10) = 0;
                return;
            }
            txm_panic(0x38);
        }
        if (*(uint8_t *)(obj + 0x10) == 0xff) {
            *(uint8_t *)(obj + 0x11) = 0;
            return;
        }
        txm_panic(0x3b);
    } else {
        txm_panic(0x3a);
    }
}

/* ============================================================================
 * Boot-object handle resolve / release (region with magic 0x1337 header).
 * ==========================================================================*/

/* FUN_00024f14 @ 0x00024f14  (est. txm_boot_obj_resolve)
 * Ghidra: short * FUN_00024f14(ulong param_1)
 * Resolves a boot object handle `size` into its data pointer. Acquires the
 * current context region, validates the object header magic 0x1337 (fault
 * 0x59), the size match (fault 0x5a), and releases the context before
 * returning the object payload (header + 8 + size).
 * Confidence: high
 * Notes: 0002988c is a thunk to this function. */
short *txm_boot_obj_resolve(uint64_t size)
{
    uint64_t reg[3];
    short *obj;
    txm_ctx_region_read(reg);
    if (reg[0] != 0) {
        obj = (short *)reg[0];
        short *end = (short *)((uint64_t)obj + (uint64_t)*(uint32_t *)(obj + 2) + 8);
        if (obj + 4 <= end) {
            if (*(short *)obj == 0x1337) {
                if (size == *(uint32_t *)(obj + 2)) {
                    txm_ctx_region_release(reg);
                    return obj + 4;
                }
                txm_panic(0x5a);
            }
            txm_panic(0x59);
        }
    }
    txm_fault(0x19);
}

/* FUN_00024fc8 @ 0x00024fc8  (est. txm_boot_obj_release)
 * Ghidra: void FUN_00024fc8(short *param_1,ulong param_2)
 * Releases a boot object at `obj` of size `size`: validates the magic header
 * 0x1337 (fault 0x59), the size match (fault 0x5a), then frees the enclosing
 * page via txm_slab_free or txm_page_release (FUN_00026a74). Faults 0x5b on
 * an out-of-window pointer and 0x19 on an overflow. 00029894 forwards here.
 * Confidence: high */
void txm_boot_obj_release(short *obj, uint64_t size)
{
    short *hdr = obj - 4;
    if ((uint64_t)obj < 4)
        txm_panic(0x5b);
    if ((uint64_t)obj < (uint64_t)hdr + (size + 8))
        txm_fault(0x19);
    if (*(short *)hdr == 0x1337) {
        if (size == *(uint32_t *)(obj - 2)) {
            txm_mem_commit(hdr, size + 8);
            if ((*(uint8_t *)(obj - 3) & 1) == 0)
                return;
            if (txm_span_is_large(size + 8) == 0) {
                txm_slab_free((uint64_t *)hdr, size + 8);
                return;
            }
            if (hdr != NULL && (uint64_t)hdr < 0xffffffffffffc000) {
                if (((uint64_t)hdr & 0x3fff) == 0) {
                    txm_page_release((uint64_t)hdr, (char *)(size + 8));
                    return;
                }
                txm_panic(0xc0);
            }
            txm_panic(0x42);
        }
        txm_panic(0x5a);
    }
    txm_panic(0x59);
}

/* ============================================================================
 * Panic family.
 * ==========================================================================*/

/* FUN_00029a98 @ 0x00029a98  (est. txm_panic_header_write)
 * Ghidra: void FUN_00029a98(undefined8 param_1,undefined8 param_2)
 * Writes the "TXM [Panic] " header into `buf` (cap `len`) via the fortified
 * snprintf. Returns the number of bytes written.
 * Confidence: high */
int txm_panic_header_write(char *buf, uint64_t len)
{
    return txm_snprintf_chk(buf, 0x100, 0, len, "TXM [Panic] ", NULL);
}

/* FUN_00029784 @ 0x00029784  (est. txm_panic_call)
 * Ghidra: void FUN_00029784(undefined8 param_1,undefined8 param_2)
 * The monitor's panic printer: sets the panic-in-progress flag
 * (DAT_00070690), formats "TXM [Panic] " plus the variadic message into a
 * 0x100-byte buffer, emits it to the console (FUN_0004f304), then faults
 * 0x4b. Noreturn. (000293e8 forwards here.)
 * Confidence: high
 * Notes: the message buffer is zeroed before formatting; a missing NUL
 *   terminator after the format faults 0x19. */
__attribute__((noreturn))
void txm_panic_call(const char *fmt, va_list va)
{
    char buf[0x100];
    int n;
    txm_memset(buf, 0, sizeof buf);
    g_panic_in_progress = 1;              /* DAT_00070690 */
    n = txm_panic_header_write(buf, 0x100);
    if (n < 0x100) {
        int r = txm_snprintf_chk(buf + n, 0x100 - n, 0, 0x100 - (uint64_t)n, fmt, va);
        if ((uint64_t)(long)r < 0x100 - (uint64_t)n) {
            int k = 0;
            for (;;) {
                if (k == 0x100)
                    txm_fault(0x19);
                if (buf[k] == '\0')
                    break;
                k++;
            }
            txm_panic_console(buf);
        }
    }
    txm_panic(0x4b);
}

/* FUN_00029730 @ 0x00029730  (est. txm_panic_msg)
 * Ghidra: void FUN_00029730(undefined8 param_1)
 * Variadic panic entry: forwards to txm_panic_call with the argument list.
 * Noreturn. (0002985c is a no-arg alias, 0002976c a canned-message alias.)
 * Confidence: high */
__attribute__((noreturn))
void txm_panic_msg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    txm_panic_call(fmt, ap);
    va_end(ap);
    __builtin_unreachable();
}

/* FUN_000298ec @ 0x000298ec  (est. txm_panic)
 * Ghidra: void FUN_000298ec(int param_1)
 * The monitor's code-based panic: records the code into the per-CPU state
 * block (fault code 0xa0 additionally writes the cpu-id/state words via
 * txm_state_trap), then faults through txm_panic_msg with the formatted
 * code string "(code: 0x%08X)". Noreturn.
 * Confidence: high */
__attribute__((noreturn))
void txm_panic(uint32_t code)
{
    uint8_t *s = txm_state_base();
    if (code == 0xa0) {
        s[1] = 1;
        if (*s == 0)
            txm_state_trap(0xdeadbeef);
        txm_state_trap(*(uint8_t *)(s + 0x7a));
    }
    txm_panic_msg(" (code: 0x%08X) %u", code, 0);
    __builtin_unreachable();
}

/* FUN_00029a3c @ 0x00029a3c  (est. txm_fault)
 * Ghidra: void FUN_00029a3c(void)
 * The sanitizer-style trap fault: faults through txm_panic_msg with the
 * "trapped due to a sanitizer runtime..." message. Noreturn.
 * Confidence: high */
__attribute__((noreturn))
void txm_fault(uint32_t code)
{
    (void)code;
    txm_panic_msg("trapped due to a sanitizer runtime failure");
    __builtin_unreachable();
}

/* FUN_0002976c @ 0x0002976c  (est. txm_panic_abort)
 * Ghidra: void FUN_0002976c(void)
 * Canned "fatal abort" panic. Noreturn.
 * Confidence: high */
__attribute__((noreturn))
void txm_panic_abort(void)
{
    txm_panic_msg("fatal abort condition issued from the monitor");
    __builtin_unreachable();
}

/* FUN_0002985c @ 0x0002985c  (est. txm_panic_abort_default)
 * Ghidra: void FUN_0002985c(void)
 * No-argument panic alias that forwards to txm_panic_call with no message.
 * Noreturn.
 * Confidence: high */
__attribute__((noreturn))
void txm_panic_abort_default(void)
{
    txm_panic_call("", (va_list)0);
    __builtin_unreachable();
}

/* ============================================================================
 * Version / feature probes.
 * ==========================================================================*/

/* FUN_00029714 @ 0x00029714  (est. txm_version)
 * Ghidra: undefined8 FUN_00029714(void)
 * Returns the TXM build/version constant 0x1800 (6144).
 * Confidence: high */
uint64_t txm_version(void)
{
    return 0x1800;
}

/* FUN_00029724 @ 0x00029724  (est. txm_runtime_enabled)
 * Ghidra: undefined8 FUN_00029724(void)
 * Returns 0; used as a runtime-enabled probe (0 == enabled) across the slab
 * range checks and size-class selectors.
 * Confidence: high */
uint64_t txm_runtime_enabled(void)
{
    return 0;
}

/* FUN_00029750 @ 0x00029750  (est. txm_log_error_code)
 * Ghidra: long FUN_00029750(void)
 * Returns a pointer to the per-CPU state block's log-error word
 * (txm_state_base() + 4).
 * Confidence: high */
uint32_t *txm_log_error_code(void)
{
    return (uint32_t *)(txm_state_base() + 4);
}

/* FUN_0002986c @ 0x0002986c  (est. txm_dit_capability)
 * Ghidra: undefined4 FUN_0002986c(void)
 * Returns 2 if the caller's stack is 128-byte aligned, else 0 — a quick
 * DIT (data-independence-timing) alignment capability probe.
 * Confidence: medium
 * Notes: checks bits 7-13 of a local address (0x3f80 mask). */
uint32_t txm_dit_capability(void)
{
    uint8_t probe;
    if (((uint64_t)&probe & 0x3f80) != 0)
        return 0;
    return 2;
}

/* FUN_000299e4 @ 0x000299e4  (est. txm_dit_available)
 * Ghidra: byte FUN_000299e4(void)
 * Returns whether the DIT feature was detected at platform init
 * (DAT_000104eb bit0).
 * Confidence: high */
uint8_t txm_dit_available(void)
{
    return g_dit_supported & 1;           /* DAT_000104eb */
}

/* FUN_000299fc @ 0x000299fc  (est. txm_lockdown_check)
 * Ghidra: void FUN_000299fc(void)
 * When lockdown is armed (DAT_00071030 bit0) and the lockdown entry word is
 * still clear (DAT_00010518), faults 0x2d. Returns normally otherwise.
 * Confidence: high */
void txm_lockdown_check(void)
{
    if ((g_lockdown_flag & 1) != 0 && g_lockdown_entered == 0)
        txm_panic(0x2d);
}

/* FUN_0002988c @ 0x0002988c  (thunk -> txm_boot_obj_resolve)
 * No-argument alias that forwards to txm_boot_obj_resolve. */
short *txm_boot_obj_resolve_thunk(void)
{
    return txm_boot_obj_resolve(0);
}

/* FUN_00029894 @ 0x00029894  (alias -> txm_boot_obj_release)
 * Forwards to txm_boot_obj_release with default args. */
void txm_boot_obj_release_alias(void)
{
    txm_boot_obj_release((short *)0, 0);
}

/* ============================================================================
 * Early platform / device-tree probes.
 * ==========================================================================*/

/* FUN_00029ad8 @ 0x00029ad8  (est. txm_dt_range_setup)
 * Ghidra: void FUN_00029ad8(long param_1)
 * Sets up the DeviceTree range from the boot descriptor `desc`: computes the
 * aligned end of the region at +0x18, validates the base at +0x10 (non-null,
 * aligned, non-overflowing; faults 0x40-0x43/0xc0), installs the DT root
 * (FUN_0004e880), sets g_dt_setup, and logs. Faults 0x11 if already set up.
 * Confidence: high */
void txm_dt_range_setup(uint64_t desc)
{
    uint64_t base = *(uint64_t *)(desc + 0x10);
    uint64_t end;
    if ((g_dt_setup & 1) != 0) {
        txm_panic(0x11);
    }
    end = (*(uint64_t *)(desc + 0x18) + 0x3fff) & 0xffffffffffffc000;
    if (end < *(uint64_t *)(desc + 0x18)) {
        txm_panic(0x43);
    }
    if (base == 0)
        txm_panic(0x40);
    if (end == 0)
        txm_panic(0x41);
    if (base + end < base)
        txm_panic(0x42);
    if ((base & 0x3fff) != 0)
        txm_panic(0xc0);
    /* FUN_0004e880(&g_dt_root) -- install DT root */
    g_dt_setup = 1;
    txm_log("setup device-tree range");
}

/* FUN_00029b94 @ 0x00029b94  (est. txm_dt_root)
 * Ghidra: undefined8 * FUN_00029b94(void)
 * Returns the DeviceTree root, faulting 0x11 if not set up.
 * Confidence: high */
uint64_t *txm_dt_root(void)
{
    if ((g_dt_setup & 1) != 0)
        return (uint64_t *)g_dt_root;
    txm_panic(0x11);
}

/* FUN_00029bc8 @ 0x00029bc8  (est. txm_dt_debug_enabled)
 * Ghidra: bool FUN_00029bc8(void)
 * Reads the "/chosen/debug-enabled" DeviceTree property; returns its 4-byte
 * value nonzero (true), or logs and returns false if absent/mis-sized.
 * Faults 0x11 if the DT is not set up, 0x29 if /chosen is missing.
 * Confidence: high */
bool txm_dt_debug_enabled(void)
{
    int *val = NULL;
    int len = 0;
    uint64_t node = 0;
    if ((g_dt_setup & 1) == 0)
        txm_panic(0x11);
    if (dt_find_node((uint64_t *)g_dt_root, 0, "/chosen", &node) == 1) {
        if (dt_get_property((uint64_t *)g_dt_root, node, "debug-enabled",
                            (void **)&val, &len) == 1) {
            if (len == 4)
                return *val != 0;
            txm_log("invalid length for debug-enabled property");
        } else {
            txm_log("unable to find debug-enabled property");
        }
        return false;
    }
    txm_panic(0x29);
}

/* FUN_00029c9c @ 0x00029c9c  (est. txm_dt_esdm_fuses)
 * Ghidra: byte FUN_00029c9c(void)
 * Reads the "/chosen/esdm-fuses" DeviceTree property; returns its low bit.
 * Logs and returns 0 if absent/mis-sized; faults 0x11/0x29 as above.
 * Confidence: high */
uint8_t txm_dt_esdm_fuses(void)
{
    uint8_t *val = NULL;
    int len = 0;
    uint64_t node = 0;
    if ((g_dt_setup & 1) == 0)
        txm_panic(0x11);
    if (dt_find_node((uint64_t *)g_dt_root, 0, "/chosen", &node) == 1) {
        if (dt_get_property((uint64_t *)g_dt_root, node, "esdm-fuses",
                            (void **)&val, &len) == 1) {
            if (len == 4) {
                txm_log("acquired valid /chosen esdm fuses property");
                return *val & 1;
            }
            txm_log("invalid length for esdm-fuses property");
        } else {
            txm_log("unable to find esdm-fuses property");
        }
        return 0;
    }
    txm_panic(0x29);
}

/* FUN_00029e48 @ 0x00029e48  (est. txm_dt_darwinos_variant)
 * Ghidra: uint FUN_00029e48(void)
 * Reads the "/chosen/darwinos-security-environment" property; returns its
 * low byte (0 if absent). Faults 0x11/0x29.
 * Confidence: high */
uint32_t txm_dt_darwinos_variant(void)
{
    uint32_t *val = NULL;
    int len = 0;
    uint64_t node = 0;
    if ((g_dt_setup & 1) == 0)
        txm_panic(0x11);
    if (dt_find_node((uint64_t *)g_dt_root, 0, "/chosen", &node) != 1)
        txm_panic(0x29);
    if (dt_get_property((uint64_t *)g_dt_root, node,
                        "darwinos-security-environment", (void **)&val, &len) == 1) {
        if (len == 4) {
            if (*val != 0)
                txm_log("darwinOS variant from device tree");
            return *val & 0xff;
        }
        txm_log("invalid length for darwinos-security-environment property");
    }
    return 0;
}

/* FUN_00029d84 @ 0x00029d84  (est. txm_device_type_resolve)
 * Ghidra: undefined8 FUN_00029d84(void)
 * Resolves the device type: if the darwinOS variant is 6, returns 7;
 * otherwise parses the "/model" property string, validating its bounds and
 * NUL termination (fault 0x19 on overflow), returning 0. Faults 0x11 if the
 * DT is not set up.
 * Confidence: high */
uint64_t txm_device_type_resolve(void)
{
    char *model = NULL;
    int len = 0;
    if ((g_dt_setup & 1) == 0)
        txm_panic(0x11);
    if (txm_dt_darwinos_variant() == 6)
        return 7;
    if (dt_get_property((uint64_t *)g_dt_root, 0, "model",
                        (void **)&model, &len) != 1)
        txm_panic_msg("unable to find /model property in device tree");
    if (model + len <= model)
        txm_fault(0x19);
    for (;;) {
        if (model + len < model + 1)
            txm_fault(0x19);
        if (*model == '\0')
            break;
        model++;
    }
    return 0;
}

/* FUN_00029f28 @ 0x00029f28  (est. txm_dt_security_mode_change)
 * Ghidra: int FUN_00029f28(void)
 * Reads the "/chosen/security-mode-change-enable" property; returns its
 * value (nonzero when security boot-mode change is enabled). Logs and
 * returns 0 if absent/mis-sized. Faults 0x11/0x29.
 * Confidence: high */
int txm_dt_security_mode_change(void)
{
    int *val = NULL;
    int len = 0;
    uint64_t node = 0;
    if ((g_dt_setup & 1) == 0)
        txm_panic(0x11);
    if (dt_find_node((uint64_t *)g_dt_root, 0, "/chosen", &node) == 1) {
        if (dt_get_property((uint64_t *)g_dt_root, node,
                            "security-mode-change-enable", (void **)&val, &len) == 1) {
            if (len == 4) {
                if (*val != 0) {
                    txm_log("security boot-mode environment ...");
                    return *val;
                }
            } else {
                txm_log("invalid length for security-mode-change-enable property");
            }
        }
        return 0;
    }
    txm_panic(0x29);
}

/* ============================================================================
 * TXM platform init (FUN_0002940c) and its externs.
 * ==========================================================================*/

/* Boot-state getters (out of batch; used by txm_platform_init). */
extern uint64_t txm_boot_security_state(void);   /* FUN_0002a280 */
extern uint8_t  txm_boot_security_variant(void); /* FUN_0002a0d8 */
extern int      txm_boot_security_flag(void);    /* FUN_0002a1ac */
extern uint64_t txm_boot_license(void);          /* FUN_0002a514 */
extern void     txm_security_channel_open(void); /* FUN_000239f8 */
extern void     txm_boot_complete(void);         /* FUN_00025ec4 */
extern void     txm_crypto_init(void);           /* FUN_00024000 */
extern void     txm_register_pools(void);        /* FUN_0002cbb8 */
extern void     txm_asid_table_init(uint64_t desc); /* FUN_00020e24 */
extern void     txm_sc_init(void);               /* FUN_000236f0 */
extern void     txm_boot_args_init(uint64_t desc);/* FUN_000207e4 */
extern uint64_t txm_profile_store(uint64_t desc); /* FUN_0002697c */

/* FUN_0002940c @ 0x0002940c  (est. txm_platform_init)
 * Ghidra: void FUN_0002940c(long param_1)
 * The monitor's early platform-init hub: detects DIT support and the ESDM
 * fuse, reads the debug/security device-tree state, validates the boot
 * profile's CRYPTEX region descriptors, and — provided the security-research
 * device is permitted — initializes the ASID table, secure channel, and the
 * slab-pool registry before marking the runtime ready (g_platform_ready = 1).
 * Otherwise faults with "denying security research device". Faults 0x10 if
 * already initialized, 0x19 on descriptor overflow, 0x40-0x42/0xc0 on bad
 * CRYPTEX descriptors.
 * Confidence: high (platform-init hub; many extern sub-steps) */
void txm_platform_init(uint64_t desc)
{
    uint64_t i;
    if ((g_platform_ready & 1) != 0)
        txm_panic(0x10);
    txm_svc();
    txm_profile_store(desc);
    txm_boot_complete();
    g_dit_supported = (*(uint64_t *)(desc + 0x20) & 0xf000000000000) != 0;
    if (g_dit_supported != 0)
        txm_log("system supports DIT feature");
    g_esdm_fuse = (*(uint64_t *)(desc + 0x28) & 0xf00) != 0;
    txm_dt_range_setup(desc);
    txm_boot_args_init(desc);
    if (txm_dt_debug_enabled())
        g_boot_state |= 1;
    if (txm_dt_esdm_fuses())
        g_boot_state |= 2;
    g_platform_variant = txm_boot_security_state();
    g_platform_variant_hi = txm_device_type_resolve();
    if (7 < g_platform_variant_hi)
        txm_panic_msg("unsupported device type (%u)");
    txm_log("resolved system platform identity");

    /* Validate and install each CRYPTEX region descriptor. */
    uint64_t table = *(uint64_t *)(desc + 0x40);
    uint32_t count = *(uint32_t *)(desc + 8);
    if (table + (uint64_t)count * 8 < table)
        txm_fault(0x19);
    for (i = 0; i < count; i++) {
        uint64_t base = *(uint64_t *)(table + i * 8);
        if (base == 0)
            txm_panic(0x40);
        if (base > 0xffffffffffffbfff)
            txm_panic(0x42);
        if ((base & 0x3fff) != 0)
            txm_panic(0xc0);
        /* FUN_0002cb64(&desc, 0x2d); commit the region */
        txm_mem_commit((void *)(base + 0x3c00), 0x3b0);
        /* FUN_000269b4(&desc, 0x4000, 0x2f) -- reserve */
        /* install into the CRYPTEX region table */
        g_cryptex_base = base;
    }
    txm_asid_table_init(desc);
    txm_sc_init();

    if ((txm_boot_security_state() & 1) != 0 ||
        ((txm_dt_debug_enabled() | (txm_boot_license() ^ 1)) & 1) != 0) {
        g_security_research = txm_boot_security_variant();
        g_security_research_flag = (uint8_t)(txm_boot_security_flag() != 0);
        txm_security_channel_open();
        txm_boot_complete();
        txm_crypto_init();
        txm_register_pools();
        g_platform_ready = 1;
        return;
    }
    txm_panic_msg("denying security research device");
}

/* FUN_000293b8 @ 0x000293b8  (est. txm_trace_log)
 * Ghidra: void FUN_000293b8(undefined8 param_1,undefined8 param_2)
 * Forwards to the trace logger (FUN_00025c98) with the current stack frame.
 * Confidence: medium */
void txm_trace_log(uint64_t a, uint64_t b)
{
    extern void txm_log_v(uint64_t arg, uint64_t stack);   /* FUN_00025c98 */
    txm_log_v(b, (uint64_t)&a);
}

/* FUN_000293e8 @ 0x000293e8  (est. txm_panic_with_call)
 * Ghidra: void FUN_000293e8(undefined8 param_1,undefined8 param_2)
 * Panic alias that forwards the message to txm_panic_call. Noreturn.
 * Confidence: high */
__attribute__((noreturn))
void txm_panic_with_call(uint64_t fmt, uint64_t args)
{
    txm_panic_call((const char *)fmt, (va_list)args);
    __builtin_unreachable();
}

/* txm_mem_commit -- memset alias used across the runtime. */
void *txm_mem_commit(void *dst, uint64_t n)
{
    return txm_memset(dst, 0, n);
}
