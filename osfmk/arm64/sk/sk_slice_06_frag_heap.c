/* sk_slice_06_frag_heap.c — VAS heap / region allocator (0x33780-0x34468).
 *
 * These functions implement the global VAS heap: the fixed node at 0x6af180
 * (tag 0xd) whose fields are laid out in sk_vas_heap_node_t below, the two
 * bootstrap region descriptors (0x6af020 / 0x6af0d0), the free-list and the
 * per-pool element allocators. All cross-function helpers that the shared
 * header declares with an incompatible signature (void where the decompile
 * returns a value, or a different arity) are reached through local extern
 * aliases so the bodies stay faithful.
 */
#include "sk_slice_06_shared.h"

/* ---- Local model of the fixed VAS heap node at 0x6af180. ---- */
typedef struct {
    uint8_t  pad00[0x40];        /* +0x00 */
    uint8_t  h2_kind;            /* +0x40 */
    uint8_t  h2_flags;           /* +0x41 */
    uint8_t  pad42[6];           /* +0x42 */
    uint64_t h2_base;            /* +0x48 */
    uint64_t h2_end;             /* +0x50 */
    uint8_t  h2_meta;            /* +0x58 */
    uint8_t  pad59[0xf];         /* +0x59 */
    uint64_t h2_region;          /* +0x68 */
    uint8_t  h2_active;          /* +0x70 */
    uint8_t  pad71[7];
    uint8_t  h0_kind;            /* +0x78 */
    uint8_t  h0_flags;           /* +0x79 */
    uint8_t  pad7a[6];
    uint64_t h0_base;            /* +0x80 */
    uint64_t h0_end;             /* +0x88 */
    uint8_t  h0_meta;            /* +0x90 */
    uint8_t  pad91[7];
    uint64_t h0_next;            /* +0x98 */
    uint64_t h0_region;          /* +0xa0 */
    uint8_t  h0_active;          /* +0xa8 */
    uint8_t  pada9[7];
    uint64_t region;             /* +0xb0 */
    uint8_t  padb8[8];
    uint8_t  active;             /* +0xc0 */
    uint8_t  guard;              /* +0xc1 */
    uint8_t  slot_in;            /* +0xc2 */
    uint8_t  padc3[0xd];
    uint64_t free_head;          /* +0xd0 */
    uint64_t free_tail;          /* +0xd8 */
    uint64_t free_ptr;           /* +0xe0 */
    uint8_t  reserve_pool[0x38]; /* +0xe8 */
    uint8_t  pad120[0xe0];       /* +0x120 */
    uint8_t  pool0[0x38];        /* +0x200 */
    uint8_t  pool1[0x38];        /* +0x238 */
    uint8_t  pad270[0x150];      /* +0x270 */
    uint64_t direct[3];          /* +0x3c0 */
    uint8_t  count;              /* +0x3d8 */
    uint8_t  min;                /* +0x3d9 */
    uint8_t  pad3da[6];
    uint8_t  end;                /* +0x3e0 */
} sk_vas_frag_heap_node_t;

/* ---- Global VAS registry / bootstrap state (Ghidra data addresses). ---- */
static void     *heap_registry_head;   /* DAT_0064c6d0 (registry list head) */
static uint64_t  heap_0064c728;        /* DAT_0064c728 = DAT_004bc3b8 */
static uint64_t  heap_004bc3b8;        /* DAT_004bc3b8 (bootstrap constant) */
static uint64_t  heap_0064c768;        /* DAT_0064c768 (region-0 base const) */
static uint64_t  heap_0064c770;        /* DAT_0064c770 */
static uint64_t  heap_0064c778;        /* DAT_0064c778 */
static uint64_t  heap_0064c780;        /* DAT_0064c780 */
static uint64_t  heap_0064c730;        /* DAT_0064c730 (region-1 base const) */
static uint64_t  heap_0064c738;        /* DAT_0064c738 */
static uint64_t  heap_0064c740[2];     /* DAT_0064c740 (16-byte common) */
static uint64_t  heap_bss_lock;        /* s___bss_0064c6f0 (shared VAS lock) */
static uint64_t  heap_registry_table[4];/* DAT_0064cab0 (registry slot table) */
static uint8_t   heap_registry_count;  /* DAT_0064cac8 (low byte) */
static uint8_t   heap_registry_overflow;/* DAT_0064cac9 */
static uint8_t   heap_region0[0xb0];   /* DAT_006af020 (bootstrap region 0) */
static uint8_t   heap_region1[0xb0];   /* DAT_006af0d0 (bootstrap region 1) */
static uint64_t *heap_region0_ptr;     /* DAT_0064c790 */
static uint64_t *heap_region1_ptr;     /* DAT_0064c758 */
static uint8_t   heap_clean;           /* *(extraout_x1 + 0x38) byte flag */

/* Triple/quad return of the direct-refill helper FUN_004b233c (Ghidra renders
 * the extra x8/x9/x10 return registers as extraout_*). */
typedef struct {
    uint64_t   node;   /* x0 (the node to run count/guard ops on) */
    uint64_t   value;  /* x8 (the allocated element) */
    uint64_t  *slot;   /* x9 */
    uint64_t  *count;  /* x10 */
} sk_vas_refill_t;

/* FUN_00033780 @ 0x00033780  (est. sk_vas_registry_init)
 * Ghidra: void FUN_00033780(void)
 * One-time initialisation of the global VAS registry and its bootstrap region
 * descriptors. Returns immediately if a type-4/flags-0xd VAS object already
 * exists. Otherwise it stamps the two bootstrap regions (0x6af020/0x6af0d0)
 * with the fixed kernel/heap bounds, initialises the shared VAS lock, then
 * walks the 4-entry registry slot table: each empty slot is filled by popping
 * the per-CPU VAS stack (FUN_00043eac); when that stack is exhausted it
 * switches to the current node and