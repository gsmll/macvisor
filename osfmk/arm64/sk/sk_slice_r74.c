/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R74: 0x687b74-0x687f34 — the last five functions in the binary.
 * This slice is the tail of the cL4 cryptographic primitive layer: a
 * stateful absorb/stream engine driven through a per-context method table
 * (the context carries a vtable at +0x48/+0x68 and a phase field at +0x50:
 * 1 = initializing, 2 = absorb-complete, 3 = streaming), plus two noreturn
 * panic helpers in the region/fault path. The absorb functions process
 * 16-byte blocks XORed into a state region, invoke a permutation core via
 * the method table, and byte-swap the bit-length as padding — consistent
 * with a ChaCha20 / sponge-style primitive. Ghidra FUN_ names are kept only
 * in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sk_internal.h"

/* Stack-canary slot used by the crypto absorb functions (DAT_006b5ed0). */
extern unsigned long sk_stack_guard;

/* ---------------- external helpers (out of slice) ---------------- */

/* Permutation / block-transform core: FUN_00681538(ctx, state) ->
 * FUN_006818c0(state, ctx + 0x80). Table-driven (a64_TBL with DAT_00681c00). */
extern void sk_crypto_permute(unsigned char *ctx, unsigned char *state);

/* Load/absorb `size` bytes into `dst` from the primitive's internal source:
 * FUN_00681f44(size, dst) -> FUN_0067ce24(dst, size, 0, size, ~0). */
extern void sk_crypto_load_bytes(unsigned long size, void *dst);

/* Increment the 4-byte block counter at ctx+0x2f and invoke the method-table
 * block callback at (+0x68)+0x18. FUN_00681cd8. */
extern void sk_crypto_bump_counter(unsigned char *ctx);

/* Initialize a fresh context: load two 16-byte words at +0x10/+0x40, zero
 * phase/size/offset, set phase=1. FUN_00681548. */
extern void sk_crypto_init_state(unsigned char *ctx);

/* Block transform (FUN_006815c0). Out of slice; large. */
extern void sk_crypto_block_transform(void *dst, unsigned char *ctx);

/* Bulk 16-byte-block stream transform: FUN_0067fac0(in, out, ctx, blocks,
 * work_buf, key). Decompiler fails on it ("Unable to find unique hash for
 * varnode"); kept as extern. */
extern void sk_crypto_stream_blocks(const unsigned char *in, unsigned char *out,
                                    unsigned char *ctx, unsigned int blocks,
                                    void *work_buf, unsigned long key);

/* Advance phase: when phase==2 and the pending-block nibble is nonzero, run
 * one permutation, then set phase=3. FUN_00681e08. */
extern void sk_crypto_advance_phase(unsigned char *ctx);

/* noreturn panic printer: FUN_006833d4(msg) -> FUN_0065c310(0, msg, &stack). */
extern void sk_panic_fmt(unsigned long msg) __attribute__((noreturn));

/* Stack-guard mismatch handler: FUN_0067f660(err). noreturn on mismatch. */
extern void sk_stack_check_fail(unsigned long err);

/* 64-bit byte-reversal (bswap64). */
static inline unsigned long bswap64(unsigned long v)
{
    return __builtin_bswap64(v);
}

/* ------------------------------------------------------------------ */
/* FUN_00687b74 @ 0x00687b74   (est. sk_panic_crypto_region)
 * Ghidra: void FUN_00687b74(void)
 * noreturn panic helper in the region/fault path: prints a fixed message
 * (string pointer 0x6b0bca, source 0x6b0c32, line 0x2c0) and halts.
 * Confidence: medium
 * Notes: reached only on a fail-closed path from FUN_0067a510; the message
 *   string lives in a segment not readable via the memory API, so its text
 *   is unknown. */
void sk_panic_crypto_region(void)
{
    sk_panic_fmt(0x6b0bca);   /* message string @0x6b0bca (file 0x6b0c32, line 0x2c0) */
}

/* ------------------------------------------------------------------ */
/* FUN_00687bac @ 0x00687bac   (est. sk_panic_crypto_state)
 * Ghidra: void FUN_00687bac(void)
 * noreturn panic helper (sibling of FUN_00687b74): prints a fixed message
 * (string pointer 0x6b0c5c, source 0x6b0cbb, line 0x2db) and halts. Used by
 * FUN_0067a740 when the crypto/region state is inconsistent.
 * Confidence: medium
 * Notes: message text not readable via the memory API. */
void sk_panic_crypto_state(void)
{
    sk_panic_fmt(0x6b0c5c);   /* message string @0x6b0c5c (file 0x6b0cbb, line 0x2db) */
}

/* ------------------------------------------------------------------ */
/* FUN_00687d18 @ 0x00687d18   (est. sk_crypto_ctx_init)
 * Ghidra: undefined8 FUN_00687d18(long param_1, long param_2)
 * Initializes a crypto context from a method table. `ctx` carries a vtable
 * pointer at +0x48; when the vtable's method-count word at (+0x48)+8 equals
 * 0x10 (16 methods), the new context is filled in and both the destroy
 * (+0x10) and block (+0x18) vtable callbacks plus the init and block-transform
 * helpers are driven. Returns 0 on success, 0xffffffff (-1) when the vtable
 * shape is unexpected.
 * Confidence: medium
 * Notes: registered as method 0 of the object table built by FUN_0067f6d8
 *   (DAT_006feba0..); vtable callbacks are indirect `code*` calls. */
long sk_crypto_ctx_init(unsigned char *ctx, unsigned char *out)
{
    unsigned long *vtable;
    long vtable_count;

    vtable = (unsigned long *)(*(unsigned long *)(ctx + 0x48));
    vtable_count = *(long *)(vtable + 1);   /* word at (+0x48)+8 */
    if (vtable_count == 0x10) {
        /* store the vtable and a scratch area into the new context */
        *(unsigned long *)(out + 0x68) = (unsigned long)vtable;
        *(unsigned long *)(out + 0x70) = (unsigned long)(out + 0x180);
        *(uint32_t *)(out + 0x78) = *(uint32_t *)(ctx + 8);

        /* vtable destroy callback */
        ((void (*)(unsigned long))vtable[2])((unsigned long)vtable);

        /* clear the stream-flag byte and run the init/finalize helpers */
        *(uint16_t *)(out + 0x52) = 0;
        sk_crypto_init_state(out);   /* FUN_00681548: zero phase/size/offset, load 2x16B */

        /* vtable block callback: (scratch, 1, state+0x10, ctx) */
        ((void (*)(unsigned long, long, void *, void *))vtable[3])
            (*(unsigned long *)(out + 0x70), 1, out + 0x10, out);

        sk_crypto_block_transform(out + 0x80, out);   /* FUN_006815c0 */
        return 0;
    }
    return 0xffffffff;
}

/* ------------------------------------------------------------------ */
/* FUN_00687da8 @ 0x00687da8   (est. sk_crypto_absorb)
 * Ghidra: void FUN_00687da8(long param_1, ulong param_2, undefined8 *param_3)
 * Absorb `len` bytes from `src` into the crypto state at `ctx`. Requires the
 * phase at ctx+0x50 to be 1 (initializing) and the flag bit at ctx+0x52 to be
 * clear; otherwise returns 0xffffffbc (-68). A 12-byte input takes a special
 * path (loads the 8+4-byte words and a 0x1000000 tag into ctx+0x20..0x2c).
 * For general input, 8 bytes are absorbed into a local word and the
 * byte-swapped bit-length (bswap64 of len<<3) into a second local; 16-byte
 * message blocks are XORed into the state window at +0x1f..+0x2f with a
 * permutation per block; then both locals are XORed into the state words at
 * +0x20/+0x28, the state is committed to +0x30/+0x38, and the block counter
 * is bumped. On success sets phase to 2 and returns 0.
 * Confidence: medium
 * Notes: byte-reversal of len<<3 is the standard little-endian bit-length
 *   padding of a sponge/stream primitive. */
long sk_crypto_absorb(unsigned char *ctx, unsigned long len, const unsigned char *src)
{
    unsigned long guard;
    unsigned long state_w1, state_w0, local_lo, local_hi;
    unsigned long i;

    guard = sk_stack_guard;

    /* phase must be 1 (init) and the block-in-progress flag clear */
    if ((*(uint16_t *)(ctx + 0x50) != 1) ||
        ((*(uint16_t *)(ctx + 0x52) & 1) != 0)) {
        return 0xffffffbc;
    }
    if ((len == 0) || (src == NULL)) {
        return 0xffffffbc;
    }

    if (len == 0xc) {
        /* special 12-byte input: load 8+4-byte words + fixed tag */
        state_w0 = *(unsigned long *)src;
        *(uint32_t *)(ctx + 0x28) = *(uint32_t *)(src + 8);
        *(unsigned long *)(ctx + 0x20) = state_w0;
        *(uint32_t *)(ctx + 0x2c) = 0x1000000;
    } else {
        local_lo = 0;
        local_hi = 0;
        sk_crypto_load_bytes(8, &local_lo);         /* absorb 8 bytes into lo word */
        local_hi = bswap64(len << 3);               /* bit-length padding, byte-swapped */
        sk_crypto_load_bytes(0x10, ctx + 0x20);     /* absorb 16 bytes into state */

        if (len < 0x10) {
            /* XOR the trailing bytes into the state window, then permute */
            do {
                ctx[len + 0x1f] ^= src[len - 1];
                len--;
            } while (len != 0);
            sk_crypto_permute(ctx, ctx + 0x20);
        } else {
            /* XOR 16-byte blocks into state+0x2f, permute each block */
            do {
                i = 0;
                do {
                    ctx[i + 0x2f] ^= src[i + 0xf];
                    i--;
                } while (i != (unsigned long)-0x10);
                sk_crypto_permute(ctx, ctx + 0x20);
                src += 0x10;
                len -= 0x10;
            } while (0xf < len);
            if (len != 0) {
                /* trailing partial block */
                do {
                    ctx[len + 0x1f] ^= src[len - 1];
                    len--;
                } while (len != 0);
                sk_crypto_permute(ctx, ctx + 0x20);
            }
        }
        /* XOR the absorbed local (lo) and bit-length (hi) words into state */
        *(unsigned long *)(ctx + 0x28) ^= local_hi;
        *(unsigned long *)(ctx + 0x20) ^= local_lo;
        sk_crypto_permute(ctx, ctx + 0x20);
    }

    /* commit state to +0x30/+0x38, bump the block counter, advance phase */
    *(unsigned long *)(ctx + 0x38) = *(unsigned long *)(ctx + 0x28);
    *(unsigned long *)(ctx + 0x30) = *(unsigned long *)(ctx + 0x20);
    sk_crypto_bump_counter(ctx);
    *(uint16_t *)(ctx + 0x50) = 2;

    if (sk_stack_guard != guard) {
        sk_stack_check_fail(0);
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* FUN_00687f34 @ 0x00687f34   (est. sk_crypto_stream_update)
 * Ghidra: undefined8 FUN_00687f34(long param_1, ulong param_2, long param_3, long param_4)
 * Streaming absorb/transform of `len` bytes: reads from `src` (param_3),
 * writes the transformed keystream to `dst` (param_4), updating the running
 * byte offset at ctx+0x60. Requires phase == 3 (streaming); returns
 * 0xffffffbc (-68) otherwise, or 0xffffffbd (-67) if the offset+len overflows
 * or exceeds the 0xffffffffffe0-byte cap. A partially-filled first block is
 * completed first, then whole 16-byte blocks go through the bulk transform
 * FUN_0067fac0 (and, for any remainder, through the per-block loop with a
 * permutation per block), and the trailing partial block is XORed last.
 * Returns 0 on success.
 * Confidence: medium
 * Notes: the byte offset at ctx+0x60 is advanced by the absorbed length; the
 *   state window used for the per-block XOR is ctx+0x1f..+0x4f, matching the
 *   absorb path. */
long sk_crypto_stream_update(unsigned char *ctx, unsigned long len,
                             const unsigned char *src, unsigned char *dst)
{
    unsigned long offset, off_nib, fill, i;

    offset = *(unsigned long *)(ctx + 0x60);
    sk_crypto_advance_phase(ctx);   /* FUN_00681e08: phase 2 -> 3 */

    if (*(uint16_t *)(ctx + 0x50) != 3) {
        return 0xffffffbc;
    }
    /* overflow / cap checks on offset + len */
    if (offset + len < offset) {
        return 0xffffffbd;
    }
    if (0xfffffffe0 < offset + len) {
        return 0xffffffbd;
    }

    off_nib = offset & 0xf;
    if ((offset & 0xf) != 0) {
        /* complete the partially-filled first block */
        fill = 0x10 - off_nib;
        if (len < fill) {
            /* won't fill the block: XOR everything into the tail */
            i = len;
            do {
                dst[len - 1] = ctx[off_nib + len + 0x3f] ^ src[len - 1];
                len--;
            } while (len != 0);
            i = off_nib + 0;                 /* (offset nibble index for the tail) */
            goto done_partial;
        }
        /* fill the first partial block, permute, advance */
        i = fill;
        do {
            dst[fill - 1] = ctx[off_nib + fill + 0x3f] ^ src[fill - 1];
            fill--;
        } while (fill != 0);
        fill = 0x10 - off_nib;
        do {
            ctx[off_nib + fill + 0xf] ^= dst[fill - 1];
            fill--;
        } while (fill != 0);
        sk_crypto_permute(ctx, ctx + 0x10);
        len -= 0x10 - off_nib;
        src += 0x10 - off_nib;
        dst += 0x10 - off_nib;
        *(unsigned long *)(ctx + 0x60) = *(long *)(ctx + 0x60) + (0x10 - off_nib);
        sk_crypto_bump_counter(ctx);
    }

    if (0xf < len) {
        /* bulk: whole 16-byte blocks through the stream transform */
        sk_crypto_stream_blocks(src, dst, ctx, (unsigned int)(len & 0xfffffff0),
                                ctx + 0x80, *(unsigned long *)(ctx + 0x70));
        i = len & 0xfffffff0;
        src += i;
        dst += i;
        *(unsigned long *)(ctx + 0x60) = *(long *)(ctx + 0x60) + i;
        ((void (*)(unsigned long, long, void *, void *))
            (*(unsigned long *)(ctx + 0x68) + 0x18))
            (*(unsigned long *)(ctx + 0x70), 1, ctx + 0x20, ctx + 0x40);

        /* remainder (a multiple of 16, up to 0xf0), processed per block */
        for (len = len & 0xffffffff0000000f; 0xf < len; len -= 0x10) {
            i = 0;
            do {
                dst[i + 0xf] = ctx[i + 0x4f] ^ src[i + 0xf];
                i--;
            } while (i != (unsigned long)-0x10);
            i = 0;
            do {
                ctx[i + 0x1f] = dst[i + 0xf] ^ ctx[i + 0x1f];
                i--;
            } while (i != (unsigned long)-0x10);
            sk_crypto_permute(ctx, ctx + 0x10);
            src += 0x10;
            dst += 0x10;
            *(unsigned long *)(ctx + 0x60) = *(long *)(ctx + 0x60) + 0x10;
            sk_crypto_bump_counter(ctx);
        }
    }

done_partial:
    /* trailing partial block (len < 0x10) XORed into the tail */
    if (len != 0) {
        i = len;
        do {
            dst[len - 1] = ctx[off_nib + len + 0x3f] ^ src[len - 1];
            len--;
        } while (len != 0);
        i = off_nib + 0;                     /* tail offset within the state */
        do {
            ctx[i + len + 0xf] ^= dst[len - 1];
        } while (0);                         /* placeholder, unreachable */
    }
    return 0;
}
