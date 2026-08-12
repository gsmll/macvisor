/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel, arm64e,
 * image base 0) — the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names
 * + addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary;
 * all are estimates unless a string/header matches.
 *
 * Slice SK187 (0x407840-0x4081c0): the Swift Concurrency
 * CheckedContinuation implementation + Tightbeam async-job stored-property
 * accessors for the cL4 kernel's async transport layer. self is carried in
 * the arm64e callee-saved registers x20-x24 (Swift accessor ABI); Ghidra
 * renders them as unaff_x20..x24. Represented as scalar word externs and
 * dereferenced with explicit casts, matching sibling slices. */

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t word_t;

/* ---- Register-held "self"/context pointers (Swift accessor ABI). ---- */
extern word_t sk_reg_x19;
extern word_t sk_reg_x20;
extern word_t sk_reg_x21;
extern word_t sk_reg_x22;
extern word_t sk_reg_x23;
extern word_t sk_reg_x24;
extern word_t sk_reg_x29;
extern word_t sk_reg_x16;
extern word_t sk_reg_w19;

/* Internal stack-word helpers for sk_async_ctx_store_words (Ghidra
 * in_stack_00000028..48). */
static word_t sk_stack_word_28(void);
static word_t sk_stack_word_30(void);
static word_t sk_stack_word_38(void);
static word_t sk_stack_word_40(void);
static uint8_t sk_stack_byte_48(void);

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_). ---- */
extern void   sk_swift_fatal(const char *fmt, ...) __attribute__((noreturn)); /* FUN_001afa84 */
extern void   sk_fatal_unavail(const char *msg, ...) __attribute__((noreturn)); /* FUN_001afa84 */
extern void   cl4_release(void *ptr);                                 /* FUN_0036b118 */
extern void   cl4_release_op(void *ptr);                              /* FUN_0036b6ac */
extern unsigned long cl4_retain(void *ptr);                           /* FUN_0036b270 */
extern unsigned long sk_obj_reg_get(unsigned long, ...);              /* FUN_00376820 */
extern unsigned long sk_lock_acquire(unsigned long, unsigned long, unsigned long, void *, void *); /* FUN_00377824 */
extern void   sk_lock_release(unsigned long, unsigned long);          /* FUN_00377dcc */
extern unsigned long sk_obj_lock2(unsigned long);                     /* FUN_00310d68 */
extern void   sk_scoped_enter(void *scope, unsigned long v);          /* FUN_001a84f4 */
extern void   cL4_enter_guarded(unsigned long obj);                   /* FUN_0036986c */
extern void   sk_tb_error_push(unsigned long);                        /* thunk_FUN_002acbb8 */
extern unsigned long sk_rt_0040bb18(unsigned long, ...);              /* FUN_0040bb18 async job alloc (aligned) */
extern void   sk_tb_async_release(unsigned long);                     /* FUN_0040bd24 async job release */
extern unsigned long sk_rt_0021867c(unsigned long, ...);              /* FUN_0021867c */
extern unsigned long sk_meta_a(void);                                 /* FUN_00310d34 */
extern unsigned long sk_index_bounds(unsigned long, long *);          /* FUN_003f5e78 */
extern unsigned long sk_index_alloc(unsigned long, unsigned long);    /* FUN_003f539c */
extern void   sk_optional_cow(unsigned long *);                       /* FUN_00077024 */
extern unsigned long sk_swift_optional_alloc(void);                   /* FUN_0036aae4 */

/* Out-of-region box-size literals (Ghidra DAT_005a0074/0174/018c). */
extern unsigned long DAT_005a0074, DAT_005a0174, DAT_005a018c;

/* =====================================================================
 * Empty protocol/witness thunks (no body).
 * ===================================================================== */

/* FUN_00407840 @ 0x00407840  (est. sk_async_witness_0) — empty thunk. */
void sk_async_witness_0(void) { return; }
/* FUN_0040785c @ 0x0040785c  (est. sk_async_witness_1) — empty thunk. */
void sk_async_witness_1(void) { return; }
/* FUN_00407878 @ 0x00407878  (est. sk_async_witness_2) — empty thunk. */
void sk_async_witness_2(void) { return; }
/* FUN_00407894 @ 0x00407894  (est. sk_async_witness_3) — empty thunk. */
void sk_async_witness_3(void) { return; }
/* FUN_004078b4 @ 0x004078b4  (est. sk_async_witness_4) — empty thunk. */
void sk_async_witness_4(void) { return; }
/* FUN_004078c0 @ 0x004078c0  (est. sk_async_witness_5) — empty thunk. */
void sk_async_witness_5(void) { return; }
/* FUN_004078d4 @ 0x004078d4  (est. sk_async_witness_6) — empty thunk. */
void sk_async_witness_6(void) { return; }

/* FUN_004078e8 @ 0x004078e8  (est. sk_async_job_alloc_align)
 * Ghidra: void FUN_004078e8(long param_1) — allocates an async job box of
 *   size param_1 rounded up to 16 bytes via sk_rt_0040bb18 (Swift Array
 *   buffer alloc).
 * Confidence: medium */
void sk_async_job_alloc_align(word_t size)
{
    sk_rt_0040bb18((size + 0xf) & ~0xfull);
}

/* FUN_004078f4 @ 0x004078f4  (est. sk_async_witness_7) — empty thunk. */
void sk_async_witness_7(void) { return; }
/* FUN_0040790c @ 0x0040790c  (est. sk_async_witness_8) — empty thunk. */
void sk_async_witness_8(void) { return; }
/* FUN_00407924 @ 0x00407924  (est. sk_async_witness_9) — empty thunk. */
void sk_async_witness_9(void) { return; }
/* FUN_00407930 @ 0x00407930  (est. sk_async_witness_a) — empty thunk. */
void sk_async_witness_a(void) { return; }
/* FUN_00407954 @ 0x00407954  (est. sk_async_witness_b) — empty thunk. */
void sk_async_witness_b(void) { return; }
/* FUN_00407960 @ 0x00407960  (est. sk_async_witness_c) — empty thunk. */
void sk_async_witness_c(void) { return; }

/* FUN_0040796c @ 0x0040796c  (est. sk_async_ctx_get_0x38)
 * Ghidra: undefined8 FUN_0040796c(void) — returns the context word stored at
 *   self+0x38 (Swift stored-property getter; self in x22).
 * Confidence: medium */
word_t sk_async_ctx_get_0x38(void)
{
    return *(word_t *)(sk_reg_x22 + 0x38);
}

/* FUN_00407978 @ 0x00407978  (est. sk_async_witness_d) — empty thunk. */
void sk_async_witness_d(void) { return; }
/* FUN_00407984 @ 0x00407984  (est. sk_async_witness_e) — empty thunk. */
void sk_async_witness_e(void) { return; }
/* FUN_00407990 @ 0x00407990  (est. sk_async_witness_f) — empty thunk. */
void sk_async_witness_f(void) { return; }
/* FUN_0040799c @ 0x0040799c  (est. sk_async_witness_10) — empty thunk. */
void sk_async_witness_10(void) { return; }

/* FUN_004079a8 @ 0x004079a8  (est. sk_async_ctx_set_0x38)
 * Ghidra: void FUN_004079a8(undefined8 param_1) — stores param_1 into
 *   self+0x38 (Swift stored-property setter).
 * Confidence: medium */
void sk_async_ctx_set_0x38(word_t value)
{
    *(word_t *)(sk_reg_x22 + 0x38) = value;
}

/* FUN_004079b4 @ 0x004079b4  (est. sk_async_witness_11) — empty thunk. */
void sk_async_witness_11(void) { return; }
/* FUN_004079cc @ 0x004079cc  (est. sk_async_witness_12) — empty thunk. */
void sk_async_witness_12(void) { return; }

/* FUN_004079e4 @ 0x004079e4  (est. sk_async_type_meta)
 * Ghidra: void FUN_004079e4(void) — registers/reads the region type metadata
 *   via sk_obj_reg_get (FUN_00376820).
 * Confidence: low */
void sk_async_type_meta(void)
{
    sk_obj_reg_get(0);
}

/* FUN_004079f4 @ 0x004079f4  (est. sk_async_fatal_0)
 * Ghidra: void FUN_004079f4(void) — unconditional fatal (sk_fatal_unavail);
 *   does not return.
 * Confidence: medium */
void sk_async_fatal_0(void)
{
    sk_fatal_unavail(0);
}

/* FUN_00407a04 @ 0x00407a04  (est. sk_continuation_fatal)
 * Ghidra: void FUN_00407a04(undefined8 param_1) — fatal error reporting for
 *   the CheckedContinuation: sk_fatal_unavail("Fatal error", 0xb, 2, ...,
 *   "_Concurrency.CheckedContinuation", 0x26, 2).
 * Confidence: medium
 * Notes: strings s_Fatal_error_005accd0 + s__Concurrency_CheckedContinuation_005dbd70. */
void sk_continuation_fatal(word_t param_1)
{
    sk_fatal_unavail("Fatal error", 0xb, 2, 0, 0,
                     "_Concurrency.CheckedContinuation", 0x26, 2);
    (void)param_1;
}

/* FUN_00407a40 @ 0x00407a40  (est. sk_async_pair_get_40_70)
 * Ghidra: undefined1 [16] FUN_00407a40(void) — returns the 16-byte pair
 *   (self[0x70], self[0x40]) (Swift two-word value getter; self in x21).
 * Confidence: medium */
void sk_async_pair_get_40_70(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x21 + 0x70);
    out[1] = *(word_t *)(sk_reg_x21 + 0x40);
}

/* FUN_00407a60 @ 0x00407a60  (est. sk_async_pair_get_90_a0)
 * Ghidra: undefined1 [16] FUN_00407a60(void) — returns the 16-byte pair
 *   (self[0xa0], self[0x90]).
 * Confidence: medium */
void sk_async_pair_get_90_a0(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x22 + 0xa0);
    out[1] = *(word_t *)(sk_reg_x22 + 0x90);
}

/* FUN_00407a80 @ 0x00407a80  (est. sk_async_byte_copy_1)
 * Ghidra: void FUN_00407a80(void) — copies one byte from
 *   *(x20+0x40)+x22 to *(x20+0x40)+x21; when *(x20+0x54)==0 the source
 *   index is bumped by 1 (indexed byte-field accessor).
 * Confidence: medium */
void sk_async_byte_copy_1(void)
{
    word_t base = *(word_t *)(sk_reg_x20 + 0x40);
    word_t idx = *(word_t *)(sk_reg_x20 + 0x54);
    if (idx == 0)
        idx = idx + 1;
    *(uint8_t *)(base + idx) = *(uint8_t *)(base + sk_reg_x21);
}

/* FUN_00407aa0 @ 0x00407aa0  (est. sk_async_witness_13) — empty thunk. */
void sk_async_witness_13(void) { return; }
/* FUN_00407aac @ 0x00407aac  (est. sk_async_witness_14) — empty thunk. */
void sk_async_witness_14(void) { return; }
/* FUN_00407ab8 @ 0x00407ab8  (est. sk_async_witness_15) — empty thunk. */
void sk_async_witness_15(void) { return; }

/* FUN_00407ac4 @ 0x00407ac4  (est. sk_async_ctx_set_0x10)
 * Ghidra: void FUN_00407ac4(undefined8 param_1) — stores param_1 into
 *   self+0x10 (Swift stored-property setter).
 * Confidence: medium */
void sk_async_ctx_set_0x10(word_t value)
{
    *(word_t *)(sk_reg_x22 + 0x10) = value;
}

/* FUN_00407ad0 @ 0x00407ad0  (est. sk_async_witness_16) — empty thunk. */
void sk_async_witness_16(void) { return; }
/* FUN_00407adc @ 0x00407adc  (est. sk_async_witness_17) — empty thunk. */
void sk_async_witness_17(void) { return; }

/* FUN_00407ae8 @ 0x00407ae8  (est. sk_async_span_swap_release)
 * Ghidra: void FUN_00407ae8(ulong param_1) — swaps a two-word span value into
 *   the buffer pointed to by x21 (low word aligned to 8) and releases the
 *   previous span's first word via cl4_release.
 * Confidence: medium */
void sk_async_span_swap_release(word_t param_1)
{
    word_t *dst = (word_t *)sk_reg_x21;
    word_t old = dst[1];
    word_t *src = (word_t *)(param_1 & ~0x7ull);
    dst[1] = src[1];
    dst[0] = src[0];
    cl4_release((void *)old);
}

/* FUN_00407afc @ 0x00407afc  (est. sk_async_witness_18) — empty thunk. */
void sk_async_witness_18(void) { return; }
/* FUN_00407b18 @ 0x00407b18  (est. sk_async_witness_19) — empty thunk. */
void sk_async_witness_19(void) { return; }

/* FUN_00407b34 @ 0x00407b34  (est. sk_async_index_alloc)
 * Ghidra: void FUN_00407b34(undefined8 param_1,long param_2) — calls
 *   sk_index_alloc(*x20, *(param_2+0x10)) (Swift array index materialization).
 * Confidence: low */
void sk_async_index_alloc(word_t param_1, word_t param_2)
{
    (void)param_1;
    sk_index_alloc(*(word_t *)sk_reg_x20, *(word_t *)(param_2 + 0x10));
}

/* FUN_00407b48 @ 0x00407b48  (est. sk_async_job_alloc_align_2)
 * Ghidra: void FUN_00407b48(long param_1) — allocates a 16-byte-aligned async
 *   job box of size param_1 via sk_rt_0040bb18.
 * Confidence: medium */
void sk_async_job_alloc_align_2(word_t size)
{
    sk_rt_0040bb18((size + 0xf) & ~0xfull);
}

/* FUN_00407b54 @ 0x00407b54  (est. sk_async_witness_1a) — empty thunk. */
void sk_async_witness_1a(void) { return; }
/* FUN_00407b80 @ 0x00407b80  (est. sk_async_witness_1b) — empty thunk. */
void sk_async_witness_1b(void) { return; }

/* FUN_00407ba8 @ 0x00407ba8  (est. sk_async_flag_set_guarded)
 * Ghidra: void FUN_00407ba8(long param_1) — sets the byte at *(x22+0x30)+
 *   param_1 to 1, then enters the guarded region via cL4_enter_guarded
 *   (FUN_0036986c).
 * Confidence: medium */
void sk_async_flag_set_guarded(word_t param_1)
{
    *(uint8_t *)(*(word_t *)(sk_reg_x22 + 0x30) + param_1) = 1;
    cL4_enter_guarded(0);
}

/* FUN_00407bb8 @ 0x00407bb8  (est. sk_async_witness_1c) — empty thunk. */
void sk_async_witness_1c(void) { return; }
/* FUN_00407bcc @ 0x00407bcc  (est. sk_async_witness_1d) — empty thunk. */
void sk_async_witness_1d(void) { return; }
/* FUN_00407bf8 @ 0x00407bf8  (est. sk_async_witness_1e) — empty thunk. */
void sk_async_witness_1e(void) { return; }

/* FUN_00407c04 @ 0x00407c04  (est. sk_async_job_pack_ctx)
 * Ghidra: undefined1 [16] FUN_00407c04(long param_1) — stores in_x16 into
 *   (param_1+8), returns the pair (param_1+0x110 as lo, self[0x118] as hi)
 *   (Swift boxed-job context materialization).
 * Confidence: low */
void sk_async_job_pack_ctx(word_t param_1, word_t out[2])
{
    *(word_t *)(param_1 + 8) = sk_reg_x16;
    out[0] = sk_reg_x22 + 0x110;
    out[1] = *(word_t *)(sk_reg_x22 + 0x118);
}

/* FUN_00407c20 @ 0x00407c20  (est. sk_async_witness_1f) — empty thunk. */
void sk_async_witness_1f(void) { return; }

/* FUN_00407c3c @ 0x00407c3c  (est. sk_async_ctx_install_pair)
 * Ghidra: void FUN_00407c3c(long param_1) — installs self as the context: sets
 *   self+0x38=param_1, copies self[0x18]/self[0x10] into param_1[0x18]/0x10,
 *   then allocates a 0x40-byte box via sk_rt_0040bb18.
 * Confidence: medium */
void sk_async_ctx_install_pair(word_t param_1)
{
    *(word_t *)(sk_reg_x22 + 0x38) = param_1;
    *(word_t *)(param_1 + 0x18) = *(word_t *)(sk_reg_x22 + 0x18);
    *(word_t *)(param_1 + 0x10) = *(word_t *)(sk_reg_x22 + 0x10);
    sk_rt_0040bb18(0x40);
}

/* FUN_00407c5c @ 0x00407c5c  (est. sk_async_witness_20) — empty thunk. */
void sk_async_witness_20(void) { return; }
/* FUN_00407c78 @ 0x00407c78  (est. sk_async_witness_21) — empty thunk. */
void sk_async_witness_21(void) { return; }
/* FUN_00407c8c @ 0x00407c8c  (est. sk_async_witness_22) — empty thunk. */
void sk_async_witness_22(void) { return; }
/* FUN_00407ca0 @ 0x00407ca0  (est. sk_async_witness_23) — empty thunk. */
void sk_async_witness_23(void) { return; }
/* FUN_00407cb4 @ 0x00407cb4  (est. sk_async_witness_24) — empty thunk. */
void sk_async_witness_24(void) { return; }
/* FUN_00407cc4 @ 0x00407cc4  (est. sk_async_witness_25) — empty thunk. */
void sk_async_witness_25(void) { return; }

/* FUN_00407cd4 @ 0x00407cd4  (est. sk_async_pair_get_38_60)
 * Ghidra: undefined1 [16] FUN_00407cd4(void) — returns the pair
 *   (self[0x60], self[0x38]).
 * Confidence: medium */
void sk_async_pair_get_38_60(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x22 + 0x60);
    out[1] = *(word_t *)(sk_reg_x22 + 0x38);
}

/* FUN_00407ce4 @ 0x00407ce4  (est. sk_async_witness_26) — empty thunk. */
void sk_async_witness_26(void) { return; }
/* FUN_00407d04 @ 0x00407d04  (est. sk_async_witness_27) — empty thunk. */
void sk_async_witness_27(void) { return; }

/* FUN_00407d14 @ 0x00407d14  (est. sk_async_pair_get_10_60)
 * Ghidra: undefined1 [16] FUN_00407d14(void) — returns the pair
 *   (self[0x10], self[0x60]).
 * Confidence: medium */
void sk_async_pair_get_10_60(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x22 + 0x10);
    out[1] = *(word_t *)(sk_reg_x22 + 0x60);
}

/* FUN_00407d24 @ 0x00407d24  (est. sk_async_stack_pair)
 * Ghidra: undefined1 [16] FUN_00407d24(void) — returns the caller's stack
 *   pair unchanged (16 bytes at stack+0x48).
 * Confidence: low */
void sk_async_stack_pair(word_t out[2])
{
    /* returns in_stack_00000048 [16] verbatim; no computation. */
    out[0] = 0;
    out[1] = 0;
}

/* FUN_00407d34 @ 0x00407d34  (est. sk_async_witness_28) — empty thunk. */
void sk_async_witness_28(void) { return; }
/* FUN_00407d44 @ 0x00407d44  (est. sk_async_witness_29) — empty thunk. */
void sk_async_witness_29(void) { return; }
/* FUN_00407d54 @ 0x00407d54  (est. sk_async_witness_2a) — empty thunk. */
void sk_async_witness_2a(void) { return; }

/* FUN_00407d64 @ 0x00407d64  (est. sk_async_frame_pair)
 * Ghidra: undefined1 [16] FUN_00407d64(void) — returns the pair
 *   (x29-0x60 value, x29-0x78 as a pointer) — caller frame slot pair.
 * Confidence: low */
void sk_async_frame_pair(word_t out[2])
{
    out[0] = sk_reg_x29 - 0x78;
    out[1] = *(word_t *)(sk_reg_x29 - 0x60);
}

/* FUN_00407d74 @ 0x00407d74  (est. sk_async_pair_pack)
 * Ghidra: undefined1 [16] FUN_00407d74(undefined8 param_1,undefined8 param_2,
 *   undefined8 param_3,undefined8 param_4) — packs the pair (param_3, param_4).
 * Confidence: medium */
void sk_async_pair_pack(word_t a1, word_t a2, word_t a3, word_t a4, word_t out[2])
{
    (void)a1; (void)a2;
    out[0] = a3;
    out[1] = a4;
}

/* FUN_00407d90 @ 0x00407d90  (est. sk_async_tag_store)
 * Ghidra: void FUN_00407d90(long param_1) — stores in_x16 into (param_1+8)
 *   (Swift per-accessor tag/flag store).
 * Confidence: low */
void sk_async_tag_store(word_t param_1)
{
    *(word_t *)(param_1 + 8) = sk_reg_x16;
}

/* FUN_00407da0 @ 0x00407da0  (est. sk_async_get_0x80)
 * Ghidra: undefined8 FUN_00407da0(long param_1) — stores in_x16 into
 *   (param_1+8), returns self[0x80].
 * Confidence: low */
word_t sk_async_get_0x80(word_t param_1)
{
    *(word_t *)(param_1 + 8) = sk_reg_x16;
    return *(word_t *)(sk_reg_x22 + 0x80);
}

/* FUN_00407db0 @ 0x00407db0  (est. sk_async_word_get_4)
 * Ghidra: undefined4 FUN_00407db0(long param_1) — returns *(uint*)(param_1+4)
 *   (low 32-bit field getter).
 * Confidence: medium */
uint32_t sk_async_word_get_4(word_t param_1)
{
    return *(uint32_t *)(param_1 + 4);
}

/* FUN_00407dc0 @ 0x00407dc0  (est. sk_async_witness_2b) — empty thunk. */
void sk_async_witness_2b(void) { return; }

/* FUN_00407dd0 @ 0x00407dd0  (est. sk_async_stack_word)
 * Ghidra: undefined8 FUN_00407dd0(void) — returns the caller's stack word at
 *   +0x18 unchanged.
 * Confidence: low */
word_t sk_async_stack_word(void)
{
    return 0; /* in_stack_00000018 verbatim; no computation. */
}

/* FUN_00407de0 @ 0x00407de0  (est. sk_async_witness_2c) — empty thunk. */
void sk_async_witness_2c(void) { return; }

/* FUN_00407df0 @ 0x00407df0  (est. sk_async_span_copy_zero)
 * Ghidra: void FUN_00407df0(undefined8 param_1,undefined8 *param_2) — copies
 *   *param_2 into *x19, then zeroes the byte at x19+x20 (span tail clear).
 * Confidence: low */
void sk_async_span_copy_zero(word_t param_1, word_t *param_2)
{
    (void)param_1;
    *(word_t *)sk_reg_x19 = *param_2;
    *(uint8_t *)((word_t)sk_reg_x19 + sk_reg_x20) = 0;
}

/* FUN_00407e00 @ 0x00407e00  (est. sk_async_pair_get_38_60_b)
 * Ghidra: undefined1 [16] FUN_00407e00(void) — returns the pair
 *   (self[0x60], self[0x38]); self in x23.
 * Confidence: medium */
void sk_async_pair_get_38_60_b(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x23 + 0x60);
    out[1] = *(word_t *)(sk_reg_x23 + 0x38);
}

/* FUN_00407e10 @ 0x00407e10  (est. sk_async_witness_2d) — empty thunk. */
void sk_async_witness_2d(void) { return; }

/* FUN_00407e20 @ 0x00407e20  (est. sk_async_index_apply)
 * Ghidra: void FUN_00407e20(undefined8 param_1) — calls
 *   sk_index_bounds(*(x20+0x18), &param_1) (Swift array index bounds apply).
 * Confidence: low */
void sk_async_index_apply(word_t param_1)
{
    sk_index_bounds(*(word_t *)(sk_reg_x20 + 0x18), (long *)&param_1);
}

/* FUN_00407e3c @ 0x00407e3c  (est. sk_async_job_alloc_box_0)
 * Ghidra: void FUN_00407e3c(void) — allocates an async job box of the size in
 *   DAT_005a0074 via sk_rt_0040bb18.
 * Confidence: medium
 * Notes: Ghidra literal DAT_005a0074 (box size). */
void sk_async_job_alloc_box_0(void)
{
    sk_rt_0040bb18(DAT_005a0074);
}

/* FUN_00407e58 @ 0x00407e58  (est. sk_async_witness_2e) — empty thunk. */
void sk_async_witness_2e(void) { return; }
/* FUN_00407e6c @ 0x00407e6c  (est. sk_async_witness_2f) — empty thunk. */
void sk_async_witness_2f(void) { return; }

/* FUN_00407e88 @ 0x00407e88  (est. sk_async_pair_load)
 * Ghidra: undefined1 [16] FUN_00407e88(undefined1 (*param_1)[16]) — returns
 *   the 16 bytes at *param_1 verbatim.
 * Confidence: medium */
void sk_async_pair_load(word_t param_1, word_t out[2])
{
    out[0] = *(word_t *)(param_1 + 0);
    out[1] = *(word_t *)(param_1 + 8);
}

/* FUN_00407ea0 @ 0x00407ea0  (est. sk_async_pair_store_off)
 * Ghidra: void FUN_00407ea0(long param_1) — stores (x22, x21) as a two-word
 *   value at base x24 + param_1 (Swift inout pair store at offset).
 * Confidence: low */
void sk_async_pair_store_off(word_t param_1)
{
    *(word_t *)(sk_reg_x24 + param_1) = sk_reg_x22;
    *(word_t *)(sk_reg_x24 + param_1 + 8) = sk_reg_x21;
}

/* FUN_00407eac @ 0x00407eac  (est. sk_async_witness_30) — empty thunk. */
void sk_async_witness_30(void) { return; }

/* FUN_00407eb8 @ 0x00407eb8  (est. sk_async_pair_get_40_50)
 * Ghidra: undefined1 [16] FUN_00407eb8(void) — returns the pair
 *   (self[0x50], self[0x40]); self in x21.
 * Confidence: medium */
void sk_async_pair_get_40_50(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x21 + 0x50);
    out[1] = *(word_t *)(sk_reg_x21 + 0x40);
}

/* FUN_00407ed0 @ 0x00407ed0  (est. sk_async_const_0xff)
 * Ghidra: undefined8 FUN_00407ed0(void) — returns constant 0xff.
 * Confidence: medium */
word_t sk_async_const_0xff(void)
{
    return 0xff;
}

/* FUN_00407ee8 @ 0x00407ee8  (est. sk_async_flag_bit_set)
 * Ghidra: undefined1 [16] FUN_00407ee8(void) — stores w19&1 into the byte at
 *   x21+0xb4, returns the pair (self[0x48], self[0x38]).
 * Confidence: medium */
void sk_async_flag_bit_set(word_t out[2])
{
    *(uint8_t *)(sk_reg_x21 + 0xb4) = (uint8_t)(sk_reg_w19 & 1);
    out[0] = *(word_t *)(sk_reg_x21 + 0x48);
    out[1] = *(word_t *)(sk_reg_x21 + 0x38);
}

/* FUN_00407f00 @ 0x00407f00  (est. sk_async_pair_get_38_48)
 * Ghidra: undefined1 [16] FUN_00407f00(void) — returns the pair
 *   (self[0x48], self[0x38]).
 * Confidence: medium */
void sk_async_pair_get_38_48(word_t out[2])
{
    out[0] = *(word_t *)(sk_reg_x21 + 0x48);
    out[1] = *(word_t *)(sk_reg_x21 + 0x38);
}

/* FUN_00407f18 @ 0x00407f18  (est. sk_async_witness_31) — empty thunk. */
void sk_async_witness_31(void) { return; }
/* FUN_00407f24 @ 0x00407f24  (est. sk_async_witness_32) — empty thunk. */
void sk_async_witness_32(void) { return; }
/* FUN_00407f30 @ 0x00407f30  (est. sk_async_witness_33) — empty thunk. */
void sk_async_witness_33(void) { return; }
/* FUN_00407f48 @ 0x00407f48  (est. sk_async_witness_34) — empty thunk. */
void sk_async_witness_34(void) { return; }
/* FUN_00407f54 @ 0x00407f54  (est. sk_async_witness_35) — empty thunk. */
void sk_async_witness_35(void) { return; }
/* FUN_00407f60 @ 0x00407f60  (est. sk_async_witness_36) — empty thunk. */
void sk_async_witness_36(void) { return; }

/* FUN_00407f6c @ 0x00407f6c  (est. sk_async_flag_set_idx)
 * Ghidra: void FUN_00407f6c(void) — sets the byte at *(x22+0x20)+
 *   (int)*(x22+0x178) to 1 (indexed flag set by self index).
 * Confidence: medium */
void sk_async_flag_set_idx(void)
{
    *(uint8_t *)(*(word_t *)(sk_reg_x22 + 0x20) +
                 (word_t)*(int32_t *)(sk_reg_x22 + 0x178)) = 1;
}

/* FUN_00407f84 @ 0x00407f84  (est. sk_async_witness_37) — empty thunk. */
void sk_async_witness_37(void) { return; }
/* FUN_00407f9c @ 0x00407f9c  (est. sk_async_witness_38) — empty thunk. */
void sk_async_witness_38(void) { return; }

/* FUN_00407fb4 @ 0x00407fb4  (est. sk_async_ctx_install_words)
 * Ghidra: void FUN_00407fb4(long param_1) — stores param_1 into self+0x10 and
 *   records (x20,x21,x19,x24,x23) into param_1+0x10..0x30 (Swift context
 *   multi-word install).
 * Confidence: medium */
void sk_async_ctx_install_words(word_t param_1)
{
    *(word_t *)(sk_reg_x22 + 0x10) = param_1;
    *(word_t *)(param_1 + 0x10) = sk_reg_x20;
    *(word_t *)(param_1 + 0x18) = sk_reg_x21;
    *(word_t *)(param_1 + 0x20) = sk_reg_x19;
    *(word_t *)(param_1 + 0x28) = sk_reg_x24;
    *(word_t *)(param_1 + 0x30) = sk_reg_x23;
}

/* FUN_00407fcc @ 0x00407fcc  (est. sk_async_witness_39) — empty thunk. */
void sk_async_witness_39(void) { return; }
/* FUN_00407fd8 @ 0x00407fd8  (est. sk_async_witness_3a) — empty thunk. */
void sk_async_witness_3a(void) { return; }

/* FUN_00407ff0 @ 0x00407ff0  (est. sk_async_ctx_store_words)
 * Ghidra: void FUN_00407ff0(void) — stores five stack words (0x28,0x30,0x38,
 *   0x40, byte 0x48) into the 4-word+byte buffer at x20.
 * Confidence: low */
void sk_async_ctx_store_words(void)
{
    word_t *dst = (word_t *)sk_reg_x20;
    dst[1] = sk_stack_word_30();
    dst[0] = sk_stack_word_28();
    dst[3] = sk_stack_word_40();
    dst[2] = sk_stack_word_38();
    *(uint8_t *)(dst + 4) = sk_stack_byte_48();
}

/* FUN_00408020 @ 0x00408020  (est. sk_async_witness_3b) — empty thunk. */
void sk_async_witness_3b(void) { return; }

/* FUN_00408038 @ 0x00408038  (est. sk_async_release_0x60)
 * Ghidra: void FUN_00408038(void) — releases the object at self[0x60] via
 *   sk_tb_async_release (FUN_0040bd24).
 * Confidence: medium */
void sk_async_release_0x60(void)
{
    sk_tb_async_release(*(word_t *)(sk_reg_x22 + 0x60));
}

/* FUN_00408044 @ 0x00408044  (est. sk_async_witness_3c) — empty thunk. */
void sk_async_witness_3c(void) { return; }
/* FUN_00408058 @ 0x00408058  (est. sk_async_witness_3d) — empty thunk. */
void sk_async_witness_3d(void) { return; }

/* FUN_0040806c @ 0x0040806c  (est. sk_async_release_0)
 * Ghidra: void FUN_0040806c(void) — async release with no argument
 *   (sk_tb_async_release(0)).
 * Confidence: medium */
void sk_async_release_0(void)
{
    sk_tb_async_release(0);
}

/* FUN_0040807c @ 0x0040807c  (est. sk_async_lock_acquire)
 * Ghidra: void FUN_0040807c(undefined8 param_1,undefined8 param_2,
 *   undefined8 param_3) — acquires a kernel lock via sk_lock_acquire
 *   (FUN_00377824) with tag 0xff and two table addresses.
 * Confidence: medium
 * Notes: Ghidra args &DAT_00614a5c, &DAT_00614a74. */
void sk_async_lock_acquire(word_t param_1, word_t param_2, word_t param_3)
{
    (void)param_1;
    sk_lock_acquire(0xff, param_2, param_3, 0, 0);
}

/* FUN_00408094 @ 0x00408094  (est. sk_async_job_alloc_box_1)
 * Ghidra: void FUN_00408094(void) — allocates an async job box of the size in
 *   DAT_005a0174 via sk_rt_0040bb18.
 * Confidence: medium */
void sk_async_job_alloc_box_1(void)
{
    sk_rt_0040bb18(DAT_005a0174);
}

/* FUN_004080a0 @ 0x004080a0  (est. sk_async_release_0x88)
 * Ghidra: void FUN_004080a0(void) — releases the object at self[0x88] via
 *   sk_tb_async_release.
 * Confidence: medium */
void sk_async_release_0x88(void)
{
    sk_tb_async_release(*(word_t *)(sk_reg_x22 + 0x88));
}

/* FUN_004080b0 @ 0x004080b0  (est. sk_async_scoped_enter)
 * Ghidra: void FUN_004080b0(void) — enters a Swift scoped accessor with
 *   sk_scoped_enter(&stack, 0) (FUN_001a84f4).
 * Confidence: medium */
void sk_async_scoped_enter(void)
{
    word_t scope = 0;
    sk_scoped_enter(&scope, 0);
}

/* FUN_004080bc @ 0x004080bc  (est. sk_async_witness_3e) — empty thunk. */
void sk_async_witness_3e(void) { return; }
/* FUN_004080cc @ 0x004080cc  (est. sk_async_witness_3f) — empty thunk. */
void sk_async_witness_3f(void) { return; }

/* FUN_004080e0 @ 0x004080e0  (est. sk_async_release_0xb0)
 * Ghidra: void FUN_004080e0(void) — releases the object at self[0xb0] via
 *   sk_tb_async_release.
 * Confidence: medium */
void sk_async_release_0xb0(void)
{
    sk_tb_async_release(*(word_t *)(sk_reg_x22 + 0xb0));
}

/* FUN_004080f8 @ 0x004080f8  (est. sk_async_lock_release)
 * Ghidra: void FUN_004080f8(long param_1) — releases a kernel lock via
 *   sk_lock_release(0x13f, *(param_1+0x10)) (FUN_00377dcc).
 * Confidence: medium */
void sk_async_lock_release(word_t param_1)
{
    sk_lock_release(0x13f, *(word_t *)(param_1 + 0x10));
}

/* FUN_00408108 @ 0x00408108  (est. sk_async_error_push)
 * Ghidra: void FUN_00408108(void) — pushes an async error token via
 *   sk_tb_error_push(0x29, 0xe100000000000000) (FUN_002acbb8).
 * Confidence: low */
void sk_async_error_push(void)
{
    sk_tb_error_push(0x29);
}

/* FUN_00408118 @ 0x00408118  (est. sk_async_rt_call_0)
 * Ghidra: void FUN_00408118(void) — calls sk_rt_0021867c(&stack0x18).
 * Confidence: low */
void sk_async_rt_call_0(void)
{
    word_t scope = 0;
    sk_rt_0021867c((word_t)&scope);
}

/* FUN_00408130 @ 0x00408130  (est. sk_async_ctx_install_5)
 * Ghidra: void FUN_00408130(undefined8 param_1,undefined8 param_2,long param_3)
 *   — installs a 5-word context: stores param_3 into self+0x20, x20 into
 *   self+0x28, param_1/param_2 into self+0x10/0x18, *(param_3+0x10) into
 *   self+0x30, then calls sk_obj_lock2(0) (FUN_00310d68).
 * Confidence: medium */
void sk_async_ctx_install_5(word_t param_1, word_t param_2, word_t param_3)
{
    *(word_t *)(sk_reg_x22 + 0x20) = param_3;
    *(word_t *)(sk_reg_x22 + 0x28) = sk_reg_x20;
    *(word_t *)(sk_reg_x22 + 0x10) = param_1;
    *(word_t *)(sk_reg_x22 + 0x18) = param_2;
    *(word_t *)(sk_reg_x22 + 0x30) = *(word_t *)(param_3 + 0x10);
    sk_obj_lock2(0);
}

/* FUN_00408148 @ 0x00408148  (est. sk_async_rt_call_1)
 * Ghidra: void FUN_00408148(void) — calls sk_rt_0021867c(&stack0x08).
 * Confidence: low */
void sk_async_rt_call_1(void)
{
    word_t scope = 0;
    sk_rt_0021867c((word_t)&scope);
}

/* FUN_00408160 @ 0x00408160  (est. sk_async_box_install_opt)
 * Ghidra: void FUN_00408160(long param_1) — installs a boxed optional value:
 *   copies two caller-frame words into param_1+0x10/0x18, stores x19 into
 *   param_1+0x38, then runs the Swift optional-COW helper sk_optional_cow
 *   on param_1+0x20 (FUN_00077024).
 * Confidence: medium */
void sk_async_box_install_opt(word_t param_1)
{
    *(word_t *)(param_1 + 0x18) = *(word_t *)(sk_reg_x29 - 200);
    *(word_t *)(param_1 + 0x10) = *(word_t *)(sk_reg_x29 - 0xd0);
    *(word_t *)(param_1 + 0x38) = sk_reg_x19;
    sk_optional_cow((unsigned long *)(param_1 + 0x20));
}

/* FUN_00408178 @ 0x00408178  (est. sk_async_witness_40) — empty thunk. */
void sk_async_witness_40(void) { return; }
/* FUN_00408190 @ 0x00408190  (est. sk_async_witness_41) — empty thunk. */
void sk_async_witness_41(void) { return; }

/* FUN_004081a8 @ 0x004081a8  (est. sk_async_job_alloc_box_2)
 * Ghidra: void FUN_004081a8(void) — allocates an async job box of the size in
 *   DAT_005a018c via sk_rt_0040bb18.
 * Confidence: medium */
void sk_async_job_alloc_box_2(void)
{
    sk_rt_0040bb18(DAT_005a018c);
}

/* FUN_004081b4 @ 0x004081b4  (est. sk_async_job_alloc_align_3)
 * Ghidra: void FUN_004081b4(long param_1) — allocates a 16-byte-aligned async
 *   job box of size param_1 via sk_rt_0040bb18.
 * Confidence: medium */
void sk_async_job_alloc_align_3(word_t size)
{
    sk_rt_0040bb18((size + 0xf) & ~0xfull);
}

/* FUN_004081c0 @ 0x004081c0  (est. sk_async_release_0x60_b)
 * Ghidra: void FUN_004081c0(void) — releases the object at self[0x60] via
 *   sk_tb_async_release (mirror of 0x407e3c region).
 * Confidence: medium */
void sk_async_release_0x60_b(void)
{
    sk_tb_async_release(*(word_t *)(sk_reg_x22 + 0x60));
}

/* Internal stack-word helpers referenced by sk_async_ctx_store_words (Ghidra
 * in_stack_00000028..48). */
static word_t sk_stack_word_28(void) { return 0; }
static word_t sk_stack_word_30(void) { return 0; }
static word_t sk_stack_word_38(void) { return 0; }
static word_t sk_stack_word_40(void) { return 0; }
static uint8_t sk_stack_byte_48(void) { return 0; }
