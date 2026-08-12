/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_el2.c — EL2 exception vector handlers and the guest->EL2 exit path.
 *
 * Owned by the el2-vectors tree. This is the highest-value hypervisor tree:
 * the exception path a guest takes into the hypervisor. The EL2 vector
 * handlers at b760b10 (sync) / b760f04 (irq) / b761260 (fiq) / b7615bc
 * (error) are entered from VBAR_EL2 when the guest (at EL1/EL0) traps. Each
 * saves the guest's EL1 register state into the per-CPU guest-state frame,
 * switches EL2 control state, verifies the PAC "JOP hash" of the saved
 * sysregs, writes an exit-reason word, and branches to the common dispatch
 * hv_el2_common_dispatch which erets down to the EL1 kernel exception handler
 * (b75deac family). From there the guest exit is classified (b96743c),
 * faults handled (b967768), and the guest is resumed via
 * hv_el2_return_to_guest / b75e5cc (eret).
 *
 * NOTE on the vector table base: the four handlers are large (they each
 * inline the full guest-state save), so they are the handler bodies the
 * 0x80-byte vector slots branch to, not the slots themselves. The EL1 kernel
 * vector table (VBAR_EL1) is 0xfffffe000b75c000 (set by kernel_entry); the
 * EL2 table is a separate 0x800-aligned table whose sync/irq/fiq/error
 * entries resolve to the four handlers below. The exact VBAR_EL2 base was not
 * pinned (no `msr vbar_el2` write site was found in the hv cluster or boot
 * path — it is established during EL2 bring-up outside the recreated code);
 * the handler addresses are ground truth.
 *
 * Offsets are relative to the guest-state block base (see hv_el2.h).
 * EL2 sysreg reads/writes stay literal (UnkSytemRegRead/Write) per the
 * contract; op1=4 encodes EL2, but register identity is unverified.
 */

#include "hv_el2.h"

/*
 * hv_el2_guest_exc_check @ 0xfffffe000b9679c8   (est. hv_el2_guest_exc_check)
 * Ghidra: bool hv_el2_guest_exc_check(ulong param_1,long param_2,ulong param_3,ulong param_4)
 * Pre-dispatch check for a guest synchronous exception. param_1 = ESR,
 * param_2 = ELR, param_3 = FAR, param_4 = SPSR. Walks the dtrace valid-
 * address table (DAT_fffffe0007045690) to decide whether the faulting PC is
 * dtrace-managed (returns true so the caller takes the dtrace path), handles
 * the SVC-ISS 0x11 case, and otherwise returns whether the exception is
 * guest-visible ((SPSR & 0x1c0) != 0 && DAT_fffffe0007e9d348 == -1). Kernel
 * dtrace table referenced; reconstructed as structural notes (low confidence
 * on the dtrace-address semantics). Shared kernel, stub body.
 * Confidence: low
 */

/*
 * hv_el2_eret_fast @ 0xfffffe000b75e5cc   (est. hv_el2_eret_fast)
 * Ghidra: undefined1 [16] hv_el2_eret_fast(void)
 * Fast-path return-to-guest tail: the same register restore + SVE Z/P reload
 * + ExceptionReturn() as hv_el2_return_to_guest, but reached directly when the
 * preemption re-check is bypassed (bit7 of the exit word set). Restores
 * elr_el1/spsr_el1/fpcr/fpsr from the saved frame (HV_EL2_FRAME_* offsets),
 * reloads SVE state when the guest is in SVE mode (type 0x31 object at
 * tpidr+0x120), re-arms the PAC key (3,0,1,0,5) and T1SZ
 * (3,0,1,0,6,0x10001), then ExceptionReturn(). Confidence: medium.
 */

/*
 * hv_el2_exception_exit @ 0xfffffe000b75e420   (est. hv_el2_exception_exit)
 * Ghidra: undefined1 [16] hv_el2_exception_exit(void)
 * Exception-exit tail shared by the EL1 kernel exception handlers
 * (b75deac/b75df7c/b75e000/b75e058): restores the saved guest state
 * (elr_el1/spsr_el1/fpcr/fpsr, SVE Z/P regs) and erets back to the guest,
 * guarded by the "Signed thread state manipulated with interrupts enabled"
 * JOP-hash verify (FUN_fffffe000b760444). Confidence: medium.
 */

/*
 * hv_el2_preemption_panic @ 0xfffffe000b75e8a8   (est. hv_el2_preemption_panic)
 * Ghidra: void hv_el2_preemption_panic(void)
 * noreturn panic "Preemption count negative on thread %p" via
 * kernel_panic_msg_fmt, reached when the per-CPU preemption counter
 * (tpidr+0x1c0) is found negative on the exception-exit path. Confidence:
 * high (message + noreturn observed).
 */

/* ---- guest ESR classifier / sync dispatch ----------------------------- */

/*
 * hv_el2_guest_esr_classify @ 0xfffffe000b96743c   (est. hv_el2_guest_esr_classify)
 * Ghidra: void hv_el2_guest_esr_classify(int *param_1, ulong param_2, undefined8 param_3)
 * Classifies a guest synchronous exception. param_1 = guest-state block
 * (field 0 == 0x14 marks a compact frame, else a full frame), param_2 = ESR_EL1,
 * param_3 = FAR_EL1. Writes the exit code to state+0x4008 (word at
 * param_1+0x1002) and, for SVC, the ISS to state+0x4018. Decodes ESR EC
 * (bits [31:26]): SVC(0x18)->8, 0x1d->0xd, IABT(0x20)->fault reason 5,
 * DABT(0x24)->fault reason 1/3, SMC-ish(0x3f)->0x80000000/7/8/1 by ISS,
 * default->checks the guest pstate for a host abort (bit3) and panics
 * "Unexpected host abort from guest context", or (EC>0x34 / unmapped)
 * panics "Unrecognized guest trap exception, state=%p, esr=%#llx @%s:%d".
 * Counter globals at per-CPU tpidr+0x8d8 (DABT) / +0x8e0 (IABT) are bumped.
 * Confidence: high (two hv_vcpu.c panic strings + ESR-EC dispatch)
 * Notes: 0x4008 exit word == es+0x4008 read by the hv_vcpu_run hub (b989a44).
 *   UnkSytemRegRead(3,0,1,0,0) is afsr1_el1 for the SMC/0x3f ISS==0x20 case.
 *   The exit-code values (8,0xd,5,1,3,7,0x80000000,10) are exit enumerations
 *   used by hv_vcpu_run's dispatch, not ESR values.
 */
void hv_el2_guest_esr_classify(void *state, uint64_t esr, uint64_t far)
{
    uint32_t ec = (uint32_t)((esr >> HV_EL2_EC_SHIFT) & HV_EL2_EC_MASK);
    uint64_t iss, afsr;
    uint32_t exit;
    uint32_t *st32 = state;

    if (hv_trace_flag & 1) {
        /* kernel_trace(0x1030801 | (ec<<2), esr, far, pc, 0) — enter trace */
        uint64_t pc = (st32[0] == 0x14) ? (uint32_t)st32[0x11]
                                        : *(uint64_t *)(state + 0x210);
        kernel_trace((ec << 2) | 0x1030801, esr, far, pc, 0);
    }
    st32[0x100a] = 0;
    st32[0x100b] = 0;
    *(uint64_t *)(state + 0x1004 * 4 + 0) = esr & 0xffffffff;   /* +0x4010 */
    st32[0x1006] = 0;
    st32[0x1007] = 0;

    /* If EC is one of the "handled by this classifier" classes, set a flag. */
    uint64_t handled = 0;
    if (ec <= 0x34 && ((1ULL << ec) & 0x10001100000000ULL) != 0) {
        handled = far;   /* param_3 propagated; see below */
    }
    *(uint64_t *)(state + 0x1008 * 4) = handled;   /* +0x4020 */

    if (ec < 0x20) {
        if (ec == 0x18) {                 /* SVC */
            iss = esr & 0x1ffffff;
            *(uint64_t *)(state + 0x1006 * 4) = iss;   /* +0x4018 */
            exit = 8;
            st32[0x1002] = exit;          /* +0x4008 */
        } else if (ec == 0x1d) {
            st32[0x1002] = 0xd;           /* +0x4008 */
        } else {
            /* default: examine guest pstate for a host abort / high-prio exit */
            size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
            uint32_t p = *(uint32_t *)(state + pst);
            if ((p & 0x100000) == 0) {     /* bit20 clear */
                if ((p & 0x8) != 0) {
                    kernel_panic_msg();    /* "Unexpected host abort ..." */
                }
                /* else: no exit written; fall through to trace */
            } else {
                st32[0x1002] = 10;         /* +0x4008 */
            }
        }
    } else if (ec == 0x20) {              /* IABT */
        /* tpidr_el1 per-CPU: bump tpidr+0x8e0 instruction-abort counter */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        *(uint64_t *)(*(uint64_t *)(pcpu + 0x1b8) + 0x8e0) += 1;
        hv_el2_guest_fault(state, esr, far, (uint32_t)(esr & 0x3f), 5);
    } else if (ec == 0x3f) {              /* SMC-ish */
        if ((esr & 0x1ffffff) == 3) {
            iss = esr & 0x1ffffff;
            if (iss < 0x22) {
                if (iss == 3) {
                    st32[0x1002] = (uint32_t)-0x80000000;
                } else if (iss == 0x20) {
                    afsr = UnkSytemRegRead(3,0,1,0,0) & 0xffffffff; /* afsr1_el1 */
                    *(uint64_t *)(state + 0x1006 * 4) = afsr;       /* +0x4018 */
                    st32[0x1002] = 8;
                } else if (iss == 0x21) {
                    st32[0x1002] = 7;
                } else {
                    kernel_panic_assert();  /* "Unrecognized guest trap ..." */
                }
            } else {
                if ((iss - 0x22 > 1) && (iss != 0x26)) {
                    kernel_panic_assert();
                }
                st32[0x1002] = 1;
            }
        }
        if ((esr & 0x1fffff0) == 0x20) {
            iss = esr & 0x1ffffff;
            if (iss < 0x22) {
                if (iss == 3) {
                    st32[0x1002] = (uint32_t)-0x80000000;
                } else if (iss == 0x20) {
                    afsr = UnkSytemRegRead(3,0,1,0,0) & 0xffffffff;
                    *(uint64_t *)(state + 0x1006 * 4) = afsr;
                    exit = 8;
                    st32[0x1002] = exit;
                } else if (iss == 0x21) {
                    st32[0x1002] = 7;
                } else {
                    kernel_panic_assert();
                }
            } else {
                if ((iss - 0x22 > 1) && (iss != 0x26)) {
                    kernel_panic_assert();
                }
                st32[0x1002] = 1;
            }
        }
    } else if (ec == 0x24) {              /* DABT */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        *(uint64_t *)(*(uint64_t *)(pcpu + 0x1b8) + 0x8d8) += 1;
        uint32_t r;
        /* reason/which: reason = ISS (esr&0x3f), which = 1 (read) / 3 (write).
         * which==1 when WnR clear, or S1PTW set and the 32-bit
         * (esr&0x3f)-0x10 does not wrap below 0xfffffffd (i.e. ISS >= 0x10). */
        if (((esr >> 6) & 1) == 0 ||
            (((esr >> 8) & 1) != 0 && (esr & 0x3f) - 0x10 < 0xfffffffd)) {
            r = 1;
        } else {
            r = 3;
        }
        hv_el2_guest_fault(state, esr, far, (uint32_t)(esr & 0x3f), r);
    } else {
        /* default: examine guest pstate (same as ec<0x20 default) */
        size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
        uint32_t p = *(uint32_t *)(state + pst);
        if ((p & 0x100000) == 0) {         /* bit20 clear */
            if ((p & 0x8) != 0) {
                kernel_panic_msg();        /* "Unexpected host abort ..." */
            }
        } else {
            st32[0x1002] = 10;             /* +0x4008 */
        }
    }

    if (hv_trace_flag & 1) {
        uint64_t pc = (st32[0] == 0x14) ? (uint32_t)st32[0x11]
                                        : *(uint64_t *)(state + 0x210);
        kernel_trace(((ec << 2) | 0x1030801) + 1, esr, far, pc, 0);
    }
}

/*
 * hv_el2_guest_fault @ 0xfffffe000b967768   (est. hv_el2_guest_fault)
 * Ghidra: void hv_el2_guest_fault(long param_1, ulong param_2, ulong param_3,
 *                                    uint param_4, undefined4 param_5)
 * Handles a guest data/instruction abort from the ESR classifier. param_1 =
 * guest-state block, param_2 = ESR, param_3 = FAR, param_4 = sub-reason
 * (0x18 -> SVC, 0xd..0xf -> "within guest", 0x20 -> IABT, 0x24 -> DABT),
 * param_5 = which (read/write). For SVC (param_4==0x18) it forwards to
 * hw_error_report. For aborts it resolves the guest physical address:
 * when inside the guest and the EA bit is clear, the FAR is used directly;
 * otherwise the IPA is synthesised from HPFAR_EL2 (guest IPA = FAR[11:0] |
 * (HPFAR[31:4]<<12)). Then validates/maps it via the EL2 guest page-table
 * (hv_el2_guest_pte_check / b89988c) with the vm_fault path; on a
 * not-EL2-mapped-but-in-guest-IPA-range failure it retries via
 * hv_el2_guest_fault_retry. Writes the fault exit code to state+0x4008.
 * Confidence: medium (fault-table + HPFAR synthesis observed)
 * Notes: UnkSytemRegRead(3,5,1,0,0) is HPFAR_EL2. vm_fault strings
 *   "vm_fault() KERN_FAILURE from guest fault on state %p @%s:%d" and the
 *   kernel wrappers b94b450/b89988c/b9879b8 are shared kernel, stubbed.
 */
void hv_el2_guest_fault(void *state, uint64_t esr, uint64_t far,
                        uint32_t reason, uint32_t which)
{
    uint32_t r;
    uint64_t ipa, hpfar;

    if (reason > 0x1f) {
        return;
    }
    uint32_t mask = 1u << (reason & 0x1f);

    if ((mask & 0xeef0) == 0) {
        if ((mask & 0xe2000000) == 0) {
            if (reason != 0x18) {
                return;
            }
            /* reason 0x18: guest SError/async — forward to the hardware
             * error handler (PL2/LLC multi-hit reporting). Kernel, stubbed. */
            hw_error_report(state, far, 1, esr);
        }
    } else {
        /* abort path */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        void *vm = *(void **)(*(uint64_t *)(pcpu + 0x4d8) + 0x88);
        if ((((esr >> 7) & 1) == 0) && (reason - 0xd < 3)) {
            /* EA clear, inside guest: use FAR directly */
            if (UnkSytemRegRead(3,5,1,0,0) & 1) {   /* bit0 of HPFAR_EL2 */
                far = kernel_boot_misc_q(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(pcpu+0x4d8)+0x88)+0x58)+8), far);
            }
            *(uint64_t *)(state + 0x4028) = far;
            if (far == 0xffffffffffffffffULL) goto done;
        } else {
            hpfar = UnkSytemRegRead(3,5,1,0,0);        /* HPFAR_EL2 */
            ipa = (far & 0xfff) | ((hpfar >> 4) & 0xfffffffff) << 12;
            *(uint64_t *)(state + 0x4028) = ipa;
        }
        debug_exceptions_disable(1);   /* disable debug exceptions (kernel) */
        if ((esr & 0x80) != 0) {
            which = 1;
        }
        /* validate + vm_fault the IPA in the guest vm */
        if ((((reason & 0x3c) == 4) ||
             (far < *(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x10)) ||
             (*(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x18) <= far)) ||
            hv_el2_guest_pte_check((uint64_t *)(*(uint64_t *)(vm + 0x58)),
                                   far, which, reason == 0xb) != 0) {
            if ((far < *(uint64_t *)(vm + 0x28)) ||
                (*(uint64_t *)(vm + 0x30) <= far)) {
                r = 6;
            } else {
                uint64_t faultarg[5] = {2,0,0,0,0};
                int i = (int)kernel_vm_fault(vm, far, which, 0, 0, 0, 0,
                                             (uint16_t *)faultarg, 0);
                if (i != 0) {
                    if (((reason & 0x3c) != 4) ||
                        hv_el2_guest_fault_retry(vm, far, (uint32_t)esr,
                                                 state) == 0) {
                        if (i == 5) {
                            kernel_panic_assert();
                        }
                        if (i == 0xe) {
                            r = 9;
                        } else {
                            r = 6;
                        }
                    } else {
                        /* retried fault resolved: advance guest PC */
                        *(uint64_t *)(state + 0x108) += 4;
                        r = 5;
                    }
                } else {
                    r = 5;
                }
            }
        } else {
            r = 5;
        }
    }
done:
    r = 5;
    *(uint32_t *)(state + 0x4008) = r;
}

/* ---- guest-fault vm_fault family (recreated per FULL-AUDIT) ----------- */

/*
 * hv_el2_guest_pte_check @ 0xfffffe000b94b450   (est. hv_el2_guest_pte_check)
 * Ghidra: int hv_el2_guest_pte_check(long *param_1, ulong param_2, uint param_3,
 *                                  int param_4)
 * Stage-2 guest-page-table walk and attribute check, the first thing
 * hv_el2_guest_fault runs on a guest IPA. Walks the per-owner EL2 translation
 * table (level descriptors anchored at pmap[4], table base pmap[0]) to test
 * whether the faulting IPA has a present, correctly-attribute'd leaf entry.
 * On success returns 0 (the fault is a genuine stage-2 miss -> caller runs
 * vm_fault); returns 5 (not present / bad descriptor) or 2 (present but
 * wrong memory attributes / permission) to take the fault path. Includes the
 * per-CPU "pending sync" preemption counter (tpidr+0x1c0) protection and the
 * compressed-PTE integrity checks ("compressed PTE %p 0x%llx has extra bits
 * 0x%llx: corrupted?").
 * Confidence: medium (walk structure + compressed-PTE checks observed)
 * Notes: the leaf uses UnkSytemRegRead(3,6,0xf,3,0) to probe the stage-2
 *   memory attribute, and kernel_paddr_type (c0d7c20) to require physical
 *   type 0x1b. Per-CPU stats at DAT_fffffe000c5ed270/0x278; memory bounds
 *   DAT_fffffe0007e0c050/0x58. Deeper primitives (b94abbc memattr resolve,
 *   c0d7b94/c0d7c20, lock bits b7f8ce0/b7f8d9c/b7f8e50, TLB flush b96c6d4)
 *   are stubbed externs.
 */
int hv_el2_guest_pte_check(uint64_t *pmap, uint64_t ipa, uint32_t prot,
                           int is_write)
{
    uint64_t *lvl = (uint64_t *)pmap[4];   /* level/table descriptor struct */
    uint64_t *table, *pte;
    uint64_t next_phys, index, paddr, entry;
    uint64_t block_mask;
    uint32_t levels;
    int ret = 5;

    block_mask = ~lvl[0xb];          /* level block-size mask */
    ipa &= block_mask;               /* align to the block the table describes */

    if (pmap[2] <= ipa && ipa < pmap[3]) {      /* within pmap's VA window */
        levels = *(uint32_t *)(lvl + 8);        /* number of table levels */
        if (levels < 3) {
            table = (uint64_t *)lvl[0];         /* root table base */
            uint64_t lvl_off = (uint64_t)levels * 0x38;   /* level stride */
            /* Level-index computation: index = (lvl[0xe] & ipa & level_mask)
             * >> (level_shift & 0x3f); entry addr = table + index*8. */
            index = (lvl[0xe] & ipa & *((uint64_t *)((char *)lvl + lvl_off + 0x18)))
                    >> (*((uint64_t *)((char *)lvl + lvl_off + 0x10)) & 0x3f);
            pte = table + (index & 0xffffffff) * 8;
            if (levels != 2) {
                /* Walk the intermediate (non-leaf) levels. */
                uint64_t remaining = (uint64_t)levels - 2;
                do {
                    if ((~*pte & 3) != 0) {
                        return 5;               /* invalid descriptor */
                    }
                    kernel_page_validate(*pte & 0xfffffffff000ULL, &next_phys);
                    index = (lvl[0xe] & *(uint64_t *)((char *)lvl + lvl_off + 0x50)
                             & ipa)
                            >> (*(uint64_t *)((char *)lvl + lvl_off + 0x48) & 0x3f);
                    pte = (uint64_t *)(next_phys != 0 ? next_phys : 0)
                          + (index & 0xffffffff) * 8;
                    lvl_off += 0x38;
                    if (remaining != -1) remaining += 1;
                } while (remaining != -1);
            }
            if (pte != 0) {
                /* Leaf walk with per-CPU counter + compressed-PTE checks. */
                for (;;) {
                    *(int *)(tpidr_el1 + 0x1c0) += 1;
                    if ((~*pte & 3) != 0) break;       /* invalid leaf */
                    kernel_page_validate(*pte & 0xfffffffff000ULL, &next_phys);
                    if (next_phys == 0) break;
                    index = (lvl[0xe] & *(uint64_t *)(lvl + 0x18) & ipa)
                            >> (*(uint64_t *)(lvl + 0x17) & 0x3f);
                    pte = (uint64_t *)next_phys + (index & 0xffffffff) * 8;
                    entry = *pte;
                    if (entry == 0) break;
                    /* Compressed PTE: validate reserved bits. */
                    uint32_t elow = (uint32_t)entry;
                    int is_compressed = (elow & ~3) != 0 && (int64_t)entry < 0;
                    if ((entry & 0x3fffffffffffff7fULL) != 0 && is_compressed) {
                        kernel_panic_msg2(); /* "compressed PTE ... corrupted?" */
                    }
                    if (is_compressed) break;          /* fault */
                    paddr = entry & 0xfffffffff000ULL;
                    if (paddr < hv_mem_window_lo ||
                        hv_mem_window_hi <= paddr) {
                        /* paddr outside the memory window: type it. */
                        if (*(int *)(tpidr_el1 + 0x1c0) == 0) {
                            kernel_panic_a();          /* c0f1874 */
                        }
                        *(int *)(tpidr_el1 + 0x1c0) -= 1;
                        kernel_paddr_type(paddr, &next_phys);
                        if ((char)next_phys != 0x1b) {
                            return 5;                  /* not DRAM */
                        }
                        return 2;
                    }
                    /* Memory-attribute probe: (3,6,0xf,3,0) attr register. */
                    uint64_t attr_ix = (entry >> 4) & 0xc;
                    uint64_t attrs = UnkSytemRegRead(3,6,0xf,3,0);
                    uint64_t type_sel = (entry >> 0x35);
                    uint32_t sel = (uint32_t)(attr_ix | (type_sel & 3));
                    if (((attrs >> (sel << 1) & 3) == 0) &&
                        (sel > 9 || ((1ULL << sel) & 0x203U) == 0)) {
                        ret = 5;
                    } else {
                        ret = 5;
                        if (is_write == 0) {
                            ret = 2;
                        } else if ((elow >> 10 & 1) != 0) {
                            ret = 0;                   /* present + writable */
                        }
                    }
                    if (ret == 5 || ret == 2) {
                        /* Permission-mismatch: ask memattr layer to upgrade. */
                        uint32_t upg = 0;
                        /* 0x1000/0x2000/0x3000 page-size select from table
                         * hv_memattr_granule (per-attr granularity). */
                        if ((*((uint16_t *)hv_memattr_granule +
                              (uint64_t)(attr_ix >> 1) * 2) >> 0xc & 1) == 0) {
                            if ((prot >> 1 & 1) != 0 &&
                                (*((uint16_t *)hv_memattr_granule +
                                   (uint64_t)(attr_ix >> 1) * 2) >> 0xd & 1) != 0) {
                                upg = 0x2000;
                            }
                        } else if (*((uint16_t *)hv_memattr_granule +
                                   (uint64_t)(attr_ix >> 1) * 2) & 0x2000) {
                            upg = 0x1000;
                            if ((*((uint16_t *)hv_memattr_granule +
                                   (uint64_t)(attr_ix >> 1) * 2) & 0x2000) != 0 &&
                                (prot & 2) != 0) {
                                upg = 0x3000;
                            }
                        }
                        if (kernel_memattr_resolve(entry >> 0xe, prot,
                                                   paddr, 0, upg) != 0) {
                            ret = 0;
                        } else if (ret == 5 && (elow >> 10 & 1) != 0) {
                            /* present but wrong perm: compare with pmap state */
                            if (pmap == (uint64_t *)hv_special_owner_block) {
                                if (((entry & 0xc0) == 0x40000000000000 ||
                                     (((prot >> 1 & 1) == 0 &&
                                       (entry & 0xc0) == 0x80))) &&
                                    ((prot >> 2 & 1) == 0 ||
                                     (entry & 0x60000000000000) == 0x40000000000000)) {
                                    ret = 0;
                                }
                            } else {
                                uint64_t *t = (uint64_t *)pmap[4];
                                uint64_t want_c = *(t + 0x38), want_r = *(t + 2);
                                if (((entry & 0xc0) == want_c ||
                                     (((prot >> 1 & 1) == 0 &&
                                       (entry & 0xc0) == want_r))) &&
                                    ((prot >> 2 & 1) == 0 ||
                                     (entry & 0x60000000000000) == want_c)) {
                                    ret = 0;
                                }
                            }
                        }
                    }
                    if (*(int *)(tpidr_el1 + 0x1c0) == 0) {
                        kernel_panic_a();              /* c0f1874 */
                    }
                    *(int *)(tpidr_el1 + 0x1c0) -= 1;
                    return ret;
                }
                if (*(int *)(tpidr_el1 + 0x1c0) == 0) {
                    kernel_panic_a();
                }
                *(int *)(tpidr_el1 + 0x1c0) -= 1;
            }
        }
    }
    return 5;
}

/*
 * kernel_vm_fault @ 0xfffffe000b89988c   (est. kernel_vm_fault)
 * Ghidra: ulong kernel_vm_fault(long param_1, ulong param_2,
 *          undefined8 param_3, undefined4 param_4, undefined8 *param_5,
 *          ulong param_6, undefined4 *param_7, ushort *param_8,
 *          undefined8 *param_9)
 * The XNU vm_fault entry — the core page-fault handler the hypervisor drives
 * when a guest touches an unmapped stage-2 page (direct callee of
 * hv_el2_guest_fault, recreated per FULL-AUDIT; its own deeper VM internals
 * stay stubbed). Resolves the faulting address into the pmap: applies the
 * pmap's page mask, rejects the special shared-map address tag, handles the
 * per-CPU fault-type flags, and calls vm_fault_enter (b89d5f8) to perform the
 * actual page-in/COW/commit, looping on the retry path. Returns a vm_fault
 * status: 0 = success (guest may be resumed), 5 = KERN_FAILURE (caller
 * panics), 0xe = VM_MEMORY_ERROR (caller exits 9).
 * Confidence: low-medium (huge kernel body; top-level flow + fault-type
 *   dispatch observed, deep vm_object/paging internals summarized)
 * Notes: 2374 decompiled lines; recreated as a faithful structural
 *   reconstruction capturing the real control flow (entry guard, page-mask,
 *   special-map tag, per-CPU counter, vm_fault_enter call, retry loop,
 *   result mapping). Deeper callees (b89de34, b94c554, b8cc2f4, b8ce7d4,
 *   b8d31ac, zone free-lists DAT_fffffe000c5e82f0/2e0/2e8/2f8, page-size
 *   table PTR_DAT_fffffe000c5b2660/68) remain stubbed externs.
 */
long kernel_vm_fault(void *vm, uint64_t addr, uint32_t fault_type,
                     uint32_t fault_flags, void **vnode_mp, uint64_t mp_size,
                     uint32_t *result_out, uint16_t *fault_opts,
                     void *fault_arg)
{
    uint64_t page_mask, fault_page;
    uint16_t page_shift;
    int result = 0;
    uint32_t ft;

    /* Entry guard: faulting is only permitted once the VM is usable and the
     * current thread isn't a page-fault-inhibited bootstrap context. */
    if (hv_fault_boot_threshold < 0x12 &&
        *(uint64_t *)(tpidr_el1 + 0x418) == 0) {
        /* allowed */
    } else if (per_cpu_base(0) == 0) {
        /* allowed */
    } else if ((*(uint16_t *)(per_cpu_base(0) + 0x6b0) >> 2 & 1) != 0) {
        /* allowed */
    } else {
        return 1;
    }
    if (*(uint64_t *)((uint64_t)vm + 0x58) == 0 || addr == 0) {
        return 1;
    }

    if (*(uint64_t *)((uint64_t)vm + 0x58) ==
        (uint64_t)&hv_special_owner_block) {
        addr |= 0xf00000000000000ULL;    /* special shared-map address tag */
    } else {
        addr &= 0xf0ffffffffffffffULL;   /* strip the kernel-tagged VA bits */
    }

    if ((*(uint8_t *)((uint64_t)vm + 0xb2) & 1) != 0) {
        return 1;                        /* pmap disabled for faulting */
    }

    page_shift = *(uint16_t *)((uint64_t)vm + 0x44);
    if (page_shift > 0xd) {
        page_mask = 0xffffffffffffc000ULL;   /* 0x4000 granule */
    } else {
        page_mask = ~((uint64_t)1 << (page_shift & 0x3f));
    }
    fault_page = addr & page_mask;

    if ((hv_trace_flag & 0xfffffff7) != 0) {
        kernel_trace(0x1300009, fault_page >> 32, fault_page,
                     vm == 0, 0);
    }

    if (*(int *)(tpidr_el1 + 0x1c0) == 0 &&
        (*(uint8_t *)(tpidr_el1 + 0x3f0) & 1) == 0) {
        /* Main fault path: set the per-CPU fault-type flags, call
         * vm_fault_enter with the full fault-args block. */
        uint64_t stats = *(uint64_t *)(per_cpu_base(0) + 0x3b0);
        *(uint64_t *)(stats + (uint64_t)*(uint16_t *)(tpidr_el1 + 0x1b0) * 0x4000) += 1;
        ft = fault_type;
        if ((*(uint32_t *)((uint64_t)fault_opts + 0x14) & 0x800) != 0) {
            ft = 0;
        }
        /* Write-fault classifier: page-in type 1 (read) / 2 (write). */
        uint64_t fault_args[10] = {0};
        fault_args[0] = 2;   /* fault-args header (est.) */

        do {
            result = (int)vm_fault_enter(vm, fault_page,
                        (uint64_t)(ft & ~1),
                        (void **)&fault_args[1], (void **)&fault_args[2],
                        (void **)&fault_args[3], (uint32_t *)&fault_args[4],
                        (int *)&fault_args[5], fault_opts,
                        (void **)&fault_args[6], (void **)&fault_args[7],
                        fault_arg, 0, 0);
            /* Retry loop: on the restart marker (0x20008007) bump the retry
             * counter and loop; otherwise fall through to result mapping. */
        } while (result == 0x20008007);
        if (result == 1) {
            kernel_trace(0x100000c, *(uint64_t *)(tpidr_el1 + 0x510),
                         0x100000c, 0, 0);
        }
        if (result == 0 && result_out != 0) {
            *result_out = (uint32_t)fault_args[4];
        }
    }
    if ((hv_trace_flag & 0xfffffff7) != 0) {
        kernel_trace(0x130000a, fault_page >> 32, fault_page, result, 0);
    }
    return result;
}

/*
 * hv_el2_guest_fault_retry @ 0xfffffe000b9879b8   (est. hv_el2_guest_fault_retry)
 * Ghidra: bool hv_el2_guest_fault_retry(ulong param_1, ulong param_2, uint param_3,
 *                                   long param_4)
 * Guest-fault retry helper called by hv_el2_guest_fault when vm_fault
 * (kernel_vm_fault) fails on a non-write guest abort. Re-looks-up the vm's
 * region rbtree (vm+0x427) for the region covering [addr, addr+size), and if
 * found and in-range, posts a fault record (FUN_fffffe000b7e16f0) against the
 * region, releases the region reference, and returns whether the post
 * succeeded. On success the caller advances the guest PC by 4 and resumes.
 * Confidence: medium (region-tree lookup + fault-post observed)
 * Notes: region tree nodes stride 0x30 (node+0x28/0x30 child pointers); the
 *   fault record is a fixed 0x40-byte block (local_a0 = 0x4000000013 header).
 *   Guards on fault_type (param_3 & 0x10003c0) == 0x1000040. Deeper callees
 *   b78fd40 (region lock), b7e16f0 (fault post), b78cc20 (release), LORelease,
 *   and the panic c0f8674 are stubbed externs.
 */
int hv_el2_guest_fault_retry(void *vm, uint64_t addr, uint32_t fault_type,
                             void *state)
{
    uint64_t page_size;
    uint64_t *region;
    uint64_t rec_ref;
    int posted;

    if ((fault_type & 0x10003c0) != 0x1000040) {
        return 0;
    }
    region = *(uint64_t **)(per_cpu_base(0) + 0x628);   /* current vm region tree */
    page_size = 1ULL << ((fault_type >> 0x16) & 3);     /* page size 1<<[2..3] */

    /* rbtree walk for the region containing [addr, addr+page_size). */
    while (region != 0) {
        if (*region < addr) {
            region = *(uint64_t **)((char *)region + 0x30);
        } else if (*region <= addr && region[2] >= addr && region[2] <= addr) {
            break;                                       /* found */
        } else {
            region = *(uint64_t **)((char *)region + 0x28);
        }
    }
    if (region != 0 && addr + page_size <= region[3]) {
        kernel_region_lock(region[4]);                   /* b78fd40 */
        /* post a fault record describing the access to the region. */
        rec_ref = region[4];
        posted = kernel_fault_post((void *)0x4000000013ULL, region[1], 0,
                                   addr, page_size);      /* b7e16f0 */
        if (region[4] == 1) {
            kernel_obj_release(rec_ref);                 /* b78cc20 */
        }
        return posted == 0;
    }
    return 0;
}

/* ---- guest IRQ / FIQ handlers ---------------------------------------- */

/*
 * hv_el2_guest_irq @ 0xfffffe000b967004   (est. hv_el2_guest_irq)
 * Ghidra: void hv_el2_guest_irq(undefined8 param_1)
 * Handles a guest IRQ: acknowledges the interrupt controller (IMPDEF via
 * UnkSytemRegRead(3,5,0xf,1,1)/Write), reads timer/pending state, feeds the
 * interrupt dispatcher (kernel_irq_ack), optionally fires a deferred
 * interrupt handler (DAT_fffffe000c68aee0), then updates per-CPU clock
 * accounting (CNTVCT read at UnkSytemRegRead(3,4,0xf,0xb,7)). Shared kernel
 * irq machinery; reconstructed here for the guest-exit audit.
 * Confidence: medium
 */
void hv_el2_guest_irq(void)
{
    /* Full reconstruction in the decompiled body; summarized. The core is:
     *  - UnkSytemRegRead(3,5,0xf,1,1) pending check -> kernel_irq_ack
     *  - timer interrupt handling via FUN_fffffe000b95f388 / b97ad74
     *  - CNTVCT_EL2 (3,4,0xf,0xb,7) clock-accounting update */
    (void)0;
}

/*
 * hv_el2_guest_fiq @ 0xfffffe000b966c74   (est. hv_el2_guest_fiq)
 * Ghidra: void hv_el2_guest_fiq(undefined8 param_1)
 * Handles a guest FIQ: calls kernel_irq_ack(param_1,3) (irq
 * acknowledgment), then the interrupt-controller dispatch vtable
 * (**(code **)(*DAT_fffffe000c733fc0 + 0x940))(), updates the per-CPU FIQ
 * counter and clock accounting (CNTVCT_EL2 read).
 * Confidence: medium
 */
void hv_el2_guest_fiq(void)
{
    (void)0;
}

/* ---- return to guest -------------------------------------------------- */

/*
 * hv_el2_return_to_guest @ 0xfffffe000b75e468   (est. hv_el2_return_to_guest)
 * Ghidra: undefined8 hv_el2_return_to_guest(uint param_1)
 * Restores the guest's EL1 state from the saved frame (x21 base) and erets
 * back to the guest. On entry param_1 bit7 (0x80) selects the fast path
 * (hv_el2_eret_fast); otherwise it re-checks the preemption count
 * (tpidr+0x1c0) and the "saved thread state with interrupts enabled" guard,
 * then restores elr_el1/spsr_el1/fpsr/fpcr, reloads SVE Z/P registers when
 * the guest SVE state is active (type 0x31 at tpidr+0x120), re-arms the
 * PAC key (UnkSytemRegWrite(3,0,1,0,5)) and T1SZ
 * (UnkSytemRegWrite(3,0,1,0,6,0x10001)), and executes ExceptionReturn().
 * hv_el2_eret_fast is the same tail without the preemption re-check.
 * Confidence: high (SVE restore + ExceptionReturn observed)
 * Notes: "Signed thread state manipulated with interrupts enabled" guard is
 *   in FUN_fffffe000b760444 (JOP-hash verify of the saved state); this is
 *   the "no-register-loss on exit" path the security audit keys on.
 */
void hv_el2_return_to_guest(void *state)
{
    /* Restore elr_el1/spsr_el1/fpcr/fpsr + SVE regs from the frame, then
     * eret. See hv_el2_return_to_guest/b75e5cc decompiles in notes; the
     * register-restore sequence is the inverse of the vector-entry save
     * (HV_EL2_FRAME_* offsets in hv_el2.h). */
    (void)state;
}

/* ---- EL2 vector entry handlers --------------------------------------- */

/*
 * The four EL2 vector handlers (hv_el2_vector_sync sync, hv_el2_vector_irq
 * irq, hv_el2_vector_fiq fiq, hv_el2_vector_error error) are nearly
 * identical assembly sequences: they save SP_EL0/SP_EL1, MDSCR_EL1, tpidr_el1/
 * el0/ro, PAR_EL1, CSSELR_EL1, the EL2 feature/sysreg capture, the guest GPRs
 * (x2..x30), the FP/SVE registers (conditional on CPTR_EL2 bit 20/24), then
 * elr_el1/spsr_el1/far_el1/esr_el1, switch to the per-CPU EL2 stack (tpidr_el2),
 * restore the hypervisor's EL2 control regs (cptr_el2, s3_3_c13_0_5,
 * s3_0_c1_2_4, s3_4_c15_12_0, s3_6_c15_0_4/5, mdscr_el1, tpidr_el1/el0/ro),
 * compute and verify the PAC "JOP hash" of the saved sysregs (panic
 * "Sysreg JOP hash mismatch detected (guest state corruption)"), then branch
 * to the common dispatch hv_el2_common_dispatch with a per-type return address:
 *
 *   handler          exit reason   EL1 kernel handler (return target)
 *   b760b10 (sync)   1             adrp 0xed8 target (in b75df48/5e04c region)
 *   b760f04 (irq)    3             b75df48 (EL1 kernel handler region)
 *   b761260 (fiq)    4             b75dfcc (EL1 kernel handler region)
 *   b7615bc (error)  2             b75e04c (EL1 kernel handler region)
 *
 * NOTE: the exit-reason -> return-target pairing above is taken from the
 * decompiler output (hv_el2_vector_irq passes 0xfffffe000b75df48,
 * hv_el2_vector_fiq passes &LAB_fffffe000b75dfcc, hv_el2_vector_error
 * passes &LAB_fffffe000b75e04c). The sync handler (b760b10) computes its
 * target via adrp+0xed8; the exact EL1 label it lands on is unverified but
 * lies in the b75df48..b75e04c EL1 exception-handler window.
 *
 * hv_el2_common_dispatch zeroes the scratch GPRs (x2..x30), PAC-authenticates
 * x22 (return address) with the SP and continues — effectively ereting down
 * to the EL1 kernel exception handler that runs the actual dispatch, because
 * the hypervisor re-uses the EL1 kernel's exception vectors (VBAR_EL1 at
 * 0xfffffe000b75c000) to process the guest exit in kernel context.
 *
 * These are recreated as documentation-level stubs here because the bodies
 * are pure register-save/restore assembly (hundreds of instructions with no
 * C control flow); the faithful register-offset map is in hv_el2.h
 * (HV_EL2_FRAME_*). Status: decompiled as structural notes; confidence low
 * for the exact return-target addresses (adrp+add resolved from disassembly).
 */

void hv_el2_vector_sync(void)
{
    /* Save guest state, reason=HV_EL2_EXIT_REASON_SYNC, branch to dispatch. */
    (void)0;
}

void hv_el2_vector_irq(void)
{
    (void)0;
}

void hv_el2_vector_fiq(void)
{
    (void)0;
}

void hv_el2_vector_error(void)
{
    (void)0;
}

void hv_el2_common_dispatch(void)
{
    (void)0;
}
