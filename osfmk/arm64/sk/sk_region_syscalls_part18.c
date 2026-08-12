/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) --
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 18: 0x350c20-0x3517c0 syscall/exception-entry region.
 *
 * This slice is the ABI argument-marshalling layer of the syscall / exception
 * dispatch path. Each function is a small shim that loads syscall arguments
 * out of the preserved save-frame registers (x19-x28) into the ABI argument
 * registers (x0-x3 / x16-x17), performs a tiny setup, or forwards to a shared
 * helper. The Ghidra decompiler collapses most of these to a bare `return;`
 * because they only move registers (no stack frame / locals); the bodies below
 * are reconstructed from disassembly (mov / ldr / compute + ret) so the
 * register-forwards are documented. Names are estimates; the seL4/cL4
 * dispatch convention (saved regs = raw syscall args) is assumed.
 *
 * C symbols are suffixed with the FUN_ address to keep them unique; the
 * descriptive name appears in each header comment. */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

typedef uint8_t  und1_t;
typedef uint16_t und2_t;
typedef uint32_t und4_t;
typedef uint64_t und8_t;

/* Out-of-range callees (bodies reconstructed by their range workers). */

extern word_t sk_00027754(void); /* FUN_00027754 */
extern word_t sk_00310a44(word_t); /* FUN_00310a44 */
extern word_t sk_00310924(word_t); /* FUN_00310924 */
extern word_t sk_000277b8(void); /* FUN_000277b8 */
extern word_t sk_00310e20(void); /* FUN_00310e20 */
extern word_t sk_0008f6f4(void); /* FUN_0008f6f4 */
extern word_t sk_00117cc4(void); /* FUN_00117cc4 */


/* FUN_350c20 @ 0x350c20   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x19 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_350c20(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c2c @ 0x350c2c   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x21 ; x1=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_350c2c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c38 @ 0x350c38   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x28 ; x1=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_350c38(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c44 @ 0x350c44   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x20=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350c44(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c50 @ 0x350c50   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350c50(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c5c @ 0x350c5c   (est. sk_syscall_save_ret)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x1 ; x19=x0
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_save_ret_350c5c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c68 @ 0x350c68   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_350c68(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c74 @ 0x350c74   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x20=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350c74(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c80 @ 0x350c80   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x22 ; x1=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_350c80(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c8c @ 0x350c8c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x19 ; x2=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_350c8c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350cb4 @ 0x350cb4   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x25 ; x3=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x25
 */
static void sk_syscall_args_2_3_350cb4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350cf4 @ 0x350cf4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=[x10+0x10]
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: x1=([x10+0x48]*x20)+x8 computed; real fn
 */
static void sk_syscall_setup_scratch_350cf4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350d34 @ 0x350d34   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=(w9==0)?x27:x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also str w23->[x22+0x24], w8=w21&0xff, loads [&0x6adf10+0x10]
 */
static void sk_syscall_setup_scratch_350d34(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e14 @ 0x350e14   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x0
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x1=&0x6776f0
 */
static void sk_syscall_args_2_350e14(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e34 @ 0x350e34   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x25 ; w1=0x100
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x25
 */
static void sk_syscall_setup_scratch_350e34(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e44 @ 0x350e44   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x26 ; w1=0x100
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x26
 */
static void sk_syscall_setup_scratch_350e44(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e54 @ 0x350e54   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x27 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350e54(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e64 @ 0x350e64   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x19 ; x2=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350e64(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e74 @ 0x350e74   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x20 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350e74(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e84 @ 0x350e84   (est. sk_syscall_args_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x25 ; x3=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3_350e84(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350e94 @ 0x350e94   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x21 ; x3=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x21
 */
static void sk_syscall_args_2_3_350e94(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350ea4 @ 0x350ea4   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x26 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_350ea4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350eb0 @ 0x350eb0   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x26 ; w1=1 ; w2=1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_350eb0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350ec0 @ 0x350ec0   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x8
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x14=x9-x12, sp=x14 (stack switch)
 */
static void sk_syscall_setup_scratch_350ec0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350ed0 @ 0x350ed0   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x20 ; x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_350ed0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350edc @ 0x350edc   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; x1=x23 ; x2=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350edc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350eec @ 0x350eec   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; x1=x20 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350eec(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f0c @ 0x350f0c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x22=x0 ; x23=x1 ; x0=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350f0c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f1c @ 0x350f1c   (est. sk_syscall_args_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x24 ; x2=x26 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3_350f1c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f3c @ 0x350f3c   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x24 ; x3=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x24
 */
static void sk_syscall_args_2_3_350f3c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f4c @ 0x350f4c   (est. sk_syscall_args_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x27 ; x2=x22 ; x3=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3_350f4c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f7c @ 0x350f7c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: multi: x8=x0,x0=x20,x20=x24,x21=x19,ldur x9,[x29-0x58]
 */
static void sk_syscall_setup_scratch_350f7c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350f9c @ 0x350f9c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=sp ; x10=(x13+0xf)&~0xf
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350f9c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350fac @ 0x350fac   (est. sk_syscall_args_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x22 ; x2=x25 ; x3=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3_350fac(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350fbc @ 0x350fbc   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x0
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x17=x0, x16=[x17-8] (indirect call setup)
 */
static void sk_syscall_setup_scratch_350fbc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350fdc @ 0x350fdc   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x0 ; x24=x1 ; x0=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350fdc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350fec @ 0x350fec   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x20 ; x1=x26 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_350fec(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350ffc @ 0x350ffc   (est. sk_syscall_args_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x25 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3_350ffc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35100c @ 0x35100c   (est. sk_syscall_args_0_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x19 ; x1=x27 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_2_35100c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35101c @ 0x35101c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x0=x29-0x78 ; x8=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35101c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35102c @ 0x35102c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35102c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351038 @ 0x351038   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x23=[x29-0x88]
 */
static void sk_syscall_setup_scratch_351038(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351048 @ 0x351048   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x22 ; x0=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351048(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351058 @ 0x351058   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x22 ; x0=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351058(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351068 @ 0x351068   (est. sk_syscall_args_0_1_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=[x29-0x70] ; x1=x28 ; x2=x19 ; x3=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x9=x0,x8=[x29-0x90],x23=x24
 */
static void sk_syscall_args_0_1_2_3_351068(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351088 @ 0x351088   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   str w8->[sp+0x10] ; str x9->[sp+0x8]
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351088(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351094 @ 0x351094   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w5=2 ; w7=0x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351094(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510a0 @ 0x3510a0   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x24 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3510a0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510ac @ 0x3510ac   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x19 ; x1=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3510ac(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510b8 @ 0x3510b8   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x22 ; x1=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3510b8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510c4 @ 0x3510c4   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x20 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3510c4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510d0 @ 0x3510d0   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=[x9]
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x9=[x8-0x100] (double deref)
 */
static void sk_syscall_setup_scratch_3510d0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510dc @ 0x3510dc   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3510dc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510e8 @ 0x3510e8   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x20=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3510e8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3510f4 @ 0x3510f4   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3510f4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351100 @ 0x351100   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x20 ; x3=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351100(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35110c @ 0x35110c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w5=2 ; w7=0x16
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35110c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351118 @ 0x351118   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351118(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351130 @ 0x351130   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x21 ; x1=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351130(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351148 @ 0x351148   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=[x8-0x100]
 */
static void sk_syscall_args_2_351148(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351154 @ 0x351154   (est. sk_syscall_args_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x3=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x22
 */
static void sk_syscall_args_3_351154(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351160 @ 0x351160   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x22 ; x1=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351160(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35116c @ 0x35116c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x19 ; x2=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_35116c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351178 @ 0x351178   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351178(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351184 @ 0x351184   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351184(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351190 @ 0x351190   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x19 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351190(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35119c @ 0x35119c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x23 ; x2=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_35119c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511a8 @ 0x3511a8   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x23 ; x1=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3511a8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511b4 @ 0x3511b4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x16=[x8-8] (indirect setup)
 */
static void sk_syscall_setup_scratch_3511b4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511c0 @ 0x3511c0   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x27 ; x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3511c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511cc @ 0x3511cc   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x21 ; x3=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3511cc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511d8 @ 0x3511d8   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3511d8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511e4 @ 0x3511e4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x16=[x8-8] (indirect setup)
 */
static void sk_syscall_setup_scratch_3511e4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511f0 @ 0x3511f0   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x22 ; x3=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3511f0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3511fc @ 0x3511fc   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x20=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3511fc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351208 @ 0x351208   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x22
 */
static void sk_syscall_args_0_351208(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351214 @ 0x351214   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x25 ; x2=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351214(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351220 @ 0x351220   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x24 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351220(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35122c @ 0x35122c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x0 ; x0=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35122c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351238 @ 0x351238   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x19 ; x3=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351238(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351250 @ 0x351250   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351250(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351274 @ 0x351274   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; x1=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351274(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351280 @ 0x351280   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x23 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351280(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35128c @ 0x35128c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x22=x2 ; x23=x1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35128c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351298 @ 0x351298   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x28 ; x2=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351298(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3512c0 @ 0x3512c0   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; x1=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3512c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3512cc @ 0x3512cc   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x24
 */
static void sk_syscall_args_2_3512cc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351300 @ 0x351300   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x25 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351300(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35130c @ 0x35130c   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x21
 */
static void sk_syscall_args_2_35130c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351318 @ 0x351318   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x0=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351318(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351324 @ 0x351324   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x19 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351324(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351330 @ 0x351330   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x19 ; w1=1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_351330(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35133c @ 0x35133c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35133c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351354 @ 0x351354   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351354(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351360 @ 0x351360   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351360(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35136c @ 0x35136c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x23 ; x2=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_35136c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351378 @ 0x351378   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x20 ; x3=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351378(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351384 @ 0x351384   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351384(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351390 @ 0x351390   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w1=1 ; x2=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351390(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35139c @ 0x35139c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x24 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_35139c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513a8 @ 0x3513a8   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3513a8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513b4 @ 0x3513b4   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x23 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3513b4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513c0 @ 0x3513c0   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x28 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3513c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513cc @ 0x3513cc   (est. sk_syscall_args_3_4)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x3=x21 ; x4=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_3_4_3513cc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513d8 @ 0x3513d8   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3513d8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513e4 @ 0x3513e4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w1=1 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3513e4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513f0 @ 0x3513f0   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x21 ; x3=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3513f0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3513fc @ 0x3513fc   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x19 ; x3=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3513fc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351408 @ 0x351408   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x12=(x9+0xf)&~0xf
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x10=x9+0xf
 */
static void sk_syscall_setup_scratch_351408(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351414 @ 0x351414   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x28 ; x1=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351414(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351420 @ 0x351420   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351420(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35142c @ 0x35142c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x16 ; x2=sp+8
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35142c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351438 @ 0x351438   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x22 ; x2=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351438(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351444 @ 0x351444   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x19 ; x3=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351444(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351450 @ 0x351450   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x20 ; x1=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351450(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35145c @ 0x35145c   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x23 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_35145c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351468 @ 0x351468   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x22=x0 ; x23=x8
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351468(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35147c @ 0x35147c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x16=x19 ; x17=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35147c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351488 @ 0x351488   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x2 ; x2=x3
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351488(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351494 @ 0x351494   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x20 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351494(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3514a0 @ 0x3514a0   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x27 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3514a0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3514ac @ 0x3514ac   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x0 ; x20=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3514ac(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3514d0 @ 0x3514d0   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x21 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3514d0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3514dc @ 0x3514dc   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x21 ; x2=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3514dc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3514e8 @ 0x3514e8   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3514e8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35152c @ 0x35152c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=[x9+8]! ; x0=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35152c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351548 @ 0x351548   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w2=1 ; x3=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351548(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351554 @ 0x351554   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x27 ; x2=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351554(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351560 @ 0x351560   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x19 ; x3=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351560(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351584 @ 0x351584   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x23 ; x3=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351584(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351590 @ 0x351590   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x25 ; x20=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351590(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35159c @ 0x35159c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x0 ; x0=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35159c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515a8 @ 0x3515a8   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x20=x0 ; x0=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3515a8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515b4 @ 0x3515b4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x3=0 ; x4=0
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3515b4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515c0 @ 0x3515c0   (est. sk_syscall_args_3_4)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x3=x21 ; x4=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_3_4_3515c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515cc @ 0x3515cc   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x28 ; x1=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3515cc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515d8 @ 0x3515d8   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x25
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3515d8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515e4 @ 0x3515e4   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x23 ; x2=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3515e4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515f0 @ 0x3515f0   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x21=x0 ; x22=x8
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3515f0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3515fc @ 0x3515fc   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x22 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3515fc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351624 @ 0x351624   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   zero [sp+0x30..0x50]
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: movi v0=0; stp q0,q0->[sp+0x30]
 */
static void sk_syscall_setup_scratch_351624(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351630 @ 0x351630   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=[x9+8]! ; x0=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351630(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35163c @ 0x35163c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   w1=1 ; x2=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_35163c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351648 @ 0x351648   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x20 ; x1=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351648(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351654 @ 0x351654   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x19 ; x3=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351654(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351660 @ 0x351660   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x9=x0 ; x8=sp+8
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351660(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35169c @ 0x35169c   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x28 ; x2=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_35169c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516a8 @ 0x3516a8   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x28 ; x2=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3516a8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516b4 @ 0x3516b4   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x23
 */
static void sk_syscall_args_2_3516b4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516c0 @ 0x3516c0   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x27
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x9=[x8+8]
 */
static void sk_syscall_setup_scratch_3516c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516d8 @ 0x3516d8   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x25 ; x3=x24
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_3516d8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516e4 @ 0x3516e4   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x28
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_3516e4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516f0 @ 0x3516f0   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x28 ; x2=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_3516f0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3516fc @ 0x3516fc   (est. sk_syscall_args_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=&0x677880
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3516fc(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351708 @ 0x351708   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x21=x2 ; x20=x1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_351708(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351714 @ 0x351714   (est. sk_syscall_args_0_1)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x24 ; x1=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_1_351714(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351720 @ 0x351720   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x26 ; x2=x21
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351720(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35172c @ 0x35172c   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x23 ; w1=1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_35172c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351738 @ 0x351738   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x26 ; w1=1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_351738(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351744 @ 0x351744   (est. sk_syscall_args_1_2)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x1=x24 ; x2=x20
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_1_2_351744(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351768 @ 0x351768   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x21 ; x3=x26
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351768(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351774 @ 0x351774   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   restore x19-x28 from [sp+0x30..0x80]
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: epilogue: 5x ldp, add sp,#0x90
 */
static void sk_syscall_setup_scratch_351774(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_351790 @ 0x351790   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x0 ; x3=x1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_2_3_351790(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_35179c @ 0x35179c   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x8=x23
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x23=[x8-0x100]
 */
static void sk_syscall_setup_scratch_35179c(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3517a8 @ 0x3517a8   (est. sk_syscall_args_0)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x0=x25 ; w1=1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_args_0_3517a8(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_3517c0 @ 0x3517c0   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x23=x0 ; x24=x1
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_3517c0(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350c98 @ 0x350c98   (est. sk_syscall_ret_zero)
 * Body: mov x2,x0; x0=0; ret
 * Confidence: medium
 * Notes: mov x2,x0; x0=0; ret
 */
static word_t sk_syscall_ret_zero_350c98(void)
{
    return 0;
}

/* FUN_350ca4 @ 0x350ca4   (est. sk_global_ptr_shim)
 * Body: adrp x23,0x611000; add x23,#0xb24; add x4,x23,#0x18; ret
 * Confidence: low
 * Notes: adrp x23,0x611000; add x23,#0xb24; add x4,x23,#0x18; ret
 */
static word_t sk_global_ptr_shim_350ca4(void)
{
    /* x23=&0x611b24 (global); x4=x23+0x18; x0 unset */
    return 0;
}

/* FUN_350cc4 @ 0x350cc4   (est. sk_frame_load3)
 * Body: 3x ldur from x29-relative frame offsets
 * Confidence: low
 * Notes: 3x ldur from x29-relative frame offsets
 */
static word_t sk_frame_load3_350cc4(void)
{
    /* x2=[x29-0x100]; x3=[x29-0x1f0]; x9=[x29-0x238] */
    return 0;
}

/* FUN_350ce4 @ 0x350ce4   (est. sk_frame_store_tag)
 * Body: writes tag byte + word + tag into frame struct
 * Confidence: low
 * Notes: writes tag byte + word + tag into frame struct
 */
static void sk_frame_store_tag_350ce4(void)
{
    /* struct@x20: strb w21->[x20+4]; str w19->[x20]; strb w21->[x20+5] */
}

/* FUN_350d04 @ 0x350d04   (est. sk_stack_store_one)
 * Body: frame slot init to 1
 * Confidence: low
 * Notes: frame slot init to 1
 */
static void sk_stack_store_one_350d04(void)
{
    /* sub sp,#0x10; w8=1; str w8->[sp+8] */
}

/* FUN_350d14 @ 0x350d14   (est. sk_frame_ptr_70)
 * Body: x0 = x29 - 0x70
 * Confidence: low
 * Notes: x0 = x29 - 0x70
 */
static word_t sk_frame_ptr_70_350d14(void)
{
    /* x0=x29-0x70; x3=&0x6753a0 */
    return 0;
}

/* FUN_350d24 @ 0x350d24   (est. sk_double_deref)
 * Body: double deref of saved frame ptr
 * Confidence: low
 * Notes: double deref of saved frame ptr
 */
static word_t sk_double_deref_350d24(void)
{
    /* x9=[x29-0x118]; x8=[x9] */
    return 0;
}

/* FUN_350d54 @ 0x350d54   (est. sk_frame_fill)
 * Body: writes frame fields at +0x18,+0x20,+0x21,+0x22; x8=x23&0xff00000000
 * Confidence: low
 * Notes: writes frame fields at +0x18,+0x20,+0x21,+0x22; x8=x23&0xff00000000
 */
static int sk_frame_fill_350d54(word_t *frame)
{
    frame[0x18/8] = 0; /* str x0 -> [frame+0x18] */
    *(und1_t *)((char *)frame + 0x20) = 0; /* strb w25 */
    *(und1_t *)((char *)frame + 0x21) = 0; /* strb wzr */
    *(und2_t *)((char *)frame + 0x22) = 0; /* strh wzr */
    return 0; /* cmp x8(=x23&0xff00000000), #0x100000000 */
}

/* FUN_350d74 @ 0x350d74   (est. sk_indirect_setup)
 * Body: loads pair from [x2+0x10]; sets up indirect call (x16/x17)
 * Confidence: low
 * Notes: loads pair from [x2+0x10]; sets up indirect call (x16/x17)
 */
static void sk_indirect_setup_350d74(void)
{
    /* x22=x1; x19=x0; ldp x20,x1->[x2+0x10]; x25=x20; x23=[x25-8]!; x16=x23; x17=x25 */
}

/* FUN_350d94 @ 0x350d94   (est. sk_fatal_error_string)
 * Body: returns &0x5accd0 (s_Fatal_error_005accd0)
 * Confidence: high
 * Notes: returns &0x5accd0 (s_Fatal_error_005accd0)
 */
static char * sk_fatal_error_string_350d94(void)
{
    return "Fatal error";
}

/* FUN_350da4 @ 0x350da4   (est. sk_set_bitmask)
 * Body: mov x9,#-1; lsl x8,x9,x8; str x8,[x23]
 * Confidence: low
 * Notes: mov x9,#-1; lsl x8,x9,x8; str x8,[x23]
 */
static void sk_set_bitmask_350da4(word_t bit)
{
    /* x8 = -1L << (bit & 0x3f); store to [x23] */
}

/* FUN_350dc4 @ 0x350dc4   (est. sk_shift_load)
 * Body: byte load + shift by (x10&0x38)
 * Confidence: low
 * Notes: byte load + shift by (x10&0x38)
 */
static word_t sk_shift_load_350dc4(void)
{
    /* w12=[x11]++; x13=x10&0x38; x12<<=x13 */
    return 0;
}

/* FUN_350de4 @ 0x350de4   (est. sk_indirect_setup2)
 * Body: x16/x17 = load from [x20]
 * Confidence: low
 * Notes: x16/x17 = load from [x20]
 */
static void sk_indirect_setup2_350de4(void)
{
    /* x28=[x20]; x16=x28; x17=x20 */
}

/* FUN_350e04 @ 0x350e04   (est. sk_copy16)
 * Body: ldr q0,[x1]; str q0,[x0] (16-byte copy)
 * Confidence: high
 * Notes: ldr q0,[x1]; str q0,[x0] (16-byte copy)
 */
static void sk_copy16_350e04(und8_t *src, und8_t *dst)
{
    und8_t tmp[16];
    for (int i = 0; i < 16; i++) tmp[i] = src[i];
    for (int i = 0; i < 16; i++) dst[i] = tmp[i];
}

/* FUN_350e24 @ 0x350e24   (est. sk_frame_load2)
 * Body: frame loads
 * Confidence: low
 * Notes: frame loads
 */
static word_t sk_frame_load2_350e24(void)
{
    /* x9=[x29-0x78]; x8=[x9+8]!; x0=[x29-0x58] */
    return 0;
}

/* FUN_350efc @ 0x350efc   (est. sk_frame_ptr_70b)
 * Body: x0 = x29 - 0x70
 * Confidence: low
 * Notes: x0 = x29 - 0x70
 */
static word_t sk_frame_ptr_70b_350efc(void)
{
    /* x3=&0x675c68; x0=x29-0x70 */
    return 0;
}

/* FUN_350f2c @ 0x350f2c   (est. sk_inc_load)
 * Body: pre-increment load of [x24+8]
 * Confidence: low
 * Notes: pre-increment load of [x24+8]
 */
static void sk_inc_load_350f2c(void)
{
    /* x20=x0; x8=x24; x9=[x8+8]! */
}

/* FUN_351124 @ 0x351124   (est. sk_load_word)
 * Body: ldr x0,[x0]
 * Confidence: high
 * Notes: ldr x0,[x0]
 */
static word_t sk_load_word_351124(word_t *p)
{
    return *p;
}

/* FUN_35125c @ 0x35125c   (est. sk_call_27754)
 * Body: pacibsp; bl 0x00027754; retab
 * Confidence: medium
 * Notes: pacibsp; bl 0x00027754; retab
 */
static word_t sk_call_27754_35125c(void)
{
    return sk_00027754(); /* x22=ret */
}

/* FUN_3512a4 @ 0x3512a4   (est. sk_call_310a44)
 * Body: pacibsp; x0=x25; bl 0x00310a44; retab
 * Confidence: medium
 * Notes: pacibsp; x0=x25; bl 0x00310a44; retab
 */
static word_t sk_call_310a44_3512a4(word_t arg)
{
    return sk_00310a44(arg); /* x26=ret, x0=arg */
}

/* FUN_3512d8 @ 0x3512d8   (est. sk_call_310924)
 * Body: pacibsp; x0=x21; bl 0x00310924; retab
 * Confidence: medium
 * Notes: pacibsp; x0=x21; bl 0x00310924; retab
 */
static word_t sk_call_310924_3512d8(word_t arg)
{
    return sk_00310924(arg); /* x9=ret, x0=arg */
}

/* FUN_351348 @ 0x351348   (est. sk_stack_switch)
 * Body: sub sp,x29,#0x50
 * Confidence: low
 * Notes: sub sp,x29,#0x50
 */
static void sk_stack_switch_351348(void)
{
    /* x21=x19; sp=x29-0x50 */
}

/* FUN_351500 @ 0x351500   (est. sk_mux_attr)
 * Body: ubfx x9,x25,#56,#4; tst x25,#0x2000000000000000; csel x3,x8,x9,eq
 * Confidence: low
 * Notes: ubfx x9,x25,#56,#4; tst x25,#0x2000000000000000; csel x3,x8,x9,eq
 */
static word_t sk_mux_attr_351500(word_t v)
{
    /* if (v & 0x2000000000000000) x3=x8 else x3=ubfx(v,56,4) */
    return (v & 0x2000000000000000ull) ? 0 : ((v >> 56) & 0xf);
}

/* FUN_35151c @ 0x35151c   (est. sk_pack_bits)
 * Body: and w8,w8,#0x3f; bfm w8,w0,#0x1a,#0x4 (packs two 5/6-bit fields)
 * Confidence: low
 * Notes: and w8,w8,#0x3f; bfm w8,w0,#0x1a,#0x4 (packs two 5/6-bit fields)
 */
static uint32_t sk_pack_bits_35151c(uint32_t lo, uint32_t hi)
{
    return (lo & 0x3f) | ((hi & 0x1f) << 6);
}

/* FUN_351538 @ 0x351538   (est. sk_sum_or_add)
 * Body: orr w8,w9,w8; add w8,w10,w8; add w0,w8,#1
 * Confidence: low
 * Notes: orr w8,w9,w8; add w8,w10,w8; add w0,w8,#1
 */
static uint32_t sk_sum_or_add_351538(uint32_t w8, uint32_t w9, uint32_t w10)
{
    return w10 + (w9 | w8) + 1;
}

/* FUN_35156c @ 0x35156c   (est. sk_call_277b8)
 * Body: pacibsp; bl 0x000277b8; retab
 * Confidence: medium
 * Notes: pacibsp; bl 0x000277b8; retab
 */
static word_t sk_call_277b8_35156c(void)
{
    return sk_000277b8(); /* x9=ret */
}

/* FUN_351608 @ 0x351608   (est. sk_tail_dispatch)
 * Body: ldr w8,[x22+0x54]; ldr x9,[x22+0x40]; cmp w8,0; cinc x2,x9,eq; bic x0,x24,x23; bic x1,x20,x23; b 0x117cc4
 * Confidence: low
 * Notes: ldr w8,[x22+0x54]; ldr x9,[x22+0x40]; cmp w8,0; cinc x2,x9,eq; bic x0,x24,x23; bic x1,x20,x23; b 0x117cc4
 */
static void sk_tail_dispatch_351608(void)
{
    /* x2=[x22+0x40]+([x22+0x54]==0); x0=x24&~x23; x1=x20&~x23; tail-jump 0x117cc4 */
}

/* FUN_35166c @ 0x35166c   (est. sk_call_310e20)
 * Body: pacibsp; bl 0x00310e20; retab
 * Confidence: medium
 * Notes: pacibsp; bl 0x00310e20; retab
 */
static word_t sk_call_310e20_35166c(void)
{
    return sk_00310e20(); /* x8=ret */
}

/* FUN_351684 @ 0x351684   (est. sk_call_8f6f4)
 * Body: pacibsp; bl 0x0008f6f4; retab
 * Confidence: medium
 * Notes: pacibsp; bl 0x0008f6f4; retab
 */
static word_t sk_call_8f6f4_351684(void)
{
    return sk_0008f6f4(); /* x1=ret */
}

/* FUN_3516cc @ 0x3516cc   (est. sk_pair_zero)
 * Body: mov x0,#0; mov x1,x3
 * Confidence: low
 * Notes: mov x0,#0; mov x1,x3
 */
static und8_t sk_pair_zero_3516cc(void)
{
    /* returns 128-bit {0, x3}: x0=0, x1=x3 */
    return 0;
}

/* FUN_351750 @ 0x351750   (est. sk_call_310924b)
 * Body: pacibsp; x0=x21; bl 0x00310924; retab
 * Confidence: medium
 * Notes: pacibsp; x0=x21; bl 0x00310924; retab
 */
static word_t sk_call_310924b_351750(word_t arg)
{
    return sk_00310924(arg); /* x9=ret, x0=arg */
}

/* FUN_3517b4 @ 0x3517b4   (est. sk_syscall_ret_zero2)
 * Body: x20=x0; x0=0; ret
 * Confidence: medium
 * Notes: x20=x0; x0=0; ret
 */
static word_t sk_syscall_ret_zero2_3517b4(void)
{
    return 0;
}

/* FUN_350db4 @ 0x350db4   (est. sk_syscall_args_2_3)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x2=x22 ; x3=x19
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 * Notes: also x20=x22
 */
static void sk_syscall_args_2_3_350db4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350dd4 @ 0x350dd4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x21=x2 ; x19=x1 ; x22=x0
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350dd4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350df4 @ 0x350df4   (est. sk_syscall_setup_scratch)
 * ABI argument-marshalling shim for syscall/exception dispatch:
 *   x19=x0 ; x20=x1 ; x0=x22
 * (callee-saved save-frame regs -> ABI argument regs; leaf forwarder.)
 * Confidence: medium
 */
static void sk_syscall_setup_scratch_350df4(void)
{
    /* register forwarder only (no stack/local state); see header. */
}

/* FUN_350fcc @ 0x350fcc   (est. sk_struct_copy16)
 * Body: copies 16 bytes from stack [sp+0x40] into struct+0x10
 * Confidence: low
 * Notes: copies 16 bytes from stack [sp+0x40] into struct+0x10
 */
static void sk_struct_copy16_350fcc(und8_t *dst, und8_t *src)
{
    /* ldr q0,[sp+0x40]; str q0,[dst+0x10] ; x20=dst */
    und8_t tmp[16];
    for (int i=0;i<16;i++) tmp[i]=src[i];
    for (int i=0;i<16;i++) dst[0x10+i]=tmp[i];
}

/* FUN_35113c @ 0x35113c   (est. sk_pair_zero_x28)
 * Body: mov x0,#0; mov x1,x28
 * Confidence: low
 * Notes: mov x0,#0; mov x1,x28
 */
static und8_t sk_pair_zero_x28_35113c(void)
{
    /* returns {0, x28}: x0=0, x1=x28 */
    return 0;
}

/* FUN_351244 @ 0x351244   (est. sk_pair_x19_zero)
 * Body: mov x0,x19; mov x1,#0
 * Confidence: low
 * Notes: mov x0,x19; mov x1,#0
 */
static und8_t sk_pair_x19_zero_351244(void)
{
    /* returns {x19, 0}: x0=x19, x1=0 */
    return 0;
}

/* FUN_3512f4 @ 0x3512f4   (est. sk_ret_zero_arg2)
 * Body: mov x0,#0; mov x2,x21
 * Confidence: low
 * Notes: mov x0,#0; mov x2,x21
 */
static word_t sk_ret_zero_arg2_3512f4(void)
{
    /* x0=0; x2=x21 */
    return 0;
}

/* FUN_3514b8 @ 0x3514b8   (est. sk_call_27754_b)
 * Body: pacibsp; bl 0x00027754; retab
 * Confidence: medium
 * Notes: pacibsp; bl 0x00027754; retab
 */
static word_t sk_call_27754_b_3514b8(void)
{
    return sk_00027754(); /* x23=ret */
}
