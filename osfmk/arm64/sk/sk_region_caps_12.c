/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 *
 * Slice 12: 0x80000-0x100000 caps region — the Exclave Launcher configuration
 * subsystem: typed-value parsing/serialization (bool, u8/u16/u32/u64,
 * s8/s16/s32/s64, f32/f64), generic object sorting, and MMIO region setup.
 * All names are estimates unless string/header-matched.
 *
 * GENTER/GEXIT are rendered opaque; SoftwareBreakpoint(1,addr) trap sites are
 * rendered as CL4_TRAP(addr).  The cL4 "tagged" scalar encoding packs a type
 * tag in the top bits and (for short strings) the bytes inline; bit 0x3c/0x3d
 * of the tag word select the string representation (direct vs. heap pointer).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Shared base types (see sk_internal.h).
 * ------------------------------------------------------------------ */

typedef uint64_t word_t;
typedef uint64_t cptr_t;

/* A 16-byte value+kind pair returned by the launcher config parsers. */
typedef struct cl4_val {
    uint64_t lo;
    uint64_t hi;
} cl4_val_t;

/* Trap / software-breakpoint on an internal-consistency failure. */
#define CL4_TRAP(_addr)  do { __builtin_trap(); } while (0)

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helpers (declared extern; bodies owned by the range
 * workers that cover them).  Keep exact Ghidra FUN_ names in comments.
 * ------------------------------------------------------------------ */

/* FUN_0036b270 @ 0x36b270 — retain/acquire a reference on an object. */
extern uint64_t cL4_ref_acquire(uint64_t obj);
/* FUN_0036b118 @ 0x36b118 — release a reference on an object. */
extern void cL4_ref_release(int64_t obj);
/* FUN_0036a940 @ 0x36a940 — allocate a typed object; returns its address. */
extern uint64_t cL4_obj_alloc_typed(uint64_t tag, uint64_t a, uint64_t b);
/* FUN_003a25d4 @ 0x3a25d4 — release wrapper: cL4_ref_release(obj & mask). */
extern void cL4_release_mask(uint64_t obj);
/* FUN_003a261c @ 0x3a261c — return whether an object's refcount is exactly 1. */
extern bool cL4_refcount_is_one(int64_t obj);
/* FUN_0036b6f4 @ 0x36b6f4 — error unwind / teardown path. */
extern void cL4_err_unwind(int64_t a, int64_t b, uint64_t c, uint64_t d);
/* FUN_0036b6ac @ 0x36b6ac — second unwind/teardown path (no args). */
extern void cL4_err_unwind2(void);
/* FUN_0036993c @ 0x36993c — build a 16-byte debug/log value from two addrs. */
extern cl4_val_t cL4_debug_value(uint64_t a, uint64_t b, int64_t c, uint64_t d);

/* Object-sort / vector helpers. */
/* FUN_000f9680 @ 0xf9680 — grow/reallocate a sorted-run vector. */
extern uint64_t cL4_vec_grow(uint64_t exact, uint64_t need, uint64_t step, uint64_t vec);
/* FUN_000f9930 @ 0xf9930 — copy/reallocate a vector. */
extern uint64_t cL4_vec_copy(uint64_t vec);
/* thunk_FUN_000f9608 @ 0xf9608 — allocate a vector with `n` entries. */
extern uint64_t cL4_vec_alloc(uint64_t n);
/* FUN_000f98ac @ 0xf98ac — shrink/trim a vector to `n` entries. */
extern void cL4_vec_trim(uint64_t n);
/* FUN_00069970 @ 0x69970 — memmove a span within a vector. */
extern void cL4_vec_move(void *dst, uint64_t n, void *src);
/* FUN_00117d14 @ 0x117d14 — copy `len` bytes src->dst. */
extern void cL4_mem_copy(void *dst, void *src, uint64_t len);
/* FUN_00117cc4 @ 0x117cc4 — copy `len` bytes into a stack buffer. */
extern void cL4_stack_copy(void *dst, void *src, uint64_t len);
/* FUN_00081974 @ 0x81974 — copy a bounded region. */
extern void cL4_region_copy(void *dst, uint64_t n, void *src);

/* Object/id helpers. */
/* FUN_0006cf50 @ 0x6cf50 — return the current object id / slot index. */
extern uint64_t cL4_obj_id(void);
/* FUN_0006d0b8 @ 0x6d0b8 — resolve an id/selector to an object pointer. */
extern uint64_t cL4_obj_resolve(uint64_t id);
/* FUN_0006d150 @ 0x6d150 — acquire a slot / allocate an object handle. */
extern int64_t cL4_slot_acquire(void);
/* FUN_0006d1e4 @ 0x6d1e4 — release a slot / object handle. */
extern void cL4_slot_release(void);
/* FUN_0006d024 @ 0x6d024 — size/limit of a region with the given id. */
extern uint64_t cL4_region_limit(uint64_t id);

/* String / numeric parsing helpers (out of slice). */
/* FUN_000b0888 @ 0xb0888 — skip/parse a sign character from a string. */
extern cl4_val_t cL4_str_parse_sign(int64_t flag, uint8_t *s);
/* FUN_0008df28 @ 0x8df28 — begin a hex-accumulation pass. */
extern cl4_val_t cL4_hex_begin(void);
/* FUN_0008dfac @ 0x8dfac — fetch next hex digit (returns status in hi). */
extern cl4_val_t cL4_hex_next(uint64_t lo, uint64_t hi);
/* FUN_0008e0f4 @ 0x8e0f4 — classify a hex digit as [A-F]. */
extern cl4_val_t cL4_hex_upper(uint64_t lo, uint64_t hi);
/* FUN_0008e0e8 @ 0x8e0e8 — classify a hex digit as [a-f]. */
extern cl4_val_t cL4_hex_lower(uint64_t lo, uint64_t hi);
/* FUN_0008e1c8 @ 0x8e1c8 — accumulate a hex nibble into the value. */
extern cl4_val_t cL4_hex_acc(uint64_t acc);
/* FUN_0008e260 @ 0x8e260 — report a parse error / invalid digit. */
extern void cL4_hex_error(void);
/* FUN_00097188 @ 0x97188 — fetch one byte of a tagged string. */
extern uint64_t cL4_tag_str_byte(uint64_t idx);
/* FUN_000bd3f0 @ 0xbd3f0 (in-slice, see below) — accumulate a nibble. */
extern int64_t cL4_nibble_acc(int64_t acc);

/* Typed-value getters for the launcher config (out of slice). */
/* FUN_001b5d4c @ 0x1b5d4c — parse a bool ("true"/"false") value. */
extern uint64_t cL4_val_get_bool(uint64_t lo, uint64_t hi);
/* FUN_000b05bc @ 0xb05bc / FUN_000b05d4 — get an s16/u16 value. */
extern void cL4_val_get_s16(void);
/* FUN_000b04e4 @ 0xb04e4 — get an s8 value. */
extern void cL4_val_get_s8(uint64_t a, uint64_t b, uint64_t c);
/* FUN_000b04cc @ 0xb04cc — get an s16 value variant. */
extern void cL4_val_get_s16b(void);
/* FUN_000b03cc @ 0xb03cc / FUN_000b03fc — get an s32 value. */
extern void cL4_val_get_s32(void);
/* FUN_000b03e4 @ 0xb03e4 — get an s32 value variant. */
extern void cL4_val_get_s32b(void);
/* FUN_000b06a4 @ 0xb06a4 — get a bool value variant. */
extern void cL4_val_get_bool2(uint64_t a, uint64_t b, uint64_t c);
/* FUN_000b077c @ 0xb077c / FUN_000b02f4 — get an s64 value. */
extern void cL4_val_get_s64(void);
/* FUN_000b02dc @ 0xb02dc — get an s64 value variant. */
extern void cL4_val_get_s64b(void);

/* Logging / exception primitives (out of slice). */
/* FUN_002acbb8 @ 0x2acbb8 — emit a (tagged) string/error to the log. */
extern void cL4_log_tagged(uint64_t lo, uint64_t hi);
/* FUN_002a4ab4 @ 0x2a4ab4 — log an operation/assert with a code. */
extern void cL4_log_code(uint64_t code);
/* FUN_002a0cf8 @ 0x2a0cf8 — compare two tagged values for equality. */
extern uint64_t cL4_tag_eq(uint64_t a, uint64_t b, uint64_t c, uint64_t d, char e);
/* FUN_003d3130 @ 0x3d3130 — parse a bool from a tagged string (variant A). */
extern int64_t cL4_parse_bool_a(uint64_t *s, uint32_t *err);
/* FUN_003d30c4 @ 0x3d30c4 — parse a bool from a tagged string (variant B). */
extern int64_t cL4_parse_bool_b(uint64_t *s, uint64_t *err);
/* FUN_000276c4 @ 0x276c4 — fetch the 16-byte {value,kind} of a typed object. */
extern uint64_t cL4_typed_val(uint64_t obj);
/* FUN_00023c78 @ 0x23c78 — fetch a typed object's value as uint64. */
extern uint64_t cL4_typed_raw(uint64_t obj);
/* FUN_00027724 @ 0x27724 — resolve a log format string by address. */
extern uint64_t cL4_log_fmt(uint64_t addr);
/* FUN_0003a6a? — none. */
/* FUN_002a9ba8 @ 0x2a9ba8 — resolve a tagged string's {len,ptr} span. */
extern cl4_val_t FUN_002a9ba8(uint64_t v);
/* FUN_0029d3d8 @ 0x29d3d8 — resolve a tagged value's {tag,kind} pair. */
extern cl4_val_t FUN_0029d3d8(uint64_t a, uint64_t b);
/* FUN_002a4468 @ 0x2a4468 — parse a tagged string via a parser callback. */
extern void FUN_002a4468(uint64_t *out, uint64_t cb, uint64_t a, uint64_t b,
                         uint64_t c, uint64_t fmt);

/* Forward declarations for in-slice functions used before their definition. */
void FUN_000b9518(int64_t *param_1, uint64_t param_2, int64_t *param_3, int64_t param_4);
int64_t FUN_000b9c14(int64_t *vec, uint64_t arr, int64_t *array);
cl4_val_t FUN_000bb378(uint64_t val, uint8_t kind);
void FUN_000ba34c(uint8_t v);
void FUN_000bdc00(void);
void FUN_000bd7b8(uint64_t p1, uint64_t p2, uint64_t base, uint64_t size);
void FUN_000bdb6c(uint64_t *out, uint64_t p2);
void FUN_000be154(uint64_t id);
void FUN_000be250(uint64_t *out, uint64_t mode);
/* FUN_0006e7c0 @ 0x6e7c0 — read a device/MMIO description into a buffer. */
extern void FUN_0006e7c0(uint64_t id, uint8_t *buf);
/* FUN_000ff728 @ 0xff728 — build/attach a region from a device description. */
extern uint64_t FUN_000ff728(uint64_t tag, uint8_t *buf);
/* FUN_000026e8 @ 0x26e8 — log/diagnose a device region operation. */
extern void FUN_000026e8(uint64_t id);
/* FUN_000fdb98 @ 0xfdb98 — build a region in "private" mode. */
extern void FUN_000fdb98(cl4_val_t *vals);
/* FUN_000ffba8 @ 0xffba8 — build a region in "shared" mode. */
extern void FUN_000ffba8(void);
void FUN_000bd2b8(uint64_t out);
void FUN_000bd2e8(uint64_t out);
void FUN_000bd248(uint64_t out, uint8_t *tag, uint64_t p3, int64_t (*cb)(void));
/* FUN_003d3130 @ 0x3d3130 — parse a bool from a tagged string (variant A). */
extern int64_t FUN_003d3130(uint64_t *s, uint32_t *err);
/* FUN_003d30c4 @ 0x3d30c4 — parse a bool from a tagged string (variant B). */
extern int64_t FUN_003d30c4(uint64_t *s, uint64_t *err);

/* MMIO / region setup helpers (out of slice). */
/* FUN_000fdd78 @ 0xfdd78 — initialize a stack scratch buffer. */
extern void cL4_scratch_init(uint8_t *buf);
/* FUN_000a9ae8 @ 0xa9ae8 — classify the scratch buffer contents (1 = error). */
extern int cL4_scratch_classify(uint8_t *buf);
/* FUN_000aa3ac @ 0xaa3ac — emit a fatal error frame. */
extern void cL4_fatal_frame(void);
/* FUN_001ebfb0 @ 0x1ebfb0 — format a value into a string buffer. */
extern void cL4_fmt_value(uint64_t *out, uint64_t n, uint64_t tag, uint64_t buf, uint64_t val);
/* FUN_0001e790 @ 0x1e790 — return a format context pointer. */
extern uint64_t cL4_fmt_ctx(void);
/* FUN_00034f70 @ 0x34f70 — find/create an MMIO untyped capability. */
extern int64_t cL4_mmio_untyped(void);
/* FUN_00085374 @ 0x85374 — log an init/create failure. */
extern void cL4_log_init_fail(const char *s, uint64_t a, uint64_t b, uint64_t c);
/* FUN_000fb7d0 @ 0xfb7d0 — log an MMIO region setup line. */
extern void cL4_log_mmio_setup(uint64_t a, uint64_t b, const char *tag, uint64_t d,
                               uint64_t e, const char *fmt, uint64_t g, uint64_t h,
                               uint64_t i, int64_t j, int64_t k, uint64_t l, uint64_t m);
/* FUN_001000b8 @ 0x1000b8 — allocate a kernel object of a given kind. */
extern uint64_t cL4_obj_kernel_alloc(uint64_t kind);
/* FUN_000fefe8 @ 0xfefe8 — reference / wrap an object for a slot. */
extern uint64_t cL4_obj_ref_for_slot(int64_t obj);
/* FUN_004b23d8 @ 0x4b23d8 — release an MMIO untyped. */
extern void cL4_mmio_untyped_release(int64_t obj);
/* FUN_001e9c00 @ 0x1e9c00 — log a register dump. */
extern void cL4_log_regdump(cl4_val_t *vals);
/* FUN_0011d7e8 @ 0x11d7e8 — terminate / assert with a 16-byte message. */
extern void cL4_terminate(uint64_t lo, uint64_t hi);
/* FUN_0006e7c0 @ 0x6e7c0 — read a device/MMIO description into a buffer. */
extern void cL4_dev_read(uint64_t id, uint8_t *buf);
/* FUN_001003e8 @ 0x1003e8 — allocate an object; returns its address. */
extern uint64_t cL4_obj_alloc_typed2(uint64_t kind);
/* FUN_000ff728 @ 0xff728 — build/attach a region from a device description. */
extern uint64_t cL4_region_from_dev(uint64_t tag, uint8_t *buf);
/* FUN_000026e8 @ 0x26e8 — log/diagnose a device region operation. */
extern void cL4_dev_op_log(uint64_t id);
/* FUN_000ffba8 @ 0xffba8 — build a region in "shared" mode. */
extern void cL4_region_build_shared(void);
/* FUN_000fdb98 @ 0xfdb98 — build a region in "private" mode. */
extern void cL4_region_build_private(cl4_val_t *vals);
/* FUN_0009d1c0 @ 0x9d1c0 — launch/execute a nested exclave with args. */
extern void cL4_exclave_launch(uint64_t tcb, uint64_t a, uint64_t b);
/* FUN_0009d1c0 @ 0x9d1c0 — launch/execute a nested exclave with args. */
extern void FUN_0009d1c0(uint64_t tcb, uint64_t a, uint64_t b);
/* FUN_00151974 @ 0x151974 — capture the current 16-byte exit value. */
extern cl4_val_t cL4_exit_capture(void);
/* FUN_00151a6c @ 0x151a6c — log a code/fault line with format string. */
extern void cL4_log_fault_line(void *fn, uint64_t z, const char *tag, uint64_t d,
                               uint64_t e, uint64_t f, uint64_t lo, uint64_t hi);
/* FUN_000fdb98/ffba8 above; FUN_000bde88 etc are in-slice no-ops. */

/* ------------------------------------------------------------------ *
 * In-slice shared no-op hooks (used as tiny state-machine steps).
 * ------------------------------------------------------------------ */

/* 0xba34c — no-op hook (called by the bool getter 0xb91bc). */
static void cL4_hook_noop_a(void) { }

/* 0xba31c / 0xba334 / 0xba370 — no-op hooks (vtable slots). */
static void cL4_hook_noop(void) { }

/* 0xbd318 / 0xbd32c / 0xbd33c / 0xbd34c — no-op parse hooks. */
static void cL4_parse_noop(void) { }

/* 0xbd3a4 / 0xbd3b0 / 0xbd3bc / 0xbd3cc / 0xbd404 / 0xbd418 — no-op
 * per-type read hooks consulted by the tagged-value dispatcher. */
static void cL4_type_noop(void) { }

/* 0xbde88 / 0xbdeb0 — no-op error/log hooks. */
static void cL4_log_noop(void) { }

/* ------------------------------------------------------------------ *
 * Sort framework (generic stable merge sort over object arrays,
 * comparing elements through their vtable comparator at +0x88).
 * ------------------------------------------------------------------ */

/* FUN_000ba1b4 @ 0xba1b4   (est. cL4_sort_span_bounds)
 * Ghidra: undefined1[16] FUN_000ba1b4(undefined8, long, long, long)
 * Given a base `base` (param_3), a count `count` (param_4) and a per-element
 * stride/limit `limit` (param_2), copy the first min(limit,count) elements
 * of `base` into a scratch area (via cL4_region_copy) and return {out_start,
 * out_end} = {base+min(limit,count), base+count}.
 * Confidence: medium
 * Notes: overflows guarded; returns the copy's head/tail span. */
cl4_val_t FUN_000ba1b4(uint64_t param_1, int64_t limit, uint64_t base, int64_t count)
{
    int64_t copied;
    int64_t end;

    if (count == 0 || limit == 0) {
        end = 0;
        if (base != 0) {
            end = count + base;                 /* base + count */
        }
    } else {
        int64_t n = count;
        if (limit <= count) {
            n = limit;
        }
        cL4_region_copy((void *)base, (uint64_t)n, (void *)param_1);
        end = base + count;
        base = base + (uint64_t)n;
    }
    cl4_val_t r;
    r.hi = (uint64_t)end;
    r.lo = base;
    return r;
}

/* FUN_000b9f14 @ 0xb9f14   (est. cL4_sort_merge)
 * Ghidra: undefined8 FUN_000b9f14(undefined8*, undefined8*, undefined8*, undefined8*)
 * Merge two already-sorted subarrays [param_1,param_2) and [param_2,param_3)
 * using a scratch buffer param_4, comparing elements by their vtable
 * comparator (method at +0x88).  The smaller half is copied to scratch and
 * merged back in order; returns 1.
 * Confidence: medium
 * Notes: SoftwareBreakpoint guards on index/pointer arithmetic; comparator
 *   invocation wrapped in retain/release (FUN_0036b270 / FUN_0036b118). */
int64_t FUN_000b9f14(uint64_t *lo, uint64_t *mid, uint64_t *hi, uint64_t *scratch)
{
    int64_t nlo = ((int64_t)mid - (int64_t)lo) / 8;
    int64_t nhi = ((int64_t)hi - (int64_t)mid) / 8;

    if (nlo < nhi) {
        cL4_region_copy((void *)lo, (uint64_t)nlo, (void *)scratch);
        uint64_t *sp = scratch + nlo;
        uint64_t *out = lo;
        while (scratch < sp && mid < hi) {
            uint64_t *el_b = (uint64_t *)*mid;    /* element via left half */
            uint64_t *el_s = (uint64_t *)*scratch;
            /* vtable comparator at +0x88 */
            int64_t (*cmp_b)(void) = *(int64_t (**)(void))(*el_b + 0x88);
            int64_t (*cmp_s)(void) = *(int64_t (**)(void))(*el_s + 0x88);
            cL4_ref_acquire((uint64_t)el_b);
            cL4_ref_acquire((uint64_t)el_s);
            uint64_t vb = (uint64_t)cmp_b();
            uint64_t vs = (uint64_t)cmp_s();
            cL4_ref_release((int64_t)el_b);
            cL4_ref_release((int64_t)el_s);
            uint64_t *src;
            if (vb < vs) {
                src = mid++;
            } else {
                src = scratch++;
            }
            if (out != src) {
                *out = *src;
            }
            out++;
        }
        /* copy any remaining scratch tail back into out */
        int64_t remaining = ((int64_t)sp - (int64_t)scratch) / 8;
        if (remaining < -7) {
            CL4_TRAP(0xba1b4);
        }
        int64_t n = ((int64_t)sp - (int64_t)scratch) / 8;
        if (out != scratch || scratch + n <= out) {
            cL4_mem_copy(out, scratch, (uint64_t)n << 3);
        }
        return 1;
    }

    /* Right half is smaller (or equal): copy it to scratch, merge back
     * from the right, taking larger elements first for stability. */
    cL4_region_copy((void *)mid, (uint64_t)nhi, (void *)scratch);
    uint64_t *sp = scratch + nhi;
    uint64_t *wr = hi;
    for (;;) {
        uint64_t *rp = mid - 1;
        uint64_t *src = hi;
        for (;;) {
            hi = (uint64_t *)((uint64_t)hi - 1);
            uint64_t *out = mid;
            if (mid <= lo || sp <= scratch) {
                goto copy_tail;
            }
            uint64_t *sel = sp - 1;
            uint64_t *el_s = (uint64_t *)*sel;
            uint64_t *el_r = (uint64_t *)*rp;
            int64_t (*cmp_s)(void) = *(int64_t (**)(void))(*el_s + 0x88);
            int64_t (*cmp_r)(void) = *(int64_t (**)(void))(*el_r + 0x88);
            cL4_ref_acquire((uint64_t)el_s);
            cL4_ref_acquire((uint64_t)el_r);
            uint64_t vs = (uint64_t)cmp_s();
            uint64_t vr = (uint64_t)cmp_r();
            cL4_ref_release((int64_t)el_s);
            cL4_ref_release((int64_t)el_r);
            if (vs < vr) {
                break;                          /* right element wins */
            }
            bool advance = sp != src;
            sp = sel;
            hi = (uint64_t *)((uint64_t)hi - 1);
            if (advance) {
                *hi = *sel;
            }
        }
        bool advance = (uint64_t)hi != (uint64_t)mid;
        mid = rp;
        if (advance) {
            *hi = *rp;
        }
    }
copy_tail: ;
    /* copy the remaining scratch tail back into lo.. */
    int64_t remaining = ((int64_t)sp - (int64_t)scratch) / 8;
    if (remaining < -7) {
        CL4_TRAP(0xba1b4);
    }
    int64_t n = ((int64_t)sp - (int64_t)scratch) / 8;
    if (lo != scratch || scratch + n <= lo) {
        cL4_mem_copy(lo, scratch, (uint64_t)n << 3);
    }
    return 1;
}

/* FUN_000b9ac4 @ 0xb9ac4   (est. cL4_sort_insertion)
 * Ghidra: void FUN_000b9ac4(long, long, long, long*)
 * Insertion sort over the slice [param_1,param_2) of the array described by
 * param_4 ({base,count}), starting at index param_3.  Each swap compares via
 * the vtable comparator at +0x88 and walks the current element left while it
 * is smaller than its predecessor (insertion sort).
 * Confidence: medium
 * Notes: SoftwareBreakpoint guards; comparator wrapped in retain/release. */
void FUN_000b9ac4(int64_t lo_idx, int64_t hi_idx, int64_t cur, int64_t *arr)
{
    if (cur == hi_idx) {
        return;
    }
    uint64_t base = (uint64_t)arr[0];
    uint64_t count = (uint64_t)arr[1];
    uint64_t *slot = (uint64_t *)(base + cur * 8);
    uint64_t *start = slot;
    int64_t i = cur;
    do {
        int64_t prev = i - 1;
        if (prev < 0) {            /* SBORROW8(i,1) -> underflow trap 0xb9c08 */
            CL4_TRAP(0xb9c08);
        }
        if (prev < 0 || count <= (uint64_t)i) {
            CL4_TRAP(0xb9c0c);
        }
        if (prev < 0 || count <= (uint64_t)prev) {
            CL4_TRAP(0xb9c10);
        }
        uint64_t *el = (uint64_t *)*slot;
        uint64_t *el_prev = *(uint64_t **)(base + prev * 8);
        int64_t (*cmp)(void) = *(int64_t (**)(void))(*el + 0x88);
        int64_t (*cmp_p)(void) = *(int64_t (**)(void))(*el_prev + 0x88);
        cL4_ref_acquire((uint64_t)el);
        cL4_ref_acquire((uint64_t)el_prev);
        uint64_t v = (uint64_t)cmp();
        uint64_t vp = (uint64_t)cmp_p();
        cL4_ref_release((int64_t)el);
        cL4_ref_release((int64_t)el_prev);
        if (v < vp) {
            if (base == 0) {
                CL4_TRAP(0xb9c14);
            }
            uint64_t tmp = *slot;
            *slot = *(uint64_t *)(base + prev * 8);
            *(uint64_t *)(base + prev * 8) = tmp;
            i = prev;
            slot -= 1;
            if (prev != lo_idx) {
                continue;
            }
        }
        i = (int64_t)start + 1;
        slot = start + 1;
        start = slot;
    } while (i != hi_idx);
}

/* FUN_000b9e6c @ 0xb9e6c   (est. cL4_sort_run)
 * Ghidra: undefined* FUN_000b9e6c(long, undefined8, undefined8)
 * Allocate a run-tracking vector sized `param_1` (or the static empty vector
 * at DAT_00657778 if param_1==0), seed it with one empty run [0,param_1), and
 * drive the recursive merge sort (FUN_000b9518) over the array `param_2` with
 * comparison limit `param_3`.  Resets the run count to 0 before returning.
 * Confidence: medium
 * Notes: DAT_00657778 is the static empty vector; on unwind the vector is
 *   released via cL4_ref_release. */
void *FUN_000b9e6c(int64_t hint, uint64_t arr, uint64_t limit)
{
    uint64_t vec;
    if (hint >= 0) {
        if (hint == 0) {
            vec = 0x657778;                     /* DAT_00657778 static empty vector */
        } else {
            vec = cL4_vec_alloc((uint64_t)hint);
            *(int64_t *)(vec + 0x10) = hint;    /* vector length */
        }
        /* run list lives at vec+0x20; seed [0,hint) */
        int64_t *runs = (int64_t *)(vec + 0x20);
        runs[0] = 0;
        runs[1] = hint;
        FUN_000b9518(runs, (uint64_t)runs, (int64_t *)(uintptr_t)arr, limit);
        *(uint64_t *)(vec + 0x10) = 0;
        if (0) {                                /* unaff_x21 unwind flag */
            cL4_ref_release((int64_t)vec);
        }
        return (void *)vec;
    }
    CL4_TRAP(0xb9f14);
}

/* FUN_000b9518 @ 0xb9518   (est. cL4_sort_merge_runs)
 * Ghidra: void FUN_000b9518(long*, undefined8, long*, long)
 * Bottom-up stable merge sort of the object array described by param_3
 * ({base,count}), using the run list at param_1.  Elements are compared by
 * their vtable comparator at +0x88; runs are merged with FUN_000b9f14 and
 * the run list is compacted via FUN_000b9c14.  `param_4` is a comparison
 * threshold passed to the merge step.
 * Confidence: low
 * Notes: DAT_00657778 static empty vector; extensive SoftwareBreakpoint
 *   index guards; FUN_003a261c checks single-ref before vector growth.
 *   The inner merge-partition loop is restructured (not 1:1 with the
 *   decompile's do/while + partition phase) and the many index-guard traps
 *   are collapsed; unaff_x21 unwind flag rendered as `if (0 != 0)`. */
void FUN_000b9518(int64_t *runlist, uint64_t scratch, int64_t *array, int64_t limit)
{
    /* `runlist` points at a dynamic vector of {start,end} run pairs.  The
     * decompile seeds it from the static empty vector DAT_00657778.  We
     * reconstruct the merge-sort driver faithfully. */
    uint64_t *vec = (uint64_t *)runlist;        /* vector header at runlist */
    uint64_t *runs = vec + 0x20 / 8;            /* run pairs at +0x20 */
    uint64_t base = (uint64_t)array[0];
    uint64_t count = (uint64_t)array[1];

    uint64_t i = 0;
    while ((int64_t)i < (int64_t)count) {
        /* detect an already-sorted run [i, j) by comparing adjacent
         * elements via the vtable comparator at +0x88 */
        uint64_t j = i + 1;
        uint64_t run_start = i;
        while ((int64_t)j < (int64_t)count) {
            uint64_t *el_a = *(uint64_t **)(base + j * 8);
            uint64_t *el_b = *(uint64_t **)(base + run_start * 8);
            int64_t (*cmp_a)(void) = *(int64_t (**)(void))(*el_a + 0x88);
            int64_t (*cmp_b)(void) = *(int64_t (**)(void))(*el_b + 0x88);
            cL4_ref_acquire((uint64_t)el_a);
            cL4_ref_acquire((uint64_t)el_b);
            uint64_t va = (uint64_t)cmp_a();
            uint64_t vb = (uint64_t)cmp_b();
            cL4_ref_release((int64_t)el_a);
            cL4_ref_release((int64_t)el_b);
            if (va < vb) break;
            run_start = j;
            j += 1;
        }
        /* record the run [i, run_start+1) in the run list */
        uint64_t rn = *(uint64_t *)((uint64_t)vec + 0x10);   /* run count */
        if ((*(uint64_t *)((uint64_t)vec + 0x18) >> 1) <= rn) {
            vec = (uint64_t *)cL4_vec_grow(1 < *(uint64_t *)((uint64_t)vec + 0x18),
                                           rn + 1, 1, (uint64_t)vec);
        }
        *(uint64_t *)((uint64_t)vec + 0x10) = rn + 1;
        *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x20) = i;
        *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x28) = run_start + 1;
        /* merge the last two runs if they are adjacent & comparable */
        FUN_000b9c14((int64_t *)vec, array[0], array);
        i = run_start + 1;
        if (0 != 0) break;                      /* unwind flag */
    }

    /* Final pass: merge runs pairwise until a single sorted run remains. */
    uint64_t nb = array[0];
    if (nb == 0) CL4_TRAP(0xb9ac4);
    uint64_t rn = *(uint64_t *)((uint64_t)vec + 0x10);
    while (rn >= 2) {
        uint64_t lo0 = *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x20);
        uint64_t lo1 = *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x28);
        uint64_t lo2 = *(uint64_t *)((uint64_t)vec + (rn - 1) * 0x10 + 0x28);
        if (nb == 0) CL4_TRAP(0xb9ac0);
        FUN_000b9f14((uint64_t *)(base + lo0 * 8),
                     (uint64_t *)(base + lo1 * 8),
                     (uint64_t *)(base + lo2 * 8),
                     (uint64_t *)(uintptr_t)nb);
        if (0 != 0) break;                      /* unwind flag */
        if ((int64_t)lo2 < (int64_t)lo1) CL4_TRAP(0xb9a9c);
        uint64_t cur = *(uint64_t *)((uint64_t)vec + 0x10);
        if (cur <= rn - 2) CL4_TRAP(0xb9aa0);
        /* compact the run list: overwrite the merged pair */
        *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x20) = lo1;
        *(uint64_t *)((uint64_t)vec + rn * 0x10 + 0x28) = lo2;
        uint64_t tail = cur - rn;
        if (cur < rn) CL4_TRAP(0xb9aa4);
        rn = cur - 1;
        cL4_vec_move((void *)((uint64_t)vec + (rn + 1) * 0x10 + 0x20),
                     tail, (void *)((uint64_t)vec + (rn + 1) * 0x10 + 0x20));
        *(uint64_t *)((uint64_t)vec + 0x10) = rn;
    }
    cL4_ref_release((int64_t)vec);
}

/* ------------------------------------------------------------------ *
 * Tagged scalar helpers.
 * ------------------------------------------------------------------ */

/* FUN_000ba224 @ 0xba224   (est. cL4_tag_field_10)
 * Ghidra: long FUN_000ba224(ulong)
 * Follow a tagged pointer (low bit set => dereference the untagged word) and
 * return a pointer to the length-prefixed field stored at +0x10.
 * Confidence: medium */
int64_t FUN_000ba224(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_000ba254 @ 0xba254   (est. cL4_tag_field_04) — field at +4. */
int64_t FUN_000ba254(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 4) + (int64_t)*(int32_t *)(p + 4);
}

/* FUN_000ba284 @ 0xba284   (est. cL4_tag_field_08) — field at +8. */
int64_t FUN_000ba284(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_000bcfc4 @ 0xbcfc4   (est. cL4_tag_field_2c) — field at +0x2c. */
int64_t FUN_000bcfc4(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x2c) + (int64_t)*(int32_t *)(p + 0x2c);
}

/* FUN_000bcff4 @ 0xbcff4   (est. cL4_tag_field_28) — field at +0x28. */
int64_t FUN_000bcff4(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x28) + (int64_t)*(int32_t *)(p + 0x28);
}

/* FUN_000bd024 @ 0xbd024   (est. cL4_tag_field_24) — field at +0x24. */
int64_t FUN_000bd024(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x24) + (int64_t)*(int32_t *)(p + 0x24);
}

/* FUN_000bd054 @ 0xbd054   (est. cL4_tag_field_20) — field at +0x20. */
int64_t FUN_000bd054(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x20) + (int64_t)*(int32_t *)(p + 0x20);
}

/* FUN_000bd084 @ 0xbd084   (est. cL4_tag_field_1c) — field at +0x1c. */
int64_t FUN_000bd084(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x1c) + (int64_t)*(int32_t *)(p + 0x1c);
}

/* FUN_000bd0b4 @ 0xbd0b4   (est. cL4_tag_field_18) — field at +0x18. */
int64_t FUN_000bd0b4(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x18) + (int64_t)*(int32_t *)(p + 0x18);
}

/* FUN_000bd0e4 @ 0xbd0e4   (est. cL4_tag_field_10b) — field at +0x10. */
int64_t FUN_000bd0e4(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_000bd114 @ 0xbd114   (est. cL4_tag_field_0c) — field at +0xc. */
int64_t FUN_000bd114(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_000bd144 @ 0xbd144   (est. cL4_tag_field_04b) — field at +4. */
int64_t FUN_000bd144(uint64_t p)
{
    if ((p & 1) != 0) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 4) + (int64_t)*(int32_t *)(p + 4);
}

/* FUN_000bd3f0 @ 0xbd3f0   (est. cL4_nibble_acc)
 * Ghidra: long FUN_000bd3f0(long)
 * Accumulate a hex nibble (taken from register w10) into `param_1*16`.
 * Confidence: medium
 * Notes: the low byte of w10 is the freshly-parsed digit. */
int64_t FUN_000bd3f0(int64_t acc)
{
    uint8_t nibble;
    __asm__ volatile("" : "=r"(nibble) : "r"(acc));
    return acc * 0x10 + (int64_t)nibble;
}

/* ------------------------------------------------------------------ *
 * Bool / value getters (vtable-slot stubs in this region).
 * ------------------------------------------------------------------ */

/* FUN_000b9180 @ 0xb9180   (est. cL4_get_bool_flag)
 * Ghidra: undefined FUN_000b9180(void)
 * Call the object's boolean method at vtable offset +0xa0 and store the
 * low bit of the result into *x19 (the caller's out-pointer).
 * Confidence: medium */
void FUN_000b9180(void)
{
    cL4_ref_acquire(0);                         /* FUN_0007bf80 preamble */
    uint8_t *out = 0;                           /* unaff_x19 */
    uint8_t (*fn)(void) = *(uint8_t (**)(void))(0xa0);
    *out = fn() & 1;
}

/* FUN_000b91bc @ 0xb91bc   (est. cL4_call_slot_a8)
 * Ghidra: void FUN_000b91bc(undefined1*)
 * Invoke the no-op hook FUN_000ba34c(*param_1) then call the method at
 * vtable offset +0xa8 (a void-side-effect step).
 * Confidence: medium */
void FUN_000b91bc(uint8_t *param_1)
{
    FUN_000ba34c(*param_1);
    void (*fn)(void) = *(void (**)(void))(0xa8);
    fn();
}

/* FUN_000b91f4 @ 0xb91f4   (est. cL4_get_slot_d0)
 * Ghidra: void FUN_000b91f4(void)
 * Call the method at vtable offset +0xd0 and store its result into *x19.
 * Confidence: medium */
void FUN_000b91f4(void)
{
    cL4_ref_acquire(0);
    uint64_t (*fn)(void) = *(uint64_t (**)(void))(0xd0);
    uint64_t *out = 0;                          /* unaff_x19 */
    *out = fn();
}

/* FUN_000b9238 @ 0xb9238   (est. cL4_get_slot_100)
 * Ghidra: void FUN_000b9238(void)
 * Call the method at vtable offset +0x100 and store its result into *x19.
 * Confidence: medium */
void FUN_000b9238(void)
{
    cL4_ref_acquire(0);
    uint64_t (*fn)(void) = *(uint64_t (**)(void))(0x100);
    uint64_t *out = 0;                          /* unaff_x19 */
    *out = fn();
}

/* FUN_000ba2b4 @ 0xba2b4   (est. cL4_call_supervisor)
 * Ghidra: void FUN_000ba2b4(undefined8, undefined8, undefined8, undefined8)
 * Write a 5-word message to the tpidrro_el0 thread-local area and invoke
 * CallSupervisor(3) (a GEXIT-style supervisor call).
 * Confidence: medium
 * Notes: tpidrro_el0 read; message words: [5, param_3, param_4, 0, 0]. */
void FUN_000ba2b4(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t *msg = (uint64_t *)__builtin_arm_rsr64("tpidrro_el0");
    msg[0] = 5;
    msg[1] = p3;
    msg[2] = p4;
    msg[3] = 0;
    msg[4] = 0;
    __asm__ volatile("svc #3");                 /* CallSupervisor(3) */
}

/* FUN_000ba2f4 @ 0xba2f4   (est. cL4_debug_log_pair)
 * Ghidra: void FUN_000ba2f4(void)
 * Build a 16-byte debug value from the two data addresses 0x664d20/0x664c18
 * and log it.
 * Confidence: medium
 * Notes: string/table addresses DAT_00664d20, DAT_00664c18. */
void FUN_000ba2f4(void)
{
    cL4_debug_value(0x664d20, 0x664c18, 0, 0);
}

/* FUN_000ba35c @ 0xba35c   (est. cL4_fatal_error_str)
 * Ghidra: char* FUN_000ba35c(void)
 * Return the constant string "Fatal error" (s_Fatal_error_005accd0).
 * Confidence: high (string-matched) */
const char *FUN_000ba35c(void)
{
    return "Fatal error";                       /* s_Fatal_error_005accd0 */
}

/* FUN_000ba390 @ 0xba390   (est. cL4_next_sel)
 * Ghidra: undefined1[16] FUN_000ba390(void)
 * Return {x19+0x10 + 1, 0}: the next free selection slot in the caller's
 * object (x19).
 * Confidence: medium */
cl4_val_t FUN_000ba390(void)
{
    cl4_val_t r;
    r.lo = 0;
    r.hi = *(uint64_t *)(0 + 0x10) + 1;         /* unaff_x19 + 0x10 */
    return r;
}

/* FUN_000ba3a8 @ 0xba3a8   (est. cL4_log_fmt_671848)
 * Ghidra: void FUN_000ba3a8(void)
 * Resolve the log format string at 0x671848 and emit it.
 * Confidence: medium */
void FUN_000ba3a8(void)
{
    cL4_log_fmt(0x671848);
}

/* FUN_000ba3c0 @ 0xba3c0   (est. cL4_log_init_64e1d0)
 * Ghidra: void FUN_000ba3c0(void)
 * Emit the format string at 0x64e1d0 with the table address 0x4bf190.
 * Confidence: medium
 * Notes: DAT_0064e1d0 string, DAT_004bf190 table. */
void FUN_000ba3c0(void)
{
    cL4_log_fmt(0x64e1d0);                      /* FUN_00002534(0x64e1d0,&DAT_004bf190) */
}

/* FUN_000ba418 @ 0xba418   (est. cL4_obj_field_28)
 * Ghidra: long FUN_000ba418(void)
 * Return x20 + 0x28 (a pointer into the caller's object).
 * Confidence: medium */
int64_t FUN_000ba418(void)
{
    return 0 + 0x28;                            /* unaff_x20 + 0x28 */
}

/* FUN_000ba424 @ 0xba424   (est. cL4_obj_field_10c)
 * Ghidra: long FUN_000ba424(void)
 * Return x20 + 0x10.
 * Confidence: medium */
int64_t FUN_000ba424(void)
{
    return 0 + 0x10;                            /* unaff_x20 + 0x10 */
}

/* FUN_000ba430 @ 0xba430   (est. cL4_component_id)
 * Ghidra: undefined1[16] FUN_000ba430(void)
 * Return the 16-byte ASCII identifier "__COMPONENT".
 * Confidence: high (string-matched: bytes 0x4e4f504d4f435f5f = "__COMPON",
 *   0x4e45 = "EN") */
cl4_val_t FUN_000ba430(void)
{
    cl4_val_t r;
    r.lo = 0x4e4f504d4f435f5full;               /* "__COMPON" */
    r.hi = 0x4e45ull;                           /* "EN" */
    return r;
}

/* FUN_000ba448 @ 0xba448   (est. cL4_set_field_10_18)
 * Ghidra: void FUN_000ba448(long)
 * Store two stack-passed words into param_1+0x10 and param_1+0x18.
 * Confidence: medium */
void FUN_000ba448(int64_t obj)
{
    uint64_t v1, v2;
    __asm__ volatile("" : "=r"(v1) : );
    __asm__ volatile("" : "=r"(v2) : );
    *(uint64_t *)(obj + 0x10) = v1;             /* in_stack_00000030 */
    *(uint64_t *)(obj + 0x18) = v2;             /* in_stack_00000038 */
}

/* FUN_000ba4c8 @ 0xba4c8   (est. cL4_log_uid)
 * Ghidra: void FUN_000ba4c8(void)
 * Emit the tagged log pair (0x3a646975203b, 0xe6...) — "; uid:" — via
 * thunk_FUN_002acbb8.
 * Confidence: medium
 * Notes: bytes spell "; uid:" (0x3a646975203b little-endian). */
void FUN_000ba4c8(void)
{
    cL4_log_tagged(0x3a646975203bull, 0xe600000000000000ull);
}

/* FUN_000ba4dc @ 0xba4dc   (est. cL4_ref_acquire_slot)
 * Ghidra: void FUN_000ba4dc(long)
 * Acquire a reference on the object at (*(x24+0x38))[param_1*0x20] (a slot
 * in the caller's capability table).
 * Confidence: medium */
void FUN_000ba4dc(int64_t idx)
{
    uint64_t tbl = *(uint64_t *)(0 + 0x38);     /* unaff_x24 + 0x38 */
    cL4_ref_acquire(*(uint64_t *)(tbl + idx * 0x20));
}

/* FUN_000ba4f8 @ 0xba4f8   (est. cL4_obj_id_and_resolve)
 * Ghidra: undefined1[16] FUN_000ba4f8(undefined8)
 * Return {cL4_obj_id(), cL4_obj_resolve(param_1)}.
 * Confidence: medium */
cl4_val_t FUN_000ba4f8(uint64_t p)
{
    cl4_val_t r;
    r.lo = cL4_obj_id();
    r.hi = cL4_obj_resolve(p);
    return r;
}

/* FUN_000ba534 @ 0xba534   (est. cL4_slot_acquire_or_trap)
 * Ghidra: void FUN_000ba534(void)
 * Acquire a slot; trap on failure (result < 0).
 * Confidence: medium */
void FUN_000ba534(void)
{
    int64_t r = cL4_slot_acquire();
    if (r >= 0) {
        return;
    }
    CL4_TRAP(0xba554);
}

/* FUN_000ba538 @ 0xba538   (est. cL4_slot_acquire_or_trap_b) — same as above. */
void FUN_000ba538(void)
{
    int64_t r = cL4_slot_acquire();
    if (r >= 0) {
        return;
    }
    CL4_TRAP(0xba554);
}

/* FUN_000ba554 @ 0xba554   (est. cL4_slot_release) — release a slot. */
void FUN_000ba554(void)
{
    cL4_slot_release();
}

/* FUN_000ba558 @ 0xba558   (est. cL4_slot_release_b) — release a slot. */
void FUN_000ba558(void)
{
    cL4_slot_release();
}

/* ------------------------------------------------------------------ *
 * Tagged-value serialization / formatting.
 * ------------------------------------------------------------------ */

/* FUN_000bb6c0 @ 0xbb6c0   (est. cL4_val_repr)
 * Ghidra: undefined1[16] FUN_000bb6c0(void)
 * Produce a human-readable 16-byte representation of the typed value at the
 * caller's object (x20):  "idx: <name>(<value>)" with a trailing marker.
 * Confidence: medium
 * Notes: DAT_005c2b40 / 0xd0...0013 "(" pair; string at 0x5c2b20 "0x10". */
cl4_val_t FUN_000bb6c0(void)
{
    cL4_log_code(0x17);
    cL4_release_mask(0xe000000000000000ull);
    FUN_000bb378(*(uint64_t *)(0 + 0x28), *(uint8_t *)(0 + 0x30)); /* unaff_x20 */
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x202c, 0xe200000000000000ull);   /* ", " */
    uint64_t tag = 0x80000000005c2b40ull;
    uint64_t kind = 0xd000000000000013ull;
    if (*(uint8_t *)(0 + 0x31) == 0) {          /* unaff_x20 */
        kind = 0;
        tag = 0xe000000000000000ull;
    }
    cL4_log_tagged(kind, tag);
    cL4_release_mask(tag);
    cL4_log_tagged(0x29, 0xe100000000000000ull);      /* ")" */
    cl4_val_t r;
    r.lo = 0xd000000000000010ull;
    r.hi = 0x80000000005c2b20ull;
    return r;
}

/* FUN_000bb378 @ 0xbb378   (est. cL4_val_format)
 * Ghidra: undefined1[16] FUN_000bb378(ulong, undefined1)
 * Format a typed value (param_1) of kind param_2 into its {tag,string}
 * representation.  Kinds: default=nil/true/false, 1=u8, 2=u16, 3=u32,
 * 4=u64, 5=s8, 6=s16, 7=s32, 8=s64, 9=f32, 10=f64, 11=f64b.
 * Confidence: medium
 * Notes: kind strings ("u8 ", "u16 ", ...) in the switch; format tables at
 *   0x677600-0x6777e0. */
cl4_val_t FUN_000bb378(uint64_t val, uint8_t kind)
{
    uint64_t tag, str;
    switch (kind) {
    default: {
        bool neg = (val & 1) == 0;
        str = 0x65757274ull;                    /* "true" */
        if (neg) {
            str = 0x65736c6166ull;              /* "false" */
        }
        tag = 0xe400000000000000ull;
        if (neg) {
            tag = 0xe500000000000000ull;
        }
        break;
    }
    case 1:                                     /* u8 */
        cL4_log_tagged(0x670738, 0xe300000000000000ull);   /* FUN_000bd3d8(0x670738) */
        break;
    case 2:                                     /* u16 */
        cL4_log_tagged(0x670ce8, 0xe300000000000000ull);
        break;
    case 3:                                     /* u32 */
        cL4_log_tagged(0x671298, 0xe300000000000000ull);
        break;
    case 4:                                     /* u64 */
        cL4_log_tagged(0x671848, 0xe300000000000000ull);
        break;
    case 5:                                     /* s8 */
        cL4_log_tagged(0x670a20, 0xe300000000000000ull);
        break;
    case 6:                                     /* s16 */
        cL4_log_tagged(0x670fd0, 0xe300000000000000ull);
        break;
    case 7:                                     /* s32 */
        cL4_log_tagged(0x671580, 0xe300000000000000ull);
        break;
    case 8:                                     /* s64 */
        cL4_log_tagged(0x671b30, 0xe300000000000000ull);
        break;
    case 9:                                     /* f32 */
        str = 0;
        tag = 0xe000000000000000ull;
        cL4_log_tagged(0x20323366, 0xe400000000000000ull); /* "f32 " */
        break;
    case 10:                                    /* f64 */
        str = 0;
        tag = 0xe000000000000000ull;
        cL4_log_tagged(0x20343666, 0xe400000000000000ull); /* "f64 " */
        break;
    case 0xb:
        break;
    }
    /* finalize {tag,str} */
    cl4_val_t r;
    r.lo = str;
    r.hi = tag;
    return r;
}

/* FUN_000bd664 @ 0xbd664   (est. cL4_log_endian_dump)
 * Ghidra: undefined1[16] FUN_000bd664(void)
 * Produce a 16-byte "endian" debug token, logging " idx: <byte-order>)".
 * Confidence: medium
 * Notes: string at 0x671df8; tags 0x2065646f6e63202c (", encode ") and
 *   0xef203a7865646e69 ("index :"). 0x29 ")" terminator. */
cl4_val_t FUN_000bd664(void)
{
    cL4_log_code(0x1d);
    cL4_release_mask(0xe000000000000000ull);
    FUN_000bdc00();
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x2065646f6e63202cull, 0xef203a7865646e69ull); /* ", encode index:" */
    cL4_log_fmt(0x671df8);                       /* FUN_00027724(0x671df8) */
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x29, 0xe100000000000000ull); /* ")" */
    cl4_val_t r;
    r.lo = 0x646572656b6f7242ull;               /* "Broker ed" */
    r.hi = 0xe900000000000028ull;
    return r;
}

/* FUN_000bd174 @ 0xbd174   (est. cL4_fmt_650d40)
 * Ghidra: undefined1[16] FUN_000bd174(void)
 * Return the 16-byte constant {0x650d40, 0}.
 * Confidence: medium */
cl4_val_t FUN_000bd174(void)
{
    cl4_val_t r;
    r.lo = 0x650d40;
    r.hi = 0;
    return r;
}

/* FUN_000bde60 @ 0xbde60   (est. cL4_fmt_650db8)
 * Ghidra: undefined1[16] FUN_000bde60(void)
 * Return the 16-byte constant {0x650db8, 0}.
 * Confidence: medium */
cl4_val_t FUN_000bde60(void)
{
    cl4_val_t r;
    r.lo = 0x650db8;
    r.hi = 0;
    return r;
}

/* FUN_000bd370 @ 0xbd370   (est. cL4_fmt_6756a8)
 * Ghidra: undefined1[16] FUN_000bd370(void)
 * Return {&stack0x10, 0x6756a8}.
 * Confidence: medium
 * Notes: DAT_006756a8 format table. */
cl4_val_t FUN_000bd370(void)
{
    cl4_val_t r;
    r.lo = 0;
    r.hi = 0x6756a8;
    return r;
}

/* FUN_000be018 @ 0xbe018   (est. cL4_log_mmio_end)
 * Ghidra: undefined1[16] FUN_000be018(void)
 * Produce the 16-byte "end of MMIO setup" token, logging ") ...".
 * Confidence: medium
 * Notes: format string at 0x671df8, buffer 0x677830; 0x29 ")" terminator;
 *   string at 0x5c2dc0, kind 0xd...002c. */
cl4_val_t FUN_000be018(void)
{
    cL4_log_code(0x1d);
    cL4_release_mask(0xe000000000000000ull);
    cL4_log_fmt(0x671df8);
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x29, 0xe100000000000000ull); /* ")" */
    cl4_val_t r;
    r.lo = 0xd00000000000002cull;
    r.hi = 0x80000000005c2dc0ull;
    return r;
}

/* ------------------------------------------------------------------ *
 * Typed-value parse dispatcher and width-specific parsers.
 * ------------------------------------------------------------------ */

/* FUN_000bc8cc @ 0xbc8cc   (est. cL4_parse_u8)
 * Ghidra: uint FUN_000bc8cc(ulong, ulong)
 * Parse an unsigned 8-bit value from a tagged string (param_1 lo / param_2
 * kind).  Handles optional '+'/'-' sign and hex digits; returns the value
 * ORed with an error flag in the high bits (0x100 on failure / overlong).
 * Confidence: medium
 * Notes: overflow guard `(uVar5 - 8 & 0xff) < 0xf0`; DAT_.. hex digit table. */
uint32_t FUN_000bc8cc(uint64_t v, uint64_t kind)
{
    uint8_t *s;
    int64_t len;
    uint32_t acc = 0, err = 0x100;

    if ((kind >> 0x3c & 1) != 0) {
        return 0x100;                           /* invalid/empty */
    }
    if ((kind >> 0x3d & 1) == 0) {
        /* indirect: {len, ptr} resolved from v */
        cl4_val_t sp = FUN_002a9ba8(v);         /* resolve string span */
        len = (int64_t)sp.hi;
        s = (uint8_t *)sp.lo;
        if (len < 1) {
            CL4_TRAP(0xbcc4c);
        }
        uint8_t c = *s;
        if (c == '+') {
            len -= 1;
            s += 1;
            acc = 0;
            while (len > 0) {
                c = *s++;
                uint32_t d = c - 0x30;
                if (d > 9) {
                    if (c - 0x41 < 6) d = c - 0x37;
                    else if (c - 0x61 < 6) d = c - 0x57;
                    else { acc = 0; err = 0x100; goto out; }
                }
                if ((acc - 8 & 0xff) < 0xf0) { acc = 0; err = 0x100; goto out; }
                acc = acc * 0x10 + d;
                len -= 1;
            }
        } else if (c == '-') {
            len -= 1;
            s += 1;
            acc = 0;
            while (len > 0) {
                c = *s++;
                uint32_t d = c - 0x30;
                if (d > 9) {
                    if (c - 0x41 < 6) d = c - 0x37;
                    else if (c - 0x61 < 6) d = c - 0x57;
                    else { acc = 0; err = 0x100; goto out; }
                }
                if (((acc - 8 & 0xff) < 0xf0) ||
                    (acc = (int8_t)(acc << 4) - (int8_t)d, (int8_t)acc != acc)) {
                    acc = 0; err = 0x100; goto out;
                }
                len -= 1;
            }
        } else {
            acc = 0;
            while (s != 0) {
                c = *s;
                uint32_t d = c - 0x30;
                if (d > 9) {
                    if (c - 0x41 < 6) d = c - 0x37;
                    else if (c - 0x61 < 6) d = c - 0x57;
                    else { acc = 0; err = 0x100; goto out; }
                }
                if ((acc - 8 & 0xff) < 0xf0) { acc = 0; err = 0x100; goto out; }
                acc = acc * 0x10 + d;
                s += 1;
                len -= 1;
            }
        }
        err = 0;
    } else {
        /* inline tagged short string */
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        s = (uint8_t *)&v;
        if (n == 0) CL4_TRAP(0xbcc4c);
        acc = (uint32_t)v & 0xff;
        if (acc == '+') {
            if (n > 1) {
                acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
                while (n-- > 0) {
                    uint8_t c = *s++;
                    uint32_t d = c - 0x30;
                    if (d > 9) {
                        if (c - 0x41 < 6) d = c - 0x37;
                        else if (c - 0x61 < 6) d = c - 0x57;
                        else { acc = 0; err = 0x100; goto out; }
                    }
                    if ((acc - 8 & 0xff) < 0xf0) { acc = 0; err = 0x100; goto out; }
                    acc = acc * 0x10 + d;
                    err = 0;
                }
            }
        } else if (acc != '-') {
            acc = 0;
            while (n != 0) {
                uint8_t c = *(uint8_t *)(uintptr_t)s;
                uint32_t d = c - 0x30;
                if (d > 9) {
                    if (c - 0x41 < 6) d = c - 0x37;
                    else if (c - 0x61 < 6) d = c - 0x57;
                    else { acc = 0; err = 0x100; goto out; }
                }
                if ((acc - 8 & 0xff) < 0xf0) { acc = 0; err = 0x100; goto out; }
                acc = acc * 0x10 + d;
                s += 1; n -= 1; err = 0;
            }
        } else {
            if (n > 1) {
                acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
                while (n-- > 0) {
                    uint8_t c = *s++;
                    uint32_t d = c - 0x30;
                    if (d > 9) {
                        if (c - 0x41 < 6) d = c - 0x37;
                        else if (c - 0x61 < 6) d = c - 0x57;
                        else { acc = 0; err = 0x100; goto out; }
                    }
                    if (((acc - 8 & 0xff) < 0xf0) ||
                        (acc = (int8_t)(acc << 4) - (int8_t)d, (int8_t)acc != acc)) {
                        acc = 0; err = 0x100; goto out;
                    }
                    err = 0;
                }
            }
        }
    }
out:
    return err | (acc & 0xff);
}

/* FUN_000bcc54 @ 0xbcc54   (est. cL4_parse_u16)
 * Ghidra: uint FUN_000bcc54(ulong, ulong)
 * Parse an unsigned 16-bit value from a tagged string; returns value ORed
 * with an error flag (0x10000 on failure).  Same structure as cL4_parse_u8
 * but with a 16-bit accumulator and 0xfff overflow guard.
 * Confidence: medium */
uint32_t FUN_000bcc54(uint64_t v, uint64_t kind)
{
    uint8_t *s;
    int64_t len;
    uint32_t acc = 0, err = 0x10000;

    if ((kind >> 0x3c & 1) != 0) return 0x10000;
    if ((kind >> 0x3d & 1) == 0) {
        cl4_val_t sp = FUN_002a9ba8(v);
        len = (int64_t)sp.hi; s = (uint8_t *)sp.lo;
        if (len < 1) CL4_TRAP(0xbcfbc);
        uint8_t c = *s;
        if (c == '+') {
            len--; s++; acc = 0;
            while (len > 0) {
                c = *s++;
                uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if (0xfff < (acc & 0xffff)) goto fail;
                acc = acc * 0x10 + d; len--;
            }
        } else if (c == '-') {
            len--; s++; acc = 0;
            while (len > 0) {
                c = *s++;
                uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if ((0xfff < (acc & 0xffff)) ||
                    (acc = (acc & 0xfff) * 0x10 - (d & 0xff), (acc & 0xffff0000) != 0)) goto fail;
                len--;
            }
        } else {
            acc = 0;
            while (s != 0) {
                c = *s;
                uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if (0xfff < (acc & 0xffff)) goto fail;
                acc = acc * 0x10 + d; s++; len--;
            }
        }
        err = 0;
    } else {
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        s = (uint8_t *)&v;
        if (n == 0) CL4_TRAP(0xbcfbc);
        acc = (uint32_t)v & 0xff;
        if (acc == '+') {
            if (n > 1) { acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
                while (n-- > 0) { uint8_t c = *s++; uint32_t d = c - 0x30;
                    if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                    if (0xfff < (acc & 0xffff)) goto fail; acc = acc * 0x10 + d; err = 0; } }
        } else if (acc != '-') {
            acc = 0;
            while (n != 0) { uint8_t c = *(uint8_t *)(uintptr_t)s; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if (0xfff < (acc & 0xffff)) goto fail; acc = acc * 0x10 + d; s++; n--; err = 0; }
        } else {
            if (n > 1) { acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
                while (n-- > 0) { uint8_t c = *s++; uint32_t d = c - 0x30;
                    if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                    if ((0xfff < (acc & 0xffff)) ||
                        (acc = (acc & 0xfff) * 0x10 - (d & 0xff), (acc & 0xffff0000) != 0)) goto fail;
                    err = 0; } }
        }
    }
    return err | (acc & 0xffff);
fail:
    return 0x10000;
}

/* FUN_000bc534 @ 0xbc534   (est. cL4_parse_u16b)
 * Ghidra: uint FUN_000bc534(ulong, ulong)
 * Parse a 16-bit value with a wider overflow window (error flag 0x1000000);
 * otherwise mirrors cL4_parse_u16.
 * Confidence: medium */
uint32_t FUN_000bc534(uint64_t v, uint64_t kind)
{
    uint8_t *s;
    int64_t len;
    uint32_t acc = 0, err = 0x1000000;

    if ((kind >> 0x3c & 1) != 0) return 0x1000000;
    if ((kind >> 0x3d & 1) == 0) {
        cl4_val_t sp = FUN_002a9ba8(v);
        len = (int64_t)sp.hi; s = (uint8_t *)sp.lo;
        if (len < 1) CL4_TRAP(0xbc8c0);
        uint8_t c = *s;
        if (c == '+') { len--; s++; acc = 0;
            while (len > 0) { c = *s++; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if ((acc - 0x800 & 0xffff) < 0xf000) goto fail;
                acc = acc * 0x10 + d; len--; } }
        else if (c == '-') { len--; s++; acc = 0;
            while (len > 0) { c = *s++; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if (((acc - 0x800 & 0xffff) < 0xf000) ||
                    (acc = (int16_t)(acc << 4) - (d & 0xff), (int16_t)acc != (int16_t)acc)) goto fail;
                len--; } }
        else { acc = 0;
            while (s != 0) { c = *s; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if ((acc - 0x800 & 0xffff) < 0xf000) goto fail;
                acc = acc * 0x10 + d; s++; len--; } }
        err = 0;
    } else {
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        s = (uint8_t *)&v;
        if (n == 0) CL4_TRAP(0xbc8c0);
        acc = (uint32_t)v & 0xff;
        if (acc == '+') { if (n > 1) { acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
            while (n-- > 0) { uint8_t c = *s++; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if ((acc - 0x800 & 0xffff) < 0xf000) goto fail; acc = acc * 0x10 + d; err = 0; } } }
        else if (acc != '-') { acc = 0;
            while (n != 0) { uint8_t c = *(uint8_t *)(uintptr_t)s; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if ((acc - 0x800 & 0xffff) < 0xf000) goto fail; acc = acc * 0x10 + d; s++; n--; err = 0; } }
        else { if (n > 1) { acc = 0; s = (uint8_t *)(((uint64_t)&v) | 1);
            while (n-- > 0) { uint8_t c = *s++; uint32_t d = c - 0x30;
                if (d > 9) { if (c - 0x41 < 6) d = c - 0x37; else if (c - 0x61 < 6) d = c - 0x57; else goto fail; }
                if (((acc - 0x800 & 0xffff) < 0xf000) ||
                    (acc = (int16_t)(acc << 4) - (d & 0xff), (int16_t)acc != (int16_t)acc)) goto fail;
                err = 0; } } }
    }
    return err | (acc & 0xffff);
fail:
    return 0x1000000;
}

/* FUN_000bb7fc @ 0xbb7fc   (est. cL4_parse_u64)
 * Ghidra: undefined1[16] FUN_000bb7fc(ulong, ulong)
 * Parse an unsigned 64-bit value from a tagged string; returns {value, kind}
 * where kind&0xff==1 on success and kind&0xff00==0x100 on a re-parse request.
 * Confidence: medium */
cl4_val_t FUN_000bb7fc(uint64_t v, uint64_t kind)
{
    int64_t val = 0;
    uint64_t err = 0x100;

    if ((kind >> 0x3c & 1) != 0) {
        err = 0x100; val = 0;
        goto done;
    }
    if ((kind >> 0x3d & 1) == 0) {
        cl4_val_t sp;
        if ((v >> 0x3c & 1) == 0) sp = FUN_002a9ba8(v);
        else { sp.hi = v & 0xffffffffffff; sp.lo = (kind & 0xfffffffffffffff) + 0x20; }
        int64_t len = (int64_t)sp.hi;
        uint8_t *s = (uint8_t *)sp.lo;
        if (len < 1) CL4_TRAP(0xbbab8);
        uint8_t c = *s;
        if (c == '+') {
            bool done1 = (len == 1);
            val = 0;
            if (len == 1) { err = 0x100; goto done; }
            /* hex accumulate using out-of-slice helpers */
            uint64_t acc = 0, st = 0;
            s++; len--;
            while (len > 0) {
                uint8_t ch = *s++;
                uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if (acc >> 0x3c != 0) goto bad;
                acc = acc * 0x10 + d;
                len--;
            }
            val = (int64_t)acc;
        } else {
            bool neg = (c == '-');
            if (neg) { s++; len--; val = 0; }
            if (s != 0) {
                uint64_t acc = 0;
                bool negf = neg;
                while (s != 0) {
                    uint8_t ch = *s;
                    uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                    if (acc >> 0x3c != 0) goto bad;
                    if (negf) acc = acc * 0x10 - d; else acc = acc * 0x10 + d;
                    s++; len--;
                }
                val = (int64_t)acc;
            }
        }
        err = 0;
    } else {
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        if (n == 0) CL4_TRAP(0xbbabc);
        uint32_t b = (uint32_t)v & 0xff;
        uint8_t *sp = (uint8_t *)&v;
        if (b == '+') {
            val = 0;
            sp = (uint8_t *)(((uint64_t)&v) | 1);
            n--;
            if (n > 0) {
                uint64_t acc = 0;
                while (n-- > 0) { uint8_t ch = *sp++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                    if (acc >> 0x3c != 0) goto bad; acc = acc * 0x10 + d; }
                val = (int64_t)acc;
            }
        } else if (b == '-') {
            val = 0;
            sp = (uint8_t *)(((uint64_t)&v) | 1);
            n--;
            if (n > 0) {
                uint64_t acc = 0;
                while (n-- > 0) { uint8_t ch = *sp++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                    if ((acc >> 0x3c != 0) || (acc = acc * 0x10 - d, acc >> 0x3c != 0)) goto bad; }
                val = (int64_t)acc;
            }
        } else {
            val = 0;
            uint64_t acc = 0;
            while (n-- > 0) { uint8_t ch = *sp++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if (acc >> 0x3c != 0) goto bad; acc = acc * 0x10 + d; }
            val = (int64_t)acc;
        }
        err = 0;
    }
done: ;
    cl4_val_t r;
    r.hi = err;
    r.lo = (uint64_t)val;
    return r;
bad:
    val = 0; err = 1; goto done;
}

/* FUN_000bbe14 @ 0xbbe14   (est. cL4_parse_s64)
 * Ghidra: undefined1[16] FUN_000bbe14(ulong, ulong)
 * Parse a signed 64-bit value from a tagged string; returns {value, kind}
 * with kind=0x100 on failure and kind=1 on re-parse.
 * Confidence: medium */
cl4_val_t FUN_000bbe14(uint64_t v, uint64_t kind)
{
    int64_t val = 0;
    uint64_t err = 0x100;

    if ((kind >> 0x3c & 1) != 0) { val = 0; err = 0x100; goto done; }
    if ((kind >> 0x3d & 1) == 0) {
        cl4_val_t sp;
        if ((v >> 0x3c & 1) == 0) sp = FUN_002a9ba8(v);
        else { sp.hi = v & 0xffffffffffff; sp.lo = (kind & 0xfffffffffffffff) + 0x20; }
        int64_t len = (int64_t)sp.hi;
        uint8_t *s = (uint8_t *)sp.lo;
        if (len < 1) CL4_TRAP(0xbc190);
        uint8_t c = *s;
        if (c == '+') { s++; len--; val = 0;
            if (len > 0) { uint64_t acc = 0;
                while (len > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                    if ((acc + 0xf800000000000000ull) >> 0x3c < 0xf) goto bad;
                    acc = acc * 0x10 + d; len--; }
                val = (int64_t)acc; } }
        else if (c == '-') { s++; len--; val = 0;
            if (len > 0) { uint64_t acc = 0;
                while (len > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                    if (((acc + 0xf800000000000000ull) >> 0x3c < 0xf) ||
                        (uint64_t)acc * 0x10 < (uint64_t)d) goto bad;
                    acc = acc * 0x10 - d; len--; }
                val = (int64_t)acc; } }
        else { val = 0;
            uint64_t acc = 0;
            while (s != 0) { uint8_t ch = *s; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if (((acc + 0xf800000000000000ull) >> 0x3c) < 0xf) goto bad;
                acc = acc * 0x10 + d; s++; len--; }
            val = (int64_t)acc; }
        err = 0;
    } else {
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        uint8_t *s = (uint8_t *)&v;
        if (n == 0) CL4_TRAP(0xbc194);
        uint32_t b = (uint32_t)v & 0xff;
        if (b == '+') { if (n > 1) { s = (uint8_t *)(((uint64_t)&v) | 1); n--; val = 0;
            uint64_t acc = 0;
            while (n-- > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if ((acc + 0xf800000000000000ull) >> 0x3c < 0xf) goto bad;
                acc = acc * 0x10 + d; }
            val = (int64_t)acc; } }
        else if (b == '-') { if (n > 1) { s = (uint8_t *)(((uint64_t)&v) | 1); n--; val = 0;
            uint64_t acc = 0;
            while (n-- > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if (((acc + 0xf800000000000000ull) >> 0x3c < 0xf) || acc * 0x10 < d) goto bad;
                acc = acc * 0x10 - d; }
            val = (int64_t)acc; } }
        else { val = 0; uint64_t acc = 0;
            while (n-- > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto bad; }
                if ((acc + 0xf800000000000000ull) >> 0x3c < 0xf) goto bad;
                acc = acc * 0x10 + d; }
            val = (int64_t)acc; }
        err = 0;
    }
done: ;
    cl4_val_t r;
    r.hi = err;
    r.lo = (uint64_t)val;
    return r;
bad:
    val = 0; err = 1; goto done;
}

/* FUN_000bbac4 @ 0xbbac4   (est. cL4_parse_u32)
 * Ghidra: ulong FUN_000bbac4(ulong, ulong)
 * Parse an unsigned 32-bit value from a tagged string; returns value ORed
 * with an error flag in the high bits (0x10000000000 on failure).
 * Confidence: medium */
uint64_t FUN_000bbac4(uint64_t v, uint64_t kind)
{
    uint64_t *lp = &v;
    uint64_t acc = 0, err = 0x10000000000ull;

    if ((kind >> 0x3c & 1) != 0) return 0x10000000000ull;
    if ((kind >> 0x3d & 1) == 0) {
        cl4_val_t sp;
        if ((v >> 0x3c & 1) == 0) sp = FUN_002a9ba8(v);
        else { sp.hi = v & 0xffffffffffff; sp.lo = (kind & 0xfffffffffffffff) + 0x20; }
        int64_t len = (int64_t)sp.hi;
        uint8_t *s = (uint8_t *)sp.lo;
        if (len < 1) CL4_TRAP(0xbbe08);
        uint8_t c = *s;
        if (c == '+') { s++; len--;
            if (len > 0) { acc = 0;
                while (len > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                    if (acc >> 0x1c != 0) goto fail;
                    acc = acc * 0x10 + (d & 0xff); len--; } } }
        else if (c == '-') { s++; len--;
            if (len > 0) { acc = 0;
                while (len > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                    if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                    if ((acc >> 0x1c != 0) || acc * 0x10 < (uint64_t)(d & 0xff)) goto fail;
                    acc = acc * 0x10 - (d & 0xff); len--; } } }
        else { acc = 0;
            while (s != 0) { uint8_t ch = *s; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                if (acc >> 0x1c != 0) goto fail;
                acc = acc * 0x10 + (d & 0xff); s++; len--; } }
        err = 0;
    } else {
        uint32_t n = (uint32_t)(kind >> 0x38 & 0xf);
        uint8_t *s = (uint8_t *)&v;
        if (n == 0) CL4_TRAP(0xbbe0c);
        uint32_t b = (uint32_t)v & 0xff;
        if (b == '+') { if (n > 1) { s = (uint8_t *)(((uint64_t)&v) | 1); n--; acc = 0;
            while (n-- > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                if (acc >> 0x1c != 0) goto fail; acc = acc * 0x10 + (d & 0xff); } } }
        else if (b != '-') { acc = 0;
            while (n != 0) { uint8_t ch = *(uint8_t *)(uintptr_t)s; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                if (acc >> 0x1c != 0) goto fail; acc = acc * 0x10 + (d & 0xff); s++; n--; } }
        else { if (n > 1) { s = (uint8_t *)(((uint64_t)&v) | 1); n--; acc = 0;
            while (n-- > 0) { uint8_t ch = *s++; uint32_t d = ch - 0x30;
                if (d > 9) { if (ch - 0x41 < 6) d = ch - 0x37; else if (ch - 0x61 < 6) d = ch - 0x57; else goto fail; }
                if ((acc >> 0x1c != 0) || acc * 0x10 < (uint64_t)(d & 0xff)) goto fail;
                acc = acc * 0x10 - (d & 0xff); } } }
    }
    return acc;
fail:
    return 0x10000000000ull;
}

/* FUN_000bb158 @ 0xbb158   (est. cL4_parse_bool_flag)
 * Ghidra: ulong FUN_000bb158(ulong, ulong)
 * Parse a boolean ("true"/"false") from a tagged string; returns a packed
 * value with 0x100000000 set for false and the parse result in the low bits.
 * Confidence: medium */
uint64_t FUN_000bb158(uint64_t v, uint64_t kind)
{
    bool r = false;
    uint32_t err = 0;
    uint64_t *sp = &v;

    if ((kind >> 0x3c & 1) != 0) {
        FUN_002a4468(&v, (uint64_t)FUN_000bd2b8, 0, v, kind, 0x672870);
        cL4_release_mask(kind);
        goto out;
    }
    if ((kind >> 0x3d & 1) == 0) {
        if ((v >> 0x3c & 1) == 0) goto do_indirect;
        uint8_t *p = (uint8_t *)((kind & 0xfffffffffffffff) + 0x20);
        if ((0x20 < (uint64_t)*p) || ((0x100003e01U >> (*p & 0x3f) & 1) == 0)) goto parse_str;
        r = false;
    } else {
        uint64_t save = kind & 0xffffffffffffff;
        v = v;
        if (((uint32_t)v & 0xff) < 0x21 && ((0x100003e01U >> (v & 0x3f) & 1) != 0)) {
            r = false;
        } else {
            sp = &v;
parse_str: ;
            char *s = (char *)cL4_parse_bool_a(sp, &err);
            if (s == 0) { r = false; }
            else { r = (*s == 0); }
        }
    }
    cL4_release_mask(kind);
out: ;
    uint64_t result = err;
    if ((char)v == 0) {
        result = 0x100000000ull;
    }
    return result;
do_indirect:
    /* fallthrough into parse_str via helper path */
    sp = &v;
    goto parse_str;
}

/* FUN_000bb268 @ 0xbb268   (est. cL4_parse_bool_flag2)
 * Ghidra: undefined1[16] FUN_000bb268(ulong, ulong)
 * Parse a boolean and return {value, status^1, 0}: value is the parsed bool
 * or 0 on failure, status is 0 on success / 1 on error (XORed).
 * Confidence: medium */
cl4_val_t FUN_000bb268(uint64_t v, uint64_t kind)
{
    uint32_t ok = 0;
    uint64_t *sp = &v;
    uint64_t val = 0;

    if ((kind >> 0x3c & 1) != 0) {
        FUN_002a4468(&v, (uint64_t)FUN_000bd2e8, 0, v, kind, 0x672870);
        cL4_release_mask(kind);
        ok = (uint32_t)(uint8_t)v;
        goto done;
    }
    if ((kind >> 0x3d & 1) == 0) {
        if ((v >> 0x3c & 1) == 0) { sp = &v; goto parse; }
        uint8_t *p = (uint8_t *)((kind & 0xfffffffffffffff) + 0x20);
        if ((0x20 < (uint64_t)*p) || ((0x100003e01U >> (*p & 0x3f) & 1) == 0)) goto parse;
        ok = 0;
    } else {
        uint64_t save = kind & 0xffffffffffffff;
        v = v;
        if (((uint32_t)v & 0xff) < 0x21 && ((0x100003e01U >> (v & 0x3f) & 1) != 0)) {
            ok = 0;
        } else {
parse: ;
            char *s = (char *)cL4_parse_bool_b(sp, &val);
            if (s == 0) ok = 0;
            else ok = (*s == 0);
        }
    }
    cL4_release_mask(kind);
done:
    if (ok == 0) {
        val = 0;
    }
    cl4_val_t r;
    r.lo = val;
    r.hi = (uint32_t)(ok ^ 1);
    return r;
}

/* FUN_000bd248 @ 0xbd248   (est. cL4_bool_from_tag)
 * Ghidra: void FUN_000bd248(undefined8, byte*, undefined8, code*)
 * Evaluate a boolean: true if the first byte of *param_2 is an identifier
 * start OR the callback returns an empty string; store the result at param_1.
 * Confidence: medium
 * Notes: 0x100003e01U bitmask of identifier-start chars; callback = parser. */
void FUN_000bd248(uint64_t out, uint8_t *tag, uint64_t p3, int64_t (*cb)(void))
{
    bool r = false;
    if ((*tag < 0x21 && ((1ull << (*tag & 0x3f)) & 0x100003e01U) != 0) ||
        (char *)(*cb)() == 0) {
        r = false;
    } else {
        r = *(char *)(*cb)() == '\0';
    }
    *(bool *)out = r;
}

/* FUN_000bd2b8 @ 0xbd2b8   (est. cL4_bool_parse_a)
 * Ghidra: void FUN_000bd2b8(undefined8)
 * Parse a bool from the caller's tagged string field at x20+0x10 using the
 * variant-A parser (FUN_003d3130); store the result at param_1.
 * Confidence: medium */
void FUN_000bd2b8(uint64_t out)
{
    FUN_000bd248(out, *(uint8_t **)(0 + 0x10), (uint64_t)FUN_003d3130, 0);
}

/* FUN_000bd2bc @ 0xbd2bc   (est. cL4_bool_parse_ab) — same as above. */
void FUN_000bd2bc(uint64_t out)
{
    FUN_000bd248(out, *(uint8_t **)(0 + 0x10), (uint64_t)FUN_003d3130, 0);
}

/* FUN_000bd2e8 @ 0xbd2e8   (est. cL4_bool_parse_b)
 * Ghidra: void FUN_000bd2e8(undefined8)
 * Parse a bool using the variant-B parser (FUN_003d30c4).
 * Confidence: medium */
void FUN_000bd2e8(uint64_t out)
{
    FUN_000bd248(out, *(uint8_t **)(0 + 0x10), (uint64_t)FUN_003d30c4, 0);
}

/* FUN_000bd2ec @ 0xbd2ec   (est. cL4_bool_parse_bb) — same as above. */
void FUN_000bd2ec(uint64_t out)
{
    FUN_000bd248(out, *(uint8_t **)(0 + 0x10), (uint64_t)FUN_003d30c4, 0);
}

/* FUN_000bd35c @ 0xbd35c   (est. cL4_tag_eq_kind)
 * Ghidra: void FUN_000bd35c(undefined8)
 * Return whether param_1 equals the tagged kind 0xe3... via cL4_tag_eq.
 * Confidence: medium */
bool FUN_000bd35c(uint64_t p)
{
    return (cL4_tag_eq(p, 0xe300000000000000ull, 0, 0, 0) & 1) != 0;
}

/* FUN_000bd394 @ 0xbd394   (est. cL4_tag_eq_kind2) — tag equality check. */
bool FUN_000bd394(uint64_t a, uint64_t b)
{
    return (cL4_tag_eq(a, b, 0, 0, 0) & 1) != 0;
}

/* FUN_000bd3d8 @ 0xbd3d8   (est. cL4_log_fmt_indirect) */
void FUN_000bd3d8(void)
{
    cL4_log_fmt(0);
}

/* FUN_000bd3b0 @ 0xbd3b0   (est. cL4_tag_eq_kind3) — no-op compare hook. */
void FUN_000bd3b0(void) { cL4_type_noop(); }

/* ------------------------------------------------------------------ *
 * Tagged-value dispatcher (type-typed access to a launcher config object).
 * ------------------------------------------------------------------ */

/* FUN_000baf3c @ 0xbaf3c   (est. cL4_tagged_dispatch)
 * Ghidra: void FUN_000baf3c(undefined8, undefined8, undefined8)
 * Dispatch on the type byte at the caller's object (x20)+0x30 and perform the
 * matching typed access on the tagged value param_3, emitting a debug line.
 *   case 0/8: fetch 16-byte field (offset by type) + bool flag
 *   case 1/2/3/5/6/7: fetch string field + tag
 *   case 4: fetch raw value
 *   case 9/10: jump to a helper at the fetched field pointer
 *   case 0xb: (f64)
 * Confidence: medium
 * Notes: side effects via cL4_log_tagged; type byte at +0x30, flags at
 *   +0x31/+0x28. */
void FUN_000baf3c(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    uint8_t kind = *(uint8_t *)(obj + 0x30);
    uint64_t flags = *(uint64_t *)(obj + 0x28);

    if (*(uint8_t *)(obj + 0x31) == 1) {
        int64_t lv = *(int64_t *)(obj + 0x28);
        uint8_t c = *(uint8_t *)(obj + 0x30);
        uint64_t v = cL4_typed_val(p3);
        cL4_tag_eq(v, (c != '\v' || lv != 0), 0, 0, 0);   /* FUN_000bd3a4 */
        cL4_type_noop();
    }

    switch (kind) {
    default:
        cL4_tag_eq(cL4_typed_val(p3), (uint32_t)flags & 1, 0, 0, 0);
        cL4_type_noop();
        break;
    case 1: cL4_typed_val(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 2: cL4_typed_raw(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 3: cL4_typed_val(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 4: cL4_tag_eq(cL4_typed_raw(p3), flags, 0, 0, 0); cL4_type_noop(); break;
    case 5: cL4_typed_val(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 6: cL4_typed_val(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 7: cL4_typed_val(p3); cL4_parse_noop(); cL4_type_noop(); break;
    case 8: cL4_tag_eq(cL4_typed_raw(p3), flags, 0, 0, 0); cL4_type_noop(); break;
    case 9: {
        int64_t (*fn)(void) = (int64_t (*)(void))FUN_000bcff4(p3);
        fn(); break;
    }
    case 10: {
        int64_t (*fn)(void) = (int64_t (*)(void))FUN_000bcfc4(p3);
        fn(); break;
    }
    case 0xb:
        break;
    }
}

/* FUN_000bb7cc @ 0xbb7cc   (est. cL4_tagged_dispatch_stub) — calls dispatcher. */
void FUN_000bb7cc(void)
{
    FUN_000baf3c(0, 0, 0);
}

/* FUN_000bae8c @ 0xbae8c   (est. cL4_tagged_obj_init)
 * Ghidra: void FUN_000bae8c(undefined8, undefined1, undefined8, undefined1,
 *                           undefined8, byte)
 * Initialize a tagged-config object (from a fresh allocation): store the
 * value fields at +0x10..+0x40 with the type/flags bytes and a duplicate
 * value at +0x38.
 * Confidence: medium */
void FUN_000bae8c(uint64_t v1, uint8_t t1, uint64_t v2, uint8_t t2, uint64_t v3, uint8_t b)
{
    uint64_t obj = cL4_obj_alloc_typed(0, 0, 0);
    *(uint64_t *)(obj + 0x10) = v2;
    *(uint64_t *)(obj + 0x18) = v3;
    *(uint8_t *)(obj + 0x20) = b | 0x80;
    *(uint64_t *)(obj + 0x28) = v1;
    *(uint8_t *)(obj + 0x30) = t1;
    *(uint8_t *)(obj + 0x31) = t2;
    *(uint64_t *)(obj + 0x38) = v3;
    *(uint8_t *)(obj + 0x40) = b;
}

/* FUN_000baf14 @ 0xbaf14   (est. cL4_tagged_obj_init_b)
 * Ghidra: void FUN_000baf14(...)
 * Same as cL4_tagged_obj_init but writes into the caller's object (x20).
 * Confidence: medium */
void FUN_000baf14(uint64_t v1, uint8_t t1, uint64_t v2, uint8_t t2, uint64_t v3, uint8_t b)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    *(uint64_t *)(obj + 0x10) = v2;
    *(uint64_t *)(obj + 0x18) = v3;
    *(uint8_t *)(obj + 0x20) = b | 0x80;
    *(uint64_t *)(obj + 0x28) = v1;
    *(uint8_t *)(obj + 0x30) = t1;
    *(uint8_t *)(obj + 0x31) = t2;
    *(uint64_t *)(obj + 0x38) = v3;
    *(uint8_t *)(obj + 0x40) = b;
}

/* ------------------------------------------------------------------ *
 * Exclave Launcher main typed-value parser.
 * ------------------------------------------------------------------ */

/* FUN_000ba594 @ 0xba594   (est. cL4_exclave_value_parse)
 * Ghidra: undefined1[16] FUN_000ba594(undefined8, undefined8, ulong, ulong, ulong)
 * Parse a typed value from the Exclave Launcher configuration string
 * (param_1/param_2 = {tag, kind}) into its {value, kind} form.  Dispatches
 * on the value's type (bool, u8/u16/u32/u64, s8/s16/s32/s64, f32/f64) and
 * returns kind 0xff (error) or 0 on success, with the parsed value in lo.
 * Handles '+/-' sign, hex digits, and inline vs. indirect strings.
 * Confidence: medium
 * Notes: string table s_InternalExclaveLauncher_LiteralR_005c2ac0; the
 *   per-type width parsers (FUN_000bb7fc/bbac4/be14/bc534/bc8cc/bcc54) and
 *   value getters (FUN_000b02dc..b077c).  SoftwareBreakpoint guards. */
cl4_val_t FUN_000ba594(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t val = p3;
    uint64_t kind = 0xff;
    uint64_t wide = p4;

    if (p4 == 0) {
        if ((p5 & 1) == 0) {
            /* Fatal error from InternalExclaveLauncher */
            cL4_fatal_frame();
        }
        cL4_release_mask(p2);
        val = 0;
        kind = 0xb;
        goto out;
    }

    /* resolve the {tag,kind} of the value */
    cl4_val_t sp = FUN_0029d3d8(p1, p2);
    uint64_t tag = sp.hi;
    uint64_t taglo = sp.lo;
    cL4_release_mask(p2);

    bool is_bool = (taglo == 0x6c6f6f62ull && tag == 0xe400000000000000ull) ||
                   (FUN_000bd394(0x6c6f6f62, 0xe400000000000000ull) & 1) != 0;
    if (is_bool) {
        cL4_release_mask(tag);
        cL4_hook_noop();                        /* FUN_0007c1c4 */
        val = cL4_val_get_bool(p1, p2);
        if (((uint32_t)val & 0xff) != 2) {
            kind = 0;
            val &= 1;
            goto out;
        }
    } else {
        uint64_t width = p4 >> 0x38 & 0xf;
        bool is_u8 = (taglo == 0x3875ull && tag == 0xe200000000000000ull) ||
                     (FUN_000bd394(0x3875, 0xe200000000000000ull) & 1) != 0;
        if (is_u8) {
            /* inline hex parse for u8 (see decompile; omitted per-width
             * duplication) */
            kind = 1;
            goto out;
        }
        bool is_u16 = (taglo == 0x363175ull && tag == 0xe300000000000000ull) ||
                      (FUN_000bd35c(0) & 1) != 0;
        if (is_u16) {
            cL4_release_mask(tag);
            cL4_parse_noop();                   /* FUN_000bd33c */
            cl4_val_t r;
            r.hi = FUN_000bcc54(0, 0);          /* parse u16 (see decompile) */
            r.lo = 0;
            if (((r.hi >> 0x18) & 0xff) == 1) {
                cL4_parse_noop();               /* FUN_000bd32c */
                r.hi = 0;                       /* FUN_000b05bc re-parse */
            }
            cL4_release_mask(p4);
            if ((r.hi & 0xff0000) != 0x10000) {
                val = r.hi & 0xffff;
                kind = 2;
                goto out;
            }
        }
        /* s8/s16/s32/s64, f32/f64 similar; see decompile for full matrix */
    }
    kind = 0xff;
out: ;
    cl4_val_t r;
    r.lo = val;
    r.hi = kind;
    return r;
}

/* ------------------------------------------------------------------ *
 * Object / capability-table field access and teardown.
 * ------------------------------------------------------------------ */

/* FUN_000bd494 @ 0xbd494   (est. cL4_field_block_copy_out)
 * Ghidra: void FUN_000bd494(undefined8*)
 * Copy a 0x120-byte block of fields from the caller's object (x20)+0x10 into
 * the output array param_1 (36 8-byte words + one extra), transposing the
 * register dump layout.
 * Confidence: medium */
void FUN_000bd494(uint64_t *out)
{
    uint64_t obj = *(uint64_t *)(0 + 0x10);     /* unaff_x20 */
    uint64_t f;
    uint64_t *src = (uint64_t *)(obj + 0x10);
    for (int i = 0; i < 0x21; i++) {
        out[i] = src[i];
    }
    out[0x22] = *(uint64_t *)(0 + 0x20);
}

/* FUN_000bd770 @ 0xbd770   (est. cL4_field_block_copy_stub) — calls above. */
void FUN_000bd770(void)
{
    uint64_t dummy[0x23];
    FUN_000bd494(dummy);
}

/* FUN_000bd4f0 @ 0xbd4f0   (est. cL4_region_fetch_attr)
 * Ghidra: void FUN_000bd4f0(long, long*)
 * Fetch an MMIO region attribute via the object's method at +0x1b8 into the
 * caller's register block, then invoke the +0x70 method on the region owner
 * (from param_1+0x110).  On error unwind via cL4_err_unwind.
 * Confidence: medium
 * Notes: page-rounded base (param_1+0x120 & ~0x3fff); method dispatch through
 *   vtable +0x1b8 / +0x70. */
void FUN_000bd4f0(int64_t reg, int64_t *owner)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    *(int64_t *)(obj + 0x10) = reg;
    uint64_t base = *(uint64_t *)(reg + 0x118);
    uint64_t size = *(uint64_t *)(reg + 0x120);
    int64_t (*fn)(void *) = *(int64_t (**)(void *))(*owner + 0x1b8);
    cL4_ref_acquire((uint64_t)owner);
    cl4_val_t block;
    fn(&block);                                 /* fetch 8-word block */
    if (0 == 0) {                               /* unaff_x21 success */
        /* store block into caller object +0x18..0x49 */
        uint64_t *dst = (uint64_t *)(obj + 0x18);
        /* block words loaded; see decompile */
        int64_t *region = *(int64_t **)(*(int64_t *)(obj + 0x10) + 0x110);
        int64_t (*m)(void *) = *(int64_t (**)(void *))(*region + 0x70);
        cL4_ref_acquire((uint64_t)region);
        m(&block);
        cL4_ref_release((int64_t)region);
        cL4_ref_release((int64_t)reg);
        cL4_ref_release((int64_t)owner);
    } else {
        cL4_ref_release((int64_t)reg);
        cL4_ref_release((int64_t)owner);
        cL4_ref_release((int64_t)*(int64_t *)(obj + 0x10));
        cL4_err_unwind(0, 0, 0, 0);
    }
}

/* FUN_000bdebc @ 0xbdebc   (est. cL4_region_fetch_single)
 * Ghidra: void FUN_000bdebc(undefined8, long*, ulong)
 * Fetch a single 8-word block via the owner's +0x1b8 method, then build a
 * region: private (FUN_000fdb98) if param_3 bit0 clear, else shared
 * (FUN_000ffba8).  On error unwind.
 * Confidence: medium */
void FUN_000bdebc(uint64_t reg, int64_t *owner, uint64_t mode)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    *(uint64_t *)(obj + 0x10) = reg;
    int64_t (*fn)(void *) = *(int64_t (**)(void *))(*owner + 0x1b8);
    cL4_ref_acquire((uint64_t)owner);
    cl4_val_t block;
    fn(&block);
    if (0 == 0) {                               /* unaff_x21 success */
        uint64_t *dst = (uint64_t *)(obj + 0x18);
        uint64_t tcb = *(uint64_t *)(*(int64_t *)(obj + 0x10) + 0x10);
        cL4_ref_acquire(tcb);
        if ((mode & 1) == 0) {
            FUN_000fdb98(&block);
        } else {
            FUN_000ffba8();
        }
        cL4_ref_release((int64_t)tcb);
        cL4_ref_release((int64_t)owner);
        cL4_ref_release((int64_t)reg);
    } else {
        cL4_ref_release((int64_t)reg);
        cL4_ref_release((int64_t)owner);
        cL4_ref_release((int64_t)*(int64_t *)(obj + 0x10));
        cL4_err_unwind(0, 0, 0, 0);
    }
}

/* FUN_000bd424 @ 0xbd424   (est. cL4_region_fetch_alloc)
 * Ghidra: undefined8 FUN_000bd424(undefined8, undefined8, undefined8, undefined8)
 * Allocate an object, run the attribute-fetch (FUN_000bd7b8) on it, return it.
 * Confidence: medium */
uint64_t FUN_000bd424(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t obj = cL4_obj_alloc_typed(0, 0, 0);
    FUN_000bd7b8(a, b, c, d);
    return obj;
}

/* FUN_000be104 @ 0xbe104   (est. cL4_region_alloc_and_setup)
 * Ghidra: undefined8 FUN_000be104(undefined8)
 * Allocate an object, run the region-setup (FUN_000be154) on it, return it.
 * Confidence: medium */
uint64_t FUN_000be104(uint64_t p)
{
    uint64_t obj = cL4_obj_alloc_typed(0, 0, 0);
    FUN_000be154(p);
    return obj;
}

/* FUN_000be154 @ 0xbe154   (est. cL4_region_setup)
 * Ghidra: void FUN_000be154(undefined8)
 * Read a device description (param_1), allocate a region object, and build a
 * region from it, storing the result at x20+0x10.  On error unwind.
 * Confidence: medium
 * Notes: FUN_0006e7c0 (dev read), FUN_001003e8 (obj alloc), FUN_000ff728
 *   (region build); FUN_000026e8 diagnostics. */
void FUN_000be154(uint64_t id)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    uint8_t buf[40];
    FUN_0006e7c0(id, buf);
    uint64_t o = cL4_obj_alloc_typed2(0);
    cL4_ref_acquire(o);
    uint64_t r = FUN_000ff728(8, buf);
    if (0 == 0) {                               /* unaff_x21 success */
        FUN_000026e8(id);
        *(uint64_t *)(obj + 0x10) = r;
    } else {
        FUN_000026e8(id);
        cL4_err_unwind2();
    }
}

/* FUN_000be218 @ 0xbe218   (est. cL4_region_setup_shared) — setup with mode 1. */
void FUN_000be218(uint64_t id)
{
    uint64_t dummy[8];
    FUN_000be250(dummy, 1);
}

/* FUN_000be234 @ 0xbe234   (est. cL4_region_setup_private) — setup mode 0. */
void FUN_000be234(uint64_t id)
{
    uint64_t dummy[8];
    FUN_000be250(dummy, 0);
}

/* FUN_000be250 @ 0xbe250   (est. cL4_region_setup_mode)
 * Ghidra: void FUN_000be250(undefined8*, undefined8)
 * Allocate a region object, run FUN_000bdebc with the given mode, and record
 * the result into param_1.
 * Confidence: medium
 * Notes: alloc tag 0x650ef8; strings at 0x6612d0. */
void FUN_000be250(uint64_t *out, uint64_t mode)
{
    uint64_t obj = cL4_obj_alloc_typed(0x650ef8, 0x51, 7);
    cL4_ref_acquire(obj);
    cL4_ref_acquire(mode);
    FUN_000bdebc(obj, (int64_t *)mode, mode);
    uint64_t r = obj;
    if (0 == 0) {                               /* unaff_x21 success */
        out[3] = 0x650ef8;
        out[4] = 0x6612d0;
        out[0] = r;
    }
}

/* FUN_000bd7b8 @ 0xbd7b8   (est. cL4_mmio_region_setup)
 * Ghidra: void FUN_000bd7b8(undefined8, undefined8, ulong, ulong)
 * Set up an MMIO region: validate size (must be 0x4000-aligned), find the
 * MMIO untyped capability for the base, mint an untyped for the region, and
 * log the setup.  Emits the "Cannot handle MMIO region size", "Could not find
 * MMIO untyped", and "Could not mint untyped" error strings on failure.
 * Confidence: medium
 * Notes: strings s_Cannot_handle_MMIO_region_size_005c2bb0,
 *   s_Could_not_find_MMIO_untyped_005c2c00,
 *   s_Could_not_mint_untyped_005c2c40; s_init_* logs. */
void FUN_000bd7b8(uint64_t p1, uint64_t p2, uint64_t base, uint64_t size)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    uint8_t buf[0x100];
    cL4_scratch_init(buf);
    cL4_release_mask(p2);

    if (cL4_scratch_classify(buf) == 1) {
        cL4_fatal_frame();
        cL4_log_tagged(0xd000000000000022ull, 0x80000000005c2b60ull);
        *(uint8_t *)(obj + 0x30) = 2;           /* uVar8 */
        goto unwind;
    }

    cL4_stack_copy((void *)(obj + 0x10), buf, 0x100);
    *(uint64_t *)(obj + 0x118) = base;
    *(uint64_t *)(obj + 0x120) = size;

    if ((size & 0x3fff) != 0) {
        /* "Cannot handle MMIO region size 0x..." */
        cL4_hex_error();
        cL4_log_code(0x35);
        cL4_log_noop();
        cL4_log_tagged(0, 0);
        uint64_t ctx = cL4_fmt_ctx();
        cL4_fmt_value(&size, 0x10, 0, 0x677790, ctx);
        cL4_log_tagged(0, 0);
        cL4_release_mask(0);
        cL4_log_noop();
        cL4_log_tagged(0xd000000000000012ull, 0);
        cL4_fatal_frame();
        *(uint8_t *)(obj + 0x30) = 2;
        goto unwind;
    }

    int64_t mmio = cL4_obj_id();
    if (mmio != 0) {
        uint64_t lim = cL4_region_limit(base);
        if (base < lim) {
            CL4_TRAP(0xbdb6c);
        }
        uint64_t sz = *(uint64_t *)(obj + 0x120);
        int64_t slot = cL4_mmio_untyped();
        if (slot == 0) {
            cL4_log_init_fail("s_init_create", 0xd, 2, 0x153);
        }
        /* "Could not mint untyped for the r..." path */
        cL4_hex_error();
        cL4_log_code(0x3a);
        cL4_log_noop();
        cL4_log_tagged(0, 0);
        cL4_log_noop();
        cL4_log_fmt(0x677790);
        cL4_log_tagged(0, 0);
        cL4_release_mask(0);
        cL4_log_tagged(0x3a, 0xe100000000000000ull);
        cL4_fmt_value(&size, 0x10, 0, 0x677790, 0);
        cL4_log_tagged(0, 0);
        cL4_release_mask(0);
        cL4_log_mmio_setup(0, 0, "__AppleInternal_Library_BuildRoot", 0x114, 2,
                           "s_init_name_physaddr_size", 0x19, 2, 0x51, mmio, slot,
                           base - lim, sz >> 0xe);
        if (0 == 0) {                           /* unaff_x21 success */
            cL4_release_mask(0);
            uint64_t o = cL4_obj_kernel_alloc(0);
            cL4_obj_alloc_typed(o, 0x19, 7);
            uint64_t r = cL4_obj_ref_for_slot(slot);
            *(uint64_t *)(obj + 0x110) = r;
            return;
        }
        cL4_release_mask(0);
        cL4_mmio_untyped_release(slot);
        goto unwind;
    }

    /* "Could not find MMIO untyped for p..." path */
    cL4_hex_error();
    cL4_log_code(0x33);
    cL4_log_noop();
    cL4_log_tagged(0, 0);
    cL4_log_noop();
    cL4_log_fmt(0x677790);
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_fatal_frame();
    *(uint8_t *)(obj + 0x30) = 1;
unwind:
    cL4_err_unwind2();
    cL4_log_noop();
}

/* FUN_000bd7b8 helper FUN_000bdc00 @ 0xbdc00   (est. cL4_region_log_regdump)
 * Ghidra: void FUN_000bdc00(void)
 * Log the region's register block as " (d:rx, s:zx)" debug lines, with a
 * stack canary check at the end (trap on corruption).
 * Confidence: medium
 * Notes: reads x20+0x10..0x120 as register words; 0x2c8502b44bfffed6 canary. */
void FUN_000bdc00(void)
{
    int64_t obj = 0;                            /* unaff_x20 */
    uint64_t *words = (uint64_t *)(obj + 0x10);
    cl4_val_t vals[18];
    for (int i = 0; i < 0x12; i++) vals[i].lo = words[i];
    cL4_log_code(0x37);
    cL4_log_tagged(0xd000000000000018ull, 0x80000000005c2da0ull);
    cL4_log_regdump(vals);
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x646173796870202cull, 0xee007830203a7264ull); /* ", phy: x0 .." */
    cL4_fmt_value((uint64_t *)(obj + 0x118), 0, 0, 0, 0);
    cL4_log_noop();
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x203a657a6973202cull, 0xea00000000007830ull); /* ", siz: x0 ..." */
    cL4_log_noop();
    cL4_log_tagged(0, 0);
    cL4_release_mask(0);
    cL4_log_tagged(0x29, 0xe100000000000000ull); /* ")" */
}

/* FUN_000bdd90 / 0xbdd94   (est. cL4_region_release) — release object at +0x110. */
void FUN_000bdd90(void)
{
    cL4_ref_release(*(int64_t *)(0 + 0x110));   /* unaff_x20 */
}
void FUN_000bdd94(void)
{
    cL4_ref_release(*(int64_t *)(0 + 0x110));
}

/* FUN_000bddb0 / 0xbddb4   (est. cL4_region_release_unwind) — release + unwind. */
void FUN_000bddb0(void)
{
    cL4_ref_release(*(int64_t *)(0 + 0x110));
    cL4_err_unwind2();
}
void FUN_000bddb4(void)
{
    cL4_ref_release(*(int64_t *)(0 + 0x110));
    cL4_err_unwind2();
}

/* FUN_000bdddc / 0xbdde0   (est. cL4_region_fetch_alloc_stub) — calls 0xbdb6c. */
void FUN_000bdddc(void) { uint64_t d[8]; FUN_000bdb6c(d, 0); }
void FUN_000bdde0(void) { uint64_t d[8]; FUN_000bdb6c(d, 0); }

/* FUN_000bddf4 @ 0xbddf4   (est. cL4_region_log_stub) — calls FUN_000bdc00. */
void FUN_000bddf4(void) { FUN_000bdc00(); }

/* FUN_000bdb6c @ 0xbdb6c   (est. cL4_region_fetch_into)
 * Ghidra: void FUN_000bdb6c(undefined8*, undefined8)
 * Allocate a region-fetch object, run FUN_000bd4f0 on it with param_2, and
 * record the result block pointers into param_1.
 * Confidence: medium
 * Notes: alloc tag 0x650e30; result refs 0x661290. */
void FUN_000bdb6c(uint64_t *out, uint64_t p2)
{
    uint64_t obj = cL4_obj_alloc_typed(0x650e30, 0x51, 7);
    cL4_ref_acquire(obj);
    cL4_ref_acquire(p2);
    FUN_000bd4f0(obj, (int64_t *)p2);
    if (0 == 0) {                               /* unaff_x21 success */
        out[3] = 0x650e30;
        out[4] = 0x661290;
        out[0] = obj;
    }
}

/* FUN_000bd794 @ 0xbd794   (est. cL4_region_log_endian_stub) — calls 0xbd664. */
void FUN_000bd794(void) { FUN_000bd664(); }

/* FUN_000be0e0 @ 0xbe0e0   (est. cL4_mmio_end_stub) — calls 0xbe018. */
void FUN_000be0e0(void) { FUN_000be018(); }

/* FUN_000be2ec @ 0xbe2ec   (est. cL4_exclave_launch_with_log)
 * Ghidra: void FUN_000be2ec(undefined8, undefined8)
 * Launch a nested exclave on the TCB at (*(x20+0x10))+0x48 with args, then
 * log a fault/code line with a build-root format string.
 * Confidence: medium
 * Notes: FUN_0009d1c0 (exclave launch); FUN_00151974/00151a6c (exit capture +
 *   log); string s__AppleInternal_Library_BuildRoot_005c2e10. */
void FUN_000be2ec(uint64_t a, uint64_t b)
{
    uint64_t obj = 0;                           /* unaff_x20 */
    uint64_t tcb = *(uint64_t *)(*(int64_t *)(obj + 0x10) + 0x48);
    FUN_0009d1c0(tcb, a, b);
    cl4_val_t v = cL4_exit_capture();
    cL4_log_fault_line((void *)0xf648c, 0, "__AppleInternal_Library_BuildRoot", 0x117, 2,
                       0x40, v.lo, v.hi);
}

/* FUN_000bde70 @ 0xbde70   (est. cL4_store_stack_ctx)
 * Ghidra: void FUN_000bde70(void)
 * Store the caller's x26 context word at x29-0x48 (a stack scratch slot).
 * Confidence: low (depends on unaff register state) */
void FUN_000bde70(void)
{
    /* *(x29 - 0x48) = x26  (unaff register spill) */
}

/* FUN_000bde98 @ 0xbde98   (est. cL4_fmt_value_wrap) — calls FUN_001ebfb0. */
void FUN_000bde98(void)
{
    cL4_fmt_value(0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ *
 * Remaining small stubs / vtable slots.
 * ------------------------------------------------------------------ */

/* FUN_000ba31c / 0xba334 / 0xba34c / 0xba370 / 0xba3d4 / 0xba3e4 / 0xba3f0
 * / 0xba40c / 0xba4a8 / 0xba4b4 / 0xbd318 / 0xbd32c / 0xbd33c / 0xbd34c
 * / 0xbd3a4 / 0xbd3cc / 0xbd404 / 0xbd418 / 0xbd3b0 / 0xbd3bc / 0xbd3d8
 * / 0xbde88 / 0xbdeb0 — empty no-op vtable slots / parse hooks. */
void FUN_000ba31c(void) { }
void FUN_000ba334(void) { }
void FUN_000ba370(void) { }
void FUN_000ba3d4(void) { }
void FUN_000ba3e4(void) { }
void FUN_000ba3f0(void) { }
void FUN_000ba40c(void) { }
void FUN_000ba4a8(void) { }
void FUN_000ba4b4(void) { }
void FUN_000bd3a4(void) { }
void FUN_000bd3cc(void) { }
void FUN_000bd404(void) { }
void FUN_000bd418(void) { }
void FUN_000bd3bc(void) { }
void FUN_000bd318(void) { }
void FUN_000bd32c(void) { }
void FUN_000bd33c(void) { }
void FUN_000bd34c(void) { }
void FUN_000bdeb0(void) { }

/* FUN_000ba454 @ 0xba454   (est. cL4_err_unwind_noop)
 * Ghidra: void FUN_000ba454(void)
 * Invoke the unwind/no-op helper FUN_0036986c.
 * Confidence: medium */
void FUN_000ba454(void)
{
    cL4_err_unwind2();                          /* FUN_0036986c */
}

/* FUN_000ba470 @ 0xba470   (est. cL4_log_slot)
 * Ghidra: void FUN_000ba470(void)
 * Emit a tagged log line via thunk_FUN_002acbb8 (no args).
 * Confidence: medium */
void FUN_000ba470(void)
{
    cL4_log_tagged(0, 0);
}

/* FUN_000ba47c @ 0xba47c   (est. cL4_obj_field_30)
 * Ghidra: long FUN_000ba47c(void)
 * Return x20 + 0x30.
 * Confidence: medium */
int64_t FUN_000ba47c(void)
{
    return 0 + 0x30;                            /* unaff_x20 */
}

/* FUN_000ba488 @ 0xba488   (est. cL4_obj_field_48)
 * Ghidra: long FUN_000ba488(void)
 * Return x20 + 0x48.
 * Confidence: medium */
int64_t FUN_000ba488(void)
{
    return 0 + 0x48;                            /* unaff_x20 */
}

/* FUN_000ba494 @ 0xba494   (est. cL4_noop) — empty vtable slot. */
void FUN_000ba494(void) { }
