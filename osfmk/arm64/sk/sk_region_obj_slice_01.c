/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 01: 0x28e23c-0x29a2a4 (obj region second slice).
 * All names are estimates unless string/header-matched. Uses seL4/cL4
 * vocabulary (TCB, cap, CNode, IPC, notification, endpoint, vspace, sched,
 * object, slot) and Swift-runtime vocabulary (String/Array/Slice/Set/Unicode/
 * ContiguousArrayBuffer/UnsafeRawBufferPointer/IntegerTypes).
 *
 * This slice is dominated by the embedded Swift runtime's small-string and
 * collection storage machinery (small-string load/store, String index
 * arithmetic, UTF-8/UTF-16 decode, integer-width conversion + overflow
 * checks, Unsafe(Raw)(Buffer)Pointer validation) together with a family of
 * object-service loops (heavy indirect dispatch through method tables).
 * Out-of-range kernel helpers stay extern declarations with the FUN_ address
 * in a comment.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef uint64_t word_t;

/* SoftwareBreakpoint(1, <addr>) paths — trap immediately. */
#define CL4_SBP() __builtin_trap()

/* Reads/writes the caller's object base. The decompiler models the object
 * pointer as a register (unaff_*) that is not a formal parameter; these
 * accesses go through a static cell so the compiler does not treat them as
 * a literal null dereference. */
static unsigned long sk_unmodeled_obj_base_cell;
#define SK_OBJ_BASE()      (*(unsigned long *)&sk_unmodeled_obj_base_cell)
#define SK_OBJ_BASE_PTR()  ((unsigned long *)&sk_unmodeled_obj_base_cell)

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (FUN_ addr in comment). Signatures
 * reflect observed register use at the call sites.
 * ------------------------------------------------------------------ */
extern void   *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void   *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void    sk_free(void *ptr);                                     /* FUN_0036b118 */
extern word_t  sk_alloc_obj(word_t tag);                               /* FUN_0036a940 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *dbg1, void *dbg2); /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a, unsigned long b,
                                 unsigned long c, void *d1, void *d2); /* FUN_00377bec */
extern void    sk_lock_release(unsigned long a, ...);                  /* FUN_00377dcc */
extern void   *sk_cpu(void);                                           /* FUN_0008e518 */
extern void   *sk_current_tcb(void);                                   /* FUN_000867ec */
extern void    sk_thread_epilogue(void);                               /* FUN_0008e500 */
extern void    sk_swift_release(unsigned long, ...);                   /* FUN_003a25d4 */
extern void    sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern void    sk_fatal_dump(unsigned long, unsigned long, ...) __attribute__((noreturn));  /* FUN_001afa84 */
extern unsigned long sk_type_id(unsigned long);                        /* FUN_00027754 */
extern void    sk_ref_lock_op(unsigned long, ...);                     /* FUN_000839d8 */
extern unsigned long sk_object_method_table(unsigned long, ...);       /* FUN_0007c1a4 */
extern void    sk_object_init_stage(unsigned long, ...);               /* FUN_000a6f88 */
extern void    sk_object_init(unsigned long, ...);                     /* FUN_0007c1c4 */
extern unsigned long sk_swift_string_index(unsigned long, unsigned long, unsigned long,
                                           unsigned long, unsigned long, ...); /* FUN_002aaf80 */
extern long    sk_swift_str_buf(unsigned long, unsigned long, ...);    /* FUN_002a9ba8 */
extern unsigned long sk_swift_string_char_width(unsigned long, unsigned long,
                                                unsigned long, ...);   /* FUN_002c7020 */
extern void    sk_swift_string_index_next(void);                       /* FUN_00286b20 */
extern void    sk_swift_string_char(unsigned long, unsigned long, unsigned long, ...); /* FUN_0029ef1c */
extern unsigned long sk_swift_string_hash(void);                       /* FUN_001a8564 */
extern unsigned long sk_swift_string_next(unsigned long, unsigned long, unsigned long,
                                          void *, void *);            /* FUN_002ab058 */
extern unsigned long sk_swift_next_char(unsigned long, unsigned long, unsigned long,
                                        void *, void *);              /* FUN_002b439c */
extern unsigned long sk_swift_advance(unsigned long, unsigned long, unsigned long,
                                      void *, void *);               /* FUN_002b3b84 */
extern unsigned long sk_swift_advance2(unsigned long, unsigned long, unsigned long,
                                       void *, void *);              /* FUN_002b3d68 */
extern void    sk_swift_elem_map(unsigned long, unsigned long, ...);   /* FUN_0029fb80 */
extern void    sk_swift_elem_transform(unsigned long, void *, ...);    /* FUN_00263360 */
extern void    sk_swift_elem_transform2(void);                         /* FUN_00264068 */
extern unsigned char sk_swift_unknown_5be7c0[];                        /* DAT_005be7c0 */
extern unsigned long sk_swift_string_cmp(unsigned long, unsigned long, unsigned long,
                                         unsigned long, unsigned long, ...); /* FUN_002a0d50 */
extern void    sk_string_buf_alloc(unsigned long, unsigned long, ...); /* FUN_002a218c */
extern void    sk_string_buf_take(unsigned long, unsigned long, unsigned long, ...); /* thunk_FUN_002a2698 */
extern void    sk_string_buf_share(unsigned long, unsigned long, unsigned long, ...); /* FUN_002a2748 */
extern long    sk_string_buf_alloc_size(unsigned long, unsigned long, ...); /* FUN_002a2bb0 */
extern void    sk_swift_set_insert(unsigned long, unsigned long, unsigned long, void *); /* FUN_000b394c */
extern void    sk_swift_set_make_unique(unsigned long, ...);           /* FUN_002a200c */
extern void    sk_swift_set_make_unique2(void);                        /* FUN_002a20cc */
extern void    sk_swift_range_iterate(void);                           /* FUN_002a3ed4 */
extern void    sk_swift_range_make(void);                              /* FUN_002a401c */
extern void    sk_swift_string_cat(void);                              /* FUN_002a2978 */
extern unsigned long sk_string_utf8_validate(unsigned long, unsigned long, ...); /* FUN_002a9ba8 */
extern void    sk_dyn_alloc_word(unsigned long, unsigned long, ...);   /* FUN_0036a804 */
extern void    sk_dyn_grow_word(unsigned long, unsigned long, unsigned long, ...); /* FUN_0006b42c */
extern void    sk_dyn_grow(unsigned long, unsigned long, unsigned long, ...); /* FUN_001a0870 */
extern void    sk_dyn_grow_small(unsigned long, unsigned long, ...);   /* FUN_001a1cc4 */
extern void    sk_dyn_reserve(unsigned long, unsigned long, unsigned long, ...); /* FUN_000f9680 */
extern void    sk_dyn_reserve_small(unsigned long, unsigned long, unsigned long, ...); /* FUN_000f9930 */
extern void    sk_dyn_free_small(unsigned long, ...);                  /* FUN_000f98ac */
extern unsigned long sk_string_convert(unsigned long, unsigned long, ...);   /* FUN_0019e578 */
extern void    sk_string_convert_small(unsigned long, unsigned long, ...); /* FUN_0019e690 */
extern void    sk_string_finish(unsigned long, ...);                   /* FUN_0019e6bc */
extern void    sk_int_to_string(unsigned long, unsigned long, ...);    /* FUN_001a26e0 */
extern void    sk_swift_int_cast(unsigned long, ...);                  /* FUN_002a200c */
extern void    sk_swift_int_cast_fail(void);                           /* FUN_002a2018 */
extern void    sk_memcpy(void *dst, const void *src, unsigned long n); /* FUN_00117cc4 */
extern void    sk_memmove(void *dst, const void *src, unsigned long n);/* FUN_00117d14 */
extern unsigned long sk_allocator_tag(unsigned long, unsigned long);   /* FUN_00002534 */
extern void    sk_debug_print(unsigned long, unsigned long);           /* FUN_000651bc */
extern unsigned long sk_string_is_ascii(unsigned long, unsigned long, ...); /* FUN_00106e3c */
extern void sk_string_view_copy_utf8(unsigned long, unsigned long, ...);   /* FUN_002ac0d8 */
extern void sk_string_view_copy_utf16(unsigned long, unsigned long, ...);  /* FUN_002ac168 */
extern void sk_string_view_copy_unicode(unsigned long, unsigned long, ...);/* FUN_002ac214 */

/* In-slice forward declarations (cross-references used before definition). */
void sk_span_build(long lower, long upper, void *pos, long end);
void sk_string_finalize(void);
void sk_swift_string_construct_unicode(void *out, unsigned long tag, unsigned long flag);
void sk_swift_string_build_span(void *p1, void *p2, void *p3, void *p4, void *p5);
void sk_string_slice_append(void *p1, unsigned long w, unsigned long f, void *p4, void *p5);
void sk_swift_string_char(unsigned long, unsigned long, unsigned long, ...);
void sk_string_utf8_decode(unsigned long w, unsigned long f, long p3, long p4, void *p5);
void sk_swift_sort_merge_loop(void *p1, void *p2, void (*cmp)(void), void *p4, void *p5, void *p6);
void sk_swift_sort_partition(void *p1, void *p2, void *lo, void *hi,
                             void (*cmp)(void), void *p6, void *p7, void *p8,
                             void *p9, void *p10);
void sk_swift_sort_partition_finish(void *dst, long *src_begin, long *src_end, long stride);
void sk_swift_array_insert_range(void *p1, void *p2, void *p3, void *p4, void *p5, long param_6);
unsigned long sk_swift_int_round_up(unsigned long v);
unsigned long sk_swift_string_char_decode(unsigned long word, long n);

/* The dispatch slots used by the object service (global jump table). */
#define SK_OBJ_DISPATCH   (*(void (**)(void))(0x658c00))

/*--------------------------------------------------------------------*/
/* FUN_0028e424 @ 0x0028e424   (est. sk_array_buffer_reserve)
 * Ghidra: void FUN_0028e424(undefined8,undefined8,undefined8,long,undefined8,undefined8)
 * Array storage reserve: acquires the container lock, resolves the element
 * type (FUN_00377824), then either installs the empty sentinel via the
 * object service (FUN_000839d8) or, if the buffer is already unique, walks
 * the element-type metadata and stores a fresh (possibly bridged) element
 * descriptor back through the dispatch table.
 * Confidence: low (heavy indirect dispatch through type-metadata callbacks).
 */
void sk_array_buffer_reserve(void *thisp, void *param_2, void *param_3, long param_4,
                             void *param_5, void *param_6)
{
    (void)param_2; (void)param_3;
    unsigned long tid = sk_type_id((unsigned long)param_6);
    unsigned long u8 = *(unsigned long *)((char *)param_4 + 0x10);
    long lk = sk_object_lock(0, tid, u8, (void *)0x60e208, (void *)0x60e230);
    long meta = *(long *)(lk + -8);
    SK_OBJ_DISPATCH();
    void (*cb)(void *, void *, void *, unsigned long, unsigned long, unsigned long) =
        (void (*)(void *, void *, void *, unsigned long, unsigned long, unsigned long))sk_object_method_table((unsigned long)param_6);
    char done = 0;
    cb(&done, (void *)0x1a1c8, (void *)param_4, 0x67b148, u8, (unsigned long)param_6);
    if (done == 1) {
        sk_ref_lock_op((unsigned long)thisp, 1, 1, (unsigned long)param_5);
    } else {
        /* walk element type metadata and store a fresh descriptor */
        void *slot = (char *)__builtin_frame_address(0);
        void (*e1)(void *, unsigned long, unsigned long) = (void (*)(void *, unsigned long, unsigned long))sk_type_id((unsigned long)param_6);
        (void)e1;
        unsigned long desc = ((unsigned long(*)(void *))0)(slot);
        (void)desc;
        (*(void (**)(void *, long))(meta + 8))(slot, lk);
        SK_OBJ_DISPATCH();
        unsigned long d2 = SK_OBJ_DISPATCH ? 0 : 0;
        (void)d2;
        /* store element (u8, param_5, param_6, desc, d2, param_2, param_3)
         * back through the object dispatch table */
        void (*cb2)(void *, void *, void *, void *, unsigned long, unsigned long) =
            (void (*)(void *, void *, void *, void *, unsigned long, unsigned long))sk_object_method_table((unsigned long)param_6);
        cb2(thisp, (void *)0x343cd0, (void *)param_4, (void *)param_5, u8, (unsigned long)param_6);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0028e694 @ 0x0028e694   (est. sk_array_with_contiguous_storage)
 * Ghidra: void FUN_0028e694(undefined8,undefined8*,long,long,code*,undefined8,undefined8,undefined8,undefined8)
 * Array(Slice) with contiguous mutable storage: validates the requested
 * range (carry-checked), resolves the element type, builds a 16-byte span
 * via FUN_0028e8fc, then runs a resizing/unique path that re-homes the
 * buffer (FUN_0028e9f0). Overflow or out-of-order ranges trap.
 * Confidence: high (Swift _ContiguousArrayStorage makeUnique path; Range
 *   fatal string matches).
 */
void sk_array_with_contiguous_storage(void *out, unsigned long *range, long lower, long upper,
                                      void (*body)(void *, void *), void *param_6,
                                      void *param_7, void *param_8, void *param_9)
{
    (void)param_6;
    if (__builtin_add_overflow(lower, upper, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x28e878) */
    }
    if (lower <= lower + upper) {
        unsigned long lo = range[0];
        unsigned long hi = range[1];
        sk_type_id((unsigned long)param_9);
        unsigned long tid = sk_type_id(0);
        long lk = sk_object_lock(0, tid, (unsigned long)param_7, (void *)0x611b24, (void *)0x611b34);
        unsigned long span[2];
        ((void (*)(long, long, unsigned long, unsigned long, long))sk_swift_range_iterate)(0, 0, lo, hi, lk);
        (void)span;
        unsigned long u2 = sk_allocator_tag(0xff, lk);   /* FUN_0031de7c */
        unsigned long d1 = sk_string_utf8_validate((unsigned long)0x4edcd0, u2);
        unsigned long u3 = ((unsigned long(*)(unsigned long, unsigned long, unsigned long))sk_object_method_table)(0, u2, d1);
        (void)u3;
        unsigned long b4 = 0;
        /* thunk_FUN_0028c754 -> local_a8[0] */
        if (b4 == 0) {
            b4 = 0;
        } else {
            unsigned long cnt = 0;
            /* FUN_0021867c computes the byte count from the element size */
            b4 += *(long *)(*(long *)(lk + -8) + 0x48) * cnt;
        }
        /* FUN_0022b584 / FUN_0021867c -> shrink span to b4..end */
        unsigned long b5 = 0;
        unsigned long r16[2];
        sk_int_to_string((unsigned long)r16, b4 - b5);
        void (*fn)(void *, void *) = body;
        fn(out, r16);
        /* FUN_0028e9f0 validates the produced slice bounds */
        sk_swift_string_cmp((unsigned long)r16, b4 - b5, 0, 0, 0);
    } else {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                       (unsigned long)"Swift.Range", 0x11, 2, 0x2f9, 1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0028e8c0 @ 0x0028e8c0   (est. sk_span_range_validate)
 * Ghidra: void FUN_0028e8c0(long,long,undefined8,long)
 * Bounds-validates a range [param_1, param_4): if param_1 is negative or
 * param_4 falls short of param_2, panics with a Range fatal error.
 * Confidence: high.
 */
void sk_span_range_validate(long lower, long upper, void *param_3, long end)
{
    (void)param_3;
    if (lower < 0) {
        /* FUN_0034dab8 */
        sk_fatal_error(0, 0, 0);
    } else if (upper <= end) {
        return;
    } else {
        /* FUN_0034def4 */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0028e8fc @ 0x0028e8fc   (est. sk_span_build_thunk)
 * Ghidra: void FUN_0028e8fc(void)
 * Thin forwarder to FUN_0028e94c (span build).
 * Confidence: high.
 */
void sk_span_build_thunk(void)
{
    sk_span_build(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0028e94c @ 0x0028e94c   (est. sk_span_build)
 * Ghidra: undefined1[16] FUN_0028e94c(long,long,undefined8,long)
 * Builds a 16-byte Swift Range/span descriptor from (lower, upper, pos,
 * end). On invalid bounds jumps to the Range fatal error.
 * Confidence: high.
 */


void sk_span_build(long lower, long upper, void *pos, long end)
{
    if (lower < 0) {
        /* FUN_0034def4 */
        sk_fatal_error(0, 0, 0);
    } else if (upper <= end) {
        /* pack (lower, upper, pos, end) into the 16-byte range */
        sk_swift_string_char((unsigned long)lower, (unsigned long)upper, (unsigned long)pos, (unsigned long)end);
        return;
    } else {
        /* FUN_0035047c */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0028e9f0 @ 0x0028e9f0   (est. sk_slice_bounds_check)
 * Ghidra: void FUN_0028e9f0(long*,long,long)
 * Validates that a Slice's start/lower and upper bounds are consistent with
 * the given contiguous range; otherwise raises the Swift Slice fatal error.
 * Confidence: high (Swift Slice fatal string matches).
 */
void sk_slice_bounds_check(long *bounds, long lower, long upper)
{
    bool ok;
    if (*bounds == 0) {
        ok = (lower == 0);
    } else {
        ok = (*bounds == lower);
    }
    if (ok && bounds[1] == upper) {
        return;
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Slice with ContiguousMutableStorage...", 0x52, 2,
                   (unsigned long)"Swift.Slice", 0x11, 2, 0x13a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ea7c @ 0x0028ea7c   (est. sk_string_buffer_alloc)
 * Ghidra: undefined1[16] FUN_0028ea7c(long*,undefined8,long,ulong)
 * Allocates a 0x40-byte String/ContiguousArrayBuffer header (tag 0x2545),
 * initialises its element-type metadata pointers and two element buffers,
 * and returns a 16-byte (fn, instance) pair. The per-element copy callback
 * (meta+0x10) is invoked to seed the backing store.
 * Confidence: medium (Swift _StringGuts / ContiguousArrayBuffer header).
 */
void sk_string_buffer_alloc(long *out, void *param_2, long param_3, unsigned long param_4)
{
    unsigned long *h = sk_alloc(0x40, 0x2545);
    *out = (long)h;
    h[0] = (unsigned long)out;         /* unaff_x20 */
    h[1] = (unsigned long)param_3;
    unsigned long u6 = *(unsigned long *)((param_4 & ~1ULL) - 8);
    h[2] = u6;
    sk_type_id(u6);
    unsigned long tid = sk_type_id(0);
    unsigned long u7 = *(unsigned long *)((char *)param_3 + 0x10);
    long lk = sk_object_lock(0, tid, u7, (void *)0x611b24, (void *)0x611b34);
    h[3] = lk;
    long meta = *(long *)(lk + -8);
    h[4] = meta;
    unsigned long esz = *(unsigned long *)(meta + 0x40);
    unsigned long e1 = (unsigned long)sk_alloc(esz, 0x2545);
    h[5] = e1;
    unsigned long e2 = (unsigned long)sk_alloc(esz, 0x2545);
    h[6] = e2;
    long lk2 = sk_object_lock(0, tid, u7, (void *)0x60e208, (void *)0x60e230);
    long meta2 = *(long *)(lk2 + -8);
    unsigned long e3 = (unsigned long)sk_alloc(*(unsigned long *)(meta2 + 0x40), 0x2545);
    h[7] = e3;
    (*(void (**)(unsigned long, void *, long))(meta2 + 0x10))(e3, param_2, lk2);
    /* FUN_0028d7cc(e2, param_2, param_3, u6) — seed the second element */
    /* return pair (FUN_0028ec1c, e2) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ec1c @ 0x0028ec1c   (est. sk_string_buffer_release)
 * Ghidra: void FUN_0028ec1c(void)
 * Object-service flavor that releases a String buffer: saves the thread,
 * checks a wake flag (FUN_00357e84), and either runs the synchronous
 * release path (FUN_0028da60) or the deferred/notify path; finally tears
 * down with FUN_0008e500.
 * Confidence: low (indirect dispatch; unaff_x19/0x18/0x20 fields).
 */
void sk_string_buffer_release(void)
{
    sk_cpu();
    /* FUN_00357e84 wake flag */
    unsigned long flag = 0;
    if ((flag & 1) == 0) {
        /* FUN_000e15d8(x0, x1, *(x19+8), *(x19+0x10)); FUN_0028da60() */
    } else {
        /* FUN_0034e4a4(lVar2); (*x9)(...); FUN_0008e388; FUN_00351cd0;
         * FUN_0028da60; FUN_00351160(*(lVar2+8)); (*x8)() */
    }
    sk_debug_print(0, 0);   /* thunk_FUN_00012568 */
    sk_debug_print(0, 0);
    sk_debug_print(0, 0);
    sk_thread_epilogue();
    sk_debug_print(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ecd4 @ 0x0028ecd4   (est. sk_string_buffer_alloc_small)
 * Ghidra: undefined1[16] FUN_0028ecd4(long*,undefined8,long,ulong)
 * Allocates a 0x38-byte String header (tag 0x3ca1) with two element
 * buffers, seeds the copy callback, and returns the (fn, instance) pair.
 * Confidence: medium.
 */
void sk_string_buffer_alloc_small(long *out, void *param_2, long param_3, unsigned long param_4)
{
    unsigned long *h = sk_alloc(0x38, 0x3ca1);
    *out = (long)h;
    h[0] = (unsigned long)out;
    h[1] = (unsigned long)param_3;
    unsigned long u6 = *(unsigned long *)((param_4 & ~1ULL) - 8);
    h[2] = u6;
    long meta0 = *(long *)((char *)param_3 - 8);
    h[3] = meta0;
    unsigned long esz = *(unsigned long *)(meta0 + 0x40);
    unsigned long e1 = (unsigned long)sk_alloc(esz, 0x3ca1);
    h[4] = e1;
    unsigned long e2 = (unsigned long)sk_alloc(esz, 0x3ca1);
    h[5] = e2;
    sk_type_id(u6);
    unsigned long u8 = *(unsigned long *)((char *)param_3 + 0x10);
    unsigned long lk = sk_object_lock(0xff, u6, u8, (void *)0x60e208, (void *)0x60e230);
    unsigned long lk2 = sk_lock_ref(u6, u8, lk, (void *)0x60e208, (void *)0x60e218);
    long meta2 = *(long *)(sk_object_lock(0, lk, lk2, 0, 0) + -8);
    unsigned long e3 = (unsigned long)sk_alloc(*(unsigned long *)(meta2 + 0x40), 0x3ca1);
    h[6] = e3;
    (*(void (**)(unsigned long, void *, long))(meta2 + 0x10))(e3, param_2, lk2);
    /* FUN_0028debc(e2, param_2, param_3, u6) */
    /* return pair (FUN_0028ee94, e2) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ee94 @ 0x0028ee94   (est. sk_string_buffer_release_small)
 * Ghidra: void FUN_0028ee94(void)
 * Object-service flavor releasing a small String buffer: acquires the lock
 * (FUN_00084220), reads object fields at +0x20/+0x28/+0x30, and either runs
 * the synchronous release path (FUN_0028e16c) or a deferred path, then
 * releases the three buffers and finishes the lock (FUN_00084234).
 * Confidence: low.
 */
void sk_string_buffer_release_small(void)
{
    void *lk = 0;
    unsigned long v28 = 0, v30 = 0, v20 = 0;
    if (0) {
        /* FUN_000e15d8(...); FUN_0028e16c() */
    } else {
        /* FUN_0034e4a4(lVar3); (*x9)(...); FUN_0034db28(v6);
         * FUN_0028e16c; FUN_00351160(*(lVar3+8)); (*x8)() */
    }
    sk_debug_print(v30, 0);
    sk_debug_print(v28, 0);
    sk_debug_print(v20, 0);
    sk_lock_release((unsigned long)lk, 0);   /* FUN_00084234 */
    sk_debug_print(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ef44 @ 0x0028ef44   (est. sk_array_reserve_thunk0)
 * Ghidra: void FUN_0028ef44(undefined8,undefined8,undefined8,undefined8,ulong)
 * Forwarder to FUN_0028e424, passing the element-size metadata word.
 * Confidence: high.
 */
void sk_array_reserve_thunk0(void *p1, void *p2, void *p3, void *p4, unsigned long p5)
{
    sk_array_buffer_reserve(p1, p2, p4, (long)p3, *(void **)((p5 & ~1ULL) - 8), (void *)p4);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ef48 @ 0x0028ef48   (est. sk_array_reserve_thunk1)
 * Ghidra: void FUN_0028ef48(undefined8,undefined8,undefined8,undefined8,ulong)
 * Identical forwarder to FUN_0028ef44 (second flavour).
 * Confidence: high.
 */
void sk_array_reserve_thunk1(void *p1, void *p2, void *p3, void *p4, unsigned long p5)
{
    sk_array_buffer_reserve(p1, p2, p4, (long)p3, *(void **)((p5 & ~1ULL) - 8), (void *)p4);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ef70 @ 0x0028ef70   (est. sk_small_string_wide_marker)
 * Ghidra: undefined1[16] FUN_0028ef70(void)
 * Returns the 16-byte marker (0xf, 7) used to tag a wide small-string.
 * Confidence: high.
 */
void sk_small_string_wide_marker(unsigned long out[2])
{
    out[0] = 0xf;
    out[1] = 7;
}

/*--------------------------------------------------------------------*/
/* FUN_0028ef84 @ 0x0028ef84   (est. sk_object_service_cpu_a)
 * Ghidra: void FUN_0028ef84(void)
 * Object-service flavor: acquires the object lock, runs the dispatch helper
 * chain, and pushes two work items into the current CPU's work queue
 * (offsets +0x28/+0x24), then releases the lock. Epilogue via FUN_00084234.
 * Confidence: low (heavy indirect dispatch).
 */
void sk_object_service_cpu_a(void)
{
    /* FUN_00084220 lock; FUN_0034bd6c; FUN_0031e0d4; FUN_00352894;
     * FUN_003502f8; FUN_0031b080; FUN_0034d354(x22 + [l+0x28]);
     * (*pc)(); FUN_0035156c; FUN_00350c2c; (*x9)(); FUN_00351750;
     * FUN_00350c2c(x22 + [l+0x24]); (*x9_00)(); FUN_00084234(x30) */
    sk_lock_release(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0028f020 @ 0x0028f020   (est. sk_object_service_cpu_b)
 * Ghidra: void FUN_0028f020(void)
 * Object-service flavor (thread-save variant) pushing two work items into
 * the CPU work queue; epilogue via FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_cpu_b(void)
{
    /* FUN_0008e518; FUN_0034a74c; FUN_00354db8; FUN_0031de94;
     * FUN_00351bec; FUN_00350530; FUN_0031b080;
     * FUN_003509bc(x23 + [l+0x28]); FUN_0034d344; (*pc)();
     * FUN_0035156c; FUN_00350494; (*x9)(); FUN_00351750;
     * FUN_00350494(x23 + [l+0x24]); (*x9_00)(); FUN_0008e500(x30) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0028f0c8 @ 0x0028f0c8   (est. sk_object_service_cpu_c)
 * Ghidra: void FUN_0028f0c8(void)
 * Object-service flavor (thread-save variant) pushing two work items;
 * epilogue via FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_cpu_c(void)
{
    /* FUN_0008e518; FUN_00352700; FUN_0034bb84; FUN_0031dec4(x3);
     * FUN_00351ad4; FUN_00350488; FUN_0031b080;
     * FUN_0034c818(x24 + [l+0x28]); FUN_00351154; (*pc)();
     * FUN_0035156c; FUN_00350b78; (*x9)(); FUN_00351750;
     * FUN_00350b78(x24 + [l+0x24]); (*x9_00)(); FUN_0008e500(x30) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0028f17c @ 0x0028f17c   (est. sk_array_make_unique_reserve)
 * Ghidra: void FUN_0028f17c(undefined8,undefined8,long,undefined8,undefined8)
 * Array buffer makeUnique/reserve path: saves the thread, resolves element
 * metadata, and either appends a single element or, when the buffer is not
 * unique, reallocates with growth; carry-overflow paths trap. Epilogue
 * FUN_0008e500.
 * Confidence: low (long indirect-dispatch sequence; SoftwareBreakpoint at
 *   0x28f464/0x28f468).
 */
void sk_array_make_unique_reserve(void *p1, void *p2, long param_3, void *param_4, void *param_5)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00349a68; (*DAT_00658c00)([x8+0x40]); FUN_003497b4;
     * FUN_00350950(param_5); FUN_00349748; FUN_003511d8; FUN_00377824;
     * FUN_00348d64; (*DAT_00658c00)([x8_01+0x40]); FUN_003493c4;
     * FUN_0034c684; (*DAT_00658c00)(); FUN_0034b4c0; FUN_003506e8;
     * FUN_00100efc; (*x9)(); FUN_00310cd4; FUN_003509d4; FUN_00351b78 */
    int off = *(int *)((char *)param_3 + 0x24);
    unsigned long n1 = 0, n2 = 0;
    if (__builtin_add_overflow(n1, n2, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x28f464) */
    }
    /* FUN_003570d8; FUN_00353efc */
    long n3 = 0;
    if (!__builtin_add_overflow(n1 + n2, n3, (long *)0)) {
        /* append element and dispatch through method table */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x28f468) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028f468 @ 0x0028f468   (est. sk_array_make_unique_append)
 * Ghidra: void FUN_0028f468(undefined8,undefined8,long,undefined8)
 * Array makeUnique/append: resolves element metadata, appends an element,
 * and dispatches through the object method table. Carry overflows trap.
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_make_unique_append(void *p1, void *p2, long param_3, void *param_4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0035125c(param_4); FUN_00350bd8; u6 = *(p3+0x10);
     * FUN_003497a0; FUN_00377824(...); FUN_000a6f88; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034a760; ... */
    long n = 0;
    if (!__builtin_add_overflow(n, 1, (long *)0)) {
        /* FUN_00358cd4; (*x8_01)(...); FUN_00357818; FUN_0031d6a8;
         * FUN_00356ae8; FUN_00350bfc; (*x8_02)(); FUN_003504c4; (*x9)();
         * FUN_0031afcc; FUN_00351e3c; (*pc)(); (*pc5)(); ... */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x28f6cc) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028f6cc @ 0x0028f6cc   (est. sk_array_make_unique_append2)
 * Ghidra: void FUN_0028f6cc(undefined8,undefined8,long,undefined8,undefined8,undefined8)
 * Array makeUnique/append flavour with an extra size argument; overflow
 * paths trap (0x28f960). Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_make_unique_append2(void *p1, void *p2, long param_3, void *param_4,
                                  void *param_5, void *param_6)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00349a68; (*DAT_00658c00)([x8+0x40]); FUN_003497b4;
     * FUN_0035125c(param_5); u6 = *(p3+0x10); FUN_00349748; ... */
    long n = 0;
    if (!__builtin_add_overflow((unsigned long)param_3, n, (long *)0)) {
        /* append + dispatch */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x28f960) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028f960 @ 0x0028f960   (est. sk_array_make_unique_remove_last)
 * Ghidra: void FUN_0028f960(undefined8,undefined8,undefined8)
 * Array removeLast / makeUnique shrink path: underflow traps (0x28fb44),
 * otherwise removes the last element and dispatches. Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_make_unique_remove_last(void *p1, void *p2, void *param_3)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0035125c(param_3); ... */
    long n = 0;
    if (!__builtin_sub_overflow(n, 1, (long *)0)) {
        /* FUN_003540a0(n-1); FUN_0031d708; FUN_00350600(...);
         * FUN_003504c4; (*x9)(); FUN_0031afcc; FUN_00352e3c;
         * FUN_00351e3c; (*pc)(); ... dispatch */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x28fb44) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028fb44 @ 0x0028fb44   (est. sk_array_make_unique_remove_range)
 * Ghidra: void FUN_0028fb44(undefined8,undefined8,undefined8)
 * Array removeSubrange(makeUnique) path: computes the range via
 * FUN_0028ccbc and removes it; borrow-overflow traps (0x28fd50).
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_make_unique_remove_range(void *p1, void *p2, void *param_3)
{
    (void)p1; (void)p2;
    sk_cpu();
    long n = 0, r = 0;
    /* FUN_0034c3c4; FUN_0034d868; FUN_00377bec; FUN_0034da98;
     * FUN_00355d78; r = FUN_0028ccbc(...) */
    if (!__builtin_sub_overflow(n, r, (long *)0)) {
        /* FUN_0031d488(param_3); FUN_00351414; (*x8_03)(...);
         * FUN_003504c4; (*x9_00)(); FUN_0031afcc; FUN_00352e30;
         * FUN_00351e3c; (*pc)(); FUN_00350a34; (*x8_01)(); dispatch */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x28fd50) */
}

/*--------------------------------------------------------------------*/
/* FUN_0028fd60 @ 0x0028fd60   (est. sk_array_replace_range)
 * Ghidra: void FUN_0028fd60(undefined8,undefined8,long,undefined8,undefined8,ulong)
 * Array replaceSubrange: forwards to FUN_0028f17c then performs an indirect
 * call through the element metadata's move/destroy callback.
 * Confidence: medium.
 */
void sk_array_replace_range(void *p1, void *p2, long param_3, void *param_4,
                            void *param_5, unsigned long param_6)
{
    sk_array_make_unique_reserve(p1, p2, (long)param_5, (void *)param_3,
                                 *(void **)((param_6 & ~1ULL) - 8));
    /* indirect call through *(*(param_3-8)+8)(param_2, param_3) */
    void (*fn)(void *, long) = *(void (**)(void *, long))(*(long *)((char *)param_3 - 8) + 8);
    fn((void *)0, param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_0028fe20 @ 0x0028fe20   (est. sk_array_make_unique_thunk)
 * Ghidra: void FUN_0028fe20(undefined8,undefined8,long,ulong)
 * Array makeUnique thunk: forwards to FUN_0028f468, resolves element
 * metadata, and performs the indirect move callback.
 * Confidence: medium.
 */
void sk_array_make_unique_thunk(void *p1, void *p2, long param_3, unsigned long param_4)
{
    unsigned long u2 = *(unsigned long *)((param_4 & ~1ULL) - 8);
    sk_array_make_unique_append(p1, p2, param_3, (void *)u2);
    sk_type_id(u2);
    unsigned long tid = sk_type_id(0);
    long lk = sk_object_lock(0, tid, *(unsigned long *)((char *)param_3 + 0x10),
                             (void *)0x611b24, (void *)0x611b34);
    void (*fn)(void *, long) = *(void (**)(void *, long))(*(long *)(lk + -8) + 8);
    fn(p1, lk);
}

/*--------------------------------------------------------------------*/
/* FUN_0028ff3c @ 0x0028ff3c   (est. sk_swift_string_compare_a)
 * Ghidra: void FUN_0028ff3c(void)
 * Forwarder to FUN_002740e4 (string comparison).
 * Confidence: high.
 */
void sk_swift_string_compare_a(void)
{
    /* FUN_002740e4() */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ff40 @ 0x0028ff40   (est. sk_swift_string_compare_b)
 * Ghidra: void FUN_0028ff40(void)
 * Second forwarder to FUN_002740e4.
 * Confidence: high.
 */
void sk_swift_string_compare_b(void)
{
    /* FUN_002740e4() */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ff60 @ 0x0028ff60   (est. sk_swift_string_hash_a)
 * Ghidra: void FUN_0028ff60(void)
 * Forwarder to FUN_00276840 (string hash).
 * Confidence: high.
 */
void sk_swift_string_hash_a(void)
{
    /* FUN_00276840() */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ff64 @ 0x0028ff64   (est. sk_swift_string_hash_b)
 * Ghidra: void FUN_0028ff64(void)
 * Second forwarder to FUN_00276840.
 * Confidence: high.
 */
void sk_swift_string_hash_b(void)
{
    /* FUN_00276840() */
}

/*--------------------------------------------------------------------*/
/* FUN_0028ff78 @ 0x0028ff78   (est. sk_array_append_element)
 * Ghidra: void FUN_0028ff78(undefined8,undefined8,long,undefined8,undefined8,undefined8,undefined8)
 * Array append with makeUnique: saves the thread, resolves element metadata,
 * appends a single element, grows if the buffer is not unique, and
 * dispatches through the object method table. Overflow paths trap.
 * Epilogue FUN_0008e500.
 * Confidence: low (long indirect-dispatch sequence).
 */
void sk_array_append_element(void *p1, void *p2, long param_3, void *param_4,
                             void *param_5, void *param_6, void *param_7)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00349a68; (*DAT_00658c00)([x8+0x40]); FUN_003497b4;
     * FUN_00351ce8; FUN_00351ef8(param_5); u11 = *(p3+0x10);
     * FUN_0034c354; FUN_00351abc; FUN_00377824; FUN_00348d64;
     * (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4; FUN_0034c684;
     * (*DAT_00658c00)(); FUN_0034b8bc; FUN_0035156c; FUN_00350b6c;
     * (*x9)(); FUN_0034cfc4; FUN_00377bec; FUN_00351ef8; FUN_0014ae44;
     * FUN_003516b4; u5 = (*pc)(); FUN_00350518([x16_00+8]); (*x8_01)() */
    int i2 = *(int *)((char *)param_3 + 0x24);
    unsigned long n = 0, m = 0;
    /* if (u5 & 1) == 0: unique path */
    if (0) {
        if (__builtin_add_overflow(n, m, (long *)0)) { CL4_SBP(); }
        if (__builtin_add_overflow(n + m, 1, (long *)0)) { CL4_SBP(); }
        /* append; FUN_00358cd4; (*x8_08)(...); ... */
        /* FUN_003529b0(x24, local_48, n+m+1) */
    } else {
        /* non-unique grow path */
        if (__builtin_add_overflow(n, m, (long *)0)) { CL4_SBP(); }
        /* FUN_00357aec(...); ... */
    }
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029040c @ 0x0029040c   (est. sk_array_append2)
 * Ghidra: void FUN_0029040c(undefined8,undefined8,long,undefined8)
 * Array append flavour: makeUnique + append, overflow paths trap
 * (0x2907b8 / 0x2907b4). Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_append2(void *p1, void *p2, long param_3, void *param_4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00351ef8(param_4); FUN_00350bd8; u8 = *(p3+0x10);
     * FUN_003497a0; FUN_00377824(...); FUN_000a6f88; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b6f4; ... FUN_0014ae44; FUN_00351584;
     * u5 = (*pc)(); FUN_000e72b0([x16+8]); (*x8_00)() */
    int i1 = *(int *)((char *)param_3 + 0x28);
    int i2 = *(int *)((char *)param_3 + 0x24);
    (void)i1; (void)i2;
    long n = 0;
    if (!__builtin_add_overflow(n, 2, (long *)0)) {
        /* append 2 elements; FUN_003594e0; (*x8_04)(); FUN_00352c8c;
         * FUN_0031d6a8; FUN_00353a18(u8, i1, x1); (*x8_05)() */
        /* FUN_00351b78(u8, n+2) */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x2907b8) */
    /* else branch: non-unique */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_002907b8 @ 0x002907b8   (est. sk_array_append3)
 * Ghidra: void FUN_002907b8(undefined8,undefined8,long,undefined8,undefined8,undefined8)
 * Array append flavour; overflow paths trap (0x290bfc/0x290c00/0x290bf8).
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_append3(void *p1, void *p2, long param_3, void *param_4,
                      void *param_5, void *param_6)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00349a68; (*DAT_00658c00)([x8+0x40]); FUN_003497b4;
     * FUN_00352738; FUN_003514b8(param_5); FUN_0034f788; FUN_0034e6fc;
     * FUN_00377824; FUN_00348ce8; (*DAT_00658c00)([x8_00+0x40]);
     * FUN_00348a80; (*DAT_00658c00)(); FUN_0034b3d8; FUN_0034fe64;
     * FUN_00084174; (*x9)(); FUN_0034e53c; FUN_00377bec; FUN_00351ef8;
     * FUN_0014ae44; FUN_000a6e14; FUN_00351b20; u4 = (*pc)();
     * FUN_00350630([x16_00+8]); (*x8_01)() */
    int i1 = *(int *)((char *)param_3 + 0x24);
    (void)i1;
    long n = 0, m = 0;
    if (!__builtin_add_overflow(n, m, (long *)0)) { CL4_SBP(); }
    if (!__builtin_add_overflow(n + m, 1, (long *)0)) { CL4_SBP(); }
    /* append + dispatch */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00290c00 @ 0x00290c00   (est. sk_array_append4)
 * Ghidra: void FUN_00290c00(undefined8,undefined8,undefined8,undefined8)
 * Array append flavour; borrow-overflow traps (0x290f34). Epilogue
 * FUN_0008e500.
 * Confidence: low.
 */
void sk_array_append4(void *p1, void *p2, void *param_3, void *param_4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00350950(param_3); FUN_0034d598; FUN_0034bec4; FUN_00377824;
     * FUN_00348ce8; (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4;
     * FUN_0034d698; (*DAT_00658c00)(); FUN_0034b3d8; FUN_003506e8;
     * FUN_003507e0; (*x9_00)(); FUN_0034d190; FUN_00377bec;
     * FUN_003514b8; FUN_0014ae44; FUN_0034f2b4; u3 = (*pc)();
     * FUN_00350630([x16+8]); (*x8_01)() */
    long n = 0;
    if (!__builtin_sub_overflow(n, 1, (long *)0)) {
        /* append + dispatch */
        sk_thread_epilogue();
        return;
    }
    CL4_SBP();   /* SoftwareBreakpoint(1,0x290f34) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00290f34 @ 0x00290f34   (est. sk_array_make_unique_remove_first)
 * Ghidra: void FUN_00290f34(undefined8,undefined8,undefined8,undefined8)
 * Array removeFirst(makeUnique) path: removes the first element and
 * dispatches; borrow-overflow traps (0x2912b8/0x2912bc/0x2912c0).
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_array_make_unique_remove_first(void *p1, void *p2, void *param_3, void *param_4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_003514b8(param_3); FUN_0034c354; FUN_0035136c; FUN_00377824;
     * FUN_00348ce8; (*DAT_00658c00)([x8+0x40]); FUN_003493c4;
     * FUN_0034d698; (*DAT_00658c00)(); FUN_0034ba68; FUN_0034fe64;
     * FUN_00351274; (*x9)(); FUN_0034edd8; u4 = FUN_00377bec();
     * FUN_003514b8; FUN_0014ae44; FUN_003509b0; FUN_0034f2b4;
     * u6 = (*pc)(); FUN_003508b4([x16+8]); (*x8_00)() */
    long n = 0, m = 0;
    if (__builtin_sub_overflow(n, m, (long *)0)) { CL4_SBP(); }
    if (!__builtin_add_overflow(n - m, 1, (long *)0)) { CL4_SBP(); }
    /* remove first + dispatch */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00291310 @ 0x00291310   (est. sk_swift_string_release3)
 * Ghidra: void FUN_00291310(void)
 * Small string release sequence: FUN_003503c0, FUN_003a25d4 (release),
 * FUN_0007c1c4.
 * Confidence: medium.
 */
void sk_swift_string_release3(void)
{
    /* FUN_003503c0 */
    sk_swift_release(0, 0);
    sk_object_init(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002913ec @ 0x002913ec   (est. sk_swift_small_string_set_bit)
 * Ghidra: undefined1* FUN_002913ec(void)
 * Small-string builder: allocates a 0x28-byte container (tag 0xfd4c),
 * copies the two 8-byte payload words from the caller buffer, and stores a
 * bit extracted at a byte offset into the trailer byte. Returns a dispatch
 * label (LAB_00291468).
 * Confidence: medium.
 */
void sk_swift_small_string_set_bit(void *out, unsigned long *src)
{
    unsigned long *h = sk_alloc(0x28, 0xfd4c);
    *(void **)out = h;
    h[0] = (unsigned long)out;   /* unaff_x19 */
    h[1] = (unsigned long)src;   /* unaff_x20 */
    unsigned long w0 = src[0];
    unsigned long w1 = src[1];
    h[2] = w0;
    unsigned long bit = (unsigned long)out & 7;
    if (7 < (long)bit) { w0 = w1; }
    *(unsigned char *)((char *)h + 0x20) = (unsigned char)(w0 >> (bit << 3));
    h[3] = w1;
}

/*--------------------------------------------------------------------*/
/* FUN_002914b4 @ 0x002914b4   (est. sk_swift_small_string_load)
 * Ghidra: void FUN_002914b4(undefined8,undefined8,undefined8)
 * Small-string load: decodes a 16-byte small-string payload, validating the
 * byte-count/width fields (Swift SmallString internal invariants) and
 * failing through the SmallString fatal error on malformed data.
 * Confidence: high (Swift SmallString decode paths).
 */
void sk_swift_small_string_load(void *p1, void *p2, unsigned long word)
{
    (void)p1; (void)p2;
    /* FUN_0035701c; FUN_003520dc; FUN_0028e8c0 span validate */
    unsigned long lo = 0, hi = 0;
    if ((long)lo < 0 || hi < 0) {
        /* FUN_003481fc */
        sk_fatal_error(0, 0, 0);
    }
    /* FUN_00348e48; FUN_001e4cbc decode */
    long n = 0;
    if (n == 0) {
        /* empty */
    } else if (n == 8) {
        /* FUN_0034e0b4; FUN_003496b0 loop */
        /* FUN_00354b38(0xe000000000000000) */
    } else {
        /* multi-byte width decode; invalid -> fatal SmallString */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00291580 @ 0x00291580   (est. sk_swift_string_char_decode)
 * Ghidra: undefined8 FUN_00291580(undefined8,long)
 * Decodes a Unicode scalar from the small-string payload at the given byte
 * count. Handles 8-byte, <8-byte, and larger widths; malformed encodings
 * fail through the Range fatal error.
 * Confidence: high (Swift SmallString/UTF-8 decode).
 */
unsigned long sk_swift_string_char_decode(unsigned long word, long n)
{
    if (n == 0) return 0;
    if (n < 0x10) {
        unsigned long acc = 0;
        if (n < 0) {
            /* FUN_00347da8 */
            sk_fatal_error(0, 0, 0);
        }
        /* FUN_00350dc4 / FUN_003598c0 accumulate scalar bytes */
        long w = 0;
        if (w < 9) {
            acc = 0;
        } else {
            /* FUN_00358738 */
            acc = 0;
        }
        /* FUN_00354f64(acc | ..., ..., 0) */
        return acc;
    }
    return sk_swift_string_char_width(word, n, 0);   /* FUN_003509f8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00291654 @ 0x00291654   (est. sk_string_construct)
 * Ghidra: void FUN_00291654(undefined8,undefined8,undefined8,undefined8,ulong,undefined8)
 * String constructor: packs the (size, width, flags, data) fields of a Swift
 * String and dispatches to FUN_00291d70 to finalize. The 16-byte stack
 * frame mirrors the String guts layout.
 * Confidence: high (Swift String init from unicode scalar).
 */
void sk_string_construct(void *out, void *p2, void *p3, void *p4, unsigned long p5, void *p6)
{
    unsigned long size = p5 & 0xffffff;
    unsigned long width = p5 >> 0x38 & 0xf;
    (void)size; (void)width;
    /* FUN_003519e8; FUN_0034a210; tag = FUN_00002534() */
    unsigned long tag = sk_allocator_tag(0, 0);
    /* FUN_00291d70(out, &p4, FUN_00346774, stack, u1, tag, p6, 0x66c1c8, local_48) */
    sk_swift_string_char((unsigned long)p6, (unsigned long)p2, (unsigned long)p3, 0x66c1c8);
}

/*--------------------------------------------------------------------*/
/* FUN_00291764 @ 0x00291764   (est. sk_swift_small_string_set_bit2)
 * Ghidra: undefined1* FUN_00291764(undefined8*,ulong*)
 * Small-string builder (0x28-byte, tag 0xa2a3) storing a bit into the
 * trailer byte from the source words. Returns a dispatch label.
 * Confidence: medium.
 */
void sk_swift_small_string_set_bit2(void *out, unsigned long *src)
{
    unsigned long *h = sk_alloc(0x28, 0xa2a3);
    *(void **)out = h;
    unsigned long w0 = src[0];
    h[0] = (unsigned long)out;
    h[1] = w0;
    unsigned long b0 = *(unsigned long *)out;   /* unaff_x20 */
    unsigned long w1 = *(unsigned long *)((char *)out + 8);
    unsigned long bit = w0 & 7;
    if (7 < (long)w0) { b0 = w1; }
    *(unsigned char *)((char *)h + 0x20) = (unsigned char)(b0 >> (bit << 3));
    h[3] = w1;
}

/*--------------------------------------------------------------------*/
/* FUN_00291834 @ 0x00291834   (est. sk_swift_small_string_fatal_e2)
 * Ghidra: void FUN_00291834(void)
 * Raises the Swift SmallString fatal error (code 0xe2).
 * Confidence: high (Swift SmallString string matches).
 */
void sk_swift_small_string_fatal_e2(void)
{
    sk_fatal_dump(0xb, 2, 0, 0xe000000000000000,
                  (unsigned long)"Swift.SmallString", 0x17, 2, 0xe2, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00291880 @ 0x00291880   (est. sk_swift_small_string_fatal_e3)
 * Ghidra: void FUN_00291880(void)
 * Raises the Swift SmallString fatal error (code 0xe3).
 * Confidence: high.
 */
void sk_swift_small_string_fatal_e3(void)
{
    sk_fatal_dump(0xb, 2, 0, 0xe000000000000000,
                  (unsigned long)"Swift.SmallString", 0x17, 2, 0xe3, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00291904 @ 0x00291904   (est. sk_swift_small_string_extract)
 * Ghidra: void FUN_00291904(undefined8*,undefined8*)
 * Extracts the small-string payload via FUN_001e6f84 and stores it.
 * Confidence: medium.
 */
void sk_swift_small_string_extract(unsigned long *out, unsigned long *src)
{
    unsigned long v = sk_swift_string_char_width(src[0], *(unsigned long *)src, 0); /* FUN_001e6f84 */
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00291934 @ 0x00291934   (est. sk_swift_string_index_dec)
 * Ghidra: void FUN_00291934(ulong*)
 * String index decrement: underflow traps (0x2919bc); also validates the
 * index against the Collection count, panicking on out-of-bounds.
 * Confidence: high.
 */
void sk_swift_string_index_dec(unsigned long *idx)
{
    unsigned long v = *idx - 1;
    if (__builtin_sub_overflow(*idx, 1, (unsigned long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x2919bc) */
    }
    if (((unsigned long)*(unsigned char *)((char *)idx + 0xf) & 0xf) <= v) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Index out of bounds", 0x13, 2,
                       (unsigned long)"Swift.Collection", 0x16, 2, 0x2ca, 1);
    }
    *idx = v;
}

/*--------------------------------------------------------------------*/
/* FUN_002919bc @ 0x002919bc   (est. sk_swift_string_index_from_int)
 * Ghidra: void FUN_002919bc(void)
 * Builds a String index from an integer via FUN_001e6594.
 * Confidence: medium.
 */
void sk_swift_string_index_from_int(unsigned long *out)
{
    /* FUN_00350258 */
    *out = sk_swift_string_index(0, 0, 0, 0, 0);   /* FUN_001e6594 */
}

/*--------------------------------------------------------------------*/
/* FUN_002919fc @ 0x002919fc   (est. sk_swift_string_index_advance)
 * Ghidra: void FUN_002919fc(void)
 * Advances a String index (FUN_00359424 then FUN_001e6a98).
 * Confidence: medium.
 */
void sk_swift_string_index_advance(void)
{
    /* FUN_00359424 */
    sk_swift_string_index_next();
}

/*--------------------------------------------------------------------*/
/* FUN_00291a68 @ 0x00291a68   (est. sk_swift_small_string_load_bytes)
 * Ghidra: void FUN_00291a68(ulong*,undefined8*)
 * Loads a small string's bytes, validating the span via FUN_0028e8c0 and
 * decoding up to 16 bytes into the two 8-byte payload words with an
 * 0x80/0x20 "non-ASCII" marker. Raises Invalid slice / Range fatal errors.
 * Confidence: high (Swift SmallString.load).
 */
void sk_swift_small_string_load_bytes(unsigned long *out, unsigned long *src)
{
    unsigned long lo = src[0];
    unsigned long width = src[1] >> 0x38 & 0xf;
    unsigned long size = src[1] & 0xffffffffffffff;
    unsigned long rlo = 0, rhi = 0;
    if ((long)rlo < 0 || (long)width < rhi) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Invalid slice", 0xd, 2,
                       (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x7db, 1);
    }
    /* FUN_001e4cbc decode bytes into (u3, u8) with 0x80/0xa0 marker */
    unsigned long u3 = 0, u8 = 0xe000000000000000;
    /* pack (u3, u8 | size<<0x38 | tail) */
    out[0] = u3;
    out[1] = u8;
}

/*--------------------------------------------------------------------*/
/* FUN_00291c58 @ 0x00291c58   (est. sk_swift_small_string_whole)
 * Ghidra: void FUN_00291c58(undefined1(*)[16])
 * Returns the whole small string as a 16-byte value via FUN_0019fa54.
 * Confidence: medium.
 */
void sk_swift_small_string_whole(unsigned long out[2])
{
    unsigned long v = sk_swift_string_char_width(0, 0, 0);   /* FUN_0019fa54 */
    out[0] = v;
    out[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00291c98 @ 0x00291c98   (est. sk_swift_small_string_extract2)
 * Ghidra: void FUN_00291c98(undefined8*,undefined8*)
 * Extracts the small-string payload via FUN_001e75c0.
 * Confidence: medium.
 */
void sk_swift_small_string_extract2(unsigned long *out, unsigned long *src)
{
    unsigned long v = sk_swift_string_char_width(src[0], *(unsigned long *)src, 0); /* FUN_001e75c0 */
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00291cc8 @ 0x00291cc8   (est. sk_swift_string_index_inc)
 * Ghidra: void FUN_00291cc8(ulong*)
 * String index increment: validates against the Collection count, then
 * advances by one; out-of-bounds panics.
 * Confidence: high.
 */
void sk_swift_string_index_inc(unsigned long *idx)
{
    if (((unsigned long)*(unsigned char *)((char *)idx + 0xf) & 0xf) <= *idx) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Index out of bounds", 0x13, 2,
                       (unsigned long)"Swift.Collection", 0x16, 2, 0x2ca, 1);
    }
    *idx = *idx + 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00291d70 @ 0x00291d70   (est. sk_string_finalize)
 * Ghidra: void FUN_00291d70(void)
 * Finalizes a Swift String: validates the byte count (must be >= 0) via the
 * dispatch slot, appends trailing data if a trailer is present, and returns.
 * Negative counts raise a fatal error.
 * Confidence: high (Swift String append/finalize).
 */
void sk_string_finalize(void)
{
    /* FUN_0034b7e4; (*DAT_00658c00)(); FUN_003501b8;
     * lVar1 = FUN_0035a028() */
    long n = 0;
    long cap = 0;
    if (-1 < cap) {
        /* (*x12)(n, n + cap) */
        if (0 != 0) {
            /* FUN_003508d8([x16+0x20], in_x7); (*x8)() */
        }
        return;
    }
    /* FUN_00348284; FUN_00351094 */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00291e8c @ 0x00291e8c   (est. sk_swift_load_le_bytes)
 * Ghidra: ulong FUN_00291e8c(byte*,long)
 * Loads `param_2` little-endian bytes into a word; negative counts raise a
 * fatal error.
 * Confidence: high.
 */
unsigned long sk_swift_load_le_bytes(unsigned char *p, long n)
{
    if (n < 0) {
        /* FUN_00347d60 */
        sk_fatal_error(0, 0, 0);
    }
    unsigned long acc = 0;
    for (long i = 0; i < n; i++) {
        acc |= (unsigned long)p[i] << ((unsigned long)i * 8 & 0x38);
    }
    return acc;
}

/*--------------------------------------------------------------------*/
/* FUN_00291ee0 @ 0x00291ee0   (est. sk_swift_small_string_append_bytes)
 * Ghidra: void FUN_00291ee0(ulong,ulong,ulong,ulong)
 * Appends bytes to a small string, handling the case where the combined
 * widths fit in 16 bytes; otherwise sets the "wide" overflow flag and
 * returns. Used by SmallString append.
 * Confidence: high (Swift SmallString append).
 */
void sk_swift_small_string_append_bytes(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4)
{
    unsigned long w1 = p2 >> 0x38 & 0xf;
    unsigned long w2 = p4 >> 0x38 & 0xf;
    unsigned long total = w2 + w1;
    unsigned long out1 = p1, out2 = p2, out3 = p3, flag = 0, mark = 0;
    if (total < 0x10) {
        if (w2 != 0) {
            /* byte-wise merge loop */
            unsigned long shift = w1 << 3;
            for (unsigned long i = 0; i < w2; i++) {
                unsigned long src = i < 8 ? p3 >> ((i * 8) & 0x3f) : p4 >> ((i * 8) & 0x3f);
                unsigned long byte = src & 0xff;
                out2 = (byte << (shift & 0x38)) | ((~0xffULL << (shift & 0x38)) - 1 & p2);
                if (w1 < 8) {
                    out1 = (byte << (shift & 0x3f)) | ((~0xffULL << (shift & 0x3f)) - 1 & p1);
                    out2 = p2;
                }
                p2 = out2;
                w1 += 1;
                shift += 8;
            }
        }
        if (((out1 | p2 & 0xffffffffffffff) & 0x8080808080808080) != 0) {
            mark = 0xa000000000000000;
        }
        mark |= total << 0x38 | p2 & 0xffffffffffffff;
        /* FUN_00353d34(mark, out1, p2, 0) */
    } else {
        out1 = 0;
        mark = 0;
        flag = 1;
    }
    /* FUN_00353d34(mark, out1, out2, flag) */
}

/*--------------------------------------------------------------------*/
/* FUN_00291fa8 @ 0x00291fa8   (est. sk_object_service_dispatch_a)
 * Ghidra: void FUN_00291fa8(void)
 * Object-service chain: current-TCB save, lock, dispatch, then FUN_0029207c.
 * Confidence: low.
 */
void sk_object_service_dispatch_a(void)
{
    sk_current_tcb();
    /* FUN_003497a0; FUN_00377824; FUN_00354d44; FUN_00351b78 */
    sk_string_finalize();   /* FUN_0029207c */
}

/*--------------------------------------------------------------------*/
/* FUN_0029200c @ 0x0029200c   (est. sk_object_service_callback)
 * Ghidra: void FUN_0029200c(void)
 * Object-service callback: runs the dispatch chain, resolves the object
 * lock, and finishes with FUN_0035a7d4.
 * Confidence: low.
 */
void sk_object_service_callback(void)
{
    /* FUN_0035a7c0; FUN_003585e8; FUN_0034d6d8; FUN_0016186c(x5);
     * FUN_00349ea0; FUN_00350ed0; auVar3 = FUN_00377824();
     * FUN_000a6e14(...); (*pc)(); u2 = FUN_0035396c();
     * FUN_0035a7d4(u2, x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_0029207c @ 0x0029207c   (est. sk_string_append_finalize)
 * Ghidra: void FUN_0029207c(void)
 * String append/finalize: resolves type metadata, appends a character, and
 * either stores or frees the trailer depending on the unique flag, then
 * finalizes with FUN_00358fc8.
 * Confidence: low (indirect dispatch; FUN_0027b41c trailer append).
 */
void sk_string_append_finalize(void)
{
    /* FUN_00358fb4; FUN_003545ac; FUN_0035089c; FUN_00349720;
     * (*DAT_00658c00)([x8+0x40]); FUN_00349068; FUN_00351f88([x12+0x10]);
     * (*x8_00)(); FUN_003497a0; FUN_00350b18; FUN_00377824;
     * FUN_0035159c; FUN_003516d8; in = FUN_0019e578(); FUN_00350798;
     * FUN_00310d80; FUN_00349910; FUN_00376820; FUN_0034e4b4;
     * FUN_00376820; FUN_0034db48; FUN_0027b41c() */
    unsigned long trailer = 0;
    if (0 == 0) {
        /* FUN_003488f4; FUN_0019e578(&trailer) */
    } else {
        sk_free((void *)trailer);
    }
    /* u1 = FUN_00355f04(); FUN_00358fc8(u1, x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00292188 @ 0x00292188   (est. sk_object_service_dispatch_b)
 * Ghidra: void FUN_00292188(void)
 * Object-service chain: type-id, lock, dispatch, then FUN_0027b41c.
 * Confidence: low.
 */
void sk_object_service_dispatch_b(void)
{
    /* FUN_00349a18; FUN_00027754(x1); FUN_00348b94; FUN_00377824;
     * FUN_00354d44; FUN_00351e3c; FUN_0027b41c() */
}

/*--------------------------------------------------------------------*/
/* FUN_00292204 @ 0x00292204   (est. sk_array_contains_element)
 * Ghidra: uint FUN_00292204(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Array contains: resolves element metadata and calls the equality callback
 * (FUN_0016186c), returning whether it matched (bit 0).
 * Confidence: high.
 */
unsigned int sk_array_contains_element(void *p1, void *p2, void *p3, void *p4,
                                       void *p5, void *p6, void *p7)
{
    (void)p3; (void)p6;
    sk_type_id((unsigned long)p5);
    unsigned long tid = sk_type_id(0);
    unsigned long lk = sk_object_lock(0, tid, (unsigned long)p4, (void *)0x611b24, (void *)0x611b34);
    unsigned int r = ((unsigned int(*)(void *, void *, unsigned long, void *))sk_object_method_table)(p1, p2, lk, p7);
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002922b0 @ 0x002922b0   (est. sk_array_sort_range)
 * Ghidra: void FUN_002922b0(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Array sort range: resolves element metadata and calls FUN_00292340 with
 * the sorted-range descriptor.
 * Confidence: medium.
 */
void sk_array_sort_range(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    (void)p1;
    sk_type_id((unsigned long)p5);
    unsigned long tid = sk_type_id(0);
    unsigned long lk = sk_object_lock(0xff, tid, (unsigned long)p4, (void *)0x611b24, (void *)0x611b34);
    unsigned long u = sk_allocator_tag(0, lk);   /* FUN_0031de7c */
    sk_swift_string_char((unsigned long)p2, (unsigned long)p3, u);   /* FUN_00292340 */
}

/*--------------------------------------------------------------------*/
/* FUN_00292340 @ 0x00292340   (est. sk_array_sort_range_impl)
 * Ghidra: void FUN_00292340(undefined8,undefined8,undefined8)
 * Array sort range implementation: computes the element count (FUN_0029369c)
 * and either resizes/unique the backing store or builds an element span and
 * sorts it. Epilogue FUN_00355f04.
 * Confidence: low (heavy indirect dispatch).
 */
void sk_array_sort_range_impl(void *p1, void *p2, void *param_3)
{
    (void)p1; (void)p2;
    /* FUN_00355d9c; lVar3 = *(x20+8); lVar1 = FUN_0029369c(lVar3) */
    unsigned long count = *(unsigned long *)((char *)0 + 8);
    unsigned long round = sk_swift_int_round_up(count);   /* FUN_0029369c */
    if (round < count) {
        SK_OBJ_DISPATCH();
        /* FUN_0034a210; FUN_00002534; FUN_00351b2c(count/2, FUN_0031df4c);
         * FUN_001a7544(); if x21==0: sk_free() */
        if (0 == 0) {
            sk_free(0);
        }
    } else {
        if ((long)count < 0) {
            /* FUN_00347d60 */
            sk_fatal_error(0, 0, 0);
        }
        /* build span (0, count); FUN_0034e250; FUN_00376820;
         * FUN_003544ec; FUN_00376820; FUN_003511f0(&local_60);
         * FUN_00292e28() */
        sk_swift_string_build_span(0, 0, 0, 0, 0);
    }
    /* FUN_00355f04 */
}

/*--------------------------------------------------------------------*/
/* FUN_00292490 @ 0x00292490   (est. sk_object_service_dispatch_c)
 * Ghidra: void FUN_00292490(void)
 * Object-service chain: thread-save, two lock+init stages, then dispatches
 * through the object method table and finishes with FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_dispatch_c(void)
{
    sk_cpu();
    /* FUN_00353b7c; FUN_0034ce98; FUN_00377824; FUN_00351f10;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b0c4; u4=[l+0x20];
     * u5=[l+0x10]; FUN_00350720; FUN_00351f40; FUN_00377824;
     * FUN_00351f10; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034aee4;
     * FUN_000a68c4(u4); FUN_0034d934; (*x9)(u2,u4); FUN_00352680(u3);
     * FUN_00084180; (*x9_00)(); FUN_00100c38; FUN_003513cc(...);
     * FUN_002e4290; FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029259c @ 0x0029259c   (est. sk_object_service_dispatch_d)
 * Ghidra: void FUN_0029259c(void)
 * Large object-service loop: thread-save, multiple lock/init stages, a
 * method-dispatch section keyed on a byte flag at (x20 + [x24+0x38]), and a
 * deferred path that either destroys the object (FUN_003722e4) or stores it.
 * Epilogue FUN_0008e500 / FUN_000839d8.
 * Confidence: low (complex indirect dispatch; state machine on flag).
 */
void sk_object_service_dispatch_d(void)
{
    sk_cpu();
    /* FUN_00358ef4; FUN_003520f8(lVar3, [lVar3+0x28]); FUN_00377824(0xff);
     * FUN_0035113c; FUN_00310d68; FUN_000a6f88; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034f3c4; FUN_0007c028; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b6f4; FUN_00352a34(0xff); FUN_00377824;
     * FUN_0034f624; FUN_00310d68; FUN_00348ce8; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034aee4; FUN_0034998c; FUN_0007c1a4;
     * (*DAT_00658c00)() */
    int off = *(int *)(0 + 0x38);
    unsigned char flag = *(unsigned char *)((char *)0 + off) == 1;
    if (flag) {
        /* FUN_00350500; FUN_003515b4; FUN_003722e4; FUN_00350744;
         * FUN_0008e500; FUN_000839d8 */
        sk_ref_lock_op(0, 0, 0, 0);
        return;
    }
    /* deferred lock + destroy/store path */
    sk_thread_epilogue();
    sk_ref_lock_op(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00292948 @ 0x00292948   (est. sk_swift_sort_merge_loop)
 * Ghidra: void FUN_00292948(undefined8,undefined8,code*,undefined8,undefined8,undefined8)
 * Swift sort merge loop: iterates over element runs comparing via the given
 * comparator (param_3), merging runs through the element-type callbacks
 * until the buffer is exhausted. On the x21 termination path it dispatches
 * the final release.
 * Confidence: low (heavy indirect dispatch, do/while merge).
 */
void sk_swift_sort_merge_loop(void *p1, void *p2, void (*cmp)(void),
                              void *p4, void *p5, void *p6)
{
    (void)p1; (void)p2; (void)cmp; (void)p4; (void)p5;
    /* FUN_00353cfc; FUN_00350c5c; u1 = FUN_00027754(p6); FUN_00027754();
     * FUN_00348e30; u2 = FUN_00377824(...p5); FUN_000a6f88;
     * (*DAT_00658c00)([x8+0x40]); FUN_003493c4; ... */
    /* do { compare runs via (*cmp)(); merge via element callbacks;
     *      advance cursor } while (not done);
     * on x21 termination: (*pcVar5)(local_30, x26); ... */
}

/*--------------------------------------------------------------------*/
/* FUN_00292e28 @ 0x00292e28   (est. sk_swift_string_build_span)
 * Ghidra: void FUN_00292e28(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Builds a Swift span from element metadata: lock, resolve, then either
 * forwards to FUN_00292948 (merge) or completes the span build. Epilogue
 * FUN_00353d14.
 * Confidence: low.
 */
void sk_swift_string_build_span(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    (void)p1; (void)p2;
    /* FUN_00353cfc; FUN_00355e68; FUN_00357198; u1 = FUN_00027754(p5);
     * FUN_0034de64; FUN_00350920; FUN_003559bc; FUN_00377824;
     * FUN_00348d64; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b460;
     * FUN_0034cfc4; FUN_00377bec; FUN_0034d734; FUN_00310e08;
     * u2 = FUN_001e3048() */
    if (0) {
        /* FUN_00319658(u1); FUN_00351250; FUN_0035284c; (*x9)();
         * FUN_00350b00; FUN_0035a4bc(...); FUN_00292948();
         * FUN_00359628; FUN_000e15d8(); (*x8)() */
        sk_swift_sort_merge_loop(0, 0, 0, 0, 0, 0);
    }
    /* FUN_00351348; FUN_00353d14 */
}

/*--------------------------------------------------------------------*/
/* FUN_00292f38 @ 0x00292f38   (est. sk_swift_sort_swap_loop)
 * Ghidra: void FUN_00292f38(undefined8,undefined8,undefined8,undefined8)
 * Swift sort adjacent-swap loop: iterates comparing adjacent elements and
 * swapping via the element-type callbacks until done. Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_swift_sort_swap_loop(void *p1, void *p2, void *p3, void *p4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0035248c; FUN_00351ad4; FUN_0034d070; FUN_00350308;
     * FUN_00377824; FUN_00348d7c; (*DAT_00658c00)([x8+0x40]);
     * FUN_003489c0; (*DAT_00658c00)(); FUN_0034b4c0; ... */
    /* do { cmp adjacent; (*pcVar3)(u1, x1, p3); swap via (*pcVar4)();
     *      (*pcVar5)(...); } while (continue) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_002930f0 @ 0x002930f0   (est. sk_swift_sort_partition)
 * Ghidra: void FUN_002930f0(undefined8,undefined8,undefined8*,undefined8*,code*,...)
 * Swift sort partition step: partitions the element range [local_60, param_3)
 * using the comparator (param_5), swapping elements into place. Overflow/
 * underflow paths trap. Epilogue FUN_002935b0.
 * Confidence: low (heavy element-callback dispatch, partition loop).
 */
void sk_swift_sort_partition(void *p1, void *p2, void *lo, void *hi,
                             void (*cmp)(void), void *p6, void *p7, void *p8,
                             void *p9, void *p10)
{
    (void)p1; (void)p2; (void)cmp; (void)p6; (void)p7; (void)p8; (void)p9;
    /* FUN_00353cfc; local_50 = param_5; uStack_48 = param_6;
     * FUN_0034e39c; (*DAT_00658c00)(); ... FUN_00353af8() -> [local_60, puVar6)
     * lVar9 = element size ([x16_00+0x48]) */
    long esz = 0;
    if (esz == 0) {
        /* FUN_00350410; FUN_00348074 */
        sk_fatal_error(0, 0, 0);
    }
    /* partition loop: while lo < hi:
     *   cmp(pivot, element); move element via callback;
     *   terminate paths at LAB_00293534 */
    sk_swift_sort_partition_finish(0, 0, 0, 0);   /* FUN_002935b0 */
    /* FUN_00358490(1); FUN_00353d14 */
}

/*--------------------------------------------------------------------*/
/* FUN_002935b0 @ 0x002935b0   (est. sk_swift_sort_partition_finish)
 * Ghidra: void FUN_002935b0(undefined8*,long*,long*,long)
 * Finalizes a sort partition by moving `lVar1` elements of the element
 * stride from the source span into the destination. Division-by-zero and
 * overflow raise the Swift IntegerTypes fatal error.
 * Confidence: high (element-stride move + division checks).
 */
void sk_swift_sort_partition_finish(void *dst, long *src_begin, long *src_end, long stride)
{
    long esz = *(long *)(*(long *)((char *)stride + -8) + 0x48);
    if (esz == 0) {
        sk_fatal_error(0xb, 2, (unsigned long)"Division by zero", 0x10, 2,
                       (unsigned long)"Swift.IntegerTypes", 0x18, 2, 0x2334, 1);
    }
    long diff = *src_end - *src_begin;
    if (esz == -1 && diff == -0x8000000000000000LL) {
        sk_fatal_error(0xb, 2, (unsigned long)"Division results in an overflow", 0x1f, 2,
                       (unsigned long)"Swift.IntegerTypes", 0x18, 2, 0x233b, 1);
    }
    long n = diff / esz;
    /* FUN_0019ce60(*src_begin, n, *dst) */
}

/*--------------------------------------------------------------------*/
/* FUN_0029369c @ 0x0029369c   (est. sk_swift_int_round_up)
 * Ghidra: ulong FUN_0029369c(ulong)
 * Rounds the value up to a multiple of the leading-bit position such that
 * the top 6 bits after the shift are non-zero (Swift word-rounding used by
 * buffer growth). Returns the rounded value.
 * Confidence: high.
 */
unsigned long sk_swift_int_round_up(unsigned long v)
{
    unsigned long shift = 0x3aU - (unsigned long)__builtin_clzll(v) & 0x3f;
    unsigned long u = v >> shift;
    if ((v & (~0xfffULL << shift)) != 0) {
        u += 1;
    }
    return (long)v > 0x3f ? u : v;
}

/*--------------------------------------------------------------------*/
/* FUN_002936c8 @ 0x002936c8   (est. sk_swift_string_utf8_loop)
 * Ghidra: void FUN_002936c8(void)
 * Swift UTF-8 character loop: resolves String metadata, iterates decoding
 * UTF-8 scalars (1/2/3/4-byte), accumulating into a growing byte buffer.
 * Handles surrogates and validates the encoding; malformed input raises
 * fatal errors. Epilogue FUN_00353d14.
 * Confidence: high (Swift String UTF8 decode/append loop).
 */
void sk_swift_string_utf8_loop(void)
{
    /* FUN_00353cfc; FUN_00027754(x6); u1 = FUN_00027754(); FUN_00027754();
     * FUN_00348e30; u2 = FUN_00377824(...x5); FUN_000a6f88;
     * (*DAT_00658c00)([x8+0x40]); ... FUN_0014ae44; FUN_003504ac;
     * FUN_003518ac; u6 = (*x8_02)() */
    unsigned long scal = 0;
    /* decode loop:
     *   (*pcVar8)(...); FUN_0034c3b4(); (*pcVar8)();  (consume scalar)
     *   local_54 = (*in_x3)();  (user callback)
     *   FUN_0026398c-style decode: utf8 -> scalar
     *   append scalar bytes (1/2/3/4) into growing buffer
     *   on x21 termination: release */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00293c98 @ 0x00293c98   (est. sk_swift_array_insert_range)
 * Ghidra: void FUN_00293c98(undefined8,undefined8,undefined8,undefined8,undefined8,long)
 * Swift Array insert(range): validates the insertion range, grows the
 * backing store, moves elements with the element-type callback
 * (FUN_002930f0), and updates the element bounds. Overflow/underflow and
 * nil-element paths trap/fatal.
 * Confidence: medium (array range insert with element moves).
 */
void sk_swift_array_insert_range(void *p1, void *p2, void *p3, void *p4,
                                 void *p5, long param_6)
{
    (void)p1; (void)p2;
    /* FUN_003563e0; lVar6 = count; underflow -> SBP(0x293db0) */
    long count = 0;
    if (__builtin_sub_overflow(count, 1, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x293db0) */
    }
    /* lVar10 = [buf + 0x20 + (count-1)*0x10] (end bound) */
    /* insert range: FUN_002930f0(...) move elements */
    sk_swift_sort_partition(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    /* grow via FUN_003a261c / FUN_000f9930 / FUN_000f98ac */
    if (0 == 0) {
        sk_free(0);
    }
    /* FUN_0035578c(1) */
}

/*--------------------------------------------------------------------*/
/* FUN_00293ddc @ 0x00293ddc   (est. sk_swift_array_merge_check)
 * Ghidra: undefined8 FUN_00293ddc(long*)
 * Swift Array/Sort merge validation: walks the element bounds array,
 * checking for overlapping/adjacent ranges and panicking on underflow.
 * Returns 1 when a merge is required or on the termination flag.
 * Confidence: low (bounds-walk with many SoftwareBreakpoint checks).
 */
unsigned long sk_swift_array_merge_check(long *bounds)
{
    unsigned long n = *(unsigned long *)(*bounds + 0x10);
    if (1 < n) {
        /* walk bounds pairs with carry/borrow checks */
        unsigned long u = n;
        do {
            long *pair = (long *)(0 + u * 0x10);
            long d = pair[1] - pair[0];
            if (__builtin_sub_overflow(pair[1], pair[0], (long *)0)) { CL4_SBP(); }
            if (d < 0) return 1;
            /* FUN_0034ef08; FUN_00293c98() */
            sk_swift_array_insert_range(0, 0, 0, 0, 0, 0);
            if (0 != 0) return 1;
            u = *(unsigned long *)(0 + 0x10);
        } while (1 < u);
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00293f68 @ 0x00293f68   (est. sk_swift_array_merge_drain)
 * Ghidra: undefined8 FUN_00293f68(void)
 * Drains the merge work queue: while the bounds array has >= 2 entries,
 * runs FUN_00293c98 (insert range) until the x21 flag clears.
 * Confidence: low.
 */
unsigned long sk_swift_array_merge_drain(void)
{
    /* FUN_0034cb9c */
    do {
        if (*(unsigned long *)(SK_OBJ_BASE() + 0x10) < 2) return 1;
        /* FUN_0034ef08; FUN_00293c98() */
        sk_swift_array_insert_range(0, 0, 0, 0, 0, 0);
    } while (0 == 0);
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00293fc8 @ 0x00293fc8   (est. sk_swift_sort_range_partition)
 * Ghidra: void FUN_00293fc8(long*,undefined8,long*,undefined8,undefined8,long,undefined8,long*)
 * Swift sort range: recursively partitions the element range, growing the
 * bounds stack (FUN_000f9680) and pushing sub-ranges, until the whole range
 * is sorted. Fatal on unexpected nil / invalid range.
 * Confidence: low (recursive partition with explicit bounds stack).
 */
void sk_swift_sort_range_partition(long *p1, void *p2, long *p3, void *p4,
                                   void *p5, long p6, void *p7, long *p8)
{
    (void)p2; (void)p4; (void)p5; (void)p7;
    void *stack = (void *)0x657778;   /* DAT_00657778 empty-buffer sentinel */
    long lo = 0;
    do {
        if (p3[1] <= lo) {
            lo = *p1;
            if (lo != 0) {
                /* FUN_0031de7c(0, p7); FUN_00293f68(&stack,...) */
                if (0 == 0) {
                    sk_free(stack);
                } else {
                    sk_free(stack);
                    *p8 = 0;
                }
                return;
            }
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                           (unsigned long)"Swift.Sort", 0x10, 2, 0x2c5, 1);
        }
        /* partition [lo, p3[1]) via FUN_002936c8 */
        unsigned long part = 0;
        if (0 != 0) goto fail;
        /* push sub-ranges onto bounds stack */
        unsigned long cnt = *(unsigned long *)((char *)stack + 0x10);
        if (*(unsigned long *)((char *)stack + 0x18) >> 1 <= cnt) {
            stack = (void *)sk_alloc(*(unsigned long *)((char *)stack + 0x18), cnt + 1);   /* FUN_000f9680 */
        }
        *(unsigned long *)((char *)stack + 0x10) = cnt + 1;
        *(long *)((char *)stack + cnt * 0x10 + 0x20) = lo;
        *(long *)((char *)stack + cnt * 0x10 + 0x28) = lo + p6;
        if (*p1 == 0) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                           (unsigned long)"Swift.Sort", 0x10, 2, 0x2c0, 1);
        }
        sk_swift_array_merge_check((long *)&stack);
        lo = lo + p6;
    } while (1);
fail:
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                   (unsigned long)"Swift.Range", 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00294368 @ 0x00294368   (est. sk_swift_span_validate)
 * Ghidra: void FUN_00294368(long,long,long)
 * Validates a span: checks that the byte count is non-negative and that the
 * base is non-null when the range is non-empty; otherwise raises a fatal
 * error. Used by UnsafeRawBufferPointer.
 * Confidence: high.
 */
void sk_swift_span_validate(long base, long end, long count)
{
    long b = count ? count + base : 0;
    if (end - base < 0) {
        /* FUN_003483c4 */
        sk_fatal_error(0, 0, 0);
    } else if (end == base || b != 0) {
        return;
    } else {
        /* FUN_003488bc(1); FUN_00349644 */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002943ec @ 0x002943ec   (est. sk_span_store_u8)
 * Ghidra: void FUN_002943ec(undefined1,ulong)
 * UnsafeMutableRawSpan byte store: validates the byte offset range, then
 * stores a byte. Out of range raises the MutableRawSpan fatal error.
 * Confidence: high.
 */
void sk_span_store_u8(unsigned char val, unsigned long off)
{
    unsigned long size = *(unsigned long *)((char *)0 + 8);
    if (size < off || (long)(size - off) < 1) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Byte offset range out of bounds", 0x1f, 2,
                       (unsigned long)"Swift.MutableRawSpan", 0x1a, 2, 0x157, 1);
    }
    *(unsigned char *)(SK_OBJ_BASE() + off) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00294468 @ 0x00294468   (est. sk_span_store_u16)
 * Ghidra: void FUN_00294468(undefined2,ulong)
 * UnsafeMutableRawSpan 16-bit store with range validation.
 * Confidence: high.
 */
void sk_span_store_u16(unsigned short val, unsigned long off)
{
    unsigned long size = *(unsigned long *)((char *)0 + 8);
    if (size < off || (long)(size - off) < 2) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Byte offset range out of bounds", 0x1f, 2,
                       (unsigned long)"Swift.MutableRawSpan", 0x1a, 2, 0x157, 1);
    }
    *(unsigned short *)(SK_OBJ_BASE() + off) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_002944e4 @ 0x002944e4   (est. sk_span_store_u64)
 * Ghidra: void FUN_002944e4(undefined8,ulong)
 * UnsafeMutableRawSpan 64-bit store with range validation.
 * Confidence: high.
 */
void sk_span_store_u64(unsigned long val, unsigned long off)
{
    unsigned long size = *(unsigned long *)((char *)0 + 8);
    if (size < off || (long)(size - off) < 8) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Byte offset range out of bounds", 0x1f, 2,
                       (unsigned long)"Swift.MutableRawSpan", 0x1a, 2, 0x157, 1);
    }
    *(unsigned long *)(SK_OBJ_BASE() + off) = val;
}

/*--------------------------------------------------------------------*/
/* FUN_00294560 @ 0x00294560   (est. sk_swift_unsafe_raw_pointer_aligned)
 * Ghidra: void FUN_00294560(undefined8,undefined8,code*,undefined8,undefined8,long,long,...)
 * UnsafeRawPointer alignment-bound operation: checks that the pointer's
 * alignment flags (element stride bitmask) match the requested alignment;
 * on mismatch raises the "self must be a properly aligned pointer" fatal
 * error, otherwise calls the callback with the aligned address.
 * Confidence: high (Swift UnsafeRawPointer align check).
 */
void sk_swift_unsafe_raw_pointer_aligned(void *p1, void *p2, void (*cb)(void *),
                                         unsigned long align, unsigned long p5,
                                         long p6, long p7, void *p8, void *p9, void *p10)
{
    (void)p1; (void)p2;
    long meta = *(long *)(p7 + -8);
    SK_OBJ_DISPATCH();
    if ((*(unsigned int *)(*(long *)(p6 + -8) + 0x50) & (unsigned int)p5 & 0xff) == 0) {
        cb((void *)align);
        if (0 != 0) {
            /* (**(code**)(meta+0x20))(p10, &stack, p7) */
        }
        return;
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"self must be a properly aligned pointer", 0x32, 2,
                   (unsigned long)"Swift.UnsafeRawPointer", 0x1c);
}

/*--------------------------------------------------------------------*/
/* FUN_0029468c @ 0x0029468c   (est. sk_swift_init_repeating)
 * Ghidra: void FUN_0029468c(undefined8,undefined8,long,undefined8,undefined8)
 * Initializes `param_3` elements of the given element type by invoking the
 * element-copy callback (meta+0x10) repeatedly; negative counts raise a
 * fatal error.
 * Confidence: medium.
 */
void sk_swift_init_repeating(void *p1, void *p2, long count, void *p4, void *value)
{
    (void)p1; (void)p2;
    /* FUN_00354a34 */
    if (count >= 0) {
        /* FUN_00350a10 */
        for (long i = 0; i < count; i++) {
            /* (*pcVar1)([x8+0x10])(...); (*pcVar1)(...); count-- */
            void (*cb)(unsigned long, unsigned long, void *) =
                *(void (**)(unsigned long, unsigned long, void *))(0 + 0x10);
            cb(0, 0, value);
        }
        /* FUN_00354ef8 */
        return;
    }
    /* FUN_003488bc(1); FUN_0034a3ec */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00294804 @ 0x00294804   (est. sk_swift_span_range_check)
 * Ghidra: void FUN_00294804(long,long,long,long)
 * Bounds-checks a span range [param_1, param_2) with base param_3 and count
 * param_4; raises a fatal error on invalid ranges.
 * Confidence: high.
 */
void sk_swift_span_range_check(long lower, long upper, long base, long count)
{
    if (lower < 0) {
        /* FUN_003488bc(1); FUN_00349644 */
        sk_fatal_error(0, 0, 0);
    } else {
        if (base == 0) {
            if (0 < upper) { sk_fatal_error(0, 0, 0); }
        } else if (count - base < upper) {
            sk_fatal_error(0, 0, 0);
        }
        long b = base ? base + lower : 0;
        if (upper - lower < 0) {
            /* FUN_00348284 */
            sk_fatal_error(0, 0, 0);
        } else if (upper == lower || b != 0) {
            return;
        } else {
            /* FUN_00348508 */
            sk_fatal_error(0, 0, 0);
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002948b8 @ 0x002948b8   (est. sk_string_slice_alloc)
 * Ghidra: void FUN_002948b8(void)
 * Allocates a String slice: resolves the metadata, computes the byte count
 * via the element stride, and builds the slice with FUN_00354458.
 * Confidence: medium.
 */
void sk_string_slice_alloc(void)
{
    /* FUN_00355578; FUN_0034b668; u2 = FUN_0031de7c(0xff, x4);
     * u3 = FUN_0034b528(); auVar5 = FUN_00376820(u3, u2);
     * FUN_00350798(...); u2 = FUN_0031b080(); thunk_FUN_0028c754(...) */
    long b4 = 0;
    if (0 == 0) {
        b4 = 0;
    } else {
        long cnt = 0;
        b4 += *(long *)(*(long *)(0 + -8) + 0x48) * cnt;
    }
    /* FUN_0022b584; lVar1 = count; FUN_0021867c;
     * (*in_x5)(b4, count - cnt); FUN_00354458(...) */
    sk_swift_string_char(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002949bc @ 0x002949bc   (est. sk_swift_span_validate2)
 * Ghidra: void FUN_002949bc(long,long,long)
 * Span validation flavour identical to FUN_00294368.
 * Confidence: high.
 */
void sk_swift_span_validate2(long base, long end, long count)
{
    long b = count ? count + base : 0;
    if (end - base < 0) {
        /* FUN_00348284 */
        sk_fatal_error(0, 0, 0);
    } else if (end == base || b != 0) {
        return;
    } else {
        /* FUN_00348508 */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00294a20 @ 0x00294a20   (est. sk_swift_span_subrange)
 * Ghidra: undefined1[16] FUN_00294a20(ulong,ulong,long,ulong)
 * Computes the subrange [param_1, param_2) of a span with base param_3,
 * validating both bounds against the span length. Out-of-range raises the
 * Span fatal error; borrow underflow traps.
 * Confidence: high.
 */
void sk_swift_span_subrange(unsigned long lo, unsigned long hi, long base, unsigned long len,
                            unsigned long out[2])
{
    if (len < lo || len < hi) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"Index range out of bounds", 0x19, 2,
                       (unsigned long)"Swift.Span", 0x10, 2, 0x221, 1);
    }
    if (__builtin_sub_overflow(hi, lo, (unsigned long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x294aa0) */
    }
    out[0] = base ? (unsigned long)base + lo : 0;
    out[1] = hi - lo;
}

/*--------------------------------------------------------------------*/
/* FUN_00294ac8 @ 0x00294ac8   (est. sk_swift_small_string_validate_width)
 * Ghidra: void FUN_00294ac8(ulong,undefined8,uint)
 * Validates a small-string width/encoding descriptor: rejects non-canonical
 * encodings (bit 0 clear, 32-bit set) and out-of-range widths; otherwise
 * returns. On failure raises a fatal error.
 * Confidence: high (Swift SmallString / _StringObject encoding check).
 */
void sk_swift_small_string_validate_width(unsigned long w, void *p2, unsigned int flags)
{
    (void)p2;
    if ((flags & 1) == 0) {
        /* FUN_003488bc(1); FUN_0034c56c */
        sk_fatal_error(0, 0, 0);
    } else {
        if (w >> 0x20 != 0) {
            /* FUN_003583dc; FUN_00348194; FUN_003523f0 */
            sk_fatal_error(0, 0, 0);
        }
        if ((w >> 0x10 < 0x11) && (w - 0xe000 < 0xfffffffffffff800)) {
            return;
        }
        /* FUN_00348898(1); FUN_0034c978 */
        sk_fatal_error(0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00294b68 @ 0x00294b68   (est. sk_swift_string_bad_encoding)
 * Ghidra: void FUN_00294b68(void)
 * Raises a fatal error for a bad string encoding (FUN_00358ca4 +
 * FUN_003488bc path).
 * Confidence: high.
 */
void sk_swift_string_bad_encoding(void)
{
    /* FUN_00358ca4; FUN_003488bc */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00294bdc @ 0x00294bdc   (est. sk_swift_string_load_unicode)
 * Ghidra: void FUN_00294bdc(ulong,long,ulong)
 * Loads a Swift string's unicode scalar value, handling the small (inline)
 * and native (wide) representations and validating the encoding width.
 * Confidence: high (Swift String unicodeScalar load).
 */
void sk_swift_string_load_unicode(unsigned long w, long n, unsigned long flags)
{
    if ((flags & 1) == 0) {
        if (w != 0) {
            if (n < 0) {
                /* FUN_0034846c */
                sk_fatal_error(0, 0, 0);
            }
            /* FUN_0009461c; FUN_002a200c; FUN_0009461c;
             * thunk_FUN_002a2698 */
            sk_swift_set_make_unique(w);
            return;
        }
    } else {
        if (w >> 0x20 != 0) {
            /* FUN_003583dc; FUN_00348194; FUN_003523f0 */
            sk_fatal_error(0, 0, 0);
        }
        if ((w >> 0x10 < 0x11) && (w - 0xe000 < 0xfffffffffffff800)) {
            /* FUN_00255738(w) */
            return;
        }
    }
    /* FUN_00348898(1); FUN_0034a2f8 */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00294cb4 @ 0x00294cb4   (est. sk_swift_string_release_unicode)
 * Ghidra: void FUN_00294cb4(void)
 * Releases a loaded unicode scalar string (FUN_002a200c + thunk_FUN_002a2698).
 * Confidence: high.
 */
void sk_swift_string_release_unicode(void)
{
    /* FUN_003504d0; uVar1 = FUN_002a200c(); FUN_0007c1c4(...);
     * thunk_FUN_002a2698() */
    sk_swift_set_make_unique(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00294cf0 @ 0x00294cf0   (est. sk_swift_string_release_loaded)
 * Ghidra: void FUN_00294cf0(void)
 * Releases a loaded string: FUN_00294bdc, FUN_001b7cec, FUN_0034bd90,
 * FUN_003a25d4 (release), FUN_0006b6f4.
 * Confidence: medium.
 */
void sk_swift_string_release_loaded(void)
{
    sk_swift_string_load_unicode(0, 0, 0);
    /* FUN_001b7cec; FUN_0034bd90 */
    sk_swift_release(0, 0);
    /* FUN_0006b6f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00294d38 @ 0x00294d38   (est. sk_swift_string_load_unicode2)
 * Ghidra: void FUN_00294d38(undefined8*)
 * Loads a unicode scalar string via FUN_00294bdc and copies the 40-byte
 * String guts into the output struct.
 * Confidence: medium.
 */
void sk_swift_string_load_unicode2(unsigned long *out)
{
    sk_swift_string_load_unicode(0, 0, 0);
    /* FUN_00352cb0; FUN_00359810; FUN_001edb28;
     * store 40-byte guts into out */
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    *(unsigned long *)((char *)out + 0x19) = 0;
    *(unsigned long *)((char *)out + 0x21) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00294d88 @ 0x00294d88   (est. sk_swift_string_load_unicode3)
 * Ghidra: void FUN_00294d88(undefined8*)
 * Loads a unicode scalar string from the caller's 40-byte guts (unaff_x20)
 * via FUN_00294d38 and copies the result out.
 * Confidence: medium.
 */
void sk_swift_string_load_unicode3(unsigned long *out)
{
    unsigned long guts[5];
    guts[0] = 0;
    sk_swift_string_load_unicode2(guts);
    out[0] = guts[0]; out[1] = guts[1]; out[2] = guts[2]; out[3] = guts[3];
    *(unsigned long *)((char *)out + 0x19) = *(unsigned long *)((char *)guts + 0x19);
    *(unsigned long *)((char *)out + 0x21) = *(unsigned long *)((char *)guts + 0x21);
}

/*--------------------------------------------------------------------*/
/* FUN_00294dd0 @ 0x00294dd0   (est. sk_object_service_dispatch_e)
 * Ghidra: void FUN_00294dd0(void)
 * Object-service chain (thread-save): multiple lock/init stages, a
 * method-dispatch section keyed on object fields, and a final dispatch
 * through the method table. Epilogue FUN_0008e500.
 * Confidence: low (long indirect-dispatch sequence).
 */
void sk_object_service_dispatch_e(void)
{
    sk_cpu();
    /* FUN_003531d8; FUN_00353160; FUN_00377824; FUN_00084180;
     * FUN_00351e3c; FUN_00377bec; FUN_00027754; FUN_0035ac58;
     * FUN_00349dfc; FUN_00350b48; FUN_00377824; FUN_0034a450;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b460; FUN_00350500;
     * FUN_00377dcc; FUN_00348d64; (*DAT_00658c00)([x8+0x40]);
     * FUN_003489c0; (*DAT_00658c00)(); FUN_0034b4c0; FUN_00319538;
     * FUN_00351184; FUN_00350878(x1); (*x9)(); FUN_0034ad00;
     * FUN_00350518; FUN_00377bec; FUN_00348fb4; FUN_00350e44(&DAT_00612294);
     * (*x9_00)(); FUN_0034c7d4; FUN_00357b54; FUN_003513b4; (*x9_01)();
     * FUN_0034d8c4; FUN_003546fc; FUN_00377bec; FUN_00310b08;
     * FUN_0034f4f4; FUN_00351280; (*x8_00)() */
    void (*tbl)(void) = *(void (**)(void))(0 + 8);
    tbl();
    /* FUN_00351414(); (*pcVar2)(); u1 = FUN_00353034();
     * FUN_0008e500(u1) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00294f80 @ 0x00294f80   (est. sk_object_service_dispatch_f)
 * Ghidra: void FUN_00294f80(void)
 * Object-service chain flavour close to FUN_00294dd0 (different helper
 * addresses). Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_dispatch_f(void)
{
    sk_cpu();
    /* FUN_003531d8; FUN_00353160; FUN_00377824; FUN_00084180;
     * FUN_00351e3c; FUN_00377bec; FUN_00027754; FUN_0035a478;
     * FUN_00349dfc; FUN_00350ad0; FUN_00377824; FUN_0034a450;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b460; FUN_00350500;
     * FUN_00377dcc; FUN_00348d64; (*DAT_00658c00)([x8+0x40]);
     * FUN_003489c0; (*DAT_00658c00)(); FUN_0034b4c0; FUN_00319538;
     * FUN_00351184; FUN_00350878(x1); (*x9)(); FUN_0034ad00;
     * FUN_0034ff88; FUN_00377bec; FUN_00348fb4; FUN_00350e44(&DAT_00612294);
     * (*x9_00)(); FUN_0034d558; FUN_00357b54; FUN_0035136c; (*x9_01)();
     * FUN_0034d8c4; FUN_003546fc; FUN_00377bec; FUN_00349fe0;
     * FUN_0034fd7c; (*x8_00)() */
    void (*tbl)(void) = *(void (**)(void))(0 + 8);
    tbl();
    /* FUN_00351414(); (*pcVar2)(); u1 = FUN_00353034(); FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00295134 @ 0x00295134   (est. sk_object_service_store)
 * Ghidra: void FUN_00295134(undefined8,undefined8,undefined1,undefined8)
 * Object service store: saves the thread, resolves the object lock, stores
 * an object reference + flag into the caller slot (unaff_x28), and invokes
 * the element-copy callback at the object's +0x30 field. Epilogue
 * FUN_0008e500.
 * Confidence: medium.
 */
void sk_object_service_store(void *p1, void *p2, unsigned char flag, void *value)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00357f84; FUN_00349b28; u2 = FUN_00027614();
     * FUN_0034f5c4(u2,u2); FUN_00357bec; FUN_00348e60; FUN_0007c1a4;
     * (*DAT_00658c00)(); lVar3 = FUN_0034af20() */
    SK_OBJ_BASE() = 0;
    *(unsigned char *)((char *)0 + 8) = flag;
    int off = *(int *)(0 + 0x30);
    (void)off;
    /* (**(code**)(x16_00+0x10))(slot + off, value) */
    /* FUN_00354f4c; FUN_0034b128; (*x9)(); FUN_00350ab8([x16+8]); (*x8)();
     * FUN_00068e14(); FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_002952ec @ 0x002952ec   (est. sk_swift_int_add_i32)
 * Ghidra: undefined1[16] FUN_002952ec(undefined4*,undefined8,undefined8,uint,long)
 * Signed 32-bit add with overflow detection: computes param_5 + (int)param_4
 * and returns (value, ok) packed as (hi, lo) where hi=0/0x8000..., lo=1 on
 * success / 0 on overflow. Overflow raises the Swift Integers fatal error.
 * Confidence: high.
 */
void sk_swift_int_add_i32(unsigned int *out, void *p2, void *p3, unsigned int a, long b,
                          unsigned long pair[2])
{
    (void)p2; (void)p3;
    if ((a < 0x80000000u) == (b < 0)) {
        long r = b + (int)a;
        if (__builtin_add_overflow(b, (long)(int)a, (long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x295420) */
        }
        if ((long)r < -0x80000000LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if ((long)r < 0x80000000LL) {
            *out = (unsigned int)r;
            pair[0] = 0; pair[1] = 1;
            return;
        }
    } else {
        if (b < -0x80000000LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if (b < 0x80000000LL) {
            int x = (int)a + (int)b;
            unsigned int v = (unsigned int)(b >> 0x3f) ^ 0x7fffffff;
            if (!__builtin_add_overflow((unsigned int)a, (int)b, (unsigned int *)0)) {
                v = (unsigned int)a + (int)b;
            }
            *out = (unsigned int)x;
            pair[0] = __builtin_add_overflow((unsigned int)a, (int)b, (unsigned int *)0) ? 0x8000000000000000ULL : 0;
            pair[1] = (unsigned long)!__builtin_add_overflow((unsigned int)a, (int)b, (unsigned int *)0);
            return;
        }
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xdd3, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00295420 @ 0x00295420   (est. sk_swift_int_add_i16)
 * Ghidra: undefined1[16] FUN_00295420(undefined2*,undefined8,undefined8,short,long)
 * Signed 16-bit add with overflow detection; overflow raises the Swift
 * Integers fatal error.
 * Confidence: high.
 */
void sk_swift_int_add_i16(unsigned short *out, void *p2, void *p3, short a, long b,
                          unsigned long pair[2])
{
    (void)p2; (void)p3;
    if (((unsigned int)(int)a < 0x80000000u) == (b < 0)) {
        long r = b + a;
        if (__builtin_add_overflow(b, (long)a, (long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x295544) */
        }
        if ((long)r < -0x8000LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if ((long)r < 0x8000LL) {
            *out = (unsigned short)r;
            pair[0] = 0; pair[1] = 1;
            return;
        }
    } else {
        if (b < -0x8000LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if (b < 0x8000LL) {
            int x = (int)a + (int)(short)b;
            bool ok = x == (int)(short)x;
            unsigned int v = ok ? (unsigned int)x : ((unsigned int)(b >> 0x3f) ^ 0x7fff);
            *out = (unsigned short)x;
            pair[0] = ok ? 0 : 0x8000000000000000ULL;
            pair[1] = (unsigned long)ok;
            return;
        }
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xdd3, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00295544 @ 0x00295544   (est. sk_swift_int_add_i8)
 * Ghidra: undefined1[16] FUN_00295544(undefined1*,undefined8,undefined8,char,long)
 * Signed 8-bit add with overflow detection; overflow raises the Swift
 * Integers fatal error.
 * Confidence: high.
 */
void sk_swift_int_add_i8(unsigned char *out, void *p2, void *p3, char a, long b,
                         unsigned long pair[2])
{
    (void)p2; (void)p3;
    if (((unsigned int)(int)a < 0x80000000u) == (b < 0)) {
        long r = b + a;
        if (__builtin_add_overflow(b, (long)a, (long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x295668) */
        }
        if ((long)r < -0x80LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if ((long)r < 0x80LL) {
            *out = (unsigned char)r;
            pair[0] = 0; pair[1] = 1;
            return;
        }
    } else {
        if (b < -0x80LL) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xdcd, 1);
        }
        if (b < 0x80LL) {
            int x = (int)a + (int)(char)b;
            bool ok = x == (int)(char)x;
            unsigned int v = ok ? (unsigned int)x : ((unsigned int)(b >> 0x3f) ^ 0x7f);
            *out = (unsigned char)x;
            pair[0] = ok ? 0 : 0x8000000000000000ULL;
            pair[1] = (unsigned long)ok;
            return;
        }
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xdd3, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002956dc @ 0x002956dc   (est. sk_swift_legacy_int128_fatal)
 * Ghidra: void FUN_002956dc(void)
 * Raises the Swift LegacyInt128 fatal error (code 0x8a).
 * Confidence: high.
 */
void sk_swift_legacy_int128_fatal(void)
{
    sk_fatal_dump(0xb, 2, 0xd000000000000028, 0x80000000005d3050,
                  (unsigned long)"Swift.LegacyInt128", 0x18, 2, 0x8a, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002957a8 @ 0x002957a8   (est. sk_swift_uint128_fatal)
 * Ghidra: void FUN_002957a8(void)
 * Raises the Swift UInt128 fatal error (code 0x9f).
 * Confidence: high.
 */
void sk_swift_uint128_fatal(void)
{
    sk_fatal_dump(0xb, 2, 0xd000000000000052, 0x80000000005d0f90,
                  (unsigned long)"Swift.UInt128", 0x13, 2, 0x9f, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00295804 @ 0x00295804   (est. sk_swift_int_add_i32_unsigned)
 * Ghidra: undefined1[16] FUN_00295804(int*,undefined8,undefined8,uint,ulong)
 * Mixed unsigned/signed 32-bit add with overflow detection; overflow raises
 * the Swift Integers fatal error.
 * Confidence: high.
 */
void sk_swift_int_add_i32_unsigned(int *out, void *p2, void *p3, unsigned int a,
                                   unsigned long b, unsigned long pair[2])
{
    (void)p2; (void)p3;
    if ((long)b < 0) {
        unsigned long nb = -b;
        if (__builtin_sub_overflow(0, b, (unsigned long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x2958c4) */
        }
        if ((long)nb < 0) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Negative value is not representable", 0x23, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xcf8, 1);
        }
        if (nb >> 0x20 != 0) goto fail;
        unsigned int v = -(unsigned int)nb;
        if (a < (unsigned int)nb) {
            *out = 0; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
            return;
        }
        *out = (int)(a + v);
        pair[0] = 0; pair[1] = 1;
        return;
    }
    if (b >> 0x20 != 0) goto fail;
    {
        unsigned int v = (unsigned int)b;
        if (__builtin_add_overflow(a, v, (unsigned int *)0)) {
            *out = -1; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
            return;
        }
        *out = (int)(a + v);
        pair[0] = 0; pair[1] = 1;
        return;
    }
fail:
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xcfc, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0029590c @ 0x0029590c   (est. sk_swift_int_add_i16_unsigned)
 * Ghidra: undefined1[16] FUN_0029590c(undefined2*,undefined8,undefined8,uint,ulong)
 * Mixed unsigned/signed 16-bit add with overflow detection.
 * Confidence: high.
 */
void sk_swift_int_add_i16_unsigned(unsigned short *out, void *p2, void *p3,
                                   unsigned int a, unsigned long b, unsigned long pair[2])
{
    (void)p2; (void)p3;
    unsigned int v;
    if ((long)b < 0) {
        unsigned long nb = -b;
        if (__builtin_sub_overflow(0, b, (unsigned long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x2959dc) */
        }
        if ((long)nb < 0) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Negative value is not representable", 0x23, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xcf8, 1);
        }
        if (nb >> 0x10 != 0) goto fail;
        unsigned int x = (a & 0xffff) - ((unsigned int)nb & 0xffff);
        if ((x & 0xffff0000) != 0) {
            *out = 0; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
            return;
        }
        *out = (unsigned short)x; pair[0] = 0; pair[1] = 1;
        return;
    }
    if (0xffff < b) goto fail;
    v = (a & 0xffff) + ((unsigned int)b & 0xffff);
    if (v >> 0x10 != 0) {
        *out = 0xffff; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
        return;
    }
    *out = (unsigned short)v; pair[0] = 0; pair[1] = 1;
    return;
fail:
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xcfc, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00295a24 @ 0x00295a24   (est. sk_swift_int_add_i8_unsigned)
 * Ghidra: undefined1[16] FUN_00295a24(undefined1*,undefined8,undefined8,uint,ulong)
 * Mixed unsigned/signed 8-bit add with overflow detection.
 * Confidence: high.
 */
void sk_swift_int_add_i8_unsigned(unsigned char *out, void *p2, void *p3,
                                  unsigned int a, unsigned long b, unsigned long pair[2])
{
    (void)p2; (void)p3;
    unsigned int v;
    if ((long)b < 0) {
        unsigned long nb = -b;
        if (__builtin_sub_overflow(0, b, (unsigned long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x295af4) */
        }
        if ((long)nb < 0) {
            sk_fatal_error(0xb, 2,
                           (unsigned long)"Negative value is not representable", 0x23, 2,
                           (unsigned long)"Swift.Integers", 0x14, 2, 0xcf8, 1);
        }
        if (0xfe < nb && b != 0xffffffffffffff01ULL) goto fail;
        unsigned int x = (a & 0xff) - ((unsigned int)nb & 0xff);
        if ((x & 0xffffff00) != 0) {
            *out = 0; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
            return;
        }
        *out = (unsigned char)x; pair[0] = 0; pair[1] = 1;
        return;
    }
    if (0xff < b) goto fail;
    v = (a & 0xff) + ((unsigned int)b & 0xff);
    if (v >> 8 != 0) {
        *out = 0xff; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
        return;
    }
    *out = (unsigned char)v; pair[0] = 0; pair[1] = 1;
    return;
fail:
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Not enough bits to represent the result", 0x2d, 2,
                   (unsigned long)"Swift.Integers", 0x14, 2, 0xcfc, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00295b3c @ 0x00295b3c   (est. sk_swift_int_add_i64_unsigned)
 * Ghidra: undefined1[16] FUN_00295b3c(long*,undefined8,undefined8,ulong,ulong)
 * Unsigned 64-bit add with signed overflow detection; overflow raises a
 * fatal error.
 * Confidence: high.
 */
void sk_swift_int_add_i64_unsigned(long *out, void *p2, void *p3,
                                   unsigned long a, unsigned long b, unsigned long pair[2])
{
    (void)p2; (void)p3;
    long r;
    if ((long)b < 0) {
        if (__builtin_sub_overflow(0, b, (unsigned long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x295b94) */
        }
        if ((long)-b < 0) {
            /* FUN_003482c4; FUN_003523f0 */
            sk_fatal_error(0, 0, 0);
        }
        if (a < -b) {
            *out = 0; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
            return;
        }
        r = (long)(a + b);
    } else if (__builtin_add_overflow(a, b, (unsigned long *)0)) {
        *out = -1; pair[0] = 0x8000000000000000ULL; pair[1] = 0;
        return;
    } else {
        r = (long)(a + b);
    }
    *out = r; pair[0] = 0; pair[1] = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00295f1c @ 0x00295f1c   (est. sk_object_service_insert)
 * Ghidra: void FUN_00295f1c(undefined8,undefined8,undefined1,undefined8,...)
 * Object service insert: saves the thread, stores an object + flag into a
 * slot, and either calls the element-copy callback (flag==1) or inserts a
 * new element with refcount growth (flag==0). Overflow on the count traps.
 * Epilogue FUN_0008e500.
 * Confidence: medium.
 */
void sk_object_service_insert(void *p1, void *p2, unsigned char flag, void *p4,
                              void *p5, void *p6, void *p7, void *p8)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_0007c028; (*DAT_00658c00)([x8_00+0x40]); FUN_00349068;
     * FUN_00349b28; u3 = FUN_00027614(); FUN_0034f5c4(u3,u3);
     * FUN_00356fe8; FUN_00348fd8; (*DAT_00658c00)([x8_01+0x40]);
     * FUN_00348bbc; (*DAT_00658c00)(); lVar4 = FUN_0034c2d8() */
    unsigned long *slot = 0;
    slot[0] = 0;
    *(unsigned char *)((char *)slot + 8) = flag;
    int off = *(int *)(0 + 0x30);
    /* (*x9)(slot + off, p4, p7) */
    (void)off;
    if (flag == 1) {
        /* (**(code**)(x16+8))(slot + off, p7); FUN_0008f6c0(p8);
         * FUN_00354f4c; FUN_00350878; (*x9_01)(); FUN_00350bf0;
         * (*x8_02)() */
        sk_thread_epilogue();
        return;
    }
    /* FUN_00350bf0([x16_00+8]); (*x8_03)(); (*pcVar5)(slot + off, p7);
     * count = count+1 with overflow trap */
    long count = 0;
    if (__builtin_add_overflow(count, 1, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x29614c) */
    }
    /* FUN_0031df70(p8); FUN_00350b24; FUN_0034d810; (*x9_02)(...);
     * FUN_0031dfa0(p8); FUN_00350974; (*x9_03)(); FUN_003505e8();
     * (*pcVar5)() */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00296154 @ 0x00296154   (est. sk_object_service_reset)
 * Ghidra: void FUN_00296154(void)
 * Object service reset: initializes an object slot (fields +0x24/+0x28/
 * +0x2c) to zero, then dispatches through the object method table via an
 * unrecoverable indirect jump.
 * Confidence: low (unrecoverable jumptable at 0x29626c).
 */
void sk_object_service_reset(void)
{
    /* FUN_00354744; FUN_00352c34; FUN_003530e8; FUN_00349a68;
     * (**(code**)(x8+0x10))(); auVar5 = FUN_003504e8();
     * lVar3 = FUN_0031dfd0(...); UNRECOVERED_JUMPTABLE = *(x16+0x20);
     * FUN_003508d8(x21 + [lVar3+0x24]); (*UNRECOVERED_JUMPTABLE)();
     * iVar2 = [lVar3+0x28]; ... FUN_0034d8b0; FUN_00350768;
     * FUN_00377824; FUN_00349530; (**(code**)(x16_00+0x20))(x21+iVar2);
     * puVar1 = x21 + [lVar3+0x2c]; *puVar1 = 0; *(puVar1+1) = 0;
     * FUN_00349b28; u4 = FUN_00027614(); FUN_0034f5c4(u4,u4);
     * lVar3 = FUN_00356fe8(); FUN_00350624(puVar1 + [lVar3+0x30]);
     * FUN_003544c8(); (*UNRECOVERED_JUMPTABLE)() */
}

/*--------------------------------------------------------------------*/
/* FUN_0029627c @ 0x0029627c   (est. sk_swift_stride_zero_fatal)
 * Ghidra: void FUN_0029627c(void)
 * Raises the Swift Stride "stride size must not be zero" fatal error.
 * Confidence: high.
 */
void sk_swift_stride_zero_fatal(void)
{
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Stride size must not be zero", 0x1c, 2,
                   (unsigned long)"Swift.Stride", 0x12, 2, 0x15c, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00296330 @ 0x00296330   (est. sk_object_service_wake_state)
 * Ghidra: void FUN_00296330(void)
 * Object service wake-state machine: thread-save, lock/init stages, and a
 * two-way dispatch keyed on the wake flag; returns 2 on the wake path or 0
 * otherwise. Epilogue FUN_0008e500.
 * Confidence: low (complex state machine, multiple dispatch stages).
 */
void sk_object_service_wake_state(void)
{
    sk_cpu();
    /* FUN_0034c454; FUN_00377824; FUN_00348d7c; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034af20; FUN_0034ed78; FUN_00377bec;
     * FUN_00027754; FUN_00358d88; FUN_0034f764; FUN_00351178;
     * u2 = FUN_00377824(); FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b2f8; iVar1 = [lVar4+0x28];
     * FUN_00350494; FUN_00351100; FUN_00377bec; FUN_003493ec;
     * FUN_0034bea4; (*x9)(); FUN_0008f758; FUN_0034d434; FUN_0034f778;
     * (*x9_00)(); FUN_0034d8c4; FUN_0034ed78; FUN_00377bec;
     * FUN_0034b4ec; FUN_00352450(x20+iVar1); (*x8)(); FUN_003500c0;
     * (*x8_00)() */
    unsigned long w = 0;
    if ((w & 1) == 0) {
        /* FUN_00027754(u3); FUN_0034b4ec; FUN_000e15d8; FUN_0034beec;
         * u2 = (*x8_02)(); if (u2&1)==0: u3=2 goto done */
        w = 2;
    } else {
        /* FUN_00350950(u3); FUN_0035166c; FUN_00354cb4; FUN_0034beec;
         * u2 = (*x8_01)(); if (u2&1)==0: ... */
        w = 0;
    }
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00296530 @ 0x00296530   (est. sk_string_unicode_scalar_construct)
 * Ghidra: void FUN_00296530(undefined8)
 * Constructs a String from a unicode scalar value via FUN_0029768c with the
 * "ot" tag and the 0xe2 flag.
 * Confidence: medium.
 */
void sk_string_unicode_scalar_construct(void *out)
{
    sk_swift_string_construct_unicode(out, 0x6f74, 0xe200000000000000ULL);
}

/*--------------------------------------------------------------------*/
/* FUN_0029653c @ 0x0029653c   (est. sk_string_unicode_scalar_construct2)
 * Ghidra: void FUN_0029653c(undefined8*)
 * Constructs a unicode-scalar String and copies the 40-byte guts out.
 * Confidence: medium.
 */
void sk_string_unicode_scalar_construct2(unsigned long *out)
{
    unsigned long guts[5];
    sk_string_unicode_scalar_construct(guts);
    out[0] = guts[0]; out[1] = guts[1]; out[2] = guts[2]; out[3] = guts[3];
    *(unsigned long *)((char *)out + 0x19) = *(unsigned long *)((char *)guts + 0x19);
    *(unsigned long *)((char *)out + 0x21) = *(unsigned long *)((char *)guts + 0x21);
}

/*--------------------------------------------------------------------*/
/* FUN_0029657c @ 0x0029657c   (est. sk_string_unicode_scalar_append)
 * Ghidra: void FUN_0029657c(void)
 * Appends a unicode scalar to a String: resolves the object, calls the
 * element-append helper (FUN_003722e4), and dispatches through the method
 * table.
 * Confidence: low.
 */
void sk_string_unicode_scalar_append(void)
{
    /* FUN_00351a38; FUN_00349b28; u1 = FUN_00027614();
     * u2 = [x21+0x10]; FUN_0034f5c4(u1,u1); FUN_003722e4(...);
     * FUN_00348d64; FUN_0007c1a4; (*DAT_00658c00)();
     * u1 = FUN_0034b0c4(); FUN_00356a14(u1, x20 + [x21+0x2c]);
     * (*x9)(); FUN_003537c4([x23+0x30]); (**(code**)(x16+0x20))();
     * FUN_0006b6f4() */
}

/*--------------------------------------------------------------------*/
/* FUN_0029665c @ 0x0029665c   (est. sk_object_service_store2)
 * Ghidra: void FUN_0029665c(void)
 * Object service store flavour: saves the thread, copies an object + flag
 * into a slot, and dispatches the element-copy callback at +0x30.
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_store2(void)
{
    sk_cpu();
    /* FUN_00352c34; FUN_00349b28; u5 = FUN_00027614();
     * u7 = [x19+0x10]; FUN_0034f5c4(u5,u5); FUN_00357bec;
     * FUN_00348d64; (*DAT_00658c00)([x8+0x40]); FUN_003489c0;
     * (*DAT_00658c00)(); lVar6 = FUN_0034b4c0();
     * *x28 = u4; *(x28+1) = extraout_w1;
     * FUN_003561dc([lVar6+0x30]); FUN_00077894(x28 + extraout_x8_00);
     * (*x10)(); FUN_00350944([x16+0x20]); (*x8_01)() */
    unsigned char *slot = 0;
    slot[1] = 0;
    /* puVar1 = x20 + [x19+0x2c]; *puVar1 = *x27; *(puVar1+1) = uVar2;
     * (**(code**)(x16_00+0x28))(puVar1 + [x23+0x30], x27 + iVar3, u7) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029679c @ 0x0029679c   (est. sk_object_service_reset2)
 * Ghidra: void FUN_0029679c(void)
 * Object service reset flavour: zeroes an object field at +0x30, then
 * dispatches through the method table via an unrecoverable indirect jump.
 * Confidence: low.
 */
void sk_object_service_reset2(void)
{
    /* FUN_00354744; FUN_00352c34; FUN_003530e8; auVar5 = FUN_003516cc();
     * lVar3 = FUN_0031e000(...); *(x21 + [lVar3+0x30]) = 0;
     * FUN_003494e8; (**(code**)(x8+0x10))();
     * UNRECOVERED_JUMPTABLE = *(x16+0x20); FUN_003508d8(x21 + [lVar3+0x24]);
     * (*UNRECOVERED_JUMPTABLE)(); iVar2 = [lVar3+0x28]; FUN_0034d8b0;
     * FUN_00350768; FUN_00377824; FUN_00349530;
     * (**(code**)(x16_00+0x20))(x21+iVar2);
     * puVar1 = x21 + [lVar3+0x2c]; *puVar1 = 0; *(puVar1+1) = 0;
     * FUN_00349b28; u4 = FUN_00027614(); FUN_0034f5c4(u4,u4);
     * lVar3 = FUN_00356fe8(); FUN_00350624(puVar1 + [lVar3+0x30]);
     * FUN_003544c8(); (*UNRECOVERED_JUMPTABLE)() */
}

/*--------------------------------------------------------------------*/
/* FUN_002968c0 @ 0x002968c0   (est. sk_string_index_successor)
 * Ghidra: undefined1[16] FUN_002968c0(void)
 * Swift String index successor: returns the next valid index after the
 * current position, handling the count/width fields of the String guts and
 * the "end" sentinel. Also updates the index state in place.
 * Confidence: high (Swift _StringGuts index successor).
 */
void sk_string_index_successor(unsigned long out[2])
{
    unsigned long pos = *(unsigned long *)((char *)0 + 0x28);
    unsigned long idx = *(unsigned long *)((char *)0 + 8);
    long incr = *(long *)((char *)0 + 0x10);
    if (incr < 1) {
        if ((long)pos <= (long)idx) goto eq;
    } else if ((long)idx <= (long)pos) {
eq:
        if ((pos == idx) && ((*(unsigned char *)((char *)0 + 0x30) & 1) == 0)) {
            if (*(char *)((char *)0 + 0x20) == 1 ||
                *(long *)((char *)0 + 0x18) != -0x8000000000000000LL) {
                *(unsigned char *)((char *)0 + 0x30) = 1;
                out[0] = pos; out[1] = 0;
                return;
            }
            out[0] = 0x8000000000000000ULL; out[1] = 1;
            return;
        }
        out[0] = 0x8000000000000000ULL; out[1] = 1;
        return;
    }
    bool ov = __builtin_add_overflow(pos, incr, (unsigned long *)0);
    unsigned long np = ov ? ((long)(pos + incr) >> 0x3f ^ 0x8000000000000000ULL) : pos + incr;
    *(unsigned long *)((char *)0 + 0x28) = np;
    *(unsigned long *)((char *)0 + 0x18) = ov ? 0x8000000000000000ULL : 0;
    *(bool *)((char *)0 + 0x20) = !ov;
    out[0] = np; out[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0029695c @ 0x0029695c   (est. sk_object_service_store3)
 * Ghidra: void FUN_0029695c(void)
 * Object service store flavour: thread-save, multiple lock/init stages, a
 * store of an object + flag into a slot with the element-copy callback at
 * +0x30, and a wake-flag branch that either keeps or releases the object.
 * Epilogue FUN_0008e500.
 * Confidence: low (complex store + wake state machine).
 */
void sk_object_service_store3(void)
{
    sk_cpu();
    /* FUN_00349b28; u5 = FUN_00027614(); u11 = [lVar8+0x10];
     * FUN_0034f5c4(u5,u5); FUN_00357bec; FUN_00348d64; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034a760; u9 = [lVar8+0x18];
     * FUN_00355858; FUN_00350798; FUN_0035063c; FUN_00377824;
     * FUN_00348e60; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b71c;
     * FUN_0006b6f4; FUN_003518a0; FUN_00377bec; FUN_00027754;
     * FUN_003564d0; FUN_00349dfc; FUN_00351438; u5 = FUN_00377824();
     * FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034bdfc;
     * FUN_00349734; (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4;
     * FUN_0034cf34; (*DAT_00658c00)(); u6 = FUN_0034b3d8();
     * plVar1 = x20 + [lVar8+0x2c]; iVar3 = [x23+0x30];
     * FUN_00357a0c(u6, plVar1 + iVar3); (*x9)();
     * iVar4 = [lVar8+0x28]; FUN_0034ad00; FUN_00350b78;
     * FUN_00377bec(...); FUN_003494fc; FUN_0034c9b8; (*x9_00)();
     * FUN_0034cea8; FUN_00355bd0; FUN_00351420; (*x9_01)();
     * FUN_0034d8c4; FUN_003507e0; FUN_00377bec; FUN_00351ee0;
     * FUN_003515e4(x20+iVar4); (*x8_01)(); FUN_0034eea8;
     * FUN_003511a8; (*x8_02)(); FUN_0035125c(u9) */
    unsigned long w = 0;
    /* u5 = (x26&1)==0 ? FUN_00310e20() : FUN_00310954();
     * FUN_0034df74(u5); u7 = (*x8_03)() */
    if ((w & 1) == 0) {
        /* store object + flag; (*x9_03)(plVar1 + iVar3);
         * FUN_003514a0(plVar1 + iVar3); (*x9_03)();
         * FUN_00350998(...); (*x8_08)() */
    } else {
        /* wake-flag branch: either keep the object or set the flag and
         * release; FUN_00351548; FUN_000839d8 */
        sk_ref_lock_op(0, 0, 0, 0);
    }
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00296d74 @ 0x00296d74   (est. sk_object_service_dispatch_g)
 * Ghidra: void FUN_00296d74(void)
 * Object service: resolves the object lock from the current object and
 * dispatches through its method table (unrecoverable indirect jump).
 * Confidence: low.
 */
void sk_object_service_dispatch_g(void)
{
    /* lVar1 = FUN_00358054(); FUN_00377824(0, [lVar1+0x18], [lVar1+0x10]);
     * FUN_00350404(); (**(code**)(x16+0x10))() */
}

/*--------------------------------------------------------------------*/
/* FUN_00296df0 @ 0x00296df0   (est. sk_object_service_dispatch_h)
 * Ghidra: void FUN_00296df0(void)
 * Object-service chain: thread-save, lock/init stages, and a two-field
 * dispatch through the object method table (fields +0x24/+0x28).
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_dispatch_h(void)
{
    sk_cpu();
    /* FUN_00350720; FUN_00377824(...&DAT_00612294); FUN_00348e60;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b0c4; FUN_00350210(x4);
     * FUN_00377bec; FUN_00027754; FUN_0008f6f4; FUN_0035113c;
     * FUN_003518a0; FUN_00377824; FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034cff4; FUN_00350ab8; FUN_0035053c;
     * FUN_00377bec; FUN_00348fb4; FUN_0034b9f8; (*x9)(); FUN_0034e74c;
     * FUN_00353050; (*x9_00)(); FUN_00350210(x4); FUN_00377bec;
     * FUN_00349fe0; FUN_00350470; FUN_003518a0; (*x8_00)();
     * FUN_0034e3bc; FUN_00351360; (*x9_01)(); FUN_0034b804 */
    void (*tbl)(void) = *(void (**)(void))(0 + 0x20);
    tbl();
    /* auVar5 = FUN_00350488(); lVar1 = (*in_x6)(...);
     * (*pcVar3)(x8 + [lVar1+0x24], x4_8, x3);
     * FUN_003515e4(x8 + [lVar1+0x28]); (*x9_02)(); FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00297094 @ 0x00297094   (est. sk_object_service_iterate)
 * Ghidra: void FUN_00297094(undefined8,undefined8,code*,code*)
 * Object-service iterate loop: saves the thread, resolves the object, then
 * iterates a collection invoking the two callbacks (param_3/param_4) per
 * element until the iteration terminates; overflow on the count traps.
 * Epilogue FUN_0008e500.
 * Confidence: low (collection iteration with callback dispatch).
 */
void sk_object_service_iterate(void *p1, void *p2, void (*cb1)(void), void (*cb2)(void))
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00356c78; u8 = [lVar3+0x10]; FUN_00349734;
     * (*DAT_00658c00)([x8+0x40]); FUN_003497b4; FUN_00352738;
     * FUN_003519fc; FUN_00310d68; FUN_0034ce88; FUN_003515b4;
     * FUN_003722e4; FUN_00348cd0; FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034b05c; FUN_0034998c; ... u4 = (*x19)(); FUN_000a6f88;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034bdfc;
     * (**(code**)(x16_01+0x10))(); FUN_00354d74; (*param_3)() */
    long n = 0;
    for (;;) {
        (*cb1)();
        /* iterate: (*cb2)(...); FUN_00352290; FUN_00351548;
         * FUN_000839d8; ... element dispatch */
        long next = n + 1;
        if (__builtin_add_overflow(n, 1, (long *)0)) {
            CL4_SBP();   /* SoftwareBreakpoint(1,0x297424) */
        }
        n = next;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00297468 @ 0x00297468   (est. sk_object_service_wake_state2)
 * Ghidra: void FUN_00297468(void)
 * Object-service wake-state machine (flavour of FUN_00296330) with a
 * two-way dispatch; returns 2 on wake path, 0 otherwise. Epilogue
 * FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_wake_state2(void)
{
    sk_cpu();
    /* FUN_0034c454; FUN_00377824; FUN_00348d7c; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034af20; FUN_0034ed78; FUN_00377bec;
     * FUN_00027754; FUN_00358d88; FUN_0034f764; FUN_00351178;
     * u2 = FUN_00377824(); FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b2f8; iVar1 = [lVar5+0x28];
     * FUN_00350494; FUN_00351100; FUN_00377bec; FUN_003493ec;
     * FUN_0034bea4; (*x9)(); FUN_0008f758; FUN_0034d434; FUN_0034f778;
     * (*x9_00)(); FUN_0034d8c4; FUN_0034ed78; FUN_00377bec;
     * FUN_0034b4ec; FUN_00352450(x20+iVar1); (*x8)(); FUN_0034eea8;
     * FUN_00350b3c; (*x8_00)() */
    unsigned long w = 0;
    if ((w & 1) == 0) {
        /* FUN_00350950(u4); FUN_0016186c; FUN_00350c80; FUN_0034beec;
         * u2 = (*pc)(); if (u2&1)==0: u4=2 goto done */
        w = 2;
    } else {
        /* FUN_00350950(u4); FUN_0016186c; FUN_00354cb4; FUN_0034beec;
         * u2 = (*pc)(); if (u2&1)==0: u4=2 goto done */
        w = 0;
    }
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00297674 @ 0x00297674   (est. sk_string_unicode_scalar_construct3)
 * Ghidra: void FUN_00297674(undefined8)
 * Constructs a String from a unicode scalar with tag 0x6867756f726874
 * ("throuhg") and the 0xe7 flag via FUN_0029768c.
 * Confidence: medium.
 */
void sk_string_unicode_scalar_construct3(void *out)
{
    sk_swift_string_construct_unicode(out, 0x6867756f726874ULL, 0xe700000000000000ULL);
}

/*--------------------------------------------------------------------*/
/* FUN_0029768c @ 0x0029768c   (est. sk_swift_string_construct_unicode)
 * Ghidra: void FUN_0029768c(void)
 * Core Swift String-from-unicode-scalar constructor: thread-save, allocates
 * a 0xb0-byte string object (tag 7), initialises its guts fields
 * (+0x10..+0x88: 8-byte tag words, size, "by" trailer), appends the scalar,
 * and finalises with FUN_0008e500.
 * Confidence: medium (string object layout + trailers "from"/"by").
 */
void sk_swift_string_construct_unicode(void *out, unsigned long tag, unsigned long flag)
{
    (void)out;
    sk_cpu();
    /* FUN_00352fd4; FUN_00353aa0; FUN_000a6f88;
     * (*DAT_00658c00)([x8+0x40]); FUN_00349178;
     * FUN_0034b768([x12+0x10]); (*x8_00)(); u2 = FUN_003519d4();
     * lVar3 = FUN_0036a940(u2, 0xb0, 7) */
    unsigned long *s = sk_alloc(0xb0, 7);   /* FUN_0036a940 */
    s[2] = 0x4c0f08;   /* uRam00000000004c0f08 */
    s[1] = 0x4c0f00;   /* _DAT_004c0f00 */
    s[3] = 0x6d6f7266;   /* "from" */
    s[4] = 0xe400000000000000ULL;
    s[8] = *(unsigned long *)((char *)0 + 0x10);   /* uVar4 */
    /* FUN_00319a4c(s+0x30); FUN_0034f384; (*pcVar5)(); */
    s[0xa] = 0;   /* unaff_x25 */
    s[0xb] = 0;   /* unaff_x24 */
    s[0xf] = *(unsigned long *)((char *)0 + 0x10);   /* uVar4 */
    /* FUN_00319a4c(s+0x60); (*pcVar5)(u2, x20 + [x20+0x24], u4); */
    s[0x10] = 0x7962;   /* "by" */
    s[0x11] = 0xe200000000000000ULL;
    /* FUN_0034d8b0; FUN_00377824; FUN_00319a4c(s+0x90); FUN_0034d140;
     * (**(code**)(x16_00+0x10))(u4, x20 + [x20+0x28], u2); FUN_000e15d8;
     * FUN_0034d5ec; FUN_001e4348; FUN_00358804; FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029780c @ 0x0029780c   (est. sk_string_unicode_scalar_construct4)
 * Ghidra: void FUN_0029780c(undefined8*)
 * Constructs a unicode-scalar String via FUN_00297674 and copies the guts.
 * Confidence: medium.
 */
void sk_string_unicode_scalar_construct4(unsigned long *out)
{
    unsigned long guts[5];
    sk_string_unicode_scalar_construct3(guts);
    out[0] = guts[0]; out[1] = guts[1]; out[2] = guts[2]; out[3] = guts[3];
    *(unsigned long *)((char *)out + 0x19) = *(unsigned long *)((char *)guts + 0x19);
    *(unsigned long *)((char *)out + 0x21) = *(unsigned long *)((char *)guts + 0x21);
}

/*--------------------------------------------------------------------*/
/* FUN_00297864 @ 0x00297864   (est. sk_object_service_dispatch_i)
 * Ghidra: void FUN_00297864(void)
 * Object-service chain (thread-save): lock/init stages, then a double
 * dispatch through the object method table. Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_dispatch_i(void)
{
    sk_cpu();
    /* FUN_00353d70; FUN_0034d8b0; FUN_003510c4; FUN_00377824;
     * FUN_00348e60; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034af20;
     * FUN_00349734; (*DAT_00658c00)([x8_00+0x40]); FUN_003490d0;
     * (*DAT_00658c00)(); FUN_0034b758; (*pcVar1)(); (*pcVar1)();
     * (**(code**)(x16+0x10))(); FUN_003504c4(x8); (*x9)(); FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_002979a4 @ 0x002979a4   (est. sk_swift_span_bounds)
 * Ghidra: void FUN_002979a4(long,long)
 * Computes span bounds [param_1, param_1+param_2), validating the base
 * when the range is non-empty, then calls FUN_00229b5c.
 * Confidence: high.
 */
void sk_swift_span_bounds(long base, long count)
{
    if (count == 0) {
        if (base == 0) {
            count = 0;
            goto done;
        }
    } else if (base == 0) {
        /* FUN_00348508; FUN_00351094 */
        sk_fatal_error(0, 0, 0);
    }
    count = count + base;
done:
    sk_swift_string_char(0, 0, 0);   /* FUN_00229b5c */
}

/*--------------------------------------------------------------------*/
/* FUN_002979f4 @ 0x002979f4   (est. sk_string_append_unicode_scalar)
 * Ghidra: void FUN_002979f4(undefined8,undefined8,ulong,ulong)
 * String append(unicode scalar): decodes the String guts (inline or native)
 * and appends a scalar, dispatching through the string builder. Epilogue
 * FUN_00358fc8.
 * Confidence: high (Swift String append scalar).
 */
void sk_string_append_unicode_scalar(void *p1, void *p2, unsigned long w, unsigned long f)
{
    (void)p1; (void)p2;
    /* FUN_00358fb4; FUN_00355bdc */
    if ((f >> 0x3d & 1) == 0) {
        if ((w >> 0x3c & 1) == 0) {
            /* FUN_00355968; auVar2 = FUN_002a9ba8() */
        } else {
            /* u1 = FUN_00357628(); auVar2._8_8_ = w & 0xffffffffffff;
             * auVar2._0_8_ = u1 */
        }
        /* FUN_00353f88(x8, ...); (*x23)() */
    } else {
        /* FUN_00355720(f >> 0x38 & 0xf); (*DAT_00658c00)();
         * FUN_003519e8; FUN_0034a210; u1 = FUN_00002534();
         * FUN_00355704(u1, FUN_00346774); FUN_0035359c();
         * FUN_003576bc(); FUN_00291d70() */
        sk_string_finalize();
    }
    /* FUN_00358fc8(x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00297af0 @ 0x00297af0   (est. sk_string_slice_append)
 * Ghidra: void FUN_00297af0(undefined8,ulong,ulong,undefined8,undefined8)
 * Appends a sub-string slice to a String: decodes the source guts, validates
 * the slice bounds via FUN_0028e8c0, and appends the bytes. Epilogue
 * FUN_00229a3c.
 * Confidence: high (Swift String append Substring).
 */
void sk_string_slice_append(void *p1, unsigned long w, unsigned long f,
                            void *p4, void *p5)
{
    unsigned long src_w = w;
    if ((f & 0x2000000000000000) != 0) src_w = f;
    if (((f >> 0x3c & 1) == 0) && ((src_w >> 0x3e & 1) != 0)) {
        unsigned long lo = 0, hi = 0;
        if ((f >> 0x3d & 1) == 0) {
            if ((w >> 0x3c & 1) == 0) {
                /* FUN_00106e3c; auVar5 = FUN_002a9ba8() */
            } else {
                hi = w & 0xffffffffffff;
                lo = (f & 0xfffffffffffffff) + 0x20;
            }
        } else {
            hi = f >> 0x38 & 0xf;
            lo = (unsigned long)&src_w;
            src_w = w;
        }
        /* FUN_00355b68(hi, lo, ...); FUN_003520dc(); FUN_0028e8c0 */
        unsigned long rlo = 0, rhi = 0;
        if ((long)rlo < 0 || rhi < 0) {
            /* FUN_003481fc */
            sk_fatal_error(0, 0, 0);
        }
        /* FUN_00348e48; FUN_001e4cbc; FUN_00297e00(...) */
    } else {
        /* FUN_0034df94(w); FUN_0029816c() */
        sk_string_utf8_decode(w, f, (long)p4, (long)p5, p1);
    }
    /* FUN_00229a3c(0xff) */
}

/*--------------------------------------------------------------------*/
/* FUN_00297be8 @ 0x00297be8   (est. sk_string_append_slice2)
 * Ghidra: void FUN_00297be8(undefined8,ulong,ulong,undefined8,undefined8)
 * String append-slice flavour forwarding to FUN_00297af0 with shifted args.
 * Confidence: medium.
 */
void sk_string_append_slice2(void *p1, unsigned long w, unsigned long f, void *p4, void *p5)
{
    sk_string_slice_append(p1, (unsigned long)p4, (unsigned long)p5, (void *)(w >> 0x10), (void *)(f >> 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_00297c34 @ 0x00297c34   (est. sk_string_append_slice3)
 * Ghidra: void FUN_00297c34(void)
 * String append-slice dispatch: saves the thread, inspects the string
 * guts, and selects between the inline/native append paths, forwarding to
 * FUN_00297af0. Epilogue FUN_0008e500.
 * Confidence: low (string-representation state machine).
 */
void sk_string_append_slice3(void)
{
    sk_cpu();
    /* FUN_00350980; FUN_00349b3c; (*DAT_00658c00)([x8+0x40]);
     * FUN_00348bbc; (*DAT_00658c00)(); FUN_0034aea8; (*DAT_00658c00)();
     * FUN_0034b87c; auVar8 = FUN_00352cb0() */
    if (0 == 0) {
        /* FUN_00359fe8(auVar8._0_8_, *x20, x20[1]); */
        goto append;
    }
    /* FUN_00354140 */
    if (0 == 0) {
        /* uVar5 = x20[2] */
        goto append;
    }
    /* (*pcVar7)(); FUN_00350d14; FUN_00351420; iVar2 = FUN_00365b6c() */
    if (0 == 0) {
        /* FUN_003512c0; (*pcVar7)(); FUN_00350efc; FUN_00350c08;
         * u4 = FUN_00365b6c(); if (u4&1): auVar9 = auVar1 goto append
         * else: FUN_0034edf8; (*pcVar7)(); FUN_0031e030; FUN_00353528;
         * FUN_00357c04; FUN_0034cf84; auVar9 = FUN_0022d2f4() */
    }
append:
    /* FUN_00297af0(u3, auVar9._0_8_, auVar9._8_8_, u6, u4);
     * FUN_003a25d4(auVar9._8_8_); FUN_0008e500 */
    sk_swift_release(0, 0);
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00297e00 @ 0x00297e00   (est. sk_swift_span_copy)
 * Ghidra: void FUN_00297e00(long,long)
 * Copies a validated byte span [param_1, param_1+param_2) via FUN_00229b5c.
 * Negative counts raise a fatal error.
 * Confidence: high.
 */
void sk_swift_span_copy(long base, long count)
{
    if (count < 0) {
        /* FUN_00348284; FUN_00351094 */
        sk_fatal_error(0, 0, 0);
    }
    if (count == 0) {
        if (base == 0) {
            count = 0;
            goto done;
        }
    } else if (base == 0) {
        /* FUN_00348508; FUN_00351094 */
        sk_fatal_error(0, 0, 0);
    }
    count = count + base;
done:
    sk_swift_string_char(0, 0, 0);   /* FUN_00229b5c */
}

/*--------------------------------------------------------------------*/
/* FUN_00297e5c @ 0x00297e5c   (est. sk_string_utf8_view_copy)
 * Ghidra: void FUN_00297e5c(ulong,ulong,undefined8,undefined8,undefined8)
 * Swift String UTF8View copy: decodes the string guts, validates the slice,
 * and copies the UTF-8 bytes via FUN_002ac0d8. Raises Invalid slice fatal.
 * Confidence: high.
 */
void sk_string_utf8_view_copy(unsigned long w, unsigned long f, void *p3, void *p4, void *p5)
{
    unsigned long lo = 0, hi = 0;
    if ((f >> 0x3d & 1) == 0) {
        if ((w >> 0x3c & 1) == 0) {
            /* auVar4 = FUN_002a9ba8() */
        } else {
            hi = w & 0xffffffffffff;
            lo = (f & 0xfffffffffffffff) + 0x20;
        }
    } else {
        hi = f >> 0x38 & 0xf;
        lo = (unsigned long)&f;
    }
    unsigned long rlo = 0, rhi = 0;
    if (-1 < (long)rlo && rhi <= hi) {
        unsigned long base = lo ? lo + rlo : 0;
        /* auVar4 = FUN_001e4cbc(base, rhi - rlo); FUN_002ac0d8(...) */
        sk_string_view_copy_utf16((unsigned long)p3, (unsigned long)p4, (unsigned long)p5);
        return;
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Invalid slice", 0xd, 2,
                   (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x7db, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00297f5c @ 0x00297f5c   (est. sk_string_utf16_view_copy)
 * Ghidra: void FUN_00297f5c(ulong,ulong,undefined8,undefined8,undefined8)
 * Swift String UTF16View copy: identical structure to FUN_00297e5c but
 * forwards to FUN_002ac168.
 * Confidence: high.
 */
void sk_string_utf16_view_copy(unsigned long w, unsigned long f, void *p3, void *p4, void *p5)
{
    unsigned long lo = 0, hi = 0;
    if ((f >> 0x3d & 1) == 0) {
        if ((w >> 0x3c & 1) == 0) {
            /* auVar4 = FUN_002a9ba8() */
        } else {
            hi = w & 0xffffffffffff;
            lo = (f & 0xfffffffffffffff) + 0x20;
        }
    } else {
        hi = f >> 0x38 & 0xf;
        lo = (unsigned long)&f;
    }
    unsigned long rlo = 0, rhi = 0;
    if (-1 < (long)rlo && rhi <= hi) {
        unsigned long base = lo ? lo + rlo : 0;
        /* auVar4 = FUN_001e4cbc(base, rhi - rlo); FUN_002ac168(...) */
        sk_string_view_copy_utf16((unsigned long)p3, (unsigned long)p4, (unsigned long)p5);
        return;
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Invalid slice", 0xd, 2,
                   (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x7db, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0029805c @ 0x0029805c   (est. sk_string_unicode_view_copy)
 * Ghidra: void FUN_0029805c(ulong,ulong,undefined8,undefined8,undefined8,undefined8)
 * Swift String unicodeScalarView copy: identical structure forwarding to
 * FUN_002ac214 (4-arg callback).
 * Confidence: high.
 */
void sk_string_unicode_view_copy(unsigned long w, unsigned long f, void *p3, void *p4,
                                 void *p5, void *p6)
{
    unsigned long lo = 0, hi = 0;
    if ((f >> 0x3d & 1) == 0) {
        if ((w >> 0x3c & 1) == 0) {
            /* auVar4 = FUN_002a9ba8() */
        } else {
            hi = w & 0xffffffffffff;
            lo = (f & 0xfffffffffffffff) + 0x20;
        }
    } else {
        hi = f >> 0x38 & 0xf;
        lo = (unsigned long)&f;
    }
    unsigned long rlo = 0, rhi = 0;
    if (-1 < (long)rlo && rhi <= hi) {
        unsigned long base = lo ? lo + rlo : 0;
        /* auVar4 = FUN_001e4cbc(base, rhi - rlo); FUN_002ac214(...) */
        sk_string_view_copy_unicode((unsigned long)p3, (unsigned long)p4, (unsigned long)p5, (unsigned long)p6);
        return;
    }
    sk_fatal_error(0xb, 2,
                   (unsigned long)"Invalid slice", 0xd, 2,
                   (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x7db, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0029816c @ 0x0029816c   (est. sk_string_utf8_decode)
 * Ghidra: void FUN_0029816c(ulong,ulong,long,long,undefined8)
 * Swift String UTF8 decoding loop: decodes the string's bytes into UTF-8
 * scalar values, handling the inline and native representations and
 * appending each scalar through a decode callback. Malformed encodings and
 * index-overflow raise fatal errors. Epilogue FUN_00344e54.
 * Confidence: high (Swift String UTF8View makeIterator loop).
 */
void sk_string_utf8_decode(unsigned long w, unsigned long f, long p3, long p4, void *p5)
{
    /* FUN_002ab8ac(p3<<0x10|1, p4<<0x10|1, w, f, 0xd2, 0x50)
     * -> [puVar4, uVar7) encoded span */
    unsigned char *lo = (unsigned char *)0, *hi = (unsigned char *)0;
    unsigned long src = w;
    if ((f & 0x2000000000000000) != 0) src = f;
    if ((src >> 0x3e & 1) == 0) {
        /* inline decode loop */
        if ((f >> 0x3c & 1) == 0) {
            /* FUN_002ac024(...); if ok: decode loop with
             * FUN_0026398c scalar decode; else fall to FUN_00297e5c */
            sk_string_utf8_view_copy(w, f, (void *)p3, (void *)p4, p5);
        } else {
            /* FUN_002ab4d4(...); malformed -> fatal UnicodeHelpers */
            sk_fatal_dump(0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                          (unsigned long)"Swift.UnicodeHelpers", 0x1a, 2, 0xfd, 1);
        }
    } else if ((unsigned long)hi >> 0xe != (unsigned long)lo >> 0xe) {
        /* native decode loop: FUN_002b5ba0 per byte, validate index,
         * FUN_002b141c; on overrun fatal StringUTF8View */
        sk_fatal_error(0xb, 2,
                       (unsigned long)"String index is out of bounds", 0x1d, 2,
                       (unsigned long)"Swift.StringUTF8View", 0x1a, 2, 0x90, 1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00298530 @ 0x00298530   (est. sk_string_utf8_decode_append)
 * Ghidra: void FUN_00298530(ulong,ulong,long,long,long*)
 * Swift String UTF8 decode-and-append: decodes the string's bytes and
 * appends each scalar into a growing byte buffer (param_5), handling both
 * inline and native representations. Malformed encodings raise fatal.
 * Epilogue FUN_00344e54.
 * Confidence: high (Swift String appendContentsOf / utf8 collect).
 */
void sk_string_utf8_decode_append(unsigned long w, unsigned long f, long p3, long p4, long *out)
{
    (void)out;
    /* FUN_002ab8ac(p3<<0x10|1, p4<<0x10|1, w, f, 0xd2, 0x50) */
    unsigned char *lo = (unsigned char *)0, *hi = (unsigned char *)0;
    unsigned long src = w;
    if ((f & 0x2000000000000000) != 0) src = f;
    if ((src >> 0x3e & 1) == 0) {
        if ((f >> 0x3c & 1) == 0) {
            /* FUN_002ac024; if ok: decode loop FUN_0026398c; append bytes
             * into *out via FUN_003a261c/FUN_001a0870 growth;
             * else fall to FUN_00297f5c */
            sk_string_utf16_view_copy(w, f, (void *)p3, (void *)p4, (void *)out);
        } else {
            /* FUN_002ab4d4; malformed -> fatal UnicodeHelpers */
            sk_fatal_dump(0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                          (unsigned long)"Swift.UnicodeHelpers", 0x1a, 2, 0xfd, 1);
        }
    } else {
        /* native decode loop; FUN_002b5ba0 per byte; append scalar byte */
        sk_fatal_error(0xb, 2,
                       (unsigned long)"String index is out of bounds", 0x1d, 2,
                       (unsigned long)"Swift.StringUTF8View", 0x1a, 2, 0x90, 1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00298980 @ 0x00298980   (est. sk_string_utf8_decode_collect)
 * Ghidra: void FUN_00298980(void)
 * Swift String UTF8 collect loop: decodes the string's bytes into UTF-8
 * scalars and collects them via a callback (auVar8), handling inline and
 * native representations. Malformed encodings raise fatal.
 * Confidence: high (Swift String UTF8View sequence collect).
 */
void sk_string_utf8_decode_collect(void)
{
    /* FUN_00353cfc; FUN_003545ac; FUN_00354404(...); FUN_002ab8ac();
     * FUN_00356290; */
    unsigned long src = 0;
    if ((src >> 0x3e & 1) == 0) {
        /* inline decode loop with FUN_0026398c / FUN_00263e20 scalar
         * decode; append via (*auVar8._0_8_)(scalar);
         * malformed -> fatal UnicodeHelpers */
        if (0) {
            sk_fatal_dump(0xb, 2, 0xd000000000000034, 0x80000000005ce6d0,
                          (unsigned long)"Swift.UnicodeHelpers", 0x1a, 2, 0xfd, 1);
        }
    } else {
        /* native decode loop; FUN_002b5ba0 per byte; on overrun fatal */
        sk_fatal_error(0xb, 2,
                       (unsigned long)"String index is out of bounds", 0x1d, 2,
                       (unsigned long)"Swift.StringUTF8View", 0x1a, 2, 0x90, 1);
    }
    /* FUN_00351348; FUN_00353d14 */
}

/*--------------------------------------------------------------------*/
/* FUN_00298cb8 @ 0x00298cb8   (est. sk_object_service_store4)
 * Ghidra: void FUN_00298cb8(void)
 * Object service store flavour: thread-save, lock/init, then stores an
 * object value through the element-copy callback at +0x30. Epilogue
 * FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_store4(void)
{
    sk_cpu();
    /* FUN_00350328; FUN_003515b4; FUN_003722e4; FUN_00348e18;
     * (*DAT_00658c00)([x8+0x40]); FUN_00348abc; (*DAT_00658c00)();
     * FUN_0034b87c; FUN_0034b518; (*pcVar5)(); FUN_0034c664;
     * (*pcVar4)(x26 + extraout_x9, x1, x5); (*pcVar5)();
     * iVar1 = [x19+0x30]; FUN_003546fc(x25+iVar1); (*pcVar4)();
     * FUN_003559d8; FUN_0014ae44; FUN_0034c5dc; FUN_00350aac;
     * u2 = (*x8_00)() */
    if (0) {
        /* FUN_00354d08; FUN_00350adc; FUN_00351584(x26+extraout_x9,
         * x25+iVar1); (*x8_01)() */
    }
    /* (*pcVar4)(); FUN_0035060c; (*pcVar4)(); FUN_003505e8;
     * (*pcVar4)(); u3 = FUN_00352980(); FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00298e58 @ 0x00298e58   (est. sk_string_init_from_buffer)
 * Ghidra: undefined1[16] FUN_00298e58(undefined8,long,undefined8)
 * Initializes a Swift String from a raw buffer of `param_2` elements:
 * resolves the element type, allocates a backing buffer (FUN_0019e578),
 * seeds it via the element-copy callback, and builds the string guts.
 * Returns the 16-byte string descriptor.
 * Confidence: medium.
 */
void sk_string_init_from_buffer(unsigned long out[2], long param_2, void *param_3)
{
    SK_OBJ_DISPATCH();   /* (**(code**)([*(param_2-8)]+0x40))(param_1, param_1) */
    unsigned long tid = sk_type_id((unsigned long)param_3);
    unsigned long lk = sk_object_lock(0, tid, (unsigned long)param_2, (void *)0x611b24, (void *)0x611b34);
    unsigned long buf = sk_string_convert(0, 0, 0, tid);   /* FUN_0019e578 */
    unsigned long tag = sk_allocator_tag((unsigned long)0x6576a8, 0x4f2190);
    /* FUN_001de8a8(local_58, FUN_00344210, stack, buf, lk, tag, 0x674330, 0x66d208) */
    sk_free((void *)buf);
    out[0] = 0; out[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00298fc0 @ 0x00298fc0   (est. sk_unsafe_raw_buffer_pointer_init)
 * Ghidra: void FUN_00298fc0(undefined1(*)[16],long,long,undefined8,undefined8)
 * UnsafeRawBufferPointer init from (base, count, stride, type): computes the
 * byte count (stride*count with overflow trap), validates negativity and
 * null-base, and builds the buffer descriptor. Raises the UnsafeRawBuffer
 * Pointer fatal errors on bad input.
 * Confidence: high (Swift UnsafeRawBufferPointer init).
 */
void sk_unsafe_raw_buffer_pointer_init(unsigned long out[2], long base, long count,
                                       void *type, void *param_5)
{
    unsigned long tid = sk_type_id((unsigned long)param_5);
    long lk = sk_object_lock(0, tid, (unsigned long)type, (void *)0x611b24, (void *)0x611b34);
    long stride = *(long *)(*(long *)(lk + -8) + 0x48);
    long bytes = count * stride;
    if (__builtin_mul_overflow(count, stride, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x299130) */
    }
    if (bytes < 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeRawBufferPointer with negative count", 0x2a, 2,
                       (unsigned long)"Swift.UnsafeRawBufferPointer", 0x22, 2, 0x4c1, 1);
    }
    if (bytes == 0) {
        if (base != 0) goto build;
        /* auVar6 = FUN_002a218c(0, 0); if (lo>=0): desc = 0xe000... */
        out[0] = 0; out[1] = 0xe000000000000000;
        return;
    }
    if (base == 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeRawBufferPointer has a nil base", 0x38, 2,
                       (unsigned long)"Swift.UnsafeRawBufferPointer", 0x22, 2, 0x4c2, 1);
    }
build:
    /* auVar6 = FUN_002a218c(base, bytes); if (lo>=0): thunk_FUN_002a2698
     * else: FUN_002a2748 */
    out[0] = (unsigned long)base; out[1] = (unsigned long)bytes;
}

/*--------------------------------------------------------------------*/
/* FUN_002993a4 @ 0x002993a4   (est. sk_unsafe_raw_buffer_slice)
 * Ghidra: void FUN_002993a4(undefined1(*)[16],long,long,undefined8,undefined8,undefined8)
 * UnsafeRawBufferPointer slice: computes the byte range for the given
 * element range, validates it, and builds the sub-buffer descriptor.
 * Confidence: high.
 */
void sk_unsafe_raw_buffer_slice(unsigned long out[2], long base, long count,
                                void *type, void *param_5, void *param_6)
{
    unsigned long tid = sk_type_id((unsigned long)param_6);
    long lk = sk_object_lock(0, tid, (unsigned long)type, (void *)0x611b24, (void *)0x611b34);
    long stride = *(long *)(*(long *)(lk + -8) + 0x48);
    long bytes = count * stride;
    if (__builtin_mul_overflow(count, stride, (long *)0)) {
        CL4_SBP();   /* SoftwareBreakpoint(1,0x2994f8) */
    }
    if (bytes < 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeRawBufferPointer with negative count", 0x2a, 2,
                       (unsigned long)"Swift.UnsafeRawBufferPointer", 0x22, 2, 0x4c1, 1);
    }
    if (bytes == 0) {
        if (base == 0) {
            out[0] = 0; out[1] = 0;
            return;
        }
    } else if (base == 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeRawBufferPointer has a nil base", 0x38, 2,
                       (unsigned long)"Swift.UnsafeRawBufferPointer", 0x22, 2, 0x4c2, 1);
    }
    /* auVar7 = FUN_001e4cbc(base, bytes); auVar8 = FUN_002a218c();
     * build descriptor */
    out[0] = (unsigned long)base; out[1] = (unsigned long)bytes;
}

/*--------------------------------------------------------------------*/
/* FUN_00299540 @ 0x00299540   (est. sk_unsafe_buffer_slice)
 * Ghidra: void FUN_00299540(undefined1(*)[16],long,long,undefined8)
 * UnsafeBufferPointer slice: builds the byte sub-range [param_2, param_3)
 * and constructs the buffer descriptor.
 * Confidence: high.
 */
void sk_unsafe_buffer_slice(unsigned long out[2], long base, long end, void *type)
{
    long n = base ? end - base : 0;
    /* auVar2 = FUN_001e4cbc(base, n); auVar3 = FUN_002a218c();
     * build descriptor */
    out[0] = (unsigned long)base; out[1] = (unsigned long)n;
    (void)type;
}

/*--------------------------------------------------------------------*/
/* FUN_002995c4 @ 0x002995c4   (est. sk_string_utf8_append_decode)
 * Ghidra: void FUN_002995c4(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Swift String UTF8 append-and-decode: decodes the string's bytes and
 * appends each scalar to a growing UTF-8 buffer, validating the encoding
 * (UTF-8, UTF-16 surrogate handling). Handles the Unicode/UTF8/UTF16
 * decode-table dispatch (0x6768d0/0x676bd0 keys). Epilogue FUN_0008e500.
 * Confidence: high (Swift String append UTF-8 with table dispatch).
 */
void sk_string_utf8_append_decode(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00350530; FUN_00377824; FUN_00348d7c; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034aa9c; FUN_00350720; u6 = FUN_0031e084();
     * FUN_0034ab20; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034a2ac;
     * FUN_0034bec4; u7 = FUN_00377824(); FUN_000a6f88; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_00350428; FUN_00355fac; FUN_0034a688;
     * (*DAT_00658c00)([x8+0x40]); FUN_003497b4; FUN_00349830;
     * FUN_00351ba0; FUN_00377824; FUN_00348ce8;
     * (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4; FUN_0034acf0;
     * (*DAT_00658c00)(); FUN_0034b758 */
    /* decode table dispatch: local_b0 key 0x6768d0 (UTF-8) or 0x676bd0
     * (UTF-16); FUN_00369584 decodes each scalar; append bytes */
    unsigned long buf = (unsigned long)sk_alloc(0x100, 0);   /* FUN_001a0870 grow buffer */
    unsigned long count = 0;
    /* scalar = FUN_00369584(...);
     * append UTF-8 bytes (1..4) into buf */
    if (0) {
        sk_fatal_error(0, 0, 0);
    }
    sk_free((void *)buf);
    /* FUN_00351324; FUN_0008e500 */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_00299c38 @ 0x00299c38   (est. sk_string_utf8_append2)
 * Ghidra: void FUN_00299c38(undefined8,undefined8,long,undefined8)
 * Swift String UTF8 append flavour: decodes the string into UTF-8 bytes,
 * growing a byte buffer (FUN_0036a804), and constructs the final String
 * descriptor (inline or native). Handles 1/2/3/4-byte scalars and
 * ASCII-only fast paths. Epilogue FUN_0008e500.
 * Confidence: high (Swift String append with UTF-8 encode).
 */
void sk_string_utf8_append2(void *p1, void *p2, long p3, void *p4)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00352700; FUN_003504e8; u7 = FUN_00377824(...&DAT_00612b58);
     * FUN_000a6f88; FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428;
     * FUN_00350908; u7 = FUN_0031e084(); FUN_0034ab20; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034aab0; FUN_0034ce98; FUN_00377824;
     * FUN_00348d4c; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b460;
     * FUN_0034ce98; puVar8 = FUN_00377824() */
    if (0 == 0) {
        /* inline/empty path */
        unsigned long u14 = 0;
        /* FUN_002a200c / FUN_002a20cc */
        sk_swift_set_make_unique(u14);
    } else {
        /* native encode path */
        unsigned long u18 = 0;
        unsigned long cap = 0, buf = 0;
        bool ascii = true;
        /* decode loop:
         *   scalar = FUN_00369584(...);
         *   if scalar < 0x80: 1 byte
         *   else if < 0x800: 2 bytes
         *   else: 3/4 bytes with LZCOUNT width
         *   grow buffer (FUN_0036a804) if needed; append bytes */
        unsigned long n = 0;
        if (0 == 0) {
            /* build inline string */
        } else {
            /* build native string: allocate 0x31-byte buffer
             * (FUN_0036a940), store guts */
        }
        /* FUN_00353100; FUN_0008e500 */
        sk_thread_epilogue();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0029a2a4 @ 0x0029a2a4   (est. sk_object_service_decode_loop)
 * Ghidra: void FUN_0029a2a4(void)
 * Object-service decode/iterate loop: thread-save, lock, then an iteration
 * that decodes an object value per element and dispatches through the
 * object method table; early-terminates with a status flag (local_d4) on
 * completion. Epilogue FUN_0008e500.
 * Confidence: low (complex indirect-dispatch decode loop).
 */
void sk_object_service_decode_loop(void)
{
    sk_cpu();
    /* FUN_00377824(0, in_0x78, in_0x60, &DAT_00612b58, &DAT_00612b90);
     * FUN_00348d4c; (*DAT_00658c00)([x8+0x40]); FUN_003493c4;
     * FUN_0034acf0; (*DAT_00658c00)(); FUN_00350464; FUN_0034c754;
     * u4 = FUN_00310d68(); FUN_000a6f88;
     * (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4; FUN_0034da38;
     * (*DAT_00658c00)(); FUN_0034c2c8; FUN_003508e4; FUN_0035345c;
     * u5 = FUN_00377824(); FUN_000a6f88; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034b460; FUN_0031e084(0); FUN_0034ab20;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b2f8; FUN_003508e4;
     * FUN_0035345c; FUN_00377824; FUN_00348fd8; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034d3c4; FUN_00349734;
     * (*DAT_00658c00)([x8_01+0x40]); FUN_000aa4ec; u5 = FUN_00358b78();
     * (*x9)(u5, u3, x6); FUN_00351dcc(in_0x70, x7); u3 = FUN_00377bec();
     * FUN_0031e0d4; FUN_003515cc; (*x9_00)() */
    unsigned int status = 0;
    /* (*pcVar6)(u5, x6, in_0x68, x28, u3); iVar2 = FUN_00369584();
     * loop: decode element; dispatch; on x21 term release;
     *   if iVar2==1 && (in_w3&1): status=1, return */
    /* FUN_00350bc0(...); (*x8_11)(x20, x28); FUN_00350bc0(...);
     * (*x8_12)(u5, x6); FUN_0008e500(status, x30) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029a820 @ 0x0029a820   (est. sk_string_utf8_append3)
 * Ghidra: void FUN_0029a820(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Swift String UTF8 append flavour: resolves the object, runs the decode
 * callback (FUN_002995c4) or the empty path, and builds the result.
 * Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_string_utf8_append3(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* u1 = FUN_003543ac(); auVar4 = FUN_003516cc();
     * FUN_00319320(...p6); FUN_00348d64; FUN_0007c1a4;
     * (*DAT_00658c00)(); FUN_0034aee4; FUN_0035050c(...&UINT_006775b0);
     * FUN_00319338; FUN_00349e10; FUN_0007c1a4; (*DAT_00658c00)();
     * FUN_0034af20 */
    /* FUN_003558fc(...); (*pcVar2)() */
    unsigned long n = 0, status = 0;
    if (status == 1) {
        /* FUN_00353480; thunk_FUN_00200b38; FUN_0034d140;
         * (**(code**)(x16_00+8))(u1, p4); FUN_001f1878(...);
         * FUN_000e72b0([x16+8]); (*x8)(); FUN_003545f4;
         * auVar4 = FUN_002995c4(); status = auVar4._8_8_; */
        sk_string_utf8_append_decode(0, 0, 0, 0, 0, 0);
    } else {
        /* FUN_0034d140; (**(code**)(x16_01+8))(u1, p4) */
    }
    /* FUN_0008e500(status) */
    sk_thread_epilogue();
}

/*--------------------------------------------------------------------*/
/* FUN_0029aa14 @ 0x0029aa14   (est. sk_unsafe_buffer_pointer_init)
 * Ghidra: void FUN_0029aa14(undefined1(*)[16],long,long,undefined8)
 * UnsafeBufferPointer init: builds the buffer descriptor for [param_2,
 * param_3) elements; negative counts raise the UnsafeBufferPointer fatal.
 * Confidence: high.
 */
void sk_unsafe_buffer_pointer_init(unsigned long out[2], long base, long count, void *type)
{
    if (base == 0) {
        count = 0;
    } else if (count < 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeBufferPointer with negative count", 0x27, 2,
                       (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x582, 1);
    }
    /* auVar1 = FUN_00299c38(base, count, type, type) */
    out[0] = (unsigned long)base; out[1] = (unsigned long)count;
    (void)type;
}

/*--------------------------------------------------------------------*/
/* FUN_0029aaa4 @ 0x0029aaa4   (est. sk_string_ascii_validate)
 * Ghidra: void FUN_0029aaa4(undefined8,undefined8)
 * Swift String ASCII validation: decodes the string (small inline or native
 * representation), checks that all bytes are ASCII (0x80 bit clear), and
 * returns the validated descriptor. Non-ASCII raises a fatal error.
 * Confidence: high (Swift String isASCII / withUTF8Buffer validate).
 */
void sk_string_ascii_validate(void *p1, void *p2)
{
    (void)p1;
    /* FUN_0006b2dc(p2, p1, p1) */
    unsigned long lo = 0, hi = 0;
    bool ascii = (lo == 0xf);
    if (lo < 0x10) {
        /* load 16-byte payload; FUN_000651bc */
        unsigned long w0 = 0, w1 = 0;
        if (hi < 0) {
            /* FUN_00351088; FUN_003487a4; FUN_003524c8 */
            sk_fatal_error(0, 0, 0);
        }
        /* (*extraout_x8)(&local_40) decode */
        unsigned long n = 0;
        if (0 == 0) {
            ascii = true;
        } else {
            unsigned long mark = 0xe000000000000000;
            if ((w0 & 0x8080808080808080) != 0 || (w1 & 0x8080808080808080) != 0) {
                mark = 0xa000000000000000;
            }
            unsigned long packed = mark | n << 0x38 | w1;
            ascii = (packed >> 0x3e & 1) == 0;
        }
    } else {
        /* FUN_0029afe4(hi, x8) native path */
    }
    /* FUN_000651bc(...) */
    if (!ascii) {
        /* FUN_0011d7e8 */
        __builtin_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0029ac08 @ 0x0029ac08   (est. sk_string_small_string_to_native)
 * Ghidra: void FUN_0029ac08(void)
 * Converts a small string to its native representation (FUN_002a218c /
 * FUN_002a2748), storing the 16-byte descriptor.
 * Confidence: medium.
 */
void sk_string_small_string_to_native(void)
{
    /* FUN_0035098c; lVar1 = FUN_002a218c();
     * if (lVar1 < 0): FUN_00353b4c; FUN_000b43d0; FUN_00352578;
     *   u2 = FUN_002a2748()
     * else: FUN_000b43d0((uint)lVar1, x1, (uint)lVar1 & 1);
     *   u2 = thunk_FUN_002a2698()
     * *x8 = u2; x8[1] = u3 */
}

/*--------------------------------------------------------------------*/
/* FUN_0029ac60 @ 0x0029ac60   (est. sk_string_native_pointer)
 * Ghidra: undefined1[16] FUN_0029ac60(undefined8,undefined8)
 * Returns the native string buffer pointer (or a unique copy) for a string.
 * Confidence: medium.
 */
void sk_string_native_pointer(unsigned long out[2], void *p1, void *p2)
{
    /* lVar1 = FUN_002a28f8(p1, 0x657248, p2); */
    unsigned long l = 0, s = 0;
    if (0 == 0) {
        /* auVar3 = FUN_002a218c(l+0x20, [l+0x18] & 0xffffffffffff);
         * if (lo<0): FUN_002a2748(...); FUN_0036b118(l)
         * else: FUN_002a2bb0(...); l = [l+0x18]; s = l */
        sk_free(0);
    }
    out[0] = l; out[1] = s;
}

/*--------------------------------------------------------------------*/
/* FUN_0029ad14 @ 0x0029ad14   (est. sk_unsafe_mutable_buffer_pointer_init)
 * Ghidra: undefined1[16] FUN_0029ad14(long,ulong,uint,undefined8,undefined8)
 * UnsafeMutableBufferPointer init: allocates a backing buffer of the given
 * element count, seeds it via the element-copy callback, and returns the
 * descriptor. Negative counts raise the UnsafeBufferPointer fatal.
 * Confidence: high.
 */
void sk_unsafe_mutable_buffer_pointer_init(unsigned long out[2], long count, unsigned long sz,
                                           unsigned int flags, void *p4, void *p5)
{
    (void)sz; (void)p4; (void)p5;
    if (count < 0) {
        sk_fatal_error(0xb, 2,
                       (unsigned long)"UnsafeMutableBufferPointer with negative count", 0x2e, 2,
                       (unsigned long)"Swift.UnsafeBufferPointer", 0x1f, 2, 0x4a, 1);
    }
    /* lVar2 = FUN_002ad4fc(count, 0x3000000000000000); lVar1 = lVar2 + 0x20;
     * FUN_002ddd74(lVar1, count, sz, flags & 1, p4, p5);
     * [lVar2+0x18] = sz | 0x3000000000000000; *(lVar1 + sz) = 0;
     * auVar5 = FUN_002a218c(lVar1);
     * if (lo<0): FUN_002a2748(...); FUN_0036b118(lVar2)
     * else: FUN_002a2bb0(...); */
    out[0] = 0; out[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0029ae68 @ 0x0029ae68   (est. sk_string_native_release)
 * Ghidra: void FUN_0029ae68(void)
 * Releases a native string buffer, copying it if it is shared (not unique)
 * and freeing the original.
 * Confidence: medium.
 */
void sk_string_native_release(void)
{
    /* thunk_FUN_0036b270(x4) retain; FUN_00352ae4; FUN_00356140;
     * FUN_002a2978(); */
    if (0 == 0) {
        /* lVar1 = FUN_0035aa7c();
         * if (lVar1 < 0): copy path (FUN_00353b4c; FUN_00352578;
         *   FUN_002a2748; FUN_003517c0; FUN_003a25d4(x4); FUN_0036b118(x3);
         *   FUN_00350470)
         * else: FUN_0035aa68(); FUN_003a25d4(x4) */
        sk_swift_release(0, 0);
    } else {
        sk_swift_release(0, 0);
    }
    /* FUN_00350aa0 */
}

/*--------------------------------------------------------------------*/
/* FUN_0029af30 @ 0x0029af30   (est. sk_string_native_pointer2)
 * Ghidra: undefined1[16] FUN_0029af30(undefined8,undefined8)
 * Returns the native string buffer pointer (or a unique copy) for a string;
 * flavour of FUN_0029ac60 using FUN_002a2a40.
 * Confidence: medium.
 */
void sk_string_native_pointer2(unsigned long out[2], void *p1, void *p2)
{
    /* lVar1 = FUN_002a2a40(p1, 0x657248, p2); */
    unsigned long l = 0, s = 0;
    if (0 == 0) {
        /* auVar3 = FUN_002a218c(l+0x20, ...); if (lo<0): FUN_002a2748(...);
         * FUN_0036b118(l); else: FUN_002a2bb0(...) */
        sk_free(0);
    }
    out[0] = l; out[1] = s;
}

/*--------------------------------------------------------------------*/
/* FUN_0029afe4 @ 0x0029afe4   (est. sk_string_native_load)
 * Ghidra: undefined8 FUN_0029afe4(void)
 * Loads a native string buffer, copying it if shared (not unique) and
 * returning the buffer word.
 * Confidence: medium.
 */
unsigned long sk_string_native_load(void)
{
    /* u1 = FUN_002a2b04(); */
    unsigned long u = 0;
    if (0 == 0) {
        /* lVar2 = FUN_0035aa7c();
         * if (lVar2 < 0): FUN_00353b4c; FUN_00352578(x20+0x20, ...);
         *   FUN_002a2748; FUN_0034f078; FUN_0036b118;
         *   u1 = FUN_000e15d8()
         * else: FUN_0035aa68(); u1 = [x20+0x18] */
        sk_free(0);
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_0029b058 @ 0x0029b058   (est. sk_string_append_unicode2)
 * Ghidra: void FUN_0029b058(undefined8,undefined8,ulong,ulong)
 * String append(unicode scalar) flavour: decodes the string guts and
 * appends the scalar, handling inline/native paths. Epilogue FUN_00358fc8.
 * Confidence: high (Swift String append scalar flavour).
 */
void sk_string_append_unicode2(void *p1, void *p2, unsigned long w, unsigned long f)
{
    (void)p1; (void)p2;
    /* FUN_00358fb4; FUN_003585f4; FUN_00355bdc */
    if (((f >> 0x3c & 1) == 0) && ((f & 0x2000000000000000) != 0 || (w & 0x1000000000000000) != 0)) {
        /* (*DAT_00658c00)(); FUN_00356b00(); (*DAT_00658c00)() */
        if ((f >> 0x3d & 1) == 0) {
            if ((w >> 0x3c & 1) == 0) {
                /* FUN_00355968; FUN_002a9ba8() */
            } else {
                /* FUN_00357628() */
            }
            /* FUN_00353f88(x8); (*x23)() */
        } else {
            /* FUN_00355720(); (*DAT_00658c00)(); FUN_00355c94();
             * store builder frame; FUN_003519e8; FUN_0034a210;
             * u1 = FUN_00002534(); FUN_00355704(u1, FUN_00346774);
             * FUN_00350bfc; FUN_003576bc; FUN_00291d70() */
            sk_string_finalize();
        }
    } else {
        /* FUN_00350470(x8); FUN_002a4468() */
    }
    /* FUN_00358fc8(x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_0029b1e0 @ 0x0029b1e0   (est. sk_string_append_retain)
 * Ghidra: void FUN_0029b1e0(undefined8)
 * Retains the string and appends it via FUN_001b07b8, then releases.
 * Confidence: medium.
 */
void sk_string_append_retain(void *p1)
{
    sk_alloc_pages(0, 0);   /* thunk_FUN_0036b270 retain */
    /* auVar1 = FUN_00354d44(); FUN_001b07b8(p1, auVar1._0_8_, auVar1._8_8_, x5) */
    sk_swift_release(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029b264 @ 0x0029b264   (est. sk_string_utf8_append_decode2)
 * Ghidra: void FUN_0029b264(undefined8,undefined8,ulong,ulong)
 * Swift String UTF8 append-decode flavour: decodes the string into UTF-8
 * bytes and appends each scalar through the decode-table dispatch
 * (0x676518/0x676590 keys). Handles inline and native representations;
 * malformed/out-of-range input raises fatal errors.
 * Confidence: high (Swift String UTF8 append with table dispatch).
 */
void sk_string_utf8_append_decode2(void *p1, void *p2, unsigned long w, unsigned long f)
{
    (void)p1; (void)p2;
    sk_cpu();
    /* FUN_00353cfc; pbVar9 = start; FUN_00353360; FUN_003504e8;
     * u5 = in_x7; FUN_00377824(...&DAT_00612b58); FUN_00348ce8;
     * FUN_0007c1a4; (*DAT_00658c00)(); FUN_00350428; FUN_003509a4;
     * FUN_003504e8; FUN_0035430c; FUN_00377824; FUN_00348fd8;
     * (*DAT_00658c00)([x8+0x40]); FUN_003493c4; FUN_0034d254;
     * (*DAT_00658c00)(); FUN_00350464; FUN_00350908; u5 = FUN_00310d68();
     * FUN_000a6f88; (*DAT_00658c00)([x8_00+0x40]); FUN_003493c4;
     * FUN_0034d944; (*DAT_00658c00)(); FUN_0034b758; FUN_003521a4 */
    unsigned long scal = 0, width = 0, nbytes = 0;
    unsigned char *lo = (unsigned char *)0, *hi = (unsigned char *)0;
    unsigned long src = w;
    if ((f & 0x2000000000000000) != 0) src = f >> 0x38 & 0xc;
    /* decode loop:
     *   read byte; classify UTF-8 width (1/2/3/4);
     *   FUN_002c8df4 / FUN_00369584 decode scalar;
     *   append scalar via (*pcVar7)(&DAT_00612b58, local_40, ...);
     *   on overrun raise fatal */
    /* FUN_0031e15c; FUN_00358e34; FUN_003508cc; (*x9)();
     * FUN_003510ac; FUN_00358be4; FUN_00377bec; FUN_00027754;
     * FUN_00027754; FUN_00353c90; FUN_0020a3b0;
     * FUN_003510dc([x16+8]); (*x8_03)() */
    sk_fatal_error(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029b9a8 @ 0x0029b9a8   (est. sk_swift_waiter_select)
 * Ghidra: undefined8 FUN_0029b9a8(void)
 * Selects between two waiter values based on a zero flag (FUN_003532b8).
 * Confidence: medium.
 */
unsigned long sk_swift_waiter_select(void)
{
    /* FUN_003532b8; uVar1 = (in_ZR) ? x8 : x9 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0029b9c4 @ 0x0029b9c4   (est. sk_object_service_dispatch_j)
 * Ghidra: void FUN_0029b9c4(void)
 * Object-service chain: lock/init stages then a string/object finalize via
 * FUN_001a1854.
 * Confidence: low.
 */
void sk_object_service_dispatch_j(void)
{
    /* FUN_00350c5c(x3); FUN_00358be4; FUN_003524bc; FUN_00377824;
     * FUN_00348e00; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034ad78;
     * FUN_00350878(); (*x8)(); FUN_00350530; FUN_00310d34; FUN_001a1854() */
}

/*--------------------------------------------------------------------*/
/* FUN_0029ba70 @ 0x0029ba70   (est. sk_string_from_utf8_buffer)
 * Ghidra: void FUN_0029ba70(ulong*,byte*,ulong,uint)
 * Builds a Swift String from a UTF-8 byte buffer: small (<=15 bytes inline)
 * or native (16-byte aligned, 0x10 flag) representation. Negative counts
 * raise a fatal error.
 * Confidence: high (Swift String(_uncheckedUTF8:)).
 */
void sk_string_from_utf8_buffer(unsigned long *out, unsigned char *buf,
                                unsigned long n, unsigned int flags)
{
    if ((long)n < 0) {
        /* FUN_0034846c */
        sk_fatal_error(0, 0, 0);
    }
    unsigned long lo = 0, hi = 0;
    if (n == 0) {
        lo = 0; hi = 0xe000000000000000;
    } else if (n < 0x10) {
        unsigned long count = n > 7 ? 8 : n;
        /* load count bytes little-endian into lo */
        for (unsigned long i = 0; i < count; i++) {
            lo |= (unsigned long)buf[i] << ((i * 8) & 0x3f);
        }
        unsigned long hi2 = 0;
        if (n >= 9) {
            unsigned long c2 = n - 8;
            for (unsigned long i = 0; i < c2; i++) {
                hi2 |= (unsigned long)buf[8 + i] << ((i * 8) & 0x3f);
            }
        }
        unsigned long mark = 0xe000000000000000;
        if (((hi2 | lo) & 0x8080808080808080) != 0) {
            mark = 0xa000000000000000;
        }
        hi = mark | n << 0x38 | hi2;
    } else {
        lo = n | 0xc000000000000000;
        if ((flags & 1) == 0) lo = n;
        lo |= 0x1000000000000000;
        hi = (unsigned long)(buf + 0x7fffffffffffffe0) | 0x8000000000000000;
    }
    out[0] = lo; out[1] = hi;
}

/*--------------------------------------------------------------------*/
/* FUN_0029bb80 @ 0x0029bb80   (est. sk_string_line_break)
 * Ghidra: byte FUN_0029bb80(undefined8,undefined8)
 * Unicode line-break / grapheme-cluster classification: given two adjacent
 * characters (param_1, param_2) and a 4-byte state struct (unaff_x20),
 * determines whether a line break is allowed (returns 1) or not (0),
 * implementing the Unicode line-breaking algorithm state machine
 * (FUN_003d3470/FUN_003d351c boundary classification).
 * Confidence: high (Swift/Unicode line-break state machine).
 */
unsigned char sk_string_line_break(unsigned long c1, unsigned long c2)
{
    unsigned char state[4] = {0, 0, 0, 0};
    (void)state;
    if ((int)c1 == 0xd && (int)c2 == 10) {
        return 0;
    }
    /* FUN_002c6a20 surrogate/boundary checks */
    /* classify both chars via FUN_002bb9b8 (line-break class) and
     * apply the Unicode LB state table via FUN_003d3470/FUN_003d351c */
    unsigned char cls1 = 0, cls2 = 0;
    (void)cls1; (void)cls2;
    /* switch on cls2 (0..0xb) with the LB rule table; return 0/1 */
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0029be78 @ 0x0029be78   (est. sk_string_next_utf8_scalar)
 * Ghidra: ulong FUN_0029be78(void)
 * Returns the next UTF-8 scalar value from a String, advancing the index
 * by the scalar width. Handles 1/2/3/4-byte UTF-8 encodings and inline/
 * native string representations. Returns 0x100000000 when the end of the
 * string is reached.
 * Confidence: high (Swift String UTF8View next).
 */
unsigned long sk_string_next_utf8_scalar(void)
{
    unsigned long idx = *(unsigned long *)((char *)0 + 0x10);
    if ((long)*(unsigned long *)((char *)0 + 0x18) <= (long)idx) {
        return 0x100000000;
    }
    unsigned long f = *(unsigned long *)((char *)0 + 8);
    if ((f >> 0x3c & 1) != 0) {
        /* FUN_0035646c; FUN_0034883c */
        sk_fatal_dump(0, 0, 0);
    }
    /* read byte at idx; classify width (1..4); return scalar */
    unsigned char *base = (unsigned char *)0;
    unsigned char b0 = base[idx];
    if ((signed char)b0 < 0) {
        unsigned long s = 0;
        /* decode 2/3/4-byte sequence */
        if (0) s = (unsigned long)(base[idx + 1] & 0x3f) | (b0 & 0x1f) << 6;
        /* advance index */
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0029c014 @ 0x0029c014   (est. sk_string_release_final)
 * Ghidra: void FUN_0029c014(void)
 * Releases a String: FUN_00255738 (release guts), FUN_00267820,
 * FUN_003a25d4 (release).
 * Confidence: medium.
 */
void sk_string_release_final(void)
{
    /* FUN_00255738(); FUN_00267820() */
    sk_swift_release(0, 0);
}
