/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_pmap.h — stage-2 MMU (guest -> host) translation layer.
 *
 * Owned by the hv-pmap tree.
 *
 * In this hypervisor the guest->host memory boundary is implemented as a host
 * vm_map per VM owner (built by hv_vm_map_core, hv_vm_map_core, owned by
 * the trap-dispatch tree) plus a small fixed EL2 translation table that is
 * allocated by hv_el2_pt_alloc (hv_el2_pt_alloc, el2-state tree) and
 * programmed by hv_el2_state_build (hv_el2_state_build, el2-state tree).
 * This header models the EL2 stage-2 table layout and the (estimated) ARM
 * VMSAv8-64 stage-2 descriptor format, and declares the hv-pmap owner-lookup /
 * unwind helpers decompiled into hv_pmap.c.
 *
 * The descriptor bit layout is an ESTIMATE derived from the ARM ARM
 * (VMSAv8-64 stage 2, D5.4); it is NOT directly observed in the decompiles —
 * the hv cluster builds the host vm_map and programs EL2 registers, and the
 * page-table walk itself runs in hardware. Treat every bit assignment below
 * as unverified.
 */

#ifndef _HV_PMAP_H_
#define _HV_PMAP_H_

#include <stdint.h>
#include <stddef.h>

/* ======================================================================== *
 * EL2 translation table layout (offsets within the per-CPU EL2 block that
 * hv_el2_pt_alloc, hv_el2_pt_alloc, allocates and stores at vm+0x4150).
 * Observed offsets come from hv_el2_state_build (hv_el2_state_build), which
 * sets param_1[0xd] = base+0x1000 and param_1[0xe] = base+0x2000 and writes
 * the EL2 register state at base+0x4000..:
 * ======================================================================== */
#define HV_PT_ROOT_OFF      0x0000   /* level-1 (root) table, 512 x 8 B      */
#define HV_PT_L2_OFF        0x1000   /* level-2 table                         */
#define HV_PT_L3_OFF        0x2000   /* level-3 table                         */
#define HV_PT_RSVD_OFF      0x3000   /* spare 0x1000                          */
#define HV_PT_STATE_OFF     0x4000   /* EL2 register-state block (see hv_vmm.h) */

/* Pointer fields on the vm config object set by the EL2 state builder. */
#define HV_CFG_PT_L2_SLOT   0xd      /* (param_1[0xd]) = base + HV_PT_L2_OFF   */
#define HV_CFG_PT_L3_SLOT   0xe      /* (param_1[0xe]) = base + HV_PT_L3_OFF   */
#define HV_CFG_PT_BASE      0x4150   /* vm+0x4150 holds the EL2 block base      */

/* ======================================================================== *
 * Stage-2 (VMSAv8-64) descriptor format — ESTIMATES, unverified.
 * A 64-bit descriptor is a {type, address, attributes} triple:
 *   [1:0]  type:  0b00 invalid, 0b01 leaf (block/page), 0b11 table
 *   [2]    Res0 (stage 2)
 *   [3]    leaf: nT (not-translated), stage 2
 *   [4]    leaf: NS
 *   [5]    leaf: reserved (0) in stage 2  (bit numbering approximate)
 *   [7:6]  leaf: AttrIndx[1:0] (memattr index into MAIR)
 *   [9]    leaf: XN
 *   [11:10]Res0 (stage 2 block)
 *   [18:16]CONTIG
 *   [47:12]output address[47:12]  (block/page) / next-level base (table)
 *   [55:48],[63:56] = 0
 * Table descriptor: [1:0]=0b11, [2]=0, [47:12]=next-level base.
 * ======================================================================== */
#define S2_DESC_TYPE_SHIFT   0
#define S2_DESC_TYPE_MASK    0x3ULL
#define S2_DESC_TYPE_INVALID 0x0ULL
#define S2_DESC_TYPE_BLOCK   0x1ULL   /* leaf: block (L1/L2) or page (L3) */
#define S2_DESC_TYPE_TABLE   0x3ULL
#define S2_DESC_NT_SHIFT     3        /* not-translated                 */
#define S2_DESC_NS_SHIFT     4        /* non-secure                     */
#define S2_DESC_ATTRINDX_SHIFT 6       /* memattr index [7:6]            */
#define S2_DESC_ATTRINDX_MASK 0x3ULL
#define S2_DESC_XN_SHIFT     9        /* execute-never                  */
#define S2_DESC_CONTIG_SHIFT 16
#define S2_DESC_ADDR_SHIFT   12       /* output addr / next-level base  */
#define S2_DESC_ADDR_MASK    0x000ffffffffff000ULL
#define S2_LEVEL_SHIFT       12        /* bits[47:12] are the table addr */
#define S2_TABLE_ENTRIES     512       /* 0x1000 / 8                     */
#define S2_INDEX_MASK        0x1ffULL   /* 9-bit index per level          */

/* Estimated per-level block granularity (granule 4KB). */
#define S2_LEVEL0_SHIFT      39
#define S2_LEVEL1_SHIFT      30
#define S2_LEVEL2_SHIFT      21
#define S2_LEVEL3_SHIFT      12

/* ======================================================================== *
 * Error codes returned by the hv map/unmap layer (0xfae94xxx family).
 * ======================================================================== */
#define HV_ERR_GENERIC   0xfae94001u   /* generic failure                 */
#define HV_ERR_BAD_ID    0xfae94002u   /* bad vcpu/id                     */
#define HV_ERR_BAD_RANGE 0xfae94003u   /* bad copyin / out-of-range map   */
#define HV_ERR_FULL      0xfae94005u   /* resource/alloc failure          */
#define HV_ERR_ABSENT    0xfae94006u   /* object absent                   */
#define HV_ERR_CONFLICT  0xfae94008u   /* region overlap / already mapped */
#define HV_ERR_BADOP     0xfae9400fu   /* invalid operation               */

/* ======================================================================== *
 * Shared kernel dependencies — stubbed, NEVER decompiled.
 * ======================================================================== */
/* vm-map core body owned by the trap-dispatch tree (FUN_fffffe000b9868a8,
 * decompiled in osfmk/arm64/hypervisor/hv.c; prototype in hv.h). */

/* Owner/map resolution (FUN_fffffe000b7e0f30, kernel object lookup). */
extern int kernel_obj_lookup(uint64_t base, uint64_t id, uint32_t type,
                             char **out);           /* b7e0f30 */
/* Kernel refcount increment with zone-magic validation (FUN_fffffe000b8af98c). */
extern void kernel_refcount_inc(uint64_t obj);      /* b8af98c */
/* XNU object release (FUN_fffffe000b8afa78, est. os_release). */
extern void os_release(void *obj);                  /* b8afa78 */
/* Zone free with waitq teardown (FUN_fffffe000b793cf4); the decompiler
 * drops the argument at most call sites. */
extern void zfree_waitq();            /* b793cf4 */
/* Per-CPU owner table slot (per_cpu_base + 0x628), current CPU base. */
extern void *per_cpu_base(uint64_t cpu);            /* b866ec4 */
/* Lock/unlock around the shared owner lock DAT_fffffe000c62c0b8
 * (canonical names in hv_internal.h; these are the same functions). */
extern void lck_mtx_lock(void *lock, ...);     /* b7f0afc */
extern void lock_release(void *lock);          /* b7f1e4c */
extern void lck_mtx_unlock(void *lock, ...);   /* b7f1e80 */
/* Panic helpers (noreturn). */
extern void kernel_panic(void) __attribute__((noreturn));   /* c0f1874 */
extern void kernel_panic_b(void) __attribute__((noreturn)); /* c0f8674 */
extern void kernel_panic_c(void) __attribute__((noreturn)); /* c0f86a4 */
extern void kernel_panic_msg(void *msg, uint64_t a, uint64_t b)
                                __attribute__((noreturn));   /* c0e1c3c */
/* XNU object release-refcount (LORelease). */
extern void LORelease(void);
/* Owner/vcpu object release on refcount drop to 1 (FUN_fffffe000b98533c,
 * owned by the vcpu-core tree; see hv_vcpu.c). */
extern void hv_vcpu_object_release(uint64_t *object);

/* Hypervisor/feature globals (see docs/kernelcache.md anchors). */
extern uint64_t tpidr_el1;            /* per-cpu data base (kernel) */
extern uint64_t hv_lock;              /* DAT_fffffe000c62c0b8 shared owner lock */
extern uint64_t hv_cached_cpu_id;     /* DAT_fffffe000c62c0c0 current-cpu cache */
extern uint32_t hv_debug_flag;        /* DAT_fffffe000c62b3d0 lock-storm flag   */

/* ======================================================================== *
 * hv-pmap prototypes — the stage-2 MMU owner/map helpers decompiled in
 * hv_pmap.c.
 * ======================================================================== */

/* FUN_fffffe000b986b34 @ 0xfffffe000b986b34 — resolve a vm/owner handle to
 *   the underlying map/state pointer. */
uint64_t hv_pmap_resolve_owner(uint64_t id, char **name_out);

/* FUN_fffffe000b986d34 @ 0xfffffe000b986d34 — unwind a failed map: release
 *   the owner reference or detach the current vcpu. */
void hv_pmap_unwind(char *name, uint64_t owner);

#endif /* _HV_PMAP_H_ */
