/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_support.h — support/init prototypes and EL2 feature globals (est.).
 *
 * Owned by the support-init tree.
 * Globals: DAT_fffffe0007e0d7f0 (quota), DAT_fffffe0007e0d800 (EL2 features),
 *   DAT_fffffe0007e41db0 (hv availability), DAT_fffffe0007e0d818/1c/1e
 *   (SoC/feature flags derived by hv_el2_feature_detect).
 */

#ifndef _ARM64_HYPERVISOR_HV_SUPPORT_H_
#define _ARM64_HYPERVISOR_HV_SUPPORT_H_

typedef long (*hv_op_func_t)(ulong arg);   /* est. hv mach-trap op handler */

/* FUN_fffffe000b984d4c — est. hv_support_init. Boot-time init; returns 1
 * when EL2 is active and hypervisor support is enabled. */
static int hv_support_init(void);

/* FUN_fffffe000b987fa8 — est. hv_el2_feature_detect. Reads EL2 sysregs and
 * fills the EL2 feature / SoC globals. */
static void hv_el2_feature_detect(void);

/* FUN_fffffe000b984ed8 — est. hv_available. Mach-trap dispatcher over the
 * PTR_FUN_fffffe0007e0d750 operation table. */
static void hv_available(long param_1);

/* ---- Shared kernel dependencies (declared, NOT recreated) ---- */
extern int   FUN_fffffe000c09c084(long node, const char *path, void **out);  /* kernel DT node lookup, not recreated */
extern int   FUN_fffffe000c09c31c(const void *node, const char *name, uint **val, int *size); /* kernel DT property get, not recreated */
extern int   FUN_fffffe000c09cbf0(long base, const char *name, int *val, int size, long flag); /* kernel boot-arg getter, not recreated */
extern void  FUN_fffffe000bd30528(int event, ...);  /* kernel trace/log, not recreated */

/* EL2 feature globals (est.), written by hv_el2_feature_detect / hv_support_init */
extern ulong hv_el2_features;   /* DAT_fffffe0007e0d800 EL2 features */
extern uint  hv_quota[3];       /* DAT_fffffe0007e0d7f0/0x7f4/0x7f8 hv ISA VM quota */
extern uint  hv_available_flag; /* DAT_fffffe0007e41db0 hv availability flag */

#endif /* _ARM64_HYPERVISOR_HV_SUPPORT_H_ */
