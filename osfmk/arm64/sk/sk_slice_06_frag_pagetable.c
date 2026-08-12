/* sk_slice_06_frag_pagetable.c — VAS page-table copy/count (packed PTE shuffle).

 * Recreated from cl4_kernel.raw (cL4 Secure Kernel, image base 0). These two
 * functions implement a page-table serialization scheme that shuffles PTEs
 * between a source array and a packed destination using 2-bit (code), 4-bit
 * (dedup slot) and 10-bit (offset) field packing. The compression relies on a
 * 16-slot dedup cache: PTEs sharing a page frame (upper 22 bits) collapse to a
 * single cached entry plus a 10-bit offset, and exact duplicates collapse to a
 * slot reference.
 *
 * Ground truth: Ghidra FUN_ names + addresses; firmware constant tables read
 * from the loaded image (DAT_004bc5e0 etc.). All names are estimates. */

#include "sk_slice_06_shared.h"

/* ------------------------------------------------------------------ *
 * Firmware constant tables (read from cl4_kernel.raw).
 *
 * sk_pt_hash    — DAT_004bc5e0, 256-byte lookup. Indexed by the low 8 bits of
 *                 the PTE page frame ((pte >> 10) & 0xff); returns a dedup-slot
 *                 byte offset into the 16-entry cache (values 4*{0..15}).
 * sk_pt_code_shl/_mask — _DAT_004bc6e0 / DAT_004bc6f0..6ff: NEON USHL shift
 *                 lanes {0,-2,-4,-6} and 0x03 byte masks used to expand the
 *                 packed 2-bit code words into the 4096-byte code array.
 * sk_pt_slot_shl/_mask — _DAT_004bc700 / DAT_004bc710..71f: shift lanes
 *                 {0,-4,0,-4} and 0x0f masks used to unpack the dedup-slot
 *                 nibbles.
 * sk_pt_off_shl — _DAT_004bc720 = {6,0,6,0} and DAT_004bc730 = {0,-20,0,-20},
 *                 with DAT_004bc740..75f masks; used to unpack the 10-bit
 *                 offset stream. The encode side packs 3 offsets (10 bits
 *                 each) per 32-bit word.
 * ------------------------------------------------------------------ */
static const uint8_t sk_pt_hash[256] = {
    0x00,0x34,0x08,0x38,0x10,0x0c,0x1c,0x14,0x04,0x24,0x30,0x18,0x2c,0x28,0x20,0x3c,
    0x08,0x0c,0x1c,0x14,0x04,0x3c,0x10,0x24,0x18,0x30,0x2c,0x20,0x34,0x38,0x28,0x0c,
    0x08,0x30,0x10,0x34,0x3c,0x1c,0x38,0x20,0x14,0x24,0x24,0x28,0x2c,0x04,0x08,0x28,
    0x3c,0x20,0x14,0x2c,0x04,0x24,0x34,0x18,0x10,0x38,0x30,0x0c,0x1c,0x10,0x08,0x28,
    0x24,0x1c,0x20,0x0c,0x04,0x2c,0x34,0x14,0x18,0x30,0x3c,0x38,0x28,0x30,0x08,0x20,
    0x1c,0x24,0x04,0x2c,0x14,0x38,0x3c,0x18,0x34,0x10,0x0c,0x0c,0x04,0x30,0x14,0x08,
    0x34,0x10,0x3c,0x18,0x24,0x2c,0x1c,0x38,0x28,0x20,0x24,0x14,0x18,0x3c,0x28,0x2c,
    0x34,0x10,0x20,0x04,0x30,0x08,0x1c,0x38,0x0c,0x1c,0x20,0x28,0x34,0x24,0x10,0x14,
    0x30,0x08,0x04,0x3c,0x18,0x38,0x2c,0x0c,0x08,0x24,0x18,0x1c,0x10,0x3c,0x14,0x38,
    0x20,0x28,0x30,0x0c,0x04,0x2c,0x34,0x2c,0x28,0x0c,0x38,0x08,0x24,0x18,0x3c,0x1c,
    0x30,0x04,0x20,0x14,0x10,0x34,0x3c,0x0c,0x24,0x24,0x08,0x04,0x10,0x38,0x30,0x2c,
    0x28,0x34,0x20,0x14,0x1c,0x20,0x0c,0x24,0x1c,0x18,0x38,0x28,0x10,0x34,0x2c,0x04,
    0x14,0x3c,0x08,0x30,0x30,0x34,0x0c,0x14,0x20,0x2c,0x24,0x1c,0x04,0x28,0x18,0x08,
    0x38,0x3c,0x10,0x24,0x20,0x08,0x28,0x04,0x34,0x18,0x2c,0x14,0x0c,0x1c,0x30,0x38,
    0x10,0x3c,0x04,0x34,0x3c,0x30,0x14,0x10,0x38,0x2c,0x18,0x08,0x28,0x0c,0x20,0x1c,
    0x24,0x18,0x20,0x0c,0x04,0x14,0x10,0x3c,0x24,0x1c,0x08,0x34,0x28,0x30,0x2c,0x38,
};

/* Dedup slot index for a PTE's page frame (low 8 bits of frame -> slot byte
 * offset). All values are 4*{0..15}. */
static inline uint32_t sk_pt_slot_of(uint32_t pte)
{
    return sk_pt_hash[(pte >> 10) & 0xff] >> 2;
}

/* Expand `n` packed 32-bit words (src[0..n)) into `n*16` code bytes at map.
 * Firmware does this with a NEON USHL (shift lanes {0,-2,-4,-6}) on a splat of
 * each word followed by 0x03 byte masks (DAT_004bc6e0/004bc6f0). Each output
 * byte j is the 2-bit field [2j+1:2j] of word j/16. */
static void sk_pt_expand_codes(uint8_t *map, const uint32_t *words)
{
    for (int j = 0; j < 0x1000; j++)
        map[j] = (uint8_t)((words[j >> 4] >> (2 * (j & 15))) & 3);
}

/* Expand `n` packed 32-bit words into `n*8` dedup-slot nibbles at map.
 * Firmware: NEON USHL shift lanes {0,-4,0,-4} (DAT_004bc700) on a
 * [lo,lo,hi,hi] splat, masked 0x0f (DAT_004bc710). Per word this yields the
 * low then high nibble of each byte, i.e. 4 slots + 4 zero high-nibbles. */
static void sk_pt_expand_slots(uint8_t *map, const uint32_t *words, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        uint32_t w = words[i];
        map[8 * i + 0] = (uint8_t)((w >> 0) & 0xf);
        map[8 * i + 1] = (uint8_t)((w >> 8) & 0xf);
        map[8 * i + 2] = (uint8_t)((w >> 16) & 0xf);
        map[8 * i + 3] = (uint8_t)((w >> 24) & 0xf);
        map[8 * i + 4] = (uint8_t)((w >> 4) & 0xf);
        map[8 * i + 5] = (uint8_t)((w >> 12) & 0xf);
        map[8 * i + 6] = (uint8_t)((w >> 20) & 0xf);
        map[8 * i + 7] = (uint8_t)((w >> 28) & 0xf);
    }
}

/* Expand `n` packed 32-bit words into the flat 10-bit offset stream at map.
 * The encode side packs 3 offsets (10 bits each) per word; this is the inverse
 * (DAT_004bc720/004bc730 shifts, 0x03ff masks at DAT_004bc740..75f). */
static void sk_pt_expand_offsets(uint16_t *map, const uint32_t *words, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        uint32_t p = words[i];
        map[3 * i + 0] = (uint16_t)((p >> 0) & 0x3ff);
        map[3 * i + 1] = (uint16_t)((p >> 10) & 0x3ff);
        map[3 * i + 2] = (uint16_t)((p >> 20) & 0x3ff);
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000304d0 @ 0x000304d0  (est. sk_vas_pt_write)
 * Ghidra: void FUN_000304d0(uint*,uint*,byte*,long)
 * Decodes a page-table encoding into `dst`. If `src[0]` carries the magic
 * 0x4321 the encoding is the packed-sparse form: `dst` is zeroed (4096 u32,
 * via DC ZVA) and (value, byte-offset) 6-byte records are applied. Otherwise
 * encoding is the unpacked form and the map scratch buffer (map[0..0x1000)
 * codes, map[0x1000..) dedup slots, map[0x2000..) 10-bit offsets) is
 * rebuilt from the header fields in `src[0..2]` and then walked to emit the
 * PTE array, maintaining the 16-slot dedup cache as it goes.
 * Confidence: high
 * Notes: constants DAT_004bc5e0/6e0/6f0/700/710/720/730/740; magic 0x4321;
 *   NEON USHL transposes rendered as scalar loops. */
static void sk_vas_pt_write(uint32_t *dst, uint32_t *src, uint8_t *map, uint64_t off)
{
    uint32_t dedup[16];

    if (src[0] == 0x4321) {
        /* Packed-sparse form: zero the whole 4096-entry table, then scatter
         * the sparse 6-byte records [value u32][byte-offset u16]. */
        sk_mem_zero(dst, 0, 0x4000);            /* DC ZVA loop zeroes 0x4000 B */
        uint64_t rec = 4;                        /* skip the magic word */
        while (rec != off) {
            uint32_t value  = *(const uint32_t *)((const uint8_t *)src + rec);
            uint16_t offset = *(const uint16_t *)((const uint8_t *)src + rec + 4);
            *(uint32_t *)((uint8_t *)dst + offset) = value;
            rec += 6;
        }
        return;
    }

    /* Unpacked form: rebuild the map scratch structures from the header. */
    sk_mem_zero(dedup, 0, sizeof dedup);         /* clear 16 dedup slots */

    /* 1) Codes: the 256 packed words at src[3..0x103) become 4096 code bytes. */
    sk_pt_expand_codes(map, src + 3);

    /* 2) Dedup slots: region src[src[0] .. src[1]) carries packed slot words. */
    uint32_t slot_a = src[0];
    uint32_t slot_b = src[1];
    sk_pt_expand_slots(map + 0x1000, src + slot_a, slot_b - slot_a);

    /* 3) 10-bit offsets: region src[src[1] .. src[2]) carries packed offsets. */
    uint32_t off_b = src[2];
    sk_pt_expand_offsets((uint16_t *)(map + 0x2000), src + slot_b, off_b - slot_b);

    /* 4) Walk the code array and emit the reconstructed PTE table. */
    const uint8_t  *code = map;
    const uint8_t  *slot = map + 0x1000;
    const uint16_t *offs = (const uint16_t *)(map + 0x2000);
    const uint32_t *full = src + 0x103;
    int32_t left = 0x1000;                       /* up to 4096 entries */
    while (left != 0) {
        uint8_t c = *code++;
        if (c == 0) {
            *dst++ = 0;                          /* zero page */
        } else if (c == 2) {
            uint32_t pte = *full++;              /* full new page */
            *dst++ = pte;
            dedup[sk_pt_slot_of(pte)] = pte;
        } else if (c == 3) {
            *dst++ = dedup[*slot++];             /* exact duplicate */
        } else {                                 /* c == 1: page frame reused */
            uint32_t base = dedup[*slot];
            uint32_t v = (base & 0xfffffc00) | (*offs++ & 0x3ff);
            dedup[*slot++] = v;
            *dst++ = v;
        }
        left--;
    }
}

/* ------------------------------------------------------------------ *
 * FUN_00030780 @ 0x00030780  (est. sk_vas_pt_count)
 * Ghidra: ulong FUN_00030780(uint*,uint*,char*,long)
 * Encodes up to 4096 PTEs from `src` into `dst` (with `map` as scratch),
 * compressing repeated page frames via a 16-slot dedup cache. Per entry a code
 * byte is written to map[0..): 0 = zero, 1 = page frame reused (dedup slot to
 * map[0x1000), low 10 bits to map[0x2000)), 2 = full new entry (word appended
 * to `dst`), 3 = exact duplicate (dedup slot to map[0x1000)). If the result
 * packs tightly a magic-0x4321 sparse form is emitted; otherwise the unpacked
 * form is emitted. Returns the encoded size in bytes, 0 for a degenerate input
 * (caller substitutes 4), or -1 on overflow.
 * Confidence: high
 * Notes: constants DAT_004bc5e0; the decode counterpart is sk_vas_pt_write;
 *   caller sk_cap_split (FUN_0002fb88) treats return 0 as size 4 and <1 as
 *   error 0x1510002. */
static uint64_t sk_vas_pt_count(uint32_t *dst, uint32_t *src, char *map, uint64_t n)
{
    uint8_t  dedup[64];                          /* 16 x 4-byte dedup slots */
    uint8_t *code_out = (uint8_t *)map;          /* per-entry code byte */
    uint8_t *slot_out = (uint8_t *)map + 0x1000; /* dedup slot per code 1/3 */
    uint16_t *off_out = (uint16_t *)(map + 0x2000); /* low 10 bits per code 1 */
    uint32_t *full_out = dst + 0x103;            /* full entries land here */

    sk_mem_zero(dedup, 0, sizeof dedup);
    uint32_t *full = full_out;
    uint8_t  *slot = slot_out;
    uint16_t *offs = off_out;
    const uint32_t *srcp = src;
    int64_t full_space = (int64_t)n - 0x40c;     /* capacity for full entries */
    int64_t budget = 0x1a0;                      /* phase-1 entry budget */
    bool phase2 = false;

    for (;;) {
        const uint8_t *code_here = code_out;
        uint32_t pte = *srcp++;
        if (pte == 0) {
            *code_out++ = 0;
        } else {
            uint32_t slot_off = sk_pt_hash[(pte >> 10) & 0xff]; /* byte offset */
            uint32_t slot_no  = slot_off >> 2;
            uint32_t hit = *(uint32_t *)(dedup + slot_off) ^ pte;
            if (hit == 0) {
                /* Exact duplicate of a cached page: code 3. */
                *code_out++ = 3;
                *slot++ = (uint8_t)slot_no;
            } else if (hit >> 10 == 0) {
                /* Same page frame, different 10-bit offset: code 1. */
                *code_out++ = 1;
                *(uint32_t *)(dedup + slot_off) = pte;
                *slot++ = (uint8_t)slot_no;
                *offs++ = (uint16_t)(pte & 0x3ff);
            } else {
                /* Entirely new page frame: code 2, store the full entry. */
                int64_t sp = full_space - 4;
                if (sp == 0 || full_space < 4)
                    return (uint64_t)-1;
                *full++ = pte;
                *(uint32_t *)(dedup + slot_off) = pte;
                *code_out++ = 2;
                full_space = sp;
            }
        }

        /* Dedup-slot records are only emitted for codes 1 and 3; the shared
         * entry budget (phase 1 = 0x1a0, phase 2 = 0xe60, total 0x1000) is
         * consumed one per source PTE. */
        if (--budget == 0) {
            if (phase2)
                break;                            /* 4096 entries done */
            /* Between phases: sanity-check the encoded size so far. */
            int64_t est = (int64_t)((uint8_t *)full - (uint8_t *)full_out)
                        + ((int64_t)((uint8_t *)slot - (uint8_t *)slot_out) >> 1)
                        + (((int64_t)((uint8_t *)offs - (uint8_t *)off_out) * 0x555) >> 0xb);
            if (est > 0x640)
                return (uint64_t)-1;
            phase2 = true;
            budget = 0xe60;
        }
    }

    /* Both phases complete: decide whether the packed-sparse form fits. */
    if ((uint8_t *)full == (uint8_t *)full_out &&
        (uint8_t *)slot == (uint8_t *)slot_out)
        return 0;                                 /* all-zero input */

    uint32_t full_words = (uint32_t)((uint8_t *)full - (uint8_t *)full_out) >> 2;
    int64_t  slot_bytes = (uint8_t *)slot - (uint8_t *)slot_out;
    uint32_t off_words  = (uint32_t)((uint8_t *)offs - (uint8_t *)off_out) >> 1;

    /* Degenerate fast paths: a lone full entry followed by duplicates, or a
     * single page frame with offsets, already fit the smallest forms. */
    if (!(((off_words != 0) || (slot_bytes != 0xfff) || (full_words != 1) ||
           (*map != 2)) &&
          ((off_words != 1) || (slot_bytes != 0x1000) || (*map != 1)))) {
        return 0;
    }

    /* General packed-sparse size: 4-byte magic + 6 bytes per (full word or
     * slot byte). Accept if it beats the current unpacked estimate. */
    uint64_t packed = ((uint64_t)full_words + (uint64_t)slot_bytes) * 6 + 4;
    int64_t est = (int64_t)((uint8_t *)full - (uint8_t *)full_out)
                + ((int64_t)((uint8_t *)slot - (uint8_t *)slot_out) >> 1)
                + (((int64_t)((uint8_t *)offs - (uint8_t *)off_out) * 0x555) >> 0xb);
    if ((int64_t)packed <= est + 0x40c) {
        if (n < packed)
            return (uint64_t)-1;
        /* Emit the magic-0x4321 sparse form: one 6-byte (value, byte-offset)
         * record per nonzero word of src. */
        uint32_t *out = dst + 1;
        *dst = 0x4321;
        for (uint64_t i = 0; i < 0x4000; i += 8) {
            uint64_t pair = *(const uint64_t *)((const uint8_t *)src + i);
            if (pair != 0) {
                if ((uint32_t)pair != 0) {
                    *out = (uint32_t)pair;
                    *(uint16_t *)((uint8_t *)out + 4) = (uint16_t)i;
                    out = (uint32_t *)((uint8_t *)out + 6);
                }
                uint32_t hi = (uint32_t)(pair >> 32);
                if (hi != 0) {
                    *out = hi;
                    *(uint16_t *)((uint8_t *)out + 4) = (uint16_t)(i + 4);
                    out = (uint32_t *)((uint8_t *)out + 6);
                }
            }
        }
        return packed;
    }

    /* Unpacked form. Header word 0 = end of the full-entry region (in words).
     * The 4096 code bytes are re-packed 32-bytes-to-2-words into dst+3. */
    *dst = (uint32_t)(((uint8_t *)full - (uint8_t *)dst) >> 2) & 0x3fffffff;
    uint32_t *out = dst + 3;
    const uint8_t *codes = (const uint8_t *)map;
    const uint8_t *codes_end = code_out;
    while (codes < codes_end) {
        uint32_t lo = 0, hi = 0;
        for (int i = 0; i < 16; i++) {
            lo |= (uint32_t)((codes[i] & 3) << (2 * i));
            hi |= (uint32_t)((codes[i + 16] & 3) << (2 * i));
        }
        out[0] = lo;
        out[1] = hi;
        out += 2;
        codes += 0x20;
    }

    /* Pack the dedup-slot bytes 4-per-word into the region that follows the
     * codes. Zero-pad the slot array up to the next 8-byte boundary first. */
    uint32_t slot_round = (uint32_t)(((uint8_t *)slot - (uint8_t *)slot_out) + 7) >> 3;
    uint8_t *slot_end = slot_out + slot_round;
    if (full_space < (int64_t)(slot_round * 4))
        return (uint64_t)-1;
    while (slot < slot_end)                       /* pad to 8-byte multiple */
        *slot++ = 0;
    uint32_t hdr = *dst;
    for (uint8_t *s = slot_out; s < slot_end; s += 4) {
        uint32_t pack = ((uint32_t)s[0]) | ((uint32_t)s[1] << 8)
                      | ((uint32_t)s[2] << 16) | ((uint32_t)s[3] << 24);
        *full++ = pack;
    }
    hdr = (uint32_t)(((uint8_t *)full - (uint8_t *)dst) >> 2);
    dst[1] = hdr;

    /* Pack the 10-bit offset ushorts 3-per-word to finish the unpacked form.
     * Each word holds offs[0] | offs[1]<<10 | offs[2]<<20. */
    int32_t off_count = (int32_t)(((uint8_t *)offs - (uint8_t *)off_out) >> 1);
    full_space -= (int64_t)(slot_round * 4);
    const uint16_t *osrc = off_out;
    while (off_count >= 3) {
        if (full_space < 4)
            return (uint64_t)-1;
        uint32_t p = (uint32_t)osrc[0] | ((uint32_t)osrc[1] << 10)
                   | ((uint32_t)osrc[2] << 20);
        *full++ = p;
        full_space -= 4;
        osrc += 3;
        off_count -= 3;
    }
    /* Tail: 1..2 leftover offsets. */
    if (off_count != 0) {
        if (full_space < 5)
            return (uint64_t)-1;
        uint32_t t = (uint32_t)osrc[0];
        if (off_count == 2)
            t |= (uint32_t)osrc[1] << 10;
        *full++ = t;
    }
    dst[2] = (uint32_t)(((uint8_t *)full - (uint8_t *)dst) >> 2) & 0x3fffffff;
    return (uint64_t)(((uint8_t *)full - (uint8_t *)dst) >> 2) << 2;
}
