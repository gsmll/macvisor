/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R65: 0x458d68-0x45bcb0. This is a Swift-runtime region that manages
 * strongly-reference-counted boxed values / owned value slots: a family of
 * value-destroy (release) and value-assign (copy + retain/release) helpers
 * driven by a small operation selector in the w4 register (or an 8-bit
 * selector byte), plus a set of one-time global-initializer gate functions
 * that lazily build a Swift object behind a check-once flag. The op codes
 * seen are 0/1/2 (and a few 3/4/7/0xb/0xc/0xd/0xe) and select between
 * releasing field 0 / field 1 / an inline box / an owned indirect box.
 * All names are estimates unless string-matched.
 *
 * Calling-convention note: retain = sk_refcount_acquire_c (FUN_0036b270),
 * release = sk_refcount_release_b (FUN_0036b118), release-with-low-tag-mask
 * = addr_mask_release (FUN_003a25d4). These are the reference-count
 * primitives the whole region is built on. Ghidra FUN_ names are kept only
 * in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;
typedef unsigned int uint;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Shared kernel/runtime helpers (bodies live in other slice files; the
 * FUN_ address in each comment is ground truth).
 * ------------------------------------------------------------------ */
extern void  sk_refcount_release_b(word_t obj);            /* FUN_0036b118 */
extern void  sk_refcount_acquire_c(word_t obj);            /* FUN_0036b270 */
extern void  addr_mask_release(word_t obj);                /* FUN_003a25d4 (release, low tag masked off) */
extern void  sk_obj_destroy_check(void);                   /* FUN_0036b21c */
extern word_t sk_obj_resolve_forward(word_t arg, word_t arg2); /* FUN_00376820 */
extern cL4_w16_t sk_word_copy(word_t *p);                  /* FUN_0034f2f4 */
extern cL4_w16_t exc_restore_2b20(void);                   /* FUN_00352b20 */
extern void   *sk_f_0034d454(void);                        /* FUN_0034d454 */
extern void   *sk_sys_stub_04d0(void);                     /* FUN_003504d0 */
extern void   *sk_003504d0(void);   /* alias */
extern void    sk_syscall_save_ret(void);                  /* FUN_00350c5c */
extern cL4_w16_t sk_frame_copy16(void);                    /* FUN_00355938 */
extern cL4_w16_t sk_00355938(void);   /* alias */
extern cL4_w16_t sk_pair_make(void);                       /* FUN_00355968 */
extern void    sk_release_666c0(void);                     /* FUN_004666c0 */
extern void    swift_runtime_stub_noop(void);              /* FUN_0034f8e4 / FUN_0034f3b4 */
extern void    cL4_nop_handler(void);                      /* FUN_00084220 / FUN_00084234 */
extern void    sk_copy16(void);                            /* FUN_00350e04 */
extern void    sk_store_regs_640d0(word_t a0,word_t a1,word_t a2,word_t a3,word_t a4,
                                   word_t a5,word_t a6,word_t a7,word_t a8,word_t a9,
                                   word_t a10,word_t a11,word_t a12,word_t a13); /* FUN_004640d0 */
extern void    sk_rt_463154(void);                         /* FUN_00463154 */
extern void    sk_noop_463504(void);                       /* FUN_00463504 */
extern void    sk_noop_c444(void);                         /* FUN_0034c444 */
extern cL4_w16_t sk_rt_46306c(void);                       /* FUN_0046306c */
extern void    sk_cmp_462bd8(word_t a);                    /* FUN_00462bd8 */
extern void    sk_rt_462e54(word_t a);                     /* FUN_00462e54 */
extern void    sk_noop_462e88(word_t a);                   /* FUN_00462e88 */
extern void    sk_rt_462fec(void);                         /* FUN_00462fec */
extern void    sk_rt_463028(word_t a,word_t b,word_t c,word_t d); /* FUN_00463028 */
extern void    sk_rt_46303c(void);                         /* FUN_0046303c */
extern void    sk_noop_463058(void);                       /* FUN_00463058 */
extern void    sk_rt_463080(void);                         /* FUN_00463080 */
extern void    sk_cmp_4632b8(void);                        /* FUN_004632b8 */
extern void    sk_rt_463358(word_t a);                     /* FUN_00463358 */
extern void    sk_rt_46337c(void);                         /* FUN_0046337c */
extern void    sk_cmp_463484(void);                        /* FUN_00463484 */
extern void    sk_copy_words_18_20(void);                  /* FUN_00463750 */
extern void    sk_store19_words(void);                     /* FUN_004638d8 */
extern void    sk_copy_field_pair(void);                   /* FUN_00463a10 */
extern void    sk_copy_byte_18(void);                      /* FUN_00463a48 */
extern void    sk_load16_40(void);                         /* FUN_00463aa0 */
extern void    sk_copy_word_640b8(void);                   /* FUN_004640b8 */
extern void    sk_copy_word_64504(void);                   /* FUN_00464504 */
extern void    sk_copy_fields_645d8(void);                 /* FUN_004645d8 */
extern void    sk_nop_464ae8(void);                        /* FUN_00464ae8 */
extern void   *sk_nop_464b04(void);                        /* FUN_00464b04 */
extern void    sk_gate_4627d0(void);                       /* FUN_004627d0 */
extern void    sk_syscall_stub_34db28(void);               /* FUN_0034db28 */
extern void    sk_copy_field_10_464dcc(void);              /* FUN_00464dcc */
extern void    sk_fwd_45a4b4_464e9c(void);                 /* FUN_00464e9c */
extern void    sk_copy2words_53cc(void);                   /* FUN_004653cc */
extern void    sk_fwd_54ec(void);                          /* FUN_004654ec */
extern void    sk_copy2words_56e0(void);                   /* FUN_004656e0 */
extern void    sk_copy2bytes_5770(void);                   /* FUN_00465770 */
extern void    sk_copy5words_5a50(void);                   /* FUN_00465a50 */
extern void    sk_store_load_ref_5b1c(void);               /* FUN_00465b1c */
extern void    sk_copy2words_5d28(void);                   /* FUN_00465d28 */
extern void    sk_copy6words_5eec(void);                   /* FUN_00465eec */
extern void    sk_copy5words_5f20(void);                   /* FUN_00465f20 */
extern void    sk_copy2words_5f68(void);                   /* FUN_00465f68 */
extern void    sk_copy2words_6034(void);                   /* FUN_00466034 */
extern void    sk_copy2words_61a4(void);                   /* FUN_004661a4 */
extern void    sk_nop_661fc(void);                         /* FUN_004661fc */
extern void    sk_copy_word_66220(void);                   /* FUN_00466220 */
extern void    sk_copy_fields_66374(void);                 /* FUN_00466374 */
extern void    sk_nop_663ec(void);                         /* FUN_004663ec */
extern cL4_w16_t sk_466408(void);                         /* FUN_00466408 */
extern void    sk_global_init_gate(void);                  /* FUN_00462758 */
extern void    sk_global_store(void);                      /* FUN_00460d50 */
extern void    sk_global_gate2(void);                      /* FUN_004627d0 */
extern void    sk_462b90(void);                            /* FUN_00462b90 */
extern void    sk_462848(void);                            /* FUN_00462848 */
extern void    sk_460ae4(void);                            /* FUN_00460ae4 */
extern void    sk_5c89c(void *obj);                        /* FUN_0045c89c */
extern void    sk_5e45c(void);                             /* FUN_0045e45c */
extern void    sk_5e484(word_t a, word_t b);               /* FUN_0045e484 */
extern void    sk_5ee90(word_t a, word_t b);               /* FUN_0045ee90 */
extern void    sk_5fc8c(void);                             /* FUN_0045fc8c */
extern void    sk_61dc4(word_t a, word_t b);               /* FUN_00461dc4 */
extern void    sk_55574(word_t a, word_t b, word_t c, word_t d, word_t e); /* FUN_00455574 */
extern void    sk_588cc(void);                             /* FUN_004588cc */
extern void    sk_58940(word_t, word_t, word_t, word_t);   /* FUN_00458940 */
extern void    sk_58b94(word_t, word_t, word_t, word_t);   /* FUN_00458b94 */
extern void    sk_58bac(void);                             /* FUN_00458bac */
extern void    sk_4663ec(word_t a, word_t b);              /* FUN_004663ec */
extern long    sk_464644(word_t a, word_t b, word_t c);    /* FUN_004644cc */
extern void    sk_46350(void);                             /* FUN_00463504 */
extern void    sk_4640d0(void);                            /* FUN_004640d0 */
extern void    sk_464ae8(word_t a, word_t b);              /* FUN_00464ae8 */
extern void   *sk_464b04(word_t a);                        /* FUN_00464b04 */
extern void    sk_464dcc(void);                            /* FUN_00464dcc */
extern void    sk_464e9c(void);                            /* FUN_00464e9c */
extern void    sk_4653cc(void);                            /* FUN_004653cc */
extern void    sk_4654ec(void);                            /* FUN_004654ec */
extern void    sk_4656e0(void);                            /* FUN_004656e0 */
extern void    sk_465770(void);                            /* FUN_00465770 */
extern void    sk_465a50(void);                            /* FUN_00465a50 */
extern void    sk_465b1c(void);                            /* FUN_00465b1c */
extern void    sk_465d28(void);                            /* FUN_00465d28 */
extern void    sk_465eec(void);                            /* FUN_00465eec */
extern void    sk_465f20(void);                            /* FUN_00465f20 */
extern void    sk_465f68(void);                            /* FUN_00465f68 */
extern void    sk_466034(void);                            /* FUN_00466034 */
extern void    sk_4661a4(void);                            /* FUN_004661a4 */
extern void    sk_466220(void);                            /* FUN_00466220 */
extern void    sk_466374(void);                            /* FUN_00466374 */
extern void    sk_4666c0(void);                            /* FUN_004666c0 */
extern void    sk_4607c4(void *obj, word_t arg, void (*fn)(void)); /* FUN_004607c4 */
extern void    sk_460d(word_t a);                          /* FUN_00460d50 */
extern void    sk_4629(void);                              /* FUN_00462948 */

/* runtime data references (opaque address constants). */
extern byte DAT_005a2018, DAT_005a2ca8, DAT_005a2db0, DAT_005a26cc, DAT_005a2cb0,
    DAT_005a2e08, DAT_005a2e60, DAT_005a2eb8, DAT_005a2f10, DAT_004ea7c8,
    DAT_004ea794, DAT_004eb028, DAT_004eb078, DAT_004ea760, DAT_004bbe30,
    DAT_0064c2d8, DAT_0064c2e0, DAT_0045961c;
extern void sk_word_copy_3(void);   /* FUN_0034b264 */


/* ------------------------------------------------------------------ *
 * Slice R65 function bodies.
 * ------------------------------------------------------------------ */

/* Missing low-level helpers (FUN_ address in comments). */
extern void    sk_0001a1cc(void);            /* FUN_0001a1cc */
extern void    sk_00021480(void);            /* FUN_00021480 */
extern cL4_w16_t sk_00355968(void);          /* FUN_00355968 */
extern cL4_w16_t sk_00002534(void);          /* FUN_00002534 */
extern void    sk_003509c8(word_t a, word_t b, word_t c, word_t d); /* FUN_003509c8 */
extern void    sk_indirect_10(void);         /* indirect call through slot +0x10 */
extern void    sk_00002850(void);            /* FUN_00002850 */
extern void    sk_00002834(void);            /* FUN_00002834 */
extern void    sk_00350af4(word_t a, word_t b, word_t *c); /* FUN_00350af4 */
extern void    sk_00027754(word_t a);        /* FUN_00027754 */
extern void    sk_00027614(word_t a, word_t b); /* FUN_00027614 */
extern cL4_w16_t sk_00027670(void);          /* FUN_00027670 */
extern void    sk_0006b6f4(word_t a, word_t b, word_t *c); /* FUN_0006b6f4 */
extern void    sk_0010a9f8(void);            /* FUN_0010a9f8 */
extern void    sk_464f40(word_t a);          /* FUN_00464f40 */
extern void    sk_465884(void);              /* FUN_00465884 */
extern void    sk_00355538(void);            /* FUN_00355538 */
extern void    sk_00114330(word_t *p, word_t n); /* thunk_FUN_00114330 */
extern void    sk_global_2cb0_store(word_t v);   /* store into 0x657a60 slot */
extern cL4_w16_t sk_call_pair_slot(word_t fn);   /* indirect call through pair slot */

/* Forward declarations of slice-internal statics that call each other. */
static void sk_rt_458f00(word_t, word_t, word_t, word_t, uint);
static void sk_rt_458f9c(word_t, word_t, word_t, word_t, uint);
static void sk_rt_459280(word_t, word_t, word_t, word_t, byte);
static void sk_rt_4592dc(word_t, word_t, word_t, word_t, byte);
static void sk_rt_4592f4(word_t, word_t, word_t, word_t, word_t, word_t, word_t, byte);
static void sk_rt_459138(word_t, word_t, word_t, word_t, word_t, word_t, word_t, word_t, byte);
static void sk_rt_459888(word_t, word_t);
static void sk_rt_459768(word_t, word_t, word_t);
static word_t sk_rt_459698(void);
static word_t sk_rt_459800(void);
static void sk_rt_45a1f8(word_t, word_t, word_t, word_t, byte);
static void sk_rt_45a5fc(word_t, word_t, word_t, word_t, byte);
static void sk_rt_45a658(word_t, word_t, word_t, word_t, word_t, word_t, word_t, byte);
static void sk_rt_45a4b4(word_t, word_t, word_t, word_t, word_t, word_t, word_t, word_t, byte);
static void sk_rt_45b1a0(word_t, word_t, void (*)(void));
static void sk_rt_459b6c(void);
static void sk_rt_4593ac(unsigned long);
static void sk_rt_45aa44(word_t *, uint, uint);
static void sk_rt_45a904(word_t *, uint, uint);



/* FUN_00458d68 @ 0x00458d68  (est. sk_rt_destroy_then_copy)
 * Destroy helper: forwards both arguments to the shared copy routine
 * FUN_0045e484. Confidence: medium (structural). */
static void sk_rt_458d68(word_t a, word_t b)
{
    sk_5e484(b, a);
}

/* FUN_00458d78 @ 0x00458d78  (est. sk_rt_teardown_ret)
 * Teardown helper: runs FUN_0045e45c and returns its first argument
 * unchanged. Confidence: medium (structural). */
static word_t sk_rt_458d78(word_t a)
{
    sk_5e45c();
    return a;
}

/* FUN_00458da0 @ 0x00458da0  (est. sk_rt_copy_then_store)
 * Copy helper: forwards both arguments to FUN_0045ee90.
 * Confidence: medium (structural). */
static void sk_rt_458da0(word_t a, word_t b)
{
    sk_5ee90(b, a);
}

/* FUN_00458db4 @ 0x00458db4  (est. sk_rt_destroy_op)
 * Value-destroy dispatcher on the 8-bit selector byte in the stack frame.
 * op 2: release param_4 and the x7 register value; op 1: addr-mask-release
 * x7; op 0: addr-mask-release param_2; anything else: no-op.
 * Confidence: medium (structural). */
static void sk_rt_458db4(word_t p2, word_t p4, word_t x7, byte op)
{
    if (op == 2) { sk_refcount_release_b(p4); sk_refcount_release_b(x7); return; }
    if (op == 1) { addr_mask_release(x7); }
    else if (op != 0) return;
    addr_mask_release(p2);
}

/* FUN_00458e28 @ 0x00458e28  (est. sk_rt_object_op_ret)
 * Forwards to FUN_0045c89c and returns the input argument unchanged.
 * Confidence: medium (structural). */
static word_t sk_rt_458e28(word_t a)
{
    sk_5c89c((void*)a);
    return a;
}

/* FUN_00458e50 @ 0x00458e50  (est. sk_rt_slice_end)
 * Returns (address + 8) + the signed 32-bit length at offset +8 of the
 * object, following the tag bit to a pointer if set (inline-payload size
 * accessor). Confidence: medium (structural). */
static long sk_rt_458e50(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_00458e80 @ 0x00458e80  (est. sk_rt_destroy_op_small)
 * op-destroy dispatcher: op 0 addr-mask-releases param_2; op 1/2 releases
 * the register-held value; else no-op. Confidence: medium (structural). */
static void sk_rt_458e80(word_t p1, word_t p2, word_t p3, byte op)
{
    if ((op != 2) && (op != 1)) {
        if (op == 0) { addr_mask_release(p2); return; }
        return;
    }
    sk_refcount_release_b(0);
}

/* FUN_00458ea8 @ 0x00458ea8  (est. sk_rt_box_copy5)
 * Copies a 5-word (0x28-byte) box payload from param_1 to param_2, then
 * calls FUN_0001a1cc. Confidence: medium (structural). */
static void sk_rt_458ea8(word_t *src, word_t *dst)
{
    word_t w1, w2, w3, w4;
    w2 = src[1]; w1 = *src; w4 = src[3]; w3 = src[2];
    dst[4] = src[4];
    dst[1] = w2; *dst = w1; dst[3] = w4; dst[2] = w3;
    sk_0001a1cc();
}

/* FUN_00458ebc @ 0x00458ebc  (est. sk_rt_slice_end_c)
 * Returns (address + 0xc) + the signed 32-bit length at offset +0xc,
 * following the tag bit to a pointer if set. Confidence: medium. */
static long sk_rt_458ebc(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_00458eec @ 0x00458eec  (est. sk_rt_gate_w4)
 * Guard: if the w4 selector is not -1, forwards to FUN_00458f00.
 * Confidence: medium (structural). */
static void sk_rt_458eec(void)
{
    sk_rt_458f00(0,0,0,0,0);
}

/* FUN_00458f00 @ 0x00458f00  (est. sk_rt_retain_selector)
 * Selector-driven retain dispatcher over up to 36 value slots. Bitmaps
 * 0x363fbff5f and 0x800040000 select which fields get retained/forwarded.
 * Confidence: medium (structural). */
static void sk_rt_458f00(word_t p1, word_t p2, word_t p3, word_t p4, uint sel)
{
    unsigned long bit;
    if (0x23 < (sel & 0xff)) return;
    bit = 1UL << (sel & 0x3f);
    if ((bit & 0x363fbff5fUL) == 0) {
        if ((bit & 0x800040000UL) == 0) return;
        sk_refcount_acquire_c(p2);
        p2 = p4;
    }
    sk_refcount_acquire_c(p2);
}

/* FUN_00458f88 @ 0x00458f88  (est. sk_rt_gate_w4b)
 * Guard: if the w4 selector is not -1, forwards to FUN_00458f9c.
 * Confidence: medium (structural). */
static void sk_rt_458f88(void)
{
    sk_rt_458f9c(0,0,0,0,0);
}

/* FUN_00458f9c @ 0x00458f9c  (est. sk_rt_release_selector)
 * Selector-driven release dispatcher over up to 36 value slots, using the
 * same bitmap families as FUN_00458f00 but releasing instead of retaining.
 * Confidence: medium (structural). */
static void sk_rt_458f9c(word_t p1, word_t p2, word_t p3, word_t p4, uint sel)
{
    word_t u;
    unsigned long bit, s;
    if (0x23 < (sel & 0xff)) return;
    s = (unsigned long)sel & 0xff;
    bit = 1UL << (sel & 0x3f);
    if ((bit & 0x363fbff5fUL) == 0) {
        u = p4;
        if ((s != 0x12) && (u = p2, p2 = p4, s != 0x23)) return;
        addr_mask_release(u);
    }
    addr_mask_release(p2);
}


/* FUN_00459024 @ 0x00459024  (est. sk_rt_copy_then_destroy)
 * Copy helper: forwards both arguments to FUN_00461dc4.
 * Confidence: medium (structural). */
static void sk_rt_459024(word_t a, word_t b)
{
    sk_61dc4(b, a);
}

/* FUN_00459034 @ 0x00459034  (est. sk_rt_forward_21480)
 * Forwards to FUN_00021480. Confidence: medium (structural). */
static void sk_rt_459034(void)
{
    sk_00021480();
}

/* FUN_0045904c @ 0x0045904c  (est. sk_rt_run_then_ret)
 * Runs FUN_00460ae4 and returns the input argument unchanged.
 * Confidence: medium (structural). */
static word_t sk_rt_45904c(word_t a)
{
    sk_460ae4();
    return a;
}

/* FUN_00459074 @ 0x00459074  (est. sk_rt_forward_21480b)
 * Forwards to FUN_00021480. Confidence: medium (structural). */
static void sk_rt_459074(void)
{
    sk_00021480();
}

/* FUN_0045908c @ 0x0045908c  (est. sk_rt_dispatch_indirect)
 * Indirect dispatch: runs three setup helpers, calls FUN_00002534 for a
 * 16-byte pair, then calls through the function-pointer slot at offset
 * +0x10 of a register-held object. Confidence: medium (structural). */
static void sk_rt_45908c(void)
{
    cL4_w16_t pair;
    sk_sys_stub_04d0();
    sk_00355968();
    pair = sk_00002534();
    sk_003509c8(pair.lo, pair.lo, pair.hi, pair.lo);
    sk_indirect_10();
}

/* FUN_004590e0 @ 0x004590e0  (est. sk_rt_run_then_retb)
 * Runs FUN_0045fc8c and returns the input argument unchanged.
 * Confidence: medium (structural). */
static word_t sk_rt_4590e0(word_t a)
{
    sk_5fc8c();
    return a;
}

/* FUN_0045910c @ 0x0045910c  (est. sk_rt_destroy_field28)
 * Releases the refcounted field at +0x28, runs FUN_00002850, then the
 * destroy-check. Confidence: medium (structural). */
static void sk_rt_45910c(word_t *obj)
{
    sk_refcount_release_b(*(word_t *)((char*)obj + 0x28));
    sk_00002850();
    sk_obj_destroy_check();
}

/* FUN_00459110 @ 0x00459110  (est. sk_rt_destroy_field28b)
 * Same as FUN_0045910c. Confidence: medium (structural). */
static void sk_rt_459110(word_t *obj)
{
    sk_refcount_release_b(*(word_t *)((char*)obj + 0x28));
    sk_00002850();
    sk_obj_destroy_check();
}

/* FUN_00459138 @ 0x00459138  (est. sk_rt_destroy_big_dispatch)
 * Multi-way value-destroy dispatcher on a 4-bit selector (selector byte
 * >> 4). Case 2/0xd release via sk_refcount_release_b; case 3/9/10/0xb
 * forward to narrower destroy helpers; default addr-mask-releases the
 * forwarded field. Confidence: medium (structural). */
static void sk_rt_459138(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5,
                         word_t p6, word_t p7, word_t p8, byte sel)
{
    switch (sel >> 4) {
    default: p5 = p2; break;
    case 1: case 4: return;
    case 2: sk_refcount_release_b(0); p2 = p8; sk_refcount_release_b(p2); return;
    case 3: sk_rt_459280(p1, p2, 0, 0, 0); return;
    case 9: case 10: sk_rt_4592dc(p1, p2, 0, 0, 0); return;
    case 0xb: sk_rt_4592f4(p1, p2, 0, 0, 0, 0, 0, 0); return;
    case 0xc: break;
    case 0xd: sk_refcount_release_b(p4); p2 = p8;
              sk_refcount_release_b(p2); return;
    }
    addr_mask_release(p5);
}

/* FUN_00459280 @ 0x00459280  (est. sk_rt_destroy_owned_box)
 * Destroy dispatcher: op 4 addr-mask-releases param_2; op 0xe
 * addr-mask-releases param_4; op 7 releases param_3.
 * Confidence: medium (structural). */
static void sk_rt_459280(word_t p1, word_t p2, word_t p3, word_t p4, byte op)
{
    if (op != 4) {
        if (op == 0xe) { addr_mask_release(p4); }
        else { p2 = p3; if (op != 7) return; }
    }
    addr_mask_release(p2);
}

/* FUN_004592dc @ 0x004592dc  (est. sk_rt_destroy_small)
 * Destroy helper: op 2 addr-mask-releases param_2; else no-op.
 * Confidence: medium (structural). */
static void sk_rt_4592dc(word_t p1, word_t p2, word_t p3, word_t p4, byte op)
{
    if (op == 2) { addr_mask_release(p2); return; }
    (void)p1; (void)p3; (void)p4;
}

/* FUN_004592f4 @ 0x004592f4  (est. sk_rt_destroy_multi)
 * Multi-field destroy dispatcher. op 2: addr-mask-release param_4 and the
 * +0x18 stack value; op 1: addr-mask-release param_2 and x7, release +0x30;
 * op 0: forward to FUN_00458bac. Confidence: medium (structural). */
static void sk_rt_4592f4(word_t p1, word_t p2, word_t p3, word_t p4, word_t x7,
                         word_t s18, word_t s30, byte op)
{
    if (op == 2) { addr_mask_release(p4); addr_mask_release(s18); return; }
    if (op != 1) {
        if (op == 0) { sk_58bac(); return; }
        return;
    }
    addr_mask_release(p2);
    addr_mask_release(x7);
    sk_refcount_release_b(s30);
}

/* FUN_00459384 @ 0x00459384  (est. sk_rt_destroy_frame18)
 * Releases the field at +0x18, runs FUN_00355538, then destroy-check.
 * Confidence: medium (structural). */
static void sk_rt_459384(word_t *obj)
{
    addr_mask_release(*(word_t *)((char*)obj + 0x18));
    sk_00355538();
    sk_obj_destroy_check();
}

/* FUN_00459388 @ 0x00459388  (est. sk_rt_destroy_frame18b)
 * Same as FUN_00459384. Confidence: medium (structural). */
static void sk_rt_459388(word_t *obj)
{
    addr_mask_release(*(word_t *)((char*)obj + 0x18));
    sk_00355538();
    sk_obj_destroy_check();
}

/* FUN_004593ac @ 0x004593ac  (est. sk_rt_destroy_tagged)
 * Destroy dispatcher on the low 3 tag bits of the stack value at +0x28.
 * tag 3: forward to FUN_00458db4 then release (masked); tag 1 or 0: forward
 * to FUN_004592dc; other non-zero tags: no-op. Confidence: medium. */
static void sk_rt_4593ac(unsigned long s28)
{
    uint tag = (uint)s28 & 7;
    if (tag == 3) {
        sk_rt_458db4(0,0,0,0);
        sk_refcount_release_b(s28 & 0xffffffffffffff8);
        return;
    }
    if ((tag != 1) && ((s28 & 7) != 0)) return;
    sk_rt_4592dc(0,0,0,0,0);
}

/* FUN_0045942c @ 0x0045942c  (est. sk_rt_destroy_frame50)
 * Object destroy: runs several teardown helpers and releases the field at
 * +0x78 (low tag masked off). Confidence: medium (structural). */
static void sk_rt_45942c(word_t *obj)
{
    sk_0010a9f8();
    sk_464f40(*(word_t *)((char*)obj + 0x50));
    sk_rt_458db4(0,0,0,0);
    sk_refcount_release_b(*(unsigned long *)((char*)obj + 0x78) & 0xfffffffffffffff);
    sk_465884();
    sk_obj_destroy_check();
}

/* FUN_0045947c @ 0x0045947c  (est. sk_rt_slice_end_4)
 * Returns (address + 4) + the signed 32-bit length at offset +4, following
 * the tag bit to a pointer if set. Confidence: medium (structural). */
static long sk_rt_45947c(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}


/* FUN_004594c4 @ 0x004594c4  (est. sk_rt_destroy_field18_2834)
 * Releases the field at +0x18, runs FUN_00002834, then destroy-check.
 * Confidence: medium (structural). */
static void sk_rt_4594c4(word_t *obj)
{
    sk_refcount_release_b(*(word_t *)((char*)obj + 0x18));
    sk_00002834();
    sk_obj_destroy_check();
}

/* FUN_004594c8 @ 0x004594c8  (est. sk_rt_destroy_field18_2834b)
 * Same as FUN_004594c4. Confidence: medium (structural). */
static void sk_rt_4594c8(word_t *obj)
{
    sk_refcount_release_b(*(word_t *)((char*)obj + 0x18));
    sk_00002834();
    sk_obj_destroy_check();
}

/* FUN_004594f4 @ 0x004594f4  (est. sk_rt_build_frame_55574)
 * Builds a value frame: forwards the two arguments plus three register-held
 * fields (+0x10/+0x18/+0x20 of a frame object) to FUN_00455574.
 * Confidence: medium (structural). */
static void sk_rt_4594f4(word_t a, word_t b, word_t *obj)
{
    sk_55574(a, b, *(word_t *)((char*)obj + 0x10),
             *(word_t *)((char*)obj + 0x18), *(word_t *)((char*)obj + 0x20));
}

/* FUN_004594f8 @ 0x004594f8  (est. sk_rt_build_frame_55574b)
 * Same as FUN_004594f4. Confidence: medium (structural). */
static void sk_rt_4594f8(word_t a, word_t b, word_t *obj)
{
    sk_55574(a, b, *(word_t *)((char*)obj + 0x10),
             *(word_t *)((char*)obj + 0x18), *(word_t *)((char*)obj + 0x20));
}

/* FUN_00459514 @ 0x00459514  (est. sk_rt_global_init_2018)
 * One-time global initializer for the object at 0x657a40/0x657a48: gates on
 * the string DAT_005a2018 then stores. Confidence: medium (structural). */
static void sk_rt_459514(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459518 @ 0x00459518  (est. sk_rt_global_init_2018b)
 * One-time global initializer: gates on 0x657a40/0x657a48 and DAT_005a2018,
 * then stores. Confidence: medium (structural). */
static void sk_rt_459518(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459548 @ 0x00459548  (est. sk_rt_global_init_26cc)
 * One-time global initializer that builds an object behind DAT_005a26cc and
 * stores it at +8 of a frame object. Confidence: medium (structural). */
static void sk_rt_459548(word_t a, word_t b, word_t *obj)
{
    word_t v;
    sk_sys_stub_04d0();
    sk_00027754(*obj);
    v = sk_obj_resolve_forward((word_t)&DAT_005a26cc, 0);
    *(word_t *)((char*)obj + 8) = v;
}

/* FUN_004595a0 @ 0x004595a0  (est. sk_rt_global_init_4ea7c8)
 * One-time global initializer for the object at 0x656378 built behind
 * DAT_004ea7c8. Confidence: medium (structural). */
static void sk_rt_4595a0(void)
{
    sk_rt_459888(0x656378, (word_t)&DAT_004ea7c8);
}

/* FUN_004595a4 @ 0x004595a4  (est. sk_rt_global_init_4ea7c8b)
 * Same as FUN_004595a0. Confidence: medium (structural). */
static void sk_rt_4595a4(void)
{
    sk_rt_459888(0x656378, (word_t)&DAT_004ea7c8);
}

/* FUN_004595d4 @ 0x004595d4  (est. sk_rt_global_init_4eb078)
 * One-time global initializer at 0x657a50 built behind DAT_004eb078, using
 * FUN_00459768 with a trampoline at DAT_0045961c. Confidence: medium. */
static void sk_rt_4595d4(void)
{
    sk_rt_459768(0x657a50, (word_t)&DAT_0045961c, (word_t)&DAT_004eb078);
}

/* FUN_004595d8 @ 0x004595d8  (est. sk_rt_global_init_4eb078b)
 * Same as FUN_004595d4. Confidence: medium (structural). */
static void sk_rt_4595d8(void)
{
    sk_rt_459768(0x657a50, (word_t)&DAT_0045961c, (word_t)&DAT_004eb078);
}

/* FUN_0045962c @ 0x0045962c  (est. sk_rt_global_init_2cb0)
 * One-time global initializer: resolves the object behind DAT_005a2cb0 with
 * the 0x685478 fallback and stores it into the 0x657a60 slot (a read-only
 * region write warning was emitted by the decompiler). Confidence: medium. */
static void sk_rt_45962c(void)
{
    sk_global_2cb0_store(sk_obj_resolve_forward((word_t)&DAT_005a2cb0, 0x685478));
}

/* FUN_00459630 @ 0x00459630  (est. sk_rt_global_init_2cb0b)
 * Same as FUN_0045962c. Confidence: medium (structural). */
static void sk_rt_459630(void)
{
    sk_global_2cb0_store(sk_obj_resolve_forward((word_t)&DAT_005a2cb0, 0x685478));
}

/* FUN_00459670 @ 0x00459670  (est. sk_rt_store_global)
 * Stores the value produced by FUN_00459698 into offset +8 of param_1.
 * Confidence: medium (structural). */
static void sk_rt_459670(word_t *obj)
{
    *(word_t *)((char*)obj + 8) = sk_rt_459698();
}

/* FUN_00459698 @ 0x00459698  (est. sk_rt_global_slot_657a68)
 * Returns the 64-bit constant 0xf9004030dac10230 stored in the 0x657a68
 * global slot (the decompiler collapsed the body to a single store with an
 * unreachable tail). Confidence: medium (structural). */
static word_t sk_rt_459698(void)
{
    return 0xf9004030dac10230UL;
}

/* FUN_004596ec @ 0x004596ec  (est. sk_rt_global_init_4ea794)
 * One-time global initializer for the object at 0x656380 built behind
 * DAT_004ea794. Confidence: medium (structural). */
static void sk_rt_4596ec(void)
{
    sk_rt_459888(0x656380, (word_t)&DAT_004ea794);
}

/* FUN_004596f0 @ 0x004596f0  (est. sk_rt_global_init_4ea794b)
 * Same as FUN_004596ec. Confidence: medium (structural). */
static void sk_rt_4596f0(void)
{
    sk_rt_459888(0x656380, (word_t)&DAT_004ea794);
}

/* FUN_00459720 @ 0x00459720  (est. sk_rt_global_init_4eb028)
 * One-time global initializer at 0x657a70 built behind DAT_004eb028, using
 * FUN_00459768 with the FUN_00459698 trampoline. Confidence: medium. */
static void sk_rt_459720(void)
{
    sk_rt_459768(0x657a70, (word_t)&sk_rt_459698, (word_t)&DAT_004eb028);
}

/* FUN_00459724 @ 0x00459724  (est. sk_rt_global_init_4eb028b)
 * Same as FUN_00459720. Confidence: medium (structural). */
static void sk_rt_459724(void)
{
    sk_rt_459768(0x657a70, (word_t)&sk_rt_459698, (word_t)&DAT_004eb028);
}

/* FUN_00459768 @ 0x00459768  (est. sk_rt_global_init_core)
 * Core one-time global initializer: gates on the 16-byte pair from
 * FUN_00352b20; if not yet initialized, bootstraps with FUN_00027614 (arg
 * 0x657a58, string DAT_005a2ca8), calls through the pair's function slot to
 * build a 16-byte value, forwards it through FUN_00350af4, then resolves the
 * object via FUN_00376820 and stores it into the target slot.
 * Confidence: medium (structural). */
static void sk_rt_459768(word_t dst, word_t tramp, word_t str)
{
    cL4_w16_t pair = exc_restore_2b20();
    word_t v;
    if (pair.lo == 0) {
        sk_00027614(0x657a58, (word_t)&DAT_005a2ca8);
        pair = sk_call_pair_slot(pair.hi);
        sk_00350af4(pair.lo, pair.hi, (word_t *)&pair.lo);
        v = sk_obj_resolve_forward(0, 0);
        *(word_t*)dst = v;
    }
}

/* FUN_004597d8 @ 0x004597d8  (est. sk_rt_store_global_b)
 * Stores the value produced by FUN_00459800 into offset +8 of param_1.
 * Confidence: medium (structural). */
static void sk_rt_4597d8(word_t *obj)
{
    *(word_t *)((char*)obj + 8) = sk_rt_459800();
}

/* FUN_00459800 @ 0x00459800  (est. sk_rt_global_slot_657a78)
 * Returns the 64-bit constant 0xdac10230d29170b1 stored in the 0x657a78
 * global slot (decompiler collapsed body to a single store with an
 * unreachable tail). Confidence: medium (structural). */
static word_t sk_rt_459800(void)
{
    return 0xdac10230d29170b1UL;
}

/* FUN_00459854 @ 0x00459854  (est. sk_rt_global_init_4ea760)
 * One-time global initializer for the object at 0x64c2e0 built behind
 * DAT_004ea760. Confidence: medium (structural). */
static void sk_rt_459854(void)
{
    sk_rt_459888((word_t)&DAT_0064c2e0, (word_t)&DAT_004ea760);
}

/* FUN_00459858 @ 0x00459858  (est. sk_rt_global_init_4ea760b)
 * Same as FUN_00459854. Confidence: medium (structural). */
static void sk_rt_459858(void)
{
    sk_rt_459888((word_t)&DAT_0064c2e0, (word_t)&DAT_004ea760);
}

/* FUN_00459888 @ 0x00459888  (est. sk_rt_global_init_generic)
 * Generic one-time global initializer: gates on the 16-byte pair from
 * FUN_00352b20; if not yet initialized, bootstraps with FUN_00027614
 * (strings DAT_0064c2d8 / DAT_004bbe30), calls FUN_00027670 for a 16-byte
 * value, merges it through FUN_0006b6f4 with the 0x6720e8 frame address,
 * then resolves the object via FUN_00376820 into the target slot.
 * Confidence: medium (structural). */
static void sk_rt_459888(word_t slot, word_t str)
{
    cL4_w16_t pair = exc_restore_2b20();
    cL4_w16_t b;
    word_t v;
    if (pair.lo == 0) {
        sk_00027614((word_t)&DAT_0064c2d8, (word_t)&DAT_004bbe30);
        pair = sk_00027670();
        b = pair;
        sk_0006b6f4(b.lo, b.hi, (word_t*)0x6720e8);
        v = sk_obj_resolve_forward(0, 0);
        *(word_t*)slot = v;
    }
}



/* FUN_00459900 @ 0x00459900  (est. sk_rt_global_init_2db0)
 * One-time global initializer: gates on 0x657a80/0x657a88 + DAT_005a2db0
 * then stores. Confidence: medium (structural). */
static void sk_rt_459900(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459904 @ 0x00459904  (est. sk_rt_global_init_2db0b)
 * Same as FUN_00459900. Confidence: medium (structural). */
static void sk_rt_459904(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459934 @ 0x00459934  (est. sk_rt_global_init_2e08)
 * One-time global initializer for 0x657a90/0x657a98 + DAT_005a2e08.
 * Confidence: medium (structural). */
static void sk_rt_459934(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459938 @ 0x00459938  (est. sk_rt_global_init_2e08b)
 * Same as FUN_00459934. Confidence: medium (structural). */
static void sk_rt_459938(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459968 @ 0x00459968  (est. sk_rt_global_init_2e60)
 * One-time global initializer for 0x657aa0/0x657aa8 + DAT_005a2e60.
 * Confidence: medium (structural). */
static void sk_rt_459968(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_0045996c @ 0x0045996c  (est. sk_rt_global_init_2e60b)
 * Same as FUN_00459968. Confidence: medium (structural). */
static void sk_rt_45996c(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_0045999c @ 0x0045999c  (est. sk_rt_global_init_2eb8)
 * One-time global initializer for 0x657ab0/0x657ab8 + DAT_005a2eb8.
 * Confidence: medium (structural). */
static void sk_rt_45999c(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_004599a0 @ 0x004599a0  (est. sk_rt_global_init_2eb8b)
 * Same as FUN_0045999c. Confidence: medium (structural). */
static void sk_rt_4599a0(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_004599d0 @ 0x004599d0  (est. sk_rt_global_init_2f10)
 * One-time global initializer for 0x657ac0/0x657ac8 + DAT_005a2f10.
 * Confidence: medium (structural). */
static void sk_rt_4599d0(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_004599d4 @ 0x004599d4  (est. sk_rt_global_init_2f10b)
 * Same as FUN_004599d0. Confidence: medium (structural). */
static void sk_rt_4599d4(void)
{
    sk_global_init_gate();
    sk_global_store();
}

/* FUN_00459a04 @ 0x00459a04  (est. sk_rt_release_vec3)
 * Releases three refcounted slots of a vector (fields 0..2), each with the
 * low tag masked off. Confidence: medium (structural). */
static void sk_rt_459a04(unsigned long *v)
{
    sk_refcount_release_b(*v & 0xfffffffffffffff);
    sk_refcount_release_b(v[1]);
    sk_refcount_release_b(v[2]);
}

/* FUN_00459a40 @ 0x00459a40  (est. sk_rt_box_copy5_release)
 * Loads a 16-byte pair, swaps 5 owned words between two box objects,
 * releasing the replaced values, then runs the field-copy helper.
 * Confidence: medium (structural). */
static void sk_rt_459a40(void)
{
    cL4_w16_t pair = sk_word_copy(0);
    word_t *src = (word_t*)pair.hi;
    word_t *dst = (word_t*)pair.lo;
    word_t u3, u4;
    u3 = *(word_t*)((char*)src + 0x10);
    u4 = *(word_t*)((char*)src + 8);
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    *(word_t*)((char*)dst + 8) = u4;
    *(byte*)((char*)dst + 0x18) = *(byte*)((char*)src + 0x18);
    sk_refcount_acquire_c(0);
    sk_refcount_acquire_c(u4);
    sk_refcount_acquire_c(u3);
}

/* FUN_00459aa0 @ 0x00459aa0  (est. sk_rt_swap_retain_release)
 * Swaps two owned slots (offset +8 and +0x10) between two objects with
 * retain/release, and swaps the global pointer at FUN_0034d454.
 * Confidence: medium (structural). */
static void sk_rt_459aa0(word_t *dst, word_t *src)
{
    unsigned long *gp = (unsigned long*)sk_f_0034d454();
    unsigned long old = *gp;
    word_t u;
    *gp = (unsigned long)gp;
    sk_refcount_acquire_c((word_t)gp & 0xfffffffffffffff);
    sk_refcount_release_b(old & 0xfffffffffffffff);
    u = *(word_t*)((char*)dst + 8);
    *(word_t*)((char*)dst + 8) = *(word_t*)((char*)src + 8);
    sk_refcount_acquire_c(0);
    sk_refcount_release_b(u);
    u = *(word_t*)((char*)dst + 0x10);
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    sk_refcount_acquire_c(0);
    sk_refcount_release_b(u);
    sk_copy_byte_18();
}

/* FUN_00459b14 @ 0x00459b14  (est. sk_rt_swap_release)
 * Releases a slot and swaps two owned fields between two objects.
 * Confidence: medium (structural). */
static void sk_rt_459b14(word_t *dst, word_t *src)
{
    unsigned long *gp = (unsigned long*)sk_f_0034d454();
    unsigned long old = *gp;
    word_t u;
    *gp = (unsigned long)gp;
    sk_refcount_release_b(old & 0xfffffffffffffff);
    sk_refcount_release_b(*(word_t*)((char*)dst + 8));
    u = *(word_t*)((char*)dst + 0x10);
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    *(word_t*)((char*)dst + 8) = *(word_t*)((char*)src + 8);
    sk_refcount_release_b(u);
    sk_copy_byte_18();
}

/* FUN_00459b6c @ 0x00459b6c  (est. sk_rt_load_release_pair)
 * Loads a 16-byte pair and releases the low-tag-masked word.
 * Confidence: medium (structural). */
static void sk_rt_459b6c(void)
{
    sk_word_copy(0);
    sk_refcount_release_b(0);
}

/* FUN_00459ba4 @ 0x00459ba4  (est. sk_rt_assign_swap)
 * Assigns *param_2 into *param_1 with retain of the new value and release of
 * the old, returning param_1. Confidence: medium (structural). */
static word_t *sk_rt_459ba4(word_t *dst, word_t *src)
{
    word_t old = *dst;
    word_t nw = *src;
    *dst = nw;
    sk_refcount_acquire_c(nw & 0xfffffffffffffff);
    sk_refcount_release_b(old & 0xfffffffffffffff);
    return dst;
}

/* FUN_00459be4 @ 0x00459be4  (est. sk_rt_assign_move)
 * Moves *param_2 into *param_1 releasing the old value; returns param_1.
 * Confidence: medium (structural). */
static word_t *sk_rt_459be4(word_t *dst, word_t *src)
{
    word_t old = *dst;
    *dst = *src;
    sk_refcount_release_b(old & 0xfffffffffffffff);
    return dst;
}

/* FUN_00459cfc @ 0x00459cfc  (est. sk_rt_copy_field8)
 * Copies offset +8 from one object to another and runs copy helpers.
 * Confidence: medium (structural). */
static void sk_rt_459cfc(word_t *dst, word_t *src)
{
    sk_003504d0();
    sk_465b1c();
    sk_refcount_release_b(0);
    *(word_t*)((char*)dst + 8) = *(word_t*)((char*)src + 8);
    sk_464dcc();
}

/* FUN_00459d40 @ 0x00459d40  (est. sk_rt_copy_fields_to_box)
 * Copies 3 words (+0,+8,+0x10) from a source box into a destination box
 * after releasing the destination's current value. Confidence: medium. */
static void sk_rt_459d40(word_t *dst, word_t *src)
{
    word_t *gp = (word_t*)sk_f_0034d454();
    word_t old = *gp;
    *dst = (word_t)gp;
    sk_refcount_release_b(old);
    dst[2] = *(word_t*)((char*)src + 0x10);
    dst[1] = *(word_t*)((char*)src + 8);
    (void)src;
}


/* FUN_00459e14 @ 0x00459e14  (est. sk_rt_copy_fields_10)
 * Copies four owned fields (+0x10..+0x28) of a box into the shared field
 * copier FUN_00458940. Confidence: medium (structural). */
static void sk_rt_459e14(word_t *obj)
{
    sk_58940(*(word_t*)((char*)obj + 0x10), *(word_t*)((char*)obj + 0x18),
             *(word_t*)((char*)obj + 0x20), *(word_t*)((char*)obj + 0x28));
}

/* FUN_00459e24 @ 0x00459e24  (est. sk_rt_copy_frame_10)
 * Copies a value frame: runs copy helpers and copies 5 words (+0x10..+0x38)
 * from one frame object to another. Confidence: medium (structural). */
static void sk_rt_459e24(word_t *dst, word_t *src,
                         word_t v21, word_t v22, word_t v23, word_t v24)
{
    sk_rt_46306c();
    sk_nop_661fc();
    sk_4629();
    sk_588cc();
    *(word_t*)((char*)dst + 0x10) = v21;
    *(word_t*)((char*)dst + 0x18) = v22;
    *(word_t*)((char*)dst + 0x20) = v23;
    *(word_t*)((char*)dst + 0x28) = v24;
    *(word_t*)((char*)dst + 0x38) = *(word_t*)((char*)src + 0x38);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
}

/* FUN_00459e74 @ 0x00459e74  (est. sk_rt_copy_frame_10b)
 * Copy frame: runs copy helpers, copies 5 words + 0x30, forwards through
 * the shared field copier. Confidence: medium (structural). */
static void sk_rt_459e74(word_t *dst, word_t *src,
                         word_t v21, word_t v22, word_t v23, word_t v24)
{
    sk_word_copy_3();
    sk_copy_word_640b8();
    sk_nop_661fc();
    sk_4629();
    sk_588cc();
    sk_0010a9f8();
    *(word_t*)((char*)dst + 0x10) = v21;
    *(word_t*)((char*)dst + 0x18) = v22;
    *(word_t*)((char*)dst + 0x20) = v23;
    *(word_t*)((char*)dst + 0x28) = v24;
    sk_58940(0, 0, 0, 0);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
    sk_copy_word_66220();
}

/* FUN_00459ed4 @ 0x00459ed4  (est. sk_rt_copy_frame_8)
 * Copy frame: copies 8 words (+0..+0x38) from one frame to another and
 * forwards four register-held words to the shared field copier.
 * Confidence: medium (structural). */
static void sk_rt_459ed4(word_t *dst, word_t *src)
{
    word_t u3, u4, u5;
    u3 = *(word_t*)((char*)src + 0x10);
    u4 = src[4];
    u5 = src[5];
    dst[1] = src[1]; *dst = *src; dst[3] = src[3]; dst[2] = src[2];
    dst[5] = src[5]; dst[4] = src[4];
    sk_58940(u3, src[3], src[4], src[5]);
    dst[7] = src[7]; dst[6] = src[6];
}

/* FUN_00459ffc @ 0x00459ffc  (est. sk_rt_store_frame_4)
 * Stores four words (+0..+0x18) from registers into a frame after copy
 * helpers. Confidence: medium (structural). */
static void sk_rt_459ffc(word_t *dst, word_t v20, word_t v21, word_t v22, word_t v23)
{
    sk_noop_463504();
    sk_noop_c444();
    sk_588cc();
    *dst = v20;
    dst[1] = v21;
    dst[2] = v22;
    dst[3] = v23;
}

/* FUN_0045a044 @ 0x0045a044  (est. sk_rt_swap_frame_4)
 * Swap four words of a frame with the shared field copier.
 * Confidence: medium (structural). */
static void sk_rt_45a044(word_t *obj, word_t v20, word_t v21, word_t v22, word_t v23)
{
    word_t u1, u2, u3, u4;
    sk_noop_463504();
    sk_noop_c444();
    sk_588cc();
    u1 = *obj; u3 = obj[1]; u2 = obj[2]; u4 = obj[3];
    *obj = v20; obj[1] = v21; obj[2] = v22; obj[3] = v23;
    sk_58940(u1, u3, u2, u4);
}

/* FUN_0045a098 @ 0x0045a098  (est. sk_rt_copy_from_pair)
 * Copies 4 words from the 16-byte-pair-derived source into a frame and
 * forwards to the shared field copier. Confidence: medium (structural). */
static void sk_rt_45a098(word_t *dst)
{
    cL4_w16_t pair = exc_restore_2b20();
    word_t *src = (word_t*)pair.hi;
    word_t u1, u2, u4;
    u1 = dst[1]; u2 = dst[2]; u4 = dst[3];
    dst[1] = src[1]; *dst = *src; dst[3] = src[3]; dst[2] = src[2];
    sk_58940(pair.lo, u1, u2, u4);
}

/* FUN_0045a1f8 @ 0x0045a1f8  (est. sk_rt_retain_small)
 * Retain helper: op 2 retains param_2; else no-op. Confidence: medium. */
static void sk_rt_45a1f8(word_t p1, word_t p2, word_t p3, word_t p4, byte op)
{
    if (op == 2) { sk_refcount_acquire_c(p2); return; }
    (void)p1; (void)p3; (void)p4;
}

/* FUN_0045a210 @ 0x0045a210  (est. sk_rt_copy_fields_20)
 * Copy fields of a box (+0x20..+0x58) through the shared helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a210(word_t *dst, word_t *src)
{
    cL4_nop_handler();
    sk_462848();
    sk_rt_45a1f8(0,0,0,0,0);
    sk_4640d0();
    *(byte*)((char*)dst + 0x20) = *(byte*)((char*)src + 0x20);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
    *(word_t*)((char*)dst + 0x28) = *(word_t*)((char*)src + 0x28);
    sk_copy_fields_645d8();
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    cL4_nop_handler();
}

/* FUN_0045a268 @ 0x0045a268  (est. sk_rt_copy_fields_28)
 * Copy fields of a box (+0x28..+0x58) through the shared helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a268(word_t *dst, word_t *src)
{
    cL4_nop_handler();
    sk_462848();
    sk_rt_45a1f8(0,0,0,0,0);
    sk_rt_46303c();
    sk_rt_4592dc(0,0,0,0,0);
    *(byte*)((char*)dst + 0x48) = *(byte*)((char*)src + 0x48);
    *(word_t*)((char*)dst + 0x40) = *(word_t*)((char*)src + 0x40);
    *(word_t*)((char*)dst + 0x38) = *(word_t*)((char*)src + 0x38);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
    *(word_t*)((char*)dst + 0x28) = *(word_t*)((char*)src + 0x28);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    cL4_nop_handler();
}

/* FUN_0045a2d4 @ 0x0045a2d4  (est. sk_rt_copy_fields_28b)
 * Copy fields of a box (+0x28..+0x58) through the shared helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a2d4(word_t *dst, word_t *src)
{
    sk_rt_463154();
    sk_rt_4592dc(0,0,0,0,0);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
    *(word_t*)((char*)dst + 0x28) = *(word_t*)((char*)src + 0x28);
    sk_copy_fields_645d8();
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
}

/* FUN_0045a3ac @ 0x0045a3ac  (est. sk_rt_dispatch_fn)
 * Dispatches through FUN_004607c4 with the destroy helper FUN_004592dc.
 * Confidence: medium (structural). */
static void sk_rt_45a3ac(word_t a, word_t b)
{
    sk_4607c4((void*)a, b, (void(*)(void))sk_rt_4592dc);
}

/* FUN_0045a4b4 @ 0x0045a4b4  (est. sk_rt_retain_big_dispatch)
 * Multi-way value-retain dispatcher on a 4-bit selector (byte >> 4).
 * Mirror of FUN_00459138 but retaining. Confidence: medium (structural). */
static void sk_rt_45a4b4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5,
                         word_t p6, word_t p7, word_t p8, byte sel)
{
    switch (sel >> 4) {
    default: p5 = p2; break;
    case 1: case 4: return;
    case 2: sk_refcount_acquire_c(0); p2 = p8; sk_refcount_acquire_c(p2); return;
    case 3: sk_rt_45a5fc(p1, p2, 0, 0, 0); return;
    case 9: case 10: sk_rt_45a1f8(p1, p2, 0, 0, 0); return;
    case 0xb: sk_rt_45a658(p1, p2, 0, 0, 0, 0, 0, 0); return;
    case 0xc: break;
    case 0xd: sk_refcount_acquire_c(p4); p2 = p8;
              sk_refcount_acquire_c(p2); return;
    }
    sk_refcount_acquire_c(p5);
}

/* FUN_0045a658 @ 0x0045a658  (est. sk_rt_retain_multi)
 * Multi-field retain dispatcher. op 2: retain +0x18; op 1: retain +0x30 and
 * param_2, forward x7; op 0: forward to FUN_00458b94.
 * Confidence: medium (structural). */
static void sk_rt_45a658(word_t p1, word_t p2, word_t p3, word_t p4, word_t x7,
                         word_t s18, word_t s30, byte op)
{
    if (op == 2) { sk_refcount_acquire_c(s18); }
    else {
        if (op != 1) {
            if (op == 0) { sk_58b94(p1, p2, p3, p4); return; }
            return;
        }
        sk_refcount_acquire_c(s30);
        sk_refcount_acquire_c(p2);
        p4 = x7;
    }
    sk_refcount_acquire_c(p4);
}

/* FUN_0045a6f4 @ 0x0045a6f4  (est. sk_rt_copy_fields_a0)
 * Copy box fields (+0xa0/+0xa8) through many shared copy helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a6f4(word_t *dst, word_t *src)
{
    sk_nop_464b04();
    sk_syscall_save_ret();
    sk_cmp_462bd8(0);
    sk_noop_463058();
    sk_syscall_stub_34db28();
    sk_fwd_45a4b4_464e9c();
    sk_store19_words();
    *(word_t*)((char*)dst + 0xa8) = *(word_t*)((char*)src + 0xa8);
    *(word_t*)((char*)dst + 0xa0) = *(word_t*)((char*)src + 0xa0);
    sk_nop_464ae8();
}

/* FUN_0045a774 @ 0x0045a774  (est. sk_rt_copy_fields_40)
 * Copy box fields (+0x40..+0x98) through many shared copy helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a774(word_t *dst, word_t *src,
                         word_t s68, word_t s70, word_t s78, word_t s80,
                         word_t s88, word_t s90, word_t s98, word_t sa0,
                         word_t sa8, word_t sb0)
{
    sk_nop_464b04();
    sk_syscall_save_ret();
    sk_noop_462e88(0);
    sk_cmp_462bd8(0);
    sk_noop_463058();
    sk_gate_4627d0();
    sk_rt_45a4b4(0,0,0,0,0,0,0,0,0);
    sk_rt_463080();
    sk_load16_40();
    sk_rt_462fec();
    *(word_t*)((char*)dst + 0x40) = s68;
    *(word_t*)((char*)dst + 0x48) = s70;
    *(word_t*)((char*)dst + 0x50) = s78;
    *(word_t*)((char*)dst + 0x58) = s80;
    *(word_t*)((char*)dst + 0x60) = s88;
    *(word_t*)((char*)dst + 0x68) = s90;
    *(word_t*)((char*)dst + 0x70) = s98;
    *(word_t*)((char*)dst + 0x78) = sa0;
    *(word_t*)((char*)dst + 0x80) = sa8;
    *(word_t*)((char*)dst + 0x88) = sb0;
    *(word_t*)((char*)dst + 0x90) = *(word_t*)((char*)src + 0x90);
    *(byte*)((char*)dst + 0x98) = *(byte*)((char*)src + 0x98);
    sk_462b90();
    sk_rt_459138(0,0,0,0,0,0,0,0,0);
    sk_copy2words_61a4();
    sk_nop_464ae8();
}

/* FUN_0045a830 @ 0x0045a830  (est. sk_rt_copy_box_16)
 * Copy an 0x98-byte box (22 words + flags) through the shared helpers.
 * Confidence: medium (structural). */
static void sk_rt_45a830(word_t *dst, word_t *src)
{
    sk_syscall_save_ret();
    sk_rt_462e54(*(word_t*)((char*)src + 0x90));
    dst[1] = src[1]; *dst = *src; dst[3] = src[3]; dst[2] = src[2];
    dst[5] = src[5]; dst[4] = src[4]; dst[7] = src[7]; dst[6] = src[6];
    dst[9] = src[9]; dst[8] = src[8]; dst[0xb] = src[0xb]; dst[10] = src[10];
    dst[0xd] = src[0xd]; dst[0xc] = src[0xc]; dst[0xf] = src[0xf]; dst[0xe] = src[0xe];
    dst[0x11] = src[0x11]; dst[0x10] = src[0x10];
    dst[0x12] = src[0x12];
    *(byte*)((char*)dst + 0x13) = *(byte*)((char*)src + 0x13);
    swift_runtime_stub_noop();
    sk_rt_459138(0,0,0,0,0,0,0,0,0);
    dst[0x15] = src[0x15]; dst[0x14] = src[0x14];
}

/* FUN_0045a904 @ 0x0045a904  (est. sk_rt_box_ensure_small)
 * Box sizing helper: for small lengths writes the length and flag bytes into
 * the box header; for large lengths zeroes the header words, builds the
 * extra-length entry via FUN_00463358, and sets the overflow flag.
 * Confidence: medium (structural). */
static void sk_rt_45a904(word_t *box, uint len, uint cap)
{
    if (len < 0x32) {
        if (0x31 < cap) *(byte*)((char*)box + 0x16) = 0;
        if (len != 0) {
            sk_fwd_54ec();
            *(byte*)((char*)box + 0x13) = 0;
        }
    } else {
        box[0x15] = 0; box[0x14] = 0; box[0x13] = 0;
        box[0x12] = 0; box[0x11] = 0;
        sk_rt_463358(len - 0x32);
        *box = 0;
        if (0x31 < cap) *(byte*)((char*)box + 0x16) = 1;
    }
}

/* FUN_0045a980 @ 0x0045a980  (est. sk_rt_dispatch_fn_b)
 * Dispatches through FUN_0045b1a0 with the destroy helper FUN_00459138.
 * Confidence: medium (structural). */
static void sk_rt_45a980(word_t a, word_t b)
{
    sk_rt_45b1a0(a, b, (void(*)(void))sk_rt_459138);
}

/* FUN_0045aab0 @ 0x0045aab0  (est. sk_rt_box_set_selector)
 * Stores an operation selector into the box header flags byte. Small
 * selectors (< 0xe) are packed into the low nibble; larger ones are stored
 * as the length and the flags byte set to 0xe0. Confidence: medium. */
static void sk_rt_45aab0(word_t *box, uint sel)
{
    byte b;
    if (sel < 0xe) {
        b = (byte)box[0x13] & 3 | (byte)(sel << 4);
    } else {
        *box = (word_t)(sel - 0xe);
        sk_00114330(box + 1, 0x90);
        b = 0xe0;
    }
    *(byte*)((char*)box + 0x13) = b;
}


/* FUN_0045a5fc @ 0x0045a5fc  (est. sk_rt_release_owned_box)
 * Release dispatcher: op 4 addr-mask-releases param_2; op 0xe releases
 * param_2 then param_4; op 7 releases param_3; else no-op.
 * Confidence: medium (structural). */
static void sk_rt_45a5fc(word_t p1, word_t p2, word_t p3, word_t p4, byte op)
{
    if (op != 4) {
        if (op == 0xe) { sk_refcount_acquire_c(p2); p2 = p4; }
        else { p2 = p3; if (op != 7) return; }
    }
    sk_refcount_acquire_c(p2);
}

/* FUN_0045aa44 @ 0x0045aa44  (est. sk_rt_box_ensure_sel)
 * Box sizing/setup helper, mirror of FUN_0045a904 with a different flag
 * layout. Confidence: medium (structural). */
static void sk_rt_45aa44(word_t *box, uint len, uint cap)
{
    if (len < 0x32) {
        if (0x31 < cap) *(byte*)((char*)box + 0x99) = 0;
        if (len != 0) {
            sk_fwd_54ec();
            *(byte*)((char*)box + 0x13) = 0;
        }
    } else {
        box[0x12] = 0; box[0x11] = 0;
        sk_rt_463358(len - 0x32);
        *(byte*)((char*)box + 0x13) = 0;
        *box = 0;
        if (0x31 < cap) *(byte*)((char*)box + 0x99) = 1;
    }
}

/* FUN_0045ab5c @ 0x0045ab5c  (est. sk_rt_assign2_retain)
 * Copies two words from param_2 into param_1 with retain of both copied
 * values; returns param_1. Confidence: medium (structural). */
static word_t *sk_rt_45ab5c(word_t *dst, word_t *src)
{
    word_t u1 = src[1], u2 = *src;
    dst[1] = src[1]; *dst = u2;
    sk_refcount_acquire_c(u2);
    sk_refcount_acquire_c(u1);
    return dst;
}

/* FUN_0045ab9c @ 0x0045ab9c  (est. sk_rt_copy_field8_swap)
 * Swaps offset +8 between two objects with retain/release.
 * Confidence: medium (structural). */
static void sk_rt_45ab9c(word_t *dst, word_t *src)
{
    word_t u;
    sk_003504d0();
    sk_465b1c();
    sk_refcount_release_b(0);
    u = *(word_t*)((char*)dst + 8);
    *(word_t*)((char*)dst + 8) = *(word_t*)((char*)src + 8);
    sk_refcount_acquire_c(0);
    sk_refcount_release_b(u);
}

/* FUN_0045abec @ 0x0045abec  (est. sk_rt_copy2_release)
 * Copies two words from one box to another releasing the destination's old
 * values. Confidence: medium (structural). */
static void sk_rt_45abec(word_t *dst, word_t *src)
{
    word_t *gp = (word_t*)sk_003504d0();
    word_t u;
    sk_refcount_release_b(*gp);
    u = dst[1];
    dst[1] = src[1]; *dst = *src;
    sk_refcount_release_b(u);
}

/* FUN_0045ad90 @ 0x0045ad90  (est. sk_rt_copy_fields_20b)
 * Copy small box fields (+0x20/+0x21) through shared helpers.
 * Confidence: medium (structural). */
static void sk_rt_45ad90(word_t *dst, word_t *src)
{
    cL4_nop_handler();
    sk_462848();
    sk_rt_45a5fc(0,0,0,0,0);
    sk_4640d0();
    *(byte*)((char*)dst + 0x20) = *(byte*)((char*)src + 0x20);
    *(short*)((char*)dst + 0x21) = *(short*)((char*)src + 0x21);
    cL4_nop_handler();
}

/* FUN_0045addc @ 0x0045addc  (est. sk_rt_copy_fields_20c)
 * Copy box fields through shared helpers with the copy2bytes helper.
 * Confidence: medium (structural). */
static void sk_rt_45addc(void)
{
    cL4_nop_handler();
    sk_462848();
    sk_rt_45a5fc(0,0,0,0,0);
    sk_rt_46303c();
    sk_rt_459280(0,0,0,0,0);
    sk_copy2bytes_5770();
    cL4_nop_handler();
}

/* FUN_0045ae20 @ 0x0045ae20  (est. sk_rt_copy_fields_20d)
 * Copy box fields through shared helpers with the copy2bytes helper.
 * Confidence: medium (structural). */
static void sk_rt_45ae20(void)
{
    sk_rt_463154();
    sk_rt_459280(0,0,0,0,0);
    sk_copy2bytes_5770();
}

/* FUN_0045b1a0 @ 0x0045b1a0  (est. sk_rt_dispatch_thunk)
 * Thunk: resolves an object via FUN_004644cc, forwards five words through
 * FUN_0034f8e4, then calls through an indirect slot.
 * Confidence: medium (structural). */
static void sk_rt_45b1a0(word_t a, word_t b, void (*fn)(void))
{
    long base = sk_464644(b, a, *(word_t*)((char*)a + 8));
    swift_runtime_stub_noop();
    (*fn)();
}

/* FUN_0045b1f4 @ 0x0045b1f4  (est. sk_rt_copy_box_40)
 * Copy a 0x98-byte box (22 words + flags): reads fields, dispatches through
 * FUN_0034f3b4 with the retain helper, stores all fields, forwards through
 * FUN_004663ec. Confidence: medium (structural). */
static void sk_rt_45b1f4(void)
{
    cL4_w16_t pair = sk_466408();
    word_t *src = (word_t*)pair.hi;
    word_t *dst = (word_t*)pair.lo;
    word_t w[11];
    int i;
    for (i = 0; i < 11; i++) w[i] = src[8+i];
    swift_runtime_stub_noop();
    sk_rt_462fec();
    for (i = 0; i < 10; i++) *(word_t*)((char*)dst + 0x40 + i*8) = w[i];
    *(word_t*)((char*)dst + 0x90) = w[10];
    *(char*)((char*)dst + 0x98) = *(char*)((char*)src + 0x13);
    sk_4663ec((word_t)dst, 0);
}

/* FUN_0045b330 @ 0x0045b330  (est. sk_rt_copy_box_40b)
 * Copy a 0x98-byte box: reads source fields, dispatches through the shared
 * store helper, writes all fields, runs copy helpers. Confidence: medium. */
static void sk_rt_45b330(void)
{
    cL4_w16_t pair;
    word_t *box = (word_t*)sk_464b04(0);
    word_t w[11];
    int i;
    sk_noop_462e88(0);
    for (i = 0; i < 10; i++) w[i] = *(word_t*)((char*)box + 0x40 + i*8);
    w[10] = *(word_t*)((char*)box + 0x90);
    sk_gate_4627d0();
    swift_runtime_stub_noop();
    sk_4640d0();
    for (i = 0; i < 4; i++) box[4+i] = 0;
    for (i = 0; i < 10; i++) *(word_t*)((char*)box + 0x40 + i*8) = w[i];
    *(word_t*)((char*)box + 0x90) = w[10];
    *(char*)((char*)box + 0x98) = *(char*)((char*)box + 0x13);
    sk_462b90();
    swift_runtime_stub_noop();
    sk_464ae8(0,0);
}

/* FUN_0045b458 @ 0x0045b458  (est. sk_rt_copy_box_into)
 * Copy a 0x98-byte box into param_3 from the shared pair source, forwarding
 * through FUN_0034f8e4. Confidence: medium (structural). */
static word_t *sk_rt_45b458(word_t *dst, word_t *src, word_t a, word_t b, word_t c)
{
    cL4_w16_t pair;
    word_t u1, u3, u4;
    int i;
    sk_rt_463028(c, *dst, a, dst[2]);
    u1 = dst[0xc]; u3 = dst[0xe]; u4 = dst[0x10];
    for (i = 0; i < 0x12; i++) dst[i] = dst[i];
    dst[0x12] = dst[0x12];
    *(byte*)((char*)dst + 0x13) = *(byte*)((char*)dst + 0x13);
    swift_runtime_stub_noop();
    return dst;
}

/* FUN_0045b5a8 @ 0x0045b5a8  (est. sk_rt_copy_fields_20e)
 * Copy box fields through shared helpers. Confidence: medium. */
static void sk_rt_45b5a8(word_t *dst, word_t *src)
{
    cL4_nop_handler();
    sk_462848();
    sk_58b94(0, 0, 0, 0);
    sk_4640d0();
    *(byte*)((char*)dst + 0x20) = *(byte*)((char*)src + 0x20);
    sk_4653cc();
    cL4_nop_handler();
}

/* FUN_0045b5ec @ 0x0045b5ec  (est. sk_rt_copy_fields_20f)
 * Copy box fields through shared helpers. Confidence: medium. */
static void sk_rt_45b5ec(void)
{
    cL4_nop_handler();
    sk_462848();
    sk_58b94(0, 0, 0, 0);
    sk_rt_46303c();
    sk_58bac();
    sk_cmp_4632b8();
    cL4_nop_handler();
}

/* FUN_0045b634 @ 0x0045b634  (est. sk_rt_copy_fields_20g)
 * Copy box fields through shared helpers. Confidence: medium. */
static void sk_rt_45b634(void)
{
    sk_rt_463154();
    sk_58bac();
    sk_4653cc();
}

/* FUN_0045b7f4 @ 0x0045b7f4  (est. sk_rt_destroy_38_70)
 * Releases fields at +0x38 (addr-mask) and +0x70 (refcount) and runs the
 * teardown helper. Confidence: medium (structural). */
static void sk_rt_45b7f4(word_t *obj)
{
    sk_release_666c0();
    addr_mask_release(*(word_t*)((char*)obj + 0x38));
    sk_refcount_release_b(*(word_t*)((char*)obj + 0x70));
}

/* FUN_0045b824 @ 0x0045b824  (est. sk_rt_copy_box_40c)
 * Copy many box fields (+0x40..+0x80) with retain of the new values.
 * Confidence: medium (structural). */
static void sk_rt_45b824(word_t *dst, word_t *src)
{
    sk_00355938();
    sk_465f20();
    *(word_t*)((char*)dst + 0x48) = *(word_t*)((char*)src + 0x48);
    *(word_t*)((char*)dst + 0x40) = *(word_t*)((char*)src + 0x40);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    *(word_t*)((char*)dst + 0x68) = *(word_t*)((char*)src + 0x68);
    *(word_t*)((char*)dst + 0x60) = *(word_t*)((char*)src + 0x60);
    *(word_t*)((char*)dst + 0x70) = *(word_t*)((char*)src + 0x70);
    *(word_t*)((char*)dst + 0x80) = *(word_t*)((char*)src + 0x80);
    *(word_t*)((char*)dst + 0x78) = *(word_t*)((char*)src + 0x78);
    sk_refcount_acquire_c(0);
    sk_refcount_acquire_c(0);
    sk_refcount_acquire_c(0);
}

/* FUN_0045b888 @ 0x0045b888  (est. sk_rt_copy_box_40d)
 * Copy many box fields (+8..+0x80) with retain/release per field.
 * Confidence: medium (structural). */
static void sk_rt_45b888(word_t *dst, word_t *src)
{
    word_t u;
    sk_word_copy(0);
    u = *(word_t*)((char*)dst + 8);
    *(word_t*)((char*)dst + 8) = *(word_t*)((char*)src + 8);
    sk_refcount_acquire_c(0);
    addr_mask_release(u);
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    sk_copy2words_6034();
    *(word_t*)((char*)dst + 0x28) = *(word_t*)((char*)src + 0x28);
    *(word_t*)((char*)dst + 0x30) = *(word_t*)((char*)src + 0x30);
    u = *(word_t*)((char*)dst + 0x38);
    *(word_t*)((char*)dst + 0x38) = *(word_t*)((char*)src + 0x38);
    sk_refcount_acquire_c(0);
    addr_mask_release(u);
    *(word_t*)((char*)dst + 0x40) = *(word_t*)((char*)src + 0x40);
    *(word_t*)((char*)dst + 0x48) = *(word_t*)((char*)src + 0x48);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    sk_copy2words_56e0();
    *(word_t*)((char*)dst + 0x68) = 0;
    u = *(word_t*)((char*)dst + 0x70);
    *(word_t*)((char*)dst + 0x70) = *(word_t*)((char*)src + 0x70);
    sk_refcount_acquire_c(0);
    sk_refcount_release_b(u);
    *(word_t*)((char*)dst + 0x78) = *(word_t*)((char*)src + 0x78);
    *(word_t*)((char*)dst + 0x80) = *(word_t*)((char*)src + 0x80);
}

/* FUN_0045b954 @ 0x0045b954  (est. sk_rt_copy_box_40e)
 * Copy box fields (+0x40..+0x80) releasing the destination's old values.
 * Confidence: medium (structural). */
static void sk_rt_45b954(word_t *dst, word_t *src)
{
    word_t u;
    sk_rt_46337c();
    sk_465a50();
    *(word_t*)((char*)dst + 0x48) = *(word_t*)((char*)src + 0x48);
    *(word_t*)((char*)dst + 0x40) = *(word_t*)((char*)src + 0x40);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    *(word_t*)((char*)dst + 0x68) = *(word_t*)((char*)src + 0x68);
    *(word_t*)((char*)dst + 0x60) = *(word_t*)((char*)src + 0x60);
    u = *(word_t*)((char*)dst + 0x70);
    *(word_t*)((char*)dst + 0x70) = *(word_t*)((char*)src + 0x70);
    sk_refcount_release_b(u);
    *(word_t*)((char*)dst + 0x80) = *(word_t*)((char*)src + 0x80);
    *(word_t*)((char*)dst + 0x78) = *(word_t*)((char*)src + 0x78);
}

/* FUN_0045ba44 @ 0x0045ba44  (est. sk_rt_copy_fields_10c)
 * Copy fields (+0x10..+0x20) with retain. Confidence: medium. */
static void sk_rt_45ba44(word_t *dst, word_t *src)
{
    sk_copy16();
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    *(word_t*)((char*)dst + 0x20) = *(word_t*)((char*)src + 0x20);
    *(word_t*)((char*)dst + 0x18) = *(word_t*)((char*)src + 0x18);
    sk_refcount_acquire_c(0);
}

/* FUN_0045ba7c @ 0x0045ba7c  (est. sk_rt_copy_frame_release)
 * Copy frame with retain/release through shared helpers. Confidence: medium. */
static void sk_rt_45ba7c(void)
{
    sk_word_copy_3();
    sk_copy_field_pair();
    sk_refcount_acquire_c(0);
    sk_refcount_release_b(0);
    sk_copy_words_18_20();
}

/* FUN_0045babc @ 0x0045babc  (est. sk_rt_copy_fields_10d)
 * Copy fields (+0x10..+0x20) releasing the old value. Confidence: medium. */
static void sk_rt_45babc(word_t *dst, word_t *src)
{
    cL4_w16_t pair = sk_rt_46306c();
    word_t u = *(word_t*)((char*)pair.lo + 0x10);
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)pair.hi + 0x10);
    sk_refcount_release_b(u);
    *(word_t*)((char*)dst + 0x20) = *(word_t*)((char*)src + 0x20);
    *(word_t*)((char*)dst + 0x18) = *(word_t*)((char*)src + 0x18);
}

/* FUN_0045bb84 @ 0x0045bb84  (est. sk_rt_destroy_18_58)
 * Releases fields at +0x18 and +0x58 with addr-mask release.
 * Confidence: medium (structural). */
static void sk_rt_45bb84(word_t *obj)
{
    addr_mask_release(*(word_t*)((char*)obj + 0x18));
    addr_mask_release(*(word_t*)((char*)obj + 0x58));
}

/* FUN_0045bbb4 @ 0x0045bbb4  (est. sk_rt_copy_box_40f)
 * Copy box fields (+0x10..+0x90) with retain. Confidence: medium. */
static void sk_rt_45bbb4(word_t *dst, word_t *src)
{
    word_t u;
    sk_copy16();
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)src + 0x10);
    *(word_t*)((char*)dst + 0x18) = *(word_t*)((char*)src + 0x18);
    sk_465eec();
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    *(word_t*)((char*)dst + 0x68) = *(word_t*)((char*)src + 0x68);
    *(word_t*)((char*)dst + 0x60) = *(word_t*)((char*)src + 0x60);
    *(word_t*)((char*)dst + 0x78) = *(word_t*)((char*)src + 0x78);
    *(word_t*)((char*)dst + 0x70) = *(word_t*)((char*)src + 0x70);
    *(word_t*)((char*)dst + 0x90) = *(word_t*)((char*)src + 0x90);
    *(word_t*)((char*)dst + 0x88) = *(word_t*)((char*)src + 0x88);
    *(word_t*)((char*)dst + 0x80) = *(word_t*)((char*)src + 0x80);
    sk_refcount_acquire_c(0);
    sk_refcount_acquire_c(0);
}

/* FUN_0045bc10 @ 0x0045bc10  (est. sk_rt_copy_box_50)
 * Copy box fields (+0x50..+0x90) with retain/release. Confidence: medium. */
static void sk_rt_45bc10(word_t *dst, word_t *src)
{
    word_t u;
    sk_word_copy_3();
    sk_cmp_463484();
    sk_refcount_acquire_c(0);
    addr_mask_release(0);
    sk_copy_word_64504();
    sk_cmp_4632b8();
    sk_copy_word_66220();
    sk_copy2words_5d28();
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    u = *(word_t*)((char*)dst + 0x58);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    sk_refcount_acquire_c(0);
    addr_mask_release(u);
    *(word_t*)((char*)dst + 0x60) = *(word_t*)((char*)src + 0x60);
    *(word_t*)((char*)dst + 0x68) = *(word_t*)((char*)src + 0x68);
    sk_copy2words_5f68();
    *(byte*)((char*)dst + 0x80) = *(byte*)((char*)src + 0x80);
    *(word_t*)((char*)dst + 0x88) = *(word_t*)((char*)src + 0x88);
    *(word_t*)((char*)dst + 0x90) = *(word_t*)((char*)src + 0x90);
}

/* FUN_0045bcb0 @ 0x0045bcb0  (est. sk_rt_copy_box_50b)
 * Copy box fields (+0x10..+0x90) releasing the destination's old values.
 * Confidence: medium (structural). */
static void sk_rt_45bcb0(word_t *dst, word_t *src)
{
    cL4_w16_t pair = sk_rt_46306c();
    word_t u;
    *(word_t*)((char*)dst + 0x10) = *(word_t*)((char*)pair.hi + 0x10);
    *(word_t*)((char*)dst + 0x18) = *(word_t*)((char*)pair.hi + 0x18);
    addr_mask_release(*(word_t*)((char*)pair.lo + 0x18));
    sk_466374();
    *(word_t*)((char*)dst + 0x50) = *(word_t*)((char*)src + 0x50);
    u = *(word_t*)((char*)dst + 0x58);
    *(word_t*)((char*)dst + 0x58) = *(word_t*)((char*)src + 0x58);
    addr_mask_release(u);
    *(word_t*)((char*)dst + 0x60) = *(word_t*)((char*)src + 0x60);
    *(word_t*)((char*)dst + 0x78) = *(word_t*)((char*)src + 0x78);
    *(word_t*)((char*)dst + 0x70) = *(word_t*)((char*)src + 0x70);
    *(word_t*)((char*)dst + 0x68) = *(word_t*)((char*)src + 0x68);
    *(byte*)((char*)dst + 0x80) = *(byte*)((char*)src + 0x80);
    *(word_t*)((char*)dst + 0x90) = *(word_t*)((char*)src + 0x90);
    *(word_t*)((char*)dst + 0x88) = *(word_t*)((char*)src + 0x88);
}

