/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_vmm.h — EL2 register state offsets and prototypes (est.).
 *
 * Owned by the el2-state tree.
 *
 * Ground truth anchors (from Ghidra):
 *   FUN_fffffe000b9895b8 (est. hv_el2_state_build) writes the per-CPU EL2
 *   state block at param_2 + 0x4000 ... 0x4148 with HCR/SCTLR/TCR-style
 *   constants, and a parallel "template"/requested set at param_2 + 0x6a8 ...
 *   0x780, plus two translation pages at param_2 + 0x1000 / 0x2000 and a
 *   far region at +0x9f0 / +0xa28.
 *
 * All register names are ESTIMATES of the EL2 register each offset holds.
 * Register identity is UNVERIFIED — the kernelcache is stripped, so we only
 * see a 64-bit constant written to each offset. Names follow the constant's
 * shape (HCR_EL2 = 0x10300000 has trap bits 20/21/24, etc.).
 */

#ifndef _HV_VMM_H_
#define _HV_VMM_H_

#include <stdint.h>
#include <stddef.h>

/*
 * EL2 state block offsets (relative to the per-CPU state base = param_2).
 * Two parallel 64-bit register banks:
 *   - "template"/requested bank at +0x6a8 (HV_EL2_TMPL_BASE),
 *   - "active"/committed bank at +0x4030 (HV_EL2_ACTIVE_BASE).
 * Slot i of the template bank (offset +0x6a8 + 8*i) shadows active slot i
 * (offset +0x4030 + 8*i); delta between banks is +0x3988.
 */
#define HV_EL2_TMPL_BASE     0x6a8
#define HV_EL2_ACTIVE_BASE   0x4030
#define HV_EL2_TMPL_SLOTS    18       /* +0x6a8 .. +0x730 */

/* Guest-saved EL2 registers + dirty-tracking flags. */
#define HV_EL2_DIRTY_BASE    0x738    /* 8 x 64-bit dirty flags (+0x738..0x770) */
#define HV_EL2_GSAVE_BASE    0x40c0   /* 8 x 64-bit guest-saved EL2 regs      */

/* Named active-bank registers (all ESTIMATES). */
#define HV_EL2_MAGIC         (HV_EL2_ACTIVE_BASE + 0x0)   /* +0x4000 */
#define HV_EL2_SCTLR         (HV_EL2_ACTIVE_BASE + 0x0)   /* +0x4030 */
#define HV_EL2_TCR           (HV_EL2_ACTIVE_BASE + 0x8)   /* +0x4038 */
#define HV_EL2_HCR           (HV_EL2_ACTIVE_BASE + 0x10)  /* +0x4040 */
#define HV_EL2_CPTR          (HV_EL2_ACTIVE_BASE + 0x18)  /* +0x4048 */
#define HV_EL2_MAIR          (HV_EL2_ACTIVE_BASE + 0x28)  /* +0x4058 */
#define HV_EL2_CTL           (HV_EL2_ACTIVE_BASE + 0xd0)  /* +0x4100 */
#define HV_EL2_HIPR          (HV_EL2_ACTIVE_BASE + 0xd8)  /* +0x4108 */
#define HV_EL2_MASK          (HV_EL2_ACTIVE_BASE + 0xe0)  /* +0x4110 */
#define HV_EL2_FLAGS         (HV_EL2_ACTIVE_BASE + 0xe8)  /* +0x4118 */
#define HV_EL2_VBAR          (HV_EL2_ACTIVE_BASE + 0xf0)  /* +0x4120 */
#define HV_EL2_GUEST_PT      (HV_EL2_ACTIVE_BASE + 0x120) /* +0x4150 */

/* Far-region state. */
#define HV_EL2_SYSREG        0x9f0    /* EL2 sysreg capture (3,4,0xf,0xc,0) */
#define HV_EL2_VER           0xa28    /* EL2 state version (3) */

/* Accessor macros over a raw uint8_t * base. */
#define EL2_RD(base, off)     (*(uint64_t *)((uint8_t *)(base) + (off)))
#define EL2_RW(base, off, v)  (*(uint64_t *)((uint8_t *)(base) + (off)) = (uint64_t)(v))
#define EL2_TMPL(base, i)     EL2_RD((base), HV_EL2_TMPL_BASE + 8 * (i))
#define EL2_ACTIVE(base, i)   EL2_RD((base), HV_EL2_ACTIVE_BASE + 8 * (i))

/*
 * hv_vm_config — the config object pointed at by *param_1 in the el2-state
 * functions. The +0x2088/+0x2090/+0x2098 triple (and +0x20a0/+0x20a8/+0x20b0)
 * are "mask / value1 / value2" groups that FUN_fffffe000b98dd40 uses to merge
 * template EL2 regs into the active set. Names are estimates.
 */
struct hv_vm_config {
    uint8_t   _pad0[0x2088];          /* up to +0x2088 */
    uint64_t  sctlr_mask;             /* +0x2088 */
    uint64_t  sctlr_val1;             /* +0x2090 */
    uint64_t  sctlr_val2;             /* +0x2098 */
    uint64_t  tcr_mask;               /* +0x20a0 */
    uint64_t  tcr_val1;               /* +0x20a8 */
    uint64_t  tcr_val2;               /* +0x20b0 */
    uint8_t   _pad1[0x2118 - 0x20b8];
    uint64_t  hipr_mask;              /* +0x2118 */
    uint8_t   _pad2[0x2148 - 0x2120];
    uint64_t  vcpu_slot[8];           /* +0x2148 .. 0x2188 */
    uint8_t   _pad3[0x2198 - 0x2188];
    uint64_t  el2_cfg;                /* +0x2198 */
    uint64_t  el2_state_id;           /* +0x21a0 */
};

/*
 * hv_vm — the per-VM object passed as param_1 by the el2-state functions.
 * Field 0 points at hv_vm_config; +0xb0 points at the per-CPU EL2 state.
 * Names are estimates.
 */
struct hv_vm {
    struct hv_vm_config *cfg;         /* +0x00 */
    uint8_t   _pad0[0x68 - 0x08];
    uint64_t  page0;                  /* +0x68: el2_state + 0x1000 */
    uint64_t  page1;                  /* +0x70: el2_state + 0x2000 */
    uint8_t   _pad1[0x88 - 0x78];
    uint64_t  base;                   /* +0x88 (alloc base in slot op) */
    uint8_t   _pad2[0xb0 - 0x90];
    uint8_t  *el2;                    /* +0xb0: per-CPU EL2 state base */
    uint8_t   built;                  /* +0xb8 */
    uint8_t   _pad3[0xc0 - 0xb9];
    uint64_t  pt_block;               /* +0xc0: 0x4000 EL2 translation block */
};

/* --- prototypes (est.) --- */

/*
 * hv_vcpu_run_state — the per-vCPU run object used by FUN_fffffe000b98dd04
 * (est. hv_vcpu_run_prepare) and FUN_fffffe000b98ded4 (hv_el2_state_commit):
 *   +8    -> run buffer (fields +8, +0x10 written)
 *   +0xb0 -> run buffer base (aliases +8; the EL2 state base in commit)
 *   +0xe8 / +0xf0 -> state (2 -> 1 transition observed)
 */
struct hv_vcpu_run_state {
    uint64_t  pad0;                   /* +0x00 */
    uint64_t *runbuf;                 /* +0x08 */
    uint8_t   _pad[0xb0 - 0x10];
    uint64_t  runbuf_slot;            /* +0xb0 */
    uint8_t   _pad2[0xe8 - 0xb8];
    uint64_t  state2;                 /* +0xe8 */
    uint64_t *state_ptr;              /* +0xf0: ptr to int state */
};


/* FUN_fffffe000b9895b8 @ 0xfffffe000b9895b8 — build per-CPU EL2 register state */
void hv_el2_state_build(struct hv_vm *vm, uint8_t *el2, uint32_t flags);

/* FUN_fffffe000b98dd40 @ 0xfffffe000b98dd40 — merge template EL2 regs into active */
void hv_el2_state_apply(struct hv_vm *vm);

/* FUN_fffffe000b98dd04 @ 0xfffffe000b98dd04 — prepare a vCPU run */
void hv_vcpu_run_prepare(struct hv_vcpu_run_state *vcpu, int param2);

/* FUN_fffffe000b98ded4 @ 0xfffffe000b98ded4 — commit/clear dirty EL2 flags */
void hv_el2_state_commit(struct hv_vcpu_run_state *vcpu);

/* FUN_fffffe000b98e020 @ 0xfffffe000b98e020 — copy user buffer w/ fault handling */
uint32_t hv_copyin_user(void *vm, void **dst, uint64_t src, uint64_t len);

/* FUN_fffffe000b98e12c @ 0xfffffe000b98e12c — vCPU slot op (copyin/out) */
uint32_t hv_vcpu_slot_op(struct hv_vm *vm, uint64_t slot, uint64_t which);

/* FUN_fffffe000b98e344 @ 0xfffffe000b98e344 — allocate EL2 translation block */
void hv_el2_pt_alloc(struct hv_vm *vm);

/* FUN_fffffe000b98e99c @ 0xfffffe000b98e99c — table-dispatched wrapper */
uint64_t hv_el2_pt_alloc_wrapper(uint64_t vcpu);

/* Shared kernel deps (NOT recreated): see docs/chain-map.md + manifest. */
extern int kernel_copyin(void *, uint64_t, uint64_t, int, int, int, int, uint64_t *);
extern int kernel_copyin2(uint64_t, uint64_t, uint64_t, int, uint64_t *);
extern int kernel_mem_validate(void *, void *, uint64_t, int, uint32_t, uint64_t,
                               uint64_t, int, int *, int *, int);
extern int kernel_copyout(uint64_t, uint64_t, uint64_t, int, uint64_t);
extern int kernel_mem_release(uint64_t, uint64_t, uint64_t);
extern void kernel_memzero(uint64_t, uint64_t, uint64_t, int, uint64_t);
extern int kernel_alloc(uint64_t, uint64_t, uint64_t, uint32_t, int, int);
extern void kernel_lock_ref(uint64_t);
extern void kernel_tlb_flush(void);
extern void kernel_panic(void);             /* noreturn */
extern void LORelease(void);                /* XNU object release */

/* EL2 sysreg reads — kept literal; identity unverified (op1=4 ⇒ EL2). */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);

/* Hypervisor/feature globals (see docs/kernelcache.md anchors). */
extern uint64_t DAT_fffffe0007e0d800;       /* EL2 features */
extern uint16_t DAT_fffffe0007e0d81e;       /* feature flag bit 0 */
extern uint64_t DAT_fffffe0007e0da68;       /* build-path gate (==0) */
extern uint64_t DAT_fffffe0007e31628;       /* SoC feature index */
extern uint8_t  DAT_fffffe0007d813d8[];     /* {int,char*} VM_MAP_WIRE fault table */
extern uint8_t  DAT_fffffe0007d81408[];     /* {int,char*} VM_MAP_UNWIRE fault table */
extern uint8_t *tpidr_el1;                  /* per-cpu data base (kernel) */

/* vcpu-core tree, not decompiled here (see docs/chain-map.md). */
extern void FUN_fffffe000b986e50(uint64_t); /* est. hv_vcpu_run (vcpu-core) */

#endif /* _HV_VMM_H_ */
