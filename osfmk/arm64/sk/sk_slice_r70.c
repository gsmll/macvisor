/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x6766b0-0x67d440) is the embedded C/printf runtime + the
 * object/region and memory-management helpers layered on top of it: L4 error
 * code descriptors, region (page-range) descriptor layout/translate/unmap,
 * the memory block list used for mapping objects, the SIMD-string primitives
 * (memset/memmove/strcmp/strlen/memchr), the object-list iterators, and the
 * vcbprintf-style formatter (%e/%g/%f/%d/%x) with its FILE-like writer.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;
typedef unsigned long ulong;
typedef void *code;                         /* opaque function-pointer slot */

/* ------------------------------------------------------------------ *
 * Out-of-region callees (declared extern; live elsewhere in the kernel).
 * ------------------------------------------------------------------ */
extern void FUN_006833d4(ulong msg);                 /* noreturn panic(message addr) */
extern void FUN_0067f660(void);                      /* noreturn stack-canary fail */
extern ulong FUN_0065be08(ulong, int, int);          /* percpu/global state getter */
extern void FUN_0065cc0c(int, int);                  /* init helper */
extern void FUN_006568d0(void);                      /* read config byte */
extern void FUN_00656908(void);
extern void FUN_006568ec(void);
extern void FUN_0065cbbc(ulong);                     /* release/note helper */
extern void FUN_0064e07c(void);                      /* 16-byte return */
extern void FUN_00654d4c(void);                      /* list head getter */
extern void FUN_0064effc(ulong *, int);              /* copy descriptor */
extern unsigned char FUN_0068761c(void);             /* read boot error-code byte */
extern void FUN_00687654(void);
extern void FUN_006876a4(void);
extern void FUN_0068767c(ulong, ulong);
extern void FUN_006876cc(ulong, ulong, ulong, ulong);
extern void FUN_00687758(void);
extern void FUN_00687784(ulong, ulong);
extern void FUN_006877ec(void);
extern void FUN_006878a0(void);
extern void FUN_00687814(void);
extern void FUN_0068784c(void);
extern void FUN_0066a8f4(ulong, ulong, ulong);       /* install callback */
extern void FUN_0066a1cc(ulong);                     /* release one slot */
extern void FUN_00687524(void);                      /* panic/report path */
extern void FUN_00687550(void);                      /* unreachable/bad state */
extern void FUN_00687564(ulong, ulong);
extern void FUN_006875c0(ulong, ulong);
extern void FUN_00656978(void);                      /* 16-byte return op */
extern void FUN_00656924(void);
extern void FUN_0066bce0(ulong *, ulong, int, ulong); /* build mapping entry */
extern void FUN_00655e7c(void);                      /* ints-disabled check */
extern void FUN_0066a988(ulong);                     /* try-lock state */
extern void FUN_0066a9bc(ulong);                     /* 16-byte return */
extern void FUN_0066ab40(ulong, ulong, ulong);       /* restore state */
extern void FUN_006874b4(ulong, ...);                /* fatal report w/ args */
extern void FUN_006878cc(ulong, ulong);
extern void FUN_00687928(void);
extern void FUN_00687960(void);
extern void FUN_00687998(ulong, ulong);
extern void FUN_00672e5c(ulong, ulong *, ulong *);   /* clip range */
extern void FUN_006879f4(void);
extern void FUN_00687a2c(void);
extern void FUN_00671320(ulong);
extern void FUN_00671220(ulong, ulong);
extern void FUN_00671150(ulong);
extern void FUN_00671384(ulong);
extern void FUN_00671018(void);
extern void FUN_006710e8(ulong, ulong);
extern void FUN_00671af0(ulong*,ulong,ulong,ulong,ulong,ulong,ulong,int); /* 16-byte? */
extern void FUN_00671398(void);
extern void FUN_00671bc4(ulong*,ulong);
extern void FUN_00687a9c(void);
extern void FUN_00687ad4(void);
extern void FUN_00687b0c(void);
extern void FUN_00687b48(void);
extern void FUN_00687b74(void);
extern void FUN_00687bac(void);
extern void FUN_00655650(void);
extern void FUN_006555fc(ulong);
extern void FUN_0065569c(void);
extern void FUN_00655774(void);
extern void FUN_006551d0(void);
extern void FUN_00655218(void);
extern void FUN_00655234(void);
extern void FUN_00655274(ulong, ulong);
extern void FUN_006552b0(void);
extern void FUN_006552c4(void);
extern void FUN_006552f8(void);
extern void FUN_0065c288(ulong);                     /* noreturn panic */
extern void FUN_0065558c(void);                      /* noreturn */
extern void FUN_00665d70(ulong, ulong);              /* teardown/cleanup */
extern ulong thunk_FUN_00660b28(ulong);              /* state query */
extern void FUN_0067d83c(ulong, ulong, ulong *);
extern void FUN_0067d6c0(void);
extern void FUN_0065562c(ulong, ulong *);            /* 16-byte return */
extern void FUN_00661178(void);
extern void FUN_00656b98(ulong);
extern void FUN_0067e9c0(void);
extern void FUN_0067dc08(void);
extern void FUN_0067d4a4(ulong, ulong, ulong);

/* AArch64 system helpers. */
extern void CallSupervisor(unsigned long n);        /* SVC with selector in x16 */
extern void SoftwareBreakpoint(unsigned long op, unsigned long addr);
extern void DC_ZVA(unsigned long addr);             /* data-cache zero by VA */
extern void NEON_uminv(void *buf, int sz);          /* min-across-vector (byte) */

/* ------------------------------------------------------------------ *
 * Binary globals referenced by these bodies.
 * ------------------------------------------------------------------ */
extern volatile unsigned long _DAT_006b5ed0;        /* stack-cookie */
extern volatile unsigned long _DAT_006b4368;
extern volatile unsigned long _DAT_006b4370;
extern volatile unsigned long _DAT_006b4378;
extern volatile unsigned long _DAT_006b4360;
extern volatile unsigned char  DAT_006feb78;
extern volatile unsigned long  DAT_006feb80;
extern volatile unsigned long  DAT_006feb88;        /* PRNG state lo */
extern volatile unsigned long  DAT_006feb90;        /* PRNG state hi */
extern volatile unsigned char  DAT_006feca0;        /* tco toggle flag */
extern volatile unsigned long  _DAT_0067a8e0;
extern volatile unsigned long  _DAT_0067a8e8;
extern volatile unsigned long  _DAT_0067aea0;
extern volatile unsigned long  _DAT_0067aea8;
extern volatile unsigned long  _DAT_0067afe0;
extern volatile unsigned long  _DAT_0067afe8;
extern volatile unsigned long  _DAT_0067b160;
extern volatile unsigned long  _DAT_0067b168;
extern volatile unsigned long  _DAT_0067b170;
extern volatile unsigned long  _DAT_0067b178;

extern unsigned long tpidrro_el0;                   /* RO thread ptr (u/s boundary) */
extern unsigned long tpidr_el0;
extern int tco;                                     /* errno-ish toggle */

/* ================================================================== *
 * L4 error code descriptors + region (page-range) management.
 * ================================================================== */

/* FUN_006766cc @ 0x6766b0
 * Ghidra: void FUN_006766cc(undefined8 param_1, ulong *param_2)
 * Validate an error-code/level value against the region descriptor table;
 * panics on inconsistent ranges. Confidence: medium. */
void FUN_006766cc(ulong level, ulong *range)
{
    int lv = (int)level;
    if (lv == 1) {
        ulong cfg = FUN_006767f8();
        if ((cfg & 1) == 0)
            FUN_00687524();                 /* config not enabled -> report */
    } else {
        ulong lo = 0, hi = ~0UL;
        if (range != NULL) { lo = range[0]; hi = range[1]; }
        ulong a = FUN_0067686c(level);
        ulong b = FUN_006768b4(level);
        ulong m1 = (lo <= a) ? a : lo;
        ulong m2 = (b <= hi) ? b : hi;
        if (hi <= lo || b <= a || m2 <= m1)
            FUN_006833d4(0x6af0d9);         /* invalid range pair */
        if ((lv - 1U < 2) || lv == 0)
            return;
    }
    FUN_006833d4(0x6af267);                 /* bad level */
}

/* FUN_006767f8 @ 0x6767f8
 * Ghidra: undefined1 FUN_006767f8(void)
 * Return the configuration byte at the global state pointer, initialising
 * the config word (via three sub-reads) on first use. Confidence: medium. */
unsigned char FUN_006767f8(void)
{
    if ((DAT_006feb78 & 1) == 0) {
        long r = FUN_0065cc0c(4, 0xc);
        if (r == 0) {
            *(volatile unsigned char *)&DAT_006feb79 = FUN_006568d0();
            *(volatile unsigned char *)&DAT_006feb7a = FUN_00656908();
            *(volatile unsigned char *)&DAT_006feb7b = FUN_006568ec();
            FUN_0065cbbc(0x6b5eb0);
        }
        DAT_006feb78 = 1;
    }
    unsigned char *p = (unsigned char *)FUN_0067747c();
    return *p;
}

/* FUN_0067686c @ 0x67686c
 * Ghidra: undefined8 FUN_0067686c(uint param_1)
 * Return the level-size word from the fixed table at DAT_0068a8a0. */
unsigned long FUN_0067686c(unsigned int level)
{
    if (level < 3)
        return *(unsigned long *)(&DAT_0068a8a0 + level * 8);
    FUN_006833d4(0x6af267);
}

/* FUN_006768b4 @ 0x6768b4
 * Ghidra: long FUN_006768b4(int param_1)
 * Return the byte span for a region level: fixed 64GB / 4TB, or (for the
 * configured level) 1 << (config byte+1). Confidence: medium. */
long FUN_006768b4(int level)
{
    if (level == 0)
        return 0x1000000000L;
    if (level == 2)
        return 0x40000000000L;
    if (level != 1)
        FUN_006833d4(0x6af267);
    long base = FUN_0067747c();
    return 1L << ((unsigned long)*(unsigned char *)(base + 1) & 0x3f);
}

/* FUN_00676924 @ 0x676924
 * Ghidra: long FUN_00676924(long, int, ulong, long, undefined8, undefined8)
 * Build the page-range descriptor table inside a region object: stamp the
 * type byte, the base and end addresses, the invoke callbacks, then fill
 * the per-level range entries (0x18 bytes each) and accumulate the total
 * span. Confidence: medium. */
long FUN_00676924(long region, int level, ulong base, long end, ulong cb0, ulong cb1)
{
    *(char *)(region + 0x98) = (char)level;
    *(ulong *)(region + 0x28) = base;
    *(long *)(region + 0x30) = end;
    *(ulong *)(region + 0xb0) = cb0;
    *(ulong *)(region + 0xb8) = cb1;

    ulong nlevels;
    if (level == 0)
        nlevels = 2;
    else if (level == 2)
        nlevels = 3;
    else {
        if (level != 1)
            FUN_006833d4(0x6af267);
        long cfg = FUN_0067747c();
        ulong v = (ulong)*(unsigned char *)(cfg + 1) - 0xe;
        nlevels = v / 0xb;
        if (v % 0xb != 0)
            nlevels = nlevels + 1;
    }

    ulong idx = 0, accum = 0, lv = 0;
    do {
        unsigned char *slot = (unsigned char *)(region + 0x38) + idx * 0x18;
        if (slot < (unsigned char *)(region + 0x38) ||
            (unsigned char *)(region + 0x98) < slot + 0x18 || slot + 0x18 < slot)
            SoftwareBreakpoint(0x5519, 0x676a5c);
        ulong mask = -1L << ((ulong)((int)lv * 0xb + 0x16) & 0x3f) & base;
        ulong span = (end + ~(-0x4000L << (idx * 0xb & 0x3f))) - mask >>
                     (idx * 0xb + 0xe & 0x3f);
        *(ulong *)(slot + 8) = mask;
        *(ulong *)(slot + 0x10) = span;
        long w = 0;
        if ((span & 0xff) != 0)
            w = 0x100;
        accum = accum + (w + (span & 0x3ffffffffffff00)) * 0x40;
        ulong nxt = (ulong)((int)lv + 1);
        lv = nxt;
    } while ((unsigned char)nxt <= (unsigned char)nlevels);
    return accum;
}

/* FUN_00676a7c @ 0x676a7c
 * Ghidra: void FUN_00676a7c(undefined8, long, long)
 * Full mapping-install path: ensure the root region exists, walk the
 * capability list, (re)install page-table entries for each mapped object,
 * and seed the initial free page range. Confidence: low (large, hot path). */
void FUN_00676a7c(ulong arg1, long base, long len)
{
    long cookie = _DAT_006b5ed0;
    long r = FUN_0065cc0c(4, 0xb);
    if (r == 0) {
        *(volatile unsigned long *)&DAT_006feb58 = 0x6b5760;
        FUN_0065cbbc(0x6b5e90);
    }
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if ((*(unsigned char *)(st + 0x100) & 1) != 0) {
done:
        if (_DAT_006b5ed0 == cookie)
            return;
        FUN_0067f660();
    }

    ulong obj = *(ulong *)(st + 0xf8);
    if (obj <= obj + 0xd0) {
        FUN_006766cc(0, 0);
        FUN_00676924(obj, 0, 0, 0, 0, 0);
        if (*(ulong *)(obj + 0x48) >> 0xe == 0)
            FUN_006833d4(0x6af1d6);
        ulong *it = (ulong *)FUN_00654d4c();
        ulong st2 = FUN_0065be08(0x6feb70, 4, 0xb);
        ulong region = *(ulong *)(st2 + 0xf8);
        if (region <= region + 0xd0) {
            ulong *rt = (ulong *)(region + 0x98);
            char k = *(char *)rt;
            ulong nlv;
            if (k == 0) nlv = 2;
            else if (k == 2) nlv = 3;
            else {
                if (k != 1) FUN_006833d4(0x6af267);
                long cfg = FUN_0067747c();
                ulong v = (ulong)*(unsigned char *)(cfg + 1) - 0xe;
                nlv = v / 0xb;
                if (v % 0xb != 0) nlv = nlv + 1;
            }
            /* install any direct object pages already present in the list */
            if (it != (ulong *)-1) {
                ulong *tbl = (ulong *)(region + 0x38) + nlv * 3;
                do {
                    if (it + 0x800 < it) goto trap;
                    ulong cnt = *it;
                    if (cnt != 0) {
                        ulong *e = it + 4;
                        do {
                            if (e != NULL && (e < it + 4 || it + 0x800 < e + 4 || e + 4 < e))
                                goto trap;
                            if (k != 2) {
                                ulong tag = *e;
                                unsigned int bt = (unsigned int)(unsigned char)(tag >> 0x38);
                                if (k == 1) {
                                    if (tag >> 0x38 == 0x11 ||
                                        *(unsigned char *)(FUN_0067747c() + 2) == bt)
                                        FUN_00687550();
                                } else {
                                    if (k != 0) goto bad;
                                    bt = bt - 4;
                                    if (((bt & 0xff) < 0xe) &&
                                        ((0x3f01U >> (ulong)(bt & 0x1f) & 1) != 0) &&
                                        *(ulong *)(&DAT_0068a8b8 + ((ulong)bt & 0xff) * 8) == nlv) {
                                        if (tbl < (ulong *)(region + 0x38)) goto trap;
                                        if (*tbl == 0)
                                            *tbl = tag & 0xffffffffffffff;
                                    }
                                }
                            }
bad:
                            e = e + 4;
                            cnt = cnt - 1;
                        } while (cnt != 0);
                    }
                    it = (ulong *)it[1];
                } while (it != (ulong *)-1);
            }

            /* seed the free range slots */
            ulong end = base + (ulong)len * 0x40;
            ulong start = end - 0x4000;
            if ((ulong)((ulong)len * 0x40) < 0x4001)
                start = (ulong)base;
            ulong *slots = (ulong *)(region + 0x38);
            ulong *level3 = slots + nlv * 3;
            if (slots <= level3 && level3 + 3 <= rt && level3 <= level3 + 3) {
                if (*level3 == 0)
                    FUN_006833d4(0x6af9ce);
                ulong k2 = nlv - 1;
                if (k2 != 0) {
                    ulong *p = (ulong *)(region + nlv * 0x18 + 0x20);
                    do {
                        if (p < slots || rt < p + 3 || p + 3 < p) goto trap;
                        ulong sz = p[2];
                        if (0xff < sz) break;
                        if (end - start < sz)
                            FUN_006833d4(0x6afa7b);
                        end = end + sz * -0x40;
                        *p = end;
                        k2 = k2 - 1;
                        p = p - 3;
                    } while (k2 != 0);
                }
                if (end - start < 0x240)
                    FUN_006833d4(0x6afae7);
                long i = 0;
                do {
                    ulong *dst = (ulong *)(obj + i + 0x30);
                    ulong *src = (ulong *)(obj + i + 0x38);
                    if ((ulong *)(obj + 0x60) < src || src < dst) goto trap;
                    *dst = end;
                    end = end - 0x40;
                    i = i + 8;
                } while (i != 0x30);
                long j = 0;
                *(ulong *)(obj + 0x78) = 6;
                *(char *)(obj + 0x101) = 6;
                ulong *free = (ulong *)(obj + 0x60);
                do {
                    if ((ulong *)(obj + 0x78) < free + 1 || free + 1 < free) goto trap;
                    *free = end + j;
                    j = j - 0x40;
                    free = free + 1;
                } while (j != -0xc0);
                *(ulong *)(obj + 0x80) = 3;
                if (obj <= obj + 0x110) {
                    FUN_0066a8f4(obj, FUN_006792a4, 0);
                    /* re-walk the object list and fix up PTEs for page objects */
                    for (ulong *o = (ulong *)FUN_00654d4c(); o != (ulong *)-1;
                         o = (ulong *)o[1]) {
                        if (o + 0x800 < o) goto trap;
                        ulong cnt = *o;
                        if (cnt != 0) {
                            ulong *e = o + 4;
                            do {
                                if (e != NULL && (e < o + 4 || o + 0x800 < e + 4 || e + 4 < e))
                                    goto trap;
                                char k = *(char *)rt;
                                if (k != 2) {
                                    ulong tag = *e;
                                    unsigned char bt = (unsigned char)(tag >> 0x38);
                                    if (k == 1) {
                                        if (tag >> 0x38 == 0x11 ||
                                            *(char *)(FUN_0067747c() + 2) == (char)bt)
                                            goto badstate;
                                    } else {
                                        if (k != 0) goto badstate;
                                        if (((unsigned char)(bt - 0xcU) < 5) &&
                                            (k2 < *(ulong *)(&DAT_0068a928 +
                                             (ulong)(unsigned char)(bt - 0xc) * 8))) {
                                            ulong v = tag & 0xffffffffffffff;
                                            ulong phys = FUN_00677674(region,
                                                *(ulong *)(&DAT_0068a928 +
                                                (ulong)(unsigned char)(bt - 0xc) * 8),
                                                (e[2] & 0xffffffffff) << 0xc);
                                            if (v != phys) {
                                                CallSupervisor(1);
                                                if ((tag & 0xff) != 0) {
                                                    FUN_00687564(v, (ulong)0);
                                                    goto badstate;
                                                }
                                                *e = phys & 0xffffffffffffff |
                                                     (ulong)*(unsigned char *)((long)e + 7) << 0x38;
                                            }
                                        }
                                    }
                                }
                                e = e + 4;
                                cnt = cnt - 1;
                            } while (cnt != 0);
                        }
                    }
                    /* drain the deferred-unmap queue for page mappings */
                    long *q = (long *)FUN_00654d4c();
                    cL4_w16_t st3 = (cL4_w16_t)FUN_0065be08(0x6feb70, 4, 0xb);
                    if (q != (long *)-1) {
                        ulong rgn = *(ulong *)(st3.lo + 0xf8);
                        do {
                            long n = *q;
                            if (n != 0) {
                                long c = 0;
                                ulong *e = (ulong *)(q + 4);
                                do {
                                    if (e != NULL && (e < q + 4 || q + 0x800 < e + 4 || e + 4 < e))
                                        goto trap;
                                    char k = *(char *)(rgn + 0x98);
                                    if (k != 2) {
                                        ulong tag = *e;
                                        unsigned char bt = (unsigned char)(tag >> 0x38);
                                        if (k == 1) {
                                            if (tag >> 0x38 == 0x11 ||
                                                *(char *)(FUN_0067747c() + 2) == (char)bt)
                                                goto badstate;
                                        } else if (k == 0) {
                                            if ((unsigned char)(bt - 0xcU) < 5) {
                                                ulong v = tag & 0xffffffffffffff;
                                                cL4_w16_t r = (cL4_w16_t)FUN_00677674(rgn,
                                                    *(ulong *)(&DAT_0068a928 +
                                                    (ulong)(unsigned char)(bt - 0xc) * 8),
                                                    (e[2] & 0xffffffffff) << 0xc);
                                                if (v != r.lo) {
                                                    CallSupervisor(1);
                                                    if ((tag & 0xff) == 5) {
                                                        ulong ok = FUN_006777d8(rgn, r.lo);
                                                        if ((ok & 1) == 0) goto badstate;
                                                        CallSupervisor(1);
                                                    }
                                                    if ((tag & 0xff) != 0) {
                                                        FUN_006875c0(v, (ulong)0);
                                                        goto badstate;
                                                    }
                                                    *e = r.lo & 0xffffffffffffff |
                                                         (ulong)*(unsigned char *)((long)e + 7) << 0x38;
                                                }
                                            }
                                        } else goto badstate;
                                    }
                                    c = c + 1;
                                    e = e + 4;
                                } while (n != c);
                            }
                            q = (long *)q[1];
                        } while (q != (long *)-1);
                    }
                    *(char *)(st + 0x100) = 1;
                    goto done;
                }
            }
        }
    }
trap:
    SoftwareBreakpoint(0x5519, 0x677108);
badstate:
    FUN_006833d4(0x6af267);
}

/* FUN_0067728c @ 0x67728c
 * Ghidra: void FUN_0067728c(void)
 * Release every occupied slot in the region's free-range bookkeeping, then
 * free all frames of each populated level. Confidence: medium. */
void FUN_0067728c(void)
{
    long i;
    for (i = 0x30; i != 0x60; i += 8) {
        long st = FUN_0065be08(0x6feb70, 4, 0xb);
        ulong *p = (ulong *)(st + i);
        if ((ulong *)(st + 0x60) < p + 1 || p + 1 < p) goto trap;
        FUN_0066a1cc(*p);
    }
    for (i = 0x60; i != 0x78; i += 8) {
        long st = FUN_0065be08(0x6feb70, 4, 0xb);
        ulong *p = (ulong *)(st + i);
        if ((ulong *)(st + 0x78) < p + 1 || p + 1 < p) goto trap;
        FUN_0066a1cc(*p);
    }
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    ulong obj = *(ulong *)(st + 0xf8);
    if (obj <= obj + 0xd0) {
        char *rt = (char *)(obj + 0x98);
        char k = *rt;
        long lv;
        if (k == 0) lv = 1;
        else if (k == 2) lv = 2;
        else {
            if (k != 1) FUN_006833d4(0x6af267);
            long cfg = FUN_0067747c();
            ulong v = (ulong)*(unsigned char *)(cfg + 1) - 0xe;
            ulong n = v / 0xb;
            if (v % 0xb != 0) n = n + 1;
            lv = n - 1;
        }
        char *base = (char *)(obj + 0x38);
        char *e = base + lv * 0x18;
        if (base <= e && e + 0x18 <= rt && e <= e + 0x18) {
            do {
                ulong cnt = *(ulong *)(obj + 0x48 + lv * 0x18);
                if (0xff < cnt) return;
                if (cnt != 0) {
                    long f = *(long *)(base + lv * 0x18);
                    do {
                        FUN_0066a1cc(f);
                        f = f + 0x40;
                        cnt = cnt - 1;
                    } while (cnt != 0);
                }
                lv = lv - 1;
                e = base + lv * 0x18;
            } while ((base <= e && e + 0x18 <= rt) && e <= e + 0x18);
        }
    }
trap:
    SoftwareBreakpoint(0x5519, 0x677440);
}

/* FUN_0067747c @ 0x67747c
 * Ghidra: void FUN_0067747c(void) (returns a 32-byte config descriptor)
 * Return a pointer to the current L4 configuration/error-code descriptor.
 * On first use the configuration word is bootstrapped from the fixed
 * error-code name table. Callers read byte[+1] (level) / byte[+2]
 * (page-size byte). Confidence: medium. */
ulong FUN_0067747c(void)
{
    if ((DAT_006feb78 & 1) != 0) {
        return FUN_0065be08(0x6feb80, 4, 0xc);
    }
    /* One-time bootstrap: read the current error code and copy the matching
     * 4-word descriptor into the caller's output register block (x8). */
    unsigned char code = FUN_0068761c();
    if (code > 9) {
        FUN_0064effc((ulong *)0x68a888, 0x20);   /* default descriptor */
    } else {
        unsigned long base;
        switch (code) {
        default: base = 0x68a740; break;   /* Success */
        case 1:  base = 0x68a760; break;   /* Preempted */
        case 2:  base = 0x68a780; break;   /* Canceled */
        case 3:  base = 0x68a7a0; break;   /* Truncated */
        case 4:  base = 0x68a7c0; break;   /* CapInvalid */
        case 5:  base = 0x68a7e0; break;   /* SlotInvalid */
        case 6:  base = 0x68a800; break;   /* MethodInvalid */
        case 7:  base = 0x68a820; break;   /* ArgumentInvalid */
        case 8:  base = 0x68a840; break;   /* OperationInvalid */
        case 9:  base = 0x68a860; break;   /* PermissionInvalid */
        }
        FUN_0064effc((ulong *)base, 0x20);
    }
    return 0x68a880;                        /* descriptor base word */
}

/* FUN_006774ac @ 0x6774ac
 * Ghidra: void FUN_006774ac(undefined8 *param_1, byte param_2)
 * Fill a 32-byte caller buffer with the 4-word descriptor for the given L4
 * error code (name, id, etc.) from the fixed table. Confidence: medium. */
void FUN_006774ac(ulong *out, unsigned char code)
{
    unsigned long *src;
    if (code > 9) {
        out[0] = 0x68a880; out[1] = 0x68a888;
        out[2] = 0x68a890; out[3] = 0x68a898;
        return;
    }
    switch (code) {
    default: src = (unsigned long *)0x68a740; break;    /* Success */
    case 1:  src = (unsigned long *)0x68a760; break;    /* Preempted */
    case 2:  src = (unsigned long *)0x68a780; break;    /* Canceled */
    case 3:  src = (unsigned long *)0x68a7a0; break;    /* Truncated */
    case 4:  src = (unsigned long *)0x68a7c0; break;    /* CapInvalid */
    case 5:  src = (unsigned long *)0x68a7e0; break;    /* SlotInvalid */
    case 6:  src = (unsigned long *)0x68a800; break;    /* MethodInvalid */
    case 7:  src = (unsigned long *)0x68a820; break;    /* ArgumentInvalid */
    case 8:  src = (unsigned long *)0x68a840; break;    /* OperationInvalid */
    case 9:  src = (unsigned long *)0x68a860; break;    /* PermissionInvalid */
    }
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    out[3] = src[3];
}

/* FUN_006775c0 @ 0x6775c0
 * Ghidra: uint FUN_006775c0(long param_1, ulong param_2)
 * Return the page-size byte for a region level: 0 for the 2-level mode, the
 * configured size byte for level 1, or an encoded value for level 0
 * (0x04/0x0e/etc. via the 0xc0d0e04 bit layout). Confidence: medium. */
unsigned int FUN_006775c0(long region, ulong level)
{
    char k = *(char *)(region + 0x98);
    unsigned int r;
    if (k == 2)
        r = 0;
    else if (k == 1) {
        if (2 < level - 1)
            FUN_006833d4(0x6af952);
        r = (unsigned int)*(unsigned char *)(FUN_0067747c() + 2);
    } else {
        if (k != 0)
            FUN_006833d4(0x6af999);
        r = 0xc0d0e04 >> (ulong)(((unsigned int)level & 3) << 3);
        if (3 < level)
            r = 4;
    }
    return r & 0xff;
}

/* FUN_00677674 @ 0x677674
 * Ghidra: long FUN_00677674(long param_1, long param_2, long param_3)
 * Translate a virtual address through a region's level table: return the
 * physical frame pointer (or the cached alias from the overflow map).
 * Confidence: medium. */
long FUN_00677674(long region, long level, long vaddr)
{
    if (region == 0) {
        FUN_00687654();
    } else {
        long *slot = (long *)(region + 0x38) + level * 3;
        if (slot < (long *)(region + 0x38) || (long *)(region + 0x98) < slot + 3 || slot + 3 < slot)
            SoftwareBreakpoint(0x5519, 0x6777a0);
        ulong idx = (ulong)(vaddr - slot[1]) >> (level * 0xb + 0xeU & 0x3f);
        if (idx < (ulong)slot[2]) {
            long phys = *slot + idx * 0x40;
            long st = FUN_0065be08(0x6feb70, 4, 0xb);
            if (region == *(long *)(st + 0xf8)) {
                long n = *(long *)(st + 0xe8);
                if (n != 0) {
                    ulong k = *(ulong *)(st + 0xf0);
                    long e = st + k * 0x10;
                    do {
                        long el = e + (k / 6) * -0x60;
                        if ((long *)(el + 0x88) < (long *)(st + 0x88) ||
                            (long *)(st + 0xe8) < (long *)(el + 0x98) ||
                            (long *)(el + 0x98) < (long *)(el + 0x88))
                            SoftwareBreakpoint(0x5519, 0x6777a0);
                        if (*(long *)(el + 0x90) == phys)
                            return *(long *)(e + (k / 6) * -0x60 + 0x88);
                        e = e + 0x10;
                        k = k + 1;
                        n = n - 1;
                    } while (n != 0);
                }
            }
            return phys;
        }
    }
    FUN_006833d4(0x6af3f0);
}

/* FUN_006777d8 @ 0x6777d8
 * Ghidra: ulong FUN_006777d8(long param_1, ulong param_2)
 * Unmap a single page from a region: dispatch to the region's unmap helper,
 * following the deferred-unmap queue when a level must be torn down.
 * Returns nonzero on success. Confidence: low. */
ulong FUN_006777d8(long region, ulong vaddr)
{
    long cookie = _DAT_006b5ed0;
    if (region == 0) {
        FUN_006876a4();
        return 0;
    }
    cL4_w16_t st = (cL4_w16_t)FUN_0065be08(0x6feb70, 4, 0xb);
    if (region == *(long *)(st.lo + 0xf8)) {
        cL4_w16_t r = (cL4_w16_t)FUN_00677a88(vaddr, 0);
        vaddr = r.hi;
        return r.lo != 0;
    }
    if (*(char *)(region + 0x98) == 2) {
        return 0;
    }
    CallSupervisor(1);
    if (vaddr != 5) {
        if ((vaddr & 0xfb) != 0) {
            cL4_w16_t r = (cL4_w16_t)FUN_0068767c(vaddr, (ulong)0);
            ulong phys = r.hi;
            ulong *slot = r.lo;
            ulong arg3 = 0x40;
            long st2 = FUN_0065be08(0x6feb70, 4, 0xb);
            if (slot == *(ulong **)(st2 + 0xf8))
                FUN_006833d4(0x6affaa);
            long clip = phys - slot[2];
            if (phys < (ulong)slot[2])
                FUN_006833d4(0x6b00b9);
            ulong *lk = slot + 0x14;
            if (lk <= slot + 0x16) {
                if (FUN_0067cffc(lk) != 0)
                    FUN_006833d4(0x6a8797);
                unsigned char rc = (**(unsigned char (**)(void))(slot[1] + 0x20))
                                    (*slot, &clip, &arg3);
                if (FUN_0067d02c(lk) != 0)
                    FUN_006833d4(0x6a8797);
                if (rc == 0)
                    return phys;
                if ((ulong)rc * 8 + 0x6b5e50 - 1 < (ulong)0x6b5e50 ||
                    (unsigned long *)0x6b5e58 + rc * 8 > (unsigned long *)0x6b5e90)
                    FUN_006833d4(0x6b0117);
            }
            SoftwareBreakpoint(0x5519, 0x677a88);
        }
        FUN_006778bc(region, vaddr);
        vaddr = 1;
    }
    return 1;
}

/* FUN_006778bc @ 0x6778bc
 * Ghidra: ulong FUN_006778bc(undefined8 *param_1, ulong param_2)
 * Unmap the exact frame at param_2 through the object's methods, returning
 * the (possibly adjusted) frame address. Confidence: low. */
ulong FUN_006778bc(ulong *obj, ulong vaddr)
{
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if (obj == *(ulong **)(st + 0xf8))
        FUN_006833d4(0x6affaa);
    ulong arg2 = 0x40;
    long clip = vaddr - obj[2];
    if (vaddr < (ulong)obj[2])
        FUN_006833d4(0x6b00b9);
    ulong *lk = obj + 0x14;
    if (lk <= obj + 0x16) {
        if (FUN_0067cffc(lk) != 0)
            FUN_006833d4(0x6a8797);
        unsigned char rc = (**(unsigned char (**)(void))(obj[1] + 0x20))
                            (*obj, &clip, &arg2);
        if (FUN_0067d02c(lk) != 0)
            FUN_006833d4(0x6a8797);
        if (rc == 0)
            return vaddr;
        if ((ulong)rc * 8 + 0x6b5e50 - 1 < (ulong)0x6b5e50 ||
            (unsigned long *)0x6b5e58 + rc * 8 > (unsigned long *)0x6b5e90)
            FUN_006833d4(0x6b0117);
    }
    SoftwareBreakpoint(0x5519, 0x677a88);
}

/* FUN_00677a88 @ 0x677a88
 * Ghidra: ulong FUN_00677a88(ulong param_1, ulong param_2)
 * Region unmap core: walk the region's levels, following the deferred-unmap
 * ring buffer for pages whose level must be released, and invoke the
 * region's unmapping callback per page. Returns 0 on success.
 * Confidence: low (large, hot unmapping path). */
ulong FUN_00677a88(ulong vaddr, ulong level)
{
    long cookie = _DAT_006b5ed0;
    ulong st = FUN_0065be08(0x6feb70, 4, 0xb);
    ulong ints = FUN_00655e7c();
    if ((ints & 1) == 0) {
        if (st + 0x110 < st || st + 0x30 < st) goto trap;
        ints = FUN_0066a988(st);
        if ((ints & 1) == 0)
            FUN_00678a40();
    }
    if (st + 0x110 < st || st + 0x30 < st) goto trap;
    cL4_w16_t s = (cL4_w16_t)FUN_0066a9bc(st);
    ulong flags = s.lo;
    long region = *(long *)(st + 0xf8);
    long lvl = (long)level + 1;
    ulong mask = -1L << ((unsigned long)level * -3 + (unsigned long)lvl * 0xe & 0x3f);
    ulong target = mask & vaddr;
    ulong rc = FUN_00677674(region, level, target);
    CallSupervisor(1);
    ulong result = rc;
    if (rc == 5) {
        /* ring-buffer drain of deferred unmaps */
        ulong cur = result;
        if ((flags & 1) != 0) goto out3;
loop_drain:
        {
            ulong st2 = FUN_0065be08(0x6feb70, 4, 0xb);
            if (st2 + 0x30 < st2) goto trap;
            cur = FUN_0066a988();
            if ((cur & 1) == 0) {
                if (st2 <= st2 + 0x110)
                    FUN_006833d4(0x6afe41);
                goto trap;
            }
            ulong *head = (ulong *)(st2 + 0xe8);
            if (*head == 0) goto out3;
            bool drained = true;
            long rgn = *(long *)(st2 + 0xf8);
            do {
                ulong *slot = (ulong *)(st2 + 0x88) + *(long *)(st2 + 0xf0) * 2;
                if (slot < (ulong *)(st2 + 0x88) || head < slot + 2 || slot + 2 < slot)
                    goto trap;
                ulong tag = *slot, arg = slot[1];
                CallSupervisor(1);
                if ((tag & 0xff) == 5) {
                    long lr = FUN_00677a88(arg, 0);
                    if (lr != 0) {
                        CallSupervisor(1);
                        goto drain_next;
                    }
drain_free:
                    do { CallSupervisor(4); } while (tag == 1);
                    (**(void (**)(void))(*(long *)(rgn + 0xb8) + 0x10))
                        (*(ulong *)(rgn + 0xb0), arg);
                    FUN_0067d1f0(_DAT_006b4368, 0x6aff07);
                    FUN_0067d190(_DAT_006b4368);
                    drained = false;
                } else {
drain_next:
                    if (tag != 0) goto drain_free;
                }
                *(long *)(st2 + 0xe8) = *(long *)(st2 + 0xe8) + -1;
                *(ulong *)(st2 + 0xf0) = (*(long *)(st2 + 0xf0) + 1U) % 6;
                ulong *q = (ulong *)FUN_0065be08(0x6feb70, 4, 0xb);
                ulong *qslot = q + 6;
                if (qslot < q) goto trap;
                ulong qfl = FUN_0066a988();
                if ((qfl & 1) == 0) {
                    if (q <= q + 0x22) FUN_006833d4(0x6afe41);
                    goto trap;
                }
                ulong *dst = qslot + q[0xf];
                if (dst < qslot || q + 0xc < dst + 1 || dst + 1 < dst) goto trap;
                *dst = tag;
                q[0xf] = q[0xf] + 1;
            } while (*head != 0);
            if (drained) goto out3;
        }
    } else if ((rc & 0xfb) != 0) {
        FUN_0068767c(rc, (ulong)0);
        FUN_006833d4(0x6af999);
    } else {
        /* pop one frame from the deferred queue and invoke the unmap cb */
        ulong *q = (ulong *)FUN_0065be08(0x6feb70, 4, 0xb);
        ulong *qslot = q + 6;
        if (qslot < q) goto trap;
        ulong qfl = FUN_0066a988();
        if ((qfl & 1) == 0) {
            if (q <= q + 0x22) FUN_006833d4(0x6afe41);
            goto trap;
        }
        if (q[0xf] == 0) {
            FUN_00687758();
            goto loop_drain;
        }
        ulong n = q[0xf] - 1;
        q[0xf] = n;
        if (n < *(unsigned char *)((long)q + 0x101))
            *(char *)((long)q + 0x101) = (char)n;
        ulong *ent = qslot + n;
        if (ent < qslot) goto trap;
        if (q + 0xc < ent + 1 || ent + 1 < ent) goto trap;
        do { CallSupervisor(4); } while (*ent == 1);
        ent = qslot + q[0xf];
        if (ent < qslot || q + 0xc < ent + 1 || ent + 1 < ent) goto trap;
        ulong tag = *ent;
        /* page-size byte for the region at this level */
        char k = *(char *)(region + 0x98);
        unsigned int ps;
        if (k == 2) ps = 0;
        else if (k == 1) {
            if (2 < level - 1) FUN_006833d4(0x6af952);
            ps = (unsigned int)*(unsigned char *)(FUN_0067747c() + 2);
        } else {
            if (k != 0) FUN_006833d4(0x6af999);
            ps = 0xc0d0e04 >> (ulong)(((unsigned int)level & 3) << 3);
            if (3 < level) ps = 4;
        }
        long cb = (*(long (**)(void))**(ulong **)(region + 0xb8))
                    (*(ulong *)(region + 0xb0), ps & 0xff, rc, tag, 0);
        if (cb != 0) {
            ulong *q2 = (ulong *)FUN_0065be08(0x6feb70, 4, 0xb);
            ulong *qs2 = q2 + 6;
            if (qs2 < q2) goto trap;
            ulong f2 = FUN_0066a988();
            if ((f2 & 1) == 0) {
                if (q2 <= q2 + 0x22) FUN_006833d4(0x6afe41);
                goto trap;
            }
            ulong *dst2 = qs2 + q2[0xf];
            if (dst2 < qs2 || q2 + 0xc < dst2 + 1 || dst2 + 1 < dst2) goto trap;
            *dst2 = tag;
            q2[0xf] = q2[0xf] + 1;
            if (cb != 0x107) {
                FUN_006876cc(region, level, target, cb);
                result = 0;
            }
            goto out3;
        }
        /* try the next level down */
        ulong phys = FUN_00677674(region, lvl, target);
        ulong r2 = FUN_006786fc(region, phys, tag, target);
        if ((r2 & 0xff) == 4) {
            long lv2 = FUN_00677a88(target, lvl);
            if (lv2 != 0)
                r2 = FUN_006786fc(region, lv2, tag, target);
            else {
                (**(void (**)(void))(*(long *)(region + 0xb8) + 0x10))
                    (*(ulong *)(region + 0xb0), rc);
                ulong *q3 = (ulong *)FUN_0065be08(0x6feb70, 4, 0xb);
                ulong *qs3 = q3 + 6;
                if (qs3 < q3) goto trap;
                ulong f3 = FUN_0066a988();
                if ((f3 & 1) == 0) {
                    if (q3 <= q3 + 0x22) FUN_006833d4(0x6afe41);
                    goto trap;
                }
                ulong *dst3 = qs3 + q3[0xf];
                if (dst3 < qs3 || q3 + 0xc < dst3 + 1 || dst3 + 1 < dst3) goto trap;
                result = 0;
                *dst3 = tag;
                q3[0xf] = q3[0xf] + 1;
                goto out3;
            }
        }
        if (r2 != 0) {
            (**(void (**)(void))(*(long *)(region + 0xb8) + 0x10))
                (*(ulong *)(region + 0xb0), rc);
            ulong *q4 = (ulong *)FUN_0065be08(0x6feb70, 4, 0xb);
            ulong *qs4 = q4 + 6;
            if (qs4 < q4) goto trap;
            ulong f4 = FUN_0066a988();
            if ((f4 & 1) == 0) {
                if (q4 <= q4 + 0x22) FUN_006833d4(0x6afe41);
                goto trap;
            }
            ulong *dst4 = qs4 + q4[0xf];
            if (dst4 < qs4 || q4 + 0xc < dst4 + 1 || dst4 + 1 < dst4) goto trap;
            result = 0;
            *dst4 = tag;
            q4[0xf] = q4[0xf] + 1;
            goto out3;
        }
        /* record the successful unmap in the ring */
        ulong st3 = FUN_0065be08(0x6feb70, 4, 0xb);
        if (st3 + 0x30 < st3) goto trap;
        ulong f5 = FUN_0066a988();
        if ((f5 & 1) == 0) {
            if (st3 <= st3 + 0x110) FUN_006833d4(0x6afe41);
            goto trap;
        }
        ulong *ring = (ulong *)(st3 + 0xe8);
        ulong cnt = *ring;
        ulong *ringslot = (ulong *)(st3 + 0x88) + ((cnt + *(long *)(st3 + 0xf0)) % 6) * 2;
        if (ringslot < (ulong *)(st3 + 0x88) || ring < ringslot + 2 || ringslot + 2 < ringslot)
            goto trap;
        *ringslot = tag;
        ringslot[1] = rc;
        *ring = cnt + 1;
        if ((flags & 1) == 0) goto loop_drain;
out3:
        if (result != 0) goto out_final;
    }
    FUN_00687784(target, level);
    result = 0;
out_final:
    FUN_0066ab40(st, flags, s.hi);
    if (_DAT_006b5ed0 != cookie)
        FUN_0067f660();
    return result;
trap:
    SoftwareBreakpoint(0x5519, 0x6782b4);
}

/* FUN_006782b4 @ 0x6782b4
 * Ghidra: ulong FUN_006782b4(long, undefined8, ulong, ulong, ...)
 * Unmap a range of pages (or a whole region): for the root region dispatch
 * to FUN_00677a88; for a leaf object recurse via FUN_00678338. Returns
 * nonzero on success. Confidence: low. */
ulong FUN_006782b4(long region, ulong vaddr, ulong level, ulong unused,
                   ulong p5, ulong p6, ulong p7, ulong p8)
{
    if (region != 0) {
        long st = FUN_0065be08(0x6feb70, 4, 0xb);
        if (region == *(long *)(st + 0xf8)) {
            long r = FUN_00677a88(vaddr, 1);
            return r != 0;
        }
        FUN_00678338(region, vaddr, 1, unused, p5, p6, p7, p8);
        return 1;
    }
    cL4_w16_t r0 = (cL4_w16_t)FUN_006877ec();
    ulong v = r0.hi;
    long obj = r0.lo;
    long cookie = _DAT_006b5ed0;
    long st2 = FUN_0065be08(0x6feb70, 4, 0xb);
    if (obj == *(long *)(st2 + 0xf8))
        FUN_006833d4(0x6affaa);
    char k = *(char *)(obj + 0x98);
    ulong nlv;
    if (k == 0) nlv = 2;
    else if (k == 2) nlv = 3;
    else {
        if (k != 1) FUN_006833d4(0x6af267);
        ulong cfg = (ulong)*(unsigned char *)(FUN_0067747c() + 1) - 0xe;
        nlv = cfg / 0xb;
        if (cfg % 0xb != 0) nlv = nlv + 1;
    }
    if (level == nlv)
        FUN_006833d4(0x6b0007);
    long lvl = level + 1;
    ulong mask = -1L << ((unsigned long)level * -3 + (unsigned long)lvl * 0xe & 0x3f);
    ulong target = mask & v;
    ulong phys = FUN_00677674(obj, level);
    FUN_006778bc(obj, phys);
    CallSupervisor(1);
    if (phys != 5) {
        if ((phys & 0xfb) != 0) {
            cL4_w16_t r2 = (cL4_w16_t)FUN_0068767c(phys, (ulong)0);
            ulong res = r2.hi;
            char k2 = *(char *)(r2.lo + 0x98);
            if (k2 == 2) {
                return 4;
            }
            if (k2 == 1)
                return FUN_00656978(res, target, unused);
            if (k2 != 0) FUN_006833d4(0x6af267);
            ulong *tp = (ulong *)tpidrro_el0;
            tp[0] = target; tp[1] = unused; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0);
            tp[0] = target;
            return res;
        }
        ulong next = FUN_00677674(obj, lvl, mask & v);
        for (;;) {
            char k3 = *(char *)(obj + 0x98);
            unsigned int ps;
            if (k3 == 2) ps = 0;
            else if (k3 == 1) {
                if (2 < level - 1) FUN_006833d4(0x6af952);
                ps = (unsigned int)*(unsigned char *)(FUN_0067747c() + 2);
            } else {
                if (k3 != 0) FUN_006833d4(0x6af999);
                ps = 0xc0d0e04 >> (ulong)(((unsigned int)level & 3) << 3);
                if (3 < level) ps = 4;
            }
            ulong r = (*(ulong (**)(void))**(ulong **)(obj + 0xb8))
                        (*(ulong *)(obj + 0xb0), ps & 0xff, phys, phys,
                         *(unsigned int *)(obj + 0xc0));
            ulong g = _DAT_006b4368;
            if ((r & 0xff) != 0) {
                FUN_006774ac((ulong *)(ulong)0, (unsigned char)r);
                FUN_006874b4(g, 0x6af2cd, 0x593, 0x6aff92, 0x6b005e, p7, p8,
                             (ulong)0, r >> 8, (unsigned int)ps, phys,
                             *(unsigned int *)(obj + 0xc0), r);
                FUN_006833d4(0x6a71a1);
            }
            cL4_w16_t rr = (cL4_w16_t)FUN_006786fc(obj, next, phys, mask & v);
            if ((rr.lo & 0xff) != 4) goto done_lbl;
            if (*(char *)(obj + 0x98) != 1 || (*(unsigned int *)(obj + 0xc0) & 1) != 0)
                break;
            *(unsigned int *)(obj + 0xc0) |= 1;
            (**(void (**)(void))(*(long *)(obj + 0xb8) + 0x10))
                (*(ulong *)(obj + 0xb0), phys);
        }
        long l2 = FUN_00678338(obj, mask & v, lvl);
        if (l2 != 0) {
            FUN_006786fc(obj, l2, phys, mask & v);
done_lbl:
            return 0;
        }
        (**(void (**)(void))(*(long *)(obj + 0xb8) + 0x10))
            (*(ulong *)(obj + 0xb0), phys);
        return 0;
    }
    if (_DAT_006b5ed0 != cookie)
        FUN_0067f660();
    return 0;
}

/* FUN_00678338 @ 0x678338
 * Ghidra: ulong FUN_00678338(long, ulong, ulong, ulong, undefined8, ...)
 * Recursive region-unmap helper: translate, unmap one level, then walk to
 * the next level down. Confidence: low. */
ulong FUN_00678338(long obj, ulong vaddr, ulong level, ulong unused,
                   ulong p5, ulong p6, ulong p7, ulong p8)
{
    long cookie = _DAT_006b5ed0;
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if (obj == *(long *)(st + 0xf8))
        FUN_006833d4(0x6affaa);
    char k = *(char *)(obj + 0x98);
    ulong nlv;
    if (k == 0) nlv = 2;
    else if (k == 2) nlv = 3;
    else {
        if (k != 1) FUN_006833d4(0x6af267);
        ulong cfg = (ulong)*(unsigned char *)(FUN_0067747c() + 1) - 0xe;
        nlv = cfg / 0xb;
        if (cfg % 0xb != 0) nlv = nlv + 1;
    }
    if (level == nlv)
        FUN_006833d4(0x6b0007);
    long lvl = level + 1;
    ulong mask = -1L << ((unsigned long)level * -3 + (unsigned long)lvl * 0xe & 0x3f);
    ulong target = mask & vaddr;
    ulong phys = FUN_00677674(obj, level);
    FUN_006778bc(obj, phys);
    CallSupervisor(1);
    if (phys != 5) {
        if ((phys & 0xfb) != 0) {
            cL4_w16_t r2 = (cL4_w16_t)FUN_0068767c(phys, (ulong)0);
            ulong res = r2.hi;
            char k2 = *(char *)(r2.lo + 0x98);
            if (k2 == 2) return 4;
            if (k2 == 1) return FUN_00656978(res, target, unused);
            if (k2 != 0) FUN_006833d4(0x6af267);
            ulong *tp = (ulong *)tpidrro_el0;
            tp[0] = target; tp[1] = unused; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0);
            tp[0] = target;
            return res;
        }
        ulong next = FUN_00677674(obj, lvl, mask & vaddr);
        for (;;) {
            char k3 = *(char *)(obj + 0x98);
            unsigned int ps;
            if (k3 == 2) ps = 0;
            else if (k3 == 1) {
                if (2 < level - 1) FUN_006833d4(0x6af952);
                ps = (unsigned int)*(unsigned char *)(FUN_0067747c() + 2);
            } else {
                if (k3 != 0) FUN_006833d4(0x6af999);
                ps = 0xc0d0e04 >> (ulong)(((unsigned int)level & 3) << 3);
                if (3 < level) ps = 4;
            }
            ulong r = (*(ulong (**)(void))**(ulong **)(obj + 0xb8))
                        (*(ulong *)(obj + 0xb0), ps & 0xff, phys, phys,
                         *(unsigned int *)(obj + 0xc0));
            ulong g = _DAT_006b4368;
            if ((r & 0xff) != 0) {
                FUN_006774ac((ulong *)(ulong)0, (unsigned char)r);
                FUN_006874b4(g, 0x6af2cd, 0x593, 0x6aff92, 0x6b005e, p7, p8,
                             (ulong)0, r >> 8, (unsigned int)ps, phys,
                             *(unsigned int *)(obj + 0xc0), r);
                FUN_006833d4(0x6a71a1);
            }
            cL4_w16_t rr = (cL4_w16_t)FUN_006786fc(obj, next, phys, mask & vaddr);
            if ((rr.lo & 0xff) != 4) goto out_lbl;
            if (*(char *)(obj + 0x98) != 1 || (*(unsigned int *)(obj + 0xc0) & 1) != 0)
                break;
            *(unsigned int *)(obj + 0xc0) |= 1;
            (**(void (**)(void))(*(long *)(obj + 0xb8) + 0x10))
                (*(ulong *)(obj + 0xb0), phys);
        }
        long l2 = FUN_00678338(obj, mask & vaddr, lvl, unused, p5, p6, p7, p8);
        if (l2 != 0) {
            FUN_006786fc(obj, l2, phys, mask & vaddr);
out_lbl:
            return 0;
        }
        (**(void (**)(void))(*(long *)(obj + 0xb8) + 0x10))
            (*(ulong *)(obj + 0xb0), phys);
        return 0;
    }
    if (_DAT_006b5ed0 != cookie)
        FUN_0067f660();
    return 0;
}

/* FUN_006786fc @ 0x6786fc
 * Ghidra: undefined1 [16] FUN_006786fc(long, undefined8, undefined8, undefined8)
 * Invoke a memory operation: for a leaf/level-2 object return status 4; for
 * a Swift-level object re-dispatch; for the plain object, marshal the args
 * through tpidrro_el0 and SVC. Returns a 16-byte pair. Confidence: medium. */
cL4_w16_t FUN_006786fc(long obj, ulong a, ulong b, ulong c)
{
    char k = *(char *)(obj + 0x98);
    ulong r;
    cL4_w16_t out;
    if (k == 2) {
        r = 4;
    } else {
        if (k == 1)
            return (cL4_w16_t)FUN_00656978(a, b, c);
        if (k != 0)
            FUN_006833d4(0x6af267);
        ulong *tp = (ulong *)tpidrro_el0;
        tp[0] = b; tp[1] = c; tp[2] = 0; tp[3] = 0;
        CallSupervisor(0);
        tp[0] = b;
        r = a;
        a = 0;
    }
    out.hi = a;
    out.lo = r;
    return out;
}

/* FUN_006787a0 @ 0x6787a0
 * Ghidra: undefined1 [16] FUN_006787a0(long, ulong, undefined8, ...)
 * Invoke a memory operation with five marshalled words (or four for the
 * leaf/plain paths). Returns a 16-byte pair. Confidence: medium. */
cL4_w16_t FUN_006787a0(long obj, ulong a, ulong b, ulong c, ulong d, ulong e)
{
    char k = *(char *)(obj + 0x98);
    cL4_w16_t out;
    if (k == 2) {
        out.hi = a;
        out.lo = 4;
        return out;
    }
    if (k != 1) {
        if (k == 0) {
            ulong *tp = (ulong *)tpidrro_el0;
            tp[0] = b; tp[1] = c; tp[2] = d; tp[3] = e;
            CallSupervisor(0);
            tp[0] = b;
            out.hi = 0;
            out.lo = a;
            return out;
        }
        FUN_006833d4(0x6af4c8);
    }
    return (cL4_w16_t)FUN_00656924(a, b, c, (unsigned int)d & 1);
}

/* FUN_0067882c @ 0x67882c
 * Ghidra: undefined8 FUN_0067882c(undefined8, ulong, ulong, ulong)
 * Scan the object list for a mapping covering the given address range and
 * build the matching page-table entries for each cap object found.
 * Confidence: low. */
ulong FUN_0067882c(ulong out, ulong base, ulong len, ulong region)
{
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    ulong obj = *(ulong *)(st + 0xf8);
    if (obj == region) {
        base = base & 0xffffffffffffc000;
        ulong end = base + len;
        if (base < end && end <= obj + 0x30) {
            if (*(ulong *)(obj + 0x28) <= base && end < *(ulong *)(obj + 0x30)) {
                long round = 0;
                if ((end & 0x3fff) != 0) round = 0x4000;
                long *it = (long *)FUN_00654d4c();
                if (it != (long *)-1) {
                    do {
                        long n = *it;
                        if (n != 0) {
                            ulong *e = (ulong *)(it + 4);
                            do {
                                if (e != NULL && (e < it + 4 || it + 0x800 < e + 4 || e + 4 < e))
                                    SoftwareBreakpoint(0x5519, 0x6789f0);
                                char k = *(char *)(obj + 0x98);
                                if (k != 2) {
                                    ulong tag = *e;
                                    unsigned char bt = (unsigned char)(tag >> 0x38);
                                    if (k == 1) {
                                        if (tag >> 0x38 != 0x11 &&
                                            *(char *)(FUN_0067747c() + 2) != (char)bt)
                                            goto next;
                                        FUN_00687550();
                                    }
                                    if (k != 0) FUN_006833d4(0x6af267);
                                    if (bt == 0x04 || bt == 0x11) {
                                        ulong phys = e[2] * 0x1000 & 0xffffffffff000;
                                        if (base <= phys &&
                                            phys < round + (end & 0xffffffffffffc000)) {
                                            ulong t[4] = {0,0,0,0};
                                            FUN_0066bce0(t, out,
                                                (int)(e[2] * 0x1000 - *(long *)(obj + 0x28) >> 0xe) + 1,
                                                tag & 0xffffffffffffff);
                                            out = t[0];
                                        }
                                    }
                                }
next:
                                e = e + 4;
                                n = n - 1;
                            } while (n != 0);
                        }
                        it = (long *)it[1];
                    } while (it != (long *)-1);
                }
            }
        }
    }
    return out;
}

/* FUN_00678a40 @ 0x678a40
 * Ghidra: ulong FUN_00678a40(void)
 * Pop a frame from the region's free-slot pool, growing the pool if empty.
 * Returns 0 on success (frame via hidden x8), else the error. Confidence: low. */
ulong FUN_00678a40(void)
{
    ulong r = thunk_FUN_00660b28(0x1800);
    if ((r & 1) != 0)
        return r;
    FUN_00687814();
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if (*(long *)(st + 0x80) == 0) {
        FUN_006878a0();
    } else {
        long n = *(long *)(st + 0x80) - 1;
        *(long *)(st + 0x80) = n;
        ulong slot = st + 0x60 + n * 8;
        if (st + 0x60 <= slot && slot + 8 <= st + 0x78 && slot <= slot + 8) {
            if ((FUN_0068784c() & 1) == 0)
                return 0;
        }
    }
    SoftwareBreakpoint(0x5519, 0x678ae0);
}

/* FUN_00678a64 @ 0x678a64
 * Ghidra: undefined8 FUN_00678a64(void)
 * Pop a frame from the free-slot pool (result returned via x8). Confidence: low. */
ulong FUN_00678a64(void)
{
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if (*(long *)(st + 0x80) == 0) {
        FUN_006878a0();
    } else {
        long n = *(long *)(st + 0x80) - 1;
        *(long *)(st + 0x80) = n;
        ulong slot = st + 0x60 + n * 8;
        if (st + 0x60 <= slot && slot + 8 <= st + 0x78 && slot <= slot + 8) {
            if ((FUN_0068784c() & 1) == 0)
                return 0;
        }
    }
    SoftwareBreakpoint(0x5519, 0x678ae0);
}

/* FUN_00678ae0 @ 0x678ae0
 * Ghidra: void FUN_00678ae0(long, ulong, ulong, ulong, long)
 * Unmap a whole span of pages across every level of a region: clip the span
 * to the region bounds, then call the level-0 unmap (via callback or the
 * object's method table) and recurse into sub-levels. Confidence: low. */
void FUN_00678ae0(long region, ulong base, ulong len, ulong clip, long cb)
{
    long cookie = _DAT_006b5ed0;
    ulong end = base + len;
    if (base > end) {
        FUN_006833d4(0x6ac07f);                 /* overflow */
    }
    base = base & 0xffffffffffffc000;
    ulong rbase = *(ulong *)(region + 0x28);
    if (base < rbase)
        FUN_006833d4(0x6ac0f1);
    ulong rend = *(ulong *)(region + 0x30);
    if (rend < end)
        FUN_006833d4(0x6ac156);
    long round = 0;
    if ((end & 0x3fff) != 0) round = 0x4000;
    ulong endr = round + (end & 0xffffffffffffc000);
    ulong span = endr - base;
    ulong phys0 = FUN_00677674(region, 0, base);
    unsigned int u9 = (unsigned int)cb;
    if ((int)clip != 0 && span != 0) {
        ulong n = span >> 0xe;
        ulong owner = *(ulong *)(region + 0xb0);
        long vt = *(long *)(region + 0xb8);
        ulong cur = phys0;
        if (*(code **)(vt + 0x30) != 0) {
            ulong r = (**(ulong (**)(void))(vt + 0x30))(owner, cur, n);
            cur = 0;
            while ((r & 0xff) != 0) {
                FUN_006878cc(r, (ulong)0);
                n = n;
                cur = phys0;
                goto inner;
            }
        } else {
inner:
            while (1) {
                ulong r = (**(ulong (**)(void))(vt + 0x10))(owner, cur);
                u9 = (unsigned int)cb;
                n = n - 1;
                cur = cur + 0x40;
                if (r != 0x107 && r != 0) break;
                if (n == 0) goto done_loop;
            }
        }
    }
done_loop:
    if (cb == 0) {
        long r2 = 0;
        if ((phys0 & 0x3fff) != 0) r2 = 0x4000;
        if (r2 + (phys0 & 0xffffffffffffc000) < (phys0 + (span >> 8) & 0xffffffffffffc000))
            goto deeper;
    } else {
deeper:
        if (*(long *)(*(long *)(region + 0xb8) + 0x30) != 0) {
            ulong st = FUN_0065be08(0x6feb70, 4, 0xb);
            if (region == *(long *)(st + 0xf8)) {
                if (st + 0x110 < st) SoftwareBreakpoint(0x5519, 0x678ddc);
                if (FUN_0066a988(st) != 0) {
                    cL4_w16_t r3 = (cL4_w16_t)FUN_00687928();
                    ulong obj = r3.hi;
                    ulong *slots = r3.lo;
                    long stack_cookie = _DAT_006b5ed0;
                    ulong lv = 0xb;
                    ulong lof = 0;
                    ulong lob = 0;
                    ulong hof = span;
                    ulong hob = n;
                    ulong ob = phys0;
                    ulong lvl = lv;
                    if (clip != 0) {
                        FUN_00672e5c(clip, &lob, &lof);
                        if (obj < lob) FUN_006833d4(0x6b0160);
                        if (lof < lv) FUN_006833d4(0x6b0160);
                    }
                    bool first = true;
                    bool b15 = false;
                    long k = 0;
                    for (;;) {
                        bool iter = first;
                        if (lv <= obj || obj < lob || lof < lv)
                            FUN_006833d4(0x6b0287);
                        long *slot = slots + k * 3 + 7;
                        if (slots + 0x13 < slot + 3 || slot + 3 < slot) goto trap;
                        long sh = k * 0xb + 0xe;
                        ulong m = ~(-0x4000L << k * 0xb);
                        long sv = slot[1];
                        ulong a0 = (lob + m) - sv >> sh;
                        ulong a1 = lof - sv >> sh;
                        ulong a2 = (obj + m) - sv >> sh;
                        ulong a3 = lv - sv >> sh;
                        ulong a4 = obj - sv >> sh;
                        if (a2 <= a0) a4 = a2;
                        a2 = (lv + m) - sv >> sh;
                        if (a1 <= a3) a2 = a3;
                        if (a2 <= a4) break;
                        if (a4 < a0 || a1 < a2)
                            FUN_006833d4(0x6b0359);
                        if ((ulong)slot[2] < a1)
                            FUN_006833d4(0x6b0455);
                        long st2 = FUN_0065be08(0x6feb70, 4, 0xb);
                        if (slots == *(ulong **)(st2 + 0xf8) && *(long *)(st2 + 0xe8) != 0) {
                            FUN_00687960();
                            goto trap;
                        }
                        ulong lo = *slot + a0 * 0x40;
                        ulong hi = *slot + a1 * 0x40;
                        long rd = 0;
                        if ((lo & 0x3fff) != 0) rd = 0x4000;
                        ulong hiA = hi & 0xffffffffffffc000;
                        ulong loA = rd + (lo & 0xffffffffffffc000);
                        if (hiA <= loA) { loA = 0; hiA = 0; }
                        if (((u9 & 1) != 0 || b15) && lo < hi) {
                            long cnt = (a1 * 0x40 + a0 * -0x40) >> 6;
                            ulong owner = slots[0x16];
                            long vt = slots[0x17];
                            if (*(code **)(vt + 0x30) == 0) {
                                do {
                                    ulong r = (**(ulong (**)(void))(vt + 0x10))(owner, lo);
                                    cnt = cnt - 1;
                                    lo = lo + 0x40;
                                    if (r != 0x107 && r != 0) goto err_cb;
                                } while (cnt != 0);
                            } else {
                                ulong r = (**(ulong (**)(void))(vt + 0x30))(owner, lo, cnt);
err_cb:
                                if ((r & 0xff) != 0) {
                                    FUN_00687998(r, (ulong)0);
                                    goto trap;
                                }
                            }
                        }
                        if (loA != 0) {
                            long st3 = FUN_0065be08(0x6feb70, 4, 0xb);
                            if (slots == *(ulong **)(st3 + 0xf8)) {
                                if ((u9 & 1) == 0)
                                    FUN_00678e48(slots, loA, hiA, 0, 1);
                            } else {
                                long args[4];
                                args[0] = loA - slots[2];
                                args[1] = hiA - loA;
                                ulong r = (**(ulong (**)(void))(slots[1] + 0x30))
                                            (*slots, args, args + 1);
                                if ((r & 0xff) != 0) {
                                    if ((ulong)(r & 0xff) * 8 + 0x6b5e50 - 1 < (ulong)0x6b5e50 ||
                                        (unsigned long *)0x6b5e58 + (r & 0xff) * 8 >
                                            (unsigned long *)0x6b5e90)
                                        FUN_006833d4(0x6b0226);
trap:
                                    SoftwareBreakpoint(0x5519, 0x679238);
                                }
                            }
                        }
                        b15 = true;
                        k = 1;
                        first = false;
                        if (!iter) break;
                    }
                    if (_DAT_006b5ed0 == stack_cookie)
                        return;
                    FUN_0067f660();
                }
                ulong ints = FUN_00655e7c();
                if ((ints & 1) == 0)
                    FUN_00678a40();
                cL4_w16_t s2 = (cL4_w16_t)FUN_0066a9bc(st);
                FUN_00678e48(region, base, endr, cb, 0);
                if (_DAT_006b5ed0 == cookie) {
                    FUN_0066ab40(st, s2.lo, s2.hi);
                    return;
                }
                FUN_0067f660();
            }
            if (FUN_0067cffc(region + 0xa0) != 0)
                FUN_006833d4(0x6a8797);
            FUN_00678e48(region, base, endr, cb, 0);
            if (FUN_0067d02c(region + 0xa0) != 0)
                FUN_006833d4(0x6a8797);
        }
    }
    if (_DAT_006b5ed0 == cookie)
        return;
    FUN_0067f660();
}

/* FUN_00678e48 @ 0x678e48
 * Ghidra: void FUN_00678e48(undefined8 *, ulong, ulong, long, uint)
 * Unmap a span helper: walk levels, free the covered frames, and recurse
 * into the next sub-level. Confidence: low. */
void FUN_00678e48(ulong *slots, ulong lo, ulong hi, long clip, unsigned int flag)
{
    long cookie = _DAT_006b5ed0;
    ulong lob = hi, lof = lo;
    if (clip != 0) {
        FUN_00672e5c(clip, &lof, &lob);
        if (lo < lof) FUN_006833d4(0x6b0160);
        if (lob < hi) FUN_006833d4(0x6b0160);
    }
    bool first = true;
    long k = 0;
    bool b12 = false;
    for (;;) {
        bool iter = first;
        if (hi <= lo || lo < lof || lob < hi)
            FUN_006833d4(0x6b0287);
        long *slot = slots + k * 3 + 7;
        if (slots + 0x13 < slot + 3 || slot + 3 < slot) goto trap2;
        long sh = k * 0xb + 0xe;
        ulong m = ~(-0x4000L << k * 0xb);
        long sv = slot[1];
        ulong a0 = (lof + m) - sv >> sh;
        ulong a1 = lob - sv >> sh;
        ulong a2 = (lo + m) - sv >> sh;
        ulong a3 = hi - sv >> sh;
        ulong a4 = lo - sv >> sh;
        if (a2 <= a0) a4 = a2;
        a2 = (hi + m) - sv >> sh;
        if (a1 <= a3) a2 = a3;
        if (a2 <= a4) break;
        if (a4 < a0 || a1 < a2)
            FUN_006833d4(0x6b0359);
        if ((ulong)slot[2] < a1)
            FUN_006833d4(0x6b0455);
        long st = FUN_0065be08(0x6feb70, 4, 0xb);
        if (slots == *(ulong **)(st + 0xf8) && *(long *)(st + 0xe8) != 0) {
            FUN_00687960();
            goto trap2;
        }
        ulong lo2 = *slot + a0 * 0x40;
        ulong hi2 = *slot + a1 * 0x40;
        long rd = 0;
        if ((lo2 & 0x3fff) != 0) rd = 0x4000;
        ulong hiA = hi2 & 0xffffffffffffc000;
        ulong loA = rd + (lo2 & 0xffffffffffffc000);
        if (hiA <= loA) { loA = 0; hiA = 0; }
        if (((flag & 1) != 0 || b12) && lo2 < hi2) {
            long cnt = (a1 * 0x40 + a0 * -0x40) >> 6;
            ulong owner = slots[0x16];
            long vt = slots[0x17];
            if (*(code **)(vt + 0x30) == 0) {
                do {
                    ulong r = (**(ulong (**)(void))(vt + 0x10))(owner, lo2);
                    cnt = cnt - 1;
                    lo2 = lo2 + 0x40;
                    if (r != 0x107 && r != 0) goto err2;
                } while (cnt != 0);
            } else {
                ulong r = (**(ulong (**)(void))(vt + 0x30))(owner, lo2, cnt);
err2:
                if ((r & 0xff) != 0) {
                    FUN_00687998(r, (ulong)0);
                    goto trap2;
                }
            }
        }
        if (loA != 0) {
            long st2 = FUN_0065be08(0x6feb70, 4, 0xb);
            if (slots == *(ulong **)(st2 + 0xf8)) {
                if ((flag & 1) == 0)
                    FUN_00678e48(slots, loA, hiA, 0, 1);
            } else {
                long args[4];
                args[0] = loA - slots[2];
                args[1] = hiA - loA;
                ulong r = (**(ulong (**)(void))(slots[1] + 0x30))(*slots, args, args + 1);
                if ((r & 0xff) != 0) {
                    if ((ulong)(r & 0xff) * 8 + 0x6b5e50 - 1 < (ulong)0x6b5e50 ||
                        (unsigned long *)0x6b5e58 + (r & 0xff) * 8 > (unsigned long *)0x6b5e90)
                        FUN_006833d4(0x6b0226);
trap2:
                    SoftwareBreakpoint(0x5519, 0x679238);
                }
            }
        }
        b12 = true;
        k = 1;
        first = false;
        if (!iter) break;
    }
    if (_DAT_006b5ed0 == cookie)
        return;
    FUN_0067f660();
}

/* FUN_006792a4 @ 0x6792a4
 * Ghidra: void FUN_006792a4(void)
 * Assert the free-slot pool state: level count must be 6 and the deferred
 * queue empty; otherwise panic. Confidence: medium. */
void FUN_006792a4(void)
{
    long st = FUN_0065be08(0x6feb70, 4, 0xb);
    if (*(long *)(st + 0x78) != 6)
        FUN_006833d4(0x6afb9b);
    if (*(long *)(st + 0xe8) == 0)
        return;
    FUN_006833d4(0x6afc39);
}

/* ---- Panic / fatal-report helpers (0x679348-0x6793f4) ---- */

/* FUN_00679348 @ 0x679348
 * Ghidra: void FUN_00679348(void)
 * Report the current error code descriptor and return. Confidence: low. */
void FUN_00679348(void)
{
    FUN_006774ac((ulong *)(ulong)0x10, 0);
}

/* FUN_00679368 @ 0x679368
 * Ghidra: void FUN_00679368(void)
 * Fatal: report an error word (shifted by 8) via the panic formatter. Confidence: low. */
void FUN_00679368(void)
{
    ulong word = 0;                        /* unaff_x20 >> 8 */
    FUN_006874b4(word >> 8);
}

/* FUN_00679394 @ 0x679394
 * Ghidra: void FUN_00679394(void)
 * Fatal: panic with the "state mismatch" message (0x6afd4f). Confidence: low. */
void FUN_00679394(void)
{
    FUN_006833d4(0x6afd4f);
}

/* FUN_006793b0 @ 0x6793b0
 * Ghidra: void FUN_006793b0(undefined8 param_1)
 * Fatal: panic with the "bad argument" message carrying param_1. Confidence: low. */
void FUN_006793b0(ulong arg)
{
    (void)arg;
    FUN_006833d4(0x6af394);
}

/* FUN_006793c4 @ 0x6793c4
 * Ghidra: void FUN_006793c4(void)
 * Report the current error code descriptor. Confidence: low. */
void FUN_006793c4(void)
{
    FUN_006774ac((ulong *)(ulong)0, 0);
}

/* FUN_006793d0 @ 0x6793d0
 * Ghidra: void FUN_006793d0(void)
 * Fatal: panic with the "bad level" message (0x6af912). Confidence: low. */
void FUN_006793d0(void)
{
    FUN_006833d4(0x6af912);
}

/* FUN_006793e0 @ 0x6793e0
 * Ghidra: void FUN_006793e0(undefined8 param_1)
 * Fatal: panic with the "bad page" message carrying param_1. Confidence: low. */
void FUN_006793e0(ulong arg)
{
    (void)arg;
    FUN_006833d4(0x6af60f);
}

/* FUN_006793f4 @ 0x6793f4
 * Ghidra: void FUN_006793f4(undefined8, undefined8, long)
 * Iterate a collection via its enumerator callback and print each element
 * through the character writer. Confidence: low. */
void FUN_006793f4(ulong out, ulong cb2, long coll)
{
    typedef cL4_w16_t (*f16a)(ulong);
    typedef cL4_w16_t (*f16b)(ulong *);
    typedef ulong (*fbits)(ulong, ulong *);
    cL4_w16_t it = ((f16a)((*(code **)(coll + 0x28))))(cb2);
    for (;;) {
        if (it.lo == 0)
            return;
        cL4_w16_t el = ((f16b)it.hi)(&it);
        ulong val = 0;
        if (el.hi == 0)
            FUN_0065558c();
        ulong bits = ((fbits)(el.hi + 8))(el.lo, &val);
        bits &= 0xfffffffe;
        FUN_00656b98(val & 0xff);
        FUN_0067d1f0(out, 0x6b0578);
        FUN_0067d440(0x6b0598, out);
        if (bits != 0) {
            do {
                FUN_0067d1f0(out, 0x6b05a9);
                bool more = (bits & -bits) != bits;
                bits &= ~(bits & -bits);
                if (!more) break;
            } while (1);
        }
        FUN_0067d3f8(10, out);
    }
}
