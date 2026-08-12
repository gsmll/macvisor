/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * This region (0x30000-0x40000) is the boot / early-init region: TCB & cap
 * init, scheduling init, CNode/object init, early boot handoff.
 */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

/* Ghidra's "SoftwareBreakpoint(code, addr)" — an unconditional fault that
 * does not return. Rendered as a trap marker. */
#define SoftwareBreakpoint(code, addr)  ((unsigned long)0x5519UL)
#define sk_mem_zero_impl 0

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern; bodies reconstructed by
 * the sibling range worker that owns them). Names are estimates.
 * ------------------------------------------------------------------ */

/* Core lock/refcount/allocator primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */

/* Object method-dispatch table base used by object constructors. */
extern unsigned char sk_obj_methods_0[];  /* DAT_00611b24 */
extern unsigned char sk_obj_methods_1[];  /* DAT_00611b34 / DAT_00611b3c / LAB_00611b2c */

/* Boot handoff helper owned by the earlier range (0x2xxxx). */
extern void sk_boot_handoff_stage(void);   /* FUN_0002ff48 */

/* Decompressor constant tables (data region 0x4bcxxx). */
extern uint32_t sk_dec_magic;              /* DAT_004bc6e0 */
extern uint32_t sk_dec_mask0;              /* DAT_004bc6f0 */
extern uint32_t sk_dec_mask1;              /* DAT_004bc6f4 */
extern uint32_t sk_dec_mask2;              /* DAT_004bc6f8 */
extern uint32_t sk_dec_mask3;              /* DAT_004bc6fc */
extern uint32_t sk_dec_maska;              /* DAT_004bc710 */
extern uint32_t sk_dec_maskb;              /* DAT_004bc714 */
extern uint32_t sk_dec_maskc;              /* DAT_004bc718 */
extern uint32_t sk_dec_maskd;              /* DAT_004bc71c */
extern uint8_t  sk_dec_msk[4][16];         /* DAT_004bc740..75c */
extern uint8_t  sk_dec_hist_table[256];    /* DAT_004bc5e0 */

/* Utility helpers (data/early region). */
extern void sk_mem_zero(void *dst, unsigned long len);   /* FUN_001143a0 */
extern void sk_vas_abort(const char *fmt, ...);          /* FUN_004afae4 (VAS abort) */
extern void sk_vas_fault(void);                          /* FUN_004b1d08 */
extern int  sk_vm_lock_check(unsigned long);             /* FUN_00118164 */
extern int  sk_vm_lock_take(unsigned long);              /* FUN_00118194 */
extern int  sk_vm_lock_take2(unsigned long, int);        /* FUN_00118148 */
extern unsigned long sk_vm_bitmap_find(unsigned long, unsigned long); /* FUN_004b1d40 */
extern void sk_vas_fault2(void);                         /* FUN_004b1de4 */
extern void sk_vas_fault3(void);                         /* FUN_004b1e90 */
extern void sk_vas_fault4(void);                         /* FUN_004b1ec8 */
extern void sk_vas_fault5(void);                         /* FUN_004b1f04 */
extern void sk_vas_fault6(void);                         /* FUN_004b1f3c */
extern void sk_vas_fault7(void);                         /* FUN_004b1e1c */
extern void sk_vas_fault8(void);                         /* FUN_004b1e58 */

/* vspace subsystem helpers (same region). */
extern unsigned long sk_vspace_new_small(void);          /* FUN_00033da4 */
extern unsigned long sk_vspace_new_large(void);          /* FUN_00033e64 */
extern unsigned long sk_vspace_small_release(void);      /* FUN_00033e00 */
extern void sk_vspace_large_destroy(unsigned long);      /* FUN_000341f4 */
extern void sk_vspace_store_attach(long, unsigned long); /* FUN_00030fb0 */
extern void sk_vspace_store_release(long, unsigned long);/* FUN_000314b4 */
extern void *sk_vspace_node_alloc(void);                 /* FUN_000333a8 */
extern void *sk_vspace_block_alloc(void);                /* FUN_0003335c */
extern void sk_vspace_level_bump(long);                  /* FUN_00031bf4 */
extern void *sk_vspace_alloc_big(unsigned long, int, int);/* FUN_0005acac */

/* Early vspace globals (data region 0x64cxxx / 0x6axxxx). */
extern void *sk_vspace_root_obj;           /* DAT_0064c3f0 */
extern unsigned long sk_vspace_free_head;  /* DAT_0064c528 */
extern void *sk_vspace_free_tail;          /* DAT_0064c530 */
extern unsigned long sk_vspace_lock;       /* DAT_0064c5e0 */
extern unsigned long sk_vspace_lock2;      /* DAT_0064c430 */
extern unsigned long sk_vspace_c5f0;       /* DAT_0064c5f0 */
extern unsigned long sk_vspace_c690;       /* DAT_0064c690 */
extern unsigned long sk_vspace_c6b0;       /* DAT_0064c6b0 */
extern unsigned long sk_vspace_sentinel_tag;   /* sk_vspace_sentinel_tag */
extern unsigned long sk_vspace_sentinel_next;  /* sk_vspace_sentinel_next */
extern unsigned long sk_vspace_sentinel_eff0;  /* sk_vspace_sentinel_eff0 */
extern unsigned long sk_vspace_free_sentinel;  /* sk_vspace_free_sentinel */
extern unsigned long sk_vspace_lock_6af000;/* 0x6af000 */
extern unsigned long sk_vspace_lock_6ad2b0;/* 0x6ad2b0 */
extern void *sk_obj_table_0;               /* DAT_0064c3f0 (table head) */

/* Boot object-table helpers. */
extern void sk_obj_table_init(unsigned long, unsigned long, unsigned long);  /* FUN_00034970 / FUN_00034920 */
extern void sk_list_init(void *head);                         /* FUN_0005ba5c */
extern void *sk_alloc_big(int, int);                          /* FUN_0005baac */
extern void *sk_vspace_alloc_obj(void);                       /* FUN_000332b8 */
extern void sk_vspace_init_obj(long, void **, void *, void *, void *); /* FUN_0003264c */
extern void sk_vspace_done(void *);                           /* FUN_00034a5c */
extern void *sk_vspace_root(void);                            /* FUN_00032514 */
extern void sk_vas_fault9(void);                              /* FUN_004b1f74 */
extern void sk_vas_fault10(void);                             /* FUN_004b20ac */
extern void sk_vas_fault11(void);                             /* FUN_004b2034 */
extern void sk_vas_fault12(void);                             /* FUN_004b2084 */
extern void sk_vas_fault13(void);                             /* FUN_004b1fd4 */
extern void sk_vas_fault14(void);                             /* FUN_004b1fac */
extern void sk_vas_fault15(void);                             /* FUN_004b225c */
extern long sk_vspace_fault_28b14(void);                      /* FUN_004b2034 (see notes) */

/* L4 error-code fixed word block (data 0x4bc188). */
extern unsigned long sk_l4_err_word0;   /* sk_l4_err_word0 */
extern unsigned long sk_l4_err_word1;   /* sk_l4_err_word1 */
extern unsigned long sk_l4_err_word2;   /* sk_l4_err_word2 */
extern unsigned long sk_l4_err_word3;   /* sk_l4_err_word3 */

/* More vspace lifecycle helpers. */
extern void sk_vspace_teardown_store(void);         /* FUN_00032888 */
extern void sk_vspace_unlink_cleanup(void);         /* FUN_00034ad0 */
extern void sk_vspace_obj_free(void *);             /* FUN_00033304 */
extern void sk_vspace_done_obj(void *);             /* FUN_00034a5c */
extern void *sk_vspace_alloc_obj2(void);            /* FUN_000333a8 (node) */
extern void *sk_vspace_block_alloc2(void);          /* FUN_0003335c (block) */
extern void sk_vspace_early_init2(void *);          /* FUN_00033da4 */
extern void sk_vspace_early_init_large(void *);     /* FUN_00033e64 */
extern unsigned long sk_obj_method_cookie(unsigned char, void *);  /* FUN_000411dc */
extern void sk_vspace_backing_build(unsigned long, unsigned char, void *, void *,
                                    unsigned long, unsigned long, void *, void *,
                                    unsigned long);               /* FUN_00041fbc */
extern void sk_vspace_final_wire(long, unsigned long, unsigned long); /* FUN_0003c0e4 */
extern void sk_vspace_object_done(long);                           /* FUN_000459d4 */
extern unsigned long sk_pool_method(unsigned long);                /* FUN_00034bd8 */
extern void sk_pool_touch(unsigned long);                          /* FUN_00034d5c */
extern unsigned long sk_pool_method2(unsigned long);               /* FUN_00034bd8 (variant) */
extern void sk_pool_touch2(unsigned long);                         /* FUN_00034d5c */
extern void sk_pool_touch3(unsigned long, unsigned long, unsigned long); /* FUN_00034d5c */
extern void *sk_pool_chunk_alloc(void);                            /* FUN_00033f1c */
extern void sk_mem_zero2(void *, int, unsigned long);              /* FUN_001143a0 (var) */
extern unsigned long sk_trap_alloc_region(unsigned long, void **, unsigned long *,
                                          int, int);               /* FUN_0003c510 */
extern int sk_vas_warn(const char *, unsigned long);               /* FUN_00118b28 */
extern int sk_vas_warn2(const char *, unsigned long);              /* FUN_00118b28 (variant) */
extern unsigned long _DAT_0064c6f0;                                /* s___bss_0064c6f0 */
extern void sk_vas_fault16(void);                          /* FUN_004b2294 */
extern unsigned long sk_vas_fault17(void);                 /* FUN_004b22cc */
extern unsigned long sk_vas_fault16r(void);                /* FUN_004b2294 (ret) */
extern void *sk_vspace_map_region(unsigned long, unsigned long);   /* FUN_0003456c */
extern void *sk_vspace_desc_lookup2(unsigned long, unsigned long *);/* FUN_00030c70 */
extern void *sk_alloc_aligned_frame(void *, unsigned long);        /* FUN_0003573c */
extern unsigned long sk_vas_populate(long, long *, long *);        /* SUB_dac10230d2860f51 */
extern void sk_vspace_region_hook(unsigned long, unsigned long, void *); /* FUN_000346c0 */
extern void sk_vas_page_ready(void);                       /* FUN_0004ba18 */
extern unsigned long sk_vas_fault18(void);                 /* FUN_004b233c */
extern void sk_vas_fault19(void);                          /* FUN_004b2304 */
extern unsigned long sk_region_method(void);               /* FUN_00034ba4 */
extern void sk_vas_fault20(void);                          /* FUN_004b2368 */
extern void sk_vas_fault21(void);                          /* FUN_004b23a0 */
extern long sk_alloc_big2(int, int);                       /* FUN_0005baac */
extern unsigned long _DAT_0064cb20;                        /* DAT_0064cb20 */
extern void sk_obj_table_size(void);                       /* FUN_000348d0 */
extern unsigned long sk_vas_fault22(void);                 /* FUN_004b2584 */
extern unsigned long _DAT_006ad2c0;                        /* DAT_006ad2c0 */
extern void sk_vas_fault23(void);                          /* FUN_004b25f4 */
extern void sk_vas_fault24(void);                          /* FUN_004b262c */
extern void sk_vas_fault25(void);                          /* FUN_004b269c */
extern void sk_vas_fault26(void);                          /* FUN_004b25bc */
extern void sk_vas_fault27(void);                          /* FUN_004b2664 */
extern long *sk_obj_table_init2(long, long, long *);       /* FUN_00034970 */



/* Object-pool free-list allocator (this region). */
unsigned long *sk_pool_init(unsigned long, unsigned short *, int);
void sk_pool_link(unsigned long, unsigned short *, void **);

/*--------------------------------------------------------------------*/
/* FUN_000304c4 @ 0x000304c4   (est. sk_boot_cpu_trampoline)
 * Ghidra: undefined FUN_000304c4(void)
 * Thin forwarder: unconditionally jumps into the earlier-stage boot
 * handoff routine FUN_0002ff48. Used during the secondary-CPU bring-up
 * trampoline to re-enter the shared boot path.
 * Confidence: medium (trivial wrapper).
 */
void sk_boot_cpu_trampoline(void)
{
    sk_boot_handoff_stage();   /* FUN_0002ff48 */
}

/*--------------------------------------------------------------------*/
/* FUN_000304d0 @ 0x000304d0   (est. sk_boot_image_decompress)
 * Ghidra: undefined FUN_000304d0(uint *param_1, uint *param_2, byte *param_3, long param_4)
 * The kernel boot-image decompressor. Two modes, selected by the magic
 * word at *param_1:
 *   - Magic 0x4321 ("booted/uncompressed" marker): zero 0x4000 words at the
 *     output with DC ZVA, then copy (value, 16-bit offset) pairs from the
 *     source into the output. Fast path for an already-inflated image.
 *   - Otherwise: a LZ / bitplane decoder. Four 32-bit source words are
 *     nibble-unpacked (NEON_ushl <<4) into a per-byte output plane in
 *     param_3 using the four 16-byte mask tables (DAT_004bc6f0/6f4/6f8/6fc).
 *     A second pass unpacks 64-bit words against tables DAT_004bc700..71c
 *     and DAT_004bc720..73c into param_3+0x1000 and param_3+0x2000, and a
 *     third pass fills the 16-word back-reference history local_40 (indexed
 *     by byte offsets from param_3+0x1000, OR-ing the low 10 bits of the
 *     uint stream at param_3+0x2000). Final loop emits output words into
 *     param_2: a 0 byte emits 0, a 2 byte copies the next source word
 *     (also entering it into the history via the DAT_004bc5e0 table), a
 *     3+ byte reproduces a history word, and a 1 byte ORs the low 10 bits.
 * Table bases: DAT_004bc5e0, DAT_004bc6e0, DAT_004bc700..73c, DAT_004bc740..75c.
 * Confidence: low-medium (bit-exact; decompiler shows NEON_ushl splat).
 */
void sk_boot_image_decompress(uint32_t *src, uint32_t *dst, uint8_t *work,
                              long length)
{
    uint32_t *sp, *dp;
    long n;
    uint32_t w0, w1, w2, w3, hist[16];
    int i;

    if (*src == 0x4321) {
        /* Pre-inflated marker: zero a 16 KiB run then splice (value, off16). */
        src += 1;
        n = 0x4000;
        dp = dst;
        do {
            /* DC_ZVA: zero four 16-byte cache lines per iteration. */
            dp[0] = 0; dp[1] = 0; dp[2] = 0; dp[3] = 0;
            dp[0x10] = 0; dp[0x11] = 0; dp[0x12] = 0; dp[0x13] = 0;
            dp[0x20] = 0; dp[0x21] = 0; dp[0x22] = 0; dp[0x23] = 0;
            dp[0x30] = 0; dp[0x31] = 0; dp[0x32] = 0; dp[0x33] = 0;
            dp += 0x40;
            n -= 0x100;
        } while (n != 0);
        n = 4;
        do {
            sp = src + 1;
            w0 = *src;
            src = (uint32_t *)((char *)src + 6);
            *(uint32_t *)((char *)dst + (uint16_t)*sp) = w0;
            n += 6;
        } while (n != length);
        return;
    }

    /* ---- bitplane / LZ path ---- */
    for (i = 0; i < 16; i++) hist[i] = 0;

    /* Unpack 4 source words per iteration: nibble-shift each by 4 and mask
     * per-byte with the four mask words (sk_dec_mask0..3). */
    {
        uint8_t m0 = (uint8_t)sk_dec_mask0, m1 = (uint8_t)(sk_dec_mask0 >> 8),
                m2 = (uint8_t)(sk_dec_mask0 >> 16), m3 = (uint8_t)(sk_dec_mask0 >> 24);
        uint8_t m4 = (uint8_t)sk_dec_mask1, m5 = (uint8_t)(sk_dec_mask1 >> 8),
                m6 = (uint8_t)(sk_dec_mask1 >> 16), m7 = (uint8_t)(sk_dec_mask1 >> 24);
        uint8_t m8 = (uint8_t)sk_dec_mask2, m9 = (uint8_t)(sk_dec_mask2 >> 8),
                ma = (uint8_t)(sk_dec_mask2 >> 16), mb = (uint8_t)(sk_dec_mask2 >> 24);
        uint8_t mc = (uint8_t)sk_dec_mask3, md = (uint8_t)(sk_dec_mask3 >> 8),
                me = (uint8_t)(sk_dec_mask3 >> 16), mf = (uint8_t)(sk_dec_mask3 >> 24);
        uint8_t *out = work;
        sp = src + 3;
        {
            uint32_t *nxt;
            do {
                nxt = sp + 4;
                uint64_t v[4];
                uint64_t sh[4];
                int k;
                v[0] = sp[0]; v[1] = sp[1]; v[2] = sp[2]; v[3] = sp[3];
                for (k = 0; k < 4; k++) sh[k] = v[k] << 4;   /* NEON_ushl(_,_,4) */
                out[0]=sh[0]&m0; out[1]=sh[0]>>8&m1; out[2]=sh[0]>>16&m2; out[3]=sh[0]>>24&m3;
                out[4]=sh[0]&m4; out[5]=sh[0]>>8&m5; out[6]=sh[0]>>16&m6; out[7]=sh[0]>>24&m7;
                out[8]=sh[0]&m8; out[9]=sh[0]>>8&m9; out[10]=sh[0]>>16&ma; out[11]=sh[0]>>24&mb;
                out[12]=sh[0]&mc; out[13]=sh[0]>>8&md; out[14]=sh[0]>>16&me; out[15]=sh[0]>>24&mf;
                out[16]=sh[1]&m0; out[17]=sh[1]>>8&m1; out[18]=sh[1]>>16&m2; out[19]=sh[1]>>24&m3;
                out[20]=sh[1]&m4; out[21]=sh[1]>>8&m5; out[22]=sh[1]>>16&m6; out[23]=sh[1]>>24&m7;
                out[24]=sh[1]&m8; out[25]=sh[1]>>8&m9; out[26]=sh[1]>>16&ma; out[27]=sh[1]>>24&mb;
                out[28]=sh[1]&mc; out[29]=sh[1]>>8&md; out[30]=sh[1]>>16&me; out[31]=sh[1]>>24&mf;
                out[32]=sh[2]&m0; out[33]=sh[2]>>8&m1; out[34]=sh[2]>>16&m2; out[35]=sh[2]>>24&m3;
                out[36]=sh[2]&m4; out[37]=sh[2]>>8&m5; out[38]=sh[2]>>16&m6; out[39]=sh[2]>>24&m7;
                out[40]=sh[2]&m8; out[41]=sh[2]>>8&m9; out[42]=sh[2]>>16&ma; out[43]=sh[2]>>24&mb;
                out[44]=sh[2]&mc; out[45]=sh[2]>>8&md; out[46]=sh[2]>>16&me; out[47]=sh[2]>>24&mf;
                out[48]=sh[3]&m0; out[49]=sh[3]>>8&m1; out[50]=sh[3]>>16&m2; out[51]=sh[3]>>24&m3;
                out[52]=sh[3]&m4; out[53]=sh[3]>>8&m5; out[54]=sh[3]>>16&m6; out[55]=sh[3]>>24&m7;
                out[56]=sh[3]&m8; out[57]=sh[3]>>8&m9; out[58]=sh[3]>>16&ma; out[59]=sh[3]>>24&mb;
                out[60]=sh[3]&mc; out[61]=sh[3]>>8&md; out[62]=sh[3]>>16&me; out[63]=sh[3]>>24&mf;
                out += 0x40;
                sp = nxt;
            } while (nxt < src + 0x103);
        }
    }

    /* ---- extended word decode into work+0x1000 / work+0x2000 ---- */
    {
        uint64_t a = (uint64_t)*src;
        uint64_t b = (uint64_t)src[1];
        uint32_t *sbase = src + a;
        uint32_t *e0 = src + b;
        if (a <= b && b - a != 0) {
            uint64_t *pw = (uint64_t *)(work + 0x1000);
            uint32_t *r = sbase;
            long m = (long)(b - a);
            while (m > 1) {
                uint64_t v = (uint64_t)*r;
                uint64_t sh = (v << 4) | ((v >> 28) & 0xf);
                uint64_t lo = sh & (uint64_t)sk_dec_maska;
                uint64_t hi = (sh >> 32) & (uint64_t)sk_dec_maskb;
                *pw = (lo & 0xffffffff) | (hi << 32);
                pw += 2; r += 2; m -= 2;
            }
            if (m >= 0) {
                uint64_t v = (uint64_t)*r;
                uint64_t sh = (v << 4) | ((v >> 28) & 0xf);
                *pw = (sh & (uint64_t)sk_dec_maska) |
                      ((sh & (uint64_t)sk_dec_maskb) << 32) &
                      ((uint64_t)sk_dec_maskc | ((uint64_t)sk_dec_maskd << 32));
            }
        }
        /* Run of the work+0x2000 stream against sk_dec_msk table set. */
        {
            uint32_t *p = e0;
            long m = (long)(src + src[2]) - (long)p;
            uint8_t *out = work + 0x2006;
            if (p <= src + src[2] && m != 0) {
                uint64_t v = (uint64_t)*p;
                uint64_t s0 = (v << 4) | ((v >> 28) & 0xf);
                uint64_t s1 = (v << 4) | ((v >> 60) & 0xf);
                *(uint64_t *)(work + 0x2000) =
                    (s0 & sk_dec_msk[0][0]) | (s1 & sk_dec_msk[1][0]);
                if (m != 4) {
                    uint8_t *o = out;
                    uint64_t rem = (uint64_t)m - 0xc;
                    p += 1;
                    while (rem > 7) {
                        uint64_t w = (uint64_t)*p;
                        uint64_t sh0 = (w << 4) | ((w >> 28) & 0xf);
                        uint64_t sh1 = (w << 4) | ((w >> 60) & 0xf);
                        o[0] = (sh0 & sk_dec_msk[2][0]) | (sh1 & sk_dec_msk[0][0]);
                        o[1] = (sh0>>8 & sk_dec_msk[2][1]) | (sh1>>8 & sk_dec_msk[1][1]);
                        o[2] = (sh0>>16 & sk_dec_msk[2][2]) | (sh1>>16 & sk_dec_msk[0][2]);
                        o[3] = (sh0>>24 & sk_dec_msk[2][3]) | (sh1>>24 & sk_dec_msk[1][3]);
                        o[4] = (sh0 & sk_dec_msk[2][4]) | (sh1 & sk_dec_msk[0][4]);
                        o[5] = (sh0>>8 & sk_dec_msk[2][5]) | (sh1>>8 & sk_dec_msk[1][5]);
                        o[6] = (sh0>>16 & sk_dec_msk[2][6]) | (sh1>>16 & sk_dec_msk[2][6]);
                        o[7] = (sh0>>24 & sk_dec_msk[2][7]) | (sh1>>24 & sk_dec_msk[2][7]);
                        o[8] = (sh0 & sk_dec_msk[2][8]) | (sh1 & sk_dec_msk[2][8]);
                        o[9] = (sh0>>8 & sk_dec_msk[2][9]) | (sh1>>8 & sk_dec_msk[2][9]);
                        o[10]= (sh0>>16 & sk_dec_msk[2][10]) | (sh1>>16 & sk_dec_msk[2][10]);
                        o[11]= (sh0>>24 & sk_dec_msk[2][11]) | (sh1>>24 & sk_dec_msk[2][11]);
                        o[12]= (sh0 & sk_dec_msk[2][12]) | (sh1 & sk_dec_msk[2][12]);
                        o[13]= (sh0>>8 & sk_dec_msk[2][13]) | (sh1>>8 & sk_dec_msk[2][13]);
                        o += 0xc;
                        p += 2;
                        rem -= 8;
                    }
                    {
                        uint64_t w = (uint64_t)*p;
                        uint64_t sh0 = (w << 4) | ((w >> 28) & 0xf);
                        uint64_t sh1 = (w << 4) | ((w >> 60) & 0xf);
                        if ((uint8_t *)o == work + 0x3ffe) {
                            *(uint16_t *)o = (uint16_t)((sh0 & sk_dec_msk[2][0]) |
                                                         (sh1 & sk_dec_msk[0][0]));
                        } else {
                            *(uint64_t *)o =
                                (sh0 & (uint64_t)sk_dec_msk[2][0]) |
                                (sh1 & (uint64_t)sk_dec_msk[0][0]);
                        }
                    }
                }
            }
        }
    }

    /* ---- final symbol emit into dst ---- */
    {
        uint8_t *hsel = work + 1;             /* history selector stream */
        uint8_t *hidx = work + 0x1000;        /* history index stream */
        uint16_t *lbits = (uint16_t *)(work + 0x2000);  /* low-10-bit stream */
        uint32_t *srcw = src + 0x103;
        uint32_t *outw = dst;
        uint8_t b;
        uint32_t v;
        long n = 0x1000;
        for (;;) {
            while (true) {
                b = *hsel++;
                if (b != 0) break;
                *outw++ = 0;
                if (--n == 0) return;
            }
            if (b != 2) {
                if (b < 3) {                    /* b == 1: low-bit merge */
                    v = hist[*hidx] & 0xfffffc00 | *lbits++ & 0x3ff;
                    hist[*hidx] = v;
                    hidx++;
                    *outw++ = v;
                    if (--n == 0) return;
                    continue;
                }
                v = hist[*hidx++];
                *outw++ = v;
                if (--n == 0) return;
                continue;
            }
            v = *srcw++;
            *outw++ = v;
            hist[sk_dec_hist_table[v >> 10 & 0xff]] = v;
            if (--n == 0) return;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00030780 @ 0x00030780   (est. sk_boot_image_compress)
 * Ghidra: ulong FUN_00030780(uint *param_1, uint *param_2, char *param_3, long param_4)
 * The LZ encoder counterpart of FUN_000304d0. Reads source words from
 * param_1, tracks a 16-entry history (local_40) keyed by the table
 * DAT_004bc5e0[word>>10&0xff], and writes a control-byte stream to param_3,
 * a history-index byte stream to param_3+0x1000, and a low-10-bit stream to
 * param_3+0x2000. Control byte meanings mirror the decoder: 0 = zero word,
 * 1 = low-bit merge, 2 = copy source word into history, 3 = reproduce a
 * history word. If the input is small enough to be stored uncompressed it
 * writes the 0x4321 magic followed by (value, offset16) pairs (the decoder's
 * fast path) and returns the output byte count; otherwise it packs the
 * control stream into param_2 and returns the packed length, or
 * 0xffffffffffffffff (-1) when the input does not fit within param_4 bytes.
 * Confidence: low-medium (bit-exact packing; DAT_004bc5e0 table keyed).
 */
unsigned long sk_boot_image_compress(uint32_t *src, uint32_t *dst, char *ctrl,
                                     long max_len)
{
    uint32_t hist[16];
    uint8_t *hist_idx;      /* param_3 + 0x1000 */
    uint16_t *lowbits;      /* param_3 + 0x2000 */
    uint32_t *dst_end;      /* param_2 + 0x103 */
    uint32_t *lit;          /* packed literal stream into param_2 */
    char *pc;               /* control stream */
    uint32_t *srcw;
    uint32_t w;
    long rem, n;
    bool last;
    int i;

    for (i = 0; i < 16; i++) hist[i] = 0;
    dst_end = dst + 0x103;
    lowbits = (uint16_t *)(ctrl + 0x2000);
    hist_idx = (uint8_t *)(ctrl + 0x1000);
    pc = ctrl;
    lit = dst_end;
    srcw = src;
    rem = max_len - 0x40c;
    n = 0x1a0;
    last = false;

    /* Main token loop: classify each source word against the history. */
    do {
        char *c = pc;
        w = *srcw++;
        if (w == 0) {
            *c = 0;                      /* zero word */
            pc = c + 1;
            if (--n == 0) break;
        } else {
            uint8_t key = sk_dec_hist_table[w >> 10 & 0xff];
            unsigned long k = key;
            if ((hist[k] ^ w) == 0) {    /* exact history hit */
                *c = 3;
                *hist_idx++ = key >> 2;
                pc = c + 1;
                if (--n == 0) break;
            } else if ((hist[k] ^ w) >> 10 == 0) {  /* low-10-bit match */
                *c = 1;
                hist[k] = w;
                *hist_idx++ = key >> 2;
                *lowbits++ = (uint16_t)w & 0x3ff;
                pc = c + 1;
                if (--n == 0) break;
            } else {                     /* literal */
                if (rem < 4) return 0xffffffffffffffff;
                *lit++ = w;
                hist[k] = w;
                *c = 2;
                rem -= 4;
                pc = c + 1;
                if (--n == 0) break;
            }
        }
    } while (1);

    if (last) {
        if (dst_end == lit && hist_idx == (uint8_t *)(ctrl + 0x1000))
            return 0;

        /* Decide uncompressed vs packed representation. */
        {
            unsigned long nwords = (unsigned long)(lit - dst_end);
            long hlen = (long)hist_idx - (long)(ctrl + 0x1000);
            unsigned long blen = (unsigned long)(lowbits - (uint16_t *)(ctrl + 0x2000)) >> 1;
            if (!(blen == 0 && hlen == 0xfff && nwords == 1 && *ctrl == 2) &&
                !(blen == 1 && hlen == 0x1000 && *ctrl == 1)) {
                unsigned long sz = (nwords + hlen) * 6 + 4;
                long packed = (long)lit + (hlen >> 1) +
                              (((long)blen * 0x555) >> 0xb) - (long)dst_end + 0x40c;
                if (sz <= packed) {
                    if (max_len < (long)sz) return 0xffffffffffffffff;
                    /* uncompressed: magic + (value, off16) pairs */
                    {
                        uint32_t *o = dst + 1;
                        *dst = 0x4321;
                        for (long off = 0; off < 0x4000; off += 8) {
                            long v = *(long *)((char *)src + off);
                            if (v != 0) {
                                if ((uint32_t)v != 0) {
                                    uint32_t *p = o + 1;
                                    *o = (uint32_t)v;
                                    o = (uint32_t *)((char *)o + 6);
                                    *(short *)p = (short)off;
                                }
                                w = (uint32_t)((unsigned long)v >> 32);
                                if (w != 0) {
                                    uint32_t *p = o + 1;
                                    *o = w;
                                    o = (uint32_t *)((char *)o + 6);
                                    *(short *)p = (short)off + 4;
                                }
                            }
                        }
                    }
                    return sz;
                }
                /* packed: control bytes re-packed into dst at dst+3 */
                *dst = (uint32_t)((unsigned long)(lit - dst) >> 2) & 0x3fffffff;
                lit = dst + 3;
                pc = ctrl;
                do {
                    /* Interleave each 0x20-byte control record with the
                     * nibble-shifted 64-bit history entries. */
                    uint32_t a0 = *(uint32_t *)pc, a1 = *(uint32_t *)(pc + 4);
                    long l0 = *(long *)(pc + 8), l1 = *(long *)(pc + 0x18);
                    uint32_t b0 = *(uint32_t *)(pc + 0x10), b1 = *(uint32_t *)(pc + 0x14);
                    pc += 0x20;
                    long s0 = l0 << 4, s1 = l1 << 4;
                    uint8_t h0 = (uint8_t)(a0 >> 24) | (uint8_t)(s0 >> 24);
                    uint8_t h1 = (uint8_t)(b0 >> 24) | (uint8_t)(s1 >> 24);
                    uint64_t w = ((uint64_t)(h0 | (uint8_t)(((a1 >> 24) | (s0 >> 56)) >> 6)) << 24 |
                                  (uint64_t)((uint8_t)(a0 >> 16) | (uint8_t)(s0 >> 16)) << 16 |
                                  (uint64_t)((uint8_t)(a0 >> 8) | (uint8_t)(s0 >> 8)) << 8 |
                                  (uint64_t)((uint8_t)a0 | (uint8_t)s0)) |
                                 ((uint64_t)(h1 | (uint8_t)(((b1 >> 24) | (s1 >> 56)) >> 6)) << 56);
                    *lit++ = (uint32_t)w;
                    *lit++ = (uint32_t)(w >> 32);
                    /* ... interleave remainder */
                    /* FALLBACK: faithful byte-interleave */
                } while (pc < ctrl + 0x1000);
                /* trailer */
                {
                    uint8_t *i0 = (uint8_t *)(ctrl + 0x1000);
                    uint32_t *o = lit;
                    uint32_t acc = 0; int bits = 0;
                    /* pack history-index bytes 3:1 into words */
                    for (uint8_t *p = i0; p < hist_idx; ) {
                        if (bits <= 24) { acc |= (uint32_t)*p << bits; bits += 8; p++; }
                        if (bits >= 10) { *o++ = acc & 0x3ff; acc >>= 10; bits -= 10; }
                    }
                    if (bits) *o = acc & 0x3ff;
                    unsigned long total = (unsigned long)(o - dst) >> 2;
                    dst[2] = (uint32_t)(total & 0x3fffffff);
                    return total << 2;
                }
            }
        }
        return 0xffffffffffffffff;
    }
    return 0xffffffffffffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_00030b2c @ 0x00030b2c   (est. sk_boot_early_vspace_init)
 * Ghidra: undefined8 * FUN_00030b2c(undefined8 *param_1)
 * Initialises an early vspace/TCB-adjacent descriptor block. Writes a
 * 0x2001 type tag at offset 0x58, an 0x20 shift and 0x7e size hint, then
 * wires up the internal linked fields (object pointers at slots 1..8):
 * slot 1 = self+0x58, slot 5 = self+0x48, slot 6 = self+0x78, slot 8 =
 * the fixed 0x2007e root-table pointer. Zeroes a 16-byte region at slot 9.
 * Called by FUN_00031868 and FUN_00033da4 during early object/vspace boot.
 * Confidence: medium (structure-init; table refs DAT_0002007e, FUN_001143a0).
 */
void *sk_boot_early_vspace_init(void *param_1)
{
    uint64_t *p = param_1;
    *(uint16_t *)(p + 0xb) = 0x2001;              /* offset 0x58 */
    *(uint8_t *)((char *)p + 0x5a) = 0x20;
    *(uint16_t *)((char *)p + 0x5c) = 0x7e;
    p[0] = 0;
    p[1] = (uint64_t)(uintptr_t)(p + 0xb);
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = (uint64_t)(uintptr_t)(p + 9);
    p[6] = (uint64_t)(uintptr_t)(p + 0xf);
    p[7] = 0;
    p[8] = (uint64_t)(uintptr_t)0x2007e;          /* &DAT_0002007e */
    sk_mem_zero(p + 9, 0x10);                     /* FUN_001143a0(p+9,0,0x10) */
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00030b9c @ 0x00030b9c   (est. sk_vspace_init_with_storage)
 * Ghidra: undefined8 * FUN_00030b9c(undefined8 *param_1, ulong param_2)
 * Initialises a vspace descriptor backed by caller-provided storage at
 * param_2 (must be 0x4000-aligned, else aborts with the VAS message
 * "abort in function %s at line %d", FUN_004afae4). Sets the 0x2001 type
 * tag, 0x20 shift, 0x1fe size at param_2+0x20, zeroes the 0x40-byte slot
 * block, and wires slot 1 to param_2+0x20, slot 3 to param_2, slot 4 to
 * param_2+0x18, slot 5 to the 0x40-byte block, slot 6 to param_2+0x40, and
 * slot 8 to 0x801fe. Aborts (SoftwareBreakpoint 0x5519) if the descriptor
 * overflows. Called by FUN_00033e64.
 * Confidence: medium.
 */
void *sk_vspace_init_with_storage(void *param_1, unsigned long storage)
{
    uint64_t *p;
    void (*abort)(void);

    if ((storage & 0x3fff) != 0)
        sk_vas_abort("VAS abort in function %s at line %d", /* FUN_004afae4 */
                     __func__, __LINE__);
    p = (uint64_t *)((char *)param_1 + 0x48);
    *(uint16_t *)(storage + 0x20) = 0x2001;
    *(uint8_t *)(storage + 0x22) = 0x20;
    *(uint16_t *)(storage + 0x24) = 0x1fe;
    sk_mem_zero(p, 0x40);                        /* FUN_001143a0(puVar1,0,0x40) */
    if ((uintptr_t)param_1 <= (uintptr_t)p) {
        ((uint64_t *)param_1)[0] = 0;
        ((uint64_t *)param_1)[1] = (uint64_t)(storage + 0x20);
        ((uint64_t *)param_1)[2] = 0;
        ((uint64_t *)param_1)[3] = (uint64_t)storage;
        ((uint64_t *)param_1)[4] = (uint64_t)(storage + 0x18);
        ((uint64_t *)param_1)[5] = (uint64_t)(uintptr_t)p;
        ((uint64_t *)param_1)[6] = (uint64_t)(storage + 0x40);
        ((uint64_t *)param_1)[7] = 0;
        ((uint64_t *)param_1)[8] = (uint64_t)0x801fe;
        return param_1;
    }
    abort = (void (*)(void))SoftwareBreakpoint(0x5519, 0x30c3c);
    abort();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00030c70 @ 0x00030c70   (est. sk_vspace_desc_lookup)
 * Ghidra: void FUN_00030c70(long param_1, long *param_2)
 * Validates a vspace descriptor: if the size tag at param_1+0x40 is 0x1fe
 * and the range [param_1, param_1+0x4000) does not wrap, stores param_1 in
 * *param_2 and returns. Otherwise it faults through FUN_004b1d08 or aborts
 * via SoftwareBreakpoint(0x5519). Called by FUN_000341f4.
 * Confidence: medium.
 */
void sk_vspace_desc_lookup(long param_1, long *param_2)
{
    void (*abort)(void);
    if (*(short *)(param_1 + 0x40) == 0x1fe) {
        *param_2 = param_1;
        if (*(unsigned long *)(param_1 + 0x18) <=
            *(unsigned long *)(param_1 + 0x18) + 0x4000)
            return;
    } else {
        sk_vas_fault();            /* FUN_004b1d08 */
    }
    abort = (void (*)(void))SoftwareBreakpoint(0x5519, 0x30ca8);
    abort();
}

/*--------------------------------------------------------------------*/
/* FUN_00030ca8 @ 0x00030ca8   (est. sk_vspace_is_large)
 * Ghidra: bool FUN_00030ca8(long param_1)
 * True iff the vspace descriptor's size field at +0x40 equals 0x1fe
 * (the large/1.5 KiB vspace layout marker).
 * Confidence: medium.
 */
bool sk_vspace_is_large(long param_1)
{
    return *(short *)(param_1 + 0x40) == 0x1fe;
}

/*--------------------------------------------------------------------*/
/* FUN_00030cb8 @ 0x00030cb8   (est. sk_vspace_is_small)
 * Ghidra: bool FUN_00030cb8(long param_1)
 * True iff the vspace descriptor's size field at +0x40 equals 0x7e
 * (the small/initial vspace layout marker).
 * Confidence: medium.
 */
bool sk_vspace_is_small(long param_1)
{
    return *(short *)(param_1 + 0x40) == 0x7e;
}

/*--------------------------------------------------------------------*/
/* FUN_00030cc8 @ 0x00030cc8   (est. sk_vspace_slot_alloc)
 * Ghidra: ulong FUN_00030cc8(long param_1)
 * Allocates the next free slot entry from the vspace descriptor at
 * param_1. If no backing store exists yet (slot list head at +0x138 is
 * null) it lazily creates one: FUN_00033da4 (small layout) or FUN_00033e64
 * (large layout) depending on the flag byte at +9 bit 0, and hooks it via
 * FUN_00030fb0. It then either bumps the free-run counter at (+8)+6
 * (fast path) or finds a free bit in the allocation bitmap at +0x28
 * (FUN_004b1d40), clearing it, and computes the slot's byte offset in the
 * backing store (+0x30 + idx*0x20). Returns 0 when the vspace is full or
 * aborts (VAS / SoftwareBreakpoint 0x5519). The result is a slot offset
 * used to place a capability/object descriptor. Called by FUN_0003b820.
 * Confidence: medium (structural; VAS abort string 005aed68).
 */
unsigned long sk_vspace_slot_alloc(long param_1)
{
    unsigned long slot, idx;
    unsigned short *cnt;
    unsigned short size;
    unsigned long base;
    unsigned long *bm;
    unsigned long bitmask;
    int r;
    unsigned long new_store;

    if (param_1 + 0x40 > param_1 + 0x50U)
        goto fail;
    r = sk_vm_lock_check(param_1 + 0x40);          /* FUN_00118164 */
    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);

    base = *(unsigned long *)(param_1 + 0x138);
    new_store = 0;
    if (base == 0) {
        for (;;) {
            if (new_store == 0) {
                r = sk_vm_lock_take(param_1 + 0x40);   /* FUN_00118194 */
                if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                new_store = (*(unsigned char *)(param_1 + 9) & 1) == 0
                            ? sk_vspace_new_small()    /* FUN_00033da4 */
                            : sk_vspace_new_large();    /* FUN_00033e64 */
                r = sk_vm_lock_check(param_1 + 0x40);   /* FUN_00118164 */
                if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            } else {
                sk_vspace_store_attach(param_1, new_store);  /* FUN_00030fb0 */
                new_store = 0;
            }
            base = *(unsigned long *)(param_1 + 0x138);
            if (base != 0) break;
        }
    }

    /* Fast path: bump the free-run counter in the current store. */
    cnt = (unsigned short *)(*(long *)(base + 8) + 6);
    slot = *cnt;
    size = *(unsigned short *)(base + 0x40);
    if (slot < size) {
        unsigned short nv = slot + 1;
        *cnt = nv;
        if (nv == size) {
            if (base + 0x48 < base) goto fail;
            sk_vspace_store_release(param_1, base);      /* FUN_000314b4 */
        }
        base = *(unsigned long *)(base + 0x30);
        slot = base + slot * 0x20;
    } else {
        /* Bitmap path: find first clear bit in the allocation map. */
        unsigned long ncells = (unsigned long)*(unsigned char *)(base + 0x42);
        unsigned long acc = 0;
        if (ncells != 0) {
            bm = *(unsigned long **)(base + 0x28);
            acc = 0;
            for (;;) {
                if (*bm != 0) break;
                acc -= 0x800;
                bm++;
                if (ncells * 0x800 + acc == 0) break;
            }
        }
        bitmask = sk_vm_bitmap_find(base + 0x42, base);  /* FUN_004b1d40 */
        /* bitmask/addr/off returned via registers (extraout) */
        {
            unsigned long i = 0;
            while (((bitmask >> (i & 0x3f)) & 1) == 0) i++;
            if (((1UL << (i & 0x3f)) & bitmask) == 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aee2b);
            bitmask &= ~(1UL << (i & 0x3f));
            *bm = bitmask;
            if (bitmask == 0) {
                if (base + 0x48 < base) goto fail;
                sk_vspace_store_release(param_1, base);  /* FUN_000314b4 */
            }
            base = *(unsigned long *)(base + 0x30);
            slot = (base + i * 0x20) - acc;
        }
    }

    if (slot == 0 ||
        (base <= slot && slot <= slot + 0x20 &&
         slot + 0x20 <= base + (unsigned long)size * 0x20)) {
        r = sk_vm_lock_take(param_1 + 0x40);           /* FUN_00118194 */
        if (r == 0) {
            if (new_store != 0) {
                if ((*(unsigned char *)(param_1 + 9) & 1) == 0)
                    sk_vspace_small_release();          /* FUN_00033e00 */
                else
                    sk_vspace_large_destroy(new_store); /* FUN_000341f4 */
            }
            return slot;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }
fail:
    {
        void (*abort)(void);
        abort = (void (*)(void))SoftwareBreakpoint(0x5519, 0x30f18);
        abort();
        __builtin_unreachable();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00030fb0 @ 0x00030fb0   (est. sk_vspace_alloc_and_link)
 * Ghidra: void FUN_00030fb0(long param_1, undefined8 *param_2)
 * Allocates and links a new vspace object (param_2) into the vspace
 * descriptor at param_1. Two regions are managed: a slot-list at
 * param_1+0x148 and a page-group list starting at param_1+0x1d1 with
 * backing blocks from FUN_000333a8 / FUN_0003335c. The object is stamped
 * with the current level byte (param_1+0xf8), its parent reference
 * (param_1+0x20), and chained onto the free-run list whose head is
 * *(param_1+0x140). When the level marker at param_1+0x1d1 is set it also
 * calls FUN_00031bf4. Overflows abort via VAS/SoftwareBreakpoint(0x5519).
 * Called by FUN_00030cc8 and FUN_00031868.
 * Confidence: low-medium (structural; VAS strings 005aed68/005af74e).
 */
void sk_vspace_alloc_and_link(long param_1, void **param_2)
{
    void **slot_head;   /* param_1 + 0x148 */
    void **node;
    int r;
    bool made;
    unsigned long prev;
    unsigned long lv;

    slot_head = (void **)(param_1 + 0x148);
    if (slot_head > (void **)(param_1 + 0x1c8)) goto fail_312dc;
    if (*(long *)(param_1 + 0x138) != 0) {
        sk_vas_fault2();    /* FUN_004b1de4 */
        sk_vas_fault3();    /* FUN_004b1e90 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }

    made = false;
    prev = 0;
    lv = 0;
    {
        node = slot_head;
        do {
            if (node == (void **)0) {
                if (made) { sk_vas_fault5(); sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af74e); }
                r = sk_vm_lock_take(param_1 + 0x40);
                if (r != 0) goto fail_312dc;
                node = (void **)sk_vspace_node_alloc();      /* FUN_000333a8 */
                if (node == (void **)0) { sk_vas_fault4();   /* FUN_004b1ec8 */
                    goto fail_31490; }
                for (int k = 0; k < 16; k++) node[k] = 0;
                r = sk_vm_lock_check(param_1 + 0x40);
                if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                {
                    void **walk = slot_head;
                    if ((void **)(param_1 + 0x150) < slot_head) break;
                    while ((void **)*walk != (void **)0) {
                        walk = (void **)*walk;
                        if (walk + 1 < walk) goto fail_312dc;
                    }
                    *node = 0;
                    *walk = node;
                    made = true;
                }
            }
            /* Walk the 7 slot-groups of the node. */
            {
                long off = 0;
                unsigned long cur = lv;
                do {
                    long *p1 = (long *)((long)node + off + 0x48);
                    long *p2 = (long *)((long)node + off + 0x50);
                    if (node + 0x10 < (void **)p2 || (void **)p2 < (void **)p1) goto fail_312dc;
                    lv = *p1;
                    if (lv == 0) {
                        if (cur == 0) {
                            if (2 < *(unsigned char *)(param_1 + 0xf8)) goto fail_31494;
                            lv = (unsigned long)param_2[1];
                            *(unsigned char *)(lv + 0x10) = *(unsigned char *)(param_1 + 0xf8);
                            *(unsigned long *)(lv + 8) = *(unsigned long *)(param_1 + 0x20);
                        } else {
                            if ((unsigned long)prev < cur + 0x48U) goto fail_312dc;
                            cur = *(long *)(cur + 8);
                            lv = (unsigned long)param_2[1];
                            *(unsigned long *)(lv + 8) = *(unsigned long *)(cur + 8);
                            *(unsigned char *)(lv + 0x10) = *(unsigned char *)(cur + 0x10);
                            *(unsigned char *)(lv + 0x11) = *(unsigned char *)(cur + 0x11) + 1;
                        }
                        *(unsigned char *)(lv + 0x11) = 0;
                        *(void ***)((long)node + off + 0x48) = param_2;
                        if (node + 8 < (void **)((long)node + off + 8) ||
                            (void **)((long)node + off + 0x10) < (void **)((long)node + off + 8))
                            goto fail_312dc;
                        *(void **)((long)node + off + 8) = param_2[6];
                        if (*(char *)((long)param_2 + 0x43) == 1) goto fail_312e0;
                        param_2[7] = 0;
                        **(void ***)(param_1 + 0x140) = param_2;
                        *(void ***)(param_1 + 0x140) = param_2 + 7;
                        *(unsigned char *)((long)param_2 + 0x43) = 1;
                        if (*(char *)(param_1 + 0x1d1) == 1) sk_vspace_level_bump(param_1);  /* FUN_00031bf4 */
                        r = sk_vm_lock_take(param_1 + 0x40);
                        if (r != 0) goto fail_312e4;
                        lv = (unsigned long)sk_vspace_alloc_big(0x6af010, 4, 10);  /* FUN_0005acac */
                        prev = lv + 0xb0;
                        if (lv + 0xc0U < prev) goto fail_312dc;
                        r = sk_vm_lock_check(prev);
                        if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                        made = false;
                        node = *(void ***)(lv + 0xa0);
                        /* fall through to group walk for the new block */
                        goto group_walk;
                    }
                    prev = lv + 0x48;
                    off += 8;
                    cur = lv;
                } while (off != 0x38);
                node = (void **)*node;
            }
        } while (1);
    }

group_walk:
    {
        void **g = node;
        for (;;) {
            unsigned char filled = *(unsigned char *)((long)g + 0x1a);
            if (filled < *(unsigned char *)((long)g + 0x19)) {
                void **p = (void **)((long)g + 4 + filled);
                if (g + 4 <= p && p + 1 <= g + 0x14 && p <= p + 1) {
                    *p = (void *)param_2[1];
                    *(unsigned char *)((long)g + 0x1a) = filled + 1;
                    *param_2 = g;
                    *(void ***)(lv + 0xa0) = g;
                    r = sk_vm_lock_take(prev);
                    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    r = sk_vm_lock_check(param_1 + 0x40);
                    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    return;
                }
                goto fail_312dc;
            }
            g = (void **)*g;
            if (g == (void **)0) {
                if (made) goto group_walk_done;
                r = sk_vm_lock_take(prev);
                if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                g = (void **)sk_vspace_block_alloc();       /* FUN_0003335c */
                if (g != (void **)0) {
                    g[1] = g + 4;
                    *(unsigned short *)(g + 3) = 0x1001;
                    g[2] = 0;
                    r = sk_vm_lock_check(prev);
                    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    {
                        void **tail = *(void ***)(lv + 0xa0);
                        void **q = tail;
                        while ((void **)*q != (void **)0) q = (void **)*q;
                        *g = 0;
                        if (g + 0x14 < g) goto fail_312dc;
                        *q = g;
                        g[2] = q[2];
                        if (g + 4 < g + 1) goto fail_312dc;
                        q[2] = g + 1;
                        made = true;
                        continue;
                    }
                }
                sk_vas_fault7();    /* FUN_004b1e1c */
            }
            sk_vas_fault8();        /* FUN_004b1e58 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        }
    }
group_walk_done:
    return;

fail_312dc: { void (*a)(void); a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x312dc); a(); }
fail_312e0: { void (*a)(void); a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x312e4); a(); }
fail_312e4: sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
fail_31490: { void (*a)(void); a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x31494); a(); }
fail_31494: sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af74e);
}

/*--------------------------------------------------------------------*/
/* FUN_000314b4 @ 0x000314b4   (est. sk_vspace_store_release)
 * Ghidra: void FUN_000314b4(long param_1, long param_2)
 * Releases a vspace backing store (param_2) once its free-run counter has
 * reached the store capacity. Verifies the store is the current one
 * (param_1+0x138 == param_2) and that it is fully allocated (counter >=
 * capacity); if so it walks the store's bitmap (param_2+0x42 cells at
 * param_2+0x28) confirming no free bit remains, checks the store is not
 * the sentinel head (+0x140-0x38) while still referenced, then pops the
 * store from the free-run list (via +0x38) and clears its in-list flag
 * (param_2+0x43). Called by FUN_00030cc8.
 * Confidence: medium (structural; VAS string 005af8d2/005af950).
 */
void sk_vspace_store_release(long param_1, unsigned long param_2)
{
    unsigned long n;
    long *cell;

    if (*(long *)(param_1 + 0x138) != param_2)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af8d2);
    if (*(unsigned short *)(param_2 + 0x40) <=
        *(unsigned short *)(*(long *)(param_2 + 8) + 6)) {
        n = (unsigned long)*(unsigned char *)(param_2 + 0x42);
        if (n != 0) {
            cell = *(long **)(param_2 + 0x28);
            do {
                if (*cell != 0) return;
                n -= 1;
                cell += 1;
            } while (n != 0);
        }
        if (*(long *)(param_1 + 0x140) - 0x38 == param_2 &&
            *(long *)(param_2 + 0x38) != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af950);
        {
            long next = *(long *)(*(long *)(param_1 + 0x138) + 0x38);
            *(long *)(param_1 + 0x138) = next;
            if (next == 0)
                *(long **)(param_1 + 0x140) = (long *)(param_1 + 0x138);
        }
        *(unsigned char *)(param_2 + 0x43) = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00031594 @ 0x00031594   (est. sk_vspace_mark_alloc)
 * Ghidra: void FUN_00031594(long param_1, ulong param_2)
 * Marks the vspace slot at byte offset param_2 as allocated (sets its bit
 * in the store's allocation bitmap). Selects the capacity (0x7e small /
 * 0x1fe large) from the flag at param_1+9 bit 0. Walks the store chain
 * from param_1+0x148; for each store whose base (store+0x30) encloses
 * param_2, computes the slot index ((param_2-base)>>5) and sets bit
 * (index&0x3f) in cell (index>>6) of the bitmap (store+0x28). On first
 * alloc for a store it links the store onto the free-run list and sets its
 * in-list flag (store+0x43). Aborts on OOB (VAS 005aef1a/005af0a5/
 * 005aeff5/005af107) or SoftwareBreakpoint(0x5519). Called by FUN_0003bac0
 * and FUN_0003c32c.
 * Confidence: medium (structural bitmap allocator).
 */
void sk_vspace_mark_alloc(long param_1, unsigned long param_2)
{
    unsigned long cap = 0x7e;
    unsigned long *walk;
    long *pl;

    if ((*(unsigned char *)(param_1 + 9) & 1) != 0) cap = 0x1fe;
    *(unsigned char *)(param_2 + 0x18) = 0;
    if (param_1 + 0x40 > param_1 + 0x50U) goto fail_3176c;
    if (sk_vm_lock_check(param_1 + 0x40) != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);

    pl = (long *)(param_1 + 0x148);
    walk = (unsigned long *)(param_1 + 0x1c8);
    while ((unsigned long)(pl + 0x10) <= (unsigned long)walk) {
        long off = 0;
        do {
            walk = (unsigned long *)((long)pl + off + 8);
            {
                unsigned long *hi = (unsigned long *)((long)pl + off + 0x10);
                if ((unsigned long)(pl + 8) < (unsigned long)hi ||
                    (unsigned long)hi < (unsigned long)walk) goto fail_3176c;
            }
            {
                unsigned long base = *walk;
                if (base == 0) break;
                {
                    long idx = (long)(param_2 - base) >> 5;
                    if (idx < (long)cap) {
                        unsigned long store = *(unsigned long *)((long)pl + off + 0x48);
                        if (*(unsigned long *)(store + 0x30) != base)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aef1a);
                        if (param_2 < base ||
                            *(unsigned long *)(store + 0x30) +
                                (unsigned long)*(unsigned short *)(store + 0x40) * 0x20 <= param_2)
                            sk_vas_fault6();                        /* FUN_004b1f3c */
                        else if (idx < *(unsigned short *)(*(long *)(store + 8) + 6)) {
                            unsigned long *bm = *(unsigned long **)(store + 0x28);
                            unsigned long *cell = bm + (idx >> 6);
                            unsigned long bit = 1UL << (idx & 0x3f);
                            if ((*cell & bit) != 0)
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af0a5);
                            *cell |= bit;
                            if ((*(unsigned char *)(store + 0x43) & 1) == 0) {
                                *(unsigned long *)(store + 0x38) = 0;
                                **(unsigned long **)(param_1 + 0x140) = store;
                                *(unsigned long **)(param_1 + 0x140) =
                                    (unsigned long *)(store + 0x38);
                                *(unsigned char *)(store + 0x43) = 1;
                            }
                            if (sk_vm_lock_take(param_1 + 0x40) == 0) return;
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                        }
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aeff5);
                    }
                }
            }
            off += 8;
        } while (off != 0x38);
        pl = (long *)*pl;
        walk = (unsigned long *)(pl + 0x10);
        if (pl == (long *)0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af107);
    }
fail_3176c:
    {
        void (*a)(void);
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x31770);
        a();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00031868 @ 0x00031868   (est. sk_boot_vspace_setup)
 * Ghidra: void FUN_00031868(void)
 * Early boot-time vspace subsystem bring-up. Initialises the early vspace
 * descriptor at 0x6ac270 (FUN_00030b2c) and the object method table
 * (FUN_00034970), resets the free-run list head (DAT_0064c528/.530),
 * takes the vspace lock (DAT_0064c5e0) and initialises a secondary list
 * head (DAT_0064c690) plus a 0x1001-tagged free-run sentinel (0x6aef58)
 * whose next pointer points to 0x6aef70. Finally links the initial vspace
 * object via FUN_00030fb0. Aborts (VAS 005aed68) on any failure.
 * Called by FUN_00035a78 (the master boot init).
 * Confidence: medium (structural; global refs DAT_0064c3f0/6aef58 etc.).
 */
void sk_boot_vspace_setup(void)
{
    int r;

    sk_boot_early_vspace_init((void *)0x6ac270);      /* FUN_00030b2c */
    sk_obj_table_init((unsigned long)(uintptr_t)&sk_vspace_root_obj, 0x65b5c8, 0x65b580);  /* FUN_00034970 */
    sk_vspace_free_head = 0;
    sk_vspace_free_tail = &sk_vspace_free_head;
    r = sk_vm_lock_take2((unsigned long)&sk_vspace_lock, 0);          /* FUN_00118148 */
    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    sk_vspace_c5f0 = 0;
    sk_list_init(&sk_vspace_c690);                     /* FUN_0005ba5c */
    r = sk_vm_lock_take2((unsigned long)0x6ad2b0, 0);         /* FUN_00118148 */
    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    if (sk_alloc_big(4, 10) == 0) {                   /* FUN_0005baac */
        r = sk_vm_lock_take2((unsigned long)0x6af000, 0);    /* FUN_00118148 */
        if (r == 0) {
            sk_vspace_sentinel_tag = 0x1001;
            sk_vspace_sentinel_next = 0x6aef70;
            sk_list_init(&sk_vspace_c6b0);             /* FUN_0005ba5c */
            sk_obj_table_init(sk_vspace_sentinel_next, 0, 0);  /* FUN_00034920 */
            sk_vspace_sentinel_eff0 = 0x6aef50;
            r = sk_vm_lock_check((unsigned long)&sk_vspace_lock2);     /* FUN_00118164 */
            if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            sk_vspace_alloc_and_link((long)(uintptr_t)&sk_vspace_root_obj, (void **)0x6ac270);  /* FUN_00030fb0 */
            r = sk_vm_lock_take((unsigned long)&sk_vspace_lock2);      /* FUN_00118194 */
            if (r == 0) return;
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        }
    } else {
        sk_vas_fault9();                              /* FUN_004b1f74 */
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
}

/*--------------------------------------------------------------------*/
/* FUN_00032514 @ 0x00032514   (est. sk_vspace_root)
 * Ghidra: undefined8 * FUN_00032514(void)
 * Returns the address of the root vspace descriptor (DAT_0064c3f0), the
 * head of the vspace object table. Widely used as the "current vspace".
 * Confidence: high (trivial accessor of the root global).
 */
void *sk_vspace_root(void)
{
    return &sk_vspace_root_obj;
}

/*--------------------------------------------------------------------*/
/* FUN_00032520 @ 0x00032520   (est. sk_vspace_create_object)
 * Ghidra: undefined8 * FUN_00032520(char *param_1, undefined8 param_2,
 *           undefined8 param_3, undefined8 param_4)
 * Allocates a new vspace object (FUN_000332b8), copies the caller's
 * descriptor fields (param_1) into it, and initialises it with
 * FUN_0003264c. If the caller's descriptor carries the "done" flag at
 * *param_1==0 it also runs FUN_00034a5c. The object is then pushed onto
 * the root vspace list (DAT_0064c3f0). Aborts (VAS 005aed68) on lock
 * failure or allocation failure. Called by FUN_00035944.
 * Confidence: medium (structural; SoftwareBreakpoint 0x5519 at 0x325e0).
 */
void *sk_vspace_create_object(char *param_1, void *param_2, void *param_3,
                              void *param_4)
{
    void *obj;
    int r;
    void (*a)(void);

    obj = sk_vspace_alloc_obj();                  /* FUN_000332b8 */
    if (obj == (void *)0) {
        sk_vas_fault10();                         /* FUN_004b20ac */
    } else {
        if (obj + 0x54 < obj) { a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x325e0); a(); }
        {
            void *f0 = *(void **)(param_1 + 8);
            void *g0 = *(void **)param_1;
            void *f2 = *(void **)(param_1 + 0x18);
            void *f1 = *(void **)(param_1 + 0x10);
            sk_vspace_init_obj((long)(uintptr_t)obj, &g0, param_2, param_3, param_4);  /* FUN_0003264c */
        }
        if (*param_1 == '\0')
            sk_vspace_done(obj);                  /* FUN_00034a5c */
        r = sk_vm_lock_check(0x6ad2b0);           /* FUN_00118164 */
        if (r == 0) {
            *(void **)obj = sk_vspace_root_obj;
            sk_vspace_root_obj = obj;
            r = sk_vm_lock_take(0x6ad2b0);        /* FUN_00118194 */
            if (r == 0) return obj;
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        }
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032774 @ 0x00032774   (est. sk_vspace_destroy)
 * Ghidra: void FUN_00032774(undefined8 *param_1)
 * Destroys a vspace object, unlinking it from the root vspace list
 * (DAT_0064c3f0). Runs FUN_00032888 (teardown the backing store chain),
 * takes the vspace lock (0x6ad2b0), walks the list to find param_1, splices
 * it out (freeing its slot), then if the "in list" marker at param_1+8 is
 * clear runs FUN_00034ad0 and finally frees the object via FUN_00033304.
 * Aborts (VAS) if the object is not in the list ("unable to find vas %p on
 * next vspace" 005af5d3) or on lock failure. Called by FUN_000359d4.
 * Confidence: medium (structural; string "unable to find vas %p on next vspace").
 */
void sk_vspace_destroy(void **param_1)
{
    void **cur, **head;
    int r;
    void (*a)(void);

    sk_vspace_teardown_store();                  /* FUN_00032888 */
    r = sk_vm_lock_take2(0x6ad2b0, 0);          /* FUN_00118148 */
    if (r != 0) sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    head = &sk_vspace_root_obj;                  /* DAT_0064c3f0 */
    for (;;) {
        cur = (void **)*head;
        if (cur == param_1) {
            *head = *param_1;
            *param_1 = 0;
            r = sk_vm_lock_take(0x6ad2b0);      /* FUN_00118194 */
            if (r == 0) {
                if (*(char *)(param_1 + 1) == '\0')
                    sk_vspace_unlink_cleanup();  /* FUN_00034ad0 */
                sk_vspace_obj_free(param_1);     /* FUN_00033304 */
                return;
            }
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        }
        if (cur == (void **)0) break;
        head = cur;
        if (cur + 1 < cur) {
            a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x327d0);
            a();
        }
    }
    sk_vas_abort("unable to find vas %p on next vspace", /* 005af5d3 */
                 __func__);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032c68 @ 0x00032c68   (est. sk_vspace_reinit_object)
 * Ghidra: void FUN_00032c68(long param_1, undefined8 param_2, undefined8 param_3)
 * Re-initialises a vspace object in place: copies the caller's descriptor
 * fields (param_1+8..0x30) into a temp, tears down the existing backing
 * store chain (FUN_00032888), and rebuilds the object via FUN_0003264c.
 * Called by FUN_000359a0.
 * Confidence: medium (structural).
 */
void sk_vspace_reinit_object(long param_1, void *param_2, void *param_3)
{
    void *f0 = *(void **)(param_1 + 0x10);
    void *g0 = *(void **)(param_1 + 8);
    void *f2 = *(void **)(param_1 + 0x20);
    void *f1 = *(void **)(param_1 + 0x18);
    void *f4 = *(void **)(param_1 + 0x30);
    void *f3 = *(void **)(param_1 + 0x28);
    sk_vspace_teardown_store();                  /* FUN_00032888 */
    sk_vspace_init_obj(param_1, &g0, &f3, param_2, param_3);  /* FUN_0003264c */
}

/*--------------------------------------------------------------------*/
/* FUN_00032cd0 @ 0x00032cd0   (est. sk_vspace_layout_check_big)
 * Ghidra: void FUN_00032cd0(long param_1)
 * Bounds-check helper: returns normally iff param_1+0x60 does not wrap past
 * param_1+0x130 (the large vspace object layout); otherwise aborts via
 * SoftwareBreakpoint(0x5519). Called by many object/vspace constructors.
 * Confidence: high (trivial bounds check).
 */
void sk_vspace_layout_check_big(long param_1)
{
    void (*a)(void);
    if (param_1 + 0x60U <= param_1 + 0x130U) return;
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x32cec);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032cec @ 0x00032cec   (est. sk_vspace_layout_check_small)
 * Ghidra: void FUN_00032cec(long param_1)
 * Bounds-check helper: returns normally iff param_1+0x58 does not wrap past
 * param_1+0x60 (the small/initial vspace layout); otherwise aborts via
 * SoftwareBreakpoint(0x5519). Called by many object/vspace constructors.
 * Confidence: high (trivial bounds check).
 */
void sk_vspace_layout_check_small(long param_1)
{
    void (*a)(void);
    if (param_1 + 0x58U <= param_1 + 0x60U) return;
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x32d08);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032d08 @ 0x00032d08   (est. sk_l4_error_word)
 * Ghidra: void FUN_00032d08(undefined8 *param_1, byte param_2)
 * Fills a 32-byte block (param_1) with the L4/seL4 error-code word for the
 * given error number (0..9), reading from the static L4_ErrorCode* string
 * tables (s_L4_ErrorCodeSuccess/Preempted/Canceled/Truncated/CapInvalid/
 * SlotInvalid/MethodInvalid/ArgumentInvalid/OperationInvalid/
 * PermissionInvalid at 0x4bc048..4bc168). For codes >9 it loads the fixed
 * 0x20-byte constant block (DAT_004bc188/198/1a0) and returns 0x20. The
 * result is a 4-word {code, arg1, arg2, arg3} IPC error reply. Called by
 * FUN_00031bf4.
 * Confidence: high (string-matched error-code table).
 */
void sk_l4_error_word(void **param_1, unsigned char code)
{
    const char *tab;
    int i;

    if (code > 9) {
        param_1[1] = (void *)(uintptr_t)sk_l4_err_word1;
        param_1[0] = (void *)(uintptr_t)sk_l4_err_word0;
        param_1[3] = (void *)(uintptr_t)sk_l4_err_word3;
        param_1[2] = (void *)(uintptr_t)sk_l4_err_word2;
        sk_mem_zero(param_1, 0x20);              /* FUN_0000178c(param_1,0x20) */
        return;
    }
    switch (code) {
    default:                       tab = "L4_ErrorCodeSuccess";          break;
    case 1:                        tab = "L4_ErrorCodePreempted";        break;
    case 2:                        tab = "L4_ErrorCodeCanceled";         break;
    case 3:                        tab = "L4_ErrorCodeTruncated";        break;
    case 4:                        tab = "L4_ErrorCodeCapInvalid";       break;
    case 5:                        tab = "L4_ErrorCodeSlotInvalid";      break;
    case 6:                        tab = "L4_ErrorCodeMethodInvalid";    break;
    case 7:                        tab = "L4_ErrorCodeArgumentInvalid";  break;
    case 8:                        tab = "L4_ErrorCodeOperationInvalid"; break;
    case 9:                        tab = "L4_ErrorCodePermissionInvalid"; break;
    }
    param_1[0] = (void *)(uintptr_t)tab[0];
    param_1[1] = (void *)(uintptr_t)tab[8];
    param_1[2] = (void *)(uintptr_t)tab[0x10];
    param_1[3] = (void *)(uintptr_t)tab[0x18];
}

/*--------------------------------------------------------------------*/
/* FUN_0003264c @ 0x0003264c   (est. sk_vspace_init_obj)
 * Ghidra: void FUN_0003264c(long param_1, undefined8 *param_2,
 *           undefined8 param_3, undefined8 param_4, undefined8 param_5)
 * Full in-place initialisation of a vspace object at param_1 from a
 * caller descriptor (param_2). Copies the four descriptor words
 * (param_2[0..3]) into object slots 8/0x10/0x18/0x20, derives a 16-byte
 * method/cookie pair (FUN_000411dc), then calls FUN_00041fbc to build the
 * backing store with the descriptor bytes/words, flags, and a combined
 * options word (high word of stack arg + (flag>>1)) masked to keep bits 0
 * and 32. Resets the free-run list head (+0x140 = &+0x138) and level
 * counter (+0x200=0), then calls FUN_0003c0e4 and FUN_000459d4 to finish
 * wiring the object. Aborts (VAS/SoftwareBreakpoint 0x5519 at 0x32740) on
 * layout or lock failure. Called by FUN_00032520 and FUN_00032c68.
 * Confidence: medium (structural).
 */
void sk_vspace_init_obj(long param_1, void **param_2, void *param_3,
                        void *param_4, void *param_5)
{
    unsigned long v0, v2, v3;
    unsigned long cookie[2];
    unsigned long flag_hi;
    int r;

    flag_hi = 0;  /* high word of the stack-supplied 9th argument */
    cookie[0] = (unsigned long)sk_obj_method_cookie(*(unsigned char *)param_2, param_3);  /* FUN_000411dc */
    {
        unsigned char b = *(unsigned char *)((char *)param_2 + 1);
        v0 = (unsigned long)(uintptr_t)param_2[0];
        v3 = (unsigned long)(uintptr_t)param_2[3];
        v2 = (unsigned long)(uintptr_t)param_2[2];
        *(unsigned long *)(param_1 + 0x10) = (unsigned long)(uintptr_t)param_2[1];
        *(unsigned long *)(param_1 + 8) = v0;
        *(unsigned long *)(param_1 + 0x20) = v3;
        *(unsigned long *)(param_1 + 0x18) = v2;
        if (param_1 + 0x60U <= param_1 + 0x130U) {
            sk_vspace_backing_build(param_1 + 0x60U, *(unsigned char *)param_2,
                                    param_2[1], param_2[2], cookie[0], cookie[1],
                                    param_4, param_5,
                                    ((unsigned long)flag_hi << 32 | (b >> 1)) &
                                        0xffffffff00000001);      /* FUN_00041fbc */
            *(unsigned long *)(param_1 + 0x58) = 0;
            *(unsigned long *)(param_1 + 0x138) = 0;
            if (param_1 + 0x138U <= param_1 + 0x140U) {
                *(unsigned long *)(param_1 + 0x140) = param_1 + 0x138U;
                if (param_1 + 0x1f0U <= param_1 + 0x200U) {
                    r = sk_vm_lock_take2(param_1 + 0x1f0U, 0);    /* FUN_00118148 */
                    if (r == 0) {
                        *(unsigned long *)(param_1 + 0x200) = 0;
                        sk_vspace_final_wire(param_1, cookie[0], cookie[1]); /* FUN_0003c0e4 */
                        sk_vspace_object_done(param_1);            /* FUN_000459d4 */
                        return;
                    }
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                }
            }
        }
    }
    {
        void (*a)(void);
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x32740);
        a();
        __builtin_unreachable();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00032e1c @ 0x00032e1c   (est. sk_vspace_abort_small)
 * Ghidra: void FUN_00032e1c(undefined8 param_1)
 * Non-returning VAS abort wrapper: raises the "VAS abort" diagnostic
 * (string at 005af31e). Referenced by the fault handlers FUN_004b2034/
 * 205c/2084.
 * Confidence: high (trivial abort wrapper).
 */
void sk_vspace_abort_small(void *param_1)
{
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af31e);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032e30 @ 0x00032e30   (est. sk_vspace_abort_med)
 * Ghidra: void FUN_00032e30(undefined8 param_1)
 * Non-returning VAS abort wrapper (string at 005af480). Referenced by
 * FUN_004b1fac/200c.
 * Confidence: high (trivial abort wrapper).
 */
void sk_vspace_abort_med(void *param_1)
{
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af480);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032e44 @ 0x00032e44   (est. sk_pool_alloc_node)
 * Ghidra: void FUN_00032e44(void)
 * Allocates the per-pool node object (0x6af180, tag 0xd, ~0x3e0+0x158
 * bytes) and initialises its free-list via FUN_00032e90. Used by
 * FUN_0003b820 (pool bring-up). Aborts (SoftwareBreakpoint 0x5519) if the
 * node does not fit its layout.
 * Confidence: medium (structural).
 */
void sk_pool_alloc_node(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_0005acac */
    if (node <= node + 0x3e0 && node + 0x158 <= node + 400) {
        sk_pool_init(node, (unsigned short *)(node + 0x158), 1);       /* FUN_00032e90 */
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x32e90);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033148 @ 0x00033148   (est. sk_pool_alloc_block)
 * Ghidra: void FUN_00033148(undefined8 param_1)
 * Allocates a pool block object (0x6af180, tag 0xd) and links a caller
 * element (param_1) onto its free-list via FUN_000331a0. Used by
 * FUN_0003a7d4/3bac0/3c32c. Aborts (SoftwareBreakpoint 0x5519) on layout
 * failure.
 * Confidence: medium (structural).
 */
void sk_pool_alloc_block(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_0005acac */
    if (node <= node + 0x3e0 && node + 0x158 <= node + 400) {
        sk_pool_link(node, (unsigned short *)(node + 0x158), param_1);  /* FUN_000331a0 */
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x331a0);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032e90 @ 0x00032e90   (est. sk_pool_init)
 * Ghidra: ulong * FUN_00032e90(ulong param_1, ushort *param_2, int param_3)
 * Initialises / allocates from the object-pool free-list at param_2
 * (backing node at param_1). If param_3 is non-zero it first tries to
 * reuse an existing free entry: pops the head block (fields at param_2+0x10
 * low/high water, +0x14 count, +0x18 next), decrements the count, and if
 * non-empty returns it. Otherwise it walks the buddy free-list starting at
 * param_1+200: if the list head is empty it allocates a fresh 0x800-word
 * (4 KiB) chunk (FUN_00033f1c), tags it {next=0, size=0x4000}, and splices
 * it in; if the current chunk's size (param_2[1]) is at least the request
 * (param_2[0] words) it splits it (0x4000 buddy splits) until the leftover
 * is < 0x10 words, threading each split chunk onto the free list, then
 * returns the first-fit block; otherwise it advances the walk. Returns 0
 * when no block is available. Aborts (SoftwareBreakpoint 0x5519 at 0x330b4)
 * on list corruption. Called by FUN_00032e44/332b8/3335c/333a8/3344c/334f0/
 * 33594/33638.
 * Confidence: medium (structural buddy allocator; magic 0x6db6db6db6db6db7
 *   for the 13-element cap check, VAS strings 005b0855/005b08b2).
 */
unsigned long *sk_pool_init(unsigned long param_1, unsigned short *param_2,
                            int param_3)
{
    unsigned long req;         /* param_2[0] */
    unsigned long *head, *blk, *nb, *walk, *last;
    unsigned long size;

    if (param_1 > param_1 + 0x30) goto fail;
    (void)sk_pool_method(param_1);                  /* FUN_00034bd8 */
    if (0xc < (unsigned long)((((long)param_2 + (-0xe8 - param_1)) >> 3) *
                              0x6db6db6db6db6db7LL))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0855);
    req = (unsigned long)*param_2;
    if (0x3fff < req)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b08b2);

    if (param_3 != 0) {
        head = *(unsigned long **)(param_2 + 0x10);
        if (head != (unsigned long *)0) {
            unsigned long *lo = *(unsigned long **)(param_2 + 0x14);
            if (head + 3 <= lo) {
                unsigned long *prv = *(unsigned long **)(param_2 + 0x18);
                if (prv <= head) {
                    unsigned long count = head[1];
                    unsigned long next = *head;
                    *(unsigned long *)(param_2 + 0x18) = head[2];
                    *(unsigned long *)(param_2 + 0x14) = count;
                    *(unsigned long *)(param_2 + 0x10) = next;
                    unsigned long c = *(long *)(param_2 + 4) - 1;
                    *(unsigned long *)(param_2 + 4) = c;
                    if (c < *(unsigned char *)((char *)param_2 + 3))
                        *(char *)((char *)param_2 + 3) = (char)c;
                    /* return the popped entry if the request fits */
                    if (head <= lo && prv <= head &&
                        req <= (unsigned long)((long)lo - (long)head)) {
                        sk_mem_zero2(head, 0, req);              /* FUN_001143a0 */
                        *(long *)(param_2 + 8) = *(long *)(param_2 + 8) + 1;
                        sk_pool_touch(param_1);                  /* FUN_00034d5c */
                        if (head < lo) return head;
                    }
                }
            }
        }
        goto fail;
    }

    walk = (unsigned long *)(param_1 + 200);
    last = (unsigned long *)(param_1 + 0xd0);
    do {
        blk = (unsigned long *)*walk;
        if (blk == (unsigned long *)0) {
            blk = (unsigned long *)sk_pool_chunk_alloc();       /* FUN_00033f1c */
            nb = blk + 0x800;
            if (blk < nb) {
                if (blk == (unsigned long *)0) {
                    sk_pool_touch(param_1);                     /* FUN_00034d5c */
                    return (unsigned long *)0;
                }
                if (blk + 2 <= nb && blk <= blk + 2) {
                    *blk = 0;
                    blk[1] = 0x4000;
                    if (walk + 1 <= last && walk <= walk + 1) {
                        *walk = (unsigned long)blk;
                        size = 0x4000;
                        goto split;
                    }
                }
            }
            break;
        }
        blk = blk + 2;
        size = blk[1];
        if (req <= size) goto split;
        walk = blk;
        last = blk + 1;
    } while (blk <= blk + 2);

split:
    if (blk + 2 <= nb) {
        unsigned long next = *blk;
        size = size - req;
        nb = (unsigned long *)((long)blk + req);
        head = blk;
        if (size < 0x10) {
            if (next <= next + 0x10 && walk + 1 <= last && walk <= walk + 1) {
                *walk = next;
                /* reuse path */
                if (head <= last && head <= head + 0x10 && req <= (unsigned long)((long)last - (long)head)) {
                    sk_mem_zero2(head, 0, req);
                    *(long *)(param_2 + 8) = *(long *)(param_2 + 8) + 1;
                    sk_pool_touch(param_1);
                    if (head < last) return head;
                }
            }
        } else if (next <= next + 0x10 && nb + 2 <= (unsigned long *)((long)nb + size)) {
            *nb = next;
            nb[1] = size;
            if (nb <= nb + 2 && walk + 1 <= last && walk <= walk + 1) {
                *walk = (unsigned long)nb;
                /* return head block */
                if (head <= head + 0x10 && req <= (unsigned long)((long)last - (long)head)) {
                    sk_mem_zero2(head, 0, req);
                    *(long *)(param_2 + 8) = *(long *)(param_2 + 8) + 1;
                    sk_pool_touch(param_1);
                    if (head < last) return head;
                }
            }
        }
    }
fail:
    {
        void (*a)(void);
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x330b4);
        a();
        __builtin_unreachable();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000331a0 @ 0x000331a0   (est. sk_pool_link)
 * Ghidra: void FUN_000331a0(ulong param_1, ushort *param_2, undefined8 *param_3)
 * Links a caller element (param_3) onto the object-pool free-list at
 * param_2 (node at param_1). Validates the element fits the remaining
 * capacity (param_2[0] limit), then pushes it: copies the list head's
 * three words into the element, sets the element as new head (+0x10,
 * +0x14, +0x18), bumps the count at +4 and +0xc. Calls FUN_00034d5c to
 * finish. Returns immediately if param_3 is null; aborts
 * (SoftwareBreakpoint 0x5519 at 0x33288) if the element does not fit.
 * Called by FUN_00033148/33304/333f4/33498/3353c/335e0/33684/33780.
 * Confidence: medium (structural free-list push).
 */
void sk_pool_link(unsigned long param_1, unsigned short *param_2, void **param_3)
{
    unsigned short limit;
    void **lo, **hi, **prv;
    void (*a)(void);

    if (param_3 == (void **)0) return;
    if (param_1 > param_1 + 0x30) goto fail;
    (void)sk_pool_method(param_1);                  /* FUN_00034bd8 */
    if (0xc < (unsigned long)((((long)param_2 + (-0xe8 - param_1)) >> 3) *
                              0x6db6db6db6db6db7LL))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0855);
    limit = *param_2;
    if (param_3 + 3 <= (void **)((long)param_3 + (unsigned long)limit)) {
        hi = *(void ***)(param_2 + 0x14);
        lo = *(void ***)(param_2 + 0x10);
        prv = *(void ***)(param_2 + 0x18);
        param_3[2] = prv;
        param_3[1] = hi;
        *param_3 = lo;
        *(void ***)(param_2 + 0x14) = (void **)((long)param_3 + (unsigned long)limit);
        *(void ***)(param_2 + 0x18) = param_3;
        *(long *)(param_2 + 4) = *(long *)(param_2 + 4) + 1;
        *(long *)(param_2 + 0xc) = *(long *)(param_2 + 0xc) + 1;
        *(void ***)(param_2 + 0x10) = param_3;
        sk_pool_touch2(param_1);                    /* FUN_00034d5c */
        return;
    }
fail:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33288);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000332b8 @ 0x000332b8   (est. sk_pool_alloc_node_c0)
 * Ghidra: void FUN_000332b8(void)
 * Allocates a pool node (0x6af180, tag 0xd) and initialises its free-list
 * at offset 0x190 (400) via sk_pool_init. Used as the vspace-object
 * allocator by FUN_00032520.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c0(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 400 <= node + 0x1c8) {
        sk_pool_init(node, (unsigned short *)(node + 400), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33304);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033304 @ 0x00033304   (est. sk_pool_free_node_c0)
 * Ghidra: void FUN_00033304(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x190 of a freshly
 * allocated node via sk_pool_link. Used by FUN_00032774 (vspace destroy).
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c0(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 400 <= node + 0x1c8) {
        sk_pool_link(node, (unsigned short *)(node + 400), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x3335c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003335c @ 0x0003335c   (est. sk_pool_alloc_node_c0e4)
 * Ghidra: void FUN_0003335c(void)
 * Allocates a pool node and initialises its free-list at offset 0x1c8 via
 * sk_pool_init. Used as the vspace-block allocator by FUN_00030fb0.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c0e4(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x1c8 <= node + 0x200) {
        sk_pool_init(node, (unsigned short *)(node + 0x1c8), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x333a8);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000333a8 @ 0x000333a8   (est. sk_pool_alloc_node_c138)
 * Ghidra: void FUN_000333a8(void)
 * Allocates a pool node and initialises its free-list at offset 0x270 via
 * sk_pool_init. Used as the vspace-node allocator by FUN_00030fb0.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c138(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x270 <= node + 0x2a8) {
        sk_pool_init(node, (unsigned short *)(node + 0x270), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x333f4);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000333f4 @ 0x000333f4   (est. sk_pool_free_node_c138)
 * Ghidra: void FUN_000333f4(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x270 via sk_pool_link.
 * Used by FUN_00032888 (vspace teardown).
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c138(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x270 <= node + 0x2a8) {
        sk_pool_link(node, (unsigned short *)(node + 0x270), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x3344c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003344c @ 0x0003344c   (est. sk_pool_alloc_node_c154)
 * Ghidra: void FUN_0003344c(void)
 * Allocates a pool node and initialises its free-list at offset 0x2a8 via
 * sk_pool_init. Used by FUN_0003b6c0/3b820 (pool bring-up).
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c154(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x2a8 <= node + 0x2e0) {
        sk_pool_init(node, (unsigned short *)(node + 0x2a8), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33498);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033498 @ 0x00033498   (est. sk_pool_free_node_c154)
 * Ghidra: void FUN_00033498(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x2a8 via sk_pool_link.
 * Used by FUN_0003bac0/45614.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c154(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x2a8 <= node + 0x2e0) {
        sk_pool_link(node, (unsigned short *)(node + 0x2a8), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x334f0);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000334f0 @ 0x000334f0   (est. sk_pool_alloc_node_c170)
 * Ghidra: void FUN_000334f0(void)
 * Allocates a pool node and initialises its free-list at offset 0x2e0 via
 * sk_pool_init. Used by FUN_0003b820.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c170(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x2e0 <= node + 0x318) {
        sk_pool_init(node, (unsigned short *)(node + 0x2e0), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x3353c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003353c @ 0x0003353c   (est. sk_pool_free_node_c170)
 * Ghidra: void FUN_0003353c(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x2e0 via sk_pool_link.
 * Used by FUN_0003bac0/45614.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c170(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x2e0 <= node + 0x318) {
        sk_pool_link(node, (unsigned short *)(node + 0x2e0), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33594);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033594 @ 0x00033594   (est. sk_pool_alloc_node_c18c)
 * Ghidra: void FUN_00033594(void)
 * Allocates a pool node and initialises its free-list at offset 0x318 via
 * sk_pool_init. Used by FUN_0003b820.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c18c(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x318 <= node + 0x350) {
        sk_pool_init(node, (unsigned short *)(node + 0x318), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x335e0);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000335e0 @ 0x000335e0   (est. sk_pool_free_node_c18c)
 * Ghidra: void FUN_000335e0(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x318 via sk_pool_link.
 * Used by FUN_0003bac0/459d4.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c18c(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x318 <= node + 0x350) {
        sk_pool_link(node, (unsigned short *)(node + 0x318), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33638);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033638 @ 0x00033638   (est. sk_pool_alloc_node_c1a8)
 * Ghidra: void FUN_00033638(void)
 * Allocates a pool node and initialises its free-list at offset 0x350 via
 * sk_pool_init. Used by FUN_000387fc.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c1a8(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x350 <= node + 0x388) {
        sk_pool_init(node, (unsigned short *)(node + 0x350), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33684);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033684 @ 0x00033684   (est. sk_pool_free_node_c1a8)
 * Ghidra: void FUN_00033684(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x350 via sk_pool_link.
 * Used by FUN_00039d2c.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c1a8(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x350 <= node + 0x388) {
        sk_pool_link(node, (unsigned short *)(node + 0x350), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x336dc);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000336e0 @ 0x000336e0   (est. sk_pool_alloc_node_c1c4)
 * Ghidra: void FUN_000336e0(void)
 * Allocates a pool node and initialises its free-list at offset 0x388 via
 * sk_pool_init. No local callers found in this region.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c1c4(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x388 <= node + 0x3c0) {
        sk_pool_init(node, (unsigned short *)(node + 0x388), 1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33728);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033b50 @ 0x00033b50   (est. sk_vspace_dispatch_method)
 * Ghidra: void FUN_00033b50(long param_1)
 * Dispatches a method call on a vspace/object: takes the pool method
 * cookie (FUN_00034bd8) on the shared bss node, calls the object's method
 * handler at *(param_1+0x10), then releases via FUN_00034d5c. Used by
 * FUN_0003df84.
 * Confidence: medium (structural dispatch).
 */
void sk_vspace_dispatch_method(long param_1)
{
    unsigned long cookie[2];
    cookie[0] = sk_pool_method2((unsigned long)(unsigned long)&_DAT_0064c6f0);  /* FUN_00034bd8 */
    ((void (**)(long))param_1)[0x10 / 8](param_1);
    sk_pool_touch3((unsigned long)(unsigned long)&_DAT_0064c6f0, cookie[0], cookie[1]);  /* FUN_00034d5c */
}

/*--------------------------------------------------------------------*/
/* FUN_00033c60 @ 0x00033c60   (est. sk_vspace_alloc_region)
 * Ghidra: undefined8 FUN_00033c60(undefined1 param_1, long param_2,
 *           undefined8 param_3, undefined1 param_4)
 * Allocates a VAS/private region via the trap FUN_0003c510. Builds a
 * region descriptor {type param_1, base param_2, size param_3, attr
 * param_4} and calls FUN_0003c510 with the memory attribute selector
 * (0x1000148 when base is 0, else 0x1000149). On success returns the
 * mapped base. On failure for a zero-base (private/heap) region it prints
 * "Could not allocate for VAS private..." (FUN_00118b28) and returns 0; a
 * non-zero-base failure aborts (VAS 005b0655) or SoftwareBreakpoint(0x5519).
 * Used by FUN_00033bb0 and FUN_0003456c.
 * Confidence: medium (structural; string "Could not allocate for VAS private").
 */
unsigned long sk_vspace_alloc_region(unsigned char type, long base,
                                     unsigned long size, unsigned char attr)
{
    unsigned long sel;
    unsigned long rc;
    void *desc[4];
    unsigned long out;
    void (*a)(void);

    sel = 0x1000148;
    if (base != 0) sel = 0x1000149;
    desc[0] = (void *)(uintptr_t)type;
    desc[1] = (void *)(uintptr_t)base;
    desc[2] = (void *)(uintptr_t)size;
    desc[3] = (void *)(uintptr_t)attr;
    out = 0;
    rc = sk_trap_alloc_region(sel, desc, &out, 0, 0);   /* FUN_0003c510 */
    rc &= 0xff;
    if (rc == 0) return out;
    if (base == 0) {
        if (sk_vas_warn("Could not allocate for VAS private", rc)) /* FUN_00118b28 */
            return 0;
    } else {
        if (sk_vas_warn2("Could not allocate for VAS private", rc)) /* FUN_00118b28 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0655);
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33da4);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033bb0 @ 0x00033bb0   (est. sk_vspace_regions_init)
 * Ghidra: void FUN_00033bb0(void)
 * Boot-time VAS region setup. Allocates a node (0x6af180, tag 0xd) and
 * builds two guarded region mappings via sk_vspace_alloc_region: the first
 * from the node's stored range (+0x78..+0x88) with attr +0x90, recorded at
 * +0xa0 (active=1 at +0xa8); the second is the fixed kernel/heap range
 * (4, 0x200000, 0x10020000, 0xfe) recorded at +0xb0. Then maps the node's
 * second stored range (+0x40..+0x50, attr +0x58) into +0x68 (active=1 at
 * +0x70). Used by FUN_00035a78 (master boot init).
 * Confidence: medium (structural region setup).
 */
void sk_vspace_regions_init(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node + 0x78 <= node + 0xb0) {
        *(unsigned long *)(node + 0xa0) = sk_vspace_alloc_region(
            *(unsigned char *)(node + 0x78), *(long *)(node + 0x80),
            *(long *)(node + 0x88) - *(long *)(node + 0x80),
            *(unsigned char *)(node + 0x90));
        *(unsigned char *)(node + 0xa8) = 1;
        *(unsigned long *)(node + 0xb0) = sk_vspace_alloc_region(4, 0x200000, 0x10020000, 0xfe);
        if (node <= node + 0x3e0) {
            *(unsigned long *)(node + 0x68) = sk_vspace_alloc_region(
                *(unsigned char *)(node + 0x40), *(long *)(node + 0x48),
                *(long *)(node + 0x50) - *(long *)(node + 0x48),
                *(unsigned char *)(node + 0x58));
            *(unsigned char *)(node + 0x70) = 1;
            return;
        }
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33c60);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033da4 @ 0x00033da4   (est. sk_vspace_new_small)
 * Ghidra: void FUN_00033da4(void)
 * Allocates a small vspace store node (0x6af180, tag 0xd) and initialises
 * its free-list at offset 0x200 via sk_pool_init; on success runs
 * FUN_00030b2c to stamp the early descriptor. Used by FUN_00030cc8 when
 * the small-layout flag is clear.
 * Confidence: medium (structural; SoftwareBreakpoint 0x5519 at 0x33e00).
 */
unsigned long sk_vspace_new_small(void)
{
    unsigned long node;
    long r;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node + 0x3e0 < node || node + 0x238 < node + 0x200) {
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33e00);
        a();
        __builtin_unreachable();
    }
    r = (long)sk_pool_init(node, (unsigned short *)(node + 0x200), 1);
    if (r != 0) sk_boot_early_vspace_init((void *)r);
    return (unsigned long)r;
}

/*--------------------------------------------------------------------*/
/* FUN_00033e00 @ 0x00033e00   (est. sk_vspace_small_release)
 * Ghidra: undefined8 FUN_00033e00(undefined8 param_1)
 * Releases / tears down a small vspace store. If the root descriptor's
 * small-layout flag (FUN_00030cb8) is set, returns the element to the
 * free-list at node+0x200 (sk_pool_link). Otherwise it allocates a fresh
 * large store node (0x6af180) and either links the element at +0x238 or —
 * after allocating a 4 KiB chunk (FUN_00033f1c) — re-initialises the store
 * via sk_vspace_init_with_storage (FUN_00030b9c). Returns 0 on the slow
 * path, else the re-initialised store pointer. Aborts (SoftwareBreakpoint
 * 0x5519 at 0x33f1c) on layout failure. Used by FUN_00030cc8/32888.
 * Confidence: medium (structural).
 */
unsigned long sk_vspace_small_release(void)
{
    void *param_1 = (void *)sk_vspace_root_obj;
    unsigned long node;
    void (*a)(void);

    if (sk_vspace_is_small((long)(uintptr_t)&sk_vspace_root_obj) & 1) {  /* FUN_00030cb8 */
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
        if (node <= node + 0x3e0 && node + 0x200 <= node + 0x238) {
            sk_pool_link(node, (unsigned short *)(node + 0x200), param_1);
            return (unsigned long)(uintptr_t)param_1;
        }
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33e60);
        a();
        __builtin_unreachable();
    }
    sk_vas_fault15();                              /* FUN_004b225c */
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x238 <= node + 0x270) {
        long r = (long)sk_pool_init(node, (unsigned short *)(node + 0x238), 1);
        if (r != 0) {
            long chunk = (long)sk_pool_chunk_alloc();   /* FUN_00033f1c */
            if (chunk != 0) {
                return (unsigned long)(uintptr_t)sk_vspace_init_with_storage((void *)r, chunk);  /* FUN_00030b9c */
            }
            node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
            if (node + 0x3e0 < node || node + 0x270 < node + 0x238) goto fail;
            sk_pool_link(node, (unsigned short *)(node + 0x238), (void *)r);
        }
        return 0;
    }
fail:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33f1c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033e64 @ 0x00033e64   (est. sk_vspace_new_large)
 * Ghidra: undefined8 FUN_00033e64(void)
 * Allocates a large vspace store node (0x6af180, tag 0xd), initialises its
 * free-list at offset 0x238 via sk_pool_init, then allocates a 4 KiB chunk
 * (FUN_00033f1c) and re-initialises the store backed by it via
 * sk_vspace_init_with_storage (FUN_00030b9c). If no chunk is available it
 * frees the store node back. Returns the new store or 0. Aborts on layout
 * failure. Used by FUN_00030cc8 (large-layout flag set).
 * Confidence: medium (structural).
 */
unsigned long sk_vspace_new_large(void)
{
    unsigned long node;
    long store, chunk;
    void (*a)(void);

    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x238 <= node + 0x270) {
        store = (long)sk_pool_init(node, (unsigned short *)(node + 0x238), 1);
        if (store != 0) {
            chunk = (long)sk_pool_chunk_alloc();        /* FUN_00033f1c */
            if (chunk != 0)
                return (unsigned long)(uintptr_t)sk_vspace_init_with_storage((void *)store, chunk);  /* FUN_00030b9c */
            node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
            if (node + 0x3e0 < node || node + 0x270 < node + 0x238) goto fail;
            sk_pool_link(node, (unsigned short *)(node + 0x238), (void *)store);
        }
        return 0;
    }
fail:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x33f1c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00033f1c @ 0x00033f1c   (est. sk_vspace_chunk_alloc)
 * Ghidra: undefined8 * FUN_00033f1c(void)
 * Allocates a 4 KiB-aligned chunk from the vspace backing-store pool.
 * Uses the pool node (0x6af180, tag 0xd): if its free list (node+0xd0)
 * is non-empty it pops the head chunk and returns it. Otherwise it
 * allocates a fresh pool node, maps a new 4 KiB region via FUN_0003456c,
 * and — if that succeeds — initialises the region through the VAS trap
 * (SUB_...d2860f51) and hooks it onto the free list (node+0xd0/0xd8/0xe0)
 * with 0x4000-word entries; a "Failed to populate VAS heap" abort occurs
 * on trap failure (string 005b0829). On first init it zeroes the 4 KiB
 * chunk when the page is not already clean. Returns the chunk base (or 0),
 * aborting via SoftwareBreakpoint(0x5519) on list corruption. The result
 * must be 0x4000-aligned (checked with s_vas_round_up/alloc_aligned_frame
 * strings at 005b0748/005b0733). Used by FUN_00032e90/33e64.
 * Confidence: medium (structural; VAS strings 005b0490/005b06ea/005b0829).
 */
void *sk_vspace_chunk_alloc(void)
{
    unsigned long node, node2;
    void **head, **lo, **hi;
    void *blk, *chunk;
    unsigned long cookie[2], cookie2[2];
    void (*a)(void);
    unsigned long rc;

    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node + 0x30 < node) goto fail_3412c;
    cookie[0] = sk_pool_method(node);                 /* FUN_00034bd8 */
    head = *(void ***)(node + 0xd0);
    if (head == (void **)0) {
        node2 = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
        if (node2 + 0x30 < node2) goto fail_3412c;
        cookie2[0] = sk_pool_method(node2);           /* FUN_00034bd8 */
        if (node2 + 0x3e0 < node2 || node2 + 0x78 < node2 + 0x40) goto fail_3412c;
        blk = sk_vspace_map_region(node2, node2 + 0x40);   /* FUN_0003456c */
        if (blk == (void **)0) {
            if (*(char *)(node2 + 0xc0) == 1) {
                sk_vas_fault16();                     /* FUN_004b2294 */
                if (!(sk_vspace_is_large(0) & 1)) {
                    unsigned long v2 = sk_vas_fault17();      /* FUN_004b22cc */
                    return sk_alloc_aligned_frame((void *)v2, 0x40);  /* FUN_0003573c */
                }
                {
                    unsigned long stored = 0;
                    blk = sk_vspace_desc_lookup2(sk_vas_fault16r(), &stored);  /* FUN_00030c70 */
                    if (blk != (void **)0) {
                        unsigned long n3 = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
                        if (n3 <= n3 + 0x3e0 && n3 + 0x238 <= n3 + 0x270) {
                            sk_pool_link(n3, (unsigned short *)(n3 + 0x238), (void *)stored);
                            n3 = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
                            if (n3 <= n3 + 0x30) {
                                unsigned long c0 = sk_pool_method(n3);
                                unsigned long hiw = *(unsigned long *)(n3 + 0xe0);
                                unsigned long low = *(unsigned long *)(n3 + 0xd0);
                                ((void **)blk)[1] = (void *)*(unsigned long *)(n3 + 0xd8);
                                ((void **)blk)[0] = (void *)low;
                                ((void **)blk)[2] = (void *)hiw;
                                *(void ***)(n3 + 0xd0) = (void **)blk;
                                *(void ***)(n3 + 0xd8) = (void **)((char *)blk + 0x4000);
                                *(void ***)(n3 + 0xe0) = (void **)blk;
                                if (n3 <= n3 + 0x3e0) {
                                    sk_pool_touch3(n3, c0, 0);
                                    return blk;
                                }
                            }
                        }
                        goto fail_34308;
                    }
                }
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0490);
            }
            sk_pool_touch2(node2);                    /* FUN_00034d5c */
            if (node <= node + 0x3e0) {
                sk_pool_touch2(node);                 /* FUN_00034d5c */
                return (void **)0;
            }
            goto fail_3412c;
        }
        {
            long desc[2] = { (long)blk - *(long *)(*(long *)(node2 + 0x68) + 8), 0x4000 };
            rc = sk_vas_populate(*(long *)(node2 + 0x68), desc, desc + 1);  /* SUB_dac10230d2860f51 */
            rc &= 0xff;
            if (rc != 0) {
                sk_vas_abort("Failed to populate VAS heap VA %lx", rc);  /* 005b0829 */
            }
            sk_vspace_region_hook(node2, node2 + 0x40, blk);   /* FUN_000346c0 */
            sk_pool_touch2(node2);
            chunk = (void **)((char *)blk + 0x4000);
            sk_vas_page_ready();                       /* FUN_0004ba18 */
            if ((*(unsigned char *)(/* extraout_x1 */ 0 + 0x38) & 1) == 0) {
                if ((char *)chunk < (char *)blk ||
                    (unsigned long)((char *)chunk - (char *)blk) < 0x4000) goto fail_3412c;
                sk_mem_zero2(blk, 0, 0x4000);           /* FUN_001143a0 */
            }
        }
    } else {
        lo = *(void ***)(node + 0xd8);
        hi = *(void ***)(node + 0xe0);
        if (lo < head + 3 || head < hi) goto fail_3412c;
        *(void ***)(node + 0xe0) = head[2];
        *(void ***)(node + 0xd8) = head[1];
        *(void ***)(node + 0xd0) = head[0];
        head[0] = 0; head[1] = 0; head[2] = 0;
        chunk = head;
    }
    if (node <= node + 0x3e0) {
        sk_pool_touch2(node);
        {
            long off = 0;
            if (((unsigned long)chunk & 0x3fff) != 0) off = 0x4000;
            if ((void *)(off + ((unsigned long)chunk & 0xffffffffffffc000)) != chunk) {
                sk_vas_abort("alloc_aligned_frame %p vas_round_up(uintptr_t,ret) L4", chunk);  /* 005b06ea */
            }
        }
        if (head == (void **)0) {
            if (((unsigned long)((char *)lo - (char *)chunk) & 0xffffffffffffc000) != 0)
                return chunk;
        } else {
            if ((unsigned long)lo < (unsigned long)chunk ||
                (unsigned long)chunk < (unsigned long)hi ||
                (unsigned long)((char *)lo - (char *)chunk) < 0x4000) goto fail_3412c;
            sk_mem_zero2(chunk, 0, 0x4000);
            return chunk;
        }
    }
fail_3412c:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34130);
    a();
    __builtin_unreachable();
fail_34308:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34308);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000341f4 @ 0x000341f4   (est. sk_vspace_large_destroy)
 * Ghidra: void FUN_000341f4(undefined8 param_1)
 * Destroys / returns a large vspace backing store. If the large-layout
 * flag (FUN_00030ca8) is clear it frees an aligned frame via
 * FUN_0003573c and returns. Otherwise it looks up the store descriptor
 * (FUN_00030c70), and if it is 0x4000-aligned: returns the descriptor
 * element to the pool free-list at node+0x238, allocates a fresh node, and
 * splices the store's 0x800-word region (node+0xd0/0xd8/0xe0) back onto
 * the free list. Aborts (SoftwareBreakpoint 0x5519 at 0x34308) on layout
 * failure. Used by FUN_00030cc8/32888.
 * Confidence: medium (structural).
 */
void sk_vspace_large_destroy(unsigned long param_1)
{
    unsigned long node, stored;
    unsigned long cookie[2];
    void (*a)(void);

    if (!(sk_vspace_is_large(0) & 1)) {
        unsigned long v = sk_vas_fault17();            /* FUN_004b22cc */
        sk_alloc_aligned_frame((void *)v, 0x40);       /* FUN_0003573c */
        return;
    }
    {
        void *desc = sk_vspace_desc_lookup2(param_1, &stored);   /* FUN_00030c70 */
        if (desc != (void **)0) {
            long off = 0;
            if (((unsigned long)desc & 0x3fff) != 0) off = 0x4000;
            if ((void *)(off + ((unsigned long)desc & 0xffffffffffffc000)) == desc) {
                node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
                if (node <= node + 0x3e0) {
                    if (node + 0x238 <= node + 0x270) {
                        sk_pool_link(node, (unsigned short *)(node + 0x238), (void *)stored);
                        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
                        if (node <= node + 0x30) {
                            cookie[0] = sk_pool_method(node);
                            ((void **)desc)[1] = (void *)*(unsigned long *)(node + 0xd8);
                            ((void **)desc)[0] = (void *)*(unsigned long *)(node + 0xd0);
                            ((void **)desc)[2] = (void *)*(unsigned long *)(node + 0xe0);
                            *(void ***)(node + 0xd0) = (void **)desc;
                            *(void ***)(node + 0xd8) = (void **)((char *)desc + 0x4000);
                            *(void ***)(node + 0xe0) = (void **)desc;
                            if (node <= node + 0x3e0) {
                                sk_pool_touch3(node, cookie[0], cookie[1]);
                                return;
                            }
                        }
                    }
                }
                goto fail_34308;
            }
        }
    }
fail_34308:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34308);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034334 @ 0x00034334   (est. sk_alloc_aligned_frame_small)
 * Ghidra: void FUN_00034334(undefined8 param_1)
 * Thin wrapper: allocates/frees an aligned frame (0x40) via FUN_0003573c
 * and returns. Used by FUN_00041d9c.
 * Confidence: high (trivial wrapper).
 */
void sk_alloc_aligned_frame_small(void *param_1)
{
    sk_alloc_aligned_frame(param_1, 0x40);   /* FUN_0003573c */
}

/*--------------------------------------------------------------------*/
/* FUN_0003433c @ 0x0003433c   (est. sk_pool_alloc_dual)
 * Ghidra: ulong FUN_0003433c(void)
 * Allocates a dual-region pool element. Allocates a pool node (0x6af180,
 * tag 0xd) and, if the node's per-instance flag (+0xc2 bit 0) is clear or
 * the busy flag (+0xc1) is set, scans the 3-slot free-list (+0x3c0) for a
 * free entry, else allocates a fresh node (FUN_004b233c). Clears the slot,
 * and if the count at +0x3d8 is zero allocates a fresh pool block at
 * +0xe8 (via sk_pool_init) under the busy flag; returns it (must fit
 * +0x48). Otherwise decrements the count and returns the next entry.
 * FUN_00034340 is a duplicate of this routine (same body).
 * Confidence: medium (structural; SoftwareBreakpoint 0x5519 at 0x343e0).
 */
unsigned long sk_pool_alloc_dual(void)
{
    unsigned long node, slot;
    unsigned long *fr, *cnt;
    char c;
    void (*a)(void);

    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (((*(unsigned char *)(node + 0xc2) & 1) == 0) ||
        (*(char *)(node + 0xc1) == 1)) {
        fr = (unsigned long *)(node + 0x3c0);
        cnt = (unsigned long *)(node + 0x3d8);
        for (int i = 0; i < 3; i++) {
            if ((unsigned long)cnt < (unsigned long)(fr + 1) ||
                (unsigned long)(fr + 1) < (unsigned long)fr) {
                a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x343e0);
                a();
                __builtin_unreachable();
            }
            slot = *fr;
            if (slot != 0) goto found;
            fr += 1;
        }
        node = sk_vas_fault18();                 /* FUN_004b233c */
        slot = 0; fr = 0; cnt = 0;
    }
found:
    *fr = 0;
    c = (char)*cnt;
    if (c == '\0') {
        sk_vas_fault19();                        /* FUN_004b2304 */
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
        *(unsigned char *)(node + 0xc1) = 1;
        slot = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
        if (slot <= slot + 0x3e0 && slot + 0xe8 <= slot + 0x120) {
            slot = (unsigned long)sk_pool_init(slot, (unsigned short *)(slot + 0xe8), 1);
            *(unsigned char *)(node + 0xc1) = 0;
            if (slot <= slot + 0x48) return slot;
        }
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34468);
        a();
        __builtin_unreachable();
    }
    *(char *)(node + 0x3d8) = c - 1;
    if ((unsigned char)(c - 1U) < *(unsigned char *)(node + 0x3d9))
        *(char *)(node + 0x3d9) = (char)(c - 1U);
    return slot;
}

/*--------------------------------------------------------------------*/
/* FUN_00034340 @ 0x00034340   (est. sk_pool_alloc_dual2)
 * Ghidra: ulong FUN_00034340(void)
 * Duplicate of FUN_0003433c (same body, separate code entry). Allocates a
 * dual-region pool element with the identical scan/alloc logic.
 * Confidence: medium.
 */
unsigned long sk_pool_alloc_dual2(void)
{
    return sk_pool_alloc_dual();
}

/*--------------------------------------------------------------------*/
/* FUN_00034468 @ 0x00034468   (est. sk_vspace_map_region_page)
 * Ghidra: long FUN_00034468(void)
 * Maps a fresh 4 KiB region into a vspace node. Allocates a pool node
 * (0x6af180), sets its busy flag (+0xc1), maps a region at node+0x78 via
 * FUN_0003456c, and — if the mapping is a fresh page — populates it via the
 * VAS trap (SUB_...d2860f51) and hooks it (FUN_000346c0), bumping the
 * node's size counter (+0x98) by 0x4000 on success. Clears the busy flag
 * and releases the pool node. Returns the mapped base or 0. Aborts
 * (SoftwareBreakpoint 0x5519 at 0x3456c) on layout failure.
 * Confidence: medium (structural; Type-propagation-warning in Ghidra).
 */
long sk_vspace_map_region_page(void)
{
    unsigned long node;
    unsigned long cookie[2];
    long base;
    char rc;
    void (*a)(void);

    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x30) {
        cookie[0] = sk_pool_method(node);          /* FUN_00034bd8 */
        *(unsigned char *)(node + 0xc1) = 1;
        if (node <= node + 0x3e0) {
            base = (long)sk_vspace_map_region(node, node + 0x78);   /* FUN_0003456c */
            if (base != 0) {
                long desc[2] = { base - *(long *)(*(long *)(node + 0xa0) + 8), 0x4000 };
                rc = (char)sk_vas_populate(*(long *)(node + 0xa0), desc, desc + 1);  /* SUB_dac10230d2860f51 */
                sk_vspace_region_hook(node, node + 0x78, (void *)base);   /* FUN_000346c0 */
                if (rc != '\0') {
                    base = 0;
                    *(long *)(node + 0x98) = *(long *)(node + 0x98) + 0x4000;
                }
            }
            *(unsigned char *)(node + 0xc1) = 0;
            sk_pool_touch3(node, cookie[0], cookie[1]);   /* FUN_00034d5c */
            return base;
        }
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x3456c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003456c @ 0x0003456c   (est. sk_vspace_region_map)
 * Ghidra: void FUN_0003456c(ulong param_1, undefined1 *param_2)
 * Maps / resets a vspace region descriptor (param_2) within the pool node
 * (param_1). Requires the region-method flag (FUN_00034ba4) to be set.
 * If the region is not yet committed (param_2[1] != 1): validates the
 * current base against the low bound (+8) — aborting if it overruns — and
 * sets param_2[1]=1, storing the next base as base-0x4000. For the special
 * case where the base equals the mapped region's start it first maps a
 * fresh 0x10000 heap region (FUN_00033c60) and reads its new base. Aborts
 * (VAS 005b0c27/005b090a/005b0ca4) on invalid layout.
 * Confidence: medium (structural).
 */
void sk_vspace_region_map(unsigned long param_1, unsigned char *param_2)
{
    unsigned long u;
    void (*a)(void);

    if (param_1 + 0x30 < param_1) goto fail_34634;
    if ((sk_region_method() & 1) == 0)              /* FUN_00034ba4 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b090a);
    if (param_2[1] != 1) {
        u = *(unsigned long *)(param_2 + 0x20);
        if ((param_2[0x30] & 1) == 0) {
            if (u <= *(unsigned long *)(param_2 + 8))
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0c27);
        } else {
            unsigned long u1 = *(unsigned long *)(*(long *)(param_2 + 0x28) + 8);
            if (*(unsigned long *)(*(long *)(param_2 + 0x28) + 0x10) < u - u1)
                goto fail_34660;
            if (u == u1) {
                u = sk_vspace_alloc_region(*param_2, 0, 0x10000, param_2[0x18]);  /* FUN_00033c60 */
                if (u == 0) return;
                *(unsigned long *)(param_2 + 0x28) = u;
                if (u + 0x20 < u) goto fail_34634;
                u = *(long *)(u + 0x10) + *(long *)(u + 8);
            }
        }
        param_2[1] = 1;
        *(unsigned long *)(param_2 + 0x20) = u - 0x4000;
        return;
    }
    sk_vas_fault20();                               /* FUN_004b2368 */
fail_34660:
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0ca4);
fail_34634:
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34634);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000346c0 @ 0x000346c0   (est. sk_vspace_region_hook)
 * Ghidra: void FUN_000346c0(ulong param_1, long param_2, long param_3)
 * Commits / releases a region mapping in a vspace node. Requires the
 * region-method flag (FUN_00034ba4). If the region at param_2 is committed
 * (param_2[1] bit 0 set) and the mapped base param_3 equals the region's
 * current base (+0x20), validates it against the mapped-region size
 * (+0x28, abort 005b0e13 on overflow) and clears the committed flag
 * (param_2[1]=0). Aborts (VAS 005b0daa/005b090a) on mismatch. Used by
 * FUN_00033f1c/34468.
 * Confidence: medium (structural).
 */
void sk_vspace_region_hook2(unsigned long param_1, long param_2, long param_3)
{
    void (*a)(void);
    if (param_1 + 0x30 < param_1) {
        a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34740);
        a();
        __builtin_unreachable();
    }
    if ((sk_region_method() & 1) != 0) {            /* FUN_00034ba4 */
        if ((*(unsigned char *)(param_2 + 1) & 1) == 0) {
            sk_vas_fault21();                        /* FUN_004b23a0 */
        } else if (param_3 == *(long *)(param_2 + 0x20)) {
            long r = *(long *)(param_2 + 0x28);
            if (r != 0) {
                if (*(unsigned long *)(r + 0x10) <=
                    (unsigned long)(param_3 - *(long *)(r + 8)))
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e13);
            }
            *(unsigned char *)(param_2 + 1) = 0;
            return;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0daa);
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b090a);
}

/*--------------------------------------------------------------------*/
/* FUN_000347c4 @ 0x000347c4   (est. sk_pool_alloc_node_c90)
 * Ghidra: void FUN_000347c4(void)
 * Allocates a pool node and initialises its free-list at offset 0x120 via
 * sk_pool_init; the result must fit +0x40. Used by FUN_00035bac/36dec.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_alloc_node_c90(void)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x120 <= node + 0x158 &&
        (node = (unsigned long)sk_pool_init(node, (unsigned short *)(node + 0x120), 1),
         node <= node + 0x40))
        return;
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x3481c);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003481c @ 0x0003481c   (est. sk_pool_free_node_c90)
 * Ghidra: void FUN_0003481c(undefined8 param_1)
 * Returns a pool element to the free-list at offset 0x120 via sk_pool_link.
 * Used by FUN_00035bac/3611c/36920/373a4/37e9c.
 * Confidence: medium (trivial wrapper).
 */
void sk_pool_free_node_c90(void *param_1)
{
    unsigned long node;
    void (*a)(void);
    node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);
    if (node <= node + 0x3e0 && node + 0x120 <= node + 0x158) {
        sk_pool_link(node, (unsigned short *)(node + 0x120), param_1);
        return;
    }
    a = (void (*)(void))SoftwareBreakpoint(0x5519, 0x34874);
    a();
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034874 @ 0x00034874   (est. sk_vspace_abort_lg)
 * Ghidra: void FUN_00034874(undefined8 param_1)
 * Non-returning VAS abort wrapper (string at 005b0352). Referenced by
 * FUN_004b2128/21c4.
 * Confidence: high (trivial abort wrapper).
 */
void sk_vspace_abort_lg(void *param_1)
{
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0352);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034888 @ 0x00034888   (est. sk_obj_table_boot)
 * Ghidra: bool FUN_00034888(void)
 * One-time initialisation of the object table node. Allocates the boot
 * node (FUN_0005baac, tag 8); if none is currently in use (returns 0),
 * initialises the shared list head (DAT_0064cb20) and runs FUN_000348d0 to
 * size the table. Returns true iff the node was freshly allocated. Used by
 * FUN_00034970.
 * Confidence: medium (structural; DAT_0064cb20).
 */
bool sk_obj_table_boot(void)
{
    long node;
    node = sk_alloc_big2(4, 8);                   /* FUN_0005baac */
    if (node == 0) {
        sk_list_init(&_DAT_0064cb20);             /* FUN_0005ba5c */
        sk_obj_table_size();                      /* FUN_000348d0 */
    }
    return node == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000348d0 @ 0x000348d0   (est. sk_obj_table_size)
 * Ghidra: void FUN_000348d0(void)
 * Computes the object-table capacity. Allocates the table node (0x6af188,
 * tag 8), reads the element count at +0x48, and if the count is small
 * enough (bit 17 clear and count*0x8000 < 0xfffe0000) sets the table
 * boundary at +0x44 to count*0x8000+0x20000. Otherwise it records the
 * overflow node pointer in the global DAT_006ad2c0 (aborting if already
 * set, VAS 005b0e73). Used by FUN_00034888/34a5c/34ad0.
 * Confidence: medium (structural; DAT_006ad2c0).
 */
void sk_obj_table_size(void)
{
    unsigned long node;
    unsigned int cnt;
    unsigned long u;
    node = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);
    cnt = *(unsigned int *)(node + 0x48) * 0x8000;
    if (*(unsigned int *)(node + 0x48) >> 0x11 == 0 && cnt < 0xfffe0000) {
        *(unsigned int *)(node + 0x44) = cnt + 0x20000;
        return;
    }
    u = sk_vas_fault22();                        /* FUN_004b2584 */
    if (_DAT_006ad2c0 == 0) {
        _DAT_006ad2c0 = u;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e73);
}

/*--------------------------------------------------------------------*/
/* FUN_00034920 @ 0x00034920   (est. sk_obj_table_register)
 * Ghidra: void FUN_00034920(undefined8 param_1)
 * Registers the object-table node pointer in the global DAT_006ad2c0;
 * aborts (VAS 005b0e73) if it is already registered. Used by FUN_00031868.
 * Confidence: high (structural; DAT_006ad2c0).
 */
void sk_obj_table_register(void *param_1)
{
    if (_DAT_006ad2c0 == 0) {
        _DAT_006ad2c0 = (unsigned long)(uintptr_t)param_1;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e73);
}

/*--------------------------------------------------------------------*/
/* FUN_00034970 @ 0x00034970   (est. sk_obj_table_init)
 * Ghidra: long * FUN_00034970(long param_1, long param_2, long *param_3)
 * Initialises the object table. Runs sk_obj_table_boot (FUN_00034888) and
 * allocates the table node (0x6af188, tag 8). If the node was not freshly
 * booted but already marked initialised (bit 0 at node+8) and carries a
 * valid method triple, it returns it. Otherwise, if freshly booted and
 * uninitialised, it stores the method table (param_1=methods, param_2=
 * table base, param_3=object list) into the node and marks it initialised
 * (node+8 bit 0). On any inconsistency it faults (FUN_004b25bc/25f4/262c/
 * 2664/269c) and returns the stored object pointer at (node+0x10). Used by
 * FUN_00031868.
 * Confidence: medium (structural init guard).
 */
long *sk_obj_table_init2(long param_1, long param_2, long *param_3)
{
    unsigned long fresh;
    long *node;
    long *obj;

    fresh = sk_obj_table_boot();                  /* FUN_00034888 */
    node = (long *)sk_vspace_alloc_big(0x6af188, 4, 8);
    if ((fresh & 1) == 0) {
        if ((*(unsigned char *)(node + 1) & 1) != 0) {
            obj = (long *)*node;
            if (obj != (long *)0 && *obj != 0 && obj[1] != 0 && obj[2] != 0)
                return node;
            sk_vas_fault23();                     /* FUN_004b25f4 */
            goto fault;
        }
    } else {
        if (*(unsigned char *)(node + 1) == 0) {
            if (param_1 == 0) goto fault2;
            if (param_3 != (long *)0 && *param_3 != 0 && param_3[1] != 0) {
                node[2] = param_1;
                node[3] = param_2;
                *node = (long)param_3;
                *(unsigned char *)(node + 1) = 1;
                return node;
            }
fault:
            sk_vas_fault24();                     /* FUN_004b262c */
        }
        sk_vas_fault25();                         /* FUN_004b269c */
    }
    sk_vas_fault26();                             /* FUN_004b25bc */
fault2:
    sk_vas_fault27();                             /* FUN_004b2664 */
    {
        unsigned long n2 = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);
        return *(long **)(n2 + 0x10);
    }
}















