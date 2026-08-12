/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 26: 0x357440-0x358268 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/*--------------------------------------------------------------------*/
/* FUN_00357440 @ 0x00357440   (est. sk_syscall_nop_7440)
 * Ghidra: void FUN_00357440(void)
 * Empty body (single RET) — an unused/no-op slot in the syscall dispatch
 * region. No side effects.
 * Confidence: medium.
 */
void sk_syscall_nop_7440(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035745c @ 0x0035745c   (est. sk_syscall_nop_745c)
 * Ghidra: void FUN_0035745c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_745c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357468 @ 0x00357468   (est. sk_regpair_store_10_20)
 * Ghidra: void FUN_00357468(void)
 * Fragment that writes a word to the object at [ctx+0x10] and a byte to
 * [ctx+reg+0x20]. Registers x19/x20/w23/x24 hold caller-preserved values
 * (context/object pointers) so the real signature is hidden; this is a
 * mid-function slice of a larger routine.
 * Confidence: low (register fragment).
 */
void sk_regpair_store_10_20(void)
{
    long ctx = 0;        /* x19: object/context base (unaff) */
    uint64_t val = 0;    /* x20: word payload (unaff) */
    char delta = 0;      /* w23: byte payload-1 (unaff) */
    long off = 0;        /* x24: small offset (unaff) */
    *(uint64_t *)(ctx + 0x10) = val;
    *(char *)(ctx + off + 0x20) = delta - 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0035748c @ 0x0035748c   (est. sk_syscall_nop_748c)
 * Ghidra: void FUN_0035748c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_748c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357498 @ 0x00357498   (est. sk_reg_pair_7498)
 * Ghidra: undefined1 [16] FUN_00357498(void)
 * Returns a 16-byte pair: hi = saved word at [fp-0xb8]; lo = x26 + s32[x21+0x50].
 * Fragment reading caller-preserved registers.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_reg_pair_7498(void)
{
    long fp = 0;    /* x29 frame (unaff) */
    long base = 0;  /* x21 (unaff) */
    long add = 0;   /* x26 (unaff) */
    cl4_result_t r;
    r.hi = *(uint64_t *)(fp - 0xb8);
    r.lo = add + (int)*(uint32_t *)(base + 0x50);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003574b4 @ 0x003574b4   (est. sk_copy_partial_attr)
 * Ghidra: void FUN_003574b4(long param_1,long param_2)
 * Copies three small fields from source to destination: bytes at +1, +2 and
 * +8. Partial attribute/status field copy.
 * Confidence: medium.
 */
void sk_copy_partial_attr(uint8_t *dst, const uint8_t *src)
{
    dst[1] = src[1];
    dst[2] = src[2];
    dst[8] = src[8];
}

/*--------------------------------------------------------------------*/
/* FUN_003574d0 @ 0x003574d0   (est. sk_syscall_nop_74d0)
 * Ghidra: void FUN_003574d0(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_74d0(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003574ec @ 0x003574ec   (est. sk_syscall_nop_74ec)
 * Ghidra: void FUN_003574ec(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_74ec(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357508 @ 0x00357508   (est. sk_load_word_fp_68)
 * Ghidra: undefined8 FUN_00357508(void)
 * Returns the saved word at [fp-0x68]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_68(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x68);
}

/*--------------------------------------------------------------------*/
/* FUN_00357514 @ 0x00357514   (est. sk_stack_pair_7514)
 * Ghidra: undefined1 [16] FUN_00357514(void)
 * Returns a 16-byte pair of two stack addresses (0x140, 0x170).
 * Fragment; likely address-of pair for an out-parameter tuple.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_stack_pair_7514(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0) + 0x170;
    r.hi = (uint64_t)__builtin_frame_address(0) + 0x140;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00357540 @ 0x00357540   (est. sk_syscall_nop_7540)
 * Ghidra: void FUN_00357540(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7540(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035754c @ 0x0035754c   (est. sk_syscall_nop_754c)
 * Ghidra: void FUN_0035754c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_754c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357558 @ 0x00357558   (est. sk_syscall_nop_7558)
 * Ghidra: void FUN_00357558(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7558(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357564 @ 0x00357564   (est. sk_forward_31a29c)
 * Ghidra: void FUN_00357564(void)
 * Trivial forwarder to FUN_0031a29c (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_31a29c(void)
{
    extern void sk_helper_31a29c(void);  /* FUN_0031a29c */
    sk_helper_31a29c();
}

/*--------------------------------------------------------------------*/
/* FUN_00357584 @ 0x00357584   (est. sk_store_attr_triple)
 * Ghidra: void FUN_00357584(long param_1)
 * Calls FUN_0024a428(fp-0xa0, param_1, param_1 + x26): stores a triple of
 * related pointers (base, base+delta). Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_attr_triple(long base)
{
    long fp = 0;   /* x29 frame (unaff) */
    long delta = 0;/* x26 (unaff) */
    extern void sk_helper_24a428(uint64_t *dst, long a, long b);  /* FUN_0024a428 */
    sk_helper_24a428((uint64_t *)(fp - 0xa0), base, base + delta);
}

/*--------------------------------------------------------------------*/
/* FUN_003575a4 @ 0x003575a4   (est. sk_syscall_nop_75a4)
 * Ghidra: void FUN_003575a4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_75a4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003575b0 @ 0x003575b0   (est. sk_global_ptr_7d48)
 * Ghidra: undefined * FUN_003575b0(void)
 * Returns pointer to global data DAT_004e7d48.
 * Confidence: high (data address known).
 */
void *sk_global_ptr_7d48(void)
{
    static uint8_t g_7d48;   /* DAT_004e7d48 */
    return &g_7d48;
}

/*--------------------------------------------------------------------*/
/* FUN_003575bc @ 0x003575bc   (est. sk_forward_1679fc)
 * Ghidra: void FUN_003575bc(void)
 * Trivial forwarder to FUN_001679fc (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_1679fc(void)
{
    extern void sk_helper_1679fc(void);  /* FUN_001679fc */
    sk_helper_1679fc();
}

/*--------------------------------------------------------------------*/
/* FUN_003575d4 @ 0x003575d4   (est. sk_copy_word_28)
 * Ghidra: void FUN_003575d4(void)
 * Copies the word at [src+0x28] into [dst+0x28]. Fragment (registers).
 * Confidence: low (register fragment).
 */
void sk_copy_word_28(void)
{
    long dst = 0;  /* x19 (unaff) */
    long src = 0;  /* x20 (unaff) */
    *(uint64_t *)(dst + 0x28) = *(uint64_t *)(src + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_003575f0 @ 0x003575f0   (est. sk_store_5bytes)
 * Ghidra: void FUN_003575f0(void)
 * Writes a 32-bit word plus one byte into the object at x19 (a 5-byte packed
 * field). Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_5bytes(void)
{
    uint32_t *obj = 0;   /* x19 (unaff) */
    uint32_t lo = 0;     /* stack 0x48 (unaff) */
    uint8_t hi = 0;      /* stack 0x4c (unaff) */
    obj[0] = lo;
    *(uint8_t *)(obj + 1) = hi;
}

/*--------------------------------------------------------------------*/
/* FUN_0035760c @ 0x0035760c   (est. sk_syscall_nop_760c)
 * Ghidra: void FUN_0035760c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_760c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357628 @ 0x00357628   (est. sk_cap_slot_size)
 * Ghidra: long FUN_00357628(void)
 * Returns (x3 & 0xfffffffffffffff) + 0x20: masks a capability word to its
 * low 52 bits and adds the 0x20 object-header size. Likely computes an object
 * size/end from a size field (x3 held in a caller register).
 * Confidence: low (register fragment).
 */
long sk_cap_slot_size(void)
{
    uint64_t size_field = 0;  /* x3 (unaff) */
    return (long)((size_field & 0xfffffffffffffffULL) + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_00357634 @ 0x00357634   (est. sk_load_word_fp_290)
 * Ghidra: undefined8 FUN_00357634(void)
 * Returns the saved word at [fp-0x290]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_290(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x290);
}

/*--------------------------------------------------------------------*/
/* FUN_00357640 @ 0x00357640   (est. sk_syscall_nop_7640)
 * Ghidra: void FUN_00357640(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7640(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035764c @ 0x0035764c   (est. sk_forward_31d6d8)
 * Ghidra: void FUN_0035764c(void)
 * Trivial forwarder to FUN_0031d6d8 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_31d6d8(void)
{
    extern void sk_helper_31d6d8(void);  /* FUN_0031d6d8 */
    sk_helper_31d6d8();
}

/*--------------------------------------------------------------------*/
/* FUN_00357664 @ 0x00357664   (est. sk_load_word_fp_68b)
 * Ghidra: undefined8 FUN_00357664(void)
 * Returns the saved word at [fp-0x68]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_68b(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x68);
}

/*--------------------------------------------------------------------*/
/* FUN_00357670 @ 0x00357670   (est. sk_store_2words)
 * Ghidra: void FUN_00357670(undefined8 param_1,undefined4 param_2)
 * Stores a word and a 32-bit value into the 12-byte record at x19.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_2words(uint64_t word, uint32_t lo)
{
    uint64_t *rec = 0;  /* x19 (unaff) */
    rec[0] = word;
    *(uint32_t *)(rec + 1) = lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0035767c @ 0x0035767c   (est. sk_syscall_nop_767c)
 * Ghidra: void FUN_0035767c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_767c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357688 @ 0x00357688   (est. sk_syscall_nop_7688)
 * Ghidra: void FUN_00357688(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7688(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357694 @ 0x00357694   (est. sk_store_4words)
 * Ghidra: void FUN_00357694(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Stores four consecutive words into the 32-byte record at x24.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_4words(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t *rec = 0;  /* x24 (unaff) */
    rec[0] = a;
    rec[1] = b;
    rec[2] = c;
    rec[3] = d;
}

/*--------------------------------------------------------------------*/
/* FUN_003576a0 @ 0x003576a0   (est. sk_store_5bytes_a0)
 * Ghidra: void FUN_003576a0(void)
 * Writes a 32-bit word plus one byte into the object at x19 (a 5-byte packed
 * field). Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_5bytes_a0(void)
{
    uint32_t *obj = 0;   /* x19 (unaff) */
    uint32_t lo = 0;     /* stack 0x48 (unaff) */
    uint8_t hi = 0;      /* stack 0x4c (unaff) */
    obj[0] = lo;
    *(uint8_t *)(obj + 1) = hi;
}

/*--------------------------------------------------------------------*/
/* FUN_003576bc @ 0x003576bc   (est. sk_syscall_nop_76bc)
 * Ghidra: void FUN_003576bc(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_76bc(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003576c8 @ 0x003576c8   (est. sk_cap_slot_size_c8)
 * Ghidra: long FUN_003576c8(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Returns (param_3 & 0xfffffffffffffff) + 0x20: object size + header.
 * Confidence: medium.
 */
long sk_cap_slot_size_c8(uint64_t a, uint64_t b, uint64_t size_field)
{
    (void)a; (void)b;
    return (long)((size_field & 0xfffffffffffffffULL) + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_003576dc @ 0x003576dc   (est. sk_bswap128)
 * Ghidra: undefined1 [16] FUN_003576dc(ulong param_1,ulong param_2)
 * 128-bit byte-swap (endian flip) of the two-word value {param_1, param_2}:
 * each 64-bit half is byte-reversed (8/16/32-bit swaps) and the two halves
 * are exchanged. Likely converts between host and on-wire/disk byte order.
 * Confidence: high (unambiguous bswap sequence).
 */
cl4_result_t sk_bswap128(uint64_t lo, uint64_t hi)
{
    uint64_t r0, r1;
    r0 = (hi & 0xff00ff00ff00ff00ULL) >> 8 | (hi & 0xff00ff00ff00ffULL) << 8;
    r0 = (r0 & 0xffff0000ffff0000ULL) >> 16 | (r0 & 0xffff0000ffffULL) << 16;
    r1 = (lo & 0xff00ff00ff00ff00ULL) >> 8 | (lo & 0xff00ff00ff00ffULL) << 8;
    r1 = (r1 & 0xffff0000ffff0000ULL) >> 16 | (r1 & 0xffff0000ffffULL) << 16;
    r0 = r0 >> 32 | r0 << 32;
    r1 = r1 >> 32 | r1 << 32;
    return (cl4_result_t){ .lo = r0, .hi = r1 };
}

/*--------------------------------------------------------------------*/
/* FUN_003576ec @ 0x003576ec   (est. sk_syscall_nop_76ec)
 * Ghidra: void FUN_003576ec(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_76ec(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357710 @ 0x00357710   (est. sk_load_word_fp_98)
 * Ghidra: undefined8 FUN_00357710(void)
 * Returns the saved word at [fp-0x98]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_98(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x98);
}

/*--------------------------------------------------------------------*/
/* FUN_0035772c @ 0x0035772c   (est. sk_syscall_nop_772c)
 * Ghidra: void FUN_0035772c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_772c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357748 @ 0x00357748   (est. sk_syscall_nop_7748)
 * Ghidra: void FUN_00357748(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7748(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357754 @ 0x00357754   (est. sk_global_ptr_7d40)
 * Ghidra: undefined * FUN_00357754(void)
 * Returns pointer to global data DAT_004e7d40.
 * Confidence: high (data address known).
 */
void *sk_global_ptr_7d40(void)
{
    static uint8_t g_7d40;   /* DAT_004e7d40 */
    return &g_7d40;
}

/*--------------------------------------------------------------------*/
/* FUN_00357760 @ 0x00357760   (est. sk_syscall_nop_7760)
 * Ghidra: void FUN_00357760(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7760(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035776c @ 0x0035776c   (est. sk_pair_2_3)
 * Ghidra: undefined1 [16] FUN_0035776c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Returns a 16-byte pair {param_2, param_3} (param_1 unused). Pair
 * constructor.
 * Confidence: medium.
 */
cl4_result_t sk_pair_2_3(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a;
    return (cl4_result_t){ .lo = b, .hi = c };
}

/*--------------------------------------------------------------------*/
/* FUN_00357788 @ 0x00357788   (est. sk_syscall_nop_7788)
 * Ghidra: void FUN_00357788(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7788(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357794 @ 0x00357794   (est. sk_syscall_nop_7794)
 * Ghidra: void FUN_00357794(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7794(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003577a0 @ 0x003577a0   (est. sk_cap_slot_size_a0)
 * Ghidra: long FUN_003577a0(void)
 * Returns (x21 & 0xfffffffffffffff) + 0x20: object size + header, with the
 * size field in a caller register (x21). Fragment.
 * Confidence: low (register fragment).
 */
long sk_cap_slot_size_a0(void)
{
    uint64_t size_field = 0;  /* x21 (unaff) */
    return (long)((size_field & 0xfffffffffffffffULL) + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_003577b4 @ 0x003577b4   (est. sk_syscall_nop_77b4)
 * Ghidra: void FUN_003577b4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_77b4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003577c0 @ 0x003577c0   (est. sk_syscall_nop_77c0)
 * Ghidra: void FUN_003577c0(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_77c0(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003577cc @ 0x003577cc   (est. sk_forward_1f99f4)
 * Ghidra: void FUN_003577cc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Forwards param_1, param_3, param_5 to FUN_001f99f4 (reordered args).
 * Confidence: medium.
 */
void sk_forward_1f99f4(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)b; (void)d;
    extern void sk_helper_1f99f4(uint64_t a, uint64_t c, uint64_t e);  /* FUN_001f99f4 */
    sk_helper_1f99f4(a, c, e);
}

/*--------------------------------------------------------------------*/
/* FUN_003577e4 @ 0x003577e4   (est. sk_syscall_nop_77e4)
 * Ghidra: void FUN_003577e4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_77e4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003577f0 @ 0x003577f0   (est. sk_copy_status_fields)
 * Ghidra: void FUN_003577f0(undefined8 param_1,long param_2)
 * Copies five fields (+0x10..+0x28) from param_2 into the object at x19.
 * Status/state record copy fragment.
 * Confidence: low (register fragment).
 */
void sk_copy_status_fields(uint64_t param_1, const uint8_t *src)
{
    (void)param_1;
    uint8_t *dst = 0;  /* x19 (unaff) */
    uint64_t w = *(uint64_t *)(src + 0x18);
    *(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
    *(uint64_t *)(dst + 0x18) = w;
    *(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
    *(uint8_t *)(dst + 0x28) = *(uint8_t *)(src + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_0035780c @ 0x0035780c   (est. sk_stack_addr_a8)
 * Ghidra: long FUN_0035780c(void)
 * Returns fp-0xa8 (stack address of a local). Fragment.
 * Confidence: low (register fragment).
 */
long sk_stack_addr_a8(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return fp - 0xa8;
}

/*--------------------------------------------------------------------*/
/* FUN_00357818 @ 0x00357818   (est. sk_load_word_fp_60)
 * Ghidra: undefined8 FUN_00357818(void)
 * Returns the saved word at [fp-0x60]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_60(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x60);
}

/*--------------------------------------------------------------------*/
/* FUN_00357850 @ 0x00357850   (est. sk_shift16_or4)
 * Ghidra: ulong FUN_00357850(long param_1)
 * Returns (param_1 << 0x10) | 4: packs a 16-bit-shifted value with flag bit 2.
 * Confidence: medium.
 */
uint64_t sk_shift16_or4(long v)
{
    return (uint64_t)((v << 16) | 4);
}

/*--------------------------------------------------------------------*/
/* FUN_0035785c @ 0x0035785c   (est. sk_syscall_nop_785c)
 * Ghidra: void FUN_0035785c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_785c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357868 @ 0x00357868   (est. sk_syscall_nop_7868)
 * Ghidra: void FUN_00357868(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7868(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357874 @ 0x00357874   (est. sk_align_up_mask)
 * Ghidra: long FUN_00357874(ulong param_1,long param_2)
 * Returns param_2 + ((param_1 + 0x20) & ~param_1): rounds an object up to an
 * alignment derived from param_1 and offsets by param_2.
 * Confidence: medium.
 */
long sk_align_up_mask(uint64_t param_1, long param_2)
{
    return param_2 + (long)((param_1 + 0x20) & ~param_1);
}

/*--------------------------------------------------------------------*/
/* FUN_00357884 @ 0x00357884   (est. sk_syscall_nop_7884)
 * Ghidra: void FUN_00357884(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7884(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357898 @ 0x00357898   (est. sk_forward_258c60)
 * Ghidra: void FUN_00357898(void)
 * Trivial forwarder to FUN_00258c60 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_258c60(void)
{
    extern void sk_helper_258c60(void);  /* FUN_00258c60 */
    sk_helper_258c60();
}

/*--------------------------------------------------------------------*/
/* FUN_003578a8 @ 0x003578a8   (est. sk_load_word_fp_88)
 * Ghidra: undefined8 FUN_003578a8(void)
 * Returns the saved word at [fp-0x88]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_88(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x88);
}

/*--------------------------------------------------------------------*/
/* FUN_003578b4 @ 0x003578b4   (est. sk_syscall_nop_78b4)
 * Ghidra: void FUN_003578b4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_78b4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003578c0 @ 0x003578c0   (est. sk_load_word_fp_80)
 * Ghidra: undefined8 FUN_003578c0(void)
 * Returns the saved word at [fp-0x80]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_80(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x80);
}

/*--------------------------------------------------------------------*/
/* FUN_003578cc @ 0x003578cc   (est. sk_syscall_nop_78cc)
 * Ghidra: void FUN_003578cc(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_78cc(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003578d8 @ 0x003578d8   (est. sk_syscall_nop_78d8)
 * Ghidra: void FUN_003578d8(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_78d8(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003578e4 @ 0x003578e4   (est. sk_forward_1ef804)
 * Ghidra: void FUN_003578e4(void)
 * Trivial forwarder to FUN_001ef804 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_1ef804(void)
{
    extern void sk_helper_1ef804(void);  /* FUN_001ef804 */
    sk_helper_1ef804();
}

/*--------------------------------------------------------------------*/
/* FUN_00357904 @ 0x00357904   (est. sk_syscall_nop_7904)
 * Ghidra: void FUN_00357904(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7904(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357910 @ 0x00357910   (est. sk_syscall_nop_7910)
 * Ghidra: void FUN_00357910(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7910(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035792c @ 0x0035792c   (est. sk_syscall_nop_792c)
 * Ghidra: void FUN_0035792c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_792c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357938 @ 0x00357938   (est. sk_set_flag_or1)
 * Ghidra: ulong FUN_00357938(ulong param_1)
 * Returns x9 | param_1 | 1: ORs the argument with a caller register and sets
 * flag bit 0. Fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_set_flag_or1(uint64_t param_1)
{
    uint64_t reg = 0;   /* x9 (unaff) */
    return reg | param_1 | 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00357944 @ 0x00357944   (est. sk_syscall_nop_7944)
 * Ghidra: void FUN_00357944(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7944(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003579c0 @ 0x003579c0   (est. sk_table_idx_offset)
 * Ghidra: long FUN_003579c0(long param_1)
 * Returns x19 + s32[param_1+0x24]: adds an offset field to a table base held
 * in a caller register. Fragment.
 * Confidence: low (register fragment).
 */
long sk_table_idx_offset(long param_1)
{
    long base = 0;   /* x19 (unaff) */
    return base + (int)*(uint32_t *)(param_1 + 0x24);
}

/*--------------------------------------------------------------------*/
/* FUN_003579d8 @ 0x003579d8   (est. sk_forward_3722e4)
 * Ghidra: void FUN_003579d8(void)
 * Trivial forwarder to FUN_003722e4 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_3722e4(void)
{
    extern void sk_helper_3722e4(void);  /* FUN_003722e4 */
    sk_helper_3722e4();
}

/*--------------------------------------------------------------------*/
/* FUN_00357a5c @ 0x00357a5c   (est. sk_load_word_fp_78)
 * Ghidra: undefined8 FUN_00357a5c(void)
 * Returns the saved word at [fp-0x78]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_78(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x78);
}

/*--------------------------------------------------------------------*/
/* FUN_00357a90 @ 0x00357a90   (est. sk_load_word_fp_a0)
 * Ghidra: undefined8 FUN_00357a90(void)
 * Returns the saved word at [fp-0xa0]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_a0(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0xa0);
}

/*--------------------------------------------------------------------*/
/* FUN_00357acc @ 0x00357acc   (est. sk_panic_code_13f)
 * Ghidra: void FUN_00357acc(undefined8 param_1)
 * Calls FUN_00310d68(0x13f, param_1): raises a kernel trace/panic event with
 * code 0x13f and the given context word. Likely a fatal-error reporter.
 * Confidence: medium.
 */
void sk_panic_code_13f(uint64_t ctx)
{
    extern void sk_helper_310d68(uint64_t code, uint64_t ctx);  /* FUN_00310d68 */
    sk_helper_310d68(0x13f, ctx);
}

/*--------------------------------------------------------------------*/
/* FUN_00357b10 @ 0x00357b10   (est. sk_trace_026e8)
 * Ghidra: void FUN_00357b10(void)
 * Calls FUN_000026e8(&stack[8]): trace hook with a stack-local pointer.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_trace_026e8(void)
{
    extern void sk_helper_026e8(uint64_t *p);  /* FUN_000026e8 */
    sk_helper_026e8((uint64_t *)__builtin_frame_address(0) + 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00357b20 @ 0x00357b20   (est. sk_stack_ptr_8)
 * Ghidra: undefined1 * FUN_00357b20(void)
 * Returns &stack[8]. Fragment.
 * Confidence: low (register fragment).
 */
uint8_t *sk_stack_ptr_8(void)
{
    return (uint8_t *)__builtin_frame_address(0) + 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00357b2c @ 0x00357b2c   (est. sk_forward_1bcc18)
 * Ghidra: void FUN_00357b2c(undefined8 param_1,undefined8 param_2)
 * Calls FUN_001bcc18(param_2, param_1) — arguments swapped.
 * Confidence: medium.
 */
void sk_forward_1bcc18(uint64_t a, uint64_t b)
{
    extern void sk_helper_1bcc18(uint64_t b, uint64_t a);  /* FUN_001bcc18 */
    sk_helper_1bcc18(b, a);
}

/*--------------------------------------------------------------------*/
/* FUN_00357ba4 @ 0x00357ba4   (est. sk_init_then_flush)
 * Ghidra: void FUN_00357ba4(void)
 * Calls FUN_00310a74() then FUN_0001df60(): a two-step init/flush sequence.
 * Confidence: medium.
 */
void sk_init_then_flush(void)
{
    extern void sk_helper_310a74(void);  /* FUN_00310a74 */
    extern void sk_helper_1df60(void);   /* FUN_0001df60 */
    sk_helper_310a74();
    sk_helper_1df60();
}

/*--------------------------------------------------------------------*/
/* FUN_00357bc4 @ 0x00357bc4   (est. sk_passthrough_x3)
 * Ghidra: undefined8 FUN_00357bc4(void)
 * Returns x3 unchanged (register passthrough). Fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_passthrough_x3(void)
{
    return 0;   /* x3 (unaff) */
}

/*--------------------------------------------------------------------*/
/* FUN_00357bd0 @ 0x00357bd0   (est. sk_panic_noreturn)
 * Ghidra: void FUN_00357bd0(void)
 * Calls FUN_001afa84, which does not return — a fatal panic.
 * Confidence: high (noreturn callee).
 */
void sk_panic_noreturn(void)
{
    extern void sk_panic_helper(void);  /* FUN_001afa84 (noreturn) */
    sk_panic_helper();
    for (;;) { }  /* unreachable */
}

/*--------------------------------------------------------------------*/
/* FUN_00357bec @ 0x00357bec   (est. sk_forward_3722e4_b)
 * Ghidra: void FUN_00357bec(void)
 * Trivial forwarder to FUN_003722e4 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_3722e4_b(void)
{
    extern void sk_helper_3722e4(void);  /* FUN_003722e4 */
    sk_helper_3722e4();
}

/*--------------------------------------------------------------------*/
/* FUN_00357bf8 @ 0x00357bf8   (est. sk_forward_365b6c)
 * Ghidra: void FUN_00357bf8(void)
 * Trivial forwarder to FUN_00365b6c (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_365b6c(void)
{
    extern void sk_helper_365b6c(void);  /* FUN_00365b6c */
    sk_helper_365b6c();
}

/*--------------------------------------------------------------------*/
/* FUN_00357c04 @ 0x00357c04   (est. sk_call_27754x3)
 * Ghidra: void FUN_00357c04(void)
 * Calls FUN_00027754 three times in sequence (triple flush/poke).
 * Confidence: medium.
 */
void sk_call_27754x3(void)
{
    extern void sk_helper_27754(void);  /* FUN_00027754 */
    sk_helper_27754();
    sk_helper_27754();
    sk_helper_27754();
}

/*--------------------------------------------------------------------*/
/* FUN_00357c2c @ 0x00357c2c   (est. sk_trace_026e8_b)
 * Ghidra: void FUN_00357c2c(void)
 * Calls FUN_000026e8(&stack[8]): trace hook with a stack-local pointer.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_trace_026e8_b(void)
{
    extern void sk_helper_026e8(uint64_t *p);  /* FUN_000026e8 */
    sk_helper_026e8((uint64_t *)__builtin_frame_address(0) + 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00357c58 @ 0x00357c58   (est. sk_init_then_flush_b)
 * Ghidra: void FUN_00357c58(void)
 * Calls FUN_00310a74() then FUN_0001df60(): init/flush sequence.
 * Confidence: medium.
 */
void sk_init_then_flush_b(void)
{
    extern void sk_helper_310a74(void);  /* FUN_00310a74 */
    extern void sk_helper_1df60(void);   /* FUN_0001df60 */
    sk_helper_310a74();
    sk_helper_1df60();
}

/*--------------------------------------------------------------------*/
/* FUN_00357c88 @ 0x00357c88   (est. sk_forward_a6b64)
 * Ghidra: void FUN_00357c88(void)
 * Trivial forwarder to FUN_000a6b64 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_a6b64(void)
{
    extern void sk_helper_a6b64(void);  /* FUN_000a6b64 */
    sk_helper_a6b64();
}

/*--------------------------------------------------------------------*/
/* FUN_00357cc8 @ 0x00357cc8   (est. sk_swift_existential_meta)
 * Ghidra: undefined1 [16] FUN_00357cc8(void)
 * Returns a Swift existential-metadata pair: {string s_Swift_ExistentialCollection, 0x21}.
 * Confidence: high (string matched).
 */
cl4_result_t sk_swift_existential_meta(void)
{
    static const char s_meta[] = "Swift_ExistentialCollection";  /* s_005cf680 */
    return (cl4_result_t){ .lo = (uint64_t)(uintptr_t)s_meta, .hi = 0x21 };
}

/*--------------------------------------------------------------------*/
/* FUN_00357cfc @ 0x00357cfc   (est. sk_store_word_hi_byte)
 * Ghidra: void FUN_00357cfc(undefined8 param_1)
 * Writes the low 32 bits of param_1 to [fp-0x78] and the byte at bit 32 to
 * [fp-0x74]: stores a 33-bit packed value. Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_word_hi_byte(uint64_t v)
{
    long fp = 0;   /* x29 frame (unaff) */
    *(int32_t *)(fp - 0x78) = (int32_t)v;
    *(char *)(fp - 0x74) = (char)(v >> 32);
}

/*--------------------------------------------------------------------*/
/* FUN_00357d34 @ 0x00357d34   (est. sk_copy_word_20)
 * Ghidra: void FUN_00357d34(void)
 * Copies the word at [src+0x20] into [dst+0x20]. Fragment.
 * Confidence: low (register fragment).
 */
void sk_copy_word_20(void)
{
    long dst = 0;  /* x20 (unaff) */
    long src = 0;  /* x19 (unaff) */
    *(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_00357da4 @ 0x00357da4   (est. sk_inc_counter_24)
 * Ghidra: void FUN_00357da4(void)
 * Increments the 32-bit counter at [obj+0x24]. Fragment.
 * Confidence: low (register fragment).
 */
void sk_inc_counter_24(void)
{
    long obj = 0;   /* x19 (unaff) */
    *(int32_t *)(obj + 0x24) = *(int32_t *)(obj + 0x24) + 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00357dd4 @ 0x00357dd4   (est. sk_store_3bytes)
 * Ghidra: void FUN_00357dd4(void)
 * Writes a 24-bit value (low 16 bits + high 8 bits) into the object at x19.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_3bytes(void)
{
    uint16_t *obj = 0;   /* x19 (unaff) */
    uint32_t v = 0;      /* w20 (unaff) */
    obj[0] = (uint16_t)v;
    *(uint8_t *)(obj + 1) = (uint8_t)(v >> 16);
}

/*--------------------------------------------------------------------*/
/* FUN_00357e64 @ 0x00357e64   (est. sk_pair_load_68)
 * Ghidra: undefined1 [16] FUN_00357e64(void)
 * Returns pair {load[x21+0x68], 0}, shifted left 64 bits. Fragment.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_pair_load_68(void)
{
    long base = 0;   /* x21 (unaff) */
    cl4_result_t r = { .lo = *(uint64_t *)(base + 0x68), .hi = 0 };
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00357f04 @ 0x00357f04   (est. sk_spill_7args)
 * Ghidra: void FUN_00357f04(undefined8 param_1,...7 args)
 * Spills seven argument words into the caller frame stack slots. Fragment
 * (argument-register save).
 * Confidence: low (register fragment).
 */
void sk_spill_7args(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                    uint64_t e, uint64_t f, uint64_t g)
{
    long fp = 0;   /* x29 frame (unaff) */
    *(uint64_t *)(fp - 0xa8) = f;
    *(uint64_t *)(fp - 0xa0) = g;
    *(uint64_t *)(fp - 0xb8) = d;
    *(uint64_t *)(fp - 0xb0) = e;
    *(uint64_t *)(fp - 0xc8) = b;
    *(uint64_t *)(fp - 0xc0) = c;
    (void)a;
}

/*--------------------------------------------------------------------*/
/* FUN_00357f14 @ 0x00357f14   (est. sk_stack_ptr_8_b)
 * Ghidra: undefined1 * FUN_00357f14(void)
 * Returns &stack[8]. Fragment.
 * Confidence: low (register fragment).
 */
uint8_t *sk_stack_ptr_8_b(void)
{
    return (uint8_t *)__builtin_frame_address(0) + 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00357f24 @ 0x00357f24   (est. sk_store_rec_0_3)
 * Ghidra: void FUN_00357f24(undefined8 param_1)
 * Stores param_1 at rec[3] and x19 at rec[0]. Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_rec_0_3(uint64_t v)
{
    uint64_t *rec = 0;  /* x20 (unaff) */
    uint64_t cur = 0;   /* x19 (unaff) */
    rec[3] = v;
    rec[0] = cur;
}

/*--------------------------------------------------------------------*/
/* FUN_00357f34 @ 0x00357f34   (est. sk_mask_align_sub)
 * Ghidra: long FUN_00357f34(ulong param_1)
 * Returns (param_1 & 0xffffffffffff0000) - 0xfffc: masks to a 64K boundary
 * and backs off by 0xfffc.
 * Confidence: medium.
 */
long sk_mask_align_sub(uint64_t v)
{
    return (long)((v & 0xffffffffffff0000ULL) - 0xfffc);
}

/*--------------------------------------------------------------------*/
/* FUN_00357f54 @ 0x00357f54   (est. sk_copy_2words_neg)
 * Ghidra: void FUN_00357f54(long param_1)
 * Copies words at [param_1-0xf8] and [param_1-0x100] into fp-0x128/-0x130.
 * Fragment.
 * Confidence: low (register fragment).
 */
void sk_copy_2words_neg(long src)
{
    long fp = 0;   /* x29 frame (unaff) */
    uint64_t u = *(uint64_t *)(src - 0x100);
    *(uint64_t *)(fp - 0x128) = *(uint64_t *)(src - 0xf8);
    *(uint64_t *)(fp - 0x130) = u;
}

/*--------------------------------------------------------------------*/
/* FUN_00357f94 @ 0x00357f94   (est. sk_pair_add_frag)
 * Ghidra: undefined1 [16] FUN_00357f94(long param_1)
 * Returns pair {x26+x9, x23+param_1}. Fragment.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_pair_add_frag(long param_1)
{
    long a = 0;   /* x23 (unaff) */
    long b = 0;   /* x26 (unaff) */
    long c = 0;   /* x9 (unaff) */
    return (cl4_result_t){ .lo = b + c, .hi = a + param_1 };
}

/*--------------------------------------------------------------------*/
/* FUN_00357fb4 @ 0x00357fb4   (est. sk_spill_3regs)
 * Ghidra: void FUN_00357fb4(void)
 * Spills three caller registers into fp-0xa0/-0x98/-0x78. Fragment.
 * Confidence: low (register fragment).
 */
void sk_spill_3regs(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    uint64_t r1 = 0;   /* x27 (unaff) */
    uint64_t r2 = 0;   /* x26 (unaff) */
    uint64_t r3 = 0;   /* x22 (unaff) */
    *(uint64_t *)(fp - 0xa0) = r1;
    *(uint64_t *)(fp - 0x98) = r2;
    *(uint64_t *)(fp - 0x78) = r3;
}

/*--------------------------------------------------------------------*/
/* FUN_00357fc4 @ 0x00357fc4   (est. sk_pair_add_frag_c4)
 * Ghidra: undefined1 [16] FUN_00357fc4(long param_1)
 * Returns pair {x27 + s32[x22+0x24], x25 + param_1}. Fragment.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_pair_add_frag_c4(long param_1)
{
    long base = 0;   /* x22 (unaff) */
    long a = 0;      /* x25 (unaff) */
    long b = 0;      /* x27 (unaff) */
    return (cl4_result_t){ .lo = b + (int)*(uint32_t *)(base + 0x24),
                           .hi = a + param_1 };
}

/*--------------------------------------------------------------------*/
/* FUN_00357fd4 @ 0x00357fd4   (est. sk_is_not_one)
 * Ghidra: bool FUN_00357fd4(void)
 * Returns (w20 != 1). Fragment.
 * Confidence: low (register fragment).
 */
bool sk_is_not_one(void)
{
    return (0 /* w20 (unaff) */) != 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00357fe4 @ 0x00357fe4   (est. sk_store_counter)
 * Ghidra: void FUN_00357fe4(long param_1)
 * Stores x21+1 into [param_1+0x10]. Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_counter(long obj)
{
    long v = 0;   /* x21 (unaff) */
    *(long *)(obj + 0x10) = v + 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00357ff4 @ 0x00357ff4   (est. sk_pair_load_2)
 * Ghidra: undefined1 [16] FUN_00357ff4(void)
 * Returns pair {load[fp-0x88], load[fp-0xd8]+x26}. Fragment.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_pair_load_2(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    long add = 0;  /* x26 (unaff) */
    return (cl4_result_t){ .lo = *(uint64_t *)(fp - 0x88),
                           .hi = *(long *)(fp - 0xd8) + add };
}

/*--------------------------------------------------------------------*/
/* FUN_00358034 @ 0x00358034   (est. sk_stack_addr_128)
 * Ghidra: long FUN_00358034(void)
 * Returns fp-0x128 (stack address of a local). Fragment.
 * Confidence: low (register fragment).
 */
long sk_stack_addr_128(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return fp - 0x128;
}

/*--------------------------------------------------------------------*/
/* FUN_00358064 @ 0x00358064   (est. sk_load_word_fp_70)
 * Ghidra: undefined8 FUN_00358064(void)
 * Returns the saved word at [fp-0x70]. Stack-locals fragment.
 * Confidence: low (register fragment).
 */
uint64_t sk_load_word_fp_70(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    return *(uint64_t *)(fp - 0x70);
}

/*--------------------------------------------------------------------*/
/* FUN_003580a4 @ 0x003580a4   (est. sk_pair_load_masked)
 * Ghidra: undefined1 [16] FUN_003580a4(void)
 * Returns pair {load[x20+8] & 0xffffffffffffff, load[x20+0x10]}. Fragment.
 * Confidence: low (register fragment).
 */
cl4_result_t sk_pair_load_masked(void)
{
    long base = 0;   /* x20 (unaff) */
    return (cl4_result_t){ .lo = *(uint64_t *)(base + 8) & 0xffffffffffffffULL,
                           .hi = *(uint64_t *)(base + 0x10) };
}

/*--------------------------------------------------------------------*/
/* FUN_00358104 @ 0x00358104   (est. sk_store_one_word)
 * Ghidra: void FUN_00358104(undefined8 param_1)
 * Stores param_1 into *x20. Fragment.
 * Confidence: low (register fragment).
 */
void sk_store_one_word(uint64_t v)
{
    uint64_t *dst = 0;   /* x20 (unaff) */
    *dst = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00358114 @ 0x00358114   (est. sk_spill_6args)
 * Ghidra: void FUN_00358114(...6 args)
 * Spills six argument words into caller frame stack slots. Fragment.
 * Confidence: low (register fragment).
 */
void sk_spill_6args(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                    uint32_t e, uint64_t f)
{
    long fp = 0;   /* x29 frame (unaff) */
    (void)a; (void)b;
    *(uint64_t *)(fp - 0x78) = f;
    *(uint64_t *)(fp - 0x70) = c;
    *(uint32_t *)(fp - 0x5c) = e;
    *(uint64_t *)(fp - 0x68) = d;
}

/*--------------------------------------------------------------------*/
/* FUN_00358134 @ 0x00358134   (est. sk_div_shift_store)
 * Ghidra: void FUN_00358134(long param_1)
 * Stores x19 at [x20+0x10] and (param_1 / x21) << 1 at [x20+0x18]. Fragment.
 * Confidence: low (register fragment).
 */
void sk_div_shift_store(long num)
{
    uint64_t cur = 0;   /* x19 (unaff) */
    long *dst = 0;      /* x20 (unaff) */
    long den = 0;       /* x21 (unaff) */
    long q = 0;
    if (den != 0) q = num / den;
    *(uint64_t *)(dst + 0x10) = cur;               /* [x20+0x10] */
    *(uint64_t *)(dst + 0x18) = (uint64_t)(q << 1); /* [x20+0x18] */
}

/*--------------------------------------------------------------------*/
/* FUN_00358144 @ 0x00358144   (est. sk_load_word_20)
 * Ghidra: undefined8 FUN_00358144(long param_1)
 * Returns load[param_1+0x20].
 * Confidence: medium.
 */
uint64_t sk_load_word_20(long obj)
{
    return *(uint64_t *)(obj + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_00358154 @ 0x00358154   (est. sk_stack_ptr_20)
 * Ghidra: undefined1 * FUN_00358154(void)
 * Returns &stack[0x20]. Fragment.
 * Confidence: low (register fragment).
 */
uint8_t *sk_stack_ptr_20(void)
{
    return (uint8_t *)__builtin_frame_address(0) + 0x20;
}

/*--------------------------------------------------------------------*/
/* FUN_00358164 @ 0x00358164   (est. sk_load_word_18)
 * Ghidra: undefined8 FUN_00358164(undefined8 param_1,long param_2)
 * Returns load[param_2+0x18] (param_1 unused).
 * Confidence: medium.
 */
uint64_t sk_load_word_18(uint64_t unused, long obj)
{
    (void)unused;
    return *(uint64_t *)(obj + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_00358174 @ 0x00358174   (est. sk_passthrough_stack)
 * Ghidra: undefined8 FUN_00358174(void)
 * Returns the stack argument at [fp+0x10] unchanged (register passthrough).
 * Confidence: low (register fragment).
 */
uint64_t sk_passthrough_stack(void)
{
    return 0;   /* in_stack_0x10 (unaff) */
}

/*--------------------------------------------------------------------*/
/* FUN_003581a4 @ 0x003581a4   (est. sk_not_bit0)
 * Ghidra: uint FUN_003581a4(void)
 * Returns (w20 ^ 0xffffffff) & 1: bit-0 negation of a caller register.
 * Fragment.
 * Confidence: low (register fragment).
 */
uint32_t sk_not_bit0(void)
{
    return (0 /* w20 (unaff) */ ^ 0xffffffffu) & 1u;
}

/*--------------------------------------------------------------------*/
/* FUN_003581b4 @ 0x003581b4   (est. sk_mask_shift_neg1)
 * Ghidra: void FUN_003581b4(void)
 * Stores -1 << (x26 & 0x3f) into *x24. Fragment.
 * Confidence: low (register fragment).
 */
void sk_mask_shift_neg1(void)
{
    long *dst = 0;   /* x24 (unaff) */
    uint64_t sh = 0; /* x26 (unaff) */
    *dst = -1L << (sh & 0x3f);
}

/*--------------------------------------------------------------------*/
/* FUN_003581c4 @ 0x003581c4   (est. sk_spill_2regs)
 * Ghidra: void FUN_003581c4(void)
 * Spills two caller registers into fp-0x78/-0x70. Fragment.
 * Confidence: low (register fragment).
 */
void sk_spill_2regs(void)
{
    long fp = 0;   /* x29 frame (unaff) */
    uint64_t a = 0;  /* x24 (unaff) */
    uint64_t b = 0;  /* x26 (unaff) */
    *(uint64_t *)(fp - 0x78) = a;
    *(uint64_t *)(fp - 0x70) = b;
}

/*--------------------------------------------------------------------*/
/* FUN_003581d4 @ 0x003581d4   (est. sk_thunk_298d4x3)
 * Ghidra: void FUN_003581d4(void)
 * Calls thunk_FUN_002298d4 three times, the last with a byte argument.
 * Confidence: medium.
 */
void sk_thunk_298d4x3(void)
{
    extern void sk_thunk_298d4(void);            /* thunk_FUN_002298d4 */
    extern void sk_thunk_298d4_b(uint8_t v);     /* thunk_FUN_002298d4 */
    sk_thunk_298d4();
    sk_thunk_298d4();
    sk_thunk_298d4_b(0 /* w27 (unaff) */);
}

/*--------------------------------------------------------------------*/
/* FUN_003581fc @ 0x003581fc   (est. sk_forward_376820)
 * Ghidra: void FUN_003581fc(void)
 * Trivial forwarder to FUN_00376820 (out-of-range helper).
 * Confidence: medium.
 */
void sk_forward_376820(void)
{
    extern void sk_helper_376820(void);  /* FUN_00376820 */
    sk_helper_376820();
}

/*--------------------------------------------------------------------*/
/* FUN_00357958 @ 0x00357958   (est. sk_syscall_nop_7958)
 * Ghidra: void FUN_00357958(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7958(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357964 @ 0x00357964   (est. sk_syscall_nop_7964)
 * Ghidra: void FUN_00357964(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7964(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357970 @ 0x00357970   (est. sk_syscall_nop_7970)
 * Ghidra: void FUN_00357970(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7970(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_0035798c @ 0x0035798c   (est. sk_syscall_nop_798c)
 * Ghidra: void FUN_0035798c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_798c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357998 @ 0x00357998   (est. sk_syscall_nop_7998)
 * Ghidra: void FUN_00357998(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7998(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003579a4 @ 0x003579a4   (est. sk_syscall_nop_79a4)
 * Ghidra: void FUN_003579a4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_79a4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003579cc @ 0x003579cc   (est. sk_syscall_nop_79cc)
 * Ghidra: void FUN_003579cc(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_79cc(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003579e8 @ 0x003579e8   (est. sk_syscall_nop_79e8)
 * Ghidra: void FUN_003579e8(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_79e8(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003579f4 @ 0x003579f4   (est. sk_syscall_nop_79f4)
 * Ghidra: void FUN_003579f4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_79f4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a00 @ 0x00357a00   (est. sk_syscall_nop_7a00)
 * Ghidra: void FUN_00357a00(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a00(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a0c @ 0x00357a0c   (est. sk_syscall_nop_7a0c)
 * Ghidra: void FUN_00357a0c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a0c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a18 @ 0x00357a18   (est. sk_syscall_nop_7a18)
 * Ghidra: void FUN_00357a18(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a18(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a34 @ 0x00357a34   (est. sk_syscall_nop_7a34)
 * Ghidra: void FUN_00357a34(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a34(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a68 @ 0x00357a68   (est. sk_syscall_nop_7a68)
 * Ghidra: void FUN_00357a68(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a68(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a84 @ 0x00357a84   (est. sk_syscall_nop_7a84)
 * Ghidra: void FUN_00357a84(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a84(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357a9c @ 0x00357a9c   (est. sk_syscall_nop_7a9c)
 * Ghidra: void FUN_00357a9c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7a9c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357aa8 @ 0x00357aa8   (est. sk_syscall_nop_7aa8)
 * Ghidra: void FUN_00357aa8(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7aa8(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ab4 @ 0x00357ab4   (est. sk_syscall_nop_7ab4)
 * Ghidra: void FUN_00357ab4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ab4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ac0 @ 0x00357ac0   (est. sk_syscall_nop_7ac0)
 * Ghidra: void FUN_00357ac0(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ac0(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357aec @ 0x00357aec   (est. sk_syscall_nop_7aec)
 * Ghidra: void FUN_00357aec(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7aec(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357af8 @ 0x00357af8   (est. sk_syscall_nop_7af8)
 * Ghidra: void FUN_00357af8(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7af8(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b04 @ 0x00357b04   (est. sk_syscall_nop_7b04)
 * Ghidra: void FUN_00357b04(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b04(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b3c @ 0x00357b3c   (est. sk_syscall_nop_7b3c)
 * Ghidra: void FUN_00357b3c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b3c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b48 @ 0x00357b48   (est. sk_syscall_nop_7b48)
 * Ghidra: void FUN_00357b48(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b48(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b54 @ 0x00357b54   (est. sk_syscall_nop_7b54)
 * Ghidra: void FUN_00357b54(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b54(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b60 @ 0x00357b60   (est. sk_syscall_nop_7b60)
 * Ghidra: void FUN_00357b60(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b60(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b7c @ 0x00357b7c   (est. sk_syscall_nop_7b7c)
 * Ghidra: void FUN_00357b7c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7b7c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357b88 @ 0x00357b88   (est. sk_return_zero_7b88)
 * Ghidra: undefined8 FUN_00357b88(void)
 * Returns the constant 0. Trivial zero return.
 * Confidence: medium.
 */
uint64_t sk_return_zero_7b88(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00357be0 @ 0x00357be0   (est. sk_syscall_nop_7be0)
 * Ghidra: void FUN_00357be0(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7be0(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357c20 @ 0x00357c20   (est. sk_syscall_nop_7c20)
 * Ghidra: void FUN_00357c20(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7c20(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357c38 @ 0x00357c38   (est. sk_syscall_nop_7c38)
 * Ghidra: void FUN_00357c38(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7c38(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357c44 @ 0x00357c44   (est. sk_syscall_nop_7c44)
 * Ghidra: void FUN_00357c44(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7c44(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357c74 @ 0x00357c74   (est. sk_syscall_nop_7c74)
 * Ghidra: void FUN_00357c74(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7c74(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ca0 @ 0x00357ca0   (est. sk_syscall_nop_7ca0)
 * Ghidra: void FUN_00357ca0(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ca0(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357cb4 @ 0x00357cb4   (est. sk_syscall_nop_7cb4)
 * Ghidra: void FUN_00357cb4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7cb4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357cdc @ 0x00357cdc   (est. sk_syscall_nop_7cdc)
 * Ghidra: void FUN_00357cdc(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7cdc(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357cec @ 0x00357cec   (est. sk_syscall_nop_7cec)
 * Ghidra: void FUN_00357cec(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7cec(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d0c @ 0x00357d0c   (est. sk_syscall_nop_7d0c)
 * Ghidra: void FUN_00357d0c(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d0c(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d44 @ 0x00357d44   (est. sk_syscall_nop_7d44)
 * Ghidra: void FUN_00357d44(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d44(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d54 @ 0x00357d54   (est. sk_syscall_nop_7d54)
 * Ghidra: void FUN_00357d54(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d54(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d64 @ 0x00357d64   (est. sk_syscall_nop_7d64)
 * Ghidra: void FUN_00357d64(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d64(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d74 @ 0x00357d74   (est. sk_syscall_nop_7d74)
 * Ghidra: void FUN_00357d74(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d74(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d84 @ 0x00357d84   (est. sk_syscall_nop_7d84)
 * Ghidra: void FUN_00357d84(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d84(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357d94 @ 0x00357d94   (est. sk_syscall_nop_7d94)
 * Ghidra: void FUN_00357d94(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7d94(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357db4 @ 0x00357db4   (est. sk_syscall_nop_7db4)
 * Ghidra: void FUN_00357db4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7db4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357dc4 @ 0x00357dc4   (est. sk_syscall_nop_7dc4)
 * Ghidra: void FUN_00357dc4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7dc4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357de4 @ 0x00357de4   (est. sk_syscall_nop_7de4)
 * Ghidra: void FUN_00357de4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7de4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357df4 @ 0x00357df4   (est. sk_syscall_nop_7df4)
 * Ghidra: void FUN_00357df4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7df4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e04 @ 0x00357e04   (est. sk_syscall_nop_7e04)
 * Ghidra: void FUN_00357e04(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e04(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e14 @ 0x00357e14   (est. sk_syscall_nop_7e14)
 * Ghidra: void FUN_00357e14(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e14(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e24 @ 0x00357e24   (est. sk_syscall_nop_7e24)
 * Ghidra: void FUN_00357e24(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e24(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e34 @ 0x00357e34   (est. sk_syscall_nop_7e34)
 * Ghidra: void FUN_00357e34(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e34(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e44 @ 0x00357e44   (est. sk_syscall_nop_7e44)
 * Ghidra: void FUN_00357e44(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e44(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e84 @ 0x00357e84   (est. sk_syscall_nop_7e84)
 * Ghidra: void FUN_00357e84(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e84(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357e94 @ 0x00357e94   (est. sk_syscall_nop_7e94)
 * Ghidra: void FUN_00357e94(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7e94(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357eb4 @ 0x00357eb4   (est. sk_syscall_nop_7eb4)
 * Ghidra: void FUN_00357eb4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7eb4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ec4 @ 0x00357ec4   (est. sk_syscall_nop_7ec4)
 * Ghidra: void FUN_00357ec4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ec4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ed4 @ 0x00357ed4   (est. sk_syscall_nop_7ed4)
 * Ghidra: void FUN_00357ed4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ed4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ee4 @ 0x00357ee4   (est. sk_syscall_nop_7ee4)
 * Ghidra: void FUN_00357ee4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ee4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357ef4 @ 0x00357ef4   (est. sk_syscall_nop_7ef4)
 * Ghidra: void FUN_00357ef4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7ef4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357f44 @ 0x00357f44   (est. sk_syscall_nop_7f44)
 * Ghidra: void FUN_00357f44(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7f44(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357f64 @ 0x00357f64   (est. sk_syscall_nop_7f64)
 * Ghidra: void FUN_00357f64(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7f64(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357f74 @ 0x00357f74   (est. sk_syscall_nop_7f74)
 * Ghidra: void FUN_00357f74(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7f74(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357f84 @ 0x00357f84   (est. sk_syscall_nop_7f84)
 * Ghidra: void FUN_00357f84(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7f84(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00357fa4 @ 0x00357fa4   (est. sk_syscall_nop_7fa4)
 * Ghidra: void FUN_00357fa4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_7fa4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358004 @ 0x00358004   (est. sk_syscall_nop_8004)
 * Ghidra: void FUN_00358004(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8004(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358014 @ 0x00358014   (est. sk_syscall_nop_8014)
 * Ghidra: void FUN_00358014(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8014(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358024 @ 0x00358024   (est. sk_syscall_nop_8024)
 * Ghidra: void FUN_00358024(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8024(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358044 @ 0x00358044   (est. sk_syscall_nop_8044)
 * Ghidra: void FUN_00358044(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8044(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358054 @ 0x00358054   (est. sk_syscall_nop_8054)
 * Ghidra: void FUN_00358054(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8054(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358074 @ 0x00358074   (est. sk_syscall_nop_8074)
 * Ghidra: void FUN_00358074(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8074(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358084 @ 0x00358084   (est. sk_syscall_nop_8084)
 * Ghidra: void FUN_00358084(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8084(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358094 @ 0x00358094   (est. sk_syscall_nop_8094)
 * Ghidra: void FUN_00358094(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8094(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003580b4 @ 0x003580b4   (est. sk_syscall_nop_80b4)
 * Ghidra: void FUN_003580b4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_80b4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003580c4 @ 0x003580c4   (est. sk_syscall_nop_80c4)
 * Ghidra: void FUN_003580c4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_80c4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003580d4 @ 0x003580d4   (est. sk_syscall_nop_80d4)
 * Ghidra: void FUN_003580d4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_80d4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003580e4 @ 0x003580e4   (est. sk_syscall_nop_80e4)
 * Ghidra: void FUN_003580e4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_80e4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_003580f4 @ 0x003580f4   (est. sk_syscall_nop_80f4)
 * Ghidra: void FUN_003580f4(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_80f4(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358124 @ 0x00358124   (est. sk_syscall_nop_8124)
 * Ghidra: void FUN_00358124(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8124(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358184 @ 0x00358184   (est. sk_syscall_nop_8184)
 * Ghidra: void FUN_00358184(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8184(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358194 @ 0x00358194   (est. sk_syscall_nop_8194)
 * Ghidra: void FUN_00358194(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8194(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358208 @ 0x00358208   (est. sk_syscall_nop_8208)
 * Ghidra: void FUN_00358208(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8208(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358218 @ 0x00358218   (est. sk_syscall_nop_8218)
 * Ghidra: void FUN_00358218(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8218(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358228 @ 0x00358228   (est. sk_syscall_nop_8228)
 * Ghidra: void FUN_00358228(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8228(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358238 @ 0x00358238   (est. sk_syscall_nop_8238)
 * Ghidra: void FUN_00358238(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8238(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358248 @ 0x00358248   (est. sk_syscall_nop_8248)
 * Ghidra: void FUN_00358248(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8248(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358258 @ 0x00358258   (est. sk_syscall_nop_8258)
 * Ghidra: void FUN_00358258(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8258(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* FUN_00358268 @ 0x00358268   (est. sk_syscall_nop_8268)
 * Ghidra: void FUN_00358268(void)
 * Empty body (single RET) — unused/no-op slot.
 * Confidence: medium.
 */
void sk_syscall_nop_8268(void)
{
    /* empty */
}

/*--------------------------------------------------------------------*/
/* (next function) */
