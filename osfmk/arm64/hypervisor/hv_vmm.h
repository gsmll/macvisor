/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vmm.h — EL2 register state offsets and prototypes (est.).
 *
 * Owned by the el2-state tree.
 *
 * Ground truth anchors (from Ghidra):
 *   hv_el2_state_build (est. hv_el2_state_build) writes the per-CPU EL2
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
 * The per-VM owner block (hv_vm_t / hv_vm_percpu_t) and the region-rbtree
 * node are consolidated in hv_vm.h (structs-audit tree). The el2-state
 * functions receive the vcpu as `param_1` and read the owner-block fields
 * via the same offsets (cfg +0x00, base +0x88, el2 +0xb0, built +0xb8,
 * pt_block +0xc0) — those fields are carried on hv_vm_t.
 */
#include "hv_vm.h"

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
 * are "mask / value1 / value2" groups that hv_el2_state_apply uses to merge
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
 * hv_vm — the per-VM owner block. Moved to hv_vm.h (structs-audit tree) and
 * renamed hv_vm_t. The el2-state functions here receive the vcpu as
 * `param_1` and read the owner-block fields at these offsets: +0x00 cfg,
 * +0x68 page0, +0x70 page1, +0x88 base, +0xb0 el2, +0xb8 built, +0xc0
 * pt_block. The full owner block (refcount, quota/tier, host map +0x2120,
 * region rbtree root +0x2138, per-cpu vcpu slots +0x2148, embedded config
 * +0x2088) is defined in hv_vm.h.
 */

/*
 * struct hv_el2_state — the per-CPU EL2 state block layout (base = the
 * `el2` pointer; also reached at the vcpu's +0xb0 / the owner's +0xb0).
 * Consolidates the EL2_RW/EL2_RD offsets observed in the el2-state
 * (hv_vmm.c), vcpu-core (hv_vcpu.c hv_vcpu_save_el2_state hv_vcpu_save_el2_state
 * and the hub b989a44) and el2-vectors (hv_el2.h) files. All register names
 * are ESTIMATES; register identity unverified (stripped kernelcache).
 *
 * The two parallel 64-bit banks are:
 *   - template / requested bank at +0x6a8 (HV_EL2_TMPL_BASE), and
 *   - active / committed bank at +0x4030 (HV_EL2_ACTIVE_BASE).
 * Slot i of the template bank (offset +0x6a8 + 8*i) shadows active slot i
 * (offset +0x4030 + 8*i); delta between banks is +0x3988. The build function
 * (hv_el2_state_build) writes both banks; the apply function
 * (hv_el2_state_apply) merges template into active under the config masks.
 */
struct hv_el2_state {
    /* ---- translation pages (wired by hv_el2_state_build on primary vCPU) ---- */
    uint8_t   l1_table[0x1000];        /* +0x0000 level-1 root (also vm->pt_block) */
    uint8_t   l2_table[0x1000];        /* +0x1000 level-2 table (vm->page0)       */
    uint8_t   l3_table[0x1000];        /* +0x2000 level-3 table (vm->page1)       */
    uint8_t   rsvd_3000[0x1000];       /* +0x3000 spare                             */

    /* +0x3b8 .. +0x470 : guest-saved EL2 capture group 0 (GIC / timer / EL2
     *   control sysregs) — written by hv_vcpu_save_el2_state
     *   (hv_vcpu_save_el2_state) when dirty bit 0 is set. */
    uint8_t   gic_capture[0x470 - 0x3b8];

    /* +0x698 / +0x6a0 : timer/counter group (dirty bit 3). */
    uint8_t   timer_698[0x6a8 - 0x698];

    /* +0x6a8 .. +0x780 : TEMPLATE bank (HV_EL2_TMPL_BASE), 18 x 64-bit slots.
     *   Slots (est. identity): 0 SCTLR, 1 TCR, 2 HCR, 3 CPTR, 4 misc0,
     *   5 MAIR, 6..16 misc, 17 el2_reg9 (+0x730, 0x1c00); +0x778 tmpl_ctl. */
    uint64_t  tmpl_reg[18];            /* +0x6a8 .. +0x730 */
    uint8_t   tmpl_pad[0x778 - 0x730];
    uint64_t  tmpl_ctl;                /* +0x778 (merged into active +0x4100) */

    /* +0x738 .. +0x770 : dirty-tracking flags (HV_EL2_DIRTY_BASE), 8 x 64-bit.
     *   Bit 32 (0x100000000) = "changed"; cleared by hv_el2_state_commit
     *   (hv_el2_state_commit). */
    uint64_t  dirty[8];                /* +0x738 .. +0x770 */

    /* +0x798 / +0x7a0 : CNTP/CTL capture group (save_el2_state bit 0x39). */
    uint8_t   cntp_798[0x7b0 - 0x798];

    /* +0x7b0 .. +0x868 : CNTHV / EL0-accessible timer group (bit 0x3e). */
    uint8_t   cnthv[0x868 - 0x7b0];

    /* +0x870 : (save_el2_state bit 0 tail) UnkSytemRegRead(3,4,0xf,2,6). */
    uint64_t  sctlr_capture;           /* +0x870 */

    /* +0x880 .. +0x948 : CNTHP / feature capture groups (bits 0x3c/0x3d/0x3a). */
    uint8_t   cnthp_880[0x950 - 0x880];

    /* +0x950 .. +0x9c8 : CNTHPS / EL2 timer group (bit 0x3b). */
    uint8_t   cnthps_950[0x9f0 - 0x950];

    /* +0x9f0 : EL2 sysreg capture (HV_EL2_SYSREG), read (3,4,0xf,0xc,0). */
    uint64_t  sysreg_capture;          /* +0x9f0 */

    /* +0x9f8 .. +0xa28 : (save_el2_state bit 0x38 group, 0x9f8/0xa00/0xa08/0xa10/
     *   0xa18/0xa20) and EL2 state version (HV_EL2_VER = 3) at +0xa28. */
    uint8_t   misc_a00[0xa28 - 0x9f8];
    uint64_t  state_version;           /* +0xa28 (3) */

    uint8_t   pad_a30[0x4000 - 0xa30];

    /* +0x4000 .. : active EL2 register bank (HV_EL2_ACTIVE_BASE) + header.
     * The build (hv_el2_state_build) writes the magic at +0x4000, the exit
     * reason word at +0x4008, ESR/ISS/exit-record words at +0x4010/+0x4018,
     * the synthesised guest IPA at +0x4028, then the active registers at
     * +0x4030..0x4148 and the guest-saved EL2 regs at +0x40c0..0x40f8. */
    uint64_t  magic;                   /* +0x4000 HV_EL2_MAGIC_PRIMARY 0x2068797003000000 */
    uint32_t  exit_reason;             /* +0x4008 (1 sync/2 error/3 irq/4 fiq) */
    uint8_t   pad_400c[0x4010 - 0x400c];
    uint64_t  esr_word;                /* +0x4010 (>>26 = EC)               */
    uint64_t  iss;                     /* +0x4018 (SVC ISS / exit record)   */
    uint64_t  synth_ipa;               /* +0x4028 (HPFAR_EL2-derived IPA)   */

    /* +0x4030 .. +0x40c0 : ACTIVE bank (HV_EL2_ACTIVE_BASE), 18 x 64-bit.
     *   Named slots (est.): SCTLR +0x4030, TCR +0x4038, HCR +0x4040,
     *   CPTR +0x4048, misc0 +0x4050, MAIR +0x4058, +0x4060, +0x4068..+0x40b0,
     *   el2_reg9 +0x40b8. The apply fn (b98dd40) merges template slots into
     *   these under the config masks. */
    uint64_t  active_reg[18];          /* +0x4030 .. +0x40c0 */

    /* +0x40c0 .. +0x40f8 : guest-saved EL2 registers (HV_EL2_GSAVE_BASE),
     *   8 x 64-bit, compared/committed by hv_el2_state_commit. */
    uint64_t  gsave[8];                /* +0x40c0 .. +0x4100 */
    uint64_t  el2_ctl;                 /* +0x4100 */
    uint64_t  el2_hipr;                /* +0x4108 */
    uint64_t  el2_mask;                /* +0x4110 */
    uint64_t  el2_flags;               /* +0x4118 (dirty/flags; bit49 = hyp-pt-active) */
    uint64_t  vbar;                    /* +0x4120 HV_EL2_VBAR (captured VBAR_EL2) */
    uint8_t   pad_4128[0x4138 - 0x4128];
    uint64_t  svcr;                    /* +0x4138 SVCR_EL2-style mode (bits 0/1) */
    uint16_t  sme_guard;               /* +0x4140 (SME save-state guard)     */
    uint8_t   pad_4142[0x4148 - 0x4142];
    uint64_t  el2_scratch_va;          /* +0x4148 (0x4000 SVE/EL2 scratch VA) */
    uint64_t  el2_block_base;          /* +0x4150 HV_EL2_GUEST_PT (EL2 xlate block base) */
};

/* --- prototypes (est.) --- */

/*
 * hv_vcpu_run_state — the per-vCPU run object used by hv_vcpu_run_prepare
 * (est. hv_vcpu_run_prepare) and hv_el2_state_commit (hv_el2_state_commit):
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
extern uint64_t hv_el2_features;            /* DAT_fffffe0007e0d800 EL2 features */
extern uint16_t hv_el2_capable;             /* DAT_fffffe0007e0d81e feature flag bit 0 */
extern uint64_t hv_build_gate;              /* DAT_fffffe0007e0da68 build-path gate (==0) */
extern uint64_t hv_soc_feature_index;       /* DAT_fffffe0007e31628 SoC feature index */
extern uint8_t  hv_vm_wire_fault_table[];   /* DAT_fffffe0007d813d8 {int,char*} VM_MAP_WIRE fault table */
extern uint8_t  hv_vm_unwire_fault_table[]; /* DAT_fffffe0007d81408 {int,char*} VM_MAP_UNWIRE fault table */
extern uint64_t tpidr_el1;                  /* per-cpu data base (kernel) */

/* vcpu-core tree, not decompiled here (see docs/chain-map.md).
 * hv_vcpu_attach (FUN_fffffe000b986e50) prototype lives in hv_internal.h. */

#endif /* _HV_VMM_H_ */
