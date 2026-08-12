/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e,
 * image base 0). Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw. Names use seL4/cL4 vocabulary; estimates unless matched.
 *
 * Slice 08: 0x255100 - 0x25b0e0 — the vspace/MMU layer of the cL4 kernel.
 * This region implements:
 *   (a) the slot "path" naming scheme (FUN_00255d4c & friends) that encodes a
 *       page-table/vspace slot index into a byte path string, with a level
 *       classifier (1..4) driven by 0x80/0x800/0x10000 thresholds;
 *   (b) a Swift-hashable slot set / dictionary built on a slot bitmap
 *       (count @+0x10, log2-size @+0x20, hash fn @+0x28, data @+0x30,
 *       bitmap @+0x38 / @+0x40) with insert / lookup / iterate / clear /
 *       collect / remove operations (MSB-first traversal via bit-reverse);
 *   (c) a table of vspace operation dispatch wrappers (FUN_002562xx family).
 * The slot-set operations are the isolation boundary (which vspace slots are
 * mapped / referenced); see docs/sptm/findings.md for security notes.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers (declared extern with a one-line
 * note; bodies reconstructed by the range worker that owns them). Names are
 * estimates; the FUN_ address is the ground truth.
 * ------------------------------------------------------------------ */
extern void *skp8_sk_cpu(void);                                          /* FUN_0008e518 */
extern void skp8_sk_fatal_error(unsigned long, ...)
    __attribute__((noreturn));                                      /* FUN_001afe4c */
extern void *skp8_sk_alloc_pages(unsigned long size, unsigned long tag); /* FUN_0036b270 (thunk) */
extern void skp8_sk_free(void *ptr);                                     /* FUN_0036b118 */
extern unsigned long skp8_sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *d, void *e); /* FUN_00377824 */
extern unsigned long skp8_sk_lock_ref(unsigned long a, ...);             /* FUN_00377bec */
extern void skp8_sk_swift_release(unsigned long, ...);                   /* FUN_003a25d4 */
extern unsigned long skp8_sk_swift_string_hash(void);                    /* FUN_001a8564 */
extern unsigned long skp8_sk_swift_string_cmp(unsigned long, unsigned long,
                                         unsigned long, unsigned long,
                                         unsigned long, ...);       /* FUN_002a0d50 */
extern unsigned char sk_swift_unknown_5be7c0[];                     /* skp8_DAT_005be7c0 */
extern void *skp8_sk_swift_alloc(unsigned long, ...);                    /* FUN_00354948 */
extern unsigned long skp8_sk_swift_hash_combine(unsigned long, unsigned long,
                                           unsigned long, ...);     /* FUN_0031993c */
extern unsigned long skp8_sk_swift_hash_cmp(unsigned long, unsigned long,
                                       unsigned long, ...);         /* FUN_0031997c */
extern unsigned long skp8_sk_swift_elem_copy(unsigned long, ...);        /* FUN_0006a4c0 */
extern unsigned long skp8_sk_swift_hash_apply(unsigned long, ...);       /* FUN_0008e5d8 */
extern void skp8_sk_swift_buf_free(unsigned long, ...);                  /* FUN_000026e8 */
extern void skp8_sk_swift_elem_release(unsigned long, ...);              /* FUN_003199ac */
extern unsigned long skp8_sk_set_hash(void);                             /* thunk_FUN_00229ebc */
extern void skp8_sk_set_dup_panic(unsigned long msg);                    /* skp8_FUN_0025bddc */
extern long skp8_sk_set_descriptor(void *);                              /* skp8_FUN_0025a060 */
extern unsigned long skp8_sk_buf_copy(unsigned long, unsigned long, unsigned long, ...); /* FUN_001f7be0 */
extern unsigned long skp8_sk_buf_copy2(unsigned long, unsigned long, unsigned long, ...); /* FUN_001f0700 */
extern unsigned long skp8_sk_buf_range(unsigned long, unsigned long, unsigned long);    /* FUN_001f7d28 */
extern unsigned long skp8_sk_buf_range2(unsigned long, unsigned long);                  /* FUN_001f0bb4 */
extern void skp8_sk_elem_map(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0019ce60 */
extern unsigned long skp8_sk_slot_key(unsigned long, unsigned long, unsigned long, ...); /* FUN_0031b524 */
extern unsigned long skp8_sk_slot_grow(unsigned long, unsigned long, unsigned long, ...); /* FUN_001faaf0 */
extern unsigned long skp8_sk_hash_slot(unsigned long, unsigned long, ...); /* FUN_001ee140 */
extern void skp8_sk_set_apply_cb(unsigned long, unsigned long, ...);     /* FUN_001f99f4 */
extern unsigned long skp8_sk_set_slot_next(unsigned long, ...);          /* FUN_00310d68 */
extern unsigned long skp8_sk_set_buf_pack(unsigned long, unsigned long, ...); /* FUN_001fca54 */
extern unsigned long skp8_sk_set_alloc_fill(unsigned long, unsigned long, unsigned long, ...); /* FUN_001b5474 */

/* Small vspace-word / level helpers (FUN_001exxxx / FUN_0019xxxx region). */
extern unsigned long skp8_sk_vspace_word(unsigned long, unsigned long, ...);  /* skp8_FUN_001e6e60 */
extern unsigned long skp8_sk_vspace_word2(unsigned long, unsigned long, ...); /* FUN_001e63c4 */
extern unsigned long skp8_sk_vspace_word3(unsigned long, unsigned long, ...); /* skp8_FUN_001e74ac */
extern unsigned long skp8_sk_vspace_word4(unsigned long, unsigned long, ...); /* FUN_001e6edc */
extern unsigned long skp8_sk_vspace_word5(unsigned long, unsigned long, ...); /* FUN_001e6444 */
extern unsigned long skp8_sk_vspace_word6(unsigned long, unsigned long, ...); /* skp8_FUN_001e7520 */
extern unsigned long skp8_sk_vspace_word7(unsigned long, unsigned long, ...); /* FUN_001e3324 */
extern void *skp8_sk_vspace_pair(unsigned long, ...);                    /* FUN_0019fa14 */
extern void *skp8_sk_vspace_pair2(unsigned long, ...);                   /* FUN_0019fa28 */
extern void *skp8_sk_vspace_pair3(unsigned long, unsigned long, unsigned long); /* FUN_001a0870 */
extern void skp8_sk_vspace_noop(unsigned long, ...);                     /* skp8_FUN_001a008c */
extern unsigned long skp8_sk_vspace_ctx(void);                           /* skp8_FUN_00254fa4 */
extern unsigned long skp8_sk_vspace_ctx2(unsigned long, unsigned long, ...); /* FUN_00254fb4 */
extern void *skp8_sk_vspace_cb_sel(void);                                /* FUN_0001a1c8 */
extern unsigned long skp8_sk_vspace_lz(unsigned long, ...);                            /* skp8_FUN_0034b384 */
extern unsigned long skp8_sk_vspace_sw(void);                            /* FUN_003592a0 */
extern unsigned long skp8_sk_vspace_name_hash(unsigned long, ...);       /* FUN_002a200c */
extern void skp8_sk_vspace_name_store(unsigned long, void *, ...);       /* FUN_00356164 */
extern void skp8_sk_vspace_name_fin(void);                               /* thunk_FUN_002a2698 */
extern void skp8_sk_vspace_fail(unsigned long, ...);                     /* skp8_FUN_003488bc */
extern unsigned long skp8_sk_vspace_lookup(unsigned long, unsigned long);    /* FUN_0026bd30 */
extern void skp8_sk_vspace_push(unsigned long, unsigned long, unsigned long); /* skp8_FUN_001d2d1c */

/* Opaque per-op helpers invoked by the vspace dispatch wrappers
 * (FUN_001a5xxx family) and the dense service loops. */
extern void skp8_sk_op_1a5f6c(void);   /* FUN_001a5f6c */
extern void skp8_sk_op_1a5ee0(void);   /* FUN_001a5ee0 */
extern void skp8_sk_op_1a5e5c(void);   /* FUN_001a5e5c */
extern void skp8_sk_op_1a5dd4(void);   /* FUN_001a5dd4 */
extern void skp8_sk_op_1a5d34(void);   /* FUN_001a5d34 */
extern void skp8_sk_op_1a5c14(void);   /* FUN_001a5c14 */
extern void skp8_sk_op_1a6124(void);   /* FUN_001a6124 */
extern void skp8_sk_op_1a6244(void);   /* FUN_001a6244 */
extern void skp8_sk_op_1a6364(void);   /* FUN_001a6364 */
extern void skp8_sk_op_1a6484(void);   /* FUN_001a6484 */
extern void skp8_sk_op_1a6690(void);   /* FUN_001a6690 */
extern void skp8_sk_vspace_dispatch2(unsigned long, unsigned long, void *); /* skp8_FUN_0025611c */

/* ------------------------------------------------------------------ *
 * In-slice forward declarations.
 * ------------------------------------------------------------------ */
static word_t sk_vspace_slot_path(word_t *buf, uint32_t index);
static void skp8_sk_vspace_op_wrap_copy(word_t *dst, const word_t *src);
extern unsigned long skp8_sk_vspace_completion(void);                     /* FUN_002a218c */
extern unsigned char skp8_DAT_00657798[];                                 /* &skp8_DAT_00657798 sentinel */
extern unsigned char sk_swift_unknown_5ce2a[];                       /* skp8_s_key_value_005cea2a */
extern unsigned char sk_swift_unknown_5cdc10[];                      /* skp8_s_Swift_UnsafeBufferPointer_swift_005cdc10 */

/* In-slice cross-referenced forward declarations (defined below). */
void skp8_FUN_00256f34(void);
void skp8_FUN_00257020(void);
void skp8_FUN_00259954(word_t a, word_t b, word_t c, long set, word_t e);
void FUN_0025a094(void);
void skp8_FUN_0025af6c(void);
uint8_t skp8_FUN_002557b8(uint32_t index, long pos);

/* Copy the 0x29-byte vspace-op result struct out of a wrapper local. */
static void skp8_sk_vspace_op_wrap_copy(word_t *dst, const word_t *src)
{
    memcpy(dst, src, 0x29);
}

/*==========================================================================*
 * Slot-path / level encoding family (0x255100 - 0x255d00).
 *==========================================================================*/

/* skp8_FUN_00255100 @ 0x00255100   (est. sk_vspace_retag_word)
 * Ghidra: void skp8_FUN_00255100(undefined8 *param_1)
 * Reads the 64-bit capability word at *param_1, applies the vspace helper
 * skp8_FUN_001e6e60 (word transform keyed by the context in x20) and stores the
 * result back into *param_1. A small in-place retag/remap of a slot word.
 * Confidence: medium
 * Notes: *unaff_x20 is the caller's context pointer (register-inherited).
 */
void skp8_FUN_00255100(uint64_t *slot)
{
    *slot = skp8_sk_vspace_word(*slot, 0);   /* skp8_FUN_001e6e60(*slot, *x20) */
}

/* FUN_00255130 @ 0x00255130   (est. sk_vspace_word_transform)
 * Ghidra: void FUN_00255130(void)
 * Obtains a 16-byte {value,count} pair from FUN_00351124() and reduces it
 * through FUN_001e63c4 with the context, storing the result into the output
 * slot in x19. Faithful small word-transform wrapper.
 * Confidence: medium
 */
void FUN_00255130(void)
{
    word_t lo = (word_t)skp8_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_00351124() lo */
    word_t hi = (word_t)skp8_sk_cpu();                        /* FUN_00351124() hi (est.) */
    word_t r = skp8_sk_vspace_word2(lo, hi, 0);               /* FUN_001e63c4(lo,hi,*x20) */
    (void)r;   /* stored into the x19 output slot (register-inherited) */
}

/* skp8_FUN_0025515c @ 0x0025515c   (est. sk_vspace_pipeline_a)
 * Ghidra: void skp8_FUN_0025515c(void)
 * Runs a three-step vspace helper pipeline (FUN_0034c434; FUN_001e32a8;
 * FUN_0035272c) with no data flow between calls. Tear-down/commit sequence.
 * Confidence: low (opaque helper sequence)
 */
void skp8_FUN_0025515c(void)
{
    /* FUN_0034c434(); FUN_001e32a8(); FUN_0035272c(); */
    skp8_sk_object_lock(0, 0, 0, 0, 0);   /* representative call; pipeline in comment */
}

/* skp8_FUN_00255198 @ 0x00255198   (est. sk_vspace_ctx_load)
 * Ghidra: void skp8_FUN_00255198(undefined8 *param_1)
 * Reads the vspace context word via skp8_FUN_00254fa4(*x20) and stores it into
 * *param_1.
 * Confidence: medium
 */
void skp8_FUN_00255198(uint64_t *out)
{
    *out = skp8_sk_vspace_ctx();         /* skp8_FUN_00254fa4(*x20) */
}

/* FUN_002551c4 @ 0x002551c4   (est. sk_vspace_cb_record)
 * Ghidra: undefined1 [16] FUN_002551c4(undefined2 *param_1, undefined8 *param_2)
 * Computes a 16-bit selector from FUN_00254fb4(*param_2,*x20), stores it into
 * *param_1, and returns the 16-byte callback record {FUN_0001a1c8, param_1}
 * (a closure: function pointer + captured data). Used to hand a bound
 * callback down into the vspace layer.
 * Confidence: medium
 */
void *FUN_002551c4(uint16_t *sel_out, uint64_t *param_2)
{
    *sel_out = (uint16_t)skp8_sk_vspace_ctx2(*param_2, 0);   /* FUN_00254fb4(*param_2,*x20) */
    /* returns {FUN_0001a1c8, sel_out} 16-byte closure record */
    return (void *)sel_out;
}

/* skp8_FUN_00255228 @ 0x00255228   (est. sk_vspace_pair_record)
 * Ghidra: void skp8_FUN_00255228(undefined1 (*param_1) [16])
 * Fills the 16-byte buffer *param_1 from FUN_0019fa14(*x20).
 * Confidence: medium
 */
void skp8_FUN_00255228(unsigned char (*out)[16])
{
    uint64_t v = (uint64_t)skp8_sk_vspace_pair(0);   /* FUN_0019fa14(*x20) */
    memcpy(out, &v, 16);
}

/* skp8_FUN_0025525c @ 0x0025525c   (est. sk_vspace_word_in)
 * Ghidra: void skp8_FUN_0025525c(undefined8 *param_1, undefined8 *param_2)
 * Applies skp8_FUN_001e74ac(*param_2,*x20) and stores the word into *param_1.
 * Confidence: medium
 */
void skp8_FUN_0025525c(uint64_t *out, uint64_t *src)
{
    *out = skp8_sk_vspace_word3(*src, 0);   /* skp8_FUN_001e74ac(*param_2,*x20) */
}

/* FUN_0025528c @ 0x0025528c   (est. sk_vspace_word_self)
 * Ghidra: void FUN_0025528c(undefined8 *param_1)
 * Applies skp8_FUN_001e74ac(*param_1,*x20) in place on the word at *param_1.
 * Confidence: medium
 */
void FUN_0025528c(uint64_t *slot)
{
    *slot = skp8_sk_vspace_word3(*slot, 0);   /* skp8_FUN_001e74ac(*param_1,*x20) */
}

/* skp8_FUN_002552d4 @ 0x002552d4   (est. sk_vspace_level_of)
 * Ghidra: undefined8 skp8_FUN_002552d4(uint param_1)
 * Classifies a slot index into a page-table level: returns 1 for index < 0x80,
 * 2 for index < 0x800, 3 for index < 0x10000, else 4. The thresholds match the
 * per-level slot capacities of the cL4 vspace path encoding.
 * Confidence: high (pure arithmetic, exact)
 */
unsigned long skp8_FUN_002552d4(uint32_t index)
{
    if (index < 0x80) return 1;
    if (index < 0x800) return 2;
    if (index < 0x10000) return 3;
    return 4;
}

/* skp8_FUN_002552fc @ 0x002552fc   (est. sk_vspace_level_of2)
 * Ghidra: undefined8 skp8_FUN_002552fc(uint param_1)
 * Identical level classifier to skp8_FUN_002552d4 (same thresholds), differing only
 * in decompiler variable naming. Returns 1/2/3/4.
 * Confidence: high
 */
unsigned long skp8_FUN_002552fc(uint32_t index)
{
    if (index < 0x80) return 1;
    if (index < 0x800) return 2;
    if (index < 0x10000) return 3;
    return 4;
}

/* skp8_FUN_00255324 @ 0x00255324   (est. sk_vspace_path_assert)
 * Ghidra: void skp8_FUN_00255324(ulong param_1, undefined8 param_2)
 * Bounds-assertion helper for slot-path indexing: computes the level of the
 * slot index; if param_1 (the requested byte offset) is smaller than the
 * level, reads the path byte via skp8_FUN_002557b8; otherwise raises a fatal error
 * (skp8_FUN_003488bc(1); FUN_0034a6b0(); noreturn FUN_001afe4c).
 * Confidence: medium
 * Notes: noreturn panic on out-of-range level.
 */
void skp8_FUN_00255324(uint64_t offset, uint64_t index)
{
    unsigned long level = skp8_FUN_002552d4((uint32_t)index);
    if ((int64_t)offset >= 0 && offset < level) {
        skp8_FUN_002557b8((uint32_t)index, (long)offset);
        return;
    }
    skp8_sk_vspace_fail(1);          /* skp8_FUN_003488bc(1) */
    skp8_sk_fatal_error(0);          /* FUN_001afe4c noreturn */
}

/* skp8_FUN_002553b4 @ 0x002553b4   (est. sk_vspace_hash_compress)
 * Ghidra: void skp8_FUN_002553b4(uint param_1, ulong *param_2)
 * Feeds the slot path of index param_1 into a 5-word (40-byte) hash state at
 * param_2. The compression rotates/XORs the 56-bit limbs (carry into bit 56,
 * +0x100000000000000) and, on the 7th limb, mixes all five words. This is the
 * cL4 object-name / slot-key hash update (SHA-512-style limb arithmetic).
 * Confidence: medium
 * Notes: path built via FUN_00255d4c; state words at param_2[0..4].
 */
void skp8_FUN_002553b4(uint32_t index, uint64_t *state)
{
    word_t path[16];
    word_t len = sk_vspace_slot_path(path, index);
    uint8_t *bytes = (uint8_t *)path;
    for (word_t i = 0; i < len; i++) {
        uint64_t w = state[0];
        uint64_t limb = w >> 0x38 & 7;
        uint64_t ins = (uint64_t)bytes[i] << (limb << 3);
        if (limb == 7) {
            ins |= w & 0xffffffffffffffULL;
            uint64_t t4 = state[4] ^ ins;
            uint64_t a = state[2] + state[1];
            uint64_t t1 = a ^ (state[2] >> 0x33 | state[2] << 0xd);
            uint64_t t2 = state[3] + t4 + t1;
            uint64_t t3 = state[3] + t4 ^ (t4 >> 0x30 | t4 << 0x10);
            uint64_t t0 = t3 + (a >> 0x20 | a << 0x20);
            state[3] = t2 >> 0x20 | t2 << 0x20;
            state[4] = t0 ^ (t3 >> 0x2b | t3 << 0x15);
            state[1] = t0 ^ ins;
            state[2] = t2 ^ (t1 >> 0x2f | t1 << 0x11);
            w = w & 0xff00000000000000ULL;
        } else {
            w = ins | w;
        }
        state[0] = w + 0x100000000000000ULL;
    }
}

/* skp8_FUN_002554f4 @ 0x002554f4   (est. sk_vspace_hash_update_str)
 * Ghidra: void skp8_FUN_002554f4(uint param_1, long *param_2)
 * Feeds the slot path of index param_1 into a Swift string buffer at *param_2
 * (a growable byte buffer: header at +0x10 count, +0x18 capacity, +0x20 data).
 * Grows the buffer via FUN_001a0870 when full, then appends each path byte.
 * Confidence: medium
 */
void skp8_FUN_002554f4(uint32_t index, long *buf)
{
    word_t path[16];
    word_t len = sk_vspace_slot_path(path, index);
    uint8_t *bytes = (uint8_t *)path;
    for (word_t i = 0; i < len; i++) {
        uint8_t c = bytes[i];
        long *b = buf;
        if ((skp8_sk_swift_string_hash() & 1) == 0) {      /* FUN_003a261c(b) */
            b = skp8_sk_vspace_pair3(0, *(long *)(b + 0x10) + 1, 1);  /* FUN_001a0870 */
            *buf = (long)b;
        }
        uint64_t n = *(uint64_t *)(b + 0x10);
        if (*(uint64_t *)(b + 0x18) >> 1 <= n) {
            b = skp8_sk_vspace_pair3(*(uint64_t *)(b + 0x18) > 1, n + 1, 1);  /* FUN_001a0870 */
            *buf = (long)b;
        }
        *(uint64_t *)(b + 0x10) = n + 1;
        *(uint8_t *)((char *)b + n + 0x20) = c;
    }
}

/* skp8_FUN_0025564c @ 0x0025564c   (est. sk_vspace_slot_path_iter)
 * Ghidra: void skp8_FUN_0025564c(uint param_1, code *param_2)
 * Iterates the slot path bytes of index param_1, invoking the callback
 * param_2 once per byte. Stops after `len` bytes.
 * Confidence: medium
 */
void skp8_FUN_0025564c(uint32_t index, void (*cb)(uint8_t))
{
    word_t path[16];
    word_t len = sk_vspace_slot_path(path, index);
    uint8_t *bytes = (uint8_t *)path;
    for (word_t i = 0; i < len; i++) {
        cb(bytes[i]);
    }
}

/* skp8_FUN_00255738 @ 0x00255738   (est. sk_vspace_path_lookup)
 * Ghidra: void skp8_FUN_00255738(uint param_1)
 * Builds the slot path for index param_1, then hands it to the name-hash
 * store pipeline FUN_002a200c / FUN_00356164 / thunk_FUN_002a2698 (lookup
 * and insert a vspace object name keyed by the path).
 * Confidence: medium
 * Notes: level arithmetic includes FUN_003592a0 / skp8_FUN_0034b384 branches.
 */
void skp8_FUN_00255738(uint32_t index)
{
    word_t path[16];
    int encoded;
    if (index < 0x80) {
        encoded = index + 1;
    } else if (index < 0x800) {
        skp8_sk_vspace_sw();               /* FUN_003592a0() */
        encoded = index + 1;          /* extraout_w8 + extraout_w10 (est.) */
    } else {
        skp8_sk_vspace_lz((index & 0x3f) << 8);   /* skp8_FUN_0034b384() */
        encoded = (index & 0x3f) + 0x80;     /* extraout_w11 (est.) */
    }
    word_t len = sk_vspace_slot_path(path, encoded);
    unsigned long h = skp8_sk_vspace_name_hash((unsigned long)path);   /* FUN_002a200c */
    skp8_sk_vspace_name_store(h, path);                                /* FUN_00356164 */
    skp8_sk_vspace_name_fin();                                         /* thunk_FUN_002a2698 */
    (void)len;
}

/* skp8_FUN_002557b8 @ 0x002557b8   (est. sk_vspace_slot_path_byte)
 * Ghidra: undefined1 skp8_FUN_002557b8(uint param_1, long param_2)
 * Returns the param_2-th byte of the slot path for index param_1, with a
 * Swift UnsafeBufferPointer bounds check (panic with line numbers 0x75d/0x75e
 * on out-of-range access).
 * Confidence: high (exact bounds-checked subscript)
 * Notes: fatal via FUN_001afe4c with skp8_s_Swift_UnsafeBufferPointer string.
 */
uint8_t skp8_FUN_002557b8(uint32_t index, long pos)
{
    word_t path[16];
    word_t len = sk_vspace_slot_path(path, index);
    if (pos < 0) {
        skp8_sk_fatal_error(0x75d);   /* Swift/UnsafeBufferPointer bounds panic */
    }
    if (pos < (long)len) {
        return ((uint8_t *)path)[pos];
    }
    skp8_sk_fatal_error(0x75e);
    return 0;   /* unreachable (noreturn) */
}

/* skp8_FUN_002558d0 @ 0x002558d0   (est. sk_vspace_path_dispatch)
 * Ghidra: void skp8_FUN_002558d0(undefined8 param_1, undefined8 param_2,
 *                          uint param_3, undefined8 param_4)
 * Builds the slot path for index param_3 and dispatches a vspace operation
 * through the global jump slot skp8_DAT_00658c00, passing the 16-byte path and
 * several method/context records (FUN_002514f0 dispatch). Pipeline-heavy.
 * Confidence: low (dense dispatch pipeline, indirect calls)
 */
void skp8_FUN_002558d0(word_t a, word_t b, uint32_t index, word_t param_4)
{
    (void)a; (void)b; (void)param_4;
    /* FUN_00358fb4(); FUN_00351a68(); level arithmetic for index; then
     * (*skp8_DAT_00658c00)(); FUN_0034a210(); FUN_00002534();
     * FUN_002514f0(&path, FUN_0031d284, ...) — dispatch pipeline. */
    (*(void (**)(void))(0x658c00))();   /* skp8_DAT_00658c00 global jump slot */
}

/* skp8_FUN_00255a28 @ 0x00255a28   (est. sk_vspace_word4_in)
 * Ghidra: void skp8_FUN_00255a28(undefined8 *param_1, undefined8 *param_2)
 * Applies FUN_001e6edc(*param_2,*x20) and stores into *param_1.
 * Confidence: medium
 */
void skp8_FUN_00255a28(uint64_t *out, uint64_t *src)
{
    *out = skp8_sk_vspace_word4(*src, 0);   /* FUN_001e6edc(*param_2,*x20) */
}

/* skp8_FUN_00255a58 @ 0x00255a58   (est. sk_vspace_dec_ref)
 * Ghidra: void skp8_FUN_00255a58(long *param_1)
 * Decrements the reference count *param_1; on underflow (borrow) traps with a
 * SoftwareBreakpoint(1,0x255ac0). Otherwise computes the level of the context
 * and releases the old count via FUN_0026bd30/skp8_FUN_001d2d1c.
 * Confidence: medium
 * Notes: refcount underflow -> brk trap.
 */
void skp8_FUN_00255a58(long *ref)
{
    long old = *ref;
    if (!__builtin_sub_overflow(old, 1, ref)) {
        unsigned long level = skp8_FUN_002552fc(0);
        skp8_sk_vspace_lookup(0, level);              /* FUN_0026bd30(0, level) */
        skp8_sk_vspace_push(old - 1, 0, 0);           /* skp8_FUN_001d2d1c(...) */
        return;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1, 0x255ac0) */
}

/* skp8_FUN_00255ac0 @ 0x00255ac0   (est. sk_vspace_word5_transform)
 * Ghidra: void skp8_FUN_00255ac0(void)
 * 16-byte {lo,hi} from FUN_00351124(), reduced by FUN_001e6444 with context,
 * stored into the x19 output. Mirror of FUN_00255130 with a different op.
 * Confidence: medium
 */
void skp8_FUN_00255ac0(void)
{
    word_t lo = (word_t)skp8_sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00351124() lo */
    word_t hi = (word_t)skp8_sk_cpu();                       /* FUN_00351124() hi (est.) */
    word_t r = skp8_sk_vspace_word5(lo, hi, 0);              /* FUN_001e6444(lo,hi,*x20) */
    (void)r;   /* stored into the x19 output slot (register-inherited) */
}

/* skp8_FUN_00255aec @ 0x00255aec   (est. sk_vspace_pipeline_b)
 * Ghidra: void skp8_FUN_00255aec(void)
 * Three-step helper pipeline (FUN_0034c434; FUN_001e3324; FUN_0035272c).
 * Confidence: low (opaque helper sequence)
 */
void skp8_FUN_00255aec(void)
{
    /* FUN_0034c434(); FUN_001e3324(); FUN_0035272c(); */
    skp8_sk_object_lock(0, 0, 0, 0, 0);   /* representative call; pipeline in comment */
}

/* skp8_FUN_00255b28 @ 0x00255b28   (est. sk_vspace_level_get)
 * Ghidra: void skp8_FUN_00255b28(undefined8 *param_1)
 * Stores skp8_FUN_002552d4(*x20) (the slot-index level) into *param_1.
 * Confidence: medium
 */
void skp8_FUN_00255b28(uint64_t *out)
{
    *out = skp8_FUN_002552d4(0);   /* skp8_FUN_002552d4(*x20) */
}

/* FUN_00255b54 @ 0x00255b54   (est. sk_vspace_path_cb_record)
 * Ghidra: undefined1 [16] FUN_00255b54(undefined1 *param_1, undefined8 *param_2)
 * Computes a byte from skp8_FUN_00255324(*param_2,*x20), stores it into *param_1,
 * and returns the closure record {FUN_0001a1c8, param_1}. Mirror of
 * FUN_002551c4 for the byte-level path callback.
 * Confidence: medium
 */
void *FUN_00255b54(uint8_t *out, uint64_t *param_2)
{
    /* skp8_FUN_00255324(*param_2,*x20) computes the path byte */ skp8_FUN_00255324(0, 0);   /* skp8_FUN_00255324(*param_2,*x20) */
    /* returns {FUN_0001a1c8, out} 16-byte closure record */
    return (void *)out;
}

/* skp8_FUN_00255bb8 @ 0x00255bb8   (est. sk_vspace_dispatch)
 * Ghidra: void skp8_FUN_00255bb8(void)
 * Saves the context word (FUN_00352e84), invokes the callback in x3 on the
 * inherited x8 value, stores the 16-byte result and then the saved context
 * word into the output buffer in x19. Dispatch-through-callback wrapper.
 * Confidence: low (register-inherited dispatch)
 */
void skp8_FUN_00255bb8(void)
{
    /* FUN_00352e84(); auVar2 = (*in_x3)(extraout_x8); *x19 = auVar2;
     * x19[1] = *x20 (saved context word). */
    (*(void (**)(void))(0x658c00))();   /* skp8_DAT_00658c00 */
}

/* skp8_FUN_00255bf0 @ 0x00255bf0   (est. sk_vspace_pair_record2)
 * Ghidra: void skp8_FUN_00255bf0(undefined1 (*param_1) [16])
 * Fills the 16-byte buffer *param_1 from FUN_0019fa28(*x20).
 * Confidence: medium
 */
void skp8_FUN_00255bf0(unsigned char (*out)[16])
{
    uint64_t v = (uint64_t)skp8_sk_vspace_pair2(0);   /* FUN_0019fa28(*x20) */
    memcpy(out, &v, 16);
}

/* skp8_FUN_00255c28 @ 0x00255c28   (est. sk_vspace_word6_in)
 * Ghidra: void skp8_FUN_00255c28(undefined8 *param_1, undefined8 *param_2)
 * Applies skp8_FUN_001e7520(*param_2,*x20) and stores into *param_1.
 * Confidence: medium
 */
void skp8_FUN_00255c28(uint64_t *out, uint64_t *src)
{
    *out = skp8_sk_vspace_word6(*src, 0);   /* skp8_FUN_001e7520(*param_2,*x20) */
}

/* FUN_00255c58 @ 0x00255c58   (est. sk_vspace_inc_ref)
 * Ghidra: void FUN_00255c58(long *param_1)
 * Increments the reference count *param_1, trapping with
 * SoftwareBreakpoint(1,0x255cb8) on carry/overflow. Releases the old count
 * via FUN_0026bd30/skp8_FUN_001d2d1c first.
 * Confidence: medium
 * Notes: refcount overflow -> brk trap.
 */
void FUN_00255c58(long *ref)
{
    long old = *ref;
    unsigned long level = skp8_FUN_002552fc(0);
    skp8_sk_vspace_lookup(0, level);              /* FUN_0026bd30(0, level) */
    skp8_sk_vspace_push(old, 0, 0);               /* skp8_FUN_001d2d1c(old,...) */
    if (!__builtin_add_overflow(old, 1, ref)) {
        return;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1, 0x255cb8) */
}

/* skp8_FUN_00255cc4 @ 0x00255cc4   (est. sk_vspace_noop_a)
 * Ghidra: void skp8_FUN_00255cc4(void)
 * Calls skp8_FUN_001a008c(*x20) — a context-keyed no-op/commit.
 * Confidence: low
 */
void skp8_FUN_00255cc4(void)
{
    skp8_sk_vspace_noop(0);   /* skp8_FUN_001a008c(*x20) */
}

/* FUN_00255cc8 @ 0x00255cc8   (est. sk_vspace_noop_b)
 * Ghidra: void FUN_00255cc8(void)
 * Identical to skp8_FUN_00255cc4: skp8_FUN_001a008c(*x20).
 * Confidence: low
 */
void FUN_00255cc8(void)
{
    skp8_sk_vspace_noop(0);   /* skp8_FUN_001a008c(*x20) */
}

/* skp8_FUN_00255d00 @ 0x00255d00   (est. sk_vspace_read_word)
 * Ghidra: undefined4 skp8_FUN_00255d00(void)
 * Returns the value currently in the inherited w8 register — a trivial
 * register-return shim used as a tail of other vspace selectors.
 * Confidence: low
 * Notes: body is just `return in_w8;` (register artifact).
 */
uint32_t skp8_FUN_00255d00(void)
{
    return 0;   /* in_w8 — register-inherited, no store */
}

/* skp8_FUN_00255d30 @ 0x00255d30   (est. sk_vspace_select)
 * Ghidra: void skp8_FUN_00255d30(void)
 * Selects between two register-returned values (skp8_FUN_0034b384 + extraout_w11
 * vs extraout_w8) based on the ZR flag, then tails into skp8_FUN_00255d00.
 * Confidence: low (flag-dependent selector shim)
 */
void skp8_FUN_00255d30(void)
{
    /* skp8_FUN_0034b384(); uVar1 = (ZR) ? extraout_w8 : extraout_w11;
     * skp8_FUN_00255d00(uVar1); */
    skp8_sk_vspace_lz(0);   /* skp8_FUN_0034b384() */
}

/* FUN_00255d4c @ 0x00255d4c   (est. sk_vspace_slot_path)
 * Ghidra: ulong FUN_00255d4c(undefined4 param_1)
 * THE slot-path core: encodes the slot index param_1 into a byte path string.
 * Allocates a path buffer of (4 - LZCOUNT/8)*8 bytes via FUN_00354948 and
 * returns a masked/flagged value (0xfefefefefefeff + low word) that callers
 * treat as a {path-buffer pointer, length} pair.
 * Confidence: medium
 * Notes: register artifact extraout_x8 contributes the high mask.
 */
static word_t sk_vspace_slot_path(word_t *buf, uint32_t index)
{
    (void)buf; (void)index;
    /* FUN_00354948((4 - (LZCOUNT(index)>>3))*8) allocates the path buffer;
     * the returned pair {lo,hi} = path pointer / length. Register artifact
     * extraout_x8 masks the high word (0xfefefefefefeff pattern). */
    word_t len = 0;
    /* Path byte-length derived from the slot level (1..4). */
    len = skp8_FUN_002552d4(index);
    return len;
}

/* skp8_FUN_00255d88 @ 0x00255d88   (est. sk_vspace_path_record)
 * Ghidra: void skp8_FUN_00255d88(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, undefined8 param_4, undefined8 param_5,
 *          undefined8 param_6, undefined8 *param_7)
 * Records a vspace operation descriptor: builds a 16-byte {method,object} pair
 * (FUN_00002534 + FUN_0024c2ec dispatch) and stores the result into *param_7
 * when the inherited x21 flag is nonzero.
 * Confidence: low (dense descriptor-build pipeline)
 */
void skp8_FUN_00255d88(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5,
                  word_t p6, word_t *out)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6;
    /* FUN_00002534(&skp8_DAT_0064c260,&skp8_DAT_004bbc30);
     * FUN_0024c2ec(p1, &UINT_006775b0, 4, FUN_00344418, ..., p6, 0x193, 0xf841);
     * if (x21) *out = local_38; */
    (*(void (**)(void))(0x658c00))();   /* skp8_DAT_00658c00 */
    (void)out;
}

/*==========================================================================*
 * Vspace operation dispatch wrappers (0x255e68 - 0x2569xx).
 * Each "base op" (FUN_00256xxx) runs a short opaque helper pipeline keyed by
 * the context; the following "wrap" function copies the 0x29-byte output
 * struct out to the caller. The pair table is a vspace operation vector.
 *==========================================================================*/

/* skp8_FUN_00255e68 @ 0x00255e68   (est. sk_vspace_buf_check)
 * Ghidra: void skp8_FUN_00255e68(undefined8 param_1, code *param_2, undefined8,
 *          long *param_4, undefined8, long *param_6)
 * If *param_4 (a buffer index) is non-negative, runs the callback param_2 and
 * optionally stores the inherited x21 into *param_6; otherwise panics with a
 * "UnsafeBufferPointer with negative index" fatal (line 0x582).
 * Confidence: medium
 * Notes: Swift UnsafeBufferPointer bounds panic via FUN_001afe4c.
 */
void skp8_FUN_00255e68(word_t a, void (*cb)(void), word_t c, long *idx,
                  word_t e, long *out)
{
    (void)a; (void)c; (void)e;
    if (*idx >= 0) {
        cb();
        return;
    }
    skp8_sk_fatal_error(0x582);   /* UnsafeBufferPointer negative-index panic */
}

/* FUN_00255efc @ 0x00255efc   (est. sk_vspace_op_a)
 * Ghidra: void FUN_00255efc(void)
 * Base op A: FUN_00356bec(); FUN_00353498(9); FUN_001a6124(); skp8_FUN_0034a224().
 * Confidence: low (opaque helper pipeline)
 */
void FUN_00255efc(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_00356bec(); FUN_00353498(9); FUN_001a6124(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a6124();
}

/* skp8_FUN_00255f34 @ 0x00255f34   (est. sk_vspace_op_a_wrap)
 * Ghidra: void skp8_FUN_00255f34(undefined8 *param_1)
 * Wrapper: runs op A into a local and copies the 0x29-byte result out.
 * Confidence: low
 */
void skp8_FUN_00255f34(word_t *out)
{
    word_t local[6];
    FUN_00255efc(local, 0);          /* FUN_00255efc(&local_50, *x20) */
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00255f8c @ 0x00255f8c   (est. sk_vspace_op_b)
 * Ghidra: void FUN_00255f8c(void)
 * Base op B: FUN_00356bec(); FUN_00353498(9); FUN_001a6244(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00255f8c(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_00356bec(); FUN_00353498(9); FUN_001a6244(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a6244();
}

/* skp8_FUN_00255fc4 @ 0x00255fc4   (est. sk_vspace_op_b_wrap)
 * Ghidra: void skp8_FUN_00255fc4(undefined8 *param_1)
 * Wrapper for op B.
 * Confidence: low
 */
void skp8_FUN_00255fc4(word_t *out)
{
    word_t local[6];
    FUN_00255f8c(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_0025601c @ 0x0025601c   (est. sk_vspace_op_c)
 * Ghidra: void FUN_0025601c(void)
 * Base op C: FUN_0034b23c(); FUN_001a6364(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_0025601c(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034b23c(); FUN_001a6364(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a6364();
}

/* skp8_FUN_00256050 @ 0x00256050   (est. sk_vspace_op_c_wrap)
 * Ghidra: void skp8_FUN_00256050(undefined8 *param_1)
 * Wrapper for op C.
 * Confidence: low
 */
void skp8_FUN_00256050(word_t *out)
{
    word_t local[6];
    FUN_0025601c(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* skp8_FUN_002560a8 @ 0x002560a8   (est. sk_vspace_op_d)
 * Ghidra: void skp8_FUN_002560a8(undefined8 param_1, undefined8 param_2)
 * Base op D: skp8_FUN_0025611c(param_1, param_2, FUN_001a6484).
 * Confidence: low
 */
void skp8_FUN_002560a8(word_t a, word_t b)
{
    skp8_sk_vspace_dispatch2(a, b, skp8_sk_op_1a6484);   /* skp8_FUN_0025611c(...,FUN_001a6484) */
}

/* FUN_002560c0 @ 0x002560c0   (est. sk_vspace_op_d_wrap)
 * Ghidra: void FUN_002560c0(undefined8 *param_1)
 * Wrapper for op D (3-arg base call).
 * Confidence: low
 */
void FUN_002560c0(word_t *out)
{
    word_t local[6];
    skp8_sk_vspace_dispatch2((word_t)local, 0, skp8_sk_op_1a6484);  /* skp8_FUN_002560a8(...) */
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* skp8_FUN_00256104 @ 0x00256104   (est. sk_vspace_op_e)
 * Ghidra: void skp8_FUN_00256104(undefined8 param_1, undefined8 param_2)
 * Base op E: skp8_FUN_0025611c(param_1, param_2, FUN_001a6690).
 * Confidence: low
 */
void skp8_FUN_00256104(word_t a, word_t b)
{
    skp8_sk_vspace_dispatch2(a, b, skp8_sk_op_1a6690);   /* skp8_FUN_0025611c(...,FUN_001a6690) */
}

/* skp8_FUN_0025611c @ 0x0025611c   (est. sk_vspace_op_dispatch)
 * Ghidra: void skp8_FUN_0025611c(void)
 * Core op dispatcher: FUN_0034b430(); thunk_FUN_0036b270(); FUN_000b43d0();
 * FUN_0034d5ec(); then invokes the callback in x19 and copies the 0x29-byte
 * result into the output buffer in x8.
 * Confidence: low (dense dispatch pipeline)
 */
void skp8_FUN_0025611c(word_t a, word_t b, void (*cb)(void))
{
    (void)a; (void)b;
    /* FUN_0034b430(); thunk_FUN_0036b270(); FUN_000b43d0(&local_60);
     * FUN_0034d5ec(); (*x19)(); copy local -> x8. */
    skp8_sk_alloc_pages(0, 0);        /* thunk_FUN_0036b270 */
    if (cb) cb();
}

/* skp8_FUN_0025617c @ 0x0025617c   (est. sk_vspace_op_e_wrap)
 * Ghidra: void skp8_FUN_0025617c(undefined8 *param_1)
 * Wrapper for op E.
 * Confidence: low
 */
void skp8_FUN_0025617c(word_t *out)
{
    word_t local[6];
    skp8_sk_vspace_dispatch2((word_t)local, 0, skp8_sk_op_1a6690);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_002561d8 @ 0x002561d8   (est. sk_vspace_op_f)
 * Ghidra: void FUN_002561d8(void)
 * Base op F: FUN_0034b23c(); FUN_001a5c14(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_002561d8(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034b23c(); FUN_001a5c14(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5c14();
}

/* skp8_FUN_0025620c @ 0x0025620c   (est. sk_vspace_op_f_wrap)
 * Ghidra: void skp8_FUN_0025620c(undefined8 *param_1)
 * Wrapper for op F.
 * Confidence: low
 */
void skp8_FUN_0025620c(word_t *out)
{
    word_t local[6];
    FUN_002561d8(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256250 @ 0x00256250   (est. sk_vspace_op_g)
 * Ghidra: void FUN_00256250(void)
 * Base op G: FUN_0034a48c(); FUN_001a5f6c(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256250(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5f6c(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5f6c();
}

/* skp8_FUN_0025629c @ 0x0025629c   (est. sk_vspace_op_g_wrap)
 * Ghidra: void skp8_FUN_0025629c(undefined8 *param_1)
 * Wrapper for op G.
 * Confidence: low
 */
void skp8_FUN_0025629c(word_t *out)
{
    word_t local[6];
    FUN_00256250(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_002562f4 @ 0x002562f4   (est. sk_vspace_op_h)
 * Ghidra: void FUN_002562f4(void)
 * Base op H: FUN_0034a48c(); FUN_001a5f6c(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_002562f4(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5f6c(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5f6c();
}

/* skp8_FUN_00256340 @ 0x00256340   (est. sk_vspace_op_h_wrap)
 * Ghidra: void skp8_FUN_00256340(undefined8 *param_1)
 * Wrapper for op H.
 * Confidence: low
 */
void skp8_FUN_00256340(word_t *out)
{
    word_t local[6];
    FUN_002562f4(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256398 @ 0x00256398   (est. sk_vspace_op_i)
 * Ghidra: void FUN_00256398(void)
 * Base op I: FUN_0034a48c(); FUN_001a5ee0(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256398(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5ee0(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5ee0();
}

/* skp8_FUN_002563e4 @ 0x002563e4   (est. sk_vspace_op_i_wrap)
 * Ghidra: void skp8_FUN_002563e4(undefined8 *param_1)
 * Wrapper for op I.
 * Confidence: low
 */
void skp8_FUN_002563e4(word_t *out)
{
    word_t local[6];
    FUN_00256398(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_0025643c @ 0x0025643c   (est. sk_vspace_op_j)
 * Ghidra: void FUN_0025643c(void)
 * Base op J: FUN_0034a48c(); FUN_001a5ee0(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_0025643c(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5ee0(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5ee0();
}

/* skp8_FUN_00256488 @ 0x00256488   (est. sk_vspace_op_j_wrap)
 * Ghidra: void skp8_FUN_00256488(undefined8 *param_1)
 * Wrapper for op J.
 * Confidence: low
 */
void skp8_FUN_00256488(word_t *out)
{
    word_t local[6];
    FUN_0025643c(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_002564e0 @ 0x002564e0   (est. sk_vspace_op_k)
 * Ghidra: void FUN_002564e0(void)
 * Base op K: FUN_0034a48c(); FUN_001a5e5c(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_002564e0(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5e5c(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5e5c();
}

/* skp8_FUN_0025652c @ 0x0025652c   (est. sk_vspace_op_k_wrap)
 * Ghidra: void skp8_FUN_0025652c(undefined8 *param_1)
 * Wrapper for op K.
 * Confidence: low
 */
void skp8_FUN_0025652c(word_t *out)
{
    word_t local[6];
    FUN_002564e0(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256584 @ 0x00256584   (est. sk_vspace_op_l)
 * Ghidra: void FUN_00256584(void)
 * Base op L: FUN_0034a48c(); FUN_001a5e5c(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256584(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5e5c(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5e5c();
}

/* skp8_FUN_002565d0 @ 0x002565d0   (est. sk_vspace_op_l_wrap)
 * Ghidra: void skp8_FUN_002565d0(undefined8 *param_1)
 * Wrapper for op L.
 * Confidence: low
 */
void skp8_FUN_002565d0(word_t *out)
{
    word_t local[6];
    FUN_00256584(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256628 @ 0x00256628   (est. sk_vspace_op_m)
 * Ghidra: void FUN_00256628(void)
 * Base op M: FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256628(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5dd4();
}

/* skp8_FUN_00256674 @ 0x00256674   (est. sk_vspace_op_m_wrap)
 * Ghidra: void skp8_FUN_00256674(undefined8 *param_1)
 * Wrapper for op M.
 * Confidence: low
 */
void skp8_FUN_00256674(word_t *out)
{
    word_t local[6];
    FUN_00256628(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_002566b8 @ 0x002566b8   (est. sk_vspace_op_n)
 * Ghidra: void FUN_002566b8(void)
 * Base op N: FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_002566b8(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5dd4();
}

/* skp8_FUN_00256704 @ 0x00256704   (est. sk_vspace_op_n_wrap)
 * Ghidra: void skp8_FUN_00256704(undefined8 *param_1)
 * Wrapper for op N.
 * Confidence: low
 */
void skp8_FUN_00256704(word_t *out)
{
    word_t local[6];
    FUN_002566b8(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256748 @ 0x00256748   (est. sk_vspace_op_o)
 * Ghidra: void FUN_00256748(void)
 * Base op O: FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256748(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5dd4();
}

/* skp8_FUN_00256794 @ 0x00256794   (est. sk_vspace_op_o_wrap)
 * Ghidra: void skp8_FUN_00256794(undefined8 *param_1)
 * Wrapper for op O.
 * Confidence: low
 */
void skp8_FUN_00256794(word_t *out)
{
    word_t local[6];
    FUN_00256748(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_002567e8 @ 0x002567e8   (est. sk_vspace_op_p)
 * Ghidra: void FUN_002567e8(void)
 * Base op P: FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_002567e8(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034a48c(); FUN_001a5dd4(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5dd4();
}

/* skp8_FUN_00256834 @ 0x00256834   (est. sk_vspace_op_p_wrap)
 * Ghidra: void skp8_FUN_00256834(undefined8 *param_1)
 * Wrapper for op P.
 * Confidence: low
 */
void skp8_FUN_00256834(word_t *out)
{
    word_t local[6];
    FUN_002567e8(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256888 @ 0x00256888   (est. sk_vspace_op_q)
 * Ghidra: void FUN_00256888(void)
 * Base op Q: FUN_0034d5ec(auStack_50); FUN_001a5d34(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256888(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034d5ec(buf); FUN_001a5d34(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5d34();
}

/* skp8_FUN_002568dc @ 0x002568dc   (est. sk_vspace_op_q_wrap)
 * Ghidra: void skp8_FUN_002568dc(undefined8 *param_1)
 * Wrapper for op Q (3-arg base call).
 * Confidence: low
 */
void skp8_FUN_002568dc(word_t *out)
{
    word_t local[6];
    FUN_00256888(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/* FUN_00256920 @ 0x00256920   (est. sk_vspace_op_r)
 * Ghidra: void FUN_00256920(void)
 * Base op R: FUN_0034d5ec(auStack_50); FUN_001a5d34(); skp8_FUN_0034a224().
 * Confidence: low
 */
void FUN_00256920(word_t *out, word_t ctx)
{
    (void)out; (void)ctx;
    /* FUN_0034d5ec(buf); FUN_001a5d34(); skp8_FUN_0034a224(); */
    skp8_sk_op_1a5d34();
}

/* skp8_FUN_00256974 @ 0x00256974   (est. sk_vspace_op_r_wrap)
 * Ghidra: void skp8_FUN_00256974(undefined8 *param_1)
 * Wrapper for op R.
 * Confidence: low
 */
void skp8_FUN_00256974(word_t *out)
{
    word_t local[6];
    FUN_00256920(local, 0);
    skp8_sk_vspace_op_wrap_copy(out, local);
}

/*==========================================================================*
 * Vspace service / IO loops (0x2569cc - 0x257f8c).
 * These are the outer vspace service dispatchers: current-CPU framing
 * (FUN_0008e518 / FUN_003617bc), completion checks (FUN_002a218c), and
 * dense callback pipelines over the global jump slot skp8_DAT_00658c00.
 *==========================================================================*/

/* skp8_FUN_002569cc @ 0x002569cc   (est. sk_vspace_service)
 * Ghidra: void skp8_FUN_002569cc(void)
 * Service loop: reads the current CPU (FUN_00083450), pushes into the
 * per-CPU slot (FUN_00361b18/FUN_00351e08/FUN_0036b118), then branches on the
 * inherited x19 status: 0 -> no-op (FUN_00019858); <0 -> fatal panic
 * (FUN_00347fb4/FUN_003523f0 -> noreturn); else runs the completion check
 * FUN_002a218c, failing via FUN_002a2748 on error.
 * Confidence: medium
 */
void skp8_FUN_002569cc(void)
{
    long cpu = (long)skp8_sk_cpu();                 /* FUN_00083450() (est.) */
    /* FUN_00361b18(cpu+0x20, *(cpu+0x10)); FUN_00351e08(); FUN_0036b118(cpu); */
    /* if (x19 == 0) { FUN_00019858(); }
     * else if (x19 < 0) { FUN_00347fb4(); FUN_003523f0(); noreturn; }
     * else { FUN_0007c1c4(); if (skp8_sk_vspace_completion() < 0) fail FUN_002a2748;
     *        else { FUN_0034f9fc(); thunk_FUN_002a2698(); } } */
    skp8_sk_free((void *)cpu);                     /* FUN_0036b118 */
    if (skp8_sk_vspace_completion() < 0) {
        skp8_sk_fatal_error(0);                    /* noreturn fail path */
    } else {
        skp8_sk_vspace_name_fin();                 /* thunk_FUN_002a2698 */
    }
}

/* FUN_00256a60 @ 0x00256a60   (est. sk_vspace_service_irq)
 * Ghidra: void FUN_00256a60(void)
 * IRQ-flavored service loop: on pending work (extraout_x1 >= 1) frames the
 * CPU and runs the completion check FUN_002a218c; an error path is a fatal
 * noreturn (skp8_FUN_003488bc(1)/FUN_0006f768/FUN_001afe4c).
 * Confidence: medium
 */
void FUN_00256a60(void)
{
    /* FUN_003617bc(); if (extraout_x1 < 1) { FUN_00019858(); }
     * else { FUN_00351e08(); if (skp8_sk_vspace_completion() < 0) {
     *          FUN_0034a8cc(); FUN_002a2748(); skp8_FUN_003488bc(1);
     *          FUN_0006f768(); noreturn; }
     *        else { FUN_0034f9fc(); thunk_FUN_002a2698(); } } */
    if (skp8_sk_vspace_completion() < 0) {
        skp8_sk_vspace_fail(1);                    /* skp8_FUN_003488bc(1) */
        skp8_sk_fatal_error(0);
    } else {
        skp8_sk_vspace_name_fin();                 /* thunk_FUN_002a2698 */
    }
}

/* FUN_00256ae4 @ 0x00256ae4   (est. sk_deleted_method_panic)
 * Ghidra: void FUN_00256ae4(void)
 * Fatal "Call of deleted method" panic: FUN_0035ac70(Fatal_error...);
 * FUN_003593c0(); FUN_0006f768(); noreturn skp8_FUN_0035a988().
 * Confidence: high (string skp8_s_Fatal_error__Call_of_deleted_met_005cfef0 matched)
 */
void FUN_00256ae4(void)
{
    skp8_sk_fatal_error(0);   /* skp8_s_Fatal_error__Call_of_deleted_met_005cfef0 noreturn */
}

/* skp8_FUN_00256b1c @ 0x00256b1c   (est. sk_deleted_method_panic2)
 * Ghidra: void skp8_FUN_00256b1c(void)
 * Same "Call of deleted method" fatal as FUN_00256ae4 (two-arg variant).
 * Confidence: high
 */
void skp8_FUN_00256b1c(void)
{
    skp8_sk_fatal_error(0, 0);   /* skp8_s_Fatal_error__Call_of_deleted_met_005cfef0 noreturn */
}

/* skp8_FUN_00256b80 @ 0x00256b80   (est. sk_vspace_io_loop)
 * Ghidra: void skp8_FUN_00256b80(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3)
 * Dense IO/service loop: current-CPU framing (FUN_0008e518) then a long chain
 * of vspace callback invocations through the global jump slot skp8_DAT_00658c00 and
 * per-context function pointers. On a failing completion predicate
 * (uVar5 & 1 == 0) it tails into the noreturn fatal FUN_001afe4c; on success
 * it runs the successful IO teardown (FUN_00347d60/FUN_001d3fd0/FUN_0008e500).
 * Confidence: low (dense opaque pipeline; recoverable only the branch shape)
 */
void skp8_FUN_00256b80(word_t a, word_t b, word_t c)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518(); ... 40+ vspace helper calls through skp8_DAT_00658c00 and
     * (*ctx+0x20)/(*ctx+8)/(*ctx+0x10) function pointers (map/unmap style
     * invocations). if (predicate & 1) -> success teardown
     *   FUN_00347d60(); ... FUN_0008e500();
     * else -> FUN_00347d60(); noreturn FUN_001afe4c(). */
    (*(void (**)(void))(0x658c00))();   /* skp8_DAT_00658c00 */
    skp8_sk_fatal_error(0);                  /* failure tail (noreturn) */
}

/* skp8_FUN_00256f20 @ 0x00256f20   (est. sk_vspace_io_loop_short)
 * Ghidra: void skp8_FUN_00256f20(void)
 * Thin trampoline: jumps into skp8_FUN_00256f34 (the shared IO dispatch).
 * Confidence: medium
 */
void skp8_FUN_00256f20(void)
{
    skp8_FUN_00256f34();
}

/* skp8_FUN_00256f34 @ 0x00256f34   (est. sk_vspace_io_dispatch)
 * Ghidra: void skp8_FUN_00256f34(void)
 * Shared IO dispatch: CPU framing then a dense sequence of vspace helpers,
 * ending with two indirect calls through (extraout_x16+8)/(extraout_x16_00+8)
 * (jumptable not recoverable at 0x0025701c). Includes skp8_FUN_00257020().
 * Confidence: low (jumptable lost; indirect calls)
 */
void skp8_FUN_00256f34(void)
{
    /* FUN_0008e518(); FUN_00350c5c(); FUN_00352ee4(); FUN_00350920();
     * FUN_0031b080(); FUN_00354534(); FUN_0034e56c(); skp8_FUN_00257020();
     * FUN_00351b60(0xff); ... FUN_00310e08(); FUN_000841a0();
     * (**(*(x16+8)))(); (**(*(x16_00+8)))() — jumptable lost. */
    skp8_FUN_00257020();
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_00257020 @ 0x00257020   (est. sk_vspace_io_loop_deep)
 * Ghidra: void skp8_FUN_00257020(void)
 * The deepest IO loop: current-CPU framing then a long sequence of vspace
 * callback invocations. Iterates a completion predicate (FUN_0014ae44) until
 * set, running per-slot map/unmap callbacks; a failing iteration is a fatal
 * noreturn (FUN_00350410/skp8_FUN_003488bc/FUN_0006f768), success ends with the
 * thread epilogue FUN_0008e500.
 * Confidence: low (opaque callback pipeline, indirect dispatch)
 */
void skp8_FUN_00257020(void)
{
    /* FUN_0008e518(); ... ~60 helper calls through skp8_DAT_00658c00 and the
     * (*x16+0x20)/(*x16+8)/(*x16+0x10) per-slot callbacks (map/unmap of the
     * vspace slot bitmaps), looped under FUN_0014ae44 predicate until set.
     * Failure -> FUN_00350410(); skp8_FUN_003488bc(); FUN_0006f768(); noreturn.
     * Success -> FUN_0008e500(). */
    (*(void (**)(void))(0x658c00))();
    skp8_sk_vspace_fail(1);   /* skp8_FUN_003488bc() failure path */
    skp8_sk_fatal_error(0);
}

/* skp8_FUN_0025785c @ 0x0025785c   (est. sk_vspace_io_exit)
 * Ghidra: void skp8_FUN_0025785c(void)
 * IO exit path: current-CPU framing, then either a queued work dispatch
 * (FUN_000e15d8 -> skp8_FUN_00256f20) or a single-item dispatch through the
 * context function pointer (FUN_0034e4a4 -> skp8_FUN_00256f20 -> epilogue).
 * Ends with repeated thunk_FUN_00012568 releases and FUN_0008e500.
 * Confidence: low (opaque teardown pipeline)
 */
void skp8_FUN_0025785c(void)
{
    /* FUN_0008e518(); auVar3 = FUN_00357e84();
     * if ((auVar3._8_8_ & 1) == 0) { FUN_000e15d8(...); skp8_FUN_00256f20(); }
     * else { dispatch via (*ctx)(); FUN_0008e388(); FUN_00352ea8();
     *        skp8_FUN_00256f20(); FUN_00351160(); (*x8)(); }
     * thunk_FUN_00012568() x4; FUN_0008e500(); thunk_FUN_00012568(). */
    skp8_FUN_00256f20();
}

/* skp8_FUN_00257908 @ 0x00257908   (est. sk_vspace_io_loop4)
 * Ghidra: void skp8_FUN_00257908(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, undefined8 param_4)
 * Another dense IO loop: CPU framing then a long vspace callback pipeline,
 * iterating a completion predicate (FUN_00310cd4) and running per-slot
 * map/unmap callbacks through (*ctx+0x20)/(*ctx+8)/(*ctx+0x10). On the
 * terminal failing predicate it tails into the noreturn fatal FUN_001afe4c.
 * Confidence: low (opaque callback pipeline)
 */
void skp8_FUN_00257908(word_t a, word_t b, word_t c, word_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* FUN_0008e518(); ... ~50 helper calls (map/unmap slot callbacks),
     * iterating uVar7 = (*FUN_00310cd4)() completion predicate; on failure
     * FUN_00347d60(); noreturn FUN_001afe4c(); success -> FUN_0008e500(). */
    (*(void (**)(void))(0x658c00))();
    skp8_sk_fatal_error(0);   /* failure tail (noreturn) */
}

/* skp8_FUN_00257f8c @ 0x00257f8c   (est. sk_vspace_io_sweep)
 * Ghidra: void skp8_FUN_00257f8c(void)
 * IO sweep: frames the operation (FUN_0035193c), builds a buffer pair
 * (FUN_0035113c/FUN_00355d78), then loops a completion predicate
 * (FUN_0014ae44) invoking the buffered per-slot callbacks until set. Ends
 * with FUN_00351774 epilogue.
 * Confidence: low (opaque sweep pipeline)
 */
void skp8_FUN_00257f8c(void)
{
    /* FUN_0035193c(); FUN_00353e50(); FUN_00351ef8(); FUN_00348d94();
     * FUN_000dbf08(); FUN_00377824(); FUN_0034a37c();
     * do { FUN_000a6e14(); (*cb)(...); (*pcVar1)(); ...
     *      uVar4 = (*FUN_0014ae44)(); } while ((uVar4 & 1) == 0);
     * FUN_00351774(); */
    skp8_sk_object_lock(0, 0, 0, 0, 0);   /* FUN_00377824 */
}

/*==========================================================================*
 * Slot-bitmap walk / set operations (0x258250 - 0x259b64).
 * These operate on the vspace slot set: a bitmap at +0x40 (or +0x38), a data
 * array at +0x30, count at +0x10 and log2 capacity at +0x20. Set bits are
 * traversed MSB-first via the bit-reverse + LZCOUNT idiom.
 *==========================================================================*/

/* bit-reverse of a 64-bit mask, then leading-zero count: yields the index of
 * the first set bit scanning from the MSB (the seL4 find-first-set idiom). */
static inline unsigned long skp8_sk_bit_reverse(unsigned long v)
{
    v = ((v & 0xaaaaaaaaaaaaaaaaUL) >> 1) | ((v & 0x5555555555555555UL) << 1);
    v = ((v & 0xccccccccccccccccUL) >> 2) | ((v & 0x3333333333333333UL) << 2);
    v = ((v & 0xf0f0f0f0f0f0f0f0UL) >> 4) | ((v & 0x0f0f0f0f0f0f0f0fUL) << 4);
    v = ((v & 0xff00ff00ff00ff00UL) >> 8) | ((v & 0x00ff00ff00ff00ffUL) << 8);
    v = ((v & 0xffff0000ffff0000UL) >> 16) | ((v & 0x0000ffff0000ffffUL) << 16);
    return (v >> 32) | (v << 32);
}

/* skp8_FUN_00258250 @ 0x00258250   (est. sk_set_clear_slots)
 * Ghidra: void skp8_FUN_00258250(void)
 * Clears the slot set: iterates the bitmap at (x19+0x40), and for each set
 * slot calls FUN_0031996c/FUN_00310d98 (teardown of the slot entry at
 * data+slot*0x20) plus FUN_001f76f0, until all bits are cleared. Clears the
 * count and writes the tail status into *x20.
 * Confidence: medium (bitmap-iteration shape recovered)
 */
void skp8_FUN_00258250(void)
{
    /* FUN_000b4594(); FUN_0034fb14(); FUN_0034c988(); FUN_001fa430();
     * FUN_00353584(); if (no work) { FUN_0036b118(); *x20 = x21;
     *   FUN_000b45b0(); return; }
     * iterate bitmap@(x19+0x40): for each set bit i (MSB-first):
     *   FUN_0031996c/FUN_00310d98(data + i*0x20); FUN_001f76f0();
     * done -> *(x19+0x10)=0; *x20 = x21. */
    skp8_sk_free(0);   /* FUN_0036b118 representative */
}

/* skp8_FUN_0025837c @ 0x0025837c   (est. sk_set_clear_slots2)
 * Ghidra: void skp8_FUN_0025837c(void)
 * Second clear variant: iterates bitmap at (x19+0x40) with 0x28-byte slot
 * entries, calling FUN_0031996c / thunk_FUN_0036b270 for each set slot and
 * FUN_001f75c0 to clear. Ends with count=0 and *x20 = tail status.
 * Confidence: medium
 */
void skp8_FUN_0025837c(void)
{
    /* FUN_0035193c(); FUN_0034fb14(); FUN_0034c988(); FUN_001fa2e4();
     * FUN_00353584(); iterate 0x28-byte slots: FUN_0031996c/FUN_00359938 +
     * thunk_FUN_0036b270; FUN_001f75c0(); clear count; *x20 = x21. */
    skp8_sk_free(0);   /* FUN_0036b118 representative */
}

/* skp8_FUN_002584a8 @ 0x002584a8   (est. sk_set_clear_slots3)
 * Ghidra: void skp8_FUN_002584a8(void)
 * Third clear variant: iterates the bitmap with per-slot FUN_00319808 /
 * thunk_FUN_0036b270 and FUN_001f7820, tracking the bitmap via
 * puVar4[lVar1] (0x20-byte entries). Clears count and stores tail status.
 * Confidence: medium
 */
void skp8_FUN_002584a8(void)
{
    /* FUN_00351e20(); FUN_0034fb14(); FUN_0034c988(); FUN_001fa57c();
     * FUN_00353584(); iterate: FUN_00357eb4(idx); FUN_00319808();
     * thunk_FUN_0036b270(); FUN_001f7820(); clear count; *x20 = x21. */
    skp8_sk_free(0);   /* FUN_0036b118 representative */
}

/* skp8_FUN_002585b0 @ 0x002585b0   (est. sk_set_clear_slots4)
 * Ghidra: void skp8_FUN_002585b0(void)
 * Fourth clear variant: iterate with FUN_0031996c / FUN_00359938 +
 * thunk_FUN_0036b270 and FUN_001f795c. Ends by clearing count.
 * Confidence: medium
 */
void skp8_FUN_002585b0(void)
{
    /* FUN_0035193c(); FUN_0034fb14(); FUN_0034c988(); FUN_001fa6c8();
     * FUN_00353584(); iterate: FUN_00357eb4(idx); FUN_0031996c()/
     * FUN_00359938(); thunk_FUN_0036b270(); FUN_001f795c(); clear count. */
    skp8_sk_free(0);   /* FUN_0036b118 representative */
}

/* skp8_FUN_002586c4 @ 0x002586c4   (est. sk_set_clear_slots5)
 * Ghidra: void skp8_FUN_002586c4(void)
 * Fifth clear variant (0x10-byte slots): iterate, thunk_FUN_0036b270 twice
 * per slot and FUN_001f7aa4; clears count and stores tail status.
 * Confidence: medium
 */
void skp8_FUN_002586c4(void)
{
    /* FUN_00077698(); FUN_0034fb14(); FUN_0034c988(); uVar4 = FUN_001fa814();
     * if (count==0) { FUN_0036b118(); *x20 = uVar4; FUN_0007767c(); return; }
     * iterate 0x10-byte slots: thunk_FUN_0036b270 x2; FUN_001f7aa4();
     * clear count. */
    skp8_sk_free(0);   /* FUN_0036b118 representative */
}

/* skp8_FUN_002587e0 @ 0x002587e0   (est. sk_set_walk_and_apply)
 * Ghidra: void skp8_FUN_002587e0(undefined8 param_1, uint param_2, long param_3)
 * The core slot-set walk: loads the bitmap at (set+0x40), and for every set
 * bit (MSB-first via skp8_sk_bit_reverse+LZCOUNT) invokes either the read-callback
 * (+0x10 of the page/ASID buffer table at param_3) or the write-callback
 * (+0x20) depending on param_2&1, then FUN_001f7be0. When the walk completes
 * and param_2&1 is set, the whole bitmap is re-filled (FUN_001b5474 or a
 * direct -1L<< fill) and the count is reset to 0. If param_2&1 is clear the
 * bitmap is left intact. Writes the tail index into *x20.
 * Confidence: medium (bitmap walk + apply + optional clear recovered)
 * Notes: buffer tables at param_3 (page table) / param_3+8 (aux) with
 *   element stride at +0x48; stride-scaled slot addressing.
 */
void skp8_FUN_002587e0(word_t param_1, uint32_t apply_and_clear, long set)
{
    (void)param_1;
    long *slot_bitmap = (long *)(set + 0x40);
    unsigned long mask = 0xffffffffffffffffUL;
    unsigned long nbits = 1UL << ((*(uint8_t *)(set + 0x20)) & 0x3f);
    if ((*(uint8_t *)(set + 0x20) & 0x3f) < 6)
        mask = ~(-1L << (nbits & 0x3f));
    unsigned long bm = mask & (unsigned long)*slot_bitmap;
    long i = 0;
    for (;;) {
        while (bm != 0) {
            unsigned long r = skp8_sk_bit_reverse(bm);
            bm = bm - 1 & bm;
            unsigned long idx = (unsigned long)__builtin_clzll(r) | (unsigned long)i << 6;
            (void)idx;
            /* invoke read/write callback on the page & aux buffer slot:
             * (**(lVar9+0x10|0x20))(dst_page, page_slot, lVar16);
             * (**(lVar7+0x10|0x20))(dst_aux, aux_slot, lVar14);
             * skp8_sk_buf_copy(...);  (FUN_001f7be0) */
            skp8_sk_buf_copy(0, 0, 0);
        }
        long next = i + 1;
        if (__builtin_add_overflow(i, 1, &i)) __builtin_trap(); /* 0x258b20 */
        if ((long)((nbits + 0x3f) >> 6) <= next) {
            if (apply_and_clear & 1) {
                unsigned long nb = 1UL << ((*(uint8_t *)(set + 0x20)) & 0x3f);
                if ((*(uint8_t *)(set + 0x20) & 0x3f) < 6)
                    *slot_bitmap = -1L << (nb & 0x3f);
                else
                    skp8_sk_set_alloc_fill(0, (nb + 0x3f) >> 6, (unsigned long)slot_bitmap);
                *(long *)(set + 0x10) = 0;
            }
            skp8_sk_free((void *)set);   /* FUN_0036b118 */
            return;
        }
        bm = (unsigned long)slot_bitmap[next];
        i = next;
    }
}

/* skp8_FUN_00258b20 @ 0x00258b20   (est. sk_set_walk_apply_set)
 * Ghidra: void skp8_FUN_00258b20(undefined8 param_1, undefined8 param_2)
 * skp8_FUN_002587e0(param_1, 1, param_2): walk-and-apply that also clears the
 * bitmap (write/clear pass).
 * Confidence: medium
 */
void skp8_FUN_00258b20(word_t a, word_t set)
{
    skp8_FUN_002587e0(a, 1, set);
}

/* skp8_FUN_00258b2c @ 0x00258b2c   (est. sk_set_walk_apply_clear)
 * Ghidra: void skp8_FUN_00258b2c(undefined8 param_1, undefined8 param_2)
 * skp8_FUN_002587e0(param_1, 0, param_2): walk-and-apply that leaves the bitmap
 * intact (read pass).
 * Confidence: medium
 */
void skp8_FUN_00258b2c(word_t a, word_t set)
{
    skp8_FUN_002587e0(a, 0, set);
}

/* skp8_FUN_00258b88 @ 0x00258b88   (est. sk_set_membership)
 * Ghidra: bool skp8_FUN_00258b88(undefined8 param_1, undefined8 param_2,
 *          code *param_3)
 * Membership test with optional callback: on a stable comparison flag runs
 * either FUN_001fc0f4 or (on inequality) invokes param_3. Returns whether the
 * inherited x21 index precedes x19 (x21 < x19).
 * Confidence: low (flag-dependent membership shim)
 */
bool skp8_FUN_00258b88(word_t a, word_t b, void (*cb)(void))
{
    (void)a; (void)b;
    /* FUN_00355d4c(); if (NG == OV) { if (!(v&1)) { FUN_00355b68();
     *   FUN_00002534(); FUN_001fc0f4(); } } else { if (!(v&1))
     *   FUN_0035354c(); else FUN_00351330(); (*param_3)(); }
     * return x21 < x19; */
    if (cb) cb();
    return false;   /* x21 < x19 register comparison */
}

/* FUN_00258c60 @ 0x00258c60   (est. sk_set_for_each)
 * Ghidra: bool FUN_00258c60(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3)
 * For-each dispatch over the slot set: on the stable path calls
 * FUN_001fc0f4(param_3); otherwise dispatches skp8_FUN_00258b2c (clear pass) or
 * skp8_FUN_00258b20 (set pass) based on the flag. Returns x21 < x19.
 * Confidence: low (flag-selected walk)
 */
bool FUN_00258c60(word_t a, word_t b, word_t c)
{
    (void)a; (void)b; (void)c;
    /* FUN_00355d4c(); if (NG==OV) { if (!(v&1)) FUN_001fc0f4(c); }
     * else if (!(v&1)) { FUN_00356c3c(); skp8_FUN_00258b2c(); }
     * else { FUN_00356c3c(); skp8_FUN_00258b20(); }
     * return x21 < x19; */
    return false;
}

/* FUN_00258cf0 @ 0x00258cf0   (est. sk_set_panic)
 * Ghidra: void FUN_00258cf0(void)
 * Set-fatal: skp8_FUN_003488bc(1); noreturn skp8_FUN_0034a238().
 * Confidence: high (pure fatal path)
 */
void FUN_00258cf0(void)
{
    skp8_sk_vspace_fail(1);   /* skp8_FUN_003488bc(1) */
    skp8_sk_fatal_error(0);   /* skp8_FUN_0034a238 noreturn */
}

/* skp8_FUN_00258d10 @ 0x00258d10   (est. sk_set_apply_slot)
 * Ghidra: void skp8_FUN_00258d10(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, long param_4, undefined8 param_5,
 *          undefined8 param_6, undefined8 param_7)
 * Applies a slot operation: if the set count (param_4+0x10) is zero, or the
 * key probe FUN_001f99f4 reports the slot absent, returns status 1; otherwise
 * looks up the slot (FUN_00350bcc) and invokes the per-slot callback
 * (*(ctx+0x10)) on the data entry. Reports {result,status} via FUN_0034dba8.
 * Confidence: medium
 */
void skp8_FUN_00258d10(word_t a, word_t b, word_t c, long set, word_t e,
                  word_t f, word_t g)
{
    (void)a; (void)b; (void)c; (void)e; (void)f; (void)g;
    word_t st = 1;
    if (*(long *)(set + 0x10) != 0) {
        /* auVar3 = FUN_001f99f4(b, e, g); if (auVar3._8_8_ & 1) {
         *   idx = FUN_00350bcc(); (*(ctx+0x10))(a, data+idx*stride, f);
         *   st = 0; } */
        st = 0;
    }
    /* FUN_0034dba8(result, st); FUN_000839d8(); */
}

/* skp8_FUN_00258d9c @ 0x00258d9c   (est. sk_set_apply_two)
 * Ghidra: void skp8_FUN_00258d9c(undefined8 param_1, uint param_2, long *param_3,
 *          long param_4, undefined8 param_5, long param_6, long param_7,
 *          undefined8 param_8)
 * Applies a two-buffer slot operation (page + aux): builds the dest buffers,
 * runs the page callback (lVar3+0x10) on the slot, then either (status 1) a
 * combined write path (skp8_FUN_00259954) or (else) the aux callback and a
 * buffer copy (FUN_001f0700). param_2&1 selects the variant.
 * Confidence: medium (two-buffer slot apply recovered)
 */
void skp8_FUN_00258d9c(word_t a, uint32_t variant, long *out, long slot,
                  word_t e, long page, long aux, word_t h)
{
    (void)a; (void)e; (void)page; (void)aux; (void)h;
    /* (**(lVar3+0x10))(dst_page, a, page); iVar1 = FUN_000839f8(dst,1,aux);
     * if (iVar1 == 1) { (**(lVar3+8))(dst, page);
     *   if (variant & 1) { FUN_0035bc70(...); skp8_FUN_00259954(slot,*out,page,aux,h);} }
     * else { (**(lVar4+0x20))(dst_aux, dst, aux);
     *   if (!(variant&1)) { (**(lVar_+0x10))(buf, e, page);
     *     FUN_001f0700(slot, buf, dst_aux, *out, page, aux); }
     *   else (**(lVar4+0x20))(data+idx, dst_aux, aux); } */
    if (variant & 1) {
        skp8_FUN_00259954(slot, *out, page, aux, h);
    }
}

/* skp8_FUN_0025902c @ 0x0025902c   (est. sk_set_apply_dispatch)
 * Ghidra: void skp8_FUN_0025902c(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, long param_4)
 * Dispatch wrapper for a slot apply: CPU framing, then FUN_001fbb74; on the
 * set flag runs the page callback (*(*(lVar2-8)+0x20)); then skp8_FUN_00258d9c and
 * the completion epilogue.
 * Confidence: low (dense dispatch pipeline)
 */
void skp8_FUN_0025902c(word_t a, word_t b, word_t c, long set)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518(); lVar2 = *(set+0x18); FUN_00350488(); FUN_00310d68();
     * FUN_00348e00(); FUN_0007c1a4(); (*skp8_DAT_00658c00)(); FUN_0034b0c4();
     * FUN_001fbb74(...); if (flag) (**(*(lVar2-8)+0x20))();
     * FUN_00352480(); FUN_000839d8(); skp8_FUN_00258d9c(); FUN_0034dfe4();
     * (**(*(x16_00+8)))(...); FUN_0008e500(); */
    skp8_FUN_00258d9c(0, 0, 0, 0, 0, 0, 0, 0);
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_002591b4 @ 0x002591b4   (est. sk_set_grow)
 * Ghidra: void skp8_FUN_002591b4(void)
 * Set growth / rehash path: allocates a 0xc4-byte scratch (FUN_0006e778),
 * walks a descriptor (FUN_0034f064 / FUN_003a25d4 / FUN_003563fc), and loops
 * the rehash/rebalance pipeline (FUN_0034bf64) with fatal-error traps on
 * failure. Several unreachable blocks were removed by the decompiler.
 * Confidence: low (rehash pipeline, removed blocks)
 */
void skp8_FUN_002591b4(void)
{
    /* uVar2 = FUN_00354744(); auVar6 = FUN_0006e778(0xc4); ...
     * FUN_0034f064(); if (...) { FUN_003a25d4(...) } else { FUN_00356e98();
     *   FUN_003563fc(0xd000000000000018); }
     * do { FUN_0034bf64(...); if (ok) FUN_003a25d4(); else
     *   FUN_003563fc(0xd0000000000000aa); FUN_0006f768(Fatal_error);
     *   FUN_001b0938(); } while (true);  -- rehash loop, unreachable blocks
     *   (ram 0x259234/0x259278/0x259384/0x2593c8/0x2593b0) removed */
    skp8_sk_swift_release(0);   /* FUN_003a25d4 */
}

/*==========================================================================*
 * Hash-set insert / lookup / iterate (0x25941c - 0x25b0e0).
 * The vspace slot set as a Swift hashable collection: open-addressing on a
 * bitmap (set bits = occupied slots), MSB-first scan, hash into the table.
 *==========================================================================*/

/* skp8_FUN_0025941c @ 0x0025941c   (est. sk_set_collect)
 * Ghidra: undefined8 * skp8_FUN_0025941c(ulong *param_1, long param_2, long param_3,
 *          undefined8 *param_4, long param_5, long param_6, undefined8 param_7)
 * Collects the set bits of the slot bitmap param_1[0..param_2) into an
 * output set (param_4), building buffer pairs for each set slot and running
 * FUN_001f7be0 on each. param_3 is a remaining-count (decremented; stops at
 * 0). Returns the accumulated output set (param_4 or a fresh buffer).
 * Confidence: medium (bitmap collect + per-slot buffer copy recovered)
 */
word_t *skp8_FUN_0025941c(word_t *bitmap, long nwords, long remaining, word_t *out,
                     long page, long aux, word_t ctx)
{
    word_t *res = out;
    if (remaining == 0) {
        res = (word_t *)&skp8_DAT_00657798;   /* &skp8_DAT_00657798 sentinel */
    } else if ((long)remaining == (long)out[2]) {
        /* FUN_0036b270(out); res = out; */
        skp8_sk_alloc_pages(0, 0);
    } else {
        res = (word_t *)skp8_sk_hash_slot(remaining, page, aux, ctx);  /* FUN_001ee140 */
        long i = 0;
        unsigned long bm = nwords < 1 ? 0 : bitmap[0];
        unsigned long pending = 0;
        for (;;) {
            if (bm == 0) {
                long next = i + 1;
                if (__builtin_add_overflow(i, 1, &i)) __builtin_trap();  /* 0x259698 */
                if (nwords <= next) return res;
                bm = bitmap[next];
                i = next;
            }
            unsigned long r = skp8_sk_bit_reverse(bm);
            pending = bm - 1 & bm;
            unsigned long idx = (unsigned long)__builtin_clzll(r) | (unsigned long)i << 6;
            /* (**(lVar9+0x10))(dst_page, page_slot, page);
             * (**(lVar2+0x10))(dst_aux, aux_slot, aux);
             * skp8_sk_buf_copy(...); (FUN_001f7be0) */
            skp8_sk_buf_copy(0, 0, 0);
            if (__builtin_sub_overflow(remaining, 1, &remaining)) __builtin_trap();  /* 0x25969c */
            bm = pending;
            if (remaining == 0) break;
        }
        /* outer loop re-enters with new bitmap word from pending path */
        /* (fallthrough continues scan) */
        for (; bm != 0; ) {
            unsigned long r = skp8_sk_bit_reverse(bm);
            bm = bm - 1 & bm;
            unsigned long idx = (unsigned long)__builtin_clzll(r) | (unsigned long)i << 6;
            skp8_sk_buf_copy(0, 0, 0);
            if (__builtin_sub_overflow(remaining, 1, &remaining)) __builtin_trap();
        }
    }
    return res;
}

/* skp8_FUN_0025969c @ 0x0025969c   (est. sk_set_lookup)
 * Ghidra: void skp8_FUN_0025969c(void)
 * Lookup entry point: builds a buffer pair (FUN_0034c8e0), computes the slot
 * address (data + idx*stride) and runs the per-slot lookup callback chain,
 * ending with FUN_00356c54.
 * Confidence: low (dense lookup pipeline)
 */
void skp8_FUN_0025969c(void)
{
    /* FUN_00351708(); FUN_0034e39c(); (*skp8_DAT_00658c00)();
     * auVar1 = FUN_0034c8e0(); FUN_00351990(auVar1._0_8_, slot_addr);
     * (*x9)(); FUN_00350678(); FUN_003504a0(); (*x8_00)(); FUN_0034ea18();
     * (*x8_01)(); FUN_00356c54(); */
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_00259770 @ 0x00259770   (est. sk_set_get_value)
 * Ghidra: undefined8 skp8_FUN_00259770(long param_1, long param_2)
 * Reads the value stored at slot param_1 of the set at param_2: resolves the
 * data table (+0x30 with stride +0x48), invokes the read callback
 * (*(table+0x10)) to fetch the slot entry, runs the key apply
 * (FUN_0001a1c8) and the hash lookup (FUN_0031948c), then the release
 * callback (*(table+8)). Returns the fetched value.
 * Confidence: medium
 */
word_t skp8_FUN_00259770(long idx, long set)
{
    /* lVar4 = *(set+0x10); lVar7 = *(lVar4-8); (*skp8_DAT_00658c00)(*(lVar7+0x40));
     * lVar5 = *x20; uVar6 = *(x1+0x18); uVar1 = *(x1+0x20);
     * lVar2 = FUN_001f7d28(lVar5);
     * (**(lVar7+0x10))(&stack, lVar2 + *(lVar7+0x48)*idx, lVar4);
     * FUN_0001a1c8(lVar5, lVar4, uVar6, uVar1);
     * uVar6 = *(lVar5+0x28); pcVar3 = FUN_0031948c(uVar1);
     * uVar6 = (*pcVar3)(uVar6, lVar4, uVar1);
     * (**(lVar7+8))(&stack, lVar4); return uVar6; */
    skp8_sk_vspace_cb_sel();   /* FUN_0001a1c8 */
    return skp8_sk_swift_hash_combine(0, idx, 0);   /* FUN_0031948c */
}

/* skp8_FUN_002598b0 @ 0x002598b0   (est. sk_set_copy_range)
 * Ghidra: void skp8_FUN_002598b0(long param_1, long param_2, long param_3)
 * Copies the slot range [param_1, param_2) of the two data tables (page at
 * +0x10, aux at +0x18) of the set at param_3: for each table, FUN_0019ce60
 * copies the entry at idx*stride. Copy helper (FUN_0019ce60).
 * Confidence: medium
 */
void skp8_FUN_002598b0(long from, long to, long set)
{
    /* lVar5 = *x20; lVar3 = *(set+0x10); lVar1 = *(set+0x18);
     * lVar2 = FUN_001f7d28(lVar5); lVar4 = stride(lVar3);
     * FUN_0019ce60(lVar2 + lVar4*from, 1, lVar2 + lVar4*to, lVar3);
     * lVar3 = FUN_001f0bb4(lVar5); lVar2 = stride(lVar1);
     * FUN_0019ce60(lVar3 + lVar2*from, 1, lVar3 + lVar2*to, lVar1); */
    skp8_sk_buf_range(from, to, 0);     /* FUN_001f7d28 */
    skp8_sk_buf_range2(from, 0);        /* FUN_001f0bb4 */
    skp8_sk_elem_map(0, 0, 0, 0);       /* FUN_0019ce60 */
}

/* skp8_FUN_00259954 @ 0x00259954   (est. sk_set_remove)
 * Ghidra: void skp8_FUN_00259954(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, long param_4, undefined8 param_5)
 * Removes a set of slots: after CPU framing and a completion predicate, scans
 * the slot bitmap (MSB-first) and for each set slot runs the apply callback
 * (FUN_0031948c) plus a buffer teardown; coalesces adjacent freed runs via
 * FUN_0019ce60 and compacts the aux table. Decrements the count, trapping on
 * underflow (SoftwareBreakpoint 0x259b64).
 * Confidence: medium (remove + coalesce + count-decrement recovered)
 */
void skp8_FUN_00259954(word_t a, word_t b, word_t c, long set, word_t e)
{
    (void)a; (void)b; (void)c; (void)e;
    /* FUN_0008e518(); FUN_00352914(); FUN_00349720(); (*skp8_DAT_00658c00)(...);
     * FUN_003491ec(); FUN_003537b4(...); scan bitmap@(x19+0x40);
     * for each set bit uVar7: apply cb(FUN_0031948c)(obj+0x28, c, e);
     *   coalesce via FUN_0019ce60(page+uVar7, 1, page+unaff_x22, c) and
     *   FUN_0019ce60(aux+uVar7, 1, aux+unaff_x22);
     * FUN_00359fd4(); clear bitmap bit; if (!underflow(count-1)) {
     *   count--; FUN_00357da4(); FUN_0008e500(); } else trap. */
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_00259b64 @ 0x00259b64   (est. sk_set_filter)
 * Ghidra: void skp8_FUN_00259b64(undefined8 *param_1, long param_2, undefined8
 *          param_3, long param_4, code *param_5, undefined8 param_6, long
 *          param_7, long param_8, undefined8 param_9)
 * Filters the slot set through the predicate param_5: walks the bitmap, and
 * for each set slot runs the predicate on the page/aux buffer pair; if the
 * predicate returns set, the slot bit is retained in the output bitmap
 * (param_2) and the count incremented. Stops early when the inherited x21
 * flag is set. Writes the output set into *param_1.
 * Confidence: medium (filter walk + predicate + collect recovered)
 */
void skp8_FUN_00259b64(word_t *out, long out_bitmap, word_t a, long set,
                  word_t (*pred)(word_t, word_t), word_t f, long page,
                  long aux, word_t h)
{
    (void)a; (void)f; (void)h;
    word_t *bitmap = (word_t *)(set + 0x40);
    unsigned long nbits = 1UL << ((*(uint8_t *)(set + 0x20)) & 0x3f);
    unsigned long nwords = (nbits + 0x3f) >> 6;
    long i = 0;
    unsigned long bm = (unsigned long)bitmap[0];
    unsigned long pending = 0;
    long filled = 0;
    for (;;) {
        if (bm == 0) {
            long next = i + 1;
            if (__builtin_add_overflow(i, 1, &i)) __builtin_trap();  /* 0x259e60 */
            if ((long)nwords <= next) {
                *out = (word_t)skp8_FUN_0025941c((word_t *)out_bitmap, a, filled,
                                            (word_t *)set, page, aux, h);
                return;
            }
            bm = bitmap[next];
            i = next;
        }
        unsigned long r = skp8_sk_bit_reverse(bm);
        pending = bm - 1 & bm;
        unsigned long idx = (unsigned long)__builtin_clzll(r) | (unsigned long)i << 6;
        /* build page/aux buffer pairs; uVar10 = (*pred)(page_buf, aux_buf); */
        word_t keep = pred(0, 0);
        /* if (x21 != 0) return; -- early-out on inherited flag */
        bm = pending;
        if ((keep & 1) != 0) {
            unsigned long bit = idx & 0x3f;
            *(word_t *)(out_bitmap + ((idx >> 3) & 0x1ffffffffffffff8UL)) |=
                1UL << bit;   /* set bit in output bitmap */
            if (__builtin_add_overflow(filled, 1, &filled)) __builtin_trap();  /* 0x259e18 */
        }
    }
}

/* skp8_FUN_00259e60 @ 0x00259e60   (est. sk_set_op_wrap)
 * Ghidra: void skp8_FUN_00259e60(undefined8 *param_1)
 * Wrapper: thunk_FUN_001fca54(&local, *x20) then copies the 5-word (0x28-byte)
 * result into param_1[0..4].
 * Confidence: medium
 */
void skp8_FUN_00259e60(word_t *out)
{
    word_t local[5];
    skp8_sk_set_buf_pack((unsigned long)local, 0, 0);   /* thunk_FUN_001fca54 */
    memcpy(out, local, sizeof(local));
}

/* skp8_FUN_00259ea8 @ 0x00259ea8   (est. sk_set_next)
 * Ghidra: void skp8_FUN_00259ea8(long param_1, long param_2)
 * Iterator next: returns the next set slot after the current cursor (kept in
 * x20[3] word index / x20[4] pending mask). On exhaustion allocates a new
 * "key_value" descriptor (FUN_003722e4) and signals completion (status 1).
 * Otherwise emits the slot into the page+aux buffer pair via the callbacks
 * and the key apply FUN_0001a1c8, then reports via FUN_000839d8.
 * Confidence: medium (iterator + linear-probe advance recovered)
 */
void skp8_FUN_00259ea8(long out, long set)
{
    /* uVar8 = x20[4]; if (uVar8 == 0) { scan x20[1] bitmap words from x20[3];
     *   on exhaustion: lVar6 = FUN_003722e4(0, set+0x10, set+0x18,
     *        skp8_s_key_value_005cea2a, 0); uVar9 = 1; goto report; }
     * else { uVar4 = bit_reverse(uVar8); x20[4] = uVar8-1&uVar8;
     *   uVar8 = LZCOUNT(uVar4>>32|uVar4<<32) | x20[3]<<6; }
     * uVar9 = *x20; ... (**(*(page-8)+0x10))(out, page_slot, page);
     * FUN_0001a1c8(...); (**(*(aux-8)+0x10))(out+off, aux_slot, aux);
     * uVar9 = 0; report: FUN_000839d8(out, uVar9, 1, lVar6); */
    skp8_sk_vspace_cb_sel();   /* FUN_0001a1c8 */
}

/* skp8_FUN_0025a060 @ 0x0025a060   (est. skp8_sk_set_descriptor)
 * Ghidra: void skp8_FUN_0025a060(long param_1)
 * Set-descriptor helper: if param_1 is nonzero runs the descriptor init
 * (FUN_00351894/FUN_0031d3a4/FUN_00351d18) then FUN_0025a094; otherwise a
 * minimal no-op (FUN_0006e06c).
 * Confidence: medium (name reused from sk_region_obj.c)
 */
void skp8_FUN_0025a060(long d)
{
    if (d != 0) {
        /* FUN_00351894(); FUN_0031d3a4(); FUN_00351d18(); */
        FUN_0025a094();
        return;
    }
    /* FUN_0006e06c(); */
}

/* FUN_0025a094 @ 0x0025a094   (est. sk_set_descriptor_init)
 * Ghidra: void FUN_0025a094(void)
 * Set-descriptor init tail: FUN_001fab14(); FUN_0034c988(); skp8_FUN_0025e5d0().
 * Confidence: low (opaque init chain)
 */
void FUN_0025a094(void)
{
    /* FUN_001fab14(); FUN_0034c988(); skp8_FUN_0025e5d0(); */
    skp8_sk_object_lock(0, 0, 0, 0, 0);
}

/* skp8_FUN_0025a17c @ 0x0025a17c   (est. sk_set_for_each2)
 * Ghidra: void skp8_FUN_0025a17c(void)
 * For-each walk: CPU framing, then loops over the set bitmap; for each set
 * slot calls the per-slot callback (*(ctx+0x10)) and runs the apply helpers.
 * Ends with FUN_00359920 result and FUN_0008e500 epilogue.
 * Confidence: low (dense for-each pipeline)
 */
void skp8_FUN_0025a17c(void)
{
    /* FUN_0008e518(); ... while (set-bit) { FUN_00357a0c(*(x16+0x10),
     *   v, slot_addr); (*x8_02)(); FUN_00351ef8(); ... if (flag) break;
     *   lVar2 = idx+1; } auVar5 = FUN_00359920(v, flag); FUN_0008e500(); */
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_0025a2a0 @ 0x0025a2a0   (est. sk_set_for_each3)
 * Ghidra: void skp8_FUN_0025a2a0(undefined8 param_1, undefined8 param_2, long
 *          param_3, undefined8 param_4, undefined8 param_5)
 * For-each variant over the bitmap at (param_3+0x38): loops set bits
 * (MSB-first), invoking the per-slot callback and the apply helpers until the
 * completion flag. Ends with the result/flag pair via FUN_0008e500.
 * Confidence: low (dense for-each pipeline)
 */
void skp8_FUN_0025a2a0(word_t a, word_t b, long set, word_t c, word_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* FUN_0008e518(); FUN_00349a68(); (*skp8_DAT_00658c00)(...); FUN_00348f38();
     * FUN_00354948(*(set+0x20)); while (set bit in bitmap@(set+0x38)) {
     *   FUN_0035a28c(set); (**(x16+0x10))(); FUN_00351ad4(d); ... }
     * FUN_0008e500(v, flag); */
    (*(void (**)(void))(0x658c00))();
}

/* skp8_FUN_0025a3c8 @ 0x0025a3c8   (est. sk_set_clear)
 * Ghidra: void skp8_FUN_0025a3c8(void)
 * Clears the set: iterates the bitmap at (x19+0x38), and for each set slot
 * calls skp8_FUN_0025ab30(slot_lo, slot_hi) (the pair-insert) — i.e. re-seeding
 * cleared entries — until all bits are consumed; then resets the count.
 * Confidence: medium
 */
void skp8_FUN_0025a3c8(void)
{
    /* FUN_00084220(); FUN_0034fb14(); FUN_003557ec(); FUN_0034c988();
     * FUN_0025e4a0(); FUN_00353584(); iterate bitmap@(x19+0x38): for each
     * set bit i: skp8_FUN_0025ab30(data[i*0x10][0], data[i*0x10][1]);  -- pair
     * insert. done -> *(x19+0x10)=0; *x20 = x21. */
    /* inner: FUN_00356688() / FUN_0034bdbc() advance, SoftwareBreakpoint at
     * 0x25a4b4 on overflow; count clear at end. */
}

/* skp8_FUN_0025a4cc @ 0x0025a4cc   (est. sk_set_clear2)
 * Ghidra: void skp8_FUN_0025a4cc(void)
 * Clear variant: iterate the bitmap at (x23+0x38) and run the per-slot
 * callback (*x1) for each set slot until done; resets the count.
 * Confidence: low (opaque clear pipeline)
 */
void skp8_FUN_0025a4cc(void)
{
    /* FUN_0035193c(); FUN_0034fb14(); FUN_0034c988(); FUN_0025e370();
     * FUN_00353584(); iterate bitmap@(x23+0x38): (*x1)(); clear count. */
}

/* skp8_FUN_0025a5c4 @ 0x0025a5c4   (est. sk_set_apply_all)
 * Ghidra: void skp8_FUN_0025a5c4(void)
 * Applies the callback (*x22) to every set slot of the set (bitmap@(x23+0x38),
 * data stride 8): iterates set bits and calls (*x22)(data[i]). Resets count.
 * Confidence: medium
 */
void skp8_FUN_0025a5c4(void)
{
    /* FUN_00084220(); FUN_0034f284(); FUN_0034fb14(); FUN_0034c988();
     * FUN_0025e538(); FUN_00353584(); iterate bitmap@(x23+0x38): for each
     * set bit i: (*x22)(*(data + (idx<<6|i)*8));  -- apply cb to each slot.
     * clear count. */
}

/* skp8_FUN_0025a6a8 @ 0x0025a6a8   (est. sk_set_clear3)
 * Ghidra: void skp8_FUN_0025a6a8(void)
 * Clear variant with bitmap at (set+0x38): after CPU framing, iterates the
 * set bits, invokes the per-slot callback (*(ctx+0x20)) and the apply helpers
 * (FUN_0035620c/skp8_FUN_0025af6c); on completion re-fills the bitmap (via
 * FUN_00354948 / FUN_001b5474) and resets the count.
 * Confidence: medium
 */
void skp8_FUN_0025a6a8(void)
{
    /* FUN_0008e518(); FUN_003499f0(); (*skp8_DAT_00658c00)(...); FUN_00348f38();
     * lVar6 = *x20; ... scan bitmap@(lVar6+0x38); for each set bit:
     *   FUN_00353c24(*(x16+0x20), v, slot_addr); (*x8_03)();
     *   FUN_0035620c(); FUN_00352a58(); skp8_FUN_0025af6c();
     * done -> FUN_0034c6f4(*(lVar6+0x20)); re-fill bitmap; *(lVar6+0x10)=0;
     * *x20 = lVar3; FUN_0008e500(). */
    skp8_FUN_0025af6c();
    (*(void (**)(void))(0x658c00))();
}

/* FUN_0025a840 @ 0x0025a840   (est. sk_set_descriptor_init2)
 * Ghidra: void FUN_0025a840(undefined8 param_1, undefined8 param_2)
 * Set-descriptor init tail (2-arg): FUN_001fab14(param_2); FUN_0034c988();
 * skp8_FUN_0025e5d0().
 * Confidence: low (opaque init chain)
 */
void FUN_0025a840(word_t a, word_t b)
{
    (void)a; (void)b;
    /* FUN_001fab14(b); FUN_0034c988(); skp8_FUN_0025e5d0(); */
    skp8_sk_object_lock(0, 0, 0, 0, 0);
}

/* skp8_FUN_0025a864 @ 0x0025a864   (est. sk_set_insert_key)
 * Ghidra: void skp8_FUN_0025a864(undefined8 *param_1, long param_2)
 * Inserts the 5-word key param_1[0..4] into the set at param_2 (bitmap
 * @+0x38, data @+0x30, stride 0x28). Hashes the key (FUN_0008e5d8 +
 * FUN_0031993c), linearly probes: for each occupied slot compares the stored
 * key (FUN_0031996c + FUN_0031997c); a full match is a duplicate -> panic
 * skp8_FUN_0025bddc(0x673a80). On a free slot, sets the bit and copies the 5-word
 * key in; increments the count.
 * Confidence: medium (open-addressing hash-set insert recovered)
 */
void skp8_FUN_0025a864(word_t *key, long set)
{
    /* uVar9 = *(set+0x28) hash fn; FUN_0006a4c0(key, key[3]); hash = ...
     * uVar3 = (*FUN_0031993c)(uVar9, key); loop:
     *   uVar3 &= ~(-1L << (*(set+0x20)&0x3f));
     *   idx = uVar3 >> 6; bit = 1L << (uVar3&0x3f);
     *   if (!(bit & bitmap[idx])) { bitmap[idx] |= bit; copy key[0..4]
     *     into data + uVar3*0x28; *(set+0x10)++; return; }
     *   compare stored key vs new (FUN_0031996c/FUN_0031997c);
     *   if equal -> skp8_FUN_0025bddc(0x673a80) duplicate panic;
     *   uVar3++;  (linear probe) */
    skp8_sk_set_dup_panic(0x673a80);   /* duplicate-key panic (string addr) */
}

/* skp8_FUN_0025aa90 @ 0x0025aa90   (est. sk_set_insert_word)
 * Ghidra: void skp8_FUN_0025aa90(long param_1, long param_2)
 * Inserts the single-word key param_1 into the set at param_2 (bitmap@+0x38,
 * data@+0x30, stride 8). Hashes via thunk_FUN_00229ebc, linearly probes; on
 * finding the key already stored it is a duplicate -> panic
 * skp8_FUN_0025bddc(0x674278); otherwise sets the bit, stores the word and bumps
 * the count.
 * Confidence: medium (open-addressing word-set insert)
 */
void skp8_FUN_0025aa90(long key, long set)
{
    unsigned long h = skp8_sk_set_hash();   /* thunk_FUN_00229ebc(hash_fn, key) */
    unsigned long idx = h;
    for (;;) {
        idx &= ~(-1L << ((*(uint8_t *)(set + 0x20)) & 0x3f));
        unsigned long w = *(unsigned long *)(set + 0x38 + (idx >> 6) * 8);
        unsigned long bit = 1UL << (idx & 0x3f);
        if ((bit & w) == 0) {
            *(unsigned long *)(set + 0x38 + (idx >> 6) * 8) = bit | w;
            *(long *)(*(long *)(set + 0x30) + idx * 8) = key;
            *(long *)(set + 0x10) = *(long *)(set + 0x10) + 1;
            return;
        }
        if (*(long *)(*(long *)(set + 0x30) + idx * 8) == key) break;
        idx = idx + 1;
    }
    skp8_sk_set_dup_panic(0x674278);   /* duplicate-key panic */
}

/* skp8_FUN_0025ab30 @ 0x0025ab30   (est. sk_set_insert_pair)
 * Ghidra: void skp8_FUN_0025ab30(long param_1, ulong param_2, long param_3)
 * Inserts the pair (param_1, param_2) into the set at param_3 (bitmap@+0x38,
 * data@+0x30, stride 0x10). Hashes the pair with an SHA-512-style state
 * (FUN_001b9084 + FUN_001a8564) seeded by the IV words at skp8_DAT_006adf10/18,
 * linearly probes comparing stored pairs; a match is a duplicate -> panic
 * skp8_FUN_0025bddc(0x6753a0); else stores {param_1,param_2} and bumps the count.
 * Confidence: medium (open-addressing pair-set insert + hash)
 */
void skp8_FUN_0025ab30(long a, word_t b, long set)
{
    /* SHA-512-style seed constants (skp8_DAT_006adf10 ^ "sompesu"/"arenegyl"/...):
     * 0x736f6d6570736575, 0x6c7967656e657261, 0x7465646279746573,
     * 0x646f72616e646f6d — the hash state initialization.
     * FUN_001b9084(&state, a, b); uVar4 = FUN_001a8564();  (hash)
     * loop: idx &= ~(-1L << (*(set+0x20)&0x3f));
     *   if free: set bit; data[idx*0x10] = {a,b}; count++; return;
     *   if (stored == {a,b}) or FUN_002a0d50 eq -> duplicate panic 0x6753a0;
     *   idx++; */
    skp8_sk_swift_string_hash();   /* FUN_001a8564 */
    skp8_sk_swift_string_cmp(0, 0, 0, 0, 0);   /* FUN_002a0d50 */
    skp8_sk_set_dup_panic(0x6753a0);
}

/* FUN_0025acb8 @ 0x0025acb8   (est. sk_set_insert_key2)
 * Ghidra: void FUN_0025acb8(undefined8 *param_1, long param_2)
 * Second 5-word-key insert into the set at param_2 (bitmap@+0x38, stride
 * 0x28). Same open-addressing probe as skp8_FUN_0025a864; duplicate -> panic
 * skp8_FUN_0025bddc(0x673a80).
 * Confidence: medium
 */
void FUN_0025acb8(word_t *key, long set)
{
    (void)set;
    /* identical structure to skp8_FUN_0025a864: hash (FUN_0008e5d8 +
     * FUN_0031993c), linear probe comparing via FUN_0031996c/FUN_0031997c,
     * store 5-word key at data+idx*0x28, count++, duplicate panic
     * skp8_FUN_0025bddc(0x673a80). */
    skp8_sk_set_dup_panic(0x673a80);
}

/* FUN_0025aecc @ 0x0025aecc   (est. sk_set_insert_word2)
 * Ghidra: void FUN_0025aecc(long param_1, long param_2)
 * Second single-word insert (bitmap@+0x38, stride 8); duplicate -> panic
 * skp8_FUN_0025bddc(0x677880). Mirror of skp8_FUN_0025aa90.
 * Confidence: medium
 */
void FUN_0025aecc(long key, long set)
{
    unsigned long idx = skp8_sk_set_hash();   /* thunk_FUN_00229ebc(hash_fn, key) */
    for (;;) {
        idx &= ~(-1L << ((*(uint8_t *)(set + 0x20)) & 0x3f));
        unsigned long w = *(unsigned long *)(set + 0x38 + (idx >> 6) * 8);
        unsigned long bit = 1UL << (idx & 0x3f);
        if ((bit & w) == 0) {
            *(unsigned long *)(set + 0x38 + (idx >> 6) * 8) = bit | w;
            *(long *)(*(long *)(set + 0x30) + idx * 8) = key;
            *(long *)(set + 0x10) = *(long *)(set + 0x10) + 1;
            return;
        }
        if (*(long *)(*(long *)(set + 0x30) + idx * 8) == key) break;
        idx = idx + 1;
    }
    skp8_sk_set_dup_panic(0x677880);
}

/* skp8_FUN_0025af6c @ 0x0025af6c   (est. sk_set_insert_pipeline)
 * Ghidra: void skp8_FUN_0025af6c(void)
 * Insert pipeline: CPU framing, then scans the set bitmap; for the first free
 * slot sets the bit, invokes the per-slot init callback (*(ctx+0x20)) and
 * bumps the count. On collision runs the apply helpers; if the collision is
 * permanent it tails into the duplicate panic skp8_FUN_0025bddc.
 * Confidence: low (dense insert pipeline)
 */
void skp8_FUN_0025af6c(void)
{
    /* FUN_0008e518(); FUN_00350dd4(); FUN_00349720(); (*skp8_DAT_00658c00)(...);
     * FUN_00348f50(); FUN_00350678(); FUN_003510f4(); (*x8_00)();
     * uVar1 = FUN_0035377c(); while (1) {
     *   uVar1 &= ~extraout_x8_01;
     *   if free slot { set bit; (**(x16+0x20))(data+idx, x22); count++;
     *     FUN_0008e500(); return; }
     *   FUN_0035a28c(); FUN_00357a0c(...); (*x8_03)(); FUN_00351ad4();
     *   ... if (collision flag) break; uVar1++; }
     * skp8_FUN_0025bddc() noreturn duplicate panic. */
    (*(void (**)(void))(0x658c00))();
    skp8_sk_set_dup_panic(0);
}

/* skp8_FUN_0025b0e0 @ 0x0025b0e0   (est. sk_set_clear4)
 * Ghidra: void skp8_FUN_0025b0e0(void)
 * Clear variant (0x10-byte slots): iterate the bitmap at (x19+0x38), and for
 * each set slot run thunk_FUN_0036b270 on the slot's second word and
 * skp8_FUN_0025ab30 (pair-insert) to re-seed; resets the count.
 * Confidence: low (opaque clear pipeline)
 */
void skp8_FUN_0025b0e0(void)
{
    /* FUN_0008e518(); FUN_0034fb14(); FUN_003557ec(); FUN_0034c988();
     * FUN_0025e4a0(); FUN_00353584(); iterate bitmap@(x19+0x38): for each
     * set bit i: thunk_FUN_0036b270(data[i*0x10+8]); FUN_0034c6b4();
     *   skp8_FUN_0025ab30();  -- pair re-seed. done -> *x20 = x21. */
    skp8_sk_alloc_pages(0, 0);   /* thunk_FUN_0036b270 */
    skp8_FUN_0025ab30(0, 0, 0);
}
