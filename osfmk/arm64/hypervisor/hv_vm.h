/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vm.h — the per-VM owner block and the per-CPU hypervisor state.
 *
 * Owned by the structs-audit tree.
 *
 * This header consolidates the VM / per-CPU structure offsets that were
 * scattered across the decompiled files into single definitions. Every
 * field carries a comment naming the Ghidra offset and the function(s) it
 * was observed in. Names are estimates; the Ghidra FUN_ + address (and the
 * qword index `owner[0xNNN]` where the decompile indexed the owner as a
 * `long *`) are ground truth.
 *
 * The object model (from hv_vm_create, est. hv_vm_create):
 *
 *   hv_vm_t  (the "owner block")  -- the per-VM object allocated from the
 *     hv_vm_zone (FUN_fffffe000b7eb624). Reached from the per-CPU struct via
 *     hv_vm_percpu_t.owner (+0x628), and from a bound vcpu as vcpu->container
 *     (hv_vcpu_t.+0x00). It embeds the per-CPU vcpu slot array, the region
 *     rbtree root, the entitlement tier / quota fields, and the host map
 *     pointer that implements the guest's stage-2 translation. The
 *     `hv_vm_config` region (+0x2088.., defined in hv_vmm.h) is a VIEW of
 *     the same storage the el2-state functions receive as `cfg` (= this
 *     block's base; cfg->sctlr_mask @ +0x2088 == owner[0x411]).
 *
 *   hv_vm_percpu_t  -- the per-CPU struct reached via tpidr_el1 /
 *     current_cpu_datap (est. per_cpu_base). Carries the bound vcpu, cpu
 *     id, the owner-block pointer, the EL2 nesting counter and the EL2
 *     control-state pointer used around guest run / teardown.
 *
 *   hv_vm_region_node  -- a node of the interval rbtree whose root lives at
 *     hv_vm_t.rbtree_root (+0x2138, owner[0x427]); built by
 *     hv_vm_map_region (est. hv_vm_map_region) and unlinked by
 *     hv_rbtree_unlink (est. hv_rbtree_unlink).
 *
 * Note on hv_vmm.h's former `struct hv_vm`: the EL2-state functions
 * (hv_el2_state_build etc.) receive the *vcpu* as `param_1` and treat
 * its +0x88/+0xb0/+0xc0 fields (base / el2 / pt_block) as the "vm". The
 * same offsets are carried on the owner block here; the two objects share
 * the layout at those offsets. See the per-field evidence.
 */

#ifndef _HV_VM_H_
#define _HV_VM_H_

#include <stdint.h>
#include <stddef.h>

/* Forward decl: hv_vm_config is defined in hv_vmm.h (owned by el2-state). */
struct hv_vm_config;

/*
 * hv_vm_t — the per-VM owner block (the `owner`/`container` in hv.c,
 * hv_vcpu.c, hv_vmapple.c; `struct hv_vm` in the el2-state files).
 *
 * Offsets are byte offsets from the owner-block base. Where the decompile
 * indexed the owner as a `long *`, the qword index is shown as
 * `owner[0xNNN]` (= byte offset 0xNNN*8) for traceability.
 *
 * ALL names are estimates; every field is backed by an observation.
 */
typedef struct hv_vm {
    /* +0x00  struct hv_vm_config *cfg
     *   Points at the owner block itself (self-referential view): the
     *   el2-state functions get `param_1` (here a vcpu) and read
     *   `param_1[0]` as cfg, whose sctlr_mask is at cfg+0x2088 == this
     *   block's +0x2088 (== owner[0x411], the feature mask written in
     *   hv_vm_create). Observed in hv_el2_state_build / b98dd40
     *   (hv_el2_state_build / apply). */
    struct hv_vm_config *cfg;

    /* +0x08  uint32_t refcount  (owner[1], low 32 bits)
     *   Object refcount. Set to 1 in hv_vm_create (hv_vm_create);
     *   incremented/decremented around lookup in hv_pmap_resolve_owner
     *   (hv_pmap_resolve_owner) and hv_ikot_hypervisor_handler
     *   (hv_ikot_hypervisor_handler); decremented in hv_vm_destroy
     *   (hv_vm_destroy). On the 1->0 transition the last releaser
     *   panics (kernel_panic_b). */
    uint32_t  refcount;
    uint8_t   _pad08[0x68 - 0x0c];      /* +0x0c .. +0x68 */

    /* +0x68  uint64_t page0  — L2 translation page (el2_state + 0x1000).
     *   Written in hv_el2_state_build (hv_el2_state_build) on the primary
     *   vCPU: `vm->page0 = el2 + 0x1000`. */
    uint64_t  page0;

    /* +0x70  uint64_t page1  — L3 translation page (el2_state + 0x2000).
     *   Same builder. */
    uint64_t  page1;
    uint8_t   _pad78[0x88 - 0x78];      /* +0x78 .. +0x88 */

    /* +0x88  uint64_t base  (param_1[0x11])
     *   "vm->base" — the allocation/slot base used by hv_vcpu_slot_op
     *   (hv_vcpu_slot_op reads it as param_1[0x11], the +0x88 word).
     *   On the vcpu object the same offset holds the container copy
     *   (hv_vcpu_t.guest_ctx). */
    uint64_t  base;
    uint8_t   _pad90[0xb0 - 0x90];      /* +0x90 .. +0xb0 */

    /* +0xb0  uint8_t *el2  — per-CPU EL2 state base (param_1[0x16]).
     *   hv_el2_state_apply (hv_el2_state_apply): `el2 = vm->el2`; the EL2
     *   block layout is in hv_vmm.h (struct hv_el2_state). The EL2 block
     *   base for the stage-2 tables is stored inside it at +0x4150. */
    uint8_t  *el2;

    /* +0xb8  uint8_t built  — EL2-build-done flag.
     *   Cleared in hv_el2_state_build (b9895b8) on the primary vCPU, set to 1
     *   at the end of hv_el2_pt_alloc (hv_el2_pt_alloc). */
    uint8_t   built;
    uint8_t   _padb9[0xc0 - 0xb9];      /* +0xb9 .. +0xc0 */

    /* +0xc0  uint64_t pt_block  — 0x4000-byte EL2 translation block.
     *   Allocated by hv_el2_pt_alloc (hv_el2_pt_alloc); its base is
     *   stored into el2_state+0x4150. (param_1[0x18].) */
    uint64_t  pt_block;
    uint8_t   _padc8[0x2080 - 0xc8];    /* +0xc8 .. +0x2080 */

    /* +0x2080  uint64_t addr_width  (owner[0x410])
     *   Address-width value written in hv_vm_create
     *   (hv_vm_create): `owner[0x410] = hv_addr_width(..,
     *   0xa004)`. */
    uint64_t  addr_width;

    /* +0x2088 .. +0x21a8 : embedded hv_vm_config region.
     *   The same bytes the el2-state functions read as `cfg->…`. Fields are
     *   enumerated inline below (and in hv_vmm.h's struct hv_vm_config). */

    /* +0x2088  uint64_t sctlr_mask  (cfg->sctlr_mask; owner[0x411])
     *   SCTLR_EL2 mask; also the capability feature mask written in
     *   hv_vm_create via hv_caps_feature_mask(owner+0x411). Read in
     *   hv_el2_state_build / apply (b9895b8 / b98dd40). */
    uint64_t  sctlr_mask;

    /* +0x2090 / +0x2098 : sctlr value pair used by hv_el2_state_apply. */
    uint64_t  sctlr_val1;               /* +0x2090 cfg->sctlr_val1 */
    uint64_t  sctlr_val2;               /* +0x2098 cfg->sctlr_val2 */

    /* +0x20a0 / +0x20a8 / +0x20b0 : TCR_EL2 mask + value pair. */
    uint64_t  tcr_mask;                 /* +0x20a0 cfg->tcr_mask  */
    uint64_t  tcr_val1;                 /* +0x20a8 cfg->tcr_val1  */
    uint64_t  tcr_val2;                 /* +0x20b0 cfg->tcr_val2  */
    uint8_t   _pad20b8[0x2118 - 0x20b8];/* +0x20b8 .. +0x2118 */

    /* +0x2118  uint64_t hipr_mask  (cfg->hipr_mask)
     *   Used by hv_el2_state_build: `EL2_RW(el2, HV_EL2_MASK, ~(cfg->hipr_mask |
     *   el2_flags))`. */
    uint64_t  hipr_mask;

    /* +0x2120  uint64_t host_map  (owner[0x424])
     *   Host vm_map pointer implementing the guest's stage-2 translation.
     *   Returned by hv_pmap_resolve_owner (hv_pmap_resolve_owner: `map_ptr =
     *   *(owner + 0x2120)`); written by hv_vcpu_map_memory
     *   (hv_vcpu_map_memory: `*(vcpu + 0x2120) = mapping` when no handle);
     *   copied into the vcpu's +0x88 in hv_vcpu_create
     *   (`vcpu_p[0x11] = container[0x424]`); released in hv_vcpu_object_release
     *   (hv_vcpu_object_release: `os_release(obj[0x424])`). */
    uint64_t  host_map;

    /* +0x2128  uint32_t tier  (owner[0x425])
     *   Entitlement tier stored at vm creation (hv_vm_create:
     *   `owner[0x425] = tier`); read by hv_vcpu_object_release
     *   (`if (*(uint32_t *)(obj + 0x425) > 1)`) to index the quota pool. */
    uint32_t  tier;

    /* +0x212c  uint32_t quota_cap  (owner[0x426])
     *   hv_quota_cap (DAT_fffffe000c5b83a8) captured at creation
     *   (hv_vm_create: `owner[0x426] = hv_quota_cap`). */
    uint32_t  quota_cap;
    uint8_t   _pad2130[0x2138 - 0x2130];/* +0x2130 .. +0x2138 */

    /* +0x2138  uintptr_t rbtree_root  (owner[0x427])
     *   Root of the VM's interval (region) red-black tree. Written in
     *   hv_vm_map_region (hv_vm_map_region: `owner[0x427] = node` for the
     *   first node); traversed/unlinked by hv_ikot_hypervisor_handler
     *   (hv_ikot_hypervisor_handler) and hv_rbtree_unlink (hv_rbtree_unlink,
     *   which reads the root at `param_1[0x427]`). */
    uintptr_t rbtree_root;
    uint8_t   _pad2140[0x2148 - 0x2140];/* +0x2140 .. +0x2148 */

    /* +0x2148  uint64_t vcpu_slot[8]  (owner[0x429 .. 0x430])
     *   Per-CPU vcpu slot array (8 slots). Each slot is a pointer to a
     *   per-slot registration array. Allocated in hv_vm_create
     *   (`for j in 0..7: owner[0x429+j] = alloc(&hv_slot_zone)`), freed in
     *   hv_vcpu_object_release (walks `obj[0x429+i]`, i in 0..8). Same
     *   storage as `cfg->vcpu_slot[8]` read by hv_vcpu_slot_op
     *   (hv_vcpu_slot_op). */
    uint64_t  vcpu_slot[8];
    uint8_t   _pad2188[0x2190 - 0x2188];/* +0x2188 .. +0x2190 */

    /* +0x2190  uint32_t tier3_flag  (owner[0x432])
     *   Boolean `(tier - 3) < 2` written in hv_vm_create
     *   (`owner[0x432] = (tier - 3) < 2`). */
    uint32_t  tier3_flag;
    /* +0x2194 .. : config tail (cfg->el2_cfg @ +0x2198, cfg->el2_state_id
     *   @ +0x21a0) — see struct hv_vm_config in hv_vmm.h. */
} hv_vm_t;

/*
 * hv_vm_percpu_t — the per-CPU hypervisor state, reached via tpidr_el1 or
 * current_cpu_datap (est. per_cpu_base). Offsets are byte offsets from
 * the per-cpu base. All names are estimates.
 */
typedef struct hv_vm_percpu {
    /* +0x120  void *sve_state  (est.)
     *   Guest SVE state object (kernel type 0x31 object) referenced by the
     *   return-to-guest path (hv_el2_return_to_guest) at tpidr+0x120. */
    void     *sve_state;
    uint8_t   _pad128[0x1b8 - 0x128];   /* +0x128 .. +0x1b8 */

    /* +0x1b8  void *el2_ctrl_ptr  (est.)
     *   Pointer whose +0x4c bit 2 gates the post-EL2 hook (TLB flush /
     *   nesting-exit) in hv_vcpu_destroy_trap (hv_vcpu_destroy_trap),
     *   hv_vcpu_run_trap (hv_vcpu_run_trap), hv_trap_op_15
     *   (hv_trap_op_15), hv_el2_pt_alloc (hv_el2_pt_alloc):
     *   `(*(uint8_t *)(*(long *)(cpu_slot + 0x1b8) + 0x4c) >> 2) & 1`. */
    void     *el2_ctrl_ptr;

    /* +0x1c0  int32_t nesting  — EL2 critical-section / nesting counter.
     *   Incremented on guest run / save / teardown and decremented after;
     *   the post-EL2 hook runs when it returns to 0. Observed in
     *   hv_vcpu_destroy_trap, b9899b0, b98e788, b98e344 and the vcpu
     *   destroy path (hv_vcpu.c hv_vcpu_destroy). */
    int32_t   nesting;
    uint8_t   _pad1c4[0x318 - 0x1c4];   /* +0x1c4 .. +0x318 */

    /* +0x318  void *resource_base  (est.)
     *   Per-CPU resource / object-lookup base. Read in hv_vm_map_shared
     *   (hv_vm_map_shared) and hv_vm_map_region (hv_vm_map_region)
     *   as `per_cpu_base(cpu); *(long **)(base + 0x318)`, and used as the
     *   obj-lookup base in hv_pmap_resolve_owner (hv_pmap_resolve_owner). */
    void     *resource_base;
    uint8_t   _pad320[0x4d8 - 0x320];   /* +0x320 .. +0x4d8 */

    /* +0x4d8  void *bound_vcpu  — the vcpu bound to this CPU (est.).
     *   Per-cpu vcpu slot (PERCPU_VCPU_SLOT). Read/written by every
     *   vcpu-core and trap handler: hv_vcpu_create (hv_vcpu_create),
     *   hv_vcpu_destroy_trap (b9897bc), hv_vcpu_run_trap (b9899b0),
     *   hv_trap_op_10/15/16 (b98e488/b98e788/b98e964), the hub
     *   hv_vcpu_run, and hv_pmap_resolve_owner (b986b34). */
    void     *bound_vcpu;
    uint8_t   _pad4e0[0x518 - 0x4e0];   /* +0x4e0 .. +0x518 */

    /* +0x518  uint32_t cpu_id  — the physical CPU id of this per-CPU struct
     *   (PERCPU_CPU_ID). Read whenever the kernel caches/compares the current
     *   cpu id (`hv_cached_cpu_id == *(uint32_t *)(cpu_slot + 0x518)`).
     *   Observed in hv_vm_destroy, hv_vcpu_create, hv_vcpu_destroy_trap,
     *   hv_trap_op_10, hv_pmap_resolve_owner, hv_ikot_hypervisor_handler. */
    uint32_t  cpu_id;
    uint8_t   _pad51c[0x628 - 0x51c];   /* +0x51c .. +0x628 */

    /* +0x628  hv_vm_t *owner  — the per-CPU owner-block pointer (est.).
     *   The per-VM owner block bound to this CPU. Read in hv_vm_create /
     *   hv_vcpu_create (`container = *(void **)(per_cpu_base(cpu) + 0x628)`),
     *   hv_vm_destroy (`owner = *(long **)(per_cpu_base(cpu_slot) + 0x628)`),
     *   hv_trap_op_10, hv_vm_map_region, hv_pmap_resolve_owner
     *   (hv_pmap_resolve_owner), hv_ikot_hypervisor_handler
     *   (hv_ikot_hypervisor_handler). */
    hv_vm_t  *owner;
    uint8_t   _pad630[0x8d8 - 0x630];   /* +0x630 .. +0x8d8 */

    /* +0x8d8  uint64_t dabt_counter  (est.)
     *   Guest DABT fault counter, incremented by the ESR classifier
     *   (hv_el2_guest_esr_classify) on EC 0x24 at tpidr+0x8d8. */
    uint64_t  dabt_counter;

    /* +0x8e0  uint64_t iabt_counter  (est.)
     *   Guest IABT fault counter, incremented by the ESR classifier
     *   (hv_el2_guest_esr_classify) on EC 0x20 at tpidr+0x8e0. */
    uint64_t  iabt_counter;
} hv_vm_percpu_t;

/*
 * hv_vm_region_node — a node of the VM's interval rbtree (root at
 * hv_vm_t.rbtree_root, +0x2138 / owner[0x427]).
 *
 * Layout observed in hv_vm_map_region (est. hv_vm_map_region):
 *   node[0]=vm, node[2]=start, node[3]=start+size, node[4]=ret,
 *   node[5..7]=rbtree links. Byte offsets = qword index * 8.
 * The link offsets match hv_rbtree_unlink (est. hv_rbtree_unlink):
 *   +0x28 left, +0x30 right, +0x38 parent (low bit = red flag).
 */
typedef struct hv_vm_region_node {
    hv_vm_t       *vm;                  /* node[0] +0x00  owning VM/owner   */
    uint64_t       rsvd_08;             /* node[1] +0x08  (unobserved)      */
    uint64_t       start;               /* node[2] +0x10  region start      */
    uint64_t       end;                 /* node[3] +0x18  start + size      */
    void          *ret;                 /* node[4] +0x20  name/ref handle   */
    struct hv_vm_region_node *left;     /* node[5] +0x28  rbtree left  */
    struct hv_vm_region_node *right;    /* node[6] +0x30  rbtree right */
    uintptr_t      parent_red;          /* node[7] +0x38  parent + red-bit */
} hv_vm_region_node_t;

#endif /* _HV_VM_H_ */
