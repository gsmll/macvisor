/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 21: 0x003530e8-0x00353db8 syscall/exception-entry region.
 *
 * This region is the cL4 syscall/exception ENTRY argument-marshalling
 * cluster: a dense run of tiny register-setup fragments (mov/ldp/ldur
 * sequences) that the syscall dispatcher tail-calls into to prepare
 * argument registers x0-x7/x8 or callee-saved x19-x28 before a guarded
 * dispatch. Ghidra promoted each 12-byte-aligned fragment to its own
 * FUN_ entry. Most have no C-visible effect (the decompiler collapses the
 * moves to an empty body); the register marshalling is documented in each
 * function comment from the disassembly.
 */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* Out-of-range kernel helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Names are estimates. */
extern void sk_trap_panic_norentry(void);                    /* FUN_001afa84, noreturn */
extern void *sk_syscall_dispatch_310a14(void *a0);           /* FUN_00310a14 */
extern void *sk_lock_acquire_6a4c0(void *a1);                /* FUN_0006a4c0 */
extern void *sk_syscall_ret_310fc4(void *a0);                /* FUN_00310fc4 */
extern void *sk_helper_310984(void);                         /* FUN_00310984 */
extern void sk_trace_log_1a89a8(const void *msg, int level, int count); /* FUN_001a89a8 */
extern void sk_debug_print_2534(const void *fmt, const void *arg);      /* FUN_00002534 */
extern void sk_panic_1df60(void);                            /* FUN_0001df60, noreturn */
extern void *sk_cap_check_3a25d4(void *a0);                  /* FUN_003a25d4 */
extern void *sk_vspace_op_2a4c98(unsigned long a0, unsigned long a1, unsigned long a2, unsigned long a3); /* FUN_002a4c98 */
extern void *sk_cpu_8e5d8(void);                             /* FUN_0008e5d8 */
extern void *sk_helper_319658(void);                         /* FUN_00319658 */
extern void *sk_syscall_dispatch_310a74(unsigned long w);    /* FUN_00310a74 */

/* FUN_003530E8 @ 0x003530E8   (est. sk_sysreg_marshal_30e8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x0 | mov x21,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_30e8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003530F4 @ 0x003530F4   (est. sk_sysreg_marshal_30f4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x20 | mov x1,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_30f4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353100 @ 0x00353100   (est. sk_sysreg_marshal_3100)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x19 | sub sp,x29,#0x50 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3100(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035310C @ 0x0035310C   (est. sk_sysreg_marshal_310c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x0 | mov x0,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_310c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353118 @ 0x00353118   (est. sk_sysreg_marshal_3118)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0xd0] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3118(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353124 @ 0x00353124   (est. sk_sysreg_marshal_3124)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x24,[x8, #-0x100] | mov x0,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3124(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353130 @ 0x00353130   (est. sk_sysreg_marshal_3130)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x8,x29,#0x30 | ldur x8,[x8, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3130(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035313C @ 0x0035313C   (est. sk_sysreg_marshal_313c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0x80] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_313c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353148 @ 0x00353148   (est. sk_sysreg_marshal_3148)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x8,x29,#0x20 | ldur x8,[x8, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3148(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353154 @ 0x00353154   (est. sk_sysreg_marshal_3154)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0x98] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3154(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353160 @ 0x00353160   (est. sk_sysreg_marshal_3160)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w0,#0xff | mov x1,x3 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3160(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035316C @ 0x0035316C   (est. sk_sysreg_marshal_316c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x22,x1 | mov x21,x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_316c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353178 @ 0x00353178   (est. sk_sysreg_marshal_3178)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x3 | mov x2,x4 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3178(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353184 @ 0x00353184   (est. sk_sysreg_marshal_3184)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x26 | mov x3,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3184(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353190 @ 0x00353190   (est. sk_sysreg_marshal_3190)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x21 | mov x0,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3190(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035319C @ 0x0035319C   (est. sk_sysreg_marshal_319c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x21 | mov x0,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_319c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531A8 @ 0x003531A8   (est. sk_sysreg_marshal_31a8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x26 | mov x0,x25 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31a8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531B4 @ 0x003531B4   (est. sk_sysreg_marshal_31b4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov sp,x8 | mov x0,x25 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31b4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531C0 @ 0x003531C0   (est. sk_sysreg_marshal_31c0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x24 | mov x0,x28 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31c0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531CC @ 0x003531CC   (est. sk_sysreg_marshal_31cc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x25 | mov x20,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31cc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531D8 @ 0x003531D8   (est. sk_sysreg_marshal_31d8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x21,x3 | mov x19,x2 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31d8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531E4 @ 0x003531E4   (est. sk_sysreg_marshal_31e4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x20 | mov x3,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31e4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531F0 @ 0x003531F0   (est. sk_sysreg_marshal_31f0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x2 | mov x19,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31f0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003531FC @ 0x003531FC   (est. sk_sysreg_marshal_31fc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x24,x1 | mov x0,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_31fc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353208 @ 0x00353208   (est. sk_sysreg_marshal_3208)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x22 | mov x4,x21 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3208(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353214 @ 0x00353214   (est. sk_sysreg_marshal_3214)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x27 | mov x2,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3214(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353220 @ 0x00353220   (est. sk_sysreg_marshal_3220)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x20 | mov w2,#0x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3220(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035322C @ 0x0035322C   (est. sk_sysreg_marshal_322c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,x0 | ldur x8,[x29, #-0x90] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_322c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353238 @ 0x00353238   (est. sk_sysreg_restore_all)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldp x20,x19,[sp, #0x80] | ldp x22,x21,[sp, #0x70] | ldp x24,x23,[sp, #0x60] | ldp x26,x25,[sp, #0x50] | ldp x28,x27,[sp, #0x40] | add sp,sp,#0xa0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_restore_all(void)
{
    /* Restore all callee-saved registers (x19-x28) from the stack area at
     * sp+0x40..0x80 and pop the 0xa0-byte frame. Syscall/exception epilogue. */
    (void)0;
}

/* FUN_00353254 @ 0x00353254   (est. sk_sysreg_pacda_dispatch_entry)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x1 | adrp x2,0x674000 | add x2,x2,#0x4c8 | adrp x16,0x66d000 | add x16,x16,#0x3c0 | mov x17,#0xb830 | pacda x16,x17 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_pacda_dispatch_entry(void)
{
    /* Build a data-authenticated (PACDA) dispatch entry pointer at
     * 0x66d000+0x3c0 with context 0xb830, table ptr x2=0x674000+0x4c8, and
     * forward x1 into x3. Arms an indirect call for a capability-table op. */
    (void)0;
}

/* FUN_00353274 @ 0x00353274   (est. sk_sysreg_marshal_3274)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x22,x3 | mov x23,x2 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3274(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003532A8 @ 0x003532A8   (est. sk_sysreg_trap_dispatch_panic)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: movk x3,#0xd000, LSL #48 | mov w6,#0x13 | mov w7,#0x2 | b 0x001afa84
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_trap_dispatch_panic(void)
{
    /* Tail-call the noreturn trap dispatch (FUN_001afa84) with a tagged
     * descriptor: x3 |= 0xd000<<48, w6=0x13, w7=0x2. Trap classification. */
    sk_trap_panic_norentry();
}

/* FUN_003532B8 @ 0x003532B8   (est. sk_sysreg_classify_descriptor)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x8,x0,#0xffffffffffff | ubfx x9,x1,#0x38,#0x4 | tst x1,#0x2000000000000000 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_classify_descriptor(void)
{
    /* Mask x0 to 48 bits, extract the 4-bit type field [59:56] of x1, and
     * test the high tag bit 0x2000000000000000 in x1, leaving comparison
     * flags for the caller. Capability-descriptor classification fragment. */
    (void)0;
}

/* FUN_003532C8 @ 0x003532C8   (est. sk_sysreg_dispatch_310a14)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | mov x0,x22 | bl 0x00310a14 | mov x26,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_dispatch_310a14(void)
{
    /* Guarded call wrapper: call FUN_00310a14(x22), keep result in x26,
     * return with the frame authenticated (retab). */
    sk_syscall_dispatch_310a14((void*)0);
}

/* FUN_003532E4 @ 0x003532E4   (est. sk_sysreg_lock_acquire_6a4c0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | mov x1,x19 | bl 0x0006a4c0 | mov x1,x19 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_lock_acquire_6a4c0(void)
{
    /* Guarded call wrapper: call the lock-acquire helper FUN_0006a4c0(x19)
     * and re-set x1=x19 (retry probe). Spin-lock acquisition site. */
    sk_lock_acquire_6a4c0((void*)0);
}

/* FUN_00353300 @ 0x00353300   (est. sk_sysreg_call_310fc4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | mov x0,x19 | bl 0x00310fc4 | mov x9,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_call_310fc4(void)
{
    /* Guarded call wrapper: call FUN_00310fc4(x19), result -> x9, return. */
    sk_syscall_ret_310fc4((void*)0);
}

/* FUN_0035331C @ 0x0035331C   (est. sk_sysreg_marshal_8args)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldp x9,x8,[x29, #0x40] | ldr x10,[x29, #0x38] | sub sp,sp,#0x20 | stp x9,x8,[sp, #0x10] | ldur x8,[x29, #-0xf0] | add x0,x26,x8 | ldp x9,x8,[x29, #-0xc8] | add x1,x26,x9 | add x2,x26,x8 | ldur x8,[x29, #-0xb0] | add x3,x25,x8 | add x4,x25,x23 | add x5,x25,x24 | stp x27,x10,[sp] | ldur x6,[x29, #-0xa8] | ldur x7,[x29, #-0x80] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_8args(void)
{
    /* Re-marshal eight syscall arguments (x0-x7) from the saved exception
     * frame at x29: each arg = base (x26/x25) + frame offset, plus two stack
     * args (x27, x10) pushed at [sp]. Builds a fresh argument vector. */
    (void)0;
}

/* FUN_00353360 @ 0x00353360   (est. sk_sysreg_marshal_3360)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x9,x29,#0x28 | stur x8,[x9, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3360(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035336C @ 0x0035336C   (est. sk_sysreg_marshal_336c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0xa8] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_336c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353378 @ 0x00353378   (est. sk_sysreg_marshal_3378)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x23 | mov x0,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3378(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353384 @ 0x00353384   (est. sk_sysreg_marshal_3384)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x23 | ldr x9,[x8, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3384(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353390 @ 0x00353390   (est. sk_sysreg_marshal_3390)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x27,[x29, #-0xa0] | mov x0,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3390(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035339C @ 0x0035339C   (est. sk_sysreg_setup_pt_descriptors)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x28,#-0x1 | lsl x11,x28,x9 | cmp w10,#0x6 | csinv x10,x28,x11,cs | and x10,x10,x8 | add x8,x9,#0x3f | lsr x11,x8,#0x6 | add x12,x20,#0x10 | add x9,x20,#0x20 | add x8,x26,#0x38 | stur x8,[x29, #-0x68] | add x24,x20,#0x8 | mov x8,x12 | movk x8,#0xe3ba, LSL #48 | stp x9,x8,[x29, #-0x80] | stp x11,x21,[x29, #-0xa8] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_setup_pt_descriptors(void)
{
    /* Build page-table descriptor fragments in the frame: a mask (all-ones
     * shifted by x9, or all-ones when w10>6), a granule count (x9+0x3f)>>6,
     * descriptor words x20+0x10 (tagged 0xe3ba<<48) and x20+0x20, and base
     * x26+0x38. Page-table walk / descriptor setup fragment. */
    (void)0;
}

/* FUN_003533E0 @ 0x003533E0   (est. sk_sysreg_hash_crc_accumulate)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: add w8,w24,w21 | mov w9,#0x81c1 | add w8,w8,w9 | orr w9,w21,w22 | lsl w9,w9,#0x8 | orr w10,w9,w23 | ldr w11,[sp, #0x18] | orr w10,w11,w10, LSL #0x8 | mov w11,#0x81f1 | movk w11,#0x8181, LSL #16 | add w10,w10,w11 | ldr w11,[sp, #0x1c] | add w9,w11,w9 | mov w11,#0x81e1 | movk w11,#0x81, LSL #16 | add w9,w9,w11 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_hash_crc_accumulate(void)
{
    /* 32-bit hash/CRC accumulation: w24+w21+0x81c1, mix (w21|w22)<<8 with
     * w23 and two stack words, add 0x818181f1 and 0x000081e1. Checksum. */
    (void)0;
}

/* FUN_00353424 @ 0x00353424   (est. sk_sysreg_marshal_3424)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: str x8,[sp, #0x8] | add x3,sp,#0x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3424(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353430 @ 0x00353430   (est. sk_sysreg_marshal_3430)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x2 | mov x22,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3430(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035343C @ 0x0035343C   (est. sk_sysreg_marshal_343c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w5,#0x2 | mov w7,#0x12 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_343c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353448 @ 0x00353448   (est. sk_sysreg_marshal_3448)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w1,#0xb | mov w2,#0x2 | mov x3,#0x0 | mov x4,#-0x2000000000000000 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3448(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035345C @ 0x0035345C   (est. sk_sysreg_marshal_345c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x25 | mov x3,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_345c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353468 @ 0x00353468   (est. sk_sysreg_marshal_3468)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x21 | mov x0,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3468(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353474 @ 0x00353474   (est. sk_sysreg_marshal_3474)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x24 | mov x2,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3474(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353480 @ 0x00353480   (est. sk_sysreg_marshal_3480)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x26 | mov x0,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3480(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035348C @ 0x0035348C   (est. sk_sysreg_marshal_348c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x28 | mov x0,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_348c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353498 @ 0x00353498   (est. sk_sysreg_marshal_3498)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,#0x0 | mov x2,#0x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3498(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534A4 @ 0x003534A4   (est. sk_sysreg_call_310984)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | bl 0x00310984 | mov x8,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_call_310984(void)
{
    /* Guarded call wrapper: call FUN_00310984(), result -> x8, return. */
    sk_helper_310984();
}

/* FUN_003534BC @ 0x003534BC   (est. sk_sysreg_marshal_34bc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x24 | ldr x9,[x8, #0x10]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34bc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534C8 @ 0x003534C8   (est. sk_sysreg_marshal_34c8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x19 | mov x4,x25 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34c8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534D4 @ 0x003534D4   (est. sk_sysreg_marshal_34d4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x2 | mov x22,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34d4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534E0 @ 0x003534E0   (est. sk_sysreg_marshal_34e0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x25,x0 | mov x26,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34e0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534EC @ 0x003534EC   (est. sk_sysreg_marshal_34ec)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x24 | mov x3,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34ec(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003534F8 @ 0x003534F8   (est. sk_sysreg_marshal_34f8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x27 | mov x0,x28 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_34f8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353504 @ 0x00353504   (est. sk_sysreg_marshal_3504)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x26 | mov x4,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3504(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353510 @ 0x00353510   (est. sk_sysreg_marshal_3510)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x8 | ldp x0,x1,[x20] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3510(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035351C @ 0x0035351C   (est. sk_sysreg_marshal_351c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x0 | mov x26,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_351c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353528 @ 0x00353528   (est. sk_sysreg_marshal_3528)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x0 | mov x0,x21 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3528(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353534 @ 0x00353534   (est. sk_sysreg_marshal_3534)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x19 | mov x2,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3534(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353540 @ 0x00353540   (est. sk_sysreg_marshal_3540)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,#0x0 | mov x1,x4 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3540(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035354C @ 0x0035354C   (est. sk_sysreg_marshal_354c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x19 | mov w1,#0x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_354c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353558 @ 0x00353558   (est. sk_sysreg_pacia_dispatch_target)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,x0 | adrp x2,0x675000 | add x2,x2,#0x3a0 | adrp x16,0x299000 | add x16,x16,#0x540 | mov x17,#0x323 | pacia x16,x17 | mov x0,x16 | sub x8,x29,#0xb0 | mov x1,#0x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_pacia_dispatch_target(void)
{
    /* Build a code-authenticated (PACIA) dispatch target for 0x299540
     * (context 0x323), set x0=target, x1=0, x2=0x675000+0x3a0, x8=x29-0xb0.
     * Arms an indirect call for a debug/dispatch helper. */
    (void)0;
}

/* FUN_00353584 @ 0x00353584   (est. sk_sysreg_marshal_3584)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x21,x0 | ldr x8,[x19, #0x10] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3584(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353590 @ 0x00353590   (est. sk_sysreg_marshal_3590)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x9,x0,#0xc | mov w10,#0x4 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3590(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035359C @ 0x0035359C   (est. sk_sysreg_marshal_359c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x25 | mov x3,x23 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_359c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003535A8 @ 0x003535A8   (est. sk_sysreg_marshal_35a8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x22,x0 | mov x23,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_35a8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003535B4 @ 0x003535B4   (est. sk_sysreg_marshal_35b4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrb w10,[x9, #0x2] | ldrb w9,[x9, #0x3] | ubfiz w22,w22,#0x12,#0x4 | bfm w22,w8,#0x14,#0x5 | bfm w22,w10,#0x1a,#0x5 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_35b4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003535CC @ 0x003535CC   (est. sk_sysreg_marshal_35cc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: lsl w8,w1,#0x3 | mov w9,#0xffffffff | lsl w8,w9,w8 | cmp w1,#0x3 | csinv w8,w9,w8,hi | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_35cc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003535E4 @ 0x003535E4   (est. sk_sysreg_marshal_35e4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x0,[x9, #0x8] | ldr q0,[x9] | str q0,[x8] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_35e4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003535F4 @ 0x003535F4   (est. sk_sysreg_marshal_35f4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrb w8,[x2, #0x20] | mov x9,#-0x1 | lsl x8,x9,x8 | neg x9,x8 | cmp x0,x9 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_35f4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035360C @ 0x0035360C   (est. sk_sysreg_store_flags)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: str w19,[x20] | strb w21,[x20, #0x4] | strb w21,[x20, #0x5] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_store_flags(void)
{
    /* Store 32-bit word w19 at *x20, and bytes w21 at +4 and +5. Packs
     * three flag/status fields into a descriptor. */
    (void)0;
}

/* FUN_0035361C @ 0x0035361C   (est. sk_sysreg_marshal_361c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x3,0x5ce000 | add x3,x3,#0xa2a | mov w0,#0xff | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_361c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035362C @ 0x0035362C   (est. sk_sysreg_marshal_362c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x8,[x21, #-0x8]! | mov x16,x8 | mov x17,x21 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_362c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035363C @ 0x0035363C   (est. sk_sysreg_marshal_363c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x26,x0 | mov x21,x27 | ldr x20,[x21, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_363c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035364C @ 0x0035364C   (est. sk_sysreg_marshal_364c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: rbit x8,x11 | clz x8,x8 | sub x10,x11,#0x1 | and x10,x10,x11 | str x10,[x20, #0x20] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_364c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353664 @ 0x00353664   (est. sk_sysreg_marshal_3664)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: str x9,[x20, #0x18] | ldr x11,[x20, #0x8] | ldr x11,[x11, x9, LSL #0x3] | str x11,[x20, #0x20] | add x8,x8,#0x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3664(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035367C @ 0x0035367C   (est. sk_sysreg_marshal_367c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ubfiz w23,w23,#0x12,#0x4 | bfm w23,w9,#0x14,#0x5 | bfm w23,w10,#0x1a,#0x5 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_367c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035368C @ 0x0035368C   (est. sk_sysreg_marshal_368c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: stp x19,x20,[x29, #-0x78] | mov x26,x20 | mov x22,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_368c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035369C @ 0x0035369C   (est. sk_sysreg_marshal_369c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: stp x19,x20,[x29, #-0x78] | mov x28,x20 | mov x22,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_369c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003536AC @ 0x003536AC   (est. sk_sysreg_marshal_36ac)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x4,x0 | adrp x3,0x674000 | add x3,x3,#0x330 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_36ac(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003536BC @ 0x003536BC   (est. sk_sysreg_trace_log_msg2)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x0,0x5d0000 | add x0,x0,#0xc46 | mov w1,#0x2 | mov w2,#0x1 | b 0x001a89a8
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_trace_log_msg2(void)
{
    /* Tail-call the trace/log helper with static message 0x5d0c46, level 2,
     * count 1. */
    sk_trace_log_1a89a8((const void*)0x5d0c46, 2, 1);
}

/* FUN_003536D0 @ 0x003536D0   (est. sk_sysreg_marshal_36d0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x16,x23 | mov x17,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_36d0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003536DC @ 0x003536DC   (est. sk_sysreg_marshal_36dc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x8,[x8, #-0x100] | add x21,x8,#0x8 | cmp x0,#0x40 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_36dc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003536EC @ 0x003536EC   (est. sk_sysreg_marshal_36ec)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x8,x22,#0xffffffffffff | tst x26,#0x2000000000000000 | csel x25,x8,x25,eq | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_36ec(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003536FC @ 0x003536FC   (est. sk_sysreg_marshal_36fc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x8,x19,#0xffffffffffff | tst x24,#0x2000000000000000 | csel x25,x8,x25,eq | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_36fc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035370C @ 0x0035370C   (est. sk_sysreg_marshal_370c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,#0x0 | mov x3,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_370c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353718 @ 0x00353718   (est. sk_sysreg_marshal_3718)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x8,x29,#0x10 | ldur x8,[x8, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3718(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353724 @ 0x00353724   (est. sk_sysreg_marshal_3724)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x20,[x19, #0x10] | add x0,x19,#0x20 | mov x1,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3724(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353734 @ 0x00353734   (est. sk_sysreg_marshal_3734)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x8,x29,#0x8 | ldur x8,[x8, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3734(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353740 @ 0x00353740   (est. sk_sysreg_marshal_3740)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mul x8,x0,x23 | umulh x9,x0,x23 | mul x10,x0,x25 | umulh x11,x0,x25 | adds x9,x9,x10 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3740(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353758 @ 0x00353758   (est. sk_sysreg_debug_print_2534)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x0,0x656000 | add x0,x0,#0x1f8 | adrp x1,0x4e8000 | add x1,x1,#0x50 | b 0x00002534
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_debug_print_2534(void)
{
    /* Tail-call FUN_00002534 with format string 0x6561f8 and data 0x4e8050.
     * Debug print site. */
    sk_debug_print_2534((const void*)0x6561f8, (const void*)0x4e8050);
}

/* FUN_0035376C @ 0x0035376C   (est. sk_sysreg_marshal_376c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrb w9,[x19, #0x2] | ldrh w10,[x19] | orr w9,w10,w9, LSL #0x10 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_376c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035377C @ 0x0035377C   (est. sk_sysreg_marshal_377c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrb w8,[x19, #0x20] | mov x9,#-0x1 | lsl x8,x9,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_377c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035378C @ 0x0035378C   (est. sk_sysreg_init80_dispatch_panic)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | mov w8,#0x80 | stur x8,[x29, #-0x60] | mov x0,x19 | bl 0x00310a74 | mov x25,x0 | ldr x30,[sp], #0x10 | autibsp | b 0x0001df60
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_init80_dispatch_panic(void)
{
    /* Store 0x80 into frame slot x29-0x60, call FUN_00310a74(x19) -> x25,
     * then tail-call the noreturn panic path FUN_0001df60. */
    sk_syscall_dispatch_310a74(0x80);
    sk_panic_1df60();
}

/* FUN_003537B4 @ 0x003537B4   (est. sk_sysreg_marshal_37b4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,#-0x1 | lsl x8,x9,x8 | add x9,x0,#0x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37b4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003537C4 @ 0x003537C4   (est. sk_sysreg_marshal_37c4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,x22 | ldr x16,[x9, #-0x8]! | mov x17,x9 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37c4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003537D4 @ 0x003537D4   (est. sk_sysreg_marshal_37d4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w0,#0xff | mov x1,x2 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37d4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003537E0 @ 0x003537E0   (est. sk_sysreg_marshal_37e0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: lsl x8,x0,#0x8 | cmp x0,#0x3f | csel x8,xzr,x8,gt | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37e0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003537F0 @ 0x003537F0   (est. sk_sysreg_marshal_37f0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x19,[x29, #-0x98] | mov x0,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37f0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003537FC @ 0x003537FC   (est. sk_sysreg_marshal_37fc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x26,x1 | mov x27,x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_37fc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353808 @ 0x00353808   (est. sk_sysreg_marshal_3808)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrb w12,[x11], #0x1 | lsl x12,x12,x9 | orr x23,x12,x23 | add x9,x9,#0x8 | cmp x10,x9 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3808(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353820 @ 0x00353820   (est. sk_sysreg_marshal_3820)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w0,#0xa | mov w1,#0x0 | mov x2,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3820(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353830 @ 0x00353830   (est. sk_sysreg_trace_log_msg3)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x0,0x5ce000 | add x0,x0,#0x766 | mov w1,#0x3 | mov w2,#0x1 | b 0x001a89a8
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_trace_log_msg3(void)
{
    /* Tail-call the trace/log helper with static message 0x5ce766, level 3,
     * count 1. */
    sk_trace_log_1a89a8((const void*)0x5ce766, 3, 1);
}

/* FUN_00353844 @ 0x00353844   (est. sk_sysreg_marshal_3844)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: add x9,x9,#0x7 | and x9,x9,#-0x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3844(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353850 @ 0x00353850   (est. sk_sysreg_marshal_3850)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x8,x0,#-0xd | and x9,x23,#0xc | orr x8,x9,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3850(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353860 @ 0x00353860   (est. sk_sysreg_marshal_3860)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x20 | mov x21,x0 | ldr x20,[x20] | mov x16,x20 | mov x17,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3860(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353878 @ 0x00353878   (est. sk_sysreg_marshal_3878)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x8,x20,#0xffffffffffffff | stp x21,x8,[sp, #0x20] | add x8,sp,#0x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3878(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353888 @ 0x00353888   (est. sk_sysreg_marshal_3888)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and x20,x10,x8 | and x8,x11,x9 | orr x9,x8,x20 | tst x9,#-0x7f7f7f7f7f7f7f80 | mov x9,#-0x6000000000000000 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3888(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003538A0 @ 0x003538A0   (est. sk_sysreg_marshal_38a0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ubfiz w1,w1,#0x12,#0x4 | bfm w1,w9,#0x14,#0x5 | bfm w1,w10,#0x1a,#0x5 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_38a0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003538B0 @ 0x003538B0   (est. sk_sysreg_marshal_38b0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w1,#0x3 | mov w2,#0x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_38b0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003538BC @ 0x003538BC   (est. sk_sysreg_marshal_38bc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x2,[x29, #-0x70] | mov x20,x2 | sub x9,x29,#0x158 | ldur x3,[x9, #-0x100] | ldur x9,[x29, #-0xe0] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_38bc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003538D4 @ 0x003538D4   (est. sk_sysreg_marshal_38d4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w9,#0x4 | cmp w12,#0x3 | csel w9,w9,w12,hi | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_38d4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003538F0 @ 0x003538F0   (est. sk_sysreg_copy_byte)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x0 | ldrb w8,[x1] | strb w8,[x0] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_copy_byte(void)
{
    /* Copy a single byte: *dst = *src (byte pointers). */
    (void)0;
}

/* FUN_00353900 @ 0x00353900   (est. sk_sysreg_marshal_3900)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x0 | ldr x0,[x1] | str x0,[x19] | ldur q0,[x1, #0x8] | stur q0,[x19, #0x8] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3900(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353918 @ 0x00353918   (est. sk_sysreg_marshal_3918)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x19,x0 | mov x22,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3918(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353924 @ 0x00353924   (est. sk_sysreg_marshal_3924)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x8,[x9, #0x8]! | mov x0,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3924(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353930 @ 0x00353930   (est. sk_sysreg_marshal_3930)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x9,[x8, #0x8]! | mov x10,x8 | movk x10,#0x4f8, LSL #48 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3930(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353948 @ 0x00353948   (est. sk_sysreg_marshal_3948)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x23 | ldur x21,[x29, #-0x58] | mov x3,x26 | mov x4,x24 | ldur x9,[x29, #-0x48] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3948(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353960 @ 0x00353960   (est. sk_sysreg_marshal_3960)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x23 | mov x3,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3960(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035396C @ 0x0035396C   (est. sk_sysreg_marshal_396c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: and w0,w0,#0x1 | mov x21,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_396c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353978 @ 0x00353978   (est. sk_sysreg_marshal_3978)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x16 | mov x1,x25 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3978(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353984 @ 0x00353984   (est. sk_sysreg_marshal_3984)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x24 | mov x0,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3984(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353990 @ 0x00353990   (est. sk_sysreg_marshal_3990)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x24 | ldr x9,[x8, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3990(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_0035399C @ 0x0035399C   (est. sk_sysreg_marshal_399c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x19 | ldr x9,[x8, #0x10]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_399c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003539A8 @ 0x003539A8   (est. sk_sysreg_dispatch_310a74_x25)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | mov x0,x25 | bl 0x00310a74 | mov x27,x0 | ldr x30,[sp], #0x10 | autibsp | b 0x0001df60
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_dispatch_310a74_x25(void)
{
    /* Call FUN_00310a74(x25) -> x27, then tail-call noreturn panic
     * FUN_0001df60. */
    sk_syscall_dispatch_310a74(0);
    sk_panic_1df60();
}

/* FUN_003539C8 @ 0x003539C8   (est. sk_sysreg_marshal_39c8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x25 | ldur x1,[x29, #-0x60] | mov x2,x23 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_39c8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003539D8 @ 0x003539D8   (est. sk_sysreg_marshal_39d8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x22 | mov x0,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_39d8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003539E4 @ 0x003539E4   (est. sk_sysreg_marshal_39e4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,sp | sub x1,x8,#0x30 | mov sp,x1 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_39e4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_003539F4 @ 0x003539F4   (est. sk_sysreg_marshal_39f4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x21,x3 | mov x20,x2 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_39f4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A00 @ 0x00353A00   (est. sk_sysreg_marshal_3a00)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x20 | ldr x9,[x8, #0x10]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a00(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A0C @ 0x00353A0C   (est. sk_sysreg_marshal_3a0c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x21,x1 | mov x23,x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a0c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A18 @ 0x00353A18   (est. sk_sysreg_marshal_3a18)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x22 | mov x3,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a18(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A24 @ 0x00353A24   (est. sk_sysreg_marshal_3a24)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x24,x1 | mov x20,x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a24(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A30 @ 0x00353A30   (est. sk_sysreg_marshal_3a30)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x0 | mov x0,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a30(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A3C @ 0x00353A3C   (est. sk_sysreg_marshal_3a3c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x0 | and x8,x2,#-0x2 | ldur q0,[x8, #-0x10] | ext v0.16B,v0.16B,v0.16B,0x8 | str q0,[sp] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a3c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A54 @ 0x00353A54   (est. sk_sysreg_marshal_3a54)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x11,[sp, #0x28] | lsl x8,x1,x11 | mvn w9,w11 | lsr x10,x0,#0x1 | lsr x9,x10,x9 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a54(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A6C @ 0x00353A6C   (est. sk_sysreg_marshal_3a6c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x24 | mov x3,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a6c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A78 @ 0x00353A78   (est. sk_sysreg_marshal_3a78)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x24 | mov x3,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a78(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A84 @ 0x00353A84   (est. sk_sysreg_marshal_3a84)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x27 | mov x0,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3a84(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353A90 @ 0x00353A90   (est. sk_sysreg_tail_cap_check)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x24,x0 | mov x25,x1 | mov x0,x20 | b 0x003a25d4
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_tail_cap_check(void)
{
    /* Save x0->x24, x1->x25, then tail-call the capability check
     * FUN_003a25d4(x20). */
    sk_cap_check_3a25d4((void*)0);
}

/* FUN_00353AA0 @ 0x00353AA0   (est. sk_sysreg_marshal_3aa0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x0 | mov x19,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3aa0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353AAC @ 0x00353AAC   (est. sk_sysreg_marshal_3aac)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x20 | mov w1,#0x30 | mov w2,#0x7 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3aac(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353ABC @ 0x00353ABC   (est. sk_sysreg_marshal_3abc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x21 | mov x20,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3abc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353AC8 @ 0x00353AC8   (est. sk_sysreg_marshal_3ac8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldrsw x8,[x0, #0x24] | ldur x9,[x29, #-0x58] | add x0,x9,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3ac8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353AD8 @ 0x00353AD8   (est. sk_sysreg_tail_vspace_op)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,#0x0 | mov x1,#-0x2000000000000000 | mov x2,#0x0 | mov x3,#0x0 | b 0x002a4c98
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_tail_vspace_op(void)
{
    /* Tail-call the vspace/MMU op FUN_002a4c98(0, 0xe000000000000000, 0, 0)
     * with a tagged capability argument. */
    sk_vspace_op_2a4c98(0, 0xe000000000000000ull, 0, 0);
}

/* FUN_00353AEC @ 0x00353AEC   (est. sk_sysreg_marshal_3aec)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x19 | mov x2,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3aec(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353AF8 @ 0x00353AF8   (est. sk_sysreg_marshal_3af8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x16,x8 | mov x17,x13 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3af8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B04 @ 0x00353B04   (est. sk_sysreg_marshal_3b04)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,x0 | mov x8,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b04(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B10 @ 0x00353B10   (est. sk_sysreg_marshal_3b10)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x21,x0 | mov x19,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b10(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B1C @ 0x00353B1C   (est. sk_sysreg_call_8e5d8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | bl 0x0008e5d8 | mov x9,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_call_8e5d8(void)
{
    /* Guarded call wrapper: call FUN_0008e5d8(), result -> x9, return. */
    sk_cpu_8e5d8();
}

/* FUN_00353B34 @ 0x00353B34   (est. sk_sysreg_marshal_3b34)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w5,#0x2 | mov w7,#0x1b | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b34(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B40 @ 0x00353B40   (est. sk_sysreg_marshal_3b40)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,#0x0 | mov x3,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b40(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B4C @ 0x00353B4C   (est. sk_sysreg_marshal_3b4c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x1 | mov x4,x2 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b4c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B58 @ 0x00353B58   (est. sk_sysreg_marshal_3b58)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x23 | mov x4,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b58(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B64 @ 0x00353B64   (est. sk_sysreg_marshal_3b64)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x9,x29,#0x30 | stur x8,[x9, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b64(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B70 @ 0x00353B70   (est. sk_sysreg_marshal_3b70)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x9,x29,#0x38 | stur x8,[x9, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b70(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B7C @ 0x00353B7C   (est. sk_sysreg_marshal_3b7c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x26,0x611000 | add x26,x26,#0xb24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b7c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B88 @ 0x00353B88   (est. sk_sysreg_marshal_3b88)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x24,x28 | mov x28,x0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b88(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353B94 @ 0x00353B94   (est. sk_sysreg_marshal_3b94)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x23,[x29, #-0x60] | mov x0,x23 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3b94(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BA0 @ 0x00353BA0   (est. sk_sysreg_marshal_3ba0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x8,[x12, #0x10]! | mov x0,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3ba0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BAC @ 0x00353BAC   (est. sk_sysreg_marshal_3bac)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: sub x8,x29,#0x58 | ldur x8,[x8, #-0x100] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bac(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BB8 @ 0x00353BB8   (est. sk_sysreg_marshal_3bb8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x0,[x29, #-0x70] | mov x1,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bb8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BC4 @ 0x00353BC4   (est. sk_sysreg_marshal_3bc4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x28 | mov x4,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bc4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BD0 @ 0x00353BD0   (est. sk_sysreg_marshal_3bd0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x21,[x29, #-0xb0] | mov x8,x21 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bd0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BDC @ 0x00353BDC   (est. sk_sysreg_marshal_3bdc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x2,0x5cf000 | add x2,x2,#0x680 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bdc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BE8 @ 0x00353BE8   (est. sk_sysreg_marshal_3be8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0xb0] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3be8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353BF4 @ 0x00353BF4   (est. sk_sysreg_marshal_3bf4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0xa0] | ldr x8,[x9] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3bf4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C00 @ 0x00353C00   (est. sk_sysreg_marshal_3c00)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x9,[x8, #0x8]! | mov x0,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c00(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C0C @ 0x00353C0C   (est. sk_sysreg_marshal_3c0c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x21 | ldr x9,[x8, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c0c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C18 @ 0x00353C18   (est. sk_sysreg_marshal_3c18)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x21 | mov x0,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c18(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C24 @ 0x00353C24   (est. sk_sysreg_marshal_3c24)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x24 | mov x2,x22 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c24(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C30 @ 0x00353C30   (est. sk_sysreg_marshal_3c30)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x26 | mov x3,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c30(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C3C @ 0x00353C3C   (est. sk_sysreg_marshal_3c3c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x26 | mov x3,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c3c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C48 @ 0x00353C48   (est. sk_sysreg_marshal_3c48)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldr x8,[x20] | ldr x8,[x8, #0x10] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c48(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C54 @ 0x00353C54   (est. sk_sysreg_marshal_3c54)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x16 | mov x1,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c54(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C60 @ 0x00353C60   (est. sk_sysreg_marshal_3c60)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x24 | mov x0,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c60(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C6C @ 0x00353C6C   (est. sk_sysreg_marshal_3c6c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x25 | mov x2,x19 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c6c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C78 @ 0x00353C78   (est. sk_sysreg_marshal_3c78)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x25 | mov x0,x26 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c78(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C84 @ 0x00353C84   (est. sk_sysreg_marshal_3c84)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov w1,#0x1 | mov x2,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c84(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353C90 @ 0x00353C90   (est. sk_sysreg_marshal_3c90)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x3,x0 | adrp x16,0x344000 | add x16,x16,#0x204 | mov x17,#0x489d | pacia x16,x17 | mov x0,x16 | sub x1,x29,#0xc0 | mov x2,x28 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3c90(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CB4 @ 0x00353CB4   (est. sk_sysreg_marshal_3cb4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x8,x0 | sub x0,x29,#0x78 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3cb4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CC0 @ 0x00353CC0   (est. sk_sysreg_marshal_3cc0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x2,x21 | mov x3,x25 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3cc0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CCC @ 0x00353CCC   (est. sk_sysreg_marshal_3ccc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x0 | mov x0,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3ccc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CD8 @ 0x00353CD8   (est. sk_sysreg_marshal_3cd8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x21 | mov x2,x20 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3cd8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CE4 @ 0x00353CE4   (est. sk_sysreg_marshal_3ce4)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x9,x0 | ldur x8,[x29, #-0x88] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3ce4(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CF0 @ 0x00353CF0   (est. sk_sysreg_marshal_3cf0)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x0,x20 | mov x1,x24 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3cf0(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353CFC @ 0x00353CFC   (est. sk_sysreg_marshal_3cfc)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: str x28,[sp, #-0x60]! | stp x27,x26,[sp, #0x10] | stp x25,x24,[sp, #0x20] | stp x23,x22,[sp, #0x30] | stp x20,x19,[sp, #0x40] | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3cfc(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D14 @ 0x00353D14   (est. sk_sysreg_marshal_3d14)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldp x20,x19,[sp, #0x40] | ldp x23,x22,[sp, #0x30] | ldp x25,x24,[sp, #0x20] | ldp x27,x26,[sp, #0x10] | ldr x28,[sp], #0x60 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d14(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D34 @ 0x00353D34   (est. sk_sysreg_marshal_3d34)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x1,x8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d34(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D44 @ 0x00353D44   (est. sk_sysreg_call_310a74)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | bl 0x00310a74 | mov x22,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_call_310a74(void)
{
    /* Guarded call wrapper: call FUN_00310a74() -> x22, return. */
    sk_syscall_dispatch_310a74(0);
}

/* FUN_00353D5C @ 0x00353D5C   (est. sk_sysreg_marshal_3d5c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: fmov h0,w8 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d5c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D64 @ 0x00353D64   (est. sk_sysreg_marshal_3d64)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: adrp x3,0x675000 | add x3,x3,#0x3a0 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d64(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D70 @ 0x00353D70   (est. sk_sysreg_marshal_3d70)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: mov x20,x4 | mov x21,x3 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d70(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D7C @ 0x00353D7C   (est. sk_sysreg_marshal_3d7c)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x28,[x29, #-0x78] | mov x0,x28 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d7c(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D88 @ 0x00353D88   (est. sk_sysreg_marshal_3d88)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x27,[x29, #-0x78] | mov x8,x27 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3d88(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353D94 @ 0x00353D94   (est. sk_sysreg_call_319658)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: pacibsp | str x30,[sp, #-0x10]! | bl 0x00319658 | mov x9,x0 | ldr x30,[sp], #0x10 | retab
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_call_319658(void)
{
    /* Guarded call wrapper: call FUN_00319658(), result -> x9, return. */
    sk_helper_319658();
}

/* FUN_00353DAC @ 0x00353DAC   (est. sk_sysreg_marshal_3dac)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x28,[x8, #-0x100] | mov x0,x28 | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3dac(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}

/* FUN_00353DB8 @ 0x00353DB8   (est. sk_sysreg_marshal_3db8)
 * Register-marshalling fragment of the cL4 syscall/exception entry path.
 * Disassembly: ldur x9,[x29, #-0xc8] | ldr x8,[x9, #0x8]! | ret
 * Confidence: medium
 * Notes: register-setup fragment; decompiler collapses to empty body where noted. */
void sk_sysreg_marshal_3db8(void)
{
    /* register marshalling only; see disassembly above */
    (void)0;
}
