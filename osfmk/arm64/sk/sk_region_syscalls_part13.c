/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) -
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 13: 0x34c044-0x34d054 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern; their bodies
 * are reconstructed by the range worker that owns each address).
 * ------------------------------------------------------------------ */
extern void FUN_00310a44(void); /* out of slice */
extern void FUN_00310ad4(void); /* out of slice */
extern void FUN_00310a74(void); /* out of slice */
extern void FUN_003109b4(void); /* out of slice */
extern void FUN_00027754(void); /* out of slice */
extern void FUN_0016186c(void); /* out of slice */
extern void FUN_0008f758(void); /* out of slice */
extern void FUN_0006a4c0(void); /* out of slice */
extern void FUN_00291ee0(void); /* out of slice */
extern void FUN_0014ae44(void); /* out of slice */
extern void FUN_00377bec(uint64_t); /* out of slice */
extern void FUN_000839f8(uint64_t, uint64_t); /* out of slice */
extern void FUN_000a649c(uint64_t); /* out of slice */
extern void FUN_00377824(uint64_t, uint64_t, uint64_t, const void *, const void *); /* out of slice */
extern unsigned char DAT_00611b24[]; /* out of slice (data/string ref) */
extern unsigned char DAT_00611b3c[]; /* out of slice (data/string ref) */

/* Decompiler frame-base helper for recovered frame-slot accesses. */
static inline uint64_t *frame_base(void) { return (uint64_t *)0; }

/* FUN_0034C044 @ 0x0034c044   (est. sk_noop_c044)
 * Ghidra: FUN_0034C044(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c044(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C054 @ 0x0034c054   (est. sk_noop_c054)
 * Ghidra: FUN_0034C054(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c054(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C064 @ 0x0034c064   (est. sk_noop_c064)
 * Ghidra: FUN_0034C064(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c064(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C074 @ 0x0034c074   (est. sk_noop_c074)
 * Ghidra: FUN_0034C074(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c074(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C084 @ 0x0034c084   (est. sk_noop_c084)
 * Ghidra: FUN_0034C084(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c084(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C094 @ 0x0034c094   (est. sk_noop_c094)
 * Ghidra: FUN_0034C094(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c094(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C0A4 @ 0x0034c0a4   (est. sk_noop_c0a4)
 * Ghidra: FUN_0034C0A4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c0a4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C0B4 @ 0x0034c0b4   (est. sk_thunk_00310a44_c0b4)
 * Ghidra: FUN_0034C0B4(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310a44. */
void sk_thunk_00310a44_c0b4(void)
{
FUN_00310a44();
}

/* FUN_0034C0D0 @ 0x0034c0d0   (est. sk_thunk_00310a44_c0d0)
 * Ghidra: FUN_0034C0D0(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310a44. */
void sk_thunk_00310a44_c0d0(void)
{
FUN_00310a44();
}

/* FUN_0034C0EC @ 0x0034c0ec   (est. sk_thunk_00310a44_c0ec)
 * Ghidra: FUN_0034C0EC(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310a44. */
void sk_thunk_00310a44_c0ec(void)
{
FUN_00310a44();
}

/* FUN_0034C108 @ 0x0034c108   (est. sk_ret0_c108)
 * Ghidra: FUN_0034C108(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c108(void)
{
    return 0;
}

/* FUN_0034C11C @ 0x0034c11c   (est. sk_noop_c11c)
 * Ghidra: FUN_0034C11C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c11c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C130 @ 0x0034c130   (est. sk_noop_c130)
 * Ghidra: FUN_0034C130(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c130(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C144 @ 0x0034c144   (est. sk_noop_c144)
 * Ghidra: FUN_0034C144(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c144(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C158 @ 0x0034c158   (est. sk_retff_c158)
 * Ghidra: FUN_0034C158(void) (decompiled empty/const)
 * Returns 0xff (255) - a constant-sentinel helper (e.g. 'no such entry' marker).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_retff_c158(void)
{
    return 0xff;
}

/* FUN_0034C16C @ 0x0034c16c   (est. sk_noop_c16c)
 * Ghidra: FUN_0034C16C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c16c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C180 @ 0x0034c180   (est. sk_noop_c180)
 * Ghidra: FUN_0034C180(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c180(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C194 @ 0x0034c194   (est. sk_noop_c194)
 * Ghidra: FUN_0034C194(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c194(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C1A8 @ 0x0034c1a8   (est. sk_noop_c1a8)
 * Ghidra: FUN_0034C1A8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c1a8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C1BC @ 0x0034c1bc   (est. sk_noop_c1bc)
 * Ghidra: FUN_0034C1BC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c1bc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C1D0 @ 0x0034c1d0   (est. sk_noop_c1d0)
 * Ghidra: FUN_0034C1D0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c1d0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C1E4 @ 0x0034c1e4   (est. sk_ret0_c1e4)
 * Ghidra: FUN_0034C1E4(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c1e4(void)
{
    return 0;
}

/* FUN_0034C1F8 @ 0x0034c1f8   (est. sk_noop_c1f8)
 * Ghidra: FUN_0034C1F8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c1f8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C20C @ 0x0034c20c   (est. sk_ret0_c20c)
 * Ghidra: FUN_0034C20C(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c20c(void)
{
    return 0;
}

/* FUN_0034C220 @ 0x0034c220   (est. sk_noop_c220)
 * Ghidra: FUN_0034C220(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c220(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C234 @ 0x0034c234   (est. sk_noop_c234)
 * Ghidra: FUN_0034C234(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c234(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C244 @ 0x0034c244   (est. sk_noop_c244)
 * Ghidra: FUN_0034C244(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c244(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C258 @ 0x0034c258   (est. sk_noop_c258)
 * Ghidra: FUN_0034C258(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c258(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C26C @ 0x0034c26c   (est. sk_noop_c26c)
 * Ghidra: FUN_0034C26C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c26c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C280 @ 0x0034c280   (est. sk_noop_c280)
 * Ghidra: FUN_0034C280(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c280(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C290 @ 0x0034c290   (est. sk_noop_c290)
 * Ghidra: FUN_0034C290(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c290(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C2A4 @ 0x0034c2a4   (est. sk_noop_c2a4)
 * Ghidra: FUN_0034C2A4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c2a4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C2B4 @ 0x0034c2b4   (est. sk_frame_addr_90)
 * Ghidra: FUN_0034C2B4(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0x90 <- &stack0 - in_x12); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_frame_addr_90(uint64_t in_x12)
{
    /* recovered: *(frame_base-0x90) <- &stack0 - in_x12 */
    return;
}

/* FUN_0034C2C8 @ 0x0034c2c8   (est. sk_noop_c2c8)
 * Ghidra: FUN_0034C2C8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c2c8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C2D8 @ 0x0034c2d8   (est. sk_noop_c2d8)
 * Ghidra: FUN_0034C2D8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c2d8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C2E8 @ 0x0034c2e8   (est. sk_noop_c2e8)
 * Ghidra: FUN_0034C2E8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c2e8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C2F8 @ 0x0034c2f8   (est. sk_store_x9_90)
 * Ghidra: FUN_0034C2F8(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0x90 <- in_x9); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_store_x9_90(void)
{
    /* recovered: *(frame_base-0x90) <- in_x9 */
    return;
}

/* FUN_0034C308 @ 0x0034c308   (est. sk_noop_c308)
 * Ghidra: FUN_0034C308(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c308(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C31C @ 0x0034c31c   (est. sk_noop_c31c)
 * Ghidra: FUN_0034C31C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c31c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C330 @ 0x0034c330   (est. sk_frame_addr_d8)
 * Ghidra: FUN_0034C330(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0xd8 <- &stack0 - param_1); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_frame_addr_d8(uint64_t param_1)
{
    /* recovered: *(frame_base-0xd8) <- &stack0 - param_1 */
    return;
}

/* FUN_0034C344 @ 0x0034c344   (est. sk_noop_c344)
 * Ghidra: FUN_0034C344(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c344(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C354 @ 0x0034c354   (est. sk_ret0_c354)
 * Ghidra: FUN_0034C354(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c354(void)
{
    return 0;
}

/* FUN_0034C368 @ 0x0034c368   (est. sk_thunk_00310a44_c368)
 * Ghidra: FUN_0034C368(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310a44. */
void sk_thunk_00310a44_c368(void)
{
FUN_00310a44();
}

/* FUN_0034C384 @ 0x0034c384   (est. sk_thunk_0008f758_c384)
 * Ghidra: FUN_0034C384(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0008f758. */
void sk_thunk_0008f758_c384(void)
{
FUN_0008f758();
}

/* FUN_0034C3A0 @ 0x0034c3a0   (est. sk_noop_c3a0)
 * Ghidra: FUN_0034C3A0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c3a0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C3B4 @ 0x0034c3b4   (est. sk_stack_ctx_get)
 * Ghidra: FUN_0034C3B4(...)
 * Returns a 16-byte value whose low word is the current stack frame pointer (frame base minus 0x78) and high word zero - a caller-preserved register-pair getter.
 * Confidence: low
 * Notes: decompiler: auVar1._0_8_=unaff_x29-0x78,_8_8_=0; 14 callers. */
cl4_result_t sk_stack_ctx_get(void)
{
cl4_result_t r = { (uint64_t)(frame_base()-0x78), 0 };
    return r;
}

/* FUN_0034C3C4 @ 0x0034c3c4   (est. sk_noop_c3c4)
 * Ghidra: FUN_0034C3C4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c3c4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C3D4 @ 0x0034c3d4   (est. sk_noop_c3d4)
 * Ghidra: FUN_0034C3D4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c3d4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C3E4 @ 0x0034c3e4   (est. sk_noop_c3e4)
 * Ghidra: FUN_0034C3E4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c3e4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C3F4 @ 0x0034c3f4   (est. sk_noop_c3f4)
 * Ghidra: FUN_0034C3F4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c3f4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C404 @ 0x0034c404   (est. sk_noop_c404)
 * Ghidra: FUN_0034C404(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c404(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C414 @ 0x0034c414   (est. sk_noop_c414)
 * Ghidra: FUN_0034C414(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c414(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C424 @ 0x0034c424   (est. sk_noop_c424)
 * Ghidra: FUN_0034C424(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c424(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C434 @ 0x0034c434   (est. sk_word_load)
 * Ghidra: FUN_0034C434(...)
 * Dereferences ptr and returns the loaded word.
 * Confidence: medium
 * Notes: decompiler: return *param_1. */
uint64_t sk_word_load(const uint64_t *ptr)
{
return *ptr;
}

/* FUN_0034C444 @ 0x0034c444   (est. sk_noop_c444)
 * Ghidra: FUN_0034C444(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c444(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C454 @ 0x0034c454   (est. sk_ret0_c454)
 * Ghidra: FUN_0034C454(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c454(void)
{
    return 0;
}

/* FUN_0034C464 @ 0x0034c464   (est. sk_thunk_0016186c_c464)
 * Ghidra: FUN_0034C464(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0016186c. */
void sk_thunk_0016186c_c464(void)
{
FUN_0016186c();
}

/* FUN_0034C480 @ 0x0034c480   (est. sk_thunk_00310ad4_00027754_c480)
 * Ghidra: FUN_0034C480(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310ad4, FUN_00027754. */
void sk_thunk_00310ad4_00027754_c480(void)
{
FUN_00310ad4();; FUN_00027754();
}

/* FUN_0034C49C @ 0x0034c49c   (est. sk_call_with_slot)
 * Ghidra: FUN_0034C49C(...)
 * Calls helper with a word loaded from caller frame slot 0x118.
 * Confidence: low
 * Notes: decompiler: FUN_00377bec(*(x29-0x118)). */
void sk_call_with_slot(void)
{
FUN_00377bec(*(uint64_t*)(frame_base()-0x118));
}

/* FUN_0034C4BC @ 0x0034c4bc   (est. sk_call_flags)
 * Ghidra: FUN_0034C4BC(...)
 * Calls the helper with value and constant 1.
 * Confidence: low
 * Notes: decompiler: FUN_000839f8(param_1,1); 19 callers. */
void sk_call_flags(uint64_t value)
{
FUN_000839f8(value,1);
}

/* FUN_0034C4DC @ 0x0034c4dc   (est. sk_thunk_0006a4c0_c4dc)
 * Ghidra: FUN_0034C4DC(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0006a4c0. */
void sk_thunk_0006a4c0_c4dc(void)
{
FUN_0006a4c0();
}

/* FUN_0034C4FC @ 0x0034c4fc   (est. sk_thunk_00027754_0014ae44_c4fc)
 * Ghidra: FUN_0034C4FC(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00027754, FUN_0014ae44. */
void sk_thunk_00027754_0014ae44_c4fc(void)
{
FUN_00027754();; FUN_0014ae44();
}

/* FUN_0034C51C @ 0x0034c51c   (est. sk_thunk_00291ee0_c51c)
 * Ghidra: FUN_0034C51C(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00291ee0. */
void sk_thunk_00291ee0_c51c(void)
{
FUN_00291ee0();
}

/* FUN_0034C53C @ 0x0034c53c   (est. sk_noop_c53c)
 * Ghidra: FUN_0034C53C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c53c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C54C @ 0x0034c54c   (est. sk_noop_c54c)
 * Ghidra: FUN_0034C54C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c54c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C55C @ 0x0034c55c   (est. sk_ret0_c55c)
 * Ghidra: FUN_0034C55C(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c55c(void)
{
    return 0;
}

/* FUN_0034C56C @ 0x0034c56c   (est. sk_noop_c56c)
 * Ghidra: FUN_0034C56C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c56c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C57C @ 0x0034c57c   (est. sk_noop_c57c)
 * Ghidra: FUN_0034C57C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c57c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C58C @ 0x0034c58c   (est. sk_noop_c58c)
 * Ghidra: FUN_0034C58C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c58c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C59C @ 0x0034c59c   (est. sk_noop_c59c)
 * Ghidra: FUN_0034C59C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c59c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5AC @ 0x0034c5ac   (est. sk_noop_c5ac)
 * Ghidra: FUN_0034C5AC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5ac(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5BC @ 0x0034c5bc   (est. sk_noop_c5bc)
 * Ghidra: FUN_0034C5BC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5bc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5CC @ 0x0034c5cc   (est. sk_noop_c5cc)
 * Ghidra: FUN_0034C5CC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5cc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5DC @ 0x0034c5dc   (est. sk_noop_c5dc)
 * Ghidra: FUN_0034C5DC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5dc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5EC @ 0x0034c5ec   (est. sk_noop_c5ec)
 * Ghidra: FUN_0034C5EC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5ec(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C5FC @ 0x0034c5fc   (est. sk_noop_c5fc)
 * Ghidra: FUN_0034C5FC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c5fc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C60C @ 0x0034c60c   (est. sk_ret0_c60c)
 * Ghidra: FUN_0034C60C(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c60c(void)
{
    return 0;
}

/* FUN_0034C61C @ 0x0034c61c   (est. sk_thunk_00310ad4_00027754_c61c)
 * Ghidra: FUN_0034C61C(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310ad4, FUN_00027754. */
void sk_thunk_0310ad4_00027754(void)
{
FUN_00310ad4();; FUN_00027754();
}

/* FUN_0034C638 @ 0x0034c638   (est. sk_thunk_0016186c_c638)
 * Ghidra: FUN_0034C638(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0016186c. */
void sk_thunk_0016186c(void)
{
FUN_0016186c();
}

/* FUN_0034C654 @ 0x0034c654   (est. sk_ret0_c654)
 * Ghidra: FUN_0034C654(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c654(void)
{
    return 0;
}

/* FUN_0034C664 @ 0x0034c664   (est. sk_noop_c664)
 * Ghidra: FUN_0034C664(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c664(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C674 @ 0x0034c674   (est. sk_noop_c674)
 * Ghidra: FUN_0034C674(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c674(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C684 @ 0x0034c684   (est. sk_store_x9_98)
 * Ghidra: FUN_0034C684(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0x98 <- in_x9); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_store_x9_98(void)
{
    /* recovered: *(frame_base-0x98) <- in_x9 */
    return;
}

/* FUN_0034C694 @ 0x0034c694   (est. sk_noop_c694)
 * Ghidra: FUN_0034C694(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c694(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6A4 @ 0x0034c6a4   (est. sk_noop_c6a4)
 * Ghidra: FUN_0034C6A4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6a4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6B4 @ 0x0034c6b4   (est. sk_noop_c6b4)
 * Ghidra: FUN_0034C6B4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6b4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6C4 @ 0x0034c6c4   (est. sk_noop_c6c4)
 * Ghidra: FUN_0034C6C4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6c4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6D4 @ 0x0034c6d4   (est. sk_noop_c6d4)
 * Ghidra: FUN_0034C6D4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6d4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6E4 @ 0x0034c6e4   (est. sk_noop_c6e4)
 * Ghidra: FUN_0034C6E4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6e4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C6F4 @ 0x0034c6f4   (est. sk_noop_c6f4)
 * Ghidra: FUN_0034C6F4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c6f4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C704 @ 0x0034c704   (est. sk_noop_c704)
 * Ghidra: FUN_0034C704(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c704(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C720 @ 0x0034c720   (est. sk_two_slot_load)
 * Ghidra: FUN_0034C720(...)
 * Loads two words from caller frame slots (base-0x168/-0x198) and returns them as a pair.
 * Confidence: low
 * Notes: decompiler: unaff_x29-0x168/-0x198; caller FUN_00234384. */
cl4_result_t sk_two_slot_load(void)
{
cl4_result_t r = { *(uint64_t*)(frame_base()-0x168), *(uint64_t*)(frame_base()-0x198) };
    return r;
}

/* FUN_0034C738 @ 0x0034c738   (est. sk_noop_c738)
 * Ghidra: FUN_0034C738(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c738(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C754 @ 0x0034c754   (est. sk_store_x9_word)
 * Ghidra: FUN_0034C754(...)
 * Stores value into frame slot x9-0x100 and returns 0.
 * Confidence: low
 * Notes: decompiler: *(in_x9-0x100)=param_1; 16 callers. */
uint64_t sk_store_x9_word(uint64_t value)
{
/* recovered: store value into caller frame slot (x9-0x100) */
    (void)value;
    return 0;
}

/* FUN_0034C764 @ 0x0034c764   (est. sk_copy_9byte)
 * Ghidra: FUN_0034C764(...)
 * Copies an 8-byte word plus a 1-byte tag between 8-byte-aligned addresses.
 * Confidence: medium
 * Notes: copies qword+1 byte; 5 callers in 0x33. */
void sk_copy_9byte(uint64_t dst, uint64_t src)
{
*(uint64_t*)(dst&~7u)=*(uint64_t*)(src&~7u);
    *(uint8_t*)((dst&~7u)+1)=*(uint8_t*)((src&~7u)+1);
}

/* FUN_0034C780 @ 0x0034c780   (est. sk_noop_c780)
 * Ghidra: FUN_0034C780(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c780(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C798 @ 0x0034c798   (est. sk_noop_c798)
 * Ghidra: FUN_0034C798(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c798(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C7A8 @ 0x0034c7a8   (est. sk_noop_c7a8)
 * Ghidra: FUN_0034C7A8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c7a8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C7C4 @ 0x0034c7c4   (est. sk_handle_from_obj)
 * Ghidra: FUN_0034C7C4(...)
 * Builds a 16-byte capability/object descriptor: low word = fixed tag 0x13f (319), high word = object word at +0x10. ~20 vspace/PT callers - consistent with an object handle/ref encode.
 * Confidence: medium
 * Notes: constant 0x13f=319; callers in 0x32-0x34. */
cl4_result_t sk_handle_from_obj(uint64_t obj)
{
cl4_result_t r = { 0x13f, *(uint64_t*)(obj+0x10) };
    return r;
}

/* FUN_0034C7D4 @ 0x0034c7d4   (est. sk_thunk_0008f758_c7d4)
 * Ghidra: FUN_0034C7D4(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0008f758. */
void sk_thunk_0008f758(void)
{
FUN_0008f758();
}

/* FUN_0034C7F0 @ 0x0034c7f0   (est. sk_noop_c7f0)
 * Ghidra: FUN_0034C7F0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c7f0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C800 @ 0x0034c800   (est. sk_noop_c800)
 * Ghidra: FUN_0034C800(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c800(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C818 @ 0x0034c818   (est. sk_noop_c818)
 * Ghidra: FUN_0034C818(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c818(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C828 @ 0x0034c828   (est. sk_ret0_c828)
 * Ghidra: FUN_0034C828(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c828(void)
{
    return 0;
}

/* FUN_0034C840 @ 0x0034c840   (est. sk_noop_c840)
 * Ghidra: FUN_0034C840(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c840(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C858 @ 0x0034c858   (est. sk_noop_c858)
 * Ghidra: FUN_0034C858(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c858(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C870 @ 0x0034c870   (est. sk_noop_c870)
 * Ghidra: FUN_0034C870(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c870(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C888 @ 0x0034c888   (est. sk_noop_c888)
 * Ghidra: FUN_0034C888(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c888(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C8A0 @ 0x0034c8a0   (est. sk_noop_c8a0)
 * Ghidra: FUN_0034C8A0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c8a0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C8B8 @ 0x0034c8b8   (est. sk_noop_c8b8)
 * Ghidra: FUN_0034C8B8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c8b8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C8C8 @ 0x0034c8c8   (est. sk_frame_addr_110)
 * Ghidra: FUN_0034C8C8(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0x110 <- &stack0 - param_1); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_frame_addr_110(uint64_t param_1)
{
    /* recovered: *(frame_base-0x110) <- &stack0 - param_1 */
    return;
}

/* FUN_0034C8E0 @ 0x0034c8e0   (est. sk_noop_c8e0)
 * Ghidra: FUN_0034C8E0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c8e0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C8F8 @ 0x0034c8f8   (est. sk_noop_c8f8)
 * Ghidra: FUN_0034C8F8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c8f8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C908 @ 0x0034c908   (est. sk_noop_c908)
 * Ghidra: FUN_0034C908(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c908(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C920 @ 0x0034c920   (est. sk_ret0_c920)
 * Ghidra: FUN_0034C920(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_c920(void)
{
    return 0;
}

/* FUN_0034C930 @ 0x0034c930   (est. sk_noop_c930)
 * Ghidra: FUN_0034C930(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c930(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C948 @ 0x0034c948   (est. sk_noop_c948)
 * Ghidra: FUN_0034C948(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c948(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C960 @ 0x0034c960   (est. sk_noop_c960)
 * Ghidra: FUN_0034C960(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c960(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C978 @ 0x0034c978   (est. sk_noop_c978)
 * Ghidra: FUN_0034C978(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c978(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C988 @ 0x0034c988   (est. sk_noop_c988)
 * Ghidra: FUN_0034C988(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c988(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C998 @ 0x0034c998   (est. sk_noop_c998)
 * Ghidra: FUN_0034C998(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c998(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9A8 @ 0x0034c9a8   (est. sk_noop_c9a8)
 * Ghidra: FUN_0034C9A8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9a8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9B8 @ 0x0034c9b8   (est. sk_noop_c9b8)
 * Ghidra: FUN_0034C9B8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9b8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9C8 @ 0x0034c9c8   (est. sk_noop_c9c8)
 * Ghidra: FUN_0034C9C8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9c8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9D8 @ 0x0034c9d8   (est. sk_noop_c9d8)
 * Ghidra: FUN_0034C9D8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9d8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9E8 @ 0x0034c9e8   (est. sk_noop_c9e8)
 * Ghidra: FUN_0034C9E8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9e8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034C9F8 @ 0x0034c9f8   (est. sk_noop_c9f8)
 * Ghidra: FUN_0034C9F8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_c9f8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CA08 @ 0x0034ca08   (est. sk_noop_ca08)
 * Ghidra: FUN_0034CA08(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ca08(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CA18 @ 0x0034ca18   (est. sk_noop_ca18)
 * Ghidra: FUN_0034CA18(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ca18(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CA28 @ 0x0034ca28   (est. sk_noop_ca28)
 * Ghidra: FUN_0034CA28(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ca28(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CA38 @ 0x0034ca38   (est. sk_load_and_call)
 * Ghidra: FUN_0034CA38(...)
 * Reads words at obj+0x18/+0x20, saves obj to a stack slot, calls two helpers, returns the +0x18 value. Order-preserving thunk sequence.
 * Confidence: low
 * Notes: decompiler: unaff_x20+0x18/+0x20; callees FUN_0006a4c0, FUN_000a649c. */
cl4_result_t sk_load_and_call(uint64_t obj)
{
cl4_result_t r = *(cl4_result_t*)(obj+0x18);
    FUN_0006a4c0();
    FUN_000a649c(*(uint64_t*)(obj+0x20));
    return r;
}

/* FUN_0034CA7C @ 0x0034ca7c   (est. sk_log_fault)
 * Ghidra: FUN_0034CA7C(...)
 * Invokes the logging helper with zero code, two word operands from obj (+0x20/+0x10), and two data-string addresses. Diagnostic/fault-record emit.
 * Confidence: low
 * Notes: DAT_00611b24, DAT_00611b3c refs; FUN_00377824 out of slice. */
void sk_log_fault(uint64_t obj)
{
FUN_00377824(0, *(uint64_t*)(obj+0x20), *(uint64_t*)(obj+0x10), DAT_00611b24, DAT_00611b3c);
}

/* FUN_0034CAB0 @ 0x0034cab0   (est. sk_thunk_00310ad4_00027754_0016186c_cab0)
 * Ghidra: FUN_0034CAB0(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310ad4, FUN_00027754, FUN_0016186c. */
void sk_thunk_0310ad4_00027754_0016186c(void)
{
FUN_00310ad4();; FUN_00027754();; FUN_0016186c();
}

/* FUN_0034CAD8 @ 0x0034cad8   (est. sk_noop_cad8)
 * Ghidra: FUN_0034CAD8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cad8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CAE8 @ 0x0034cae8   (est. sk_ret0_cae8)
 * Ghidra: FUN_0034CAE8(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_cae8(void)
{
    return 0;
}

/* FUN_0034CAFC @ 0x0034cafc   (est. sk_noop_cafc)
 * Ghidra: FUN_0034CAFC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cafc(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB10 @ 0x0034cb10   (est. sk_noop_cb10)
 * Ghidra: FUN_0034CB10(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb10(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB24 @ 0x0034cb24   (est. sk_noop_cb24)
 * Ghidra: FUN_0034CB24(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb24(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB38 @ 0x0034cb38   (est. sk_noop_cb38)
 * Ghidra: FUN_0034CB38(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb38(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB4C @ 0x0034cb4c   (est. sk_noop_cb4c)
 * Ghidra: FUN_0034CB4C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb4c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB60 @ 0x0034cb60   (est. sk_noop_cb60)
 * Ghidra: FUN_0034CB60(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb60(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB74 @ 0x0034cb74   (est. sk_noop_cb74)
 * Ghidra: FUN_0034CB74(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb74(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB88 @ 0x0034cb88   (est. sk_noop_cb88)
 * Ghidra: FUN_0034CB88(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb88(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CB9C @ 0x0034cb9c   (est. sk_noop_cb9c)
 * Ghidra: FUN_0034CB9C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cb9c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CBB0 @ 0x0034cbb0   (est. sk_noop_cbb0)
 * Ghidra: FUN_0034CBB0(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cbb0(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CBC4 @ 0x0034cbc4   (est. sk_noop_cbc4)
 * Ghidra: FUN_0034CBC4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cbc4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CBD8 @ 0x0034cbd8   (est. sk_noop_cbd8)
 * Ghidra: FUN_0034CBD8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cbd8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CBEC @ 0x0034cbec   (est. sk_noop_cbec)
 * Ghidra: FUN_0034CBEC(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cbec(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CC00 @ 0x0034cc00   (est. sk_slot_load)
 * Ghidra: FUN_0034CC00(...)
 * Returns the word at caller frame base-0x158 - a register-restore loader.
 * Confidence: low
 * Notes: decompiler: unaff_x29-0x158; caller FUN_00234384. */
uint64_t sk_slot_load(void)
{
return *(uint64_t*)(frame_base()-0x158);
}

/* FUN_0034CC24 @ 0x0034cc24   (est. sk_noop_cc24)
 * Ghidra: FUN_0034CC24(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cc24(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CC38 @ 0x0034cc38   (est. sk_ptr_blend_38)
 * Ghidra: FUN_0034CC38(...)
 * Returns a 16-byte pair computed as an address blend (add-mask). Consistent with an arm64e pointer-auth / tagged-pointer primitive used by the vspace layer.
 * Confidence: low
 * Notes: decompiler add-mask artifact; regs x19,x23,x26,x27. */
cl4_result_t sk_ptr_blend_a(uint64_t x19,uint64_t x23,uint64_t x26,uint64_t x27)
{
cl4_result_t r;
    r.lo = (x26+x27+x19);
    r.hi = (x26+x27+x23);
    return r;
}

/* FUN_0034CC5C @ 0x0034cc5c   (est. sk_ptr_blend_5c)
 * Ghidra: FUN_0034CC5C(...)
 * Returns a 16-byte pair computed as an address blend (add-mask). Consistent with an arm64e pointer-auth / tagged-pointer primitive used by the vspace layer.
 * Confidence: low
 * Notes: decompiler add-mask artifact; regs x19,x23,x26,x27. */
cl4_result_t sk_ptr_blend_b(uint64_t x19,uint64_t x23,uint64_t x26,uint64_t x27)
{
cl4_result_t r;
    r.lo = (x27+x26+x19);
    r.hi = (x27+x26+x23);
    return r;
}

/* FUN_0034CC80 @ 0x0034cc80   (est. sk_noop_cc80)
 * Ghidra: FUN_0034CC80(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cc80(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CC94 @ 0x0034cc94   (est. sk_noop_cc94)
 * Ghidra: FUN_0034CC94(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cc94(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CCA8 @ 0x0034cca8   (est. sk_noop_cca8)
 * Ghidra: FUN_0034CCA8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cca8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CCBC @ 0x0034ccbc   (est. sk_ptr_blend_bc)
 * Ghidra: FUN_0034CCBC(...)
 * Returns a 16-byte pair computed as an address blend (add-mask). Consistent with an arm64e pointer-auth / tagged-pointer primitive used by the vspace layer.
 * Confidence: low
 * Notes: decompiler add-mask artifact; regs x19,x20,x26,param. */
cl4_result_t sk_ptr_blend_c(uint64_t x19,uint64_t x20,uint64_t x26,uint64_t param)
{
cl4_result_t r;
    r.lo = (x26+param+x20);
    r.hi = (x26+param+x19);
    return r;
}

/* FUN_0034CCE0 @ 0x0034cce0   (est. sk_ptr_blend_e0)
 * Ghidra: FUN_0034CCE0(...)
 * Returns a 16-byte pair computed as an address blend (add-mask). Consistent with an arm64e pointer-auth / tagged-pointer primitive used by the vspace layer.
 * Confidence: low
 * Notes: decompiler add-mask artifact; regs x20,x21,x26,param. */
cl4_result_t sk_ptr_blend_d(uint64_t x20,uint64_t x21,uint64_t x26,uint64_t param)
{
cl4_result_t r;
    r.lo = (x26+param+x21);
    r.hi = (x26+param+x20);
    return r;
}

/* FUN_0034CD04 @ 0x0034cd04   (est. sk_noop_cd04)
 * Ghidra: FUN_0034CD04(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cd04(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CD18 @ 0x0034cd18   (est. sk_noop_cd18)
 * Ghidra: FUN_0034CD18(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cd18(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CD2C @ 0x0034cd2c   (est. sk_noop_cd2c)
 * Ghidra: FUN_0034CD2C(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cd2c(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CD40 @ 0x0034cd40   (est. sk_frame_addr_e0)
 * Ghidra: FUN_0034CD40(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0xe0 <- &stack0 - param_1); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_frame_addr_e0(uint64_t param_1)
{
    /* recovered: *(frame_base-0xe0) <- &stack0 - param_1 */
    return;
}

/* FUN_0034CD54 @ 0x0034cd54   (est. sk_frame_addr_b0)
 * Ghidra: FUN_0034CD54(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0xb0 <- &stack0 - param_1); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_frame_addr_b0(uint64_t param_1)
{
    /* recovered: *(frame_base-0xb0) <- &stack0 - param_1 */
    return;
}

/* FUN_0034CD68 @ 0x0034cd68   (est. sk_noop_cd68)
 * Ghidra: FUN_0034CD68(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cd68(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CD7C @ 0x0034cd7c   (est. sk_retff_cd7c)
 * Ghidra: FUN_0034CD7C(void) (decompiled empty/const)
 * Returns 0xff (255) - a constant-sentinel helper (e.g. 'no such entry' marker).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_retff_cd7c(void)
{
    return 0xff;
}

/* FUN_0034CD90 @ 0x0034cd90   (est. sk_obj_5word_copy)
 * Ghidra: FUN_0034CD90(...)
 * Initialises a 5-word kernel object from a source template: stores dst via an output pointer, then copies five words. Used by object-alloc/init sites.
 * Confidence: medium
 * Notes: decompiler: unaff_x19=*out, unaff_x20=src, param_1=dst; 4 callers. */
void sk_obj_5word_copy(uint64_t *dst,const uint64_t *src,uint64_t **out_ptr)
{
*out_ptr=dst;
    dst[0]=src[0]; dst[1]=src[1]; dst[2]=src[2];
    dst[3]=src[3]; dst[4]=src[4];
}

/* FUN_0034CDB4 @ 0x0034cdb4   (est. sk_byte_copy)
 * Ghidra: FUN_0034CDB4(...)
 * Copies a single byte source->dest - minimal object-field copy primitive.
 * Confidence: medium
 * Notes: 14 callers incl. 0x45 range. */
void sk_byte_copy(uint8_t *dst,const uint8_t *src)
{
*dst=*src;
}

/* FUN_0034CDC8 @ 0x0034cdc8   (est. sk_noop_cdc8)
 * Ghidra: FUN_0034CDC8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cdc8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CDD8 @ 0x0034cdd8   (est. sk_noop_cdd8)
 * Ghidra: FUN_0034CDD8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cdd8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CDE8 @ 0x0034cde8   (est. sk_store_x9_c0)
 * Ghidra: FUN_0034CDE8(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0xc0 <- in_x9); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_store_x9_c0(void)
{
    /* recovered: *(frame_base-0xc0) <- in_x9 */
    return;
}

/* FUN_0034CDF8 @ 0x0034cdf8   (est. sk_noop_cdf8)
 * Ghidra: FUN_0034CDF8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cdf8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE08 @ 0x0034ce08   (est. sk_noop_ce08)
 * Ghidra: FUN_0034CE08(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce08(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE18 @ 0x0034ce18   (est. sk_noop_ce18)
 * Ghidra: FUN_0034CE18(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce18(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE28 @ 0x0034ce28   (est. sk_noop_ce28)
 * Ghidra: FUN_0034CE28(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce28(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE38 @ 0x0034ce38   (est. sk_noop_ce38)
 * Ghidra: FUN_0034CE38(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce38(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE48 @ 0x0034ce48   (est. sk_noop_ce48)
 * Ghidra: FUN_0034CE48(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce48(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE58 @ 0x0034ce58   (est. sk_noop_ce58)
 * Ghidra: FUN_0034CE58(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce58(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE68 @ 0x0034ce68   (est. sk_noop_ce68)
 * Ghidra: FUN_0034CE68(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce68(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE78 @ 0x0034ce78   (est. sk_noop_ce78)
 * Ghidra: FUN_0034CE78(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ce78(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CE88 @ 0x0034ce88   (est. sk_return_zero)
 * Ghidra: FUN_0034CE88(...)
 * Returns 0.
 * Confidence: medium
 * Notes:  */
uint64_t sk_return_zero(void)
{
return 0;
}

/* FUN_0034CE98 @ 0x0034ce98   (est. sk_return_zero2)
 * Ghidra: FUN_0034CE98(...)
 * Returns 0.
 * Confidence: medium
 * Notes:  */
uint64_t sk_return_zero2(void)
{
return 0;
}

/* FUN_0034CEA8 @ 0x0034cea8   (est. sk_thunk_0008f758_cea8)
 * Ghidra: FUN_0034CEA8(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_0008f758. */
void sk_thunk_0008f758_cea8(void)
{
FUN_0008f758();
}

/* FUN_0034CEC4 @ 0x0034cec4   (est. sk_encode_tag_field)
 * Ghidra: FUN_0034CEC4(...)
 * Combines two bit-fields into a 16-bit descriptor word: (flags&0xf)<<12 | (byte[base+1]&0x3f)<<6. Encoding a page-table/capability tag word.
 * Confidence: medium
 * Notes: 18 callers. */
uint32_t sk_encode_tag_field(uint64_t base,uint32_t flags)
{
return (uint32_t)((flags & 0xfu) << 12 | (*(uint8_t*)(base+1) & 0x3fu) << 6);
}

/* FUN_0034CED8 @ 0x0034ced8   (est. sk_noop_ced8)
 * Ghidra: FUN_0034CED8(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_ced8(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CEE8 @ 0x0034cee8   (est. sk_thunk_00310a74_cee8)
 * Ghidra: FUN_0034CEE8(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_00310a74. */
void sk_thunk_00310a74_cee8(void)
{
FUN_00310a74();
}

/* FUN_0034CF04 @ 0x0034cf04   (est. sk_noop_cf04)
 * Ghidra: FUN_0034CF04(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf04(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF14 @ 0x0034cf14   (est. sk_noop_cf14)
 * Ghidra: FUN_0034CF14(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf14(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF24 @ 0x0034cf24   (est. sk_noop_cf24)
 * Ghidra: FUN_0034CF24(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf24(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF34 @ 0x0034cf34   (est. sk_store_x9_a8)
 * Ghidra: FUN_0034CF34(...)
 * Decompiler recovered only a single frame-slot store (frame_base-0xa8 <- in_x9); the surrounding body was not recovered. Rendered as a no-op.
 * Confidence: low
 * Notes: decompiler-collapsed frame-store artifact. */
void sk_store_x9_a8(void)
{
    /* recovered: *(frame_base-0xa8) <- in_x9 */
    return;
}

/* FUN_0034CF44 @ 0x0034cf44   (est. sk_noop_cf44)
 * Ghidra: FUN_0034CF44(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf44(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF54 @ 0x0034cf54   (est. sk_noop_cf54)
 * Ghidra: FUN_0034CF54(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf54(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF64 @ 0x0034cf64   (est. sk_noop_cf64)
 * Ghidra: FUN_0034CF64(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf64(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF74 @ 0x0034cf74   (est. sk_noop_cf74)
 * Ghidra: FUN_0034CF74(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf74(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF84 @ 0x0034cf84   (est. sk_noop_cf84)
 * Ghidra: FUN_0034CF84(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf84(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CF94 @ 0x0034cf94   (est. sk_noop_cf94)
 * Ghidra: FUN_0034CF94(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cf94(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CFA4 @ 0x0034cfa4   (est. sk_stack_ctx_get_b)
 * Ghidra: FUN_0034CFA4(...)
 * 16-byte value with low word = frame base-0x70, high zero; companion to 0034c3b4.
 * Confidence: low
 * Notes: decompiler: auVar1._0_8_=unaff_x29-0x70,_8_8_=0; 14 callers. */
cl4_result_t sk_stack_ctx_get_b(void)
{
cl4_result_t r = { (uint64_t)(frame_base()-0x70), 0 };
    return r;
}

/* FUN_0034CFB4 @ 0x0034cfb4   (est. sk_noop_cfb4)
 * Ghidra: FUN_0034CFB4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cfb4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CFC4 @ 0x0034cfc4   (est. sk_noop_cfc4)
 * Ghidra: FUN_0034CFC4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cfc4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CFD4 @ 0x0034cfd4   (est. sk_noop_cfd4)
 * Ghidra: FUN_0034CFD4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cfd4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CFE4 @ 0x0034cfe4   (est. sk_noop_cfe4)
 * Ghidra: FUN_0034CFE4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cfe4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034CFF4 @ 0x0034cff4   (est. sk_noop_cff4)
 * Ghidra: FUN_0034CFF4(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_cff4(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034D004 @ 0x0034d004   (est. sk_noop_d004)
 * Ghidra: FUN_0034D004(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_d004(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034D014 @ 0x0034d014   (est. sk_ret0_d014)
 * Ghidra: FUN_0034D014(void) (decompiled empty/const)
 * Returns 0 - a constant-0 helper (unimplemented/absent operation returning success).
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
uint64_t sk_ret0_d014(void)
{
    return 0;
}

/* FUN_0034D024 @ 0x0034d024   (est. sk_word_to_hi)
 * Ghidra: FUN_0034D024(...)
 * 16-byte value with the word in the HIGH half (128-bit shift-left-64 of {param_3,0}).
 * Confidence: low
 * Notes: decompiler: auVar1<<0x40 artifact; 17 callers. */
cl4_result_t sk_word_to_hi(uint64_t param_3)
{
cl4_result_t r = { 0, param_3 };
    return r;
}

/* FUN_0034D034 @ 0x0034d034   (est. sk_noop_d034)
 * Ghidra: FUN_0034D034(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_d034(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034D044 @ 0x0034d044   (est. sk_noop_d044)
 * Ghidra: FUN_0034D044(void) (decompiled empty/const)
 * Decompiles to an empty body (bare return). A padding/landing-pad stub or an unimplemented/unused handler slot in this syscall/exception region.
 * Confidence: medium
 * Notes: faithful to decompile; no semantic identity (no string/caller match). */
void sk_noop_d044(void)
{
    /* decompiled body is empty (bare return) */
    return;
}

/* FUN_0034D054 @ 0x0034d054   (est. sk_thunk_003109b4_d054)
 * Ghidra: FUN_0034D054(...)
 * Thin wrapper invoking the listed helper(s) and returning; a dispatch/sequencing thunk.
 * Confidence: medium
 * Notes: callees out of slice: FUN_003109b4. */
void sk_thunk_003109b4_d054(void)
{
FUN_003109b4();
}

