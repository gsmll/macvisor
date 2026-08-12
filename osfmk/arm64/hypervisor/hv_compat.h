/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

#ifndef _HV_COMPAT_H_
#define _HV_COMPAT_H_

/*
 * hv_compat.h — project-wide compatibility preamble.
 *
 * FIRST include in every file. The kernel proper is NOT recreated; these
 * shims provide the XNU-style types and Ghidra-decompiler artifacts the
 * reconstructions use, so the tree is readable and syntactically checkable
 * as a unit. All names are estimates; ground truth is the Ghidra FUN_/DAT_
 * name + address in comments.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* XNU-style typedefs used by the decompiled code (estimates). */
typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char byte;        /* Ghidra 'byte' */
typedef unsigned char boolean_t;   /* est. XNU boolean_t */
typedef uint32_t      kern_return_t;   /* matches hv.h; est. XNU kern_return_t */

/* Ghidra decompiler carry macros used in arithmetic-heavy reconstructions. */
#define CARRY8(a, b)   (((uint8_t)((a) + (b)) < (uint8_t)(a)) ? 1 : 0)
#define CARRY16(a, b)  (((uint16_t)((a) + (b)) < (uint16_t)(a)) ? 1 : 0)
#define CARRY32(a, b)  (((uint32_t)((a) + (b)) < (uint32_t)(a)) ? 1 : 0)
#define CARRY64(a, b)  (((uint64_t)((a) + (b)) < (uint64_t)(a)) ? 1 : 0)

/* Ghidra pseudo-functions from the decompile output (EL2 sysreg access).
 * op1 == 4 means EL2; register identity is unverified. */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);
extern void     UnkSytemRegWrite(int op0, int op1, int crn, int crm,
                                 int op2, uint64_t val);

/* Registers read as globals by the reconstructions. The reconstructions do
 * integer arithmetic on the raw register values, so these are uint64_t. */
extern uint64_t currentel;    /* CurrentEL (est.) */
extern uint64_t tpidr_el1;    /* TPIDR_EL1 per-cpu data base (raw value) */
extern uint64_t aidr_el1;     /* AIDR_EL1 auxiliary ID (SoC identity) */
extern uint64_t id_aa64pfr0_el1;  /* ID_AA64PFR0_EL1 (feature reg) */
extern uint64_t id_aa64pfr1_el1;  /* ID_AA64PFR1_EL1 (feature reg) */
extern uint64_t id_aa64dfr0_el1;  /* ID_AA64DFR0_EL1 (feature reg) */
extern uint64_t id_aa64dfr1_el1;  /* ID_AA64DFR1_EL1 (feature reg) */
extern uint64_t id_aa64isar0_el1; /* ID_AA64ISAR0_EL1 (feature reg) */
extern uint64_t id_aa64isar1_el1; /* ID_AA64ISAR1_EL1 (feature reg) */
extern uint64_t id_aa64mmfr0_el1; /* ID_AA64MMFR0_EL1 (feature reg) */
extern uint64_t id_aa64mmfr1_el1; /* ID_AA64MMFR1_EL1 (feature reg) */
extern uint64_t ctr_el0;      /* CTR_EL0 cache type register */
extern uint64_t dczid_el0;    /* DCZID_EL0 cache-zero register */
extern uint64_t daif;         /* DAIF debug/interrupt mask */
extern uint64_t actlr_el1;    /* ACTLR_EL1 aux control */
extern uint64_t cntkctl_el1;  /* CNTKCTL_EL1 timer control */
extern uint64_t cntp_ctl_el0; /* CNTP_CTL_EL0 counter control */
extern uint64_t cpacr_el1;    /* CPACR_EL1 coprocessor access */
extern uint64_t mpidr_el1;    /* MPIDR_EL1 multiprocessor affinity */
extern uint64_t pan;          /* PSTATE.PAN (est.) */
extern uint64_t tco;          /* PSTATE.TCO (est.) */

/* Ghidra pseudo-functions for ARM barriers / cache ops (est.). The
 * decompiler emits some with extra size arguments; accept and ignore them.
 * Statement-expression form so they can appear inside comma expressions. */
#define DataMemoryBarrier(...)        ({ __asm__ volatile("dmb sy" ::: "memory"); 0; })
#define DataSynchronizationBarrier(...) ({ __asm__ volatile("dsb sy" ::: "memory"); 0; })
#define InstructionSynchronizationBarrier(...) ({ __asm__ volatile("isb"); 0; })
#define TLBI_VMALLE1IS(...)           ({ __asm__ volatile("tlbi vmalle1is"); 0; })
#define NEON_rev64(x, ...)            __builtin_bswap64((uint64_t)(x))

typedef unsigned short ushort;   /* Ghidra type */

/* Ghidra pseudo-functions / registers from the decompiles (est.). */
extern void __amx_disable(void);   /* AMX unit disable (intrinsic) */
extern uint64_t svcr;              /* SVCR_EL2 streaming-SVE control (est.) */
extern void halt_baddata(void) __attribute__((noreturn));  /* bad-instruction halt */
extern void sveStreamingModeStop(void);  /* SVE streaming-mode stop (intrinsic) */
#define bitrev64(x) __builtin_bitreverse64((uint64_t)(x))

/* Ghidra POPCOUNT used in cache-geometry arithmetic (est.). */
#define POPCOUNT(x) __builtin_popcountll((uint64_t)(x))

/* Kernel alloc/dealloc helpers (kernel, not recreated). */
extern int kalloc_zalloc(void *out, size_t size); /* est. FUN_fffffe000b8a6c14 */
extern void dealloc(void *addr, size_t size);     /* est. FUN_fffffe000b8a8078 */

/* Kernel zone allocator used by hv_vm_create (kernel, not recreated). */
extern void *hv_zone_alloc(void *zone, int kind); /* est. FUN_fffffe000b7eb624 hv zone alloc */

/* hv mach-trap operation table (19 entries, see docs/chain-map.md). */
extern void *PTR_hv_op_table;

/* LORelease — ARC-style object release (kernel, not recreated). */
extern void container_release(void *obj);

/* Task-zone base/size used by current_task (kernel, not recreated). */
extern uint64_t hv_task_zone_base;  /* DAT_fffffe000c5c5bb0 */
extern uint64_t hv_task_zone_size;  /* DAT_fffffe000c6492c8 */

/* Panic with an encoded code (FUN_fffffe000c0eae24), used by current_task. */
extern void panic_dyn(int code) __attribute__((noreturn)); /* est. kernel panic */

/* Shared global naming table + cross-file prototypes (see hv_internal.h). */
#include "hv_internal.h"

#endif /* _HV_COMPAT_H_ */
