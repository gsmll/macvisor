/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * SART (System Address Register Translation) region driver + T8110 DART
 * IOMMU register/programming helpers. This file covers the SART region
 * programming/validation state machine and the low-level DART per-client
 * register accessors, TLB-invalidate poll machinery, lock/PS-refcount
 * helpers, and the DART table walk used for guest-I/O VA translation.
 *
 * Function map (Ghidra address -> estimated name):
 *   000c60e4 sptm_sart_validate_region
 *   000c6364 sptm_sart_region_lookup
 *   000c64b4 sptm_sart_region_add
 *   000c68e4 sptm_sart_region_program
 *   000c6a54 sptm_sart_program_regions
 *   000c6e30 sptm_sart_state_init
 *   000c72f0 sptm_dart_disable
 *   000c76ac sptm_dart_clear_error
 *   000c786c sptm_dart_poll
 *   000c7bac sptm_dart_flush           (alias sptm_dart_client_tlb_invalidate)
 *   000c7df8 sptm_dart_read_reg
 *   000c7e5c sptm_dart_write_reg_v1
 *   000c8960 sptm_dart_save_all
 *   000c8a14 sptm_dart_save
 *   000c8ba0 sptm_dart_ctrl_write
 *   000c92e8 sptm_dart_acquire_v1
 *   000c9364 sptm_dart_acquire_v2       (alias sptm_dart_instance_lookup)
 *   000caa9c sptm_dart_lock
 *   000cabb4 sptm_dart_lock_set
 *   000cc2bc sptm_dart_ps_refcount
 *   000cc3f8 sptm_dart_write_field_v1
 *   000cc490 sptm_dart_write_field_v2
 *   000cc540 sptm_dart_write_reg_v2     (value-verify variant)
 *   000cd970 sptm_dart_tt_lookup        (alias sptm_dart_va_to_pte)
 *   000cdd0c sptm_dart_tlb_flush        (alias sptm_dart_tlb_invalidate)
 *   000ce0b4 sptm_dart_flush_cmd
 */

#include <stdint.h>
#include <stddef.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * Shared SPTM helpers (declared here; bodies live in sibling trees).
 * ------------------------------------------------------------------ */

/* FUN_000f8844 — noreturn formatted panic: panic(code, arg, fmt). */
extern void sptm_panic(uint32_t code, uint64_t arg, const char *fmt)
    __attribute__((noreturn));
/* FUN_000f8804 — noreturn assertion failure (message string). */
extern void sptm_assert_fail(const char *msg) __attribute__((noreturn));

/* UnkSytemRegRead/Write — SPTM EL2 IMP-DEF system-register access. */
extern uint64_t sptm_sysreg_read(unsigned int op0, unsigned int op1,
    unsigned int crn, unsigned int crm, unsigned int op2);
extern void DataSynchronizationBarrier(uint64_t a, uint64_t b, uint64_t c);

/* FUN_000abeb0 — memcpy. */
extern void *sptm_memcpy(void *dst, const void *src, size_t n);

/* Opaque SPTM lock primitives (LOAcquire / LORelease). */
extern void sptm_lock_acquire(void);
extern void sptm_lock_release(void);
#define LOAcquire() sptm_lock_acquire()
#define LORelease() sptm_lock_release()

/* FUN_000e4d78 — per-CPU SPTM state base ({x0=base, x1=dbg}); the DART/SART
 * control block lives at base+0x10. */
extern void *sptm_percpu_base(uint64_t hint, uint64_t *dbg_out);

/* FUN_000e56ac — take an IOMMU page reference for `type` (1=4KB, 2=2MB). */
extern void sptm_iommu_page_ref(uint64_t paddr, uint32_t type);

/* FUN_000e40ec — translate a physical address to its SPTM virtual address
 * ({va,err}). */
extern uintptr_t sptm_va_lookup(uintptr_t pa);

/* Device-tree helpers. FUN_000b79e8 = sptm_dt_find_node; FUN_000b7c04 =
 * sptm_dt_get_prop; FUN_000b7898 = DT next-node iterator. */
extern int sptm_dt_find_node(uintptr_t iter, uintptr_t parent,
    const char *name, uintptr_t *out);
extern int sptm_dt_get_prop(uintptr_t node, const char *name,
    uintptr_t *out_val, uint32_t *out_size, uintptr_t iter, uintptr_t ctx);
extern int sptm_dt_next_node(uintptr_t state, uintptr_t *node, void *stack); /* FUN_000b7898 */

/* SART/DART address-map helpers used by the state init. */
extern uint64_t sptm_phys_map_va(uintptr_t percpu, uint64_t paddr, uint32_t size); /* FUN_000e63c8 */
extern uint64_t sptm_va_to_phys(uint64_t va, uint32_t pages, uint32_t flag);      /* FUN_000e45a8 */
extern void sptm_helper_e4424(const char *s);                                      /* FUN_000e4424 (debug print) */

/* ------------------------------------------------------------------ *
 * Shared SPTM globals (Ghidra DAT_ symbols; addresses in comments).
 * ------------------------------------------------------------------ */

/* DAT_00095d18 / DAT_00095d20 — SPTM physical memory window [low, high). */
extern uint64_t sptm_mem_low;
extern uint64_t sptm_mem_high;
/* DAT_00095110 — SPTM direct-map virtual base (paddr - mem_low + base). */
extern uint64_t sptm_direct_map_base;
/* DAT_001012d8 / DAT_00101ac8 / DAT_00101ad0 — memory-map feature flag and
 * the non-linear translation descriptor table. */
extern uint32_t sptm_mem_feature;
extern uint64_t sptm_region_count;
extern uint64_t sptm_regions[];   /* stride 3 u64: {start, physbase, pages} */
/* DAT_000130d8 / DAT_000130f8 — per-level VA<->index shift/mask tables. */
extern uint64_t sptm_pt_shifts[];
extern uint32_t sptm_pt_shifts_lo[];

/* SART driver state base (DAT_00094cc8). Bytes used as an addressable block.
 * Layout fields referenced below:
 *   +0x10..  region-entry array (5 u32 per region, see sptm_sart_region_program)
 *   +0x1f0  live region count
 *   +0x1f8  SART register-map VA base
 *   +0x200  SART register-map size (bytes)
 *   +0x204  throttle version, +0x208 throttle offset, +0x210 throttle VA,
 *   +0x218 power-canary size, +0x21c power-canary offset, +0x220 ..,
 *   +0x224 power-canary-present flag, +0x228 throttle-reg array (copied)
 *   +0x238  SART register descriptor base (version-scaled table +0x13028)
 *   +0x240  throttle register descriptor base (+0x12f78)
 *   +0x248  region-program mode (0=off, 1=on), +0x24a per-CPU guard
 */
extern uint8_t sptm_sart_state[];        /* DAT_00094cc8 */
/* DAT_00094cc0 — "exclusive bounds" SART validation flag (set when the
 * device tree does NOT supply an "exclusive-bounds" property). */
extern uint32_t sptm_sart_exclusive_bounds; /* DAT_00094cc0 */
/* T8110 DART instance-validation table (DAT_00094ec0): -1/0xff => invalid. */
extern uint8_t sptm_dart_valid_instances[]; /* DAT_00094ec0 */

/* DAT_00094ab8 — device-tree iteration state {iter, ctx}. */
extern uintptr_t sptm_dt_state[2];       /* DAT_00094ab8 */

/* Per-CPU SPTM state base read from the EL2 IMP-DEF sysreg pair. */
static inline uint8_t *
sptm_cur_cpu_state(void)
{
    uintptr_t b = sptm_sysreg_read(3, 6, 0xf, 8, 0);
    if (b == 0) {
        return (uint8_t *)__builtin_arm_rsr64("tpidr_el2");
    }
    return (uint8_t *)sptm_sysreg_read(3, 6, 0xf, 0xb, 1);
}

/* s_uat_instance_>handoff_region_>mi_0000142e — per-CPU state-guard token
 * table (indexed by [cpu_state + 10]); bitshifted+1 forms the guard value. */
extern const uint8_t sptm_guard_token[]; /* s_uat_instance_>handoff_region_>mi_0000142e */

/* Take/release the SART/DART per-CPU reentrancy guard at state+0x24a. */
static inline void
sptm_take_guard(uint8_t *state, uint64_t err)
{
    uint8_t *cpu = sptm_cur_cpu_state();
    if (*(state + 0x24a) != 0) {
        sptm_panic(0x200000a, err, "%s %s %s %d %s %llx %s %s %llx");
    }
    *(state + 0x24a) = (uint8_t)(sptm_guard_token[cpu + 10] << 1 | 1);
}

static inline void
sptm_release_guard(uint8_t *state)
{
    uint8_t *cpu = sptm_cur_cpu_state();
    if (*(state + 0x24a) != (uint8_t)(sptm_guard_token[cpu + 10] << 1 | 1)) {
        sptm_assert_fail("state guard release %llx");
    }
    *(state + 0x24a) = 0;
}

/* DART PS (power-state) refcount descriptor table. DAT_001012b4 = count;
 * DAT_001012b8 = table base, stride 6 bytes: {u16 reg-offset, u8 ctrl-idx,
 * u8 bit, ...}. DAT_001012c0 is a guard slot. */
extern uint32_t sptm_dart_ps_wr_count;       /* DAT_001012b4 */
extern const uint8_t sptm_dart_ps_wr_table[];/* DAT_001012b8, stride 6 */

/* DAT_00015530 — per-policy DART flush descriptor table (stride 0x20; the
 * first byte of each entry is the poll-mode: 1 => check +0x604, else +0x80). */
extern const uint8_t sptm_dart_policy_desc[]; /* DAT_00015530, stride 0x20 */

/* DAT_00012f40 / DAT_00012f48 — legacy (v1) DART TLB-invalidate command
 * words used by sptm_dart_tlb_flush on < 0x300 DART revisions. */
extern uint64_t sptm_dart_tlb_cmd0;          /* DAT_00012f40 */
extern uint64_t sptm_dart_tlb_cmd1;          /* DAT_00012f48 */

/* Fixed SPTM diagnostic format strings (kept as comments-only markers;
 * the panic engine resolves the leading %s/%s/%d from the caller PC). */
#define SPTM_FMT_LLX  "%s %s %s %d %s %llx %s %s %llx"

/* Forward declarations (mutually-recursive DART helpers). */
int  sptm_dart_poll(void *ctrl, uint64_t phase);
int  sptm_dart_flush(void *ctrl, uint32_t client, uint32_t policy, uint64_t flags);
uint32_t sptm_dart_read_reg(void *ctrl, uint32_t client, uint32_t reg);
void sptm_dart_write_reg_v1(void *ctrl, uint32_t client, uint32_t reg, uint32_t val);
void sptm_dart_save(void *ctrl, uint32_t client);
void sptm_dart_flush_cmd(void *ctrl, void *cmd);

/* ------------------------------------------------------------------ *
 * SART region functions.
 * ------------------------------------------------------------------ */

/* FUN_000c60e4 @ 0x000c60e4   (sptm_sart_validate_region)
 * Ghidra: void FUN_000c60e4(ulong,ulong,ulong*,ulong*)
 * Validate/unpack a SART region request. Requires `paddr` 16K-aligned and
 * inside [sptm_mem_low, sptm_mem_high); requires `size` (>=1, 16K-aligned)
 * to fit within the SART register map (regs-size * 0x1000) and to stay
 * inside the SART register window. On success stores the validated range
 * back: *out_va = paddr, *out_paddr = size. Panics on any violation.
 * Confidence: medium
 * Notes: reads SART state (DAT_00094cc8) +0x238 descriptor (regs-size at
 *   +0x1c, base at +0x28); sart_regs_size<<12 is the map byte length. */
void
sptm_sart_validate_region(uint64_t paddr, uint64_t size,
    uint64_t *out_va, uint64_t *out_paddr)
{
    uint8_t *st = sptm_sart_state;
    uint8_t *desc = *(uint8_t **)(st + 0x238);
    uint32_t regs_size = *(uint32_t *)(desc + 0x1c) << 12;   /* map length (bytes) */
    uint32_t regs_base = *(uint32_t *)(desc + 0x28) << 12;   /* map base (bytes) */
    uint64_t last = size - 1;

    if (((paddr & 0x3fff) != 0) || (paddr < sptm_mem_low) || (sptm_mem_high <= paddr)) {
        sptm_panic(6, size, SPTM_FMT_LLX);
    }
    if (regs_size <= last) {
        sptm_panic(0x12, size, SPTM_FMT_LLX);
    }
    if ((paddr + last) >= paddr && (size & 0x3fff) == 0) {
        if (regs_base < paddr) {
            sptm_panic(0x2000001, size, SPTM_FMT_LLX);
        }
        if (size <= regs_size) {
            if ((paddr + last) >= sptm_mem_low && (paddr + last) < sptm_mem_high) {
                *out_va = paddr;
                *out_paddr = size;
                return;
            }
            sptm_panic(6, size, "%s %s %s %d %s %llx");
        }
    }
    sptm_panic(0x2000003, size, SPTM_FMT_LLX);
}

/* FUN_000c6364 @ 0x000c6364   (sptm_sart_region_lookup)
 * Ghidra: void FUN_000c6364(int,uint*,uint*,int*)
 * Look up a SART region by id and return its stored offsets: *out0 = the
 * size/perm word at the primary region slot, *out1 = the offset word at the
 * auxiliary slot, *out2 = the region size (in 16K pages) read from the size
 * slot. Panics on an invalid SART offset or (when DAT_00094cc0 set) an
 * invalid size-region.
 * Confidence: medium
 * Notes: reads SART descriptors from the +0x238/+0x1f8 register tables;
 *   the DAT_00094cc0 flag gates the size-region validity check. */
void
sptm_sart_region_lookup(uint32_t id, uint32_t *out0, uint32_t *out1, uint32_t *out2)
{
    uint8_t *st = sptm_sart_state;
    uint8_t *desc = *(uint8_t **)(st + 0x238);
    uint32_t map_size = *(uint32_t *)(st + 0x200);
    uint32_t *map = *(uint32_t **)(st + 0x1f8);
    uint32_t prim = *(int32_t *)(desc + 8) + id * *(uint8_t *)(desc + 0xc);
    uint32_t aux, size_slot;
    uint8_t shift;
    uint32_t mask;
    uint32_t off;

    if (((prim & 3) != 0) || (prim >= map_size)) {
        sptm_assert_fail("Invalid SART offset %x");
    }
    uint32_t prim_val = map[prim / 4];
    if (*(int32_t *)(desc + 0x14) == 0) {
        /* Single region table: mask the size field out of the primary slot. */
        shift = *(uint8_t *)(desc + 0x19);
        mask  = *(uint32_t *)(desc + 0x1c);
        off   = prim_val & ~(mask << (shift & 0x1f));
        aux   = prim_val;
    } else {
        aux = *(int32_t *)(desc + 0x14) + id * *(uint8_t *)(desc + 0x18);
        if ((aux >= map_size) || (aux & 3) != 0) {
            sptm_assert_fail("Invalid SART offset %x");
        }
        shift = *(uint8_t *)(desc + 0x19);
        mask  = *(uint32_t *)(desc + 0x1c);
        off   = map[aux / 4] >> (shift & 0x1f) & mask;
    }
    uint32_t size = off;
    if ((sptm_sart_exclusive_bounds & 1) != 0) {
        size = size + 1;
        if (size != (uint32_t)(size * 0x80000000 >> 0x1f)) {
            sptm_assert_fail("Invalid SART size region %d");
        }
    }
    size_slot = *(int32_t *)(desc + 0x20) + id * *(uint8_t *)(desc + 0x24);
    if ((size_slot < map_size) && (size_slot & 3) == 0) {
        shift = *(uint8_t *)(desc + 0x25);
        mask  = *(uint32_t *)(desc + 0x28);
        *out0 = (uint32_t)off;   /* the (masked) primary word */
        *out1 = map[size_slot / 4] >> (shift & 0x1f) & mask;
        *out2 = size;
        return;
    }
    sptm_assert_fail("Invalid SART offset %x");
}

/* FUN_000c64b4 @ 0x000c64b4   (sptm_sart_region_add)
 * Ghidra: void FUN_000c64b4(undefined8,undefined8,uint,uint)
 * Program a new SART region into the live region table. Validates
 * [paddr,paddr+size) (sptm_sart_validate_region), takes the per-CPU state
 * guard, accounts the optional power-canary page, issues an IOMMU page-ref
 * (1=4KB or 2=2MB per mode) for each 16K block, then fills a free region
 * entry with {paddr>>12, size>>12, mode, flags, perm-bits} and bumps the
 * live region count. `mode` is 0 or 1 (0x2000004/0x2000005 panic otherwise);
 * `flags` must be < 2. Panics on region overflow / state-guard mismatch.
 * Confidence: medium
 * Notes: state+0x24a guard; DAT_00094cc8+0x89 "has power canary" bit and the
 *   +0x84/+0x87 overflow accounting; per-page refs via FUN_000e56ac; region
 *   entries at DAT_00094cc8+0x10 (5 u32 stride); live count at +0x7c. */
void
sptm_sart_region_add(uint64_t paddr, uint64_t size, uint32_t mode, uint32_t flags)
{
    uint8_t *st = sptm_sart_state;
    uint64_t va = 0, sz = 0;
    uint64_t cur;
    uint32_t idx, type;

    sptm_sart_validate_region(paddr, size, &va, &sz);
    if (mode > 1) {
        sptm_panic(0x2000004, 0, SPTM_FMT_LLX);
    }
    if (flags >= 2) {
        sptm_panic(0x2000005, 0, SPTM_FMT_LLX);
    }

    type = 1;
    if (mode == 1) {
        type = 2;   /* 2MB blocks for mode 1 */
    }

    sptm_take_guard(st, 0);

    /* Power-canary page accounting (+0x89 flag, +0x88 counter). */
    if ((flags == 1) && (*(st + 0x89) & 1) != 0) {
        uint32_t n = *(uint32_t *)(st + 0x88 * 4);
        if (n == 0) {
            *(uint32_t *)(*(uint64_t *)(st + 0x84) + *(uint32_t *)(st + 0x87)) = 0xabfedeed;
            n = *(uint32_t *)(st + 0x88 * 4);
        }
        uint64_t v = (uint64_t)n + 1;
        *(uint32_t *)(st + 0x88 * 4) = (uint32_t)v;
        if (v != (uint64_t)(v * 0x80000000 >> 0x1f)) {
            sptm_assert_fail("overflow");
        }
    }

    /* IOMMU page-ref each 16K block of the new region. */
    if (sz > 0x3fff) {
        uint64_t blocks = sz >> 0xe;
        uint64_t p = va;
        do {
            sptm_iommu_page_ref(p, type);
            p += 0x4000;
            blocks--;
        } while (blocks != 0);
    }

    /* Find a free (zeroed) region entry and fill it. */
    uint8_t *desc = *(uint8_t **)(st + 0x8e);
    uint32_t nregs = *(uint8_t *)(desc + 4);
    for (idx = 0; idx < nregs; idx++) {
        if ((*(uint32_t *)(st + 0x10 + (uint64_t)idx * 0x14 + 0x0) == 0) &&
            (*(uint32_t *)(st + 0x10 + (uint64_t)idx * 0x14 + 0x4) == 0)) {
            uint32_t *e = (uint32_t *)(st + 0x10 + (uint64_t)idx * 0x14);
            uint8_t b2, b3, b4, b5, b6;

            e[0] = (uint32_t)(va >> 0xc);
            b2 = *(uint8_t *)(desc + 0x11);
            b3 = *(uint8_t *)(desc + 0x10);
            b4 = *(uint8_t *)(desc + 0xe);
            b5 = *(uint8_t *)(desc + 0xf);
            b6 = *(uint8_t *)(desc + 0xd);
            e[1] = mode;
            e[2] = flags;
            e[3] = (uint32_t)(sz >> 0xc);
            e[4] = (1u << (b3 & 0x1f)) | (1u << (b2 & 0x1f)) |
                   (2u + (mode == 1) << (b4 & 0x1f)) |
                   (2u + (mode == 1) << (b5 & 0x1f)) |
                   (2u + (mode == 1) << (b6 & 0x1f));
            sptm_sart_region_program(idx);

            /* Bump and bound the live region count. */
            uint32_t cnt = *(uint32_t *)(st + 0x7c * 4);
            *(uint32_t *)(st + 0x7c * 4) = cnt + 1;
            if (*(uint8_t *)(*(uint64_t *)(st + 0x8e) + 4) < cnt + 1) {
                sptm_assert_fail("n_region_overflow");
            }
            sptm_release_guard(st);
            return;
        }
    }
    sptm_release_guard(st);
    sptm_panic(0x2000007, 0, SPTM_FMT_LLX);
}

/* FUN_000c68e4 @ 0x000c68e4   (sptm_sart_region_program)
 * Ghidra: void FUN_000c68e4(uint)
 * Write a SART region entry (id `id`) into the SART register-map table at
 * DAT_00094cc8+0x1f8: copies the stored size/perm word into the primary slot
 * and the offset/flag words into the auxiliary/size slots, OR-ing the size
 * field. Panics on an invalid SART offset.
 * Confidence: medium
 * Notes: region entry layout at DAT_00094cc8+0x10 (stride 0x14): +0x18 size,
 *   +0x14 offset, +0x1c perm; DAT_00094cc0 gates the size decrement. */
void
sptm_sart_region_program(uint32_t id)
{
    uint8_t *st = sptm_sart_state;
    uint8_t *desc = *(uint8_t **)(st + 0x238);
    uint32_t map_size = *(uint32_t *)(st + 0x200);
    uint32_t *map = *(uint32_t **)(st + 0x1f8);
    uint32_t *e = (uint32_t *)(st + 0x10 + (uint64_t)id * 0x14);
    uint32_t prim = *(int32_t *)(desc + 8) + id * *(uint8_t *)(desc + 0xc);
    uint32_t aux, size_slot;
    uint8_t shift;
    uint32_t mask;
    uint32_t size_word;

    if (((prim & 3) != 0) || (prim >= map_size)) {
        sptm_assert_fail("Invalid SART offset %x");
    }
    map[prim / 4] = e[1];   /* +0x18 word -> primary slot */

    aux = *(int32_t *)(desc + 0x20) + id * *(uint8_t *)(desc + 0x24);
    if (((aux & 3) != 0) || (aux >= map_size)) {
        sptm_assert_fail("Invalid SART offset %x");
    }
    map[aux / 4] = (*(uint32_t *)(desc + 0x28) & e[2]) << (*(uint8_t *)(desc + 0x25) & 0x1f);

    size_word = (*(uint32_t *)(desc + 0x1c) & e[0]) << (*(uint8_t *)(desc + 0x19) & 0x1f);
    if ((sptm_sart_exclusive_bounds & 1) != 0) {
        if (size_word == 0) {
            sptm_assert_fail("Invalid SART size region %d");
        }
        size_word = size_word - 1;
    }
    if (*(int32_t *)(desc + 0x14) == 0) {
        size_slot = *(int32_t *)(desc + 8) + prim;
        if (((size_slot & 3) != 0) || (size_slot >= map_size)) {
            sptm_assert_fail("Invalid SART offset %x");
        }
        size_word = size_word | e[1];
    } else {
        size_slot = *(int32_t *)(desc + 0x14) + id * *(uint8_t *)(desc + 0x18);
        if (((size_slot & 3) != 0) || (size_slot >= map_size)) {
            sptm_assert_fail("Invalid SART offset %x");
        }
    }
    map[size_slot / 4] = size_word;
}

/* FUN_000c6a54 @ 0x000c6a54   (sptm_sart_program_regions)
 * Ghidra: void FUN_000c6a54(byte,undefined8)
 * Enable (mode==1) or disable (mode==0) SART region programming. With mode 1
 * and the "bootloader regions" path (state+0x249 bit0 clear) it validates and
 * copies the bootloader SART region/throttle configuration from the
 * descriptor tables into the live region table and throttle-reg array; with
 * bit0 set it re-programs existing regions. mode==1 with no prior state just
 * arms the region table (state+0x248 = 1). Guards the whole operation with
 * the per-CPU state guard.
 * Confidence: medium
 * Notes: reads the bootloader region table (DAT_00094cc8+0x238 desc +0x1f8
 *   map); throttle config via DAT_00094cc8+0x240 desc and +0x208 offset;
 *   copies throttle regs into +0x228..; sets +0x248 mode word. */
void
sptm_sart_program_regions(uint8_t mode, uint64_t err)
{
    uint8_t *st = sptm_sart_state;
    uint8_t *desc;
    uint32_t map_size;
    uint32_t *map;
    uint8_t nregs;
    uint32_t id;

    sptm_take_guard(st, err);
    if (mode > 1) {
        sptm_panic(0x200000d, err, SPTM_FMT_LLX);
    }

    if (mode == 1) {
        desc = *(uint8_t **)(st + 0x238);
        if ((*(st + 0x249) & 1) == 0) {
            /* Bootloader-region path: pull regions + throttle config. */
            if (*(int8_t *)(desc + 4) != 0) {
                for (id = 0; id < (uint8_t)*(int8_t *)(desc + 4); id++) {
                    uint32_t lo = 0, lc = 0, sz = 0;
                    sptm_sart_region_lookup(id, &lo, &lc, &sz);
                    if (((lc != 0 || sz != 0) && lo != 0)) {
                        uint32_t pages = (sz >> 2) & 0x3ffff;
                        if ((int32_t)pages != 0) {
                            uint64_t p = (uint64_t)lc << 0xc;
                            do {
                                if ((p >= sptm_mem_low) && (p < sptm_mem_high)) {
                                    sptm_assert_fail("Invalid bootloader mapping c");
                                }
                                p += 0x4000;
                                pages--;
                            } while (pages != 0);
                        }
                        *(int32_t *)(st + 0x1f0) += 1;
                        uint32_t *e = (uint32_t *)(st + 0x10 + (uint64_t)id * 0x14);
                        e[0] = lc;
                        e[1] = sz;
                        e[2] = lo;
                    }
                }
            }
            *(uint16_t *)(st + 0x248) = 0x101;
            uint8_t *thr = *(uint8_t **)(st + 0x240) + 0x18;
            uint32_t n = **(uint8_t **)(st + 0x240);
            if (n == 0) {
                sptm_assert_fail("Sart invalid throttle regs");
            }
            uint32_t base = *(int32_t *)(st + 0x208);
            map_size = *(uint32_t *)(st + 0x200);
            for (uint32_t i = 0; i < n; i++) {
                uint32_t off = *(int32_t *)(thr + i * 4) + base;
                if (((off & 3) != 0) || (off >= map_size)) {
                    sptm_assert_fail("Invalid SART offset %x");
                }
                map = *(uint32_t **)(st + 0x1f8);
                if (map[off / 4] == 0) {
                    sptm_assert_fail("Sart invalid throttle cfg");
                }
            }
            /* Copy the throttle register words into state+0x228.. */
            uint32_t *dst = (uint32_t *)(st + 0x228);
            uint32_t i = 0;
            do {
                uint32_t off = *(int32_t *)thr + base;
                if ((off & 3) != 0 || off >= map_size) {
                    sptm_assert_fail("Invalid SART offset %x");
                }
                *dst = map[off / 4];
                i++;
                dst++;
                thr += 4;
            } while (i < n);
        } else {
            /* Re-program existing regions. */
            if (*(int8_t *)(desc + 4) != 0) {
                for (id = 0; id < (uint8_t)*(int8_t *)(desc + 4); id++) {
                    if (*(int32_t *)(st + 0x10 + (uint64_t)id * 0x14) != 0) {
                        sptm_sart_region_program(id);
                    }
                }
            }
            *(uint8_t *)(st + 0x248) = 1;
        }
    } else {
        *(uint8_t *)(st + 0x248) = 0;
    }
    sptm_release_guard(st);
}

/* FUN_000c6e30 @ 0x000c6e30   (sptm_sart_state_init)
 * Ghidra: undefined8 FUN_000c6e30(void)
 * Initialize the SART driver state from the device tree. Looks up the
 * "arm-io-sart" node and reads its sart-version / sart-throttle-version /
 * sart-throttle-offset / power-canary-offset / regs properties, maps the SART
 * register window and (when present) the power-canary window, validates the
 * version-scaled descriptor offsets, and records the "exclusive-bounds" flag
 * (DAT_00094cc0). Returns 0 on success; panics on any malformed DT input.
 * Confidence: medium
 * Notes: DT props read via sptm_dt_find_node/sptm_dt_get_prop; maps via
 *   FUN_000e63c8 (phys->va) and FUN_000e45a8 (va->phys, 0xffffffff on fail);
 *   descriptor bases computed as (version-1)*0x2c + 0x13028 / 0x12f78. */
int
sptm_sart_state_init(void)
{
    uint8_t *st;
    uint32_t regs_size, thr_size;
    uint32_t *pu;
    uint32_t ver;
    uint32_t thr_ver;
    uint32_t thr_off;
    uint32_t pc_off;
    uintptr_t node = 0, out = 0;
    uintptr_t *desc = NULL;
    uint32_t sz = 0;
    uint64_t va, va_pc;

    sptm_helper_e4424("SART state init");
    st = (uint8_t *)sptm_percpu_base(0, NULL);
    sptm_sart_state = st;   /* DAT_00094cc8 = per-cpu base */
    *(st + 0x24a) = 0;
    *(uint32_t *)(st + 0x1f0) = 0;

    if (sptm_dt_state == NULL || sptm_dt_state[0] == 0) {
        sptm_assert_fail("error %d looking up %s");
    }
    out = sptm_dt_state[0];
    if (sptm_dt_next_node((uintptr_t)sptm_dt_state, &out, (void *)&out) != 1) {
        sptm_assert_fail("error %d looking up %s");
    }

    out = 0;
    if (sptm_dt_find_node((uintptr_t)sptm_dt_state, 0, "arm-io-sart", &out) != 1) {
        sptm_assert_fail("error %d looking up %s");
    }
    uintptr_t sart_node = out;

    pu = NULL;
    sz = 0;
    if (sptm_dt_get_prop(out, "sart-version", &out, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) != 1) {
        sptm_assert_fail("error %d looking up %s");
    }
    if (sz != 4) {
        sptm_assert_fail("DT property %s has illegal");
    }
    *(uint32_t *)(st + 500) = *(uint32_t *)out;

    if (sptm_dt_get_prop(out, "sart-throttle-version", &out, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) == 1) {
        if (sz != 4) {
            sptm_assert_fail("DT property %s has illegal");
        }
        pu = (uint32_t *)out;
    } else {
        pu = (uint32_t *)(st + 500);
    }
    *(uint32_t *)(st + 0x204) = *pu;

    if (sptm_dt_get_prop(out, "sart-throttle-offset", &out, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) == 1) {
        if (sz != 4) {
            sptm_assert_fail("DT property %s has illegal");
        }
        thr_off = *(uint32_t *)out;
    } else {
        thr_off = 0;
    }
    *(uint32_t *)(st + 0x208) = thr_off;

    *(bool *)(st + 0x224) =
        sptm_dt_get_prop(out, "power-canary-offset", &out, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) == 1;

    desc = NULL;
    if (sptm_dt_get_prop(out, "regs", &desc, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) != 1) {
        sptm_assert_fail("error %d looking up %s");
    }
    if (sz < (*(st + 0x224) & 1) ? 0x20 : 0x10) {
        sptm_assert_fail("DT property %s has illegal");
    }

    regs_size = (uint32_t)desc[1];
    *(uint32_t *)(st + 0x200) = regs_size;
    if (regs_size >> 0xe == 0) {
        sptm_assert_fail("Illegal SART Register Size");
    }
    va = sptm_phys_map_va((uintptr_t)sptm_percpu_base(0, NULL), desc[0],
        (uint32_t)desc[1]);

    if ((*(st + 0x224) & 1) != 0) {
        uint32_t pc_size = (uint32_t)desc[3];
        *(uint32_t *)(st + 0x218) = pc_size;
        if (pc_size >> 0xe == 0) {
            sptm_assert_fail("Illegal SART Register Size");
        }
        va_pc = sptm_phys_map_va((uintptr_t)sptm_percpu_base(0, NULL), desc[2],
            (uint32_t)desc[3]);
        uint64_t pc_va = sptm_va_to_phys(va_pc, pc_size >> 0xe, 0);
        *(uint64_t *)(st + 0x210) = pc_va;
        if (pc_va == 0xffffffff) {
            sptm_assert_fail("%s invalid papt returned by");
        }
        uint32_t *pco = NULL;
        if (sptm_dt_get_prop(out, "power-canary-offset", &pco, &sz,
                sptm_dt_state[0], sptm_dt_state[1]) != 1) {
            sptm_assert_fail("error %d looking up %s");
        }
        if (sz != 4) {
            sptm_assert_fail("DT property %s has illegal");
        }
        *(uint32_t *)(st + 0x21c) = *pco;
    }

    /* "exclusive-bounds" absent => set DAT_00094cc0. */
    sptm_sart_exclusive_bounds =
        sptm_dt_get_prop(out, "exclusive-bounds", &desc, &sz,
            sptm_dt_state[0], sptm_dt_state[1]) != 1;

    uint64_t map_va = sptm_va_to_phys(va, regs_size >> 0xe, 0);
    *(uint64_t *)(st + 0x1f8) = map_va;
    if (map_va != 0xffffffff) {
        ver = *(uint32_t *)(st + 500);
        if (ver - 5 <= 0xfffffffb) {
            /* Version 5..0x1fffffff supported; compute scaled descriptor base. */
            *(uint64_t *)(st + 0x238) = (uint64_t)(ver - 1) * 0x2c + 0x13028;
            thr_ver = *(uint32_t *)(st + 0x204);
            if (thr_ver - 5 <= 0xfffffffb) {
                *(uint64_t *)(st + 0x240) = (uint64_t)(thr_ver - 1) * 0x2c + 0x12f78;
                *(uint32_t *)(st + 0x220) = 0;
                *(uint16_t *)(st + 0x248) = 0;
                return 0;
            }
        }
        sptm_assert_fail("Invalid SART version %d from");
    }
    sptm_assert_fail("%s invalid papt returned by");
}

/* ------------------------------------------------------------------ *
 * T8110 DART register / TLB helpers.
 * ------------------------------------------------------------------ */

/* DART per-client hardware base: ctrl+0x8 + idx*0x78, PAC-checked. */
static inline uint32_t *
sptm_dart_client_hw(uint8_t *ctrl, uint32_t idx)
{
    uintptr_t p = (uintptr_t)(ctrl + 8 + (uint64_t)idx * 0x78);
    /* PAC address-mask: restore the pointer-authenticated tag. */
    if (((uintptr_t)ctrl + 8 ^ p) & 0xffc0000000000000) {
        p = (p & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
    }
    return (uint32_t *)p;
}

/* FUN_000c72f0 @ 0x000c72f0   (sptm_dart_disable)
 * Ghidra: void FUN_000c72f0(byte,undefined8)
 * Tear down / disable a DART instance (id `dart_id`): for each configured
 * client writes 0xffffffff to its error register (offset +0xbc4) and 0 to its
 * fault register (offset +0xbcc), clearing pending DART errors. Validates the
 * instance id against the DAT_00094ec0 table first. Returns quietly if the
 * instance has no configured clients.
 * Confidence: medium
 * Notes: instance id resolved through sptm_dart_valid_instances; per-CPU
 *   ctrl block from sptm_percpu_base; client hw pointers at ctrl+0x8 (stride
 *   0x78); client count at ctrl+0xba4. */
void
sptm_dart_disable(uint8_t dart_id, uint64_t err)
{
    uint8_t *ctrl;
    uint32_t n;
    uint32_t idx;

    if (sptm_dart_valid_instances[dart_id] == 0xff) {
        sptm_panic(0x6000006, err, "%s %s %s %d %s %llx");
    }
    ctrl = (uint8_t *)sptm_percpu_base(sptm_dart_valid_instances[dart_id], NULL);
    ctrl = *(uint8_t **)(ctrl + 0x10);
    if (*(int32_t *)(ctrl + 0xba4) != 0) {
        n = *(uint32_t *)(ctrl + 0xba4);
        uint64_t slot = 8;
        idx = 0;
        do {
            uint32_t *hw = *(uint32_t **)(ctrl + slot);
            hw[(*(uint32_t *)(ctrl + 0xbc4) & 0xfffffffc) / 4] = 0xffffffff;
            if (*(uint32_t *)(ctrl + 0xba4) <= idx) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            hw[(*(uint32_t *)(ctrl + 0xbcc) & 0xfffffffc) / 4] = 0;
            if (*(uint32_t *)(ctrl + 0xba4) <= idx) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            idx++;
            slot += 0x78;
        } while (idx < *(uint32_t *)(ctrl + 0xba4));
    }
}

/* FUN_000c76ac @ 0x000c76ac   (sptm_dart_clear_error)
 * Ghidra: void FUN_000c76ac(long,undefined8)
 * Clear a pending DART error condition on `ctrl`: takes the per-CPU state
 * guard, optionally serializes the flush machinery (LO lock + memcpy of a
 * 0x18-byte flush command), then polls the flush completion. Refuses to run
 * on the "flush unlocked" revision ((*(ushort*)(ctrl+0xbdc) & 0xfffe) == 0x100).
 * Confidence: medium
 * Notes: ctrl+0xbdc DART version; ctrl+0xbdf guard; ctrl+0xbe0 mode (2 =
 *   already serialized); ctrl+0xc2c serialization mask; FUN_000c786c poll. */
void
sptm_dart_clear_error(void *ctrl)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint16_t vers;
    int rc;

    if ((*(uint16_t *)(c + 0xbdc) & 0xfffe) == 0x100) {
        sptm_assert_fail("dart %s %d %s %u Flush Unlocked");
    }
    uint64_t flush_cmd[3] = { 0, 0, 0x40000000000 };
    sptm_take_guard(c, 0);
    if (*(int8_t *)(c + 0xbe0) != 2) {
        LOAcquire();
        vers = *(uint16_t *)(c + 0xc2c);
        *(uint16_t *)(c + 0xc2c) = vers | 1;
        LORelease();
        if ((vers & 1) != 0) {
            sptm_assert_fail("dart %s %d %s %u Not serialized");
        }
        sptm_memcpy(c + 0xbfc, &flush_cmd, 0x18);
    }
    do {
        rc = sptm_dart_poll(c, 0);
    } while (rc == 0);
    sptm_release_guard(c);
}

/* FUN_000c786c @ 0x000c786c   (sptm_dart_poll)
 * Ghidra: undefined8 FUN_000c786c(long,ulong)
 * Poll/advance the DART TLB-flush state machine for `ctrl`. If the machine is
 * already busy (guard bit at +0xbe2) or still flushing (bit `param_2` of the
 * +0xc2e pending mask was clear), returns 0 (not complete). Otherwise runs the
 * per-client TLB invalidate (via FUN_000c7bac) for each configured client,
 * clears the selected flush-phase bit, re-arms the next flush phase, programs
 * the per-client error/status registers from the current 0x18-byte flush
 * record, and returns 1 when the flush sequence is complete.
 * Confidence: low (large state machine; several field identities inferred)
 * Notes: ctrl+0xbe0 mode (2 => always done); +0xbe2 busy gate; +0xc2e pending
 *   flush mask; +0xc2c in-progress mask; +0xc30 current phase; +0xbfc flush
 *   record array (stride 0x18); client hw at +0x8 stride 0x78; +0xba4 count;
 *   FUN_000c7bac per-client invalidate; DAT_000c7bac poll-mode. */
int
sptm_dart_poll(void *ctrl, uint64_t phase)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint8_t mode;
    uint8_t busy;
    uint8_t policy;
    uint16_t pend, inprog;
    uint16_t bitmask;
    uint32_t count;
    uint32_t i;
    uint64_t r;
    int rc;

    if (*(int8_t *)(c + 0xbe0) == 2) {
        return 1;
    }
    LOAcquire();
    busy = *(uint8_t *)(c + 0xbe2);
    *(uint8_t *)(c + 0xbe2) = 1;
    LORelease();
    if ((busy & 1) != 0) {
        return 0;
    }

    if (*(int16_t *)(c + 0xc2e) == 0) {
        policy = 0;
        count = *(uint32_t *)(c + 0xba4);
    } else {
        policy = *(uint8_t *)(c + 0xbfc + *(uint32_t *)(c + 0xc30) * 0x18);
        count = *(uint32_t *)(c + 0xba4);
    }
    if (count != 0) {
        for (i = 0; i < count; i++) {
            r = sptm_dart_flush(c, i, policy, 1);
            if ((r & 1) != 0) {
                goto fail;
            }
        }
    }

    bitmask = (uint16_t)(1u << (phase & 0x3f));
    LOAcquire();
    pend = *(uint16_t *)(c + 0xc2e);
    *(uint16_t *)(c + 0xc2e) = pend & ~bitmask;
    LORelease();
    if ((bitmask & pend) != 0) {
        goto done;   /* this phase was already clear: flush complete */
    }

    uint8_t sel = *(uint8_t *)(c + 0xbe1);
    uint16_t selbit = (uint16_t)(1u << (sel & 0x3f));
    if ((selbit & *(uint16_t *)(c + 0xc2c)) == 0) {
        sel = 1 - sel;
        selbit = (uint16_t)(1u << (sel & 0x3f));
        if ((selbit & *(uint16_t *)(c + 0xc2c)) == 0) {
            goto fail;
        }
        LOAcquire();
        *(uint16_t *)(c + 0xc2c) = *(uint16_t *)(c + 0xc2c) & ~selbit;
        LORelease();
    } else {
        LOAcquire();
        *(uint16_t *)(c + 0xc2c) = *(uint16_t *)(c + 0xc2c) & ~selbit;
        LORelease();
    }
    uint8_t *rec = c + 0xbfc + (uint64_t)sel * 0x18;
    if ((*(uintptr_t)(c + 0xbfc) ^ (uintptr_t)rec) & 0xffc0000000000000) {
        rec = (uint8_t *)(((uintptr_t)rec & 0xffffffffffffULL) | 0xc8a2000000000000ULL);
    }

    if (*(int8_t *)(c + 0xbe0) == 3) {
        uint32_t w = *(uint32_t *)(rec + 0x14);
        uint32_t t5 = w >> 8 & 7;
        if (t5 < 2) {
            if (t5 == 0) {
                for (i = 0; i < count; i++) {
                    *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)i * 0x78) + 0x80 / 4) = w;
                }
            } else {
                /* t5 == 1 */
                for (i = 0; i < count; i++) {
                    uint32_t *hw = *(uint32_t **)(c + 8 + (uint64_t)i * 0x78);
                    if ((w >> 0xe & 1) != 0) {
                        hw[0x98 / 4] = (*(uint32_t *)(rec + 4) & 0xfffffff) << 2;
                        if (count <= i) {
                            sptm_assert_fail("dart %s %d %s %u Invalid DART");
                        }
                        hw[0xa0 / 4] = (*(uint32_t *)(rec + 8) & 0xfffffff) << 2;
                    }
                    if (count <= i) {
                        sptm_assert_fail("dart %s %d %s %u Invalid DART");
                    }
                    w = *(uint32_t *)(rec + 0x14);
                    hw[0x80 / 4] = w;
                }
            }
        } else {
            if (t5 != 2) {
                if (t5 != 4) {
                    sptm_assert_fail("dart %s %d %s %u Unsupported");
                }
                for (i = 0; i < count; i++) {
                    *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)i * 0x78) + 0x80 / 4) = w;
                }
            } else {
                /* t5 == 2: single targeted client */
                uint32_t tgt = *(uint32_t *)(rec + 0x10);
                if (count <= tgt) {
                    sptm_assert_fail("dart %s %d %s %u Invalid DART");
                }
                uint32_t *hw = *(uint32_t **)(c + 8 + (uint64_t)tgt * 0x78);
                hw[0x84 / 4] = *(uint32_t *)(rec + 0xc);
                if (count <= tgt) {
                    sptm_assert_fail("dart %s %d %s %u Invalid DART");
                }
                hw[0x80 / 4] = *(uint32_t *)(rec + 0x14);
            }
        }
        if (((w >> 0xf & 1) != 0) && ((w & 0x600) == 0) &&
            (*(c + 0xbed) & 1) != 0 && (count != 0)) {
            for (i = 0; i < count; i++) {
                *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)i * 0x78) + 0x600 / 4) = 0;
            }
        }
    }

    LOAcquire();
    *(uint16_t *)(c + 0xc2e) = *(uint16_t *)(c + 0xc2e) | bitmask;
    LORelease();
    *(uint32_t *)(c + 0xc30) = sel;
    rc = 0;
    goto out;
fail:
    rc = 0;
    goto out;
done:
    rc = 1;
out:
    *(uint32_t *)(c + 0xbe2) = 0;
    return rc;
}

/* FUN_000c7bac @ 0x000c7bac   (sptm_dart_flush / sptm_dart_client_tlb_invalidate)
 * Ghidra: undefined8 FUN_000c7bac(long,ulong,uint,ulong)
 * Per-client DART TLB/table invalidate with polling. Selects the poll-mode
 * from the per-policy descriptor (DAT_00015530, stride 0x20): mode 1 waits
 * for bit0 of the +0x604 status register to clear; otherwise waits for the
 * +0x80 status word to go non-negative. Each iteration issues a DSB and spins
 * on the physical counter (CNTPCT_EL0) until a 1/10s (cntfrq-based) deadline
 * passes. After `flags&1` (or 5 failed retries) escalates: clears the +0x210
 * error-enable bit (0x210 |= 1) and panics, returning 1 (failure) when the
 * caller asked for the non-panicking form.
 * Confidence: medium
 * Notes: policy descriptor DAT_00015530[policy*0x20]; client hw base ctrl+0x8
 *   + idx*0x78 (PAC-masked); per-client count ctrl+0xba4; register read/write
 *   via FUN_000c7df8 / FUN_000c7e5c. */
int
sptm_dart_flush(void *ctrl, uint32_t client, uint32_t policy, uint64_t flags)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint32_t *hw;
    uint8_t pollmode;
    int retries = 0;
    uint32_t val;
    uint64_t start, deadline, now;

    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (policy > 2) {
        sptm_assert_fail("dart %s %d %s %u Invalid policy");
    }
    hw = sptm_dart_client_hw(c, client);
    pollmode = sptm_dart_policy_desc[policy * 0x20];
    if (pollmode > 2) {
        sptm_assert_fail("dart %s %d %s %u Invalid policy");
    }
    for (;;) {
        if (pollmode == 1) {
            if (*(uint32_t *)(c + 0xba4) <= client) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            if ((*(uint32_t *)(*hw + 0x604) & 1) == 0) {
                return 0;
            }
        } else {
            if (*(uint32_t *)(c + 0xba4) <= client) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            if (*(int32_t *)(*hw + 0x80) >= 0) {
                return 0;
            }
        }
        DataSynchronizationBarrier(3, 3, 0);
        start = sptm_sysreg_read(3, 3, 0xe, 0, 6);       /* CNTPCT_EL0 */
        deadline = (sptm_sysreg_read(3, 3, 0xe, 0, 0) & 0xffffff80) / 10000000 + start;
        do {
            __asm__ volatile("wfe" ::: "memory");
            DataSynchronizationBarrier(3, 3, 0);
            now = sptm_sysreg_read(3, 3, 0xe, 0, 6);
        } while (now < deadline);
        if ((flags & 1) != 0 || ++retries > 5) {
            if ((flags & 1) == 0) {
                val = sptm_dart_read_reg(c, client, 0x210);
                sptm_dart_write_reg_v1(c, client, 0x210, val | 1);
                sptm_assert_fail("dart %s %d %s %u DART instance");
            }
            return 1;
        }
    }
}

/* Alias: per-client TLB invalidate (guest-IO tree name). */
void
sptm_dart_client_tlb_invalidate(void *state, uint8_t client, int a, int b)
{
    (void)b;
    sptm_dart_flush(state, client, (uint32_t)a, 0);
}

/* FUN_000c7df8 @ 0x000c7df8   (sptm_dart_read_reg)
 * Ghidra: undefined4 FUN_000c7df8(long,uint,uint)
 * Read a 32-bit register at byte offset `reg` (4-aligned) from DART client
 * `client` of `ctrl`. Panics if the client index is out of range.
 * Confidence: medium
 * Notes: client hw base ctrl+0x8 + idx*0x78; client count ctrl+0xba4. */
uint32_t
sptm_dart_read_reg(void *ctrl, uint32_t client, uint32_t reg)
{
    uint8_t *c = (uint8_t *)ctrl;
    if (client < *(uint32_t *)(c + 0xba4)) {
        return *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)client * 0x78) +
            (reg & 0xfffffffc));
    }
    sptm_assert_fail("dart %s %d %s %u Invalid DART");
}

/* FUN_000c7e5c @ 0x000c7e5c   (sptm_dart_write_reg_v1)
 * Ghidra: void FUN_000c7e5c(long,uint,uint,undefined4)
 * Write a 32-bit value to byte offset `reg` (4-aligned) of DART client
 * `client` of `ctrl`. Panics on a NULL ctrl or out-of-range client index.
 * Confidence: medium
 * Notes: client hw base ctrl+0x8 + idx*0x78; client count ctrl+0xba4. */
void
sptm_dart_write_reg_v1(void *ctrl, uint32_t client, uint32_t reg, uint32_t val)
{
    uint8_t *c = (uint8_t *)ctrl;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (client < *(uint32_t *)(c + 0xba4)) {
        *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)client * 0x78) + (reg & 0xfffffffc)) = val;
        return;
    }
    sptm_assert_fail("dart %s %d %s %u Invalid DART");
}

/* FUN_000c8960 @ 0x000c8960   (sptm_dart_save_all)
 * Ghidra: void FUN_000c8960(byte,undefined8)
 * Save/disable every DART client of instance `dart_id`: for each configured
 * client calls sptm_dart_save (flush its registers). Validates the instance
 * id first.
 * Confidence: medium
 * Notes: instance via sptm_dart_valid_instances + sptm_percpu_base; ctrl at
 *   +0x10; client count at +0xba4. */
void
sptm_dart_save_all(uint8_t dart_id, uint64_t err)
{
    uint8_t *ctrl;
    uint32_t n, i;

    if (sptm_dart_valid_instances[dart_id] != 0xff) {
        ctrl = (uint8_t *)sptm_percpu_base(sptm_dart_valid_instances[dart_id], NULL);
        ctrl = *(uint8_t **)(ctrl + 0x10);
        n = *(uint32_t *)(ctrl + 0xba4);
        if (n != 0) {
            for (i = 0; i < n; i++) {
                sptm_dart_save(ctrl, i);
            }
        }
        return;
    }
    sptm_panic(0x6000006, err, "%s %s %s %d %s %llx");
}

/* FUN_000c8a14 @ 0x000c8a14   (sptm_dart_save)
 * Ghidra: void FUN_000c8a14(long,uint)
 * Save a single DART client's registers. On DART revision < 0x202 reads back
 * (self-writes) the +0x100 control and +0x1c0 status words if the client has
 * the "enable" bit set; on newer revisions it re-writes the whole 0x4000-byte
 * register block. Finally re-arms the error register at offset +0xbc8 with
 * 0xffffffff. Panics on an invalid client index.
 * Confidence: medium
 * Notes: DART version at ctrl+0xbdc; client hw at ctrl+0x8 stride 0x78;
 *   +0xbf3 "instance present" flag gate for the +0x1c0 write; reg block
 *   length from ctrl+0xb9c. */
void
sptm_dart_save(void *ctrl, uint32_t client)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint32_t *hw;
    uint32_t n;
    uint64_t blocks;

    if (*(uint16_t *)(c + 0xbdc) < 0x202) {
        n = *(uint32_t *)(c + 0xba4);
        if (n <= client) {
            sptm_assert_fail("dart %s %d %s %u Invalid DART");
        }
        hw = *(uint32_t **)(c + 8 + (uint64_t)client * 0x78);
        if ((*(uint32_t *)(hw + 0x100 / 4) >> 0x13 & 1) != 0) {
            if ((*(c + 0xbf3) & 1) == 0) {
                sptm_assert_fail("dart %s %d %s %u DART instance");
            }
            *(uint32_t *)(hw + 0x1c0 / 4) = *(uint32_t *)(hw + 0x1c0 / 4);
            n = *(uint32_t *)(c + 0xba4);
        }
        if (n <= client) {
            sptm_assert_fail("dart %s %d %s %u Invalid DART");
        }
        *(uint32_t *)(hw + 0x100 / 4) = *(uint32_t *)(hw + 0x100 / 4);
    } else if (*(uint32_t *)(c + 0xb9c) != 0) {
        /* Newer revision: flush the whole register block by re-writing it. */
        blocks = ((uint64_t)*(uint32_t *)(c + 0xb9c) + 0x1f) >> 5;
        hw = sptm_dart_client_hw(c, client);
        uint64_t off = 0x4000;
        do {
            if (*(uint32_t *)(c + 0xba4) <= client) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            *(uint32_t *)(*hw + off) = *(uint32_t *)(*hw + off);
            off += 4;
            blocks--;
        } while (blocks != 0);
    }
    if (client < *(uint32_t *)(c + 0xba4)) {
        *(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)client * 0x78) +
            (*(uint32_t *)(c + 0xbc8) & 0xfffffffc)) = 0xffffffff;
        return;
    }
    sptm_assert_fail("dart %s %d %s %u Invalid DART");
}

/* FUN_000c8ba0 @ 0x000c8ba0   (sptm_dart_ctrl_write)
 * Ghidra: void FUN_000c8ba0(byte,ulong,uint)
 * Write the per-client control bits `bits & 0x777` into the control register
 * at offset +0xbc8 of DART client `client` for instance `dart_id`. Ignores
 * the write when `bits & 0x777 == 0`. Validates the instance and client id.
 * Confidence: medium
 * Notes: instance via sptm_dart_valid_instances; ctrl at percpu+0x10; client
 *   hw at ctrl+0x8 stride 0x78; control-reg offset ctrl+0xbc8. */
void
sptm_dart_ctrl_write(uint8_t dart_id, uint64_t client_id, uint32_t bits)
{
    uint8_t *ctrl;
    uint32_t *hw;

    if (sptm_dart_valid_instances[dart_id] == 0xff) {
        sptm_panic(0x6000006, client_id, "%s %s %s %d %s %llx");
    }
    ctrl = (uint8_t *)sptm_percpu_base(sptm_dart_valid_instances[dart_id], NULL);
    ctrl = *(uint8_t **)(ctrl + 0x10);
    if (*(uint32_t *)(ctrl + 0xba4) <= (uint32_t)client_id) {
        sptm_panic(0x6000015, client_id, SPTM_FMT_LLX);
    }
    if ((bits & 0x777) != 0) {
        hw = *(uint32_t **)(ctrl + 8 + (client_id & 0xffffffff) * 0x78);
        hw[(*(uint32_t *)(ctrl + 0xbc8) & 0xfffffffc) / 4] = bits & 0x777;
        if (*(uint32_t *)(ctrl + 0xba4) <= (uint32_t)client_id) {
            sptm_assert_fail("dart %s %d %s %u Invalid DART");
        }
    }
}

/* FUN_000c92e8 @ 0x000c92e8   (sptm_dart_acquire_v1)
 * Ghidra: bool FUN_000c92e8(long,uint)
 * Return whether DART client `client` of `ctrl` is present AND enabled: true
 * iff the client instance entry exists (ctrl+0x238 + idx*8) and its +0x18
 * status byte has bit0x80 clear (enabled/ready). False for a NULL ctrl or an
 * out-of-range / absent instance.
 * Confidence: medium
 * Notes: client-count gate at ctrl+0xb98; instance pointers at ctrl+0x238
 *   (stride 8); the +0x18 byte bit0x80 is the disabled/teardown marker. */
int
sptm_dart_acquire_v1(void *ctrl, uint32_t client, uint64_t *dbg_out)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint8_t *inst;
    (void)dbg_out;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (client < *(uint32_t *)(c + 0xb98)) {
        inst = *(uint8_t **)(c + (uint64_t)client * 8 + 0x238);
        if (inst != NULL) {
            return (*(inst + 0x18) & 0x80) == 0;
        }
    }
    return 0;
}

/* FUN_000c9364 @ 0x000c9364   (sptm_dart_acquire_v2 / sptm_dart_instance_lookup)
 * Ghidra: bool FUN_000c9364(long,uint)
 * Return whether DART client `client` of `ctrl` has an instance entry: true
 * iff ctrl+0x238 + idx*8 is non-NULL. False for a NULL ctrl or an
 * out-of-range / absent instance. (The guest-IO tree consumes the result as a
 * "present" bitmask via sptm_dart_instance_lookup.)
 * Confidence: medium
 * Notes: client-count gate at ctrl+0xb98; instance pointers at ctrl+0x238. */
int
sptm_dart_acquire_v2(void *ctrl, uint32_t client, uint64_t *dbg_out)
{
    uint8_t *c = (uint8_t *)ctrl;
    (void)dbg_out;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (client < *(uint32_t *)(c + 0xb98)) {
        return *(uint64_t *)(c + (uint64_t)client * 8 + 0x238) != 0;
    }
    return 0;
}

/* Alias for the guest-IO tree (instance-present bitmask). */
void *
sptm_dart_instance_lookup(void *state, uint8_t instance)
{
    return (void *)(uintptr_t)sptm_dart_acquire_v2(state, instance, NULL);
}

/* FUN_000caa9c @ 0x000caa9c   (sptm_dart_lock)
 * Ghidra: uint FUN_000caa9c(long,uint)
 * Acquire / validate the DART lock for client `client` of `ctrl`. Computes
 * the lock-status mask based on the DART revision and the client's feature
 * bits, then checks the client lock word (+0x200 & +0x208): for non-legacy
 * revisions the masked status must match exactly, else panic; the "locked"
 * result is bit0 of the lock word. Returns 0/1 (locked state).
 * Confidence: medium
 * Notes: DART version at ctrl+0xbdc; lock word at client+0x200 masked by
 *   +0x208; status-mask base 0xa0 (or 0x1a0 when +0x20000000 set, plus 0x40
 *   when +0x3f00 power-state bits present); legacy revision uses 0x1e0. */
uint32_t
sptm_dart_lock(void *ctrl, uint32_t client)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint32_t *hw;
    uint32_t status_mask, lockword, masked;

    if (*(uint16_t *)(c + 0xbdc) < 0x204) {
        status_mask = 0x1e0;
    } else {
        if (*(uint32_t *)(c + 0xba4) <= client) {
            sptm_assert_fail("dart %s %d %s %u Invalid DART");
        }
        hw = *(uint32_t **)(c + 8 + (uint64_t)client * 0x78);
        status_mask = 0xa0;
        if ((*hw & 0x20000000) != 0) {
            status_mask = 0x1a0;
        }
        if ((hw[5] & 0x3f00) != 0) {
            status_mask |= 0x40;
        }
    }
    if (client < *(uint32_t *)(c + 0xba4)) {
        hw = *(uint32_t **)(c + 8 + (uint64_t)client * 0x78);
        lockword = *(uint32_t *)(hw + 0x200 / 4) & *(uint32_t *)(hw + 0x208 / 4);
        if ((*(uint16_t *)(c + 0xbdc) & 0xfffe) != 0x100) {
            masked = lockword & status_mask;
            if ((lockword & 1) == 0) {
                status_mask = 0;
            }
            if (masked != status_mask) {
                sptm_assert_fail("dart %s %d %s %u DART instance");
            }
        }
        return lockword & 1;
    }
    sptm_assert_fail("dart %s %d %s %u Invalid DART");
}

/* FUN_000cabb4 @ 0x000cabb4   (sptm_dart_lock_set)
 * Ghidra: void FUN_000cabb4(long,uint,uint)
 * Validate a DART lock-set configuration for client `client` of `ctrl`
 * against instance entry `idx`. When the instance's +0x18 "enabled" bit (bit1)
 * is set, checks that either the client is on a legacy DART with no power
 * states, or the instance is in an allowed configuration (bit0 clear, feature
 * bit +0xbf2, power-state class) and unbound (+8 == 0); panics otherwise.
 * Confidence: low (several instance-config fields inferred)
 * Notes: instance entries at ctrl+0x238 (stride 8); +0x18 byte bits; DART
 *   version ctrl+0xbdc; client count ctrl+0xba4. */
void
sptm_dart_lock_set(void *ctrl, uint32_t dart_id, uint64_t idx)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint8_t *inst;
    uint32_t flags;

    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    inst = *(uint8_t **)(c + (uint64_t)idx * 8 + 0x238);
    flags = *(uint32_t *)(inst + 0x18);
    if ((flags >> 1 & 1) != 0) {
        if ((*(uint16_t *)(c + 0xbdc) & 0xfffe) != 0x100) {
            if (*(uint32_t *)(c + 0xba4) <= dart_id) {
                sptm_assert_fail("dart %s %d %s %u Invalid DART");
            }
            if ((*(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)dart_id * 0x78) + 0x14 / 4) & 0x3f00) != 0) {
                return;
            }
        }
        if (((flags & 1) != 0) ||
            ((*(c + 0xbf2) & 1) == 0 &&
             ((1u << (idx & 0x1f) & 0xf000) == 0 || (idx & 0xe0) != 0)) ||
            (*(uint64_t *)(inst + 8) != 0)) {
            sptm_assert_fail("dart %s %d %s %u DART instance");
        }
    }
}

/* FUN_000cc2bc @ 0x000cc2bc   (sptm_dart_ps_refcount)
 * Ghidra: void FUN_000cc2bc(long,uint,int)
 * Adjust the power-state (PS) refcount for DART PS descriptor `ps` of `ctrl`.
 * The PS descriptor (DAT_001012b8, stride 6) gives {u16 reg-offset, u8
 * ctrl-idx, u8 bit}; the refcount bit is toggled in the register block
 * selected by (ctrl + ps[1]*8 + 0x228) at offset ps[0]. Panics if the count is
 * out of range or the set/clear fails. `inc` nonzero sets the bit, zero clears
 * it.
 * Confidence: medium
 * Notes: table count at DAT_001012b4; DAT_001012b8 stride 6; per-ctrl
 *   register blocks at ctrl+0x228 (indexed by descriptor byte 1). */
void
sptm_dart_ps_refcount(void *ctrl, uint8_t ps, int inc)
{
    uint8_t *c = (uint8_t *)ctrl;
    const uint8_t *desc;
    uint32_t *slot;
    uint64_t bit;

    if (sptm_dart_ps_wr_count == 0) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (ps >= sptm_dart_ps_wr_count) {
        sptm_assert_fail("dart %s %s %d Invalid ps write");
    }
    desc = &sptm_dart_ps_wr_table[(uint64_t)ps * 6];
    slot = (uint32_t *)(*(uint64_t *)(c + (uint64_t)(desc[1] & 0xff) * 8 + 0x228) + *(uint16_t *)desc);
    bit = 1ull << ((desc[3] & 0xff) & 0x3f);
    if (inc == 0) {
        *slot &= (uint32_t)~bit;
        if ((*slot & (uint32_t)bit) != 0) {
            sptm_assert_fail("dart %s %s %d Failed to clear");
        }
    } else {
        *slot |= (uint32_t)bit;
        if ((*slot & (uint32_t)bit) == 0) {
            sptm_assert_fail("dart %s %s %d Failed to set");
        }
    }
}

/* FUN_000cc3f8 @ 0x000cc3f8   (sptm_dart_write_field_v1)
 * Ghidra: void FUN_000cc3f8(long,uint,uint,undefined4)
 * Write a 32-bit register value for DART client `client` of `ctrl` through
 * the client's +0x18 sub-handle at byte offset `reg` (4-aligned). The
 * declared `mask` argument is not read by the body (raw value write). Panics
 * on a NULL ctrl or missing sub-handle.
 * Confidence: medium
 * Notes: client block at ctrl+0x18 + idx*0x78 holds the +0x18 hw pointer;
 *   the 5th (mask) parameter declared by callers is unused in the body. */
void
sptm_dart_write_field_v1(void *ctrl, uint32_t client, uint32_t reg, uint32_t val,
    uint64_t mask)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint32_t *hw;
    (void)mask;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    hw = *(uint32_t **)(c + (uint64_t)client * 0x78 + 0x18);
    if (hw != NULL) {
        *(uint32_t *)(*hw + (reg & 0xfffffffc)) = val;
        return;
    }
    sptm_assert_fail("dart %s %d %s %u Invalid DAP");
}

/* FUN_000cc490 @ 0x000cc490   (sptm_dart_write_field_v2)
 * Ghidra: void FUN_000cc490(long,uint,uint,uint,uint)
 * Verify a DART register field for client `client` of `ctrl`: reads the 32-bit
 * value at byte offset `reg` (4-aligned) through the +0x18 sub-handle and
 * asserts `(cur & mask) == (mask & want)`. Panics on a NULL ctrl or a
 * mismatched field.
 * Confidence: medium
 * Notes: despite the write_ prefix this is a read-back verification; client
 *   block at ctrl+0x18 + idx*0x78. */
void
sptm_dart_write_field_v2(void *ctrl, uint32_t client, uint32_t reg, uint32_t want,
    uint32_t mask)
{
    uint8_t *c = (uint8_t *)ctrl;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if ((*(uint32_t *)(**(uint32_t **)(c + (uint64_t)client * 0x78 + 0x18) + (reg & 0xfffffffc)) &
         mask) == (mask & want)) {
        return;
    }
    sptm_assert_fail("dart %s %d %s %u DART instance");
}

/* FUN_000cc540 @ 0x000cc540   (sptm_dart_write_reg_v2)
 * Ghidra: void FUN_000cc540(long,uint,uint,int)
 * Verify a DART client register equals an expected value: reads the 32-bit
 * value at byte offset `reg` (4-aligned) of client `client` and asserts it
 * equals `val`. Panics on a NULL ctrl or a value mismatch.
 * Confidence: medium
 * Notes: despite the write_ prefix this is a read-back verification; client
 *   hw base ctrl+0x8 + idx*0x78. */
void
sptm_dart_write_reg_v2(void *ctrl, uint32_t client, uint32_t reg, uint32_t val)
{
    uint8_t *c = (uint8_t *)ctrl;
    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    if (*(uint32_t *)(*(uint32_t **)(c + 8 + (uint64_t)client * 0x78) + (reg & 0xfffffffc)) == val) {
        return;
    }
    sptm_assert_fail("dart %s %d %s %u DART instance");
}

/* ------------------------------------------------------------------ *
 * DART table walk / TLB flush.
 * ------------------------------------------------------------------ */

/* FUN_000cd970 @ 0x000cd970   (sptm_dart_tt_lookup / sptm_dart_va_to_pte)
 * Ghidra: void FUN_000cd970(long,uint,ulong,ulong*)
 * Walk the DART translation tables for client `client` of `ctrl` to resolve
 * `va` to the leaf page-table entry: returns the virtual address of the leaf
 * PTE table and stores the leaf table's physical address in `*out`. Walks up
 * to three levels (per the client's +0x18 geometry bits and the VA shift/mask
 * tables DAT_000130d8/DAT_000130f8), translating each table physical address
 * through the EL2 window (or the region table / default papt when outside it).
 * Panics if a table is not present or cannot be translated.
 * Confidence: medium
 * Notes: instance entry at ctrl+0x238 + idx*8; +0x18 byte bit3 selects the
 *   3-level (vs 2-level) walk; level shifts from sptm_pt_shifts / _lo; papt
 *   translation via sptm_va_lookup (FUN_000e40ec). The Ghidra body is `void`
 *   but callers consume the leaf-table VA as the return; the binary returns it
 *   in x0. */
static uint64_t
sptm_dart_paddr_to_va(uint64_t paddr, uint64_t *err_out)
{
    uint64_t n, start;
    uint64_t *r;

    if (((uint32_t)sptm_mem_feature >> 8 & 1) == 0) {
        return (paddr - sptm_mem_low) + sptm_direct_map_base;
    }
    n = sptm_region_count;
    if (n != 0) {
        r = sptm_regions;
        do {
            start = *r;
            if ((start <= paddr) && (paddr < start + (uint64_t)(uint32_t)r[2] * 0x4000)) {
                return (paddr - start) + r[1];
            }
            r += 3;
            n--;
        } while (n != 0);
    }
    /* Default papt translation (FUN_000e40ec): {va, err}. */
    return sptm_va_lookup(paddr);
}

void *
sptm_dart_tt_lookup(void *ctrl, uint32_t client, uint64_t va, uint64_t *out_paddr)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint8_t *inst;
    uint32_t geom;
    uint64_t pte, paddr, table_va, idx;
    int root_lvl;
    uint64_t err;

    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }
    inst = *(uint8_t **)(c + 0x238 + (uint64_t)client * 8);
    geom = *(uint32_t *)(inst + 0x18);
    *out_paddr = 0;
    err = 0;

    /* Root level: bit3 of geometry selects level 1 (3-level walk) or 0. */
    root_lvl = (geom & 8) == 0 ? 0 : 1;
    idx = (sptm_pt_shifts[root_lvl] & (va >> 0xe)) >> (sptm_pt_shifts_lo[root_lvl] & 0x3f);
    pte = *(uint64_t *)(inst + idx * 8);
    if (((pte & 1) == 0) || ((pte & 0x3ffffffc00) == 0)) {
        goto not_present;
    }
    paddr = (pte & 0x3ffffffc00) * 0x10;
    *out_paddr = paddr;
    table_va = sptm_dart_paddr_to_va(paddr, &err);

    /* Second level. */
    int lvl2 = (geom & 8) == 0 ? 2 : 1;
    if ((geom >> 3 & 1) == 0 ||
        ((*(uint32_t *)(*(uint8_t **)(c + 0x238 + (uint64_t)client * 8) + 0x18) >> 3 & 1) != 0)) {
        idx = (sptm_pt_shifts[lvl2] & (va >> 0xe)) >> (sptm_pt_shifts_lo[lvl2] & 0x3f);
    } else {
        idx = 0;
    }
    pte = *(uint64_t *)(table_va + idx * 8);
    if (((pte & 1) == 0) || ((pte & 0x3ffffffc00) == 0)) {
        goto not_present;
    }
    paddr = (pte & 0x3ffffffc00) * 0x10;
    *out_paddr = paddr;
    table_va = sptm_dart_paddr_to_va(paddr, &err);

    /* Third level (only for the 3-level geometry). */
    if ((geom >> 3 & 1) != 0) {
        pte = *(uint64_t *)(table_va + (va >> 0x19 & 0x7ff) * 8);
        if (((pte & 1) == 0) || ((pte & 0x3ffffffc00) == 0)) {
            goto not_present;
        }
        paddr = (pte & 0x3ffffffc00) * 0x10;
        *out_paddr = paddr;
        table_va = sptm_dart_paddr_to_va(paddr, &err);
    }
    if (*out_paddr == 0) {
        sptm_assert_fail("dart %s %d %s %u table pa %d 0");
    }
    if (table_va != 0) {
        return (void *)table_va;
    }
    sptm_assert_fail("dart %s %d %s %u table %d 0");
not_present:
    sptm_panic(0x6000012, client, SPTM_FMT_LLX);
}

/* Alias: guest-IO tree name for the DART table walk. */
void *
sptm_dart_va_to_pte(void *state, uint8_t instance, uint64_t va, uint64_t *out_paddr)
{
    return sptm_dart_tt_lookup(state, instance, va, out_paddr);
}

/* FUN_000cdd0c @ 0x000cdd0c   (sptm_dart_tlb_flush / sptm_dart_tlb_invalidate)
 * Ghidra: void FUN_000cdd0c(long,ulong,uint,uint,int)
 * Flush the DART TLB over a VA range. In "full flush" mode (ctrl+0xbeb bit0
 * clear) writes a 0x18-byte full-flush command record and polls it. In range
 * mode it builds a range-invalidate command (start<<32 | end; command word
 * 0x6100/0x7100 for clear/no-clear, plus revision bits), takes the state
 * guard, serializes if needed, issues the flush command and polls completion;
 * on DART revisions < 0x300 with a single-level client it also issues two
 * legacy invalidation command words (DAT_00012f40 / 00012f48). Panics on an
 * invalid flush range / guard mismatch.
 * Confidence: medium
 * Notes: DART version ctrl+0xbdc; guard ctrl+0xbdf; mode ctrl+0xbe0; command
 *   record at ctrl+0xbfc; poll via FUN_000c786c; legacy cmds DAT_00012f40 /
 *   DAT_00012f48 via FUN_000ce0b4. */
void
sptm_dart_tlb_flush(void *ctrl, uint32_t instance, uint64_t va_start_shift14,
    int va_end_shift14, int clear)
{
    uint8_t *c = (uint8_t *)ctrl;
    uint8_t *inst;
    uint64_t flush_cmd[3];
    uint16_t vers;
    int rc;

    if (c == NULL) {
        sptm_assert_fail("dart %s %s %d %s %d %s NULL");
    }

    if ((*(c + 0xbeb) & 1) == 0) {
        /* Full flush. */
        flush_cmd[0] = 0;
        flush_cmd[1] = 0;
        flush_cmd[2] = 0x100 | (uint32_t)instance;
        if (*(uint16_t *)(c + 0xbdc) > 0x201) {
            flush_cmd[2] = 0x8100 | (uint32_t)instance;
        }
        sptm_dart_flush_cmd(ctrl, (uint8_t *)&flush_cmd);
        return;
    }

    if ((uint32_t)va_end_shift14 < va_start_shift14) {
        sptm_assert_fail("dart %s %d %s %u Invalid flush");
    }
    flush_cmd[0] = (uint64_t)va_start_shift14 << 0x20;
    flush_cmd[1] = (uint64_t)va_end_shift14;
    flush_cmd[2] = clear == 0 ? 0x7100 : 0x6100;
    flush_cmd[2] |= (uint32_t)instance;
    if (*(uint16_t *)(c + 0xbdc) > 0x201) {
        flush_cmd[2] |= 0x8000;
    }
    sptm_dart_flush_cmd(ctrl, (uint8_t *)&flush_cmd);

    /* Legacy (v1) two-word invalidate for single-level clients on rev < 0x300. */
    if ((*(uint16_t *)(c + 0xbdc) < 0x300)) {
        inst = *(uint8_t **)(c + (uint64_t)instance * 8 + 0x238);
        if ((*(inst + 0x18) >> 3 & 1) == 0) {
            uint64_t w0 = flush_cmd[0];
            flush_cmd[0] = sptm_dart_tlb_cmd0;
            sptm_dart_flush_cmd(ctrl, (uint8_t *)&flush_cmd);
            flush_cmd[0] = w0;
            flush_cmd[1] = sptm_dart_tlb_cmd1;
            sptm_dart_flush_cmd(ctrl, (uint8_t *)&flush_cmd);
        }
    }
}

/* FUN_000ce0b4 @ 0x000ce0b4   (sptm_dart_flush_cmd)
 * Ghidra: void FUN_000ce0b4(long,undefined8)
 * Issue a 0x18-byte DART flush command record into ctrl+0xbfc and poll for
 * completion. Serializes the flush machinery first (LO lock + memcpy of the
 * command) unless the DART is already in the serialized mode (ctrl+0xbe0 == 2).
 * Confidence: medium
 * Notes: ctrl+0xc2c serialization mask; command copy via sptm_memcpy;
 *   completion poll via FUN_000c786c. */
void
sptm_dart_flush_cmd(void *ctrl, void *cmd)
{
    uint8_t *c = (uint8_t *)ctrl;
    ushort m;
    int rc;

    if (*(int8_t *)(c + 0xbe0) != 2) {
        LOAcquire();
        m = *(uint16_t *)(c + 0xc2c);
        *(uint16_t *)(c + 0xc2c) = m | 1;
        LORelease();
        if ((m & 1) != 0) {
            sptm_assert_fail("dart %s %d %s %u Not serialized");
        }
        sptm_memcpy(c + 0xbfc, cmd, 0x18);
    }
    do {
        rc = sptm_dart_poll(c, 0);
    } while (rc == 0);
}
