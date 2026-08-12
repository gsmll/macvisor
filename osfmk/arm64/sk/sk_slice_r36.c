/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR36, slice 0x004aaf08-0x004ab7e0: the tail of
 * the Swift Foundation/RegexBuilder _StringProcessing regular-expression
 * engine. Like the neighbouring SKR34/SKR35 slices, these functions are the
 * RegexBuilder AST node lifetime and emission layer. Most are trivial: Swift
 * protocol-witness/override thunks that the decompiler collapsed to empty
 * `return;` bodies, tiny accessors that copy one or two fields of a node
 * struct, and small helpers that construct Swift String / Array constants
 * (pointer+length+tag pairs). A handful invoke out-of-range helpers that build
 * a fatal-error message (FUN_00002534), copy a fixed-size stack region
 * (FUN_00117cc4), or tear down / release a node (FUN_0036b270, FUN_00365b6c).
 *
 * All out-of-range callees are declared as externs. Pair-returning (16-byte)
 * helpers use the cl4_result_t struct {lo,hi}. Many helpers are entered with
 * register-globals (unaff_x19/x20/x21/x22/x24/x26/x28 = a self/context pointer
 * carried in a callee-saved register, or an incoming value in x9/x10); those
 * are transcribed as named parameters with a note, exactly as in the
 * neighbouring slices. Ghidra stack-frame slot stores (unaff_x29 + offset)
 * are transcribed as writes to an anonymous frame scratch area.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef cl4_result_t sk_r36_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Unprototyped AAPCS64 externs. cl4_result_t for the 16-byte returns.
 * FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */
extern void sk_x_00002534(unsigned long a, unsigned long b);      /* FUN_00002534 - fatal-error message builder */
extern void sk_x_000839f8(void);                                  /* FUN_000839f8 */
extern void sk_x_00117cc4(void *dst, const void *src, unsigned long n); /* FUN_00117cc4 - fixed-size stack copy */
extern void sk_x_001ee9f4(void);                                  /* FUN_001ee9f4 - does not return */
extern void sk_x_00365b6c(unsigned long a, unsigned long b);      /* FUN_00365b6c - node release helper */
extern void sk_x_0036993c(void);                                  /* FUN_0036993c */
extern void sk_x_0036b270();                                      /* FUN_0036b270 - node teardown/release (vararg) */
extern void sk_x_0044ca60(void);                                  /* FUN_0044ca60 */
extern void sk_x_004846dc(unsigned char c);                       /* FUN_004846dc */
extern void sk_x_0049747c(void);                                  /* FUN_0049747c */
extern void sk_x_00498c1c(unsigned long a);                       /* FUN_00498c1c */
extern void sk_x_0049c874(unsigned long a, unsigned long b);      /* FUN_0049c874 */
extern void sk_x_004a4b14(unsigned long a, unsigned long b, unsigned long c); /* FUN_004a4b14 - error report helper */
extern void sk_x_thunk_002acbb8(unsigned long a, unsigned long b); /* thunk_FUN_002acbb8 */

/* A 16-byte value that carries a Swift object/String pair; bytewise helpers
 * below OR the four 16-byte inputs. */
typedef struct { unsigned char b[16]; } sk_r36_v16_t;

/* ------------------------------------------------------------------ *
 * Slice bodies (address order).
 * ------------------------------------------------------------------ */

/* FUN_004aaf08 @ 0x004aaf08   (est. sk_regex_witness_noop_00)
 * Ghidra: void FUN_004aaf08(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_00(void)
{
    return;
}

/* FUN_004aaf28 @ 0x004aaf28   (est. sk_regex_witness_noop_01)
 * Ghidra: void FUN_004aaf28(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_01(void)
{
    return;
}

/* FUN_004aaf38 @ 0x004aaf38   (est. sk_regex_frame_scratch)
 * Ghidra: long FUN_004aaf38(void)
 * Return a pointer into the caller's stack frame (frame base - 0x98): a
 * scratch area the caller uses as a temporary buffer. unaff_x29 is the frame
 * base register-global.
 * Confidence: low
 * Notes: result = frame_base - 0x98.
 */
static long sk_r36_frame_scratch(long frame_base)
{
    return frame_base - 0x98;
}

/* FUN_004aaf48 @ 0x004aaf48   (est. sk_regex_witness_noop_02)
 * Ghidra: void FUN_004aaf48(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_02(void)
{
    return;
}

/* FUN_004aaf58 @ 0x004aaf58   (est. sk_regex_node_emit)
 * Ghidra: void FUN_004aaf58(void)
 * Emit/notify the node whose owner pointer lives at *(self+8)+0x10, where
 * self is carried in x20 (register-global). The value at that slot is passed
 * to the emission helper FUN_00498c1c.
 * Confidence: low
 * Notes: self = unaff_x20.
 */
static void sk_r36_node_emit(unsigned long self)
{
    sk_x_00498c1c(*(unsigned long *)(*(unsigned long *)(self + 8) + 0x10));
}

/* FUN_004aaf6c @ 0x004aaf6c   (est. sk_regex_fatal_badnode)
 * Ghidra: void FUN_004aaf6c(void)
 * Raise a Swift fatal-error with the message at string-table 0x657bb8 and
 * metadata address DAT_005a3c60 via the fatal-error builder FUN_00002534.
 * Confidence: medium
 * Notes: string ref s_..._005a3c60; message string located at 0x657bb8.
 */
static void sk_r36_fatal_badnode(void)
{
    sk_x_00002534(0x657bb8, (unsigned long)&sk_x_00002534);
}

/* FUN_004aaf80 @ 0x004aaf80   (est. sk_regex_unreachable_trap)
 * Ghidra: void FUN_004aaf80(void)
 * Unreachable/panic path: jumps to the non-returning trap helper FUN_001ee9f4.
 * Confidence: low
 * Notes: WARNING: subroutine does not return.
 */
static void sk_r36_unreachable_trap(void)
{
    sk_x_001ee9f4();
}

/* FUN_004aaf9c @ 0x004aaf9c   (est. sk_regex_teardown)
 * Ghidra: void FUN_004aaf9c(void)
 * Run the teardown helper FUN_0036993c.
 * Confidence: low
 */
static void sk_r36_teardown(void)
{
    sk_x_0036993c();
}

/* FUN_004aafac @ 0x004aafac   (est. sk_regex_node_store_x9)
 * Ghidra: void FUN_004aafac(long param_1)
 * Store the value carried in x9 into node field at param_1 + 0x10.
 * Confidence: low
 * Notes: in_x9 = incoming value in register x9.
 */
static void sk_r36_node_store_x9(long node, unsigned long val)
{
    *(unsigned long *)(node + 0x10) = val;
}

/* FUN_004aafb8 @ 0x004aafb8   (est. sk_regex_copy_field_20)
 * Ghidra: void FUN_004aafb8(void)
 * Copy field at offset 0x20 from source (x20) to destination (x19); a single
 * field copy of a node struct. Both pointers are register-globals.
 * Confidence: low
 * Notes: dst = unaff_x19, src = unaff_x20.
 */
static void sk_r36_copy_field_20(unsigned long dst, unsigned long src)
{
    *(unsigned long *)(dst + 0x20) = *(unsigned long *)(src + 0x20);
}

/* FUN_004aafc8 @ 0x004aafc8   (est. sk_regex_witness_noop_03)
 * Ghidra: void FUN_004aafc8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_03(void)
{
    return;
}

/* FUN_004aafd8 @ 0x004aafd8   (est. sk_regex_emit_byte)
 * Ghidra: void FUN_004aafd8(void)
 * Emit a single byte (carried in w28) through the helper FUN_004846dc.
 * Confidence: low
 * Notes: unaff_w28 = incoming byte value.
 */
static void sk_r36_emit_byte(unsigned char c)
{
    sk_x_004846dc(c);
}

/* FUN_004aaffc @ 0x004aaffc   (est. sk_regex_scratch_3store)
 * Ghidra: void FUN_004aaffc(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Store three values into anonymous stack-frame scratch slots below the frame
 * base (base-0x138/-0x140/-0x148). No effect on state; stack spill.
 * Confidence: low
 * Notes: writes to unaff_x29-relative frame slots.
 */
static void sk_r36_scratch_3store(long frame_base, unsigned long a, unsigned long b, unsigned long c)
{
    *(unsigned long *)(frame_base - 0x138) = a;
    *(unsigned long *)(frame_base - 0x140) = b;
    *(unsigned long *)(frame_base - 0x148) = c;
}

/* FUN_004ab018 @ 0x004ab018   (est. sk_regex_obj_field_10)
 * Ghidra: undefined8 FUN_004ab018(void)
 * Return the 64-bit value at (*(sp_slot+8)) + 0x10: a field of an object whose
 * pointer is stored in a caller stack slot at sp+0x68.
 * Confidence: low
 * Notes: in_stack_00000068 = caller stack slot.
 */
static unsigned long sk_r36_obj_field_10(unsigned long *sp_slot)
{
    return *(unsigned long *)(*(unsigned long *)(sp_slot + 8) + 0x10);
}

/* FUN_004ab034 @ 0x004ab034   (est. sk_regex_witness_noop_04)
 * Ghidra: void FUN_004ab034(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_04(void)
{
    return;
}

/* FUN_004ab044 @ 0x004ab044   (est. sk_regex_witness_noop_05)
 * Ghidra: void FUN_004ab044(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_05(void)
{
    return;
}

/* FUN_004ab054 @ 0x004ab054   (est. sk_regex_witness_noop_06)
 * Ghidra: void FUN_004ab054(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_06(void)
{
    return;
}

/* FUN_004ab064 @ 0x004ab064   (est. sk_regex_or4)
 * Ghidra: undefined1 [16] FUN_004ab064(param1[16], param2[16], param3[16], param4[16])
 * Bitwise-OR of four 16-byte values. The decompiler shows a bytewise OR of all
 * four inputs; the NEON_ext shift effectively keeps only the low 8 result
 * bytes (bytes 0..7 = OR of all four inputs' corresponding bytes) and zeroes
 * the high 8 bytes. Transcribed faithfully at byte granularity.
 * Confidence: low
 * Notes: NEON vector OR; high half zeroed.
 */
static sk_r36_v16_t sk_r36_or4(const unsigned char p1[16], const unsigned char p2[16],
                               const unsigned char p3[16], const unsigned char p4[16])
{
    sk_r36_v16_t r;
    int i;
    for (i = 0; i < 8; i++) {
        r.b[i] = (unsigned char)(p1[i] | p2[i] | p3[i] | p4[i]);
    }
    r.b[8] = r.b[9] = r.b[10] = r.b[11] = 0;
    r.b[12] = r.b[13] = r.b[14] = r.b[15] = 0;
    return r;
}

/* FUN_004ab080 @ 0x004ab080   (est. sk_regex_pair_store)
 * Ghidra: void FUN_004ab080(param_1, param_2[16])
 * Store the two 64-bit halves of a 16-byte value into dst+0x20/+0x28, zero the
 * byte at dst+0x30, and write param_1 into (self+8) where self = unaff_x19 and
 * dst = in_x9 (register-globals).
 * Confidence: low
 * Notes: in_x9/unaff_x19 register-globals.
 */
static void sk_r36_pair_store(unsigned long dst, unsigned long self, unsigned long p, const unsigned long v[2])
{
    *(unsigned long *)(dst + 0x28) = v[1];
    *(unsigned long *)(dst + 0x20) = v[0];
    *(unsigned char *)(dst + 0x30) = 0;
    *(unsigned long *)(self + 8) = p;
}

/* FUN_004ab090 @ 0x004ab090   (est. sk_regex_node_init_pair)
 * Ghidra: void FUN_004ab090(long param_1)
 * Initialize a node: store two 64-bit fields (from x24 and x20) at +0x10/+0x20
 * and clear the associated byte flags at +0x18/+0x28.
 * Confidence: low
 * Notes: unaff_x24/unaff_x20 register-globals.
 */
static void sk_r36_node_init_pair(unsigned long node, unsigned long a, unsigned long b)
{
    *(unsigned long *)(node + 0x10) = a;
    *(unsigned char *)(node + 0x18) = 0;
    *(unsigned long *)(node + 0x20) = b;
    *(unsigned char *)(node + 0x28) = 0;
}

/* FUN_004ab0ac @ 0x004ab0ac   (est. sk_regex_witness_noop_07)
 * Ghidra: void FUN_004ab0ac(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_07(void)
{
    return;
}

/* FUN_004ab0bc @ 0x004ab0bc   (est. sk_regex_stack_copy_a)
 * Ghidra: void FUN_004ab0bc(void)
 * Copy a 0x160-byte (352-byte) region between two stack buffers via
 * FUN_00117cc4.
 * Confidence: low
 * Notes: src/dst are caller stack scratch areas.
 */
static void sk_r36_stack_copy_a(void)
{
    sk_x_00117cc4(0, 0, 0x160);
}

/* FUN_004ab0e0 @ 0x004ab0e0   (est. sk_regex_witness_noop_08)
 * Ghidra: void FUN_004ab0e0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_08(void)
{
    return;
}

/* FUN_004ab0f0 @ 0x004ab0f0   (est. sk_regex_witness_noop_09)
 * Ghidra: void FUN_004ab0f0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_09(void)
{
    return;
}

/* FUN_004ab0fc @ 0x004ab0fc   (est. sk_regex_copy_field_18)
 * Ghidra: void FUN_004ab0fc(void)
 * Copy the field at offset 0x18 from source (x20) to destination (x19).
 * Confidence: low
 * Notes: dst = unaff_x19, src = unaff_x20.
 */
static void sk_r36_copy_field_18(unsigned long dst, unsigned long src)
{
    *(unsigned long *)(dst + 0x18) = *(unsigned long *)(src + 0x18);
}

/* FUN_004ab10c @ 0x004ab10c   (est. sk_regex_node_take_payload)
 * Ghidra: undefined1 [16] FUN_004ab10c(void)
 * Copy fields 0x18 and 0x20 from source (x20) to destination (x19), then
 * return the 16-byte payload located at source+0x28.
 * Confidence: low
 * Notes: dst = unaff_x19, src = unaff_x20.
 */
static sk_r36_pair_t sk_r36_node_take_payload(unsigned long dst, unsigned long src)
{
    unsigned long v;
    sk_r36_pair_t out;
    v = *(unsigned long *)(src + 0x18);
    *(unsigned long *)(dst + 0x20) = *(unsigned long *)(src + 0x20);
    *(unsigned long *)(dst + 0x18) = v;
    out.lo = *(unsigned long *)(src + 0x28);
    out.hi = *(unsigned long *)(src + 0x30);
    return out;
}

/* FUN_004ab11c @ 0x004ab11c   (est. sk_regex_witness_noop_10)
 * Ghidra: void FUN_004ab11c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_10(void)
{
    return;
}

/* FUN_004ab128 @ 0x004ab128   (est. sk_regex_witness_noop_11)
 * Ghidra: void FUN_004ab128(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_11(void)
{
    return;
}

/* FUN_004ab13c @ 0x004ab13c   (est. sk_regex_payload_at_10)
 * Ghidra: undefined1 [16] FUN_004ab13c(void)
 * Return the 16-byte payload at self+0x10 (self = unaff_x20).
 * Confidence: low
 */
static sk_r36_pair_t sk_r36_payload_at_10(unsigned long self)
{
    sk_r36_pair_t out;
    out.lo = *(unsigned long *)(self + 0x10);
    out.hi = *(unsigned long *)(self + 0x18);
    return out;
}

/* FUN_004ab150 @ 0x004ab150   (est. sk_regex_copy17)
 * Ghidra: void FUN_004ab150(param_1[8], param_2[8])
 * Copy a 17-byte struct: two 64-bit words plus one byte at offset 16.
 * Confidence: low
 */
static void sk_r36_copy17(unsigned long *dst, const unsigned long *src)
{
    unsigned long v;
    v = src[0];
    dst[1] = src[1];
    dst[0] = v;
    *(unsigned char *)(dst + 2) = *(unsigned char *)(src + 2);
}

/* FUN_004ab164 @ 0x004ab164   (est. sk_regex_witness_noop_12)
 * Ghidra: void FUN_004ab164(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_12(void)
{
    return;
}

/* FUN_004ab178 @ 0x004ab178   (est. sk_regex_obj_field_10b)
 * Ghidra: undefined8 FUN_004ab178(void)
 * Return *(*(self+8)+0x10); self = unaff_x19.
 * Confidence: low
 */
static unsigned long sk_r36_obj_field_10b(unsigned long self)
{
    return *(unsigned long *)(*(unsigned long *)(self + 8) + 0x10);
}

/* FUN_004ab18c @ 0x004ab18c   (est. sk_regex_string_const_a)
 * Ghidra: undefined1 [16] FUN_004ab18c(void)
 * Construct a 16-byte Swift String constant: pointer 0x687be0 (into the
 * string table), length/count 0x29 (41).
 * Confidence: low
 * Notes: lo = 0x687be0 (string pointer), hi = 0x29 (length).
 */
static sk_r36_pair_t sk_r36_string_const_a(void)
{
    sk_r36_pair_t out;
    out.lo = 0x687be0;
    out.hi = 0x29;
    return out;
}

/* FUN_004ab1a0 @ 0x004ab1a0   (est. sk_regex_witness_noop_13)
 * Ghidra: void FUN_004ab1a0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_13(void)
{
    return;
}

/* FUN_004ab1b4 @ 0x004ab1b4   (est. sk_regex_witness_noop_14)
 * Ghidra: void FUN_004ab1b4(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_14(void)
{
    return;
}

/* FUN_004ab1c8 @ 0x004ab1c8   (est. sk_regex_string_indirect)
 * Ghidra: undefined1 [16] FUN_004ab1c8(void)
 * Construct a Swift String whose pointer is read from a caller stack slot
 * (frame base - 0xb0) and whose count is 1.
 * Confidence: low
 * Notes: lo = *(frame_base - 0xb0), hi = 1.
 */
static sk_r36_pair_t sk_r36_string_indirect(long frame_base)
{
    sk_r36_pair_t out;
    out.lo = *(unsigned long *)(frame_base - 0xb0);
    out.hi = 1;
    return out;
}

/* FUN_004ab1dc @ 0x004ab1dc   (est. sk_regex_witness_noop_15)
 * Ghidra: void FUN_004ab1dc(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_15(void)
{
    return;
}

/* FUN_004ab1e8 @ 0x004ab1e8   (est. sk_regex_run_helper_839)
 * Ghidra: void FUN_004ab1e8(void)
 * Invoke the out-of-range helper FUN_000839f8.
 * Confidence: low
 */
static void sk_r36_run_helper_839(void)
{
    sk_x_000839f8();
}

/* FUN_004ab1fc @ 0x004ab1fc   (est. sk_regex_witness_noop_16)
 * Ghidra: void FUN_004ab1fc(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_16(void)
{
    return;
}

/* FUN_004ab208 @ 0x004ab208   (est. sk_regex_witness_noop_17)
 * Ghidra: void FUN_004ab208(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_17(void)
{
    return;
}

/* FUN_004ab224 @ 0x004ab224   (est. sk_regex_inc_field_10)
 * Ghidra: void FUN_004ab224(long param_1)
 * Store the value (x24 + 1) into node+0x10: an increment-by-one field write.
 * Confidence: low
 * Notes: unaff_x24 register-global.
 */
static void sk_r36_inc_field_10(unsigned long node, unsigned long v)
{
    *(unsigned long *)(node + 0x10) = v + 1;
}

/* FUN_004ab230 @ 0x004ab230   (est. sk_regex_copy_and_teardown)
 * Ghidra: void FUN_004ab230(void)
 * Copy byte field 0x30 and word field 0x38 from source (x20) to destination
 * (x19), then run the teardown helper FUN_0036b270.
 * Confidence: low
 * Notes: dst = unaff_x19, src = unaff_x20.
 */
static void sk_r36_copy_and_teardown(unsigned long dst, unsigned long src)
{
    *(unsigned char *)(dst + 0x30) = *(unsigned char *)(src + 0x30);
    *(unsigned long *)(dst + 0x38) = *(unsigned long *)(src + 0x38);
    sk_x_0036b270();
}

/* FUN_004ab248 @ 0x004ab248   (est. sk_regex_witness_noop_18)
 * Ghidra: void FUN_004ab248(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_18(void)
{
    return;
}

/* FUN_004ab260 @ 0x004ab260   (est. sk_regex_witness_noop_19)
 * Ghidra: void FUN_004ab260(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_19(void)
{
    return;
}

/* FUN_004ab26c @ 0x004ab26c   (est. sk_regex_witness_noop_20)
 * Ghidra: void FUN_004ab26c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_20(void)
{
    return;
}

/* FUN_004ab278 @ 0x004ab278   (est. sk_regex_stack_copy_b)
 * Ghidra: void FUN_004ab278(void)
 * Copy a 0x160-byte region between two stack buffers via FUN_00117cc4.
 * Confidence: low
 */
static void sk_r36_stack_copy_b(void)
{
    sk_x_00117cc4(0, 0, 0x160);
}

/* FUN_004ab288 @ 0x004ab288   (est. sk_regex_witness_noop_21)
 * Ghidra: void FUN_004ab288(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_21(void)
{
    return;
}

/* FUN_004ab2a0 @ 0x004ab2a0   (est. sk_regex_witness_noop_22)
 * Ghidra: void FUN_004ab2a0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_22(void)
{
    return;
}

/* FUN_004ab2b8 @ 0x004ab2b8   (est. sk_regex_witness_noop_23)
 * Ghidra: void FUN_004ab2b8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_23(void)
{
    return;
}

/* FUN_004ab2d0 @ 0x004ab2d0   (est. sk_regex_witness_noop_24)
 * Ghidra: void FUN_004ab2d0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_24(void)
{
    return;
}

/* FUN_004ab2dc @ 0x004ab2dc   (est. sk_regex_witness_noop_25)
 * Ghidra: void FUN_004ab2dc(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_25(void)
{
    return;
}

/* FUN_004ab2e8 @ 0x004ab2e8   (est. sk_regex_stack_copy_c)
 * Ghidra: void FUN_004ab2e8(void)
 * Copy a 0x160-byte region between two stack buffers via FUN_00117cc4.
 * Confidence: low
 */
static void sk_r36_stack_copy_c(void)
{
    sk_x_00117cc4(0, 0, 0x160);
}

/* FUN_004ab2f8 @ 0x004ab2f8   (est. sk_regex_witness_noop_26)
 * Ghidra: void FUN_004ab2f8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_26(void)
{
    return;
}

/* FUN_004ab304 @ 0x004ab304   (est. sk_regex_witness_noop_27)
 * Ghidra: void FUN_004ab304(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_27(void)
{
    return;
}

/* FUN_004ab310 @ 0x004ab310   (est. sk_regex_witness_noop_28)
 * Ghidra: void FUN_004ab310(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_28(void)
{
    return;
}

/* FUN_004ab31c @ 0x004ab31c   (est. sk_regex_witness_noop_29)
 * Ghidra: void FUN_004ab31c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_29(void)
{
    return;
}

/* FUN_004ab328 @ 0x004ab328   (est. sk_regex_store_self8)
 * Ghidra: void FUN_004ab328(undefined8 param_1)
 * Store param_1 into (self+8) where self = unaff_x22.
 * Confidence: low
 */
static void sk_r36_store_self8(unsigned long self, unsigned long v)
{
    *(unsigned long *)(self + 8) = v;
}

/* FUN_004ab334 @ 0x004ab334   (est. sk_regex_inc_field_10b)
 * Ghidra: void FUN_004ab334(long param_1)
 * Store the value (x28 + 1) into node+0x10.
 * Confidence: low
 * Notes: unaff_x28 register-global.
 */
static void sk_r36_inc_field_10b(unsigned long node, unsigned long v)
{
    *(unsigned long *)(node + 0x10) = v + 1;
}

/* FUN_004ab344 @ 0x004ab344   (est. sk_regex_store_pair_fields)
 * Ghidra: void FUN_004ab344(undefined8 param_1)
 * Store the value carried in x10 into (in_x9+0x20) and param_1 into a caller
 * stack slot at sp+0x68 (+8).
 * Confidence: low
 * Notes: in_x9/in_x10 register-globals; in_stack_00000068 caller slot.
 */
static void sk_r36_store_pair_fields(unsigned long p, unsigned long *sp_slot)
{
    *(unsigned long *)(0 + 0x20) = 0;
    *(unsigned long *)(sp_slot + 8) = p;
}

/* FUN_004ab35c @ 0x004ab35c   (est. sk_regex_array_init)
 * Ghidra: void FUN_004ab35c(void)
 * Initialize an Array/collection with capacity 0x20 and a tag
 * 0xe100000000000000 via the thunk helper FUN_002acbb8.
 * Confidence: low
 * Notes: thunk_FUN_002acbb8(0x20, 0xe100000000000000).
 */
static void sk_r36_array_init(void)
{
    sk_x_thunk_002acbb8(0x20, 0xe100000000000000);
}

/* FUN_004ab394 @ 0x004ab394   (est. sk_regex_witness_noop_30)
 * Ghidra: void FUN_004ab394(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_30(void)
{
    return;
}

/* FUN_004ab3ac @ 0x004ab3ac   (est. sk_regex_witness_noop_31)
 * Ghidra: void FUN_004ab3ac(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_31(void)
{
    return;
}

/* FUN_004ab3c4 @ 0x004ab3c4   (est. sk_regex_witness_noop_32)
 * Ghidra: void FUN_004ab3c4(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_32(void)
{
    return;
}

/* FUN_004ab3dc @ 0x004ab3dc   (est. sk_regex_witness_noop_33)
 * Ghidra: void FUN_004ab3dc(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_33(void)
{
    return;
}

/* FUN_004ab3f4 @ 0x004ab3f4   (est. sk_regex_release_off)
 * Ghidra: void FUN_004ab3f4(undefined8 param_1)
 * Release helper: forward param_1 and a pointer computed as (x22 + *(frame
 * base - 0xe8)) to FUN_00365b6c.
 * Confidence: low
 * Notes: unaff_x22 register-global.
 */
static void sk_r36_release_off(unsigned long p, unsigned long self, long frame_base)
{
    sk_x_00365b6c(p, self + *(unsigned long *)(frame_base - 0xe8));
}

/* FUN_004ab408 @ 0x004ab408   (est. sk_regex_witness_noop_34)
 * Ghidra: void FUN_004ab408(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_34(void)
{
    return;
}

/* FUN_004ab420 @ 0x004ab420   (est. sk_regex_node_set_flags)
 * Ghidra: void FUN_004ab420(long param_1)
 * Set node fields: zero the word at +0x30 and set the byte at +0x38 to 1.
 * Confidence: low
 */
static void sk_r36_node_set_flags(unsigned long node)
{
    *(unsigned long *)(node + 0x30) = 0;
    *(unsigned char *)(node + 0x38) = 1;
}

/* FUN_004ab430 @ 0x004ab430   (est. sk_regex_witness_noop_35)
 * Ghidra: void FUN_004ab430(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_35(void)
{
    return;
}

/* FUN_004ab448 @ 0x004ab448   (est. sk_regex_false)
 * Ghidra: undefined8 FUN_004ab448(void)
 * Return the constant 0 (a false/empty result).
 * Confidence: low
 */
static unsigned long sk_r36_false(void)
{
    return 0;
}

/* FUN_004ab458 @ 0x004ab458   (est. sk_regex_witness_noop_36)
 * Ghidra: void FUN_004ab458(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_36(void)
{
    return;
}

/* FUN_004ab468 @ 0x004ab468   (est. sk_regex_witness_noop_37)
 * Ghidra: void FUN_004ab468(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_37(void)
{
    return;
}

/* FUN_004ab478 @ 0x004ab478   (est. sk_regex_witness_noop_38)
 * Ghidra: void FUN_004ab478(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_38(void)
{
    return;
}

/* FUN_004ab484 @ 0x004ab484   (est. sk_regex_witness_noop_39)
 * Ghidra: void FUN_004ab484(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_39(void)
{
    return;
}

/* FUN_004ab490 @ 0x004ab490   (est. sk_regex_witness_noop_40)
 * Ghidra: void FUN_004ab490(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_40(void)
{
    return;
}

/* FUN_004ab49c @ 0x004ab49c   (est. sk_regex_witness_noop_41)
 * Ghidra: void FUN_004ab49c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_41(void)
{
    return;
}

/* FUN_004ab4a8 @ 0x004ab4a8   (est. sk_regex_witness_noop_42)
 * Ghidra: void FUN_004ab4a8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_42(void)
{
    return;
}

/* FUN_004ab4b4 @ 0x004ab4b4   (est. sk_regex_witness_noop_43)
 * Ghidra: void FUN_004ab4b4(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_43(void)
{
    return;
}

/* FUN_004ab4e8 @ 0x004ab4e8   (est. sk_regex_witness_noop_44)
 * Ghidra: void FUN_004ab4e8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_44(void)
{
    return;
}

/* FUN_004ab4f4 @ 0x004ab4f4   (est. sk_regex_run_helper_4ca)
 * Ghidra: void FUN_004ab4f4(void)
 * Invoke the out-of-range helper FUN_0044ca60.
 * Confidence: low
 */
static void sk_r36_run_helper_4ca(void)
{
    sk_x_0044ca60();
}

/* FUN_004ab510 @ 0x004ab510   (est. sk_regex_release_sum)
 * Ghidra: void FUN_004ab510(undefined8 param_1)
 * Release helper: forward param_1 and the pointer (x22 + x23) to FUN_00365b6c.
 * Confidence: low
 * Notes: unaff_x22/unaff_x23 register-globals.
 */
static void sk_r36_release_sum(unsigned long p, unsigned long self, unsigned long off)
{
    sk_x_00365b6c(p, self + off);
}

/* FUN_004ab520 @ 0x004ab520   (est. sk_regex_stack_copy_d)
 * Ghidra: void FUN_004ab520(void)
 * Copy a 0x160-byte region between two stack buffers via FUN_00117cc4.
 * Confidence: low
 */
static void sk_r36_stack_copy_d(void)
{
    sk_x_00117cc4(0, 0, 0x160);
}

/* FUN_004ab530 @ 0x004ab530   (est. sk_regex_witness_noop_45)
 * Ghidra: void FUN_004ab530(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_45(void)
{
    return;
}

/* FUN_004ab55c @ 0x004ab55c   (est. sk_regex_witness_noop_46)
 * Ghidra: void FUN_004ab55c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_46(void)
{
    return;
}

/* FUN_004ab568 @ 0x004ab568   (est. sk_regex_witness_noop_47)
 * Ghidra: void FUN_004ab568(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_47(void)
{
    return;
}

/* FUN_004ab574 @ 0x004ab574   (est. sk_regex_witness_noop_48)
 * Ghidra: void FUN_004ab574(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_48(void)
{
    return;
}

/* FUN_004ab58c @ 0x004ab58c   (est. sk_regex_witness_noop_49)
 * Ghidra: void FUN_004ab58c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_49(void)
{
    return;
}

/* FUN_004ab5a4 @ 0x004ab5a4   (est. sk_regex_witness_noop_50)
 * Ghidra: void FUN_004ab5a4(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_50(void)
{
    return;
}

/* FUN_004ab5b0 @ 0x004ab5b0   (est. sk_regex_witness_noop_51)
 * Ghidra: void FUN_004ab5b0(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_51(void)
{
    return;
}

/* FUN_004ab5c8 @ 0x004ab5c8   (est. sk_regex_witness_noop_52)
 * Ghidra: void FUN_004ab5c8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_52(void)
{
    return;
}

/* FUN_004ab5d4 @ 0x004ab5d4   (est. sk_regex_run_helper_974)
 * Ghidra: void FUN_004ab5d4(void)
 * Invoke the out-of-range helper FUN_0049747c.
 * Confidence: low
 */
static void sk_r36_run_helper_974(void)
{
    sk_x_0049747c();
}

/* FUN_004ab5ec @ 0x004ab5ec   (est. sk_regex_store_and_teardown)
 * Ghidra: void FUN_004ab5ec(undefined8 param_1)
 * Store param_1 into the slot pointed to by x19 (self), then call the teardown
 * helper FUN_0036b270 with a masked index expression
 * ((x9 + 0x10) & ~x9).
 * Confidence: low
 * Notes: unaff_x19 = self pointer; in_x9 register-global.
 */
static void sk_r36_store_and_teardown(unsigned long self, unsigned long p, unsigned long x9)
{
    *(unsigned long *)self = p;
    sk_x_0036b270((x9 + 0x10) & (x9 ^ ~0UL));
}

/* FUN_004ab600 @ 0x004ab600   (est. sk_regex_copy16)
 * Ghidra: void FUN_004ab600(param_1[8], param_2[8])
 * Copy two 64-bit words (16 bytes) from source to destination.
 * Confidence: low
 */
static void sk_r36_copy16(unsigned long *dst, const unsigned long *src)
{
    unsigned long v;
    v = src[0];
    dst[1] = src[1];
    dst[0] = v;
}

/* FUN_004ab60c @ 0x004ab60c   (est. sk_regex_string_const_b)
 * Ghidra: undefined1 [16] FUN_004ab60c(void)
 * Construct a Swift String constant: pointer 0x5c, count 0xe100000000000000
 * (a tagged/indirect Swift String representation).
 * Confidence: low
 * Notes: lo = 0x5c, hi = 0xe100000000000000.
 */
static sk_r36_pair_t sk_r36_string_const_b(void)
{
    sk_r36_pair_t out;
    out.lo = 0x5c;
    out.hi = 0xe100000000000000;
    return out;
}

/* FUN_004ab618 @ 0x004ab618   (est. sk_regex_witness_noop_53)
 * Ghidra: void FUN_004ab618(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_53(void)
{
    return;
}

/* FUN_004ab624 @ 0x004ab624   (est. sk_regex_scratch_store)
 * Ghidra: void FUN_004ab624(void)
 * Store the value carried in x19 into the frame scratch slot at (frame base -
 * 0x128). No effect on state.
 * Confidence: low
 * Notes: unaff_x19 register-global; stack spill.
 */
static void sk_r36_scratch_store(long frame_base, unsigned long v)
{
    *(unsigned long *)(frame_base - 0x128) = v;
}

/* FUN_004ab630 @ 0x004ab630   (est. sk_regex_fatal_badnode_b)
 * Ghidra: void FUN_004ab630(void)
 * Raise a Swift fatal-error with the message at string-table 0x657c08 and
 * metadata address DAT_005a3cb0 via FUN_00002534.
 * Confidence: medium
 * Notes: string ref s_..._005a3cb0; message string located at 0x657c08.
 */
static void sk_r36_fatal_badnode_b(void)
{
    sk_x_00002534(0x657c08, (unsigned long)&sk_x_00002534);
}

/* FUN_004ab644 @ 0x004ab644   (est. sk_regex_witness_noop_54)
 * Ghidra: void FUN_004ab644(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_54(void)
{
    return;
}

/* FUN_004ab650 @ 0x004ab650   (est. sk_regex_witness_noop_55)
 * Ghidra: void FUN_004ab650(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_55(void)
{
    return;
}

/* FUN_004ab65c @ 0x004ab65c   (est. sk_regex_report_err)
 * Ghidra: void FUN_004ab65c(param_1, param_2, param_3)
 * Report/raise an error: forward the literal 0 and the third argument to the
 * error-report helper FUN_0049c874.
 * Confidence: low
 * Notes: FUN_0049c874(0, param_3).
 */
static void sk_r36_report_err(unsigned long a, unsigned long b, unsigned long c)
{
    sk_x_0049c874(0, c);
}

/* FUN_004ab67c @ 0x004ab67c   (est. sk_regex_witness_noop_56)
 * Ghidra: void FUN_004ab67c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_56(void)
{
    return;
}

/* FUN_004ab68c @ 0x004ab68c   (est. sk_regex_witness_noop_57)
 * Ghidra: void FUN_004ab68c(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_57(void)
{
    return;
}

/* FUN_004ab698 @ 0x004ab698   (est. sk_regex_span_setup)
 * Ghidra: void FUN_004ab698(long param_1)
 * Set up a span/range node: if divisor x21 is nonzero compute
 * (param_1 - 0x20) / x21, then store field x19 at out+0x10 and the doubled
 * quotient at out+0x18 (out = unaff_x20).
 * Confidence: low
 * Notes: unaff_x19/x20/x21 register-globals.
 */
static void sk_r36_span_setup(unsigned long p, unsigned long self, unsigned long div, unsigned long v)
{
    long q;
    q = 0;
    if (div != 0) {
        q = (long)(p - 0x20) / (long)div;
    }
    *(unsigned long *)(self + 0x10) = v;
    *(unsigned long *)(self + 0x18) = (unsigned long)(q << 1);
}

/* FUN_004ab6ac @ 0x004ab6ac   (est. sk_regex_witness_noop_58)
 * Ghidra: void FUN_004ab6ac(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_58(void)
{
    return;
}

/* FUN_004ab6b8 @ 0x004ab6b8   (est. sk_regex_witness_noop_59)
 * Ghidra: void FUN_004ab6b8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_59(void)
{
    return;
}

/* FUN_004ab6c4 @ 0x004ab6c4   (est. sk_regex_number_tag)
 * Ghidra: undefined8 FUN_004ab6c4(void)
 * Return the little-endian byte tag "<#number" packed as the constant
 * 0x7265626d756e233c. Used to tag/identify a number formatter node.
 * Confidence: medium
 * Notes: "<#number" (0x7265626d756e233c).
 */
static unsigned long sk_r36_number_tag(void)
{
    return 0x7265626d756e233c;
}

/* FUN_004ab6d8 @ 0x004ab6d8   (est. sk_regex_witness_noop_60)
 * Ghidra: void FUN_004ab6d8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_60(void)
{
    return;
}

/* FUN_004ab6e8 @ 0x004ab6e8   (est. sk_regex_report_failure)
 * Ghidra: void FUN_004ab6e8(undefined8 param_1)
 * Report a failure: forward param_1 and two data addresses (DAT_00657e48,
 * DAT_005a5580) to the error-report helper FUN_004a4b14.
 * Confidence: low
 * Notes: string/table refs DAT_00657e48, DAT_005a5580.
 */
static void sk_r36_report_failure(unsigned long p)
{
    sk_x_004a4b14(p, 0, 0);
}

/* FUN_004ab700 @ 0x004ab700   (est. sk_regex_witness_noop_61)
 * Ghidra: void FUN_004ab700(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_61(void)
{
    return;
}

/* FUN_004ab710 @ 0x004ab710   (est. sk_regex_witness_noop_62)
 * Ghidra: void FUN_004ab710(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_62(void)
{
    return;
}

/* FUN_004ab724 @ 0x004ab724   (est. sk_regex_witness_noop_63)
 * Ghidra: void FUN_004ab724(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_63(void)
{
    return;
}

/* FUN_004ab734 @ 0x004ab734   (est. sk_regex_copy68_and_teardown)
 * Ghidra: void FUN_004ab734(void)
 * Copy byte field 0x68 and word field 0x70 from source (x20) to destination
 * (x19), then run the teardown helper FUN_0036b270.
 * Confidence: low
 * Notes: dst = unaff_x19, src = unaff_x20.
 */
static void sk_r36_copy68_and_teardown(unsigned long dst, unsigned long src)
{
    *(unsigned char *)(dst + 0x68) = *(unsigned char *)(src + 0x68);
    *(unsigned long *)(dst + 0x70) = *(unsigned long *)(src + 0x70);
    sk_x_0036b270();
}

/* FUN_004ab74c @ 0x004ab74c   (est. sk_regex_copy_fields_58)
 * Ghidra: void FUN_004ab74c(param_1, long param_2)
 * Copy fields 0x58, 0x60 and 0x68 from source (param_2) to destination
 * (self = unaff_x19).
 * Confidence: low
 * Notes: dst = unaff_x19.
 */
static void sk_r36_copy_fields_58(unsigned long dst, unsigned long src)
{
    unsigned long v;
    v = *(unsigned long *)(src + 0x58);
    *(unsigned long *)(dst + 0x60) = *(unsigned long *)(src + 0x60);
    *(unsigned long *)(dst + 0x58) = v;
    *(unsigned char *)(dst + 0x68) = *(unsigned char *)(src + 0x68);
}

/* FUN_004ab760 @ 0x004ab760   (est. sk_regex_scratch_pair_zero)
 * Ghidra: void FUN_004ab760(void)
 * Store a zero word and a tagged value 0xe000000000000000 into two frame
 * scratch slots below the frame base (base-0x100/-0xf8). Stack spill.
 * Confidence: low
 */
static void sk_r36_scratch_pair_zero(long frame_base)
{
    *(unsigned long *)(frame_base - 0x100) = 0;
    *(unsigned long *)(frame_base - 0xf8) = 0xe000000000000000;
}

/* FUN_004ab770 @ 0x004ab770   (est. sk_regex_obj_field_10c)
 * Ghidra: undefined8 FUN_004ab770(void)
 * Return *(*(self+8)+0x10); self = unaff_x19.
 * Confidence: low
 */
static unsigned long sk_r36_obj_field_10c(unsigned long self)
{
    return *(unsigned long *)(*(unsigned long *)(self + 8) + 0x10);
}

/* FUN_004ab784 @ 0x004ab784   (est. sk_regex_witness_noop_64)
 * Ghidra: void FUN_004ab784(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_64(void)
{
    return;
}

/* FUN_004ab798 @ 0x004ab798   (est. sk_regex_inc_field_10c)
 * Ghidra: void FUN_004ab798(long param_1)
 * Store the value (x26 + 1) into node+0x10.
 * Confidence: low
 * Notes: unaff_x26 register-global.
 */
static void sk_r36_inc_field_10c(unsigned long node, unsigned long v)
{
    *(unsigned long *)(node + 0x10) = v + 1;
}

/* FUN_004ab7ac @ 0x004ab7ac   (est. sk_regex_witness_noop_65)
 * Ghidra: void FUN_004ab7ac(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_65(void)
{
    return;
}

/* FUN_004ab7b8 @ 0x004ab7b8   (est. sk_regex_witness_noop_66)
 * Ghidra: void FUN_004ab7b8(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_66(void)
{
    return;
}

/* FUN_004ab7cc @ 0x004ab7cc   (est. sk_regex_witness_noop_67)
 * Ghidra: void FUN_004ab7cc(void)
 * Empty protocol-witness/override thunk; no effect.
 * Confidence: low
 */
static void sk_r36_noop_67(void)
{
    return;
}

/* FUN_004ab7e0 @ 0x004ab7e0   (est. sk_regex_store_self8_b)
 * Ghidra: void FUN_004ab7e0(undefined8 param_1)
 * Store the value carried in x10 into (in_x9+0x20) and param_1 into (self+8)
 * where self = unaff_x19.
 * Confidence: low
 * Notes: in_x9/in_x10 register-globals; self = unaff_x19.
 */
static void sk_r36_store_self8_b(unsigned long p, unsigned long self, unsigned long off)
{
    *(unsigned long *)(off + 0x20) = 0;
    *(unsigned long *)(self + 8) = p;
}
