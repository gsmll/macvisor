/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_internal.h — internal shared helpers and cross-file prototypes.
 *
 * Owned by the shared-utils tree ONLY. Other trees must NOT add to this
 * file; they declare their own externals or reference the manifest.
 *
 * This header centralises the helpers that MORE THAN ONE tree's decompiled
 * file references, so the hypervisor subtree compiles as a unit conceptually.
 * Two groups:
 *
 *   (1) Shared kernel dependencies — XNU / shared-kernel routines that are
 *       stubbed, never decompiled (see docs/chain-map.md + docs/manifest.json
 *       entries with status "stubbed"). Ground truth is the Ghidra FUN_/DAT_
 *       name + address; estimated names are guesses.
 *
 *   (2) hv cross-file prototypes — functions DECOMPILED in another tree's
 *       file but called from a second tree's file. Ground truth is the Ghidra
 *       FUN_ name + address; the owner file is noted on each.
 *
 * This header is intentionally self-contained (forward-declared structs, no
 * include of the tree headers) so it can be included without triggering the
 * pre-existing cross-tree collision below. It does NOT force any include into
 * the .c files — declaration ownership is documented here instead (see
 * AGENTS.md "prefer minimal edits").
 *
 * KNOWN PRE-EXISTING COLLISION (not introduced by this header, resolve at
 * integration): hv.h and hv_vcpu.h both declare hv_vcpu_destroy and hv_vcpu_run
 * with DIFFERENT signatures for DIFFERENT Ghidra functions:
 *   hv.h        : kern_return_t hv_vcpu_destroy(void *);   idx7 FUN_fffffe000b9897bc
 *                 kern_return_t hv_vcpu_run(void *);       idx8 FUN_fffffe000b9899b0
 *   hv_vcpu.h   : void hv_vcpu_destroy(hv_vcpu_t *);          FUN_fffffe000b988e70
 *                 uint64_t hv_vcpu_run(void *);               FUN_fffffe000b989a44 hub
 * A single translation unit cannot include both headers today. The main
 * session should rename the trap-dispatch pair (e.g. hv_vcpu_destroy_trap /
 * hv_vcpu_run_trap) at integration; this header declares the vcpu-core
 * versions and documents both addresses.
 *
 * Declaration ownership (which file already declares what):
 *   - hv_support.c/h  : DT property/boot-arg getters (c09c084/c09c31c/c09cbf0),
 *                       kernel trace (bd30528); EL2 globals DAT_fffffe0007e0d800,
 *                       DAT_fffffe0007e0d7f0, DAT_fffffe0007e41db0. All three
 *                       hv_support functions are static (not cross-file).
 *   - hv_vmm.h        : kernel_copyin/copyin2/copyout/mem_validate/mem_release/
 *                       memzero/alloc/lock_ref/tlb_flush/kernel_panic, LORelease,
 *                       UnkSytemRegRead, el2-state DAT_ globals, tpidr_el1.
 *   - hv_vcpu.h       : copyin/copyout (b95c144/b95d6f4), kalloc/kfree,
 *                       vm_map_enter, the vcpu lifecycle prototypes.
 *   - hv.h            : hv_trap_record layout + the trap-dispatch handler
 *                       prototypes, boot_prop_getter.
 *   - hv_entitlements.h / hv_vmapple.h : empty stubs (entitlements/vmapple trees
 *                       not yet decompiled into the manifest).
 */

#ifndef _ARM64_HYPERVISOR_HV_INTERNAL_H_
#define _ARM64_HYPERVISOR_HV_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>

/* Forward declarations so this header needs no tree-header include. */
struct hv_vm;
struct hv_vcpu;
struct hv_vcpu_run_state;

/* ======================================================================== *
 * (1) SHARED KERNEL DEPENDENCIES — stubbed, NEVER decompiled.
 *     Ghidra FUN_ name + address is ground truth; each is referenced by
 *     >=2 hv trees.
 * ======================================================================== */

/* copyin/copyout — user<->kernel buffer moves.
 *   FUN_fffffe000b95c144 @ 0xfffffe000b95c144  (est. copyin)
 *   FUN_fffffe000b95d6f4 @ 0xfffffe000b95d6f4  (est. copyout)
 * Referenced by vcpu-core (hv_vcpu.c) and trap-dispatch (hv.c). */
extern int  copyin(const void *src, void *dst, size_t len);
extern int  copyout(const void *src, void *dst, size_t len);

/* Per-CPU object locks around the shared vm/owner lock DAT_fffffe000c62c0b8.
 *   FUN_fffffe000b7f0afc @ 0xfffffe000b7f0afc  (est. lock_acquire)
 *   FUN_fffffe000b7f1e4c @ 0xfffffe000b7f1e4c  (est. lock_release)
 *   FUN_fffffe000b7f1e80 @ 0xfffffe000b7f1e80  (est. per-cpu sync / release)
 * Referenced by vcpu-core and trap-dispatch. The decompiles differ in arity
 * (vcpu.c passes 2 args, hv.c up to 4); keep call sites as decompiled. */
extern void lock_acquire(void *lock, uint64_t arg, ...);
extern void lock_release(void *lock);
extern void lock_sync(void *lock, uint64_t cpu);

/* Per-CPU state base.
 *   FUN_fffffe000b866ec4 @ 0xfffffe000b866ec4  (est. per_cpu_base)
 * Returns the current CPU's per-cpu struct base (also reachable via
 * tpidr_el1). Referenced by vcpu-core and trap-dispatch. */
extern void *per_cpu_base(uint64_t cpu);

/* Kernel panic (all noreturn). Referenced by vcpu-core, el2-state and
 * trap-dispatch. Ghidra names kept as identifiers because the .c files call
 * them by FUN_ name; hv_vmm.h aliases c0f1874 as `kernel_panic`. */
extern void FUN_fffffe000c0f86a4(void) __attribute__((noreturn)); /* est. panic */
extern void FUN_fffffe000c0f8674(void) __attribute__((noreturn)); /* est. panic */
extern void FUN_fffffe000c0f1874(void) __attribute__((noreturn)); /* est. panic (hv_vmm.h: kernel_panic) */

/* XNU object release (refcount decrement, no free).
 * Referenced by el2-state (hv_vmm.c) and trap-dispatch (hv.c). */
extern void LORelease(void);

/* Kernel zone allocation / free + validation used for EL2 translation and
 * guest-memory windows. Referenced by vcpu-core and el2-state.
 *   FUN_fffffe000b8a6c14 @ 0xfffffe000b8a6c14  (est. kernel_alloc / kalloc)
 *   FUN_fffffe000b8b51c8 @ 0xfffffe000b8b51c8  (est. kernel_mem_validate / vm_map_enter)
 *   FUN_fffffe000b8a8078 @ 0xfffffe000b8a8078  (est. kernel_mem_release / dealloc)
 *   FUN_fffffe000b8b6860 @ 0xfffffe000b8b6860  (est. kernel_memzero / kfree) */
extern int  kernel_alloc(uint64_t a, uint64_t b, uint64_t c, uint32_t prot,
                         int e, int f);
extern int  kernel_mem_validate(void *a, void *b, uint64_t len, int prot,
                                uint32_t flags, uint64_t x, uint64_t y,
                                int z, int *out1, int *out2, int k);
extern int  kernel_mem_release(uint64_t a, uint64_t b, uint64_t c);
extern void kernel_memzero(uint64_t a, uint64_t b, uint64_t c, int d, uint64_t e);

/* --- Shared DAT_ globals used across >=2 files (ground truth: Ghidra) --- */

extern uint8_t *tpidr_el1;                 /* per-cpu data base (el2-state, vcpu-core, trap-dispatch) */
extern uint64_t DAT_fffffe0007e0d800;      /* EL2 features (support-init writes, el2-state/vcpu-core read) */
extern uint16_t DAT_fffffe0007e0d81e;      /* EL2 feature flag bit 0 (el2-state, vcpu-core) */
extern uint64_t DAT_fffffe0007e0da68;      /* EL2 build-path gate (==0) (el2-state, vcpu-core) */
extern uint64_t DAT_fffffe000c62c0b8;      /* shared vm/owner lock (vcpu-core, trap-dispatch) */
extern uint32_t DAT_fffffe000c62b3d0;      /* "pending sync" / lock-storm flag (vcpu-core, trap-dispatch) */
extern uint64_t DAT_fffffe000c62c0c0;      /* cached per-cpu id (vcpu-core, trap-dispatch) */
extern uint64_t DAT_fffffe000c5b83b0;      /* hv quota array (support-init, vcpu-core, trap-dispatch) */

/* ======================================================================== *
 * (2) hv CROSS-FILE PROTOTYPES — decompiled in another tree's file, called
 *     from a second tree. Ground truth: Ghidra FUN_ + address; owner file on
 *     each. Signatures match the owning header.
 * ======================================================================== */

/* ---- from osfmk/arm64/hypervisor/hv_vmm.c (el2-state tree) ---- */
void hv_el2_state_build(struct hv_vm *vm, uint8_t *el2, uint32_t flags); /* FUN_fffffe000b9895b8; called by hv_vcpu.c */
void hv_el2_state_apply(struct hv_vm *vm);                                /* FUN_fffffe000b98dd40 */
void hv_vcpu_run_prepare(struct hv_vcpu_run_state *vcpu, int param2);     /* FUN_fffffe000b98dd04; calls b986e50 */
void hv_el2_state_commit(struct hv_vcpu_run_state *vcpu);                 /* FUN_fffffe000b98ded4 */
uint32_t hv_copyin_user(void *vm, void **dst, uint64_t src, uint64_t len);/* FUN_fffffe000b98e020 */
uint32_t hv_vcpu_slot_op(struct hv_vm *vm, uint64_t slot, uint64_t which);/* FUN_fffffe000b98e12c */
void hv_el2_pt_alloc(struct hv_vm *vm);                                   /* FUN_fffffe000b98e344; called by hv.c (op16) */
uint64_t hv_el2_pt_alloc_wrapper(uint64_t vcpu);                          /* FUN_fffffe000b98e99c */
extern void FUN_fffffe000b98e74c(uint64_t owner);  /* est. hv_el2_state_finalize, el2-state; called by hv_trap_op_10 (hv.c). NOT yet in manifest — needs an el2-state entry. */

/* ---- from osfmk/arm64/hypervisor/hv_vcpu.c (vcpu-core tree) ---- */
uint64_t hv_vcpu_create(void *user_state);              /* FUN_fffffe000b989040 */
int hv_vcpu_alloc_init(struct hv_vcpu **out, uint64_t vm, int flag); /* FUN_fffffe000b989390 */
void hv_vcpu_destroy(struct hv_vcpu *vcpu);             /* FUN_fffffe000b988e70 (see collision note above) */
void hv_vcpu_object_release(void *object);              /* FUN_fffffe000b98533c; called by hv.c (vm create/destroy) */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t off_a,
                         uint64_t len_a, uint64_t off_b, uint64_t len_b); /* FUN_fffffe000b98503c */
uint64_t hv_vcpu_map_memory(void *vcpu, uint64_t gpa, uint64_t size,
                            uint32_t page_size, uint64_t *handle_out);   /* FUN_fffffe000b9866d0; called by hv.c */
uint64_t hv_vcpu_attach(struct hv_vcpu *vcpu, uint64_t id); /* FUN_fffffe000b986e50; called by hv_vmm.c (run_prepare) */
void hv_vcpu_save_el2_state(struct hv_vcpu *vcpu, uint64_t dirty_mask);  /* FUN_fffffe000b988358 */
uint64_t hv_vcpu_run(void *arg);                        /* FUN_fffffe000b989a44 (the run/exit hub; see collision note) */

/* ---- from osfmk/arm64/hypervisor/hv_entitlements.c (entitlements tree) ---- */
/* Referenced by hv.c (hv_vm_create). Entitlements tree has decompiled
 * FUN_fffffe000b985ae4: takes NO args (reads current thread's proc/cred
 * itself), returns uint8_t tier 0/1/3/4 (0=none,1=com.apple.security.hypervisor,
 * 3=vmapple or private,4=private+bootflag). hv.c's `hv_entitlement_tier(&in)`
 * call is a reconstruction approximation; real signature is void->uint8_t. */
uint8_t hv_entitlement_tier(void);

#endif /* _ARM64_HYPERVISOR_HV_INTERNAL_H_ */
