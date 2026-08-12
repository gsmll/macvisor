/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_entitlements.h — entitlement-gated capability prototypes and the
 * entitlement-relevant shared globals (est.).
 *
 * Owned by the entitlements tree.
 * Ground-truth anchors: DAT_fffffe0007e93310 (credential/sandbox ops table,
 * slot +0x1c0 = entitlement probe); DAT_fffffe0007e255f8 (boot-arg enable
 * flags, bit 4 used by hv_support_init, bits 0x1010 by the entitlement tier);
 * DAT_fffffe0007e0d818 (SoC implementer), DAT_fffffe0007e0d820 (hv feature
 * flags), DAT_fffffe0007e0c6ac (cache/topology flags), PTR_PTR_fffffe000c5b3f68
 * (page-size tables).
 */

#ifndef _ARM64_HYPERVISOR_HV_ENTITLEMENTS_H_
#define _ARM64_HYPERVISOR_HV_ENTITLEMENTS_H_

#include <stdint.h>
#include <stdbool.h>

/* FUN_fffffe000b985ae4 — current thread's hypervisor entitlement tier. */
uint8_t hv_entitlement_tier(void);

/* FUN_fffffe000b987d9c — fill 19-qword capability feature mask from tier. */
void hv_caps_feature_mask(uint64_t *mask, uint32_t tier);

/* FUN_fffffe000b988038 — fill hv capabilities CPU/memory feature report. */
void hv_caps_cpu_report(int64_t tier_block, uint64_t *report);

/* ---- Shared kernel deps used by the entitlement code (declared, NOT
 *      recreated; direct callees get bodies in hv_kernel_glue.c) ---- */

/* Credential/sandbox ops table; slot index 0x38 (offset +0x1c0) is the
 * entitlement probe returning 0 when the cred carries the entitlement. */
extern uintptr_t cred_ops[];                         /* DAT_fffffe0007e93310 */

/* Thread->proc accessor (FUN_fffffe000b866ec4) and credential validator
 * (FUN_fffffe000b8663e8, recreated as current_task in hv_kernel_glue.c). */
extern void *per_cpu_base(uint64_t thread);
extern void *current_task(void *obj);   /* FUN_fffffe000b8663e8, body in hv_kernel_glue.c */
extern long  FUN_fffffe000b95fe60(int idx);   /* est. cache_type_lookup */

/* Entitlement-relevant globals (est.). */
extern uint8_t *tpidr_el1;                     /* per-cpu data base (kernel) */
extern uint32_t hv_bootarg_flags;                  /* DAT_fffffe0007e255f8 boot-arg enable flags */
extern uint32_t hv_soc_implementer;                /* DAT_fffffe0007e0d818 SoC implementer (hv_el2_feature_detect) */
extern uint64_t hv_features;                       /* DAT_fffffe0007e0d820 hv feature flags */
extern uint64_t hv_cache_flags;                    /* DAT_fffffe0007e0c6ac cache/topology flags */
extern uint64_t *hv_page_size_table_1;             /* PTR_PTR_fffffe000c5b3f58 page-size table base 1 */
extern uint64_t *hv_page_size_table_2;             /* PTR_PTR_fffffe000c5b3f60 page-size table base 2 */
extern uint64_t *hv_page_size_table_3;             /* PTR_PTR_fffffe000c5b3f68 page-size table base 3 */

/* EL2 sysreg reads — kept literal; identity unverified. */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);

/* Kernel panics / halts (all noreturn), declared extern. */
extern void halt_baddata(void) __attribute__((noreturn));

#endif /* _ARM64_HYPERVISOR_HV_ENTITLEMENTS_H_ */
