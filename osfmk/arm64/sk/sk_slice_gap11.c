/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in the
 * cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all are estimates unless
 * string/header matched. This slice (SKGAP11, 0x00351d24-0x00353118) is a dense
 * run of small leaf/thunk/helper functions — the bulk are empty no-op stubs. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef void (*code_t)(void);

/* 16-byte value (a 128-bit register / pair of words). lo = low 64 bits,
 * hi = high 64 bits. */
typedef struct { word_t lo, hi; } sk16_t;

/* Called helpers (ground-truth FUN_ addresses). Named from manifest/callee
 * notes: 00310a74 = swift_type_metadata_field_30, 00310b08 =
 * swift_type_metadata_field_14, 0001df60 / 00027754 = boot-region helpers.
 * 00310a74 takes a single word (0 passed where the decompile shows no arg). */
extern word_t sk_h_00310a74(word_t);
extern void sk_h_0001df60(void);
extern void sk_h_00027754(void);
extern void sk_h_00310b08(void);

/* Opaque data symbol referenced by FUN_003521a4 (DAT_00657778). */
extern byte sk_d_00657778;

/* 64-bit rotate-left / rotate-right helpers (used by the hash round 00351d4c). */
static inline word_t rol(word_t v, unsigned n){ return (v << n) | (v >> (64 - n)); }
static inline word_t ror(word_t v, unsigned n){ return (v >> n) | (v << (64 - n)); }


/* FUN_00351d24 @ 0x00351d24   (est. sk_f_00351d24)
 * Ghidra: void FUN_00351d24(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351d24(void){ return; }
/* FUN_00351d30 @ 0x00351d30   (est. sk_f_00351d30)
 * Ghidra: void FUN_00351d30(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351d30(void){ return; }
/* FUN_00351d4c @ 0x00351d4c   (est. sk_hash_round_00351d4c)
 * Ghidra: ulong FUN_00351d4c(ulong param_1)  [reads in_x10, in_x11, in_x12]
 * A 64-bit mixing/round function (ChaCha-style quarter-round with byte-swap
 * halving and ROL 13/16/17/21). Takes one explicit input word plus three
 * compiler-carried register inputs (in_x10/x11/x12, not real parameters) and
 * returns a mixed word. Called from FUN_001a842c and FUN_00229ebc. Identity is
 * an estimate; the structure is a hash/PRF round.
 * Confidence: medium
 * Notes: the (x >> 32 | x << 32) terms are the 64<->32-byte-swap Ghidra renders
 *   for the seL4/ChaCha mixing; the register inputs in_x10/x11/x12 are modeled
 *   as extra parameters. No string refs. */
word_t sk_f_00351d4c(word_t input, word_t r10, word_t r11, word_t r12){
  word_t t  = r11 ^ rol(r10, 13);
  word_t u  = ror(r12, 32) + input;
  word_t v  = t + u;
  u        ^= rol(input, 16);
  word_t w  = v ^ rol(t, 17);
  t         = ror(r11, 32) + u;
  word_t x  = t ^ rol(u, 21);
  t         = (w + t) ^ rol(w, 13);
  u         = ror(v, 32) + x;
  v         = t + u;
  u        ^= rol(x, 16);
  return rol(u, 21) ^ rol(t, 17) ^ ror(v, 32) ^ v;
}
/* FUN_00351d9c @ 0x00351d9c   (est. sk_f_00351d9c)
 * Ghidra: void FUN_00351d9c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351d9c(void){ return; }
/* FUN_00351da8 @ 0x00351da8   (est. sk_f_00351da8)
 * Ghidra: void FUN_00351da8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351da8(void){ return; }
/* FUN_00351db4 @ 0x00351db4   (est. sk_f_00351db4)
 * Ghidra: void FUN_00351db4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351db4(void){ return; }
/* FUN_00351dc0 @ 0x00351dc0   (est. sk_f_00351dc0)
 * Ghidra: void FUN_00351dc0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351dc0(void){ return; }
/* FUN_00351dcc @ 0x00351dcc   (est. sk_f_00351dcc)
 * Ghidra: void FUN_00351dcc(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351dcc(void){ return; }
/* FUN_00351dd8 @ 0x00351dd8   (est. sk_f_00351dd8)
 * Ghidra: void FUN_00351dd8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351dd8(void){ return; }
/* FUN_00351de4 @ 0x00351de4   (est. sk_f_00351de4)
 * Ghidra: void FUN_00351de4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351de4(void){ return; }
/* FUN_00351df0 @ 0x00351df0   (est. sk_f_00351df0)
 * Ghidra: void FUN_00351df0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351df0(void){ return; }
/* FUN_00351dfc @ 0x00351dfc   (est. sk_f_00351dfc)
 * Ghidra: void FUN_00351dfc(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351dfc(void){ return; }
/* FUN_00351e08 @ 0x00351e08   (est. sk_f_00351e08)
 * Ghidra: void FUN_00351e08(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e08(void){ return; }
/* FUN_00351e14 @ 0x00351e14   (est. sk_f_00351e14)
 * Ghidra: void FUN_00351e14(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e14(void){ return; }
/* FUN_00351e20 @ 0x00351e20   (est. sk_f_00351e20)
 * Ghidra: void FUN_00351e20(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e20(void){ return; }
/* FUN_00351e3c @ 0x00351e3c   (est. sk_f_00351e3c)
 * Ghidra: void FUN_00351e3c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e3c(void){ return; }
/* FUN_00351e48 @ 0x00351e48   (est. sk_f_00351e48)
 * Ghidra: void FUN_00351e48(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e48(void){ return; }
/* FUN_00351e54 @ 0x00351e54   (est. sk_f_00351e54)
 * Ghidra: void FUN_00351e54(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e54(void){ return; }
/* FUN_00351e60 @ 0x00351e60   (est. sk_f_00351e60)
 * Ghidra: void FUN_00351e60(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e60(void){ return; }
/* FUN_00351e6c @ 0x00351e6c   (est. sk_f_00351e6c)
 * Ghidra: void FUN_00351e6c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e6c(void){ return; }
/* FUN_00351e78 @ 0x00351e78   (est. sk_f_00351e78)
 * Ghidra: void FUN_00351e78(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e78(void){ return; }
/* FUN_00351e84 @ 0x00351e84   (est. sk_f_00351e84)
 * Ghidra: void FUN_00351e84(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e84(void){ return; }
/* FUN_00351e90 @ 0x00351e90   (est. sk_f_00351e90)
 * Ghidra: void FUN_00351e90(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e90(void){ return; }
/* FUN_00351e9c @ 0x00351e9c   (est. sk_f_00351e9c)
 * Ghidra: void FUN_00351e9c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351e9c(void){ return; }
/* FUN_00351ea8 @ 0x00351ea8   (est. sk_f_00351ea8)
 * Ghidra: void FUN_00351ea8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351ea8(void){ return; }
/* FUN_00351eb4 @ 0x00351eb4   (est. sk_f_00351eb4)
 * Ghidra: void FUN_00351eb4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351eb4(void){ return; }
/* FUN_00351ec0 @ 0x00351ec0   (est. sk_f_00351ec0)
 * Ghidra: void FUN_00351ec0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351ec0(void){ return; }
/* FUN_00351ecc @ 0x00351ecc   (est. sk_f_00351ecc)
 * Ghidra: undefined8 FUN_00351ecc(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_00351ecc(void){ return 0; }
/* FUN_00351ee0 @ 0x00351ee0   (est. sk_f_00351ee0)
 * Ghidra: void FUN_00351ee0(void)
 * Forwarding thunk; calls FUN_00310b08 (swift_type_metadata_field_14) and returns.
 * Confidence: medium
 * Notes: forwards to 00310b08. */
void sk_f_00351ee0(void){ sk_h_00310b08(); return; }
/* FUN_00351ef8 @ 0x00351ef8   (est. sk_f_00351ef8)
 * Ghidra: void FUN_00351ef8(void)
 * Forwarding thunk; calls FUN_00027754 (boot-region helper) and returns.
 * Confidence: medium
 * Notes: forwards to 00027754. */
void sk_f_00351ef8(void){ sk_h_00027754(); return; }
/* FUN_00351f10 @ 0x00351f10   (est. sk_f_00351f10)
 * Ghidra: void FUN_00351f10(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f10(void){ return; }
/* FUN_00351f1c @ 0x00351f1c   (est. sk_f_00351f1c)
 * Ghidra: void FUN_00351f1c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f1c(void){ return; }
/* FUN_00351f28 @ 0x00351f28   (est. sk_f_00351f28)
 * Ghidra: void FUN_00351f28(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f28(void){ return; }
/* FUN_00351f34 @ 0x00351f34   (est. sk_f_00351f34)
 * Ghidra: void FUN_00351f34(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f34(void){ return; }
/* FUN_00351f40 @ 0x00351f40   (est. sk_f_00351f40)
 * Ghidra: void FUN_00351f40(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f40(void){ return; }
/* FUN_00351f4c @ 0x00351f4c   (est. sk_f_00351f4c)
 * Ghidra: void FUN_00351f4c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f4c(void){ return; }
/* FUN_00351f58 @ 0x00351f58   (est. sk_f_00351f58)
 * Ghidra: void FUN_00351f58(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f58(void){ return; }
/* FUN_00351f64 @ 0x00351f64   (est. sk_f_00351f64)
 * Ghidra: void FUN_00351f64(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f64(void){ return; }
/* FUN_00351f70 @ 0x00351f70   (est. sk_f_00351f70)
 * Ghidra: void FUN_00351f70(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f70(void){ return; }
/* FUN_00351f7c @ 0x00351f7c   (est. sk_f_00351f7c)
 * Ghidra: void FUN_00351f7c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f7c(void){ return; }
/* FUN_00351f88 @ 0x00351f88   (est. sk_f_00351f88)
 * Ghidra: void FUN_00351f88(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f88(void){ return; }
/* FUN_00351f94 @ 0x00351f94   (est. sk_f_00351f94)
 * Ghidra: void FUN_00351f94(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351f94(void){ return; }
/* FUN_00351fb0 @ 0x00351fb0   (est. sk_f_00351fb0)
 * Ghidra: void FUN_00351fb0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00351fb0(void){ return; }
/* FUN_00351fc0 @ 0x00351fc0   (est. sk_f_00351fc0)
 * Ghidra: void FUN_00351fc0(undefined8 param_1)  [writes via unaff_x19]
 * Stores the low 32 bits of its argument as an int at offset 0 of the
 * caller-provided word pointer (unaff_x19), then stores bit 32..39 as a byte at
 * byte offset 4. A 5-byte field-packing write.
 * Confidence: medium
 * Notes: unaff_x19 (caller register) modeled as a dst parameter. */
void sk_f_00351fc0(word_t value, uint32_t *dst){
  dst[0] = (uint32_t)value;
  ((byte*)dst)[4] = (byte)(value >> 32);
}
/* FUN_00351fd0 @ 0x00351fd0   (est. sk_f_00351fd0)
 * Ghidra: undefined1[16] FUN_00351fd0(void)  [reads unaff_x19, unaff_x22]
 * Builds a 16-byte value from two compiler-carried registers: hi = (r22 &
 * 0xffffffffffff), lo = (r19 & 0xfffffffffffffff) + 0x20. The +0x20 and low-bit
 * masking suggest a tagged pointer + small offset construction. Called from six
 * sites in the 0x22xxxx range.
 * Confidence: medium
 * Notes: unaff_x19/x22 modeled as parameters; 0x20 offset of unknown meaning. */
sk16_t sk_f_00351fd0(word_t r19, word_t r22){
  sk16_t r;
  r.hi = r22 & 0xffffffffffffull;
  r.lo = (r19 & 0xfffffffffffffffull) + 0x20;
  return r;
}
/* FUN_00351fe0 @ 0x00351fe0   (est. sk_f_00351fe0)
 * Ghidra: void FUN_00351fe0(void)  [reads *(unaff_x29 + -0x78)]
 * Loads the caller-frame word at x29-0x78, passes it to FUN_00310a74
 * (swift_type_metadata_field_30), then calls FUN_0001df60.
 * Confidence: low
 * Notes: unaff_x29 caller frame; the x29-0x78 slot modeled as a parameter. */
void sk_f_00351fe0(word_t frame_slot){
  sk_h_00310a74(frame_slot);
  sk_h_0001df60();
}
/* FUN_00352008 @ 0x00352008   (est. sk_f_00352008)
 * Ghidra: void FUN_00352008(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352008(void){ return; }
/* FUN_00352018 @ 0x00352018   (est. sk_f_00352018)
 * Ghidra: void FUN_00352018(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352018(void){ return; }
/* FUN_00352028 @ 0x00352028   (est. sk_f_00352028)
 * Ghidra: void FUN_00352028(undefined8 param_1,long param_2)  [writes unaff_x20+8]
 * Copies the word at (param_2 + 8) into the word at (unaff_x20 + 8). A
 * field-copy thunk (element 1 of a two-word pair).
 * Confidence: low
 * Notes: unaff_x20 (caller register) modeled as dst; param_1 ignored. */
void sk_f_00352028(word_t arg1, word_t *src, word_t *dst){
  dst[1] = src[1];
}
/* FUN_00352038 @ 0x00352038   (est. sk_f_00352038)
 * Ghidra: void FUN_00352038(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352038(void){ return; }
/* FUN_00352048 @ 0x00352048   (est. sk_f_00352048)
 * Ghidra: undefined8 FUN_00352048(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_00352048(void){ return 0; }
/* FUN_00352058 @ 0x00352058   (est. sk_f_00352058)
 * Ghidra: undefined1[16] FUN_00352058(void)
 * Returns {lo=1, hi=&stack0x00000020} — a {tag=1, ptr} pair where the "ptr" is
 * an address into the caller stack that Ghidra could not resolve to a symbol.
 * Confidence: low
 * Notes: hi is the Ghidra artifact &stack0x00000020; modeled as a parameter. */
sk16_t sk_f_00352058(word_t stack_ptr){
  sk16_t r; r.lo = 1; r.hi = stack_ptr; return r;
}
/* FUN_00352068 @ 0x00352068   (est. sk_f_00352068)
 * Ghidra: void FUN_00352068(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352068(void){ return; }
/* FUN_00352078 @ 0x00352078   (est. sk_f_00352078)
 * Ghidra: void FUN_00352078(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352078(void){ return; }
/* FUN_00352088 @ 0x00352088   (est. sk_f_00352088)
 * Ghidra: void FUN_00352088(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352088(void){ return; }
/* FUN_00352098 @ 0x00352098   (est. sk_f_00352098)
 * Ghidra: void FUN_00352098(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352098(void){ return; }
/* FUN_003520a4 @ 0x003520a4   (est. sk_f_003520a4)
 * Ghidra: undefined1[16] FUN_003520a4(undefined8 param_1)
 * Returns {lo=1, hi=param_1} — a {tag, value} pair builder.
 * Confidence: medium
 * Notes: packs a single value with the tag 1. */
sk16_t sk_f_003520a4(word_t value){
  sk16_t r; r.lo = 1; r.hi = value; return r;
}
/* FUN_003520b4 @ 0x003520b4   (est. sk_f_003520b4)
 * Ghidra: undefined8 FUN_003520b4(long param_1)
 * Loads and returns the word at (param_1 - 0x100). A negative-offset field load.
 * Confidence: low
 * Notes: reads 0x100 bytes before the argument (caller metadata block). */
word_t sk_f_003520b4(word_t *base){
  return *(word_t*)((char*)base - 0x100);
}
/* FUN_003520c0 @ 0x003520c0   (est. sk_f_003520c0)
 * Ghidra: void FUN_003520c0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003520c0(void){ return; }
/* FUN_003520d0 @ 0x003520d0   (est. sk_f_003520d0)
 * Ghidra: void FUN_003520d0(void)  [writes unaff_x29 + -0x58]
 * Stores the constant 0x8000000000000000 (sign bit set) into the caller-frame
 * slot at x29-0x58. A sentinel-init write.
 * Confidence: low
 * Notes: unaff_x29 caller frame; slot modeled as a parameter. */
void sk_f_003520d0(word_t *frame_slot){
  *frame_slot = 0x8000000000000000ull;
}
/* FUN_003520dc @ 0x003520dc   (est. sk_f_003520dc)
 * Ghidra: void FUN_003520dc(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003520dc(void){ return; }
/* FUN_003520e8 @ 0x003520e8   (est. sk_f_003520e8)
 * Ghidra: ulong FUN_003520e8(long param_1)  [reads unaff_x19, in_x9]
 * Returns (param_1 + r19) & ~r9 — align-down to a mask from compiler-carried
 * registers. A classic address-alignment primitive.
 * Confidence: low
 * Notes: unaff_x19 and in_x9 (unresolved register inputs) modeled as params. */
word_t sk_f_003520e8(word_t value, word_t r19, word_t r9){
  return (value + r19) & ~r9;
}
/* FUN_003520f8 @ 0x003520f8   (est. sk_f_003520f8)
 * Ghidra: void FUN_003520f8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003520f8(void){ return; }
/* FUN_00352108 @ 0x00352108   (est. sk_f_00352108)
 * Ghidra: void FUN_00352108(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352108(void){ return; }
/* FUN_00352118 @ 0x00352118   (est. sk_f_00352118)
 * Ghidra: void FUN_00352118(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352118(void){ return; }
/* FUN_00352128 @ 0x00352128   (est. sk_f_00352128)
 * Ghidra: void FUN_00352128(undefined8 param_1)  [writes unaff_x29 + -0x78]
 * Stores its argument into the caller-frame slot at x29-0x78. A spill write.
 * Confidence: low
 * Notes: unaff_x29 caller frame; slot modeled as a parameter. */
void sk_f_00352128(word_t value, word_t *frame_slot){
  *frame_slot = value;
}
/* FUN_00352134 @ 0x00352134   (est. sk_f_00352134)
 * Ghidra: void FUN_00352134(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352134(void){ return; }
/* FUN_00352140 @ 0x00352140   (est. sk_f_00352140)
 * Ghidra: undefined8 FUN_00352140(void)  [reads unaff_x29 + -0x2b0]
 * Loads and returns the word at the caller-frame slot x29-0x2b0.
 * Confidence: low
 * Notes: unaff_x29 caller frame; slot modeled as a parameter. */
word_t sk_f_00352140(word_t *frame_slot){
  return *frame_slot;
}
/* FUN_0035215c @ 0x0035215c   (est. sk_f_0035215c)
 * Ghidra: void FUN_0035215c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035215c(void){ return; }
/* FUN_0035216c @ 0x0035216c   (est. sk_f_0035216c)
 * Ghidra: void FUN_0035216c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035216c(void){ return; }
/* FUN_0035217c @ 0x0035217c   (est. sk_f_0035217c)
 * Ghidra: void FUN_0035217c(undefined8 param_1)  [writes unaff_x29 + -0x58]
 * Stores its argument into the caller-frame slot at x29-0x58. A spill write.
 * Confidence: low
 * Notes: unaff_x29 caller frame; slot modeled as a parameter. */
void sk_f_0035217c(word_t value, word_t *frame_slot){
  *frame_slot = value;
}
/* FUN_00352188 @ 0x00352188   (est. sk_f_00352188)
 * Ghidra: void FUN_00352188(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352188(void){ return; }
/* FUN_00352194 @ 0x00352194   (est. sk_f_00352194)
 * Ghidra: undefined8 FUN_00352194(undefined8 *param_1)
 * Loads and returns the 64-bit value pointed to by its argument. A load thunk.
 * Confidence: medium
 * Notes: dereferences the word pointer argument. */
word_t sk_f_00352194(word_t *ptr){ return *ptr; }
/* FUN_003521a4 @ 0x003521a4   (est. sk_f_003521a4)
 * Ghidra: void FUN_003521a4(void)  [writes unaff_x29 + -0x48]
 * Stores the address of DAT_00657778 into the caller-frame slot at x29-0x48.
 * A global-address init write.
 * Confidence: low
 * Notes: unaff_x29 caller frame; DAT_00657778 (opaque global) modeled as extern. */
void sk_f_003521a4(word_t *frame_slot){
  *frame_slot = (word_t)(uintptr_t)&sk_d_00657778;
}
/* FUN_003521b4 @ 0x003521b4   (est. sk_f_003521b4)
 * Ghidra: void FUN_003521b4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003521b4(void){ return; }
/* FUN_003521c4 @ 0x003521c4   (est. sk_f_003521c4)
 * Ghidra: void FUN_003521c4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003521c4(void){ return; }
/* FUN_003521d4 @ 0x003521d4   (est. sk_f_003521d4)
 * Ghidra: void FUN_003521d4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003521d4(void){ return; }
/* FUN_003521e4 @ 0x003521e4   (est. sk_f_003521e4)
 * Ghidra: void FUN_003521e4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003521e4(void){ return; }
/* FUN_00352200 @ 0x00352200   (est. sk_f_00352200)
 * Ghidra: void FUN_00352200(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352200(void){ return; }
/* FUN_00352210 @ 0x00352210   (est. sk_f_00352210)
 * Ghidra: void FUN_00352210(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352210(void){ return; }
/* FUN_00352220 @ 0x00352220   (est. sk_f_00352220)
 * Ghidra: void FUN_00352220(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352220(void){ return; }
/* FUN_00352230 @ 0x00352230   (est. sk_f_00352230)
 * Ghidra: void FUN_00352230(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352230(void){ return; }
/* FUN_00352240 @ 0x00352240   (est. sk_f_00352240)
 * Ghidra: void FUN_00352240(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352240(void){ return; }
/* FUN_00352250 @ 0x00352250   (est. sk_f_00352250)
 * Ghidra: void FUN_00352250(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352250(void){ return; }
/* FUN_00352260 @ 0x00352260   (est. sk_f_00352260)
 * Ghidra: undefined1[16] FUN_00352260(void)  [reads unaff_x29 + -0x60]
 * Loads and returns the 16-byte value at the caller-frame slot x29-0x60.
 * Confidence: low
 * Notes: unaff_x29 caller frame; slot modeled as a parameter. */
sk16_t sk_f_00352260(sk16_t *frame_slot){ return *frame_slot; }
/* FUN_00352270 @ 0x00352270   (est. sk_f_00352270)
 * Ghidra: void FUN_00352270(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352270(void){ return; }
/* FUN_00352280 @ 0x00352280   (est. sk_f_00352280)
 * Ghidra: void FUN_00352280(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352280(void){ return; }
/* FUN_00352290 @ 0x00352290   (est. sk_f_00352290)
 * Ghidra: void FUN_00352290(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352290(void){ return; }
/* FUN_0035229c @ 0x0035229c   (est. sk_f_0035229c)
 * Ghidra: void FUN_0035229c(ulong param_1)  [writes unaff_x20 + 0x20]
 * Stores (param_1 & (param_1 - 1)) into the word at (unaff_x20 + 0x20). Clears
 * the lowest set bit — the classic "is a power of two" / bit-unset primitive.
 * Confidence: medium
 * Notes: unaff_x20 (caller register) modeled as dst pointer. */
void sk_f_0035229c(word_t v, word_t *dst){
  dst[4] = v & (v - 1);
}
/* FUN_003522b8 @ 0x003522b8   (est. sk_f_003522b8)
 * Ghidra: void FUN_003522b8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003522b8(void){ return; }
/* FUN_003522c8 @ 0x003522c8   (est. sk_f_003522c8)
 * Ghidra: void FUN_003522c8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003522c8(void){ return; }
/* FUN_003522d4 @ 0x003522d4   (est. sk_f_003522d4)
 * Ghidra: void FUN_003522d4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003522d4(void){ return; }
/* FUN_003522e4 @ 0x003522e4   (est. sk_f_003522e4)
 * Ghidra: void FUN_003522e4(void)
 * Calls FUN_00310a74 (swift_type_metadata_field_30) then FUN_0001df60.
 * Confidence: low
 * Notes: no args shown; helper pair call. */
void sk_f_003522e4(void){ sk_h_00310a74(0); sk_h_0001df60(); return; }
/* FUN_00352304 @ 0x00352304   (est. sk_f_00352304)
 * Ghidra: undefined8 FUN_00352304(void)
 * Returns constant 0xff (255).
 * Confidence: medium
 * Notes: constant return; 0xff is a common max-byte sentinel. */
word_t sk_f_00352304(void){ return 0xff; }
/* FUN_00352314 @ 0x00352314   (est. sk_f_00352314)
 * Ghidra: void FUN_00352314(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352314(void){ return; }
/* FUN_00352320 @ 0x00352320   (est. sk_f_00352320)
 * Ghidra: void FUN_00352320(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352320(void){ return; }
/* FUN_00352330 @ 0x00352330   (est. sk_f_00352330)
 * Ghidra: void FUN_00352330(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352330(void){ return; }
/* FUN_00352340 @ 0x00352340   (est. sk_f_00352340)
 * Ghidra: void FUN_00352340(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352340(void){ return; }
/* FUN_00352350 @ 0x00352350   (est. sk_f_00352350)
 * Ghidra: void FUN_00352350(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352350(void){ return; }
/* FUN_00352360 @ 0x00352360   (est. sk_f_00352360)
 * Ghidra: void FUN_00352360(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352360(void){ return; }
/* FUN_00352370 @ 0x00352370   (est. sk_f_00352370)
 * Ghidra: void FUN_00352370(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352370(void){ return; }
/* FUN_0035237c @ 0x0035237c   (est. sk_f_0035237c)
 * Ghidra: undefined1[16] FUN_0035237c(undefined1 (*param_1)[16])
 * Loads and returns the 16-byte value pointed to by its argument. A load thunk.
 * Confidence: medium
 * Notes: dereferences the 16-byte pointer argument. */
sk16_t sk_f_0035237c(sk16_t *ptr){ return *ptr; }
/* FUN_0035238c @ 0x0035238c   (est. sk_f_0035238c)
 * Ghidra: void FUN_0035238c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035238c(void){ return; }
/* FUN_0035239c @ 0x0035239c   (est. sk_f_0035239c)
 * Ghidra: undefined1[16] FUN_0035239c(p1,p2,p3)
 * Returns {lo=param_2, hi=param_3}, ignoring param_1. A pair builder.
 * Called from FUN_002b45a8, FUN_002b7808, FUN_002b7830.
 * Confidence: medium
 * Notes: argument 1 ignored; packs args 2 and 3 into the 16-byte result. */
sk16_t sk_f_0035239c(word_t arg1, word_t lo, word_t hi){
  sk16_t r; r.lo = lo; r.hi = hi; return r;
}
/* FUN_003523ac @ 0x003523ac   (est. sk_f_003523ac)
 * Ghidra: void FUN_003523ac(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003523ac(void){ return; }
/* FUN_003523bc @ 0x003523bc   (est. sk_f_003523bc)
 * Ghidra: void FUN_003523bc(void)  [reads unaff_x28, writes unaff_x29 + -0x60]
 * Stores the compiler-carried register unaff_x28 into the caller-frame slot at
 * x29-0x60, then calls FUN_00310a74 (swift_type_metadata_field_30) and
 * FUN_0001df60.
 * Confidence: low
 * Notes: unaff_x28/x29 modeled as parameters. */
void sk_f_003523bc(word_t r28, word_t *frame_slot){
  *frame_slot = r28;
  sk_h_00310a74(0);
  sk_h_0001df60();
}
/* FUN_003523e0 @ 0x003523e0   (est. sk_f_003523e0)
 * Ghidra: void FUN_003523e0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003523e0(void){ return; }
/* FUN_003523f0 @ 0x003523f0   (est. sk_f_003523f0)
 * Ghidra: void FUN_003523f0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003523f0(void){ return; }
/* FUN_003523fc @ 0x003523fc   (est. sk_f_003523fc)
 * Ghidra: void FUN_003523fc(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003523fc(void){ return; }
/* FUN_00352408 @ 0x00352408   (est. sk_f_00352408)
 * Ghidra: void FUN_00352408(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352408(void){ return; }
/* FUN_00352414 @ 0x00352414   (est. sk_f_00352414)
 * Ghidra: void FUN_00352414(void)  [writes *unaff_x19]
 * Stores the constant 0x8000000000000000 (sign bit set) into the word pointed
 * to by unaff_x19. A sentinel-init write.
 * Confidence: low
 * Notes: unaff_x19 (caller register) modeled as a dst pointer. */
void sk_f_00352414(word_t *dst){
  *dst = 0x8000000000000000ull;
}
/* FUN_00352420 @ 0x00352420   (est. sk_f_00352420)
 * Ghidra: void FUN_00352420(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352420(void){ return; }
/* FUN_0035242c @ 0x0035242c   (est. sk_f_0035242c)
 * Ghidra: void FUN_0035242c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035242c(void){ return; }
/* FUN_00352438 @ 0x00352438   (est. sk_f_00352438)
 * Ghidra: void FUN_00352438(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352438(void){ return; }
/* FUN_00352444 @ 0x00352444   (est. sk_f_00352444)
 * Ghidra: void FUN_00352444(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00352444(void){ return; }
/* FUN_003530e8 @ 0x003530e8   (est. sk_f_003530e8)
 * Ghidra: void FUN_003530e8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003530e8(void){ return; }
/* FUN_003530f4 @ 0x003530f4   (est. sk_f_003530f4)
 * Ghidra: void FUN_003530f4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003530f4(void){ return; }
/* FUN_00353100 @ 0x00353100   (est. sk_f_00353100)
 * Ghidra: void FUN_00353100(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00353100(void){ return; }
/* FUN_0035310c @ 0x0035310c   (est. sk_f_0035310c)
 * Ghidra: void FUN_0035310c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035310c(void){ return; }
/* FUN_00353118 @ 0x00353118   (est. sk_f_00353118)
 * Ghidra: void FUN_00353118(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00353118(void){ return; }
