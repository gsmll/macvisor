/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0049eee8-0x004a36fc (worker SKR33): the frame / context bookkeeping
 * layer of the cap-invocation machinery. These small functions open the
 * running op context (x19/x20/x22), seed per-invocation fields from the
 * current thread frame, resolve descriptor/status words, bind continuation
 * records, and tail-dispatch into the reply/continuation tables. Many are
 * offset-shifted siblings that differ only in which context slot they touch.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))

/* ------------------------------------------------------------------ *
 * Globals referenced by this slice (image-base addresses are the Ghidra
 * ground truth).
 * ------------------------------------------------------------------ */

extern uint64_t sk_g_00657d98;  /* DAT_00657d98: one-time init guard/result */

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). The
 * sk_x_XXXXXXXX names encode the Ghidra FUN_ address. Functions that
 * Ghidra shows returning a 16-byte register pair are typed cl4_result_t.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_000026e8();
extern unsigned long sk_x_00002834();
extern unsigned long sk_x_00012568();
extern unsigned long sk_x_00019858();
extern unsigned long sk_x_00021480();
extern unsigned long sk_x_00027614();
extern unsigned long sk_x_00027754();
extern unsigned long sk_x_0006b438();
extern unsigned long sk_x_000839d8();
extern unsigned long sk_x_000839f8();
extern unsigned long sk_x_00084220();
extern unsigned long sk_x_00084234();
extern cl4_result_t sk_x_0009461c();
extern unsigned long sk_x_000a6f88();
extern unsigned long sk_x_00114330();
extern unsigned long sk_x_00117cc4();
extern unsigned long sk_x_0024c9c0();
extern unsigned long sk_x_0032b65c();
extern unsigned long sk_x_00349530();
extern unsigned long sk_x_0034ab20();
extern unsigned long sk_x_0034b044();
extern unsigned long sk_x_0034b07c();
extern cl4_result_t sk_x_0034b264();
extern unsigned long sk_x_0034b7e4();
extern unsigned long sk_x_0034ba48();
extern unsigned long sk_x_0034bfb4();
extern unsigned long sk_x_0034e34c();
extern cl4_result_t sk_x_0034f2f4();
extern unsigned long sk_x_0034f8e4();
extern unsigned long sk_x_003504d0();
extern unsigned long sk_x_003507e0();
extern cl4_result_t sk_x_00350c5c();
extern cl4_result_t sk_x_00351244();
extern unsigned long sk_x_00351a38();
extern unsigned long sk_x_00351d18();
extern unsigned long sk_x_00352b20();
extern cl4_result_t sk_x_00354070();
extern unsigned long sk_x_003540d0();
extern unsigned long sk_x_00355538();
extern unsigned long sk_x_0035944c();
extern unsigned long sk_x_0036851c();
extern unsigned long sk_x_0036b118();
extern unsigned long sk_x_0036b21c();
extern unsigned long sk_x_0036b270();
extern unsigned long sk_x_003728b8();
extern unsigned long sk_x_00376820();
extern cl4_result_t sk_x_00377824();
extern cl4_result_t sk_x_00377dcc();
extern unsigned long sk_x_003a25d4();
extern unsigned long sk_x_00458940();
extern unsigned long sk_x_00459138();
extern unsigned long sk_x_004593ac();
extern unsigned long sk_x_0045a4b4();
extern unsigned long sk_x_00462bd8();
extern unsigned long sk_x_00462fec();
extern cl4_result_t sk_x_00463028();
extern unsigned long sk_x_00463058();
extern unsigned long sk_x_00463080();
extern unsigned long sk_x_004633e0();
extern unsigned long sk_x_00464ae8();
extern unsigned long sk_x_00464b04();
extern unsigned long sk_x_004661a4();
extern unsigned long sk_x_00492850();
extern unsigned long sk_x_00492920();
extern unsigned long sk_x_00492b3c();
extern unsigned long sk_x_00492c6c();
extern cl4_result_t sk_x_00497504();
extern unsigned long sk_x_0049df60();
extern unsigned long sk_x_0049dfa0();
extern unsigned long sk_x_004a4b14();
extern unsigned long sk_x_004a5414();
extern unsigned long sk_x_004a54b0();
extern unsigned long sk_x_004a83c0();
extern unsigned long sk_x_004a8ef8();
extern unsigned long sk_x_004a8f0c();
extern unsigned long sk_x_004a90e4();
extern unsigned long sk_x_004a96a0();
extern unsigned long sk_x_004aa47c();
extern cl4_result_t sk_x_004aa4fc();
extern unsigned long sk_x_004aa6f0();
extern unsigned long sk_x_004aa850();
extern unsigned long sk_x_004aa864();
extern unsigned long sk_x_004aa8b0();
extern cl4_result_t sk_x_004aa914();
extern unsigned long sk_x_004aaa88();
extern unsigned long sk_x_004aaaf4();
extern unsigned long sk_x_004aab30();
extern unsigned long sk_x_004aaba8();
extern unsigned long sk_x_004aabb8();
extern unsigned long sk_x_004aac14();
extern unsigned long sk_x_004aadb8();
extern unsigned long sk_x_004aae14();
extern unsigned long sk_x_004aae88();
extern unsigned long sk_x_004aaed8();
extern unsigned long sk_x_004aaf48();
extern unsigned long sk_x_004aafb8();
extern unsigned long sk_x_004ab0fc();
extern cl4_result_t sk_x_004ab10c();
extern unsigned long sk_x_004ab13c();
extern cl4_result_t sk_x_004ab150();
extern unsigned long sk_x_004ab1e8();
extern unsigned long sk_x_004ab230();
extern unsigned long sk_x_004ab2dc();
extern unsigned long sk_x_004ab5ec();
extern cl4_result_t sk_x_004ab600();
extern cl4_result_t sk_x_004ab710();
extern unsigned long sk_x_004ab734();
extern unsigned long sk_x_004ab74c();
extern unsigned long sk_x_004ab954();
extern unsigned long sk_x_004ab998();
extern unsigned long sk_x_004aba1c();
extern unsigned long sk_x_004aba50();
extern unsigned long sk_x_004aba60();
extern unsigned long sk_x_004aba70();
extern unsigned long sk_x_004abae4();
extern unsigned long sk_x_004abb64();
extern unsigned long sk_x_004abb80();
extern unsigned long sk_x_004abbc4();
extern unsigned long sk_x_004abbe0();
extern unsigned long sk_x_004abc50();
extern unsigned long sk_x_004abcc0();
extern unsigned long sk_x_004abda8();
extern unsigned long sk_x_004abdd0();
extern unsigned long sk_x_004abdec();
extern unsigned long sk_x_004abe08();
extern unsigned long sk_x_004abe40();
extern unsigned long sk_x_004abec0();
extern unsigned long sk_x_004abee0();
extern unsigned long sk_x_004abf50();
extern cl4_result_t sk_x_004abf7c();
extern unsigned long sk_x_004ac168();
extern unsigned long sk_x_004ac1d4();
extern unsigned long sk_x_004ac264();
extern unsigned long sk_x_004ac384();
extern unsigned long sk_x_004ac390();
extern unsigned long sk_x_004ac3a8();
extern unsigned long sk_x_004ac3c0();
extern unsigned long sk_x_004ac3d8();
extern unsigned long sk_x_004ac3fc();
extern unsigned long sk_x_004ac40c();
extern unsigned long sk_x_004ac42c();
extern unsigned long sk_x_004ac45c();
extern unsigned long sk_x_004ac46c();
extern unsigned long sk_x_004ac484();
extern unsigned long sk_x_004ac49c();
extern unsigned long sk_x_004ac4ac();
extern unsigned long sk_x_004ac4d0();
extern unsigned long sk_x_004ac550();
extern unsigned long sk_x_004ac6d0();
extern cl4_result_t sk_x_004ac784();
extern unsigned long sk_x_004ac790();
extern cl4_result_t sk_x_004ac7c8();
extern unsigned long sk_x_004ac804();
extern unsigned long sk_x_004ac87c();
extern unsigned long sk_x_004ac8fc();
extern unsigned long sk_x_004aca6c();
extern unsigned long sk_x_004aca80();
extern unsigned long sk_x_004acac0();
extern unsigned long sk_x_004acc70();
extern unsigned long sk_x_004accf0();
extern unsigned long sk_x_004a3714();

/* ------------------------------------------------------------------ *
 * In-slice forward declarations.
 * ------------------------------------------------------------------ */
static void sk_x_0049eee8(void);
static void sk_x_0049ef48(void);
static void sk_x_0049ef90(void);
static void sk_x_0049f05c(void);
static void sk_x_0049f144(cl4_result_t param_1, cl4_result_t param_2);
static void sk_x_0049f1d8(uint64_t *param_1, uint32_t param_2, uint32_t param_3);
static void sk_x_0049f264(void);
static void sk_x_0049f2ac(void);
static void sk_x_0049f318(void);
static void sk_x_0049f3e8(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_0049f500(uint64_t param_1, uint64_t param_2);
static void sk_x_0049f660(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_0049f75c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_0049f810(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static uint64_t sk_x_0049f90c(uint32_t *param_1, uint32_t param_2, uint64_t param_3);
static void sk_x_0049fcf8(void);
static void sk_x_0049fd10(void);
static void sk_x_0049fd28(uint64_t param_1);
static void sk_x_0049fd8c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_0049fe68(uint64_t param_1, uint64_t param_2);
static void sk_x_0049ff7c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a0058(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a00f4(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static int32_t sk_x_004a01d0(uint32_t *param_1, uint32_t param_2, uint64_t param_3);
static void sk_x_004a058c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a05d0(void);
static void sk_x_004a061c(void);
static void sk_x_004a07e4(uint64_t param_1);
static void sk_x_004a0858(void);
static void sk_x_004a0934(void);
static void sk_x_004a0970(void);
static void sk_x_004a09ac(void);
static uint64_t sk_x_004a0a94(void);
static void sk_x_004a0cf4(uint64_t param_1);
static void sk_x_004a0d6c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a0eb8(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a0f64(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a1010(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a10bc(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static uint64_t sk_x_004a1168(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a1624(void);
static void sk_x_004a16bc(void);
static void sk_x_004a17d0(void);
static void sk_x_004a18e8(void);
static void sk_x_004a1a50(uint64_t param_1);
static uint64_t sk_x_004a1a88(uint64_t param_1);
static void sk_x_004a1b04(void);
static void sk_x_004a1bb8(void);
static void sk_x_004a1cc0(uint64_t param_1);
static uint64_t sk_x_004a1d6c(uint64_t param_1, uint64_t *param_2, uint64_t param_3);
static void sk_x_004a1e84(uint64_t param_1, uint64_t param_2);
static void sk_x_004a1fb4(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a204c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a20e4(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static uint64_t sk_x_004a217c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a25ec(cl4_result_t param_1, cl4_result_t param_2);
static void sk_x_004a2634(void);
static void sk_x_004a26a0(void);
static void sk_x_004a2718(uint64_t param_1);
static void sk_x_004a2754(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a27cc(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_004a28b8(void);
static void sk_x_004a29d4(void);
static void sk_x_004a2a60(void);
static void sk_x_004a2b3c(void);
static void sk_x_004a2c3c(void);
static void sk_x_004a2ea8(uint64_t param_1, uint64_t param_2, uint64_t *param_3);
static uint64_t sk_x_004a2fa8(uint64_t param_1);
static uint64_t sk_x_004a2fd8(uint64_t param_1);
static uint64_t sk_x_004a3008(uint64_t param_1);
static void sk_x_004a3038(void);
static void sk_x_004a3050(uint64_t param_1, uint64_t *param_2);
static void sk_x_004a30d4(void);
static uint64_t sk_x_004a30ec(uint64_t param_1);
static void sk_x_004a311c(void);
static void sk_x_004a3120(void);
static void sk_x_004a3154(void);
static void sk_x_004a3158(void);
static void sk_x_004a3184(void);
static void sk_x_004a31ec(uint64_t param_1, uint64_t param_2);
static void sk_x_004a31fc(uint64_t param_1);
static void sk_x_004a3214(uint64_t param_1);
static void sk_x_004a322c(uint64_t *param_1);
static void sk_x_004a3268(uint64_t param_1);
static void sk_x_004a3290(void);
static void sk_x_004a3294(void);
static void sk_x_004a32c4(uint64_t param_1);
static void sk_x_004a32ec(uint64_t param_1);
static void sk_x_004a3318(uint64_t param_1);
static void sk_x_004a3340(uint64_t param_1);
static void sk_x_004a3368(uint64_t param_1);
static void sk_x_004a3390(uint64_t param_1);
static void sk_x_004a33b8(void);
static void sk_x_004a33bc(void);
static void sk_x_004a33e0(uint64_t param_1);
static void sk_x_004a33e4(uint64_t param_1);
static void sk_x_004a3400(void);
static void sk_x_004a3418(void);
static void sk_x_004a341c(void);
static void sk_x_004a3438(uint64_t param_1);
static void sk_x_004a343c(uint64_t param_1);
static void sk_x_004a3458(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
static void sk_x_004a3494(void);
static void sk_x_004a3498(void);
static void sk_x_004a34b4(uint64_t *param_1);
static void sk_x_004a34f0(uint64_t param_1, uint64_t param_2);
static uint64_t sk_x_004a3500(uint64_t param_1);
static uint64_t sk_x_004a3528(uint64_t param_1);
static void sk_x_004a3550(uint64_t param_1, uint64_t param_2);
static uint64_t sk_x_004a3560(uint64_t param_1);
static int64_t sk_x_004a3588(uint64_t param_1);
static void sk_x_004a35b8(void);
static void sk_x_004a363c(uint64_t param_1, uint64_t param_2);
static uint64_t sk_x_004a364c(uint64_t param_1);
static void sk_x_004a3674(void);
static void sk_x_004a3678(void);
static void sk_x_004a369c(void);
static void sk_x_004a36c4(uint64_t param_1, uint64_t param_2);
static uint64_t sk_x_004a36d4(uint64_t param_1);
static void sk_x_004a36fc(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                          uint64_t param_4, uint64_t param_5);

/* ------------------------------------------------------------------ *
 * Function bodies (in address order).
 * ------------------------------------------------------------------ */

/* FUN_0049eee8 @ 0x0049eee8   (est. sk_x_0049eee8)
 * Ghidra: void FUN_0049eee8(void)
 * Message/mailbox teardown helper: retrieves a 16-byte pair via sk_x_004ab150,
 * swaps the 0x18 word between the pair's halves, then copies the 0x30/0x38
 * fields of preserved register x19 into x20, releasing the displaced references
 * with sk_x_0036b118. Runs against the callee-saved frame pointers x19/x20.
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 are preserved callee-saved registers (byte offsets
 *        0x18/0x30/0x38); auVar2 is the 16-byte pair returned by sk_x_004ab150. */
static void sk_x_0049eee8(void)
{
    uint64_t uVar1;
    uint64_t *unaff_x19;   /* preserved x19 */
    uint64_t *unaff_x20;   /* preserved x20 */
    cl4_result_t auVar2;

    sk_x_003504d0();
    auVar2 = sk_x_004ab150();
    uVar1 = *(uint64_t *)(auVar2.lo + 0x18);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x18) = *(uint64_t *)(auVar2.hi + 0x18);
    sk_x_0036b118(uVar1);
    sk_x_004ac87c();
    *(uint8_t *)((uint8_t *)unaff_x20 + 0x30) = *(uint8_t *)((uint8_t *)unaff_x19 + 0x30);
    uVar1 = *(uint64_t *)((uint8_t *)unaff_x20 + 0x38);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x38) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x38);
    sk_x_0036b118(uVar1);
}

/* FUN_0049ef48 @ 0x0049ef48   (est. sk_x_0049ef48)
 * Ghidra: void FUN_0049ef48(void)
 * Retrieves a context/record pointer via sk_x_004aadb8 and forwards five 8-byte
 * fields (offsets 0x40..0x80) of it to sk_x_0034f8e4, then releases the result
 * register (x8) via sk_x_00459138. 
 * Confidence: low
 * Notes: extraout_x8 carries the x8 output of the preceding call into
 *        sk_x_00459138. */
static void sk_x_0049ef48(void)
{
    uint64_t lVar1;
    uint64_t extraout_x8;   /* output x8 of previous call */

    lVar1 = sk_x_004aadb8();
    sk_x_0034f8e4(*(uint64_t *)(lVar1 + 0x40), *(uint64_t *)(lVar1 + 0x50),
                  *(uint64_t *)(lVar1 + 0x60), *(uint64_t *)(lVar1 + 0x70),
                  *(uint64_t *)(lVar1 + 0x80));
    sk_x_00459138(extraout_x8);
}

/* FUN_0049ef90 @ 0x0049ef90   (est. sk_x_0049ef90)
 * Ghidra: void FUN_0049ef90(void)
 * Fills a 19-word descriptor at preserved register x19: the first eight words
 * come from the output pointer of sk_x_00350c5c (with word 0 replaced by the
 * return of sk_x_00463058), the next ten from stack spill slots, then a byte at
 * offset 0x98. Also performs bookkeeping calls and releases. 
 * Confidence: low
 * Notes: extraout_x1 is the pointer output of the preceding call; in_stack_*
 *        are stack-spilled arguments passed by the caller; byte offset 0x98
 *        stores a truncated byte. */
static void sk_x_0049ef90(void)
{
    uint64_t uVar1, uVar2, uVar3, uVar4, uVar5, uVar6, uVar7, uVar8, uVar9;
    uint64_t *unaff_x19;        /* preserved x19 */
    uint64_t *extraout_x1;      /* x1 pointer output of previous call */
    uint64_t extraout_x1_00;    /* x1 value output of previous call */
    uint64_t in_stack_68, in_stack_70, in_stack_78, in_stack_80, in_stack_88;
    uint64_t in_stack_90, in_stack_98, in_stack_a0, in_stack_a8, in_stack_b0;
    uint32_t uStack_c4;

    sk_x_00464b04();
    sk_x_00350c5c();
    uVar4 = extraout_x1[1];
    uVar1 = extraout_x1[2];
    uVar5 = extraout_x1[3];
    uVar2 = extraout_x1[4];
    uVar6 = extraout_x1[5];
    uVar3 = extraout_x1[6];
    uVar8 = extraout_x1[7];
    sk_x_00462bd8(*extraout_x1);
    uVar9 = *(uint64_t *)(extraout_x1_00 + 0x90);
    uStack_c4 = (uint32_t)*(uint8_t *)(extraout_x1_00 + 0x98);
    uVar7 = sk_x_00463058();
    sk_x_004aa850();
    sk_x_0045a4b4();
    *unaff_x19 = uVar7;
    unaff_x19[1] = uVar4;
    unaff_x19[2] = uVar1;
    unaff_x19[3] = uVar5;
    unaff_x19[4] = uVar2;
    unaff_x19[5] = uVar6;
    unaff_x19[6] = uVar3;
    unaff_x19[7] = uVar8;
    unaff_x19[8] = in_stack_68;
    unaff_x19[9] = in_stack_70;
    unaff_x19[10] = in_stack_78;
    unaff_x19[0xb] = in_stack_80;
    unaff_x19[0xc] = in_stack_88;
    unaff_x19[0xd] = in_stack_90;
    unaff_x19[0xe] = in_stack_98;
    unaff_x19[0xf] = in_stack_a0;
    unaff_x19[0x10] = in_stack_a8;
    unaff_x19[0x11] = in_stack_b0;
    unaff_x19[0x12] = uVar9;
    *(uint8_t *)((uint8_t *)unaff_x19 + 0x98) = (uint8_t)uStack_c4;
    sk_x_004ac1d4();
    sk_x_00464ae8();
}

/* FUN_0049f05c @ 0x0049f05c   (est. sk_x_0049f05c)
 * Ghidra: void FUN_0049f05c(void)
 * Counterpart of sk_x_0049ef90: writes a descriptor at preserved register x19
 * from stack spill slots (offsets 0x40..0x90), seeds the 0x90/0x98 fields from
 * a pointer, and forwards the 0x90 plus 0x40..0x80 fields to sk_x_00462fec.
 * Confidence: low
 * Notes: unaff_x19 is a preserved callee-saved pointer; in_stack_* are caller
 *        stack args; extraout_x1/_00 carry outputs of the preceding call. */
static void sk_x_0049f05c(void)
{
    uint64_t uVar1, uVar2;
    uint64_t *unaff_x19;        /* preserved x19 */
    uint64_t *extraout_x1;      /* x1 pointer output of previous call */
    uint64_t extraout_x1_00;    /* x1 value output of previous call */
    uint64_t in_stack_68, in_stack_70, in_stack_78, in_stack_80, in_stack_88;
    uint64_t in_stack_90, in_stack_98, in_stack_a0, in_stack_a8, in_stack_b0;
    uint32_t uStack_c4;

    sk_x_00464b04();
    sk_x_00350c5c();
    uVar1 = *extraout_x1;
    sk_x_00462bd8();
    uVar2 = *(uint64_t *)(extraout_x1_00 + 0x90);
    uStack_c4 = (uint32_t)*(uint8_t *)(extraout_x1_00 + 0x98);
    sk_x_00463058();
    sk_x_004aa864(uVar1);
    sk_x_0045a4b4();
    sk_x_00463080();
    sk_x_00462fec(*(uint64_t *)((uint8_t *)unaff_x19 + 0x90),
                  *(uint64_t *)((uint8_t *)unaff_x19 + 0x40),
                  *(uint64_t *)((uint8_t *)unaff_x19 + 0x50),
                  *(uint64_t *)((uint8_t *)unaff_x19 + 0x60),
                  *(uint64_t *)((uint8_t *)unaff_x19 + 0x70),
                  *(uint64_t *)((uint8_t *)unaff_x19 + 0x80));
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x40) = in_stack_68;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x48) = in_stack_70;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x50) = in_stack_78;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x58) = in_stack_80;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x60) = in_stack_88;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x68) = in_stack_90;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x70) = in_stack_98;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x78) = in_stack_a0;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x80) = in_stack_a8;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x88) = in_stack_b0;
    *(uint64_t *)((uint8_t *)unaff_x19 + 0x90) = uVar2;
    *(uint8_t *)((uint8_t *)unaff_x19 + 0x98) = (uint8_t)uStack_c4;
    sk_x_0034f8e4();
    sk_x_00459138();
    sk_x_004661a4();
    sk_x_00464ae8();
}
/* FUN_0049f144 @ 0x0049f144   (est. sk_x_0049f144)
 * Ghidra: void FUN_0049f144(undefined1 param_1 [16],undefined1 param_2 [16])
 * Message descriptor builder: copies an 18-word descriptor from preserved
 * register x20 into x19 (word-for-word, including a trailing byte at offset
 * 0x98), then forwards the result of sk_x_00463028 plus param_2 and three saved
 * words to sk_x_0034f8e4.
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 are preserved callee-saved pointers; auVar7 is the
 *        16-byte pair from sk_x_00350c5c/sk_x_00463028; extraout_x8/_w9 carry
 *        prior-call outputs into the last descriptor words. */
static void sk_x_0049f144(cl4_result_t param_1, cl4_result_t param_2)
{
    uint64_t uVar1, uVar2, uVar3, uVar4, uVar5, uVar6;
    uint64_t extraout_x8;    /* x8 output of previous call */
    uint8_t extraout_w9;     /* w9 output of previous call */
    uint64_t *unaff_x19;     /* preserved x19 */
    uint64_t *unaff_x20;     /* preserved x20 */
    cl4_result_t auVar7;

    auVar7 = sk_x_00350c5c();
    auVar7 = sk_x_00463028(*(uint64_t *)(auVar7.hi + 0x90), *(uint64_t *)auVar7.lo,
                           unaff_x19[1], unaff_x19[2]);
    uVar1 = unaff_x19[0xc];
    uVar2 = unaff_x19[0xe];
    uVar3 = unaff_x19[0x10];
    uVar4 = *unaff_x20;
    uVar6 = unaff_x20[3];
    uVar5 = unaff_x20[2];
    unaff_x19[1] = unaff_x20[1];
    *unaff_x19 = uVar4;
    unaff_x19[3] = uVar6;
    unaff_x19[2] = uVar5;
    uVar4 = unaff_x20[4];
    uVar6 = unaff_x20[7];
    uVar5 = unaff_x20[6];
    unaff_x19[5] = unaff_x20[5];
    unaff_x19[4] = uVar4;
    unaff_x19[7] = uVar6;
    unaff_x19[6] = uVar5;
    uVar4 = unaff_x20[8];
    uVar6 = unaff_x20[0xb];
    uVar5 = unaff_x20[10];
    unaff_x19[9] = unaff_x20[9];
    unaff_x19[8] = uVar4;
    unaff_x19[0xb] = uVar6;
    unaff_x19[10] = uVar5;
    uVar4 = unaff_x20[0xc];
    uVar6 = unaff_x20[0xf];
    uVar5 = unaff_x20[0xe];
    unaff_x19[0xd] = unaff_x20[0xd];
    unaff_x19[0xc] = uVar4;
    unaff_x19[0xf] = uVar6;
    unaff_x19[0xe] = uVar5;
    uVar4 = unaff_x20[0x10];
    unaff_x19[0x11] = unaff_x20[0x11];
    unaff_x19[0x10] = uVar4;
    unaff_x19[0x12] = extraout_x8;
    *(uint8_t *)((uint8_t *)unaff_x19 + 0x98) = extraout_w9;
    sk_x_0034f8e4(auVar7, param_2, uVar1, uVar2, uVar3);
    sk_x_00459138();
    sk_x_004ac1d4();
}

/* FUN_0049f1d8 @ 0x0049f1d8   (est. sk_x_0049f1d8)
 * Ghidra: void FUN_0049f1d8(undefined8 *param_1,uint param_2,uint param_3)
 * Decodes a message length/count into a descriptor at param_1. For small sizes
 * (<0x32) it clears a byte at 0xb0, zeroes 0x98 bytes and stores a derived
 * alignment byte at 0x98; for larger sizes it clears word 0xa8, computes a new
 * size via sk_x_004aabb8 and records a "large" flag at 0xb0.
 * Confidence: medium
 * Notes: byte stores at word offsets 0x13/0x16 correspond to bytes 0x98/0xb0;
 *        param_2/param_3 are uint (32-bit) lengths. */
static void sk_x_0049f1d8(uint64_t *param_1, uint32_t param_2, uint32_t param_3)
{
    uint64_t extraout_x8;

    if (param_2 < 0x32) {
        if (0x31 < param_3) {
            *(uint8_t *)((uint8_t *)param_1 + 0xb0) = 0;
        }
        if (param_2 != 0) {
            sk_x_00114330(param_1, 0x98);
            *(uint8_t *)((uint8_t *)param_1 + 0x98) =
                (uint8_t)((((uint8_t)((uint32_t)(-(int32_t)param_2) >> 4) & 3)
                           + (int8_t)param_2 * -4) * 4);
        }
    }
    else {
        param_1[0x15] = 0;
        sk_x_004aabb8(param_2 - 0x32, 0);
        *param_1 = extraout_x8;
        if (0x31 < param_3) {
            *(uint8_t *)((uint8_t *)param_1 + 0xb0) = 1;
        }
    }
}

/* FUN_0049f264 @ 0x0049f264   (est. sk_x_0049f264)
 * Ghidra: void FUN_0049f264(void)
 * Swaps a set of fields between two structures obtained from the 16-byte pair
 * returned by sk_x_0034f2f4: copies 0x08/0x10/0x18/0x20 words from the hi
 * pointer to the lo pointer, releasing the displaced references via
 * sk_x_0036b270.
 * Confidence: medium
 * Notes: auVar6.lo/auVar6.hi are the two halves of the returned pair. */
static void sk_x_0049f264(void)
{
    uint64_t lVar1, lVar2, uVar3, uVar4, uVar5;
    cl4_result_t auVar6;

    auVar6 = sk_x_0034f2f4();
    lVar2 = auVar6.hi;
    lVar1 = auVar6.lo;
    uVar3 = *(uint64_t *)(lVar2 + 0x10);
    uVar4 = *(uint64_t *)(lVar2 + 8);
    *(uint64_t *)(lVar1 + 0x10) = *(uint64_t *)(lVar2 + 0x10);
    *(uint64_t *)(lVar1 + 8) = uVar4;
    uVar5 = *(uint64_t *)(lVar2 + 0x18);
    *(uint64_t *)(lVar1 + 0x20) = *(uint64_t *)(lVar2 + 0x20);
    *(uint64_t *)(lVar1 + 0x18) = uVar5;
    sk_x_0036b270(uVar4);
    sk_x_0036b270(uVar3);
}

/* FUN_0049f2ac @ 0x0049f2ac   (est. sk_x_0049f2ac)
 * Ghidra: void FUN_0049f2ac(void)
 * Object/state migration: acquires state via sk_x_0034b264, then copies the
 * 0x08 word from the returned pointer into x20's frame (releasing the old
 * value) and the 0x10/0x18/0x20 words from preserved x19 into x20's frame,
 * releasing displaced references.
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 are preserved callee-saved pointers; extraout_x1
 *        is the pointer output of sk_x_0034b264. */
static void sk_x_0049f2ac(void)
{
    uint64_t uVar1;
    uint64_t extraout_x1;   /* x1 pointer output of previous call */
    uint64_t *unaff_x19;    /* preserved x19 */
    uint64_t *unaff_x20;    /* preserved x20 */

    sk_x_0034b264();
    uVar1 = *(uint64_t *)((uint8_t *)unaff_x20 + 8);
    *(uint64_t *)((uint8_t *)unaff_x20 + 8) = *(uint64_t *)((uint8_t *)extraout_x1 + 8);
    sk_x_0036b270();
    sk_x_003a25d4(uVar1);
    uVar1 = *(uint64_t *)((uint8_t *)unaff_x20 + 0x10);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x10) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x10);
    sk_x_0036b270();
    sk_x_0036b118(uVar1);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x18) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x18);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x20) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x20);
}

/* FUN_0049f318 @ 0x0049f318   (est. sk_x_0049f318)
 * Ghidra: void FUN_0049f318(void)
 * State migration counterpart of sk_x_0049f2ac: acquires state, releases the
 * 0x08 word, then copies the 0x08/0x10/0x18/0x20 words from preserved x19 into
 * x20's frame, releasing the displaced 0x10 value.
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 are preserved callee-saved pointers; lVar1 is the
 *        pointer returned by sk_x_0034b264. */
static void sk_x_0049f318(void)
{
    uint64_t lVar1, uVar2, uVar3;
    uint64_t *unaff_x19;    /* preserved x19 */
    uint64_t *unaff_x20;    /* preserved x20 */

    lVar1 = sk_x_0034b264().lo;
    sk_x_003a25d4(*(uint64_t *)(lVar1 + 8));
    uVar2 = *(uint64_t *)((uint8_t *)unaff_x20 + 0x10);
    uVar3 = *(uint64_t *)((uint8_t *)unaff_x19 + 8);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x10) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x10);
    *(uint64_t *)((uint8_t *)unaff_x20 + 8) = uVar3;
    sk_x_0036b118(uVar2);
    uVar2 = *(uint64_t *)((uint8_t *)unaff_x19 + 0x18);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x20) = *(uint64_t *)((uint8_t *)unaff_x19 + 0x20);
    *(uint64_t *)((uint8_t *)unaff_x20 + 0x18) = uVar2;
}
/* FUN_0049f3e8 @ 0x0049f3e8   (est. sk_x_0049f3e8)
 * Ghidra: void FUN_0049f3e8(undefined8 param_1,undefined8 param_2,long param_3)
 * Message buffer refill/validation: reads a length byte at offset 0x50 and a
 * count at 0x54 of the context at param_3, computes an aligned source pointer,
 * and if the computed range is small enough invokes a handler pointer at 0x10
 * (with a breakpoint-assisted setup path when sk_x_004ab1e8 returns 0);
 * otherwise copies one word and releases via sk_x_0036b270.
 * Confidence: low
 * Notes: heavy register/masking arithmetic; unaff_x19/unaff_x20 are preserved
 *        callee-saved pointers; pcVar8 is the handler function pointer; the
 *        XOR masks are ~(low byte) masking for alignment. */
static void sk_x_0049f3e8(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uVar1, uVar6, uVar9, lVar5, lVar7;
    uint32_t uVar2;
    int32_t iVar3;
    uint64_t extraout_x8;     /* x8 output of previous call */
    uint64_t extraout_x16;    /* x16 output of previous call */
    uint64_t *unaff_x19;      /* preserved x19 */
    uint64_t *unaff_x20;      /* preserved x20 */
    uint64_t unaff_x30;       /* preserved x30 */
    void (*pcVar8)();         /* handler; called with 0 and with 2 args */
    cl4_result_t uVar4;       /* 16-byte result of sk_x_00350c5c */
    cl4_result_t auVar10;

    sk_x_00084220();
    uVar4 = sk_x_00350c5c();
    sk_x_004aa47c(uVar4.lo, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();
    sk_x_000a6f88();
    uVar2 = *(uint32_t *)(extraout_x16 + 0x50);
    lVar7 = *(uint64_t *)(extraout_x8 + 0x40);
    lVar5 = lVar7;
    if (*(int32_t *)(extraout_x16 + 0x54) == 0) {
        lVar5 = lVar7 + 1;
    }
    uVar6 = (uint64_t)uVar2 & 0xff;
    uVar9 = ~uVar6;
    uVar1 = lVar5 + (uint64_t)(uint8_t)uVar2;
    if (((uint32_t)uVar6 < 8 && (uVar2 & 0x100000) == 0) &&
        ((uVar1 & (uVar6 ^ UINT64_MAX)) + lVar7) < 0x19) {
        iVar3 = sk_x_004ab1e8();
        if (iVar3 == 0) {
            pcVar8 = *(void (**)())(extraout_x16 + 0x10);
            sk_x_0034bfb4();
            (*pcVar8)();
            sk_x_0034ba48();
            sk_x_000839d8();
        }
        else {
            auVar10 = sk_x_0009461c();
            sk_x_00117cc4(auVar10.lo, auVar10.hi, lVar5);
            pcVar8 = *(void (**)())(extraout_x16 + 0x10);
        }
        (*pcVar8)((uVar1 + (uint64_t)unaff_x19) & uVar9,
                  (uVar1 + (uint64_t)unaff_x20) & uVar9);
    }
    else {
        lVar5 = *unaff_x20;
        *unaff_x19 = lVar5;
        unaff_x19 = (uint64_t *)(lVar5 + ((uVar6 + 0x10) & uVar9));
        sk_x_0036b270();
    }
    sk_x_00084234(unaff_x19, unaff_x30);
}

/* FUN_0049f500 @ 0x0049f500   (est. sk_x_0049f500)
 * Ghidra: void FUN_0049f500(long param_1,long param_2)
 * Copies/advances a message: builds a length via sk_x_004aa47c and dispatches
 * through a handler function pointer read from (frame - 8) + 0x08, masking the
 * destination pointer to a byte alignment stored at offset 0x50 of the handler
 * frame (with a +1 step when the count at 0x54 is zero).
 * Confidence: low
 * Notes: unaff_x20 is a preserved callee-saved pointer; the handler pointer is
 *        at lVar3 + 0x08 and the mask byte at lVar3 + 0x50. */
static void sk_x_0049f500(uint64_t param_1, uint64_t param_2)
{
    int32_t iVar1;
    uint64_t uVar2;
    uint64_t extraout_x8;   /* x8 output of previous call */
    uint64_t *unaff_x20;    /* preserved x20 */
    uint64_t lVar3;

    uVar2 = sk_x_004aa47c(*(uint64_t *)(param_2 + 0x18), param_1, param_2,
                          *(uint64_t *)(param_2 + 0x10));
    sk_x_00377824(uVar2, extraout_x8);
    uVar2 = sk_x_00351d18();
    iVar1 = sk_x_000839f8(uVar2, 1);
    lVar3 = *(uint64_t *)((uint8_t *)unaff_x20 - 8);
    if (iVar1 == 0) {
        (*(void (**)(uint64_t))(lVar3 + 8))(param_1);
    }
    param_1 = *(uint64_t *)(lVar3 + 0x40) + param_1;
    if (*(int32_t *)(lVar3 + 0x54) == 0) {
        param_1 = param_1 + 1;
    }
    (*(void (**)(uint64_t))(lVar3 + 8))(
        (param_1 + (uint64_t)*(uint8_t *)(lVar3 + 0x50)) &
        ((uint64_t)*(uint8_t *)(lVar3 + 0x50) ^ UINT64_MAX));
}

/* FUN_0049f660 @ 0x0049f660   (est. sk_x_0049f660)
 * Ghidra: void FUN_0049f660(undefined8 param_1,undefined8 param_2,long param_3)
 * Message-dispatch refill: validates a length via sk_x_004aa8b0; on the
 * two-call path (unaff_w23 == 0) either invokes a handler and jumps to the
 * tail, or copies through a handler; otherwise invokes sk_x_00354070 to obtain
 * a 16-byte pair and an adjusted length, then maps it. Tail always releases
 * offset 0x18/0x28-adjacent state and calls a final handler.
 * Confidence: low
 * Notes: extraout_x8/_x9_00/_x9_01/_x8_00 are function pointers carried in
 *        registers from prior calls; unaff_w23 is a preserved flag register. */
static void sk_x_0049f660(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    int32_t iVar1;
    int32_t extraout_w8;
    int32_t unaff_w23;         /* preserved w23 flag */
    uint64_t extraout_x9, lVar3, extraout_x16;
    void (*extraout_x9_01)(void);      /* x9 handler from prior call */
    void (*extraout_x9_00)(void);      /* x9 handler from prior call */
    cl4_result_t (*extraout_x8)(void); /* x8 handler from prior call */
    void (*extraout_x8_00)(void);      /* x8 handler from prior call */
    cl4_result_t uVar2;        /* 16-byte result of sk_x_00350c5c */
    cl4_result_t auVar4;

    uVar2 = sk_x_00350c5c();
    sk_x_004aa47c(uVar2.lo, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();
    iVar1 = sk_x_004aa8b0();
    if (unaff_w23 == 0) {
        if (iVar1 == 0) {
            sk_x_0034bfb4();
            (*extraout_x9_01)();
            goto LAB_0049f720;
        }
        sk_x_003507e0(*(uint64_t *)(extraout_x16 + 8));
        auVar4 = (*extraout_x8)();
        iVar1 = *(int32_t *)(extraout_x16 + 0x54);
        lVar3 = *(uint64_t *)(extraout_x16 + 0x40);
    }
    else {
        if (iVar1 == 0) {
            sk_x_0034bfb4();
            (*extraout_x9_00)();
            sk_x_0034ba48();
            sk_x_000839d8();
            goto LAB_0049f720;
        }
        auVar4 = sk_x_00354070();
        lVar3 = extraout_x9;
        iVar1 = extraout_w8;
    }
    if (iVar1 == 0) {
        lVar3 = lVar3 + 1;
    }
    sk_x_0009461c(auVar4.lo, auVar4.hi, lVar3);
    sk_x_00117cc4();
LAB_0049f720:
    sk_x_004ac804(*(uint64_t *)(extraout_x16 + 0x18));
    sk_x_004aab30();
    (*extraout_x8_00)();
}

/* FUN_0049f75c @ 0x0049f75c   (est. sk_x_0049f75c)
 * Ghidra: void FUN_0049f75c(undefined8 param_1,undefined8 param_2,long param_3)
 * Message-dispatch refill variant: validates via sk_x_004aa914; on failure
 * invokes a breakpoint-setup handler; on success obtains a 16-byte pair from
 * sk_x_00354070, computes an adjusted length and maps it. Tail releases the
 * 0x20 field of the frame pointer and calls a final handler.
 * Confidence: low
 * Notes: extraout_x8/_x9_00 are handler function pointers carried from prior
 *        calls; extraout_x17 is a register address used for the frame base. */
static void sk_x_0049f75c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t lVar1, lVar4;
    int32_t iVar2;
    int32_t extraout_w8;
    uint64_t extraout_x9, extraout_x17;
    void (*extraout_x8)(void);
    void (*extraout_x9_00)(void);
    cl4_result_t uVar3;        /* 16-byte result of sk_x_00350c5c */
    cl4_result_t auVar5;

    uVar3 = sk_x_00350c5c();
    sk_x_004aa47c(uVar3.lo, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();
    iVar2 = (int32_t)sk_x_004aa914().lo;
    lVar4 = *(uint64_t *)(extraout_x17 - 8);
    if (iVar2 == 0) {
        sk_x_0034bfb4();
        (*extraout_x9_00)();
        sk_x_0034ba48();
        sk_x_000839d8();
    }
    else {
        auVar5 = sk_x_00354070();
        lVar1 = extraout_x9;
        if (extraout_w8 == 0) {
            lVar1 = extraout_x9 + 1;
        }
        sk_x_0009461c(auVar5.lo, auVar5.hi, lVar1);
        sk_x_00117cc4();
    }
    sk_x_004ac804(*(uint64_t *)(lVar4 + 0x20));
    sk_x_004aab30();
    (*extraout_x8)();
}

/* FUN_0049f810 @ 0x0049f810   (est. sk_x_0049f810)
 * Ghidra: void FUN_0049f810(undefined8 param_1,undefined8 param_2,long param_3)
 * Message-dispatch refill twin of sk_x_0049f660: identical structure, but the
 * tail releases the 0x28 field of the context instead of 0x18. Validates via
 * sk_x_004aa8b0, copies through handlers or sk_x_00354070, then maps.
 * Confidence: low
 * Notes: extraout_x8/_x9_00/_x9_01/_x8_00 are register-carried function
 *        pointers; unaff_w23 is a preserved flag register. */
static void sk_x_0049f810(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    int32_t iVar1;
    int32_t extraout_w8;
    int32_t unaff_w23;         /* preserved w23 flag */
    uint64_t extraout_x9, lVar3, extraout_x16;
    void (*extraout_x9_01)(void);
    void (*extraout_x9_00)(void);
    cl4_result_t (*extraout_x8)(void);
    void (*extraout_x8_00)(void);
    cl4_result_t uVar2;        /* 16-byte result of sk_x_00350c5c */
    cl4_result_t auVar4;

    uVar2 = sk_x_00350c5c();
    sk_x_004aa47c(uVar2.lo, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();
    iVar1 = sk_x_004aa8b0();
    if (unaff_w23 == 0) {
        if (iVar1 == 0) {
            sk_x_0034bfb4();
            (*extraout_x9_01)();
            goto LAB_0049f8d0;
        }
        sk_x_003507e0(*(uint64_t *)(extraout_x16 + 8));
        auVar4 = (*extraout_x8)();
        iVar1 = *(int32_t *)(extraout_x16 + 0x54);
        lVar3 = *(uint64_t *)(extraout_x16 + 0x40);
    }
    else {
        if (iVar1 == 0) {
            sk_x_0034bfb4();
            (*extraout_x9_00)();
            sk_x_0034ba48();
            sk_x_000839d8();
            goto LAB_0049f8d0;
        }
        auVar4 = sk_x_00354070();
        lVar3 = extraout_x9;
        iVar1 = extraout_w8;
    }
    if (iVar1 == 0) {
        lVar3 = lVar3 + 1;
    }
    sk_x_0009461c(auVar4.lo, auVar4.hi, lVar3);
    sk_x_00117cc4();
LAB_0049f8d0:
    sk_x_004ac804(*(uint64_t *)(extraout_x16 + 0x28));
    sk_x_004aab30();
    (*extraout_x8_00)();
}

/* FUN_0049f90c @ 0x0049f90c   (est. sk_x_0049f90c)
 * Ghidra: ulong FUN_0049f90c(uint *param_1,uint param_2,long param_3)
 * Computes the total size (in 8-byte words) of a variable-length message whose
 * data starts at param_1. Reads a length byte (0x50) and count (0x54) from the
 * context, then scans the buffer: decodes a length-prefixed element of up to 4
 * bytes (width chosen by a 2-bit alignment), and either returns
 * count + value + 1 directly or resolves a fallback length via sk_x_000839f8.
 * Confidence: medium
 * Notes: returns ulong (uint64_t); the switch selects 1/2/3/4-byte element
 *        reads at *param_1 based on a 2-bit alignment uVar10; the byte-mask
 *        arithmetic computes element length from the encoded prefix. */
static uint64_t sk_x_0049f90c(uint32_t *param_1, uint32_t param_2, uint64_t param_3)
{
    uint64_t lVar1, uVar2, uVar7, uVar9;
    uint32_t uVar3, uVar4, uVar8, uVar10, uVar11;
    int32_t iVar5;
    uint64_t uVar6;
    uint64_t extraout_x8;    /* x8 output of previous call */
    uint64_t extraout_x16;   /* x16 output of previous call */

    sk_x_004aa47c(param_1, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();
    uVar6 = sk_x_0034e34c();
    uVar4 = *(uint32_t *)(extraout_x16 + 0x54);
    uVar3 = 0;
    if (uVar4 != 0) {
        uVar3 = uVar4 - 1;
    }
    uVar9 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    uVar7 = *(uint64_t *)(extraout_x8 + 0x40) + uVar9;
    uVar2 = uVar7;
    if (uVar4 == 0) {
        uVar2 = uVar7 + 1;
    }
    if (param_2 == 0) {
LAB_0049fa34:
        uVar7 = 0;
    }
    else {
        if (uVar4 <= param_2 && param_2 - uVar4 != 0) {
            lVar1 = (uVar2 & (uVar9 ^ UINT64_MAX)) + *(uint64_t *)(extraout_x8 + 0x40);
            uVar10 = (uint32_t)lVar1;
            uVar8 = uVar10 << 3;
            if (uVar10 < 4) {
                uVar11 = ((param_2 - uVar4) +
                          ~(UINT32_MAX << (uVar8 & 0x1f)) >> (uVar8 & 0x1f)) + 1;
                if (0xff < uVar11) {
                    if (uVar11 >> 0x10 == 0) {
                        uVar11 = (uint32_t)*(uint16_t *)((uint8_t *)param_1 + lVar1);
                    }
                    else {
                        uVar11 = *(uint32_t *)((uint8_t *)param_1 + lVar1);
                    }
                    goto LAB_0049f99c;
                }
                if (1 < uVar11) goto LAB_0049f998;
            }
            else {
LAB_0049f998:
                uVar11 = (uint32_t)*(uint8_t *)((uint8_t *)param_1 + lVar1);
LAB_0049f99c:
                if (uVar11 != 0) {
                    uVar3 = 0;
                    if (uVar10 < 4) {
                        uVar3 = (uVar11 - 1) << (uVar8 & 0x1f);
                    }
                    if (uVar10 == 0) {
                        uVar8 = 0;
                    }
                    else {
                        uVar8 = 4;
                        if (uVar10 < 4) {
                            uVar8 = uVar10;
                        }
                        switch (uVar8) {
                        default:
                            uVar8 = (uint32_t)*(uint8_t *)param_1;
                            break;
                        case 2:
                            uVar8 = (uint32_t)*(uint16_t *)param_1;
                            break;
                        case 3:
                            uVar8 = (uint32_t)((uint8_t *)param_1)[0]
                                  | ((uint32_t)((uint8_t *)param_1)[1] << 8)
                                  | ((uint32_t)((uint8_t *)param_1)[2] << 16);
                            break;
                        case 4:
                            uVar8 = *param_1;
                        }
                    }
                    return (uint64_t)(uVar4 + (uVar8 | uVar3) + 1);
                }
            }
            if (uVar4 == 0) goto LAB_0049fa34;
        }
        if (uVar3 != uVar4) {
            uVar7 = sk_x_000839f8((uint64_t)(uVar7 + (uint64_t)param_1) & ~uVar9,
                                  uVar4, uVar6);
            return uVar7;
        }
        iVar5 = sk_x_000839f8(param_1, uVar4, uVar6);
        uVar3 = 0;
        if (iVar5 != 0) {
            uVar3 = (uint32_t)(iVar5 - 1);
        }
        uVar7 = (uint64_t)uVar3;
    }
    return uVar7;
}
/* FUN_0049fcf8 @ 0x0049fcf8   (est. sk_x_0049fcf8)
 * Ghidra: void FUN_0049fcf8(void)
 * Thin wrapper that forwards unconditionally to the shared routine at 0x00021480.
 * No inputs, outputs, or side effects of its own.
 * Confidence: high
 * Notes: single direct tail call. */
static void sk_x_0049fcf8(void)
{
    sk_x_00021480();
    return;
}

/* FUN_0049fd10 @ 0x0049fd10   (est. sk_x_0049fd10)
 * Ghidra: void FUN_0049fd10(void)
 * Thin wrapper that forwards unconditionally to the shared routine at 0x00021480.
 * No inputs, outputs, or side effects of its own.
 * Confidence: high
 * Notes: single direct tail call; identical shape to sk_x_0049fcf8. */
static void sk_x_0049fd10(void)
{
    sk_x_00021480();
    return;
}

/* FUN_0049fd28 @ 0x0049fd28   (est. sk_x_0049fd28)
 * Ghidra: void FUN_0049fd28(long param_1)
 * Registers the given object context (param_1) by pushing its +0x18/+0x10 words
 * through sk_x_004633e0, then queries a metadata handle via sk_x_00377824(0x13f).
 * If the returned high word (a size/level) is below 0x40, it links the object
 * into a doubly-linked list at (lo-8) and runs two finalization steps.
 * Confidence: medium
 * Notes: 16-byte pair return modeled as cl4_result_t (auVar2). */
static void sk_x_0049fd28(uint64_t param_1)
{
    uint64_t *head_ptr;   /* Ghidra plVar1 */
    cl4_result_t result;  /* Ghidra auVar2 */

    sk_x_004633e0(param_1, *(uint64_t *)(param_1 + 0x18), *(uint64_t *)(param_1 + 0x10));
    result = sk_x_00377824(0x13f);
    if (result.hi < 0x40) {
        head_ptr = (uint64_t *)(result.lo - 8);
        sk_x_00351244(head_ptr, result.hi, *head_ptr + 0x40);
        sk_x_0036851c();
        sk_x_00019858();
    }
    return;
}

/* FUN_0049fd8c @ 0x0049fd8c   (est. sk_x_0049fd8c)
 * Ghidra: void FUN_0049fd8c(undefined8 param_1,undefined8 param_2,long param_3)
 * Dispatches a permission/object operation on context param_3: pulls a per-state
 * count from register outputs of sk_x_00377824 (x8->+0x40, x16->+0x54/+0x50),
 * increments the count when the +0x54 field is zero, and — when the +0x50
 * capability-class/low-bit checks pass and the count stays under 0x19 — either
 * emits a fault report (sk_x_0009461c/sk_x_00117cc4) or invokes an indirect
 * handler and tears the operation down; otherwise routes to sk_x_004ac46c.
 * Confidence: low
 * Notes: heavy register-calling-convention artifacts (extraout_x8/x16, code*
 * extraout_x8_00 whose value Ghidra could not trace). */
static void sk_x_0049fd8c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uvar2;            /* Ghidra uVar2 */
    uint64_t x8_state;         /* Ghidra extraout_x8 (x8 output of FUN_00377824) */
    uint64_t x16_state;        /* Ghidra extraout_x16 (x16 output of FUN_00377824) */
    void (*handler)(void);     /* Ghidra extraout_x8_00 (indirect target in x8) */
    uint64_t uvar3;            /* Ghidra uVar3 */
    int32_t iret;              /* Ghidra iVar1 */
    cl4_result_t result;       /* Ghidra auVar4 */

    uvar2 = sk_x_00350c5c().lo;
    sk_x_004aa47c(uvar2, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();           /* leaves x8 -> x8_state, x16 -> x16_state */
    uvar3 = *(uint64_t *)(x8_state + 0x40);
    if (*(int32_t *)(x16_state + 0x54) == 0) {
        uvar3 = uvar3 + 1;
    }
    if (((*(uint32_t *)(x16_state + 0x50) & 0xff) < 8 &&
         (*(uint32_t *)(x16_state + 0x50) & 0x100000) == 0) && uvar3 < 0x19) {
        iret = sk_x_004ab1e8();
        if (iret != 0) {
            result = sk_x_0009461c();
            sk_x_00117cc4(result.lo, result.hi, uvar3);
            return;
        }
        sk_x_0034bfb4(*(uint64_t *)(x16_state + 0x10));
        handler();             /* indirect call through x8 (extraout_x8_00) */
        sk_x_0034ba48();
        sk_x_000839d8();
    } else {
        sk_x_004ac46c();
    }
    return;
}

/* FUN_0049fe68 @ 0x0049fe68   (est. sk_x_0049fe68)
 * Ghidra: void FUN_0049fe68(undefined8 param_1,long param_2)
 * Validates an operation permit on context param_2 via sk_x_000839f8(...,1).
 * When the check succeeds it returns early; on failure it dispatches through a
 * vtable-like slot at (incoming-x20 - 8) + 8, passing param_1 to the handler.
 * Confidence: low
 * Notes: indirect-jump dispatch at 0x0049fedc not recovered (treated as call);
 * unaff_x20 is an incoming-register artifact; extraout_x8 passed into
 * FUN_00377824 is a Ghidra register artifact. */
static void sk_x_0049fe68(uint64_t param_1, uint64_t param_2)
{
    uint64_t uvar2;                     /* Ghidra uVar2 */
    uint64_t x8_out;                    /* Ghidra extraout_x8 (register artifact) */
    uint64_t x20_in;                    /* Ghidra unaff_x20 (incoming register) */
    void (*handler)(uint64_t);          /* indirect dispatch target */
    int32_t iret;                       /* Ghidra iVar1 */

    uvar2 = sk_x_004aa47c(*(uint64_t *)(param_2 + 0x18), param_1, param_2,
                          *(uint64_t *)(param_2 + 0x10));
    sk_x_00377824(uvar2, x8_out);
    uvar2 = sk_x_00351d18();
    iret = sk_x_000839f8(uvar2, 1);
    if (iret != 0) {
        return;
    }
    /* WARNING: could not recover jumptable at 0x0049fedc; indirect jump as call */
    handler = *(void (**)(uint64_t))(*(uint64_t *)(x20_in - 8) + 8);
    handler(param_1);
    return;
}

/* FUN_0049ff7c @ 0x0049ff7c   (est. sk_x_0049ff7c)
 * Ghidra: void FUN_0049ff7c(undefined8 param_1,undefined8 param_2,long param_3)
 * Object/operation dispatch on context param_3: consults a state from register
 * outputs of sk_x_00377824 and a permit result from sk_x_004aa8b0, then on the
 * success paths raises a fault report (sk_x_0009461c/sk_x_00117cc4 with a count
 * derived from state +0x54/+0x40) or invokes an indirect handler; the failure
 * path tears down via sk_x_0034ba48/sk_x_000839d8.
 * Confidence: low
 * Notes: unaff_w23 is an incoming-register artifact; extraout_x8/x8_00/x8_01/x9/
 * w8/x16 are register outputs Ghidra could not trace through the indirect call. */
static void sk_x_0049ff7c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    int32_t iret;                 /* Ghidra iVar1 */
    uint64_t uvar2;               /* Ghidra uVar2 */
    int32_t w8_out;               /* Ghidra extraout_w8 */
    cl4_result_t (*x8_fn)(void);  /* Ghidra extraout_x8 (returns 16-byte pair) */
    void (*x8_fn_0)(void);        /* Ghidra extraout_x8_00 */
    void (*x8_fn_1)(void);        /* Ghidra extraout_x8_01 */
    uint64_t x9_out;              /* Ghidra extraout_x9 */
    uint64_t lvar3;               /* Ghidra lVar3 */
    uint64_t x16_state;           /* Ghidra extraout_x16 */
    int32_t w23_in;               /* Ghidra unaff_w23 (incoming register) */
    cl4_result_t result;          /* Ghidra auVar4 */

    uvar2 = sk_x_00350c5c().lo;
    sk_x_004aa47c(uvar2, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();              /* leaves x16 -> x16_state */
    iret = sk_x_004aa8b0();
    if (w23_in == 0) {
        if (iret == 0) {
            sk_x_0034bfb4(*(uint64_t *)(x16_state + 0x18));
            x8_fn_1();            /* indirect call through x8 */
            return;
        }
        sk_x_003507e0(*(uint64_t *)(x16_state + 8));
        result = x8_fn();
        iret = *(int32_t *)(x16_state + 0x54);
        lvar3 = *(uint64_t *)(x16_state + 0x40);
    } else {
        if (iret == 0) {
            sk_x_0034bfb4(*(uint64_t *)(x16_state + 0x10));
            x8_fn_0();            /* indirect call through x8 */
            sk_x_0034ba48();
            sk_x_000839d8();
            return;
        }
        result = sk_x_00354070();
        lvar3 = x9_out;
        iret = w8_out;
    }
    if (iret == 0) {
        lvar3 = lvar3 + 1;
    }
    sk_x_0009461c(result.lo, result.hi, lvar3);
    sk_x_00117cc4();
    return;
}

/* FUN_004a0058 @ 0x004a0058   (est. sk_x_004a0058)
 * Ghidra: void FUN_004a0058(undefined8 param_1,undefined8 param_2,long param_3)
 * Object/operation dispatch on context param_3: obtains a 16-byte result from
 * sk_x_004aa914 and a state pointer from the x17 register output of
 * sk_x_00377824. When the result's low word is nonzero it emits a fault report
 * (sk_x_0009461c/sk_x_00117cc4) with a count from state +0x40 (+1 if +0x54 is
 * zero); otherwise it invokes an indirect handler at (state)+0x20 and tears down.
 * Confidence: low
 * Notes: extraout_x17 register artifact; indirect call through (lVar3 + 0x20). */
static void sk_x_004a0058(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uvar1;            /* Ghidra uVar1 */
    uint64_t x17_state;        /* Ghidra extraout_x17 */
    uint64_t lvar2;            /* Ghidra lVar2 */
    uint64_t lvar3;            /* Ghidra lVar3 */
    cl4_result_t result;       /* Ghidra auVar4 */

    uvar1 = sk_x_00350c5c().lo;
    sk_x_004aa47c(uvar1, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();           /* leaves x17 -> x17_state */
    result = sk_x_004aa914();
    lvar3 = *(uint64_t *)(x17_state - 8);
    if ((uint32_t)result.lo != 0) {
        lvar2 = *(uint64_t *)(lvar3 + 0x40);
        if (*(int32_t *)(lvar3 + 0x54) == 0) {
            lvar2 = lvar2 + 1;
        }
        sk_x_0009461c(result.lo, result.hi, lvar2);
        sk_x_00117cc4();
        return;
    }
    ((void (*)(void))(*(uint64_t *)(lvar3 + 0x20)))();
    sk_x_0034ba48();
    sk_x_000839d8();
    return;
}

/* FUN_004a00f4 @ 0x004a00f4   (est. sk_x_004a00f4)
 * Ghidra: void FUN_004a00f4(undefined8 param_1,undefined8 param_2,long param_3)
 * Object/operation dispatch on context param_3; structurally identical to
 * sk_x_0049ff7c but reads the indirect-handler argument from state +0x28 (and
 * +0x20 on the failure path) instead of +0x18/+0x10.
 * Confidence: low
 * Notes: unaff_w23 incoming-register artifact; extraout_w8/x8/x8_00/x8_01/x9/x16
 * register outputs not traceable through the indirect call. */
static void sk_x_004a00f4(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    int32_t iret;                 /* Ghidra iVar1 */
    uint64_t uvar2;               /* Ghidra uVar2 */
    int32_t w8_out;               /* Ghidra extraout_w8 */
    cl4_result_t (*x8_fn)(void);  /* Ghidra extraout_x8 */
    void (*x8_fn_0)(void);        /* Ghidra extraout_x8_00 */
    void (*x8_fn_1)(void);        /* Ghidra extraout_x8_01 */
    uint64_t x9_out;              /* Ghidra extraout_x9 */
    uint64_t lvar3;               /* Ghidra lVar3 */
    uint64_t x16_state;           /* Ghidra extraout_x16 */
    int32_t w23_in;               /* Ghidra unaff_w23 */
    cl4_result_t result;          /* Ghidra auVar4 */

    uvar2 = sk_x_00350c5c().lo;
    sk_x_004aa47c(uvar2, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();              /* leaves x16 -> x16_state */
    iret = sk_x_004aa8b0();
    if (w23_in == 0) {
        if (iret == 0) {
            sk_x_0034bfb4(*(uint64_t *)(x16_state + 0x28));
            x8_fn_1();            /* indirect call through x8 */
            return;
        }
        sk_x_003507e0(*(uint64_t *)(x16_state + 8));
        result = x8_fn();
        iret = *(int32_t *)(x16_state + 0x54);
        lvar3 = *(uint64_t *)(x16_state + 0x40);
    } else {
        if (iret == 0) {
            sk_x_0034bfb4(*(uint64_t *)(x16_state + 0x20));
            x8_fn_0();            /* indirect call through x8 */
            sk_x_0034ba48();
            sk_x_000839d8();
            return;
        }
        result = sk_x_00354070();
        lvar3 = x9_out;
        iret = w8_out;
    }
    if (iret == 0) {
        lvar3 = lvar3 + 1;
    }
    sk_x_0009461c(result.lo, result.hi, lvar3);
    sk_x_00117cc4();
    return;
}

/* FUN_004a01d0 @ 0x004a01d0   (est. sk_x_004a01d0)
 * Ghidra: int FUN_004a01d0(uint *param_1,uint param_2,long param_3)
 * Scans the bitmap/table at param_1 for the entry addressed by param_2. Using
 * state from register outputs of sk_x_00377824 (x8->+0x40 base/count, x16->+0x54
 * capacity), it decodes an element of the size given by the base's low 2 bits
 * (1/2/3/4 bytes) and returns its encoded value; on short/invalid elements it
 * falls back to a lookup via sk_x_000839f8 and returns the found index (or 0).
 * Confidence: low
 * Notes: Ghidra uint3 rendered as an inline 3-byte little-endian load; extraout_x8
 * /extraout_x16 register artifacts; goto structure preserved (LAB_004a02c8 ->
 * byte_load_fallback, LAB_004a024c -> byte_load). */
static int32_t sk_x_004a01d0(uint32_t *param_1, uint32_t param_2, uint64_t param_3)
{
    uint32_t uvar1;            /* Ghidra uVar1 */
    uint32_t uvar2;            /* Ghidra uVar2 */
    uint32_t uvar3;            /* Ghidra uVar3 */
    int32_t iret4;             /* Ghidra iVar4 */
    uint64_t uvar5;            /* Ghidra uVar5 */
    uint64_t x8_state;         /* Ghidra extraout_x8 */
    uint32_t uvar6;            /* Ghidra uVar6 */
    uint64_t uvar7;            /* Ghidra uVar7 */
    uint32_t uvar8;            /* Ghidra uVar8 */
    uint64_t x16_state;        /* Ghidra extraout_x16 */

    sk_x_004aa47c(param_1, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    sk_x_00377824();           /* leaves x8 -> x8_state, x16 -> x16_state */
    uvar5 = sk_x_0034e34c();
    uvar2 = *(uint32_t *)(x16_state + 0x54);
    uvar1 = 0;
    if (uvar2 != 0) {
        uvar1 = uvar2 - 1;
    }
    uvar7 = *(uint64_t *)(x8_state + 0x40);
    if (uvar2 == 0) {
        uvar7 = uvar7 + 1;
    }
    if (param_2 == 0) {
        return 0;
    }
    if (param_2 < uvar1 || param_2 - uvar1 == 0) {
        goto byte_load_fallback;      /* LAB_004a02c8 */
    }
    uvar6 = (uint32_t)uvar7;
    uvar3 = uvar6 << 3;
    if (uvar6 < 4) {
        uvar8 = ((param_2 - uvar1) + ~(-1u << (uvar3 & 0x1f)) >> (uvar3 & 0x1f)) + 1;
        if (uvar8 < 0x100) {
            if (uvar8 < 2) {
                goto byte_load_fallback;
            }
            goto byte_load;           /* LAB_004a024c */
        }
        if (uvar8 >> 0x10 == 0) {
            uvar8 = (uint32_t)*(uint16_t *)((uint64_t)param_1 + uvar7);
        } else {
            uvar8 = *(uint32_t *)((uint64_t)param_1 + uvar7);
        }
    } else {
byte_load:                            /* LAB_004a024c */
        uvar8 = (uint32_t)*(uint8_t *)((uint64_t)param_1 + uvar7);
    }
    if (uvar8 != 0) {
        uvar2 = 0;
        if (uvar6 < 4) {
            uvar2 = (uvar8 - 1) << (uvar3 & 0x1f);
        }
        if (uvar6 != 0) {
            uvar3 = 4;
            if (uvar6 < 4) {
                uvar3 = uvar6;
            }
            switch (uvar3) {
            default:
                /* 1 byte */
                uvar7 = (uint64_t)*(uint8_t *)param_1;
                break;
            case 2:
                /* 2 bytes */
                uvar7 = (uint64_t)*(uint16_t *)param_1;
                break;
            case 3:
                /* 3 bytes, little-endian (Ghidra uint3) */
                uvar7 = (uint64_t)((uint32_t)*(uint8_t *)param_1 |
                                   ((uint32_t)*(uint8_t *)((uint64_t)param_1 + 1) << 8) |
                                   ((uint32_t)*(uint8_t *)((uint64_t)param_1 + 2) << 16));
                break;
            case 4:
                /* 4 bytes */
                uvar7 = (uint64_t)*param_1;
            }
        }
        return (int32_t)(uvar1 + (((uint32_t)uvar7 | uvar2) + 1));
    }
byte_load_fallback:                   /* LAB_004a02c8 */
    if (uvar2 < 2) {
        return 0;
    }
    iret4 = sk_x_000839f8(param_1, uvar2, uvar5);
    if (iret4 != 0) {
        return iret4 - 1;
    }
    return 0;
}

/* FUN_004a058c @ 0x004a058c   (est. sk_x_004a058c)
 * Ghidra: void FUN_004a058c(undefined8 param_1,undefined8 param_2,long param_3)
 * Registers context param_3 via sk_x_004aa47c, then forwards (param_1, param_2,
 * 1, uvar1) to the shared cleanup/release routine sk_x_000839d8 where uvar1 is
 * the value returned by sk_x_00377824.
 * Confidence: medium
 * Notes: straightforward four-argument forwarding. */
static void sk_x_004a058c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uvar1;   /* Ghidra uVar1 */

    sk_x_004aa47c(param_1, *(uint64_t *)(param_3 + 0x18), *(uint64_t *)(param_3 + 0x10));
    uvar1 = sk_x_00377824().lo;
    sk_x_000839d8(param_1, param_2, 1, uvar1);
    return;
}

/* FUN_004a05d0 @ 0x004a05d0   (est. sk_x_004a05d0)
 * Ghidra: void FUN_004a05d0(void)
 * Runs three sequential state/finalization steps: sk_x_0034f2f4, sk_x_004abf50,
 * and sk_x_0036b270. No arguments or outputs.
 * Confidence: medium
 * Notes: three chained direct calls, no branching. */
static void sk_x_004a05d0(void)
{
    sk_x_0034f2f4();
    sk_x_004abf50();
    sk_x_0036b270();
    return;
}

/* FUN_004a061c @ 0x004a061c   (est. sk_x_004a061c)
 * Ghidra: void FUN_004a061c(void)
 * Fetches a global pointer slot via sk_x_004ab2dc, saves its current value,
 * overwrites it with a register leftover (extraout_x8), then passes the saved
 * value (with bit 2 cleared) to sk_x_0036b118.
 * Confidence: low
 * Notes: extraout_x8 is an untraceable register artifact written into the slot. */
static void sk_x_004a061c(void)
{
    uint64_t *slot;    /* Ghidra puVar1 */
    uint64_t x8_out;   /* Ghidra extraout_x8 (register artifact) */
    uint64_t old;      /* Ghidra uVar2 */

    slot = (uint64_t *)sk_x_004ab2dc();
    old = *slot;
    *slot = x8_out;
    sk_x_0036b118(old & 0xffffffffffffffb);
    return;
}

/* FUN_004a07e4 @ 0x004a07e4   (est. sk_x_004a07e4)
 * Ghidra: void FUN_004a07e4(long param_1)
 * Calls sk_x_00377dcc(0x13f, *(param_1 + 0x18)); if the x1 register output is
 * below 0x40 it obtains a 16-byte pair from sk_x_00351244 and runs
 * sk_x_003728b8(lo, hi, 1) followed by sk_x_00019858.
 * Confidence: low
 * Notes: extraout_x1 register artifact; 16-byte pair modeled as cl4_result_t. */
static void sk_x_004a07e4(uint64_t param_1)
{
    uint64_t x1_out;       /* Ghidra extraout_x1 */
    cl4_result_t result;   /* Ghidra auVar1 */

    sk_x_00377dcc(0x13f, *(uint64_t *)(param_1 + 0x18));
    if (x1_out < 0x40) {
        result = sk_x_00351244();
        sk_x_003728b8(result.lo, result.hi, 1);
        sk_x_00019858();
    }
    return;
}

/* FUN_004a0858 @ 0x004a0858   (est. sk_x_004a0858)
 * Ghidra: void FUN_004a0858(void)
 * Runs a sequence of helpers (sk_x_004ac384, sk_x_0034b7e4, sk_x_0035944c) that
 * leave several registers and condition flags set. If the flags indicate the
 * "lower-or-same" (unsigned <=) result, x10 < 0x19, and w11 == 0, it invokes an
 * indirect handler at x8 + 0x10; otherwise it calls sk_x_004ab5ec(*x1).
 * Confidence: low
 * Notes: extraout_x1/x8/x10/x16, extraout_w11, and in_ZR/in_CY are condition-
 * flag/register artifacts of sk_x_0035944c; the !CY||ZR test is unsigned <=. */
static void sk_x_004a0858(void)
{
    uint64_t *x1_out;        /* Ghidra extraout_x1 */
    uint64_t x8_out;         /* Ghidra extraout_x8 */
    uint64_t x10_out;        /* Ghidra extraout_x10 */
    int32_t w11_out;         /* Ghidra extraout_w11 */
    uint64_t x16_out;        /* Ghidra extraout_x16 */
    int carry;               /* Ghidra in_CY */
    int zero;                /* Ghidra in_ZR */
    void (*handler)(void);   /* indirect target */

    sk_x_004ac384();
    sk_x_0034b7e4();
    sk_x_0035944c(x16_out);  /* sets x1/x8/x10/w11 and condition flags */
    if (((!carry || zero) && x10_out < 0x19) && w11_out == 0) {
        handler = *(void (**)(void))(x8_out + 0x10);
        handler();
    } else {
        sk_x_004ab5ec(*x1_out);
    }
    return;
}

/* FUN_004a0934 @ 0x004a0934   (est. sk_x_004a0934)
 * Ghidra: void FUN_004a0934(void)
 * Calls sk_x_004ac384 and sk_x_0034b07c (whose x16 register output is captured),
 * then invokes the indirect handler stored at x16 + 0x18.
 * Confidence: low
 * Notes: extraout_x16 register artifact; indirect call through (x16 + 0x18). */
static void sk_x_004a0934(void)
{
    uint64_t x16_out;        /* Ghidra extraout_x16 */
    void (*handler)(void);   /* indirect target */

    sk_x_004ac384();
    sk_x_0034b07c();         /* leaves x16 -> x16_out */
    handler = *(void (**)(void))(x16_out + 0x18);
    handler();
    return;
}
/* FUN_004a0970 @ 0x4a0970   (est. sk_x_004a0970)
 * Ghidra: void FUN_004a0970(void)
 * Runs the standard cL4 dispatch preamble (sk_x_004ac384, sk_x_0034b07c) and
 * then dispatches through the method-slot at offset +0x20 of the context/method
 * table base carried in scratch register x16. No args, no return; side effects
 * are those of the dispatched method.
 * Confidence: low
 * Notes: extraout_x16 is a Ghidra register artifact (x16 scratch return from the
 * preceding call) used as a method-table base. */
static void sk_x_004a0970(void)
{
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base from x16) */

    sk_x_004ac384();
    sk_x_0034b07c();
    (*(void (**)(void))(extraout_x16 + 0x20))();
    return;
}

/* FUN_004a09ac @ 0x4a09ac   (est. sk_x_004a09ac)
 * Ghidra: void FUN_004a09ac(void)
 * Identical dispatch pattern to sk_x_004a0970, but dispatches through the
 * method-slot at offset +0x28 instead of +0x20. Runs the same two-step preamble.
 * Confidence: low
 * Notes: extraout_x16 is a Ghidra register artifact (method-table base from x16). */
static void sk_x_004a09ac(void)
{
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base from x16) */

    sk_x_004ac384();
    sk_x_0034b07c();
    (*(void (**)(void))(extraout_x16 + 0x28))();
    return;
}

/* FUN_004a0a94 @ 0x4a0a94   (est. sk_x_004a0a94)
 * Ghidra: undefined8 FUN_004a0a94(void)
 * Reads a variable-width object tag from a freshly returned cl4_result (pair)
 * and looks it up. The width of the tag read (byte/halfword/word) is selected by
 * the scratch size register w10; a non-zero tag is shifted by a bit position from
 * w8 and combined with an aligned length, then passed to sk_x_0006b438 as a key.
 * If the returned pair's hi word is zero, returns 0 directly.
 * Confidence: low
 * Notes: extraout_w10 (size), extraout_x9 (offset), extraout_w8 (shift) are Ghidra
 * register artifacts from the preceding call. auVar7 is the cl4_result pair. */
static uint64_t sk_x_004a0a94(void)
{
    uint32_t uVar6;
    uint32_t *puVar2;
    uint64_t uVar3;
    uint32_t extraout_w8;    /* Ghidra: extraout_w8 (bit shift) */
    uint32_t uVar4;
    uint64_t extraout_x9;    /* Ghidra: extraout_x9 (tag offset) */
    uint32_t uVar1;
    uint32_t extraout_w10;   /* Ghidra: extraout_w10 (tag width selector) */
    uint64_t uVar5;
    cl4_result_t auVar7;

    auVar7 = sk_x_004abf7c();
    puVar2 = (uint32_t *)auVar7.lo;
    if (extraout_w10 < 0x100) {
        if (extraout_w10 < 2) goto LAB_004a0ab8;
        uVar6 = (uint32_t)*(uint8_t *)((uint64_t)puVar2 + extraout_x9);
    } else if (extraout_w10 >> 0x10 == 0) {
        uVar6 = (uint32_t)*(uint16_t *)((uint64_t)puVar2 + extraout_x9);
    } else {
        uVar6 = *(uint32_t *)((uint64_t)puVar2 + extraout_x9);
    }
    if (uVar6 != 0) {
        uVar4 = (uint32_t)extraout_x9;
        uVar1 = 0;
        if (uVar4 < 4) {
            uVar1 = (uVar6 - 1) << (extraout_w8 & 0x1f);
        }
        uVar5 = extraout_x9;
        if (uVar4 != 0) {
            uVar6 = 4;
            if (uVar4 < 4) {
                uVar6 = uVar4;
            }
            switch (uVar6) {
            default:
                uVar5 = (uint64_t)(uint8_t)*puVar2;
                break;
            case 2:
                uVar5 = (uint64_t)(uint16_t)*puVar2;
                break;
            case 3:
                uVar5 = (uint64_t)((uint32_t)*puVar2 & 0xffffff);
                break;
            case 4:
                uVar5 = (uint64_t)*puVar2;
            }
        }
        uVar3 = sk_x_0006b438((uint32_t)auVar7.hi + ((uint32_t)uVar5 | uVar1));
        return uVar3;
    }
LAB_004a0ab8:
    if ((uint32_t)auVar7.hi == 0) {
        return 0;
    }
    uVar3 = sk_x_000839f8();
    return uVar3;
}

/* FUN_004a0cf4 @ 0x4a0cf4   (est. sk_x_004a0cf4)
 * Ghidra: void FUN_004a0cf4(long param_1)
 * Looks up an object table entry by id 0x13f with the key fields at param_1+0x10
 * and param_1+0x18 (sk_x_00497504). If the returned pair's hi word is below 0x40,
 * releases the entry, then runs a follow-up query (sk_x_00351244) and forwards the
 * resulting pair with the kind constant 3 to sk_x_003728b8 before sk_x_00019858.
 * Confidence: low
 * Notes: auVar1 is the cl4_result pair from sk_x_00497504. */
static void sk_x_004a0cf4(uint64_t param_1)
{
    cl4_result_t auVar1;

    auVar1 = sk_x_00497504(0x13f, *(uint64_t *)(param_1 + 0x10), *(uint64_t *)(param_1 + 0x18));
    if (auVar1.hi < 0x40) {
        sk_x_004abc50(*(uint64_t *)(auVar1.lo - 8) + 0x40);
        auVar1 = sk_x_00351244();
        sk_x_003728b8(auVar1.lo, auVar1.hi, 3);
        sk_x_00019858();
    }
    return;
}

/* FUN_004a0d6c @ 0x4a0d6c   (est. sk_x_004a0d6c)
 * Ghidra: void FUN_004a0d6c(undefined8 param_1, undefined8 param_2, long param_3)
 * Performs an object-table lookup on the key pair from param_3+0x18 via
 * sk_x_004aa4fc, then writes the mapping through sk_x_00377824. Afterwards it
 * computes two destination addresses from the method-table base (x16 scratch),
 * a byte length from offset +0x50, and a base from +0x40. If the combined flag
 * word passes the 0x1000f8 mask and the size check fits within 0x19, it copies a
 * 9-byte double-word pair into the two destinations and runs a helper dispatch;
 * otherwise it reports a fault via sk_x_004ac46c.
 * Confidence: low
 * Notes: many extraout_* (x8/x9/x10/x11/x13/x16) and unaff_x19/x20 are Ghidra
 * register artifacts (method-table base and context pointers). */
static void sk_x_004a0d6c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t lVar1;
    uint64_t lVar2;
    uint64_t uVar3;
    uint32_t uVar4;
    uint64_t uVar5;
    uint64_t extraout_x8;    /* Ghidra: extraout_x8 */
    uint64_t *puVar6;
    uint64_t *puVar7;
    uint64_t extraout_x9;    /* Ghidra: extraout_x9 (code ptr) */
    uint64_t extraout_x10;   /* Ghidra: extraout_x10 (mask) */
    uint64_t extraout_x11;   /* Ghidra: extraout_x11 */
    uint64_t extraout_x11_00; /* Ghidra: extraout_x11_00 */
    uint32_t extraout_w13;   /* Ghidra: extraout_w13 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint64_t extraout_x16_01; /* Ghidra: extraout_x16_01 */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming context base) */
    uint64_t x20;            /* Ghidra: unaff_x20 (incoming context base) */
    cl4_result_t auVar8;

    sk_x_00084220();
    uVar5 = sk_x_00350c5c().lo;
    uVar3 = *(uint64_t *)(param_3 + 0x10);
    auVar8 = sk_x_004aa4fc(uVar5, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar8.lo, auVar8.hi, uVar3);
    sk_x_0034b7e4();
    sk_x_004ac7c8(extraout_x16);
    lVar1 = extraout_x11 + (uint64_t)(uint8_t)*(uint32_t *)(extraout_x16_00 + 0x50);
    auVar8 = sk_x_004ac7c8();
    lVar2 = extraout_x11_00 + *(uint64_t *)(extraout_x16_01 + 0x40);
    uVar4 = *(uint32_t *)(extraout_x8 + 0x50) | extraout_w13;
    if ((uVar4 & 0x1000f8) == 0 && (((lVar2 + 7U) & ~0x7ULL) + 9) < 0x19) {
        sk_x_0009461c(auVar8.lo, auVar8.hi, auVar8.lo);
        (*(void (*)(void))extraout_x9)();
        (*(void (**)(uint64_t, uint64_t, uint64_t))(extraout_x16_00 + 0x10))
            ((lVar1 + x19) & ~extraout_x10, (lVar1 + x20) & ~extraout_x10, uVar3);
        puVar6 = (uint64_t *)((x19 + lVar2 + 7) & ~0x7ULL);
        puVar7 = (uint64_t *)((x20 + lVar2 + 7) & ~0x7ULL);
        *puVar6 = *puVar7;
        *(uint8_t *)(puVar6 + 1) = *(uint8_t *)(puVar7 + 1);
    } else {
        sk_x_004ac46c(uVar4 & 0xf8 | 7);
    }
    sk_x_00084234();
    return;
}

/* FUN_004a0eb8 @ 0x4a0eb8   (est. sk_x_004a0eb8)
 * Ghidra: void FUN_004a0eb8(undefined8 param_1, undefined8 param_2, long param_3)
 * Looks up a mapping key from param_3+0x18 via sk_x_004aa4fc (seed from
 * sk_x_003504d0) and installs it with sk_x_00377824. Then dispatches the
 * method-slot at +0x10 of the method table (x16 scratch), feeds the value at
 * table+0x40 to sk_x_004aaba8, and computes a destination from a byte length at
 * table+0x50. Calls the +0x10 slot with two masked destination addresses, then
 * releases/commits the range via sk_x_004aa6f0.
 * Confidence: low
 * Notes: extraout_x16/_00 and unaff_x19/x20 are Ghidra register artifacts. */
static void sk_x_004a0eb8(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint64_t extraout_x8;    /* Ghidra: extraout_x8 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming context base) */
    uint64_t x20;            /* Ghidra: unaff_x20 (incoming context base) */
    uint64_t uVar4;
    cl4_result_t auVar5;

    uVar3 = sk_x_003504d0();
    uVar2 = *(uint64_t *)(param_3 + 0x10);
    auVar5 = sk_x_004aa4fc(uVar3, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar5.lo, auVar5.hi, uVar2);
    sk_x_00349530();
    (*(void (**)(void))(extraout_x16 + 0x10))();
    sk_x_004aaba8(*(uint64_t *)(extraout_x16 + 0x40));
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar1 = extraout_x8 + uVar4;
    (*(void (**)(uint64_t, uint64_t, uint64_t))(extraout_x16_00 + 0x10))
        ((uVar1 + x20) & ~uVar4, (uVar1 + x19) & ~uVar4, uVar2);
    sk_x_004aa6f0(uVar1 & ~uVar4);
    return;
}

/* FUN_004a0f64 @ 0x4a0f64   (est. sk_x_004a0f64)
 * Ghidra: void FUN_004a0f64(undefined8 param_1, undefined8 param_2, long param_3)
 * Same mapping/install sequence as sk_x_004a0eb8, but dispatches the method-slot
 * at +0x18 (both for the empty call and for the masked two-address call).
 * Confidence: low
 * Notes: extraout_x16/_00 and unaff_x19/x20 are Ghidra register artifacts. */
static void sk_x_004a0f64(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint64_t extraout_x8;    /* Ghidra: extraout_x8 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming context base) */
    uint64_t x20;            /* Ghidra: unaff_x20 (incoming context base) */
    uint64_t uVar4;
    cl4_result_t auVar5;

    uVar3 = sk_x_003504d0();
    uVar2 = *(uint64_t *)(param_3 + 0x10);
    auVar5 = sk_x_004aa4fc(uVar3, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar5.lo, auVar5.hi, uVar2);
    sk_x_00349530();
    (*(void (**)(void))(extraout_x16 + 0x18))();
    sk_x_004aaba8(*(uint64_t *)(extraout_x16 + 0x40));
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar1 = extraout_x8 + uVar4;
    (*(void (**)(uint64_t, uint64_t, uint64_t))(extraout_x16_00 + 0x18))
        ((uVar1 + x20) & ~uVar4, (uVar1 + x19) & ~uVar4, uVar2);
    sk_x_004aa6f0(uVar1 & ~uVar4);
    return;
}

/* FUN_004a1010 @ 0x4a1010   (est. sk_x_004a1010)
 * Ghidra: void FUN_004a1010(undefined8 param_1, undefined8 param_2, long param_3)
 * Same mapping/install sequence as sk_x_004a0eb8, but dispatches the method-slot
 * at +0x20 (both for the empty call and for the masked two-address call).
 * Confidence: low
 * Notes: extraout_x16/_00 and unaff_x19/x20 are Ghidra register artifacts. */
static void sk_x_004a1010(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint64_t extraout_x8;    /* Ghidra: extraout_x8 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming context base) */
    uint64_t x20;            /* Ghidra: unaff_x20 (incoming context base) */
    uint64_t uVar4;
    cl4_result_t auVar5;

    uVar3 = sk_x_003504d0();
    uVar2 = *(uint64_t *)(param_3 + 0x10);
    auVar5 = sk_x_004aa4fc(uVar3, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar5.lo, auVar5.hi, uVar2);
    sk_x_00349530();
    (*(void (**)(void))(extraout_x16 + 0x20))();
    sk_x_004aaba8(*(uint64_t *)(extraout_x16 + 0x40));
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar1 = extraout_x8 + uVar4;
    (*(void (**)(uint64_t, uint64_t, uint64_t))(extraout_x16_00 + 0x20))
        ((uVar1 + x20) & ~uVar4, (uVar1 + x19) & ~uVar4, uVar2);
    sk_x_004aa6f0(uVar1 & ~uVar4);
    return;
}

/* FUN_004a10bc @ 0x4a10bc   (est. sk_x_004a10bc)
 * Ghidra: void FUN_004a10bc(undefined8 param_1, undefined8 param_2, long param_3)
 * Same mapping/install sequence as sk_x_004a0eb8, but dispatches the method-slot
 * at +0x28 (both for the empty call and for the masked two-address call).
 * Confidence: low
 * Notes: extraout_x16/_00 and unaff_x19/x20 are Ghidra register artifacts. */
static void sk_x_004a10bc(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint64_t extraout_x8;    /* Ghidra: extraout_x8 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming context base) */
    uint64_t x20;            /* Ghidra: unaff_x20 (incoming context base) */
    uint64_t uVar4;
    cl4_result_t auVar5;

    uVar3 = sk_x_003504d0();
    uVar2 = *(uint64_t *)(param_3 + 0x10);
    auVar5 = sk_x_004aa4fc(uVar3, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar5.lo, auVar5.hi, uVar2);
    sk_x_00349530();
    (*(void (**)(void))(extraout_x16 + 0x28))();
    sk_x_004aaba8(*(uint64_t *)(extraout_x16 + 0x40));
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar1 = extraout_x8 + uVar4;
    (*(void (**)(uint64_t, uint64_t, uint64_t))(extraout_x16_00 + 0x28))
        ((uVar1 + x20) & ~uVar4, (uVar1 + x19) & ~uVar4, uVar2);
    sk_x_004aa6f0(uVar1 & ~uVar4);
    return;
}

/* FUN_004a1168 @ 0x4a1168   (est. sk_x_004a1168)
 * Ghidra: ulong FUN_004a1168(undefined8 param_1, undefined8 param_2, long param_3)
 * Installs a mapping from the key pair at param_3+0x18 (sk_x_004aa4fc) through
 * sk_x_00377824, then walks a variable-length tag table rooted at the incoming
 * x19 base to resolve a length/size value. Reads the tag with the width chosen
 * by uVar3 (byte/halfword/word), shifts a length by the low byte-aligned bits,
 * and combines it with extraout_w12 to produce the returned size. A size-1
 * table probe hits a SoftwareBreakpoint trap at 0x4a1330 (does not return).
 * Confidence: low
 * Notes: unaff_x19 (table base), unaff_w21 (incoming length) and the many
 * extraout_* values are Ghidra register artifacts. */
static uint64_t sk_x_004a1168(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t lVar1;
    uint64_t lVar2;
    uint32_t uVar3;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t extraout_w8;    /* Ghidra: extraout_w8 */
    uint64_t extraout_x9;    /* Ghidra: extraout_x9 */
    uint32_t extraout_w12;   /* Ghidra: extraout_w12 */
    uint32_t extraout_w13;   /* Ghidra: extraout_w13 */
    uint32_t uVar10;
    uint64_t extraout_x14;   /* Ghidra: extraout_x14 */
    uint64_t extraout_x16;   /* Ghidra: extraout_x16 (method-table base) */
    uint64_t extraout_x16_00; /* Ghidra: extraout_x16_00 */
    uint32_t *x19;           /* Ghidra: unaff_x19 (incoming tag-table base) */
    uint32_t w21;            /* Ghidra: unaff_w21 (incoming length) */
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    cl4_result_t auVar11;

    uVar5 = sk_x_00351a38();
    uVar6 = *(uint64_t *)(param_3 + 0x10);
    auVar11 = sk_x_004aa4fc(uVar5, *(uint64_t *)(param_3 + 0x18));
    sk_x_00377824(auVar11.lo, auVar11.hi, uVar6);
    uVar6 = sk_x_004ac790();
    sk_x_004ac784(uVar6, *(uint32_t *)(extraout_x16 + 0x54));
    auVar11 = sk_x_004ac784();
    if (w21 == 0) {
        return 0;
    }
    lVar2 = ((extraout_x14 + extraout_x9) & ~extraout_x9) +
            *(uint64_t *)(extraout_x16_00 + 0x40);
    if (extraout_w12 <= w21 && (w21 - extraout_w12) != 0) {
        lVar1 = ((lVar2 + 7U) & ~0x7ULL) + 9;
        uVar10 = (uint32_t)lVar1;
        uVar8 = 2;
        uVar9 = uVar8;
        if (uVar10 < 4) {
            uVar9 = (((w21 - extraout_w12) + 0xff) >> 8) + 1;
        }
        if (0xffff < uVar9) {
            uVar8 = 4;
        }
        if (uVar9 < 0x100) {
            uVar8 = 1;
        }
        uVar3 = 0;
        if (1 < uVar9) {
            uVar3 = uVar8;
        }
        switch (uVar3) {
        case 1:
            uVar8 = (uint32_t)*(uint8_t *)((uint64_t)x19 + lVar1);
            if (*(uint8_t *)((uint64_t)x19 + lVar1) != 0) {
LAB_004a1284:
                uVar8 = (uVar8 - 1) << ((uVar10 & 3) << 3);
                if (uVar10 < 4) {
                    uVar9 = (uint32_t)(uint8_t)*x19;
                } else {
                    uVar9 = *x19;
                    uVar8 = 0;
                }
                uVar8 = extraout_w12 + (uVar9 | uVar8);
                goto LAB_004a1318;
            }
            break;
        case 2:
            uVar8 = (uint32_t)*(uint16_t *)((uint64_t)x19 + lVar1);
            if (*(uint16_t *)((uint64_t)x19 + lVar1) != 0) goto LAB_004a1284;
            break;
        case 3:
            /* WARNING: does not return (Ghidra models the trap as returning a
             * code pointer that is then called). */
            SoftwareBreakpoint(1, 0x4a1330);
        case 4:
            uVar8 = *(uint32_t *)((uint64_t)x19 + lVar1);
            if (uVar8 != 0) goto LAB_004a1284;
        }
    }
    if (0xfd < extraout_w13) {
        if ((uint32_t)auVar11.hi < extraout_w8) {
            sk_x_004ac168(auVar11.lo, auVar11.hi, auVar11.lo);
        }
        uVar7 = sk_x_000839f8();
        return uVar7;
    }
    uVar8 = (uint32_t)*(uint8_t *)((((uint64_t)x19 + lVar2 + 7) & ~0x7ULL) + 8);
    if (uVar8 < 2) {
        return 0;
    }
    uVar8 = (uVar8 + 0x7ffffffe) & 0x7fffffff;
LAB_004a1318:
    return (uint64_t)(uVar8 + 1);
}

/* FUN_004a1624 @ 0x4a1624   (est. sk_x_004a1624)
 * Ghidra: void FUN_004a1624(void)
 * Releases a battery of capability/object handles held at fixed offsets in the
 * incoming x19 context/object, interleaving the release helper sk_x_0036b118
 * (with the field value as the handle) and sk_x_003a25d4 for the two offset
 * slots that use a different destroy path (+0x20 and +0x98). Starts with a
 * paired preamble (sk_x_00352b20, sk_x_0036b118()).
 * Confidence: low
 * Notes: unaff_x19 is the incoming object base (Ghidra register artifact). */
static void sk_x_004a1624(void)
{
    uint64_t x19;   /* Ghidra: unaff_x19 (incoming object base) */

    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(x19 + 0x18));
    sk_x_003a25d4(*(uint64_t *)(x19 + 0x20));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x28));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x38));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x40));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x48));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x50));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x58));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x60));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x70));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x78));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x80));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x88));
    sk_x_003a25d4(*(uint64_t *)(x19 + 0x98));
    return;
}

/* FUN_004a16bc @ 0x4a16bc   (est. sk_x_004a16bc)
 * Ghidra: void FUN_004a16bc(void)
 * Copies a large contiguous field region from the incoming source base (x1
 * scratch from sk_x_004aac14) into the incoming x19 destination object, covering
 * offsets 0x20..0xb8, then runs a long sequence of balanced acquire/release
 * helper pairs (sk_x_0036b270 / sk_x_004aba1c etc.) with the copied field values
 * passed as handles. The exact pairing mirrors a kernel object-ref handoff.
 * Confidence: low
 * Notes: extraout_x1/_00/_01 (source bases) and unaff_x19 (dest base) are Ghidra
 * register artifacts. thunk_FUN_0036b270 aliases sk_x_0036b270. */
static void sk_x_004a16bc(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t extraout_x1;    /* Ghidra: extraout_x1 (source base) */
    uint64_t extraout_x1_00; /* Ghidra: extraout_x1_00 (source base) */
    uint64_t extraout_x1_01; /* Ghidra: extraout_x1_01 (source base) */
    uint64_t x19;            /* Ghidra: unaff_x19 (incoming dest base) */
    uint64_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    uint64_t uVar10;
    uint64_t uVar11;

    sk_x_004aac14();
    uVar1 = *(uint64_t *)(extraout_x1 + 0x20);
    uVar2 = *(uint64_t *)(extraout_x1 + 0x28);
    *(uint64_t *)(x19 + 0x28) = uVar2;
    *(uint8_t *)(x19 + 0x30) = *(uint8_t *)(extraout_x1 + 0x30);
    uVar6 = *(uint64_t *)(extraout_x1 + 0x40);
    uVar8 = *(uint64_t *)(extraout_x1 + 0x38);
    *(uint64_t *)(x19 + 0x40) = *(uint64_t *)(extraout_x1 + 0x40);
    *(uint64_t *)(x19 + 0x38) = uVar8;
    uVar7 = *(uint64_t *)(extraout_x1 + 0x50);
    sk_x_004abee0();
    uVar5 = *(uint64_t *)(extraout_x1_00 + 0x60);
    sk_x_004ab74c();
    uVar4 = *(uint64_t *)(extraout_x1_01 + 0x78);
    uVar9 = *(uint64_t *)(extraout_x1_01 + 0x70);
    uVar3 = *(uint64_t *)(extraout_x1_01 + 0x88);
    uVar8 = *(uint64_t *)(extraout_x1_01 + 0x80);
    *(uint64_t *)(x19 + 0x78) = *(uint64_t *)(extraout_x1_01 + 0x78);
    *(uint64_t *)(x19 + 0x70) = uVar9;
    *(uint64_t *)(x19 + 0x88) = uVar3;
    *(uint64_t *)(x19 + 0x80) = uVar8;
    uVar8 = *(uint64_t *)(extraout_x1_01 + 0x88);
    uVar3 = *(uint64_t *)(extraout_x1_01 + 0x98);
    *(uint64_t *)(x19 + 0x90) = *(uint64_t *)(extraout_x1_01 + 0x90);
    *(uint64_t *)(x19 + 0x98) = uVar3;
    uVar9 = *(uint64_t *)(extraout_x1_01 + 0xa0);
    uVar11 = *(uint64_t *)(extraout_x1_01 + 0xb8);
    uVar10 = *(uint64_t *)(extraout_x1_01 + 0xb0);
    *(uint64_t *)(x19 + 0xa8) = *(uint64_t *)(extraout_x1_01 + 0xa8);
    *(uint64_t *)(x19 + 0xa0) = uVar9;
    *(uint64_t *)(x19 + 0xb8) = uVar11;
    *(uint64_t *)(x19 + 0xb0) = uVar10;
    sk_x_0036b270();
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(uVar1);
    sk_x_0036b270(uVar2);
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270(uVar6);
    sk_x_004ac3d8();
    sk_x_0036b270(uVar7);
    sk_x_004ac550();
    sk_x_0036b270(uVar5);
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(uVar4);
    sk_x_004ac4ac();
    sk_x_0036b270(uVar8);
    sk_x_0036b270(uVar3);
    return;
}

/* FUN_004a17d0 @ 0x4a17d0   (est. sk_x_004a17d0)
 * Ghidra: void FUN_004a17d0(void)
 * Copies the 8-byte handle and the 1-byte tag from source offsets +8/+0x10 into
 * the incoming x19 object, then walks a long fixed sequence of teardown/acquire
 * helper pairs (sk_x_0036b118 / sk_x_004aba60 etc., and sk_x_0036b270 /
 * sk_x_004aaaf4 etc.) and finally copies the +0xb0/+0xb8 tail words from x20.
 * Confidence: low
 * Notes: unaff_x19 (dest) and unaff_x20 (source) are Ghidra register artifacts.
 * thunk_FUN_0036b270 aliases sk_x_0036b270. */
static void sk_x_004a17d0(void)
{
    uint64_t uVar1;
    uint64_t x19;   /* Ghidra: unaff_x19 (incoming dest base) */
    uint64_t x20;   /* Ghidra: unaff_x20 (incoming source base) */

    sk_x_004aae14();
    sk_x_0036b118();
    uVar1 = *(uint64_t *)(x20 + 8);
    *(uint8_t *)(x19 + 0x10) = *(uint8_t *)(x20 + 0x10);
    *(uint64_t *)(x19 + 8) = uVar1;
    sk_x_004aaaf4();
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_003a25d4();
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004ab230();
    sk_x_0036b118();
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aba60();
    sk_x_0036b118();
    sk_x_004aba50();
    sk_x_0036b118();
    sk_x_004aba70();
    sk_x_0036b118();
    sk_x_004abda8();
    sk_x_0036b118();
    sk_x_004ab734();
    sk_x_0036b118();
    sk_x_004abbe0();
    sk_x_0036b118();
    sk_x_004abbc4();
    sk_x_0036b118();
    sk_x_004ac49c();
    sk_x_0036b118();
    sk_x_004ac484();
    sk_x_003a25d4();
    sk_x_004661a4();
    *(uint64_t *)(x19 + 0xb0) = *(uint64_t *)(x20 + 0xb0);
    *(uint64_t *)(x19 + 0xb8) = *(uint64_t *)(x20 + 0xb8);
    return;
}

/* FUN_004a18e8 @ 0x4a18e8   (est. sk_x_004a18e8)
 * Ghidra: void FUN_004a18e8(void)
 * Copies the handle/tag and a broad run of per-field values from the incoming
 * x20 source into the x19 destination object (offsets +8..+0xb8), releasing each
 * copied-out old handle via sk_x_0036b118 or sk_x_003a25d4 and running the paired
 * teardown helpers sk_x_004ac42c etc. in between. End result: a full object-field
 * swap/migration with old-value release.
 * Confidence: low
 * Notes: unaff_x19 (dest) and unaff_x20 (source) are Ghidra register artifacts. */
static void sk_x_004a18e8(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t x19;   /* Ghidra: unaff_x19 (incoming dest base) */
    uint64_t x20;   /* Ghidra: unaff_x20 (incoming source base) */
    uint64_t uVar3;

    sk_x_004aaf48();
    sk_x_004accf0();
    *(uint64_t *)(x19 + 8) = *(uint64_t *)(x20 + 8);
    *(uint8_t *)(x19 + 0x10) = *(uint8_t *)(x20 + 0x10);
    sk_x_004aaaf4();
    sk_x_0036b118(*(uint64_t *)(x19 + 0x18));
    sk_x_004abec0();
    sk_x_003a25d4();
    sk_x_004ac42c();
    *(uint8_t *)(x19 + 0x30) = *(uint8_t *)(x20 + 0x30);
    sk_x_0036b118(*(uint64_t *)(x19 + 0x38));
    sk_x_004ac40c();
    sk_x_0036b118(*(uint64_t *)(x19 + 0x48));
    sk_x_004ac4d0();
    sk_x_0036b118(*(uint64_t *)(x19 + 0x58));
    sk_x_004ac3fc();
    *(uint8_t *)(x19 + 0x68) = *(uint8_t *)(x20 + 0x68);
    sk_x_0036b118(*(uint64_t *)(x19 + 0x70));
    uVar1 = *(uint64_t *)(x19 + 0x78);
    uVar2 = *(uint64_t *)(x20 + 0x70);
    *(uint64_t *)(x19 + 0x78) = *(uint64_t *)(x20 + 0x78);
    *(uint64_t *)(x19 + 0x70) = uVar2;
    sk_x_0036b118(uVar1);
    sk_x_0036b118(*(uint64_t *)(x19 + 0x80));
    uVar1 = *(uint64_t *)(x19 + 0x88);
    uVar2 = *(uint64_t *)(x20 + 0x80);
    *(uint64_t *)(x19 + 0x88) = *(uint64_t *)(x20 + 0x88);
    *(uint64_t *)(x19 + 0x80) = uVar2;
    sk_x_0036b118(uVar1);
    uVar1 = *(uint64_t *)(x20 + 0x98);
    uVar2 = *(uint64_t *)(x19 + 0x98);
    *(uint64_t *)(x19 + 0x90) = *(uint64_t *)(x20 + 0x90);
    *(uint64_t *)(x19 + 0x98) = uVar1;
    sk_x_003a25d4(uVar2);
    uVar1 = *(uint64_t *)(x20 + 0xa0);
    uVar3 = *(uint64_t *)(x20 + 0xb8);
    uVar2 = *(uint64_t *)(x20 + 0xb0);
    *(uint64_t *)(x19 + 0xa8) = *(uint64_t *)(x20 + 0xa8);
    *(uint64_t *)(x19 + 0xa0) = uVar1;
    *(uint64_t *)(x19 + 0xb8) = uVar3;
    *(uint64_t *)(x19 + 0xb0) = uVar2;
    return;
}

/* FUN_004a1a50 @ 0x4a1a50   (est. sk_x_004a1a50)
 * Ghidra: void FUN_004a1a50(long param_1)
 * Releases three capability/object handles stored at param_1+0x18, +0x38 and
 * +0x40 using the sk_x_003a25d4 destroy path. Likely the tail of a larger
 * object teardown (only these three slots are handled here).
 * Confidence: low */
static void sk_x_004a1a50(uint64_t param_1)
{
    sk_x_003a25d4(*(uint64_t *)(param_1 + 0x18));
    sk_x_003a25d4(*(uint64_t *)(param_1 + 0x38));
    sk_x_003a25d4(*(uint64_t *)(param_1 + 0x40));
    return;
}
/* FUN_004a1a88 @ 0x4a1a88   (est. sk_x_004a1a88)
 * Ghidra: long FUN_004a1a88(long param_1)
 * Copies a 0x60-byte object image from the pair returned by sk_x_004ab600()
 * into the object at param_1 (field copies at +0x10..+0x58), then runs a
 * finalize/commit sequence (sk_x_0036b270, sk_x_004aba1c). Returns param_1.
 * Confidence: medium
 * Notes: sk_x_004ab600 returns a pair; only its .hi word (extraout_x1) is the
 * source base. thunk_FUN_0036b270 is sk_x_0036b270. */
static uint64_t sk_x_004a1a88(uint64_t param_1)
{
	cl4_result_t r;
	uint64_t base;
	uint64_t v;

	r = sk_x_004ab600();
	base = r.hi;                                   /* extraout_x1 */
	*(uint64_t *)(param_1 + 0x10) = *(uint64_t *)(base + 0x10);
	*(uint64_t *)(param_1 + 0x18) = *(uint64_t *)(base + 0x18);
	v = *(uint64_t *)(base + 0x20);
	*(uint64_t *)(param_1 + 0x28) = *(uint64_t *)(base + 0x28);
	*(uint64_t *)(param_1 + 0x20) = v;
	*(uint64_t *)(param_1 + 0x30) = *(uint64_t *)(base + 0x30);
	v = *(uint64_t *)(base + 0x38);
	*(uint64_t *)(param_1 + 0x40) = *(uint64_t *)(base + 0x40);
	*(uint64_t *)(param_1 + 0x38) = v;
	v = *(uint64_t *)(base + 0x40);
	*(uint64_t *)(param_1 + 0x48) = *(uint64_t *)(base + 0x48);
	*(uint64_t *)(param_1 + 0x50) = *(uint64_t *)(base + 0x50);
	*(uint8_t *)(param_1 + 0x58) = *(uint8_t *)(base + 0x58);
	sk_x_0036b270();
	sk_x_004aba1c();
	sk_x_0036b270();
	sk_x_0036b270(v);
	return param_1;
}

/* FUN_004a1b04 @ 0x4a1b04   (est. sk_x_004a1b04)
 * Ghidra: void FUN_004a1b04(void)
 * Uses caller-provided register bases unaff_x20 (destination) and unaff_x19
 * (source): builds an object from the pair returned by sk_x_0034b264, copies
 * a 0x60-byte image from the source to the destination, running release
 * (sk_x_003a25d4) on the displaced destination fields. Returns void.
 * Confidence: medium
 * Notes: unaff_x19/unaff_x20 are register-passed bases (Ghidra could not track
 * them); represented here as locals src/dst. */
static void sk_x_004a1b04(void)
{
	cl4_result_t r;
	uint64_t p;
	uint64_t q;
	uint64_t src;
	uint64_t dst;
	uint64_t v;

	r = sk_x_0034b264();
	p = r.lo;                                      /* auVar3._0_8_ */
	q = r.hi;                                      /* lVar1 */
	*(uint64_t *)(p + 8) = *(uint64_t *)(q + 8);
	*(uint64_t *)(p + 0x10) = *(uint64_t *)(q + 0x10);
	v = *(uint64_t *)(dst + 0x18);
	*(uint64_t *)(dst + 0x18) = *(uint64_t *)(q + 0x18);
	sk_x_0036b270();
	sk_x_003a25d4(v);
	*(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
	*(uint64_t *)(dst + 0x28) = *(uint64_t *)(src + 0x28);
	*(uint64_t *)(dst + 0x30) = *(uint64_t *)(src + 0x30);
	v = *(uint64_t *)(dst + 0x38);
	*(uint64_t *)(dst + 0x38) = *(uint64_t *)(src + 0x38);
	sk_x_0036b270();
	sk_x_003a25d4(v);
	v = *(uint64_t *)(dst + 0x40);
	*(uint64_t *)(dst + 0x40) = *(uint64_t *)(src + 0x40);
	sk_x_0036b270();
	sk_x_003a25d4(v);
	*(uint64_t *)(dst + 0x48) = *(uint64_t *)(src + 0x48);
	v = *(uint64_t *)(src + 0x50);
	*(uint8_t *)(dst + 0x58) = *(uint8_t *)(src + 0x58);
	*(uint64_t *)(dst + 0x50) = v;
}

/* FUN_004a1bb8 @ 0x4a1bb8   (est. sk_x_004a1bb8)
 * Ghidra: void FUN_004a1bb8(void)
 * Rebuilds the object at caller register base unaff_x20 from the pair returned
 * by sk_x_004ab600() (source base = .hi) and copies a 0x60-byte image from
 * unaff_x19, releasing displaced fields with sk_x_003a25d4. Returns void.
 * Confidence: medium
 * Notes: unaff_x19/unaff_x20 register bases represented as locals src/dst. */
static void sk_x_004a1bb8(void)
{
	cl4_result_t r;
	uint64_t base;
	uint64_t src;
	uint64_t dst;
	uint64_t v;
	uint64_t w;

	sk_x_003504d0();
	r = sk_x_004ab600();
	base = r.hi;                                   /* auVar3._8_8_ */
	w = *(uint64_t *)(base + 0x18);                /* uVar2 */
	v = *(uint64_t *)(r.lo + 0x18);                /* uVar1 */
	*(uint64_t *)(dst + 0x10) = *(uint64_t *)(base + 0x10);
	*(uint64_t *)(dst + 0x18) = w;
	sk_x_003a25d4(v);
	sk_x_004ac87c();
	*(uint64_t *)(dst + 0x30) = *(uint64_t *)(src + 0x30);
	sk_x_003a25d4(*(uint64_t *)(dst + 0x38));
	w = *(uint64_t *)(dst + 0x40);
	v = *(uint64_t *)(src + 0x38);
	*(uint64_t *)(dst + 0x40) = *(uint64_t *)(src + 0x40);
	*(uint64_t *)(dst + 0x38) = v;
	sk_x_003a25d4(w);
	w = *(uint64_t *)(src + 0x50);
	*(uint64_t *)(dst + 0x48) = *(uint64_t *)(src + 0x48);
	*(uint64_t *)(dst + 0x50) = w;
	*(uint8_t *)(dst + 0x58) = *(uint8_t *)(src + 0x58);
}

/* FUN_004a1cc0 @ 0x4a1cc0   (est. sk_x_004a1cc0)
 * Ghidra: void FUN_004a1cc0(long param_1)
 * Performs a two-step check on the object at param_1: first sk_x_00377824 with
 * selector 0x13f and a message from param_1+0x10; if its low result is < 0x40,
 * a second check sk_x_00377dcc (selector 0x13f) must also return < 0x40, in
 * which case the pair from sk_x_004ab710() is registered with count 2 via
 * sk_x_003728b8 and sk_x_00019858() runs. Returns void.
 * Confidence: medium
 * Notes: DAT_0061628c/LAB_0061629c are data/code addresses (0x61628c, 0x61629c)
 * passed as tags; extraout_x1 / extraout_x1_00 are the .lo words of the pair
 * returns from sk_x_00377824 / sk_x_00377dcc. */
static void sk_x_004a1cc0(uint64_t param_1)
{
	cl4_result_t r;
	cl4_result_t s;
	cl4_result_t q;
	uint64_t u;

	u = *(uint64_t *)(param_1 + 0x10);
	r = sk_x_00377824(0x13f, *(uint64_t *)(param_1 + 0x18), u,
	                  (uint64_t)0x61628c, (uint64_t)0x61629c);   /* DAT_0061628c, LAB_0061629c */
	if (r.lo < 0x40) {                              /* extraout_x1 */
		s = sk_x_00377dcc(0x13f, u);
		if (s.lo < 0x40) {                          /* extraout_x1_00 */
			q = sk_x_004ab710();
			sk_x_003728b8(q.lo, q.hi, 2);
			sk_x_00019858();
		}
	}
}

/* FUN_004a1d6c @ 0x4a1d6c   (est. sk_x_004a1d6c)
 * Ghidra: long FUN_004a1d6c(long param_1, undefined8 *param_2, long param_3)
 * Message send / capability-call trampoline: builds a message from param_3
 * (+0x10/+0x18) via sk_x_004aa4fc and sk_x_00377824, then either performs an
 * indirect invocation through the target at extraout_x16_00 (+0x10, with
 * param_1/param_2 masked to the object size) when the type flags (word at
 * +0x50) permit, or falls back to sk_x_004ab5ec(*param_2). Returns param_1.
 * Confidence: low
 * Notes: Heavy Ghidra register-residue artifacts (extraout_x8/x9/x10/x11/x16/
 * w13); the indirect-call targets and size masks are not fully recoverable.
 * Residue pointers are locals here. */
static uint64_t sk_x_004a1d6c(uint64_t param_1, uint64_t *param_2, uint64_t param_3)
{
	cl4_result_t r;
	cl4_result_t s;
	uint64_t u;
	uint64_t l;
	uint64_t res16;     /* extraout_x16  (residue) */
	uint64_t res16b;    /* extraout_x16_00 */
	uint64_t res16c;    /* extraout_x16_01 */
	uint64_t res8;      /* extraout_x8   */
	uint64_t res9;      /* extraout_x9   */
	uint64_t res10;     /* extraout_x10  */
	uint64_t res11;     /* extraout_x11  */
	uint64_t res11b;    /* extraout_x11_00 */
	uint32_t resw13;    /* extraout_w13  */
	uint32_t flags;
	uint64_t size;

	u = *(uint64_t *)(param_3 + 0x10);
	r = sk_x_004aa4fc(param_1, *(uint64_t *)(param_3 + 0x18));
	sk_x_00377824(r.lo, r.hi, u);
	sk_x_0034b7e4();
	s = sk_x_004ac7c8(res16);
	l = res11 + (uint64_t)*(uint8_t *)(res16b + 0x50);
	s = sk_x_004ac7c8();
	flags = *(uint32_t *)(res8 + 0x50) | resw13;
	if (((flags & 0xff) < 8 && (flags & 0x100000) == 0) &&
	    (uint64_t)(res11b + *(int64_t *)(res16c + 0x40)) < 0x19) {
		sk_x_003507e0(s.lo, s.hi, s.lo);
		((void (*)(void))res9)();
		((void (*)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(res16b + 0x10))
		        (l + param_1 & ~res10, l + (uint64_t)param_2 & ~res10, u);
	} else {
		sk_x_004ab5ec(*param_2);
	}
	return param_1;
}

/* FUN_004a1e84 @ 0x4a1e84   (est. sk_x_004a1e84)
 * Ghidra: void FUN_004a1e84(long param_1,long param_2)
 * Capability invocation on object param_1 using message built from param_2
 * (+0x10/+0x18) via sk_x_004aa4fc/sk_x_00377824; dispatches through an
 * indirect call at (extraout_x16+8) with param_1, then a second indirect call
 * through the target's dispatch table (+8) with an address computed from the
 * tag byte at +0x50 masked to object size. Returns void.
 * Confidence: low
 * Notes: Ghidra could not recover the indirect-jump table at 0x4a1f18; several
 * extraout register residues (extraout_x8/x16) are unrecoverable locals. */
static void sk_x_004a1e84(uint64_t param_1, uint64_t param_2)
{
	uint64_t l;
	uint64_t v;
	uint64_t res8;      /* extraout_x8  */
	uint64_t res16;     /* extraout_x16 */
	uint64_t tag;
	uint64_t base;

	l = *(uint64_t *)(param_2 + 0x10);
	v = sk_x_004aa4fc(*(uint64_t *)(param_2 + 0x18)).lo;
	v = sk_x_00377824(v, res8, l).lo;
	sk_x_0034ab20(v, v);
	((void (*)(uint64_t))*(uint64_t *)(res16 + 8))(param_1);
	tag = (uint64_t)*(uint8_t *)(*(uint64_t *)(l + -8) + 0x50);
	base = *(uint64_t *)(l + -8);
	((void (*)(uint64_t, uint64_t))*(uint64_t *)(base + 8))
	        (*(uint64_t *)(res16 + 0x40) + param_1 + tag & (tag ^ 0xffffffffffffffff), l);
}

/* FUN_004a1fb4 @ 0x4a1fb4   (est. sk_x_004a1fb4)
 * Ghidra: void FUN_004a1fb4(undefined8 param_1,undefined8 param_2,long param_3)
 * Capability message send: builds a message from param_3 (+0x10/+0x18) via
 * sk_x_003504d0/sk_x_004aa4fc/sk_x_00377824, runs an indirect handler at
 * (extraout_x16+0x18), then an indirect invoke at (extraout_x16_00+0x18) on
 * unaff_x19/unaff_x20 masked to the tag size from the byte at +0x50.
 * Returns void.
 * Confidence: low
 * Notes: extraout_x8/x16/x16_00 are unrecoverable register residues; unaff_x19/
 * unaff_x20 are register-passed bases (locals here). */
static void sk_x_004a1fb4(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
	cl4_result_t r;
	uint64_t u;
	uint64_t v;
	uint64_t res8;      /* extraout_x8   */
	uint64_t res16;     /* extraout_x16  */
	uint64_t res16b;    /* extraout_x16_00 */
	uint64_t x19;       /* unaff_x19     */
	uint64_t x20;       /* unaff_x20     */
	uint64_t tag;

	v = sk_x_003504d0();
	u = *(uint64_t *)(param_3 + 0x10);
	r = sk_x_004aa4fc(v, *(uint64_t *)(param_3 + 0x18));
	sk_x_00377824(r.lo, r.hi, u);
	sk_x_00349530();
	((void (*)(void))*(uint64_t *)(res16 + 0x18))();
	sk_x_004aaba8(*(uint64_t *)(res16 + 0x40));
	tag = (uint64_t)*(uint8_t *)(res16b + 0x50);
	((void (*)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(res16b + 0x18))
	        (res8 + tag + x20 & (tag ^ 0xffffffffffffffff),
	         res8 + tag + x19 & (tag ^ 0xffffffffffffffff), u);
}

/* FUN_004a204c @ 0x4a204c   (est. sk_x_004a204c)
 * Ghidra: void FUN_004a204c(undefined8 param_1,undefined8 param_2,long param_3)
 * Same shape as sk_x_004a1fb4 but dispatches through offsets +0x20: builds the
 * message from param_3, runs an indirect handler at (extraout_x16+0x20), then
 * an indirect invoke at (extraout_x16_00+0x20) on unaff_x19/unaff_x20 masked
 * by the tag byte at +0x50. Returns void.
 * Confidence: low
 * Notes: extraout residue pointers and unaff_x19/unaff_x20 register bases are
 * locals here (unrecoverable by Ghidra). */
static void sk_x_004a204c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
	cl4_result_t r;
	uint64_t u;
	uint64_t v;
	uint64_t res8;      /* extraout_x8   */
	uint64_t res16;     /* extraout_x16  */
	uint64_t res16b;    /* extraout_x16_00 */
	uint64_t x19;       /* unaff_x19     */
	uint64_t x20;       /* unaff_x20     */
	uint64_t tag;

	v = sk_x_003504d0();
	u = *(uint64_t *)(param_3 + 0x10);
	r = sk_x_004aa4fc(v, *(uint64_t *)(param_3 + 0x18));
	sk_x_00377824(r.lo, r.hi, u);
	sk_x_00349530();
	((void (*)(void))*(uint64_t *)(res16 + 0x20))();
	sk_x_004aaba8(*(uint64_t *)(res16 + 0x40));
	tag = (uint64_t)*(uint8_t *)(res16b + 0x50);
	((void (*)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(res16b + 0x20))
	        (res8 + tag + x20 & (tag ^ 0xffffffffffffffff),
	         res8 + tag + x19 & (tag ^ 0xffffffffffffffff), u);
}

/* FUN_004a20e4 @ 0x4a20e4   (est. sk_x_004a20e4)
 * Ghidra: void FUN_004a20e4(undefined8 param_1,undefined8 param_2,long param_3)
 * Same shape as sk_x_004a1fb4 but dispatches through offsets +0x28: builds the
 * message from param_3, runs an indirect handler at (extraout_x16+0x28), then
 * an indirect invoke at (extraout_x16_00+0x28) on unaff_x19/unaff_x20 masked
 * by the tag byte at +0x50. Returns void.
 * Confidence: low
 * Notes: extraout residue pointers and unaff_x19/unaff_x20 register bases are
 * locals here (unrecoverable by Ghidra). */
static void sk_x_004a20e4(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
	cl4_result_t r;
	uint64_t u;
	uint64_t v;
	uint64_t res8;      /* extraout_x8   */
	uint64_t res16;     /* extraout_x16  */
	uint64_t res16b;    /* extraout_x16_00 */
	uint64_t x19;       /* unaff_x19     */
	uint64_t x20;       /* unaff_x20     */
	uint64_t tag;

	v = sk_x_003504d0();
	u = *(uint64_t *)(param_3 + 0x10);
	r = sk_x_004aa4fc(v, *(uint64_t *)(param_3 + 0x18));
	sk_x_00377824(r.lo, r.hi, u);
	sk_x_00349530();
	((void (*)(void))*(uint64_t *)(res16 + 0x28))();
	sk_x_004aaba8(*(uint64_t *)(res16 + 0x40));
	tag = (uint64_t)*(uint8_t *)(res16b + 0x50);
	((void (*)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(res16b + 0x28))
	        (res8 + tag + x20 & (tag ^ 0xffffffffffffffff),
	         res8 + tag + x19 & (tag ^ 0xffffffffffffffff), u);
}

/* FUN_004a217c @ 0x4a217c   (est. sk_x_004a217c)
 * Ghidra: ulong FUN_004a217c(undefined8 param_1,undefined8 param_2,long param_3)
 * Index / slot lookup: builds a message from param_3, then resolves a size and
 * index range (words at +0x54 of two objects) and, when the caller index
 * (unaff_w21) exceeds the resolved upper bound, walks a packed bit-field /
 * index table rooted at unaff_x19 to compute the returned slot (a + (low|high)
 * + 1), falling back to sk_x_000839f8() on the error path. Returns the slot.
 * Confidence: low
 * Notes: complex variable-length-index decode with `uint3` 3-byte reads and an
 * unrecoverable jump-table; extraout_x9/x16 and unaff_w21/unaff_x19 are
 * register residues/bases represented as locals. */
static uint64_t sk_x_004a217c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
	cl4_result_t pr;
	uint64_t v;
	uint64_t l;
	uint64_t lv;
	uint64_t res;
	uint64_t res9;      /* extraout_x9   */
	uint64_t res16;     /* extraout_x16  */
	uint32_t *x19;      /* unaff_x19     */
	uint32_t w21;       /* unaff_w21     */
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;

	v = sk_x_00351a38();
	l = *(uint64_t *)(param_3 + 0x10);
	pr = sk_x_004aa4fc(v, *(uint64_t *)(param_3 + 0x18));
	sk_x_00377824(pr.lo, pr.hi, l);
	v = sk_x_004ac6d0();
	b = *(uint32_t *)(res16 + 0x54);
	l = *(uint64_t *)(l + -8);
	f = *(uint32_t *)(l + 0x54);
	a = f;
	if (f <= b) {
		a = b;
	}
	if (w21 == 0) {
		return 0;
	}
	if (w21 < a || w21 - a == 0) {
		goto LAB_004a22b0;
	}
	lv = (*(uint64_t *)(res9 + 0x40) + (uint64_t)*(uint8_t *)(l + 0x50) &
	      ((uint64_t)*(uint8_t *)(l + 0x50) ^ 0xffffffffffffffff)) + *(uint64_t *)(l + 0x40);
	c = (uint32_t)lv;
	d = c << 3;
	if (c < 4) {
		e = ((w21 - a) + ~(-1 << (uint64_t)(d & 0x1f)) >> (uint64_t)(d & 0x1f)) + 1;
		if (0xff < e) {
			if (e >> 0x10 == 0) {
				e = (uint32_t)*(uint16_t *)((uint64_t)x19 + lv);
			} else {
				e = *(uint32_t *)((uint64_t)x19 + lv);
			}
			goto LAB_004a2234;
		}
		if (1 < e) {
			goto LAB_004a2230;
		}
	} else {
LAB_004a2230:
		e = (uint32_t)*(uint8_t *)((uint64_t)x19 + lv);
LAB_004a2234:
		if (e != 0) {
			b = 0;
			if (c < 4) {
				b = e - 1 << (uint64_t)(d & 0x1f);
			}
			if (c == 0) {
				f = 0;
			} else {
				f = 4;
				if (c < 4) {
					f = c;
				}
				switch (f) {
				default:
					f = (uint32_t)*(uint8_t *)x19;
					break;
				case 2:
					f = (uint32_t)*(uint16_t *)x19;
					break;
				case 3:
					f = ((uint32_t)((uint8_t *)x19)[0] |
					     ((uint32_t)((uint8_t *)x19)[1] << 8) |
					     ((uint32_t)((uint8_t *)x19)[2] << 16));   /* uint3 */
					break;
				case 4:
					f = *x19;
				}
			}
			return (uint64_t)(a + (f | b) + 1);
		}
	}
	if (a == 0) {
		return 0;
	}
LAB_004a22b0:
	if (b < f) {
		sk_x_004ac168(v, b, v);
	}
	res = sk_x_000839f8();
	return res;
}

/* FUN_004a25ec @ 0x4a25ec   (est. sk_x_004a25ec)
 * Ghidra: void FUN_004a25ec(undefined1 param_1 [16],undefined1 param_2 [16])
 * Allocates a 4-word record via sk_x_004aca80() and fills it with the two
 * pair arguments param_1 (words [0],[1]) and param_2 (words [2],[3]), then
 * runs the commit/finalize sequence sk_x_0036b270 (three times). Returns void.
 * Confidence: low
 * Notes: extraout_d0 / extraout_var are unrecoverable register residues stored
 * into the record's first two words. */
static void sk_x_004a25ec(cl4_result_t param_1, cl4_result_t param_2)
{
	uint64_t *p;
	uint64_t u2;
	uint64_t u3;
	uint64_t res_d0;    /* extraout_d0  */
	uint64_t res_var;   /* extraout_var */

	u3 = param_2.hi;
	u2 = param_2.lo;
	p = (uint64_t *)sk_x_004aca80();
	p[1] = res_var;
	p[0] = res_d0;
	p[3] = u3;
	p[2] = u2;
	sk_x_0036b270(res_d0);
	sk_x_0036b270();
	sk_x_0036b270();
}

/* FUN_004a2634 @ 0x4a2634   (est. sk_x_004a2634)
 * Ghidra: void FUN_004a2634(void)
 * Rebuilds the object at caller register base unaff_x20 by copying the
 * 0x20-byte leading image from unaff_x19 (+8..+0x18), releasing displaced
 * destination fields (sk_x_0036b118/sk_x_0036b270/sk_x_0034b044). Returns void.
 * Confidence: medium
 * Notes: unaff_x19/unaff_x20 register bases represented as locals src/dst. */
static void sk_x_004a2634(void)
{
	uint64_t src;
	uint64_t dst;
	uint64_t v;
	uint64_t w;

	sk_x_0034b044();
	sk_x_0036b270();
	sk_x_0036b118();
	v = *(uint64_t *)(dst + 8);
	*(uint64_t *)(dst + 8) = *(uint64_t *)(src + 8);
	sk_x_0036b270();
	sk_x_0036b118(v);
	w = *(uint64_t *)(dst + 0x18);
	v = *(uint64_t *)(src + 0x18);
	*(uint64_t *)(dst + 0x18) = *(uint64_t *)(src + 0x18);
	*(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
	sk_x_0036b270(v);
	sk_x_0036b118(w);
}

/* FUN_004a26a0 @ 0x4a26a0   (est. sk_x_004a26a0)
 * Ghidra: void FUN_004a26a0(void)
 * Rebuilds part of the object at caller register base unaff_x20 from the
 * object at unaff_x19: dereferences the pair returned by sk_x_003504d0() and
 * releases its first word (sk_x_0036b118), runs sk_x_004ac45c(), then copies
 * the +0x10/+0x18 words from source to destination and releases the displaced
 * destination word. Returns void.
 * Confidence: medium
 * Notes: unaff_x19/unaff_x20 register bases represented as locals src/dst. */
static void sk_x_004a26a0(void)
{
	uint64_t *p;
	uint64_t src;
	uint64_t dst;
	uint64_t v;

	p = (uint64_t *)sk_x_003504d0();
	sk_x_0036b118(*p);
	sk_x_004ac45c();
	v = *(uint64_t *)(dst + 0x18);
	*(uint64_t *)(dst + 0x18) = *(uint64_t *)(src + 0x18);
	*(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
	sk_x_0036b118(v);
}

/* FUN_004a2718 @ 0x4a2718   (est. sk_x_004a2718)
 * Ghidra: void FUN_004a2718(long param_1)
 * Tear-down helper: if the count word at param_1+0x30 is > 1, calls
 * sk_x_000026e8 on param_1+0x18 (releasing a child list/object), then always
 * releases the object at param_1+0x40 via sk_x_003a25d4. Returns void.
 * Confidence: high */
static void sk_x_004a2718(uint64_t param_1)
{
	if (1 < *(uint64_t *)(param_1 + 0x30)) {
		sk_x_000026e8(param_1 + 0x18);
	}
	sk_x_003a25d4(*(uint64_t *)(param_1 + 0x40));
}

/* FUN_004a2754 @ 0x4a2754   (est. sk_x_004a2754)
 * Ghidra: void FUN_004a2754(undefined8 param_1,undefined8 param_2,long param_3)
 * Object teardown / re-registration: runs sk_x_00350c5c() and sk_x_004ac3c0();
 * if the carry flag (in_ZR) from that call is set, calls sk_x_004ac3a8();
 * otherwise copies the +8/+0x10 words of unaff_x20 into a record at
 * extraout_x8 and either stores a pair from sk_x_004ab10c() into unaff_x19+0x28
 * (when param_3 == 0) or stores param_3 at unaff_x19+0x30, runs sk_x_0034b07c()
 * and an indirect call at *extraout_x16 on (x19+0x18, x20+0x18). Finally runs
 * sk_x_004abe08() and sk_x_0036b270(). Returns void.
 * Confidence: low
 * Notes: in_ZR is the NZCV carry from sk_x_004ac3c0(); extraout_x8/x16 and
 * unaff_x19/unaff_x20 are register residues/bases (locals here). */
static void sk_x_004a2754(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
	cl4_result_t r;
	uint64_t *x8;       /* extraout_x8  */
	uint64_t *x16;      /* extraout_x16 */
	uint64_t x19;       /* unaff_x19    */
	uint64_t x20;       /* unaff_x20    */
	uint64_t u;
	bool carry;         /* in_ZR */

	sk_x_00350c5c();
	sk_x_004ac3c0();
	if (carry) {
		sk_x_004ac3a8();
	} else {
		u = *(uint64_t *)(x20 + 8);
		x8[1] = *(uint64_t *)(x20 + 0x10);
		x8[0] = u;
		if (param_3 == 0) {
			r = sk_x_004ab10c();
			*(cl4_result_t *)(x19 + 0x28) = r;
		} else {
			*(uint64_t *)(x19 + 0x30) = param_3;
			sk_x_0034b07c();
			((void (*)(uint64_t, uint64_t))*x16)(x19 + 0x18, x20 + 0x18);
		}
	}
	sk_x_004abe08();
	sk_x_0036b270();
}


/* FUN_004a27cc @ 0x004a27cc   (est. sk_x_004a27cc)
 * Ghidra: void FUN_004a27cc(undefined8 param_1,long param_2,long param_3)
 * Object-ref/context teardown+rebuild helper. Resolves the current context via
 * sk_x_0034f2f4 (returns a 16-byte pair whose two 8-byte words carry pointers
 * read at +0x30), then branches on a pair of state words at +0x30 to decide
 * which re-initialization path to run, finally copying a +0x38 word from the
 * source object into the working context and running a set of finalizers.
 * Side effects: updates the caller context object at unaff_x19, releases and
 * re-acquires several sub-objects through the sk_x_0036b118/sk_x_0036b270 pair.
 * Confidence: low
 * Notes: unaff_x19 is the preserved current-context pointer; extraout_x8/x16
 * are register-return artifacts from the helper calls. */
static void sk_x_004a27cc(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t extraout_x8;
    uint64_t lVar1;
    uint64_t *extraout_x16;
    uint64_t unaff_x19;
    cl4_result_t auVar2;

    auVar2 = sk_x_0034f2f4();
    lVar1 = *(uint64_t *)(auVar2.hi + 0x30);
    if (*(uint64_t *)(auVar2.lo + 0x30) == 1) {
        if (lVar1 == 1) {
            sk_x_004abe40();
            goto LAB_004a2880;
        }
        sk_x_004acac0();
        param_3 = *(uint64_t *)(param_2 + 0x30);
    LAB_004a284c:
        if (param_3 != 0) {
            *(uint64_t *)(unaff_x19 + 0x30) = param_3;
            sk_x_0034b07c();
            /* indirect call: (*(code *)*extraout_x16)(unaff_x19+0x18, param_2+0x18) */
            ((void (*)(uint64_t, uint64_t))*extraout_x16)(unaff_x19 + 0x18, param_2 + 0x18);
            goto LAB_004a2880;
        }
    } else {
        if (lVar1 == 1) {
            sk_x_004aaa88();
            sk_x_004a4b14(unaff_x19 + 8);
            sk_x_004abb64();
            goto LAB_004a2880;
        }
        sk_x_004ac390();
        if (extraout_x8 == 0) goto LAB_004a284c;
        if (param_3 != 0) {
            sk_x_0032b65c(unaff_x19 + 0x18, param_2 + 0x18);
            goto LAB_004a2880;
        }
        sk_x_000026e8(unaff_x19 + 0x18);
    }
    sk_x_004ab954();
LAB_004a2880:
    *(uint64_t *)(unaff_x19 + 0x38) = *(uint64_t *)(param_2 + 0x38);
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_003a25d4();
    sk_x_004abdec();
    return;
}

/* FUN_004a28b8 @ 0x004a28b8   (est. sk_x_004a28b8)
 * Ghidra: void FUN_004a28b8(void)
 * Context/object teardown path: resets state via sk_x_00350c5c and
 * sk_x_004ac264, then, on the (artifact) zero-flag, either reinitializes the
 * sub-object at unaff_x19+0x18 (or panics it via sk_x_000026e8) depending on a
 * word at unaff_x20+0x30, or runs the sk_x_004aaa88 / sk_x_004a4b14 re-init
 * pair. Ends with a fixed tail of three calls.
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 are preserved context pointers; in_ZR is the
 * zero-flag register artifact from the sk_x_004ac264 call. */
static void sk_x_004a28b8(void)
{
    uint64_t in_ZR;
    uint64_t extraout_x8;
    uint64_t unaff_x19;
    uint64_t unaff_x20;

    sk_x_00350c5c();
    sk_x_004ac264();
    if (!(in_ZR)) {
        if (*(uint64_t *)(unaff_x20 + 0x30) != 1) {
            sk_x_004acac0();
            if (extraout_x8 != 0) {
                sk_x_000026e8(unaff_x19 + 0x18);
            }
            sk_x_004ab10c();
            goto LAB_004a290c;
        }
        sk_x_004aaa88();
        sk_x_004a4b14(unaff_x19 + 8);
    }
    sk_x_004aca6c();
LAB_004a290c:
    sk_x_004acc70();
    sk_x_004abdd0();
    return;
}

/* FUN_004a29d4 @ 0x004a29d4   (est. sk_x_004a29d4)
 * Ghidra: void FUN_004a29d4(void)
 * Bulk release of the many owned sub-object slots of the context object at
 * unaff_x19. Starts with one bootstrap call and a no-arg release, then releases
 * each pointer at +0x18, +0x28, +0x38..+0x88 (with +0x20 released by
 * sk_x_003a25d4) through the sk_x_0036b118 release helper.
 * Confidence: low
 * Notes: unaff_x19 is the preserved context pointer; the +0x30 slot is skipped
 * (not owned). */
static void sk_x_004a29d4(void)
{
    uint64_t unaff_x19;

    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x18));
    sk_x_003a25d4(*(uint64_t *)(unaff_x19 + 0x20));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x28));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x38));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x40));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x48));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x50));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x58));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x60));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x70));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x78));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x80));
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x88));
    return;
}

/* FUN_004a2a60 @ 0x004a2a60   (est. sk_x_004a2a60)
 * Ghidra: void FUN_004a2a60(void)
 * Context migration/copy helper: reads a series of word pointers from the
 * source objects produced by the helper calls (via their extraout_x1 register
 * returns) and stores them into the context object at unaff_x19 at +0x28,
 * +0x70, +0x78, +0x80 and +0x88, interleaved with retain/release pairs
 * (sk_x_0036b270/sk_x_0036b118) around the borrowed pointers.
 * Confidence: low
 * Notes: unaff_x19 is the preserved destination context pointer; the
 * extraout_x1_* locals are register-return artifacts from each preceding call. */
static void sk_x_004a2a60(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t extraout_x1;
    uint64_t extraout_x1_00;
    uint64_t extraout_x1_01;
    uint64_t extraout_x1_02;
    uint64_t unaff_x19;
    uint64_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    uint64_t uVar9;

    sk_x_004aac14();
    uVar1 = *(uint64_t *)(extraout_x1 + 0x20);
    uVar2 = *(uint64_t *)(extraout_x1 + 0x28);
    *(uint64_t *)(unaff_x19 + 0x28) = uVar2;
    sk_x_004abcc0();
    uVar4 = *(uint64_t *)(extraout_x1_00 + 0x50);
    sk_x_004abee0();
    uVar5 = *(uint64_t *)(extraout_x1_01 + 0x60);
    sk_x_004ab74c();
    uVar6 = *(uint64_t *)(extraout_x1_02 + 0x78);
    uVar9 = *(uint64_t *)(extraout_x1_02 + 0x70);
    uVar3 = *(uint64_t *)(extraout_x1_02 + 0x88);
    uVar8 = *(uint64_t *)(extraout_x1_02 + 0x88);
    uVar7 = *(uint64_t *)(extraout_x1_02 + 0x80);
    *(uint64_t *)(unaff_x19 + 0x78) = *(uint64_t *)(extraout_x1_02 + 0x78);
    *(uint64_t *)(unaff_x19 + 0x70) = uVar9;
    *(uint64_t *)(unaff_x19 + 0x88) = uVar8;
    *(uint64_t *)(unaff_x19 + 0x80) = uVar7;
    sk_x_0036b270();
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(uVar1);
    sk_x_0036b270(uVar2);
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270();
    sk_x_004ac3d8();
    sk_x_0036b270(uVar4);
    sk_x_004ac550();
    sk_x_0036b270(uVar5);
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(uVar6);
    sk_x_004ac4ac();
    sk_x_0036b270(uVar3);
    return;
}

/* FUN_004a2b3c @ 0x004a2b3c   (est. sk_x_004a2b3c)
 * Ghidra: void FUN_004a2b3c(void)
 * Copies the two-word header (offset +8 and +0x10) from the source object at
 * unaff_x20 into the destination context at unaff_x19, then runs a long chain
 * of alternating setup calls and sk_x_0036b118/sk_x_0036b270 retain/release
 * helpers. Ends by swapping the +0x88 pointer of x19 with x20 and releasing the
 * old value.
 * Confidence: low
 * Notes: unaff_x19 destination / unaff_x20 source preserved context pointers;
 * the +0x10 copy is a single byte. */
static void sk_x_004a2b3c(void)
{
    uint64_t uVar1;
    uint64_t unaff_x19;
    uint64_t unaff_x20;

    sk_x_004aae14();
    sk_x_0036b118();
    uVar1 = *(uint64_t *)(unaff_x20 + 8);
    *(uint8_t *)(unaff_x19 + 0x10) = *(uint8_t *)(unaff_x20 + 0x10);
    *(uint64_t *)(unaff_x19 + 8) = uVar1;
    sk_x_004aaaf4();
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_003a25d4();
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004ab230();
    sk_x_0036b118();
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aba60();
    sk_x_0036b118();
    sk_x_004aba50();
    sk_x_0036b118();
    sk_x_004aba70();
    sk_x_0036b118();
    sk_x_004abda8();
    sk_x_0036b118();
    sk_x_004ab734();
    sk_x_0036b118();
    sk_x_004abbe0();
    sk_x_0036b118();
    sk_x_004abbc4();
    sk_x_0036b118();
    uVar1 = *(uint64_t *)(unaff_x19 + 0x88);
    *(uint64_t *)(unaff_x19 + 0x88) = *(uint64_t *)(unaff_x20 + 0x88);
    sk_x_0036b270();
    sk_x_0036b118(uVar1);
    return;
}

/* FUN_004a2c3c @ 0x004a2c3c   (est. sk_x_004a2c3c)
 * Ghidra: void FUN_004a2c3c(void)
 * Context swap/copy helper: copies the +8/+0x10 header words and the +0x30 and
 * +0x68 single bytes from source object at unaff_x20 into the context at
 * unaff_x19, while swapping the +0x70/+0x78 and +0x80/+0x88 pointer pairs
 * between the two objects, releasing each displaced pointer via
 * sk_x_0036b118. Interleaved with retain (sk_x_0036b270) of +0x18/+0x38/
 * +0x48/+0x58/+0x70 and a series of setup calls.
 * Confidence: low
 * Notes: unaff_x19 destination / unaff_x20 source preserved context pointers. */
static void sk_x_004a2c3c(void)
{
    uint64_t uVar1;
    uint64_t unaff_x19;
    uint64_t unaff_x20;
    uint64_t uVar2;

    sk_x_004aaf48();
    sk_x_004accf0();
    *(uint64_t *)(unaff_x19 + 8) = *(uint64_t *)(unaff_x20 + 8);
    *(uint8_t *)(unaff_x19 + 0x10) = *(uint8_t *)(unaff_x20 + 0x10);
    sk_x_004aaaf4();
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x18));
    sk_x_004abec0();
    sk_x_003a25d4();
    sk_x_004ac42c();
    *(uint8_t *)(unaff_x19 + 0x30) = *(uint8_t *)(unaff_x20 + 0x30);
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x38));
    sk_x_004ac40c();
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x48));
    sk_x_004ac4d0();
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x58));
    sk_x_004ac3fc();
    *(uint8_t *)(unaff_x19 + 0x68) = *(uint8_t *)(unaff_x20 + 0x68);
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x70));
    uVar1 = *(uint64_t *)(unaff_x19 + 0x78);
    uVar2 = *(uint64_t *)(unaff_x20 + 0x70);
    *(uint64_t *)(unaff_x19 + 0x78) = *(uint64_t *)(unaff_x20 + 0x78);
    *(uint64_t *)(unaff_x19 + 0x70) = uVar2;
    sk_x_0036b118(uVar1);
    sk_x_0036b118(*(uint64_t *)(unaff_x19 + 0x80));
    uVar1 = *(uint64_t *)(unaff_x19 + 0x88);
    uVar2 = *(uint64_t *)(unaff_x20 + 0x80);
    *(uint64_t *)(unaff_x19 + 0x88) = *(uint64_t *)(unaff_x20 + 0x88);
    *(uint64_t *)(unaff_x19 + 0x80) = uVar2;
    sk_x_0036b118(uVar1);
    return;
}

/* FUN_004a2ea8 @ 0x004a2ea8   (est. sk_x_004a2ea8)
 * Ghidra: void FUN_004a2ea8(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Looks up a per-context capability/object: runs two setup helpers, passes
 * *param_3 to sk_x_00027754, then stores the result of sk_x_00376820 against a
 * fixed global data table (DAT_005a47d0) into the context object at
 * unaff_x20+8.
 * Confidence: low
 * Notes: unaff_x20 is the preserved context pointer; DAT_005a47d0 is a global
 * data address (rendered as literal 0x5a47d0). */
static void sk_x_004a2ea8(uint64_t param_1, uint64_t param_2, uint64_t *param_3)
{
    uint64_t uVar1;
    uint64_t unaff_x20;

    sk_x_003504d0();
    sk_x_00027754(*param_3);
    uVar1 = sk_x_00376820((uint64_t *)0x5a47d0); /* &DAT_005a47d0 */
    *(uint64_t *)(unaff_x20 + 8) = uVar1;
    return;
}

/* FUN_004a2fa8 @ 0x004a2fa8   (est. sk_x_004a2fa8)
 * Ghidra: long FUN_004a2fa8(ulong param_1)
 * If the tag bit (param_1 & 1) is set, dereferences the pointer at the
 * cleared-tag address to obtain the real object, then returns the offset-+8
 * pointer plus the signed 32-bit length stored at that +8 field (an end-address
 * computation over an 8-byte-header region).
 * Confidence: high
 * Notes: pointer tagging: bit 0 marks an indirect (pointer-to-pointer) entry. */
static uint64_t sk_x_004a2fa8(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffe);
    }
    return (uint64_t)((int64_t)(param_1 + 8) + (int64_t)*(int32_t *)(param_1 + 8));
}

/* FUN_004a2fd8 @ 0x004a2fd8   (est. sk_x_004a2fd8)
 * Ghidra: long FUN_004a2fd8(ulong param_1)
 * Like sk_x_004a2fa8 but for a region with a 0x14-byte header: returns the
 * offset-+0x14 pointer plus the signed 32-bit length stored at +0x14. Tag bit 0
 * marks an indirect (pointer-to-pointer) entry that is dereferenced first.
 * Confidence: high
 * Notes: pointer tagging: bit 0 marks an indirect entry. */
static uint64_t sk_x_004a2fd8(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffe);
    }
    return (uint64_t)((int64_t)(param_1 + 0x14) + (int64_t)*(int32_t *)(param_1 + 0x14));
}

/* FUN_004a3008 @ 0x004a3008   (est. sk_x_004a3008)
 * Ghidra: long FUN_004a3008(ulong param_1)
 * Returns the offset-+0x10 pointer plus the signed 32-bit length stored at
 * +0x10 of the (possibly tag-dereferenced) object. Tag bit 0 marks an indirect
 * (pointer-to-pointer) entry that is dereferenced first.
 * Confidence: high
 * Notes: pointer tagging: bit 0 marks an indirect entry. */
static uint64_t sk_x_004a3008(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffe);
    }
    return (uint64_t)((int64_t)(param_1 + 0x10) + (int64_t)*(int32_t *)(param_1 + 0x10));
}

/* FUN_004a3038 @ 0x004a3038   (est. sk_x_004a3038)
 * Ghidra: void FUN_004a3038(void)
 * Thin wrapper: forwards directly to the boot/entry helper sk_x_00021480.
 * Confidence: high
 * Notes: trivial tail-call wrapper. */
static void sk_x_004a3038(void)
{
    sk_x_00021480();
    return;
}

/* FUN_004a3050 @ 0x004a3050   (est. sk_x_004a3050)
 * Ghidra: void FUN_004a3050(undefined8 param_1,undefined8 *param_2)
 * Reads a 5-word (40-byte) argument block from param_2 into locals, retains two
 * of the words (param_2[1] and param_2[2]) via sk_x_0036b270, calls
 * sk_x_0024c9c0 with param_1 and a pointer to the copied block, then releases
 * the retained words again via sk_x_0036b118.
 * Confidence: low
 * Notes: the copied block is a 5-word struct; the release helpers are the
 * sk_x_0036b118/sk_x_0036b270 retain-release pair. */
static void sk_x_004a3050(uint64_t param_1, uint64_t *param_2)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t local_58;
    uint64_t local_50;
    uint64_t uStack_48;
    uint64_t uStack_40;
    uint64_t uStack_38;

    local_58 = *param_2;
    uVar1 = param_2[2];
    uStack_48 = param_2[2];
    uVar2 = param_2[1];
    uStack_38 = param_2[4];
    uStack_40 = param_2[3];
    local_50 = uVar2;
    sk_x_0036b270(uVar2);
    sk_x_0036b270(uVar1);
    sk_x_0024c9c0(param_1, &local_58);
    sk_x_003a25d4(uVar2);
    sk_x_0036b118(uVar1);
    return;
}

/* FUN_004a30d4 @ 0x004a30d4   (est. sk_x_004a30d4)
 * Ghidra: void FUN_004a30d4(void)
 * Thin wrapper: forwards directly to the boot/entry helper sk_x_00021480
 * (identical to sk_x_004a3038).
 * Confidence: high
 * Notes: trivial tail-call wrapper. */
static void sk_x_004a30d4(void)
{
    sk_x_00021480();
    return;
}

/* FUN_004a30ec @ 0x004a30ec   (est. sk_x_004a30ec)
 * Ghidra: long FUN_004a30ec(ulong param_1)
 * Returns the offset-+0x10 pointer plus the signed 32-bit length stored at
 * +0x10 of the (possibly tag-dereferenced) object. Identical shape to
 * sk_x_004a3008; tag bit 0 marks an indirect (pointer-to-pointer) entry.
 * Confidence: high
 * Notes: pointer tagging: bit 0 marks an indirect entry. */
static uint64_t sk_x_004a30ec(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffe);
    }
    return (uint64_t)((int64_t)(param_1 + 0x10) + (int64_t)*(int32_t *)(param_1 + 0x10));
}

/* FUN_004a311c @ 0x004a311c   (est. sk_x_004a311c)
 * Ghidra: void FUN_004a311c(void)
 * Re-initializes a sub-object of the context at unaff_x20: passes the pointer
 * at +0x10 to sk_x_004abf50, releases two word slots (+0x18 masked to 52 bits
 * via sk_x_0036b118, plus a no-arg release), runs sk_x_00002834 and finishes
 * with sk_x_0036b21c.
 * Confidence: low
 * Notes: unaff_x20 is the preserved context pointer; the +0x18 value is masked
 * with 0xfffffffffffffff before release. */
static void sk_x_004a311c(void)
{
    uint64_t unaff_x20;

    sk_x_004abf50(*(uint64_t *)(unaff_x20 + 0x10));
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(unaff_x20 + 0x18) & 0xfffffffffffffff);
    sk_x_00002834();
    sk_x_0036b21c();
    return;
}
/* FUN_004a3120 @ 0x4a3120   (est. sk_x_004a3120)
 * Ghidra: void FUN_004a3120(void)
 * Runs on a caller-established context (unaff_x20): calls the object/state
 * flush at offset 0x10, then signals via sk_x_0036b118 with a masked field at
 * 0x18, finishes with an unmasked signal, an init tick, and the shared
 * post-op barrier sk_x_0036b21c. No inputs or outputs beyond the context.
 * Confidence: low
 * Notes: unaff_x20 is a register-held context pointer not recoverable in C;
 *         represented as a local `ctx`. */
static void sk_x_004a3120(void) {
    /* ctx: unaff_x20 (context pointer established by caller) */
    uint8_t *ctx = NULL;
    sk_x_004abf50(*(uint64_t *)(ctx + 0x10));
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(ctx + 0x18) & 0xfffffffffffffff);
    sk_x_00002834();
    sk_x_0036b21c();
}

/* FUN_004a3154 @ 0x4a3154   (est. sk_x_004a3154)
 * Ghidra: void FUN_004a3154(void)
 * Forwards the four 8-byte words at context (unaff_x20) offsets 0x20-0x38 to
 * sk_x_00458940, then runs the shared post-op barrier sk_x_0036b21c. No return
 * value or side effects other than the forwarded call.
 * Confidence: low
 * Notes: unaff_x20 is a register-held context pointer represented as `ctx`. */
static void sk_x_004a3154(void) {
    uint8_t *ctx = NULL;
    sk_x_00458940(*(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
                  *(uint64_t *)(ctx + 0x30), *(uint64_t *)(ctx + 0x38));
    sk_x_0036b21c();
}

/* FUN_004a3158 @ 0x4a3158   (est. sk_x_004a3158)
 * Ghidra: void FUN_004a3158(void)
 * Byte-identical to sk_x_004a3154: forwards the four 8-byte words at context
 * (unaff_x20) offsets 0x20-0x38 to sk_x_00458940, then the post-op barrier
 * sk_x_0036b21c. Likely a duplicated alias/trampoline of the same forwarding
 * action.
 * Confidence: low
 * Notes: unaff_x20 register-held context pointer represented as `ctx`. */
static void sk_x_004a3158(void) {
    uint8_t *ctx = NULL;
    sk_x_00458940(*(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
                  *(uint64_t *)(ctx + 0x30), *(uint64_t *)(ctx + 0x38));
    sk_x_0036b21c();
}

/* FUN_004a3184 @ 0x4a3184   (est. sk_x_004a3184)
 * Ghidra: void FUN_004a3184(void)
 * Context (unaff_x20) teardown: runs an idle/barrier helper sk_x_004ab13c,
 * forwards three words at offsets 0x50/0x60/0x70 to sk_x_003540d0, calls
 * sk_x_004593ac, releases the object at 0x90 via sk_x_004ab998, masks the
 * register leftovers into two sk_x_0036b118 signals, runs sk_x_004ac8fc, and
 * the post-op barrier sk_x_0036b21c.
 * Confidence: low
 * Notes: unaff_x20 context pointer; unaff_x19 is a register-held mask and
 *         extraout_x8 a leftover register value from sk_x_004593ac — both
 *         represented as locals. */
static void sk_x_004a3184(void) {
    uint8_t *ctx = NULL;
    /* mask: unaff_x19 (register-held mask) */
    uint64_t mask = 0;
    /* extra: extraout_x8 (leftover register value from sk_x_004593ac) */
    uint64_t extra = 0;
    sk_x_004ab13c();
    sk_x_003540d0(*(uint64_t *)(ctx + 0x50), *(uint64_t *)(ctx + 0x60),
                  *(uint64_t *)(ctx + 0x70));
    sk_x_004593ac();
    sk_x_004ab998(*(uint64_t *)(ctx + 0x90));
    sk_x_0036b118(extra & mask);
    sk_x_0036b118(*(uint64_t *)(ctx + 0x98) & mask);
    sk_x_004ac8fc();
    sk_x_0036b21c();
}

/* FUN_004a31ec @ 0x4a31ec   (est. sk_x_004a31ec)
 * Ghidra: void FUN_004a31ec(undefined8 param_1,undefined8 param_2)
 * Thin wrapper: forwards its two arguments (reversed) to sk_x_0049ef90,
 * i.e. sk_x_0049ef90(param_2, param_1). No other work.
 * Confidence: high */
static void sk_x_004a31ec(uint64_t param_1, uint64_t param_2) {
    ((void (*)(uint64_t, uint64_t))sk_x_0049ef90)(param_2, param_1);  /* callee takes no params; args are register residue */
}

/* FUN_004a31fc @ 0x4a31fc   (est. sk_x_004a31fc)
 * Ghidra: void FUN_004a31fc(long param_1)
 * Sets capability/state flags in the word at object offset 0x98: clears all
 * but the low and high nibble bits (mask 0xf3) and ORs in 0x6000000000000000
 * (high nibble = 6). Caller-supplied object; no return.
 * Confidence: high */
static void sk_x_004a31fc(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x6000000000000000;
}

/* FUN_004a3214 @ 0x4a3214   (est. sk_x_004a3214)
 * Ghidra: void FUN_004a3214(long param_1)
 * Sets capability/state flags in the word at object offset 0x98: clears all
 * but the low and high nibble bits (mask 0xf3) and ORs in 0x4000000000000000
 * (high nibble = 4). Sibling of sk_x_004a31fc with a different flag value.
 * Confidence: high */
static void sk_x_004a3214(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x4000000000000000;
}

/* FUN_004a322c @ 0x4a322c   (est. sk_x_004a322c)
 * Ghidra: void FUN_004a322c(undefined8 *param_1)
 * Initializes a structure at param_1: sets the type word to 2, zero-fills the
 * 0x90 bytes following the header via sk_x_00114330, zeroes words at [0x14]
 * and [0x15], and stamps [0x13] with the 0x8000000000000000 (high-bit) flag.
 * Confidence: high */
static void sk_x_004a322c(uint64_t *param_1) {
    *param_1 = 2;
    sk_x_00114330(param_1 + 1, 0x90);
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x13] = 0x8000000000000000;
}

/* FUN_004a3268 @ 0x4a3268   (est. sk_x_004a3268)
 * Ghidra: void FUN_004a3268(long param_1)
 * Clears both flag words at offsets 0x98 and 0x148 down to the low+high nibble
 * bits (mask 0xf0000000000000f3), then sets the high-nibble flags in the
 * 0x148 word to 0x800000000000000 (value 8). Caller-supplied object.
 * Confidence: high */
static void sk_x_004a3268(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0x800000000000000;
}

/* FUN_004a3290 @ 0x4a3290   (est. sk_x_004a3290)
 * Ghidra: void FUN_004a3290(void)
 * Context (unaff_x20) notify helper: signals sk_x_0036b118 with the words at
 * offsets 0x10 and 0x20, then runs the post-op barrier sk_x_0036b21c.
 * Confidence: low
 * Notes: unaff_x20 register-held context pointer represented as `ctx`. */
static void sk_x_004a3290(void) {
    uint8_t *ctx = NULL;
    sk_x_0036b118(*(uint64_t *)(ctx + 0x10));
    sk_x_0036b118(*(uint64_t *)(ctx + 0x20));
    sk_x_0036b21c();
}

/* FUN_004a3294 @ 0x4a3294   (est. sk_x_004a3294)
 * Ghidra: void FUN_004a3294(void)
 * Byte-identical to sk_x_004a3290: signals sk_x_0036b118 with the context
 * (unaff_x20) words at offsets 0x10 and 0x20, then the post-op barrier
 * sk_x_0036b21c. Likely a duplicated alias.
 * Confidence: low
 * Notes: unaff_x20 register-held context pointer represented as `ctx`. */
static void sk_x_004a3294(void) {
    uint8_t *ctx = NULL;
    sk_x_0036b118(*(uint64_t *)(ctx + 0x10));
    sk_x_0036b118(*(uint64_t *)(ctx + 0x20));
    sk_x_0036b21c();
}

/* FUN_004a32c4 @ 0x4a32c4   (est. sk_x_004a32c4)
 * Ghidra: void FUN_004a32c4(long param_1)
 * Clears both flag words at offsets 0x98 and 0x148 down to the low+high nibble
 * bits (mask 0xf0000000000000f3), then sets the high-nibble flags in the
 * 0x148 word to 0xe00000000000000 (value 0xe). Sibling flag-setter of
 * sk_x_004a3268 with a different value.
 * Confidence: high */
static void sk_x_004a32c4(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0xe00000000000000;
}

/* FUN_004a32ec @ 0x4a32ec   (est. sk_x_004a32ec)
 * Ghidra: void FUN_004a32ec(long param_1)
 * Clears both flag words at offsets 0x98 and 0x148 down to the low+high nibble
 * bits (mask 0xf0000000000000f3), then sets the high-nibble flags in the
 * 0x148 word to 0xa00000000000000 (value 0xa). Sibling flag-setter.
 * Confidence: high */
static void sk_x_004a32ec(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0xa00000000000000;
}

/* FUN_004a3318 @ 0x4a3318   (est. sk_x_004a3318)
 * Ghidra: void FUN_004a3318(long param_1)
 * Clears both flag words at offsets 0x98 and 0x148 down to the low+high nibble
 * bits (mask 0xf0000000000000f3), then sets the high-nibble flags in the
 * 0x148 word to 0xc00000000000000 (value 0xc). Sibling flag-setter.
 * Confidence: high */
static void sk_x_004a3318(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0xc00000000000000;
}

/* FUN_004a3340 @ 0x4a3340   (est. sk_x_004a3340)
 * Ghidra: void FUN_004a3340(long param_1)
 * Clears both flag words at offsets 0x98 and 0x148 down to the low+high nibble
 * bits (mask 0xf0000000000000f3), then sets the high-nibble flags in the
 * 0x148 word to 0x600000000000000 (value 6). Sibling flag-setter.
 * Confidence: high */
static void sk_x_004a3340(uint64_t param_1) {
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0x600000000000000;
}
/* FUN_004a3368 @ 0x4a3368   (est. sk_x_004a3368)
 * Ghidra: void FUN_004a3368(long param_1)
 * Masks the capability-state field at +0x98 with 0xf0000000000000f3, and ORs the
 * +0x148 state field with bit 0x200000000000000 while clearing the same mask bits.
 * Mutates two per-object control words; no return value.
 * Confidence: medium
 * Notes: plain bit-clear/set on two 64-bit fields. */
static void sk_x_004a3368(uint64_t param_1)
{
	*(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
	*(uint64_t *)(param_1 + 0x148) = *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0x200000000000000;
	return;
}

/* FUN_004a3390 @ 0x4a3390   (est. sk_x_004a3390)
 * Ghidra: void FUN_004a3390(long param_1)
 * Same field-masking pattern as sk_x_004a3368, but sets the +0x148 field bit
 * 0x400000000000000 instead. Mutates two per-object control words.
 * Confidence: medium
 * Notes: sibling of 0x4a3368. */
static void sk_x_004a3390(uint64_t param_1)
{
	*(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
	*(uint64_t *)(param_1 + 0x148) = *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3 | 0x400000000000000;
	return;
}

/* FUN_004a33b8 @ 0x4a33b8   (est. sk_x_004a33b8)
 * Ghidra: void FUN_004a33b8(void)
 * Uses the caller-preserved base register (unaff_x20, object pointer): reads the
 * +0x28 field into sk_x_0036b118, then calls sk_x_00355538 and sk_x_0036b21c.
 * Sequence of three teardown/release-style calls on the object.
 * Confidence: low
 * Notes: unaff_x20 -> local 'base' (preserved register, value from caller). */
static void sk_x_004a33b8(void)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_0036b118(*(uint64_t *)(base + 0x28));
	sk_x_00355538();
	sk_x_0036b21c();
	return;
}

/* FUN_004a33bc @ 0x4a33bc   (est. sk_x_004a33bc)
 * Ghidra: void FUN_004a33bc(void)
 * Identical body to sk_x_004a33b8: three teardown calls, reading the +0x28 field
 * from the preserved base register (unaff_x20).
 * Confidence: low
 * Notes: duplicate of 0x4a33b8. */
static void sk_x_004a33bc(void)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_0036b118(*(uint64_t *)(base + 0x28));
	sk_x_00355538();
	sk_x_0036b21c();
	return;
}

/* FUN_004a33e0 @ 0x4a33e0   (est. sk_x_004a33e0)
 * Ghidra: void FUN_004a33e0(undefined8 param_1)
 * Forwards param_1 plus four fields read from the preserved base register
 * (unaff_x20 +0x20, +0x28, +0x10, +0x18) into sk_x_00492c6c. A dispatcher/trampoline
 * for a method-style call with five arguments.
 * Confidence: low
 * Notes: unaff_x20 -> local 'base'. */
static void sk_x_004a33e0(uint64_t param_1)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_00492c6c(param_1, *(uint64_t *)(base + 0x20), *(uint64_t *)(base + 0x28),
	              *(uint64_t *)(base + 0x10), *(uint64_t *)(base + 0x18));
	return;
}

/* FUN_004a33e4 @ 0x4a33e4   (est. sk_x_004a33e4)
 * Ghidra: void FUN_004a33e4(undefined8 param_1)
 * Identical forwarding body to sk_x_004a33e0: param_1 plus four preserved-base
 * fields (+0x20, +0x28, +0x10, +0x18) into sk_x_00492c6c.
 * Confidence: low
 * Notes: duplicate of 0x4a33e0. */
static void sk_x_004a33e4(uint64_t param_1)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_00492c6c(param_1, *(uint64_t *)(base + 0x20), *(uint64_t *)(base + 0x28),
	              *(uint64_t *)(base + 0x10), *(uint64_t *)(base + 0x18));
	return;
}

/* FUN_004a3400 @ 0x4a3400   (est. sk_x_004a3400)
 * Ghidra: void FUN_004a3400(void)
 * Thin trampoline that immediately calls sk_x_004a3458 with no arguments.
 * Confidence: low
 * Notes: single forward call. */
static void sk_x_004a3400(void)
{
	((void (*)(void))sk_x_004a3458)();  /* callee takes 4 params; decompile shows none (register residue) */
	return;
}

/* FUN_004a3418 @ 0x4a3418   (est. sk_x_004a3418)
 * Ghidra: void FUN_004a3418(void)
 * Thin trampoline that immediately calls sk_x_00492b3c with no arguments.
 * Confidence: low
 * Notes: single forward call. */
static void sk_x_004a3418(void)
{
	sk_x_00492b3c();
	return;
}

/* FUN_004a341c @ 0x4a341c   (est. sk_x_004a341c)
 * Ghidra: void FUN_004a341c(void)
 * Thin trampoline that immediately calls sk_x_00492b3c with no arguments.
 * Confidence: low
 * Notes: duplicate of 0x4a3418. */
static void sk_x_004a341c(void)
{
	sk_x_00492b3c();
	return;
}

/* FUN_004a3438 @ 0x4a3438   (est. sk_x_004a3438)
 * Ghidra: void FUN_004a3438(undefined8 param_1)
 * Forwards param_1 plus four fields read from the preserved base register
 * (unaff_x20 +0x20, +0x28, +0x10, +0x18) into sk_x_00492920. Method-style
 * dispatcher with five arguments.
 * Confidence: low
 * Notes: unaff_x20 -> local 'base'. */
static void sk_x_004a3438(uint64_t param_1)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_00492920(param_1, *(uint64_t *)(base + 0x20), *(uint64_t *)(base + 0x28),
	              *(uint64_t *)(base + 0x10), *(uint64_t *)(base + 0x18));
	return;
}

/* FUN_004a343c @ 0x4a343c   (est. sk_x_004a343c)
 * Ghidra: void FUN_004a343c(undefined8 param_1)
 * Identical forwarding body to sk_x_004a3438: param_1 plus four preserved-base
 * fields (+0x20, +0x28, +0x10, +0x18) into sk_x_00492920.
 * Confidence: low
 * Notes: duplicate of 0x4a3438. */
static void sk_x_004a343c(uint64_t param_1)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	sk_x_00492920(param_1, *(uint64_t *)(base + 0x20), *(uint64_t *)(base + 0x28),
	              *(uint64_t *)(base + 0x10), *(uint64_t *)(base + 0x18));
	return;
}

/* FUN_004a3458 @ 0x4a3458   (est. sk_x_004a3458)
 * Ghidra: void FUN_004a3458(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Packs its four arguments into four contiguous 64-bit stack locals and calls a
 * function pointer stored at the preserved base register +0x20 (unaff_x20),
 * passing the address of the packed 32-byte argument block. Indirect method call.
 * Confidence: low
 * Notes: unaff_x20 -> local 'base'; call is (*(base+0x20))(&block). */
static void sk_x_004a3458(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
{
	uint64_t base; /* unaff_x20: caller-provided preserved register (object pointer) */
	uint64_t local_40;
	uint64_t uStack_38;
	uint64_t local_30;
	uint64_t local_28;

	local_40 = param_1;
	uStack_38 = param_2;
	local_30 = param_3;
	local_28 = param_4;
	(*(void (*)(uint64_t *))(base + 0x20))(&local_40);
	return;
}

/* FUN_004a3494 @ 0x4a3494   (est. sk_x_004a3494)
 * Ghidra: void FUN_004a3494(void)
 * Thin trampoline that immediately calls sk_x_00492850 with no arguments.
 * Confidence: low
 * Notes: single forward call. */
static void sk_x_004a3494(void)
{
	sk_x_00492850();
	return;
}

/* FUN_004a3498 @ 0x4a3498   (est. sk_x_004a3498)
 * Ghidra: void FUN_004a3498(void)
 * Thin trampoline that immediately calls sk_x_00492850 with no arguments.
 * Confidence: low
 * Notes: duplicate of 0x4a3494. */
static void sk_x_004a3498(void)
{
	sk_x_00492850();
	return;
}

/* FUN_004a34b4 @ 0x4a34b4   (est. sk_x_004a34b4)
 * Ghidra: void FUN_004a34b4(undefined8 *param_1)
 * Reads a flags/type word at (*(param_1[3] - 8) + 0x50). If bit 0x11 is clear,
 * returns immediately. Otherwise extracts the low byte as a size/count (uVar2),
 * computes a pointer from (*(param_1[3] - 8) + 0x40) offset by
 * (uVar2 + 0x10) & ~uVar2, and calls sk_x_00012568(*param_1, ptr, uVar2 | 7).
 * Looks like a conditional deferred/teardown operation on a descriptor.
 * Confidence: low
 * Notes: thunk_FUN_00012568 -> sk_x_00012568; (uVar2+0x10) & ~uVar2 rounds up
 * to a power-of-two boundary. */
static void sk_x_004a34b4(uint64_t *param_1)
{
	uint32_t uVar1;
	uint64_t uVar2;

	uVar1 = *(uint32_t *)(*(uint64_t *)(param_1[3] + -8) + 0x50);
	if ((uVar1 >> 0x11 & 1) == 0) {
		return;
	}
	uVar2 = (uint64_t)uVar1 & 0xff;
	sk_x_00012568(*param_1, *(uint64_t *)(*(uint64_t *)(param_1[3] + -8) + 0x40) +
	                        (uVar2 + 0x10 & (uVar2 ^ 0xffffffffffffffff)), uVar2 | 7);
	return;
}
/* FUN_004a34f0 @ 0x004a34f0   (est. sk_x_004a34f0)
 * Ghidra: void FUN_004a34f0(undefined8 param_1,undefined8 param_2)
 * Forwards the two arguments (swapped) to the out-of-slice helper sk_x_004a96a0.
 * Thin shim/tail-call wrapper with no state of its own.
 * Confidence: high
 * Notes: call order (param_2, param_1) is reversed vs. caller argument order. */
static void sk_x_004a34f0(uint64_t param_1, uint64_t param_2)
{
    sk_x_004a96a0(param_2, param_1);
    return;
}

/* FUN_004a3500 @ 0x004a3500   (est. sk_x_004a3500)
 * Ghidra: undefined8 FUN_004a3500(undefined8 param_1)
 * Calls the out-of-slice helper sk_x_004a90e4 (no arguments) then returns its
 * own input argument unchanged. A pass-through/no-op wrapper around a side-effecting helper.
 * Confidence: high
 * Notes: return value is the original param_1, not the helper's result. */
static uint64_t sk_x_004a3500(uint64_t param_1)
{
    sk_x_004a90e4();
    return param_1;
}

/* FUN_004a3528 @ 0x004a3528   (est. sk_x_004a3528)
 * Ghidra: undefined8 FUN_004a3528(undefined8 param_1)
 * Calls the out-of-slice helper sk_x_004a8ef8 (no arguments) then returns its
 * own input argument unchanged. Pass-through wrapper.
 * Confidence: high
 * Notes: return value is the original param_1, not the helper's result. */
static uint64_t sk_x_004a3528(uint64_t param_1)
{
    sk_x_004a8ef8();
    return param_1;
}

/* FUN_004a3550 @ 0x004a3550   (est. sk_x_004a3550)
 * Ghidra: void FUN_004a3550(undefined8 param_1,undefined8 param_2)
 * Forwards the two arguments (swapped) to the out-of-slice helper sk_x_004a8f0c.
 * Thin shim/tail-call wrapper.
 * Confidence: high
 * Notes: call order (param_2, param_1) is reversed vs. caller argument order. */
static void sk_x_004a3550(uint64_t param_1, uint64_t param_2)
{
    sk_x_004a8f0c(param_2, param_1);
    return;
}

/* FUN_004a3560 @ 0x004a3560   (est. sk_x_004a3560)
 * Ghidra: undefined8 FUN_004a3560(undefined8 param_1)
 * Calls the out-of-slice helper sk_x_004a83c0 (no arguments) then returns its
 * own input argument unchanged. Pass-through wrapper.
 * Confidence: high
 * Notes: return value is the original param_1, not the helper's result. */
static uint64_t sk_x_004a3560(uint64_t param_1)
{
    sk_x_004a83c0();
    return param_1;
}

/* FUN_004a3588 @ 0x004a3588   (est. sk_x_004a3588)
 * Ghidra: long FUN_004a3588(ulong param_1)
 * Resolves a tagged/locked pointer: if the low bit of param_1 is set, the real
 * pointer is loaded from the address stored at (param_1 & ~1). Returns the end
 * address of a header+payload: base + 8 + the signed 32-bit length at base+8.
 * Confidence: high
 * Notes: param_1 & 0xfffffffffffffffe strips the tag bit; *(int*)(param_1+8) is
 *       a signed length added to the base+8 offset. */
static int64_t sk_x_004a3588(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (int64_t)(param_1 + 8) + (int64_t)*(int32_t *)(param_1 + 8);
}

/* FUN_004a35b8 @ 0x004a35b8   (est. sk_x_004a35b8)
 * Ghidra: void FUN_004a35b8(void)
 * One-time lazy initializer: if the global sk_g_00657d98 (DAT_00657d98) is already non-zero it
 * returns immediately. Otherwise it builds a descriptor (uVar1 via the
 * out-of-slice helper sk_x_00027614 with two global addresses) and stores the
 * result of sk_x_00376820 into sk_g_00657d98 (DAT_00657d98), passing a pointer to a local that
 * holds the address 0x6707a8.
 * Confidence: low
 * Notes: DAT_00657d98 (init guard/result), DAT_004e8330 and local_18=0x6707a8
 *       are external/global addresses; local_18's address is passed by &local_18. */
static void sk_x_004a35b8(void)
{
    uint64_t uVar1;
    uint64_t local_18;

    if (sk_g_00657d98 != 0) {
        return;
    }
    uVar1 = sk_x_00027614(0x64e078ULL, 0x005a4b80ULL);
    local_18 = 0x6707a8ULL;
    sk_g_00657d98 = sk_x_00376820(0x004e8330ULL, uVar1, &local_18);
    return;
}

/* FUN_004a363c @ 0x004a363c   (est. sk_x_004a363c)
 * Ghidra: void FUN_004a363c(undefined8 param_1,undefined8 param_2)
 * Forwards the two arguments (swapped) to the out-of-slice helper sk_x_004a54b0.
 * Thin shim/tail-call wrapper.
 * Confidence: high
 * Notes: call order (param_2, param_1) is reversed vs. caller argument order. */
static void sk_x_004a363c(uint64_t param_1, uint64_t param_2)
{
    sk_x_004a54b0(param_2, param_1);
    return;
}

/* FUN_004a364c @ 0x004a364c   (est. sk_x_004a364c)
 * Ghidra: undefined8 FUN_004a364c(undefined8 param_1)
 * Calls the out-of-slice helper sk_x_004a5414 (no arguments) then returns its
 * own input argument unchanged. Pass-through wrapper.
 * Confidence: high
 * Notes: return value is the original param_1, not the helper's result. */
static uint64_t sk_x_004a364c(uint64_t param_1)
{
    sk_x_004a5414();
    return param_1;
}

/* FUN_004a3674 @ 0x004a3674   (est. sk_x_004a3674)
 * Ghidra: void FUN_004a3674(void)
 * Reads the value at offset 0x18 of the context object held in the preserved
 * register x20 and passes it to sk_x_0036b118, then calls the out-of-slice
 * helpers sk_x_00002834 and sk_x_0036b21c in sequence. Context-teardown helper.
 * Confidence: low
 * Notes: unaff_x20 is the preserved context base (a uint64_t holding a pointer);
 *       the value at +0x18 is a pointer-sized argument to sk_x_0036b118. */
static void sk_x_004a3674(void)
{
    uint64_t ctx;

    sk_x_0036b118(*(uint64_t *)(ctx + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
    return;
}

/* FUN_004a3678 @ 0x004a3678   (est. sk_x_004a3678)
 * Ghidra: void FUN_004a3678(void)
 * Identical in structure to sk_x_004a3674: passes the value at context+0x18 to
 * sk_x_0036b118, then calls sk_x_00002834 and sk_x_0036b21c. Context-teardown helper.
 * Confidence: low
 * Notes: unaff_x20 is the preserved context base (a uint64_t holding a pointer);
 *       the value at +0x18 is a pointer-sized argument to sk_x_0036b118. */
static void sk_x_004a3678(void)
{
    uint64_t ctx;

    sk_x_0036b118(*(uint64_t *)(ctx + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
    return;
}

/* FUN_004a369c @ 0x004a369c   (est. sk_x_004a369c)
 * Ghidra: void FUN_004a369c(void)
 * Loads a function pointer from offset 0x10 of the context object held in the
 * preserved register x20 and invokes it with no arguments. Generic dispatch/
 * callback trampoline.
 * Confidence: low
 * Notes: unaff_x20 is the preserved context base (a uint64_t holding a pointer);
 *       (**(code **)(unaff_x20 + 0x10)) is an indirect call through the pointer
 *       stored at context+0x10. */
static void sk_x_004a369c(void)
{
    uint64_t ctx;

    ((void (*)(void))*(uint64_t *)(ctx + 0x10))();
    return;
}

/* FUN_004a36c4 @ 0x004a36c4   (est. sk_x_004a36c4)
 * Ghidra: void FUN_004a36c4(undefined8 param_1,undefined8 param_2)
 * Forwards the two arguments (swapped) to the out-of-slice helper sk_x_0049dfa0.
 * Thin shim/tail-call wrapper.
 * Confidence: high
 * Notes: call order (param_2, param_1) is reversed vs. caller argument order. */
static void sk_x_004a36c4(uint64_t param_1, uint64_t param_2)
{
    sk_x_0049dfa0(param_2, param_1);
    return;
}

/* FUN_004a36d4 @ 0x004a36d4   (est. sk_x_004a36d4)
 * Ghidra: undefined8 FUN_004a36d4(undefined8 param_1)
 * Calls the out-of-slice helper sk_x_0049df60 (no arguments) then returns its
 * own input argument unchanged. Pass-through wrapper.
 * Confidence: high
 * Notes: return value is the original param_1, not the helper's result. */
static uint64_t sk_x_004a36d4(uint64_t param_1)
{
    sk_x_0049df60();
    return param_1;
}

/* FUN_004a36fc @ 0x004a36fc   (est. sk_x_004a36fc)
 * Ghidra: void FUN_004a36fc(long param_1,undefined8 param_2,undefined8 param_3,
 *                           undefined8 param_4,undefined8 param_5)
 * Conditional dispatch: if param_1 is non-zero it forwards the trailing three
 * arguments (param_3, param_4, param_5) to the out-of-slice helper
 * sk_x_004a3714; otherwise it does nothing.
 * Confidence: high
 * Notes: param_1 is the guard (likely a valid/ready flag); param_2 is read but
 *       unused by the call. */
static void sk_x_004a36fc(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                          uint64_t param_4, uint64_t param_5)
{
    if (param_1 != 0) {
        sk_x_004a3714(param_3, param_4, param_5);
        return;
    }
    return;
}
