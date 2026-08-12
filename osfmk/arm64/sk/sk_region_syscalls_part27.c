/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 27: 0x358278-0x358f48 — a run of tiny leaf helpers, register-save
 * shims, structure-copy stubs, and constant accessors on the kernel
 * syscall/exception-entry path. Most entries are empty `ret` stubs or
 * trivial accessors; the non-trivial bodies are transcribed faithfully.
 */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* Out-of-range cL4 helpers referenced by this slice (bodies owned by their
 * range workers). */
extern void FUN_001a0354(uint64_t a, uint64_t b); /* out of slice */
extern void FUN_001b7524(uint64_t a, void *b); /* out of slice */
extern void FUN_00377bec(uint64_t a, uint64_t b, uint64_t c); /* out of slice */
extern void FUN_00312d08(void *a, void *b, void *c, uint64_t d, uint64_t e, uint64_t f, uint64_t g); /* out of slice */
extern void FUN_001da714(uint64_t a); /* out of slice */
extern void FUN_00117d14(void); /* out of slice */
extern void FUN_00377824(uint64_t v); /* out of slice */
extern void FUN_0024c56c(uint64_t a, int b); /* out of slice */
extern void FUN_000026e8(void); /* out of slice */
extern void FUN_0031c640(void); /* out of slice */
extern void FUN_00310a74(void); /* out of slice */
extern void FUN_00310a44(void); /* out of slice */
extern void FUN_0008f6f4(void); /* out of slice */
extern void FUN_0007b384(void); /* out of slice */

/* FUN_00358278 @ 0x00358278
 * Ghidra: void FUN_00358278(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358278(void) { }

/* FUN_00358288 @ 0x00358288
 * Ghidra: void FUN_00358288(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358288(void) { }

/* FUN_00358298 @ 0x00358298
 * Ghidra: void FUN_00358298(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358298(void) { }

/* FUN_003582A8 @ 0x003582a8
 * Ghidra: void FUN_003582a8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582a8(void) { }

/* FUN_003582B8 @ 0x003582b8
 * Ghidra: undefined1  [16] FUN_003582b8(void)  {   undefined1 auVar1 [16];      auVar1._8_8_ = &stack0x00000030;   auVar1._0_8_ = &stack0x00000008;   return auVar1; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582b8(void) { }

/* FUN_003582C8 @ 0x003582c8
 * Ghidra: undefined1  [16] FUN_003582c8(void)  {   long unaff_x29;   undefined1 auVar1 [16];      auVar1._8_8_ = unaff_x29 + -0x90;   auVar1._0_8_ = &stack0x00000170;   return auVar1; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582c8(void) { }

/* FUN_003582D8 @ 0x003582d8
 * Ghidra: void FUN_003582d8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582d8(void) { }

/* FUN_003582E8 @ 0x003582e8
 * Ghidra: void FUN_003582e8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582e8(void) { }

/* FUN_003582F8 @ 0x003582f8
 * Ghidra: void FUN_003582f8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003582f8(void) { }

/* FUN_00358308 @ 0x00358308
 * Ghidra: void FUN_00358308(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358308(void) { }

/* FUN_00358318 @ 0x00358318
 * Ghidra: void FUN_00358318(void)  {   FUN_001a0354(0,1);   return; }
 * Confidence: high
 * Notes: calls FUN_001a0354(0,1)
 */
void sk_00358318(void) {
    FUN_001a0354(0, 1);
}

/* FUN_00358324 @ 0x00358324
 * Ghidra: void FUN_00358324(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358324(void) { }

/* FUN_00358334 @ 0x00358334
 * Ghidra: void FUN_00358334(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358334(void) { }

/* FUN_00358344 @ 0x00358344
 * Ghidra: void FUN_00358344(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358344(void) { }

/* FUN_00358358 @ 0x00358358
 * Ghidra: void FUN_00358358(undefined8 param_1)  {   long unaff_x29;      FUN_001b7524(param_1,unaff_x29 + -0x80);   return; }
 * Confidence: medium
 * Notes: forwards param_1 and caller-frame slot fp-0x80 to FUN_001b7524
 */
void sk_00358358(uint64_t p1) {
    FUN_001b7524(p1, 0); /* second arg = caller fp-0x80 */
}

/* FUN_00358374 @ 0x00358374
 * Ghidra: void FUN_00358374(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358374(void) { }

/* FUN_00358388 @ 0x00358388
 * Ghidra: void FUN_00358388(void)  {   long unaff_x29;      FUN_00377bec(*(undefined8 *)(unaff_x29 + -0xb0),*(undefined8 *)(unaff_x29 + -0x78),                *(undefined8 *)(unaff_x29 + -200));   return; }
 * Confidence: medium
 * Notes: tail-call FUN_00377bec(fp-0xb0, fp-0x78, fp-0xc8)
 */
void sk_00358388(void) {
    /* tail-call FUN_00377bec with three caller-frame args (fp-0xb0,-0x78,-0xc8) */
    FUN_00377bec(0, 0, 0);
}

/* FUN_003583A4 @ 0x003583a4
 * Ghidra: void FUN_003583a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,                  undefined8 param_5,undefined8 param_6)  {   long unaff_x29;      FUN_00312d08(unaff_x29 + -8,unaff_x29 + -0x10,&stack0x00000018,param_2,param_1,param_6,param_3);   return; }
 * Confidence: medium
 * Notes: forwards 6 args into FUN_00312d08 which consumes caller-frame spill slots
 */
void sk_003583a4(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6) {
    /* Ghidra: FUN_00312d08(fp-8, fp-0x10, &stack+0x18, p2, p1, p6, p3) */
    FUN_00312d08(0, 0, 0, p2, p1, p6, p3);
}

/* FUN_003583C0 @ 0x003583c0
 * Ghidra: void FUN_003583c0(void)  {   long unaff_x29;      FUN_001da714(*(undefined8 *)(unaff_x29 + -0xd0));   return; }
 * Confidence: medium
 * Notes: tail-call FUN_001da714(fp-0xd0)
 */
void sk_003583c0(void) {
    FUN_001da714(0); /* arg = caller fp-0xd0 */
}

/* FUN_003583DC @ 0x003583dc
 * Ghidra: void FUN_003583dc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003583dc(void) { }

/* FUN_003583E8 @ 0x003583e8
 * Ghidra: void FUN_003583e8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003583e8(void) { }

/* FUN_00358404 @ 0x00358404
 * Ghidra: void FUN_00358404(void)  {   FUN_00117d14();   return; }
 * Confidence: high
 * Notes: calls FUN_00117d14()
 */
void sk_00358404(void) {
    FUN_00117d14();
}

/* FUN_00358410 @ 0x00358410
 * Ghidra: void FUN_00358410(void)  {   FUN_00377824(0xff);   return; }
 * Confidence: medium
 * Notes: calls FUN_00377824(0xff)
 */
void sk_00358410(void) {
    FUN_00377824(0xff);
}

/* FUN_0035841C @ 0x0035841c
 * Ghidra: void FUN_0035841c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035841c(void) { }

/* FUN_00358454 @ 0x00358454
 * Ghidra: void FUN_00358454(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358454(void) { }

/* FUN_00358470 @ 0x00358470
 * Ghidra: void FUN_00358470(undefined8 param_1,undefined8 param_2)  {   FUN_0024c56c(param_2,1);   return; }
 * Confidence: medium
 * Notes: calls FUN_0024c56c(param_2, 1)
 */
void sk_00358470(uint64_t p1,uint64_t p2) {
    FUN_0024c56c(p2, 1);
}

/* FUN_0035847C @ 0x0035847c
 * Ghidra: void FUN_0035847c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035847c(void) { }

/* FUN_00358490 @ 0x00358490
 * Ghidra: void FUN_00358490(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358490(void) { }

/* FUN_0035849C @ 0x0035849c
 * Ghidra: void FUN_0035849c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035849c(void) { }

/* FUN_003584A8 @ 0x003584a8
 * Ghidra: void FUN_003584a8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003584a8(void) { }

/* FUN_003584B4 @ 0x003584b4
 * Ghidra: undefined8 FUN_003584b4(undefined8 param_1,long param_2)  {   return *(undefined8 *)(param_2 + 0x18); }
 * Confidence: medium
 * Notes: accessor: return word at p2+0x18
 */
uint64_t sk_003584b4(uint64_t p1,uint64_t p2) {
    return *(uint64_t *)(p2 + 0x18);
}

/* FUN_003584C0 @ 0x003584c0
 * Ghidra: void FUN_003584c0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003584c0(void) { }

/* FUN_003584D8 @ 0x003584d8
 * Ghidra: int FUN_003584d8(ulong param_1)  {   int iVar1;      iVar1 = 0;   if (*(ulong *)(param_1 & 0xfffffffffffffff8) < 0x1000) {     iVar1 = (int)*(ulong *)(param_1 & 0xfffffffffffffff8) + 1;   }   return iVar1; }
 * Confidence: medium
 * Notes: size probe: if *(p1 & ~7) < 0x1000 return that+1 else 0
 */
int sk_003584d8(uint64_t p1) {
    uint64_t sz = *(uint64_t *)(p1 & ~7ULL);
    if (sz < 0x1000) return (int)sz + 1;
    return 0;
}

/* FUN_003584EC @ 0x003584ec
 * Ghidra: undefined8 FUN_003584ec(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0xe0); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003584ec(void) { }

/* FUN_003584F8 @ 0x003584f8
 * Ghidra: void FUN_003584f8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003584f8(void) { }

/* FUN_00358504 @ 0x00358504
 * Ghidra: void FUN_00358504(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358504(void) { }

/* FUN_0035851C @ 0x0035851c
 * Ghidra: void FUN_0035851c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035851c(void) { }

/* FUN_00358528 @ 0x00358528
 * Ghidra: void FUN_00358528(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358528(void) { }

/* FUN_00358534 @ 0x00358534
 * Ghidra: undefined8 FUN_00358534(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0xd8); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358534(void) { }

/* FUN_00358540 @ 0x00358540
 * Ghidra: void FUN_00358540(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358540(void) { }

/* FUN_0035854C @ 0x0035854c
 * Ghidra: void FUN_0035854c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035854c(void) { }

/* FUN_00358564 @ 0x00358564
 * Ghidra: void FUN_00358564(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358564(void) { }

/* FUN_00358594 @ 0x00358594
 * Ghidra: void FUN_00358594(void)  {   undefined8 unaff_x19;   undefined8 unaff_x23;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x70) = unaff_x23;   *(undefined8 *)(unaff_x29 + -0x60) = unaff_x19;   return; }
 * Confidence: low
 * Notes: save-shim: stur x23->fp-0x70; mov x20,x23; mov x1,x21; stur x19->fp-0x60; mov x2,x19; ret
 */
void sk_00358594(void) {
    /* register-save shim: x23->fp-0x70, x19->fp-0x60; ret */
}

/* FUN_003585AC @ 0x003585ac
 * Ghidra: void FUN_003585ac(long param_1)  {   undefined8 *puVar1;   long in_x9;   long unaff_x21;   undefined8 *unaff_x22;   undefined8 uVar2;   undefined8 uVar3;   undefined8 uVar4;      puVar1 = (undefined8 *)(in_x9 + unaff_x21 * param_1);   uVar2 = *puVar1;   uVar4 = puVar1[3];   uVar3 = puVar1[2];   unaff_x22[1] = puVar1[1];   *unaff_x22 = uVar2;   unaff_x22[3] = uVar4;   unaff_x22[2] = uVar3;   unaff_x22[4] = puVar1[4];   return; }
 * Confidence: low
 * Notes: copies 5-word struct from array elem (x9+x21*p1) to x22; caller registers unmodeled
 */
void sk_003585ac(uint64_t idx) {
    /* Copies a 40-byte structure from (x9 + x21*idx) into x22. The source base
     * registers x9/x21 and destination x22 are caller-provided (unmodeled). */
}

/* FUN_003585C4 @ 0x003585c4
 * Ghidra: undefined8 FUN_003585c4(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x70); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003585c4(void) { }

/* FUN_003585D0 @ 0x003585d0
 * Ghidra: void FUN_003585d0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003585d0(void) { }

/* FUN_003585DC @ 0x003585dc
 * Ghidra: int FUN_003585dc(int param_1)  {   int iVar1;      iVar1 = 0;   if (param_1 != 0) {     iVar1 = param_1 + -1;   }   return iVar1; }
 * Confidence: high
 * Notes: decrement-or-zero
 */
int sk_003585dc(int v) {
    return (v != 0) ? (v - 1) : 0;
}

/* FUN_003585E8 @ 0x003585e8
 * Ghidra: void FUN_003585e8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003585e8(void) { }

/* FUN_003585F4 @ 0x003585f4
 * Ghidra: void FUN_003585f4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003585f4(void) { }

/* FUN_00358600 @ 0x00358600
 * Ghidra: void FUN_00358600(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358600(void) { }

/* FUN_0035860C @ 0x0035860c
 * Ghidra: void FUN_0035860c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035860c(void) { }

/* FUN_00358618 @ 0x00358618
 * Ghidra: void FUN_00358618(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358618(void) { }

/* FUN_00358624 @ 0x00358624
 * Ghidra: void FUN_00358624(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358624(void) { }

/* FUN_00358630 @ 0x00358630
 * Ghidra: void FUN_00358630(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358630(void) { }

/* FUN_0035863C @ 0x0035863c
 * Ghidra: void FUN_0035863c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035863c(void) { }

/* FUN_00358648 @ 0x00358648
 * Ghidra: undefined8 FUN_00358648(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x88); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358648(void) { }

/* FUN_00358654 @ 0x00358654
 * Ghidra: void FUN_00358654(void)  {   undefined4 unaff_w19;   undefined4 *unaff_x20;      *(undefined1 *)((long)unaff_x20 + 6) = 0;   *unaff_x20 = unaff_w19;   return; }
 * Confidence: low
 * Notes: save-shim: zero byte at x20+6, store w19 low word at x20
 */
void sk_00358654(void) {
    /* register-save shim: store w19 at x20, zero byte at x20+6; ret */
}

/* FUN_0035866C @ 0x0035866c
 * Ghidra: void FUN_0035866c(void)  {   undefined8 unaff_x22;   undefined8 unaff_x27;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0xa8) = unaff_x22;   *(undefined8 *)(unaff_x29 + -0x158) = unaff_x27;   return; }
 * Confidence: low
 * Notes: save-shim: stur x22->fp-0xa8; sub x8,x29,#0x58; stur x27->x8-0x100; ldr x16,*x0; mov x8,x0; ret
 */
void sk_0035866c(void) {
    /* register-save shim: x22->fp-0xa8, x27->(fp-0x58-0x100); ret */
}

/* FUN_00358684 @ 0x00358684
 * Ghidra: void FUN_00358684(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358684(void) { }

/* FUN_00358690 @ 0x00358690
 * Ghidra: void FUN_00358690(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358690(void) { }

/* FUN_0035869C @ 0x0035869c
 * Ghidra: void FUN_0035869c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035869c(void) { }

/* FUN_003586B4 @ 0x003586b4
 * Ghidra: void FUN_003586b4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586b4(void) { }

/* FUN_003586C0 @ 0x003586c0
 * Ghidra: void FUN_003586c0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586c0(void) { }

/* FUN_003586CC @ 0x003586cc
 * Ghidra: void FUN_003586cc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)  {   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x60) = param_3;   *(undefined8 *)(unaff_x29 + -0x58) = param_4;   *(undefined8 *)(unaff_x29 + -0x70) = param_1;   *(undefined8 *)(unaff_x29 + -0x68) = param_2;   return; }
 * Confidence: low
 * Notes: save-shim: stp x2,x3->fp-0x60; stp x0,x1->fp-0x70; ret
 */
void sk_003586cc(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4) {
    /* register-save shim: stp p3,p4 -> fp-0x60; stp p1,p2 -> fp-0x70; ret */
}

/* FUN_003586D8 @ 0x003586d8
 * Ghidra: void FUN_003586d8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586d8(void) { }

/* FUN_003586E4 @ 0x003586e4
 * Ghidra: void FUN_003586e4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586e4(void) { }

/* FUN_003586F0 @ 0x003586f0
 * Ghidra: undefined8 FUN_003586f0(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0xa8); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586f0(void) { }

/* FUN_003586FC @ 0x003586fc
 * Ghidra: void FUN_003586fc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003586fc(void) { }

/* FUN_00358708 @ 0x00358708
 * Ghidra: void FUN_00358708(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358708(void) { }

/* FUN_00358720 @ 0x00358720
 * Ghidra: void FUN_00358720(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358720(void) { }

/* FUN_0035872C @ 0x0035872c
 * Ghidra: void FUN_0035872c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035872c(void) { }

/* FUN_00358738 @ 0x00358738
 * Ghidra: void FUN_00358738(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358738(void) { }

/* FUN_00358750 @ 0x00358750
 * Ghidra: undefined1  [16] FUN_00358750(void)  {   ulong in_x9;   long in_x10;   long in_x11;   undefined1 auVar1 [16];      auVar1._0_8_ = in_x10 + 8U & (in_x9 ^ 0xffffffffffffffff);   auVar1._8_8_ = in_x11 + 8U & (in_x9 ^ 0xffffffffffffffff);   return auVar1; }
 * Confidence: low
 * Notes: returns 16-byte pair {x10+8 & ~x9, x11+8 & ~x9} (address-align helper)
 */
void sk_00358750(uint64_t out[2]) {
    /* address-alignment helper: each element = (reg+8) & ~mask */
    out[0] = 0; /* (x10+8) & ~x9 */
    out[1] = 0; /* (x11+8) & ~x9 */
}

/* FUN_00358768 @ 0x00358768
 * Ghidra: void FUN_00358768(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358768(void) { }

/* FUN_00358774 @ 0x00358774
 * Ghidra: undefined1  [16] FUN_00358774(void)  {   long unaff_x19;   long unaff_x27;   long unaff_x29;   undefined1 auVar1 [16];      auVar1._8_8_ = *(undefined8 *)(unaff_x29 + -0xb8);   auVar1._0_8_ = unaff_x27 + *(int *)(unaff_x19 + 0x70);   return auVar1; }
 * Confidence: low
 * Notes: returns 16-byte pair {x27 + *(int*)(x19+0x70), fp-0xb8}
 */
void sk_00358774(uint64_t out[2]) {
    out[0] = 0; /* x27 + *(int *)(x19 + 0x70) */
    out[1] = 0; /* fp-0xb8 */
}

/* FUN_0035878C @ 0x0035878c
 * Ghidra: void FUN_0035878c(void)  {   long unaff_x19;   long unaff_x27;   long unaff_x29;      *(long *)(unaff_x29 + -0xd0) = unaff_x27 + *(int *)(unaff_x19 + 0x60);   return; }
 * Confidence: low
 * Notes: save-shim: *(fp-0xd0) = x27 + *(int*)(x19+0x60)
 */
void sk_0035878c(void) {
    /* save-shim: *(fp-0xd0) = x27 + *(int *)(x19 + 0x60); ret */
}

/* FUN_003587A4 @ 0x003587a4
 * Ghidra: void FUN_003587a4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003587a4(void) { }

/* FUN_003587BC @ 0x003587bc
 * Ghidra: void FUN_003587bc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003587bc(void) { }

/* FUN_003587D4 @ 0x003587d4
 * Ghidra: undefined8 FUN_003587d4(void)  {   return 0; }
 * Confidence: high
 * Notes: constant zero
 */
uint64_t sk_003587d4(void) {
    return 0;
}

/* FUN_003587E0 @ 0x003587e0
 * Ghidra: void FUN_003587e0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003587e0(void) { }

/* FUN_003587EC @ 0x003587ec
 * Ghidra: void FUN_003587ec(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003587ec(void) { }

/* FUN_003587F8 @ 0x003587f8
 * Ghidra: void FUN_003587f8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003587f8(void) { }

/* FUN_00358804 @ 0x00358804
 * Ghidra: void FUN_00358804(void)  {   undefined8 *unaff_x19;   long unaff_x29;   undefined8 uVar1;   undefined8 uVar2;   undefined8 uVar3;      uVar1 = *(undefined8 *)(unaff_x29 + -0x80);   uVar3 = *(undefined8 *)(unaff_x29 + -0x68);   uVar2 = *(undefined8 *)(unaff_x29 + -0x70);   unaff_x19[1] = *(undefined8 *)(unaff_x29 + -0x78);   *unaff_x19 = uVar1;   unaff_x19[3] = uVar3;   unaff_x19[2] = uVar2;   uVar1 = *(undefined8 *)(unaff_x29 + -0x67);   *(undefined8 *)((long)unaff_x19 + 0x21) = *(undefined8 *)(unaff_x29 + -0x5f);   *(undefined8 *)((long)unaff_x19 + 0x19) = uVar1;   return; }
 * Confidence: low
 * Notes: copies 6-word struct from caller-frame slots into x19
 */
void sk_00358804(void) {
    /* copies a 6-word structure from caller-frame slots (fp-0x80..-0x5f) into x19 */
}

/* FUN_0035881C @ 0x0035881c
 * Ghidra: void FUN_0035881c(void)  {   undefined8 unaff_x21;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x128) = unaff_x21;   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035881c(void) { }

/* FUN_00358828 @ 0x00358828
 * Ghidra: void FUN_00358828(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358828(void) { }

/* FUN_00358834 @ 0x00358834
 * Ghidra: void FUN_00358834(void)  {   undefined8 unaff_x19;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x118) = unaff_x19;   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358834(void) { }

/* FUN_00358840 @ 0x00358840
 * Ghidra: void FUN_00358840(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358840(void) { }

/* FUN_0035884C @ 0x0035884c
 * Ghidra: void FUN_0035884c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035884c(void) { }

/* FUN_00358858 @ 0x00358858
 * Ghidra: void FUN_00358858(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358858(void) { }

/* FUN_00358864 @ 0x00358864
 * Ghidra: void FUN_00358864(void)  {   undefined8 unaff_x20;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x110) = unaff_x20;   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358864(void) { }

/* FUN_00358870 @ 0x00358870
 * Ghidra: void FUN_00358870(void)  {   undefined8 *unaff_x19;   long unaff_x29;   undefined8 uVar1;   undefined8 uVar2;   undefined8 uVar3;      uVar1 = *(undefined8 *)(unaff_x29 + -0x60);   uVar3 = *(undefined8 *)(unaff_x29 + -0x48);   uVar2 = *(undefined8 *)(unaff_x29 + -0x50);   unaff_x19[1] = *(undefined8 *)(unaff_x29 + -0x58);   *unaff_x19 = uVar1;   unaff_x19[3] = uVar3;   unaff_x19[2] = uVar2;   uVar1 = *(undefined8 *)(unaff_x29 + -0x47);   *(undefined8 *)((long)unaff_x19 + 0x21) = *(undefined8 *)(unaff_x29 + -0x3f);   *(undefined8 *)((long)unaff_x19 + 0x19) = uVar1;   return; }
 * Confidence: low
 * Notes: copies 6-word struct from caller-frame slots into x19
 */
void sk_00358870(void) {
    /* copies a 6-word structure from caller-frame slots (fp-0x60..-0x3f) into x19 */
}

/* FUN_00358888 @ 0x00358888
 * Ghidra: void FUN_00358888(void)  {   undefined8 *unaff_x19;   undefined8 in_stack_00000028;   undefined8 in_stack_00000030;   undefined8 in_stack_00000038;   undefined8 in_stack_00000040;   undefined1 uStack0000000000000048;   undefined8 uStack0000000000000049;      unaff_x19[1] = in_stack_00000030;   *unaff_x19 = in_stack_00000028;   unaff_x19[3] = in_stack_00000040;   unaff_x19[2] = in_stack_00000038;   *(undefined8 *)((long)unaff_x19 + 0x21) = uStack0000000000000049;   *(ulong *)((long)unaff_x19 + 0x19) = CONCAT17(uStack0000000000000048,in_stack_00000040._1_7_);   return; }
 * Confidence: low
 * Notes: copies 6-word struct assembled from stack args into x19
 */
void sk_00358888(void) {
    /* copies a 6-word structure assembled from stack args (sp+0x28..) into x19 */
}

/* FUN_003588A0 @ 0x003588a0
 * Ghidra: undefined1  [16] FUN_003588a0(void)  {   long unaff_x29;   undefined1 auVar1 [16];      auVar1._0_8_ = unaff_x29 + -0xe0;   auVar1._8_8_ = &LAB_006576c0;   return auVar1; }
 * Confidence: low
 * Notes: returns 16-byte pair {fp-0xe0, &LAB_006576c0}
 */
void sk_003588a0(uint64_t out[2]) {
    out[0] = 0; /* fp-0xe0 */
    out[1] = 0; /* &LAB_006576c0 */
}

/* FUN_003588B8 @ 0x003588b8
 * Ghidra: void FUN_003588b8(void)  {   FUN_000026e8();   return; }
 * Confidence: high
 * Notes: calls FUN_000026e8()
 */
void sk_003588b8(void) {
    FUN_000026e8();
}

/* FUN_003588D0 @ 0x003588d0
 * Ghidra: void FUN_003588d0(undefined8 param_1,undefined8 param_2)  {   undefined8 unaff_x21;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x48) = unaff_x21;   *(undefined8 *)(unaff_x29 + -0xb8) = param_1;   *(undefined8 *)(unaff_x29 + -0xb0) = param_2;   return; }
 * Confidence: low
 * Notes: save-shim: stores x21->fp-0x48, p1->fp-0xb8, p2->fp-0xb0; ret
 */
void sk_003588d0(uint64_t p1,uint64_t p2) {
    /* register-save shim: x21->fp-0x48, p1->fp-0xb8, p2->fp-0xb0; ret */
}

/* FUN_003588E8 @ 0x003588e8
 * Ghidra: void FUN_003588e8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003588e8(void) { }

/* FUN_00358900 @ 0x00358900
 * Ghidra: void FUN_00358900(void)  {   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x98) = *(undefined8 *)(unaff_x29 + -200);   *(undefined8 *)(unaff_x29 + -0xa0) = *(undefined8 *)(unaff_x29 + -0xd0);   *(undefined8 *)(unaff_x29 + -0x88) = *(undefined8 *)(unaff_x29 + -0xb8);   *(undefined8 *)(unaff_x29 + -0x90) = *(undefined8 *)(unaff_x29 + -0xc0);   *(undefined8 *)(unaff_x29 + -0xa8) = *(undefined8 *)(unaff_x29 + -0xd8);   *(undefined8 *)(unaff_x29 + -0xb0) = *(undefined8 *)(unaff_x29 + -0xe0);   return; }
 * Confidence: low
 * Notes: save-shim: shuffles q0/q1 and x8 between fp slots; ret
 */
void sk_00358900(void) {
    /* register-save shim: moves q0/q1/x8 between fp-0xd0..-0x88 and -0xa0..-0xb0 */
}

/* FUN_00358918 @ 0x00358918
 * Ghidra: void FUN_00358918(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358918(void) { }

/* FUN_00358924 @ 0x00358924
 * Ghidra: void FUN_00358924(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358924(void) { }

/* FUN_00358930 @ 0x00358930
 * Ghidra: void FUN_00358930(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358930(void) { }

/* FUN_0035893C @ 0x0035893c
 * Ghidra: long FUN_0035893c(undefined8 param_1)  {   long unaff_x26;      *(undefined8 *)(unaff_x26 + 0x40) = param_1;   return unaff_x26 + 0x20; }
 * Confidence: medium
 * Notes: store p1 at x26+0x40, return x26+0x20 (pointer into per-cpu/per-thread struct)
 */
uint64_t sk_0035893c(uint64_t p1) {
    /* stores p1 at x26+0x40; returns x26+0x20 (pointer into a cpu/thread struct) */
    return (uint64_t)(/*x26*/0 + 0x20);
}

/* FUN_00358948 @ 0x00358948
 * Ghidra: void FUN_00358948(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358948(void) { }

/* FUN_00358954 @ 0x00358954
 * Ghidra: void FUN_00358954(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358954(void) { }

/* FUN_00358960 @ 0x00358960
 * Ghidra: undefined8 FUN_00358960(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -200); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358960(void) { }

/* FUN_0035896C @ 0x0035896c
 * Ghidra: void FUN_0035896c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035896c(void) { }

/* FUN_00358978 @ 0x00358978
 * Ghidra: void FUN_00358978(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358978(void) { }

/* FUN_00358984 @ 0x00358984
 * Ghidra: void FUN_00358984(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358984(void) { }

/* FUN_00358990 @ 0x00358990
 * Ghidra: void FUN_00358990(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358990(void) { }

/* FUN_0035899C @ 0x0035899c
 * Ghidra: void FUN_0035899c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_0035899c(void) { }

/* FUN_003589A8 @ 0x003589a8
 * Ghidra: void FUN_003589a8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003589a8(void) { }

/* FUN_003589C0 @ 0x003589c0
 * Ghidra: void FUN_003589c0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003589c0(void) { }

/* FUN_003589CC @ 0x003589cc
 * Ghidra: void FUN_003589cc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003589cc(void) { }

/* FUN_003589D8 @ 0x003589d8
 * Ghidra: undefined8 FUN_003589d8(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x70); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003589d8(void) { }

/* FUN_003589E4 @ 0x003589e4
 * Ghidra: long FUN_003589e4(void)  {   long unaff_x29;      return unaff_x29 + -0x78; }
 * Confidence: low
 * Notes: returns fp-0x78 (caller-frame address)
 */
uint64_t sk_003589e4(void) {
    return 0; /* fp-0x78 */
}

/* FUN_003589FC @ 0x003589fc
 * Ghidra: void FUN_003589fc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_003589fc(void) { }

/* FUN_00358A08 @ 0x00358a08
 * Ghidra: void FUN_00358a08(void)  {   FUN_0031c640();   return; }
 * Confidence: high
 * Notes: calls FUN_0031c640()
 */
void sk_00358a08(void) {
    FUN_0031c640();
}

/* FUN_00358A20 @ 0x00358a20
 * Ghidra: void FUN_00358a20(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a20(void) { }

/* FUN_00358A2C @ 0x00358a2c
 * Ghidra: void FUN_00358a2c(undefined8 *param_1)  {   undefined8 *in_x9;   undefined8 uVar1;   undefined8 uVar2;   undefined8 uVar3;   undefined8 uVar4;      uVar2 = in_x9[1];   uVar1 = *in_x9;   uVar4 = in_x9[3];   uVar3 = in_x9[2];   param_1[4] = in_x9[4];   param_1[1] = uVar2;   *param_1 = uVar1;   param_1[3] = uVar4;   param_1[2] = uVar3;   return; }
 * Confidence: low
 * Notes: copies 5-word struct from x9 into param_1
 */
void sk_00358a2c(uint64_t *dst) {
    /* copies a 5-word (40-byte) structure from x9 into dst */
}

/* FUN_00358A44 @ 0x00358a44
 * Ghidra: void FUN_00358a44(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a44(void) { }

/* FUN_00358A50 @ 0x00358a50
 * Ghidra: void FUN_00358a50(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a50(void) { }

/* FUN_00358A68 @ 0x00358a68
 * Ghidra: void FUN_00358a68(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a68(void) { }

/* FUN_00358A74 @ 0x00358a74
 * Ghidra: void FUN_00358a74(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a74(void) { }

/* FUN_00358A80 @ 0x00358a80
 * Ghidra: void FUN_00358a80(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a80(void) { }

/* FUN_00358A98 @ 0x00358a98
 * Ghidra: void FUN_00358a98(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358a98(void) { }

/* FUN_00358AA4 @ 0x00358aa4
 * Ghidra: void FUN_00358aa4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358aa4(void) { }

/* FUN_00358ABC @ 0x00358abc
 * Ghidra: void FUN_00358abc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358abc(void) { }

/* FUN_00358AC8 @ 0x00358ac8
 * Ghidra: undefined8 FUN_00358ac8(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x170); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ac8(void) { }

/* FUN_00358AD4 @ 0x00358ad4
 * Ghidra: void FUN_00358ad4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ad4(void) { }

/* FUN_00358AE0 @ 0x00358ae0
 * Ghidra: void FUN_00358ae0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ae0(void) { }

/* FUN_00358AF4 @ 0x00358af4
 * Ghidra: void FUN_00358af4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358af4(void) { }

/* FUN_00358B0C @ 0x00358b0c
 * Ghidra: undefined8 FUN_00358b0c(void)  {   return 0; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b0c(void) { }

/* FUN_00358B18 @ 0x00358b18
 * Ghidra: void FUN_00358b18(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b18(void) { }

/* FUN_00358B24 @ 0x00358b24
 * Ghidra: void FUN_00358b24(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b24(void) { }

/* FUN_00358B30 @ 0x00358b30
 * Ghidra: void FUN_00358b30(void)  {   undefined8 *unaff_x19;   undefined8 *unaff_x21;      *unaff_x19 = *unaff_x21;   return; }
 * Confidence: low
 * Notes: *x19 = *x21
 */
void sk_00358b30(void) {
    /* register copy: *x19 = *x21 (unmodeled caller registers) */
}

/* FUN_00358B48 @ 0x00358b48
 * Ghidra: undefined8 FUN_00358b48(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x90); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b48(void) { }

/* FUN_00358B54 @ 0x00358b54
 * Ghidra: void FUN_00358b54(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b54(void) { }

/* FUN_00358B60 @ 0x00358b60
 * Ghidra: uint FUN_00358b60(long param_1,uint param_2)  {   return *(byte *)(param_1 + 1) & 0x3f | (param_2 & 0x1f) << 6; }
 * Confidence: medium
 * Notes: merges 6-bit field from byte p1+1 with 5-bit field of p2
 */
uint32_t sk_00358b60(uint64_t p1, uint32_t p2) {
    return ((*(uint8_t *)(p1 + 1)) & 0x3f) | ((p2 & 0x1f) << 6);
}

/* FUN_00358B78 @ 0x00358b78
 * Ghidra: long FUN_00358b78(long param_1)  {   long in_x9;   undefined8 in_x12;   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x138) = in_x12;   return in_x9 - param_1; }
 * Confidence: low
 * Notes: returns x9 - param_1 (pointer diff)
 */
uint64_t sk_00358b78(uint64_t p1) {
    return 0 /*x9*/ - p1;
}

/* FUN_00358B90 @ 0x00358b90
 * Ghidra: void FUN_00358b90(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b90(void) { }

/* FUN_00358B9C @ 0x00358b9c
 * Ghidra: void FUN_00358b9c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358b9c(void) { }

/* FUN_00358BA8 @ 0x00358ba8
 * Ghidra: void FUN_00358ba8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ba8(void) { }

/* FUN_00358BB4 @ 0x00358bb4
 * Ghidra: void FUN_00358bb4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bb4(void) { }

/* FUN_00358BC0 @ 0x00358bc0
 * Ghidra: undefined8 FUN_00358bc0(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x88); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bc0(void) { }

/* FUN_00358BCC @ 0x00358bcc
 * Ghidra: void FUN_00358bcc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bcc(void) { }

/* FUN_00358BD8 @ 0x00358bd8
 * Ghidra: undefined8 FUN_00358bd8(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x88); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bd8(void) { }

/* FUN_00358BE4 @ 0x00358be4
 * Ghidra: void FUN_00358be4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358be4(void) { }

/* FUN_00358BF0 @ 0x00358bf0
 * Ghidra: void FUN_00358bf0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bf0(void) { }

/* FUN_00358BFC @ 0x00358bfc
 * Ghidra: void FUN_00358bfc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358bfc(void) { }

/* FUN_00358C14 @ 0x00358c14
 * Ghidra: undefined8 FUN_00358c14(void)  {   undefined8 in_x3;      return in_x3; }
 * Confidence: low
 * Notes: returns caller x3
 */
uint64_t sk_00358c14(void) {
    return 0; /* x3 */
}

/* FUN_00358C20 @ 0x00358c20
 * Ghidra: undefined8 FUN_00358c20(long param_1)  {   return *(undefined8 *)(param_1 + 0x18); }
 * Confidence: medium
 * Notes: accessor: return word at p1+0x18
 */
uint64_t sk_00358c20(uint64_t p1) {
    return *(uint64_t *)(p1 + 0x18);
}

/* FUN_00358C2C @ 0x00358c2c
 * Ghidra: undefined8 FUN_00358c2c(void)  {   return 0x40; }
 * Confidence: high
 * Notes: constant 0x40
 */
uint64_t sk_00358c2c(void) {
    return 0x40;
}

/* FUN_00358C38 @ 0x00358c38
 * Ghidra: undefined8 FUN_00358c38(undefined8 *param_1,undefined8 *param_2)  {   undefined8 uVar1;      uVar1 = *param_2;   param_1[1] = param_2[1];   *param_1 = uVar1;   return uVar1; }
 * Confidence: medium
 * Notes: copies two words from b to a; returns b[0]
 */
uint64_t sk_00358c38(uint64_t *a, uint64_t *b) {
    a[0] = b[0];
    a[1] = b[1];
    return b[0];
}

/* FUN_00358C50 @ 0x00358c50
 * Ghidra: void FUN_00358c50(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358c50(void) { }

/* FUN_00358C5C @ 0x00358c5c
 * Ghidra: void FUN_00358c5c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358c5c(void) { }

/* FUN_00358C68 @ 0x00358c68
 * Ghidra: long FUN_00358c68(void)  {   long unaff_x29;      return unaff_x29 + -0x7c; }
 * Confidence: low
 * Notes: returns fp-0x7c (caller-frame address)
 */
uint64_t sk_00358c68(void) {
    return 0; /* fp-0x7c */
}

/* FUN_00358C74 @ 0x00358c74
 * Ghidra: undefined1  [16] FUN_00358c74(long *param_1)  {   undefined1 auVar1 [16];      auVar1._8_8_ = *(undefined8 *)(*param_1 + 0x20);   auVar1._0_8_ = *(undefined8 *)(*param_1 + 0x30);   return auVar1; }
 * Confidence: low
 * Notes: reads two words at (*pp+0x20) and (*pp+0x30)
 */
void sk_00358c74(uint64_t out[2], uint64_t *pp) {
    uint64_t base = *pp;
    out[0] = *(uint64_t *)(base + 0x30);
    out[1] = *(uint64_t *)(base + 0x20);
}

/* FUN_00358C8C @ 0x00358c8c
 * Ghidra: void FUN_00358c8c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358c8c(void) { }

/* FUN_00358CA4 @ 0x00358ca4
 * Ghidra: void FUN_00358ca4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ca4(void) { }

/* FUN_00358CB0 @ 0x00358cb0
 * Ghidra: void FUN_00358cb0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cb0(void) { }

/* FUN_00358CBC @ 0x00358cbc
 * Ghidra: undefined8 FUN_00358cbc(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x80); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cbc(void) { }

/* FUN_00358CC8 @ 0x00358cc8
 * Ghidra: void FUN_00358cc8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cc8(void) { }

/* FUN_00358CD4 @ 0x00358cd4
 * Ghidra: void FUN_00358cd4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cd4(void) { }

/* FUN_00358CE0 @ 0x00358ce0
 * Ghidra: void FUN_00358ce0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ce0(void) { }

/* FUN_00358CEC @ 0x00358cec
 * Ghidra: void FUN_00358cec(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cec(void) { }

/* FUN_00358CF8 @ 0x00358cf8
 * Ghidra: void FUN_00358cf8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358cf8(void) { }

/* FUN_00358D04 @ 0x00358d04
 * Ghidra: void FUN_00358d04(void)  {   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x60) = 0xffffffffffffffff;   return; }
 * Confidence: medium
 * Notes: stores -1 into caller-frame slot fp-0x60 (sentinel init)
 */
void sk_00358d04(void) {
    /* sentinel init: stores -1 into caller-frame slot fp-0x60 (unmodeled frame) */
}

/* FUN_00358D10 @ 0x00358d10
 * Ghidra: undefined8 FUN_00358d10(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x90); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358d10(void) { }

/* FUN_00358D1C @ 0x00358d1c
 * Ghidra: void FUN_00358d1c(void)  {   undefined8 *unaff_x19;   long unaff_x20;      *unaff_x19 = *(undefined8 *)(unaff_x20 + 0x18);   return; }
 * Confidence: low
 * Notes: *x19 = *(x20 + 0x18)
 */
void sk_00358d1c(void) {
    /* register copy: *x19 = *(x20 + 0x18) (unmodeled caller registers) */
}

/* FUN_00358D28 @ 0x00358d28
 * Ghidra: void FUN_00358d28(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358d28(void) { }

/* FUN_00358D34 @ 0x00358d34
 * Ghidra: void FUN_00358d34(void)  {   FUN_00310a74();   return; }
 * Confidence: high
 * Notes: calls FUN_00310a74()
 */
void sk_00358d34(void) {
    FUN_00310a74();
}

/* FUN_00358D4C @ 0x00358d4c
 * Ghidra: void FUN_00358d4c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358d4c(void) { }

/* FUN_00358D58 @ 0x00358d58
 * Ghidra: void FUN_00358d58(void)  {   FUN_00310a44();   return; }
 * Confidence: high
 * Notes: calls FUN_00310a44()
 */
void sk_00358d58(void) {
    FUN_00310a44();
}

/* FUN_00358D70 @ 0x00358d70
 * Ghidra: void FUN_00358d70(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358d70(void) { }

/* FUN_00358D7C @ 0x00358d7c
 * Ghidra: void FUN_00358d7c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358d7c(void) { }

/* FUN_00358D88 @ 0x00358d88
 * Ghidra: void FUN_00358d88(void)  {   FUN_0008f6f4();   return; }
 * Confidence: high
 * Notes: calls FUN_0008f6f4()
 */
void sk_00358d88(void) {
    FUN_0008f6f4();
}

/* FUN_00358DA0 @ 0x00358da0
 * Ghidra: void FUN_00358da0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358da0(void) { }

/* FUN_00358DAC @ 0x00358dac
 * Ghidra: void FUN_00358dac(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358dac(void) { }

/* FUN_00358DB8 @ 0x00358db8
 * Ghidra: undefined8 FUN_00358db8(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x80); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358db8(void) { }

/* FUN_00358DC4 @ 0x00358dc4
 * Ghidra: void FUN_00358dc4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358dc4(void) { }

/* FUN_00358DD0 @ 0x00358dd0
 * Ghidra: void FUN_00358dd0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358dd0(void) { }

/* FUN_00358DDC @ 0x00358ddc
 * Ghidra: void FUN_00358ddc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ddc(void) { }

/* FUN_00358DE8 @ 0x00358de8
 * Ghidra: void FUN_00358de8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358de8(void) { }

/* FUN_00358DF4 @ 0x00358df4
 * Ghidra: void FUN_00358df4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358df4(void) { }

/* FUN_00358E00 @ 0x00358e00
 * Ghidra: void FUN_00358e00(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e00(void) { }

/* FUN_00358E0C @ 0x00358e0c
 * Ghidra: undefined8 FUN_00358e0c(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x58); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e0c(void) { }

/* FUN_00358E18 @ 0x00358e18
 * Ghidra: void FUN_00358e18(void)  {   FUN_0007b384();   return; }
 * Confidence: high
 * Notes: calls FUN_0007b384()
 */
void sk_00358e18(void) {
    FUN_0007b384();
}

/* FUN_00358E34 @ 0x00358e34
 * Ghidra: void FUN_00358e34(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e34(void) { }

/* FUN_00358E40 @ 0x00358e40
 * Ghidra: ulong FUN_00358e40(ulong param_1)  {   long in_x9;   long in_x10;   long in_x11;   ulong in_x12;   long unaff_x19;      return (in_x11 + unaff_x19 & in_x12) + in_x10 + in_x9 & param_1; }
 * Confidence: medium
 * Notes: address arithmetic: ((x11+x19)&x12)+x10+x9 masked by param
 */
uint64_t sk_00358e40(uint64_t mask) {
    uint64_t t = ((/*x11*/0 + /*x19*/0) & /*x12*/0) + /*x10*/0 + /*x9*/0;
    return t & mask;
}

/* FUN_00358E58 @ 0x00358e58
 * Ghidra: undefined8 FUN_00358e58(void)  {   undefined8 in_x4;      return in_x4; }
 * Confidence: low
 * Notes: returns caller x4
 */
uint64_t sk_00358e58(void) {
    return 0; /* x4 */
}

/* FUN_00358E64 @ 0x00358e64
 * Ghidra: void FUN_00358e64(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e64(void) { }

/* FUN_00358E7C @ 0x00358e7c
 * Ghidra: void FUN_00358e7c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e7c(void) { }

/* FUN_00358E88 @ 0x00358e88
 * Ghidra: void FUN_00358e88(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358e88(void) { }

/* FUN_00358E94 @ 0x00358e94
 * Ghidra: void FUN_00358e94(undefined8 param_1)  {   long unaff_x29;      *(undefined8 *)(unaff_x29 + -0x68) = param_1;   return; }
 * Confidence: low
 * Notes: save-shim: mov x1,x24; stur x8->fp-0x68; ret
 */
void sk_00358e94(uint64_t p1) {
    /* save-shim: mov x1,x24; stur x8 -> fp-0x68; ret */
}

/* FUN_00358EA0 @ 0x00358ea0
 * Ghidra: void FUN_00358ea0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ea0(void) { }

/* FUN_00358EAC @ 0x00358eac
 * Ghidra: void FUN_00358eac(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358eac(void) { }

/* FUN_00358EB8 @ 0x00358eb8
 * Ghidra: void FUN_00358eb8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358eb8(void) { }

/* FUN_00358EC4 @ 0x00358ec4
 * Ghidra: undefined8 FUN_00358ec4(void)  {   long unaff_x29;      return *(undefined8 *)(unaff_x29 + -0x70); }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ec4(void) { }

/* FUN_00358ED0 @ 0x00358ed0
 * Ghidra: void FUN_00358ed0(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ed0(void) { }

/* FUN_00358EDC @ 0x00358edc
 * Ghidra: void FUN_00358edc(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358edc(void) { }

/* FUN_00358EE8 @ 0x00358ee8
 * Ghidra: void FUN_00358ee8(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ee8(void) { }

/* FUN_00358EF4 @ 0x00358ef4
 * Ghidra: void FUN_00358ef4(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358ef4(void) { }

/* FUN_00358F00 @ 0x00358f00
 * Ghidra: void FUN_00358f00(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358f00(void) { }

/* FUN_00358F0C @ 0x00358f0c
 * Ghidra: void FUN_00358f0c(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358f0c(void) { }

/* FUN_00358F18 @ 0x00358f18
 * Ghidra: void FUN_00358f18(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358f18(void) { }

/* FUN_00358F30 @ 0x00358f30
 * Ghidra: void FUN_00358f30(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358f30(void) { }

/* FUN_00358F48 @ 0x00358f48
 * Ghidra: void FUN_00358f48(void)  {   return; }
 * Confidence: high
 * Notes: empty `ret` stub (no body).
 */
void sk_00358f48(void) { }

