/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * osfmk/arm64/hv_el2_vectors.s — EL2 exception vector handlers.
 *
 * Owned by the el2-vectors tree. These four handlers (entered from VBAR_EL2
 * when the guest at EL1/EL0 traps) are pure assembly: each saves the guest's
 * EL1 register state into the per-CPU guest-state frame, switches EL2 control
 * state, verifies the PAC "JOP hash" of the saved EL2 sysregs, writes an
 * exit-reason word at frame+0x4008, and branches to the common dispatch
 * hv_el2_common_dispatch with x0 = frame base, x1 = EL1 return target,
 * w2 = exit reason.
 *
 * Ground-truth function bodies (Ghidra, transcrived verbatim):
 *   hv_el2_vector_sync   FUN_fffffe000b760b94  body fffffe000b760b10-...0ed7 (sync)
 *   hv_el2_vector_irq    FUN_fffffe000b760f04  body fffffe000b760f04-...125f
 *   hv_el2_vector_fiq    FUN_fffffe000b761260  body fffffe000b761260-...15bb
 *   hv_el2_vector_error  FUN_fffffe000b7615bc  body fffffe000b7615bc-...18ff
 *   hv_el2_jop_hash_panic (shared stub)        body fffffe000b760b10-...0b2c
 *
 * Frame / register-offset conventions (see hv_el2.h HV_EL2_FRAME_*):
 *   frame+0x370 sp_el0, +0x378 sp_el1, +0x350 mdscr_el1, +0x358 tpidr_el1,
 *   +0x360 tpidr_el0, +0x368 tpidrro_el0, +0x380 par_el1, +0x388 csselr_el1,
 *   +0x390/+0x398 EL2 ctrl sysregs, +0x9f0 EL2 ctrl, +0x3a0/+0x3a8/+0x3b0
 *   +0x4138 EL2 ctrl save slots, GPRs x2..x30 at +0x18..+0xf8, FP q0..q31 at
 *   +0x140..+0x320, fpsr +0x340, fpcr +0x344, elr/spsr/far/esr_el1 at
 *   +0x108/+0x110/+0x118/+0x120, exit-reason word at +0x4008.
 *
 * The per-CPU EL2 block (TPIDR_EL2) holds the hypervisor's own saved control
 * regs: [0]=cptr_el2, [0x8]=mdscr_el1, [0x10]=tpidr_el1, [0x18]=tpidr_el0,
 * [0x20]=tpidrro_el0, [0x28]=guest-state frame base, [0x30]=expected JOP
 * hash, [0x40]+ EL2 ctrl regs, [0x58]/[0x60]/[0x78]/[0x80]/[0x88] EL2 ctrl.
 *
 * This is a faithful, annotated reconstruction (not a bootable kernel): the
 * adrp+add absolute return-targets are shown as the documented EL1 addresses
 * via local labels + @PAGE/@PAGEOFF. It assembles with clang -c for arm64.
 */

    .text
    .arch armv8.5-a+sve+sme
    .p2align 4

/* Shared JOP-hash-mismatch panic stub — b760b10.
 * All four vectors' `b.ne` land here when the PAC "JOP hash" of the saved
 * EL2 sysregs does not match frame+0x30 (saved-state corruption). Falls into
 * kernel_panic_msg_fmt (FUN_fffffe000c0e11ec), noreturn. */
    .p2align 2
/* local (file-internal) symbol: referenced only by the four vectors' b.eq
 * fallthrough; kept non-global so the assembler resolves the branch in-file */
_hv_el2_jop_hash_panic:                     /* fffffe000b760b10 */
    msr  spsel, #1                          /* SPSel = 1 (use SP_EL1) */
    str  x2, [sp, #-0x20]!                  /* push x2 (mismatched hash) */
    str  x1, [sp, #0x8]                     /* save x1 (frame/saved reg) */
    mrs  x0, tpidr_el2                      /* per-CPU EL2 block */
    str  x0, [sp, #0x10]
    adr  x0, .L_jop_hash_msg                /* panic format string */
    bl   _kernel_panic_msg_fmt              /* FUN_fffffe000c0e11ec, noreturn */
.L_jop_hash_msg:
    /* Message string address not pinned; name per the hv_el2.c notes. */
    .asciz "Sysreg JOP hash mismatch detected (guest state corruption)"

/* =====================================================================
 * hv_el2_vector_sync — FUN_fffffe000b760b94 (body b760b10..b760ed7).
 * Guest synchronous exception (incl. HVC/SVC) entry.
 * Exit reason HV_EL2_EXIT_REASON_SYNC (1); return target b760eec
 * (FUN_fffffe000b760eec: classify ESR + return to guest).
 * ===================================================================== */
    .p2align 4
    .global _hv_el2_vector_sync
_hv_el2_vector_sync:                        /* fffffe000b760b94 */
    msr  pan, #1                            /* PSTATE.PAN = 1 */
    mrs  x1, tpidr_el2                      /* per-CPU EL2 block */
    ldr  x1, [x1, #0x90]                    /* EL2 guest-state frame base (+0x90 field) */
    mrs  x0, sp_el0                         /* guest SP_EL0 */
    str  x0, [x1, #0x370]                   /* frame+0x370 = sp_el0 */
    mrs  x0, sp_el1                         /* guest SP_EL1 */
    str  x0, [x1, #0x378]                   /* frame+0x378 = sp_el1 */
    msr  sp_el0, x1                         /* sp_el0 = frame base */
    ldp  x0, x1, [sp], #0x10                /* pop saved x0/x1 off frame stack */
    msr  spsel, #0                          /* SPSel = 0 (use SP_EL0) */
    stp  x0, x1, [sp, #0x8]                 /* re-store at frame+0x8 */
    mov  x0, #0
    msr  s3_5_c15_c1_3, x0                  /* clear (3,5,c15,c1,3) IMPDEF ctrl */
    mrs  x0, s3_4_c12_c11_0                 /* (3,4,c12,c11,0) ctrl reg */
    and  x0, x0, #-2                        /* clear bit 0 */
    msr  s3_4_c12_c11_0, x0
    mrs  x0, mdscr_el1                      /* guest MDSCR_EL1 */
    str  x0, [sp, #0x350]                   /* frame+0x350 = mdscr_el1 */
    mrs  x0, tpidr_el1                      /* guest TPIDR_EL1 */
    str  x0, [sp, #0x358]                   /* frame+0x358 = tpidr_el1 */
    mrs  x0, tpidr_el0                      /* guest TPIDR_EL0 */
    str  x0, [sp, #0x360]                   /* frame+0x360 = tpidr_el0 */
    mrs  x0, tpidrro_el0                    /* guest TPIDRRO_EL0 */
    str  x0, [sp, #0x368]                   /* frame+0x368 = tpidrro_el0 */
    mrs  x0, par_el1                        /* guest PAR_EL1 */
    str  x0, [sp, #0x380]                   /* frame+0x380 = par_el1 */
    mrs  x0, csselr_el1                     /* guest CSSELR_EL1 */
    str  x0, [sp, #0x388]                   /* frame+0x388 = csselr_el1 */
    mrs  x0, s3_6_c15_c8_3                  /* EL2 ctrl (3,6,c15,c8,3) */
    str  x0, [sp, #0x390]
    mrs  x0, s3_6_c15_c2_5                  /* EL2 ctrl (3,6,c15,c2,5) */
    str  x0, [sp, #0x398]
    mrs  x0, s3_4_c15_c12_0                 /* EL2 ctrl (3,4,c15,c12,0) */
    str  x0, [sp, #0x9f0]
    adrp x0, _hv_el2_capable@GOTPAGE  /* DAT_fffffe0007e0d81e (hv_el2_capable) */
    ldr  x0, [x0, _hv_el2_capable@GOTPAGEOFF]
    ldrb w0, [x0]                     /* EL2-capable feature flag */
    cbz  x0, .L_sync_sysreg                 /* if not EL2-capable, skip EL2 ctrl save */
    mrs  x0, s3_3_c13_c0_7                  /* EL2 ctrl (3,3,c13,c0,7) */
    str  x0, [sp, #0x3a0]                   /* frame+0x3a0 */
.L_sync_sysreg:                             /* fffffe000b760c30 */
    mov  x0, sp                             /* x0 = frame base */
    stp  x2, x3, [x0, #0x18]                /* save guest GPRs */
    stp  x4, x5, [x0, #0x28]
    stp  x6, x7, [x0, #0x38]
    stp  x8, x9, [x0, #0x48]
    stp  x10, x11, [x0, #0x58]
    stp  x12, x13, [x0, #0x68]
    stp  x14, x15, [x0, #0x78]
    stp  x16, x17, [x0, #0x88]
    stp  x18, x19, [x0, #0x98]
    stp  x20, x21, [x0, #0xa8]
    stp  x22, x23, [x0, #0xb8]
    stp  x24, x25, [x0, #0xc8]
    stp  x26, x27, [x0, #0xd8]
    stp  x28, x29, [x0, #0xe8]
    str  x30, [x0, #0xf8]                   /* save guest LR */
    mov  x25, #0
    mrs  x1, cptr_el2                       /* CPTR_EL2 */
    tbz  w1, #0x14, .L_sync_fp_saved        /* bit 20 clear -> skip FP save */
    stp  q0, q1, [x0, #0x140]               /* save guest FP/SIMD q0..q31 */
    stp  q2, q3, [x0, #0x160]
    stp  q4, q5, [x0, #0x180]
    stp  q6, q7, [x0, #0x1a0]
    stp  q8, q9, [x0, #0x1c0]
    stp  q10, q11, [x0, #0x1e0]
    stp  q12, q13, [x0, #0x200]
    stp  q14, q15, [x0, #0x220]
    stp  q16, q17, [x0, #0x240]
    stp  q18, q19, [x0, #0x260]
    stp  q20, q21, [x0, #0x280]
    stp  q22, q23, [x0, #0x2a0]
    stp  q24, q25, [x0, #0x2c0]
    stp  q26, q27, [x0, #0x2e0]
    stp  q28, q29, [x0, #0x300]
    stp  q30, q31, [x0, #0x320]
    mrs  x24, fpsr                         /* guest FPSR */
    str  w24, [x0, #0x340]                 /* frame+0x340 = fpsr */
    mrs  x25, fpcr                         /* guest FPCR */
    str  w25, [x0, #0x344]                 /* frame+0x344 = fpcr */
.L_sync_fp_saved:                           /* fffffe000b760ccc */
    mrs  x22, elr_el1                      /* guest ELR_EL1 */
    mrs  x23, spsr_el1                     /* guest SPSR_EL1 */
    mrs  x20, far_el1                      /* guest FAR_EL1 */
    mrs  x21, esr_el1                      /* guest ESR_EL1 */
    str  x20, [x0, #0x118]                 /* frame+0x118 = far_el1 */
    str  x22, [x0, #0x108]                 /* frame+0x108 = elr_el1 */
    str  x21, [x0, #0x120]                 /* frame+0x120 = esr_el1 */
    str  w23, [x0, #0x110]                 /* frame+0x110 = spsr_el1 */
    adrp x1, _hv_build_gate@GOTPAGE  /* DAT_fffffe0007e0da68 (hv_build_gate) */
    ldr  x1, [x1, _hv_build_gate@GOTPAGEOFF]
    ldr  w1, [x1]                     /* EL2 build gate (==0 skips SVE save) */
    cbz  w1, .L_sync_sve_done               /* if gate==0 skip SVE/SME save */
    mrs  x1, s3_3_c13_c0_5                  /* EL2 ctrl (3,3,c13,c0,5) */
    str  x1, [sp, #0x3a8]
    mrs  x1, s3_0_c1_c2_4                   /* EL2 ctrl (3,0,c1,c2,4) */
    str  x1, [sp, #0x3b0]
    mrs  x1, cptr_el2
    tbz  w1, #0x18, .L_sync_sve_done        /* bit 24 clear -> no SME/SVE ctrl */
    mrs  x1, s3_3_c4_c2_2                   /* SVE ctrl (3,3,c4,c2,2) */
    str  x1, [sp, #0x4138]                  /* frame+0x4138 */
    tbz  w1, #0x0, .L_sync_sve_done         /* SVE-active bit clear -> skip */
    add  x1, sp, #0x4, lsl #12              /* x1 = frame + 0x4000 */
    ldrh w1, [x1, #0x140]                   /* Z-register count (frame+0x4140) */
    mrs  x2, tpidr_el2
    ldr  x2, [x2, #0xb0]                    /* per-CPU SVE save buffer */
    add  x2, x2, #0x40
    str  z0, [x2]                           /* save Z0..Z31 (256-bit) */
    str  z1, [x2, #1, mul vl]
    str  z2, [x2, #2, mul vl]
    str  z3, [x2, #3, mul vl]
    str  z4, [x2, #4, mul vl]
    str  z5, [x2, #5, mul vl]
    str  z6, [x2, #6, mul vl]
    str  z7, [x2, #7, mul vl]
    str  z8, [x2, #8, mul vl]
    str  z9, [x2, #9, mul vl]
    str  z10, [x2, #0xa, mul vl]
    str  z11, [x2, #0xb, mul vl]
    str  z12, [x2, #0xc, mul vl]
    str  z13, [x2, #0xd, mul vl]
    str  z14, [x2, #0xe, mul vl]
    str  z15, [x2, #0xf, mul vl]
    str  z16, [x2, #0x10, mul vl]
    str  z17, [x2, #0x11, mul vl]
    str  z18, [x2, #0x12, mul vl]
    str  z19, [x2, #0x13, mul vl]
    str  z20, [x2, #0x14, mul vl]
    str  z21, [x2, #0x15, mul vl]
    str  z22, [x2, #0x16, mul vl]
    str  z23, [x2, #0x17, mul vl]
    str  z24, [x2, #0x18, mul vl]
    str  z25, [x2, #0x19, mul vl]
    str  z26, [x2, #0x1a, mul vl]
    str  z27, [x2, #0x1b, mul vl]
    str  z28, [x2, #0x1c, mul vl]
    str  z29, [x2, #0x1d, mul vl]
    str  z30, [x2, #0x1e, mul vl]
    str  z31, [x2, #0x1f, mul vl]
    add  x2, x2, x1, lsl #5                 /* advance past Z regs (count*32) */
    str  p0, [x2]                           /* save P0..P15 predicates */
    str  p1, [x2, #1, mul vl]
    str  p2, [x2, #2, mul vl]
    str  p3, [x2, #3, mul vl]
    str  p4, [x2, #4, mul vl]
    str  p5, [x2, #5, mul vl]
    str  p6, [x2, #6, mul vl]
    str  p7, [x2, #7, mul vl]
    str  p8, [x2, #8, mul vl]
    str  p9, [x2, #9, mul vl]
    str  p10, [x2, #0xa, mul vl]
    str  p11, [x2, #0xb, mul vl]
    str  p12, [x2, #0xc, mul vl]
    str  p13, [x2, #0xd, mul vl]
    str  p14, [x2, #0xe, mul vl]
    str  p15, [x2, #0xf, mul vl]
    mrs  x1, fpsr                          /* preserve FPSR across smstop */
    smstop sm                               /* Ghidra: smstop {SM}: stop streaming mode */
    msr  fpsr, x1
.L_sync_sve_done:                           /* fffffe000b760e00 */
    mov  x2, #0
    cmp  x25, x2                           /* FPCR saved? (x25 = 0 when skipped) */
    b.eq .L_sync_fpcr_keep
    msr  fpcr, x2                          /* clear FPCR in the hypervisor */
.L_sync_fpcr_keep:                          /* fffffe000b760e10 */
    mrs  x1, tpidr_el2
    mov  sp, x1                            /* sp = per-CPU EL2 block */
    mrs  x1, s3_4_c15_c10_6                /* EL2 ctrl (3,4,c15,c10,6) */
    str  x1, [sp, #0x40]
    ldr  x1, [sp]                          /* [0] = saved CPTR_EL2 */
    msr  cptr_el2, x1                      /* restore hypervisor CPTR_EL2 */
    ldr  x2, [sp, #0x58]
    msr  s3_3_c13_c0_5, x2                 /* restore EL2 ctrl (3,3,c13,c0,5) */
    ldr  x2, [sp, #0x60]
    msr  s3_0_c1_c2_4, x2                  /* restore EL2 ctrl (3,0,c1,c2,4) */
    ldr  x1, [sp, #0x78]
    msr  s3_4_c15_c12_0, x1                /* restore EL2 ctrl (3,4,c15,c12,0) */
    ldr  x1, [sp, #0x80]
    msr  s3_6_c15_c0_4, x1                 /* restore EL2 ctrl (3,6,c15,c0,4) */
    ldr  x1, [sp, #0x88]
    msr  s3_6_c15_c0_5, x1                 /* restore EL2 ctrl (3,6,c15,c0,5) */
    ldr  x2, [sp, #0x8]                    /* [0x8] = saved MDSCR_EL1 */
    mov  x1, #0xec880000
    movk x1, #0x4040                       /* x1 = 0x4040ec880000 (bitmask) */
    bic  x2, x2, x1                        /* clear MDSCR bits */
    msr  mdscr_el1, x2                     /* restore MDSCR_EL1 */
    mov  x1, sp                            /* x1 = EL2 block base */
    lsl  x1, x1, #4
    orr  x1, x1, #4
    pacga x1, x1, x2                       /* JOP hash: chain(mdscr) */
    ldr  x2, [sp, #0x10]                   /* [0x10] = saved TPIDR_EL1 */
    msr  tpidr_el1, x2                     /* restore TPIDR_EL1 */
    orr  x1, x1, #4
    pacga x1, x1, x2                       /* chain(tpidr_el1) */
    ldr  x2, [sp, #0x18]                   /* [0x18] = saved TPIDR_EL0 */
    msr  tpidr_el0, x2                     /* restore TPIDR_EL0 */
    orr  x1, x1, #4
    pacga x1, x1, x2                       /* chain(tpidr_el0) */
    ldr  x2, [sp, #0x20]                   /* [0x20] = saved TPIDRRO_EL0 */
    msr  tpidrro_el0, x2                   /* restore TPIDRRO_EL0 */
    orr  x1, x1, #4
    pacga x1, x1, x2                       /* chain(tpidrro_el0) */
    ldr  x21, [sp, #0x28]                  /* [0x28] = guest-state frame base */
    orr  x1, x1, #4
    pacga x1, x1, x21                      /* chain(frame base) */
    ldr  x2, [sp, #0x30]                   /* [0x30] = expected JOP hash */
    cmp  x2, x1
    b.eq .L_jop_ok_sync
    b    _hv_el2_jop_hash_panic            /* mismatch -> panic stub */
.L_jop_ok_sync:
    mov  sp, x21                           /* sp = guest-state frame base */
    add  x2, x0, #0x4, lsl #12             /* x2 = frame + 0x4000 */
    mov  w1, #0x1                          /* exit reason = SYNC (1) */
    str  w1, [x2, #0x8]                    /* frame+0x4008 = 1 */
    adr  x1, .L_sync_target           /* EL1 return target b760eec (FUN_fffffe000b760eec, classify+return) */
    b    _hv_el2_common_dispatch           /* -> common dispatch (x0=frame, x1=target) */

/* =====================================================================
 * hv_el2_vector_irq — FUN_fffffe000b760f04 (body b760f04..b76125f).
 * Guest IRQ entry. Exit reason HV_EL2_EXIT_REASON_IRQ (3); return target
 * b75df48 (EL1 irq handler entry). Identical save sequence to sync; only
 * the exit-reason word and the stack/return-target tail differ.
 * ===================================================================== */
    .p2align 4
    .global _hv_el2_vector_irq
_hv_el2_vector_irq:                         /* fffffe000b760f04 */
    msr  pan, #1
    mrs  x1, tpidr_el2
    ldr  x1, [x1, #0x90]                    /* EL2 guest-state frame base */
    mrs  x0, sp_el0
    str  x0, [x1, #0x370]                   /* frame+0x370 = sp_el0 */
    mrs  x0, sp_el1
    str  x0, [x1, #0x378]                   /* frame+0x378 = sp_el1 */
    msr  sp_el0, x1
    ldp  x0, x1, [sp], #0x10
    msr  spsel, #0
    stp  x0, x1, [sp, #0x8]
    mov  x0, #0
    msr  s3_5_c15_c1_3, x0
    mrs  x0, s3_4_c12_c11_0
    and  x0, x0, #-2
    msr  s3_4_c12_c11_0, x0
    mrs  x0, mdscr_el1
    str  x0, [sp, #0x350]                   /* frame+0x350 = mdscr_el1 */
    mrs  x0, tpidr_el1
    str  x0, [sp, #0x358]                   /* frame+0x358 = tpidr_el1 */
    mrs  x0, tpidr_el0
    str  x0, [sp, #0x360]                   /* frame+0x360 = tpidr_el0 */
    mrs  x0, tpidrro_el0
    str  x0, [sp, #0x368]                   /* frame+0x368 = tpidrro_el0 */
    mrs  x0, par_el1
    str  x0, [sp, #0x380]                   /* frame+0x380 = par_el1 */
    mrs  x0, csselr_el1
    str  x0, [sp, #0x388]                   /* frame+0x388 = csselr_el1 */
    mrs  x0, s3_6_c15_c8_3
    str  x0, [sp, #0x390]
    mrs  x0, s3_6_c15_c2_5
    str  x0, [sp, #0x398]
    mrs  x0, s3_4_c15_c12_0
    str  x0, [sp, #0x9f0]
    adrp x0, _hv_el2_capable@GOTPAGE
    ldr  x0, [x0, _hv_el2_capable@GOTPAGEOFF]
    ldrb w0, [x0]  /* hv_el2_capable */
    cbz  x0, .L_irq_sysreg
    mrs  x0, s3_3_c13_c0_7
    str  x0, [sp, #0x3a0]
.L_irq_sysreg:                              /* fffffe000b760fa0 */
    mov  x0, sp
    stp  x2, x3, [x0, #0x18]                /* save guest GPRs */
    stp  x4, x5, [x0, #0x28]
    stp  x6, x7, [x0, #0x38]
    stp  x8, x9, [x0, #0x48]
    stp  x10, x11, [x0, #0x58]
    stp  x12, x13, [x0, #0x68]
    stp  x14, x15, [x0, #0x78]
    stp  x16, x17, [x0, #0x88]
    stp  x18, x19, [x0, #0x98]
    stp  x20, x21, [x0, #0xa8]
    stp  x22, x23, [x0, #0xb8]
    stp  x24, x25, [x0, #0xc8]
    stp  x26, x27, [x0, #0xd8]
    stp  x28, x29, [x0, #0xe8]
    str  x30, [x0, #0xf8]
    mov  x25, #0
    mrs  x1, cptr_el2
    tbz  w1, #0x14, .L_irq_fp_saved         /* bit 20 clear -> skip FP */
    stp  q0, q1, [x0, #0x140]
    stp  q2, q3, [x0, #0x160]
    stp  q4, q5, [x0, #0x180]
    stp  q6, q7, [x0, #0x1a0]
    stp  q8, q9, [x0, #0x1c0]
    stp  q10, q11, [x0, #0x1e0]
    stp  q12, q13, [x0, #0x200]
    stp  q14, q15, [x0, #0x220]
    stp  q16, q17, [x0, #0x240]
    stp  q18, q19, [x0, #0x260]
    stp  q20, q21, [x0, #0x280]
    stp  q22, q23, [x0, #0x2a0]
    stp  q24, q25, [x0, #0x2c0]
    stp  q26, q27, [x0, #0x2e0]
    stp  q28, q29, [x0, #0x300]
    stp  q30, q31, [x0, #0x320]
    mrs  x24, fpsr
    str  w24, [x0, #0x340]                  /* frame+0x340 = fpsr */
    mrs  x25, fpcr
    str  w25, [x0, #0x344]                  /* frame+0x344 = fpcr */
.L_irq_fp_saved:                            /* fffffe000b76103c */
    mrs  x22, elr_el1
    mrs  x23, spsr_el1
    mrs  x20, far_el1
    mrs  x21, esr_el1
    str  x20, [x0, #0x118]
    str  x22, [x0, #0x108]
    str  x21, [x0, #0x120]
    str  w23, [x0, #0x110]
    adrp x1, _hv_build_gate@GOTPAGE
    ldr  x1, [x1, _hv_build_gate@GOTPAGEOFF]
    ldr  w1, [x1]  /* hv_build_gate */
    cbz  w1, .L_irq_sve_done
    mrs  x1, s3_3_c13_c0_5
    str  x1, [sp, #0x3a8]
    mrs  x1, s3_0_c1_c2_4
    str  x1, [sp, #0x3b0]
    mrs  x1, cptr_el2
    tbz  w1, #0x18, .L_irq_sve_done
    mrs  x1, s3_3_c4_c2_2
    str  x1, [sp, #0x4138]
    tbz  w1, #0x0, .L_irq_sve_done
    add  x1, sp, #0x4, lsl #12
    ldrh w1, [x1, #0x140]                   /* Z-register count */
    mrs  x2, tpidr_el2
    ldr  x2, [x2, #0xb0]
    add  x2, x2, #0x40
    str  z0, [x2]
    str  z1, [x2, #1, mul vl]
    str  z2, [x2, #2, mul vl]
    str  z3, [x2, #3, mul vl]
    str  z4, [x2, #4, mul vl]
    str  z5, [x2, #5, mul vl]
    str  z6, [x2, #6, mul vl]
    str  z7, [x2, #7, mul vl]
    str  z8, [x2, #8, mul vl]
    str  z9, [x2, #9, mul vl]
    str  z10, [x2, #0xa, mul vl]
    str  z11, [x2, #0xb, mul vl]
    str  z12, [x2, #0xc, mul vl]
    str  z13, [x2, #0xd, mul vl]
    str  z14, [x2, #0xe, mul vl]
    str  z15, [x2, #0xf, mul vl]
    str  z16, [x2, #0x10, mul vl]
    str  z17, [x2, #0x11, mul vl]
    str  z18, [x2, #0x12, mul vl]
    str  z19, [x2, #0x13, mul vl]
    str  z20, [x2, #0x14, mul vl]
    str  z21, [x2, #0x15, mul vl]
    str  z22, [x2, #0x16, mul vl]
    str  z23, [x2, #0x17, mul vl]
    str  z24, [x2, #0x18, mul vl]
    str  z25, [x2, #0x19, mul vl]
    str  z26, [x2, #0x1a, mul vl]
    str  z27, [x2, #0x1b, mul vl]
    str  z28, [x2, #0x1c, mul vl]
    str  z29, [x2, #0x1d, mul vl]
    str  z30, [x2, #0x1e, mul vl]
    str  z31, [x2, #0x1f, mul vl]
    add  x2, x2, x1, lsl #5
    str  p0, [x2]
    str  p1, [x2, #1, mul vl]
    str  p2, [x2, #2, mul vl]
    str  p3, [x2, #3, mul vl]
    str  p4, [x2, #4, mul vl]
    str  p5, [x2, #5, mul vl]
    str  p6, [x2, #6, mul vl]
    str  p7, [x2, #7, mul vl]
    str  p8, [x2, #8, mul vl]
    str  p9, [x2, #9, mul vl]
    str  p10, [x2, #0xa, mul vl]
    str  p11, [x2, #0xb, mul vl]
    str  p12, [x2, #0xc, mul vl]
    str  p13, [x2, #0xd, mul vl]
    str  p14, [x2, #0xe, mul vl]
    str  p15, [x2, #0xf, mul vl]
    mrs  x1, fpsr
    smstop sm                               /* Ghidra: smstop {SM} */
    msr  fpsr, x1
.L_irq_sve_done:                            /* fffffe000b761170 */
    mov  x2, #0
    cmp  x25, x2
    b.eq .L_irq_fpcr_keep
    msr  fpcr, x2
.L_irq_fpcr_keep:                           /* fffffe000b761180 */
    mrs  x1, tpidr_el2
    mov  sp, x1                             /* sp = per-CPU EL2 block */
    mrs  x1, s3_4_c15_c10_6
    str  x1, [sp, #0x40]
    ldr  x1, [sp]                           /* [0] = saved CPTR_EL2 */
    msr  cptr_el2, x1
    ldr  x2, [sp, #0x58]
    msr  s3_3_c13_c0_5, x2
    ldr  x2, [sp, #0x60]
    msr  s3_0_c1_c2_4, x2
    ldr  x1, [sp, #0x78]
    msr  s3_4_c15_c12_0, x1
    ldr  x1, [sp, #0x80]
    msr  s3_6_c15_c0_4, x1
    ldr  x1, [sp, #0x88]
    msr  s3_6_c15_c0_5, x1
    ldr  x2, [sp, #0x8]                     /* [0x8] = saved MDSCR_EL1 */
    mov  x1, #0xec880000
    movk x1, #0x4040
    bic  x2, x2, x1
    msr  mdscr_el1, x2
    mov  x1, sp
    lsl  x1, x1, #4
    orr  x1, x1, #4
    pacga x1, x1, x2                        /* JOP hash: chain(mdscr) */
    ldr  x2, [sp, #0x10]
    msr  tpidr_el1, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x18]
    msr  tpidr_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x20]
    msr  tpidrro_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x21, [sp, #0x28]                   /* frame base */
    orr  x1, x1, #4
    pacga x1, x1, x21
    ldr  x2, [sp, #0x30]                    /* expected JOP hash */
    cmp  x2, x1
    b.eq .L_jop_ok_irq
    b    _hv_el2_jop_hash_panic             /* mismatch -> panic */
.L_jop_ok_irq:
    /* IRQ tail differs from sync: the EL2 stack is re-derived from the
     * authenticated thread frame rather than the saved x21. */
    mrs  x1, tpidr_el1
    ldr  x2, [x1, #0x1b8]                   /* per-CPU thread struct */
    add  x2, x2, #0x10
    ldr  x1, [x2]                           /* PAC-authenticated thread frame */
    movk x2, #0xe94d, lsl #48               /* PAC key context (0xe94d << 48) */
    autda x1, x2                            /* authenticate x1 (A-key, mod x2) */
    mov  sp, x1                             /* sp = authenticated thread frame */
    add  x2, x0, #0x4, lsl #12              /* x2 = frame + 0x4000 */
    mov  w1, #0x3                           /* exit reason = IRQ (3) */
    str  w1, [x2, #0x8]                     /* frame+0x4008 = 3 */
    adr  x1, .L_irq_target             /* EL1 return target b75df48 (EL1 irq handler entry) */
    b    _hv_el2_common_dispatch

/* =====================================================================
 * hv_el2_vector_fiq — FUN_fffffe000b761260 (body b761260..b7615bb).
 * Guest FIQ entry. Exit reason HV_EL2_EXIT_REASON_FIQ (4); return target
 * b75dfcc (EL1 fiq handler entry). Same tail as irq.
 * ===================================================================== */
    .p2align 4
    .global _hv_el2_vector_fiq
_hv_el2_vector_fiq:                         /* fffffe000b761260 */
    msr  pan, #1
    mrs  x1, tpidr_el2
    ldr  x1, [x1, #0x90]
    mrs  x0, sp_el0
    str  x0, [x1, #0x370]
    mrs  x0, sp_el1
    str  x0, [x1, #0x378]
    msr  sp_el0, x1
    ldp  x0, x1, [sp], #0x10
    msr  spsel, #0
    stp  x0, x1, [sp, #0x8]
    mov  x0, #0
    msr  s3_5_c15_c1_3, x0
    mrs  x0, s3_4_c12_c11_0
    and  x0, x0, #-2
    msr  s3_4_c12_c11_0, x0
    mrs  x0, mdscr_el1
    str  x0, [sp, #0x350]
    mrs  x0, tpidr_el1
    str  x0, [sp, #0x358]
    mrs  x0, tpidr_el0
    str  x0, [sp, #0x360]
    mrs  x0, tpidrro_el0
    str  x0, [sp, #0x368]
    mrs  x0, par_el1
    str  x0, [sp, #0x380]
    mrs  x0, csselr_el1
    str  x0, [sp, #0x388]
    mrs  x0, s3_6_c15_c8_3
    str  x0, [sp, #0x390]
    mrs  x0, s3_6_c15_c2_5
    str  x0, [sp, #0x398]
    mrs  x0, s3_4_c15_c12_0
    str  x0, [sp, #0x9f0]
    adrp x0, _hv_el2_capable@GOTPAGE
    ldr  x0, [x0, _hv_el2_capable@GOTPAGEOFF]
    ldrb w0, [x0]
    cbz  x0, .L_fiq_sysreg
    mrs  x0, s3_3_c13_c0_7
    str  x0, [sp, #0x3a0]
.L_fiq_sysreg:                              /* fffffe000b7612fc */
    mov  x0, sp
    stp  x2, x3, [x0, #0x18]
    stp  x4, x5, [x0, #0x28]
    stp  x6, x7, [x0, #0x38]
    stp  x8, x9, [x0, #0x48]
    stp  x10, x11, [x0, #0x58]
    stp  x12, x13, [x0, #0x68]
    stp  x14, x15, [x0, #0x78]
    stp  x16, x17, [x0, #0x88]
    stp  x18, x19, [x0, #0x98]
    stp  x20, x21, [x0, #0xa8]
    stp  x22, x23, [x0, #0xb8]
    stp  x24, x25, [x0, #0xc8]
    stp  x26, x27, [x0, #0xd8]
    stp  x28, x29, [x0, #0xe8]
    str  x30, [x0, #0xf8]
    mov  x25, #0
    mrs  x1, cptr_el2
    tbz  w1, #0x14, .L_fiq_fp_saved
    stp  q0, q1, [x0, #0x140]
    stp  q2, q3, [x0, #0x160]
    stp  q4, q5, [x0, #0x180]
    stp  q6, q7, [x0, #0x1a0]
    stp  q8, q9, [x0, #0x1c0]
    stp  q10, q11, [x0, #0x1e0]
    stp  q12, q13, [x0, #0x200]
    stp  q14, q15, [x0, #0x220]
    stp  q16, q17, [x0, #0x240]
    stp  q18, q19, [x0, #0x260]
    stp  q20, q21, [x0, #0x280]
    stp  q22, q23, [x0, #0x2a0]
    stp  q24, q25, [x0, #0x2c0]
    stp  q26, q27, [x0, #0x2e0]
    stp  q28, q29, [x0, #0x300]
    stp  q30, q31, [x0, #0x320]
    mrs  x24, fpsr
    str  w24, [x0, #0x340]
    mrs  x25, fpcr
    str  w25, [x0, #0x344]
.L_fiq_fp_saved:                            /* fffffe000b761398 */
    mrs  x22, elr_el1
    mrs  x23, spsr_el1
    mrs  x20, far_el1
    mrs  x21, esr_el1
    str  x20, [x0, #0x118]
    str  x22, [x0, #0x108]
    str  x21, [x0, #0x120]
    str  w23, [x0, #0x110]
    adrp x1, _hv_build_gate@GOTPAGE
    ldr  x1, [x1, _hv_build_gate@GOTPAGEOFF]
    ldr  w1, [x1]
    cbz  w1, .L_fiq_sve_done
    mrs  x1, s3_3_c13_c0_5
    str  x1, [sp, #0x3a8]
    mrs  x1, s3_0_c1_c2_4
    str  x1, [sp, #0x3b0]
    mrs  x1, cptr_el2
    tbz  w1, #0x18, .L_fiq_sve_done
    mrs  x1, s3_3_c4_c2_2
    str  x1, [sp, #0x4138]
    tbz  w1, #0x0, .L_fiq_sve_done
    add  x1, sp, #0x4, lsl #12
    ldrh w1, [x1, #0x140]
    mrs  x2, tpidr_el2
    ldr  x2, [x2, #0xb0]
    add  x2, x2, #0x40
    str  z0, [x2]
    str  z1, [x2, #1, mul vl]
    str  z2, [x2, #2, mul vl]
    str  z3, [x2, #3, mul vl]
    str  z4, [x2, #4, mul vl]
    str  z5, [x2, #5, mul vl]
    str  z6, [x2, #6, mul vl]
    str  z7, [x2, #7, mul vl]
    str  z8, [x2, #8, mul vl]
    str  z9, [x2, #9, mul vl]
    str  z10, [x2, #0xa, mul vl]
    str  z11, [x2, #0xb, mul vl]
    str  z12, [x2, #0xc, mul vl]
    str  z13, [x2, #0xd, mul vl]
    str  z14, [x2, #0xe, mul vl]
    str  z15, [x2, #0xf, mul vl]
    str  z16, [x2, #0x10, mul vl]
    str  z17, [x2, #0x11, mul vl]
    str  z18, [x2, #0x12, mul vl]
    str  z19, [x2, #0x13, mul vl]
    str  z20, [x2, #0x14, mul vl]
    str  z21, [x2, #0x15, mul vl]
    str  z22, [x2, #0x16, mul vl]
    str  z23, [x2, #0x17, mul vl]
    str  z24, [x2, #0x18, mul vl]
    str  z25, [x2, #0x19, mul vl]
    str  z26, [x2, #0x1a, mul vl]
    str  z27, [x2, #0x1b, mul vl]
    str  z28, [x2, #0x1c, mul vl]
    str  z29, [x2, #0x1d, mul vl]
    str  z30, [x2, #0x1e, mul vl]
    str  z31, [x2, #0x1f, mul vl]
    add  x2, x2, x1, lsl #5
    str  p0, [x2]
    str  p1, [x2, #1, mul vl]
    str  p2, [x2, #2, mul vl]
    str  p3, [x2, #3, mul vl]
    str  p4, [x2, #4, mul vl]
    str  p5, [x2, #5, mul vl]
    str  p6, [x2, #6, mul vl]
    str  p7, [x2, #7, mul vl]
    str  p8, [x2, #8, mul vl]
    str  p9, [x2, #9, mul vl]
    str  p10, [x2, #0xa, mul vl]
    str  p11, [x2, #0xb, mul vl]
    str  p12, [x2, #0xc, mul vl]
    str  p13, [x2, #0xd, mul vl]
    str  p14, [x2, #0xe, mul vl]
    str  p15, [x2, #0xf, mul vl]
    mrs  x1, fpsr
    smstop sm                               /* Ghidra: smstop {SM} */
    msr  fpsr, x1
.L_fiq_sve_done:                            /* fffffe000b7614cc */
    mov  x2, #0
    cmp  x25, x2
    b.eq .L_fiq_fpcr_keep
    msr  fpcr, x2
.L_fiq_fpcr_keep:                           /* fffffe000b7614dc */
    mrs  x1, tpidr_el2
    mov  sp, x1
    mrs  x1, s3_4_c15_c10_6
    str  x1, [sp, #0x40]
    ldr  x1, [sp]
    msr  cptr_el2, x1
    ldr  x2, [sp, #0x58]
    msr  s3_3_c13_c0_5, x2
    ldr  x2, [sp, #0x60]
    msr  s3_0_c1_c2_4, x2
    ldr  x1, [sp, #0x78]
    msr  s3_4_c15_c12_0, x1
    ldr  x1, [sp, #0x80]
    msr  s3_6_c15_c0_4, x1
    ldr  x1, [sp, #0x88]
    msr  s3_6_c15_c0_5, x1
    ldr  x2, [sp, #0x8]
    mov  x1, #0xec880000
    movk x1, #0x4040
    bic  x2, x2, x1
    msr  mdscr_el1, x2
    mov  x1, sp
    lsl  x1, x1, #4
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x10]
    msr  tpidr_el1, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x18]
    msr  tpidr_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x20]
    msr  tpidrro_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x21, [sp, #0x28]
    orr  x1, x1, #4
    pacga x1, x1, x21
    ldr  x2, [sp, #0x30]
    cmp  x2, x1
    b.eq .L_jop_ok_fiq
    b    _hv_el2_jop_hash_panic
.L_jop_ok_fiq:
    mrs  x1, tpidr_el1
    ldr  x2, [x1, #0x1b8]
    add  x2, x2, #0x10
    ldr  x1, [x2]
    movk x2, #0xe94d, lsl #48
    autda x1, x2
    mov  sp, x1
    add  x2, x0, #0x4, lsl #12
    mov  w1, #0x4                           /* exit reason = FIQ (4) */
    str  w1, [x2, #0x8]                     /* frame+0x4008 = 4 */
    adr  x1, .L_fiq_target             /* EL1 return target b75dfcc (EL1 fiq handler entry) */
    b    _hv_el2_common_dispatch

/* =====================================================================
 * hv_el2_vector_error — FUN_fffffe000b7615bc (body b7615bc..b7618ff).
 * Guest SError/async exception entry. Exit reason
 * HV_EL2_EXIT_REASON_ERROR (2); return target b75e04c (EL1 error entry).
 * Same save sequence as sync; tail restores sp from x21 like sync.
 * ===================================================================== */
    .p2align 4
    .global _hv_el2_vector_error
_hv_el2_vector_error:                       /* fffffe000b7615bc */
    msr  pan, #1
    mrs  x1, tpidr_el2
    ldr  x1, [x1, #0x90]
    mrs  x0, sp_el0
    str  x0, [x1, #0x370]
    mrs  x0, sp_el1
    str  x0, [x1, #0x378]
    msr  sp_el0, x1
    ldp  x0, x1, [sp], #0x10
    msr  spsel, #0
    stp  x0, x1, [sp, #0x8]
    mov  x0, #0
    msr  s3_5_c15_c1_3, x0
    mrs  x0, s3_4_c12_c11_0
    and  x0, x0, #-2
    msr  s3_4_c12_c11_0, x0
    mrs  x0, mdscr_el1
    str  x0, [sp, #0x350]
    mrs  x0, tpidr_el1
    str  x0, [sp, #0x358]
    mrs  x0, tpidr_el0
    str  x0, [sp, #0x360]
    mrs  x0, tpidrro_el0
    str  x0, [sp, #0x368]
    mrs  x0, par_el1
    str  x0, [sp, #0x380]
    mrs  x0, csselr_el1
    str  x0, [sp, #0x388]
    mrs  x0, s3_6_c15_c8_3
    str  x0, [sp, #0x390]
    mrs  x0, s3_6_c15_c2_5
    str  x0, [sp, #0x398]
    mrs  x0, s3_4_c15_c12_0
    str  x0, [sp, #0x9f0]
    adrp x0, _hv_el2_capable@GOTPAGE
    ldr  x0, [x0, _hv_el2_capable@GOTPAGEOFF]
    ldrb w0, [x0]
    cbz  x0, .L_err_sysreg
    mrs  x0, s3_3_c13_c0_7
    str  x0, [sp, #0x3a0]
.L_err_sysreg:                              /* fffffe000b761658 */
    mov  x0, sp
    stp  x2, x3, [x0, #0x18]
    stp  x4, x5, [x0, #0x28]
    stp  x6, x7, [x0, #0x38]
    stp  x8, x9, [x0, #0x48]
    stp  x10, x11, [x0, #0x58]
    stp  x12, x13, [x0, #0x68]
    stp  x14, x15, [x0, #0x78]
    stp  x16, x17, [x0, #0x88]
    stp  x18, x19, [x0, #0x98]
    stp  x20, x21, [x0, #0xa8]
    stp  x22, x23, [x0, #0xb8]
    stp  x24, x25, [x0, #0xc8]
    stp  x26, x27, [x0, #0xd8]
    stp  x28, x29, [x0, #0xe8]
    str  x30, [x0, #0xf8]
    mov  x25, #0
    mrs  x1, cptr_el2
    tbz  w1, #0x14, .L_err_fp_saved
    stp  q0, q1, [x0, #0x140]
    stp  q2, q3, [x0, #0x160]
    stp  q4, q5, [x0, #0x180]
    stp  q6, q7, [x0, #0x1a0]
    stp  q8, q9, [x0, #0x1c0]
    stp  q10, q11, [x0, #0x1e0]
    stp  q12, q13, [x0, #0x200]
    stp  q14, q15, [x0, #0x220]
    stp  q16, q17, [x0, #0x240]
    stp  q18, q19, [x0, #0x260]
    stp  q20, q21, [x0, #0x280]
    stp  q22, q23, [x0, #0x2a0]
    stp  q24, q25, [x0, #0x2c0]
    stp  q26, q27, [x0, #0x2e0]
    stp  q28, q29, [x0, #0x300]
    stp  q30, q31, [x0, #0x320]
    mrs  x24, fpsr
    str  w24, [x0, #0x340]
    mrs  x25, fpcr
    str  w25, [x0, #0x344]
.L_err_fp_saved:                            /* fffffe000b7616f4 */
    mrs  x22, elr_el1
    mrs  x23, spsr_el1
    mrs  x20, far_el1
    mrs  x21, esr_el1
    str  x20, [x0, #0x118]
    str  x22, [x0, #0x108]
    str  x21, [x0, #0x120]
    str  w23, [x0, #0x110]
    adrp x1, _hv_build_gate@GOTPAGE
    ldr  x1, [x1, _hv_build_gate@GOTPAGEOFF]
    ldr  w1, [x1]
    cbz  w1, .L_err_sve_done
    mrs  x1, s3_3_c13_c0_5
    str  x1, [sp, #0x3a8]
    mrs  x1, s3_0_c1_c2_4
    str  x1, [sp, #0x3b0]
    mrs  x1, cptr_el2
    tbz  w1, #0x18, .L_err_sve_done
    mrs  x1, s3_3_c4_c2_2
    str  x1, [sp, #0x4138]
    tbz  w1, #0x0, .L_err_sve_done
    add  x1, sp, #0x4, lsl #12
    ldrh w1, [x1, #0x140]
    mrs  x2, tpidr_el2
    ldr  x2, [x2, #0xb0]
    add  x2, x2, #0x40
    str  z0, [x2]
    str  z1, [x2, #1, mul vl]
    str  z2, [x2, #2, mul vl]
    str  z3, [x2, #3, mul vl]
    str  z4, [x2, #4, mul vl]
    str  z5, [x2, #5, mul vl]
    str  z6, [x2, #6, mul vl]
    str  z7, [x2, #7, mul vl]
    str  z8, [x2, #8, mul vl]
    str  z9, [x2, #9, mul vl]
    str  z10, [x2, #0xa, mul vl]
    str  z11, [x2, #0xb, mul vl]
    str  z12, [x2, #0xc, mul vl]
    str  z13, [x2, #0xd, mul vl]
    str  z14, [x2, #0xe, mul vl]
    str  z15, [x2, #0xf, mul vl]
    str  z16, [x2, #0x10, mul vl]
    str  z17, [x2, #0x11, mul vl]
    str  z18, [x2, #0x12, mul vl]
    str  z19, [x2, #0x13, mul vl]
    str  z20, [x2, #0x14, mul vl]
    str  z21, [x2, #0x15, mul vl]
    str  z22, [x2, #0x16, mul vl]
    str  z23, [x2, #0x17, mul vl]
    str  z24, [x2, #0x18, mul vl]
    str  z25, [x2, #0x19, mul vl]
    str  z26, [x2, #0x1a, mul vl]
    str  z27, [x2, #0x1b, mul vl]
    str  z28, [x2, #0x1c, mul vl]
    str  z29, [x2, #0x1d, mul vl]
    str  z30, [x2, #0x1e, mul vl]
    str  z31, [x2, #0x1f, mul vl]
    add  x2, x2, x1, lsl #5
    str  p0, [x2]
    str  p1, [x2, #1, mul vl]
    str  p2, [x2, #2, mul vl]
    str  p3, [x2, #3, mul vl]
    str  p4, [x2, #4, mul vl]
    str  p5, [x2, #5, mul vl]
    str  p6, [x2, #6, mul vl]
    str  p7, [x2, #7, mul vl]
    str  p8, [x2, #8, mul vl]
    str  p9, [x2, #9, mul vl]
    str  p10, [x2, #0xa, mul vl]
    str  p11, [x2, #0xb, mul vl]
    str  p12, [x2, #0xc, mul vl]
    str  p13, [x2, #0xd, mul vl]
    str  p14, [x2, #0xe, mul vl]
    str  p15, [x2, #0xf, mul vl]
    mrs  x1, fpsr
    smstop sm                               /* Ghidra: smstop {SM} */
    msr  fpsr, x1
.L_err_sve_done:                            /* fffffe000b761828 */
    mov  x2, #0
    cmp  x25, x2
    b.eq .L_err_fpcr_keep
    msr  fpcr, x2
.L_err_fpcr_keep:                           /* fffffe000b761838 */
    mrs  x1, tpidr_el2
    mov  sp, x1
    mrs  x1, s3_4_c15_c10_6
    str  x1, [sp, #0x40]
    ldr  x1, [sp]
    msr  cptr_el2, x1
    ldr  x2, [sp, #0x58]
    msr  s3_3_c13_c0_5, x2
    ldr  x2, [sp, #0x60]
    msr  s3_0_c1_c2_4, x2
    ldr  x1, [sp, #0x78]
    msr  s3_4_c15_c12_0, x1
    ldr  x1, [sp, #0x80]
    msr  s3_6_c15_c0_4, x1
    ldr  x1, [sp, #0x88]
    msr  s3_6_c15_c0_5, x1
    ldr  x2, [sp, #0x8]
    mov  x1, #0xec880000
    movk x1, #0x4040
    bic  x2, x2, x1
    msr  mdscr_el1, x2
    mov  x1, sp
    lsl  x1, x1, #4
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x10]
    msr  tpidr_el1, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x18]
    msr  tpidr_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x2, [sp, #0x20]
    msr  tpidrro_el0, x2
    orr  x1, x1, #4
    pacga x1, x1, x2
    ldr  x21, [sp, #0x28]
    orr  x1, x1, #4
    pacga x1, x1, x21
    ldr  x2, [sp, #0x30]
    cmp  x2, x1
    b.eq .L_jop_ok_err
    b    _hv_el2_jop_hash_panic
.L_jop_ok_err:
    mov  sp, x21                            /* sp = guest-state frame base */
    add  x2, x0, #0x4, lsl #12
    mov  w1, #0x2                           /* exit reason = ERROR (2) */
    str  w1, [x2, #0x8]                     /* frame+0x4008 = 2 */
    adr  x1, .L_err_target             /* EL1 return target b75e04c (EL1 error handler entry) */
    b    _hv_el2_common_dispatch

/* ---- documented EL1 return targets (see header notes) ----
 * The adrp+add above resolve to these absolute addresses in the binary:
 *   sync  -> fffffe000b760eec (FUN_fffffe000b760eec: classify ESR + return)
 *   irq   -> fffffe000b75df48 (EL1 irq handler entry)
 *   fiq   -> fffffe000b75dfcc (EL1 fiq handler entry)
 *   error -> fffffe000b75e04c (EL1 error handler entry)                    */
    .p2align 4
.L_sync_target:
    nop
.L_irq_target:
    nop
.L_fiq_target:
    nop
.L_err_target:
    nop

/* Common dispatch and panic helper are C symbols (hv_el2.c): extern refs. */
    .global _hv_el2_common_dispatch
    .global _kernel_panic_msg_fmt

/* ---- documented data globals referenced by the vectors ----
 * The adrp+ldr above resolve to these absolute addresses in the binary:
 *   hv_el2_capable -> DAT_fffffe0007e0d81e (EL2 feature flag, bit 0)
 *   hv_build_gate  -> DAT_fffffe0007e0da68 (EL2 build gate, ==0 at runtime) */
    .data
    .p2align 3
    .global _hv_el2_capable
_hv_el2_capable:
    .byte 0
    .p2align 3
    .global _hv_build_gate
_hv_build_gate:
    .word 0

