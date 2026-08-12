/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 17: 0x350048-0x350c14 syscall/exception-entry region (stub/trampoline table). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit value returned in the x0:x1 register pair. */
typedef struct { uint64_t lo, hi; } cl4_pair_t;

extern char sk_stack_anchor;   /* synthetic stack symbol for frame-depth deltas */
extern word_t sk_global_4c1010;
extern word_t sk_syscall_table_4e984c[];
extern word_t sk_syscall_table_4e9518[];

/* Out-of-range cL4 helpers referenced by trampolines below (declared extern;
 * bodies reconstructed by their owning range workers). */
extern void sk_sys_dispatch_001a89a8(void);
extern void sk_sys_dispatch_003109b4(void);
extern void sk_sys_dispatch_0008f728(void);
extern void sk_sys_dispatch_0031948c(void);
extern void sk_sys_dispatch_00310a74(void);
extern void sk_sys_dispatch_000a68c4(void);
extern void sk_sys_dispatch_000277b8(void);
extern void sk_sys_dispatch_00310924(void);
extern void sk_sys_dispatch_00027754(void);
extern void sk_sys_dispatch_00310a44(void);
extern void sk_sys_dispatch_000839f8(void);
extern void sk_sys_dispatch_0016186c(void);
extern void sk_sys_dispatch_0014ae44(void);
extern void sk_assert_msg(const char *msg, unsigned long len, unsigned long code);
extern void sk_cache_maintenance(void);  /* FUN_0016186c */

/* FUN_00350048 @ 0x00350048   (est. sk_sys_stub_0048)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0048(void)
{
  /* no-op */
}

/* FUN_00350058 @ 0x00350058   (est. sk_sys_stub_0058)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0058(void)
{
  /* no-op */
}

/* FUN_00350068 @ 0x00350068   (est. sk_sys_stub_0068)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0068(void)
{
  /* no-op */
}

/* FUN_00350078 @ 0x00350078   (est. sk_sys_stub_0078)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0078(void)
{
  /* no-op */
}

/* FUN_00350088 @ 0x00350088   (est. sk_sys_stub_0088)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0088(void)
{
  /* no-op */
}

/* FUN_00350098 @ 0x00350098   (est. sk_sys_stub_0098)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0098(void)
{
  /* no-op */
}

/* FUN_003500B0 @ 0x003500b0   (est. sk_sys_stub_00b0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_00b0(void)
{
  /* no-op */
}

/* FUN_003500C0 @ 0x003500c0   (est. sk_sys_stub_00c0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_00c0(void)
{
  /* no-op */
}

/* FUN_003500D4 @ 0x003500d4   (est. sk_sys_stub_00d4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_00d4(void)
{
  /* no-op */
}

/* FUN_003500E4 @ 0x003500e4   (est. sk_sys_stub_00e4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_00e4(void)
{
  /* no-op */
}

/* FUN_003500F4 @ 0x003500f4   (est. sk_sys_stub_00f4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_00f4(void)
{
  /* no-op */
}

/* FUN_00350104 @ 0x00350104   (est. sk_sys_stub_0104)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0104(void)
{
  /* no-op */
}

/* FUN_00350114 @ 0x00350114   (est. sk_add_trampoline)
 * sum of two values carried in callee-saved regs x20/x24 (Ghidra unaff_x20/unaff_x24)
 * Confidence: medium */
word_t sk_sys_0114()
{
  word_t val_b;  /* from x24 */
  word_t val_a;  /* from x20 */
  return val_b + val_a;
}

/* FUN_0035012C @ 0x0035012c   (est. sk_sys_stub_012c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_012c(void)
{
  /* no-op */
}

/* FUN_0035013C @ 0x0035013c   (est. sk_sys_stub_013c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_013c(void)
{
  /* no-op */
}

/* FUN_0035014C @ 0x0035014c   (est. sk_sys_stub_014c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_014c(void)
{
  /* no-op */
}

/* FUN_00350164 @ 0x00350164   (est. sk_sys_stub_0164)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0164(void)
{
  /* no-op */
}

/* FUN_00350198 @ 0x00350198   (est. sk_sys_stub_0198)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0198(void)
{
  /* no-op */
}

/* FUN_003501A8 @ 0x003501a8   (est. sk_sys_stub_01a8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_01a8(void)
{
  /* no-op */
}

/* FUN_003501B8 @ 0x003501b8   (est. sk_sys_stub_01b8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_01b8(void)
{
  /* no-op */
}

/* FUN_003501D0 @ 0x003501d0   (est. sk_frame_spill)
 * records stack-depth delta into caller frame slot fp-0xf0
 * Confidence: medium */
void sk_sys_01d0(word_t arg, word_t *fp)
{
  /* Ghidra: *(long *)(unaff_x29 + -0xf0) = (long)&stack0x00000000 - arg */
  fp[-30] = (word_t)&sk_stack_anchor - arg;
}

/* FUN_003501E4 @ 0x003501e4   (est. sk_frame_spill)
 * records stack-depth delta into caller frame slot fp-0x148
 * Confidence: medium */
void sk_sys_01e4(word_t arg, word_t *fp)
{
  /* Ghidra: *(long *)(unaff_x29 + -0x148) = (long)&stack0x00000000 - arg */
  fp[-41] = (word_t)&sk_stack_anchor - arg;
}

/* FUN_003501FC @ 0x003501fc   (est. sk_frame_save)
 * stores arg + 4 callee-saved regs into record (offsets 0x20-0x38)
 * Confidence: medium */
void sk_sys_01fc(word_t *rec, word_t *save_slot)
{
  *save_slot = (word_t)rec;
  word_t x19, x20, x21, x22;  /* callee-saved regs */
  rec[6] = x19;  /* +0x30 */
  rec[7] = x20;  /* +0x38 */
  rec[4] = x22;  /* +0x20 */
  rec[5] = x21;  /* +0x28 */
}

/* FUN_00350210 @ 0x00350210   (est. sk_sys_stub_0210)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0210(void)
{
  /* no-op */
}

/* FUN_00350220 @ 0x00350220   (est. sk_sys_stub_0220)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0220(void)
{
  /* no-op */
}

/* FUN_00350230 @ 0x00350230   (est. sk_sys_stub_0230)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0230(void)
{
  /* no-op */
}

/* FUN_00350240 @ 0x00350240   (est. sk_load16)
 * loads and returns 16 bytes at src
 * Confidence: medium */
cl4_pair_t sk_sys_0240(const word_t *src)
{
  return (cl4_pair_t){ .lo = src[0], .hi = src[1] };
}

/* FUN_00350258 @ 0x00350258   (est. sk_load64)
 * loads word at src
 * Confidence: medium */
word_t sk_sys_0258(const word_t *src)
{
  return *src;
}

/* FUN_00350268 @ 0x00350268   (est. sk_sys_stub_0268)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0268(void)
{
  /* no-op */
}

/* FUN_00350278 @ 0x00350278   (est. sk_sys_stub_0278)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0278(void)
{
  /* no-op */
}

/* FUN_00350288 @ 0x00350288   (est. sk_sys_stub_0288)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0288(void)
{
  /* no-op */
}

/* FUN_00350298 @ 0x00350298   (est. sk_sys_stub_0298)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0298(void)
{
  /* no-op */
}

/* FUN_003502A8 @ 0x003502a8   (est. sk_sys_stub_02a8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_02a8(void)
{
  /* no-op */
}

/* FUN_003502B8 @ 0x003502b8   (est. sk_sys_stub_02b8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_02b8(void)
{
  /* no-op */
}

/* FUN_003502C8 @ 0x003502c8   (est. sk_sys_stub_02c8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_02c8(void)
{
  /* no-op */
}

/* FUN_003502D8 @ 0x003502d8   (est. sk_sys_stub_02d8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_02d8(void)
{
  /* no-op */
}

/* FUN_003502E8 @ 0x003502e8   (est. sk_sys_stub_02e8)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_02e8(void)
{
  return 0;
}

/* FUN_003502F8 @ 0x003502f8   (est. sk_sys_stub_02f8)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_02f8(void)
{
  return 0;
}

/* FUN_00350308 @ 0x00350308   (est. sk_sys_stub_0308)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0308(void)
{
  return 0;
}

/* FUN_00350318 @ 0x00350318   (est. sk_sys_stub_0318)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0318(void)
{
  return 0;
}

/* FUN_00350328 @ 0x00350328   (est. sk_make_pair)
 * builds 128-bit pair, value in high half (Ghidra auVar1 << 0x40)
 * Confidence: medium */
cl4_pair_t sk_sys_0328(word_t in_x4)
{
  return (cl4_pair_t){ .lo = 0, .hi = in_x4 };
}

/* FUN_00350338 @ 0x00350338   (est. sk_frame_load)
 * loads word at fp-0x70 (Ghidra *(unaff_x29-0x70))
 * Confidence: medium */
word_t sk_sys_0338(word_t *fp)
{
  return fp[-14];  /* +? fp-0x70 */
}

/* FUN_0035034C @ 0x0035034c   (est. sk_sys_stub_034c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_034c(void)
{
  /* no-op */
}

/* FUN_0035035C @ 0x0035035c   (est. sk_sys_stub_035c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_035c(void)
{
  /* no-op */
}

/* FUN_0035036C @ 0x0035036c   (est. sk_sys_stub_036c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_036c(void)
{
  /* no-op */
}

/* FUN_0035037C @ 0x0035037c   (est. sk_sys_stub_037c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_037c(void)
{
  /* no-op */
}

/* FUN_00350390 @ 0x00350390   (est. sk_sys_stub_0390)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0390(void)
{
  /* no-op */
}

/* FUN_003503A0 @ 0x003503a0   (est. sk_sys_stub_03a0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03a0(void)
{
  /* no-op */
}

/* FUN_003503B0 @ 0x003503b0   (est. sk_sys_stub_03b0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03b0(void)
{
  /* no-op */
}

/* FUN_003503C0 @ 0x003503c0   (est. sk_forward_arg2)
 * forwards second argument
 * Confidence: medium */
word_t sk_sys_03c0(word_t param_1, word_t param_2)
{
  return param_2;
}

/* FUN_003503D0 @ 0x003503d0   (est. sk_sys_stub_03d0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03d0(void)
{
  /* no-op */
}

/* FUN_003503E0 @ 0x003503e0   (est. sk_sys_stub_03e0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03e0(void)
{
  /* no-op */
}

/* FUN_003503EC @ 0x003503ec   (est. sk_sys_stub_03ec)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03ec(void)
{
  /* no-op */
}

/* FUN_003503F8 @ 0x003503f8   (est. sk_sys_stub_03f8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_03f8(void)
{
  /* no-op */
}

/* FUN_00350404 @ 0x00350404   (est. sk_sys_stub_0404)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0404(void)
{
  /* no-op */
}

/* FUN_00350410 @ 0x00350410   (est. sk_sys_stub_0410)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0410(void)
{
  /* no-op */
}

/* FUN_0035041C @ 0x0035041c   (est. sk_sys_stub_041c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_041c(void)
{
  /* no-op */
}

/* FUN_00350428 @ 0x00350428   (est. sk_sys_stub_0428)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0428(void)
{
  /* no-op */
}

/* FUN_00350434 @ 0x00350434   (est. sk_sys_stub_0434)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0434(void)
{
  /* no-op */
}

/* FUN_00350440 @ 0x00350440   (est. sk_global_addr_4c1010)
 * returns address of global DAT_004c1010
 * Confidence: medium */
word_t *sk_sys_0440()
{
  return &sk_global_4c1010;
}

/* FUN_0035044C @ 0x0035044c   (est. sk_cache_maintenance)
 * tail call FUN_0016186c (cache maintenance)
 * Confidence: medium */
void sk_sys_044c()
{
  sk_cache_maintenance();
}

/* FUN_00350464 @ 0x00350464   (est. sk_sys_stub_0464)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0464(void)
{
  /* no-op */
}

/* FUN_00350470 @ 0x00350470   (est. sk_sys_stub_0470)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0470(void)
{
  /* no-op */
}

/* FUN_0035047C @ 0x0035047c   (est. sk_sys_stub_047c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_047c(void)
{
  /* no-op */
}

/* FUN_00350488 @ 0x00350488   (est. sk_sys_stub_0488)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0488(void)
{
  return 0;
}

/* FUN_00350494 @ 0x00350494   (est. sk_sys_stub_0494)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0494(void)
{
  /* no-op */
}

/* FUN_003504A0 @ 0x003504a0   (est. sk_sys_stub_04a0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04a0(void)
{
  /* no-op */
}

/* FUN_003504AC @ 0x003504ac   (est. sk_sys_stub_04ac)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04ac(void)
{
  /* no-op */
}

/* FUN_003504B8 @ 0x003504b8   (est. sk_sys_stub_04b8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04b8(void)
{
  /* no-op */
}

/* FUN_003504C4 @ 0x003504c4   (est. sk_sys_stub_04c4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04c4(void)
{
  /* no-op */
}

/* FUN_003504D0 @ 0x003504d0   (est. sk_sys_stub_04d0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04d0(void)
{
  /* no-op */
}

/* FUN_003504DC @ 0x003504dc   (est. sk_sys_stub_04dc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04dc(void)
{
  /* no-op */
}

/* FUN_003504E8 @ 0x003504e8   (est. sk_sys_stub_04e8)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_04e8(void)
{
  return 0;
}

/* FUN_003504F4 @ 0x003504f4   (est. sk_sys_stub_04f4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_04f4(void)
{
  /* no-op */
}

/* FUN_00350500 @ 0x00350500   (est. sk_sys_stub_0500)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0500(void)
{
  return 0;
}

/* FUN_0035050C @ 0x0035050c   (est. sk_sys_stub_050c)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_050c(void)
{
  return 0;
}

/* FUN_00350518 @ 0x00350518   (est. sk_sys_stub_0518)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0518(void)
{
  /* no-op */
}

/* FUN_00350524 @ 0x00350524   (est. sk_sys_stub_0524)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0524(void)
{
  /* no-op */
}

/* FUN_00350530 @ 0x00350530   (est. sk_sys_stub_0530)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0530(void)
{
  return 0;
}

/* FUN_0035053C @ 0x0035053c   (est. sk_sys_stub_053c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_053c(void)
{
  /* no-op */
}

/* FUN_00350548 @ 0x00350548   (est. sk_sys_stub_0548)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0548(void)
{
  /* no-op */
}

/* FUN_00350554 @ 0x00350554   (est. sk_sys_stub_0554)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0554(void)
{
  /* no-op */
}

/* FUN_00350560 @ 0x00350560   (est. sk_sys_stub_0560)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0560(void)
{
  /* no-op */
}

/* FUN_0035056C @ 0x0035056c   (est. sk_sys_stub_056c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_056c(void)
{
  /* no-op */
}

/* FUN_00350578 @ 0x00350578   (est. sk_sys_stub_0578)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0578(void)
{
  /* no-op */
}

/* FUN_00350584 @ 0x00350584   (est. sk_sys_forward_109b4)
 * tail call FUN_003109b4
 * Confidence: medium */
void sk_sys_0584()
{
  sk_sys_dispatch_003109b4();
}

/* FUN_0035059C @ 0x0035059c   (est. sk_assert_value)
 * assert-fail entry, prints "value " via FUN_001a89a8 (s_value_005ce9d2)
 * Confidence: medium */
void sk_sys_059c()
{
  sk_assert_msg("value ", 7, 1);
}

/* FUN_003505B0 @ 0x003505b0   (est. sk_assert_from_invalid)
 * assert-fail entry, prints " from invalid" via FUN_001a89a8 (s_from_invalid_005ce9c3)
 * Confidence: medium */
void sk_sys_05b0()
{
  sk_assert_msg(" from invalid", 14, 1);
}

/* FUN_003505C4 @ 0x003505c4   (est. sk_sys_stub_05c4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_05c4(void)
{
  /* no-op */
}

/* FUN_003505D0 @ 0x003505d0   (est. sk_sys_stub_05d0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_05d0(void)
{
  /* no-op */
}

/* FUN_003505DC @ 0x003505dc   (est. sk_sys_stub_05dc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_05dc(void)
{
  /* no-op */
}

/* FUN_003505E8 @ 0x003505e8   (est. sk_sys_stub_05e8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_05e8(void)
{
  /* no-op */
}

/* FUN_003505F4 @ 0x003505f4   (est. sk_sys_stub_05f4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_05f4(void)
{
  /* no-op */
}

/* FUN_00350600 @ 0x00350600   (est. sk_sys_stub_0600)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0600(void)
{
  /* no-op */
}

/* FUN_0035060C @ 0x0035060c   (est. sk_sys_stub_060c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_060c(void)
{
  /* no-op */
}

/* FUN_00350618 @ 0x00350618   (est. sk_sys_stub_0618)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0618(void)
{
  /* no-op */
}

/* FUN_00350624 @ 0x00350624   (est. sk_sys_stub_0624)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0624(void)
{
  /* no-op */
}

/* FUN_00350630 @ 0x00350630   (est. sk_sys_stub_0630)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0630(void)
{
  /* no-op */
}

/* FUN_0035063C @ 0x0035063c   (est. sk_sys_stub_063c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_063c(void)
{
  /* no-op */
}

/* FUN_00350648 @ 0x00350648   (est. sk_sys_stub_0648)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0648(void)
{
  /* no-op */
}

/* FUN_00350654 @ 0x00350654   (est. sk_sys_forward_08f728)
 * tail call FUN_0008f728
 * Confidence: medium */
void sk_sys_0654()
{
  sk_sys_dispatch_0008f728();
}

/* FUN_0035066C @ 0x0035066c   (est. sk_sys_stub_066c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_066c(void)
{
  /* no-op */
}

/* FUN_00350678 @ 0x00350678   (est. sk_sys_forward_31948c)
 * tail call FUN_0031948c
 * Confidence: medium */
void sk_sys_0678()
{
  sk_sys_dispatch_0031948c();
}

/* FUN_00350694 @ 0x00350694   (est. sk_sys_forward_310a74)
 * tail call FUN_00310a74
 * Confidence: medium */
void sk_sys_0694()
{
  sk_sys_dispatch_00310a74();
}

/* FUN_003506B0 @ 0x003506b0   (est. sk_sys_forward_0a68c4)
 * tail call FUN_000a68c4
 * Confidence: medium */
void sk_sys_06b0()
{
  sk_sys_dispatch_000a68c4();
}

/* FUN_003506CC @ 0x003506cc   (est. sk_sys_forward_310a74)
 * tail call FUN_00310a74
 * Confidence: medium */
void sk_sys_06cc()
{
  sk_sys_dispatch_00310a74();
}

/* FUN_003506E8 @ 0x003506e8   (est. sk_sys_forward_0277b8)
 * tail call FUN_000277b8
 * Confidence: medium */
void sk_sys_06e8()
{
  sk_sys_dispatch_000277b8();
}

/* FUN_00350704 @ 0x00350704   (est. sk_sys_forward_310924)
 * tail call FUN_00310924
 * Confidence: medium */
void sk_sys_0704()
{
  sk_sys_dispatch_00310924();
}

/* FUN_00350720 @ 0x00350720   (est. sk_sys_stub_0720)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0720(void)
{
  return 0;
}

/* FUN_0035072C @ 0x0035072c   (est. sk_sys_stub_072c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_072c(void)
{
  /* no-op */
}

/* FUN_00350738 @ 0x00350738   (est. sk_sys_stub_0738)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0738(void)
{
  /* no-op */
}

/* FUN_00350744 @ 0x00350744   (est. sk_sys_stub_0744)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0744(void)
{
  /* no-op */
}

/* FUN_00350750 @ 0x00350750   (est. sk_sys_stub_0750)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0750(void)
{
  /* no-op */
}

/* FUN_0035075C @ 0x0035075c   (est. sk_sys_stub_075c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_075c(void)
{
  /* no-op */
}

/* FUN_00350768 @ 0x00350768   (est. sk_sys_stub_0768)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0768(void)
{
  /* no-op */
}

/* FUN_00350774 @ 0x00350774   (est. sk_sys_stub_0774)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0774(void)
{
  /* no-op */
}

/* FUN_00350780 @ 0x00350780   (est. sk_sys_forward_027754)
 * tail call FUN_00027754
 * Confidence: medium */
void sk_sys_0780()
{
  sk_sys_dispatch_00027754();
}

/* FUN_00350798 @ 0x00350798   (est. sk_sys_stub_0798)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0798(void)
{
  return 0;
}

/* FUN_003507A4 @ 0x003507a4   (est. sk_sys_forward_310a44)
 * tail call FUN_00310a44
 * Confidence: medium */
void sk_sys_07a4()
{
  sk_sys_dispatch_00310a44();
}

/* FUN_003507BC @ 0x003507bc   (est. sk_sys_stub_07bc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07bc(void)
{
  /* no-op */
}

/* FUN_003507C8 @ 0x003507c8   (est. sk_sys_stub_07c8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07c8(void)
{
  /* no-op */
}

/* FUN_003507D4 @ 0x003507d4   (est. sk_sys_stub_07d4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07d4(void)
{
  /* no-op */
}

/* FUN_003507E0 @ 0x003507e0   (est. sk_sys_stub_07e0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07e0(void)
{
  /* no-op */
}

/* FUN_003507EC @ 0x003507ec   (est. sk_sys_stub_07ec)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07ec(void)
{
  /* no-op */
}

/* FUN_003507F8 @ 0x003507f8   (est. sk_sys_stub_07f8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_07f8(void)
{
  /* no-op */
}

/* FUN_00350804 @ 0x00350804   (est. sk_sys_stub_0804)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0804(void)
{
  /* no-op */
}

/* FUN_00350810 @ 0x00350810   (est. sk_sys_stub_0810)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0810(void)
{
  /* no-op */
}

/* FUN_0035081C @ 0x0035081c   (est. sk_syscall_table_4e984c)
 * returns address of syscall table DAT_004e984c (near name tables @0x4e3240)
 * Confidence: medium */
word_t *sk_sys_081c()
{
  return sk_syscall_table_4e984c;
}

/* FUN_00350834 @ 0x00350834   (est. sk_syscall_table_4e9518)
 * returns address of syscall table DAT_004e9518 (near name tables @0x4e3240)
 * Confidence: medium */
word_t *sk_sys_0834()
{
  return sk_syscall_table_4e9518;
}

/* FUN_0035084C @ 0x0035084c   (est. sk_sys_stub_084c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_084c(void)
{
  /* no-op */
}

/* FUN_00350858 @ 0x00350858   (est. sk_sys_stub_0858)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0858(void)
{
  /* no-op */
}

/* FUN_00350868 @ 0x00350868   (est. sk_sys_stub_0868)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0868(void)
{
  /* no-op */
}

/* FUN_00350878 @ 0x00350878   (est. sk_sys_stub_0878)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0878(void)
{
  /* no-op */
}

/* FUN_00350884 @ 0x00350884   (est. sk_sys_forward_0839f8)
 * tail call FUN_000839f8
 * Confidence: medium */
void sk_sys_0884()
{
  sk_sys_dispatch_000839f8();
}

/* FUN_0035089C @ 0x0035089c   (est. sk_sys_stub_089c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_089c(void)
{
  /* no-op */
}

/* FUN_003508A8 @ 0x003508a8   (est. sk_sys_stub_08a8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08a8(void)
{
  /* no-op */
}

/* FUN_003508B4 @ 0x003508b4   (est. sk_sys_stub_08b4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08b4(void)
{
  /* no-op */
}

/* FUN_003508C0 @ 0x003508c0   (est. sk_sys_stub_08c0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08c0(void)
{
  /* no-op */
}

/* FUN_003508CC @ 0x003508cc   (est. sk_sys_stub_08cc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08cc(void)
{
  /* no-op */
}

/* FUN_003508D8 @ 0x003508d8   (est. sk_sys_stub_08d8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08d8(void)
{
  /* no-op */
}

/* FUN_003508E4 @ 0x003508e4   (est. sk_sys_stub_08e4)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_08e4(void)
{
  return 0;
}

/* FUN_003508F0 @ 0x003508f0   (est. sk_sys_stub_08f0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08f0(void)
{
  /* no-op */
}

/* FUN_003508FC @ 0x003508fc   (est. sk_sys_stub_08fc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_08fc(void)
{
  /* no-op */
}

/* FUN_00350908 @ 0x00350908   (est. sk_sys_stub_0908)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0908(void)
{
  return 0;
}

/* FUN_00350914 @ 0x00350914   (est. sk_sys_stub_0914)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0914(void)
{
  /* no-op */
}

/* FUN_00350920 @ 0x00350920   (est. sk_sys_stub_0920)
 * No-op syscall handler slot returning 0 (unimplemented).
 * Confidence: medium */
word_t sk_sys_0920(void)
{
  return 0;
}

/* FUN_0035092C @ 0x0035092c   (est. sk_sys_stub_092c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_092c(void)
{
  /* no-op */
}

/* FUN_00350938 @ 0x00350938   (est. sk_sys_stub_0938)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0938(void)
{
  /* no-op */
}

/* FUN_00350944 @ 0x00350944   (est. sk_sys_stub_0944)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0944(void)
{
  /* no-op */
}

/* FUN_00350950 @ 0x00350950   (est. sk_sys_forward_027754)
 * tail call FUN_00027754
 * Confidence: medium */
void sk_sys_0950()
{
  sk_sys_dispatch_00027754();
}

/* FUN_00350968 @ 0x00350968   (est. sk_sys_stub_0968)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0968(void)
{
  /* no-op */
}

/* FUN_00350974 @ 0x00350974   (est. sk_sys_stub_0974)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0974(void)
{
  /* no-op */
}

/* FUN_00350980 @ 0x00350980   (est. sk_sys_stub_0980)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0980(void)
{
  /* no-op */
}

/* FUN_0035098C @ 0x0035098c   (est. sk_sys_stub_098c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_098c(void)
{
  /* no-op */
}

/* FUN_00350998 @ 0x00350998   (est. sk_sys_stub_0998)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0998(void)
{
  /* no-op */
}

/* FUN_003509A4 @ 0x003509a4   (est. sk_frame_spill)
 * spills arg to base-0x100 (Ghidra *(in_x9-0x100)=arg)
 * Confidence: medium */
void sk_sys_09a4(word_t arg, word_t *base)
{
  base[-32] = arg;  /* x9-0x100 */
}

/* FUN_003509B0 @ 0x003509b0   (est. sk_sys_stub_09b0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09b0(void)
{
  /* no-op */
}

/* FUN_003509BC @ 0x003509bc   (est. sk_sys_stub_09bc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09bc(void)
{
  /* no-op */
}

/* FUN_003509C8 @ 0x003509c8   (est. sk_sys_stub_09c8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09c8(void)
{
  /* no-op */
}

/* FUN_003509D4 @ 0x003509d4   (est. sk_sys_stub_09d4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09d4(void)
{
  /* no-op */
}

/* FUN_003509E0 @ 0x003509e0   (est. sk_sys_stub_09e0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09e0(void)
{
  /* no-op */
}

/* FUN_003509EC @ 0x003509ec   (est. sk_sys_stub_09ec)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09ec(void)
{
  /* no-op */
}

/* FUN_003509F8 @ 0x003509f8   (est. sk_sys_stub_09f8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_09f8(void)
{
  /* no-op */
}

/* FUN_00350A04 @ 0x00350a04   (est. sk_sys_stub_0a04)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a04(void)
{
  /* no-op */
}

/* FUN_00350A10 @ 0x00350a10   (est. sk_sys_stub_0a10)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a10(void)
{
  /* no-op */
}

/* FUN_00350A1C @ 0x00350a1c   (est. sk_sys_stub_0a1c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a1c(void)
{
  /* no-op */
}

/* FUN_00350A28 @ 0x00350a28   (est. sk_sys_stub_0a28)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a28(void)
{
  /* no-op */
}

/* FUN_00350A34 @ 0x00350a34   (est. sk_sys_stub_0a34)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a34(void)
{
  /* no-op */
}

/* FUN_00350A40 @ 0x00350a40   (est. sk_sys_stub_0a40)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a40(void)
{
  /* no-op */
}

/* FUN_00350A4C @ 0x00350a4c   (est. sk_sys_forward_310a74)
 * tail call FUN_00310a74
 * Confidence: medium */
void sk_sys_0a4c()
{
  sk_sys_dispatch_00310a74();
}

/* FUN_00350A64 @ 0x00350a64   (est. sk_make_pair)
 * builds 128-bit pair, value in high half (Ghidra auVar1 << 0x40)
 * Confidence: medium */
cl4_pair_t sk_sys_0a64(word_t param_1, word_t param_2, word_t param_3)
{
  return (cl4_pair_t){ .lo = 0, .hi = param_3 };
}

/* FUN_00350A70 @ 0x00350a70   (est. sk_sys_stub_0a70)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a70(void)
{
  /* no-op */
}

/* FUN_00350A7C @ 0x00350a7c   (est. sk_sys_stub_0a7c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a7c(void)
{
  /* no-op */
}

/* FUN_00350A88 @ 0x00350a88   (est. sk_sys_stub_0a88)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a88(void)
{
  /* no-op */
}

/* FUN_00350A94 @ 0x00350a94   (est. sk_sys_stub_0a94)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0a94(void)
{
  /* no-op */
}

/* FUN_00350AA0 @ 0x00350aa0   (est. sk_sys_stub_0aa0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0aa0(void)
{
  /* no-op */
}

/* FUN_00350AAC @ 0x00350aac   (est. sk_sys_stub_0aac)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0aac(void)
{
  /* no-op */
}

/* FUN_00350AB8 @ 0x00350ab8   (est. sk_sys_stub_0ab8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0ab8(void)
{
  /* no-op */
}

/* FUN_00350AC4 @ 0x00350ac4   (est. sk_sys_stub_0ac4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0ac4(void)
{
  /* no-op */
}

/* FUN_00350AD0 @ 0x00350ad0   (est. sk_sys_stub_0ad0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0ad0(void)
{
  /* no-op */
}

/* FUN_00350ADC @ 0x00350adc   (est. sk_sys_forward_14ae44)
 * tail call FUN_0014ae44
 * Confidence: medium */
void sk_sys_0adc()
{
  sk_sys_dispatch_0014ae44();
}

/* FUN_00350AF4 @ 0x00350af4   (est. sk_sys_stub_0af4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0af4(void)
{
  /* no-op */
}

/* FUN_00350B00 @ 0x00350b00   (est. sk_sys_stub_0b00)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b00(void)
{
  /* no-op */
}

/* FUN_00350B0C @ 0x00350b0c   (est. sk_sys_stub_0b0c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b0c(void)
{
  /* no-op */
}

/* FUN_00350B18 @ 0x00350b18   (est. sk_sys_stub_0b18)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b18(void)
{
  /* no-op */
}

/* FUN_00350B24 @ 0x00350b24   (est. sk_sys_stub_0b24)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b24(void)
{
  /* no-op */
}

/* FUN_00350B30 @ 0x00350b30   (est. sk_sys_stub_0b30)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b30(void)
{
  /* no-op */
}

/* FUN_00350B3C @ 0x00350b3c   (est. sk_sys_stub_0b3c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b3c(void)
{
  /* no-op */
}

/* FUN_00350B48 @ 0x00350b48   (est. sk_sys_stub_0b48)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b48(void)
{
  /* no-op */
}

/* FUN_00350B54 @ 0x00350b54   (est. sk_sys_stub_0b54)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b54(void)
{
  /* no-op */
}

/* FUN_00350B60 @ 0x00350b60   (est. sk_sys_stub_0b60)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b60(void)
{
  /* no-op */
}

/* FUN_00350B6C @ 0x00350b6c   (est. sk_sys_stub_0b6c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b6c(void)
{
  /* no-op */
}

/* FUN_00350B78 @ 0x00350b78   (est. sk_sys_stub_0b78)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b78(void)
{
  /* no-op */
}

/* FUN_00350B84 @ 0x00350b84   (est. sk_sys_stub_0b84)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b84(void)
{
  /* no-op */
}

/* FUN_00350B90 @ 0x00350b90   (est. sk_sys_stub_0b90)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b90(void)
{
  /* no-op */
}

/* FUN_00350B9C @ 0x00350b9c   (est. sk_sys_stub_0b9c)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0b9c(void)
{
  /* no-op */
}

/* FUN_00350BA8 @ 0x00350ba8   (est. sk_sys_stub_0ba8)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0ba8(void)
{
  /* no-op */
}

/* FUN_00350BB4 @ 0x00350bb4   (est. sk_sys_stub_0bb4)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0bb4(void)
{
  /* no-op */
}

/* FUN_00350BC0 @ 0x00350bc0   (est. sk_sys_stub_0bc0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0bc0(void)
{
  /* no-op */
}

/* FUN_00350BCC @ 0x00350bcc   (est. sk_sys_stub_0bcc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0bcc(void)
{
  /* no-op */
}

/* FUN_00350BD8 @ 0x00350bd8   (est. sk_sys_forward_027754)
 * tail call FUN_00027754
 * Confidence: medium */
void sk_sys_0bd8()
{
  sk_sys_dispatch_00027754();
}

/* FUN_00350BF0 @ 0x00350bf0   (est. sk_sys_stub_0bf0)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0bf0(void)
{
  /* no-op */
}

/* FUN_00350BFC @ 0x00350bfc   (est. sk_sys_stub_0bfc)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0bfc(void)
{
  /* no-op */
}

/* FUN_00350C08 @ 0x00350c08   (est. sk_sys_stub_0c08)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0c08(void)
{
  /* no-op */
}

/* FUN_00350C14 @ 0x00350c14   (est. sk_sys_stub_0c14)
 * Empty syscall/exception handler slot (no-op; unimplemented entry).
 * Confidence: medium */
void sk_sys_0c14(void)
{
  /* no-op */
}
