/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * Region 0x34e830..0x34f21c (120 functions): a dense Swift-runtime
 * `_Concurrency` / metadata support cluster. The bulk are tiny
 * register-shuffling continuation thunks (a few instructions each: they set
 * up argument registers x0-x4 / x19-x28 from the caller's context registers
 * and return; Ghidra's decompiler collapses most of them to `return;`). The
 * remainder are real bodies: 24-byte copies, stack-pointer adjustments,
 * struct/descriptor builders, and thin wrappers over the shared Swift runtime
 * helpers (sk_vt_dispatch30 = FUN_000839f8, the swift_type_metadata_field_*
 * accessors, swift_small_string_encode = FUN_001a89a8). Names are estimates
 * (seL4/cL4 + Swift vocabulary); confidence low unless a shared-helper
 * identity raises it.
 *
 * Registers x19-x28 are the Swift callee-saved context (loaded by the caller
 * before the jump). Functions marked "register-shuffle thunk" perform no
 * memory or call side effect; they only rearrange these registers so the
 * next executed instruction (a continuation) sees its arguments in place.
 * The decompile for each is literally `return;`; the register contract from
 * disassembly is recorded in the body comment. */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint64_t word_t;
typedef uint32_t word32_t;

/* Two-word Swift ABI value returned in x0/x1 (also a 16-byte struct). */
typedef struct { word_t lo; word_t hi; } sk06_pair_t;

/* ------------------------------------------------------------------ *
 * Shared Swift-runtime helpers (ground truth FUN_ addresses; bodies are
 * reconstructed in other slices / files — not part of this slice).
 * ------------------------------------------------------------------ */

extern void   sk_vt_dispatch30(word_t param_1, word_t param_2, word_t param_3);            /* FUN_000839f8 (indirect vtable dispatch) */
extern word_t swift_type_metadata_field_30(word_t tagged);                                  /* FUN_00310a74 (field offset at +0x30) */
extern word_t swift_type_metadata_field_40(word_t tagged);                                  /* FUN_00310a44 (field offset at +0x40) */
extern word_t swift_type_metadata_field_c(word_t tagged);                                   /* FUN_00310e20 (field offset at +0x0c) */
extern word_t swift_type_metadata_field_4(word_t tagged);                                   /* FUN_0014ae44 (field offset at +0x04) */
extern word_t swift_type_metadata_field_20(word_t tagged);                                  /* FUN_000277b8 (field offset at +0x20) */
extern word_t sk_swift_field0x50_accessor(word_t *param_1, word_t param_2);                 /* FUN_0006a4c0 */
extern word_t swift_small_string_encode(word_t param_1, word_t param_2, word_t param_3);    /* FUN_001a89a8 */
extern void   sk_metadata_hook_dispatch(void);                                              /* FUN_0036986c (calls *_DAT_006adee8 if set) */
extern void   sk_swift_runtime_1df60(void);                                                 /* FUN_0001df60 (lazy-init DAT_0064c0f8) */
extern void   sk_big_alloc_2a4c98(word_t, word_t, word_t, word_t);                          /* FUN_002a4c98 (large allocator) */

/* ------------------------------------------------------------------ *
 * Real bodies.
 * ------------------------------------------------------------------ */

/* FUN_0034e830 @ 0x0034e830   (est. sk06_e830_capture_store)
 * Ghidra: void FUN_0034e830(long param_1, undefined8 param_2)
 * Builds a capture-context record at param_1: stores param_2 at +8, the
 * caller's x11 at +0x10, zero at +0x18, and (x10 masked by a shifted
 * complement of x9, ANDed with x12) at +0x20. The x9/x10/x12 values arrive
 * in the caller's registers. Confidence: low (Swift closure-capture setup).
 * Notes: decompile drops the register contract; disasm shows
 *   neg x9,x9; lsl x13,x10,x9; cmp x9,#0x40; csinv x9,x10,x13,cs. */
void sk06_e830_capture_store(word_t *record, word_t param_2,
                             word_t shift, word_t x10, word_t x11, word_t x12)
{
    if ((word_t)-shift < 0x40) {
        x10 = ~(x10 << (-shift & 0x3fU));
    }
    record[1] = param_2;        /* +8 */
    record[2] = x11;            /* +0x10 */
    record[3] = 0;              /* +0x18 */
    record[4] = x10 & x12;      /* +0x20 */
}

/* FUN_0034e850 @ 0x0034e850   (est. sk06_e850_pair_alloc)
 * Ghidra: undefined1 [16] FUN_0034e850(long param_1)
 * Returns a two-word pair {p+x25+x23 & ~x25, p+x25+x20 & ~x25} where p is the
 * argument and x25/x23/x20 are caller context registers; also reloads x2=x19.
 * Pointer-masking allocation thunk. Confidence: low. */
sk06_pair_t sk06_e850_pair_alloc(word_t param_1, word_t mask,
                                 word_t x23, word_t x20)
{
    sk06_pair_t r;
    r.lo = (param_1 + mask + x23) & ~mask;
    r.hi = (param_1 + mask + x20) & ~mask;
    return r;
}

/* FUN_0034e86c @ 0x0034e86c   (est. sk06_e86c_copy24)
 * Ghidra: void FUN_0034e86c(undefined8 *param_1, undefined8 *param_2)
 * Copies the 24-byte (3-word) block param_2[0..2] into param_1[0..2].
 * Swift value copy. Confidence: low. */
void sk06_e86c_copy24(word_t *dst, const word_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

/* FUN_0034e888 @ 0x0034e888   (est. sk06_e888_ceil_div)
 * Ghidra: void FUN_0034e888(void)
 * Register-only computation: w13 = ((w13 + ~((-1) << w12)) >> w12) + 1 —
 * a rounding-up division/alignment step. Result left in w13 for the
 * caller's continuation. Confidence: low (thunk).
 * Notes: decompile collapses to `return;`; body recovered from disassembly. */
void sk06_e888_ceil_div(void)
{
    /* w13 = ((w13 + ~((word32_t)-1 << w12)) >> w12) + 1 — register-only. */
}

/* FUN_0034e8a4 @ 0x0034e8a4   (est. sk06_e8a4_restore_args)
 * Ghidra: void FUN_0034e8a4(void)
 * Register-shuffle continuation thunk: x24<-x5, x25<-x4, x19<-x3, x21<-x2.
 * No memory/call side effect. Confidence: low. */
void sk06_e8a4_restore_args(void)
{
    /* mov x24,x5 ; mov x25,x4 ; mov x19,x3 ; mov x21,x2 ; ret */
}

/* FUN_0034e8b8 @ 0x0034e8b8   (est. sk06_e8b8_pair_alloc_b)
 * Ghidra: undefined1 [16] FUN_0034e8b8(long param_1)
 * Variant of FUN_0034e850: returns {p+x9+x20 & ~x9, p+x9+x19 & ~x9} with
 * mask x9; reloads x2=x21. Pointer-masking allocation thunk. Confidence: low. */
sk06_pair_t sk06_e8b8_pair_alloc_b(word_t param_1, word_t mask,
                                   word_t x20, word_t x19)
{
    sk06_pair_t r;
    r.lo = (param_1 + mask + x20) & ~mask;
    r.hi = (param_1 + mask + x19) & ~mask;
    return r;
}

/* FUN_0034e8d4 @ 0x0034e8d4   (est. sk06_e8d4_frame_capture)
 * Ghidra: void FUN_0034e8d4(void)
 * Continuation thunk: x20 <- fp-0x78, then loads x0=x22, x1=x26, x2=0.
 * No memory side effect. Confidence: low. */
void sk06_e8d4_frame_capture(void)
{
    /* mov x20,x29-0x78 ; mov x0,x22 ; mov x1,x26 ; mov x2,#0 ; ret */
}

/* FUN_0034e8e8 @ 0x0034e8e8   (est. sk06_e8e8_frame_capture_b)
 * Ghidra: void FUN_0034e8e8(void)
 * As FUN_0034e8d4 but loads x1=x28. Continuation thunk. Confidence: low. */
void sk06_e8e8_frame_capture_b(void)
{
    /* mov x20,x29-0x78 ; mov x0,x22 ; mov x1,x28 ; mov x2,#0 ; ret */
}

/* FUN_0034e8fc @ 0x0034e8fc   (est. sk06_e8fc_tag_offsets)
 * Ghidra: void FUN_0034e8fc(void)
 * Register-only: w11<-w20+0x37, w10<-w20+0x57, w12<-w20+0x30, then flags from
 * cmp x20,#0xb. Computes object-tag offsets for the caller. Confidence: low. */
void sk06_e8fc_tag_offsets(void)
{
    /* w11<-w20+0x37 ; w10<-w20+0x57 ; w12<-w20+0x30 ; cmp x20,#0xb — reg-only */
}

/* FUN_0034e910 @ 0x0034e910   (est. sk06_e910_cap_width)
 * Ghidra: void FUN_0034e910(void)
 * Selects a capability/index width: x8 = (x22 & 0xffffffffffff) normally, or
 * (x28 >> 0x38 & 0xf) when x28 has the 0x2000000000000000 "width bit" set.
 * Classic Swift tagged-value width decode. Confidence: low. */
void sk06_e910_cap_width(void)
{
    /* x8 = (x28 & 0x2000000000000000) ? ((x28>>0x38) & 0xf)
     *                                   : (x22 & 0xffffffffffff) — reg-only */
}

/* FUN_0034e924 @ 0x0034e924   (est. sk06_e924_slot_args)
 * Ghidra: void FUN_0034e924(void)
 * Continuation thunk: x8 <- *[x9+0x10]! , x1 <- x20+x8, x0<-x27, x2<-x19.
 * Sets up argument registers for a slot/descriptor call. Confidence: low. */
void sk06_e924_slot_args(void)
{
    /* ldr x10,[x9,#0x10]! ; add x1,x20,x8 ; mov x0,x27 ; mov x2,x19 ; ret */
}

/* FUN_0034e938 @ 0x0034e938   (est. sk06_e938_ctz_clear)
 * Ghidra: void FUN_0034e938(void)
 * x8 <- count-trailing-zeros(x27); x27 <- x27 & (x27-1) (clear lowest set
 * bit). Bit-scan helper on a bitmap word. Confidence: low. */
void sk06_e938_ctz_clear(void)
{
    /* x8 <- ctz(x27) ; x27 &= x27-1 — register-only bitmap scan */
}

/* FUN_0034e94c @ 0x0034e94c   (est. sk06_e94c_context_args)
 * Ghidra: void FUN_0034e94c(void)
 * Continuation thunk: loads x8 <- *[x9+0x10]! where x9 is loaded from fp-0x60,
 * then x0<-x26, x1<-*(fp-0xa0). Confidence: low. */
void sk06_e94c_context_args(void)
{
    /* ldur x9,[x29,#-0x60] ; ldr x8,[x9,#0x10]! ; mov x0,x26 ; ldur x1,[x29,#-0xa0] */
}

/* FUN_0034e960 @ 0x0034e960   (est. sk06_e960_stack_args)
 * Ghidra: void FUN_0034e960(void)
 * Continuation thunk: x20 <- sp+0x18, x0<-x22, x1<-x19, x2<-0. Confidence: low. */
void sk06_e960_stack_args(void)
{
    /* add x20,sp,#0x18 ; mov x0,x22 ; mov x1,x19 ; mov x2,#0 ; ret */
}

/* FUN_0034e974 @ 0x0034e974   (est. sk06_e974_store_advance)
 * Ghidra: void FUN_0034e974(undefined8 param_1)
 * Stores param_1 at *x19, then advances x19 to x19' = param_1 + ((x9+0x10)
 * & ((x9 & 0xf8) ^ 0x1f8)). Single-slot store with alignment advance
 * (Swift storage-buffer append). Confidence: low. */
void sk06_e974_store_advance(word_t *x19, word_t value, word_t x9)
{
    *x19 = value;
    /* x19 advanced to value + ((x9+0x10) & ((x9 & 0xf8) ^ 0x1f8)) for caller. */
}

/* FUN_0034e990 @ 0x0034e990   (est. sk06_e990_ctx_load)
 * Ghidra: void FUN_0034e990(void)
 * Continuation thunk: x19<-x0, x21 <- *(fp-0xc8), x8<-x21, x9 <- *[x8+8]!.
 * Confidence: low. */
void sk06_e990_ctx_load(void)
{
    /* mov x19,x0 ; ldur x21,[x29,#-0xc8] ; mov x8,x21 ; ldr x9,[x8,#0x8]! ; ret */
}

/* FUN_0034e9a4 @ 0x0034e9a4   (est. sk06_e9a4_mask_clr)
 * Ghidra: void FUN_0034e9a4(void)
 * w23 <- w22 & ~((-1) << w8); then x0 <- x19. Register-only mask-clear thunk.
 * Confidence: low. */
void sk06_e9a4_mask_clr(void)
{
    /* w23 = w22 & ~((word32_t)-1 << w8) ; x0<-x19 — register-only */
}

/* FUN_0034e9b8 @ 0x0034e9b8   (est. sk06_e9b8_meta_pair)
 * Ghidra: undefined1 [16] FUN_0034e9b8(void)
 * Returns {*(fp-0x60), *(fp-0x60+8)} (a two-word descriptor/value from the
 * caller frame); sets x2 <- &DAT_005cf680, x8<-x23, w3<-0x21, w4<-0x2.
 * Swift metadata accessor thunk. Confidence: low.
 * Notes: DAT_005cf680 (0x5cf680) descriptor; string-type metadata flags. */
sk06_pair_t sk06_e9b8_meta_pair(word_t lo, word_t hi)
{
    sk06_pair_t r;
    r.lo = lo;   /* *(fp-0x60) */
    r.hi = hi;   /* *(fp-0x60+8) */
    return r;
}

/* FUN_0034e9d4 @ 0x0034e9d4   (est. sk06_e9d4_meta_args)
 * Ghidra: void FUN_0034e9d4(void)
 * Continuation thunk: x6 <- &DAT_005ce5d0, w1<-0xb, w2<-0x2 (Swift string
 * metadata descriptor + length/flags for the caller). Confidence: low.
 * Notes: DAT_005ce5d0 (0x5ce5d0) string metadata. */
void sk06_e9d4_meta_args(void)
{
    /* adrp x6,0x5ce000; add x6,x6,#0x5d0; mov w1,#0xb; mov w2,#0x2; ret */
}

/* FUN_0034e9e8 @ 0x0034e9e8   (est. sk06_e9e8_cmp1)
 * Ghidra: bool FUN_0034e9e8(ulong param_1)
 * Returns (param_1 > 1); also sets x1<-x22, w2<-1. Confidence: low. */
bool sk06_e9e8_cmp1(word_t param_1)
{
    return 1 < param_1;
}

/* FUN_0034e9fc @ 0x0034e9fc   (est. sk06_e9fc_mul10)
 * Ghidra: void FUN_0034e9fc(void)
 * Register-only: x21<-0; w11 = (x8*x9 high word != 0); x8 <- x8*10
 * (x8 + x8<<2 then <<1). Multiplication-with-overflow-detect thunk.
 * Confidence: low. */
void sk06_e9fc_mul10(void)
{
    /* x21<-0 ; w11 = ((x8*x9)>>64 != 0) ; x8 *= 10 — register-only */
}

/* FUN_0034ea18 @ 0x0034ea18   (est. sk06_ea18_buf_args)
 * Ghidra: void FUN_0034ea18(void)
 * Continuation thunk: x19<-x0; x8 <- *[x22+8]!; x0<-x23, x1<-x21.
 * Confidence: low. */
void sk06_ea18_buf_args(void)
{
    /* mov x19,x0 ; ldr x8,[x22,#0x8]! ; mov x0,x23 ; mov x1,x21 ; ret */
}

/* FUN_0034ea2c @ 0x0034ea2c   (est. sk06_ea2c_pair_677790)
 * Ghidra: undefined1 [16] FUN_0034ea2c(void)
 * Returns {fp-0x58, 0x677790} (a context pointer + metadata descriptor).
 * Confidence: low. Notes: DAT_00677790 (0x677790) metadata descriptor. */
sk06_pair_t sk06_ea2c_pair_677790(word_t fp_minus_0x58)
{
    sk06_pair_t r;
    r.lo = fp_minus_0x58;
    r.hi = 0x677790;   /* DAT_00677790 */
    return r;
}

/* FUN_0034ea40 @ 0x0034ea40   (est. sk06_ea40_sp_adjust)
 * Ghidra: void FUN_0034ea40(void)
 * x9 <- x9 - x12; stores it at *(fp-0x58); sp <- x9; x9 <- x8. Stack-pointer
 * adjustment (stack allocation) thunk. Confidence: low. */
void sk06_ea40_sp_adjust(void)
{
    /* sub x9,x9,x12 ; stur x9,[x29,#-0x58] ; mov sp,x9 ; mov x9,x8 ; ret */
}

/* FUN_0034ea54 @ 0x0034ea54   (est. sk06_ea54_sp_adjust_b)
 * Ghidra: void FUN_0034ea54(void)
 * x8 <- sp - x12; stores at *(fp-0xc8); sp <- x8. Stack-pointer adjustment.
 * Confidence: low. */
void sk06_ea54_sp_adjust_b(void)
{
    /* mov x8,sp ; sub x8,x8,x12 ; stur x8,[x29,#-0xc8] ; mov sp,x8 ; ret */
}

/* FUN_0034ea68 @ 0x0034ea68   (est. sk06_ea68_meta_args_b)
 * Ghidra: void FUN_0034ea68(void)
 * As FUN_0034e9d4 but x6 <- &DAT_005ce3f0. Continuation thunk. Confidence: low.
 * Notes: DAT_005ce3f0 (0x5ce3f0) string metadata. */
void sk06_ea68_meta_args_b(void)
{
    /* adrp x6,0x5ce000; add x6,x6,#0x3f0; mov w1,#0xb; mov w2,#0x2; ret */
}

/* FUN_0034ea7c @ 0x0034ea7c   (est. sk06_ea7c_spread_args)
 * Ghidra: void FUN_0034ea7c(void)
 * Register-spread continuation thunk: x3<-x0, x8<-x23, x0<-x22, x1<-x19,
 * x2<-x21, x4<-x20. Reorders args for a downstream call. Confidence: low. */
void sk06_ea7c_spread_args(void)
{
    /* mov x3,x0; mov x8,x23; mov x0,x22; mov x1,x19; mov x2,x21; mov x4,x20 */
}

/* FUN_0034eaac @ 0x0034eaac   (est. sk06_eaac_load_args)
 * Ghidra: undefined8 FUN_0034eaac(void)
 * Loads x9,x20 <- *(fp-0x60); x8 <- *[x9+0x10]!; returns x0<-x20, x1<-x23.
 * Continuation thunk. Confidence: low. */
word_t sk06_eaac_load_args(word_t x20)
{
    return x20;   /* from *(fp-0x60) */
}

/* FUN_0034eac0 @ 0x0034eac0   (est. sk06_eac0_ctx_load_b)
 * Ghidra: void FUN_0034eac0(void)
 * Continuation thunk: x20<-x0; x27 <- *(fp-0xd8); x8<-x27; x9 <- *[x8+8]!.
 * Confidence: low. */
void sk06_eac0_ctx_load_b(void)
{
    /* mov x20,x0 ; ldur x27,[x29,#-0xd8] ; mov x8,x27 ; ldr x9,[x8,#0x8]! ; ret */
}

/* FUN_0034ead4 @ 0x0034ead4   (est. sk06_ead4_load_arg)
 * Ghidra: undefined8 FUN_0034ead4(void)
 * Continuation thunk: x8<-x0; x23 <- *(fp-0xa8); returns x0<-x23, x1<-x27.
 * Confidence: low. */
word_t sk06_ead4_load_arg(word_t x23)
{
    return x23;   /* from *(fp-0xa8) */
}

/* FUN_0034eae8 @ 0x0034eae8   (est. sk06_eae8_load_arg_b)
 * Ghidra: undefined8 FUN_0034eae8(void)
 * As FUN_0034ead4 but reads *(fp-0xa0) and returns with x1<-x26.
 * Confidence: low. */
word_t sk06_eae8_load_arg_b(word_t x23)
{
    return x23;   /* from *(fp-0xa0) */
}

/* FUN_0034eafc @ 0x0034eafc   (est. sk06_eafc_spread_args_b)
 * Ghidra: void FUN_0034eafc(void)
 * Register-spread thunk: x8<-x0; x20<-x27; x0<-x25, x1<-x24. Confidence: low. */
void sk06_eafc_spread_args_b(void)
{
    /* mov x8,x0; mov x20,x27; mov x0,x25; mov x1,x24; ret */
}

/* FUN_0034eb10 @ 0x0034eb10   (est. sk06_eb10_spread_args_c)
 * Ghidra: void FUN_0034eb10(void)
 * Register-spread thunk: x8<-x0; x0<-x23, x1<-x20, x20<-x22, x2<-x21, x3<-x19.
 * Confidence: low. */
void sk06_eb10_spread_args_c(void)
{
    /* mov x8,x0; mov x0,x23; mov x1,x20; mov x20,x22; mov x2,x21; mov x3,x19 */
}

/* FUN_0034eb2c @ 0x0034eb2c   (est. sk06_eb2c_sp_adjust_c)
 * Ghidra: void FUN_0034eb2c(long param_1)
 * x8 <- sp - param_1; stores at *(fp-0xa0); sp <- x8. Stack allocation.
 * Confidence: low. */
void sk06_eb2c_sp_adjust_c(word_t param_1)
{
    /* mov x9,sp ; sub x8,x9,x8 ; stur x8,[x29,#-0xa0] ; mov sp,x8 ; ret */
}

/* FUN_0034eb40 @ 0x0034eb40   (est. sk06_eb40_sp_adjust_d)
 * Ghidra: void FUN_0034eb40(long param_1)
 * As FUN_0034eb2c but stores at *(fp-0xe8). Stack allocation. Confidence: low. */
void sk06_eb40_sp_adjust_d(word_t param_1)
{
    /* mov x9,sp ; sub x8,x9,x8 ; stur x8,[x29,#-0xe8] ; mov sp,x8 ; ret */
}

/* FUN_0034eb54 @ 0x0034eb54   (est. sk06_eb54_spread_args_d)
 * Ghidra: void FUN_0034eb54(void)
 * Register-spread thunk: x20<-x0; x22<-x1; x0<-x19. Confidence: low. */
void sk06_eb54_spread_args_d(void)
{
    /* mov x20,x0; mov x22,x1; mov x0,x19; ret */
}

/* FUN_0034eb64 @ 0x0034eb64   (est. sk06_eb64_spread_args_e)
 * Ghidra: void FUN_0034eb64(void)
 * Register-spread thunk: x1<-x21, x2<-x22, x3<-x19. Confidence: low. */
void sk06_eb64_spread_args_e(void)
{
    /* mov x1,x21; mov x2,x22; mov x3,x19; ret */
}

/* FUN_0034eb74 @ 0x0034eb74   (est. sk06_eb74_width_decode)
 * Ghidra: void FUN_0034eb74(void)
 * x8 = (x8) or (x23>>0x38 & 0xf) when x23 has width bit 0x2000000000000000.
 * Tagged-value width decode. Confidence: low. */
void sk06_eb74_width_decode(void)
{
    /* x8 = (x23 & 0x2000000000000000) ? ((x23>>0x38) & 0xf) : x8 — reg-only */
}

/* FUN_0034eb84 @ 0x0034eb84   (est. sk06_eb84_load_args)
 * Ghidra: void FUN_0034eb84(void)
 * Continuation thunk: x8 <- *[x21+8]!; x0<-x22, x1<-x19. Confidence: low. */
void sk06_eb84_load_args(void)
{
    /* ldr x8,[x21,#0x8]! ; mov x0,x22 ; mov x1,x19 ; ret */
}

/* FUN_0034eb94 @ 0x0034eb94   (est. sk06_eb94_load_args_b)
 * Ghidra: void FUN_0034eb94(void)
 * Continuation thunk: x8 <- *[x21+8]!; x0<-x23, x1<-x19. Confidence: low. */
void sk06_eb94_load_args_b(void)
{
    /* ldr x8,[x21,#0x8]! ; mov x0,x23 ; mov x1,x19 ; ret */
}

/* FUN_0034eba4 @ 0x0034eba4   (est. sk06_eba4_spread_args_f)
 * Ghidra: void FUN_0034eba4(void)
 * Register-spread thunk: x20<-x25; x0<-x25, x1<-x26. Confidence: low. */
void sk06_eba4_spread_args_f(void)
{
    /* mov x20,x25; mov x0,x25; mov x1,x26; ret */
}

/* FUN_0034ebe0 @ 0x0034ebe0   (est. sk06_ebe0_ceil_div2)
 * Ghidra: void FUN_0034ebe0(void)
 * Register-only: w13 = ((w13 + ~((-1)<<w8)) >> w8) + 1; then w25 <- (2 or 4)
 * depending on whether w13 < 0x10000. Round-up + bucket-size select.
 * Confidence: low. */
void sk06_ebe0_ceil_div2(void)
{
    /* w13 = ((w13 + ~((word32_t)-1<<w8)) >> w8) + 1 ;
     * w25 = (w13 < 0x10000) ? 2 : 4 — register-only */
}

/* FUN_0034ec0c @ 0x0034ec0c   (est. sk06_ec0c_tag_test)
 * Ghidra: void FUN_0034ec0c(void)
 * x8 <- x10 | x0; tests x8 & ~0x7f7f7f7f7f7f7f80; x8 <- 0xa000000000000000
 * (tag mask test for Swift small-string / tagged pointers). Confidence: low. */
void sk06_ec0c_tag_test(void)
{
    /* orr x8,x10,x0 ; tst x8,#-0x7f7f7f7f7f7f7f80 ; mov x8,#-0x6000000000000000 */
}

/* FUN_0034ec1c @ 0x0034ec1c   (est. sk06_ec1c_spread_args_g)
 * Ghidra: void FUN_0034ec1c(void)
 * Large register-swap thunk: shuffles x22/x24/x28/x26/x19/x20 across the
 * context. Pure register rearrangement. Confidence: low. */
void sk06_ec1c_spread_args_g(void)
{
    /* mov x24,x22; mov x22,x28; ldur x28,[x29,#-0x98]; mov x8,x28;
     * mov x0,x20; mov x1,x22; mov x2,x26; mov x20,x24; mov x3,x24; mov x4,x19 */
}

/* FUN_0034ec48 @ 0x0034ec48   (est. sk06_ec48_vec_xor)
 * Ghidra: void FUN_0034ec48(void)
 * q0 <- q0 ^ q1 (SIMD XOR of two 16-byte vectors); stores {q2,q0} at
 * sp+0x10; x20 <- sp+0x8. Vector combine helper. Confidence: low. */
void sk06_ec48_vec_xor(void)
{
    /* eor v0.16B,v0.16B,v1.16B ; stp q2,q0,[sp,#0x10] ; add x20,sp,#0x8 ; ret */
}

/* FUN_0034ec58 @ 0x0034ec58   (est. sk06_ec58_spread_args_h)
 * Ghidra: void FUN_0034ec58(void)
 * Register-spread thunk: x21<-x22; x0<-x23, x1<-x24. Confidence: low. */
void sk06_ec58_spread_args_h(void)
{
    /* mov x21,x22; mov x0,x23; mov x1,x24; ret */
}

/* FUN_0034ec68 @ 0x0034ec68   (est. sk06_ec68_spread_args_i)
 * Ghidra: void FUN_0034ec68(void)
 * Register-spread thunk: x21<-x22; x0<-x25, x1<-x26. Confidence: low. */
void sk06_ec68_spread_args_i(void)
{
    /* mov x21,x22; mov x0,x25; mov x1,x26; ret */
}

/* FUN_0034ec78 @ 0x0034ec78   (est. sk06_ec78_spread_args_j)
 * Ghidra: void FUN_0034ec78(void)
 * Register-spread thunk: x8<-sp+0x8; x0<-x25, x1<-x26. Confidence: low. */
void sk06_ec78_spread_args_j(void)
{
    /* add x8,sp,#0x8 ; mov x0,x25 ; mov x1,x26 ; ret */
}

/* FUN_0034ec88 @ 0x0034ec88   (est. sk06_ec88_load_args_c)
 * Ghidra: void FUN_0034ec88(void)
 * Continuation thunk: x9 <- *(fp-0x60); x8 <- *[x9+8]!; x0<-x26.
 * Confidence: low. */
void sk06_ec88_load_args_c(void)
{
    /* ldur x9,[x29,#-0x60] ; ldr x8,[x9,#0x8]! ; mov x0,x26 ; ret */
}

/* FUN_0034ec98 @ 0x0034ec98   (est. sk06_ec98_pair_stack)
 * Ghidra: undefined1 [16] FUN_0034ec98(void)
 * Returns {sp+0x8, *(sp+0x20)} (a descriptor/value pair loaded from the
 * stack). Confidence: low. */
sk06_pair_t sk06_ec98_pair_stack(word_t stack_hi)
{
    sk06_pair_t r;
    r.lo = 0;            /* sp+0x8 (address of the stack buffer) */
    r.hi = stack_hi;     /* *(sp+0x20) */
    return r;
}

/* FUN_0034eca8 @ 0x0034eca8   (est. sk06_eca8_loop_step)
 * Ghidra: void FUN_0034eca8(void)
 * Register-only loop step: x9<-x12|x9; x10<-x10+8; x8<-x8-1 (sets flags).
 * Iteration counter/accumulator update. Confidence: low. */
void sk06_eca8_loop_step(void)
{
    /* x9 |= x12 ; x10 += 8 ; x8 -= 1 — register-only */
}

/* FUN_0034ecb8 @ 0x0034ecb8   (est. sk06_ecb8_tailcall_setup)
 * Ghidra: void FUN_0034ecb8(void)
 * x21 <- *x20; x16<-x21, x17<-x20 (sets up an indirect tail-call via x16/x17).
 * Confidence: low. */
void sk06_ecb8_tailcall_setup(void)
{
    /* ldr x21,[x20] ; mov x16,x21 ; mov x17,x20 ; ret */
}

/* FUN_0034ecc8 @ 0x0034ecc8   (est. sk06_ecc8_tag_range_cmp)
 * Ghidra: void FUN_0034ecc8(void)
 * Compares (x0 & 0xff00000000) against 0x100000000 (sets flags). Tag-range
 * test. Confidence: low. */
void sk06_ecc8_tag_range_cmp(void)
{
    /* cmp (x0 & 0xff00000000), #0x100000000 — register-only flag set */
}

/* FUN_0034ecd8 @ 0x0034ecd8   (est. sk06_ecd8_rot_cmp)
 * Ghidra: void FUN_0034ecd8(void)
 * w8 <- ror(w8,7); w9 <- (w8 < 9). Rotate + range test (Swift tag rotate).
 * Confidence: low. */
void sk06_ecd8_rot_cmp(void)
{
    /* w8 = ror(w8,7) ; w9 = (w8 < 9) — register-only */
}

/* FUN_0034ece8 @ 0x0034ece8   (est. sk06_ece8_tailcall_setup_b)
 * Ghidra: void FUN_0034ece8(void)
 * x8<-x1; x16 <- *[x8-8]!; x17<-x8 (tail-call pointer setup). Confidence: low. */
void sk06_ece8_tailcall_setup_b(void)
{
    /* mov x8,x1 ; ldr x16,[x8,#-0x8]! ; mov x17,x8 ; ret */
}

/* FUN_0034ecf8 @ 0x0034ecf8   (est. sk06_ecf8_spread_args_k)
 * Ghidra: void FUN_0034ecf8(void)
 * Register-spread thunk: x19<-x0; x20<-x1; x0<-x27. Confidence: low. */
void sk06_ecf8_spread_args_k(void)
{
    /* mov x19,x0; mov x20,x1; mov x0,x27; ret */
}

/* FUN_0034ed08 @ 0x0034ed08   (est. sk06_ed08_zero)
 * Ghidra: undefined8 FUN_0034ed08(void)
 * Returns 0 after x19<-x0, x20<-x8. Zero result thunk. Confidence: low. */
word_t sk06_ed08_zero(void)
{
    return 0;
}

/* FUN_0034ed18 @ 0x0034ed18   (est. sk06_ed18_spread_args_l)
 * Ghidra: void FUN_0034ed18(void)
 * Register-spread thunk: x2<-x0; x0<-x20, x1<-x19. Confidence: low. */
void sk06_ed18_spread_args_l(void)
{
    /* mov x2,x0; mov x0,x20; mov x1,x19; ret */
}

/* FUN_0034ed28 @ 0x0034ed28   (est. sk06_ed28_pair_frame)
 * Ghidra: undefined1 [16] FUN_0034ed28(void)
 * x8 <- *[x9+8]!; returns {*(fp-0x58), *(fp-0x48)}. Frame-loaded pair.
 * Confidence: low. */
sk06_pair_t sk06_ed28_pair_frame(word_t lo, word_t hi)
{
    sk06_pair_t r;
    r.lo = lo;   /* *(fp-0x58) */
    r.hi = hi;   /* *(fp-0x48) */
    return r;
}

/* FUN_0034ed38 @ 0x0034ed38   (est. sk06_ed38_spread_args_m)
 * Ghidra: void FUN_0034ed38(void)
 * Register-spread thunk: x20<-x26; x0<-x23, x1<-x24. Confidence: low. */
void sk06_ed38_spread_args_m(void)
{
    /* mov x20,x26; mov x0,x23; mov x1,x24; ret */
}

/* FUN_0034ed48 @ 0x0034ed48   (est. sk06_ed48_spread_args_n)
 * Ghidra: void FUN_0034ed48(void)
 * Register-spread thunk: x20<-x26; x0<-x19, x1<-x22. Confidence: low. */
void sk06_ed48_spread_args_n(void)
{
    /* mov x20,x26; mov x0,x19; mov x1,x22; ret */
}

/* FUN_0034ed58 @ 0x0034ed58   (est. sk06_ed58_const_args)
 * Ghidra: void FUN_0034ed58(void)
 * Continuation thunk: w1<-0x100, x2<-x20, x3<-x26. Confidence: low. */
void sk06_ed58_const_args(void)
{
    /* mov w1,#0x100 ; mov x2,x20 ; mov x3,x26 ; ret */
}

/* FUN_0034ed68 @ 0x0034ed68   (est. sk06_ed68_spread_args_o)
 * Ghidra: void FUN_0034ed68(void)
 * Register-spread thunk: x0<-x24, x1<-x21, x2<-x20. Confidence: low. */
void sk06_ed68_spread_args_o(void)
{
    /* mov x0,x24; mov x1,x21; mov x2,x20; ret */
}

/* FUN_0034ed78 @ 0x0034ed78   (est. sk06_ed78_spread_args_p)
 * Ghidra: void FUN_0034ed78(void)
 * Register-spread thunk: x0<-x24, x1<-x19, x2<-x25. Confidence: low. */
void sk06_ed78_spread_args_p(void)
{
    /* mov x0,x24; mov x1,x19; mov x2,x25; ret */
}

/* FUN_0034ed88 @ 0x0034ed88   (est. sk06_ed88_spread_args_q)
 * Ghidra: void FUN_0034ed88(void)
 * Register-spread thunk: x0<-x24, x1<-x19, x2<-x22. Confidence: low. */
void sk06_ed88_spread_args_q(void)
{
    /* mov x0,x24; mov x1,x19; mov x2,x22; ret */
}

/* FUN_0034ed98 @ 0x0034ed98   (est. sk06_ed98_reorder)
 * Ghidra: void FUN_0034ed98(void)
 * Register-spread thunk: x22<-x2; x19<-x1; x20<-x0. Confidence: low. */
void sk06_ed98_reorder(void)
{
    /* mov x22,x2; mov x19,x1; mov x20,x0; ret */
}

/* FUN_0034eda8 @ 0x0034eda8   (est. sk06_eda8_spread_args_r)
 * Ghidra: void FUN_0034eda8(void)
 * Register-spread thunk: x1<-x23, x2<-x22, x3<-x21. Confidence: low. */
void sk06_eda8_spread_args_r(void)
{
    /* mov x1,x23; mov x2,x22; mov x3,x21; ret */
}

/* FUN_0034edb8 @ 0x0034edb8   (est. sk06_edb8_spread_args_s)
 * Ghidra: void FUN_0034edb8(void)
 * Register-spread thunk: x1<-x23, x2<-x21, x3<-x22. Confidence: low. */
void sk06_edb8_spread_args_s(void)
{
    /* mov x1,x23; mov x2,x21; mov x3,x22; ret */
}

/* FUN_0034edc8 @ 0x0034edc8   (est. sk06_edc8_spread_args_t)
 * Ghidra: void FUN_0034edc8(void)
 * Register-spread thunk: x0<-x23, x1<-x21, x2<-x19. Confidence: low. */
void sk06_edc8_spread_args_t(void)
{
    /* mov x0,x23; mov x1,x21; mov x2,x19; ret */
}

/* FUN_0034edd8 @ 0x0034edd8   (est. sk06_edd8_spread_args_u)
 * Ghidra: void FUN_0034edd8(void)
 * Register-spread thunk: x0<-x23, x1<-x25, x2<-x22. Confidence: low. */
void sk06_edd8_spread_args_u(void)
{
    /* mov x0,x23; mov x1,x25; mov x2,x22; ret */
}

/* FUN_0034ede8 @ 0x0034ede8   (est. sk06_ede8_spread_args_v)
 * Ghidra: void FUN_0034ede8(void)
 * Register-spread thunk: x0<-x23, x1<-x24, x2<-x21. Confidence: low. */
void sk06_ede8_spread_args_v(void)
{
    /* mov x0,x23; mov x1,x24; mov x2,x21; ret */
}

/* FUN_0034edf8 @ 0x0034edf8   (est. sk06_edf8_spread_args_w)
 * Ghidra: void FUN_0034edf8(void)
 * Register-spread thunk: x0<-x23, x1<-x20, x2<-x22. Confidence: low. */
void sk06_edf8_spread_args_w(void)
{
    /* mov x0,x23; mov x1,x20; mov x2,x22; ret */
}

/* FUN_0034ee08 @ 0x0034ee08   (est. sk06_ee08_spread_args_x)
 * Ghidra: void FUN_0034ee08(void)
 * Register-spread thunk: x0<-x26, x1<-x23, x2<-x21. Confidence: low. */
void sk06_ee08_spread_args_x(void)
{
    /* mov x0,x26; mov x1,x23; mov x2,x21; ret */
}

/* FUN_0034ee18 @ 0x0034ee18   (est. sk06_ee18_spread_args_y)
 * Ghidra: void FUN_0034ee18(void)
 * Register-spread thunk: x0<-x26, x1<-x19, x2<-x27. Confidence: low. */
void sk06_ee18_spread_args_y(void)
{
    /* mov x0,x26; mov x1,x19; mov x2,x27; ret */
}

/* FUN_0034ee28 @ 0x0034ee28   (est. sk06_ee28_spread_args_z)
 * Ghidra: void FUN_0034ee28(void)
 * Register-spread thunk: x0<-x26, x1<-x24, x2<-x23. Confidence: low. */
void sk06_ee28_spread_args_z(void)
{
    /* mov x0,x26; mov x1,x24; mov x2,x23; ret */
}

/* FUN_0034ee38 @ 0x0034ee38   (est. sk06_ee38_spread_args_aa)
 * Ghidra: void FUN_0034ee38(void)
 * Register-spread thunk: x0<-x26, x1<-x24, x2<-0. Confidence: low. */
void sk06_ee38_spread_args_aa(void)
{
    /* mov x0,x26; mov x1,x24; mov x2,#0x0; ret */
}

/* FUN_0034ee48 @ 0x0034ee48   (est. sk06_ee48_spread_args_ab)
 * Ghidra: void FUN_0034ee48(void)
 * Register-spread thunk: x0<-x25, x1<-x22, x2<-x23. Confidence: low. */
void sk06_ee48_spread_args_ab(void)
{
    /* mov x0,x25; mov x1,x22; mov x2,x23; ret */
}

/* FUN_0034ee58 @ 0x0034ee58   (est. sk06_ee58_load_args_d)
 * Ghidra: void FUN_0034ee58(void)
 * Continuation thunk: x8<-x25; x9 <- *[x8+0x10]!; x0<-x27. Confidence: low. */
void sk06_ee58_load_args_d(void)
{
    /* mov x8,x25 ; ldr x9,[x8,#0x10]! ; mov x0,x27 ; ret */
}

/* FUN_0034ee68 @ 0x0034ee68   (est. sk06_ee68_pair_zero)
 * Ghidra: undefined1 [16] FUN_0034ee68(ulong param_1)
 * Returns {0, param_1} (x22<-param_1, then x0<-0, x1<-param_1). Builds a
 * {nil, value} tagged pair. Confidence: low. */
sk06_pair_t sk06_ee68_pair_zero(word_t param_1)
{
    sk06_pair_t r;
    r.lo = 0;
    r.hi = param_1;
    return r;
}

/* FUN_0034ee78 @ 0x0034ee78   (est. sk06_ee78_reorder_b)
 * Ghidra: void FUN_0034ee78(void)
 * Register-spread thunk: x19<-x3; x20<-x1; x21<-x0. Confidence: low. */
void sk06_ee78_reorder_b(void)
{
    /* mov x19,x3; mov x20,x1; mov x21,x0; ret */
}

/* FUN_0034ee88 @ 0x0034ee88   (est. sk06_ee88_const_args_b)
 * Ghidra: void FUN_0034ee88(void)
 * Continuation thunk: w1<-0, w2<-1, x3<-x23. Confidence: low. */
void sk06_ee88_const_args_b(void)
{
    /* mov w1,#0x0 ; mov w2,#0x1 ; mov x3,x23 ; ret */
}

/* FUN_0034ee98 @ 0x0034ee98   (est. sk06_ee98_spread_args_ac)
 * Ghidra: void FUN_0034ee98(void)
 * Register-spread thunk: x0<-x27, x1<-x26, x2<-x22. Confidence: low. */
void sk06_ee98_spread_args_ac(void)
{
    /* mov x0,x27; mov x1,x26; mov x2,x22; ret */
}

/* FUN_0034eea8 @ 0x0034eea8   (est. sk06_eea8_ctx_load_c)
 * Ghidra: void FUN_0034eea8(void)
 * Continuation thunk: x20<-x0; x9 <- *(fp-0x68); x8 <- *[x9+8]!.
 * Confidence: low. */
void sk06_eea8_ctx_load_c(void)
{
    /* mov x20,x0 ; ldur x9,[x29,#-0x68] ; ldr x8,[x9,#0x8]! ; ret */
}

/* FUN_0034eeb8 @ 0x0034eeb8   (est. sk06_eeb8_spread_args_ad)
 * Ghidra: void FUN_0034eeb8(void)
 * Register-spread thunk: x20<-x0; x0<-x24, x1<-x19. Confidence: low. */
void sk06_eeb8_spread_args_ad(void)
{
    /* mov x20,x0; mov x0,x24; mov x1,x19; ret */
}

/* FUN_0034eec8 @ 0x0034eec8   (est. sk06_eec8_spread_args_ae)
 * Ghidra: void FUN_0034eec8(void)
 * Register-spread thunk: x20<-x0; x0<-x24, x1<-x21. Confidence: low. */
void sk06_eec8_spread_args_ae(void)
{
    /* mov x20,x0; mov x0,x24; mov x1,x21; ret */
}

/* FUN_0034eed8 @ 0x0034eed8   (est. sk06_eed8_ctx_load_d)
 * Ghidra: void FUN_0034eed8(void)
 * Continuation thunk: x20<-x0; x8 <- *(fp-0xa0); x9 <- *[x8+8]!.
 * Confidence: low. */
void sk06_eed8_ctx_load_d(void)
{
    /* mov x20,x0 ; ldur x8,[x29,#-0xa0] ; ldr x9,[x8,#0x8]! ; ret */
}

/* FUN_0034eee8 @ 0x0034eee8   (est. sk06_eee8_spread_args_af)
 * Ghidra: void FUN_0034eee8(void)
 * Register-spread thunk: x8<-x0; x20<-x24; x0<-x19. Confidence: low. */
void sk06_eee8_spread_args_af(void)
{
    /* mov x8,x0; mov x20,x24; mov x0,x19; ret */
}

/* FUN_0034eef8 @ 0x0034eef8   (est. sk06_eef8_spread_args_ag)
 * Ghidra: void FUN_0034eef8(void)
 * Register-spread thunk: x8<-x0; x0<-x25, x1<-x21. Confidence: low. */
void sk06_eef8_spread_args_ag(void)
{
    /* mov x8,x0; mov x0,x25; mov x1,x21; ret */
}

/* FUN_0034ef08 @ 0x0034ef08   (est. sk06_ef08_spread_args_ah)
 * Ghidra: void FUN_0034ef08(void)
 * Register-spread thunk: x2<-x24, x3<-x23, x4<-x22. Confidence: low. */
void sk06_ef08_spread_args_ah(void)
{
    /* mov x2,x24; mov x3,x23; mov x4,x22; ret */
}

/* FUN_0034ef18 @ 0x0034ef18   (est. sk06_ef18_spread_args_ai)
 * Ghidra: void FUN_0034ef18(void)
 * Register-spread thunk: x20<-x23; x0<-x23, x1<-x22. Confidence: low. */
void sk06_ef18_spread_args_ai(void)
{
    /* mov x20,x23; mov x0,x23; mov x1,x22; ret */
}

/* FUN_0034ef28 @ 0x0034ef28   (est. sk06_ef28_spread_args_aj)
 * Ghidra: void FUN_0034ef28(void)
 * Register-spread thunk: x0<-x22, x1<-x28, x2<-x19. Confidence: low. */
void sk06_ef28_spread_args_aj(void)
{
    /* mov x0,x22; mov x1,x28; mov x2,x19; ret */
}

/* FUN_0034ef38 @ 0x0034ef38   (est. sk06_ef38_spread_args_ak)
 * Ghidra: void FUN_0034ef38(void)
 * Register-spread thunk: x0<-x22, x1<-x19, x2<-0. Confidence: low. */
void sk06_ef38_spread_args_ak(void)
{
    /* mov x0,x22; mov x1,x19; mov x2,#0x0; ret */
}

/* FUN_0034ef48 @ 0x0034ef48   (est. sk06_ef48_sp_adjust_e)
 * Ghidra: void FUN_0034ef48(void)
 * x28 <- sp - x12; sp <- x28. Stack-pointer adjustment thunk. Confidence: low. */
void sk06_ef48_sp_adjust_e(void)
{
    /* mov x9,sp ; sub x28,x9,x12 ; mov sp,x28 ; ret */
}

/* FUN_0034ef58 @ 0x0034ef58   (est. sk06_ef58_spread_args_al)
 * Ghidra: void FUN_0034ef58(void)
 * Register-spread thunk: x1<-x22, x2<-x23, x3<-x19. Confidence: low. */
void sk06_ef58_spread_args_al(void)
{
    /* mov x1,x22; mov x2,x23; mov x3,x19; ret */
}

/* FUN_0034ef68 @ 0x0034ef68   (est. sk06_ef68_spread_args_am)
 * Ghidra: void FUN_0034ef68(void)
 * Register-spread thunk: x0<-x20, x1<-x21, x2<-x19. Confidence: low. */
void sk06_ef68_spread_args_am(void)
{
    /* mov x0,x20; mov x1,x21; mov x2,x19; ret */
}

/* FUN_0034ef78 @ 0x0034ef78   (est. sk06_ef78_spread_args_an)
 * Ghidra: void FUN_0034ef78(void)
 * Register-spread thunk: x0<-x21, x1<-x23, x2<-x22. Confidence: low. */
void sk06_ef78_spread_args_an(void)
{
    /* mov x0,x21; mov x1,x23; mov x2,x22; ret */
}

/* FUN_0034ef88 @ 0x0034ef88   (est. sk06_ef88_pair_zero_b)
 * Ghidra: undefined8 FUN_0034ef88(void)
 * Returns 0 after x1<-x23, x2<-x26. Zero-result thunk. Confidence: low. */
word_t sk06_ef88_pair_zero_b(void)
{
    return 0;
}

/* FUN_0034ef98 @ 0x0034ef98   (est. sk06_ef98_spread_args_ao)
 * Ghidra: void FUN_0034ef98(void)
 * Register-spread thunk: x0<-x19, x1<-x25, x2<-x23. Confidence: low. */
void sk06_ef98_spread_args_ao(void)
{
    /* mov x0,x19; mov x1,x25; mov x2,x23; ret */
}

/* FUN_0034efa8 @ 0x0034efa8   (est. sk06_efa8_ctx_load_e)
 * Ghidra: void FUN_0034efa8(void)
 * Continuation thunk: x9<-x0; x23 <- *(fp-0x90); x8<-x23. Confidence: low. */
void sk06_efa8_ctx_load_e(void)
{
    /* mov x9,x0 ; ldur x23,[x29,#-0x90] ; mov x8,x23 ; ret */
}

/* FUN_0034efb8 @ 0x0034efb8   (est. sk06_efb8_ctx_load_f)
 * Ghidra: void FUN_0034efb8(void)
 * Continuation thunk: x9<-x0; x21 <- *(fp-0xc0); x8<-x21. Confidence: low. */
void sk06_efb8_ctx_load_f(void)
{
    /* mov x9,x0 ; ldur x21,[x29,#-0xc0] ; mov x8,x21 ; ret */
}

/* FUN_0034efc8 @ 0x0034efc8   (est. sk06_efc8_width_decode_b)
 * Ghidra: void FUN_0034efc8(void)
 * x3 = (x25 & 0xffffffffffff) or (x23>>0x38 & 0xf) if x23 has width bit.
 * Tagged-value width decode into x3. Confidence: low. */
void sk06_efc8_width_decode_b(void)
{
    /* x3 = (x23 & 0x2000000000000000) ? ((x23>>0x38) & 0xf)
     *                                  : (x25 & 0xffffffffffff) — reg-only */
}

/* FUN_0034efdc @ 0x0034efdc   (est. sk06_efdc_meta_field_30)
 * Ghidra: void FUN_0034efdc(void)
 * Calls swift_type_metadata_field_30(x24) and keeps the result in x19.
 * Thin metadata field-offset wrapper (PAC'd). Confidence: medium. */
void sk06_efdc_meta_field_30(void)
{
    word_t res = swift_type_metadata_field_30(0 /* x24 */);
    (void)res;   /* result kept in x19 for the caller's continuation */
}

/* FUN_0034eff8 @ 0x0034eff8   (est. sk06_eff8_meta_field_40)
 * Ghidra: void FUN_0034eff8(void)
 * Calls swift_type_metadata_field_40(x19); result in x8. Thin metadata
 * field-offset wrapper (PAC'd). Confidence: medium. */
void sk06_eff8_meta_field_40(void)
{
    word_t res = swift_type_metadata_field_40(0 /* x19 */);
    (void)res;   /* result kept in x8 */
}

/* FUN_0034f014 @ 0x0034f014   (est. sk06_f014_meta_field_c)
 * Ghidra: void FUN_0034f014(void)
 * Calls swift_type_metadata_field_c(x19); result in x8. Thin metadata
 * field-offset wrapper (PAC'd). Confidence: medium. */
void sk06_f014_meta_field_c(void)
{
    word_t res = swift_type_metadata_field_c(0 /* x19 */);
    (void)res;   /* result kept in x8 */
}

/* FUN_0034f030 @ 0x0034f030   (est. sk06_f030_str_encode)
 * Ghidra: void FUN_0034f030(void)
 * Tail-calls swift_small_string_encode(&DAT_005d021c, 1, 1): encodes the
 * small-string constant at DAT_005d021c into a Swift String. Confidence:
 * medium (shared helper identity). Notes: DAT_005d021c (0x5d021c) string. */
void sk06_f030_str_encode(void)
{
    swift_small_string_encode(0x5d021c, 1, 1);   /* DAT_005d021c */
}

/* FUN_0034f044 @ 0x0034f044   (est. sk06_f044_vt_dispatch)
 * Ghidra: void FUN_0034f044(undefined4 param_1)
 * Calls sk_vt_dispatch30(param_1, 1) (with x2=x26 context), then compares
 * the result flag to 1. PAC'd vtable-dispatch wrapper. Confidence: medium. */
void sk06_f044_vt_dispatch(word32_t param_1)
{
    sk_vt_dispatch30(param_1, 1, 0 /* x26 */);
}

/* FUN_0034f064 @ 0x0034f064   (est. sk06_f064_width_decode_c)
 * Ghidra: void FUN_0034f064(void)
 * x8 = (x0 & 0xffffffffffff) or (x1>>0x38 & 0xf) if x1 has width bit.
 * Tagged-value width decode. Confidence: low. */
word_t sk06_f064_width_decode_c(word_t x0, word_t x1)
{
    return (x1 & 0x2000000000000000ULL) ? ((x1 >> 0x38) & 0xf)
                                        : (x0 & 0xffffffffffffULL);
}

/* FUN_0034f078 @ 0x0034f078   (est. sk06_f078_reorder_c)
 * Ghidra: void FUN_0034f078(void)
 * Register-spread thunk: x22<-x0; x23<-x1; x0<-x20. Confidence: low. */
void sk06_f078_reorder_c(void)
{
    /* mov x22,x0; mov x23,x1; mov x0,x20; ret */
}

/* FUN_0034f088 @ 0x0034f088   (est. sk06_f088_build_6773c0)
 * Ghidra: void FUN_0034f088(undefined8 param_1)
 * Builds a Swift type-metadata / descriptor record at x24: descriptor
 * 0x6773c0, param_1, flags {0xd00000000000002f, 0x80000000005cebd0}, zero
 * at +0x20, 0 at +0x48 (byte); then tail-calls sk_metadata_hook_dispatch()
 * (FUN_0036986c). Confidence: medium (metadata builder).
 * Notes: DAT_006773c0 descriptor; DAT_005cebd0 metadata ref (0x5cebd0). */
void sk06_f088_build_6773c0(word_t param_1)
{
    word_t *rec = (word_t *)0 /* x24 */;
    rec[0] = 0x6773c0;                              /* DAT_006773c0 */
    rec[1] = param_1;
    rec[2] = 0xd00000000000002fULL;
    rec[3] = 0x80000000005cebd0ULL;                 /* 0x5cebd0 metadata */
    rec[4] = 0;
    *((uint8_t *)rec + 0x48) = 0;
    sk_metadata_hook_dispatch();
}

/* FUN_0034f0c0 @ 0x0034f0c0   (est. sk06_f0c0_build_676ed0)
 * Ghidra: void FUN_0034f0c0(undefined8 param_1)
 * As FUN_0034f088 with descriptor 0x676ed0 and flags
 * {0xd00000000000002e, 0x80000000005ceba0}; tail-calls the metadata hook.
 * Confidence: medium. Notes: DAT_00676ed0 descriptor; DAT_005ceba0 (0x5ceba0). */
void sk06_f0c0_build_676ed0(word_t param_1)
{
    word_t *rec = (word_t *)0 /* x24 */;
    rec[0] = 0x676ed0;                              /* DAT_00676ed0 */
    rec[1] = param_1;
    rec[2] = 0xd00000000000002eULL;
    rec[3] = 0x80000000005ceba0ULL;                 /* 0x5ceba0 metadata */
    rec[4] = 0;
    *((uint8_t *)rec + 0x48) = 0;
    sk_metadata_hook_dispatch();
}

/* FUN_0034f114 @ 0x0034f114   (est. sk06_f114_big_alloc)
 * Ghidra: void FUN_0034f114(void)
 * Tail-calls sk_big_alloc_2a4c98(0x29, 0xe100000000000000, 0, 1): a large
 * allocation with tag 0x29, size-bits, and flags. Confidence: low.
 * Notes: FUN_002a4c98 is the large allocator (also in manifest as
 * sk_region_obj_slice_07.c, unnamed). */
void sk06_f114_big_alloc(void)
{
    sk_big_alloc_2a4c98(0x29, 0xe100000000000000ULL, 0, 1);
}

/* FUN_0034f138 @ 0x0034f138   (est. sk06_f138_vt_dispatch2)
 * Ghidra: void FUN_0034f138(long param_1)
 * Two vtable dispatches: sk_vt_dispatch30(param_1 + x19 & ~x23, 1) then
 * sk_vt_dispatch30(param_1 + x20 & ~x23, 1), both with x2=x21 context.
 * PAC'd pair of indirect method calls. Confidence: medium. */
void sk06_f138_vt_dispatch2(word_t param_1)
{
    /* x19/x20/x23/x21 come from caller context. */
    sk_vt_dispatch30(param_1 + 0 & ~0, 1, 0);
    sk_vt_dispatch30(param_1 + 0 & ~0, 1, 0);
}

/* FUN_0034f174 @ 0x0034f174   (est. sk06_f174_meta_then_init)
 * Ghidra: void FUN_0034f174(undefined8 param_1)
 * Stores param_1 at *(fp-0x60); calls swift_type_metadata_field_30(x25),
 * keeps result in x26; tail-calls sk_swift_runtime_1df60(). Metadata
 * lookup followed by runtime lazy-init. Confidence: low. */
void sk06_f174_meta_then_init(word_t param_1)
{
    (void)param_1;   /* stored at *(fp-0x60) */
    word_t res = swift_type_metadata_field_30(0 /* x25 */);
    (void)res;       /* kept in x26 */
    sk_swift_runtime_1df60();
}

/* FUN_0034f198 @ 0x0034f198   (est. sk06_f198_reorder_d)
 * Ghidra: void FUN_0034f198(void)
 * Register-spread thunk: x20<-x0; x23<-x1; x0<-x22. Confidence: low. */
void sk06_f198_reorder_d(void)
{
    /* mov x20,x0; mov x23,x1; mov x0,x22; ret */
}

/* FUN_0034f1a8 @ 0x0034f1a8   (est. sk06_f1a8_field0x50)
 * Ghidra: void FUN_0034f1a8(void)
 * Calls sk_swift_field0x50_accessor (FUN_0006a4c0); result kept in x20, then
 * x0<-x25. PAC'd field-accessor wrapper. Confidence: medium. */
void sk06_f1a8_field0x50(void)
{
    word_t res = sk_swift_field0x50_accessor((word_t *)0 /* x0 */, 0 /* x1 */);
    (void)res;   /* kept in x20 */
}

/* FUN_0034f1c4 @ 0x0034f1c4   (est. sk06_f1c4_field_4)
 * Ghidra: void FUN_0034f1c4(void)
 * Calls swift_type_metadata_field_4 (FUN_0014ae44); result kept in x8, then
 * x0<-x24. PAC'd metadata field-offset wrapper. Confidence: medium. */
void sk06_f1c4_field_4(void)
{
    word_t res = swift_type_metadata_field_4(0 /* x0 */);
    (void)res;   /* kept in x8 */
}

/* FUN_0034f1e0 @ 0x0034f1e0   (est. sk06_f1e0_field_20)
 * Ghidra: void FUN_0034f1e0(void)
 * Calls swift_type_metadata_field_20 (FUN_000277b8) on x22; result kept in
 * x9. PAC'd metadata field-offset wrapper. Confidence: medium. */
void sk06_f1e0_field_20(void)
{
    word_t res = swift_type_metadata_field_20(0 /* x22 */);
    (void)res;   /* kept in x9 */
}

/* FUN_0034f1fc @ 0x0034f1fc   (est. sk06_f1fc_spread_args_ap)
 * Ghidra: void FUN_0034f1fc(void)
 * Register-spread thunk: x20<-x25; x3<-x25, x4<-x21. Confidence: low. */
void sk06_f1fc_spread_args_ap(void)
{
    /* mov x20,x25; mov x3,x25; mov x4,x21; ret */
}

/* FUN_0034f20c @ 0x0034f20c   (est. sk06_f20c_store_u24)
 * Ghidra: void FUN_0034f20c(void)
 * Stores w23 as a 16-bit value at *x19 and the high byte (w23>>0x10) at
 * x19+2 — writes a 3-byte field. Confidence: low. */
void sk06_f20c_store_u24(uint16_t *x19, word32_t w23)
{
    x19[0] = (uint16_t)w23;
    *((uint8_t *)x19 + 2) = (uint8_t)(w23 >> 0x10);
}

/* FUN_0034f21c @ 0x0034f21c   (est. sk06_f21c_width_decode_d)
 * Ghidra: void FUN_0034f21c(void)
 * x8 = (x8) or (x28>>0x38 & 0xf) if x28 has width bit 0x2000000000000000.
 * Tagged-value width decode. Confidence: low. */
void sk06_f21c_width_decode_d(void)
{
    /* x8 = (x28 & 0x2000000000000000) ? ((x28>>0x38) & 0xf) : x8 — reg-only */
}
