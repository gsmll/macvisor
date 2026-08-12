/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R67: 0x461514-0x462b90. This region is the object/state management
 * table: per-object-type tag initializers (set a type byte at +0x98 or a
 * 3-word tag/flags group at +0x98/+0x158/+0x170), 16-byte state-descriptor
 * zero-init and copy/swap helpers (4-word descriptors at +0x28..+0x40 with a
 * type byte at +0x48), region-array insert/split machinery (stride-0x178
 * records at +0x20), and a tail of no-op witness handlers. All names are
 * estimates unless string-matched; Ghidra FUN_ names are kept only in
 * comments.
 *
 * Convention: decompiles that read the object pointer from x20/x19 without a
 * declared parameter (Ghidra "unaff_xNN") are modelled here by promoting that
 * register to a leading `word_t` parameter (documented per function). No-op
 * functions (body `return;`) are transcribed faithfully as empty handlers.
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

/* SoftwareBreakpoint(1, addr) fail-closed trap (brk #1). */
#define CL4_SW_BP(addr) __asm__ volatile("brk #1" ::: "memory")

/* noreturn SoftwareBreakpoint wrapper so the trap sites compile cleanly. */
__attribute__((noreturn)) static void cl4_sw_bp_trap(unsigned long addr)
{
    (void)addr;
    CL4_SW_BP(addr);
    __builtin_unreachable();
}

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use;
 * FUN_/thunk_ address in comment is ground truth. Helpers whose call arity
 * varies are declared variadic.
 * ------------------------------------------------------------------ */
extern void  sk_op_end(void);                       /* FUN_0036b21c — common handler tail */
extern void  sk_obj_put(word_t v);                  /* FUN_0036b118 — release/deref one word */
extern void  sk_region_enter(void);                 /* FUN_0010a9f8 */
extern void  sk_region_leave(void);                 /* FUN_00459138 */
extern void  sk_notify_finish(void);                /* FUN_00466104 */
extern void  sk_memcpy_tagged(void *dst, word_t size, word_t tag); /* FUN_0035bc70 */
extern void  sk_memmove_range(void *dst, word_t cnt, void *src);  /* FUN_00456cd8 */
extern void  sk_many_args(word_t a0, word_t a1, word_t a2, word_t a3, word_t a4,
                          word_t a5, word_t a6, word_t a7, word_t a8, word_t a9,
                          word_t a10);             /* FUN_003540d0 — 11-arg helper */
extern void  sk_obj_free(word_t v);                     /* FUN_003a25d4 — 0/1 arg (pass 0) */
extern void  sk_desc4_put(word_t a, word_t b, word_t c, word_t d); /* FUN_00458940 */
extern void  sk_state_lock(void);                   /* FUN_0034d868 */
extern void  sk_state_unlock(void);                 /* FUN_00458f00 */
extern void  sk_desc4_free(word_t a, word_t b, word_t c, word_t d, word_t t); /* FUN_00458f9c */
extern void  sk_desc4_put2(word_t a, word_t b, word_t c, word_t d); /* FUN_00464340 */
extern void  sk_desc_put_one(void *p);              /* FUN_0045f4fc */
extern word_t sk_state_after(void);                 /* FUN_004662e0 — returns ptr in x1 */
extern void  sk_type_bad(void);                     /* FUN_00459280 — type-check failure */
extern void  sk_type_bad2(void);                    /* FUN_004592dc */
extern void  sk_type_bad3(void);                    /* FUN_004593ac */
extern void  sk_check_fail(void);                   /* FUN_0045a3ac */
extern void  sk_log_tag(word_t tag);                /* FUN_00460d50 — format-string ref 0x64e038 */
extern cL4_w16_t sk_state_pair(void);               /* FUN_0046404c — returns ptr pair in x0/x1 */
extern word_t sk_state_init(void);                  /* FUN_004640b8 — returns ptr in x1 */
extern void  sk_merge_lock(void);                   /* FUN_00350c5c */
extern void  sk_state_notify(void);                 /* FUN_00466034 */
extern void  sk_finish2(void);                      /* FUN_00466124 */
extern void  sk_finish3(void);                      /* FUN_00465ce8 */
extern void  sk_finish4(void);                      /* FUN_00465128 */
extern void  sk_finish5(void);                      /* FUN_00463750 */
extern void  sk_finish6(void);                      /* FUN_00463a10 */
extern void  sk_exchange(word_t a, word_t b);       /* FUN_0045dab4 */
extern void  sk_finish7(void);                      /* FUN_00460d94 */
extern void  sk_finish8(void);                      /* FUN_00462ee8 */
extern void  sk_memzero_block(void *p, word_t n);   /* thunk_FUN_00114330 — memset-style */
extern void  sk_release_both(void);                 /* thunk_FUN_0036b270 */
extern word_t sk_get_pair(word_t a, word_t b);      /* FUN_00002534 */
extern word_t sk_pair_use(word_t a, word_t b, word_t c); /* FUN_003509c8 — returns vtable in x16 */
extern void  sk_early_boot(void);                   /* FUN_00027724 */
extern cL4_w16_t sk_state_pair2(void);              /* FUN_0034cdb4 — returns ptr pair */
extern void  sk_desc4_free_4(word_t a, word_t b, word_t c, word_t d); /* FUN_00458e80 */
extern void  sk_unused_455fe4(void);                /* FUN_00455fe4 */

/* Template globals copied by FUN_004618bc (DAT_005a1800 / 005a1808). */
extern word_t sk_global_5a1800;
extern word_t sk_global_5a1808;

/* No-op witness FUN_00462b90 (called from sk_dispatch_init with 6 args). */
void sk_noop_b90(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f);

/* ------------------------------------------------------------------ *
 * Function bodies (address order).
 * ------------------------------------------------------------------ */

/* FUN_00461514 @ 0x00461514   (est. sk_dispatch_init)
 * Ghidra: void FUN_00461514(void)   (object pointer in x20)
 * Dispatch initializer: enters the region, forwards 6 fields (+0x50..+0xa0)
 * of the object to sk_noop_b90, then runs region-leave/notify/finish tail.
 * Confidence: medium */
void sk_dispatch_init(word_t obj)
{
    sk_region_enter();
    sk_noop_b90(*(word_t *)(obj + 0xa0), *(word_t *)(obj + 0x50),
                *(word_t *)(obj + 0x60), *(word_t *)(obj + 0x70),
                *(word_t *)(obj + 0x80), *(word_t *)(obj + 0x90));
    sk_region_leave();
    sk_notify_finish();
    sk_op_end();
}

/* FUN_00461564 @ 0x00461564   (est. sk_dispatch_4args)
 * Ghidra: void FUN_00461564(void)   (object pointer in x20)
 * Forwards 4 object fields (+0x20..+0x38) to sk_desc4_put, then finish tail.
 * Confidence: medium */
void sk_dispatch_4args(word_t obj)
{
    sk_desc4_put(*(word_t *)(obj + 0x20), *(word_t *)(obj + 0x28),
                 *(word_t *)(obj + 0x30), *(word_t *)(obj + 0x38));
    sk_finish4();
    sk_op_end();
}

/* FUN_00461568 @ 0x00461568   (est. sk_dispatch_4args2)
 * Identical twin of FUN_00461564 (same 4-field forward + finish tail).
 * Confidence: medium */
void sk_dispatch_4args2(word_t obj)
{
    sk_desc4_put(*(word_t *)(obj + 0x20), *(word_t *)(obj + 0x28),
                 *(word_t *)(obj + 0x30), *(word_t *)(obj + 0x38));
    sk_finish4();
    sk_op_end();
}

/* FUN_00461590 @ 0x00461590   (est. sk_obj_set_size3)
 * Ghidra: void FUN_00461590(long param_1)
 * Sets the low 3 bits of the size/flags word at +0x68 to 3 (keeps the rest).
 * Confidence: high */
void sk_obj_set_size3(word_t param_1)
{
    *(word_t *)(param_1 + 0x68) = (*(word_t *)(param_1 + 0x68) & ~7UL) | 3UL;
}

/* FUN_004615a8 @ 0x004615a8   (est. sk_dispatch_many)
 * Ghidra: void FUN_004615a8(void)   (object pointer in x20)
 * Forwards 11 object fields (+0x20..+0x60) to the 11-arg helper, runs a type
 * check, releases two word fields (+0xb0, +0xd0, low 51 bits), then the
 * finish tail.
 * Confidence: medium */
void sk_dispatch_many(word_t obj)
{
    sk_many_args(*(word_t *)(obj + 0x60), *(word_t *)(obj + 0x70),
                 *(word_t *)(obj + 0x80), *(word_t *)(obj + 0x20),
                 *(word_t *)(obj + 0x28), *(word_t *)(obj + 0x30),
                 *(word_t *)(obj + 0x38), *(word_t *)(obj + 0x40),
                 *(word_t *)(obj + 0x48), *(word_t *)(obj + 0x50),
                 *(word_t *)(obj + 0x58));
    sk_type_bad3();
    sk_obj_put(*(word_t *)(obj + 0xb0) & 0xfffffffffffffffUL);
    sk_obj_put(*(word_t *)(obj + 0xd0) & 0xfffffffffffffffUL);
    sk_finish2();
    sk_op_end();
}

/* FUN_00461610 @ 0x00461610   (est. sk_region_insert)
 * Ghidra: void FUN_00461610(long param_1, long param_2, long param_3)
 *   (region-descriptor base pointer in x20)
 * Inserts a run into a sorted region table: copies `param_1` records worth of
 * data to a scratch span, shifts the tail right by `param_3` records, and
 * updates the record count at +0x10. Record stride is 0x178. All bounds
 * violations trap via SoftwareBreakpoint(1, addr).
 * Confidence: low (register base + carry/borrow checks reconstructed) */
void sk_region_insert(word_t param_1, word_t param_2, word_t param_3,
                      word_t reg_base)
{
    word_t base = *(word_t *)reg_base;      /* descriptor base */
    long lVar1 = (long)param_2 - (long)param_1;
    if ((long)param_2 < (long)param_1)      /* SBORROW8 */
        cl4_sw_bp_trap(0x4616c0);
    if (lVar1 < 0)
        cl4_sw_bp_trap(0x4616c4);
    word_t lVar4 = base;
    word_t lVar5 = lVar4 + 0x20 + param_1 * 0x178;
    sk_memcpy_tagged((void *)lVar5, (word_t)lVar1, 0x684390);
    long lVar2 = (long)param_3 - lVar1;
    if ((long)param_3 < lVar1)              /* SBORROW8 */
        cl4_sw_bp_trap(0x4616c8);
    if (lVar2 != 0) {
        if (*(long *)(lVar4 + 0x10) < (long)param_2)   /* SBORROW8 */
            cl4_sw_bp_trap(0x4616cc);
        sk_memmove_range((void *)(lVar4 + 0x20 + param_2 * 0x178),
                         (word_t)(*(long *)(lVar4 + 0x10) - (long)param_2),
                         (void *)(lVar5 + param_3 * 0x178));
        {
            long sum;
            if (__builtin_add_overflow(*(long *)(lVar4 + 0x10), lVar2, &sum))
                cl4_sw_bp_trap(0x4616d0);               /* SCARRY8 */
            *(long *)(lVar4 + 0x10) = sum;
        }
    }
    if (param_3 < 1)
        return;
    cl4_sw_bp_trap(0x4616d4);
}

/* FUN_004616d4 @ 0x004616d4   (est. sk_obj_flag_a)
 * Ghidra: void FUN_004616d4(long param_1)
 * Clears the low type bits of +0x98 and +0x158 and sets the low 3 bits of
 * the +0x170 flags word to 0xa (with top bit set).
 * Confidence: high */
void sk_obj_flag_a(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) =
        (*(word_t *)(param_1 + 0x170) & ~7UL) | 0xa000000000000000UL;
}

/* FUN_00461708 @ 0x00461708   (est. sk_obj_flag_4)
 * Same shape as FUN_004616d4 but flags word low 3 bits set to 0x4.
 * Confidence: high */
void sk_obj_flag_4(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) =
        (*(word_t *)(param_1 + 0x170) & ~7UL) | 0x4000000000000000UL;
}

/* FUN_00461738 @ 0x00461738   (est. sk_obj_flag_8)
 * Same shape; flags low 3 bits set to 0x8.
 * Confidence: high */
void sk_obj_flag_8(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) =
        (*(word_t *)(param_1 + 0x170) & ~7UL) | 0x8000000000000000UL;
}

/* FUN_00461768 @ 0x00461768   (est. sk_obj_flag_6)
 * Same shape; flags low 3 bits set to 0x6.
 * Confidence: high */
void sk_obj_flag_6(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) =
        (*(word_t *)(param_1 + 0x170) & ~7UL) | 0x6000000000000000UL;
}

/* FUN_00461798 @ 0x00461798   (est. sk_obj_flag_clear)
 * Same shape but only clears the low 3 bits of +0x170 (no new value set).
 * Confidence: high */
void sk_obj_flag_clear(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) &= ~7UL;
}

/* FUN_004617c4 @ 0x004617c4   (est. sk_obj_type_clear_hi)
 * Ghidra: void FUN_004617c4(long param_1)
 * Keeps only the low 2 bits of the type byte at +0x98.
 * Confidence: high */
void sk_obj_type_clear_hi(word_t param_1)
{
    *(byte *)(param_1 + 0x98) &= 3;
}

/* FUN_004617d4 @ 0x004617d4   (est. sk_cap_bits_extract)
 * Ghidra: int FUN_004617d4(long param_1)
 * Extracts a signed bitfield from the +0x98 word: (word>>6 & 0x3fffffffc) |
 * (word>>2 & 3); negates if the 32-bit result is > 0x80000000.
 * Confidence: medium */
int sk_cap_bits_extract(word_t param_1)
{
    word_t v = *(word_t *)(param_1 + 0x98);
    uint32_t u = ((uint32_t)(v >> 6) & 0xfffffffcU) | (((uint32_t)v >> 2) & 3U);
    int r = 0;
    if (0x80000000U < u)
        r = -(int)u;
    return r;
}

/* FUN_004617f0 @ 0x004617f0   (est. sk_obj_flag_2)
 * Same shape; flags low 3 bits set to 0x2.
 * Confidence: high */
void sk_obj_flag_2(word_t param_1)
{
    *(word_t *)(param_1 + 0x98) &= 0xf3UL;
    *(word_t *)(param_1 + 0x158) &= 0xf3UL;
    *(word_t *)(param_1 + 0x170) =
        (*(word_t *)(param_1 + 0x170) & ~7UL) | 0x2000000000000000UL;
}

/* FUN_00461820 @ 0x00461820   (est. sk_obj_init_fc_full)
 * Ghidra: void FUN_00461820(long param_1)
 * Zeroes +0x00..+0x97 and +0xa0/+0xa8, then sets the +0x98 tag word to 0xfc.
 * Confidence: high */
void sk_obj_init_fc_full(word_t param_1)
{
    sk_memzero_block((void *)param_1, 0x98);
    *(word_t *)(param_1 + 0xa0) = 0;
    *(word_t *)(param_1 + 0xa8) = 0;
    *(word_t *)(param_1 + 0x98) = 0xfc;
}

/* FUN_00461854 @ 0x00461854   (est. sk_obj_init_large)
 * Ghidra: void FUN_00461854(long param_1)
 * Zeroes +0x00..+0x97, sets +0x98 to 0x3fffffff0c, zeroes +0xa0..+0xd7.
 * Confidence: high */
void sk_obj_init_large(word_t param_1)
{
    sk_memzero_block((void *)param_1, 0x98);
    *(word_t *)(param_1 + 0x98) = 0x3fffffff0cUL;
    sk_memzero_block((void *)(param_1 + 0xa0), 0xd8);
}

/* FUN_00461894 @ 0x00461894   (est. sk_type_size)
 * Ghidra: int FUN_00461894(long param_1)
 * Computes 0x40 - u where u is a 6-bit field split out of the +0x98 byte
 * (high nibble | middle 2 bits << 4); returns 0 if u's complement > 0x30.
 * Confidence: medium */
int sk_type_size(word_t param_1)
{
    byte b = *(byte *)(param_1 + 0x98);
    uint32_t u = ((uint32_t)(b >> 4)) | (((uint32_t)((b >> 2) & 3)) << 4);
    int r = 0x40 - (int)u;
    if ((u ^ 0x3fU) > 0x30U)
        r = 0;
    return r;
}

/* FUN_004618bc @ 0x004618bc   (est. sk_obj_template_init)
 * Ghidra: void FUN_004618bc(undefined8 *param_1)
 * Copies the 2-word template from globals 0x5a1800/0x5a1808 into words 0-1
 * and zeroes words 2..0xf.
 * Confidence: high */
void sk_obj_template_init(word_t *param_1)
{
    param_1[1] = sk_global_5a1808;
    param_1[0] = sk_global_5a1800;
    param_1[3] = param_1[2] = 0;
    param_1[5] = param_1[4] = 0;
    param_1[7] = param_1[6] = 0;
    param_1[9] = param_1[8] = 0;
    param_1[11] = param_1[10] = 0;
    param_1[13] = param_1[12] = 0;
    param_1[15] = param_1[14] = 0;
}

/* FUN_004618dc @ 0x004618dc   (est. sk_offset_extract)
 * Ghidra: int FUN_004618dc(long param_1)
 * Returns a signed quantity from (word at +8)>>1, negated when > 0x80000000.
 * Confidence: medium */
int sk_offset_extract(word_t param_1)
{
    uint32_t u = (uint32_t)(*(word_t *)(param_1 + 8) >> 1);
    int r = 0;
    if (0x80000000U < u)
        r = -(int)u;
    return r;
}

/* FUN_004618f4 @ 0x004618f4   (est. sk_obj_init_fc)
 * Ghidra: void FUN_004618f4(long param_1)
 * Zeroes +0x00..+0x97 and sets the type byte at +0x98 to 0xfc.
 * Confidence: high */
void sk_obj_init_fc(word_t param_1)
{
    sk_memzero_block((void *)param_1, 0x98);
    *(byte *)(param_1 + 0x98) = 0xfc;
}

/* FUN_00461924 @ 0x00461924   (est. sk_obj_init_type2)
 * Ghidra: void FUN_00461924(undefined8 *param_1)
 * Sets word 0 to 2, zeroes bytes 0x08..0x97, sets the type byte at 0x98
 * (param_1[0x13]) to 0xe0.
 * Confidence: high */
void sk_obj_init_type2(word_t *param_1)
{
    param_1[0] = 2;
    sk_memzero_block((byte *)param_1 + 8, 0x90);
    *(byte *)((byte *)param_1 + 0x98) = 0xe0;
}

/* FUN_0046195c @ 0x0046195c   (est. sk_obj_init_type1)
 * Same shape as FUN_00461924 but word 0 set to 1.
 * Confidence: high */
void sk_obj_init_type1(word_t *param_1)
{
    param_1[0] = 1;
    sk_memzero_block((byte *)param_1 + 8, 0x90);
    *(byte *)((byte *)param_1 + 0x98) = 0xe0;
}

/* FUN_00461994 @ 0x00461994   (est. sk_obj_init_e0)
 * Ghidra: void FUN_00461994(long param_1)
 * Zeroes +0x00..+0x97 and sets the type byte at +0x98 to 0xe0.
 * Confidence: high */
void sk_obj_init_e0(word_t param_1)
{
    sk_memzero_block((void *)param_1, 0x98);
    *(byte *)(param_1 + 0x98) = 0xe0;
}

/* FUN_004619c4 @ 0x004619c4   (est. sk_obj_init_type3)
 * Same shape as FUN_00461924 but word 0 set to 3.
 * Confidence: high */
void sk_obj_init_type3(word_t *param_1)
{
    param_1[0] = 3;
    sk_memzero_block((byte *)param_1 + 8, 0x90);
    *(byte *)((byte *)param_1 + 0x98) = 0xe0;
}

/* FUN_004619fc @ 0x004619fc   (est. sk_type_0x30)
 * Ghidra: void FUN_004619fc(long param_1)
 * Sets the +0x98 type byte to (low2 preserved) | 0x30.
 * Confidence: high */
void sk_type_0x30(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x30;
}

/* FUN_00461a10 @ 0x00461a10   (est. sk_type_extract)
 * Ghidra: int FUN_00461a10(long param_1)
 * Returns (typebyte ^ 0xff) + 1 when the type byte > 2, else 0.
 * Confidence: medium */
int sk_type_extract(word_t param_1)
{
    int r = 0;
    if (2 < *(byte *)(param_1 + 0x98))
        r = (*(byte *)(param_1 + 0x98) ^ 0xff) + 1;
    return r;
}

/* FUN_00461a24 @ 0x00461a24   (est. sk_type_0xb0)
 * Type byte at +0x98 := (low2 preserved) | 0xb0.
 * Confidence: high */
void sk_type_0xb0(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0xb0;
}

/* FUN_00461a38 @ 0x00461a38   (est. sk_type_0xc0)
 * Confidence: high */
void sk_type_0xc0(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0xc0;
}

/* FUN_00461a4c @ 0x00461a4c   (est. sk_type_0xd0)
 * Confidence: high */
void sk_type_0xd0(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0xd0;
}

/* FUN_00461a60 @ 0x00461a60   (est. sk_obj_init_ff)
 * Zeroes +0x00..+0x97 and sets the type byte at +0x98 to 0xff.
 * Confidence: high */
void sk_obj_init_ff(word_t param_1)
{
    sk_memzero_block((void *)param_1, 0x98);
    *(byte *)(param_1 + 0x98) = 0xff;
}

/* FUN_00461a90 @ 0x00461a90   (est. sk_type_2)
 * Sets the +0x98 type byte to 2 (full byte store).
 * Confidence: high */
void sk_type_2(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = 2;
}

/* FUN_00461a9c @ 0x00461a9c   (est. sk_type_1)
 * Sets the +0x98 type byte to 1.
 * Confidence: high */
void sk_type_1(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = 1;
}

/* FUN_00461aa8 @ 0x00461aa8   (est. sk_type_0)
 * Sets the +0x98 type byte to 0.
 * Confidence: high */
void sk_type_0(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = 0;
}

/* FUN_00461ab0 @ 0x00461ab0   (est. sk_release_unless_one)
 * Ghidra: void FUN_00461ab0(void)   (reads incoming x4)
 * Releases the value in x4 unless it equals 1.
 * Confidence: medium */
void sk_release_unless_one(word_t in_x4)
{
    if (in_x4 == 1)
        return;
    sk_obj_free(in_x4);
}

/* FUN_00461ac4 @ 0x00461ac4   (est. sk_type_0xa0)
 * Confidence: high */
void sk_type_0xa0(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0xa0;
}

/* FUN_00461ad8 @ 0x00461ad8   (est. sk_type_0x90)
 * Confidence: high */
void sk_type_0x90(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x90;
}

/* FUN_00461aec @ 0x00461aec   (est. sk_check_type)
 * Ghidra: void FUN_00461aec(void)   (reads incoming w4)
 * If the incoming type byte is not -1, reports a type-check failure.
 * Confidence: medium */
void sk_check_type(char in_w4)
{
    if (in_w4 != (char)-1)
        sk_type_bad2();
}

/* FUN_00461b00 @ 0x00461b00   (est. sk_type_0x40)
 * Confidence: high */
void sk_type_0x40(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x40;
}

/* FUN_00461b14 @ 0x00461b14   (est. sk_type_0x60)
 * Confidence: high */
void sk_type_0x60(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x60;
}

/* FUN_00461b28 @ 0x00461b28   (est. sk_type_0x70)
 * Confidence: high */
void sk_type_0x70(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x70;
}

/* FUN_00461b3c @ 0x00461b3c   (est. sk_type_0x50)
 * Confidence: high */
void sk_type_0x50(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x50;
}

/* FUN_00461b50 @ 0x00461b50   (est. sk_type_0x10)
 * Confidence: high */
void sk_type_0x10(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x10;
}

/* FUN_00461b64 @ 0x00461b64   (est. sk_type_0x20)
 * Confidence: high */
void sk_type_0x20(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x20;
}

/* FUN_00461b78 @ 0x00461b78   (est. sk_type_0x80)
 * Confidence: high */
void sk_type_0x80(word_t param_1)
{
    *(byte *)(param_1 + 0x98) = (*(byte *)(param_1 + 0x98) & 3) | 0x80;
}

/* FUN_00461b8c @ 0x00461b8c   (est. sk_check_type_w)
 * Ghidra: void FUN_00461b8c(void)   (reads incoming w4)
 * If (value & 0xff00) != 0x200, reports a type-check failure.
 * Confidence: medium */
void sk_check_type_w(uint32_t in_w4)
{
    if ((in_w4 & 0xff00U) == 0x200U)
        return;
    sk_type_bad();
}

/* FUN_00461ba0 @ 0x00461ba0   (est. sk_check_type_l)
 * Ghidra: void FUN_00461ba0(void)   (reads incoming x4)
 * 64-bit twin of FUN_00461b8c.
 * Confidence: medium */
void sk_check_type_l(word_t in_x4)
{
    if ((in_x4 & 0xff00UL) == 0x200UL)
        return;
    sk_type_bad();
}

/* FUN_00461bb4 @ 0x00461bb4   (est. sk_obj_init_seven)
 * Ghidra: void FUN_00461bb4(undefined8 *param_1)
 * Zeroes words 0..0x11 except word 0xd which is set to 7.
 * Confidence: high */
void sk_obj_init_seven(word_t *param_1)
{
    for (int i = 0; i <= 0xc; i++)
        param_1[i] = 0;
    param_1[0xd] = 7;
    for (int i = 0xe; i <= 0x11; i++)
        param_1[i] = 0;
}

/* FUN_00461bd4 @ 0x00461bd4   (est. sk_type_size_alt)
 * Ghidra: int FUN_00461bd4(long param_1)
 * Returns 8 - (word@+0x68 & 7), or 0 when (u ^ 7) > 2.
 * Confidence: medium */
int sk_type_size_alt(word_t param_1)
{
    uint32_t u = (uint32_t)(*(word_t *)(param_1 + 0x68) & 7);
    int r = 8 - (int)u;
    if ((u ^ 7U) > 2U)
        r = 0;
    return r;
}

/* FUN_00461bf4 @ 0x00461bf4   (est. sk_pass_through)
 * Ghidra: undefined8 FUN_00461bf4(undefined8 param_1)
 * Runs a check and passes the argument through unchanged.
 * Confidence: medium */
word_t sk_pass_through(word_t param_1)
{
    sk_check_fail();
    return param_1;
}

/* FUN_00461c1c @ 0x00461c1c   (est. sk_obj_init_seven2)
 * Ghidra: void FUN_00461c1c(undefined8 *param_1)
 * Zeroes words 0..0xf except word 0xd which is set to 7.
 * Confidence: high */
void sk_obj_init_seven2(word_t *param_1)
{
    for (int i = 0; i <= 0xc; i++)
        param_1[i] = 0;
    param_1[0xd] = 7;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
}

/* FUN_00461c3c @ 0x00461c3c   (est. sk_obj_init_four)
 * Ghidra: void FUN_00461c3c(undefined8 *param_1)
 * Sets word 0 to 1, zeroes words 1..0xc, sets word 0xd to 4, zeroes 0xe/0xf.
 * Confidence: high */
void sk_obj_init_four(word_t *param_1)
{
    param_1[0] = 1;
    for (int i = 1; i <= 0xc; i++)
        param_1[i] = 0;
    param_1[0xd] = 4;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
}

/* FUN_00461c70 @ 0x00461c70   (est. sk_obj_init_four2)
 * Ghidra: void FUN_00461c70(undefined8 *param_1)
 * Zeroes words 0..0xf except word 0xd which is set to 4.
 * Confidence: high */
void sk_obj_init_four2(word_t *param_1)
{
    for (int i = 0; i <= 0xc; i++)
        param_1[i] = 0;
    param_1[0xd] = 4;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
}

/* FUN_00461c90 @ 0x00461c90   (est. sk_size_1)
 * Ghidra: void FUN_00461c90(long param_1)
 * Sets the low 3 bits of +0x68 to 1.
 * Confidence: high */
void sk_size_1(word_t param_1)
{
    *(word_t *)(param_1 + 0x68) = (*(word_t *)(param_1 + 0x68) & ~7UL) | 1UL;
}

/* FUN_00461ca4 @ 0x00461ca4   (est. sk_size_2)
 * Sets the low 3 bits of +0x68 to 2.
 * Confidence: high */
void sk_size_2(word_t param_1)
{
    *(word_t *)(param_1 + 0x68) = (*(word_t *)(param_1 + 0x68) & ~7UL) | 2UL;
}

/* FUN_00461cb8 @ 0x00461cb8   (est. sk_vtable_dispatch)
 * Ghidra: undefined8 FUN_00461cb8(undefined8 param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Resolves a pair, derives a vtable pointer, and calls *(vtable+8)(param_1).
 * Confidence: low (extraout_x16 vtable reconstructed) */
word_t sk_vtable_dispatch(word_t param_1, word_t param_2, word_t param_3)
{
    word_t v = sk_get_pair(param_2, param_3);
    word_t vtable = sk_pair_use(v, v, v);      /* returns vtable ptr in x16 */
    (*(void (*)(word_t))(vtable + 8))(param_1);
    return param_1;
}

/* FUN_00461d0c @ 0x00461d0c   (est. sk_dispatch_4)
 * Ghidra: void FUN_00461d0c(void)   (object pointer in x20)
 * Forwards 4 fields (+0x10..+0x28) to sk_desc4_free_4, then finish tail.
 * Confidence: medium */
void sk_dispatch_4(word_t obj)
{
    sk_desc4_free_4(*(word_t *)(obj + 0x10), *(word_t *)(obj + 0x18),
                    *(word_t *)(obj + 0x20), *(byte *)(obj + 0x28));
    sk_finish3();
    sk_op_end();
}

/* FUN_00461d10 @ 0x00461d10   (est. sk_dispatch_4b)
 * Identical twin of FUN_00461d0c.
 * Confidence: medium */
void sk_dispatch_4b(word_t obj)
{
    sk_desc4_free_4(*(word_t *)(obj + 0x10), *(word_t *)(obj + 0x18),
                    *(word_t *)(obj + 0x20), *(byte *)(obj + 0x28));
    sk_finish3();
    sk_op_end();
}

/* FUN_00461d3c @ 0x00461d3c   (est. sk_dispatch_1)
 * Ghidra: void FUN_00461d3c(void)   (object pointer in x20)
 * Releases field +0x10 and runs the finish tail.
 * Confidence: medium */
void sk_dispatch_1(word_t obj)
{
    sk_obj_put(*(word_t *)(obj + 0x10));
    sk_op_end();
}

/* FUN_00461d40 @ 0x00461d40   (est. sk_dispatch_1b)
 * Identical twin of FUN_00461d3c.
 * Confidence: medium */
void sk_dispatch_1b(word_t obj)
{
    sk_obj_put(*(word_t *)(obj + 0x10));
    sk_op_end();
}

/* FUN_00461d68 @ 0x00461d68   (est. sk_state_exchange)
 * Ghidra: void FUN_00461d68(undefined8 param_1, undefined8 param_2)
 * Exchanges the two arguments.
 * Confidence: medium */
void sk_state_exchange(word_t param_1, word_t param_2)
{
    sk_exchange(param_2, param_1);
}

/* FUN_00461d78 @ 0x00461d78   (est. sk_state_release)
 * Ghidra: void FUN_00461d78(long param_1)
 * Releases field +0x10; if the descriptor type byte at +0x48 is not -1,
 * releases the 4-word descriptor at +0x28..+0x40.
 * Confidence: medium */
void sk_state_release(word_t param_1)
{
    sk_obj_free(*(word_t *)(param_1 + 0x10));
    if (*(char *)(param_1 + 0x48) != -1)
        sk_desc4_free(*(word_t *)(param_1 + 0x28), *(word_t *)(param_1 + 0x30),
                      *(word_t *)(param_1 + 0x38), *(word_t *)(param_1 + 0x40), 0);
}

/* FUN_00461dc4 @ 0x00461dc4   (est. sk_state_merge2)
 * Ghidra: void FUN_00461dc4(void)   (dst=x19, src=x20)
 * Merges a 4-word descriptor (+0x28..+0x40) + type byte (+0x48) from src
 * into dst. If the intermediate state's type byte is -1 the descriptor is
 * dropped (sk_desc4_put2) and only the type byte is copied; otherwise the
 * descriptor words are copied under lock and the type byte stored.
 * Confidence: medium */
void sk_state_merge2(word_t dst, word_t src)
{
    sk_merge_lock();
    sk_state_pair();                        /* return discarded */
    word_t extra = sk_state_after();        /* FUN_004662e0 -> ptr in x1 */
    char cVar5 = *(char *)(extra + 0x48);
    sk_release_both();
    if (cVar5 == -1) {
        sk_desc4_put2(0,0,0,0);
        *(byte *)(dst + 0x48) = *(byte *)(src + 0x48);
    } else {
        word_t a = *(word_t *)(src + 0x28), b = *(word_t *)(src + 0x30);
        word_t c = *(word_t *)(src + 0x38), d = *(word_t *)(src + 0x40);
        sk_state_lock();
        sk_state_unlock();
        *(word_t *)(dst + 0x28) = a;
        *(word_t *)(dst + 0x30) = b;
        *(word_t *)(dst + 0x38) = c;
        *(word_t *)(dst + 0x40) = d;
        *(char *)(dst + 0x48) = cVar5;
    }
}

/* FUN_00461e44 @ 0x00461e44   (est. sk_state_merge)
 * Ghidra: void FUN_00461e44(void)   (dst=x19, src=x20)
 * State-merge hub with four cases keyed on the type bytes of the intermediate
 * state, dst (+0x48) and src (+0x48). Swaps the +0x10 word with the
 * intermediate state, then either copies, drops (sk_desc_put_one), or swaps
 * (sk_desc4_free of the old dst descriptor) the 4-word descriptor.
 * Confidence: medium */
void sk_state_merge(word_t dst, word_t src)
{
    sk_merge_lock();
    sk_state_pair();                        /* return discarded */
    word_t extra = sk_state_init();         /* FUN_004640b8 -> ptr in x1 */
    word_t uVar7 = *(word_t *)(dst + 0x10);
    *(word_t *)(dst + 0x10) = *(word_t *)(extra + 0x10);
    sk_release_both();
    sk_obj_free(uVar7);
    sk_state_notify();
    char cVar5 = *(char *)(src + 0x48);
    if (*(char *)(dst + 0x48) == -1) {
        if (cVar5 == -1) {
            word_t u8 = *(word_t *)(src + 0x30), u7 = *(word_t *)(src + 0x28);
            word_t u10 = *(word_t *)(src + 0x40), u9 = *(word_t *)(src + 0x38);
            *(byte *)(dst + 0x48) = *(byte *)(src + 0x48);
            *(word_t *)(dst + 0x40) = u10;
            *(word_t *)(dst + 0x38) = u9;
            *(word_t *)(dst + 0x30) = u8;
            *(word_t *)(dst + 0x28) = u7;
        } else {
            word_t u7 = *(word_t *)(src + 0x28), u9 = *(word_t *)(src + 0x30);
            word_t u8 = *(word_t *)(src + 0x38), u10 = *(word_t *)(src + 0x40);
            sk_state_lock();
            sk_state_unlock();
            *(word_t *)(dst + 0x28) = u7;
            *(word_t *)(dst + 0x30) = u9;
            *(word_t *)(dst + 0x38) = u8;
            *(word_t *)(dst + 0x40) = u10;
            *(char *)(dst + 0x48) = cVar5;
        }
    } else if (cVar5 == -1) {
        sk_desc_put_one((void *)(dst + 0x28));
        byte u6 = *(byte *)(src + 0x48);
        word_t u8 = *(word_t *)(src + 0x40), u7 = *(word_t *)(src + 0x38);
        word_t u9 = *(word_t *)(src + 0x28);
        *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
        *(word_t *)(dst + 0x28) = u9;
        *(word_t *)(dst + 0x40) = u8;
        *(word_t *)(dst + 0x38) = u7;
        *(byte *)(dst + 0x48) = u6;
    } else {
        word_t u7 = *(word_t *)(src + 0x28), u1 = *(word_t *)(src + 0x30);
        word_t u8 = *(word_t *)(src + 0x38), u2 = *(word_t *)(src + 0x40);
        sk_state_lock();
        sk_state_unlock();
        word_t u9 = *(word_t *)(dst + 0x28), u3 = *(word_t *)(dst + 0x30);
        word_t u10 = *(word_t *)(dst + 0x38), u4 = *(word_t *)(dst + 0x40);
        *(word_t *)(dst + 0x28) = u7;
        *(word_t *)(dst + 0x30) = u1;
        *(word_t *)(dst + 0x38) = u8;
        *(word_t *)(dst + 0x40) = u2;
        byte u6 = *(byte *)(dst + 0x48);
        *(char *)(dst + 0x48) = cVar5;
        sk_desc4_free(u9, u3, u10, u4, u6);     /* free old dst descriptor */
    }
}

/* FUN_00461f58 @ 0x00461f58   (est. sk_state_swap)
 * Ghidra: void FUN_00461f58(void)   (dst=x19, src=x20)
 * Swaps the +0x10/+0x18/+0x20 words with the intermediate state pair and
 * copies src words; then swaps the 4-word descriptor depending on the type
 * bytes of dst/src.
 * Confidence: low (extraout_w8 byte write reconstructed as 0) */
void sk_state_swap(word_t dst, word_t src)
{
    sk_merge_lock();
    cL4_w16_t pair = sk_state_pair();       /* FUN_0046404c */
    word_t uVar2 = *(word_t *)(pair.hi + 0x10);
    word_t uVar1 = *(word_t *)(pair.lo + 0x10);
    *(word_t *)(dst + 8) = *(word_t *)(pair.hi + 8);
    *(word_t *)(dst + 0x10) = uVar2;
    sk_obj_free(uVar1);
    word_t u2 = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x18) = u2;
    if (*(char *)(dst + 0x48) != -1) {
        if (*(char *)(src + 0x48) != -1) {
            sk_desc4_put2(*(word_t *)(dst + 0x28), *(word_t *)(dst + 0x30),
                          *(word_t *)(dst + 0x38), *(word_t *)(dst + 0x40));
            *(byte *)(dst + 0x48) = 0;      /* extraout_w8 (byte return of sk_desc4_put2) */
            sk_desc4_free(0,0,0,0,0);
            return;
        }
        sk_desc_put_one((void *)(dst + 0x28));
    }
    sk_desc4_put2(0,0,0,0);
    *(byte *)(dst + 0x48) = *(byte *)(src + 0x48);
}

/* FUN_00462088 @ 0x00462088   (est. sk_state_copy4)
 * Ghidra: undefined8 * FUN_00462088(undefined8 *param_1, undefined8 *param_2)
 * Copies the 4-word + byte descriptor from param_2 to param_1 after running
 * two finish helpers, and returns param_1.
 * Confidence: medium */
word_t *sk_state_copy4(word_t *param_1, word_t *param_2)
{
    word_t a = *param_2, b = param_2[1], d = param_2[2];
    byte c = *(byte *)((byte *)param_2 + 0x18);   /* param_2+3 as byte */
    sk_finish8();
    sk_finish7();
    *param_1 = a;
    param_1[1] = b;
    param_1[2] = d;
    *(byte *)((byte *)param_1 + 0x18) = c;
    return param_1;
}

/* FUN_004620e0 @ 0x004620e0   (est. sk_state_swap4)
 * Ghidra: undefined8 * FUN_004620e0(undefined8 *param_1, undefined8 *param_2)
 * Swaps the 4-word + byte descriptor: copies param_2 into param_1 and frees
 * the old param_1 descriptor via sk_desc4_free_4.
 * Confidence: medium */
word_t *sk_state_swap4(word_t *param_1, word_t *param_2)
{
    word_t a = *param_2, b = param_2[1], c = param_2[2];
    byte e = *(byte *)((byte *)param_2 + 0x18);
    sk_finish8();
    sk_finish7();
    word_t oa = *param_1, ob = param_1[1], oc = param_1[2];
    *param_1 = a;
    param_1[1] = b;
    param_1[2] = c;
    byte oe = *(byte *)((byte *)param_1 + 0x18);
    *(byte *)((byte *)param_1 + 0x18) = e;
    sk_desc4_free_4(oa, ob, oc, oe);
    return param_1;
}

/* FUN_00462148 @ 0x00462148   (est. sk_state_swap4b)
 * Ghidra: undefined8 * FUN_00462148(undefined8 *param_1, undefined8 *param_2)
 * Same swap as FUN_004620e0 but without the two finish helpers.
 * Confidence: medium */
word_t *sk_state_swap4b(word_t *param_1, word_t *param_2)
{
    word_t uc = param_2[2], eb = *(byte *)((byte *)param_2 + 0x18);
    word_t oa = *param_1, ob = param_1[1], oc = param_1[2];
    word_t ua = *param_2;
    param_1[1] = param_2[1];
    *param_1 = ua;
    param_1[2] = uc;
    byte oe = *(byte *)((byte *)param_1 + 0x18);
    *(byte *)((byte *)param_1 + 0x18) = eb;
    sk_desc4_free_4(oa, ob, oc, oe);
    return param_1;
}

/* FUN_0046239c @ 0x0046239c   (est. sk_state_copy_byte)
 * Ghidra: long FUN_0046239c(long param_1)
 * Copies the type byte at +0x28 from the intermediate state into param_1.
 * Confidence: medium */
word_t sk_state_copy_byte(word_t param_1)
{
    word_t extra = sk_state_after();        /* FUN_004662e0 -> ptr in x1 */
    *(byte *)(param_1 + 0x28) = *(byte *)(extra + 0x28);
    sk_release_both();
    return param_1;
}

/* FUN_004623d4 @ 0x004623d4   (est. sk_state_init_copy)
 * Ghidra: void FUN_004623d4(void)   (dst=x20, src=x19)
 * Initializes dst from the pair state and copies the type byte at +0x28 from
 * src into dst.
 * Confidence: medium */
void sk_state_init_copy(word_t dst, word_t src)
{
    sk_state_pair2();                       /* FUN_0034cdb4 */
    sk_finish6();
    sk_release_both();
    sk_obj_free(0);
    sk_finish5();
    *(byte *)(src + 0x28) = *(byte *)(dst + 0x28);
}

/* FUN_0046241c @ 0x0046241c   (est. sk_state_init_copy2)
 * Ghidra: void FUN_0046241c(void)   (dst=x20, src=x19)
 * Initializes dst words +8/+0x10 from the pair state, copies +0x18/+0x20 and
 * the type byte at +0x28 from src into dst.
 * Confidence: medium */
void sk_state_init_copy2(word_t dst, word_t src)
{
    cL4_w16_t pair = sk_state_pair2();      /* FUN_0034cdb4 */
    word_t u2 = *(word_t *)(pair.hi + 0x10);
    word_t u1 = *(word_t *)(pair.lo + 0x10);
    *(word_t *)(dst + 8) = *(word_t *)(pair.hi + 8);
    *(word_t *)(dst + 0x10) = u2;
    sk_obj_free(u1);
    word_t u2b = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x18) = u2b;
    *(byte *)(dst + 0x28) = *(byte *)(src + 0x28);
}

/* FUN_00462848 @ 0x00462848   (est. sk_state_load16)
 * Ghidra: undefined1 [16] FUN_00462848(undefined8 param_1,
 *                                       undefined1 (*param_2) [16])
 * Returns the 16-byte value pointed to by param_2 unchanged.
 * Confidence: high */
cL4_w16_t sk_state_load16(word_t param_1, const cL4_w16_t *param_2)
{
    (void)param_1;
    return *param_2;
}

/* FUN_00462898 @ 0x00462898   (est. sk_log_638)
 * Ghidra: void FUN_00462898(void)
 * Emits a log message with the format-string reference 0x64e038.
 * Confidence: medium */
void sk_log_638(void)
{
    sk_log_tag(0x64e038);
}

/* FUN_00462908 @ 0x00462908   (est. sk_state_index)
 * Ghidra: undefined1 [16] FUN_00462908(void)   (obj=x19, index=x22)
 * Returns a 16-byte (base, meta) pair for a stride-0x50 element: increments
 * the element count at *(obj+0x50)+0x10 and returns the element base at
 * *(obj+0x50) + idx*0x50 + 0x20.
 * Confidence: low (stack-meta word rendered as 0) */
cL4_w16_t sk_state_index(word_t obj, word_t idx)
{
    word_t base = *(word_t *)(obj + 0x50);
    *(long *)(base + 0x10) = (long)idx + 1;
    cL4_w16_t r = { .lo = base + idx * 0x50 + 0x20, .hi = 0 }; /* hi was &stack0x1000 */
    return r;
}

/* FUN_0046295c @ 0x0046295c   (est. sk_get_tag)
 * Ghidra: undefined8 FUN_0046295c(void)
 * Returns the constant tag 0x677880.
 * Confidence: high */
word_t sk_get_tag(void)
{
    return 0x677880;
}

/* FUN_00462974 @ 0x00462974   (est. sk_state_advance)
 * Ghidra: undefined1 [16] FUN_00462974(long param_1)
 * Returns a 16-byte value built from param_1+1 (decompiler shows a 128-bit
 * left shift by 64; rendered as {0, param_1+1}).
 * Confidence: low */
cL4_w16_t sk_state_advance(word_t param_1)
{
    cL4_w16_t r = { .lo = 0, .hi = param_1 + 1 };   /* auVar1 << 0x40 artifact */
    return r;
}

/* FUN_00462a48 @ 0x00462a48   (est. sk_state_clear4)
 * Ghidra: void FUN_00462a48(long param_1)
 * Zeroes the 4-word descriptor at +0x28..+0x40.
 * Confidence: high */
void sk_state_clear4(word_t param_1)
{
    *(word_t *)(param_1 + 0x30) = 0;
    *(word_t *)(param_1 + 0x28) = 0;
    *(word_t *)(param_1 + 0x40) = 0;
    *(word_t *)(param_1 + 0x38) = 0;
}

/* FUN_00462a84 @ 0x00462a84   (est. sk_get_tag2)
 * Ghidra: undefined8 FUN_00462a84(void)
 * Returns the constant tag 0x677880.
 * Confidence: high */
word_t sk_get_tag2(void)
{
    return 0x677880;
}

/* FUN_00462abc @ 0x00462abc   (est. sk_get_tag_init)
 * Ghidra: undefined8 FUN_00462abc(void)
 * Runs an early-boot step, then returns the constant tag 0x677880.
 * Confidence: medium */
word_t sk_get_tag_init(void)
{
    sk_early_boot();
    return 0x677880;
}

/* FUN_00462710 @ 0x00462710   (est. sk_noop)
 * Ghidra: void FUN_00462710(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462710(void) {}

/* FUN_00462728 @ 0x00462728   (est. sk_noop)
 * Ghidra: void FUN_00462728(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462728(void) {}

/* FUN_00462740 @ 0x00462740   (est. sk_noop)
 * Ghidra: void FUN_00462740(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462740(void) {}

/* FUN_00462758 @ 0x00462758   (est. sk_noop)
 * Ghidra: void FUN_00462758(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462758(void) {}

/* FUN_00462770 @ 0x00462770   (est. sk_noop)
 * Ghidra: void FUN_00462770(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462770(void) {}

/* FUN_00462788 @ 0x00462788   (est. sk_noop)
 * Ghidra: void FUN_00462788(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462788(void) {}

/* FUN_004627a0 @ 0x004627a0   (est. sk_noop)
 * Ghidra: void FUN_004627a0(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004627a0(void) {}

/* FUN_004627b8 @ 0x004627b8   (est. sk_noop)
 * Ghidra: void FUN_004627b8(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004627b8(void) {}

/* FUN_004627d0 @ 0x004627d0   (est. sk_noop)
 * Ghidra: void FUN_004627d0(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004627d0(void) {}

/* FUN_004627f4 @ 0x004627f4   (est. sk_noop)
 * Ghidra: void FUN_004627f4(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004627f4(void) {}

/* FUN_00462810 @ 0x00462810   (est. sk_noop)
 * Ghidra: void FUN_00462810(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462810(void) {}

/* FUN_0046282c @ 0x0046282c   (est. sk_noop)
 * Ghidra: void FUN_0046282c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_0046282c(void) {}

/* FUN_00462870 @ 0x00462870   (est. sk_noop)
 * Ghidra: void FUN_00462870(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462870(void) {}

/* FUN_00462884 @ 0x00462884   (est. sk_noop)
 * Ghidra: void FUN_00462884(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462884(void) {}

/* FUN_004628c4 @ 0x004628c4   (est. sk_noop)
 * Ghidra: void FUN_004628c4(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004628c4(void) {}

/* FUN_004628d8 @ 0x004628d8   (est. sk_noop)
 * Ghidra: void FUN_004628d8(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004628d8(void) {}

/* FUN_004628f4 @ 0x004628f4   (est. sk_noop)
 * Ghidra: void FUN_004628f4(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004628f4(void) {}

/* FUN_00462928 @ 0x00462928   (est. sk_noop)
 * Ghidra: void FUN_00462928(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462928(void) {}

/* FUN_00462948 @ 0x00462948   (est. sk_noop)
 * Ghidra: void FUN_00462948(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462948(void) {}

/* FUN_00462988 @ 0x00462988   (est. sk_noop)
 * Ghidra: void FUN_00462988(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462988(void) {}

/* FUN_0046299c @ 0x0046299c   (est. sk_noop)
 * Ghidra: void FUN_0046299c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_0046299c(void) {}

/* FUN_004629b4 @ 0x004629b4   (est. sk_noop)
 * Ghidra: void FUN_004629b4(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004629b4(void) {}

/* FUN_004629cc @ 0x004629cc   (est. sk_noop)
 * Ghidra: void FUN_004629cc(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004629cc(void) {}

/* FUN_004629e0 @ 0x004629e0   (est. sk_noop)
 * Ghidra: void FUN_004629e0(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004629e0(void) {}

/* FUN_004629f4 @ 0x004629f4   (est. sk_noop)
 * Ghidra: void FUN_004629f4(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_004629f4(void) {}

/* FUN_00462a08 @ 0x00462a08   (est. sk_noop)
 * Ghidra: void FUN_00462a08(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a08(void) {}

/* FUN_00462a1c @ 0x00462a1c   (est. sk_noop)
 * Ghidra: void FUN_00462a1c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a1c(void) {}

/* FUN_00462a34 @ 0x00462a34   (est. sk_noop)
 * Ghidra: void FUN_00462a34(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a34(void) {}

/* FUN_00462a5c @ 0x00462a5c   (est. sk_noop)
 * Ghidra: void FUN_00462a5c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a5c(void) {}

/* FUN_00462a70 @ 0x00462a70   (est. sk_noop)
 * Ghidra: void FUN_00462a70(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a70(void) {}

/* FUN_00462a98 @ 0x00462a98   (est. sk_noop)
 * Ghidra: void FUN_00462a98(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462a98(void) {}

/* FUN_00462aac @ 0x00462aac   (est. sk_noop)
 * Ghidra: void FUN_00462aac(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462aac(void) {}

/* FUN_00462adc @ 0x00462adc   (est. sk_noop)
 * Ghidra: void FUN_00462adc(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462adc(void) {}

/* FUN_00462af0 @ 0x00462af0   (est. sk_noop)
 * Ghidra: void FUN_00462af0(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462af0(void) {}

/* FUN_00462b00 @ 0x00462b00   (est. sk_noop)
 * Ghidra: void FUN_00462b00(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b00(void) {}

/* FUN_00462b10 @ 0x00462b10   (est. sk_noop)
 * Ghidra: void FUN_00462b10(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b10(void) {}

/* FUN_00462b2c @ 0x00462b2c   (est. sk_noop)
 * Ghidra: void FUN_00462b2c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b2c(void) {}

/* FUN_00462b40 @ 0x00462b40   (est. sk_noop)
 * Ghidra: void FUN_00462b40(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b40(void) {}

/* FUN_00462b54 @ 0x00462b54   (est. sk_noop)
 * Ghidra: void FUN_00462b54(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b54(void) {}

/* FUN_00462b6c @ 0x00462b6c   (est. sk_noop)
 * Ghidra: void FUN_00462b6c(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b6c(void) {}

/* FUN_00462b80 @ 0x00462b80   (est. sk_noop)
 * Ghidra: void FUN_00462b80(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b80(void) {}

/* FUN_00462b90 @ 0x00462b90   (est. sk_noop)
 * Ghidra: void FUN_00462b90(void)
 * No-op witness handler (decompiled body is `return;`).
 * Confidence: high (decompiler reports no stores or calls) */
void sk_noop_00462b90(void) {}
