/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv.h — Hypervisor.framework trap handler prototypes and the trap-dispatch
 * record layout (est.).
 *
 * Owned by the trap-dispatch tree.
 *
 * The mach-trap argument-munger FUN_fffffe000bda3ca8 (est. trap_arg_munger,
 * shared kernel, NOT recreated — see docs/chain-map.md) consumes a
 * `struct hv_trap_record` whose offsets were verified from its decompile and
 * from FUN_fffffe000be39fd0 (est. hv_vmm_present), which invokes the record's
 * copyout helper directly:
 *   +0x10 copyin flag, +0x28 copyin/copyout helper, +0x30 copyout flag,
 *   +0x38 arg size (4 or 8), +0x48 handler.
 * All kernel-provided helper routines used below are declared extern and NOT
 * recreated (shared kernel dependencies).
 */

#ifndef _HV_H_
#define _HV_H_

#include <stdint.h>
#include <stddef.h>

typedef uint32_t kern_return_t;

struct hv_trap_record;

/* Trap dispatch record consumed by hv trap handlers and the shared munger. */
typedef struct hv_trap_record {
	void      *rsvd_00;                                             /* +0x00 */
	void      *rsvd_08;                                             /* +0x08 */
	uint64_t   copyin_flag;                                         /* +0x10 */
	void      *rsvd_18;                                             /* +0x18 */
	void      *rsvd_20;                                             /* +0x20 */
	kern_return_t (*copy)(struct hv_trap_record *, void *, size_t); /* +0x28 copyin/copyout helper */
	uint64_t   copyout_flag;                                        /* +0x30 */
	uint64_t   arg_size;                                            /* +0x38 (4 or 8) */
	void      *rsvd_40;                                             /* +0x40 */
	kern_return_t (*handler)(struct hv_trap_record *, void *, uint64_t); /* +0x48 */
} hv_trap_record_t;

/*
 * Boot property getter: reads a boot-arg/device-tree property by name into a
 * caller buffer. Kernel helper, NOT recreated.
 *   FUN_fffffe000bf77834 @ 0xfffffe000bf77834  (est. boot_prop_getter)
 */
extern int boot_prop_getter(const char *name, void *buf, size_t len); /* kernel, not recreated */

/* hv_vmm_present — mach trap: report whether the hypervisor is present. */
void hv_vmm_present(hv_trap_record_t *rec);  /* FUN_fffffe000be39fd0 */

/*
 * Hypervisor trap handlers dispatched through the hv op table
 * PTR_FUN_fffffe0007e0d750 (19 entries, see docs/chain-map.md). All take the
 * user trap arg buffer in x0 and return a kern_return_t error code
 * (0xfae94xxx family). Estimated identities per table index; every name is a
 * guess (Ghidra FUN_* is ground truth).
 */
kern_return_t hv_capabilities(hv_trap_record_t *rec); /* idx0  FUN_fffffe000b984fd8 */
kern_return_t hv_vm_create(void *args);              /* idx1  FUN_fffffe000b985588 */
kern_return_t hv_vm_destroy(void *args);             /* idx2  FUN_fffffe000b985bf0 */
kern_return_t hv_vm_map(void *args);                 /* idx3  FUN_fffffe000b986898 */
kern_return_t hv_vm_protect(void *args);             /* idx4  FUN_fffffe000b986d84 (stub) */
kern_return_t hv_vm_unmap(void *args);               /* idx5  FUN_fffffe000b986d94 */
kern_return_t hv_vcpu_destroy_trap(void *args);      /* idx7  FUN_fffffe000b9897bc */
kern_return_t hv_vcpu_run_trap(void *args);          /* idx8  FUN_fffffe000b9899b0 */
kern_return_t hv_trap_op_10(void *args);             /* idx10 FUN_fffffe000b98e488 (unidentified) */
kern_return_t hv_vm_map_shared(void *args);          /* idx12 FUN_fffffe000b986da4 */
kern_return_t hv_vm_set_trap_debug(void *args);      /* idx14 FUN_fffffe000b986f1c */
kern_return_t hv_trap_op_15(void *args);             /* idx15 FUN_fffffe000b98e788 (unidentified) */
kern_return_t hv_trap_op_16(void *args);             /* idx16 FUN_fffffe000b98e964 (unidentified) */
kern_return_t hv_vm_map_region(void *args);          /* idx17 FUN_fffffe000b986ff4 */

/* Shared vm/region mapping core used by hv_vm_map (idx3) and hv_vm_unmap (idx5). */
kern_return_t hv_vm_map_core(void *args, int op, int mode); /* FUN_fffffe000b9868a8 */

#endif /* _HV_H_ */
