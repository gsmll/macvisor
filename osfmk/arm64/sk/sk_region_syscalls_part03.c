/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 03: 0x31a99c-0x31d4e8 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"



/* Out-of-slice cL4 helper declarations (bodies reconstructed by their
 * range workers; K&R unspecified-args so calls with varying arity compile).
 * Return type: cl4_result_t where the 16-byte struct result is used, else
 * word_t (values read through x8/x0 that Ghidra exposes as returns). */
extern word_t FUN_000026e8(); /* out of slice 0x000026e8 */
extern word_t FUN_00019858(); /* out of slice 0x00019858 */
extern word_t FUN_00021480(); /* out of slice 0x00021480 */
extern word_t FUN_00027754(); /* out of slice 0x00027754 */
extern word_t FUN_00041138(); /* out of slice 0x00041138 */
extern cl4_result_t FUN_00084220(); /* out of slice 0x00084220 */
extern word_t FUN_00084234(); /* out of slice 0x00084234 */
extern word_t FUN_000e15d8(); /* out of slice 0x000e15d8 */
extern word_t FUN_00115080(); /* out of slice 0x00115080 */
extern word_t FUN_00115334(); /* out of slice 0x00115334 */
extern word_t FUN_0014ae44(); /* out of slice 0x0014ae44 */
extern word_t FUN_001afe4c(); /* out of slice 0x001afe4c */
extern word_t FUN_001d8808(); /* out of slice 0x001d8808 */
extern word_t FUN_001d8cdc(); /* out of slice 0x001d8cdc */
extern word_t FUN_001d9a94(); /* out of slice 0x001d9a94 */
extern word_t FUN_001dfc28(); /* out of slice 0x001dfc28 */
extern word_t FUN_001ee0fc(); /* out of slice 0x001ee0fc */
extern word_t FUN_001ee364(); /* out of slice 0x001ee364 */
extern word_t FUN_001f0e80(); /* out of slice 0x001f0e80 */
extern word_t FUN_001fe218(); /* out of slice 0x001fe218 */
extern word_t FUN_001ff7ec(); /* out of slice 0x001ff7ec */
extern word_t FUN_0020d620(); /* out of slice 0x0020d620 */
extern word_t FUN_0020f970(); /* out of slice 0x0020f970 */
extern word_t FUN_002120e4(); /* out of slice 0x002120e4 */
extern word_t FUN_0022fb38(); /* out of slice 0x0022fb38 */
extern word_t FUN_002487b8(); /* out of slice 0x002487b8 */
extern word_t FUN_002488b4(); /* out of slice 0x002488b4 */
extern word_t FUN_00248a34(); /* out of slice 0x00248a34 */
extern word_t FUN_002493c8(); /* out of slice 0x002493c8 */
extern word_t FUN_00249e20(); /* out of slice 0x00249e20 */
extern word_t FUN_0024a290(); /* out of slice 0x0024a290 */
extern word_t FUN_0024be2c(); /* out of slice 0x0024be2c */
extern word_t FUN_0024c0d0(); /* out of slice 0x0024c0d0 */
extern word_t FUN_0024c158(); /* out of slice 0x0024c158 */
extern word_t FUN_0024c7bc(); /* out of slice 0x0024c7bc */
extern word_t FUN_0024c82c(); /* out of slice 0x0024c82c */
extern word_t FUN_0024dbfc(); /* out of slice 0x0024dbfc */
extern word_t FUN_00251acc(); /* out of slice 0x00251acc */
extern word_t FUN_00253d94(); /* out of slice 0x00253d94 */
extern word_t FUN_00254020(); /* out of slice 0x00254020 */
extern word_t FUN_00255d88(); /* out of slice 0x00255d88 */
extern word_t FUN_00262690(); /* out of slice 0x00262690 */
extern word_t FUN_00277be4(); /* out of slice 0x00277be4 */
extern word_t FUN_0027d530(); /* out of slice 0x0027d530 */
extern word_t FUN_002a200c(); /* out of slice 0x002a200c */
extern word_t FUN_002a20cc(); /* out of slice 0x002a20cc */
extern word_t FUN_002a4340(); /* out of slice 0x002a4340 */
extern word_t FUN_00310954(); /* out of slice 0x00310954 */
extern word_t FUN_00310e08(); /* out of slice 0x00310e08 */
extern word_t FUN_00319338(); /* out of slice 0x00319338 */
extern word_t FUN_0031dc88(); /* out of slice 0x0031dc88 */
extern word_t FUN_0031dd04(); /* out of slice 0x0031dd04 */
extern word_t FUN_00344d14(); /* out of slice 0x00344d14 */
extern word_t FUN_00344dc8(); /* out of slice 0x00344dc8 */
extern word_t FUN_00348194(); /* out of slice 0x00348194 */
extern word_t FUN_00348284(); /* out of slice 0x00348284 */
extern word_t FUN_003482c4(); /* out of slice 0x003482c4 */
extern word_t FUN_00348508(); /* out of slice 0x00348508 */
extern cl4_result_t FUN_00349ea0(); /* out of slice 0x00349ea0 */
extern word_t FUN_0034b2e8(); /* out of slice 0x0034b2e8 */
extern word_t FUN_0034b3e8(); /* out of slice 0x0034b3e8 */
extern word_t FUN_0034b7b8(); /* out of slice 0x0034b7b8 */
extern word_t FUN_0034ce98(); /* out of slice 0x0034ce98 */
extern word_t FUN_00350308(); /* out of slice 0x00350308 */
extern word_t FUN_003504e8(); /* out of slice 0x003504e8 */
extern word_t FUN_00350518(); /* out of slice 0x00350518 */
extern word_t FUN_00350884(); /* out of slice 0x00350884 */
extern cl4_result_t FUN_003509bc(); /* out of slice 0x003509bc */
extern word_t FUN_00350b48(); /* out of slice 0x00350b48 */
extern word_t FUN_00351094(); /* out of slice 0x00351094 */
extern word_t FUN_00351244(); /* out of slice 0x00351244 */
extern word_t FUN_00351790(); /* out of slice 0x00351790 */
extern word_t FUN_00351b2c(); /* out of slice 0x00351b2c */
extern word_t FUN_00351cc4(); /* out of slice 0x00351cc4 */
extern word_t FUN_00351f10(); /* out of slice 0x00351f10 */
extern word_t FUN_00351fc0(); /* out of slice 0x00351fc0 */
extern word_t FUN_00352018(); /* out of slice 0x00352018 */
extern word_t FUN_003523f0(); /* out of slice 0x003523f0 */
extern word_t FUN_00352894(); /* out of slice 0x00352894 */
extern word_t FUN_00352ea8(); /* out of slice 0x00352ea8 */
extern word_t FUN_00352efc(); /* out of slice 0x00352efc */
extern word_t FUN_0035362c(); /* out of slice 0x0035362c */
extern word_t FUN_00353844(); /* out of slice 0x00353844 */
extern word_t FUN_0035396c(); /* out of slice 0x0035396c */
extern word_t FUN_00353c18(); /* out of slice 0x00353c18 */
extern word_t FUN_00354720(); /* out of slice 0x00354720 */
extern word_t FUN_00354d44(); /* out of slice 0x00354d44 */
extern word_t FUN_00355190(); /* out of slice 0x00355190 */
extern cl4_result_t FUN_003551c4(); /* out of slice 0x003551c4 */
extern word_t FUN_003551d8(); /* out of slice 0x003551d8 */
extern word_t FUN_00355ce4(); /* out of slice 0x00355ce4 */
extern word_t FUN_0035626c(); /* out of slice 0x0035626c */
extern word_t FUN_00356454(); /* out of slice 0x00356454 */
extern word_t FUN_003564e8(); /* out of slice 0x003564e8 */
extern word_t FUN_0035662c(); /* out of slice 0x0035662c */
extern word_t FUN_00356bb0(); /* out of slice 0x00356bb0 */
extern word_t FUN_00356d20(); /* out of slice 0x00356d20 */
extern word_t FUN_003571a4(); /* out of slice 0x003571a4 */
extern word_t FUN_00357640(); /* out of slice 0x00357640 */
extern word_t FUN_003580d4(); /* out of slice 0x003580d4 */
extern word_t FUN_003583dc(); /* out of slice 0x003583dc */
extern word_t FUN_0035847c(); /* out of slice 0x0035847c */
extern word_t FUN_0035860c(); /* out of slice 0x0035860c */
extern cl4_result_t FUN_003586d8(); /* out of slice 0x003586d8 */
extern word_t FUN_00358fa8(); /* out of slice 0x00358fa8 */
extern word_t FUN_00358fb4(); /* out of slice 0x00358fb4 */
extern word_t FUN_00358fc8(); /* out of slice 0x00358fc8 */
extern cl4_result_t FUN_00359abc(); /* out of slice 0x00359abc */
extern word_t FUN_00359ac8(); /* out of slice 0x00359ac8 */
extern word_t FUN_00359ae0(); /* out of slice 0x00359ae0 */
extern word_t FUN_0035a218(); /* out of slice 0x0035a218 */
extern word_t FUN_0035a38c(); /* out of slice 0x0035a38c */
extern word_t FUN_0035a690(); /* out of slice 0x0035a690 */
extern word_t FUN_0035aa40(); /* out of slice 0x0035aa40 */
extern word_t FUN_0036b118(); /* out of slice 0x0036b118 */
extern word_t FUN_0036b21c(); /* out of slice 0x0036b21c */
extern word_t FUN_0036b270(); /* out of slice 0x0036b270 */
extern word_t FUN_0036ffc0(); /* out of slice 0x0036ffc0 */
extern word_t FUN_00377824(); /* out of slice 0x00377824 */
extern word_t FUN_00377bec(); /* out of slice 0x00377bec */
extern word_t FUN_0039fcc4(); /* out of slice 0x0039fcc4 */
extern word_t FUN_003a25d4(); /* out of slice 0x003a25d4 */


/* Out-of-slice data symbols referenced by bodies (Ghidra names kept). */
extern unsigned char g_scan_mask0[16]; /* DAT_00114fd0 (16-byte OR mask) */
extern unsigned char g_scan_mask1[16]; /* DAT_00114fc0 (16-byte OR mask) */
extern uint64_t DAT_00614028;          /* operation table */
extern uint64_t DAT_00613f7c;          /* operation table */
extern uint64_t DAT_0000656140;        /* fixed-patch target */


/* Forward declarations for in-slice functions called before their definitions. */
void sk_method_call_then_flush_0031bb4c(word_t *ctx, word_t *ctx2);
void sk_op_fetch_0031cc00(); /* unspecified args */


/* FUN_0031a99c @ 0x0031a99c  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031a99c_0031a99c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031a99c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031a9cc @ 0x0031a9cc  (est. sk_obj_end_0x14)
 * Ghidra: long FUN_0031a9cc_0031a9cc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x14 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x14.
 * Confidence: medium */
long sk_obj_end_0x14_0031a9cc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}

/* FUN_0031a9fc @ 0x0031a9fc  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031a9fc_0031a9fc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031a9fc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031aa2c @ 0x0031aa2c  (est. sk_obj_end_0x1c)
 * Ghidra: long FUN_0031aa2c_0031aa2c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x1c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x1c.
 * Confidence: medium */
long sk_obj_end_0x1c_0031aa2c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}

/* FUN_0031ab1c @ 0x0031ab1c  (est. sk_obj_end_0x30)
 * Ghidra: long FUN_0031ab1c_0031ab1c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x30 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x30.
 * Confidence: medium */
long sk_obj_end_0x30_0031ab1c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x30) + (long)*(int *)(obj + 0x30);
}

/* FUN_0031ac3c @ 0x0031ac3c  (est. sk_obj_end_0x48)
 * Ghidra: long FUN_0031ac3c_0031ac3c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x48 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x48.
 * Confidence: medium */
long sk_obj_end_0x48_0031ac3c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x48) + (long)*(int *)(obj + 0x48);
}

/* FUN_0031ac9c @ 0x0031ac9c  (est. sk_obj_end_0x14)
 * Ghidra: long FUN_0031ac9c_0031ac9c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x14 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x14.
 * Confidence: medium */
long sk_obj_end_0x14_0031ac9c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}

/* FUN_0031accc @ 0x0031accc  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031accc_0031accc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031accc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031acfc @ 0x0031acfc  (est. sk_obj_end_0x1c)
 * Ghidra: long FUN_0031acfc_0031acfc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x1c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x1c.
 * Confidence: medium */
long sk_obj_end_0x1c_0031acfc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}

/* FUN_0031ad2c @ 0x0031ad2c  (est. sk_obj_end_0x20)
 * Ghidra: long FUN_0031ad2c_0031ad2c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x20 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x20.
 * Confidence: medium */
long sk_obj_end_0x20_0031ad2c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/* FUN_0031ad5c @ 0x0031ad5c  (est. sk_obj_end_0x24)
 * Ghidra: long FUN_0031ad5c_0031ad5c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x24 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x24.
 * Confidence: medium */
long sk_obj_end_0x24_0031ad5c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x24) + (long)*(int *)(obj + 0x24);
}

/* FUN_0031ae4c @ 0x0031ae4c  (est. sk_obj_end_0x38)
 * Ghidra: long FUN_0031ae4c_0031ae4c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x38 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x38.
 * Confidence: medium */
long sk_obj_end_0x38_0031ae4c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x38) + (long)*(int *)(obj + 0x38);
}

/* FUN_0031af6c @ 0x0031af6c  (est. sk_obj_end_0x50)
 * Ghidra: long FUN_0031af6c_0031af6c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x50 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x50.
 * Confidence: medium */
long sk_obj_end_0x50_0031af6c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x50) + (long)*(int *)(obj + 0x50);
}

/* FUN_0031afcc @ 0x0031afcc  (est. sk_obj_end_0x44)
 * Ghidra: long FUN_0031afcc_0031afcc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x44 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x44.
 * Confidence: medium */
long sk_obj_end_0x44_0031afcc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x44) + (long)*(int *)(obj + 0x44);
}

/* FUN_0031affc @ 0x0031affc  (est. sk_fixed_patch)
 * Ghidra: void FUN_0031affc_0031affc(void); one unreachable block (0x31b010) removed.
 * Decompiler artifact: writes a 64-bit constant into RAM at 0x656140. This
 * looks like a mis-decoded branch/data patch rather than a real routine body.
 * Confidence: low */
void sk_fixed_patch_0031affc(void)
{
    *(uint64_t *)0x656140 = 0x39000d28d378fc48ULL; /* DAT_0000656140, artifact */
}

/* FUN_0031b050 @ 0x0031b050  (est. sk_obj_end_0x58)
 * Ghidra: long FUN_0031b050_0031b050(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x58 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x58.
 * Confidence: medium */
long sk_obj_end_0x58_0031b050(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x58) + (long)*(int *)(obj + 0x58);
}

/* FUN_0031b080 @ 0x0031b080  (est. sk_stub_unsupported_0031b080)
 * Ghidra: void FUN_0031b080_0031b080(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b080_0031b080(void)
{
    return FUN_00021480();
}

/* FUN_0031b098 @ 0x0031b098  (est. sk_op_cap_test)
 * Ghidra: uint32_t FUN_0031b098_0031b098(undefined8 param_1)
 * Method-table entry (x20=context): runs the capability/bounds predicate
 * FUN_001d9a94 over param_1 and the context's fixed operands (offset 0x28, then
 * 0x10, 0x18, 0x20) and returns its truth bit.
 * Confidence: medium; Notes: callee FUN_001d9a94 out of slice */
uint32_t sk_op_cap_test_0031b098(word_t arg, word_t *ctx)
{
    return FUN_001d9a94(arg, ctx[5], ctx[2], ctx[3], ctx[4]) & 1;
}

/* FUN_0031b0bc @ 0x0031b0bc  (est. sk_obj_end_0x3c)
 * Ghidra: long FUN_0031b0bc_0031b0bc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x3c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x3c.
 * Confidence: medium */
long sk_obj_end_0x3c_0031b0bc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x3c) + (long)*(int *)(obj + 0x3c);
}

/* FUN_0031b0ec @ 0x0031b0ec  (est. sk_op_sync, dual slot)
 * Ghidra: void FUN_0031b0ec_0031b0ec(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both arguments plus the context's
 * operand words (0x20, 0x10, 0x18) to the shared worker FUN_001d8808.
 * Confidence: medium; Notes: callee FUN_001d8808 out of slice; identical body
 * at 0x31b0f0 (same handler in two dispatch slots). */
void sk_op_sync_0031b0ec(word_t a, word_t b, word_t *ctx)
{
    FUN_001d8808(a, ctx[4], ctx[2], ctx[3], b);
}

/* FUN_0031b0f0 @ 0x0031b0f0  (est. sk_op_sync_2, dual slot)
 * Ghidra: void FUN_0031b0ec_0031b0f0(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both arguments plus the context's
 * operand words (0x20, 0x10, 0x18) to the shared worker FUN_001d8808.
 * Confidence: medium; Notes: callee FUN_001d8808 out of slice; identical body
 * at 0x31b0f0 (same handler in two dispatch slots). */
void sk_op_sync_0031b0f0(word_t a, word_t b, word_t *ctx)
{
    FUN_001d8808(a, ctx[4], ctx[2], ctx[3], b);
}

/* FUN_0031b110 @ 0x0031b110  (est. sk_obj_end_0x40)
 * Ghidra: long FUN_0031b110_0031b110(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x40 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x40.
 * Confidence: medium */
long sk_obj_end_0x40_0031b110(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x40) + (long)*(int *)(obj + 0x40);
}

/* FUN_0031b140 @ 0x0031b140  (est. sk_op_wait_test, dual slot)
 * Ghidra: uint32_t FUN_0031b140_0031b140(undefined8 param_1)
 * Method-table entry (x20=context): runs predicate FUN_001d8cdc over param_1
 * and context operands (0x28, 0x10, 0x18, 0x20); returns truth bit.
 * Confidence: medium; Notes: callee FUN_001d8cdc out of slice; identical body
 * at 0x31b144 (dual dispatch slot). */
uint32_t sk_op_wait_test_0031b140(word_t arg, word_t *ctx)
{
    return FUN_001d8cdc(arg, ctx[5], ctx[2], ctx[3], ctx[4]) & 1;
}

/* FUN_0031b144 @ 0x0031b144  (est. sk_op_wait_test_2, dual slot)
 * Ghidra: uint32_t FUN_0031b140_0031b144(undefined8 param_1)
 * Method-table entry (x20=context): runs predicate FUN_001d8cdc over param_1
 * and context operands (0x28, 0x10, 0x18, 0x20); returns truth bit.
 * Confidence: medium; Notes: callee FUN_001d8cdc out of slice; identical body
 * at 0x31b144 (dual dispatch slot). */
uint32_t sk_op_wait_test_0031b144(word_t arg, word_t *ctx)
{
    return FUN_001d8cdc(arg, ctx[5], ctx[2], ctx[3], ctx[4]) & 1;
}

/* FUN_0031b164 @ 0x0031b164  (est. sk_obj_end_0xc)
 * Ghidra: long FUN_0031b164_0031b164(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc.
 * Confidence: medium */
long sk_obj_end_0xc_0031b164(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}

/* FUN_0031b194 @ 0x0031b194  (est. sk_obj_end_0x20)
 * Ghidra: long FUN_0031b194_0031b194(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x20 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x20.
 * Confidence: medium */
long sk_obj_end_0x20_0031b194(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/* FUN_0031b1c4 @ 0x0031b1c4  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031b1c4_0031b1c4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031b1c4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031b1f4 @ 0x0031b1f4  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031b1f4_0031b1f4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031b1f4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031b224 @ 0x0031b224  (est. sk_method_call_then_flush, dual slot)
 * Ghidra: void FUN_0031b224_0031b224(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x20;
 * if x21 (a preserved second context register) is non-null, follows with the
 * out-of-slice flush/teardown FUN_00354720.
 * Confidence: medium; Notes: identical body at 0x31bb4c (dual dispatch slot);
 * FUN_00354720 out of slice. */
void sk_method_call_then_flush_0031b224(word_t *ctx, word_t *ctx2)
{
    ((void (*)(void))ctx[4])();
    if (ctx2 != 0) {
        FUN_00354720();
    }
}

/* FUN_0031b258 @ 0x0031b258  (est. sk_op_teardown_pair)
 * Ghidra: void FUN_0031b258_0031b258(void)
 * Method-table entry: invokes the context teardown FUN_00359ae0 followed by the
 * out-of-slice deinit FUN_001dfc28.
 * Confidence: medium; Notes: callees FUN_00359ae0 / FUN_001dfc28 out of slice */
void sk_op_teardown_pair_0031b258(void)
{
    FUN_00359ae0();
    FUN_001dfc28();
}

/* FUN_0031b274 @ 0x0031b274  (est. sk_stub_unsupported_0031b274)
 * Ghidra: void FUN_0031b274_0031b274(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b274_0031b274(void)
{
    return FUN_00021480();
}

/* FUN_0031b28c @ 0x0031b28c  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031b28c_0031b28c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031b28c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031b2bc @ 0x0031b2bc  (est. sk_obj_end_0x54)
 * Ghidra: long FUN_0031b2bc_0031b2bc(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x54 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x54.
 * Confidence: medium */
long sk_obj_end_0x54_0031b2bc(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x54) + (long)*(int *)(obj + 0x54);
}

/* FUN_0031b2ec @ 0x0031b2ec  (est. sk_obj_end_0x50)
 * Ghidra: long FUN_0031b2ec_0031b2ec(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x50 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x50.
 * Confidence: medium */
long sk_obj_end_0x50_0031b2ec(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x50) + (long)*(int *)(obj + 0x50);
}

/* FUN_0031b31c @ 0x0031b31c  (est. sk_scan_zero_offset)
 * Ghidra: thunk_FUN_00115080(word_t param_1); uses NEON_uminv (byte-min
 * reduction); globals DAT_00114fd0 (16B mask) and DAT_00114fc0 (16B mask).
 * Vectorized scan: walk 16-byte-aligned chunks of the object, OR-ing each
 * chunk with a fixed 16-byte mask, until a byte position where
 * (data | mask0) == 0 is found (i.e. a zero data byte not covered by mask0).
 * The trailing chunk is OR-ed with a second mask (mask1) and the position of
 * the minimum (zero) byte yields the offset of the match relative to the
 * input pointer. If the low bit of the flag register (w18) is set, delegates
 * to FUN_00115334 instead. Semantics captured portably (NEON noted).
 * Confidence: low; Notes: masks at 0x114fd0 / 0x114fc0 out of slice */
long sk_scan_zero_offset_0031b31c_0031b31c(word_t obj, uint32_t flag)
{
    int i;
    if (flag & 1) {
        return FUN_00115334();
    }
    {
        const unsigned char *q = (const unsigned char *)(obj & ~0xfULL);
        for (;;) {
            unsigned char v[16], mn;
            for (i = 0; i < 16; i++) v[i] = (unsigned char)(q[i] | g_scan_mask0[i]);
            mn = v[0];
            for (i = 1; i < 16; i++) if (v[i] < mn) mn = v[i];
            if (mn == 0) {
                unsigned char pmin = (unsigned char)(q[0] | g_scan_mask1[0]);
                int pos = 0;
                for (i = 1; i < 16; i++) {
                    unsigned char c = (unsigned char)(q[i] | g_scan_mask1[i]);
                    if (c < pmin) { pmin = c; pos = i; }
                }
                return (long)(q - (const unsigned char *)obj) + pos;
            }
            q += 16;
        }
    }
}

/* FUN_0031b320 @ 0x0031b320  (est. sk_dispatch_0x18)
 * Ghidra: void FUN_0031b320_0031b320(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x18.
 * Confidence: medium */
void sk_dispatch_0x18_0031b320(word_t *ctx)
{
    ((void (*)(void))ctx[3])();
}

/* FUN_0031b348 @ 0x0031b348  (est. sk_op_teardown_variant)
 * Ghidra: void FUN_0031b348_0031b348(void)
 * Method-table entry: invokes FUN_00359ae0 then the out-of-slice FUN_002a4340.
 * Confidence: medium; Notes: callees out of slice */
void sk_op_teardown_variant_0031b348(void)
{
    FUN_00359ae0();
    FUN_002a4340();
}

/* FUN_0031b364 @ 0x0031b364  (est. sk_op_release)
 * Ghidra: void FUN_0031b364_0031b364(void)
 * Method-table entry: forwards to out-of-slice FUN_00344d14 (likely refcount
 * release / object free).
 * Confidence: medium; Notes: callee FUN_00344d14 out of slice */
void sk_op_release_0031b364(void)
{
    FUN_00344d14();
}

/* FUN_0031b37c @ 0x0031b37c  (est. sk_stub_unsupported_0031b37c)
 * Ghidra: void FUN_0031b37c_0031b37c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b37c_0031b37c(void)
{
    return FUN_00021480();
}

/* FUN_0031b394 @ 0x0031b394  (est. sk_op_allocate)
 * Ghidra: void FUN_0031b394_0031b394(void)
 * Method-table entry (x20=context): allocates an object of size x25 * the
 * context's element size, with a signed-overflow guard that traps
 * (SoftwareBreakpoint(1,0x31b43c)) if the 128-bit product does not fit in a
 * word. On negative/zero or a preallocated container (x22) it branches between
 * FUN_00348284 (error), FUN_000e15d8/FUN_002a200c/FUN_00019858/FUN_002a20cc
 * (fast/slow allocation paths) and FUN_00348508. Failure paths end in the
 * no-return FUN_001afe4c.
 * Confidence: low; Notes: heavy use of preserved regs (x20/x22/x25) and
 * extraout_* artifacts; all callees out of slice */
void sk_op_allocate_0031b394(word_t *ctx, long count, long prealloc)
{
    word_t obj_hdr = ctx[2];
    word_t uVar2 = FUN_00027754(ctx[4]);
    cl4_result_t r = FUN_00349ea0(uVar2, uVar2);
    FUN_00377824(r.lo, r.hi, obj_hdr);
    FUN_00351f10();
    {
        long size = count * (long)(ctx[9] & 0xffff); /* element size at +0x48 */
        long prod = count * (long)(ctx[9] & 0xffff);
        if (__builtin_mul_overflow(count, (long)(ctx[9] & 0xffff), &prod)) {
            /* WARNING: does not return */
            __builtin_trap(); /* SoftwareBreakpoint(1,0x31b43c) */
        }
        size = prod;
        if (size < 0) {
            FUN_00348284();
        } else if (size == 0 || prealloc != 0) {
            FUN_000e15d8();
            if ((FUN_002a200c() & 1) == 0) {
                (void)FUN_00019858();
            } else {
                FUN_000e15d8();
                (void)FUN_002a20cc();
            }
            return;
        } else {
            FUN_00348508();
        }
        FUN_00351094();
        FUN_001afe4c(); /* noreturn */
    }
}

/* FUN_0031b458 @ 0x0031b458  (est. sk_op_release_if_not_last)
 * Ghidra: void FUN_0031b458_0031b458(undefined8 param_1, long param_2)
 * Method-table entry: if the count/refcount (param_2) is 1, do nothing;
 * otherwise forward it to the out-of-slice decrement FUN_003a25d4.
 * Confidence: medium; Notes: callee FUN_003a25d4 out of slice; param_1 unused */
void sk_op_release_if_not_last_0031b458(word_t unused, long count)
{
    if (count == 1) {
        return;
    }
    FUN_003a25d4(count);
}

/* FUN_0031b46c @ 0x0031b46c  (est. sk_obj_end_0x8)
 * Ghidra: long FUN_0031b46c_0031b46c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x8.
 * Confidence: medium */
long sk_obj_end_0x8_0031b46c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}

/* FUN_0031b49c @ 0x0031b49c  (est. sk_obj_end_0x4)
 * Ghidra: long FUN_0031b49c_0031b49c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4.
 * Confidence: medium */
long sk_obj_end_0x4_0031b49c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}

/* FUN_0031b4cc @ 0x0031b4cc  (est. sk_dispatch_0x28)
 * Ghidra: void FUN_0031b4cc_0031b4cc(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x28.
 * Confidence: medium; Notes: identical bodies at 0x31cf88 and 0x31cff4
 * (multiple dispatch slots). */
void sk_dispatch_0x28_0031b4cc(word_t *ctx)
{
    ((void (*)(void))ctx[5])();
}

/* FUN_0031b4f4 @ 0x0031b4f4  (est. sk_obj_end_0x4)
 * Ghidra: long FUN_0031b4f4_0031b4f4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4.
 * Confidence: medium */
long sk_obj_end_0x4_0031b4f4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}

/* FUN_0031b524 @ 0x0031b524  (est. sk_stub_unsupported_0031b524)
 * Ghidra: void FUN_0031b524_0031b524(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b524_0031b524(void)
{
    return FUN_00021480();
}

/* FUN_0031b53c @ 0x0031b53c  (est. sk_op_forward7, dual slot)
 * Ghidra: void FUN_0031b53c_0031b53c(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus six context
 * operands (0x10..0x30) to out-of-slice FUN_001ee364.
 * Confidence: medium; Notes: callee FUN_001ee364 out of slice; identical body
 * at 0x31b540 (dual dispatch slot). */
void sk_op_forward7_0031b53c(word_t a, word_t b, word_t *ctx)
{
    FUN_001ee364(a, b, ctx[2], ctx[3], ctx[4], ctx[5], ctx[6]);
}

/* FUN_0031b540 @ 0x0031b540  (est. sk_op_forward7_2, dual slot)
 * Ghidra: void FUN_0031b53c_0031b540(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus six context
 * operands (0x10..0x30) to out-of-slice FUN_001ee364.
 * Confidence: medium; Notes: callee FUN_001ee364 out of slice; identical body
 * at 0x31b540 (dual dispatch slot). */
void sk_op_forward7_0031b540(word_t a, word_t b, word_t *ctx)
{
    FUN_001ee364(a, b, ctx[2], ctx[3], ctx[4], ctx[5], ctx[6]);
}

/* FUN_0031b560 @ 0x0031b560  (est. sk_stub_unsupported_0031b560)
 * Ghidra: void FUN_0031b560_0031b560(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b560_0031b560(void)
{
    return FUN_00021480();
}

/* FUN_0031b578 @ 0x0031b578  (est. sk_copy5words)
 * Ghidra: undefined8 * FUN_0031b578(undefined8 *param_1, undefined8 *param_2)
 * Initializes param_2 with FUN_000026e8 then copies five words from param_1 to
 * param_2, returning param_2 (a small struct copy / field load helper).
 * Confidence: medium; Notes: callee FUN_000026e8 out of slice */
word_t *sk_copy5words_0031b578(word_t *src, word_t *dst)
{
    FUN_000026e8(dst);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    return dst;
}

/* FUN_0031b5b8 @ 0x0031b5b8  (est. sk_op_flush_pair, dual slot)
 * Ghidra: void FUN_0031b5b8_0031b5b8(void)
 * Method-table entry: invokes FUN_003551d8 then out-of-slice FUN_001f0e80.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31b5bc. */
void sk_op_flush_pair_0031b5b8(void)
{
    FUN_003551d8();
    FUN_001f0e80();
}

/* FUN_0031b5bc @ 0x0031b5bc  (est. sk_op_flush_pair_2, dual slot)
 * Ghidra: void FUN_0031b5b8_0031b5bc(void)
 * Method-table entry: invokes FUN_003551d8 then out-of-slice FUN_001f0e80.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31b5bc. */
void sk_op_flush_pair_0031b5bc(void)
{
    FUN_003551d8();
    FUN_001f0e80();
}

/* FUN_0031b5e0 @ 0x0031b5e0  (est. sk_op_finalize_retain, dual slot)
 * Ghidra: void FUN_0031b5e0_0031b5e0(void)
 * Method-table entry (x20=context): retains the operand at context+0x30
 * (FUN_0036b118), runs FUN_00355ce4, then balances with FUN_0036b21c.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31b5e4. */
void sk_op_finalize_retain_0031b5e0(word_t *ctx)
{
    FUN_0036b118(ctx[6]);
    FUN_00355ce4();
    FUN_0036b21c();
}

/* FUN_0031b5e4 @ 0x0031b5e4  (est. sk_op_finalize_retain_2, dual slot)
 * Ghidra: void FUN_0031b5e0_0031b5e4(void)
 * Method-table entry (x20=context): retains the operand at context+0x30
 * (FUN_0036b118), runs FUN_00355ce4, then balances with FUN_0036b21c.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31b5e4. */
void sk_op_finalize_retain_0031b5e4(word_t *ctx)
{
    FUN_0036b118(ctx[6]);
    FUN_00355ce4();
    FUN_0036b21c();
}

/* FUN_0031b614 @ 0x0031b614  (est. sk_stub_unsupported_0031b614)
 * Ghidra: void FUN_0031b614_0031b614(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b614_0031b614(void)
{
    return FUN_00021480();
}

/* FUN_0031b62c @ 0x0031b62c  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031b62c_0031b62c(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031b62c(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031b65c @ 0x0031b65c  (est. sk_stub_unsupported_0031b65c)
 * Ghidra: void FUN_0031b65c_0031b65c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b65c_0031b65c(void)
{
    return FUN_00021480();
}

/* FUN_0031b674 @ 0x0031b674  (est. sk_stub_unsupported_0031b674)
 * Ghidra: void FUN_0031b674_0031b674(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b674_0031b674(void)
{
    return FUN_00021480();
}

/* FUN_0031b68c @ 0x0031b68c  (est. sk_op_settable)
 * Ghidra: void FUN_0031b68c_0031b68c(undefined8 param_1, undefined8 param_2)
 * Forwards both args to the setter dispatcher FUN_0036ffc0 with the operation
 * table DAT_00614028. The table address differs per slot (0x614028 here,
 * 0x613f7c at 0x31d3bc).
 * Confidence: medium; Notes: FUN_0036ffc0 out of slice; table DAT_00614028
 * / DAT_00613f7c are out-of-slice data */
void sk_op_settable_0031b68c(word_t a, word_t b)
{
    FUN_0036ffc0(a, b, &DAT_00614028);
}

/* FUN_0031b6a4 @ 0x0031b6a4  (est. sk_stub_unsupported_0031b6a4)
 * Ghidra: void FUN_0031b6a4_0031b6a4(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b6a4_0031b6a4(void)
{
    return FUN_00021480();
}

/* FUN_0031b6bc @ 0x0031b6bc  (est. sk_stub_unsupported_0031b6bc)
 * Ghidra: void FUN_0031b6bc_0031b6bc(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b6bc_0031b6bc(void)
{
    return FUN_00021480();
}

/* FUN_0031b6d4 @ 0x0031b6d4  (est. sk_op_lookup_test)
 * Ghidra: uint32_t FUN_0031b6d4_0031b6d4(undefined8 param_1, undefined8 param_2)
 * Runs the out-of-slice lookup FUN_0031dd04 over both args with the callback
 * FUN_0014ae44 and returns its truth bit.
 * Confidence: medium; Notes: FUN_0031dd04 out of slice; FUN_0014ae44 out of
 * slice (callback) */
uint32_t sk_op_lookup_test_0031b6d4(word_t a, word_t b)
{
    return FUN_0031dd04(a, b, FUN_0014ae44) & 1;
}

/* FUN_0031b704 @ 0x0031b704  (est. sk_stub_unsupported_0031b704)
 * Ghidra: void FUN_0031b704_0031b704(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b704_0031b704(void)
{
    return FUN_00021480();
}

/* FUN_0031b71c @ 0x0031b71c  (est. sk_stub_unsupported_0031b71c)
 * Ghidra: void FUN_0031b71c_0031b71c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b71c_0031b71c(void)
{
    return FUN_00021480();
}

/* FUN_0031b734 @ 0x0031b734  (est. sk_op_forward3)
 * Ghidra: void FUN_0031b734_0031b734(undefined8 param_1)
 * Method-table entry (x20=context): forwards param_1 plus context operands
 * (0x10, 0x18) to out-of-slice FUN_001fe218.
 * Confidence: medium; Notes: callee FUN_001fe218 out of slice */
void sk_op_forward3_0031b734(word_t a, word_t *ctx)
{
    FUN_001fe218(a, ctx[2], ctx[3]);
}

/* FUN_0031b760 @ 0x0031b760  (est. sk_stub_unsupported_0031b760)
 * Ghidra: void FUN_0031b760_0031b760(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b760_0031b760(void)
{
    return FUN_00021480();
}

/* FUN_0031b778 @ 0x0031b778  (est. sk_stub_unsupported_0031b778)
 * Ghidra: void FUN_0031b778_0031b778(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b778_0031b778(void)
{
    return FUN_00021480();
}

/* FUN_0031b790 @ 0x0031b790  (est. sk_op_forward5)
 * Ghidra: void FUN_0031b790_0031b790(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus context operands
 * (0x20, 0x10, 0x18) to out-of-slice FUN_001ff7ec.
 * Confidence: medium; Notes: callee FUN_001ff7ec out of slice */
void sk_op_forward5_0031b790(word_t a, word_t b, word_t *ctx)
{
    FUN_001ff7ec(a, b, ctx[4], ctx[2], ctx[3]);
}

/* FUN_0031b7c0 @ 0x0031b7c0  (est. sk_op_composite)
 * Ghidra: void FUN_0031b7c0_0031b7c0(void)
 * Method-table entry (x20=context): runs a long fixed sequence of out-of-slice
 * subsystem calls (lock/validate/broadcast/notify bookkeeping), threading the
 * context operand at +0x20 into FUN_00351b2c. Sequence:
 * FUN_00358fb4, FUN_0035662c, FUN_0034b2e8, FUN_00350b48, FUN_00377824,
 * FUN_0035626c, FUN_00350518, FUN_00352ea8, FUN_00377bec, FUN_00350308,
 * FUN_00310e08, FUN_00310954, FUN_0035a690, FUN_00351b2c, FUN_0035396c,
 * FUN_00358fc8.
 * Confidence: low; Notes: all callees out of slice; extraout_* register
 * artifacts make argument threading approximate */
void sk_op_composite_0031b7c0(word_t *ctx)
{
    word_t uVar1, extraout_x1;
    word_t uVar2 = ctx[4];
    FUN_00358fb4();
    FUN_0035662c();
    FUN_0034b2e8();
    FUN_00350b48();
    FUN_00377824();
    FUN_0035626c();
    FUN_00350518();
    FUN_00352ea8();
    uVar1 = FUN_00377bec();
    FUN_00350308();
    FUN_00310e08();
    FUN_00310954(uVar1);
    uVar1 = FUN_0035a690();
    FUN_00351b2c(uVar1, uVar2);
    (void)uVar1;
    uVar1 = FUN_0035396c();
    FUN_00358fc8(uVar1, extraout_x1);
}

/* FUN_0031b858 @ 0x0031b858  (est. sk_stub_unsupported_0031b858)
 * Ghidra: void FUN_0031b858_0031b858(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b858_0031b858(void)
{
    return FUN_00021480();
}

/* FUN_0031b870 @ 0x0031b870  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031b870_0031b870(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031b870(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031b8d0 @ 0x0031b8d0  (est. sk_obj_end_0x4)
 * Ghidra: long FUN_0031b8d0_0031b8d0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4.
 * Confidence: medium */
long sk_obj_end_0x4_0031b8d0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}

/* FUN_0031b900 @ 0x0031b900  (est. sk_obj_end_0xc)
 * Ghidra: long FUN_0031b900_0031b900(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc.
 * Confidence: medium */
long sk_obj_end_0xc_0031b900(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}

/* FUN_0031b930 @ 0x0031b930  (est. sk_stub_unsupported_0031b930)
 * Ghidra: void FUN_0031b930_0031b930(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b930_0031b930(void)
{
    return FUN_00021480();
}

/* FUN_0031b948 @ 0x0031b948  (est. sk_stub_unsupported_0031b948)
 * Ghidra: void FUN_0031b948_0031b948(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b948_0031b948(void)
{
    return FUN_00021480();
}

/* FUN_0031b978 @ 0x0031b978  (est. sk_stub_unsupported_0031b978)
 * Ghidra: void FUN_0031b978_0031b978(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b978_0031b978(void)
{
    return FUN_00021480();
}

/* FUN_0031b990 @ 0x0031b990  (est. sk_stub_unsupported_0031b990)
 * Ghidra: void FUN_0031b990_0031b990(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b990_0031b990(void)
{
    return FUN_00021480();
}

/* FUN_0031b9c0 @ 0x0031b9c0  (est. sk_stub_unsupported_0031b9c0)
 * Ghidra: void FUN_0031b9c0_0031b9c0(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031b9c0_0031b9c0(void)
{
    return FUN_00021480();
}

/* FUN_0031b9d8 @ 0x0031b9d8  (est. sk_obj_end_0x8)
 * Ghidra: long FUN_0031b9d8_0031b9d8(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x8.
 * Confidence: medium */
long sk_obj_end_0x8_0031b9d8(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}

/* FUN_0031ba08 @ 0x0031ba08  (est. sk_op_pair_d620, dual slot)
 * Ghidra: void FUN_0031ba08_0031ba08(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_0020d620.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31ba0c. */
void sk_op_pair_d620_0031ba08(void)
{
    FUN_00357640();
    FUN_0020d620();
}

/* FUN_0031ba0c @ 0x0031ba0c  (est. sk_op_pair_d620_2, dual slot)
 * Ghidra: void FUN_0031ba08_0031ba0c(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_0020d620.
 * Confidence: medium; Notes: callees out of slice; identical body at 0x31ba0c. */
void sk_op_pair_d620_0031ba0c(void)
{
    FUN_00357640();
    FUN_0020d620();
}

/* FUN_0031ba24 @ 0x0031ba24  (est. sk_op_retain)
 * Ghidra: void FUN_0031ba24_0031ba24(void)
 * Method-table entry: forwards to out-of-slice FUN_0031dc88 (retain).
 * Confidence: medium; Notes: callee FUN_0031dc88 out of slice */
void sk_op_retain_0031ba24(void)
{
    FUN_0031dc88();
}

/* FUN_0031ba3c @ 0x0031ba3c  (est. sk_stub_unsupported_0031ba3c)
 * Ghidra: void FUN_0031ba3c_0031ba3c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031ba3c_0031ba3c(void)
{
    return FUN_00021480();
}

/* FUN_0031ba54 @ 0x0031ba54  (est. sk_op_pair_f970, dual slot)
 * Ghidra: void FUN_0031ba54_0031ba54(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_0020f970.
 * Confidence: medium; Notes: identical body at 0x31ba58. */
void sk_op_pair_f970_0031ba54(void)
{
    FUN_00357640();
    FUN_0020f970();
}

/* FUN_0031ba58 @ 0x0031ba58  (est. sk_op_pair_f970_2, dual slot)
 * Ghidra: void FUN_0031ba54_0031ba58(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_0020f970.
 * Confidence: medium; Notes: identical body at 0x31ba58. */
void sk_op_pair_f970_0031ba58(void)
{
    FUN_00357640();
    FUN_0020f970();
}

/* FUN_0031ba70 @ 0x0031ba70  (est. sk_obj_end_0x20)
 * Ghidra: long FUN_0031ba70_0031ba70(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x20 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x20.
 * Confidence: medium */
long sk_obj_end_0x20_0031ba70(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/* FUN_0031baa0 @ 0x0031baa0  (est. sk_stub_unsupported_0031baa0)
 * Ghidra: void FUN_0031baa0_0031baa0(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031baa0_0031baa0(void)
{
    return FUN_00021480();
}

/* FUN_0031bab8 @ 0x0031bab8  (est. sk_obj_end_0x14)
 * Ghidra: long FUN_0031bab8_0031bab8(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x14 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x14.
 * Confidence: medium */
long sk_obj_end_0x14_0031bab8(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}

/* FUN_0031bae8 @ 0x0031bae8  (est. sk_op_pair_20e4, dual slot)
 * Ghidra: void FUN_0031bae8_0031bae8(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_002120e4.
 * Confidence: medium; Notes: identical body at 0x31baec. */
void sk_op_pair_20e4_0031bae8(void)
{
    FUN_00357640();
    FUN_002120e4();
}

/* FUN_0031baec @ 0x0031baec  (est. sk_op_pair_20e4_2, dual slot)
 * Ghidra: void FUN_0031bae8_0031baec(void)
 * Method-table entry: FUN_00357640 then out-of-slice FUN_002120e4.
 * Confidence: medium; Notes: identical body at 0x31baec. */
void sk_op_pair_20e4_0031baec(void)
{
    FUN_00357640();
    FUN_002120e4();
}

/* FUN_0031bb04 @ 0x0031bb04  (est. sk_stub_unsupported_0031bb04)
 * Ghidra: void FUN_0031bb04_0031bb04(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031bb04_0031bb04(void)
{
    return FUN_00021480();
}

/* FUN_0031bb1c @ 0x0031bb1c  (est. sk_stub_unsupported_0031bb1c)
 * Ghidra: void FUN_0031bb1c_0031bb1c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031bb1c_0031bb1c(void)
{
    return FUN_00021480();
}

/* FUN_0031bb34 @ 0x0031bb34  (est. sk_method_call_then_flush_wrap)
 * Ghidra: void FUN_0031bb34_0031bb34(void)
 * Thin wrapper: forwards to sk_method_call_then_flush (0x31bb4c).
 * Confidence: medium */
void sk_method_call_then_flush_wrap_0031bb34(word_t *ctx, word_t *ctx2)
{
    sk_method_call_then_flush_0031bb4c(ctx, ctx2);
}

/* FUN_0031bb4c @ 0x0031bb4c  (est. sk_method_call_then_flush_2, dual slot)
 * Ghidra: void FUN_0031b224_0031bb4c(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x20;
 * if x21 (a preserved second context register) is non-null, follows with the
 * out-of-slice flush/teardown FUN_00354720.
 * Confidence: medium; Notes: identical body at 0x31bb4c (dual dispatch slot);
 * FUN_00354720 out of slice. */
void sk_method_call_then_flush_0031bb4c(word_t *ctx, word_t *ctx2)
{
    ((void (*)(void))ctx[4])();
    if (ctx2 != 0) {
        FUN_00354720();
    }
}

/* FUN_0031bb80 @ 0x0031bb80  (est. sk_obj_end_0x4)
 * Ghidra: long FUN_0031bb80_0031bb80(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4.
 * Confidence: medium */
long sk_obj_end_0x4_0031bb80(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}

/* FUN_0031bbb0 @ 0x0031bbb0  (est. sk_obj_end_0xc)
 * Ghidra: long FUN_0031bbb0_0031bbb0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc.
 * Confidence: medium */
long sk_obj_end_0xc_0031bbb0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}

/* FUN_0031bbe0 @ 0x0031bbe0  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031bbe0_0031bbe0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031bbe0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031bc40 @ 0x0031bc40  (est. sk_stub_unsupported_0031bc40)
 * Ghidra: void FUN_0031bc40_0031bc40(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031bc40_0031bc40(void)
{
    return FUN_00021480();
}

/* FUN_0031bc58 @ 0x0031bc58  (est. sk_stub_unsupported_0031bc58)
 * Ghidra: void FUN_0031bc58_0031bc58(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031bc58_0031bc58(void)
{
    return FUN_00021480();
}

/* FUN_0031bc70 @ 0x0031bc70  (est. sk_obj_end_0x8)
 * Ghidra: long FUN_0031bc70_0031bc70(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x8.
 * Confidence: medium */
long sk_obj_end_0x8_0031bc70(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}

/* FUN_0031bca0 @ 0x0031bca0  (est. sk_op_init_region)
 * Ghidra: void FUN_0031bca0_0031bca0(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): initializes a region. Reads the context's
 * start (0x10) and parent (0x18), computes an aligned sub-region offset from
 * the byte at (base+0x50) (rounding), calls FUN_003504e8 with the parent, then
 * FUN_0035362c/FUN_0034b3e8 and dispatches into the object's method table
 * ((**)(extraout+8)) with the computed region; releases retained operands via
 * FUN_0036b118 / FUN_0036b21c.
 * Confidence: low; Notes: extraout_* and byte-at-+0x50 artifacts; all callees
 * out of slice */
void sk_op_init_region_0031bca0(word_t a, word_t b, word_t *ctx)
{
    word_t start = ctx[2];
    long lVar3 = (long)sk_stub_unsupported_0031bc40_0031bc40();
    word_t obj = ctx[3];
    FUN_003504e8(a, b, obj);
    FUN_0035362c();
    {
        unsigned char c = *(unsigned char *)(0 /*extraout_x16*/ + 0x50);
        word_t sub = (word_t)((c + 0x20) & (c ^ (word_t)-1));
        long lVar5 = *(long *)(0 /*extraout_x8*/ + 0x40);
        long lVar1 = (long)ctx + (long)sub;
        FUN_0034b3e8();
        (*(void (**)(long, word_t))(0 /*extraout_x16_00*/ + 8))(lVar1, start);
        FUN_0036b118(*(word_t *)(lVar1 + *(int *)(lVar3 + 0x2c) + 8));
        FUN_0036b118(*(word_t *)((long)ctx + (lVar5 + sub + 7 & ~7ULL) + 8));
        FUN_0036b21c();
    }
}

/* FUN_0031bd68 @ 0x0031bd68  (est. sk_op_validate)
 * Ghidra: uint32_t FUN_0031bd68_0031bd68(undefined8 param_1)
 * Method-table entry (x20=context): runs the validation chain. Calls
 * FUN_0031bc40, FUN_00352018, FUN_00353844 (with an aligned offset from the
 * byte at +0x50), then invokes two function pointers derived from the context
 * and the object's table: the first predicate on param_1, and if it returns
 * true the second handler, returning its truth bit.
 * Confidence: low; Notes: extraout_* artifacts; callees out of slice */
uint32_t sk_op_validate_0031bd68(word_t arg, word_t *ctx)
{
    (void)sk_stub_unsupported_0031bc40_0031bc40();
    FUN_00352018();
    {
        word_t (*pcVar1)(word_t) = *(word_t (**)(word_t))((long)ctx + 0 /*extraout_x9*/);
        long lVar3 = FUN_00353844((word_t)(*(unsigned char *)(0 /*+0x50*/) + 0x20) &
                                  (*(unsigned char *)(0 /*+0x50*/) ^ 0xff));
        word_t uVar4 = (*(word_t (**)(word_t))((long)ctx + *(int *)(lVar3 + 0x2c) + 0 /*extraout_x8*/))(arg);
        if ((uVar4 & 1) == 0) {
            return 0;
        }
        return pcVar1(arg) & 1;
    }
}

/* FUN_0031be18 @ 0x0031be18  (est. sk_stub_unsupported_0031be18)
 * Ghidra: void FUN_0031be18_0031be18(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031be18_0031be18(void)
{
    return FUN_00021480();
}

/* FUN_0031be30 @ 0x0031be30  (est. sk_op_allow, dual slot)
 * Ghidra: bool FUN_0031be30_0031be30(undefined8 param_1)
 * Method-table entry (x20=context): runs FUN_00350884(param_1, 1, ctx[3]) and
 * returns the negation of its zero flag (i.e. true when it succeeds).
 * Confidence: medium; Notes: callee FUN_00350884 out of slice; identical body
 * at 0x31be34. */
bool sk_op_allow_0031be30(word_t arg, word_t *ctx)
{
    return FUN_00350884(arg, 1, ctx[3]) != 0;
}

/* FUN_0031be34 @ 0x0031be34  (est. sk_op_allow_2, dual slot)
 * Ghidra: bool FUN_0031be30_0031be34(undefined8 param_1)
 * Method-table entry (x20=context): runs FUN_00350884(param_1, 1, ctx[3]) and
 * returns the negation of its zero flag (i.e. true when it succeeds).
 * Confidence: medium; Notes: callee FUN_00350884 out of slice; identical body
 * at 0x31be34. */
bool sk_op_allow_0031be34(word_t arg, word_t *ctx)
{
    return FUN_00350884(arg, 1, ctx[3]) != 0;
}

/* FUN_0031be60 @ 0x0031be60  (est. sk_stub_unsupported_0031be60)
 * Ghidra: void FUN_0031be60_0031be60(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031be60_0031be60(void)
{
    return FUN_00021480();
}

/* FUN_0031be78 @ 0x0031be78  (est. sk_stub_unsupported_0031be78)
 * Ghidra: void FUN_0031be78_0031be78(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031be78_0031be78(void)
{
    return FUN_00021480();
}

/* FUN_0031be90 @ 0x0031be90  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031be90_0031be90(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031be90(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031bec0 @ 0x0031bec0  (est. sk_obj_end_0xa8)
 * Ghidra: long FUN_0031bec0_0031bec0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xa8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xa8.
 * Confidence: medium */
long sk_obj_end_0xa8_0031bec0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xa8) + (long)*(int *)(obj + 0xa8);
}

/* FUN_0031bef0 @ 0x0031bef0  (est. sk_obj_end_0xac)
 * Ghidra: long FUN_0031bef0_0031bef0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xac plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xac.
 * Confidence: medium */
long sk_obj_end_0xac_0031bef0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xac) + (long)*(int *)(obj + 0xac);
}

/* FUN_0031bf20 @ 0x0031bf20  (est. sk_obj_end_0xb0)
 * Ghidra: long FUN_0031bf20_0031bf20(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xb0 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xb0.
 * Confidence: medium */
long sk_obj_end_0xb0_0031bf20(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xb0) + (long)*(int *)(obj + 0xb0);
}

/* FUN_0031bf50 @ 0x0031bf50  (est. sk_obj_end_0x44)
 * Ghidra: long FUN_0031bf50_0031bf50(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x44 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x44.
 * Confidence: medium */
long sk_obj_end_0x44_0031bf50(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x44) + (long)*(int *)(obj + 0x44);
}

/* FUN_0031bf80 @ 0x0031bf80  (est. sk_obj_end_0x9c)
 * Ghidra: long FUN_0031bf80_0031bf80(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x9c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x9c.
 * Confidence: medium */
long sk_obj_end_0x9c_0031bf80(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x9c) + (long)*(int *)(obj + 0x9c);
}

/* FUN_0031bfb0 @ 0x0031bfb0  (est. sk_obj_end_0x98)
 * Ghidra: long FUN_0031bfb0_0031bfb0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x98 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x98.
 * Confidence: medium */
long sk_obj_end_0x98_0031bfb0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x98) + (long)*(int *)(obj + 0x98);
}

/* FUN_0031bfe0 @ 0x0031bfe0  (est. sk_obj_end_0xa0)
 * Ghidra: long FUN_0031bfe0_0031bfe0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xa0 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xa0.
 * Confidence: medium */
long sk_obj_end_0xa0_0031bfe0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xa0) + (long)*(int *)(obj + 0xa0);
}

/* FUN_0031c070 @ 0x0031c070  (est. sk_obj_end_0x7c)
 * Ghidra: long FUN_0031c070_0031c070(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x7c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x7c.
 * Confidence: medium */
long sk_obj_end_0x7c_0031c070(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x7c) + (long)*(int *)(obj + 0x7c);
}

/* FUN_0031c0a0 @ 0x0031c0a0  (est. sk_obj_end_0x84)
 * Ghidra: long FUN_0031c0a0_0031c0a0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x84 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x84.
 * Confidence: medium */
long sk_obj_end_0x84_0031c0a0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x84) + (long)*(int *)(obj + 0x84);
}

/* FUN_0031c0d0 @ 0x0031c0d0  (est. sk_obj_end_0xcc)
 * Ghidra: long FUN_0031c0d0_0031c0d0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xcc plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xcc.
 * Confidence: medium */
long sk_obj_end_0xcc_0031c0d0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xcc) + (long)*(int *)(obj + 0xcc);
}

/* FUN_0031c100 @ 0x0031c100  (est. sk_obj_end_0xd0)
 * Ghidra: long FUN_0031c100_0031c100(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xd0 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xd0.
 * Confidence: medium */
long sk_obj_end_0xd0_0031c100(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xd0) + (long)*(int *)(obj + 0xd0);
}

/* FUN_0031c130 @ 0x0031c130  (est. sk_obj_end_0xc8)
 * Ghidra: long FUN_0031c130_0031c130(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc8.
 * Confidence: medium */
long sk_obj_end_0xc8_0031c130(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc8) + (long)*(int *)(obj + 0xc8);
}

/* FUN_0031c160 @ 0x0031c160  (est. sk_obj_end_0xb8)
 * Ghidra: long FUN_0031c160_0031c160(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xb8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xb8.
 * Confidence: medium */
long sk_obj_end_0xb8_0031c160(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xb8) + (long)*(int *)(obj + 0xb8);
}

/* FUN_0031c190 @ 0x0031c190  (est. sk_obj_end_0xc4)
 * Ghidra: long FUN_0031c190_0031c190(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc4.
 * Confidence: medium */
long sk_obj_end_0xc4_0031c190(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc4) + (long)*(int *)(obj + 0xc4);
}

/* FUN_0031c1c0 @ 0x0031c1c0  (est. sk_obj_end_0x54)
 * Ghidra: long FUN_0031c1c0_0031c1c0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x54 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x54.
 * Confidence: medium */
long sk_obj_end_0x54_0031c1c0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x54) + (long)*(int *)(obj + 0x54);
}

/* FUN_0031c1f0 @ 0x0031c1f0  (est. sk_obj_end_0x1c)
 * Ghidra: long FUN_0031c1f0_0031c1f0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x1c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x1c.
 * Confidence: medium */
long sk_obj_end_0x1c_0031c1f0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}

/* FUN_0031c220 @ 0x0031c220  (est. sk_obj_end_0xc0)
 * Ghidra: long FUN_0031c220_0031c220(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xc0 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xc0.
 * Confidence: medium */
long sk_obj_end_0xc0_0031c220(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xc0) + (long)*(int *)(obj + 0xc0);
}

/* FUN_0031c250 @ 0x0031c250  (est. sk_obj_end_0xbc)
 * Ghidra: long FUN_0031c250_0031c250(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xbc plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xbc.
 * Confidence: medium */
long sk_obj_end_0xbc_0031c250(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xbc) + (long)*(int *)(obj + 0xbc);
}

/* FUN_0031c280 @ 0x0031c280  (est. sk_obj_end_0x30)
 * Ghidra: long FUN_0031c280_0031c280(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x30 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x30.
 * Confidence: medium */
long sk_obj_end_0x30_0031c280(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x30) + (long)*(int *)(obj + 0x30);
}

/* FUN_0031c2b0 @ 0x0031c2b0  (est. sk_obj_end_0x34)
 * Ghidra: long FUN_0031c2b0_0031c2b0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x34 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x34.
 * Confidence: medium */
long sk_obj_end_0x34_0031c2b0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x34) + (long)*(int *)(obj + 0x34);
}

/* FUN_0031c2e0 @ 0x0031c2e0  (est. sk_obj_end_0x68)
 * Ghidra: long FUN_0031c2e0_0031c2e0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x68 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x68.
 * Confidence: medium */
long sk_obj_end_0x68_0031c2e0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x68) + (long)*(int *)(obj + 0x68);
}

/* FUN_0031c310 @ 0x0031c310  (est. sk_obj_end_0x3c)
 * Ghidra: long FUN_0031c310_0031c310(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x3c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x3c.
 * Confidence: medium */
long sk_obj_end_0x3c_0031c310(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x3c) + (long)*(int *)(obj + 0x3c);
}

/* FUN_0031c340 @ 0x0031c340  (est. sk_obj_end_0x38)
 * Ghidra: long FUN_0031c340_0031c340(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x38 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x38.
 * Confidence: medium */
long sk_obj_end_0x38_0031c340(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x38) + (long)*(int *)(obj + 0x38);
}

/* FUN_0031c370 @ 0x0031c370  (est. sk_obj_end_0x58)
 * Ghidra: long FUN_0031c370_0031c370(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x58 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x58.
 * Confidence: medium */
long sk_obj_end_0x58_0031c370(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x58) + (long)*(int *)(obj + 0x58);
}

/* FUN_0031c3a0 @ 0x0031c3a0  (est. sk_obj_end_0x4c)
 * Ghidra: long FUN_0031c3a0_0031c3a0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4c.
 * Confidence: medium */
long sk_obj_end_0x4c_0031c3a0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4c) + (long)*(int *)(obj + 0x4c);
}

/* FUN_0031c3d0 @ 0x0031c3d0  (est. sk_obj_end_0x48)
 * Ghidra: long FUN_0031c3d0_0031c3d0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x48 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x48.
 * Confidence: medium */
long sk_obj_end_0x48_0031c3d0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x48) + (long)*(int *)(obj + 0x48);
}

/* FUN_0031c400 @ 0x0031c400  (est. sk_obj_end_0x70)
 * Ghidra: long FUN_0031c400_0031c400(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x70 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x70.
 * Confidence: medium */
long sk_obj_end_0x70_0031c400(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x70) + (long)*(int *)(obj + 0x70);
}

/* FUN_0031c430 @ 0x0031c430  (est. sk_obj_end_0x78)
 * Ghidra: long FUN_0031c430_0031c430(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x78 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x78.
 * Confidence: medium */
long sk_obj_end_0x78_0031c430(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x78) + (long)*(int *)(obj + 0x78);
}

/* FUN_0031c460 @ 0x0031c460  (est. sk_obj_end_0x80)
 * Ghidra: long FUN_0031c460_0031c460(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x80 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x80.
 * Confidence: medium */
long sk_obj_end_0x80_0031c460(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x80) + (long)*(int *)(obj + 0x80);
}

/* FUN_0031c490 @ 0x0031c490  (est. sk_obj_end_0x4c)
 * Ghidra: long FUN_0031c490_0031c490(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x4c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x4c.
 * Confidence: medium */
long sk_obj_end_0x4c_0031c490(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x4c) + (long)*(int *)(obj + 0x4c);
}

/* FUN_0031c4c0 @ 0x0031c4c0  (est. sk_obj_end_0xa4)
 * Ghidra: long FUN_0031c4c0_0031c4c0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0xa4 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0xa4.
 * Confidence: medium */
long sk_obj_end_0xa4_0031c4c0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0xa4) + (long)*(int *)(obj + 0xa4);
}

/* FUN_0031c4f0 @ 0x0031c4f0  (est. sk_obj_end_0x50)
 * Ghidra: long FUN_0031c4f0_0031c4f0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x50 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x50.
 * Confidence: medium */
long sk_obj_end_0x50_0031c4f0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x50) + (long)*(int *)(obj + 0x50);
}

/* FUN_0031c520 @ 0x0031c520  (est. sk_obj_end_0x30)
 * Ghidra: long FUN_0031c520_0031c520(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x30 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x30.
 * Confidence: medium */
long sk_obj_end_0x30_0031c520(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x30) + (long)*(int *)(obj + 0x30);
}

/* FUN_0031c550 @ 0x0031c550  (est. sk_obj_end_0x34)
 * Ghidra: long FUN_0031c550_0031c550(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x34 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x34.
 * Confidence: medium */
long sk_obj_end_0x34_0031c550(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x34) + (long)*(int *)(obj + 0x34);
}

/* FUN_0031c580 @ 0x0031c580  (est. sk_obj_end_0x20)
 * Ghidra: long FUN_0031c580_0031c580(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x20 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x20.
 * Confidence: medium */
long sk_obj_end_0x20_0031c580(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/* FUN_0031c5b0 @ 0x0031c5b0  (est. sk_obj_end_0x24)
 * Ghidra: long FUN_0031c5b0_0031c5b0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x24 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x24.
 * Confidence: medium */
long sk_obj_end_0x24_0031c5b0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x24) + (long)*(int *)(obj + 0x24);
}

/* FUN_0031c5e0 @ 0x0031c5e0  (est. sk_obj_end_0x20)
 * Ghidra: long FUN_0031c5e0_0031c5e0(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x20 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x20.
 * Confidence: medium */
long sk_obj_end_0x20_0031c5e0(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/* FUN_0031c610 @ 0x0031c610  (est. sk_obj_end_0x28)
 * Ghidra: long FUN_0031c610_0031c610(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x28 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x28.
 * Confidence: medium */
long sk_obj_end_0x28_0031c610(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x28) + (long)*(int *)(obj + 0x28);
}

/* FUN_0031c640 @ 0x0031c640  (est. sk_obj_end_0x44)
 * Ghidra: long FUN_0031c640_0031c640(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x44 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x44.
 * Confidence: medium */
long sk_obj_end_0x44_0031c640(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x44) + (long)*(int *)(obj + 0x44);
}

/* FUN_0031c670 @ 0x0031c670  (est. sk_stub_unsupported_0031c670)
 * Ghidra: void FUN_0031c670_0031c670(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031c670_0031c670(void)
{
    return FUN_00021480();
}

/* FUN_0031c688 @ 0x0031c688  (est. sk_obj_end_0x18)
 * Ghidra: long FUN_0031c688_0031c688(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x18 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x18.
 * Confidence: medium */
long sk_obj_end_0x18_0031c688(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}

/* FUN_0031c748 @ 0x0031c748  (est. sk_stub_unsupported_0031c748)
 * Ghidra: void FUN_0031c748_0031c748(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031c748_0031c748(void)
{
    return FUN_00021480();
}

/* FUN_0031c760 @ 0x0031c760  (est. sk_noop)
 * Ghidra: void FUN_0031c760_0031c760(long param_1)
 * No-op: returns immediately regardless of the argument.
 * Confidence: medium */
void sk_noop_0031c760(long arg)
{
    (void)arg;
}

/* FUN_0031c788 @ 0x0031c788  (est. sk_obj_end_0x3c)
 * Ghidra: long FUN_0031c788_0031c788(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x3c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x3c.
 * Confidence: medium */
long sk_obj_end_0x3c_0031c788(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x3c) + (long)*(int *)(obj + 0x3c);
}

/* FUN_0031c7b8 @ 0x0031c7b8  (est. sk_op_foreach)
 * Ghidra: void FUN_0031c7b8_0031c7b8(undefined8 param_1, undefined8 param_2)
 * Runs the out-of-slice iterator FUN_00344dc8 over both args with the per-item
 * callback FUN_0022fb38.
 * Confidence: medium; Notes: FUN_00344dc8 / FUN_0022fb38 out of slice;
 * identical body at 0x31c7bc. */
void sk_op_foreach_0031c7b8(word_t a, word_t b)
{
    FUN_00344dc8(a, b, FUN_0022fb38);
}

/* FUN_0031c7bc @ 0x0031c7bc  (est. sk_op_foreach_2)
 * Ghidra: void FUN_0031c7b8_0031c7bc(undefined8 param_1, undefined8 param_2)
 * Runs the out-of-slice iterator FUN_00344dc8 over both args with the per-item
 * callback FUN_0022fb38.
 * Confidence: medium; Notes: FUN_00344dc8 / FUN_0022fb38 out of slice;
 * identical body at 0x31c7bc. */
void sk_op_foreach_0031c7bc(word_t a, word_t b)
{
    FUN_00344dc8(a, b, FUN_0022fb38);
}

/* FUN_0031c7e4 @ 0x0031c7e4  (est. sk_obj_end_0x54)
 * Ghidra: long FUN_0031c7e4_0031c7e4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x54 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x54.
 * Confidence: medium */
long sk_obj_end_0x54_0031c7e4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x54) + (long)*(int *)(obj + 0x54);
}

/* FUN_0031c874 @ 0x0031c874  (est. sk_obj_end_0x74)
 * Ghidra: long FUN_0031c874_0031c874(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x74 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x74.
 * Confidence: medium */
long sk_obj_end_0x74_0031c874(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x74) + (long)*(int *)(obj + 0x74);
}

/* FUN_0031c8a4 @ 0x0031c8a4  (est. sk_obj_end_0x7c)
 * Ghidra: long FUN_0031c8a4_0031c8a4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x7c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x7c.
 * Confidence: medium */
long sk_obj_end_0x7c_0031c8a4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x7c) + (long)*(int *)(obj + 0x7c);
}

/* FUN_0031c904 @ 0x0031c904  (est. sk_obj_end_0x60)
 * Ghidra: long FUN_0031c904_0031c904(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x60 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x60.
 * Confidence: medium */
long sk_obj_end_0x60_0031c904(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x60) + (long)*(int *)(obj + 0x60);
}

/* FUN_0031c964 @ 0x0031c964  (est. sk_obj_end_0x64)
 * Ghidra: long FUN_0031c964_0031c964(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x64 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x64.
 * Confidence: medium */
long sk_obj_end_0x64_0031c964(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x64) + (long)*(int *)(obj + 0x64);
}

/* FUN_0031c9c4 @ 0x0031c9c4  (est. sk_obj_end_0x3c)
 * Ghidra: long FUN_0031c9c4_0031c9c4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x3c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x3c.
 * Confidence: medium */
long sk_obj_end_0x3c_0031c9c4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x3c) + (long)*(int *)(obj + 0x3c);
}

/* FUN_0031c9f4 @ 0x0031c9f4  (est. sk_obj_end_0x10)
 * Ghidra: long FUN_0031c9f4_0031c9f4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x10 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x10.
 * Confidence: medium */
long sk_obj_end_0x10_0031c9f4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}

/* FUN_0031ca24 @ 0x0031ca24  (est. sk_stub_unsupported_0031ca24)
 * Ghidra: void FUN_0031ca24_0031ca24(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031ca24_0031ca24(void)
{
    return FUN_00021480();
}

/* FUN_0031ca3c @ 0x0031ca3c  (est. sk_stub_unsupported_0031ca3c)
 * Ghidra: void FUN_0031ca3c_0031ca3c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031ca3c_0031ca3c(void)
{
    return FUN_00021480();
}

/* FUN_0031ca54 @ 0x0031ca54  (est. sk_op_masked, dual slot)
 * Ghidra: void FUN_0031ca54_0031ca54(undefined8 param_1, undefined8 param_2, uint32_t param_3)
 * Builds a 16-byte result from FUN_003586d8 and FUN_00359abc then forwards it
 * with a masked flags value (param_3 & carry flag) to FUN_002493c8.
 * Confidence: low; Notes: extraout_w9 (carry) artifact; callees out of slice */
void sk_op_masked_0031ca54(word_t a, word_t b, uint32_t flags, word_t *ctx)
{
    cl4_result_t r = FUN_003586d8();
    (void)r;
    cl4_result_t rr = FUN_00359abc();
    (void)rr;
    uint32_t x = flags & 0 /*extraout_w9*/;
    FUN_002493c8(rr.lo, rr.hi, x);
}

/* FUN_0031ca58 @ 0x0031ca58  (est. sk_op_masked_2, dual slot)
 * Ghidra: void FUN_0031ca54_0031ca58(undefined8 param_1, undefined8 param_2, uint32_t param_3)
 * Builds a 16-byte result from FUN_003586d8 and FUN_00359abc then forwards it
 * with a masked flags value (param_3 & carry flag) to FUN_002493c8.
 * Confidence: low; Notes: extraout_w9 (carry) artifact; callees out of slice */
void sk_op_masked_0031ca58(word_t a, word_t b, uint32_t flags, word_t *ctx)
{
    cl4_result_t r = FUN_003586d8();
    (void)r;
    cl4_result_t rr = FUN_00359abc();
    (void)rr;
    uint32_t x = flags & 0 /*extraout_w9*/;
    FUN_002493c8(rr.lo, rr.hi, x);
}

/* FUN_0031ca7c @ 0x0031ca7c  (est. sk_op_chain)
 * Ghidra: void FUN_0031ca7c_0031ca7c(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): runs FUN_003571a4 over both args and ctx[3],
 * then dispatches through the method pointer at (extraout_x16 + 0x10) with the
 * resulting pointer.
 * Confidence: low; Notes: extraout_* artifacts; callees out of slice */
void sk_op_chain_0031ca7c(word_t a, word_t b, word_t *ctx)
{
    long lVar1 = FUN_003571a4(a, b, ctx[3]);
    (*(void (**)(word_t))(0 /*extraout_x16*/ + 0x10))(lVar1 + 0 /*extraout_x9*/);
}

/* FUN_0031cad8 @ 0x0031cad8  (est. sk_op_release_0x10, dual slot)
 * Ghidra: void FUN_0031cad8_0031cad8(void)
 * Method-table entry (x20=context): releases the retained operand at context
 * +0x10 (FUN_0036b118) then balances (FUN_0036b21c).
 * Confidence: medium; Notes: identical body at 0x31cadc. */
void sk_op_release_0x10_0031cad8(word_t *ctx)
{
    FUN_0036b118(ctx[2]);
    FUN_0036b21c();
}

/* FUN_0031cadc @ 0x0031cadc  (est. sk_op_release_0x10_2, dual slot)
 * Ghidra: void FUN_0031cad8_0031cadc(void)
 * Method-table entry (x20=context): releases the retained operand at context
 * +0x10 (FUN_0036b118) then balances (FUN_0036b21c).
 * Confidence: medium; Notes: identical body at 0x31cadc. */
void sk_op_release_0x10_0031cadc(word_t *ctx)
{
    FUN_0036b118(ctx[2]);
    FUN_0036b21c();
}

/* FUN_0031cb04 @ 0x0031cb04  (est. sk_op_drain)
 * Ghidra: void FUN_0031cb04_0031cb04(void)
 * Method-table entry (x20=context): drains a queue/list. Calls FUN_003564e8 and
 * FUN_0035860c, reads the head (0x20) and tail (0x30) pointers plus a scratch
 * slot (0x38). If the FUN_003551c4 range is empty, stores head->0x10 and 0.
 * Otherwise walks FUN_00248a34 / FUN_00249e20 (advance) collecting the new head
 * into the scratch slot, then publishes it and the old tail-0x10 to x22 and
 * releases the tail via FUN_0036b270. Ends with FUN_00356454.
 * Confidence: low; Notes: list-walk artifacts; callees out of slice */
void sk_op_drain_0031cb04(word_t *ctx, word_t *out)
{
    word_t lVar5 = 0;
    FUN_003564e8();
    (void)lVar5;
    FUN_0035860c();
    {
        word_t *head = (word_t *)ctx[4];
        word_t *tail = (word_t *)ctx[6];
        word_t *scratch = (word_t *)ctx[7];
        cl4_result_t r = FUN_003551c4();
        if (r.lo == 0 || r.hi == r.lo) {
            out[0] = *(word_t *)(head + 2);
            out[1] = 0;
        } else {
            word_t uVar4 = 0;
            while (1) {
                FUN_00248a34();
                FUN_0035a218(*(word_t *)(head + 2));
                uVar4 = FUN_00249e20();
                *(word_t *)(head + 2) = uVar4;
                if (lVar5 == 0) break;
                *scratch = lVar5;
                lVar5 = 0;
            }
            word_t uVar7 = *(word_t *)(tail + 2);
            out[0] = uVar4;
            out[1] = uVar7;
            FUN_0036b270(uVar7);
        }
        FUN_00356454(0 /*unaff_x30*/);
    }
}

/* FUN_0031cbbc @ 0x0031cbbc  (est. sk_op_masked7, dual slot)
 * Ghidra: void FUN_0031cbbc_0031cbbc(undefined8 param_1, undefined8 param_2, uint32_t param_3)
 * Builds a 16-byte value from FUN_003586d8 then forwards it, a masked flags
 * word, and six context operands to out-of-slice FUN_0024a290.
 * Confidence: low; Notes: extraout_w9 artifact; callees out of slice */
void sk_op_masked7_0031cbbc(word_t a, word_t b, uint32_t flags, word_t *ctx)
{
    cl4_result_t r = FUN_003586d8();
    FUN_0024a290(r.lo, r.hi, flags & 0 /*extraout_w9*/, ctx[4], ctx[5], ctx[2], ctx[3]);
}

/* FUN_0031cbc0 @ 0x0031cbc0  (est. sk_op_masked7_2, dual slot)
 * Ghidra: void FUN_0031cbbc_0031cbc0(undefined8 param_1, undefined8 param_2, uint32_t param_3)
 * Builds a 16-byte value from FUN_003586d8 then forwards it, a masked flags
 * word, and six context operands to out-of-slice FUN_0024a290.
 * Confidence: low; Notes: extraout_w9 artifact; callees out of slice */
void sk_op_masked7_0031cbc0(word_t a, word_t b, uint32_t flags, word_t *ctx)
{
    cl4_result_t r = FUN_003586d8();
    FUN_0024a290(r.lo, r.hi, flags & 0 /*extraout_w9*/, ctx[4], ctx[5], ctx[2], ctx[3]);
}

/* FUN_0031cbe4 @ 0x0031cbe4  (est. sk_op_fetch_wrap)
 * Ghidra: void FUN_0031cbe4_0031cbe4(void)
 * Thin wrapper: forwards to sk_op_fetch (0x31cc00).
 * Confidence: medium */
void sk_op_fetch_wrap_0031cbe4(void)
{
    sk_op_fetch_0031cc00();
}

/* FUN_0031cc00 @ 0x0031cc00  (est. sk_op_fetch)
 * Ghidra: void FUN_0031cc00_0031cc00(void)
 * Method-table entry (x20=context): calls FUN_0035860c, invokes the fetch
 * handler at context+0x20, and stores its 16-byte result through x22.
 * Confidence: low; Notes: 16-byte result via x22; callees out of slice */
void sk_op_fetch_0031cc00(word_t *ctx, void *out)
{
    (void)FUN_0035860c();
    *(void **)out = (*(void *(*)(void))ctx[4])();
}

/* FUN_0031cc3c @ 0x0031cc3c  (est. sk_stub_unsupported_0031cc3c)
 * Ghidra: void FUN_0031cc3c_0031cc3c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cc3c_0031cc3c(void)
{
    return FUN_00021480();
}

/* FUN_0031cc54 @ 0x0031cc54  (est. sk_stub_unsupported_0031cc54)
 * Ghidra: void FUN_0031cc54_0031cc54(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cc54_0031cc54(void)
{
    return FUN_00021480();
}

/* FUN_0031cc6c @ 0x0031cc6c  (est. sk_stub_unsupported_0031cc6c)
 * Ghidra: void FUN_0031cc6c_0031cc6c(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cc6c_0031cc6c(void)
{
    return FUN_00021480();
}

/* FUN_0031cc84 @ 0x0031cc84  (est. sk_op_getword)
 * Ghidra: void FUN_0031cc84_0031cc84(undefined8 *param_1)
 * Method-table entry: calls FUN_00354d44 then FUN_002487b8 and stores the
 * resulting word through param_1.
 * Confidence: medium; Notes: callees out of slice */
void sk_op_getword_0031cc84(word_t *out)
{
    FUN_00354d44();
    *out = FUN_002487b8();
}

/* FUN_0031cd00 @ 0x0031cd00  (est. sk_stub_unsupported_0031cd00)
 * Ghidra: void FUN_0031cd00_0031cd00(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cd00_0031cd00(void)
{
    return FUN_00021480();
}

/* FUN_0031cd18 @ 0x0031cd18  (est. sk_op_query)
 * Ghidra: void FUN_0031cd18_0031cd18(void)
 * Method-table entry (x20=context): runs FUN_00358fa8, FUN_00359abc(ctx[3]),
 * out-of-slice FUN_0024dbfc, and FUN_00351fc0 in sequence.
 * Confidence: low; Notes: callees out of slice */
void sk_op_query_0031cd18(word_t *ctx)
{
    FUN_00358fa8();
    FUN_00359abc(ctx[3]);
    FUN_0024dbfc();
    FUN_00351fc0();
}

/* FUN_0031cd48 @ 0x0031cd48  (est. sk_op_map)
 * Ghidra: void FUN_0031cd48_0031cd48(void)
 * Method-table entry (x20=context): maps a region. Reads size (0x10, decremented
 * by 8 with a SoftwareBreakpoint(1,0x31ce04) trap on underflow) and a vaddr (0x20).
 * On a non-negative 32-bit size it runs FUN_00355190/FUN_00351790, maps via
 * FUN_0024c0d0((uint32_t)size | 0xa0000000, 0), releases via FUN_0039fcc4, and for a
 * 32-bit vaddr does FUN_0027d530/FUN_0035aa40/FUN_0035847c. Error paths funnel
 * to FUN_003482c4/FUN_003583dc/FUN_00348194 and finally the no-return
 * FUN_001afe4c.
 * Confidence: low; Notes: stack args (0x20/0x28); callees out of slice */
void sk_op_map_0031cd48(word_t *ctx)
{
    word_t uVar1 = ctx[3];
    word_t uVar4 = ctx[4];
    word_t uVar2 = ctx[2] - 8;
    if (ctx[2] < 8) {
        __builtin_trap(); /* SoftwareBreakpoint(1,0x31ce04) */
    }
    if ((long)uVar2 < 0) {
        FUN_003482c4();
    } else if (uVar2 >> 32 == 0) {
        FUN_00355190();
        FUN_00351790();
        FUN_0024c0d0((uint32_t)uVar2 | 0xa0000000, 0);
        FUN_00355190();
        FUN_0039fcc4(uVar1);
        if ((long)uVar4 < 0) {
            FUN_003482c4();
        } else if (uVar4 >> 32 == 0) {
            FUN_0027d530();
            {
                word_t stack_zero = 0;
                FUN_0035aa40(&stack_zero);
            }
            FUN_0035847c(0 /*unaff_x30*/);
            return;
        } else {
            FUN_003583dc();
            FUN_00348194();
        }
    } else {
        FUN_003583dc();
        FUN_00348194();
    }
    FUN_003523f0();
    FUN_001afe4c(); /* noreturn */
}

/* FUN_0031ce04 @ 0x0031ce04  (est. sk_op_map_poll)
 * Ghidra: void FUN_0031ce04_0031ce04(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3, long param_4)
 * Method-table entry (x20=context): maps with polling. Reads size (0x10),
 * flags bytes (0x18..0x1a) and a target (0x20). For a non-negative 32-bit size
 * it assembles page-table bits (0x80000000 read-only when byte+0x18 set,
 * 0x40000000 from byte+0x19, 0x20000000 from byte+0x1a), runs
 * FUN_0024c82c/FUN_00351790, maps via FUN_0024c0d0(bits, 0), then walks
 * FUN_002488b4 / FUN_00248a34 / FUN_003580d4 / FUN_0024be2c until param_4
 * becomes 0, and finishes with FUN_0024c7bc / FUN_00352efc / FUN_001ee0fc /
 * FUN_0024c82c / FUN_00351790 / FUN_00351244 / FUN_0024c158. Error paths funnel
 * to FUN_003482c4/FUN_003583dc/FUN_00348194 and no-return FUN_001afe4c.
 * Confidence: low; Notes: byte flags + page-bit assembly; callees out of slice */
void sk_op_map_poll_0031ce04(word_t a, word_t b, word_t c, long poll, word_t *ctx)
{
    word_t uVar6 = ctx[2];
    unsigned char bVar2 = *(unsigned char *)((char *)ctx + 0x19);
    long lVar4 = (long)ctx[4];
    word_t local_58 = a;
    word_t uStack_50 = b;
    (void)c;
    if ((long)uVar6 < 0) {
        FUN_003482c4();
    } else if (uVar6 >> 32 == 0) {
        if (*(char *)((char *)ctx + 0x18) != '\0') {
            uVar6 = (word_t)((uint32_t)uVar6 | 0x80000000);
            bVar2 &= 1;
        }
        uint32_t uVar5 = (uint32_t)uVar6;
        if (bVar2 != 0) uVar5 |= 0x40000000;
        uint32_t uVar3 = 0x20000000;
        if (*(char *)((char *)ctx + 0x1a) == '\0') uVar3 = 0;
        FUN_0024c82c(4, 4);
        FUN_00351790();
        FUN_0024c0d0(uVar5 | uVar3, 0);
        FUN_0024c82c(4, 4);
        (void)FUN_002488b4(lVar4 + 0x18);
        FUN_003551c4();
        do {
            FUN_00248a34();
            uVar6 = FUN_003580d4();
            lVar4 = 0 /*extraout_x8*/;
            FUN_0024be2c(&local_58, (uVar6 >> 31) & 1, 0);
            poll = lVar4;
        } while (poll != 0);
        (void)FUN_0024c7bc(0 /*local_48._8_8_*/);
        FUN_00352efc();
        FUN_001ee0fc();
        FUN_0024c82c(8, 8);
        FUN_00351790();
        FUN_00351244();
        FUN_0024c158();
        return;
    } else {
        FUN_003583dc();
        FUN_00348194();
    }
    FUN_003523f0();
    FUN_001afe4c(); /* noreturn */
}

/* FUN_0031cf30 @ 0x0031cf30  (est. sk_stub_unsupported_0031cf30)
 * Ghidra: void FUN_0031cf30_0031cf30(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cf30_0031cf30(void)
{
    return FUN_00021480();
}

/* FUN_0031cf48 @ 0x0031cf48  (est. sk_op_forward7_b, dual slot)
 * Ghidra: void FUN_0031cf48_0031cf48(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus six context
 * operands (0x20,0x28,0x30,0x10,0x18) to out-of-slice FUN_00251acc.
 * Confidence: medium; Notes: callee FUN_00251acc out of slice; identical body
 * at 0x31cf4c. */
void sk_op_forward7_b_0031cf48(word_t a, word_t b, word_t *ctx)
{
    FUN_00251acc(a, ctx[4], ctx[5], ctx[6], ctx[2], ctx[3], b);
}

/* FUN_0031cf4c @ 0x0031cf4c  (est. sk_op_forward7_b_2, dual slot)
 * Ghidra: void FUN_0031cf48_0031cf4c(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus six context
 * operands (0x20,0x28,0x30,0x10,0x18) to out-of-slice FUN_00251acc.
 * Confidence: medium; Notes: callee FUN_00251acc out of slice; identical body
 * at 0x31cf4c. */
void sk_op_forward7_b_0031cf4c(word_t a, word_t b, word_t *ctx)
{
    FUN_00251acc(a, ctx[4], ctx[5], ctx[6], ctx[2], ctx[3], b);
}

/* FUN_0031cf70 @ 0x0031cf70  (est. sk_stub_unsupported_0031cf70)
 * Ghidra: void FUN_0031cf70_0031cf70(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cf70_0031cf70(void)
{
    return FUN_00021480();
}

/* FUN_0031cf88 @ 0x0031cf88  (est. sk_dispatch_0x28_2)
 * Ghidra: void FUN_0031b4cc_0031cf88(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x28.
 * Confidence: medium; Notes: identical bodies at 0x31cf88 and 0x31cff4
 * (multiple dispatch slots). */
void sk_dispatch_0x28_0031cf88(word_t *ctx)
{
    ((void (*)(void))ctx[5])();
}

/* FUN_0031cfb0 @ 0x0031cfb0  (est. sk_dispatch_0x28_1)
 * Ghidra: void FUN_0031cfb0_0031cfb0(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): calls the handler pointer at context+0x28
 * with param_2.
 * Confidence: medium */
void sk_dispatch_0x28_1_0031cfb0(word_t a, word_t b, word_t *ctx)
{
    (void)a;
    ((void (*)(word_t))ctx[5])(b);
}

/* FUN_0031cfdc @ 0x0031cfdc  (est. sk_stub_unsupported_0031cfdc)
 * Ghidra: void FUN_0031cfdc_0031cfdc(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031cfdc_0031cfdc(void)
{
    return FUN_00021480();
}

/* FUN_0031cff4 @ 0x0031cff4  (est. sk_dispatch_0x28_3)
 * Ghidra: void FUN_0031b4cc_0031cff4(void)
 * Method-table entry (x20=context): calls the handler pointer at context+0x28.
 * Confidence: medium; Notes: identical bodies at 0x31cf88 and 0x31cff4
 * (multiple dispatch slots). */
void sk_dispatch_0x28_0031cff4(word_t *ctx)
{
    ((void (*)(void))ctx[5])();
}

/* FUN_0031d024 @ 0x0031d024  (est. sk_op_init_region2)
 * Ghidra: void FUN_0031d024_0031d024(void)
 * Method-table entry (x20=context): region init variant. Builds a key from
 * FUN_00084220, calls FUN_003504e8 with ctx[3]/ctx[5], resolves an object via
 * FUN_00319338/FUN_0035362c, releases ctx[7] (FUN_0036b118), computes an
 * aligned sub-region from the byte at +0x50, dispatches the method at
 * (extraout_x16_00+8), then FUN_00084234/FUN_0036b21c.
 * Confidence: low; Notes: extraout_* artifacts; callees out of slice */
void sk_op_init_region2_0031d024(word_t *ctx)
{
    cl4_result_t r = FUN_00084220();
    word_t uVar2 = ctx[2];
    FUN_003504e8(r.lo, r.hi, ctx[3], ctx[5]);
    (void)FUN_00319338();
    FUN_0035362c();
    {
        unsigned char bVar3 = *(unsigned char *)(0 /*+0x50*/);
        FUN_0036b118(ctx[7]);
        long lVar1 = (long)ctx + ((word_t)bVar3 + 0x40 & (bVar3 ^ (word_t)-1));
        FUN_0034b3e8();
        (*(void (**)(long, word_t))(0 /*extraout_x16_00*/ + 8))(lVar1, uVar2);
        FUN_0036b118(*(word_t *)(lVar1 + *(int *)((long)0 /*lVar4*/ + 0x34) + 8));
        FUN_00084234();
        FUN_0036b21c();
    }
}

/* FUN_0031d0e0 @ 0x0031d0e0  (est. sk_op_query_map)
 * Ghidra: void FUN_0031d0e0_0031d0e0(void)
 * Method-table entry (x20=context): query/map sequence. FUN_00084220,
 * FUN_00351cc4, FUN_0034b7b8, FUN_00319338, then FUN_00353c18 with the result
 * of FUN_00351f10, ctx[6], ctx[7] and an aligned region, then FUN_0035a38c,
 * FUN_00084234, out-of-slice FUN_00253d94.
 * Confidence: low; Notes: callees out of slice */
void sk_op_query_map_0031d0e0(word_t *ctx)
{
    (void)FUN_00084220();
    FUN_00351cc4();
    FUN_0034b7b8();
    (void)FUN_00319338();
    {
        word_t uVar1 = FUN_00351f10();
        long rgn = (long)ctx + ((word_t)(*(unsigned char *)(0 /*+0x50*/) + 0x40) &
                                (*(unsigned char *)(0 /*+0x50*/) ^ (word_t)-1));
        FUN_00353c18(uVar1, ctx[6], ctx[7], rgn);
    }
    FUN_0035a38c();
    FUN_00084234();
    FUN_00253d94();
}

/* FUN_0031d150 @ 0x0031d150  (est. sk_op_init_region3)
 * Ghidra: void FUN_0031d150_0031d150(void)
 * Method-table entry (x20=context): region init variant using FUN_00356bb0 /
 * FUN_0034ce98 instead of FUN_003504e8.
 * Confidence: low; Notes: extraout_* artifacts; callees out of slice */
void sk_op_init_region3_0031d150(word_t *ctx)
{
    cl4_result_t r = FUN_00084220();
    word_t uVar2 = ctx[2];
    FUN_00356bb0(ctx[5]);
    FUN_0034ce98();
    (void)FUN_00319338();
    FUN_0035362c();
    {
        unsigned char bVar3 = *(unsigned char *)(0 /*+0x50*/);
        FUN_0036b118(ctx[7]);
        long lVar1 = (long)ctx + ((word_t)bVar3 + 0x40 & (bVar3 ^ (word_t)-1));
        FUN_0034b3e8();
        (*(void (**)(long, word_t))(0 /*extraout_x16_00*/ + 8))(lVar1, uVar2);
        FUN_0036b118(*(word_t *)(lVar1 + *(int *)((long)0 /*lVar4*/ + 0x34) + 8));
        FUN_00084234();
        FUN_0036b21c();
    }
}

/* FUN_0031d210 @ 0x0031d210  (est. sk_op_query_map2)
 * Ghidra: void FUN_0031d210_0031d210(void)
 * Method-table entry (x20=context): query/map sequence variant using
 * FUN_00356bb0, finishing with out-of-slice FUN_00254020.
 * Confidence: low; Notes: callees out of slice */
void sk_op_query_map2_0031d210(word_t *ctx)
{
    (void)FUN_00084220();
    FUN_00351cc4();
    FUN_00356bb0(ctx[5]);
    FUN_0034b7b8();
    (void)FUN_00319338();
    {
        word_t uVar1 = FUN_00351f10();
        long rgn = (long)ctx + ((word_t)(*(unsigned char *)(0 /*+0x50*/) + 0x40) &
                                (*(unsigned char *)(0 /*+0x50*/) ^ (word_t)-1));
        FUN_00353c18(uVar1, ctx[6], ctx[7], rgn);
    }
    FUN_0035a38c();
    FUN_00084234();
    FUN_00254020();
}

/* FUN_0031d284 @ 0x0031d284  (est. sk_op_forward6, dual slot)
 * Ghidra: void FUN_0031d284_0031d284(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus four context
 * operands (0x18,0x20,0x28,0x10) to out-of-slice FUN_00255d88.
 * Confidence: medium; Notes: callee FUN_00255d88 out of slice; identical body
 * at 0x31d288. */
void sk_op_forward6_0031d284(word_t a, word_t b, word_t *ctx)
{
    FUN_00255d88(a, ctx[3], ctx[4], ctx[5], ctx[2], b);
}

/* FUN_0031d288 @ 0x0031d288  (est. sk_op_forward6_2, dual slot)
 * Ghidra: void FUN_0031d284_0031d288(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus four context
 * operands (0x18,0x20,0x28,0x10) to out-of-slice FUN_00255d88.
 * Confidence: medium; Notes: callee FUN_00255d88 out of slice; identical body
 * at 0x31d288. */
void sk_op_forward6_0031d288(word_t a, word_t b, word_t *ctx)
{
    FUN_00255d88(a, ctx[3], ctx[4], ctx[5], ctx[2], b);
}

/* FUN_0031d2a8 @ 0x0031d2a8  (est. sk_op_composite2)
 * Ghidra: void FUN_0031d2a8_0031d2a8(void)
 * Method-table entry (x20=context): composite sequence threading ctx[3] into
 * FUN_00352894 and a FUN_003509bc result into out-of-slice FUN_00277be4.
 * Confidence: low; Notes: extraout_* artifacts; callees out of slice */
void sk_op_composite2_0031d2a8(word_t *ctx)
{
    word_t uVar1, extraout_x1;
    FUN_00358fb4();
    FUN_0035662c();
    FUN_00352894(ctx[3]);
    FUN_0034b2e8();
    FUN_00350b48();
    uVar1 = FUN_00377824();
    FUN_0035626c();
    FUN_00350518();
    FUN_00352ea8();
    FUN_00377bec();
    {
        cl4_result_t r = FUN_003509bc();
        FUN_00277be4(r.lo, r.hi, uVar1);
    }
    uVar1 = FUN_0035396c();
    FUN_00358fc8(uVar1, extraout_x1);
}

/* FUN_0031d324 @ 0x0031d324  (est. sk_op_composite3)
 * Ghidra: void FUN_0031d324_0031d324(void)
 * Same composite sequence as sk_op_composite2 but ends with FUN_00356d20
 * instead of FUN_003509bc.
 * Confidence: low; Notes: callees out of slice */
void sk_op_composite3_0031d324(word_t *ctx)
{
    word_t uVar1, extraout_x1;
    FUN_00358fb4();
    FUN_0035662c();
    FUN_00352894(ctx[3]);
    FUN_0034b2e8();
    FUN_00350b48();
    uVar1 = FUN_00377824();
    FUN_0035626c();
    FUN_00350518();
    FUN_00352ea8();
    FUN_00377bec();
    {
        cl4_result_t r = FUN_003509bc();
        FUN_00277be4(r.lo, r.hi, uVar1);
    }
    uVar1 = FUN_00356d20();
    FUN_00358fc8(uVar1, extraout_x1);
}

/* FUN_0031d3a4 @ 0x0031d3a4  (est. sk_stub_unsupported_0031d3a4)
 * Ghidra: void FUN_0031d3a4_0031d3a4(void)
 * Stub that forwards to the shared out-of-range routine FUN_00021480 (region
 * 0x00020000, not this slice). Likely the "unsupported/unimplemented syscall"
 * or empty-method no-op handler. Returned word is whatever FUN_00021480 leaves
 * in x0.
 * Confidence: medium */
word_t sk_stub_unsupported_0031d3a4_0031d3a4(void)
{
    return FUN_00021480();
}

/* FUN_0031d3bc @ 0x0031d3bc  (est. sk_op_settable_2)
 * Ghidra: void FUN_0031b68c_0031d3bc(undefined8 param_1, undefined8 param_2)
 * Forwards both args to the setter dispatcher FUN_0036ffc0 with the operation
 * table DAT_00614028. The table address differs per slot (0x614028 here,
 * 0x613f7c at 0x31d3bc).
 * Confidence: medium; Notes: FUN_0036ffc0 out of slice; table DAT_00614028
 * / DAT_00613f7c are out-of-slice data */
void sk_op_settable_0031d3bc(word_t a, word_t b)
{
    FUN_0036ffc0(a, b, &DAT_00614028);
}

/* FUN_0031d3d4 @ 0x0031d3d4  (est. sk_obj_end_0x8)
 * Ghidra: long FUN_0031d3d4_0031d3d4(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x8 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x8.
 * Confidence: medium */
long sk_obj_end_0x8_0031d3d4(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}

/* FUN_0031d404 @ 0x0031d404  (est. sk_op_forward4)
 * Ghidra: void FUN_0031d404_0031d404(undefined8 param_1, undefined8 param_2)
 * Method-table entry (x20=context): forwards both args plus context operands
 * (0x10,0x18,0x20) to out-of-slice FUN_00262690.
 * Confidence: medium; Notes: callee FUN_00262690 out of slice */
void sk_op_forward4_0031d404(word_t a, word_t b, word_t *ctx)
{
    FUN_00262690(a, ctx[2], ctx[3], ctx[4], b);
}

/* FUN_0031d428 @ 0x0031d428  (est. sk_obj_end_0x14)
 * Ghidra: long FUN_0031d428_0031d428(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x14 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x14.
 * Confidence: medium */
long sk_obj_end_0x14_0031d428(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}

/* FUN_0031d458 @ 0x0031d458  (est. sk_obj_end_0x30)
 * Ghidra: long FUN_0031d458_0031d458(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x30 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x30.
 * Confidence: medium */
long sk_obj_end_0x30_0031d458(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x30) + (long)*(int *)(obj + 0x30);
}

/* FUN_0031d488 @ 0x0031d488  (est. sk_obj_end_0x34)
 * Ghidra: long FUN_0031d488_0031d488(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x34 plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x34.
 * Confidence: medium */
long sk_obj_end_0x34_0031d488(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x34) + (long)*(int *)(obj + 0x34);
}

/* FUN_0031d4e8 @ 0x0031d4e8  (est. sk_obj_end_0x1c)
 * Ghidra: long FUN_0031d4e8_0031d4e8(ulong param_1)
 * Tagged-object region-end accessor: if the low bit of the object reference is
 * set it is an indirect/tagged pointer, so dereference it first. Returns
 * base+0x1c plus the signed length stored at that offset, i.e. the end of
 * the object region whose header lives at offset 0x1c.
 * Confidence: medium */
long sk_obj_end_0x1c_0031d4e8(word_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(word_t *)(obj & 0xfffffffffffffffe);
    }
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}
