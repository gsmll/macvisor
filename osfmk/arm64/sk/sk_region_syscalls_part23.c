/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 23: 0x354b2c-0x355908 syscall/exception-entry region (small leaf
 * helpers / frame glue / register-shims / constructors).
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"


/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

extern void FUN_00002534(void); /* out of slice */
extern void FUN_000a6894(void); /* out of slice */
extern void FUN_001a0908(void); /* out of slice */
extern void FUN_001a0be4(void); /* out of slice */
extern void FUN_001a157c(void); /* out of slice */
extern void FUN_00205844(void); /* out of slice */
extern void FUN_002060d4(void); /* out of slice */
extern void FUN_0024c82c(void); /* out of slice */
extern void FUN_0026bbd4(void); /* out of slice */
extern void FUN_00310a74(void); /* out of slice */
extern void FUN_00310ca4(void); /* out of slice */
extern void FUN_0031b900(void); /* out of slice */
extern void FUN_00327e08(void); /* out of slice */
extern void FUN_00376820(void); /* out of slice */


/* FUN_00354b2c @ 0x00354b2c   (est. sk_ret_00354b2c)
 * Ghidra: void FUN_00354b2c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b2c(void)
{
    return;
}

/* FUN_00354b38 @ 0x00354b38   (est. sk_ret_00354b38)
 * Ghidra: void FUN_00354b38(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b38(void)
{
    return;
}

/* FUN_00354b44 @ 0x00354b44   (est. sk_stack_param_store)
 * Ghidra: void FUN_00354b44(undefined8 param_1)
 * Confidence: low
 * Notes: arg spilled to stack slot x29-400
 */
void sk_stack_param_store(unsigned long v)
{
    (void)v; /* arg spilled to caller frame (x29-400) */
}

/* FUN_00354b50 @ 0x00354b50   (est. sk_read_prev_word)
 * Ghidra: undefined8 FUN_00354b50(long param_1)
 * Confidence: low
 * Notes: reads word at param-0x100
 */
unsigned long sk_read_prev_word(unsigned long base)
{
    return *(unsigned long *)(base - 0x100);
}

/* FUN_00354b5c @ 0x00354b5c   (est. sk_ret_00354b5c)
 * Ghidra: void FUN_00354b5c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b5c(void)
{
    return;
}

/* FUN_00354b68 @ 0x00354b68   (est. sk_ret_00354b68)
 * Ghidra: void FUN_00354b68(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b68(void)
{
    return;
}

/* FUN_00354b74 @ 0x00354b74   (est. sk_ret_00354b74)
 * Ghidra: void FUN_00354b74(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b74(void)
{
    return;
}

/* FUN_00354b80 @ 0x00354b80   (est. sk_ret_00354b80)
 * Ghidra: void FUN_00354b80(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b80(void)
{
    return;
}

/* FUN_00354b8c @ 0x00354b8c   (est. sk_ret_00354b8c)
 * Ghidra: void FUN_00354b8c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b8c(void)
{
    return;
}

/* FUN_00354b98 @ 0x00354b98   (est. sk_ret_00354b98)
 * Ghidra: void FUN_00354b98(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354b98(void)
{
    return;
}

/* FUN_00354ba4 @ 0x00354ba4   (est. sk_ret_00354ba4)
 * Ghidra: void FUN_00354ba4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ba4(void)
{
    return;
}

/* FUN_00354bb0 @ 0x00354bb0   (est. sk_ret_00354bb0)
 * Ghidra: void FUN_00354bb0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354bb0(void)
{
    return;
}

/* FUN_00354bbc @ 0x00354bbc   (est. sk_ret_00354bbc)
 * Ghidra: void FUN_00354bbc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354bbc(void)
{
    return;
}

/* FUN_00354bc8 @ 0x00354bc8   (est. sk_mk_pair_one)
 * Ghidra: undefined1 [16] FUN_00354bc8(undefined8 param_1)
 * Confidence: low
 * Notes: returns 16B pair {1,param}
 */
unsigned long sk_mk_pair_one(unsigned long hi)
{
    (void)hi; /* returns 16B {lo=1, hi=param} */
    return 1;
}

/* FUN_00354bd4 @ 0x00354bd4   (est. sk_ret_00354bd4)
 * Ghidra: void FUN_00354bd4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354bd4(void)
{
    return;
}

/* FUN_00354be0 @ 0x00354be0   (est. sk_ret_00354be0)
 * Ghidra: void FUN_00354be0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354be0(void)
{
    return;
}

/* FUN_00354bec @ 0x00354bec   (est. sk_ret_00354bec)
 * Ghidra: void FUN_00354bec(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354bec(void)
{
    return;
}

/* FUN_00354bf8 @ 0x00354bf8   (est. sk_ctor_656180)
 * Ghidra: void FUN_00354bf8(void)
 * Confidence: low
 * Notes: FUN_00002534(0x656180,&DAT_004e7fd8)
 */
void sk_ctor_656180(void)
{
    /* FUN_00002534(0x656180, &DAT_004e7fd8) */
}

/* FUN_00354c38 @ 0x00354c38   (est. sk_frame_ptr_neg78)
 * Ghidra: long FUN_00354c38(void)
 * Confidence: low
 * Notes: returns x29-0x78
 */
unsigned long sk_frame_ptr_neg78(void)
{
    return 0; /* x29-0x78 */
}

/* FUN_00354c44 @ 0x00354c44   (est. sk_ctor_64f3c0)
 * Ghidra: void FUN_00354c44(void)
 * Confidence: low
 * Notes: FUN_00002534(0x64f3c0,&DAT_004e7fc0)
 */
void sk_ctor_64f3c0(void)
{
    /* FUN_00002534(0x64f3c0, &DAT_004e7fc0) */
}

/* FUN_00354c58 @ 0x00354c58   (est. sk_id_or_zero)
 * Ghidra: long FUN_00354c58(long param_1)
 * Confidence: low
 * Notes: no-op normalize
 */
unsigned long sk_id_or_zero(unsigned long v)
{
    return v; /* Ghidra: if(v==0) v=0; no-op normalize */
}

/* FUN_00354c64 @ 0x00354c64   (est. sk_ret_00354c64)
 * Ghidra: void FUN_00354c64(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354c64(void)
{
    return;
}

/* FUN_00354c70 @ 0x00354c70   (est. sk_ret_00354c70)
 * Ghidra: void FUN_00354c70(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354c70(void)
{
    return;
}

/* FUN_00354c9c @ 0x00354c9c   (est. sk_ret_00354c9c)
 * Ghidra: void FUN_00354c9c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354c9c(void)
{
    return;
}

/* FUN_00354ca8 @ 0x00354ca8   (est. sk_ret_00354ca8)
 * Ghidra: void FUN_00354ca8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ca8(void)
{
    return;
}

/* FUN_00354cb4 @ 0x00354cb4   (est. sk_frame_load_neg58)
 * Ghidra: undefined8 FUN_00354cb4(void)
 * Confidence: low
 * Notes: loads frame-0x58
 */
unsigned long sk_frame_load_neg58(void)
{
    return 0; /* *(x29-0x58) */
}

/* FUN_00354cc0 @ 0x00354cc0   (est. sk_ret_00354cc0)
 * Ghidra: void FUN_00354cc0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354cc0(void)
{
    return;
}

/* FUN_00354ccc @ 0x00354ccc   (est. sk_ret_00354ccc)
 * Ghidra: void FUN_00354ccc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ccc(void)
{
    return;
}

/* FUN_00354cd8 @ 0x00354cd8   (est. sk_ret_00354cd8)
 * Ghidra: void FUN_00354cd8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354cd8(void)
{
    return;
}

/* FUN_00354ce4 @ 0x00354ce4   (est. sk_ret_00354ce4)
 * Ghidra: void FUN_00354ce4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ce4(void)
{
    return;
}

/* FUN_00354cf0 @ 0x00354cf0   (est. sk_frame_store_minus1)
 * Ghidra: void FUN_00354cf0(void)
 * Confidence: low
 * Notes: stores -1 at frame-0x58
 */
void sk_frame_store_minus1(void)
{
    /* *(x29-0x58) = 0xffffffffffffffff */
}

/* FUN_00354cfc @ 0x00354cfc   (est. sk_ret_00354cfc)
 * Ghidra: void FUN_00354cfc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354cfc(void)
{
    return;
}

/* FUN_00354d08 @ 0x00354d08   (est. sk_frame_load_neg78)
 * Ghidra: undefined8 FUN_00354d08(void)
 * Confidence: low
 * Notes: loads frame-0x78
 */
unsigned long sk_frame_load_neg78(void)
{
    return 0; /* *(x29-0x78) */
}

/* FUN_00354d14 @ 0x00354d14   (est. sk_ret_00354d14)
 * Ghidra: void FUN_00354d14(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d14(void)
{
    return;
}

/* FUN_00354d20 @ 0x00354d20   (est. sk_ret_00354d20)
 * Ghidra: void FUN_00354d20(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d20(void)
{
    return;
}

/* FUN_00354d2c @ 0x00354d2c   (est. sk_ret_00354d2c)
 * Ghidra: void FUN_00354d2c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d2c(void)
{
    return;
}

/* FUN_00354d38 @ 0x00354d38   (est. sk_ret_00354d38)
 * Ghidra: void FUN_00354d38(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d38(void)
{
    return;
}

/* FUN_00354d44 @ 0x00354d44   (est. sk_ret_00354d44)
 * Ghidra: void FUN_00354d44(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d44(void)
{
    return;
}

/* FUN_00354d50 @ 0x00354d50   (est. sk_ret_00354d50)
 * Ghidra: void FUN_00354d50(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d50(void)
{
    return;
}

/* FUN_00354d5c @ 0x00354d5c   (est. sk_ret_00354d5c)
 * Ghidra: void FUN_00354d5c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d5c(void)
{
    return;
}

/* FUN_00354d68 @ 0x00354d68   (est. sk_ret_00354d68)
 * Ghidra: void FUN_00354d68(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d68(void)
{
    return;
}

/* FUN_00354d74 @ 0x00354d74   (est. sk_ret_00354d74)
 * Ghidra: void FUN_00354d74(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d74(void)
{
    return;
}

/* FUN_00354d80 @ 0x00354d80   (est. sk_ctor_656248)
 * Ghidra: void FUN_00354d80(void)
 * Confidence: low
 * Notes: FUN_00002534(0x656248,&DAT_004e80a0)
 */
void sk_ctor_656248(void)
{
    /* FUN_00002534(0x656248, &DAT_004e80a0) */
}

/* FUN_00354d94 @ 0x00354d94   (est. sk_ret_00354d94)
 * Ghidra: void FUN_00354d94(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354d94(void)
{
    return;
}

/* FUN_00354da0 @ 0x00354da0   (est. sk_helper_31b900)
 * Ghidra: void FUN_00354da0(void)
 * Confidence: low
 * Notes: FUN_0031b900()
 */
void sk_helper_31b900(void)
{
    /* FUN_0031b900() */
}

/* FUN_00354db8 @ 0x00354db8   (est. sk_pass_x3)
 * Ghidra: undefined8 FUN_00354db8(void)
 * Confidence: low
 * Notes: returns in_x3
 */
unsigned long sk_pass_x3(void)
{
    return 0; /* in_x3 */
}

/* FUN_00354dc4 @ 0x00354dc4   (est. sk_ret_00354dc4)
 * Ghidra: void FUN_00354dc4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354dc4(void)
{
    return;
}

/* FUN_00354dd0 @ 0x00354dd0   (est. sk_ret_00354dd0)
 * Ghidra: void FUN_00354dd0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354dd0(void)
{
    return;
}

/* FUN_00354ddc @ 0x00354ddc   (est. sk_ret_00354ddc)
 * Ghidra: void FUN_00354ddc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ddc(void)
{
    return;
}

/* FUN_00354de8 @ 0x00354de8   (est. sk_ret_00354de8)
 * Ghidra: void FUN_00354de8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354de8(void)
{
    return;
}

/* FUN_00354df4 @ 0x00354df4   (est. sk_ret_00354df4)
 * Ghidra: void FUN_00354df4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354df4(void)
{
    return;
}

/* FUN_00354e00 @ 0x00354e00   (est. sk_ret_arg3)
 * Ghidra: undefined8 FUN_00354e00(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: low
 * Notes: returns param_3
 */
unsigned long sk_ret_arg3(unsigned long a,unsigned long b,unsigned long c)
{
    (void)a;(void)b; return c;
}

/* FUN_00354e0c @ 0x00354e0c   (est. sk_ret_00354e0c)
 * Ghidra: void FUN_00354e0c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354e0c(void)
{
    return;
}

/* FUN_00354e18 @ 0x00354e18   (est. sk_dtor_data_4ea794)
 * Ghidra: void FUN_00354e18(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004ea794)
 */
void sk_dtor_data_4ea794(void)
{
    /* FUN_00376820(&DAT_004ea794) */
}

/* FUN_00354e34 @ 0x00354e34   (est. sk_reg_cb_1a0908)
 * Ghidra: void FUN_00354e34(void)
 * Confidence: low
 * Notes: FUN_001a157c(FUN_001a0908)
 */
void sk_reg_cb_1a0908(void)
{
    /* FUN_001a157c(FUN_001a0908) */
}

/* FUN_00354e50 @ 0x00354e50   (est. sk_dtor_data_4eac00)
 * Ghidra: void FUN_00354e50(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004eac00)
 */
void sk_dtor_data_4eac00(void)
{
    /* FUN_00376820(&DAT_004eac00) */
}

/* FUN_00354e6c @ 0x00354e6c   (est. sk_dtor_data_4f0e1c)
 * Ghidra: void FUN_00354e6c(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004f0e1c)
 */
void sk_dtor_data_4f0e1c(void)
{
    /* FUN_00376820(&DAT_004f0e1c) */
}

/* FUN_00354e88 @ 0x00354e88   (est. sk_dtor_data_4ec318)
 * Ghidra: void FUN_00354e88(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004ec318)
 */
void sk_dtor_data_4ec318(void)
{
    /* FUN_00376820(&DAT_004ec318) */
}

/* FUN_00354ea4 @ 0x00354ea4   (est. sk_dtor_data_4e9d3c)
 * Ghidra: void FUN_00354ea4(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004e9d3c)
 */
void sk_dtor_data_4e9d3c(void)
{
    /* FUN_00376820(&DAT_004e9d3c) */
}

/* FUN_00354ec0 @ 0x00354ec0   (est. sk_dtor_data_4eddb0)
 * Ghidra: void FUN_00354ec0(void)
 * Confidence: low
 * Notes: FUN_00376820(&DAT_004eddb0)
 */
void sk_dtor_data_4eddb0(void)
{
    /* FUN_00376820(&DAT_004eddb0) */
}

/* FUN_00354edc @ 0x00354edc   (est. sk_reg_cb_1a0be4)
 * Ghidra: void FUN_00354edc(void)
 * Confidence: low
 * Notes: FUN_001a157c(FUN_001a0be4)
 */
void sk_reg_cb_1a0be4(void)
{
    /* FUN_001a157c(FUN_001a0be4) */
}

/* FUN_00354ef8 @ 0x00354ef8   (est. sk_ret_00354ef8)
 * Ghidra: void FUN_00354ef8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ef8(void)
{
    return;
}

/* FUN_00354f10 @ 0x00354f10   (est. sk_ret_00354f10)
 * Ghidra: void FUN_00354f10(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f10(void)
{
    return;
}

/* FUN_00354f1c @ 0x00354f1c   (est. sk_ret_00354f1c)
 * Ghidra: void FUN_00354f1c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f1c(void)
{
    return;
}

/* FUN_00354f28 @ 0x00354f28   (est. sk_ret_00354f28)
 * Ghidra: void FUN_00354f28(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f28(void)
{
    return;
}

/* FUN_00354f34 @ 0x00354f34   (est. sk_helper_a6894)
 * Ghidra: void FUN_00354f34(void)
 * Confidence: low
 * Notes: FUN_000a6894()
 */
void sk_helper_a6894(void)
{
    /* FUN_000a6894() */
}

/* FUN_00354f4c @ 0x00354f4c   (est. sk_helper_310ca4)
 * Ghidra: void FUN_00354f4c(void)
 * Confidence: low
 * Notes: FUN_00310ca4()
 */
void sk_helper_310ca4(void)
{
    /* FUN_00310ca4() */
}

/* FUN_00354f64 @ 0x00354f64   (est. sk_ret_00354f64)
 * Ghidra: void FUN_00354f64(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f64(void)
{
    return;
}

/* FUN_00354f70 @ 0x00354f70   (est. sk_ret_00354f70)
 * Ghidra: void FUN_00354f70(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f70(void)
{
    return;
}

/* FUN_00354f80 @ 0x00354f80   (est. sk_ret_00354f80)
 * Ghidra: void FUN_00354f80(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f80(void)
{
    return;
}

/* FUN_00354f8c @ 0x00354f8c   (est. sk_ret_00354f8c)
 * Ghidra: void FUN_00354f8c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354f8c(void)
{
    return;
}

/* FUN_00354f98 @ 0x00354f98   (est. sk_copy_pair)
 * Ghidra: void FUN_00354f98(void)
 * Confidence: low
 * Notes: copies {+0x20 word, +0x28 byte} x19->x20
 */
void sk_copy_pair(unsigned long *dst,unsigned long *src)
{
    dst[4] = src[4]; /* +0x20 */
    *(unsigned char *)((char*)dst+0x28) = *(unsigned char *)((char*)src+0x28);
}

/* FUN_00354fac @ 0x00354fac   (est. sk_ret_00354fac)
 * Ghidra: void FUN_00354fac(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354fac(void)
{
    return;
}

/* FUN_00354fc0 @ 0x00354fc0   (est. sk_ret_00354fc0)
 * Ghidra: void FUN_00354fc0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354fc0(void)
{
    return;
}

/* FUN_00354fd0 @ 0x00354fd0   (est. sk_ret_00354fd0)
 * Ghidra: void FUN_00354fd0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354fd0(void)
{
    return;
}

/* FUN_00354fe0 @ 0x00354fe0   (est. sk_ret_00354fe0)
 * Ghidra: void FUN_00354fe0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354fe0(void)
{
    return;
}

/* FUN_00354ff4 @ 0x00354ff4   (est. sk_ret_00354ff4)
 * Ghidra: void FUN_00354ff4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00354ff4(void)
{
    return;
}

/* FUN_00355008 @ 0x00355008   (est. sk_ret_00355008)
 * Ghidra: void FUN_00355008(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355008(void)
{
    return;
}

/* FUN_00355018 @ 0x00355018   (est. sk_ret_00355018)
 * Ghidra: void FUN_00355018(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355018(void)
{
    return;
}

/* FUN_0035503c @ 0x0035503c   (est. sk_ret_0035503c)
 * Ghidra: void FUN_0035503c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035503c(void)
{
    return;
}

/* FUN_0035504c @ 0x0035504c   (est. sk_load_slot)
 * Ghidra: void FUN_0035504c(undefined8 param_1,undefined8 *param_2)
 * Confidence: low
 * Notes: *x19 = *param_2
 */
void sk_load_slot(unsigned long *dst,unsigned long *src)
{
    *dst = *src;
}

/* FUN_0035505c @ 0x0035505c   (est. sk_frame_load_neg130)
 * Ghidra: undefined8 FUN_0035505c(void)
 * Confidence: low
 * Notes: loads frame-0x130
 */
unsigned long sk_frame_load_neg130(void)
{
    return 0; /* *(x29-0x130) */
}

/* FUN_00355068 @ 0x00355068   (est. sk_ret_00355068)
 * Ghidra: void FUN_00355068(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355068(void)
{
    return;
}

/* FUN_00355074 @ 0x00355074   (est. sk_ret_00355074)
 * Ghidra: void FUN_00355074(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355074(void)
{
    return;
}

/* FUN_00355080 @ 0x00355080   (est. sk_ret_00355080)
 * Ghidra: void FUN_00355080(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355080(void)
{
    return;
}

/* FUN_00355090 @ 0x00355090   (est. sk_copy_pair_2)
 * Ghidra: void FUN_00355090(long param_1,long param_2)
 * Confidence: low
 * Notes: copies {+0x20 word,+0x28 word}
 */
void sk_copy_pair_2(unsigned long *dst,unsigned long *src)
{
    *(unsigned long*)((char*)dst+0x20) = *(unsigned long*)((char*)src+0x20);
    *(unsigned int*)((char*)dst+0x28) = *(unsigned int*)((char*)src+0x28);
}

/* FUN_003550a4 @ 0x003550a4   (est. sk_ret_003550a4)
 * Ghidra: void FUN_003550a4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003550a4(void)
{
    return;
}

/* FUN_003550cc @ 0x003550cc   (est. sk_ret_003550cc)
 * Ghidra: void FUN_003550cc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003550cc(void)
{
    return;
}

/* FUN_003550e0 @ 0x003550e0   (est. sk_andc_pair)
 * Ghidra: undefined1 [16] FUN_003550e0(void)
 * Confidence: low
 * Notes: returns 16B {x24&~x23, x20&~x23}
 */
unsigned long sk_andc_pair(void)
{
    return 0; /* {lo=x24&~x23, hi=x20&~x23} */
}

/* FUN_003550f0 @ 0x003550f0   (est. sk_ret_003550f0)
 * Ghidra: void FUN_003550f0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003550f0(void)
{
    return;
}

/* FUN_00355100 @ 0x00355100   (est. sk_read_prev_word_2)
 * Ghidra: undefined8 FUN_00355100(long param_1)
 * Confidence: low
 * Notes: reads word at param-0x100
 */
unsigned long sk_read_prev_word_2(unsigned long base)
{
    return *(unsigned long *)(base - 0x100);
}

/* FUN_0035510c @ 0x0035510c   (est. sk_ret_0035510c)
 * Ghidra: void FUN_0035510c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035510c(void)
{
    return;
}

/* FUN_00355118 @ 0x00355118   (est. sk_copy16_ret3)
 * Ghidra: undefined8 FUN_00355118(undefined8 *param_1,undefined8 *param_2)
 * Confidence: low
 * Notes: copies 16B, returns param_1[3]
 */
unsigned long sk_copy16_ret3(unsigned long *dst,unsigned long *src)
{
    dst[0]=src[0]; dst[1]=src[1];
    return dst[3];
}

/* FUN_0035512c @ 0x0035512c   (est. sk_frame_load_neg60)
 * Ghidra: undefined8 FUN_0035512c(void)
 * Confidence: low
 * Notes: loads frame-0x60
 */
unsigned long sk_frame_load_neg60(void)
{
    return 0; /* *(x29-0x60) */
}

/* FUN_00355150 @ 0x00355150   (est. sk_ret_00355150)
 * Ghidra: void FUN_00355150(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355150(void)
{
    return;
}

/* FUN_00355160 @ 0x00355160   (est. sk_ret_00355160)
 * Ghidra: void FUN_00355160(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355160(void)
{
    return;
}

/* FUN_0035516c @ 0x0035516c   (est. sk_ret_0035516c)
 * Ghidra: void FUN_0035516c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035516c(void)
{
    return;
}

/* FUN_0035517c @ 0x0035517c   (est. sk_ret_0035517c)
 * Ghidra: void FUN_0035517c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035517c(void)
{
    return;
}

/* FUN_00355190 @ 0x00355190   (est. sk_helper_24c82c)
 * Ghidra: void FUN_00355190(void)
 * Confidence: low
 * Notes: FUN_0024c82c(4,4)
 */
void sk_helper_24c82c(void)
{
    /* FUN_0024c82c(4,4) */
}

/* FUN_003551a0 @ 0x003551a0   (est. sk_ret_003551a0)
 * Ghidra: void FUN_003551a0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003551a0(void)
{
    return;
}

/* FUN_003551b0 @ 0x003551b0   (est. sk_ret_003551b0)
 * Ghidra: void FUN_003551b0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003551b0(void)
{
    return;
}

/* FUN_003551c4 @ 0x003551c4   (est. sk_ret_003551c4)
 * Ghidra: void FUN_003551c4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003551c4(void)
{
    return;
}

/* FUN_003551d8 @ 0x003551d8   (est. sk_ret_003551d8)
 * Ghidra: void FUN_003551d8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003551d8(void)
{
    return;
}

/* FUN_003551e8 @ 0x003551e8   (est. sk_ret_003551e8)
 * Ghidra: void FUN_003551e8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003551e8(void)
{
    return;
}

/* FUN_003551f8 @ 0x003551f8   (est. sk_store4)
 * Ghidra: void FUN_003551f8(void)
 * Confidence: low
 * Notes: x19[0..3] = 4 stack args
 */
void sk_store4(unsigned long a,unsigned long b,unsigned long c,unsigned long d)
{
    (void)a;(void)b;(void)c;(void)d; /* stores 4 words to x19 frame */
}

/* FUN_00355208 @ 0x00355208   (est. sk_ret_00355208)
 * Ghidra: void FUN_00355208(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355208(void)
{
    return;
}

/* FUN_00355224 @ 0x00355224   (est. sk_ret_00355224)
 * Ghidra: void FUN_00355224(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355224(void)
{
    return;
}

/* FUN_00355230 @ 0x00355230   (est. sk_pair_from_frame)
 * Ghidra: undefined1 [16] FUN_00355230(void)
 * Confidence: low
 * Notes: returns {x29-0x70, x29-0x88}
 */
unsigned long sk_pair_from_frame(void)
{
    return 0; /* {lo=*(x29-0x70), hi=*(x29-0x88)} */
}

/* FUN_00355244 @ 0x00355244   (est. sk_helper_327e08)
 * Ghidra: void FUN_00355244(void)
 * Confidence: low
 * Notes: FUN_00327e08()
 */
void sk_helper_327e08(void)
{
    /* FUN_00327e08() */
}

/* FUN_0035525c @ 0x0035525c   (est. sk_ret_zero)
 * Ghidra: undefined8 FUN_0035525c(void)
 * Confidence: low
 * Notes: returns 0
 */
unsigned long sk_ret_zero(void)
{
    return 0;
}

/* FUN_00355270 @ 0x00355270   (est. sk_branch_2060d4)
 * Ghidra: void FUN_00355270(void)
 * Confidence: low
 * Notes: pcStack=FUN_002060d4; FUN_0026bbd4()
 */
void sk_branch_2060d4(void)
{
    /* FUN_0026bbd4() with FUN_002060d4 */
}

/* FUN_00355288 @ 0x00355288   (est. sk_ret_00355288)
 * Ghidra: void FUN_00355288(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355288(void)
{
    return;
}

/* FUN_003552a0 @ 0x003552a0   (est. sk_ret_003552a0)
 * Ghidra: void FUN_003552a0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003552a0(void)
{
    return;
}

/* FUN_003552ac @ 0x003552ac   (est. sk_store2_frame)
 * Ghidra: void FUN_003552ac(void)
 * Confidence: low
 * Notes: stores x25,x26 to frame
 */
void sk_store2_frame(void)
{
    /* *(x29-0x78)=x25; *(x29-0x70)=x26 */
}

/* FUN_003552bc @ 0x003552bc   (est. sk_ret_003552bc)
 * Ghidra: void FUN_003552bc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003552bc(void)
{
    return;
}

/* FUN_003552d0 @ 0x003552d0   (est. sk_load16_frame10)
 * Ghidra: undefined1 [16] FUN_003552d0(void)
 * Confidence: low
 * Notes: returns 16B at frame+0x10
 */
unsigned long sk_load16_frame10(void)
{
    return 0; /* *(x29+0x10) */
}

/* FUN_003552e0 @ 0x003552e0   (est. sk_ret_003552e0)
 * Ghidra: void FUN_003552e0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003552e0(void)
{
    return;
}

/* FUN_003552f0 @ 0x003552f0   (est. sk_load_glob_6adf10)
 * Ghidra: undefined1 [16] FUN_003552f0(void)
 * Confidence: low
 * Notes: returns _DAT_006adf10
 */
unsigned long sk_load_glob_6adf10(void)
{
    return 0; /* _DAT_006adf10 */
}

/* FUN_00355300 @ 0x00355300   (est. sk_ret_00355300)
 * Ghidra: void FUN_00355300(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355300(void)
{
    return;
}

/* FUN_00355314 @ 0x00355314   (est. sk_ret_00355314)
 * Ghidra: void FUN_00355314(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355314(void)
{
    return;
}

/* FUN_00355324 @ 0x00355324   (est. sk_const_ff)
 * Ghidra: undefined8 FUN_00355324(void)
 * Confidence: low
 * Notes: returns 0xff
 */
unsigned long sk_const_ff(void)
{
    return 0xff;
}

/* FUN_00355334 @ 0x00355334   (est. sk_stack_ptr_8)
 * Ghidra: undefined1 * FUN_00355334(void)
 * Confidence: low
 * Notes: returns &stack0x8
 */
void *sk_stack_ptr_8(void)
{
    return 0; /* &stack0x8 */
}

/* FUN_00355340 @ 0x00355340   (est. sk_ret_00355340)
 * Ghidra: void FUN_00355340(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355340(void)
{
    return;
}

/* FUN_00355354 @ 0x00355354   (est. sk_bit_from_tag)
 * Ghidra: undefined1 [16] FUN_00355354(long param_1)
 * Confidence: low
 * Notes: returns {1L<<byte(param+0x20), *(param+0x24), 0}
 */
unsigned long sk_bit_from_tag(unsigned long base)
{
    (void)base;
    return 1L << (*(unsigned char*)(base+0x20) & 0x3f);
}

/* FUN_00355374 @ 0x00355374   (est. sk_store2_frame_2)
 * Ghidra: void FUN_00355374(void)
 * Confidence: low
 * Notes: stores x20,x22 to frame
 */
void sk_store2_frame_2(void)
{
    /* *(x29-0x78)=x20; *(x29-0x70)=x22 */
}

/* FUN_00355384 @ 0x00355384   (est. sk_store2_frame_3)
 * Ghidra: void FUN_00355384(void)
 * Confidence: low
 * Notes: stores x19,x20 to frame
 */
void sk_store2_frame_3(void)
{
    /* *(x29-0x78)=x19; *(x29-0x70)=x20 */
}

/* FUN_00355394 @ 0x00355394   (est. sk_const_ff_2)
 * Ghidra: undefined8 FUN_00355394(void)
 * Confidence: low
 * Notes: returns 0xff
 */
unsigned long sk_const_ff_2(void)
{
    return 0xff;
}

/* FUN_003553a8 @ 0x003553a8   (est. sk_ret_003553a8)
 * Ghidra: void FUN_003553a8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003553a8(void)
{
    return;
}

/* FUN_003553b8 @ 0x003553b8   (est. sk_ret_003553b8)
 * Ghidra: void FUN_003553b8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003553b8(void)
{
    return;
}

/* FUN_003553cc @ 0x003553cc   (est. sk_stack_store_neg118)
 * Ghidra: void FUN_003553cc(undefined8 param_1)
 * Confidence: low
 * Notes: stores param at frame-0x118
 */
void sk_stack_store_neg118(unsigned long v)
{
    (void)v; /* *(x29-0x118)=v */
}

/* FUN_003553d8 @ 0x003553d8   (est. sk_ret_003553d8)
 * Ghidra: void FUN_003553d8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003553d8(void)
{
    return;
}

/* FUN_003553e4 @ 0x003553e4   (est. sk_ret_003553e4)
 * Ghidra: void FUN_003553e4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003553e4(void)
{
    return;
}

/* FUN_003553f4 @ 0x003553f4   (est. sk_const_max63)
 * Ghidra: undefined1 [16] FUN_003553f4(void)
 * Confidence: low
 * Notes: ZEXT816(0x7fffffffffffffff)
 */
unsigned long sk_const_max63(void)
{
    return 0x7fffffffffffffff;
}

/* FUN_00355404 @ 0x00355404   (est. sk_ret_00355404)
 * Ghidra: void FUN_00355404(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355404(void)
{
    return;
}

/* FUN_00355418 @ 0x00355418   (est. sk_ret_00355418)
 * Ghidra: void FUN_00355418(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355418(void)
{
    return;
}

/* FUN_00355424 @ 0x00355424   (est. sk_ret_00355424)
 * Ghidra: void FUN_00355424(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355424(void)
{
    return;
}

/* FUN_00355430 @ 0x00355430   (est. sk_ret_00355430)
 * Ghidra: void FUN_00355430(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355430(void)
{
    return;
}

/* FUN_0035543c @ 0x0035543c   (est. sk_stack_ptr_8_2)
 * Ghidra: undefined1 * FUN_0035543c(void)
 * Confidence: low
 * Notes: returns &stack0x8
 */
void *sk_stack_ptr_8_2(void)
{
    return 0; /* &stack0x8 */
}

/* FUN_00355448 @ 0x00355448   (est. sk_stack_ptr_8_3)
 * Ghidra: undefined1 * FUN_00355448(void)
 * Confidence: low
 * Notes: returns &stack0x8
 */
void *sk_stack_ptr_8_3(void)
{
    return 0; /* &stack0x8 */
}

/* FUN_00355458 @ 0x00355458   (est. sk_ret_00355458)
 * Ghidra: void FUN_00355458(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355458(void)
{
    return;
}

/* FUN_00355464 @ 0x00355464   (est. sk_ret_00355464)
 * Ghidra: void FUN_00355464(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355464(void)
{
    return;
}

/* FUN_00355474 @ 0x00355474   (est. sk_store80_call)
 * Ghidra: void FUN_00355474(void)
 * Confidence: low
 * Notes: stores -0x80 at frame-0x58; FUN_00310a74()
 */
void sk_store80_call(void)
{
    /* *(x29-0x58)=0xffffffffffffff80; FUN_00310a74() */
}

/* FUN_00355484 @ 0x00355484   (est. sk_branch_205844)
 * Ghidra: void FUN_00355484(void)
 * Confidence: low
 * Notes: FUN_0026bbd4() with FUN_00205844
 */
void sk_branch_205844(void)
{
    /* FUN_0026bbd4() with FUN_00205844 */
}

/* FUN_0035549c @ 0x0035549c   (est. sk_ret_0035549c)
 * Ghidra: void FUN_0035549c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035549c(void)
{
    return;
}

/* FUN_003554b0 @ 0x003554b0   (est. sk_ret_003554b0)
 * Ghidra: void FUN_003554b0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003554b0(void)
{
    return;
}

/* FUN_003554c4 @ 0x003554c4   (est. sk_ret_003554c4)
 * Ghidra: void FUN_003554c4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003554c4(void)
{
    return;
}

/* FUN_003554d4 @ 0x003554d4   (est. sk_ret_003554d4)
 * Ghidra: void FUN_003554d4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003554d4(void)
{
    return;
}

/* FUN_003554e0 @ 0x003554e0   (est. sk_store4_args)
 * Ghidra: void FUN_003554e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Confidence: low
 * Notes: x19[0..3] = 4 args
 */
void sk_store4_args(unsigned long a,unsigned long b,unsigned long c,unsigned long d)
{
    (void)a;(void)b;(void)c;(void)d;
}

/* FUN_003554ec @ 0x003554ec   (est. sk_ret_003554ec)
 * Ghidra: void FUN_003554ec(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003554ec(void)
{
    return;
}

/* FUN_00355528 @ 0x00355528   (est. sk_pair_stack)
 * Ghidra: undefined1 [16] FUN_00355528(void)
 * Confidence: low
 * Notes: returns {&stack0x18,&stack0x10}
 */
unsigned long sk_pair_stack(void)
{
    return 0; /* {lo=&stack0x18, hi=&stack0x10} */
}

/* FUN_00355538 @ 0x00355538   (est. sk_ret_00355538)
 * Ghidra: void FUN_00355538(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355538(void)
{
    return;
}

/* FUN_00355544 @ 0x00355544   (est. sk_ret_00355544)
 * Ghidra: void FUN_00355544(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355544(void)
{
    return;
}

/* FUN_00355550 @ 0x00355550   (est. sk_ret_00355550)
 * Ghidra: void FUN_00355550(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355550(void)
{
    return;
}

/* FUN_00355560 @ 0x00355560   (est. sk_ret_00355560)
 * Ghidra: void FUN_00355560(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355560(void)
{
    return;
}

/* FUN_0035556c @ 0x0035556c   (est. sk_load_slot_2)
 * Ghidra: void FUN_0035556c(undefined8 param_1,undefined8 *param_2)
 * Confidence: low
 * Notes: *x19 = *param_2
 */
void sk_load_slot_2(unsigned long *dst,unsigned long *src)
{
    *dst = *src;
}

/* FUN_00355578 @ 0x00355578   (est. sk_ret_00355578)
 * Ghidra: void FUN_00355578(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355578(void)
{
    return;
}

/* FUN_00355594 @ 0x00355594   (est. sk_ret_00355594)
 * Ghidra: void FUN_00355594(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355594(void)
{
    return;
}

/* FUN_003555a0 @ 0x003555a0   (est. sk_ret_003555a0)
 * Ghidra: void FUN_003555a0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003555a0(void)
{
    return;
}

/* FUN_003555b4 @ 0x003555b4   (est. sk_ret_003555b4)
 * Ghidra: void FUN_003555b4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003555b4(void)
{
    return;
}

/* FUN_003555dc @ 0x003555dc   (est. sk_ret_003555dc)
 * Ghidra: void FUN_003555dc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003555dc(void)
{
    return;
}

/* FUN_00355604 @ 0x00355604   (est. sk_frame_load_neg58_2)
 * Ghidra: undefined8 FUN_00355604(void)
 * Confidence: low
 * Notes: loads frame-0x58
 */
unsigned long sk_frame_load_neg58_2(void)
{
    return 0; /* *(x29-0x58) */
}

/* FUN_00355610 @ 0x00355610   (est. sk_ret_00355610)
 * Ghidra: void FUN_00355610(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355610(void)
{
    return;
}

/* FUN_00355624 @ 0x00355624   (est. sk_ret_00355624)
 * Ghidra: void FUN_00355624(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355624(void)
{
    return;
}

/* FUN_00355634 @ 0x00355634   (est. sk_frame_ptr_neg78_2)
 * Ghidra: long FUN_00355634(void)
 * Confidence: low
 * Notes: returns x29-0x78
 */
unsigned long sk_frame_ptr_neg78_2(void)
{
    return 0; /* x29-0x78 */
}

/* FUN_00355640 @ 0x00355640   (est. sk_ret_00355640)
 * Ghidra: void FUN_00355640(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355640(void)
{
    return;
}

/* FUN_0035564c @ 0x0035564c   (est. sk_ret_0035564c)
 * Ghidra: void FUN_0035564c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035564c(void)
{
    return;
}

/* FUN_00355660 @ 0x00355660   (est. sk_ret_00355660)
 * Ghidra: void FUN_00355660(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355660(void)
{
    return;
}

/* FUN_00355674 @ 0x00355674   (est. sk_zero5_slots)
 * Ghidra: void FUN_00355674(void)
 * Confidence: low
 * Notes: zeroes 5 frame slots
 */
void sk_zero5_slots(void)
{
    /* *(x29-0x80..-0x98)=0 x5 */
}

/* FUN_00355684 @ 0x00355684   (est. sk_ret_00355684)
 * Ghidra: void FUN_00355684(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355684(void)
{
    return;
}

/* FUN_00355694 @ 0x00355694   (est. sk_ret_00355694)
 * Ghidra: void FUN_00355694(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355694(void)
{
    return;
}

/* FUN_003556a4 @ 0x003556a4   (est. sk_ret_003556a4)
 * Ghidra: void FUN_003556a4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003556a4(void)
{
    return;
}

/* FUN_003556b0 @ 0x003556b0   (est. sk_shift_ctor)
 * Ghidra: void FUN_003556b0(char param_1)
 * Confidence: low
 * Notes: FUN_00002534((1L<<shift)+0x3f, x4, x5)
 */
void sk_shift_ctor(char shift)
{
    (void)shift; /* FUN_00002534((1L<<shift)+0x3f, in_x4, in_x5) */
}

/* FUN_003556e0 @ 0x003556e0   (est. sk_ret_003556e0)
 * Ghidra: void FUN_003556e0(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003556e0(void)
{
    return;
}

/* FUN_003556f4 @ 0x003556f4   (est. sk_ret_003556f4)
 * Ghidra: void FUN_003556f4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003556f4(void)
{
    return;
}

/* FUN_00355704 @ 0x00355704   (est. sk_frame_ptr_neg50)
 * Ghidra: long FUN_00355704(void)
 * Confidence: low
 * Notes: returns x29-0x50
 */
unsigned long sk_frame_ptr_neg50(void)
{
    return 0; /* x29-0x50 */
}

/* FUN_00355720 @ 0x00355720   (est. sk_store_arg_masked)
 * Ghidra: void FUN_00355720(undefined8 param_1,undefined8 param_2,undefined8 param_3,ulong param_4)
 * Confidence: low
 * Notes: stores param_3 and param_4&0xffffff
 */
void sk_store_arg_masked(unsigned long a,unsigned long b,unsigned long c,unsigned long d)
{
    (void)a;(void)b;(void)c;(void)(d&0xffffff);
}

/* FUN_00355730 @ 0x00355730   (est. sk_ret_00355730)
 * Ghidra: void FUN_00355730(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355730(void)
{
    return;
}

/* FUN_00355740 @ 0x00355740   (est. sk_ret_00355740)
 * Ghidra: void FUN_00355740(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355740(void)
{
    return;
}

/* FUN_00355754 @ 0x00355754   (est. sk_ret_00355754)
 * Ghidra: void FUN_00355754(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355754(void)
{
    return;
}

/* FUN_00355760 @ 0x00355760   (est. sk_ret_00355760)
 * Ghidra: void FUN_00355760(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355760(void)
{
    return;
}

/* FUN_00355770 @ 0x00355770   (est. sk_ret_00355770)
 * Ghidra: void FUN_00355770(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355770(void)
{
    return;
}

/* FUN_00355780 @ 0x00355780   (est. sk_const_ff_3)
 * Ghidra: undefined8 FUN_00355780(void)
 * Confidence: low
 * Notes: returns 0xff
 */
unsigned long sk_const_ff_3(void)
{
    return 0xff;
}

/* FUN_0035578c @ 0x0035578c   (est. sk_ret_0035578c)
 * Ghidra: void FUN_0035578c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035578c(void)
{
    return;
}

/* FUN_003557a8 @ 0x003557a8   (est. sk_ret_003557a8)
 * Ghidra: void FUN_003557a8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003557a8(void)
{
    return;
}

/* FUN_003557b4 @ 0x003557b4   (est. sk_ret_003557b4)
 * Ghidra: void FUN_003557b4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003557b4(void)
{
    return;
}

/* FUN_003557c8 @ 0x003557c8   (est. sk_ret_003557c8)
 * Ghidra: void FUN_003557c8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003557c8(void)
{
    return;
}

/* FUN_003557d8 @ 0x003557d8   (est. sk_ret_003557d8)
 * Ghidra: void FUN_003557d8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003557d8(void)
{
    return;
}

/* FUN_003557ec @ 0x003557ec   (est. sk_ret_003557ec)
 * Ghidra: void FUN_003557ec(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003557ec(void)
{
    return;
}

/* FUN_00355800 @ 0x00355800   (est. sk_ret_00355800)
 * Ghidra: void FUN_00355800(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355800(void)
{
    return;
}

/* FUN_00355814 @ 0x00355814   (est. sk_ret_00355814)
 * Ghidra: void FUN_00355814(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355814(void)
{
    return;
}

/* FUN_00355824 @ 0x00355824   (est. sk_copy_byte_idx)
 * Ghidra: void FUN_00355824(long param_1)
 * Confidence: low
 * Notes: copies byte at param+idx1 -> param+idx2
 */
void sk_copy_byte_idx(unsigned long base)
{
    (void)base; /* byte copy between two index offsets */
}

/* FUN_0035583c @ 0x0035583c   (est. sk_ret_0035583c)
 * Ghidra: void FUN_0035583c(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_0035583c(void)
{
    return;
}

/* FUN_00355848 @ 0x00355848   (est. sk_ret_00355848)
 * Ghidra: void FUN_00355848(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355848(void)
{
    return;
}

/* FUN_00355858 @ 0x00355858   (est. sk_ret_00355858)
 * Ghidra: void FUN_00355858(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355858(void)
{
    return;
}

/* FUN_00355868 @ 0x00355868   (est. sk_andc)
 * Ghidra: ulong FUN_00355868(void)
 * Confidence: low
 * Notes: returns x24&~x23
 */
unsigned long sk_andc(void)
{
    return 0; /* x24 & ~x23 */
}

/* FUN_00355878 @ 0x00355878   (est. sk_ret_00355878)
 * Ghidra: void FUN_00355878(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355878(void)
{
    return;
}

/* FUN_00355884 @ 0x00355884   (est. sk_ret_00355884)
 * Ghidra: void FUN_00355884(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355884(void)
{
    return;
}

/* FUN_00355890 @ 0x00355890   (est. sk_ret_00355890)
 * Ghidra: void FUN_00355890(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355890(void)
{
    return;
}

/* FUN_003558a8 @ 0x003558a8   (est. sk_ret_003558a8)
 * Ghidra: void FUN_003558a8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003558a8(void)
{
    return;
}

/* FUN_003558b8 @ 0x003558b8   (est. sk_ret_003558b8)
 * Ghidra: void FUN_003558b8(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003558b8(void)
{
    return;
}

/* FUN_003558c4 @ 0x003558c4   (est. sk_ret_003558c4)
 * Ghidra: void FUN_003558c4(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003558c4(void)
{
    return;
}

/* FUN_003558d8 @ 0x003558d8   (est. sk_stack_store_neg200)
 * Ghidra: void FUN_003558d8(undefined8 param_1)
 * Confidence: low
 * Notes: stores param at frame-200
 */
void sk_stack_store_neg200(unsigned long v)
{
    (void)v; /* *(x29-200)=v */
}

/* FUN_003558ec @ 0x003558ec   (est. sk_ret_003558ec)
 * Ghidra: void FUN_003558ec(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003558ec(void)
{
    return;
}

/* FUN_003558fc @ 0x003558fc   (est. sk_ret_003558fc)
 * Ghidra: void FUN_003558fc(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_003558fc(void)
{
    return;
}

/* FUN_00355908 @ 0x00355908   (est. sk_ret_00355908)
 * Ghidra: void FUN_00355908(void)
 * Confidence: low
 * Notes: trivial leaf; bare ret
 */
void sk_ret_00355908(void)
{
    return;
}
