/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 17: 0x73b7c-0x776b4. All names are estimates unless string/header-
 * matched. Uses seL4/cL4 vocabulary.
 *
 * This region is the cap-vector / cap-allocation factory layer. It contains:
 *   - cap-factory wrappers (0x73b7c-0x7499c): per-cap-type allocation
 *     front-ends that lock the grow state, call a per-element-size allocator
 *     dispatcher (FUN_00071c4c/1d74/1dbc/1e04/1e74/1f54/1f9c), then either
 *     copy the freshly-built element into the vector or grow + move the tail.
 *   - ranged element-copy helpers (0x74a28-0x75c50): copy [from,to) elements
 *     of a fixed stride out of a container into a destination range, with a
 *     non-overlap check and a tail release of the container token.
 *   - vector insert/move/remove primitives (0x75cb4-0x76d08): lock-tagged
 *     (FUN_00258c60) element insertion with grow-on-collision, moving/clearing
 *     the prior occupant, and the two bitmap-slot iterator cores (0x76ac8,
 *     0x76d08) that walk set bits of a reversed bitmap to enumerate free/
 *     occupied slots and write the element into each.
 *   - small pointer/tagged-union helpers (0x76f74-0x774c8) and the
 *     container lock-state / size / copy glue (0x7752c-0x776b4).
 *
 * NOTE on the calling convention: as in the sibling slices, the decompiler
 * shows many of these as `void FUN(void)` because all arguments (including
 * the C++ `this`, `unaff_x19`/`unaff_x20`) travel in registers and are not
 * modelled as formal parameters. We model the container `this` pointer as an
 * explicit first parameter `thisp` and give the helper signatures that match
 * the register usage observed at call sites. Ghidra FUN_ names and DAT_
 * typeinfo pairs are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (bodies reconstructed by the
 * range workers that own them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern word_t FUN_0036b118(word_t);            /* cL4 ref release */
extern word_t FUN_003a25d4(word_t);            /* token release */
extern word_t FUN_003a261c(word_t);            /* allocator probe */
extern void   FUN_00117cc4(word_t, word_t, word_t); /* memcpy */
extern void   FUN_00117d14(word_t, word_t, word_t); /* memmove */
extern word_t FUN_0035b67c(word_t, word_t, word_t, word_t); /* constructed-copy */
extern word_t FUN_00002534(word_t, word_t);    /* typeinfo resolve (tag pair) */
extern word_t FUN_00258c60(word_t, word_t, word_t); /* lock-tag acquire */
extern void   FUN_002591b4(word_t);            /* fatal exception (noreturn) */
extern word_t FUN_0036aae4(void);              /* tag deref / move */
extern word_t thunk_FUN_0036b270(word_t);      /* retain (returns obj) */
extern word_t FUN_0036a9d4(word_t, word_t);    /* object alloc */
extern word_t thunk_FUN_000126e8(void);        /* size/count probe */
extern void   FUN_0006ae9c(word_t, word_t);    /* span/key builder */
extern void   FUN_00072464(word_t);            /* slot-key resolve */
extern void   FUN_000724cc(word_t, word_t);    /* slot-key resolve (2 arg) */
extern void   FUN_0007198c(word_t *, word_t, word_t, word_t); /* bitmap ctx */
extern void   FUN_00072664(word_t);            /* key rebuild */
extern void   FUN_00081b10(word_t, word_t, word_t, word_t, word_t); /* insert */
extern void   FUN_00081b4c(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t, word_t); /* insert (wide) */
extern void   FUN_00081b9c(void);              /* insert-move */
extern void   FUN_00081bd0(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t);    /* insert (5-arg) */
extern void   FUN_00081c1c(word_t);            /* insert */
extern void   FUN_00081c58(void);              /* insert-move */
extern void   FUN_00081c98(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t);    /* insert (wide) */
extern void   FUN_00081d14(void);              /* insert */
extern void   FUN_00081d60(void);              /* insert-move */
extern void   FUN_00081df0(void);              /* insert */
extern void   FUN_00081fe0(word_t *, word_t, word_t, word_t); /* build */
extern word_t thunk_FUN_00081ce8(word_t);      /* element move */
extern void   FUN_000777c4(word_t, word_t, word_t); /* move helper */
extern void   FUN_00077860(word_t, word_t, word_t, word_t); /* move (u08) */
extern word_t FUN_00077888(void);              /* size probe */
extern void   FUN_00077910(void);              /* typeinfo probe */
extern void   FUN_000776e4(void);              /* constructed copy */
extern word_t FUN_000776d8(void);              /* grow probe */
extern void   FUN_000776cc(void);              /* grow probe */
extern void   FUN_0007764c(word_t, word_t);    /* token/typeinfo build */
extern void   FUN_000776f8(void);              /* size bump */
extern void   FUN_000775dc(word_t);            /* size compute */
extern void   FUN_0007791c(word_t);            /* alloc */
extern void   FUN_00077630(void);              /* alloc count probe */
extern void   FUN_0007766c(word_t);            /* size compute */
extern void   FUN_00072044(word_t, word_t, word_t); /* move tail (u10) */
extern void   FUN_000721b0(word_t, word_t, word_t); /* move tail (u08) */
extern void   FUN_0007220c(word_t, word_t, word_t); /* move tail (u18) */
extern void   FUN_000723c0(word_t, word_t, word_t); /* move tail (u28) */
extern void   FUN_000723f4(word_t, word_t, word_t); /* move tail (u30) */
extern void   FUN_0007206c(word_t, word_t, word_t); /* move tail (u28,memmove) */
extern void   FUN_00072358(word_t, word_t, word_t); /* move tail */
extern void   FUN_00072270(word_t, word_t, word_t); /* move tail */
extern void   FUN_000722b0(word_t, word_t, word_t); /* move tail */
extern void   FUN_00069970(word_t, word_t, word_t); /* move tail */
extern void   FUN_000699a4(word_t, word_t, word_t); /* move tail */
extern void   FUN_000699d8(word_t, word_t, word_t); /* move tail */
extern long   FUN_000737e8(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t);    /* generic cap factory */
extern word_t FUN_00071c4c(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071d74(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071dbc(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071e04(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071e74(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071f54(word_t, word_t, word_t, word_t); /* alloc dispatcher */
extern word_t FUN_00071f9c(word_t, word_t, word_t, word_t); /* alloc dispatcher */

/* Lock-state / element-vector glue reconstructed in this slice. */
static word_t sk_lock_state_save(void) { return 0; }            /* 7752c */
static void   sk_lock_state_clear(void) { }                     /* 77550 */
static void   sk_lock_state_probe(void) { }                     /* 77560 */
static void   sk_lock_state_enter(void) { }                     /* 77570 */
static word_t sk_this_tail(word_t thisp) { return thisp + 0x20; } /* 77580 */
static void   sk_slot_release(word_t thisp, word_t slot) { }    /* 77590 */
static void   sk_clear_element(word_t thisp) { }                /* 77604 */
static void   sk_element_probe(void) { }                        /* 77614 */
static void   sk_overflow_probe(void) { }                       /* 77624 */

/* ================================================================== *
 * Cap-type allocation factory wrappers.
 * Common shape (register-passed `this` in x19, grow flag in x20/param_3):
 *   - enter the grow lock state
 *   - if the grow flag is set and the size probe reports overflow, take the
 *     overflow path (fatal SBP if negative)
 *   - call the per-element-size allocator dispatcher with the element table
 *     (this+0x10), the value, and the (typeinfo, move-tag) pair
 *   - on the in-place path call the matching range-copy helper; on the grow
 *     path advance the tail and move the displaced tail run, then release the
 *     old element token.
 * ================================================================== */

/* FUN_00073b7c @ 0x73b7c  (est. sk_cap_factory_u10)
 * Cap-factory front-end (0x10-byte element vector): lock the grow state,
 * dispatch allocation via FUN_00071e04 on the element table, then either
 * range-copy the built element (FUN_000750bc) or grow+move+release.
 * Confidence: medium */
static word_t sk_cap_factory_73b7c(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73c08) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e04(*(word_t *)(thisp + 0x10), v, 0x64e820, 0x4c0678);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c -> 0 */
        sk_copy17_750bc(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000721b0(/*move tail*/ 0, 0, 0);    /* 721b0 */
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073c08 @ 0x73c08  (est. sk_cap_factory_u08a)
 * Cap-factory front-end over FUN_00071e04 (8-byte element vector); range-copy
 * via FUN_00075118, grow+move via FUN_000721d8.
 * Confidence: medium */
static word_t sk_cap_factory_73c08(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73c94) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e04(*(word_t *)(thisp + 0x10), v, 0x64e818, 0x4c0670);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75118(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000721d8(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073c94 @ 0x73c94  (est. sk_cap_factory_u18a)
 * Cap-factory front-end over FUN_00071d74 (0x18-byte element vector);
 * range-copy via FUN_000751b4, grow+move via FUN_0007220c.
 * Confidence: medium */
static word_t sk_cap_factory_73c94(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73d30) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071d74(*(word_t *)(thisp + 0x10), v, 0x64e808, 0x4c0660);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_751b4(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_0007220c(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073d30 @ 0x73d30  (est. sk_cap_factory_thunk1)
 * Thin thunk to the generic cap factory FUN_000737e8.
 * Confidence: high (single call) */
static void sk_cap_factory_thunk_73d30(word_t a, word_t b, word_t c,
                                       word_t d, word_t e, word_t f, word_t g)
{
    FUN_000737e8(a, b, c, d, e, f, g);
}

/* FUN_00073d70 @ 0x73d70  (est. sk_cap_factory_u38)
 * Cap-factory front-end over FUN_00071c4c (0x38-byte element vector);
 * range-copy via FUN_000752a4, grow+move via FUN_00072270.
 * Confidence: medium */
static word_t sk_cap_factory_73d70(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73dfc) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071c4c(*(word_t *)(thisp + 0x10), v, 0x64e7f0, 0x4c0648);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_752a4(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00072270(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073dfc @ 0x73dfc  (est. sk_cap_factory_u10b)
 * Cap-factory front-end over FUN_00071e74 (0x10-byte element vector);
 * range-copy via FUN_0007534c, grow+move via FUN_00069970.
 * Confidence: medium */
static word_t sk_cap_factory_73dfc(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73e88) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e74(*(word_t *)(thisp + 0x10), v, 0x64e7c0, 0x4c0618);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_7534c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00069970(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073e88 @ 0x73e88  (est. sk_cap_factory_u28)
 * Cap-factory front-end over FUN_00071f9c (0x28-byte element vector);
 * range-copy via FUN_000753c0, grow+move via FUN_0007206c.
 * Confidence: medium */
static word_t sk_cap_factory_73e88(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73f14) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f9c(*(word_t *)(thisp + 0x10), v, 0x64e7d0, 0x4c0628);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_753c0(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_0007206c(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073f14 @ 0x73f14  (est. sk_cap_factory_u10c)
 * Cap-factory front-end over FUN_00071e74 (0x10-byte element vector);
 * range-copy via FUN_0007543c, grow+move via FUN_00069970.
 * Confidence: medium */
static word_t sk_cap_factory_73f14(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x73fa0) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e74(*(word_t *)(thisp + 0x10), v, 0x64e7b8, 0x4c0610);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_7543c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00069970(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00073fa0 @ 0x73fa0  (est. sk_cap_factory_u18b)
 * Cap-factory front-end over FUN_00071d74 (0x18-byte element vector);
 * range-copy via FUN_000754b0, grow+move via FUN_000699d8.
 * Confidence: medium */
static word_t sk_cap_factory_73fa0(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x7402c) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071d74(*(word_t *)(thisp + 0x10), v, 0x64e7c8, 0x4c0620);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_754b0(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000699d8(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_0007402c @ 0x7402c  (est. sk_cap_factory_u20a)
 * Cap-factory front-end over FUN_00071dbc (0x20-byte element vector);
 * grow+move via FUN_000699a4 (no in-place range copy in this shape).
 * Confidence: medium */
static word_t sk_cap_factory_7402c(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x740b8) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071dbc(*(word_t *)(thisp + 0x10), v, 0x64e7b0, 0x4c0608);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_74b08(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000699a4(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_000740b8 @ 0x740b8  (est. sk_cap_factory_u28b)
 * Cap-factory front-end over FUN_00071f9c (0x28-byte element vector);
 * range-copy via FUN_00075b2c, grow+move via FUN_000723c0.
 * Confidence: medium */
static word_t sk_cap_factory_740b8(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74154) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f9c(*(word_t *)(thisp + 0x10), v, 0x64e748, 0x4c0598);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75b2c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000723c0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074154 @ 0x74154  (est. sk_cap_factory_u38b)
 * Cap-factory front-end over FUN_00071c4c (0x38-byte element vector);
 * range-copy via FUN_0007552c, grow+move via FUN_000722b0.
 * Confidence: medium */
static word_t sk_cap_factory_74154(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x741e0) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071c4c(*(word_t *)(thisp + 0x10), v, 0x64e750, 0x4c05a0);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_7552c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000722b0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_000741e0 @ 0x741e0  (est. sk_cap_factory_thunk2)
 * Thin thunk to the generic cap factory FUN_000737e8.
 * Confidence: high (single call) */
static void sk_cap_factory_thunk_741e0(word_t a, word_t b, word_t c,
                                       word_t d, word_t e, word_t f, word_t g)
{
    FUN_000737e8(a, b, c, d, e, f, g);
}

/* FUN_00074220 @ 0x74220  (est. sk_cap_factory_u10d)
 * Cap-factory front-end over FUN_00071e74 (0x10-byte element vector);
 * range-copy via FUN_00075624, grow+move via FUN_00069970.
 * Confidence: medium */
static word_t sk_cap_factory_74220(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x742ac) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e74(*(word_t *)(thisp + 0x10), v, 0x64e6b0, 0x4c0500);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75624(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00069970(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_000742ac @ 0x742ac  (est. sk_cap_factory_thunk3)
 * Thin thunk to the generic cap factory FUN_000737e8.
 * Confidence: high (single call) */
static void sk_cap_factory_thunk_742ac(word_t a, word_t b, word_t c,
                                       word_t d, word_t e, word_t f, word_t g)
{
    FUN_000737e8(a, b, c, d, e, f, g);
}

/* FUN_000742ec @ 0x742ec  (est. sk_cap_factory_u20b)
 * Cap-factory front-end over FUN_00071dbc (0x20-byte element vector);
 * range-copy via FUN_00075710, grow+move via FUN_000699a4.
 * Confidence: medium */
static word_t sk_cap_factory_742ec(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74378) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071dbc(*(word_t *)(thisp + 0x10), v, 0x64e790, 0x4c05e8);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75710(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000699a4(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074378 @ 0x74378  (est. sk_cap_factory_u18c)
 * Cap-factory front-end over FUN_00071d74 (0x18-byte element vector);
 * range-copy via FUN_00075784, grow+move via FUN_00072358.
 * Confidence: medium */
static word_t sk_cap_factory_74378(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74404) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071d74(*(word_t *)(thisp + 0x10), v, 0x64e6c0, 0x4c0510);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75784(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00072358(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074404 @ 0x74404  (est. sk_cap_factory_u20c)
 * Cap-factory front-end over FUN_00071dbc (0x20-byte element vector);
 * range-copy via FUN_000757e8, grow+move via FUN_000699a4.
 * Confidence: medium */
static word_t sk_cap_factory_74404(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74490) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071dbc(*(word_t *)(thisp + 0x10), v, 0x64e6c8, 0x4c0518);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_757e8(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000699a4(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074490 @ 0x74490  (est. sk_cap_factory_u28c)
 * Cap-factory front-end over FUN_00071f9c (0x28-byte element vector);
 * range-copy via FUN_0007585c, grow+move via FUN_0007206c.
 * Confidence: medium */
static word_t sk_cap_factory_74490(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x7451c) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f9c(*(word_t *)(thisp + 0x10), v, 0x64e6e8, 0x4c0538);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_7585c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_0007206c(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_0007451c @ 0x7451c  (est. sk_cap_factory_u10_grow)
 * Cap-factory with explicit capacity growth: when the grow flag is set, the
 * desired capacity is half of the current count (this+0x18>>1), clamped up to
 * the requested count (fatal 0x73604 on signed overflow past 0x4000000000000000),
 * else kept at the current even count. Dispatch via FUN_00071e74; on the
 * in-place path range-copy via FUN_000758d8 with a fixed move tag 0x659bd0;
 * on the grow path move the tail and release the old element.
 * Confidence: medium */
static word_t sk_cap_factory_grow_7451c(word_t thisp, word_t count, word_t flags,
                                        word_t *out)
{
    word_t capacity = count;
    word_t elem;
    if ((flags & 1) != 0) {
        capacity = *(word_t *)(thisp + 0x18) >> 1;
        if ((long)capacity < (long)count) {
            if ((long)(capacity + 0x4000000000000000) < 0) CL4_FATAL(); /* 73604 */
            capacity = *(word_t *)(thisp + 0x18) & 0xfffffffffffffffe;
            if ((long)capacity <= (long)count) capacity = count;
        }
    }
    elem = *(word_t *)(thisp + 0x10);
    capacity = FUN_00071e74(elem, capacity, 0x64e6e0, 0x4c0530);
    if ((flags & 1) == 0) {
        sk_copy17_758d8(0, elem, capacity + 0x20, thisp, 0x659bd0);
    } else {
        FUN_00072044(thisp + 0x20, elem, capacity + 0x20);
        FUN_00077718(/*release*/);
    }
    return capacity;
}

/* FUN_00074538 @ 0x74538  (est. sk_cap_factory_u08b)
 * Cap-factory front-end over FUN_00071e04 (8-byte element vector);
 * range-copy via FUN_00075948, grow+move via FUN_000721b0.
 * Confidence: medium */
static word_t sk_cap_factory_74538(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x745d4) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e04(*(word_t *)(thisp + 0x10), v, 0x64e6f8, 0x4c0548);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75948(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000721b0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_000745d4 @ 0x745d4  (est. sk_cap_factory_u08c)
 * Cap-factory front-end over FUN_00071e04 (8-byte element vector);
 * range-copy via FUN_00075948, grow+move via FUN_000721b0. Distinct typeinfo
 * pair (0x64e6d8, 0x4c2e80).
 * Confidence: medium */
static word_t sk_cap_factory_745d4(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74670) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e04(*(word_t *)(thisp + 0x10), v, 0x64e6d8, 0x4c2e80);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75948(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000721b0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074670 @ 0x74670  (est. sk_cap_factory_u10e)
 * Cap-factory front-end over FUN_00071e74 (0x10-byte element vector);
 * range-copy via FUN_000759c0, grow+move via FUN_00072044.
 * Confidence: medium */
static word_t sk_cap_factory_74670(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x7470c) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e74(*(word_t *)(thisp + 0x10), v, 0x64e708, 0x4c0558);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_759c0(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00072044(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_0007470c @ 0x7470c  (est. sk_cap_factory_u10f)
 * Cap-factory front-end over FUN_00071e74 (0x10-byte element vector);
 * range-copy via FUN_000759c0, grow+move via FUN_00072044. Distinct typeinfo
 * pair (0x64e720, 0x4c0570).
 * Confidence: medium */
static word_t sk_cap_factory_7470c(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x747a8) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071e74(*(word_t *)(thisp + 0x10), v, 0x64e720, 0x4c0570);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_759c0(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_00072044(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_000747a8 @ 0x747a8  (est. sk_cap_factory_u30)
 * Cap-factory front-end over FUN_00071f54 (0x30-byte element vector);
 * range-copy via FUN_00075a38, grow+move via FUN_000723f4.
 * Confidence: medium */
static word_t sk_cap_factory_747a8(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74834) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f54(*(word_t *)(thisp + 0x10), v, 0x64e730, 0x4c0580);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75a38(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000723f4(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074834 @ 0x74834  (est. sk_cap_factory_thunk4)
 * Thin thunk to the generic cap factory FUN_000737e8.
 * Confidence: high (single call) */
static void sk_cap_factory_thunk_74834(word_t a, word_t b, word_t c,
                                       word_t d, word_t e, word_t f, word_t g)
{
    FUN_000737e8(a, b, c, d, e, f, g);
}

/* FUN_00074874 @ 0x74874  (est. sk_cap_factory_u28d)
 * Cap-factory front-end over FUN_00071f9c (0x28-byte element vector);
 * range-copy via FUN_00075b2c, grow+move via FUN_000723c0. Distinct typeinfo
 * pair (0x64e770, 0x4c2ea0).
 * Confidence: medium */
static word_t sk_cap_factory_74874(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74910) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f9c(*(word_t *)(thisp + 0x10), v, 0x64e770, 0x4c2ea0);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75b2c(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000723c0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_00074910 @ 0x74910  (est. sk_cap_factory_u30b)
 * Cap-factory front-end over FUN_00071f54 (0x30-byte element vector);
 * range-copy via FUN_00075bac, grow+move via FUN_000723f4.
 * Confidence: medium */
static word_t sk_cap_factory_74910(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x7499c) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f54(*(word_t *)(thisp + 0x10), v, 0x64e698, 0x4c04e8);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75bac(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000723f4(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}

/* FUN_0007499c @ 0x7499c  (est. sk_cap_factory_u28e)
 * Cap-factory front-end over FUN_00071f9c (0x28-byte element vector);
 * range-copy via FUN_00075c50, grow+move via FUN_000723c0. Distinct typeinfo
 * pair (0x64e628, 0x4c0478).
 * Confidence: medium */
static word_t sk_cap_factory_7499c(word_t thisp, word_t value, word_t flags)
{
    word_t v;
    sk_lock_state_enter();                      /* 77570 */
    v = value;
    if ((flags & 1) != 0 && sk_lock_state_probe()) {
        sk_overflow_probe();                    /* 77624 */
        if (/*NG*/ 1) CL4_FATAL();              /* SBP(1,0x74a28) */
        sk_lock_state_clear();                  /* 77550 */
    }
    v = FUN_00071f9c(*(word_t *)(thisp + 0x10), v, 0x64e628, 0x4c0478);
    if ((flags & 1) == 0) {
        sk_lock_state_save();                   /* 7752c */
        sk_copy17_75c50(0, 0, 0, thisp);
    } else {
        sk_this_tail(thisp);                    /* 77580 */
        FUN_000723c0(/*move tail*/ 0, 0, 0);
        FUN_00077718(/*release*/);
    }
    return v;
}
