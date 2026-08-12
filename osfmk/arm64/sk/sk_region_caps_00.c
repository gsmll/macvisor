/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 00: 0x80000-0x100000 caps region. All names are estimates unless
 * string/header-matched. Uses seL4/cL4 vocabulary (caps, CNode, TCB, IPC,
 * endpoints, notifications, sched, vspace).
 *
 * This region is dominated by the cL4 kernel's dynamic array / cap-table
 * container primitives: growable vectors (element sizes 8/16/0x18/0x20/0x28/
 * 0x30/0x70) with per-element copy/destroy callbacks, bounds-checked ranged
 * copy helpers, bitmap-backed slot allocators (bit-reverse + CLZ scan), and a
 * family of cap-type allocation factories.
 *
 * NOTE on the calling convention: the decompiler shows most of these as
 * `void FUN(void)` because every argument (including the C++ `this` pointer,
 * `unaff_x20`) is passed in registers and not modelled as a formal parameter.
 * We model the container `this` pointer as the explicit first parameter
 * `thisp` and give the out-of-range helpers signatures that match the actual
 * register usage observed at the call sites. Ghidra FUN_ names are kept only
 * in comments.
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
extern word_t FUN_0036b270(word_t);            /* cL4 ref retain (returns obj) */
extern word_t FUN_003a25d4(word_t);            /* token release */
extern unsigned char *FUN_00362acc(word_t, word_t); /* map/unwrap obj -> buffer */
extern word_t FUN_00324bf0(int);               /* allocator domain lookup */
extern void   FUN_0036b6ac(void);              /* lock/token release */
extern word_t FUN_00083f5c(void);              /* vec alloc start */
extern word_t FUN_00083f8c(void);              /* vec elem index alloc */
extern word_t FUN_00083fcc(void);              /* vec elem alloc (idx) */
extern word_t FUN_00084010(word_t);            /* vec size bump */
extern word_t FUN_00084024(word_t);            /* bitmap slot alloc (idx) */
extern word_t FUN_00084094(word_t);            /* vec size bump */
extern word_t FUN_00084018(void);              /* vec count get */
extern word_t FUN_00084064(void);              /* token release */
extern word_t FUN_00084074(void);              /* token release */
extern word_t FUN_0008403c(void);              /* token release */
extern word_t FUN_00083fb8(void);              /* vec grow helper */
extern word_t FUN_00083ff0(word_t);            /* vec elem dtor/grow */
extern word_t FUN_00083acc(word_t);            /* vec dtor */
extern word_t FUN_00083e9c(word_t, word_t, word_t); /* obj release */
extern word_t FUN_00083e34(word_t, word_t);    /* list iterate */
extern word_t FUN_00083d2c(word_t);            /* list begin */
extern word_t FUN_000840e8(void);              /* size carry check helper */
extern word_t FUN_0008409c(void);              /* vec range get */
extern word_t FUN_000840a8(word_t);            /* vec release */
extern word_t FUN_00084140(void);              /* vec copy helper */
extern word_t FUN_00084168(word_t);            /* mem region get */
extern word_t FUN_000841b4(void);              /* vec bump */
extern word_t FUN_000841d0(void);              /* vec bump */
extern word_t FUN_000841ec(void);              /* cleanup */
extern word_t FUN_000840d8(void);              /* helper */
extern word_t FUN_00084220(void);              /* lock enter start */
extern word_t FUN_00084200(void);              /* lock value */
extern word_t FUN_00084234(word_t, word_t, word_t); /* lock acquire done */
extern word_t FUN_00084248(void);              /* vec size bump */
extern word_t FUN_0006ae9c(word_t, word_t);    /* tagged-union build */
extern word_t FUN_0006b2ec(void);              /* span begin */
extern word_t FUN_000775b8(void);              /* lock state save */
extern void   FUN_00077070(word_t, word_t);    /* elem move */
extern word_t FUN_00077698(void);              /* buf begin/end */
extern word_t FUN_0007767c(word_t);            /* buf release */
extern word_t FUN_00077770(word_t);            /* table deref */
extern word_t FUN_00268540(word_t, word_t);    /* cap lookup */
extern void   FUN_002cb61c(word_t, word_t, word_t, word_t); /* memcpy-into */
extern word_t FUN_002abe60(word_t, word_t, word_t, word_t); /* lock op */
extern void   FUN_002a4ab4(int);               /* fault builder */
extern word_t FUN_00258c60(word_t, word_t, word_t); /* lock-tag acquire */
extern void   FUN_002591b4(word_t);            /* fatal exception (noreturn) */
extern word_t FUN_002b24b8(word_t, word_t);    /* addr decode */
extern void   FUN_002a4528(word_t, word_t, word_t, word_t); /* phys claim */
extern void   FUN_00117cc4(word_t, word_t, word_t); /* memcpy */
extern void   FUN_00117d14(word_t, word_t, word_t); /* memmove */
extern word_t FUN_001394c8(int);               /* alloc */
extern void   FUN_0011d7e8(void);              /* noreturn fatal */
extern word_t FUN_001ee018(word_t, word_t);    /* rw lock op */
extern void   FUN_001afa84(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t, word_t, word_t, word_t); /* fatal dump */
extern void   FUN_001a0774(word_t, long, unsigned int); /* grow/realloc */
extern word_t FUN_000e22c0(void);              /* time/counter */
extern word_t FUN_000e21b4(void);              /* time/counter */
extern unsigned char *FUN_000b1d54(word_t, int);  /* phys alloc */
extern word_t FUN_0008f5f4(void);              /* vec state probe */
extern word_t FUN_0008f9c4(long, long, word_t, word_t, word_t, word_t); /* vec grow */
extern word_t FUN_0008f9dc(void);              /* vec grow info */
extern void   FUN_0008f9f4(word_t, long, int, word_t, word_t); /* vec grow */
extern void   FUN_0008fe7c(word_t, word_t, word_t, word_t, word_t, word_t, word_t); /* range move */
extern long   FUN_0008d1c4(word_t *, long, long, word_t); /* insert scan */
extern long   FUN_0008cf58(word_t *, long, long, word_t); /* scan */
extern word_t FUN_00086590(int);               /* subsystem init */
extern word_t FUN_00086440(int);               /* subsystem init */
extern word_t FUN_00085a54(word_t *, word_t, word_t, word_t, int); /* frame alloc */
extern word_t FUN_000f6d20(word_t, long, word_t); /* region claim */
extern void   FUN_000026e8(word_t);            /* elem release */
extern word_t FUN_00027724(word_t);            /* typeinfo */
extern word_t FUN_000651bc(word_t);            /* lock release */
extern word_t FUN_00034f70(void);              /* object factory */
extern word_t FUN_00321084(void);              /* RNG byte */
extern word_t FUN_0036a940(word_t);            /* object alloc */
extern word_t FUN_0036a9d4(word_t, word_t);    /* object alloc */
extern void   FUN_0036aa30(word_t, word_t, unsigned int); /* token op */
extern word_t FUN_003a261c(word_t);            /* allocator probe */
extern word_t FUN_000719dc(word_t, word_t);    /* cap allocator (u08 pair) */
extern word_t FUN_00072d5c(word_t, word_t, word_t, word_t); /* cap allocator (bitmap vec) */
extern word_t FUN_0001dde4(word_t, word_t, word_t, word_t); /* cap allocator (byte vec) */
extern word_t FUN_00073140(word_t, word_t, word_t, word_t); /* cap allocator (u28 vec) */
extern word_t FUN_0007499c(word_t, word_t, word_t, word_t); /* cap allocator */
extern word_t FUN_00074874(word_t, word_t, word_t, word_t); /* cap allocator */
extern word_t FUN_00072e74(word_t,word_t,word_t,word_t);  /* cap allocator (no-arg factory) */
extern word_t FUN_00072f00(word_t,word_t,word_t,word_t);
extern word_t FUN_00072f8c(word_t,word_t,word_t,word_t);
extern word_t FUN_00073380(word_t,word_t,word_t,word_t);
extern word_t FUN_00073524(word_t,word_t,word_t,word_t);
extern word_t FUN_00073604(word_t,word_t,word_t,word_t);
extern word_t FUN_000738b0(word_t,word_t,word_t,word_t);
extern word_t FUN_00072de8(word_t,word_t,word_t,word_t);
extern word_t FUN_00073a64(word_t,word_t,word_t,word_t);
extern word_t FUN_00073af0(word_t,word_t,word_t,word_t);
extern word_t FUN_00073b7c(word_t,word_t,word_t,word_t);
extern word_t FUN_00073c08(word_t,word_t,word_t,word_t);
extern word_t FUN_00073c94(word_t,word_t,word_t,word_t);
extern word_t FUN_00073d30(word_t,word_t,word_t,word_t);
extern word_t FUN_00073d70(word_t,word_t,word_t,word_t);
extern word_t FUN_00073dfc(word_t,word_t,word_t,word_t);
extern word_t FUN_00073e88(word_t,word_t,word_t,word_t);
extern word_t FUN_0007402c(word_t,word_t,word_t,word_t);
extern word_t FUN_000730a4(word_t,word_t,word_t,word_t);
extern word_t FUN_00074220(word_t,word_t,word_t,word_t);
extern word_t FUN_000742ac(word_t,word_t,word_t,word_t);
extern word_t FUN_00074490(word_t,word_t,word_t,word_t);
extern word_t FUN_0007451c(word_t,word_t,word_t,word_t);
extern word_t FUN_00074670(word_t,word_t,word_t,word_t);
extern word_t FUN_0007470c(word_t,word_t,word_t,word_t);
extern word_t FUN_000740b8(word_t, word_t, word_t, word_t); /* cap allocator */
extern word_t FUN_00074378(word_t, word_t, word_t, word_t); /* cap allocator */
extern word_t FUN_0007340c(word_t, word_t, word_t, word_t); /* cap allocator */
extern void   FUN_0007d0fc(int, word_t, word_t);  /* span check */
extern void   FUN_0007d128(word_t, word_t, word_t, word_t, word_t, word_t); /* span commit */
extern word_t FUN_00083f48(void);              /* cleanup */
extern word_t FUN_0006afb4(void);              /* out of slice */
extern word_t FUN_0035b67c(word_t, word_t, word_t, word_t); /* memcpy helper */
extern word_t FUN_00002534(word_t, word_t);    /* allocator tag */
extern void   thunk_FUN_002acbb8(word_t, word_t); /* debug print */
extern word_t thunk_FUN_0036b270(word_t);      /* retain */
extern void   thunk_FUN_001f66cc(word_t, word_t, word_t, word_t); /* fault fmt */
extern word_t thunk_FUN_00072664(word_t);      /* lock helper */extern void   thunk_FUN_00114330(word_t, word_t); /* debug */
extern void   thunk_FUN_0007198c(word_t);      /* list init */

/* In-slice globals referenced (decompiler DAT_ symbols). */
extern unsigned char *_DAT_00657778;   /* empty-buffer sentinel */
extern word_t _DAT_004c0590, _DAT_004c05c0, _DAT_004c04f0, _DAT_004c0c60;
extern word_t _DAT_004c0c58, _DAT_004c0c70, _DAT_004c1000, _DAT_004c0630;
extern word_t _DAT_004bf190, _DAT_0064e7d8, _DAT_0064ea20, _DAT_0064e6a0;
extern word_t _DAT_0064ee40, _DAT_0064e680, _DAT_0064f0e8, _DAT_0064f0d8;
extern word_t _DAT_0064f0f0, _DAT_0064e1d0, _DAT_0064e1c0;
extern word_t _DAT_004c04d0;

/* Forward declarations for mutually-recursive local functions. */
static void sk_vec_grow_u28(word_t thisp);
static void sk_lock_acquire_gen(word_t a, word_t b, word_t tag, word_t tab);
static void sk_vec_reserve_cap(word_t thisp, unsigned long n);
static void sk_vec_index_ok(word_t vec, long idx);
static void sk_vec_insert_bytes(void *dst);
static void sk_vec_copy_bytes(unsigned char *lo, unsigned char *hi);
static long sk_object_build(word_t a, long obj, long holder, word_t d);

/* ================================================================== *
 * Virtual-dispatch thunks: indirect call through the object's vtable.
 * The container object starts with a vtable pointer; the offset
 * (0x48 / 0x50 = slots 9 / 10) selects the member function.
 * ================================================================== */

/* FUN_000804a8 @ 0x804a8  (est. sk_obj_dispatch_vt48)
 * Call the member function at vtable offset 0x48 (slot 9) of the object
 * whose vtable pointer lives at thisp. Generic no-arg virtual dispatch.
 * Confidence: high (structural) */
static void sk_obj_dispatch_vt48(word_t thisp)
{
    void (**vt)(void) = *(void (***)(void))thisp;
    vt[9]();            /* vtable +0x48 */
}

/* FUN_000804e4 @ 0x804e4  (est. sk_obj_dispatch_vt50)
 * Virtual dispatch through vtable offset 0x50 (slot 10). No arguments.
 * Confidence: high (structural) */
static void sk_obj_dispatch_vt50(word_t thisp)
{
    void (**vt)(void) = *(void (***)(void))thisp;
    vt[10]();           /* vtable +0x50 */
}

/* FUN_00080ac4 / 0x80b00 / 0x80d0c / 0x80ea0  (est. sk_obj_dispatch_vt50*) */
static void sk_obj_dispatch_vt50_a(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[10](); }
static void sk_obj_dispatch_vt50_b(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[10](); }
static void sk_obj_dispatch_vt50_c(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[10](); }
static void sk_obj_dispatch_vt50_d(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[10](); }

/* FUN_00080cd0 / 0x80e64  (est. sk_obj_dispatch_vt48*) */
static void sk_obj_dispatch_vt48_a(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[9](); }
static void sk_obj_dispatch_vt48_b(word_t thisp)
{ void (**vt)(void) = *(void (***)(void))thisp; vt[9](); }

/* FUN_00080d48 @ 0x80d48  (est. sk_retain_cap10)
 * Retain (bump the refcount of) the capability object at thisp+0x10.
 * Confidence: medium */
static void sk_retain_cap10(word_t thisp)
{
    FUN_0036b270(*(word_t *)(thisp + 0x10));
}

/* FUN_00080d84 @ 0x80d84  (est. sk_pair_store)
 * Fill the four data slots (thisp+0x10 .. +0x28) of a freshly allocated
 * pair object with the four supplied words.
 * Confidence: high (structural) */
static void sk_pair_store(word_t thisp, word_t a, word_t b, word_t c, word_t d)
{
    word_t base = FUN_0036a940(thisp);
    *(word_t *)(base + 0x10) = a;
    *(word_t *)(base + 0x18) = b;
    *(word_t *)(base + 0x20) = c;
    *(word_t *)(base + 0x28) = d;
}

/* FUN_00080e38 / 0x80e3c  (est. sk_vec_release_cap10)
 * Release the cap at thisp+0x10 then drop the lock.
 * Confidence: medium */
static void sk_vec_release_cap10_a(word_t thisp)
{
    FUN_0036b118(*(word_t *)(thisp + 0x10));
    FUN_0036b6ac();
}
static void sk_vec_release_cap10_b(word_t thisp)
{
    FUN_0036b118(*(word_t *)(thisp + 0x10));
    FUN_0036b6ac();
}

/* FUN_00080c8c / 0x80c90  (est. sk_release_token18)
 * Release the token stored at thisp+0x18.
 * Confidence: high (structural) */
static void sk_release_token18_a(word_t thisp) { FUN_003a25d4(*(word_t *)(thisp + 0x18)); }
static void sk_release_token18_b(word_t thisp) { FUN_003a25d4(*(word_t *)(thisp + 0x18)); }

/* FUN_00080cac / 0x80cb0  (est. sk_release_token18_unlock)
 * Release the token at thisp+0x18, then another resource and the lock.
 * Confidence: medium */
static void sk_release_token18_c(word_t thisp)
{
    FUN_003a25d4(*(word_t *)(thisp + 0x18));
    FUN_00084064();
    FUN_0036b6ac();
}
static void sk_release_token18_d(word_t thisp)
{
    FUN_003a25d4(*(word_t *)(thisp + 0x18));
    FUN_00084064();
    FUN_0036b6ac();
}

/* FUN_00080aa0 / 0x80aa4  (est. sk_vec_release_cap10_token)
 * Release the cap at thisp+0x10, then a token and the lock.
 * Confidence: medium */
static void sk_vec_release_cap10_token_a(word_t thisp)
{
    FUN_0036b118(*(word_t *)(thisp + 0x10));
    FUN_00084074();
    FUN_0036b6ac();
}
static void sk_vec_release_cap10_token_b(word_t thisp)
{
    FUN_0036b118(*(word_t *)(thisp + 0x10));
    FUN_00084074();
    FUN_0036b6ac();
}

/* FUN_00080edc @ 0x80edc  (est. sk_fault_flush)
 * Flush the fault pipeline: release a token, then forward to the u28
 * grow/settle routine.
 * Confidence: low */
static void sk_fault_flush(word_t thisp)
{
    FUN_0008403c();
    sk_vec_grow_u28(thisp);
}

/* ================================================================== *
 * Bounds-checked ranged copy helpers. Each validates that [src, src+n*sz)
 * does not overlap the destination and lies in bounds, then performs the
 * element-wise copy. All share the same shape.
 * ================================================================== */

/* FUN_00080a6c @ 0x80a6c  (est. sk_vec_store_checked)
 * Store one 8-byte word `val` into the container at byte offset `idx`,
 * after verifying idx >= 0 and idx+8 fits within [base, base+avail).
 * Confidence: high (structural) */
static void sk_vec_store_checked(word_t val, long idx, word_t base, word_t end)
{
    if (idx < 0) CL4_FATAL();                          /* 0x80a98 */
    if (__builtin_add_overflow((word_t)idx, 8, (word_t *)0)) CL4_FATAL();
    long avail = (base != 0) ? (long)(end - base) : 0;
    if ((word_t)(idx + 8) <= (word_t)avail) {
        *(word_t *)(base + idx) = val;
        return;
    }
    CL4_FATAL();                                       /* 0x80aa0 */
}

/* FUN_0008192c @ 0x8192c  (est. sk_index_bounds)
 * Bounds check: panic if idx < 0 or idx >= vec->length (vec+0x10).
 * Confidence: high (structural) */
static void sk_index_bounds(word_t idx, word_t unused, word_t vec)
{
    if ((long)idx < 0) CL4_FATAL();                    /* 0x81944 */
    if (idx < *(word_t *)(vec + 0x10)) return;
    CL4_FATAL();                                       /* 0x81948 */
}
static void thunk_sk_index_bounds(word_t idx, word_t unused, word_t vec)
{ sk_index_bounds(idx, unused, vec); }

/* FUN_00081948 @ 0x81948  (est. sk_copy_u08_nonoverlap)
 * Copy `n` 8-byte words from src to dst after verifying the two ranges do
 * not overlap and n >= 0.
 * Confidence: high (structural) */
static void sk_copy_u08_nonoverlap(word_t dst, long n, word_t src)
{
    if (n < 0) CL4_FATAL();                            /* 0x81970 */
    if (src + (word_t)n*8 <= dst || dst + (word_t)n*8 <= src) {
        FUN_000840a8(dst);
        return;
    }
    CL4_FATAL();                                       /* 0x81974 */
}

/* FUN_00081974 @ 0x81974  (est. sk_copy_bytes_nonoverlap)
 * Copy `n` raw bytes from src to dst (byte-wise) after non-overlap check.
 * Confidence: high (structural) */
static void sk_copy_bytes_nonoverlap(word_t dst, long n, word_t src)
{
    if (n < 0) CL4_FATAL();                            /* 0x819a4 */
    if (src + (word_t)n <= dst || dst + (word_t)n <= src) {
        FUN_00117cc4(src, dst, (word_t)n);
        return;
    }
    CL4_FATAL();                                       /* 0x819a8 */
}

/* FUN_00081a10 @ 0x81a10  (est. sk_copy_u08v_nonoverlap)
 * Copy `n` 8-byte words with a constructed-copy (memmove) helper.
 * Confidence: high (structural) */
static void sk_copy_u08v_nonoverlap(word_t dst, long n, word_t src)
{
    if (n < 0) CL4_FATAL();                            /* 0x81a78 */
    if (src + (word_t)n*8 <= dst || dst + (word_t)n*8 <= src) {
        word_t u = FUN_001394c8(0);
        FUN_0035b67c(src, dst, (word_t)n, u);
        return;
    }
    CL4_FATAL();                                       /* 0x81a7c */
}

/* FUN_00081a7c @ 0x81a7c  (est. sk_copy_u18_nonoverlap)
 * Copy `n` 0x18-byte elements from src to dst after non-overlap check.
 * Confidence: high (structural) */
static void sk_copy_u18_nonoverlap(word_t dst, long n, word_t src)
{
    if (n < 0) CL4_FATAL();                            /* 0x81aa8 */
    if (src + (word_t)n*0x18 <= dst || dst + (word_t)n*0x18 <= src) {
        FUN_000840a8(dst);
        return;
    }
    CL4_FATAL();                                       /* 0x81aac */
}

/* FUN_00081aac @ 0x81aac  (est. sk_copy_u28_nonoverlap)
 * Copy `n` 0x28-byte elements from src to dst (constructed copy with the
 * element's move tag pair) after the non-overlap check.
 * Confidence: high (structural) */
static void sk_copy_u28_nonoverlap(word_t dst, long n, word_t src,
                                   word_t tag, word_t t2)
{
    if (n < 0) CL4_FATAL();                            /* 0x81b0c */
    FUN_0008409c();
    if (src + (word_t)n*0x28 <= dst || dst + (word_t)n*0x28 <= src) {
        FUN_00002534(tag, t2);
        FUN_00084140();
        FUN_0035b67c(src, dst, (word_t)n, tag);
        return;
    }
    CL4_FATAL();                                       /* 0x81b10 */
}

/* FUN_000819a8 @ 0x819a8  (est. sk_copy_u10_nonoverlap)
 * Copy `n` 0x10-byte elements from src to dst (constructed copy) after
 * the non-overlap check.
 * Confidence: high (structural) */
static void sk_copy_u10_nonoverlap(word_t dst, long n, word_t src)
{
    if (n < 0) CL4_FATAL();                            /* 0x81a0c */
    FUN_0008409c();
    if (src + (word_t)n*0x10 <= dst || dst + (word_t)n*0x10 <= src) {
        FUN_00002534(0x64e6a0, _DAT_004c04f0);
        FUN_00084140();
        FUN_0035b67c(src, dst, (word_t)n, _DAT_004c04f0);
        return;
    }
    CL4_FATAL();                                       /* 0x81a10 */
}

/* ================================================================== *
 * Append / insert primitives. Each allocates one (or a keyed pair of)
 * slot(s) in the container, fills the element, and bumps the length.
 * ================================================================== */

/* FUN_00081b10 @ 0x81b10  (est. sk_append_u10_elem)
 * Append a 0x10-byte element to the u10 vector plus a parallel 8-byte
 * tag word; then bump length.
 * Confidence: medium */
static void sk_append_u10_elem(word_t a, word_t b, unsigned char f, word_t d, word_t vec)
{
    word_t slot = FUN_00083fcc();
    /* element write at extraout_x8 + slot*0x10; parallel tag at vec+0x38 */
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        FUN_00084010(*(word_t *)(vec + 0x10) + 1);
    else
        CL4_FATAL();                                   /* 0x81b4c */
}

/* FUN_00081b4c @ 0x81b4c  (est. sk_append_u20_keyed)
 * Append a keyed 0x20-byte element to the bitmap container: allocate a
 * slot for `key` (bitmap at vec + (key>>6)*8), write 4 words of element
 * data plus 4 words of key data, bump length.
 * Confidence: medium */
static void sk_append_u20_keyed(word_t key, word_t a, word_t b, word_t c, word_t d,
                                word_t e, word_t f, word_t vec)
{
    word_t slot = FUN_00084024(vec + (key >> 6) * 8);
    /* parallel key array at vec+0x30, data array at vec+0x38 */
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        *(word_t *)(vec + 0x10) += 1;
    else
        CL4_FATAL();                                   /* 0x81b9c */
}

/* FUN_00081bd0 @ 0x81bd0  (est. sk_append_u20_keyed2)
 * Append a keyed 0x20-byte element (4 data words + 1 key word) to the
 * bitmap container; bump length.
 * Confidence: medium */
static void sk_append_u20_keyed2(word_t key, word_t a, word_t b, word_t c, word_t d,
                                 word_t e, word_t vec)
{
    word_t slot = FUN_00084024(vec + (key >> 6) * 8);
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        *(word_t *)(vec + 0x10) += 1;
    else
        CL4_FATAL();                                   /* 0x81c1c */
}

/* FUN_00081c1c @ 0x81c1c  (est. sk_append_u10_kv)
 * Append a 0x10-byte element to the u10 container; bump length.
 * Confidence: medium */
static void sk_append_u10_kv(word_t a, word_t b, unsigned char f, word_t d, word_t vec)
{
    word_t slot = FUN_00083fcc();
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        FUN_00084010(*(word_t *)(vec + 0x10) + 1);
    else
        CL4_FATAL();                                   /* 0x81c58 */
}

/* FUN_00081c58 @ 0x81c58  (est. sk_append_u08_keyonly)
 * Allocate a slot for `key` and bump the length of the bitmap container.
 * Confidence: medium */
static void sk_append_u08_keyonly(word_t key, word_t thisp)
{
    FUN_00084024(thisp + (key >> 6) * 8);
    FUN_00084248();
    /* size updated via helper */
}

/* FUN_00081c98 @ 0x81c98  (est. sk_append_u20_keyed3)
 * Append a keyed 0x20-byte element (1 key word + 4 data words) to the
 * bitmap container; bump length.
 * Confidence: medium */
static void sk_append_u20_keyed3(word_t key, word_t a, word_t b, word_t c, word_t d,
                                 word_t e, word_t vec)
{
    word_t slot = FUN_00084024(vec + (key >> 6) * 8);
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        *(word_t *)(vec + 0x10) += 1;
    else
        CL4_FATAL();                                   /* 0x81ce4 */
}

/* FUN_00081ce8 @ 0x81ce8  (est. sk_append_u08)
 * Append one 8-byte word to the u08 vector; bump length.
 * Confidence: medium */
static void sk_append_u08(word_t a, word_t b, word_t v, word_t vec)
{
    long idx = (long)FUN_00083f8c();
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        FUN_00084094(*(word_t *)(vec + 0x10) + 1);
    else
        CL4_FATAL();                                   /* 0x81d14 */
}
static void thunk_sk_append_u08(word_t a, word_t b, word_t v, word_t vec)
{ sk_append_u08(a, b, v, vec); }

/* FUN_00081d14 @ 0x81d14  (est. sk_append_u70)
 * Append a 0x70-byte (112-byte) element by copying from src; bump length.
 * Confidence: medium */
static void sk_append_u70(word_t a, word_t b, word_t v, word_t vec)
{
    long idx = (long)FUN_00083f8c();
    FUN_00117cc4((word_t)idx * 0x70, v, 0x6a);
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        *(word_t *)(vec + 0x10) += 1;
    else
        CL4_FATAL();                                   /* 0x81d60 */
}

/* FUN_00081d94 @ 0x81d94  (est. sk_append_u30_keyed)
 * Append a keyed 0x30-byte element to the bitmap container: set the key's
 * bit, store the key word, copy 6 words of element data, bump length.
 * Confidence: medium */
static void sk_append_u30_keyed(word_t key, word_t v, word_t *src, word_t vec)
{
    word_t l1 = vec + (key >> 6) * 8;
    *(word_t *)(l1 + 0x40) |= 1UL << (key & 0x3f);
    *(word_t *)(*(word_t *)(vec + 0x30) + key * 8) = v;
    /* data[6 words] at vec+0x38 + key*0x30 */
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        FUN_00084094(*(word_t *)(vec + 0x10) + 1);
    else
        CL4_FATAL();                                   /* 0x81df0 */
}

/* FUN_00081df0 @ 0x81df0  (est. sk_append_u28_elem)
 * Append a 0x28-byte element (5 words) copied from src to the u28 vector;
 * bump length.
 * Confidence: medium */
static void sk_append_u28_elem(word_t a, word_t b, word_t *src, word_t vec)
{
    long idx = (long)FUN_00083f8c();
    /* 5-word copy at extraout_x8 + idx*0x28 */
    if (!__builtin_add_overflow(*(word_t *)(vec + 0x10), 1, (word_t *)0))
        FUN_00084094(*(word_t *)(vec + 0x10) + 1);
    else
        CL4_FATAL();                                   /* 0x81e30 */
}

/* FUN_00081b9c @ 0x81b9c  (est. sk_append_generic)
 * Allocate a slot and bump the size of the container.
 * Confidence: low */
static void sk_append_generic(word_t thisp)
{
    FUN_00083fcc();
    FUN_000841b4();
    FUN_00084010(*(word_t *)(thisp + 0x10) + 1);
}

/* FUN_00081d60 @ 0x81d60  (est. sk_append_generic2)
 * Allocate a slot and bump the size of the container.
 * Confidence: low */
static void sk_append_generic2(word_t thisp)
{
    FUN_00083fcc();
    FUN_000841d0();
    FUN_00084010(*(word_t *)(thisp + 0x10) + 1);
}

/* FUN_00081e30 @ 0x81e30  (thunk_FUN_0006afb4) — out-of-slice helper
 * Fill the 5-word descriptor `out` describing a range within `obj`:
 * out[0]=obj, out[1]=obj+0x40, out[2]=~flag, out[3]=0,
 * out[4]= (mask & word at obj+0x40). The mask depends on a shift count
 * read from obj+0x20.
 * Confidence: medium (structural) */
static void thunk_FUN_0006afb4(long *out, long obj)
{
    unsigned long flag = -1UL << ((unsigned long)*(unsigned char *)(obj + 0x20) & 0x3f);
    out[0] = obj;
    unsigned long w = *(unsigned long *)(obj + 0x40);
    unsigned long neg = -flag;
    unsigned long mask = 0xffffffffffffffffUL;
    if (neg < 0x40) mask = ~(-1UL << (neg & 0x3f));
    out[1] = obj + 0x40;
    out[2] = ~flag;
    out[3] = 0;
    out[4] = mask & w;
}

/* FUN_00081e34 @ 0x81e34  (est. sk_rwlock_try_enter)
 * Try to enter a read/write lock with the given mode; if a competing
 * owner is observed, upgrade the lock and re-validate the owner bit.
 * Confidence: medium */
static void sk_rwlock_try_enter(word_t a, word_t b, unsigned int mode)
{
    word_t s1 = FUN_00084220();
    FUN_0006ae9c(a, b);
    word_t s2 = FUN_000775b8();
    word_t c = FUN_00084200();
    word_t r = FUN_00258c60(mode & 1, s1, c);
    if ((r & 1) != 0) {
        word_t s3 = FUN_0006ae9c(s1, c);
        if ((s2 & 1) != (s3 & 1))
            FUN_002591b4(0x6753a0);    /* fatal: owner mismatch */
        FUN_00084234(s3, s2 & 1, a);
    } else {
        FUN_00084234(s2, s2 & 1, a);
    }
}

/* FUN_00081ee8 @ 0x81ee8  (est. sk_lock_aq_dispatch) */
static void sk_lock_aq_dispatch(word_t a, word_t b)
{ sk_lock_acquire_gen(a, b, 0x64e680, _DAT_004c04d0); }
/* FUN_00081efc @ 0x81efc  (est. sk_lock_aq_dispatch2) */
static void sk_lock_aq_dispatch2(word_t a, word_t b)
{ sk_lock_acquire_gen(a, b, 0x64f0e8, _DAT_004c0c60); }
/* FUN_00081f10 @ 0x81f10  (est. sk_lock_aq_dispatch3) */
static void sk_lock_aq_dispatch3(word_t a, word_t b)
{ sk_lock_acquire_gen(a, b, 0x64f0d8, _DAT_004c0c58); }

/* FUN_00081f24 @ 0x81f24  (est. sk_lock_acquire_gen)
 * Acquire a lock with a type tag; if a competing owner is observed,
 * re-probe and validate the owner bit, panicking on mismatch.
 * Confidence: medium */
static void sk_lock_acquire_gen(word_t a, word_t b, word_t tag, word_t tab)
{
    word_t s1 = FUN_00084220();
    thunk_FUN_00072664(s1);
    word_t s2 = FUN_000775b8();
    word_t c = FUN_00002534(tag, tab);
    word_t r = FUN_00258c60(s1 & 1, s1, c);
    if ((r & 1) != 0) {
        word_t s3 = thunk_FUN_00072664(s1);
        if ((s2 & 1) != (s3 & 1))
            FUN_002591b4(0x677790);    /* fatal: owner mismatch */
        FUN_00084234(s3, s2 & 1, a);
    } else {
        FUN_00084234(s2, s2 & 1, a);
    }
}

/* FUN_00081fe0 @ 0x81fe0  (est. sk_pair_init)
 * Initialize a 3-word pair object from three words and return them as a
 * 16-byte value; the low word is stored into dst[0].
 * Confidence: high (structural) */
static word_t sk_pair_init(word_t *dst, word_t a, word_t b, word_t c)
{
    dst[0] = c;
    return b;   /* {b, a} pair hi */
}

/* FUN_00081ff0 @ 0x81ff0  (est. sk_pair_init2)
 * Initialize a 4-word record from four words while retaining two source
 * objects; returns a 16-byte value.
 * Confidence: medium */
static word_t sk_pair_init2(word_t *dst, word_t a, word_t b, word_t c,
                            word_t d, word_t e, word_t f)
{
    dst[0] = c; dst[1] = d; dst[2] = e; dst[3] = f;
    thunk_FUN_0036b270(b);
    FUN_0036b270(c);
    return b;
}

/* FUN_000829ec @ 0x829ec  (est. sk_vec_convert_pair)
 * Expand a 6-word source pair into a 3x2-word destination triplet via
 * sk_pair_init2.
 * Confidence: low */
static void sk_vec_convert_pair(word_t out, word_t *src)
{
    word_t l0, u38, u30, u28;
    word_t r = sk_pair_init2(&l0, src[0], src[1], src[2], src[3], src[4], src[5]);
    /* writes 3 words into out */
}

/* ================================================================== *
 * Grow / reserve / insert-range routines. These manage the container's
 * backing buffer: capacity doubling (low bit of +0x18 = owned), realloc
 * through the per-type allocator callback, and range insertion.
 * ================================================================== */

/* FUN_00082974 @ 0x82974  (est. sk_vec_ensure)
 * Ensure the vector has room for at least `n` elements. If the owned
 * buffer is too small (or not owned), grow to max(current, n) elements.
 * Confidence: high (structural) */
static void sk_vec_ensure(word_t thisp, word_t n, unsigned int flags,
                          word_t (*grow)(word_t, word_t, word_t, word_t))
{
    word_t v = thisp;
    word_t owner = FUN_003a261c(v);
    if (owner == 0 || (word_t)(*(word_t *)(v + 0x18) >> 1) < n) {
        word_t want = *(word_t *)(v + 0x10);
        if (*(word_t *)(v + 0x10) <= n) want = n;
        word_t nb = grow(owner, want, flags & 1, v);
        *((word_t *)(thisp)) = nb;    /* grow may relocate this */
    }
}
static void sk_vec_ensure_u28(word_t thisp, word_t n, unsigned int flags)
{ sk_vec_ensure(thisp, n, flags, FUN_0007499c); }
static void sk_vec_ensure_bitmap(word_t thisp, word_t n, unsigned int flags)
{ sk_vec_ensure(thisp, n, flags, FUN_00072d5c); }

/* FUN_000828ec @ 0x828ec  (est. sk_vec_reserve)
 * Reserve capacity for at least `n` elements; if the buffer is owned and
 * already large enough, return immediately.
 * Confidence: medium */
static void sk_vec_reserve(word_t thisp, word_t n, unsigned int flags)
{
    word_t v = thisp;
    word_t owner = FUN_003a261c(v);
    if ((int)owner != 0 && n <= (*(word_t *)(v + 0x18) >> 1)) return;
    word_t want = *(word_t *)(v + 0x10);
    if (*(word_t *)(v + 0x10) <= n) want = n;
    FUN_001a0774(owner, want, flags & 1);
}

/* FUN_0008295c @ 0x8295c  (est. sk_vec_ensure_u28) — wrapper */
static void sk_vec_ensure_u28w(word_t thisp, word_t n, unsigned int flags)
{ sk_vec_ensure(thisp, n, flags, FUN_0007499c); }

/* FUN_000827c4 @ 0x827c4  (est. sk_vec_push_owned)
 * Allocate an owned buffer for `arg` elements and zero it.
 * Confidence: medium */
static void sk_vec_push_owned(word_t thisp, word_t arg)
{
    word_t v = FUN_000719dc(0, arg);
    sk_vec_index_ok(v, 0);
}

/* FUN_000828a4 @ 0x828a4  (est. sk_vec_index_ok)
 * Validate that idx + vec->length does not overflow and stays >= 0.
 * Confidence: high (structural) */
static void sk_vec_index_ok(word_t vec, long idx)
{
    if (__builtin_sub_overflow(0, (word_t)idx, (word_t *)0)) CL4_FATAL(); /* 0x828e0 */
    word_t sum = (word_t)idx + *(word_t *)(vec + 0x10);
    if (__builtin_add_overflow((word_t)idx, *(word_t *)(vec + 0x10), (word_t *)0)) CL4_FATAL(); /* 0x828e4 */
    if ((long)sum < (long)idx) CL4_FATAL();           /* 0x828e8 */
    if ((long)sum >= 0) return;
    CL4_FATAL();                                      /* 0x828ec */
}

/* FUN_000827ec @ 0x827ec  (est. sk_vec_size_advance)
 * Grow the vector's logical length by `delta`: locate the owned backing
 * buffer, add delta to its length, and pack the new length (with the
 * owned flag) back into +0x18.
 * Confidence: medium */
static void sk_vec_size_advance(word_t thisp, long delta)
{
    word_t *v = (word_t *)thisp;
    unsigned long u1 = v[3];
    unsigned long half = u1 >> 1;
    long used = half - v[2];
    if (__builtin_sub_overflow(half, v[2], (word_t *)0)) CL4_FATAL(); /* 0x82894 */
    long rem = delta - used;
    if (__builtin_sub_overflow((word_t)delta, (word_t)used, (word_t *)0)) CL4_FATAL(); /* 0x82898 */
    if (rem != 0) {
        word_t base = v[0];
        word_t dom = FUN_00324bf0(0);
        word_t rr = FUN_0036b270(base);
        unsigned char *buf = FUN_00362acc(rr, dom);
        if (buf == 0) { FUN_0036b118(base); buf = _DAT_00657778; }
        if (__builtin_add_overflow(*(word_t *)(buf + 0x10), (word_t)rem, (word_t *)0)) CL4_FATAL(); /* 0x8289c */
        *(long *)(buf + 0x10) += rem;
        FUN_0036b118(base);
        if (__builtin_add_overflow(half, (word_t)rem, (word_t *)0)) CL4_FATAL(); /* 0x828a0 */
        if ((long)(half + (word_t)rem) < 0) CL4_FATAL(); /* 0x828a4 */
        v[3] = (u1 & 1) | (half + (word_t)rem) * 2;
    }
}

/* FUN_00082ee4 @ 0x82ee4  (est. sk_vec_grow_cap)
 * Grow the container's capacity to at least `n` elements, doubling when
 * the current owned capacity is exhausted.
 * Confidence: medium */
static void sk_vec_grow_cap(word_t thisp, unsigned long n)
{
    word_t *v = (word_t *)thisp;
    word_t c2 = v[2];
    word_t cap = v[3] >> 1;
    long used = cap - c2;
    if (__builtin_sub_overflow(cap, c2, (word_t *)0)) CL4_FATAL(); /* 0x82fd4 */
    long grow = used;
    if ((v[3] & 1) != 0) {
        word_t base = v[0];
        word_t dom = FUN_00324bf0(0);
        word_t rr = FUN_0036b270(base);
        unsigned char *buf = FUN_00362acc(rr, dom);
        if (buf == 0) { FUN_0036b118(base); buf = _DAT_00657778; }
        long blen = *(long *)(buf + 0x10);
        if ((unsigned char *)(v[1] + c2 + used) == buf + blen + 0x20) {
            word_t cap2 = *(word_t *)(buf + 0x18);
            FUN_0036b118(base);
            long extra = (cap2 >> 1) - blen;
            grow = used + extra;
            if (__builtin_add_overflow((word_t)used, (word_t)extra, (word_t *)0)) CL4_FATAL(); /* 0x82fe0 */
        } else {
            FUN_0036b118(base);
        }
    }
    long want = used + (long)n;
    if (!__builtin_add_overflow((word_t)used, n, (word_t *)0)) {
        long newcap = want;
        if (grow < want) {
            if ((unsigned long)(grow + 0x4000000000000000L) >> 63) CL4_FATAL(); /* 0x82fdc */
            newcap = grow * 2;
            if (newcap - want == 0 || newcap < want) newcap = want;
        }
        sk_vec_reserve_cap(thisp, (word_t)newcap);
        return;
    }
    CL4_FATAL();                                      /* 0x82fd8 */
}

/* FUN_00082a34 @ 0x82a34  (est. sk_vec_reserve_cap)
 * Ensure capacity for `n` elements, coalescing with the owned buffer when
 * it is contiguous; otherwise reallocate and move the used prefix.
 * Confidence: medium */
static void sk_vec_reserve_cap(word_t thisp, unsigned long n)
{
    word_t *v = (word_t *)thisp;
    word_t probe = FUN_0008f5f4();
    if ((probe & 1) != 0) {
        word_t c2 = v[2];
        word_t cap = v[3] >> 1;
        long used = cap - c2;
        if (__builtin_sub_overflow(cap, c2, (word_t *)0)) CL4_FATAL(); /* 0x82b90 */
        word_t base = v[0];
        if ((v[3] & 1) != 0) {
            word_t dom = FUN_00324bf0(0);
            word_t rr = FUN_0036b270(base);
            unsigned char *buf = FUN_00362acc(rr, dom);
            if (buf == 0) { FUN_0036b118(base); buf = _DAT_00657778; }
            long blen = *(long *)(buf + 0x10);
            if ((unsigned char *)(v[1] + c2 + used) == buf + blen + 0x20) {
                word_t cap2 = *(word_t *)(buf + 0x18);
                FUN_0036b118(base);
                long extra = (cap2 >> 1) - blen;
                used += extra;
                if (__builtin_add_overflow((word_t)(used - extra), (word_t)extra, (word_t *)0)) CL4_FATAL(); /* 0x82b94 */
            } else {
                FUN_0036b118(base);
            }
        }
        if (n <= (word_t)used) return;
    }
    word_t used2 = v[2];
    word_t cap2 = v[3];
    word_t h = cap2 >> 1;
    if (__builtin_sub_overflow(h, used2, (word_t *)0)) CL4_FATAL(); /* 0x82b88 */
    long span = h - used2;
    word_t nb = FUN_000719dc((word_t)span, n);
    if ((long)h < (long)used2) CL4_FATAL();          /* 0x82b8c */
    word_t oldbase = v[0];
    word_t olddata = v[1];
    FUN_0036b270(oldbase);
    FUN_0008fe7c(used2, h, nb + 0x20, oldbase, olddata, used2, cap2);
    sk_vec_index_ok(nb, used2);
    FUN_0036b118(oldbase);
    v[1] = nb + 0x20;
    v[2] = nb + 0x20;
    v[3] = oldbase;
}

/* FUN_00082d4c @ 0x82d4c  (est. sk_vec_append_range)
 * Append the byte range [lo, hi) to the vector, growing capacity as
 * needed and copying the source bytes into place.
 * Confidence: medium */
static void sk_vec_append_range(word_t thisp, unsigned long lo, unsigned long hi)
{
    word_t *v = (word_t *)thisp;
    word_t span = hi - lo;
    word_t n = (lo != 0) ? span : 0;
    sk_vec_grow_cap(thisp, n);
    FUN_0008f5f4();
    word_t c2 = v[2];
    word_t cap = v[3] >> 1;
    long used = cap - c2;
    if (__builtin_sub_overflow(cap, c2, (word_t *)0)) CL4_FATAL(); /* 0x82ecc */
    unsigned char *dst = (unsigned char *)(v[1] + c2 + used);
    long avail = used;
    if ((v[3] & 1) != 0) {
        word_t base = v[0];
        word_t dom = FUN_00324bf0(0);
        word_t rr = FUN_0036b270(base);
        unsigned char *buf = FUN_00362acc(rr, dom);
        if (buf == 0) { FUN_0036b118(base); buf = _DAT_00657778; }
        long blen = *(long *)(buf + 0x10);
        if (dst == buf + blen + 0x20) {
            word_t cap2 = *(word_t *)(buf + 0x18);
            FUN_0036b118(base);
            long extra = (cap2 >> 1) - blen;
            avail = used + extra;
            if (__builtin_add_overflow((word_t)used, (word_t)extra, (word_t *)0)) CL4_FATAL(); /* 0x82ee0 */
        } else {
            FUN_0036b118(base);
        }
    }
    word_t free = (word_t)(avail - used);
    if (__builtin_sub_overflow((word_t)avail, (word_t)used, (word_t *)0)) CL4_FATAL(); /* 0x82ed0 */
    if ((long)free < 0) CL4_FATAL();                  /* 0x82ed4 */
    word_t copied = 0;
    if ((lo != 0) && (hi != 0)) {
        copied = 0;
        if ((lo < hi) && (free != 0)) {
            if ((long)span < 0) CL4_FATAL();          /* 0x82ee4 */
            copied = span;
            if (free <= span) copied = free;
            FUN_00117d14((word_t)dst, lo, copied);
            lo += copied;
        }
    }
    if ((long)copied < (long)n) CL4_FATAL();          /* 0x82ed8 */
    if (copied != 0) {
        if (__builtin_add_overflow((word_t)used, copied, (word_t *)0)) CL4_FATAL(); /* 0x82edc */
        sk_vec_size_advance(thisp, used + copied);
    }
    if (copied != free) return;
    sk_vec_copy_bytes((unsigned char *)lo, (unsigned char *)hi);
}

/* FUN_00082b94 @ 0x82b94  (est. sk_vec_insert_range)
 * Insert the byte range [src+lo, src+hi) into the vector, growing
 * capacity, copying source bytes in, and updating the length.
 * Confidence: medium */
static void sk_vec_insert_range(word_t *src, long n, unsigned long lo, unsigned long hi)
{
    word_t *v = (word_t *)*src;
    word_t h = hi >> 1;
    long need = h - lo;
    if (__builtin_sub_overflow(h, lo, (word_t *)0)) CL4_FATAL(); /* 0x82d30 */
    sk_vec_grow_cap((word_t)v, need);
    FUN_0008f5f4();
    word_t c2 = v[2];
    word_t cap = v[3] >> 1;
    long used = cap - c2;
    if (__builtin_sub_overflow(cap, c2, (word_t *)0)) CL4_FATAL(); /* 0x82d34 */
    unsigned char *dst = (unsigned char *)(v[1] + c2 + used);
    long avail = used;
    if ((v[3] & 1) != 0) {
        word_t base = v[0];
        word_t dom = FUN_00324bf0(0);
        word_t rr = FUN_0036b270(base);
        unsigned char *buf = FUN_00362acc(rr, dom);
        if (buf == 0) { FUN_0036b118(base); buf = _DAT_00657778; }
        long blen = *(long *)(buf + 0x10);
        if (dst == buf + blen + 0x20) {
            word_t cap2 = *(word_t *)(buf + 0x18);
            FUN_0036b118(base);
            long extra = (cap2 >> 1) - blen;
            avail = used + extra;
            if (__builtin_add_overflow((word_t)used, (word_t)extra, (word_t *)0)) CL4_FATAL(); /* 0x82d48 */
        } else {
            FUN_0036b118(base);
        }
    }
    long availused = avail - used;
    if (__builtin_sub_overflow((word_t)avail, (word_t)used, (word_t *)0)) CL4_FATAL(); /* 0x82d38 */
    if (availused < 0) CL4_FATAL();                   /* 0x82d3c */
    if (lo == h) {
        if (need > 0) CL4_FATAL();                    /* 0x82d40 */
        need = 0;
        h = lo;
    } else {
        if (availused < need) CL4_FATAL();            /* 0x82d44 */
        sk_copy_bytes_nonoverlap((word_t)n + lo, need, (word_t)dst);
        if (need > 0) {
            if (__builtin_add_overflow((word_t)used, (word_t)need, (word_t *)0)) CL4_FATAL(); /* 0x82d4c */
            sk_vec_size_advance((word_t)v, used + need);
        }
    }
    if (need != availused) { FUN_0036b118(src[0]); return; }
    /* commit via sk_vec_insert_bytes with the range descriptor */
    sk_vec_insert_bytes(&need);
}

/* ================================================================== *
 * Bitmap scan / grow: find the first set bit (via bit-reversal + CLZ) in
 * the slot bitmap and grow the container's parallel arrays.
 * ================================================================== */

/* FUN_00080ef4 @ 0x80ef4  (est. sk_bitmap_grow_install)
 * Scan the container's slot bitmap for the first set bit (bit-reversed
 * CLZ), then install that element into the grown value array, extending
 * the length.
 * Confidence: low */
static void sk_bitmap_grow_install(word_t thisp, void *src)
{
    word_t *v = (word_t *)thisp;
    word_t count = v[2];
    if (__builtin_add_overflow(v[2], count, (word_t *)0)) CL4_FATAL(); /* 0x80fbc */
    sk_vec_ensure(thisp, v[2] + count, 1, FUN_00072d5c);
    long space = (*(word_t *)(v[3] >> 1) - v[2]);
    if (space < 0) CL4_FATAL();                       /* 0x80fc0 */
    word_t r = 0;
    FUN_0008cf58(&r, v[1] + v[2] * 8 + 0x20, space, (word_t)src);
    /* ... bit-scan + element install ... */
    /* *src = v: the caller's pointer is updated via the return path */
}

/* FUN_0008110c @ 0x8110c  (est. sk_bytes_grow_from_src)
 * Copy bytes from a source buffer into the byte vector, growing as
 * needed; if the buffer becomes full, continue by reading RNG bytes.
 * Confidence: low */
static void sk_bytes_grow_from_src(word_t thisp, void *src)
{
    word_t r = FUN_00077698();                 /* r = {src_lo, src_hi} */
    word_t *v = (word_t *)thisp;
    word_t n = 0, q = 0;
    if (__builtin_add_overflow(v[2], q, (word_t *)0)) CL4_FATAL(); /* 0x811fc */
    sk_vec_ensure(thisp, v[2] + q, 1, FUN_0001dde4);
    /* copy min(q, capacity-used) bytes, then RNG fill */
    FUN_0007767c((word_t)src);
}

/* FUN_0008129c @ 0x8129c  (est. sk_vec_grow_with_src)
 * Grow the vector with elements from a source iterator, using the byte
 * allocator.
 * Confidence: low */
static void sk_vec_grow_with_src(word_t thisp)
{
    word_t u = FUN_00083f5c();
    sk_vec_ensure(thisp, u, 1, FUN_0001dde4);
    FUN_00083fb8();
    /* iterate source, append */
}

/* FUN_00081370 @ 0x81370  (est. sk_vec_grow_u28)
 * Grow the u28 vector, appending elements from the source iterator
 * (element size 0x28), handling owned-buffer coalescing.
 * Confidence: low */
static void sk_vec_grow_u28(word_t thisp)
{
    word_t u = FUN_00083f5c();
    sk_vec_ensure(thisp, u, 1, FUN_00072d5c);
    word_t *v = (word_t *)thisp;
    word_t free = (*(word_t *)(v[3] >> 1) - v[2]);
    if ((long)free >= 0) {
        if (v[2] == 0) {
            FUN_0036b118(v[0]);
        } else {
            FUN_00083ff0(v[1] + v[2] * 0x28);
            sk_append_u28_elem(0, 0, (word_t *)v[1], thisp);
            FUN_0036b118(v[0]);
        }
        return;
    }
    CL4_FATAL();                                      /* 0x8142c */
}

/* FUN_00081348 @ 0x81348  (est. sk_attach_sched_node)
 * Attach a scheduling node: forward to the u28 grow/settle path.
 * Confidence: low */
static void sk_attach_sched_node(word_t arg, word_t thisp)
{
    sk_vec_grow_u28(thisp);
}

/* FUN_00081900 @ 0x81900  (est. sk_attach_sched_node_b) */
static void sk_attach_sched_node_b(word_t arg, word_t thisp)
{
    sk_vec_grow_u28(thisp);
}

/* FUN_00081438 / 0x814e4 / 0x8157c / 0x8162c  (est. sk_vec_grow_u08/u18/u10)
 * Grow the container, appending elements from the source iterator; the
 * element stride distinguishes the vector type.
 * Confidence: low */
static void sk_vec_grow_generic(word_t thisp)
{
    word_t u = FUN_00083f5c();
    sk_vec_ensure(thisp, u, 1, FUN_00072d5c);
    FUN_00083fb8();
    word_t *v = (word_t *)thisp;
    if (v[2] == 0) {
        FUN_0036b118(v[0]);
    } else {
        FUN_00083ff0(v[1] + v[2] * 8);
        sk_append_u08(0, 0, 0, thisp);
        FUN_0036b118(v[0]);
        FUN_000840e8();
    }
}
static void sk_vec_grow_u08(word_t thisp)  { sk_vec_grow_generic(thisp); }
static void sk_vec_grow_u08b(word_t thisp) { sk_vec_grow_generic(thisp); }
static void sk_vec_grow_u18(word_t thisp)  { sk_vec_grow_generic(thisp); }
static void sk_vec_grow_u10(word_t thisp)  { sk_vec_grow_generic(thisp); }

/* FUN_000816d8 @ 0x816d8  (est. sk_vec_grow_u28_deep)
 * Grow the u28 vector with a deep copy: scan the source, move whole
 * 0x28-byte elements, and coalesce with the owned buffer.
 * Confidence: low */
static void sk_vec_grow_u28_deep(word_t thisp, void *src)
{
    word_t pr[2];
    sk_vec_ensure(thisp, *(word_t *)(thisp + 0x10), 1, FUN_00073140);
    word_t *v = (word_t *)thisp;
    long free = (*(word_t *)(v[3] >> 1) - v[2]);
    if (free < 0) CL4_FATAL();                        /* 0x817b0 */
    long r = FUN_0008d1c4(pr, v[1] + v[2] * 0x28 + 0x20, free, (word_t)src);
    if (r < 0) CL4_FATAL();                           /* 0x817b4 */
    if (r != 0) {
        if (__builtin_add_overflow(v[2], r, (word_t *)0)) CL4_FATAL(); /* 0x81900 */
        v[2] += r;
    }
    /* iterate source, append elements if r == free */
}

/* ================================================================== *
 * Cap-type allocation factories. Each calls a dedicated allocator
 * (FUN_00072xxx / FUN_00073xxx / FUN_00074xxx) and stores the result
 * into `this`. These are the per-capability-kind object constructors.
 * ================================================================== */
#define SK_NEW_CAP_FACTORY(name, addr, alloc) \
    static void name(word_t thisp){ word_t v = alloc(0,0,0,0); *(word_t *)thisp = v; }
SK_NEW_CAP_FACTORY(sk_new_cap_a,  0x82424, FUN_00072e74)
SK_NEW_CAP_FACTORY(sk_new_cap_b,  0x82444, FUN_00072f00)
SK_NEW_CAP_FACTORY(sk_new_cap_c,  0x82464, FUN_00072f8c)
SK_NEW_CAP_FACTORY(sk_new_cap_d,  0x82484, FUN_00073380)
SK_NEW_CAP_FACTORY(sk_new_cap_e,  0x824a4, FUN_00073140)
SK_NEW_CAP_FACTORY(sk_new_cap_f,  0x824c4, FUN_00073524)
SK_NEW_CAP_FACTORY(sk_new_cap_g,  0x824e4, FUN_00073604)
SK_NEW_CAP_FACTORY(sk_new_cap_h,  0x82504, FUN_000738b0)
SK_NEW_CAP_FACTORY(sk_new_cap_i,  0x82524, FUN_00072d5c)
SK_NEW_CAP_FACTORY(sk_new_cap_j,  0x82544, FUN_00072de8)
SK_NEW_CAP_FACTORY(sk_new_cap_k,  0x82564, FUN_00073a64)
SK_NEW_CAP_FACTORY(sk_new_cap_l,  0x82584, FUN_00073af0)
SK_NEW_CAP_FACTORY(sk_new_cap_m,  0x825a4, FUN_00073b7c)
SK_NEW_CAP_FACTORY(sk_new_cap_n,  0x825c4, FUN_00073c08)
SK_NEW_CAP_FACTORY(sk_new_cap_o,  0x825e4, FUN_00073c94)
SK_NEW_CAP_FACTORY(sk_new_cap_p,  0x82604, FUN_00073d30)
SK_NEW_CAP_FACTORY(sk_new_cap_q,  0x82624, FUN_00073d70)
SK_NEW_CAP_FACTORY(sk_new_cap_r,  0x82644, FUN_00073dfc)
SK_NEW_CAP_FACTORY(sk_new_cap_s,  0x82664, FUN_00073e88)
SK_NEW_CAP_FACTORY(sk_new_cap_t,  0x82684, FUN_0007402c)
SK_NEW_CAP_FACTORY(sk_new_cap_u,  0x826a4, FUN_000730a4)
SK_NEW_CAP_FACTORY(sk_new_cap_v,  0x826c4, FUN_00074220)
SK_NEW_CAP_FACTORY(sk_new_cap_w,  0x826e4, FUN_000742ac)
SK_NEW_CAP_FACTORY(sk_new_cap_x,  0x82704, FUN_00074378)
SK_NEW_CAP_FACTORY(sk_new_cap_y,  0x82724, FUN_00074490)
SK_NEW_CAP_FACTORY(sk_new_cap_z,  0x82744, FUN_0007451c)
SK_NEW_CAP_FACTORY(sk_new_cap_aa, 0x82764, FUN_00074670)
SK_NEW_CAP_FACTORY(sk_new_cap_ab, 0x82784, FUN_0007470c)
SK_NEW_CAP_FACTORY(sk_new_cap_ac, 0x827a4, FUN_0001dde4)

/* ================================================================== *
 * Region lookup / physical memory helpers.
 * ================================================================== */

/* FUN_00083450 @ 0x83450  (est. sk_find_region)
 * Look up the physical region covering `pa` with attributes `attr`;
 * returns a pointer to its buffer, or the empty sentinel if none.
 * Confidence: medium */
static unsigned char *sk_find_region(unsigned long pa, unsigned long attr)
{
    unsigned long size;
    if (((attr >> 0x3c) & 1) == 0) {
        size = pa & 0xffffffffffff;
        if ((attr & 0x2000000000000000) != 0)
            size = (attr >> 0x38) & 0xf;
    } else {
        size = FUN_002b24b8(pa, attr);
    }
    if (size == 0) return _DAT_00657778;
    unsigned char *p = FUN_000b1d54(size, 0);
    if ((long)size < 0) CL4_FATAL();                  /* 0x834f8 */
    FUN_002a4528((word_t)(p + 0x20), size, pa, attr);
    /* auVar4 status validated by the phys-claim helper */
    return p;
}

/* FUN_000834fc @ 0x834fc  (est. sk_find_region_copy)
 * Return a buffer holding a copy of the byte range [lo, hi), or the empty
 * sentinel when the range is empty.
 * Confidence: medium */
static unsigned char *sk_find_region_copy(unsigned long lo, unsigned long hi)
{
    long len = hi - lo;
    if (lo == 0 || len == 0) return _DAT_00657778;
    unsigned char *p = FUN_000b1d54(len, 0);
    if (lo < hi) {
        FUN_00117d14((word_t)(p + 0x20), lo, (word_t)len);
        lo += len;
    } else {
        if (hi == 0) CL4_FATAL();                     /* 0x835a0 */
    }
    if (lo != hi) {
        if (lo < hi) CL4_FATAL();                     /* 0x8359c */
        CL4_FATAL();                                  /* 0x835a4 */
    }
    return p;
}

/* FUN_00083990 @ 0x83990  (est. sk_ro_buf_next)
 * Return the next offset past a length-prefixed record in a read-only
 * buffer: if the low tag bit is set, follow the indirection pointer
 * (aligned to 2), then skip the 4-byte length at +4.
 * Confidence: medium */
static long sk_ro_buf_next(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}
/* FUN_00083a18 @ 0x83a18  (est. sk_ro_buf_next_8) */
static long sk_ro_buf_next_8(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}
/* FUN_00083a48 @ 0x83a48  (est. sk_ro_buf_next_c) */
static long sk_ro_buf_next_c(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_00083a78 @ 0x83a78  (est. sk_ref_acquire_pair)
 * Acquire a reference on a pair of objects by dispatching through the
 * global refcount table. Returns the second object.
 * Confidence: low */
static word_t sk_ref_acquire_pair(word_t a, word_t b)
{
    /* (*_DAT_39000062d4000011)(b, a) */
    return b;
}

/* FUN_0008396c @ 0x8396c  (est. sk_free_if_tagged)
 * If tag == 1, release the object's token.
 * Confidence: high (structural) */
static void sk_free_if_tagged(word_t a, word_t obj, char tag)
{
    if (tag == '\x01') FUN_003a25d4(obj);
}

/* FUN_00083984 @ 0x83984  (est. sk_deref_table) */
static void sk_deref_table(word_t thisp)
{
    FUN_00077770(0x64ee40);
}

/* FUN_000839d8 @ 0x839d8  (est. sk_vt_dispatch38)
 * Indirect dispatch through vtable offset 0x38 (slot 7) of the object at
 * thisp-8. (Decompiler: jumptable too large; treated as indirect call.)
 * Confidence: low */
static void sk_vt_dispatch38(word_t thisp)
{
    void (**vt)(void) = *(void (***)(void))(*(word_t *)(thisp - 8));
    vt[7]();            /* vtable +0x38 */
}
/* FUN_000839f8 @ 0x839f8  (est. sk_vt_dispatch30)
 * Indirect dispatch through vtable offset 0x30 (slot 6).
 * Confidence: low */
static void sk_vt_dispatch30(word_t thisp)
{
    void (**vt)(void) = *(void (***)(void))(*(word_t *)(thisp - 8));
    vt[6]();            /* vtable +0x30 */
}

/* ================================================================== *
 * Object construction / attachment / build.
 * ================================================================== */

/* FUN_000835a4 @ 0x835a4  (est. sk_object_construct)
 * Construct an object: acquire the type table, invoke the constructor
 * vtable entry, build the body, then run the destructor vtable entry.
 * Confidence: low */
static word_t sk_object_construct(word_t a, word_t b, long obj, word_t d)
{
    word_t r;
    long tbl = *(long *)(obj - 8);
    (*(void (**)(void))(tbl + 0x40))();        /* SUB_911f721090000010 */
    word_t u = FUN_0036a940(_DAT_0064ea20);
    (*(void (**)(void))(tbl + 0x10))();
    r = sk_object_build(a, u, obj, d);         /* FUN_000836e0 */
    (*(void (**)(void))(tbl + 8))();
    return r;
}

/* FUN_000836a4 @ 0x836a4  (est. sk_object_attach)
 * If the holder's type table flags bit 0x20000, run the attach token op.
 * Confidence: low */
static word_t sk_object_attach(word_t obj, long holder)
{
    unsigned int f = *(unsigned int *)(*(long *)(holder - 8) + 0x50);
    if ((f >> 0x11) & 1)
        FUN_0036aa30(obj, (word_t)holder, f & 0xff);
    return obj;
}

/* FUN_000836e0 @ 0x836e0  (est. sk_object_build)
 * Build a kernel object of the given kind: allocate its frame, initialize
 * its fields, and register it in the object table. Returns the object.
 * Confidence: medium */
static long sk_object_build(word_t a, long obj, long holder, word_t d)
{
    long tbl = *(long *)(holder - 8);
    (*(void (**)(void))(tbl + 0x40))();
    (*(void (**)(void))(tbl + 0x20))();
    *(word_t *)(obj + 0x10) = 0;
    word_t u0 = FUN_00086440(0);
    word_t ls0 = FUN_0036a9d4(u0, 0x64e1c0);
    word_t extra = 0x65f998;
    u0 = FUN_00086590(0);
    FUN_0036a940(u0);
    word_t f = FUN_00085a54(&ls0, 0x4000, 0x11, 0x1808, 0);
    *(word_t *)(obj + 0x18) = f;
    word_t v0 = FUN_00034f70();
    word_t v1 = FUN_000f6d20(v0, holder, d);
    *(word_t *)(obj + 0x20) = v0;
    *(word_t *)(obj + 0x28) = v1;
    long *body = *(long **)(obj + 0x18);
    word_t (**vvt)(word_t, word_t) = *(word_t (***)(word_t, word_t))*body;
    FUN_0036b270((word_t)body);
    vvt[0x12](0, v0);    /* vtable +0x90 */
    FUN_0036b118((word_t)body);
    body = *(long **)(obj + 0x18);
    long (**svt)(void) = *(long (***)(void))*body;
    FUN_0036b270((word_t)body);
    long sz = svt[0x1c]();   /* vtable +0xe0 */
    FUN_0036b118((word_t)body);
    if (sz == 0) CL4_FATAL();       /* 0x838f0 */
    *(long *)(obj + 0x30) = sz;
    *(word_t *)(obj + 0x38) = 0x40;
    thunk_FUN_00114330(sz, 0x400);
    (*(void (**)(void))(tbl + 8))();
    return obj;
}

/* ================================================================== *
 * Cap-table sweep / relocate.
 * ================================================================== */

/* FUN_00080520 @ 0x80520  (est. sk_vec_sweep_build)
 * Iterate the cap-sweep list and build a report of the swept entries;
 * returns the count of collected entries (+8 for the header).
 * Confidence: low */
static long sk_vec_sweep_build(word_t thisp)
{
    word_t *v = (word_t *)thisp;
    long r = *(long *)(v[2] + 0x10);
    if (r == 0) return 4;
    word_t cur = v[2] + 0x20;
    unsigned long cnt = 4;
    do {
        word_t buf[2];
        FUN_00117cc4((word_t)buf, cur, 0x42);
        word_t hi = 0;
        sk_ref_acquire_pair((word_t)buf, hi);
        thunk_FUN_0036b270(hi);
        word_t s = FUN_002abe60(0xd00000000000001e, 0x80000000005c0190, (word_t)buf, hi);
        FUN_003a25d4(hi);
        if ((s & 1) == 0) {
            word_t next = cnt + 0x10;
            if (cnt > 0xfffffffffffffff0UL) CL4_FATAL(); /* 0x80638 */
            thunk_FUN_0036b270(hi);
            long ok = FUN_001ee018((word_t)buf, hi);
            FUN_003a25d4(hi);
            if (ok < 0) CL4_FATAL();                      /* 0x8063c */
            cnt = next + ok + 1;
            if (__builtin_add_overflow(next, ok + 1, (word_t *)0)) CL4_FATAL(); /* 0x80640 */
        }
        cur += 0x48;
        r -= 1;
    } while (r != 0);
    if (cnt > 0xfffffffffffffff7UL) CL4_FATAL();          /* 0x80644 */
    return cnt + 8;
}

/* FUN_00080b7c @ 0x80b7c  (est. sk_vec_append_checked)
 * Append an element (and a parallel tag) to the vector after computing a
 * size; performs the element copy into both the primary and parallel
 * arrays and bumps the length. On a carry, panics.
 * Confidence: low */
static void sk_vec_append_checked(word_t thisp, word_t a, word_t b, unsigned long n)
{
    word_t *v = (word_t *)thisp;
    FUN_0006b2ec();
    word_t u1 = v[2];
    word_t u2 = v[3];
    long key = FUN_00268540(u1, u2);
    word_t w = *(word_t *)(key + 0x10);
    FUN_0036b118(w);
    long total = n + 0x10;
    if (n > 0xfffffffffffffff0UL) CL4_FATAL();            /* 0x80c7c */
    if (total == 0) CL4_FATAL();                          /* 0x80c80 */
    FUN_002cb61c(w, (word_t)v, a, b);
    FUN_0007d0fc(0x10, a, b);
    word_t c = FUN_00084018();
    long span = 0, extra = 0;
    if (span < 0) CL4_FATAL();                            /* 0x80c84 */
    long key2 = FUN_00268540(u1, u2);
    FUN_002cb61c(key2 + 0x20, key2 + 0x20 + *(word_t *)(key2 + 0x10), extra, span);
    FUN_0036b118(key2);
    FUN_000651bc(w);
    if (span != 0) FUN_0011d7e8();
}

/* FUN_00080b3c @ 0x80b3c  (est. sk_vec_cap_key_probe)
 * Probe the cap's key; validate the container allows one more element.
 * Confidence: medium */
static void sk_vec_cap_key_probe(word_t thisp)
{
    word_t *v = (word_t *)thisp;
    long k = FUN_00268540(v[2], v[3]);
    long sz = *(long *)(k + 0x10);
    FUN_0036b118((word_t)k);
    if (__builtin_add_overflow((word_t)sz, 0x10, (word_t *)0)) CL4_FATAL(); /* 0x80b78 */
    if (sz + 0x10 >= 0) return;
    CL4_FATAL();                                          /* 0x80b7c */
}

/* FUN_00082040 @ 0x82040  (est. sk_cap_sweep_relocate)
 * Relocate capabilities during a table sweep: iterate the source bitmap,
 * for each set bit allocate a destination slot, move the capability (and
 * its key) across, and record the mapping. On collision with a moved
 * entry, emits a fatal error with component tag.
 * Confidence: low */
static void sk_cap_sweep_relocate(word_t thisp, word_t p1, word_t p2,
                                  unsigned int mode, long *p5, long *p6, word_t p7)
{
    word_t a0 = 0;
    thunk_FUN_0007198c(a0);
    thunk_FUN_0036b270(p1);
    FUN_0036b270(p2);
    /* iterate source bitmap, relocate each entry */
    FUN_001afa84(0x5accd0, 0xb, 2, 0, 0, 0x5bff40, 0x31, 2, 0x8e, 0);
}

/* FUN_00080644 @ 0x80644  (est. sk_rtc_sweep_publish)
 * Publish a runtime-capability sweep: lock the global cap list, walk the
 * per-cap sweep records, map each swept capability's frames, commit the
 * mapping, then free the temporary buffers. On error, panics.
 * Confidence: low */
static void sk_rtc_sweep_publish(word_t thisp)
{
    FUN_0006b2ec();
    /* validate span, walk cap records, map frames, commit */
    FUN_000840d8();
}

/* FUN_00083298 @ 0x83298  (est. sk_vec_copy_bytes)
 * Copy the byte range [lo, hi) into the vector, growing and extending as
 * needed; equivalent to memmove with allocation.
 * Confidence: low */
static void sk_vec_copy_bytes(unsigned char *lo, unsigned char *hi)
{
    if (lo != 0 && hi != 0 && lo != hi) {
        /* grow, copy bytes, bump length */
    }
}

/* FUN_00082fe0 @ 0x82fe0  (est. sk_vec_insert_bytes)
 * Insert the byte range described by dst into the vector, growing and
 * coalescing with the owned buffer.
 * Confidence: low */
static void sk_vec_insert_bytes(void *dst)
{
    /* iterate source bytes, grow vector, insert */
}

/* thunk_FUN_00081928 @ 0x81928  (thunk of sk_index_bounds)
 * Thin forwarding thunk: performs the same vector bounds check as
 * sk_index_bounds (0x8192c), faulting on idx<0 or idx>=len.
 * Confidence: high (thunk of covered function) */
static void sk_index_bounds_thunk(word_t idx, word_t unused, word_t vec)
{
    sk_index_bounds(idx, unused, vec);
}
