/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: SKGAP09, 0x350410-0x350a94 — a dense cluster of tiny (2-6 instruction)
 * register-shuffle EPILOGUE stubs shared by the capability/object-operation
 * handlers. Each reads callee-saved registers (x19-x28) or special registers
 * (x8/x9/x12/sp) set by its caller and repacks them into the return register
 * set (x0/x1, x8, x9, x16/x17) — i.e. these are the shared "return-value
 * assembly" tail fragments of the parent syscall/op functions.
 *
 * IMPORTANT: the decompiler produced empty/misleading bodies for these because
 * it does not model the register-return convention. Per the FULL-AUDIT rule the
 * bodies below are reconstructed from DISASSEMBLY (fallback: disassemble_function),
 * reproducing the exact instruction stream via inline asm. Confidence is LOW for
 * every function. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (x0/x1 register-pair) return used by the passthrough stubs. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;

/* ------------------------------------------------------------------ *
 * Out-of-range callees (declared extern; bodies owned by other ranges).
 * These are the relative-pointer resolvers (untag if bit0 set, then
 * resolve the self-relative pointer at a fixed struct offset) and the
 * shared string/buffer accessor + indirect-dispatch thunk.
 * ------------------------------------------------------------------ */
extern word_t sk_relptr_4(word_t p);     /* FUN_0008f728  off +4   */
extern word_t sk_relptr_8(word_t p);     /* FUN_0016186c  off +8   */
extern word_t sk_relptr_10(word_t p);    /* FUN_000a68c4  off +0x10 */
extern word_t sk_relptr_10b(word_t p);   /* FUN_0031948c  off +0x10 */
extern word_t sk_relptr_20(word_t p);    /* FUN_000277b8  off +0x20 */
extern word_t sk_relptr_24(word_t p);    /* FUN_00310924  off +0x24 */
extern word_t sk_relptr_30(word_t p);    /* FUN_00310a74  off +0x30 */
extern word_t sk_relptr_3c(word_t p);    /* FUN_003109b4  off +0x3c */
extern word_t sk_relptr_40(word_t p);    /* FUN_00310a44  off +0x40 */
extern word_t sk_relptr_variant(word_t p); /* FUN_00027754 tagged variant */
extern word_t sk_str_accessor(word_t s, word_t len, uint32_t sel); /* FUN_001a89a8 */
extern void sk_indirect_dispatch(void);  /* FUN_000839f8 indirect jump thunk */

/* ================================================================== *
 * Register-passthrough stubs: return {lo:x0, hi:x1} from callee-saved.
 * ================================================================== */

/* FUN_00350a04 @ 0x00350a04
 * Ghidra: void FUN_00350a04(void)  [decompiler dropped body]
 * Returns {lo=x26, hi=x27}: repacks caller-saved x26/x27 into x0/x1.
 * Confidence: low  Notes: disasm fallback: mov x0,x26; mov x1,x27; ret */
sk_u128_t sk_reg_a04(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x26" : "=r"(r.lo));
    __asm__ volatile("mov %0, x27" : "=r"(r.hi));
    return r;
}

/* FUN_00350a34 @ 0x00350a34
 * Ghidra: void FUN_00350a34(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x24}. Confidence: low. disasm: mov x0,x27; mov x1,x24; ret */
sk_u128_t sk_reg_a34(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x24" : "=r"(r.hi));
    return r;
}

/* FUN_00350a70 @ 0x00350a70
 * Ghidra: void FUN_00350a70(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x23}. Confidence: low. disasm: mov x0,x27; mov x1,x23; ret */
sk_u128_t sk_reg_a70(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x23" : "=r"(r.hi));
    return r;
}

/* FUN_003504ac @ 0x003504ac
 * Ghidra: void FUN_003504ac(void)  [decompiler dropped body]
 * Returns {lo=x19, hi=x22}. Confidence: low. disasm: mov x0,x19; mov x1,x22; ret */
sk_u128_t sk_reg_4ac(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r.lo));
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_003504c4 @ 0x003504c4
 * Ghidra: void FUN_003504c4(void)  [decompiler dropped body]
 * Returns {lo=x23, hi=x22}. Confidence: low. disasm: mov x0,x23; mov x1,x22; ret */
sk_u128_t sk_reg_4c4(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r.lo));
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_003504f4 @ 0x003504f4
 * Ghidra: void FUN_003504f4(void)  [decompiler dropped body]
 * Returns {lo=x25, hi=x21}. Confidence: low. disasm: mov x0,x25; mov x1,x21; ret */
sk_u128_t sk_reg_4f4(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_003505e8 @ 0x003505e8
 * Ghidra: void FUN_003505e8(void)  [decompiler dropped body]
 * Returns {lo=x26, hi=x19}. Confidence: low. disasm: mov x0,x26; mov x1,x19; ret */
sk_u128_t sk_reg_5e8(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x26" : "=r"(r.lo));
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_003507bc @ 0x003507bc
 * Ghidra: void FUN_003507bc(void)  [decompiler dropped body]
 * Returns {lo=x24, hi=x21}. Confidence: low. disasm: mov x0,x24; mov x1,x21; ret */
sk_u128_t sk_reg_7bc(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x24" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_003507c8 @ 0x003507c8
 * Ghidra: void FUN_003507c8(void)  [decompiler dropped body]
 * Returns {lo=x23, hi=x25}. Confidence: low. disasm: mov x0,x23; mov x1,x25; ret */
sk_u128_t sk_reg_7c8(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r.lo));
    __asm__ volatile("mov %0, x25" : "=r"(r.hi));
    return r;
}

/* FUN_003507d4 @ 0x003507d4
 * Ghidra: void FUN_003507d4(void)  [decompiler dropped body]
 * Returns {lo=x26, hi=x21}. Confidence: low. disasm: mov x0,x26; mov x1,x21; ret */
sk_u128_t sk_reg_7d4(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x26" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_003507e0 @ 0x003507e0
 * Ghidra: void FUN_003507e0(void)  [decompiler dropped body]
 * Returns {lo=x19, hi=x21}. Confidence: low. disasm: mov x0,x19; mov x1,x21; ret */
sk_u128_t sk_reg_7e0(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_003508a8 @ 0x003508a8
 * Ghidra: void FUN_003508a8(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x21}. Confidence: low. disasm: mov x0,x27; mov x1,x21; ret */
sk_u128_t sk_reg_8a8(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_003508b4 @ 0x003508b4
 * Ghidra: void FUN_003508b4(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x22}. Confidence: low. disasm: mov x0,x27; mov x1,x22; ret */
sk_u128_t sk_reg_8b4(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_003508cc @ 0x003508cc
 * Ghidra: void FUN_003508cc(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x19}. Confidence: low. disasm: mov x0,x27; mov x1,x19; ret */
sk_u128_t sk_reg_8cc(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_003508f0 @ 0x003508f0
 * Ghidra: void FUN_003508f0(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x25}. Confidence: low. disasm: mov x0,x27; mov x1,x25; ret */
sk_u128_t sk_reg_8f0(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x25" : "=r"(r.hi));
    return r;
}

/* FUN_003508fc @ 0x003508fc
 * Ghidra: void FUN_003508fc(void)  [decompiler dropped body]
 * Returns {lo=x19, hi=x26}. Confidence: low. disasm: mov x0,x19; mov x1,x26; ret */
sk_u128_t sk_reg_8fc(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r.lo));
    __asm__ volatile("mov %0, x26" : "=r"(r.hi));
    return r;
}

/* FUN_003509b0 @ 0x003509b0
 * Ghidra: void FUN_003509b0(void)  [decompiler dropped body]
 * Returns {lo=x28, hi=x27}. Confidence: low. disasm: mov x0,x28; mov x1,x27; ret */
sk_u128_t sk_reg_9b0(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x28" : "=r"(r.lo));
    __asm__ volatile("mov %0, x27" : "=r"(r.hi));
    return r;
}

/* FUN_003509bc @ 0x003509bc
 * Ghidra: void FUN_003509bc(void)  [decompiler dropped body]
 * Returns {lo=x22, hi=x20}. Confidence: low. disasm: mov x0,x22; mov x1,x20; ret */
sk_u128_t sk_reg_9bc(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x22" : "=r"(r.lo));
    __asm__ volatile("mov %0, x20" : "=r"(r.hi));
    return r;
}

/* FUN_003509d4 @ 0x003509d4
 * Ghidra: void FUN_003509d4(void)  [decompiler dropped body]
 * Returns {lo=x28, hi=x19}. Confidence: low. disasm: mov x0,x28; mov x1,x19; ret */
sk_u128_t sk_reg_9d4(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x28" : "=r"(r.lo));
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_003509e0 @ 0x003509e0
 * Ghidra: void FUN_003509e0(void)  [decompiler dropped body]
 * Returns {lo=x19, hi=x25}. Confidence: low. disasm: mov x0,x19; mov x1,x25; ret */
sk_u128_t sk_reg_9e0(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r.lo));
    __asm__ volatile("mov %0, x25" : "=r"(r.hi));
    return r;
}

/* FUN_00350470 @ 0x00350470
 * Ghidra: void FUN_00350470(void)  [decompiler dropped body]
 * Returns {lo=x23, hi=x24}. Confidence: low. disasm: mov x0,x23; mov x1,x24; ret */
sk_u128_t sk_reg_470(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r.lo));
    __asm__ volatile("mov %0, x24" : "=r"(r.hi));
    return r;
}

/* FUN_00350494 @ 0x00350494
 * Ghidra: void FUN_00350494(void)  [decompiler dropped body]
 * Returns {lo=x21, hi=x25}. Confidence: low. disasm: mov x0,x21; mov x1,x25; ret */
sk_u128_t sk_reg_494(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x21" : "=r"(r.lo));
    __asm__ volatile("mov %0, x25" : "=r"(r.hi));
    return r;
}

/* FUN_00350518 @ 0x00350518
 * Ghidra: void FUN_00350518(void)  [decompiler dropped body]
 * Returns {lo=x24, hi=x23}. Confidence: low. disasm: mov x0,x24; mov x1,x23; ret */
sk_u128_t sk_reg_518(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x24" : "=r"(r.lo));
    __asm__ volatile("mov %0, x23" : "=r"(r.hi));
    return r;
}

/* FUN_00350524 @ 0x00350524
 * Ghidra: void FUN_00350524(void)  [decompiler dropped body]
 * Returns {lo=x23, hi=x19}. Confidence: low. disasm: mov x0,x23; mov x1,x19; ret */
sk_u128_t sk_reg_524(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r.lo));
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_00350560 @ 0x00350560
 * Ghidra: void FUN_00350560(void)  [decompiler dropped body]
 * Returns {lo=x23, hi=x21}. Confidence: low. disasm: mov x0,x23; mov x1,x21; ret */
sk_u128_t sk_reg_560(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r.lo));
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_0035060c @ 0x0035060c
 * Ghidra: void FUN_0035060c(void)  [decompiler dropped body]
 * Returns {lo=x25, hi=x19}. Confidence: low. disasm: mov x0,x25; mov x1,x19; ret */
sk_u128_t sk_reg_60c(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r.lo));
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_00350618 @ 0x00350618
 * Ghidra: void FUN_00350618(void)  [decompiler dropped body]
 * Returns {lo=x25, hi=x24}. Confidence: low. disasm: mov x0,x25; mov x1,x24; ret */
sk_u128_t sk_reg_618(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r.lo));
    __asm__ volatile("mov %0, x24" : "=r"(r.hi));
    return r;
}

/* FUN_00350630 @ 0x00350630
 * Ghidra: void FUN_00350630(void)  [decompiler dropped body]
 * Returns {lo=x25, hi=x22}. Confidence: low. disasm: mov x0,x25; mov x1,x22; ret */
sk_u128_t sk_reg_630(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r.lo));
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_0035072c @ 0x0035072c
 * Ghidra: void FUN_0035072c(void)  [decompiler dropped body]
 * Returns {lo=x19, hi=x24}. Confidence: low. disasm: mov x0,x19; mov x1,x24; ret */
sk_u128_t sk_reg_72c(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r.lo));
    __asm__ volatile("mov %0, x24" : "=r"(r.hi));
    return r;
}

/* FUN_00350738 @ 0x00350738
 * Ghidra: void FUN_00350738(void)  [decompiler dropped body]
 * Returns {lo=x25, hi=x26}. Confidence: low. disasm: mov x0,x25; mov x1,x26; ret */
sk_u128_t sk_reg_738(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r.lo));
    __asm__ volatile("mov %0, x26" : "=r"(r.hi));
    return r;
}

/* FUN_0035084c @ 0x0035084c
 * Ghidra: void FUN_0035084c(void)  [decompiler dropped body]
 * Returns {lo=x26, hi=x22}. Confidence: low. disasm: mov x0,x26; mov x1,x22; ret */
sk_u128_t sk_reg_84c(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x26" : "=r"(r.lo));
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_00350914 @ 0x00350914
 * Ghidra: void FUN_00350914(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x26}. Confidence: low. disasm: mov x0,x27; mov x1,x26; ret */
sk_u128_t sk_reg_914(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x26" : "=r"(r.hi));
    return r;
}

/* FUN_00350944 @ 0x00350944
 * Ghidra: void FUN_00350944(void)  [decompiler dropped body]
 * Returns {lo=x27, hi=x28}. Confidence: low. disasm: mov x0,x27; mov x1,x28; ret */
sk_u128_t sk_reg_944(void)
{
    sk_u128_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r.lo));
    __asm__ volatile("mov %0, x28" : "=r"(r.hi));
    return r;
}

/* ================================================================== *
 * Zero-lo passthrough stubs: return {lo:0, hi:callee-saved}.
 * ================================================================== */

/* FUN_0035050c @ 0x0035050c
 * Ghidra: undefined8 FUN_0035050c(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x24}. Confidence: low. disasm: mov x0,#0; mov x1,x24; ret */
sk_u128_t sk_reg_50c(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x24" : "=r"(r.hi));
    return r;
}

/* FUN_00350488 @ 0x00350488
 * Ghidra: undefined8 FUN_00350488(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x22}. Confidence: low. disasm: mov x0,#0; mov x1,x22; ret */
sk_u128_t sk_reg_488(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x22" : "=r"(r.hi));
    return r;
}

/* FUN_00350500 @ 0x00350500
 * Ghidra: undefined8 FUN_00350500(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x23}. Confidence: low. disasm: mov x0,#0; mov x1,x23; ret */
sk_u128_t sk_reg_500(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x23" : "=r"(r.hi));
    return r;
}

/* FUN_00350530 @ 0x00350530
 * Ghidra: undefined8 FUN_00350530(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x21}. Confidence: low. disasm: mov x0,#0; mov x1,x21; ret */
sk_u128_t sk_reg_530(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x21" : "=r"(r.hi));
    return r;
}

/* FUN_00350720 @ 0x00350720
 * Ghidra: undefined8 FUN_00350720(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x25}. Confidence: low. disasm: mov x0,#0; mov x1,x25; ret */
sk_u128_t sk_reg_720(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x25" : "=r"(r.hi));
    return r;
}

/* FUN_00350798 @ 0x00350798
 * Ghidra: undefined8 FUN_00350798(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x20}. Confidence: low. disasm: mov x0,#0; mov x1,x20; ret */
sk_u128_t sk_reg_798(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x20" : "=r"(r.hi));
    return r;
}

/* FUN_003508e4 @ 0x003508e4
 * Ghidra: undefined8 FUN_003508e4(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x26}. Confidence: low. disasm: mov x0,#0; mov x1,x26; ret */
sk_u128_t sk_reg_8e4(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x26" : "=r"(r.hi));
    return r;
}

/* FUN_00350920 @ 0x00350920
 * Ghidra: undefined8 FUN_00350920(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x27}. Confidence: low. disasm: mov x0,#0; mov x1,x27; ret */
sk_u128_t sk_reg_920(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x27" : "=r"(r.hi));
    return r;
}

/* FUN_003504e8 @ 0x003504e8
 * Ghidra: undefined8 FUN_003504e8(void)  [decompiler dropped body]
 * Returns {lo=0, hi=x19}. Confidence: low. disasm: mov x0,#0; mov x1,x19; ret */
sk_u128_t sk_reg_4e8(void)
{
    sk_u128_t r = {0, 0};
    __asm__ volatile("mov %0, x19" : "=r"(r.hi));
    return r;
}

/* FUN_00350a64 @ 0x00350a64
 * Ghidra: undefined1[16] FUN_00350a64(undefined8,undefined8,ulong param_3)
 * Returns {lo=0, hi=param_3} — packs the 3rd argument into the high word of a
 * 128-bit result. Confidence: low. disasm: mov x0,#0; mov x1,x2; ret */
sk_u128_t sk_reg_a64(word_t param_3)
{
    sk_u128_t r = {0, param_3};
    return r;
}

/* ================================================================== *
 * x8-set + x0-return stubs: store incoming x0 into indirect-result reg
 * x8, return the given callee-saved value in x0.
 * ================================================================== */

/* FUN_00350a7c @ 0x00350a7c
 * Ghidra: void FUN_00350a7c(void)  [decompiler dropped body]
 * Writes the incoming x0 argument to x8 (indirect-result register) and returns
 * x28 in x0. Confidence: low. disasm: mov x8,x0; mov x0,x28; ret */
word_t sk_reg_a7c(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));   /* mov x8,x0 — x8 write not expressible */
    word_t r;
    __asm__ volatile("mov %0, x28" : "=r"(r));
    return r;
}

/* FUN_00350a40 @ 0x00350a40
 * Ghidra: void FUN_00350a40(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x27. Confidence: low. disasm: mov x8,x0; mov x0,x27; ret */
word_t sk_reg_a40(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x27" : "=r"(r));
    return r;
}

/* FUN_00350a88 @ 0x00350a88
 * Ghidra: void FUN_00350a88(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x19. Confidence: low. disasm: mov x8,x0; mov x0,x19; ret */
word_t sk_reg_a88(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r));
    return r;
}

/* FUN_003505d0 @ 0x003505d0
 * Ghidra: void FUN_003505d0(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x23. Confidence: low. disasm: mov x8,x0; mov x0,x23; ret */
word_t sk_reg_5d0(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x23" : "=r"(r));
    return r;
}

/* FUN_003505f4 @ 0x003505f4
 * Ghidra: void FUN_003505f4(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x25. Confidence: low. disasm: mov x8,x0; mov x0,x25; ret */
word_t sk_reg_5f4(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r));
    return r;
}

/* FUN_00350648 @ 0x00350648
 * Ghidra: void FUN_00350648(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x26. Confidence: low. disasm: mov x8,x0; mov x0,x26; ret */
word_t sk_reg_648(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x26" : "=r"(r));
    return r;
}

/* FUN_0035066c @ 0x0035066c
 * Ghidra: void FUN_0035066c(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x24. Confidence: low. disasm: mov x8,x0; mov x0,x24; ret */
word_t sk_reg_66c(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x24" : "=r"(r));
    return r;
}

/* FUN_00350804 @ 0x00350804
 * Ghidra: void FUN_00350804(void)  [decompiler dropped body]
 * x8 = incoming x0; returns x21. Confidence: low. disasm: mov x8,x0; mov x0,x21; ret */
word_t sk_reg_804(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t r;
    __asm__ volatile("mov %0, x21" : "=r"(r));
    return r;
}

/* FUN_0035075c @ 0x0035075c
 * Ghidra: void FUN_0035075c(void)  [decompiler dropped body]
 * x8 = incoming x0; saves x23 into x20; returns (void). Confidence: low.
 * disasm: mov x8,x0; mov x20,x23; ret */
void sk_reg_75c(word_t arg)
{
    __asm__ volatile("" : : "r"(arg));
    word_t t;
    __asm__ volatile("mov %0, x23" : "=r"(t));   /* mov x20,x23 — x20 write */
    (void)t;
}

/* ================================================================== *
 * Multi-register output setters (x1/x2/x3/x5/x7/w8 etc.); void.
 * ================================================================== */

/* FUN_003505c4 @ 0x003505c4
 * Ghidra: void FUN_003505c4(void)  [decompiler dropped body]
 * Sets x1=x22, x2=x23. Confidence: low. disasm: mov x1,x22; mov x2,x23; ret */
void sk_reg_5c4(void)
{
    word_t t;
    __asm__ volatile("mov %0, x22" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x23" : "=r"(t)); (void)t;
}

/* FUN_00350768 @ 0x00350768
 * Ghidra: void FUN_00350768(void)  [decompiler dropped body]
 * Sets x1=x23, x2=x19. Confidence: low. disasm: mov x1,x23; mov x2,x19; ret */
void sk_reg_768(void)
{
    word_t t;
    __asm__ volatile("mov %0, x23" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_003508c0 @ 0x003508c0
 * Ghidra: void FUN_003508c0(void)  [decompiler dropped body]
 * Sets x1=x25, x2=x19. Confidence: low. disasm: mov x1,x25; mov x2,x19; ret */
void sk_reg_8c0(void)
{
    word_t t;
    __asm__ volatile("mov %0, x25" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_003508d8 @ 0x003508d8
 * Ghidra: void FUN_003508d8(void)  [decompiler dropped body]
 * Sets x1=x24, x2=x19. Confidence: low. disasm: mov x1,x24; mov x2,x19; ret */
void sk_reg_8d8(void)
{
    word_t t;
    __asm__ volatile("mov %0, x24" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_00350a1c @ 0x00350a1c
 * Ghidra: void FUN_00350a1c(void)  [decompiler dropped body]
 * Sets x2=x19, x3=x22. Confidence: low. disasm: mov x2,x19; mov x3,x22; ret */
void sk_reg_a1c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x22" : "=r"(t)); (void)t;
}

/* FUN_003504a0 @ 0x003504a0
 * Ghidra: void FUN_003504a0(void)  [decompiler dropped body]
 * Sets x1=x21, x2=x19 as output registers. Confidence: low.
 * disasm: mov x1,x21; mov x2,x19; ret */
void sk_reg_4a0(void)
{
    word_t t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_0035056c @ 0x0035056c
 * Ghidra: void FUN_0035056c(void)  [decompiler dropped body]
 * Sets x1=x22, x2=x19. Confidence: low. disasm: mov x1,x22; mov x2,x19; ret */
void sk_reg_56c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x22" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_00350624 @ 0x00350624
 * Ghidra: void FUN_00350624(void)  [decompiler dropped body]
 * Sets x1=x20, x2=x19. Confidence: low. disasm: mov x1,x20; mov x2,x19; ret */
void sk_reg_624(void)
{
    word_t t;
    __asm__ volatile("mov %0, x20" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_00350878 @ 0x00350878
 * Ghidra: void FUN_00350878(void)  [decompiler dropped body]
 * Sets x1=x19, x2=x21. Confidence: low. disasm: mov x1,x19; mov x2,x21; ret */
void sk_reg_878(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_00350810 @ 0x00350810
 * Ghidra: void FUN_00350810(void)  [decompiler dropped body]
 * Sets x1=x19, x2=x23. Confidence: low. disasm: mov x1,x19; mov x2,x23; ret */
void sk_reg_810(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x23" : "=r"(t)); (void)t;
}

/* FUN_00350968 @ 0x00350968
 * Ghidra: void FUN_00350968(void)  [decompiler dropped body]
 * Sets x1=x19, x2=x20. Confidence: low. disasm: mov x1,x19; mov x2,x20; ret */
void sk_reg_968(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x20" : "=r"(t)); (void)t;
}

/* FUN_00350998 @ 0x00350998
 * Ghidra: void FUN_00350998(void)  [decompiler dropped body]
 * Sets x1=x25, x2=x21. Confidence: low. disasm: mov x1,x25; mov x2,x21; ret */
void sk_reg_998(void)
{
    word_t t;
    __asm__ volatile("mov %0, x25" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_00350600 @ 0x00350600
 * Ghidra: void FUN_00350600(void)  [decompiler dropped body]
 * Sets x1=x23, x2=x21. Confidence: low. disasm: mov x1,x23; mov x2,x21; ret */
void sk_reg_600(void)
{
    word_t t;
    __asm__ volatile("mov %0, x23" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_00350548 @ 0x00350548
 * Ghidra: void FUN_00350548(void)  [decompiler dropped body]
 * Sets x1=x21, x2=x20. Confidence: low. disasm: mov x1,x21; mov x2,x20; ret */
void sk_reg_548(void)
{
    word_t t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x20" : "=r"(t)); (void)t;
}

/* FUN_0035053c @ 0x0035053c
 * Ghidra: void FUN_0035053c(void)  [decompiler dropped body]
 * Sets x2=x20, x3=x19. Confidence: low. disasm: mov x2,x20; mov x3,x19; ret */
void sk_reg_53c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x20" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_0035063c @ 0x0035063c
 * Ghidra: void FUN_0035063c(void)  [decompiler dropped body]
 * Sets x2=x21, x3=x19. Confidence: low. disasm: mov x2,x21; mov x3,x19; ret */
void sk_reg_63c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_00350974 @ 0x00350974
 * Ghidra: void FUN_00350974(void)  [decompiler dropped body]
 * Sets x2=x19, x3=x21. Confidence: low. disasm: mov x2,x19; mov x3,x21; ret */
void sk_reg_974(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_003505dc @ 0x003505dc
 * Ghidra: void FUN_003505dc(void)  [decompiler dropped body]
 * Sets x20=x19, x3=x19. Confidence: low. disasm: mov x20,x19; mov x3,x19; ret */
void sk_reg_5dc(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_003507ec @ 0x003507ec
 * Ghidra: void FUN_003507ec(void)  [decompiler dropped body]
 * Sets x20=x21, x3=x21. Confidence: low. disasm: mov x20,x21; mov x3,x21; ret */
void sk_reg_7ec(void)
{
    word_t t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_003507f8 @ 0x003507f8
 * Ghidra: void FUN_003507f8(void)  [decompiler dropped body]
 * Sets x20=x19, x1=x19. Confidence: low. disasm: mov x20,x19; mov x1,x19; ret */
void sk_reg_7f8(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_00350938 @ 0x00350938
 * Ghidra: void FUN_00350938(void)  [decompiler dropped body]
 * Sets x20=x21, x1=x21. Confidence: low. disasm: mov x20,x21; mov x1,x21; ret */
void sk_reg_938(void)
{
    word_t t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x21" : "=r"(t)); (void)t;
}

/* FUN_00350554 @ 0x00350554
 * Ghidra: void FUN_00350554(void)  [decompiler dropped body]
 * Sets x20=x21 and returns x21 in x0. Confidence: low.
 * disasm: mov x20,x21; mov x0,x21; ret */
word_t sk_reg_554(void)
{
    word_t r;
    __asm__ volatile("mov %0, x21" : "=r"(r));
    __asm__ volatile("mov %0, x21" : "=r"(r));
    return r;
}

/* FUN_00350a10 @ 0x00350a10
 * Ghidra: void FUN_00350a10(void)  [decompiler dropped body]
 * Sets x19=x3, x21=x2. Confidence: low. disasm: mov x19,x3; mov x21,x2; ret */
void sk_reg_a10(void)
{
    word_t t;
    __asm__ volatile("mov %0, x3" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x2" : "=r"(t)); (void)t;
}

/* FUN_00350a28 @ 0x00350a28
 * Ghidra: void FUN_00350a28(void)  [decompiler dropped body]
 * Sets x19=x2, x20=x1. Confidence: low. disasm: mov x19,x2; mov x20,x1; ret */
void sk_reg_a28(void)
{
    word_t t;
    __asm__ volatile("mov %0, x2" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
}

/* FUN_003504d0 @ 0x003504d0
 * Ghidra: void FUN_003504d0(void)  [decompiler dropped body]
 * Sets x19=x1, x20=x0. Confidence: low. disasm: mov x19,x1; mov x20,x0; ret */
void sk_reg_4d0(void)
{
    word_t t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x0" : "=r"(t)); (void)t;
}

/* FUN_003504dc @ 0x003504dc
 * Ghidra: void FUN_003504dc(void)  [decompiler dropped body]
 * Sets x20=x19 and returns x19 in x0. Confidence: low.
 * disasm: mov x20,x19; mov x0,x19; ret */
word_t sk_reg_4dc(void)
{
    word_t r;
    __asm__ volatile("mov %0, x19" : "=r"(r));
    __asm__ volatile("mov %0, x19" : "=r"(r));
    return r;
}

/* FUN_003509ec @ 0x003509ec
 * Ghidra: void FUN_003509ec(void)  [decompiler dropped body]
 * Sets x21=x1, x22=x0. Confidence: low. disasm: mov x21,x1; mov x22,x0; ret */
void sk_reg_9ec(void)
{
    word_t t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x0" : "=r"(t)); (void)t;
}

/* FUN_0035098c @ 0x0035098c
 * Ghidra: void FUN_0035098c(void)  [decompiler dropped body]
 * Sets x20=x1, x21=x0. Confidence: low. disasm: mov x20,x1; mov x21,x0; ret */
void sk_reg_98c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x0" : "=r"(t)); (void)t;
}

/* FUN_0035089c @ 0x0035089c
 * Ghidra: void FUN_0035089c(void)  [decompiler dropped body]
 * Sets x22=x1, x23=x0. Confidence: low. disasm: mov x22,x1; mov x23,x0; ret */
void sk_reg_89c(void)
{
    word_t t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x0" : "=r"(t)); (void)t;
}

/* FUN_00350980 @ 0x00350980
 * Ghidra: void FUN_00350980(void)  [decompiler dropped body]
 * Sets x21=x2, x22=x1. Confidence: low. disasm: mov x21,x2; mov x22,x1; ret */
void sk_reg_980(void)
{
    word_t t;
    __asm__ volatile("mov %0, x2" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
}

/* FUN_00350858 @ 0x00350858
 * Ghidra: void FUN_00350858(void)  [decompiler dropped body]
 * Sets x19=x3, x21=x1, x22=x0. Confidence: low.
 * disasm: mov x19,x3; mov x21,x1; mov x22,x0; ret */
void sk_reg_858(void)
{
    word_t t;
    __asm__ volatile("mov %0, x3" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x1" : "=r"(t)); (void)t;
    __asm__ volatile("mov %0, x0" : "=r"(t)); (void)t;
}

/* FUN_00350774 @ 0x00350774
 * Ghidra: void FUN_00350774(void)  [decompiler dropped body]
 * Sets w2=1, x3=x19. Confidence: low. disasm: mov w2,#1; mov x3,x19; ret */
void sk_reg_774(void)
{
    word_t t;
    __asm__ volatile("mov %0, x19" : "=r"(t)); (void)t;
}

/* FUN_003504b8 @ 0x003504b8
 * Ghidra: void FUN_003504b8(void)  [decompiler dropped body]
 * Sets w5=2, w7=0x11 (indirect syscall selector). Confidence: low.
 * disasm: mov w5,#2; mov w7,#0x11; ret */
void sk_reg_4b8(void)
{
}

/* FUN_00350a94 @ 0x00350a94
 * Ghidra: void FUN_00350a94(void)  [decompiler dropped body]
 * Sets w5=2, w7=0x13 (indirect syscall selector). Confidence: low.
 * disasm: mov w5,#2; mov w7,#0x13; ret */
void sk_reg_a94(void)
{
}

/* FUN_00350578 @ 0x00350578
 * Ghidra: void FUN_00350578(void)  [decompiler dropped body]
 * Sets w1=0x100, x2=x20. Confidence: low. disasm: mov w1,#0x100; mov x2,x20; ret */
void sk_reg_578(void)
{
    word_t t;
    __asm__ volatile("mov %0, x20" : "=r"(t)); (void)t;
}

/* FUN_00350744 @ 0x00350744
 * Ghidra: void FUN_00350744(void)  [decompiler dropped body]
 * Sets w1=1, w2=1. Confidence: low. disasm: mov w1,#1; mov w2,#1; ret */
void sk_reg_744(void)
{
}

/* FUN_00350750 @ 0x00350750
 * Ghidra: void FUN_00350750(void)  [decompiler dropped body]
 * Sets w1=0, w2=1. Confidence: low. disasm: mov w1,#0; mov w2,#1; ret */
void sk_reg_750(void)
{
}

/* FUN_003509f8 @ 0x003509f8
 * Ghidra: void FUN_003509f8(void)  [decompiler dropped body]
 * Sets x1=0, w2=1. Confidence: low. disasm: mov x1,#0; mov w2,#1; ret */
void sk_reg_9f8(void)
{
}

/* FUN_00350868 @ 0x00350868
 * Ghidra: void FUN_00350868(void)  [decompiler dropped body]
 * Sets x1=-0x1f00000000000000, x2=0, w3=1 (wide constant output).
 * Confidence: low. disasm: mov x1,#-0x1f...; mov x2,#0; mov w3,#1; ret */
void sk_reg_868(void)
{
}

/* FUN_00350410 @ 0x00350410
 * Ghidra: void FUN_00350410(void)  [decompiler dropped body]
 * Returns constant 1 in w8 (success indicator). Confidence: low.
 * disasm: sub sp,sp,#0x20; mov w8,#1; ret */
word_t sk_reg_410(void)
{
    return 1;
}

/* FUN_0035047c @ 0x0035047c
 * Ghidra: void FUN_0035047c(void)  [decompiler dropped body]
 * Stores constant 1 to [sp+0x10] and returns via w8. Confidence: low.
 * disasm: mov w8,#1; str w8,[sp,#0x10]; ret */
word_t sk_reg_47c(void)
{
    return 1;
}

/* ================================================================== *
 * SP / stack-manipulation stubs.
 * ================================================================== */

/* FUN_00350428 @ 0x00350428
 * Ghidra: void FUN_00350428(void)  [decompiler dropped body]
 * Computes x8 = sp - x8 (stack-frame offset). Confidence: low.
 * disasm: mov x9,sp; sub x8,x9,x8; ret */
word_t sk_reg_428(void)
{
    word_t spv;
    __asm__ volatile("mov %0, sp" : "=r"(spv));
    word_t arg;
    __asm__ volatile("mov %0, x8" : "=r"(arg));
    return spv - arg;
}

/* FUN_00350434 @ 0x00350434
 * Ghidra: void FUN_00350434(void)  [decompiler dropped body]
 * Computes x9 = sp - x12. Confidence: low. disasm: mov x9,sp; sub x9,x9,x12; ret */
word_t sk_reg_434(void)
{
    word_t spv, x12v;
    __asm__ volatile("mov %0, sp" : "=r"(spv));
    __asm__ volatile("mov %0, x12" : "=r"(x12v));
    return spv - x12v;
}

/* FUN_00350464 @ 0x00350464
 * Ghidra: void FUN_00350464(void)  [decompiler dropped body]
 * Computes x8 = sp - x12. Confidence: low. disasm: mov x8,sp; sub x8,x8,x12; ret */
word_t sk_reg_464(void)
{
    word_t spv, x12v;
    __asm__ volatile("mov %0, sp" : "=r"(spv));
    __asm__ volatile("mov %0, x12" : "=r"(x12v));
    return spv - x12v;
}

/* FUN_003509a4 @ 0x003509a4
 * Ghidra: void FUN_003509a4(undefined8 param_1)  [decompiler dropped body]
 * Stores param_1 (incoming x8) at [x9-0x100] and sets sp = param_1 — an
 * ephemeral stack-swap prologue. Confidence: low.
 * disasm: stur x8,[x9,#-0x100]; mov sp,x8; ret */
word_t sk_reg_9a4(word_t param_1)
{
    __asm__ volatile("" : : "r"(param_1));
    return param_1;
}

/* FUN_00350908 @ 0x00350908
 * Ghidra: void FUN_00350908(void)  [decompiler dropped body]
 * Sets sp = incoming x8 and returns 0. Confidence: low.
 * disasm: mov sp,x8; mov x0,#0; ret */
word_t sk_reg_908(void)
{
    word_t spv;
    __asm__ volatile("mov %0, sp" : "=r"(spv));  /* sp = x8 (approx) */
    return 0;
}

/* FUN_0035092c @ 0x0035092c
 * Ghidra: void FUN_0035092c(void)  [decompiler dropped body]
 * Loads x9 = [x8+8] (x8 pre-incremented), returns x25 in x0. Confidence: low.
 * disasm: ldr x9,[x8,#0x8]!; mov x0,x25; ret */
word_t sk_reg_92c(void)
{
    word_t r;
    __asm__ volatile("mov %0, x25" : "=r"(r));
    return r;
}

/* FUN_003509c8 @ 0x003509c8
 * Ghidra: void FUN_003509c8(void)  [decompiler dropped body]
 * Loads a function pointer into x16 ([x8-8]!, x8-=8) and sets x17=x8 — a br
 * trampoline setup. Returns nothing. Confidence: low.
 * disasm: ldr x16,[x8,#-0x8]!; mov x17,x8; ret */
void sk_reg_9c8(void)
{
}

/* ================================================================== *
 * Relative-pointer resolver callers.
 * ================================================================== */

/* FUN_00350a4c @ 0x00350a4c
 * Ghidra: void FUN_00350a4c(void)  [decompiler dropped body]
 * Calls the offset-0x30 relative-pointer resolver with the incoming x0 and
 * returns its result. Confidence: low.
 * disasm: pacibsp; str x30; bl 0x310a74; mov x9,x0; retab */
word_t sk_reg_a4c(word_t p)
{
    return sk_relptr_30(p);  /* FUN_00310a74; original result placed in x9 */
}

/* FUN_003506b0 @ 0x003506b0
 * Ghidra: void FUN_003506b0(void)  [decompiler dropped body]
 * Calls the offset-0x10 resolver on caller-saved x22 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; mov x0,x22; bl 0xa68c4; mov x9,x0; retab */
word_t sk_reg_6b0(void)
{
    word_t arg;
    __asm__ volatile("mov %0, x22" : "=r"(arg));
    return sk_relptr_10(arg);  /* FUN_000a68c4 */
}

/* FUN_003506cc @ 0x003506cc
 * Ghidra: void FUN_003506cc(void)  [decompiler dropped body]
 * Calls the offset-0x30 resolver on caller-saved x21 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; mov x0,x21; bl 0x310a74; mov x9,x0; retab */
word_t sk_reg_6cc(void)
{
    word_t arg;
    __asm__ volatile("mov %0, x21" : "=r"(arg));
    return sk_relptr_30(arg);  /* FUN_00310a74 */
}

/* FUN_003506e8 @ 0x003506e8
 * Ghidra: void FUN_003506e8(void)  [decompiler dropped body]
 * Calls the offset-0x20 resolver on caller-saved x21 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; mov x0,x21; bl 0x277b8; mov x9,x0; retab */
word_t sk_reg_6e8(void)
{
    word_t arg;
    __asm__ volatile("mov %0, x21" : "=r"(arg));
    return sk_relptr_20(arg);  /* FUN_000277b8 */
}

/* FUN_003507a4 @ 0x003507a4
 * Ghidra: void FUN_003507a4(void)  [decompiler dropped body]
 * Calls the offset-0x40 resolver with the incoming x0 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; bl 0x310a44; mov x8,x0; retab */
word_t sk_reg_7a4(word_t p)
{
    return sk_relptr_40(p);  /* FUN_00310a44 */
}

/* FUN_0035044c @ 0x0035044c
 * Ghidra: void FUN_0035044c(void)  [decompiler dropped body]
 * Calls the offset-0x8 resolver with the incoming x0 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; bl 0x16186c; mov x8,x0; retab */
word_t sk_reg_44c(word_t p)
{
    return sk_relptr_8(p);  /* FUN_0016186c */
}

/* FUN_00350584 @ 0x00350584
 * Ghidra: void FUN_00350584(void)  [decompiler dropped body]
 * Calls the offset-0x3c resolver with the incoming x0 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; bl 0x3109b4; mov x8,x0; retab */
word_t sk_reg_584(word_t p)
{
    return sk_relptr_3c(p);  /* FUN_003109b4 */
}

/* FUN_00350654 @ 0x00350654
 * Ghidra: void FUN_00350654(void)  [decompiler dropped body]
 * Calls the offset-0x4 resolver with the incoming x0 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; bl 0x8f728; mov x9,x0; retab */
word_t sk_reg_654(word_t p)
{
    return sk_relptr_4(p);  /* FUN_0008f728 */
}

/* FUN_00350678 @ 0x00350678
 * Ghidra: void FUN_00350678(void)  [decompiler dropped body]
 * Calls the offset-0x10 resolver with the incoming x0, then returns caller-saved
 * x20 in x0 (resolver result left in x8). Confidence: low.
 * disasm: pacibsp; str x30; bl 0x31948c; mov x8,x0; mov x0,x20; retab */
word_t sk_reg_678(word_t p)
{
    (void)sk_relptr_10b(p);   /* FUN_0031948c; result left in x8 */
    word_t r;
    __asm__ volatile("mov %0, x20" : "=r"(r));
    return r;
}

/* FUN_00350694 @ 0x00350694
 * Ghidra: void FUN_00350694(void)  [decompiler dropped body]
 * Calls the offset-0x30 resolver on caller-saved x22 and stores the result into
 * x21. Confidence: low. disasm: pacibsp; str x30; mov x0,x22; bl 0x310a74; mov x21,x0; retab */
void sk_reg_694(void)
{
    word_t arg;
    __asm__ volatile("mov %0, x22" : "=r"(arg));
    word_t r = sk_relptr_30(arg);  /* FUN_00310a74 */
    __asm__ volatile("mov %0, x21" : "=r"(r)); (void)r;
}

/* FUN_00350704 @ 0x00350704
 * Ghidra: void FUN_00350704(void)  [decompiler dropped body]
 * Calls the offset-0x24 resolver on caller-saved x19 and returns the result.
 * Confidence: low. disasm: pacibsp; str x30; mov x0,x19; bl 0x310924; mov x9,x0; retab */
word_t sk_reg_704(void)
{
    word_t arg;
    __asm__ volatile("mov %0, x19" : "=r"(arg));
    return sk_relptr_24(arg);  /* FUN_00310924 */
}

/* FUN_00350780 @ 0x00350780
 * Ghidra: void FUN_00350780(void)  [decompiler dropped body]
 * Calls the tagged relative-pointer resolver (FUN_00027754) with the incoming x0
 * and stores the result into x19. Confidence: low.
 * disasm: pacibsp; str x30; bl 0x27754; mov x19,x0; retab */
void sk_reg_780(word_t p)
{
    word_t r = sk_relptr_variant(p);  /* FUN_00027754 */
    __asm__ volatile("mov %0, x19" : "=r"(r)); (void)r;
}

/* FUN_00350884 @ 0x00350884
 * Ghidra: void FUN_00350884(void)  [decompiler dropped body]
 * Calls the indirect-dispatch thunk and compares its result against 1 (sets NZ
 * flags for the parent). Returns the raw result. Confidence: low.
 * disasm: pacibsp; str x30; bl 0x839f8; cmp w0,#1; retab */
word_t sk_reg_884(void)
{
    word_t r;
    __asm__ volatile("mov %0, x0" : "=r"(r));
    sk_indirect_dispatch();  /* FUN_000839f8; cmp w0,#1 follows */
    return r;
}

/* FUN_00350950 @ 0x00350950
 * Ghidra: void FUN_00350950(void)  [decompiler dropped body]
 * Calls the tagged relative-pointer resolver (FUN_00027754) with the incoming x0
 * and stores the result into x21. Confidence: low.
 * disasm: pacibsp; str x30; bl 0x27754; mov x21,x0; retab */
void sk_reg_950(word_t p)
{
    word_t r = sk_relptr_variant(p);  /* FUN_00027754 */
    __asm__ volatile("mov %0, x21" : "=r"(r)); (void)r;
}

/* ================================================================== *
 * String-constant tail calls into the shared string/buffer accessor.
 * ================================================================== */

/* FUN_0035059c @ 0x0035059c
 * Ghidra: void FUN_0035059c(void)  [decompiler dropped body]
 * Tail-calls the shared string accessor with the literal string at 0x5ce9d2
 * ("value", 7 bytes) and selector 1. Confidence: low.
 * disasm: adrp x0,0x5ce000; add x0,#0x9d2; mov w1,#7; mov w2,#1; b 0x1a89a8 */
word_t sk_reg_59c(void)
{
    return sk_str_accessor((word_t)0x5ce9d2, 7, 1);  /* s_value_005ce9d2; FUN_001a89a8 */
}

/* FUN_003505b0 @ 0x003505b0
 * Ghidra: void FUN_003505b0(void)  [decompiler dropped body]
 * Tail-calls the shared string accessor with the literal string at 0x5ce9c3
 * ("from invalid", 14 bytes) and selector 1. Confidence: low.
 * disasm: adrp x0,0x5ce000; add x0,#0x9c3; mov w1,#0xe; mov w2,#1; b 0x1a89a8 */
word_t sk_reg_5b0(void)
{
    return sk_str_accessor((word_t)0x5ce9c3, 0xe, 1);  /* s_from_invalid_005ce9c3; FUN_001a89a8 */
}

/* ================================================================== *
 * Pointer / data getters.
 * ================================================================== */

/* FUN_00350440 @ 0x00350440
 * Ghidra: undefined * FUN_00350440(void)
 * Returns a pointer to the descriptor block at 0x4c1010. Confidence: low.
 * disasm: adrp x0,0x4c1000; add x0,#0x10; ret */
word_t sk_reg_440(void)
{
    return (word_t)0x4c1010;  /* DAT_004c1010 */
}

/* FUN_0035041c @ 0x0035041c
 * Ghidra: void FUN_0035041c(void)  [decompiler dropped body]
 * Returns the address 0x677880 in x1. Confidence: low.
 * disasm: adrp x1,0x677000; add x1,#0x880; ret */
word_t sk_reg_41c(void)
{
    return (word_t)0x677880;
}

/* FUN_0035081c @ 0x0035081c
 * Ghidra: undefined * FUN_0035081c(void)
 * Returns a PAC-signed pointer to the descriptor block at 0x4e984c using the
 * fixed discriminator 0xc6eb. Confidence: low.
 * disasm: adrp x16,0x4e9000; add x16,#0x84c; mov x17,#0xc6eb; pacda x16,x17; mov x0,x16; ret */
word_t sk_reg_81c(void)
{
    word_t p = (word_t)0x4e984c;  /* DAT_004e984c */
    __asm__ volatile("mov x17, %0" : : "r"((word_t)0xc6eb) : "x17");
    __asm__ volatile("pacda %0, x17" : "+r"(p) : : "x17");
    return p;
}

/* FUN_00350834 @ 0x00350834
 * Ghidra: undefined * FUN_00350834(void)
 * Returns a PAC-signed pointer to the descriptor block at 0x4e9518 using the
 * fixed discriminator 0xc6eb. Confidence: low.
 * disasm: adrp x16,0x4e9000; add x16,#0x518; mov x17,#0xc6eb; pacda x16,x17; mov x0,x16; ret */
word_t sk_reg_834(void)
{
    word_t p = (word_t)0x4e9518;  /* DAT_004e9518 */
    __asm__ volatile("mov x17, %0" : : "r"((word_t)0xc6eb) : "x17");
    __asm__ volatile("pacda %0, x17" : "+r"(p) : : "x17");
    return p;
}
