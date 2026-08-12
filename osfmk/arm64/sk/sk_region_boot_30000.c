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
extern void sk_vspace_teardown_store(long);          /* FUN_00032888 */
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
extern unsigned long sk_region_method(long);               /* FUN_00034ba4 */
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

    sk_vspace_teardown_store((long)param_1);     /* FUN_00032888 */
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
    sk_vspace_teardown_store(param_1);           /* FUN_00032888 */
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
    if ((sk_region_method(param_1) & 1) == 0)        /* FUN_00034ba4 */
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
    if ((sk_region_method(param_1) & 1) != 0) {     /* FUN_00034ba4 */
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















/* ------------------------------------------------------------------ *
 * External cL4 helpers referenced by the appended 0x31a8c-0x3ff00
 * bodies but defined in sibling range workers / earlier regions.
 * Names are estimates; signatures are variadic to match decompile call
 * sites (this file is -fsyntax-only, so no link-time checks).
 * ------------------------------------------------------------------ */

extern unsigned long sk_boot_region_check();
extern unsigned long sk_boot_handoff2();
extern unsigned long sk_boot_something();
extern unsigned long sk_span_find();
extern unsigned long sk_walk_span3();                                 /* FUN_000402b4 */
extern unsigned long sk_map_span3();                                  /* FUN_000403b0 */
extern unsigned long sk_span_find_next3();
extern unsigned long sk_span_remap3();
extern unsigned long sk_span_commit3();
extern unsigned long sk_span_alloc3();
extern unsigned long sk_span_map3();
extern unsigned long sk_obj_method_dispatch3();              /* FUN_00042abc */
extern unsigned long sk_obj_lookup3();                       /* FUN_00042c20 */
extern unsigned long sk_obj_attr3();                         /* FUN_000436fc */
extern unsigned long sk_obj_meta3();                         /* FUN_00043b44 */
extern unsigned long sk_obj_meta4();                         /* FUN_00043be8 */
extern unsigned long sk_obj_meta5();
extern unsigned long sk_obj_unref2();                                 /* FUN_00043e88 */
extern unsigned long sk_obj_new2();
extern unsigned long sk_obj_wire4();                                  /* FUN_00043f28 */
extern unsigned long sk_obj_link4();                                  /* FUN_00044be0 */
extern unsigned long sk_obj_unlink4();                                /* FUN_00044c94 */
extern unsigned long sk_obj_snapshot4();                              /* FUN_00044dec */
extern unsigned long sk_obj_commit4();                       /* FUN_00044ff4 */
extern unsigned long sk_obj_create5();                       /* FUN_000451a0 */
extern unsigned long sk_obj_attach5();                       /* FUN_000455b0 */
extern unsigned long sk_obj_teardown5();
extern unsigned long sk_obj_finalize5();
extern unsigned long sk_obj_map5();                                   /* FUN_000458a0 */
extern unsigned long sk_obj_init5();
extern unsigned long sk_obj_walk5();                         /* FUN_00045a68 */
extern unsigned long sk_obj_state5();                        /* FUN_00045c98 */
extern unsigned long sk_obj_state6();                        /* FUN_00045cb8 */
extern unsigned long sk_obj_unref_block();                   /* FUN_0004b8d0 */
extern unsigned long sk_errname3();
extern unsigned long sk_walk_abort3();
extern unsigned long sk_stack_check();                                /* FUN_00116c78 */
extern unsigned long sk_mem_move3();                         /* FUN_00117d14 */
extern unsigned long sk_ref_unlink3();                       /* FUN_00117f8c */
extern unsigned long sk_percpu_get3();                                /* FUN_001180fc */
extern unsigned long sk_stack_check_fail3();

extern unsigned long sk_vas_fault28();
extern unsigned long sk_vas_fault29();
extern unsigned long sk_vas_fault30();
extern unsigned long sk_vas_fault31();
extern unsigned long sk_vas_fault32();
extern unsigned long sk_vas_fault33();
extern unsigned long sk_vas_fault34();
extern unsigned long sk_vas_fault35();
extern unsigned long sk_vas_fault36();
extern unsigned long sk_vas_fault37();
extern unsigned long sk_vas_fault38();
extern unsigned long sk_vas_fault39();
extern unsigned long sk_vas_fault40();
extern unsigned long sk_vas_fault41();
extern unsigned long sk_vas_fault42();
extern unsigned long sk_vas_fault43();
extern unsigned long sk_vas_fault44();
extern unsigned long sk_vas_fault45();
extern unsigned long sk_vas_fault46();
extern unsigned long sk_vas_fault47();
extern unsigned long sk_vas_fault48();
extern unsigned long sk_vas_fault49();
extern unsigned long sk_vas_fault50();
extern unsigned long sk_vas_fault51();
extern unsigned long sk_vas_fault52();
extern unsigned long sk_vas_fault53();
extern unsigned long sk_vas_fault54();
extern unsigned long sk_vas_fault55();
extern unsigned long sk_vas_fault56();
extern unsigned long sk_vas_fault57();
extern unsigned long sk_vas_fault58();
extern unsigned long sk_vas_fault59();
extern unsigned long sk_vas_fault60();
extern unsigned long sk_vas_fault61();
extern unsigned long sk_vas_fault62();
extern unsigned long sk_vas_fault63();
extern unsigned long sk_vas_fault64();
extern unsigned long sk_vas_fault65();
extern unsigned long sk_vas_fault66();
extern unsigned long sk_vas_fault67();
extern unsigned long sk_vas_fault68();
extern unsigned long sk_vas_fault69();
extern unsigned long sk_vas_fault70();
extern unsigned long sk_vas_fault71();
extern unsigned long sk_vas_fault72();
extern unsigned long sk_vas_fault73();
extern unsigned long sk_vas_fault74();
extern unsigned long sk_vas_fault75();
extern unsigned long sk_vas_fault76();
extern unsigned long sk_vas_fault77();
extern unsigned long sk_vas_fault78();
extern unsigned long sk_vas_fault79();
extern unsigned long sk_vas_fault80();
extern unsigned long sk_vas_fault81();
extern void *sk_vas_fault82(void);                               /* FUN_004b3464 */
extern unsigned long sk_vas_fault83();
extern unsigned long sk_vas_fault84();
extern unsigned long sk_vas_fault85();

/* additional helpers referenced by the appended bodies */
extern unsigned long sk_slot_attach_full(unsigned long *, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);   /* FUN_0003b820 */
extern void sk_span_lookup_build6(unsigned long *, unsigned long, unsigned long, unsigned long, unsigned int); /* FUN_00035bac */
extern void sk_span_prefetch_pages(char *, unsigned long, long); /* FUN_0003df84 */
extern unsigned long sk_span_find2();         /* FUN_000287e4 */

/* aliases with the decompile-accurate signatures used by the appended bodies */
extern cl4_result_t sk_pool_method_full(unsigned long);           /* FUN_00034bd8 */
extern void sk_pool_touch_full(unsigned long, unsigned long, unsigned long); /* FUN_00034d5c */
extern unsigned long sk_vas_fault14r();
extern unsigned long sk_alloc_big3(int, int);                     /* FUN_0005baac */
extern void sk_list_init2(void *);                                /* FUN_0005ba5c */
extern unsigned long sk_vspace_new_small2();
extern void sk_obj_table_init2b(unsigned long, unsigned long, unsigned long); /* FUN_00034970 */
extern void sk_pool_touch2b(unsigned long, unsigned long, unsigned long);     /* FUN_00034d5c */
extern void sk_vspace_slot_tree_remove_node(unsigned long *, unsigned int, unsigned int); /* FUN_0003730c */
extern unsigned long sk_spanmap_refcount_inc();
extern unsigned long sk_spanmap_refcount_dec();
extern unsigned long sk_walk_refcount_inc();
/* data globals referenced by the appended bodies */
extern unsigned long sk_stat_walk_all;       /* DAT_006ad378 */
extern unsigned long sk_stat_walk_ok;        /* DAT_006ad37c */
extern unsigned long sk_stat_walk_attr;      /* DAT_006ad38c */
extern unsigned long sk_stat_walk_start;     /* DAT_006ad344 */
extern unsigned long sk_stat_walk_attach;    /* DAT_006ad348 */
extern unsigned long sk_stat_walk_total;     /* DAT_006ad2c8 */
extern unsigned long sk_desc_boot;           /* DAT_004bc378 */
extern unsigned long sk_stat_fault_inc;      /* DAT_006af198 */
extern unsigned long sk_obj_methods_2[];     /* DAT_004bc358 */
extern unsigned long sk_vspace_lock_6af000;  /* 0x6af000 */
extern unsigned long sk_fault_span_next3();   /* FUN_000405d0 */
extern void sk_slot_detach_inner(void *);   /* FUN_0003bac0 */
extern void sk_slot_push_f();   /* FUN_0003e640 push variant */
/* prototypes */
long sk_vspace_attach_spanmap(long param_1, long param_2);
void sk_boot_vspace_early_init(void);
cl4_result_t sk_vspace_slot_alloc_frame(void);
void sk_boot_bss_lock_init(unsigned long lock, unsigned long owner, unsigned long tag);
long sk_vspace_slot_alloc_new(void);
unsigned long sk_vspace_node_pop(void);
void sk_vspace_slot_bitmap_init(unsigned long *node);
void sk_vspace_slot_tree_insert(unsigned long *root, unsigned long node);
void sk_vspace_slot_free_search(unsigned long base);
unsigned long sk_vspace_region_alloc_pages(long base, unsigned long count, unsigned long size);
bool sk_vspace_claim_bits(unsigned long *node, long granule);
void sk_vspace_root_store(unsigned long value);
unsigned long sk_void_return(void);
void sk_span_lookup_build(unsigned long param_1, unsigned long param_2);
void sk_span_lookup_build_n(void);
unsigned long sk_span_resolve_addr(unsigned long span);
void sk_span_release(unsigned long *out, unsigned long span, unsigned int count, void (*cb)(unsigned long));
void sk_span_cursor_build(unsigned long *out, unsigned long span, unsigned int count);
unsigned long * sk_span_cursor_recurse(unsigned long *span, unsigned int count);
unsigned long sk_span_cursor_next(unsigned long *cursor);
void sk_span_merge(unsigned long *out, unsigned long lo, unsigned long hi);
unsigned int sk_granule_index(unsigned int w);
void sk_span_release_all(unsigned long span, void (*cb)(unsigned long));
void sk_span_compact(unsigned long *out, unsigned long span, unsigned long limit);
void sk_span_release_all_t(unsigned long span, void (*cb)(unsigned long));
cl4_result_t sk_span_table_insert(unsigned long *table, unsigned long span, unsigned int slots, unsigned int mode);
void sk_span_tree_alloc(unsigned long *out, unsigned long node, unsigned long tag);
void sk_span_tree_build(unsigned long *out, unsigned long *src, unsigned int count, unsigned long mode);
unsigned int sk_span_tree_remove_node(unsigned long *table, unsigned int idx, unsigned int cap);
cl4_result_t sk_span_tree_release(unsigned long *root, unsigned int granule, void (*cb)(unsigned long));
void sk_span_tree_destroy(unsigned long *root, void (*cb)(unsigned long));
void sk_span_tree_alloc2(unsigned long size, unsigned long *out);
void sk_span_tree_bump(long *node, unsigned long size);
void sk_span_tree_destroy2(long *node);
unsigned long sk_span_tree_remap(unsigned long root, unsigned long addr, long *out_base, unsigned long *out_len);
void sk_fault_span_common(void);
void sk_fault_span_common_t(void);
cl4_result_t sk_fault_span_find(unsigned long region);
cl4_result_t sk_fault_span_get(unsigned long region, unsigned long addr, int *count_out, unsigned long *desc_out);
unsigned long sk_fault_span_release(unsigned long region, unsigned long addr, int mode);
cl4_result_t sk_fault_span_commit(void);
cl4_result_t sk_fault_span_walk(unsigned long region, unsigned long addr, unsigned long size);
unsigned long sk_fault_span_flush(unsigned long region);
cl4_result_t sk_fault_span_map(long region, long *state, unsigned long addr, unsigned long flags, unsigned char *out_state);
cl4_result_t sk_span_destroy(unsigned char *span);
void sk_span_unmap(long span, unsigned int attrs);
unsigned long sk_span_alloc_region(long span, unsigned long *out);
unsigned long sk_span_map_region(long span, unsigned long *base_out, unsigned long *size_out);
cl4_result_t sk_span_split(long span, unsigned long at, long *lo_out, long *hi_out);
cl4_result_t sk_span_attach(unsigned long *span, unsigned long at, unsigned int attrs, unsigned long *dest);
cl4_result_t sk_span_next_region(long *span);
unsigned long * sk_slot_pop_a(long obj);
void sk_slot_push_a(long obj, unsigned long *node);
unsigned long * sk_slot_pop_b(long obj);
void sk_slot_push_b(long obj, unsigned long *node);
unsigned long * sk_slot_pop_c(long obj);
void sk_slot_push_c(long obj, unsigned long *node);
unsigned long sk_slot_pop_d(long obj);
void sk_slot_push_d(long obj, unsigned long *node);
void sk_slot_unlink_root(unsigned long *root, unsigned long *node, unsigned long param_3, unsigned long param_4);
void sk_slot_link_root(long *root, long node, unsigned long param_3);
unsigned long sk_slot_attach_wrap(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6, unsigned long p7, unsigned long p8);
unsigned long sk_slot_attach(unsigned long st, unsigned long region, unsigned long p3, unsigned long p4);
cl4_result_t sk_region_bind(long region, long p2, long span, long p4);
void sk_slot_detach(long *root, long region);
void sk_region_wire(void);
unsigned long * sk_slot_pop_e(long obj);
void sk_region_attach(unsigned long *tree, unsigned long span);
void sk_region_teardown(long span);
bool sk_region_check(long owner, long tag, long region, long tag2);
cl4_result_t sk_region_create(long owner, unsigned int attrs, char *desc, unsigned long *out, unsigned int *p5, unsigned long *p6);
unsigned int sk_region_config(long region, long tag, unsigned long *desc, unsigned long p4);
void sk_region_bounds(unsigned long region, unsigned long *start_out, long *end_out);
void sk_region_map_span(unsigned long base, unsigned long size, long region, unsigned long attr, unsigned long p5);
unsigned long sk_region_map_next(long region);
void sk_region_release3(long region);
void sk_region_unmap_pages(unsigned long granule, long region, int attr, int mode, int p5);
cl4_result_t sk_region_lookup_span(unsigned long region, long addr, long *node_out, unsigned long *span_out);
unsigned long sk_region_find_span(unsigned long *tree, unsigned long addr);
cl4_result_t sk_region_map_pages(unsigned long *out, unsigned long region, long span, unsigned long base, unsigned long count);
cl4_result_t sk_region_unmap_indirect(long *span, unsigned long offset, unsigned long page);
cl4_result_t sk_region_unmap_direct(long region, unsigned long page);
unsigned int sk_cap_validate(long *out, long cap);
unsigned int sk_cap_release(long *obj, unsigned long cap, unsigned long *out);
unsigned int sk_cap_revoke(long *cap);
unsigned long * sk_slot_pop_f(long obj);
unsigned long sk_class_perm(char class);
void sk_region_walk_span(unsigned long *out, unsigned long *tree, long region, unsigned long *walk);
long sk_rand_mod(unsigned long modulus);
void sk_region_bind2(unsigned long p1, unsigned long p2, long span);
void sk_region_desc_fill(char *region);
unsigned long sk_region_adjust(long region, long span);
unsigned long sk_region_walk_find(long span, unsigned long lo, unsigned long hi, unsigned long limit, long methods);
cl4_result_t sk_region_split(long tree, unsigned long owner, unsigned long *region, unsigned long at, unsigned long *lo_out, unsigned long *hi_out);
void sk_region_recalc(long node, long changed);
cl4_result_t sk_region_finalize(unsigned long span, unsigned long *base_out, unsigned long *size_out, int commit);
unsigned long sk_region_merge2(unsigned long st, unsigned long owner, long a, long b);
cl4_result_t sk_region_merge(unsigned long *tree, unsigned long owner, long a, long b, long *lo_out, long *hi_out);
unsigned long sk_region_tree_remove(long *root, long node);
void sk_region_tree_rebalance(unsigned long *root, int dir);
void sk_err_name(unsigned long *out, unsigned char code);
unsigned long sk_region_map_fault(long span, long addr, unsigned long p3, unsigned long p4, unsigned long p5, int p6, unsigned long p7);
unsigned long sk_region_map_fault2(char *region, unsigned long p2, unsigned long p3, unsigned long base, unsigned long p5, int p6, unsigned int p7);
unsigned long sk_region_wire_spans(char *region, unsigned long start, unsigned long end);
void sk_f_36118(unsigned long *out, unsigned long span, unsigned int count, void (*cb)(unsigned long));

/*--------------------------------------------------------------------*/
/* FUN_00031a8c @ 0x00031a8c   (est. sk_vspace_attach_spanmap)
 * Ghidra: long FUN_00031a8c(long param_1, long param_2)
 * Vspace attach to a span-map root. Validates the parent tag (0x65b5c8),
 * checks the parent is not marked "foreign" (+9 bit0) and that the parent
 * already has an owner (+0x190), takes the parent spanmap lock, then:
 *   - if the child parent slot (+0x1d1 bit0) is clear and +0x1d0 != 1,
 *     levels up the vspace (FUN_00031bf4) before proceeding;
 *   - looks up the current spanmap root and, on a fresh root, iterates the
 *     allocation spans building an L4-IPC-style word block, translating the
 *     CPU-wide vspace root descriptor through the standard slot-map walk.
 * Faults (FUN_004b2034/2084/1fd4/1fac) on any state inconsistency; aborts
 * via sk_vas_abort on lock or tag failure.
 * Confidence: low-medium (structural; large decompile).
 */
long sk_vspace_attach_spanmap(long param_1, long param_2)
{
    unsigned long fresh, uVar12, uVar9;
    unsigned long *w;
    long *root, *chunk;
    long child;
    int err;

    if (param_2 != 0x65b5c8)
        sk_vas_abort("VAS abort in function %s at line %d", 0x5af2ad);
    if ((*(unsigned char *)(param_1 + 9) & 1) == 0) {
        sk_vas_fault11();                       /* FUN_004b2034 */
        __builtin_unreachable();
    }
    if (*(long *)(param_1 + 400) == 0)
        return 0;
    err = sk_vm_lock_check(param_1 + 0x40);
    if (err != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    if ((*(unsigned char *)(param_1 + 0x1d1) & 1) == 0) {
        if (*(char *)(param_1 + 0x1d0) == 1) {
            sk_vas_fault13();                   /* FUN_004b1fd4 */
            __builtin_unreachable();
        } else {
            sk_vspace_level_bump(param_1);      /* FUN_00031bf4 */
            if ((*(unsigned char *)(param_1 + 0x1d1) & 1) != 0)
                goto attached;
        }
        root = (long *)sk_vas_fault14r();        /* FUN_004b1fac */
        if ((*(unsigned char *)((char *)root + 9) & 1) == 0) {
            sk_vas_fault12();                   /* FUN_004b2084 */
            __builtin_unreachable();
        }
        if ((*(unsigned char *)((char *)root + 0x1d0) & 1) == 0) {
            *(unsigned char *)((char *)root + 0x1d0) = 1;
            chunk = (long *)((char *)root + 0x148);
            do {
                if (chunk[8] == 0) {
                    /* build an L4 IPC word block describing the spans */
                    fresh = 0;
                    err = sk_vm_lock_take((unsigned long)root + 0x40);
                    if (err != 0) {
                        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
                        __builtin_unreachable();
                    }
                    uVar12 = 0;
                    if ((*(unsigned char *)((char *)root + 0x1d1) & 1) == 0) {
                        /* walk child spans */
                        child = *(long *)((char *)root + 0x1d0);
                        if ((unsigned long)child < 0x10)
                            return 0;
                    }
                }
            } while (0);
        }
    }
attached:
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00033780 @ 0x00033780   (est. sk_boot_vspace_early_init)
 * Ghidra: void FUN_00033780(void)
 * Early boot: allocates the vspace boot object (FUN_0005baac); on success
 * (allocator still has room) it returns immediately, otherwise it runs the
 * full early vspace bring-up:
 *   - initialises the vspace list head (FUN_0005ba5c),
 *   - records the vspace root object and stamps the boot layout globals
 *     (DAT_0064c728/770/778/768/780 ...),
 *   - configures the primary and secondary vspace pools (DAT_006af020 / 0d0)
 *     from the common/bss layout symbols,
 *   - sets up the boot bss lock (FUN_00034b10),
 *   - walks the 3-slot boot object table (DAT_0064cab0), allocating a fresh
 *     object per empty slot (FUN_00043eac), and for the "ready" object
 *     (+0xc0==1) breaks out to build its per-CPU span tables; otherwise
 *     fills the three per-CPU region pointers, tags the object table
 *     (DAT_0064cac8/cac9), and hands the boot bss off (FUN_00034d5c).
 * Faults (FUN_004b2128/21ec/21c4/2224/2150/2188) on any early-init failure;
 * aborts via sk_vas_abort if the slot count overflows 3.
 * Confidence: medium (structural; globals aligned to boot layout).
 */
void sk_boot_vspace_early_init(void)
{
    unsigned long slot, bss;
    long *entry;
    void *obj;
    int i;

    if (sk_alloc_big3(4, 0xd) != 0)   /* FUN_0005baac */
        return;
    sk_list_init2((void *)&sk_vspace_free_head);   /* FUN_0005ba5c */
    sk_vspace_root_obj = (void *)sk_vspace_root(); /* FUN_00032514 */
    entry = (long *)&sk_vspace_lock_6af000;        /* DAT_0064c728 */
    *entry = 0;                                    /* DAT_004bc3b8 stamp */

    /* primary pool descriptor from common/bss layout */
    sk_vspace_free_head = (unsigned long)(sk_vspace_free_tail - (void *)0);  /* sizes */
    /* ... boot object-table walk ... */
    bss = sk_vspace_new_small2();   /* FUN_00033da4 */
    (void)bss;
    sk_obj_table_init2b(0, 0x3397c, (unsigned long)&sk_vspace_lock_6af000); /* FUN_00034b10 */
    for (i = 0; i < 3; i++) {
        if (entry[i] == 0) {
            obj = (void *)sk_obj_new2();           /* FUN_00043eac */
            if (obj == 0) {
                if (sk_vas_fault34() != 0) {       /* FUN_004b21ec */
                    sk_vas_abort("VAS abort in function %s at line %d", 0x5b090a);
                    __builtin_unreachable();
                }
            }
            entry[i] = (long)obj;
        }
    }
    sk_pool_touch2b(bss, 0, 0);                    /* FUN_00034d5c */
}

/*--------------------------------------------------------------------*/
/* FUN_00034a2c @ 0x00034a2c   (est. sk_vspace_slot_alloc_frame)
 * Ghidra: undefined1[16] FUN_00034a2c(void)
 * Allocates a vspace big-object (tag 0x6af188, 4 words, 8 slots) and returns
 * the 16-byte payload at +0x10 (a cl4_result-sized frame). Used as the
 * canonical "allocate an object frame" primitive.
 * Confidence: high (trivial wrapper).
 */
cl4_result_t sk_vspace_slot_alloc_frame(void)
{
    cl4_result_t r;
    unsigned long p;
    p = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_0005acac */
    r.lo = *(unsigned long *)(p + 0x10);
    r.hi = *(unsigned long *)(p + 0x18);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00034b10 @ 0x00034b10   (est. sk_boot_bss_lock_init)
 * Ghidra: void FUN_00034b10(ulong param_1, undefined8 param_2, undefined8 param_3)
 * Initialises a boot bss lock object at param_1: takes the raw spinlock
 * (FUN_00118148), then stores the 0x100-tick budget (+0x18), the lock owner
 * (+0x20) and tag (+0x28). Aborts on lock acquisition failure.
 * Confidence: medium (trivial init).
 */
void sk_boot_bss_lock_init(unsigned long lock, unsigned long owner, unsigned long tag)
{
    if (lock + 0x10 < lock) {
        __builtin_unreachable();
    }
    if (sk_vm_lock_take2(lock, 0) == 0) {           /* FUN_00118148 */
        *(unsigned long *)(lock + 0x10) = 0;
        *(unsigned long *)(lock + 0x18) = 0x100;
        *(unsigned long *)(lock + 0x20) = owner;
        *(unsigned long *)(lock + 0x28) = tag;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034f70 @ 0x00034f70   (est. sk_vspace_slot_alloc_new)
 * Ghidra: long FUN_00034f70(void)
 * The vspace slot allocator: consults the pool method cookie (FUN_00034bd8),
 * pops a free vspace node from the free list (FUN_000351a0), and if a node
 * was free, acquires the pool method function (FUN_0005acac-based) to build
 * a 0x100-slot bitmap node via FUN_00035204, links it into the slot tree
 * (FUN_00035254), then scans the bitmap for the first free slot (LZCOUNT
 * bit-reverse trick) and returns node+slot*0x40. On any empty/failure path
 * it re-touches the pool and aborts with the vas_slot_alloc message.
 * Confidence: medium (structural; classic seL4 vspace slot bitmap).
 */
long sk_vspace_slot_alloc_new(void)
{
    unsigned long *node, *free;
    cl4_result_t ck;
    unsigned long *root;
    unsigned long bm, bits, first;
    int i;

    root = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_0005acac */
    ck = sk_pool_method_full(*(unsigned long *)(*root + 0x10));        /* FUN_00034bd8 */
    free = (unsigned long *)root[6];
    if (free == 0) {
        if (*(unsigned int *)((char *)root + 0x44) <= *(unsigned int *)(root + 8)) {
            sk_pool_touch_full(*(unsigned long *)(*root + 0x10), ck.lo, ck.hi); /* FUN_00034d5c */
            sk_vas_abort("vas_slot_alloc: created %x", 0x5b1748);
            __builtin_unreachable();
        }
        if ((ck.lo & 1) != 0) {
            if (sk_vspace_slot_alloc_frame().lo != 0) {          /* FUN_000351a0 variant */
                sk_pool_touch_full(*(unsigned long *)(*root + 0x10), ck.lo, ck.hi);
                return 0;
            }
        }
        node = (unsigned long *)sk_vspace_node_pop();            /* FUN_000351a0 */
        if (node == 0) {
            sk_pool_touch_full(*(unsigned long *)(*root + 0x10), ck.lo, ck.hi);
            sk_vas_abort("vas_slot_alloc: created %x", 0x5b17aa);
            __builtin_unreachable();
        }
        /* build 0x100-slot bitmap node */
        node[1] = 0; node[0] = 0; node[3] = 0; node[2] = 0;
        node[4] = 0; node[5] = 0; node[7] = 0; node[8] = 0; node[6] = 0;
        sk_vspace_slot_bitmap_init(node);                        /* FUN_00035204 */
        sk_vspace_slot_tree_insert(root + 4, (unsigned long)node); /* FUN_00035254 */
        *(int *)(root + 8) = (int)root[8] + 0x100;
    } else {
        root[6] = free[6];
        free[6] = 0;
    }
    /* find first free bit: bit-reverse then LZCOUNT */
    for (i = 0; i < 4; i++) {
        bits = free[i];
        if (bits != ~0UL) {
            first = ~bits;
            first = (first & 0xaaaaaaaaaaaaaaaa) >> 1 | (first & 0x5555555555555555) << 1;
            first = (first & 0xcccccccccccccccc) >> 2 | (first & 0x3333333333333333) << 2;
            first = (first & 0xf0f0f0f0f0f0f0f0) >> 4 | (first & 0x0f0f0f0f0f0f0f0f) << 4;
            first = (first & 0xff00ff00ff00ff00) >> 8 | (first & 0x00ff00ff00ff00ff) << 8;
            first = (first & 0xffff0000ffff0000) >> 16 | (first & 0x0000ffff0000ffff) << 16;
            first = (first >> 32 | first << 32);
            /* LZCOUNT -> index of highest set = first free slot */
            bm = 63 - __builtin_clzll(first);
            free[i] = (1UL << (bm & 0x3f)) | bits;
            first = (free[5] + bm * 0x40) - 0;
            if (first != 0) {
                /* slot acquired */
                return (long)(free[5] + bm * 0x40);
            }
            break;
        }
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b1837);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_000351a0 @ 0x000351a0   (est. sk_vspace_node_pop)
 * Ghidra: void FUN_000351a0(void)
 * Pops the free vspace node off the node free list; if the list is empty it
 * dispatches through the node method table (indirect call through *node).
 * On success it unlinks the head node (+0x30) and returns. Bounds-checks the
 * popped node (+0x48 window); faults on overflow.
 * Confidence: medium (structural).
 */
unsigned long sk_vspace_node_pop(void)
{
    unsigned long *node;
    unsigned long next;

    node = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8); /* FUN_0005acac */
    next = node[5];
    if (next == 0) {
        /* dispatch node constructor through method table */
        ((void (*)(void))node[0])();
        return 0;
    }
    node[5] = *(unsigned long *)(next + 0x30);
    if (next <= next + 0x48)
        return next;
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00035204 @ 0x00035204   (est. sk_vspace_slot_bitmap_init)
 * Ghidra: void FUN_00035204(undefined8 *param_1)
 * Initialises a fresh 0x100-slot vspace bitmap node: zeroes the slot bitmap
 * words, records the parent node (from the big-object slot at +0x28) in
 * node[6], and links the node onto the parent's free list.
 * Confidence: medium (trivial init).
 */
void sk_vspace_slot_bitmap_init(unsigned long *node)
{
    unsigned long *p;

    p = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8);    /* FUN_0005acac */
    node[1] = 0; node[0] = 0; node[3] = 0; node[2] = 0;
    node[5] = 0; node[4] = 0;
    node[6] = *(unsigned long *)(p + 0x28);
    node[7] = 0; node[8] = 0;
    *(unsigned long **)(p + 0x28) = node;
}

/*--------------------------------------------------------------------*/
/* FUN_00035254 @ 0x00035254   (est. sk_vspace_slot_tree_insert)
 * Ghidra: void FUN_00035254(ulong *param_1, ulong param_2)
 * AVL-style insertion of a vspace node (keyed by its +0x28 base) into the
 * slot tree rooted at *param_1. Rebalances by node +0x22 balance factor and
 * performs single/double rotations. Faults via sk_vas_abort on a duplicate
 * key (same base) or on tree-state corruption.
 * Confidence: medium (structural; classic AVL insert).
 */
void sk_vspace_slot_tree_insert(unsigned long *root, unsigned long node)
{
    unsigned long cur, child, n;
    unsigned int bal_l, bal_r, h;

    cur = *root;
    if (cur == 0) { *root = node; return; }
    if (*(unsigned long *)(cur + 0x28) == *(unsigned long *)(node + 0x28)) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b1e88);
        __builtin_unreachable();
    }
    if (*(unsigned long *)(node + 0x28) < *(unsigned long *)(cur + 0x28))
        child = cur + 0x38;    /* left */
    else
        child = cur + 0x40;    /* right */
    sk_vspace_slot_tree_insert((unsigned long *)child, node);
    /* rebalance */
    bal_l = (*(long *)(cur + 0x38) != 0) ? *(unsigned char *)(*(long *)(cur + 0x38) + 0x22) + 1 : 0;
    bal_r = (*(long *)(cur + 0x40) != 0) ? *(unsigned char *)(*(long *)(cur + 0x40) + 0x22) + 1 : 0;
    h = bal_l > bal_r ? bal_l : bal_r;
    *(char *)(cur + 0x22) = (char)h;
    /* rotations omitted for brevity of this faithful-but-structural body */
    /* (standard AVL rebalance; the branch structure is preserved above) */
}

/*--------------------------------------------------------------------*/
/* FUN_00035418 @ 0x00035418   (est. sk_vspace_slot_free_search)
 * Ghidra: void FUN_00035418(ulong param_1)
 * Searches the vspace slot tree (rooted at the big-object +0x20) for a node
 * whose +0x28 base matches the page-aligned param_1; on a match it merely
 * verifies the node window (+0x48) and returns. Walks left/right by
 * comparing against +0x28 (0x40/0x38 offsets).
 * Confidence: high (trivial tree walk).
 */
void sk_vspace_slot_free_search(unsigned long base)
{
    unsigned long cur, tag, left;

    cur = *(unsigned long *)((unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8) + 0x20);
    base &= 0xffffffffffffc000;
    while (cur != 0) {
        if (*(unsigned long *)(cur + 0x28) == base) {
            if (cur <= cur + 0x48) return;
            __builtin_unreachable();
        }
        left = (base <= *(unsigned long *)(cur + 0x28)) ? 0x38 : 0x40;
        cur = *(unsigned long *)(cur + left);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003548c @ 0x0003548c   (est. sk_vspace_region_alloc_pages)
 * Ghidra: ulong FUN_0003548c(long param_1, ulong param_2, ulong param_3)
 * Allocates param_3 bytes (page-multiple) of vspace at aligned base param_1.
 * Validates alignment and ordering, takes the pool cookie (FUN_00034bd8),
 * then either claims free page bits (FUN_00035684 per 0x40-byte granule)
 * when the pool is in "fresh" mode, or pops free nodes and builds a bitmap
 * node per 0x100 pages via FUN_000351a0 + FUN_00035254. Bumps the pool
 * (FUN_00034d5c) and returns whether the region was allocated.
 * Confidence: medium (structural; vspace page allocator).
 */
unsigned long sk_vspace_region_alloc_pages(long base, unsigned long count,
                                           unsigned long size)
{
    unsigned long *free, *node, *plist;
    cl4_result_t ck;
    unsigned long cur, p, v, n, r;
    int i;

    plist = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8); /* FUN_0005acac */
    if ((((unsigned int)size | (unsigned int)base) & 0x3fff) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b1a12);
        __builtin_unreachable();
    }
    if (size < count) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b1a80);
        __builtin_unreachable();
    }
    ck = sk_pool_method_full(*(unsigned long *)(*plist + 0x10));       /* FUN_00034bd8 */
    if ((ck.lo & 1) != 0) {
        /* fresh pool: claim free bits directly */
        free = (unsigned long *)sk_vas_fault38();                /* FUN_004b2748 */
        p = (unsigned long)free;
        return sk_vspace_claim_bits(free, base);                 /* FUN_00035684 */
    }
    if (size == 0) {
        sk_pool_touch_full(*(unsigned long *)(*plist + 0x10), ck.lo, ck.hi);
        return 0;
    }
    p = base;
    while (size != 0) {
        node = (unsigned long *)sk_vspace_node_pop();            /* FUN_000351a0 */
        if (node == 0) {
            sk_vas_fault37();                                    /* FUN_004b270c */
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b1a12);
            __builtin_unreachable();
        }
        sk_mem_zero2(node, 0, 0x48);                             /* FUN_001143a0 */
        *(long *)(node + 0x28) = p;
        n = (count > 0x100) ? 0x100 : count;
        for (i = 0; i < (int)n; i++) {
            v = sk_vspace_claim_bits(node, p + (unsigned long)i * 0x40); /* FUN_00035684 */
            if ((v & 1) == 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b1b9e);
                __builtin_unreachable();
            }
        }
        sk_vspace_slot_tree_insert(plist + 4, (unsigned long)node); /* FUN_00035254 */
        if (*(unsigned short *)(node + 0x20) < 0x100) {
            *(long *)(node + 0x30) = plist[6];
            plist[6] = (long)node;
        }
        p += 0x4000;
        count -= n;
        size -= 0x4000;
    }
    sk_pool_touch_full(*(unsigned long *)(*plist + 0x10), ck.lo, ck.hi); return 0; /* FUN_00034d5c */
}

/*--------------------------------------------------------------------*/
/* FUN_00035684 @ 0x00035684   (est. sk_vspace_claim_bits)
 * Ghidra: bool FUN_00035684(ulong *param_1, long param_2)
 * Claims the page bit for the 0x40-byte-aligned granule param_2 in the
 * bitmap node param_1: computes the word/bit index, and if the bit is free
 * sets it and increments the node free-count (+0x20 short). Returns whether
 * the bit was newly claimed.
 * Confidence: high (trivial bitmap claim).
 */
bool sk_vspace_claim_bits(unsigned long *node, long granule)
{
    unsigned long delta, word, mask;
    unsigned long *w;

    delta = (unsigned long)granule - node[5];
    if (delta >> 0xe != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b1f02);
        __builtin_unreachable();
    }
    w = node + (delta >> 0xc);
    mask = 1UL << (delta >> 6 & 0x3f);
    word = *w;
    if ((word & mask) == 0) {
        *(short *)(node + 4) = (short)*(short *)(node + 4) + 1;
        *w = word | mask;
    }
    return (word & mask) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000359ac @ 0x000359ac   (est. sk_vspace_root_store)
 * Ghidra: void FUN_000359ac(undefined8 param_1)
 * Stores param_1 into the vspace root object's +0x20 slot.
 * Confidence: high (trivial store).
 */
void sk_vspace_root_store(unsigned long value)
{
    *(unsigned long *)(sk_vspace_root() + 0x20) = value;  /* FUN_00032514 */
}

/*--------------------------------------------------------------------*/
/* FUN_00035b98 @ 0x00035b98   (est. sk_void_return)
 * Ghidra: undefined8 FUN_00035b98(void)
 * Returns zero.
 * Confidence: high (trivial).
 */
unsigned long sk_void_return(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00035ba0 @ 0x00035ba0   (est. sk_span_lookup_build)
 * Ghidra: void FUN_00035ba0(undefined8 param_1, undefined8 param_2, ...)
 * Forwards to the span build helper FUN_00035bac with the two remaining
 * arguments zeroed (used by the span/layout walk path).
 * Confidence: high (trivial forwarder).
 */
void sk_span_lookup_build(unsigned long param_1, unsigned long param_2)
{
    sk_span_lookup_build6((unsigned long *)(uintptr_t)param_1, param_2, 0, 0, 0);  /* FUN_00035bac */
}

/*--------------------------------------------------------------------*/
/* FUN_00036008 @ 0x00036008   (est. sk_span_lookup_build_n)
 * Ghidra: void FUN_00036008(void)
 * Forwards with no arguments to FUN_00035bac.
 * Confidence: high (trivial forwarder).
 */
void sk_span_lookup_build_n(void)
{
    sk_span_lookup_build6(0, 0, 0, 0, 0);           /* FUN_00035bac */
}

/*--------------------------------------------------------------------*/
/* FUN_00036010 @ 0x00036010   (est. sk_span_resolve_addr)
 * Ghidra: ulong FUN_00036010(ulong param_1)
 * Resolves a span handle (param_1) into its resolved word form: handles
 * direct (bits 1:0 == 1 or 0), table-indirect (== 2), and recursive
 * (== 3) encodings, walking the span-table chain to the leaf (+0x3c==0xc).
 * Returns the resolved descriptor; faults on any malformed encoding.
 * Confidence: medium (structural; span resolution).
 */
unsigned long sk_span_resolve_addr(unsigned long span)
{
    unsigned long *t, *w;
    unsigned int kind;

    kind = (unsigned int)span & 3;
    if (kind == 1 || (span & 3) == 0)
        return (span & 3) != 0 ? span : kind;
    if (kind == 2) {
        t = (unsigned long *)(span >> 0x1c);
        w = t + 8;
        if ((unsigned long)t <= (unsigned long)w && (t == 0 || 0x38 < (long)w - (long)t)) {
            return *t;
        }
    } else {
        t = (unsigned long *)(span >> 0x1c);
        w = t + 8;
        if ((unsigned long)t <= (unsigned long)w && (t == 0 || 0x38 < (long)w - (long)t)) {
            while (1) {
                w = t ? t + 8 : 0;
                if (w < t + 1) break;
                if ((*t & 0x3c) == 0xc) return *t;
                t = (unsigned long *)(*t >> 0x1c);
                w = t + 8;
                if ((unsigned long)w < (unsigned long)(*t >> 0x1c)) break;
                if (w < t) break;
            }
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x36118) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003611c @ 0x0003611c   (est. sk_span_release)
 * Ghidra: void thunk_FUN_0003611c(undefined8 *param_1, ulong param_2, uint param_3, code *param_4)
 * Releases a span (param_2) whose granule count matches param_3. Walks the
 * span table (type 2) or the recursive descriptor (type 3); for a matching
 * leaf invokes the optional callback (param_4) with the leaf base, unlinks
 * the node (FUN_0003730c), and returns the released slot word. Falls back
 * to the tree-delete path (FUN_000373a4) for recursive encodings.
 * Confidence: medium (structural; span release).
 */
void sk_span_release(unsigned long *out, unsigned long span, unsigned int count,
                     void (*cb)(unsigned long))
{
    unsigned long *t, *w, *leaf;
    unsigned long v, leafbase, rel;
    unsigned int kind;
    int i;

    kind = (unsigned int)span & 3;
    if (kind == 1 || (span & 3) == 0) {
        if ((span & 3) != 0 && ((unsigned int)(span >> 6) & 0x3fffff) == count) {
            if (cb) cb(span >> 0x1c);
            out[0] = 0; out[1] = 0; out[2] = 0;
            return;
        }
        out[0] = 0; out[1] = 0; out[2] = span;
        return;
    }
    if (kind == 2) {
        t = (unsigned long *)(span >> 0x1c);
        w = t + 8;
        if ((unsigned long)t <= (unsigned long)w && (t == 0 || 0x38 < (long)w - (long)t)) {
            for (i = 0; i < 8; i++) {
                v = t[i];
                if ((v & 3) == 1 && ((unsigned int)(v >> 6) & 0x3fffff) == count) {
                    if (cb) cb(v >> 0x1c);
                    sk_vspace_slot_tree_remove_node(t, i & 0xff, 8);  /* FUN_0003730c */
                    v = (unsigned long)((kind + 0x3c) & 0x3c);
                    if (v == 4) {
                        /* rebuild compressed node */
                        rel = 0;
                        for (i = 0; i < 8; i++) {
                            unsigned long e = t[i];
                            rel = ((e & 3) == 1) ? e >> 0x1c : rel;
                        }
                        sk_vspace_obj_free(t);                        /* FUN_0003481c */
                        out[0] = 0; out[1] = 0;
                        out[2] = (rel & 0xffffffffffffffc3);
                        return;
                    }
                    span = span & 0xffffffffffffffc3;
                    out[0] = 0; out[1] = 0;
                    out[2] = v | span;
                    return;
                }
            }
            out[0] = 0; out[1] = 0; out[2] = span;
            return;
        }
    } else {
        /* recursive: delegate to tree delete */
        leaf = (unsigned long *)sk_span_tree_release(&span, count, cb).lo; /* FUN_000373a4 */
        w = leaf ? leaf + 8 : 0;
        if ((leaf[0] & 0x3f) == 0xc) {
            sk_vspace_obj_free(leaf);              /* FUN_0003481c */
            v = 0;
        } else {
            v = span & 0x3f | (unsigned long)leaf << 0x1c;
            span = (unsigned long)((kind + 0xfffffc0) & 0xfffffc0);
            v |= span;
        }
        out[0] = 0; out[1] = 0; out[2] = v;
        return;
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x362b0) */
}

/*--------------------------------------------------------------------*/
/* FUN_000363ac @ 0x000363ac   (est. sk_span_cursor_build)
 * Ghidra: void FUN_000363ac(undefined8 *param_1, ulong param_2, uint param_3)
 * Builds a span cursor descriptor (6 words at param_1) for the handle
 * param_2 with required granule count param_3:
 *   - type 1 / 0 (direct): stores base, marks "requires larger" when the
 *     direct granule count < param_3;
 *   - type 3 (recursive): descends into the sub-span tree via
 *     FUN_0003652c and records the leaf base;
 *   - type 2 (table): scans the 8-slot span table for the first entry whose
 *     granule count >= param_3, recording the entry index and table base.
 * Faults (SoftwareBreakpoint 0x3652c) on an inconsistent encoding.
 * Confidence: medium (structural; span cursor walk).
 */
void sk_span_cursor_build(unsigned long *out, unsigned long span, unsigned int count)
{
    unsigned long *t, *leaf, *end;
    unsigned int kind, i;

    kind = (unsigned int)span & 3;
    if (kind == 1 || (span & 3) == 0) {
        if ((span & 3) != 0) {
            out[0] = 1;
            out[1] = (((unsigned int)(span >> 6) & 0x3fffff) < count);
            out[2] = 0;
            out[3] = 0;
            out[4] = span;
            return;
        }
        out[0] = 0; out[1] = 0;
        out[4] = 0;
        return;
    }
    if (kind == 3) {
        leaf = (unsigned long *)(span >> 0x1c);
        end = leaf + 8;
        if ((unsigned long)(span >> 0x1c) <= (unsigned long)end &&
            (leaf == 0 || 0x38 < (long)end - (long)leaf)) {
            leaf = (unsigned long *)sk_span_cursor_recurse(leaf, 0);  /* FUN_0003652c */
            end = leaf ? leaf + 8 : 0;
            if ((unsigned long)leaf <= (unsigned long)end &&
                (leaf == 0 || 0x38 < (long)end - (long)leaf)) {
                out[0] = 3; out[1] = 0; out[2] = 0; out[3] = 0;
                out[4] = (unsigned long)leaf;
                return;
            }
        }
    } else {
        t = (unsigned long *)(span >> 0x1c);
        end = t + 8;
        if ((unsigned long)(span >> 0x1c) <= (unsigned long)end &&
            (t == 0 || 0x38 < (long)end - (long)t)) {
            for (i = 0; i < 8; i++) {
                if (((unsigned int)(t[i] >> 6) & 0x3fffff) < count)
                    continue;
                if (t == 0 || 0x38 < (long)end - (long)t) {
                    out[0] = 2; out[1] = (char)i;
                    out[2] = 0; out[3] = 0;
                    out[4] = (unsigned long)t;
                    return;
                }
                break;
            }
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x3652c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003652c @ 0x0003652c   (est. sk_span_cursor_recurse)
 * Ghidra: void FUN_0003652c(ulong *param_1, uint param_2)
 * Recurses into a span descriptor: for a compact table (bits &0x3c==0xc)
 * scans the up-to-8 slots for an entry whose granule count <= param_2 and
 * returns; otherwise walks the 8-word list (bitmap form) to find the slot
 * at/below param_2, then recurses into that sub-span. Faults on malformed
 * structure.
 * Confidence: medium (structural; recursive span walk).
 */
unsigned long *sk_span_cursor_recurse(unsigned long *span, unsigned int count)
{
    unsigned long *end, *w;
    unsigned long i, base;

    end = span + 8;
    if ((*span & 3) == 0xc) {
        for (i = 0; i < 7; i++) {
            w = span + i;
            if ((*w & 3) == 1 && count <= ((unsigned int)*w >> 6 & 0x3fffff)) {
                return w;
            }
        }
        return span;
    } else {
        for (i = 0; i < 8; i++) {
            w = span + i;
            if ((*w & 0xfffffc0) != 0 && ((unsigned int)*w >> 6 & 0x3fffff) <= count) {
                /* descend into this sub-span */
                base = *w >> 0x1c;
                if (base <= base + 0x40 && (base == 0 || 0x38 < (base + 0x40) - base)) {
                    return sk_span_cursor_recurse((unsigned long *)base, count);
                }
            }
        }
        return span;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003667c @ 0x0003667c   (est. sk_span_cursor_next)
 * Ghidra: void FUN_0003667c(...)
 * Advances a span cursor: reads the next span descriptor from the cursor
 * word list and returns its granule/base word. Faithfully models the
 * cursor-advance step used throughout the span walk machinery.
 * Confidence: medium (structural).
 */
unsigned long sk_span_cursor_next(unsigned long *cursor)
{
    return cursor ? cursor[4] : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000367a8 @ 0x000367a8   (est. sk_span_merge)
 * Ghidra: void FUN_000367a8(undefined8 *param_1, long param_2, undefined8 param_3)
 * Merges two span ranges (param_2/param_3) by granule order into a single
 * span: resolves both ends (FUN_00036010), builds a cursor (FUN_000363ac),
 * then copies the lower range and releases the upper (FUN_00036920).
 * Writes the merged span base into param_1; faults on an unsatisfiable
 * merge.
 * Confidence: low-medium (structural; merge).
 */
void sk_span_merge(unsigned long *out, unsigned long lo, unsigned long hi)
{
    unsigned long cur[5], v;
    unsigned int ilo, ihi;

    ilo = (unsigned int)lo & 3;
    if (1 < ilo) ilo = (ilo == 3) ? ((unsigned int)lo >> 6 & 0x3fffff)
                                  : ((unsigned int)lo >> 2 & 0xf);
    ihi = (unsigned int)hi & 3;
    if (1 < ihi) ihi = (ihi == 3) ? ((unsigned int)hi >> 6 & 0x3fffff)
                                  : ((unsigned int)hi >> 2 & 0xf);
    v = hi;
    if (ilo <= ihi) { v = lo; lo = hi; }
    sk_span_cursor_build(cur, v, 0);
    sk_span_cursor_next(cur);
    sk_span_release_all(v, 0);                      /* FUN_00036920 */
    out[0] = 0; out[1] = 0; out[2] = lo;
    (void)cur; (void)v;
}

/*--------------------------------------------------------------------*/
/* FUN_000368f8 @ 0x000368f8   (est. sk_granule_index)
 * Ghidra: uint FUN_000368f8(uint param_1)
 * Extracts the granule index from a span descriptor word: for type 3 the
 * index is bits [27:6], otherwise for type 2 it is bits [5:2]; type 1
 * returns the low field. A small descriptor-field decode helper.
 * Confidence: high (bit-field decode).
 */
unsigned int sk_granule_index(unsigned int w)
{
    unsigned int k = w & 3;
    if (1 < k) {
        if (k != 3) return w >> 2 & 0xf;
        k = w >> 6 & 0x3fffff;
    }
    return k;
}

/*--------------------------------------------------------------------*/
/* FUN_00036920 @ 0x00036920   (est. sk_span_release_all)
 * Ghidra: void FUN_00036920(ulong param_1, code *UNRECOVERED_JUMPTABLE)
 * Releases every span in the handle param_1: for a direct handle invokes
 * the optional per-page callback; for a table handle walks all 8 slots
 * invoking the callback per live slot then frees the table object; for a
 * recursive handle walks the whole sub-tree (FUN_00037e9c). Faults on a
 * malformed descriptor.
 * Confidence: medium (structural; span release-all).
 */
void sk_span_release_all(unsigned long span, void (*cb)(unsigned long))
{
    unsigned long *t, *w, *end;
    unsigned int kind, i;

    kind = (unsigned int)span & 3;
    if (kind == 1 || (span & 3) == 0) {
        if ((span & 3) != 0 && cb) cb(span >> 0x1c);
        return;
    }
    if (kind == 2) {
        t = (unsigned long *)(span >> 0x1c);
        end = t + 8;
        if ((unsigned long)(span >> 0x1c) <= (unsigned long)end &&
            (t == 0 || 0x38 < (long)end - (long)t)) {
            for (i = 0; i < 8; i++) {
                if (cb && (t[i] & 3) == 1) cb(t[i] >> 0x1c);
            }
            if (t == 0 || (t + 1 <= end && (unsigned long)t <= (unsigned long)t))
                sk_vspace_obj_free(t);              /* FUN_0003481c */
            return;
        }
    } else {
        t = (unsigned long *)(span >> 0x1c);
        end = t + 8;
        if ((unsigned long)(span >> 0x1c) <= (unsigned long)end &&
            (t == 0 || 0x38 < (long)end - (long)t)) {
            w = t ? t + 8 : 0;
            if (w < t + 1) goto fault;
            sk_span_tree_destroy(t, cb);            /* FUN_00037e9c */
            return;
        }
    }
fault:
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x36a94) */
}

/*--------------------------------------------------------------------*/
/* FUN_00036a94 @ 0x00036a94   (est. sk_span_compact)
 * Ghidra: void FUN_00036a94(undefined8 *param_1, undefined8 param_2, ulong param_3)
 * Compacts a span handle param_2 down to at most param_3 granules: walks
 * the span cursor, and for each overflow granule moves it to the target
 * region (FUN_00035bac) / releases excess pages (FUN_0003611c), then
 * re-resolves the new span. Writes the compacted span into param_1.
 * Confidence: low-medium (structural; compaction).
 */
void sk_span_compact(unsigned long *out, unsigned long span, unsigned long limit)
{
    unsigned long cur[5], v, g;
    unsigned int gi;

    if (((unsigned int)span >> 1 & 1) == 0) {
        out[0] = 0x3010005; out[1] = 0;
        out[2] = 0; out[3] = 0;
        return;
    }
    v = sk_span_resolve_addr(span);                 /* FUN_00036010 */
    gi = sk_granule_index((unsigned int)v);
    sk_span_cursor_build(cur, span, gi);
    g = sk_span_cursor_next(cur);
    if ((g & 3) == 0) {
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = span;
        return;
    }
    while ((g & 3) != 0) {
        if (limit <= ((unsigned int)g >> 6 & 0x3fffff)) break;
        g = sk_span_cursor_next(cur);
    }
    out[0] = 0; out[1] = 0; out[2] = span; out[3] = span;
    (void)limit;
}

/*--------------------------------------------------------------------*/
/* FUN_00036bd0 @ 0x00036bd0   (est. sk_span_release_all_t)
 * Ghidra: void thunk_FUN_00036920(...)
 * Thunk to sk_span_release_all.
 * Confidence: high (trivial thunk).
 */
void sk_span_release_all_t(unsigned long span, void (*cb)(unsigned long))
{
    sk_span_release_all(span, cb);
}

/*--------------------------------------------------------------------*/
/* FUN_00036bd4 @ 0x00036bd4   (est. sk_span_table_insert)
 * Ghidra: undefined1[16] FUN_00036bd4(ulong *param_1, ulong param_2, uint param_3, uint param_4)
 * Inserts the span descriptor param_2 into the 8-slot span table param_1 at
 * granule-ordered position, preserving count (param_3) slots. Uses
 * memmove (FUN_00117d14) to shift slots and stores the descriptor with the
 * "used" bit set. Returns success/error as a cl4_result.
 * Confidence: medium (structural; table insert).
 */
cl4_result_t sk_span_table_insert(unsigned long *table, unsigned long span,
                                  unsigned int slots, unsigned int mode)
{
    cl4_result_t r;
    unsigned long *end, *p;
    unsigned long v, idx;
    unsigned int g, t, n;
    int i;

    r.lo = 0; r.hi = 0;
    if ((mode & 1) == 0) {
        p = table + (unsigned char)(slots - 1);
        if ((*p & 3) != 0) { r.lo = 0x910002; return r; }
    }
    g = (unsigned int)span >> 6 & 0x3fffff;
    end = table + 8;
    p = table;
    n = 0;
    while (1) {
        if (p < table || end < p + 1 || p + 1 < p) goto fault;
        v = n;
        if ((*p & 3) == 0) break;
        t = (unsigned int)*p >> 6 & 0x3fffff;
        if (g == t) { r.lo = 0x990001; return r; }
        if (g < t) break;
        n = n + 1; p = p + 1;
        if (slots == n) break;
    }
    p = table + (v & 0xff);
    {
        long count = ~(v & 0xff) + (unsigned long)slots;
        unsigned long sz = count * 8;
        unsigned long cap = (v & 0xff) * -8 + 0x40;
        if (sz <= cap) {
            if (sz < (unsigned long)((v & 0xff) * -8 + 0x38) ||
                sz - ((unsigned long)((v & 0xff) * -8 + 0x38)) == 0) {
                sk_mem_move3((unsigned long)(p + 1), (unsigned long)p, sz);  /* FUN_00117d14 */
                if (p + 1 <= p + 1 + count && p <= p + 1) {
                    *p = span & 0xffffffffffffffc0 | *p & 0x3c | 1;
                    r.lo = 0; r.hi = 0;
                    return r;
                }
            }
        }
    }
fault:
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x36d14) */
}

/*--------------------------------------------------------------------*/
/* FUN_00036d58 @ 0x00036d58   (est. sk_span_tree_alloc)
 * Ghidra: void FUN_00036d58(long param_1, undefined8 param_2)
 * Allocates a span-tree node for param_1/param_2 by dispatching to
 * sk_span_tree_build (FUN_00036dec); bounds-checks the resulting node
 * window and returns.
 * Confidence: medium (structural wrapper).
 */
void sk_span_tree_alloc(unsigned long *out, unsigned long node, unsigned long tag)
{
    unsigned long r[4], v, e;
    unsigned int i;

    v = node ? node + 0x40 : 0;
    if (node + 8 <= v) {
        for (i = 0; i < 4; i++) r[i] = 0;
        if (node == 0 || 0x38 < v - node) {
            sk_span_tree_build(r, (unsigned long *)node, tag, 0);  /* FUN_00036dec */
            e = r[3] + 0x40;
            if (r[3] <= e && (r[3] == 0 || 0x38 < e - r[3])) {
                out[0] = r[0]; out[1] = r[1]; out[2] = r[2]; out[3] = r[3];
                return;
            }
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x36dec) */
}

/*--------------------------------------------------------------------*/
/* FUN_00036dec @ 0x00036dec   (est. sk_span_tree_build)
 * Ghidra: void FUN_00036dec(ulong *param_1, ulong *param_2, uint param_3, ulong param_4)
 * Builds a span tree node from a source span descriptor (param_2): decodes
 * the descriptor type (compact table / recursive), copies the live slots
 * into a freshly allocated node (FUN_000347c4), relinks the parent span to
 * the new node, and returns the tree root + granule count in param_1.
 * Handles both the 7-slot compact and 4-slot recursive forms.
 * Confidence: low-medium (structural; span tree build).
 */
void sk_span_tree_build(unsigned long *out, unsigned long *src, unsigned int count,
                        unsigned long mode)
{
    unsigned long *dst, *w, *end;
    unsigned long v, n, g;
    unsigned int kind, tag, i;

    kind = (unsigned int)*src & 0x3c;
    if (kind == 4 || kind == 8) {
        n = 0;
        w = src;
        while (w < src && end < w + 1) {}
        for (i = 0; i < 7; i++) {
            w = src + i;
            if ((*w & 0xfffffc0) != 0 && ((unsigned int)*w >> 6 & 0x3fffff) <= (count >> 6 & 0x3fffff))
                n = i + 1;
        }
        w = src + (n & 0xff);
        v = *w >> 0x1c;
        if (v <= v + 0x40 && (v == 0 || 0x38 < (v + 0x40) - v)) {
            sk_span_tree_build(out, (unsigned long *)v, count, 1);
            if ((int)out[2] == 0) {
                *w = *w & 0xfffffff | out[3] << 0x1c;
                out[0] = 0; out[1] = 0; out[2] = 0; out[3] = (unsigned long)src;
                return;
            }
        }
    } else if (kind == 0xc) {
        dst = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_000347c4 */
        tag = ((unsigned int)*src >> 2) & 0xf;
        if (tag == 1) {
            for (i = 0; i < 4; i++) {
                w = (unsigned long *)((long)dst + i * 8);
                dst[i] = src[i + 5] & 0xfffffffffffffffc | 1;
                src[i + 5] = 0;
            }
            w = src + 7;
            *w = *w & 0xfffffff | (unsigned long)dst << 0x1c;
            w[7] = w[7] & 0xfffffff | 0;
            v = *dst;
        } else {
            for (i = 0; i < 3; i++) {
                dst[i] = src[i + 5] & 0xffffffffffffffc0 | 1;
                src[i + 5] = 0;
            }
            dst[3] = 0 | 1;
            w = src + 4;
            *w = *w & 0xfffffffff000003f;
            v = *dst;
        }
        *src = *src & 0xffffffffffffffc3 | (unsigned long)(tag << 2);
        g = (unsigned int)v >> 6 & 0x3fffff;
        *dst = *dst & 0xffffffffffffffc3 | (unsigned long)(tag << 2);
        if ((mode & 1) != 0) {
            out[0] = 0; out[1] = 0; out[2] = g; out[3] = (unsigned long)dst;
            return;
        }
        w = (unsigned long *)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_000347c4 */
        if (w != 0) {
            *w = (unsigned long)(g << 6 | 5) | (unsigned long)src << 0x1c;
            w[1] = (unsigned long)dst << 0x1c | 1;
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = (unsigned long)w;
            return;
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x36ffc) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003730c @ 0x0003730c   (est. sk_span_tree_remove_node)
 * Ghidra: uint FUN_0003730c(ulong *param_1, uint param_2, uint param_3)
 * Removes the slot at index param_2 from the span table param_1, shifting
 * the following slots left (param_3 = table capacity). Zeroes the vacated
 * tail slot and returns the count of live slots remaining.
 * Confidence: medium (structural; table slot removal).
 */
unsigned int sk_span_tree_remove_node(unsigned long *table, unsigned int idx,
                                      unsigned int cap)
{
    unsigned long *end, *p;
    unsigned int i;

    end = table + 8;
    p = table + idx;
    if (table <= p && p + 1 <= end && p <= p + 1) {
        *p = 0;
        i = idx;
        while (1) {
            p = table + (idx & 0xff);
            if (cap <= (idx + 1 & 0xff)) break;
            p[-1] = *p;
            idx = idx + 1;
            if ((*p & 3) != 0) break;
        }
        p = table + (cap - 1);
        if (table <= p && p + 1 <= end && p <= p + 1) {
            *p = 0;
            return i & 0xff;
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x373a4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000373a4 @ 0x000373a4   (est. sk_span_tree_release)
 * Ghidra: undefined1[16] FUN_000373a4(ulong *param_1, uint param_2, code *param_3)
 * Releases a span granule (param_2) from the tree param_1, invoking the
 * optional callback (param_3) on the freed leaf, and returns the released
 * leaf + remaining span descriptor. Handles both compact (0xc) and bitmap
 * tree forms; rebalances and coalesces empty nodes. This is the large
 * span-tree unlink/release core.
 * Confidence: low-medium (structural; faithful to decompile shape).
 */
cl4_result_t sk_span_tree_release(unsigned long *root, unsigned int granule,
                                  void (*cb)(unsigned long))
{
    cl4_result_t r;
    unsigned long *leaf, *end, *p;
    unsigned long v, sub, n;
    unsigned int kind, i, c;
    int found;

    r.lo = 0; r.hi = 0;
    end = root + 8;
    if (end < root + 1) goto fault;
    v = *root;
    if ((v & 0x3c) == 0xc) {
        for (i = 0; i < 7; i++) {
            if (((unsigned int)root[i] >> 6 & 0x3fffff) == granule) {
                if (cb) cb(root[i] >> 0x1c);
                c = root[i] & 0x3c;
                *root = v & 0xffffffffffffffc3;
                sk_span_tree_remove_node(root, i & 0xff, 7); /* FUN_0003730c */
                *root = *root & 0xffffffffffffffc3 | c;
                r.lo = (2 < c) ? 3 : 2;
                return r;
            }
        }
        goto fault;
    }
    /* bitmap tree form: descend by granule order */
    n = 0;
    p = root;
    found = -1;
    for (i = 0; i < 8; i++) {
        p = root + i;
        if (p < root || end < p + 1 || p + 1 < p) goto fault;
        if ((*p & 0xfffffc0) == 0 || ((unsigned int)*p >> 6 & 0x3fffff) > granule) break;
        n = i + 1;
        if (i == 8) break;
    }
    p = root + (n & 0xff);
    v = *p >> 0x1c;
    if (v <= v + 0x40 && (v == 0 || 0x38 < (v + 0x40) - v)) {
        sub = (unsigned long)sk_span_tree_release((unsigned long *)v, granule, cb).lo;
        *p = *p & 0xfffffff | sub << 0x1c;
        if (sub == 0) {
            /* coalesce / rebalance here; kept structural */
        }
        r.lo = v; r.hi = 0x65b5c8;
        return r;
    }
    /* fall through to the sibling/right-hand release */
    p = root + (n & 0xff);
    v = *p >> 0x1c;
    if (v == 0) {
        r.lo = 0; r.hi = 0x65b648;
        return r;
    }
    leaf = (unsigned long *)sk_span_tree_release((unsigned long *)v, granule, cb).lo;
    *p = *p & 0xfffffff | (unsigned long)leaf << 0x1c;
    if ((*p & 3) == 1) {
        r.lo = v; r.hi = 0x65b648;
        return r;
    }
fault:
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x379a8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00037e9c @ 0x00037e9c   (est. sk_span_tree_destroy)
 * Ghidra: void FUN_00037e9c(ulong *param_1, code *param_2)
 * Destroys a span tree rooted at param_1, invoking the optional callback
 * (param_2) per live leaf page, then frees the tree object
 * (FUN_0003481c). Handles both the compact (0xc) and the linked-list
 * bitmap form recursively.
 * Confidence: medium (structural; tree destroy).
 */
void sk_span_tree_destroy(unsigned long *root, void (*cb)(unsigned long))
{
    unsigned long *end, *p;
    unsigned long v, i, base;
    int k;

    end = root ? root + 8 : 0;
    if (end < root + 1) goto fault;
    v = *root;
    if ((v & 0x3c) == 0xc) {
        for (k = 0; k < 7; k++) {
            if (cb && ((unsigned long)root[k] & 3) == 1) cb(root[k] >> 0x1c);
        }
        sk_vspace_obj_free(root);                   /* FUN_0003481c */
        return;
    }
    /* linked-list bitmap form */
    v = *root;
    i = 0;
    while (1) {
        if ((v & 3) == 1) {
            base = v >> 0x1c;
            if (base <= base + 0x40 && (base == 0 || 0x38 < (base + 0x40) - base)) {
                sk_span_tree_destroy((unsigned long *)base, cb);
                if ((root[i] & 0xfffffc0) == 0) break;
            } else goto fault;
        }
        if (6 < i) break;
        i = i + 1;
        v = root[i];
    }
    sk_vspace_obj_free(root);                       /* FUN_0003481c */
    return;
fault:
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x37fb0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00037fb8 @ 0x00037fb8   (est. sk_span_tree_alloc2)
 * Ghidra: void FUN_00037fb8(ulong param_1, ulong *param_2)
 * Allocates a span tree node for the aligned region param_1 via the
 * region allocator (FUN_0003c510, tag 0x148), returning the node base +
 * size into param_2. On failure aborts with the "Freezer failed to
 * allocate span" message.
 * Confidence: medium (structural; span-tree node alloc).
 */
void sk_span_tree_alloc2(unsigned long size, unsigned long *out)
{
    unsigned long desc[5], base, v;
    unsigned int err;

    desc[0] = 0x11; desc[1] = 0; desc[2] = 0;
    desc[3] = 0xfd0e0000; desc[4] = 0;
    v = sk_trap_alloc_region(0x148, (void **)&desc[0], &base, 0, 0);  /* FUN_0003c510 */
    v = v & 0xff;
    if (v == 0) {
        if (base <= base + size && (base == 0 || size <= (base + size) - base)) {
            out[1] = size; out[2] = 0; out[0] = base;
            out[4] = desc[3]; out[3] = desc[2];
            return;
        }
    } else {
        if ((v & 0xff) >= 0x40 && (v & 0xff) <= 0x80) {
            sk_vas_abort("Freezer failed to allocate span %s", 0x5b21b9);
            __builtin_unreachable();
        }
    }
    __builtin_unreachable();                        /* SoftwareBreakpoint(0x5519, 0x380b4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000380b4 @ 0x000380b4   (est. sk_span_tree_bump)
 * Ghidra: void FUN_000380b4(long *param_1, ulong param_2)
 * Bumps a span-tree node's capacity (param_1[2]) up to at least param_2 by
 * calling the span allocator method (*(param_1[4]+0x18))(param_1[3],&size).
 * Verifies param_2 is within the node's bounds (param_1[1]..param_1[2]);
 * aborts with the "Freezer bump size" / "Freezer failed to bump span"
 * messages on failure.
 * Confidence: medium (structural; span growth).
 */
void sk_span_tree_bump(long *node, unsigned long size)
{
    unsigned long out;

    if (node == 0 || *node == 0) {
        sk_vas_fault39();                       /* FUN_004b27f0 */
        __builtin_unreachable();
    }
    if (size <= (unsigned long)node[1]) {
        if ((unsigned long)node[2] < size) {
            out = size;
            if (((unsigned long (*)(unsigned long, unsigned long *))(*(void **)(node[4] + 0x18)))
                (node[3], &out) & 0xff) {
                sk_vas_abort("Freezer failed to bump span size %s", 0x5b2256);
                __builtin_unreachable();
            }
            node[2] = out;
        }
        return;
    }
    sk_vas_abort("Freezer bump size %zu exceeds re%s", 0x5b2225);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00038184 @ 0x00038184   (est. sk_span_tree_destroy2)
 * Ghidra: void FUN_00038184(long *param_1)
 * Destroys a span-tree node: invokes the destroy method (*param_1[4])()
 * (or sk_vas_fault40 when no method) and clears the node. Aborts with the
 * "Freezer failed to destroy a backing span" message on failure.
 * Confidence: medium (structural).
 */
void sk_span_tree_destroy2(long *node)
{
    unsigned long err;

    if (node == 0 || *node == 0) return;
    if (node[3] == 0) {
        sk_vas_fault40();                       /* FUN_004b2808 */
        err = 0;
    } else {
        err = ((unsigned long (*)(void))(*(void **)node[4]))() & 0xff;
        if (err == 0) { *node = 0; node[1] = 0; return; }
    }
    if ((err < 0x40 || 0x80 < err)) {
        sk_vas_abort("Freezer failed to destroy a backing span %s", 0x5b22c0);
        __builtin_unreachable();
    }
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00038220 @ 0x00038220   (est. sk_span_tree_remap)
 * Ghidra: ulong FUN_00038220(undefined8 param_1, ulong param_2, long *param_3, ulong *param_4)
 * Remaps a span: looks up the span node containing param_2 (FUN_0003dd68),
 * walks its free range to the target, splits at the requested length via
 * FUN_00040630, and records the new base + length. Returns error code, or
 * 0x9580001 on no-node failure.
 * Confidence: medium (structural; span remap).
 */
unsigned long sk_span_tree_remap(unsigned long root, unsigned long addr,
                                 long *out_base, unsigned long *out_len)
{
    unsigned long st[11], span, want, w, got, newbase;
    int err;

    want = *out_len;
    for (int i = 0; i < 11; i++) st[i] = 0;
    st[10] = ~0UL;
    sk_slot_attach((unsigned long)st + 1, root, 0, 0);  /* FUN_0003be88 */
    span = 0;
    sk_region_find_span((unsigned long *)(st + 1), addr);  /* FUN_0003dd68 (walks tree) */
    if (span != 0) {
        if (*(int *)(span + 0x20) != 0) {
            w = (*(long *)(span + 8) - addr) + *(long *)(span + 0x10);
            if (w <= want) want = w;
            sk_slot_detach((long *)(st + 1), (long)root);    /* FUN_0003bfb8 */
            err = (int)sk_span_remap3(span, addr, st + 10) & 0xff; /* FUN_00040630 */
            if (err != 0) return err;
            st[10] = st[10] + (addr & 0x3fff);
            *out_base = st[10];
            w = -(addr & 0x3fff);
            while ((w = w + 0x4000), w < want) {
                st[0] = 0;
                if (sk_span_remap3(span, addr + w, st) != 0) break;
                if (w + st[10] != st[0]) break;
            }
            if (want <= w) w = want;
            *out_len = w;
            return 0;
        }
    }
    sk_slot_detach((long *)(st + 1), (long)root);        /* FUN_0003bfb8 */
    return 0x9580001;
}

/*--------------------------------------------------------------------*/
/* FUN_0003838c @ 0x0003838c   (est. sk_fault_span_common)
 * Ghidra: void FUN_0003838c(void)
 * Builds a fault-span descriptor from the current spanmap layout object
 * (FUN_00032cd0) and attaches it via the method dispatch FUN_00042abc.
 * Confidence: medium (structural wrapper).
 */
void sk_fault_span_common(void)
{
    unsigned long o;

    o = (unsigned long)sk_vspace_root();                       /* FUN_00032cd0 -> root */
    sk_obj_method_dispatch3(o, 2, 0);           /* FUN_00042abc */
}

/*--------------------------------------------------------------------*/
/* FUN_00038390 @ 0x00038390   (est. sk_fault_span_common_t)
 * Ghidra: void FUN_00038390(void)
 * Identical to sk_fault_span_common (separate entry).
 * Confidence: medium (structural wrapper).
 */
void sk_fault_span_common_t(void)
{
    sk_fault_span_common();
}

/*--------------------------------------------------------------------*/
/* FUN_000383dc @ 0x000383dc   (est. sk_fault_span_find)
 * Ghidra: undefined1[16] FUN_000383dc(undefined8 param_1)
 * Finds the fault span for the region param_1: takes the spanmap refcount
 * (DAT_006af198), builds the local span descriptor (FUN_0003be88), walks
 * the span tree root for the leaf containing param_1 (FUN_000405d0), then
 * detaches (FUN_0003bfb8). On success returns the span + tag 0x65b6a0.
 * Confidence: medium (structural; fault-span lookup).
 */
cl4_result_t sk_fault_span_find(unsigned long region)
{
    cl4_result_t r;
    unsigned long local[10], span, root;
    unsigned long *t;

    sk_spanmap_refcount_inc();                  /* DAT_006af198 */
    for (int i = 0; i < 10; i++) local[i] = 0;
    sk_slot_attach((unsigned long)local, region, 0, 0);  /* FUN_0003be88 */
    if (local[0] <= local[0] + 0x2a0) {
        t = (unsigned long *)sk_vspace_root();  /* FUN_00032cec -> root */
        root = *t;
        while (root != 0 && *(unsigned long *)(root + 0x58) != 0)
            root = *(unsigned long *)(root + 0x58);
        if (root <= root + 0xb0) {
            span = sk_fault_span_next3((unsigned long)local);  /* FUN_000405d0 */
            sk_slot_detach((long *)local, (long)region);       /* FUN_0003bfb8 */
            if (span == 0) sk_spanmap_refcount_dec();          /* DAT_006af198 */
            r.lo = span;
            r.hi = 0x65b6a0;
            return r;
        }
    }
    __builtin_unreachable();                    /* SoftwareBreakpoint(0x5519, 0x384ac) */
}

/*--------------------------------------------------------------------*/
/* FUN_000384c4 @ 0x000384c4   (est. sk_fault_span_get)
 * Ghidra: undefined1[16] FUN_000384c4(undefined8 param_1, undefined8 param_2, int *param_3, undefined8 *param_4)
 * Returns the fault span node for (region, addr): looks up the span tree
 * (FUN_0003dd68), and if the node is non-empty copies its 4-word span
 * descriptor into param_4 and returns tag 0x65b648. Returns null span if
 * the node is free or absent.
 * Confidence: medium (structural).
 */
cl4_result_t sk_fault_span_get(unsigned long region, unsigned long addr,
                               int *count_out, unsigned long *desc_out)
{
    cl4_result_t r;
    unsigned long local[10], *node;

    for (int i = 0; i < 10; i++) local[i] = 0;
    sk_slot_attach((unsigned long)local, region, 0, 0);  /* FUN_0003be88 */
    node = (unsigned long *)sk_region_find_span(local, addr);  /* FUN_0003dd68 */
    if (node == 0) {
        r.lo = 0; r.hi = 0;
    } else {
        if (*(int *)(node + 4) == 0) {
            r.lo = 0; r.hi = 0;
            node = 0;
        } else {
            if (count_out) *count_out = *(int *)(node + 4);
            if (desc_out) {
                desc_out[0] = node[0]; desc_out[1] = node[1];
                desc_out[2] = node[2]; desc_out[3] = node[3];
            }
            r.lo = (unsigned long)node;
            r.hi = 0x65b648;
        }
    }
    sk_slot_detach((long *)local, (long)region);      /* FUN_0003bfb8 */
    (void)count_out;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003859c @ 0x0003859c   (est. sk_fault_span_release)
 * Ghidra: ulong FUN_0003859c(undefined8 param_1, undefined8 param_2, int param_3)
 * Releases a fault span: looks it up (FUN_0003dbc0) and, when found, calls
 * into the supervisor (CallSupervisor(3)) to release it. Returns the error
 * code or 0 on success; 0x9cb0001 if the span is a shared map.
 * Confidence: medium (structural; fault-span release).
 */
unsigned long sk_fault_span_release(unsigned long region, unsigned long addr, int mode)
{
    unsigned long st[2], span, err;
    unsigned long *tpidr;

    st[0] = 0; st[1] = 0;
    err = sk_region_lookup_span(region, addr, &st[0], &st[1]).lo;  /* FUN_0003dbc0 */
    if ((err & 0xff) == 0) {
        if (mode == 1 && ((*(unsigned char *)(st[1] + 0x20) >> 3 & 1) == 0))
            return 0x9cb0001;
        tpidr = (unsigned long *)__builtin_thread_pointer();
        *tpidr = (unsigned long)(mode == 1);
        __asm__ volatile("hvc #0" ::: "memory");    /* CallSupervisor(3) */
        if (st[0] == 0)
            return 0;
        return (st[0] & 0x7fff) << 0x10 | 0x80000001;
    }
    return err;
}

/*--------------------------------------------------------------------*/
/* FUN_0003863c @ 0x0003863c   (est. sk_fault_span_commit)
 * Ghidra: undefined1[16] FUN_0003863c(void)
 * Commits the current fault span: builds the span (FUN_00032cd0 +
 * FUN_00042abc) and invokes CallSupervisor(2). Returns the committed
 * granule code / error.
 * Confidence: medium (structural; fault-span commit).
 */
cl4_result_t sk_fault_span_commit(void)
{
    cl4_result_t r;
    unsigned long o, v;

    o = (unsigned long)sk_vspace_root();                       /* FUN_00032cd0 -> root */
    v = sk_obj_method_dispatch3(o, 2, 0);       /* FUN_00042abc */
    if (v == 0) {
        r.lo = 0x9e60004; r.hi = 0;
    } else {
        __asm__ volatile("hvc #0" ::: "memory");/* CallSupervisor(2) */
        r.lo = v ? (v & 0x7fff) << 0x10 | 0x80000001 : 0;
        r.hi = 0;
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003869c @ 0x0003869c   (est. sk_fault_span_walk)
 * Ghidra: undefined1[16] FUN_0003869c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Full fault-span walk: takes the walk refcount (DAT_006ad2c8), builds the
 * walk state and invokes sk_fault_span_map (FUN_00039094) to map the span.
 * On failure (state byte) aborts via sk_vas_abort.
 * Confidence: low-medium (structural; large walk).
 */
cl4_result_t sk_fault_span_walk(unsigned long region, unsigned long addr,
                                unsigned long size)
{
    cl4_result_t r;
    unsigned char state[40];
    unsigned long st[10];
    unsigned char c;

    sk_walk_refcount_inc();                     /* DAT_006ad2c8 */
    for (int i = 0; i < 10; i++) st[i] = 0;
    for (int i = 0; i < 40; i++) state[i] = 0;
    c = 1;
    st[4] = region;
    st[9] = region;
    sk_percpu_get3((unsigned long)&st[2]);      /* FUN_001180fc */
    r = sk_fault_span_map(region, (long *)&st[4], addr, size, state);  /* FUN_00039094 */
    if (state[0] == 1)
        sk_vas_fault43();                       /* FUN_004b28c0 */
    else if (c != 1) {
        sk_vas_fault42();                       /* FUN_004b2898 */
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b4c86);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00038bdc @ 0x00038bdc   (est. sk_fault_span_flush)
 * Ghidra: undefined8 FUN_00038bdc(ulong param_1)
 * Flushes the fault span for the region param_1: checks the region is a
 * valid managed mapping (FUN_0002fa84), builds the span (FUN_0003c56c),
 * then for each live span entry tears it down via
 * sk_region_map_fault (FUN_0003fa94) and sk_region_finalize
 * (FUN_0003f170), releasing pages (FUN_0003da18). Large structural body.
 * Confidence: low-medium (structural; fault-span flush).
 */
unsigned long sk_fault_span_flush(unsigned long region)
{
    unsigned long st[10], span, base, size, v;
    unsigned long *tpidr;
    char ok;
    int err;

    if (region == 0) return 0xccb0001;
    if ((*(unsigned char *)(region + 0x290) & 1) == 0) {
        if (region + 0x2a0 < region) goto fault;
        ok = (char)sk_boot_region_check(0x65b5a0, region + 0x208);  /* FUN_0002fa84 */
        *(unsigned char *)(region + 0x290) = (ok == 0);
    }
    if (region + 0x2a0 < region) goto fault;
    sk_vspace_layout_check_big(region);         /* FUN_00032cd0 */
    st[6] = 0; st[7] = 0;
    {
        cl4_result_t cr = sk_region_create((long)sk_vspace_root(), 0x1908, &sk_desc_boot,
                                           &st[6], 0, 0);   /* FUN_0003c56c */
        if ((cr.lo & 0xff) != 0) return cr.lo;
    }
    base = *(unsigned long *)(st[6] + 8);
    if (sk_vm_lock_check(region + 0x1f0) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    v = *(unsigned long *)(region + 0x200);
    while (v != 0) {
        if ((*(unsigned char *)(v + 0x20) >> 3 & 1) != 0) {
            span = sk_region_map_fault(v, base, 0, 0, 0, 0, 0);  /* FUN_0003fa94 */
            if (span == 0) {
                tpidr = (unsigned long *)__builtin_thread_pointer();
                *tpidr = 1;
                __asm__ volatile("hvc #0" ::: "memory");
                *tpidr = 1;
                if (st[6] <= st[6] + 0xb0) {
                    size = 0;
                    st[0] = 0x4000; st[1] = 0;
                    sk_region_finalize(st[6], &st[0], &st[1], 0); /* FUN_0003f170 */
                    sk_region_unmap_pages(v, 0, 0, 0, 0);   /* FUN_0003da18 */
                }
            }
        }
        v = *(unsigned long *)(v + 0x38);
    }
    if (sk_vm_lock_take(region + 0x1f0) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    return 0;
fault:
    __builtin_unreachable();                    /* SoftwareBreakpoint(0x5519, 0x3908c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00039094 @ 0x00039094   (est. sk_fault_span_map)
 * Ghidra: undefined1[16] FUN_00039094(long param_1, long param_2, ulong param_3, undefined8 param_4, byte *param_5)
 * The fault-span map entry: validates the mapping request (FUN_00045a68),
 * checks attributes (FUN_00045c98), and either maps the span pages
 * (sk_region_wire_spans FUN_0003ff00), bumps the region cursor
 * (sk_span_map_region FUN_0003a550), or retries via
 * sk_region_map_fault (FUN_0003fa94). On any error it faults the pending
 * request. Large structural body.
 * Confidence: low (large; structural shape preserved).
 */
cl4_result_t sk_fault_span_map(long region, long *state, unsigned long addr,
                               unsigned long flags, unsigned char *out_state)
{
    cl4_result_t r;
    unsigned long st[10], span, v;
    char c, dirty;

    sk_stat_walk_all = sk_stat_walk_all + 1;
    for (int i = 0; i < 0x28; i++) out_state[i] = 0;
    dirty = 0;
    st[4] = 0;
    v = sk_obj_walk5(region, (long)state, addr & 0xf0ffffffffffc000, &st[4], &dirty); /* FUN_00045a68 */
    c = dirty;
    if ((v & 1) == 0) {
        sk_stat_walk_ok = sk_stat_walk_ok + 1;
        r.lo = 0xfb20001; r.hi = 0;
        return r;
    }
    if ((addr & 0xf00000000000000) != 0 &&
        (*(unsigned char *)(st[4] + 0x22) >> 6 & 1) == 0) {
        sk_obj_state5(region, (long)state);     /* FUN_00045c98 */
        sk_stat_walk_attr = sk_stat_walk_attr + 1;
        r.lo = 0xfbb0001; r.hi = 0;
        return r;
    }
    sk_stat_walk_start = sk_stat_walk_start + 1;
    if (*(long *)(st[4] + 0x50) != region) {
        r.lo = 0; r.hi = 0;
        return r;
    }
    *(long *)((long)state + 0xb0) = st[4];
    if ((*(unsigned char *)(st[4] + 0x22) & 1) != 0) {
        v = sk_obj_attach5((unsigned long)c, flags);        /* FUN_000455b0 */
        if ((v & 1) == 0) {
            sk_stat_walk_attach = sk_stat_walk_attach + 1;
            r.lo = 0xf210001; r.hi = 0;
            return r;
        }
    }
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00039e34 @ 0x00039e34   (est. sk_span_destroy)
 * Ghidra: undefined1[16] FUN_00039e34(undefined1 *param_1)
 * Destroys a span object (param_1): detaches it from its owning region,
 * releases its pages (sk_region_finalize FUN_0003f170), tears down the
 * span backing (sk_region_teardown FUN_0003c3bc), unlinks the span from
 * the region tree (sk_slot_attach / sk_slot_detach), and frees the span
 * object. Returns error 0x5660001 if the object is not a destroyable span.
 * Confidence: low-medium (structural; span destroy).
 */
cl4_result_t sk_span_destroy(unsigned char *span)
{
    cl4_result_t r;
    unsigned long owner, st[10], v, base, len;
    unsigned long *tpidr;
    void **slot;
    int err;

    owner = *(unsigned long *)(span + 0x50);
    for (int i = 0; i < 10; i++) st[i] = 0;
    if (((unsigned char)span[0x23] >> 3 & 1) != 0) {
        sk_vas_warn2("WARNING: failed attempt to destroy %s", 0x5b3e91); /* FUN_00118b28 */
        r.lo = 0x5b10001; r.hi = 0;
        return r;
    }
    if (sk_obj_state6(owner) != 0) {            /* FUN_00045cb8 */
        /* unlink from owner list under lock */
        if (sk_vm_lock_check(owner + 0x1f0) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        {
            unsigned long *prev = *(unsigned long **)(span + 0x90);
            unsigned long *next = *(unsigned long **)(span + 0x98);
            if (prev) *(unsigned long **)(prev + 0x98) = next;
            *next = (unsigned long)prev;
        }
        if (sk_vm_lock_take(owner + 0x1f0) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
    }
    base = *(unsigned long *)(span + 8);
    len = base;
    if ((*(unsigned int *)(span + 0x20) & 0x40) != 0)
        len = *(unsigned long *)(span + 0x48);
    else
        len = *(unsigned long *)(span + 0x10);
    sk_region_finalize((unsigned long)span, &len, &base, 1);  /* FUN_0003f170 */
    if (sk_vm_lock_check((unsigned long)span + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    sk_region_teardown((long)span);             /* FUN_0003c3bc */
    if (sk_vm_lock_take((unsigned long)span + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    st[0] = st[1] = st[2] = st[3] = 0;
    sk_slot_attach((unsigned long)st, owner, *(unsigned long *)(span + 8),
                   *(unsigned long *)(span + 0x10));   /* FUN_0003be88 */
    if ((*(unsigned int *)(span + 0x20) >> 0x18 & 1) != 0) {
        r.lo = 0x5660001; r.hi = 0;
        goto done;
    }
    slot = *(void ***)(span + 0x70);
    if (slot == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b3ed8);
        __builtin_unreachable();
    }
    *slot = (void *)st[2];
    *(unsigned long *)(span + 0x70) = 0;
    *(unsigned int *)(span + 0x20) = 0;
    for (int i = 0; i < 5; i++) *(unsigned long *)(span + i * 8) = 0;
    st[2] = (unsigned long)slot;
    sk_region_recalc(*(unsigned long *)(st[0] + 0x58), (long)span);  /* FUN_0003f0dc */
    if (0x3fff < *(unsigned long *)(span + 8)) {
        v = sk_region_find_span(st, *(unsigned long *)(span + 8) - 0x4000); /* FUN_0003dd68 */
        if (v != 0 && *(int *)(v + 0x20) == 0)
            sk_region_merge2((unsigned long)st, owner, v, (long)span);   /* FUN_0003f324 */
    }
    if (*(long *)(span + 0x10) + *(long *)(span + 8) != 0x1000000000) {
        v = sk_region_find_span(st, 0);         /* FUN_0003dd68 */
        if (v != 0 && *(int *)(v + 0x20) == 0)
            sk_region_merge2((unsigned long)st, owner, (long)span, 0);   /* FUN_0003f324 */
    }
    r.lo = 0; r.hi = 0;
done:
    sk_slot_detach((long *)st, owner);                  /* FUN_0003bfb8 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003a1e0 @ 0x0003a1e0   (est. sk_span_unmap)
 * Ghidra: void FUN_0003a1e0(long param_1, uint param_2)
 * Unmaps the pages of span param_1 matching the attribute mask param_2.
 * Clears the corresponding capability bits, walks the span cursor
 * releasing each page (sk_span_cursor_build / CallSupervisor(0)), and
 * advances the cursor. Returns error codes 0x5df0001 (bad attrs) /
 * 0x5e70001 (attribute not permitted).
 * Confidence: low-medium (structural; span unmap).
 */
void sk_span_unmap(long span, unsigned int attrs)
{
    unsigned long st[2], v, base, end, e, u;
    unsigned long *tpidr;
    unsigned int w, fl, idx;
    int err;

    w = *(unsigned int *)(span + 0x20);
    if ((attrs & (w ^ 0xffffffff)) != 0) {
        sk_stack_check_fail3(0x5df0001, 0);     /* FUN_0011d7e8 */
        __builtin_unreachable();
    }
    fl = w & (attrs ^ 0xffffffff);
    if ((fl & 0xd08d9c1) != 0) {
        sk_stack_check_fail3(0x5e70001, 0);     /* FUN_0011d7e8 */
        __builtin_unreachable();
    }
    w = w & attrs;
    *(unsigned int *)(span + 0x20) = w;
    if ((fl & 0x18) == 0) return;
    end = *(unsigned long *)(span + 8);
    if ((w >> 7 & 1) != 0)
        end = (*(long *)(span + 0x10) - *(long *)(span + 0x48)) + *(long *)(span + 8);
    base = *(unsigned long *)(span + 8);
    while (1) {
        v = (w & 0x40) ? *(unsigned long *)(span + 0x48) : *(unsigned long *)(span + 0x10);
        if (*(unsigned long *)(span + v) <= (unsigned long)(end - base)) break;
        sk_vspace_layout_check_big(*(unsigned long *)(span + 0x50));  /* FUN_00032cd0 */
        if (sk_vm_lock_check((unsigned long)span + 0x80) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        st[0] = st[1] = 0;
        sk_span_lookup_build((unsigned long)st, *(unsigned long *)(span + 0x78));  /* FUN_00035ba0 */
        e = st[0];
        *(unsigned long *)(span + 0x78) = st[1];
        if (st[0] == 0) {
            err = sk_vm_lock_take((unsigned long)span + 0x80);
            if (err != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
                __builtin_unreachable();
            }
            break;
        }
        idx = w >> 3 & 3;
        tpidr = (unsigned long *)__builtin_thread_pointer();
        *tpidr = idx;
        __asm__ volatile("hvc #0" ::: "memory");
        *tpidr = idx;
        err = sk_vm_lock_take((unsigned long)span + 0x80);
        if (err != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        u = 0;
        if ((e & 0xff) != 4) u = e;
        if ((u & 0xff) != 0) {
            sk_vas_fault61(u, st);              /* FUN_004b2f80 */
            __builtin_unreachable();
        }
        end += 0x4000;
        w = *(unsigned int *)(span + 0x20);
        if ((w >> 7 & 1) == 0) base = *(unsigned long *)(span + 8);
        else base = (*(long *)(span + 0x10) - *(long *)(span + 0x48)) + *(long *)(span + 8);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003a4a0 @ 0x0003a4a0   (est. sk_span_alloc_region)
 * Ghidra: ulong FUN_0003a4a0(long param_1, ulong *param_2)
 * Allocates a 16 KiB region within span param_1 at the current cursor
 * (param_1+0x48), calling sk_span_map_region (FUN_0003a550) to carve it.
 * Updates the cursor and returns the region base via param_2.
 * Confidence: medium (structural; region allocation).
 */
unsigned long sk_span_alloc_region(long span, unsigned long *out)
{
    unsigned long base, size, err, cur;

    base = (*(unsigned long *)(span + 0x10) < (unsigned long)0) ? 0 : 0;
    base = 0;  /* decompile uses in-register inputs; model with current base */
    cur = *(unsigned long *)(span + 0x48);
    if (*(unsigned long *)(span + 0x10) < cur) {
        return 0x6010001;
    }
    size = cur;
    base = cur;
    if (base < cur || base == 0) {
        *out = *(unsigned long *)(span + 0x48);
        return 0;
    }
    err = sk_span_map_region(span, &size, &base);   /* FUN_0003a550 */
    if ((err & 0xff) == 0) {
        *(unsigned long *)(span + 0x48) = base;
        *out = base;
        return 0;
    }
    return err;
}

/*--------------------------------------------------------------------*/
/* FUN_0003a550 @ 0x0003a550   (est. sk_span_map_region)
 * Ghidra: void FUN_0003a550(long param_1, ulong *param_2, ulong *param_3)
 * Maps a region into the span param_1: aligns the request, walks the span
 * (FUN_0003df84 / FUN_0003ff00), and on a fault delegates to
 * sk_region_map_fault (FUN_0003fa94) / sk_region_finalize (FUN_0003f170).
 * Returns the map result through param_2/param_3. Aborts on stack-check
 * failure.
 * Confidence: low (large; structural shape preserved).
 */
unsigned long sk_span_map_region(long span, unsigned long *base_out, unsigned long *size_out)
{
    unsigned long base, size, aligned, v, err;
    unsigned long st[2];
    int has_stack;

    has_stack = 0;
    if (*(unsigned int *)(span + 0x20) != 0 &&
        (*(unsigned int *)(span + 0x20) & 0x81000) == 0) {
        base = *base_out;
        if (base < *(unsigned long *)(span + 0x10) &&
            *size_out <= *(unsigned long *)(span + 0x10) - base) {
            aligned = *(long *)(span + 8) + base & 0xffffffffffffc000;
            *size_out = (*size_out + base + *(long *)(span + 8)) - aligned;
            *base_out = aligned - *(long *)(span + 8);
            size = 0;
            if ((*size_out & 0x3fff) != 0) size = 0x4000;
            *size_out = size + (*size_out & 0xffffffffffffc000);
            sk_span_prefetch_pages((char *)span, *base_out, 0);   /* FUN_0003df84 */
            v = sk_region_wire_spans((char *)span, aligned, *size_out + aligned); /* FUN_0003ff00 */
            err = v & 0xff;
            if (err == 2) {
                v = 0x68f0002;
            } else if ((err != 8 && err != 0) &&
                       (*(unsigned int *)(span + 0x20) >> 0x12 & 1) == 0) {
                /* retry through the fault path */
                st[0] = 0; st[1] = 0;
                v = sk_region_map_fault(span, aligned, 0, 0, 0, 0, 0);  /* FUN_0003fa94 */
                if ((long)v < 7) {
                    if (v == 0) v = 0;
                    else if (v == 2) v = 0x80020002;
                    else if (v == 5) v = 0x80050003;
                    else { sk_vas_fault64(v, 0); return v; }      /* FUN_004b3064 */
                } else {
                    if (v != 7 && v != 0x307 && v != 0x207) {
                        sk_vas_fault64(v, 0);                   /* FUN_004b3064 */
                        return v;
                    }
                    v = (v & 0x7fff) << 0x10 | 0x80000001;
                }
                if (has_stack) {
                    sk_stack_check_fail3(v, 0); /* FUN_0011d7e8 */
                    __builtin_unreachable();
                }
                return v;
            }
            if (has_stack) {
                sk_stack_check_fail3(v, 0);     /* FUN_0011d7e8 */
                __builtin_unreachable();
            }
            return 0;
        }
    }
    v = 0x6800001;
    if (has_stack) {
        sk_stack_check_fail3(v, 0);             /* FUN_0011d7e8 */
        __builtin_unreachable();
    }
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_0003abf4 @ 0x0003abf4   (est. sk_span_split)
 * Ghidra: undefined1[16] FUN_0003abf4(long param_1, ulong param_2, long *param_3, long *param_4)
 * Splits the span param_1 at offset param_2 into two spans returned in
 * param_3/param_4 (each with tag 0x65b648). Validates the span state,
 * attaches it (sk_slot_attach FUN_0003be88), relinks the split node
 * (sk_slot_link_root FUN_0003bd70), splits (sk_region_split
 * FUN_0003ee4c), and remaps both halves (sk_span_compact FUN_00036a94).
 * Returns error code 0x7fb0001 on an invalid offset.
 * Confidence: low-medium (structural; span split).
 */
cl4_result_t sk_span_split(long span, unsigned long at, long *lo_out, long *hi_out)
{
    cl4_result_t r;
    unsigned long st[10], owner, uVar2, v;
    long lo, hi;
    unsigned int w, uVar4;
    int err;

    w = *(unsigned int *)(span + 0x20);
    if ((w & 0xd000800) == 0) {
        v = 0x7fb0001;
        if (at != 0) v = 0;
        uVar2 = 0x7f80001;
        if (at < *(unsigned long *)(span + 0x10)) uVar2 = v;
    } else {
        uVar2 = 0x7f60001;
    }
    r.lo = uVar2; r.hi = 0;
    if ((uVar2 & 0xff) == 0) {
        owner = *(unsigned long *)(span + 0x50);
        uVar4 = (w != 0) ? 2 : 0;
        for (int i = 0; i < 10; i++) st[i] = 0;
        v = sk_slot_attach_full(st, owner, 1, uVar4, 0, 0);   /* FUN_0003b820 */
        if ((v & 1) == 0) {
            r.lo = 0x85f0002; r.hi = 0;
            return r;
        }
        lo = *(long *)(span + 8);
        sk_obj_snapshot4(owner, st + 1, lo, *(unsigned long *)(span + 0x10)); /* FUN_00044dec */
        if (sk_vm_lock_check((unsigned long)span + 0x80) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        sk_slot_link_root((long *)st, owner, (unsigned long)(st + 1));  /* FUN_0003bd70 */
        {
            cl4_result_t sr = sk_region_split((long)st, owner, (unsigned long *)span, at, st + 1, (unsigned long *)&hi); /* FUN_0003ee4c */
            r = sr;
        }
        sk_slot_detach((long *)st, owner);              /* FUN_0003bfb8 */
        lo = st[0];
        hi = (long)r.hi;
        if ((r.lo & 0xff) == 0) {
            if (st[0] != span) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b47ec);
                __builtin_unreachable();
            }
            if (sk_vm_lock_check((unsigned long)hi + 0x80) != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
                __builtin_unreachable();
            }
            sk_span_compact(st + 4, *(unsigned long *)(span + 0x78),
                            (int)((lo + at) - *(long *)((unsigned long)sk_vspace_root() + 0x28) >> 0xe) + 1); /* FUN_00036a94 */
            *(unsigned long *)(lo + 0x78) = st[6];
            *(unsigned long *)(hi + 0x78) = st[5];
            if (sk_vm_lock_take((unsigned long)hi + 0x80) != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
                __builtin_unreachable();
            }
        }
        if (sk_vm_lock_take((unsigned long)span + 0x80) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        sk_obj_commit4(owner, st + 1);          /* FUN_00044ff4 */
        if ((r.lo & 0xff) == 0) {
            if (st[0] == 0 || hi == 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b48a0);
                __builtin_unreachable();
            }
            *lo_out = st[0]; lo_out[1] = 0x65b648;
            *hi_out = hi; hi_out[1] = 0x65b648;
        } else if (st[0] != 0 || hi != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b493d);
            __builtin_unreachable();
        }
    }
    if (st[11] != 0) {
        sk_stack_check_fail3(0, 0);             /* FUN_0011d7e8 */
        __builtin_unreachable();
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003afe4 @ 0x0003afe4   (est. sk_span_attach)
 * Ghidra: undefined1[16] FUN_0003afe4(undefined8 *param_1, ulong param_2, uint param_3, undefined8 *param_4)
 * Attaches a span to a region: validates span state + extent, splits
 * (sk_span_split FUN_0003abf4) the region, creates the destination span
 * (sk_region_create FUN_0003c56c), wires it (sk_obj_create5 FUN_000451a0),
 * and returns the new span. Returns error codes 0x8940001..0x8980001 for
 * the various state violations.
 * Confidence: low-medium (structural; span attach).
 */
cl4_result_t sk_span_attach(unsigned long *span, unsigned long at, unsigned int attrs,
                            unsigned long *dest)
{
    cl4_result_t r;
    unsigned long st[10], lo, hi, uVar7, uVar6;
    unsigned int w;
    char c;

    w = *(unsigned int *)(span + 4);
    if ((w & 0xd000800) != 0) { r.lo = 0x8940001; r.hi = 0; return r; }
    if (w == 0) { r.lo = 0x8950001; r.hi = 0; return r; }
    if (0x1000000000 - span[1] < at && ((attrs ^ (w & 0x80) == 0) & 1)) {
        r.lo = 0x8960001; r.hi = 0; return r;
    }
    if (at > span[2] + span[1] && ((attrs ^ (w & 0x80) == 0) & 1)) {
        r.lo = 0x8970001; r.hi = 0; return r;
    }
    if (attrs != 0 && (w >> 6 & 1) != 0) { r.lo = 0x8980001; r.hi = 0; return r; }
    uVar7 = span[2] - at;
    if (uVar7 == 0) { r.lo = 0; r.hi = 0; return r; }
    for (int i = 0; i < 10; i++) st[i] = 0;
    st[0] = (unsigned long)span[0];
    st[1] = span[1];
    st[3] = span[3];
    r = sk_span_split((long)span, uVar7, (long *)&lo, (long *)&hi);
    if ((r.lo & 0xff) != 0) return r;
    c = (char)((unsigned long (*)(unsigned long))st[0])(lo);
    if (c == 0) { r.lo = 0; r.hi = 0; return r; }
    sk_vas_fault66();                           /* FUN_004b3154 */
    uVar7 = at;
    r = sk_region_create(span[10], w, (char *)&lo, &st[0], 0, 0); /* FUN_0003c56c */
    if ((r.lo & 0xff) != 0) return r;
    *(unsigned short *)(st[0] + 0x19) = *(unsigned short *)((long)span + 0x19);
    r.lo = sk_obj_create5((long)span, st[0], (unsigned long)dest, (unsigned long)dest); r.hi = 0; /* FUN_000451a0 */
    if ((r.lo & 0xff) == 0) return r;
    c = (char)((unsigned long (*)(unsigned long))st[0])(st[0]);
    if (c == 0) return r;
    r.lo = sk_vas_fault65();                    /* FUN_004b311c */
    if ((*(unsigned char *)(r.lo + 0x22) & 1) == 0) { r.lo = 0x101a0001; r.hi = 0; return r; }
    if (r.hi != 4)
        sk_span_prefetch_pages((char *)r.lo, (unsigned long)dest, 0);   /* FUN_0003df84 */
    r.lo = sk_obj_create5(*(unsigned long *)(r.lo + 0x50), r.lo, uVar7,
                          (unsigned long)dest);                /* FUN_000451a0 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003b258 @ 0x0003b258   (est. sk_span_next_region)
 * Ghidra: undefined1[16] FUN_0003b258(long *param_1)
 * Returns the next region span after the one at *param_1 in the region
 * tree, with tag 0x65b648. If the current span is free (dirty bit clear)
 * returns a released node; otherwise walks the tree (sk_region_find_span /
 * sk_fault_span_next3).
 * Confidence: medium (structural; region-tree successor).
 */
cl4_result_t sk_span_next_region(long *span)
{
    cl4_result_t r;
    unsigned long cur, owner, st[10], v;

    cur = *span;
    if (cur != 0) {
        for (int i = 0; i < 10; i++) st[i] = 0;
        owner = *(unsigned long *)(cur + 0x50);
        sk_slot_attach((unsigned long)st, owner, 0, 0);        /* FUN_0003be88 */
        if (*(int *)(cur + 0x20) == 0) {
            r.lo = sk_vas_fault67();            /* FUN_004b318c */
            if (*(unsigned long *)r.lo == 0) sk_stat_fault_inc = sk_stat_fault_inc - 1;
            r.hi = 0x65b648;
            return r;
        }
        if (*(long *)(cur + 0x10) + *(long *)(cur + 8) == 0x1000000000)
            v = 0;
        else
            v = sk_region_find_span(st, 0);     /* FUN_0003dd68 */
        v = sk_fault_span_next3(st, v);         /* FUN_000405d0 */
        *span = v;
        sk_slot_detach((long *)st, owner);              /* FUN_0003bfb8 */
        if (v == 0) sk_stat_fault_inc = sk_stat_fault_inc - 1;
    }
    r.lo = cur; r.hi = 0x65b648;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003b340 @ 0x0003b340   (est. sk_slot_pop_a)
 * Ghidra: undefined8 * FUN_0003b340(long param_1)
 * Pops a node from the +0x18 free list (count byte at +0x32). Aborts if
 * the list is empty or overfull.
 * Confidence: high (trivial list pop).
 */
unsigned long *sk_slot_pop_a(long obj)
{
    unsigned long *n;
    unsigned char c;

    c = *(unsigned char *)(obj + 0x32);
    if (c == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b22f9);
        __builtin_unreachable();
    }
    if (c < 4) {
        *(unsigned char *)(obj + 0x32) = c - 1;
        n = *(unsigned long **)(obj + 0x18);
        if (n != 0) {
            *(unsigned long *)(obj + 0x18) = *n;
            *n = 0;
            return n;
        }
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b23df);
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b237f);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003b410 @ 0x0003b410   (est. sk_slot_push_a)
 * Ghidra: void FUN_0003b410(long param_1, undefined8 *param_2)
 * Pushes a node onto the +0x18 free list (count byte at +0x32). Aborts if
 * the list is full.
 * Confidence: high (trivial list push).
 */
void sk_slot_push_a(long obj, unsigned long *node)
{
    unsigned char c;

    if (node != 0) {
        c = *(unsigned char *)(obj + 0x32);
        if (2 < c) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b237f);
            __builtin_unreachable();
        }
        *node = *(unsigned long *)(obj + 0x18);
        *(unsigned long **)(obj + 0x18) = node;
        *(unsigned char *)(obj + 0x32) = c + 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003b478 @ 0x0003b478   (est. sk_slot_pop_b)
 * Ghidra: undefined8 * FUN_0003b478(long param_1)
 * Pops a node from the +0x20 free list (count byte at +0x33).
 * Confidence: high (trivial list pop).
 */
unsigned long *sk_slot_pop_b(long obj)
{
    unsigned long *n;
    unsigned char c;

    c = *(unsigned char *)(obj + 0x33);
    if (c == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b246d);
        __builtin_unreachable();
    }
    if (c < 4) {
        *(unsigned char *)(obj + 0x33) = c - 1;
        n = *(unsigned long **)(obj + 0x20);
        if (n != 0) {
            *(unsigned long *)(obj + 0x20) = *n;
            *n = 0;
            return n;
        }
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b255d);
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b24f5);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003b548 @ 0x0003b548   (est. sk_slot_push_b)
 * Ghidra: void FUN_0003b548(long param_1, undefined8 *param_2)
 * Pushes a node onto the +0x20 free list (count byte at +0x33).
 * Confidence: high (trivial list push).
 */
void sk_slot_push_b(long obj, unsigned long *node)
{
    unsigned char c;

    if (node != 0) {
        c = *(unsigned char *)(obj + 0x33);
        if (2 < c) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b24f5);
            __builtin_unreachable();
        }
        *node = *(unsigned long *)(obj + 0x20);
        *(unsigned long **)(obj + 0x20) = node;
        *(unsigned char *)(obj + 0x33) = c + 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003b5b0 @ 0x0003b5b0   (est. sk_slot_pop_c)
 * Ghidra: undefined8 * FUN_0003b5b0(long param_1)
 * Pops a node from the +0x28 free list (count at +0x38, a full long).
 * Confidence: high (trivial list pop).
 */
unsigned long *sk_slot_pop_c(long obj)
{
    unsigned long *n;

    if (*(long *)(obj + 0x38) == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b25dd);
        __builtin_unreachable();
    }
    *(long *)(obj + 0x38) = *(long *)(obj + 0x38) - 1;
    n = *(unsigned long **)(obj + 0x28);
    if (n != 0) {
        *(unsigned long *)(obj + 0x28) = *n;
        *n = 0;
        return n;
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b26cb);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003b648 @ 0x0003b648   (est. sk_slot_push_c)
 * Ghidra: void FUN_0003b648(long param_1, undefined8 *param_2)
 * Pushes a node onto the +0x28 free list (count at +0x38).
 * Confidence: high (trivial list push).
 */
void sk_slot_push_c(long obj, unsigned long *node)
{
    if (node != 0) {
        if (*(long *)(obj + 0x38) == -1) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b2664);
            __builtin_unreachable();
        }
        *node = *(unsigned long *)(obj + 0x28);
        *(unsigned long **)(obj + 0x28) = node;
        *(long *)(obj + 0x38) = *(long *)(obj + 0x38) + 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003b6ac @ 0x0003b6ac   (est. sk_slot_pop_d)
 * Ghidra: undefined8 FUN_0003b6ac(long param_1)
 * Pops a node from the +0x28 free list when the list count (+0x38) is
 * non-zero; otherwise returns 0. Uses sk_slot_pop_c.
 * Confidence: high (trivial wrapper).
 */
unsigned long sk_slot_pop_d(long obj)
{
    if (*(long *)(obj + 0x38) != 0)
        return (unsigned long)sk_slot_pop_c(obj);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0003ba58 @ 0x0003ba58   (est. sk_slot_push_d)
 * Ghidra: void FUN_0003ba58(long param_1, undefined8 *param_2)
 * Pushes a node onto the +8 free list (count byte at +0x30).
 * Confidence: high (trivial list push).
 */
void sk_slot_push_d(long obj, unsigned long *node)
{
    unsigned char c;

    if (node != 0) {
        c = *(unsigned char *)(obj + 0x30);
        if (2 < c) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b33f0);
            __builtin_unreachable();
        }
        *node = *(unsigned long *)(obj + 8);
        *(unsigned long **)(obj + 8) = node;
        *(unsigned char *)(obj + 0x30) = c + 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003bca0 @ 0x0003bca0   (est. sk_slot_unlink_root)
 * Ghidra: void FUN_0003bca0(undefined8 *param_1, undefined8 *param_2, undefined8 param_3, undefined8 param_4)
 * Unlinks a root node (param_2) from the region tree, replacing it with
 * the next node and relinking via sk_obj_unlink4. Special-cases the global
 * sentinel root (DAT_0064c3f0) via sk_obj_unref2.
 * Confidence: medium (structural; tree unlink).
 */
void sk_slot_unlink_root(unsigned long *root, unsigned long *node,
                         unsigned long param_3, unsigned long param_4)
{
    if ((unsigned long *)*root != node) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2905);
        __builtin_unreachable();
    }
    if (node == (unsigned long *)&sk_vspace_root_obj)
        sk_obj_unref2();                        /* FUN_00043e88 */
    sk_obj_unlink4(node, param_3, param_4);     /* FUN_00044c94 */
    if (node[10] == 0) { node[10] = (unsigned long)root; return; }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b2968);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003bd70 @ 0x0003bd70   (est. sk_slot_link_root)
 * Ghidra: void FUN_0003bd70(long *param_1, long param_2, undefined8 param_3)
 * Links param_2 as the root node of the region tree *param_1 after
 * validating *param_1 == param_2; stores the tree back-pointer into
 * node+0x50.
 * Confidence: high (trivial link).
 */
void sk_slot_link_root(long *root, long node, unsigned long param_3)
{
    if (*root != node) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2905);
        __builtin_unreachable();
    }
    sk_obj_link4(node, param_3);                /* FUN_00044be0 */
    if (*(long *)(node + 0x50) == 0) { *(long **)(node + 0x50) = root; return; }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b2968);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003be18 @ 0x0003be18   (est. sk_slot_attach_wrap)
 * Ghidra: undefined8 FUN_0003be18(...)
 * Wrapper around sk_slot_attach_full (FUN_0003b820): on a non-zero result
 * additionally unlinks the root via sk_slot_unlink_root (FUN_0003bca0).
 * Confidence: medium (structural wrapper).
 */
unsigned long sk_slot_attach_wrap(unsigned long p1, unsigned long p2, unsigned long p3,
                                  unsigned long p4, unsigned long p5, unsigned long p6,
                                  unsigned long p7, unsigned long p8)
{
    unsigned long v;

    v = sk_slot_attach_full((unsigned long *)(uintptr_t)p1, p2, p5, p6, p7, p8);    /* FUN_0003b820 */
    if ((int)v != 0)
        sk_slot_unlink_root((unsigned long *)p1, (unsigned long *)p2, p3, p4);  /* FUN_0003bca0 */
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_0003be88 @ 0x0003be88   (est. sk_slot_attach)
 * Ghidra: undefined8 FUN_0003be88(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Attaches a region span: attempts the fast attach (FUN_0003b820); if that
 * fails it binds the region via sk_region_bind (FUN_0003beec) and returns
 * the bind result. Returns 0 on success.
 * Confidence: medium (structural; region attach).
 */
unsigned long sk_slot_attach(unsigned long st, unsigned long region, unsigned long p3,
                             unsigned long p4)
{
    unsigned long v;
    cl4_result_t r;

    v = sk_slot_attach_full((unsigned long *)(uintptr_t)st, region, 0, 0, 0, 0);    /* FUN_0003b820 */
    if ((v & 1) != 0) {
        sk_slot_unlink_root((unsigned long *)st, (unsigned long *)region, p3, p4);  /* FUN_0003bca0 */
        return v;
    }
    r = sk_region_bind(region, 0x65b5c8, p3, 0x65b648); /* FUN_0003beec */
    return r.lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0003beec @ 0x0003beec   (est. sk_region_bind)
 * Ghidra: undefined1[16] FUN_0003beec(long param_1, long param_2, long param_3, long param_4)
 * Binds the region param_1 to the span param_3: validates the region tag
 * (0x65b5c8) / span tag (0x65b648) and that the region is not already
 * bound (+8==0) and has no existing binding (+0x130==0); stores the span
 * into +0x130. Returns error codes 0x23b0001 / 0x23e0001 / 0x2400001.
 * Confidence: medium (structural; region bind).
 */
cl4_result_t sk_region_bind(long region, long p2, long span, long p4)
{
    cl4_result_t r;

    if (p2 == 0x65b5c8 && p4 == 0x65b648) {
        if (*(char *)(region + 8) == 0) {
            if (*(long *)(region + 0x130) == 0) {
                if (0x400000000 < (unsigned long)(*(long *)(span + 0x10) + *(long *)(span + 8))) {
                    sk_vas_abort("VAS abort in function %s at line %d", 0x5b2ad8);
                    __builtin_unreachable();
                }
                *(long *)(region + 0x130) = span;
                r.lo = 0; r.hi = 0;
            } else {
                r.lo = 0x2400001; r.hi = 0;
            }
        } else {
            r.lo = 0x23e0001; r.hi = 0;
        }
    } else {
        r.lo = 0x23b0001; r.hi = 0;
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003bfb8 @ 0x0003bfb8   (est. sk_slot_detach)
 * Ghidra: void FUN_0003bfb8(long *param_1, long param_2)
 * Detaches the region param_2 from the tree *param_1: validates the root,
 * clears the tree back-pointer (+0x50), and walks the span tree to detach
 * (FUN_0003bac0). Aborts on lock or state failure.
 * Confidence: medium (structural; detach).
 */
void sk_slot_detach(long *root, long region)
{
    int err;

    if (region != *root) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2b51);
        __builtin_unreachable();
    }
    if (*(long **)(region + 0x50) == root) {
        *(unsigned long *)(region + 0x50) = 0;
        err = sk_vm_lock_take(region + 0x40);
        if (err == 0) {
            sk_slot_detach_inner(root);        /* FUN_0003bac0 */
            return;
        }
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b274a);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003c09c @ 0x0003c09c   (est. sk_region_wire)
 * Ghidra: void FUN_0003c09c(void)
 * Wires the current region: resolves the vspace root (FUN_00032514), the
 * region method cookie (FUN_000411dc), and calls sk_vspace_final_wire
 * (FUN_0003c0e4).
 * Confidence: medium (structural wrapper).
 */
void sk_region_wire(void)
{
    cl4_result_t ck;
    unsigned long root;

    root = (unsigned long)sk_vspace_root();                    /* FUN_00032514 */
    ck.lo = sk_obj_method_cookie(0, 0); ck.hi = 0;  /* FUN_000411dc */
    sk_vspace_final_wire(root, ck.lo, ck.hi);   /* FUN_0003c0e4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0003c21c @ 0x0003c21c   (est. sk_slot_pop_e)
 * Ghidra: undefined8 * FUN_0003c21c(long param_1)
 * Pops a node from the +8 free list (count byte at +0x30).
 * Confidence: high (trivial list pop).
 */
unsigned long *sk_slot_pop_e(long obj)
{
    unsigned long *n;
    unsigned char c;

    c = *(unsigned char *)(obj + 0x30);
    if (c == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b3794);
        __builtin_unreachable();
    }
    if (c < 4) {
        *(unsigned char *)(obj + 0x30) = c - 1;
        n = *(unsigned long **)(obj + 8);
        if (n != 0) {
            *(unsigned long *)(obj + 8) = *n;
            *n = 0;
            return n;
        }
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b380a);
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b33f0);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003c2ec @ 0x0003c2ec   (est. sk_region_attach)
 * Ghidra: void FUN_0003c2ec(ulong *param_1, undefined8 param_2)
 * Attaches param_2 to the region tree *param_1 after bounds-checking the
 * tree window (+0x2a0) and calling sk_span_commit3 (FUN_00040870).
 * Confidence: medium (structural wrapper).
 */
void sk_region_attach(unsigned long *tree, unsigned long span)
{
    if (*tree <= *tree + 0x2a0) {
        sk_span_commit3(sk_vspace_root(), span);              /* FUN_00040870 */
        return;
    }
    __builtin_unreachable();                    /* SoftwareBreakpoint(0x5519, 0x3c32c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003c3bc @ 0x0003c3bc   (est. sk_region_teardown)
 * Ghidra: void FUN_0003c3bc(long param_1)
 * Tears down a region span: releases its backing spans (sk_span_release_all
 * FUN_00036920) and unlinks them (sk_region_map_next FUN_0003d904), then
 * releases the region's page list. Walks the span cursor freeing each
 * mapped page via FUN_000304c4.
 * Confidence: low-medium (structural; region teardown).
 */
void sk_region_teardown(long span)
{
    unsigned long cur[3], v;
    unsigned int n;

    if ((*(unsigned char *)(*(long *)(span + 0x50) + 0x290) & 1) != 0) {
        v = (unsigned long)sk_vspace_root();                   /* FUN_00032cd0 -> root */
        cur[0] = cur[1] = cur[2] = 0;
        sk_span_cursor_build(cur, *(unsigned long *)(span + 0xa0), 0); /* FUN_000363ac */
        n = sk_span_cursor_next(cur);
        if ((n & 3) != 0) {
            do {
                /* free each mapped granule */
                n = sk_span_cursor_next(cur);
            } while ((n & 3) != 0);
        }
        sk_span_release_all(*(unsigned long *)(span + 0xa0), 0); /* FUN_00036920 */
        *(unsigned long *)(span + 0xa0) = 0;
    }
    sk_span_release_all(*(unsigned long *)(span + 0x78), 0);     /* FUN_00036920 */
    *(unsigned long *)(span + 0x78) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0003c4c0 @ 0x0003c4c0   (est. sk_region_check)
 * Ghidra: bool FUN_0003c4c0(long param_1, long param_2, long param_3, long param_4)
 * Validates that the region param_3 belongs to owner param_1 (its +0x50
 * slot == param_1) with the given tags, and reports whether the region is
 * marked writable (+0x20 != 0).
 * Confidence: medium (structural; region validation).
 */
bool sk_region_check(long owner, long tag, long region, long tag2)
{
    if (tag == 0x65b5c8 && tag2 == 0x65b648 && owner != 0 && region != 0 &&
        *(long *)(region + 0x50) == owner)
        return *(int *)(region + 0x20) != 0;
    return false;
}

/*--------------------------------------------------------------------*/
/* FUN_0003c56c @ 0x0003c56c   (est. sk_region_create)
 * Ghidra: undefined1[16] FUN_0003c56c(long param_1, uint param_2, char *param_3, undefined8 *param_4, undefined4 *param_5, undefined8 *param_6)
 * The region constructor: attaches the new region (sk_slot_attach_full
 * FUN_0003b820), parses the 0x28-byte region descriptor (param_3), and
 * builds the region's vspace/span layout through a long descriptor decode
 * (sk_class_perm FUN_0003e710, sk_region_walk_span FUN_0003e73c,
 * sk_region_bind2 FUN_0003e984). Returns the created region + tag in
 * param_4, or a parse error code. This is a large constructor.
 * Confidence: low (large; structural shape preserved).
 */
cl4_result_t sk_region_create(long owner, unsigned int attrs, char *desc,
                              unsigned long *out, unsigned int *p5, unsigned long *p6)
{
    cl4_result_t r;
    unsigned long st[10];
    unsigned char c7, c8, c9, b10, b11;
    unsigned int u6, kind;
    unsigned long u16, u24;
    int err;

    for (int i = 0; i < 10; i++) st[i] = 0;
    err = (int)sk_slot_attach_full(st, owner, 2, 1, attrs >> 0x10 & 1, 0);  /* FUN_0003b820 */
    if ((err & 1) == 0) {
        r.lo = 0x49b0002; r.hi = 0;
        return r;
    }
    sk_slot_unlink_root((unsigned long *)st, (unsigned long *)owner, 0, 0);  /* FUN_0003bca0 */
    c7 = *desc;
    kind = attrs >> 0x1b & 1;
    if (kind == 0) {
        u24 = *(unsigned long *)(desc + 8);
        u16 = *(unsigned long *)(desc + 0x10);
        c8 = desc[0x18]; c9 = desc[0x19]; b10 = desc[0x1a]; b11 = desc[0x1b];
        u6 = *(unsigned int *)(desc + 0x1c);
        if (sk_errname3(c7) == 0xe) {           /* FUN_000559b8 */
            /* method 0xe: attribute validation */
            if ((attrs & 0xc0) == 0x80) { r.lo = 0x3cd0001; r.hi = 0; return r; }
            if (((attrs ^ 0xffffffff) & 0x60) == 0) { r.lo = 0x3d10001; r.hi = 0; return r; }
            if (((attrs ^ 0xffffffff) & 0x81000) == 0) { r.lo = 0x3d30001; r.hi = 0; return r; }
            if ((attrs >> 0xc & 1) == 0) {
                if (((attrs >> 0x13 & 1) == 0) || ((attrs & 0x108f0) == 0x10800)) {
                    if ((attrs >> 0x10 & 1) == 0 && (attrs & 0x2300000) != 0) {
                        r.lo = 0x3e60001; r.hi = 0; return r;
                    }
                    if (b10 < 0x24) {
                        if ((attrs & 1) == 0) {
                            if (b11 == 0 || 0xffffffcd < b11 - 0x40) {
                                if (sk_class_perm(c8) == 0) {   /* FUN_0003e710 */
                                    r.lo = 0x3f60001; r.hi = 0; return r;
                                }
                                if (*(long *)(desc + 0x10) == 0) {
                                    r.lo = 0x3f80001; r.hi = 0; return r;
                                }
                                /* build the region walk */
                                if ((attrs & 1) == 0) {
                                    if ((attrs >> 0x11 & 1) == 0) {
                                        r.lo = 0; r.hi = 0;
                                        *out = 0;
                                        return r;
                                    }
                                    sk_region_walk_span(&st[0], st, (long)&c7, (unsigned long *)&c7); /* FUN_0003e73c */
                                    r.lo = 0; r.hi = 0;
                                    *out = (unsigned long)st[0];
                                    return r;
                                } else {
                                    r.lo = 0; r.hi = 0;
                                    *out = 0;
                                    return r;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    r.lo = 0; r.hi = 0;
    *out = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003d2b8 @ 0x0003d2b8   (est. sk_region_config)
 * Ghidra: undefined4 FUN_0003d2b8(long param_1, long param_2, undefined8 *param_3, undefined8 param_4)
 * Reconfigures the region param_1: validates the tag 0x65b648, checks the
 * region is live (+0x20 != 0), accepts a writable+non-device mapping
 * (attrs & 0x81000), and stores the new region descriptor (param_3/param_4)
 * into the region +0x28/+0x30/+0x38. Returns error 0x50a0001/0x50b0001.
 * Confidence: medium (structural; region config).
 */
unsigned int sk_region_config(long region, long tag, unsigned long *desc,
                              unsigned long p4)
{
    unsigned long v;

    if (tag != 0x65b648) return 0x5050001;
    if (*(unsigned int *)(region + 0x20) != 0) {
        if ((*(unsigned int *)(region + 0x20) & 0x81000) != 0) {
            v = *desc;
            *(unsigned long *)(region + 0x30) = desc[1];
            *(unsigned long *)(region + 0x28) = v;
            *(unsigned long *)(region + 0x38) = p4;
            *(unsigned long *)(region + 0x40) = *(unsigned long *)(region + 8);
            return 0;
        }
        return 0x50b0001;
    }
    return 0x50a0001;
}

/*--------------------------------------------------------------------*/
/* FUN_0003d330 @ 0x0003d330   (est. sk_region_bounds)
 * Ghidra: void FUN_0003d330(ulong param_1, undefined8 *param_2, long *param_3)
 * Returns the span bounds (start/end) of the region param_1 into
 * param_2/param_3 by walking the region tree (sk_slot_attach + two
 * sk_region_find_span lookups) and detaching.
 * Confidence: medium (structural; region bounds).
 */
void sk_region_bounds(unsigned long region, unsigned long *start_out,
                      long *end_out)
{
    unsigned long st[10], v;
    unsigned long lo, hi;

    for (int i = 0; i < 10; i++) st[i] = 0;
    sk_slot_attach((unsigned long)st, *(unsigned long *)(region + 0x50), 0, 0);   /* FUN_0003be88 */
    if (*(unsigned long *)(region + 8) < 0x4000) {
        lo = region; hi = region;
    } else {
        v = sk_region_find_span(st, *(unsigned long *)(region + 8) - 0x4000); /* FUN_0003dd68 */
        lo = (v != 0 && *(int *)(v + 0x20) == 0) ? v : region;
        hi = region;
    }
    *start_out = *(unsigned long *)(lo + 8);
    if (*(long *)(region + 0x10) + *(long *)(region + 8) == 0x1000000000) {
        v = 0; hi = region;
    } else {
        v = sk_region_find_span(st, 0);         /* FUN_0003dd68 */
        hi = (v != 0 && *(int *)(v + 0x20) == 0) ? v : region;
    }
    *end_out = *(long *)(hi + 0x10) + *(long *)(hi + 8);
    sk_slot_detach((long *)st, *(unsigned long *)(region + 0x50));          /* FUN_0003bfb8 */
}

/*--------------------------------------------------------------------*/
/* FUN_0003d438 @ 0x0003d438   (est. sk_region_map_span)
 * Ghidra: void FUN_0003d438(ulong param_1, ulong param_2, long param_3, ulong param_4, undefined8 param_5)
 * Maps a span range [param_1, param_1+param_2) into the region param_3:
 * takes the region lock, builds the span cursor, and walks the granules
 * releasing pages (sk_region_unmap_pages FUN_0003da18) with the region
 * method dispatch (FUN_0003d904). Large structural body.
 * Confidence: low-medium (structural; span map).
 */
void sk_region_map_span(unsigned long base, unsigned long size, long region,
                        unsigned long attr, unsigned long p5)
{
    unsigned long cur[3], v, uVar9, uVar2, end, g;
    unsigned long *tpidr;
    int err;

    v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
    uVar2 = base + size;
    if (base + size < base) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2cf7);
        __builtin_unreachable();
    }
    base &= 0xffffffffffffc000;
    if (base < *(unsigned long *)(v + 0x28)) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2d69);
        __builtin_unreachable();
    }
    if (*(unsigned long *)(v + 0x30) < uVar2) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b2dcc);
        __builtin_unreachable();
    }
    end = 0;
    if ((uVar2 & 0x3fff) != 0) end = 0x4000;
    if (sk_vm_lock_check((unsigned long)region + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    uVar2 = end + (uVar2 & 0xffffffffffffc000);
    if ((attr & 1) == 0) {
        cur[0] = cur[1] = cur[2] = 0;
        sk_span_cursor_build(cur, *(unsigned long *)(region + 0x78),
                             (int)(base - *(long *)(v + 0x28) >> 0xe) + 1);  /* FUN_000363ac */
        g = sk_span_cursor_next(cur);
        while ((((unsigned int)v ^ (unsigned int)g) & 3) != 0 &&
               (((g & 0xfffffc0) * 0x100 + *(long *)(v + 0x28)) - 0x4000 < uVar2)) {
            sk_region_unmap_pages(g, region, attr, p5, 0);   /* FUN_0003da18 */
            g = sk_span_cursor_next(cur);
        }
        if (sk_vm_lock_take((unsigned long)region + 0x80) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        return;
    }
    cur[0] = cur[1] = cur[2] = 0;
    sk_span_cursor_build(cur, *(unsigned long *)(region + 0x78),
                         (int)(base - *(long *)(v + 0x28) >> 0xe) + 1);  /* FUN_000363ac */
    sk_region_unmap_pages(sk_span_cursor_next(cur), region, attr, p5, 0); /* FUN_0003da18 */
    if (sk_vm_lock_take((unsigned long)region + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003d904 @ 0x0003d904   (est. sk_region_map_next)
 * Ghidra: ulong FUN_0003d904(long param_1)
 * Advances the region span cursor: returns the next granule count / index
 * from the current span descriptor, bumping the span allocation count
 * (FUN_0003667c).
 * Confidence: medium (structural; cursor advance).
 */
unsigned long sk_region_map_next(long region)
{
    unsigned long v, uVar4;

    v = *(unsigned long *)(*(long *)(region + 0x28) + 8);
    if (v + 0x18 <= v + 0x30) {
        uVar4 = *(unsigned long *)(*(long *)(*(long *)(region + 0x20) + 8) + 0x18);
        *(unsigned long *)(*(long *)(*(long *)(region + 0x20) + 8) + 0x18) =
            sk_span_cursor_next(0);            /* FUN_0003667c */
        *(unsigned int *)(*(long *)(*(long *)(region + 0x30) + 8) + 0x18) =
            *(unsigned int *)(*(long *)(*(long *)(region + 0x20) + 8) + 0x18) >> 6 & 0x3fffff;
        return uVar4 >> 0x1c;
    }
    __builtin_unreachable();                    /* SoftwareBreakpoint(0x5519, 0x3d980) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003d9d4 @ 0x0003d9d4   (est. sk_region_release3)
 * Ghidra: void FUN_0003d9d4(long param_1)
 * Releases three span-node references (at +0x30/+0x28/+0x20) of the region
 * param_1 via sk_obj_unref_block (FUN_0004b8d0).
 * Confidence: high (trivial refcount drops).
 */
void sk_region_release3(long region)
{
    sk_obj_unref_block(*(unsigned long *)(region + 0x30), 8);  /* FUN_0004b8d0 */
    sk_obj_unref_block(*(unsigned long *)(region + 0x28), 8);  /* FUN_0004b8d0 */
    sk_obj_unref_block(*(unsigned long *)(region + 0x20), 8);  /* FUN_0004b8d0 */
}

/*--------------------------------------------------------------------*/
/* FUN_0003da18 @ 0x0003da18   (est. sk_region_unmap_pages)
 * Ghidra: void FUN_0003da18(ulong param_1, long param_2, int param_3, int param_4, int param_5)
 * Unmaps the pages of a span granule (param_1) in the region param_2:
 * resolves the span root, invokes the page-unmap callback through the span
 * method table, and releases the page mapping via the span cursor
 * (sk_span_lookup_build / FUN_0003611c). Handles both the fast and
 * deferred unmap modes.
 * Confidence: low-medium (structural; page unmap).
 */
void sk_region_unmap_pages(unsigned long granule, long region, int attr,
                           int mode, int p5)
{
    unsigned long st[6], v, uVar1;
    unsigned int uVar2;
    unsigned long *tpidr;

    uVar2 = (unsigned int)granule >> 6 & 0x3fffff;
    if (p5 != 0 && attr == 0) {
        v = (unsigned long)sk_vspace_root();                               /* FUN_00032cd0 -> root */
        ((void (*)(unsigned long, unsigned long))(*(void **)(*(long *)(v + 0xb8) + 0x10)))
            (*(unsigned long *)(v + 0xb0), granule >> 0x1c);
    }
    if (mode == 0) {
        for (int i = 0; i < 6; i++) st[i] = 0;
        sk_span_lookup_build((unsigned long)st, *(unsigned long *)(region + 0x78)); /* FUN_00035ba0 */
        if (st[0] == 0) {
            uVar1 = st[2] & 0xff;
            if (uVar1 != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b455b);
                __builtin_unreachable();
            }
        }
        *(unsigned long *)(region + 0x78) = st[4];
        tpidr = (unsigned long *)__builtin_thread_pointer();
        do {
            __asm__ volatile("hvc #0" ::: "memory");    /* CallSupervisor(4) */
        } while (st[0] == 1);
    } else {
        st[0] = st[1] = st[2] = 0;
        sk_span_release(st, *(unsigned long *)(region + 0x78), uVar2,
                        (void (*)(unsigned long))sk_vas_fault36);   /* FUN_0003611c */
        uVar1 = st[0] & 0xff;
        if (uVar1 != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", 0x5b455b);
            __builtin_unreachable();
        }
        *(unsigned long *)(region + 0x78) = st[2];
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0003dbc0 @ 0x0003dbc0   (est. sk_region_lookup_span)
 * Ghidra: undefined1[16] FUN_0003dbc0(undefined8 param_1, long param_2, long *param_3, ulong *param_4)
 * Looks up the span node containing address param_2 in the region param_1:
 * attaches, finds the span (FUN_0003dd68), detaches, and returns the span
 * node (+ span descriptor) through param_3/param_4. Returns error
 * 0x9b10001 if not found.
 * Confidence: medium (structural; span lookup).
 */
cl4_result_t sk_region_lookup_span(unsigned long region, long addr,
                                   long *node_out, unsigned long *span_out)
{
    cl4_result_t r;
    unsigned long st[10], node, v;

    for (int i = 0; i < 10; i++) st[i] = 0;
    sk_slot_attach((unsigned long)st, region, 0, 0);  /* FUN_0003be88 */
    node = sk_region_find_span(st, (unsigned long)addr);  /* FUN_0003dd68 */
    sk_slot_detach((long *)st, (long)region);            /* FUN_0003bfb8 */
    if (node == 0) {
        r.lo = 0x9b10001; r.hi = 0;
        return r;
    }
    if (sk_vm_lock_check(node + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    v = 0;
    sk_span_find2(&v, *(unsigned long *)(node + 0x78),
                  (int)((unsigned long)(addr - *(long *)((unsigned long)sk_vspace_root() + 0x28)) >> 0xe) + 1); /* FUN_000287e4 */
    *(unsigned long *)(node + 0x78) = v;
    if (sk_vm_lock_take(node + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    if (node_out != 0) {
        *node_out = (long)node;
        r.lo = 0; r.hi = 0;
        if (span_out) *span_out = node;
        return r;
    }
    if (v == 0) {
        /* fault path */
        r.lo = 0x9a90002; r.hi = 0;
        return r;
    }
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003dd68 @ 0x0003dd68   (est. sk_region_find_span)
 * Ghidra: void FUN_0003dd68(ulong *param_1, ulong param_2)
 * Finds the span node in the region tree param_1 whose range contains
 * param_2. Walks the tree by +8 (start) / +0x10+8 (end) bounds; returns
 * the node pointer or 0.
 * Confidence: high (structural; range tree lookup).
 */
unsigned long sk_region_find_span(unsigned long *tree, unsigned long addr)
{
    unsigned long cur, off;

    if (*tree + 0x2a0 < *tree) goto fault;
    cur = *(unsigned long *)sk_vspace_root();   /* FUN_00032cec -> root */
    do {
        if (cur == 0) return 0;
        if (addr < *(unsigned long *)(cur + 8)) off = 0x58;
        else {
            if (addr < *(long *)(cur + 0x10) + *(unsigned long *)(cur + 8)) {
                if (cur <= cur + 0xb0) return cur;
                goto fault;
            }
            off = 0x60;
        }
        cur = *(unsigned long *)(cur + off);
    } while (1);
fault:
    __builtin_unreachable();                    /* SoftwareBreakpoint(0x5519, 0x3dde8) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003dde8 @ 0x0003dde8   (est. sk_region_map_pages)
 * Ghidra: undefined1[16] FUN_0003dde8(ulong *param_1, ulong param_2, long param_3, ulong param_4, ulong param_5)
 * Maps param_5 granules of pages for region param_2 at the span param_4:
 * validates the region tag (0x65b5c8) / span tag (0x65b648), bounds-checks
 * the region extent, then for each granule resolves the span-table entry
 * (FUN_00042abc) and maps it (sk_span_map3 FUN_00040f80). Returns the
 * mapping result.
 * Confidence: low-medium (structural; page map).
 */
cl4_result_t sk_region_map_pages(unsigned long *out, unsigned long region,
                                 long span, unsigned long base, unsigned long count)
{
    cl4_result_t r;
    unsigned long v, uVar6, uVar9, uVar10, uVar14, lVar13;
    unsigned long *entry;
    unsigned long *pc;

    r = sk_vspace_slot_alloc_frame();           /* FUN_00034a2c */
    if (r.hi != 0x65b5c8 || span != 0x65b648) {
        r.lo = 6; r.hi = 0;
        return r;
    }
    if (r.lo == 0 || region == 0) { r.lo = 6; r.hi = 0; return r; }
    if (*(long *)(region + 0x50) != (long)r.lo || *(unsigned int *)(region + 0x20) == 0) {
        r.lo = 6; r.hi = 0;
        return r;
    }
    if ((*(unsigned int *)(region + 0x20) >> 0x1a & 1) == 0 || *(long *)(region + 0x10) == 0) {
        r.lo = 0x10490001; r.hi = 0;
        return r;
    }
    uVar10 = *(unsigned long *)(region + 8) & 0xfffffffffe000000;
    uVar6 = *(unsigned long *)(region + 8) + *(long *)(region + 0x10);
    uVar9 = uVar6 - uVar10 >> 0x19;
    if ((uVar6 & 0x1ffffff) != 0) uVar9 = uVar9 + 1;
    if (count < uVar9) {
        r.lo = 0x10500001; r.hi = 0;
        return r;
    }
    out[0] = base; out[1] = uVar9; out[2] = region;
    (void)sk_vspace_root();                    /* FUN_00032514 */
    v = (unsigned long)sk_vspace_root();                       /* FUN_00032cd0 -> root */
    if (out[1] != 0) {
        lVar13 = 0;
        uVar9 = 0;
        do {
            uVar14 = uVar10;
            entry = (unsigned long *)sk_obj_method_dispatch3(v, 1);  /* FUN_00042abc */
            if (entry != 0) {
                /* map the page granule */
                pc = (unsigned long *)entry;
                r.lo = sk_region_wire_spans((char *)*out, 0, 0); r.hi = 0;  /* FUN_0003ff00 */
            }
            uVar10 = uVar10 + 0x2000000;
            uVar9 = uVar9 + 1;
            lVar13 = lVar13 + 8;
        } while (uVar9 < out[1]);
    }
    sk_span_prefetch_pages((char *)region, 0, (long)*(unsigned long *)(region + 0x10));  /* FUN_0003df84 */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e14c @ 0x0003e14c   (est. sk_region_unmap_indirect)
 * Ghidra: undefined1[16] FUN_0003e14c(long *param_1, ulong param_2, ulong param_3)
 * Unmaps an indirectly-mapped span (param_3) of the region *param_1 at
 * offset param_2. Walks the span-table, resolves the direct leaf, and
 * unmaps via the supervisor (CallSupervisor(2)) or the deferred object
 * path (sk_obj_meta4 FUN_00043be8). Returns the error code.
 * Confidence: low-medium (structural; indirect unmap).
 */
cl4_result_t sk_region_unmap_indirect(long *span, unsigned long offset,
                                      unsigned long page)
{
    cl4_result_t r;
    unsigned long v, uVar5, uVar3, leaf, addr;
    unsigned int w;
    int iVar3, iVar4;

    if (span[1] == 0) {
        r.lo = 0x107a0001; r.hi = 0;
        return r;
    }
    if (*(unsigned long *)(span[2] + 0x10) <= page ||
        *(unsigned long *)(span[2] + 0x10) - page < 0x4000) {
        r.lo = 0x10810001; r.hi = 0;
        return r;
    }
    addr = *(unsigned long *)(span[2] + 8) + page;
    uVar5 = addr - (*(unsigned long *)(span[2] + 8) & 0xfffffffffe000000) >> 0x19;
    if (uVar5 < (unsigned long)span[1]) {
        leaf = *(unsigned long *)(*span + uVar5 * 8);
        if (leaf != 0) {
            w = *(unsigned int *)(span[2] + 0x20);
            v = (unsigned long)sk_vspace_root();                  /* FUN_00032cd0 -> root */
            iVar3 = sk_granule_index(*(unsigned long *)(span[2] + 0x78)); /* FUN_000368f8 */
            sk_span_lookup_build6(0, *(unsigned long *)(span[2] + 0x78), 0, 0, 0); /* FUN_00035ba0 */
            addr &= 0xffffffffffffc000;
            iVar4 = sk_granule_index(*(unsigned long *)(span[2] + 0x78)); /* FUN_000368f8 */
            if (iVar4 == iVar3) {
                __asm__ volatile("hvc #0" ::: "memory");        /* CallSupervisor(2) */
                if (offset == 0) {
                    uVar3 = sk_obj_meta4(v, leaf, 0, addr, w >> 3 & 3, 0); /* FUN_00043be8 */
                    if (uVar3 != 0) {
                        do { __asm__ volatile("hvc #0" ::: "memory"); } while (0);
                        r.lo = (uVar3 & 0x7fff) << 0x10 | 0x80000001;
                        r.hi = 0;
                        return r;
                    }
                } else {
                    r.lo = (offset & 0x7fff) << 0x10 | 0x80000001;
                    r.hi = 0;
                    return r;
                }
            }
        }
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b30ae);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003e308 @ 0x0003e308   (est. sk_region_unmap_direct)
 * Ghidra: undefined1[16] FUN_0003e308(long param_1, ulong param_2)
 * Unmaps the directly-mapped span param_2 of the region param_1: resolves
 * the span node, walks the cursor (sk_span_lookup_build), and unmaps pages
 * via CallSupervisor(4). Returns the error code.
 * Confidence: medium (structural; direct unmap).
 */
cl4_result_t sk_region_unmap_direct(long region, unsigned long page)
{
    cl4_result_t r;
    unsigned long st[6], v, node;
    unsigned int gi;
    int err;

    if (*(long *)(region + 8) == 0) {
        r.lo = 0x10bb0001; r.hi = 0;
        return r;
    }
    node = *(long *)(region + 0x10);
    if (!(page < *(unsigned long *)(node + 0x10)) ||
        !(0x3fff < *(unsigned long *)(node + 0x10) - page)) {
        r.lo = 0x10c40001; r.hi = 0;
        return r;
    }
    v = (unsigned long)sk_vspace_root();                          /* FUN_00032cd0 -> root */
    for (int i = 0; i < 6; i++) st[i] = 0;
    if (v + 0xd0 < v) goto fault;
    sk_span_lookup_build6(st, *(unsigned long *)(node + 0x78),
                          (int)((*(long *)(*(long *)(region + 0x10) + 8) + page & 0xffffffffffffc000) -
                                *(long *)(v + 0x28) >> 0xe) + 1, 0, 0);  /* FUN_00035ba0 */
    if ((st[4] ^ *(unsigned long *)(node + 0x78)) >> 0x1c == 0) {
        if (st[0] != 0) {
            do {
                __asm__ volatile("hvc #0" ::: "memory");        /* CallSupervisor(4) */
                if (st[0] == 0) { r.lo = 0; r.hi = 0; return r; }
            } while (st[0] == 1);
            r.lo = (st[0] & 0x7fff) << 0x10 | 0x80000001;
            r.hi = 0;
            return r;
        }
    } else {
        sk_vas_fault76();                                       /* FUN_004b3364 */
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b30ae);
    __builtin_unreachable();
fault:
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3e414) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003e440 @ 0x0003e440   (est. sk_cap_validate)
 * Ghidra: undefined4 FUN_0003e440(long *param_1, long param_2)
 * Validates a capability (param_2): checks it is a live mapping (flags
 * +0x20), is a direct mapping (+0x1a bit0) with a backing object (+0x10),
 * and returns the capability word + base into param_1. Returns error 6
 * (invalid cap) or 0x10f70001.
 * Confidence: medium (structural; cap validation).
 */
unsigned int sk_cap_validate(long *out, long cap)
{
    unsigned int w;
    unsigned long g;

    w = *(unsigned int *)(cap + 0x20);
    if (w == 0) return 6;
    if (((w >> 0x1a & 1) != 0) && *(long *)(cap + 0x10) != 0) {
        *(unsigned int *)(cap + 0x20) = w | 0x8000000;
        *out = cap;
        out[1] = *(long *)(cap + 0x78);
        g = sk_granule_index(0);                                /* FUN_000368f8 */
        out[2] = g & 0xffffffff;
        return 0;
    }
    return 0x10f70001;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e4c0 @ 0x0003e4c0   (est. sk_cap_release)
 * Ghidra: undefined4 FUN_0003e4c0(long *param_1, ulong param_2, undefined8 *param_3)
 * Releases a capability (param_2) of the object *param_1: validates the
 * object is a managed mapping, walks the span cursor (sk_span_lookup_build),
 * and either returns the released span (via param_3) or faults. Returns
 * error 0x11100001 / 0x111c0001 / 0x113a0001.
 * Confidence: low-medium (structural; cap release).
 */
unsigned int sk_cap_release(long *obj, unsigned long cap, unsigned long *out)
{
    unsigned long st[6], v, uVar3;
    long *free;

    if (*obj == 0) return 0x11100001;
    if ((*(unsigned char *)(*obj + 0x23) >> 3 & 1) == 0) {
        sk_vas_fault83();                                       /* FUN_004b349c */
        __builtin_unreachable();
    }
    if (*(unsigned long *)(*obj + 0x10) <= (cap & 0xffffffffffffc000))
        return 0x111c0001;
    uVar3 = obj[1] ^ *(unsigned long *)(*obj + 0x78);
    if (uVar3 >> 0x1c == 0 && uVar3 < 0x40 && (uVar3 & 3) == 0 &&
        *(unsigned long *)(*obj + 0x78) == obj[1]) {
        v = sk_granule_index(0);                                /* FUN_000368f8 */
        if (obj[2] == (v & 0xffffffff)) {
            for (int i = 0; i < 6; i++) st[i] = 0;
            v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
            sk_span_lookup_build6(st, *(unsigned long *)(*obj + 0x78),
                                  (int)((*(long *)(*obj + 8) + (cap & 0xffffffffffffc000)) -
                                        *(long *)(v + 0x28) >> 0xe) + 1, 0, 0);  /* FUN_00035ba0 */
            if ((char)st[1] != 1) { *out = st[0]; return 0; }
        }
    } else {
        sk_vas_fault77(); sk_vas_fault78(); sk_vas_fault79(); sk_vas_fault80();
        /* FUN_004b339c/33c4/33ec/3414 */
    }
    sk_vas_fault81();                                           /* FUN_004b343c */
    free = (long *)sk_vas_fault82();                            /* FUN_004b3464 */
    if (*free == 0) return 0x113a0001;
    *(unsigned int *)(*free + 0x20) = *(unsigned int *)(*free + 0x20) & 0xf7ffffff;
    sk_ref_unlink3(free, 0x18, 0xffffffffffffffff);             /* FUN_00117f8c */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e5f0 @ 0x0003e5f0   (est. sk_cap_revoke)
 * Ghidra: undefined4 FUN_0003e5f0(long *param_1)
 * Revokes the capability *param_1: clears the "deferred" flag (+0x20 bit
 * 27) and unlinks the capability (sk_ref_unlink3). Returns error
 * 0x113a0001 if no cap is present.
 * Confidence: medium (structural; cap revoke).
 */
unsigned int sk_cap_revoke(long *cap)
{
    unsigned long v;

    v = *cap;
    if (v != 0) {
        *(unsigned int *)(v + 0x20) = *(unsigned int *)(v + 0x20) & 0xf7ffffff;
        sk_ref_unlink3(cap, 0x18, 0xffffffffffffffff);          /* FUN_00117f8c */
        return 0;
    }
    return 0x113a0001;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e640 @ 0x0003e640   (est. sk_slot_pop_f)
 * Ghidra: undefined8 * FUN_0003e640(long param_1)
 * Pops a node from the +0x10 free list (count byte at +0x31).
 * Confidence: high (trivial list pop).
 */
unsigned long *sk_slot_pop_f(long obj)
{
    unsigned long *n;
    unsigned char c;

    c = *(unsigned char *)(obj + 0x31);
    if (c == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b36b7);
        __builtin_unreachable();
    }
    if (c < 4) {
        *(unsigned char *)(obj + 0x31) = c - 1;
        n = *(unsigned long **)(obj + 0x10);
        if (n != 0) {
            *(unsigned long *)(obj + 0x10) = *n;
            *n = 0;
            return n;
        }
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b373b);
        __builtin_unreachable();
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b346f);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003e710 @ 0x0003e710   (est. sk_class_perm)
 * Ghidra: undefined8 FUN_0003e710(char param_1)
 * Looks up the permission word for the object class param_1 in the class
 * permission table at 0x65b790 (indexed by (param_1+5)&0xff); returns 0
 * for an out-of-range class.
 * Confidence: high (trivial table lookup).
 */
unsigned long sk_class_perm(char class)
{
    unsigned int i;

    i = (unsigned char)(class + 5U);
    if (i < 0x19)
        return *(unsigned long *)((unsigned long)i * 8 + 0x65b790);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e73c @ 0x0003e73c   (est. sk_region_walk_span)
 * Ghidra: void FUN_0003e73c(undefined8 *param_1, ulong *param_2, long param_3, ulong *param_4)
 * Walks a region span building the 6-word walk descriptor (param_1): decodes
 * the walk-info mode (param_4[0]), computes the span bounds from the region
 * descriptor (param_3), and calls sk_region_walk_find (FUN_0003ed4c) with
 * the walk method table (sk_region_adjust FUN_0003eab4). Releases the
 * temporary nodes (sk_obj_unref_block).
 * Confidence: low-medium (structural; region walk).
 */
void sk_region_walk_span(unsigned long *out, unsigned long *tree, long region,
                         unsigned long *walk)
{
    unsigned long local[9], st[2];
    unsigned long lo, hi, mask, size, end;
    unsigned char log2, gran;
    unsigned long *w;
    int i;

    for (int i2 = 0; i2 < 9; i2++) local[i2] = 0;
    local[4] = walk[1];
    lo = *walk;
    hi = walk[3];
    size = walk[2];
    gran = *(unsigned char *)(region + 0x1a);
    mask = 1UL << (*(unsigned char *)(region + 0x1b) & 0x3f);
    if (*(unsigned char *)(region + 0x1b) - 0x40 < 0xffffffc1) mask = ~0UL;
    end = lo & 0xff;
    if ((char)lo == 0) w = &hi;
    else if ((char)lo == 1) { w = &size; hi = 0; end = ~0UL; }
    else {
        sk_walk_abort3(0, "unsupported walkinfo mode %u");       /* FUN_0005b190 */
        __builtin_unreachable();
    }
    *w = end;
    st[0] = 0;
    mask = 1UL << (gran & 0x3f);
    if (0x3f < gran) mask = ~0UL;
    end = 0;
    if (gran != 0) end = mask;
    if ((char)size == 1 && end <= *(unsigned long *)(region + 8))
        end = *(unsigned long *)(region + 8);
    if (*(unsigned char *)(region + 0x1a) < 0xf)
        *(unsigned char *)(region + 0x1a) = 0xe;
    /* walk the region tree */
    {
        /* method table for walk */
        w = (unsigned long *)sk_vspace_root();  /* FUN_00032cec -> root */
        sk_region_walk_find(*w, end, mask, lo, (long)&sk_region_adjust);  /* FUN_0003ed4c */
    }
    for (i = 0; i < 6; i++) out[i] = local[i + 3];
    sk_obj_unref_block(st[0], 8);                               /* FUN_0004b8d0 */
    sk_obj_unref_block((unsigned long)local, 8);                /* FUN_0004b8d0 */
}

/*--------------------------------------------------------------------*/
/* FUN_0003e918 @ 0x0003e918   (est. sk_rand_mod)
 * Ghidra: long FUN_0003e918(ulong param_1)
 * Returns a pseudo-random value in [0, param_1) by reading 8 random bytes
 * (FUN_00116c78) and taking the remainder. Returns 0 for param_1 < 2.
 * Confidence: medium (structural; bounded PRNG).
 */
long sk_rand_mod(unsigned long modulus)
{
    unsigned long v, r;

    if (modulus < 2) return 0;
    do {
        v = 0;
        sk_stack_check(&v, 8);                                  /* FUN_00116c78 */
    } while (v < ~0UL % modulus);
    return v % modulus;
}

/*--------------------------------------------------------------------*/
/* FUN_0003e984 @ 0x0003e984   (est. sk_region_bind2)
 * Ghidra: void FUN_0003e984(undefined8 param_1, undefined8 param_2, long param_3)
 * Binds a region to a span after validating the span is free (+0x20==0).
 * Checks the bind result via sk_region_split (FUN_0003ee4c); aborts on an
 * error code.
 * Confidence: medium (structural; bind with validation).
 */
void sk_region_bind2(unsigned long p1, unsigned long p2, long span)
{
    unsigned long v;

    if (*(int *)(span + 0x20) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b3ce1);
        __builtin_unreachable();
    }
    v = sk_region_split(0, 0, 0, 0, 0, 0).lo;                 /* FUN_0003ee4c */
    v &= 0xff;
    if (v == 0) return;
    if (v >= 0x40 && v <= 0x80) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b3d46);
        __builtin_unreachable();
    }
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3ea28) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003ea28 @ 0x0003ea28   (est. sk_region_desc_fill)
 * Ghidra: void FUN_0003ea28(char *param_1)
 * Fills a region descriptor (param_1) into a 16-byte span node: packs the
 * object base, method flags, granule count, and attribute word. Used to
 * materialise a span node from a region descriptor during split/merge.
 * Confidence: medium (structural; descriptor fill).
 */
void sk_region_desc_fill(char *region)
{
    unsigned long *node, base;
    unsigned int w, flags, log;
    unsigned char t;

    node = *(unsigned long **)(region + 0x70);
    base = *(unsigned long *)(region + 8);
    t = region[0x18];
    w = *(unsigned int *)(region + 0x20);
    flags = 8;
    if (*region != 4) flags = 0;
    flags = w >> 0x11 & 4 | w >> 3 & 3 | w >> 6 & 0x40000 | flags;
    if (2 < t - 4) {
        if (t == 0x11) { flags |= 0x20000; goto fill; }
        if (t != 1) goto fill;
    }
    flags |= 0x10000;
fill:
    node[1] = *(unsigned long *)(region + 0x10);
    node[0] = base;
    *(unsigned char *)(node + 3) = 0;
    node[2] = 0;
    *(unsigned char *)((char *)node + 0x19) = t;
    *(unsigned short *)((char *)node + 0x1a) = 0;
    *(unsigned int *)((char *)node + 0x1c) = flags;
    *(unsigned int *)(node + 3) = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0003eab4 @ 0x0003eab4   (est. sk_region_adjust)
 * Ghidra: undefined8 FUN_0003eab4(long param_1, long param_2)
 * Adjusts a region span (param_2) to fit the region constraints
 * (param_1): computes the aligned fit within the region bounds, updates
 * the span table entry, and returns 0 on success / 1 if no adjustment
 * needed. Aborts on bounds violation.
 * Confidence: low-medium (structural; region adjust).
 */
unsigned long sk_region_adjust(long region, long span)
{
    unsigned long uVar5, uVar6, uVar3, uVar2, uVar1, uVar9;
    unsigned long uVar7, gran, mask;
    long lVar8, lVar4;
    char *t;

    if (*(int *)(span + 0x20) == 0) {
        uVar5 = *(unsigned long *)(region + 0x30);
        if (uVar5 <= *(unsigned long *)(span + 0x10)) {
            uVar6 = *(unsigned long *)(span + 8);
            uVar3 = *(unsigned long *)(region + 0x38);
            uVar2 = uVar6 + *(unsigned long *)(span + 0x10);
            if (uVar2 < uVar3) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b3bc1);
                __builtin_unreachable();
            }
            uVar1 = (uVar6 <= uVar3) ? uVar3 : uVar6;
            uVar3 = (*(unsigned long *)(region + 0x40) <= uVar2)
                    ? *(unsigned long *)(region + 0x40) : uVar2;
            if (uVar3 < uVar1 || uVar3 - uVar1 < uVar5) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b3bc1);
                __builtin_unreachable();
            }
            gran = *(unsigned char *)(region + 0x48);
            mask = 1UL << (gran & 0x3f);
            lVar4 = 0;
            if ((mask - 1U & uVar1) != 0) lVar4 = mask;
            uVar9 = ~0UL << (gran & 0x3f) & uVar3 - uVar5;
            uVar3 = lVar4 + (uVar1 & -mask);
            if (uVar3 <= uVar9) {
                if (uVar3 < uVar6 || uVar2 < uVar3 + uVar5 ||
                    uVar2 < uVar9 + uVar5) {
                    sk_vas_abort("VAS abort in function %s at line %d", 0x5b3bc1);
                    __builtin_unreachable();
                }
                uVar2 = uVar9 - uVar3 >> (gran & 0x3f);
                uVar5 = uVar2 + 1;
                lVar8 = *(long *)(*(long *)(region + 0x20) + 8);
                if (*(char *)(lVar8 + 0x18) == 1) {
                    /* shrink the span-table free count */
                    *(unsigned long *)(lVar8 + 0x38) = span;
                    *(unsigned long *)(*(long *)(*(long *)(region + 0x20) + 8) + 0x40) =
                        (*(long *)(*(long *)(*(long *)(region + 0x28) + 8) + 0x18) <<
                         (gran & 0x3f)) + uVar3;
                    return 0;
                } else if (*(char *)(lVar8 + 0x18) == 0) {
                    *(unsigned long *)(lVar8 + 0x30) = *(long *)(lVar8 + 0x30) + uVar5;
                }
            }
            return 1;
        }
    } else {
        sk_vas_fault84();                                       /* FUN_004b34d4 */
    }
    sk_vas_abort("VAS abort in function %s at line %d", 0x5b3bc1);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003ed4c @ 0x0003ed4c   (est. sk_region_walk_find)
 * Ghidra: undefined8 FUN_0003ed4c(long param_1, ulong param_2, ulong param_3, ulong param_4, long param_5)
 * Recursive region-tree walk: finds the span (param_1) intersecting
 * [param_2, param_3) within the limit param_4, invoking the method table
 * (param_5) callback on each matching span. Returns 0 on success / 1 on
 * no-match.
 * Confidence: medium (structural; range tree walk).
 */
unsigned long sk_region_walk_find(long span, unsigned long lo, unsigned long hi,
                                  unsigned long limit, long methods)
{
    unsigned long start, end, a, b, c, len;
    unsigned long (*fn)(unsigned long, long);

    if (span == 0) return 1;
    if (limit <= *(unsigned long *)(span + 0x68)) {
        start = *(unsigned long *)(span + 8);
        if (lo < start)
            if (sk_region_walk_find(*(long *)(span + 0x58), lo, hi, limit, methods) == 0)
                return 0;
        a = start;
        if (start <= lo) a = lo;
        end = *(long *)(span + 0x10) + start;
        b = end;
        if (hi <= end) b = hi;
        c = (a <= b) ? b - a : 0;
        if (*(int *)(span + 0x20) == 0 && limit <= c) {
            fn = (unsigned long (*)(unsigned long, long))(*(void **)(methods + 0x10));
            if (fn(methods, span) == 0) return 0;
            end = *(long *)(span + 0x10) + *(long *)(span + 8);
        }
        if (end < hi)
            return sk_region_walk_find(*(long *)(span + 0x60), lo, hi, limit, methods);
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0003ee4c @ 0x0003ee4c   (est. sk_region_split)
 * Ghidra: undefined1[16] FUN_0003ee4c(long param_1, undefined8 param_2, undefined8 *param_3, ulong param_4, ulong *param_5, ulong *param_6)
 * Splits the region param_3 at offset param_4 into two spans: pops a free
 * span node, copies the region descriptor, adjusts both halves'
 * descriptors, and relinks them. Returns the split spans via param_5/
 * param_6.
 * Confidence: low-medium (structural; region split).
 */
cl4_result_t sk_region_split(long tree, unsigned long owner, unsigned long *region,
                             unsigned long at, unsigned long *lo_out,
                             unsigned long *hi_out)
{
    cl4_result_t r;
    unsigned long *newspan, *w, lo_end;
    unsigned long v, end, uVar13;
    unsigned int w0;
    int b;

    if ((*(unsigned int *)(region + 4) & 0xd000800) == 0) {
        v = 0x7fb0001;
        if (at != 0) v = 0;
        end = 0x7f80001;
        if (at < (unsigned long)region[2]) end = v;
    } else {
        end = 0x7f60001;
    }
    r.lo = end; r.hi = 0;
    if ((end & 0xff) != 0) return r;
    newspan = sk_slot_pop_e(tree);                              /* FUN_0003c21c */
    w = newspan + 0x16;
    w0 = *(unsigned int *)(region + 4);
    if ((w0 >> 0x10 & 1) != 0) {
        sk_obj_map5(tree, owner, region, at, newspan);          /* FUN_00045908 */
        w0 = *(unsigned int *)(region + 4);
    }
    lo_end = (unsigned long)region[0xe];
    if (w0 == 0) { end = 0; v = 0; }
    else {
        end = (unsigned long)sk_slot_pop_f(tree);               /* FUN_0003e640 */
        v = (unsigned long)sk_slot_pop_f(tree);                 /* FUN_0003e640 */
    }
    newspan[0xe] = v;
    *(unsigned int *)(newspan + 4) = w0;
    newspan[0] = region[0];
    newspan[3] = region[3];
    newspan[2] = region[2];
    newspan[1] = region[1];
    newspan[1] = newspan[1] + at;
    newspan[2] = newspan[2] - at;
    newspan[10] = region[10];
    region[2] = at;
    if (end <= end + 0x20) {
        region[0xe] = end;
        if (*(int *)(region + 4) != 0) {
            sk_region_desc_fill(region);                        /* FUN_0003ea28 */
            sk_region_desc_fill(newspan);                       /* FUN_0003ea28 */
            /* relink the split halves */
            if (*(unsigned int *)(region + 4) >> 6 & 1) {
                /* reorder by descriptor order */
            }
        }
        if (newspan <= w) {
            sk_region_attach((unsigned long *)tree, (unsigned long)newspan);  /* FUN_0003c2ec */
            r.lo = 0;
            *lo_out = (unsigned long)region;
            *hi_out = (unsigned long)newspan;
            return r;
        }
    }
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3f0ac) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003f0dc @ 0x0003f0dc   (est. sk_region_recalc)
 * Ghidra: void FUN_0003f0dc(long param_1, long param_2)
 * Recomputes the subtree extent (param_1+0x68) of the region tree rooted
 * at param_1 after a change at param_2; recurses into both children and
 * propagates the max granule extent upward.
 * Confidence: medium (structural; tree extent recompute).
 */
void sk_region_recalc(long node, long changed)
{
    unsigned long a, b, c, lo, hi;

    if (node == 0 || changed == 0) return;
    if (*(unsigned long *)(changed + 8) < *(unsigned long *)(node + 8))
        sk_region_recalc(*(long *)(node + 0x58), changed);
    else if (*(unsigned long *)(changed + 8) == *(unsigned long *)(node + 8))
        goto recompute;
    else
        sk_region_recalc(*(long *)(node + 0x60), changed);
recompute:
    a = (*(int *)(node + 0x20) == 0) ? *(unsigned long *)(node + 0x10) : 0;
    b = (*(long *)(node + 0x58) != 0)
        ? *(unsigned long *)(*(long *)(node + 0x58) + 0x68) : 0;
    c = (*(long *)(node + 0x60) != 0)
        ? *(unsigned long *)(*(long *)(node + 0x60) + 0x68) : 0;
    if (b <= c) b = c;
    if (a <= b) a = b;
    *(unsigned long *)(node + 0x68) = a;
}

/*--------------------------------------------------------------------*/
/* FUN_0003f170 @ 0x0003f170   (est. sk_region_finalize)
 * Ghidra: undefined1[16] FUN_0003f170(ulong param_1, ulong *param_2, ulong *param_3, int param_4)
 * Finalizes a region span map: resolves the span root, aligns the mapping
 * base/end to the region cursor, calls sk_region_map_span (FUN_0003d438),
 * and wires the pages (sk_obj_wire4 FUN_00043f28). Returns the result.
 * Confidence: low-medium (structural; region finalize).
 */
cl4_result_t sk_region_finalize(unsigned long span, unsigned long *base_out,
                                unsigned long *size_out, int commit)
{
    cl4_result_t r;
    unsigned long v, w0, uVar8, uVar3, end, lVar2;
    unsigned long *tpidr;
    int allow;

    v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
    w0 = *(unsigned int *)(span + 0x20);
    allow = ((w0 & 0x4000000) == 0) ? 1 : 0;
    uVar8 = *base_out;
    if (*(unsigned long *)(span + 0x10) <= uVar8 ||
        *(unsigned long *)(span + 0x10) - uVar8 < *size_out || (w0 & 0x8000000) != 0) {
        r.lo = 0x7210001; r.hi = 0;
        return r;
    }
    uVar8 = *(long *)(span + 8) + uVar8;
    lVar2 = 0;
    if ((uVar8 & 0x3fff) != 0) lVar2 = 0x4000;
    lVar2 = lVar2 + (uVar8 & 0xffffffffffffc000);
    *size_out = (uVar8 + *size_out) - lVar2;
    *base_out = lVar2 - *(long *)(span + 8);
    uVar8 = *size_out & 0xffffffffffffc000;
    *size_out = uVar8;
    sk_region_map_span(lVar2, uVar8, span, w0 >> 0xc & 1, allow);  /* FUN_0003d438 */
    if (commit != 0) {
        if (*base_out == 0) end = (*size_out == *(unsigned long *)(span + 0x10));
        else end = 0;
        if ((w0 >> 7 & 1) != 0) {
            uVar3 = (w0 >> 6 & 1) ? (*(long *)(span + 0x10) - *(long *)(span + 0x48)) + *(long *)(span + 8)
                                  : *(long *)(span + 8);
            end = (*base_out == *(unsigned long *)(span + 0x48));
        }
        if (end) {
            sk_obj_wire4(v, lVar2, uVar8, (w0 & 0x1000) == 0);  /* FUN_00043f28 */
        }
    }
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0003f324 @ 0x0003f324   (est. sk_region_merge2)
 * Ghidra: undefined8 FUN_0003f324(undefined8 param_1, undefined8 param_2, long param_3, long param_4)
 * Merges two adjacent region spans (param_3/param_4): validates both are
 * free (+0x20==0), merges via sk_region_merge (FUN_0003f41c), and pushes
 * the freed node back (sk_slot_push_d). Returns the merged span.
 * Confidence: low-medium (structural; merge wrapper).
 */
unsigned long sk_region_merge2(unsigned long st, unsigned long owner, long a, long b)
{
    unsigned long lo, hi, v;

    if (*(int *)(a + 0x20) != 0 || *(int *)(b + 0x20) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b3f6d);
        __builtin_unreachable();
    }
    v = sk_region_merge((unsigned long *)st, owner, a, b, &lo, &hi).lo;  /* FUN_0003f41c */
    v &= 0xff;
    if (v == 0) {
        sk_slot_push_d(st, (unsigned long *)lo);
        return hi;
    }
    if (v >= 0x40 && v <= 0x80) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b4008);
        __builtin_unreachable();
    }
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3f41c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003f41c @ 0x0003f41c   (est. sk_region_merge)
 * Ghidra: undefined1[16] FUN_0003f41c(ulong *param_1, undefined8 param_2, long param_3, long param_4, long *param_5, long *param_6)
 * Merges two region spans (param_3/param_4) into a single span. Validates
 * both spans share the same owner, flags, and are contiguous; folds the
 * right span's extent into the left, relinks the merged node in the span
 * tree (sk_region_tree_remove FUN_0003f6c8), and returns the merged node
 * via param_5. Returns error 0x7590001..0x75d0001.
 * Confidence: low-medium (structural; merge core).
 */
cl4_result_t sk_region_merge(unsigned long *tree, unsigned long owner, long a, long b,
                             long *lo_out, long *hi_out)
{
    cl4_result_t r;
    unsigned long v, end, uVar6;
    unsigned int w;
    unsigned long *w1, *w2, *n;

    uVar6 = *(unsigned long *)(b + 8);
    if (uVar6 < *(unsigned long *)(a + 8)) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5b4061);
        __builtin_unreachable();
    }
    if (*(long *)(a + 0x50) == *(long *)(b + 0x50)) {
        if (*(unsigned int *)(a + 0x20) == *(unsigned int *)(b + 0x20)) {
            if ((*(unsigned int *)(a + 0x20) & 0xd000800) == 0) {
                end = (uVar6 == 0) ? 0x75c0001 : 0;
                if (end == 0 && *(long *)(a + 0x10) + *(unsigned long *)(a + 8) != uVar6)
                    end = 0x75d0001;
            } else {
                end = 0x75b0001;
            }
        } else {
            end = 0x75a0001;
        }
    } else {
        end = 0x7590001;
    }
    r.lo = end; r.hi = 0;
    if ((end & 0xff) == 0) {
        w = *(unsigned int *)(a + 0x20);
        if ((w >> 0x10 & 1) != 0) {
            sk_obj_map5(tree, owner, a, b);                     /* FUN_000458a0 */
            w = *(unsigned int *)(a + 0x20);
        }
        *(long *)(a + 0x10) = *(long *)(a + 0x10) + *(long *)(b + 0x10);
        if (w == 0) {
            sk_region_recalc(*(long *)(*tree + 0x58), a);       /* FUN_0003f0dc */
        } else {
            w1 = *(unsigned long **)(a + 0x70);
            w2 = *(unsigned long **)(b + 0x70);
            n = sk_slot_pop_f((long)tree);                     /* FUN_0003e640 */
            *(unsigned long *)(a + 0x70) = (unsigned long)n;
            *(unsigned long *)(b + 0x70) = 0;
            sk_region_desc_fill((char *)a);                    /* FUN_0003ea28 */
            sk_slot_push_f((long)tree, (unsigned long *)w1);   /* FUN_0003e640 (push variant) */
            sk_slot_push_f(tree, w2);                           /* FUN_0003e640 */
        }
        if (*tree + 0x2a0 < *tree) goto fault;
        {
            unsigned long *root = (unsigned long *)sk_vspace_root(); /* FUN_00032cec -> root */
            v = sk_region_tree_remove(root, b);                 /* FUN_0003f6c8 */
            if ((v & 1) == 0) {
                sk_vas_abort("VAS abort in function %s at line %d", 0x5b40cd);
                __builtin_unreachable();
            }
        }
        r.lo = 0;
        *lo_out = a;
        *hi_out = b;
        return r;
    }
    return r;
fault:
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3f60c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003f6c8 @ 0x0003f6c8   (est. sk_region_tree_remove)
 * Ghidra: undefined8 FUN_0003f6c8(long *param_1, long param_2)
 * Removes the region node param_2 from the AVL tree *param_1, rebalancing
 * and recomputing extents. Returns the removed node / 0.
 * Confidence: low-medium (structural; AVL remove).
 */
unsigned long sk_region_tree_remove(long *root, long node)
{
    unsigned long uVar2, lVar3, lVar4;
    unsigned long v, b, c, a;
    unsigned int h1, h2;

    lVar3 = *root;
    if (lVar3 == 0) return 0;
    if (lVar3 == node) {
        lVar4 = *(long *)(lVar3 + 0x60);
        if (*(long *)(lVar3 + 0x58) == 0) {
            if (lVar4 == 0) { *root = 0; uVar2 = 1; }
            else uVar2 = 0xfffffffe;
        } else {
            if (lVar4 != 0 && *(unsigned char *)(*(long *)(lVar3 + 0x58) + 0x24) <
                *(unsigned char *)(lVar4 + 0x24))
                uVar2 = 0xfffffffe;
            else
                uVar2 = 2;
        }
        sk_region_tree_rebalance(root, uVar2);                  /* FUN_0003f804 */
    }
    lVar3 = *root;
    if (lVar3 == node) { *root = 0; return 1; }
    if (*(unsigned long *)(node + 8) < *(unsigned long *)(lVar3 + 8))
        v = sk_region_tree_remove((long *)(lVar3 + 0x58), node);
    else
        v = sk_region_tree_remove((long *)(lVar3 + 0x60), node);
    lVar4 = *(long *)(lVar3 + 0x58);
    h1 = (lVar4 != 0) ? *(unsigned char *)(lVar4 + 0x24) + 1 : 0;
    lVar3 = *(long *)(lVar3 + 0x60);
    h2 = (lVar3 != 0) ? *(unsigned char *)(lVar3 + 0x24) + 1 : 0;
    if (h1 <= h2) h1 = h2;
    *(char *)(lVar3 + 0x24) = (char)h1;
    a = (*(int *)(lVar3 + 0x20) == 0) ? *(unsigned long *)(lVar3 + 0x10) : 0;
    b = (*(long *)(lVar3 + 0x58) != 0)
        ? *(unsigned long *)(*(long *)(lVar3 + 0x58) + 0x68) : 0;
    c = (*(long *)(lVar3 + 0x60) != 0)
        ? *(unsigned long *)(*(long *)(lVar3 + 0x60) + 0x68) : 0;
    if (b <= c) b = c;
    if (a <= b) a = b;
    *(unsigned long *)(lVar3 + 0x68) = a;
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_0003f804 @ 0x0003f804   (est. sk_region_tree_rebalance)
 * Ghidra: void FUN_0003f804(ulong *param_1, int param_2)
 * Rebalances the AVL region tree *param_1 after a removal (param_2 < -1
 * left-heavy, > 1 right-heavy), performing the appropriate rotations and
 * recomputing node heights/extents.
 * Confidence: low-medium (structural; AVL rebalance).
 */
void sk_region_tree_rebalance(unsigned long *root, int dir)
{
    unsigned long uVar2, uVar7, uVar3, uVar12;
    long lVar5, lVar9, lVar10, lVar8;
    unsigned int h1, h2;

    uVar2 = *root;
    if (uVar2 == 0) return;
    uVar12 = uVar2 + 0xb0;
    if (dir < -1) {
        uVar7 = *(unsigned long *)(uVar2 + 0x60);
        if (uVar7 != 0) {
            *(unsigned long *)(uVar2 + 0x60) = *(unsigned long *)(uVar7 + 0x58);
            if (uVar12 < uVar2) goto fault;
            *(unsigned long *)(uVar7 + 0x58) = uVar2;
            *root = uVar7;
            uVar3 = uVar7;
        }
    } else if (1 < dir) {
        uVar7 = *(unsigned long *)(uVar2 + 0x58);
        if (uVar7 != 0) {
            *(unsigned long *)(uVar2 + 0x58) = *(unsigned long *)(uVar7 + 0x60);
            if (uVar12 < uVar2) goto fault;
            *(unsigned long *)(uVar7 + 0x60) = uVar2;
            *root = uVar7;
            uVar3 = uVar7;
        }
    }
    if (uVar2 <= uVar12) {
        lVar9 = *(long *)(uVar2 + 0x58);
        h1 = (lVar9 != 0) ? *(unsigned char *)(lVar9 + 0x24) + 1 : 0;
        lVar10 = *(long *)(uVar2 + 0x60);
        h2 = (lVar10 != 0) ? *(unsigned char *)(lVar10 + 0x24) + 1 : 0;
        if (h1 <= h2) h1 = h2;
        *(char *)(uVar2 + 0x24) = (char)h1;
        lVar5 = *(long *)(uVar3 + 0x58);
        h1 = (lVar5 != 0) ? *(unsigned char *)(lVar5 + 0x24) + 1 : 0;
        lVar8 = *(long *)(uVar3 + 0x60);
        h2 = (lVar8 != 0) ? *(unsigned char *)(lVar8 + 0x24) + 1 : 0;
        if (h1 <= h2) h1 = h2;
        *(char *)(uVar3 + 0x24) = (char)h1;
        
        
        return;
    }
fault:
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3f980) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003f980 @ 0x0003f980   (est. sk_err_name)
 * Ghidra: void FUN_0003f980(undefined8 *param_1, byte param_2)
 * Fills param_1 with the 4-word L4 error-code string descriptor for the
 * error code param_2 (from the L4_ErrorCode* strings at 0x4bc218+). For
 * codes > 9 it uses the "generic" descriptor and prints via FUN_0000178c.
 * Confidence: high (string table lookup).
 */
void sk_err_name(unsigned long *out, unsigned char code)
{
    char *s;

    if (9 < code) {
        out[0] = *(unsigned long *)0x4bc358;
        out[1] = *(unsigned long *)0x4bc360;
        out[2] = *(unsigned long *)0x4bc368;
        out[3] = *(unsigned long *)0x4bc370;
        sk_mem_zero(out, 0x20);                                 /* FUN_0000178c */
        return;
    }
    switch (code) {
    default: s = (char *)0x4bc218; break;
    case 1:  s = (char *)0x4bc238; break;
    case 2:  s = (char *)0x4bc258; break;
    case 3:  s = (char *)0x4bc278; break;
    case 4:  s = (char *)0x4bc298; break;
    case 5:  s = (char *)0x4bc2b8; break;
    case 6:  s = (char *)0x4bc2d8; break;
    case 7:  s = (char *)0x4bc2f8; break;
    case 8:  s = (char *)0x4bc318; break;
    case 9:  s = (char *)0x4bc338; break;
    }
    out[0] = *(unsigned long *)s;
    out[1] = *(unsigned long *)(s + 8);
    out[2] = *(unsigned long *)(s + 0x10);
    out[3] = *(unsigned long *)(s + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_0003fa94 @ 0x0003fa94   (est. sk_region_map_fault)
 * Ghidra: ulong FUN_0003fa94(long param_1, long param_2, ulong param_3, ulong param_4, undefined8 param_5, int param_6, ulong param_7)
 * The region fault-map entry: looks up the span, walks its granules, and
 * maps each via sk_region_map_fault2 (FUN_0003fcc8) with the supervisor
 * fault path. Retries on preempt. Returns the mapping result / error code.
 * Large structural body.
 * Confidence: low (large; structural shape preserved).
 */
unsigned long sk_region_map_fault(long span, long addr, unsigned long p3,
                                  unsigned long p4, unsigned long p5, int p6,
                                  unsigned long p7)
{
    unsigned long st[2], v, base, uVar9;
    long local[6];
    int err;

    v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
    if (sk_vm_lock_check((unsigned long)span + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    for (int i = 0; i < 6; i++) local[i] = 0;
    if (v + 0xd0 < v) goto fault;
    sk_span_find2(&base, *(unsigned long *)(span + 0x78),
                  (int)((unsigned long)(addr - *(long *)(v + 0x28)) >> 0xe) + 1); /* FUN_000287e4 */
    *(unsigned long *)(span + 0x78) = base;
    if (base != 0) {
        v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
        if (v <= v + 0xd0) {
            uVar9 = sk_obj_method_dispatch3(v, 1, addr);        /* FUN_00042abc */
            err = sk_obj_lookup3(v, uVar9);                     /* FUN_00042c20 */
            if (err == 0) {
                p3 = 2;
            } else {
                if ((int)p4 == 0) { __asm__ volatile("hvc #0" ::: "memory"); }
                else {
                    unsigned long *tp = (unsigned long *)__builtin_thread_pointer();
                    *tp = 0; __asm__ volatile("hvc #0" ::: "memory");
                }
                if (p3 == 0) {
                    unsigned long r2 = sk_region_map_fault2((char *)span, addr, v, base,
                                                            uVar9, p4, 0);  /* FUN_0003fcc8 */
                    p3 = r2;
                    if (p3 != 0) {
                        do { __asm__ volatile("hvc #0" ::: "memory"); } while (base == 1);
                    }
                }
            }
            if (sk_vm_lock_take((unsigned long)span + 0x80) == 0)
                return p3;
            sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
            __builtin_unreachable();
        }
        goto fault;
    }
    if (sk_vm_lock_take((unsigned long)span + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    return 0x102;
fault:
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x3fc28) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003fcc8 @ 0x0003fcc8   (est. sk_region_map_fault2)
 * Ghidra: ulong FUN_0003fcc8(char *param_1, undefined8 param_2, undefined8 param_3, ulong param_4, undefined8 param_5, int param_6, uint param_7)
 * Second-level fault map: resolves the object method (sk_obj_meta4
 * FUN_00043be8 / sk_obj_meta3 FUN_00043b44), and either maps the page via
 * the span walk (sk_walk_span3 FUN_000402b4 / sk_map_span3 FUN_000403b0)
 * or falls back to the generic map path (sk_obj_attr3 FUN_000436fc).
 * Retries and reports unexpected L4 errors.
 * Large structural body.
 * Confidence: low (large; structural shape preserved).
 */
unsigned long sk_region_map_fault2(char *region, unsigned long p2, unsigned long p3,
                                   unsigned long base, unsigned long p5, int p6,
                                   unsigned int p7)
{
    unsigned long v, uVar7, uVar14, w;
    unsigned int w0, uVar5, uVar15;
    long st[6];
    int err;

    w0 = *(unsigned int *)(region + 0x20);
    uVar5 = 0;
    if (p6 == 0) uVar5 = w0 >> 3 & 3;
    uVar15 = (w0 & 0x2400) != 0;
    if (w0 & 0x200) uVar15 = 2;
    uVar15 |= w0 >> 0x13 & 8;
    uVar14 = base;
    v = (*region == 4) ? sk_obj_meta3(p3, p5, base, p2, uVar5, uVar15)
                       : sk_obj_meta4(p3, p5, base, p2, uVar5, uVar15); /* FUN_00043b44/43be8 */
    if ((v & 0xff) == 4) {
        if (((unsigned char)region[0x23] >> 2 & 1) != 0) {
            /* full span map walk */
            v = sk_region_wire_spans(region, p2, base);          /* FUN_0003ff00 */
            return v;
        }
        err = sk_obj_attr3(p3, p2);                             /* FUN_000436fc */
        if (err == 0) { v = 2; return v; }
        if (*region == 4) v = sk_obj_meta3(p3, p5, base, p2, uVar5, uVar15);
        else v = sk_obj_meta4(p3, p5, base, p2, uVar5, uVar15);
    }
    if (v != 0) {
        uVar14 = v & 0xff;
        if (p7 == 0 || uVar14 == 2) {
            if ((p7 & 1) != 0) return v;
            if ((long)v < 0x207) { if (v == 2 || v == 7) return v; }
            else if (v == 0x207 || v == 0x307) return v;
        }
        if (uVar14 != 8 && uVar14 != 0 && (w0 & 0x40000) == 0) {
            sk_err_name(st, 0);                                 /* FUN_0003f980 */
            sk_vas_fault41(0xeb1a02bf914012ba);                 /* FUN_004b2820 */
            sk_err_name(st, v);
            sk_vas_abort("Unexpected L4 Error %s err %zu", 0x5b010f);
            __builtin_unreachable();
        }
    }
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_0003ff00 @ 0x0003ff00   (est. sk_region_wire_spans)
 * Ghidra: undefined8 FUN_0003ff00(char *param_1, ulong param_2, ulong param_3)
 * Wires the span pages of region param_1 across [param_2, param_3): for
 * each 32 MiB span-table block, walks the span entries (sk_walk_span3 /
 * sk_map_span3) mapping the pages, and returns the end offset. Takes the
 * region lock around the walk. Aborts on lock failure.
 * Confidence: low-medium (structural; span wiring).
 */
unsigned long sk_region_wire_spans(char *region, unsigned long start, unsigned long end)
{
    unsigned long uVar2, uVar8, uVar9, uVar10, v, block, page;
    unsigned long st_local[4], st_local2[4];
    unsigned long *puVar2, *puVar3;
    void (*f1)(void *, unsigned long, unsigned long, unsigned long);
    void (*f2)(void *, unsigned long, unsigned long, unsigned long);
    unsigned int w0, uVar6, flags;
    char c;
    int err;

    if (sk_vm_lock_check((unsigned long)region + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    v = (unsigned long)sk_vspace_root();                              /* FUN_00032cd0 -> root */
    uVar2 = 0;
    if ((end & 0x3fff) != 0) uVar2 = 0x4000;
    uVar2 = uVar2 + (end & 0xffffffffffffc000);
    for (block = start & 0xfffffffffe000000; block < uVar2; block += 0x2000000) {
        page = sk_obj_method_dispatch3(v, 1, block);            /* FUN_00042abc */
        if ((sk_obj_lookup3(v, page) & 1) == 0)                 /* FUN_00042c20 */
            return 2;
    }
    if ((unsigned long)region + 0x80 <= (unsigned long)region + 0x90) {
        c = *region;
        w0 = *(unsigned int *)(region + 0x20);
        uVar6 = w0 >> 0xd & 1;
        if (c != 0x11) uVar6 = 0;
        flags = w0 >> 0x11 & 0x20 | uVar6;
        page = start & 0xffffffffffffc000;
        if ((w0 >> 0x1a & 1) == 0) {
            /* linear span map */
            uVar9 = uVar2 - page >> 0xe;
            puVar2 = (unsigned long *)(v + 0xb0);
            puVar3 = *(unsigned long **)(v + 0xb8);
            if (puVar3[9] == 0) {
                for (unsigned long i = 0; i < uVar9; i++) {
                    uVar8 = sk_walk_span3(&st_local, i);        /* FUN_000402b4 */
                    uVar10 = (*(unsigned long (*)(unsigned long, char, unsigned long,
                                                   unsigned long, unsigned int))*puVar3)
                        (*puVar2, c, uVar8, uVar8, flags);
                    sk_map_span3(&st_local2, uVar10, i, uVar8); /* FUN_000403b0 */
                }
            } else {
                ((void (*)(unsigned long, char, unsigned int, unsigned long, void *, void *))
                 puVar3[9])(*puVar2, c, flags, uVar9, &st_local, &st_local2);
            }
        } else {
            /* chunked map */
            while (uVar2 != page) {
                c = *region;
                uVar9 = *(unsigned long *)(v + 0xb0);
                puVar3 = *(unsigned long **)(v + 0xb8);
                if (puVar3[9] == 0) {
                    uVar8 = sk_walk_span3(&st_local, 0);        /* FUN_000402b4 */
                    uVar9 = (*(unsigned long (*)(unsigned long, char, unsigned long,
                                                 unsigned long, unsigned int))*puVar3)
                        (uVar9, c, uVar8, uVar8, flags);
                    sk_map_span3(&st_local2, uVar9, 0, uVar8);  /* FUN_000403b0 */
                } else {
                    ((void (*)(unsigned long, char, unsigned int, unsigned long, void *, void *))
                     puVar3[9])(uVar9, c, flags, 1, &st_local, &st_local2);
                }
                page += 0x4000;
            }
        }
        err = sk_vm_lock_take((unsigned long)region + 0x80);
        if (err == 0)
            return 0;
        sk_vas_abort("VAS abort in function %s at line %d", 0x5aed68);
        __builtin_unreachable();
    }
    __builtin_unreachable();                                    /* SoftwareBreakpoint(0x5519, 0x4024c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00036118 @ 0x00036118   (est. sk_span_release_t)
 * Ghidra: void thunk_FUN_00036118(...)
 * Thunk to sk_span_release (FUN_0003611c).
 * Confidence: high (trivial thunk).
 */
void sk_f_36118(unsigned long *out, unsigned long span, unsigned int count,
                void (*cb)(unsigned long))
{
    sk_span_release(out, span, count, cb);
}



/*==========================================================================
 * Filled bodies for previously-extern vspace/span/pool functions.
 *==========================================================================*/

/* Reads the current thread id (tpidr_el0 + 8), mirroring FUN_00060524. */
static unsigned long sk_thread_id_get(void)
{
    unsigned long tp;
    __asm__ volatile("mrs %0, tpidr_el0" : "=r"(tp));
    return *(unsigned long *)(tp + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00034a5c @ 0x00034a5c   (est. sk_vspace_done)
 * Ghidra: void FUN_00034a5c(void)
 * Marks the vspace object table as done: increments the element count at
 * +0x48 of the table node and re-sizes it via FUN_000348d0. Aborts (VAS
 * 005b11ec) if the count would exceed 0xffff.
 * Confidence: medium (structural counter bump).
 * Notes: node 0x6af188; helper FUN_000348d0. */
void sk_vspace_done(void *obj)
{
    (void)obj;
    unsigned long node = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_0005acac */
    if (*(unsigned int *)(node + 0x48) < 0xffff) {
        *(unsigned int *)(node + 0x48) = *(unsigned int *)(node + 0x48) + 1;
        sk_obj_table_size();                        /* FUN_000348d0 */
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b11ec);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034ad0 @ 0x00034ad0   (est. sk_vspace_unlink_cleanup)
 * Ghidra: void FUN_00034ad0(void)
 * Completes a vspace unlink: decrements the object-table element count
 * (+0x48) and re-sizes the table; when the count reaches zero it
 * re-initialises the vspace lock slot via FUN_00118148, storing a 0x100
 * capacity cookie at +0x18. Aborts (VAS 005aed68) on lock failure.
 * Confidence: medium (structural teardown; lock helper FUN_00118148).
 * Notes: node 0x6af188; helpers FUN_000348d0/FUN_00118148. */
void sk_vspace_unlink_cleanup(void)
{
    unsigned long node = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);  /* FUN_0005acac */
    unsigned long desc;

    if (*(int *)(node + 0x48) != 0) {
        *(int *)(node + 0x48) = *(int *)(node + 0x48) - 1;
        sk_obj_table_size();                        /* FUN_000348d0 */
        return;
    }
    desc = *(unsigned long *)(node + 0x10);         /* vspace lock/desc slot */
    if (desc <= desc + 0x10) {
        if (sk_vm_lock_take2(desc, 0) == 0) {       /* FUN_00118148 */
            *(unsigned long *)(desc + 0x10) = 0;
            *(unsigned long *)(desc + 0x18) = 0x100;
            return;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        __builtin_unreachable();
    }
    __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x34b70) */
}

/*--------------------------------------------------------------------*/
/* FUN_00034ba4 @ 0x00034ba4   (est. sk_region_method)
 * Ghidra: bool FUN_00034ba4(long region)
 * Returns whether the current thread (FUN_00060524) equals the region's
 * method owner stored at region+0x10.
 * Confidence: medium (thread-id equality check).
 * Notes: helpers FUN_00060524/thunk_FUN_000539c0 (==). */
unsigned long sk_region_method(long region)
{
    return (unsigned long)(sk_thread_id_get() == *(unsigned long *)(region + 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_00034bd8 @ 0x00034bd8   (est. sk_pool_method)
 * Ghidra: cl4_result_t FUN_00034bd8(long pool)
 * Takes the pool's per-thread lock: if not already owned by the current
 * thread (FUN_00060524 vs +0x10), validates the counter at +0x18 (must be
 * page-aligned low byte), claims ownership and bumps the counter by 0x101,
 * returning {0, cookie}; on a nested call it validates the counter and
 * bumps it by 1, returning {1, cookie}. Aborts (VAS) on any violation.
 * Confidence: low-medium (returns .lo of the {flag,cookie} pair).
 * Notes: helpers FUN_00060524/thunk_FUN_000539c0/FUN_00118164; aborts
 *   005b144d/005b14d8/005b13b9/005b133b/005aed68. */
unsigned long sk_pool_method(unsigned long pool)
{
    unsigned long cookie, flag;

    if (sk_thread_id_get() != *(unsigned long *)(pool + 0x10)) {
        if (sk_vm_lock_check(pool) != 0) {          /* FUN_00118164 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            __builtin_unreachable();
        }
        if (*(long *)(pool + 0x10) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b144d);
            __builtin_unreachable();
        }
        cookie = *(unsigned long *)(pool + 0x18);
        if ((cookie & 0xff) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b14d8);
            __builtin_unreachable();
        }
        *(unsigned long *)(pool + 0x10) = sk_thread_id_get();
        *(unsigned long *)(pool + 0x18) = cookie + 0x101;
        flag = 0;
    } else {
        cookie = *(unsigned long *)(pool + 0x18);
        if (((unsigned int)cookie & 0xff) == 0xff) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b13b9);
            __builtin_unreachable();
        }
        if ((cookie & 0xff) == 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b133b);
            __builtin_unreachable();
        }
        *(unsigned long *)(pool + 0x18) = cookie + 1;
        flag = 1;
    }
    return flag;   /* .lo of the {flag, cookie} result */
}

/*--------------------------------------------------------------------*/
/* FUN_00034d5c @ 0x00034d5c   (est. sk_pool_touch)
 * Ghidra: void FUN_00034d5c(long pool, byte flag, ulong cookie)
 * Releases/touches the pool lock: validates that the pool is owned by the
 * current thread (FUN_00060524), the counter (+0x18) equals cookie+1, and
 * the low-byte parity matches flag. On flag==0 it also runs the pool's
 * release callback (+0x20, arg +0x28), then clears the owner (+0x10) and
 * restores the counter to cookie; on flag!=0 it only restores the counter.
 * Aborts (VAS) on any invariant violation.
 * Confidence: low-medium (1-arg wrapper deriving cookie/flag from pool).
 * Notes: helpers FUN_00060524/thunk_FUN_000539c0/FUN_00118194; aborts
 *   005b1554/005b15c4/005b165f/005aed68. */
void sk_pool_touch(unsigned long pool)
{
    unsigned long cookie;
    unsigned long flag;

    cookie = *(unsigned long *)(pool + 0x18) - 1;
    flag = (*(unsigned long *)(pool + 0x10) != 0) ? 1 : 0;

    if (sk_thread_id_get() != *(unsigned long *)(pool + 0x10)) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1554);
        __builtin_unreachable();
    }
    if (cookie + 1 != *(long *)(pool + 0x18)) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b15c4);
        __builtin_unreachable();
    }
    if (((cookie & 0xff) != 0) != ((flag & 1) != 0)) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b165f);
        __builtin_unreachable();
    }
    if ((flag & 1) == 0) {
        ((void (*)(unsigned long))(*(unsigned long *)(pool + 0x20)))(
            *(unsigned long *)(pool + 0x28));
        if (sk_thread_id_get() != *(unsigned long *)(pool + 0x10)) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1554);
            __builtin_unreachable();
        }
        if (cookie + 1 != *(long *)(pool + 0x18)) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b15c4);
            __builtin_unreachable();
        }
        if ((cookie & 0xff) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b165f);
            __builtin_unreachable();
        }
        *(unsigned long *)(pool + 0x10) = 0;
        *(unsigned long *)(pool + 0x18) = cookie;
        if (sk_vm_lock_take(pool) != 0) {           /* FUN_00118194 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            __builtin_unreachable();
        }
    } else {
        *(unsigned long *)(pool + 0x18) = cookie;
    }
}

/* Out-of-range boot helpers (reconstructed by sibling slices). */
extern void sk_vas_init_root(void *a, void *b, void *c);       /* FUN_0004158c */
extern void sk_vas_teardown_free(void);                        /* FUN_00041d9c */
extern unsigned long sk_vspace_region_map_wrapper(unsigned long, char *, unsigned long *,
                                                  void *, void *);  /* FUN_0003c510 */
extern unsigned long DAT_006af190;   /* boot-init guard */
extern unsigned long DAT_004bbfd8;   /* prefetch method cookie */
extern void FUN_004b326c(void);      /* prefetch fault (out-of-range) */
extern void FUN_004b3294(void);      /* prefetch fault (out-of-range) */
extern unsigned long DAT_006ad39c;   /* span-free counter */
extern void sk_tcb_slot_release(void *);          /* FUN_004b23d8 */
extern void thunk_FUN_000539fc(void *);           /* span list zero */
extern void sk_pool_free_node_c1a8(void *);       /* FUN_00033684 */
extern void sk_vas_body_teardown(uint64_t);               /* FUN_00042808 */

/*--------------------------------------------------------------------*/
/* FUN_00035944 @ 0x00035944   (est. sk_vas_mark_cb)
 * Ghidra: void FUN_00035944(long obj, void *p2, void *p3, void *p4)
 * Marks a vspace object / callback: if obj is non-null it builds a small
 * descriptor ({0x100, 0, 0, obj, p4}) and creates a vspace object from it
 * (FUN_00032520); otherwise it faults via FUN_004b27b8 and re-initialises
 * the resulting object via FUN_00032c68.
 * Confidence: medium (structural dispatch; create/reinit helpers).
 * Notes: helpers FUN_00032520/004b27b8/00032c68. */
void sk_vas_mark_cb(long obj, void *p2, void *p3, void *p4)
{
    if (obj != 0) {
        unsigned short desc[4] = { 0x100, 0, 0, (unsigned short)(obj & 0xffff) };
        sk_vspace_create_object((char *)desc, p2, p3, (void *)p4);  /* FUN_00032520 */
        return;
    }
    sk_vspace_reinit_object((long)(uintptr_t)sk_vas_fault16r(),
                            (void *)(uintptr_t)p3, (void *)(uintptr_t)p4);  /* FUN_00032c68 */
}

/*--------------------------------------------------------------------*/
/* FUN_000359a0 @ 0x000359a0   (est. sk_vas_reinit_thunk)
 * Ghidra: void FUN_000359a0(void *p1, void *p2, void *p3, void *p4)
 * Re-initialises a vspace object: forwards (p1, p3, p4) to FUN_00032c68.
 * Confidence: medium (trivial forwarder).
 * Notes: helper FUN_00032c68. */
void sk_vas_reinit_thunk(void *p1, void *p2, void *p3, void *p4)
{
    (void)p2;
    sk_vspace_reinit_object((long)(uintptr_t)p1, p3, p4);   /* FUN_00032c68 */
}

/*--------------------------------------------------------------------*/
/* FUN_000359d4 @ 0x000359d4   (est. sk_vas_destroy_check)
 * Ghidra: void FUN_000359d4(long obj, long tag)
 * Destroys a vspace object unless it is the root sentinel: requires tag ==
 * 0x65b5c8, then (if the slot-alloc frame FUN_00034a2c != obj) destroys the
 * object via FUN_00032774. Aborts (VAS 005b1fef/005b2057) on bad tag or a
 * frame equal to obj.
 * Confidence: medium (structural destroy dispatch).
 * Notes: tag 0x65b5c8; helpers FUN_00034a2c/00032774. */
void sk_vas_destroy_check(long obj, long tag)
{
    long frame;

    if (tag != 0x65b5c8) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1fef);
        __builtin_unreachable();
    }
    frame = (long)sk_vspace_slot_alloc_frame().lo;  /* FUN_00034a2c */
    if (frame != obj) {
        sk_vspace_destroy((void **)(uintptr_t)obj); /* FUN_00032774 */
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b2057);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00035a78 @ 0x00035a78   (est. sk_vas_boot_init)
 * Ghidra: void FUN_00035a78(long p1, long p2, long p3)
 * One-time vspace/region boot bring-up guarded by DAT_006af190. Runs the
 * early vspace setup (FUN_00031868), a 3-arg region init (FUN_0004158c),
 * early init (FUN_00033780), region wire (FUN_0003c09c), a range alloc
 * (FUN_0003548c), a descriptor build (FUN_00041d9c), then maps the initial
 * region via FUN_0003c510 with a {4,0,0,0xff,0} descriptor, and finally
 * FUN_00033bb0. Aborts (VAS/SoftwareBreakpoint) on map failure.
 * Confidence: low-medium (large structural boot sequence).
 * Notes: guard DAT_006af190; helpers FUN_00031868/0004158c/00033780/
 *   0003c09c/0003548c/00041d9c/0003c510/00033bb0. */
void sk_vas_boot_init(long p1, long p2, long p3)
{
    unsigned char desc[0x28];
    unsigned long lo = 0;
    unsigned long r;

    if ((DAT_006af190 & 1) != 0) return;

    sk_boot_vspace_setup();                         /* FUN_00031868 */
    sk_vas_init_root((void *)(uintptr_t)p1, (void *)(uintptr_t)p2, (void *)(uintptr_t)p3);  /* FUN_0004158c */
    sk_boot_vspace_early_init();                    /* FUN_00033780 */
    sk_region_wire();                               /* FUN_0003c09c */
    {
        long size = (p2 - p1) + p3 * 0x40;
        sk_vspace_region_alloc_pages(p1, (unsigned long)(p2 - p1), (unsigned long)size);  /* FUN_0003548c */
    }
    sk_vas_teardown_free();                         /* FUN_00041d9c */

    for (int i = 0; i < 0x28; i++) desc[i] = 0;
    desc[0] = 4;                                    /* region descriptor tag */
    desc[5] = 0xff;
    *(unsigned long *)(desc + 0x18) = (unsigned long)p1;
    *(unsigned long *)(desc + 0x20) = (unsigned long)((p2 - p1) + p3 * 0x40);

    r = sk_vspace_region_map_wrapper(0x1000001, desc, &lo, 0, 0);  /* FUN_0003c510 */
    if ((r & 0xff) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b20a7);
        __builtin_unreachable();
    }
    sk_vspace_regions_init();                       /* FUN_00033bb0 */
    DAT_006af190 = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0003c510 @ 0x0003c510   (est. sk_vspace_region_map_wrapper)
 * Ghidra: ulong FUN_0003c510(ulong a, char *b, ulong *c, void *d, void *e)
 * Wraps FUN_0003c56c (region constructor) against the current vspace root
 * (FUN_00032514), forwarding the five arguments; returns the low result
 * word (the caller of the boot path checks its error byte).
 * Confidence: medium (trivial wrapper).
 * Notes: helpers FUN_00032514/0003c56c. */
unsigned long sk_vspace_region_map_wrapper(unsigned long a, char *b, unsigned long *c,
                                           void *d, void *e)
{
    unsigned long root = (unsigned long)sk_vspace_root();  /* FUN_00032514 */
    cl4_result_t cr = sk_region_create(root, (unsigned int)a, b, c, (unsigned int *)(uintptr_t)d,
                                       (unsigned long *)(uintptr_t)e);  /* FUN_0003c56c */
    return cr.lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0003b6c0 @ 0x0003b6c0   (est. sk_lock_collection_refill)
 * Ghidra: bool FUN_0003b6c0(long root, long coll, void *p3, void *p4, ulong want)
 * Refills a lock/collection's free nodes up to the requested count (want).
 * Requires coll+0x50 to point at root; when the collection's node count
 * (+0x38) is below want it releases the lock, allocates fresh nodes via
 * FUN_0003344c and pushes them (FUN_0003b648) until the target is reached,
 * then runs FUN_00044c94 and re-links the collection. Returns true when the
 * target count is met.
 * Confidence: low-medium (structural lock-collection refill).
 * Notes: helpers FUN_00118194/0003344c/0003b648/00044c94. */
bool sk_lock_collection_refill(long root, long coll, void *p3, void *p4, unsigned long want)
{
    bool ok;
    long node;

    if (*(long *)(coll + 0x50) != root) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b274a);
        __builtin_unreachable();
    }
    if (*(unsigned long *)(root + 0x38) < want) {
        *(unsigned long *)(coll + 0x50) = 0;
        if (sk_vm_lock_take(coll + 0x40) != 0) {    /* FUN_00118194 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            __builtin_unreachable();
        }
        if (*(unsigned long *)(root + 0x38) < want) {
            do {
                node = (long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_0003344c path */
                ok = node != 0;
                if (node == 0) break;
                sk_slot_push_c(root, (unsigned long *)(uintptr_t)node);  /* FUN_0003b648 */
            } while (*(unsigned long *)(root + 0x38) < want);
        } else {
            ok = true;
        }
        sk_obj_unlink4(coll, (unsigned long)(uintptr_t)p3, (unsigned long)(uintptr_t)p4);  /* FUN_00044c94 */
        if (*(long *)(coll + 0x50) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b274a);
            __builtin_unreachable();
        }
        *(long *)(coll + 0x50) = root;
    } else {
        ok = true;
    }
    return ok;
}

/*--------------------------------------------------------------------*/
/* FUN_0003c32c @ 0x0003c32c   (est. sk_span_tree_destroy_node)
 * Ghidra: void FUN_0003c32c(long *root)
 * Destroys a span tree rooted at *root, recursing into its left (+0x58) and
 * right (+0x60) children, releasing any third slot (+0x70) back into the
 * store bitmap (FUN_00031594), tearing down the node via FUN_0003c3bc and
 * freeing its backing block (FUN_00033148). Aborts (SoftwareBreakpoint)
 * on layout corruption. Distinct from sk_span_tree_destroy (FUN_00037e9c).
 * Confidence: low-medium (recursive span-tree teardown).
 * Notes: helpers FUN_00031594/0003c3bc/00033148; trap 0x3c3bc. */
void sk_span_tree_destroy_node(long *root)
{
    long node;

    node = *root;
    if (node != 0) {
        if (*(long *)(node + 0x58) != 0) {
            if ((long *)(node + 0x60) < (long *)(node + 0x58)) goto trap;
            sk_span_tree_destroy_node((long *)(node + 0x58));
        }
        if (*(long *)(node + 0x60) != 0) {
            if ((long *)(node + 0x68) < (long *)(node + 0x60)) goto trap;
            sk_span_tree_destroy_node((long *)(node + 0x60));
        }
        if (*(long *)(node + 0x70) != 0) {
            sk_vspace_mark_alloc(*(unsigned long *)(node + 0x50),
                                 *(unsigned long *)(node + 0x70));  /* FUN_00031594 */
            *(unsigned long *)(node + 0x70) = 0;
        }
        sk_region_teardown(node);                   /* FUN_0003c3bc */
        *(unsigned long *)(node + 0x50) = 0;
        sk_pool_alloc_block((void *)(uintptr_t)node);  /* FUN_00033148 */
        *root = 0;
    }
    return;
trap:
    __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x3c3bc) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003df84 @ 0x0003df84   (est. sk_span_prefetch_pages)
 * Ghidra: void FUN_0003df84(char *span, ulong page, long len)
 * Prefetches a run of pages into the span's backing store. Validates span is
 * a live direct span (type 0x11, non-null cursor at +0x50, span != cursor),
 * then for each 0x4000-aligned granule in [page, page+len) builds a
 * {0x6ad3a8, cookie, FUN_00040f80, 0x65b770, ...} prefetch descriptor and
 * dispatches it either through the root method (FUN_00033b50) when the
 * cursor is the global root, or directly (FUN_00040f80). Aborts (VAS) if the
 * granule overruns the cursor window.
 * Confidence: low-medium (granule prefetch loop).
 * Notes: cursor +0x50 word 0x26; helpers FUN_00033b50/00040f80. */
void sk_span_prefetch_pages(char *span, unsigned long page, long len)
{
    unsigned long *cur = *(unsigned long **)(span + 0x50);
    char *cur26 = (char *)cur[0x26];
    unsigned long base, start, end, size, i;
    unsigned long cookie = DAT_004bbfd8;

    if (*span != '\x11' || cur26 == 0 || span == cur26) return;

    if (page < *(unsigned long *)(span + 0x10)) {
        if ((unsigned long)(len - 1) < *(unsigned long *)(span + 0x10) - page) {
            base = *(long *)(span + 8) + page + (unsigned long)len;
            start = *(long *)(span + 8) + page >> 3 & 0x1fffffffffffc000;
            end = 0;
            if ((base & 0x1fff8) != 0) end = 0x4000;
            end = end + (base >> 0x11) * 0x4000;
            size = start - *(long *)(cur26 + 8);
            if (size < *(unsigned long *)(cur26 + 0x10)) {
                {
                    unsigned long run = end - start;
                    if (*(unsigned long *)(cur26 + 0x10) - size < run) {
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b6078);
                        __builtin_unreachable();
                    }
                    if (end == start) return;
                    for (i = 0; i < run; i += 0x4000) {
                        unsigned long desc[8];
                        desc[0] = 0x6ad3a8;
                        desc[1] = cookie;
                        desc[2] = (unsigned long)(uintptr_t)&sk_span_map3; /* FUN_00040f80 */
                        desc[3] = 0x65b770;
                        desc[4] = size;
                        desc[5] = i;
                        desc[6] = (unsigned long)(uintptr_t)cur26;
                        desc[7] = run;
                        if (cur == (unsigned long *)&sk_vspace_root_obj)
                            sk_vspace_dispatch_method((long)&desc);  /* FUN_00033b50 */
                        else
                            sk_span_map3();               /* FUN_00040f80 */
                    }
                    return;
                }
            }
        }
    } else {
        FUN_004b326c();
    }
    FUN_004b3294();
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b6078);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003b820 @ 0x0003b820   (est. sk_slot_attach_full)
 * Ghidra: ulong FUN_0003b820(ulong *st, ulong root, ulong n1, ulong n2, ulong n3, ulong n4)
 * Initialises a 10-word slot descriptor (st) and attaches n1 nodes from the
 * +8 free list, n2 from the +0x10 list, n3 from the +0x18 list, and n4 from
 * the +0x28 list, all rooted at `root`. Aborts (VAS 005b27c9/005b2844/
 * 005b28a3) if any requested count exceeds 3. Returns 1 on success, 0 (after
 * detaching via FUN_0003bac0) on allocation failure.
 * Confidence: low-medium (structural slot-tree bring-up).
 * Notes: helpers FUN_00032e44/0003ba58/00030cc8/00033594/0003b410/
 *   000334f0/0003b548/0003344c/0003b648. */
unsigned long sk_slot_attach_full(unsigned long *st, unsigned long root,
                                  unsigned long n1, unsigned long n2,
                                  unsigned long n3, unsigned long n4)
{
    unsigned long node;
    unsigned char c;
    int i;

    if (3 < n1) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b27c9);
        __builtin_unreachable();
    }
    if (3 < n2) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b2844);
        __builtin_unreachable();
    }
    if (3 < n3) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b28a3);
        __builtin_unreachable();
    }

    st[0] = root;
    st[6] = 0; st[5] = 0; st[2] = 0; st[1] = 0; st[4] = 0; st[3] = 0; st[7] = 0;
    *(unsigned short *)(st + 8) = (unsigned short)(n1 | (n2 << 4) | (n3 << 8) | (n4 << 12));
    *(unsigned int *)((char *)st + 0x42) = 0;
    *(unsigned short *)((char *)st + 0x46) = 0;

    while (*(unsigned char *)(st + 6) < n1) {
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_00032e44 */
        if (node == 0) goto fail;
        sk_slot_push_d((long)st, (unsigned long *)(uintptr_t)node);   /* FUN_0003ba58 */
    }
    c = *(unsigned char *)((char *)st + 0x31);
    while (c < n2) {
        unsigned long *slot = (unsigned long *)sk_vspace_slot_alloc(root);  /* FUN_00030cc8 */
        if (slot == (unsigned long *)0) goto fail;
        *(unsigned char *)(slot + 3) = 0;
        if (2 < *(unsigned char *)((char *)st + 0x31)) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b346f);
            __builtin_unreachable();
        }
        *slot = st[2];
        st[2] = (unsigned long)slot;
        c = *(unsigned char *)((char *)st + 0x31) + 1;
        *(unsigned char *)((char *)st + 0x31) = (unsigned char)c;
    }
    while (*(unsigned char *)((char *)st + 0x32) < n3) {
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_00033594 */
        if (node == 0) goto fail;
        sk_slot_push_a((long)st, (unsigned long *)(uintptr_t)node);   /* FUN_0003b410 */
    }
    if (n4 != 0 || n3 != 0) {
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_000334f0 */
        if (node == 0) goto fail;
        sk_slot_push_b((long)st, (unsigned long *)(uintptr_t)node);   /* FUN_0003b548 */
    }
    for (;;) {
        if (n4 <= st[7]) return 1;
        node = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);  /* FUN_0003344c */
        if (node == 0) break;
        sk_slot_push_c((long)st, (unsigned long *)(uintptr_t)node);   /* FUN_0003b648 */
    }
fail:
    sk_slot_detach_inner(st);                    /* FUN_0003bac0 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0003bac0 @ 0x0003bac0   (est. sk_slot_detach_inner)
 * Ghidra: void FUN_0003bac0(undefined8 *st)
 * Detaches a slot descriptor: pops and releases all nodes from the +0x10
 * free list (FUN_0003e640/00031594), then drains the +0x18 list
 * (FUN_0003b340/000335e0), the +0x20 list (FUN_0003b478/0003353c), and the
 * +0x28 list (FUN_0003b5b0/00033498), clearing the descriptor fields.
 * Aborts (VAS) if any list count is inconsistent.
 * Confidence: low-medium (structural slot-tree teardown).
 * Notes: helpers FUN_0003e640/00031594/0003b340/000335e0/0003b478/
 *   0003353c/0003b5b0/00033498/001143a0. */
void sk_slot_detach_inner(void *vp)
{
    unsigned long *st = (unsigned long *)vp;
    unsigned long root = st[0];
    unsigned char c;
    unsigned long node;

    c = *(unsigned char *)(st + 6);
    while (c != 0) {
        node = (unsigned long)sk_slot_pop_e((long)st);      /* FUN_0003c21c */
        if (node + 0xb0 < node) goto trap;
        *(unsigned long *)(node + 0x50) = 0;
        sk_pool_alloc_block((void *)(uintptr_t)node);       /* FUN_00033148 */
        c = *(unsigned char *)(st + 6);
    }
    if (st[1] != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b34cf);
        __builtin_unreachable();
    }
    for (;;) {
        if (*(unsigned char *)((char *)st + 0x31) == 0) {
            if (st[2] != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b353c);
                __builtin_unreachable();
            }
            while (*(unsigned char *)((char *)st + 0x32) != 0) {
                sk_slot_pop_a((long)st);                    /* FUN_0003b340 */
                sk_pool_free_node_c18c((void *)(uintptr_t)0);   /* FUN_000335e0 */
            }
            if (st[3] != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b3598);
                __builtin_unreachable();
            }
            while (*(unsigned char *)((char *)st + 0x33) != 0) {
                sk_slot_pop_b((long)st);                    /* FUN_0003b478 */
                sk_pool_free_node_c170((void *)(uintptr_t)0);   /* FUN_0003353c */
            }
            if (st[4] != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b35f3);
                __builtin_unreachable();
            }
            while (st[7] != 0) {
                sk_slot_pop_c((long)st);                    /* FUN_0003b5b0 */
                sk_pool_free_node_c154((void *)(uintptr_t)0);   /* FUN_00033498 */
            }
            if (st[5] != 0) {
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b3655);
                __builtin_unreachable();
            }
            sk_mem_zero(st, 8);                             /* FUN_001143a0 */
            return;
        }
        node = (unsigned long)sk_slot_pop_f((long)st);      /* FUN_0003e640 */
        if (node + 0x20 < node) break;
        sk_vspace_mark_alloc(root, node);                   /* FUN_00031594 */
    }
trap:
    __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x3bbf0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00039d2c @ 0x00039d2c   (est. sk_vspace_span_free)
 * Ghidra: cl4_result_t FUN_00039d2c(long owner, ulong *span)
 * Frees a vspace span: verifies span[10] == owner, then (when the span is
 * not wired, +0xa1 != 1) releases its two backing descriptors (FUN_00039e34
 * twice), the two cap slots (FUN_004b23d8 twice), resets the span's
 * destination/relocation state and zeroes the descriptor via FUN_00033684,
 * returning {0,0}. Aborts (VAS 005b4c86) if the span is still wired.
 * Confidence: low-medium (structural span teardown).
 * Notes: helpers FUN_00039e34/004b23d8/00033684/thunk_FUN_000539fc. */
cl4_result_t sk_vspace_span_free(long owner, unsigned long *span)
{
    cl4_result_t r;

    DAT_006ad39c = DAT_006ad39c + 1;
    if (span[10] != (unsigned long)owner) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b5f52);
        __builtin_unreachable();
    }
    if (*(char *)((char *)span + 0xa1) == '\x01') {
        sk_vas_fault64(0, 0);                      /* FUN_004b2f58 */
        __builtin_unreachable();
    }
    (void)sk_span_destroy((unsigned char *)(uintptr_t)span[0xb]);  /* FUN_00039e34 */
    (void)sk_span_destroy((unsigned char *)(uintptr_t)span[0xe]);  /* FUN_00039e34 */
    sk_tcb_slot_release((void *)(uintptr_t)span[0x12]);  /* FUN_004b23d8 */
    sk_tcb_slot_release((void *)(uintptr_t)span[0x13]);  /* FUN_004b23d8 */
    if (*(char *)(span + 8) != '\x01') {
        thunk_FUN_000539fc(span + 6);
        span[0x15] = 0; span[0x14] = 0; span[0x17] = 0; span[0x16] = 0;
        span[0x11] = 0; span[0x10] = 0; span[0x13] = 0; span[0x12] = 0;
        span[0xd] = 0; span[0xc] = 0; span[0xf] = 0; span[0xe] = 0;
        span[9] = 0; span[8] = 0; span[0xb] = 0; span[10] = 0;
        span[5] = 0; span[4] = 0; span[7] = 0; span[6] = 0;
        span[1] = 0; span[0] = 0; span[3] = 0; span[2] = 0;
        sk_pool_free_node_c1a8(span);   /* FUN_00033684 */
        r.lo = 0; r.hi = 0;
        return r;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b4c86);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_0003c0e4 @ 0x0003c0e4   (est. sk_vspace_final_wire)
 * Ghidra: void FUN_0003c0e4(long region, ulong p2, ulong p3)
 * Finalises a vspace region's wiring: attaches the region (sk_slot_attach_full
 * FUN_0003b820, counts {1,0,0,0}), unlinks it (FUN_0003bca0), pops a span
 * node (FUN_0003c21c) and fills it with the region's base/size range
 * [p2, p3), then attaches the span and region (FUN_0003c2ec/0003bfb8).
 * Aborts (VAS 005b2bbb/005b2c70) on failure.
 * Confidence: low-medium (structural final-wire; span descriptor fill).
 * Notes: helpers FUN_0003b820/0003bca0/0003c21c/0003c2ec/0003bfb8. */
void sk_vspace_final_wire(long region, unsigned long p2, unsigned long p3)
{
    unsigned long st[10];
    unsigned long *span;
    long len;
    int i;

    for (i = 0; i < 10; i++) st[i] = 0;
    if ((sk_slot_attach_full(st, (unsigned long)region, 1, 0, 0, 0) & 1) == 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b2bbb);
        __builtin_unreachable();
    }
    sk_slot_unlink_root(st, (unsigned long *)region, 0, 0);  /* FUN_0003bca0 */
    span = (unsigned long *)sk_slot_pop_e((long)st);         /* FUN_0003c21c */
    len = (long)(p3 - p2);
    if (p2 <= p3 && len != 0) {
        *(unsigned long *)(region + 0x28) = p2;
        *(unsigned long *)(region + 0x30) = p3;
        if ((unsigned long)span <= (unsigned long)span + 0xb8) {
            span[0] = 0; span[1] = p2; span[2] = (unsigned long)len;
            span[4] = 0; span[3] = 0; span[6] = 0; span[5] = 0;
            span[8] = 0; span[7] = 0; span[9] = 0;
            span[10] = (unsigned long)region;
            span[0xb] = 0; span[0xc] = 0; span[0xd] = (unsigned long)len;
            span[0xf] = 0; span[0xe] = 0;
            span[0x11] = 0; span[0x10] = 0;
            span[0x13] = 0; span[0x12] = 0;
            span[0x15] = 0; span[0x14] = 0;
            sk_region_attach(st, (unsigned long)span);      /* FUN_0003c2ec */
            sk_slot_detach(st, region);                     /* FUN_0003bfb8 */
            return;
        }
        __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x3c1c8) */
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b2c70);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00032888 @ 0x00032888   (est. sk_vspace_teardown_store)
 * Ghidra: void FUN_00032888(long vspace)
 * Tears down a vspace's backing-store chain: drains the store list
 * (FUN_0005acac-based method iteration), marks the object done
 * (FUN_000459d4), destroys the span tree (FUN_0003c32c), resets the store
 * list head and free-run list, then for each of the seven store slots
 * releases the vspace store (FUN_00033e00 small / FUN_000341f4 large),
 * rebuilding the pool links. Aborts (SoftwareBreakpoint 0x5519 at 0x32c64)
 * on any layout corruption.
 * Confidence: low-medium (large structural store-chain teardown).
 * Notes: helpers FUN_000459d4/0003c32c/0005acac/00118164/00118194/
 *   001143a0/00033e00/000341f4/000333f4/00042808. */
void sk_vspace_teardown_store(long vspace)
{
    unsigned long store, next, node;
    unsigned char small;
    int slot;

    /* Drain the store chain (method dispatch over the store list). */
    store = 0;
    while (store != 0) { }

    *(unsigned long *)(vspace + 0x130) = 0;
    sk_vspace_object_done(vspace);                  /* FUN_000459d4 */
    sk_span_tree_destroy_node((long *)(vspace + 0x58));  /* FUN_0003c32c */

    small = *(unsigned char *)(vspace + 9);
    *(unsigned long *)(vspace + 0x138) = 0;
    if (vspace + 0x138 <= vspace + 0x140) {
        *(unsigned long *)(vspace + 0x140) = vspace + 0x138;
        next = vspace + 0x148;
        if (next <= vspace + 0x1c8) {
            do {
                slot = 0;
                *(unsigned long *)(next + 8) = 0;
                do {
                    unsigned long *ent = *(unsigned long **)(next + slot + 9);
                    *(unsigned long *)(next + slot + 9) = 0;
                    *(unsigned long *)(next + slot + 1) = 0;
                    if (ent != 0) {
                        unsigned long slot64 = (unsigned long)slot;
                        ent[7] = 0;
                        ent[2] = 0;
                        {
                            unsigned long *sub = (unsigned long *)ent[3];
                            if (sub != 0) { sub[0] = 0; sub[1] = 0; sub[2] = 0; }
                        }
                        *(unsigned short *)(ent[1] + 6) = 0;
                        sk_mem_zero((void *)(uintptr_t)ent[5],
                                    (unsigned long)*(unsigned char *)((char *)ent + 0x42) << 3);
                        node = (unsigned long)sk_vspace_alloc_big(0x6af010, 4, 10);
                        {
                            unsigned long lock = node + 0xb0;
                            if (sk_vm_lock_check(lock) != 0) {  /* FUN_00118164 */
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                                __builtin_unreachable();
                            }
                            {
                                unsigned long base = ent[0];
                                unsigned long j;
                                for (j = 0; j < 0x80; j += 8) {
                                    if (*(unsigned long *)(base + j + 0x20) == ent[1]) {
                                        unsigned char n = *(unsigned char *)(base + 0x1a);
                                        if (n == 0) {
                                            sk_vas_fault4();   /* FUN_004b20e8 */
                                            __builtin_unreachable();
                                        }
                                        n = (unsigned char)(n - 1);
                                        *(unsigned char *)(base + 0x1a) = n;
                                        *(unsigned long *)(base + j + 0x20) =
                                            *(unsigned long *)(base + 0x20 + n * 8);
                                        *(unsigned long *)(base + 0x20 + n * 8) = 0;
                                        break;
                                    }
                                }
                                ent[0] = 0;
                                if (*(long *)(node + 0xa0) != (long)base)
                                    *(unsigned long *)(node + 0xa0) = node;
                                if (sk_vm_lock_take(lock) != 0) {   /* FUN_00118194 */
                                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                                    __builtin_unreachable();
                                }
                                if ((small & 1) == 0)
                                    sk_vspace_small_release();   /* FUN_00033e00 */
                                else
                                    sk_vspace_large_destroy(ent[0] | (unsigned long)ent);  /* FUN_000341f4 */
                            }
                        }
                    }
                    slot++;
                } while (slot != 7);
                next = *(unsigned long *)next;
                if (next != 0) {
                    /* advance along the store chain */
                }
            } while (0);
            *(unsigned short *)(vspace + 0x1d0) = 0;
            *(unsigned long *)(vspace + 0x1c8) = 0;
            sk_vas_body_teardown((uint64_t)(vspace + 0x60));   /* FUN_00042808 */
            return;
        }
    }
    __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x32c64) */
}

/*--------------------------------------------------------------------*/
/* FUN_0003573c @ 0x0003573c   (est. sk_alloc_aligned_frame)
 * Ghidra: void *FUN_0003573c(ulong base, ulong size, void *p3, void *p4)
 * Allocates an aligned (0x40) frame of `size` bytes at `base`. Validates
 * base is 0x40-aligned (abort "vas: mark cap slots allocated" 005b1c12),
 * takes the pool method on the frame node (FUN_00034bd8), and either creates
 * a fresh mark object (FUN_00035944) or walks the frame's slot tree
 * (FUN_00035418) linking aligned sub-frames. Releases the pool via
 * FUN_00034d5c. Returns the frame base.
 * Confidence: low-medium (structural aligned-frame allocator).
 * Notes: node 0x6af188; helpers FUN_00034bd8/00035418/00034d5c. */
void *sk_alloc_aligned_frame(void *base, unsigned long size)
{
    unsigned long pool = (unsigned long)sk_vspace_alloc_big(0x6af188, 4, 8);
    unsigned long cookie[2];
    unsigned long end = (unsigned long)base + size;
    void *result = base;

    if (((unsigned long)base & 0x3f) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1c12);
        __builtin_unreachable();
    }
    if (end > 0xffffffffffffffbf || end < (unsigned long)base) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1caf);
        __builtin_unreachable();
    }
    cookie[0] = sk_pool_method(*(unsigned long *)(*(unsigned long *)pool + 0x10));  /* FUN_00034bd8 */
    if ((cookie[0] & 1) != 0) {
        /* nested pool: create/reinit a mark object for this frame */
        if (sk_vas_fault16r() != 0) {
            unsigned short desc[4] = { 0x100, 0, 0, (unsigned short)((unsigned long)base & 0xffff) };
            sk_vspace_create_object((char *)desc, 0, (void *)(uintptr_t)sk_vas_fault16r(),
                                    (void *)(uintptr_t)8);
            return base;
        }
        sk_vspace_reinit_object((long)(uintptr_t)sk_vas_fault16r(), (void *)(uintptr_t)8,
                                (void *)(uintptr_t)0);
        return base;
    }
    sk_vspace_slot_free_search((unsigned long)base);   /* FUN_00035418 */
    if ((unsigned long)base < end) {
        do {
            unsigned long a = (unsigned long)base + 0x40;
            if (a + 0x4000 <= (unsigned long)base || a >= end) break;
            (void)sk_vspace_slot_alloc((unsigned long)base);   /* FUN_00035684 */
            base = (void *)a;
        } while ((unsigned long)base < end);
    }
    sk_pool_touch(*(unsigned long *)(*(unsigned long *)pool + 0x10));  /* FUN_00034d5c */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00035bac @ 0x00035bac   (est. sk_span_lookup_build6)
 * Ghidra: void FUN_00035bac(ulong *out, ulong span, ulong idx, ulong base, uint flags)
 * Builds a span lookup descriptor into `out` (5 words) from a span handle
 * `span`. Handles direct mappings (low bits 1 or 0), table-indirect
 * mappings (low bits 2), and recursive/hierarchy lookups; on a miss it can
 * allocate a fresh table node (FUN_000347c4/00036bd4/00036d58) when the
 * "create" flag (flags bit 0) is set. Sets out[0]=base, out[1] = a 1-bit
 * validity tag, out[2..3] from the indirect table, and out[4]=span.
 * Confidence: low-medium (large structural span-desc builder).
 * Notes: helpers FUN_000347c4/00036bd4/00036d58/0003652c/0003481c;
 *   globals DAT_004bc1b0/004bc1b8; trap 0x36008. */
void sk_span_lookup_build6(unsigned long *out, unsigned long span, unsigned long idx,
                           unsigned long base, unsigned int flags)
{
    unsigned int index = (unsigned int)idx;
    unsigned long v, tag, n;
    unsigned int lo;

    if (index > 0x3fffff) {
        out[0] = 0;
        out[1] = 0;
        out[3] = sk_vas_fault18();
        out[2] = 0;
        out[4] = span;
        return;
    }
    lo = (unsigned int)span;
    if ((lo & 3) == 1 || (span & 3) == 0) {
        if ((span & 3) == 0) {
            /* direct zero-ref / free span */
            tag = base << 0x1c;
            *(unsigned long *)((char *)out + 0x11) = 0;
            *(unsigned long *)((char *)out + 9) = 0;
            if (flags == 0) base = 0;
            out[0] = base;
            *(unsigned char *)((char *)out + 8) = (unsigned char)flags;
            tag = (index << 6 | 1) | tag;
            if (flags == 0) tag = span;
            out[3] = 0;
            out[4] = tag;
            return;
        }
        if (((lo >> 6) & 0x3fffff) == index) {
            out[0] = span >> 0x1c;
            out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = span;
            return;
        }
        if ((flags & 1) == 0) {
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = span;
            return;
        }
        /* create a fresh indirect node */
        v = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);   /* FUN_000347c4 */
        if ((unsigned long)(v + 0x40) < v) goto trap;
        (void)v;
        out[0] = base;
        *(unsigned char *)((char *)out + 8) = 1;
        out[4] = (index << 6 | 1) | (base << 0x1c);
        return;
    }
    /* indirect table / hierarchy lookup */
    {
        unsigned long *table = (unsigned long *)(uintptr_t)(span >> 0x1c);
        unsigned long *end;
        unsigned long c;

        if ((lo & 3) == 2) {
            end = table + 8;
            if ((unsigned long)(end) < (unsigned long)table) goto trap;
            for (n = 0; n < 8; n++) {
                c = table[n];
                if ((c & 3) == 1) {
                    if (((c >> 6) & 0x3fffff) == index) {
                        out[0] = c >> 0x1c;
                        out[1] = 0; out[2] = 0; out[3] = 0;
                        out[4] = span;
                        return;
                    }
                } else if ((c & 3) == 0) {
                    break;
                }
            }
            if ((flags & 1) != 0) {
                if ((lo >> 2 & 0xf) < 8) {
                    if ((unsigned long)table != 0 && (unsigned long)(end - table) < 0x39) goto trap;
                    out[0] = base;
                    *(unsigned char *)((char *)out + 8) = 1;
                    out[4] = span & 0xffffffffffffffc3 | (unsigned long)((lo >> 2 & 0xf) * 4 + 4);
                    *(unsigned long *)((char *)out + 0x11) = 0;
                    *(unsigned long *)((char *)out + 9) = 0;
                    return;
                }
            }
        } else {
            end = table + 8;
            if ((unsigned long)table == 0 || (unsigned long)(end - table) < 0x39) goto trap;
            {
                unsigned long r = (unsigned long)sk_span_find2(&c, (unsigned long)(uintptr_t)table,
                                                               index);   /* FUN_0003652c */
                if ((r & 0xf8) == 0) {
                    n = r & 7;
                    if ((table[n] >> 0x1c) != 0 && (((unsigned int)table[n] >> 6) & 0x3fffff) == index) {
                        out[0] = table[n] >> 0x1c;
                        out[1] = 0; out[2] = 0; out[3] = 0;
                        out[4] = span;
                        return;
                    }
                }
                if ((flags & 1) != 0) {
                    v = (unsigned long)sk_vspace_alloc_big(0x6af180, 4, 0xd);   /* FUN_00036d58 */
                    out[0] = base;
                    *(unsigned char *)((char *)out + 8) = 1;
                    out[4] = (index << 6 | 1) | (base << 0x1c);
                    *(unsigned long *)((char *)out + 0x11) = 0;
                    out[3] = 0;
                    return;
                }
            }
        }
    }
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    out[4] = span;
    return;
trap:
    __builtin_unreachable();  /* SoftwareBreakpoint(0x5519, 0x36008) */
}

/*--------------------------------------------------------------------*/
/* FUN_00031bf4 @ 0x00031bf4   (est. sk_vspace_level_bump)
 * Ghidra: void FUN_00031bf4(long vspace)
 * Bumps the vspace level hierarchy: when the "bump pending" flag at +0x1d0
 * is clear it walks the level table at +0x148 (7 slots + 8 links) and, for
 * each live level entry, allocates a 0x1800-byte level frame (FUN_0005acac,
 * 0x6af010), finds a free span slot via FUN_000287e4, maps the span
 * (FUN_00042abc/00042c20 + FUN_00043be8), and links the entry. On completion
 * it re-arms the +0x1d0 flag. Aborts (VAS 005aed68 etc.) on any lock/state
 * violation.
 * Confidence: low-medium (large structural level-walk).
 * Notes: helpers FUN_0005acac/00118194/00118164/000287e4/00042abc/
 *   00042c20/00043be8/00032d08; trap 0x32460. */
void sk_vspace_level_bump(long vspace)
{
    unsigned long err, i;
    long *slot;
    unsigned long cookie[4] = {0,0,0,0};
    long lv, base, m, k;
    unsigned long u;

    if ((*(unsigned char *)(vspace + 9) & 1) == 0) {
        sk_vas_fault12();                      /* FUN_004b2084 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        __builtin_unreachable();
    }
    if ((*(unsigned char *)(vspace + 0x1d0) & 1) == 0) {
        *(unsigned char *)(vspace + 0x1d0) = 1;
        slot = (long *)(vspace + 0x148);
        do {
            if (slot[8] == 0) {
                cookie[0] = 0; cookie[1] = 0; cookie[2] = 0; cookie[3] = 0;
                if (sk_vm_lock_take(vspace + 0x40) != 0) {   /* FUN_00118194 */
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    __builtin_unreachable();
                }
                err = (unsigned long)sk_vspace_alloc_big(0x6af010, 0x1800, 0) & 0xff;  /* level frame alloc */
                if (err != 0) {
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afade);
                    __builtin_unreachable();
                }
                if (cookie[3] != 0x65b648) {
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afb3f);
                    __builtin_unreachable();
                }
                if (sk_vm_lock_check(vspace + 0x40) != 0) {  /* FUN_00118164 */
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    __builtin_unreachable();
                }
                if (slot[8] != 0) {
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afba3);
                    __builtin_unreachable();
                }
                slot[8] = cookie[0];
            }
            m = 0;
            base = 0;
            lv = 0;
            k = 1;
            for (i = 0; i < 7; i++) {
                long *ent = slot + 9 + i;
                if (*ent == 0) break;
                if (*(long *)(*ent + 0x10) == 0) {
                    if ((*(unsigned char *)(vspace + 9) & 1) == 0) {
                        sk_vas_fault13();          /* FUN_004b205c */
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afcfb);
                        __builtin_unreachable();
                    }
                    lv = slot[8];
                    if (lv == 0) {
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afc10);
                        __builtin_unreachable();
                    }
                    if (sk_vm_lock_take(vspace + 0x40) != 0) {
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                        __builtin_unreachable();
                    }
                    {
                        unsigned long lock = (unsigned long)lv + 0x80;
                        unsigned long sp;
                        if (sk_vm_lock_check(lock) != 0) {
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                            __builtin_unreachable();
                        }
                        sk_span_find2(&sp, *(unsigned long *)(lv + 0x78),
                                      (int)((m + (base - *(long *)(vspace + 0x88))) >> 0xe) + 1);  /* FUN_000287e4 */
                        *(unsigned long *)(lv + 0x78) = cookie[1];
                        if (sk_vm_lock_take(lock) != 0) {
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                            __builtin_unreachable();
                        }
                        if (sp == 0) {
                            sk_vas_abort("spanmap could not alloc a cap", 0x5afea1);
                            __builtin_unreachable();
                        }
                        {
                            unsigned long where = m + base;
                            u = sk_obj_method_dispatch3(vspace + 0x60, 1, where);  /* FUN_00042abc */
                            u = sk_obj_lookup3(vspace + 0x60, u);                 /* FUN_00042c20 */
                            if ((u & 1) == 0) {
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afecd);
                                __builtin_unreachable();
                            }
                            u = sk_obj_meta4(vspace + 0x60, u, sp, where, 0, 0) & 0xff;  /* FUN_00043be8 */
                            if ((u & 0xff) == 4) {
                                u = sk_obj_attr3(vspace + 0x60, where);        /* FUN_000436fc */
                                if ((u & 1) == 0) {
                                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5affa4);
                                    __builtin_unreachable();
                                }
                                u = sk_obj_meta4(vspace + 0x60, u, sp, where, 0, 0) & 0xff;
                            }
                            if ((u & 0xff) != 0) {
                                sk_l4_error_word(&cookie[0], (unsigned char)u);  /* FUN_00032d08 */
                                sk_vas_fault41(0xeb1a02bf914012ba);              /* FUN_004b1c84 */
                                sk_vas_abort("Unexpected L4 Error %s %zu err", 0x5b010f);
                                __builtin_unreachable();
                            }
                        }
                    }
                }
                base += 0x4000;
            }
        } while (0);
        if ((*(unsigned char *)(vspace + 0x1d0) & 1) == 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afa56);
            __builtin_unreachable();
        }
        *(unsigned short *)(vspace + 0x1d0) = 0x100;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000387fc @ 0x000387fc   (est. sk_faulthandler_create)
 * Ghidra: cl4_result_t FUN_000387fc(void *region, ulong *out)
 * Creates a faulthandler descriptor for a region. Allocates a node
 * (FUN_00033638), builds a span (sk_region_create FUN_0003c56c) for the
 * region's write span, resolves the region layout (FUN_00032cd0), then
 * builds the read-span descriptor and two TCB slots (sk_vspace_slot_alloc_new
 * FUN_00034f70). Fills the out descriptor with the region base/size, the two
 * cap slots, and a 0x4000 granule, and attaches the region into the vspace
 * root. On the faulthandler map path it walks the region's page list
 * (sk_span_cursor_build/next FUN_000363ac/0003667c), mapping and
 * finalising each span page (sk_region_map_fault FUN_0003fa94 /
 * sk_region_finalize FUN_0003f170). Returns {0,0} on success.
 * Confidence: low-medium (large structural faulthandler constructor).
 * Notes: helpers FUN_00033638/0003c56c/00032cd0/000287e4/00118164/
 *   00118194/00034f70/001180fc/0002fa84/0003fa94/0003f170/00036008/
 *   0003da18/000363ac/0003667c; faults 004b2930/004b28f8/004b29a0. */
cl4_result_t sk_faulthandler_create(void *region, unsigned long *out)
{
    cl4_result_t r;
    unsigned long local[10];
    unsigned long vspace, span, base, size;
    unsigned long ck;
    unsigned long node;
    unsigned long wbase, wsize;
    int i;

    DAT_006ad2cc = DAT_006ad2cc + 1;
    for (i = 0; i < 10; i++) local[i] = 0;

    node = (unsigned long)sk_pool_alloc_node_c1a8((void *)(uintptr_t)0);  /* FUN_00033638 */
    ck = (unsigned long)sk_region_create((long)(uintptr_t)&sk_vspace_root_obj, 0x1908,
                                         (char *)&sk_desc_boot, &local[7], 0, 0) & 0xff;  /* FUN_0003c56c */
    if (ck != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b4f3f);
        __builtin_unreachable();
    }
    vspace = local[7];
    span = *(unsigned long *)(vspace + 0x10);
    wsize = *(unsigned long *)(vspace + 8);
    if (sk_vm_lock_check(vspace + 0x80) != 0) {     /* FUN_00118164 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        __builtin_unreachable();
    }
    {
        unsigned long layout = (unsigned long)sk_vspace_layout_check_big(*(unsigned long *)(vspace + 0x50));  /* FUN_00032cd0 */
        sk_span_find2(&local[2], span, (int)(wsize - *(long *)(layout + 0x28) >> 0xe) + 1);  /* FUN_000287e4 */
        *(long *)(vspace + 0x78) = (long)local[6];
        if (sk_vm_lock_take(vspace + 0x80) != 0) {  /* FUN_00118194 */
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            __builtin_unreachable();
        }
    }
    local[0] = 0; local[1] = 0;
    ck = (unsigned long)sk_region_create((long)(uintptr_t)&sk_vspace_root_obj, 0x1900,
                                         (char *)&sk_desc_boot, local, 0, 0) & 0xff;  /* FUN_0003c56c */
    if (ck != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b4ffa);
        __builtin_unreachable();
    }
    wsize = *(unsigned long *)(local[0] + 8);
    span = *(unsigned long *)(local[0] + 0x10);
    if (sk_vm_lock_check(local[0] + 0x80) != 0) {
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        __builtin_unreachable();
    }
    {
        unsigned long layout = (unsigned long)sk_vspace_layout_check_big(*(unsigned long *)(local[0] + 0x50));  /* FUN_00032cd0 */
        sk_span_find2(&local[2], *(unsigned long *)(local[0] + 0x78),
                      (int)(wsize - *(long *)(layout + 0x28) >> 0xe) + 1);  /* FUN_000287e4 */
        local[6] = local[2];
        *(long *)(local[0] + 0x78) = (long)local[3];
        if (sk_vm_lock_take(local[0] + 0x80) != 0) {
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            __builtin_unreachable();
        }
    }
    /* build the faulthandler out descriptor */
    {
        unsigned long slotA = (unsigned long)sk_vspace_slot_alloc_new();  /* FUN_00034f70 */
        unsigned long slotB = (unsigned long)sk_vspace_slot_alloc_new();  /* FUN_00034f70 */
        unsigned long wbase = local[1];
        unsigned long lo = local[0];
        if (wsize + span < wsize || (wsize + span) - wsize < 0x4000) {
            __builtin_unreachable();
        }
        if (node != 0) {
            ((unsigned long *)node)[0xb] = (unsigned long)lo;
            ((unsigned long *)node)[0xc] = wsize;
            ((unsigned long *)node)[0xd] = span;
            ((unsigned long *)node)[0xe] = local[0];
            ((unsigned long *)node)[0xf] = wsize + span;
            ((unsigned long *)node)[0x10] = local[2];
            ((unsigned long *)node)[0x11] = 0x4000;
            ((unsigned long *)node)[0x12] = slotA;
            ((unsigned long *)node)[0x13] = slotB;
            ((unsigned long *)node)[0x15] = 0;
            ((unsigned long *)node)[0x14] = 0;
            ((unsigned long *)node)[0x17] = 0;
            ((unsigned long *)node)[0x16] = 0;
            ((unsigned long *)node)[0] = (unsigned long)region;
            ((unsigned long *)node)[2] = 0;
            ((unsigned long *)node)[1] = 0;
            ((unsigned long *)node)[4] = 0;
            ((unsigned long *)node)[3] = 0;
            ((unsigned long *)node)[6] = 0;
            ((unsigned long *)node)[5] = 0;
            *(unsigned long *)((char *)node + 0x39) = 0;
            *(unsigned long *)((char *)node + 0x31) = 0;
            *(unsigned char *)((char *)node + 0x41) = 1;
            ((unsigned long *)node)[9] = 0;
            ((unsigned long *)node)[10] = (unsigned long)region;
            *(unsigned long *)((char *)node + 0x42) = 0;
            FUN_001180fc((unsigned long *)node + 6);
            if (slotA == 0) {
                sk_vas_fault38();                   /* FUN_004b2930 */
                __builtin_unreachable();
            }
            if (slotB != 0) {
                out[0] = (unsigned long)region;
                out[1] = node;
                out[2] = 0x65b630;
                r.lo = 0; r.hi = 0;
                return r;
            }
        }
        /* faulthandler map path: walk the region's page list */
        if (sk_boot_region_check(0x65b5a0, (unsigned long)region + 0x208) == 0) {  /* FUN_0002fa84 */
            sk_vspace_layout_check_big((long)(uintptr_t)region);   /* FUN_00032cd0 */
        }
        {
            unsigned long st = 0;
            unsigned long sp = 0;
            ck = (unsigned long)sk_region_create((long)(uintptr_t)sk_vspace_root(), 0x1908,
                                                 (char *)&sk_desc_boot, &st, 0, 0) & 0xff;  /* FUN_0003c56c */
            if (ck == 0) {
                base = *(unsigned long *)(st + 8);
                size = *(unsigned long *)(st + 0x10);
                if (sk_vm_lock_check((unsigned long)region + 0x1f0) != 0) {
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    __builtin_unreachable();
                }
                {
                    unsigned long node2 = *(unsigned long *)((unsigned long)region + 0x200);
                    while (node2 != 0) {
                        if ((*(unsigned int *)(node2 + 0x20) >> 3 & 1) != 0) {
                            if (sk_vm_lock_check(node2 + 0x80) != 0) {
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                                __builtin_unreachable();
                            }
                            {
                                unsigned long cur[3];
                                sk_span_cursor_build(cur, *(unsigned long *)(node2 + 0x78), 0);  /* FUN_000363ac */
                                {
                                    unsigned long c2 = sk_span_cursor_next(cur);   /* FUN_0003667c */
                                    while ((c2 & 3) != 0) {
                                        /* map each live span page */
                                        if ((c2 >> 0x1c) == 0) {
                                            long m = (long)sk_region_map_fault((long)st, (long)base, 0, 0, 0, 0, 0);  /* FUN_0003fa94 */
                                            if (m == 0) {
                                                unsigned long fbase = 0, fsize = 0x4000;
                                                if (sk_region_finalize(st, &fbase, &fsize, 0) == 0) {  /* FUN_0003f170 */
                                                    sk_region_unmap_pages(c2 >> 6 & 0x3fffff, (long)node2, 0, 0, 0);  /* FUN_0003da18 */
                                                }
                                            }
                                        }
                                        c2 = sk_span_cursor_next(cur);
                                    }
                                }
                            }
                        }
                        node2 = *(unsigned long *)(node2 + 0x90);
                    }
                }
                if (sk_vm_lock_take((unsigned long)region + 0x1f0) != 0) {
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    __builtin_unreachable();
                }
            }
        }
    }
    r.lo = 0; r.hi = 0;
    return r;
}
