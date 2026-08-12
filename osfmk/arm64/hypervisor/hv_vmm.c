/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_vmm.c — EL2 register state construction and feature reads.
 *
 * Owned by the el2-state tree.
 * Seed roots: FUN_fffffe000b9895b8 (est. hv_el2_state_build),
 *   FUN_fffffe000b98dd40 (hv_el2_state_apply), FUN_fffffe000b98dd04
 *   (hv_vcpu_run_prepare), FUN_fffffe000b98ded4 (hv_el2_state_commit),
 *   FUN_fffffe000b98e020 (hv_copyin_user), FUN_fffffe000b98e12c
 *   (hv_vcpu_slot_op), FUN_fffffe000b98e344 (hv_el2_pt_alloc), plus the
 *   table-dispatched wrapper FUN_fffffe000b98e99c.
 *
 * See hv_vmm.h for the EL2 state offsets. All register-identity names are
 * estimates; constants are recorded verbatim. EL2 sysreg reads stay literal.
 */

#include "hv_vmm.h"

/* EL2 state magic/version stored at +0x4000 of the per-CPU block. */
#define HV_EL2_MAGIC_PRIMARY  0x2068797003000000ULL

/*
 * EL2 register constants written by FUN_fffffe000b9895b8 and the offsets
 * they land in. All are ESTIMATES of the named register; bit-field decodes
 * are against the ARM ARM AArch64 system-register encodings and are marked
 * unverified because the kernelcache is stripped (we only see the 64-bit
 * value, not the sysreg it is written to).
 *
 *   +0x4030  SCTLR_EL2 (est): base = cfg.sctlr_mask | 0x100000;
 *            feature bit 0 adds 0x20000000100000.
 *            0x100000      = bit 20 = SCTLR_EL2.I0C (icache coherent) [unverified]
 *            0x20000000000000 = bit 53 = SCTLR_EL2 reserved (TBI/EEOS region) [unverified]
 *   +0x4038  TCR_EL2 (est): from cfg.tcr_mask (+0x20a0).
 *   +0x4040  HCR_EL2 (est): 0x10300000
 *            bits: 0x10000000=28 (TVM, trap VM ops), 0x200000=21 (TID3),
 *                  0x100000=20 (TACR) [unverified]
 *   +0x4048  CPTR_EL2 (est): 0x8000e00
 *            bits: 0x80000000=31 (TCPAC, trap CPTR access), 0x800=11 (TTA),
 *                  0x400=10 (TFP, trap FP), 0x200=9 (TAM) [unverified]
 *   +0x4050  el2_misc0 (est): 0x80000000 (bit 31)
 *   +0x4058  MAIR_EL2 (est): 0x610f0000
 *            attr bytes: 0x61 (Write-Back Normal), 0x0f (Device-nGnRnE/NC) [unverified]
 *   +0x40b8  el2_reg9 (est): 0x3c00 (bits 10,11,12,13)  [unverified]
 *   +0x4100  el2_ctl (est): 0x28 (bits 3,5)
 *   +0x4118  el2_flags (est): 0x5 (bits 0,2); bit 49 (0x40000000000000)
 *            set by hv_el2_pt_alloc to mark "hyp translation active"
 *   +0x6a8   template SCTLR (est): 0x30000100000
 *            bits 0x300000000000=49,48; 0x100000=20 [unverified]
 *   +0x6b8   template HCR (est): 0x300000 (bits 20,21)
 *   +0x6d0   template MAIR (est): 0x610f0000
 *   +0x730   template el2_reg9 (est): 0x1c00 (bits 10,11,12)
 */

/*
 * FUN_fffffe000b9895b8 @ 0xfffffe000b9895b8   (est. hv_el2_state_build)
 * Ghidra: void FUN_fffffe000b9895b8(long *param_1,long param_2,uint param_3)
 * Builds the initial per-CPU EL2 register state. param_1 = hv_vm (field 0 =
 * hv_vm_config), param_2 = per-CPU EL2 state block base, param_3 = flags
 * (bit 0 == primary vCPU). Writes the magic header, reads EL2 sysregs, then
 * fills the active (+0x4030..) and template (+0x6a8..) EL2 register banks
 * with HCR/SCTLR/TCR/MAIR/CPTR-style constants, wires two translation pages
 * (param_2+0x1000/0x2000) into the vm when primary, and stores an EL2 state
 * mask + sysreg captures in the far region.
 * Confidence: high (ground-truth anchor, matches kernelcache.md)
 * Notes: decompiler warnings "Control flow encountered bad instruction data"
 *   and "Removing unreachable block (ram,0xfffffe000b989768)" — the
 *   DAT_fffffe0007e0da68 != 0 branch is decompiled as halt_baddata (dead
 *   here; that global is 0). UnkSytemRegRead(3,4,0xc,0xb,1) and
 *   (3,4,0xf,0xc,0) stay literal; register identity unverified. Reads
 *   DAT_fffffe0007e0d81e (feature bit) and DAT_fffffe0007e31628 (SoC feature
 *   index; >4 clears a TCR bit). HCR_EL2 = 0x10300000 has trap bits 20/21/24;
 *   SCTLR_EL2 mask uses 0x100000/0x20000000100000. Register names are
 *   estimates of the register each offset holds.
 */
void hv_el2_state_build(struct hv_vm *vm, uint8_t *el2, uint32_t flags)
{
    struct hv_vm_config *cfg = vm->cfg;
    uint64_t magic, sysreg, sctlr_mask;

    if (flags == 0) {
        magic = HV_EL2_MAGIC_PRIMARY;
    } else {
        magic = cfg->el2_state_id;               /* +0x21a0 */
    }
    EL2_RW(el2, HV_EL2_MAGIC, magic);            /* +0x4000 */
    *(uint32_t *)(el2 + 0x4008) = 0;

    sysreg = UnkSytemRegRead(3,4,0xc,0xb,1);     /* op1=4 ⇒ EL2; identity unverified */
    EL2_RW(el2, HV_EL2_VBAR, sysreg & 0xffffffff);   /* +0x4120 */

    if (DAT_fffffe0007e0da68 == 0) {             /* runtime: 0 (feature global) */
        EL2_RW(el2, 0x4148, 0);
        sctlr_mask = cfg->sctlr_mask;            /* +0x2088 */
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x0, sctlr_mask | 0x100000);   /* sctlr (est) */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x0, 0x30000100000);
        if ((DAT_fffffe0007e0d81e & 1) != 0) {   /* feature bit 0 */
            EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x0, sctlr_mask | 0x20000000100000);
            EL2_RW(el2, HV_EL2_TMPL_BASE + 0x0,
                   EL2_RD(el2, HV_EL2_TMPL_BASE + 0x0) | 0x20000000000000);
        }
        EL2_RW(el2, HV_EL2_CTL, 0x28);           /* +0x4100 */
        EL2_RW(el2, 0x778, 0);                   /* tmpl_ctl */
        EL2_RW(el2, HV_EL2_TCR, cfg->tcr_mask);  /* +0x20a0, tcr (est) */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x8, 0);
        EL2_RW(el2, HV_EL2_HCR, 0x10300000);     /* hcr (est): bits 20/21/24 */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x10, 0x300000);
        EL2_RW(el2, HV_EL2_CPTR, 0x8000e00);     /* cptr (est) */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x18, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x20, 0x80000000);   /* +0x4050 */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x20, 0);
        EL2_RW(el2, HV_EL2_MAIR, 0x610f0000);    /* +0x4058, mair (est) */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x28, 0x610f0000);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x30, 0);             /* +0x4060 */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x30, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x88, 0x3c00);        /* +0x40b8 */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x88, 0x1c00);          /* tmpl[17] */
        /* el2_reg[1..9] = 0; tmpl[7..16] = 0 */
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x38, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x40, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x38, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x40, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x48, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x48, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x50, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x50, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x58, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x58, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x60, DAT_fffffe0007e0d800);  /* +0x4090: EL2 features */
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x60, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x68, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x68, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x70, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x70, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x78, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x78, 0);
        EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x80, 0);
        EL2_RW(el2, HV_EL2_TMPL_BASE + 0x80, 0);
        EL2_RW(el2, 0x780, 0);
        EL2_RW(el2, HV_EL2_FLAGS, 5);            /* +0x4118 */
        if ((flags & 1) == 0) {                  /* primary vCPU */
            vm->built = 0;                       /* byte at +0xb8 */
            vm->page0 = (uint64_t)el2 + 0x1000;
            vm->page1 = (uint64_t)el2 + 0x2000;
        }
        sysreg = UnkSytemRegRead(3,4,0xf,0xc,0); /* op1=4 ⇒ EL2; identity unverified */
        EL2_RW(el2, HV_EL2_SYSREG, sysreg);      /* +0x9f0 */
        EL2_RW(el2, HV_EL2_VER, 3);              /* +0xa28 */
        if (4 < DAT_fffffe0007e31628) {          /* SoC feature index */
            EL2_RW(el2, HV_EL2_TCR, EL2_RD(el2, HV_EL2_TCR) & 0xfffffffffffbffffULL);
        }
        EL2_RW(el2, HV_EL2_HIPR, 0xffffffffffffffffULL);       /* +0x4108 */
        EL2_RW(el2, HV_EL2_MASK,
               ~(cfg->hipr_mask /* +0x2118 */ | EL2_RD(el2, HV_EL2_FLAGS)));
    }
}

/*
 * FUN_fffffe000b98dd40 @ 0xfffffe000b98dd40   (est. hv_el2_state_apply)
 * Ghidra: void FUN_fffffe000b98dd40(long *param_1)
 * Merges the template (requested) EL2 register values (+0x6a8..) into the
 * active set (+0x4030..), applying per-register config masks from
 * hv_vm_config (+0x2088..). Called by the vcpu hub FUN_fffffe000b989a44 to
 * commit a guest's EL2 register requests to the live state.
 * Confidence: medium (inferred from param_1[0x16] -> el2 base and *param_1
 *   -> cfg; matches template/active split in b9895b8)
 * Notes: bit expressions are exact copies of the decompiler output; the
 *   sctlr/tcr merges combine cfg masks (mask/val1/val2 triples) with the
 *   current template + active values. Does not touch the features global.
 */
void hv_el2_state_apply(struct hv_vm *vm)
{
    uint8_t *el2 = vm->el2;                      /* param_1[0x16] = +0xb0 */
    struct hv_vm_config *cfg = vm->cfg;          /* *param_1 */
    uint64_t val2, mask, val1;

    /* sctlr (active +0x4030 <- tmpl +0x6a8) */
    val2 = cfg->sctlr_val2; mask = cfg->sctlr_mask; val1 = cfg->sctlr_val1;
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x0,
        ((val2 & mask | val1) & EL2_TMPL(el2, 0) |
         EL2_ACTIVE(el2, 0) & ~val1) &
        (EL2_TMPL(el2, 0) | ~val2 | mask));

    /* +0x4100 bit4 <- +0x778 bit4 */
    EL2_RW(el2, HV_EL2_CTL,
        EL2_RD(el2, HV_EL2_CTL) & 0xffffffffffffffe0 |
        EL2_RD(el2, HV_EL2_CTL) & 0xf |
        ((EL2_RD(el2, 0x778) >> 4 & 1) << 4));

    /* tcr (active +0x4038 <- tmpl +0x6b0) */
    val2 = cfg->tcr_val2; mask = cfg->tcr_mask; val1 = cfg->tcr_val1;
    EL2_RW(el2, HV_EL2_TCR,
        ((val2 & mask | val1) & EL2_TMPL(el2, 1) |
         EL2_ACTIVE(el2, 1) & ~val1) &
        (EL2_TMPL(el2, 1) | ~val2 | mask));

    EL2_RW(el2, HV_EL2_HCR,
        EL2_TMPL(el2, 2) & 0x80300000 | EL2_ACTIVE(el2, 2) & 0xffffffff7fcfffff);
    EL2_RW(el2, HV_EL2_CPTR,
        EL2_TMPL(el2, 3) & 0x300 | EL2_ACTIVE(el2, 3) & 0xfffffffffffffeff);
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x20, EL2_TMPL(el2, 4));   /* +0x4050 */
    EL2_RW(el2, HV_EL2_MAIR, EL2_TMPL(el2, 5));                /* +0x4058 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x30, EL2_TMPL(el2, 6));  /* +0x4060 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x88,
        EL2_TMPL(el2, 17) & 0xffffffffffffdfff | EL2_ACTIVE(el2, 17) & 0x3c00);
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x38, EL2_TMPL(el2, 7));  /* +0x4068 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x40, EL2_TMPL(el2, 8));  /* +0x4070 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x48, EL2_TMPL(el2, 9));  /* +0x4078 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x50, EL2_TMPL(el2, 10)); /* +0x4080 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x58, EL2_TMPL(el2, 11)); /* +0x4088 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x60,
        EL2_TMPL(el2, 12) & 0x1ec00 | EL2_ACTIVE(el2, 12) & 0xfffffffffffe13ff);
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x68,
        EL2_ACTIVE(el2, 13) & ~1ULL | EL2_TMPL(el2, 13) & 1);
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x70, EL2_TMPL(el2, 14)); /* +0x40a0 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x78, EL2_TMPL(el2, 15)); /* +0x40a8 */
    EL2_RW(el2, HV_EL2_ACTIVE_BASE + 0x80,
        EL2_ACTIVE(el2, 16) & ~1ULL | EL2_TMPL(el2, 16) & 1);
}

/*
 * FUN_fffffe000b98dd04 @ 0xfffffe000b98dd04   (est. hv_vcpu_run_prepare)
 * Ghidra: void FUN_fffffe000b98dd04(long param_1,int param_2)
 * Sets up a vCPU run request: transitions a state word (2 -> 1), records the
 * run buffer, and delegates the actual run to FUN_fffffe000b986e50
 * (vcpu-core tree, not decompiled here).
 * Confidence: medium (inferred from state transition + buffer setup)
 * Notes: the +0xf0 field is a pointer to an int state that goes 2->1; +8 is
 *   a buffer whose +8/+0x10 are written with param_2; +0xb0 aliases it.
 *   Calls FUN_fffffe000b986e50 (est. hv_vcpu_run, vcpu-core tree).
 */
void hv_vcpu_run_prepare(struct hv_vcpu_run_state *vcpu, int param2)
{
    if (*vcpu->state_ptr == 2) {
        *vcpu->state_ptr = 1;
    }
    vcpu->runbuf[1] = (uint64_t)param2;          /* runbuf->+8 */
    vcpu->runbuf[2] = 0;                         /* runbuf->+0x10 */
    vcpu->runbuf_slot = (uint64_t)vcpu->runbuf;  /* +0xb0 */
    vcpu->state2 = 0;                            /* +0xe8 */
    vcpu->state_ptr = NULL;                      /* +0xf0 */
    FUN_fffffe000b986e50(0);   /* est. hv_vcpu_run — vcpu-core tree */
}

/*
 * FUN_fffffe000b98ded4 @ 0xfffffe000b98ded4   (est. hv_el2_state_commit)
 * Ghidra: void FUN_fffffe000b98ded4(long param_1)
 * Iterates the 8 dirty-tracking registers (template +0x738..0x770 vs
 * guest-saved +0x40c0..0x40f8). For each slot whose "changed" bit (bit 32)
 * is set, validates the saved value against the current guest value, then
 * clears the change flag in both the saved and template words once committed.
 * This is the "write back committed EL2 regs" path.
 * Confidence: low (shape-only: complex compare/clear loop, no strong identity)
 * Notes: bit 32 (0x100000000) is the dirty flag in each 64-bit word; the
 *   shifted-bit tests (>>0x3d, >>0x3e) gate the commit. Accesses the
 *   run-buffer base at +0xb0 (same field hv_vcpu_run_prepare writes).
 */
void hv_el2_state_commit(struct hv_vcpu_run_state *vcpu)
{
    uint8_t *base = (uint8_t *)vcpu->runbuf_slot;  /* +0xb0 */
    uint64_t off, dirty_word, saved, r;
    int i, s, dup;

    for (off = 0; off < 0x40; off += 8) {        /* 8 slots */
        dirty_word = EL2_RD(base, HV_EL2_DIRTY_BASE + off);
        if ((dirty_word >> 0x20 & 1) != 0) {
            saved = EL2_RD(base, HV_EL2_GSAVE_BASE + off);
            if ((dirty_word & 0xfffffffeffffffffULL) != saved) {
                /*
                 * Gate the commit: committable only if bit 45 is set, OR if
                 * bit 46 is set and no OTHER saved register (>>0x3e tag)
                 * already holds the same low-32 address i as this word.
                 * (Equivalent to the decompiler's nested compare loop.)
                 */
                i = (int)dirty_word;
                dup = 0;
                for (s = 0; s < 8; s++) {
                    if (s * 8 == (int)off) continue;      /* skip current slot */
                    r = EL2_RD(base, HV_EL2_GSAVE_BASE + s * 8);
                    if ((r >> 0x3e != 0) && (int)r == i) { dup = 1; break; }
                }
                if (!((dirty_word >> 0x3d & 1) != 0 || (dirty_word >> 0x3e != 0 && dup))) {
                    /* not committable (decompiler: goto LAB_fffffe000b98def8) — skip */
                } else {
                    EL2_RW(base, HV_EL2_GSAVE_BASE + off, dirty_word & 0xfffffffeffffffffULL);
                    base = (uint8_t *)vcpu->runbuf_slot;
                }
            }
            EL2_RW(base, HV_EL2_DIRTY_BASE + off,
                   EL2_RD(base, HV_EL2_DIRTY_BASE + off) & 0xfffffffeffffffffULL);
        }
    }
}

/*
 * FUN_fffffe000b98e020 @ 0xfffffe000b98e020   (est. hv_copyin_user)
 * Ghidra: undefined4 FUN_fffffe000b98e020(undefined8 param_1,long *param_2,
 *         undefined8 param_3,long param_4)
 * Validates and copies a user buffer of length param_4 from address *param_2.
 * First validates the range via kernel_mem_validate (FUN_fffffe000b8b51c8)
 * with protection 0x1c100008, then copies via kernel_copyin
 * (FUN_fffffe000b8afb18) with the VM_MAP_WIRE fault table. Returns 0 on
 * success or an hv error code (0xfae94001/3/5).
 * Confidence: medium (two-step validate-then-copyin shape, kernel helper refs)
 * Notes: error decode — kernel result 1 -> 0xfae94003, 3 -> 0xfae94005,
 *   else 0xfae94001. DAT_fffffe0007d813d8 is a {int,char*} fault-name array
 *   pointing at "VM_MAP_WIRE" (fffffe0007067b6b) / "VM_MAP_UNWIRE"
 *   (fffffe0007067b77). On copyin failure calls kernel_mem_release
 *   (FUN_fffffe000b8a8078) to unwind the validated range.
 */
uint32_t hv_copyin_user(void *vm, void **dst, uint64_t src, uint64_t len)
{
    int kr, ret;
    int prot = 3, prot2 = 3;

    kr = kernel_mem_validate(0, dst, len, 0, 0x1c100008, (uint64_t)vm, src, 0,
                             &prot2, &prot, 2);            /* FUN_fffffe000b8b51c8 */
    if (kr == 0) {
        kr = kernel_copyin(0, (uint64_t)*dst, (uint64_t)*dst + len, 3, 0x1c,
                           0, 0, (uint64_t *)&DAT_fffffe0007d813d8);
        /* FUN_fffffe000b8afb18 */
        if (kr == 0) {
            return 0;
        }
        ret = 0xfae94003;
        if (kr != 1) ret = 0xfae94001;
        ret = 0xfae94005;
        if (kr != 3) ret = (kr == 1) ? 0xfae94003 : 0xfae94001;
        kernel_mem_release(0, (uint64_t)*dst, len);        /* FUN_fffffe000b8a8078 */
    } else {
        ret = 0xfae94003;
        if (kr != 1) ret = 0xfae94001;
        ret = 0xfae94005;
        if (kr != 3) ret = (kr == 1) ? 0xfae94003 : 0xfae94001;
    }
    return (uint32_t)ret;
}

/*
 * FUN_fffffe000b98e12c @ 0xfffffe000b98e12c   (est. hv_vcpu_slot_op)
 * Ghidra: undefined4 FUN_fffffe000b98e12c(long *param_1,ulong param_2,ulong param_3)
 * Performs an operation on a vCPU slot (index param_2 < 8, sub-field
 * param_3 < 64). Bumps the vcpu object's refcount (LORelease on unwind),
 * transitions a per-slot word from 1 -> 2, then either wires a fresh
 * translation (kernel_memzero + copyout) or uses the existing EL2 config to
 * copy the guest memory window in/out. Returns 0 or an hv error code.
 * Confidence: low (complex slot/refcount logic, no strong identity)
 * Notes: cfg->vcpu_slot[] at +0x2148; object refcount at *(obj) (negative ->
 *   0xfae94002, zero -> 0xfae94006). kernel deps: kernel_lock_ref
 *   (FUN_fffffe000b7f62e8), kernel_memzero (FUN_fffffe000b8b6860),
 *   kernel_copyout (FUN_fffffe000b8b49e8), kernel_copyin2
 *   (FUN_fffffe000b8b122c, with DAT_fffffe0007d81408 fault table =
 *   {20,"VM_MAP_UNWIRE",19,"VM_MAP_WIRE"...}), kernel_mem_release
 *   (FUN_fffffe000b8a8078 thunk @ b9141a4). Uses param_1[0x11] (+0x88) and
 *   cfg->el2_cfg (+0x2198). LORelease on every unwind path.
 */
uint32_t hv_vcpu_slot_op(struct hv_vm *vm, uint64_t slot, uint64_t which)
{
    struct hv_vm_config *cfg = vm->cfg;
    int *vcpu;
    int *slot_desc;
    uint8_t *base;
    uint64_t src, dst, buf, len, count;
    int ref, cur, kr;
    uint32_t ret;

    if (7 < slot) return 0xfae94003;
    if (0x3f < which) return 0xfae94003;

    vcpu = (int *)cfg->vcpu_slot[slot];          /* +0x2148 + slot*8 */
    do {
        if (*vcpu < 0) return 0xfae94002;
        cur = *vcpu;
        ref = *vcpu;
    } while (ref != cur);                        /* read-stable refcount */
    *vcpu = cur + 1;

    if (*(uint64_t *)(vcpu + 0x402) == 0) {      /* +0x1008 */
        *vcpu = *vcpu - 1;
        LORelease();
        return 0xfae94006;
    }

    slot_desc = (int *)((uint8_t *)vcpu + which * 0x40 + 8);
    cur = *slot_desc;
    if (cur != 1) {
        *vcpu = *vcpu - 1;
        LORelease();
        return cur == 0 ? 0xfae94003 : 0xfae94002;
    }
    *slot_desc = 2;

    if (*(uint64_t *)(slot_desc + 4) == 0) {     /* +0x10 */
        buf = *(uint64_t *)(slot_desc + 2);      /* +0x8 (lVar11) */
        base = (uint8_t *)vm->base;              /* param_1[0x11] = +0x88 */
        len = 0x4000;
        count = 0x4000;
        ret = 0xfae94001;
        if (base == 0) goto commit;
    } else {
        src = cfg->el2_cfg;                      /* +0x2198 */
        dst = *(uint64_t *)(slot_desc + 2);      /* +0x8 */
        kernel_lock_ref(0);                      /* FUN_fffffe000b7f62e8 */
        kernel_memzero(0, dst, dst + 0x8000, 1, 0);   /* FUN_fffffe000b8b6860 */
        count = *(uint32_t *)(src + 0x20);
        len   = *(uint32_t *)(src + 0x28);
        buf = *(uint64_t *)(slot_desc + 4);      /* +0x10 (lVar11) */
        base = (uint8_t *)vm->base;              /* +0x88 */
        if (base == 0) {
            ret = 0xfae94001;
            goto commit;
        }
        if (len == 0) {
            len = 0;
            ret = 0;
            goto commit;
        }
    }

    kr = kernel_copyout((uint64_t)base, *(uint64_t *)(slot_desc + 6), /* +0x18 */
                        len + *(uint64_t *)(slot_desc + 6), 0, slot_desc[8]);
        /* FUN_fffffe000b8b49e8 */
    ret = kr != 0 ? 0xfae94001 : 0;

commit:
    kr = kernel_copyin2(0, buf, count + len + buf, 0,
                        (uint64_t *)&DAT_fffffe0007d81408);  /* FUN_fffffe000b8b122c */
    if (kr != 0) ret = 0xfae94001;
    kr = kernel_mem_release(0, buf, count + len);          /* FUN_fffffe000b8a8078 */
    if (kr != 0) ret = 0xfae94001;

    slot_desc[2] = 0;                            /* +8 */
    slot_desc[3] = 0;                            /* +0xc */
    slot_desc[4] = 0;                            /* +0x10 */
    slot_desc[5] = 0;                            /* +0x14 */
    if (*slot_desc == 2) *slot_desc = 0;
    *vcpu = *vcpu - 1;
    LORelease();
    return ret;
}

/*
 * FUN_fffffe000b98e344 @ 0xfffffe000b98e344   (est. hv_el2_pt_alloc)
 * Ghidra: void FUN_fffffe000b98e344(long *param_1)
 * Allocates the 0x4000-byte EL2 translation block for a vCPU (via
 * kernel_alloc FUN_fffffe000b8a6c14), validates it with
 * kernel_mem_validate (FUN_fffffe000b8b51c8), stores it into the per-CPU EL2
 * state at +0x4150, sets the "hyp running" flag bit (bit 49 of +0x4118), and
 * on the last reference clears it via an EL2 TLB flush (FUN_fffffe000b96c6d4).
 * Uses the per-cpu counter at tpidr_el1 + 0x1c0; panics on overflow via
 * FUN_fffffe000c0f1874. Marks vm->built = 1 on exit.
 * Confidence: medium (allocation + per-cpu refcount + flush shape)
 * Notes: kernel deps: kernel_alloc (FUN_fffffe000b8a6c14, size 0x4000,
 *   prot 0x10080), kernel_mem_validate (FUN_fffffe000b8b51c8),
 *   kernel_lock_ref (FUN_fffffe000b7f62e8), kernel_memzero
 *   (FUN_fffffe000b8b6860), kernel_tlb_flush (FUN_fffffe000b96c6d4),
 *   kernel_panic noreturn (FUN_fffffe000c0f1874). param_1[0x18] (+0xc0) is
 *   the allocation pointer; param_1[0x16] (+0xb0) is the el2 state base.
 */
void hv_el2_pt_alloc(struct hv_vm *vm)
{
    uint64_t block = 0;
    int kr, *cnt;
    int prot = 3, prot2 = 3;

    if (vm->pt_block == 0) {
        kr = kernel_alloc(0, 0x4000, 0, 0x10080, 0x1c, 0);   /* FUN_fffffe000b8a6c14 */
        if (kr == 0) {
            kr = kernel_mem_validate((void *)((uint64_t)vm->cfg + 0x10), &block,
                                     0x4000, 0, 0x1c100008, 0, block, 0,
                                     &prot2, &prot, 2);      /* FUN_fffffe000b8b51c8 */
            if (kr == 0) {
                cnt = (int *)(tpidr_el1 + 0x1c0);
                *cnt = *cnt + 1;
                vm->pt_block = block;
                EL2_RW(vm->el2, HV_EL2_GUEST_PT, block);     /* +0x4150 */
                EL2_RW(vm->el2, HV_EL2_FLAGS,
                       EL2_RD(vm->el2, HV_EL2_FLAGS) | 0x40000000000000ULL);  /* bit49 */
                if (*cnt == 0) {
                    kernel_panic();                          /* FUN_fffffe000c0f1874, noreturn */
                }
                kr = *cnt - 1;
                *cnt = kr;
                if (kr == 0 &&
                    (*(uint8_t *)(*(uint64_t *)(tpidr_el1 + 0x1b8) + 0x4c) >> 2 & 1) != 0) {
                    kernel_tlb_flush();                      /* FUN_fffffe000b96c6d4 */
                }
            } else {
                kernel_lock_ref(0);                          /* FUN_fffffe000b7f62e8 */
                kernel_memzero(0, block, block + 0x4000, 1, 0);  /* FUN_fffffe000b8b6860 */
            }
        }
    }
    vm->built = 1;                                           /* +0xb8 */
}

/*
 * FUN_fffffe000b98e99c @ 0xfffffe000b98e99c   (est. hv_el2_pt_alloc_wrapper)
 * Ghidra: undefined8 FUN_fffffe000b98e99c(undefined8 param_1)
 * Thin table-dispatched wrapper: calls FUN_fffffe000b98e344 on its argument
 * and returns 0. No direct callers (dispatched via the vcpu hub's table).
 * Confidence: high (trivial 2-instruction wrapper, callee confirmed)
 * Notes: only callee is FUN_fffffe000b98e344.
 */
uint64_t hv_el2_pt_alloc_wrapper(uint64_t vcpu)
{
    hv_el2_pt_alloc((struct hv_vm *)vcpu);
    return 0;
}
