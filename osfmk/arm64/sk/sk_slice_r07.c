/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x3d2f10-0x3d952c) is the Swift standard-library + concurrency
 * runtime embedded in the kernel: Unicode scalar property tables, once
 * (pthread_once-style) primitives, and the async task / executor machinery.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_0038df24 @ 0x38df24 — build a formatted string into *out using the
 * format string in x1 (Swift String(format:) helper). */
extern void cL4_str_format(unsigned long *out, const char *fmt, ...);
/* FUN_004b9d68 @ 0x4b9d68 — take a retained string/object reference. */
extern void cL4_ref_take(unsigned long obj);
/* FUN_00012568 @ 0x12568 — release a Swift String / print a string to the
 * kernel log (the thunk pair). Used after formatting fatal messages. */
extern void cL4_thunk_print(unsigned long str);
/* FUN_003d2e80 @ 0x3d2e80 — continuation used by the generic print path. */
extern void cL4_print_dispatch(unsigned long a, unsigned long b,
                               unsigned long c, unsigned long d);
/* FUN_00054414 @ 0x54414 — zero-init a buffer of length in x1 (memset 0). */
extern void cL4_thunk_zero(unsigned long *buf, unsigned long len);
/* FUN_00054464 @ 0x54464 — store an immediate 64-bit value (global store). */
extern void cL4_thunk_store64(unsigned long value);
/* FUN_0005453c @ 0x5453c — store an immediate 64-bit value (variant thunk). */
extern void cL4_thunk_store64_b(unsigned long value);
/* FUN_0006037c @ 0x6037c — return a global word pointer. */
extern unsigned long *cL4_thunk_global(void);
/* FUN_0011ae84 @ 0x11ae84 — string parse helper returning a uint status. */
extern unsigned int cL4_str_parse_uint(unsigned long str, unsigned long *out);
/* FUN_00115080 @ 0x115080 — string parse helper returning a value. */
extern unsigned long cL4_str_parse(unsigned long str);
/* FUN_001180e0 @ 0x1180e0 — cnd_broadcast(&_DAT_006c0b40); 0 on success. */
extern int cL4_cnd_broadcast(unsigned long cnd);
/* FUN_0011812c @ 0x11812c — cnd_wait(&_DAT_006c0b40, &_DAT_006c0b30); 0 on success. */
extern int cL4_cnd_wait(unsigned long cnd, unsigned long mtx);
/* FUN_00118164 @ 0x118164 — mtx_lock(&_DAT_006c0b30); 0 on success. */
extern int cL4_mtx_lock(unsigned long mtx);
/* FUN_00118194 @ 0x118194 — mtx_unlock(&_DAT_006c0b30); 0 on success. */
extern int cL4_mtx_unlock(unsigned long mtx);
/* FUN_00118148 @ 0x118148 — mtx_init(&_DAT_006c0b30, type); 0 on success. */
extern int cL4_mtx_init(unsigned long mtx, int type);
/* FUN_001180fc @ 0x1180fc — cnd_init(&_DAT_006c0b40); 0 on success. */
extern int cL4_cnd_init(unsigned long cnd);
/* FUN_00060524 @ 0x60524 — return the current thread/task pointer. */
extern unsigned long cL4_current_thread(void);
/* FUN_000539c0 @ 0x539c0 — return nonzero if the two values are equal. */
extern int cL4_eq(unsigned long a, unsigned long b);
/* FUN_003a2578 @ 0x3a2578 — [[noreturn]] kernel fatal error with a string. */
extern void cL4_fatal(const char *msg);
/* FUN_001afa84 @ 0x1afa84 — [[noreturn]] Swift runtime fatal error with
 * source location (file/line/column) metadata. */
extern void cL4_runtime_fatal(unsigned long a, int b, int c, unsigned long d,
                              unsigned long e, const char *file, int line,
                              int col, ...);
/* FUN_0035ac70 @ 0x35ac70 — allocate/build a Swift String from a C literal. */
extern unsigned long cL4_str_from_cstr(const char *s);
/* FUN_003593c0 @ 0x3593c0 — return a static fatal-error message handle. */
extern unsigned long cL4_static_str(unsigned long a);
/* FUN_00350b54 @ 0x350b54 — allocate a fresh task/job record. */
extern unsigned long cL4_task_alloc(void);
/* FUN_0036a940 @ 0x36a940 — return the current executor/job storage. */
extern unsigned long cL4_executor_storage(void);
/* FUN_0036b270 @ 0x36b270 — retain an object/run-once barrier. */
extern void cL4_retain(unsigned long obj);
/* FUN_0036b118 @ 0x36b118 — release an object/run-once barrier. */
extern void cL4_release(unsigned long obj);
/* FUN_000f5e5c @ 0xf5e5c — destructor hook for a box/context at +0x18. */
extern void cL4_box_destroy(unsigned long box);
/* FUN_00100c04 @ 0x100c04 — clear/abort a task context. */
extern void cL4_task_abort(void);
/* FUN_002a4ab4 @ 0x2a4ab4 — stack-marker/metadata push (value in x0). */
extern void cL4_stack_mark(unsigned long kind);
/* FUN_002acbb8 @ 0x2acbb8 — emit a metadata/trace record (kind, payload). */
extern void cL4_trace_emit(unsigned long kind, unsigned long payload);
/* FUN_00268540 @ 0x268540 — runtime crash/abort path returning a frame. */
extern unsigned long cL4_crash_frame(unsigned long a, unsigned long b);
/* FUN_0040a694 @ 0x40a694 — deallocate an object frame. */
extern void cL4_frame_dealloc(unsigned long frame);
/* FUN_003a25d4 @ 0x3a25d4 — release a Swift string/object. */
extern void cL4_obj_release(unsigned long obj);
/* FUN_00409eXX-family async helpers: task creation / job dispatch. */
extern void cL4_async_enter(void);
extern void cL4_async_leave(void);
/* FUN_00350d04 @ 0x350d04 — begin an async job on the current executor. */
extern void cL4_async_begin(void);
extern void cL4_async_cleanup(void);

/* Popcount of a 64-bit word — used by the Unicode bitmap index helpers. */
static inline int cl4_popcount64(unsigned long w)
{
    return __builtin_popcountll(w);
}

/* ------------------------------------------------------------------ *
 * 0x3d2f10 - 0x3d2ffc : Swift print / fatal-error wrappers and the
 * standard-library float-string parse helpers.
 * ------------------------------------------------------------------ */

/* FUN_003d2f10 @ 0x3d2f10   (est. cL4_swift_uint_conv2)
 * Ghidra: void FUN_003d2f10(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Formats the message "%s, %s, %s" (three string arguments), takes a
 * reference, prints it via the thunk, then forwards to the generic print
 * dispatch. The extra argument (param_5) is the format-argument bundle.
 * Confidence: low
 * Notes: string ref s___,___,___@0x5db6b1; caller sk_region_sched names it
 *   "swift_uint_conv2" (a Swift UInt->String conversion entry). */
void FUN_003d2f10(unsigned long param_1, unsigned long param_2,
                  unsigned long param_3, unsigned long param_4,
                  unsigned long param_5)
{
    unsigned long local_48;
    cL4_str_format(&local_48, (const char *)0x5db6b1); /* "%s, %s, %s" */
    cL4_ref_take(param_5);
    cL4_thunk_print(local_48);
    cL4_print_dispatch(param_1, param_2, param_3, param_4);
}

/* FUN_003d2f9c @ 0x3d2f9c   (est. cL4_swift_unimplemented_fatal)
 * Ghidra: void FUN_003d2f9c(void)
 * Formats the string "%s: %s: Fatal error: Use of unimplemented initializer"
 * and raises it as a fatal error. Used when a Swift type's
 * init()/init(from:) is unimplemented.
 * Confidence: medium
 * Notes: string ref s__s__Fatal_error__Use_of_unimi@0x5db6bd. */
void FUN_003d2f9c(void)
{
    unsigned long local_28;
    cL4_str_format(&local_28,
                   (const char *)0x5db6bd); /* "%s: %s: Fatal error: Use of unimplemented..." */
    cL4_ref_take(*(unsigned int *)0);       /* in_stack_00000000 */
    cL4_thunk_print(local_28);
}

/* FUN_003d2ffc @ 0x3d2ffc   (est. cL4_once_guard_lazy)
 * Ghidra: void FUN_003d2ffc(void)  [globals overlap]
 * Lazy one-time global initialization guard. If the once-token at
 * 0x6adee0 is not already armed (>= 0), run the init closure. Then, based
 * on the flag byte at 0x6adec5, either clear the two global slots
 * (0x6adf10/0x6adf18) or leave them, and record the completed state in
 * 0x6adf20.
 * Confidence: low
 * Notes: _DAT_006adee0/_DAT_006adec5/_DAT_006adf10/_DAT_006adf18/
 *   _DAT_006adf20 are the Swift runtime global-init state. */
void FUN_003d2ffc(void)
{
    int done;
    if (-1 < (long)_DAT_006adee0) {
        FUN_003d3dd8(&DAT_006adee0, (void *)&DAT_003697c0, 0);
    }
    done = (DAT_006adec5 != 1);
    if (done) {
        unsigned long local_20 = 0, uStack_18 = 0;
        cL4_thunk_zero(&uStack_18, 8);
        cL4_thunk_zero(&local_20, 8);
        _DAT_006adf10 = uStack_18;
        _DAT_006adf18 = local_20;
    } else {
        _DAT_006adf10 = 0;
        _DAT_006adf18 = 0;
        _DAT_006adf20 = 0;
    }
    _DAT_006adf20 = (_DAT_006adf20 & 0xffffffffffffff00) | (unsigned long)!done;
}

/* FUN_003d3130 @ 0x3d3130   (est. cL4_str_to_int_parse)
 * Ghidra: long FUN_003d3130(long, undefined4*)
 * Parse an integer from the string in param_1. If the string is a plain
 * number (FUN_003d3200 returns 0, i.e. not nan/inf), clear a scratch word
 * and parse normally, storing the status. Otherwise the value is computed
 * from the string length and a "nan"/"inf" sentinel is produced.
 * Confidence: low
 * Notes: FUN_003d3200 detects the literal tokens "nan"/"snan"/"inf". */
long FUN_003d3130(long param_1, unsigned int *param_2)
{
    int iVar1;
    long local_28;
    iVar1 = FUN_003d3200((unsigned char *)param_1);
    if (iVar1 == 0) {
        local_28 = 0;
        *cL4_thunk_global() = 0;
        *param_2 = cL4_str_parse_uint(param_1, &local_28);
    } else {
        *param_2 = 0x7fa00000;
        local_28 = cL4_str_parse(param_1);
        local_28 = param_1 + local_28;
    }
    return local_28;
}

/* FUN_003d31d8 @ 0x3d31d8   (est. cL4_swift_once_store_guard)
 * Ghidra: void FUN_003d31d8(void)
 * Store the canonical once-guard token value 0xb4000769f84206c9 into the
 * global slot handled by the thunk (a Swift lazy-global once marker).
 * Confidence: low
 * Notes: mirror of FUN_003d31e8 which stores the same constant. */
void FUN_003d31d8(void)
{
    cL4_thunk_store64(0xb4000769f84206c9);
}

/* FUN_003d31e8 @ 0x3d31e8   (est. cL4_swift_once_store_guard_b)
 * Ghidra: void FUN_003d31e8(void)
 * Same once-guard store as FUN_003d31d8 but through the alternative store
 * thunk (0x5453c); returns nothing.
 * Confidence: low */
void FUN_003d31e8(void)
{
    cL4_thunk_store64_b(0xb4000769f84206c9);
}

/* FUN_003d31f8 @ 0x3d31f8   (est. cL4_nop_identity)
 * Ghidra: undefined8 FUN_003d31f8(void)
 * Identity/no-op returning zero.
 * Confidence: high
 * Notes: trivial body. */
unsigned long FUN_003d31f8(void)
{
    return 0;
}

/* FUN_003d3200 @ 0x3d3200   (est. cL4_str_is_nan_inf_token)
 * Ghidra: undefined8 FUN_003d3200(byte*)
 * Return 1 if the NUL-terminated string at param_1 is the token "nan"
 * (optionally signed, case-insensitive; also accepts "snan" prefix),
 * otherwise 0. Used by the float/double parser to recognise
 * NaN/Infinity literals.
 * Confidence: high
 * Notes: matches the Swift Float/Double init(from: String) NaN detection. */
unsigned long FUN_003d3200(unsigned char *param_1)
{
    unsigned char bVar1;
    bVar1 = *param_1;
    if (bVar1 == 0x2d || bVar1 == 0x2b) {   /* '-' or '+' */
        param_1++;
        bVar1 = *param_1;
    }
    if ((((bVar1 | 0x20) == 0x73) &&        /* 's'/'S' */
         ((param_1[1] | 0x20) == 0x6e)) &&  /* 'n'/'N' */
        (((param_1[2] | 0x20) == 0x61) &&   /* 'a'/'A' */
         (param_1[3] == 0x61 && param_1[4] == 0))) {
        /* "snan" (signaling NaN) */
        return 1;
    }
    return 0;
}

/* FUN_003d326c @ 0x3d326c   (est. cL4_unicode_bitmap_index)
 * Ghidra: uint FUN_003d326c(int, long, long, long, long)
 * Core two-level bitmap index lookup shared by the Unicode scalar property
 * tables. For each of the `param_2` ranges, mixes the 16-bit range value
 * with a MurmurHash-style constant through the level-0 bitmap (param_3),
 * counts set bits (popcount) in the bitmap to derive a cumulative offset,
 * then indexes the level-1 table (param_4) and returns the populated
 * property value. Returns 0 when the range is unmapped.
 * Confidence: medium
 * Notes: this is the Swift standard library's Unicode property lookup;
 *   the constants 0x1b873593 / 0xe6546b64 are MurmurHash3 mix steps. */
unsigned int FUN_003d326c(int param_1, long param_2, long param_3,
                          long param_4, long param_5)
{
    unsigned int uVar1, uVar6, uVar8;
    unsigned short uVar2;
    unsigned long uVar3, uVar7, uVar9, lVar4, lVar5;
    char c;
    long i;

    if (param_2 != 0) {
        lVar5 = 0;
        do {
            lVar4 = *(long *)(param_3 + lVar5 * 8);
            uVar2 = *(unsigned short *)(param_5 + lVar5 * 2);
            uVar1 = (unsigned int)(param_1 * 0x16a88000u |
                    (unsigned int)(param_1 * -0x3361d2afu) >> 0x11) * 0x1b873593u ^
                    (unsigned int)lVar5;
            uVar1 = ((unsigned int)uVar2 * 0x16a88000u |
                     (unsigned int)uVar2 * -0x3361d2afu >> 0x11) * 0x1b873593u ^
                    (uVar1 >> 0x13 | uVar1 << 0xd) * 5u + 0xe6546b64u;
            uVar1 = (uVar1 >> 0x13 | uVar1 << 0xd) * 5u + 0xe6546b64u;
            uVar1 = (uVar1 ^ uVar1 >> 0x10 ^ 8) * -0x7a143595u;
            uVar1 = (uVar1 ^ uVar1 >> 0xd) * -0x3d4d51cbu;
            uVar1 = uVar1 ^ uVar1 >> 0x10;
            uVar6 = 0;
            uVar8 = (unsigned int)uVar2;
            if (uVar8 != 0) {
                uVar6 = uVar1 / uVar8;
            }
            uVar1 = uVar1 - uVar6 * uVar8;
            uVar3 = (unsigned long)(uVar1 >> 6);
            uVar9 = *(unsigned long *)(lVar4 + uVar3 * 8);
            if ((uVar9 >> (uVar1 & 0x3f) & 1) != 0) {
                uVar6 = (unsigned int)*(unsigned short *)
                        (*(long *)(param_4 + lVar5 * 8) + (unsigned long)(uVar1 >> 9) * 2);
                for (uVar7 = uVar3 & 0x3f8; uVar3 != uVar7; uVar7++) {
                    unsigned long v = *(unsigned long *)(lVar4 + uVar7 * 8);
                    uVar6 += (unsigned int)cl4_popcount64(v);
                }
                lVar5 = uVar9 << (unsigned long)(-(uVar1 & 0x3f) & 0x3f);
                if ((uVar1 & 0x3f) != 0) {
                    uVar6 += (unsigned int)cl4_popcount64(lVar5);
                }
                return uVar6 & 0xffff;
            }
            lVar5++;
        } while (param_2 != lVar5);
    }
    return 0;
}

/* FUN_003d3398 @ 0x3d3398   (est. cL4_unicode_range_index)
 * Ghidra: long FUN_003d3398(uint, long*, long)
 * Second-level Unicode property table lookup. Given a scalar value
 * param_1, a level-0 bitmap (param_2) and a level-1 offset table
 * (param_3), navigate the two-level radix (0x4400-byte / 0x110 sub-blocks)
 * via popcount accumulation, and return the byte offset into the property
 * table. Returns 0x7fffffffffffffff (the canonical "not found" sentinel)
 * when the value is unmapped.
 * Confidence: medium
 * Notes: 0x7fffffffffffffff sentinel is checked by every caller. */
long FUN_003d3398(unsigned int param_1, long *param_2, long param_3)
{
    unsigned short uVar1;
    unsigned long uVar2, uVar5, uVar8;
    long lVar3, lVar4, lVar6;
    int iVar7;

    uVar2 = param_1;
    lVar3 = *param_2;
    if (uVar2 / 0x4400 <= (unsigned long)(lVar3 - 1)) {
        uVar8 = uVar2 / 0x110 & 0x3f;
        if (((unsigned long)param_2[uVar2 / 0x4400 + 1] >> uVar8 & 1) != 0) {
            uVar1 = *(unsigned short *)(param_3 + (uVar2 / 0x4400) * 2);
            uVar5 = uVar1;
            iVar7 = (int)uVar8;
            if (iVar7 != 0) {
                lVar6 = param_2[uVar2 / 0x4400 + 1] << ((unsigned long)(unsigned int)-iVar7 & 0x3f);
                uVar5 = (unsigned long)((unsigned int)uVar1 +
                                        (unsigned int)cl4_popcount64(lVar6));
            }
            lVar6 = (uVar5 & 0xffff) * 4 + (uVar5 & 0xffff);
            param_1 = param_1 % 0x110;
            if (((unsigned long)param_2[lVar3 + lVar6 + (unsigned long)(param_1 >> 6) + 1]
                  >> (param_1 & 0x3f) & 1) != 0) {
                uVar1 = *(unsigned short *)(param_3 + lVar3 * 2 + lVar6 * 2 +
                                            (unsigned long)(param_1 >> 6) * 2);
                lVar4 = param_2[lVar3 + lVar6 + (unsigned long)(param_1 >> 6) + 1] <<
                        ((unsigned long)-(param_1 & 0x3f) & 0x3f);
                if ((param_1 & 0x3f) != 0) {
                    uVar1 = (unsigned short)(uVar1 +
                                             (unsigned short)cl4_popcount64(lVar4));
                }
                return ((unsigned long)param_2[lVar3 + lVar6 + 5] >> 0x10) +
                       (unsigned long)uVar1;
            }
        }
    }
    return 0x7fffffffffffffff;
}

/* ------------------------------------------------------------------ *
 * 0x3d3470 - 0x3d3c88 : Unicode scalar property getters built on the
 * two-level index (general category, binary properties, case mapping).
 * ------------------------------------------------------------------ */

/* FUN_003d3470 @ 0x3d3470   (est. cL4_unicode_prop_is_valid_scalar)
 * Ghidra: bool FUN_003d3470(undefined8)
 * Return true if param_1 is a defined Unicode scalar value (>= 0xA9 and
 * present in the property table). 
 * Confidence: medium
 * Notes: DAT_004f2a70/DAT_004f2f18 are the first property table. */
bool FUN_003d3470(unsigned long param_1)
{
    long lVar1;
    if ((unsigned int)param_1 < 0xa9) {
        return false;
    }
    lVar1 = FUN_003d3398(param_1, (long *)&DAT_004f2a70, (long)&DAT_004f2f18);
    return lVar1 != 0x7fffffffffffffff;
}

/* FUN_003d34b8 @ 0x3d34b8   (est. cL4_unicode_general_category)
 * Ghidra: uint FUN_003d34b8(uint)
 * Binary search the sorted general-category range table at 0x4f3040 and
 * return the 5-bit general category code (bits 29..) for the scalar.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 8-bit count, 5-bit category. */
unsigned int FUN_003d34b8(unsigned int param_1)
{
    unsigned int uVar1, uVar2, uVar3;
    uVar3 = 1;
    do {
        uVar1 = *(unsigned int *)((long)(int)uVar3 * 4 + 0x4f3040);
        if (param_1 < (uVar1 & 0x1fffff)) {
            uVar3 <<= 1;
        } else {
            uVar2 = 0x1ff;
            if (uVar1 >> 0x1d != 5) {
                uVar2 = 0xff;
            }
            if (param_1 <= (uVar2 & uVar1 >> 0x15) + (uVar1 & 0x1fffff)) {
                return uVar1 >> 0x1d;
            }
            uVar3 = uVar3 << 1 | 1;
        }
        if (0x23d < (int)uVar3) {
            return 0xff;
        }
    } while (1);
}

/* FUN_003d351c @ 0x3d351c   (est. cL4_unicode_prop_binary_1)
 * Ghidra: bool FUN_003d351c(undefined8)
 * Return true if the scalar is present in the binary property table
 * (DAT_004f3938/DAT_004f3c88) — e.g. "Alphabetic".
 * Confidence: medium */
bool FUN_003d351c(unsigned long param_1)
{
    long lVar1;
    lVar1 = FUN_003d3398(param_1, (long *)&DAT_004f3938, (long)&DAT_004f3c88);
    return lVar1 != 0x7fffffffffffffff;
}

/* FUN_003d3550 @ 0x3d3550   (est. cL4_unicode_case_mapping16)
 * Ghidra: undefined2 FUN_003d3550(undefined8)
 * For a scalar > 0xBF, look it up and return a 16-bit case-mapping value
 * from the table indexed by the property byte.
 * Confidence: low
 * Notes: DAT_004f3d60/DAT_004f4b10/DAT_004f4e7a/DAT_004f5ab0. */
unsigned short FUN_003d3550(unsigned long param_1)
{
    long lVar1;
    if (0xbf < (unsigned int)param_1) {
        lVar1 = FUN_003d3398(param_1, (long *)&DAT_004f3d60, (long)&DAT_004f4b10);
        if (lVar1 != 0x7fffffffffffffff) {
            return *(unsigned short *)(&DAT_004f5ab0 +
                (unsigned long)(unsigned char)(&DAT_004f4e7a)[lVar1] * 2);
        }
    }
    return 0;
}

/* FUN_003d35b0 @ 0x3d35b0   (est. cL4_unicode_prop_word32)
 * Ghidra: undefined4 FUN_003d35b0(undefined8)
 * Index a 32-bit property value for the scalar from the 12-range table.
 * Confidence: low
 * Notes: FUN_003d326c(…,0xc,0x67d130,0x67d190,&DAT_004f80d2). */
unsigned int FUN_003d35b0(unsigned long param_1)
{
    long lVar1;
    lVar1 = FUN_003d326c(param_1, 0xc, (long)0x67d130, (long)0x67d190,
                         (long)&DAT_004f80d2);
    return *(unsigned int *)(&DAT_004f80ec + lVar1 * 4);
}

/* FUN_003d35f0 @ 0x3d35f0   (est. cL4_unicode_combining_class)
 * Ghidra: int FUN_003d35f0(uint, undefined8)
 * Search a 4-entry sorted table (0x67d1f0/0x67d210) via the index helper
 * for the given class value and return the mapped combining class
 * (0x3fff field) plus the scalar, or -1 if not present.
 * Confidence: low
 * Notes: binary search over puVar5 entries; -1 sentinel on miss. */
int FUN_003d35f0(unsigned int param_1, unsigned long param_2)
{
    unsigned int uVar1, uVar2, uVar3, uVar6, uVar7;
    unsigned int *puVar5;
    long lVar4;

    lVar4 = FUN_003d326c(param_2, 4, (long)0x67d1f0, (long)0x67d210,
                         (long)&DAT_004fa170);
    puVar5 = *(unsigned int **)(lVar4 * 8 + 0x67d230);
    uVar6 = *puVar5;
    if (((unsigned int)param_2 == (uVar6 & 0x1fffff)) &&
        (uVar6 = (uVar6 >> 0x15) - 1, uVar6 != 0)) {
        uVar7 = 1;
        do {
            uVar1 = uVar7 + (uVar6 - uVar7 >> 1);
            uVar3 = puVar5[uVar1];
            uVar2 = uVar3 & 0x1ffff;
            if (param_1 == uVar2) {
                uVar7 = uVar3 >> 0x11 & 0x3fff;
                uVar6 = (int)(uVar3) < 0 ? (unsigned int)-(int)uVar7 : uVar7;
                return (int)(uVar6 + param_1);
            }
            uVar3 = uVar1 - 1;
            if (uVar2 <= param_1) {
                uVar3 = uVar6;
            }
            if (uVar2 < param_1) {
                uVar7 = uVar1 + 1;
                uVar3 = uVar6;
            }
            uVar6 = uVar3;
        } while (uVar7 <= uVar6);
    }
    return -1;
}

/* FUN_003d36b0 @ 0x3d36b0   (est. cL4_unicode_uppercase_mapping)
 * Ghidra: undefined8 FUN_003d36b0(uint)
 * Binary search the case-conversion range table (0x4fb4f8) and return the
 * mapped uppercase value for the scalar, or 0 if unmapped.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 21-bit count<<... */
unsigned long FUN_003d36b0(unsigned int param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned int uVar2, uVar6;

    iVar4 = 0;
    iVar5 = 0x13d4;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        if (iVar1 == 0x13d4) {
            uVar6 = 0x10ffff;
        } else {
            uVar6 = (*(unsigned int *)(&DAT_004fb4fc + (long)iVar1 * 4) & 0x1fffff) - 1;
        }
        uVar2 = *(unsigned int *)(&DAT_004fb4f8 + (long)iVar1 * 4) & 0x1fffff;
        if (uVar2 <= param_1 && param_1 <= uVar6) {
            return *(unsigned long *)(&DAT_00500450 +
                (unsigned long)(*(unsigned int *)(&DAT_004fb4f8 + (long)iVar1 * 4) >> 0x15) * 8);
        }
        iVar3 = iVar1 - 1;
        if (uVar2 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar6 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0;
}

/* FUN_003d3740 @ 0x3d3740   (est. cL4_unicode_bidi_class)
 * Ghidra: uint FUN_003d3740(uint)
 * Binary search the sorted table at 0x500a58 and return the 5-bit bidi /
 * general-property class for the scalar; 0xff on miss.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 8-bit count, 5-bit class. */
unsigned int FUN_003d3740(unsigned int param_1)
{
    int iVar2, iVar4, iVar6, iVar7;
    unsigned int uVar1, uVar3, uVar5;

    iVar6 = 0;
    iVar7 = 0x105;
    do {
        iVar2 = iVar6 + ((unsigned int)(iVar7 - iVar6) >> 1);
        uVar5 = *(unsigned int *)(&DAT_00500a58 + (long)iVar2 * 4);
        uVar3 = uVar5 & 0x1fffff;
        uVar1 = uVar3 + (uVar5 >> 0x15 & 0xff);
        if (uVar3 <= param_1 && param_1 <= uVar1) {
            return uVar5 >> 0x1d;
        }
        iVar4 = iVar2 - 1;
        if (uVar3 <= param_1) {
            iVar4 = iVar7;
        }
        if (uVar1 < param_1) {
            iVar6 = iVar2 + 1;
            iVar4 = iVar7;
        }
        iVar7 = iVar4;
    } while (iVar6 <= iVar7);
    return 0xff;
}

/* FUN_003d37a4 @ 0x3d37a4   (est. cL4_unicode_pair16)
 * Ghidra: undefined1[16] FUN_003d37a4(undefined8)
 * Return a 16-byte pair whose low 8 bytes hold a mapped 64-bit value for
 * the scalar (from DAT_00501670 via the 11-range index), high 8 bytes 0.
 * Confidence: low
 * Notes: FUN_003d326c(…,0xb,0x67d470,0x67d4c8,&DAT_00500e70). */
cL4_w16_t FUN_003d37a4(unsigned long param_1)
{
    long lVar1;
    cL4_w16_t r;
    lVar1 = FUN_003d326c(param_1, 0xb, (long)0x67d470, (long)0x67d4c8,
                         (long)&DAT_00500e70);
    r.lo = *(unsigned long *)(&DAT_00501670 +
        (unsigned long)(unsigned char)(&DAT_00500e86)[lVar1] * 8);
    r.hi = 0;
    return r;
}

/* FUN_003d37f0 @ 0x3d37f0   (est. cL4_unicode_64bit_prop)
 * Ghidra: undefined8 FUN_003d37f0(undefined8)
 * Return the 64-bit property value for the scalar from the table at
 * 0x67d520, or 0 if unmapped.
 * Confidence: medium
 * Notes: DAT_00501af0/DAT_00501ed0 are the index tables. */
unsigned long FUN_003d37f0(unsigned long param_1)
{
    long lVar1;
    unsigned long uVar2;
    lVar1 = FUN_003d3398(param_1, (long *)&DAT_00501af0, (long)&DAT_00501ed0);
    if (lVar1 == 0x7fffffffffffffff) {
        uVar2 = 0;
    } else {
        uVar2 = *(unsigned long *)(lVar1 * 8 + 0x67d520);
    }
    return uVar2;
}

/* FUN_003d3838 @ 0x3d3838   (est. cL4_unicode_general_category_value)
 * Ghidra: undefined4 FUN_003d3838(undefined8, int)
 * Look up the scalar in the category table (0x501fc8/0x5024e8) and return
 * the category value, selecting a byte lane by param_2 (0=lo, 1=mid,
 * 2=hi). Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_00502630 holds packed category bytes. */
unsigned int FUN_003d3838(unsigned long param_1, int param_2)
{
    long lVar1;
    unsigned int uVar2;

    lVar1 = FUN_003d3398(param_1, (long *)&DAT_00501fc8, (long)&DAT_005024e8);
    if (lVar1 != 0x7fffffffffffffff) {
        uVar2 = *(unsigned int *)(&DAT_00502630 + lVar1 * 4);
        if (param_2 != 0) {
            if (param_2 == 2) {
                uVar2 >>= 0x10;
            } else if (param_2 == 1) {
                uVar2 >>= 8;
            } else {
                return 0;
            }
        }
        if ((uVar2 & 0xff) != 0xff) {
            return *(unsigned int *)(&DAT_005054e4 + (unsigned long)(uVar2 & 0xff) * 4);
        }
    }
    return 0;
}

/* FUN_003d38c4 @ 0x3d38c4   (est. cL4_unicode_decomposition_string)
 * Ghidra: byte* FUN_003d38c4(undefined8, int, ulong*)
 * Look up the scalar in the decomposition table and return a pointer into
 * the decomposition string storage (0x505a3f); for param_2==1 store the
 * single-byte length, for param_2==2 advance past a two-byte length prefix,
 * for 0 keep the whole string. Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_005057b0/DAT_00505918 index; 0x505a3f string pool. */
unsigned char *FUN_003d38c4(unsigned long param_1, int param_2, unsigned long *param_3)
{
    unsigned char *pbVar1, *pbVar3, *pbVar5;
    long lVar2;
    unsigned long uVar4;

    lVar2 = FUN_003d3398(param_1, (long *)&DAT_005057b0, (long)&DAT_00505918);
    if (lVar2 == 0x7fffffffffffffff) {
        pbVar3 = 0;
    } else {
        pbVar3 = (unsigned char *)((unsigned long)*(unsigned short *)
                                   (&DAT_00505970 + lVar2 * 2) + 0x505a3f);
        uVar4 = (unsigned char)(&DAT_00505a3e)[*(unsigned short *)(&DAT_00505970 + lVar2 * 2)];
        pbVar1 = pbVar3 + uVar4;
        pbVar5 = pbVar1 + 1;
        if (param_2 == 2) {
            pbVar3 = pbVar5 + *pbVar1 + 1;
            uVar4 = (unsigned long)pbVar5[*pbVar1];
        } else if (param_2 == 1) {
            *param_3 = (unsigned long)*pbVar1;
            return pbVar5;
        } else if (param_2 != 0) {
            return 0;
        }
        *param_3 = uVar4;
    }
    return pbVar3;
}

/* FUN_003d3964 @ 0x3d3964   (est. cL4_unicode_lowercase_mapping)
 * Ghidra: long FUN_003d3964(ulong, long, long)
 * Produce the lowercase mapping of scalar param_1 into the output buffer
 * param_2, copying at most param_3 bytes. Walks the per-scalar case-mapping
 * records (0x532a14) writing mapped bytes (spaces separating runs), stopping
 * when the buffer limit or record end is reached.
 * Confidence: low
 * Notes: DAT_00505e12/DAT_0050a214 index; DAT_0056adec/DAT_005781a0
 *   mapping byte tables. */
long FUN_003d3964(unsigned long param_1, long param_2, long param_3)
{
    unsigned int uVar1, uVar12, uVar2, iVar3;
    unsigned long uVar4;
    long lVar5, lVar7;
    unsigned char bVar6;
    unsigned char *pbVar8, *pbVar9;
    int iVar10, iVar13, iVar14;
    int *piVar11;

    if (*(unsigned short *)(&DAT_00505e12 + (param_1 >> 7 & 0x1ffffff) * 2) != 0xffff) {
        uVar12 = (unsigned int)param_1 & 0x7f |
                 (unsigned int)*(unsigned short *)(&DAT_00505e12 +
                    (param_1 >> 7 & 0x1ffffff) * 2) << 7;
        iVar3 = *(int *)(&DAT_0050a214 + (unsigned long)uVar12 * 4);
        if (((unsigned int)param_1 == 0x20) || (iVar3 != 0)) {
            if (uVar12 == 0xa1ff) {
                iVar10 = 0x383d6;
            } else {
                piVar11 = (int *)(&DAT_0050a214 + (unsigned long)uVar12 * 4);
                do {
                    piVar11++;
                    iVar10 = *piVar11;
                } while (iVar10 == 0);
            }
            if (iVar10 == iVar3) {
                return -1;
            }
            uVar12 = 0;
            iVar13 = 0;
            do {
                uVar4 = (unsigned char)(&DAT_00532a14)[uVar12 + iVar3];
                if (uVar4 == 0xff) {
                    uVar1 = iVar3 + 1 + uVar12;
                    uVar2 = uVar12 + iVar3 + 2;
                    uVar12 += 2;
                    uVar4 = (unsigned long)((unsigned char)(&DAT_00532a14)[uVar2] << 8 |
                                            (unsigned char)(&DAT_00532a14)[uVar1]);
                }
                bVar6 = (&DAT_005781a0)[*(unsigned int *)(&DAT_0056adec + uVar4 * 4)];
                iVar14 = iVar13;
                if ((char)bVar6 >= 0) {
                    lVar5 = (param_3 <= iVar13) ? (long)iVar13 : param_3;
                    lVar7 = lVar5 - iVar13;
                    pbVar9 = &DAT_005781a0 + *(unsigned int *)(&DAT_0056adec + uVar4 * 4);
                    pbVar8 = (unsigned char *)(param_2 + iVar13);
                    do {
                        pbVar9++;
                        if (lVar7 == 0) {
                            return lVar5;
                        }
                        *pbVar8 = bVar6;
                        bVar6 = *pbVar9;
                        lVar7--;
                        iVar14++;
                        pbVar8++;
                    } while ((char)bVar6 >= 0);
                }
                lVar5 = (long)iVar14;
                if (param_3 <= iVar14) {
                    return lVar5;
                }
                lVar7 = lVar5 + 1;
                *(unsigned char *)(param_2 + lVar5) = bVar6 & 0x7f;
                if (param_3 <= lVar7) {
                    return lVar7;
                }
                iVar13 = iVar14 + 2;
                *(unsigned char *)(param_2 + lVar7) = 0x20;   /* space separator */
                uVar12++;
            } while (uVar12 < (unsigned int)(iVar10 - iVar3));
            return (long)(iVar14 + 1);
        }
    }
    return 0;
}

/* FUN_003d3ac0 @ 0x3d3ac0   (est. cL4_unicode_decompose_canonical16)
 * Ghidra: undefined2 FUN_003d3ac0(ulong)
 * Binary search the canonical-decomposition range table (0x58cb70) and
 * return the 16-bit decomposition code for the scalar; 0xffff on miss.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 32-bit count, 8-bit code index. */
unsigned short FUN_003d3ac0(unsigned long param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned long uVar2, uVar6, uVar7;

    iVar4 = 0;
    param_1 &= 0xffffffff;
    iVar5 = 0x6fb;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        uVar6 = *(unsigned long *)(&DAT_0058cb70 + (long)iVar1 * 8);
        uVar7 = uVar6 & 0x1fffff;
        uVar2 = uVar7 + (uVar6 >> 0x20);
        if (uVar7 <= param_1 && param_1 <= uVar2) {
            return *(unsigned short *)(&DAT_00590350 + (uVar6 >> 0x15 & 0xff) * 2);
        }
        iVar3 = iVar1 - 1;
        if (uVar7 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar2 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0xffff;
}

/* FUN_003d3b30 @ 0x3d3b30   (est. cL4_unicode_compat_mapping)
 * Ghidra: uint FUN_003d3b30(ulong)
 * Binary search the compatibility-decomposition table (0x590388) and
 * return the 21-bit mapping offset (bits 0x15..); 0xff on miss.
 * Confidence: medium */
unsigned int FUN_003d3b30(unsigned long param_1)
{
    int iVar1, iVar3, iVar4, iVar6;
    unsigned int uVar5;
    unsigned long uVar2, uVar7, uVar8;

    iVar4 = 0;
    param_1 &= 0xffffffff;
    iVar6 = 0x102f;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar6 - iVar4) >> 1);
        uVar7 = *(unsigned long *)(&DAT_00590388 + (long)iVar1 * 8);
        uVar8 = uVar7 & 0x1fffff;
        uVar2 = uVar8 + (uVar7 >> 0x20);
        if (uVar8 <= param_1 && param_1 <= uVar2) {
            uVar5 = (unsigned int)(uVar7 >> 0x15);
            return uVar5 & 0xff;
        }
        iVar3 = iVar1 - 1;
        if (uVar8 <= param_1) {
            iVar3 = iVar6;
        }
        if (uVar2 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar6;
        }
        iVar6 = iVar3;
    } while (iVar4 <= iVar6);
    return 0xff;
}

/* FUN_003d3b98 @ 0x3d3b98   (est. cL4_unicode_case_fold_code)
 * Ghidra: uint FUN_003d3b98(uint)
 * Binary search the case-folding table (0x598508) and return the folding
 * code (bits 0x15..); 0xff on miss.
 * Confidence: medium */
unsigned int FUN_003d3b98(unsigned int param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned int uVar2, uVar6;

    iVar4 = 0;
    iVar5 = 0x6b5;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        if (iVar1 == 0x6b5) {
            uVar6 = 0x10ffff;
        } else {
            uVar6 = (*(unsigned int *)(&DAT_0059850c + (long)iVar1 * 4) & 0x1fffff) - 1;
        }
        uVar2 = *(unsigned int *)(&DAT_00598508 + (long)iVar1 * 4) & 0x1fffff;
        if (uVar2 <= param_1 && param_1 <= uVar6) {
            uVar6 = *(unsigned int *)(&DAT_00598508 + (long)iVar1 * 4) >> 0x15;
            return uVar6 & 0xff;
        }
        iVar3 = iVar1 - 1;
        if (uVar2 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar6 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0xff;
}

/* FUN_003d3c1c @ 0x3d3c1c   (est. cL4_unicode_script_info)
 * Ghidra: long FUN_003d3c1c(undefined8, byte*)
 * Look up the scalar in the script table and return (a) the script byte in
 * *param_2 (bits 0xb..) and (b) an offset into the script-name string pool
 * (0x59ad42). Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_00599fe0/DAT_0059a668 index; DAT_0059a808 code table. */
long FUN_003d3c1c(unsigned long param_1, unsigned char *param_2)
{
    unsigned short uVar1;
    long lVar2;

    lVar2 = FUN_003d3398(param_1, (long *)&DAT_00599fe0, (long)&DAT_0059a668);
    if (lVar2 == 0x7fffffffffffffff) {
        lVar2 = 0;
    } else {
        uVar1 = *(unsigned short *)(&DAT_0059a808 + lVar2 * 2);
        *param_2 = (unsigned char)(uVar1 >> 0xb);
        lVar2 = ((unsigned long)uVar1 & 0x7ff) + 0x59ad42;
    }
    return lVar2;
}

/* FUN_003d3c88 @ 0x3d3c88   (est. cL4_unicode_decompose_multi)
 * Ghidra: void FUN_003d3c88(ulong, int*)
 * Decompose the scalar into its canonical decomposition, writing the
 * mapped scalar values into the int array param_2 (one entry per code
 * point, via the 0x11-bit packing in the decomposition table). A single
 * scalar that is its own decomposition writes itself.
 * Confidence: low
 * Notes: DAT_0059af5a/DAT_0059af70 index; DAT_0059e0f8/DAT_0059e108
 *   multi-codepoint records. */
void FUN_003d3c88(unsigned long param_1, int *param_2)
{
    unsigned int uVar1, uVar2, uVar6;
    long lVar3;
    unsigned long uVar4, uVar5;

    lVar3 = FUN_003d326c(param_1, 0xb, (long)0x67d658, (long)0x67d6b0,
                         (long)&DAT_0059af5a);
    uVar4 = *(unsigned long *)(&DAT_0059af70 + lVar3 * 8);
    uVar6 = (unsigned int)param_1;
    if (uVar6 == ((unsigned int)uVar4 & 0x1fffff)) {
        if ((long)uVar4 < 0) {
            lVar3 = FUN_003d326c(param_1, 5, (long)0x67d708, (long)0x67d730,
                                 (long)u_hF____0059e0f8);
            uVar5 = *(unsigned long *)(&DAT_0059e108 + lVar3 * 8);
            uVar4 = uVar5 >> 0x3e;
            do {
                uVar1 = (unsigned int)uVar5 & 0xffff;
                uVar2 = (unsigned int)(-(int)uVar1);
                if ((uVar5 & 0x10000) != 0) {
                    uVar2 = uVar1;
                }
                uVar5 >>= 0x11;
                *param_2 = (int)(uVar2 + uVar6);
                uVar4--;
                param_2++;
            } while (uVar4 != 0);
            return;
        }
        param_1 = (unsigned long)(uVar6 - (int)(uVar4 >> 0x15));
    }
    *param_2 = (int)param_1;
}

/* FUN_003d3d4c @ 0x3d3d4c   (est. cL4_unicode_byte_property)
 * Ghidra: undefined1 FUN_003d3d4c(uint)
 * Walk the 8-bit property trie at 0x59e9d4 (leaf at 0x59fae4) to return the
 * single-byte property for the scalar; 0xff on miss.
 * Confidence: low
 * Notes: trie entries: 21-bit first, 21-bit count. */
unsigned char FUN_003d3d4c(unsigned int param_1)
{
    unsigned int uVar1, uVar2, uVar3;

    uVar3 = 1;
    do {
        uVar2 = *(unsigned int *)((long)(int)uVar3 * 4 + 0x59e9d4);
        uVar1 = uVar2 & 0x1fffff;
        if (param_1 < uVar1) {
            uVar3 <<= 1;
        } else {
            if (param_1 <= (uVar1 + (uVar2 >> 0x15)) - 1) {
                return *(unsigned char *)((long)(int)uVar3 + 0x59fae4);
            }
            uVar3 = uVar3 << 1 | 1;
        }
    } while ((int)uVar3 < 0x444);
    return 0xff;
}

/* FUN_003d3dac @ 0x3d3dac   (est. cL4_is_once_completed)
 * Ghidra: bool FUN_003d3dac(void)
 * Return true if the once token at 0x6c0b20 equals the current thread's
 * recorded token (i.e. the once block has already been run on this thread).
 * Confidence: medium
 * Notes: _DAT_006c0b20 is the shared once token. */
bool FUN_003d3dac(void)
{
    int iVar1;
    unsigned long uVar2;

    uVar2 = cL4_current_thread();
    iVar1 = cL4_eq(uVar2, _DAT_006c0b20);
    return iVar1 != 0;
}

/* FUN_003d3dd8 @ 0x3d3dd8   (est. cL4_once_execute)
 * Ghidra: void FUN_003d3dd8(long*, code*, undefined8)
 * pthread_once-style primitive. If the token *param_1 is zero, arm it,
 * run the closure param_2 with param_3, then mark it -1 (complete) and
 * broadcast the condvar; a waiting thread wakes via cnd_wait. If the token
 * is already -1 (complete) returns immediately.
 * Confidence: high
 * Notes: uses globals 0x6c0b40 (onceCond) and 0x6c0b30 (onceMutex); the
 *   failure strings are cnd_broadcast/cnd_wait/mtx_lock/mtx_unlock asserts. */
void FUN_003d3dd8(long *param_1, void (*param_2)(unsigned long), unsigned long param_3)
{
    int iVar1;

    if (*param_1 == 0) {
        *param_1 = 1;
        (*param_2)(param_3);
        *param_1 = -1;
        FUN_003d3e94();
        FUN_003d3ed0();
        iVar1 = cL4_cnd_broadcast(0x6c0b40);
        if (iVar1 != 0) {
            cL4_fatal((const char *)0x5dbc8c);   /* "cnd_broadcast (onceCond) failed..." */
        }
        return;
    }
    FUN_003d3e94();
    do {
        if (*param_1 < 0) {
            FUN_003d3ed0();
            return;
        }
        iVar1 = cL4_cnd_wait(0x6c0b40, 0x6c0b30);
    } while (iVar1 == 0);
    cL4_fatal((const char *)0x5dbcbc);   /* "cnd_wait (onceCond, onceMutex)..." */
}

/* FUN_003d3e94 @ 0x3d3e94   (est. cL4_once_mutex_lock)
 * Ghidra: void FUN_003d3e94(void)
 * Lock the once mutex (0x6c0b30), asserting success.
 * Confidence: high
 * Notes: string ref s_mtx_lock__onceMutex___failed@0x5dbc32. */
void FUN_003d3e94(void)
{
    int iVar1;

    iVar1 = cL4_mtx_lock(0x6c0b30);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc32);   /* "mtx_lock (onceMutex) failed w..." */
}

/* FUN_003d3ed0 @ 0x3d3ed0   (est. cL4_once_mutex_unlock)
 * Ghidra: void FUN_003d3ed0(void)
 * Unlock the once mutex (0x6c0b30), asserting success.
 * Confidence: high
 * Notes: string ref s_mtx_unlock__onceMutex___failed@0x5dbc5e. */
void FUN_003d3ed0(void)
{
    int iVar1;

    iVar1 = cL4_mtx_unlock(0x6c0b30);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc5e);   /* "mtx_unlock (onceMutex) failed..." */
}

/* FUN_003d3f0c @ 0x3d3f0c   (est. cL4_once_global_init)
 * Ghidra: void FUN_003d3f0c(void)
 * One-time global initialiser: record the current thread as the once owner
 * and initialise the once mutex and condvar (0x6c0b30 / 0x6c0b40),
 * asserting success.
 * Confidence: high
 * Notes: string refs s___mtx_init__onceMutex___mtx_pl@0x5dbbca and
 *   s___cnd_init__onceCond___failed@0x5dbc05. */
void FUN_003d3f0c(void)
{
    int iVar1;

    _DAT_006c0b20 = cL4_current_thread();
    iVar1 = cL4_mtx_init(0x6c0b30, 0);
    if (iVar1 != 0) {
        cL4_fatal((const char *)0x5dbbca);   /* "mtx_init (onceMutex) mtx_pl..." */
    }
    iVar1 = cL4_cnd_init(0x6c0b40);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc05);   /* "cnd_init (onceCond) failed w..." */
}

/* FUN_003d3f78 @ 0x3d3f78   (est. cL4_executor_job_create)
 * Ghidra: long FUN_003d3f78(void)
 * Allocate a new job/task record, initialise its executor context fields
 * (+0x10 from the current task, +0x18/+0x20 preserved registers), run the
 * retain barrier, and return the new record.
 * Confidence: low
 * Notes: uses FUN_00350b54/FUN_0036a940 and thunk_FUN_0036b270. */
long FUN_003d3f78(void)
{
    unsigned long uVar1;
    long lVar2;

    uVar1 = cL4_task_alloc();
    lVar2 = cL4_executor_storage();
    *(unsigned long *)(lVar2 + 0x10) = uVar1;
    *(unsigned long *)(lVar2 + 0x18) = 0;   /* unaff_x21 (callee-saved) */
    *(unsigned long *)(lVar2 + 0x20) = 0;   /* unaff_x19 (callee-saved) */
    cL4_retain(0);
    return lVar2;
}

/* FUN_003d3fcc @ 0x3d3fcc   (est. cL4_executor_teardown)
 * Ghidra: void FUN_003d3fcc(void)
 * Tear down the current async job/executor context: destroy the box at
 * +0x18, and if a task handle exists at +0x10, abort the task, emit trace
 * records, release references and free the frame.
 * Confidence: low
 * Notes: heavy use of trace_emit (0x2acbb8) and runtime-crash frames. */
void FUN_003d3fcc(void)
{
    unsigned long uVar1;
    long lVar2;

    cL4_box_destroy(0);                     /* unaff_x20 + 0x18 */
    if (*(long *)0x10 != 0) {
        cL4_task_abort();
        cL4_stack_mark(0x90);
        cL4_trace_emit(0xd000000000000020, 0x80000000005dbce0);
        uVar1 = *(unsigned long *)0x20;
        cL4_retain(uVar1);
        FUN_000b4390();
        cL4_trace_emit(0, 0);
        cL4_obj_release(uVar1);
        cL4_trace_emit(0xd00000000000006e, 0x80000000005dc5e0);
        lVar2 = cL4_crash_frame(0, 0);
        cL4_obj_release(0);
        cL4_frame_dealloc(lVar2 + 0x20);
        cL4_release(lVar2);
    }
}
