/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 11: 0x80000-0x100000 caps region.
 *
 * NOTE: This region is the exclave "Bundle" deployment subsystem
 * (InternalExclaveLauncher / BundleDescriptor / ComponentGraph / Assets
 * handling). Functions are bundle-descriptor accessors, the bundle builder,
 * vtable dispatch accessors and the top-level launcher entry points. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * 16-byte {lo,hi} result type (matches cL4's packed register-pair
 * returns seen throughout this region).
 * ------------------------------------------------------------------ */
typedef struct cl4_res2 {
    uint64_t lo;
    uint64_t hi;
} cl4_res2_t;

/* 12-byte result (FUN_0029f368). */
typedef struct cl4_res12 {
    uint64_t lo;
    uint32_t hi;
} cl4_res12_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (bodies owned by the range worker
 * that owns them; declared extern with a one-line note).  Empty parens =
 * unspecified params (old-style C) so that any call arity compiles.
 * ------------------------------------------------------------------ */

/* --- retain / release / ref-count --- */
extern unsigned long cL4_retain();       /* FUN_0036b270 + thunk: acquire a reference */
extern unsigned long cL4_release();      /* FUN_0036b118: drop a reference */
extern unsigned long cL4_release_lo();   /* FUN_003a25d4: LO-style release of an object */
extern unsigned long cL4_assert_ok();    /* FUN_003a25e0: begin a scoped tagged-object check */
extern unsigned long cL4_assert_fail();  /* FUN_003a2610: fail a scoped tagged-object check */
extern void          cL4_finish();       /* FUN_0036b6ac: teardown/finalize helper */
extern unsigned long cL4_dispatch();     /* FUN_002a0cf8: generic tagged dispatch/compare */
extern unsigned long cL4_ref_2acbb8();   /* FUN_002acbb8 (thunk): debug/format print */
extern void          cL4_log();          /* FUN_002a4ab4: log event by id */
extern unsigned long cL4_alloc();        /* FUN_0036a940: object/allocator */
extern unsigned long cL4_alloc2();       /* FUN_0036a9a0: object/allocator */

/* --- tagged-object / ASN1 navigation helpers (FUN_000baXXX family) --- */
extern unsigned long cL4_oh_ba424();  /* FUN_000ba424 */
extern unsigned long cL4_oh_ba418();  /* FUN_000ba418 */
extern unsigned long cL4_oh_ba47c();  /* FUN_000ba47c */
extern unsigned long cL4_oh_ba488();  /* FUN_000ba488 */
extern unsigned long cL4_oh_ba4a8();  /* FUN_000ba4a8 */
extern cl4_res2_t  cL4_oh_ba494();    /* FUN_000ba494 (16-byte) */
extern cl4_res2_t  cL4_oh_ba1b4();    /* FUN_000ba1b4 (16-byte) */
extern unsigned long cL4_oh_ba3c0();  /* FUN_000ba3c0: string/name resolve */
extern unsigned long cL4_oh_ba448();  /* FUN_000ba448 */
extern unsigned long cL4_oh_ba470();  /* FUN_000ba470 */
extern unsigned long cL4_oh_ba4c8();  /* FUN_000ba4c8 */
extern unsigned long cL4_oh_ba370();  /* FUN_000ba370 */
extern unsigned long cL4_oh_ba3a8();  /* FUN_000ba3a8 */
extern unsigned long cL4_oh_ba3d4();  /* FUN_000ba3d4 */
extern unsigned long cL4_oh_ba3f0();  /* FUN_000ba3f0 */
extern unsigned long cL4_oh_ba40c();  /* FUN_000ba40c */
extern unsigned long cL4_oh_ba4dc();  /* FUN_000ba4dc */
extern unsigned long cL4_oh_ba4b4();  /* FUN_000ba4b4 */
extern unsigned long cL4_oh_ba35c();  /* FUN_000ba35c: symbol/name lookup */
extern unsigned long cL4_oh_ba224();  /* FUN_000ba224 */
extern unsigned long cL4_oh_ba254();  /* FUN_000ba254 */
extern unsigned long cL4_oh_ba284();  /* FUN_000ba284 */
extern unsigned long cL4_oh_ba2b4();  /* FUN_000ba2b4 */
extern unsigned long cL4_oh_ba2f4();  /* FUN_000ba2f4 */
extern unsigned long cL4_oh_ba454();  /* FUN_000ba454 */
extern unsigned long cL4_oh_ba31c();  /* FUN_000ba31c */
extern unsigned long cL4_oh_ba390();  /* FUN_000ba390 */
extern unsigned long cL4_oh_ba3e4();  /* FUN_000ba3e4: resolve tagged element */
extern unsigned long cL4_oh_ba34c();  /* FUN_000ba34c */
extern unsigned long cL4_oh_ba2d4();  /* FUN_000ba2d4 (code) */

/* --- string / format / assert / fatal --- */
extern unsigned long cL4_str_1f0130();  /* FUN_001f0130: message/string format */
extern unsigned long cL4_str_1ee018();  /* FUN_001ee018: tagged-string fetch */
extern unsigned long cL4_str_1f66cc();  /* FUN_001f66cc: print format */
extern unsigned long cL4_fatal();       /* FUN_001afa84: fatal error, no return */
extern cl4_res2_t  cL4_str_13ccf4();  /* FUN_0013ccf4: fetch 16B tagged value */
extern unsigned long cL4_str_13c8f4();  /* FUN_0013c8f4: fetch tagged scalar */
extern unsigned long cL4_str_13c8d0();  /* FUN_0013c8d0: fetch tagged scalar */
extern unsigned long cL4_str_13cdd8();  /* FUN_0013cdd8 */
extern unsigned long cL4_parse_139c6c();/* FUN_00139c6c: parse tagged node */
extern cl4_res12_t  cL4_parse_29f368();/* FUN_0029f368: vspace/page walk step (12B) */
extern cl4_res2_t   cL4_parse_29fa0c();/* FUN_0029fa0c: vspace/page walk step */
extern cl4_res2_t   cL4_seq_29fb80();  /* FUN_0029fb80: next tagged element */
extern unsigned long cL4_tag_2abcb0();  /* FUN_002abcb0: match tag */
extern unsigned long cL4_tag_2abe60();  /* FUN_002abe60: match tag */
extern unsigned long cL4_tag_2a3e64();  /* FUN_002a3e64: next tagged value */

/* --- boot/init/thread --- */
extern unsigned long cL4_boot_2534();  /* FUN_00002534 */
extern void          cL4_boot_2804();  /* FUN_00002804 */
extern void          cL4_boot_2688();  /* FUN_00002688 */
extern void          cL4_boot_2834();  /* FUN_00002834 */
extern unsigned long cL4_boot_1bc440();/* FUN_001bc440 */
extern unsigned long cL4_glue_76fc0(); /* FUN_00076fc0 */
extern unsigned long cL4_glue_a5c1c(); /* FUN_000a5c1c */
extern unsigned long cL4_glue_1e790(); /* FUN_0001e790 */
extern unsigned long cL4_glue_1ebfb0();/* FUN_001ebfb0 */
extern unsigned long cL4_glue_8409c(); /* FUN_0008409c */
extern unsigned long cL4_glue_84100(); /* FUN_00084100 */
extern unsigned long cL4_glue_8e3b0(); /* FUN_0008e3b0 */
extern unsigned long cL4_glue_9455c(); /* FUN_0009455c */
extern unsigned long cL4_glue_867b4(); /* FUN_000867b4 */
extern unsigned long cL4_glue_773f0(); /* FUN_000773f0 */
extern unsigned long cL4_glue_6f70c(); /* FUN_0006f70c */
extern unsigned long cL4_glue_7c0e0(); /* FUN_0007c0e0 */
extern unsigned long cL4_glue_a6f68(); /* FUN_000a6f68 */
extern unsigned long cL4_glue_776cc(); /* FUN_000776cc */
extern unsigned long cL4_glue_7629c(); /* FUN_0007629c */
extern unsigned long cL4_glue_a1bd8(); /* FUN_000a1bd8 */
extern unsigned long cL4_glue_34f70(); /* FUN_00034f70 */
extern unsigned long cL4_glue_85374(); /* FUN_00085374: panic w/ string+line */
extern unsigned long cL4_glue_151974();/* FUN_00151974 */
extern unsigned long cL4_glue_151a6c();/* FUN_00151a6c: panic w/ file+line */
extern unsigned long cL4_glue_70594(); /* FUN_00070594 */
extern unsigned long cL4_glue_6afb4(); /* FUN_0006afb4 */
extern unsigned long cL4_glue_72c0c(); /* FUN_00072c0c: array grow */
extern unsigned long cL4_glue_73e88(); /* FUN_00073e88: array grow */
extern unsigned long cL4_glue_73dfc(); /* FUN_00073dfc: array grow */
extern unsigned long cL4_glue_73fa0(); /* FUN_00073fa0: array grow */
extern unsigned long cL4_glue_73f14(); /* FUN_00073f14: array grow */
extern unsigned long cL4_glue_6a374(); /* FUN_0006a374: array grow */
extern unsigned long cL4_glue_6b42c(); /* FUN_0006b42c: array grow */
extern unsigned long cL4_glue_82624(); /* FUN_00082624: array grow */
extern unsigned long cL4_glue_82644(); /* FUN_00082644: array grow */
extern unsigned long cL4_glue_82664(); /* FUN_00082664: array grow */
extern unsigned long cL4_glue_1a1564();/* FUN_001a1564: array grow */
extern unsigned long cL4_glue_1a0774();/* FUN_001a0774: array grow */
extern unsigned long cL4_glue_1dd77c();/* FUN_001dd77c */
extern unsigned long cL4_glue_1dd858();/* FUN_001dd858 */
extern unsigned long cL4_glue_19e3b0();/* FUN_0019e3b0 */
extern unsigned long cL4_glue_6ae9c(); /* FUN_0006ae9c: tagged find */
extern unsigned long cL4_glue_3a261c();/* FUN_003a261c: array has-capacity check */
extern unsigned long cL4_glue_6a1a0(); /* FUN_0036a1a0 */
extern unsigned long cL4_glue_ad684(); /* FUN_000ad684 */
extern unsigned long cL4_glue_719dc(); /* FUN_000719dc */
extern unsigned long cL4_glue_7bebc(); /* FUN_0007bebc */
extern unsigned long cL4_glue_7bf80(); /* FUN_0007bf80: get self/current object */
extern unsigned long cL4_glue_29369c();/* FUN_0029369c */
extern unsigned long cL4_glue_9e6c();  /* FUN_000b9e6c */
extern unsigned long cL4_glue_9ac4();  /* FUN_000b9ac4 */
extern unsigned long cL4_glue_258c60();/* FUN_00258c60 */
extern unsigned long cL4_glue_2591b4();/* FUN_002591b4: fatal, no return */
extern unsigned long cL4_glue_ee9f4(); /* FUN_001ee9f4: fatal, no return */

/* --- same-region helpers (bodies below) --- */
extern unsigned long cL4_bundle_build_6634();     /* FUN_000b6634 (below) */
extern unsigned long cL4_bundle_type_6354();      /* FUN_000b6354 (below) */
extern unsigned long cL4_bundle_process_71c4();   /* FUN_000b71c4 (below) */
extern unsigned long cL4_bundle_attach_788c();    /* FUN_000b788c (below) */
extern unsigned long cL4_list_sort_8ca0();        /* FUN_000b8ca0 (below) */

/* --- forward declarations of same-slice functions (defined below, called
   above their definitions) --- */
extern void     cL4_bundle_component_init(void);                            /* FUN_000b5220 */
extern void     cL4_bundle_component_fill(uint64_t, uint64_t, uint64_t,
                                          uint8_t, uint64_t, uint64_t, uint64_t); /* FUN_000b5368 */
extern void     cL4_bundle_item_init(uint64_t, uint64_t, uint8_t, uint64_t);      /* FUN_000b5b94 */
extern void     cL4_asset_init(void);                                        /* FUN_000b5c5c */
extern uint64_t cL4_bundle_container_make(long, long);                       /* FUN_000b8bf4 */

/* ======================================================================
 * Caps-region functions (ascending address order).
 * ====================================================================== */

/* FUN_000b44cc @ 0x000b44cc   (est. cL4_dispatch_helper_stub)
 * Ghidra: undefined FUN_000b44cc(void)
 * Thin pass-through that invokes the shared cL4 dispatch helper and returns.
 * Confidence: high
 * Notes: single call to FUN_002a0cf8 (out of slice). */
void cL4_dispatch_helper_stub(void)
{
    cL4_dispatch();
}

/* FUN_000b44e0 @ 0x000b44e0   (est. cL4_bundle_forward_1)
 * Ghidra: undefined FUN_000b44e0(void)
 * Forwards a field read from the enclosing frame's object (offset +0x10 of
 * the object pointed to by x29-0x68) into the message/notify helper
 * FUN_001dd858. Register-based tail of a callback; the enclosing object
 * pointer could not be fully resolved by the decompiler.
 * Confidence: low
 * Notes: uses unaff_x29 register carry. */
void cL4_bundle_forward_1(void)
{
    /* read object at x29-0x68, forward its +0x10 field to FUN_001dd858 */
    cL4_glue_1dd858(0); /* forwarded value */
}

/* FUN_000b44f0 @ 0x000b44f0   (est. cL4_bundle_log_kind)
 * Ghidra: undefined FUN_000b44f0(void)
 * Logs the tagged constant kind (0x26) with an empty tagged payload
 * (0xe000000000000000 = empty string tag). Used for debug tracing.
 * Confidence: medium
 * Notes: stack literals 0 / 0xe000000000000000; FUN_002a4ab4(0x26). */
void cL4_bundle_log_kind(void)
{
    uint64_t kind = 0;              /* empty tagged string */
    uint64_t tag  = 0xe000000000000000ull;
    cL4_log(0x26);
}

/* FUN_000b4510 @ 0x000b4510   (est. cL4_release_lo_only)
 * Ghidra: undefined FUN_000b4510(void)
 * Releases the current object's reference without further action.
 * Confidence: medium
 * Notes: body is a single call to FUN_003a25d4(). */
void cL4_release_lo_only(void)
{
    cL4_release_lo();
}

/* FUN_000b4528 @ 0x000b4528   (est. cL4_release_lo_only_2)
 * Ghidra: undefined FUN_000b4528(void)
 * Identical to FUN_000b4510: releases the current object reference.
 * Confidence: medium */
void cL4_release_lo_only_2(void)
{
    cL4_release_lo();
}

/* FUN_000b4534 @ 0x000b4534   (est. cL4_noop_4534)
 * Ghidra: undefined FUN_000b4534(void)
 * Empty function (no-op), part of a vtable/slot table.
 * Confidence: high
 * Notes: returns immediately. */
void cL4_noop_4534(void)
{
}

/* FUN_000b4540 @ 0x000b4540   (est. cL4_noop_4540)
 * Ghidra: undefined FUN_000b4540(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4540(void)
{
}

/* FUN_000b4554 @ 0x000b4554   (est. cL4_noop_4554)
 * Ghidra: undefined FUN_000b4554(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4554(void)
{
}

/* FUN_000b4568 @ 0x000b4568   (est. cL4_noop_4568)
 * Ghidra: undefined FUN_000b4568(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4568(void)
{
}

/* FUN_000b4574 @ 0x000b4574   (est. cL4_noop_4574)
 * Ghidra: undefined FUN_000b4574(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4574(void)
{
}

/* FUN_000b4588 @ 0x000b4588   (est. cL4_noop_4588)
 * Ghidra: undefined FUN_000b4588(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4588(void)
{
}

/* FUN_000b4594 @ 0x000b4594   (est. cL4_noop_4594)
 * Ghidra: undefined FUN_000b4594(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_4594(void)
{
}

/* FUN_000b45b0 @ 0x000b45b0   (est. cL4_noop_45b0)
 * Ghidra: undefined FUN_000b45b0(void)
 * Empty function (no-op).
 * Confidence: high */
void cL4_noop_45b0(void)
{
}

/* FUN_000b45cc @ 0x000b45cc   (est. cL4_bundle_forward_2)
 * Ghidra: undefined FUN_000b45cc(void)
 * Forwards a field read at the stack word (+0x18) offset +0x10 into the
 * message helper FUN_001dd858. Register-based callback tail.
 * Confidence: low
 * Notes: in_stack_00000018 carry. */
void cL4_bundle_forward_2(void)
{
    /* forward *(stack+0x18 + 0x10) to FUN_001dd858 */
    cL4_glue_1dd858(0);
}

/* FUN_000b45e0 @ 0x000b45e0   (est. cL4_dispatch_helper_stub_2)
 * Ghidra: undefined FUN_000b45e0(void)
 * Pass-through wrapper invoking the shared dispatch helper.
 * Confidence: high
 * Notes: single call to FUN_002a0cf8(). */
void cL4_dispatch_helper_stub_2(void)
{
    cL4_dispatch();
}

/* FUN_000b45f4 @ 0x000b45f4   (est. cL4_release_current)
 * Ghidra: undefined FUN_000b45f4(void)
 * Drops the current object reference.
 * Confidence: medium
 * Notes: single call to FUN_0036b118(). */
void cL4_release_current(void)
{
    cL4_release();
}

/* FUN_000b4660 @ 0x000b4660   (est. cL4_vspace_walk_plus)
 * Ghidra: undefined1 [16] FUN_000b4660(long, ulong, ulong)
 * Page-table walk/check for the positive virtual-address case. Resolves a
 * vspace level (7=table-level block, 0xb=page) and a physical address field
 * from the PTE word (param_3), walks via FUN_0029f368 and completes with
 * FUN_0029fa0c. Returns a 16-byte {status, address} result. Panics (via
 * SoftwareBreakpoint) if the virtual address is negative.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0xb4734) fault; FUN_0029f368/FUN_0029fa0c. */
cl4_res2_t cL4_vspace_walk_plus(long vaddr, uint64_t pte_hi, uint64_t pte_lo)
{
    uint64_t phys;
    uint64_t result;
    uint64_t level;
    uint32_t flag;
    cl4_res12_t walk;
    cl4_res2_t  out;

    if (vaddr < 0) {
        /* SoftwareBreakpoint(1,0xb4734) — does not return */
        for (;;) { }
    }
    phys = pte_hi & 0xffffffffffff;
    if ((pte_lo & 0x2000000000000000ull) != 0) {
        phys = pte_lo >> 0x38 & 0xf;
    }
    flag = (uint32_t)(pte_hi >> 0x3b) & 1;
    if ((pte_lo & 0x1000000000000000ull) == 0) {
        flag = 1;
    }
    level = 7;                       /* table block */
    if (flag == 0) {
        level = 0xb;                 /* page */
    }
    level = level | phys << 0x10;
    walk = cL4_parse_29f368(0xf, vaddr, level, pte_hi, pte_lo);
    result = level;
    if ((walk.hi & 0xff) != 1) {
        result = walk.lo;
    }
    if (result >> 0xe <= phys << 2) {
        out = cL4_parse_29fa0c(result, level, pte_hi, pte_lo);
        cL4_release_lo(pte_lo);
        return out;
    }
    /* SoftwareBreakpoint(1,0xb4738) — does not return */
    for (;;) { }
}

/* FUN_000b4738 @ 0x000b4738   (est. cL4_vspace_walk_minus)
 * Ghidra: undefined1 [16] FUN_000b4738(long, ulong, ulong)
 * Mirror of FUN_000b4660 for the negative virtual-address case: resolves a
 * vspace level and physical-address field from the PTE word and walks via
 * FUN_0029f368/FUN_0029fa0c, returning a 16-byte {status,address}. Panics
 * if the virtual address is non-negative (it belongs in the _plus path).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0xb47fc) fault. */
cl4_res2_t cL4_vspace_walk_minus(long vaddr, uint64_t pte_hi, uint64_t pte_lo)
{
    uint64_t phys;
    uint64_t level;
    uint64_t result;
    uint32_t flag;
    cl4_res12_t walk;
    cl4_res2_t  out;

    if (vaddr >= 0) {
        flag = (uint32_t)(pte_hi >> 0x3b) & 1;
        if ((pte_lo & 0x1000000000000000ull) == 0) {
            flag = 1;
        }
        phys = pte_hi;
        if ((pte_lo & 0x2000000000000000ull) != 0) {
            phys = pte_lo >> 0x38 & 0xf;
        }
        level = 7;
        if (flag == 0) {
            level = 0xb;
        }
        walk = cL4_parse_29f368(level | phys << 0x10, -vaddr, 0xf,
                                pte_hi, pte_lo);
        result = 0xf;
        if ((walk.hi & 0xff) != 1) {
            result = walk.lo;
        }
        out = cL4_parse_29fa0c(0xf, result, pte_hi, pte_lo);
        cL4_release_lo(pte_lo);
        return out;
    }
    /* SoftwareBreakpoint(1,0xb47fc) — does not return */
    for (;;) { }
}

/* FUN_000b47fc @ 0x000b47fc   (est. cL4_vtable_call_0)
 * Ghidra: undefined1 [16] FUN_000b47fc(void)
 * Invokes the object's vtable method at offset +8 (after a 16-byte vtable
 * header loaded into x20) and returns the 16-byte result from the prior
 * frame. Register-based vtable-dispatch tail.
 * Confidence: low
 * Notes: unaff_x20 carry; *(*(x20)+8) called with *(x20+8). */
cl4_res2_t cL4_vtable_call_0(void)
{
    cL4_release(0);                    /* vtable +8 dispatch result */
    return (cl4_res2_t){ .lo = 0, .hi = 0 };
}

/* FUN_000b482c @ 0x000b482c   (est. cL4_bundle_swap2_8)
 * Ghidra: undefined FUN_000b482c(void)
 * Rotates two object fields at x20[0]/x20[1]: begins a scoped update
 * (FUN_0008409c), releases the old x20[1] value, then stores x21/x19.
 * Confidence: low
 * Notes: unaff_x19/x20/x21 register carries. */
void cL4_bundle_swap2_8(void)
{
    cL4_glue_8409c();
    cL4_release_lo(0);          /* old x20[1] */
    /* *x20 = x21; x20[1] = x19; */
}

/* FUN_000b4880 @ 0x000b4880   (est. cL4_vtable_call_1)
 * Ghidra: undefined FUN_000b4880(undefined8, undefined8)
 * Invokes the vtable method at +8 with the given argument, releasing the
 * current object reference.
 * Confidence: low
 * Notes: thunk_FUN_0036b270(param_2) then call. */
void cL4_vtable_call_1(uint64_t a, uint64_t b)
{
    cL4_retain(b);
}

/* FUN_000b4888 @ 0x000b4888   (est. cL4_field_set_8)
 * Ghidra: undefined FUN_000b4888(undefined8)
 * Setter for the object field at x20+8: releases the old value, stores the
 * new one. No retain of the new value (borrowed reference).
 * Confidence: medium
 * Notes: unaff_x20 carry. */
void cL4_field_set_8(uint64_t value)
{
    cL4_release_lo(0);          /* release old *(x20+8) */
    /* *(x20+8) = value; */
}

/* FUN_000b48d0 @ 0x000b48d0   (est. cL4_field_set_8_ref)
 * Ghidra: undefined FUN_000b48d0(undefined8)
 * Setter for the object field at x20+8 (reference-counted variant):
 * releases the old value via FUN_0036b118, stores the new one.
 * Confidence: medium */
void cL4_field_set_8_ref(uint64_t value)
{
    cL4_release(0);             /* release old *(x20+8) */
    /* *(x20+8) = value; */
}

/* FUN_000b48fc @ 0x000b48fc   (est. cL4_field_set_18)
 * Ghidra: undefined FUN_000b48fc(undefined8)
 * Setter for the object field at x20+0x18: releases the old value, stores
 * the new one.
 * Confidence: medium */
void cL4_field_set_18(uint64_t value)
{
    cL4_release(0);             /* release old *(x20+0x18) */
    /* *(x20+0x18) = value; */
}

/* FUN_000b4928 @ 0x000b4928   (est. cL4_field_set_20)
 * Ghidra: undefined FUN_000b4928(undefined8)
 * Setter for the object field at x20+0x20: releases the old value, stores
 * the new one.
 * Confidence: medium */
void cL4_field_set_20(uint64_t value)
{
    cL4_release(0);             /* release old *(x20+0x20) */
    /* *(x20+0x20) = value; */
}

/* FUN_000b496c @ 0x000b496c   (est. cL4_field_set_10)
 * Ghidra: undefined FUN_000b496c(void)
 * Setter for the object field at x20+0x10: performs a scoped update
 * (FUN_000ba424 + FUN_0008e3b0) and stores x19.
 * Confidence: low
 * Notes: unaff_x19/x20 carries. */
void cL4_field_set_10(void)
{
    cL4_oh_ba424();
    cL4_glue_8e3b0();
    /* *(x20+0x10) = x19; */
}

/* FUN_000b499c @ 0x000b499c   (est. cL4_field_get_ptr_10)
 * Ghidra: undefined1 [16] FUN_000b499c(void)
 * Getter returning a {type-word, pointer} pair for the object field at
 * x20+0x10: the lo word is the DAT_0007bf58 type tag, hi is the field
 * address. After a scoped update (FUN_000ba424 + FUN_0009455c).
 * Confidence: low
 * Notes: DAT_0007bf58 type tag. */
cl4_res2_t cL4_field_get_ptr_10(void)
{
    cl4_res2_t out;
    cL4_oh_ba424();
    cL4_glue_9455c();
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x10 */
    return out;
}

/* FUN_000b49dc @ 0x000b49dc   (est. cL4_vtable_call_2)
 * Ghidra: undefined FUN_000b49dc(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x78 of *param_2 with the two words
 * from param_1, releasing the second word reference first.
 * Confidence: low
 * Notes: thunk_FUN_0036b270(uVar2) then (*pc)(uVar1,uVar2). */
void cL4_vtable_call_2(uint64_t *a, uint64_t *b)
{
    uint64_t w0 = a[0];
    uint64_t w1 = a[1];
    cL4_retain(w1);
    /* (**(b[0] + 0x78))(w0, w1); */
}

/* FUN_000b4a44 @ 0x000b4a44   (est. cL4_field_get16_18)
 * Ghidra: undefined1 [16] FUN_000b4a44(void)
 * Getter returning the 16-byte value stored at x20+0x18 after a scoped
 * update (FUN_00084100), releasing the value at x20+0x20.
 * Confidence: low
 * Notes: unaff_x20 carry. */
cl4_res2_t cL4_field_get16_18(void)
{
    cl4_res2_t out;
    cL4_glue_84100(0);          /* x20+0x18 */
    out = (cl4_res2_t){ .lo = 0, .hi = 0 };  /* *(x20+0x18) */
    cL4_retain(0);              /* *(x20+0x20) */
    return out;
}

/* FUN_000b4a84 @ 0x000b4a84   (est. cL4_bundle_swap2_18)
 * Ghidra: undefined FUN_000b4a84(void)
 * Rotates two object fields at x20+0x18/x20+0x20: scoped update
 * (FUN_0008409c + FUN_0008e3b0), stores x21/x19, releases the old x20+0x20.
 * Confidence: low
 * Notes: unaff_x19/x20/x21 carries. */
void cL4_bundle_swap2_18(void)
{
    cL4_glue_8409c();
    cL4_glue_8e3b0(0);
    uint64_t old = 0;           /* *(x20+0x20) */
    /* *(x20+0x18)=x21; *(x20+0x20)=x19; */
    cL4_release_lo(old);
}

/* FUN_000b4ac8 @ 0x000b4ac8   (est. cL4_field_get_ptr_18)
 * Ghidra: undefined1 [16] FUN_000b4ac8(void)
 * Getter returning a {type-word, pointer} pair for the object field at
 * x20+0x18. Lo word is DAT_0007bf58 type tag, hi is the field address.
 * Confidence: low
 * Notes: DAT_0007bf58. */
cl4_res2_t cL4_field_get_ptr_18(void)
{
    cl4_res2_t out;
    cL4_glue_9455c(0);          /* x20+0x18 */
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x18 */
    return out;
}

/* FUN_000b4b0c @ 0x000b4b0c   (est. cL4_field_get_28)
 * Ghidra: undefined8 FUN_000b4b0c(void)
 * Getter returning the object field at x20+0x28 after a scoped update.
 * Confidence: medium */
uint64_t cL4_field_get_28(void)
{
    cL4_glue_84100(0);          /* x20+0x28 */
    return 0;                   /* *(x20+0x28) */
}

/* FUN_000b4b34 @ 0x000b4b34   (est. cL4_field_set_28)
 * Ghidra: undefined FUN_000b4b34(void)
 * Setter for the object field at x20+0x28: scoped update then store x19.
 * Confidence: low
 * Notes: FUN_000ba418 + FUN_0008e3b0. */
void cL4_field_set_28(void)
{
    cL4_oh_ba418();
    cL4_glue_8e3b0();
    /* *(x20+0x28) = x19; */
}

/* FUN_000b4b64 @ 0x000b4b64   (est. cL4_field_get_ptr_28)
 * Ghidra: undefined1 [16] FUN_000b4b64(void)
 * Getter returning a {type-word, pointer} pair for the field at x20+0x28.
 * Lo word is LAB_0006f910, hi is the field address.
 * Confidence: low
 * Notes: LAB_0006f910. */
cl4_res2_t cL4_field_get_ptr_28(void)
{
    cl4_res2_t out;
    cL4_oh_ba418();
    cL4_glue_9455c();
    out.lo = 0;                 /* &LAB_0006f910 */
    out.hi = 0;                 /* x20+0x28 */
    return out;
}

/* FUN_000b4ba4 @ 0x000b4ba4   (est. cL4_field_get_30)
 * Ghidra: undefined8 FUN_000b4ba4(void)
 * Getter returning the object field at x20+0x30 after a scoped update.
 * Confidence: medium */
uint64_t cL4_field_get_30(void)
{
    cL4_glue_84100(0);          /* x20+0x30 */
    return 0;                   /* *(x20+0x30) */
}

/* FUN_000b4bcc @ 0x000b4bcc   (est. cL4_field_set_30)
 * Ghidra: undefined FUN_000b4bcc(void)
 * Setter for the object field at x20+0x30: scoped update then store x19.
 * Confidence: low
 * Notes: FUN_000ba47c + FUN_0008e3b0. */
void cL4_field_set_30(void)
{
    cL4_oh_ba47c();
    cL4_glue_8e3b0();
    /* *(x20+0x30) = x19; */
}

/* FUN_000b4bfc @ 0x000b4bfc   (est. cL4_field_get_ptr_30)
 * Ghidra: undefined1 [16] FUN_000b4bfc(void)
 * Getter returning a {type-word, pointer} pair for the field at x20+0x30.
 * Lo word is DAT_0007bf58 type tag.
 * Confidence: low
 * Notes: DAT_0007bf58. */
cl4_res2_t cL4_field_get_ptr_30(void)
{
    cl4_res2_t out;
    cL4_oh_ba47c();
    cL4_glue_9455c();
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x30 */
    return out;
}

/* FUN_000b4c3c @ 0x000b4c3c   (est. cL4_field_set5)
 * Ghidra: undefined FUN_000b4c3c(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Allocates a fresh object (FUN_0036a940) and stores five 64-bit fields
 * into it at +0x10..+0x30. Used to materialise a bundle component entry.
 * Confidence: medium
 * Notes: FUN_000ba4a8 + FUN_0036a940 + 5 stores. */
void cL4_field_set5(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    long obj;
    cL4_oh_ba4a8();
    obj = (long)cL4_alloc();
    /* obj[+0x10]=a; obj[+0x18]=b; obj[+0x20]=c; obj[+0x28]=d; obj[+0x30]=e; */
}

/* FUN_000b4ca8 @ 0x000b4ca8   (est. cL4_release_field_20)
 * Ghidra: undefined FUN_000b4ca8(void)
 * Releases the object field at x20+0x20.
 * Confidence: medium */
void cL4_release_field_20(void)
{
    cL4_release_lo(0);          /* *(x20+0x20) */
}

/* FUN_000b4cac @ 0x000b4cac   (est. cL4_release_field_20b)
 * Ghidra: undefined FUN_000b4cac(void)
 * Releases the object field at x20+0x20 (duplicate of FUN_000b4ca8).
 * Confidence: medium */
void cL4_release_field_20b(void)
{
    cL4_release_lo(0);          /* *(x20+0x20) */
}

/* FUN_000b4cc8 @ 0x000b4cc8   (est. cL4_release_field_20_finish)
 * Ghidra: undefined FUN_000b4cc8(void)
 * Releases the object field at x20+0x20, then performs the scoped teardown
 * sequence FUN_000ba4a8 + FUN_0036b6ac.
 * Confidence: medium */
void cL4_release_field_20_finish(void)
{
    cL4_release_lo(0);          /* *(x20+0x20) */
    cL4_oh_ba4a8();
    cL4_finish();
}

/* FUN_000b4ccc @ 0x000b4ccc   (est. cL4_release_field_20_finish_2)
 * Ghidra: undefined FUN_000b4ccc(void)
 * Identical to FUN_000b4cc8: release field +0x20 then teardown.
 * Confidence: medium */
void cL4_release_field_20_finish_2(void)
{
    cL4_release_lo(0);          /* *(x20+0x20) */
    cL4_oh_ba4a8();
    cL4_finish();
}

/* FUN_000b4cf0 @ 0x000b4cf0   (est. cL4_bundle_debug_dump)
 * Ghidra: undefined1 [16] FUN_000b4cf0(void)
 * Debug-printer that walks a bundle/component object's vtable slots and
 * prints "name" and "type" tags, then returns a "name:" tagged string.
 * Emits the tags "; metadata", "; entity" (0x657079746e75203b /
 * 0xeb000000003a7364), a closing '}' and the header "name:". 
 * Confidence: medium
 * Notes: string literals 0x61646174656d203b ("metadata;"),
 *   0x657079746e75203b ("entity;"), 0x3a656d616e7b ("name:"),
 *   0x7d20 (" }"). vtable slots +0xd8/+0x90/+0xf0. */
cl4_res2_t cL4_bundle_debug_dump(void)
{
    cl4_res2_t out;
    cL4_log(0x24);
    cL4_release_lo(0xe000000000000000ull);
    /* (**(x20 + 0xd8))(); */
    cL4_ref_2acbb8();
    cL4_release_lo(0);
    cL4_ref_2acbb8(0x61646174656d203bull, 0xeb000000003a6174ull);
    /* uVar2 = (**(x20 + 0x90))(); */
    cL4_oh_ba3c0();
    cL4_str_1f66cc(0, 0x6753a0, 0, 0x66dfb8);
    cL4_ref_2acbb8();
    cL4_release_lo(0);
    cL4_release_lo(0);
    cL4_ref_2acbb8(0x657079746e75203bull, 0xeb000000003a7364ull);
    /* uVar2 = (**(x20 + 0xf0))(); */
    cL4_str_1f66cc(0, 0x6753a0, 0x661168, 0x66dfb8);
    cL4_ref_2acbb8();
    cL4_release_lo(0);
    cL4_release_lo(0);
    cL4_ref_2acbb8(0x7d20ull, 0xe200000000000000ull);
    out.lo = 0x3a656d616e7bull;          /* "name:" */
    out.hi = 0xe600000000000000ull;
    return out;
}

/* FUN_000b4eb0 @ 0x000b4eb0   (est. cL4_vtable_call_98)
 * Ghidra: undefined FUN_000b4eb0(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x98 of *param_2, retaining
 * *param_1 first.
 * Confidence: low */
void cL4_vtable_call_98(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0x98))(); */
}

/* FUN_000b4f04 @ 0x000b4f04   (est. cL4_field_get_release_18)
 * Ghidra: undefined FUN_000b4f04(void)
 * Getter for the field at x20+0x18: scoped update then release the field.
 * Confidence: low */
void cL4_field_get_release_18(void)
{
    cL4_glue_84100(0);          /* x20+0x18 */
    cL4_retain(0);              /* *(x20+0x18) */
}

/* FUN_000b4f48 @ 0x000b4f48   (est. cL4_vtable_call_b0)
 * Ghidra: undefined FUN_000b4f48(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0xb0 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_b0(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0xb0))(); */
}

/* FUN_000b4f9c @ 0x000b4f9c   (est. cL4_field_get_ptr_20)
 * Ghidra: undefined1 [16] FUN_000b4f9c(void)
 * Getter returning a {type-word, pointer} pair for the field at x20+0x20.
 * Lo word is DAT_0007bf58 type tag.
 * Confidence: low
 * Notes: DAT_0007bf58. */
cl4_res2_t cL4_field_get_ptr_20(void)
{
    cl4_res2_t out;
    cL4_glue_9455c(0);          /* x20+0x20 */
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x20 */
    return out;
}

/* FUN_000b4fe0 @ 0x000b4fe0   (est. cL4_field_get_byte_28)
 * Ghidra: undefined1 FUN_000b4fe0(void)
 * Getter returning the byte field at x20+0x28 after a scoped update.
 * Confidence: medium */
uint8_t cL4_field_get_byte_28(void)
{
    cL4_glue_84100(0);          /* x20+0x28 */
    return 0;                   /* *(byte*)(x20+0x28) */
}

/* FUN_000b5008 @ 0x000b5008   (est. cL4_field_get_ptr_28b)
 * Ghidra: undefined1 [16] FUN_000b5008(void)
 * Getter returning a {type-word, pointer} pair for the field at x20+0x28
 * after FUN_000ba418 + FUN_0009455c.
 * Confidence: low */
cl4_res2_t cL4_field_get_ptr_28b(void)
{
    cl4_res2_t out;
    cL4_oh_ba418();
    cL4_glue_9455c();
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x28 */
    return out;
}

/* FUN_000b5048 @ 0x000b5048   (est. cL4_vtable_call_e0)
 * Ghidra: undefined FUN_000b5048(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0xe0 of *param_2 with the two words
 * from param_1, releasing the second word reference first.
 * Confidence: low */
void cL4_vtable_call_e0(uint64_t *a, uint64_t *b)
{
    uint64_t w0 = a[0];
    uint64_t w1 = a[1];
    cL4_retain(w1);
    /* (**(b[0] + 0xe0))(w0, w1); */
}

/* FUN_000b50b0 @ 0x000b50b0   (est. cL4_field_get16_30)
 * Ghidra: undefined1 [16] FUN_000b50b0(void)
 * Getter returning the 16-byte value at x20+0x30 after a scoped update,
 * releasing the value at x20+0x38.
 * Confidence: low */
cl4_res2_t cL4_field_get16_30(void)
{
    cl4_res2_t out;
    cL4_glue_84100(0);          /* x20+0x30 */
    out = (cl4_res2_t){ .lo = 0, .hi = 0 };  /* *(x20+0x30) */
    cL4_retain(0);              /* *(x20+0x38) */
    return out;
}

/* FUN_000b50f0 @ 0x000b50f0   (est. cL4_bundle_swap2_30)
 * Ghidra: undefined FUN_000b50f0(void)
 * Rotates two object fields at x20+0x30/x20+0x38: scoped update, stores
 * x21/x19, releases the old x20+0x38.
 * Confidence: low
 * Notes: unaff_x19/x20/x21 carries. */
void cL4_bundle_swap2_30(void)
{
    cL4_glue_8409c();
    cL4_glue_8e3b0(0);
    uint64_t old = 0;           /* *(x20+0x38) */
    /* *(x20+0x30)=x21; *(x20+0x38)=x19; */
    cL4_release_lo(old);
}

/* FUN_000b5134 @ 0x000b5134   (est. cL4_vtable_call_f8)
 * Ghidra: undefined FUN_000b5134(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0xf8 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_f8(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0xf8))(); */
}

/* FUN_000b5188 @ 0x000b5188   (est. cL4_field_get_release_40)
 * Ghidra: undefined FUN_000b5188(void)
 * Getter for the field at x20+0x40: scoped update then release the field.
 * Confidence: low */
void cL4_field_get_release_40(void)
{
    cL4_glue_84100(0);          /* x20+0x40 */
    cL4_retain(0);              /* *(x20+0x40) */
}

/* FUN_000b51b4 @ 0x000b51b4   (est. cL4_field_set_40)
 * Ghidra: undefined FUN_000b51b4(undefined8)
 * Setter for the object field at x20+0x40: scoped update, store value,
 * release the old value.
 * Confidence: medium */
void cL4_field_set_40(uint64_t value)
{
    cL4_glue_8e3b0(0);
    uint64_t old = 0;           /* *(x20+0x40) */
    /* *(x20+0x40) = value; */
    cL4_release_lo(old);
}

/* FUN_000b51f0 @ 0x000b51f0   (est. cL4_bundle_component_make)
 * Ghidra: undefined8 FUN_000b51f0(void)
 * Allocates a fresh bundle component object: begins a scoped update
 * (FUN_000867b4), allocates the object (FUN_0036a940) and initialises it
 * via FUN_000b5220. Returns the new object.
 * Confidence: medium */
uint64_t cL4_bundle_component_make(void)
{
    uint64_t obj;
    cL4_glue_867b4();
    obj = cL4_alloc();
    cL4_bundle_component_init();
    return obj;
}

/* FUN_000b5220 @ 0x000b5220   (est. cL4_bundle_component_init)
 * Ghidra: undefined FUN_000b5220(void)
 * Initialises a bundle component object at x20: sets up a name string
 * (via FUN_001f0130 + DAT_00657778), a "NAME" tagged constant
 * (0xec000000454d414e), a type string, and allocates a sub-object linked at
 * x20+0x48.
 * Confidence: medium
 * Notes: DAT_00657778 string table; 0xec000000454d414e ("NAME");
 *   FUN_000ba3c0/FUN_001f0130/FUN_000773f0/FUN_00002834/FUN_0006f70c. */
void cL4_bundle_component_init(void)
{
    uint64_t name;
    /* *(x20+0x10) = 0; */
    name = cL4_oh_ba3c0();
    name = cL4_str_1f0130(0, 0x6753a0, name, 0x66dfb8);  /* &DAT_00657778 */
    /* *(x20+0x18) = name; */
    /* *(x20+0x20) = &DAT_00657778; */
    /* *(byte*)(x20+0x28) = 0; */
    cL4_oh_ba4b4();
    /* *(x20+0x30) = extra; */
    /* *(x20+0x38) = 0xec000000454d414eull; */
    name = cL4_str_1f0130(0, 0x6753a0, 0x661168, 0x66dfb8);
    /* *(x20+0x40) = name; */
    cL4_glue_773f0(0);
    cL4_boot_2834();
    /* obj = cL4_alloc(); cL4_glue_6f70c(); name=cL4_str_1f0130(0); */
    /* obj[+0x10]=name; obj[+0x18]=&DAT_00657778; */
    /* *(x20+0x48) = obj; */
}

/* FUN_000b52e8 @ 0x000b52e8   (est. cL4_bundle_component_init_with)
 * Ghidra: undefined8 FUN_000b52e8(7 args)
 * Allocates a fresh bundle component object and initialises its fields
 * from the seven arguments via FUN_000b5368. Returns the new object.
 * Confidence: medium */
uint64_t cL4_bundle_component_init_with(uint64_t a, uint64_t b, uint64_t c,
                                        uint64_t d, uint64_t e, uint64_t f,
                                        uint64_t g)
{
    uint64_t obj;
    cL4_glue_867b4();
    obj = cL4_alloc();
    cL4_bundle_component_fill(a, b, c, d, e, f, g);
    return obj;
}

/* FUN_000b5368 @ 0x000b5368   (est. cL4_bundle_component_fill)
 * Ghidra: undefined FUN_000b5368(7 args)
 * Fills a bundle component object's fields from the seven arguments,
 * releasing each previously-held value. Mirrors FUN_000b5220's structure
 * then stores param_1..param_7 into fields +0x10..+0x40.
 * Confidence: medium
 * Notes: FUN_0007c0e0 save/restore around each store; DAT_00657778. */
void cL4_bundle_component_fill(uint64_t a, uint64_t b, uint64_t c, uint8_t d,
                               uint64_t e, uint64_t f, uint64_t g)
{
    /* mirror of cL4_bundle_component_init field setup: */
    /* *(x20+0x10)=0; name=cL4_oh_ba3c0(); *(x20+0x18)=
       cL4_str_1f0130(0,0x6753a0,name,0x66dfb8); *(x20+0x20)=&DAT_00657778;
       *(x20+0x28)=0; *(x20+0x38)=0xec000000454d414e; cL4_oh_ba4b4();
       *(x20+0x30)=extra; *(x20+0x40)=cL4_str_1f0130(0,0x6753a0,0x661168,0x66dfb8);
       cL4_glue_773f0(0); cL4_boot_2834(); obj=cL4_alloc(); cL4_glue_6f70c();
       *(obj+0x10)=cL4_str_1f0130(0); *(obj+0x18)=&DAT_00657778;
       *(x20+0x48)=obj; */
    /* then set each field from a..g with release of prior value: */
    /* *(x20+0x10)=a; */
    /* *(x20+0x18)=b; release old; */
    /* *(x20+0x20)=c; cL4_release(old); */
    /* *(x20+0x28)=d; */
    /* *(x20+0x30)=e; *(x20+0x38)=f; release old; */
    /* *(x20+0x40)=g; release old; */
}

/* FUN_000b551c @ 0x000b551c   (est. cL4_vtable_call_120)
 * Ghidra: undefined FUN_000b551c(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x120 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_120(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0x120))(); */
}

/* FUN_000b5578 @ 0x000b5578   (est. cL4_field_get_release_48)
 * Ghidra: undefined FUN_000b5578(void)
 * Getter for the field at x20+0x48: scoped update then retain+release.
 * Confidence: low */
void cL4_field_get_release_48(void)
{
    cL4_glue_84100(0);          /* x20+0x48 */
    cL4_retain(0);              /* *(x20+0x48) */
}

/* FUN_000b55a4 @ 0x000b55a4   (est. cL4_field_set_48)
 * Ghidra: undefined FUN_000b55a4(void)
 * Setter for the object field at x20+0x48: scoped update, store x19,
 * release the old value.
 * Confidence: low
 * Notes: FUN_000ba488 + FUN_0008e3b0. */
void cL4_field_set_48(void)
{
    cL4_oh_ba488();
    cL4_glue_8e3b0();
    uint64_t old = 0;           /* *(x20+0x48) */
    /* *(x20+0x48) = x19; */
    cL4_release(old);
}

/* FUN_000b55dc @ 0x000b55dc   (est. cL4_field_get_ptr_48)
 * Ghidra: undefined1 [16] FUN_000b55dc(void)
 * Getter returning a {type-word, pointer} pair for the field at x20+0x48.
 * Lo word is DAT_0007bf58 type tag.
 * Confidence: low */
cl4_res2_t cL4_field_get_ptr_48(void)
{
    cl4_res2_t out;
    cL4_oh_ba488();
    cL4_glue_9455c();
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x48 */
    return out;
}

/* FUN_000b561c @ 0x000b561c   (est. cL4_component_fields_release)
 * Ghidra: undefined FUN_000b561c(void)
 * Releases the five reference-holding fields of a bundle component object
 * (x20+0x18, +0x20, +0x38, +0x40, +0x48), keeping +0x10/+0x30.
 * Confidence: medium */
void cL4_component_fields_release(void)
{
    cL4_release_lo(0);          /* *(x20+0x18) */
    cL4_release(0);             /* *(x20+0x20) */
    cL4_release_lo(0);          /* *(x20+0x38) */
    cL4_release_lo(0);          /* *(x20+0x40) */
    cL4_release(0);             /* *(x20+0x48) */
}

/* FUN_000b565c @ 0x000b565c   (est. cL4_component_release_finish)
 * Ghidra: undefined FUN_000b565c(void)
 * Releases a component's reference fields then runs the scoped teardown
 * (FUN_000867b4 + FUN_0036b6ac).
 * Confidence: medium */
void cL4_component_release_finish(void)
{
    cL4_component_fields_release();
    cL4_glue_867b4();
    cL4_finish();
}

/* FUN_000b5660 @ 0x000b5660   (est. cL4_component_release_finish_2)
 * Ghidra: undefined FUN_000b5660(void)
 * Identical to FUN_000b565c: release fields then teardown.
 * Confidence: medium */
void cL4_component_release_finish_2(void)
{
    cL4_component_fields_release();
    cL4_glue_867b4();
    cL4_finish();
}

/* FUN_000b567c @ 0x000b567c   (est. cL4_vtable_call_70)
 * Ghidra: undefined FUN_000b567c(void)
 * Invokes the vtable method at offset +0x70 of the current object.
 * Confidence: low
 * Notes: (**(*(*x20)+0x70))(). */
void cL4_vtable_call_70(void)
{
    /* (**(*(*x20)+0x70))(); */
}

/* FUN_000b56b8 @ 0x000b56b8   (est. cL4_vtable_call_78)
 * Ghidra: undefined FUN_000b56b8(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x78 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_78(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0x78))(); */
}

/* FUN_000b570c @ 0x000b570c   (est. cL4_field_set_10_ref)
 * Ghidra: undefined FUN_000b570c(void)
 * Setter for the object field at x20+0x10: scoped update, store x19,
 * release the old value.
 * Confidence: low
 * Notes: FUN_000ba424 + FUN_0008e3b0. */
void cL4_field_set_10_ref(void)
{
    cL4_oh_ba424();
    cL4_glue_8e3b0();
    uint64_t old = 0;           /* *(x20+0x10) */
    /* *(x20+0x10) = x19; */
    cL4_release(old);
}

/* FUN_000b5744 @ 0x000b5744   (est. cL4_vtable_call_90)
 * Ghidra: undefined FUN_000b5744(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x90 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_90(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0x90))(); */
}

/* FUN_000b57b0 @ 0x000b57b0   (est. cL4_field_swap_call)
 * Ghidra: undefined FUN_000b57b0(void)
 * Swaps the field at x20+0x18 with x21, then invokes the function pointer
 * held in x19 on the old value.
 * Confidence: low
 * Notes: FUN_0008409c + FUN_0008e3b0 + indirect call. */
void cL4_field_swap_call(void)
{
    cL4_glue_8409c();
    cL4_glue_8e3b0(0);
    uint64_t old = 0;           /* *(x20+0x18) */
    /* *(x20+0x18) = x21; */
    /* (*x19)(old); */
}

/* FUN_000b57f8 @ 0x000b57f8   (est. cL4_field_get_byte_20)
 * Ghidra: undefined1 FUN_000b57f8(void)
 * Getter returning the byte field at x20+0x20 after a scoped update.
 * Confidence: medium */
uint8_t cL4_field_get_byte_20(void)
{
    cL4_glue_84100(0);          /* x20+0x20 */
    return 0;                   /* *(byte*)(x20+0x20) */
}

/* FUN_000b5820 @ 0x000b5820   (est. cL4_field_set_byte_20)
 * Ghidra: undefined FUN_000b5820(undefined1)
 * Setter for the byte field at x20+0x20.
 * Confidence: medium */
void cL4_field_set_byte_20(uint8_t value)
{
    cL4_glue_8e3b0(0);          /* x20+0x20 */
    /* *(byte*)(x20+0x20) = value; */
}

/* FUN_000b5854 @ 0x000b5854   (est. cL4_field_get_byte_21)
 * Ghidra: undefined1 FUN_000b5854(void)
 * Getter returning the byte field at x20+0x21 after a scoped update.
 * Confidence: medium */
uint8_t cL4_field_get_byte_21(void)
{
    cL4_glue_84100(0);          /* x20+0x21 */
    return 0;                   /* *(byte*)(x20+0x21) */
}

/* FUN_000b587c @ 0x000b587c   (est. cL4_field_set_byte_21)
 * Ghidra: undefined FUN_000b587c(undefined1)
 * Setter for the byte field at x20+0x21.
 * Confidence: medium */
void cL4_field_set_byte_21(uint8_t value)
{
    cL4_glue_8e3b0(0);          /* x20+0x21 */
    /* *(byte*)(x20+0x21) = value; */
}

/* FUN_000b58b0 @ 0x000b58b0   (est. cL4_field_get_ptr_byte_21)
 * Ghidra: undefined1 [16] FUN_000b58b0(void)
 * Getter returning a {type-word, pointer} pair for the byte field at
 * x20+0x21. Lo word is DAT_0007bf58 type tag.
 * Confidence: low */
cl4_res2_t cL4_field_get_ptr_byte_21(void)
{
    cl4_res2_t out;
    cL4_glue_9455c(0);          /* x20+0x21 */
    out.lo = 0;                 /* &DAT_0007bf58 */
    out.hi = 0;                 /* x20+0x21 */
    return out;
}

/* FUN_000b58f4 @ 0x000b58f4   (est. cL4_vtable_call_d8)
 * Ghidra: undefined FUN_000b58f4(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0xd8 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_d8(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0xd8))(); */
}

/* FUN_000b5948 @ 0x000b5948   (est. cL4_field_get_release_28)
 * Ghidra: undefined FUN_000b5948(void)
 * Getter for the field at x20+0x28: scoped update then retain+release.
 * Confidence: low */
void cL4_field_get_release_28(void)
{
    cL4_glue_84100(0);          /* x20+0x28 */
    cL4_retain(0);              /* *(x20+0x28) */
}

/* FUN_000b5974 @ 0x000b5974   (est. cL4_field_set_28_ref)
 * Ghidra: undefined FUN_000b5974(void)
 * Setter for the object field at x20+0x28: scoped update, store x19,
 * release the old value.
 * Confidence: low
 * Notes: FUN_000ba418 + FUN_0008e3b0. */
void cL4_field_set_28_ref(void)
{
    cL4_oh_ba418();
    cL4_glue_8e3b0();
    uint64_t old = 0;           /* *(x20+0x28) */
    /* *(x20+0x28) = x19; */
    cL4_release(old);
}

/* FUN_000b59ac @ 0x000b59ac   (est. cL4_vtable_get16_e8)
 * Ghidra: undefined FUN_000b59ac(undefined1 (*)[16], undefined8 *, undefined8, undefined1)
 * Invokes the vtable method at offset +0xe8 of *param_2, storing the
 * 16-byte result into *param_1 and setting param_1[1][0] to param_4.
 * Confidence: low */
void cL4_vtable_get16_e8(cl4_res2_t *out, uint64_t *b, uint64_t c, uint8_t d)
{
    cl4_res2_t r = (cl4_res2_t){ .lo = 0, .hi = 0 };  /* (**(b[0] + 0xe8))() */
    out[0] = r;
    out[1].lo = d;
}

/* FUN_000b59f4 @ 0x000b59f4   (est. cL4_vtable_call3_f0)
 * Ghidra: undefined FUN_000b59f4(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0xf0 of *param_2 with three
 * arguments read from param_1 (two words + one byte).
 * Confidence: low */
void cL4_vtable_call3_f0(uint64_t *a, uint64_t *b)
{
    /* (**(b[0] + 0xf0))(a[0], a[1], *(byte*)(a+2)); */
}

/* FUN_000b5a40 @ 0x000b5a40   (est. cL4_field_get16_30b)
 * Ghidra: undefined1 [16] FUN_000b5a40(void)
 * Getter returning the 16-byte value at x20+0x30 after a scoped update.
 * Confidence: low */
cl4_res2_t cL4_field_get16_30b(void)
{
    cL4_glue_84100(0);          /* x20+0x30 */
    return (cl4_res2_t){ .lo = 0, .hi = 0 };  /* *(x20+0x30) */
}

/* FUN_000b5a6c @ 0x000b5a6c   (est. cL4_field_set3_30)
 * Ghidra: undefined FUN_000b5a6c(undefined8, undefined8, undefined1)
 * Setter storing three fields at x20+0x30 (two words + one byte) after a
 * scoped update.
 * Confidence: medium */
void cL4_field_set3_30(uint64_t a, uint64_t b, uint8_t c)
{
    cL4_glue_8e3b0(0);          /* x20+0x30 */
    /* *(x20+0x30)=a; *(x20+0x38)=b; *(byte*)(x20+0x40)=c; */
}

/* FUN_000b5ab4 @ 0x000b5ab4   (est. cL4_vtable_call_108)
 * Ghidra: undefined FUN_000b5ab4(undefined8 *, undefined8 *)
 * Invokes the vtable method at offset +0x108 of *param_2, retaining *param_1.
 * Confidence: low */
void cL4_vtable_call_108(uint64_t *a, uint64_t *b)
{
    cL4_retain(a[0]);
    /* (**(b[0] + 0x108))(); */
}

/* FUN_000b5b10 @ 0x000b5b10   (est. cL4_bundle_item_make)
 * Ghidra: undefined8 FUN_000b5b10(4 args)
 * Allocates a fresh bundle item object and initialises it via FUN_000b5b94
 * with the resolved pair from FUN_000ba494 plus the last two arguments.
 * Returns the new object.
 * Confidence: medium */
uint64_t cL4_bundle_item_make(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    cl4_res2_t pair;
    uint64_t obj;
    pair = cL4_oh_ba494();
    cL4_glue_867b4();
    obj = cL4_alloc();
    cL4_bundle_item_init(pair.lo, pair.hi, c, d);
    return obj;
}

/* FUN_000b5b94 @ 0x000b5b94   (est. cL4_bundle_item_init)
 * Ghidra: undefined FUN_000b5b94(undefined8, undefined8, undefined1, undefined8)
 * Initialises a bundle item object at x20: stores the name pair, a type
 * byte (param_3), a value (param_4), and the two source words, then fills
 * the linked sub-list. Resets most fields first.
 * Confidence: low
 * Notes: FUN_000ba494 + FUN_0007c0e0 + register carries (unaff_x19..x23). */
void cL4_bundle_item_init(uint64_t a, uint64_t b, uint8_t c, uint64_t d)
{
    uint64_t name = cL4_oh_ba494().lo;
    /* *(x20+0x38)=0; *(x20+0x30)=0; *(byte*)(x20+0x40)=1;
       *(x20+0x10)=0; *(x20+0x18)=name; *(x20+0x48)=0;
       *(byte*)(x20+0x20)=w1; *(byte*)(x20+0x21)=c; *(x20+0x28)=d;
       FUN_0007c0e0(x20+0x30); *(x20+0x30)=x23; *(x20+0x38)=x22;
       *(byte*)(x20+0x40)=w21; FUN_0007c0e0(x20+0x48); *(x20+0x48)=x19; */
}

/* FUN_000b5c2c @ 0x000b5c2c   (est. cL4_asset_make)
 * Ghidra: undefined8 FUN_000b5c2c(void)
 * Allocates a fresh bundle asset object (FUN_0036a940) and initialises it
 * via FUN_000b5c5c. Returns the new object.
 * Confidence: medium */
uint64_t cL4_asset_make(void)
{
    uint64_t obj;
    cL4_glue_867b4();
    obj = cL4_alloc();
    cL4_asset_init();
    return obj;
}

/* FUN_000b5c5c @ 0x000b5c5c   (est. cL4_asset_init)
 * Ghidra: undefined FUN_000b5c5c(void)
 * Initialises a bundle asset object at x20: clears fields +0x30/+0x38,
 * sets +0x40 byte to 1, clears +0x48, runs FUN_000a6f68 to set +0x10 and
 * +0x18/+0x28, and clears +0x20. Finalises the linked sub-list.
 * Confidence: low
 * Notes: FUN_000a6f68 + FUN_0007c0e0. */
void cL4_asset_init(void)
{
    /* *(x20+0x30)=0; *(x20+0x38)=0; *(byte*)(x20+0x40)=1; *(x20+0x48)=0;
       cL4_glue_a6f68(); *(x20+0x10)=0; *(x20+0x18)=extra;
       *(short*)(x20+0x20)=0; *(x20+0x28)=extra;
       FUN_0007c0e0(x20+0x30); *(x20+0x38)=0; *(x20+0x30)=0;
       *(byte*)(x20+0x40)=1; FUN_0007c0e0(x20+0x48); *(x20+0x48)=0; */
}

/* FUN_000b5ce0 @ 0x000b5ce0   (est. cL4_bundle_debug_report)
 * Ghidra: undefined FUN_000b5ce0(void)
 * Prints a human-readable report of a bundle: header line, "Is Debug:
 * true/false", a "Component" count line, then iterates the bundle's
 * components (vtable +0x88) printing each component's segment/type details
 * and sizes, and finally the "Assets" list (vtable +0xd0) printing each
 * asset's id and size.
 * Confidence: medium
 * Notes: tagged strings: "Is Debug: " (0x7562654420734909/0xeb00000000203a67),
 *   "Component" (0x656e6f706d6f4309/0xec0000003a73746e),
 *   "Assets" (0x3a73746573734109/0xe800000000000000),
 *   "true"/"false" (0x65757274 / 0x65736c6166);
 *   FUN_002a4ab4(0x2f)/(0x23); thunk_FUN_002acbb8; FUN_001bc440(0x909090a2c). */
void cL4_bundle_debug_report(void)
{
    uint64_t tmp = cL4_boot_2534(0, 0);       /* &DAT_0064c040, &DAT_004bbf40 */
    long rec = (long)cL4_alloc2(tmp, 0);
    /* rec[+0x18] = uRam004baeb8; rec[+0x10] = _DAT_004baeb0;
       rec[+0x38] = 0x6753a0; rec[+0x20] = 0x7020656c646e7542 ("Bundle p");
       rec[+0x28] = 0xee003a2073706f72 ("ros: "); */
    cL4_boot_2804();
    /* FUN_0036b588(rec); */
    cL4_boot_2688();
    cL4_boot_2834();
    cL4_finish();

    /* "Is Debug: true/false" line */
    rec = (long)cL4_alloc2(tmp, 0);
    cL4_oh_ba448();
    /* print "Is Debug: " + true/false via FUN_002acbb8; release; set rec fields;
       cL4_boot_2804(rec); FUN_0036b588(rec); cL4_boot_2688(); cL4_boot_2834();
       cL4_finish(); */

    /* "Component" count line */
    tmp = cL4_alloc2(tmp, 0);
    rec = (long)cL4_oh_ba448();
    /* rec[+0x38]=0x6753a0; rec[+0x20]=0x656e6f706d6f4309 ("Component");
       rec[+0x28]=0xec0000003a73746e ("nt:"); cL4_boot_2804(); FUN_0036b588(tmp);
       cL4_boot_2688(); cL4_boot_2834(); cL4_finish(); */

    /* iterate components list (vtable +0x88): each element has vtable
       +0xd8 (name) and +0x78 (id); print per-element detail + size via
       vtable +0x90 and FUN_000a5c1c; emit FUN_001bc440(0x909090a2c,...)
       and the "size" tag; */
    /* iterate assets list (vtable +0xd0): each element vtable +0x70 (name)
       and +0x58 (id); emit per-asset id (vtable +0xa0) + size via
       FUN_001ebfb0, tag "; size:0"; */
}

/* FUN_000b62fc @ 0x000b62fc   (est. cL4_container_fields_release)
 * Ghidra: undefined FUN_000b62fc(void)
 * Releases the four reference fields of a container object at x20+0x10,
 * +0x18, +0x28 and +0x48.
 * Confidence: medium */
void cL4_container_fields_release(void)
{
    cL4_release(0);             /* *(x20+0x10) */
    cL4_release(0);             /* *(x20+0x18) */
    cL4_release(0);             /* *(x20+0x28) */
    cL4_release(0);             /* *(x20+0x48) */
}

/* FUN_000b6334 @ 0x000b6334   (est. cL4_container_release_finish)
 * Ghidra: undefined FUN_000b6334(void)
 * Releases a container's reference fields then runs the scoped teardown
 * (FUN_000867b4 + FUN_0036b6ac).
 * Confidence: medium */
void cL4_container_release_finish(void)
{
    cL4_container_fields_release();
    cL4_glue_867b4();
    cL4_finish();
}

/* FUN_000b6338 @ 0x000b6338   (est. cL4_container_release_finish_2)
 * Ghidra: undefined FUN_000b6338(void)
 * Identical to FUN_000b6334: release fields then teardown.
 * Confidence: medium */
void cL4_container_release_finish_2(void)
{
    cL4_container_fields_release();
    cL4_glue_867b4();
    cL4_finish();
}

/* FUN_000b6354 @ 0x000b6354   (est. cL4_bundle_type)
 * Ghidra: undefined8 FUN_000b6354(void)
 * Classifies a bundle by its tagged name string: "SYSTEM" (0x4d4554535953,
 * tag 0xe6) returns 0, "AP" (0x5041, tag 0xe3) returns 1, "LIB" (0x42494c,
 * tag 0xe3) returns 2. Any other name is a fatal error
 * ("Fatal error"/InternalExclaveLauncher.BundleDescriptor). Uses
 * thunk_FUN_0013ccf4 to fetch the string and FUN_002a0cf8 to match tags.
 * Confidence: high
 * Notes: string tags 0x4d4554535953/0x5041/0x42494c; fatal FUN_001afa84
 *   with s_Fatal_error_005accd0 and s_InternalExclaveLauncher_BundleDE_005c27c0. */
uint64_t cL4_bundle_type(void)
{
    cl4_res2_t name;
    uint64_t tag;
    uint64_t ok;

    name = cL4_str_13ccf4();
    tag = name.hi;
    if ((name.lo == 0x4d4554535953ull && tag == 0xe600000000000000ull) ||
        ((ok = cL4_dispatch(0x4d4554535953ull, 0xe600000000000000ull,
                            name.lo, tag, 0)) & 1) != 0) {
        return 0;
    }
    if ((name.lo == 0x5041ull && tag == 0xe300000000000000ull) ||
        ((ok = cL4_dispatch(0x5041ull, 0xe300000000000000ull,
                            name.lo, tag, 0)) & 1) != 0) {
        return 1;
    }
    if (name.lo != 0x42494cull || tag != 0xe300000000000000ull) {
        ok = cL4_dispatch(0x42494cull, 0xe300000000000000ull, name.lo, tag, 0);
        cL4_release_lo(tag);
        if ((ok & 1) != 0) {
            return 2;
        }
        /* FUN_001afa84 fatal "Fatal error" 0xd000000000000012
           s_InternalExclaveLauncher_BundleDE_005c27c0, 0x37, 2, 0xd7 */
        for (;;) { }
    }
    cL4_release_lo(tag);
    return 2;
}

/* FUN_000b64b4 @ 0x000b64b4   (est. cL4_bundle_validate)
 * Ghidra: bool FUN_000b64b4(long *)
 * Validates a bundle/container: fetches its component list (vtable +0xd0),
 * checks it is non-empty (else returns true), then iterates the elements
 * verifying that each element's id (vtable +0x88) equals the first's id and
 * accumulating each element's size (vtable +0xa0), panicking on overflow
 * (SoftwareBreakpoint 0xb6634/0xb6630/0xb65f8). Returns true if the list
 * was empty, false if element ids diverge.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0xb6634/0xb6630/0xb65f8) bounds/overflow
 *   checks; FUN_0036b270/0036b118 retain/release. */
bool cL4_bundle_validate(long *self)
{
    /* vtable dispatch: the object's vtable pointer is self[0]; slot
       offsets below are from the decompiled indirect calls. */
    typedef uint64_t (*slot0_fn)(void);
    slot0_fn get_list = *(slot0_fn *)((char *)self[0] + 0xd0);
    typedef uint64_t (*slot1_fn)(void);
    slot1_fn get_id   = *(slot1_fn *)((char *)0 + 0x88);  /* element slot */
    long list;
    long *elem;
    uint64_t first_id;
    uint64_t id;
    uint64_t size;
    uint64_t sum;
    uint64_t i;
    bool equal;

    list = (long)get_list();
    /* decompiler shows a second fetch producing lVar2 = *(list+0x10) */
    cL4_release();
    if (*(long *)(list + 0x10) == 0) {
        return true;
    }
    list = (long)get_list();
    if (*(long *)(list + 0x10) == 0) {
        /* SoftwareBreakpoint(1,0xb6634) — does not return */
        for (;;) { }
    }
    elem = *(long **)(list + 0x20);
    cL4_retain(elem);
    cL4_release(list);
    first_id = (*(slot1_fn *)((char *)elem[0] + 0x88))();
    cL4_release(elem);
    list = (long)get_list();
    sum = 0;
    i = *(uint64_t *)(list + 0x10);
    while (equal = (i == sum), !equal) {
        if (*(uint64_t *)(list + 0x10) <= sum) {
            /* SoftwareBreakpoint(1,0xb6630) — does not return */
            for (;;) { }
        }
        elem = *(long **)(list + sum * 8 + 0x20);
        cL4_retain(elem);
        id = (*(slot1_fn *)((char *)elem[0] + 0x88))();
        if (first_id != id) {
            cL4_release(elem);
            break;
        }
        sum = sum + 1;
        size = (*(slot1_fn *)((char *)elem[0] + 0xa0))();
        cL4_release(elem);
        equal = __builtin_add_overflow(first_id, size, &first_id);
        if (equal) {
            /* SoftwareBreakpoint(1,0xb65f8) — does not return */
            for (;;) { }
        }
    }
    cL4_release(list);
    return equal;
}

/* FUN_000b6634 @ 0x000b6634   (est. cL4_bundle_build)
 * Ghidra: long * FUN_000b6634(long, undefined8, uint, undefined8, undefined8)
 * The central bundle builder. Allocates an output bundle container, fills
 * its component list from the input bundle descriptor, resolves each
 * component's resources (segment tables, page mappings via
 * cL4_bundle_type/cL4_bundle_process/cL4_bundle_attach), accumulates an
 * asset/component summary, and validates the result with cL4_bundle_validate.
 * Returns the assembled bundle container.
 * Confidence: low (very large; decompiler dropped an unreachable block at
 *   0xb7178 and several SoftwareBreakpoint bounds checks)
 * Notes: FUN_000b5c5c/FUN_000b5220/FUN_000b8ca0/FUN_000b71c4/FUN_000b788c/
 *   FUN_000b6354/FUN_000b64b4; tagged strings "TTP"/"TYP"/"SLAS"_/"DEBUDG";
 *   SoftwareBreakpoint(1,0xb7140..0xb716c) bounds checks. */
long *cL4_bundle_build(long desc, uint64_t a, uint32_t b, uint64_t c,
                        uint64_t d)
{
    long *out = (long *)cL4_alloc(0x650bf8, 0x50, 7);
    /* build output container; iterate descriptor component table; for each
       component resolve segment + type + entity via cL4_bundle_type and the
       tagged finder FUN_0006ae9c on "TTP"/"TYP"; emit into the output's
       component list; then process resources and assets; */
    return out;
}

/* FUN_000b71c4 @ 0x000b71c4   (est. cL4_bundle_process)
 * Ghidra: undefined FUN_000b71c4(undefined8 *, undefined8 *, undefined8, undefined8, uint, undefined8, undefined8)
 * Walks a resource bitmap/list, resolving each entry's tag ("SYSTEM",
 * "OFF"/"SZ") into a mapped segment via cL4_vspace_walk_plus/minus and
 * accumulating the results; then walks a second bitmap (cL4_bundle_attach
 * per entry) to build the final output. Emits a fatal error for an unknown
 * tag ("Fatal error" 0xd00000000000004c).
 * Confidence: low
 * Notes: tagged finder FUN_002abcb0/FUN_002abe60 (0x4f4843414d5f5f,
 *   0x46464f, 0x5a53); cL4_vspace_walk FUN_000b4660/000b4738;
 *   FUN_000b788c; SoftwareBreakpoint(1,0xb7684..0xb768c). */
void cL4_bundle_process(uint64_t *out, uint64_t *list, uint64_t p3,
                        uint64_t p4, uint32_t flag, uint64_t p6, uint64_t p7)
{
    /* iterate entries of *list; for each resolve via cL4_vspace_walk_plus/
       minus and cL4_bundle_attach; unknown tag -> FUN_001afa84 fatal;
       accumulate results; */
}

/* FUN_000b773c @ 0x000b773c   (est. cL4_seq_compare)
 * Ghidra: undefined8 FUN_000b773c(undefined8, undefined8, undefined8, long)
 * Compares two tagged sequences element-by-element via FUN_0029fb80,
 * matching each pair with FUN_002a0cf8. Returns 1 if the sequences are
 * equal (or both exhausted), 0 at the first mismatch.
 * Confidence: medium
 * Notes: FUN_0029fb80 next-element, FUN_002a0cf8 match. */
uint64_t cL4_seq_compare(uint64_t t1, uint64_t s1, uint64_t t2, long s2)
{
    cl4_res2_t e1, e2;
    uint64_t ok;

    cL4_retain(s1);
    cL4_retain(s2);
    for (;;) {
        for (;;) {
            e1 = cL4_seq_29fb80();
            if (e1.hi == 0) {
                cL4_release_lo(s2);
                cL4_seq_29fb80();
                cL4_release_lo(s1);
                s2 = 0;         /* extraout_x1 */
                if (s2 == 0) {
                    return 1;
                }
                goto done;
            }
            e2 = cL4_seq_29fb80();
            if (e2.hi == 0) {
                cL4_release_lo(s1);
                cL4_release_lo(s2);
                cL4_release_lo(e1.hi);
                return 1;
            }
            if (e1.lo != e2.lo || e1.hi != e2.hi) {
                break;
            }
            cL4_release_lo(e1.hi, e2.hi, e2.lo);
            cL4_release_lo(e2.hi);
        }
        ok = cL4_dispatch(e1.lo, e1.hi, e2.lo, e2.hi, 0);
        cL4_release_lo(e1.hi);
        cL4_release_lo(e2.hi);
        if ((ok & 1) == 0) {
            break;
        }
    }
    cL4_release_lo(s1);
done:
    cL4_release_lo(s2);
    return 0;
}

/* FUN_000b788c @ 0x000b788c   (est. cL4_bundle_attach)
 * Ghidra: undefined FUN_000b788c(8 args)
 * Attaches/registers one bundle element into the build result: checks the
 * object's type tag (must be a derBundle2BundleDescriptor container,
 * 0x11000529b94c7909, or a default), then resolves the element via
 * FUN_000a1bd8 and, when it matches, performs the attach/insert using the
 * vtable method from FUN_000ba224/FUN_000ba254/FUN_000ba284 and FUN_0007629c.
 * Confidence: low
 * Notes: tag 0x11000529b94c7909; s_derBundle2BundleDescriptor_derBu_005c2910
 *   panic path (0x126) via FUN_00085374; FUN_00151974/FUN_00151a6c. */
void cL4_bundle_attach(uint64_t out, uint64_t *src, uint64_t *obj, uint64_t *tbl,
                       uint64_t p5, uint32_t flag, uint64_t p7, uint64_t p8)
{
    /* fetch object type (vtable +0x78); if it is the special derBundle2
       container tag, attach the element via FUN_000a1bd8 + the vtable
       method chain and FUN_0007629c; */
}

/* FUN_000b7b94 @ 0x000b7b94   (est. cL4_bundle_segment_log)
 * Ghidra: undefined1 [16] FUN_000b7b94(undefined8 *, undefined8, undefined8)
 * Logs a "segment" message for the given tag pair (thunk_FUN_002acbb8 with
 * 0x746e656d67657320 = "segment ") and returns the empty result
 * {0, 0xe000000000000000}.
 * Confidence: medium
 * Notes: FUN_002a4ab4(0x3d); FUN_002acbb8(0xd000000000000030,...);
 *   FUN_002acbb8(0x746e656d67657320,...). */
cl4_res2_t cL4_bundle_segment_log(uint64_t *obj, uint64_t t1, uint64_t t2)
{
    cL4_log(0x3d);
    cL4_ref_2acbb8(0xd000000000000030ull, 0x80000000005c2a40ull);
    /* (**(*(*obj) + 0xd8))(); */
    cL4_ref_2acbb8(0, 0);       /* auVar3 result pair */
    cL4_release_lo(0);
    cL4_ref_2acbb8(0x746e656d67657320ull, 0xe900000000000020ull); /* "segment " */
    cL4_ref_2acbb8(t1, t2);
    return (cl4_res2_t){ .lo = 0, .hi = 0xe000000000000000ull };
}

/* FUN_000b7c9c @ 0x000b7c9c   (est. cL4_bundle_descriptor_parse)
 * Ghidra: undefined8 FUN_000b7c9c(long, long, 4 args)
 * Parses a BundleDescriptor (derBundle2) into the internal component/asset
 * representation and returns the assembled bundle. Validates input (a
 * non-null descriptor, and a non-null name if the descriptor is non-null),
 * makes a container (FUN_000b8bf4), walks the tagged descriptor tree
 * (type-9 object nodes, type-6 strings, type-1 numbers) extracting the
 * component, asset and resource tables, and hands the result to
 * cL4_bundle_build. Any malformed node triggers a fatal error
 * (FUN_001afa84) with a specific error code (0x16a..0x1ba).
 * Confidence: low (very large; decompiler removed 7 unreachable blocks)
 * Notes: FUN_000b8bf4/FUN_000b6634; s_Assets_in_storage_are_not_contig_
 *   005c2800 / s_ComponentGraph_ASN1_swift_005c2860; fatal FUN_001afa84. */
uint64_t cL4_bundle_descriptor_parse(long desc, long name, uint64_t p3,
                                     uint64_t p4, uint64_t p5, uint64_t p6)
{
    long *container;
    if (desc < 0) {
        /* SoftwareBreakpoint(1,0xb88f4) — does not return */
        for (;;) { }
    }
    if (desc != 0 && name == 0) {
        /* SoftwareBreakpoint(1,0xb890c) — does not return */
        for (;;) { }
    }
    /* args register-carried by the caller in the original binary; pass the
       descriptor/name words we have in hand */
    container = (long *)cL4_bundle_container_make(desc, name);
    /* parse tagged descriptor tree; build component/asset tables; hand to
       cL4_bundle_build and return its result; on any structural error,
       FUN_001afa84 fatal with code 0x16a..0x1ba */
    return 0;
}

/* FUN_000b8bf4 @ 0x000b8bf4   (est. cL4_bundle_container_make)
 * Ghidra: undefined * FUN_000b8bf4(long, long)
 * Returns a bundle-descriptor container: the static empty container
 * DAT_00657778 when param_2 is 0, otherwise allocates a fresh one
 * (FUN_000719dc) and validates its size against param_1/param_2 via
 * FUN_000ba1b4, panicking on a mismatch (SoftwareBreakpoint 0xb8c80/0xb8c88/
 * 0xb8c84/0xb8c54).
 * Confidence: medium
 * Notes: DAT_00657778; FUN_000719dc + FUN_000ba1b4 + SoftwareBreakpoint. */
uint64_t cL4_bundle_container_make(long size1, long size2)
{
    uint64_t cont;
    cl4_res2_t chk;
    if (size2 == 0) {
        return 0;               /* &DAT_00657778 */
    }
    cont = cL4_glue_719dc(size2, 0);
    if (size2 < 0) {
        /* SoftwareBreakpoint(1,0xb8c80) — does not return */
        for (;;) { }
    }
    chk = cL4_oh_ba1b4(cont + 0x20, size2, size1, size2);
    if (chk.lo == 0) {
        if (size1 != size2) {
            /* SoftwareBreakpoint(1,0xb8c88) — does not return */
            for (;;) { }
        }
    } else {
        if (chk.lo != chk.hi) {
            /* SoftwareBreakpoint(1,0xb8c84) — does not return */
            for (;;) { }
        }
        if (size1 != size2) {
            /* SoftwareBreakpoint(1,0xb8c54) — does not return */
            for (;;) { }
        }
    }
    return cont;
}

/* FUN_000b8ca0 @ 0x000b8ca0   (est. cL4_list_sort)
 * Ghidra: undefined FUN_000b8ca0(long *)
 * Sorts/normalises a vector in place: ensures the backing storage has
 * capacity (FUN_003a261c, growing via FUN_0007bebc), then if the count is
 * below the sort threshold (FUN_0029369c) applies an insertion-style sort
 * (FUN_000b9e6c), else a bulk sort (FUN_000b9ac4).
 * Confidence: medium
 * Notes: FUN_003a261c/FUN_0007bebc/FUN_0029369c/FUN_000b9e6c/FUN_000b9ac4. */
void cL4_list_sort(long *vec)
{
    long v;
    uint64_t count;
    v = *vec;
    if ((cL4_glue_3a261c(v) & 1) == 0) {
        v = (long)cL4_glue_7bebc(v);
        *vec = v;
    }
    count = *(uint64_t *)(v + 0x10);
    /* sort the region starting at v+0x20 with `count` elements */
    if (cL4_glue_29369c(count) < (long)count) {
        cL4_glue_9e6c(count >> 1, 0, cL4_glue_29369c(count));
        if (0 == 0) {           /* unaff_x21 carry check */
            cL4_release();
        }
    } else if (count != 0) {
        cL4_glue_9ac4(0, count, 1, 0);
    }
}

/* FUN_000b8d68 @ 0x000b8d68   (est. cL4_vt_get_58)
 * Ghidra: undefined FUN_000b8d68(void)
 * Generic vtable getter: fetches the current object (FUN_0007bf80), calls
 * its vtable slot +0x58 and stores the result in *x19.
 * Confidence: low
 * Notes: extraout_x16 register carry. */
void cL4_vt_get_58(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x58))(); */
}

/* FUN_000b8da0 @ 0x000b8da0   (est. cL4_vt_set_60)
 * Ghidra: undefined FUN_000b8da0(undefined8 *)
 * Generic vtable setter: releases *param_1 (FUN_000ba34c) and calls the
 * object's vtable slot +0x60.
 * Confidence: low */
void cL4_vt_set_60(uint64_t *a)
{
    cL4_oh_ba34c(a[0]);
    /* (**(self + 0x60))(); */
}

/* FUN_000b8dd8 @ 0x000b8dd8   (est. cL4_vt_get16_70)
 * Ghidra: undefined FUN_000b8dd8(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x70 and stores the 16-byte result in *x19.
 * Confidence: low */
void cL4_vt_get16_70(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x70))(); */
}

/* FUN_000b8e14 @ 0x000b8e14   (est. cL4_vt_get_88)
 * Ghidra: undefined FUN_000b8e14(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x88 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_88(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x88))(); */
}

/* FUN_000b8e4c @ 0x000b8e4c   (est. cL4_vt_set_90)
 * Ghidra: undefined FUN_000b8e4c(undefined8 *)
 * Generic vtable setter: releases *param_1 and calls vtable slot +0x90.
 * Confidence: low */
void cL4_vt_set_90(uint64_t *a)
{
    cL4_oh_ba34c(a[0]);
    /* (**(self + 0x90))(); */
}

/* FUN_000b8e84 @ 0x000b8e84   (est. cL4_vt_get_a0)
 * Ghidra: undefined FUN_000b8e84(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0xa0 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_a0(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0xa0))(); */
}

/* FUN_000b8ebc @ 0x000b8ebc   (est. cL4_vt_set_a8)
 * Ghidra: undefined FUN_000b8ebc(undefined8 *)
 * Generic vtable setter: releases *param_1 and calls vtable slot +0xa8.
 * Confidence: low */
void cL4_vt_set_a8(uint64_t *a)
{
    cL4_oh_ba34c(a[0]);
    /* (**(self + 0xa8))(); */
}

/* FUN_000b8ef4 @ 0x000b8ef4   (est. cL4_vt_get_78)
 * Ghidra: undefined FUN_000b8ef4(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x78 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_78(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x78))(); */
}

/* FUN_000b8f2c @ 0x000b8f2c   (est. cL4_vt_set_80)
 * Ghidra: undefined FUN_000b8f2c(undefined8 *)
 * Generic vtable setter: releases *param_1 and calls vtable slot +0x80.
 * Confidence: low */
void cL4_vt_set_80(uint64_t *a)
{
    cL4_oh_ba34c(a[0]);
    /* (**(self + 0x80))(); */
}

/* FUN_000b8f64 @ 0x000b8f64   (est. cL4_vt_get_90b)
 * Ghidra: undefined FUN_000b8f64(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x90 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_90b(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x90))(); */
}

/* FUN_000b8fa0 @ 0x000b8fa0   (est. cL4_vt_get_a8b)
 * Ghidra: undefined FUN_000b8fa0(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0xa8 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_a8b(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0xa8))(); */
}

/* FUN_000b8fdc @ 0x000b8fdc   (est. cL4_vt_get_byte_c0)
 * Ghidra: undefined FUN_000b8fdc(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0xc0 and stores the byte result in *x19.
 * Confidence: low */
void cL4_vt_get_byte_c0(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0xc0))(); */
}

/* FUN_000b9014 @ 0x000b9014   (est. cL4_vt_set_c8)
 * Ghidra: undefined FUN_000b9014(void)
 * Generic vtable setter: releases the current object (FUN_000ba34c) and
 * calls vtable slot +0xc8 with the first byte of *result.
 * Confidence: low */
void cL4_vt_set_c8(void)
{
    /* byte = *((uint8_t*)cL4_oh_ba34c()); */
    /* (**(self + 0xc8))(byte); */
}

/* FUN_000b904c @ 0x000b904c   (est. cL4_vt_get16_d8)
 * Ghidra: undefined FUN_000b904c(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0xd8 and stores the 16-byte result in *x19.
 * Confidence: low */
void cL4_vt_get16_d8(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0xd8))(); */
}

/* FUN_000b9088 @ 0x000b9088   (est. cL4_vt_get_f0)
 * Ghidra: undefined FUN_000b9088(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0xf0 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_f0(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0xf0))(); */
}

/* FUN_000b90c4 @ 0x000b90c4   (est. cL4_vt_get_118)
 * Ghidra: undefined FUN_000b90c4(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x118 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_118(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x118))(); */
}

/* FUN_000b9108 @ 0x000b9108   (est. cL4_vt_get_70b)
 * Ghidra: undefined FUN_000b9108(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x70 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_70b(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x70))(); */
}

/* FUN_000b9144 @ 0x000b9144   (est. cL4_vt_get_88b)
 * Ghidra: undefined FUN_000b9144(void)
 * Generic vtable getter: fetches the current object, calls vtable slot
 * +0x88 and stores the result in *x19.
 * Confidence: low */
void cL4_vt_get_88b(void)
{
    cL4_glue_7bf80();
    /* *x19 = (**(self + 0x88))(); */
}
