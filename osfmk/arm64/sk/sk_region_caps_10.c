/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0xaf4d0 - 0xb44ac) is the caps-region utility layer:
 *   - bitmap / bitfield primitives (test-and-clear / test-and-set),
 *   - the bitmap-indexed hash table (sk_htbl_t) used for capability and
 *     object lookup (insert / lookup / grow / rebuild),
 *   - number-string parsing, comparison, and allocation helpers,
 *   - trap/deferral glue around the hash table.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Shared kernel/object dependencies (declared extern; bodies owned by
 * other range workers — out of slice).
 * ------------------------------------------------------------------ */

extern void cL4_ref_release(uint64_t obj);
extern void cL4_ref_acquire(uint64_t obj);
extern void *cL4_alloc_exact(uint64_t size, uint64_t tag);
extern void *cL4_alloc_exact2(uint64_t size, uint64_t tag);
extern void *cL4_alloc_copy(uint64_t size);
extern void cL4_free(void *p, uint64_t size);
extern unsigned long sk_htbl_hash(uint64_t table);
extern unsigned long sk_htbl_hash2(uint64_t table, uint64_t key);
extern unsigned long sk_htbl_cmp(uint64_t a, uint64_t b, ...);
extern unsigned long sk_htbl_cmp2(uint64_t a, uint64_t b);
extern unsigned long sk_reg_read(uint64_t);
extern void sk_htbl_key_frame_init(uint64_t *frame, uint64_t seed); /* FUN_001a84f4 */
extern uint64_t sk_htbl_key_pos(void);                             /* FUN_001a8564 */
extern void sk_htbl_pair_key(uint64_t *frame, uint64_t k, uint64_t v); /* FUN_001b9084 */
extern unsigned long sk_atou(void);
extern unsigned long sk_enter_gl(void);
extern void sk_defer(void);
extern void sk_defer_flush(void);
extern cl4_result_t sk_exc_poll(void);
extern void sk_region_init(uint64_t a);
extern void sk_region_commit(uint64_t a, uint64_t b);
extern void sk_trace_note(uint64_t a, uint64_t b);
extern void sk_htbl_walk2(uint64_t a, ...);
extern void sk_bzero(void *p, uint64_t size);
extern void sk_noreturn(void);
extern unsigned long sk_alloc_small(uint64_t size, uint64_t tag);
extern void *sk_alloc_tagged(uint64_t size, uint64_t tag);
extern unsigned long sk_alloc_canary(uint64_t size, uint64_t align);
extern unsigned long sk_obj_add(uint64_t a);
extern void sk_htbl_put(uint64_t a, uint64_t b);
extern void sk_hash2(uint64_t a, uint64_t b);

/* ------------------------------------------------------------------ *
 * In-slice forward declarations.
 * ------------------------------------------------------------------ */
static cl4_result_t sk_bits_take(uint64_t mask);
static cl4_result_t sk_bits_set(uint64_t mask);
static uint64_t sk_bits_clr(uint64_t mask, uint64_t word);
static void sk_htbl_compact(void);
static void sk_htbl_grow_single(uint64_t min_slots);
static void sk_htbl_grow_single_move(uint64_t min_slots);
static void sk_htbl_compact_pair(void);
static void sk_htbl_grow_pair(uint64_t min_slots);
static void sk_htbl_grow_pair_move(uint64_t min_slots);
static void sk_htbl_compact_cb(void);
static void sk_htbl_grow_single_cb(uint64_t min_slots);
static void sk_htbl_grow_single_move_cb(uint64_t min_slots);
static void sk_htbl_setbit(uint64_t key, uint64_t pos, uint64_t *t);
static void sk_htbl_setbit_pair(uint64_t k, uint64_t v, uint64_t pos, uint64_t *t);
static void sk_htbl_insert(uint64_t key, uint64_t pos, uint64_t flags);
static void sk_htbl_insert_pair(uint64_t k, uint64_t v, uint64_t pos, uint64_t flags);
static void sk_htbl_insert_cb(uint64_t *key, uint64_t pos, uint64_t flags);
static bool sk_htbl_lookup_or_insert(uint64_t *out, uint64_t key);
static cl4_result_t sk_trap_defer2(void);
static void sk_trap_defer6(void);
static cl4_result_t sk_trap_msg_read(void);
static cl4_result_t sk_trap_msg_read2(uint64_t *a);
static cl4_result_t sk_trap_msg_read3(uint64_t *a, uint64_t s1, uint64_t s2, uint64_t s3);
static void sk_parse_store2(uint64_t a, uint64_t b, uint64_t v);
static cl4_result_t sk_common_consume(uint64_t a);
static cl4_result_t sk_msg_enter2(void);
static void sk_common_consume2(void);
static void sk_common_dispatch2(void);
static void sk_common_done(void);
static void sk_common_exit(void);
static void sk_common_clear(void);
static void sk_common_flush(void);
static void sk_common_dispatch(void);
static cl4_result_t sk_msg_enter(void);
static void sk_handle(void);
static uint64_t sk_reg_val2(void);
static uint64_t sk_reg_val3(void);
static void sk_reg_store_frame(uint64_t a, uint64_t b);
static uint8_t sk_deref_byte(uint8_t *p);
static uint64_t sk_htbl_count(uint64_t *t);
static uint8_t *sk_htbl_insert_alloc(long n, uint8_t keep, uint64_t cb,
                                     uint64_t v0, uint64_t v1, uint64_t v2);
static uint64_t *sk_htbl_finish(uint64_t *bm, long nwords, long count, uint64_t *t);
static void sk_htbl_lookup_cb(uint64_t *arg, uint64_t key);
static void sk_parse_store_impl(uint64_t a, uint64_t b, uint64_t out, int which);
static void sk_trap_parse_store3(uint64_t a, uint64_t b, uint64_t c,
                                 uint64_t d, uint64_t out);
static uint32_t sk_parse_u8(const uint8_t *s, long len, long radix);
static uint32_t sk_parse_u8_signed(const uint8_t *s, long len, long radix);
static cl4_result_t sk_parse_u64(uint64_t a, uint64_t b, uint64_t radix);
static uint64_t sk_parse_len(void);
static void sk_common_preamble(void);
static void sk_common_preamble2(uint64_t a, uint64_t b);
static uint64_t sk_trap_defer4(void);
static void sk_trap_defer6(void);
static void sk_htbl_move_bitmap(uint64_t *t, uint64_t words);
static void sk_htbl_fill(uint64_t val, long n, uint64_t *out);
static void sk_htbl_clear_bitmap(uint64_t *t);
static uint64_t *sk_htbl_bitmap(void);
static void sk_htbl_range_check(long idx, uint64_t key, long limit);
static void sk_htbl_rehash_single(uint64_t *t);
static void sk_htbl_rehash_pair(uint64_t *t);

/* Global stand-ins for register-passed pointers (unaff_x20 / unaff_x19). */
uint64_t *sk_reg_word;   /* unaff_x20: bitmap / hash-table pointer */
uint8_t  *sk_reg_byte;   /* unaff_x19: flag byte */
uint64_t  sk_reg_val;    /* unaff_x21/x22/x23/x24: register args */

/* Static empty table / empty string (DAT_00657778 / DAT_006577e0). */
static uint8_t sk_htbl_empty[0x40];
static const char sk_str_empty[1] = { 0 };

static uint64_t sk_reg_val2(void) { return sk_reg_val; }
static uint64_t sk_reg_val3(void) { return sk_reg_val; }
static void sk_reg_store_frame(uint64_t a, uint64_t b) { (void)a; (void)b; }

/* ------------------------------------------------------------------ *
 * Bitmap / bitfield primitives.
 * ------------------------------------------------------------------ */

/* FUN_000af4d0 @ 0xaf4d0   (est. sk_bits_xor)
 * Ghidra: ulong FUN_000af4d0(ulong param_1, ulong param_2)
 * XOR of two 64-bit masks.
 * Confidence: high */
static uint64_t sk_bits_xor(uint64_t a, uint64_t b) { return a ^ b; }

/* FUN_000af4d8 @ 0xaf4d8   (est. sk_bits_xor32)
 * Ghidra: uint FUN_000af4d8(uint param_1, uint param_2)
 * 32-bit XOR of two masks.
 * Confidence: high */
static uint32_t sk_bits_xor32(uint32_t a, uint32_t b) { return a ^ b; }

/* FUN_000af518 @ 0xaf518   (est. sk_bits_take)
 * Ghidra: undefined1[16] FUN_000af518(ulong param_1)
 * Test-and-clear: if any bit of `mask` is set in the word at sk_reg_word,
 * clear those bits and return {old_value, 0}; otherwise {0, 1}.
 * Confidence: high */
static cl4_result_t sk_bits_take(uint64_t mask)
{
    cl4_result_t r;
    uint64_t old = *sk_reg_word & mask;
    if (old != 0) {
        *sk_reg_word &= ~mask;
        r.lo = old; r.hi = 0;
        return r;
    }
    r.lo = 0; r.hi = 1;   /* ZEXT816(1) << 0x40 */
    return r;
}

/* FUN_000af540 @ 0xaf540   (est. sk_bits_take8)
 * Ghidra: undefined2 FUN_000af540(byte param_1)
 * 8-bit test-and-clear; returns CONCAT11(present==0, matched).
 * Confidence: high */
static uint16_t sk_bits_take8(uint8_t mask)
{
    uint8_t old = *((uint8_t *)sk_reg_word) & mask;
    if (old != 0)
        *((uint8_t *)sk_reg_word) &= (uint8_t)(mask ^ 0xff);
    return (uint16_t)((old == 0) << 8) | old;
}

/* FUN_000af56c @ 0xaf56c   (est. sk_bits_take32)
 * Ghidra: ulong FUN_000af56c(uint param_1)
 * 32-bit test-and-clear; returns matched or 0x100000000 if none.
 * Confidence: high */
static uint64_t sk_bits_take32(uint32_t mask)
{
    uint32_t old = *((uint32_t *)sk_reg_word) & mask;
    if (old != 0) {
        *((uint32_t *)sk_reg_word) &= (mask ^ UINT32_MAX);
        return old;
    }
    return 0x100000000ull;
}

/* FUN_000af4e8 @ 0xaf4e8   (est. sk_bits_take_store)
 * Ghidra: void FUN_000af4e8(undefined8 *param_1, undefined8 *param_2)
 * Store the {value,status} result of sk_bits_take(*param_2) into *param_1.
 * Confidence: high */
static void sk_bits_take_store(uint64_t *out, uint64_t *word)
{
    cl4_result_t r = sk_bits_take(*word);
    out[0] = r.lo;
    *((uint8_t *)(out + 1)) = (uint8_t)r.hi;
}

/* FUN_000af5c0 @ 0xaf5c0   (est. sk_bits_set)
 * Ghidra: undefined1[16] FUN_000af5c0(ulong param_1)
 * Test-and-set: OR mask into the word; returns {matched, (matched==0)}.
 * Confidence: high */
static cl4_result_t sk_bits_set(uint64_t mask)
{
    cl4_result_t r;
    uint64_t old = *sk_reg_word;
    *sk_reg_word = old | mask;
    old &= mask;
    r.lo = old; r.hi = (old == 0) ? 1 : 0;
    return r;
}

/* FUN_000af5d8 @ 0xaf5d8   (est. sk_bits_set8)
 * Ghidra: uint FUN_000af5d8(byte param_1)
 * 8-bit test-and-set; returns matched or 0x100.
 * Confidence: high */
static uint32_t sk_bits_set8(uint8_t mask)
{
    uint8_t old = *((uint8_t *)sk_reg_word);
    *((uint8_t *)sk_reg_word) = old | mask;
    old &= mask;
    return (old != 0) ? old : 0x100;
}

/* FUN_000af5fc @ 0xaf5fc   (est. sk_bits_set32)
 * Ghidra: ulong FUN_000af5fc(uint param_1)
 * 32-bit test-and-set; returns matched or 0x100000000.
 * Confidence: high */
static uint64_t sk_bits_set32(uint32_t mask)
{
    uint32_t old = *((uint32_t *)sk_reg_word);
    *((uint32_t *)sk_reg_word) = old | mask;
    old &= mask;
    return (old != 0) ? (uint64_t)old : 0x100000000ull;
}

/* FUN_000af590 @ 0xaf590   (est. sk_bits_set_store)
 * Ghidra: void FUN_000af590(undefined8 *param_1, undefined8 *param_2)
 * Store the {value,status} result of sk_bits_set(*param_2) into *param_1.
 * Confidence: high */
static void sk_bits_set_store(uint64_t *out, uint64_t *word)
{
    cl4_result_t r = sk_bits_set(*word);
    out[0] = r.lo;
    *((uint8_t *)(out + 1)) = (uint8_t)r.hi;
}

/* FUN_000af684 @ 0xaf684   (est. sk_bits_clr_store)
 * Ghidra: void FUN_000af684(undefined8 *param_1, undefined8 *param_2)
 * Store sk_bits_clr(*param_2, *sk_reg_word) into *param_1.
 * Confidence: high */
static void sk_bits_clr_store(uint64_t *out, uint64_t *word)
{
    out[0] = sk_bits_clr(*word, *sk_reg_word);
}

/* FUN_000af6b4 @ 0xaf6b4   (est. sk_bits_clr)
 * Ghidra: ulong FUN_000af6b4(ulong param_1, ulong param_2)
 * Clear bits of param_1 in param_2: param_2 & ~param_1.
 * Confidence: high */
static uint64_t sk_bits_clr(uint64_t mask, uint64_t word)
{
    return word & ~mask;
}

/* ------------------------------------------------------------------ *
 * Small flag/word helpers.
 * ------------------------------------------------------------------ */

/* FUN_000af75c @ 0xaf75c   (est. sk_store_thread)
 * Ghidra: void FUN_000af75c(undefined8 *param_1)
 * Store the current-thread handle into *param_1.
 * Confidence: low */
static void sk_store_thread(uint64_t *out)
{
    extern uint64_t sk_cur_thread(void); /* FUN_000aadc8 */
    *out = sk_cur_thread();
}

/* FUN_000af7b4 @ 0xaf7b4   (est. sk_ep_handshake)
 * Ghidra: uint FUN_000af7b4(undefined8 param_1, long param_2)
 * Three-phase endpoint handshake helper. Phase A: wait for an exception
 * record; if it is the Wait kind (0x52) bound to the kernel exc tag
 * (-0x1f00000000000000 = 0xe100000000000000) consume it and report bit 0;
 * otherwise forward it. Phase B: same with Send kind (0x57) reporting bit 1.
 * Phase C: Reply kind (0x58) reporting bit 2. Returns an OR of the completed
 * phase bits.
 * Confidence: low
 * Notes: exception records from FUN_0029fb80 (sk_exc_poll); kinds compared
 *   to 0xe100000000000000; forward via FUN_000b44cc / FUN_000b4528. */
static uint32_t sk_ep_handshake(uint64_t a, uint64_t param_2)
{
    cl4_result_t rec;
    uint64_t p;
    uint32_t status = 0;
    (void)a;

    cL4_ref_acquire(param_2);
    /* Phase A: Wait (0x52) */
    do {
        rec = (cl4_result_t)sk_exc_poll();
        p = rec.hi;
        if (rec.hi == 0) {
            status = 0;
            p = param_2;
            break;
        }
        if (rec.lo == 0x52 && rec.hi == 0xe100000000000000ull) {
            cL4_ref_release(param_2);
            status = 1;
            break;
        }
        sk_trace_note(rec.lo, rec.hi);
        sk_defer_flush();
    } while ((sk_reg_val & 1) == 0);
    status = 1;
    p = param_2;

    cL4_ref_release(p);
    cL4_ref_acquire(param_2);
    /* Phase B: Send (0x57) */
    do {
        rec = (cl4_result_t)sk_exc_poll();
        p = rec.hi;
        if (rec.hi == 0) {
            cL4_ref_release(param_2);
            break;
        }
        if (rec.lo == 0x57 && rec.hi == 0xe100000000000000ull) {
            cL4_ref_release(param_2);
            break;
        }
        sk_trace_note(rec.lo, rec.hi);
        cL4_ref_release(rec.hi);
        p = param_2;
    } while ((sk_reg_val & 1) == 0);
    cL4_ref_release(p);
    status |= 2;

    cL4_ref_acquire(param_2);
    /* Phase C: Reply (0x58) */
    for (;;) {
        rec = (cl4_result_t)sk_exc_poll();
        p = rec.hi;
        if (rec.hi == 0) {
            cL4_ref_release(param_2);
            return status;
        }
        if (rec.lo == 0x58 && rec.hi == 0xe100000000000000ull)
            break;
        sk_trace_note(rec.lo, rec.hi);
        cL4_ref_release(rec.hi);
        p = param_2;
        if ((sk_reg_val & 1) != 0) {
            cL4_ref_release(param_2);
            cL4_ref_release(p);
            return status | 4;
        }
    }
    cL4_ref_release(param_2);
    cL4_ref_release(param_2);
    cL4_ref_release(p);
    return status | 4;
}

/* FUN_000af96c @ 0xaf96c   (est. sk_store_byte)
 * Ghidra: void FUN_000af96c(undefined1 *param_1)
 * Store the byte from FUN_0000456c into *param_1.
 * Confidence: low */
static void sk_store_byte(uint8_t *out)
{
    extern uint8_t sk_read_byte(void); /* FUN_0000456c */
    *out = sk_read_byte();
}

/* FUN_000af994 @ 0xaf994   (est. sk_flag_take)
 * Ghidra: void FUN_000af994(void)
 * Take a bit from the flags word (thunk_FUN_0008cc7c) after the preamble.
 * Confidence: low */
static void sk_flag_take(void)
{
    extern uint8_t sk_flag_take_op(void); /* thunk_FUN_0008cc7c */
    sk_deref_byte(sk_reg_byte);
    *sk_reg_byte = sk_flag_take_op();
}

/* FUN_000af9f4 @ 0xaf9f4   (est. sk_flag_take2)
 * Ghidra: void FUN_000af9f4(void)
 * Like sk_flag_take but operator is FUN_00084cc4.
 * Confidence: low */
static void sk_flag_take2(void)
{
    extern uint8_t sk_flag_take_op2(void); /* FUN_00084cc4 */
    sk_deref_byte(sk_reg_byte);
    *sk_reg_byte = sk_flag_take_op2();
}

/* FUN_000afa1c @ 0xafa1c   (est. sk_flag_xor)
 * Ghidra: void FUN_000afa1c(void)
 * Store the low byte of the 32-bit XOR of the two register words into
 * *sk_reg_byte.
 * Confidence: low */
static void sk_flag_xor(void)
{
    uint32_t a = (uint32_t)sk_reg_val;
    uint32_t b = (uint32_t)sk_reg_val2();
    sk_deref_byte(sk_reg_byte);
    *sk_reg_byte = (uint8_t)sk_bits_xor32(a, b);
}

/* FUN_000afa4c @ 0xafa4c   (est. sk_flag_take8_store)
 * Ghidra: void FUN_000afa4c(undefined2 *param_1, undefined1 *param_2)
 * Store sk_bits_take8(*param_2) into *param_1.
 * Confidence: high */
static void sk_flag_take8_store(uint16_t *out, uint8_t *mask)
{
    *out = sk_bits_take8(*mask);
}

/* FUN_000afa78 @ 0xafa78   (est. sk_flag_set8_store)
 * Ghidra: void FUN_000afa78(undefined2 *param_1, undefined1 *param_2)
 * Store sk_bits_set8(*param_2) into *param_1.
 * Confidence: high */
static void sk_flag_set8_store(uint16_t *out, uint8_t *mask)
{
    *out = (uint16_t)sk_bits_set8(*mask);
}

/* FUN_000afab4 @ 0xafab4   (est. sk_flag_take3)
 * Ghidra: void FUN_000afab4(void)
 * Like sk_flag_take but operator is FUN_00085754.
 * Confidence: low */
static void sk_flag_take3(void)
{
    extern uint8_t sk_flag_take_op3(void); /* FUN_00085754 */
    sk_deref_byte(sk_reg_byte);
    *sk_reg_byte = sk_flag_take_op3();
}

/* FUN_000afb14 @ 0xafb14   (est. sk_store_byte2)
 * Ghidra: void FUN_000afb14(undefined1 *param_1)
 * Store the byte from FUN_000aae14 into *param_1.
 * Confidence: low */
static void sk_store_byte2(uint8_t *out)
{
    extern uint8_t sk_read_byte2(void); /* FUN_000aae14 */
    *out = sk_read_byte2();
}

/* FUN_000affac @ 0xaffac   (est. sk_feature_available)
 * Ghidra: undefined8 FUN_000affac(void)
 * Query a capability via the boot-services vector with the tag
 * 0x6c616e6f6974706f ("optional"); release any returned handle. Returns 1
 * if available.
 * Confidence: low */
static uint64_t sk_feature_available(void)
{
    extern uint64_t (*sk_boot_get)(uint64_t tag, uint64_t kind);
    uint64_t h;

    sk_enter_gl();
    sk_defer();
    if (1 && (h = sk_boot_get(0x6c616e6f6974706full, 0xe800000000000000ull)) != 0) {
        cL4_ref_release(h);
        return 1;
    }
    return 0;
}

/* FUN_000b0030 @ 0xb0030   (est. sk_build_version_ok)
 * Ghidra: uint FUN_000b0030(void)
 * Return whether the current build is supported: if the optional feature is
 * unavailable return 0; else fetch the version tuple and compare it against
 * the compiled-in tuple.
 * Confidence: low */
static uint32_t sk_build_version_ok(void)
{
    cl4_result_t tuple, cmp;
    extern cl4_result_t sk_ver_make(uint64_t a, uint64_t b, const char *s,
                                    uint64_t d, uint64_t e, uint64_t f,
                                    uint64_t g); /* FUN_000a1558 */
    extern cl4_result_t sk_ver_cur(void);         /* FUN_00121640 */

    if ((sk_feature_available() & 1) == 0)
        return 0;
    sk_enter_gl();
    tuple = sk_ver_make(0xd00000000000002aull, 0x80000000005c0b90ull,
                        "AppleInternal Library BuildRoot", 0xf5, 2, 0x248,
                        sk_reg_read(0));
    cL4_ref_release(tuple.hi);
    cmp = sk_ver_cur();
    if (tuple.lo == cmp.lo && tuple.hi == cmp.hi)
        return 1;
    return sk_htbl_cmp2(tuple.lo, tuple.hi) & 1;
}

/* ------------------------------------------------------------------ *
 * Bitmap-indexed hash table (sk_htbl_t).
 * Layout (offsets):
 *   +0x10 count, +0x18 capacity, +0x20 log2 size (byte),
 *   +0x28 hash fn, +0x30 slots, +0x38 occupancy bitmap.
 * ------------------------------------------------------------------ */

static inline uint64_t sk_htbl_slots(uint64_t *t)
{
    return 1ull << (((uint8_t *)t)[0x20] & 0x3f);
}
static inline uint64_t sk_htbl_count(uint64_t *t) { return t[2]; }

/* bit-reverse of a 64-bit word (used to turn LZCOUNT into ctz). */
static inline uint64_t sk_rev64(uint64_t v)
{
    v = ((v & 0xaaaaaaaaaaaaaaaaull) >> 1) | ((v & 0x5555555555555555ull) << 1);
    v = ((v & 0xccccccccccccccccull) >> 2) | ((v & 0x3333333333333333ull) << 2);
    v = ((v & 0xf0f0f0f0f0f0f0f0ull) >> 4) | ((v & 0x0f0f0f0f0f0f0f0full) << 4);
    v = ((v & 0xff00ff00ff00ff00ull) >> 8) | ((v & 0x00ff00ff00ff00ffull) << 8);
    v = ((v & 0xffff0000ffff0000ull) >> 16) | ((v & 0x0000ffff0000ffffull) << 16);
    return (v >> 32) | (v << 32);
}
/* Index of the lowest set bit of w (LZCOUNT of bit-reversed word). */
static inline uint64_t sk_lsb(uint64_t w)
{
    uint64_t r = sk_rev64(w);
    return __builtin_clzll(r >> 32 | r << 32);
}

/* FUN_000b02c0 @ 0xb02c0   (est. sk_htbl_fill)
 * Ghidra: void FUN_000b02c0(undefined8 param_1, long param_2, undefined8 *param_3)
 * Fill param_2 consecutive 8-byte slots at *param_3 with param_1.
 * Confidence: high */
static void sk_htbl_fill(uint64_t val, long n, uint64_t *out)
{
    if (n < 0)
        __builtin_trap();
    for (; n != 0; n--)
        *out++ = val;
}

/* FUN_000b0888 @ 0xb0888   (est. sk_htbl_range_check)
 * Ghidra: void FUN_000b0888(long param_1, undefined8 param_2, long param_3)
 * Range assertion: param_1 must be < param_3 and >= 0, else trap.
 * Confidence: high */
static void sk_htbl_range_check(long idx, uint64_t key, long limit)
{
    (void)key;
    if (idx >= limit) __builtin_trap();
    if (idx < 0) __builtin_trap();
}

/* FUN_000b402c @ 0xb402c   (est. sk_htbl_clear_bitmap)
 * Ghidra: void FUN_000b402c(long param_1)
 * Clear the occupancy bitmap of the table at param_1.
 * Confidence: high */
static void sk_htbl_clear_bitmap(uint64_t *t)
{
    uint64_t mask = ~(-1ull << (((uint8_t *)t)[0x20] & 0x3f));
    sk_region_init((uint64_t)(t + 0x38 / 8));
    (void)mask;
}

/* FUN_000b431c @ 0xb431c   (est. sk_htbl_bitmap)
 * Ghidra: long FUN_000b431c(void)
 * Return the address of the occupancy bitmap (sk_reg_word + 0x38).
 * Confidence: high */
static uint64_t *sk_htbl_bitmap(void)
{
    return sk_reg_word + 0x38 / 8;
}

/* FUN_000b3910 @ 0xb3910   (est. sk_htbl_setbit)
 * Ghidra: void FUN_000b3910(undefined8 param_1, ulong param_2, long param_3)
 * Set occupancy bit pos in table t and store key into the 8-byte slot;
 * increment count.
 * Confidence: high */
static void sk_htbl_setbit(uint64_t key, uint64_t pos, uint64_t *t)
{
    uint64_t *bm = t + 0x38 / 8 + (pos >> 6);
    *bm |= 1ull << (pos & 0x3f);
    *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8) = key;
    t[2]++;
}

/* FUN_000b394c @ 0xb394c   (est. sk_htbl_setbit_pair)
 * Ghidra: void FUN_000b394c(undefined8 param_1, undefined8 param_2,
 *                           ulong param_3, long param_4)
 * Set occupancy bit pos in table t and store {k,v} into the 16-byte slot;
 * increment count.
 * Confidence: high */
static void sk_htbl_setbit_pair(uint64_t k, uint64_t v, uint64_t pos, uint64_t *t)
{
    uint64_t *bm = t + 0x38 / 8 + (pos >> 6);
    uint64_t *slot = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 16);
    *bm |= 1ull << (pos & 0x3f);
    slot[0] = k;
    slot[1] = v;
    t[2]++;
}

/* FUN_000b24cc @ 0xb24cc   (est. sk_htbl_insert)
 * Ghidra: void FUN_000b24cc(long param_1, ulong param_2, ulong param_3)
 * Insert key into the table at sk_reg_word at hash position pos (bitmask
 * flags). Grows if full, then scans for the first free slot and stores.
 * Confidence: high */
static void sk_htbl_insert(uint64_t key, uint64_t pos, uint64_t flags)
{
    uint64_t *t = sk_reg_word;
    uint64_t n = t[2];
    uint64_t cap = t[3];

    if (n < cap) {
        if ((flags & 1) == 0)
            sk_htbl_compact();
    } else {
        if ((flags & 1) == 0)
            sk_htbl_grow_single(n + 1);
        else
            sk_htbl_grow_single_move(n + 1);
        t = sk_reg_word;
        pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)t + 0x28));
        while ((t[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1) != 0) {
            if (*(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8) == key)
                sk_region_commit(0x677790, pos);
            pos++;
        }
    }
    sk_htbl_setbit(key, pos, t);
}

/* FUN_000b2598 @ 0xb2598   (est. sk_htbl_insert_pair)
 * Ghidra: void FUN_000b2598(long param_1, long param_2, ulong param_3,
 *                           ulong param_4)
 * Insert {k,v} into the table at sk_reg_word at hash position pos.
 * Confidence: high */
static void sk_htbl_insert_pair(uint64_t k, uint64_t v, uint64_t pos, uint64_t flags)
{
    uint64_t *t = sk_reg_word;
    uint64_t n = t[2], cap = t[3];

    if (n < cap) {
        if ((flags & 1) == 0)
            sk_htbl_compact_pair();
    } else {
        if ((flags & 1) == 0)
            sk_htbl_grow_pair(n + 1);
        else
            sk_htbl_grow_pair_move(n + 1);
        t = sk_reg_word;
        sk_hash2(k, v);
        pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)t + 0x28));
        for (;;) {
            pos &= ~(-1ull << (((uint8_t *)t)[0x20] & 0x3f));
            if ((t[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1) == 0)
                break;
            {
                uint64_t *slot = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 16);
                uint64_t sk = slot[0], sv = slot[1];
                if ((sk == k && sv == v) || (sk_htbl_cmp(sk, sv, k, v, 0) & 1))
                    sk_region_commit(0x6753a0, pos);
            }
            pos++;
        }
    }
    sk_htbl_setbit_pair(k, v, pos, t);
}

/* FUN_000b26c4 @ 0xb26c4   (est. sk_htbl_insert_cb)
 * Ghidra: void FUN_000b26c4(long *param_1, ulong param_2, ulong param_3)
 * Like sk_htbl_insert but the key is compared via a callback.
 * Confidence: low */
static void sk_htbl_insert_cb(uint64_t *key, uint64_t pos, uint64_t flags)
{
    uint64_t *t = sk_reg_word;
    uint64_t n = t[2], cap = t[3];

    if (n < cap) {
        if ((flags & 1) == 0)
            sk_htbl_compact_cb();
    } else {
        if ((flags & 1) == 0)
            sk_htbl_grow_single_cb(n + 1);
        else
            sk_htbl_grow_single_move_cb(n + 1);
        t = sk_reg_word;
        pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)t + 0x28));
        for (;;) {
            pos &= ~(-1ull << (((uint8_t *)t)[0x20] & 0x3f));
            if ((t[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1) == 0)
                break;
            if (sk_htbl_cmp(*(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8), *key) & 1)
                sk_region_commit(sk_reg_read(0), pos);
            pos++;
        }
    }
    sk_htbl_setbit(*key, pos, t);
}

/* ------------------------------------------------------------------ *
 * Hash table grow / rebuild.
 * ------------------------------------------------------------------ */

/* FUN_000b2808 @ 0xb2808   (est. sk_htbl_grow_single)
 * Grow the table to hold >= min_slots single entries, re-inserting each
 * live entry. Replaces *sk_reg_word. Confidence: low */
static void sk_htbl_grow_single(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                uint64_t key = *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)nt + 0x28));
                uint64_t ww;
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    ww = 1ull << (pos & 0x3f) &
                         (nt[0x38 / 8 + (pos >> 6)] ^ UINT64_MAX);
                    if (ww != 0) {
                        uint64_t p = sk_lsb(ww) | (pos >> 6 << 6);
                        p = p & 0x7fffffffffffffc0ull | (sk_lsb(ww) & 0x3f);
                        nt[0x38 / 8 + (p >> 6)] |= 1ull << (p & 0x3f);
                        *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + p * 8) = key;
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b29f8 @ 0xb29f8   (est. sk_htbl_grow_pair)
 * Grow the table to hold >= min_slots 16-byte pairs, re-inserting each.
 * Replaces *sk_reg_word. Confidence: low */
static void sk_htbl_grow_pair(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                uint64_t *slot = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 16);
                uint64_t k = slot[0], v = slot[1];
                uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)nt + 0x28));
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    if (!(nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)) {
                        nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                        {
                            uint64_t *ns = (uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + pos * 16);
                            ns[0] = k; ns[1] = v;
                        }
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b2c20 @ 0xb2c20   (est. sk_htbl_grow_single_cb)
 * Like sk_htbl_grow_single but entries re-hashed via object vtable key.
 * Confidence: medium (fixed: added the object-vtable +0xd8 re-key dispatch
 *   with entry acquire that was dropped from the original summary) */
static void sk_htbl_grow_single_cb(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                /* Re-key each live entry via its object vtable method
                 * (+0xd8): init a key frame from the new table's +0x28
                 * seed, acquire the entry, dispatch, read the position. */
                uint64_t *entry = *(uint64_t **)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                uint64_t keyframe[3];
                sk_htbl_key_frame_init(keyframe, *(uint64_t *)((uint8_t *)nt + 0x28));
                void (*rekey)(uint64_t *) = *(void (**)(uint64_t *))(*(uint64_t *)entry + 0xd8);
                cL4_ref_acquire((uint64_t)entry);
                rekey(keyframe);
                uint64_t pos = sk_htbl_key_pos();
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    if (!(nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)) {
                        nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                        *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + pos * 8) = (uint64_t)entry;
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* move helpers: copy the live bitmap, then zero-fill the source bitmap. */
static void sk_htbl_move_bitmap(uint64_t *t, uint64_t words)
{
    uint64_t *bm = t + 0x38 / 8;
    if ((((uint8_t *)t)[0x20] & 0x3f) < 6)
        bm[0] = -1ull << (((uint8_t *)t)[0x20] & 0x3f);
    else
        sk_htbl_fill(0, (long)words, bm);
    t[2] = 0;
}

/* FUN_000b3218 @ 0xb3218   (est. sk_htbl_grow_single_move)
 * Grow for single entries, zero-filling the source bitmap. Confidence: low */
static void sk_htbl_grow_single_move(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;
    uint64_t words;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        words = (slots + 0x3f) >> 6;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                uint64_t key = *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)nt + 0x28));
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    if (!(nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)) {
                        nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                        *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + pos * 8) = key;
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
            if (words <= wi + 1) {
                sk_htbl_move_bitmap(t, words);
                break;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b3440 @ 0xb3440   (est. sk_htbl_grow_pair_move)
 * Grow for pairs, zero-filling the source bitmap.
 * Confidence: medium (fixed: added the pair re-key via FUN_001b9084(k,v)
 *   that was dropped from the original summary) */
static void sk_htbl_grow_pair_move(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;
    uint64_t words;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        words = (slots + 0x3f) >> 6;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                uint64_t *slot = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 16);
                uint64_t k = slot[0], v = slot[1];
                /* Re-key the pair via the key routine: init a key frame from
                 * the new table's +0x28 seed, run FUN_001b9084(k,v), read
                 * the resulting position. */
                uint64_t keyframe[3];
                sk_htbl_key_frame_init(keyframe, *(uint64_t *)((uint8_t *)nt + 0x28));
                sk_htbl_pair_key(keyframe, k, v);
                uint64_t pos = sk_htbl_key_pos();
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    if (!(nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)) {
                        nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                        {
                            uint64_t *ns = (uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + pos * 16);
                            ns[0] = k; ns[1] = v;
                        }
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
            if (words <= wi + 1) {
                sk_htbl_move_bitmap(t, words);
                break;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b2e64 @ 0xb2e64   (est. sk_htbl_compact)
 * Compact the table in place into a fresh same-size table. Confidence: low */
static void sk_htbl_compact(void)
{
    uint64_t *t = sk_reg_word;
    uint64_t *nt = (uint64_t *)cL4_alloc_copy(sk_atou());

    if (t[2] != 0) {
        nt[2] = t[2];
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + i * 8) =
                    *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b2f88 @ 0xb2f88   (est. sk_htbl_compact_pair)
 * Compact the table copying each live 16-byte pair. Confidence: low */
static void sk_htbl_compact_pair(void)
{
    uint64_t *t = sk_reg_word;
    uint64_t *nt = (uint64_t *)cL4_alloc_copy(sk_atou());

    if (t[2] != 0) {
        nt[2] = t[2];
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                uint64_t *ss = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 16);
                uint64_t *ds = (uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + i * 16);
                ds[0] = ss[0]; ds[1] = ss[1];
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b30e4 @ 0xb30e4   (est. sk_htbl_compact_cb)
 * Compact the table copying each live single entry. Confidence: low */
static void sk_htbl_compact_cb(void)
{
    uint64_t *t = sk_reg_word;
    uint64_t *nt = (uint64_t *)cL4_alloc_copy(sk_atou());

    if (t[2] != 0) {
        nt[2] = t[2];
        uint64_t slots = sk_htbl_slots(t);
        uint64_t words = (slots + 0x3f) >> 6;
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + i * 8) =
                    *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                w &= w - 1;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* FUN_000b36a4 @ 0xb36a4   (est. sk_htbl_grow_single_move_cb)
 * Grow/compact for object-keyed entries, zero-filling the source bitmap.
 * Confidence: medium (fixed: added the object-vtable +0xd8 re-key dispatch,
 *   no entry acquire on this path, that was dropped from the summary) */
static void sk_htbl_grow_single_move_cb(uint64_t min_slots)
{
    uint64_t *t = sk_reg_word;
    uint64_t new_slots = t[3];
    uint64_t *nt;
    uint64_t words;

    if (t[3] <= min_slots)
        new_slots = min_slots;
    nt = (uint64_t *)cL4_alloc_exact(new_slots, sk_atou());
    if (t[2] != 0) {
        uint64_t slots = sk_htbl_slots(t);
        uint64_t *bm = t + 0x38 / 8;
        uint64_t wi, w;
        words = (slots + 0x3f) >> 6;
        for (wi = 0; wi < words; wi++) {
            w = bm[wi];
            while (w != 0) {
                uint64_t i = sk_lsb(w) | (wi << 6);
                /* Re-key each live entry via its object vtable method
                 * (+0xd8): init a key frame from the new table's +0x28 seed
                 * and dispatch (no acquire on this path), then read the
                 * resulting position. */
                uint64_t *entry = *(uint64_t **)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
                uint64_t keyframe[3];
                sk_htbl_key_frame_init(keyframe, *(uint64_t *)((uint8_t *)nt + 0x28));
                (*(void (**)(uint64_t *))(*(uint64_t *)entry + 0xd8))(keyframe);
                uint64_t pos = sk_htbl_key_pos();
                for (;;) {
                    pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                    if (!(nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)) {
                        nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                        *(uint64_t *)(*(uint64_t *)((uint8_t *)nt + 0x30) + pos * 8) = (uint64_t)entry;
                        nt[2]++;
                        break;
                    }
                    pos++;
                }
                w &= w - 1;
            }
            if (words <= wi + 1) {
                sk_htbl_move_bitmap(t, words);
                break;
            }
        }
    }
    cL4_ref_release((uint64_t)t);
    sk_reg_word = nt;
}

/* ------------------------------------------------------------------ *
 * Hash table iteration / rebuild / lookup.
 * ------------------------------------------------------------------ */

/* FUN_000b0100 @ 0xb0100   (est. sk_htbl_rehash_single)
 * Re-hash every live single entry of the table at param_1, iterating the
 * bitmap in slot order. Confidence: low */
static void sk_htbl_rehash_single(uint64_t *t)
{
    uint64_t slots = sk_htbl_slots(t);
    uint64_t words = (slots + 0x3f) >> 6;
    uint64_t *bm = t + 0x38 / 8;
    uint64_t w, wi;

    for (wi = 0; wi < words; wi++) {
        w = bm[wi];
        while (w != 0) {
            uint64_t i = sk_lsb(w) | (wi << 6);
            uint64_t key = *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
            sk_htbl_lookup_cb(&key, key);
            w &= w - 1;
        }
    }
}

/* FUN_000b01f4 @ 0xb01f4   (est. sk_htbl_rehash_pair)
 * Re-hash every live 16-byte pair of the table at param_1. Confidence: high */
static void sk_htbl_rehash_pair(uint64_t *t)
{
    uint64_t slots = sk_htbl_slots(t);
    uint64_t words = (slots + 0x3f) >> 6;
    uint64_t *bm = t + 0x38 / 8;
    uint64_t w, wi;

    for (wi = 0; wi < words; wi++) {
        w = bm[wi];
        while (w != 0) {
            uint64_t i = sk_lsb(w) | (wi << 6);
            uint64_t *slot = (uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 16);
            sk_htbl_lookup_or_insert(&slot[0], slot[1]);
            w &= w - 1;
        }
    }
}

/* FUN_000b2390 @ 0xb2390   (est. sk_htbl_lookup_cb)
 * Re-insert a single entry into the table at sk_reg_word by re-hashing its
 * key; keep existing equal slots. Confidence: low */
static void sk_htbl_lookup_cb(uint64_t *arg, uint64_t key)
{
    uint64_t *t = sk_reg_word;
    uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)t + 0x28));
    uint8_t log2 = ((uint8_t *)t)[0x20];
    uint64_t w;

    (void)arg;
    do {
        pos &= ~(-1ull << (log2 & 0x3f));
        w = 1ull << (pos & 0x3f) & *(uint64_t *)((uint8_t *)t + 0x38 + (pos >> 6) * 8);
        if (w == 0) {
            sk_htbl_insert(key, pos, sk_obj_add((uint64_t)t));
            return;
        }
        sk_htbl_walk2(0);
        if (sk_htbl_cmp(*(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8), key) & 1) {
            cL4_ref_release(key);
            *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8) = key;
            return;
        }
        pos++;
    } while (1);
}

/* FUN_000b2194 @ 0xb2194   (est. sk_htbl_lookup_or_insert)
 * Look up key in the table at sk_reg_word; insert if absent. Returns
 * whether a new slot was used; *out = key. Confidence: high */
static bool sk_htbl_lookup_or_insert(uint64_t *out, uint64_t key)
{
    uint64_t *t = sk_reg_word;
    uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)t + 0x28));
    uint64_t w;

    for (;;) {
        pos &= ~(-1ull << (((uint8_t *)t)[0x20] & 0x3f));
        w = 1ull << (pos & 0x3f) & *(uint64_t *)((uint8_t *)t + 0x38 + (pos >> 6) * 8);
        if (w == 0)
            break;
        if (*(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + pos * 8) == key)
            goto found;
        pos++;
    }
    sk_htbl_insert(key, pos, sk_obj_add((uint64_t)*sk_reg_word));
    t = sk_reg_word;
found:
    *out = key;
    return w == 0;
}

/* FUN_000b1dc4 @ 0xb1dc4   (est. sk_cmp128)
 * Compare two 128-bit values: return 1 if equal, else deep-compare. */
static uint32_t sk_cmp128(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    if (a == c && b == d)
        return 1;
    return sk_htbl_cmp2(a, b) & 1;
}

/* FUN_000b3f34 @ 0xb3f34   (est. sk_cmp128_ptr) */
static uint32_t sk_cmp128_ptr(uint64_t *a, uint64_t *b)
{
    return sk_cmp128(a[0], a[1], b[0], b[1]) & 1;
}
/* FUN_000b3f60 @ 0xb3f60   (est. sk_cmp128_key) */
static uint32_t sk_cmp128_key(uint64_t *key)
{
    return sk_cmp128_ptr(key, (uint64_t *)(sk_reg_word + 0x10 / 8)) & 1;
}
/* FUN_000b4140 @ 0xb4140   (est. sk_cmp128_cur) */
static uint32_t sk_cmp128_cur(void)
{
    return sk_cmp128_key((uint64_t *)sk_reg_val) & 1;
}
/* FUN_000b4144 @ 0xb4144   (est. sk_cmp128_cur2) */
static uint32_t sk_cmp128_cur2(void) { return sk_cmp128_cur(); }
/* FUN_000b3fe8 @ 0xb3fe8   (est. sk_cmp128_other) */
static uint32_t sk_cmp128_other(uint64_t key)
{
    extern uint32_t sk_cmp_other(uint64_t a, uint64_t b); /* FUN_000ad768 */
    return sk_cmp_other(key, sk_reg_word[0x10 / 8]) & 1;
}
/* FUN_000b3fec @ 0xb3fec   (est. sk_cmp128_other2) */
static uint32_t sk_cmp128_other2(uint64_t key) { return sk_cmp128_other(key); }

/* FUN_000b3f98 @ 0xb3f98   (est. sk_obj_triple_release) */
static void sk_obj_triple_release(uint64_t a, uint64_t b, uint64_t c,
                                  uint64_t d, uint64_t e)
{
    (void)a; (void)d;
    if (c != 0) {
        cL4_ref_release(c);
        cL4_ref_release(b);
        cL4_ref_release(e);
    }
}

/* FUN_000b3fdc @ 0xb3fdc   (est. sk_debug_hook) */
static void sk_debug_hook(void)
{
    extern void sk_debug_hook_tag(uint64_t a); /* FUN_00077770 */
    sk_debug_hook_tag(0x650820);
}

/* ------------------------------------------------------------------ *
 * Hash table alloc / rebuild into a fresh table.
 * ------------------------------------------------------------------ */

/* FUN_000b398c @ 0xb398c   (est. sk_htbl_alloc) — allocate a fresh pair
 * table of `slots` entries. Confidence: low */
static uint64_t sk_htbl_alloc(uint64_t a, uint64_t b, uint64_t slots)
{
    uint64_t nwords = (slots + 0x3f) >> 6;
    uint64_t *nt;
    (void)a; (void)b;

    if ((((uint8_t *)sk_reg_word)[0x20] & 0x3f) < 0xe ||
        (sk_alloc_canary(nwords * 8, 8) & 1) != 0) {
        sk_noreturn();
        return 0;
    }
    nt = (uint64_t *)sk_alloc_tagged(nwords * 8, UINT64_MAX);
    sk_htbl_finish(nt, nwords, 0, sk_reg_word);
    cL4_ref_release((uint64_t)sk_reg_word);
    cL4_free(nt, UINT64_MAX);
    return (uint64_t)nt;
}

/* FUN_000b3b88 @ 0xb3b88   (est. sk_htbl_build) — walk live entries, set
 * bits accepted by the callback. Confidence: low */
static void sk_htbl_build(uint64_t *bm, uint64_t nwords, uint64_t *t)
{
    uint64_t slots = sk_htbl_slots(t);
    uint64_t words = (slots + 0x3f) >> 6;
    uint64_t w, wi, count = 0;

    for (wi = 0; wi < words; wi++) {
        w = t[0x38 / 8 + wi];
        while (w != 0) {
            uint64_t i = sk_lsb(w) | (wi << 6);
            uint64_t key = *(uint64_t *)(*(uint64_t *)((uint8_t *)t + 0x30) + i * 8);
            if (sk_htbl_cmp(key, 0) & 1) {
                bm[i >> 6] |= 1ull << (i & 0x3f);
                count++;
            }
            w &= w - 1;
        }
    }
    sk_htbl_finish(bm, nwords, count, t);
}

/* FUN_000b3cfc @ 0xb3cfc   (est. sk_htbl_finish) — finalize a rebuild:
 * return the empty table / same-size source / a fresh table moved.
 * Confidence: high
 * Notes: FIXED from a pair (16B k/v) rehash: per decompile this rebuilds a
 *   single-entry (8B) table storing source-slot pointers, and returns the
 *   table (empty sentinel / same-size src / fresh). Hash fn pointer is the
 *   per-source-object method at +0xd8 (rendered via sk_htbl_hash). */
static uint64_t *sk_htbl_finish(uint64_t *bm, long nwords, long count, uint64_t *src)
{
    uint64_t *nt;
    uint64_t w;
    long wi;

    if (count == 0)
        return (uint64_t *)sk_htbl_empty;
    if (count == src[2])
        return src;
    nt = (uint64_t *)cL4_alloc_exact2((uint64_t)count, sk_atou());
    w = (nwords < 1) ? 0 : bm[0];
    wi = 0;
    do {
        if (w == 0) {
            do {
                long next = wi + 1;
                if (__builtin_add_overflow(wi, 1, &next))
                    __builtin_trap();            /* 0xb3f2c */
                if (nwords <= next)
                    goto done;
                w = bm[next];
                wi = next;
            } while (w == 0);
        }
        {
            uint64_t i = sk_lsb(w) | ((uint64_t)wi << 6);
            uint64_t *sp = *(uint64_t **)((uint8_t *)src + 0x30 + i * 8);
            uint64_t pos = sk_htbl_hash(*(uint64_t *)((uint8_t *)nt + 0x28));
            for (;;) {
                pos &= ~(-1ull << (((uint8_t *)nt)[0x20] & 0x3f));
                if ((nt[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1) == 0) {
                    nt[0x38 / 8 + (pos >> 6)] |= 1ull << (pos & 0x3f);
                    *(uint64_t **)((uint8_t *)nt + 0x30 + pos * 8) = sp;
                    nt[2]++;
                    break;
                }
                pos++;
            }
        }
        w &= w - 1;                              /* clear lowest set bit */
        if (__builtin_sub_overflow(count, 1, &count))
            __builtin_trap();                    /* 0xb3f34 */
    } while (count != 0);
done:
    cL4_ref_release((uint64_t)src);
    return nt;
}

/* ------------------------------------------------------------------ *
 * Number parsing helpers.
 * ------------------------------------------------------------------ */

/* FUN_000b0a4c @ 0xb0a4c   (est. sk_parse_u64)
 * Parse an unsigned 64-bit number from sk_parse_len() with radix; returns
 * {value, status}. Confidence: high */
static cl4_result_t sk_parse_u64(uint64_t a, uint64_t b, uint64_t radix)
{
    cl4_result_t r;
    const uint8_t *s = (const uint8_t *)sk_parse_len();
    uint64_t val = 0, status = 0;
    uint8_t hi_lim, lo_lim, lo2_lim;
    long len;
    (void)a; (void)b;

    hi_lim = (uint8_t)(radix + 0x30);
    lo_lim = 0x41;
    lo2_lim = 0x61;
    if (radix > 10) {
        lo_lim = (uint8_t)(radix + 0x37);
        lo2_lim = (uint8_t)(radix + 0x57);
    }
    if (s == NULL) {
        val = 0; status = 0;
    } else {
        len = (long)sk_parse_len();
        while (len != 0) {
            uint8_t c = *s;
            int8_t sub;
            if (c < 0x30 || c >= hi_lim) {
                if (c < 0x41 || c >= lo_lim) {
                    if (c < 0x61 || c >= lo2_lim) {
                        status = 1;
                        break;
                    }
                    sub = -0x57;
                } else {
                    sub = -0x37;
                }
            } else {
                sub = -0x30;
            }
            if (val > (UINT64_MAX - (uint8_t)(c + sub)) / radix) {
                val = 0; status = 1;
                break;
            }
            val = val * radix + (uint8_t)(c + sub);
            s++;
            len--;
        }
    }
    r.lo = val;
    r.hi = status;
    return r;
}

/* FUN_000b19d0 @ 0xb19d0   (est. sk_parse_u64_simple) — like sk_parse_u64
 * with a signed overflow check. Confidence: high */
static cl4_result_t sk_parse_u64_simple(uint64_t a, uint64_t b, long radix)
{
    cl4_result_t r;
    const uint8_t *s = (const uint8_t *)sk_parse_len();
    uint64_t val = 0, status = 0;
    uint8_t hi_lim, lo_lim, lo2_lim;
    long len;
    (void)a; (void)b;

    hi_lim = (uint8_t)(radix + 0x30);
    lo_lim = 0x41;
    lo2_lim = 0x61;
    if (radix > 10) {
        lo_lim = (uint8_t)(radix + 0x37);
        lo2_lim = (uint8_t)(radix + 0x57);
    }
    if (s == NULL) {
        val = 0; status = 0;
    } else {
        len = (long)sk_parse_len();
        while (len != 0) {
            uint8_t c = *s;
            int8_t sub;
            if (c < 0x30 || c >= hi_lim) {
                if (c < 0x41 || c >= lo_lim) {
                    if (c < 0x61 || c >= lo2_lim) {
                        status = 1;
                        break;
                    }
                    sub = -0x57;
                } else {
                    sub = -0x37;
                }
            } else {
                sub = -0x30;
            }
            if ((int64_t)(val * (uint64_t)radix) < 0 ||
                val * (uint64_t)radix + (uint8_t)(c + sub) < val * (uint64_t)radix) {
                val = 0; status = 1;
                break;
            }
            val = val * (uint64_t)radix + (uint8_t)(c + sub);
            s++;
            len--;
        }
    }
    r.lo = val;
    r.hi = status;
    return r;
}

/* FUN_000b12cc @ 0xb12cc   (est. sk_parse_u8_signed)
 * Parse an 8-bit signed number with radix; returns (value & 0xff) |
 * (status << 8). Confidence: high */
static uint32_t sk_parse_u8_signed(const uint8_t *s, long len, long radix)
{
    uint8_t val = 0;
    uint32_t status = 0;
    uint8_t hi_lim, lo_lim, lo2_lim;
    long pos = 0;
    int negative = 0;

    if (len < 1) __builtin_trap();
    hi_lim = (uint8_t)(radix + 0x30);
    lo_lim = 0x41;
    lo2_lim = 0x61;
    if (radix > 10) {
        lo_lim = (uint8_t)(radix + 0x37);
        lo2_lim = (uint8_t)(radix + 0x57);
    }
    if (s[0] == '+') {
        pos = 1;
        if (pos >= len) { val = 0; status = 1; goto done; }
    } else if (s[0] == '-') {
        pos = 1; negative = 1;
        if (pos >= len) { val = 0; status = 1; goto done; }
    }
    for (; pos < len; pos++) {
        uint8_t c = s[pos];
        int8_t sub;
        uint8_t digit;
        if (c < 0x30 || c >= hi_lim) {
            if (c < 0x41 || c >= lo_lim) {
                if (c < 0x61 || c >= lo2_lim) {
                    val = 0; status = 1; goto done;
                }
                sub = -0x57;
            } else {
                sub = -0x37;
            }
        } else {
            sub = -0x30;
        }
        digit = (uint8_t)(c + sub);
        if ((uint8_t)(val * (uint8_t)radix) > 0xff - digit) {
            val = 0; status = 1; goto done;
        }
        val = (uint8_t)(val * (uint8_t)radix + digit);
    }
    if (negative)
        val = (uint8_t)-val;
done:
    return (uint32_t)(val & 0xff) | (status << 8);
}

/* FUN_000b1aac @ 0xb1aac   (est. sk_parse_u8)
 * Parse an 8-bit number (16-bit accumulator overflow check).
 * Confidence: high */
static uint32_t sk_parse_u8(const uint8_t *s, long len, long radix)
{
    uint8_t val = 0;
    uint32_t status = 0;
    uint8_t hi_lim, lo_lim, lo2_lim;
    long pos = 0;
    int negative = 0;

    if (len < 1) __builtin_trap();
    hi_lim = (uint8_t)(radix + 0x30);
    lo_lim = 0x41;
    lo2_lim = 0x61;
    if (radix > 10) {
        lo_lim = (uint8_t)(radix + 0x37);
        lo2_lim = (uint8_t)(radix + 0x57);
    }
    if (s[0] == '+') {
        pos = 1;
        if (pos >= len) { val = 0; status = 1; goto done; }
    } else if (s[0] == '-') {
        pos = 1; negative = 1;
        if (pos >= len) { val = 0; status = 1; goto done; }
    }
    for (; pos < len; pos++) {
        uint8_t c = s[pos];
        int8_t sub;
        uint8_t digit;
        uint16_t acc;
        if (c < 0x30 || c >= hi_lim) {
            if (c < 0x41 || c >= lo_lim) {
                if (c < 0x61 || c >= lo2_lim) {
                    val = 0; status = 1; goto done;
                }
                sub = -0x57;
            } else {
                sub = -0x37;
            }
        } else {
            sub = -0x30;
        }
        digit = (uint8_t)(c + sub);
        acc = (uint16_t)((uint16_t)(val * (uint8_t)radix) + digit);
        if (acc > 0xff) {
            val = 0; status = 1; goto done;
        }
        val = (uint8_t)acc;
    }
    if (negative)
        val = (uint8_t)-val;
done:
    return (uint32_t)(val & 0xff) | (status << 8);
}

/* FUN_000b1d54 @ 0xb1d54   (est. sk_strdup)
 * Allocate a buffer of max(len,min_cap)+0x20 bytes, record len and cap.
 * Confidence: medium */
static uint8_t *sk_strdup(long len, long min_cap)
{
    uint8_t *buf;
    uint64_t h;

    if (min_cap <= len)
        min_cap = len;
    if (min_cap == 0)
        return (uint8_t *)&sk_str_empty;
    h = sk_atou();
    buf = (uint8_t *)sk_alloc_small(h, (uint64_t)min_cap + 0x20);
    {
        uint64_t tag = sk_reg_read(0);
        *(long *)(buf + 0x10) = len;
        *(long *)(buf + 0x18) = (long)(tag * 2) + -0x40;
    }
    return buf;
}

/* ------------------------------------------------------------------ *
 * Trap / deferral glue wrappers.
 * ------------------------------------------------------------------ */

static cl4_result_t sk_trap_msg_read(void)
{
    cl4_result_t r; r.lo = 0; r.hi = 0; return r;
}
static cl4_result_t sk_trap_msg_read2(uint64_t *a) { (void)a; return sk_trap_msg_read(); }
static cl4_result_t sk_trap_msg_read3(uint64_t *a, uint64_t s1, uint64_t s2, uint64_t s3)
{ (void)a; (void)s1; (void)s2; (void)s3; return sk_trap_msg_read(); }
static void sk_parse_store2(uint64_t a, uint64_t b, uint64_t v) { (void)a; (void)b; (void)v; }
static cl4_result_t sk_common_consume(uint64_t a)
{ cl4_result_t r; r.lo = 0; r.hi = a; return r; }
static cl4_result_t sk_msg_enter2(void) { return sk_trap_msg_read(); }
static void sk_common_consume2(void) { }
static void sk_common_dispatch2(void) { }
static void sk_common_done(void) { }
static void sk_common_exit(void) { }
static void sk_common_clear(void) { }
static void sk_common_flush(void) { }
static void sk_common_dispatch(void) { }
static cl4_result_t sk_msg_enter(void) { return sk_trap_msg_read(); }
static void sk_handle(void) { }

/* FUN_000b02dc @ 0xb02dc   (est. sk_trap_defer) */
static void sk_trap_defer(void) { sk_trap_defer2(); }
/* FUN_000b077c @ 0xb077c   (est. sk_trap_defer_b) */
static void sk_trap_defer_b(void) { sk_trap_defer2(); }
/* thunk_FUN_000b02dc @ 0xb4184 */
static void sk_trap_defer_thunk(void) { sk_trap_defer(); }
/* thunk_FUN_000b077c @ 0xb4188 */
static void sk_trap_defer_b_thunk(void) { sk_trap_defer_b(); }

/* FUN_000b02f4 @ 0xb02f4   (est. sk_trap_defer2) — defer a pending trap to
 * the registered handler; returns its result. Confidence: medium
 * Notes: dispatch structure verified against decompile (preamble/read, the
 *   >>0x3c/>>0x3d three-level branch, handler dispatch, trap 0xb03cc);
 *   x21/x22 register forwarding rendered via sk_reg_val (opaque). */
static cl4_result_t sk_trap_defer2(void)
{
    cl4_result_t msg;
    extern cl4_result_t (*sk_trap_handler)(void); /* unaff_x19 */
    uint64_t flags = sk_reg_val;

    sk_common_preamble2(0, 0);
    sk_common_preamble();
    msg = sk_trap_msg_read();
    sk_common_exit();
    if ((sk_reg_val >> 0x3c & 1) != 0) {
        sk_common_clear();
        sk_handle();
        sk_common_flush();
    }
    if ((flags >> 0x3d & 1) == 0) {
        if ((sk_reg_val >> 0x3c & 1) == 0) {
            sk_common_clear();
            sk_msg_enter();
        } else {
            sk_common_consume(flags & 0xfffffffffffffff);
        }
        return sk_trap_handler();
    }
    sk_common_dispatch();
    {
        cl4_result_t r = sk_trap_handler();
        if (sk_reg_val != 0) {
            cL4_ref_release(flags);
            __builtin_trap();
        }
        return r;
    }
}

/* FUN_000b03cc @ 0xb03cc   (est. sk_trap_defer3) */
static void sk_trap_defer3(void) { sk_trap_defer4(); }
/* FUN_000b03e4 @ 0xb03e4   (est. sk_trap_defer3_b) */
static void sk_trap_defer3_b(void) { sk_trap_defer4(); }
/* FUN_000b03fc @ 0xb03fc   (est. sk_trap_defer4) — 40-bit result */
static uint64_t sk_trap_defer4(void) { return sk_trap_defer2().lo & 0xffffffffff; }
/* FUN_000b05d4 @ 0xb05d4   (est. sk_trap_defer5) — 24-bit result */
static uint32_t sk_trap_defer5(void) { return (uint32_t)(sk_trap_defer2().lo & 0xffffff); }
/* FUN_000b04cc @ 0xb04cc   (est. sk_trap_defer5_b) */
static void sk_trap_defer5_b(void) { sk_trap_defer6(); }
/* FUN_000b05bc @ 0xb05bc   (est. sk_trap_defer5_c) */
static void sk_trap_defer5_c(void) { sk_trap_defer6(); }
static void sk_trap_defer6(void) { sk_trap_defer2(); }

/* FUN_000b04e4 @ 0xb04e4   (est. sk_trap_parse_store) */
static void sk_trap_parse_store(uint64_t a, uint64_t b, uint64_t out)
{
    sk_parse_store_impl(a, b, out, 0);
}
/* FUN_000b06a4 @ 0xb06a4   (est. sk_trap_parse_store2)
 * Parses/stores via the u8 path: reads the message, unwinds on the high
 * failure tag, then forwards (msg.lo, msg.hi, out) to the store callee
 * FUN_000b1aac. On the no-arg (dropped) dispatch path it calls the same
 * callee with a zeroed third word and traps if msg.lo is non-null.
 * Confidence: medium */
static void sk_trap_parse_store2(uint64_t a, uint64_t b, uint64_t out)
{
    cl4_result_t msg;

    cL4_ref_acquire(b);
    sk_common_preamble();
    msg = sk_trap_msg_read2(&a);
    if ((msg.hi >> 0x3c & 1) != 0) {
        sk_common_consume2();
        sk_handle();
        sk_common_exit();
        cL4_ref_release(msg.hi);
        msg.hi = sk_reg_val;
    }
    if ((msg.hi >> 0x3d & 1) == 0) {
        if ((msg.lo >> 0x3c & 1) == 0) {
            sk_common_consume2();
            msg = sk_msg_enter2();
        } else {
            msg = sk_common_consume(msg.hi & 0xfffffffffffffff);
        }
        sk_parse_store2(msg.lo, msg.hi, out);   /* FUN_000b1aac(msg.lo, msg.hi, param_3) */
    } else {
        sk_common_dispatch2();
        sk_parse_store2(msg.lo, msg.hi, 0);     /* FUN_000b1aac() (args dropped) */
        if (msg.lo != 0) {
            cL4_ref_release(msg.lo);
            __builtin_trap();                   /* SoftwareBreakpoint(1,0xb077c) */
        }
    }
    cL4_ref_release(msg.hi);
    sk_common_done();
}

/* common implementation retained for the 04e4 (signed) wrapper
 * sk_trap_parse_store; mirrors the 06a4 body modulo the `which` parse
 * selection. */
static void sk_parse_store_impl(uint64_t a, uint64_t b, uint64_t out, int which)
{
    cl4_result_t msg;
    uint64_t v;

    cL4_ref_acquire(b);
    sk_common_preamble();
    msg = sk_trap_msg_read2(&a);
    if ((msg.hi >> 0x3c & 1) != 0) {
        sk_common_consume2();
        sk_handle();
        sk_common_exit();
        cL4_ref_release(msg.hi);
        msg.hi = sk_reg_val;
    }
    if ((msg.hi >> 0x3d & 1) == 0) {
        if ((msg.lo >> 0x3c & 1) == 0) {
            sk_common_consume2();
            msg = sk_msg_enter2();
        } else {
            msg = sk_common_consume(msg.hi & 0xfffffffffffffff);
        }
        v = which ? sk_parse_u8((const uint8_t *)msg.lo, (long)msg.hi, (long)out)
                  : sk_parse_u8_signed((const uint8_t *)msg.lo, (long)msg.hi, (long)out);
        sk_parse_store2(msg.lo, msg.hi, v);
    } else {
        sk_common_dispatch2();
        sk_parse_store2(msg.lo, msg.hi, 0);
        if (msg.lo != 0) {
            cL4_ref_release(msg.lo);
            __builtin_trap();
        }
    }
    cL4_ref_release(msg.hi);
    sk_common_done();
}

/* FUN_000b0794 @ 0xb0794   (est. sk_trap_parse_store3)
 * Confidence: medium
 * Notes: Verified against decompile: acquire(d), msg_read3(4 strings),
 *   >>0x3c/>>0x3d dispatch, parse-store, release(hi), done, trap 0xb0888.
 *   Register forwarding (unaff_x22 -> sk_reg_val) opaque. */
static void sk_trap_parse_store3(uint64_t a, uint64_t b, uint64_t c,
                                 uint64_t d, uint64_t out)
{
    cl4_result_t msg;
    uint64_t v;

    cL4_ref_acquire(d);
    msg = sk_trap_msg_read3(&a, 0x675c68, 0x66e720, 0x66e6e0);
    if ((msg.hi >> 0x3c & 1) != 0) {
        sk_common_consume2();
        sk_handle();
        sk_common_exit();
        cL4_ref_release(msg.hi);
        msg.hi = sk_reg_val;
    }
    if ((msg.hi >> 0x3d & 1) == 0) {
        if ((msg.lo >> 0x3c & 1) == 0) {
            sk_common_consume2();
            msg = sk_msg_enter2();
        } else {
            msg = sk_common_consume(msg.hi & 0xfffffffffffffff);
        }
        v = sk_parse_u8((const uint8_t *)msg.lo, (long)msg.hi, (long)out);
        sk_parse_store2(msg.lo, msg.hi, v);
    } else {
        sk_common_dispatch2();
        sk_parse_store2(msg.lo, msg.hi, 0);
        if (msg.lo != 0) {
            cL4_ref_release(msg.lo);
            __builtin_trap();
        }
    }
    cL4_ref_release(msg.hi);
    sk_common_done();
    (void)b; (void)c;
}

/* FUN_000b1e08 @ 0xb1e08   (est. sk_htbl_insert_alloc)
 * Insert a key into a dynamic hash table grown to hold n entries.
 * Confidence: low */
static uint8_t *sk_htbl_insert_alloc(long n, uint8_t keep, uint64_t cb,
                                     uint64_t v0, uint64_t v1, uint64_t v2)
{
    uint8_t *t = sk_htbl_empty;
    uint64_t pos;
    (void)keep; (void)cb; (void)v0; (void)v1; (void)v2;

    if (n < 0) __builtin_trap();
    if (n != 0) {
        while (sk_htbl_count((uint64_t *)t) < (uint64_t)n) {
            sk_htbl_grow_pair(1);
            t = (uint8_t *)sk_reg_word;
        }
    }
    pos = 0;
    while (t[0x38 / 8 + (pos >> 6)] >> (pos & 0x3f) & 1)
        pos++;
    {
        uint64_t *slot = (uint64_t *)(t + 0x30);
        slot[pos * 4 / 8 + 0] = v0;
        slot[pos * 4 / 8 + 1] = v1;
        slot[pos * 4 / 8 + 2] = v2;
    }
    t[2]++;
    return t;
}

/* FUN_000b4094 @ 0xb4094   (est. sk_htbl_callback_store) */
static void sk_htbl_callback_store(uint64_t *out, uint64_t buf, long n,
                                   void (*cb)(uint64_t *, uint64_t, long))
{
    uint64_t local;
    if (n < 0) __builtin_trap();
    if (n != 0)
        sk_bzero((void *)buf, (uint64_t)n << 3);
    cb(&local, buf, n);
    if (sk_reg_val == 0)
        *out = local;
}
/* FUN_000b411c @ 0xb411c   (est. sk_htbl_callback_store_a) */
static void sk_htbl_callback_store_a(uint64_t *out, uint64_t buf)
{
    uint64_t *f = sk_reg_word;
    sk_htbl_callback_store(out, buf, (long)f[0x18 / 8],
                           (void (*)(uint64_t *, uint64_t, long))f[0x20 / 8]);
}
/* FUN_000b4120 @ 0xb4120   (est. sk_htbl_callback_store_b) */
static void sk_htbl_callback_store_b(uint64_t *out, uint64_t buf)
{
    sk_htbl_callback_store_a(out, buf);
}

/* ------------------------------------------------------------------ *
 * Register-based small helpers (many trivial/empty).
 * ------------------------------------------------------------------ */

/* FUN_000b41a4 @ 0xb41a4   (est. sk_common_preamble) — no-op preamble.
 * Confidence: high */
static void sk_common_preamble(void) { }
/* FUN_000b41c4 @ 0xb41c4   (est. sk_fatal_error_str) */
static const char *sk_fatal_error_str(void) { return "Fatal error"; }
/* FUN_000b41d8 @ 0xb41d8   (est. sk_noop_1) — no-op. Confidence: high */
static void sk_noop_1(void) { }
/* FUN_000b41f0 @ 0xb41f0   (est. sk_noop_2) — no-op. Confidence: high */
static void sk_noop_2(void) { }
/* FUN_000b4200 @ 0xb4200   (est. sk_noop_3) — no-op. Confidence: high */
static void sk_noop_3(void) { }
/* FUN_000b4218 @ 0xb4218   (est. sk_noop_4) — no-op. Confidence: high */
static void sk_noop_4(void) { }
/* FUN_000b4228 @ 0xb4228   (est. sk_trap_frame) */
static cl4_result_t sk_trap_frame(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)(uintptr_t)__builtin_frame_address(0);
    r.hi = ((uint64_t)sk_reg_word >> 0x38) & 0xf;
    return r;
}
/* FUN_000b4244 @ 0xb4244   (est. sk_noop_5) — no-op. Confidence: high */
static void sk_noop_5(void) { }
/* FUN_000b4254 @ 0xb4254   (est. sk_trap_frame2) */
static cl4_result_t sk_trap_frame2(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)(uintptr_t)__builtin_frame_address(0);
    r.hi = (sk_reg_val >> 0x38) & 0xf;
    return r;
}
/* FUN_000b4270 @ 0xb4270   (est. sk_noop_6) — no-op. Confidence: high */
static void sk_noop_6(void) { }
/* FUN_000b4280 @ 0xb4280   (est. sk_push_slot) */
static void sk_push_slot(void)
{
    uint64_t idx = sk_reg_val2();
    *(uint64_t *)((uint8_t *)sk_reg_word + idx * 8 + 0x20) = sk_reg_val3();
    *(uint64_t *)((uint8_t *)sk_reg_word + 0x10) = idx + 1;
}
/* FUN_000b4294 @ 0xb4294   (est. sk_noop_7) — no-op. Confidence: high */
static void sk_noop_7(void) { }
/* FUN_000b42b8 @ 0xb42b8   (est. sk_ptr_tag) */
static uint64_t sk_ptr_tag(uint64_t p)
{
    return (p & 0xffffffffffffull) | 0xd000000000000000ull;
}
/* FUN_000b42c0 @ 0xb42c0   (est. sk_noop_8) — no-op. Confidence: high */
static void sk_noop_8(void) { }
/* FUN_000b42d4 @ 0xb42d4   (est. sk_deref_byte) */
static uint8_t sk_deref_byte(uint8_t *p) { return *p; }
/* FUN_000b42e4 @ 0xb42e4   (est. sk_noop_9) — no-op. Confidence: high */
static void sk_noop_9(void) { }
/* FUN_000b42f8 @ 0xb42f8   (est. sk_fatal_error_str2) */
static const char *sk_fatal_error_str2(void) { return "Fatal error"; }
/* FUN_000b430c @ 0xb430c   (est. sk_noop_10) — no-op. Confidence: high */
static void sk_noop_10(void) { }
/* FUN_000b4344 @ 0xb4344   (est. sk_noop_11) — no-op. Confidence: high */
static void sk_noop_11(void) { }
/* FUN_000b4354 @ 0xb4354   (est. sk_noop_12) — no-op. Confidence: high */
static void sk_noop_12(void) { }
/* FUN_000b4368 @ 0xb4368   (est. sk_writeln) */
static void sk_writeln(void)
{
    extern void sk_writeln_tag(uint64_t a, uint64_t b); /* thunk_FUN_002acbb8 */
    sk_writeln_tag(0x6920656c69687720ull, 0xef676e697865646eull);
}
/* FUN_000b4390 @ 0xb4390   (est. sk_noop_13) — no-op. Confidence: high */
static void sk_noop_13(void) { }
/* FUN_000b439c @ 0xb439c   (est. sk_noop_14) — no-op. Confidence: high */
static void sk_noop_14(void) { }
/* FUN_000b43bc @ 0xb43bc   (est. sk_common_preamble2) — acquire ref */
static void sk_common_preamble2(uint64_t a, uint64_t b)
{
    (void)a;
    cL4_ref_acquire(b);
}
/* FUN_000b43d0 @ 0xb43d0   (est. sk_noop_15) — no-op. Confidence: high */
static void sk_noop_15(void) { }
/* FUN_000b43dc @ 0xb43dc   (est. sk_frame_descriptor) */
static cl4_result_t sk_frame_descriptor(uint64_t p)
{
    cl4_result_t r;
    r.lo = p + 0x20;
    r.hi = sk_reg_val & 0xffffffffffffull;
    return r;
}
/* FUN_000b43e8 @ 0xb43e8   (est. sk_noop_16) — no-op. Confidence: high */
static void sk_noop_16(void) { }
/* FUN_000b43f4 @ 0xb43f4   (est. sk_noop_17) — no-op. Confidence: high */
static void sk_noop_17(void) { }
/* FUN_000b43fc @ 0xb43fc   (est. sk_trap_consume) */
static void sk_trap_consume(void)
{
    extern void sk_trap_consume_op(void); /* FUN_000aba2c */
    sk_trap_consume_op();
}
/* FUN_000b4408 @ 0xb4408   (est. sk_noop_18) — no-op. Confidence: high */
static void sk_noop_18(void) { }
/* FUN_000b4418 @ 0xb4418   (est. sk_noop_19) — no-op. Confidence: high */
static void sk_noop_19(void) { }
/* FUN_000b4428 @ 0xb4428   (est. sk_noop_20) — no-op. Confidence: high */
static void sk_noop_20(void) { }
/* FUN_000b4438 @ 0xb4438   (est. sk_noop_21) — no-op. Confidence: high */
static void sk_noop_21(void) { }
/* FUN_000b4448 @ 0xb4448   (est. sk_low16) */
static uint32_t sk_low16(void)
{
    return (uint32_t)(sk_reg_val & 0xff) | ((sk_reg_val >> 8 & 0xff) << 8);
}
/* FUN_000b4458 @ 0xb4458   (est. sk_noop_22) — no-op. Confidence: high */
static void sk_noop_22(void) { }
/* FUN_000b4470 @ 0xb4470   (est. sk_parse_len) */
static uint64_t sk_parse_len(void) { return sk_reg_read(0); }
/* FUN_000b4488 @ 0xb4488   (est. sk_frame_store) */
static void sk_frame_store(void)
{
    sk_reg_store_frame(0xd00000000000002aull, sk_reg_read(0));
}
/* FUN_000b44a0 @ 0xb44a0   (est. sk_abort) */
static void sk_abort(void) { sk_noreturn(); }
/* FUN_000b44ac @ 0xb44ac   (est. sk_htbl_insert_alloc_max) */
static void sk_htbl_insert_alloc_max(void)
{
    sk_htbl_insert_alloc(0x7fffffffffffffffll, 1, 0, 0, 0, 0);
}
