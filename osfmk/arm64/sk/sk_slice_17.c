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

/* ================================================================== *
 * Ranged element-copy helpers.  Each copies [from,to) elements of a fixed
 * stride out of a container into a destination range (dest).  It first
 * requires to >= from (SBORROW fatal), computes source = container +
 * from*SIZE + 0x20 and end = dest + n*SIZE, verifies the source and
 * destination ranges do not overlap, performs the copy (plain memcpy for
 * trivially-copyable elements, constructed-copy for the rest), releases the
 * container token, and returns the destination end.  Any overlap or negative
 * range is a hard fatal.
 * ================================================================== */

/* FUN_00074a28 @ 0x74a28  (est. sk_copy_u04_range)  stride 0x4, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74a28(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74a90) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 4 + 0x20;
        word_t end = dest + (word_t)n * 4;
        if (end <= src || src + (word_t)n * 4 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 4);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74a98) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74a94) */
}

/* FUN_00074a98 @ 0x74a98  (est. sk_copy_u40_range)  stride 0x40, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74a98(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74b00) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x40 + 0x20;
        word_t end = dest + (word_t)n * 0x40;
        if (end <= src || src + (word_t)n * 0x40 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x40);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74b08) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74b04) */
}

/* FUN_00074b08 @ 0x74b08  (est. sk_copy_u20_range)  stride 0x20, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74b08(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74b70) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x20);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74b78) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74b74) */
}

/* FUN_00074b78 @ 0x74b78  (est. sk_copy_u10_range)  stride 0x10, constructed
 * copy with move-tag FUN_00002534(0x64e668, 0x4c04c0).
 * Confidence: high (structural) */
static word_t sk_copy17_74b78(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74c0c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            word_t tag = FUN_00002534(0x64e668, 0x4c04c0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74c14) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74c10) */
}

/* FUN_00074c14 @ 0x74c14  (est. sk_copy_u28_range)  stride 0x28, constructed
 * copy with move-tag FUN_00002534(0x64e8a8, 0x4c0700).
 * Confidence: high (structural) */
static word_t sk_copy17_74c14(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74cb0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            word_t tag = FUN_00002534(0x64e8a8, 0x4c0700);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74cb8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74cb4) */
}

/* FUN_00074cb8 @ 0x74cb8  (est. sk_copy_u10_range2)  stride 0x10, constructed
 * copy with move-tag FUN_00002534(0x64e6a0, 0x4c04f0).
 * Confidence: high (structural) */
static word_t sk_copy17_74cb8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74d4c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            word_t tag = FUN_00002534(0x64e6a0, 0x4c04f0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74d54) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74d50) */
}

/* FUN_00074d54 @ 0x74d54  (est. sk_copy_u08_range)  stride 0x8, constructed
 * copy with fixed move-tag 0x662bc0.
 * Confidence: high (structural) */
static word_t sk_copy17_74d54(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74dc0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x662bc0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74dc8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74dc4) */
}

/* FUN_00074dc8 @ 0x74dc8  (est. sk_copy_u01_range)  stride 0x1, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74dc8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74e2c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from + 0x20;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74e34) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74e30) */
}

/* FUN_00074e34 @ 0x74e34  (est. sk_copy_u18_range)  stride 0x18, constructed
 * copy with fixed move-tag 0x667430.
 * Confidence: high (structural) */
static word_t sk_copy17_74e34(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74ea8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x667430);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74eb0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74eac) */
}

/* FUN_00074eb0 @ 0x74eb0  (est. sk_copy_uf8_range)  stride 0xf8, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74eb0(long from, long to, word_t dest, long container)
{
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74f20) */
    if (to - from >= 0) {
        word_t src = (word_t)container + (word_t)from * 0xf8 + 0x20;
        long n = (to - from) * 0xf8;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74f28) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74f24) */
}

/* FUN_00074f28 @ 0x74f28  (est. sk_copy_u50_range)  stride 0x50, constructed
 * copy with fixed move-tag 0x6601e8.
 * Confidence: high (structural) */
static word_t sk_copy17_74f28(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74f9c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x50 + 0x20;
        word_t end = dest + (word_t)n * 0x50;
        if (end <= src || src + (word_t)n * 0x50 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x6601e8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74fa4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74fa0) */
}

/* FUN_00074fa4 @ 0x74fa4  (est. sk_copy_u40_range2)  stride 0x40, constructed
 * copy with fixed move-tag 0x6619c0.
 * Confidence: high (structural) */
static word_t sk_copy17_74fa4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75010) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x40 + 0x20;
        word_t end = dest + (word_t)n * 0x40;
        if (end <= src || src + (word_t)n * 0x40 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x6619c0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75018) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75014) */
}

/* FUN_00075018 @ 0x75018  (est. sk_copy_u50_range2)  stride 0x50, constructed
 * copy with move-tag FUN_00002534(0x64e840, 0x4c1930).
 * Confidence: high (structural) */
static word_t sk_copy17_75018(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x750b4) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x50 + 0x20;
        word_t end = dest + (word_t)n * 0x50;
        if (end <= src || src + (word_t)n * 0x50 <= dest) {
            word_t tag = FUN_00002534(0x64e840, 0x4c1930);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x750bc) */
    }
    CL4_FATAL();                                        /* SBP(1,0x750b8) */
}

/* FUN_000750bc @ 0x750bc  (est. sk_copy_u08_move_range)  stride 0x8, move
 * variant: uses the move helper FUN_000777c4(from, container+from*8+0x20) and
 * then verifies the destination covers the moved run (FUN_00077860) before
 * releasing.  Fatal 0x75110/0x75118/0x75114.
 * Confidence: medium (structural; move-helper semantics inferred) */
static void sk_copy17_750bc(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75110) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4(from, (word_t)container + from * 8 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x75118) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75114) */
}

/* FUN_00075118 @ 0x75118  (est. sk_copy_u08_range3)  stride 0x8, constructed
 * copy with move-tag FUN_00002534(0x64e810, 0x4c0668).
 * Confidence: high (structural) */
static word_t sk_copy17_75118(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x751ac) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            word_t tag = FUN_00002534(0x64e810, 0x4c0668);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x751b4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x751b0) */
}

/* FUN_000751b4 @ 0x751b4  (est. sk_copy_u18_size_probe)  stride 0x18, uses the
 * size-probe helper FUN_00077888 to derive the source base, then constructed-
 * copy via FUN_00077910/FUN_000776e4 and release.  Fatal 0x7522c/0x75234/0x75230.
 * Confidence: medium (structural) */
static word_t sk_copy17_751b4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7522c) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75234) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75230) */
}

/* FUN_00075234 @ 0x75234  (est. sk_copy_u02_range)  stride 0x2, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75234(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7529c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 2 + 0x20;
        word_t end = dest + (word_t)n * 2;
        if (end <= src || src + (word_t)n * 2 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 2);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x752a4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x752a0) */
}

/* FUN_000752a4 @ 0x752a4  (est. sk_copy_u38_range)  stride 0x38, constructed
 * copy with move-tag FUN_00002534(0x64e7e8, 0x4c0640).
 * Confidence: high (structural) */
static word_t sk_copy17_752a4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75344) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x38 + 0x20;
        word_t end = dest + (word_t)n * 0x38;
        if (end <= src || src + (word_t)n * 0x38 <= dest) {
            word_t tag = FUN_00002534(0x64e7e8, 0x4c0640);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7534c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75348) */
}

/* FUN_0007534c @ 0x7534c  (est. sk_copy_u10_range3)  stride 0x10, constructed
 * copy with fixed move-tag 0x660f48.
 * Confidence: high (structural) */
static word_t sk_copy17_7534c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x753b8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660f48);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x753c0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x753bc) */
}

/* FUN_000753c0 @ 0x753c0  (est. sk_copy_u28_range2)  stride 0x28, constructed
 * copy with fixed move-tag 0x660e40.
 * Confidence: high (structural) */
static word_t sk_copy17_753c0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75434) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660e40);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7543c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75438) */
}

/* FUN_0007543c @ 0x7543c  (est. sk_copy_u10_range4)  stride 0x10, constructed
 * copy with fixed move-tag 0x660ec8.
 * Confidence: high (structural) */
static word_t sk_copy17_7543c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x754a8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660ec8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x754b0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x754ac) */
}

/* FUN_000754b0 @ 0x754b0  (est. sk_copy_u18_range2)  stride 0x18, constructed
 * copy with fixed move-tag 0x660fc8.
 * Confidence: high (structural) */
static word_t sk_copy17_754b0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75524) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660fc8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7552c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75528) */
}

/* FUN_0007552c @ 0x7552c  (est. sk_copy_u38_range2)  stride 0x38, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_7552c(long from, long to, word_t dest, long container)
{
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7559c) */
    if (to - from >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x38 + 0x20;
        long n = (to - from) * 0x38;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x755a4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x755a0) */
}

/* FUN_000755a4 @ 0x755a4  (est. sk_copy_u58_range)  stride 0x58, constructed
 * copy with fixed move-tag 0x660390.
 * Confidence: high (structural) */
static word_t sk_copy17_755a4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7561c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x58 + 0x20;
        word_t end = dest + (word_t)n * 0x58;
        if (end <= src || src + (word_t)n * 0x58 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660390);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75624) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75620) */
}

/* FUN_00075624 @ 0x75624  (est. sk_copy_u10_range5)  stride 0x10, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75624(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7568c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x10);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75694) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75690) */
}

/* FUN_00075694 @ 0x75694  (est. sk_copy_u48_range)  stride 0x48, constructed
 * copy with fixed move-tag 0x661ae0.
 * Confidence: high (structural) */
static word_t sk_copy17_75694(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75708) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x48 + 0x20;
        word_t end = dest + (word_t)n * 0x48;
        if (end <= src || src + (word_t)n * 0x48 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x661ae0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75710) */
    }
    CL4_FATAL();                                        /* SBP(1,0x7570c) */
}

/* FUN_00075710 @ 0x75710  (est. sk_copy_u20_range2)  stride 0x20, constructed
 * copy with fixed move-tag 0x65f878.
 * Confidence: high (structural) */
static word_t sk_copy17_75710(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7577c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x65f878);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75784) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75780) */
}

/* FUN_00075784 @ 0x75784  (est. sk_copy_u18_move_range)  stride 0x18, move
 * variant over n*3 elements via FUN_000777c4; Fatal 0x757e0/0x757e8/0x757e4.
 * Confidence: medium (structural) */
static void sk_copy17_75784(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x757e0) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4((to - from) * 3, from, (word_t)container + from * 0x18 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x757e8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x757e4) */
}

/* FUN_000757e8 @ 0x757e8  (est. sk_copy_u20_range3)  stride 0x20, constructed
 * copy with move-tag &LAB_00659cd8.
 * Confidence: high (structural) */
static word_t sk_copy17_757e8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75854) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, (word_t)&/*LAB_00659cd8*/ 0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7585c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75858) */
}

/* FUN_0007585c @ 0x7585c  (est. sk_copy_u28_range3)  stride 0x28, constructed
 * copy with move-tag &LAB_00659c50.
 * Confidence: high (structural) */
static word_t sk_copy17_7585c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x758d0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, (word_t)&/*LAB_00659c50*/ 0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x758d8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x758d4) */
}

/* FUN_000758d8 @ 0x758d8  (est. sk_copy_u10_range6)  stride 0x10, constructed
 * copy with an explicit move-tag argument (param_5).  Fatal 0x75940/0x75948/0x75944.
 * Confidence: high (structural) */
static word_t sk_copy17_758d8(long from, long to, word_t dest, long container,
                              word_t move_tag)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75940) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, move_tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75948) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75944) */
}

/* FUN_00075948 @ 0x75948  (est. sk_copy_u08_size_probe)  stride 0x8, uses the
 * size-probe helper FUN_00077888; Fatal 0x759b8/0x759c0/0x759bc.
 * Confidence: medium (structural) */
static word_t sk_copy17_75948(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x759b8) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x759c0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x759bc) */
}

/* FUN_000759c0 @ 0x759c0  (est. sk_copy_u10_size_probe)  stride 0x10, uses the
 * size-probe helper FUN_00077888; Fatal 0x75a30/0x75a38/0x75a34.
 * Confidence: medium (structural) */
static word_t sk_copy17_759c0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75a30) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75a38) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75a34) */
}

/* FUN_00075a38 @ 0x75a38  (est. sk_copy_u30_range)  stride 0x30, constructed
 * copy with fixed move-tag 0x661490.
 * Confidence: high (structural) */
static word_t sk_copy17_75a38(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75aac) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x30 + 0x20;
        word_t end = dest + (word_t)n * 0x30;
        if (end <= src || src + (word_t)n * 0x30 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x661490);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75ab4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75ab0) */
}

/* FUN_00075ab4 @ 0x75ab4  (est. sk_copy_u90_range)  stride 0x90, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75ab4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75b24) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x90 + 0x20;
        word_t end = dest + (word_t)n * 0x90;
        if (end <= src || src + (word_t)n * 0x90 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x90);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75b2c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75b28) */
}

/* FUN_00075b2c @ 0x75b2c  (est. sk_copy_u28_size_probe)  stride 0x28, uses the
 * size-probe helper FUN_00077888; Fatal 0x75ba4/0x75bac/0x75ba8.
 * Confidence: medium (structural) */
static word_t sk_copy17_75b2c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75ba4) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75bac) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75ba8) */
}

/* FUN_00075bac @ 0x75bac  (est. sk_copy_u30_range2)  stride 0x30, constructed
 * copy with move-tag FUN_00002534(0x64e690, 0x4c04e0).
 * Confidence: high (structural) */
static word_t sk_copy17_75bac(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75c48) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x30 + 0x20;
        word_t end = dest + (word_t)n * 0x30;
        if (end <= src || src + (word_t)n * 0x30 <= dest) {
            word_t tag = FUN_00002534(0x64e690, 0x4c04e0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75c50) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75c4c) */
}

/* FUN_00075c50 @ 0x75c50  (est. sk_copy_u28_move_range)  stride 0x28, move
 * variant over n*5 elements via FUN_000777c4; Fatal 0x75cac/0x75cb4/0x75cb0.
 * Confidence: medium (structural) */
static void sk_copy17_75c50(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75cac) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4((to - from) * 5, from, (word_t)container + from * 0x28 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x75cb4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75cb0) */
}

/* ================================================================== *
 * Vector insert / move / remove primitives.
 * These operate on a container whose element table is at this+0x30 (byte
 * array) / this+0x38 (8-byte-per-entry auxiliary array), a count at this+0x10,
 * a grow-lock tracked by FUN_00258c60 (lock-tag acquire), and a bitmap of
 * occupied slots at this+0x40.  The incoming key/value is resolved by the
 * slot-key helpers (FUN_000724cc / FUN_00072464 / FUN_0006ae9c) and the
 * typeinfo tag pair (DAT_0064xxxx, DAT_004cxxxx).  On slot collision the prior
 * occupant is moved/cleared and released; a null slot is written in place.
 * ================================================================== */

/* FUN_00075cb4 @ 0x75cb4  (est. sk_vec_insert_u08_key)
 * Insert a single 8-byte element keyed by (param_2,param_3): resolve the slot
 * via FUN_000724cc, acquire the grow lock (FUN_00258c60) with the typeinfo tag
 * pair (0x64e8e8, 0x4c0748), and on the free-slot path run the insert helper
 * FUN_00081b10; on the occupied path store the value directly into the slot
 * table at this+0x38.  Re-resolves and fatals 0x75dc8/0x75dc8 if the slot
 * shifted between the two resolves.
 * Confidence: medium */
static void sk_vec_insert_75cb4(word_t value, word_t key1, word_t key2)
{
    word_t lock = FUN_003a261c(/*this*/ 0);
    word_t thisp = /*this*/ 0;
    word_t slot = FUN_000724cc(key1, key2);
    word_t slot_idx = slot & 0xffffffff;      /* low 32 bits */
    word_t count = *(word_t *)(thisp + 0x10);
    word_t inc = (word_t)(~slot >> 32 & 1);
    if ((word_t)(count + inc) < count) CL4_FATAL();      /* SBP(1,0x75dc8) */
    {
        word_t tag = FUN_00002534(0x64e8e8, 0x4c0748);
        word_t r = FUN_00258c60(lock, count + inc, tag);
        if ((r & 1) != 0) {
            word_t slot2 = FUN_000724cc(key1, key2);
            if (((slot >> 32) & 1) != ((slot2 >> 32) & 1))
                FUN_002591b4(0x65f2f0);       /* fatal, noreturn */
            slot_idx = slot2 & 0xffffffff;
        }
    }
    if (((slot >> 32) & 1) == 0) {
        FUN_00081b10(slot_idx, key1, key2, value, thisp);
    } else {
        *(word_t *)(*(word_t *)(thisp + 0x38) + slot_idx * 8) = value;
    }
}

/* FUN_00075dd8 @ 0x75dd8  (est. sk_vec_insert_u08_move)
 * Insert a single 8-byte element (move variant): rebuild the slot key via
 * FUN_0006ae9c(FUN_000775c8, param_3) and the lock-state snapshot
 * (FUN_000775b8), acquire the grow lock (FUN_00258c60) with typeinfo pair
 * (0x64e8a0, 0x4c08c0); on the free path run the insert-move helper
 * FUN_00081b9c and retain param_3; on the occupied path store the moved
 * element directly.  Fatal 0x75e9c/0x75ea4.
 * Confidence: medium */
static void sk_vec_insert_75dd8(word_t value, word_t key1, word_t key2)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    word_t k = sk_element_probe();                      /* 775c8 */
    FUN_0006ae9c(k, key2);
    word_t st = sk_lock_state_save();                   /* 775b8 */
    word_t idx = st & 0xffffffff;
    word_t zero = 1;                                    /* x8+x9==0 marker */
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x75e9c) */
    {
        word_t tag = FUN_00002534(0x64e8a0, 0x4c08c0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_0006ae9c(sk_element_probe(), key2);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x75ea4) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081b9c();                                 /* 81b9c */
        thunk_FUN_0036b270(key2);                       /* retain */
    } else {
        *(word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8) = value;
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00075ea4 @ 0x75ea4  (est. sk_vec_insert_u10_wide)
 * Insert a 0x10-byte element (5-arg wide variant): snapshot the incoming
 * value with FUN_00077698, resolve the grow lock, rebuild the slot key via
 * FUN_000778e8, acquire with typeinfo pair (0x64e880, 0x4c06d8); on the free
 * path run the wide insert helper FUN_00081bd0 and retain both 8-byte halves;
 * on the occupied path store the first half.  Fatal 0x75fa4/0x75fa4.
 * Confidence: medium */
static void sk_vec_insert_75ea4(word_t v0, word_t v1, word_t v2,
                                word_t v3, word_t v4)
{
    word_t sv = sk_lock_state_save();                   /* 77698 */
    word_t lock = FUN_003a261c(/*this*/ 0);
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_000778e8();
    word_t idx = st & 0xffffffff;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x75fa4) */
    {
        word_t tag = FUN_00002534(0x64e880, 0x4c06d8);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            word_t st2 = FUN_000778e8();
            idx = st2 & 0xffffffff;
            if (((st >> 32) & 1) != ((st2 >> 32) & 1))
                FUN_002591b4(0x667910);                 /* fatal */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081bd0(idx, (sv >> 32), v2, v3, v4, (sv & 0xffffffff), /*this*/ 0);
        thunk_FUN_0036b270(v4);
        thunk_FUN_0036b270(v2);
    } else {
        *(word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8) = (sv & 0xffffffff);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00075fb4 @ 0x75fb4  (est. sk_vec_insert_u10_move)
 * Insert a 0x10-byte element (move variant): snapshot, rebuild the slot key,
 * acquire the grow lock (typeinfo 0x64e878, 0x4c06d0); on the free path run
 * the insert helper FUN_00081c1c; on the occupied path write the new low/high
 * halves and release the displaced token.  Fatal 0x76084/0x7608c.
 * Confidence: medium */
static void sk_vec_insert_75fb4(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_slot_release(/*this*/ 0, 0);       /* 777b4 */
    FUN_003a261c(/*this*/ 0);
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = sk_lock_state_save();                   /* 775b8 */
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76084) */
    {
        word_t tag = FUN_00002534(0x64e878, 0x4c06d0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7608c) */
        }
    }
    if ((/*w25*/ 1) == 0) {
        FUN_00081c1c(idx);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_hi = slot[1];
        slot[0] = v_lo;
        slot[1] = value_hi;
        FUN_0036b118(old_hi);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007608c @ 0x7608c  (est. sk_vec_insert_u10_token)
 * Insert a 0x10-byte token element: snapshot, resolve, acquire with typeinfo
 * pair (0x64e7a0, 0x4e7ff0); on the free path run the insert helper
 * FUN_00081c58 and retain; on the occupied path write both halves and release
 * the displaced token via FUN_003a25d4.  Fatal 0x76150/0x76158.
 * Confidence: medium */
static void sk_vec_insert_7608c(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_element_probe();                   /* 777e4 */
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_00077928();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76150) */
    {
        word_t tag = FUN_00002534(0x64e7a0, 0x4e7ff0);
        word_t r = FUN_00258c60(v_lo, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            FUN_00077928();
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x76158) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081c58();                                 /* 81c58 */
        thunk_FUN_0036b270(0);                          /* retain */
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_hi = slot[1];
        slot[0] = value_lo;
        slot[1] = value_hi;
        FUN_003a25d4(old_hi);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00076158 @ 0x76158  (est. sk_vec_insert_u20_wide)
 * Insert a 0x20-byte element (5-arg wide variant): snapshot, resolve, acquire
 * with typeinfo pair (0x64e830, 0x4c0688); on the free path run the wide
 * insert helper FUN_00081c98; on the occupied path write the four 8-byte
 * halves and release the displaced pair.  Fatal 0x7626c/0x76274.
 * Confidence: medium */
static void sk_vec_insert_76158(word_t v0, word_t v1, word_t v2, word_t v3, word_t v4)
{
    word_t sv = sk_lock_state_save();                   /* 77698 */
    word_t lock = FUN_003a261c(/*this*/ 0);
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_00072664(v4);
    word_t idx = st & 0xffffffff;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x7626c) */
    {
        word_t tag = FUN_00002534(0x64e830, 0x4c0688);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            word_t st2 = FUN_00072664(v4);
            idx = st2 & 0xffffffff;
            if (((st >> 32) & 1) != ((st2 >> 32) & 1))
                CL4_FATAL();                            /* SBP(1,0x76274) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081c98(idx, v4, (sv & 0xffffffff), (sv >> 32), v2, v3, /*this*/ 0);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x20);
        word_t old_hi = slot[1];
        word_t old_hi2 = slot[3];
        slot[0] = v0; slot[1] = v1; slot[2] = v2; slot[3] = v3;
        FUN_0036b118(old_hi);
        FUN_003a25d4(old_hi2);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

 @ 0x764c8  (est. sk_vec_insert_u08_move2)
 * Insert a single 8-byte element (move variant): rebuild the slot key via
 * FUN_0006ae9c(FUN_000775c8, param_3), acquire with typeinfo pair
 * (0x64e788, 0x4c05e0); free path runs FUN_00081b9c + retain param_3;
 * occupied path swaps the displaced token.  Fatal 0x76594/0x7659c.
 * Confidence: medium */
static void sk_vec_insert_764c8(word_t value, word_t key1, word_t key2)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    word_t k = sk_element_probe();                      /* 775c8 */
    FUN_0006ae9c(k, key2);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76594) */
    {
        word_t tag = FUN_00002534(0x64e788, 0x4c05e0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_0006ae9c(sk_element_probe(), key2);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7659c) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081b9c();                                 /* 81b9c */
        thunk_FUN_0036b270(key2);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8);
        word_t old = *slot;
        *slot = value;
        FUN_0036b118(old);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007659c @ 0x7659c  (est. sk_vec_insert_u08_wrapper3)
 * Thin wrapper forwarding to sk_vec_insert_765c4 with typeinfo pair
 * (0x64e650, 0x4c04a8) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */

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

/* ================================================================== *
 * Ranged element-copy helpers.  Each copies [from,to) elements of a fixed
 * stride out of a container into a destination range (dest).  It first
 * requires to >= from (SBORROW fatal), computes source = container +
 * from*SIZE + 0x20 and end = dest + n*SIZE, verifies the source and
 * destination ranges do not overlap, performs the copy (plain memcpy for
 * trivially-copyable elements, constructed-copy for the rest), releases the
 * container token, and returns the destination end.  Any overlap or negative
 * range is a hard fatal.
 * ================================================================== */

/* FUN_00074a28 @ 0x74a28  (est. sk_copy_u04_range)  stride 0x4, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74a28(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74a90) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 4 + 0x20;
        word_t end = dest + (word_t)n * 4;
        if (end <= src || src + (word_t)n * 4 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 4);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74a98) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74a94) */
}

/* FUN_00074a98 @ 0x74a98  (est. sk_copy_u40_range)  stride 0x40, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74a98(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74b00) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x40 + 0x20;
        word_t end = dest + (word_t)n * 0x40;
        if (end <= src || src + (word_t)n * 0x40 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x40);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74b08) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74b04) */
}

/* FUN_00074b08 @ 0x74b08  (est. sk_copy_u20_range)  stride 0x20, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74b08(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74b70) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x20);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74b78) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74b74) */
}

/* FUN_00074b78 @ 0x74b78  (est. sk_copy_u10_range)  stride 0x10, constructed
 * copy with move-tag FUN_00002534(0x64e668, 0x4c04c0).
 * Confidence: high (structural) */
static word_t sk_copy17_74b78(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74c0c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            word_t tag = FUN_00002534(0x64e668, 0x4c04c0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74c14) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74c10) */
}

/* FUN_00074c14 @ 0x74c14  (est. sk_copy_u28_range)  stride 0x28, constructed
 * copy with move-tag FUN_00002534(0x64e8a8, 0x4c0700).
 * Confidence: high (structural) */
static word_t sk_copy17_74c14(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74cb0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            word_t tag = FUN_00002534(0x64e8a8, 0x4c0700);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74cb8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74cb4) */
}

/* FUN_00074cb8 @ 0x74cb8  (est. sk_copy_u10_range2)  stride 0x10, constructed
 * copy with move-tag FUN_00002534(0x64e6a0, 0x4c04f0).
 * Confidence: high (structural) */
static word_t sk_copy17_74cb8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74d4c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            word_t tag = FUN_00002534(0x64e6a0, 0x4c04f0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74d54) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74d50) */
}

/* FUN_00074d54 @ 0x74d54  (est. sk_copy_u08_range)  stride 0x8, constructed
 * copy with fixed move-tag 0x662bc0.
 * Confidence: high (structural) */
static word_t sk_copy17_74d54(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74dc0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x662bc0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74dc8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74dc4) */
}

/* FUN_00074dc8 @ 0x74dc8  (est. sk_copy_u01_range)  stride 0x1, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74dc8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74e2c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from + 0x20;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74e34) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74e30) */
}

/* FUN_00074e34 @ 0x74e34  (est. sk_copy_u18_range)  stride 0x18, constructed
 * copy with fixed move-tag 0x667430.
 * Confidence: high (structural) */
static word_t sk_copy17_74e34(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74ea8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x667430);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74eb0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74eac) */
}

/* FUN_00074eb0 @ 0x74eb0  (est. sk_copy_uf8_range)  stride 0xf8, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_74eb0(long from, long to, word_t dest, long container)
{
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74f20) */
    if (to - from >= 0) {
        word_t src = (word_t)container + (word_t)from * 0xf8 + 0x20;
        long n = (to - from) * 0xf8;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74f28) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74f24) */
}

/* FUN_00074f28 @ 0x74f28  (est. sk_copy_u50_range)  stride 0x50, constructed
 * copy with fixed move-tag 0x6601e8.
 * Confidence: high (structural) */
static word_t sk_copy17_74f28(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x74f9c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x50 + 0x20;
        word_t end = dest + (word_t)n * 0x50;
        if (end <= src || src + (word_t)n * 0x50 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x6601e8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x74fa4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x74fa0) */
}

/* FUN_00074fa4 @ 0x74fa4  (est. sk_copy_u40_range2)  stride 0x40, constructed
 * copy with fixed move-tag 0x6619c0.
 * Confidence: high (structural) */
static word_t sk_copy17_74fa4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75010) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x40 + 0x20;
        word_t end = dest + (word_t)n * 0x40;
        if (end <= src || src + (word_t)n * 0x40 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x6619c0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75018) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75014) */
}

/* FUN_00075018 @ 0x75018  (est. sk_copy_u50_range2)  stride 0x50, constructed
 * copy with move-tag FUN_00002534(0x64e840, 0x4c1930).
 * Confidence: high (structural) */
static word_t sk_copy17_75018(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x750b4) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x50 + 0x20;
        word_t end = dest + (word_t)n * 0x50;
        if (end <= src || src + (word_t)n * 0x50 <= dest) {
            word_t tag = FUN_00002534(0x64e840, 0x4c1930);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x750bc) */
    }
    CL4_FATAL();                                        /* SBP(1,0x750b8) */
}

/* FUN_000750bc @ 0x750bc  (est. sk_copy_u08_move_range)  stride 0x8, move
 * variant: uses the move helper FUN_000777c4(from, container+from*8+0x20) and
 * then verifies the destination covers the moved run (FUN_00077860) before
 * releasing.  Fatal 0x75110/0x75118/0x75114.
 * Confidence: medium (structural; move-helper semantics inferred) */
static void sk_copy17_750bc(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75110) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4(from, (word_t)container + from * 8 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x75118) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75114) */
}

/* FUN_00075118 @ 0x75118  (est. sk_copy_u08_range3)  stride 0x8, constructed
 * copy with move-tag FUN_00002534(0x64e810, 0x4c0668).
 * Confidence: high (structural) */
static word_t sk_copy17_75118(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x751ac) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            word_t tag = FUN_00002534(0x64e810, 0x4c0668);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x751b4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x751b0) */
}

/* FUN_000751b4 @ 0x751b4  (est. sk_copy_u18_size_probe)  stride 0x18, uses the
 * size-probe helper FUN_00077888 to derive the source base, then constructed-
 * copy via FUN_00077910/FUN_000776e4 and release.  Fatal 0x7522c/0x75234/0x75230.
 * Confidence: medium (structural) */
static word_t sk_copy17_751b4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7522c) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75234) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75230) */
}

/* FUN_00075234 @ 0x75234  (est. sk_copy_u02_range)  stride 0x2, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75234(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7529c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 2 + 0x20;
        word_t end = dest + (word_t)n * 2;
        if (end <= src || src + (word_t)n * 2 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 2);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x752a4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x752a0) */
}

/* FUN_000752a4 @ 0x752a4  (est. sk_copy_u38_range)  stride 0x38, constructed
 * copy with move-tag FUN_00002534(0x64e7e8, 0x4c0640).
 * Confidence: high (structural) */
static word_t sk_copy17_752a4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75344) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x38 + 0x20;
        word_t end = dest + (word_t)n * 0x38;
        if (end <= src || src + (word_t)n * 0x38 <= dest) {
            word_t tag = FUN_00002534(0x64e7e8, 0x4c0640);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7534c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75348) */
}

/* FUN_0007534c @ 0x7534c  (est. sk_copy_u10_range3)  stride 0x10, constructed
 * copy with fixed move-tag 0x660f48.
 * Confidence: high (structural) */
static word_t sk_copy17_7534c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x753b8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660f48);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x753c0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x753bc) */
}

/* FUN_000753c0 @ 0x753c0  (est. sk_copy_u28_range2)  stride 0x28, constructed
 * copy with fixed move-tag 0x660e40.
 * Confidence: high (structural) */
static word_t sk_copy17_753c0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75434) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660e40);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7543c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75438) */
}

/* FUN_0007543c @ 0x7543c  (est. sk_copy_u10_range4)  stride 0x10, constructed
 * copy with fixed move-tag 0x660ec8.
 * Confidence: high (structural) */
static word_t sk_copy17_7543c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x754a8) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660ec8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x754b0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x754ac) */
}

/* FUN_000754b0 @ 0x754b0  (est. sk_copy_u18_range2)  stride 0x18, constructed
 * copy with fixed move-tag 0x660fc8.
 * Confidence: high (structural) */
static word_t sk_copy17_754b0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75524) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x18 + 0x20;
        word_t end = dest + (word_t)n * 0x18;
        if (end <= src || src + (word_t)n * 0x18 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660fc8);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7552c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75528) */
}

/* FUN_0007552c @ 0x7552c  (est. sk_copy_u38_range2)  stride 0x38, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_7552c(long from, long to, word_t dest, long container)
{
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7559c) */
    if (to - from >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x38 + 0x20;
        long n = (to - from) * 0x38;
        word_t end = dest + (word_t)n;
        if (end <= src || src + (word_t)n <= dest) {
            FUN_00117cc4(dest, src, (word_t)n);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x755a4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x755a0) */
}

/* FUN_000755a4 @ 0x755a4  (est. sk_copy_u58_range)  stride 0x58, constructed
 * copy with fixed move-tag 0x660390.
 * Confidence: high (structural) */
static word_t sk_copy17_755a4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7561c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x58 + 0x20;
        word_t end = dest + (word_t)n * 0x58;
        if (end <= src || src + (word_t)n * 0x58 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x660390);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75624) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75620) */
}

/* FUN_00075624 @ 0x75624  (est. sk_copy_u10_range5)  stride 0x10, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75624(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7568c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x10);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75694) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75690) */
}

/* FUN_00075694 @ 0x75694  (est. sk_copy_u48_range)  stride 0x48, constructed
 * copy with fixed move-tag 0x661ae0.
 * Confidence: high (structural) */
static word_t sk_copy17_75694(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75708) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x48 + 0x20;
        word_t end = dest + (word_t)n * 0x48;
        if (end <= src || src + (word_t)n * 0x48 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x661ae0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75710) */
    }
    CL4_FATAL();                                        /* SBP(1,0x7570c) */
}

/* FUN_00075710 @ 0x75710  (est. sk_copy_u20_range2)  stride 0x20, constructed
 * copy with fixed move-tag 0x65f878.
 * Confidence: high (structural) */
static word_t sk_copy17_75710(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x7577c) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x65f878);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75784) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75780) */
}

/* FUN_00075784 @ 0x75784  (est. sk_copy_u18_move_range)  stride 0x18, move
 * variant over n*3 elements via FUN_000777c4; Fatal 0x757e0/0x757e8/0x757e4.
 * Confidence: medium (structural) */
static void sk_copy17_75784(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x757e0) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4((to - from) * 3, from, (word_t)container + from * 0x18 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x757e8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x757e4) */
}

/* FUN_000757e8 @ 0x757e8  (est. sk_copy_u20_range3)  stride 0x20, constructed
 * copy with move-tag &LAB_00659cd8.
 * Confidence: high (structural) */
static word_t sk_copy17_757e8(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75854) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x20 + 0x20;
        word_t end = dest + (word_t)n * 0x20;
        if (end <= src || src + (word_t)n * 0x20 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, (word_t)&/*LAB_00659cd8*/ 0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x7585c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75858) */
}

/* FUN_0007585c @ 0x7585c  (est. sk_copy_u28_range3)  stride 0x28, constructed
 * copy with move-tag &LAB_00659c50.
 * Confidence: high (structural) */
static word_t sk_copy17_7585c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x758d0) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, (word_t)&/*LAB_00659c50*/ 0);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x758d8) */
    }
    CL4_FATAL();                                        /* SBP(1,0x758d4) */
}

/* FUN_000758d8 @ 0x758d8  (est. sk_copy_u10_range6)  stride 0x10, constructed
 * copy with an explicit move-tag argument (param_5).  Fatal 0x75940/0x75948/0x75944.
 * Confidence: high (structural) */
static word_t sk_copy17_758d8(long from, long to, word_t dest, long container,
                              word_t move_tag)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75940) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, move_tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75948) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75944) */
}

/* FUN_00075948 @ 0x75948  (est. sk_copy_u08_size_probe)  stride 0x8, uses the
 * size-probe helper FUN_00077888; Fatal 0x759b8/0x759c0/0x759bc.
 * Confidence: medium (structural) */
static word_t sk_copy17_75948(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x759b8) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 8 + 0x20;
        word_t end = dest + (word_t)n * 8;
        if (end <= src || src + (word_t)n * 8 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x759c0) */
    }
    CL4_FATAL();                                        /* SBP(1,0x759bc) */
}

/* FUN_000759c0 @ 0x759c0  (est. sk_copy_u10_size_probe)  stride 0x10, uses the
 * size-probe helper FUN_00077888; Fatal 0x75a30/0x75a38/0x75a34.
 * Confidence: medium (structural) */
static word_t sk_copy17_759c0(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75a30) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x10 + 0x20;
        word_t end = dest + (word_t)n * 0x10;
        if (end <= src || src + (word_t)n * 0x10 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75a38) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75a34) */
}

/* FUN_00075a38 @ 0x75a38  (est. sk_copy_u30_range)  stride 0x30, constructed
 * copy with fixed move-tag 0x661490.
 * Confidence: high (structural) */
static word_t sk_copy17_75a38(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75aac) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x30 + 0x20;
        word_t end = dest + (word_t)n * 0x30;
        if (end <= src || src + (word_t)n * 0x30 <= dest) {
            FUN_0035b67c(dest, src, (word_t)n, 0x661490);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75ab4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75ab0) */
}

/* FUN_00075ab4 @ 0x75ab4  (est. sk_copy_u90_range)  stride 0x90, memcpy.
 * Confidence: high (structural) */
static word_t sk_copy17_75ab4(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75b24) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x90 + 0x20;
        word_t end = dest + (word_t)n * 0x90;
        if (end <= src || src + (word_t)n * 0x90 <= dest) {
            FUN_00117cc4(dest, src, (word_t)n * 0x90);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75b2c) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75b28) */
}

/* FUN_00075b2c @ 0x75b2c  (est. sk_copy_u28_size_probe)  stride 0x28, uses the
 * size-probe helper FUN_00077888; Fatal 0x75ba4/0x75bac/0x75ba8.
 * Confidence: medium (structural) */
static word_t sk_copy17_75b2c(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75ba4) */
    if (n >= 0) {
        long probe = FUN_00077888();
        word_t src = (word_t)container + (word_t)probe * 0x28 + 0x20;
        word_t end = dest + (word_t)n * 0x28;
        if (end <= src || src + (word_t)n * 0x28 <= dest) {
            FUN_00077910();
            FUN_000776e4();
            FUN_0036b118(0);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75bac) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75ba8) */
}

/* FUN_00075bac @ 0x75bac  (est. sk_copy_u30_range2)  stride 0x30, constructed
 * copy with move-tag FUN_00002534(0x64e690, 0x4c04e0).
 * Confidence: high (structural) */
static word_t sk_copy17_75bac(long from, long to, word_t dest, long container)
{
    long n = to - from;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75c48) */
    if (n >= 0) {
        word_t src = (word_t)container + (word_t)from * 0x30 + 0x20;
        word_t end = dest + (word_t)n * 0x30;
        if (end <= src || src + (word_t)n * 0x30 <= dest) {
            word_t tag = FUN_00002534(0x64e690, 0x4c04e0);
            FUN_0035b67c(dest, src, (word_t)n, tag);
            FUN_0036b118(container);
            return end;
        }
        CL4_FATAL();                                    /* SBP(1,0x75c50) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75c4c) */
}

/* FUN_00075c50 @ 0x75c50  (est. sk_copy_u28_move_range)  stride 0x28, move
 * variant over n*5 elements via FUN_000777c4; Fatal 0x75cac/0x75cb4/0x75cb0.
 * Confidence: medium (structural) */
static void sk_copy17_75c50(word_t from, word_t to, word_t dest, long container)
{
    bool ok = from <= to;
    if ((word_t)to < (word_t)from) CL4_FATAL();         /* SBP(1,0x75cac) */
    if ((long)(to - from) >= 0) {
        FUN_000777c4((to - from) * 5, from, (word_t)container + from * 0x28 + 0x20);
        if (ok || /*extraout_x9*/ 0 <= dest) {
            FUN_00077860(/*move*/ 0, 0, 0, 0);
            FUN_0036b118(container);
            return;
        }
        CL4_FATAL();                                    /* SBP(1,0x75cb4) */
    }
    CL4_FATAL();                                        /* SBP(1,0x75cb0) */
}

/* ================================================================== *
 * Vector insert / move / remove primitives.
 * These operate on a container whose element table is at this+0x30 (byte
 * array) / this+0x38 (8-byte-per-entry auxiliary array), a count at this+0x10,
 * a grow-lock tracked by FUN_00258c60 (lock-tag acquire), and a bitmap of
 * occupied slots at this+0x40.  The incoming key/value is resolved by the
 * slot-key helpers (FUN_000724cc / FUN_00072464 / FUN_0006ae9c) and the
 * typeinfo tag pair (DAT_0064xxxx, DAT_004cxxxx).  On slot collision the prior
 * occupant is moved/cleared and released; a null slot is written in place.
 * ================================================================== */

/* FUN_00075cb4 @ 0x75cb4  (est. sk_vec_insert_u08_key)
 * Insert a single 8-byte element keyed by (param_2,param_3): resolve the slot
 * via FUN_000724cc, acquire the grow lock (FUN_00258c60) with the typeinfo tag
 * pair (0x64e8e8, 0x4c0748), and on the free-slot path run the insert helper
 * FUN_00081b10; on the occupied path store the value directly into the slot
 * table at this+0x38.  Re-resolves and fatals 0x75dc8/0x75dc8 if the slot
 * shifted between the two resolves.
 * Confidence: medium */
static void sk_vec_insert_75cb4(word_t value, word_t key1, word_t key2)
{
    word_t lock = FUN_003a261c(/*this*/ 0);
    word_t thisp = /*this*/ 0;
    word_t slot = FUN_000724cc(key1, key2);
    word_t slot_idx = slot & 0xffffffff;      /* low 32 bits */
    word_t count = *(word_t *)(thisp + 0x10);
    word_t inc = (word_t)(~slot >> 32 & 1);
    if ((word_t)(count + inc) < count) CL4_FATAL();      /* SBP(1,0x75dc8) */
    {
        word_t tag = FUN_00002534(0x64e8e8, 0x4c0748);
        word_t r = FUN_00258c60(lock, count + inc, tag);
        if ((r & 1) != 0) {
            word_t slot2 = FUN_000724cc(key1, key2);
            if (((slot >> 32) & 1) != ((slot2 >> 32) & 1))
                FUN_002591b4(0x65f2f0);       /* fatal, noreturn */
            slot_idx = slot2 & 0xffffffff;
        }
    }
    if (((slot >> 32) & 1) == 0) {
        FUN_00081b10(slot_idx, key1, key2, value, thisp);
    } else {
        *(word_t *)(*(word_t *)(thisp + 0x38) + slot_idx * 8) = value;
    }
}

/* FUN_00075dd8 @ 0x75dd8  (est. sk_vec_insert_u08_move)
 * Insert a single 8-byte element (move variant): rebuild the slot key via
 * FUN_0006ae9c(FUN_000775c8, param_3) and the lock-state snapshot
 * (FUN_000775b8), acquire the grow lock (FUN_00258c60) with typeinfo pair
 * (0x64e8a0, 0x4c08c0); on the free path run the insert-move helper
 * FUN_00081b9c and retain param_3; on the occupied path store the moved
 * element directly.  Fatal 0x75e9c/0x75ea4.
 * Confidence: medium */
static void sk_vec_insert_75dd8(word_t value, word_t key1, word_t key2)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    word_t k = sk_element_probe();                      /* 775c8 */
    FUN_0006ae9c(k, key2);
    word_t st = sk_lock_state_save();                   /* 775b8 */
    word_t idx = st & 0xffffffff;
    word_t zero = 1;                                    /* x8+x9==0 marker */
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x75e9c) */
    {
        word_t tag = FUN_00002534(0x64e8a0, 0x4c08c0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_0006ae9c(sk_element_probe(), key2);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x75ea4) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081b9c();                                 /* 81b9c */
        thunk_FUN_0036b270(key2);                       /* retain */
    } else {
        *(word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8) = value;
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00075ea4 @ 0x75ea4  (est. sk_vec_insert_u10_wide)
 * Insert a 0x10-byte element (5-arg wide variant): snapshot the incoming
 * value with FUN_00077698, resolve the grow lock, rebuild the slot key via
 * FUN_000778e8, acquire with typeinfo pair (0x64e880, 0x4c06d8); on the free
 * path run the wide insert helper FUN_00081bd0 and retain both 8-byte halves;
 * on the occupied path store the first half.  Fatal 0x75fa4/0x75fa4.
 * Confidence: medium */
static void sk_vec_insert_75ea4(word_t v0, word_t v1, word_t v2,
                                word_t v3, word_t v4)
{
    word_t sv = sk_lock_state_save();                   /* 77698 */
    word_t lock = FUN_003a261c(/*this*/ 0);
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_000778e8();
    word_t idx = st & 0xffffffff;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x75fa4) */
    {
        word_t tag = FUN_00002534(0x64e880, 0x4c06d8);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            word_t st2 = FUN_000778e8();
            idx = st2 & 0xffffffff;
            if (((st >> 32) & 1) != ((st2 >> 32) & 1))
                FUN_002591b4(0x667910);                 /* fatal */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081bd0(idx, (sv >> 32), v2, v3, v4, (sv & 0xffffffff), /*this*/ 0);
        thunk_FUN_0036b270(v4);
        thunk_FUN_0036b270(v2);
    } else {
        *(word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8) = (sv & 0xffffffff);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00075fb4 @ 0x75fb4  (est. sk_vec_insert_u10_move)
 * Insert a 0x10-byte element (move variant): snapshot, rebuild the slot key,
 * acquire the grow lock (typeinfo 0x64e878, 0x4c06d0); on the free path run
 * the insert helper FUN_00081c1c; on the occupied path write the new low/high
 * halves and release the displaced token.  Fatal 0x76084/0x7608c.
 * Confidence: medium */
static void sk_vec_insert_75fb4(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_slot_release(/*this*/ 0, 0);       /* 777b4 */
    FUN_003a261c(/*this*/ 0);
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = sk_lock_state_save();                   /* 775b8 */
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76084) */
    {
        word_t tag = FUN_00002534(0x64e878, 0x4c06d0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7608c) */
        }
    }
    if ((/*w25*/ 1) == 0) {
        FUN_00081c1c(idx);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_hi = slot[1];
        slot[0] = v_lo;
        slot[1] = value_hi;
        FUN_0036b118(old_hi);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007608c @ 0x7608c  (est. sk_vec_insert_u10_token)
 * Insert a 0x10-byte token element: snapshot, resolve, acquire with typeinfo
 * pair (0x64e7a0, 0x4e7ff0); on the free path run the insert helper
 * FUN_00081c58 and retain; on the occupied path write both halves and release
 * the displaced token via FUN_003a25d4.  Fatal 0x76150/0x76158.
 * Confidence: medium */
static void sk_vec_insert_7608c(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_element_probe();                   /* 777e4 */
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_00077928();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76150) */
    {
        word_t tag = FUN_00002534(0x64e7a0, 0x4e7ff0);
        word_t r = FUN_00258c60(v_lo, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            FUN_00077928();
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x76158) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081c58();                                 /* 81c58 */
        thunk_FUN_0036b270(0);                          /* retain */
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_hi = slot[1];
        slot[0] = value_lo;
        slot[1] = value_hi;
        FUN_003a25d4(old_hi);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_00076158 @ 0x76158  (est. sk_vec_insert_u20_wide)
 * Insert a 0x20-byte element (5-arg wide variant): snapshot, resolve, acquire
 * with typeinfo pair (0x64e830, 0x4c0688); on the free path run the wide
 * insert helper FUN_00081c98; on the occupied path write the four 8-byte
 * halves and release the displaced pair.  Fatal 0x7626c/0x76274.
 * Confidence: medium */
static void sk_vec_insert_76158(word_t v0, word_t v1, word_t v2, word_t v3, word_t v4)
{
    word_t sv = sk_lock_state_save();                   /* 77698 */
    word_t lock = FUN_003a261c(/*this*/ 0);
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    word_t st = FUN_00072664(v4);
    word_t idx = st & 0xffffffff;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x7626c) */
    {
        word_t tag = FUN_00002534(0x64e830, 0x4c0688);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            word_t st2 = FUN_00072664(v4);
            idx = st2 & 0xffffffff;
            if (((st >> 32) & 1) != ((st2 >> 32) & 1))
                CL4_FATAL();                            /* SBP(1,0x76274) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081c98(idx, v4, (sv & 0xffffffff), (sv >> 32), v2, v3, /*this*/ 0);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x20);
        word_t old_hi = slot[1];
        word_t old_hi2 = slot[3];
        slot[0] = v0; slot[1] = v1; slot[2] = v2; slot[3] = v3;
        FUN_0036b118(old_hi);
        FUN_003a25d4(old_hi2);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

 @ 0x764c8  (est. sk_vec_insert_u08_move2)
 * Insert a single 8-byte element (move variant): rebuild the slot key via
 * FUN_0006ae9c(FUN_000775c8, param_3), acquire with typeinfo pair
 * (0x64e788, 0x4c05e0); free path runs FUN_00081b9c + retain param_3;
 * occupied path swaps the displaced token.  Fatal 0x76594/0x7659c.
 * Confidence: medium */
static void sk_vec_insert_764c8(word_t value, word_t key1, word_t key2)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    word_t k = sk_element_probe();                      /* 775c8 */
    FUN_0006ae9c(k, key2);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76594) */
    {
        word_t tag = FUN_00002534(0x64e788, 0x4c05e0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_0006ae9c(sk_element_probe(), key2);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7659c) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00081b9c();                                 /* 81b9c */
        thunk_FUN_0036b270(key2);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8);
        word_t old = *slot;
        *slot = value;
        FUN_0036b118(old);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007659c @ 0x7659c  (est. sk_vec_insert_u08_wrapper3)
 * Thin wrapper forwarding to sk_vec_insert_765c4 with typeinfo pair
 * (0x64e650, 0x4c04a8) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */


/* FUN_00076274 @ 0x76274  (est. sk_vec_insert_u08_wrapperA)
 * Thin wrapper forwarding to sk_vec_insert_76918 with typeinfo pair
 * (0x64e828, 0x4c0680) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */
static void sk_vec_insert_76274(word_t a, word_t b)
{
    FUN_00076918(a, b, 0x64e828, 0x4c0680, (word_t)thunk_FUN_00081ce8);
}

/* FUN_000764a0 @ 0x764a0  (est. sk_vec_insert_u08_wrapperB)
 * Thin wrapper forwarding to sk_vec_insert_765c4 with typeinfo pair
 * (0x64e780, 0x4c05d8) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */
static void sk_vec_insert_764a0(word_t a, word_t b)
{
    FUN_000765c4(a, b, 0x64e780, 0x4c05d8, (word_t)thunk_FUN_00081ce8);
}

/* FUN_0007659c @ 0x7659c  (est. sk_vec_insert_u08_wrapperC)
 * Thin wrapper forwarding to sk_vec_insert_765c4 with typeinfo pair
 * (0x64e650, 0x4c04a8) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */
static void sk_vec_insert_7659c(word_t a, word_t b)
{
    FUN_000765c4(a, b, 0x64e650, 0x4c04a8, (word_t)thunk_FUN_00081ce8);
}

/* FUN_000765c4 @ 0x765c4  (est. sk_vec_insert_u08_workhorse)
 * The shared 8-byte element insert core.  Snapshot the lock state, resolve
 * the slot key, acquire the grow lock (FUN_00258c60) with the caller-supplied
 * typeinfo pair, then on the free path invoke the caller-supplied element-move
 * thunk (`in_stack_00000000`); on the occupied path store the moved element
 * into the slot table (this+0x38 + idx*8), releasing the displaced token.
 * Fatal 0x76674/0x7667c on count overflow.
 * Confidence: medium */
static void sk_vec_insert_765c4(word_t a, word_t b, word_t t1, word_t t2,
                                word_t move_thunk)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 77794 */
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76674) */
    {
        word_t tag = FUN_00002534(t1, t2);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7667c) */
        }
    }
    if ((/*w25*/ 1) == 0) {
        ((void (*)(word_t))move_thunk)(idx);
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8);
        word_t old = *slot;
        *slot = /*unaff_x22*/ b;
        FUN_0036b118(old);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007667c @ 0x7667c  (est. sk_vec_insert_u08_token)
 * Insert a single 8-byte token element: snapshot, resolve, acquire with
 * typeinfo pair (0x64e680, 0x4c04d0); free path runs the insert helper
 * FUN_00081d14; occupied path runs FUN_000774c8 (store+release pair).
 * Fatal 0x76758/0x76760.
 * Confidence: medium */
static void sk_vec_insert_7667c(word_t value)
{
    word_t lock = FUN_000778c0();
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76758) */
    {
        word_t tag = FUN_00002534(0x64e680, 0x4c04d0);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x76760) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00077894(idx);
        FUN_00081d14();
    } else {
        sk_vec_insert_774c8(value, 0);
    }
}

/* FUN_00076760 @ 0x76760  (est. sk_vec_insert_u10_move)
 * Insert a 0x10-byte element (move variant): snapshot, resolve, acquire with
 * typeinfo pair (0x64e778, 0x4c05d0); free path runs FUN_00081d60; occupied
 * path writes both halves and releases the displaced pair.
 * Fatal 0x76824/0x7682c.
 * Confidence: medium */
static void sk_vec_insert_76760(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_slot_release(/*this*/ 0, 0);       /* 777b4 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76824) */
    {
        word_t tag = FUN_00002534(0x64e778, 0x4c05d0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x7682c) */
        }
    }
    if ((/*w25*/ 1) == 0) {
        FUN_00081d60();                                 /* 81d60 */
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_lo = slot[0];
        word_t old_hi = slot[1];
        slot[0] = value_lo;
        slot[1] = value_hi;
        FUN_0036b118(old_hi);
        FUN_0036b118(old_lo);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_0007682c @ 0x7682c  (est. sk_vec_insert_u10_token)
 * Insert a 0x10-byte token element: snapshot, resolve, acquire with typeinfo
 * pair (0x64e688, 0x4c25c0); free path runs FUN_00081d60; occupied path
 * writes both halves and releases the displaced token via FUN_003a25d4.
 * Fatal 0x768e8/0x768f0.
 * Confidence: medium */
static void sk_vec_insert_7682c(word_t value_lo, word_t value_hi)
{
    sk_lock_state_enter();                              /* 77698 */
    word_t v_lo = sk_slot_release(/*this*/ 0, 0);       /* 777b4 */
    sk_slot_release(/*this*/ 0, 0);                     /* 7783c */
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x768e8) */
    {
        word_t tag = FUN_00002534(0x64e688, 0x4c25c0);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 77604 */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x768f0) */
        }
    }
    if ((/*w25*/ 1) == 0) {
        FUN_00081d60();                                 /* 81d60 */
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x10);
        word_t old_hi = slot[1];
        slot[0] = value_lo;
        slot[1] = value_hi;
        FUN_003a25d4(old_hi);
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_000768f0 @ 0x768f0  (est. sk_vec_insert_u08_wrapperD)
 * Thin wrapper forwarding to sk_vec_insert_76918 with typeinfo pair
 * (0x64e798, 0x4c05f0) and the element-move thunk FUN_00081ce8.
 * Confidence: high (single call) */
static void sk_vec_insert_768f0(word_t a, word_t b)
{
    FUN_00076918(a, b, 0x64e798, 0x4c05f0, (word_t)thunk_FUN_00081ce8);
}

/* FUN_00076918 @ 0x76918  (est. sk_vec_insert_u08_workhorse2)
 * The shared 8-byte element insert core (2nd shape).  Snapshot the lock state,
 * resolve the slot key, acquire the grow lock (FUN_00258c60) with the
 * caller-supplied typeinfo pair, then on the free path invoke the caller-
 * supplied element-move thunk; on the occupied path store the moved element
 * directly (no release).  Fatal 0x769cc/0x769d4 on count overflow.
 * Confidence: medium */
static void sk_vec_insert_76918(word_t a, word_t b, word_t t1, word_t t2,
                                word_t move_thunk)
{
    sk_lock_state_enter();                              /* 77698 */
    sk_slot_release(/*this*/ 0, 0);                     /* 77794 */
    sk_element_probe();                                 /* 775c8 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x769cc) */
    {
        word_t tag = FUN_00002534(t1, t2);
        word_t r = FUN_00258c60(sk_element_probe(), /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            sk_overflow_probe();                        /* 77764 */
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x769d4) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        ((void (*)(word_t))move_thunk)(idx);
    } else {
        *(word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 8) = b;
    }
    sk_clear_element(/*this*/ 0);                       /* 7767c */
}

/* FUN_000769d4 @ 0x769d4  (est. sk_vec_insert_u28_move)
 * Insert a 0x28-byte element (move variant): snapshot, resolve, acquire with
 * typeinfo pair (0x64e648, 0x4c04a0); free path runs FUN_00081df0; occupied
 * path copies the five 8-byte halves from the source element and releases the
 * displaced first half.  Fatal 0x76ac0/0x76ac8.
 * Confidence: medium */
static void sk_vec_insert_769d4(word_t *src)
{
    word_t lock = FUN_000778c0();
    sk_clear_element(/*this*/ 0);                       /* 776b4 */
    FUN_00072664(/*key*/ 0);
    word_t st = FUN_000775b8();
    word_t idx = st & 0xffffffff;
    word_t zero = 1;
    if ((word_t)(/*x8*/ 0 + /*x9*/ 0) < /*x8*/ 0) CL4_FATAL(); /* SBP(1,0x76ac0) */
    {
        word_t tag = FUN_00002534(0x64e648, 0x4c04a0);
        word_t r = FUN_00258c60(lock, /*x8+*/ 0 + /*x9*/ 0);
        if ((r & 1) != 0) {
            FUN_00072664(/*key*/ 0);
            idx = sk_clear_element(/*this*/ 0);         /* 7765c */
            if (!zero) CL4_FATAL();                     /* SBP(1,0x76ac8) */
        }
    }
    if (((st >> 32) & 1) == 0) {
        FUN_00077894(idx);
        FUN_00081df0();
    } else {
        word_t *slot = (word_t *)(*(word_t *)(/*this*/ 0 + 0x38) + idx * 0x28);
        word_t old = slot[0];
        slot[4] = src[4];
        slot[0] = src[0];
        slot[1] = src[1];
        slot[3] = src[3];
        slot[2] = src[2];
        FUN_0036b118(old);
    }
}

/* ================================================================== *
 * Bitmap-slot iterator cores.  These walk the set bits of a reversed bitmap
 * (a vector of 64-bit words) and write a derived element into each selected
 * slot.  The incoming value (param_1) and keys (param_3) are retained; the
 * bitmap context is built by FUN_0007198c.  For each set bit the bit index is
 * recovered via the standard 64-bit bit-reverse + LZCOUNT sequence, the slot
 * key is re-derived, the grow lock is acquired (FUN_00258c60), and the slot's
 * element table entry (this+0x30) / auxiliary entry (this+0x38) is written.
 * On a collision the auxiliary value is accumulated (CARRY fatal).
 * ================================================================== */

/* FUN_00076ac8 @ 0x76ac8  (est. sk_slot_iter_u08_bitmap)
 * Iterate the set bits of a bitmap-derived slot set, writing one byte into
 * this+0x30[idx] and an 8-byte count into this+0x38[idx] per bit; on collision
 * accumulate the count (CARRY fatal 0x76cf4), on free set the occupancy bit
 * in this+0x40 and bump the count (0x76cf8/0x76cf0/0x76cec fatals).  Retains
 * param_1/param_3, releases local/container/param_3 and param_1 token at exit.
 * Confidence: medium */
static void sk_slot_iter_76ac8(word_t v, word_t unused, word_t key,
                               word_t flags, word_t *out)
{
    word_t ctx[7];                                       /* local_98.. */
    FUN_0007198c(ctx, /*container*/ 0, 0, 0);
    thunk_FUN_0036b270(v);
    FUN_0036b270(key);
    word_t bits = ctx[6];                                /* local_78 */
    long word = ctx[5];                                  /* lStack_80 */
    for (;;) {
        while (bits != 0) {
            word_t b = (bits & 0xaaaaaaaaaaaaaaaaULL) >> 1 |
                       (bits & 0x5555555555555555ULL) << 1;
            b = (b & 0xccccccccccccccccULL) >> 2 | (b & 0x3333333333333333ULL) << 2;
            b = (b & 0xf0f0f0f0f0f0f0f0ULL) >> 4 | (b & 0x0f0f0f0f0f0f0f0fULL) << 4;
            b = (b & 0xff00ff00ff00ff00ULL) >> 8 | (b & 0x00ff00ff00ff00ffULL) << 8;
            b = (b & 0xffff0000ffff0000ULL) >> 16 | (b & 0x0000ffff0000ffffULL) << 16;
            word_t idx = (word_t)__builtin_clzll(b >> 32 | b << 32) | word << 6;
            /* slot byte + aux value from container tables */
            word_t slot_byte = *(unsigned char *)(ctx[0] + 0x30 + idx);
            word_t aux = *(word_t *)(ctx[0] + 0x38 + idx * 8);
            word_t tag = FUN_00002534(0x64e5b8, 0x4c03b0);
            word_t r = FUN_00258c60(flags & 1, ctx[1] + /*count*/ 0, tag);
            if ((r & 1) != 0)
                FUN_002591b4(0x65f260);                  /* slot moved fatal */
            bits = bits - 1 & bits;
            word_t thisp = *out;
            if ((((word_t)(r >> 32)) & 1) == 0) {
                word_t *bm = (word_t *)(thisp + (idx >> 6) * 8);
                bm[0x40 / 8] |= 1ULL << (idx & 0x3f);
                *(unsigned char *)(*(word_t *)(thisp + 0x30) + idx) = slot_byte;
                *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8) = aux;
                if ((word_t)(*(word_t *)(thisp + 0x10) + 1) < *(word_t *)(thisp + 0x10))
                    CL4_FATAL();                        /* SBP(1,0x76cf8) */
                *(word_t *)(thisp + 0x10) += 1;
            } else {
                word_t old = *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8);
                if ((word_t)(old + aux) < old) CL4_FATAL(); /* SBP(1,0x76cf4) */
                *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8) = old + aux;
            }
            flags = 1;
        }
        word = word + 1;
        if ((word_t)word < /*prev*/ 0) CL4_FATAL();      /* SBP(1,0x76cec) */
        if (word >= (long)(ctx[3] + 0x40 >> 6)) break;
        bits = *(word_t *)(ctx[2] + word * 8);
    }
    FUN_0036b118(/*local*/ 0);
    FUN_0036b118(ctx[0]);
    FUN_0036b118(key);
    FUN_003a25d4(v);
}

/* FUN_00076d08 @ 0x76d08  (est. sk_slot_iter_u10_bitmap)
 * Iterate the set bits of a bitmap-derived slot set, writing a 0x10-byte
 * element into this+0x30[idx*0x10] and an 8-byte count into this+0x38[idx]
 * per bit; on collision accumulate the count (CARRY fatal 0x76f60), on free
 * set the occupancy bit and bump the count (0x76f64/0x76f5c/0x76f58 fatals).
 * Retains param_1/param_3, releases local/container/param_3 and param_1 token.
 * Confidence: medium */
static void sk_slot_iter_76d08(word_t v, word_t unused, word_t key,
                               word_t flags, word_t *out)
{
    word_t ctx[7];
    FUN_0007198c(ctx, /*container*/ 0, 0, 0);
    thunk_FUN_0036b270(v);
    FUN_0036b270(key);
    word_t bits = ctx[6];
    long word = ctx[5];
    for (;;) {
        while (bits != 0) {
            word_t b = (bits & 0xaaaaaaaaaaaaaaaaULL) >> 1 |
                       (bits & 0x5555555555555555ULL) << 1;
            b = (b & 0xccccccccccccccccULL) >> 2 | (b & 0x3333333333333333ULL) << 2;
            b = (b & 0xf0f0f0f0f0f0f0f0ULL) >> 4 | (b & 0x0f0f0f0f0f0f0f0fULL) << 4;
            b = (b & 0xff00ff00ff00ff00ULL) >> 8 | (b & 0x00ff00ff00ff00ffULL) << 8;
            b = (b & 0xffff0000ffff0000ULL) >> 16 | (b & 0x0000ffff0000ffffULL) << 16;
            word_t idx = (word_t)__builtin_clzll(b >> 32 | b << 32) | word << 6;
            word_t *e = (word_t *)(ctx[0] + 0x30 + idx * 0x10);
            word_t el_lo = e[0];
            word_t el_hi = (word_t)(unsigned char)((word_t)(e + 1));
            word_t aux = *(word_t *)(ctx[0] + 0x38 + idx * 8);
            word_t tag = FUN_00002534(0x64e8e8, 0x4c0748);
            word_t r = FUN_00258c60(flags & 1, ctx[1] + /*count*/ 0, tag);
            if ((r & 1) != 0)
                FUN_002591b4(0x65f2f0);                  /* slot moved fatal */
            bits = bits - 1 & bits;
            word_t thisp = *out;
            if ((((word_t)(r >> 32)) & 1) == 0) {
                word_t *bm = (word_t *)(thisp + (idx >> 6) * 8);
                bm[0x40 / 8] |= 1ULL << (idx & 0x3f);
                word_t *slot = (word_t *)(*(word_t *)(thisp + 0x30) + idx * 0x10);
                slot[0] = el_lo;
                slot[1] = el_hi;
                *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8) = aux;
                if ((word_t)(*(word_t *)(thisp + 0x10) + 1) < *(word_t *)(thisp + 0x10))
                    CL4_FATAL();                        /* SBP(1,0x76f64) */
                *(word_t *)(thisp + 0x10) += 1;
                flags = 1;
            } else {
                word_t old = *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8);
                if ((word_t)(old + aux) < old) CL4_FATAL(); /* SBP(1,0x76f60) */
                *(word_t *)(*(word_t *)(thisp + 0x38) + idx * 8) = old + aux;
                flags = 1;
            }
        }
        word = word + 1;
        if ((word_t)word < /*prev*/ 0) CL4_FATAL();      /* SBP(1,0x76f58) */
        if (word >= (long)(ctx[3] + 0x40 >> 6)) break;
        bits = *(word_t *)(ctx[2] + word * 8);
    }
    FUN_0036b118(/*local*/ 0);
    FUN_0036b118(ctx[0]);
    FUN_0036b118(key);
    FUN_003a25d4(v);
}

/* ================================================================== *
 * Pointer / tagged-union / element helpers.
 * ================================================================== */

/* FUN_00076f74 @ 0x76f74  (est. sk_elem_build_3word)
 * Build a 3-word tagged element from the source element's fields via
 * FUN_00081fe0, storing low word, tag byte, and spill word into the
 * destination 3-word tuple.
 * Confidence: medium */
static void sk_elem_build_76f74(word_t *dst, word_t *src)
{
    word_t spill;
    word_t lo = FUN_00081fe0(&spill, src[0], *(unsigned char *)((word_t)src + 8), src[2]);
    dst[0] = lo;
    *(unsigned char *)((word_t)dst + 8) = /*extraout_w1*/ 0;
    dst[2] = spill;
}

/* FUN_00076fc0 @ 0x76fc0  (est. sk_write_imm64)
 * Write a single 64-bit immediate (0x91181400d00002a0, an ARM64 instruction
 * constant / jump-patch) to the global slot at 0x64e038.
 * Confidence: low (constant global write; unreachable block removed) */
static void sk_write_imm64_76fc0(void)
{
    *(word_t *)0x64e038 = 0x91181400d00002a0ULL;
}

/* FUN_00077024 @ 0x77024  (est. sk_tagged_deref)
 * Dereference a tagged pointer: if the tag bit (bit 1 of the byte at the
 * object's type tag +0x52) is set, unwind through FUN_0036aae4 to the real
 * pointer; else return the argument unchanged.
 * Confidence: medium */
static word_t sk_tagged_deref_77024(word_t *p)
{
    word_t *r = p;
    if ((*(unsigned char *)(*(word_t *)(p[3] + -8) + 0x52) >> 1 & 1) != 0) {
        word_t lo = FUN_0036aae4();
        r = (word_t *)/*hi*/ 0;
        *p = lo;
    }
    return (word_t)r;
}

/* FUN_00077070 @ 0x77070  (est. sk_elem_copy_5word)
 * Copy a 5-word element from src to dst (5 x 8 bytes).
 * Confidence: high (structural) */
static word_t sk_elem_copy_5word_77070(word_t *src, word_t *dst)
{
    word_t a = src[0], b = src[1], c = src[2], d = src[3];
    dst[4] = src[4];
    dst[1] = b;
    dst[0] = a;
    dst[3] = d;
    dst[2] = c;
    return (word_t)dst;
}

/* FUN_00077088 @ 0x77088  (est. sk_elem_end_off8)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +8 (len is a signed 32-bit int).  Used to find the
 * end of a packed sub-element.
 * Confidence: high (structural) */
static long sk_elem_end_off8_77088(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_000770b8 @ 0x770b8  (est. sk_elem_end_offc)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +0xc.
 * Confidence: high (structural) */
static long sk_elem_end_offc_770b8(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_000770e8 @ 0x770e8  (est. sk_elem_end_off14)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +0x14.
 * Confidence: high (structural) */
static long sk_elem_end_off14_770e8(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0x14) + (long)*(int *)(p + 0x14);
}

/* FUN_00077118 @ 0x77118  (est. sk_elem_end_off18)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +0x18.
 * Confidence: high (structural) */
static long sk_elem_end_off18_77118(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0x18) + (long)*(int *)(p + 0x18);
}

/* FUN_00077148 @ 0x77148  (est. sk_elem_end_off1c)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +0x1c.
 * Confidence: high (structural) */
static long sk_elem_end_off1c_77148(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0x1c) + (long)*(int *)(p + 0x1c);
}

/* FUN_00077178 @ 0x77178  (est. sk_elem_end_off20)
 * Resolve a tagged pointer and return the end of a length-prefixed blob whose
 * length lives at offset +0x20.
 * Confidence: high (structural) */
static long sk_elem_end_off20_77178(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeULL);
    return (long)(p + 0x20) + (long)*(int *)(p + 0x20);
}

/* FUN_000773f0 @ 0x773f0  (est. sk_slot_table_cleanup)
 * Clean up the slot table referenced by the constant 0x64e5d8 (a global
 * table address) via FUN_00077770.
 * Confidence: low (constant-table cleanup) */
static void sk_slot_table_cleanup_773f0(void)
{
    FUN_00077770(0x64e5d8);
}

/* FUN_000774c8 @ 0x774c8  (est. sk_elem_swap_store)
 * Store one element into a slot via an indirect call through a PAC'd function
 * pointer global (_DAT_aa2803e838002f47), returning the stored value.
 * Confidence: low (PAC'd global call) */
static word_t sk_elem_swap_store_774c8(word_t a, word_t b)
{
    ((void (*)(word_t, word_t))0xaa2803e838002f47)(b, a);
    return b;
}

/* ================================================================== *
 * Container lock-state / size / copy glue.
 * ================================================================== */

/* FUN_0007752c @ 0x7752c  (est. sk_lock_state_save)
 * Save lock state; returns 0.  Confidence: high */
static word_t sk_lock_state_save_7752c(void) { return 0; }

/* FUN_00077540 @ 0x77540  (est. sk_move_range)
 * memmove helper: FUN_00117d14(param_4, param_1) — move a range within a
 * container.  Confidence: high (single call) */
static void sk_move_range_77540(word_t a, word_t b, word_t c, word_t d)
{
    FUN_00117d14(d, a);
}

/* FUN_00077550 @ 0x77550  (est. sk_lock_state_clear)
 * Clear the grow-lock state (no-op in this shape).  Confidence: high */
static void sk_lock_state_clear_77550(void) { }

/* FUN_00077560 @ 0x77560  (est. sk_lock_state_probe)
 * Probe the grow-lock state (no-op).  Confidence: high */
static void sk_lock_state_probe_77560(void) { }

/* FUN_00077570 @ 0x77570  (est. sk_lock_state_enter)
 * Enter the grow-lock state (no-op).  Confidence: high */
static void sk_lock_state_enter_77570(void) { }

/* FUN_00077580 @ 0x77580  (est. sk_this_tail)
 * Return the tail pointer of the element vector (this + 0x20).
 * Confidence: high */
static long sk_this_tail_77580(long thisp) { return thisp + 0x20; }

/* FUN_00077590 @ 0x77590  (est. sk_slot_release_noop)
 * No-op.  Confidence: high */
static void sk_slot_release_noop_77590(void) { }

/* FUN_000775b8 @ 0x775b8  (est. sk_lock_snapshot)
 * No-op (register-returned lock snapshot).  Confidence: high */
static void sk_lock_snapshot_775b8(void) { }

/* FUN_000775c8 @ 0x775c8  (est. sk_element_probe_noop)
 * No-op.  Confidence: high */
static void sk_element_probe_noop_775c8(void) { }

/* FUN_000775dc @ 0x775dc  (est. sk_vec_set_size_probe)
 * Compute the element-vector size: `count = (probe - 0x20) / unaff_x21`, store
 * the element-table pointer at this+0x10 and `count<<1` at this+0x18.
 * Confidence: medium */
static void sk_vec_set_size_775dc(word_t thisp)
{
    long probe = thunk_FUN_000126e8();
    long count = 0;
    if (/*unaff_x21*/ 0 != 0) count = (probe - 0x20) / /*unaff_x21*/ 0;
    *(word_t *)(thisp + 0x10) = /*unaff_x19*/ 0;
    *(long *)(thisp + 0x18) = count << 1;
}

/* FUN_00077604 @ 0x77604  (est. sk_clear_element_noop)
 * No-op.  Confidence: high */
static void sk_clear_element_noop_77604(void) { }

/* FUN_00077614 @ 0x77614  (est. sk_element_probe_noop2)
 * No-op.  Confidence: high */
static void sk_element_probe_noop2_77614(void) { }

/* FUN_00077624 @ 0x77624  (est. sk_overflow_probe_noop)
 * No-op.  Confidence: high */
static void sk_overflow_probe_noop_77624(void) { }

/* FUN_00077630 @ 0x77630  (est. sk_alloc_count_probe)
 * Probe allocation count via thunk_FUN_000126e8.  Confidence: high */
static void sk_alloc_count_probe_77630(void) { thunk_FUN_000126e8(); }

/* FUN_0007764c @ 0x7764c  (est. sk_typeinfo_build)
 * Build a typeinfo token from a tag pair via FUN_00002534.
 * Confidence: high */
static void sk_typeinfo_build_7764c(word_t a, word_t b)
{
    FUN_00002534(a, b);
}

/* FUN_0007765c @ 0x7765c  (est. sk_clear_element_noop3)
 * No-op.  Confidence: high */
static void sk_clear_element_noop3_7765c(void) { }

/* FUN_0007766c @ 0x7766c  (est. sk_vec_set_size_probe2)
 * Compute the element-vector size: `count = param_1 / in_x9`, store the
 * element-table pointer at this+0x10 and `count<<1` at this+0x18.
 * Confidence: medium */
static void sk_vec_set_size2_7766c(word_t param_1)
{
    long count = 0;
    if (/*in_x9*/ 0 != 0) count = (long)param_1 / /*in_x9*/ 0;
    *(word_t *)(/*this*/ 0 + 0x10) = /*unaff_x19*/ 0;
    *(long *)(/*this*/ 0 + 0x18) = count << 1;
}

/* FUN_0007767c @ 0x7767c  (est. sk_clear_element_noop4)
 * No-op.  Confidence: high */
static void sk_clear_element_noop4_7767c(void) { }

/* FUN_00077698 @ 0x77698  (est. sk_lock_state_enter2)
 * No-op.  Confidence: high */
static void sk_lock_state_enter2_77698(void) { }

/* FUN_000776b4 @ 0x776b4  (est. sk_clear_element_noop5)
 * No-op.  Confidence: high */
static void sk_clear_element_noop5_776b4(void) { }
