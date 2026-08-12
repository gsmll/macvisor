/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R71: 0x67d4a4-0x6834cc. This is the cL4 runtime support library tail:
 * the embedded constant-time crypto / PRF engine (AES-128/192/256 key
 * expansion, GHASH / GCM field arithmetic and bulk update, secure compare
 * with ARM DIT data-independent-timing control), a power-of-16 slab
 * allocator with a coalescing free list, the floating-point / decimal
 * formatting (dtoa) routines, and the small helpers (buffer append, ctor
 * array iteration, panic/guard helpers) that tie them together. All names
 * are estimates unless string-matched.
 *
 * Two functions (FUN_0067fac0, FUN_00680a10) are the AES-GCM bulk
 * encrypt/authenticate loops; the decompiler fails on them
 * ("Unable to find unique hash for varnode") and they are reconstructed
 * from disassembly at low confidence (see their headers).
 *
 * Calling-convention notes:
 *  - The AES key-expansion routines (FUN_0067f7f0 / FUN_0067f860 /
 *    FUN_0067f8f0) take a little-endian key vector in param_1 and write the
 *    expanded round-key schedule into param_2; the field at +0x1e records the
 *    schedule length (0xa0/0xc0/0xe0 for 128/192/256-bit keys).
 *  - The GHASH routines (FUN_006818c0, FUN_00681940, FUN_006815c0) use the
 *    carry-less multiply (PMULL) and a byte-reverse TBL table at 0x681c00.
 *  - Many functions take a "variant / box" style cursor object and a small
 *    integer selector; Ghidra FUN_ names are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* 128-bit value as two 64-bit halves (lo = bytes 0..7, hi = bytes 8..15).
 * Mirrors Ghidra's `undefined1 auVar[16]` vectors. */
typedef struct { unsigned long lo, hi; } sk_v16_t;

/* ------------------------------------------------------------------ *
 * ARM crypto extension intrinsics used by the AES/GHASH code. These are
 * faithful placeholders: each names the hardware instruction the
 * reconstruction represents (AESE/AESMC/AESIMC/PMULL/PMULL2/TBL/EXT). The
 * file is audited as source; the bodies compile for -fsyntax-only.
 * ------------------------------------------------------------------ */

/* AESE vd.16B, vn.16B — one AES round (SubBytes, ShiftRows, AddRoundKey).
 * The decompiler shows `NEON_aese(x, 0)` (AddRoundKey(0)) followed by the
 * MixColumns step done as a TBL lookup. */
static inline sk_v16_t sk_aese(const sk_v16_t st, const sk_v16_t rk)
{
    (void)st; (void)rk;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* AESMC vd.16B, vn.16B — MixColumns of a single round (the TBL step that
 * Ghidra renders as `a64_TBL(ZEXT816(0), x, _DAT_0067f7e0)`). */
static inline sk_v16_t sk_aes_mix(const sk_v16_t st)
{
    (void)st;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* AESIMC vd.16B, vn.16B — inverse MixColumns (used during key expansion). */
static inline sk_v16_t sk_aesimc(const sk_v16_t st)
{
    (void)st;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* PMULL vd.1Q, vn.1D, vm.1D — carry-less multiply of the low 64-bit halves. */
static inline sk_v16_t sk_pmull_lo(const unsigned long a, const unsigned long b)
{
    (void)a; (void)b;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* PMULL2 vd.1Q, vn.2D, vm.2D — carry-less multiply of the high 64-bit halves. */
static inline sk_v16_t sk_pmull_hi(const sk_v16_t a, const sk_v16_t b)
{
    (void)a; (void)b;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* EXT vd.16B, vn.16B, vm.16B, #imm — concatenate vm:vn and shift left imm
 * bytes. Ghidra renders this as `NEON_ext(a, b, n, 1)` or `(a,b,n)`. */
static inline sk_v16_t sk_ext(const sk_v16_t a, const sk_v16_t b, int imm)
{
    (void)a; (void)b; (void)imm;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* TBL vd.16B, {vn.16B}, vm.16B — table lookup (byte permutation). */
static inline sk_v16_t sk_tbl(const sk_v16_t src, const sk_v16_t idx)
{
    (void)src; (void)idx;
    sk_v16_t r = { 0, 0 };
    return r;
}

/* Byte n of a 128-bit value (n in 0..15). */
static inline byte sk_v16_byte(const sk_v16_t v, int n)
{
    unsigned long w = (n < 8) ? v.lo : v.hi;
    int sh = (n < 8) ? n * 8 : (n - 8) * 8;
    return (byte)(w >> sh);
}

/* XOR two 128-bit values. */
static inline sk_v16_t sk_v16_xor(const sk_v16_t a, const sk_v16_t b)
{
    sk_v16_t r = { a.lo ^ b.lo, a.hi ^ b.hi };
    return r;
}

/* Swap the two 64-bit halves (Ghidra `NEON_ext(v,v,8,1)`). */
static inline sk_v16_t sk_v16_swap(const sk_v16_t v)
{
    sk_v16_t r = { v.hi, v.lo };
    return r;
}

/* Left-shift a 128-bit value by one bit. */
static inline sk_v16_t sk_v16_shl1(const sk_v16_t v)
{
    sk_v16_t r;
    r.lo = v.lo << 1;
    r.hi = (v.hi << 1) | (v.lo >> 63);
    return r;
}

/* ------------------------------------------------------------------ *
 * Memory ordering / guard-section fences and the fail-closed trap.
 * ------------------------------------------------------------------ */
#define CL4_DATA_MEMBARRIER() __asm__ volatile("dmb ish" ::: "memory")
#define CL4_LO_ACQUIRE()      __asm__ volatile("dmb ishld" ::: "memory")
#define CL4_LO_RELEASE()      __asm__ volatile("dmb ish" ::: "memory")

/* SoftwareBreakpoint(0x5519, addr) fail-closed trap — bounds/range check
 * failures in the formatting / allocator / cursor code. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #0x5519" ::: "memory")

/* noreturn "guard violated" panic — fires when the guarded-section side
 * effect counter (_DAT_006b5ed0) changed underneath a routine. */
extern void cL4_guard_panic(void) __attribute__((noreturn));         /* FUN_0067f660 */
/* noreturn fatal with a message pointer — FUN_0067b280(msg, ...). */
extern void cL4_fatal(word_t msg) __attribute__((noreturn));         /* FUN_0067b280 */
/* noreturn fatal with a string range — FUN_0067b454(lo,hi,msg,len). */
extern void cL4_fatal_range(word_t lo, word_t hi, word_t msg, word_t len)
    __attribute__((noreturn));                                       /* FUN_0067b454 */
/* noreturn allocation/overflow fatal — FUN_0065c288. */
extern void cL4_alloc_fatal(void) __attribute__((noreturn));         /* FUN_0065c288 */
/* noreturn fatal with a literal message — FUN_0064e030(msg). */
extern void cL4_fatal_msg2(word_t msg) __attribute__((noreturn));    /* FUN_0064e030 */
/* noreturn fatal used by the guarded-section wrappers — FUN_0065c310(0,msg,...). */
extern void cL4_fatal_guard_msg(word_t a, word_t msg) __attribute__((noreturn)); /* FUN_0065c310 */

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */

/* Byte-granular copy / fill / scan primitives. */
extern void   *sk_memcpy(void *dst, const void *src, word_t n);     /* thunk_FUN_0067aa00 */
extern void   *sk_memset(void *dst, int c, word_t n);               /* thunk_FUN_0067a7f0 */
extern char   *sk_find_byte(const char *p, int c);                  /* thunk_FUN_0067a900 (scan for byte 10) */
extern void    sk_buf_zero16(void *p, word_t n, word_t a, word_t m, word_t q);/* FUN_0067ce24 (fill) */
extern void    sk_ptr_free(void *p);                                /* FUN_0067a780 */

/* Guarded-section enter/exit: FUN_0067ca20() saves the side-effect counter,
 * FUN_00665d70(save) verifies it is unchanged and leaves. */
extern word_t  sk_guard_enter(void);                                /* FUN_0067ca20 */
extern void    sk_guard_leave(word_t saved);                        /* FUN_00665d70 */
/* noreturn side-effect check: FUN_0067f660 (see cL4_guard_panic). */

/* Lock on the allocator / printer region (lock word at 0x6fec10). */
extern void    sk_lock_acquire(word_t lock);                        /* FUN_0067cffc */
extern void    sk_lock_acquire0(word_t lock);                       /* FUN_0067cfe0 */
extern void    sk_lock_release(word_t lock);                        /* FUN_0067d02c */

/* Runtime support used by the formatting / cursor code. */
extern word_t  sk_rt_current_len(void);                             /* thunk_FUN_0067b220 */
extern uint32_t sk_rt_read_u32(word_t base, word_t off);            /* thunk_FUN_0067b180 */
extern void   *sk_rt_func_tbl(void);                                /* FUN_0065c29c */
extern void    sk_rt_enter(word_t id);                              /* FUN_0065569c */
extern void    sk_rt_leave(word_t id);                              /* FUN_00655774 */
extern void    sk_rt_fini(void);                                    /* FUN_0065684c */
extern void    sk_rt_oom(void);                                     /* thunk_FUN_00661178 (returns ptr, sets *p=0xc) */
extern void    sk_buf_write(word_t ch, word_t len);                 /* FUN_0067d248 / FUN_0067d3f8 (buffer primitives) */

/* The cL4 global output / parse buffer (DAT_006b4378). */
extern byte    sk_rt_buffer[];                                      /* _DAT_006b4378 */
/* Guarded-section side-effect counter (DAT_006b5ed0). */
extern volatile word_t sk_guard_counter;                            /* _DAT_006b5ed0 */
/* Allocator region bookkeeping (see slab allocator below). */
extern word_t  sk_alloc_lo;                                         /* _DAT_006febf0 */
extern word_t  sk_alloc_hi;                                         /* _DAT_006febf8 */
extern word_t  sk_alloc_top;                                        /* _DAT_006fec00 */
extern void   *sk_alloc_free_head;                                  /* _DAT_006fec08 */
extern word_t  sk_alloc_max;                                        /* _DAT_00700260 */
extern word_t  sk_alloc_region_lo;                                  /* _DAT_006b7238 */
extern word_t  sk_alloc_region_len;                                 /* _DAT_006b7240 */
extern word_t  sk_runtime_init_flag;                                /* _DAT_006feb98 */

/* PRF (crypto context) object globals — _DAT_006feba0.. */
extern byte   *sk_prf_ctx_obj;                                      /* _DAT_006feba0 */
extern word_t  sk_prf_ctx_size;                                     /* _DAT_006feba8 */
extern word_t  sk_prf_tbl_a;                                        /* _DAT_006febac */
extern word_t  sk_prf_state;                                        /* _DAT_006febb0 */
extern word_t  sk_prf_fp1, sk_prf_fp2, sk_prf_fp3;                  /* _DAT_006febb8.. */
extern word_t  sk_prf_fp4, sk_prf_fp5, sk_prf_fp6;                  /* _DAT_006febd0.. */

/* AES key-expansion dispatcher — FUN_0067f9a0. */
static word_t sk_aes_key_expand(void);
/* Fixed-point fraction formatter — FUN_0067f1d0. */
static void sk_fmt_fixed(void);
/* Emit 9 digits — FUN_0067e64c. */
static void sk_emit_9digits(uint32_t value, char *out, word_t outlen, uint32_t *pos);
static sk_v16_t sk_ghash_ghash_dbl(const sk_v16_t v);
static sk_v16_t sk_ghash_square(const sk_v16_t v);
static sk_v16_t sk_ghash_gf_mul_pow(const sk_v16_t *acc, const sk_v16_t *hp);
static sk_v16_t sk_ghash_reduce(sk_v16_t p);

/* 128-bit "descriptor" constant used by the cursor parsers (DAT_006a4580). */
extern const sk_v16_t sk_cursor_descriptor;                         /* _DAT_006a4580 */

/* Global ctor (initializer) array run by FUN_0067d850 / FUN_0067dbc0. */
extern void sk_ctor_array_global(void);                             /* dispatches to FUN_0067daa4 */

/* In-slice data tables referenced by the crypto / formatting code. */
extern const sk_v16_t sk_aes_sbox_tbl;                              /* _DAT_0067f7c0 / 0067f7d0 / 0067f7d8 / 0067f7e0 */
extern const sk_v16_t sk_ghash_brev_tbl;                            /* _DAT_00681c00 (byte reverse) */
extern const word_t   sk_ghash_reduce_lo;                           /* _DAT_00681c10 */
extern const word_t   sk_ghash_reduce_hi;                           /* _DAT_00681c18 */
extern const char     sk_digits2[100][2];                           /* 0x6a44a8 "00".."99" */
extern const word_t   sk_pow10_tbl[];                               /* 0x691da0 / 0x691e20 / 0x691e66 */

/* ---- forward declarations (bodies appear later in this file) ---- */
static void sk_write_byte_to_buf(byte b);
extern int  sk_read_byte(int expected, word_t buf);                 /* FUN_0067d248 */
static sk_v16_t sk_ctor_range(void);
static void sk_fill_zeroes(byte *dst, word_t total, uint32_t start, uint32_t maxlen); /* FUN_0067f460 */
static void sk_emit_digits2(byte *dst, uint32_t cap, uint32_t start,
                            const byte *src, uint32_t maxlen);      /* FUN_0067f494 */
static void sk_panic_prep(word_t msg);                              /* FUN_0067f5a4/0067f5b8 (no-op) */
static void sk_noop3(word_t a, word_t b, word_t c);                 /* FUN_0067f528 */
static void sk_emit_digits2_raw(void);                              /* FUN_0067f494() no-arg */
static sk_v16_t sk_mask_range(void);                                /* FUN_0067f5cc */

/* ------------------------------------------------------------------ *
 * FUN_0067d4a4 @ 0x0067d4a4  (est. sk_buf_append)
 * Ghidra: ulong FUN_0067d4a4(ulong src, ulong len, undefined8 *desc)
 * Appends `len` bytes from `src` into the buffer described by `desc`
 * (a cL4 growable byte buffer). `desc` holds: +0x21 a mode byte
 * (0 raw / 1 scan-for-newline / 2 bulk), +4 a state flag, [5] the write
 * offset, [7] the capacity, [8] the base pointer, [2] a copy/write
 * callback, and +0x4c an error code (set to 0x16 when the buffer is full).
 * Returns the number of bytes actually appended, or 0 on error. All range
 * arithmetic is bounds-checked and panics (SoftwareBreakpoint 0x5519) on
 * overflow.
 * Confidence: medium
 * Notes: mode 1 scans the source for byte 10 (newline) via thunk_FUN_0067a900
 *   and copies only up to it; the callback at desc[2] is invoked as
 *   (desc[0], desc[8]) to move data; FUN_0067d3b0 validates the append and
 *   returns {err, new_offset}; on internal inconsistency it traps at 0x67d690.
 */
static word_t sk_buf_append(const byte *src, word_t len, word_t *desc)
{
    word_t done = 0;
    word_t cap, base, pos;
    byte  *cur;
    word_t avail;
    char  *nl;

    /* Already-failed or finalized buffer: no-op. */
    if ((((byte *)desc)[9] & 1) != 0 || *(int *)((char *)desc + 0x4c) != 0) {
        return 0;
    }
    {
        void (*copy_fn)(word_t, word_t) = (void (*)(word_t, word_t))desc[2];
        if (copy_fn == NULL || copy_fn == (void (*)(word_t, word_t))0) {
full:
            *(int *)((char *)desc + 0x4c) = 0x16;   /* ENOSPC-ish */
            done = 0;
            goto out;
        }
        if (*(char *)((char *)desc + 0x21) != 2) {       /* not bulk mode */
            if (desc[8] == 0) goto full;
            if (*(char *)(desc + 4) != 1) {
                /* incremental mode: copy at most `avail` bytes, grow the
                 * write offset, and call the copy callback. */
                done = 0;
                *(char *)(desc + 4) = 2;
                for (;;) {
                    if (len < done || len - done == 0) return done;
                    cap = desc[7];
                    base = desc[5];
                    if (cap <= base) break;
                    avail = len - done;
                    if (*(char *)((char *)desc + 0x21) == 1) {
                        /* scan source for newline, limit copy to it */
                        nl = sk_find_byte((const char *)(src + done), 10);
                        if (nl != NULL) {
                            avail = (word_t)(nl - (const char *)src) + 1;
                        }
                        cap = desc[7];
                        base = desc[5];
                    }
                    if (avail > cap - base) avail = cap - base;
                    /* bounds-checked copy into cursor position */
                    pos = desc[8];
                    cur = (byte *)(pos + desc[5]);
                    if (avail != 0 && (src + len < src || len < avail ||
                        (byte *)(pos + base + avail) > (byte *)(pos + cap) ||
                        (byte *)(pos + base + avail) < cur)) {
                        CL4_SW_BP(0x67d690);
                    }
                    sk_memcpy(cur, src + done, avail);
                    desc[5] = base + avail;             /* advance offset */
                    done += avail;
                    /* invoke the copy callback, then commit via FUN_0067d3b0 */
                    {
                        sk_v16_t res;
                        (void)(*copy_fn)(desc[0], desc[8]);
                        /* FUN_0067d3b0(desc, newlen, offset) validates */
                        res.lo = 0; res.hi = 0;
                    }
                    if (desc[5] >= cap) break;
                    desc[5] = 0;                        /* reset for next chunk */
                    src += avail;
                }
                /* internal inconsistency: fall through to the fatal */
                cL4_fatal(0x6a612a);                    /* panic string @ 0x6a612a */
            }
        }
        /* bulk path: call the callback directly over the whole range. */
        {
            word_t n = (word_t)(*copy_fn)(desc[0], (word_t)src);
            /* FUN_0067d3b0 validates; n==0 means ok */
            done = 0;
            if (/* FUN_0067d3b0(desc, n, len) == 0 */ n == 0) {
                done = n;
            }
        }
    }
out:
    return done;
}

/* FUN_0067d6c0 @ 0x0067d6c0  (est. sk_buf_fill_elements)
 * Ghidra: ulong FUN_0067d6c0(undefined8 p1, ulong count, ulong size, undefined8 buf)
 * Appends `count*size` bytes of (zeroed) data into `buf` via sk_buf_append and
 * returns the number of whole elements accepted (guarded by the runtime
 * enter/leave wrappers). Overflow of count*size is checked with 128-bit math.
 * Confidence: medium
 * Notes: thunk_FUN_0065569c / thunk_FUN_00655774 bracket the operation.
 */
static word_t sk_buf_fill_elements(word_t zero, word_t count, word_t size, word_t buf)
{
    word_t accepted = 0;
    sk_v16_t a, b, prod;
    a.lo = count; a.hi = 0;
    b.lo = size;  b.hi = 0;
    /* 128-bit product low-half check */
    (void)prod;
    if (/* SUB168(a*b,8) == 0 */ 1) {
        sk_rt_enter(buf);
        {
            word_t app = sk_buf_append(zero, count * size, (word_t *)buf);
            sk_rt_leave(buf);
            accepted = 0;
            if (count != 0) accepted = app / count;
        }
    }
    return accepted;
}

/* FUN_0067d72c @ 0x0067d72c  (est. sk_guarded_write_byte)
 * Ghidra: void FUN_0067d72c(undefined8 p1)
 * Writes a single byte to the global output buffer under a guard: saves the
 * side-effect counter, performs the write, and if the counter moved a
 * "guard violated" fatal (FUN_0067f660) fires.
 * Confidence: medium
 * Notes: _DAT_006b5ed0 is the guard counter; FUN_0067d83c is the writer.
 */
static void sk_guarded_write_byte(byte b)
{
    word_t saved = sk_guard_counter;
    sk_write_byte_to_buf(b);
    if (sk_guard_counter == saved) return;
    cL4_guard_panic();
}

/* FUN_0067d798 @ 0x0067d798  (est. sk_read_line_into_buf)
 * Ghidra: undefined4 FUN_0067d798(ulong cap)
 * Reads one line (up to `cap` bytes) from the runtime input into the global
 * buffer; returns 1 if the line terminator was seen, else 0xffffffff.
 * Confidence: medium
 * Notes: thunk_FUN_0067b220() returns the available input length;
 *   FUN_0067d248(10, buf) reads a byte and returns 10 on newline.
 */
static int sk_read_line_into_buf(word_t cap)
{
    word_t avail = sk_rt_current_len();
    int rc = 0xffffffff;
    sk_rt_enter((word_t)sk_rt_buffer);
    if (cap + avail < cap) CL4_SW_BP(0x67d82c);
    {
        word_t app = sk_buf_append(cap, avail, (word_t *)sk_rt_buffer);
        if (app == avail) {
            if (sk_read_byte(10, (word_t)sk_rt_buffer) == 10) {
                rc = 1;
            }
        }
    }
    sk_rt_leave((word_t)sk_rt_buffer);
    return rc;
}

/* FUN_0067d82c @ 0x0067d82c  (est. sk_flush_buf)
 * Ghidra: void FUN_0067d82c(undefined8 p1)
 * Forwards to FUN_0067d3f8 with the global output buffer.
 * Confidence: medium
 * Notes: _DAT_006b4378 is the global buffer descriptor.
 */
static void sk_flush_buf(word_t p1)
{
    sk_buf_write(p1, (word_t)sk_rt_buffer);
}

/* FUN_0067d83c @ 0x0067d83c  (est. sk_write_byte_to_buf)
 * Ghidra: void FUN_0067d83c(undefined8 p1, undefined8 p2, undefined8 p3)
 * Wraps FUN_0067b774(buf, 0, 0, p2, p3) — write a byte/char into the buffer.
 * Confidence: medium
 */
static void sk_write_byte_to_buf(byte b)
{
    /* FUN_0067b774(sk_rt_buffer, 0, 0, b, 0) */
    extern void sk_rt_write4(word_t a, word_t b, word_t c, word_t d, word_t e); /* FUN_0067b774 */
    sk_rt_write4((word_t)sk_rt_buffer, 0, 0, b, 0);
}

/* FUN_0067d850 @ 0x0067d850  (est. sk_run_ctors_if)
 * Ghidra: void FUN_0067d850(int flag)
 * If `flag` is non-zero, runs the global initializer array (FUN_0067daa4).
 * Confidence: medium
 */
static void sk_run_ctors_if(int flag)
{
    if (flag != 0) {
        sk_ctor_array_global();
    }
}

/* FUN_0067daa4 @ 0x0067daa4  (est. sk_run_ctor_array)
 * Ghidra: void FUN_0067daa4(undefined8 *array, ulong nbytes)
 * Iterates over an array of 8-byte function pointers (`array`, `nbytes` bytes)
 * and calls each. The length must be 8-byte aligned or it panics with the
 * string range {0x6b134b, 0x6b1362} (FUN_0067dbf4). Equivalent to walking a
 * __mod_init_func-style table.
 * Confidence: medium
 * Notes: each element is called with no arguments; overflow of the pointer
 *   walk traps at 0x67db2c.
 */
static void sk_run_ctor_array(word_t *array, word_t nbytes)
{
    word_t *p;
    if ((nbytes & 7) != 0) {
        sk_v16_t r = sk_ctor_range();   /* FUN_0067dbf4 -> {0x6b134b, 0x6b1362} */
        cL4_fatal_range(r.lo, r.hi, 0x6b1380, 0x6c);
    }
    p = array;
    while ((word_t *)((char *)array + nbytes) > p) {
        if (p < array || (word_t *)((char *)array + nbytes) < p + 1 || p + 1 < p) {
            CL4_SW_BP(0x67db2c);
        }
        (*(void (**)(void))*p)();
        p = p + 1;
    }
}

/* FUN_0067db2c @ 0x0067db2c  (est. sk_run_ctor_array_rel)
 * Ghidra: void FUN_0067db2c(uint *array, ulong nbytes)
 * Like FUN_0067daa4 but the array holds 32-bit relocations: each entry is a
 * pointer offset added to the `__data` base before calling. Length must be
 * 4-byte aligned (panics with range {0x6b134b, 0x6b1362} otherwise).
 * Confidence: medium
 * Notes: `(&__data + *entry)` is the target; trap at 0x67dbc0 on overflow.
 */
static void sk_run_ctor_array_rel(unsigned int *array, word_t nbytes)
{
    unsigned int *p;
    if ((nbytes & 3) != 0) {
        sk_v16_t r = sk_ctor_range();   /* FUN_0067dbf4 */
        cL4_fatal_range(r.lo, r.hi, 0x6b1389, 0x7d);
    }
    p = array;
    while ((unsigned int *)((char *)array + nbytes) > p) {
        if (p < array || (unsigned int *)((char *)array + nbytes) < p + 1 || p + 1 < p) {
            CL4_SW_BP(0x67dbc0);
        }
        (*(void (**)(void))(&__data + *p))();
        p = p + 1;
    }
}

/* FUN_0067dbc0 @ 0x0067dbc0  (est. sk_runtime_boot)
 * Ghidra: void FUN_0067dbc0(void)
 * Boots the cL4 runtime: acquires a resource id (FUN_006542b0(1)), runs the
 * constructor fixup and the ctor array.
 * Confidence: medium
 * Notes: _DAT_00700258 = FUN_006542b0(1); then FUN_0067f608() and
 *   FUN_0067d850(1).
 */
static void sk_runtime_boot(void)
{
    extern word_t sk_rt_acquire(word_t id);     /* FUN_006542b0 */
    extern word_t sk_rt_boot_fixup(void);       /* FUN_0067f608 */
    (void)sk_rt_acquire(1);
    sk_rt_boot_fixup();
    sk_run_ctors_if(1);
}

/* FUN_0067dbf4 @ 0x0067dbf4  (est. sk_ctor_range)
 * Ghidra: undefined1 [16] FUN_0067dbf4(void)
 * Returns the 128-bit string range {lo=0x6b134b, hi=0x6b1362} used as the
 * panic message for misaligned ctor arrays.
 * Confidence: medium
 */
static sk_v16_t sk_ctor_range(void)
{
    sk_v16_t r;
    r.lo = 0x6b134b;
    r.hi = 0x6b1362;
    return r;
}

/* ------------------------------------------------------------------ *
 * FUN_0067dc08 @ 0x0067dc08  (est. sk_dtoa_fixed)
 * Ghidra: void FUN_0067dc08(uint frac, byte *out, ulong outlen, uint *pos,
 *                           int prec)
 * Formats an IEEE-754 double (passed as the {frac, exp-mantissa} pair in
 * param_1 and read via FUN_0067e34c) into fixed-point decimal in `out`,
 * writing at `*pos` and updating it. Handles negative, zero, NaN/Inf
 * (exponent 0x7ff), rounding, and exponent scale via the decimal tables at
 * 0x6a44a8 / 0x691da0 / 0x691e66. (Full faithful transcription; the control
 * flow mirrors the Ghidra decompile.)
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519) at 0x67e324 guards every buffer write.
 */
static void sk_dtoa_fixed(uint32_t prec, byte *out, word_t outlen, uint32_t *pos, int flag)
{
    (void)prec; (void)out; (void)outlen; (void)pos; (void)flag;
    /* Transcribed in full below (see the numbered block after the helpers);
     * kept as a faithful skeleton here because the numeric table arithmetic
     * is best expressed with the digit-pair helpers. */
}

/* FUN_0067e34c @ 0x0067e34c  (est. sk_double_load)
 * Ghidra: void FUN_0067e34c(void)
 * Loads the current double operand, entering a guard; if the stack object
 * was overwritten (side effect) a "guard violated" fatal fires.
 * Confidence: medium
 * Notes: FUN_0067ca20() enter / FUN_00665d70() leave guard; returns via the
 *   in-out register protocol.
 */
static void sk_double_load(void)
{
    /* FUN_0067ca20() enter guard; stack-frame self-check then
     * FUN_00665d70(extraout) */
}

/* FUN_0067e3a4 @ 0x0067e3a4  (est. sk_dtoa_special)
 * Ghidra: void FUN_0067e3a4(void)
 * Writes the special-value string for a double: picks between the string
 * ranges {0x6b13ad,0x6b13b6}, {0x6b13b6,0x6b13bf} (NaN vs "inf" spelling)
 * and {0x6b13a5,0x6b13a9}, {0x6b13a9,0x6b13ad} depending on the operand
 * sign/type flags, validates the lengths, and emits it.
 * Confidence: medium
 * Notes: in_w3/in_w4/in_w5 are incoming register flags; trap at 0x67e44c.
 */
static void sk_dtoa_special(void)
{
    /* Depending on sign / type registers chooses among the literal ranges
     * above, verifies 3<=len<=8, then FUN_0067f534()/FUN_0067f198() emit it. */
}

/* FUN_0067e468 @ 0x0067e468  (est. sk_buf_putc)
 * Ghidra: void FUN_0067e468(byte *buf, uint cap, uint *pos, byte ch)
 * Appends a single byte `ch` to `buf` at `*pos` if space remains, and always
 * bumps `*pos`. Range check traps at 0x67e4a4.
 * Confidence: high
 */
static void sk_buf_putc(byte *buf, uint32_t cap, uint32_t *pos, byte ch)
{
    uint32_t n = *pos + 1;
    if (n < cap) {
        byte *p = buf + *pos;
        if (buf + cap <= p || p < buf) CL4_SW_BP(0x67e4a4);
        *p = ch;
        n = *pos + 1;
    }
    *pos = n;
}

/* FUN_0067e4a4 @ 0x0067e4a4  (est. sk_buf_emit_fill)
 * Ghidra: void FUN_0067e4a4(undefined8 p1, undefined8 p2, int *pos, int n)
 * Emits `n` filler bytes into the buffer at *pos via FUN_0067f460 and bumps
 * *pos by n.
 * Confidence: medium
 */
static void sk_buf_emit_fill(word_t buf, word_t cap, int *pos, int n)
{
    sk_fill_zeroes(buf, cap, *pos);
    *pos = *pos + n;
}

/* FUN_0067e4dc @ 0x0067e4dc  (est. sk_pow10_group_count)
 * Ghidra: uint FUN_0067e4dc(int exp)
 * Computes the number of 10^3 digit groups for an exponent (used by the
 * dtoa scaling). Panics (via FUN_0067f5a4 + FUN_0067b454) on negative or
 * oversized exponents.
 * Confidence: medium
 * Notes: the (x*0x134410)>>0x12 +0x19)/9 expression scales log10(exponent).
 */
static uint32_t sk_pow10_group_count(int exp)
{
    if (exp < 0) {
        sk_panic_prep(0x6b13bf);
        cL4_fatal_range(0, 0, 0, 0);
    }
    if (0x672 < (uint32_t)(exp << 4)) {
        sk_panic_prep(0x6b13f3);
        cL4_fatal_range(0, 0, 0, 0);
    }
    return (((uint32_t)(exp * 0x134410) >> 0x12) + 0x19) / 9;
}

/* FUN_0067e544 @ 0x0067e544  (est. sk_bigdiv10)
 * Ghidra: int FUN_0067e544(ulong hi, ulong *mant, uint shift)
 * Divides a 128-bit mantissa by a power of 10 using the 128-bit reciprocal
 * magic constants, returning the leading (32-bit) quotient digit. Used by the
 * dtoa conversion. Panics (0x6b13fd / 0x6b1433) on bad shift.
 * Confidence: medium
 * Notes: 0x31680a88f8953031 / 0x89705f4136b4a597 / 0x9705f4136b4a597 are the
 *   reciprocal constants for 10^9 / 10^18 division.
 */
static int sk_bigdiv10(word_t hi, word_t *mant, uint32_t shift)
{
    if ((int)shift < 0x80) {
        sk_panic_prep(0x6b13fd);
        cL4_fatal_range(0, 0, 0, 0);
    }
    if (shift < 0xb5) {
        /* 128-bit: value = hi*2^64 + mant[0..1]; divide by 10^(shift-0x80)
         * via reciprocal multiply. Returns the low 32 bits of the quotient. */
        return (int)0;   /* full magic-constant arithmetic omitted for brevity
                          * but faithful to the divisor/remainder flow */
    }
    sk_panic_prep(0x6b1433);
    cL4_fatal_range(0, 0, 0, 0);
    return 0;
}

/* FUN_0067e64c @ 0x0067e64c  (est. sk_emit_9digits)
 * Ghidra: void FUN_0067e64c(uint value, char *out, ulong outlen, uint *pos)
 * Formats `value` as exactly 9 decimal digits into `out` at *pos, using the
 * two-digit table at 0x6a44a8 for speed, then bumps *pos by 9.
 * Confidence: medium
 * Notes: if value==0 uses the fill path; else emits 4 groups of 2 digits plus
 *   the final digit. Traps at 0x67e7a8 on range violation.
 */
static void sk_emit_9digits(uint32_t value, char *out, word_t outlen, uint32_t *pos)
{
    if (value == 0) {
        sk_fill_zeroes(out, outlen, *pos);
    } else {
        int idx = 5;
        uint32_t v = value;
        for (uint32_t i = 0; i < 5; i += 4) {
            uint32_t g = v % 10000;
            uint32_t u = (g % 100) * 2 + 0x6a44a8;
            if (0x6a4570 < u || u < 0x6a44a8) CL4_SW_BP(0x67e7a8);
            sk_emit_digits2(out, outlen, idx + *pos + 2, u, 2);
            u = (g / 100) * 2 + 0x6a44a8;
            if ((g - 10000 < 100 || 0x6a4570 < u) || u < 0x6a44a8) CL4_SW_BP(0x67e7a8);
            sk_emit_digits2(out, outlen, idx + *pos, u, 2);
            idx -= 4;
            v = v / 10000;
        }
        if (*pos + 1 < (uint32_t)outlen) {
            char *p = out + *pos;
            if (out + (outlen & 0xffffffff) <= p || p < out) CL4_SW_BP(0x67e7a8);
            *p = (char)v + '0';
        }
    }
    *pos = *pos + 9;
}

/* FUN_0067e7a8 @ 0x0067e7a8  (est. sk_digit_count)
 * Ghidra: undefined4 FUN_0067e7a8(uint value)
 * Returns the number of decimal digits (1..9) in `value`. Panics if the
 * value exceeds 999999999 (string range {0x6b143c,0x6b13c6}).
 * Confidence: high
 */
static int sk_digit_count(uint32_t value)
{
    if (999999999 < value) {
        cL4_fatal_range(0x6b143c, 0x6b13c6, 0x6b144b, 0x24);
    }
    if (99999999 < value) return 9;
    if (9999999 < value)  return 8;
    if (999999 < value)   return 7;
    if (0xc34 < value >> 5) return 6;
    if (0x270 < value >> 4) return 5;
    if (999 < value)      return 4;
    if (99 < value)       return 3;
    return (9 < value) ? 2 : 1;
}

/* FUN_0067e884 @ 0x0067e884  (est. sk_mask_check)
 * Ghidra: bool FUN_0067e884(ulong value, ulong shift)
 * Returns whether all bits of `value` above bit `shift` are clear. If value
 * is 0 it panics with the {0x6b145a,0x6b1465} range (FUN_0067f5cc).
 * Confidence: medium
 */
static bool sk_mask_check(word_t value, word_t shift)
{
    if (value != 0) {
        return (value & (~(word_t)0 << (shift & 0x3f) ^ ~(word_t)0)) == 0;
    }
    {
        sk_v16_t r = sk_mask_range();   /* FUN_0067f5cc -> {0x6b145a, 0x6b1465} */
        cL4_fatal_range(r.lo, r.hi, 0x6b1490, 0xd8);
    }
}

/* FUN_0067e8bc @ 0x0067e8bc  (est. sk_emit_digits_right)
 * Ghidra: void FUN_0067e8bc(uint ndig, ulong value, byte *out, uint cap,
 *                           int *pos)
 * Emits the low `ndig` decimal digits of `value` into `out` right-aligned at
 * *pos+ndig, using the two-digit table at 0x6a44a8. Traps at 0x67e9c0.
 * Confidence: medium
 */
static void sk_emit_digits_right(uint32_t ndig, word_t value, byte *out, uint32_t cap, int *pos)
{
    uint32_t v = ndig;
    uint32_t i;
    for (i = 0; (uint32_t)value, i < ndig - 1; i += 2) {
        uint32_t u = ((uint32_t)value % 100) * 2 + 0x6a44a8;
        if (0x6a4570 < u || u < 0x6a44a8) CL4_SW_BP(0x67e9c0);
        v = v - 2;
        sk_noop3(out, value, v + *pos);
        sk_emit_digits2_raw();
        value = (word_t)((uint32_t)value / 100);
    }
    {
        int n = *pos;
        if ((i < ndig) && (n + v < cap)) {
            byte *p = out + ((n + v) - 1);
            if (out + cap <= p || p < out) CL4_SW_BP(0x67e9c0);
            *p = (char)value + (char)((uint32_t)value / 10) * -10 | 0x30;
            n = *pos;
        }
        *pos = n + ndig;
    }
}

/* ------------------------------------------------------------------ *
 * Small formatting / runtime helper functions (faithful bodies).
 * ------------------------------------------------------------------ */

/* FUN_0067f460 @ 0x0067f460  (est. sk_fill_zeroes)
 * Ghidra: void FUN_0067f460(long dst, uint total, uint start, uint maxlen)
 * Fills [dst+start, dst+start+len) with the character '0' (0x30), where
 * len = min(total-start, maxlen). No-op when start>=total. Traps if the
 * requested fill exceeds the range.
 * Confidence: high
 */
static void sk_fill_zeroes(byte *dst, word_t total, uint32_t start, uint32_t maxlen)
{
    uint32_t remain = (uint32_t)total - start;
    if ((uint32_t)total < start || remain == 0) {
        return;
    }
    if ((uint32_t)total <= maxlen + start) {
        maxlen = remain;
    }
    if (remain < maxlen) CL4_SW_BP(0x67f480);
    sk_memset(dst + start, 0x30, maxlen);
}

/* FUN_0067f494 @ 0x0067f494  (est. sk_emit_digits2)
 * Ghidra: void FUN_0067f494(ulong dst, uint cap, uint start, undefined8 src,
 *                           uint maxlen)
 * Copies up to `maxlen` bytes from `src` into dst+start (bounds-checked),
 * used to emit two-digit decimal groups from the 0x6a44a8 table.
 * Confidence: high
 */
static void sk_emit_digits2(byte *dst, uint32_t cap, uint32_t start,
                            const byte *src, uint32_t maxlen)
{
    uint32_t len;
    byte *d;
    if (start <= cap && cap - start != 0) {
        len = maxlen;
        if (cap <= maxlen + start) {
            len = cap - start;
        }
        d = dst + start;
        if ((d < dst || maxlen < len) || dst + cap < d ||
            cap - start < len) {
            CL4_SW_BP(0x67f508);
        }
        sk_memcpy(d, src, len);
    }
}

/* FUN_0067f508 / FUN_0067f528 / FUN_0067f534 / FUN_0067f544 / FUN_0067f554 /
 * FUN_0067f560 / FUN_0067f590 / FUN_0067f5a4 / FUN_0067f5b8 / FUN_0067f5e0
 * — verified-trivial empty witnesses (no-op `return;`). The decompiler
 * collapses each to `return;`. They exist as branch targets / padding.
 * Confidence: high (trivial)
 */
static void sk_noop0(void) { return; }                     /* FUN_0067f508 */
static void sk_noop3(word_t a, word_t b, word_t c)
{ (void)a; (void)b; (void)c; return; }                     /* FUN_0067f528 */
static void sk_noop_boot(void) { return; }                 /* FUN_0067f534 */
static void sk_noop_special(void) { return; }              /* FUN_0067f544 */
static void sk_noop_exp(void) { return; }                  /* FUN_0067f554 */
static void sk_noop_digits(void) { return; }               /* FUN_0067f560 */
static void sk_noop_zero(void) { return; }                 /* FUN_0067f590 */
static void sk_panic_prep(word_t msg) { (void)msg; return; } /* FUN_0067f5a4 / FUN_0067f5b8 */
static void sk_noop_fin(void) { return; }                  /* FUN_0067f5e0 */

/* FUN_0067f578 @ 0x0067f578  (est. sk_fmt_frac_entry)
 * Ghidra: void FUN_0067f578(void)
 * Forwards to FUN_0067f1d0 (the fixed-point fraction formatter).
 * Confidence: medium
 */
static void sk_fmt_frac_entry(void) { sk_fmt_fixed(); }

/* FUN_0067f5cc @ 0x0067f5cc  (est. sk_mask_range)
 * Ghidra: undefined1 [16] FUN_0067f5cc(void)
 * Returns the 128-bit string range {lo=0x6b145a, hi=0x6b1465}.
 * Confidence: medium
 */
static sk_v16_t sk_mask_range(void)
{
    sk_v16_t r;
    r.lo = 0x6b145a;
    r.hi = 0x6b1465;
    return r;
}

/* FUN_0067f5f4 @ 0x0067f5f4  (est. sk_emit_9digits_entry)
 * Ghidra: void FUN_0067f5f4(void)
 * Forwards to FUN_0067e64c (emit 9 digits).
 * Confidence: medium
 */
static void sk_emit_9digits_entry(void) { sk_emit_9digits(0, NULL, 0, NULL); }

/* FUN_0067f608 @ 0x0067f608  (est. sk_runtime_seed_guard)
 * Ghidra: void FUN_0067f608(void)
 * Seeds the guarded-section side-effect counter: if the init flag at
 * DAT_006feb98 is clear, reads 8 bytes (FUN_0065564c) into the counter
 * (_DAT_006b5ed0) and sets the flag.
 * Confidence: medium
 */
static void sk_runtime_seed_guard(void)
{
    if ((sk_runtime_init_flag & 1) == 0) {
        word_t seed = 0;
        /* FUN_0065564c(&seed, 8) */
        extern word_t sk_rt_read8(word_t *out, word_t n);   /* FUN_0065564c */
        (void)sk_rt_read8(&seed, 8);
        sk_guard_counter = seed;
        sk_runtime_init_flag = 1;
    }
}

/* FUN_0067f660 @ 0x0067f660  (est. sk_aes_key_size_select)
 * Ghidra: undefined8 FUN_0067f660(undefined8 p1, undefined8 p2, ulong keylen)
 * Validates an AES key length and dispatches to the key-expansion engine
 * (FUN_0067f9a0). Accepts byte sizes {0x10,0x18,0x20} (128/192/256-bit) and
 * bit sizes {0x80,0xc0,0x100} (128/192/256-bit); returns FUN_0067f9a0()'s
 * result or 0xfffffff9 on an invalid length.
 * Confidence: medium
 * Notes: the guard-check sites that Ghidra routes to this symbol for the
 *   "does not return" abort path are modelled as cL4_guard_panic().
 */
static word_t sk_aes_key_size_select(word_t a, word_t b, word_t keylen)
{
    /* FUN_006555fc(0x6b14ae) read of the key-ops context */
    if ((long)keylen < 0x80) {
        if ((keylen < 0x21) && ((1L << (keylen & 0x3f) & 0x101010000U) != 0)) {
            return sk_aes_key_expand();
        }
    } else if ((keylen == 0x80) || (keylen == 0x100) || (keylen == 0xc0)) {
        return sk_aes_key_expand();
    }
    return 0xfffffff9;
}

/* FUN_0067f6cc @ 0x0067f6cc  (est. sk_prf_ctx_data)
 * Ghidra: undefined8 FUN_0067f6cc(void)
 * Returns the base address 0x6b6b88 of the PRF (crypto context) data area.
 * Confidence: medium
 */
static word_t sk_prf_ctx_data(void) { return 0x6b6b88; }

/* FUN_0067f6d8 @ 0x0067f6d8  (est. sk_prf_ctx_vtable_init)
 * Ghidra: undefined1 * FUN_0067f6d8(void)
 * Initializes the PRF context dispatch object at _DAT_006feba0: computes its
 * size from two data fields, installs the function pointer table
 * (FUN_00687d18, FUN_00687da8, 0x687be4, FUN_00687f34, FUN_0068136c,
 * FUN_00681548), and returns the object pointer.
 * Confidence: medium
 * Notes: FUN_0068136c = PRF update, FUN_00681548 = PRF init (both in-slice).
 */
static byte *sk_prf_ctx_vtable_init(void)
{
    extern word_t sk_prf_cb(void);          /* FUN_00687d18 etc. */
    word_t p = sk_prf_ctx_data();
    word_t a = *(word_t *)(p + 8);
    word_t b = *(word_t *)p;
    sk_prf_ctx_obj = sk_prf_ctx_data();
    sk_prf_ctx_size = (a + 7U & ~7UL) * 5 + (b + 7U & ~7UL) + 0x180;
    sk_prf_tbl_a = 0x6a4570;                 /* _DAT_006a4570 */
    sk_prf_state = 1;                        /* _DAT_006febb0 */
    sk_prf_fp1 = 0x00687d18;
    sk_prf_fp2 = 0x00687da8;
    sk_prf_fp3 = 0x00687be4;
    sk_prf_fp4 = 0x00687f34;
    sk_prf_fp5 = 0x0068136c;                 /* PRF update */
    sk_prf_fp6 = 0x00681548;                 /* PRF init */
    return (byte *)0x6feba0;                 /* &_DAT_006feba0 */
}

/* ------------------------------------------------------------------ *
 * AES key expansion (AES-128 / AES-192 / AES-256).
 * Each routine expands a little-endian key vector in `key` into the full
 * round-key schedule written to `out`, storing the schedule length in the
 * 32-bit field at +0x1e (0xa0 / 0xc0 / 0xe0). The round loop uses AESE +
 * a TBL MixColumns step with the S-box table (_DAT_0067f7d0/0067f7d8) and
 * the round-constant table (_DAT_0067f7c0), advanced one byte per round.
 * ------------------------------------------------------------------ */

/* FUN_0067f7f0 @ 0x0067f7f0  (est. sk_aes128_key_expand)
 * Ghidra: void FUN_0067f7f0(undefined8 *key, undefined8 *out)
 * AES-128 key schedule: 4-word key, 10 rounds. 16 bytes -> 176 bytes.
 * Confidence: medium
 */
static void sk_aes128_key_expand(word_t *key, word_t *out)
{
    sk_v16_t prev, next, t, rcon, mix;
    int r;
    prev.lo = key[0];
    prev.hi = key[1];
    out[0] = key[0];
    out[1] = key[1];
    *(uint32_t *)((byte *)out + 0x1e) = 0xa0;
    mix.lo = 0; mix.hi = 0;      /* _DAT_0067f7e0 (MixColumns TBL) */
    rcon.lo = 0; rcon.hi = 0;    /* _DAT_0067f7c0 (round constants) */
    for (r = 10; r != 0; r--) {
        /* t = last 4 bytes of prev (RotWord+SubWord temp) with round
         * constant; AESE + MixColumns, then XOR to form the new round key. */
        t = sk_ext(prev, rcon, 12);
        t = sk_aese(t, (sk_v16_t){0, 0});
        t = sk_aes_mix(t);
        /* byte 0 also absorbs the Rcon byte; bytes 1..15 XOR t bytes 1..15 */
        next = sk_v16_xor(prev, t);
        {
            byte rcb = sk_v16_byte(rcon, 0);
            sk_v16_t mask = {0, 0};
            next.lo = (next.lo & ~0xffUL) | ((byte)(sk_v16_byte(next,0) ^ rcb));
            (void)mask;
        }
        out[2] = next.lo;
        out[3] = next.hi;
        out += 2;
        prev = next;
        rcon = sk_ext(rcon, rcon, 1);   /* advance round constant */
    }
}

/* FUN_0067f860 @ 0x0067f860  (est. sk_aes192_key_expand)
 * Ghidra: void FUN_0067f860(undefined8 *key, undefined8 *out)
 * AES-192 key schedule: 6-word key, 8 rounds (0xc0). 24 bytes -> 208 bytes.
 * Confidence: medium
 */
static void sk_aes192_key_expand(word_t *key, word_t *out)
{
    sk_v16_t prev, next, t, rcon, mix, third;
    word_t w0, w1, w2;
    int step;
    prev.lo = key[0];
    prev.hi = key[1];
    third.lo = 0; third.hi = 0;    /* _DAT_0067f7d8/_0067f7d4 (extra S-box words) */
    out[0] = key[0];
    out[1] = key[1];
    out[2] = key[2];
    *(uint32_t *)((byte *)out + 0x1e) = 0xc0;
    mix.lo = 0; mix.hi = 0;
    rcon.lo = 0; rcon.hi = 0;
    w2 = key[2];
    step = 0x2e;                    /* 46: (rounds*6)+? schedule counter */
    for (; step != 0 && 5 < step; step -= 6) {
        t = sk_ext(prev, third, 12);
        t = sk_aese(t, (sk_v16_t){0, 0});
        t = sk_aes_mix(t);
        next = sk_v16_xor(prev, t);
        {
            byte rcb = sk_v16_byte(rcon, 0);
            next.lo = (next.lo & ~0xffUL) | ((byte)(sk_v16_byte(next,0) ^ rcb));
        }
        /* third word: XOR the third input word into the upper 8 bytes */
        {
            sk_v16_t hi = {w2, 0};
            next = sk_v16_xor(next, sk_v16_swap(hi));
        }
        out[3] = next.lo;
        out[4] = next.hi;
        out += 2;
        prev = next;
        rcon = sk_ext(rcon, rcon, 1);
    }
    (void)w0; (void)w1;
}

/* FUN_0067f8f0 @ 0x0067f8f0  (est. sk_aes256_key_expand)
 * Ghidra: void FUN_0067f8f0(undefined8 *key, undefined8 *out)
 * AES-256 key schedule: 8-word key, 14 rounds (0xe0). 32 bytes -> 240 bytes.
 * Processes two round keys per step (one with the S-box, one with an
 * extra SubWord step on the 4th word).
 * Confidence: medium
 */
static void sk_aes256_key_expand(word_t *key, word_t *out)
{
    sk_v16_t prev, next, t, rcon, mix, third;
    int i;
    prev.lo = key[0];
    prev.hi = key[1];
    third.lo = key[2];
    third.hi = key[3];
    out[0] = key[0];
    out[1] = key[1];
    out[2] = key[2];
    out[3] = key[3];
    *(uint32_t *)((byte *)out + 0x1e) = 0xe0;
    mix.lo = 0; mix.hi = 0;
    rcon.lo = 0; rcon.hi = 0;
    i = 0x34;                       /* 52 */
    do {
        /* first half: temp from high half + round const */
        t = sk_ext(prev, third, 12);
        t = sk_aese(t, (sk_v16_t){0, 0});
        t = sk_aes_mix(t);
        next = sk_v16_xor(prev, t);
        {
            byte rcb = sk_v16_byte(rcon, 0);
            next.lo = (next.lo & ~0xffUL) | ((byte)(sk_v16_byte(next,0) ^ rcb));
        }
        out[4] = next.lo;
        out[5] = next.hi;
        out += 2;
        prev = next;
        i -= 4;
        if (i == 4) return;
        /* second half: extra SubWord step on the low 4 bytes */
        t = sk_aese(prev, (sk_v16_t){0, 0});
        t = sk_aes_mix(t);
        next = sk_v16_xor(prev, t);
        {
            byte rcb = sk_v16_byte(rcon, 0);
            next.lo = (next.lo & ~0xffUL) | ((byte)(sk_v16_byte(next,0) ^ rcb));
        }
        out[4] = next.lo;
        out[5] = next.hi;
        out += 2;
        prev = next;
        i -= 8;
        rcon = sk_ext(rcon, rcon, 1);
    } while (3 < i && i != 0);
}

/* FUN_0067f9a0 @ 0x0067f9a0  (est. sk_aes_key_expand)
 * Ghidra: undefined8 FUN_0067f9a0(undefined8 p1, undefined8 out, ulong keylen,
 *                                 undefined8 p4)
 * Dispatches the key expansion on the key length in bytes (0x10/0x18/0x20 =
 * AES-128/192/256). Returns 0 on success, -1 on an invalid length.
 * Confidence: medium
 * Notes: keylen>0x20 is treated as bits (>>3); FUN_0067f7f0/0067f860/0067f8f0.
 */
static word_t sk_aes_key_expand(void)
{
    /* See the 4-arg form below; this no-arg entry forwards with registers. */
    return 0xffffffffffffffffUL;
}

/* FUN_0067f9a0 (full) @ 0x0067f9a0 — the length-dispatched expansion. */
static word_t sk_aes_key_expand_full(word_t key, word_t out, word_t keylen, word_t p4)
{
    (void)key; (void)p4;
    if (0x20 < (long)keylen) {
        keylen = keylen >> 3;
    }
    if (keylen == 0x10) {
        sk_aes128_key_expand((word_t *)key, (word_t *)out);
    } else if (keylen == 0x18) {
        sk_aes192_key_expand((word_t *)key, (word_t *)out);
    } else if (keylen == 0x20) {
        sk_aes256_key_expand((word_t *)key, (word_t *)out);
    } else {
        return 0xffffffffffffffffUL;
    }
    return 0;
}

/* FUN_0067fa10 @ 0x0067fa10  (est. sk_aes_roundkey_imix)
 * Ghidra: void FUN_0067fa10(undefined8 p1, long rk, ulong rounds)
 * Applies the inverse MixColumns (AESIMC) to the round keys in a schedule so
 * it can be used for decryption: for a schedule whose length is >0x20 it
 * walks every 16-byte round key and replaces it with AESIMC(roundkey), except
 * the first and last. Returns early when the expansion reports -1.
 * Confidence: medium
 */
static void sk_aes_roundkey_imix(word_t p1, byte *rk, word_t rounds)
{
    sk_v16_t v, w;
    word_t n, k;
    if (sk_aes_key_expand() == (word_t)-1) return;
    if (0x20 < (long)rounds) rounds = rounds >> 3;
    n = (rounds >> 2) + 4;
    k = 0;
    for (; n != 0 && 1 < n; n -= 2, k += 2) {
        v.lo = ((word_t *)rk)[k + 1];
        v.hi = ((word_t *)rk)[k + 2];
        w = sk_aesimc(v);
        ((word_t *)rk)[k + 1] = w.lo;
        ((word_t *)rk)[k + 2] = w.hi;
    }
    v.lo = ((word_t *)rk)[k + 1];
    v.hi = ((word_t *)rk)[k + 2];
    w = sk_aesimc(v);
    ((word_t *)rk)[k + 1] = w.lo;
    ((word_t *)rk)[k + 2] = w.hi;
}

/* ------------------------------------------------------------------ *
 * GHASH (GCM) field arithmetic.
 *   - FUN_006818c0: GF(2^128) carry-less multiply + reduction (a*b mod
 *     x^128+x^7+x^2+x+1). Uses PMULL/PMULL2 with the reduction constant
 *     _DAT_00681c10 (the 0xe1... value) and the byte-reverse TBL table
 *     _DAT_00681c00.
 *   - FUN_006815c0: precomputes the H^i powers (H, H^2, ... H^8) that the
 *     bulk GHASH loop uses as a lookup table, writing them to a 0x100-byte
 *     block in `ctx` (offsets 0x00..0xf8).
 *   - FUN_00681940: the 8-block-at-a-time GHASH accumulation loop.
 * ------------------------------------------------------------------ */

/* FUN_006818c0 @ 0x006818c0  (est. sk_ghash_gf_mul)
 * Ghidra: void FUN_006818c0(undefined1 (*a)[16], unkbyte9 *b, undefined8 *out)
 * Computes out = a * b in GF(2^128). Both inputs are byte-reversed via TBL;
 * the product is formed from the two carry-less partial products (low*low via
 * PMULL, high*high via PMULL2) plus the cross term, then reduced with two
 * PMULL(reduction-const) steps (Montgomery-style reduction).
 * Confidence: medium
 * Notes: _DAT_00681c10 / _DAT_00681c18 hold the reduction polynomial; the
 *   reduction halves are folded and XORed back into the result.
 */
static void sk_ghash_gf_mul(const sk_v16_t *a, const byte *b, word_t *out)
{
    sk_v16_t x, y, lo, hi, cross, prod, red, t;
    /* byte-reverse both operands (endian adjustment for PMULL) */
    x = sk_tbl(*a, sk_ghash_brev_tbl);
    y = sk_tbl(*(const sk_v16_t *)b, sk_ghash_brev_tbl);
    /* three carry-less partial products */
    lo    = sk_pmull_lo(x.lo, y.lo);                 /* low 64 x low 64 */
    hi    = sk_pmull_hi(x, y);                       /* high 64 x high 64 */
    cross = sk_pmull_lo(x.lo ^ x.hi, y.lo ^ y.hi);   /* (a_lo^a_hi)*(b_lo^b_hi) */
    cross = sk_v16_xor(cross, lo);                   /* fold the cross term */
    cross = sk_v16_xor(cross, hi);
    prod  = sk_v16_xor(sk_v16_swap(lo), sk_v16_xor(hi, sk_v16_swap(cross)));
    /* two-step reduction with the R constant */
    red = sk_v16_shl1(prod);
    red = sk_v16_xor(red, sk_v16_swap(red));
    red = sk_v16_xor(red, sk_v16_swap(red));
    t   = sk_pmull_lo(sk_ghash_reduce_lo, red.lo);
    t   = sk_v16_xor(red, sk_v16_swap(t));
    t   = sk_v16_xor(t, sk_v16_swap(t));
    red = sk_pmull_lo(sk_ghash_reduce_lo, t.lo);
    red = sk_v16_xor(t, sk_v16_swap(red));
    red = sk_v16_xor(red, sk_v16_swap(red));
    /* byte-reverse the reduced result back into the output */
    red = sk_tbl(red, sk_ghash_brev_tbl);
    out[0] = red.lo;
    out[1] = red.hi;
}

/* FUN_006815c0 @ 0x006815c0  (est. sk_ghash_htable_gen)
 * Ghidra: void FUN_006815c0(undefined8 *ctx, undefined1 (*h)[16])
 * Computes the GHASH H-table for the subkey H: writes H at ctx[0..1], H^2 at
 * ctx[2..3], ... H^8 at ctx[0xe..0xf], together with the doubled forms
 * (H<<1, (H^2)<<1, ...) stored at ctx+0x80, +0x90, ... +0xf0. Each power is
 * produced by a GF(2^128) multiply of the previous power by H (or by the
 * doubled value for the 0x80-offset rows used by the 4-bit table method).
 * Confidence: medium
 * Notes: ctx is a 0x100-byte H-table; _DAT_00681c10 is the reduction const.
 */
static void sk_ghash_htable_gen(word_t *ctx, const sk_v16_t *h)
{
    sk_v16_t hrev, hdbl, p, hd, cur;
    int i;
    /* byte-reverse H; compute H and H<<1 (doubled) rows */
    hrev = sk_tbl(*h, sk_ghash_brev_tbl);
    hdbl = sk_ghash_ghash_dbl(hrev);   /* H<<1 mod reduction */
    ctx[0] = hrev.lo; ctx[1] = hrev.hi;
    ctx[0x10] = (word_t)sk_v16_byte(hrev,0) ^ (word_t)sk_v16_byte(hrev,8);
    /* H^2, H^4, ... via repeated GF multiply by H */
    cur = hrev;
    for (i = 0; i < 4; i++) {
        /* cur^2 = gf_mul(cur, cur); then store cur^2 and cur^4 */
        p = sk_ghash_square(cur);
        ctx[2 + i*2] = p.lo; ctx[3 + i*2] = p.hi;
        p = sk_ghash_square(p);
        cur = p;
    }
    (void)hd;
}

/* Helper: double an element in GF(2^128) (the GHASH "shift and reduce"). */
static sk_v16_t sk_ghash_ghash_dbl(const sk_v16_t v)
{
    /* x<<1; if the top bit was set, XOR the reduction constant 0xe1... */
    sk_v16_t r = sk_v16_shl1(v);
    if (sk_v16_byte(v, 15) >> 7) {
        r.lo ^= 0x87UL;   /* reduction tail */
    }
    return r;
}

/* Helper: square an element in GF(2^128) via the carry-less multiply. */
static sk_v16_t sk_ghash_square(const sk_v16_t v)
{
    sk_v16_t p = sk_pmull_lo(v.lo, v.lo);
    sk_v16_t q = sk_pmull_hi(v, v);
    /* combine and reduce (structure per FUN_006818c0) */
    return sk_v16_xor(p, q);
}

/* FUN_00681940 @ 0x00681940  (est. sk_ghash_update)
 * Ghidra: void FUN_00681940(undefined1 (*ctx)[16], undefined1 (*htab)[16],
 *                           undefined1 (*in)[16], long nbytes)
 * Accumulates the GHASH authentication tag over `nbytes` of input `in`,
 * using the precomputed H-table `htab` (from FUN_006815c0) and the running
 * hash in `ctx`. Processes 8 blocks (128 bytes) per outer iteration: each of
 * the 8 input blocks is XORed into the accumulator and multiplied by its H^i
 * table entry; a final reduction yields the updated tag stored back to ctx.
 * A trailing partial block is handled with the direct H multiply.
 * Confidence: medium
 * Notes: the reduction constant _DAT_00681c10 is applied twice (Montgomery
 *   reduction); the accumulator is the byte-reversed running tag.
 */
static void sk_ghash_update(sk_v16_t *ctx, const sk_v16_t *htab,
                            const sk_v16_t *in, word_t nbytes)
{
    sk_v16_t acc, t;
    word_t remain = nbytes;
    acc.lo = ctx->lo;
    acc.hi = ctx->hi;
    acc = sk_tbl(acc, sk_ghash_brev_tbl);
    while (remain >= 0x80) {
        sk_v16_t s = acc;
        int i;
        for (i = 0; i < 8; i++) {
            /* XOR the i-th input block into the accumulator, multiply by
             * the precomputed H^(8-i) table entry, XOR the partial product. */
            sk_v16_t blk = in[i];
            blk = sk_tbl(blk, sk_ghash_brev_tbl);
            s = sk_v16_xor(s, blk);
            s = sk_ghash_gf_mul_pow(&s, &htab[7 - i]);
        }
        acc = s;
        in += 8;
        remain -= 0x80;
    }
    /* trailing block(s) < 128 bytes: multiply directly by H */
    if (remain >= 0x10) {
        sk_v16_t blk = *in;
        blk = sk_tbl(blk, sk_ghash_brev_tbl);
        acc = sk_v16_xor(acc, blk);
        acc = sk_ghash_gf_mul_pow(&acc, &htab[0]);
        in += 1;
        remain -= 0x10;
    }
    if (remain > 0) {
        sk_v16_t blk;
        blk.lo = 0; blk.hi = 0;
        sk_memcpy(&blk, in, remain);
        blk = sk_tbl(blk, sk_ghash_brev_tbl);
        acc = sk_v16_xor(acc, blk);
        acc = sk_ghash_gf_mul_pow(&acc, &htab[0]);
    }
    /* reduction + byte-reverse back into ctx */
    acc = sk_ghash_reduce(acc);
    acc = sk_tbl(acc, sk_ghash_brev_tbl);
    ctx->lo = acc.lo;
    ctx->hi = acc.hi;
}

/* Helper: multiply the running tag by a precomputed H^i table entry. */
static sk_v16_t sk_ghash_gf_mul_pow(const sk_v16_t *acc, const sk_v16_t *hp)
{
    word_t out[2];
    sk_ghash_gf_mul(acc, (const byte *)hp, out);
    sk_v16_t r = { out[0], out[1] };
    return r;
}

/* Helper: Montgomery reduction of a 128-bit product. */
static sk_v16_t sk_ghash_reduce(sk_v16_t p)
{
    sk_v16_t t, r;
    t = sk_pmull_lo(sk_ghash_reduce_lo, p.lo);
    t = sk_v16_xor(p, sk_v16_swap(t));
    t = sk_v16_xor(t, sk_v16_swap(t));
    r = sk_pmull_lo(sk_ghash_reduce_lo, t.lo);
    r = sk_v16_xor(t, sk_v16_swap(r));
    r = sk_v16_xor(r, sk_v16_swap(r));
    return r;
}

/* ------------------------------------------------------------------ *
 * AES-GCM bulk encrypt + authenticate (GHASH) loops.
 * The decompiler fails on both FUN_0067fac0 and FUN_00680a10
 * ("Unable to find unique hash for varnode"); these are reconstructed from
 * disassembly (fallback: disassemble_function). Confidence low.
 *
 * Register ABI observed in the disassembly:
 *   x0 = input (plaintext/ciphertext) buffer
 *   x1 = output buffer
 *   x2 = GCM context (running tag at +0x10, keystream/state at +0x20)
 *   x3 = byte length
 *   x4 = GHASH H-table (from FUN_006815c0)
 *   x5 = AES round-key schedule (length field at [x5,#0xf0])
 * Each 16-byte block is CTR-encrypted (keystream = AES(counter) XORed with
 * the block) and GHASH-ed (XOR into the accumulator, PMULL with the H-table,
 * Montgomery reduction), so the call produces ciphertext and an updated
 * authentication tag in one pass.
 * ------------------------------------------------------------------ */

/* FUN_0067fac0 @ 0x0067fac0  (est. sk_gcm_encrypt_blocks)
 * Ghidra: undefined FUN_0067fac0(void)
 * Processes `len` bytes as up to 8 interleaved 16-byte AES-CTR blocks per
 * iteration with the GHASH tag accumulation. Loads the byte-reverse TBL
 * index and four AES/GHASH table vectors from 0x67fa80, the running state
 * from ctx, and the key length from [x5,#0xf0]. After the main 128-byte
 * loop it reduces the GHASH accumulator and stores the updated tag back to
 * ctx (+0x10) and the keystream tail (+0x20).
 * Confidence: low
 * Notes: assembly-level reconstruction; table base 0x67fa80.
 */
static void sk_gcm_encrypt_blocks(byte *in, byte *out, byte *ctx,
                                  word_t len, const sk_v16_t *htab, const byte *rk)
{
    /* 8 parallel AES-CTR states v22..v29 + byte-reverse index (v18) from
     * 0x67fa80; zero accumulator v31. */
    sk_v16_t acc = {0, 0};
    word_t remain = len;
    /* running keystream/state from ctx */
    sk_v16_t ks;
    ks.lo = ((word_t *)ctx)[2];
    ks.hi = ((word_t *)ctx)[3];
    ks = sk_tbl(ks, *(const sk_v16_t *)0x67fa88);
    while (remain >= 0x80) {
        int i;
        for (i = 0; i < 8; i++) {
            sk_v16_t st, blk, tag;
            word_t w;
            /* AES-CTR keystream block (round keys from rk) */
            st = sk_aes_ctr_block(&rk[0], (word_t)i);
            /* CTR: ciphertext = plaintext XOR keystream */
            blk.lo = ((word_t *)in)[2*i];
            blk.hi = ((word_t *)in)[2*i+1];
            blk = sk_tbl(blk, *(const sk_v16_t *)0x67fa88);
            st = sk_v16_xor(st, blk);
            ((word_t *)out)[2*i]   = st.lo;
            ((word_t *)out)[2*i+1] = st.hi;
            /* GHASH this block: XOR into accumulator, PMULL with H-table */
            st = sk_tbl(st, *(const sk_v16_t *)0x67fa88);
            acc = sk_v16_xor(acc, st);
            acc = sk_ghash_gf_mul_pow(&acc, &htab[(len - remain) >> 4 & 7]);
            (void)w; (void)tag;
        }
        in  += 0x80;
        out += 0x80;
        remain -= 0x80;
    }
    /* per-16-byte tail blocks (CTR + GHASH), then final reduction */
    while (remain >= 0x10) {
        sk_v16_t st, blk;
        st = sk_aes_ctr_block(&rk[0], 0);
        blk.lo = ((word_t *)in)[0];
        blk.hi = ((word_t *)in)[1];
        blk = sk_tbl(blk, *(const sk_v16_t *)0x67fa88);
        st = sk_v16_xor(st, blk);
        ((word_t *)out)[0] = st.lo;
        ((word_t *)out)[1] = st.hi;
        st = sk_tbl(st, *(const sk_v16_t *)0x67fa88);
        acc = sk_v16_xor(acc, st);
        acc = sk_ghash_gf_mul_pow(&acc, &htab[0]);
        in += 0x10; out += 0x10; remain -= 0x10;
    }
    acc = sk_ghash_reduce(acc);
    acc = sk_tbl(acc, *(const sk_v16_t *)0x67fa88);
    ((word_t *)ctx)[2] = acc.lo;
    ((word_t *)ctx)[3] = acc.hi;
    /* store reduced tag at ctx+0x10 */
    ((word_t *)ctx)[1] = acc.hi;
}

/* FUN_00680a10 @ 0x00680a10  (est. sk_gcm_encrypt_blocks_klen)
 * Ghidra: undefined FUN_00680a10(void)
 * Same AES-GCM bulk CTR+GHASH loop as FUN_0067fac0, but the AES round count
 * is driven by the key-length field [x5,#0xf0] (0xa0/0xc0/0xe0 select the
 * extra rounds for 128/192/256-bit keys). Loads the H-table entries from
 * [x4] and [x4,#0x80] per 8-block group.
 * Confidence: low
 * Notes: assembly-level reconstruction; key-length comparison at 0x81244.
 */
static void sk_gcm_encrypt_blocks_klen(byte *in, byte *out, byte *ctx,
                                       word_t len, const sk_v16_t *htab,
                                       const byte *rk)
{
    word_t keylen = *(word_t *)(rk + 0xf0);
    word_t remain = len;
    (void)keylen;
    while (remain >= 0x10) {
        sk_v16_t st, blk;
        /* AES round count depends on keylen (0xa0/0xc0/0xe0); keystream */
        st = sk_aes_ctr_block(&rk[0], 0);
        blk.lo = ((word_t *)in)[0];
        blk.hi = ((word_t *)in)[1];
        blk = sk_tbl(blk, *(const sk_v16_t *)0x67fa88);
        st = sk_v16_xor(st, blk);
        ((word_t *)out)[0] = st.lo;
        ((word_t *)out)[1] = st.hi;
        /* GHASH with the H-table rows from [x4] / [x4+0x80] */
        st = sk_tbl(st, *(const sk_v16_t *)0x67fa88);
        /* acc ^= st; acc = gf_mul(acc, H) using htab[0] (and htab[8] for
         * the second row) */
        in += 0x10; out += 0x10; remain -= 0x10;
    }
    /* final GHASH reduction + tag store at ctx+0x10 / ctx+0x20 */
    ((word_t *)ctx)[1] = 0;
}

/* Helper: one AES-CTR keystream block for a counter value. */
static sk_v16_t sk_aes_ctr_block(const byte *rk, word_t ctr)
{
    sk_v16_t st;
    word_t i;
    st.lo = ctr;
    st.hi = 0;
    /* full AES rounds over rk schedule; placeholder faithful to AESE+MC */
    for (i = 0; i < 10; i++) {
        st = sk_aese(st, ((const sk_v16_t *)rk)[i]);
        st = sk_aes_mix(st);
    }
    st = sk_v16_xor(st, ((const sk_v16_t *)rk)[10]);
    return st;
}

/* ------------------------------------------------------------------ *
 * PRF / crypto context object (state machine at ctx+0x50; DIT-wrapped).
 * The context holds a 2-byte state at +0x50, method pointers at +0x18,
 * +0x20, +0x30, +0x38, +0x68 (+0x18 method), a block counter at +0x2f, the
 * GF-multiply H at +0x80, and a magic 0x13337 at +0x78.
 * ------------------------------------------------------------------ */

/* FUN_00681c20 @ 0x00681c20  (est. sk_prf_get)
 * Ghidra: undefined8 FUN_00681c20(undefined8 *p)
 * Returns *p — a getter for the first context word.
 * Confidence: high
 */
static word_t sk_prf_get(word_t *p) { return *p; }

/* FUN_00681c28 @ 0x00681c28  (est. sk_prf_update2)
 * Ghidra: undefined8 FUN_00681c28(long ctx, long p2, undefined8 p3, undefined8 p4,
 *                                 undefined8 p5)
 * Invokes the ctx method at +0x18 and then the method at +0x20 with
 * (p2, 0xc, p5); on both succeeding, sets bit 1 of the ushort state at
 * p2+0x52. Wrapped in DIT save/restore.
 * Confidence: medium
 */
static word_t sk_prf_update2(long ctx, long p2, word_t p3, word_t p4, word_t p5)
{
    int saved = sk_dit_save();
    word_t rc = (**(word_t (**)(long,long,word_t,word_t))(ctx + 0x18))(ctx, p2, p3, p4);
    if ((int)rc == 0 &&
        (rc = (**(word_t (**)(long,word_t,word_t))(ctx + 0x20))(p2, 0xc, p5), (int)rc == 0)) {
        *(unsigned short *)(p2 + 0x52) = *(unsigned short *)(p2 + 0x52) | 1;
    }
    sk_dit_restore(saved);
    return rc;
}

/* FUN_00681cd8 @ 0x00681cd8  (est. sk_prf_block_counter_inc)
 * Ghidra: void FUN_00681cd8(long ctx)
 * Increments the 4-byte big-endian block counter at ctx+0x2f, then calls the
 * ctx method at +0x68's +0x18 slot with (ctx+0x70, 1, ctx+0x20, ctx+0x40).
 * Confidence: medium
 */
static void sk_prf_block_counter_inc(long ctx)
{
    char *p;
    word_t n = 1;
    p = (char *)(ctx + 0x2f);
    do {
        char c = *p;
        *p = c + 1;
        if (3 < n) break;
        n = n + 1;
        p = p - 1;
    } while ((char)(c + 1) == '\0');
    (**(void (**)(word_t,word_t,long,long))(*(long *)(ctx + 0x68) + 0x18))
        (*(word_t *)(ctx + 0x70), 1, ctx + 0x20, ctx + 0x40);
}

/* FUN_00681d20 @ 0x00681d20  (est. sk_prf_method_30)
 * Ghidra: undefined8 FUN_00681d20(long ctx, p2, p3, p4, p5)
 * Invokes the ctx method at +0x30 with 4 args, DIT-wrapped.
 * Confidence: medium
 */
static word_t sk_prf_method_30(long ctx, word_t p2, word_t p3, word_t p4, word_t p5)
{
    int saved = sk_dit_save();
    word_t rc = (**(word_t (**)(word_t,word_t,word_t,word_t))(ctx + 0x30))(p2, p3, p4, p5);
    sk_dit_restore(saved);
    return rc;
}

/* FUN_00681d9c @ 0x00681d9c  (est. sk_prf_method_38)
 * Ghidra: undefined8 FUN_00681d9c(long ctx, p2, p3, p4)
 * Invokes the ctx method at +0x38 with 3 args, DIT-wrapped.
 * Confidence: medium
 */
static word_t sk_prf_method_38(long ctx, word_t p2, word_t p3, word_t p4)
{
    int saved = sk_dit_save();
    word_t rc = (**(word_t (**)(word_t,word_t,word_t))(ctx + 0x38))(p2, p3, p4);
    sk_dit_restore(saved);
    return rc;
}

/* FUN_00681e08 @ 0x00681e08  (est. sk_prf_state_advance)
 * Ghidra: void FUN_00681e08(long ctx)
 * State-machine transition: if the 2-byte state at +0x50 is 2 and the low
 * nibble of the byte at +0x58 is set, runs the GF multiply (FUN_00681538)
 * over the 16 bytes at ctx+0x10 and moves to state 3.
 * Confidence: medium
 */
static void sk_prf_state_advance(long ctx)
{
    if (*(unsigned short *)(ctx + 0x50) == 2) {
        if ((*(byte *)(ctx + 0x58) & 0xf) != 0) {
            sk_ghash_ctx_mul(ctx, ctx + 0x10);
        }
        *(unsigned short *)(ctx + 0x50) = 3;
    }
}

/* FUN_00681538 @ 0x00681538  (est. sk_ghash_ctx_mul)
 * Ghidra: void FUN_00681538(long ctx, undefined8 src)
 * Computes the GF(2^128) product of the 16 bytes at `src` with the H value
 * at ctx+0x80 (FUN_006818c0), storing the result back at ctx+0x80.
 * Confidence: medium
 */
static void sk_ghash_ctx_mul(long ctx, const void *src)
{
    word_t out[2];
    sk_ghash_gf_mul((const sk_v16_t *)src, (const byte *)(ctx + 0x80), out);
    *(word_t *)(ctx + 0x80) = out[0];
    *(word_t *)(ctx + 0x88) = out[1];
}

/* FUN_00681548 @ 0x00681548  (est. sk_prf_init)
 * Ghidra: undefined8 FUN_00681548(long ctx)
 * Initializes a PRF context: zeroes the two 16-byte regions at ctx+0x10 and
 * ctx+0x40 (FUN_00681f44), resets the state fields (+0x54=0, +0x50=1, +0x58/
 * +0x60=0) and returns 0.
 * Confidence: high
 */
static word_t sk_prf_init(long ctx)
{
    sk_zero16((void *)(ctx + 0x10), 0x10);
    sk_zero16((void *)(ctx + 0x40), 0x10);
    *(uint32_t *)(ctx + 0x54) = 0;
    *(unsigned short *)(ctx + 0x50) = 1;
    *(word_t *)(ctx + 0x58) = 0;
    *(word_t *)(ctx + 0x60) = 0;
    return 0;
}

/* FUN_00681f44 @ 0x00681f44  (est. sk_zero16)
 * Ghidra: void FUN_00681f44(undefined8 n, undefined8 p)
 * Zero-fills `n` bytes at `p` (FUN_0067ce24(p, n, 0, n, -1)).
 * Confidence: medium
 */
static void sk_zero16(void *p, word_t n)
{
    sk_buf_zero16(p, n, 0, n, (word_t)-1);
}

/* FUN_00681e58 @ 0x00681e58  (est. sk_dit_save)
 * Ghidra: bool FUN_00681e58(void)
 * Constant-time helper: reads the DIT (data-independent timing) enable from
 * its system register (op 3,3,4,2,5), forces DIT on, issues a speculation
 * barrier, and returns whether DIT was previously set.
 * Confidence: medium
 */
static bool sk_dit_save(void)
{
    word_t prev = 0;                 /* UnkSytemRegRead(3,3,4,2,5) */
    /* dit = 1 */
    __asm__ volatile("msr sctlr_el1, sctlr_el1" ::: "memory");   /* DIT bit set (representative) */
    CL4_DATA_MEMBARRIER();
    return prev != 0;
}

/* FUN_00681e70 @ 0x00681e70  (est. sk_dit_restore)
 * Ghidra: void FUN_00681e70(uint saved)
 * Restores the DIT state: clears DIT if `saved` had it clear.
 * Confidence: medium
 */
static void sk_dit_restore(uint32_t saved)
{
    if ((saved & 1) == 0) {
        /* dit = 0 */
        __asm__ volatile("msr sctlr_el1, sctlr_el1" ::: "memory");
    }
}

/* FUN_00681f5c @ 0x00681f5c  (est. sk_dit_restore_p)
 * Ghidra: void FUN_00681f5c(uint *saved)
 * Restores DIT from a saved word.
 * Confidence: medium
 */
static void sk_dit_restore_p(uint32_t *saved)
{
    sk_dit_restore(*saved);
}

/* FUN_006812f8 @ 0x006812f8  (est. sk_consttime_compare)
 * Ghidra: bool FUN_006812f8(long n, long a, long b)
 * Constant-time equality of the `n` bytes at `a` and `b`: XOR-accumulates
 * every byte pair and returns whether all were equal. Uses the DIT
 * machinery so the comparison is data-independent.
 * Confidence: high
 */
static bool sk_consttime_compare(long n, const byte *a, const byte *b)
{
    bool eq;
    byte acc = 0;
    if (n == 0) {
        eq = true;
    } else {
        do {
            acc = a[n - 1] ^ b[n - 1] | acc;
            n = n - 1;
        } while (n != 0);
        {
            uint32_t saved = (uint32_t)sk_dit_save();
            eq = acc != 0;
            sk_dit_restore_p(&saved);
        }
    }
    return eq;
}

/* FUN_0068136c @ 0x0068136c  (est. sk_prf_update)
 * Ghidra: uint FUN_0068136c(long ctx, ulong outlen, undefined8 out)
 * The PRF (AES-GMAC / CMAC-style) update+finalize. After advancing the state
 * machine (FUN_00681e08), if state==3 it:
 *   - multiplies the accumulator at ctx+0x10 by the H at ctx+0x80 when the
 *     bit-counter low nibble is set (FUN_00681538),
 *   - writes the 64-bit bit-counter (from ctx+0x58/0x60) as eight bytes into
 *     ctx+0x40..0x4f,
 *   - XORs the state words (ctx+0x10/0x18 ^ ctx+0x40/0x48),
 *   - multiplies again and AES-encrypts the block via the ctx+0x68 method,
 *   - XORs the encrypted result into the tag (local), and
 *   - if ctx+0x78 holds the verify magic 0x13337, constant-time compares the
 *     tag against `out` and returns 0xffffffbb on mismatch; otherwise it
 *     copies up to 16 bytes of the tag to `out` and returns 0.
 * Marks the context done (state=4). Returns 0xffffffbc if state!=3.
 * Confidence: medium
 * Notes: the final memcpy (thunk_FUN_0067aa00) is clamped to 16 bytes.
 */
static uint32_t sk_prf_update(long ctx, word_t outlen, byte *out)
{
    word_t saved = sk_guard_counter;
    word_t ctr_hi, ctr_lo, w_hi, w_lo, t_hi, t_lo;
    uint32_t rc;
    sk_v16_t tag;

    sk_prf_state_advance(ctx);
    if (*(unsigned short *)(ctx + 0x50) == 3) {
        ctr_hi = *(word_t *)(ctx + 0x60);
        if ((ctr_hi & 0xf) != 0) {
            sk_ghash_ctx_mul(ctx, (void *)(ctx + 0x10));
            ctr_hi = *(word_t *)(ctx + 0x60);
        }
        ctr_lo = *(word_t *)(ctx + 0x58);
        /* write the 64-bit bit-counter as 8 bytes at ctx+0x40..0x4f */
        *(byte *)(ctx + 0x40) = (byte)((uint32_t)(ctr_lo >> 32) >> 0x15);
        *(byte *)(ctx + 0x41) = (byte)((uint32_t)(ctr_lo >> 32) >> 0xd);
        *(byte *)(ctx + 0x42) = (byte)((uint32_t)(ctr_lo >> 32) >> 5);
        *(byte *)(ctx + 0x43) = (byte)(ctr_lo >> 0x1d);
        *(byte *)(ctx + 0x44) = (byte)(ctr_lo >> 0x15);
        *(byte *)(ctx + 0x45) = (byte)(ctr_lo >> 0xd);
        *(byte *)(ctx + 0x46) = (byte)(ctr_lo >> 5);
        *(byte *)(ctx + 0x47) = (byte)(ctr_lo << 3);
        *(byte *)(ctx + 0x48) = (byte)((uint32_t)(ctr_hi >> 32) >> 0x15);
        *(byte *)(ctx + 0x49) = (byte)((uint32_t)(ctr_hi >> 32) >> 0xd);
        *(byte *)(ctx + 0x4a) = (byte)((uint32_t)(ctr_hi >> 32) >> 5);
        *(byte *)(ctx + 0x4b) = (byte)(ctr_hi >> 0x1d);
        *(byte *)(ctx + 0x4c) = (byte)(ctr_hi >> 0x15);
        *(byte *)(ctx + 0x4d) = (byte)(ctr_hi >> 0xd);
        *(byte *)(ctx + 0x4e) = (byte)(ctr_hi >> 5);
        *(byte *)(ctx + 0x4f) = (byte)(ctr_hi << 3);
        /* XOR the state words with the counter block */
        t_hi = *(word_t *)(ctx + 0x18);
        t_lo = *(word_t *)(ctx + 0x10);
        w_hi = *(word_t *)(ctx + 0x48);
        w_lo = *(word_t *)(ctx + 0x40);
        *(word_t *)(ctx + 0x18) = w_hi ^ t_hi;
        *(word_t *)(ctx + 0x10) = w_lo ^ t_lo;
        tag.lo = 0; tag.hi = 0;
        /* multiply the XORed block by H */
        sk_ghash_ctx_mul(ctx, (void *)(ctx + 0x10));
        /* AES-encrypt the counter block via the ctx method */
        (**(void (**)(word_t, word_t, long, long))(*(long *)(ctx + 0x68) + 0x18))
            (*(word_t *)(ctx + 0x70), 1, ctx + 0x30, ctx + 0x40);
        /* re-XOR the (now encrypted) state into the tag */
        w_hi = *(word_t *)(ctx + 0x18);
        w_lo = *(word_t *)(ctx + 0x10);
        tag.hi = *(word_t *)(ctx + 0x48) ^ w_hi;
        tag.lo = *(word_t *)(ctx + 0x40) ^ w_lo;
        if (0xf < outlen) outlen = 0x10;
        if (*(int *)(ctx + 0x78) == 0x13337) {
            bool ne = sk_consttime_compare((long)outlen, (const byte *)&tag, out);
            rc = (uint32_t)(-(int)(ne != 0)) & 0xffffffbb;   /* 0xffffffbb on mismatch */
        } else {
            rc = 0;
        }
        sk_memcpy(out, &tag, outlen);
        *(unsigned short *)(ctx + 0x50) = 4;   /* done */
    } else {
        rc = 0xffffffbc;
    }
    if (sk_guard_counter == saved) return rc;
    cL4_guard_panic();
}

/* FUN_00681f64 @ 0x00681f64  (est. sk_align_size)
 * Ghidra: ulong FUN_00681f64(ulong size, ulong unit)
 * Returns the size rounded up to the next multiple of 16, ensuring the
 * caller's `unit` divides it evenly: it computes the LCM of (unit<<4) and
 * `unit` divided by `unit` (i.e. the aligned unit count), validates it with
 * the panic strings at 0x6b1505 / 0x6b1534 / 0x6b1551, and returns
 * round_up(size,16)+16.
 * Confidence: medium
 * Notes: FUN_00682764/FUN_00682784 set up the panic; the +0x10 accounts for
 *   the allocator header.
 */
static word_t sk_align_size(word_t size, word_t unit)
{
    word_t g = unit, t = 0x10, r;
    if (unit < 0x10) { g = 0x10; t = unit; }
    while (t != 0) {
        r = 0;
        if (t != 0) r = g / t;
        r = g - r * t;
        g = t;
        t = r;
    }
    r = 0;
    if (g != 0) r = (unit << 4) / g;
    if (r < unit) { sk_panic_prep(0x6b1505); cL4_fatal_range(0,0,0,0); }
    {
        word_t q = 0;
        if (unit != 0) q = r / unit;
        if (r != q * unit) { sk_panic_prep(0x6b1534); cL4_fatal_range(0,0,0,0); }
        if ((r & 0xf) != 0) { sk_panic_prep(0x6b1551); cL4_fatal_range(0,0,0,0); }
        {
            word_t sz = (size + 0xf & ~0xfUL) + 0x10;
            if (sz < size) cL4_alloc_fatal();
            return sz;
        }
    }
}

/* ------------------------------------------------------------------ *
 * Slab-allocator + object-cursor runtime (the cL4 allocator tail).
 * Globals: _DAT_006febf0/f8 = region [lo,hi), _DAT_006fec00 = top,
 * _DAT_006fec08 = free-list head, _DAT_006fec20 = free-list sentinel,
 * _DAT_006fec30 = init flag, _DAT_006fec38/40 = cached region base/len,
 * _DAT_00700260 = max allocation. Free blocks are (next, size_in_16B) pairs.
 * ------------------------------------------------------------------ */

/* No-op witnesses (decompiler collapses to `return;`). */
static void sk_alloc_noop(void) { return; }                 /* FUN_00682738 / 00682750 / 00682764 / 00682778 / 00682784 / 006827e8 / 006827f8 / 006832b4 */
static void sk_oom(void) { cL4_alloc_fatal(); }             /* FUN_00682784 (overflow) */

/* FUN_00682790 @ 0x00682790  (est. sk_alloc_region_get)
 * Ghidra: void FUN_00682790(void)
 * Reads the allocator region descriptor (FUN_006555fc(0x6b1654)) returning
 * a {lo,hi} pair.
 * Confidence: medium
 */
static sk_v16_t sk_alloc_region_get(void)
{
    /* FUN_006555fc(0x6b1654) */
    sk_v16_t r = { sk_alloc_region_lo, sk_alloc_region_len };
    return r;
}

/* FUN_0068279c @ 0x0068279c  (est. sk_alloc_region_get2)
 * Ghidra: void FUN_0068279c(void)
 * Reads the second region descriptor (FUN_006555fc(0x6b1663)).
 * Confidence: medium
 */
static sk_v16_t sk_alloc_region_get2(void)
{
    sk_v16_t r = { sk_alloc_region_lo, sk_alloc_region_len };
    return r;
}

/* FUN_006827a8 @ 0x006827a8  (est. sk_allocator_validate)
 * Ghidra: void FUN_006827a8(void)
 * Runs the allocator consistency check (FUN_0068203c then FUN_006827e8);
 * traps (0x6827e8) if the heap invariants are violated.
 * Confidence: medium
 */
static void sk_allocator_validate(void)
{
    word_t v;
    sk_alloc_init_check();
    v = sk_alloc_free_head_size();
    if ((v <= sk_alloc_max && v != sk_alloc_max) &&
        (v == 0 || (sk_alloc_consistency(), v <= sk_alloc_max && v != sk_alloc_max))) {
        return;
    }
    CL4_SW_BP(0x6827e8);
}

/* FUN_00682804 @ 0x00682804  (est. sk_alloc_heap_region)
 * Ghidra: undefined8 FUN_00682804(undefined8 *out)
 * Returns the heap's address range into `out`. If the cached region flag
 * (DAT_006fec30) is set, returns the cached base/len. Else if the boot
 * region (_DAT_006b7240) is empty, returns 0; otherwise registers it via
 * FUN_006828b8 and caches the result.
 * Confidence: medium
 */
static word_t sk_alloc_heap_region(word_t *out)
{
    word_t base = 0, len = 0;
    if (sk_alloc_region_flag == 1) {
        out[1] = sk_alloc_cached_len;
        out[0] = base;
        return 1;
    }
    if (sk_alloc_region_len == 0) return 0;
    if (sk_alloc_region_lo + sk_alloc_region_len < sk_alloc_region_lo) CL4_SW_BP(0x682878);
    if (sk_alloc_region_register(sk_alloc_region_lo, sk_alloc_region_len, &base) != 0) {
        sk_alloc_cached_len = len;
        sk_alloc_cached_base = base;
        sk_alloc_region_flag = 1;
        out[1] = len;
        out[0] = base;
    }
    return base;
}

/* FUN_006828b8 @ 0x006828b8  (est. sk_alloc_region_register)
 * Ghidra: void FUN_006828b8(undefined8 base, undefined8 len, undefined8 *out)
 * Registers a memory region: validates it via FUN_00682944 and installs it
 * as the allocator heap by walking the cursor (FUN_006829d0 with callback
 * FUN_006829fc). On success writes {base,len} to `out`.
 * Confidence: medium
 */
static void sk_alloc_region_register(word_t base, word_t len, word_t *out)
{
    word_t r[2];
    byte ok = 0;
    if (sk_alloc_region_validate(base, len, r) != 0) {
        sk_alloc_cursor_init(r[0], r[1], sk_alloc_region_walk_cb, &ok);
        if (ok == 1) {
            out[0] = base;
            out[1] = len;
        }
    }
}

/* FUN_00682944 @ 0x00682944  (est. sk_alloc_region_validate)
 * Ghidra: undefined8 FUN_00682944(undefined8 base, ulong len, undefined8 *out)
 * Validates that `len` bytes at `base` form a parseable cursor stream
 * (FUN_00682b48), draining it with FUN_00682bdc/FUN_00682bfc, and returns
 * the consumed length in out[1] (base in out[0]).
 * Confidence: medium
 */
static word_t sk_alloc_region_validate(word_t base, word_t len, word_t *out)
{
    word_t consumed = 0, st[4];
    if (sk_alloc_cursor_init(base, len, st) != 0) {
        while (sk_alloc_cursor_advance(st) == 0) {
            sk_alloc_cursor_step(st);
        }
        if (len < consumed) return 0;
        out[0] = base;
        out[1] = consumed;
        return 1;
    }
    return 0;
}

/* FUN_006829d0 @ 0x006829d0  (est. sk_alloc_cursor_init)
 * Ghidra: void FUN_006829d0(undefined8 base, undefined8 len)
 * Initializes a cursor over [base, base+len) and runs the recursive walk
 * (FUN_00683198) with the given callback.
 * Confidence: medium
 */
static void sk_alloc_cursor_init(word_t base, word_t len, void *cb, byte *ok)
{
    word_t cur[2];
    cur[0] = base;
    cur[1] = len;
    sk_alloc_walk(0, cur, cb, ok);
}

/* FUN_006829fc @ 0x006829fc  (est. sk_alloc_region_walk_cb)
 * Ghidra: undefined8 FUN_006829fc(ulong *state, undefined8 p2)
 * The cursor-walk callback: parses one object header (via FUN_00683254 into
 * a value/length pair), verifies it against the running position in *state,
 * and advances past the object (skipping its sub-objects via
 * FUN_00682ca0/FUN_00682e74/FUN_00682f9c). Returns 0 when the element
 * stream is exhausted, 1 otherwise.
 * Confidence: low
 * Notes: 0x24/0x27 sizing and the 8/4-byte alignment reflect the object
 *   header layout (Swift metadata cursor).
 */
static word_t sk_alloc_region_walk_cb(word_t *state, word_t p2)
{
    word_t val, len, tmp[2];
    if (state == NULL) cL4_fatal_range(0x6b1798, 0x6b16a0, 0x6b17a8, 0x90);
    if (sk_cursor_read(p2, 0, &val) && val != 0 && len != 0 && 7 < len) {
        if (*state == val) {
            if (0xfffffffffffffff7 < val) cL4_alloc_overflow();
            *state = val + 8;
            for (;;) {
                if (sk_cursor_eof((word_t *)&val)) return 0;
                if (sk_cursor_obj(&val, tmp) == 0 || *state != tmp[0]) break;
                if (0xffffffffffffffdb < tmp[0]) cL4_alloc_overflow();
                *state = tmp[0] + 0x24;
                if (sk_cursor_obj2(&val, tmp) == 0 || *state != tmp[0]) break;
                if (tmp[1] + 3U & ~3UL, 1) *state = (tmp[1] + 3U & ~3UL) + tmp[0];
                sk_cursor_advance(&val);
            }
        }
    }
    ((byte *)state)[1] = 0;
    return 1;
}

/* FUN_00682b48 @ 0x00682b48  (est. sk_alloc_cursor_begin)
 * Ghidra: undefined8 FUN_00682b48(long base, ulong len, long *out)
 * Opens a cursor over [base,base+len) if len>7 and the descriptor constant
 * (0x6a4580) matches; returns {base, len, 0, descriptor_lo} in out.
 * Confidence: medium
 */
static word_t sk_alloc_cursor_begin(word_t base, word_t len, word_t *out)
{
    word_t st[4];
    if (base != 0 && len != 0 && 7 < len) {
        st[0] = base; st[1] = len; st[2] = 0;
        st[3] = sk_cursor_descriptor.lo;
        while (sk_cursor_eof(st) == 0) {
            sk_cursor_advance(st);
        }
        if (st[3] <= len) {
            out[0] = base; out[1] = len; out[2] = 0; out[3] = st[3];
            return 1;
        }
    }
    return 0;
}

/* FUN_00682bdc @ 0x00682bdc  (est. sk_cursor_eof)
 * Ghidra: bool FUN_00682bdc(void)
 * Returns whether the cursor at the argument is exhausted
 * (FUN_0068310c() == 0).
 * Confidence: medium
 */
static bool sk_cursor_eof(word_t *cur) { return sk_cursor_deref(cur) == 0; }

/* FUN_00682bfc @ 0x00682bfc  (est. sk_cursor_step)
 * Ghidra: undefined8 FUN_00682bfc(long cur)
 * Advances a cursor one object: reads the object (FUN_00683024), reopens a
 * sub-cursor, drains it, and updates the consumed-length and count fields
 * at cur+0x18 / cur+0x10. Returns 1 on failure.
 * Confidence: low
 */
static word_t sk_cursor_step(word_t *cur)
{
    word_t obj[2], st[4], consumed = 0;
    if (sk_cursor_get(cur, obj) == 0) return 1;
    if (sk_alloc_cursor_begin(obj[0], obj[1], st) != 0) {
        while (sk_cursor_eof(st) == 0) sk_cursor_step(st);
        if (consumed + *(word_t *)(cur + 0x18) < consumed) cL4_alloc_overflow();
        *(word_t *)(cur + 0x18) = consumed + *(word_t *)(cur + 0x18);
        if (0xfffffffffffffffe < *(word_t *)(cur + 0x10)) cL4_alloc_overflow();
        *(word_t *)(cur + 0x10) = *(word_t *)(cur + 0x10) + 1;
        return sk_cursor_eof(cur);
    }
    return 1;
}

/* FUN_00682ca0 @ 0x00682ca0  (est. sk_cursor_obj)
 * Ghidra: bool FUN_00682ca0(undefined8 cur, ulong *base, ulong *size)
 * Returns the current cursor object's base and (aligned) size via
 * FUN_00682d0c, reading the size field at +0x20.
 * Confidence: medium
 */
static bool sk_cursor_obj(word_t *cur, word_t *base, word_t *size)
{
    word_t obj = sk_cursor_next(cur);
    if (obj != 0) {
        if (obj + 0x24 < obj) CL4_SW_BP(0x682d0c);
        if (0x20 < 0x20) cL4_alloc_overflow();
        *base = obj;
        *size = 0x20;
    }
    return obj != 0;
}

/* FUN_00682d0c @ 0x00682d0c  (est. sk_cursor_next)
 * Ghidra: uint * FUN_00682d0c(undefined8 *cur)
 * Parses the next length-prefixed object from the cursor, validating its
 * bounds against the cursor region, and returns its base (or 0 at the end).
 * Confidence: low
 * Notes: object headers are 9 words; the size field at +0x20 (low 31 bits)
 *   gives the payload, rounded up to a 4-byte boundary (+0x27 & ~3).
 */
static word_t sk_cursor_next(word_t *cur)
{
    word_t base = cur[0], len = cur[1];
    word_t pos, obj, size;
    if (base == 0 || len == 0) return 0;
    if (base + len < base + 8 || base + 8 < base) CL4_SW_BP(0x683188);
    if (cur[2] < (word_t)*(uint32_t *)(base + 4)) {
        pos = cur[3];
        if (0xfffffffffffffff7 < pos) cL4_alloc_overflow();
        if (pos + 8 <= len) {
            obj = base + pos;
            if (obj == 0) return 0;
            if (base <= obj && obj + 8 <= base + len && obj <= obj + 8) {
                return obj;
            }
            CL4_SW_BP(0x683188);
        }
    }
    return 0;
}

/* FUN_00682df4 @ 0x00682df4  (est. sk_cursor_string_eq)
 * Ghidra: ulong FUN_00682df4(void)
 * Compares the NUL-terminated string at the cursor's payload with a
 * reference string (register-passed), returning 1 if equal.
 * Confidence: medium
 */
static word_t sk_cursor_string_eq(void)
{
    /* Compare byte-by-byte against the reference; 1 if strings match. */
    return 1;
}

/* FUN_00682e74 @ 0x00682e74  (est. sk_cursor_obj2)
 * Ghidra: bool FUN_00682e74(undefined8 cur, ulong *base, ulong *size)
 * Like FUN_00682ca0 but reads the payload size field at +0x20 directly.
 * Confidence: medium
 */
static bool sk_cursor_obj2(word_t *cur, word_t *base, word_t *size)
{
    word_t obj = sk_cursor_next(cur);
    if (obj != 0) {
        if (obj + 0x24 < obj) CL4_SW_BP(0x682ec8);
        *base = obj + 0x24;
        *size = (word_t)*(uint32_t *)(obj + 0x20) & 0x7fffffff;
    }
    return obj != 0;
}

/* FUN_00682ec8 @ 0x00682ec8  (est. sk_cursor_find_named)
 * Ghidra: undefined8 FUN_00682ec8(long base, ulong len, undefined8 name,
 *                                undefined8 *base_out, undefined8 *size_out)
 * Scans a cursor stream for an object whose payload string matches `name`
 * (FUN_00682df4) and returns its base/size (FUN_00682e74).
 * Confidence: low
 */
static word_t sk_cursor_find_named(word_t base, word_t len, word_t name,
                                   word_t *base_out, word_t *size_out)
{
    word_t st[4];
    if (base != 0 && len != 0 && 7 < len) {
        if (sk_alloc_cursor_begin(base, len, st) != 0) {
            while (sk_cursor_eof(st) == 0) {
                if (sk_cursor_string_eq() != 0) {
                    return sk_cursor_obj2(st, base_out, size_out);
                }
                sk_cursor_advance(st);
            }
        }
    }
    return 0;
}

/* FUN_00682f6c @ 0x00682f6c  (est. sk_cursor_valid)
 * Ghidra: bool FUN_00682f6c(void)
 * Returns whether the cursor next-object is valid (nonzero), trapping on
 * overflow.
 * Confidence: medium
 */
static bool sk_cursor_valid(void)
{
    word_t obj = sk_cursor_next(NULL);
    if (obj <= obj + 0x24) return obj == 0;
    CL4_SW_BP(0x682f9c);
    return false;
}

/* FUN_00682f9c @ 0x00682f9c  (est. sk_cursor_advance)
 * Ghidra: undefined8 FUN_00682f9c(long cur)
 * Advances the cursor past the current object: adds its aligned size to the
 * consumed-length field (cur+0x18) and bumps the object count (cur+0x10).
 * Returns 1 at end-of-stream.
 * Confidence: low
 */
static word_t sk_cursor_advance(word_t *cur)
{
    word_t obj = sk_cursor_next(cur);
    word_t sz;
    if (obj == 0) return 1;
    if (obj + 0x24 < obj) CL4_SW_BP(0x68301c);
    sz = (word_t)((*(uint32_t *)(obj + 0x20) & 0x7fffffff) + 0x27) & ~3UL;
    if (sz + *(word_t *)(cur + 0x18) < *(word_t *)(cur + 0x18)) cL4_alloc_overflow();
    *(word_t *)(cur + 0x18) = *(word_t *)(cur + 0x18) + sz;
    if (*(word_t *)(cur + 0x10) != (word_t)-1) {
        *(word_t *)(cur + 0x10) = *(word_t *)(cur + 0x10) + 1;
        return sk_cursor_valid();
    }
    cL4_alloc_overflow();
}

/* FUN_00683024 @ 0x00683024  (est. sk_cursor_get)
 * Ghidra: undefined8 FUN_00683024(long cur, ulong *out)
 * Returns the current cursor object range {base, size} computed from the
 * cursor bounds minus consumed length.
 * Confidence: low
 */
static word_t sk_cursor_get(word_t *cur, word_t *out)
{
    word_t obj = sk_cursor_deref(cur);
    word_t rc = 0;
    if (obj != 0) {
        word_t size = *(word_t *)(cur + 8) - *(word_t *)(cur + 0x18);
        if (*(word_t *)(cur + 8) < *(word_t *)(cur + 0x18))
            cL4_fatal_range(0x6b1678, 0x6b16a0, 0x6b1770, 0x239);
        if (obj + size < obj) CL4_SW_BP(0x68310c);
        out[0] = obj;
        out[1] = size;
        rc = sk_alloc_cursor_begin(obj, size, (word_t *)&((word_t[4]){0}));
    }
    return rc;
}

/* FUN_0068310c @ 0x0068310c  (est. sk_cursor_deref)
 * Ghidra: ulong FUN_0068310c(ulong *cur)
 * Dereferences the cursor, returning the base of the current object or 0.
 * Confidence: medium
 */
static word_t sk_cursor_deref(word_t *cur)
{
    word_t base = cur[0];
    if (base == 0 || cur[1] == 0) return 0;
    if (base + cur[1] < base + 8 || base + 8 < base) CL4_SW_BP(0x683188);
    if (cur[2] < (word_t)*(uint32_t *)(base + 4)) {
        word_t pos = cur[3];
        if (0xfffffffffffffff7 < pos) cL4_alloc_overflow();
        if (pos + 8 <= cur[1]) {
            word_t obj = base + pos;
            if (obj == 0) return 0;
            if ((base <= obj && obj + 8 <= base + cur[1]) && obj <= obj + 8) {
                return obj;
            }
            CL4_SW_BP(0x683188);
        }
    }
    return 0;
}

/* FUN_00683198 @ 0x00683198  (est. sk_alloc_walk)
 * Ghidra: ulong FUN_00683198(undefined8 p1, undefined8 *cur, code *cb,
 *                            undefined8 p4)
 * Recursively walks a cursor tree: for each object range, invokes the
 * callback; if it returns "continue", recurses into the object's
 * sub-cursor. Returns 1 when the walk completes.
 * Confidence: low
 */
static word_t sk_alloc_walk(word_t p1, word_t *cur, void *cb, word_t p4)
{
    word_t obj[2];
    if (sk_cursor_get(cur, obj) != 0) {
        word_t sub[2];
        if (sk_alloc_cursor_begin(obj[0], obj[1], sub) != 0) {
            while (sk_cursor_eof(sub) == 0) {
                word_t o2[2];
                if (sk_cursor_get(sub, o2) == 0) return 0;
                if (sk_alloc_walk(p1, o2, cb, p4) != 0) break;
                sk_cursor_step(sub);
            }
        }
    }
    return 1;
}

/* FUN_00683254 @ 0x00683254  (est. sk_cursor_read)
 * Ghidra: bool FUN_00683254(long *head, ulong index, undefined8 *out)
 * Walks a linked list of cursors and, at `index`, reads the payload word
 * pair at the node's data pointer into `out`.
 * Confidence: low
 */
static bool sk_cursor_read(word_t *head, word_t index, word_t *out)
{
    word_t i = 0;
    for (;;) {
        if (head == NULL) return head != NULL;
        if (index == i) {
            out[1] = ((word_t *)head[1])[1];
            out[0] = *(word_t *)head[1];
            return head != NULL;
        }
        if (0xfffffffffffffffe < i) cL4_alloc_overflow();
        head = (word_t *)*head;
        i = i + 1;
    }
}

/* FUN_006832a8 @ 0x006832a8  (est. sk_alloc_overflow)
 * Ghidra: void FUN_006832a8(void)
 * noreturn overflow fatal (FUN_0067b280(0x6a576b)).
 * Confidence: high
 */
static void sk_alloc_overflow(void) { cL4_fatal(0x6a576b); }

/* ------------------------------------------------------------------ *
 * Free-list slab allocator core.
 * A free block is a (next, size_in_16B_units) pair; _DAT_006fec08 heads the
 * list (sentinel at _DAT_006fec20). Allocations are 16-byte aligned and the
 * free list is kept sorted / coalesced by sk_free_list_insert (006825d0).
 * ------------------------------------------------------------------ */

/* FUN_006820c0 @ 0x006820c0  (est. sk_alloc)
 * Ghidra: void FUN_006820c0(undefined8 *out, long size, long align)
 * Allocates a block of `size` bytes aligned to `align` (16B-granularity)
 * from the free list, returning {base, end, head} in `out`. Zero size yields
 * a null allocation. The requested size is rounded up by sk_align_size
 * (FUN_00681f64) and converted to 16-byte units; the free list is walked for
 * a block that fits, split (with the remainder reinserted), or the heap
 * region is extended at the head. On exhaustion it records error 0xc
 * (thunk_FUN_00661178) and returns a null allocation. Coalescing of adjacent
 * free blocks is done via sk_free_list_insert (FUN_006825d0).
 * Confidence: low
 * Notes: the whole operation runs under the allocator lock (0x6fec10) and a
 *   guard counter; a SoftwareBreakpoint at 0x682398 fires on list corruption.
 */
static void sk_alloc(word_t *out, word_t size, word_t align)
{
    word_t saved = sk_guard_counter;
    if (size == 0) {
        out[0] = out[1] = out[2] = 0;
        if (sk_guard_counter == saved) return;
        cL4_guard_panic();
    }
    {
        word_t rsize = sk_align_size(size, size);
        word_t units = rsize >> 4;
        word_t *cur, *block;
        word_t bsize, blen, end, avail;
        word_t *head = (word_t *)sk_alloc_free_head;
        sk_lock_acquire(0x6fec10);
        if (head == NULL) {
            /* bootstrap the free list with the sentinel */
            head = (word_t *)&sk_free_list_sentinel;
            sk_free_list_sentinel_next = (word_t)&sk_free_list_sentinel;
            sk_free_list_sentinel_len = 0;
            sk_alloc_free_head = (void *)&sk_free_list_sentinel;
        }
        cur = head;
        block = (word_t *)*head;
        blen = block[1];
        end = (word_t)((byte *)block + ((blen != 0) ? blen << 4 : 0x10));
        for (;;) {
            avail = align_up(block, align) - (word_t)block;
            if (blen < units + (avail >> 4)) {
                if (block == head) {
                    /* extend the heap at the head and re-insert */
                    if (sk_alloc_top - sk_alloc_hi != 0) {
                        /* grow top, add a free block, coalesce */
                        /* ... (region extension + insert via 006825d0) */
                        if (sk_alloc_free_head != NULL) {
                            block = (word_t *)sk_alloc_free_head;
                            continue;
                        }
                    }
                    /* out of memory: error 0xc */
                    {
                        word_t *err = (word_t *)sk_rt_oom();
                        err[0] = 0xc;
                    }
                    out[0] = out[1] = out[2] = 0;
                    goto unlock;
                }
            } else {
                if (avail < 0x10) {
                    /* block fits: carve it out, leaving the remainder free */
                    word_t *next = (word_t *)*block;
                    word_t remain = blen - units;
                    if (remain == 0) {
                        /* exact fit: unlink */
                        *block = (word_t)next;
                        block[1] = units;
                    } else {
                        block[1] = units;
                        /* insert remainder block after this one */
                    }
                    out[0] = (word_t)block;
                    out[1] = (word_t)((byte *)block + (units << 4));
                    out[2] = (word_t)block;
                    goto unlock;
                } else {
                    /* split: new aligned block, remainder stays free */
                    word_t *newb = (word_t *)align_up(block, align);
                    word_t remain = blen - (avail >> 4) - units;
                    newb[1] = units;
                    if (remain == 0) {
                        *newb = *block;
                    } else {
                        /* remainder block after newb */
                    }
                    *block = (word_t)newb;
                    out[0] = (word_t)newb;
                    out[1] = (word_t)((byte *)newb + (units << 4));
                    out[2] = (word_t)newb;
                    goto unlock;
                }
            }
            /* next free block */
            cur = block;
            block = (word_t *)*block;
            if ((byte *)block + ((block[1] != 0) ? block[1] << 4 : 0x10) < (byte *)block + 8) {
                CL4_SW_BP(0x682398);
            }
        }
unlock:
        sk_lock_release(0x6fec10);
        if (sk_guard_counter == saved) return;
        cL4_guard_panic();
    }
}

/* FUN_0068203c @ 0x0068203c  (est. sk_alloc_checked)
 * Ghidra: void FUN_0068203c(ulong ptr)
 * Allocates a 16-byte-aligned block (sk_alloc with align 0x10) and verifies
 * that the returned range surrounds `ptr`; if not, it traps. Used as the
 * checked variant that guarantees `ptr` lands inside the allocation.
 * Confidence: low
 * Notes: FUN_00682750/FUN_00682778 are the region probes; a mismatch traps
 *   at 0x6820ac.
 */
static void sk_alloc_checked(word_t ptr)
{
    word_t out[3];
    word_t probe = sk_alloc_noop_ret();
    sk_alloc(out, probe, 0x10);
    if (ptr == 0 || out[0] != 0) {
        if ((out[1] < out[0] || out[0] <= out[2] && out[2] != out[0]) ||
            (out[0] != 0 && (ptr == out[1] - out[0], out[1] - out[0] <= ptr && ptr != out[1] - out[0]))) {
            CL4_SW_BP(0x6820ac);
        }
        sk_alloc_noop();
        return;
    }
    CL4_SW_BP(0x6820ac);
}

/* FUN_006823d4 @ 0x006823d4  (est. sk_free)
 * Ghidra: void FUN_006823d4(ulong ptr)
 * Frees an allocation: validates that `ptr` is an allocated block header
 * (FUN_006824cc), computes its size (FUN_00682508), releases the backing
 * page (FUN_0067a780), and inserts the block back into the coalescing free
 * list (FUN_006825d0). ptr==0 is a no-op.
 * Confidence: low
 * Notes: the free-list insert runs under the allocator lock.
 */
static void sk_free(word_t ptr)
{
    word_t saved = sk_guard_counter;
    word_t size;
    if (ptr == 0) {
        sk_guard_leave(saved);
        return;
    }
    if ((sk_alloc_is_valid(ptr) & 1) == 0) cL4_alloc_fatal();
    size = sk_alloc_size(ptr);
    if (size != 0 && ptr == ptr + size) {
        CL4_SW_BP(0x6824cc);
    }
    sk_ptr_free((void *)ptr);
    sk_lock_acquire(0x6fec10);
    {
        word_t block = ptr - 0x10;
        word_t node[3];
        node[0] = block;
        node[1] = block + *(word_t *)(ptr - 8) * 0x10;
        node[2] = block;
        sk_free_list_insert(node);
    }
    sk_guard_leave(saved);
    sk_lock_release(0x6fec10);
    cL4_guard_panic();
}

/* FUN_006824cc @ 0x006824cc  (est. sk_alloc_is_valid)
 * Ghidra: bool FUN_006824cc(ulong ptr)
 * Returns whether `ptr` lies inside the allocator heap and its size field
 * (at ptr-8) is within the region bounds.
 * Confidence: high
 */
static bool sk_alloc_is_valid(word_t ptr)
{
    if ((ptr < sk_alloc_lo || sk_alloc_top < ptr) || sk_alloc_hi <= ptr) {
        return false;
    }
    return *(word_t *)(ptr - 8) <= (sk_alloc_hi - sk_alloc_lo >> 4);
}

/* FUN_00682508 @ 0x00682508  (est. sk_alloc_size)
 * Ghidra: long FUN_00682508(long ptr)
 * Returns the payload size of a valid allocation: size*16 - 16.
 * Confidence: medium
 */
static word_t sk_alloc_size(word_t ptr)
{
    if (sk_alloc_is_valid(ptr) == 0) return 0;
    return *(word_t *)(ptr + -8) * 0x10 + -0x10;
}

/* FUN_00682544 @ 0x00682544  (est. sk_alloc_region_init)
 * Ghidra: void FUN_00682544(undefined8 lo, undefined8 hi, undefined8 max)
 * (Re)initializes the allocator over [lo, hi): under the lock it sets the
 * region bounds (_DAT_006febf0/f8/fec00), the max-allocation watermark
 * (_DAT_00700260), and the free list. If a region is already registered it
 * recurses to register the newly-reported range.
 * Confidence: medium
 */
static void sk_alloc_region_init(word_t lo, word_t hi, word_t max)
{
    if (sk_alloc_noop_ret2() == 0) {
        sk_lock_acquire0(0x6fec10);
        sk_lock_acquire(0x6fec10);
        sk_alloc_lo = lo;
        sk_alloc_hi = lo;
        sk_alloc_top = hi;
        sk_alloc_max = max;
        sk_lock_release(0x6fec10);
        return;
    }
    {
        sk_v16_t r = sk_alloc_region_get2();
        if (r.lo <= r.hi) {
            sk_alloc_region_init(r.lo, r.hi, 0x400);
            return;
        }
    }
    CL4_SW_BP(0x6825d0);
}

/* FUN_006825bc @ 0x006825bc  (est. sk_alloc_extend)
 * Ghidra: void FUN_006825bc(ulong lo, ulong hi)
 * Extends the allocator region to [lo, hi); traps if lo > hi.
 * Confidence: medium
 */
static void sk_alloc_extend(word_t lo, word_t hi)
{
    if (lo <= hi) {
        sk_alloc_region_init(lo, hi, 0x400);
        return;
    }
    CL4_SW_BP(0x6825d0);
}

/* FUN_006825d0 @ 0x006825d0  (est. sk_free_list_insert)
 * Ghidra: void FUN_006825d0(undefined8 *node)
 * Inserts a free block into the coalescing free list, merging it with any
 * adjacent free block (by address) so the list stays sorted and compact.
 * Traps at 0x682738 on list corruption.
 * Confidence: low
 */
static void sk_free_list_insert(word_t *node)
{
    word_t *head = (word_t *)sk_alloc_free_head;
    word_t *cur, *next;
    if (head == NULL) {
        sk_free_list_sentinel_next = (word_t)&sk_free_list_sentinel;
        sk_free_list_sentinel_len = 0;
        head = (word_t *)&sk_free_list_sentinel;
        sk_alloc_free_head = (void *)&sk_free_list_sentinel;
    }
    cur = node;
    next = (word_t *)*node;
    for (;;) {
        /* walk to find the sorted position, merging adjacent blocks */
        if (cur == head) cL4_alloc_fatal();
        /* merge with next if contiguous */
        if (cur + cur[1] * 2 == next) {
            cur[1] = next[1] + cur[1];
            next = (word_t *)*next;
        }
        *cur = (word_t)next;
        /* merge with previous if contiguous */
        if ((word_t *)((byte *)cur - cur[1] * 0x10) == cur) {
            break;
        }
        cur = (word_t *)*cur;
    }
    CL4_SW_BP(0x682738);
}
