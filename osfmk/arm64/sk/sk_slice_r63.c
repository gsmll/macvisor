/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R63: 0x41d7dc-0x4519d4. This slice is dominated by the embedded
 * Swift-runtime type metadata / protocol-conformance / generic-requirement
 * decoder machinery (the "MetadataDecoder", "Conformance", "GenericRequirement"
 * and boxed-value dispatcher patterns also seen in neighboring SK slices),
 * plus cL4 string/error handling. All names are estimates unless
 * string-matched. Ghidra FUN_ names are kept only in comments.
 *
 * Calling-convention note: many functions take a "variant / box" object in
 * the first register and a small integer operation selector in x1. The
 * 0/1/2/else pattern (unwrap / release-arg / copy-clone / release-self) is a
 * Swift boxed-value (copy/retain/release) dispatcher: op 0 unwraps the box
 * into *out, op 1 releases the boxed value, op 2 allocates a fresh clone of
 * the given size and copies the payload, and anything else releases the
 * container itself.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* Memory/load ordering fences used by the refcount / conformance-table code. */
#define CL4_DATA_MEMBARRIER() __asm__ volatile("dmb ish" ::: "memory")
#define CL4_LO_ACQUIRE()      __asm__ volatile("dmb ishld" ::: "memory")
#define CL4_LO_RELEASE()      __asm__ volatile("dmb ish" ::: "memory")

/* SoftwareBreakpoint(1, addr) fail-closed trap. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")


/* =========================================================================
 * Slice R63 functions.  Externs for out-of-slice callees (declared once).
 * ========================================================================= */

/* cL4 core / Swift-runtime callees shared across this slice.  All are
 * out-of-slice; kept as externs with their Ghidra FUN_ addresses. */
extern void FUN_00354744(void);
extern void FUN_0036b270(word_t);
extern void FUN_00463fe8(void);
extern void FUN_002acbb8();
extern void FUN_0044ca60(void);
extern void FUN_00350738(void);
extern void FUN_003a25d4();
extern void FUN_00463af8(void);
extern void FUN_004645ec(void);
extern void FUN_00465d1c(void);
extern void FUN_00100efc(void);
extern void FUN_003544c8();
extern word_t FUN_00466440(void);
extern word_t FUN_000a6f68();
extern void FUN_004562f0();
extern void FUN_00465ce8(word_t);
extern word_t FUN_0036a940(void);
extern void FUN_000dbed0(word_t);
extern void FUN_00464e28(void);
extern void FUN_00458da0(void);
extern void FUN_00084180(void);
extern void FUN_00463418(void);
extern void FUN_00464ef8(void);
extern word_t FUN_0029fb80(void);
extern void FUN_0029d3d8();
extern void FUN_00351e08(void);
extern void FUN_0007c1c4();
extern void FUN_00464180(void);
extern void FUN_0035053c(void);
extern word_t FUN_002abcb0(void);
extern void FUN_00350624(word_t);
extern void FUN_000b4660(void);
extern void FUN_002a3e64(void);
extern void FUN_0034bd90();
extern void FUN_0006b6f4();
extern void FUN_0035aba4(void);
extern void FUN_001ae8a8(void);
extern void FUN_00464eec(void);
extern word_t FUN_002bc2dc(void);
extern void FUN_00462fac(void);
extern word_t FUN_002a0cf8(void);
extern void FUN_00463540();
void sk_r63_alloc_box_chain(void);
extern void FUN_0041e28c();
extern void FUN_004207b0();
extern void FUN_0041f074();
extern void FUN_00460e78();
extern cL4_w16_t FUN_001b28d4();
extern cL4_w16_t FUN_002b5e10();
extern void FUN_002ab388();
extern cL4_w16_t FUN_003f8224();
extern void FUN_0034ecc8(void);
extern cL4_w16_t FUN_002b3f40(word_t,word_t,word_t,word_t,word_t,word_t,word_t);
extern cL4_w16_t FUN_002b74c0(word_t,word_t,word_t,word_t,word_t,word_t);


/* FUN_0041d7dc @ 0x41d7dc  (est. sk_r63_callout_wrapper)
 * Ghidra: undefined FUN_0041d7dc(undefined8,undefined8,undefined8,undefined8,
 *         undefined8,undefined8,code *)
 * Runs a delegate callout: invokes a series of Swift-runtime setup/teardown
 * helpers, then increments a per-context reference counter located at
 * x20+0x40 with overflow detection (SoftwareBreakpoint on carry), calls the
 * supplied closure *param_7, and on the non-carrying path performs the
 * matching teardown sequence. The SCARRY8/SoftwareBreakpoint pattern is the
 * standard cL4 refcount-overflow guard.
 * Confidence: low
 * Notes: callees are opaque out-of-slice helpers; extraout_x1/x8 artifacts of
 *   the decompiler's register merging. */
void sk_r63_callout_wrapper(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, void (*callback)(void))
{
    word_t *ctx = (word_t *)__builtin_frame_address(0); /* x20 base */
    long carried;

    FUN_00354744();
    FUN_0036b270(0);
    FUN_00463fe8();
    FUN_002acbb8();
    FUN_002acbb8(p3, p4);
    FUN_0044ca60();
    FUN_0036b270(0);
    FUN_00350738();
    FUN_002acbb8();
    FUN_003a25d4(0);
    FUN_00463af8();
    FUN_003a25d4(0);
    FUN_004645ec();

    /* Overflow-checked increment of the reference counter at ctx+0x40. */
    carried = (ctx[8] == (word_t)-1) ? 1 : 0;   /* SCARRY8 of +1 */
    if (carried) {
        CL4_SW_BP(0x41d8e0);
    }
    ctx[8] = ctx[8] + 1;

    callback();

    FUN_00465d1c();
    if (!carried) {
        ctx[8] = 0;
        FUN_0044ca60();
        FUN_0036b270(p6);
        FUN_00100efc();
        FUN_002acbb8();
        FUN_003a25d4(p6);
        FUN_00463af8();
        FUN_004645ec();
        FUN_003544c8(0);
        return;
    }
    CL4_SW_BP(0x41d8e4);
}

/* FUN_0041d8f4 @ 0x41d8f4  (est. sk_r63_decode_box_array)
 * Ghidra: undefined FUN_0041d8f4(long param_1)
 * Decodes an array of Swift boxed values at param_1. Reads a count at
 * param_1+0x10 and dispatches: count==1 builds a single-element chain,
 * count==0 emits an empty array, otherwise iterates `count` entries (each a
 * 0x38-byte record at param_1+0x20) and materializes a linked list of
 * box-allocations, then stores the resulting array into a fresh descriptor.
 * Confidence: medium
 * Notes: 0x675c68 is an inert sentinel id; lVar2<0 checked with
 *   SoftwareBreakpoint(1) fail-closed. */
void sk_r63_decode_box_array(word_t base)
{
    long count = *(long *)(base + 0x10);
    long i, e;

    if (count == 1) {
        sk_r63_alloc_box_chain();
        return;
    }
    if (count == 0) {
        word_t desc = FUN_00466440();
        long node = FUN_000a6f68(desc, 0, 0);
        *(word_t *)(node + 0x10) = 0;   /* extraout_x8 */
        return;
    }

    FUN_000a6f68();
    FUN_004562f0(0, count, 0);
    i = 0;
    do {
        if (i == count) {
            CL4_SW_BP(0x41dadc);
        }
        word_t *rec = (word_t *)(base + 0x20 + i * 0x38);
        long arg = rec[3];
        long id = 0;
        if (rec[2] != 0x675c68) {
            id = rec[2];
        }
        if (arg < 0) {
            CL4_SW_BP(0x41dae0);
        }
        long val = rec[0];
        long ty = rec[1];
        long head, tail, tailty, tailid;
        byte has_tail;
        if (arg == 0) {
            has_tail = 0;
            head = ty;
            tail = 0; tailty = 0; tailid = 0;
        } else {
            FUN_00465ce8(0x685d58);
            long node = FUN_0036a940();
            *(long *)(node + 0x10) = val;
            *(long *)(node + 0x18) = ty;
            *(long *)(node + 0x20) = id;
            *(byte *)(node + 0x28) = 0;
            head = node;
            e = arg;
            while ((e = e - 1) != 0) {
                FUN_00465ce8(0x685d58);
                long n2 = FUN_0036a940();
                *(word_t *)(n2 + 0x18) = 0;
                *(word_t *)(n2 + 0x20) = 0;
                *(long *)(n2 + 0x10) = head;
                *(byte *)(n2 + 0x28) = 1;
                head = n2;
            }
            tail = 0;
            tailty = 0;
            tailid = 0;
            has_tail = 1;
        }
        /* Append record into the growing output array at extraout_x8_00. */
        word_t *out = (word_t *)0;   /* extraout_x8_00 */
        unsigned long u1 = *(unsigned long *)((word_t)out + 0x10);
        unsigned long u4 = *(unsigned long *)((word_t)out + 0x18);
        FUN_0036b270(ty);
        if ((u4 >> 1) <= u1) {
            FUN_000dbed0(1 < u4);
            FUN_004562f0();
        }
        i = i + 1;
        *(unsigned long *)((word_t)out + 0x10) = u1 + 1;
        long slot = (word_t)out + u1 * 0x20;
        *(long *)(slot + 0x20) = head;
        *(long *)(slot + 0x28) = tail;
        *(long *)(slot + 0x30) = tailty;
        *(byte *)(slot + 0x38) = has_tail;
    } while (i != count);

    word_t desc = FUN_00466440();
    *(long *)(desc + 0x10) = 0;   /* extraout_x8_00 */
    return;
}

/* FUN_0041dae0 @ 0x41dae0  (est. sk_r63_alloc_box_chain)
 * Ghidra: undefined FUN_0041dae0(void)
 * Allocates a chain of Swift box nodes from a descriptor at x20. Reads a
 * length at x20[3]; if non-negative, iterates that many times allocating a
 * box (0x685d58) and linking it, marking each node with a flag, then runs
 * three teardown helpers. Overflow of the negative case traps via
 * SoftwareBreakpoint.
 * Confidence: medium
 * Notes: the 0x675c68 sentinel keeps id 0 when encountered. */
void sk_r63_alloc_box_chain(void)
{
    long *ctx = (long *)__builtin_frame_address(0);
    long n = ctx[3];
    if (-1 < n) {
        long v = ctx[0];
        long ty = ctx[1];
        long id = 0;
        if (ctx[2] != 0x675c68) {
            id = ctx[2];
        }
        byte flag = 0;
        long node = 0;
        for (; n != 0; n = n - 1) {
            FUN_00465ce8(0x685d58);
            long n2 = FUN_0036a940();
            *(byte *)(n2 + 0x28) = flag;
            flag = 1;
            *(long *)(n2 + 0x10) = v;
            *(long *)(n2 + 0x18) = ty;
            *(long *)(n2 + 0x20) = id;
            ty = 0;
            id = 0;
            v = n2;
        }
        FUN_00464e28();
        FUN_00458da0();
        FUN_00084180();
        return;
    }
    CL4_SW_BP(0x41dbb4);
}

/* FUN_0041dbb4 @ 0x41dbb4  (est. sk_r63_lex_amp)
 * Ghidra: undefined FUN_0041dbb4(void)
 * Character lexer: reads tokens from the input stream and returns a single
 * classification character. On hitting the '&' token it performs the
 * ampersand-handling branch (matching a following word or falling back to a
 * literal '&'), otherwise returns the plain character. Uses a loop that
 * skips whitespace/separators via the stream helpers.
 * Confidence: low
 * Notes: token-stream functions (FUN_0029fb80 etc.) are opaque out-of-slice;
 *   the (unaff_x22==0x5f/0x2d) tests are '_' and '-' separator checks. */
char sk_r63_lex_amp(void)
{
    char local_70[32];
    word_t local_50, uStack_48;
    word_t u;

    FUN_00463418();
    FUN_00464ef8();
    for (;;) {
        word_t stream_done = FUN_0029fb80();   /* extraout_x1 artifact: 0 => input exhausted */
        if (stream_done == 0) {
            FUN_003a25d4();
            FUN_0029d3d8(local_50, uStack_48);
            FUN_00351e08();
            FUN_003a25d4(uStack_48);
            FUN_0007c1c4(local_70);
            FUN_0041e28c();
            if (local_70[0] == '&') {
                FUN_00464180();
                FUN_0035053c();
                u = FUN_002abcb0();
                if ((u & 1) == 0) {
                    FUN_003a25d4();
                    local_70[0] = '&';
                } else {
                    FUN_00350624(2);
                    FUN_000b4660();
                    FUN_002a3e64();
                    FUN_0034bd90();
                    FUN_003a25d4();
                    FUN_0006b6f4(local_70);
                    FUN_0041e28c();
                    FUN_003a25d4(0x26);
                }
            } else {
                FUN_003a25d4();
            }
            return local_70[0];
        }
        FUN_0035aba4();
        FUN_001ae8a8();
        FUN_00464eec();
        u = FUN_002bc2dc();
        if ((u & 1) == 0) {
            /* separator-consume path ('_' then '-') guarded by compare flags */
            FUN_00100efc();
            FUN_00462fac();
            u = FUN_002a0cf8();
            if ((u & 1) == 0) {
                word_t a = 0, b = 0;
                FUN_00463540(a, b, 0x2d);
                u = FUN_002a0cf8();
                if ((u & 1) == 0) {
                    FUN_00100efc();
                    FUN_002acbb8();
                }
            }
        }
        FUN_003a25d4();
    }
    CL4_SW_BP(0x41dd0c);
}

/* FUN_0041de64 @ 0x41de64  (est. sk_r63_lex_0xac)
 * Ghidra: undefined FUN_0041de64(void)
 * Character lexer, sibling of sk_r63_lex_amp: reads stream tokens and
 * returns a classification character. The special token is 0xAC (the
 * ampersand/classifier variant that dispatches through FUN_004207b0); on
 * match it attempts to parse a following word and returns '&' or 0xAC
 * depending on success.
 * Confidence: low
 * Notes: FUN_004207b0 is the per-variant classifier callback. */
char sk_r63_lex_0xac(void)
{
    char local_70[32];
    word_t local_50, uStack_48;
    word_t u;

    FUN_00463418();
    FUN_00464ef8();
    for (;;) {
        word_t stream_done = FUN_0029fb80();
        if (stream_done == 0) {
            FUN_003a25d4();
            FUN_0029d3d8(local_50, uStack_48);
            FUN_00351e08();
            FUN_003a25d4(uStack_48);
            FUN_0007c1c4(local_70);
            FUN_004207b0();
            if (local_70[0] == (char)0xac) {
                FUN_00464180();
                FUN_0035053c();
                u = FUN_002abcb0();
                if ((u & 1) == 0) {
                    FUN_003a25d4();
                    local_70[0] = (char)0xac;
                } else {
                    FUN_00350624(2);
                    FUN_000b4660();
                    FUN_002a3e64();
                    FUN_0034bd90();
                    FUN_003a25d4();
                    FUN_0006b6f4(local_70);
                    FUN_004207b0();
                    FUN_003a25d4(0xac);
                }
            } else {
                FUN_003a25d4();
            }
            return local_70[0];
        }
        FUN_0035aba4();
        FUN_001ae8a8();
        FUN_00464eec();
        u = FUN_002bc2dc();
        if ((u & 1) == 0) {
            FUN_00100efc();
            FUN_00462fac();
            u = FUN_002a0cf8();
            if ((u & 1) == 0) {
                word_t a = 0, b = 0;
                FUN_00463540(a, b, 0x2d);
                u = FUN_002a0cf8();
                if ((u & 1) == 0) {
                    FUN_00100efc();
                    FUN_002acbb8();
                }
            }
        }
        FUN_003a25d4();
    }
    CL4_SW_BP(0x41dfbc);
}

/* FUN_0041dfbc @ 0x41dfbc  (est. sk_r63_lex_guard_a)
 * Ghidra: undefined FUN_0041dfbc(void)
 * Tiny lexer guard: runs two stream helpers and, unless a condition flag
 * (in_ZR artifact) is set, consumes the next token and returns; otherwise
 * traps. FUN_0041dfc0 is an identical twin.
 * Confidence: low
 * Notes: the register-flag condition cannot be pinned to a concrete value. */
void sk_r63_lex_guard_a(void)
{
    FUN_001ae8a8();
    FUN_0034ecc8();
    if (1 == 1) {   /* in_ZR artifact -- treat as unconditional continue */
        FUN_002bc2dc();
        return;
    }
    CL4_SW_BP(0x41dfe4);
}

/* FUN_0041dfc0 @ 0x41dfc0  (est. sk_r63_lex_guard_b)
 * Ghidra: undefined FUN_0041dfc0(void)
 * Identical twin of sk_r63_lex_guard_a.
 * Confidence: low */
void sk_r63_lex_guard_b(void)
{
    FUN_001ae8a8();
    FUN_0034ecc8();
    if (1 == 1) {   /* in_ZR artifact */
        FUN_002bc2dc();
        return;
    }
    CL4_SW_BP(0x41dfe4);
}

/* FUN_0041dfe4 @ 0x41dfe4  (est. sk_r63_range_clamp16)
 * Ghidra: undefined1[16] FUN_0041dfe4(long,undefined8,ulong,undefined8,undefined8)
 * Clamps a 16-byte value (param_1 count, param_3 range) into a bounded
 * region: checks param_1 non-negative, calls a range-build helper
 * (FUN_002b3f40), and if the resulting upper bound stays within the same
 * 0x4000 (14-bit) superpage as param_3 returns the clamped pair from
 * FUN_002b74c0; otherwise traps. Returns the 16-byte result in x0/x1.
 * Confidence: low
 * Notes: the 0xe-bit mask comparison is a 16 KB alignment check. */
cL4_w16_t sk_r63_range_clamp16(long count, word_t base, word_t range,
                               word_t p4, word_t p5)
{
    if (count < 0) {
        CL4_SW_BP(0x41e09c);
    }
    cL4_w16_t v = (cL4_w16_t)FUN_002b3f40(base, count, range, base, range, p4, p5);
    word_t u1 = range;
    if ((((word_t)v.lo >> 32) & 0xff) != 1) {
        u1 = v.lo;
    }
    if ((u1 >> 0xe) <= (range >> 0xe)) {
        cL4_w16_t r = (cL4_w16_t)FUN_002b74c0(u1, range, base, range, p4, p5);
        FUN_003a25d4(p5);
        return r;
    }
    CL4_SW_BP(0x41e0a0);
    return (cL4_w16_t){0,0};
}


/* FUN_0041dd0c @ 0x41dd0c  (est. sk_r63_lex_capsule)
 * Ghidra: undefined FUN_0041dd0c(void)
 * Character lexer, sibling of sk_r63_lex_amp/lex_0xac: the special token is
 * 'C' (0x43), dispatched through FUN_0041f074. Returns the classification
 * character, matching the ampersand-parsing fallback pattern.
 * Confidence: low
 * Notes: token-stream helpers opaque out-of-slice. */
char sk_r63_lex_capsule(void)
{
    char local_70[32];
    word_t local_50, uStack_48;
    word_t u;

    FUN_00463418();
    FUN_00464ef8();
    for (;;) {
        word_t stream_done = FUN_0029fb80();
        if (stream_done == 0) {
            FUN_003a25d4();
            FUN_0029d3d8(local_50, uStack_48);
            FUN_00351e08();
            FUN_003a25d4(uStack_48);
            FUN_0007c1c4(local_70);
            FUN_0041f074();
            if (local_70[0] == 'C') {
                FUN_00464180();
                FUN_0035053c();
                u = FUN_002abcb0();
                if ((u & 1) == 0) {
                    FUN_003a25d4();
                    local_70[0] = 'C';
                } else {
                    FUN_00350624(2);
                    FUN_000b4660();
                    FUN_002a3e64();
                    FUN_0034bd90();
                    FUN_003a25d4();
                    FUN_0006b6f4(local_70);
                    FUN_0041f074();
                    FUN_003a25d4(0x43);
                }
            } else {
                FUN_003a25d4();
            }
            return local_70[0];
        }
        FUN_0035aba4();
        FUN_001ae8a8();
        FUN_00464eec();
        u = FUN_002bc2dc();
        if ((u & 1) == 0) {
            FUN_00100efc();
            FUN_00462fac();
            u = FUN_002a0cf8();
            if ((u & 1) == 0) {
                word_t a = 0, b = 0;
                FUN_00463540(a, b, 0x2d);
                u = FUN_002a0cf8();
                if ((u & 1) == 0) {
                    FUN_00100efc();
                    FUN_002acbb8();
                }
            }
        }
        FUN_003a25d4();
    }
    CL4_SW_BP(0x41de64);
}


/* FUN_0041e0a0 @ 0x41e0a0  (est. sk_r63_region_insert_flags)
 * Ghidra: undefined FUN_0041e0a0(ulong,ulong,ulong)
 * Builds and applies a region-insert descriptor from three words: validates
 * the count is non-negative, extracts an alignment/size field from the
 * range bits (the 0x2000000000000000 flag picks a 4-bit field out of
 * param_3>>0x38), composes a 4-bit type with a 16-bit offset, handles the
 * 0x800000000000000 bit flag by calling a range-builder, and finally
 * invokes FUN_00460e78 to apply the descriptor. Fails closed on out-of-range
 * shifts.
 * Confidence: low
 * Notes: bit-level MMU/region descriptors; exact semantics inferred. */
void sk_r63_region_insert_flags(word_t count, word_t p2, word_t p3)
{
    word_t size, desc;

    if ((long)count < 0) {
        CL4_SW_BP(0x41e150);
    }
    size = p2 & 0xffffffffffff;
    if ((p3 & 0x2000000000000000ULL) != 0) {
        size = (p3 >> 0x38) & 0xf;
    }
    desc = (size << 0x10) | 7;
    if (((p3 >> 0x3c) & 1) == 0) {
        if (count <= size) {
            desc = (count << 0x10) | 4;
        }
    } else {
        if ((p2 & 0x800000000000000ULL) == 0) {
            desc = (size << 0x10) | 0xb;
        }
        cL4_w16_t v = (cL4_w16_t)FUN_001b28d4(0xf, count, desc, p2, p3);
        if ((((word_t)v.lo >> 32) & 0xff) != 1) {
            desc = v.lo;
        }
    }
    if ((size << 2) < (desc >> 0xe)) {
        CL4_SW_BP(0x41e188);
    }
    unsigned long mode = (p2 >> 0x3b) & 1;
    if ((p3 & 0x1000000000000000ULL) == 0) {
        mode = 1;
    }
    word_t mode2 = 7;
    if (mode == 0) {
        mode2 = 0xb;
    }
    FUN_00460e78(desc, (size << 0x10) | mode2, p2, p3);
}

/* FUN_0041e188 @ 0x41e188  (est. sk_r63_range_apply)
 * Ghidra: undefined FUN_0041e188(long,undefined8,ulong,undefined8,undefined8)
 * Validates count >= 0, builds a range via FUN_002b5e10, clamps the result
 * to the same 16 KB superpage as the input range, and applies it via
 * FUN_002ab388. Traps if the clamped range crosses a superpage boundary.
 * Confidence: low
 * Notes: 14-bit (0x4000) alignment check. */
void sk_r63_range_apply(long count, word_t base, word_t range, word_t p4, word_t p5)
{
    if (count < 0) {
        CL4_SW_BP(0x41e218);
    }
    cL4_w16_t v = (cL4_w16_t)FUN_002b5e10(base, count, range, base, range, p4, p5);
    word_t u1 = range;
    if ((((word_t)v.lo >> 32) & 0xff) != 1) {
        u1 = v.lo;
    }
    if ((u1 >> 0xe) <= (range >> 0xe)) {
        FUN_002ab388(u1, range, base, range, p4, p5);
        return;
    }
    CL4_SW_BP(0x41e21c);
}

/* FUN_0041e21c @ 0x41e21c  (est. sk_r63_array_slice)
 * Ghidra: undefined1[16] FUN_0041e21c(long param_1,long param_2)
 * Returns a (base,count+0x20) slice pair for an array descriptor at param_2.
 * Validates param_1 >= 0, computes the bounded length via FUN_003f8224, and
 * returns {param_2, param_2+0x20} when the slice stays in range; otherwise
 * traps.
 * Confidence: medium
 * Notes: returns a 16-byte pair; the +0x20 is the descriptor's element-array
 *   offset. */
cL4_w16_t sk_r63_array_slice(long count, word_t desc)
{
    if (count < 0) {
        CL4_SW_BP(0x41e284);
    }
    long len = *(long *)(desc + 0x10);
    cL4_w16_t v = (cL4_w16_t)FUN_003f8224(0, count, len, desc);
    long r = len;
    if ((((word_t)v.lo >> 32) & 0xff) != 1) {
        r = v.lo;
    }
    if (r <= len) {
        if (-1 < r) {
            cL4_w16_t out;
            out.lo = desc;
            out.hi = desc + 0x20;
            return out;
        }
        CL4_SW_BP(0x41e28c);
    }
    CL4_SW_BP(0x41e288);
    return (cL4_w16_t){0, 0};
}

