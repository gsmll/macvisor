/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 25: 0x35667c-0x357424 syscall/exception-entry region.
 * This region is a dense run of small syscall/exception-entry handlers,
 * frame-slot accessors (read/write a caller's saved register frame), dispatch
 * table getters, and user-error emitters. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern void sk_helper_839f8(void);            /* FUN_000839f8 */
extern void sk_helper_16796c(void);           /* FUN_0016796c */
extern void sk_helper_365b6c(void);           /* FUN_00365b6c */
extern void sk_helper_27754(void);            /* FUN_00027754 */
extern void sk_helper_2a4c98(uint64_t a, uint64_t b, uint64_t c); /* FUN_002a4c98 */
extern void sk_helper_1a1138(const void *p);  /* FUN_001a1138 */
extern void sk_helper_310d68(void);           /* FUN_00310d68 */
extern void sk_helper_310ea4(void);           /* FUN_00310ea4 */
extern void sk_helper_3722e4(void);           /* FUN_003722e4 */
extern void sk_helper_36b270(void);           /* FUN_0036b270 */
extern void sk_helper_312d08(void *a, void *b, void *c,
                             uint64_t d, uint64_t e, uint64_t f, uint64_t g); /* FUN_00312d08 */
extern void sk_helper_31e874(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                             uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7); /* FUN_0031e874 */

/* Resolve/cache a kernel name string from a (pointer,length) table. FUN_00002534 */
extern void sk_resolve_string(uint64_t cache_slot, const void *table);
/* Emit a user error / exception header built from (message, length, flag).
 * FUN_001a89a8 — returns the encoded error register. */
extern uint64_t sk_user_error(const char *msg, uint64_t len, uint32_t flag);
/* Noreturn panic path. FUN_001afa84 */
extern void sk_panic_path(void) __attribute__((noreturn));

/* Named read-only string / dispatch tables referenced by this region. */
extern const unsigned char sk_tab_5d3bb7[];   /* &DAT_005d3bb7 (string) */
extern const unsigned char sk_tab_4e83ac[];   /* &DAT_004e83ac (dispatch table) */
extern const unsigned char sk_tab_4ec600[];   /* &DAT_004ec600 */
extern const unsigned char sk_tab_4ec5e4[];   /* &DAT_004ec5e4 */
extern const unsigned char sk_tab_4e9830[];   /* &DAT_004e9830 */
extern const unsigned char sk_tab_4e97c0[];   /* &DAT_004e97c0 */
extern const unsigned char sk_tab_4e9550[];   /* &DAT_004e9550 */
extern const unsigned char sk_tab_4e8454[];   /* &DAT_004e8454 */
extern const unsigned char sk_tab_4e83e4[];   /* &DAT_004e83e4 */
extern const unsigned char sk_tab_4e7f88[];   /* &DAT_004e7f88 (name table) */
extern const unsigned char sk_tab_4e8010[];   /* &DAT_004e8010 */
extern const unsigned char sk_tab_4e8008[];   /* &DAT_004e8008 */
extern const unsigned char sk_tab_4e8000[];   /* &DAT_004e8000 */
extern const unsigned char sk_tab_4e7ff8[];   /* &DAT_004e7ff8 */
extern const unsigned char sk_tab_4e7ff0[];   /* &DAT_004e7ff0 */
extern const unsigned char sk_tab_4e7fb0[];   /* &DAT_004e7fb0 */
extern const unsigned char sk_tab_4e8070[];   /* &DAT_004e8070 */
extern const unsigned char sk_tab_4e8040[];   /* &DAT_004e8040 */

/* ------------------------------------------------------------------ *
 * Slice 25 functions (ascending address order).
 * Many bodies use "unaff_" (incoming) registers/stack slots because they are
 * short tail fragments of a larger inlined syscall dispatcher. Those incoming
 * register values are modeled as leading parameters named xN (arm64 regs);
 * the Ghidra "unaff_" names are preserved in comments.
 * ------------------------------------------------------------------ */

/* FUN_0035667c @ 0x0035667c  (est. sk_store_word_35667c)
 * Tail fragment: store an incoming word register through a pointer in x19.
 * Confidence: medium */
void sk_store_word_35667c(uint64_t x19, uint64_t x23)
{
    /* [Ghidra: unaff_x19 / unaff_w23] */
    *(uint32_t *)x19 = (uint32_t)x23;
}

/* FUN_00356688 @ 0x00356688  (est. sk_syscall_stub_356688)
 * Empty handler — no-op syscall/exception entry slot. Confidence: medium */
void sk_syscall_stub_356688(void)
{
    return;
}

/* FUN_00356694 @ 0x00356694  (est. sk_syscall_stub_356694)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356694(void)
{
    return;
}

/* FUN_003566b4 @ 0x003566b4  (est. sk_syscall_stub_3566b4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3566b4(void)
{
    return;
}

/* FUN_003566c0 @ 0x003566c0  (est. sk_frame_pair_3566c0)
 * Returns a 16-byte pair read from the caller frame (x29-0xd8, x29-0x78).
 * Confidence: medium */
cl4_result_t sk_frame_pair_3566c0(uint64_t x29)
{
    cl4_result_t r;
    r.lo = *(uint64_t *)(x29 - 0xd8); /* [Ghidra: auVar1._0_8_] */
    r.hi = *(uint64_t *)(x29 - 0x78); /* [Ghidra: auVar1._8_8_] */
    return r;
}

/* FUN_003566cc @ 0x003566cc  (est. sk_copy_word8_3566cc)
 * Tail fragment: copy an 8-byte word at (x19+8) to (x20+8). Confidence: medium */
void sk_copy_word8_3566cc(uint64_t x19, uint64_t x20)
{
    *(uint64_t *)(x20 + 8) = *(uint64_t *)(x19 + 8); /* [Ghidra: unaff_x19/unaff_x20] */
}

/* FUN_003566d8 @ 0x003566d8  (est. sk_syscall_stub_3566d8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3566d8(void)
{
    return;
}

/* FUN_003566e4 @ 0x003566e4  (est. sk_syscall_stub_3566e4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3566e4(void)
{
    return;
}

/* FUN_00356704 @ 0x00356704  (est. sk_syscall_stub_356704)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356704(void)
{
    return;
}

/* FUN_00356710 @ 0x00356710  (est. sk_syscall_stub_356710)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356710(void)
{
    return;
}

/* FUN_00356730 @ 0x00356730  (est. sk_init_flag_356730)
 * Tail fragment: clear a word at x20 and set a byte flag (value 1) after it.
 * Confidence: medium */
void sk_init_flag_356730(uint64_t x20)
{
    *(uint64_t *)x20 = 0;                 /* [Ghidra: *unaff_x20] */
    *(uint8_t *)(x20 + 8) = 1;            /* [Ghidra: *(unaff_x20+1) as byte] */
}

/* FUN_00356750 @ 0x00356750  (est. sk_syscall_stub_356750)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356750(void)
{
    return;
}

/* FUN_0035675c @ 0x0035675c  (est. sk_syscall_stub_35675c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35675c(void)
{
    return;
}

/* FUN_00356768 @ 0x00356768  (est. sk_syscall_stub_356768)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356768(void)
{
    return;
}

/* FUN_00356774 @ 0x00356774  (est. sk_syscall_stub_356774)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356774(void)
{
    return;
}

/* FUN_00356780 @ 0x00356780  (est. sk_frame_read_356780)
 * Reads an 8-byte word from the caller frame at (x10 - 0x100). Confidence: medium */
uint64_t sk_frame_read_356780(uint64_t in_x10)
{
    return *(uint64_t *)(in_x10 - 0x100); /* [Ghidra: in_x10 - 0x100] */
}

/* FUN_0035678c @ 0x0035678c  (est. sk_frame_write_35678c)
 * Writes an incoming word (x24) into the caller frame at x29-0x118. Confidence: medium */
void sk_frame_write_35678c(uint64_t x29, uint64_t x24)
{
    *(uint64_t *)(x29 - 0x118) = x24; /* [Ghidra: unaff_x24 / unaff_x29] */
}

/* FUN_00356798 @ 0x00356798  (est. sk_syscall_stub_356798)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356798(void)
{
    return;
}

/* FUN_003567a4 @ 0x003567a4  (est. sk_syscall_stub_3567a4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3567a4(void)
{
    return;
}

/* FUN_003567b0 @ 0x003567b0  (est. sk_frame_read_3567b0)
 * Reads an 8-byte word from the caller frame at x29-0x68. Confidence: medium */
uint64_t sk_frame_read_3567b0(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x68);
}

/* FUN_003567bc @ 0x003567bc  (est. sk_frame_read_3567bc)
 * Reads an 8-byte word from the caller frame at x29-0x68. Confidence: medium */
uint64_t sk_frame_read_3567bc(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x68);
}

/* FUN_003567c8 @ 0x003567c8  (est. sk_syscall_stub_3567c8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3567c8(void)
{
    return;
}

/* FUN_003567d4 @ 0x003567d4  (est. sk_syscall_stub_3567d4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3567d4(void)
{
    return;
}

/* FUN_003567e0 @ 0x003567e0  (est. sk_syscall_stub_3567e0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3567e0(void)
{
    return;
}

/* FUN_003567ec @ 0x003567ec  (est. sk_syscall_stub_3567ec)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3567ec(void)
{
    return;
}

/* FUN_003567f8 @ 0x003567f8  (est. sk_string_5d3bb7_3567f8)
 * Returns a pointer to a read-only string at 0x5d3bb7. Confidence: medium */
const void *sk_string_5d3bb7_3567f8(void)
{
    return (const void *)sk_tab_5d3bb7; /* [Ghidra: &DAT_005d3bb7] */
}

/* FUN_00356804 @ 0x00356804  (est. sk_const_zero_356804)
 * Returns constant 0. Confidence: medium */
uint64_t sk_const_zero_356804(void)
{
    return 0;
}

/* FUN_00356810 @ 0x00356810  (est. sk_frame_read_356810)
 * Reads an 8-byte word from the caller frame at x29-0x90. Confidence: medium */
uint64_t sk_frame_read_356810(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x90);
}

/* FUN_0035681c @ 0x0035681c  (est. sk_tail_839f8_35681c)
 * Tail call to helper FUN_000839f8. Confidence: medium */
void sk_tail_839f8_35681c(void)
{
    sk_helper_839f8();
}

/* FUN_00356834 @ 0x00356834  (est. sk_frame_hi_word_356834)
 * Returns a 16-byte pair whose high word is *(param_2+0x10); low word is 0.
 * (The decompiler shifts the assembled pair left by 0x40.) Confidence: medium */
cl4_result_t sk_frame_hi_word_356834(uint64_t param_1, uint64_t param_2)
{
    (void)param_1;
    cl4_result_t r;
    r.lo = 0;                                     /* [Ghidra: auVar1._8_8_ = 0, << 0x40] */
    r.hi = *(uint64_t *)(param_2 + 0x10);         /* [Ghidra: auVar1._0_8_ = *(param_2+0x10)] */
    return r;
}

/* FUN_00356840 @ 0x00356840  (est. sk_syscall_stub_356840)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356840(void)
{
    return;
}

/* FUN_0035684c @ 0x0035684c  (est. sk_frame_read_35684c)
 * Reads an 8-byte word from the caller frame at x29-0x60. Confidence: medium */
uint64_t sk_frame_read_35684c(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x60);
}

/* FUN_00356858 @ 0x00356858  (est. sk_frame_addr_356858)
 * Returns the caller frame address x29-0x78. Confidence: medium */
uint64_t sk_frame_addr_356858(uint64_t x29)
{
    return x29 - 0x78;
}

/* FUN_00356864 @ 0x00356864  (est. sk_frame_addr_356864)
 * Returns the caller frame address x29-0x78. Confidence: medium */
uint64_t sk_frame_addr_356864(uint64_t x29)
{
    return x29 - 0x78;
}

/* FUN_00356870 @ 0x00356870  (est. sk_syscall_stub_356870)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356870(void)
{
    return;
}

/* FUN_0035687c @ 0x0035687c  (est. sk_mask_bit0_35687c)
 * Returns the low bit (bit 0) of the incoming word register w20. Confidence: medium */
uint32_t sk_mask_bit0_35687c(uint64_t x20)
{
    return (uint32_t)x20 & 1u; /* [Ghidra: unaff_w20 & 1] */
}

/* FUN_00356888 @ 0x00356888  (est. sk_syscall_stub_356888)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356888(void)
{
    return;
}

/* FUN_003568a8 @ 0x003568a8  (est. sk_syscall_stub_3568a8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3568a8(void)
{
    return;
}

/* FUN_003568c8 @ 0x003568c8  (est. sk_syscall_stub_3568c8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3568c8(void)
{
    return;
}

/* FUN_003568e8 @ 0x003568e8  (est. sk_frame_read_3568e8)
 * Reads an 8-byte word from the caller frame at x29-0x90. Confidence: medium */
uint64_t sk_frame_read_3568e8(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x90);
}

/* FUN_003568f4 @ 0x003568f4  (est. sk_syscall_stub_3568f4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3568f4(void)
{
    return;
}

/* FUN_00356900 @ 0x00356900  (est. sk_syscall_stub_356900)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356900(void)
{
    return;
}

/* FUN_0035690c @ 0x0035690c  (est. sk_tail_16796c_35690c)
 * Tail call to helper FUN_0016796c. Confidence: medium */
void sk_tail_16796c_35690c(void)
{
    sk_helper_16796c();
}

/* FUN_00356924 @ 0x00356924  (est. sk_frame_read_356924)
 * Reads an 8-byte word from the caller frame at x29-0xb0. Confidence: medium */
uint64_t sk_frame_read_356924(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0xb0);
}

/* FUN_00356930 @ 0x00356930  (est. sk_syscall_stub_356930)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356930(void)
{
    return;
}

/* FUN_00356940 @ 0x00356940  (est. sk_syscall_stub_356940)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356940(void)
{
    return;
}

/* FUN_0035694c @ 0x0035694c  (est. sk_syscall_stub_35694c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35694c(void)
{
    return;
}

/* FUN_00356958 @ 0x00356958  (est. sk_syscall_stub_356958)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356958(void)
{
    return;
}

/* FUN_00356964 @ 0x00356964  (est. sk_frame_read_356964)
 * Reads an 8-byte word from the caller frame at x29-0xd0. Confidence: medium */
uint64_t sk_frame_read_356964(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0xd0);
}

/* FUN_00356970 @ 0x00356970  (est. sk_syscall_stub_356970)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356970(void)
{
    return;
}

/* FUN_0035697c @ 0x0035697c  (est. sk_identity2_35697c)
 * Returns its second argument unchanged. Confidence: medium */
uint64_t sk_identity2_35697c(uint64_t param_1, uint64_t param_2)
{
    (void)param_1;
    return param_2;
}

/* FUN_00356988 @ 0x00356988  (est. sk_deref_x20_356988)
 * Returns the 8-byte word pointed to by x20. Confidence: medium */
uint64_t sk_deref_x20_356988(uint64_t x20)
{
    return *(uint64_t *)x20; /* [Ghidra: *unaff_x20] */
}

/* FUN_00356994 @ 0x00356994  (est. sk_syscall_stub_356994)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356994(void)
{
    return;
}

/* FUN_003569b4 @ 0x003569b4  (est. sk_syscall_stub_3569b4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3569b4(void)
{
    return;
}

/* FUN_003569c0 @ 0x003569c0  (est. sk_frame_addr_3569c0)
 * Returns the caller frame address x29-0x58. Confidence: medium */
uint64_t sk_frame_addr_3569c0(uint64_t x29)
{
    return x29 - 0x58;
}

/* FUN_003569cc @ 0x003569cc  (est. sk_frame_addr_3569cc)
 * Returns the caller frame address x29-0x60. Confidence: medium */
uint64_t sk_frame_addr_3569cc(uint64_t x29)
{
    return x29 - 0x60;
}

/* FUN_003569d8 @ 0x003569d8  (est. sk_frame_read_3569d8)
 * Reads an 8-byte word from the caller frame at x29-0x80. Confidence: medium */
uint64_t sk_frame_read_3569d8(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x80);
}

/* FUN_003569e4 @ 0x003569e4  (est. sk_syscall_stub_3569e4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3569e4(void)
{
    return;
}

/* FUN_003569f0 @ 0x003569f0  (est. sk_syscall_stub_3569f0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3569f0(void)
{
    return;
}

/* FUN_003569fc @ 0x003569fc  (est. sk_syscall_stub_3569fc)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3569fc(void)
{
    return;
}

/* FUN_00356a08 @ 0x00356a08  (est. sk_syscall_stub_356a08)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a08(void)
{
    return;
}

/* FUN_00356a14 @ 0x00356a14  (est. sk_syscall_stub_356a14)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a14(void)
{
    return;
}

/* FUN_00356a20 @ 0x00356a20  (est. sk_syscall_stub_356a20)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a20(void)
{
    return;
}

/* FUN_00356a2c @ 0x00356a2c  (est. sk_syscall_stub_356a2c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a2c(void)
{
    return;
}

/* FUN_00356a38 @ 0x00356a38  (est. sk_syscall_stub_356a38)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a38(void)
{
    return;
}

/* FUN_00356a44 @ 0x00356a44  (est. sk_syscall_stub_356a44)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a44(void)
{
    return;
}

/* FUN_00356a50 @ 0x00356a50  (est. sk_syscall_stub_356a50)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a50(void)
{
    return;
}

/* FUN_00356a70 @ 0x00356a70  (est. sk_syscall_stub_356a70)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a70(void)
{
    return;
}

/* FUN_00356a7c @ 0x00356a7c  (est. sk_frame_read_356a7c)
 * Reads an 8-byte word from the caller frame at x29-0x90. Confidence: medium */
uint64_t sk_frame_read_356a7c(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x90);
}

/* FUN_00356a88 @ 0x00356a88  (est. sk_frame_read_356a88)
 * Reads an 8-byte word from the caller frame at x29-0x88. Confidence: medium */
uint64_t sk_frame_read_356a88(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x88);
}

/* FUN_00356a94 @ 0x00356a94  (est. sk_syscall_stub_356a94)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356a94(void)
{
    return;
}

/* FUN_00356aa0 @ 0x00356aa0  (est. sk_syscall_stub_356aa0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356aa0(void)
{
    return;
}

/* FUN_00356aac @ 0x00356aac  (est. sk_syscall_stub_356aac)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356aac(void)
{
    return;
}

/* FUN_00356ab8 @ 0x00356ab8  (est. sk_syscall_stub_356ab8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356ab8(void)
{
    return;
}

/* FUN_00356ac4 @ 0x00356ac4  (est. sk_syscall_stub_356ac4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356ac4(void)
{
    return;
}

/* FUN_00356ad0 @ 0x00356ad0  (est. sk_syscall_stub_356ad0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356ad0(void)
{
    return;
}

/* FUN_00356adc @ 0x00356adc  (est. sk_syscall_stub_356adc)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356adc(void)
{
    return;
}

/* FUN_00356ae8 @ 0x00356ae8  (est. sk_syscall_stub_356ae8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356ae8(void)
{
    return;
}

/* FUN_00356af4 @ 0x00356af4  (est. sk_frame_read_356af4)
 * Reads an 8-byte word from the caller frame at x29-0x78. Confidence: medium */
uint64_t sk_frame_read_356af4(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x78);
}

/* FUN_00356b00 @ 0x00356b00  (est. sk_syscall_stub_356b00)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b00(void)
{
    return;
}

/* FUN_00356b20 @ 0x00356b20  (est. sk_frame_read_356b20)
 * Reads an 8-byte word from the caller frame at x29-0x70. Confidence: medium */
uint64_t sk_frame_read_356b20(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x70);
}

/* FUN_00356b2c @ 0x00356b2c  (est. sk_tail_365b6c_356b2c)
 * Tail call to helper FUN_00365b6c. Confidence: medium */
void sk_tail_365b6c_356b2c(void)
{
    sk_helper_365b6c();
}

/* FUN_00356b38 @ 0x00356b38  (est. sk_syscall_stub_356b38)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b38(void)
{
    return;
}

/* FUN_00356b44 @ 0x00356b44  (est. sk_syscall_stub_356b44)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b44(void)
{
    return;
}

/* FUN_00356b50 @ 0x00356b50  (est. sk_syscall_stub_356b50)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b50(void)
{
    return;
}

/* FUN_00356b5c @ 0x00356b5c  (est. sk_syscall_stub_356b5c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b5c(void)
{
    return;
}

/* FUN_00356b68 @ 0x00356b68  (est. sk_syscall_stub_356b68)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b68(void)
{
    return;
}

/* FUN_00356b74 @ 0x00356b74  (est. sk_syscall_stub_356b74)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b74(void)
{
    return;
}

/* FUN_00356b80 @ 0x00356b80  (est. sk_syscall_stub_356b80)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b80(void)
{
    return;
}

/* FUN_00356b8c @ 0x00356b8c  (est. sk_syscall_stub_356b8c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b8c(void)
{
    return;
}

/* FUN_00356b98 @ 0x00356b98  (est. sk_syscall_stub_356b98)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356b98(void)
{
    return;
}

/* FUN_00356ba4 @ 0x00356ba4  (est. sk_syscall_stub_356ba4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356ba4(void)
{
    return;
}

/* FUN_00356bb0 @ 0x00356bb0  (est. sk_tail_27754_356bb0)
 * Tail call to helper FUN_00027754. Confidence: medium */
void sk_tail_27754_356bb0(void)
{
    sk_helper_27754();
}

/* FUN_00356bc8 @ 0x00356bc8  (est. sk_syscall_stub_356bc8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356bc8(void)
{
    return;
}

/* FUN_00356bd4 @ 0x00356bd4  (est. sk_const_0xff_356bd4)
 * Returns constant 0xff (255). Confidence: medium */
uint64_t sk_const_0xff_356bd4(void)
{
    return 0xff;
}

/* FUN_00356be0 @ 0x00356be0  (est. sk_frame_read_356be0)
 * Reads an 8-byte word from the caller frame at x29-0xe8. Confidence: medium */
uint64_t sk_frame_read_356be0(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0xe8);
}

/* FUN_00356bec @ 0x00356bec  (est. sk_syscall_stub_356bec)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356bec(void)
{
    return;
}

/* FUN_00356bf8 @ 0x00356bf8  (est. sk_stack_ptr_356bf8)
 * Returns a pointer into the incoming stack frame (sp+0x30). Confidence: medium */
void *sk_stack_ptr_356bf8(void)
{
    return (void *)((uint8_t *)__builtin_frame_address(0) + 0x30); /* [Ghidra: &stack0x30] */
}

/* FUN_00356c18 @ 0x00356c18  (est. sk_deref_x20_356c18)
 * Returns the 8-byte word pointed to by x20. Confidence: medium */
uint64_t sk_deref_x20_356c18(uint64_t x20)
{
    return *(uint64_t *)x20; /* [Ghidra: *unaff_x20] */
}

/* FUN_00356c24 @ 0x00356c24  (est. sk_frame_read_356c24)
 * Reads an 8-byte word from the caller frame at x29-0x70. Confidence: medium */
uint64_t sk_frame_read_356c24(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x70);
}

/* FUN_00356c30 @ 0x00356c30  (est. sk_syscall_stub_356c30)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c30(void)
{
    return;
}

/* FUN_00356c3c @ 0x00356c3c  (est. sk_syscall_stub_356c3c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c3c(void)
{
    return;
}

/* FUN_00356c48 @ 0x00356c48  (est. sk_syscall_stub_356c48)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c48(void)
{
    return;
}

/* FUN_00356c54 @ 0x00356c54  (est. sk_syscall_stub_356c54)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c54(void)
{
    return;
}

/* FUN_00356c60 @ 0x00356c60  (est. sk_syscall_stub_356c60)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c60(void)
{
    return;
}

/* FUN_00356c6c @ 0x00356c6c  (est. sk_syscall_stub_356c6c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c6c(void)
{
    return;
}

/* FUN_00356c78 @ 0x00356c78  (est. sk_syscall_stub_356c78)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c78(void)
{
    return;
}

/* FUN_00356c84 @ 0x00356c84  (est. sk_syscall_stub_356c84)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356c84(void)
{
    return;
}

/* FUN_00356c90 @ 0x00356c90  (est. sk_slot_array_insert)
 * Insert a 5-word record (40 bytes) from param_1 into the slot array owned by
 * param_3 at index param_2, and set the corresponding occupancy bit in the
 * array's bitmap. The bitmap word is at (param_3+0x38) plus the word index
 * (param_2>>6)*8; the record base pointer is *(param_3+0x30) with stride 0x28.
 * This mirrors a seL4/cL4 capability/object slot-array insert.
 * Confidence: medium */
void sk_slot_array_insert(uint64_t *param_1, uint64_t param_2, uint64_t param_3)
{
    /* Set occupancy bit for index param_2. */
    uint64_t *bitmap = (uint64_t *)(param_3 + 0x38 + (param_2 >> 6) * 8);
    *bitmap |= 1ULL << (param_2 & 0x3f);

    /* Copy the 5-word record into the slot at base + index*0x28. */
    uint64_t *dst = (uint64_t *)(*(uint64_t *)(param_3 + 0x30) + param_2 * 0x28);
    dst[0] = param_1[0];
    dst[1] = param_1[1];
    dst[2] = param_1[2];
    dst[3] = param_1[3];
    dst[4] = param_1[4];
}

/* FUN_00356cd4 @ 0x00356cd4  (est. sk_tail_2a4c98_356cd4)
 * Tail call helper FUN_002a4c98(param_1, param_2, 0). Confidence: medium */
void sk_tail_2a4c98_356cd4(uint64_t param_1, uint64_t param_2)
{
    sk_helper_2a4c98(param_1, param_2, 0);
}

/* FUN_00356ce0 @ 0x00356ce0  (est. sk_tail_27754_x2_356ce0)
 * Calls helper FUN_00027754 twice (paired teardown/reset path). Confidence: medium */
void sk_tail_27754_x2_356ce0(void)
{
    sk_helper_27754();
    sk_helper_27754();
}

/* FUN_00356cfc @ 0x00356cfc  (est. sk_tail_1a1138_356cfc)
 * Tail call helper FUN_001a1138 with a pointer to the incoming stack slot.
 * Confidence: medium */
void sk_tail_1a1138_356cfc(void)
{
    sk_helper_1a1138((const void *)((uint8_t *)__builtin_frame_address(0) + 8)); /* [Ghidra: &stack0x8] */
}

/* FUN_00356d20 @ 0x00356d20  (est. sk_not_bit0_356d20)
 * Returns bit 0 of the bitwise NOT of the argument. Confidence: medium */
uint32_t sk_not_bit0_356d20(uint32_t param_1)
{
    return (param_1 ^ 0xffffffffu) & 1u;
}

/* FUN_00356d2c @ 0x00356d2c  (est. sk_syscall_stub_356d2c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356d2c(void)
{
    return;
}

/* FUN_00356d5c @ 0x00356d5c  (est. sk_table_4e83ac_356d5c)
 * Returns pointer to the dispatch table at 0x4e83ac. Confidence: medium */
const void *sk_table_4e83ac_356d5c(void)
{
    return (const void *)sk_tab_4e83ac;
}

/* FUN_00356d74 @ 0x00356d74  (est. sk_table_4ec600_356d74)
 * Returns pointer to the table at 0x4ec600. Confidence: medium */
const void *sk_table_4ec600_356d74(void)
{
    return (const void *)sk_tab_4ec600;
}

/* FUN_00356d8c @ 0x00356d8c  (est. sk_table_4ec5e4_356d8c)
 * Returns pointer to the table at 0x4ec5e4. Confidence: medium */
const void *sk_table_4ec5e4_356d8c(void)
{
    return (const void *)sk_tab_4ec5e4;
}

/* FUN_00356da4 @ 0x00356da4  (est. sk_table_4e9830_356da4)
 * Returns pointer to the table at 0x4e9830. Confidence: medium */
const void *sk_table_4e9830_356da4(void)
{
    return (const void *)sk_tab_4e9830;
}

/* FUN_00356dbc @ 0x00356dbc  (est. sk_table_4e97c0_356dbc)
 * Returns pointer to the table at 0x4e97c0. Confidence: medium */
const void *sk_table_4e97c0_356dbc(void)
{
    return (const void *)sk_tab_4e97c0;
}

/* FUN_00356dd4 @ 0x00356dd4  (est. sk_table_4e9550_356dd4)
 * Returns pointer to the table at 0x4e9550. Confidence: medium */
const void *sk_table_4e9550_356dd4(void)
{
    return (const void *)sk_tab_4e9550;
}

/* FUN_00356dec @ 0x00356dec  (est. sk_table_4e8454_356dec)
 * Returns pointer to the table at 0x4e8454. Confidence: medium */
const void *sk_table_4e8454_356dec(void)
{
    return (const void *)sk_tab_4e8454;
}

/* FUN_00356e04 @ 0x00356e04  (est. sk_table_4e83e4_356e04)
 * Returns pointer to the table at 0x4e83e4. Confidence: medium */
const void *sk_table_4e83e4_356e04(void)
{
    return (const void *)sk_tab_4e83e4;
}

/* FUN_00356e1c @ 0x00356e1c  (est. sk_syscall_stub_356e1c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356e1c(void)
{
    return;
}

/* FUN_00356e28 @ 0x00356e28  (est. sk_syscall_stub_356e28)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356e28(void)
{
    return;
}

/* FUN_00356e34 @ 0x00356e34  (est. sk_tail_310d68_356e34)
 * Tail call to helper FUN_00310d68. Confidence: medium */
void sk_tail_310d68_356e34(void)
{
    sk_helper_310d68();
}

/* FUN_00356e4c @ 0x00356e4c  (est. sk_tail_310ea4_356e4c)
 * Tail call to helper FUN_00310ea4. Confidence: medium */
void sk_tail_310ea4_356e4c(void)
{
    sk_helper_310ea4();
}

/* FUN_00356e64 @ 0x00356e64  (est. sk_arith3_356e64)
 * Returns in_w9 + (in_w10 | in_w8) + 1. Confidence: medium */
int sk_arith3_356e64(uint64_t x8, uint64_t x9, uint64_t x10)
{
    /* [Ghidra: in_w8, in_w9, in_w10] */
    return (int)x9 + ((int)x10 | (int)x8) + 1;
}

/* FUN_00356e74 @ 0x00356e74  (est. sk_syscall_stub_356e74)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356e74(void)
{
    return;
}

/* FUN_00356e84 @ 0x00356e84  (est. sk_name_lookup_6561a0_356e84)
 * Resolve/cache a kernel name string identified by ID 0x6561a0 from the name
 * table at 0x4e7f88. Confidence: medium */
void sk_name_lookup_6561a0_356e84(void)
{
    sk_resolve_string(0x6561a0, sk_tab_4e7f88); /* [Ghidra: FUN_00002534(0x6561a0,&DAT_004e7f88)] */
}

/* FUN_00356e98 @ 0x00356e98  (est. sk_syscall_stub_356e98)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356e98(void)
{
    return;
}

/* FUN_00356ea8 @ 0x00356ea8  (est. sk_panic_1afa84_356ea8)
 * Noreturn panic path: tail call FUN_001afa84. Confidence: high */
void sk_panic_1afa84_356ea8(void)
{
    sk_panic_path(); /* [Ghidra: FUN_001afa84, no return] */
}

/* FUN_00356eb4 @ 0x00356eb4  (est. sk_syscall_stub_356eb4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356eb4(void)
{
    return;
}

/* FUN_00356ecc @ 0x00356ecc  (est. sk_user_error_value_cannot_be_converted)
 * Emits a user error with the message "value cannot be converted to" (length
 * 0x1e = 30) and flag 1. Confidence: high (string match) */
void sk_user_error_value_cannot_be_converted(void)
{
    sk_user_error("value cannot be converted to", 0x1e, 1);
    /* [Ghidra: s_value_cannot_be_converted_to_005cfbb0, 0x1e, 1] */
}

/* FUN_00356ee0 @ 0x00356ee0  (est. sk_name_lookup_6561b0_356ee0)
 * Resolve/cache a kernel name string identified by ID 0x6561b0 from the name
 * table at 0x4e8010. Confidence: medium */
void sk_name_lookup_6561b0_356ee0(void)
{
    sk_resolve_string(0x6561b0, sk_tab_4e8010); /* [Ghidra: FUN_00002534(0x6561b0,&DAT_004e8010)] */
}

/* FUN_00356ef4 @ 0x00356ef4  (est. sk_name_lookup_6561a8_356ef4)
 * Resolve/cache a kernel name string identified by ID 0x6561a8 from the name
 * table at 0x4e8008. Confidence: medium */
void sk_name_lookup_6561a8_356ef4(void)
{
    sk_resolve_string(0x6561a8, sk_tab_4e8008); /* [Ghidra: FUN_00002534(0x6561a8,&DAT_004e8008)] */
}

/* FUN_00356f08 @ 0x00356f08  (est. sk_name_lookup_6561a0_356f08)
 * Resolve/cache a kernel name string identified by ID 0x6561a0 from the name
 * table at 0x4e8000. Confidence: medium */
void sk_name_lookup_6561a0_356f08(void)
{
    sk_resolve_string(0x6561a0, sk_tab_4e8000); /* [Ghidra: FUN_00002534(0x6561a0,&DAT_004e8000)] */
}

/* FUN_00356f1c @ 0x00356f1c  (est. sk_name_lookup_656198_356f1c)
 * Resolve/cache a kernel name string identified by ID 0x656198 from the name
 * table at 0x4e7ff8. Confidence: medium */
void sk_name_lookup_656198_356f1c(void)
{
    sk_resolve_string(0x656198, sk_tab_4e7ff8); /* [Ghidra: FUN_00002534(0x656198,&DAT_004e7ff8)] */
}

/* FUN_00356f30 @ 0x00356f30  (est. sk_name_lookup_64e7a0_356f30)
 * Resolve/cache a kernel name string identified by ID 0x64e7a0 from the name
 * table at 0x4e7ff0. Confidence: medium */
void sk_name_lookup_64e7a0_356f30(void)
{
    sk_resolve_string(0x64e7a0, sk_tab_4e7ff0); /* [Ghidra: FUN_00002534(0x64e7a0,&DAT_004e7ff0)] */
}

/* FUN_00356f44 @ 0x00356f44  (est. sk_user_error_more)
 * Emits a user error with the message "more" (length 5) and flag 1.
 * Confidence: high (string match) */
void sk_user_error_more(void)
{
    sk_user_error("more", 5, 1);
    /* [Ghidra: s_more_005d3bd7, 5, 1] */
}

/* FUN_00356f58 @ 0x00356f58  (est. sk_name_lookup_656160_356f58)
 * Resolve/cache a kernel name string identified by ID 0x656160 from the name
 * table at 0x4e7fb0. Confidence: medium */
void sk_name_lookup_656160_356f58(void)
{
    sk_resolve_string(0x656160, sk_tab_4e7fb0); /* [Ghidra: FUN_00002534(0x656160,&DAT_004e7fb0)] */
}

/* FUN_00356f6c @ 0x00356f6c  (est. sk_name_lookup_656218_356f6c)
 * Resolve/cache a kernel name string identified by ID 0x656218 from the name
 * table at 0x4e8070. Confidence: medium */
void sk_name_lookup_656218_356f6c(void)
{
    sk_resolve_string(0x656218, sk_tab_4e8070); /* [Ghidra: FUN_00002534(0x656218,&DAT_004e8070)] */
}

/* FUN_00356f80 @ 0x00356f80  (est. sk_syscall_stub_356f80)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356f80(void)
{
    return;
}

/* FUN_00356f9c @ 0x00356f9c  (est. sk_syscall_stub_356f9c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356f9c(void)
{
    return;
}

/* FUN_00356fb8 @ 0x00356fb8  (est. sk_name_lookup_6561e8_356fb8)
 * Resolve/cache a kernel name string identified by ID 0x6561e8 from the name
 * table at 0x4e8040. Confidence: medium */
void sk_name_lookup_6561e8_356fb8(void)
{
    sk_resolve_string(0x6561e8, sk_tab_4e8040); /* [Ghidra: FUN_00002534(0x6561e8,&DAT_004e8040)] */
}

/* FUN_00356fcc @ 0x00356fcc  (est. sk_tail_365b6c_356fcc)
 * Tail call to helper FUN_00365b6c. Confidence: medium */
void sk_tail_365b6c_356fcc(void)
{
    sk_helper_365b6c();
}

/* FUN_00356fd8 @ 0x00356fd8  (est. sk_syscall_stub_356fd8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_356fd8(void)
{
    return;
}

/* FUN_00356fe8 @ 0x00356fe8  (est. sk_tail_3722e4_356fe8)
 * Tail call to helper FUN_003722e4. Confidence: medium */
void sk_tail_3722e4_356fe8(void)
{
    sk_helper_3722e4();
}

/* FUN_00356ff4 @ 0x00356ff4  (est. sk_tail_365b6c_356ff4)
 * Tail call to helper FUN_00365b6c. Confidence: medium */
void sk_tail_365b6c_356ff4(void)
{
    sk_helper_365b6c();
}

/* FUN_0035701c @ 0x0035701c  (est. sk_syscall_stub_35701c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35701c(void)
{
    return;
}

/* FUN_00357028 @ 0x00357028  (est. sk_syscall_stub_357028)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357028(void)
{
    return;
}

/* FUN_00357044 @ 0x00357044  (est. sk_store_byte_357044)
 * Tail fragment: store an incoming byte register through a pointer in x19.
 * Confidence: medium */
void sk_store_byte_357044(uint64_t x19, uint8_t param_1)
{
    *(uint8_t *)x19 = param_1; /* [Ghidra: *unaff_x19 = param_1] */
}

/* FUN_00357050 @ 0x00357050  (est. sk_syscall_stub_357050)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357050(void)
{
    return;
}

/* FUN_0035705c @ 0x0035705c  (est. sk_syscall_stub_35705c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35705c(void)
{
    return;
}

/* FUN_00357068 @ 0x00357068  (est. sk_syscall_stub_357068)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357068(void)
{
    return;
}

/* FUN_00357074 @ 0x00357074  (est. sk_tail_312d08_357074)
 * Forwards arguments to helper FUN_00312d08 with the record's two head words
 * (param_1[1], *param_1) plus param_3/param_2 and two stack scratch slots.
 * Confidence: medium */
void sk_tail_312d08_357074(uint64_t x29, uint64_t *param_1, uint64_t param_2, uint64_t param_3)
{
    sk_helper_312d08((void *)(x29 - 0x18),
                     (void *)((uint8_t *)__builtin_frame_address(0) + 0x20),
                     (void *)((uint8_t *)__builtin_frame_address(0) + 0x18),
                     param_1[1], *param_1, param_3, param_2);
    /* [Ghidra: FUN_00312d08(x29-0x18,&stack0x20,&stack0x18,param_1[1],*param_1,param_3,param_2)] */
}

/* FUN_00357094 @ 0x00357094  (est. sk_syscall_stub_357094)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357094(void)
{
    return;
}

/* FUN_003570a0 @ 0x003570a0  (est. sk_syscall_stub_3570a0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3570a0(void)
{
    return;
}

/* FUN_003570bc @ 0x003570bc  (est. sk_syscall_stub_3570bc)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3570bc(void)
{
    return;
}

/* FUN_003570d8 @ 0x003570d8  (est. sk_frame_read_3570d8)
 * Reads an 8-byte word from the caller frame at x29-0x70. Confidence: medium */
uint64_t sk_frame_read_3570d8(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0x70);
}

/* FUN_003570e4 @ 0x003570e4  (est. sk_syscall_stub_3570e4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3570e4(void)
{
    return;
}

/* FUN_003570f0 @ 0x003570f0  (est. sk_syscall_stub_3570f0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3570f0(void)
{
    return;
}

/* FUN_00357104 @ 0x00357104  (est. sk_syscall_stub_357104)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357104(void)
{
    return;
}

/* FUN_00357120 @ 0x00357120  (est. sk_copy_record_357120)
 * Copies a 5-word record (offsets 0x18..0x38) from param_2 to param_1:
 * four 8-byte words (0x18,0x20,0x28,0x30) and one 4-byte word (0x38).
 * Confidence: medium */
void sk_copy_record_357120(uint64_t param_1, uint64_t param_2)
{
    *(uint64_t *)(param_1 + 0x20) = *(uint64_t *)(param_2 + 0x20);
    *(uint64_t *)(param_1 + 0x18) = *(uint64_t *)(param_2 + 0x18);
    *(uint64_t *)(param_1 + 0x30) = *(uint64_t *)(param_2 + 0x30);
    *(uint64_t *)(param_1 + 0x28) = *(uint64_t *)(param_2 + 0x28);
    *(uint32_t *)(param_1 + 0x38) = *(uint32_t *)(param_2 + 0x38);
}

/* FUN_0035713c @ 0x0035713c  (est. sk_syscall_stub_35713c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35713c(void)
{
    return;
}

/* FUN_00357148 @ 0x00357148  (est. sk_store_word_357148)
 * Tail fragment: store an incoming word register (w22) through a pointer in
 * x19. Confidence: medium */
void sk_store_word_357148(uint64_t x19, uint64_t x22)
{
    *(uint32_t *)x19 = (uint32_t)x22; /* [Ghidra: unaff_x19 / unaff_w22] */
}

/* FUN_00357154 @ 0x00357154  (est. sk_frame_pair_357154)
 * Returns a 16-byte pair computed from incoming registers:
 * lo = (x25 + x19) & x26, hi = (x25 + x20) & x26. Confidence: medium */
cl4_result_t sk_frame_pair_357154(uint64_t x19, uint64_t x20, uint64_t x25, uint64_t x26)
{
    cl4_result_t r;
    r.lo = (x25 + x19) & x26; /* [Ghidra: auVar1._0_8_] */
    r.hi = (x25 + x20) & x26; /* [Ghidra: auVar1._8_8_] */
    return r;
}

/* FUN_00357170 @ 0x00357170  (est. sk_syscall_stub_357170)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357170(void)
{
    return;
}

/* FUN_0035717c @ 0x0035717c  (est. sk_frame_write_35717c)
 * Writes (x21 + 0x20) into the caller frame at x29-0x90. Confidence: medium */
void sk_frame_write_35717c(uint64_t x29, uint64_t x21)
{
    *(uint64_t *)(x29 - 0x90) = x21 + 0x20;
}

/* FUN_00357198 @ 0x00357198  (est. sk_syscall_stub_357198)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357198(void)
{
    return;
}

/* FUN_003571a4 @ 0x003571a4  (est. sk_syscall_stub_3571a4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3571a4(void)
{
    return;
}

/* FUN_003571b0 @ 0x003571b0  (est. sk_frame_copy_and_reset_3571b0)
 * Copies three 8-byte words from (x20 + off) to (x19 + off) at the incoming
 * offsets (x11, x10, x9), writes a byte flag to (x19+0x48), then calls helper
 * FUN_0036b270. Tail fragment of a record-refresh path. Confidence: medium */
void sk_frame_copy_and_reset_3571b0(uint64_t x19, uint64_t x20, uint64_t x9,
                                    uint64_t x10, uint64_t x11, uint64_t x8)
{
    *(uint64_t *)(x19 + x11) = *(uint64_t *)(x20 + x11);
    *(uint64_t *)(x19 + x10) = *(uint64_t *)(x20 + x10);
    *(uint64_t *)(x19 + x9)  = *(uint64_t *)(x20 + x9);
    *(uint8_t *)(x19 + 0x48) = (uint8_t)x8; /* [Ghidra: in_w8] */
    sk_helper_36b270();
}

/* FUN_003571d0 @ 0x003571d0  (est. sk_frame_pair_3571d0)
 * Reads int at (x21+0x30); returns pair lo = (x25 + that int), hi = the word
 * at x29-0xa8 (captured before it is overwritten with x23). Confidence: medium */
cl4_result_t sk_frame_pair_3571d0(uint64_t x21, uint64_t x23, uint64_t x25, uint64_t x29)
{
    int i = *(int *)(x21 + 0x30);
    uint64_t hi = *(uint64_t *)(x29 - 0xa8); /* captured before overwrite */
    *(uint64_t *)(x29 - 0xb0) = (uint64_t)i;
    *(uint64_t *)(x29 - 0xa8) = x23;
    cl4_result_t r;
    r.lo = x25 + (uint64_t)i;
    r.hi = hi;
    return r;
}

/* FUN_003571ec @ 0x003571ec  (est. sk_syscall_stub_3571ec)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3571ec(void)
{
    return;
}

/* FUN_003571f8 @ 0x003571f8  (est. sk_dispatch_indirect_3571f8)
 * Dereferences param_1 to a call record, then dispatches through helper
 * FUN_0031e874 with the record's 8 head words as arguments.
 * Confidence: medium */
void sk_dispatch_indirect_3571f8(uint64_t *param_1)
{
    uint64_t *rec = (uint64_t *)*param_1; /* [Ghidra: param_1 = *param_1] */
    sk_helper_31e874(rec[0], rec[1], rec[2], rec[3],
                     rec[4], rec[5], rec[6], rec[7]);
}

/* FUN_00357228 @ 0x00357228  (est. sk_frame_pair_357228)
 * Returns the 16-byte value pointed to by x19. Confidence: medium */
cl4_result_t sk_frame_pair_357228(uint64_t x19)
{
    return *(cl4_result_t *)x19; /* [Ghidra: *unaff_x19] */
}

/* FUN_0035723c @ 0x0035723c  (est. sk_syscall_stub_35723c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35723c(void)
{
    return;
}

/* FUN_00357244 @ 0x00357244  (est. sk_const_0xd00000000000001e)
 * Returns the constant 0xd00000000000001e (a status/cap-encoding constant).
 * Confidence: medium */
uint64_t sk_const_0xd00000000000001e(void)
{
    return 0xd00000000000001eULL;
}

/* FUN_00357250 @ 0x00357250  (est. sk_syscall_stub_357250)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357250(void)
{
    return;
}

/* FUN_0035725c @ 0x0035725c  (est. sk_syscall_stub_35725c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35725c(void)
{
    return;
}

/* FUN_00357268 @ 0x00357268  (est. sk_frame_write_357268)
 * Writes the negation of x25 into the caller frame at x29-0x60. Confidence: medium */
void sk_frame_write_357268(uint64_t x29, uint64_t x25)
{
    *(uint64_t *)(x29 - 0x60) = (uint64_t)(-x25);
}

/* FUN_00357274 @ 0x00357274  (est. sk_frame_read_357274)
 * Reads an 8-byte word from the caller frame at x29-0xe0. Confidence: medium */
uint64_t sk_frame_read_357274(uint64_t x29)
{
    return *(uint64_t *)(x29 - 0xe0);
}

/* FUN_00357280 @ 0x00357280  (est. sk_build_frame_args_357280)
 * Builds a 5-word argument record in the caller frame at x29-0x80:
 * [x27, in_x11, in_x10, 0, (param_1 & in_x12)], and returns its address.
 * Confidence: medium */
uint64_t sk_build_frame_args_357280(uint64_t x29, uint64_t x27, uint64_t in_x10,
                                    uint64_t in_x11, uint64_t in_x12, uint64_t param_1)
{
    *(uint64_t *)(x29 - 0x80) = x27;
    *(uint64_t *)(x29 - 0x78) = in_x11;
    *(uint64_t *)(x29 - 0x70) = in_x10;
    *(uint64_t *)(x29 - 0x68) = 0;
    *(uint64_t *)(x29 - 0x60) = param_1 & in_x12;
    return x29 - 0x80;
}

/* FUN_0035729c @ 0x0035729c  (est. sk_frame_pair_35729c)
 * Reads int at (x21+0x40); stores it to x29-0xc8; returns pair lo =
 * (x26 + that int), hi = the word at x29-0xa0. Confidence: medium */
cl4_result_t sk_frame_pair_35729c(uint64_t x21, uint64_t x26, uint64_t x29)
{
    int i = *(int *)(x21 + 0x40);
    uint64_t hi = *(uint64_t *)(x29 - 0xa0);
    *(uint64_t *)(x29 - 0xc8) = (uint64_t)i;
    cl4_result_t r;
    r.lo = x26 + (uint64_t)i;
    r.hi = hi;
    return r;
}

/* FUN_003572b8 @ 0x003572b8  (est. sk_syscall_stub_3572b8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3572b8(void)
{
    return;
}

/* FUN_003572c4 @ 0x003572c4  (est. sk_user_error_frame_3572c4)
 * Emits a user error using a message/pointer and length read from the caller
 * frame (x29-0xa8, x29-0xa0) with flag 1. Confidence: medium */
void sk_user_error_frame_3572c4(uint64_t x29)
{
    sk_user_error((const char *)*(uint64_t *)(x29 - 0xa8),
                  *(uint64_t *)(x29 - 0xa0), 1);
    /* [Ghidra: FUN_001a89a8(*(x29-0xa8), *(x29-0xa0), 1)] */
}

/* FUN_003572d4 @ 0x003572d4  (est. sk_syscall_stub_3572d4)
 * Empty handler — no-op slot. (Ghidra warns a global overlaps a smaller
 * symbol at this address.) Confidence: medium */
void sk_syscall_stub_3572d4(void)
{
    return;
}

/* FUN_00357310 @ 0x00357310  (est. sk_frame_pair_357310)
 * Returns pair lo = *(x29-0x130), hi = *(x29-0xd0). Confidence: medium */
cl4_result_t sk_frame_pair_357310(uint64_t x29)
{
    cl4_result_t r;
    r.lo = *(uint64_t *)(x29 - 0x130);
    r.hi = *(uint64_t *)(x29 - 0xd0);
    return r;
}

/* FUN_0035732c @ 0x0035732c  (est. sk_stack_ptr_35732c)
 * Returns a pointer into the incoming stack frame (sp+0x10). Confidence: medium */
void *sk_stack_ptr_35732c(void)
{
    return (void *)((uint8_t *)__builtin_frame_address(0) + 0x10); /* [Ghidra: &stack0x10] */
}

/* FUN_00357338 @ 0x00357338  (est. sk_syscall_stub_357338)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357338(void)
{
    return;
}

/* FUN_00357344 @ 0x00357344  (est. sk_syscall_stub_357344)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357344(void)
{
    return;
}

/* FUN_00357350 @ 0x00357350  (est. sk_syscall_stub_357350)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357350(void)
{
    return;
}

/* FUN_0035735c @ 0x0035735c  (est. sk_syscall_stub_35735c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35735c(void)
{
    return;
}

/* FUN_00357368 @ 0x00357368  (est. sk_syscall_stub_357368)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357368(void)
{
    return;
}

/* FUN_00357374 @ 0x00357374  (est. sk_syscall_stub_357374)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357374(void)
{
    return;
}

/* FUN_00357380 @ 0x00357380  (est. sk_syscall_stub_357380)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357380(void)
{
    return;
}

/* FUN_0035738c @ 0x0035738c  (est. sk_syscall_stub_35738c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35738c(void)
{
    return;
}

/* FUN_00357398 @ 0x00357398  (est. sk_syscall_stub_357398)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357398(void)
{
    return;
}

/* FUN_003573a4 @ 0x003573a4  (est. sk_frame_pair_3573a4)
 * Returns pair lo = (x26 + *(int*)(x21+0x60)), hi = *(x29-0xa8). Confidence: medium */
cl4_result_t sk_frame_pair_3573a4(uint64_t x21, uint64_t x26, uint64_t x29)
{
    cl4_result_t r;
    r.lo = x26 + (uint64_t)(*(int *)(x21 + 0x60));
    r.hi = *(uint64_t *)(x29 - 0xa8);
    return r;
}

/* FUN_003573c0 @ 0x003573c0  (est. sk_syscall_stub_3573c0)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3573c0(void)
{
    return;
}

/* FUN_003573cc @ 0x003573cc  (est. sk_frame_write_3573cc)
 * Writes an incoming word (x23) into the caller frame at x29-0x110. Confidence: medium */
void sk_frame_write_3573cc(uint64_t x29, uint64_t x23)
{
    *(uint64_t *)(x29 - 0x110) = x23;
}

/* FUN_003573e8 @ 0x003573e8  (est. sk_syscall_stub_3573e8)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3573e8(void)
{
    return;
}

/* FUN_003573f4 @ 0x003573f4  (est. sk_syscall_stub_3573f4)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_3573f4(void)
{
    return;
}

/* FUN_00357400 @ 0x00357400  (est. sk_syscall_stub_357400)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357400(void)
{
    return;
}

/* FUN_0035740c @ 0x0035740c  (est. sk_syscall_stub_35740c)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_35740c(void)
{
    return;
}

/* FUN_00357418 @ 0x00357418  (est. sk_syscall_stub_357418)
 * Empty handler — no-op slot. Confidence: medium */
void sk_syscall_stub_357418(void)
{
    return;
}

/* FUN_00357424 @ 0x00357424  (est. sk_frame_pair_357424)
 * Returns pair lo = (x24 + *(int*)(*(x29-0x68)+0x24)), hi =
 * (x26 + *(int*)(x25+0x30)). Confidence: medium */
cl4_result_t sk_frame_pair_357424(uint64_t x24, uint64_t x25, uint64_t x26, uint64_t x29)
{
    cl4_result_t r;
    r.lo = x24 + (uint64_t)(*(int *)(*(uint64_t *)(x29 - 0x68) + 0x24));
    r.hi = x26 + (uint64_t)(*(int *)(x25 + 0x30));
    return r;
}
