/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header matched.
 * Slice 15: 0x34e004-0x34efa8 syscall/exception-entry region. This is a dense
 * syscall-dispatch table: most slots are unimplemented no-op stubs, plus a
 * handful of data-table getters, 128-bit helpers and list-walker wrappers.
 * Many small bodies are stack-frame fragments of larger handlers that Ghidra
 * over-segmented (they reference unaff_x29 / caller registers). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* Syscall descriptor/name tables (u32 offset arrays) returned by the getters. */
extern und4_t DAT_004e8b7c[];  /* table at DAT_004e8b7c */
extern und4_t DAT_004e8f9c[];  /* table at DAT_004e8f9c */
extern und4_t DAT_004e9db0[];  /* table at DAT_004e9db0 */
extern und4_t DAT_004ea760[];  /* table at DAT_004ea760 */
extern und4_t DAT_004eab00[];  /* table at DAT_004eab00 */
extern und4_t DAT_004eb964[];  /* table at DAT_004eb964 */
extern und4_t DAT_004eb980[];  /* table at DAT_004eb980 */
extern und4_t DAT_004edd08[];  /* table at DAT_004edd08 */

/* Out-of-range cL4 helpers (bodies reconstructed by their range workers). */
/* FUN_000839f8 — indirect method dispatch: invokes (*(obj-8)+0x30)(obj) through a vtable. */
extern void cL4_vtable_dispatch(word_t obj, word_t flag);
/* FUN_0006a4c0 — container advance honoring tag bit 0x11 at (*container+0x50). */
extern void cL4_container_advance(word_t p);
/* FUN_000a649c — intrusive list 'next' walker, link field @+0x14. */
extern word_t cL4_list_next_14(word_t node);
/* FUN_0008f758 — intrusive list 'next' walker, link field @+0xc. */
extern word_t cL4_list_next_0c(word_t node);
/* FUN_003109b4 — intrusive list 'next' walker, link field @+0x3c. */
extern word_t cL4_list_next_3c(word_t node);
/* FUN_00310a44 — intrusive list 'next' walker, link field @+0x40. */
extern word_t cL4_list_next_40(word_t node);
/* FUN_00310a74 — intrusive list 'next' walker, link field @+0x30. */
extern word_t cL4_list_next_30(word_t node);

/* FUN_0034E004 @ 0x0034e004   (est. sk_frag_e004)
 * Ghidra: undefined8 FUN_0034e004(void)
 * Register pass-through fragment (x3).
 * Confidence: low
 * Notes: */
word_t sk_frag_e004(void)
{
    /* register pass-through: returns the value left in x3 by the caller */
    word_t v;  /* x3 */
    return v;
}

/* FUN_0034E014 @ 0x0034e014   (est. sk_syscall_stub_e014)
 * Ghidra: void FUN_0034e014(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e014(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E024 @ 0x0034e024   (est. sk_syscall_stub_e024)
 * Ghidra: void FUN_0034e024(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e024(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E034 @ 0x0034e034   (est. sk_syscall_stub_e034)
 * Ghidra: void FUN_0034e034(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e034(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E044 @ 0x0034e044   (est. sk_syscall_stub_e044)
 * Ghidra: void FUN_0034e044(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e044(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E054 @ 0x0034e054   (est. sk_syscall_stub_e054)
 * Ghidra: void FUN_0034e054(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e054(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E064 @ 0x0034e064   (est. sk_syscall_stub_e064)
 * Ghidra: void FUN_0034e064(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e064(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E074 @ 0x0034e074   (est. sk_syscall_stub_e074)
 * Ghidra: void FUN_0034e074(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e074(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E084 @ 0x0034e084   (est. sk_syscall_stub_e084)
 * Ghidra: void FUN_0034e084(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e084(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E094 @ 0x0034e094   (est. sk_syscall_stub_e094)
 * Ghidra: void FUN_0034e094(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e094(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E0A4 @ 0x0034e0a4   (est. sk_syscall_ret0_e0a4)
 * Ghidra: undefined8 FUN_0034e0a4(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e0a4(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E0B4 @ 0x0034e0b4   (est. sk_syscall_ret0_e0b4)
 * Ghidra: undefined8 FUN_0034e0b4(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e0b4(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E0C4 @ 0x0034e0c4   (est. sk_syscall_ret0_e0c4)
 * Ghidra: undefined8 FUN_0034e0c4(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e0c4(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E0D4 @ 0x0034e0d4   (est. sk_syscall_ret0_e0d4)
 * Ghidra: undefined8 FUN_0034e0d4(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e0d4(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E0E4 @ 0x0034e0e4   (est. sk_syscall_stub_e0e4)
 * Ghidra: void FUN_0034e0e4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e0e4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E0F4 @ 0x0034e0f4   (est. sk_syscall_stub_e0f4)
 * Ghidra: void FUN_0034e0f4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e0f4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E104 @ 0x0034e104   (est. sk_list_next_3c_e104)
 * Ghidra: void FUN_0034e104(void)
 * Wrapper for the list-next walker with link field @+0x3c.
 * Confidence: medium
 * Notes: (callee FUN_0034e104, FUN_003109b4) */
word_t sk_list_next_3c_e104(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0x3c; return the callee's result (pass-through). */
    return cL4_list_next_3c(node);
}

/* FUN_0034E120 @ 0x0034e120   (est. sk_syscall_stub_e120)
 * Ghidra: void FUN_0034e120(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e120(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E130 @ 0x0034e130   (est. sk_pack_hi_e130)
 * Ghidra: undefined1 [16] FUN_0034e130(ulong param_1)
 * Packs value into the high 64-bit half of a 128-bit result.
 * Confidence: medium
 * Notes: */
cL4_w16_t sk_pack_hi_e130(word_t value)
{
    cL4_w16_t r;
    r.lo = 0;
    r.hi = value;  /* packed into the upper 64-bit half of the result */
    return r;
}

/* FUN_0034E140 @ 0x0034e140   (est. sk_list_next_40_e140)
 * Ghidra: void FUN_0034e140(void)
 * Wrapper for the list-next walker with link field @+0x40.
 * Confidence: medium
 * Notes: (callee FUN_0034e140, FUN_00310a44) */
word_t sk_list_next_40_e140(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0x40; return the callee's result (pass-through). */
    return cL4_list_next_40(node);
}

/* FUN_0034E15C @ 0x0034e15c   (est. sk_list_next_40_e15c)
 * Ghidra: void FUN_0034e15c(void)
 * Wrapper for the list-next walker with link field @+0x40.
 * Confidence: medium
 * Notes: (callee FUN_0034e15c, FUN_00310a44) */
word_t sk_list_next_40_e15c(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0x40; return the callee's result (pass-through). */
    return cL4_list_next_40(node);
}

/* FUN_0034E178 @ 0x0034e178   (est. sk_vtable_dispatch_e178)
 * Ghidra: void FUN_0034e178(undefined8 param_1)
 * Calls FUN_000839f8 (vtable+0x30 method dispatch) twice.
 * Confidence: low
 * Notes: (callee FUN_0034e178, FUN_000839f8, FUN_000839f8) */
void sk_vtable_dispatch_e178(word_t obj)
{
    /* indirect method dispatch: FUN_000839f8(obj,1) calls the method at
     * (*(obj-8)+0x30) via the object vtable; the second call re-dispatches
     * with the same x0. */
    cL4_vtable_dispatch(obj, 1);
    cL4_vtable_dispatch(obj, 0);
}

/* FUN_0034E1B0 @ 0x0034e1b0   (est. sk_vtable_dispatch_e1b0)
 * Ghidra: void FUN_0034e1b0(undefined4 param_1)
 * Calls FUN_000839f8 (vtable+0x30 method dispatch) twice.
 * Confidence: low
 * Notes: (callee FUN_0034e1b0, FUN_000839f8) */
void sk_vtable_dispatch_e1b0(word_t obj)
{
    /* indirect method dispatch: FUN_000839f8(obj,1) calls the method at
     * (*(obj-8)+0x30) via the object vtable; the second call re-dispatches
     * with the same x0. */
    cL4_vtable_dispatch(obj, 1);
    cL4_vtable_dispatch(obj, 0);
}

/* FUN_0034E1D0 @ 0x0034e1d0   (est. sk_list_next_30_e1d0)
 * Ghidra: void FUN_0034e1d0(void)
 * Wrapper for the list-next walker with link field @+0x30.
 * Confidence: medium
 * Notes: (callee FUN_0034e1d0, FUN_00310a74) */
word_t sk_list_next_30_e1d0(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0x30; return the callee's result (pass-through). */
    return cL4_list_next_30(node);
}

/* FUN_0034E1EC @ 0x0034e1ec   (est. sk_container_advance_e1ec)
 * Ghidra: void FUN_0034e1ec(void)
 * Calls FUN_0006a4c0 (container advance).
 * Confidence: low
 * Notes: (callee FUN_0034e1ec, FUN_0006a4c0) */
void sk_container_advance_e1ec(word_t p)
{
    /* container advance: FUN_0006a4c0 adjusts p per the tag bit 0x11 at
     * (*container+0x50). */
    cL4_container_advance(p);
}

/* FUN_0034E208 @ 0x0034e208   (est. sk_syscall_stub_e208)
 * Ghidra: void FUN_0034e208(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e208(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E220 @ 0x0034e220   (est. sk_syscall_table_get_e220)
 * Ghidra: undefined * FUN_0034e220(void)
 * Getter returning the syscall descriptor table at DAT_004eb980.
 * Confidence: medium
 * Notes: (returns table DAT_004eb980) */
void * sk_syscall_table_get_e220(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004eb980 */
    return (void *)&DAT_004eb980;
}

/* FUN_0034E238 @ 0x0034e238   (est. sk_syscall_table_get_e238)
 * Ghidra: undefined * FUN_0034e238(void)
 * Getter returning the syscall descriptor table at DAT_004eb964.
 * Confidence: medium
 * Notes: (returns table DAT_004eb964) */
void * sk_syscall_table_get_e238(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004eb964 */
    return (void *)&DAT_004eb964;
}

/* FUN_0034E250 @ 0x0034e250   (est. sk_syscall_table_get_e250)
 * Ghidra: undefined * FUN_0034e250(void)
 * Getter returning the syscall descriptor table at DAT_004edd08.
 * Confidence: medium
 * Notes: (returns table DAT_004edd08) */
void * sk_syscall_table_get_e250(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004edd08 */
    return (void *)&DAT_004edd08;
}

/* FUN_0034E268 @ 0x0034e268   (est. sk_syscall_table_get_e268)
 * Ghidra: undefined * FUN_0034e268(void)
 * Getter returning the syscall descriptor table at DAT_004eab00.
 * Confidence: medium
 * Notes: (returns table DAT_004eab00) */
void * sk_syscall_table_get_e268(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004eab00 */
    return (void *)&DAT_004eab00;
}

/* FUN_0034E280 @ 0x0034e280   (est. sk_syscall_stub_e280)
 * Ghidra: void FUN_0034e280(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e280(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E298 @ 0x0034e298   (est. sk_bitmap_words)
 * Ghidra: undefined1 [16] FUN_0034e298(long param_1)
 * Number of 64-bit words covering nbits (bitmap sizing).
 * Confidence: medium
 * Notes: (Ghidra packs via 128-bit shift << 0x40) */
cL4_w16_t sk_bitmap_words(word_t nbits)
{
    cL4_w16_t r;
    r.lo = 0;
    r.hi = (nbits + 0x3f) >> 6;  /* ceil(nbits/64) 64-bit words */
    return r;
}

/* FUN_0034E2A8 @ 0x0034e2a8   (est. sk_frag_e2a8)
 * Ghidra: void FUN_0034e2a8(void)
 * Stores a 24-bit value into a 3-byte field (x19/w24 fragment).
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_e2a8(void)
{
    /* stores a 24-bit value into a 3-byte little-endian field: low 16 bits
     * at *p, high 8 bits at p+2 (pointer x19, value w24). The callee-saved
     * register source is unrecoverable, so this is an annotated fragment. */
}

/* FUN_0034E2B8 @ 0x0034e2b8   (est. sk_syscall_stub_e2b8)
 * Ghidra: void FUN_0034e2b8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e2b8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E2D0 @ 0x0034e2d0   (est. sk_syscall_stub_e2d0)
 * Ghidra: void FUN_0034e2d0(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e2d0(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E2E4 @ 0x0034e2e4   (est. sk_syscall_stub_e2e4)
 * Ghidra: void FUN_0034e2e4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e2e4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E2FC @ 0x0034e2fc   (est. sk_syscall_table_get_e2fc)
 * Ghidra: undefined * FUN_0034e2fc(void)
 * Getter returning the syscall descriptor table at DAT_004ea760.
 * Confidence: medium
 * Notes: (returns table DAT_004ea760) */
void * sk_syscall_table_get_e2fc(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004ea760 */
    return (void *)&DAT_004ea760;
}

/* FUN_0034E314 @ 0x0034e314   (est. sk_syscall_table_get_e314)
 * Ghidra: undefined * FUN_0034e314(void)
 * Getter returning the syscall descriptor table at DAT_004e9db0.
 * Confidence: medium
 * Notes: (returns table DAT_004e9db0) */
void * sk_syscall_table_get_e314(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004e9db0 */
    return (void *)&DAT_004e9db0;
}

/* FUN_0034E32C @ 0x0034e32c   (est. sk_syscall_stub_e32c)
 * Ghidra: void FUN_0034e32c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e32c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E33C @ 0x0034e33c   (est. sk_syscall_stub_e33c)
 * Ghidra: void FUN_0034e33c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e33c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E34C @ 0x0034e34c   (est. sk_syscall_stub_e34c)
 * Ghidra: void FUN_0034e34c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e34c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E35C @ 0x0034e35c   (est. sk_syscall_table_get_e35c)
 * Ghidra: undefined * FUN_0034e35c(void)
 * Getter returning the syscall descriptor table at DAT_004e8f9c.
 * Confidence: medium
 * Notes: (returns table DAT_004e8f9c) */
void * sk_syscall_table_get_e35c(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004e8f9c */
    return (void *)&DAT_004e8f9c;
}

/* FUN_0034E374 @ 0x0034e374   (est. sk_syscall_stub_e374)
 * Ghidra: void FUN_0034e374(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e374(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E384 @ 0x0034e384   (est. sk_syscall_stub_e384)
 * Ghidra: void FUN_0034e384(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e384(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E39C @ 0x0034e39c   (est. sk_syscall_stub_e39c)
 * Ghidra: void FUN_0034e39c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e39c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E3AC @ 0x0034e3ac   (est. sk_syscall_stub_e3ac)
 * Ghidra: void FUN_0034e3ac(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e3ac(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E3BC @ 0x0034e3bc   (est. sk_syscall_stub_e3bc)
 * Ghidra: void FUN_0034e3bc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e3bc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E3CC @ 0x0034e3cc   (est. sk_syscall_stub_e3cc)
 * Ghidra: void FUN_0034e3cc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e3cc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E3E4 @ 0x0034e3e4   (est. sk_syscall_stub_e3e4)
 * Ghidra: void FUN_0034e3e4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e3e4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E3FC @ 0x0034e3fc   (est. sk_syscall_stub_e3fc)
 * Ghidra: void FUN_0034e3fc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e3fc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E414 @ 0x0034e414   (est. sk_syscall_ret0_e414)
 * Ghidra: undefined8 FUN_0034e414(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e414(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E424 @ 0x0034e424   (est. sk_syscall_stub_e424)
 * Ghidra: void FUN_0034e424(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e424(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E434 @ 0x0034e434   (est. sk_syscall_stub_e434)
 * Ghidra: void FUN_0034e434(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e434(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E444 @ 0x0034e444   (est. sk_syscall_stub_e444)
 * Ghidra: void FUN_0034e444(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e444(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E454 @ 0x0034e454   (est. sk_syscall_stub_e454)
 * Ghidra: void FUN_0034e454(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e454(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E464 @ 0x0034e464   (est. sk_syscall_stub_e464)
 * Ghidra: void FUN_0034e464(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e464(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E474 @ 0x0034e474   (est. sk_syscall_stub_e474)
 * Ghidra: void FUN_0034e474(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e474(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E484 @ 0x0034e484   (est. sk_syscall_stub_e484)
 * Ghidra: void FUN_0034e484(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e484(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E494 @ 0x0034e494   (est. sk_syscall_stub_e494)
 * Ghidra: void FUN_0034e494(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e494(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E4A4 @ 0x0034e4a4   (est. sk_syscall_stub_e4a4)
 * Ghidra: void FUN_0034e4a4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e4a4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E4B4 @ 0x0034e4b4   (est. sk_syscall_table_get_e4b4)
 * Ghidra: undefined * FUN_0034e4b4(void)
 * Getter returning the syscall descriptor table at DAT_004e8b7c.
 * Confidence: medium
 * Notes: (returns table DAT_004e8b7c) */
void * sk_syscall_table_get_e4b4(void)
{
    /* return pointer to the syscall descriptor/name table at DAT_004e8b7c */
    return (void *)&DAT_004e8b7c;
}

/* FUN_0034E4CC @ 0x0034e4cc   (est. sk_syscall_stub_e4cc)
 * Ghidra: void FUN_0034e4cc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e4cc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E4DC @ 0x0034e4dc   (est. sk_syscall_stub_e4dc)
 * Ghidra: void FUN_0034e4dc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e4dc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E4EC @ 0x0034e4ec   (est. sk_syscall_stub_e4ec)
 * Ghidra: void FUN_0034e4ec(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e4ec(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E4FC @ 0x0034e4fc   (est. sk_syscall_stub_e4fc)
 * Ghidra: void FUN_0034e4fc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e4fc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E50C @ 0x0034e50c   (est. sk_syscall_stub_e50c)
 * Ghidra: void FUN_0034e50c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e50c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E51C @ 0x0034e51c   (est. sk_syscall_stub_e51c)
 * Ghidra: void FUN_0034e51c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e51c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E52C @ 0x0034e52c   (est. sk_syscall_stub_e52c)
 * Ghidra: void FUN_0034e52c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e52c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E53C @ 0x0034e53c   (est. sk_syscall_stub_e53c)
 * Ghidra: void FUN_0034e53c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e53c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E54C @ 0x0034e54c   (est. sk_syscall_stub_e54c)
 * Ghidra: void FUN_0034e54c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e54c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E55C @ 0x0034e55c   (est. sk_syscall_stub_e55c)
 * Ghidra: void FUN_0034e55c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e55c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E56C @ 0x0034e56c   (est. sk_syscall_stub_e56c)
 * Ghidra: void FUN_0034e56c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e56c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E57C @ 0x0034e57c   (est. sk_pack_hi_e57c)
 * Ghidra: undefined1 [16] FUN_0034e57c(ulong param_1)
 * Packs value into the high 64-bit half of a 128-bit result.
 * Confidence: medium
 * Notes: */
cL4_w16_t sk_pack_hi_e57c(word_t value)
{
    cL4_w16_t r;
    r.lo = 0;
    r.hi = value;  /* packed into the upper 64-bit half of the result */
    return r;
}

/* FUN_0034E58C @ 0x0034e58c   (est. sk_frag_e58c)
 * Ghidra: undefined1 [16] FUN_0034e58c(void)
 * Caller-frame read fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_e58c(void)
{
    /* returns { *(fp-0x138), fp-0x130 } from the caller's frame. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034E5BC @ 0x0034e5bc   (est. sk_syscall_stub_e5bc)
 * Ghidra: void FUN_0034e5bc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e5bc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E5CC @ 0x0034e5cc   (est. sk_syscall_stub_e5cc)
 * Ghidra: void FUN_0034e5cc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e5cc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E5DC @ 0x0034e5dc   (est. sk_syscall_stub_e5dc)
 * Ghidra: void FUN_0034e5dc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e5dc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E5EC @ 0x0034e5ec   (est. sk_syscall_stub_e5ec)
 * Ghidra: void FUN_0034e5ec(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e5ec(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E5FC @ 0x0034e5fc   (est. sk_syscall_stub_e5fc)
 * Ghidra: void FUN_0034e5fc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e5fc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E60C @ 0x0034e60c   (est. sk_syscall_stub_e60c)
 * Ghidra: void FUN_0034e60c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e60c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E61C @ 0x0034e61c   (est. sk_syscall_stub_e61c)
 * Ghidra: void FUN_0034e61c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e61c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E62C @ 0x0034e62c   (est. sk_syscall_stub_e62c)
 * Ghidra: void FUN_0034e62c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e62c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E63C @ 0x0034e63c   (est. sk_syscall_stub_e63c)
 * Ghidra: void FUN_0034e63c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e63c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E64C @ 0x0034e64c   (est. sk_syscall_stub_e64c)
 * Ghidra: void FUN_0034e64c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e64c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E65C @ 0x0034e65c   (est. sk_syscall_stub_e65c)
 * Ghidra: void FUN_0034e65c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e65c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E66C @ 0x0034e66c   (est. sk_syscall_stub_e66c)
 * Ghidra: void FUN_0034e66c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e66c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E67C @ 0x0034e67c   (est. sk_pack_hi_e67c)
 * Ghidra: undefined1 [16] FUN_0034e67c(ulong param_1)
 * Packs value into the high 64-bit half of a 128-bit result.
 * Confidence: medium
 * Notes: */
cL4_w16_t sk_pack_hi_e67c(word_t value)
{
    cL4_w16_t r;
    r.lo = 0;
    r.hi = value;  /* packed into the upper 64-bit half of the result */
    return r;
}

/* FUN_0034E68C @ 0x0034e68c   (est. sk_syscall_stub_e68c)
 * Ghidra: void FUN_0034e68c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e68c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E69C @ 0x0034e69c   (est. sk_syscall_stub_e69c)
 * Ghidra: void FUN_0034e69c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e69c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E6AC @ 0x0034e6ac   (est. sk_syscall_stub_e6ac)
 * Ghidra: void FUN_0034e6ac(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e6ac(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E6BC @ 0x0034e6bc   (est. sk_syscall_stub_e6bc)
 * Ghidra: void FUN_0034e6bc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e6bc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E6CC @ 0x0034e6cc   (est. sk_frag_e6cc)
 * Ghidra: void FUN_0034e6cc(void)
 * Caller-frame store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_e6cc(void)
{
    /* stores x9 into the caller frame slot fp-0xf0. */
}

/* FUN_0034E6DC @ 0x0034e6dc   (est. sk_syscall_ret0_e6dc)
 * Ghidra: undefined8 FUN_0034e6dc(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e6dc(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E6EC @ 0x0034e6ec   (est. sk_syscall_ret0_e6ec)
 * Ghidra: undefined8 FUN_0034e6ec(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e6ec(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E6FC @ 0x0034e6fc   (est. sk_syscall_ret0_e6fc)
 * Ghidra: undefined8 FUN_0034e6fc(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e6fc(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E70C @ 0x0034e70c   (est. sk_syscall_ret0_e70c)
 * Ghidra: undefined8 FUN_0034e70c(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e70c(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E71C @ 0x0034e71c   (est. sk_syscall_stub_e71c)
 * Ghidra: void FUN_0034e71c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e71c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E72C @ 0x0034e72c   (est. sk_syscall_stub_e72c)
 * Ghidra: void FUN_0034e72c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e72c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E73C @ 0x0034e73c   (est. sk_frag_e73c)
 * Ghidra: undefined8 FUN_0034e73c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Third-argument pass-through.
 * Confidence: low
 * Notes: */
word_t sk_frag_e73c(word_t a, word_t b, word_t c)
{
    /* pass-through of the third argument. */
    return c;
}

/* FUN_0034E74C @ 0x0034e74c   (est. sk_list_next_0c_e74c)
 * Ghidra: void FUN_0034e74c(void)
 * Wrapper for the list-next walker with link field @+0xc.
 * Confidence: medium
 * Notes: (callee FUN_0034e74c, FUN_0008f758) */
word_t sk_list_next_0c_e74c(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0xc; return the callee's result (pass-through). */
    return cL4_list_next_0c(node);
}

/* FUN_0034E768 @ 0x0034e768   (est. sk_list_next_30_e768)
 * Ghidra: void FUN_0034e768(void)
 * Wrapper for the list-next walker with link field @+0x30.
 * Confidence: medium
 * Notes: (callee FUN_0034e768, FUN_00310a74) */
word_t sk_list_next_30_e768(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0x30; return the callee's result (pass-through). */
    return cL4_list_next_30(node);
}

/* FUN_0034E784 @ 0x0034e784   (est. sk_list_next_0c_e784)
 * Ghidra: void FUN_0034e784(void)
 * Wrapper for the list-next walker with link field @+0xc.
 * Confidence: medium
 * Notes: (callee FUN_0034e784, FUN_0008f758) */
word_t sk_list_next_0c_e784(word_t node)
{
    /* walk to the next element of an intrusive list whose link field is at
     * node+0xc; return the callee's result (pass-through). */
    return cL4_list_next_0c(node);
}

/* FUN_0034E7A0 @ 0x0034e7a0   (est. sk_container_advance2_e7a0)
 * Ghidra: void FUN_0034e7a0(void)
 * Calls FUN_0006a4c0 then FUN_000a649c.
 * Confidence: low
 * Notes: (callee FUN_0034e7a0, FUN_0006a4c0, FUN_000a649c) */
void sk_container_advance2_e7a0(word_t p)
{
    /* container advance then list-next walk (link @+0x14). */
    cL4_container_advance(p);
    cL4_list_next_14(p);
}

/* FUN_0034E7E0 @ 0x0034e7e0   (est. sk_syscall_ret0_e7e0)
 * Ghidra: undefined8 FUN_0034e7e0(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e7e0(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E7F4 @ 0x0034e7f4   (est. sk_u128_lt_e7f4)
 * Ghidra: undefined2 FUN_0034e7f4(undefined1 param_1 [16],undefined1 param_2 [16],undefined1 param_3 [16])
 * 128-bit unsigned less-than via NEON umaxv over 16-bit lanes.
 * Confidence: medium
 * Notes: (NEON umaxv over 8x16-bit lanes) */
und2_t sk_u128_lt_e7f4(const cL4_w16_t *a, const cL4_w16_t *b)
{
    /* 128-bit unsigned less-than: per 16-bit lane set 0xffff if a<b else 0;
     * return the max across all 8 lanes (NEON umaxv) — nonzero iff a<b. */
    unsigned int lt = 0;
    const uint16_t *pa = (const uint16_t *)a;
    const uint16_t *pb = (const uint16_t *)b;
    for (int i = 0; i < 8; i++)
        lt |= (pa[i] < pb[i]) ? 0xffffu : 0u;
    return (und2_t)lt;
}

/* FUN_0034E808 @ 0x0034e808   (est. sk_syscall_ret0_e808)
 * Ghidra: undefined8 FUN_0034e808(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_e808(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034E81C @ 0x0034e81c   (est. sk_syscall_ret0xff_e81c)
 * Ghidra: undefined8 FUN_0034e81c(void)
 * Returns the 0xff sentinel.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0xff_e81c(void)
{
    /* returns all-bits-set sentinel (0xff) */
    return 0xff;
}

/* FUN_0034E830 @ 0x0034e830   (est. sk_frag_e830)
 * Ghidra: void FUN_0034e830(long param_1,undefined8 param_2)
 * 5-field record write with conditional mask shift.
 * Confidence: low
 * Notes: */
void sk_frag_e830(word_t *rec, word_t v)
{
    /* writes record fields at offsets 8,0x10,0x18,0x20 of rec, with a
     * conditional 64-bit mask shift when shift<0x40 (bitmap/IRQ setup). */
    rec[1] = v;
    rec[2] = 0;
    rec[3] = 0;
    rec[4] = 0;
}

/* FUN_0034E850 @ 0x0034e850   (est. sk_frag_e850)
 * Ghidra: undefined1 [16] FUN_0034e850(long param_1)
 * Mask-aligned address pair fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_e850(word_t base)
{
    /* two mask-aligned (round-up to ~mask) address computations returning a
     * 16-byte pair; the alignment mask is a caller register. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034E86C @ 0x0034e86c   (est. sk_frag_e86c)
 * Ghidra: void FUN_0034e86c(undefined8 *param_1,undefined8 *param_2)
 * 24-byte (3-word) struct copy.
 * Confidence: medium
 * Notes: */
void sk_frag_e86c(word_t *dst, const word_t *src)
{
    /* copy 3 words (24 bytes) from src to dst. */
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

/* FUN_0034E888 @ 0x0034e888   (est. sk_syscall_stub_e888)
 * Ghidra: void FUN_0034e888(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e888(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E8A4 @ 0x0034e8a4   (est. sk_syscall_stub_e8a4)
 * Ghidra: void FUN_0034e8a4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e8a4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E8B8 @ 0x0034e8b8   (est. sk_frag_e8b8)
 * Ghidra: undefined1 [16] FUN_0034e8b8(long param_1)
 * Mask-aligned address pair fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_e8b8(word_t base)
{
    /* two mask-aligned (round-up to ~mask) address computations returning a
     * 16-byte pair; the alignment mask is a caller register. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034E8D4 @ 0x0034e8d4   (est. sk_syscall_stub_e8d4)
 * Ghidra: void FUN_0034e8d4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e8d4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E8E8 @ 0x0034e8e8   (est. sk_syscall_stub_e8e8)
 * Ghidra: void FUN_0034e8e8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e8e8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E8FC @ 0x0034e8fc   (est. sk_syscall_stub_e8fc)
 * Ghidra: void FUN_0034e8fc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e8fc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E910 @ 0x0034e910   (est. sk_syscall_stub_e910)
 * Ghidra: void FUN_0034e910(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e910(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E924 @ 0x0034e924   (est. sk_syscall_stub_e924)
 * Ghidra: void FUN_0034e924(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e924(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E938 @ 0x0034e938   (est. sk_syscall_stub_e938)
 * Ghidra: void FUN_0034e938(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e938(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E94C @ 0x0034e94c   (est. sk_syscall_stub_e94c)
 * Ghidra: void FUN_0034e94c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e94c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E960 @ 0x0034e960   (est. sk_syscall_stub_e960)
 * Ghidra: void FUN_0034e960(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e960(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E974 @ 0x0034e974   (est. sk_frag_e974)
 * Ghidra: void FUN_0034e974(undefined8 param_1)
 * Callee-saved-store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_e974(word_t v)
{
    /* stores v to the address held in callee-saved x19 (unrecoverable). */
}

/* FUN_0034E990 @ 0x0034e990   (est. sk_syscall_stub_e990)
 * Ghidra: void FUN_0034e990(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e990(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E9A4 @ 0x0034e9a4   (est. sk_syscall_stub_e9a4)
 * Ghidra: void FUN_0034e9a4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e9a4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E9B8 @ 0x0034e9b8   (est. sk_frag_e9b8)
 * Ghidra: undefined1 [16] FUN_0034e9b8(void)
 * Caller-frame 128-bit read fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_e9b8(void)
{
    /* returns the 128-bit value at the caller frame slot fp-0x60. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034E9D4 @ 0x0034e9d4   (est. sk_syscall_stub_e9d4)
 * Ghidra: void FUN_0034e9d4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e9d4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034E9E8 @ 0x0034e9e8   (est. sk_frag_e9e8)
 * Ghidra: bool FUN_0034e9e8(ulong param_1)
 * Returns (v > 1).
 * Confidence: medium
 * Notes: */
bool sk_frag_e9e8(word_t v)
{
    return v > 1;
}

/* FUN_0034E9FC @ 0x0034e9fc   (est. sk_syscall_stub_e9fc)
 * Ghidra: void FUN_0034e9fc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_e9fc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EA18 @ 0x0034ea18   (est. sk_syscall_stub_ea18)
 * Ghidra: void FUN_0034ea18(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ea18(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EA2C @ 0x0034ea2c   (est. sk_frag_ea2c)
 * Ghidra: undefined1 [16] FUN_0034ea2c(void)
 * Frame-address/global pairing fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_ea2c(void)
{
    /* returns { fp-0x58, 0x677790 } (a frame address paired with the global
     * at 0x677790). */
    cL4_w16_t r; r.lo = 0; r.hi = 0x677790;
    return r;
}

/* FUN_0034EA40 @ 0x0034ea40   (est. sk_frag_ea40)
 * Ghidra: void FUN_0034ea40(void)
 * Caller-frame difference-store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_ea40(void)
{
    /* stores (x9 - x12) into the caller frame slot fp-0x58. */
}

/* FUN_0034EA54 @ 0x0034ea54   (est. sk_frag_ea54)
 * Ghidra: void FUN_0034ea54(void)
 * Caller-frame stack-difference store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_ea54(void)
{
    /* stores (&stack - x12) into the caller frame slot fp-200. */
}

/* FUN_0034EA68 @ 0x0034ea68   (est. sk_syscall_stub_ea68)
 * Ghidra: void FUN_0034ea68(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ea68(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EA7C @ 0x0034ea7c   (est. sk_syscall_stub_ea7c)
 * Ghidra: void FUN_0034ea7c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ea7c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EAAC @ 0x0034eaac   (est. sk_frag_eaac)
 * Ghidra: undefined8 FUN_0034eaac(void)
 * Caller-frame load fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
word_t sk_frag_eaac(void)
{
    /* returns the caller frame slot at fp-0x58. */
    word_t v;  /* *(fp-0x58) */
    return v;
}

/* FUN_0034EAC0 @ 0x0034eac0   (est. sk_syscall_stub_eac0)
 * Ghidra: void FUN_0034eac0(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eac0(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EAD4 @ 0x0034ead4   (est. sk_frag_ead4)
 * Ghidra: undefined8 FUN_0034ead4(void)
 * Caller-frame load fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
word_t sk_frag_ead4(void)
{
    /* returns the caller frame slot at fp-0xa8. */
    word_t v;  /* *(fp-0xa8) */
    return v;
}

/* FUN_0034EAE8 @ 0x0034eae8   (est. sk_frag_eae8)
 * Ghidra: undefined8 FUN_0034eae8(void)
 * Caller-frame load fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
word_t sk_frag_eae8(void)
{
    /* returns the caller frame slot at fp-0xa0. */
    word_t v;  /* *(fp-0xa0) */
    return v;
}

/* FUN_0034EAFC @ 0x0034eafc   (est. sk_syscall_stub_eafc)
 * Ghidra: void FUN_0034eafc(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eafc(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB10 @ 0x0034eb10   (est. sk_syscall_stub_eb10)
 * Ghidra: void FUN_0034eb10(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb10(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB2C @ 0x0034eb2c   (est. sk_frag_eb2c)
 * Ghidra: void FUN_0034eb2c(long param_1)
 * Caller-frame stack-difference store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_eb2c(word_t v)
{
    /* stores (&stack - v) into the caller frame slot fp-0xa0. */
}

/* FUN_0034EB40 @ 0x0034eb40   (est. sk_frag_eb40)
 * Ghidra: void FUN_0034eb40(long param_1)
 * Caller-frame stack-difference store fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
void sk_frag_eb40(word_t v)
{
    /* stores (&stack - v) into the caller frame slot fp-0xe8. */
}

/* FUN_0034EB54 @ 0x0034eb54   (est. sk_syscall_stub_eb54)
 * Ghidra: void FUN_0034eb54(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb54(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB64 @ 0x0034eb64   (est. sk_syscall_stub_eb64)
 * Ghidra: void FUN_0034eb64(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb64(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB74 @ 0x0034eb74   (est. sk_syscall_stub_eb74)
 * Ghidra: void FUN_0034eb74(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb74(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB84 @ 0x0034eb84   (est. sk_syscall_stub_eb84)
 * Ghidra: void FUN_0034eb84(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb84(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EB94 @ 0x0034eb94   (est. sk_syscall_stub_eb94)
 * Ghidra: void FUN_0034eb94(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eb94(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EBA4 @ 0x0034eba4   (est. sk_syscall_stub_eba4)
 * Ghidra: void FUN_0034eba4(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eba4(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EBE0 @ 0x0034ebe0   (est. sk_syscall_stub_ebe0)
 * Ghidra: void FUN_0034ebe0(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ebe0(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC0C @ 0x0034ec0c   (est. sk_syscall_stub_ec0c)
 * Ghidra: void FUN_0034ec0c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec0c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC1C @ 0x0034ec1c   (est. sk_syscall_stub_ec1c)
 * Ghidra: void FUN_0034ec1c(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec1c(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC48 @ 0x0034ec48   (est. sk_syscall_stub_ec48)
 * Ghidra: void FUN_0034ec48(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec48(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC58 @ 0x0034ec58   (est. sk_syscall_stub_ec58)
 * Ghidra: void FUN_0034ec58(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec58(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC68 @ 0x0034ec68   (est. sk_syscall_stub_ec68)
 * Ghidra: void FUN_0034ec68(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec68(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC78 @ 0x0034ec78   (est. sk_syscall_stub_ec78)
 * Ghidra: void FUN_0034ec78(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec78(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC88 @ 0x0034ec88   (est. sk_syscall_stub_ec88)
 * Ghidra: void FUN_0034ec88(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ec88(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EC98 @ 0x0034ec98   (est. sk_frag_ec98)
 * Ghidra: undefined1 [16] FUN_0034ec98(void)
 * Caller-frame address/pair fragment.
 * Confidence: low
 * Notes: */
cL4_w16_t sk_frag_ec98(void)
{
    /* returns { &stack+8, *(stack+0x20) } from the caller frame. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034ECA8 @ 0x0034eca8   (est. sk_syscall_stub_eca8)
 * Ghidra: void FUN_0034eca8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eca8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ECB8 @ 0x0034ecb8   (est. sk_syscall_stub_ecb8)
 * Ghidra: void FUN_0034ecb8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ecb8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ECC8 @ 0x0034ecc8   (est. sk_syscall_stub_ecc8)
 * Ghidra: void FUN_0034ecc8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ecc8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ECD8 @ 0x0034ecd8   (est. sk_syscall_stub_ecd8)
 * Ghidra: void FUN_0034ecd8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ecd8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ECE8 @ 0x0034ece8   (est. sk_syscall_stub_ece8)
 * Ghidra: void FUN_0034ece8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ece8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ECF8 @ 0x0034ecf8   (est. sk_syscall_stub_ecf8)
 * Ghidra: void FUN_0034ecf8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ecf8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED08 @ 0x0034ed08   (est. sk_syscall_ret0_ed08)
 * Ghidra: undefined8 FUN_0034ed08(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_ed08(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034ED18 @ 0x0034ed18   (est. sk_syscall_stub_ed18)
 * Ghidra: void FUN_0034ed18(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed18(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED28 @ 0x0034ed28   (est. sk_frag_ed28)
 * Ghidra: undefined1 [16] FUN_0034ed28(void)
 * Caller-frame pair load fragment.
 * Confidence: low
 * Notes: (references unaff_x29 / caller frame registers) */
cL4_w16_t sk_frag_ed28(void)
{
    /* returns { *(fp-0x58), *(fp-0x48) } from the caller frame. */
    cL4_w16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0034ED38 @ 0x0034ed38   (est. sk_syscall_stub_ed38)
 * Ghidra: void FUN_0034ed38(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed38(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED48 @ 0x0034ed48   (est. sk_syscall_stub_ed48)
 * Ghidra: void FUN_0034ed48(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed48(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED58 @ 0x0034ed58   (est. sk_syscall_stub_ed58)
 * Ghidra: void FUN_0034ed58(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed58(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED68 @ 0x0034ed68   (est. sk_syscall_stub_ed68)
 * Ghidra: void FUN_0034ed68(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed68(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED78 @ 0x0034ed78   (est. sk_syscall_stub_ed78)
 * Ghidra: void FUN_0034ed78(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed78(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED88 @ 0x0034ed88   (est. sk_syscall_stub_ed88)
 * Ghidra: void FUN_0034ed88(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed88(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034ED98 @ 0x0034ed98   (est. sk_syscall_stub_ed98)
 * Ghidra: void FUN_0034ed98(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ed98(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDA8 @ 0x0034eda8   (est. sk_syscall_stub_eda8)
 * Ghidra: void FUN_0034eda8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eda8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDB8 @ 0x0034edb8   (est. sk_syscall_stub_edb8)
 * Ghidra: void FUN_0034edb8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_edb8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDC8 @ 0x0034edc8   (est. sk_syscall_stub_edc8)
 * Ghidra: void FUN_0034edc8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_edc8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDD8 @ 0x0034edd8   (est. sk_syscall_stub_edd8)
 * Ghidra: void FUN_0034edd8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_edd8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDE8 @ 0x0034ede8   (est. sk_syscall_stub_ede8)
 * Ghidra: void FUN_0034ede8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ede8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EDF8 @ 0x0034edf8   (est. sk_syscall_stub_edf8)
 * Ghidra: void FUN_0034edf8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_edf8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE08 @ 0x0034ee08   (est. sk_syscall_stub_ee08)
 * Ghidra: void FUN_0034ee08(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee08(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE18 @ 0x0034ee18   (est. sk_syscall_stub_ee18)
 * Ghidra: void FUN_0034ee18(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee18(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE28 @ 0x0034ee28   (est. sk_syscall_stub_ee28)
 * Ghidra: void FUN_0034ee28(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee28(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE38 @ 0x0034ee38   (est. sk_syscall_stub_ee38)
 * Ghidra: void FUN_0034ee38(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee38(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE48 @ 0x0034ee48   (est. sk_syscall_stub_ee48)
 * Ghidra: void FUN_0034ee48(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee48(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE58 @ 0x0034ee58   (est. sk_syscall_stub_ee58)
 * Ghidra: void FUN_0034ee58(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee58(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE68 @ 0x0034ee68   (est. sk_pack_hi_ee68)
 * Ghidra: undefined1 [16] FUN_0034ee68(ulong param_1)
 * Packs value into the high 64-bit half of a 128-bit result.
 * Confidence: medium
 * Notes: */
cL4_w16_t sk_pack_hi_ee68(word_t value)
{
    cL4_w16_t r;
    r.lo = 0;
    r.hi = value;  /* packed into the upper 64-bit half of the result */
    return r;
}

/* FUN_0034EE78 @ 0x0034ee78   (est. sk_syscall_stub_ee78)
 * Ghidra: void FUN_0034ee78(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee78(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE88 @ 0x0034ee88   (est. sk_syscall_stub_ee88)
 * Ghidra: void FUN_0034ee88(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee88(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EE98 @ 0x0034ee98   (est. sk_syscall_stub_ee98)
 * Ghidra: void FUN_0034ee98(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ee98(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EEA8 @ 0x0034eea8   (est. sk_syscall_stub_eea8)
 * Ghidra: void FUN_0034eea8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eea8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EEB8 @ 0x0034eeb8   (est. sk_syscall_stub_eeb8)
 * Ghidra: void FUN_0034eeb8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eeb8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EEC8 @ 0x0034eec8   (est. sk_syscall_stub_eec8)
 * Ghidra: void FUN_0034eec8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eec8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EED8 @ 0x0034eed8   (est. sk_syscall_stub_eed8)
 * Ghidra: void FUN_0034eed8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eed8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EEE8 @ 0x0034eee8   (est. sk_syscall_stub_eee8)
 * Ghidra: void FUN_0034eee8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eee8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EEF8 @ 0x0034eef8   (est. sk_syscall_stub_eef8)
 * Ghidra: void FUN_0034eef8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_eef8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF08 @ 0x0034ef08   (est. sk_syscall_stub_ef08)
 * Ghidra: void FUN_0034ef08(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef08(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF18 @ 0x0034ef18   (est. sk_syscall_stub_ef18)
 * Ghidra: void FUN_0034ef18(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef18(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF28 @ 0x0034ef28   (est. sk_syscall_stub_ef28)
 * Ghidra: void FUN_0034ef28(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef28(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF38 @ 0x0034ef38   (est. sk_syscall_stub_ef38)
 * Ghidra: void FUN_0034ef38(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef38(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF48 @ 0x0034ef48   (est. sk_syscall_stub_ef48)
 * Ghidra: void FUN_0034ef48(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef48(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF58 @ 0x0034ef58   (est. sk_syscall_stub_ef58)
 * Ghidra: void FUN_0034ef58(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef58(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF68 @ 0x0034ef68   (est. sk_syscall_stub_ef68)
 * Ghidra: void FUN_0034ef68(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef68(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF78 @ 0x0034ef78   (est. sk_syscall_stub_ef78)
 * Ghidra: void FUN_0034ef78(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef78(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EF88 @ 0x0034ef88   (est. sk_syscall_ret0_ef88)
 * Ghidra: undefined8 FUN_0034ef88(void)
 * Returns 0 — an unimplemented syscall slot accepted as success.
 * Confidence: medium
 * Notes: */
word_t sk_syscall_ret0_ef88(void)
{
    /* returns 0 (success / unimplemented no-op slot) */
    return 0;
}

/* FUN_0034EF98 @ 0x0034ef98   (est. sk_syscall_stub_ef98)
 * Ghidra: void FUN_0034ef98(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_ef98(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

/* FUN_0034EFA8 @ 0x0034efa8   (est. sk_syscall_stub_efa8)
 * Ghidra: void FUN_0034efa8(void)
 * Empty syscall-dispatch table entry; performs no operation.
 * Confidence: medium
 * Notes: */
void sk_syscall_stub_efa8(void)
{
    /* no-op: bare ret (empty syscall dispatch slot) */
}

