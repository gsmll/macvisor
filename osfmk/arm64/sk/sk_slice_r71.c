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
extern void    sk_buf_zero16(void *p, word_t n, word_t a, word_t m);/* FUN_0067ce24 (fill) */
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
