/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

#include <stdint.h>
#include <stddef.h>

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
 * KNOWN PRE-EXISTING COLLISION (RESOLVED in this cleanup pass): hv.h and
 * hv_vcpu.h both declared hv_vcpu_destroy and hv_vcpu_run with DIFFERENT
 * signatures for DIFFERENT Ghidra functions. The trap-dispatch pair in
 * hv.h/hv.c is now renamed hv_vcpu_destroy_trap / hv_vcpu_run_trap:
 *   hv.h        : kern_return_t hv_vcpu_destroy_trap(void *);  idx7 hv_vcpu_destroy_trap
 *                 kern_return_t hv_vcpu_run_trap(void *);      idx8 hv_vcpu_run_trap
 *   hv_vcpu.h   : void hv_vcpu_destroy(hv_vcpu_t *);              hv_vcpu_destroy
 *                 uint64_t hv_vcpu_run(void *);                   hv_vcpu_run hub
 * hv_vcpu_destroy (b988e70) and hv_vcpu_run (b989a44) are the canonical
 * vcpu-core names; only those two remain under those names. A single
 * translation unit can now include both headers. This header declares the
 * vcpu-core versions and documents both addresses.
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
 *   copyin @ 0xfffffe000b95c144  (est. copyin)
 *   copyout @ 0xfffffe000b95d6f4  (est. copyout)
 * Referenced by vcpu-core (hv_vcpu.c) and trap-dispatch (hv.c). */
extern int  copyin(const void *src, void *dst, size_t len);
extern int  copyout(const void *src, void *dst, size_t len);

/* Per-CPU object locks around the shared vm/owner lock DAT_fffffe000c62c0b8.
 * Verified 2026-08-12 from fresh decompiles (the s_lck_mtx_t_ilk string at
 * 0xfffffe0007d790b8 confirms these are XNU lck_mtx):
 *   lck_mtx_lock   @ 0xfffffe000b7f0afc  (4 args: lock, thread, old, flags)
 *   lock_release   @ 0xfffffe000b7f1e4c  (mutex destroy/release variant)
 *   lck_mtx_unlock @ 0xfffffe000b7f1e80  (3 args: lock, thread, flags)
 * Referenced by vcpu-core and trap-dispatch. Call sites pass 2-4 args as
 * decompiled; keep variadic so the arity matches. */
extern void lck_mtx_lock(void *lock, ...);
extern void lock_release(void *lock);
extern void lck_mtx_unlock(void *lock, ...);

/* Per-CPU state base.
 *   current_cpu_datap @ 0xfffffe000b866ec4  (est. per_cpu_base)
 * Returns the current CPU's per-cpu struct base (also reachable via
 * tpidr_el1). Referenced by vcpu-core and trap-dispatch. */
extern void *per_cpu_base(uint64_t cpu);

/* Kernel panic (all noreturn). Referenced by vcpu-core, el2-state and
 * trap-dispatch. Ghidra names kept as identifiers because the .c files call
 * them by FUN_ name; hv_vmm.h aliases c0f1874 as `kernel_panic`. */
extern void kernel_panic_a(void) __attribute__((noreturn));  /* FUN_fffffe000c0f86a4 */
extern void kernel_panic_b(void) __attribute__((noreturn));  /* FUN_fffffe000c0f8674 */
extern void kernel_panic(void) __attribute__((noreturn));    /* FUN_fffffe000c0f1874 (hv_vmm.h: kernel_panic) */
extern void kernel_panic_c(void) __attribute__((noreturn));  /* FUN_fffffe000c0e1c3c (hv_vcpu_attach path) */

/* XNU object release (refcount decrement, no free).
 * Referenced by el2-state (hv_vmm.c) and trap-dispatch (hv.c). */
extern void LORelease(void);

/* Kernel zone allocation / free + validation used for EL2 translation and
 * guest-memory windows. Referenced by vcpu-core and el2-state. Signatures
 * verified against fresh decompiles 2026-08-12:
 *   kernel_alloc @ 0xfffffe000b8a6c14 — vm-object allocation, returns
 *     {error, block} (x0/x1 pair); callers check .lo==0 and use .hi.
 *   kernel_mem_validate @ 0xfffffe000b8b51c8 — actually vm_map_enter
 *     (the vm_remap/VM_PROT_COPY strings + full map-enter body confirm).
 *   kernel_mem_release @ 0xfffffe000b8a8078 — dealloc (vm, addr, size).
 *   kernel_vm_object_batch_dealloc @ 0xfffffe000b8b6860 — NO-ARG batch
 *     vm-object release; previously misnamed kernel_memzero/kfree/dealloc
 *     (callers' 5-arg renderings are register leftovers the callee ignores). */
extern hv_u128_t kernel_alloc(uint64_t a, uint64_t size, uint64_t c,
                              uint64_t flags, uint64_t e, void *f);
extern int  kernel_mem_validate(void *vm, void *map_out, uint64_t len,
                                uint64_t prot, uint32_t flags, uint64_t x,
                                uint64_t block, int z, int *out1, int *out2,
                                int k);   /* FUN_fffffe000b8b51c8, vm_map_enter */
extern int  kernel_mem_release(uint64_t a, uint64_t b, uint64_t c);
extern void kernel_vm_object_batch_dealloc(void);

/* ======================================================================== *
 * SHARED GLOBAL NAMING TABLE — one English name per hypervisor global.
 *
 * Ground truth is the Ghidra DAT_ address (kept in the comment on every
 * line for traceability). Code uses the English name; ALL trees in this
 * subtree MUST use these names so the module compiles as one unit. The
 * DAT_ addresses appear in comments ONLY (never as code identifiers).
 *
 * Provided by the maintainer's cleanup mapping; entries not in that list
 * carry a best-effort name + "(est.)" note.
 * ======================================================================== */

extern uint64_t tpidr_el1;                 /* per-cpu data base (kernel, el2-state/vcpu-core/trap-dispatch) */

/* ---- Feature / SoC identity (written by support-init / el2 detect) ---- */
extern uint64_t hv_chip_id;        /* DAT_fffffe0007e0c03c SoC/chip id, high byte 0x61='a' */
extern uint64_t hv_features;       /* DAT_fffffe0007e0d820 hv feature flags (bits 3/4) */
extern uint64_t hv_el2_features;   /* DAT_fffffe0007e0d800 EL2 feature-register result */
extern uint16_t hv_el2_l2;         /* DAT_fffffe0007e0d81d EL2-L2 capable flag (sibling of hv_el2_capable) */
extern uint16_t hv_el2_capable;    /* DAT_fffffe0007e0d81e EL2 feature bit 0 */
extern uint64_t hv_build_gate;     /* DAT_fffffe0007e0da68 build-path gate (==0 at runtime) */
extern uint64_t hv_soc_feature_index; /* DAT_fffffe0007e31628 SoC feature index (el2-state, hv_trap_op_16) */
extern uint32_t hv_soc_implementer;/* DAT_fffffe0007e0d818 aidr bits [16:15] */
extern uint64_t hv_soc_no_l2;      /* DAT_fffffe0007e0d81c aidr bit 45 (L2-table-absent) */
extern uint64_t hv_cache_flags;    /* DAT_fffffe0007e0c6ac cache/topology flag word (est.) */

/* ---- ISA VM quota + derived copies (kept symmetric, 3 qwords each) ---- */
extern uint32_t hv_quota[3];        /* DAT_fffffe0007e0d7f0/0x7f4/0x7f8 hv ISA VM quota */
extern uint32_t hv_quota_derived[3];/* DAT_fffffe000c5b83b0/0x3b4/0x3b8 derived quota copies */
extern uint32_t hv_quota_cap;       /* DAT_fffffe000c5b83a8 quota cap value (hv_vm_create) (est.) */

/* ---- Availability / boot-arg / entitlement ---- */
extern uint64_t hv_available_flag;  /* DAT_fffffe0007e41db0 hv availability (hv_support_init return) */
extern uint32_t hv_bootarg_flags;   /* DAT_fffffe0007e255f8 boot-arg enable flags (bit 4 + 0x1010) */
extern uint64_t hv_bootarg_table;   /* DAT_fffffe0007e9d440 boot-arg descriptor table (+0x6c = hv_apple_isa_vm_quota) (est.) */
extern uint64_t hv_trace_flag;      /* DAT_fffffe000c68ac90 trace-enable flag, bit 0 (est.) */
extern uintptr_t cred_ops[];        /* DAT_fffffe0007e93310 credential/sandbox ops table; slot +0x1c0 = entitlement probe */
extern uint64_t hv_caps_gate;       /* DAT_fffffe000c649750 capability-gate flag (hv_vm_create) (est.) */

/* ---- Shared vm/owner lock + per-CPU bookkeeping ---- */
extern uint64_t hv_lock;            /* DAT_fffffe000c62c0b8 shared vm/owner lock */
extern uint64_t hv_cached_cpu_id;   /* DAT_fffffe000c62c0c0 cached per-cpu id */
extern uint32_t hv_debug_flag;      /* DAT_fffffe000c62b3d0 "pending sync" / lock-storm flag */
extern uint64_t hv_vcpu_generation; /* DAT_fffffe000c716e40 vcpu generation counter */
extern uint64_t hv_special_owner_block; /* DAT_fffffe000c62b698 special unrestricted owner block (est.) */
extern uint64_t hv_flush_lock;      /* DAT_fffffe000c756760 flush/state lock (hv_trap_op_10) (est.) */

/* ---- Object registry / container lists ---- */
extern uint16_t *hv_object_type_table;   /* DAT_fffffe0007d78658 kernel object-registry type table (stride 0x28) */
extern uint64_t hv_container_refcount;   /* DAT_fffffe0007d54078 container refcount global (est.) */

/* ---- Zone / allocator descriptors + list heads (0x7d5xxxx region) ---- */
extern uint64_t hv_vm_zone;          /* DAT_fffffe0007d53eb8 hv vm object zone descriptor (est.) */
extern uint64_t hv_slot_zone;        /* DAT_fffffe0007d53f78 per-cpu owner slot zone descriptor (est.) */
extern uint64_t hv_slot_rel_zone;    /* DAT_fffffe0007d53fb8 owner slot release zone descriptor (est.) */
extern uint64_t hv_vm_rel_zone;      /* DAT_fffffe0007d53ff8 vm unwind/rel zone descriptor (est.) */
extern uint64_t hv_region_node_zone; /* DAT_fffffe0007d54038 rbtree region-node zone descriptor (est.) */
extern uint64_t hv_vm_list;          /* DAT_fffffe0007d52478 vm object list head (est.) */
extern uint64_t hv_owner_list;       /* DAT_fffffe0007d53f38 owner object list head (est.) */
extern uint64_t hv_slot_list;        /* DAT_fffffe0007d53e38 per-slot registration list head (est.) */
extern uint64_t hv_obj_list;         /* DAT_fffffe0007d53e78 object global list head (est.) */
extern uint64_t hv_vm_pool;          /* DAT_fffffe000c5d7068 owner vm pool (est.) */

/* ---- VM_MAP fault-name tables + page-size descriptors ---- */
extern uint8_t  hv_vm_wire_fault_table[];    /* DAT_fffffe0007d813d8 {int,char*} VM_MAP_WIRE fault table */
extern uint8_t  hv_vm_unwire_fault_table[];  /* DAT_fffffe0007d81408 {int,char*} VM_MAP_UNWIRE fault table */
extern uint64_t *hv_page_size_table_1;       /* PTR_PTR_fffffe000c5b3f58 page-size descriptor table 1 */
extern uint64_t *hv_page_size_table_2;       /* PTR_PTR_fffffe000c5b3f60 page-size descriptor table 2 */
extern uint64_t *hv_page_size_table_3;       /* PTR_PTR_fffffe000c5b3f68 page-size descriptor table 3 */

/* ---- Task-zone globals (hv_kernel_glue.c current_task) ---- */
extern uint64_t hv_task_zone_base;   /* DAT_fffffe000c5c5bb0 task-zone base */
extern uint64_t hv_task_zone_size;   /* DAT_fffffe000c6492c8 task-zone size bound */

/* ---- Boot stack marker (boot path) ---- */
extern uint64_t boot_stack_marker;   /* DAT_fffffe000c5f0000 boot stack marker */

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
extern void hv_el2_state_finalize(uint64_t owner);  /* est. hv_el2_state_finalize, el2-state; called by hv_trap_op_10 (hv.c). NOT yet in manifest — needs an el2-state entry. */

/* ---- from osfmk/arm64/hypervisor/hv_vcpu.c (vcpu-core tree) ---- */
uint64_t hv_vcpu_create(void *user_state);              /* FUN_fffffe000b989040 */
int hv_vcpu_alloc_init(struct hv_vcpu **out, uint64_t vm, int flag); /* FUN_fffffe000b989390 */
void hv_vcpu_destroy(struct hv_vcpu *vcpu);             /* FUN_fffffe000b988e70 (see collision note above) */
void hv_vcpu_object_release(uint64_t *object);           /* FUN_fffffe000b98533c; called by hv.c (vm create/destroy) */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t off_a,
                         uint64_t len_a, uint64_t off_b, uint64_t len_b); /* FUN_fffffe000b98503c */
uint64_t hv_vcpu_map_memory(void *vcpu, uint64_t gpa, uint64_t size,
                            uint32_t page_size, uint64_t *handle_out);   /* FUN_fffffe000b9866d0; called by hv.c */
uint64_t hv_vcpu_attach(struct hv_vcpu *vcpu, uint64_t id); /* FUN_fffffe000b986e50; called by hv_vmm.c (run_prepare) */
void hv_vcpu_save_el2_state(struct hv_vcpu *vcpu, uint64_t dirty_mask);  /* FUN_fffffe000b988358 */
uint64_t hv_vcpu_run(void *arg);                        /* FUN_fffffe000b989a44 (the run/exit hub; see collision note) */

/* ---- raw kernel helpers referenced by hv.c with uncertain identity ----
 * (declared so the tree compiles; names/arity are best-effort estimates) */
extern void *os_ref_retain(void *obj);  /* FUN_fffffe000b7f089c: object retain */

/* ---- from osfmk/arm64/hypervisor/hv_entitlements.c (entitlements tree) ---- */
/* Referenced by hv.c (hv_vm_create). Entitlements tree has decompiled
 * hv_entitlement_tier: takes NO args (reads current thread's proc/cred
 * itself), returns uint8_t tier 0/1/3/4 (0=none,1=com.apple.security.hypervisor,
 * 3=vmapple or private,4=private+bootflag). hv.c's `hv_entitlement_tier(&in)`
 * call is a reconstruction approximation; real signature is void->uint8_t. */
uint8_t hv_entitlement_tier(void);



/* ---- kernel/boot helper shims (de-guessed; verified externs) ---- *
 * These were untyped `extern int NAME();` declarations. Each was decompiled
 * and its guessed name VERIFIED against the real Ghidra function; they are
 * universal XNU core and are now declared as typed verified externs in
 * hv_kernel_shims.h (see that file for FUN_ + address + corrected name). */
#include "hv_kernel_shims.h"

/* ---- remaining untyped hypervisor-internal helpers (NOT kernel shims;
 * these are hv-internal and are owned/de-compiled elsewhere) ---- */
extern void refcount_dec(void *ref, void *free_fn);  /* typed (hv_kernel_glue.h); FUN_fffffe000b862b6c */

/* NOTE: `hv_rbtree_insert` and `hv_vm_unwind` were removed — neither had a
 * decompiled body nor any call site. The region RB-tree insert is inlined as
 * the static hv_rb_insert_rebalance in hv.c; hv_vm_unwind had zero references. */
#endif /* _ARM64_HYPERVISOR_HV_INTERNAL_H_ */
