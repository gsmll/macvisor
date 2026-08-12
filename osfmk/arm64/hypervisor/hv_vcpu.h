/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vcpu.h — vCPU structure and lifecycle prototypes (est.).
 *
 * Owned by the vcpu-core tree.
 *
 * The vCPU object (per-cpu bound slot at tpidr_el1 + 0x4d8) is a heap
 * allocation of 0x100 bytes.  Field offsets below are lifted straight from
 * the decompiled Ghidra FUN_ functions and are estimates, not a verified
 * structure definition.
 */

#ifndef _HV_VCPU_H_
#define _HV_VCPU_H_

#include <stdint.h>
#include <stddef.h>

/*
 * vCPU object layout (0x100 bytes, est. from hv_vcpu_alloc_init/b989040
 * and the hub hv_vcpu_run). Byte offsets = qword index * 8 where
 * the decompile indexed the vcpu as a `long *` (vcpu_p[0xNN] = +0xNN*8).
 *
 *   +0x00  hv_vm_t *container  (owner VM object)
 *   +0x08  void *guest_mem     (second allocation, EL2-mapped, 0x8000)
 *   +0x10  vm_map_address      (mapping handle / address)
 *   +0x88  container copy      (vcpu_p[0x11]; host map from owner+0x2120)
 *   +0xb0  void *el2_state     (vcpu_p[0x16]; per-vcpu EL2 save area)
 *   +0xb8  amx_enable          (byte; (3,4,0xf,4,7)>>62, hv_vcpu_save_el2_state)
 *   +0xc0  vmm_ctx *           (vcpu_p[0x18]; has +0x1400 AMX state)
 *   +0xd0  void *el2_extra     (vcpu_p[0x1a]; 0x4000 EL2/SVE scratch)
 *   +0xd8  generation          (vcpu_p[0x1b]; hv_vcpu_generation capture)
 *   +0xe0  attach id string    (vcpu_p[0x1c])
 *   +0xe8  pending ptr pair    (stp xzr,xzr)
 *   +0xf0  void *attach_obj    (container/descriptor; [..+8]=vm, +0x1008 id)
 *   +0xf8  uint8_t vcpu_id     (index into container per-slot table, stride 0x80)
 */
typedef struct hv_vcpu {
    uint64_t       container;      /* +0x00 */
    uint64_t       guest_mem;      /* +0x08 */
    uint64_t       map_address;    /* +0x10 */
    uint8_t        _pad[0x70];     /* +0x18 .. 0x88 */
    uint64_t       guest_ctx;      /* +0x88 container copy / host map */
    uint8_t        _pad2[0x20];    /* +0x90 .. 0xb0 */
    uint64_t       el2_state;      /* +0xb0 (vcpu_p[0x16]) */
    uint8_t        amx_enable;     /* +0xb8 (save_el2_state (3,4,0xf,4,7)>>62) */
    uint8_t        _padb9[0xc0 - 0xb9];
    uint64_t       vmm_ctx;        /* +0xc0 (vcpu_p[0x18]; has +0x1400) */
    uint64_t       el2_extra;      /* +0xd0 (vcpu_p[0x1a]; 0x4000 EL2/SVE scratch) */
    uint64_t       generation;     /* +0xd8 (vcpu_p[0x1b]; hv_vcpu_generation) */
    uint64_t       attach_id;      /* +0xe0 (vcpu_p[0x1c]) */
    uint64_t       pending[2];     /* +0xe8 */
    uint64_t       attach_obj;     /* +0xf0 (has +0x1008 id field) */
    uint8_t        vcpu_id;        /* +0xf8 */
} hv_vcpu_t;

/* Error codes shared by the vcpu lifecycle (all 0xfae9-4xxx): */
#define HV_ERR_VCPU_UKN  0xfae94001
#define HV_ERR_VCPU_BSY  0xfae94002
#define HV_ERR_VCPU_ARG  0xfae94003
#define HV_ERR_VCPU_ALLOC 0xfae94005
#define HV_ERR_VCPU_NONE 0xfae94006

/* ------- vcpu lifecycle (hv_vcpu.c) ------- */

/* FUN_fffffe000b989040: bind a new vcpu to the calling CPU. */
uint64_t hv_vcpu_create(void *user_state);

/* FUN_fffffe000b989390: allocate + init the 0x100-byte vcpu and its mappings. */
int hv_vcpu_alloc_init(hv_vcpu_t **out, uint64_t vm, int flag);

/* FUN_fffffe000b988e70: tear down a vcpu's EL2 state and free it. */
void hv_vcpu_destroy(hv_vcpu_t *vcpu);

/* FUN_fffffe000b98533c: release the vcpu/VM object when refcount hits 0/1. */
void hv_vcpu_object_release(uint64_t *object);

/* FUN_fffffe000b98503c: merge/validate guest register state (zeros -> -1). */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t off_a,
                         uint64_t len_a, uint64_t off_b, uint64_t len_b);

/* FUN_fffffe000b9866d0: map guest physical memory, return an IO handle. */
uint64_t hv_vcpu_map_memory(void *vcpu, uint64_t gpa, uint64_t size,
                            uint32_t page_size, uint64_t *handle_out);

/* FUN_fffffe000b986e50: attach a vcpu to a container/VM by id string. */
uint64_t hv_vcpu_attach(hv_vcpu_t *vcpu, uint64_t id);

/* FUN_fffffe000b988358: capture guest EL2 system-register state. */
void hv_vcpu_save_el2_state(hv_vcpu_t *vcpu, uint64_t dirty_mask);

/* FUN_fffffe000b989a44: the main vcpu run / guest-exit dispatch hub. */
uint64_t hv_vcpu_run(void *arg);

/* ------- shared kernel deps (not recreated; see docs/chain-map.md) ------- */
extern void *kalloc(size_t);                 /* kernel allocator (FUN_fffffe000b8a6c14) */
extern void kfree(void *, size_t);           /* kernel free (FUN_fffffe000b8b6860) */
extern void *kalloc_noboot(void);            /* FUN_fffffe000b8a8078 */
extern uint64_t vm_map_enter(uint64_t, void *, uint64_t, uint64_t, uint64_t); /* b8b51c8 */
extern int copyin(const void *, void *, size_t);    /* FUN_fffffe000b95c144 */
extern int copyout(const void *, void *, size_t);   /* FUN_fffffe000b95d6f4 */

#endif /* _HV_VCPU_H_ */
