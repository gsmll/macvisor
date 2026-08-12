/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses. All names are estimates unless
 * a string/header matches. This slice (0x00354fd0–0x00355858) is a dense run
 * of Swift-runtime glue: protocol-witness dispatch thunks, value-return
 * witnesses, small copy/spill helpers, and constant-returning witnesses.
 */

#include <stdint.h>
#include <stddef.h>

typedef uint64_t word_t;
typedef uint64_t cptr_t;
typedef uint32_t seL4_Word;

/* 16-byte (two-word) Swift value returns. */
typedef struct { uint64_t lo, hi; } reg16;

/* ---- shared helpers (extern; bodies live in sibling slices) ---- */

/* FUN_0024c82c — helper invoked with two constant words (4,4). */
extern void FUN_0024c82c(uint64_t, uint64_t);          /* 0x0024c82c */
/* FUN_00327e08 — helper invoked with no args. */
extern void FUN_00327e08(void);                        /* 0x00327e08 */
/* FUN_0026bbd4 — helper invoked with a function-pointer word. */
extern void FUN_0026bbd4(uint64_t);                    /* 0x0026bbd4 */
/* FUN_00310a74 — helper invoked with a constant word. */
extern void FUN_00310a74(uint64_t);                    /* 0x00310a74 */
/* FUN_00002534 — object-name lookup helper. */
extern uint64_t FUN_00002534(uint64_t, uint64_t, uint64_t); /* 0x00002534 */
/* FUN_002060d4 / FUN_00205844 — function addresses stored as dispatch words. */
extern void FUN_002060d4(void);                        /* 0x002060d4 */
extern void FUN_00205844(void);                        /* 0x00205844 */

/* DAT_006adf10 — 16-byte global read as a value. */
extern reg16 _DAT_006adf10;

/* ============================================================================
 * Function bodies, in address order.
 * ========================================================================== */

/* FUN_00354fd0 @ 0x00354fd0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00354fd0(void) { return; }

/* FUN_00354fe0 @ 0x00354fe0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00354fe0(void) { return; }

/* FUN_00354ff4 @ 0x00354ff4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00354ff4(void) { return; }

/* FUN_00355008 @ 0x00355008  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355008(void) { return; }

/* FUN_00355018 @ 0x00355018  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355018(void) { return; }

/* FUN_0035503c @ 0x0035503c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035503c(void) { return; }

/* FUN_0035504c @ 0x0035504c
 * Copies the single word *src into the register-passed destination (unaff_x19).
 * Confidence: medium
 * Notes: destination word is register-passed (unaff_x19). */
void FUN_0035504c(uint64_t *src, uint64_t *dst /* x19 */)
{
    *dst = *src;
}

/* FUN_0035505c @ 0x0035505c
 * Loads and returns the word at the caller's stack frame - 0x130.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_0035505c(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)(sp - 0x130);
}

/* FUN_00355068 @ 0x00355068  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355068(void) { return; }

/* FUN_00355074 @ 0x00355074  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355074(void) { return; }

/* FUN_00355080 @ 0x00355080  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355080(void) { return; }

/* FUN_00355090 @ 0x00355090
 * Copies the word at src+0x20 and the dword at src+0x28 into the same offsets
 * of dst (a partial struct copy).
 * Confidence: medium */
void FUN_00355090(uint64_t *dst, uint64_t *src)
{
    *(uint64_t *)((char *)dst + 0x20) = *(uint64_t *)((char *)src + 0x20);
    *(uint32_t *)((char *)dst + 0x28) = *(uint32_t *)((char *)src + 0x28);
}

/* FUN_003550a4 @ 0x003550a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003550a4(void) { return; }

/* FUN_003550cc @ 0x003550cc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003550cc(void) { return; }

/* FUN_003550e0 @ 0x003550e0
 * Returns the 16-byte pair { lo & ~mask, hi & ~mask } where the operands are
 * register-passed (unaff_x24/x23/x20).
 * Confidence: medium
 * Notes: operands are register-passed (unaff_x24/x23/x20). */
reg16 FUN_003550e0(uint64_t lo /* x24 */, uint64_t mask /* x23 */, uint64_t hi /* x20 */)
{
    return (reg16){ .lo = lo & ~mask, .hi = hi & ~mask };
}

/* FUN_003550f0 @ 0x003550f0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003550f0(void) { return; }

/* FUN_00355100 @ 0x00355100
 * Loads and returns the word at address param_1 - 0x100.
 * Confidence: medium
 * Notes: base is the passed argument. */
uint64_t FUN_00355100(uint64_t *base)
{
    return *(uint64_t *)((char *)base - 0x100);
}

/* FUN_0035510c @ 0x0035510c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035510c(void) { return; }

/* FUN_00355118 @ 0x00355118
 * Copies the two words of *src into *dst (and dst[1]), then returns dst[3].
 * Confidence: medium */
uint64_t FUN_00355118(uint64_t *dst, uint64_t *src)
{
    uint64_t w = *src;
    dst[1] = src[1];
    *dst = w;
    return dst[3];
}

/* FUN_0035512c @ 0x0035512c
 * Loads and returns the word at the caller's stack frame - 0x60.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_0035512c(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)(sp - 0x60);
}

/* FUN_00355150 @ 0x00355150  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355150(void) { return; }

/* FUN_00355160 @ 0x00355160  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355160(void) { return; }

/* FUN_0035516c @ 0x0035516c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035516c(void) { return; }

/* FUN_0035517c @ 0x0035517c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035517c(void) { return; }

/* FUN_00355190 @ 0x00355190
 * Calls the shared helper FUN_0024c82c with the constant words (4,4).
 * Confidence: medium
 * Notes: FUN_0024c82c shared helper. */
void FUN_00355190(void)
{
    FUN_0024c82c(4, 4);
}

/* FUN_003551a0 @ 0x003551a0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003551a0(void) { return; }

/* FUN_003551b0 @ 0x003551b0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003551b0(void) { return; }

/* FUN_003551c4 @ 0x003551c4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003551c4(void) { return; }

/* FUN_003551d8 @ 0x003551d8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003551d8(void) { return; }

/* FUN_003551e8 @ 0x003551e8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003551e8(void) { return; }

/* FUN_003551f8 @ 0x003551f8
 * Stores four caller-passed stack words (stack offsets 8..0x20) into the four
 * words at the register-passed destination (unaff_x19).
 * Confidence: medium
 * Notes: destination is register-passed (unaff_x19). */
void FUN_003551f8(uint64_t *dst /* x19 */, uint64_t w0, uint64_t w1,
                  uint64_t w2, uint64_t w3)
{
    dst[0] = w0;
    dst[1] = w1;
    dst[2] = w2;
    dst[3] = w3;
}

/* FUN_00355208 @ 0x00355208  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355208(void) { return; }

/* FUN_00355224 @ 0x00355224  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355224(void) { return; }

/* FUN_00355230 @ 0x00355230
 * Returns the 16-byte value { [sp-0x70], [sp-0x88] } from the caller's frame.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
reg16 FUN_00355230(uint64_t *sp /* x29 */)
{
    return (reg16){ .lo = *(uint64_t *)(sp - 0x70), .hi = *(uint64_t *)(sp - 0x88) };
}

/* FUN_00355244 @ 0x00355244
 * Calls the shared helper FUN_00327e08() with no args.
 * Confidence: medium
 * Notes: FUN_00327e08 shared helper. */
void FUN_00355244(void)
{
    FUN_00327e08();
}

/* FUN_0035525c @ 0x0035525c  — returns constant 0. */
uint64_t FUN_0035525c(void) { return 0; }

/* FUN_00355270 @ 0x00355270
 * Passes the address of FUN_002060d4 (stored to a stack slot) into the shared
 * helper FUN_0026bbd4, then returns.
 * Confidence: medium
 * Notes: helper FUN_0026bbd4; stored word is the address FUN_002060d4. */
void FUN_00355270(void)
{
    FUN_0026bbd4((uint64_t)(uintptr_t)&FUN_002060d4);
}

/* FUN_00355288 @ 0x00355288  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355288(void) { return; }

/* FUN_003552a0 @ 0x003552a0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003552a0(void) { return; }

/* FUN_003552ac @ 0x003552ac
 * Stores two register-passed words (unaff_x25/x26) into the caller's stack
 * frame at -0x78 and -0x70.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_003552ac(uint64_t *sp /* x29 */, uint64_t a /* x25 */, uint64_t b /* x26 */)
{
    *(uint64_t *)(sp - 0x78) = a;
    *(uint64_t *)(sp - 0x70) = b;
}

/* FUN_003552bc @ 0x003552bc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003552bc(void) { return; }

/* FUN_003552d0 @ 0x003552d0
 * Loads and returns the 16 bytes at the caller's stack frame + 0x10.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
reg16 FUN_003552d0(uint64_t *sp /* x29 */)
{
    return *(reg16 *)(sp + 0x10);
}

/* FUN_003552e0 @ 0x003552e0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003552e0(void) { return; }

/* FUN_003552f0 @ 0x003552f0
 * Returns the 16-byte global value _DAT_006adf10 unchanged.
 * Confidence: medium
 * Notes: global _DAT_006adf10 (16-byte read). */
reg16 FUN_003552f0(void)
{
    return _DAT_006adf10;
}

/* FUN_00355300 @ 0x00355300  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355300(void) { return; }

/* FUN_00355314 @ 0x00355314  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355314(void) { return; }

/* FUN_00355324 @ 0x00355324  — returns constant 0xff. */
uint64_t FUN_00355324(void) { return 0xff; }

/* FUN_00355334 @ 0x00355334
 * Returns the caller's stack address + 8 (&stack0x00000008).
 * Confidence: medium
 * Notes: returns address of stack offset 8. */
uint64_t FUN_00355334(uint64_t *sp /* x29 */)
{
    return (uint64_t)(uintptr_t)(sp + 0x8);
}

/* FUN_00355340 @ 0x00355340  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355340(void) { return; }

/* FUN_00355354 @ 0x00355354
 * Returns the 16-byte value { 1 << (byte[param+0x20] & 0x3f), word32[param+0x24] }.
 * Confidence: medium
 * Notes: bit-shift from the byte at +0x20; low word from the dword at +0x24. */
reg16 FUN_00355354(uint64_t *param)
{
    uint64_t lo = 1ull << (*(uint8_t *)((char *)param + 0x20) & 0x3f);
    uint64_t hi = *(uint32_t *)((char *)param + 0x24);
    return (reg16){ .lo = lo, .hi = hi };
}

/* FUN_00355374 @ 0x00355374
 * Stores two register-passed words (unaff_x20/x22) into the caller's stack
 * frame at -0x78 and -0x70.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_00355374(uint64_t *sp /* x29 */, uint64_t a /* x20 */, uint64_t b /* x22 */)
{
    *(uint64_t *)(sp - 0x78) = a;
    *(uint64_t *)(sp - 0x70) = b;
}

/* FUN_00355384 @ 0x00355384
 * Stores two register-passed words (unaff_x19/x20) into the caller's stack
 * frame at -0x78 and -0x70.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_00355384(uint64_t *sp /* x29 */, uint64_t a /* x19 */, uint64_t b /* x20 */)
{
    *(uint64_t *)(sp - 0x78) = a;
    *(uint64_t *)(sp - 0x70) = b;
}

/* FUN_00355394 @ 0x00355394  — returns constant 0xff. */
uint64_t FUN_00355394(void) { return 0xff; }

/* FUN_003553a8 @ 0x003553a8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003553a8(void) { return; }

/* FUN_003553b8 @ 0x003553b8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003553b8(void) { return; }

/* FUN_003553cc @ 0x003553cc
 * Stores the passed word into the caller's stack frame at -0x118.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_003553cc(uint64_t *sp /* x29 */, uint64_t value)
{
    *(uint64_t *)(sp - 0x118) = value;
}

/* FUN_003553d8 @ 0x003553d8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003553d8(void) { return; }

/* FUN_003553e4 @ 0x003553e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003553e4(void) { return; }

/* FUN_003553f4 @ 0x003553f4
 * Returns the 16-byte value { 0x7fffffffffffffff, 0 } (zero-extended sign cap).
 * Confidence: medium
 * Notes: ZEXT816(0x7fffffffffffffff). */
reg16 FUN_003553f4(void)
{
    return (reg16){ .lo = 0x7fffffffffffffffull, .hi = 0 };
}

/* FUN_00355404 @ 0x00355404  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355404(void) { return; }

/* FUN_00355418 @ 0x00355418  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355418(void) { return; }

/* FUN_00355424 @ 0x00355424  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355424(void) { return; }

/* FUN_00355430 @ 0x00355430  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355430(void) { return; }

/* FUN_0035543c @ 0x0035543c
 * Returns the caller's stack address + 8 (&stack0x00000008).
 * Confidence: medium
 * Notes: returns address of stack offset 8. */
uint64_t FUN_0035543c(uint64_t *sp /* x29 */)
{
    return (uint64_t)(uintptr_t)(sp + 0x8);
}

/* FUN_00355448 @ 0x00355448
 * Returns the caller's stack address + 8 (&stack0x00000008).
 * Confidence: medium
 * Notes: returns address of stack offset 8. */
uint64_t FUN_00355448(uint64_t *sp /* x29 */)
{
    return (uint64_t)(uintptr_t)(sp + 0x8);
}

/* FUN_00355458 @ 0x00355458  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355458(void) { return; }

/* FUN_00355464 @ 0x00355464  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355464(void) { return; }

/* FUN_00355474 @ 0x00355474
 * Stores the constant 0xffffffffffffff80 (-0x80) into a caller stack slot, then
 * calls the shared helper FUN_00310a74 with it.
 * Confidence: medium
 * Notes: FUN_00310a74 shared helper; constant -0x80. */
void FUN_00355474(void)
{
    FUN_00310a74(0xffffffffffffff80ull);
}

/* FUN_00355484 @ 0x00355484
 * Passes the address of FUN_00205844 (stored to a stack slot) into the shared
 * helper FUN_0026bbd4, then returns.
 * Confidence: medium
 * Notes: helper FUN_0026bbd4; stored word is the address FUN_00205844. */
void FUN_00355484(void)
{
    FUN_0026bbd4((uint64_t)(uintptr_t)&FUN_00205844);
}

/* FUN_0035549c @ 0x0035549c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035549c(void) { return; }

/* FUN_003554b0 @ 0x003554b0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003554b0(void) { return; }

/* FUN_003554c4 @ 0x003554c4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003554c4(void) { return; }

/* FUN_003554d4 @ 0x003554d4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003554d4(void) { return; }

/* FUN_003554e0 @ 0x003554e0
 * Stores four passed words into the four words at the register-passed
 * destination (unaff_x19).
 * Confidence: medium
 * Notes: destination is register-passed (unaff_x19). */
void FUN_003554e0(uint64_t *dst /* x19 */, uint64_t w0, uint64_t w1,
                  uint64_t w2, uint64_t w3)
{
    dst[0] = w0;
    dst[1] = w1;
    dst[2] = w2;
    dst[3] = w3;
}

/* FUN_003554ec @ 0x003554ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003554ec(void) { return; }

/* FUN_00355528 @ 0x00355528
 * Returns the 16-byte pair { &stack0x18, &stack0x10 } — two caller stack
 * addresses.
 * Confidence: medium
 * Notes: returns addresses of stack offsets 0x18 and 0x10. */
reg16 FUN_00355528(uint64_t *sp /* x29 */)
{
    return (reg16){ .lo = (uint64_t)(uintptr_t)(sp + 0x18),
                    .hi = (uint64_t)(uintptr_t)(sp + 0x10) };
}

/* FUN_00355538 @ 0x00355538  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355538(void) { return; }

/* FUN_00355544 @ 0x00355544  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355544(void) { return; }

/* FUN_00355550 @ 0x00355550  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355550(void) { return; }

/* FUN_00355560 @ 0x00355560  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355560(void) { return; }

/* FUN_0035556c @ 0x0035556c
 * Copies the single word *src into the register-passed destination (unaff_x19).
 * Confidence: medium
 * Notes: destination word is register-passed (unaff_x19). */
void FUN_0035556c(uint64_t *src, uint64_t *dst /* x19 */)
{
    *dst = *src;
}

/* FUN_00355578 @ 0x00355578  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355578(void) { return; }

/* FUN_00355594 @ 0x00355594  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355594(void) { return; }

/* FUN_003555a0 @ 0x003555a0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003555a0(void) { return; }

/* FUN_003555b4 @ 0x003555b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003555b4(void) { return; }

/* FUN_003555dc @ 0x003555dc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003555dc(void) { return; }

/* FUN_00355604 @ 0x00355604
 * Loads and returns the word at the caller's stack frame - 0x58.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00355604(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)(sp - 0x58);
}

/* FUN_00355610 @ 0x00355610  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355610(void) { return; }

/* FUN_00355624 @ 0x00355624  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355624(void) { return; }

/* FUN_00355634 @ 0x00355634
 * Returns the caller's stack address - 0x78.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00355634(uint64_t *sp /* x29 */)
{
    return (uint64_t)(uintptr_t)(sp - 0x78);
}

/* FUN_00355640 @ 0x00355640  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355640(void) { return; }

/* FUN_0035564c @ 0x0035564c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035564c(void) { return; }

/* FUN_00355660 @ 0x00355660  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355660(void) { return; }

/* FUN_00355674 @ 0x00355674
 * Zeroes five words in the caller's stack frame at offsets -0x80..-0xa0.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_00355674(uint64_t *sp /* x29 */)
{
    *(uint64_t *)(sp - 0x80) = 0;
    *(uint64_t *)(sp - 0x88) = 0;
    *(uint64_t *)(sp - 0x90) = 0;
    *(uint64_t *)(sp - 0x98) = 0;
    *(uint64_t *)(sp - 0xa0) = 0;
}

/* FUN_00355684 @ 0x00355684  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355684(void) { return; }

/* FUN_00355694 @ 0x00355694  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355694(void) { return; }

/* FUN_003556a4 @ 0x003556a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003556a4(void) { return; }

/* FUN_003556b0 @ 0x003556b0
 * Calls the object-name lookup helper FUN_00002534 with the computed value
 * (1 << (param & 0x3f)) + 0x3f, plus two register-passed words (in_x4/x5).
 * Confidence: medium
 * Notes: FUN_00002534 shared helper; bit-shift from the char parameter. */
void FUN_003556b0(char param, uint64_t arg_x4, uint64_t arg_x5)
{
    FUN_00002534((1ull << ((unsigned long)param & 0x3fU)) + 0x3f, arg_x4, arg_x5);
}

/* FUN_003556e0 @ 0x003556e0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003556e0(void) { return; }

/* FUN_003556f4 @ 0x003556f4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003556f4(void) { return; }

/* FUN_00355704 @ 0x00355704
 * Returns the caller's stack address - 0x50.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00355704(uint64_t *sp /* x29 */)
{
    return (uint64_t)(uintptr_t)(sp - 0x50);
}

/* FUN_00355720 @ 0x00355720
 * Stores param_3 into the caller's stack slot -0x50, and the low 56 bits of
 * param_4 into the adjacent slot -0x48.
 * Confidence: medium
 * Notes: frame base is unaff_x29; low-56-bit mask on param_4. */
void FUN_00355720(uint64_t *sp /* x29 */, uint64_t p1, uint64_t p2,
                  uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2;
    *(uint64_t *)(sp - 0x50) = p3;
    *(uint64_t *)(sp - 0x48) = p4 & 0xffffffffffffffull;
}

/* FUN_00355730 @ 0x00355730  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355730(void) { return; }

/* FUN_00355740 @ 0x00355740  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355740(void) { return; }

/* FUN_00355754 @ 0x00355754  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355754(void) { return; }

/* FUN_00355760 @ 0x00355760  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355760(void) { return; }

/* FUN_00355770 @ 0x00355770  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355770(void) { return; }

/* FUN_00355780 @ 0x00355780  — returns constant 0xff. */
uint64_t FUN_00355780(void) { return 0xff; }

/* FUN_0035578c @ 0x0035578c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035578c(void) { return; }

/* FUN_003557a8 @ 0x003557a8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003557a8(void) { return; }

/* FUN_003557b4 @ 0x003557b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003557b4(void) { return; }

/* FUN_003557c8 @ 0x003557c8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003557c8(void) { return; }

/* FUN_003557d8 @ 0x003557d8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003557d8(void) { return; }

/* FUN_003557ec @ 0x003557ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003557ec(void) { return; }

/* FUN_00355800 @ 0x00355800  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355800(void) { return; }

/* FUN_00355814 @ 0x00355814  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355814(void) { return; }

/* FUN_00355824 @ 0x00355824
 * Copies a single byte from *(base + off_src) to *(base + off_dst), where both
 * offsets are register-passed (unaff_x21 = src, unaff_x22 = dst).
 * Confidence: medium
 * Notes: register-passed offsets (unaff_x21/x22). */
void FUN_00355824(char *base, uint64_t off_src /* x21 */, uint64_t off_dst /* x22 */)
{
    base[off_dst] = base[off_src];
}

/* FUN_0035583c @ 0x0035583c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035583c(void) { return; }

/* FUN_00355848 @ 0x00355848  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355848(void) { return; }

/* FUN_00355858 @ 0x00355858  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355858(void) { return; }
