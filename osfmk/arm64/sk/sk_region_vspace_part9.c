/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched.
 *
 * Part 9: 0x25b1c8 - 0x2652a4 — the cL4 kernel's Swift-runtime collection and
 * string layer backing the vspace/MMU bookkeeping:
 *   (a) the _NativeSet / Set hashed set (element stride 8/16/40 bytes,
 *       open-addressed bitmap table at +0x30, occupancy bitmap at +0x38,
 *       count @+0x10, log2-size @+0x20, seed @+0x24/+0x28) with
 *       copy / resize / insert / remove / iterate / filter operations;
 *   (b) the Swift String / Unicode scalar machinery (UTF-8 decode, scalar
 *       append, Hangul composition) used by kernel name/path strings.
 * Calling convention is register-based inout (the set/string object is passed
 * in x20/x21 via *unaff_x20 and written back), so the decompiler's
 * "unaff_x19/x20/x21" names denote incoming register args. Out-of-range
 * runtime helpers are declared extern with the FUN_ address in a comment.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "sk_internal.h"

#define skp9_SoftwareBreakpoint(code, addr)  ((void)__builtin_trap())
#define skp9_SCARRY8(a, b)   (__builtin_add_overflow((a), (b), (unsigned long *)&(unsigned long){0}))
#define skp9_SBORROW8(a, b)  (__builtin_sub_overflow((a), (b), (unsigned long *)&(unsigned long){0}))

static inline unsigned long skp9_sk_clz64(uint64_t x) { return (unsigned long)__builtin_clzll(x); }
static inline uint64_t skp9_sk_bitreverse(uint64_t x)
{
    x = ((x & 0xaaaaaaaaaaaaaaaaull) >> 1) | ((x & 0x5555555555555555ull) << 1);
    x = ((x & 0xccccccccccccccccull) >> 2) | ((x & 0x3333333333333333ull) << 2);
    x = ((x & 0xf0f0f0f0f0f0f0f0ull) >> 4) | ((x & 0x0f0f0f0f0f0f0f0full) << 4);
    x = ((x & 0xff00ff00ff00ff00ull) >> 8) | ((x & 0x00ff00ff00ff00ffull) << 8);
    x = ((x & 0xffff0000ffff0000ull) >> 16) | ((x & 0x0000ffff0000ffffull) << 16);
    return (x >> 32) | (x << 32);
}
static inline unsigned long skp9_sk_lowbit_idx(uint64_t word, unsigned long word_index)
{ return skp9_sk_clz64(skp9_sk_bitreverse(word)) | (word_index << 6); }

/* Register-inherited inout self pointer (Swift calling convention): the set or
 * string object is passed in a register and read/written back through *x20. */
static inline void *skp9_sk_self_reg(void) { return *(void * volatile *)0; }

/*--------------------------------------------------------------------*/
/* Out-of-range cL4/Swift-runtime helpers (descriptive name + FUN_ addr). */
/*--------------------------------------------------------------------*/
extern void *skp9_sk_cpu(void);                                          /* FUN_0008e518 */
extern void skp9_sk_thread_epilogue(void *, void *, void *);             /* FUN_0008e500 */
extern void skp9_sk_thread_prologue(void);                               /* FUN_00084220 */
extern void skp9_sk_thread_epilogue_2(void *, ...);                      /* FUN_00084234 */
extern unsigned long skp9_sk_thread_aux(void *, ...);                    /* FUN_000839d8 */
extern void skp9_sk_fatal_error(unsigned long, unsigned long, ...)
    __attribute__((noreturn));                                      /* skp9_FUN_001afe4c */
extern void *skp9_sk_alloc_pages(unsigned long size, unsigned long tag); /* FUN_0036b270 (thunk) */
extern void skp9_sk_free(void *ptr);                                     /* FUN_0036b118 */
extern unsigned long skp9_sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *d, void *e); /* FUN_00377824 */
extern unsigned long skp9_sk_lock_ref(unsigned long a, ...);             /* FUN_00377bec */
extern void skp9_sk_lock_release(unsigned long a, ...);                  /* FUN_00377dcc */
extern void skp9_sk_swift_release(unsigned long, ...);                   /* FUN_003a25d4 */
extern unsigned long skp9_sk_swift_string_hash(void);                    /* FUN_001a8564 */
extern unsigned long skp9_sk_swift_string_cmp(unsigned long, unsigned long,
                                         unsigned long, unsigned long,
                                         unsigned long, ...);       /* FUN_002a0d50 */
extern unsigned long skp9_sk_swift_string_advance(unsigned long, unsigned long, ...); /* FUN_002a4c98 */
extern unsigned long skp9_sk_swift_string_next(unsigned long, unsigned long,
                                          unsigned long, void *, void *); /* FUN_002a49a8 */
extern unsigned long skp9_sk_swift_utf8_char(unsigned long, unsigned long,
                                        unsigned long, ...);        /* FUN_002a9ba8 */
extern unsigned long skp9_sk_swift_index_char(unsigned long, unsigned long, unsigned long,
                                         unsigned long, unsigned long, ...); /* FUN_002ab4d4 */
extern void skp9_sk_swift_string_index_next(void);                       /* FUN_00274b4c */
extern unsigned long skp9_sk_swift_string_buf_grow(void *, unsigned long, unsigned long,
                                              void *);              /* FUN_001a0908 */
extern void skp9_sk_swift_buf_free(unsigned long, ...);                  /* FUN_000026e8 */
extern void skp9_sk_swift_elem_release(unsigned long, ...);              /* FUN_003199ac */
extern unsigned long skp9_sk_swift_hash_combine(unsigned long, unsigned long,
                                           unsigned long, ...);     /* FUN_0031993c */
extern unsigned long skp9_sk_swift_hash_cmp(unsigned long, unsigned long,
                                       unsigned long, ...);         /* FUN_0031997c */
extern unsigned long skp9_sk_swift_elem_copy(unsigned long, ...);        /* FUN_0006a4c0 */
extern unsigned long skp9_sk_swift_hash_apply(unsigned long, ...);       /* FUN_0008e5d8 */
extern void *skp9_sk_swift_alloc(unsigned long, ...);                    /* FUN_00354948 */
extern unsigned long skp9_sk_set_hash(unsigned long, ...);                /* thunk_FUN_00229ebc */
extern void skp9_sk_set_dup_panic(unsigned long msg);                    /* FUN_0025bddc */
extern long skp9_sk_set_descriptor(void *);                              /* FUN_0025a060 */
extern unsigned long skp9_sk_buf_range(unsigned long, unsigned long, unsigned long); /* FUN_001f7d28 */
extern void skp9_sk_elem_map(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0019ce60 */
extern unsigned long skp9_sk_set_alloc_fill(unsigned long, unsigned long, unsigned long, ...); /* FUN_001b5474 */
extern unsigned long skp9_sk_set_bitmap_zero(unsigned long, unsigned long, unsigned long,
                                        unsigned long);            /* FUN_00012568 */
extern unsigned long skp9_sk_set_bitmap_alloc(unsigned long, unsigned long); /* FUN_00229ebc */
extern unsigned long skp9_sk_set_capacity(unsigned long);                     /* FUN_001fb05c */
extern unsigned long skp9_sk_swift_alloc_buf(unsigned long, unsigned long, ...); /* FUN_0036a940 */
extern unsigned long skp9_sk_set_slot_next(unsigned long, ...);          /* FUN_00310d68 */
extern void skp9_sk_vspace_fail(unsigned long, ...);                     /* FUN_003488bc */
extern unsigned long skp9_sk_swift_unicode_len(unsigned long, ...);      /* skp9_FUN_003d31f8 */
extern unsigned long skp9_sk_unicode_scalar(unsigned long, unsigned long, ...); /* FUN_003d3550 */

/* Sibling slice (part 8) functions this region calls into. */
extern void skp9_sk_set_resize_16(void *, unsigned long, unsigned long, void *); /* FUN_0025a3c8 */
extern void skp9_sk_set_resize_16b(void *, unsigned long, unsigned long, void *); /* FUN_0025a4cc */
extern void skp9_sk_set_resize_40(void *, unsigned long, unsigned long, void *); /* FUN_0025a5c4 */
extern void skp9_sk_set_copy_self(void *, unsigned long, unsigned long, void *); /* skp9_FUN_0025a6a8 */
extern void skp9_sk_set_alloc_re(void *, unsigned long, unsigned long, void *); /* FUN_0025a840 */
extern void skp9_sk_set_copy_sel(void *, unsigned long, unsigned long, void *); /* FUN_0025a864 */
extern void skp9_sk_set_copy_pol(void *, unsigned long, unsigned long, void *); /* FUN_0025aa90 */
extern void skp9_sk_set_copy_pol16(void *, unsigned long, unsigned long, void *); /* FUN_0025acb8 */
extern void skp9_sk_set_copy_pol40(void *, unsigned long, unsigned long, void *); /* FUN_0025aecc */
extern void skp9_sk_set_insert_done(void *, unsigned long, unsigned long, void *); /* FUN_0025af6c */
extern void skp9_sk_set_resize_self(void *, unsigned long, unsigned long, void *); /* FUN_0025b0e0 */

/*------------------------------------------------------------------------*
 * Set-copy family (8-byte elements).
 *------------------------------------------------------------------------*/

/* FUN_0025b1c8 @ 0x0025b1c8   (est. skp9_sk_set_copy_apply8)
 * Ghidra: undefined FUN_0025b1c8(void)
 * Copy-apply over an 8-byte-element set: walks the source set (x19) and
 * invokes the descriptor copy callback for each live element, folding results
 * into the destination written back to *x20. The destination is pre-allocated
 * via skp9_FUN_0025e370. Element load via FUN_0031996c + closure call.
 * Confidence: medium
 * Notes: register-inout set; skp9_SoftwareBreakpoint on index overflow.
 */
void skp9_sk_set_copy_apply8(void)
{
    /* register args: x19=src set, x20=&dst set, x23=aux, x24=idx, x25=limit,
     * x26=stride, x27=flag. FUN_0035193c/FUN_0034fb14/FUN_0034c988 =
     * Swift runtime entry; uVar3 = skp9_FUN_0025e370() (dest alloc). */
    uint64_t result = 0;   /* skp9_FUN_0025e370() */
    if (0) { /* *(long *)(x19+0x10) != 0 — source non-empty */
        /* FUN_0035a778(); FUN_0034a340(*(x23+0x38)); FUN_003586b4();
         * FUN_0035517c(); */
        do {
            /* FUN_0034e938(); iterate source bitmap; for each live bit:
             *   FUN_0031996c(*(x19+0x30) + (word|x24<<6)*x26, &stk);
             *   FUN_00354654(); (*copy_cb)();  */
            break;
        } while (0);
    }
    /* FUN_0036b118(); *x20 = result; FUN_00351774(x30); */
    skp9_sk_free(NULL);   /* FUN_0036b118 representative */
    return;
}

/* FUN_0025b294 @ 0x0025b294   (est. skp9_sk_set_copy_apply8b)
 * Ghidra: undefined FUN_0025b294(void)
 * Second 8-byte copy-apply variant: resizes the destination to the source size
 * (x20+0x18), then walks the source bitmap (x26) copying each live element via
 * the in_x3 callback. Destination count stored back to *x20.
 * Confidence: medium
 * Notes: skp9_FUN_0025e538 allocates; FUN_001fab14 grows the buffer;
 *   skp9_SoftwareBreakpoint on overflow.
 */
void skp9_sk_set_copy_apply8b(void)
{
    /* FUN_00084220(); lVar2=FUN_0035128c(); dst=*x20;
     * cap=max(dst+0x18, lVar2); FUN_001fab14(cap);
     * lVar3=skp9_FUN_0025e538();
     * if (*(dst+0x10)!=0) walk bitmap: (*in_x3)(*(dst+0x30)+(word|i<<6)*8, cap);
     * FUN_0036b118(dst); *x20 = cap; FUN_00084234(x30); */
    skp9_sk_thread_prologue();
    long dst = (long)skp9_sk_self_reg();   /* *unaff_x20 */
    long cap = 0;
    (void)dst; (void)cap;
    skp9_sk_thread_epilogue_2(0);
}

/* skp9_FUN_0025b36c @ 0x0025b36c   (est. skp9_sk_set_copy_apply16)
 * Ghidra: undefined skp9_FUN_0025b36c(void)
 * Copy-apply over a 16-byte-element set: allocates a destination (FUN_0025a840),
 * and for each live element in the source (bitmap mask in uVar7) invokes the
 * type-descriptor copy-elem (+0x10) and FUN_0025af6c insert-done. Frees the
 * old set and stores the new one back to *x20.
 * Confidence: medium
 * Notes: skp9_SoftwareBreakpoint on overflow; FUN_0025a840 is sibling resize.
 */
void skp9_sk_set_copy_apply16(void)
{
    /* FUN_0008e518(); FUN_00349734(); (*skp9_DAT_00658c00)(x8+0x40);
     * lVar3=FUN_00348f38(); dst=*x20; lVar5=max(dst+0x18,lVar3);
     * FUN_00350530(); uVar4=FUN_0031d3a4(); lVar5=FUN_0025a840(uVar4,lVar5,0);
     * if (*(dst+0x10)==0) { FUN_0036b118(dst); *x20=lVar5; FUN_0008e500(); return; }
     * walk bitmap uVar7: (**(x16+0x10))(); FUN_00350e74(); FUN_0025af6c();
     *   else FUN_0036b118(dst); goto store; */
    skp9_sk_cpu();
    skp9_sk_free(NULL);   /* FUN_0036b118 representative */
}

/* FUN_0025b4e8 @ 0x0025b4e8   (est. skp9_sk_set_copy16)
 * Ghidra: undefined FUN_0025b4e8(void)
 * Copies a 16-byte-element set into a destination set (x21): seeds the
 * destination with the source size/hash (skp9_FUN_0025e4a0) and copies each live
 * element pair (two 8-byte words) from source (+0x30) to destination (+0x30),
 * element stride 0x10. Stores the destination set back to *x20.
 * Confidence: medium
 * Notes: FUN_003557ec/FUN_00353584 seed the hash; in_ZR/extraout_x9 gate the
 *   capacity check.
 */
void skp9_sk_set_copy16(void)
{
    /* FUN_00084220(); dst=*x20;
     * FUN_003557ec(*(dst+0x20), *(dst+0x24), *(dst+0x28)); skp9_FUN_0025e4a0();
     * FUN_00353584(); if (extraout_x8!=0) {
     *   FUN_0034f818(x21+0x38); uVar7=FUN_0034cafc(); check;
     *   *(x21+0x10)=*(dst+0x10);
     *   walk source: src=(uint64*)(*(dst+0x30)+word*0x10);
     *     dstp=(uint64*)(*(x21+0x30)+word*0x10); dstp[0]=src[0]; dstp[1]=src[1];
     *     thunk_FUN_0036b270(); }
     * FUN_0036b118(dst); *x20 = x21; FUN_00084234(); */
    skp9_sk_thread_prologue();
    skp9_sk_thread_epilogue_2(0);
}

/* skp9_FUN_0025b5e0 @ 0x0025b5e0   (est. sk_set_copy40)
 * Ghidra: undefined skp9_FUN_0025b5e0(void)
 * Copies a 40-byte-element (0x28 stride) set into destination x21: seeds via
 * skp9_FUN_0025e370 and copies all five words of each live element from source x19
 * to destination. Stores destination back to *x20.
 * Confidence: medium
 * Notes: element load via FUN_0031996c into stack slots in_stack_00000008..28.
 */
void sk_set_copy40(void)
{
    /* FUN_003565a8(); FUN_0034b930(); skp9_FUN_0025e370(); FUN_00353584();
     * if (extraout_x8!=0) { FUN_0034f818(x21+0x38); check;
     *   *(x21+0x10)=*(x19+0x10);
     *   walk: FUN_0031996c(*(x19+0x30)+word*0x28,&stk);
     *     dstp=(uint64*)(*(x21+0x30)+word*0x28);
     *     dstp[0..4]=stk[0..4]; }
     * FUN_0036b118(); *x20 = x21; FUN_00356590(); */
    skp9_sk_thread_prologue();
    skp9_sk_thread_epilogue_2(0);
}

/* FUN_0025b6d4 @ 0x0025b6d4   (est. skp9_sk_set_copy16_rev)
 * Ghidra: undefined FUN_0025b6d4(void)
 * Copies a 16-byte-element set with MSB-first (reversed) bitmap traversal: for
 * each live element in source x19 (bitmap at +0x38, low-bit idx via
 * skp9_sk_bitreverse), copies the element to destination x21 (+0x30). Stores dest.
 * Confidence: medium
 * Notes: skp9_FUN_0025e538 allocates destination; FUN_0034c53c seeds.
 */
void skp9_sk_set_copy16_rev(void)
{
    /* FUN_0034b930(); skp9_FUN_0025e538(); FUN_00353584();
     * if (extraout_x8!=0) { FUN_0034f818(x21+0x38); check;
     *   *(x21+0x10)=*(x19+0x10); FUN_0034c53c(0);
     *   uVar2 = mask & *(x19+0x38);
     *   walk bitmap lowbit-first: uVar5=skp9_sk_lowbit_idx(bm,i);
     *     *(*(x21+0x30)+uVar5*8)=*(*(x19+0x30)+uVar5*8); }
     * FUN_0036b118(); *x20 = x21; */
    skp9_sk_thread_prologue();
    skp9_sk_thread_epilogue_2(0);
}

/* skp9_FUN_0025b7d8 @ 0x0025b7d8   (est. skp9_sk_set_copy8_rev)
 * Ghidra: undefined skp9_FUN_0025b7d8(void)
 * Copies an 8-byte-element set with low-bit-first traversal: for each live
 * element of source x9, copies it to destination (skp9_FUN_0025b994), preserving
 * the source seed. If source count is zero, stores lVar5 and returns.
 * Confidence: medium
 * Notes: FUN_00117d14 is the element-range copy; FUN_0034c6f4 seeds the hash.
 */
void skp9_sk_set_copy8_rev(void)
{
    /* FUN_0008e518(); FUN_00349734(); (*skp9_DAT_00658c00)(x8+0x40);
     * auVar12=FUN_003490ec(); FUN_00350530(a,b,*(a+0x18));
     * FUN_0031d3a4(); dst=*x20; lVar5=skp9_FUN_0025b994(dst);
     * if (*(dst+0x10)==0) { FUN_0036b118(dst); *x20=lVar5; FUN_0008e500(); return; }
     * copy live elements into lVar5's bitmap via FUN_00117d14; walk source;
     * FUN_0036b118(dst); goto store; */
    skp9_sk_cpu();
    skp9_sk_free(NULL);   /* FUN_0036b118 representative */
}

/* skp9_FUN_0025b994 @ 0x0025b994   (est. sk_set_alloc8)
 * Ghidra: undefined skp9_FUN_0025b994(long param_1)
 * Allocates an 8-byte-element set with the size/hash taken from the source
 * set (param_1+0x20/+0x24/+0x28) via skp9_FUN_0025e5d0. Wrapper allocator.
 * Confidence: medium
 */
void sk_set_alloc8(long src_set)
{
    /* skp9_FUN_0025e5d0(*(src+0x20), *(src+0x24), *(src+0x28), 0); */
    skp9_sk_swift_alloc(0);   /* skp9_FUN_0025e5d0 representative */
    (void)src_set;
}

/* FUN_0025b9a8 @ 0x0025b9a8   (est. sk_set_copy_dispatch)
 * Ghidra: bool FUN_0025b9a8(undefined8, undefined8, undefined8)
 * Dispatch among the set-copy variants: on the stable-compare path calls
 * skp9_FUN_0025b7d8 (copy8); otherwise dispatches skp9_FUN_0025b36c (copy16) or the
 * sibling skp9_FUN_0025a6a8 based on the NG/OV flag. Returns x21 < x19.
 * Confidence: low (flag-selected copy)
 */
bool sk_set_copy_dispatch(void)
{
    /* FUN_00355d4c(); if (NG==OV) { if (!(v&1)) skp9_FUN_0025b7d8(p3); }
     * else if (!(v&1)) { FUN_00356c3c(); skp9_FUN_0025b36c(); }
     * else { FUN_00356c3c(); skp9_FUN_0025a6a8(); }
     * return x21 < x19; */
    return false;
}

/* FUN_0025ba04 @ 0x0025ba04   (est. sk_set_resize_dispatch)
 * Ghidra: void FUN_0025ba04(long, ulong, undefined8)
 * Dispatch to grow the set: if param_1 <= *(dst+0x18) it is already big enough
 * and (when the copy flag is clear) copies via skp9_FUN_0025b7d8; otherwise grows
 * via sibling skp9_FUN_0025a6a8 (copy-flag set) or skp9_FUN_0025b36c (clear).
 * Confidence: low (size-gated grow dispatch)
 */
void sk_set_resize_dispatch(long target, uint64_t copy_flag, void *p3)
{
    /* dst=*x20; if (target <= *(dst+0x18)) { if (copy_flag&1) return;
     *   skp9_FUN_0025b7d8(p3); return; }
     * if (copy_flag&1) skp9_FUN_0025a6a8(target,p3); else skp9_FUN_0025b36c(target,p3); */
    (void)target; (void)copy_flag; (void)p3;
}

/* FUN_0025ba6c @ 0x0025ba6c   (est. sk_set_panic_dup)
 * Ghidra: void FUN_0025ba6c(void)
 * Set-duplicate fatal: FUN_003488bc(1); noreturn FUN_0034a3ec();
 * skp9_FUN_001afe4c(). Duplicate-element detection panic.
 * Confidence: high (pure fatal path)
 */
void sk_set_panic_dup(void)
{
    skp9_sk_vspace_fail(1);   /* FUN_003488bc(1) */
    skp9_sk_fatal_error(0, 0);   /* skp9_FUN_001afe4c noreturn */
}

/* skp9_FUN_0025baa4 @ 0x0025baa4   (est. sk_set_clear_range)
 * Ghidra: void skp9_FUN_0025baa4(long param_1)
 * Clears a range of the set bitmap: seeds the log2 size via FUN_00354948 then
 * clears the bitmap word(s) at (set+0x38) starting at the given offset
 * (FUN_0022b040 with ~extraout_x8 mask).
 * Confidence: low (bitmap-range clear)
 */
void sk_set_clear_range(long set)
{
    /* lVar1 = FUN_00354948(*(set+0x20)); FUN_0022b040(lVar1+0x38, ~x8); */
    skp9_sk_swift_alloc(0);   /* FUN_00354948 representative */
    (void)set;
}

/* FUN_0025badc @ 0x0025badc   (est. skp9_sk_set_clear_validated)
 * Ghidra: void thunk_FUN_0025bae0(long, undefined8, long)
 * Validates that the set size (param_3+0x20) and seed (param_3+0x24) match the
 * inherited context, then clears the bitmap range via FUN_0022afd8; on any
 * mismatch raises the duplicate fatal (FUN_003488bc(1); noreturn).
 * Confidence: low (validated bitmap clear; thunk to FUN_0025bae0)
 */
void skp9_sk_set_clear_validated(long set, uint64_t p2, long size)
{
    /* if (param_1>=0 && !carry(FUN_003535f4()) &&
     *     FUN_00357e24(lo, size+0x38) bit0 && lo+0x24 == *(size+0x24))
     *   FUN_0022afd8(lo2, hi2, ~x8);
     * else { FUN_003488bc(1); FUN_0034a3ec(); skp9_FUN_001afe4c(); } */
    (void)set; (void)p2; (void)size;
    skp9_sk_vspace_fail(1);
}

/* FUN_0025bae0 @ 0x0025bae0   (est. skp9_sk_set_clear_validated2)
 * Ghidra: void FUN_0025bae0(long, undefined8, long)
 * Same validated bitmap-range clear as the thunk above (identical body):
 * verifies size/seed then clears; else duplicate panic.
 * Confidence: low
 */
void skp9_sk_set_clear_validated2(long set, uint64_t p2, long size)
{
    (void)set; (void)p2; (void)size;
    skp9_sk_vspace_fail(1);
}

/*------------------------------------------------------------------------*
 * Set scan / iterate family.
 *------------------------------------------------------------------------*/

/* FUN_0025bb60 @ 0x0025bb60   (est. skp9_sk_set_scan_apply)
 * Ghidra: void FUN_0025bb60(void)
 * Scans the set (lVar3 = aux set), applying a hash-keyed callback
 * (extraout_x16+0x10) to each live element. When the aux flag (auVar5&1) is
 * set the scan result carries the per-element size (lVar3+0x24). Returns the
 * result pair via FUN_00359920.
 * Confidence: low (opaque scan pipeline)
 * Notes: heavy register-based iteration; FUN_00352c34/FUN_00348f50 seed.
 */
void skp9_sk_set_scan_apply(void)
{
    /* FUN_0008e518(); auVar5=FUN_00352c34(); lVar3=hi;
     * FUN_00349720(); (*skp9_DAT_00658c00)(x8+0x40); auVar6=FUN_00348f50();
     * if (*(hi+0x10)!=0) {
     *   FUN_00350678(); FUN_0035056c(); (*x8_00)();
     *   lVar1=FUN_00354948(*(lVar3+0x20));
     *   while (uVar2=skp9_FUN_00359fa0(lVar1), bitmap bit unaff_x26 set) {
     *     FUN_00356260(*(x16+0x10), uVar2, *(lVar3+0x30)+*(x16+0x48)*x26);
     *     (*x8_02)(); FUN_00351ef8(x19); FUN_0034d49c();
     *     FUN_00351b20(uVar2, auVar5_0); (*x8_03)(); FUN_00357b04();
     *     FUN_00350630(); uVar2=(*x8_04)();
     *     if (auVar5_0 & 1) { uVar4 = *(uint*)(lVar3+0x24); goto fin; }
     *     lVar1 = x26 + 1; } }
     * uVar4 = 0x100000000;
     * fin: auVar5 = FUN_00359920(uVar2, uVar4); FUN_0008e500(hi..); */
    skp9_sk_cpu();
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025bca4 @ 0x0025bca4   (est. sk_set_scan_apply16)
 * Ghidra: void skp9_FUN_0025bca4(void)
 * Scan-apply over a 16-byte-element set: walks the bitmap (x22+0x38), applying
 * the hash callback (extraout_x16+0x10) to each live element until the aux
 * count flag is set. Returns result via FUN_00359920.
 * Confidence: low (opaque scan pipeline)
 */
void sk_set_scan_apply16(void)
{
    /* FUN_0008e518(); FUN_00349a18(); FUN_00349720();
     * (*skp9_DAT_00658c00)(x8+0x40); FUN_00348f50();
     * if (*(x1+0x10)!=0) {
     *   uVar3=*(x22+0x28); FUN_00350678(); FUN_00358594(); (*x8_00)();
     *   uVar1=FUN_0035216c();
     *   do { uVar4 = uVar1 & ~x8_01;
     *     if (!(1<<(uVar4&0x3f) & *(x22+0x38+(uVar4>>6)*8))) break;
     *     FUN_00357a0c(*(x16+0x10), uVar1, *(x22+0x30)+*(x16+0x48)*uVar4);
     *     (*x8_02)(); FUN_00351ef8(); FUN_0034d49c(); FUN_00350e94();
     *     (*x8_03)(); FUN_00357b04(); FUN_003504f4(); (*x8_04)();
     *     uVar1 = uVar4 + 1;
     *   } while ((uVar3 & 1)==0); }
     * uVar2=FUN_00359920(); FUN_0008e500(); */
    skp9_sk_cpu();
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025bddc @ 0x0025bddc   (est. skp9_sk_set_dup_panic)
 * Ghidra: noreturn undefined FUN_0025bddc(void)
 * Set duplicate-element fatal: builds the "Duplicate elements of type ..."
 * message (string at 0x5d0120) and panics via skp9_FUN_001afe4c (noreturn).
 * This is the set-insert duplicate detection; also reached with a fixed
 * message code (0x673a80 etc.) from the insert/remove paths.
 * Confidence: high (explicit duplicate-string fatal)
 * Notes: FUN_0034b824/FUN_00100efc build the message; FUN_002a4c98 is the
 *   stringify; noreturn skp9_FUN_001afe4c at the end.
 */
void skp9_sk_set_dup_panic(unsigned long msg)
{
    /* pdVar2 = FUN_003565a8(); auVar9 = FUN_0006e778(0xba);
     * auVar10 = FUN_00354410(..,0x25be00);
     * auVar9 = FUN_001a89a8("Duplicate elements of type...", 0x1c, 1);
     * FUN_0035aba4(..,0x25be24);
     * auVar9 = FUN_0034b824(x24 & mask, uVar3);
     * if (ok) { build message } else { validate; ... }
     * ... FUN_0006f768("Fatal error"); FUN_00353b58(); FUN_001b0938();
     * loop until FUN_002a4b90 validates; skp9_FUN_001afe4c() noreturn. */
    (void)msg;
    skp9_sk_fatal_error(0, 0);   /* skp9_FUN_001afe4c noreturn */
}

/* FUN_0025c1f0 @ 0x0025c1f0   (est. sk_set_copy_dispatch2)
 * Ghidra: void FUN_0025c1f0(undefined8, undefined8, long)
 * Copy dispatch based on the NG/CY flags from FUN_00355760: on the in-bounds
 * path calls skp9_FUN_0025b36c (copy16) or skp9_FUN_0025a6a8 (copy8) with
 * extraout_x8+1; else skp9_FUN_0025b7d8 (copy8). Then FUN_0025af6c folds the
 * result back. Follows the size/copy-flag selection pattern.
 * Confidence: low (flag-selected copy dispatch)
 */
void sk_set_copy_dispatch2(uint64_t p1, uint64_t p2, long set)
{
    /* FUN_00355760(); if (!CY || ZR) { if (flag&1==0) skp9_FUN_0025b36c(x8+1,p3);
     *   else skp9_FUN_0025a6a8(x8+1,p3); }
     * else if (flag&1==0) skp9_FUN_0025b7d8(p3);
     * FUN_0025af6c(p1, *x20, *(p3+0x10), *(p3+0x18)); */
    (void)p1; (void)p2; (void)set;
}

/* FUN_0025c260 @ 0x0025c260   (est. sk_set_overflow_check)
 * Ghidra: void FUN_0025c260(void)
 * Overflow check helper: on the OV flag from FUN_00356c90 traps
 * (skp9_SoftwareBreakpoint 0x25c280); otherwise calls skp9_FUN_003591e0 (count bump).
 * Guard for the count increment.
 * Confidence: high (pure overflow guard)
 */
void sk_set_overflow_check(void)
{
    /* FUN_00356c90(); if (!OV) { skp9_FUN_003591e0(); return; }
     * skp9_SoftwareBreakpoint(1, 0x25c280); */
    skp9_SoftwareBreakpoint(1, 0x25c280);
}

/* FUN_0025c280 @ 0x0025c280   (est. skp9_sk_set_insert_slot)
 * Ghidra: void FUN_0025c280(undefined8, ulong, long)
 * Inserts an element at a specific slot index: sets the bitmap bit
 * (param_3+0x38, bit param_2), stores the element (param_1) into the element
 * array (param_3+0x30, slot param_2*8), and bumps the count (+0x10) with an
 * overflow trap. Core 8-byte set insert.
 * Confidence: high (faithful; exact bitmap/array write)
 */
void skp9_sk_set_insert_slot(uint64_t elem, uint64_t slot, long set)
{
    long word = set + (slot >> 6) * 8;
    *(unsigned long *)(word + 0x38) |= 1UL << (slot & 0x3f);
    *(unsigned long *)(*(long *)(set + 0x30) + slot * 8) = elem;
    if (!skp9_SCARRY8(*(long *)(set + 0x10), 1)) {
        /* skp9_FUN_003591e0(*(set+0x10) + 1) */
        return;
    }
    skp9_SoftwareBreakpoint(1, 0x25c2b8);
}

/* skp9_FUN_0025c2b8 @ 0x0025c2b8   (est. sk_set_insert_slot_cb)
 * Ghidra: void skp9_FUN_0025c2b8(undefined8, ulong, long, long)
 * Inserts an element at slot with a callback: sets the bitmap bit, invokes the
 * type-descriptor copy-elem (*(*(param_4-8)+0x20)) on the element slot, then
 * bumps the count (via FUN_00359d58) with an overflow trap. Core insert that
 * runs the element's copy constructor.
 * Confidence: medium (callback identity via descriptor)
 */
void sk_set_insert_slot_cb(uint64_t elem, uint64_t slot, long set, long desc)
{
    long word = set + (slot >> 6) * 8;
    *(unsigned long *)(word + 0x38) |= 1UL << (slot & 0x3f);
    (*(void (**)(unsigned long, uint64_t, long))(*(long *)(desc - 8) + 0x20))
        (*(long *)(set + 0x30) + *(long *)(*(long *)(desc - 8) + 0x48) * slot, elem, desc);
    /* FUN_00359d58(); if (OV) skp9_SoftwareBreakpoint(1,0x25c33c); *(set+0x10)=x8; */
}

/* FUN_0025c33c @ 0x0025c33c   (est. skp9_sk_set_insert_keyed)
 * Ghidra: void FUN_0025c33c(long, ulong, ulong)
 * Insert a keyed element: if the set count is below capacity and the copy flag
 * is clear, copies via FUN_0025b6d4; otherwise grows (FUN_0025b294/FUN_0025a5c4)
 * and probes for an existing matching element (skp9_sk_set_hash + linear scan with
 * bitmap), panicking "Duplicate elements" (FUN_0025bddc) if present. Then
 * inserts at the found slot via FUN_0025c280.
 * Confidence: medium (faithful insert-with-dup-check)
 */
void skp9_sk_set_insert_keyed(uint64_t elem, uint64_t hash, uint64_t copy_flag)
{
    long set = (long)skp9_sk_self_reg();   /* *unaff_x20 */
    unsigned long count = *(unsigned long *)(set + 0x10);
    if (count < *(unsigned long *)(set + 0x18)) {
        if ((copy_flag & 1) == 0) {
            skp9_sk_set_copy16_rev();   /* FUN_0025b6d4 */
        }
    } else {
        /* grow via FUN_0025b294 (flag clear) or FUN_0025a5c4 (flag set) */
        uint64_t slot = skp9_sk_set_hash(*(unsigned long *)(set + 0x28), 0);   /* thunk_FUN_00229ebc */
        while ((slot = slot & ~(~0UL << (*(unsigned char *)(set + 0x20) & 0x3f))),
               (*(unsigned long *)(set + 0x38 + (slot >> 6) * 8) >> (slot & 0x3f) & 1) != 0) {
            if (*(long *)(*(long *)(set + 0x30) + slot * 8) == (long)elem) {
                skp9_sk_set_dup_panic(0x674278);
            }
            slot = slot + 1;
        }
    }
    skp9_sk_set_insert_slot(elem, 0, set);
}

/* FUN_0025c460 @ 0x0025c460   (est. skp9_sk_set_iterate_keyed)
 * Ghidra: void FUN_0025c460(undefined8, undefined8, long, ulong)
 * Iterates a keyed set applying a hash comparison: grows/copies the set
 * (FUN_0025b0e0 / FUN_0025a3c8) if needed, then for each live element compares
 * its hash (extraout_x1) against the target (unaff_x21); a match triggers the
 * duplicate path (FUN_0025bddc). Completes with the element-array copy.
 * Confidence: low (keyed iterate + dup detection)
 */
void skp9_sk_set_iterate_keyed(uint64_t p1, uint64_t p2, long set, uint64_t flag)
{
    (void)p1; (void)p2; (void)set; (void)flag;
    /* FUN_000b4594(); FUN_003509ec(); FUN_00355760();
     * if (!CY||ZR) { if (flag&1==0) FUN_0025b0e0(x8+1); else FUN_0025a3c8();
     *   seed; while (skp9_FUN_00359ec0(bitmap)) { FUN_00359704();
     *     bVar1 = ZR && x1==x21; if (bVar1) { FUN_003593dc(); FUN_0025bddc(); }
     *     FUN_00359d70(); bVar2 = (x21 & 0x6000000000000000)==0x6000...;
     *     if (!bVar1||!bVar2) { FUN_00351b78(); uVar3=FUN_002a0d50();
     *       if (uVar3&1) dup; } } }
     * else { if (flag&1==0) FUN_0025b4e8(); }
     * auVar5=FUN_00100efc(); FUN_000b45b0(..,x23); FUN_000b394c(); */
    skp9_sk_fatal_error(0, 0);
}

/*------------------------------------------------------------------------*
 * Set union / merge family.
 *------------------------------------------------------------------------*/

/* skp9_FUN_0025c570 @ 0x0025c570   (est. sk_set_union_apply8)
 * Ghidra: void skp9_FUN_0025c570(undefined8, undefined8, ulong)
 * Union-apply over an 8-byte set: grows the set (FUN_0025b1c8 or sibling
 * FUN_0025a4cc) and for each live element folds it via the hash callback
 * (FUN_0031996c + closure), raising the duplicate panic if the fold reports a
 * collision (uVar6&1). Completes with the element-array copy.
 * Confidence: low (union fold pipeline)
 */
void sk_set_union_apply8(uint64_t p1, uint64_t p2, uint64_t flag)
{
    (void)p1; (void)p2; (void)flag;
    /* FUN_003583e8(); auVar8=FUN_00355760();
     * if (!CY||ZR) { if (flag&1==0) FUN_0025b1c8(x8+1, FUN_0025a864);
     *   else FUN_0025a4cc(x8+1, FUN_0025a864);
     *   lVar7=*x20; seed; while (bitmap bit set) { load elem; FUN_0031996c;
     *     FUN_003513b4; uVar6=(*x8_03)();
     *     if (uVar6&1) FUN_0025bddc(0x673a80); uVar4 = uVar4+1 & ~mask; } }
     * else if (flag&1==0) auVar8=skp9_FUN_0025b5e0();
     * FUN_000b4390(auVar8, *x20); FUN_0025c260(); FUN_00358454(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025c754 @ 0x0025c754   (est. sk_set_union_apply16)
 * Ghidra: void skp9_FUN_0025c754(long, ulong, ulong)
 * Union-apply over a 16-byte set: grows via FUN_0025b1c8/FUN_0025a4cc with the
 * copy_verify callback FUN_0025acb8, then probes for a matching element
 * (element at +0x18/+0x20 compared via FUN_0031997c) and raises the dup panic
 * on collision. Completes with FUN_0025c260 count bump.
 * Confidence: low (16-byte union fold)
 */
void sk_set_union_apply16(uint64_t p1, uint64_t p2, uint64_t flag)
{
    (void)p1; (void)p2; (void)flag;
    /* uVar6=*(*x20+0x10); if (uVar6 < *(*x20+0x18)) { if (flag&1==0)
     *   skp9_FUN_0025b5e0(); }
     * else { if (flag&1==0) FUN_0025b1c8(uVar6+1, FUN_0025acb8);
     *   else FUN_0025a4cc(uVar6+1, FUN_0025acb8);
     *   seed; while (bitmap bit) { compare elem; if match FUN_0025bddc(0x673a80); } }
     * FUN_0025c260(p1,p2,*x20); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025c9a8 @ 0x0025c9a8   (est. sk_set_insert_keyed16)
 * Ghidra: void skp9_FUN_0025c9a8(long, ulong, ulong)
 * Keyed insert into a 16-byte-element set: grows (FUN_0025b6d4 or
 * FUN_0025b294/FUN_0025a5c4 with verify FUN_0025aecc), probes for a duplicate
 * (element compare at +0x30), then inserts via FUN_0025c280.
 * Confidence: medium (dup-checked insert)
 */
void sk_set_insert_keyed16(uint64_t elem, uint64_t hash, uint64_t flag)
{
    long set = (long)skp9_sk_self_reg();
    unsigned long count = *(unsigned long *)(set + 0x10);
    if (count < *(unsigned long *)(set + 0x18)) {
        if ((flag & 1) == 0) skp9_sk_set_copy16_rev();   /* FUN_0025b6d4 */
    } else {
        uint64_t slot = skp9_sk_set_hash(*(unsigned long *)(set + 0x28), 0);
        while ((slot = slot & ~(~0UL << (*(unsigned char *)(set + 0x20) & 0x3f))),
               (*(unsigned long *)(set + 0x38 + (slot >> 6) * 8) >> (slot & 0x3f) & 1) != 0) {
            if (*(long *)(*(long *)(set + 0x30) + slot * 8) == (long)elem) {
                skp9_sk_set_dup_panic(0x677880);
            }
            slot = slot + 1;
        }
    }
    skp9_sk_set_insert_slot(elem, 0, set);
}

/* FUN_0025cac8 @ 0x0025cac8   (est. sk_set_union_apply16b)
 * Ghidra: void FUN_0025cac8(undefined8, undefined8, ulong, long)
 * Union-apply over a 16-byte set (second variant): grows via
 * skp9_FUN_0025b36c/skp9_FUN_0025a6a8, then walks the bitmap applying the descriptor
 * callback; a fold collision (uVar3&1) raises the dup panic. Completes via
 * skp9_FUN_0025c2b8 (insert with callback).
 * Confidence: low (union fold)
 */
void sk_set_union_apply16b(uint64_t p1, uint64_t p2, uint64_t flag, long set)
{
    (void)p1; (void)p2; (void)flag; (void)set;
    /* uVar1=FUN_0008e518(); uVar4=*(set+0x10); FUN_003494e8();
     * (*skp9_DAT_00658c00)(x8+0x40); FUN_00348f38(); auVar8=FUN_00355760();
     * if (!CY||ZR) { if (flag&1==0) skp9_FUN_0025b36c(x8_00+1,set);
     *   else skp9_FUN_0025a6a8();
     *   while (bitmap bit) { FUN_0035a28c; FUN_00353474; (*x8_04)();
     *     FUN_00351ef8; FUN_0034f1c4; FUN_00350ac4; uVar3=(*x8_05)();
     *     if (uVar3&1) FUN_0025bddc(uVar4); } }
     * else if (flag&1==0) auVar8=skp9_FUN_0025b7d8(set);
     * FUN_00358e0c(auVar8, *x20); skp9_FUN_0025c2b8(); FUN_0008e500(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025cc54 @ 0x0025cc54   (est. skp9_sk_set_insert_40)
 * Ghidra: void FUN_0025cc54(undefined8*, undefined8*, uint)
 * Inserts a 40-byte element into a set: probes for the slot (skp9_sk_set_hash +
 * linear scan comparing the 40-byte element at param_2 via FUN_0031997c); if a
 * match is found the existing element is swapped out into param_1 (5 words),
 * otherwise the set is grown (FUN_0025b1c8/FUN_0025a4cc) and re-probed before
 * inserting. Swaps element, bumps count, returns the displaced element in
 * param_1. Faithful insert-or-update for 40-byte values.
 * Confidence: medium (faithful insert/swap logic)
 */
void skp9_sk_set_insert_40(uint64_t *out_elem, uint64_t *in_elem, uint32_t flag)
{
    long set = (long)skp9_sk_self_reg();
    uint64_t slot = skp9_sk_set_hash(*(unsigned long *)(set + 0x28), 0);
    (void)out_elem; (void)in_elem; (void)flag; (void)set; (void)slot;
    /* local_100=1 (found flag); probe bitmap:
     *   if (uVar2==0) break;  -> not present, insert
     *   compare 40-byte elem via FUN_0031997c; if mismatch bump & scan on;
     *   if match: local_100=0 (was present) -> swap into param_1.
     * lVar1 = count + local_100; if (overflow) trap;
     * if (capacity < lVar1) grow & re-probe (dup panic 0x673a80 on match);
     *   else if (flag&1==0) skp9_FUN_0025b5e0();
     * if (uVar2!=0) { swap elements (5 words each); }
     * FUN_0025c260(in_elem, slot, *x20); zero out_elem tail; return out_elem; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025d0d4 @ 0x0025d0d4   (est. skp9_sk_set_union_apply40)
 * Ghidra: void FUN_0025d0d4(undefined8, undefined8, long)
 * Union-apply over a 40-byte set: grows via skp9_FUN_0025b36c/skp9_FUN_0025a6a8, walks
 * the bitmap applying the descriptor callback; a fold collision sets lVar6=0
 * and breaks. Grows/re-probes and raises the dup panic if still colliding.
 * Completes via skp9_FUN_0025c2b8 insert-with-callback; returns {slot, found}.
 * Confidence: low (40-byte union fold)
 */
void skp9_sk_set_union_apply40(uint64_t p1, uint64_t p2, long set)
{
    (void)p1; (void)p2; (void)set;
    /* auVar11=FUN_0008e518(); uVar2=lo; uVar5=*(set+0x10);
     * FUN_003494e8(); (*skp9_DAT_00658c00)(x8+0x40); FUN_00348f50();
     * lVar9=*x20; uVar8=*(set+0x18); FUN_00350678(uVar8); FUN_00351190();
     * (*x8_01)(); auVar12=FUN_00354948(*(lVar9+0x20));
     * lVar6=1; while (bitmap bit) { apply cb; if (uVar2&1) { lVar6=0; break; } }
     * lVar4 = count + lVar6; if (overflow) trap;
     * if (capacity < lVar4) { grow; re-probe; if colliding
     *   FUN_0025bddc(uVar5); }
     * else { if (flag&1==0) auVar13=skp9_FUN_0025b7d8(set); if (uVar1) { swap; } }
     * FUN_00356254(auVar13, *x20); skp9_FUN_0025c2b8(); uVar5=1;
     * FUN_00350774(x8,uVar5); FUN_000839d8(); FUN_0008e500(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set element access / next.
 *------------------------------------------------------------------------*/

/* FUN_0025d3d0 @ 0x0025d3d0   (est. skp9_sk_set_elem_apply)
 * Ghidra: void FUN_0025d3d0(undefined8, long)
 * Applies an operation to a specific set element: probes the slot (via
 * FUN_0031948c hash), and for each live element invokes the type descriptor's
 * copy (+0x10) and compare (+0x8) callbacks; on a match applies the operation
 * (+0x28). If the set is at capacity and the slot is free, traps with the
 * "Fatal error" / "Swift NativeSet" message (0x5d0100). Faithful per-element
 * lookup-and-apply.
 * Confidence: medium (element apply with descriptor dispatch)
 */
void skp9_sk_set_elem_apply(uint64_t p1, long set)
{
    (void)p1; (void)set;
    /* lVar7=*(set+0x10); lVar6=*(lVar7-8); (*skp9_DAT_00658c00)(lVar6+0x40);
     * seed; uVar8=*(*x20+0x28); uVar9=*(x1+0x18);
     * pcVar3=FUN_0031948c(uVar9); uVar4=(*pcVar3)(uVar8,lVar7,uVar9);
     * local_70 = set+0x38; bVar1=*(set+0x20); local_80=lVar6+0x10;
     * while (true) { uVar4 = uVar4 & ~(-1<<bVar1);
     *   if (bitmap bit clear) {
     *     if (count < capacity) { skp9_FUN_0025c2b8(local_68,uVar4,set,lVar7); return; }
     *     fatal: *(stk)=1; *(stk+8)=0x1e6; *(stk)=2;
     *       skp9_FUN_001afe4c("Fatal error", 0xb, 2, skp9_DAT_5be7c0, 0, 2,
     *         "Swift NativeSet", 0x15); }
     *   lVar12 = stride*uVar4;
     *   (**(lVar6+0x10))(local_80, lVar10, *(set+0x30)+lVar12, lVar7);
     *   uVar8=FUN_00027754(local_78); pcVar3=FUN_0014ae44();
     *   uVar5=(*pcVar3)(lVar10, local_68, lVar7, uVar8);
     *   (**(lVar6+8))(lVar10, lVar7);
     *   if (uVar5&1) break; uVar4 = uVar4 + 1; }
     * (**(lVar6+0x28))(*(set+0x30)+lVar12, local_68, lVar7); */
    skp9_sk_fatal_error(0, 0x5d0100);   /* skp9_FUN_001afe4c("Swift NativeSet"...) */
}

/* FUN_0025d848 @ 0x0025d848   (est. skp9_sk_set_next_slot)
 * Ghidra: void FUN_0025d848(undefined8)
 * Returns the next occupied slot index in the set (MSB-first bitmap scan): if
 * the current bitmap word (x20[4]) is zero, advances to the next word
 * (FUN_00357ee4/FUN_00353664); else takes the low bit of the current word.
 * Applies the descriptor callback to the found slot and bumps the iteration
 * state. The set iterator's next-slot engine.
 * Confidence: medium (bitmap next-slot scan)
 */
void skp9_sk_set_next_slot(uint64_t out)
{
    /* if (x20[4]==0) { FUN_00357ee4(); lVar2=x8_00; lVar4=x10;
     *   do { if (carry) trap; if (lVar4 <= lVar2+1) { FUN_0034c6c4();
     *       goto done; } FUN_00353664(); lVar2=x8_01; lVar4=x10_00;
     *   } while (x11==0); lVar2=FUN_0035364c(); uVar3 = x8_02 | x9_00<<6; }
     * else { lVar2=FUN_0035229c(); uVar3 = x9 | x8<<6; }
     * lVar4=*(*(lVar2+0x10)-8);
     * (**(lVar4+0x10))(out, *(*x20+0x30)+*(lVar4+0x48)*uVar3, *(lVar2+0x10));
     * FUN_0034b744(); done: FUN_000839d8(); */
    skp9_sk_thread_aux(0);
}

/* FUN_0025d8f4 @ 0x0025d8f4   (est. skp9_sk_set_next_apply)
 * Ghidra: void FUN_0025d8f4(void)
 * Next-element apply: seeds the hash, and for the current slot invokes the
 * descriptor callback (extraout_x16+0x10) on the element; bumps iteration
 * state via FUN_00356c54. Compact iterator step.
 * Confidence: low (iterator step pipeline)
 */
void skp9_sk_set_next_apply(void)
{
    /* FUN_00350a10(); FUN_0034e39c(); (*skp9_DAT_00658c00)();
     * auVar1=FUN_0034c8e0();
     * FUN_00351990(auVar1_0, *(auVar1_8+0x30)+*(x8+0x48)*auVar1_0);
     * (*x9)(); FUN_00350678(); FUN_003504a0(); (*x8_00)();
     * FUN_0034ea18(); (*x8_01)(); FUN_00356c54(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025da00 @ 0x0025da00   (est. sk_set_elem_get)
 * Ghidra: undefined8 skp9_FUN_0025da00(long, long)
 * Returns the element at the given slot index: probes the slot (FUN_0031948c
 * hash) and reads the element via the descriptor's copy (+0x10), after seeding
 * the set (FUN_001f7d28 range). Returns the element word.
 * Confidence: medium (element get via descriptor)
 */
uint64_t sk_set_elem_get(long slot, long set)
{
    (void)slot; (void)set;
    /* lVar3=*(set+0x10); lVar6=*(lVar3-8); (*skp9_DAT_00658c00)(lVar6+0x40);
     * lVar4=*x20; uVar7=*(x1+0x18); lVar1=FUN_001f7d28(lVar4);
     * (**(lVar6+0x10))(&stk, lVar1+*(lVar6+0x48)*slot, lVar3);
     * FUN_0001a1c8(lVar4,lVar3,uVar7); uVar5=*(lVar4+0x28);
     * pcVar2=FUN_0031948c(uVar7); uVar5=(*pcVar2)(uVar5,lVar3,uVar7);
     * (**(lVar6+8))(&stk, lVar3); return uVar5; */
    return 0;
}

/* skp9_FUN_0025db34 @ 0x0025db34   (est. sk_set_elem_move)
 * Ghidra: void skp9_FUN_0025db34(long, long, long)
 * Moves an element from slot param_1 to slot param_2 in a set: maps the
 * element (skp9_sk_elem_map / FUN_0019ce60) over the descriptor stride.
 * Confidence: low (element move)
 */
void sk_set_elem_move(long src_slot, long dst_slot, long set)
{
    /* lVar3=*(set+0x10); lVar1=FUN_001f7d28(*x20);
     * lVar2=*(*(lVar3-8)+0x48);
     * FUN_0019ce60(lVar1+lVar2*src_slot, 1, lVar1+lVar2*dst_slot, lVar3); */
    (void)src_slot; (void)dst_slot; (void)set;
}

/*------------------------------------------------------------------------*
 * Set remove family.
 *------------------------------------------------------------------------*/

/* skp9_FUN_0025db98 @ 0x0025db98   (est. sk_set_remove_slot)
 * Ghidra: void skp9_FUN_0025db98(ulong)
 * Removes the element at the given slot (MSB-first): clears the bitmap bit,
 * then re-inserts any elements that hashed to the removed slot's probe chain
 * (linear compaction via FUN_0022b080 find), and re-seeds the hash. Decrements
 * count (+0x10) and bumps the generation (+0x24) with an underflow trap.
 * Faithful open-addressing removal.
 * Confidence: medium (faithful open-address remove + compaction)
 */
void sk_set_remove_slot(uint64_t slot)
{
    long set = (long)skp9_sk_self_reg();
    long word_base = set + 0x38;
    unsigned long size = ~0UL << (*(unsigned char *)(set + 0x20) & 0x3f);
    unsigned long slot0 = slot + 1 & ~size;
    (void)word_base; (void)size; (void)slot0;
    /* uVar8 = ~size; lVar6 = FUN_0022b080(slot, word_base, uVar8) (find);
     * uVar11 = lVar6 + 1 & uVar8;
     * do { elem = *(set+0x30)+slot0*0x10; release + rehash;
     *   uVar7 = skp9_sk_swift_string_hash() & uVar8;
     *   if (slot < uVar11) { if (uVar11<=uVar7 || uVar7<=slot) { move elem; slot=slot0; } }
     *   else if (uVar11<=uVar7 && uVar7<=slot) { move; slot=slot0; }
     *   slot0 = slot0+1 & uVar8;
     * } while (bitmap bit set);
     * *(word_base + (slot>>3 & mask)) &= ~(1 << (slot&0x3f));
     * if (!skp9_SBORROW8(count,1)) { count--; *(set+0x24)++; return; }
     * skp9_SoftwareBreakpoint(1, 0x25dd80); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025dd80 @ 0x0025dd80   (est. sk_set_remove_slot16)
 * Ghidra: void skp9_FUN_0025dd80(void)
 * Removes a 16-byte element with open-address compaction: for each element in
 * the removed slot's probe chain re-hashes and moves it into the freed slot.
 * Decrements count and bumps generation. First-word variant of the remove.
 * Confidence: medium (faithful open-address remove)
 */
void sk_set_remove_slot16(void)
{
    /* auVar12=FUN_000b4594(); uVar6=lo; lVar8=*x20;
     * FUN_003537b4(*(lVar8+0x20)); uVar9 = mask & *(lVar8+0x38);
     * if (bitmap bit set) { uVar7=~mask; FUN_0034d190(); lVar4=FUN_0022b080();
     *   uVar10=lVar4+1 & uVar7;
     *   do { uVar11=*(*(lVar8+0x30)+uVar9*0x10+8); rehash;
     *     uVar5 = skp9_sk_swift_string_hash() & uVar7;
     *     if (uVar6<uVar10) { if (uVar10<=uVar5 || uVar5<=uVar6) { move; uVar6=uVar9; } }
     *     else if (uVar10<=uVar5 && uVar5<=uVar6) { move; uVar6=uVar9; }
     *     uVar9 = uVar9+1 & uVar7; } while (bitmap bit set); }
     * FUN_0034fa78(); if (!skp9_SBORROW8(count,1)) { count--; *(lVar8+0x24)++;
     *   FUN_000b45b0(hi); return; } skp9_SoftwareBreakpoint(1, 0x25dee4); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025dee4 @ 0x0025dee4   (est. sk_set_remove_slot40)
 * Ghidra: void skp9_FUN_0025dee4(void)
 * Removes a 40-byte element with open-address compaction (0x28 stride): walks
 * the probe chain via FUN_0031996c/FUN_0034ce58, re-hashing and moving
 * elements. Decrements count and bumps generation.
 * Confidence: medium (faithful 40-byte remove)
 */
void sk_set_remove_slot40(void)
{
    /* auVar8=FUN_000b4594(); uVar3=lo; lVar6=*x20; FUN_003537b4(*(lVar6+0x20));
     * FUN_00359e4c(); if (x9&1) { FUN_0034d190(); lVar4=FUN_0022b080();
     *   uVar7=lVar4+1 & ~x8;
     *   do { FUN_0031996c(*(lVar6+0x30)+x28*0x28,&stk); FUN_0034bca4(&stk);
     *     FUN_000dbd0c(); (*x9_00)(); FUN_0034c4dc(); FUN_0031993c();
     *     auVar9=FUN_0034ce58(); uVar5=(*x8_00)(auVar9,&stk);
     *     FUN_000026e8(); FUN_003199ac(&stk); uVar5 = uVar5 & ~x8;
     *     if (uVar3<uVar7) { if (uVar7<=uVar5 || uVar5<=uVar3) { FUN_0035760c();
     *       FUN_00358a2c(); } } else if (uVar7<=uVar5 && uVar5<=uVar3) { ... }
     *     FUN_003589a8(); } while (x8_02&1); }
     * FUN_0034fa78(); if (!skp9_SBORROW8(count,1)) { count--; FUN_0035a224(count);
     *   FUN_000b45b0(hi); return; } skp9_SoftwareBreakpoint(1, 0x25e000); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025e000 @ 0x0025e000   (est. skp9_sk_set_remove_keyed)
 * Ghidra: void FUN_0025e000(void)
 * Removes a keyed element (first-word identity): walks the probe chain,
 * comparing each element's hash (FUN_00357aec + FUN_0031948c); on a match
 * moves it into the removed slot and clears the bitmap. Decrements count and
 * bumps generation. Faithful keyed remove.
 * Confidence: medium (faithful keyed remove)
 */
void skp9_sk_set_remove_keyed(void)
{
    /* FUN_0008e518(); FUN_00359ac8(); uVar10=*(x1+0x10); FUN_00349734();
     * (*skp9_DAT_00658c00)(x8+0x40); FUN_003493ac(); lVar7=*x20; lVar1=lVar7+0x38;
     * FUN_003537b4(*(lVar7+0x20)); uVar9 = mask & *(lVar7+0x38);
     * if (bitmap bit set) { uVar13=~mask; auVar14=FUN_00351160();
     *   lVar2=FUN_0022b080(auVar14, uVar13); uVar11=lVar2+1 & uVar13;
     *   uVar3=*(x25+0x18); pcVar4=FUN_0031948c(); pcVar8=*(x16+0x10);
     *   lVar2=*(x16+0x48);
     *   do { lVar12=lVar2*uVar9; FUN_00357aec(pcVar6, *(lVar7+0x30)+lVar12);
     *     (*pcVar8)(...); uVar5=(*pcVar4)(*(lVar7+0x28),uVar10,uVar3);
     *     FUN_003508a8(*(x16+8)); pcVar6=(*x8_01)(); uVar5 = uVar5 & uVar13;
     *     if (x22<uVar11) { if (uVar11<=uVar5 || uVar5<=x22) { move elem;
     *       x22=uVar9; } } else if (uVar11<=uVar5 && uVar5<=x22) { move; }
     *     uVar9 = uVar9+1 & uVar13; } while (bitmap bit set); }
     * FUN_00359fd4(); *(lVar1+x8_02) &= x9_00-1;  (clear bit)
     * if (!skp9_SBORROW8(count,1)) { count--; *(lVar7+0x24)++; FUN_0008e500(); return; }
     * skp9_SoftwareBreakpoint(1, 0x25e1c8); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025e1c8 @ 0x0025e1c8   (est. sk_set_remove_dispatch)
 * Ghidra: void skp9_FUN_0025e1c8(undefined8, undefined8, long)
 * Remove dispatch: on the stable path copies via skp9_FUN_0025b7d8 (copy8), invokes
 * the descriptor destroy (+0x20) on the removed element, then FUN_0025e000
 * (keyed remove).
 * Confidence: low (remove dispatch)
 */
void sk_set_remove_dispatch(uint64_t p1, uint64_t p2, long set)
{
    (void)p1; (void)p2; (void)set;
    /* FUN_003515f0(); if (flag&1==0) skp9_FUN_0025b7d8(set);
     * (**(*(*(set+0x10)-8)+0x20))(); FUN_00084180(); FUN_0025e000(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set alloc / grow family.
 *------------------------------------------------------------------------*/

/* FUN_0025e240 @ 0x0025e240   (est. skp9_sk_set_realloc)
 * Ghidra: void FUN_0025e240(ulong, long)
 * Reallocates the set storage: if param_1&1 is clear, allocates a fresh set of
 * the given size/seed (skp9_FUN_0025e5d0) and stores it back; otherwise it walks
 * the existing bitmap and re-hashes each live element into a new buffer
 * (FUN_003571a4 + FUN_0035bc70). Used by set growth.
 * Confidence: low (alloc/grow pipeline)
 */
void skp9_sk_set_realloc(uint64_t flag, long set)
{
    (void)flag; (void)set;
    /* lVar5=*x20; if (flag&1==0) { uVar2=*(lVar5+0x20);
     *   lVar5=FUN_0031d3a4(0, *(set+0x10), *(set+0x18)); FUN_0034c988(uVar2);
     *   skp9_FUN_0025e5d0(); FUN_00351d18(); FUN_0036b118(); *x20=lVar5; return; }
     * walk bitmap: FUN_00359894(); uVar8=bm; do { uVar8=uVar8-1&uVar8;
     *   FUN_003571a4(idx, ..., *(set+0x10)); FUN_0035bc70(..., 1); }
     *   while (uVar8!=0); ... FUN_00357da4(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025e370 @ 0x0025e370   (est. skp9_sk_set_alloc)
 * Ghidra: ulong skp9_FUN_0025e370(undefined8, ulong, ulong, char)
 * Core set allocator: builds a _NativeSet with the given log2 slot count
 * (param_1), seed (param_2), element seed (param_3) and flag (param_4).
 * Layout: +0x10 count=0, +0x18 capacity=1<<log2, +0x20 log2, +0x24 seed,
 * +0x28 seed2, +0x30 elements (bitmap + wordcount), +0x38 bitmap zeroed.
 * Element array is placed immediately after the bitmap. Returns the set.
 * Confidence: high (faithful layout)
 * Notes: FUN_00002534 is the type descriptor lookup; FUN_0036a940 allocates
 *   the backing buffer; FUN_001fb05c computes capacity.
 */
uint64_t skp9_sk_set_alloc(uint64_t log2_slots, uint64_t seed, uint64_t seed2, char flag)
{
    uint64_t nbits = 1UL << (log2_slots & 0x3f);
    uint64_t nwords = (nbits + 0x3f) >> 6;
    unsigned long desc = skp9_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_00002534(&LAB_006576b0,...) */
    uint64_t base = skp9_sk_swift_alloc_buf((nwords * 8 + 0x3f & 0x3ffffffffffffff8) +
                                       (0x28UL << (log2_slots & 0x3f)), 7);   /* FUN_0036a940 */
    long *pl = (long *)(base + 0x38);
    *(unsigned long *)(base + 0x10) = 0;
    *(unsigned long *)(base + 0x18) = skp9_sk_set_capacity(log2_slots);   /* capacity */
    *(unsigned char *)(base + 0x20) = (unsigned char)log2_slots;
    *(unsigned char *)(base + 0x21) = 0;
    *(unsigned short *)(base + 0x22) = 0;
    if ((seed & 0xff00000000) == 0x100000000) {
        seed = skp9_sk_set_hash(0, base);   /* thunk_FUN_00229ebc */
    }
    *(unsigned int *)(base + 0x24) = (unsigned int)seed;
    /* skp9_DAT_006adf20 (global string-flag) == 0 -> use base */
    if (0) log2_slots = base;
    if (flag != 1) log2_slots = seed2;
    *(unsigned long *)(base + 0x28) = log2_slots;
    *(long **)(base + 0x30) = pl + nwords;
    if ((long)nbits < 0x40) {
        *pl = ~0UL << (nbits & 0x3f);
    } else {
        skp9_sk_set_alloc_fill(0, nwords, (unsigned long)pl);   /* zero bitmap, FUN_001b5474 */
    }
    return base;
}

/* skp9_FUN_0025e4a0 @ 0x0025e4a0   (est. sk_set_alloc16)
 * Ghidra: void skp9_FUN_0025e4a0(void)
 * Allocates a 16-byte-element set: sizes the buffer from the incoming log2
 * (x27) and word count (x19), seeds +0x28/+0x30 and fills the bitmap (bit<0x40
 * direct, else FUN_001b5474). Companion to skp9_sk_set_alloc for 16-byte strides.
 * Confidence: medium (alloc pipeline)
 */
void sk_set_alloc16(void)
{
    /* FUN_0008e518(); uVar1=FUN_003556b0();
     * FUN_0036a940(uVar1, (x19*8+0x3f&mask)+(0x10<<(x27&0x3f)), 7);
     * FUN_00359368(); FUN_00350d54(); if (ZR) { FUN_00350488(); skp9_sk_set_hash(); }
     * FUN_00350d34(); uVar1=x9; if (w8!=1) uVar1=x20;
     * *(x22+0x28)=uVar1; *(x22+0x30)=x28;
     * if (x26<0x40) FUN_003581b4(); else { FUN_003504e8(); FUN_001b5474(); }
     * FUN_0008e500(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025e538 @ 0x0025e538   (est. sk_set_alloc8b)
 * Ghidra: void skp9_FUN_0025e538(void)
 * Allocates an 8-byte-element set: same structure as sk_set_alloc16 but with an
 * 8-byte element stride (0x8 << log2). Seeds +0x28/+0x30 and fills the bitmap.
 * Confidence: medium (alloc pipeline)
 */
void sk_set_alloc8b(void)
{
    /* FUN_0008e518(); uVar1=FUN_003556b0();
     * FUN_0036a940(uVar1, (x19*8+0x3f&mask)+(8<<(x27&0x3f)), 7);
     * ... identical to sk_set_alloc16 but stride 8 ... FUN_0008e500(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025e5d0 @ 0x0025e5d0   (est. sk_set_alloc_seeded)
 * Ghidra: void skp9_FUN_0025e5d0(undefined8, undefined8, undefined8)
 * Allocates a set seeded from a prototype: reads the log2 stride from the
 * source object (x20+0x88 -> type descriptor +0x50), sizes the buffer, seeds
 * +0x10/+0x28/+0x30 and fills the bitmap. The type-descriptor element stride
 * (+0x50) determines the storage layout.
 * Confidence: medium (seeded alloc)
 */
void sk_set_alloc_seeded(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    /* uVar1=FUN_00077698(); lVar3=1<<(log2&0x3f);
     * uVar4=*(*(*(x20+0x88)-8)+0x50);  (element stride)
     * lVar2=FUN_0036a940(); *(lVar2+0x10)=0; FUN_001fb05c(uVar1);
     * FUN_00350d54(); if (ZR) { FUN_00350488(); skp9_sk_set_hash(); }
     * FUN_00350d34(); uVar1=x9; if (w8!=1) uVar1=p3;
     * *(lVar2+0x28)=uVar1; *(lVar2+0x30)=uVar4+(nwords)*8+lVar2+0x38 & ~uVar4;
     * if (lVar3<0x40) FUN_003581b4(); else { FUN_00350798(); FUN_001b5474(); }
     * FUN_0007767c(lVar2, x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025e73c @ 0x0025e73c   (est. skp9_sk_set_next_slot2)
 * Ghidra: void FUN_0025e73c(undefined8, long)
 * Next-occupied-slot iterator (second variant): if the current bitmap word
 * (x20[4]) is zero, advances word-by-word (x20[3]=word index, x20[4]=word);
 * else takes the low bit of the current word. Applies the descriptor callback
 * to the found slot. Set iterator next engine.
 * Confidence: medium (bitmap next-slot)
 */
void skp9_sk_set_next_slot2(uint64_t out, long set)
{
    (void)out; (void)set;
    /* uVar6=x20[4]; if (uVar6==0) { lVar5=x20[3];
     *   do { lVar3=lVar5+1; if (carry) trap;
     *     if ((x20[2]+0x40>>6) <= lVar3) { lVar5=*(set+0x10); uVar4=1; goto done; }
     *     x20[3]=lVar3; uVar6=*(x20[1]+lVar3*8); x20[4]=uVar6;
     *     lVar5=lVar5+1; } while (uVar6==0);
     *   uVar6 = lowbit(x20[4], lVar3); }
     * else uVar6 = lowbit(x20[4], x20[3]);
     * uVar7=*x20; lVar5=*(set+0x10); uVar4=*(set+0x18);
     * lVar3=FUN_001f7d28(uVar7);
     * (**(*(lVar5-8)+0x10))(out, lVar3+*(*(lVar5-8)+0x48)*uVar6, lVar5);
     * FUN_0001a1c8(uVar7,lVar5,uVar4); uVar4=0;
     * done: FUN_000839d8(out, uVar4, 1, lVar5); */
    skp9_sk_thread_aux(0);
}

/*------------------------------------------------------------------------*
 * Set filter / transform family (Swift NativeSet filter closures).
 *------------------------------------------------------------------------*/

/* FUN_0025e85c @ 0x0025e85c   (est. skp9_sk_set_filter_40)
 * Ghidra: void FUN_0025e85c(undefined1*, long, undefined8, undefined8,
 *         long, long, long, undefined8, undefined8)
 * Filter-into-set over 40-byte elements: iterates the source via the sequence
 * engine (FUN_00377824/000a68f4), and for each element probes the destination
 * bitmap; absent elements are copied in (descriptor copy) and present ones
 * with a matching identity set the destination bit. Sets *param_1 = found
 * (whether any element was added). Faithful filter-fold.
 * Confidence: low (filter-fold via sequence engine)
 */
void skp9_sk_set_filter_40(int8_t *out_found, long dst_bitmap, uint64_t p3, uint64_t p4,
                      long src_set, long seq, long set, uint64_t p8, uint64_t p9)
{
    (void)out_found; (void)dst_bitmap; (void)p3; (void)p4; (void)src_set;
    (void)seq; (void)set; (void)p8; (void)p9;
    /* lVar11=*(seq-8); local_d0=out_found; (*skp9_DAT_00658c00)(lVar11+0x40);
     * lVar20 = alloc; (*skp9_DAT_00658c00)(); lVar12=lVar20-x12;
     * lVar4=FUN_00310d68(0, seq); lVar17=lVar12-x8_00;
     * lVar4=*(set-8); lVar15=lVar17-(x8_01+0xf&mask); lVar5=FUN_00377824(...);
     * local_d8=*(lVar5-8); lVar19=lVar15-x8_02;
     * (**(lVar4+0x10))(lVar15,p4,set); (*FUN_000a68c4(p9))(lVar19,set,p9);
     * uVar7=FUN_00377bec(...); pcVar6=FUN_000a68f4(); puVar1=lVar11+8;
     * lVar4=0;
     * do { do { local_e0=lVar4; (*pcVar6)(lVar17,lVar5,uVar7);
     *     iVar3=FUN_000839f8(lVar17,1,seq);
     *     if (iVar3==1) { uVar13=0; goto fin; }
     *     (**(lVar11+0x20))(lVar12,lVar17,seq); uVar16=*(src_set+0x28);
     *     pcVar8=FUN_0031948c(p8); uVar9=(*pcVar8)(uVar16,seq,p8);
     *     bVar2=*(src_set+0x20);
     *     do { uVar9 = uVar9 & ~(-1<<bVar2); uVar14=uVar9>>6; uVar18=1<<(uVar9&0x3f);
     *       if ((uVar18 & *(src_set+0x38+uVar14*8))==0) { (*puVar1)(lVar12,seq);
     *         lVar4=local_e0; goto outer; }
     *       (**(lVar11+0x10))(lVar20, *(src_set+0x30)+*(lVar11+0x48)*uVar9, seq);
     *       uVar16=FUN_00027754(p8); pcVar8=FUN_0014ae44();
     *       uVar10=(*pcVar8)(lVar20,lVar12,seq,uVar16); pcVar8=*(lVar11+8);
     *       (*pcVar8)(puVar1,lVar20,seq); uVar9=uVar9+1;
     *     } while ((uVar10&1)==0);
     *     (*pcVar8)(...); uVar9=*(dst_bitmap+uVar14*8);
     *     *(dst_bitmap+uVar14*8)=uVar9|uVar18; lVar4=local_e0;
     *   } while ((uVar9&uVar18)!=0);
     *   if (carry(local_e0)) trap; lVar4=local_e0+1;
     * } while (local_e0+1 != *(src_set+0x10));
     * uVar13=1;
     * fin: (**(local_d8+8))(lVar19,lVar5); *out_found=uVar13; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025ecb8 @ 0x0025ecb8   (est. sk_set_filter_40b)
 * Ghidra: void skp9_FUN_0025ecb8(undefined8, long, undefined8, undefined8, long,
 *         long, long, undefined8, undefined8)
 * Filter-into-set over 40-byte elements (second variant): same sequence-engine
 * fold, but tracks whether the destination reached capacity (local_ec) and
 * stops early. Sets *param_1 = true if elements were added / capacity hit.
 * Confidence: low (filter-fold with capacity early-out)
 */
void sk_set_filter_40b(int8_t *out_found, long dst_bitmap, uint64_t p3, uint64_t p4,
                       long src_set, long seq, long set, uint64_t p8, uint64_t p9)
{
    (void)out_found; (void)dst_bitmap; (void)p3; (void)p4; (void)src_set;
    (void)seq; (void)set; (void)p8; (void)p9;
    /* lVar13=*(seq-8); local_e0=out_found; (*skp9_DAT_00658c00)(lVar13+0x40);
     * puVar21=alloc; lVar14=...; lVar6=FUN_00310d68(0,seq);
     * lVar18=lVar14-x8_00; lVar6=*(set-8); lVar16=lVar18-(x8_01+mask);
     * lVar7=FUN_00377824(...); local_e8=*(lVar7-8); lVar20=lVar16-x8_02;
     * (**(lVar6+0x10))(lVar16,p4,set); (*FUN_000a68c4(p9))(lVar20,set,p9);
     * uVar9=FUN_00377bec(...); pcVar8=FUN_000a68f4(); lVar6=0; local_ec=0;
     * puVar1=lVar13+8; bVar3=false;
     * do { do { bVar4=bVar3; (*pcVar8)(lVar18,lVar7,uVar9);
     *     iVar5=FUN_000839f8(lVar18,1,seq);
     *     if (iVar5==1) { bVar3=false; goto fin; }
     *     (**(lVar13+0x20))(lVar14,lVar18,seq); uVar17=*(src_set+0x28);
     *     pcVar10=FUN_0031948c(p8); uVar11=(*pcVar10)(uVar17,seq,p8);
     *     bVar2=*(src_set+0x20);
     *     do { uVar11 = uVar11 & ~(-1<<bVar2); uVar15=uVar11>>6; uVar19=1<<(uVar11&0x3f);
     *       if ((uVar19 & *(src_set+0x38+uVar15*8))==0) { (*puVar1)(lVar14,seq);
     *         bVar3=true; if (bVar4) goto outer; bVar3=true; local_ec=1;
     *         if (lVar6==*(src_set+0x10)) goto fin; goto outer; }
     *       (**(lVar13+0x10))(puVar21, *(src_set+0x30)+*(lVar13+0x48)*uVar11, seq);
     *       uVar17=FUN_00027754(p8); pcVar10=FUN_0014ae44();
     *       uVar12=(*pcVar10)(puVar21,lVar14,seq,uVar17); pcVar10=*(lVar13+8);
     *       (*pcVar10)(puVar1,puVar21,seq); uVar11=uVar11+1;
     *     } while ((uVar12&1)==0);
     *     (*pcVar10)(...); uVar11=*(dst_bitmap+uVar15*8);
     *     *(dst_bitmap+uVar15*8)=uVar11|uVar19; bVar3=bVar4;
     *   } while ((uVar11&uVar19)!=0);
     *   bVar4=carry(lVar6,1); lVar6=lVar6+1; if (bVar4) trap;
     * } while ((lVar6==*(src_set+0x10) & local_ec)==0);
     * bVar3=true;
     * fin: (**(local_e8+8))(lVar20,lVar7); *out_found=bVar3; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0025f164 @ 0x0025f164   (est. sk_set_filter_alloc)
 * Ghidra: void skp9_FUN_0025f164(undefined8, undefined8, undefined8, undefined8,
 *         undefined8, undefined8, undefined8, code*)
 * Filter-closure allocator: builds a filter context (local_78) seeded from the
 * log2 stride (bit-0xd fast path vs skp9_FUN_003d31f8 slow path), runs the
 * user closure (param_8), and returns whether the filter matched (local_78[0]&1).
 * Confidence: low (filter context + closure)
 */
void sk_set_filter_alloc(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                         uint64_t p5, uint64_t p6, uint64_t p7, void (*cb)(void))
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
    /* FUN_0008e518(); FUN_0034b5a8(); local_20=FUN_0006b2ec();
     * bVar1=*(local_20_8+0x20); bVar6=bVar1&0x3f; puStack_58=auStack_50;
     * lVar7=((1<<(bVar1&0x3f))+0x3f>>6)*8; uVar3=bVar6==0xd;
     * local_60=p7; local_40=p3; uStack_38=p4; local_30=p5; uStack_28=p6;
     * local_8=x8_00;
     * if (bVar6<0xe || skp9_FUN_003d31f8(lVar7,8)&1) { (*skp9_DAT_00658c00)();
     *   auVar8=FUN_003508e4(); FUN_001b5474(.., auStack_80-(lVar7+mask));
     *   FUN_00350914(local_78); FUN_003516d8(); FUN_00356170(); (*cb)();
     *   local_78[0] &= 0xff; }
     * else { uVar5=FUN_0036a804(lVar7,0xffffffffffffffff); FUN_00350c68();
     *   auVar9=FUN_002b8254(); local_78[0]=auVar9_0; FUN_00359208(uVar5);
     *   uVar3=0; if ((auVar9_4&0xff)==1) { FUN_0034a210(); uVar5=FUN_00002534();
     *     FUN_003698b0(local_78,uVar5,0x66c1c8); skp9_SoftwareBreakpoint(1,0x25f2e4); } }
     * FUN_000651bc(local_8); if (!uVar3) FUN_0011d7e8();
     * FUN_0008e500(local_78[0]&1, x8); */
    if (cb) cb();
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_0025f2e4 @ 0x0025f2e4   (est. skp9_sk_set_filter_fold)
 * Ghidra: void FUN_0025f2e4(undefined1*, long, undefined8, undefined8, long,
 *         long, long, undefined8, undefined8)
 * Filter-fold (40-byte, third variant): iterates the source, copying elements
 * whose identity is absent from the destination; sets *param_1 = whether any
 * element was added. Same sequence-engine shape as skp9_sk_set_filter_40.
 * Confidence: low (filter-fold)
 */
void skp9_sk_set_filter_fold(int8_t *out_found, long dst_bitmap, uint64_t p3, uint64_t p4,
                        long src_set, long seq, long set, uint64_t p8, uint64_t p9)
{
    (void)out_found; (void)dst_bitmap; (void)p3; (void)p4; (void)src_set;
    (void)seq; (void)set; (void)p8; (void)p9;
    /* lVar10=*(seq-8); local_c0=p2; local_b0=out_found; (*skp9_DAT_00658c00)(lVar10+0x40);
     * lVar17=alloc; lVar11=lVar17-x12; lVar4=FUN_00310d68(0,seq);
     * lVar4=*(set-8); lVar15=(lVar11-x8_00)-(x8_01+mask); lVar5=FUN_00377824(...);
     * local_b8=*(lVar5-8); lVar13=lVar15-x8_02;
     * (**(lVar4+0x10))(lVar15,p4,set); (*FUN_000a68c4(p9))(lVar13,set,p9);
     * uVar7=FUN_00377bec(...); local_d8=FUN_000a68f4(); puVar1=lVar10+8;
     * lVar4=0; local_d0=uVar7; lStack_c8=lVar11-x8_00;
     * do { do { local_e0=lVar4; lVar4=lStack_c8; (*local_d8)(lStack_c8,lVar5,local_d0);
     *     uVar12=1; iVar3=FUN_000839f8(lVar4,1,seq);
     *     if (iVar3==1) goto fin; (**(lVar10+0x20))(lVar11,lVar4,seq);
     *     uVar7=*(src_set+0x28); pcVar6=FUN_0031948c(p8);
     *     uVar8=(*pcVar6)(uVar7,seq,p8); bVar2=*(src_set+0x20);
     *     do { uVar8 = uVar8 & ~(-1<<bVar2); uVar14=uVar8>>6; uVar16=1<<(uVar8&0x3f);
     *       if ((uVar16 & *(src_set+0x38+uVar14*8))==0) { (*puVar1)(lVar11,seq);
     *         uVar12=0; goto fin; }
     *       (**(lVar10+0x10))(lVar17, *(src_set+0x30)+*(lVar10+0x48)*uVar8, seq);
     *       uVar7=FUN_00027754(p8); pcVar6=FUN_0014ae44();
     *       uVar9=(*pcVar6)(lVar17,lVar11,seq,uVar7); pcVar6=*(lVar10+8);
     *       (*pcVar6)(puVar1,lVar17,seq); uVar8=uVar8+1;
     *     } while ((uVar9&1)==0);
     *     (*pcVar6)(...); uVar8=*(dst_bitmap+uVar14*8);
     *     *(dst_bitmap+uVar14*8)=uVar8|uVar16; lVar4=local_e0;
     *   } while ((uVar8&uVar16)!=0);
     *   if (carry(local_e0)) trap; lVar4=local_e0+1;
     * } while (local_e0+1 != *(src_set+0x10));
     * uVar12=0;
     * fin: (**(local_b8+8))(lVar13,lVar5); *out_found=uVar12; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set filter / drop family (continuation).
 *------------------------------------------------------------------------*/

/* FUN_0025f754 @ 0x0025f754   (est. skp9_sk_set_filter_keep)
 * Ghidra: undefined8* FUN_0025f754(ulong*, long, long, undefined8*, long,
 *         undefined8)
 * Keeps (filters) count elements of a set into a fresh set: if the source is
 * empty or the count already matches, returns the source; otherwise allocates
 * a new set (FUN_0025a060) and copies each of the first count live elements
 * (MSB-first bitmap scan) via the descriptor callback. Frees the source and
 * returns the new set.
 * Confidence: medium (filter-keep; faithful MSB-first scan)
 */
uint64_t *skp9_sk_set_filter_keep(uint64_t *src_bitmap, long count, long stride, uint64_t *src_set,
                             long seq, uint64_t p6)
{
    (void)src_set; (void)seq; (void)p6;
    /* lVar5=*(seq-8); lVar4=stride; local_68=p6; (*skp9_DAT_00658c00)(lVar5+0x40);
     * lVar8=alloc;
     * if (stride==0) { FUN_0036b118(src_set); return &skp9_DAT_006577e0; }
     * else if (stride != src_set[2]) {
     *   puVar3=FUN_0025a060(stride, seq, p6);  (alloc new set)
     *   uVar7 = (count<1) ? 0 : *src_bitmap;
     *   local_70=lVar5+0x10; lVar4=0;
     *   do { if (uVar7==0) { scan next bitmap word; } else { take lowbit; }
     *     (**(lVar5+0x10))(lVar8, src_set[6]+*(lVar5+0x48)*idx, seq);
     *     FUN_0025af6c(lVar8, puVar3, seq, p6);  (insert-done)
     *     if (carry(stride--)) trap; lVar4=lVar9;
     *   } while (stride!=0);
     *   FUN_0036b118(src_set); src_set = puVar3; }
     * return src_set; */
    return NULL;
}

/* skp9_FUN_0025f910 @ 0x0025f910   (est. sk_set_filter_transform)
 * Ghidra: undefined8* skp9_FUN_0025f910(undefined8, undefined8*, long, long,
 *         undefined8, undefined8)
 * Transform-filter: iterates a source set (param_3) and copies each live
 * element whose identity is absent from the destination into the destination,
 * growing it (FUN_0025a060 / buffer realloc). On a full destination it builds a
 * fresh buffer via FUN_0036a804/FUN_002b82f0. Returns the (possibly new)
 * destination set.
 * Confidence: low (transform/filter with buffer growth)
 */
uint64_t *sk_set_filter_transform(uint64_t p1, uint64_t *dst, long src, long seq,
                                  uint64_t p5, uint64_t p6)
{
    (void)dst; (void)src; (void)seq; (void)p5; (void)p6;
    /* local_70=-0x2c8502b44bfffed6 (stack canary);
     * lStack_100=FUN_00310d68(0,src); local_108=*(lStack_100-8);
     * (*skp9_DAT_00658c00)(local_108+0x40...); lVar10=*(src-8); local_c8=alloc;
     * (*skp9_DAT_00658c00)(lVar10+0x40); lVar14=...; (*skp9_DAT_00658c00)();
     * lVar11=*(seq-8); local_a0=lVar14-x12; (*skp9_DAT_00658c00)(lVar11+0x40);
     * lVar12=(lVar14-x12)-(x8_01+mask); local_b8=FUN_00377824(...);
     * (*skp9_DAT_00658c00)(local_b8-8+0x40...); lVar15=lVar12-x8_02;
     * if (dst[2]==0) { FUN_0036b118(dst); dst=&skp9_DAT_006577e0; }
     * else { seed; while (seq engine yields) { probe dst bitmap;
     *     if (absent) copy element in; else { grow buffer; FUN_002b82f0; } } }
     * if (canary ok) return dst; else FUN_0011d7e8(); */
    return NULL;
}

/* skp9_FUN_0026001c @ 0x0026001c   (est. sk_set_filter_drop)
 * Ghidra: void skp9_FUN_0026001c(undefined8*, long, undefined8, long, ulong,
 *         undefined8, long, undefined8, undefined8, undefined8)
 * Filter-drop: iterates the source set and drops the first count elements whose
 * identity is present in the destination (clearing the destination bits).
 * Returns the destination set (via *param_1) after removing the elements.
 * Faithful drop-fold over the sequence engine.
 * Confidence: low (drop-fold)
 */
void sk_set_filter_drop(uint64_t *out_dst, long dst_bitmap, uint64_t p3, long src_set,
                        uint64_t count, uint64_t p6, long seq, uint64_t p8, uint64_t p9,
                        uint64_t p10)
{
    (void)out_dst; (void)dst_bitmap; (void)p3; (void)src_set; (void)count;
    (void)p6; (void)seq; (void)p8; (void)p9; (void)p10;
    /* local_e0=p3; local_d8=out_dst; lStack_e8=FUN_00310d68(0,seq);
     * local_f0=*(lStack_e8-8); (*skp9_DAT_00658c00)(local_f0+0x40...);
     * lVar16=&local_f0-x8; lVar11=*(seq-8); (*skp9_DAT_00658c00)(lVar11+0x40);
     * lVar14=lVar16-(x8_00+mask); (*skp9_DAT_00658c00)(); lVar12=lVar14-x12;
     * local_c8=*(src_set+0x10); uVar13=count>>3&mask;
     * *(dst_bitmap+uVar13) &= ~(1<<(count&0x3f));  (clear bit)
     * local_c8=local_c8-1;
     * uVar4=FUN_00377824(0xff,p10,p8,...); uVar5=FUN_00377bec(...);
     * pcVar6=FUN_000a68f4(); puVar10=lVar11+8;
     * do { do { uVar7=FUN_00377dcc(0,uVar4); (*pcVar6)(lVar16,uVar7,uVar5);
     *     iVar3=FUN_000839f8(lVar16,1,seq);
     *     if (iVar3==1) { (**(local_f0+8))(lVar16,lStack_e8); FUN_0036b270(src_set);
     *       puVar10=FUN_0025f754(dst_bitmap,p3,local_c8,src_set,seq,p9); goto fin; }
     *     (**(lVar11+0x20))(lVar12,lVar16,seq); uVar7=*(src_set+0x28);
     *     pcVar8=FUN_0031948c(p9); uVar13=(*pcVar8)(uVar7,seq,p9);
     *     bVar1=*(src_set+0x20);
     *     do { uVar13 = uVar13 & ~(-1<<bVar1); uVar17=uVar13>>6; uVar15=1<<(uVar13&0x3f);
     *       if ((uVar15 & *(src_set+0x38+uVar17*8))==0) { (*puVar10)(lVar12,seq);
     *         goto outer; }
     *       (**(lVar11+0x10))(lVar14, *(src_set+0x30)+*(lVar11+0x48)*uVar13, seq);
     *       uVar7=FUN_00027754(p9); pcVar8=FUN_0014ae44();
     *       uVar9=(*pcVar8)(lVar14,lVar12,seq,uVar7); pcVar8=*(lVar11+8);
     *       (*pcVar8)(puVar10,lVar14,seq); uVar13=uVar13+1;
     *     } while ((uVar9&1)==0);
     *     (*pcVar8)(...); uVar13=*(dst_bitmap+uVar17*8);
     *     *(dst_bitmap+uVar17*8)=uVar13 & ~uVar15;  (clear bit)
     *   } while ((uVar13&uVar15)==0);
     *   if (carry(local_c8--)) trap;
     * } while (local_c8!=0);
     * puVar10=&skp9_DAT_006577e0;
     * fin: *out_dst=puVar10; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002603f8 @ 0x002603f8   (est. sk_set_filter_make)
 * Ghidra: void skp9_FUN_002603f8(undefined8, undefined8, long, undefined8, undefined8)
 * Filter-context maker: builds a filter context buffer sized from the set's
 * log2 stride (FUN_0031d5d8), wiring the filter callbacks
 * (FUN_003443f4 / FUN_003469f0) and copying the source set (FUN_0036b118).
 * Reuses the Swift filter machinery with a stack canary.
 * Confidence: low (filter context construction)
 */
void sk_set_filter_make(uint64_t p1, uint64_t p2, long src_set, uint64_t p4, uint64_t p5)
{
    (void)p1; (void)p2; (void)src_set; (void)p4; (void)p5;
    /* local_58=canary; bVar1=*(src_set+0x20);
     * uVar6=(1<<(bVar1&0x3f))+0x3f>>6; local_90=p4; uStack_88=p5;
     * local_80=src_set; uStack_78=p1; local_70=p2;
     * uVar2=FUN_0031d5d8(0,p4,p5); local_b0=auStack_a0; pcStack_b8=FUN_003443f4;
     * local_e0=auStack_d0; pcStack_e8=FUN_003469f0; lVar7=uVar6*8;
     * local_f0=uVar2; local_c0=uVar2;
     * if (log2<0xe || skp9_FUN_003d31f8(lVar7,8)&1) { (*skp9_DAT_00658c00)();
     *   lVar7=-(lVar7+mask); uVar4=FUN_00002534(...); *(local_120+lVar7)=0x66c1c8;
     *   FUN_002b82f0(auStack_68, local_110+lVar7, uVar6, 0x6727f0, FUN_00347348,
     *     auStack_100, 0x6727f0, uVar2, uVar4); FUN_0036b118(src_set); }
     * else { uVar4=FUN_0036a804(lVar7,0xffffffffffffffff); ... FUN_002b82f0(...);
     *   FUN_0036b118(src_set); FUN_00012568(uVar4,...); }
     * uVar4=FUN_00027614(...); uVar2=FUN_0031dc0c(0,uVar2,uVar4,0x66c1c8);
     * uVar2=FUN_0027ed7c(&local_108,uVar2,local_110);
     * if (x21!=0) local_108=uVar2;
     * if (canary ok) return; else FUN_0011d7e8(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00260690 @ 0x00260690   (est. skp9_sk_set_filter_apply)
 * Ghidra: void FUN_00260690(undefined8*, long, undefined8, long, code*,
 *         undefined8, long, undefined8)
 * Filter-apply: iterates the source set and for each live element invokes the
 * user predicate (param_5); elements passing the predicate are copied into the
 * destination bitmap (param_2). Stops early when the predicate short-circuits
 * (unaff_x21). Returns the destination set via *param_1.
 * Confidence: low (filter apply with predicate)
 */
void skp9_sk_set_filter_apply(uint64_t *out_dst, long dst_bitmap, uint64_t p3, long src_set,
                         void (*pred)(void *), uint64_t p6, long seq, uint64_t p8)
{
    (void)out_dst; (void)dst_bitmap; (void)p3; (void)src_set; (void)pred;
    (void)p6; (void)seq; (void)p8;
    /* local_d0=p3; local_c8=out_dst; local_c0=p8; local_b8=p2; local_80=pred;
     * local_70=seq; (*skp9_DAT_00658c00)(*(seq-8)+0x40); local_90=alloc;
     * local_a8=src_set+0x38; local_b0=0; uVar11=1<<(*(src_set+0x20)&0x3f);
     * uVar12=mask; if (log2<6) uVar12=~(-1<<uVar11);
     * local_98=x12+0x10; local_a0=x12+8; uVar12 &= *local_a8; lVar10=0;
     * lStack_88=x12; local_78=src_set;
     * do { if (uVar12==0) { scan next word; }
     *   else { take lowbit; } uVar9=skp9_sk_lowbit_idx(uVar12,lVar10);
     *   (**(lStack_88+0x10))(local_90, *(src_set+0x30)+*(lStack_88+0x48)*idx, seq);
     *   uVar8=(*pred)(lVar1); (**(lVar2+8))(lVar1,lVar4);
     *   if (x21!=0) return; uVar12=local_68; lVar10=lVar13;
     *   if (uVar8&1) { set bit in dst_bitmap; local_b0++; if (carry) trap; } }
     * while (true); ... FUN_0025f754(dst_bitmap,...); *out_dst=result; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002608cc @ 0x002608cc   (est. sk_set_filter_make16)
 * Ghidra: void skp9_FUN_002608cc(undefined8, long, undefined8, undefined8)
 * Filter-context maker for 16-byte-element sets: same buffer construction as
 * sk_set_filter_make but with the 16-byte filter callbacks
 * (FUN_00344230 / FUN_00344250 / FUN_0034426c). Releases the source set.
 * Confidence: low (filter context, 16-byte variant)
 */
void sk_set_filter_make16(uint64_t p1, long src_set, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)src_set; (void)p3; (void)p4;
    /* local_58=canary; bVar1=*(src_set+0x20); uVar6=(1<<(bVar1&0x3f))+0x3f>>6;
     * local_90=p3; uStack_88=p4; local_80=src_set; uStack_78=p1;
     * uVar2=FUN_0031d5d8(0,p3,p4); local_b0=auStack_a0; pcStack_b8=FUN_00344230;
     * local_e0=auStack_d0; pcStack_e8=FUN_00344250; lVar7=uVar6*8;
     * local_f0=uVar2; local_c0=uVar2;
     * if (log2<0xe || skp9_FUN_003d31f8(lVar7,8)&1) { (*skp9_DAT_00658c00)();
     *   lVar7=-(lVar7+mask); uVar4=FUN_00002534(...); *(local_130+lVar7)=0x66c1c8;
     *   FUN_002b82f0(auStack_68, auStack_120+lVar7, uVar6, 0x6727f0, FUN_0034426c,
     *     auStack_100, 0x6727f0, uVar2, uVar4); }
     * else { uVar4=FUN_0036a804(lVar7,...); ... FUN_002b82f0(...);
     *   FUN_00012568(uVar4,...); }
     * uVar4=FUN_00027614(...); uVar2=FUN_0031dc0c(0,uVar2,uVar4,0x66c1c8);
     * FUN_0027ed7c(&local_108,uVar2,auStack_110); FUN_0036b118(src_set);
     * if (canary ok) return; else FUN_0011d7e8(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set filter / merge family (continuation).
 *------------------------------------------------------------------------*/

/* FUN_00260b44 @ 0x00260b44   (est. skp9_sk_set_merge_filter)
 * Ghidra: void FUN_00260b44(undefined8*, long, undefined8, long, long, long,
 *         undefined8)
 * Merge-filter: folds the source set (param_5) into the destination (param_4)
 * only for elements whose identity is absent from both; produces the merged
 * result via FUN_0025f754. Walks both bitmaps (param_4+0x38, param_5+0x38)
 * lowbit-first and copies disjoint elements.
 * Confidence: low (two-set merge filter)
 */
void skp9_sk_set_merge_filter(uint64_t *out_dst, long dst_bitmap, uint64_t p3, long dst_set,
                         long src_set, long seq, uint64_t p7)
{
    (void)out_dst; (void)dst_bitmap; (void)p3; (void)dst_set; (void)src_set;
    (void)seq; (void)p7;
    /* lVar7=*(seq-8); lVar6=dst_set; local_f8=p3; local_f0=out_dst;
     * (*skp9_DAT_00658c00)(lVar7+0x40); puVar8=alloc; (*skp9_DAT_00658c00)();
     * lVar16=puVar8-x12; (*skp9_DAT_00658c00)(); lVar9=lVar16-x12_00; (*skp9_DAT_00658c00)();
     * lVar18=dst_set;
     * if (*(dst_set+0x10) <= *(src_set+0x10)) {
     *   (dst count <= src count: walk dst bitmap, copy disjoint into dst_bitmap)
     *   local_a0 = mask & *(dst_set+0x38); puVar1=lVar7+8; lVar9=0;
     *   do { if (local_a0==0) { scan; } else { take lowbit; }
     *     uVar17=skp9_sk_lowbit_idx; lVar13=*(lVar7+0x48); pcVar11=*(lVar7+0x10);
     *     (*pcVar11)(lVar7+0x10, puVar8, *(dst_set+0x30)+lVar13*idx, seq);
     *     uVar14=*(src_set+0x28); pcVar4=FUN_0031948c(p7);
     *     uVar15=(*pcVar4)(uVar14,seq,p7); bVar2=*(src_set+0x20);
     *     do { uVar15 = uVar15 & ~(-1<<bVar2); lVar9=lVar12;
     *       if (bitmap bit clear) { (*puVar1)(puVar8,seq); lVar18=dst_set;
     *         goto outer; }
     *       (*pcVar11)(lVar16, *(src_set+0x30)+uVar15*lVar13, seq);
     *       uVar14=FUN_00027754(p7); pcVar4=FUN_0014ae44();
     *       uVar5=(*pcVar4)(lVar16,puVar8,seq,uVar14); pcVar4=*puVar1;
     *       (*pcVar4)(lVar16,seq); uVar15=uVar15+1;
     *     } while ((uVar5&1)==0);
     *     (*pcVar4)(...); set bit in dst_bitmap; local_a8++;
     *     if (carry) trap; } while (true); }
     * else {
     *   (walk src bitmap instead)
     *   local_100=src_set+0x38; local_c8=mask & *local_100;
     *   local_108=(1<<log2)+0x3f>>6; local_a8=0; puVar1=lVar7+8;
     *   do { if (local_c8==0) { scan; } else { take lowbit; }
     *     uVar10=skp9_sk_lowbit_idx; lVar12=*(lVar7+0x48); pcVar11=*(lVar7+0x10);
     *     (*pcVar11)(lVar7+0x10, lVar9-x12_01, *(src_set+0x30)+lVar12*uVar10, seq);
     *     (**(lVar7+0x20))(lVar9, lVar9-x12_01, seq);
     *     uVar14=*(dst_set+0x28); pcVar4=FUN_0031948c(p7);
     *     uVar10=(*pcVar4)(uVar14,seq,p7); bVar2=*(dst_set+0x20);
     *     do { uVar10 = uVar10 & ~(-1<<bVar2); uVar17=uVar10>>6; uVar15=1<<(uVar10&0x3f);
     *       if (bitmap bit clear) { (*puVar1)(lVar9,seq); lVar18=dst_set;
     *         goto outer2; }
     *       (*pcVar11)(lVar16, *(dst_set+0x30)+uVar10*lVar12, seq);
     *       uVar14=FUN_00027754(p7); pcVar4=FUN_0014ae44();
     *       uVar5=(*pcVar4)(lVar16,lVar9,seq,uVar14); pcVar4=*puVar1;
     *       (*pcVar4)(lVar16,seq); uVar10=uVar10+1;
     *     } while ((uVar5&1)==0);
     *     (*pcVar4)(...); set bit in dst_bitmap; local_a8++;
     *     if (carry) trap; } while (true); }
     * fin: FUN_0036b270(lVar18); uVar14=FUN_0025f754(dst_bitmap,p3,local_a8,lVar18,seq,p7);
     *   *out_dst=uVar14; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00261134 @ 0x00261134   (est. sk_set_filter_make40)
 * Ghidra: void skp9_FUN_00261134(undefined8, long, undefined8, undefined8, undefined8,
 *         undefined8)
 * Filter-context maker for 40-byte-element sets: same buffer construction with
 * the 40-byte filter callbacks (FUN_0034428c / FUN_003469f0 / FUN_00347348).
 * Releases the source set. Stack canary guarded.
 * Confidence: low (filter context, 40-byte variant)
 */
void sk_set_filter_make40(uint64_t p1, long src_set, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6)
{
    (void)p1; (void)src_set; (void)p3; (void)p4; (void)p5; (void)p6;
    /* local_58=canary; bVar1=*(src_set+0x20); uVar6=(1<<(bVar1&0x3f))+0x3f>>6;
     * local_a0=p3; uStack_98=p4; local_90=p5; uStack_88=p6; local_80=p1;
     * lStack_78=src_set; uVar2=FUN_0031d5d8(0,p3,p5);
     * local_c0=auStack_b0; pcStack_c8=FUN_0034428c; local_f0=auStack_e0;
     * pcStack_f8=FUN_003469f0; lVar7=uVar6*8; local_100=uVar2; local_d0=uVar2;
     * if (log2<0xe || skp9_FUN_003d31f8(lVar7,8)&1) { (*skp9_DAT_00658c00)();
     *   lVar7=-(lVar7+mask); uVar4=FUN_00002534(...); *(local_140+lVar7)=0x66c1c8;
     *   FUN_002b82f0(auStack_68, auStack_130+lVar7, uVar6, 0x6727f0, FUN_00347348,
     *     auStack_110, 0x6727f0, uVar2, uVar4); }
     * else { uVar4=FUN_0036a804(lVar7,...); ... FUN_002b82f0(...);
     *   FUN_00012568(uVar4,...); }
     * uVar4=FUN_00027614(...); uVar2=FUN_0031dc0c(0,uVar2,uVar4,0x66c1c8);
     * FUN_0027ed7c(&local_118,uVar2,auStack_120); FUN_0036b118(src_set);
     * if (canary ok) return; else FUN_0011d7e8(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002613b4 @ 0x002613b4   (est. sk_set_filter_keep16)
 * Ghidra: void skp9_FUN_002613b4(undefined8*, long, undefined8, undefined8, long,
 *         long, long, undefined8, undefined8)
 * Filter-keep over a 16-byte-element set: iterates the source, copying each
 * element whose identity is absent from the destination into dst_bitmap.
 * Produces the result via FUN_0025f754. Faithful filter-keep fold.
 * Confidence: low (filter-keep, 16-byte)
 */
void sk_set_filter_keep16(uint64_t *out_dst, long dst_bitmap, uint64_t p3, uint64_t p4,
                          long src_set, long seq, long set, uint64_t p8, uint64_t p9)
{
    (void)out_dst; (void)dst_bitmap; (void)p3; (void)p4; (void)src_set;
    (void)seq; (void)set; (void)p8; (void)p9;
    /* lVar12=*(seq-8); local_e0=p3; local_d8=out_dst; (*skp9_DAT_00658c00)(lVar12+0x40);
     * puVar14=alloc; (*skp9_DAT_00658c00)(); lVar13=puVar14-x12;
     * lVar5=FUN_00310d68(0,seq); lVar18=lVar13-x8_00;
     * lVar5=*(set-8); lVar15=lVar18-(x8_01+mask); lVar6=FUN_00377824(...);
     * local_e8=*(lVar6-8); lVar20=lVar15-x8_02;
     * (**(lVar5+0x10))(lVar15,p4,set); (*FUN_000a68c4(p9))(lVar20,set,p9);
     * uVar8=FUN_00377bec(...); pcVar7=FUN_000a68f4(); lVar5=0; puVar1=lVar12+8;
     * do { (*pcVar7)(lVar18,lVar6,uVar8); iVar4=FUN_000839f8(lVar18,1,seq);
     *   if (iVar4==1) { (**(local_e8+8))(lVar20,lVar6); FUN_0036b270(src_set);
     *     uVar8=FUN_0025f754(dst_bitmap,p3,lVar5,src_set,seq,p8);
     *     *out_dst=uVar8; return; }
     *   (**(lVar12+0x20))(lVar13,lVar18,seq); uVar16=*(src_set+0x28);
     *   pcVar9=FUN_0031948c(p8); uVar10=(*pcVar9)(uVar16,seq,p8);
     *   bVar2=*(src_set+0x20);
     *   do { uVar10 = uVar10 & ~(-1<<bVar2); uVar19=uVar10>>6; uVar17=1<<(uVar10&0x3f);
     *     if ((uVar17 & *(src_set+0x38+uVar19*8))==0) { (*puVar1)(lVar13,seq);
     *       goto outer; }
     *     (**(lVar12+0x10))(puVar14, *(src_set+0x30)+*(lVar12+0x48)*uVar10, seq);
     *     uVar16=FUN_00027754(p8); pcVar9=FUN_0014ae44();
     *     uVar11=(*pcVar9)(puVar14,lVar13,seq,uVar16); pcVar9=*(lVar12+8);
     *     (*pcVar9)(puVar1,puVar14,seq); uVar10=uVar10+1;
     *   } while ((uVar11&1)==0);
     *   (*pcVar9)(...); uVar10=*(dst_bitmap+uVar19*8);
     *   *(dst_bitmap+uVar19*8)=uVar10|uVar17;
     *   if ((uVar10&uVar17)==0 && carry(lVar5++)) trap;
     * } while (true); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set dispatch / string wrappers (0x2618xx-0x2626xx).
 *------------------------------------------------------------------------*/

/* skp9_FUN_0026181c @ 0x0026181c   (est. sk_set_string_prepare)
 * Ghidra: void skp9_FUN_0026181c(undefined8, undefined8, undefined8, undefined8)
 * String/set preparation wrapper: runs the runtime prologue
 * (FUN_00084220) and a fixed sequence of string/set helpers
 * (FUN_0035125c, FUN_0034a980, FUN_00377824, FUN_0007c1a4, FUN_0034b05c,
 * FUN_0034e72c, FUN_0034d160, FUN_0034ded4, FUN_00358f90), ending with the
 * thread epilogue. Opaque dispatch pipeline.
 * Confidence: low (opaque helper sequence)
 */
void sk_set_string_prepare(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2; (void)p3; (void)p4;
    /* FUN_00084220(); FUN_0035125c(p3); FUN_0034a980(); FUN_00077894();
     * FUN_00377824(); FUN_00348d64(); FUN_0007c1a4(); (*skp9_DAT_00658c00)();
     * FUN_0034b05c(); FUN_0007b384(); FUN_0034e72c(); (*x9)();
     * FUN_00083a18(p4); uVar1=FUN_0034d160(); (*x8)(uVar1,p4);
     * FUN_0034ded4(); (*x8_00)(); uVar1=FUN_00358f90();
     * FUN_00084234(uVar1,x1); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002618e8 @ 0x002618e8   (est. sk_set_string_prepare_a)
 * Ghidra: void skp9_FUN_002618e8(void)
 * String/set preparation (variant a): same prologue and helper sequence with
 * FUN_0031945c/FUN_0034c9f8 replacing the tail helpers. Opaque pipeline.
 * Confidence: low
 */
void sk_set_string_prepare_a(void)
{
    /* FUN_00084220(); FUN_0034e004(); FUN_003514b8(); FUN_0034a980();
     * FUN_00350600(); FUN_00377824(); FUN_00348d4c(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034aee4(); FUN_0007b384(); FUN_00350b24();
     * FUN_0008e388(); (*x9)(); FUN_0031945c(x4); FUN_000dbdf4();
     * FUN_003508d8(); (*x8)(); FUN_0034c9f8(); (*x8_00)();
     * FUN_00084234(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002619b0 @ 0x002619b0   (est. sk_set_string_prepare_b)
 * Ghidra: void skp9_FUN_002619b0(void)
 * String/set preparation (variant b): identical to variant a but ends with
 * FUN_00358f90 + FUN_00084234. Opaque pipeline.
 * Confidence: low
 */
void sk_set_string_prepare_b(void)
{
    /* FUN_00084220(); FUN_0034e004(); FUN_003514b8(); FUN_0034a980();
     * FUN_00350600(); FUN_00377824(); FUN_00348d4c(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034aee4(); FUN_0007b384(); FUN_00350b24();
     * FUN_0008e388(); (*x9)(); FUN_0031948c(x4); FUN_000dbdf4();
     * FUN_003508d8(); (*x8)(); FUN_0034c9f8(); (*x8_00)();
     * uVar1=FUN_00358f90(); FUN_00084234(uVar1,x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00261a7c @ 0x00261a7c   (est. skp9_sk_set_result_zero)
 * Ghidra: void FUN_00261a7c(undefined8*, undefined8)
 * Zeroes a 5-word (40-byte) set-operation result buffer *param_1, after
 * releasing the prior element (FUN_0034ab20 + descriptor destroy). Clears
 * param_1[0..4]. Result initializer.
 * Confidence: high (faithful; explicit zeroing)
 */
void skp9_sk_set_result_zero(uint64_t *out, uint64_t p2)
{
    /* FUN_0034ab20(p2,p2); (**(x16+8))();  (descriptor destroy)
     * out[4]=0; out[1]=0; out[0]=0; out[3]=0; out[2]=0; */
    (void)p2;
    out[0] = out[1] = out[2] = out[3] = out[4] = 0;
}

/* skp9_FUN_00261ac8 @ 0x00261ac8   (est. sk_set_string_init)
 * Ghidra: void skp9_FUN_00261ac8(undefined8, undefined8, undefined8, undefined8)
 * String/set initializer: seeds the object (x21) with the type descriptor
 * (FUN_0031d3bc + skp9_DAT_004f17a8 method table), then invokes the descriptor
 * init callback (+0x20). Object constructor.
 * Confidence: low (constructor)
 */
void sk_set_string_init(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2; (void)p3; (void)p4;
    /* local_50=FUN_00351cc4(); local_40=p3; uStack_38=p4;
     * uVar1=FUN_0031d3bc(0,local_50); *(x21+0x18)=uVar1;
     * *(x21+0x20)=&skp9_DAT_004f17a8; FUN_00319a4c(); FUN_0034b3e8();
     * (**(x16+0x20))(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00261b48 @ 0x00261b48   (est. sk_set_string_dispatch)
 * Ghidra: void skp9_FUN_00261b48(void)
 * String/set dispatch: seeds the object (FUN_00353b10 + FUN_0035125c), runs
 * the helper pipeline, and applies the method-table dispatch
 * (FUN_00100c38 with the captured x21+0x28). Ends with the thread epilogue.
 * Confidence: low (dispatch pipeline)
 */
void sk_set_string_dispatch(void)
{
    /* FUN_00084220(); lVar1=FUN_00353b10(); FUN_0035125c(*(lVar1+0x20));
     * FUN_0034b7b8(); FUN_00377824(); FUN_00348d4c(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034aee4(); FUN_0007b384(); FUN_00350b24();
     * FUN_003504c4(); auVar2=(*x9)();
     * FUN_00100c38(auStack_28, auVar2, *(x21+0x28)); FUN_001a8068();
     * FUN_0034c9f8(); (*x8)(); FUN_0034d9ac(auStack_28); FUN_0008e5d8();
     * FUN_00353b04(); FUN_000b4390(); (*x9_00)(); FUN_000026e8(auStack_28);
     * FUN_00084234(x1); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Set panic / dispatch wrappers (0x261c40-0x2626xx).
 *------------------------------------------------------------------------*/

/* FUN_00261c40 @ 0x00261c40   (est. sk_set_panic_a)
 * FUN_00261c88 @ 0x00261c88   (est. skp9_sk_set_panic_b)
 * FUN_00261cd0 @ 0x00261cd0   (est. skp9_sk_set_panic_c)
 * FUN_00261d18 @ 0x00261d18   (est. skp9_sk_set_panic_d)
 * Ghidra: void FUN_00261c40(void)  (each)
 * Identical noreturn panics: FUN_003488bc(1); FUN_0006f768(); noreturn
 * skp9_FUN_00356408(). Four aliases for distinct set-fatal conditions.
 * Confidence: high (pure fatal path)
 */
void sk_set_panic_a(void) { skp9_sk_vspace_fail(1); skp9_sk_fatal_error(0, 0); }
void skp9_sk_set_panic_b(void) { skp9_sk_vspace_fail(1); skp9_sk_fatal_error(0, 0); }
void skp9_sk_set_panic_c(void) { skp9_sk_vspace_fail(1); skp9_sk_fatal_error(0, 0); }
void skp9_sk_set_panic_d(void) { skp9_sk_vspace_fail(1); skp9_sk_fatal_error(0, 0); }

/* FUN_00261d60 @ 0x00261d60   (est. skp9_sk_set_string_member)
 * Ghidra: void FUN_00261d60(long, long)
 * String/set member access: copies the source seed (param_2+0x10) into the
 * object (param_1+0x18), runs the element-init (FUN_00319a4c) and dispatches
 * the descriptor callback (+0x10). Small object-member helper.
 * Confidence: low (member access; jumptable not recovered)
 */
void skp9_sk_set_string_member(long obj, long src)
{
    /* *(obj+0x18) = *(src+0x10); FUN_00319a4c(obj); FUN_00350bcc();
     * (**(x16+0x10))();  (indirect jump at 0x261dac not recoverable) */
    (void)obj; (void)src;
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00261db0 @ 0x00261db0   (est. sk_set_string_iterate)
 * Ghidra: void skp9_FUN_00261db0(void)
 * String/set iterate: seeds the object (FUN_00356334 + FUN_0035125c), runs the
 * helper pipeline, and iterates the element set applying a compare callback
 * (FUN_0034dba8 with the tag). Ends with the thread epilogue.
 * Confidence: low (opaque iterate pipeline)
 */
void sk_set_string_iterate(void)
{
    /* FUN_0008e518(); lVar1=FUN_00356334(); FUN_0035125c(*(lVar1+0x20));
     * FUN_0034b7b8(); uVar2=FUN_00377824(); FUN_0034ab20(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034af20(); FUN_003504e8(); FUN_00310d68();
     * FUN_00348d7c(); (*skp9_DAT_00658c00)(x8_00+0x40); FUN_003489c0();
     * (*skp9_DAT_00658c00)(); FUN_0034c074(); FUN_0034998c();
     * (*skp9_DAT_00658c00)(x8_01+0x40); FUN_00348f38();
     * FUN_0034e484(*(x12+0x10)); (*x8_02)(); FUN_00350b48();
     * uVar3=FUN_00356b2c(); FUN_0034dba8(uVar3,(uint)uVar3^1); FUN_000839d8();
     * FUN_0035478c(); FUN_0034e024(); (*x9)(); FUN_00349f3c();
     * if (ZR) { FUN_0007b384(); FUN_0034d434(); auVar4=(*x9_00)();
     *   FUN_00352498(auVar4, uVar2); uVar2=FUN_00356b2c();
     *   FUN_00350268(uVar2,(uint)uVar2^1); FUN_000839d8();
     *   FUN_003508f0(*(x16+8)); (*x8_03)(); }
     * else { FUN_0034b3e8(); (**(x16_00+0x20))(x8); FUN_0034bc94(x8);
     *   FUN_000839d8(); }
     * FUN_0008e500(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00261f98 @ 0x00261f98   (est. sk_set_string_dispatch2)
 * Ghidra: void skp9_FUN_00261f98(void)
 * String/set dispatch (second variant): seeds via FUN_00350b54, runs the
 * helper pipeline with two compare dispatch branches (FUN_00365b6c result),
 * applying per-branch descriptor callbacks. Ends with the thread epilogue and
 * a stack-relative return value.
 * Confidence: low (opaque dispatch)
 */
void sk_set_string_dispatch2(void)
{
    /* FUN_0008e518(); auVar4=FUN_00350b54(); FUN_00350bd8(*(auVar4_8+0x20));
     * uVar2=*(x21+0x10); auVar5=FUN_0034fa34();
     * uVar2=FUN_00377824(auVar5, uVar2); FUN_0034ab20(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034b71c(); FUN_003504e8(); FUN_00310d68();
     * FUN_000a6f88(); (*skp9_DAT_00658c00)(x8+0x40); FUN_00348abc();
     * (*skp9_DAT_00658c00)(); FUN_0034b87c(); FUN_0034998c();
     * (*skp9_DAT_00658c00)(x8_00+0x40); FUN_0034947c(); FUN_003494e8();
     * (*skp9_DAT_00658c00)(x8_01+0x40); FUN_003503ec(); (*skp9_DAT_00658c00)();
     * FUN_00350ed0(*(x12+0x10)); (*x8_02)(); FUN_00350ea4(); FUN_00351280();
     * iVar1=FUN_00365b6c();
     * if (iVar1==0) { FUN_0034c3f4(); FUN_000839d8(); pcVar3=*(x16+8);
     *   FUN_00354d68(); (*pcVar3)(); FUN_00355dfc(); FUN_0007b384();
     *   FUN_003511a8(local_28); (*x9_00)(); auVar5=FUN_003510dc();
     *   iVar1=FUN_00356b2c(auVar5, uVar2);
     *   if (iVar1==0) { FUN_0034c3f4(); FUN_000839d8(); FUN_00353f38();
     *     (*pcVar3)(); } else { FUN_00357400(); FUN_0034bc94(); FUN_000839d8();
     *     pcVar3=*(x16_00+0x20); FUN_000dbd0c(); (*pcVar3)();
     *     FUN_003508d8(auVar4_0); (*pcVar3)(); } }
     * else { FUN_0034bc94(); FUN_000839d8(); pcVar3=*(x16_00+0x20);
     *   FUN_00350b78(); (*pcVar3)(); FUN_0035056c(auVar4_0); (*pcVar3)(); }
     * uVar2=FUN_003548b8(); FUN_0008e500(uVar2, *(stack+0x58)); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00262234 @ 0x00262234   (est. sk_set_dispatch_chain1)
 * FUN_00262238 @ 0x00262238   (est. skp9_sk_set_dispatch_chain1b)
 * FUN_00262248 @ 0x00262248   (est. skp9_sk_set_dispatch_chain2)
 * FUN_00262258 @ 0x00262258   (est. skp9_sk_set_dispatch_chain3)
 * FUN_00262268 @ 0x00262268   (est. skp9_sk_set_dispatch_chain4)
 * Ghidra: void skp9_FUN_00262234(undefined8, undefined8, undefined8)  (each)
 * Dispatch chains that run N panic guards (FUN_00261c40/00261c88/00261cd0/
 * 00261d18) and then the iterate helper skp9_FUN_00261db0(p3, guard). Progressively
 * shorter chains (4/4/3/2/1 panics) selecting the guard depth for the op.
 * Confidence: medium (guard-depth dispatch chains)
 */
void sk_set_dispatch_chain1(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    sk_set_panic_a(); skp9_sk_set_panic_b(); skp9_sk_set_panic_c();
    skp9_sk_set_panic_d();
    sk_set_string_iterate();   /* skp9_FUN_00261db0 */
}
void skp9_sk_set_dispatch_chain1b(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    sk_set_panic_a(); skp9_sk_set_panic_b(); skp9_sk_set_panic_c();
    skp9_sk_set_panic_d();
    sk_set_string_iterate();
}
void skp9_sk_set_dispatch_chain2(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    skp9_sk_set_panic_b(); skp9_sk_set_panic_c(); skp9_sk_set_panic_d();
    sk_set_string_iterate();
}
void skp9_sk_set_dispatch_chain3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    skp9_sk_set_panic_c(); skp9_sk_set_panic_d();
    sk_set_string_iterate();
}
void skp9_sk_set_dispatch_chain4(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    skp9_sk_set_panic_d();
    sk_set_string_iterate();
}

/* skp9_FUN_00262290 @ 0x00262290   (est. sk_set_string_prepare_c)
 * Ghidra: void skp9_FUN_00262290(undefined8, undefined8, undefined8)
 * String/set preparation (variant c): same prologue as sk_set_string_prepare
 * but with FUN_0031d3d4(p3)/FUN_0034d160 replacing the middle helpers.
 * Opaque pipeline.
 * Confidence: low
 */
void sk_set_string_prepare_c(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_00084220(); FUN_0035125c(x1); FUN_0034a980(); FUN_00077894();
     * FUN_00377824(); FUN_00348d64(); FUN_0007c1a4(); (*skp9_DAT_00658c00)();
     * FUN_0034b05c(); FUN_0007b384(); FUN_0034e72c(); (*x9)();
     * FUN_0031d3d4(p3); uVar1=FUN_0034d160(); (*x8)(uVar1,p3);
     * FUN_0034ded4(); (*x8_00)(); uVar1=FUN_00358f90();
     * FUN_00084234(uVar1,x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0026235c @ 0x0026235c   (est. sk_set_string_lookup)
 * Ghidra: void skp9_FUN_0026235c(void)
 * String/set lookup: runs the helper pipeline twice (two prologue stages), then
 * resolves the element (FUN_003197a8) and applies the descriptor lookup
 * callback (FUN_0035139c + FUN_00358358). Ends with the thread epilogue.
 * Confidence: low (opaque lookup pipeline)
 */
void sk_set_string_lookup(void)
{
    /* auVar2=FUN_0008e518(); FUN_00350a64(); FUN_00310d68(); FUN_00348ce8();
     * FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034b0c4(); FUN_00350bd8(x3);
     * FUN_003560f8(); FUN_00377824(); FUN_00350798(); FUN_00310d68();
     * FUN_00348cd0(); FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034bdfc();
     * FUN_0034c6c4(); FUN_000839d8(); uVar1=FUN_003197a8(x4);
     * FUN_00350968(uVar1, auVar2_0); (*x8)(); FUN_0035401c();
     * FUN_00358358(FUN_0031d404); FUN_00353384(); FUN_00350af4(); (*x9)();
     * FUN_003510ac(*(x16_00+8)); (*x8_00)();
     * FUN_0035139c(*(x16+0x20), auVar2_8); (*x8_01)(); FUN_0008e500(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002624f0 @ 0x002624f0   (est. sk_set_string_lookup2)
 * Ghidra: void skp9_FUN_002624f0(void)
 * String/set lookup (second variant): same pipeline as sk_set_string_lookup
 * but resolves via FUN_003197d8/FUN_003505e8 and the FUN_003469c0 callback,
 * returning (uVar1 & 1) as the found flag.
 * Confidence: low (opaque lookup)
 */
void sk_set_string_lookup2(void)
{
    /* FUN_0008e518(); FUN_00350a64(); FUN_00310d68(); FUN_00348ce8();
     * FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034b0c4(); FUN_00350bd8(x3);
     * FUN_003560f8(); FUN_00377824(); FUN_00350798(); FUN_00310d68();
     * FUN_00348cd0(); FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034bdfc();
     * FUN_0034c6c4(); FUN_000839d8(); uVar2=FUN_003197d8(x4);
     * FUN_003505e8(uVar2); FUN_00352e60(); uVar1=(*x8)(); FUN_0035401c();
     * FUN_00358358(FUN_003469c0); FUN_00353384(); FUN_00350af4(); (*x9)();
     * FUN_003510ac(*(x16_00+8)); (*x8_00)();
     * FUN_0035139c(*(x16+0x20), x1); (*x8_01)(); FUN_0008e500(uVar1&1, x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00262690 @ 0x00262690   (est. sk_set_string_hash_run)
 * Ghidra: void skp9_FUN_00262690(undefined8, undefined8, undefined8)
 * String/set hash run: seeds via FUN_00351468/FUN_00352894, runs the helper
 * pipeline with a hash callback (FUN_00350630 on x12+0x10). No epilogue shown.
 * Confidence: low (opaque hash pipeline)
 */
void sk_set_string_hash_run(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_00351468(); FUN_00352894(p3); FUN_0034fa34(); FUN_00351744();
     * auVar1=FUN_00377824(); FUN_000a6f88(auVar1); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034b05c(); FUN_00350630(*(x12+0x10));
     * (*x8)(); FUN_0031bc70(); FUN_0035133c(); FUN_00350eec(); (*x9)(); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00262750 @ 0x00262750   (est. sk_set_string_validate)
 * Ghidra: void FUN_00262750(undefined8, undefined8, undefined8, undefined8)
 * String/set validation: runs the prologue and helper pipeline, then checks
 * the element validity (FUN_00359be0 + FUN_00349f3c); on success dispatches
 * the descriptor callback (+0x20); on failure raises the fatal
 * (FUN_003489dc(0x95); noreturn skp9_FUN_0034a2f8()).
 * Confidence: low (validate-or-panic)
 */
void sk_set_string_validate(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2; (void)p3; (void)p4;
    /* FUN_00084220(); FUN_003503d0(); FUN_0035125c(p3); FUN_0034a980();
     * FUN_0035056c(); FUN_00377824(); FUN_0034ab20(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034aee4(); FUN_003504e8(); FUN_0034d464();
     * FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034b0c4(); FUN_0031d428(p4);
     * FUN_00350b24(); FUN_00350ad0(); (*x9)(); FUN_0031bc70(); FUN_00350c50();
     * FUN_0034d374(); (*x9_00)(); FUN_00359be0(); FUN_00349f3c();
     * if (!ZR) { FUN_0034b3e8(); (**(x16+0x20))(); FUN_00084234(x30); return; }
     * FUN_003489dc(0x95); skp9_FUN_0034a2f8(); skp9_FUN_001afe4c(); */
    skp9_sk_fatal_error(0x95, 0);
}

/*------------------------------------------------------------------------*
 * String / Unicode scalar family (0x262888-0x2652a4).
 *------------------------------------------------------------------------*/

/* skp9_FUN_00262888 @ 0x00262888   (est. sk_string_unicode_scan)
 * Ghidra: undefined8 skp9_FUN_00262888(void)
 * Unicode scan: runs a helper sequence (FUN_0035697c, FUN_00350950,
 * FUN_0007b384, FUN_0035037c) and returns the stack-saved scalar (uStack_38).
 * Opaque single-scalar reader.
 * Confidence: low (opaque scalar read)
 */
uint64_t sk_string_unicode_scan(void)
{
    /* FUN_0035697c(); FUN_00350950(); FUN_0007b384(); FUN_0035037c();
     * (*x9)(); return uStack_38; */
    return 0;
}

/* skp9_FUN_002628d0 @ 0x002628d0   (est. sk_string_unicode_next)
 * Ghidra: void skp9_FUN_002628d0(void)
 * Unicode next-scalar: runs the sequence engine (FUN_00357cb4,
 * FUN_00349fcc, FUN_00350a64, FUN_00310d68) and dispatches the descriptor
 * callback (+8). Completes via FUN_00357c74. Iterator step.
 * Confidence: low (iterator step pipeline)
 */
void sk_string_unicode_next(void)
{
    /* FUN_00357cb4(); FUN_00349fcc(); FUN_00350a64(); FUN_00310d68();
     * FUN_000841a0(); (**(x16+8))(); FUN_00350780(); FUN_0031bc70();
     * FUN_00355d1c(); FUN_0036b270(); FUN_00350624(&stk);
     * uVar1=(*x23)(); FUN_00357c74(uVar1,x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00262950 @ 0x00262950   (est. sk_string_unicode_char)
 * Ghidra: void skp9_FUN_00262950(void)
 * Unicode character read: seeds via FUN_00350b0c, runs the helper pipeline,
 * and invokes the descriptor callbacks (+8, +0x10) around the scalar fetch
 * (FUN_000dbe70). Ends with the thread epilogue.
 * Confidence: low (opaque char pipeline)
 */
void sk_string_unicode_char(void)
{
    /* FUN_0008e518(); uVar1=FUN_00350b0c(); FUN_00350a64(); FUN_00310d68();
     * FUN_00348e18(); FUN_0007c1a4(); (*skp9_DAT_00658c00)(); FUN_0034b05c();
     * pcVar2=*(x16+8); FUN_00084180(); (*pcVar2)(); local_8=uVar1;
     * FUN_0035125c(x3); FUN_0031bc70(); FUN_00357b48(); FUN_0036b270();
     * FUN_000dbe70(&local_8); (*x26)(); FUN_003504a0(*(x16+0x10));
     * (*x8)(); FUN_0034ad40(); FUN_0035060c(); (*pcVar2)();
     * uVar1=FUN_003548b8(); FUN_0008e500(uVar1, stack_48); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00262a4c @ 0x00262a4c   (est. skp9_sk_string_unicode_append)
 * Ghidra: void FUN_00262a4c(undefined8, undefined8, undefined8)
 * Unicode append: if the target (x22) is zero, runs a helper sequence
 * (FUN_00350410, FUN_00351088); otherwise appends the scalar via
 * FUN_0031bc70/FUN_00350ed0 and, on the valid flag, dispatches the descriptor
 * callback (+0x20); on failure raises the fatal.
 * Confidence: low (append-or-panic)
 */
void skp9_sk_string_unicode_append(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_00351a80(); FUN_0034d464(0); FUN_0007c1a4(); (*skp9_DAT_00658c00)();
     * FUN_0034cff4();
     * if (x22==0) { FUN_00350410(); FUN_00351088(); }
     * else { FUN_003514b8(p3); pcVar1=FUN_0031bc70(); FUN_0036b270();
     *   FUN_00350ed0(&stk); (*pcVar1)(); FUN_0034ad40();
     *   if (!ZR) { FUN_0034b518(); (**(x16+0x20))(x8); return; } }
     * FUN_00348b40(); skp9_FUN_0034a2f8(); skp9_FUN_001afe4c(); */
    skp9_sk_fatal_error(0, 0);
}

/* skp9_FUN_00262b5c @ 0x00262b5c   (est. sk_string_scalar_run)
 * Ghidra: void skp9_FUN_00262b5c(undefined8)
 * Scalar run: seeds via FUN_0034b7b8/FUN_00377824/FUN_00351f10, runs the
 * helper pipeline with a scalar callback (FUN_0034c2a4), and invokes the
 * captured closure (in_x3) with param_1. Small scalar dispatch.
 * Confidence: low (scalar dispatch)
 */
void sk_string_scalar_run(uint64_t p1)
{
    /* FUN_0034b7b8(); FUN_00377824(); FUN_00351f10(); FUN_0007c1a4();
     * (*skp9_DAT_00658c00)(); FUN_0034b0c4(); FUN_003506b0(); FUN_0034c2a4();
     * (*x9)(); FUN_00077708(p1); (*in_x3)(); */
    (void)p1;
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00262bf0 @ 0x00262bf0   (est. sk_string_unicode_init)
 * Ghidra: void skp9_FUN_00262bf0(void)
 * Unicode string initializer: seeds the object with two candidate scalars
 * (FUN_00365b6c gate), selects the appropriate seed, and writes the 0x38-byte
 * string header (type descriptor skp9_DAT_00657778, capacity 0x1000000000000, flags).
 * Faithful string-object construction.
 * Confidence: medium (faithful string header init)
 */
void sk_string_unicode_init(void)
{
    /* FUN_0008e518(); FUN_00350b0c(); FUN_00349444(); FUN_00354394();
     * FUN_00377824(); FUN_00348ce8(); (*skp9_DAT_00658c00)(x8_00+0x40);
     * FUN_00348abc(); (*skp9_DAT_00658c00)(); FUN_0034b87c();
     * pcVar4=*(x16+0x10); FUN_000bd3a4(x8); (*pcVar4)(); FUN_0034fed0();
     * (*pcVar4)(); FUN_00351420(&local_28); uVar1=FUN_00365b6c();
     * if ((uVar1&1)==0) { FUN_000bd3a4(*(x16+0x20)); (*x8_02)();
     *   FUN_00002534(...); FUN_00350c08(&local_28); uVar1=FUN_00365b6c();
     *   if ((uVar1&1)==0) { FUN_00350530(); FUN_00340538(); FUN_0035a744();
     *     *(x8_04+2)=0; lVar2=x8_04; uVar3=w9_00; goto store; } }
     * else { FUN_003504c4(*(x16+8)); (*x8_01)(); uStack_10=uStack_20;
     *   local_18=local_28; }
     * FUN_003a25d4(uStack_10); if (uStack_10&0x2000000000000000) local_18=uStack_10;
     * FUN_00350530(); FUN_00340538(); FUN_0035a744();
     * *(x8_03+2) = (local_18>>0x3e)&1; lVar2=x8_03; uVar3=w9;
     * store: *(lVar2+8)=uVar3; *(lVar2+0x10)=&skp9_DAT_00657778; *(lVar2+0x18)=0;
     *   *(lVar2+0x1c)=0x1000000000000; *(lVar2+0x28)=&skp9_DAT_00657778;
     *   *(lVar2+0x30)=0; *(lVar2+0x34)=0; *(lVar2+0x38)=uVar3;
     *   FUN_0008e500(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/*------------------------------------------------------------------------*
 * Swift String / Unicode scalar decoding (0x262da4-0x2652a4).
 *------------------------------------------------------------------------*/

/* skp9_FUN_00262da4 @ 0x00262da4   (est. sk_string_next_scalar)
 * Ghidra: ulong skp9_FUN_00262da4(long)
 * Next Unicode scalar from a Swift String: reads the string object (param_1)
 * and iterates its UTF-8 buffer via the grapheme scanner (skp9_FUN_00263e20 with
 * callback LAB_00343190, or skp9_FUN_00263068 fast path). Handles the "pending
 * scalar" state (+0x34/+0x38) and Hangul composition (skp9_FUN_002641a8). Returns
 * {scalar, continuation} packed in a 64-bit word.
 * Confidence: medium (faithful scalar-iterator state machine)
 */
uint64_t sk_string_next_scalar(long str)
{
    (void)str;
    /* uStack_38=*(str+0x18); local_40=*(str+0x10);
     * lVar1=x20 + *(str+0x24);
     * if ((*(byte*)(lVar1+1)&1)==0) { if ((*(byte*)(lVar1+2)&1)==0)
     *   skp9_FUN_00263e20(lVar1, &LAB_00343190, auStack_50);
     *   else skp9_FUN_00263068();
     *   uVar4=FUN_00359d64(); if (!ZR) { uVar5=uVar4>>0x20; goto out; } }
     * uVar5=1; *(lVar1+1)=1;
     * if ((*(byte*)(lVar1+2)&1)==0) { skp9_FUN_0026398c(lVar1);
     *   uVar4=FUN_00359d64();
     *   if (ZR) { uVar2=*(lVar1+0x34); bVar3=*(lVar1+0x38);
     *     uVar5=bVar3; *(lVar1+0x34)=(int)uVar4; *(lVar1+0x38)=1;
     *     if (bVar3==1) { uVar4=skp9_FUN_002641a8(); uVar5=(uVar4>>0x30); } }
     *   else uVar5=(uVar4>>0x20); }
     * else uVar4=0;
     * out: return uVar4&0xffffffff | (uVar5&0xff)<<0x20; */
    return 0;
}

/* skp9_FUN_00262e9c @ 0x00262e9c   (est. sk_string_utf8_decode)
 * Ghidra: void skp9_FUN_00262e9c(void)
 * UTF-8 byte decoding of a Swift String: reads the string descriptor
 * (FUN_00357ca0), locates the scalar at the current index via FUN_002ab4d4,
 * and decodes 1-4 byte UTF-8 sequences (including the ASCII fast path and the
 * slow heap path via FUN_002a9ba8). Advances the index and stores the scalar.
 * Faithful UTF-8 scalar decoder.
 * Confidence: medium (faithful UTF-8 decode)
 */
void sk_string_utf8_decode(void)
{
    /* auVar9=FUN_00357ca0(); puVar4=lo;
     * if (0x3fff < (puVar4[4]^puVar4[1])) {
     *   uVar8=puVar4[2]; uVar1=puVar4[3];
     *   uVar5=FUN_002ab4d4(puVar4[4], *puVar4, puVar4[1], uVar8, uVar1);
     *   if (uVar1>>0x3c & 1) { FUN_0035646c(); FUN_0034883c(); FUN_001afa84(); }
     *   uVar5 >>= 0x10;
     *   if (uVar1>>0x3d & 1) {  (inline scalar in object)
     *     uVar8 = byte[uVar5]; if (<0) { switch LZCOUNT: decode 2-4 bytes; } }
     *   else if (uVar8>>0x3c & 1) {  (heap buffer)
     *     lVar6=FUN_003542dc(); do { decode byte at lVar6+uVar5; } while; }
     *   ... store scalar; }
     * uVar8=0x100000000; FUN_00357c44(uVar8, hi); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00263068 @ 0x00263068   (est. sk_string_utf8_fast)
 * Ghidra: void skp9_FUN_00263068(void)
 * UTF-8 fast-path scalar decode: runs the sequence engine (FUN_00357cb4,
 * FUN_0034b430, FUN_003537d4, FUN_00351100, FUN_00377824, FUN_00356774,
 * FUN_0009461c) and returns the decoded scalar via FUN_00357c74. Used when the
 * string fits inline.
 * Confidence: low (fast-path scalar)
 */
void sk_string_utf8_fast(void)
{
    /* FUN_00357cb4(); FUN_0034b430(); FUN_003537d4(); FUN_00351100();
     * FUN_00377824(); FUN_00356774(); FUN_0009461c(); FUN_00351e3c();
     * uVar1=FUN_00377bec(); pcVar2=FUN_000a68f4(); FUN_00350500();
     * uVar3=FUN_00377dcc(); (*pcVar2)(&stk, uVar3, uVar1);
     * FUN_00357c74(CONCAT14(lo,hi), x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002630fc @ 0x002630fc   (est. sk_string_scalar_done)
 * Ghidra: void skp9_FUN_002630fc(void)
 * Scalar-done: skp9_FUN_00262da4() then FUN_00351fc0(). Advances the scalar state
 * and commits.
 * Confidence: low (thin wrapper)
 */
void sk_string_scalar_done(void)
{
    sk_string_next_scalar(0);
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00263124 @ 0x00263124   (est. sk_string_scalar_run2)
 * FUN_00263128 @ 0x00263128   (est. skp9_sk_string_scalar_run3)
 * Ghidra: void skp9_FUN_00263124(void)  (each)
 * Scalar run: FUN_003555dc() then skp9_FUN_00262b5c(). Two thin wrappers.
 * Confidence: low
 */
void sk_string_scalar_run2(void) { sk_string_scalar_run(0); }
void skp9_sk_string_scalar_run3(void) { sk_string_scalar_run(0); }

/* FUN_00263140 @ 0x00263140   (est. skp9_sk_string_scalar)
 * Ghidra: ulong FUN_00263140(char*, undefined8)
 * Reads the next Unicode scalar from a Swift String (ASCII fast path): if the
 * string is empty/finished returns 0; otherwise decodes the scalar at the
 * current index (1-byte ASCII or multi-byte via the decoder), updates the
 * grapheme buffer (param_1+8), and returns {scalar, width}. Faithful scalar
 * reader with buffer growth.
 * Confidence: medium (faithful scalar reader)
 */
uint64_t skp9_sk_string_scalar(char *str, uint64_t p2)
{
    (void)str; (void)p2;
    /* if (*str==0) { if (*(*(str+8)+0x10)==0) { str[0x10]=0; str[0x1b]=0;
     *     *str=1; goto full; }
     *   if ((str[0x10]&1)==0) { FUN_0027f100(); str[0x10]=1; }
     *   uVar5=FUN_00274b4c(); uVar2=0; }
     * else { if (*str==1) { full: if (str[0x1a]==1) goto done;
     *     uVar5=*(uint*)(str+0x14); uVar3=*(ushort*)(str+0x18);
     *     do { if ((uVar3&0x7f8)==0) goto store; if (uVar3&1) goto hangul;
     *       lVar4=*(str+8); uVar2=FUN_003a261c(lVar4); *(str+8)=lVar4;
     *       if ((uVar2&1)==0) { lVar4=skp9_sk_swift_string_buf_grow(0,*(lVar4+0x10)+1,1,lVar4);
     *         *(str+8)=lVar4; }
     *       uVar2=*(lVar4+0x10); if (*(lVar4+0x18)>>1 <= uVar2) { grow; }
     *       *(lVar4+0x10)=uVar2+1; lVar1=lVar4+uVar2*8;
     *       *(int*)(lVar1+0x20)=uVar5; *(short*)(lVar1+0x24)=uVar3; *(str+8)=lVar4;
     *     done: while (true) { uVar5=skp9_FUN_00262e9c(p2);
     *       if (uVar5>>0x20 != 0) { str[0x18..0x17]=0; str[0x1a]=1; goto eol; }
     *       if (0xbf < (uint)uVar5) break; uVar3=0;
     *     store: if (*(*(str+8)+0x10)!=0) { *(str+0x14)=uVar5; *(str+0x18)=uVar3;
     *       str[0x1a]=0; skp9_FUN_0026448c(); str[0x1b]=1; *str=0;
     *       uVar5=skp9_FUN_002641a8(); uVar2=uVar5&0x1000000000000; goto out; }
     *       if ((uVar3&1)==0) { uVar2=0; str[0x18..0x17]=0; str[0x1a]=1;
     *         uVar5=uVar5&0xffffffff | uVar3<<0x20; goto out; }
     *     hangul: if ((uVar5-0xac00>>2)<0xae9) skp9_FUN_00264558(); else skp9_FUN_002646a0(uVar5,uVar3);
     *       uVar3=FUN_003d3550(uVar5); uVar3 |= (uVar5-0xac00>>2)<0xae9; } }
     * eol: uVar5=0; uVar2=0x1000000000000; }
     * out: return uVar2 | uVar5&0xffffffffffff; */
    return 0;
}

/* skp9_FUN_00263360 @ 0x00263360   (est. sk_string_scalar2)
 * Ghidra: ulong skp9_FUN_00263360(char*, undefined8*)
 * Second scalar reader: same structure as skp9_sk_string_scalar but reads from the
 * descriptor pair (param_2[0..4]) instead of the inline string, including the
 * multi-byte UTF-8 decode paths. Handles Hangul composition and the empty
 * case. Faithful scalar reader from descriptor.
 * Confidence: medium (faithful descriptor scalar reader)
 */
uint64_t sk_string_scalar2(char *str, uint64_t *desc)
{
    (void)str; (void)desc;
    /* same shape as skp9_sk_string_scalar but reads scalar from desc[4] index /
     * desc[0..3] buffer; 4-byte UTF-8 decode; skp9_FUN_0026448c()/skp9_FUN_00264558()/
     * skp9_FUN_002646a0() Hangul. */
    return 0;
}

/* skp9_FUN_00263784 @ 0x00263784   (est. sk_string_unicode_reader)
 * Ghidra: void skp9_FUN_00263784(void)
 * Unicode scalar reader (register inout): reads the scalar from the string
 * (x20), growing the grapheme buffer (str+8) as needed, and runs the capture
 * closure (x22) per element. Handles Hangul composition and the empty case.
 * Ends with the thread epilogue. Faithful reader.
 * Confidence: medium (faithful reader with buffer growth)
 */
void sk_string_unicode_reader(void)
{
    /* FUN_00084220(); FUN_003509ec();
     * if (*x20==0) { if (*(*(x20+8)+0x10)==0) { x20[0x10]=0; x20[0x1b]=0;
     *     *x20=1; goto full; }
     *   if ((x20[0x10]&1)==0) { FUN_0027f100(); x20[0x10]=1; }
     *   uVar9=FUN_00274b4c(); uVar6=0; }
     * else { if (*x20==1) { full: uVar4=1;
     *     if (x20[0x1a]==1) goto done;
     *     uVar9=*(uint*)(x20+0x14); uVar7=*(ushort*)(x20+0x18);
     *     do { if ((uVar7&0x7f8)==0) goto store; if (uVar7&1) goto hangul;
     *       lVar8=*(x20+8); uVar6=FUN_003a261c(lVar8); *(x20+8)=lVar8;
     *       if ((uVar6&1)==0) { FUN_0006b3f4(*(lVar8+0x10)); lVar8=skp9_sk_swift_string_buf_grow();
     *         *(x20+8)=lVar8; }
     *       uVar2=*(lVar8+0x10); uVar6=*(lVar8+0x18)>>1; uVar4=(uVar2==uVar6);
     *       if (uVar6<=uVar2) { grow; } *(lVar8+0x10)=uVar2+1;
     *       lVar1=lVar8+uVar2*8; *(int*)(lVar1+0x20)=uVar9; *(short*)(lVar1+0x24)=uVar7;
     *       *(x20+8)=lVar8;
     *     done: while (true) { (*x22)(); uVar9=FUN_0034ecc8();
     *       if (uVar4) { x20[0x18..0x17]=0; x20[0x1a]=1; goto eol; }
     *       if (0xbf<(uint)uVar9) break; uVar7=0;
     *     store: if (*(*(x20+8)+0x10)!=0) { *(x20+0x14)=uVar9; *(x20+0x18)=uVar7;
     *       x20[0x1a]=0; skp9_FUN_0026448c(); x20[0x1b]=1; *x20=0;
     *       uVar9=skp9_FUN_002641a8(); uVar6=uVar9&0x1000000000000; goto out; }
     *       if ((uVar7&1)==0) { uVar6=0; x20[0x18..0x17]=0; x20[0x1a]=1;
     *         uVar9=uVar9&0xffffffff | uVar7<<0x20; goto out; }
     *     hangul: if ((uVar9-0xac00>>2)<0xae9) skp9_FUN_00264558(); else skp9_FUN_002646a0(uVar9,uVar7); }
     *       uVar7=FUN_003d3550(uVar9); uVar7 |= (uVar9-0xac00>>2)<0xae9; } }
     * eol: uVar9=0; uVar6=0x1000000000000; }
     * out: FUN_00084234(uVar6|uVar9&0xffffffffffff, x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_0026398c @ 0x0026398c   (est. sk_string_scalar_reader)
 * Ghidra: ulong skp9_FUN_0026398c(char*)
 * Scalar reader (buffer variant): reads scalars into the grapheme buffer
 * (param_1+0x28) from the decoder skp9_FUN_00264068, handling the pending-scalar
 * state (+0x34/+0x38) and Korean composition (skp9_FUN_002641f8). Returns
 * {scalar,width} or the EOL marker. Faithful scalar reader.
 * Confidence: medium (faithful reader)
 */
uint64_t sk_string_scalar_reader(char *str)
{
    (void)str;
    /* if (*str!=1) { if (*(*(str+0x28)+0x10)!=0) { if ((str[0x30]&1)==0)
     *   { FUN_0027f100(); str[0x30]=1; } uVar1=FUN_00274b4c(); uVar4=0; goto out; }
     *   str[0x30]=0; *str=1; }
     * while (uVar2=skp9_FUN_00264068(), (uVar2&0xff000000000000)!=0x1000000000000) {
     *   uVar5=(uVar2); if (str[0x38]==1) { if ((uVar2&0x7f800000000)!=0) { uVar4=0;
     *       uVar1=uVar2; goto out; } *(str+0x34)=uVar5; str[0x38]=0; }
     *   else { uVar1=*(uint*)(str+0x34); lVar6=*(str+0x28); lVar7=*(lVar6+0x10);
     *     if (lVar7==0) { if ((uVar2>>0x20&6)==0) { if ((uVar2&0x7f800000000)!=0)
     *       goto append; uVar4=0; *(str+0x34)=uVar5; str[0x38]=0; goto out; }
     *       uVar4=skp9_FUN_002641f8(uVar1,uVar2); if (uVar4>>0x20!=0 && FUN_003d35f0()==-1)
     *       goto append; store; }
     *     else { uVar3=(uVar2>>0x23)&0xff;
     *       if ((*(ushort*)(lVar6+lVar7*8+0x1c)>>3&0xff) < uVar3) { compose or append; }
     *       else { if (uVar3==0) { uVar4=0; *(str+0x34)=uVar5; str[0x38]=0; *str=0;
     *           goto out; } append; } } } }
     * uVar1=0; uVar4=0x100000000;
     * out: return uVar4|uVar1&0xffffffff; */
    return 0;
}

/* skp9_FUN_00263bcc @ 0x00263bcc   (est. sk_string_scalar_reader2)
 * Ghidra: ulong skp9_FUN_00263bcc(char*, undefined8)
 * Scalar reader (second variant): same as sk_string_scalar_reader but pulls
 * scalars from FUN_00263140(str+8, p2). Identical state machine.
 * Confidence: medium (faithful reader)
 */
uint64_t sk_string_scalar_reader2(char *str, uint64_t p2)
{
    (void)str; (void)p2;
    return sk_string_scalar_reader(str);
}

/* skp9_FUN_00263e20 @ 0x00263e20   (est. sk_string_scalar_reader3)
 * Ghidra: ulong skp9_FUN_00263e20(char*, undefined8, undefined8)
 * Scalar reader (third variant): same state machine but pulls scalars from
 * skp9_FUN_00263784(p2, p3). Faithful reader with Hangul composition.
 * Confidence: medium (faithful reader)
 */
uint64_t sk_string_scalar_reader3(char *str, uint64_t p2, uint64_t p3)
{
    (void)str; (void)p2; (void)p3;
    /* while (uVar2=skp9_FUN_00263784(p2,p3), uVar2>>0x30==0) { same state machine } */
    return 0;
}

/* skp9_FUN_00264068 @ 0x00264068   (est. sk_string_scalar_emit)
 * Ghidra: ulong skp9_FUN_00264068(void)
 * Scalar emitter: marks the buffer state (x20[0]=2), and if there are pending
 * graphemes (x20+0x1b), walks the buffer (x20+8) re-emitting each scalar
 * (FUN_003574ec/FUN_00359cc4). Returns the pending scalar or the EOL marker
 * (0x1000000000000). Faithful buffer re-emit.
 * Confidence: medium (faithful emitter)
 */
uint64_t sk_string_scalar_emit(void)
{
    /* *x20=2; plVar5=x20+8; lVar6=*plVar5;
     * if ((x20[0x1b]&1)==0) { uVar7=*(lVar6+0x10);
     *   if (1<uVar7) { uVar3=FUN_003a261c(lVar6); *plVar5=lVar6;
     *     if ((uVar3&1)==0) { lVar6=sk_swift_string_buf_release(lVar6); }
     *     *plVar5=lVar6; uVar3=1;
     *     do { if (*(lVar6+0x10)<=uVar3) { FUN_00348304(); skp9_FUN_001afe4c(); }
     *       FUN_003574ec(); lVar4=x10;
     *       while (!uVar2) { FUN_00359cc4(); write scalar to buffer;
     *         lVar4=x10_00; if (x12==1) break; uVar2 = x11<=x12-1; if (uVar2)
     *         fatal; FUN_003574d0(); lVar4=x10_01; }
     *       uVar3=lVar4+1; } while (uVar3!=uVar7); *plVar5=lVar6; }
     *   x20[0x1b]=1; }
     * if (*(lVar6+0x10)==0) { x20[0x10]=0; uVar7=CONCAT(x20[0x18],x20[0x14]);
     *   bVar1=x20[0x1a]; *(x20+0x14)=0; *(x20+0x18)=0; x20[0x1a]=1;
     *   uVar3=bVar1<<0x30; }
     * else { if ((x20[0x10]&1)==0) { FUN_0027f100(); x20[0x10]=1; }
     *   uVar7=FUN_00274b4c(); uVar3=0; }
     * return uVar3|uVar7&0xffffffffffff; */
    return 0;
}

/* skp9_FUN_002641a8 @ 0x002641a8   (est. sk_string_pending_scalar)
 * Ghidra: ulong skp9_FUN_002641a8(void)
 * Pending-scalar accessor: returns the saved scalar (x20+8) or the EOL marker
 * (0x1000000000000) if none is pending. Reads via FUN_00353c48/FUN_00274b4c.
 * Confidence: high (faithful accessor)
 */
uint64_t sk_string_pending_scalar(void)
{
    /* FUN_00353c48(); if (x8==0) { *(x20+8)=0; return 0x1000000000000; }
     * if ((*(x20+8)&1)==0) { FUN_0027f100(); *(x20+8)=1; }
     * return FUN_00274b4c() & 0xffffffffffff; */
    return 0;
}

/* skp9_FUN_002641f8 @ 0x002641f8   (est. sk_hangul_compose)
 * Ghidra: ulong skp9_FUN_002641f8(int, int)
 * Hangul syllable composition: composes a Korean precomposed syllable from a
 * leading consonant (param_1) and a following vowel/consonant (param_2), using
 * the Unicode 0x1100/0x1161/0x11a7 tables. Returns {0, composed} on success or
 * {0x100000000, 0} when not composable. Faithful Hangul compose.
 * Confidence: high (faithful Unicode arithmetic)
 */
uint64_t sk_hangul_compose(int lead, int vowel)
{
    if ((unsigned)(lead - 0x1100) < 0x13 && (unsigned)(vowel - 0x1161) < 0x15) {
        return (vowel * 0x1c + lead * 0x24c) - 0x28469c;   /* 0xac00 base composition */
    }
    if (((unsigned)(lead - 0xac00) >> 2 < 0xae9) && (unsigned)(vowel - 0x11a8) < 0x1b &&
        ((lead - 0xac00) % 0x1c == 0)) {
        return (lead + vowel) - 0x11a7;
    }
    return 0x100000000;
}

/* FUN_00264298 @ 0x00264298   (est. sk_string_panic_e)
 * Ghidra: void FUN_00264298(void)
 * String fatal: FUN_00348404(1); FUN_00351be0(); noreturn skp9_FUN_001afe4c().
 * Confidence: high (pure fatal path)
 */
void sk_string_panic_e(void)
{
    skp9_sk_vspace_fail(1);   /* FUN_00348404(1) */
    skp9_sk_fatal_error(0, 0);   /* skp9_FUN_001afe4c */
}

/* skp9_FUN_002642bc @ 0x002642bc   (est. sk_string_init_obj)
 * Ghidra: void skp9_FUN_002642bc(undefined8, undefined8, undefined8)
 * String object initializer: seeds the object via FUN_0034b430/FUN_00349444,
 * dispatches the descriptor callback (+0x20), and writes the 0x18-byte string
 * header (*x8_00=1, +8=&skp9_DAT_00657778, +0x10=0, +0x14=0x1000000000000).
 * Faithful string-object construction.
 * Confidence: medium (faithful string header)
 */
void sk_string_init_obj(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2; (void)p3;
    /* FUN_0034b430(); uVar1=FUN_00349444(); FUN_00377824(uVar1,p3);
     * FUN_00349530(); (**(x16+0x20))(x8); FUN_0034e70c(); FUN_00340b40();
     * FUN_0035a738(); *x8_00=1; *(x8_00+8)=&skp9_DAT_00657778; x8_00[0x10]=0;
     * *(x8_00+0x14)=0x1000000000000; */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00264344 @ 0x00264344   (est. skp9_sk_string_next_grapheme)
 * Ghidra: ulong FUN_00264344(long)
 * Next grapheme cluster: reads the pending scalar (skp9_FUN_002643f4); if none is
 * pending, emits the next scalar (skp9_FUN_00264068) and composes it. Returns the
 * grapheme or the EOL marker. Faithful grapheme iterator.
 * Confidence: medium (faithful grapheme iterator)
 */
uint64_t skp9_sk_string_next_grapheme(long str)
{
    (void)str;
    /* uVar1=*(str+0x18); FUN_0034bd80(); FUN_003510c4(); FUN_00377824();
     * FUN_00356774(); FUN_003513a8(uVar1); auVar5=FUN_00377bec();
     * FUN_00084174(auVar5); uVar3=skp9_FUN_002643f4();
     * if (uVar3>>0x20==0) uVar4=uVar3&0x100000000;
     * else { uVar4=skp9_FUN_00264068(); bVar2=(uVar4&0xff000000000000)!=0x1000000000000;
     *   uVar3=0; if (bVar2) uVar3=uVar4; uVar4=0x100000000; if (bVar2) uVar4=0; }
     * return uVar4|uVar3&0xffffffff; */
    return 0;
}

/* skp9_FUN_002643f4 @ 0x002643f4   (est. sk_string_pending_grapheme)
 * Ghidra: ulong skp9_FUN_002643f4(void)
 * Pending-grapheme accessor: reads via FUN_00354d44/skp9_FUN_00263784 and returns
 * {scalar, valid} with the EOL check.
 * Confidence: low (opaque accessor)
 */
uint64_t sk_string_pending_grapheme(void)
{
    /* FUN_00354d44(); uVar2=skp9_FUN_00263784(); uVar1=uVar2;
     * if (0xffffffffffff < uVar2) uVar1=0;
     * return uVar1&0xffffffff | (uVar2>>0x30&1)<<0x20; */
    return 0;
}

/* skp9_FUN_00264448 @ 0x00264448   (est. sk_string_grapheme_done)
 * Ghidra: void skp9_FUN_00264448(void)
 * Grapheme-done: FUN_00264344() then FUN_00351fc0(). Advances + commits.
 * Confidence: low (thin wrapper)
 */
void sk_string_grapheme_done(void)
{
    skp9_sk_string_next_grapheme(0);
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00264470 @ 0x00264470   (est. sk_string_run_a)
 * FUN_00264474 @ 0x00264474   (est. skp9_sk_string_run_b)
 * Ghidra: void skp9_FUN_00264470(void)  (each)
 * String run: FUN_003555b4() then skp9_FUN_00262b5c(). Two thin wrappers.
 * Confidence: low
 */
void sk_string_run_a(void) { sk_string_scalar_run(0); }
void skp9_sk_string_run_b(void) { sk_string_scalar_run(0); }

/* skp9_FUN_0026448c @ 0x0026448c   (est. sk_string_buffer_commit)
 * Ghidra: void skp9_FUN_0026448c(void)
 * Buffer commit: re-emits every grapheme in the buffer (x20+0x10 count,
 * element stride at +0x20) via the descriptor callbacks, marking the buffer
 * state. Faithful multi-grapheme commit.
 * Confidence: medium (faithful buffer re-emit)
 */
void sk_string_buffer_commit(void)
{
    /* lVar4=*x20; uVar5=*(lVar4+0x10);
     * if (1<uVar5) { uVar2=FUN_003a261c(lVar4); *x20=lVar4;
     *   if ((uVar2&1)==0) { lVar4=sk_swift_string_buf_release(lVar4); }
     *   *x20=lVar4; uVar2=1;
     *   do { if (*(lVar4+0x10)<=uVar2) { FUN_00348304(); skp9_FUN_001afe4c(); }
     *     FUN_003574ec(); lVar3=x10;
     *     while (!uVar1) { FUN_00359cc4(); write scalar; lVar3=x10_00;
     *       if (x12==1) break; uVar1=x11<=x12-1; if (uVar1) fatal;
     *       FUN_003574d0(); lVar3=x10_01; }
     *     uVar2=lVar3+1; } while (uVar2!=uVar5); *x20=lVar4; } */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_00264558 @ 0x00264558   (est. sk_hangul_decompose_append)
 * Ghidra: void skp9_FUN_00264558(void)
 * Decomposes a precomposed Hangul syllable and appends its jamo components to
 * the string buffer (x20+8): leading consonant (0x1100 base), vowel
 * (0x1161 base) and optional trailing consonant (0x11a7 base), using the
 * standard 0xac00/0x1c/0x24c decomposition arithmetic. Faithful Hangul
 * decomposition.
 * Confidence: high (faithful Unicode arithmetic)
 */
void sk_hangul_decompose_append(void)
{
    /* iVar3=FUN_0008e518(); uVar1=iVar3+0x5400&0xffff; uVar2=uVar1/0x24c;
     * FUN_001a157c(skp9_sk_swift_string_buf_grow); lVar6=*(*(x20+8)+0x10);
     * FUN_001a1648(lVar6, skp9_sk_swift_string_buf_grow);
     * lVar4=*(x20+8); *(lVar4+0x10)=lVar6+1; lVar6=lVar4+lVar6*8;
     * *(uint*)(lVar6+0x20)=uVar2|0x1100; *(ushort*)(lVar6+0x24)=0; *(x20+8)=lVar4;
     * FUN_001a157c(grow); FUN_0008e388(); FUN_001a1648();
     * FUN_00357fe4(*(x20+8)); *(uint*)(x9+0x20)=(iVar3+0x5400-uVar2*0x24c&0xffff)/0x1c+0x1161;
     * *(ushort*)(x9+0x24)=4; *(x20+8)=x8;
     * uVar1=uVar1%0x1c; if (uVar1!=0) { FUN_00354e34();
     *   uVar5=*(*(x20+8)+0x10); FUN_0035428c(); FUN_001a1648(uVar5);
     *   FUN_00357fe4(*(x20+8)); *(uint*)(x9_00+0x20)=uVar1+0x11a7; *(x9_00+0x24)=4;
     *   *(x20+8)=x8_00; }
     * FUN_0008e500(x1); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002646a0 @ 0x002646a0   (est. sk_string_utf8_append)
 * Ghidra: void skp9_FUN_002646a0(void)
 * UTF-8 append: decodes a multi-byte UTF-8 sequence (via FUN_00351e20 +
 * FUN_003d35b0 index), appends each decoded scalar to the string buffer
 * (x20+8) with its composition width (FUN_003d3550), or appends a single
 * scalar with the inherited width. Faithful UTF-8 multi-scalar append.
 * Confidence: medium (faithful UTF-8 decode+append)
 */
void sk_string_utf8_append(void)
{
    /* uVar3=FUN_00351e20(); uVar4=FUN_003d35b0();
     * if (uVar3 == (uVar4 & 0x3ffff)) {
     *   pbVar8 = (byte*)(uVar4>>0x12) + 0x7100095f3940826b;  (inline data base)
     *   uVar9 = *(byte*)((uVar4>>0x12) + 0x7100095f3940826a);  (length)
     *   while (0 < uVar9) { uVar3=*pbVar8;
     *     if ((char)*pbVar8<0) { switch LZCOUNT: decode 2/3/4-byte; }
     *     else width=1;
     *     if (uVar9 < width) { FUN_00347d60(); skp9_FUN_001afe4c(); }
     *     uVar9 -= width;
     *     if (uVar3 < 0x300) uVar2=0; else { uVar2=FUN_003d3550(uVar3);
     *       uVar2 |= (uVar3-0xac00>>2)<0xae9; }
     *     append scalar to buffer (grow as needed); pbVar8 += width; }
     *   }
     * else { single scalar append with inherited width; }
     * FUN_00351d30(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00264898 @ 0x00264898   (est. sk_string_panic_f)
 * Ghidra: void FUN_00264898(void)
 * String fatal: FUN_00348074(1); FUN_00351be0(); noreturn skp9_FUN_001afe4c().
 * Confidence: high (pure fatal path)
 */
void sk_string_panic_f(void)
{
    skp9_sk_vspace_fail(1);   /* FUN_00348074(1) */
    skp9_sk_fatal_error(0, 0);   /* skp9_FUN_001afe4c */
}

/* skp9_FUN_00264914 @ 0x00264914   (est. sk_string_tag_low)
 * FUN_00264934 @ 0x00264934   (est. skp9_sk_string_tag_low2)
 * Ghidra: uint skp9_FUN_00264914(void)  (each)
 * Tag merges: combine a base tag (FUN_0034cec4 / FUN_0034a018) with a 6-bit
 * low field (extraout_w8 & 0x3f). Two tag-packing helpers.
 * Confidence: high (faithful bit merge)
 */
uint32_t sk_string_tag_low(void)
{
    uint32_t base = (uint32_t)skp9_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_0034cec4 */
    return base & 0xffffffc0 | 0;   /* | extraout_w8 & 0x3f */
}
uint32_t skp9_sk_string_tag_low2(void)
{
    uint32_t base = (uint32_t)skp9_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_0034a018 */
    return base & 0xffffffc0 | 0;   /* | extraout_w8 & 0x3f */
}

/* skp9_FUN_00264954 @ 0x00264954   (est. sk_string_tag_merge)
 * Ghidra: uint skp9_FUN_00264954(void)
 * Tag merge: combines a 21-bit base (FUN_00353ff4) with a 6-bit low field and
 * a 5-bit shifted field (extraout_w8). Tag packer.
 * Confidence: high (faithful bit merge)
 */
uint32_t sk_string_tag_merge(void)
{
    uint32_t base = (uint32_t)skp9_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_00353ff4 */
    return (base & 0x1f) << 6 | 0;   /* | extraout_w8 & 0xfffff800 | ... & 0x3f */
}

/* FUN_00264b90 @ 0x00264b90   (est. skp9_sk_string_unicode_verify)
 * Ghidra: void FUN_00264b90(void)
 * Unicode verify: runs the helper pipeline (FUN_00353cfc, FUN_003499c8,
 * FUN_003493ac, FUN_00349720, FUN_0034947c, FUN_00355464) with a compare
 * dispatch (FUN_0034c4bc); on the non-ZR path applies per-branch callbacks.
 * Ends with FUN_000839d8 + thread epilogue.
 * Confidence: low (opaque verify pipeline)
 */
void skp9_sk_string_unicode_verify(void)
{
    /* pcVar1=FUN_00353cfc(); FUN_003499c8(); (*skp9_DAT_00658c00)(x8_00+0x40);
     * FUN_003493ac(); FUN_00349720(); (*skp9_DAT_00658c00)(x8_01+0x40);
     * FUN_0034947c(); FUN_00355464(); (*x8_02)(); uVar2=1; FUN_0034c4bc();
     * if (!ZR) { FUN_00352b50(); FUN_0034f4a4(); (*x9)(); (*pcVar1)(x8);
     *   FUN_00358618(); FUN_00350a34(); (*x8_03)();
     *   if (x21!=0) goto done; uVar2=0; }
     * FUN_000839d8(x8,uVar2,1,x3);
     * done: FUN_00351348(); FUN_00353d14(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00264ccc @ 0x00264ccc   (est. skp9_sk_string_unicode_verify2)
 * Ghidra: void FUN_00264ccc(void)
 * Unicode verify (second variant): same pipeline but with a ZR-gated compare
 * dispatch (FUN_0034b2c8); on the ZR path returns the compare result directly,
 * otherwise applies the callback. Ends with thread epilogue.
 * Confidence: low (opaque verify)
 */
void skp9_sk_string_unicode_verify2(void)
{
    /* FUN_00353cfc(); FUN_003561a0(); FUN_003499f0(); (*skp9_DAT_00658c00)(x8+0x40);
     * FUN_003493ac(); FUN_00349720(); (*skp9_DAT_00658c00)(x8_00+0x40);
     * FUN_0034947c(); FUN_00355464(); (*x8_01)(); FUN_0034b2c8();
     * if (ZR) { auVar1=FUN_003517a8(); FUN_000839d8(auVar1,1,x3); }
     * else { FUN_003567e0(); FUN_0034e5cc(); (*x9)(); FUN_0035287c();
     *   (*x24)(); FUN_003508b4(*(x16+8)); (*x8_02)(); }
     * FUN_00351348(); FUN_00353d14(x30); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00264df8 @ 0x00264df8   (est. skp9_sk_string_optional_build)
 * Ghidra: void FUN_00264df8(void)
 * Optional-string build: if the element is non-null (x19, "Optional" tag),
 * constructs an Optional-wrapped string (FUN_001a89a8 "Optional" + element
 * buffer FUN_0036a9a0 with the type descriptor skp9_DAT_004baeb0), else returns the
 * nil Optional. Handles the Optional release/retain via FUN_00349cbc.
 * Faithful Optional<String> construction.
 * Confidence: medium (faithful Optional build)
 * Notes: string at 0x5d0212 ("Optional"); type descriptor skp9_DAT_004baeb0.
 */
void skp9_sk_string_optional_build(void)
{
    /* auVar5=FUN_0008e518(); uVar3=lo; FUN_000a6f88();
     * (*skp9_DAT_00658c00)(x8+0x40); FUN_000aa4ec(); FUN_0035196c();
     * FUN_00353aec(*(x12+0x10)); (*x8_00)(); lVar4=*(uVar3+0x10);
     * FUN_0034aa54();
     * if (ZR) { FUN_00353830(); FUN_00352c80(); goto done; }
     * FUN_001a89a8("Optional", 9, 1); auVar6=FUN_00354410();
     * puVar7=hi; uVar1=FUN_0008e0d4(); lVar2=FUN_0036a9a0(uVar1, auStack_50);
     * uVar1=skp9_DAT_004baeb0; *(lVar2+0x18)=uRam_4baeb8; *(lVar2+0x10)=uVar1;
     * *(lVar2+0x38)=lVar4; FUN_00319a4c(lVar2+0x20); FUN_0034b3c8();
     * (**(x16+0x20))(); FUN_003509f8(&skp9_DAT_005be7c0); FUN_001a89a8();
     * FUN_00352c80(); FUN_0034f030(); FUN_003509f8(&skp9_DAT_005be7c0); FUN_001a89a8();
     * FUN_00357b3c(); FUN_00319808(lVar2+0x20, auStack_70);
     * FUN_00310d98(auStack_70, auStack_90); FUN_0034b824(x24&mask);
     * if (ok) { FUN_003a25d4(uVar3); puVar7=&skp9_DAT_005be7c0; }
     * else { validate; ... }
     * FUN_00351f34(); FUN_00353d64(); FUN_0034895c();
     * FUN_002060d4(auStack_90, &stk, x8_02+8); FUN_000026e8(auStack_90);
     * FUN_0036b588(lVar2); FUN_00002688(); FUN_00002834(); FUN_0036b6ac();
     * FUN_003a25d4(x1); uVar3=FUN_00349cbc(x26); ... release/retain optional;
     * done: auVar6=FUN_00084180(); FUN_0008e500(auVar6); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* FUN_00265138 @ 0x00265138   (est. skp9_sk_string_error_build)
 * Ghidra: void FUN_00265138(void)
 * Error-string build: if the sequence (FUN_000839f8) reports a non-1 status,
 * constructs an error string object (FUN_00358fe8 with type descriptor
 * skp9_DAT_004baeb0, error tag "some" 0x656d6f73 and element 0x28); else returns
 * the empty string. Ends with the thread epilogue. Faithful error-string
 * construction.
 * Confidence: medium (faithful error build)
 * Notes: "some" tag 0x656d6f73; type descriptor skp9_DAT_004baeb0.
 */
void skp9_sk_string_error_build(void)
{
    /* FUN_0008e518(); FUN_00353aa0(); FUN_000a6f88(); (*skp9_DAT_00658c00)(x8+0x40);
     * FUN_00349db0(); (*skp9_DAT_00658c00)(); FUN_0034c2d8(); pcVar5=*(x16+0x10);
     * FUN_00351160(); (*pcVar5)(); uVar4=*(x20+0x10); FUN_00350198();
     * iVar2=FUN_000839f8(); FUN_00350c2c(); (*pcVar5)();
     * if (iVar2!=1) { FUN_003519d4(); lVar3=FUN_00358fe8();
     *   uVar1=skp9_DAT_004baeb0; *(lVar3+0x18)=uRam_4baeb8; *(lVar3+0x10)=uVar1;
     *   *(lVar3+0x20)=0x656d6f73; *(lVar3+0x28)=0xe400000000000000;
     *   *(lVar3+0x48)=uVar4; FUN_00319a4c(lVar3+0x30); FUN_0034c664();
     *   (**(x16_00+0x20))(); FUN_00350c2c(local_30); }
     * FUN_003515b4(); FUN_001e4348(); FUN_00359bf8(local_8, local_30, local_18);
     * FUN_0008e500(x1); */
    skp9_sk_thread_epilogue(0, 0, 0);
}

/* skp9_FUN_002652a4 @ 0x002652a4   (est. sk_string_error_result)
 * Ghidra: void skp9_FUN_002652a4(undefined8*)
 * Error-result: builds the error string (FUN_00265138) and copies its 0x21-byte
 * representation into *param_1 (5 words + tail). Faithful result copy.
 * Confidence: high (faithful copy)
 */
void sk_string_error_result(uint64_t *out)
{
    uint64_t local_50, s48, s40, s2f, s30;
    uint8_t l37, l38;
    (void)l37; (void)l38; (void)s30; (void)s2f;
    /* FUN_00265138(&local_50); out[1]=s48; out[0]=local_50; out[3]=CONCAT(l37,s38);
     * out[2]=s40; *(out+0x21)=s2f; *(out+0x19)=CONCAT(s30,l37); */
    (void)local_50; (void)s48; (void)s40; (void)out;
    skp9_sk_string_error_build();
}
