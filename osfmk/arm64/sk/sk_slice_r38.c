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


/* FUN_004ac640 @ 0x004ac640   (est. sk_r38_load_pair_from_fp_b)
 * Loads a pair: x0 = [x29-0x60], x1 = [x29-0x108].
 * Confidence: medium
 * Notes: `ldur x26,[x29,#-0x60]; mov x0,x26; sub x10,x29,#0x8; ldur x1,[x10,#-0x100]`. */
cL4_w16_t sk_r38_load_pair_from_fp_b(word_t x29)
{
    cL4_w16_t r;
    r.lo = *(const word_t *)(x29 - 0x60);
    r.hi = *(const word_t *)(x29 - 0x108);
    return r;
}

/* FUN_004ac654 @ 0x004ac654   (est. sk_r38_glob_5e23b0)
 * Returns the address 0x5e23b0 (a global data/string descriptor) in x5.
 * Confidence: medium
 * Notes: `adrp x5,0x5e2000; add x5,x5,#0x3b0`. */
word_t sk_r38_glob_5e23b0(void)
{
    return 0x5e23b0;
}

/* FUN_004ac660 @ 0x004ac660   (est. sk_r38_copy_byte_b0)
 * Copies the byte at +0xb0 from source (x20) to destination (x19).
 * Confidence: medium
 * Notes: `ldrb w8,[x20,#0xb0]; strb w8,[x19,#0xb0]`. */
void sk_r38_copy_byte_b0(void *dst, const void *src)
{
    *((byte *)dst + 0xb0) = *((const byte *)src + 0xb0);
}

/* FUN_004ac66c @ 0x004ac66c   (est. sk_r38_extract_tag_or_head)
 * Loads (x20,x24) = [x0]; if bit 0x2000000000000000 of x24 is clear, returns
 * x20, else returns (x24>>56) & 0xf (an extracted 4-bit tag).
 * Confidence: medium
 * Notes: `ldp x20,x24,[x0]; ubfx x8,x24,#0x38,#0x4; tst x24,#0x2000000000000000; csel x8,x20,x8,eq`. */
word_t sk_r38_extract_tag_or_head(const cL4_w16_t *p)
{
    word_t head = p->lo, tagword = p->hi;
    word_t tag = (tagword >> 56) & 0xf;
    return (tagword & R38_TAG_MASK) ? tag : head;
}

/* FUN_004ac680 @ 0x004ac680   (est. sk_r38_const_ea00000000003e23)
 * Materialises the constant 0xea00000000003e23 into x19.
 * Confidence: medium
 * Notes: `mov x19,#0x3e23; movk x19,#0xea00,LSL#48`. */
word_t sk_r38_const_ea00000000003e23(void)
{
    return 0xea00000000003e23UL;
}

/* FUN_004ac68c @ 0x004ac68c   (est. sk_r38_inc_cmp_half)
 * Computes x25 = x22+1 and compares x22 against x8>>1, returning the
 * comparison flags.
 * Confidence: medium
 * Notes: `add x25,x22,#1; cmp x22,x8,LSR#1`. */
long sk_r38_inc_cmp_half(word_t x22, word_t x8)
{
    word_t x25 = x22 + 1;
    (void)x25;
    return (long)x22 - (long)(x8 >> 1);
}

/* FUN_004ac698 @ 0x004ac698   (est. sk_r38_cset_gt1)
 * Returns 1 if the value in x20 is greater than 1, else 0.
 * Confidence: medium
 * Notes: `cmp x20,#1; cset w0,hi`. */
word_t sk_r38_cset_gt1(word_t x20)
{
    return (x20 > 1) ? 1 : 0;
}

/* FUN_004ac6a4 @ 0x004ac6a4   (est. sk_r38_load_fp_a0)
 * Loads x1 = [x29-0x1a0].
 * Confidence: medium
 * Notes: `sub x8,x29,#0xa0; ldur x1,[x8,#-0x100]`. */
word_t sk_r38_load_fp_a0(word_t x29)
{
    return *(const word_t *)(x29 - 0x1a0);
}

/* FUN_004ac6b0 @ 0x004ac6b0   (est. sk_r38_stackptr_1288)
 * Returns the stack pointer offset by 0x1288 (sp + 0x1000 + 0x288) — a fixed
 * stack slot used as a scratch buffer address.
 * Confidence: medium
 * Notes: Ghidra renders as `return &stack0x00001288`. */
void *sk_r38_stackptr_1288(word_t sp)
{
    return (void *)(sp + 0x1288);
}

/* FUN_004ac6bc @ 0x004ac6bc   (est. sk_r38_csel_8181e1)
 * If w11 != 0, returns w9 + 0x8181e1, else returns w8.
 * Confidence: medium
 * Notes: `add w9,w9,#0x818,LSL#12; add w9,w9,#0x1e1; cmp w11,#0; csel w0,w8,w9,ne`. */
word_t sk_r38_csel_8181e1(word_t w8, word_t w9, word_t w11)
{
    word_t alt = (w9 & 0xffffffff) + 0x8181e1;
    return (w11 != 0) ? alt : w8;
}

/* FUN_004ac6d0 @ 0x004ac6d0   (est. sk_r38_load_pair_predec)
 * Pre-decrements x13 by 8, loads [x13-8] into x9, and returns (x16=x9,
 * x17=x13) — a 2-word (ptr, value) result.
 * Confidence: medium
 * Notes: `mov x13,x0; ldr x9,[x13,#-8]!; mov x16,x9; mov x17,x13`. */
cL4_w16_t sk_r38_load_pair_predec(word_t x0)
{
    cL4_w16_t r;
    word_t x13 = x0 - 8;
    r.lo = *(const word_t *)x13;   /* x9 -> x16 */
    r.hi = x13;                    /* x17 */
    return r;
}

/* FUN_004ac6e4 @ 0x004ac6e4   (est. sk_r38_hash_step)
 * Returns (w8>>6) + w9 + 0x81c1 — a hash/checksum accumulator step.
 * Confidence: medium
 * Notes: `lsr w8,w8,#6; mov w10,#0x81c1; add w8,w8,w9; add w0,w8,w10`. */
word_t sk_r38_hash_step(word_t w8, word_t w9)
{
    return ((w8 >> 6) & 0xffffffff) + w9 + 0x81c1;
}

/* FUN_004ac6f8 @ 0x004ac6f8   (est. sk_r38_load_head_kind)
 * Returns a pair: x0 = [x20], w1 = byte[x20+0x8]; also sets w2=1, w3=0.
 * Confidence: medium
 * Notes: `ldr x0,[x20]; ldrb w1,[x20,#0x8]; mov w2,#1; mov w3,#0`. */
cL4_w16_t sk_r38_load_head_kind(const void *obj)
{
    cL4_w16_t r;
    r.lo = *(const word_t *)obj;
    r.hi = *(const byte *)((const byte *)obj + 0x8);
    word_t w2 = 1, w3 = 0;
    (void)w2; (void)w3;
    return r;
}

/* FUN_004ac70c @ 0x004ac70c   (est. sk_r38_mask48_extract)
 * If bit 0x2000000000000000 of x9 is clear, returns x8 masked to 48 bits,
 * else returns (x9>>56) & 0xf.
 * Confidence: medium
 * Notes: `and x8,x8,#0xffffffffffff; ubfx x10,x9,#0x38,#0x4; tst x9,#0x2000000000000000; csel x8,x8,x10,eq`. */
word_t sk_r38_mask48_extract(word_t x8, word_t x9)
{
    word_t masked = x8 & 0xffffffffffffUL;
    word_t tag = (x9 >> 56) & 0xf;
    return (x9 & R38_TAG_MASK) ? tag : masked;
}

/* FUN_004ac720 @ 0x004ac720   (est. sk_r38_mask_lsl)
 * Returns -1 shifted left by x9 (a bitmask builder).
 * Confidence: medium
 * Notes: `mov x10,#-1; lsl x9,x10,x9`. */
word_t sk_r38_mask_lsl(word_t x9)
{
    word_t x10 = ~0UL;
    return x10 << (x9 & 63);
}

/* FUN_004ac72c @ 0x004ac72c   (est. sk_r38_clz)
 * Returns (w9 = clz(w8), w10 = 4) — a leading-zero-count plus a small const.
 * Confidence: medium
 * Notes: `clz w9,w8; mov w10,#4`. */
cL4_w16_t sk_r38_clz(word_t w8)
{
    cL4_w16_t r;
    r.lo = __builtin_clz((unsigned)(w8 & 0xffffffff)); /* clz w9,w8 */
    r.hi = 4;                                          /* mov w10,#4 */
    return r;
}

/* FUN_004ac738 @ 0x004ac738   (est. sk_r38_setup_x4x5)
 * Register-setup fragment: x4 = x28, x5 = x23.
 * Confidence: medium
 * Notes: `mov x4,x28; mov x5,x23`. */
void sk_r38_setup_x4x5(word_t x28, word_t x23)
{
    word_t x4 = x28, x5 = x23;
    (void)x4; (void)x5;
}

/* FUN_004ac744 @ 0x004ac744   (est. sk_r38_copy_bytes_08_09)
 * Copies the two bytes at +0x8 and +0x9 from source (x20) to destination (x19).
 * Confidence: medium
 * Notes: `ldrb w8,[x20,#0x8]; strb w8,[x19,#0x8]; ldrb w8,[x20,#0x9]; strb w8,[x19,#0x9]`. */
void sk_r38_copy_bytes_08_09(void *dst, const void *src)
{
    *((byte *)dst + 0x8) = *((const byte *)src + 0x8);
    *((byte *)dst + 0x9) = *((const byte *)src + 0x9);
}

/* FUN_004ac758 @ 0x004ac758   (est. sk_r38_setup_and_lo)
 * Register-setup fragment: w3 = w21 & 1; x0 = x22, x1 = x19, x2 = x20.
 * Confidence: medium
 * Notes: `and w3,w21,#1; mov x0,x22; mov x1,x19; mov x2,x20`. */
void sk_r38_setup_and_lo(word_t w21, word_t x22, word_t x19, word_t x20)
{
    word_t w3 = w21 & 1, x0 = x22, x1 = x19, x2 = x20;
    (void)w3; (void)x0; (void)x1; (void)x2;
}

/* FUN_004ac76c @ 0x004ac76c   (est. sk_r38_xor_lsr)
 * Returns (x0 ^ x1) >> 0xe — a hash/index computation.
 * Confidence: medium
 * Notes: `eor x8,x0,x1; lsr x8,x8,#0xe`. */
word_t sk_r38_xor_lsr(word_t x0, word_t x1)
{
    return (x0 ^ x1) >> 0xe;
}

/* FUN_004ac778 @ 0x004ac778   (est. sk_r38_field_18_half)
 * Returns [x0+0x18] >> 1 — a size/count accessor halving a field.
 * Confidence: medium
 * Notes: `ldr x8,[x0,#0x18]; lsr x8,x8,#1`. */
word_t sk_r38_field_18_half(const void *obj)
{
    return *(const word_t *)((const byte *)obj + 0x18) >> 1;
}

/* FUN_004ac784 @ 0x004ac784   (est. sk_r38_pair_x10_x15)
 * Returns (x16=x10, x17=x15) — a 2-word result pass-through.
 * Confidence: medium
 * Notes: `mov x16,x10; mov x17,x15`. */
cL4_w16_t sk_r38_pair_x10_x15(word_t x10, word_t x15)
{
    cL4_w16_t r;
    r.lo = x10;
    r.hi = x15;
    return r;
}

/* FUN_004ac790 @ 0x004ac790   (est. sk_r38_load_pair_predec_b)
 * Pre-decrements x14 by 8, loads [x14-8] into x9, and returns (x16=x9,
 * x17=x14).
 * Confidence: medium
 * Notes: `mov x14,x0; ldr x9,[x14,#-8]!; mov x16,x9; mov x17,x14`. */
cL4_w16_t sk_r38_load_pair_predec_b(word_t x0)
{
    cL4_w16_t r;
    word_t x14 = x0 - 8;
    r.lo = *(const word_t *)x14;
    r.hi = x14;
    return r;
}

/* FUN_004ac7a4 @ 0x004ac7a4   (est. sk_r38_load_deref_08)
 * Returns [ [sp+0x68] + 0x8 ] — a double dereference (indirect vtable field).
 * Confidence: medium
 * Notes: `ldr x8,[sp,#0x68]; ldr x8,[x8,#0x8]`. */
word_t sk_r38_load_deref_08(word_t sp)
{
    word_t p = *(const word_t *)(sp + 0x68);
    return *(const word_t *)(p + 0x8);
}

/* FUN_004ac7b0 @ 0x004ac7b0   (est. sk_r38_pair_sp_160)
 * Returns (x0=sp+0x160, x1=sp).
 * Confidence: medium
 * Notes: `add x0,sp,#0x160; mov x1,sp`. */
cL4_w16_t sk_r38_pair_sp_160(word_t sp)
{
    cL4_w16_t r;
    r.lo = sp + 0x160;
    r.hi = sp;
    return r;
}

/* FUN_004ac7bc @ 0x004ac7bc   (est. sk_r38_cmp_byte2_b)
 * Masks w1 to its low byte and compares it against 2, returning the
 * comparison flags.
 * Confidence: medium
 * Notes: `and w8,w1,#0xff; cmp w8,#0x2`. */
long sk_r38_cmp_byte2_b(word_t w1)
{
    return (long)(w1 & 0xff) - 2;
}

/* FUN_004ac7c8 @ 0x004ac7c8   (est. sk_r38_pair_x9_x12)
 * Returns (x16=x9, x17=x12) — a 2-word result pass-through.
 * Confidence: medium
 * Notes: `mov x16,x9; mov x17,x12`. */
cL4_w16_t sk_r38_pair_x9_x12(word_t x9, word_t x12)
{
    cL4_w16_t r;
    r.lo = x9;
    r.hi = x12;
    return r;
}

/* FUN_004ac7d4 @ 0x004ac7d4   (est. sk_r38_load_deref_10)
 * Returns [ [x27] + 0x10 ] — an indirect function/table pointer load.
 * Confidence: medium
 * Notes: `ldr x8,[x27]; ldr x9,[x8,#0x10]`. */
word_t sk_r38_load_deref_10(word_t x27)
{
    word_t p = *(const word_t *)x27;
    return *(const word_t *)(p + 0x10);
}

/* FUN_004ac7e0 @ 0x004ac7e0   (est. sk_r38_load_deref_10_b)
 * Returns [ [x20] + 0x10 ] into x22.
 * Confidence: medium
 * Notes: `ldr x8,[x20]; ldr x22,[x8,#0x10]`. */
word_t sk_r38_load_deref_10_b(word_t x20)
{
    word_t p = *(const word_t *)x20;
    return *(const word_t *)(p + 0x10);
}

/* FUN_004ac7ec @ 0x004ac7ec   (est. sk_r38_cmp_byte_1a)
 * Masks w8 to its low byte and compares it against 0x1a.
 * Confidence: medium
 * Notes: `and w8,w8,#0xff; cmp w8,#0x1a`. */
long sk_r38_cmp_byte_1a(word_t w8)
{
    return (long)(w8 & 0xff) - 0x1a;
}

/* FUN_004ac7f8 @ 0x004ac7f8   (est. sk_r38_cmp_head_a0d)
 * Loads (x20,x23)=[x0] and compares x20 against 0xa0d.
 * Confidence: medium
 * Notes: `ldp x20,x23,[x0]; cmp x20,#0xa0d`. */
long sk_r38_cmp_head_a0d(const cL4_w16_t *p)
{
    return (long)p->lo - 0xa0d;
}

/* FUN_004ac804 @ 0x004ac804   (est. sk_r38_cinc_if_zero)
 * If w9 == 0, returns x10+1, else returns x10.
 * Confidence: medium
 * Notes: `cmp w9,#0; cinc x9,x10,eq`. */
word_t sk_r38_cinc_if_zero(word_t w9, word_t x10)
{
    return (w9 == 0) ? x10 + 1 : x10;
}

/* FUN_004ac810 @ 0x004ac810   (est. sk_r38_pair_glob_6163e4)
 * Returns (x3=0x6163e4, x4=0x6163ec) — two adjacent global descriptors.
 * Confidence: medium
 * Notes: `adrp x3,0x616000; add x3,x3,#0x3e4; adrp x4,0x616000; add x4,x4,#0x3ec`. */
cL4_w16_t sk_r38_pair_glob_6163e4(void)
{
    cL4_w16_t r;
    r.lo = 0x6163e4;
    r.hi = 0x6163ec;
    return r;
}

/* FUN_004ac824 @ 0x004ac824   (est. sk_r38_const_05000001)
 * Returns the constant 0x05000001.
 * Confidence: medium
 * Notes: `mov w0,#1; movk w0,#0x500,LSL#16`. */
word_t sk_r38_const_05000001(void)
{
    return 0x05000001;
}

/* FUN_004ac830 @ 0x004ac830   (est. sk_r38_pair_glob_657c00)
 * Returns (x0=0x657c00, x1=0x5a3ca8) — two global/string descriptors.
 * Confidence: medium
 * Notes: `adrp x0,0x657000; add x0,x0,#0xc00; adrp x1,0x5a3000; add x1,x1,#0xca8`. */
cL4_w16_t sk_r38_pair_glob_657c00(void)
{
    cL4_w16_t r;
    r.lo = 0x657c00;
    r.hi = 0x5a3ca8;
    return r;
}


/* FUN_004ac0a4 @ 0x004ac0a4   (est. sk_r38_boot_init_dispatch)
 * Register-shuffle thunk: forwards six context values (loaded into x0-x5 from
 * callee-saved x20/x21/x26/x27) to the shared boot/init routine at 0x00346718.
 * Confidence: medium
 * Notes: tail-call `b 0x00346718` = thunk_FUN_002b74c0. */
void sk_r38_boot_init_dispatch(word_t x20, word_t x27, word_t x26, word_t x21)
{
    /* b 0x00346718 : mov x0,x20; x1,x27; x2,x20; x3,x27; x4,x26; x5,x21 */
    cL4_346718(x20, x27, x20, x27, x26, x21);
}

/* FUN_004ac0c0 @ 0x004ac0c0   (est. sk_r38_tag_mask_ptr)
 * Clears the top nibble (bits 60-63) and bit 2 of the value in x8 — a pointer
 * tag/flag mask — leaving the result in x8. (Ghidra collapses to bare return.)
 * Confidence: medium
 * Notes: `and x8,x8,#0xfffffffffffffff ; and x8,x8,#-0x5`. */
word_t sk_r38_tag_mask_ptr(word_t x8)
{
    return x8 & R38_OBJ_MASK;
}

/* FUN_004ac0cc @ 0x004ac0cc   (est. sk_r38_347480_dispatch)
 * Forwards argument (x1 -> x21) and a stack pointer (sp+0x10 -> x20) to the
 * dispatch routine at 0x00347480.
 * Confidence: medium
 * Notes: tail-call `b 0x00347480`. */
void sk_r38_347480_dispatch(word_t x1, word_t sp)
{
    /* mov x21,x1 ; add x20,sp,#0x10 ; b 0x00347480 */
    cL4_347480(x1, sp + 0x10);
}

/* FUN_004ac0d8 @ 0x004ac0d8   (est. sk_r38_copy_d0d8)
 * Copies a 1-byte field at +0xd0 and an 8-byte field at +0xd8 from source
 * (x20) to destination (x19); returns the destination pointer.
 * Confidence: medium
 * Notes: reads/writes through callee-saved x19 (dst) / x20 (src). */
void *sk_r38_copy_d0d8(void *dst, const void *src)
{
    /* ldrb w8,[x20,#0xd0]; strb w8,[x19,#0xd0]; ldr x8,[x20,#0xd8]; str x8,[x19,#0xd8] */
    ((byte *)dst)[0xd0] = ((const byte *)src)[0xd0];
    *(word_t *)((byte *)dst + 0xd8) = *(const word_t *)((const byte *)src + 0xd8);
    return dst; /* mov x0,x19 */
}

/* FUN_004ac0f0 @ 0x004ac0f0   (est. sk_r38_copy_6870)
 * Copies 8-byte fields at +0x68 and +0x70 from source (x20) to destination
 * (x19); also loads the +0x78 field (kept in x8 for the caller).
 * Confidence: medium
 * Notes: writes through callee-saved x19 (dst) / x20 (src). */
void sk_r38_copy_6870(void *dst, const void *src)
{
    /* ldr x8,[x20,#0x68]; str x8,[x19,#0x68]; ldr x8,[x20,#0x70]; str x8,[x19,#0x70] */
    *(word_t *)((byte *)dst + 0x68) = *(const word_t *)((const byte *)src + 0x68);
    *(word_t *)((byte *)dst + 0x70) = *(const word_t *)((const byte *)src + 0x70);
    /* ldr x8,[x20,#0x78] — result left in scratch x8 */
}

/* FUN_004ac108 @ 0x004ac108   (est. sk_r38_field_60_plus_one)
 * Loads the 8-byte field at +0x60 of the object in x19 and returns it plus
 * one (a read-only size/count accessor; no store).
 * Confidence: medium
 * Notes: `ldr x8,[x19,#0x60]; adds x8,x8,#0x1`. */
word_t sk_r38_field_60_plus_one(const void *obj)
{
    return *(const word_t *)((const byte *)obj + 0x60) + 1;
}

/* FUN_004ac114 @ 0x004ac114   (est. sk_r38_mask_const)
 * Materialises the pointer-tag mask constant 0x0ffffffffffffffb into x21.
 * Confidence: medium
 * Notes: `mov x21,#-0x5 ; movk x21,#0xfff,LSL#48`. */
word_t sk_r38_mask_const(void)
{
    return R38_OBJ_MASK;
}

/* FUN_004ac120 @ 0x004ac120   (est. sk_r38_cmp_field_10)
 * Compares x28 against the 8-byte field at +0x10 of the object in x23,
 * returning the signed difference (comparison flags).
 * Confidence: medium
 * Notes: `cmp x28,[x23,#0x10]`. */
long sk_r38_cmp_field_10(word_t x28, const void *obj)
{
    return (long)x28 - (long)*(const word_t *)((const byte *)obj + 0x10);
}

/* FUN_004ac12c @ 0x004ac12c   (est. sk_r38_setup_copy_10_b0)
 * Register-setup fragment: loads x1 = x8 + 0x10 and w2 = 0xb0 (176) — the
 * src/size for a caller-driven memcpy — then returns.
 * Confidence: medium
 * Notes: `add x1,x8,#0x10 ; mov w2,#0xb0`. */
void sk_r38_setup_copy_10_b0(word_t x8)
{
    word_t x1 = x8 + 0x10, w2 = 0xb0;
    (void)x1; (void)w2;
}

/* FUN_004ac138 @ 0x004ac138   (est. sk_r38_stackptr_13e8)
 * Returns the stack pointer offset by 0x13e8 (sp + 0x1000 + 0x3e8) — a fixed
 * stack slot used as a scratch buffer address.
 * Confidence: medium
 * Notes: Ghidra renders as `return &stack0x000013e8`. */
void *sk_r38_stackptr_13e8(word_t sp)
{
    return (void *)(sp + 0x13e8);
}

/* FUN_004ac144 @ 0x004ac144   (est. sk_r38_cmp_byte2)
 * Masks w2 to its low byte and compares it against 2, returning the
 * comparison flags (modelled as a difference).
 * Confidence: medium
 * Notes: `and w9,w2,#0xff ; cmp w9,#0x2`. */
long sk_r38_cmp_byte2(word_t w2)
{
    return (long)(w2 & 0xff) - 2;
}

/* FUN_004ac150 @ 0x004ac150   (est. sk_r38_ubfiz_cmp_800)
 * Computes w9 = (w8 & 0x3f) << 8 and compares w8 against 0x800.
 * Confidence: medium
 * Notes: `ubfiz w9,w8,#8,#6` extracts a 6-bit field and shifts left 8. */
void sk_r38_ubfiz_cmp_800(word_t w8)
{
    word_t w9 = (w8 & 0x3f) << 8;
    (void)w9;
}

/* FUN_004ac15c @ 0x004ac15c   (est. sk_r38_mask_const_b)
 * Materialises the pointer-tag mask constant 0x0ffffffffffffffb into x22.
 * Confidence: medium
 * Notes: same constant as 004ac114, delivered in x22. */
word_t sk_r38_mask_const_b(void)
{
    return R38_OBJ_MASK;
}

/* FUN_004ac168 @ 0x004ac168   (est. sk_r38_and_add_ptr)
 * Computes (x10 + x19) & ~x9 into x0, also returning x8 in x1 and x20 in x2 —
 * a multi-word (object pointer + extra words) result.
 * Confidence: medium
 * Notes: `mvn x9,x9 ; add x10,x10,x19 ; and x0,x10,x9 ; mov x1,x8 ; mov x2,x20`. */
cL4_w16_t sk_r38_and_add_ptr(word_t x9, word_t x10, word_t x19, word_t x8, word_t x20)
{
    cL4_w16_t r;
    r.lo = (x10 + x19) & ~x9;
    r.hi = x8;                 /* mov x1,x8 */
    (void)x20;                 /* mov x2,x20 — third word left in x2 */
    return r;
}

/* FUN_004ac180 @ 0x004ac180   (est. sk_r38_setup_store_sp)
 * Register-setup fragment: stores x19 to [sp], computes x5/x6/x7 = sp + 0x38/
 * 0x30/0x28, and returns x20 in x0.
 * Confidence: medium
 * Notes: `str x19,[sp]; add x5,sp,#0x38; add x6,sp,#0x30; add x7,sp,#0x28; mov x0,x20`. */
void sk_r38_setup_store_sp(word_t sp, word_t x19, word_t x20)
{
    *(word_t *)sp = x19;
    word_t x5 = sp + 0x38, x6 = sp + 0x30, x7 = sp + 0x28, x0 = x20;
    (void)x5; (void)x6; (void)x7; (void)x0;
}

/* FUN_004ac198 @ 0x004ac198   (est. sk_r38_tag_bits_from_hi)
 * Shifts x0 right by 0x3b (59) and masks to 0x1e, extracting a 5-bit tag
 * field from the top of the value into w16.
 * Confidence: medium
 * Notes: `lsr x8,x0,#0x3b ; and w16,w8,#0x1e`. */
word_t sk_r38_tag_bits_from_hi(word_t x0)
{
    return (x0 >> 0x3b) & 0x1e;
}

/* FUN_004ac1a4 @ 0x004ac1a4   (est. sk_r38_call_49df18)
 * PAC-protected thunk that calls 0x0049df18() with no arguments and returns
 * its result (also retained in x20).
 * Confidence: medium
 * Notes: prologue pacibsp/retab; `bl 0x0049df18 ; mov x20,x0`. */
word_t sk_r38_call_49df18(void)
{
    word_t result = cL4_49df18();
    return result; /* mov x20,x0 */
}

/* FUN_004ac1bc @ 0x004ac1bc   (est. sk_r38_load_pair_from_fp)
 * Loads two 8-byte frame slots into x0/x1: x0 = [x29-0x120], x1 = [x29-0x128].
 * Confidence: medium
 * Notes: `ldur x0,[x29,#-0x120] ; ldur x1,[x29,#-0x128]`. */
cL4_w16_t sk_r38_load_pair_from_fp(word_t x29)
{
    cL4_w16_t r;
    r.lo = *(const word_t *)(x29 - 0x120);
    r.hi = *(const word_t *)(x29 - 0x128);
    return r;
}

/* FUN_004ac1d4 @ 0x004ac1d4   (est. sk_r38_copy_16_a0)
 * Copies the 16-byte (Q) field at +0xa0 from source (x20) to destination (x19).
 * Confidence: medium
 * Notes: `ldr q0,[x20,#0xa0] ; str q0,[x19,#0xa0]`. */
void sk_r38_copy_16_a0(void *dst, const void *src)
{
    __builtin_memcpy((byte *)dst + 0xa0, (const byte *)src + 0xa0, 16);
}

/* FUN_004ac1e0 @ 0x004ac1e0   (est. sk_r38_orr_chain_add)
 * OR-combines (x21<<0x1b) | x8 | x9 | x10, then adds [sp+0x8], returning the
 * sum in x8.
 * Confidence: medium
 * Notes: `adds` also sets flags. */
word_t sk_r38_orr_chain_add(word_t x8, word_t x21, word_t x9, word_t x10, word_t sp)
{
    word_t acc = x8 | (x21 << 0x1b) | x9 | x10;
    return *(const word_t *)(sp + 0x8) + acc;
}

/* FUN_004ac1f8 @ 0x004ac1f8   (est. sk_r38_setup_6args)
 * Register-setup fragment: loads x2-x6 from callee-saved x28/x20/x23/x24/x25.
 * Confidence: medium
 * Notes: `mov x2,x28 ; mov x3,x20 ; mov x4,x23 ; mov x5,x24 ; mov x6,x25`. */
void sk_r38_setup_6args(word_t x28, word_t x20, word_t x23, word_t x24, word_t x25)
{
    word_t x2 = x28, x3 = x20, x4 = x23, x5 = x24, x6 = x25;
    (void)x2; (void)x3; (void)x4; (void)x5; (void)x6;
}

/* FUN_004ac210 @ 0x004ac210   (est. sk_r38_call_49e2d4_cmp7)
 * PAC-protected thunk: calls 0x0049e2d4() and compares its result against 7.
 * Confidence: medium
 * Notes: `bl 0x0049e2d4 ; cmp w0,#7`. */
long sk_r38_call_49e2d4_cmp7(void)
{
    return (long)(cL4_49e2d4(0) & 0xffffffff) - 7;
}

/* FUN_004ac228 @ 0x004ac228   (est. sk_r38_zero_0x68)
 * Zero-initialises a 0x68-byte (104-byte) object at x19: writes 0 to +0x60
 * and clears the 16-byte-aligned region [0x00,0x60) with four Q stores.
 * Confidence: high (unambiguous zeroing loop)
 * Notes: disasm confirms vectorised zeroing. */
void sk_r38_zero_0x68(void *obj)
{
    __builtin_memset((byte *)obj, 0, 0x68);
}

/* FUN_004ac240 @ 0x004ac240   (est. sk_r38_init_node_pair)
 * Initialises two linked nodes: destination object at x0 gets fields +0x10/
 * +0x18/+0x20/+0x28 = x21,x19,x23,x22; the node at x20 gets +0x00/+0x08/
 * +0x10/+0x18 = x21,x19,x24,x0 and a byte +0x20 = w25.
 * Confidence: medium
 * Notes: double-list/object-embedding init; writes through x19/x20/x21-x24. */
void sk_r38_init_node_pair(void *dst, void *node, word_t x19, word_t x21,
                           word_t x22, word_t x23, word_t x24, word_t w25)
{
    *(word_t *)((byte *)dst + 0x10) = x21;
    *(word_t *)((byte *)dst + 0x18) = x19;
    *(word_t *)((byte *)dst + 0x20) = x23;
    *(word_t *)((byte *)dst + 0x28) = x22;
    *(word_t *)((byte *)node + 0x00) = x21;
    *(word_t *)((byte *)node + 0x08) = x19;
    *(word_t *)((byte *)node + 0x10) = x24;
    *(word_t *)((byte *)node + 0x18) = (word_t)dst;
    *((byte *)node + 0x20) = (byte)w25;
}

/* FUN_004ac258 @ 0x004ac258   (est. sk_r38_clear_byte_30)
 * Writes a zero byte at +0x30 of the object in x8 and returns x22 (a saved
 * object pointer).
 * Confidence: medium
 * Notes: `strb wzr,[x8,#0x30] ; mov x0,x22`. */
word_t sk_r38_clear_byte_30(void *obj, word_t x22)
{
    *((byte *)obj + 0x30) = 0;
    return x22;
}

/* FUN_004ac264 @ 0x004ac264   (est. sk_r38_copy_head_cmp_30)
 * Copies the first 8 bytes of *x1 into *x0, then compares [x0+0x30] against 1
 * (a refcount/kind test returning flags).
 * Confidence: medium
 * Notes: `ldr x8,[x1],#8 ; str x8,[x0] ; ldr x8,[x0,#0x30] ; cmp x8,#1`. */
long sk_r38_copy_head_cmp_30(word_t *dst, const word_t *src)
{
    *dst = *src;
    return (long)*(const word_t *)((byte *)dst + 0x30) - 1;
}

