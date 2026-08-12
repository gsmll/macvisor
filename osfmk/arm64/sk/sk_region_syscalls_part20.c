/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 20: 0x352450-0x3530d8 — cL4 exception-entry / syscall dispatch
 * trampoline region.  The functions here are hand-written assembly fragments
 * (register save/restore + reload trampolines) that make up the exception and
 * syscall entry machinery.  Most are entered by fall-through/branch (not call),
 * so the decompiler sees only register effects (elided in C); each function is
 * transcribed from its disassembly in the Notes comment. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* Out-of-range cL4 helper declarations (bodies reconstructed by their range
 * workers; declared extern with a one-line note each). */
extern void cL4_000a68c4(void);    /* FUN_000a68c4 @ 0xa68c4 */
extern void cL4_000a649c(void);    /* FUN_000a649c @ 0xa649c */
extern void cL4_00002534(void *a, void *b); /* FUN_00002534 @ 0x2534 */
extern void cL4_00310a74(void);    /* FUN_00310a74 @ 0x310a74 */
extern void cL4_00319628(void);    /* FUN_00319628 @ 0x319628 */
extern void cL4_003a25d4(void);    /* FUN_003a25d4 @ 0x3a25d4 */
extern void cL4_00310954(void);    /* FUN_00310954 @ 0x310954 */
extern void cL4_00027754(void);    /* FUN_00027754 @ 0x27754 */
extern void cL4_000277e8(void);    /* FUN_000277e8 @ 0x277e8 */
extern void cL4_00310a14(void);    /* FUN_00310a14 @ 0x310a14 */
extern void cL4_0036986c(void);    /* FUN_0036986c @ 0x36986c */

/* FUN_00352450 @ 0x00352450   (est. exc_tramp_2450)
 * Ghidra: void FUN_00352450(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352450: mov x2,x25 ; 00352454: mov x3,x21 ; 00352458: ret */
void exc_tramp_2450(void)
{
    (void)0;
    return;
}

/* FUN_0035245c @ 0x0035245c   (est. exc_tramp_245c)
 * Ghidra: void FUN_0035245c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035245c: mov x20,x26 ; 00352460: mov x0,x19 ; 00352464: ret */
void exc_tramp_245c(void)
{
    (void)0;
    return;
}

/* FUN_00352468 @ 0x00352468   (est. exc_restore_2468)
 * Ghidra: void FUN_00352468(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352468: ldr x9,[x8, #0x10]! ; 0035246c: mov x0,x22 ; 00352470: ret */
void exc_restore_2468(void)
{
    (void)0;
    return;
}

/* FUN_00352474 @ 0x00352474   (est. exc_restore_2474)
 * Ghidra: void FUN_00352474(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352474: mov x8,x26 ; 00352478: ldr x9,[x8, #0x10]! ; 0035247c: ret */
void exc_restore_2474(void)
{
    (void)0;
    return;
}

/* FUN_00352480 @ 0x00352480   (est. exc_tramp_2480)
 * Ghidra: void FUN_00352480(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352480: mov w2,#0x1 ; 00352484: mov x3,x22 ; 00352488: ret */
void exc_tramp_2480(void)
{
    (void)0;
    return;
}

/* FUN_0035248c @ 0x0035248c   (est. return_arg3_248c)
 * Ghidra: undefined8 FUN_0035248c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035248c: mov x20,x0 ; 00352490: mov x0,x2 ; 00352494: ret */
word_t return_arg3_248c(word_t arg0, word_t arg1, word_t arg2)
{
    return arg2;
}

/* FUN_00352498 @ 0x00352498   (est. exc_tramp_2498)
 * Ghidra: void FUN_00352498(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352498: mov x0,x20 ; 0035249c: mov x1,x28 ; 003524a0: ret */
void exc_tramp_2498(void)
{
    (void)0;
    return;
}

/* FUN_003524a4 @ 0x003524a4   (est. exc_tramp_24a4)
 * Ghidra: void FUN_003524a4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003524a4: mov x0,x20 ; 003524a8: mov x1,x25 ; 003524ac: ret */
void exc_tramp_24a4(void)
{
    (void)0;
    return;
}

/* FUN_003524b0 @ 0x003524b0   (est. exc_tramp_24b0)
 * Ghidra: void FUN_003524b0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003524b0: mov x0,x21 ; 003524b4: mov w1,#0x1 ; 003524b8: ret */
void exc_tramp_24b0(void)
{
    (void)0;
    return;
}

/* FUN_003524bc @ 0x003524bc   (est. mk128_lo_24bc)
 * Ghidra: undefined1  [16] FUN_003524bc(ulong param_1)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003524bc: mov x0,#0x0 ; 003524c0: mov x1,x8 ; 003524c4: ret */
cl4_result_t mk128_lo_24bc(word_t arg0)
{
    cl4_result_t r = { .lo = 0, .hi = arg0 };
    return r;
}

/* FUN_003524c8 @ 0x003524c8   (est. exc_tramp_24c8)
 * Ghidra: void FUN_003524c8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003524c8: mov w5,#0x2 ; 003524cc: mov w7,#0x1f ; 003524d0: ret */
void exc_tramp_24c8(void)
{
    (void)0;
    return;
}

/* FUN_003524d4 @ 0x003524d4   (est. exc_tramp_24d4)
 * Ghidra: void FUN_003524d4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003524d4: mov x1,x22 ; 003524d8: mov x2,#0x0 ; 003524dc: ret */
void exc_tramp_24d4(void)
{
    (void)0;
    return;
}

/* FUN_003524e0 @ 0x003524e0   (est. exc_restore_24e0)
 * Ghidra: void FUN_003524e0(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003524e0: ldur x19,[x8, #-0x100] ; 003524e4: mov x8,x19 ; 003524e8: ret */
void exc_restore_24e0(void)
{
    (void)0;
    return;
}

/* FUN_003524ec @ 0x003524ec   (est. exc_arg_setup_24ec)
 * Ghidra: undefined1  [16] FUN_003524ec(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003524ec: ldp x9,x8,[x29, #0x60] ; 003524f0: ldp x11,x10,[x29, #0x50] ; 003524f4: sub sp,sp,#0x40 ; 003524f8: stp x9,x8,[sp, #0x30] ; 003524fc: stp x11,x10,[sp, #0x20] ; 00352500: sub x8,x29,#0x18 ; 00352504: ldur x8,[x8, #-0x100] ; 00352508: add x0,x27,x8 ; 0035250c: sub x8,x29,#0x20 ; 00352510: ldur x8,[x8, #-0x100] ; 00352514: add x1,x27,x8 ; 00352518: ldur x8,[x29, #-0xe8] ; 0035251c: add x2,x27,x8 ; 00352520: stp x28,x24,[sp, #0x10] ; 00352524: ldur x8,[x29, #-0xe0] ; 00352528: add x3,x27,x8 ; 0035252c: ldp x8,x9,[x29, #-0xc8] ; 00352530: add x4,x26,x9 ; 00352534: add x5,x26,x8 ; 00352538: add x6,x26,x19 ; 0035253c: add x7,x26,x22 ; 00352540: ldur x8,[x29, #-0x88] ; 00352544: str x8,[sp, #0x8] ; 00352548: ldur x8,[x29, #-0xb0] ; 0035254c: str x8,[sp] ; 00352550: ret */
void exc_arg_setup_24ec(void)
{
    (void)0;
    return;
}

/* FUN_00352554 @ 0x00352554   (est. exc_frame_store_2554)
 * Ghidra: void FUN_00352554(undefined8 param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352554: sub x9,x29,#0x10 ; 00352558: stur x8,[x9, #-0x100] ; 0035255c: ret */
void exc_frame_store_2554(word_t arg0)
{
    (void)arg0;
    return;
}

/* FUN_00352560 @ 0x00352560   (est. exc_tramp_2560)
 * Ghidra: void FUN_00352560(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352560: mov x0,x28 ; 00352564: mov w1,#0x1 ; 00352568: ret */
void exc_tramp_2560(void)
{
    (void)0;
    return;
}

/* FUN_0035256c @ 0x0035256c   (est. exc_tramp_256c)
 * Ghidra: void FUN_0035256c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035256c: mov x1,x28 ; 00352570: mov x2,x25 ; 00352574: ret */
void exc_tramp_256c(void)
{
    (void)0;
    return;
}

/* FUN_00352578 @ 0x00352578   (est. exc_tramp_2578)
 * Ghidra: void FUN_00352578(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352578: mov x2,x3 ; 0035257c: mov x3,x4 ; 00352580: ret */
void exc_tramp_2578(void)
{
    (void)0;
    return;
}

/* FUN_00352584 @ 0x00352584   (est. exc_restore_word_2584)
 * Ghidra: undefined8 FUN_00352584(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352584: ldur x19,[x8, #-0x100] ; 00352588: mov x0,x19 ; 0035258c: ret */
word_t exc_restore_word_2584(word_t arg0)
{
    return *(word_t *)(arg0 - 0x100);
}

/* FUN_00352590 @ 0x00352590   (est. exc_const_0xff_2590)
 * Ghidra: undefined8 FUN_00352590(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352590: adrp x25,0x611000 ; 00352594: add x25,x25,#0xb24 ; 00352598: add x4,x25,#0x10 ; 0035259c: mov w0,#0xff ; 003525a0: ret */
word_t exc_const_0xff_2590(void)
{
    return 0xff;
}

/* FUN_003525a4 @ 0x003525a4   (est. exc_restore_25a4)
 * Ghidra: void FUN_003525a4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003525a4: ldr x8,[x22, #0x48] ; 003525a8: add x24,x24,x8 ; 003525ac: add x20,x20,x8 ; 003525b0: subs x25,x25,#0x1 ; 003525b4: ret */
void exc_restore_25a4(void)
{
    (void)0;
    return;
}

/* FUN_003525b8 @ 0x003525b8   (est. exc_tramp_25b8)
 * Ghidra: void FUN_003525b8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003525b8: sub w8,w14,#0x1 ; 003525bc: lsl w8,w8,w13 ; 003525c0: cmp w12,#0x3 ; 003525c4: csel w8,wzr,w8,hi ; 003525c8: ret */
void exc_tramp_25b8(void)
{
    (void)0;
    return;
}

/* FUN_003525cc @ 0x003525cc   (est. exc_const_0_25cc)
 * Ghidra: undefined8 FUN_003525cc(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003525cc: adrp x21,0x60e000 ; 003525d0: add x21,x21,#0x208 ; 003525d4: add x4,x21,#0x30 ; 003525d8: mov x0,#0x0 ; 003525dc: ret */
word_t exc_const_0_25cc(void)
{
    return 0;
}

/* FUN_003525f4 @ 0x003525f4   (est. exc_restore_frame_25f4)
 * Ghidra: undefined8 FUN_003525f4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003525f4: ldur x9,[x29, #-0xd8] ; 003525f8: ldr x8,[x9, #0x20]! ; 003525fc: sub x10,x29,#0x40 ; 00352600: ldur x0,[x10, #-0x100] ; 00352604: ret */
word_t exc_restore_frame_25f4(void)
{
    return 0;
}

/* FUN_00352608 @ 0x00352608   (est. exc_frame_push2_2608)
 * Ghidra: undefined1  [16] FUN_00352608(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352608: ldur x9,[x29, #-0xd8] ; 0035260c: ldr x8,[x9, #0x8]! ; 00352610: ldur x0,[x29, #-0x60] ; 00352614: ldur x1,[x29, #-0x48] ; 00352618: ret */
cl4_result_t exc_frame_push2_2608(void)
{
    cl4_result_t r = { .lo = 0, .hi = 0 };
    return r;
}

/* FUN_0035261c @ 0x0035261c   (est. exc_frame_push_261c)
 * Ghidra: long FUN_0035261c(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035261c: stp x10,xzr,[x29, #-0x70] ; 00352620: stur x9,[x29, #-0x60] ; 00352624: sub x8,x29,#0xa8 ; 00352628: sub x0,x29,#0x80 ; 0035262c: ret */
word_t exc_frame_push_261c(void)
{
    return 0;
}

/* FUN_00352630 @ 0x00352630   (est. exc_tramp_2630)
 * Ghidra: void FUN_00352630(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352630: mov x0,x10 ; 00352634: mov x1,x3 ; 00352638: mov x2,x9 ; 0035263c: mov x3,x8 ; 00352640: ret */
void exc_tramp_2630(void)
{
    (void)0;
    return;
}

/* FUN_00352644 @ 0x00352644   (est. exc_frame_pop16_2644)
 * Ghidra: undefined1  [16] FUN_00352644(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352644: ldp q0,q1,[x29, #0x10] ; 00352648: ldp q2,q3,[x29, #0x30] ; 0035264c: ldr q4,[x29, #0x50] ; 00352650: ldp x8,x9,[x29, #0x60] ; 00352654: ret */
cl4_result_t exc_frame_pop16_2644(void)
{
    cl4_result_t r = { .lo = 0, .hi = 0 };
    return r;
}

/* FUN_00352658 @ 0x00352658   (est. err_string_16_2658)
 * Ghidra: undefined1  [16] FUN_00352658(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352658: adrp x0,0x4e7000 ; 0035265c: add x0,x0,#0xf24 ; 00352660: mov w1,#0x6 ; 00352664: mov w2,#0x1 ; 00352668: ret */
cl4_result_t err_string_16_2658(void)
{
    cl4_result_t r = { .lo = (word_t)"Double", .hi = 6 };
    return r;
}

/* FUN_0035266c @ 0x0035266c   (est. exc_restore_pair_266c)
 * Ghidra: undefined1  [16] FUN_0035266c(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035266c: ldur x22,[x8, #-0x100] ; 00352670: mov x0,x22 ; 00352674: ldur x21,[x29, #-0x70] ; 00352678: mov x1,x21 ; 0035267c: ret */
cl4_result_t exc_restore_pair_266c(word_t arg0)
{
    cl4_result_t r = { .lo = arg0 - 0x100, .hi = 0 };
    return r;
}

/* FUN_00352680 @ 0x00352680   (est. tail_000a68c4_2680)
 * Ghidra: void FUN_00352680(void)
 * Exception-entry tail wrapper: calls 0x000a68c4 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352680: pacibsp ; 00352684: str x30,[sp, #-0x10]! ; 00352688: bl 0x000a68c4 ; 0035268c: mov x9,x0 ; 00352690: ldr x30,[sp], #0x10 ; 00352694: retab */
void tail_000a68c4_2680(void)
{
    cL4_000a68c4();
    return;
}

/* FUN_00352698 @ 0x00352698   (est. exc_restore_word_2698)
 * Ghidra: undefined8 FUN_00352698(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352698: ldur x23,[x8, #-0x100] ; 0035269c: mov x0,x23 ; 003526a0: ret */
word_t exc_restore_word_2698(word_t arg0)
{
    return *(word_t *)(arg0 - 0x100);
}

/* FUN_003526a4 @ 0x003526a4   (est. exc_tramp_26a4)
 * Ghidra: void FUN_003526a4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003526a4: adrp x6,0x5d0000 ; 003526a8: add x6,x6,#0x290 ; 003526ac: mov w1,#0xb ; 003526b0: mov w2,#0x2 ; 003526b4: ret */
void exc_tramp_26a4(void)
{
    (void)0;
    return;
}

/* FUN_003526b8 @ 0x003526b8   (est. exc_restore_26b8)
 * Ghidra: void FUN_003526b8(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003526b8: ldur x21,[x8, #-0x100] ; 003526bc: mov x8,x21 ; 003526c0: ret */
void exc_restore_26b8(void)
{
    (void)0;
    return;
}

/* FUN_003526c4 @ 0x003526c4   (est. exc_tramp_26c4)
 * Ghidra: void FUN_003526c4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003526c4: mov x25,x5 ; 003526c8: mov x24,x4 ; 003526cc: mov x21,x3 ; 003526d0: mov x19,x2 ; 003526d4: ret */
void exc_tramp_26c4(void)
{
    (void)0;
    return;
}

/* FUN_003526d8 @ 0x003526d8   (est. exc_store_regs_struct_26d8)
 * Ghidra: void FUN_003526d8(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003526d8: stp x21,x20,[x19] ; 003526dc: strb w22,[x19, #0x10] ; 003526e0: stp x23,x24,[x19, #0x18] ; 003526e4: strb w8,[x19, #0x28] ; 003526e8: ret */
void exc_store_regs_struct_26d8(void *dst)
{
    /* packs caller registers into the exception-frame struct at dst:
       [0]={x21,x20}, [0x10]=w22(byte), [0x18]={x23,x24}, [0x28]=w8(byte) */
    (void)dst;
    return;
}

/* FUN_003526ec @ 0x003526ec   (est. exc_tramp_26ec)
 * Ghidra: void FUN_003526ec(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003526ec: adrp x1,0x656000 ; 003526f0: add x1,x1,#0xe0 ; 003526f4: adrp x2,0x4e7000 ; 003526f8: add x2,x2,#0xec8 ; 003526fc: ret */
void exc_tramp_26ec(void)
{
    (void)0;
    return;
}

/* FUN_00352700 @ 0x00352700   (est. exc_tramp_2700)
 * Ghidra: void FUN_00352700(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352700: mov x19,x4 ; 00352704: mov x21,x3 ; 00352708: ret */
void exc_tramp_2700(void)
{
    (void)0;
    return;
}

/* FUN_0035270c @ 0x0035270c   (est. exc_copy_reg_pair_270c)
 * Ghidra: void FUN_0035270c(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035270c: ldr x8,[x19, #0x10] ; 00352710: str x8,[x20, #0x10] ; 00352714: ldr x8,[x19, #0x18] ; 00352718: str x8,[x20, #0x18] ; 0035271c: ret */
void exc_copy_reg_pair_270c(word_t *src, word_t *dst)
{
    dst[2] = src[2];   /* offset 0x10 */
    dst[3] = src[3];   /* offset 0x18 */
    return;
}

/* FUN_00352720 @ 0x00352720   (est. exc_tramp_2720)
 * Ghidra: undefined8 FUN_00352720(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352720: mov w0,#0xff ; 00352724: mov x1,x25 ; 00352728: ret */
void exc_tramp_2720(void)
{
    (void)0;
    return;
}

/* FUN_0035272c @ 0x0035272c   (est. exc_store_tagged_272c)
 * Ghidra: void FUN_0035272c(undefined8 param_1,undefined1 param_2)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035272c: str x0,[x19] ; 00352730: strb w1,[x19, #0x8] ; 00352734: ret */
void exc_store_tagged_272c(word_t arg0, uint8_t arg1)
{
    /* stores {arg0} at [x19] and {arg1} at [x19+8] (register-base store) */
    (void)arg0; (void)arg1;
    return;
}

/* FUN_00352738 @ 0x00352738   (est. exc_store_2738)
 * Ghidra: void FUN_00352738(undefined8 param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352738: stur x8,[x29, #-0xa8] ; 0035273c: mov sp,x8 ; 00352740: ret */
void exc_store_2738(void)
{
    (void)0;
    return;
}

/* FUN_00352744 @ 0x00352744   (est. exc_restore_2744)
 * Ghidra: void FUN_00352744(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352744: sub x8,x29,#0x50 ; 00352748: ldur x8,[x8, #-0x100] ; 0035274c: sub x9,x29,#0x58 ; 00352750: ldur x9,[x9, #-0x100] ; 00352754: ret */
void exc_restore_2744(void)
{
    (void)0;
    return;
}

/* FUN_00352758 @ 0x00352758   (est. exc_tramp_2758)
 * Ghidra: void FUN_00352758(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352758: mov x22,x1 ; 0035275c: mov x19,x0 ; 00352760: ret */
void exc_tramp_2758(void)
{
    (void)0;
    return;
}

/* FUN_00352764 @ 0x00352764   (est. exc_copy_16_arg_2764)
 * Ghidra: undefined1  [16] FUN_00352764(undefined1 (*param_1) [16])
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352764: ldp x8,x9,[x0] ; 00352768: ldp x2,x3,[x1] ; 0035276c: mov x0,x8 ; 00352770: mov x1,x9 ; 00352774: ret */
cl4_result_t exc_copy_16_arg_2764(const void *arg0)
{
    return *(const cl4_result_t *)arg0;
}

/* FUN_00352778 @ 0x00352778   (est. exc_copy_word_2778)
 * Ghidra: void FUN_00352778(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352778: ldr x0,[x20] ; 0035277c: str x0,[x19] ; 00352780: ret */
void exc_copy_word_2778(word_t *src, word_t *dst)
{
    *dst = *src;
    return;
}

/* FUN_00352784 @ 0x00352784   (est. exc_tramp_2784)
 * Ghidra: void FUN_00352784(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352784: rbit x8,x28 ; 00352788: clz x8,x8 ; 0035278c: sub x9,x28,#0x1 ; 00352790: and x28,x9,x28 ; 00352794: ret */
void exc_tramp_2784(void)
{
    (void)0;
    return;
}

/* FUN_00352798 @ 0x00352798   (est. exc_tramp_2798)
 * Ghidra: void FUN_00352798(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352798: mov x23,x1 ; 0035279c: mov x19,x0 ; 003527a0: ret */
void exc_tramp_2798(void)
{
    (void)0;
    return;
}

/* FUN_003527a4 @ 0x003527a4   (est. exc_restore_27a4)
 * Ghidra: void FUN_003527a4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003527a4: ldrb w8,[x8, #0x1] ; 003527a8: and w8,w8,#0x3f ; 003527ac: bfm w8,w1,#0x1a,#0x4 ; 003527b0: mov x1,x8 ; 003527b4: ret */
void exc_restore_27a4(void)
{
    (void)0;
    return;
}

/* FUN_003527b8 @ 0x003527b8   (est. exc_tramp_27b8)
 * Ghidra: void FUN_003527b8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003527b8: mov w9,#0xffffffff ; 003527bc: eor w9,w9,w20, LSL #0x18 ; 003527c0: clz w9,w9 ; 003527c4: sub w16,w9,#0x1 ; 003527c8: ret */
void exc_tramp_27b8(void)
{
    (void)0;
    return;
}

/* FUN_003527cc @ 0x003527cc   (est. exc_restore_27cc)
 * Ghidra: void FUN_003527cc(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003527cc: ldr x9,[x23, #0x10]! ; 003527d0: add x1,x20,x8 ; 003527d4: mov x0,x24 ; 003527d8: mov x2,x21 ; 003527dc: ret */
void exc_restore_27cc(void)
{
    (void)0;
    return;
}

/* FUN_003527e0 @ 0x003527e0   (est. exc_tramp_27e0)
 * Ghidra: void FUN_003527e0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003527e0: mov x3,x24 ; 003527e4: mov x4,x25 ; 003527e8: ret */
void exc_tramp_27e0(void)
{
    (void)0;
    return;
}

/* FUN_003527ec @ 0x003527ec   (est. exc_tramp_27ec)
 * Ghidra: void FUN_003527ec(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003527ec: mov x28,x4 ; 003527f0: mov x23,x3 ; 003527f4: mov x26,x2 ; 003527f8: mov x24,x1 ; 003527fc: ret */
void exc_tramp_27ec(void)
{
    (void)0;
    return;
}

/* FUN_00352800 @ 0x00352800   (est. exc_tramp_2800)
 * Ghidra: void FUN_00352800(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352800: mov x19,x0 ; 00352804: mov x20,x8 ; 00352808: ret */
void exc_tramp_2800(void)
{
    (void)0;
    return;
}

/* FUN_0035280c @ 0x0035280c   (est. fatal_error_str_280c)
 * Ghidra: char * FUN_0035280c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035280c: adrp x0,0x5ac000 ; 00352810: add x0,x0,#0xcd0 ; 00352814: adrp x5,0x5d0000 ; 00352818: add x5,x5,#0xde0 ; 0035281c: ret */
const char * fatal_error_str_280c(void)
{
    return "Fatal error";
}

/* FUN_00352820 @ 0x00352820   (est. exc_restore_2820)
 * Ghidra: void FUN_00352820(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352820: mov x28,x0 ; 00352824: ldr x27,[x28, #-0x8]! ; 00352828: mov x16,x27 ; 0035282c: mov x17,x28 ; 00352830: ret */
void exc_restore_2820(void)
{
    (void)0;
    return;
}

/* FUN_00352834 @ 0x00352834   (est. exc_restore_2834)
 * Ghidra: void FUN_00352834(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352834: ldr x9,[x8, #0x10]! ; 00352838: mov x0,x21 ; 0035283c: ret */
void exc_restore_2834(void)
{
    (void)0;
    return;
}

/* FUN_00352840 @ 0x00352840   (est. exc_tramp_2840)
 * Ghidra: void FUN_00352840(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352840: mov x1,x26 ; 00352844: mov x2,x27 ; 00352848: ret */
void exc_tramp_2840(void)
{
    (void)0;
    return;
}

/* FUN_0035284c @ 0x0035284c   (est. exc_tramp_284c)
 * Ghidra: void FUN_0035284c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035284c: mov x1,x25 ; 00352850: mov x2,x27 ; 00352854: ret */
void exc_tramp_284c(void)
{
    (void)0;
    return;
}

/* FUN_00352858 @ 0x00352858   (est. exc_tramp_2858)
 * Ghidra: void FUN_00352858(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352858: mov x1,x28 ; 0035285c: mov x2,x26 ; 00352860: ret */
void exc_tramp_2858(void)
{
    (void)0;
    return;
}

/* FUN_00352864 @ 0x00352864   (est. exc_tramp_2864)
 * Ghidra: void FUN_00352864(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352864: mov x1,x28 ; 00352868: mov x2,x21 ; 0035286c: ret */
void exc_tramp_2864(void)
{
    (void)0;
    return;
}

/* FUN_00352870 @ 0x00352870   (est. exc_restore_2870)
 * Ghidra: void FUN_00352870(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352870: mov x8,x22 ; 00352874: ldr x9,[x8, #0x8]! ; 00352878: ret */
void exc_restore_2870(void)
{
    (void)0;
    return;
}

/* FUN_0035287c @ 0x0035287c   (est. exc_tramp_287c)
 * Ghidra: void FUN_0035287c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035287c: mov x8,x25 ; 00352880: mov x0,x27 ; 00352884: ret */
void exc_tramp_287c(void)
{
    (void)0;
    return;
}

/* FUN_00352888 @ 0x00352888   (est. exc_tramp_2888)
 * Ghidra: void FUN_00352888(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352888: mov x0,x27 ; 0035288c: mov w1,#0x1 ; 00352890: ret */
void exc_tramp_2888(void)
{
    (void)0;
    return;
}

/* FUN_00352894 @ 0x00352894   (est. tail_00027754_2894)
 * Ghidra: void FUN_00352894(void)
 * Exception-entry tail wrapper: calls 0x00027754 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352894: pacibsp ; 00352898: str x30,[sp, #-0x10]! ; 0035289c: bl 0x00027754 ; 003528a0: mov x24,x0 ; 003528a4: ldr x30,[sp], #0x10 ; 003528a8: retab */
void tail_00027754_2894(void)
{
    cL4_00027754();
    return;
}

/* FUN_003528ac @ 0x003528ac   (est. exc_tramp_28ac)
 * Ghidra: void FUN_003528ac(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003528ac: mov x2,x24 ; 003528b0: mov x3,x21 ; 003528b4: ret */
void exc_tramp_28ac(void)
{
    (void)0;
    return;
}

/* FUN_003528b8 @ 0x003528b8   (est. exc_store_regs_28b8)
 * Ghidra: void FUN_003528b8(undefined8 *param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003528b8: mov x24,x0 ; 003528bc: str x0,[x19] ; 003528c0: stp x21,x20,[x0, #0x8] ; 003528c4: str x22,[x0] ; 003528c8: ret */
void exc_store_regs_28b8(void *arg0)
{
    /* stores caller registers: *arg0 = x22 ; {x21,x20} at arg0+8 */
    (void)arg0;
    return;
}

/* FUN_003528cc @ 0x003528cc   (est. exc_tramp_28cc)
 * Ghidra: undefined8 FUN_003528cc(undefined8 param_1,undefined8 param_2)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003528cc: mov x20,x0 ; 003528d0: mov x0,x1 ; 003528d4: ret */
void exc_tramp_28cc(void)
{
    (void)0;
    return;
}

/* FUN_003528d8 @ 0x003528d8   (est. exc_const_0_28d8)
 * Ghidra: undefined8 FUN_003528d8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003528d8: adrp x23,0x60e000 ; 003528dc: add x23,x23,#0x3fc ; 003528e0: add x4,x23,#0x10 ; 003528e4: mov x0,#0x0 ; 003528e8: ret */
word_t exc_const_0_28d8(void)
{
    return 0;
}

/* FUN_003528ec @ 0x003528ec   (est. exc_restore_28ec)
 * Ghidra: void FUN_003528ec(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003528ec: mov x0,x19 ; 003528f0: sub x8,x29,#0x58 ; 003528f4: ldur x19,[x8, #-0x100] ; 003528f8: mov x1,x21 ; 003528fc: ret */
void exc_restore_28ec(void)
{
    (void)0;
    return;
}

/* FUN_00352900 @ 0x00352900   (est. exc_tramp_2900)
 * Ghidra: void FUN_00352900(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352900: mov x0,x19 ; 00352904: mov x1,x21 ; 00352908: mov x2,x23 ; 0035290c: mov x3,x22 ; 00352910: ret */
void exc_tramp_2900(void)
{
    (void)0;
    return;
}

/* FUN_00352914 @ 0x00352914   (est. exc_tramp_2914)
 * Ghidra: void FUN_00352914(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352914: mov x19,x1 ; 00352918: mov x22,x0 ; 0035291c: ret */
void exc_tramp_2914(void)
{
    (void)0;
    return;
}

/* FUN_00352920 @ 0x00352920   (est. exc_tramp_2920)
 * Ghidra: void FUN_00352920(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352920: mov x3,x21 ; 00352924: mov x4,x19 ; 00352928: ret */
void exc_tramp_2920(void)
{
    (void)0;
    return;
}

/* FUN_0035292c @ 0x0035292c   (est. exc_tramp_292c)
 * Ghidra: void FUN_0035292c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035292c: and w8,w2,#0xff ; 00352930: cmp w8,#0x1 ; 00352934: ret */
void exc_tramp_292c(void)
{
    (void)0;
    return;
}

/* FUN_00352938 @ 0x00352938   (est. exc_tramp_2938)
 * Ghidra: void FUN_00352938(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352938: mov x2,#0x0 ; 0035293c: mov x3,x25 ; 00352940: ret */
void exc_tramp_2938(void)
{
    (void)0;
    return;
}

/* FUN_00352944 @ 0x00352944   (est. store_max_word_2944)
 * Ghidra: void FUN_00352944(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352944: mov x8,#-0x8000000000000000 ; 00352948: stur x8,[x29, #-0x60] ; 0035294c: ret */
void store_max_word_2944(void)
{
    (void)0;
    return;
}

/* FUN_00352950 @ 0x00352950   (est. store_min_word_2950)
 * Ghidra: void FUN_00352950(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352950: mov x8,#0x7fffffffffffffff ; 00352954: stur x8,[x29, #-0x58] ; 00352958: ret */
void store_min_word_2950(void)
{
    (void)0;
    return;
}

/* FUN_0035295c @ 0x0035295c   (est. exc_restore_295c)
 * Ghidra: void FUN_0035295c(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035295c: mov x17,x0 ; 00352960: ldr x16,[x17, #-0x8]! ; 00352964: ret */
void exc_restore_295c(void)
{
    (void)0;
    return;
}

/* FUN_00352968 @ 0x00352968   (est. exc_const_0xff_2968)
 * Ghidra: undefined8 FUN_00352968(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352968: add x4,x19,#0x28 ; 0035296c: mov w0,#0xff ; 00352970: ret */
word_t exc_const_0xff_2968(void)
{
    return 0xff;
}

/* FUN_00352974 @ 0x00352974   (est. exc_tramp_2974)
 * Ghidra: void FUN_00352974(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352974: adrp x3,0x5cd000 ; 00352978: add x3,x3,#0xab0 ; 0035297c: ret */
void exc_tramp_2974(void)
{
    (void)0;
    return;
}

/* FUN_00352980 @ 0x00352980   (est. exc_flag_lsb_2980)
 * Ghidra: uint FUN_00352980(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352980: and w0,w20,#0x1 ; 00352984: sub sp,x29,#0x50 ; 00352988: ret */
unsigned int exc_flag_lsb_2980(unsigned int w20)
{
    /* returns w20 & 1 — tests the low bit of caller register w20 */
    return w20 & 1;
}

/* FUN_0035298c @ 0x0035298c   (est. exc_const_0xff_298c)
 * Ghidra: undefined8 FUN_0035298c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035298c: mov w0,#0xff ; 00352990: mov x1,x23 ; 00352994: ret */
word_t exc_const_0xff_298c(void)
{
    return 0xff;
}

/* FUN_00352998 @ 0x00352998   (est. exc_tramp_2998)
 * Ghidra: void FUN_00352998(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352998: mov x2,x27 ; 0035299c: mov x3,x22 ; 003529a0: ret */
void exc_tramp_2998(void)
{
    (void)0;
    return;
}

/* FUN_003529a4 @ 0x003529a4   (est. exc_restore_29a4)
 * Ghidra: void FUN_003529a4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 003529a4: ldur x9,[x29, #-0x78] ; 003529a8: ldr x8,[x9, #0x8]! ; 003529ac: ret */
void exc_restore_29a4(void)
{
    (void)0;
    return;
}

/* FUN_003529b0 @ 0x003529b0   (est. exc_tramp_29b0)
 * Ghidra: void FUN_003529b0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003529b0: mov x2,x26 ; 003529b4: mov x3,x24 ; 003529b8: ret */
void exc_tramp_29b0(void)
{
    (void)0;
    return;
}

/* FUN_003529bc @ 0x003529bc   (est. exc_tramp_29bc)
 * Ghidra: void FUN_003529bc(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003529bc: lsr w8,w20,#0x6 ; 003529c0: ubfiz w9,w20,#0x8,#0x6 ; 003529c4: add w8,w8,w9 ; 003529c8: mov w10,#0x81c1 ; 003529cc: add w8,w8,w10 ; 003529d0: ubfx w10,w20,#0x6,#0x6 ; 003529d4: orr w9,w9,w10 ; 003529d8: lsr w10,w20,#0xc ; 003529dc: lsl w9,w9,#0x8 ; 003529e0: lsr w11,w20,#0x10 ; 003529e4: ubfx w12,w20,#0xc,#0x6 ; 003529e8: orr w12,w9,w12 ; 003529ec: lsl w12,w12,#0x8 ; 003529f0: orr w12,w12,w20, LSR #0x12 ; 003529f4: mov w13,#0x81f1 ; 003529f8: movk w13,#0x8181, LSL #16 ; 003529fc: add w12,w12,w13 ; 00352a00: add w9,w10,w9 ; 00352a04: mov w10,#0x81e1 ; 00352a08: movk w10,#0x81, LSL #16 ; 00352a0c: add w9,w9,w10 ; 00352a10: cmp w11,#0x0 ; 00352a14: csel w9,w12,w9,ne ; 00352a18: ret */
void exc_tramp_29bc(void)
{
    (void)0;
    return;
}

/* FUN_00352a1c @ 0x00352a1c   (est. exc_tramp_2a1c)
 * Ghidra: void FUN_00352a1c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a1c: mov x20,x28 ; 00352a20: mov x3,x28 ; 00352a24: ret */
void exc_tramp_2a1c(void)
{
    (void)0;
    return;
}

/* FUN_00352a28 @ 0x00352a28   (est. exc_tramp_2a28)
 * Ghidra: void FUN_00352a28(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a28: mov x0,x23 ; 00352a2c: mov x2,x19 ; 00352a30: ret */
void exc_tramp_2a28(void)
{
    (void)0;
    return;
}

/* FUN_00352a34 @ 0x00352a34   (est. exc_tramp_2a34)
 * Ghidra: void FUN_00352a34(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a34: mov x1,x20 ; 00352a38: mov x2,x27 ; 00352a3c: ret */
void exc_tramp_2a34(void)
{
    (void)0;
    return;
}

/* FUN_00352a40 @ 0x00352a40   (est. exc_restore_2a40)
 * Ghidra: void FUN_00352a40(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352a40: mov x8,x25 ; 00352a44: ldr x9,[x8, #0x10]! ; 00352a48: ret */
void exc_restore_2a40(void)
{
    (void)0;
    return;
}

/* FUN_00352a4c @ 0x00352a4c   (est. exc_tramp_2a4c)
 * Ghidra: void FUN_00352a4c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a4c: mov x2,x20 ; 00352a50: mov x3,x24 ; 00352a54: ret */
void exc_tramp_2a4c(void)
{
    (void)0;
    return;
}

/* FUN_00352a58 @ 0x00352a58   (est. exc_tramp_2a58)
 * Ghidra: void FUN_00352a58(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a58: mov x2,x22 ; 00352a5c: mov x3,x25 ; 00352a60: ret */
void exc_tramp_2a58(void)
{
    (void)0;
    return;
}

/* FUN_00352a64 @ 0x00352a64   (est. exc_tramp_2a64)
 * Ghidra: void FUN_00352a64(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352a64: mov x8,x27 ; 00352a68: mov x0,x26 ; 00352a6c: ret */
void exc_tramp_2a64(void)
{
    (void)0;
    return;
}

/* FUN_00352a70 @ 0x00352a70   (est. tail_000a649c_2a70)
 * Ghidra: void FUN_00352a70(void)
 * Exception-entry tail wrapper: calls 0x000a649c (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352a70: pacibsp ; 00352a74: str x30,[sp, #-0x10]! ; 00352a78: bl 0x000a649c ; 00352a7c: mov x9,x0 ; 00352a80: sub x8,x29,#0x78 ; 00352a84: ldr x30,[sp], #0x10 ; 00352a88: retab */
void tail_000a649c_2a70(void)
{
    cL4_000a649c();
    return;
}

/* FUN_00352a8c @ 0x00352a8c   (est. panic_02534_entry_2a8c)
 * Ghidra: void FUN_00352a8c(void)
 * Exception-entry tail wrapper: calls 0x00002534 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352a8c: adrp x0,0x656000 ; 00352a90: add x0,x0,#0x208 ; 00352a94: adrp x1,0x4e8000 ; 00352a98: add x1,x1,#0x60 ; 00352a9c: b 0x00002534 */
void panic_02534_entry_2a8c(void)
{
    cL4_00002534((void *)0x656208, (void *)0x4e8060); /* DAT_004e8060 */
    return;
}

/* FUN_00352aa0 @ 0x00352aa0   (est. tail_00310a74_2aa0)
 * Ghidra: void FUN_00352aa0(void)
 * Exception-entry tail wrapper: calls 0x00310a74 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352aa0: pacibsp ; 00352aa4: str x30,[sp, #-0x10]! ; 00352aa8: mov x0,x21 ; 00352aac: bl 0x00310a74 ; 00352ab0: mov x22,x0 ; 00352ab4: ldr x30,[sp], #0x10 ; 00352ab8: retab */
void tail_00310a74_2aa0(void)
{
    cL4_00310a74();
    return;
}

/* FUN_00352abc @ 0x00352abc   (est. tail_00319628_2abc)
 * Ghidra: void FUN_00352abc(void)
 * Exception-entry tail wrapper: calls 0x00319628 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352abc: pacibsp ; 00352ac0: str x30,[sp, #-0x10]! ; 00352ac4: mov x0,x21 ; 00352ac8: bl 0x00319628 ; 00352acc: mov x9,x0 ; 00352ad0: ldr x30,[sp], #0x10 ; 00352ad4: retab */
void tail_00319628_2abc(void)
{
    cL4_00319628();
    return;
}

/* FUN_00352ad8 @ 0x00352ad8   (est. exc_tramp_2ad8)
 * Ghidra: void FUN_00352ad8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ad8: ubfx x9,x22,#0x38,#0x4 ; 00352adc: tst x22,#0x2000000000000000 ; 00352ae0: ret */
void exc_tramp_2ad8(void)
{
    (void)0;
    return;
}

/* FUN_00352ae4 @ 0x00352ae4   (est. exc_tramp_2ae4)
 * Ghidra: void FUN_00352ae4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ae4: mov x2,x24 ; 00352ae8: mov x3,x23 ; 00352aec: ret */
void exc_tramp_2ae4(void)
{
    (void)0;
    return;
}

/* FUN_00352af0 @ 0x00352af0   (est. exc_tramp_2af0)
 * Ghidra: void FUN_00352af0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352af0: clz w9,w9 ; 00352af4: sub w16,w9,#0x1 ; 00352af8: ret */
void exc_tramp_2af0(void)
{
    (void)0;
    return;
}

/* FUN_00352afc @ 0x00352afc   (est. exc_restore_word_2afc)
 * Ghidra: undefined8 FUN_00352afc(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352afc: ldur x22,[x29, #-0x68] ; 00352b00: mov x0,x22 ; 00352b04: ret */
word_t exc_restore_word_2afc(void)
{
    return 0;
}

/* FUN_00352b08 @ 0x00352b08   (est. exc_tramp_2b08)
 * Ghidra: void FUN_00352b08(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b08: mov x2,x27 ; 00352b0c: mov x3,x19 ; 00352b10: ret */
void exc_tramp_2b08(void)
{
    (void)0;
    return;
}

/* FUN_00352b14 @ 0x00352b14   (est. exc_restore_2b14)
 * Ghidra: void FUN_00352b14(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b14: ldr x8,[x9] ; 00352b18: mov x0,x27 ; 00352b1c: ret */
void exc_restore_2b14(void)
{
    (void)0;
    return;
}

/* FUN_00352b20 @ 0x00352b20   (est. exc_load_word_2b20)
 * Ghidra: undefined8 FUN_00352b20(undefined8 *param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b20: mov x19,x0 ; 00352b24: ldr x0,[x0] ; 00352b28: ret */
word_t exc_load_word_2b20(const word_t *arg0)
{
    return *arg0;
}

/* FUN_00352b2c @ 0x00352b2c   (est. exc_tramp_2b2c)
 * Ghidra: void FUN_00352b2c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b2c: mov x0,x28 ; 00352b30: mov x20,x21 ; 00352b34: ret */
void exc_tramp_2b2c(void)
{
    (void)0;
    return;
}

/* FUN_00352b38 @ 0x00352b38   (est. exc_tramp_2b38)
 * Ghidra: void FUN_00352b38(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b38: mov x1,#0x0 ; 00352b3c: mov w2,#0x2 ; 00352b40: ret */
void exc_tramp_2b38(void)
{
    (void)0;
    return;
}

/* FUN_00352b44 @ 0x00352b44   (est. exc_tramp_2b44)
 * Ghidra: void FUN_00352b44(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b44: mov x1,x25 ; 00352b48: mov x2,x28 ; 00352b4c: ret */
void exc_tramp_2b44(void)
{
    (void)0;
    return;
}

/* FUN_00352b50 @ 0x00352b50   (est. exc_restore_2b50)
 * Ghidra: void FUN_00352b50(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b50: mov x8,x25 ; 00352b54: ldr x9,[x8, #0x20]! ; 00352b58: ret */
void exc_restore_2b50(void)
{
    (void)0;
    return;
}

/* FUN_00352b5c @ 0x00352b5c   (est. exc_tramp_2b5c)
 * Ghidra: void FUN_00352b5c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b5c: mov x1,x27 ; 00352b60: mov x2,x28 ; 00352b64: ret */
void exc_tramp_2b5c(void)
{
    (void)0;
    return;
}

/* FUN_00352b68 @ 0x00352b68   (est. exc_tramp_2b68)
 * Ghidra: void FUN_00352b68(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b68: mov x2,x21 ; 00352b6c: mov x3,x28 ; 00352b70: ret */
void exc_tramp_2b68(void)
{
    (void)0;
    return;
}

/* FUN_00352b74 @ 0x00352b74   (est. exc_tramp_2b74)
 * Ghidra: void FUN_00352b74(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352b74: mov x20,x0 ; 00352b78: mov x0,x28 ; 00352b7c: ret */
void exc_tramp_2b74(void)
{
    (void)0;
    return;
}

/* FUN_00352b80 @ 0x00352b80   (est. exc_restore_2b80)
 * Ghidra: void FUN_00352b80(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b80: sub x9,x29,#0x40 ; 00352b84: ldur x9,[x9, #-0x100] ; 00352b88: ret */
void exc_restore_2b80(void)
{
    (void)0;
    return;
}

/* FUN_00352b8c @ 0x00352b8c   (est. exc_restore_word_2b8c)
 * Ghidra: undefined8 FUN_00352b8c(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b8c: ldur x22,[x8, #-0x100] ; 00352b90: mov x0,x22 ; 00352b94: ret */
word_t exc_restore_word_2b8c(word_t arg0)
{
    return *(word_t *)(arg0 - 0x100);
}

/* FUN_00352b98 @ 0x00352b98   (est. exc_frame_store_2b98)
 * Ghidra: void FUN_00352b98(undefined8 param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352b98: sub x9,x29,#0x8 ; 00352b9c: stur x8,[x9, #-0x100] ; 00352ba0: ret */
void exc_frame_store_2b98(word_t arg0)
{
    (void)arg0;
    return;
}

/* FUN_00352ba4 @ 0x00352ba4   (est. exc_tramp_2ba4)
 * Ghidra: void FUN_00352ba4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ba4: add x1,x20,x8 ; 00352ba8: mov x0,x26 ; 00352bac: ret */
void exc_tramp_2ba4(void)
{
    (void)0;
    return;
}

/* FUN_00352bb0 @ 0x00352bb0   (est. exc_restore_2bb0)
 * Ghidra: void FUN_00352bb0(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352bb0: mov x8,x23 ; 00352bb4: ldr x9,[x8, #0x10]! ; 00352bb8: ret */
void exc_restore_2bb0(void)
{
    (void)0;
    return;
}

/* FUN_00352bbc @ 0x00352bbc   (est. exc_restore_2bbc)
 * Ghidra: void FUN_00352bbc(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352bbc: sub x8,x29,#0x50 ; 00352bc0: ldur x8,[x8, #-0x100] ; 00352bc4: ret */
void exc_restore_2bbc(void)
{
    (void)0;
    return;
}

/* FUN_00352bc8 @ 0x00352bc8   (est. exc_restore_2bc8)
 * Ghidra: void FUN_00352bc8(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352bc8: ldr x8,[x9] ; 00352bcc: mov x0,x23 ; 00352bd0: ret */
void exc_restore_2bc8(void)
{
    (void)0;
    return;
}

/* FUN_00352bd4 @ 0x00352bd4   (est. exc_tramp_2bd4)
 * Ghidra: void FUN_00352bd4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352bd4: and w9,w8,#0x80808080 ; 00352bd8: cmp w8,#0xa0d ; 00352bdc: ret */
void exc_tramp_2bd4(void)
{
    (void)0;
    return;
}

/* FUN_00352be0 @ 0x00352be0   (est. exc_tramp_2be0)
 * Ghidra: void FUN_00352be0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352be0: mov w5,#0x2 ; 00352be4: mov w7,#0x17 ; 00352be8: ret */
void exc_tramp_2be0(void)
{
    (void)0;
    return;
}

/* FUN_00352bec @ 0x00352bec   (est. exc_tramp_2bec)
 * Ghidra: void FUN_00352bec(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352bec: mov x2,x25 ; 00352bf0: mov x3,x22 ; 00352bf4: ret */
void exc_tramp_2bec(void)
{
    (void)0;
    return;
}

/* FUN_00352bf8 @ 0x00352bf8   (est. exc_restore_2bf8)
 * Ghidra: void FUN_00352bf8(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352bf8: ldur x28,[x29, #-0x98] ; 00352bfc: mov x8,x28 ; 00352c00: ret */
void exc_restore_2bf8(void)
{
    (void)0;
    return;
}

/* FUN_00352c04 @ 0x00352c04   (est. exc_restore_2c04)
 * Ghidra: void FUN_00352c04(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352c04: ldr x9,[x8, #0x10]! ; 00352c08: mov x0,x19 ; 00352c0c: ret */
void exc_restore_2c04(void)
{
    (void)0;
    return;
}

/* FUN_00352c10 @ 0x00352c10   (est. exc_tramp_2c10)
 * Ghidra: void FUN_00352c10(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c10: mov x23,x2 ; 00352c14: mov x19,x1 ; 00352c18: ret */
void exc_tramp_2c10(void)
{
    (void)0;
    return;
}

/* FUN_00352c1c @ 0x00352c1c   (est. exc_tramp_2c1c)
 * Ghidra: void FUN_00352c1c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c1c: mov x8,x22 ; 00352c20: mov x0,x21 ; 00352c24: ret */
void exc_tramp_2c1c(void)
{
    (void)0;
    return;
}

/* FUN_00352c28 @ 0x00352c28   (est. exc_tramp_2c28)
 * Ghidra: void FUN_00352c28(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c28: mov x2,x20 ; 00352c2c: mov x3,x26 ; 00352c30: ret */
void exc_tramp_2c28(void)
{
    (void)0;
    return;
}

/* FUN_00352c34 @ 0x00352c34   (est. exc_tramp_2c34)
 * Ghidra: void FUN_00352c34(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c34: mov x19,x3 ; 00352c38: mov x22,x2 ; 00352c3c: ret */
void exc_tramp_2c34(void)
{
    (void)0;
    return;
}

/* FUN_00352c40 @ 0x00352c40   (est. exc_tramp_2c40)
 * Ghidra: void FUN_00352c40(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c40: mov x3,x22 ; 00352c44: mov x4,x23 ; 00352c48: ret */
void exc_tramp_2c40(void)
{
    (void)0;
    return;
}

/* FUN_00352c4c @ 0x00352c4c   (est. exc_tramp_2c4c)
 * Ghidra: void FUN_00352c4c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c4c: mov x1,x27 ; 00352c50: mov x2,x26 ; 00352c54: ret */
void exc_tramp_2c4c(void)
{
    (void)0;
    return;
}

/* FUN_00352c58 @ 0x00352c58   (est. tail_3a25d4_2c58)
 * Ghidra: void FUN_00352c58(void)
 * Exception-entry tail wrapper: calls 0x003a25d4 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352c58: mov x20,x0 ; 00352c5c: mov x23,x1 ; 00352c60: mov x0,x21 ; 00352c64: b 0x003a25d4 */
void tail_3a25d4_2c58(word_t arg0, word_t arg1, word_t arg2)
{
    /* mov x20,x0; mov x23,x1; mov x0,x21; b 0x3a25d4 */
    (void)arg0; (void)arg1; (void)arg2;
    cL4_003a25d4();
    return;
}

/* FUN_00352c68 @ 0x00352c68   (est. exc_tramp_2c68)
 * Ghidra: void FUN_00352c68(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c68: mov x0,x20 ; 00352c6c: mov w1,#0x0 ; 00352c70: ret */
void exc_tramp_2c68(void)
{
    (void)0;
    return;
}

/* FUN_00352c74 @ 0x00352c74   (est. exc_tramp_2c74)
 * Ghidra: void FUN_00352c74(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c74: mov x23,x0 ; 00352c78: mov x21,x1 ; 00352c7c: ret */
void exc_tramp_2c74(void)
{
    (void)0;
    return;
}

/* FUN_00352c80 @ 0x00352c80   (est. exc_tramp_2c80)
 * Ghidra: void FUN_00352c80(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352c80: mov x21,x0 ; 00352c84: mov x19,x1 ; 00352c88: ret */
void exc_tramp_2c80(void)
{
    (void)0;
    return;
}

/* FUN_00352c8c @ 0x00352c8c   (est. exc_restore_word_2c8c)
 * Ghidra: undefined8 FUN_00352c8c(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352c8c: ldur x24,[x29, #-0x78] ; 00352c90: mov x0,x24 ; 00352c94: ret */
word_t exc_restore_word_2c8c(void)
{
    return 0;
}

/* FUN_00352c98 @ 0x00352c98   (est. exc_restore_word_2c98)
 * Ghidra: undefined8 FUN_00352c98(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352c98: ldur x25,[x8, #-0x100] ; 00352c9c: mov x0,x25 ; 00352ca0: ret */
word_t exc_restore_word_2c98(word_t arg0)
{
    return *(word_t *)(arg0 - 0x100);
}

/* FUN_00352ca4 @ 0x00352ca4   (est. exc_restore_2ca4)
 * Ghidra: void FUN_00352ca4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352ca4: ldur x25,[x8, #-0x100] ; 00352ca8: mov x8,x25 ; 00352cac: ret */
void exc_restore_2ca4(void)
{
    (void)0;
    return;
}

/* FUN_00352cb0 @ 0x00352cb0   (est. exc_tramp_2cb0)
 * Ghidra: void FUN_00352cb0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352cb0: adrp x8,0x675000 ; 00352cb4: add x8,x8,#0x3a0 ; 00352cb8: ret */
void exc_tramp_2cb0(void)
{
    (void)0;
    return;
}

/* FUN_00352cbc @ 0x00352cbc   (est. exc_restore_2cbc)
 * Ghidra: void FUN_00352cbc(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352cbc: ldur x2,[x9, #-0x100] ; 00352cc0: mov x20,x2 ; 00352cc4: ret */
void exc_restore_2cbc(void)
{
    (void)0;
    return;
}

/* FUN_00352cc8 @ 0x00352cc8   (est. exc_tramp_2cc8)
 * Ghidra: void FUN_00352cc8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352cc8: mov x2,#0x0 ; 00352ccc: mov x3,x19 ; 00352cd0: ret */
void exc_tramp_2cc8(void)
{
    (void)0;
    return;
}

/* FUN_00352cd4 @ 0x00352cd4   (est. exc_restore_2cd4)
 * Ghidra: void FUN_00352cd4(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352cd4: ldr x16,[x24, #-0x8]! ; 00352cd8: mov x17,x24 ; 00352cdc: ret */
void exc_restore_2cd4(void)
{
    (void)0;
    return;
}

/* FUN_00352ce0 @ 0x00352ce0   (est. exc_tramp_2ce0)
 * Ghidra: void FUN_00352ce0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ce0: mov x22,x4 ; 00352ce4: mov x23,x3 ; 00352ce8: ret */
void exc_tramp_2ce0(void)
{
    (void)0;
    return;
}

/* FUN_00352cec @ 0x00352cec   (est. exc_tramp_2cec)
 * Ghidra: void FUN_00352cec(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352cec: mov x21,x2 ; 00352cf0: mov x19,x1 ; 00352cf4: ret */
void exc_tramp_2cec(void)
{
    (void)0;
    return;
}

/* FUN_00352cf8 @ 0x00352cf8   (est. exc_tramp_2cf8)
 * Ghidra: void FUN_00352cf8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352cf8: mov x20,x27 ; 00352cfc: mov x0,x27 ; 00352d00: ret */
void exc_tramp_2cf8(void)
{
    (void)0;
    return;
}

/* FUN_00352d04 @ 0x00352d04   (est. exc_restore_2d04)
 * Ghidra: void FUN_00352d04(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352d04: ldr x9,[x8, #0x8]! ; 00352d08: mov x0,x28 ; 00352d0c: ret */
void exc_restore_2d04(void)
{
    (void)0;
    return;
}

/* FUN_00352d10 @ 0x00352d10   (est. exc_restore_2d10)
 * Ghidra: void FUN_00352d10(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352d10: mov x8,x24 ; 00352d14: ldr x16,[x8, #-0x8]! ; 00352d18: ret */
void exc_restore_2d10(void)
{
    (void)0;
    return;
}

/* FUN_00352d1c @ 0x00352d1c   (est. exc_tramp_2d1c)
 * Ghidra: void FUN_00352d1c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352d1c: mov x1,x20 ; 00352d20: mov x2,x26 ; 00352d24: ret */
void exc_tramp_2d1c(void)
{
    (void)0;
    return;
}

/* FUN_00352d28 @ 0x00352d28   (est. exc_tramp_2d28)
 * Ghidra: void FUN_00352d28(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352d28: mov x8,x25 ; 00352d2c: mov x0,x22 ; 00352d30: ret */
void exc_tramp_2d28(void)
{
    (void)0;
    return;
}

/* FUN_00352d34 @ 0x00352d34   (est. exc_tramp_2d34)
 * Ghidra: void FUN_00352d34(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352d34: mov x8,x25 ; 00352d38: mov x0,x19 ; 00352d3c: ret */
void exc_tramp_2d34(void)
{
    (void)0;
    return;
}

/* FUN_00352d40 @ 0x00352d40   (est. exc_tramp_2d40)
 * Ghidra: void FUN_00352d40(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352d40: mov x2,x21 ; 00352d44: mov x3,x24 ; 00352d48: ret */
void exc_tramp_2d40(void)
{
    (void)0;
    return;
}

/* FUN_00352d4c @ 0x00352d4c   (est. tail_00310a74_2d4c)
 * Ghidra: void FUN_00352d4c(void)
 * Exception-entry tail wrapper: calls 0x00310a74 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352d4c: pacibsp ; 00352d50: str x30,[sp, #-0x10]! ; 00352d54: bl 0x00310a74 ; 00352d58: mov x21,x0 ; 00352d5c: ldr x30,[sp], #0x10 ; 00352d60: retab */
void tail_00310a74_2d4c(void)
{
    cL4_00310a74();
    return;
}

/* FUN_00352d64 @ 0x00352d64   (est. exc_restore_word_2d64)
 * Ghidra: undefined8 FUN_00352d64(long param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352d64: ldur x26,[x8, #-0x100] ; 00352d68: mov x0,x26 ; 00352d6c: ret */
word_t exc_restore_word_2d64(word_t arg0)
{
    return *(word_t *)(arg0 - 0x100);
}

/* FUN_00352d70 @ 0x00352d70   (est. tail_00310954_2d70)
 * Ghidra: void FUN_00352d70(void)
 * Exception-entry tail wrapper: calls 0x00310954 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352d70: pacibsp ; 00352d74: str x30,[sp, #-0x10]! ; 00352d78: bl 0x00310954 ; 00352d7c: mov x8,x0 ; 00352d80: ldr x30,[sp], #0x10 ; 00352d84: retab */
void tail_00310954_2d70(void)
{
    cL4_00310954();
    return;
}

/* FUN_00352d88 @ 0x00352d88   (est. exc_tramp_2d88)
 * Ghidra: void FUN_00352d88(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352d88: mov x20,x25 ; 00352d8c: mov x3,x25 ; 00352d90: ret */
void exc_tramp_2d88(void)
{
    (void)0;
    return;
}

/* FUN_00352d94 @ 0x00352d94   (est. exc_restore_2d94)
 * Ghidra: void FUN_00352d94(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352d94: sub x10,x29,#0x60 ; 00352d98: ldur x2,[x10, #-0x100] ; 00352d9c: ret */
void exc_restore_2d94(void)
{
    (void)0;
    return;
}

/* FUN_00352da0 @ 0x00352da0   (est. exc_tramp_2da0)
 * Ghidra: void FUN_00352da0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352da0: adrp x1,0x677000 ; 00352da4: add x1,x1,#0x790 ; 00352da8: ret */
void exc_tramp_2da0(void)
{
    (void)0;
    return;
}

/* FUN_00352dac @ 0x00352dac   (est. exc_copy_16_2dac)
 * Ghidra: void FUN_00352dac(undefined8 *param_1)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352dac: ldr q0,[x8] ; 00352db0: str q0,[x9] ; 00352db4: ret */
void exc_copy_16_2dac(const void *src, void *dst)
{
    /* ldr q0,[x8] ; str q0,[x9] — 16-byte copy */
    __builtin_memcpy(dst, src, 16);
    return;
}

/* FUN_00352db8 @ 0x00352db8   (est. exc_tramp_2db8)
 * Ghidra: void FUN_00352db8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352db8: mov x2,#0x0 ; 00352dbc: mov x3,x26 ; 00352dc0: ret */
void exc_tramp_2db8(void)
{
    (void)0;
    return;
}

/* FUN_00352dc4 @ 0x00352dc4   (est. exc_tramp_2dc4)
 * Ghidra: void FUN_00352dc4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352dc4: add x1,x20,x8 ; 00352dc8: mov x0,x22 ; 00352dcc: ret */
void exc_tramp_2dc4(void)
{
    (void)0;
    return;
}

/* FUN_00352dd0 @ 0x00352dd0   (est. exc_tramp_2dd0)
 * Ghidra: void FUN_00352dd0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352dd0: mov x8,x23 ; 00352dd4: mov x0,x25 ; 00352dd8: ret */
void exc_tramp_2dd0(void)
{
    (void)0;
    return;
}

/* FUN_00352ddc @ 0x00352ddc   (est. exc_const_0_2ddc)
 * Ghidra: undefined8 FUN_00352ddc(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352ddc: str x0,[sp, #0x8] ; 00352de0: mov x0,#0x0 ; 00352de4: ret */
word_t exc_const_0_2ddc(void)
{
    return 0;
}

/* FUN_00352de8 @ 0x00352de8   (est. exc_tramp_2de8)
 * Ghidra: void FUN_00352de8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352de8: mov x24,x20 ; 00352dec: movk x24,#0x6ae1, LSL #48 ; 00352df0: ret */
void exc_tramp_2de8(void)
{
    (void)0;
    return;
}

/* FUN_00352df4 @ 0x00352df4   (est. exc_tramp_2df4)
 * Ghidra: void FUN_00352df4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352df4: mov x21,x20 ; 00352df8: sub sp,x29,#0x50 ; 00352dfc: ret */
void exc_tramp_2df4(void)
{
    (void)0;
    return;
}

/* FUN_00352e00 @ 0x00352e00   (est. exc_restore_2e00)
 * Ghidra: void FUN_00352e00(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352e00: ldr x16,[x20] ; 00352e04: autda x16,x24 ; 00352e08: ret */
void exc_restore_2e00(void)
{
    (void)0;
    return;
}

/* FUN_00352e0c @ 0x00352e0c   (est. exc_tramp_2e0c)
 * Ghidra: void FUN_00352e0c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e0c: mov w5,#0x2 ; 00352e10: mov w7,#0x19 ; 00352e14: ret */
void exc_tramp_2e0c(void)
{
    (void)0;
    return;
}

/* FUN_00352e18 @ 0x00352e18   (est. exc_restore_2e18)
 * Ghidra: void FUN_00352e18(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352e18: ldr x8,[x9, #0x8]! ; 00352e1c: mov x0,x19 ; 00352e20: ret */
void exc_restore_2e18(void)
{
    (void)0;
    return;
}

/* FUN_00352e24 @ 0x00352e24   (est. exc_restore_2e24)
 * Ghidra: void FUN_00352e24(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352e24: ldr x8,[x9, #0x10]! ; 00352e28: mov x0,x20 ; 00352e2c: ret */
void exc_restore_2e24(void)
{
    (void)0;
    return;
}

/* FUN_00352e30 @ 0x00352e30   (est. exc_tramp_2e30)
 * Ghidra: void FUN_00352e30(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e30: mov x8,x26 ; 00352e34: mov x0,x27 ; 00352e38: ret */
void exc_tramp_2e30(void)
{
    (void)0;
    return;
}

/* FUN_00352e3c @ 0x00352e3c   (est. exc_tramp_2e3c)
 * Ghidra: void FUN_00352e3c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e3c: mov x8,x26 ; 00352e40: mov x0,x28 ; 00352e44: ret */
void exc_tramp_2e3c(void)
{
    (void)0;
    return;
}

/* FUN_00352e48 @ 0x00352e48   (est. exc_tramp_2e48)
 * Ghidra: void FUN_00352e48(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e48: mov x8,x25 ; 00352e4c: mov x0,x24 ; 00352e50: ret */
void exc_tramp_2e48(void)
{
    (void)0;
    return;
}

/* FUN_00352e54 @ 0x00352e54   (est. exc_tramp_2e54)
 * Ghidra: void FUN_00352e54(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e54: mov x19,x5 ; 00352e58: mov x20,x4 ; 00352e5c: ret */
void exc_tramp_2e54(void)
{
    (void)0;
    return;
}

/* FUN_00352e60 @ 0x00352e60   (est. exc_tramp_2e60)
 * Ghidra: void FUN_00352e60(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e60: mov x2,x20 ; 00352e64: mov x3,x25 ; 00352e68: ret */
void exc_tramp_2e60(void)
{
    (void)0;
    return;
}

/* FUN_00352e6c @ 0x00352e6c   (est. exc_tramp_2e6c)
 * Ghidra: void FUN_00352e6c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e6c: mov x3,x25 ; 00352e70: mov x4,x26 ; 00352e74: ret */
void exc_tramp_2e6c(void)
{
    (void)0;
    return;
}

/* FUN_00352e78 @ 0x00352e78   (est. exc_tramp_2e78)
 * Ghidra: void FUN_00352e78(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e78: mov x2,x22 ; 00352e7c: mov x3,x28 ; 00352e80: ret */
void exc_tramp_2e78(void)
{
    (void)0;
    return;
}

/* FUN_00352e84 @ 0x00352e84   (est. exc_restore_2e84)
 * Ghidra: void FUN_00352e84(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352e84: mov x19,x8 ; 00352e88: ldp x8,x1,[x0] ; 00352e8c: ret */
void exc_restore_2e84(void)
{
    (void)0;
    return;
}

/* FUN_00352e90 @ 0x00352e90   (est. exc_tramp_2e90)
 * Ghidra: void FUN_00352e90(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352e90: mov x16,x8 ; 00352e94: mov x17,x12 ; 00352e98: ret */
void exc_tramp_2e90(void)
{
    (void)0;
    return;
}

/* FUN_00352e9c @ 0x00352e9c   (est. exc_restore_2e9c)
 * Ghidra: void FUN_00352e9c(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352e9c: ldrb w9,[x8, #0x1] ; 00352ea0: ldrb w8,[x8, #0x2] ; 00352ea4: ret */
void exc_restore_2e9c(void)
{
    (void)0;
    return;
}

/* FUN_00352ea8 @ 0x00352ea8   (est. exc_tramp_2ea8)
 * Ghidra: void FUN_00352ea8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ea8: mov x2,x26 ; 00352eac: mov x3,x25 ; 00352eb0: ret */
void exc_tramp_2ea8(void)
{
    (void)0;
    return;
}

/* FUN_00352eb4 @ 0x00352eb4   (est. tail_00319628_2eb4)
 * Ghidra: void FUN_00352eb4(void)
 * Exception-entry tail wrapper: calls 0x00319628 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352eb4: pacibsp ; 00352eb8: str x30,[sp, #-0x10]! ; 00352ebc: bl 0x00319628 ; 00352ec0: mov x9,x0 ; 00352ec4: ldr x30,[sp], #0x10 ; 00352ec8: retab */
void tail_00319628_2eb4(void)
{
    cL4_00319628();
    return;
}

/* FUN_00352ecc @ 0x00352ecc   (est. tail_000277e8_2ecc)
 * Ghidra: void FUN_00352ecc(void)
 * Exception-entry tail wrapper: calls 0x000277e8 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352ecc: pacibsp ; 00352ed0: str x30,[sp, #-0x10]! ; 00352ed4: bl 0x000277e8 ; 00352ed8: mov x8,x0 ; 00352edc: ldr x30,[sp], #0x10 ; 00352ee0: retab */
void tail_000277e8_2ecc(void)
{
    cL4_000277e8();
    return;
}

/* FUN_00352ee4 @ 0x00352ee4   (est. tail_00027754_2ee4)
 * Ghidra: void FUN_00352ee4(void)
 * Exception-entry tail wrapper: calls 0x00027754 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352ee4: pacibsp ; 00352ee8: str x30,[sp, #-0x10]! ; 00352eec: bl 0x00027754 ; 00352ef0: mov x28,x0 ; 00352ef4: ldr x30,[sp], #0x10 ; 00352ef8: retab */
void tail_00027754_2ee4(void)
{
    cL4_00027754();
    return;
}

/* FUN_00352efc @ 0x00352efc   (est. mk128_hi_2efc)
 * Ghidra: undefined1  [16] FUN_00352efc(ulong param_1)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352efc: mov x1,x0 ; 00352f00: mov x0,#0x0 ; 00352f04: ret */
cl4_result_t mk128_hi_2efc(word_t arg0)
{
    cl4_result_t r = { .lo = 0, .hi = arg0 };
    return r;
}

/* FUN_00352f18 @ 0x00352f18   (est. pte_install_desc_2f18)
 * Ghidra: void FUN_00352f18(ulong param_1,undefined8 param_2)
 * Exception-entry tail wrapper: calls 0x0036986c (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 00352f18: movk x9,#0xd000, LSL #48 ; 00352f1c: stp x0,x9,[x26, #0x20] ; 00352f20: orr x8,x8,#-0x8000000000000000 ; 00352f24: stp x8,xzr,[x26, #0x30] ; 00352f28: mov x21,x25 ; 00352f2c: b 0x0036986c */
void pte_install_desc_2f18(word_t arg0, word_t arg1, word_t x9, word_t *x26)
{
    /* installs a 4-word page-table descriptor block at x26+0x20 and
       tail-calls the MMU commit helper (b 0x36986c).
       desc[4..7] = {arg1, (x9&0xffffffffffff)|0xd000000000000000,
                     arg0|0x8000000000000000, 0} */
    x26[4] = arg1;
    x26[5] = (x9 & 0xffffffffffff) | 0xd000000000000000;
    x26[6] = arg0 | 0x8000000000000000;
    x26[7] = 0;
    cL4_0036986c();
    return;
}

/* FUN_00352f3c @ 0x00352f3c   (est. exc_clear_mask_2f3c)
 * Ghidra: undefined1  [16] FUN_00352f3c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352f3c: bic x0,x24,x23 ; 00352f40: bic x1,x25,x23 ; 00352f44: ret */
cl4_result_t exc_clear_mask_2f3c(word_t x23, word_t x24, word_t x25)
{
    /* returns { x24 & ~x23, x25 & ~x23 } */
    cl4_result_t r = { .lo = x24 & ~x23, .hi = x25 & ~x23 };
    return r;
}

/* FUN_00352f48 @ 0x00352f48   (est. exc_restore_2f48)
 * Ghidra: void FUN_00352f48(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352f48: ldur x28,[x8, #-0x100] ; 00352f4c: mov x8,x28 ; 00352f50: ret */
void exc_restore_2f48(void)
{
    (void)0;
    return;
}

/* FUN_00352f54 @ 0x00352f54   (est. exc_const_0xff_2f54)
 * Ghidra: undefined8 FUN_00352f54(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352f54: add x4,x21,#0x28 ; 00352f58: mov w0,#0xff ; 00352f5c: ret */
word_t exc_const_0xff_2f54(void)
{
    return 0xff;
}

/* FUN_00352f60 @ 0x00352f60   (est. exc_zero_fields_2f60)
 * Ghidra: void FUN_00352f60(long param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352f60: movi v0.2D,#0x0 ; 00352f64: stur q0,[x8, #0x28] ; 00352f68: stur q0,[x8, #0x38] ; 00352f6c: ret */
void exc_zero_fields_2f60(word_t *base)
{
    /* zero 4 consecutive words at base+0x28 (stur q0,[x8,#0x28]; stur q0,[x8,#0x38]) */
    base[5] = 0; base[6] = 0; base[7] = 0; base[8] = 0;
    return;
}

/* FUN_00352f78 @ 0x00352f78   (est. exc_add_or_2f78)
 * Ghidra: int FUN_00352f78(undefined8 param_1,int param_2)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352f78: orr w8,w8,w9 ; 00352f7c: add w8,w1,w8 ; 00352f80: add w0,w8,#0x1 ; 00352f84: ret */
int exc_add_or_2f78(int arg1, word_t x8, word_t x9)
{
    /* returns arg1 + (w8 | w9) + 1 */
    return arg1 + (int)(x8 | x9) + 1;
}

/* FUN_00352f88 @ 0x00352f88   (est. exc_frame_store_2f88)
 * Ghidra: void FUN_00352f88(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352f88: sub x10,x29,#0x8 ; 00352f8c: stur x9,[x10, #-0x100] ; 00352f90: ret */
void exc_frame_store_2f88(void)
{
    (void)0;
    return;
}

/* FUN_00352fd4 @ 0x00352fd4   (est. exc_tramp_2fd4)
 * Ghidra: void FUN_00352fd4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352fd4: mov x24,x2 ; 00352fd8: mov x25,x1 ; 00352fdc: ret */
void exc_tramp_2fd4(void)
{
    (void)0;
    return;
}

/* FUN_00352fe0 @ 0x00352fe0   (est. exc_store_word_2fe0)
 * Ghidra: void FUN_00352fe0(undefined4 *param_1)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352fe0: str w9,[x8] ; 00352fe4: ret */
void exc_store_word_2fe0(unsigned int *arg0, word_t x9)
{
    *arg0 = (unsigned int)x9;
    return;
}

/* FUN_00352fe8 @ 0x00352fe8   (est. exc_restore_2fe8)
 * Ghidra: void FUN_00352fe8(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00352fe8: ldr x8,[x9] ; 00352fec: mov x0,x22 ; 00352ff0: ret */
void exc_restore_2fe8(void)
{
    (void)0;
    return;
}

/* FUN_00352ff4 @ 0x00352ff4   (est. exc_tramp_2ff4)
 * Ghidra: void FUN_00352ff4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00352ff4: mov x16,x28 ; 00352ff8: mov x17,x20 ; 00352ffc: ret */
void exc_tramp_2ff4(void)
{
    (void)0;
    return;
}

/* FUN_00353000 @ 0x00353000   (est. exc_tramp_3000)
 * Ghidra: void FUN_00353000(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00353000: mov x2,x28 ; 00353004: mov x3,x24 ; 00353008: ret */
void exc_tramp_3000(void)
{
    (void)0;
    return;
}

/* FUN_0035300c @ 0x0035300c   (est. exc_store_300c)
 * Ghidra: void FUN_0035300c(void)
 * Exception-frame store fragment: writes one or more registers into the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 0035300c: sub sp,sp,#0xa0 ; 00353010: stp x28,x27,[sp, #0x40] ; 00353014: stp x26,x25,[sp, #0x50] ; 00353018: stp x24,x23,[sp, #0x60] ; 0035301c: stp x22,x21,[sp, #0x70] ; 00353020: stp x20,x19,[sp, #0x80] ; 00353024: ret */
void exc_store_300c(void)
{
    (void)0;
    return;
}

/* FUN_00353034 @ 0x00353034   (est. exc_flag_lsb_3034)
 * Ghidra: uint FUN_00353034(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00353034: and w0,w19,#0x1 ; 00353038: sub sp,x29,#0x50 ; 0035303c: ret */
unsigned int exc_flag_lsb_3034(unsigned int w19)
{
    return w19 & 1;
}

/* FUN_00353050 @ 0x00353050   (est. exc_tramp_3050)
 * Ghidra: void FUN_00353050(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00353050: mov x1,x26 ; 00353054: mov x2,x28 ; 00353058: ret */
void exc_tramp_3050(void)
{
    (void)0;
    return;
}

/* FUN_0035305c @ 0x0035305c   (est. tail_00310a14_305c)
 * Ghidra: void FUN_0035305c(void)
 * Exception-entry tail wrapper: calls 0x00310a14 (PAC-returning) and returns.
 * Confidence: low
 * Notes: asm: 0035305c: pacibsp ; 00353060: str x30,[sp, #-0x10]! ; 00353064: bl 0x00310a14 ; 00353068: mov x8,x0 ; 0035306c: ldr x30,[sp], #0x10 ; 00353070: retab */
void tail_00310a14_305c(void)
{
    cL4_00310a14();
    return;
}

/* FUN_00353074 @ 0x00353074   (est. exc_restore_3074)
 * Ghidra: void FUN_00353074(void)
 * Exception-frame restore fragment: loads one or more saved registers from the exception/syscall frame.
 * Confidence: low
 * Notes: asm: 00353074: ldur x21,[x29, #-0xc0] ; 00353078: mov x8,x21 ; 0035307c: ret */
void exc_restore_3074(void)
{
    (void)0;
    return;
}

/* FUN_00353080 @ 0x00353080   (est. exc_tramp_3080)
 * Ghidra: void FUN_00353080(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00353080: mov x0,x16 ; 00353084: mov x1,x8 ; 00353088: ret */
void exc_tramp_3080(void)
{
    (void)0;
    return;
}

/* FUN_0035308c @ 0x0035308c   (est. exc_tramp_308c)
 * Ghidra: void FUN_0035308c(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 0035308c: mov x8,x24 ; 00353090: mov x0,x26 ; 00353094: ret */
void exc_tramp_308c(void)
{
    (void)0;
    return;
}

/* FUN_00353098 @ 0x00353098   (est. exc_tramp_3098)
 * Ghidra: void FUN_00353098(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 00353098: mov x1,x20 ; 0035309c: mov x2,x25 ; 003530a0: ret */
void exc_tramp_3098(void)
{
    (void)0;
    return;
}

/* FUN_003530a4 @ 0x003530a4   (est. exc_tramp_30a4)
 * Ghidra: void FUN_003530a4(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003530a4: mov x8,x22 ; 003530a8: mov x0,x25 ; 003530ac: ret */
void exc_tramp_30a4(void)
{
    (void)0;
    return;
}

/* FUN_003530b0 @ 0x003530b0   (est. exc_tramp_30b0)
 * Ghidra: void FUN_003530b0(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003530b0: mov x0,x27 ; 003530b4: mov x20,x19 ; 003530b8: ret */
void exc_tramp_30b0(void)
{
    (void)0;
    return;
}

/* FUN_003530bc @ 0x003530bc   (est. exc_tramp_30bc)
 * Ghidra: void FUN_003530bc(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003530bc: mov x26,x0 ; 003530c0: mov x27,x1 ; 003530c4: mov x0,x20 ; 003530c8: ret */
void exc_tramp_30bc(void)
{
    (void)0;
    return;
}

/* FUN_003530cc @ 0x003530cc   (est. exc_tramp_30cc)
 * Ghidra: void FUN_003530cc(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003530cc: mov x8,x27 ; 003530d0: mov x0,x23 ; 003530d4: ret */
void exc_tramp_30cc(void)
{
    (void)0;
    return;
}

/* FUN_003530d8 @ 0x003530d8   (est. exc_tramp_30d8)
 * Ghidra: void FUN_003530d8(void)
 * Register-only reload trampoline for the shared exception dispatch continuation (no memory effect).
 * Confidence: low
 * Notes: asm: 003530d8: mov x20,x0 ; 003530dc: mov x25,x1 ; 003530e0: mov x0,x23 ; 003530e4: ret */
void exc_tramp_30d8(void)
{
    (void)0;
    return;
}
