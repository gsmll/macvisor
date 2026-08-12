/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 24: 0x355914-0x356670 syscall/exception-entry region. This range is a
 * dense cluster of tiny object-field accessors (tagged-pointer aware), saved
 * register-frame load/store helpers, no-op entry stubs, single-callee
 * forwarders, and one ARX/ChaCha-style 4-word state-mix primitive (0x356530). */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers referenced by this region (FUN_ addr in
 * comment; bodies reconstructed by their range workers).
 * ------------------------------------------------------------------ */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern void sk_free_masked(unsigned long ptr);                       /* FUN_003a25d4 */
extern void sk_swift_fatal(void);          /* FUN_001afe4c, noreturn */
extern unsigned long sk_state_dispatch(unsigned long a, unsigned long b,
                                       unsigned long c, unsigned long d,
                                       unsigned long e, unsigned long f); /* FUN_002a06c4 */
extern void sk_util_init_once(void);                                  /* FUN_0001df60 */
extern unsigned long sk_cpu_call0(unsigned long);                     /* FUN_00376820 */
extern void sk_cpu_call1(unsigned long);                              /* FUN_00376838 */
extern void sk_swift_destroy(unsigned long, unsigned long, unsigned long); /* FUN_001a89a8 */
extern unsigned long sk_state_dispatch2(void);                        /* FUN_002a4c98 */
extern void sk_dispatch0(void);                                       /* FUN_00310e08 */
extern void sk_obj_field_pair(void);                                  /* FUN_000a68f4 */

/* Object field accessors (tagged-pointer aware): these live in 0x31xxxx and
 * compute the address of a sub-object field. Pattern:
 *   if (p & 1) p = *(p & ~1);   (untag indirect ref)
 *   return p + off + *(int *)(p + off);
 */
extern long sk_obj_field_a0(unsigned long);  /* FUN_00310a44 -> field +0x40 */
extern long sk_obj_field_20(unsigned long);  /* FUN_00310a14 -> field +0x20 */
extern long sk_obj_field_30(unsigned long);  /* FUN_00310a74 -> field +0x30 */
extern long sk_obj_field_4c(unsigned long);  /* FUN_00310cd4 -> field +0x4c */
extern long sk_obj_field_34(unsigned long);  /* FUN_003192a8 -> field +0x34 */
extern long sk_obj_field_14(unsigned long);  /* FUN_0016799c -> field +0x14 */
extern long sk_obj_field_0c(unsigned long);  /* FUN_0008f6c0 -> field +0xc  */
extern long sk_obj_field_08(unsigned long);  /* FUN_0008f6f4 -> field +0x8  */

/*--------------------------------------------------------------------*/
/* FUN_00355914 @ 0x00355914   (est. sk_frame_splice)
 * Ghidra: void FUN_00355914(undefined8 *param_1)
 * Copies two words from the register-saved pointer x20 into param_1, then
 * records the source pointer and its second word at param_1[2]/[3]. This is a
 * small inlining/state-capture helper used by two object operations.
 * Confidence: medium (structural; no string match).
 */
void sk_frame_splice_00355914(word_t *dst)
{
    word_t w0;   /* *unaff_x20 */
    word_t w1;   /* unaff_x20[1] */
    /* unaff_x20: register-resident source pointer (not recovered by decompiler) */
    dst[2] = 0;      /* unaff_x20 */
    dst[3] = w1;
    dst[0] = w0;
    dst[1] = w1;
}

/*--------------------------------------------------------------------*/
/* FUN_00355928 @ 0x00355928   (est. sk_entry_noop)
 * Ghidra: void FUN_00355928(void)
 * Empty body — a placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355928(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355938 @ 0x00355938   (est. sk_frame_copy16)
 * Ghidra: void FUN_00355938(undefined8 *param_1,undefined8 *param_2)
 * Copies a 16-byte (two-word) value from param_2 to param_1.
 * Confidence: medium.
 */
void sk_frame_copy16_00355938(word_t *dst, const word_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
}

/*--------------------------------------------------------------------*/
/* FUN_00355948 @ 0x00355948   (est. sk_entry_noop)
 * Ghidra: void FUN_00355948(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355948(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355958 @ 0x00355958   (est. sk_frame_bottom)
 * Ghidra: long FUN_00355958(void)
 * Returns the address of the caller's frame-slot 0x68 below x29.
 * Confidence: medium.
 */
long sk_frame_bottom_00355958(void)
{
    /* unaff_x29 */
    return 0 - 0x68;
}

/*--------------------------------------------------------------------*/
/* FUN_00355968 @ 0x00355968   (est. sk_pair_make)
 * Ghidra: undefined1 [16] FUN_00355968(param_3, param_4)
 * Builds a 16-byte pair {param_3, param_4} and returns it in registers.
 * Confidence: medium.
 */
void sk_pair_make_stub_00355968(uint64_t *out, uint64_t lo, uint64_t hi)
{
    out[0] = lo;   /* param_3 */
    out[1] = hi;   /* param_4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355988 @ 0x00355988   (est. sk_frame_load_10)
 * Ghidra: undefined8 FUN_00355988(void)
 * Returns the word at x19 + 0x10.
 * Confidence: medium.
 */
word_t sk_frame_load_10_00355988(void)
{
    /* unaff_x19 */
    return *(word_t *)(0 + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00355998 @ 0x00355998   (est. sk_entry_noop)
 * Ghidra: void FUN_00355998(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355998(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003559a8 @ 0x003559a8   (est. sk_fatal_msg)
 * Ghidra: char * FUN_003559a8(void)
 * Returns the literal "Fatal error" message string at 0x5accd0.
 * Confidence: high (string s_Fatal_error_005accd0).
 */
const char *sk_fatal_msg(void)
{
    return (const char *)0x5accd0; /* "Fatal error" */
}

/*--------------------------------------------------------------------*/
/* FUN_003559bc @ 0x003559bc   (est. sk_entry_noop)
 * Ghidra: void FUN_003559bc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003559bc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003559c8 @ 0x003559c8   (est. sk_entry_noop)
 * Ghidra: void FUN_003559c8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003559c8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003559d8 @ 0x003559d8   (est. sk_frame_load_58)
 * Ghidra: undefined8 FUN_003559d8(void)
 * Returns the word at caller frame slot x29 - 0x58.
 * Confidence: medium.
 */
word_t sk_frame_load_58_003559d8(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x58);
}

/*--------------------------------------------------------------------*/
/* FUN_003559e4 @ 0x003559e4   (est. sk_obj_field_a0_forward)
 * Ghidra: void FUN_003559e4(void)
 * Forwarder: computes an object field at +0x40 (FUN_00310a44) and discards.
 * Confidence: medium.
 */
void sk_obj_field_a0_forward_003559e4(void)
{
    sk_obj_field_a0(0);  /* FUN_00310a44 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355a00 @ 0x00355a00   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a00(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a00(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355a14 @ 0x00355a14   (est. sk_frame_load_88)
 * Ghidra: undefined8 FUN_00355a14(void)
 * Returns the word at caller frame slot x29 - 0x88.
 * Confidence: medium.
 */
word_t sk_frame_load_88_00355a14(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x88);
}

/*--------------------------------------------------------------------*/
/* FUN_00355a20 @ 0x00355a20   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a20(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a20(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355a2c @ 0x00355a2c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a2c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a2c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355a40 @ 0x00355a40   (est. sk_obj_field_a0_forward)
 * Ghidra: void FUN_00355a40(void)
 * Forwarder: computes an object field at +0x40 (FUN_00310a44) and discards.
 * Confidence: medium.
 */
void sk_obj_field_a0_forward_00355a40(void)
{
    sk_obj_field_a0(0);  /* FUN_00310a44 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355a58 @ 0x00355a58   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a58(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a58(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355a64 @ 0x00355a64   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a64(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a64(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355a78 @ 0x00355a78   (est. sk_entry_noop)
 * Ghidra: void FUN_00355a78(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355a78(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355aa0 @ 0x00355aa0   (est. sk_entry_noop)
 * Ghidra: void FUN_00355aa0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355aa0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ab4 @ 0x00355ab4   (est. sk_obj_pair_fields)
 * Ghidra: void FUN_00355ab4(void)
 * Computes two adjacent object fields (FUN_0008f6c0 field +0xc, FUN_0008f6f4
 * field +0x8) and discards both results. Called from many object paths.
 * Confidence: medium.
 */
void sk_obj_pair_fields_00355ab4(void)
{
    sk_obj_field_0c(0);  /* FUN_0008f6c0 */
    sk_obj_field_08(0);  /* FUN_0008f6f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355ad0 @ 0x00355ad0   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ad0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ad0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355adc @ 0x00355adc   (est. sk_entry_noop)
 * Ghidra: void FUN_00355adc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355adc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ae8 @ 0x00355ae8   (est. sk_pair_cross)
 * Ghidra: undefined1 [16] FUN_00355ae8(undefined8 *param_1,undefined8 *param_2)
 * Builds a 16-byte pair { *param_1, *param_2 } from the two pointed-to words.
 * Confidence: medium.
 */
void sk_pair_cross_stub_00355ae8(uint64_t *out, word_t *a, word_t *b)
{
    out[0] = (uint64_t)a[0];
    out[1] = (uint64_t)b[0];
}

/*--------------------------------------------------------------------*/
/* FUN_00355af8 @ 0x00355af8   (est. sk_entry_noop)
 * Ghidra: void FUN_00355af8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355af8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b04 @ 0x00355b04   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b04(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b04(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b10 @ 0x00355b10   (est. sk_frame_load_58)
 * Ghidra: undefined8 FUN_00355b10(void)
 * Returns the word at caller frame slot x29 - 0x58.
 * Confidence: medium.
 */
word_t sk_frame_load_58_00355b10(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x58);
}

/*--------------------------------------------------------------------*/
/* FUN_00355b1c @ 0x00355b1c   (est. sk_frame_store_60)
 * Ghidra: void FUN_00355b1c(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x60.
 * Confidence: medium.
 */
void sk_frame_store_60_00355b1c(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x60) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355b28 @ 0x00355b28   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b28(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b28(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b38 @ 0x00355b38   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b38(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b38(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b48 @ 0x00355b48   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b48(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b48(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b58 @ 0x00355b58   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b58(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b58(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355b68 @ 0x00355b68   (est. sk_pair_from_x3x4)
 * Ghidra: undefined1 [16] FUN_00355b68(void)
 * Builds a 16-byte pair { in_x3, in_x4 } from the incoming register arguments.
 * Confidence: medium.
 */
uint64_t sk_pair_from_x3x4[2];
void sk_pair_from_x3x4_stub_00355b68(uint64_t *out, uint64_t lo, uint64_t hi)
{
    out[0] = lo;  /* in_x3 */
    out[1] = hi;  /* in_x4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355b74 @ 0x00355b74   (est. sk_obj_field_pair_forward)
 * Ghidra: void FUN_00355b74(void)
 * Forwarder to FUN_000a68f4 (object field-pair computation); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_pair_forward_00355b74(void)
{
    sk_obj_field_pair();  /* FUN_000a68f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355b90 @ 0x00355b90   (est. sk_entry_noop)
 * Ghidra: void FUN_00355b90(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355b90(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355bb8 @ 0x00355bb8   (est. sk_entry_noop)
 * Ghidra: void FUN_00355bb8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355bb8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355bc4 @ 0x00355bc4   (est. sk_frame_load_90)
 * Ghidra: undefined8 FUN_00355bc4(void)
 * Returns the word at caller frame slot x29 - 0x90.
 * Confidence: medium.
 */
word_t sk_frame_load_90_00355bc4(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x90);
}

/*--------------------------------------------------------------------*/
/* FUN_00355bd0 @ 0x00355bd0   (est. sk_entry_noop)
 * Ghidra: void FUN_00355bd0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355bd0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355bdc @ 0x00355bdc   (est. sk_entry_noop)
 * Ghidra: void FUN_00355bdc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355bdc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355be8 @ 0x00355be8   (est. sk_entry_noop)
 * Ghidra: void FUN_00355be8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355be8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355bf4 @ 0x00355bf4   (est. sk_frame_bottom_b0)
 * Ghidra: long FUN_00355bf4(void)
 * Returns the address of caller frame slot x29 - 0xb0.
 * Confidence: medium.
 */
long sk_frame_bottom_b0_00355bf4(void)
{
    /* unaff_x29 */
    return 0 - 0xb0;
}

/*--------------------------------------------------------------------*/
/* FUN_00355c00 @ 0x00355c00   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c00(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c00(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c10 @ 0x00355c10   (est. sk_obj_pair_from)
 * Ghidra: undefined1 [16] FUN_00355c10(long param_1)
 * Builds a pair { *(param_1 + 0x18), param_1 } — object pointer and its
 * 0x18-offset field.
 * Confidence: medium.
 */
void sk_obj_pair_from_stub_00355c10(uint64_t *out, long obj)
{
    out[0] = (uint64_t)*(word_t *)(obj + 0x18);
    out[1] = (uint64_t)obj;
}

/*--------------------------------------------------------------------*/
/* FUN_00355c1c @ 0x00355c1c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c1c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c1c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c28 @ 0x00355c28   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c28(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c28(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c34 @ 0x00355c34   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c34(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c34(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c44 @ 0x00355c44   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c44(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c44(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c58 @ 0x00355c58   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c58(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c58(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c68 @ 0x00355c68   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c68(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c68(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c78 @ 0x00355c78   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c78(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c78(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355c84 @ 0x00355c84   (est. sk_stack_frame_delta)
 * Ghidra: long FUN_00355c84(long param_1)
 * Returns the current stack pointer (0x0 frame base) minus param_1 — the
 * caller's stack-frame extent relative to param_1.
 * Confidence: medium.
 */
long sk_stack_frame_delta_00355c84(long param_1)
{
    return (long)0 - param_1; /* &stack0x0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355c94 @ 0x00355c94   (est. sk_entry_noop)
 * Ghidra: void FUN_00355c94(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355c94(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ca4 @ 0x00355ca4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ca4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ca4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355cb0 @ 0x00355cb0   (est. sk_frame_load_78)
 * Ghidra: undefined8 FUN_00355cb0(void)
 * Returns the word at caller frame slot x29 - 0x78.
 * Confidence: medium.
 */
word_t sk_frame_load_78_00355cb0(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x78);
}

/*--------------------------------------------------------------------*/
/* FUN_00355cbc @ 0x00355cbc   (est. sk_pass_x3)
 * Ghidra: undefined8 FUN_00355cbc(void)
 * Returns the incoming register argument x3 unchanged.
 * Confidence: medium.
 */
word_t sk_pass_x3_00355cbc(void)
{
    /* in_x3 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00355cc8 @ 0x00355cc8   (est. sk_entry_noop)
 * Ghidra: void FUN_00355cc8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355cc8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355cd4 @ 0x00355cd4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355cd4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355cd4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ce4 @ 0x00355ce4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ce4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ce4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355cf4 @ 0x00355cf4   (est. sk_const_one_hi)
 * Ghidra: undefined1 [16] FUN_00355cf4(void)
 * Returns the 16-byte constant (1 << 64) — a (hi=1, lo=0) pair.
 * Confidence: medium.
 */
void sk_const_one_hi_stub_00355cf4(uint64_t *out)
{
    out[0] = 0;       /* lo */
    out[1] = 1;       /* hi */
}

/*--------------------------------------------------------------------*/
/* FUN_00355d10 @ 0x00355d10   (est. sk_const_x6_hi)
 * Ghidra: undefined1 [16] FUN_00355d10(void)
 * Returns the pair { in_x6, 0 } shifted left 64 — effectively (in_x6 << 64).
 * Confidence: medium.
 */
uint64_t sk_const_x6_hi[2];
void sk_const_x6_hi_stub_00355d10(uint64_t *out, uint64_t val)
{
    out[0] = val;  /* in_x6, lo */
    out[1] = 0;    /* hi */
}

/*--------------------------------------------------------------------*/
/* FUN_00355d1c @ 0x00355d1c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d1c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d1c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d28 @ 0x00355d28   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d28(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d28(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d34 @ 0x00355d34   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d34(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d34(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d40 @ 0x00355d40   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d40(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d40(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d4c @ 0x00355d4c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d4c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d4c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d60 @ 0x00355d60   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d60(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d60(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d6c @ 0x00355d6c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d6c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d6c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d78 @ 0x00355d78   (est. sk_dispatch_forward)
 * Ghidra: void FUN_00355d78(void)
 * Forwarder to FUN_00310e08 (which calls FUN_00021480). Frequently invoked
 * from object/timer paths; result discarded.
 * Confidence: medium.
 */
void sk_dispatch_forward_00355d78(void)
{
    sk_dispatch0();  /* FUN_00310e08 -> FUN_00021480 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355d90 @ 0x00355d90   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d90(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d90(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355d9c @ 0x00355d9c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355d9c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355d9c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355da8 @ 0x00355da8   (est. sk_load_byte)
 * Ghidra: undefined1 FUN_00355da8(undefined1 *param_1)
 * Returns the byte pointed to by param_1.
 * Confidence: medium.
 */
uint8_t sk_load_byte_00355da8(const uint8_t *p)
{
    return *p;
}

/*--------------------------------------------------------------------*/
/* FUN_00355db4 @ 0x00355db4   (est. sk_frame_store_168)
 * Ghidra: void FUN_00355db4(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x168.
 * Confidence: medium.
 */
void sk_frame_store_168_00355db4(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x168) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355dc0 @ 0x00355dc0   (est. sk_frame_store_158)
 * Ghidra: void FUN_00355dc0(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x158.
 * Confidence: medium.
 */
void sk_frame_store_158_00355dc0(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x158) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355dcc @ 0x00355dcc   (est. sk_entry_noop)
 * Ghidra: void FUN_00355dcc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355dcc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355dd8 @ 0x00355dd8   (est. sk_pair_indexed)
 * Ghidra: undefined1 [16] FUN_00355dd8(void)
 * Builds a pair { frame[0x70], x20 + *(int *)(x19 + 0x28) } — a base pointer
 * plus an indexed offset from object x19.
 * Confidence: medium.
 */
void sk_pair_indexed_stub_00355dd8(uint64_t *out, long frame, long base, long idxobj)
{
    out[0] = (uint64_t)*(word_t *)(frame - 0x70);
    out[1] = (uint64_t)(base + *(int *)(idxobj + 0x28));
}

/*--------------------------------------------------------------------*/
/* FUN_00355dfc @ 0x00355dfc   (est. sk_frame_load_68)
 * Ghidra: undefined8 FUN_00355dfc(void)
 * Returns the word at caller frame slot x29 - 0x68.
 * Confidence: medium.
 */
word_t sk_frame_load_68_00355dfc(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x68);
}

/*--------------------------------------------------------------------*/
/* FUN_00355e08 @ 0x00355e08   (est. sk_obj_store0)
 * Ghidra: void FUN_00355e08(undefined8 param_1,undefined8 *param_2)
 * Stores *param_2 into the object slot pointed to by x19.
 * Confidence: medium.
 */
void sk_obj_store0_00355e08(word_t param_1, const word_t *src)
{
    /* unaff_x19 */
    *(word_t *)0 = src[0];
}

/*--------------------------------------------------------------------*/
/* FUN_00355e2c @ 0x00355e2c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355e2c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355e2c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355e38 @ 0x00355e38   (est. sk_frame_load_138)
 * Ghidra: undefined8 FUN_00355e38(void)
 * Returns the word at caller frame slot x29 - 0x138.
 * Confidence: medium.
 */
word_t sk_frame_load_138_00355e38(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x138);
}

/*--------------------------------------------------------------------*/
/* FUN_00355e44 @ 0x00355e44   (est. sk_entry_noop)
 * Ghidra: void FUN_00355e44(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355e44(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355e50 @ 0x00355e50   (est. sk_frame_load_x10_100)
 * Ghidra: undefined8 FUN_00355e50(void)
 * Returns the word at x10 - 0x100 (address supplied in register x10).
 * Confidence: medium.
 */
word_t sk_frame_load_x10_100_00355e50(void)
{
    /* in_x10 */
    return *(word_t *)(0 - 0x100);
}

/*--------------------------------------------------------------------*/
/* FUN_00355e5c @ 0x00355e5c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355e5c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355e5c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355e68 @ 0x00355e68   (est. sk_frame_store_x20_48)
 * Ghidra: void FUN_00355e68(void)
 * Stores register x20 into caller frame slot x29 - 0x48.
 * Confidence: medium.
 */
void sk_frame_store_x20_48_00355e68(void)
{
    /* unaff_x20, unaff_x29 */
    *(word_t *)(0 - 0x48) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00355e74 @ 0x00355e74   (est. sk_entry_noop)
 * Ghidra: void FUN_00355e74(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355e74(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355e80 @ 0x00355e80   (est. sk_frame_load_78)
 * Ghidra: undefined8 FUN_00355e80(void)
 * Returns the word at caller frame slot x29 - 0x78.
 * Confidence: medium.
 */
word_t sk_frame_load_78_00355e80(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x78);
}

/*--------------------------------------------------------------------*/
/* FUN_00355e8c @ 0x00355e8c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355e8c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355e8c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355e98 @ 0x00355e98   (est. sk_obj_store16)
 * Ghidra: void FUN_00355e98(undefined8 param_1,undefined8 *param_2)
 * Copies a 16-byte (two-word) value from param_2 into the object slots at x19.
 * Confidence: medium.
 */
void sk_obj_store16_00355e98(word_t param_1, const word_t *src)
{
    word_t w0 = src[0];
    /* unaff_x19 */
    ((word_t *)0)[1] = src[1];
    ((word_t *)0)[0] = w0;
}

/*--------------------------------------------------------------------*/
/* FUN_00355ea4 @ 0x00355ea4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ea4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ea4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355eb0 @ 0x00355eb0   (est. sk_entry_noop)
 * Ghidra: void FUN_00355eb0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355eb0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ebc @ 0x00355ebc   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ebc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ebc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ec8 @ 0x00355ec8   (est. sk_pair_indexed_30)
 * Ghidra: undefined1 [16] FUN_00355ec8(void)
 * Reads an int field at x21 + 0x30, stashes it in frame[0xc0], returns a pair
 * { x26 + field, frame[0xb0] } and re-stores x28 into frame[0xb0].
 * Confidence: medium.
 */
uint64_t sk_pair_indexed_30[2];
void sk_pair_indexed_30_stub_00355ec8(uint64_t *out, long frame, long base, long idxobj,
                             word_t newslot)
{
    int field = *(int *)(idxobj + 0x30);
    *(long *)(frame - 0xc0) = (long)field;
    out[1] = (uint64_t)*(word_t *)(frame - 0xb0);
    *(word_t *)(frame - 0xb0) = newslot;
    out[0] = (uint64_t)(base + field);
}

/*--------------------------------------------------------------------*/
/* FUN_00355eec @ 0x00355eec   (est. sk_entry_noop)
 * Ghidra: void FUN_00355eec(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355eec(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355ef8 @ 0x00355ef8   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ef8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ef8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f04 @ 0x00355f04   (est. sk_entry_noop)
 * Ghidra: void FUN_00355f04(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355f04(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f10 @ 0x00355f10   (est. sk_entry_noop)
 * Ghidra: void FUN_00355f10(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355f10(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f1c @ 0x00355f1c   (est. sk_pair_indexed_40)
 * Ghidra: undefined1 [16] FUN_00355f1c(void)
 * Reads an int field at x19 + 0x40, stashes it in frame[0xe8], returns a pair
 * { x27 + field, frame[0xe0] }.
 * Confidence: medium.
 */
uint64_t sk_pair_indexed_40[2];
void sk_pair_indexed_40_stub_00355f1c(uint64_t *out, long frame, long base, long idxobj)
{
    int field = *(int *)(idxobj + 0x40);
    *(long *)(frame - 0xe8) = (long)field;
    out[1] = (uint64_t)*(word_t *)(frame - 0xe0);
    out[0] = (uint64_t)(base + field);
}

/*--------------------------------------------------------------------*/
/* FUN_00355f40 @ 0x00355f40   (est. sk_frame_store_160)
 * Ghidra: void FUN_00355f40(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x160.
 * Confidence: medium.
 */
void sk_frame_store_160_00355f40(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x160) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355f4c @ 0x00355f4c   (est. sk_pair_two_slots)
 * Ghidra: undefined1 [16] FUN_00355f4c(void)
 * Returns a pair { x25 + frame[0xa0], x25 + frame[0x98] } — two indexed
 * additions on base x25.
 * Confidence: medium.
 */
void sk_pair_two_slots_stub_00355f4c(uint64_t *out, long frame, long base)
{
    out[1] = (uint64_t)(base + *(long *)(frame - 0xa0));
    out[0] = (uint64_t)(base + *(long *)(frame - 0x98));
}

/*--------------------------------------------------------------------*/
/* FUN_00355f70 @ 0x00355f70   (est. sk_entry_noop)
 * Ghidra: void FUN_00355f70(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355f70(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f7c @ 0x00355f7c   (est. sk_entry_noop)
 * Ghidra: void FUN_00355f7c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355f7c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f88 @ 0x00355f88   (est. sk_entry_noop)
 * Ghidra: void FUN_00355f88(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355f88(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355f94 @ 0x00355f94   (est. sk_frame_store_x22_120)
 * Ghidra: void FUN_00355f94(void)
 * Stores register x22 into caller frame slot x29 - 0x120.
 * Confidence: medium.
 */
void sk_frame_store_x22_120_00355f94(void)
{
    /* unaff_x22, unaff_x29 */
    *(word_t *)(0 - 0x120) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00355fa0 @ 0x00355fa0   (est. sk_destroy_attr)
 * Ghidra: void FUN_00355fa0(undefined8 param_1)
 * Calls FUN_001a89a8(param_1, 2, 1) — Swift-style object destroy with
 * attributes (kind 2, flags 1).
 * Confidence: medium.
 */
void sk_destroy_attr_00355fa0(word_t obj)
{
    sk_swift_destroy(obj, 2, 1);  /* FUN_001a89a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00355fac @ 0x00355fac   (est. sk_frame_store_100)
 * Ghidra: void FUN_00355fac(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x100.
 * Confidence: medium.
 */
void sk_frame_store_100_00355fac(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x100) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355fb8 @ 0x00355fb8   (est. sk_frame_store_110)
 * Ghidra: void FUN_00355fb8(undefined8 param_1)
 * Stores param_1 into caller frame slot x29 - 0x110.
 * Confidence: medium.
 */
void sk_frame_store_110_00355fb8(word_t val)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x110) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00355fc4 @ 0x00355fc4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355fc4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355fc4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00355fd0 @ 0x00355fd0   (est. sk_pair_store_indexed)
 * Ghidra: long FUN_00355fd0(void)
 * Loads pointer at frame[0x68], stores frame[0xa0] through it, and returns
 * that pointer advanced by the int field at x19 + 0x30.
 * Confidence: medium.
 */
long sk_pair_store_indexed_00355fd0(void)
{
    word_t **slot = (word_t **)(0 - 0x68);   /* unaff_x29 */
    int field = *(int *)(0 + 0x30);          /* unaff_x19 */
    **slot = *(word_t *)(0 - 0xa0);
    return (long)slot + (long)field;
}

/*--------------------------------------------------------------------*/
/* FUN_00355ff4 @ 0x00355ff4   (est. sk_entry_noop)
 * Ghidra: void FUN_00355ff4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00355ff4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356000 @ 0x00356000   (est. sk_obj_field_34_forward)
 * Ghidra: void FUN_00356000(void)
 * Forwarder to FUN_003192a8 (object field +0x34 accessor); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_34_forward_00356000(void)
{
    sk_obj_field_34(0);  /* FUN_003192a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00356018 @ 0x00356018   (est. sk_entry_noop)
 * Ghidra: void FUN_00356018(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356018(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356024 @ 0x00356024   (est. sk_entry_noop)
 * Ghidra: void FUN_00356024(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356024(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356030 @ 0x00356030   (est. sk_entry_noop)
 * Ghidra: void FUN_00356030(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356030(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035603c @ 0x0035603c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035603c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035603c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356048 @ 0x00356048   (est. sk_entry_noop)
 * Ghidra: void FUN_00356048(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356048(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356054 @ 0x00356054   (est. sk_entry_noop)
 * Ghidra: void FUN_00356054(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356054(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356060 @ 0x00356060   (est. sk_entry_noop)
 * Ghidra: void FUN_00356060(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356060(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035606c @ 0x0035606c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035606c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035606c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356078 @ 0x00356078   (est. sk_frame_load_a8)
 * Ghidra: undefined8 FUN_00356078(void)
 * Returns the word at caller frame slot x29 - 0xa8.
 * Confidence: medium.
 */
word_t sk_frame_load_a8_00356078(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0xa8);
}

/*--------------------------------------------------------------------*/
/* FUN_00356084 @ 0x00356084   (est. sk_entry_noop)
 * Ghidra: void FUN_00356084(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356084(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356090 @ 0x00356090   (est. sk_entry_noop)
 * Ghidra: void FUN_00356090(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356090(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035609c @ 0x0035609c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035609c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035609c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003560a8 @ 0x003560a8   (est. sk_frame_load_90)
 * Ghidra: undefined8 FUN_003560a8(void)
 * Returns the word at caller frame slot x29 - 0x90.
 * Confidence: medium.
 */
word_t sk_frame_load_90_003560a8(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x90);
}

/*--------------------------------------------------------------------*/
/* FUN_003560b4 @ 0x003560b4   (est. sk_entry_noop)
 * Ghidra: void FUN_003560b4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003560b4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003560c0 @ 0x003560c0   (est. sk_entry_noop)
 * Ghidra: void FUN_003560c0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003560c0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003560e4 @ 0x003560e4   (est. sk_entry_noop)
 * Ghidra: void FUN_003560e4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003560e4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003560f8 @ 0x003560f8   (est. sk_const_0xff)
 * Ghidra: undefined8 FUN_003560f8(void)
 * Returns the constant 0xff.
 * Confidence: medium.
 */
word_t sk_const_0xff_003560f8(void)
{
    return 0xff;
}

/*--------------------------------------------------------------------*/
/* FUN_00356104 @ 0x00356104   (est. sk_entry_noop)
 * Ghidra: void FUN_00356104(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356104(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356110 @ 0x00356110   (est. sk_entry_noop)
 * Ghidra: void FUN_00356110(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356110(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035611c @ 0x0035611c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035611c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035611c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356128 @ 0x00356128   (est. sk_entry_noop)
 * Ghidra: void FUN_00356128(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356128(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356134 @ 0x00356134   (est. sk_entry_noop)
 * Ghidra: void FUN_00356134(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356134(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356140 @ 0x00356140   (est. sk_entry_noop)
 * Ghidra: void FUN_00356140(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356140(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035614c @ 0x0035614c   (est. sk_obj_field_14_forward)
 * Ghidra: void FUN_0035614c(void)
 * Forwarder to FUN_0016799c (object field +0x14 accessor); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_14_forward_0035614c(void)
{
    sk_obj_field_14(0);  /* FUN_0016799c */
}

/*--------------------------------------------------------------------*/
/* FUN_00356164 @ 0x00356164   (est. sk_entry_noop)
 * Ghidra: void FUN_00356164(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356164(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356170 @ 0x00356170   (est. sk_entry_noop)
 * Ghidra: void FUN_00356170(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356170(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035617c @ 0x0035617c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035617c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035617c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356188 @ 0x00356188   (est. sk_entry_noop)
 * Ghidra: void FUN_00356188(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356188(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356194 @ 0x00356194   (est. sk_entry_noop)
 * Ghidra: void FUN_00356194(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356194(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003561a0 @ 0x003561a0   (est. sk_entry_noop)
 * Ghidra: void FUN_003561a0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003561a0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003561ac @ 0x003561ac   (est. sk_entry_noop)
 * Ghidra: void FUN_003561ac(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003561ac(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003561b8 @ 0x003561b8   (est. sk_frame_advance_counters)
 * Ghidra: void FUN_003561b8(undefined8 param_1)
 * Advances two caller frame counters by 8 and stores param_1 into frame[0x90];
 * sets frame[0xb8] = frame[0xc0] + 0x10.
 * Confidence: medium.
 */
void sk_frame_advance_counters_003561b8(word_t param_1)
{
    /* unaff_x29 */
    long l = *(long *)(0 - 0xc0);
    *(long *)(0 - 0x98) = *(long *)(0 - 0x98) + 8;
    *(word_t *)(0 - 0x90) = param_1;
    *(long *)(0 - 0xc0) = l + 8;
    *(long *)(0 - 0xb8) = l + 0x10;
}

/*--------------------------------------------------------------------*/
/* FUN_003561dc @ 0x003561dc   (est. sk_entry_noop)
 * Ghidra: void FUN_003561dc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003561dc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003561e8 @ 0x003561e8   (est. sk_entry_noop)
 * Ghidra: void FUN_003561e8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003561e8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003561f4 @ 0x003561f4   (est. sk_entry_noop)
 * Ghidra: void FUN_003561f4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003561f4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356200 @ 0x00356200   (est. sk_entry_noop)
 * Ghidra: void FUN_00356200(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356200(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035620c @ 0x0035620c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035620c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035620c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356218 @ 0x00356218   (est. sk_entry_noop)
 * Ghidra: void FUN_00356218(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356218(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356224 @ 0x00356224   (est. sk_entry_noop)
 * Ghidra: void FUN_00356224(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356224(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356230 @ 0x00356230   (est. sk_entry_noop)
 * Ghidra: void FUN_00356230(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356230(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035623c @ 0x0035623c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035623c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035623c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356248 @ 0x00356248   (est. sk_entry_noop)
 * Ghidra: void FUN_00356248(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356248(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356254 @ 0x00356254   (est. sk_frame_load_58)
 * Ghidra: undefined8 FUN_00356254(void)
 * Returns the word at caller frame slot x29 - 0x58.
 * Confidence: medium.
 */
word_t sk_frame_load_58_00356254(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0x58);
}

/*--------------------------------------------------------------------*/
/* FUN_00356260 @ 0x00356260   (est. sk_entry_noop)
 * Ghidra: void FUN_00356260(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356260(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035626c @ 0x0035626c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035626c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035626c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356278 @ 0x00356278   (est. sk_entry_noop)
 * Ghidra: void FUN_00356278(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356278(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356284 @ 0x00356284   (est. sk_entry_noop)
 * Ghidra: void FUN_00356284(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356284(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356290 @ 0x00356290   (est. sk_entry_noop)
 * Ghidra: void FUN_00356290(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356290(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035629c @ 0x0035629c   (est. sk_obj_fields_30)
 * Ghidra: void FUN_0035629c(void)
 * Computes an object field at +0x30 (FUN_00310a74) then calls the one-time
 * init FUN_0001df60. Result of the field accessor is discarded.
 * Confidence: medium.
 */
void sk_obj_fields_30_0035629c(void)
{
    sk_obj_field_30(0);  /* FUN_00310a74 */
    sk_util_init_once(); /* FUN_0001df60 */
}

/*--------------------------------------------------------------------*/
/* FUN_003562bc @ 0x003562bc   (est. sk_entry_noop)
 * Ghidra: void FUN_003562bc(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562bc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003562c8 @ 0x003562c8   (est. sk_entry_noop)
 * Ghidra: void FUN_003562c8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562c8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003562d4 @ 0x003562d4   (est. sk_entry_noop)
 * Ghidra: void FUN_003562d4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562d4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003562e0 @ 0x003562e0   (est. sk_entry_noop)
 * Ghidra: void FUN_003562e0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562e0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003562ec @ 0x003562ec   (est. sk_entry_noop)
 * Ghidra: void FUN_003562ec(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562ec(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003562f8 @ 0x003562f8   (est. sk_entry_noop)
 * Ghidra: void FUN_003562f8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003562f8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356304 @ 0x00356304   (est. sk_entry_noop)
 * Ghidra: void FUN_00356304(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356304(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356310 @ 0x00356310   (est. sk_entry_noop)
 * Ghidra: void FUN_00356310(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356310(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035631c @ 0x0035631c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035631c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035631c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356328 @ 0x00356328   (est. sk_entry_noop)
 * Ghidra: void FUN_00356328(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356328(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356334 @ 0x00356334   (est. sk_entry_noop)
 * Ghidra: void FUN_00356334(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356334(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356340 @ 0x00356340   (est. sk_const_10)
 * Ghidra: undefined1 [16] FUN_00356340(void)
 * Returns the 16-byte constant 10 (lo=10, hi=0).
 * Confidence: medium.
 */
uint64_t sk_const_10[2];
void sk_const_10_stub_00356340(uint64_t *out)
{
    out[0] = 10;   /* lo */
    out[1] = 0;    /* hi */
}

/*--------------------------------------------------------------------*/
/* FUN_0035634c @ 0x0035634c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035634c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035634c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356358 @ 0x00356358   (est. sk_entry_noop)
 * Ghidra: void FUN_00356358(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356358(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356364 @ 0x00356364   (est. sk_obj_cap_align)
 * Ghidra: long FUN_00356364(void)
 * Masks x19 to the 56-bit canonical range and adds 0x20 (an object/cap
 * alignment helper).
 * Confidence: medium.
 */
long sk_obj_cap_align_00356364(void)
{
    /* unaff_x19 */
    return (0 & 0xfffffffffffffff) + 0x20;
}

/*--------------------------------------------------------------------*/
/* FUN_00356370 @ 0x00356370   (est. sk_entry_noop)
 * Ghidra: void FUN_00356370(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356370(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035638c @ 0x0035638c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035638c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035638c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003563a8 @ 0x003563a8   (est. sk_entry_noop)
 * Ghidra: void FUN_003563a8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003563a8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003563c4 @ 0x003563c4   (est. sk_entry_noop)
 * Ghidra: void FUN_003563c4(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003563c4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003563e0 @ 0x003563e0   (est. sk_entry_noop)
 * Ghidra: void FUN_003563e0(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003563e0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003563fc @ 0x003563fc   (est. sk_state_dispatch_forward)
 * Ghidra: void FUN_003563fc(void)
 * Forwarder to FUN_002a4c98 (state/object dispatch); result discarded.
 * Confidence: medium.
 */
void sk_state_dispatch_forward_003563fc(void)
{
    sk_state_dispatch2();  /* FUN_002a4c98 */
}

/*--------------------------------------------------------------------*/
/* FUN_00356408 @ 0x00356408   (est. sk_swift_fatal_stub)
 * Ghidra: void FUN_00356408(void)  [noreturn]
 * Unconditional fatal-error path (FUN_001afe4c); never returns.
 * Confidence: medium.
 */
void sk_swift_fatal_stub_00356408(void)
{
    sk_swift_fatal();  /* FUN_001afe4c, noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_0035642c @ 0x0035642c   (est. sk_state_dispatch_swapped)
 * Ghidra: void FUN_0035642c(6 params)
 * Reorders and forwards six arguments to FUN_002a06c4 (state dispatcher):
 * (p2,p1,p4,p3,p6,p5).
 * Confidence: medium.
 */
void sk_state_dispatch_swapped_0035642c(word_t p1, word_t p2, word_t p3, word_t p4,
                               word_t p5, word_t p6)
{
    sk_state_dispatch(p2, p1, p4, p3, p6, p5);  /* FUN_002a06c4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00356454 @ 0x00356454   (est. sk_entry_noop)
 * Ghidra: void FUN_00356454(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356454(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035646c @ 0x0035646c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035646c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035646c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035647c @ 0x0035647c   (est. sk_obj_field_4c_forward)
 * Ghidra: void FUN_0035647c(void)
 * Forwarder to FUN_00310cd4 (object field +0x4c accessor); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_4c_forward_0035647c(void)
{
    sk_obj_field_4c(0);  /* FUN_00310cd4 */
}

/*--------------------------------------------------------------------*/
/* FUN_003564a4 @ 0x003564a4   (est. sk_obj_field_20_forward)
 * Ghidra: void FUN_003564a4(void)
 * Forwarder to FUN_00310a14 (object field +0x20 accessor); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_20_forward_003564a4(void)
{
    sk_obj_field_20(0);  /* FUN_00310a14 */
}

/*--------------------------------------------------------------------*/
/* FUN_003564d0 @ 0x003564d0   (est. sk_obj_field_08_forward)
 * Ghidra: void FUN_003564d0(void)
 * Forwarder to FUN_0008f6f4 (object field +0x8 accessor); result discarded.
 * Confidence: medium.
 */
void sk_obj_field_08_forward_003564d0(void)
{
    sk_obj_field_08(0);  /* FUN_0008f6f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_003564e8 @ 0x003564e8   (est. sk_entry_noop)
 * Ghidra: void FUN_003564e8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003564e8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356508 @ 0x00356508   (est. sk_free_masked_forward)
 * Ghidra: void FUN_00356508(void)
 * Forwarder to FUN_003a25d4: frees a pointer masked to 61 bits (sk_free on
 * masked value). Called from several destroy paths.
 * Confidence: medium.
 */
void sk_free_masked_forward_00356508(void)
{
    sk_free_masked(0);  /* FUN_003a25d4 -> sk_free(FUN_0036b118) */
}

/*--------------------------------------------------------------------*/
/* FUN_00356518 @ 0x00356518   (est. sk_cpu_call_forward)
 * Ghidra: void FUN_00356518(void)
 * Forwarder to FUN_00376820 (per-CPU call dispatch). Called from many per-CPU
 * object paths.
 * Confidence: medium.
 */
void sk_cpu_call_forward_00356518(void)
{
    sk_cpu_call0(0);  /* FUN_00376820 -> FUN_00376838 */
}

/*--------------------------------------------------------------------*/
/* FUN_00356524 @ 0x00356524   (est. sk_swift_fatal_stub)
 * Ghidra: void FUN_00356524(void)  [noreturn]
 * Unconditional fatal-error path (FUN_001afe4c); never returns.
 * Confidence: medium.
 */
void sk_swift_fatal_stub_00356524(void)
{
    sk_swift_fatal();  /* FUN_001afe4c, noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_00356530 @ 0x00356530   (est. sk_state_mix)
 * Ghidra: void FUN_00356530(void)
 * ARX/ChaCha-style 4-word state mixer. Updates the four state words at
 * x20+8..x20+0x20 using add/rotate/xor operations on a seed word (in_x12) and
 * the previous state. Used by the string/map hash routines FUN_0022995c and
 * FUN_002299cc. Faithful transcription:
 * Confidence: medium.
 */
void sk_state_mix_00356530(void)
{
    /* unaff_x20 = state base; in_x12 = seed word */
    word_t s1 = 0 + 0x20;      /* *(x20+0x20) ^ in_x12 */
    word_t s0 = *(word_t *)(0 + 0x10);
    word_t a = s0 + *(long *)(0 + 8);
    word_t b = a ^ (s0 >> 0x33 | s0 << 0xd);
    word_t c = *(long *)(0 + 0x18) + s1;
    word_t d = c + b;
    word_t e = c ^ (s1 >> 0x30 | s1 << 0x10);
    word_t f = e + (a >> 0x20 | a << 0x20);
    *(word_t *)(0 + 0x18) = d >> 0x20 | d << 0x20;
    *(word_t *)(0 + 0x20) = f ^ (e >> 0x2b | e << 0x15);
    *(word_t *)(0 + 8) = f ^ 0;       /* ^ in_x12 */
    *(word_t *)(0 + 0x10) = d ^ (b >> 0x2f | b << 0x11);
}

/*--------------------------------------------------------------------*/
/* FUN_00356578 @ 0x00356578   (est. sk_swift_fatal_stub)
 * Ghidra: void FUN_00356578(void)  [noreturn]
 * Unconditional fatal-error path (FUN_001afe4c); never returns.
 * Confidence: medium.
 */
void sk_swift_fatal_stub_00356578(void)
{
    sk_swift_fatal();  /* FUN_001afe4c, noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_00356584 @ 0x00356584   (est. sk_entry_noop)
 * Ghidra: void FUN_00356584(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356584(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356590 @ 0x00356590   (est. sk_entry_noop)
 * Ghidra: void FUN_00356590(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356590(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003565a8 @ 0x003565a8   (est. sk_entry_noop)
 * Ghidra: void FUN_003565a8(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_003565a8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_003565c0 @ 0x003565c0   (est. sk_pair_indexed_complex)
 * Ghidra: undefined1 [16] FUN_003565c0(long param_1)
 * Builds a pair { x22 + param_1, frame[0xe8] + int field from deref }. The
 * inner address is computed through x9-relative indirect load.
 * Confidence: medium.
 */
void sk_pair_indexed_complex_stub_003565c0(uint64_t *out, long frame, long base,
                                  long extra, word_t addend)
{
    out[1] = (uint64_t)(base + extra);       /* x22 + param_1 */
    out[0] = (uint64_t)(*(long *)(frame - 0xe8)
                      + (long)*(int *)(*(long *)(0 - 0x100) + 0x24));
}

/*--------------------------------------------------------------------*/
/* FUN_003565e0 @ 0x003565e0   (est. sk_frame_multi_store)
 * Ghidra: void FUN_003565e0(undefined8 param_1)
 * Stores several pointers into caller frame slots: x25 at 0xe0, x25+8 at 0xa8,
 * param_1 at 0xa0, x28+0x10 at 0xd8, x28+8 at 0xd0. Frame-region pointer
 * population helper.
 * Confidence: medium.
 */
void sk_frame_multi_store_003565e0(word_t param_1)
{
    /* unaff_x25, unaff_x28, unaff_x29 */
    *(long *)(0 - 0xe0) = 0;       /* x25 */
    *(long *)(0 - 0xa8) = 0 + 8;   /* x25 + 8 */
    *(word_t *)(0 - 0xa0) = param_1;
    *(long *)(0 - 0xd8) = 0 + 0x10; /* x28 + 0x10 */
    *(long *)(0 - 0xd0) = 0 + 8;    /* x28 + 8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00356600 @ 0x00356600   (est. sk_entry_noop)
 * Ghidra: void FUN_00356600(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356600(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0035660c @ 0x0035660c   (est. sk_aligned_round)
 * Ghidra: ulong FUN_0035660c(long param_1)
 * Rounds an address: ((param_1 + x19 & ~x12) + x11 + x9) & ~x9 — a page/cap
 * alignment round-up helper using register-supplied alignment constants.
 * Confidence: medium.
 */
word_t sk_aligned_round_0035660c(long param_1)
{
    /* in_x9, in_x11, in_x12, unaff_x19 */
    return (param_1 + 0 & ~0) + 0 + 0 & ~0;
}

/*--------------------------------------------------------------------*/
/* FUN_0035662c @ 0x0035662c   (est. sk_entry_noop)
 * Ghidra: void FUN_0035662c(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_0035662c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356638 @ 0x00356638   (est. sk_entry_noop)
 * Ghidra: void FUN_00356638(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356638(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356644 @ 0x00356644   (est. sk_obj_load_next)
 * Ghidra: void FUN_00356644(void)
 * Stores the word at (frame[0x70] + 8) into frame[0x88] — a linked next-pointer
 * load into a local slot.
 * Confidence: medium.
 */
void sk_obj_load_next_00356644(void)
{
    /* unaff_x29 */
    *(word_t *)(0 - 0x88) = *(word_t *)(*(long *)(0 - 0x70) + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00356664 @ 0x00356664   (est. sk_entry_noop)
 * Ghidra: void FUN_00356664(void)
 * Empty body — placeholder/no-op entry point.
 * Confidence: low.
 */
void sk_entry_noop_00356664(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00356670 @ 0x00356670   (est. sk_frame_load_a8)
 * Ghidra: undefined8 FUN_00356670(void)
 * Returns the word at caller frame slot x29 - 0xa8.
 * Confidence: medium.
 */
word_t sk_frame_load_a8_00356670(void)
{
    /* unaff_x29 */
    return *(word_t *)(0 - 0xa8);
}
