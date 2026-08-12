/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R66: 0x45bdbc-0x4614e4. This is the tail of the embedded Swift-runtime
 * metadata/variant copy-and-destroy engine: the boxed-value / field-copy
 * operators, retain/release-of-refcounted-field helpers, the "variant release
 * by top-3-bits" dispatcher, the Swift Array/ContiguousArray buffer pop/push
 * range-check helpers, and the String/Substring slice-range boundary checkers
 * (the SoftwareBreakpoint(1, addr) fail-closed traps at 0x460f38/0x46123c/...).
 * All names are estimates unless string-matched. Ghidra FUN_ names are kept
 * only in comments.
 *
 * Calling-convention note: functions that take an object/container in x19/x20
 * (the "self"/"other" operands) are shown by Ghidra with unaff_x19/unaff_x20;
 * we render those as the leading parameters. A word whose low three bits are
 * tagged (a Swift runtime value with an inline refcount / enum payload) is
 * retained/released after masking the tag off (& 0xfffffffffffffff) — see
 * cL4_ref_retain / cL4_ref_release. 003a25d4 ("addr_mask_release") releases a
 * separately-masked address/token. 0036b270 = retain (returns obj),
 * 0036b118 = release.
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

/* Memory/load ordering fences used by the refcount code. */
#define CL4_DATA_MEMBARRIER() __asm__ volatile("dmb ish" ::: "memory")
#define CL4_LO_ACQUIRE()      __asm__ volatile("dmb ishld" ::: "memory")
#define CL4_LO_RELEASE()      __asm__ volatile("dmb ish" ::: "memory")

/* SoftwareBreakpoint(1, addr) fail-closed trap. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern word_t   cL4_ref_retain(word_t obj);              /* FUN_0036b270 (returns obj) */
extern void     cL4_ref_release(word_t obj);             /* FUN_0036b118 */
extern void     cL4_token_release(word_t tok);           /* FUN_003a25d4 (addr_mask_release) */
extern word_t   cL4_word_copy(void);                     /* FUN_0034b264 */
extern cL4_w16_t cL4_word_copy_b(void);                  /* FUN_0034f2f4 */
extern cL4_w16_t cL4_byte_copy(void);                    /* FUN_0034cdb4 */
extern cL4_w16_t cL4_copy16(void);                       /* FUN_00350e04 */
extern cL4_w16_t sk_reg_4d0(void);                       /* FUN_003504d0 */
extern cL4_w16_t sk_reg_9b0(void);                       /* FUN_003509b0 */
extern word_t   cL4_frame_copy16(void);                  /* FUN_00355938 */
extern cL4_w16_t exc_restore_regs(void);                 /* FUN_00352b20 */
extern void     exc_copy_reg_pair(void);                 /* FUN_0035270c */
extern void     sk_syscall_save_ret(void);               /* FUN_00350c5c */
extern void     sk_syscall_setup_scratch(void);          /* FUN_00351774 */
extern void     sk_syscall_stub_356f9c(void);            /* FUN_00356f9c */
extern void     sk_syscall_stub_356f80(void);            /* FUN_00356f80 */
extern void     swift_runtime_noop(word_t a, word_t b, word_t c, word_t d, word_t e); /* FUN_0034f8e4 */
extern void     sk_noop_34(word_t);                      /* FUN_00349104 */
extern void     sk_noop_67(void);                        /* FUN_00349928 */
extern void     sk_noop_c444(void);                      /* FUN_0034c444 */
extern cL4_w16_t sk_f_0034d454(void);                    /* FUN_0034d454 */
extern cL4_w16_t sk_h_34db28(void);                      /* FUN_0034db28 */
extern cL4_w16_t sk_h_350bfc(void);                      /* FUN_00350bfc */
extern cL4_w16_t sk_h_35193c(void);                      /* FUN_0035193c */
extern void     sk_gap14_noop_3540d0(word_t, word_t, word_t); /* FUN_003540d0 */
extern word_t   sk_h_359018(void);                       /* FUN_00359018 */
extern void     cL4_finalize_36b21c(void);               /* FUN_0036b21c */
extern cL4_w16_t sk_h_371950(word_t, word_t, word_t, word_t, word_t); /* FUN_00371950 */
extern cL4_w16_t sk_desc_deref_release(word_t, word_t);   /* FUN_00377dcc */
extern void     sk_msg_desc_build_meta(word_t, word_t, word_t, word_t, word_t); /* FUN_003728b8 */
extern word_t   sk_obj_resolve_forward(word_t, word_t);  /* FUN_00376820 */
extern word_t   capability_tag_validity_check(word_t);   /* FUN_003a261c */
extern cL4_w16_t sk_h_2a9ba8(word_t, word_t);            /* FUN_002a9ba8 */
extern word_t   sk_h_2b15d0(word_t, word_t, word_t, word_t); /* FUN_002b15d0 */
extern word_t   sk_bounds_1da84(word_t, word_t, word_t); /* FUN_0001da84 */
extern word_t   sk_h_27614(word_t, word_t);              /* FUN_00027614 */
extern void     sk_h_69970(word_t, word_t);              /* FUN_00069970 */
extern void     sk_h_6b438(word_t);                      /* FUN_0006b438 */
extern void     sk_h_2834(void);                         /* FUN_00002834 */
extern void     cL4_nop_handler(void);                   /* FUN_00084220 / FUN_00084234 */
extern void     cL4_vm_launch_setup(word_t, word_t);     /* FUN_0008e500 */
extern cL4_w16_t cL4_vm_build_launch_image(void);        /* FUN_0008e518 */
extern void     sk_noop_13(void);                        /* FUN_000b4390 */
extern void     sk_noop_9461c(void);                      /* FUN_0009461c */
extern void     sk_mem_114330(word_t, word_t);           /* FUN_00114330 */
extern void     sk_mem_117cc4(word_t, word_t, word_t);   /* FUN_00117cc4 */
extern word_t   sk_h_15f4e0(word_t, word_t, word_t, word_t, word_t, word_t); /* FUN_0015f4e0 */
extern void     sk_swift_strtod_parse2(word_t, word_t);  /* FUN_001e9c78 */

/* Retain/release of a field: the "addr_mask_release" token release. */
extern void     sk_h_45a4b4(void);                       /* FUN_0045a4b4 */
extern void     sk_h_459138(void);                       /* FUN_00459138 */
extern void     sk_h_4593ac(void);                       /* FUN_004593ac */
extern void     sk_h_458db4(void);                       /* FUN_00458db4 */
extern void     sk_h_458f00(void);                       /* FUN_00458f00 */
extern void     sk_h_458f9c(void);                       /* FUN_00458f9c */
extern void     sk_h_459e14(void);                       /* FUN_00459e14 */
extern void     sk_h_459b6c(word_t, word_t);             /* FUN_00459b6c */
extern void     sk_h_459ffc(word_t, word_t);             /* FUN_00459ffc */
extern void     sk_h_45a210(word_t, word_t);             /* FUN_0045a210 */
extern void     sk_h_45a1f8(void);                       /* FUN_0045a1f8 */
extern void     sk_h_45b1f4(word_t, word_t);             /* FUN_0045b1f4 */
extern void     sk_h_455e60(void);                       /* FUN_00455e60 */
extern void     sk_h_456cd8(void);                       /* FUN_00456cd8 */
extern void     sk_h_4567d8(void);                       /* FUN_004567d8 */
extern void     sk_h_457ed8(word_t, word_t, word_t, word_t, word_t); /* FUN_00457ed8 */
extern word_t   sk_h_457a28(word_t);                     /* FUN_00457a28 */

/* Out-of-slice copy/store/destroy helpers (already decompiled or next-slice). */
extern void     sk_h_4630d8(void);                       /* FUN_004630d8 */
extern void     sk_h_462b6c(void);                       /* FUN_00462b6c */
extern void     sk_h_462c98(void);                       /* FUN_00462c98 */
extern void     sk_h_4627d0(void);                       /* FUN_004627d0 */
extern void     sk_h_463810(word_t, word_t, word_t, word_t); /* FUN_00463810 */
extern void     sk_h_462fec(word_t, word_t, word_t, word_t); /* FUN_00462fec */
extern cL4_w16_t sk_h_46306c(void);                      /* FUN_0046306c */
extern cL4_w16_t sk_rt_463028(word_t, word_t, word_t, word_t); /* FUN_00463028 */
extern void     sk_noop_463058(void);                    /* FUN_00463058 */
extern void     sk_rt_463080(void);                      /* FUN_00463080 */
extern word_t   sk_rt_463454(word_t);                    /* FUN_00463454 */
extern void     sk_h_46337c(void);                       /* FUN_0046337c */
extern void     sk_h_464954(void);                       /* FUN_00464954 */
extern void     sk_h_464f40(word_t, word_t, word_t, word_t, word_t, word_t, word_t, word_t); /* FUN_00464f40 */
extern void     sk_h_464dcc(void);                       /* FUN_00464dcc */
extern void     sk_h_463750(void);                       /* FUN_00463750 */
extern void     sk_h_4632b8(void);                       /* FUN_004632b8 */
extern void     sk_h_463a10(void);                       /* FUN_00463a10 */
extern void     sk_h_463a48(void);                       /* FUN_00463a48 */
extern void     sk_h_463aa0(void);                      /* FUN_00463aa0 */
extern void     sk_h_464ae8(void);                       /* FUN_00464ae8 */
extern void     sk_h_464b04(void);                       /* FUN_00464b04 */
extern void     sk_h_4653cc(void);                       /* FUN_004653cc */
extern void     sk_h_4656e0(void);                       /* FUN_004656e0 */
extern void     sk_h_465950(void);                       /* FUN_00465950 */
extern cL4_w16_t sk_h_464a50(void);                      /* FUN_00464a50 */
extern void     sk_h_464e9c(void);                       /* FUN_00464e9c */
extern void     sk_h_4638d8(void);                       /* FUN_004638d8 */
extern void     sk_h_462e54(word_t);                     /* FUN_00462e54 */
extern void     sk_h_462e88(void);                       /* FUN_00462e88 */
extern void     sk_h_462b90(word_t);                     /* FUN_00462b90 */
extern void     sk_h_462bd8(word_t);                     /* FUN_00462bd8 */
extern void     sk_h_461d78(void);                       /* FUN_00461d78 */
extern void     sk_h_461610(word_t, word_t, word_t);     /* FUN_00461610 */
extern void     sk_h_462758(word_t, word_t, word_t);     /* FUN_00462758 */
extern void     sk_h_462848(word_t);                     /* FUN_00462848 */
extern void     sk_h_46303c(void);                       /* FUN_0046303c */
extern void     sk_noop_463504(word_t);                  /* FUN_00463504 */

/* Copy/store field helpers (named in manifest). */
extern void     sk_store8words_5e18(void);               /* FUN_00465e18 */
extern cL4_w16_t sk_copy_wordpair_64064(word_t);         /* FUN_00464064 */
extern cL4_w16_t sk_copy_word_640b8(void);               /* FUN_004640b8 */
extern void     sk_store_regs_640d0(void);               /* FUN_004640d0 */
extern void     sk_copy_fields_641e8(void);              /* FUN_004641e8 */
extern void     sk_copy_and_acquire_64354(void);         /* FUN_00464354 */
extern word_t   sk_nop_644cc(word_t, word_t, word_t);    /* FUN_004644cc (returns desc ptr) */
extern void     sk_copy_word_64504(void);                /* FUN_00464504 */
extern void     sk_copy_fields_645d8(void);              /* FUN_004645d8 */
extern void     sk_nop_64864(void);                      /* FUN_00464864 */
extern void     sk_copy5words_5a50(void);                /* FUN_00465a50 */
extern void     sk_store_load_ref_5b1c(void);            /* FUN_00465b1c */
extern void     sk_fill14words_5c24(void);               /* FUN_00465c24 */
extern void     sk_nop_5c98(word_t);                     /* FUN_00465c98 */
extern void     sk_copy2words_5d28(void);                /* FUN_00465d28 */
extern void     sk_copy1byte_5ee0(word_t);               /* FUN_00465ee0 */
extern void     sk_copy6words_5eec(word_t, word_t, word_t, word_t, word_t, word_t, word_t, word_t, word_t); /* FUN_00465eec */
extern void     sk_copy5words_5f20(void);                /* FUN_00465f20 */
extern word_t   sk_script_desc_5f34(word_t);             /* FUN_00465f34 */
extern void     sk_copy2words_5f68(void);                /* FUN_00465f68 */
extern void     sk_nop_6130(void);                       /* FUN_00466130 */
extern void     sk_copy2words_61a4(void);                /* FUN_004661a4 */
extern void     sk_nop_661fc(void);                      /* FUN_004661fc */
extern void     sk_copy_word_66220(void);                /* FUN_00466220 */
extern void     sk_copy_fields_66374(void);              /* FUN_00466374 */
extern void     sk_nop_664b8(void);                      /* FUN_004664b8 */
extern void     sk_release_666c0(void);                  /* FUN_004666c0 */
extern void     sk_cmp_463484(void);                     /* FUN_00463484 */
extern void     sk_cmp_463344(void);                     /* FUN_00463344 */
extern void     sk_rt_463358(word_t);                    /* FUN_00463358 */

/* ------------------------------------------------------------------ *
 * In-slice forward declarations.
 * ------------------------------------------------------------------ */
static void     sk_md_45c160(word_t obj);
static void     sk_md_45c1e0(word_t a, word_t b, word_t c, word_t d, int op);
static void     sk_md_45cdf0(word_t p2, word_t p4, word_t sel);
static void     sk_md_45d0ac(word_t p2, word_t p4, word_t sel);
static word_t   sk_sw_slice_bound(word_t lo, word_t hi, word_t len, word_t opts);
static void     sk_md_460e78(word_t, word_t, word_t, word_t);

static void     sk_md_4607ac(word_t p1, word_t p2);
static void     sk_md_4607c4(word_t *p, word_t p2, void (*h)(word_t, word_t, word_t, word_t, byte));
static void     sk_md_4607e0(word_t *dst, word_t w20, word_t w21, word_t w22, word_t w23);
static void     sk_md_460d50(word_t p1, word_t p2, word_t p3, word_t p4, word_t *out);
static void     sk_md_460d1c(void);
static void     sk_md_460b14(word_t dst, word_t src);
static void     sk_md_4610a8(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);

/* ==================================================================== *
 * Function bodies
 * ==================================================================== */

/* FUN_0045bdbc @ 0x0045bdbc  (est. sk_md_copy16_fields_bdbc)
 * Ghidra: void FUN_0045bdbc(void)
 * Copies 16 bytes (4 words: +0x10..+0x38) from the object returned by
 * sk_copy16 into the destination at unaff_x19, then performs the trailing
 * ref-retain barrier. Mirror of sk_md_45cca4 / sk_md_45e800.
 * Confidence: medium
 * Notes: FUN_00350e04 = sk_copy16 (returns {dst,src}); thunk_FUN_0036b270 = retain. */
static void sk_md_45bdbc(word_t dst, word_t src)
{
    word_t w;

    (void)cL4_copy16();
    w = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = w;
    w = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = w;
    (void)cL4_ref_retain(0);
}

/* FUN_0045bdf4 @ 0x0045bdf4  (est. sk_md_destroy_cascade_bdf4)
 * Ghidra: void FUN_0045bdf4(void)
 * Chains a sequence of destroy/release sub-operations (word copy, field copy,
 * retain barrier, token release, cmp, store) and ends with a final copy-word.
 * No locals or branches — a pure call sequence.
 * Confidence: medium
 * Notes: FUN_0034b264=word_copy, FUN_00463484=sk_cmp_463484, FUN_00464504=copy_word,
 *   FUN_004632b8=sk_h_4632b8, FUN_00466220=copy_word. */
static void sk_md_45bdf4(void)
{
    (void)cL4_word_copy();
    (void)sk_cmp_463484();
    (void)cL4_ref_retain(0);
    (void)cL4_token_release(0);
    (void)sk_copy_word_64504();
    (void)sk_h_4632b8();
    (void)sk_copy_word_66220();
}

/* FUN_0045be3c @ 0x0045be3c  (est. sk_md_copy_fields_release_be3c)
 * Ghidra: void FUN_0045be3c(void)
 * Copies the +0x10..+0x38 words from the object returned by sk_h_46306c into
 * dst (unaff_x20), releasing the old +0x18 token of the source row, then copies
 * the +0x20..+0x38 words from unaff_x19 into dst. Faithful to the decompile.
 * Confidence: medium
 * Notes: FUN_0046306c returns {dst,src}; FUN_003a25d4 = token release. */
static void sk_md_45be3c(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t w;

    pr = sk_h_46306c();
    w = *(word_t *)(pr.hi + 0x18);
    *(word_t *)(dst + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(dst + 0x18) = w;
    cL4_token_release(*(word_t *)(pr.lo + 0x18));
    w = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = w;
}

/* FUN_0045be8c @ 0x0045be8c  (est. sk_md_copy_fields_retain_be8c)
 * Ghidra: void FUN_0045be8c(void)
 * Copies +0x10..+0x30 words from the pair returned by cL4_copy16 into the
 * destination at unaff_x19, then applies the trailing retain barrier.
 * Confidence: medium
 * Notes: FUN_00350e04 = sk_copy16 {lo=dst, hi=src}; thunk_FUN_0036b270 = retain. */
static void sk_md_45be8c(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t w;

    pr = cL4_copy16();
    w = *(word_t *)(pr.hi + 0x18);
    *(word_t *)(pr.lo + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 0x18) = w;
    *(word_t *)(dst + 0x20) = *(word_t *)(pr.hi + 0x20);
    w = *(word_t *)(pr.hi + 0x28);
    *(word_t *)(dst + 0x30) = *(word_t *)(pr.hi + 0x30);
    *(word_t *)(dst + 0x28) = w;
    (void)cL4_ref_retain(0);
}

/* FUN_0045becc @ 0x0045becc  (est. sk_md_copy_words_retain_becc)
 * Ghidra: void FUN_0045becc(void)
 * Copies the +0x10..+0x20 words from the pair returned by sk_copy_word_640b8
 * into its destination, retaining the new +0x20 token and releasing the old
 * one held in unaff_x20. Ends with sk_h_4632b8.
 * Confidence: medium
 * Notes: FUN_0034cdb4=byte_copy, FUN_004640b8=copy_word, thunk retain, 003a25d4 release. */
static void sk_md_45becc(word_t self)
{
    cL4_w16_t pr;
    word_t w;

    (void)cL4_byte_copy();
    pr = sk_copy_word_640b8();
    *(word_t *)(pr.lo + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 0x18) = *(word_t *)(pr.hi + 0x18);
    w = *(word_t *)(self + 0x20);
    *(word_t *)(self + 0x20) = *(word_t *)(pr.hi + 0x20);
    (void)cL4_ref_retain(0);
    cL4_token_release(w);
    (void)sk_h_4632b8();
}

/* FUN_0045bf28 @ 0x0045bf28  (est. sk_md_copy_words_release_bf28)
 * Ghidra: void FUN_0045bf28(void)
 * Copies +8..+0x20 words from the byte_copy pair into the destination (lo),
 * releasing the old +0x20 token, then stores +0x18 from the src row into
 * unaff_x20. Ends with sk_h_4653cc.
 * Confidence: medium
 * Notes: FUN_0034cdb4=byte_copy, 003a25d4=token release. */
static void sk_md_45bf28(word_t self)
{
    cL4_w16_t pr;
    word_t w, old;

    pr = cL4_byte_copy();
    w = *(word_t *)(pr.hi + 8);
    *(word_t *)(pr.lo + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 8) = w;
    w = *(word_t *)(pr.hi + 0x20);
    old = *(word_t *)(pr.lo + 0x20);
    *(word_t *)(self + 0x18) = *(word_t *)(pr.hi + 0x18);
    *(word_t *)(self + 0x20) = w;
    cL4_token_release(old);
    (void)sk_h_4653cc();
}

/* FUN_0045c160 @ 0x0045c160  (est. sk_md_retain_by_tag_c160)
 * Ghidra: void FUN_0045c160(void)
 * Retain dispatcher keyed off the low 3 bits of the word at in_stack+0x28
 * (a tagged operand): tag==3 routes to sk_md_45c1e0 then retain of the masked
 * operand; tag==1 or tag==0 routes to sk_h_45a1f8; any other nonzero tag is
 * ignored (nothing retained). Faithful to the decompile's branch structure.
 * Confidence: medium
 * Notes: the low-3-bit field is a Swift enum/tagged-payload discriminator. */
static void sk_md_45c160(word_t tagged)
{
    unsigned tag = (unsigned)tagged & 7u;

    if (tag == 3) {
        sk_md_45c1e0(0, 0, 0, 0, 0);
        (void)cL4_ref_retain(tagged & ~7u);
        return;
    }
    if (tag != 1 && (tagged & 7u) != 0) {
        return;
    }
    sk_h_45a1f8();
}

/* FUN_0045c1e0 @ 0x0045c1e0  (est. sk_md_retain_by_op_c1e0)
 * Ghidra: void FUN_0045c1e0(param_1..param_4)
 * Retain-by-opcode dispatcher: the byte at in_stack+0x10 selects how many of
 * the register operands to retain. op==2 retains param_4 and in_x7; op==1
 * retains param_2 then falls through to retain param_2 again (via in_x7
 * reassignment); op==0 retains param_2; any other op retains nothing.
 * Confidence: medium
 * Notes: mirrors the Swift boxed-value retain (copy/retain) helper family. */
static void sk_md_45c1e0(word_t p2, word_t p4, word_t x7, word_t p, int op)
{
    if (op == 2) {
        (void)cL4_ref_retain(p4);
        (void)cL4_ref_retain(x7);
        return;
    }
    if (op == 1) {
        (void)cL4_ref_retain(p2);
        p2 = x7;
    } else if (op != 0) {
        return;
    }
    (void)cL4_ref_retain(p2);
}

/* FUN_0045c258 @ 0x0045c258  (est. sk_md_destroy_release_pair_c258)
 * Ghidra: void FUN_0045c258(long param_1)
 * Destroys a descriptor row at param_1: runs the no-op + 3540d0 + 4593ac
 * sequence, then releases the two tagged refcounted fields at +0xa0 and +0xc0
 * (masking off the low 3 tag bits).
 * Confidence: medium
 * Notes: FUN_00464954, FUN_003540d0, FUN_004593ac are sub-destroy steps. */
static void sk_md_45c258(word_t self)
{
    (void)sk_h_464954();
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    cL4_ref_release(*(word_t *)(self + 0xa0) & 0xfffffffffffffffUL);
    cL4_ref_release(*(word_t *)(self + 0xc0) & 0xfffffffffffffffUL);
}

/* FUN_0045c2a8 @ 0x0045c2a8  (est. sk_md_copy_field_block_retain_c2a8)
 * Ghidra: void FUN_0045c2a8(void)
 * Rebuilds a large descriptor row at unaff_x19 from the source rows returned
 * by the leading call sequence, copying +0x50..+0xc0, then retains the two
 * tagged refcounted fields at +0xa0 and +0xc0.
 * Confidence: medium
 * Notes: FUN_00356f9c / 00350e04 / 004661fc / 004627d0 / 0045c160 / 00465e18
 *   are the per-field copy/retain sub-steps. */
static void sk_md_45c2a8(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f, g, h;

    (void)sk_syscall_stub_356f9c();
    (void)cL4_copy16();
    (void)sk_nop_661fc();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    g = *(word_t *)(src + 0x80);
    h = *(word_t *)(src + 0x88);
    (void)sk_h_4627d0();
    sk_md_45c160(0);
    (void)sk_store8words_5e18();
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    *(word_t *)(dst + 0x80) = g;
    *(word_t *)(dst + 0x88) = h;
    a = *(word_t *)(src + 0x90);
    *(word_t *)(dst + 0x98) = *(word_t *)(src + 0x98);
    *(word_t *)(dst + 0x90) = a;
    a = *(word_t *)(src + 0xa0);
    *(word_t *)(dst + 0xa0) = a;
    *(byte *)(dst + 0xb8) = *(byte *)(src + 0xb8);
    a = *(word_t *)(src + 0xa8);
    *(word_t *)(dst + 0xb0) = *(word_t *)(src + 0xb0);
    *(word_t *)(dst + 0xa8) = a;
    a = *(word_t *)(src + 0xc0);
    *(word_t *)(dst + 0xc0) = a;
    (void)cL4_ref_retain(*(word_t *)(dst + 0xa0) & 0xfffffffffffffffUL);
    (void)cL4_ref_retain(*(word_t *)(dst + 0xc0) & 0xfffffffffffffffUL);
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045c380 @ 0x0045c380  (est. sk_md_copy_field_block_retain_c380)
 * Ghidra: void FUN_0045c380(void)
 * Rebuilds a descriptor row at unaff_x19 copying +0x50..+0x88 from the source
 * row, then copies +0x90..+0xc0 including the two tagged refcounted fields at
 * +0xa0 and +0xc0 — retaining the new values and releasing the old ones.
 * Confidence: medium
 * Notes: FUN_0034f2f4=word_copy_b, 004640b8=copy_word, 004661fc=nop,
 *   004627d0, 0045c160, 00465e18 are the copy/retain sub-steps. */
static void sk_md_45c380(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f, g, h;
    word_t n, old;

    (void)sk_syscall_stub_356f9c();
    (void)cL4_word_copy_b();
    (void)sk_copy_word_640b8();
    (void)sk_nop_661fc();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    g = *(word_t *)(src + 0x80);
    h = *(word_t *)(src + 0x88);
    (void)sk_h_4627d0();
    sk_md_45c160(0);
    (void)sk_store8words_5e18();
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    *(word_t *)(dst + 0x80) = g;
    *(word_t *)(dst + 0x88) = h;
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    *(word_t *)(dst + 0x90) = *(word_t *)(src + 0x90);
    *(word_t *)(dst + 0x98) = *(word_t *)(src + 0x98);
    n = *(word_t *)(src + 0xa0);
    old = *(word_t *)(dst + 0xa0);
    *(word_t *)(dst + 0xa0) = n;
    (void)cL4_ref_retain(n & 0xfffffffffffffffUL);
    cL4_ref_release(old & 0xfffffffffffffffUL);
    a = *(word_t *)(src + 0xb0);
    b = *(word_t *)(src + 0xa8);
    *(byte *)(dst + 0xb8) = *(byte *)(src + 0xb8);
    *(word_t *)(dst + 0xb0) = a;
    *(word_t *)(dst + 0xa8) = b;
    n = *(word_t *)(src + 0xc0);
    old = *(word_t *)(dst + 0xc0);
    *(word_t *)(dst + 0xc0) = n;
    (void)cL4_ref_retain(n & 0xfffffffffffffffUL);
    cL4_ref_release(old & 0xfffffffffffffffUL);
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045c4ac @ 0x0045c4ac  (est. sk_md_copy_block19_release_c4ac)
 * Ghidra: void FUN_0045c4ac(void)
 * Copies the full 19-word (0x98-byte) block from unaff_x20 into unaff_x19,
 * then releases the two tagged refcounted fields at +0x14 and +0x18 (masking
 * the low 3 tag bits).
 * Confidence: medium
 * Notes: FUN_00350c5c=syscall_save_ret, 00464954, 003540d0, 004593ac are
 *   the surrounding copy/teardown steps. */
static void sk_md_45c4ac(word_t dst, word_t src)
{
    word_t a, b, c;

    (void)sk_syscall_save_ret();
    (void)sk_h_464954();
    a = *(word_t *)(src + 0x00);
    b = *(word_t *)(src + 0x18);
    c = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x08) = *(word_t *)(src + 0x08);
    *(word_t *)(dst + 0x00) = a;
    *(word_t *)(dst + 0x18) = b;
    *(word_t *)(dst + 0x10) = c;
    a = *(word_t *)(src + 0x20);
    b = *(word_t *)(src + 0x38);
    c = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = a;
    *(word_t *)(dst + 0x38) = b;
    *(word_t *)(dst + 0x30) = c;
    a = *(word_t *)(src + 0x40);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x50);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x40) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x50) = c;
    a = *(word_t *)(src + 0x60);
    b = *(word_t *)(src + 0x78);
    c = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x68) = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x60) = a;
    *(word_t *)(dst + 0x78) = b;
    *(word_t *)(dst + 0x70) = c;
    a = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x88) = *(word_t *)(src + 0x88);
    *(word_t *)(dst + 0x80) = a;
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    a = *(word_t *)(src + 0x90);
    *(word_t *)(dst + 0x98) = *(word_t *)(src + 0x98);
    *(word_t *)(dst + 0x90) = a;
    a = *(word_t *)(dst + 0xa0);
    *(word_t *)(dst + 0xa0) = *(word_t *)(src + 0xa0);
    cL4_ref_release(a & 0xfffffffffffffffUL);
    a = *(word_t *)(src + 0xa8);
    *(word_t *)(dst + 0xb0) = *(word_t *)(src + 0xb0);
    *(word_t *)(dst + 0xa8) = a;
    *(byte *)(dst + 0xb8) = *(byte *)(src + 0xb8);
    a = *(word_t *)(dst + 0xc0);
    *(word_t *)(dst + 0xc0) = *(word_t *)(src + 0xc0);
    cL4_ref_release(a & 0xfffffffffffffffUL);
}

/* FUN_0045c61c @ 0x0045c61c  (est. sk_md_copy_block16_c61c)
 * Ghidra: void FUN_0045c61c(void)
 * Copies a 16-word field block (+0x20..+0x88) into unaff_x20, interleaving
 * the store_regs helper for +0x20..+0x48.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, 00462c98, 004627d0, 0045c160, 004640d0 store. */
static void sk_md_45c61c(word_t dst, word_t src, word_t r25, word_t r26, word_t r27, word_t r28)
{
    word_t a, b, c, d, e, f;

    (void)sk_syscall_stub_356f9c();
    (void)sk_reg_4d0();
    (void)sk_h_462c98();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    (void)sk_h_4627d0();
    sk_md_45c160(0);
    (void)sk_store_regs_640d0();
    *(word_t *)(dst + 0x20) = r25;
    *(word_t *)(dst + 0x28) = r26;
    *(word_t *)(dst + 0x30) = r27;
    *(word_t *)(dst + 0x38) = r28;
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    a = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x88) = *(word_t *)(src + 0x88);
    *(word_t *)(dst + 0x80) = a;
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045c6bc @ 0x0045c6bc  (est. sk_md_rebuild_block_release_c6bc)
 * Ghidra: void FUN_0045c6bc(void)
 * Rebuilds a descriptor row: copies +0x50..+0x78, recomputes the +0x40..+0x48
 * pair via sk_h_462fec, and copies +0x80..+0x88 from unaff_x20.
 * Confidence: medium
 * Notes: FUN_00350c5c=syscall_save_ret, 00462c98, 004627d0, 0045c160,
 *   00463080, 00462fec, 003540d0, 004593ac, 00356f80. */
static void sk_md_45c6bc(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f;

    (void)sk_syscall_stub_356f9c();
    (void)sk_syscall_save_ret();
    (void)sk_h_462c98();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    (void)sk_h_4627d0();
    sk_md_45c160(0);
    (void)sk_rt_463080();
    (void)sk_h_462fec(*(word_t *)(dst + 0x70), *(word_t *)(dst + 0x40),
                      *(word_t *)(dst + 0x50), *(word_t *)(dst + 0x60));
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    *(word_t *)(dst + 0x80) = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x88) = *(word_t *)(src + 0x88);
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045c780 @ 0x0045c780  (est. sk_md_copy_block18_c780)
 * Ghidra: void FUN_0045c780(void)
 * Copies an 18-word (0x90-byte) block from unaff_x19 into unaff_x20.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, 00465f34, 003540d0, 004593ac. */
static void sk_md_45c780(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f;

    (void)sk_reg_4d0();
    (void)sk_script_desc_5f34(0);
    a = *(word_t *)(dst + 0x40);
    b = *(word_t *)(dst + 0x50);
    c = *(word_t *)(dst + 0x60);
    d = *(word_t *)(src + 0x00);
    e = *(word_t *)(src + 0x18);
    f = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x08) = *(word_t *)(src + 0x08);
    *(word_t *)(dst + 0x00) = d;
    *(word_t *)(dst + 0x18) = e;
    *(word_t *)(dst + 0x10) = f;
    d = *(word_t *)(src + 0x20);
    e = *(word_t *)(src + 0x38);
    f = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = d;
    *(word_t *)(dst + 0x38) = e;
    *(word_t *)(dst + 0x30) = f;
    d = *(word_t *)(src + 0x40);
    e = *(word_t *)(src + 0x58);
    f = *(word_t *)(src + 0x50);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x40) = d;
    *(word_t *)(dst + 0x58) = e;
    *(word_t *)(dst + 0x50) = f;
    d = *(word_t *)(src + 0x60);
    e = *(word_t *)(src + 0x78);
    f = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x68) = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x60) = d;
    *(word_t *)(dst + 0x78) = e;
    *(word_t *)(dst + 0x70) = f;
    (void)sk_gap14_noop_3540d0(a, b, c);
    (void)sk_h_4593ac();
    d = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x88) = *(word_t *)(src + 0x88);
    *(word_t *)(dst + 0x80) = d;
}

/* FUN_0045c89c @ 0x0045c89c  (est. sk_md_destroy_passthrough_c89c)
 * Ghidra: void FUN_0045c89c(undefined8 *param_1)
 * Runs the 644cc nop-desc build on param_1's words, then the 3540d0 + 4593ac
 * teardown sequence using words at +0x40/+0x50/+0x60 of the built descriptor.
 * Confidence: medium
 * Notes: FUN_004644cc=sk_nop_644cc returns a descriptor pointer. */
static void sk_md_45c89c(word_t *p)
{
    word_t d;

    d = (word_t)sk_nop_644cc(p[0], (word_t)p, p[1]);
    (void)sk_gap14_noop_3540d0(*(word_t *)(d + 0x40), *(word_t *)(d + 0x50),
                               *(word_t *)(d + 0x60));
    (void)sk_h_4593ac();
}

/* FUN_0045c8dc @ 0x0045c8dc  (est. sk_md_rebuild_block_release_c8dc)
 * Ghidra: void FUN_0045c8dc(void)
 * Rebuilds a descriptor row copying +0x50..+0x78, recomputing +0x40..+0x48 via
 * sk_h_463810, and copies +0x80..+0x88. Mirror of sk_md_45c970.
 * Confidence: medium
 * Notes: FUN_00356f9c, 004630d8, 00462b6c, 00464864, 0045c160, 00463080,
 *   00463810, 003540d0, 004593ac, 00356f80. */
static void sk_md_45c8dc(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f;

    (void)sk_syscall_stub_356f9c();
    (void)sk_h_4630d8();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    (void)sk_h_462b6c();
    (void)sk_nop_64864();
    sk_md_45c160(0);
    (void)sk_h_463810(0, 0, 0, 0);
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045c970 @ 0x0045c970  (est. sk_md_rebuild_block_release_c970)
 * Ghidra: void FUN_0045c970(void)
 * Same shape as sk_md_45c8dc but the +0x40..+0x48 recompute uses sk_h_463810
 * and the store of +0x40 happens first.
 * Confidence: medium */
static void sk_md_45c970(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f;

    (void)sk_syscall_stub_356f9c();
    (void)sk_h_4630d8();
    a = *(word_t *)(src + 0x50);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x60);
    d = *(word_t *)(src + 0x68);
    e = *(word_t *)(src + 0x70);
    f = *(word_t *)(src + 0x78);
    (void)sk_h_462b6c();
    (void)sk_nop_64864();
    sk_md_45c160(0);
    (void)sk_rt_463080();
    (void)sk_h_463810(*(word_t *)(dst + 0x70), *(word_t *)(dst + 0x40),
                      *(word_t *)(dst + 0x50), *(word_t *)(dst + 0x60));
    *(word_t *)(dst + 0x50) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x60) = c;
    *(word_t *)(dst + 0x68) = d;
    *(word_t *)(dst + 0x70) = e;
    *(word_t *)(dst + 0x78) = f;
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    (void)sk_syscall_stub_356f80();
}

/* FUN_0045ca30 @ 0x0045ca30  (est. sk_md_copy_acquire_block_ca30)
 * Ghidra: void FUN_0045ca30(undefined1 param_1[16], undefined1 param_2[16])
 * Restores register state, computes a new field row via sk_rt_463028, copies
 * the +0x00..+0x60 words into unaff_x19, then runs the 3540d0/4593ac teardown.
 * Confidence: medium
 * Notes: FUN_00352b20=exc_restore_regs; FUN_00463028=sk_rt_463028. */
static void sk_md_45ca30(word_t dst, word_t *rest)
{
    cL4_w16_t pr;
    word_t a, b, c, d;

    (void)exc_restore_regs();
    (void)sk_rt_463028(0, 0, 0, 0);
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
    pr = sk_rt_463028(0, 0, 0, 0);
    a = *(word_t *)(pr.hi + 0x00);
    b = *(word_t *)(pr.hi + 0x18);
    c = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(dst + 0x08) = *(word_t *)(pr.hi + 0x08);
    *(word_t *)(dst + 0x00) = a;
    *(word_t *)(dst + 0x18) = b;
    *(word_t *)(dst + 0x10) = c;
    a = *(word_t *)(pr.hi + 0x20);
    b = *(word_t *)(pr.hi + 0x38);
    c = *(word_t *)(pr.hi + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(pr.hi + 0x28);
    *(word_t *)(dst + 0x20) = a;
    *(word_t *)(dst + 0x38) = b;
    *(word_t *)(dst + 0x30) = c;
    a = *(word_t *)(pr.hi + 0x40);
    b = *(word_t *)(pr.hi + 0x58);
    c = *(word_t *)(pr.hi + 0x50);
    *(word_t *)(dst + 0x48) = *(word_t *)(pr.hi + 0x48);
    *(word_t *)(dst + 0x40) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x50) = c;
    a = *(word_t *)(pr.hi + 0x60);
    b = *(word_t *)(pr.hi + 0x78);
    c = *(word_t *)(pr.hi + 0x70);
    *(word_t *)(dst + 0x68) = *(word_t *)(pr.hi + 0x68);
    *(word_t *)(dst + 0x60) = a;
    *(word_t *)(dst + 0x78) = b;
    *(word_t *)(dst + 0x70) = c;
    (void)sk_gap14_noop_3540d0(0, 0, 0);
    (void)sk_h_4593ac();
}

/* FUN_0045cca4 @ 0x0045cca4  (est. sk_md_copy16_fields_retain_cca4)
 * Ghidra: void FUN_0045cca4(void)
 * Copies +0x10..+0x28 from the copy16 pair into the destination at unaff_x19,
 * then applies the trailing retain barrier. Mirror of sk_md_45bdbc.
 * Confidence: medium
 * Notes: FUN_00350e04=copy16; thunk_FUN_0036b270=retain. */
static void sk_md_45cca4(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t w;

    pr = cL4_copy16();
    w = *(word_t *)(pr.hi + 0x18);
    *(word_t *)(dst + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(dst + 0x18) = w;
    w = *(word_t *)(pr.hi + 0x20);
    *(word_t *)(dst + 0x28) = *(word_t *)(pr.hi + 0x28);
    *(word_t *)(dst + 0x20) = w;
    (void)cL4_ref_retain(0);
}

/* FUN_0045ccdc @ 0x0045ccdc  (est. sk_md_destroy_cascade_ccdc)
 * Ghidra: void FUN_0045ccdc(void)
 * Chains byte_copy, cmp_463484, retain, release, cmp_463344.
 * Confidence: medium */
static void sk_md_45ccdc(void)
{
    (void)cL4_byte_copy();
    (void)sk_cmp_463484();
    (void)cL4_ref_retain(0);
    (void)cL4_ref_release(0);
    (void)sk_cmp_463344();
}

/* FUN_0045cd1c @ 0x0045cd1c  (est. sk_md_copy_words_release_cd1c)
 * Ghidra: void FUN_0045cd1c(void)
 * Copies +8..+0x18 from the byte_copy pair into its destination, releasing the
 * old +0x18 token, then copies +0x20..+0x28 from unaff_x19 into unaff_x20.
 * Confidence: medium
 * Notes: FUN_0034cdb4=byte_copy, 0036b118=release. */
static void sk_md_45cd1c(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t w;

    pr = cL4_byte_copy();
    w = *(word_t *)(pr.hi + 8);
    *(word_t *)(pr.lo + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 8) = w;
    w = *(word_t *)(pr.lo + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(pr.hi + 0x18);
    cL4_ref_release(w);
    w = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = w;
}

/* FUN_0045cdf0 @ 0x0045cdf0  (est. sk_md_variant_retain_by_topbits_cdf0)
 * Ghidra: void FUN_0045cdf0(param_1..param_5, ...rest)
 * Variant retain dispatcher keyed off the top 3 bits (>>0x3d) of the trailing
 * stack word. Default (0): retain param_5 (== param_4). Case 1: run sk_h_45a4b4
 * on the 20 stacked register/stack args then retain (masked) the selector word.
 * Case 2: run sk_h_45a4b4 and return. Cases 3/4: retain param_2 and return.
 * Case 5: retain with no explicit arg, then fall to retain(param_5).
 * Confidence: medium
 * Notes: top-3-bit selector is the Swift boxed-value discriminator; the
 *   20-arg call is the boxed "copy" path. */
static void sk_md_45cdf0(word_t p2, word_t p4, word_t sel)
{
    switch (sel >> 0x3d) {
    case 1:
        sk_h_45a4b4();
        (void)cL4_ref_retain(sel & 0x1fffffffffffffffUL);
        break;
    case 2:
        sk_h_45a4b4();
        break;
    case 3:
    case 4:
        (void)cL4_ref_retain(p2);
        break;
    case 5:
        (void)cL4_ref_retain(0);
        (void)cL4_ref_retain(p4);
        break;
    default:
        (void)cL4_ref_retain(p4);
        break;
    }
}

/* FUN_0045d028 @ 0x0045d028  (est. sk_md_destroy_passthrough_d028)
 * Ghidra: void FUN_0045d028(undefined8 *param_1)
 * Builds a descriptor via sk_nop_644cc, runs the swift_runtime_noop step with
 * the +0x40..+0x80 words, then chains sk_md_45d0ac.
 * Confidence: medium */
static void sk_md_45d028(word_t *p)
{
    word_t d;

    d = (word_t)sk_nop_644cc(p[0], (word_t)p, p[1]);
    swift_runtime_noop(*(word_t *)(d + 0x40), *(word_t *)(d + 0x50),
                       *(word_t *)(d + 0x60), *(word_t *)(d + 0x70),
                       *(word_t *)(d + 0x80));
    (void)sk_md_45d0ac(0, 0, 0);
}

/* FUN_0045d0ac @ 0x0045d0ac  (est. sk_md_variant_release_by_topbits_d0ac)
 * Ghidra: void FUN_0045d0ac(param_1..param_5, ...rest)
 * Variant release dispatcher keyed off the top 3 bits (>>0x3d) of the trailing
 * stack word. Default: release(param_5==param_4). Case 1: sk_h_459138 on the
 * 20 stacked args then release the (masked) selector word. Case 2: sk_h_459138
 * and return. Cases 3/4: token-release param_2 and return. Case 5: release
 * with no arg then fall to release(param_5).
 * Confidence: medium */
static void sk_md_45d0ac(word_t p2, word_t p4, word_t sel)
{
    switch (sel >> 0x3d) {
    case 1:
        sk_h_459138();
        cL4_ref_release(sel & 0x1fffffffffffffffUL);
        break;
    case 2:
        sk_h_459138();
        break;
    case 3:
    case 4:
        cL4_token_release(p2);
        break;
    case 5:
        cL4_ref_release(0);
        cL4_ref_release(p4);
        break;
    default:
        cL4_ref_release(p4);
        break;
    }
}

/* FUN_0045d2e4 @ 0x0045d2e4  (est. sk_md_copy_launch_image_fields_d2e4)
 * Ghidra: void FUN_0045d2e4(void)
 * Loads the VM launch image (cL4_vm_build_launch_image), stages a large block
 * of its fields, invokes the variant-retain dispatcher, then copies the
 * remaining fields back and finalizes with cL4_vm_launch_setup. Large (0x160+
 * bytes) descriptor-row rebuild.
 * Confidence: medium
 * Notes: FUN_0008e518=cL4_vm_build_launch_image, FUN_003509b0=reg_9b0,
 *   FUN_0045cdf0=variant retain, FUN_0034f8e4=swift_runtime_noop,
 *   FUN_0045d0ac=variant release, FUN_0008e500=cL4_vm_launch_setup. */
static void sk_md_45d2e4(word_t dst, word_t x30)
{
    cL4_w16_t img;
    word_t *src;

    img = cL4_vm_build_launch_image();
    src = (word_t *)img.hi;
    (void)sk_reg_9b0();
    (void)sk_md_45cdf0(img.lo, img.hi, 0);
    (void)sk_md_45d0ac(0, 0, 0);
    cL4_vm_launch_setup((word_t)src, x30);
}

/* FUN_0045d540 @ 0x0045d540  (est. sk_md_copy_launch_image_block_d540)
 * Ghidra: void FUN_0045d540(void)
 * Loads the VM launch image, stages its whole field block, invokes the variant
 * retain dispatcher, copies the fields into the destination, then finalizes
 * with cL4_vm_launch_setup. Large descriptor-row rebuild.
 * Confidence: medium
 * Notes: FUN_0008e518=cL4_vm_build_launch_image, FUN_0045cdf0=variant retain,
 *   FUN_0034f8e4=swift_runtime_noop, FUN_0045d0ac=variant release. */
static void sk_md_45d540(word_t dst, word_t x30)
{
    cL4_w16_t img;
    word_t *src;

    img = cL4_vm_build_launch_image();
    src = (word_t *)img.hi;
    (void)sk_md_45cdf0(img.lo, img.hi, 0);
    (void)sk_md_45d0ac(0, 0, 0);
    cL4_vm_launch_setup((word_t)src, x30);
}

/* FUN_0045d82c @ 0x0045d82c  (est. sk_md_copy_launch_image_d82c)
 * Ghidra: undefined8 * FUN_0045d82c(undefined8 *param_1, undefined8 param_2)
 * Rebuilds a 0x2e-word (0x170-byte) descriptor row at param_1 from the source
 * row returned by sk_h_462e54, then chains variant release and swift no-op.
 * Returns param_1.
 * Confidence: medium
 * Notes: FUN_00462e54, FUN_0034f8e4, FUN_0045d0ac. */
static word_t *sk_md_45d82c(word_t *out, word_t src)
{
    word_t a, b, c;

    (void)sk_h_462e54(src);
    (void)swift_runtime_noop(0, 0, 0, 0, 0);
    (void)sk_md_45d0ac(0, 0, 0);
    (void)swift_runtime_noop(0, 0, 0, 0, 0);
    (void)sk_md_45d0ac(0, 0, 0);
    return out;
}

/* FUN_0045d95c @ 0x0045d95c  (est. sk_md_init_block_flag_d95c)
 * Ghidra: void FUN_0045d95c(undefined8 *param_1, uint param_2, int param_3)
 * Initializes a descriptor row at param_1: when param_2 is negative (a
 * sentinel), zeros the +0x11..+0x20 range, runs the cmp helper on the masked
 * count, fills 14 words, and sets the +0x2f flag byte when param_3 < 0.
 * Otherwise, when param_3 < 0 clears the flag, and when param_2 != 0 initializes
 * the two sub-ranges via sk_mem_114330 and stores a packed length field.
 * Confidence: medium
 * Notes: FUN_00463358=sk_rt_463358, FUN_00465c24=fill14words,
 *   thunk_FUN_00114330=sk_mem_114330. The 0x98/0xd8 sizes are allocation
 *   extents for the two sub-ranges. */
static void sk_md_45d95c(word_t *p, uint n, int flag)
{
    if ((int)n < 0) {
        p[0x20] = 0; p[0x1f] = 0; p[0x1e] = 0; p[0x1d] = 0; p[0x1c] = 0;
        p[0x1b] = 0; p[0x1a] = 0; p[0x19] = 0; p[0x18] = 0; p[0x17] = 0;
        p[0x16] = 0; p[0x15] = 0; p[0x14] = 0; p[0x13] = 0; p[0x12] = 0;
        p[0x11] = 0;
        sk_rt_463358(n & 0x7fffffffU);
        (void)sk_fill14words_5c24();
        if (flag < 0) {
            *(byte *)(p + 0x2f) = 1;
        }
    } else {
        if (flag < 0) {
            *(byte *)(p + 0x2f) = 0;
        }
        if (n != 0) {
            sk_mem_114330((word_t)p, 0x98);
            p[0x13] = ((word_t)(-n) & 0xfffffffcUL) << 6 | ((word_t)(-n) & 3UL) << 2;
            sk_mem_114330((word_t)(p + 0x14), 0xd8);
        }
    }
}

/* FUN_0045da58 @ 0x0045da58  (est. sk_md_destroy_row_da58)
 * Ghidra: void FUN_0045da58(long param_1)
 * Destroys a row at param_1: releases the +0x90 and +0x150 tokens (with the
 * 459138 / 463454 steps), releases the +0x170 refcounted field.
 * Confidence: medium
 * Notes: FUN_00462e54, 00462b90, 00459138, 00463454, 0036b118. */
static void sk_md_45da58(word_t self)
{
    (void)sk_h_462e54(0);
    (void)sk_h_462b90(*(word_t *)(self + 0x90));
    (void)sk_h_459138();
    (void)sk_rt_463454(0);
    (void)sk_h_462b90(*(word_t *)(self + 0x150));
    (void)sk_h_459138();
    cL4_ref_release(*(word_t *)(self + 0x170));
}

/* FUN_0045dab4 @ 0x0045dab4  (est. sk_md_copy_large_row_retain_dab4)
 * Ghidra: void FUN_0045dab4(void)
 * Rebuilds a large (0x178-byte) descriptor row at unaff_x19 from the source
 * at unaff_x20, copying +0xa0..+0x178, then applies the trailing retain
 * barrier. Retains the +0x170 refcounted field.
 * Confidence: medium
 * Notes: FUN_00464b04, 00350c5c, 00462bd8, 00463058, 0034db28, 00464e9c,
 *   004638d8, 00464064, 0036b270, 00464ae8. */
static void sk_md_45dab4(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f;
    word_t i, j, k, l, m;

    (void)sk_h_464b04();
    (void)sk_syscall_save_ret();
    (void)sk_h_462bd8(0);
    (void)sk_noop_463058();
    (void)sk_h_34db28();
    (void)sk_h_464e9c();
    (void)sk_h_4638d8();
    a = *(word_t *)(src + 0xa0);
    b = *(word_t *)(src + 0xb8);
    c = *(word_t *)(src + 0xb0);
    *(word_t *)(dst + 0xa8) = *(word_t *)(src + 0xa8);
    *(word_t *)(dst + 0xa0) = a;
    *(word_t *)(dst + 0xb8) = b;
    *(word_t *)(dst + 0xb0) = c;
    i = *(word_t *)(src + 0xc0);
    j = *(word_t *)(src + 0xd0);
    k = *(word_t *)(src + 0xd8);
    l = *(word_t *)(src + 0xe0);
    m = *(word_t *)(src + 0xe8);
    f = *(word_t *)(src + 0xf0);
    (void)sk_copy_wordpair_64064(*(word_t *)(src + 0xc0));
    (void)sk_noop_463058();
    (void)sk_h_34db28();
    (void)sk_h_464e9c();
    *(word_t *)(dst + 0xc0) = i;
    *(word_t *)(dst + 0xc8) = i;
    *(word_t *)(dst + 0xd0) = j;
    *(word_t *)(dst + 0xd8) = k;
    *(word_t *)(dst + 0xe0) = l;
    *(word_t *)(dst + 0xe8) = m;
    *(word_t *)(dst + 0xf0) = f;
    a = *(word_t *)(src + 0x160);
    *(word_t *)(dst + 0x168) = *(word_t *)(src + 0x168);
    *(word_t *)(dst + 0x160) = a;
    *(word_t *)(dst + 0x170) = *(word_t *)(src + 0x170);
    (void)cL4_ref_retain(0);
    (void)sk_h_464ae8();
}

/* FUN_0045dbd0 @ 0x0045dbd0  (est. sk_md_copy_large_row_retain_dbd0)
 * Ghidra: void FUN_0045dbd0(void)
 * Rebuilds a large descriptor row at unaff_x19, copying the +0x40..+0x98
 * computation block, +0xb0..+0x158 field block, and +0x160..+0x170 tail with
 * retain/release of the refcounted fields.
 * Confidence: medium
 * Notes: mirror of sk_md_45dab4 with a +0x40..+0x98 prefix stage. */
static void sk_md_45dbd0(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f, g, h;
    word_t old;

    (void)sk_h_464b04();
    (void)sk_syscall_save_ret();
    (void)sk_h_462e88();
    (void)sk_h_462bd8(0);
    (void)sk_noop_463058();
    (void)sk_h_4627d0();
    (void)sk_h_45a4b4();
    (void)sk_rt_463080();
    (void)sk_h_463aa0();
    (void)sk_h_462fec(0, 0, 0, 0);
    a = *(word_t *)(src + 0xb0);
    *(word_t *)(dst + 0xb8) = *(word_t *)(src + 0xb8);
    *(word_t *)(dst + 0xb0) = a;
    a = *(word_t *)(src + 0xc0);
    b = *(word_t *)(src + 0xc8);
    c = *(word_t *)(src + 0xd0);
    d = *(word_t *)(src + 0xd8);
    e = *(word_t *)(src + 0xe0);
    f = *(word_t *)(src + 0xe8);
    g = *(word_t *)(src + 0xf0);
    h = *(word_t *)(src + 0xf8);
    (void)sk_copy_wordpair_64064(0);
    (void)sk_noop_463058();
    (void)sk_h_4627d0();
    (void)sk_h_45a4b4();
    (void)sk_rt_463454(0);
    *(word_t *)(dst + 0xc0) = a;
    *(word_t *)(dst + 0xc8) = b;
    *(word_t *)(dst + 0xd0) = c;
    *(word_t *)(dst + 0xd8) = d;
    *(word_t *)(dst + 0xe0) = e;
    *(word_t *)(dst + 0xe8) = f;
    *(word_t *)(dst + 0xf0) = g;
    *(word_t *)(dst + 0xf8) = h;
    a = *(word_t *)(src + 0x160);
    *(word_t *)(dst + 0x168) = *(word_t *)(src + 0x168);
    *(word_t *)(dst + 0x160) = a;
    old = *(word_t *)(dst + 0x170);
    *(word_t *)(dst + 0x170) = *(word_t *)(src + 0x170);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
    (void)sk_h_464ae8();
}

/* FUN_0045dd54 @ 0x0045dd54  (est. sk_md_copy_row_release_dd54)
 * Ghidra: void FUN_0045dd54(void)
 * Copies a descriptor row from unaff_x20 into unaff_x19, releasing the old
 * +0x2e token. Includes the +0x14..+0x2a field block and +0x2c..+0x2e tail.
 * Confidence: medium
 * Notes: FUN_00350c5c, 00462e54, 0034f8e4, 00459138, 00463454, 0036b118. */
static void sk_md_45dd54(word_t dst, word_t src)
{
    word_t a, b, c;

    (void)sk_syscall_save_ret();
    (void)sk_h_462e54(0);
    a = *(word_t *)(src + 0x00);
    b = *(word_t *)(src + 0x18);
    c = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x08) = *(word_t *)(src + 0x08);
    *(word_t *)(dst + 0x00) = a;
    *(word_t *)(dst + 0x18) = b;
    *(word_t *)(dst + 0x10) = c;
    a = *(word_t *)(src + 0x20);
    b = *(word_t *)(src + 0x38);
    c = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = a;
    *(word_t *)(dst + 0x38) = b;
    *(word_t *)(dst + 0x30) = c;
    a = *(word_t *)(src + 0x40);
    b = *(word_t *)(src + 0x58);
    c = *(word_t *)(src + 0x50);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x40) = a;
    *(word_t *)(dst + 0x58) = b;
    *(word_t *)(dst + 0x50) = c;
    a = *(word_t *)(src + 0x60);
    b = *(word_t *)(src + 0x78);
    c = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x68) = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x60) = a;
    *(word_t *)(dst + 0x78) = b;
    *(word_t *)(dst + 0x70) = c;
    a = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x88) = *(word_t *)(src + 0x88);
    *(word_t *)(dst + 0x80) = a;
    *(word_t *)(dst + 0x90) = 0;
    (void)swift_runtime_noop(0, 0, 0, 0, 0);
    (void)sk_h_459138();
    a = *(word_t *)(src + 0xa0);
    b = *(word_t *)(src + 0xb8);
    c = *(word_t *)(src + 0xb0);
    *(word_t *)(dst + 0xa8) = *(word_t *)(src + 0xa8);
    *(word_t *)(dst + 0xa0) = a;
    *(word_t *)(dst + 0xb8) = b;
    *(word_t *)(dst + 0xb0) = c;
    (void)sk_rt_463454(src + 0x2a);
    a = *(word_t *)(src + 0xc0);
    b = *(word_t *)(src + 0xd8);
    c = *(word_t *)(src + 0xd0);
    *(word_t *)(dst + 0xc8) = *(word_t *)(src + 0xc8);
    *(word_t *)(dst + 0xc0) = a;
    *(word_t *)(dst + 0xd8) = b;
    *(word_t *)(dst + 0xd0) = c;
    a = *(word_t *)(src + 0xe0);
    b = *(word_t *)(src + 0xf8);
    c = *(word_t *)(src + 0xf0);
    *(word_t *)(dst + 0xe8) = *(word_t *)(src + 0xe8);
    *(word_t *)(dst + 0xe0) = a;
    *(word_t *)(dst + 0xf8) = b;
    *(word_t *)(dst + 0xf0) = c;
    a = *(word_t *)(src + 0x100);
    b = *(word_t *)(src + 0x118);
    c = *(word_t *)(src + 0x110);
    *(word_t *)(dst + 0x108) = *(word_t *)(src + 0x108);
    *(word_t *)(dst + 0x100) = a;
    *(word_t *)(dst + 0x118) = b;
    *(word_t *)(dst + 0x110) = c;
    a = *(word_t *)(src + 0x120);
    b = *(word_t *)(src + 0x138);
    c = *(word_t *)(src + 0x130);
    *(word_t *)(dst + 0x128) = *(word_t *)(src + 0x128);
    *(word_t *)(dst + 0x120) = a;
    *(word_t *)(dst + 0x138) = b;
    *(word_t *)(dst + 0x130) = c;
    a = *(word_t *)(src + 0x140);
    *(word_t *)(dst + 0x148) = *(word_t *)(src + 0x148);
    *(word_t *)(dst + 0x140) = a;
    *(word_t *)(dst + 0x150) = 0;
    (void)swift_runtime_noop(0, 0, 0, 0, 0);
    (void)sk_h_459138();
    a = *(word_t *)(src + 0x160);
    *(word_t *)(dst + 0x168) = *(word_t *)(src + 0x168);
    *(word_t *)(dst + 0x160) = a;
    a = *(word_t *)(dst + 0x170);
    *(word_t *)(dst + 0x170) = *(word_t *)(src + 0x170);
    cL4_ref_release(a);
}

/* FUN_0045df3c @ 0x0045df3c  (est. sk_md_destroy_row_release_df3c)
 * Ghidra: void FUN_0045df3c(void)
 * Destroys a row at unaff_x19: restores registers, runs the 464f40 + 458db4
 * steps with the +0x40..+0x38 words, then releases the +0x68 refcounted field.
 * Confidence: medium
 * Notes: FUN_00352b20=exc_restore_regs, FUN_00464f40, FUN_00458db4. */
static void sk_md_45df3c(word_t self)
{
    word_t r;

    (void)exc_restore_regs();
    (void)sk_h_464f40(*(word_t *)(self + 0x40), *(word_t *)(self + 0x08),
                      *(word_t *)(self + 0x10), *(word_t *)(self + 0x18),
                      *(word_t *)(self + 0x20), *(word_t *)(self + 0x28),
                      *(word_t *)(self + 0x30), *(word_t *)(self + 0x38));
    (void)sk_h_458db4();
    cL4_ref_release(*(word_t *)(self + 0x68) & 0xfffffffffffffffUL);
}

/* FUN_0045df90 @ 0x0045df90  (est. sk_md_copy_field_block_retain_df90)
 * Ghidra: void FUN_0045df90(void)
 * Rebuilds a descriptor row at unaff_x20: copies +0x20..+0x50 from the source
 * row, then +0x58..+0x78 with retain of the +0x68 refcounted field.
 * Confidence: medium
 * Notes: FUN_0035193c, 003504d0, 00462c98, 00464f40, 004627d0, 0045c1e0,
 *   004640d0, 0036b270, 00351774. */
static void sk_md_45df90(word_t dst, word_t src)
{
    word_t a, b, c, d, e, f, g, h;

    (void)sk_h_35193c();
    (void)sk_reg_4d0();
    (void)sk_h_462c98();
    (void)sk_h_464f40(0, 0, 0, 0, 0, 0, 0, 0);
    (void)sk_h_4627d0();
    sk_md_45c1e0(0, 0, 0, 0, 0);
    (void)sk_store_regs_640d0();
    a = *(word_t *)(dst + 0x58);
    *(word_t *)(dst + 0x60) = *(word_t *)(src + 0x60);
    *(word_t *)(dst + 0x58) = a;
    a = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x68) = a;
    b = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
    *(word_t *)(dst + 0x70) = b;
    (void)cL4_ref_retain(a & 0xfffffffffffffffUL);
    (void)sk_syscall_setup_scratch();
}

/* FUN_0045e01c @ 0x0045e01c  (est. sk_md_rebuild_field_block_retain_e01c)
 * Ghidra: void FUN_0045e01c(void)
 * Rebuilds a descriptor row at unaff_x19: copies +0x40..+0x50, then +0x68 with
 * retain of the new value and release of the old, then +0x70..+0x78.
 * Confidence: medium
 * Notes: FUN_0035193c, 00350c5c, 00462c98, 00464f40, 004627d0, 0045c1e0,
 *   00463080, 00462fec, 00458db4, 004656e0, 0036b270, 0036b118, 00351774. */
static void sk_md_45e01c(word_t dst, word_t src)
{
    word_t n, old;

    (void)sk_h_35193c();
    (void)sk_syscall_save_ret();
    (void)sk_h_462c98();
    (void)sk_h_464f40(0, 0, 0, 0, 0, 0, 0, 0);
    (void)sk_h_4627d0();
    sk_md_45c1e0(0, 0, 0, 0, 0);
    (void)sk_rt_463080();
    (void)sk_h_462fec(*(word_t *)(dst + 0x40), 0, 0, 0);
    (void)sk_h_464f40(0, 0, 0, 0, 0, 0, 0, 0);
    (void)sk_h_458db4();
    (void)sk_h_4656e0();
    old = *(word_t *)(dst + 0x68);
    n = 0;
    *(word_t *)(dst + 0x68) = n;
    (void)cL4_ref_retain(n & 0xfffffffffffffffUL);
    cL4_ref_release(old & 0xfffffffffffffffUL);
    *(word_t *)(dst + 0x70) = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
    (void)sk_syscall_setup_scratch();
}

/* FUN_0045e0c8 @ 0x0045e0c8  (est. sk_md_copy_block_release_e0c8)
 * Ghidra: void FUN_0045e0c8(void)
 * Copies a descriptor row from unaff_x19 into unaff_x20, releasing the old
 * +0x68 refcounted field and copying +0x58..+0x78.
 * Confidence: medium
 * Notes: FUN_003504d0, 00465f34, 00466374, 00458db4, 0036b118. */
static void sk_md_45e0c8(word_t dst, word_t src)
{
    word_t a, b, c;

    (void)sk_reg_4d0();
    (void)sk_script_desc_5f34(*(byte *)(src + 0x50));
    a = *(word_t *)(src + 0x00);
    b = *(word_t *)(src + 0x18);
    c = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x08) = *(word_t *)(src + 0x08);
    *(word_t *)(dst + 0x00) = a;
    *(word_t *)(dst + 0x18) = b;
    *(word_t *)(dst + 0x10) = c;
    (void)sk_copy_fields_66374();
    (void)sk_h_458db4();
    a = *(word_t *)(src + 0x58);
    *(word_t *)(dst + 0x60) = *(word_t *)(src + 0x60);
    *(word_t *)(dst + 0x58) = a;
    cL4_ref_release(*(word_t *)(dst + 0x68) & 0xfffffffffffffffUL);
    a = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x70) = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x68) = a;
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
}

/* FUN_0045e1e4 @ 0x0045e1e4  (est. sk_md_destroy_passthrough_e1e4)
 * Ghidra: void FUN_0045e1e4(undefined8 *param_1)
 * Builds a descriptor via sk_nop_644cc then chains sk_h_458db4.
 * Confidence: medium */
static void sk_md_45e1e4(word_t *p)
{
    (void)sk_nop_644cc(p[0], (word_t)p, p[1]);
    (void)sk_h_458db4();
}

/* FUN_0045e220 @ 0x0045e220  (est. sk_md_rebuild_field_block_e220)
 * Ghidra: void FUN_0045e220(void)
 * Rebuilds a descriptor row copying +0x40..+0x50 via the 463810 step.
 * Confidence: medium
 * Notes: FUN_0035193c, 004630d8, 00462b6c, 00464864, 0045c1e0, 00463810,
 *   00351774. */
static void sk_md_45e220(word_t dst, word_t src)
{
    (void)sk_h_35193c();
    (void)sk_h_4630d8();
    (void)sk_h_462b6c();
    (void)sk_nop_64864();
    sk_md_45c1e0(0, 0, 0, 0, 0);
    (void)sk_h_463810(0, 0, 0, 0);
    (void)sk_syscall_setup_scratch();
}

/* FUN_0045e30c @ 0x0045e30c  (est. sk_md_swap_block_retain_e30c)
 * Ghidra: undefined8 * FUN_0045e30c(undefined8 *param_1, undefined8 *param_2)
 * Swaps the first 4 words between param_1 and param_2, copies the +0x20..+0x38
 * block via sk_copy6words, then chains sk_h_458db4. Returns param_1.
 * Confidence: medium
 * Notes: FUN_00465eec=copy6words. */
static word_t *sk_md_45e30c(word_t *a, word_t *b)
{
    word_t t0, t1, t2, t3;

    t0 = a[0]; t1 = a[1]; t2 = a[2]; t3 = a[3];
    a[0] = b[0]; a[1] = b[1]; a[2] = b[2]; a[3] = b[3];
    (void)sk_copy6words_5eec(t1, t0, (word_t)b, t2, t3, a[4], a[5], a[6], a[7]);
    (void)sk_h_458db4();
    return a;
}

/* FUN_0045e45c @ 0x0045e45c  (est. sk_md_destroy_release_e45c)
 * Ghidra: void FUN_0045e45c(void)
 * Destroys a row at unaff_x19: runs sk_release_666c0 then releases the +0x38
 * token.
 * Confidence: medium
 * Notes: FUN_004666c0=sk_release_666c0, 003a25d4=token release. */
static void sk_md_45e45c(word_t self)
{
    (void)sk_release_666c0();
    cL4_token_release(*(word_t *)(self + 0x38));
}

/* FUN_0045e484 @ 0x0045e484  (est. sk_md_copy_words_retain2_e484)
 * Ghidra: void FUN_0045e484(void)
 * Copies +0x40..+0x48 from the frame-copy16 source, then retains twice.
 * Confidence: medium
 * Notes: FUN_00355938=frame_copy16, thunk_FUN_0036b270=retain. */
static void sk_md_45e484(word_t dst, word_t src)
{
    word_t a;

    (void)cL4_frame_copy16();
    (void)sk_copy5words_5f20();
    a = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x40) = a;
    (void)cL4_ref_retain(0);
    (void)cL4_ref_retain(0);
}

/* FUN_0045e4c0 @ 0x0045e4c0  (est. sk_md_copy_field_retain_e4c0)
 * Ghidra: void FUN_0045e4c0(void)
 * Rebuilds a descriptor row: copies +0x38 field with retain of new / release
 * of old token.
 * Confidence: medium
 * Notes: FUN_0034b264, 00464354, 003a25d4, 00464dcc, 00463750, 004632b8,
 *   0036b270, 00465d28. */
static void sk_md_45e4c0(word_t dst, word_t src)
{
    word_t old;

    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    (void)sk_h_464dcc();
    (void)sk_h_463750();
    (void)sk_h_4632b8();
    old = *(word_t *)(dst + 0x38);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    (void)cL4_ref_retain(0);
    cL4_token_release(old);
    (void)sk_copy2words_5d28();
}

/* FUN_0045e520 @ 0x0045e520  (est. sk_md_copy_words_e520)
 * Ghidra: void FUN_0045e520(void)
 * Copies +0x40..+0x48 from unaff_x19 into unaff_x20.
 * Confidence: medium
 * Notes: FUN_0046337c, 00465a50. */
static void sk_md_45e520(word_t dst, word_t src)
{
    word_t a;

    (void)sk_h_46337c();
    (void)sk_copy5words_5a50();
    a = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x40) = a;
}

/* FUN_0045e7d0 @ 0x0045e7d0  (est. sk_md_release_pair_e7d0)
 * Ghidra: void FUN_0045e7d0(long param_1)
 * Releases the two refcounted fields at +0x18 and +0x38 of the row.
 * Confidence: high (trivial, unambiguous) */
static void sk_md_45e7d0(word_t self)
{
    cL4_ref_release(*(word_t *)(self + 0x18));
    cL4_ref_release(*(word_t *)(self + 0x38));
}

/* FUN_0045e800 @ 0x0045e800  (est. sk_md_copy_fields_retain2_e800)
 * Ghidra: void FUN_0045e800(void)
 * Copies +0x10..+0x38 from the copy16 source into the destination, retaining
 * the +0x38 refcounted field.
 * Confidence: medium
 * Notes: FUN_00350e04=copy16, 0036b270=retain. */
static void sk_md_45e800(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a;

    pr = cL4_copy16();
    *(byte *)(pr.lo + 0x10) = *(byte *)(pr.hi + 0x10);
    *(word_t *)(dst + 0x18) = *(word_t *)(pr.hi + 0x18);
    a = *(word_t *)(pr.hi + 0x20);
    *(word_t *)(dst + 0x28) = *(word_t *)(pr.hi + 0x28);
    *(word_t *)(dst + 0x20) = a;
    *(byte *)(dst + 0x30) = *(byte *)(pr.hi + 0x30);
    a = *(word_t *)(pr.hi + 0x38);
    *(word_t *)(dst + 0x38) = a;
    (void)cL4_ref_retain(0);
    (void)cL4_ref_retain(a);
}

/* FUN_0045e858 @ 0x0045e858  (est. sk_md_copy_pair_retain_e858)
 * Ghidra: void FUN_0045e858(void)
 * Copies a 3-word + byte block from the reg_4d0 source into its destination,
 * swapping the +0x18 and +0x38 refcounted fields with retain/release.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, 00465ee0=copy1byte, 0036b270/0036b118. */
static void sk_md_45e858(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a, b, old;

    pr = sk_reg_4d0();
    a = *(word_t *)(pr.hi + 8);
    b = *(word_t *)(pr.hi + 0);
    *(byte *)(pr.lo + 0x10) = *(byte *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 8) = a;
    *(word_t *)(pr.lo + 0) = b;
    old = *(word_t *)(dst + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(pr.hi + 0x18);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
    (void)sk_copy1byte_5ee0(*(word_t *)(src + 0x20));
    old = *(word_t *)(dst + 0x38);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
}

/* FUN_0045e8d0 @ 0x0045e8d0  (est. sk_md_copy_block_release_e8d0)
 * Ghidra: void FUN_0045e8d0(void)
 * Copies a descriptor row from the 46306c source into unaff_x20, releasing the
 * old +0x18 and +0x38 refcounted fields.
 * Confidence: medium
 * Notes: FUN_0046306c, 00465ee0=copy1byte, 0036b118=release. */
static void sk_md_45e8d0(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a, old;

    pr = sk_h_46306c();
    *(byte *)(pr.lo + 0x10) = *(byte *)(pr.hi + 0x10);
    old = *(word_t *)(pr.lo + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(pr.hi + 0x18);
    cL4_ref_release(old);
    a = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x20) = a;
    (void)sk_copy1byte_5ee0(0);
    old = *(word_t *)(dst + 0x38);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    cL4_ref_release(old);
}

/* FUN_0045e9e0 / FUN_0045ea94 / FUN_0045ecf4 / FUN_0045ed90
 * @ 0x0045e9e0/0x0045ea94/0x0045ecf4/0x0045ed90  (est. sk_md_cmp_flag_emit)
 * Ghidra: void FUN_0045e9e0(void) (and three identical clones)
 * Runs the 664b8 no-op, then emits the ~extraout_w8 (inverted compare flag) to
 * sk_h_6b438 when the carry-flag comparison was "greater" (CY && !ZR).
 * Confidence: medium
 * Notes: four byte-identical functions (indirect thunk targets); FUN_004664b8,
 *   FUN_0006b438. */
static void sk_md_45e9e0(void)
{
    (void)sk_nop_664b8();
    (void)sk_h_6b438(0);
}
static void sk_md_45ea94(void) { sk_md_45e9e0(); }
static void sk_md_45ecf4(void) { sk_md_45e9e0(); }
static void sk_md_45ed90(void) { sk_md_45e9e0(); }

/* FUN_0045eb38 @ 0x0045eb38  (est. sk_md_release_pair_eb38)
 * Ghidra: void FUN_0045eb38(long param_1)
 * Releases the +0x68 refcounted field (tagged) and the +0x80 field.
 * Confidence: high */
static void sk_md_45eb38(word_t self)
{
    cL4_ref_release(*(word_t *)(self + 0x68) & 0xfffffffffffffffUL);
    cL4_ref_release(*(word_t *)(self + 0x80));
}

/* FUN_0045eb6c @ 0x0045eb6c  (est. sk_md_copy_block_retain_eb6c)
 * Ghidra: void FUN_0045eb6c(void)
 * Copies +0x50..+0x80 from unaff_x19 into unaff_x20, retaining the +0x68
 * (tagged) and +0x80 fields.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, FUN_00117cc4=sk_mem_117cc4, 0036b270=retain. */
static void sk_md_45eb6c(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a, b;

    pr = sk_reg_4d0();
    sk_mem_117cc4(pr.lo, pr.hi, 0x50);
    a = *(word_t *)(src + 0x50);
    *(word_t *)(dst + 0x58) = *(word_t *)(src + 0x58);
    *(word_t *)(dst + 0x50) = a;
    a = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x60) = *(word_t *)(src + 0x60);
    *(word_t *)(dst + 0x68) = a;
    b = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
    *(word_t *)(dst + 0x70) = b;
    b = *(word_t *)(src + 0x80);
    *(word_t *)(dst + 0x80) = b;
    (void)cL4_ref_retain(a & 0xfffffffffffffffUL);
    (void)cL4_ref_retain(b);
}

/* FUN_0045ebc8 @ 0x0045ebc8  (est. sk_md_copy_block_retain_ebc8)
 * Ghidra: void FUN_0045ebc8(void)
 * Copies a 14-word block from the reg_4d0 source into its destination,
 * retaining the new +0x68 (tagged) field and releasing the old, then copies
 * +0x80 with retain/release.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, FUN_00465f68=copy2words, 0036b270/0036b118. */
static void sk_md_45ebc8(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t *s, *d;
    word_t n, old;

    pr = sk_reg_4d0();
    s = (word_t *)pr.hi;
    d = (word_t *)pr.lo;
    d[1] = s[1]; d[0] = s[0]; d[3] = s[3]; d[2] = s[2];
    d[5] = s[5]; d[4] = s[4]; d[7] = s[7]; d[6] = s[6];
    d[8] = s[8]; d[9] = s[9];
    *(byte *)(d + 0x0a) = *(byte *)(s + 0x0a);
    d[0xb] = s[0xb]; d[0xc] = s[0xc];
    n = s[0xd];
    old = d[0xd];
    d[0xd] = n;
    (void)cL4_ref_retain(n & 0xfffffffffffffffUL);
    cL4_ref_release(old & 0xfffffffffffffffUL);
    (void)sk_copy2words_5f68();
    old = *(word_t *)(dst + 0x80);
    *(word_t *)(dst + 0x80) = *(word_t *)(src + 0x80);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
}

/* FUN_0045ec64 @ 0x0045ec64  (est. sk_md_copy_block_release_ec64)
 * Ghidra: void FUN_0045ec64(void)
 * Copies a 13-word block from the reg_4d0 source, releasing the old +0x68
 * (tagged) field, then copies +0x68..+0x80 from unaff_x19 with release of the
 * old +0x80 field.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, 0036b118=release. */
static void sk_md_45ec64(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t *s, *d;
    word_t a, old;

    pr = sk_reg_4d0();
    s = (word_t *)pr.hi;
    d = (word_t *)pr.lo;
    d[1] = s[1]; d[0] = s[0]; d[3] = s[3]; d[2] = s[2];
    d[5] = s[5]; d[4] = s[4]; d[7] = s[7]; d[6] = s[6];
    d[8] = s[8]; d[9] = s[9];
    *(byte *)(d + 0x0a) = *(byte *)(s + 0x0a);
    d[0xb] = s[0xb]; d[0xc] = s[0xc];
    cL4_ref_release(d[0xd] & 0xfffffffffffffffUL);
    a = *(word_t *)(src + 0x68);
    *(word_t *)(dst + 0x70) = *(word_t *)(src + 0x70);
    *(word_t *)(dst + 0x68) = a;
    a = *(word_t *)(src + 0x80);
    old = *(word_t *)(dst + 0x80);
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
    *(word_t *)(dst + 0x80) = a;
    cL4_ref_release(old);
}

/* FUN_0045ee90 @ 0x0045ee90  (est. sk_md_copy_fields_retain_ee90)
 * Ghidra: void FUN_0045ee90(void)
 * Copies +8..+0x30 from the word_copy_b source into its destination, retaining
 * the +8 field.
 * Confidence: medium
 * Notes: FUN_0034f2f4=word_copy_b, thunk_FUN_0036b270=retain. */
static void sk_md_45ee90(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a;

    pr = cL4_word_copy_b();
    a = *(word_t *)(pr.hi + 8);
    *(word_t *)(pr.lo + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(word_t *)(pr.lo + 8) = a;
    *(word_t *)(pr.lo + 0x18) = *(word_t *)(pr.hi + 0x18);
    a = *(word_t *)(pr.hi + 0x20);
    *(word_t *)(pr.lo + 0x28) = *(word_t *)(pr.hi + 0x28);
    *(word_t *)(pr.lo + 0x20) = a;
    *(byte *)(pr.lo + 0x30) = *(byte *)(pr.hi + 0x30);
    (void)cL4_ref_retain(*(word_t *)(pr.hi + 8));
}

/* FUN_0045eedc @ 0x0045eedc  (est. sk_md_destroy_cascade_eedc)
 * Ghidra: void FUN_0045eedc(void)
 * Chains word_copy, copy_and_acquire, token_release, exc_copy_reg_pair,
 * cmp_463344, copy1byte.
 * Confidence: medium */
static void sk_md_45eedc(void)
{
    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    (void)exc_copy_reg_pair();
    (void)sk_cmp_463344();
    (void)sk_copy1byte_5ee0(0);
}

/* FUN_0045ef20 @ 0x0045ef20  (est. sk_md_copy_words_release_ef20)
 * Ghidra: void FUN_0045ef20(void)
 * Copies +8..+0x28 from unaff_x19 into unaff_x20, releasing the +8 token of
 * the word_copy source.
 * Confidence: medium
 * Notes: FUN_0034b264=word_copy, 003a25d4=token release, 00465ee0=copy1byte. */
static void sk_md_45ef20(word_t dst, word_t src)
{
    word_t a;

    a = cL4_word_copy();
    cL4_token_release(*(word_t *)(a + 8));
    a = *(word_t *)(src + 8);
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 8) = a;
    a = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x18) = a;
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    (void)sk_copy1byte_5ee0(0);
}

/* FUN_0045f0a0 @ 0x0045f0a0  (est. sk_md_copy_words_retain_f0a0)
 * Ghidra: void FUN_0045f0a0(void)
 * Copies +0x10..+0x18 from the copy16 source into unaff_x19, then retains.
 * Confidence: medium
 * Notes: FUN_00350e04=copy16, thunk_FUN_0036b270=retain. */
static void sk_md_45f0a0(word_t dst, word_t src)
{
    cL4_w16_t pr;

    pr = cL4_copy16();
    *(word_t *)(dst + 0x10) = *(word_t *)(pr.hi + 0x10);
    *(byte *)(dst + 0x18) = *(byte *)(pr.hi + 0x18);
    (void)cL4_ref_retain(0);
}

/* FUN_0045f0d8 @ 0x0045f0d8  (est. sk_md_copy_retain_f0d8)
 * Ghidra: void FUN_0045f0d8(void)
 * Chains word_copy, 463a10, retain, token_release, 463a48.
 * Confidence: medium */
static void sk_md_45f0d8(void)
{
    (void)cL4_word_copy();
    (void)sk_h_463a10();
    (void)cL4_ref_retain(0);
    (void)cL4_token_release(0);
    (void)sk_h_463a48();
}

/* FUN_0045f114 @ 0x0045f114  (est. sk_md_copy_release_f114)
 * Ghidra: void FUN_0045f114(void)
 * Copies +0x10 from the 46306c source into unaff_x20, releasing the old +0x10
 * token, then chains 463a48.
 * Confidence: medium
 * Notes: FUN_0046306c, 003a25d4, 00463a48. */
static void sk_md_45f114(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t old;

    pr = sk_h_46306c();
    old = *(word_t *)(pr.lo + 0x10);
    *(word_t *)(dst + 0x10) = *(word_t *)(pr.hi + 0x10);
    cL4_token_release(old);
    (void)sk_h_463a48();
}

/* FUN_0045f1d8 @ 0x0045f1d8  (est. sk_md_copy_words_f1d8)
 * Ghidra: void FUN_0045f1d8(void)
 * Copies +0x10..+0x18 from unaff_x19 into unaff_x20.
 * Confidence: medium
 * Notes: FUN_0034b264, 00464354, 003a25d4. */
static void sk_md_45f1d8(word_t dst, word_t src)
{
    word_t a;

    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    a = *(word_t *)(src + 0x10);
    *(byte *)(dst + 0x18) = *(byte *)(src + 0x18);
    *(word_t *)(dst + 0x10) = a;
}

/* FUN_0045f4fc @ 0x0045f4fc  (est. sk_md_destroy_passthrough_f4fc)
 * Ghidra: undefined8 FUN_0045f4fc(undefined8 param_1)
 * Runs sk_h_4607ac and returns param_1 unchanged.
 * Confidence: high */
static word_t sk_md_45f4fc(word_t p)
{
    (void)sk_md_4607ac(0, 0);
    return p;
}

/* FUN_0045f550 @ 0x0045f550  (est. sk_md_copy2_retain_f550)
 * Ghidra: undefined8 * FUN_0045f550(undefined8 *param_1, undefined8 *param_2)
 * Copies the 2 words of param_2 into param_1 and retains. Returns param_1.
 * Confidence: medium
 * Notes: FUN_0036b270=retain. */
static word_t *sk_md_45f550(word_t *dst, word_t *src)
{
    dst[0] = src[0];
    *(byte *)(dst + 1) = *(byte *)(src + 1);
    (void)cL4_ref_retain(0);
    return dst;
}

/* FUN_0045f588 @ 0x0045f588  (est. sk_md_copy_byte_release_f588)
 * Ghidra: void FUN_0045f588(void)
 * Copies the +8 byte from unaff_x19 into unaff_x20 after the 504d0/465b1c
 * release sequence.
 * Confidence: medium
 * Notes: FUN_003504d0=reg_4d0, 00465b1c=store_load_ref, 0036b118=release. */
static void sk_md_45f588(word_t dst, word_t src)
{
    (void)sk_reg_4d0();
    (void)sk_store_load_ref_5b1c();
    (void)cL4_ref_release(0);
    *(byte *)(dst + 8) = *(byte *)(src + 8);
}

/* FUN_0045f60c @ 0x0045f60c  (est. sk_md_destroy_cascade_f60c)
 * Ghidra: void FUN_0045f60c(void)
 * Chains word_copy, copy_and_acquire, token_release, exc_copy_reg_pair.
 * Confidence: medium */
static void sk_md_45f60c(void)
{
    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    (void)exc_copy_reg_pair();
}

/* FUN_0045f648 @ 0x0045f648  (est. sk_md_copy_words_f648)
 * Ghidra: void FUN_0045f648(void)
 * Copies +0x10..+0x18 from unaff_x19 into unaff_x20.
 * Confidence: medium
 * Notes: FUN_0046337c. */
static void sk_md_45f648(word_t dst, word_t src)
{
    word_t a;

    (void)sk_h_46337c();
    a = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x10) = a;
}

/* FUN_0045f6c4 @ 0x0045f6c4  (est. sk_md_desc_deref_check_f6c4)
 * Ghidra: undefined1[16] FUN_0045f6c4(long param_1, ...)
 * Dereferences a metadata descriptor (sk_desc_deref_release with kind 0x13f),
 * and if the result capacity (< 0x40) triggers a realloc of the +0x40-size
 * slot and rebuilds the message descriptor at param_1+0x20; otherwise returns
 * the (0x3f-capped) descriptor pointer pair.
 * Confidence: medium
 * Notes: FUN_00377dcc=sk_desc_deref_release, FUN_00465c98=sk_nop_5c98,
 *   FUN_003728b8=sk_msg_desc_build_meta. Returns {lo=ptr, hi=cap}. */
static cL4_w16_t sk_md_45f6c4(word_t self, word_t p2, word_t p3, word_t p4)
{
    cL4_w16_t pr;
    word_t cap, ptr;

    pr = sk_desc_deref_release(0x13f, *(word_t *)(self + 0x10));
    ptr = pr.lo;
    if (pr.hi < 0x40) {
        (void)sk_nop_5c98(*(word_t *)(ptr - 8) + 0x40);
        sk_msg_desc_build_meta(self, 0, 2, p4, self + 0x20);
        ptr = 0;
        cap = 0;
    } else {
        cap = 0x3f;
    }
    return (cL4_w16_t){ ptr, cap };
}

/* FUN_0045f758 @ 0x0045f758  (est. sk_md_desc_deref_check_f758)
 * Ghidra: undefined1[16] FUN_0045f758(long param_1, ...)
 * Identical to sk_md_45f6c4 but rebuilds the descriptor at param_1+0x18.
 * Confidence: medium */
static cL4_w16_t sk_md_45f758(word_t self, word_t p2, word_t p3, word_t p4)
{
    cL4_w16_t pr;
    word_t cap, ptr;

    pr = sk_desc_deref_release(0x13f, *(word_t *)(self + 0x10));
    ptr = pr.lo;
    if (pr.hi < 0x40) {
        (void)sk_nop_5c98(*(word_t *)(ptr - 8) + 0x40);
        sk_msg_desc_build_meta(self, 0, 2, p4, self + 0x18);
        ptr = 0;
        cap = 0;
    } else {
        cap = 0x3f;
    }
    return (cL4_w16_t){ ptr, cap };
}

/* FUN_0045f7d0 @ 0x0045f7d0  (est. sk_md_inline_copy_or_retain_f7d0)
 * Ghidra: long * FUN_0045f7d0(param_1, param_2, long param_3)
 * Performs an inlined small-struct copy between unaff_x19 and unaff_x20 when
 * the descriptor at param_3+0x10 passes the size/flag check (layout flags at
 * +0x50 low bits clear, total size < 0x19); otherwise copies the first word and
 * falls back to a ref-retain path.
 * Confidence: medium
 * Notes: FUN_00350c5c=syscall_save_ret, FUN_0009461c=noop. Returns the advanced
 *   x19 pointer. */
static word_t *sk_md_45f7d0(word_t *x19, word_t *x20, word_t p3)
{
    long d = *(long *)(*(long *)(p3 + 0x10) - 8);
    long sz = *(long *)(d + 0x40);
    unsigned fl = *(unsigned *)(d + 0x50);

    (void)sk_syscall_save_ret();
    if ((fl & 0x1000f8) == 0 && (sz + 7UL & ~7UL) + 0x10 < 0x19) {
        word_t *pd = (word_t *)((word_t)x19 + sz + 7 & ~7UL);
        word_t *ps = (word_t *)((word_t)x20 + sz + 7 & ~7UL);
        (void)sk_noop_9461c();
        pd[0] = ps[0];
        pd[1] = ps[1];
    } else {
        fl &= 0xf8;
        x19[0] = x20[0];
        x19 = (word_t *)(x19[0] + ((word_t)(fl + 0x17 & (fl ^ 0xffffffffUL)) & 0x1f8));
        (void)cL4_ref_retain(0);
    }
    return x19;
}

/* FUN_0045f8ac @ 0x0045f8ac  (est. sk_md_dispatch_copy_f8ac)
 * Ghidra: void FUN_0045f8ac(void)
 * Runs the no-op, calls the indirect function at extraout_x16+0x10, runs the
 * no-op_34 with the +0x40 word, then copies a 2-word result.
 * Confidence: medium
 * Notes: FUN_00349928=noop_67, FUN_00349104=noop_34. */
static void sk_md_45f8ac(word_t self)
{
    (*(void (**)(void))(self + 0x10))();
    (void)sk_noop_34(*(word_t *)(self + 0x40));
}

/* FUN_0045f900 @ 0x0045f900  (est. sk_md_dispatch_copy_f900)
 * Ghidra: void FUN_0045f900(void)
 * Same as sk_md_45f8ac but calls the +0x18 slot and chains 465950.
 * Confidence: medium */
static void sk_md_45f900(word_t self)
{
    (*(void (**)(void))(self + 0x18))();
    (void)sk_noop_34(*(word_t *)(self + 0x40));
    (void)sk_h_465950();
}

/* FUN_0045f94c @ 0x0045f94c  (est. sk_md_dispatch_copy_f94c)
 * Ghidra: void FUN_0045f94c(void)
 * Same as sk_md_45f8ac but calls the +0x20 slot.
 * Confidence: medium */
static void sk_md_45f94c(word_t self)
{
    (*(void (**)(void))(self + 0x20))();
    (void)sk_noop_34(*(word_t *)(self + 0x40));
}

/* FUN_0045f9a0 @ 0x0045f9a0  (est. sk_md_dispatch_copy_f9a0)
 * Ghidra: void FUN_0045f9a0(void)
 * Same as sk_md_45f900 but calls the +0x28 slot.
 * Confidence: medium */
static void sk_md_45f9a0(word_t self)
{
    (*(void (**)(void))(self + 0x28))();
    (void)sk_noop_34(*(word_t *)(self + 0x40));
    (void)sk_h_465950();
}

/* FUN_0045fc8c @ 0x0045fc8c  (est. sk_md_release_pair_fc8c)
 * Ghidra: void FUN_0045fc8c(long param_1)
 * Releases the +0x30 token and the +0x50 refcounted field of the row.
 * Confidence: high */
static void sk_md_45fc8c(word_t self)
{
    cL4_token_release(*(word_t *)(self + 0x30));
    cL4_ref_release(*(word_t *)(self + 0x50));
}

/* FUN_0045fcbc @ 0x0045fcbc  (est. sk_md_copy_fields_retain_fcbc)
 * Ghidra: void FUN_0045fcbc(void)
 * Copies +0x30..+0x50 from the word_copy_b source into unaff_x19, retaining
 * the +0x50 field.
 * Confidence: medium
 * Notes: FUN_0034f2f4=word_copy_b, 00464a50, thunk_FUN_0036b270=retain. */
static void sk_md_45fcbc(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t a;

    pr = cL4_word_copy_b();
    (void)sk_h_464a50();
    *(word_t *)(dst + 0x30) = *(word_t *)(pr.hi + 0x30);
    *(byte *)(dst + 0x38) = *(byte *)(pr.hi + 0x38);
    *(word_t *)(dst + 0x40) = *(word_t *)(pr.hi + 0x40);
    *(byte *)(dst + 0x48) = *(byte *)(pr.hi + 0x48);
    a = *(word_t *)(pr.hi + 0x50);
    *(word_t *)(dst + 0x50) = a;
    (void)cL4_ref_retain(0);
    (void)cL4_ref_retain(a);
}

/* FUN_0045fd18 @ 0x0045fd18  (est. sk_md_copy_block_retain_fd18)
 * Ghidra: void FUN_0045fd18(void)
 * Copies a descriptor row from the 0034d454 source into its destination,
 * swapping the +0x30 token with retain/release, then copies +0x50 with
 * retain/release.
 * Confidence: medium
 * Notes: FUN_0034d454, 004641e8=copy_fields, thunk retain, 003a25d4 release,
 *   0036b270/0036b118. */
static void sk_md_45fd18(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t *s, *d;
    word_t old;

    pr = sk_f_0034d454();
    s = (word_t *)pr.hi;
    d = (word_t *)pr.lo;
    *(byte *)(d + 1) = *(byte *)(s + 1);
    d[2] = s[2];
    *(byte *)(d + 3) = *(byte *)(s + 3);
    d[4] = s[4];
    d[5] = s[5];
    old = *(word_t *)(dst + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(s + 0x30);
    (void)cL4_ref_retain(0);
    cL4_token_release(old);
    *(byte *)(dst + 0x38) = *(byte *)(src + 0x38);
    (void)sk_copy_fields_641e8();
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
}

/* FUN_0045fdac @ 0x0045fdac  (est. sk_md_copy_block_release_fdac)
 * Ghidra: void FUN_0045fdac(void)
 * Copies +0x30..+0x38 from the 464a50 source with token release, then +0x50
 * with release.
 * Confidence: medium
 * Notes: FUN_0034b264=word_copy, 00464a50, 003a25d4, 004641e8, 0036b118. */
static void sk_md_45fdac(word_t dst, word_t src)
{
    cL4_w16_t pr;
    word_t old;

    (void)cL4_word_copy();
    pr = sk_h_464a50();
    old = *(word_t *)(pr.lo + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(pr.hi + 0x30);
    cL4_token_release(old);
    *(byte *)(dst + 0x38) = *(byte *)(src + 0x38);
    (void)sk_copy_fields_641e8();
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    cL4_ref_release(old);
}

/* FUN_0045febc @ 0x0045febc  (est. sk_md_destroy_release_febc)
 * Ghidra: void FUN_0045febc(void)
 * Destroys a row at unaff_x19: runs sk_release_666c0 then releases the +0x18
 * token.
 * Confidence: medium */
static void sk_md_45febc(word_t self)
{
    (void)sk_release_666c0();
    cL4_token_release(*(word_t *)(self + 0x18));
}

/* FUN_0045fee8 @ 0x0045fee8  (est. sk_md_copy_fields_retain_fee8)
 * Ghidra: void FUN_0045fee8(void)
 * Copies +0x10..+0x20 from the frame_copy16 source into unaff_x19, retaining
 * the +0x18 and +0x20 fields.
 * Confidence: medium
 * Notes: FUN_00355938=frame_copy16, thunk_FUN_0036b270=retain. */
static void sk_md_45fee8(word_t dst, word_t src)
{
    word_t a;

    (void)cL4_frame_copy16();
    a = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = a;
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    (void)cL4_ref_retain(0);
    (void)cL4_ref_retain(a);
}

/* FUN_0045ff2c @ 0x0045ff2c  (est. sk_md_copy_field_retain_ff2c)
 * Ghidra: void FUN_0045ff2c(void)
 * Rebuilds a descriptor row: copies the +0x18 field with retain of the new
 * value and release of the old token.
 * Confidence: medium
 * Notes: FUN_0034b264, 00464354, 003a25d4, 00464dcc, 0036b270, 00464504. */
static void sk_md_45ff2c(word_t dst, word_t src)
{
    word_t old;

    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    (void)sk_h_464dcc();
    old = *(word_t *)(dst + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    (void)cL4_ref_retain(0);
    cL4_token_release(old);
    (void)sk_copy_word_64504();
}

/* FUN_0045ff88 @ 0x0045ff88  (est. sk_md_copy_words_release_ff88)
 * Ghidra: void FUN_0045ff88(void)
 * Copies +0x10..+0x18 from unaff_x19 into unaff_x20, releasing the old +0x18
 * token.
 * Confidence: medium
 * Notes: FUN_0046337c, 003a25d4, 00464504. */
static void sk_md_45ff88(word_t dst, word_t src)
{
    word_t a, old;

    (void)sk_h_46337c();
    a = *(word_t *)(src + 0x18);
    old = *(word_t *)(dst + 0x18);
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = a;
    cL4_token_release(old);
    (void)sk_copy_word_64504();
}

/* FUN_004607ac @ 0x004607ac  (est. sk_md_dispatch_tail_607ac)
 * Ghidra: void FUN_004607ac(param_1, param_2)
 * Calls sk_h_4607c4 with the FUN_00458f9c target as the jumptable handler.
 * Confidence: medium */
static void sk_md_4607ac(word_t p1, word_t p2)
{
    word_t blk[5] = { 0, 0, 0, 0, 0 };
    sk_md_4607c4(blk, p2, (void (*)(word_t, word_t, word_t, word_t, byte))sk_h_458f9c);
}

/* FUN_004607c4 @ 0x004607c4  (est. sk_md_dispatch_apply_607c4)
 * Ghidra: void FUN_004607c4(undefined8 *param_1, undefined8 param_2, code *jumptable)
 * Applies the indirect jumptable handler to the 5-word argument block at
 * param_1 (4 words + a byte at +4).
 * Confidence: medium
 * Notes: the decompiler could not recover the jumptable; treated as a direct
 *   call to the handler with the boxed args. */
static void sk_md_4607c4(word_t *p, word_t p2, void (*handler)(word_t, word_t, word_t, word_t, byte))
{
    handler(p[0], p[1], p[2], p[3], *(byte *)(p + 4));
}

/* FUN_004607e0 @ 0x004607e0  (est. sk_md_dispatch_pack_607e0)
 * Ghidra: void FUN_004607e0(void)
 * Runs the 463504 step with the FUN_00458f00 handler, reads the +0x20 byte,
 * calls the indirect +0x20 slot, then packs 5 words into unaff_x19.
 * Confidence: medium
 * Notes: FUN_00463504=sk_noop_463504, FUN_0034c444=noop_c444. */
static void sk_md_4607e0(word_t *dst, word_t w20, word_t w21, word_t w22, word_t w23)
{
    (void)sk_noop_463504((word_t)sk_h_458f00);
    (void)sk_noop_c444();
    dst[0] = w20;
    dst[1] = w21;
    dst[2] = w22;
    dst[3] = w23;
}

/* FUN_00460880 @ 0x00460880  (est. sk_md_dispatch_chain_60880)
 * Ghidra: void FUN_00460880(void)
 * Chains the nop-handler, 462848, indirect x8 call, 46303c, indirect x4 call,
 * and nop-handler.
 * Confidence: medium
 * Notes: FUN_00084220/00084234=cL4_nop_handler. */
static void sk_md_460880(word_t x3, void (*x4)(void))
{
    (void)cL4_nop_handler();
    (void)sk_h_462848(x3);
    (void)sk_h_46303c();
    x4();
    (void)cL4_nop_handler();
}

/* FUN_004608e8 @ 0x004608e8  (est. sk_md_swap5_dispatch_608e8)
 * Ghidra: undefined8 * FUN_004608e8(param_1, param_2, param_3, code *param_4)
 * Swaps the 5-word block between param_1 and param_2, then applies the param_4
 * handler to the swapped-out 5 words. Returns param_1.
 * Confidence: medium */
static word_t *sk_md_4608e8(word_t *a, word_t *b, word_t p3, void (*h)(word_t, word_t, word_t, word_t, byte))
{
    byte oldb = *(byte *)(b + 4);
    word_t t0 = a[0], t1 = a[1], t2 = a[2], t3 = a[3];
    byte tb = *(byte *)(a + 4);
    byte sb = *(byte *)(b + 4);
    a[0] = b[0]; a[1] = b[1]; a[2] = b[2]; a[3] = b[3];
    *(byte *)(a + 4) = sb;
    h(t0, t1, t2, t3, tb);
    return a;
}

/* FUN_00460ae4 @ 0x00460ae4  (est. sk_md_destroy_release_60ae4)
 * Ghidra: void FUN_00460ae4(void)
 * Destroys a row at unaff_x19: sk_release_666c0, release +0x30 token, release
 * +0x50 refcounted field.
 * Confidence: medium */
static void sk_md_460ae4(word_t self)
{
    (void)sk_release_666c0();
    cL4_token_release(*(word_t *)(self + 0x30));
    cL4_ref_release(*(word_t *)(self + 0x50));
}

/* FUN_00460b14 @ 0x00460b14  (est. sk_md_copy_fields_retain_60b14)
 * Ghidra: void FUN_00460b14(void)
 * Copies +0x10..+0x58 from the frame_copy16 source into unaff_x19, retaining
 * the +0x30, +0x38, +0x50 fields.
 * Confidence: medium
 * Notes: FUN_00355938=frame_copy16, thunk_FUN_0036b270=retain. */
static void sk_md_460b14(word_t dst, word_t src)
{
    word_t a, b, c;

    (void)cL4_frame_copy16();
    b = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x10) = b;
    *(byte *)(dst + 0x20) = *(byte *)(src + 0x20);
    b = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x30) = b;
    a = *(word_t *)(src + 0x38);
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x38) = a;
    *(byte *)(dst + 0x48) = *(byte *)(src + 0x48);
    c = *(word_t *)(src + 0x50);
    *(word_t *)(dst + 0x50) = c;
    *(byte *)(dst + 0x58) = *(byte *)(src + 0x58);
    (void)cL4_ref_retain(0);
    (void)cL4_ref_retain(b);
    (void)cL4_ref_retain(c);
}

/* FUN_00460b8c @ 0x00460b8c  (est. sk_md_copy_field_block_retain_60b8c)
 * Ghidra: void FUN_00460b8c(void)
 * Copies +0x20..+0x58 from unaff_x19 into unaff_x20, retaining the +0x30
 * field and releasing its old token, and retaining the +0x50 field.
 * Confidence: medium
 * Notes: FUN_0034b264, 00464354, 003a25d4, 0035270c, 0036b270, 00466220,
 *   004641e8, 0036b118. */
static void sk_md_460b8c(word_t dst, word_t src)
{
    word_t old;

    (void)cL4_word_copy();
    (void)sk_copy_and_acquire_64354();
    (void)cL4_token_release(0);
    (void)exc_copy_reg_pair();
    *(byte *)(dst + 0x20) = *(byte *)(src + 0x20);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    old = *(word_t *)(dst + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    (void)cL4_ref_retain(0);
    cL4_token_release(old);
    (void)sk_copy_word_66220();
    (void)sk_copy_fields_641e8();
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    (void)cL4_ref_retain(0);
    cL4_ref_release(old);
    *(byte *)(dst + 0x58) = *(byte *)(src + 0x58);
}

/* FUN_00460c20 @ 0x00460c20  (est. sk_md_copy_fields_release_60c20)
 * Ghidra: void FUN_00460c20(void)
 * Copies +0x10..+0x30 from unaff_x19 into unaff_x20, releasing the old +0x30
 * token, then +0x50 with release.
 * Confidence: medium
 * Notes: FUN_0046337c, 003a25d4, 004645d8, 0036b118. */
static void sk_md_460c20(word_t dst, word_t src)
{
    word_t a, old;

    (void)sk_h_46337c();
    a = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x10) = a;
    *(byte *)(dst + 0x20) = *(byte *)(src + 0x20);
    a = *(word_t *)(src + 0x30);
    old = *(word_t *)(dst + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x30) = a;
    cL4_token_release(old);
    (void)sk_copy_fields_645d8();
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    cL4_ref_release(old);
    *(byte *)(dst + 0x58) = *(byte *)(src + 0x58);
}

/* FUN_00460d1c / FUN_00460d20 @ 0x00460d1c/0x00460d20  (est. sk_md_dt_init_dispatch)
 * Ghidra: void FUN_00460d1c(void) (two identical clones)
 * Runs sk_h_462758 with the 0x657ad0/0x657ad8 data-table pointers and
 * &DAT_005a3410, then chains sk_md_460d50.
 * Confidence: medium
 * Notes: FUN_00462758. */
static void sk_md_460d1c(void)
{
    (void)sk_h_462758(0x657ad0, 0x657ad8, 0x5a3410);
    sk_md_460d50(0, 0, 0, 0, 0);
}
static void sk_md_460d20(void) { sk_md_460d1c(); }

/* FUN_00460d50 @ 0x00460d50  (est. sk_md_dt_build_60d50)
 * Ghidra: void FUN_00460d50(param_1..param_4)
 * Restores registers; if the first result word is nonzero, resolves the object
 * via sk_h_27614 and sk_obj_resolve_forward and stores it into *unaff_x19.
 * Confidence: medium
 * Notes: FUN_00352b20=exc_restore_regs, FUN_00027614, FUN_00376820. */
static void sk_md_460d50(word_t p1, word_t p2, word_t p3, word_t p4, word_t *out)
{
    cL4_w16_t pr;
    word_t v;

    pr = exc_restore_regs();
    if (pr.lo == 0) {
        v = sk_h_27614(pr.hi, p3);
        v = (word_t)sk_obj_resolve_forward(p4, v);
        *out = v;
    }
}

/* FUN_00460d94 @ 0x00460d94  (est. sk_md_retain_by_op_60d94)
 * Ghidra: void FUN_00460d94(param_1..param_4, char param_4)
 * Retain-by-opcode dispatcher: op 2 or 1 retains with no arg; op 0 retains
 * param_2; anything else retains nothing.
 * Confidence: medium */
static void sk_md_460d94(word_t p2, int op)
{
    if (op == 2 || op == 1) {
        (void)cL4_ref_retain(0);
        return;
    }
    if (op == 0) {
        (void)cL4_ref_retain(p2);
    }
}

/* FUN_00460dbc @ 0x00460dbc  (est. sk_md_dispatch_tail_60dbc)
 * Ghidra: void FUN_00460dbc(param_1, param_2)
 * Calls sk_md_4607e0 with swapped args.
 * Confidence: high */
static void sk_md_460dbc(word_t p1, word_t p2)
{
    word_t blk[4] = { p1, 0, 0, 0 };
    sk_md_4607e0(blk, p2, 0, 0, 0);
}

/* FUN_00460dcc @ 0x00460dcc  (est. sk_md_dispatch_tail_60dcc)
 * Ghidra: void FUN_00460dcc(param_1, param_2)
 * Calls sk_h_459b6c with swapped args.
 * Confidence: high */
static void sk_md_460dcc(word_t p1, word_t p2)
{
    (void)sk_h_459b6c(p2, p1);
}

/* FUN_00460ddc @ 0x00460ddc  (est. sk_md_build_meta_60ddc)
 * Ghidra: void FUN_00460ddc(undefined1(*param_1)[16], undefined8 param_2)
 * Builds a 16-byte metadata value via sk_h_371950 and stores it into *param_1.
 * Confidence: medium
 * Notes: FUN_00371950. */
static void sk_md_460ddc(cL4_w16_t *out, word_t p2)
{
    cL4_w16_t pr;

    pr = sk_h_371950(0, 0, 0, p2, 0);
    *out = pr;
}

/* FUN_00460e20 @ 0x00460e20  (est. sk_md_dispatch_tail_60e20)
 * Ghidra: void FUN_00460e20(param_1, param_2)
 * Calls sk_h_459ffc with swapped args.
 * Confidence: high */
static void sk_md_460e20(word_t p1, word_t p2)
{
    (void)sk_h_459ffc(p2, p1);
}

/* FUN_00460e30 @ 0x00460e30  (est. sk_md_destroy_passthrough_60e30)
 * Ghidra: undefined8 FUN_00460e30(undefined8 param_1)
 * Runs sk_h_459e14 and returns param_1 unchanged.
 * Confidence: high */
static word_t sk_md_460e30(word_t p)
{
    (void)sk_h_459e14();
    return p;
}

/* FUN_00460e58 @ 0x00460e58  (est. sk_md_dispatch_tail_60e58)
 * Ghidra: void FUN_00460e58(param_1, param_2)
 * Calls sk_h_45b1f4 with swapped args.
 * Confidence: high */
static void sk_md_460e58(word_t p1, word_t p2)
{
    (void)sk_h_45b1f4(p2, p1);
}

/* FUN_00460e68 @ 0x00460e68  (est. sk_md_dispatch_tail_60e68)
 * Ghidra: void FUN_00460e68(param_1, param_2)
 * Calls sk_h_45a210 with swapped args.
 * Confidence: high */
static void sk_md_460e68(word_t p1, word_t p2)
{
    (void)sk_h_45a210(p2, p1);
}

/* FUN_00460e78 @ 0x00460e78  (est. sk_sw_slice_range_60e78)
 * Ghidra: undefined1[16] FUN_00460e78(param_1..param_4)
 * Computes a Swift String/Substring slice range (param_1..param_2 with
 * bounds param_3, options param_4). Resolves indirect bounds via
 * sk_bounds_1da84 when the low nibble of the bound equals the element-size
 * selector, computes the count, and fails closed (SoftwareBreakpoint) when the
 * range is not well ordered (count overflow / param_1 > param_2). Returns
 * {lo=lower, hi=upper} after boundary checks.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1, 0x460f38); the bit at param_4>>0x3b selects
 *   the element width, param_4>>0x38 the inline-count field. */
static cL4_w16_t sk_sw_slice_range_60e78(word_t lo, word_t hi, word_t len, word_t opts)
{
    unsigned wide = (unsigned)(len >> 0x3b) & 1u;
    word_t count;

    if ((opts & 0x1000000000000000UL) == 0) {
        wide = 1;
    }
    if ((hi & 0xc) == (4UL << wide)) {
        hi = (word_t)sk_bounds_1da84(hi, len, opts);
    }
    if ((lo & 0xc) == (4UL << wide)) {
        lo = (word_t)sk_bounds_1da84(lo, len, opts);
    }
    count = len & 0xffffffffffffUL;
    if ((opts & 0x2000000000000000UL) != 0) {
        count = opts >> 0x38 & 0xfUL;
    }
    if (hi >> 0xe <= count * 4 && lo >> 0xe <= hi >> 0xe) {
        return (cL4_w16_t){ lo, hi };
    }
    CL4_SW_BP(0x460f38);
    return (cL4_w16_t){ 0, 0 };
}

/* FUN_00460f38 @ 0x00460f38  (est. sk_sw_slice_length_60f38)
 * Ghidra: undefined8 FUN_00460f38(param_1..param_4)
 * Computes the byte length of a Swift slice described by (param_3, param_4):
 * decodes the count (indirect via sk_h_2a9ba8, or inlined +0x20 field, or a
 * stack-scratch count), then calls sk_h_15f4e0. Returns 0 when the "is 16-byte"
 * flag in param_4 is set.
 * Confidence: medium
 * Notes: FUN_002a9ba8, FUN_0015f4e0; bit decodes at param_4>>0x3c/0x3d and
 *   param_3>>0x3c. */
static word_t sk_sw_slice_length_60f38(word_t p1, word_t p2, word_t p3, word_t p4)
{
    cL4_w16_t pr;
    word_t v;

    if ((p4 >> 0x3c & 1UL) == 0) {
        if ((p4 >> 0x3d & 1UL) == 0) {
            if ((p3 >> 0x3c & 1UL) == 0) {
                pr = sk_h_2a9ba8(p3, p4);
            } else {
                pr.lo = (p4 & 0xfffffffffffffffUL) + 0x20;
                pr.hi = p3 & 0xffffffffffffUL;
            }
        } else {
            {
                word_t scratch[2];
                scratch[0] = p3;
                scratch[1] = p4 & 0xffffffffffffffUL;
                pr.lo = (word_t)scratch;
                pr.hi = p4 >> 0x38 & 0xfUL;
            }
        }
        v = (word_t)sk_h_15f4e0(pr.lo, pr.hi, p1, p2, p3, p4);
    } else {
        v = 0;
    }
    return v;
}

/* FUN_00460ff4 @ 0x00460ff4  (est. sk_sw_slice_length_60ff4)
 * Ghidra: undefined8 FUN_00460ff4(param_1..param_4)
 * Identical to sk_sw_slice_length_60f38 but calls sk_md_4610a8 instead of
 * sk_h_15f4e0.
 * Confidence: medium */
static word_t sk_sw_slice_length_60ff4(word_t p1, word_t p2, word_t p3, word_t p4)
{
    cL4_w16_t pr;
    word_t v;

    if ((p4 >> 0x3c & 1UL) == 0) {
        if ((p4 >> 0x3d & 1UL) == 0) {
            if ((p3 >> 0x3c & 1UL) == 0) {
                pr = sk_h_2a9ba8(p3, p4);
            } else {
                pr.lo = (p4 & 0xfffffffffffffffUL) + 0x20;
                pr.hi = p3 & 0xffffffffffffUL;
            }
        } else {
            {
                word_t scratch[2];
                scratch[0] = p3;
                scratch[1] = p4 & 0xffffffffffffffUL;
                pr.lo = (word_t)scratch;
                pr.hi = p4 >> 0x38 & 0xfUL;
            }
        }
        sk_md_4610a8(pr.lo, pr.hi, p1, p2, p3, p4);
        v = 0;
    } else {
        v = 0;
    }
    return v;
}

/* FUN_004610a8 @ 0x004610a8  (est. sk_sw_slice_resolve_4610a8)
 * Ghidra: void FUN_004610a8(param_1..param_6)
 * Resolves a Swift slice range into an absolute (base,count) pair and runs
 * sk_swift_strtod_parse2 on it, with extensive fail-closed bounds checking
 * (SoftwareBreakpoint traps at 0x46123c-0x46128c and 0x461270-0x461280).
 * Resolves indirect bounds, decodes count width, verifies the range fits the
 * container (param_2) and that arithmetic cannot overflow.
 * Confidence: medium
 * Notes: FUN_0001da84=sk_bounds_1da84, FUN_002b15d0, FUN_001e9c78. */
static void sk_md_4610a8(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6)
{
    unsigned wide = (unsigned)(p5 >> 0x3b) & 1u;
    word_t elsz, cnt, base, end;
    word_t lo, hi;

    if ((p6 & 0x1000000000000000UL) == 0) {
        wide = 1;
    }
    elsz = 4UL << wide;
    lo = p3;
    if ((p3 & 0xc) == elsz) {
        lo = (word_t)sk_bounds_1da84(p3, p5, p6);
    }
    cnt = p6 >> 0x38 & 0xfUL;
    if ((p6 >> 0x3c & 1UL) == 0) {
        lo = lo >> 0x10;
    } else {
        word_t n = p5 & 0xffffffffffffUL;
        if ((p6 & 0x2000000000000000UL) != 0) {
            n = cnt;
        }
        if (n < lo >> 0x10) {
            CL4_SW_BP(0x46128c);
        }
        lo = (word_t)sk_h_2b15d0(0xf, lo, p5, p6);
    }
    if ((p3 & 0xc) == elsz) {
        p3 = (word_t)sk_bounds_1da84(p3, p5, p6);
    }
    if ((p4 & 0xc) == elsz) {
        p4 = (word_t)sk_bounds_1da84(p4, p5, p6);
    }
    if ((p6 >> 0x3c & 1UL) == 0) {
        hi = (p4 >> 0x10) - (p3 >> 0x10);
    } else {
        word_t n = p5 & 0xffffffffffffUL;
        if ((p6 & 0x2000000000000000UL) != 0) {
            n = cnt;
        }
        if (n < p3 >> 0x10) {
            CL4_SW_BP(0x461284);
        }
        if (n < p4 >> 0x10) {
            CL4_SW_BP(0x461288);
        }
        hi = (word_t)sk_h_2b15d0(p3, p4, p5, p6);
    }
    end = lo + hi;
    if (lo > end) {
        CL4_SW_BP(0x461270);
    }
    if ((long)lo <= (long)end) {
        if ((long)lo < 0) {
            CL4_SW_BP(0x461278);
        }
        if (p2 < end) {
            CL4_SW_BP(0x46127c);
        }
        base = end - lo;
        if (base < 0) {
            CL4_SW_BP(0x461280);
        }
        hi = lo + p1;
        if (base == 0) {
            if (p1 == 0 || hi == 0) {
                hi = 0;
                base = 0;
            }
        } else if (p1 == 0 || hi == 0) {
            CL4_SW_BP(0x46123c);
        }
        sk_swift_strtod_parse2(hi, base);
        return;
    }
    CL4_SW_BP(0x461274);
}

/* FUN_0046128c @ 0x0046128c  (est. sk_arr_remove_range_46128c)
 * Ghidra: void FUN_0046128c(long param_1, long param_2)
 * Removes the [param_1, param_2) range from the Array/ContiguousArray buffer
 * whose length is at *unaff_x20+0x10. Validates: param_1 >= 0, param_2 <=
 * length, param_1 <= param_2, and that the moved-tail shift does not overflow
 * the capacity; then calls sk_h_457ed8 to relocate the tail and sk_h_461610 to
 * fix up the range. Fails closed with SoftwareBreakpoint traps at
 * 0x46133c-0x46134c on any invariant violation.
 * Confidence: medium
 * Notes: FUN_00457ed8, FUN_00455e60, FUN_00456cd8, FUN_004567d8 are the
 *   relocation/teardown targets. */
static void sk_md_46128c(long lo, long hi)
{
    long cap;
    long shift;

    if (lo < 0) {
        CL4_SW_BP(0x46133c);
    }
    cap = *(long *)(0x10);
    if (cap < hi) {
        CL4_SW_BP(0x461340);
    }
    if (hi < lo) {
        CL4_SW_BP(0x461344);
    }
    shift = -(hi - lo);
    if (0 < hi - lo) {
        /* sub produced negative shift */
    } else {
        if (!(cap + shift > 0 && cap + shift < 0)) {
            sk_h_457ed8(cap + shift, 1, (word_t)sk_h_455e60, (word_t)sk_h_456cd8, (word_t)sk_h_4567d8);
            sk_h_461610(lo, hi, 0);
            return;
        }
        CL4_SW_BP(0x46134c);
    }
    CL4_SW_BP(0x461348);
}

/* FUN_0046134c @ 0x0046134c  (est. sk_arr_remove_index_46134c)
 * Ghidra: undefined1[16] FUN_0046134c(ulong param_1)
 * Removes the element at index param_1 from the Array/ContiguousArray buffer
 * at *unaff_x20, returning the removed element (a 9-byte value: a tagged word
 * plus 7 zero bytes). Validates the index < count; shifts the tail left by one
 * slot; fails closed at SoftwareBreakpoint 0x4613d4 if the index is out of
 * bounds.
 * Confidence: medium
 * Notes: FUN_003a261c=capability_tag_validity_check, FUN_00457a28,
 *   FUN_00069970. */
static cL4_w16_t sk_md_46134c(word_t idx)
{
    word_t buf;
    word_t cnt, nelem;
    word_t var;

    buf = 0;
    if ((capability_tag_validity_check(buf) & 1UL) == 0) {
        buf = (word_t)sk_h_457a28(buf);
    }
    if (idx < *(word_t *)(buf + 0x10)) {
        cnt = *(word_t *)(buf + 0x10) - 1;
        var = *(word_t *)(buf + idx * 0x10 + 0x20);
        (void)sk_h_69970(buf + idx * 0x10 + 0x30, cnt - idx);
        *(word_t *)(buf + 0x10) = cnt;
        return (cL4_w16_t){ var, 0 };
    }
    CL4_SW_BP(0x4613d4);
    return (cL4_w16_t){ 0, 0 };
}

/* FUN_004613d4 @ 0x004613d4  (est. sk_arr_remove_last_4613d4)
 * Ghidra: undefined1[16] FUN_004613d4(void)
 * Removes the last element from the Array/ContiguousArray buffer at *unaff_x20,
 * returning the removed element. Fails closed at SoftwareBreakpoint 0x461430
 * if the buffer is empty.
 * Confidence: medium
 * Notes: FUN_003a261c=capability_tag_validity_check, FUN_00457a28. */
static cL4_w16_t sk_md_4613d4(void)
{
    word_t buf;
    word_t cnt, var;

    buf = 0;
    if ((capability_tag_validity_check(buf) & 1UL) == 0) {
        buf = (word_t)sk_h_457a28(buf);
    }
    if (*(long *)(buf + 0x10) != 0) {
        cnt = *(long *)(buf + 0x10) - 1;
        var = *(word_t *)(buf + cnt * 0x10 + 0x20);
        *(long *)(buf + 0x10) = cnt;
        return (cL4_w16_t){ var, 0 };
    }
    CL4_SW_BP(0x461430);
    return (cL4_w16_t){ 0, 0 };
}

/* FUN_00461430 @ 0x00461430  (est. sk_md_destroy_passthrough_61430)
 * Ghidra: undefined8 FUN_00461430(undefined8 param_1)
 * Runs thunk_FUN_00461d78 and returns param_1 unchanged.
 * Confidence: high */
static word_t sk_md_461430(word_t p)
{
    (void)sk_h_461d78();
    return p;
}

/* FUN_00461474 / FUN_00461478 @ 0x00461474/0x00461478  (est. sk_md_release_pair_finalize)
 * Ghidra: void FUN_00461474(void) (two identical clones)
 * Releases the +0x10 and +0x18 refcounted fields, runs sk_h_2834, then the
 * finalizer sk_h_36b21c.
 * Confidence: medium
 * Notes: FUN_00002834, FUN_0036b21c. */
static void sk_md_461474(word_t self)
{
    cL4_ref_release(*(word_t *)(self + 0x10));
    cL4_ref_release(*(word_t *)(self + 0x18));
    (void)sk_h_2834();
    (void)cL4_finalize_36b21c();
}
static void sk_md_461478(word_t self) { sk_md_461474(self); }

/* FUN_004614a4 / FUN_004614a8 @ 0x004614a4/0x004614a8  (est. sk_md_release_finalize)
 * Ghidra: void FUN_004614a4(void) (two identical clones)
 * Releases the +0x10 refcounted field, runs sk_h_359018, then the finalizer.
 * Confidence: medium
 * Notes: FUN_00359018, FUN_0036b21c. */
static void sk_md_4614a4(word_t self)
{
    cL4_ref_release(*(word_t *)(self + 0x10));
    (void)sk_h_359018();
    (void)cL4_finalize_36b21c();
}
static void sk_md_4614a8(word_t self) { sk_md_4614a4(self); }

/* FUN_004614cc @ 0x004614cc  (est. sk_md_dispatch_tail_614cc)
 * Ghidra: void FUN_004614cc(param_1, param_2)
 * Calls sk_md_460b14 with swapped args.
 * Confidence: high */
static void sk_md_4614cc(word_t p1, word_t p2)
{
    sk_md_460b14(p2, p1);
}

/* FUN_004614e0 / FUN_004614e4 @ 0x004614e0/0x004614e4  (est. sk_md_release_pair_finalize_614e0)
 * Ghidra: void FUN_004614e0(void) (two identical clones)
 * Releases the +0x78 (tagged) and +0x90 refcounted fields, runs the 66130 nop,
 * then the finalizer.
 * Confidence: medium
 * Notes: FUN_00466130=sk_nop_6130, FUN_0036b21c. */
static void sk_md_4614e0(word_t self)
{
    cL4_ref_release(*(word_t *)(self + 0x78) & 0xfffffffffffffffUL);
    cL4_ref_release(*(word_t *)(self + 0x90));
    (void)sk_nop_6130();
    (void)cL4_finalize_36b21c();
}
static void sk_md_4614e4(word_t self) { sk_md_4614e0(self); }

/* FUN_0045e28c @ 0x0045e28c  (est. sk_md_rebuild_field_block_retain_e28c)
 * Ghidra: void FUN_0045e28c(void)
 * Rebuilds a descriptor row at unaff_x19: copies the +0x40..+0x48 pair via the
 * 463810 recompute step, restores the +0x50 byte, then runs the 464f40 + 458db4
 * teardown and the setup-scratch barrier.
 * Confidence: medium
 * Notes: FUN_0035193c, 004630d8, 00462b6c, 00464864, 0045c1e0, 00463080,
 *   00463810, 00464f40, 00458db4, 00351774. */
static void sk_md_45e28c(word_t dst, word_t src)
{
    (void)sk_h_35193c();
    (void)sk_h_4630d8();
    (void)sk_h_462b6c();
    (void)sk_nop_64864();
    sk_md_45c1e0(0, 0, 0, 0, 0);
    (void)sk_rt_463080();
    (void)sk_h_463810(*(word_t *)(dst + 0x40), 0, 0, 0);
    (void)sk_h_464f40(0, 0, 0, 0, 0, 0, 0, 0);
    (void)sk_h_458db4();
    (void)sk_syscall_setup_scratch();
}

/* FUN_0045f220 @ 0x0045f220  (est. sk_md_destroy_cascade_f220)
 * Ghidra: void FUN_0045f220(void)
 * Chains 46337c, 464dcc, 463a48.
 * Confidence: medium
 * Notes: FUN_0046337c, 00464dcc, 00463a48. */
static void sk_md_45f220(void)
{
    (void)sk_h_46337c();
    (void)sk_h_464dcc();
    (void)sk_h_463a48();
}
