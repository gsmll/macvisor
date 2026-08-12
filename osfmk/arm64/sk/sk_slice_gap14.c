/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image
 * base 0). Ground truth: Ghidra FUN_ names + addresses; public API names from
 * seL4/cL4 vocabulary. All names are estimates unless string/header matched.
 *
 * SKGAP14 wave: functions 0x354028..0x35481c (120 functions). This is a
 * contiguous region of small helpers and empty dispatch slots. Most entries are
 * bare-return no-ops (empty handler/dispatch slots). The remaining bodies are
 * leaf helpers whose logic the decompiler collapses to caller-frame slot
 * accesses (unaff_x29/x19/x20/x21 artifacts) or to a single forwarded call.
 * Where the decompile is degenerate (frame-slot store/load only), the body is
 * rendered faithfully with the frame slot as a volatile null access + comment,
 * matching the convention used across the sk_region_*.c slices.
 *
 * Confidence: medium for the no-op slots (empty handler stubs) and for the
 * small leaf helpers; low where the decompile collapses to frame-slot accesses
 * only (real body inlined into callers).
 */
#include "sk_internal.h"

/* --- Extern shared kernel/microkernel deps (callees; FUN_ addr in comment) --- */
extern void sk_gap14_callee_310a74(void);   /* FUN_00310a74 @ 0x310a74 */
extern void sk_gap14_callee_3723cc(uint64_t, uint64_t, uint64_t, uint64_t,
                                   uint64_t, uint64_t); /* FUN_0037233c = sk_intern_create_3 @ 0x37233c */
extern void sk_gap14_callee_a68f4(void);    /* FUN_000a68f4 @ 0x0a68f4 */
extern void sk_gap14_callee_26e8(void);     /* FUN_000026e8 @ 0x0026e8 */
extern void sk_gap14_callee_310a44(void);   /* FUN_00310a44 @ 0x310a44 */

/* ===================================================================== */
/* No-op / empty dispatch slots                                          */
/* ===================================================================== */

/* FUN_00354034 @ 0x354034 — empty handler; bare return. */
void sk_gap14_noop_354034(void) { return; }

/* FUN_00354040 @ 0x354040 — empty handler; bare return. */
void sk_gap14_noop_354040(void) { return; }

/* FUN_0035404c @ 0x35404c — empty handler; bare return. */
void sk_gap14_noop_35404c(void) { return; }

/* FUN_00354058 @ 0x354058 — empty handler; bare return. */
void sk_gap14_noop_354058(void) { return; }

/* FUN_00354064 @ 0x354064 — empty handler; bare return. */
void sk_gap14_noop_354064(void) { return; }

/* FUN_00354070 @ 0x354070 — empty handler; bare return. */
void sk_gap14_noop_354070(void) { return; }

/* FUN_0035407c @ 0x35407c — empty handler; bare return. */
void sk_gap14_noop_35407c(void) { return; }

/* FUN_00354088 @ 0x354088 — empty handler; bare return. */
void sk_gap14_noop_354088(void) { return; }

/* FUN_00354094 @ 0x354094 — empty handler; bare return. */
void sk_gap14_noop_354094(void) { return; }

/* FUN_003540ac @ 0x3540ac — empty handler; bare return. */
void sk_gap14_noop_3540ac(void) { return; }

/* FUN_003540c4 @ 0x3540c4 — empty handler; bare return. */
void sk_gap14_noop_3540c4(void) { return; }

/* FUN_003540d0 @ 0x3540d0 — empty handler; bare return. */
void sk_gap14_noop_3540d0(void) { return; }

/* FUN_00354134 @ 0x354134 — empty handler; bare return. */
void sk_gap14_noop_354134(void) { return; }

/* FUN_00354140 @ 0x354140 — empty handler; bare return. */
void sk_gap14_noop_354140(void) { return; }

/* FUN_0035414c @ 0x35414c — empty handler; bare return. */
void sk_gap14_noop_35414c(void) { return; }

/* FUN_00354168 @ 0x354168 — empty handler; bare return. */
void sk_gap14_noop_354168(void) { return; }

/* FUN_00354184 @ 0x354184 — empty handler; bare return. */
void sk_gap14_noop_354184(void) { return; }

/* FUN_003541a0 @ 0x3541a0 — empty handler; bare return. */
void sk_gap14_noop_3541a0(void) { return; }

/* FUN_003541bc @ 0x3541bc — empty handler; bare return. */
void sk_gap14_noop_3541bc(void) { return; }

/* FUN_003541d8 @ 0x3541d8 — empty handler; bare return. */
void sk_gap14_noop_3541d8(void) { return; }

/* FUN_003541f4 @ 0x3541f4 — empty handler; bare return. */
void sk_gap14_noop_3541f4(void) { return; }

/* FUN_00354210 @ 0x354210 — empty handler; bare return. */
void sk_gap14_noop_354210(void) { return; }

/* FUN_0035422c @ 0x35422c — empty handler; bare return. */
void sk_gap14_noop_35422c(void) { return; }

/* FUN_00354248 @ 0x354248 — empty handler; bare return. */
void sk_gap14_noop_354248(void) { return; }

/* FUN_00354264 @ 0x354264 — empty handler; bare return. */
void sk_gap14_noop_354264(void) { return; }

/* FUN_0035428c @ 0x35428c — empty handler; bare return. */
void sk_gap14_noop_35428c(void) { return; }

/* FUN_003542c4 @ 0x3542c4 — empty handler; bare return. */
void sk_gap14_noop_3542c4(void) { return; }

/* FUN_003542d0 @ 0x3542d0 — empty handler; bare return. */
void sk_gap14_noop_3542d0(void) { return; }

/* FUN_003542e8 @ 0x3542e8 — empty handler; bare return. */
void sk_gap14_noop_3542e8(void) { return; }

/* FUN_003542f4 @ 0x3542f4 — empty handler; bare return. */
void sk_gap14_noop_3542f4(void) { return; }

/* FUN_00354300 @ 0x354300 — empty handler; bare return. */
void sk_gap14_noop_354300(void) { return; }

/* FUN_0035430c @ 0x35430c — empty handler; bare return. */
void sk_gap14_noop_35430c(void) { return; }

/* FUN_00354318 @ 0x354318 — empty handler; bare return. */
void sk_gap14_noop_354318(void) { return; }

/* FUN_00354324 @ 0x354324 — empty handler; bare return. */
void sk_gap14_noop_354324(void) { return; }

/* FUN_00354330 @ 0x354330 — empty handler; bare return. */
void sk_gap14_noop_354330(void) { return; }

/* FUN_0035433c @ 0x35433c — empty handler; bare return. */
void sk_gap14_noop_35433c(void) { return; }

/* FUN_00354364 @ 0x354364 — empty handler; bare return. */
void sk_gap14_noop_354364(void) { return; }

/* FUN_00354370 @ 0x354370 — empty handler; bare return. */
void sk_gap14_noop_354370(void) { return; }

/* FUN_0035437c @ 0x35437c — empty handler; bare return. */
void sk_gap14_noop_35437c(void) { return; }

/* FUN_00354388 @ 0x354388 — empty handler; bare return. */
void sk_gap14_noop_354388(void) { return; }

/* FUN_00354394 @ 0x354394 — empty handler; bare return. */
void sk_gap14_noop_354394(void) { return; }

/* FUN_003543a0 @ 0x3543a0 — empty handler; bare return. */
void sk_gap14_noop_3543a0(void) { return; }

/* FUN_003543ac @ 0x3543ac — empty handler; bare return. */
void sk_gap14_noop_3543ac(void) { return; }

/* FUN_003543c4 @ 0x3543c4 — empty handler; bare return. */
void sk_gap14_noop_3543c4(void) { return; }

/* FUN_003543dc @ 0x3543dc — empty handler; bare return. */
void sk_gap14_noop_3543dc(void) { return; }

/* FUN_003543f8 @ 0x3543f8 — empty handler; bare return. */
void sk_gap14_noop_3543f8(void) { return; }

/* FUN_00354404 @ 0x354404 — empty handler; bare return. */
void sk_gap14_noop_354404(void) { return; }

/* FUN_00354410 @ 0x354410 — empty handler; bare return. */
void sk_gap14_noop_354410(void) { return; }

/* FUN_0035441c @ 0x35441c — empty handler; bare return. */
void sk_gap14_noop_35441c(void) { return; }

/* FUN_00354428 @ 0x354428 — empty handler; bare return. */
void sk_gap14_noop_354428(void) { return; }

/* FUN_00354440 @ 0x354440 — empty handler; bare return. */
void sk_gap14_noop_354440(void) { return; }

/* FUN_00354458 @ 0x354458 — empty handler; bare return. */
void sk_gap14_noop_354458(void) { return; }

/* FUN_003544c8 @ 0x3544c8 — empty handler; bare return. */
void sk_gap14_noop_3544c8(void) { return; }

/* FUN_003544e0 @ 0x3544e0 — empty handler; bare return. */
void sk_gap14_noop_3544e0(void) { return; }

/* FUN_00354504 @ 0x354504 — empty handler; bare return. */
void sk_gap14_noop_354504(void) { return; }

/* FUN_00354534 @ 0x354534 — empty handler; bare return. */
void sk_gap14_noop_354534(void) { return; }

/* FUN_0035454c @ 0x35454c — empty handler; bare return. */
void sk_gap14_noop_35454c(void) { return; }

/* FUN_00354558 @ 0x354558 — empty handler; bare return. */
void sk_gap14_noop_354558(void) { return; }

/* FUN_0035457c @ 0x35457c — empty handler; bare return. */
void sk_gap14_noop_35457c(void) { return; }

/* FUN_00354588 @ 0x354588 — empty handler; bare return. */
void sk_gap14_noop_354588(void) { return; }

/* FUN_003545a0 @ 0x3545a0 — empty handler; bare return. */
void sk_gap14_noop_3545a0(void) { return; }

/* FUN_003545ac @ 0x3545ac — empty handler; bare return. */
void sk_gap14_noop_3545ac(void) { return; }

/* FUN_003545b8 @ 0x3545b8 — empty handler; bare return. */
void sk_gap14_noop_3545b8(void) { return; }

/* FUN_003545d0 @ 0x3545d0 — empty handler; bare return. */
void sk_gap14_noop_3545d0(void) { return; }

/* FUN_003545e8 @ 0x3545e8 — empty handler; bare return. */
void sk_gap14_noop_3545e8(void) { return; }

/* FUN_003545f4 @ 0x3545f4 — empty handler; bare return. */
void sk_gap14_noop_3545f4(void) { return; }

/* FUN_0035460c @ 0x35460c — empty handler; bare return. */
void sk_gap14_noop_35460c(void) { return; }

/* FUN_00354618 @ 0x354618 — empty handler; bare return. */
void sk_gap14_noop_354618(void) { return; }

/* FUN_0035463c @ 0x35463c — empty handler; bare return. */
void sk_gap14_noop_35463c(void) { return; }

/* FUN_00354660 @ 0x354660 — empty handler; bare return. */
void sk_gap14_noop_354660(void) { return; }

/* FUN_003546a8 @ 0x3546a8 — empty handler; bare return. */
void sk_gap14_noop_3546a8(void) { return; }

/* FUN_003546b4 @ 0x3546b4 — empty handler; bare return. */
void sk_gap14_noop_3546b4(void) { return; }

/* FUN_003546c0 @ 0x3546c0 — empty handler; bare return. */
void sk_gap14_noop_3546c0(void) { return; }

/* FUN_003546cc @ 0x3546cc — empty handler; bare return. */
void sk_gap14_noop_3546cc(void) { return; }

/* FUN_003546e4 @ 0x3546e4 — empty handler; bare return. */
void sk_gap14_noop_3546e4(void) { return; }

/* FUN_003546fc @ 0x3546fc — empty handler; bare return. */
void sk_gap14_noop_3546fc(void) { return; }

/* FUN_00354708 @ 0x354708 — empty handler; bare return. */
void sk_gap14_noop_354708(void) { return; }

/* FUN_00354714 @ 0x354714 — empty handler; bare return. */
void sk_gap14_noop_354714(void) { return; }

/* FUN_00354744 @ 0x354744 — empty handler; bare return. */
void sk_gap14_noop_354744(void) { return; }

/* FUN_0035475c @ 0x35475c — empty handler; bare return. */
void sk_gap14_noop_35475c(void) { return; }

/* FUN_00354774 @ 0x354774 — empty handler; bare return. */
void sk_gap14_noop_354774(void) { return; }

/* FUN_0035478c @ 0x35478c — empty handler; bare return. */
void sk_gap14_noop_35478c(void) { return; }

/* FUN_003547c8 @ 0x3547c8 — empty handler; bare return. */
void sk_gap14_noop_3547c8(void) { return; }

/* FUN_003547d4 @ 0x3547d4 — empty handler; bare return. */
void sk_gap14_noop_3547d4(void) { return; }

/* FUN_003547ec @ 0x3547ec — empty handler; bare return. */
void sk_gap14_noop_3547ec(void) { return; }

/* FUN_003547f8 @ 0x3547f8 — empty handler; bare return. */
void sk_gap14_noop_3547f8(void) { return; }

/* FUN_00354804 @ 0x354804 — empty handler; bare return. */
void sk_gap14_noop_354804(void) { return; }

/* FUN_00354810 @ 0x354810 — empty handler; bare return. */
void sk_gap14_noop_354810(void) { return; }

/* FUN_0035481c @ 0x35481c — empty handler; bare return. */
void sk_gap14_noop_35481c(void) { return; }

/* ===================================================================== */
/* Leaf helpers with real (degenerate) bodies                            */
/* ===================================================================== */

/* FUN_00354028 @ 0x354028 — store a value into the caller frame slot -0xe0.
 * Ghidra: *(sp - 0xe0) = param_1; no other effect. The store is a dead frame
 * write (caller-owned slot), rendered literally. */
void sk_gap14_store_e0(uint64_t val)
{
    *(volatile uint64_t *)0 = val;   /* unaff_x29 - 0xe0 */
    return;
}

/* FUN_003540a0 @ 0x3540a0 — return the caller frame slot at -0x70.
 * Ghidra: return *(sp - 0x70). The slot value is caller-maintained;
 * indeterminate in this rendering (artifact of inlined leaf). */
uint64_t sk_gap14_get_70(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0x70 */
}

/* FUN_003540dc @ 0x3540dc — return the caller frame slot at -0xb0.
 * Ghidra: return *(sp - 0xb0). */
uint64_t sk_gap14_get_b0(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0xb0 */
}

/* FUN_003540e8 @ 0x3540e8 — write constant 0x40 into the caller frame slot
 * -0x58. Ghidra: *(sp - 0x58) = 0x40; no other effect. */
void sk_gap14_store_const40(uint64_t dummy)
{
    (void)dummy;
    *(volatile uint64_t *)0 = 0x40;   /* unaff_x29 - 0x58 */
    return;
}

/* FUN_003540f4 @ 0x3540f4 — build a tagged "pointerValue" descriptor object.
 * Ghidra: writes into a caller-owned object:
 *   obj+0x10 = param_1.lo, obj+0x18 = param_1.hi   (16-byte value)
 *   obj+0x20 = 0x567265746e696f70 ("pointerV")
 *   obj+0x28 = 0xec00000065756c61 ("alue\0" + tag byte 0xec)
 *   obj+0x48 = 0x677790
 * i.e. a 16-byte value plus a 7-byte type tag "pointerValue" (the leading
 * 0xec byte is a type discriminator) and a static data pointer. This is a
 * microkernel object/type-name descriptor initializer (called from 0x268038,
 * 0x2680a8). Confidence low (field semantics inferred). */
void sk_gap14_pointervalue_descriptor_init(word_t *obj, cl4_result_t value)
{
    obj[2] = value.lo;                       /* obj+0x10 */
    obj[3] = value.hi;                       /* obj+0x18 */
    *(uint64_t *)((char *)obj + 0x20) = 0x567265746e696f70ull;  /* "pointerV" */
    *(uint64_t *)((char *)obj + 0x28) = 0xec00000065756c61ull;  /* "alue"+0xec */
    *(uint64_t *)((char *)obj + 0x48) = 0x677790ull;            /* static ptr */
    return;
}

/* FUN_00354128 @ 0x354128 — store a value into the caller frame slot -0x120.
 * Ghidra: *(sp - 0x120) = param_1; no other effect. */
void sk_gap14_store_120(uint64_t val)
{
    *(volatile uint64_t *)0 = val;   /* unaff_x29 - 0x120 */
    return;
}

/* FUN_00354270 @ 0x354270 — write constant 0x7fffffffffffffff (LONG_MAX, an
 * infinite/no-timeout sentinel) into the caller frame slot -0x60.
 * Ghidra: *(sp - 0x60) = 0x7fffffffffffffff. */
void sk_gap14_store_inf_timeout(uint64_t dummy)
{
    (void)dummy;
    *(volatile uint64_t *)0 = 0x7fffffffffffffffull;   /* unaff_x29 - 0x60 */
    return;
}

/* FUN_0035427c @ 0x35427c — write constant 0xffffffffffffff80 into the caller
 * frame slot -0x58, then forward to FUN_00310a74 (a leaf callee).
 * Ghidra: *(sp - 0x58) = 0xffffffffffffff80; FUN_00310a74();
 * Callers: 0x3140c4, 0x314cac, 0x317b50, 0x318718. */
void sk_gap14_store_const80_then_call(uint64_t dummy)
{
    (void)dummy;
    *(volatile uint64_t *)0 = 0xffffffffffffff80ull;   /* unaff_x29 - 0x58 */
    sk_gap14_callee_310a74();   /* FUN_00310a74 @ 0x310a74 */
    return;
}

/* FUN_003542a8 @ 0x3542a8 — store a value through a caller-preserved register
 * pointer. Ghidra: *unaff_x20 = param_1 (x20 is a caller-preserved reg; the
 * target address is caller-provided). */
void sk_gap14_store_via_reg(uint64_t val)
{
    uint64_t *slot = (uint64_t *)0;   /* unaff_x20 */
    *slot = val;
    return;
}

/* FUN_003542b0 @ 0x3542b0 — return the inverse of the carry flag from the
 * caller's comparison. Ghidra: return !in_CY. This is the tail of an inline
 * compare (e.g. "result == 0" from a subtract); indeterminate in C. */
int sk_gap14_flag_notcarry(void)
{
    return 0;   /* !in_CY — carry flag from caller context, not representable */
}

/* FUN_003542b8 @ 0x3542b8 — return constant 0xff. Ghidra: return 0xff. */
uint64_t sk_gap14_const_ff(void)
{
    return 0xff;
}

/* FUN_003542dc @ 0x3542dc — mask a caller-preserved value and add 0x20.
 * Ghidra: return (unaff_x20 & 0xfffffffffffffff) + 0x20. The 0x20 is an
 * object/field offset; the low 60-bit mask isolates a payload/pointer field. */
uint64_t sk_gap14_mask_plus_20(uint64_t v)
{
    return (v & 0xfffffffffffffffull) + 0x20;
}

/* FUN_00354348 @ 0x354348 — initialize a caller object record.
 * Ghidra (obj = unaff_x19):
 *   obj[3] = param_1
 *   obj[4] = &DAT_004f1660      (static data / vtbl / name ptr)
 *   obj[0] = param_2
 * i.e. an object whose word 0 is param_2, word 3 is param_1, and word 4 points
 * at static table DAT_004f1660. Callers: 0x2e93bc, 0x2eac2c. */
void sk_gap14_object_init_348(uint64_t *obj, uint64_t a, uint64_t b)
{
    obj[3] = a;
    obj[4] = (uint64_t)0;   /* &DAT_004f1660 @ 0x4f1660 */
    obj[0] = b;
    return;
}

/* FUN_003543b8 @ 0x3543b8 — return the caller frame slot at -0x80.
 * Ghidra: return *(sp - 0x80). */
uint64_t sk_gap14_get_80(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0x80 */
}

/* FUN_003543d0 @ 0x3543d0 — return constant 0. Ghidra: return 0. */
uint64_t sk_gap14_zero(void)
{
    return 0;
}

/* FUN_00354474 @ 0x354474 — forward to leaf callee FUN_000a68f4.
 * Ghidra: FUN_000a68f4(); return. Widely called (0x1a2128, 0x1a4554, 0x1af990,
 * 0x1bc440, 0x208884, 0x2181e0, 0x231f04, 0x24657c, 0x246d54, 0x29cb88,
 * 0x2c57a0, 0x2c6228, 0x2e3870). */
void sk_gap14_fwd_a68f4(void)
{
    sk_gap14_callee_a68f4();   /* FUN_000a68f4 @ 0x0a68f4 */
    return;
}

/* FUN_0035448c @ 0x35448c — spill arguments to the caller frame, then forward
 * to FUN_0037233c (sk_intern_create_3).
 * Ghidra (param_3..param_6 to frame slots, then):
 *   FUN_0037233c(0, param_7, param_8, *(sp+0x10), 0, 0)
 * The stack-arg slots (sp+0x10 / +0x18) come from the caller's varargs tail.
 * Callers: 0x321e64, 0x322010. */
void sk_gap14_fwd_intern_create3(uint64_t p1, uint64_t p2, uint64_t p3,
                                 uint64_t p4, uint64_t p5, uint64_t p6,
                                 uint64_t p7, uint64_t p8)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6;
    /* *(sp-0x88)=p3, *(sp-0x80)=p4, *(sp-0x78)=p5, *(sp-0x70)=*(sp+0x18),
     * *(sp-0x68)=p6 — caller-frame spills, no observable effect here. */
    sk_gap14_callee_3723cc(0, p7, p8, 0 /* *(sp+0x10) */, 0, 0);
    /* FUN_0037233c = sk_intern_create_3 @ 0x37233c */
    return;
}

/* FUN_003544ec @ 0x3544ec — return a static data address DAT_004edcec.
 * Ghidra: return &DAT_004edcec. */
uint64_t sk_gap14_static_ptr_4edcec(void)
{
    return (uint64_t)0;   /* &DAT_004edcec @ 0x4edcec */
}

/* FUN_00354570 @ 0x354570 — store a value into the caller frame slot -0x150.
 * Ghidra: *(sp - 0x150) = param_1; no other effect. */
void sk_gap14_store_150(uint64_t val)
{
    *(volatile uint64_t *)0 = val;   /* unaff_x29 - 0x150 */
    return;
}

/* FUN_00354594 @ 0x354594 — return the caller frame slot at -0x88.
 * Ghidra: return *(sp - 0x88). Callers: 0x1daea8, 0x20b358, 0x20eefc, 0x21166c,
 * 0x23a354, 0x240e10, 0x311e34. */
uint64_t sk_gap14_get_88(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0x88 */
}

/* FUN_00354624 @ 0x354624 — forward to leaf callee FUN_000026e8.
 * Ghidra: FUN_000026e8(); return. Widely called from the 0x1c6xxx..0x1cbxxx
 * region (object/notification op handling). */
void sk_gap14_fwd_26e8(void)
{
    sk_gap14_callee_26e8();   /* FUN_000026e8 @ 0x0026e8 */
    return;
}

/* FUN_00354648 @ 0x354648 — return the caller frame slot at -0x68.
 * Ghidra: return *(sp - 0x68). */
uint64_t sk_gap14_get_68(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0x68 */
}

/* FUN_00354654 @ 0x354654 — return an address into the caller's incoming stack
 * area. Ghidra: return &stack0x00000008 (the stack slot at sp+8). */
uint64_t sk_gap14_stack_arg_ptr(void)
{
    return (uint64_t)0;   /* &stack0x00000008 — caller incoming stack slot */
}

/* FUN_0035466c @ 0x35466c — return the caller frame slot at -0x80.
 * Ghidra: return *(sp - 0x80). */
uint64_t sk_gap14_get_80b(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0x80 */
}

/* FUN_00354678 @ 0x354678 — initialize a caller object record.
 * Ghidra (obj = unaff_x19):
 *   obj+0x18 = param_1
 *   obj+0x20 = &DAT_004f17e0   (static data / vtbl / name ptr)
 * i.e. an object whose +0x18 word is param_1 and whose +0x20 word points at
 * static table DAT_004f17e0. */
void sk_gap14_object_init_678(uint64_t *obj, uint64_t a)
{
    *(uint64_t *)((char *)obj + 0x18) = a;
    *(uint64_t *)((char *)obj + 0x20) = (uint64_t)0;   /* &DAT_004f17e0 */
    return;
}

/* FUN_00354690 @ 0x354690 — return a static data address DAT_004e8230.
 * Ghidra: return &DAT_004e8230. */
uint64_t sk_gap14_static_ptr_4e8230(void)
{
    return (uint64_t)0;   /* &DAT_004e8230 @ 0x4e8230 */
}

/* FUN_00354720 @ 0x354720 — copy a caller-preserved register value into a
 * caller-preserved pointer target. Ghidra: *unaff_x19 = unaff_x21. */
void sk_gap14_store_x21_via_x19(void)
{
    uint64_t *slot = (uint64_t *)0;   /* unaff_x19 */
    *slot = 0;                         /* unaff_x21 */
    return;
}

/* FUN_0035472c @ 0x35472c — initialize a caller object record.
 * Ghidra (obj = unaff_x19):
 *   obj+0x18 = param_1
 *   obj+0x20 = &DAT_004f1628   (static data / vtbl / name ptr) */
void sk_gap14_object_init_72c(uint64_t *obj, uint64_t a)
{
    *(uint64_t *)((char *)obj + 0x18) = a;
    *(uint64_t *)((char *)obj + 0x20) = (uint64_t)0;   /* &DAT_004f1628 */
    return;
}

/* FUN_00354780 @ 0x354780 — return the caller frame slot at -0xa0.
 * Ghidra: return *(sp - 0xa0). */
uint64_t sk_gap14_get_a0(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29 - 0xa0 */
}

/* FUN_00354798 @ 0x354798 — return a static data address DAT_004e9d58.
 * Ghidra: return &DAT_004e9d58. */
uint64_t sk_gap14_static_ptr_4e9d58(void)
{
    return (uint64_t)0;   /* &DAT_004e9d58 @ 0x4e9d58 */
}

/* FUN_003547b0 @ 0x3547b0 — forward to leaf callee FUN_00310a44.
 * Ghidra: FUN_00310a44(); return. Callers: 0x239294, 0x2448e0, 0x2ca154,
 * 0x2de068, 0x30c130, 0x311e34. */
void sk_gap14_fwd_310a44(void)
{
    sk_gap14_callee_310a44();   /* FUN_00310a44 @ 0x310a44 */
    return;
}
