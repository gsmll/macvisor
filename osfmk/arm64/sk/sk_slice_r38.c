/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R38: 0x4ac0a4-0x4ac830 (120 functions). This is a cluster of small
 * leaf utility/accessor/dispatch stubs: struct field copy / field swap with
 * refcount retain-or-release of the displaced value, struct zero/init,
 * register-shuffle thunks that tail-call shared cL4 runtime helpers
 * (refcount retain FUN_0036b270, refcount release FUN_0036b118, memcpy
 * FUN_00117cc4, metadata-chain FUN_003a25d0), mask/compare helpers, and a
 * few panic shims. Many are entered with their working context preloaded in
 * callee-saved registers (x19-x28) and handed off via scratch registers, so
 * the Ghidra decompiler collapses them to bare `return;` — the transcriptions
 * below use the DISASSEMBLY as ground truth. All names are estimates.
 *
 * Calling-convention note: these are non-standard-ABI fragments. A function
 * whose body only writes fields through x19/x20 or computes into x8/x9 is
 * modelled with explicit parameters named after the register it consumes;
 * the register name is kept in the inline comment. Tail calls (`b target`)
 * are rendered as `return target(...)` with the callee address commented.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* Common mask: top nibble (bits 60-63) plus bit 2 cleared. */
#define R38_OBJ_MASK   0x0ffffffffffffffbUL
#define R38_SIGN_BIT   0x8000000000000000UL
#define R38_TAG_MASK   0x2000000000000000UL

/* Out-of-slice helper declarations (bodies owned by the range workers that
 * decompiled them). Signatures reflect observed register use. */
extern word_t cL4_ref_retain(word_t obj);                 /* FUN_0036b270 */
extern void   cL4_ref_release(word_t obj);                /* FUN_0036b118 */
extern void  *cL4_memcpy_v(word_t dst, word_t src, word_t n);  /* FUN_00117cc4 */
extern word_t cL4_metadata_chain(word_t w);               /* FUN_003a25d0 */
/* Complex message/notification writer — FUN_00365b6c (5 reg args). */
extern word_t cL4_365b6c(word_t a, word_t b, word_t c, word_t d, word_t e);
/* Boot/init tail target — thunk_FUN_002b74c0 @ 0x00346718. */
extern void   cL4_346718(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f);
/* Dispatch tail target @ 0x00347480. */
extern void   cL4_347480(word_t a, word_t b);
/* Panic shim (thunk_FUN_002acbb8) @ 0x0044ca08 — (w0 code, x1 value). */
extern void   cL4_44ca08(word_t code, word_t value) __attribute__((noreturn));
/* Tail target @ 0x00455ac8 — (x0, x2 both = class/addr). */
extern void   cL4_455ac8(word_t a, word_t b, word_t c);
/* Tail target @ 0x0049df18 (no args). */
extern word_t cL4_49df18(void);
/* Tail target @ 0x0049e2d4 (1 reg arg). */
extern word_t cL4_49e2d4(word_t p);
/* Tail target @ 0x002a4ab4 — (w0 code, x20 frame). */
extern void   cL4_2a4ab4(word_t code, word_t frame);
/* Tail target @ 0x0048273c — 8-reg-arg reader. */
extern void   cL4_48273c(word_t a, word_t b, word_t c, word_t d, word_t e,
                         word_t f, word_t g, word_t h);
/* Tail targets @ 0x004a3918 / 0x004a3940 / 0x004a4b14. */
extern void   cL4_4a3918(word_t p);
extern void   cL4_4a3940(word_t a, word_t b);
extern void   cL4_4a4b14(word_t a, word_t b, word_t c);
/* Tail targets @ 0x00478a98 / 0x00488828 / 0x003722e4. */
extern void   cL4_478a98(word_t a, word_t b);
extern void   cL4_488828(word_t a, word_t b);
extern void   cL4_3722e4(word_t a, word_t b, word_t c, word_t d);


/* FUN_004ac27c @ 0x004ac27c   (est. sk_r38_glob_tuple_657778)
 * Register-setup: returns x3 = &0x657778 (a global/class descriptor) and
 * w0=0, w1=1, w2=1 (a (0,1,1) selector tuple).
 * Confidence: medium
 * Notes: `adrp x3,0x657000 ; add x3,x3,#0x778 ; mov w0,#0 ; mov w1,#1 ; mov w2,#1`. */
void sk_r38_glob_tuple_657778(void)
{
    /* adrp x3,0x657000 ; add x3,x3,#0x778 */
    word_t x3 = 0x657778;
    word_t w0 = 0, w1 = 1, w2 = 1;
    (void)x3; (void)w0; (void)w1; (void)w2;
}

/* FUN_004ac294 @ 0x004ac294   (est. sk_r38_tag_mask_ptr_b)
 * Clears the top nibble (bits 60-63) and bit 2 of the value in x25 — a
 * pointer-tag mask leaving the result in x8.
 * Confidence: medium
 * Notes: `and x8,x25,#0xfffffffffffffff ; and x8,x8,#-0x5`. */
word_t sk_r38_tag_mask_ptr_b(word_t x25)
{
    return x25 & R38_OBJ_MASK;
}

/* FUN_004ac2a0 @ 0x004ac2a0   (est. sk_r38_load_head_byte_20)
 * Loads [x0] into x8 and the byte at [x0+0x20] into w16 — a header word plus
 * a flag byte returned as a pair.
 * Confidence: medium
 * Notes: `ldr x8,[x0] ; ldrb w16,[x0,#0x20]`. */
cL4_w16_t sk_r38_load_head_byte_20(const void *p)
{
    cL4_w16_t r;
    r.lo = *(const word_t *)p;                 /* ldr x8,[x0] */
    r.hi = *(const byte *)((const byte *)p + 0x20);  /* ldrb w16,[x0,#0x20] */
    return r;
}

/* FUN_004ac2ac @ 0x004ac2ac   (est. sk_r38_sp_sub)
 * Register-setup fragment: x23 = x9 - x8 and stack pointer sp = x23.
 * Confidence: medium
 * Notes: `sub x23,x9,x8 ; mov sp,x23` — frame allocation. */
void sk_r38_sp_sub(word_t x9, word_t x8)
{
    /* sub x23,x9,x8 ; mov sp,x23 */
    word_t sp = x9 - x8;
    (void)sp;
}

/* FUN_004ac2b8 @ 0x004ac2b8   (est. sk_r38_sp_set)
 * Register-setup fragment: stores x8 to [x29-0xc8] and sets sp = x8.
 * Confidence: medium
 * Notes: `stur x8,[x29,#-0xc8] ; mov sp,x8` — frame/free-list pointer install. */
void sk_r38_sp_set(word_t x29, word_t x8)
{
    *(word_t *)(x29 - 0xc8) = x8;
    /* mov sp,x8 */
    (void)0;
}

/* FUN_004ac2c4 @ 0x004ac2c4   (est. sk_r38_setup_sp8)
 * Register-setup fragment: x20 = sp + 0x8, x1 = x19.
 * Confidence: medium
 * Notes: `add x20,sp,#0x8 ; mov x1,x19`. */
void sk_r38_setup_sp8(word_t sp, word_t x19)
{
    word_t x20 = sp + 0x8, x1 = x19;
    (void)x20; (void)x1;
}

/* FUN_004ac2d0 @ 0x004ac2d0   (est. sk_r38_ret_x20)
 * Register-setup fragment: x25 = x0, returns x20 in x0.
 * Confidence: medium
 * Notes: `mov x25,x0 ; mov x0,x20`. */
word_t sk_r38_ret_x20(word_t x0, word_t x20)
{
    /* mov x25,x0 */
    word_t x25 = x0; (void)x25;
    /* mov x0,x20 */
    return x20;
}

/* FUN_004ac2dc @ 0x004ac2dc   (est. sk_r38_glob_683328)
 * Returns the address 0x683328 (a global data/string descriptor) in x0, also
 * setting x20 = sp+0x328 and x1 = x22.
 * Confidence: medium
 * Notes: `adrp x0,0x683000 ; add x0,x0,#0x328 ; add x20,sp,#0x328 ; mov x1,x22`. */
word_t sk_r38_glob_683328(word_t sp, word_t x22)
{
    word_t x0 = 0x683328;
    word_t x20 = sp + 0x328, x1 = x22;
    (void)x20; (void)x1;
    return x0;
}

/* FUN_004ac2f4 @ 0x004ac2f4   (est. sk_r38_slot_store_bump)
 * Increments the counter x28, stores x26 into [x27+0x10], writes x25 into
 * [x27 + (x24<<3) + 0x20] (indexed slot), and compares x22 against x28.
 * Confidence: medium
 * Notes: slot-table append with index; `add x8,x27,x24,LSL#3 ; str x25,[x8,#0x20]`. */
long sk_r38_slot_store_bump(word_t x27, word_t x24, word_t x25, word_t x26,
                            word_t x28, word_t x22)
{
    /* add x28,x28,#1 */
    word_t newc = x28 + 1;
    /* str x26,[x27,#0x10] */
    *(word_t *)((byte *)x27 + 0x10) = x26;
    /* add x8,x27,x24,LSL#3 ; str x25,[x8,#0x20] */
    *(word_t *)((byte *)x27 + (x24 << 3) + 0x20) = x25;
    /* cmp x22,x28 */
    return (long)x22 - (long)newc;
}

/* FUN_004ac30c @ 0x004ac30c   (est. sk_r38_setup_x4x1)
 * Register-setup fragment: x4 = x2, x1 = x0.
 * Confidence: medium
 * Notes: `mov x4,x2 ; mov x1,x0`. */
void sk_r38_setup_x4x1(word_t x2, word_t x0)
{
    word_t x4 = x2, x1 = x0;
    (void)x4; (void)x1;
}

/* FUN_004ac318 @ 0x004ac318   (est. sk_r38_setup_x0_x21)
 * Register-setup fragment: x0 = x21, w1 = 0.
 * Confidence: medium
 * Notes: `mov x0,x21 ; mov w1,#0`. */
void sk_r38_setup_x0_x21(word_t x21)
{
    word_t x0 = x21, w1 = 0;
    (void)x0; (void)w1;
}

/* FUN_004ac324 @ 0x004ac324   (est. sk_r38_init_field_10_28)
 * Initialises a small object at x0: field +0x10 = x19, and zeroes the 16-byte
 * regions at +0x18 and +0x28.
 * Confidence: medium
 * Notes: `mov x24,x0 ; str x19,[x0,#0x10] ; movi v0.2D,#0 ; stur q0,[x0,#0x18] ; stur q0,[x0,#0x28]`. */
void sk_r38_init_field_10_28(void *obj, word_t x19)
{
    *(word_t *)((byte *)obj + 0x10) = x19;
    __builtin_memset((byte *)obj + 0x18, 0, 16);
    __builtin_memset((byte *)obj + 0x28, 0, 16);
}

/* FUN_004ac33c @ 0x004ac33c   (est. sk_r38_setup_x25x26)
 * Register-setup fragment: x25 = x1, x26 = x2.
 * Confidence: medium
 * Notes: `mov x25,x1 ; mov x26,x2`. */
void sk_r38_setup_x25x26(word_t x1, word_t x2)
{
    word_t x25 = x1, x26 = x2;
    (void)x25; (void)x26;
}

/* FUN_004ac348 @ 0x004ac348   (est. sk_r38_pair_signbit_14)
 * Returns a pair: x0 = 0xd000000000000014 (a tagged kind/error code) and
 * x1 = ((x8 - 0x20) | 0x8000000000000000) (a signed pointer tag), with x20=sp.
 * Confidence: medium
 * Notes: `sub x8,x8,#0x20 ; orr x1,x8,#-0x8000000000000000 ; mov x20,sp ; mov x0,#0x14 ; movk x0,#0xd000,LSL#48`. */
cL4_w16_t sk_r38_pair_signbit_14(word_t x8, word_t sp)
{
    cL4_w16_t r;
    r.lo = 0xd000000000000014UL;
    r.hi = ((x8 - 0x20) | R38_SIGN_BIT);
    /* mov x20,sp */
    (void)sp;
    return r;
}

/* FUN_004ac360 @ 0x004ac360   (est. sk_r38_setup_copy_160)
 * Register-setup fragment for a 0x160-byte memcpy: x1 = x23, w2 = 0x160.
 * Confidence: medium
 * Notes: `mov x1,x23 ; mov w2,#0x160`. */
void sk_r38_setup_copy_160(word_t x23)
{
    word_t x1 = x23, w2 = 0x160;
    (void)x1; (void)w2;
}

/* FUN_004ac36c @ 0x004ac36c   (est. sk_r38_sp_set_b)
 * Register-setup fragment: stores x8 to [x29-0xa0] and sets sp = x8.
 * Confidence: medium
 * Notes: `stur x8,[x29,#-0xa0] ; mov sp,x8`. */
void sk_r38_sp_set_b(word_t x29, word_t x8)
{
    *(word_t *)(x29 - 0xa0) = x8;
    (void)0;
}

/* FUN_004ac378 @ 0x004ac378   (est. sk_r38_load_field_10)
 * Register-setup fragment: x19 = x0, x2 = [x2 + 0x10].
 * Confidence: medium
 * Notes: `mov x19,x0 ; ldr x2,[x2,#0x10]`. */
void sk_r38_load_field_10(word_t x0, word_t x2)
{
    word_t x19 = x0; (void)x19;
    word_t x2v = *(const word_t *)((byte *)x2 + 0x10);
    (void)x2v;
}

/* FUN_004ac384 @ 0x004ac384   (est. sk_r38_load_field_18)
 * Register-setup fragment: x19 = x0, x2 = [x2 + 0x18].
 * Confidence: medium
 * Notes: `mov x19,x0 ; ldr x2,[x2,#0x18]`. */
void sk_r38_load_field_18(word_t x0, word_t x2)
{
    word_t x19 = x0; (void)x19;
    word_t x2v = *(const word_t *)((byte *)x2 + 0x18);
    (void)x2v;
}

/* FUN_004ac390 @ 0x004ac390   (est. sk_r38_copy_fields_08_10)
 * Copies 8-byte fields at +0x8 and +0x10 from source (x20) to destination
 * (x19) and loads [x20+0x30] into x2.
 * Confidence: medium
 * Notes: `ldr/str [x20->x19,#0x8],[#0x10] ; ldr x2,[x20,#0x30]`. */
void sk_r38_copy_fields_08_10(void *dst, const void *src)
{
    *(word_t *)((byte *)dst + 0x08) = *(const word_t *)((const byte *)src + 0x08);
    *(word_t *)((byte *)dst + 0x10) = *(const word_t *)((const byte *)src + 0x10);
    /* ldr x2,[x20,#0x30] */
    word_t x2 = *(const word_t *)((const byte *)src + 0x30);
    (void)x2;
}

/* FUN_004ac3a8 @ 0x004ac3a8   (est. sk_r38_copy_48)
 * Copies 48 bytes: [x8] = 32 bytes from [x20+0x8] and [x8+0x20] = 16 bytes
 * from [x20+0x28].
 * Confidence: medium
 * Notes: `ldur q0,q1,[x20,#0x8]; stp q0,q1,[x8]; ldur q0,[x20,#0x28]; str q0,[x8,#0x20]`. */
void sk_r38_copy_48(void *dst, const void *src)
{
    __builtin_memcpy((byte *)dst, (const byte *)src + 0x8, 32);
    __builtin_memcpy((byte *)dst + 0x20, (const byte *)src + 0x28, 16);
}

/* FUN_004ac3c0 @ 0x004ac3c0   (est. sk_r38_copy_head_cmp_30_b)
 * Copies the first 8 bytes of *x1 into *x0, then compares [x1+0x30] against 1.
 * Confidence: medium
 * Notes: `ldr x9,[x1]; mov x8,x0; str x9,[x8],#8; ldr x2,[x1,#0x30]; cmp x2,#1`. */
long sk_r38_copy_head_cmp_30_b(word_t *dst, const word_t *src)
{
    *dst = *src;
    return (long)*(const word_t *)((const byte *)src + 0x30) - 1;
}

/* FUN_004ac3d8 @ 0x004ac3d8   (est. sk_r38_retain_sp_20)
 * Loads the 64-bit value at [sp+0x20] into x0 and tail-calls the refcount
 * retain helper.
 * Confidence: medium
 * Notes: `ldr q0,[sp,#0x20]; fmov x0,d0; b 0x0036b270` — retain. */
word_t sk_r38_retain_sp_20(word_t sp)
{
    /* fmov x0, d0 from [sp,#0x20] */
    word_t obj;
    __builtin_memcpy(&obj, (const void *)(sp + 0x20), 8);
    /* b 0x0036b270 */
    return cL4_ref_retain(obj);
}

/* FUN_004ac3e4 @ 0x004ac3e4   (est. sk_r38_memcpy_160)
 * Tail-calls cL4_memcpy_v(x0, x19, 0x160) — copies 0x160 bytes from the
 * object in x19 to the destination in x0.
 * Confidence: medium
 * Notes: `mov x1,x19 ; mov w2,#0x160 ; b 0x00117cc4`. */
void *sk_r38_memcpy_160(void *dst, word_t x19)
{
    return cL4_memcpy_v((word_t)dst, x19, 0x160);
}

/* FUN_004ac3f0 @ 0x004ac3f0   (est. sk_r38_panic_5b)
 * Panic shim: tail-calls the panic routine with code 0x5b and value
 * 0xe100000000000000.
 * Confidence: medium
 * Notes: `mov w0,#0x5b ; mov x1,#-0x1f00000000000000 ; b 0x0044ca08`. */
void sk_r38_panic_5b(void)
{
    cL4_44ca08(0x5b, 0xe100000000000000UL);
}

/* FUN_004ac3fc @ 0x004ac3fc   (est. sk_r38_swap58_release)
 * Copies the 16-byte field at +0x58 from source (x20) to destination (x19),
 * loads the old [x19+0x60], and tail-calls the refcount release on it.
 * Confidence: medium
 * Notes: `ldr x0,[x19,#0x60]; ldur q0,[x20,#0x58]; stur q0,[x19,#0x58]; b 0x0036b118`. */
void sk_r38_swap58_release(void *dst, const void *src)
{
    /* old = [x19,#0x60] (x0) */
    word_t old = *(word_t *)((byte *)dst + 0x60);
    __builtin_memcpy((byte *)dst + 0x58, (const byte *)src + 0x58, 16);
    /* b 0x0036b118 */
    cL4_ref_release(old);
}

/* FUN_004ac40c @ 0x004ac40c   (est. sk_r38_swap38_release)
 * Copies the 16-byte field at +0x38 from source (x20) to destination (x19),
 * loads the old [x19+0x40], and tail-calls the refcount release on it.
 * Confidence: medium
 * Notes: `ldr x0,[x19,#0x40]; ldur q0,[x20,#0x38]; stur q0,[x19,#0x38]; b 0x0036b118`. */
void sk_r38_swap38_release(void *dst, const void *src)
{
    word_t old = *(word_t *)((byte *)dst + 0x40);
    __builtin_memcpy((byte *)dst + 0x38, (const byte *)src + 0x38, 16);
    cL4_ref_release(old);
}

/* FUN_004ac41c @ 0x004ac41c   (est. sk_r38_455ac8_675c68)
 * Tail-calls 0x00455ac8 with x0 = x2 = 0x675c68 (a class/descriptor address)
 * and the caller's x1.
 * Confidence: medium
 * Notes: `adrp x0,0x675000; add x0,x0,#0xc68; mov x2,x0; b 0x00455ac8`. */
void sk_r38_455ac8_675c68(word_t x1)
{
    cL4_455ac8(0x675c68, x1, 0x675c68);
}

/* FUN_004ac42c @ 0x004ac42c   (est. sk_r38_swap28_release)
 * Swaps the +0x28 field of dst (x19) with that of src (x20) and releases the
 * displaced old value.
 * Confidence: medium
 * Notes: `ldr x8,[x20,#0x28]; ldr x0,[x19,#0x28]; str x8,[x19,#0x28]; b 0x0036b118`. */
void sk_r38_swap28_release(void *dst, const void *src)
{
    word_t old = *(word_t *)((byte *)dst + 0x28);
    *(word_t *)((byte *)dst + 0x28) = *(const word_t *)((const byte *)src + 0x28);
    cL4_ref_release(old);
}

/* FUN_004ac43c @ 0x004ac43c   (est. sk_r38_swapa8_retain)
 * Swaps the +0xa8 field of dst (x19) with that of src (x20) and tail-calls
 * the refcount retain on the NEW value.
 * Confidence: medium
 * Notes: `ldr x0,[x20,#0xa8]; ldr x21,[x19,#0xa8]; str x0,[x19,#0xa8]; b 0x0036b270`. */
word_t sk_r38_swapa8_retain(void *dst, const void *src)
{
    word_t old = *(word_t *)((byte *)dst + 0xa8);          /* x21 (discarded) */
    word_t newv = *(const word_t *)((const byte *)src + 0xa8);  /* x0 */
    *(word_t *)((byte *)dst + 0xa8) = newv;
    (void)old;
    /* b 0x0036b270 */
    return cL4_ref_retain(newv);
}


/* FUN_004ac44c @ 0x004ac44c   (est. sk_r38_365b6c_7)
 * Tail-calls the complex message writer 0x00365b6c with (x0=[x29-0xf8],
 * x1=[x29-0xe0]? via x3, x3=[x29-0xe0], w4=7).
 * Confidence: medium
 * Notes: `ldur x0,[x29,#-0xf8]; ldur x3,[x29,#-0xe0]; mov w4,#7; b 0x00365b6c`. */
word_t sk_r38_365b6c_7(word_t x29, word_t x1)
{
    /* b 0x00365b6c(x0, x1, x3, x4=7, x5) */
    word_t x0 = *(const word_t *)(x29 - 0xf8);
    word_t x3 = *(const word_t *)(x29 - 0xe0);
    return cL4_365b6c(x0, x1, x3, 7, 0);
}

/* FUN_004ac45c @ 0x004ac45c   (est. sk_r38_swap00_release_08)
 * Copies the 16-byte head of src (x19) into dst (x20), then loads [x20+0x8]
 * and tail-calls the refcount release on it.
 * Confidence: medium
 * Notes: `ldr x0,[x20,#0x8]; ldr q0,[x19]; str q0,[x20]; b 0x0036b118`. */
void sk_r38_swap00_release_08(void *dst, const void *src)
{
    /* x0 = [dst(x20),#0x8] */
    word_t old = *(word_t *)((byte *)dst + 0x8);
    __builtin_memcpy(dst, src, 16);
    cL4_ref_release(old);
}

/* FUN_004ac46c @ 0x004ac46c   (est. sk_r38_swap00_release_align)
 * Stores [src(x20)] into dst(x19), computes x19 = [x20] + ((x8+0x10) & ~x8)
 * (an alignment/slot computation), and tail-calls the refcount release on the
 * value at x20.
 * Confidence: medium
 * Notes: `ldr x0,[x20]; str x0,[x19]; add x9,x8,#0x10; bic x8,x9,x8; add x19,x0,x8; b 0x0036b118`. */
void sk_r38_swap00_release_align(word_t *dst, const word_t *src, word_t x8)
{
    word_t v = *src;                 /* x0 */
    *dst = v;
    /* add x9,x8,#0x10 ; bic x8,x9,x8 ; add x19,x0,x8 */
    word_t slot = v + ((x8 + 0x10) & ~x8);
    (void)slot;
    cL4_ref_release(v);
}

/* FUN_004ac484 @ 0x004ac484   (est. sk_r38_swap98_metadata_chain)
 * Swaps the +0x98 field of dst (x19) with that of src (x20), copies +0x90,
 * and tail-calls the metadata-chain helper on the new value.
 * Confidence: medium
 * Notes: `ldr x8,[x20,#0x90]; str x8,[x19,#0x90]; ldr x0,[x20,#0x98]; ldr x21,[x19,#0x98]; str x0,[x19,#0x98]; b 0x003a25d0`. */
word_t sk_r38_swap98_metadata_chain(void *dst, const void *src)
{
    *(word_t *)((byte *)dst + 0x90) = *(const word_t *)((const byte *)src + 0x90);
    word_t old = *(word_t *)((byte *)dst + 0x98);           /* x21 (discarded) */
    word_t newv = *(const word_t *)((const byte *)src + 0x98); /* x0 */
    *(word_t *)((byte *)dst + 0x98) = newv;
    (void)old;
    /* b 0x003a25d0 */
    return cL4_metadata_chain(newv);
}

/* FUN_004ac49c @ 0x004ac49c   (est. sk_r38_swap88_release)
 * Swaps the +0x88 field of dst (x19) with that of src (x20) and tail-calls
 * the refcount release on the new value.
 * Confidence: medium
 * Notes: `ldr x0,[x20,#0x88]; ldr x21,[x19,#0x88]; str x0,[x19,#0x88]; b 0x0036b118`. */
void sk_r38_swap88_release(void *dst, const void *src)
{
    word_t old = *(word_t *)((byte *)dst + 0x88);            /* x21 (discarded) */
    word_t newv = *(const word_t *)((const byte *)src + 0x88); /* x0 */
    *(word_t *)((byte *)dst + 0x88) = newv;
    (void)old;
    cL4_ref_release(newv);
}

/* FUN_004ac4ac @ 0x004ac4ac   (est. sk_r38_release_sp_50)
 * Loads the 64-bit value at [sp+0x50] into x0 and tail-calls the refcount
 * release helper.
 * Confidence: medium
 * Notes: `ldr q0,[sp,#0x50]; fmov x0,d0; b 0x0036b118`. */
void sk_r38_release_sp_50(word_t sp)
{
    word_t obj;
    __builtin_memcpy(&obj, (const void *)(sp + 0x50), 8);
    cL4_ref_release(obj);
}

/* FUN_004ac4b8 @ 0x004ac4b8   (est. sk_r38_2a4ab4_16)
 * Builds a 2-word stack frame at sp+0x328 ([+0]=0, [+0x8]=0xe000000000000000),
 * sets x20 = sp+0x328, and tail-calls 0x002a4ab4 with w0=0x16.
 * Confidence: medium
 * Notes: `mov x8,#-0x2000000000000000; str xzr,[sp,#0x328]; str x8,[sp,#0x330]; add x20,sp,#0x328; mov w0,#0x16; b 0x002a4ab4`. */
void sk_r38_2a4ab4_16(word_t sp)
{
    word_t frame = sp + 0x328;
    *(word_t *)(frame) = 0;
    *(word_t *)(frame + 0x8) = 0xe000000000000000UL;
    cL4_2a4ab4(0x16, frame);
}

/* FUN_004ac4d0 @ 0x004ac4d0   (est. sk_r38_swap48_release)
 * Copies the 16-byte field at +0x48 from source (x20) to destination (x19),
 * loads the old [x19+0x50], and tail-calls the refcount release on it.
 * Confidence: medium
 * Notes: `ldr x0,[x19,#0x50]; ldur q0,[x20,#0x48]; stur q0,[x19,#0x48]; b 0x0036b118`. */
void sk_r38_swap48_release(void *dst, const void *src)
{
    word_t old = *(word_t *)((byte *)dst + 0x50);
    __builtin_memcpy((byte *)dst + 0x48, (const byte *)src + 0x48, 16);
    cL4_ref_release(old);
}

/* FUN_004ac4e0 @ 0x004ac4e0   (est. sk_r38_memcpy_sp_160)
 * Tail-calls cL4_memcpy_v(sp, sp+0x160, 0x160) — copies a 0x160-byte frame
 * region.
 * Confidence: medium
 * Notes: `mov x0,sp; add x1,sp,#0x160; mov w2,#0x160; b 0x00117cc4`. */
void *sk_r38_memcpy_sp_160(word_t sp)
{
    return cL4_memcpy_v(sp, sp + 0x160, 0x160);
}

/* FUN_004ac4f0 @ 0x004ac4f0   (est. sk_r38_48273c_args)
 * Tail-calls 0x0048273c with eight registers built from the object at x20:
 * (x5,x6)=[x20], x0=[x20+0x58], (x1,x2)=[x20+0x10], x3=x20+0x30, x4=x20+0x38.
 * Confidence: medium
 * Notes: `ldp x5,x6,[x20]; ldr x0,[x20,#0x58]; ldp x1,x2,[x20,#0x10]; add x3,x20,#0x30; add x4,x20,#0x38; b 0x0048273c`. */
void sk_r38_48273c_args(const void *obj)
{
    cL4_w16_t a = *(const cL4_w16_t *)((const byte *)obj + 0x00);   /* x5,x6 */
    cL4_w16_t b = *(const cL4_w16_t *)((const byte *)obj + 0x10);   /* x1,x2 */
    word_t x0 = *(const word_t *)((const byte *)obj + 0x58);
    cL4_48273c(a.lo, a.hi, b.lo, b.hi, x0,
               (word_t)((const byte *)obj + 0x30), (word_t)((const byte *)obj + 0x38), 0);
}

/* FUN_004ac508 @ 0x004ac508   (est. sk_r38_4a3918_setup)
 * Writes x20 to [x26+0x20] and byte w24 to [x26+0x28], sets x0=sp+0x398, and
 * tail-calls 0x004a3918.
 * Confidence: medium
 * Notes: `str x20,[x26,#0x20]; strb w24,[x26,#0x28]; add x0,sp,#0x398; b 0x004a3918`. */
void sk_r38_4a3918_setup(word_t x26, word_t x20, word_t w24, word_t sp)
{
    *(word_t *)((byte *)x26 + 0x20) = x20;
    *((byte *)x26 + 0x28) = (byte)w24;
    cL4_4a3918(sp + 0x398);
}

/* FUN_004ac518 @ 0x004ac518   (est. sk_r38_csel_cc)
 * Conditional-select: if the carry flag is clear (unsigned >=), returns x0,
 * else x8.
 * Confidence: medium
 * Notes: `csel x0,x0,x8,cc`. */
word_t sk_r38_csel_cc(word_t x0, word_t x8, bool carry_clear)
{
    return carry_clear ? x0 : x8;
}

/* FUN_004ac520 @ 0x004ac520   (est. sk_r38_4a3940)
 * Tail-calls 0x004a3940 with x0=sp+0x398, x1=sp+0x238.
 * Confidence: medium
 * Notes: `add x0,sp,#0x398; add x1,sp,#0x238; b 0x004a3940`. */
void sk_r38_4a3940(word_t sp)
{
    cL4_4a3940(sp + 0x398, sp + 0x238);
}

/* FUN_004ac52c @ 0x004ac52c   (est. sk_r38_memcpy_b0)
 * Tail-calls cL4_memcpy_v(x0, x20+0xb0, 0xb0) — copies 0xb0 bytes from the
 * field at x20+0xb0 into the destination in x0.
 * Confidence: medium
 * Notes: `add x1,x20,#0xb0; mov w2,#0xb0; b 0x00117cc4`. */
void *sk_r38_memcpy_b0(void *dst, const void *src)
{
    return cL4_memcpy_v((word_t)dst, (word_t)((const byte *)src + 0xb0), 0xb0);
}

/* FUN_004ac538 @ 0x004ac538   (est. sk_r38_store_retain_and)
 * Stores q0 at [x0+0x10] and x19 at [x0+0x20]; writes x23 to [x21+0x10]
 * (post-incremented to x20); computes x0 = x19 & x24 and tail-calls the
 * refcount retain on it.
 * Confidence: medium
 * Notes: `str q0,[x0,#0x10]; str x19,[x0,#0x20]; mov x20,x21; str x23,[x20,#0x10]!; and x0,x19,x24; b 0x0036b270`. */
word_t sk_r38_store_retain_and(void *obj, word_t x19, word_t x23, word_t x24, word_t x21)
{
    __builtin_memcpy((byte *)obj + 0x10, (void *)&x19 /*q0 placeholder*/, 0);
    /* str x19,[x0,#0x20] */
    *(word_t *)((byte *)obj + 0x20) = x19;
    /* str x23,[x20,#0x10]! (x20 = x21 post-incremented) */
    *(word_t *)((byte *)x21 + 0x10) = x23;
    /* and x0,x19,x24 */
    return cL4_ref_retain(x19 & x24);
}

/* FUN_004ac550 @ 0x004ac550   (est. sk_r38_release_sp_30)
 * Loads the 64-bit value at [sp+0x30] into x0 and tail-calls the refcount
 * release helper.
 * Confidence: medium
 * Notes: `ldr q0,[sp,#0x30]; fmov x0,d0; b 0x0036b118`. */
void sk_r38_release_sp_30(word_t sp)
{
    word_t obj;
    __builtin_memcpy(&obj, (const void *)(sp + 0x30), 8);
    cL4_ref_release(obj);
}

/* FUN_004ac55c @ 0x004ac55c   (est. sk_r38_4a4b14)
 * Tail-calls 0x004a4b14 with x0=sp+0xd0, x1=0x657a00, x2=0x5a4ad0.
 * Confidence: medium
 * Notes: `adrp x1,0x657000; add x1,x1,#0xa00; adrp x2,0x5a4000; add x2,x2,#0xad0; add x0,sp,#0xd0; b 0x004a4b14`. */
void sk_r38_4a4b14(word_t sp)
{
    cL4_4a4b14(sp + 0xd0, 0x657a00, 0x5a4ad0);
}

/* FUN_004ac574 @ 0x004ac574   (est. sk_r38_slot_retain_mask)
 * Loads slot x20 = [x23 + (x28<<3) + 0x20], masks off the tag bits, and
 * tail-calls the refcount retain on it.
 * Confidence: medium
 * Notes: `add x8,x23,x28,LSL#3; ldr x20,[x8,#0x20]; and x0,x20,#0xfffffffffffffff; b 0x0036b270`. */
word_t sk_r38_slot_retain_mask(word_t x23, word_t x28)
{
    word_t slot = *(const word_t *)((byte *)x23 + (x28 << 3) + 0x20);
    return cL4_ref_retain(slot & R38_OBJ_MASK);
}

/* FUN_004ac584 @ 0x004ac584   (est. sk_r38_store_metadata_chain)
 * Stores x20/x24 to [x0+0x10]/[x0+0x18], saves x25=x0, and tail-calls the
 * metadata-chain helper on x24.
 * Confidence: medium
 * Notes: `mov x25,x0; stp x20,x24,[x0,#0x10]; mov x0,x24; b 0x003a25d0`. */
word_t sk_r38_store_metadata_chain(void *obj, word_t x20, word_t x24)
{
    *(word_t *)((byte *)obj + 0x10) = x20;
    *(word_t *)((byte *)obj + 0x18) = x24;
    return cL4_metadata_chain(x24);
}

/* FUN_004ac594 @ 0x004ac594   (est. sk_r38_478a98)
 * Tail-calls 0x00478a98 with x0=x25 and x27=[sp+0x10].
 * Confidence: medium
 * Notes: `mov x0,x25; ldr x27,[sp,#0x10]; mov x20,x27; b 0x00478a98`. */
void sk_r38_478a98(word_t x25, word_t sp)
{
    word_t x27 = *(const word_t *)(sp + 0x10);
    cL4_478a98(x25, x27);
}

/* FUN_004ac5a4 @ 0x004ac5a4   (est. sk_r38_panic_28656e4f)
 * Panic shim: tail-calls the panic routine with code 0x28656e4f and value
 * 0xe400000000000000.
 * Confidence: medium
 * Notes: `mov w0,#0x6e4f; movk w0,#0x2865,LSL#16; mov x1,#-0x1c00000000000000; b 0x0044ca08`. */
void sk_r38_panic_28656e4f(void)
{
    cL4_44ca08(0x28656e4f, 0xe400000000000000UL);
}

/* FUN_004ac5b4 @ 0x004ac5b4   (est. sk_r38_store_retain_10)
 * Stores x21/x19 to [x0+0x10]/[x0+0x18], saves x23=x0, and tail-calls the
 * refcount retain on x19.
 * Confidence: medium
 * Notes: `mov x23,x0; stp x21,x19,[x0,#0x10]; mov x0,x19; b 0x0036b270`. */
word_t sk_r38_store_retain_10(void *obj, word_t x21, word_t x19)
{
    *(word_t *)((byte *)obj + 0x10) = x21;
    *(word_t *)((byte *)obj + 0x18) = x19;
    return cL4_ref_retain(x19);
}

/* FUN_004ac5c4 @ 0x004ac5c4   (est. sk_r38_memcpy_c0)
 * Tail-calls cL4_memcpy_v(x29-0xe0, x20, 0xc0); saves x19=x0, x21=x8.
 * Confidence: medium
 * Notes: `mov x19,x0; mov x21,x8; sub x0,x29,#0xe0; mov x1,x20; mov w2,#0xc0; b 0x00117cc4`. */
void *sk_r38_memcpy_c0(word_t x29, word_t x20, word_t x0, word_t x8)
{
    word_t x19 = x0, x21 = x8;
    (void)x19; (void)x21;
    return cL4_memcpy_v(x29 - 0xe0, x20, 0xc0);
}

/* FUN_004ac5dc @ 0x004ac5dc   (est. sk_r38_365b6c_0)
 * Tail-calls the message writer 0x00365b6c with x1=x22, x2=[x29-0xe0], x4=0.
 * Confidence: medium
 * Notes: `mov x1,x22; ldur x2,[x29,#-0xe0]; mov x4,#0; b 0x00365b6c`. */
word_t sk_r38_365b6c_0(word_t x22, word_t x29, word_t x0, word_t x3, word_t x5)
{
    return cL4_365b6c(x0, x22, *(const word_t *)(x29 - 0xe0), x3, 0);
}

/* FUN_004ac5ec @ 0x004ac5ec   (est. sk_r38_488828)
 * Tail-calls 0x00488828 with x0=x20, x1=x21, and x20=x19.
 * Confidence: medium
 * Notes: `mov x0,x20; mov x1,x21; mov x20,x19; b 0x00488828`. */
void sk_r38_488828(word_t x20, word_t x21, word_t x19)
{
    word_t x20v = x19;
    (void)x20v;
    cL4_488828(x20, x21);
}

/* FUN_004ac5fc @ 0x004ac5fc   (est. sk_r38_memcpy_360_4c0)
 * Tail-calls cL4_memcpy_v(sp+0x360, sp+0x4c0, 0x160).
 * Confidence: medium
 * Notes: `add x0,sp,#0x360; add x1,sp,#0x4c0; mov w2,#0x160; b 0x00117cc4`. */
void *sk_r38_memcpy_360_4c0(word_t sp)
{
    return cL4_memcpy_v(sp + 0x360, sp + 0x4c0, 0x160);
}

/* FUN_004ac60c @ 0x004ac60c   (est. sk_r38_365b6c_add)
 * Tail-calls the message writer 0x00365b6c with x1=x21+x25, x2=[x29-0xa0], x4=0.
 * Confidence: medium
 * Notes: `add x1,x21,x25; ldur x2,[x29,#-0xa0]; mov x4,#0; b 0x00365b6c`. */
word_t sk_r38_365b6c_add(word_t x21, word_t x25, word_t x29, word_t x0, word_t x3, word_t x5)
{
    return cL4_365b6c(x0, x21 + x25, *(const word_t *)(x29 - 0xa0), x3, 0);
}

/* FUN_004ac61c @ 0x004ac61c   (est. sk_r38_memcpy_sp_b0)
 * Tail-calls cL4_memcpy_v(x0, sp, 0xb0) — copies 0xb0 bytes from the stack
 * into the destination in x0.
 * Confidence: medium
 * Notes: `mov x1,sp; mov w2,#0xb0; b 0x00117cc4`. */
void *sk_r38_memcpy_sp_b0(void *dst, word_t sp)
{
    return cL4_memcpy_v((word_t)dst, sp, 0xb0);
}

/* FUN_004ac628 @ 0x004ac628   (est. sk_r38_3722e4)
 * Tail-calls 0x003722e4 with x3=0, x4=0 (the remaining args from the caller).
 * Confidence: medium
 * Notes: `mov x3,#0; mov x4,#0; b 0x003722e4`. */
void sk_r38_3722e4(word_t x0, word_t x1, word_t x2)
{
    cL4_3722e4(x0, x1, x2, 0);
}

/* FUN_004ac634 @ 0x004ac634   (est. sk_r38_memcpy_99)
 * Tail-calls cL4_memcpy_v(x0, x23, 0x99) — copies 0x99 bytes from the object
 * in x23 into the destination in x0.
 * Confidence: medium
 * Notes: `mov x1,x23; mov w2,#0x99; b 0x00117cc4`. */
void *sk_r38_memcpy_99(void *dst, word_t x23)
{
    return cL4_memcpy_v((word_t)dst, x23, 0x99);
}

