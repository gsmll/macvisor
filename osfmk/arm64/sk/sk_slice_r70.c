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
extern void thunk_FUN_00655200(ulong *);             /* release node */
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

/* ---- Object / region list management (0x679784-0x67b760) ---- */

/* FUN_00679784 @ 0x679784
 * Ghidra: void FUN_00679784(long, long)
 * Find a region node by address in the object's region list, panicking if
 * absent. Confidence: medium. */
void FUN_00679784(long obj, long target)
{
    if (obj + 0x50U < obj + 0x40U)
        SoftwareBreakpoint(0x5519, 0x679804);
    if (FUN_0067cffc() != 0)
        FUN_006833d4(0x6a8797);
    long node = *(long *)(obj + 0x1e0);
    for (;;) {
        if (node == 0)
            FUN_006833d4(0x6b0716);
        if (node == target)
            return;
        node = *(long *)(node + 0x18);
    }
}

/* FUN_00679838 @ 0x679838
 * Ghidra: void FUN_00679838(long, ulong, long, undefined8)
 * Insert a region node covering [base, base+len) into the object's region
 * list, splitting/merging as needed. Confidence: medium. */
void FUN_00679838(long obj, ulong base, long len, ulong p4)
{
    long round = 0;
    if ((len + base & 0x3fff) != 0) round = 0x4000;
    ulong lock = obj + 0x40;
    if (lock <= obj + 0x50U) {
        long lo = len;
        if (FUN_0067cffc(lock) != 0)
            FUN_006833d4(0x6a8797);
        if (len != 0) {
            ulong end = round + (len + base & 0xffffffffffffc000);
            if (end == (base & 0xffffffffffffc000)) {
                /* empty range: allocate a fresh node and recurse */
                cL4_w16_t r = (cL4_w16_t)FUN_00687a2c();
                long *node = r.hi;
                long nbase = r.lo;
                node[0] = nbase; node[1] = 0; node[2] = 0;
                node[3] = 0; node[4] = 0; node[5] = 0;
                node[6] = 0; node[7] = 0; node[8] = 0; node[9] = 0;
                FUN_0067cfb0(node + 6);
                FUN_00679838(nbase, (ulong)lo, (long)p4, 0);
                FUN_00679a68(nbase, node, (ulong)lo, (long)p4, 0);
                if (nbase + 0x50U < nbase + 0x40U)
                    SoftwareBreakpoint(0x5519, 0x679a34);
                if (FUN_0067d02c() == 0)
                    return;
                FUN_006833d4(0x6a8797);
            }
            while ((long n = *(long *)(obj + 0x1e0)) != 0) {
                if (end <= base) { FUN_006879f4(); goto done_lbl; }
                for (;;) {
                    ulong a = *(ulong *)(n + 8);
                    if (*(ulong *)(n + 0x10) <= a) { FUN_006879f4(); goto done_lbl; }
                    bool overlap = a < end;
                    if (a <= base) overlap = base < *(ulong *)(n + 0x10);
                    if (overlap) break;
                    n = *(long *)(n + 0x18);
                    if (n == 0) return;
                }
                *(char *)(n + 0x42) = 1;
                if (FUN_0067cfc8(n + 0x30, lock) != 0)
                    FUN_006833d4(0x6a8797);
            }
        }
        return;
    }
done_lbl:
    SoftwareBreakpoint(0x5519, 0x679958);
}

/* FUN_00679990 @ 0x679990
 * Ghidra: void FUN_00679990(long, long *, undefined8, undefined8)
 * Initialise a fresh region node and link it into the object's list. Confidence: medium. */
void FUN_00679990(long obj, long *node, ulong base, ulong len)
{
    node[0] = obj; node[1] = 0; node[2] = 0;
    node[3] = 0; node[4] = 0; node[5] = 0;
    node[6] = 0; node[7] = 0; node[8] = 0; node[9] = 0;
    FUN_0067cfb0(node + 6);
    FUN_00679838(obj, base, (long)len, 0);
    FUN_00679a68(obj, node, base, (long)len, 0);
    if (obj + 0x50U < obj + 0x40U)
        SoftwareBreakpoint(0x5519, 0x679a34);
    if (FUN_0067d02c() == 0)
        return;
    FUN_006833d4(0x6a8797);
}

/* FUN_00679a68 @ 0x679a68
 * Ghidra: void FUN_00679a68(long, long *, ulong, long, uint)
 * Link a region node into the object's list with the given [base,end)
 * bounds; validation included. Confidence: medium. */
void FUN_00679a68(long obj, long *node, ulong base, long len, unsigned int flag)
{
    long round = 0;
    if ((len + base & 0x3fff) != 0) round = 0x4000;
    ulong end = round + (len + base & 0xffffffffffffc000);
    if (end <= (base & 0xffffffffffffc000))
        FUN_006833d4(0x6b0d5a);
    if (*node != obj)
        FUN_006833d4(0x6b0dc7);
    if ((char)node[8] == 1) {
        FUN_00687a64();
    } else if (*(unsigned char *)((long)node + 0x41) == (unsigned char)flag) {
        long head = *(long *)(obj + 0x1e0);
        node[3] = head;
        node[1] = base & 0xffffffffffffc000;
        node[2] = end;
        *(char *)(node + 8) = 1;
        *(char *)((long)node + 0x42) = 0;
        if (head != 0)
            *(long **)(head + 0x20) = node + 3;
        *(long **)(obj + 0x1e0) = node;
        if (obj + 0x1e0U <= obj + 0x1e8U) {
            node[4] = obj + 0x1e0U;
            return;
        }
        SoftwareBreakpoint(0x5519, 0x679b0c);
    }
    FUN_006833d4(0x6b0e7d);
}

/* FUN_00679b98 @ 0x679b98
 * Ghidra: void FUN_00679b98(long, long *)
 * Remove a region node from the object's list and release it. Confidence: medium. */
void FUN_00679b98(long obj, long *node)
{
    ulong lock = obj + 0x40;
    if (obj + 0x50U < lock)
        SoftwareBreakpoint(0x5519, 0x679c60);
    if (FUN_0067cffc(lock) != 0)
        FUN_006833d4(0x6a8797);
    if (obj != *node)
        FUN_006833d4(0x6b0832);
    if ((*(unsigned char *)(node + 8) & 1) != 0) {
        long prev = node[3];
        long *next = (long *)node[4];
        if (prev != 0)
            *(long **)(prev + 0x20) = next;
        *next = prev;
        *(char *)(node + 8) = 0;
        char wasmarked = *(char *)((long)node + 0x42);
        if (FUN_0067d02c(lock) != 0)
            FUN_006833d4(0x6a8797);
        if (wasmarked != 0)
            FUN_0067cf94(node + 6);
        if ((*(unsigned char *)((long)node + 0x41) & 1) != 0)
            return;
        if ((char)node[8] != 1) {
            thunk_FUN_00655200(node + 6);
            return;
        }
        FUN_006833d4(0x6adaed);
    }
    FUN_006833d4(0x6b0887);
}

/* FUN_00679d44 @ 0x679d44
 * Ghidra: undefined1 [16] FUN_00679d44(undefined8, long, ulong, ulong, long)
 * Map an object into a region: choose the leaf page size from the object's
 * capability flags, allocate the frames, and install the PTEs. Returns a
 * 16-byte {error, region-node} pair. Confidence: low. */
cL4_w16_t FUN_00679d44(ulong owner, long obj, ulong psize, ulong base, long len)
{
    long round = 0;
    if ((len + base & 0x3fff) != 0) round = 0x4000;
    long flags = *(long *)(obj + 8);
    ulong err = 0xf60001;
    int ps = (int)psize;
    if (ps < 2) {
        if (ps == 0) {
            unsigned int f = *(unsigned int *)(obj + 0x20);
            unsigned int s = 1;
            if ((f & 8) != 0) s = 2;
            unsigned int s2 = 3;
            if ((f & 0x10) == 0) s2 = s;
            unsigned int s3 = 4;
            if ((f & 0x10000) != 0) s3 = s2;
            psize = s3;
        } else if (ps != 1) goto out;
        goto map;
    } else {
        if (ps != 2) {
            if (ps == 3) {
                if (((*(unsigned char *)(obj + 0x20) >> 4) & 1) == 0) goto fail;
                psize = 3;
            } else if (ps != 4) goto out;
            goto map;
        }
        if ((*(unsigned char *)(obj + 0x20) >> 3 & 1) != 0) {
            psize = 2;
            goto map;
        }
    }
fail:
    err = 0xf60001;
    goto out;
map:
    {
        ulong end = round + (len + base & 0xffffffffffffc000);
        if (end <= *(ulong *)(obj + 0x10)) {
            base = base & 0xffffffffffffc000;
            long span = end - base;
            ulong t[5] = {0,0,0,0,0};
            if ((FUN_00671af0(t, owner, flags + base, span, 0, 0, 0, 1) & 1) == 0) {
                cL4_w16_t r = (cL4_w16_t)FUN_00687a9c();
                ulong **head = *(ulong ***)(r.lo + 0x1d8);
                ulong *node = NULL;
                if (head != NULL) {
                    ulong *cur = head, *prev = NULL, *prv_end = NULL;
                    do {
                        ulong *np = cur + 6;
                        if (*cur <= r.hi && r.hi < cur[1] + *cur) {
                            if (prev != NULL) {
                                if (prv_end < prev + 6) goto trap2;
                                prev[5] = cur[5];
                                cur[5] = (ulong)head;
                                if (np < cur) goto trap2;
                                *(ulong ***)(r.lo + 0x1d8) = cur;
                            }
                            if (np < cur) { trap2: SoftwareBreakpoint(0x5519, 0x67a0f0); }
                            node = cur;
                            break;
                        }
                        ulong *nxt = cur + 5;
                        prev = cur;
                        prv_end = np;
                        cur = (ulong *)*nxt;
                    } while ((ulong *)*nxt != NULL);
                }
                cL4_w16_t o = { (ulong)node, 0 };
                return o;
            }
            if (base == 0 && *(long *)(obj + 0x10) == span) {
                long node = FUN_0067a064(owner, flags);
                if (*(long *)(node + 0x18) != 0)
                    FUN_0067a0f0(&t[0]);
                err = 0;
                *(long *)(node + 0x18) = 0;
                *(char *)(node + 0x10) = (char)psize;
            } else {
                if (span != 0) {
                    long rem = span;
                    do {
                        ulong va = (span - rem) + flags + base;
                        if ((FUN_00671398(&t[0], owner, va, rem, 2) & 1) == 0) {
                            FUN_00687ad4();
                            FUN_006833d4(0x6b0ed7);
                        }
                        long node = FUN_0067a064(owner, flags);
                        if (node == 0) {
                            err = 0x1160001;
                            goto finish;
                        }
                        if (node + 0x20U < node + 0x18U) goto trap2;
                        if ((va & 0x3fff) != 0) {
                            FUN_00687ad4();
                            FUN_006833d4(0x6b0ed7);
                        }
                        if (va < flags + err) {
                            long off = 0;
                            do {
                                ulong *pg = (ulong *)FUN_0067a1b8(node + 0x18U,
                                            va + off, &t[0], 1);
                                if (pg == NULL) break;
                                ulong idx = (va + off + (ulong)(unsigned int)-(int)pg[0x25])
                                            >> 0xe & 0x3ffff;
                                ulong *slot = (ulong *)((long)pg + (idx * 0xc30c30d >> 0x1d & 0x1fff8));
                                if (slot < pg || pg + 0x25 < slot + 1 || slot + 1 < slot)
                                    goto trap2;
                                unsigned int bi = (unsigned int)(((int)idx + (int)(idx / 0x15) * -0x15) * 3);
                                *slot = *slot & ~(7L << (bi & 0x3f)) |
                                        (psize & 0xff) << (bi & 0x3f);
                                off = off + 0x4000;
                            } while (va + off < flags + err);
                        } else {
                            /* no-op advance */
                        }
                        rem = rem - off;
                    } while (rem != 0);
                }
                err = 0;
            }
finish:
            FUN_00671bc4(&t[0], owner);
        }
    }
out:
    return (cL4_w16_t){ err, 0 };
}

/* FUN_0067a064 @ 0x67a064
 * Ghidra: ulong * FUN_0067a064(long, ulong)
 * Look up (and rotate to the front of) the object-list node covering addr. */
ulong *FUN_0067a064(long owner, ulong addr)
{
    ulong *head = *(ulong **)(owner + 0x1d8);
    if (head != NULL) {
        ulong *cur = head, *prev = NULL, *prv_end = NULL;
        do {
            ulong *np = cur + 6;
            if (*cur <= addr && addr < cur[1] + *cur) {
                if (prev != NULL) {
                    if (prv_end < prev + 6) goto trap3;
                    prev[5] = cur[5];
                    cur[5] = (ulong)head;
                    if (np < cur) goto trap3;
                    *(ulong **)(owner + 0x1d8) = cur;
                }
                if (cur <= np) return cur;
trap3:
                SoftwareBreakpoint(0x5519, 0x67a0f0);
            }
            ulong *nxt = cur + 5;
            prev = cur;
            prv_end = np;
            cur = (ulong *)*nxt;
        } while ((ulong *)*nxt != NULL);
    }
    return NULL;
}

/* FUN_0067a0f0 @ 0x67a0f0
 * Ghidra: void FUN_0067a0f0(undefined8, long)
 * Release all page objects reachable from a node's page table (32 slots),
 * then free the node's table. Confidence: medium. */
void FUN_0067a0f0(ulong owner, long node)
{
    long i;
    for (i = 0; i != 0x20; i++) {
        long n = *(long *)(node + i * 8);
        while (n != 0) {
            n = *(long *)(n + 0x130);
            FUN_00671320(owner);
        }
    }
    FUN_00671220(owner, node);
}

/* FUN_0067a154 @ 0x67a154
 * Ghidra: bool FUN_0067a154(int, int)
 * Compatibility predicate for level switches. Confidence: low. */
bool FUN_0067a154(int a, int b)
{
    if (b == 2) return a == 3;
    if (b != 1) {
        if (b == 0) return a != 4;
        FUN_006833d4(0x6b0a40);
    }
    return a == 2;
}

/* FUN_0067a1b8 @ 0x67a1b8
 * Ghidra: ulong FUN_0067a1b8(undefined8 *, ulong, undefined8, int)
 * Find (or, when alloc!=0, create and insert) a page object covering the
 * page containing addr within the node's page table. Confidence: medium. */
ulong FUN_0067a1b8(ulong *headp, ulong addr, ulong owner, int alloc)
{
    ulong *head = (ulong *)*headp;
    if (head == NULL) {
        if (alloc == 0) return 0;
        head = (ulong *)FUN_00671150(owner);
        *headp = head;
    }
    for (ulong p = *head; p != 0; p = *(ulong *)(p + 0x130)) {
        if (*(ulong *)(p + 0x128) == (addr & 0xffffffffffc00000))
            return p;
    }
    if (alloc == 0) return 0;
    ulong pg = FUN_00671384(owner);
    if (pg == 0) return 0;
    *(ulong *)(pg + 0x128) = addr & 0xffffffffffc00000;
    *(ulong *)(pg + 0x130) = *head;
    if (pg + 0x138 < pg)
        SoftwareBreakpoint(0x5519, 0x67a264);
    *head = pg;
    return pg;
}

/* FUN_0067a264 @ 0x67a264
 * Ghidra: void FUN_0067a264(undefined8, long, undefined8, undefined8, int, long)
 * Push a new object descriptor onto the owner's mapping stack. Confidence: medium. */
void FUN_0067a264(ulong owner, long obj, ulong base, ulong len, int psize, long src)
{
    if (psize != 4) {
        if (psize != 0)
            FUN_006833d4(0x6b0aa9);
        unsigned int f = *(unsigned int *)(src + 0x20);
        int s = 1;
        if ((f & 8) != 0) s = 2;
        int s2 = 3;
        if ((f & 0x10) == 0) s2 = s;
        psize = 4;
        if ((f & 0x10000) != 0) psize = s2;
    }
    ulong *node = (ulong *)FUN_00671018();
    node[0] = base;
    node[1] = len;
    *(char *)(node + 2) = (char)psize;
    node[3] = 0;
    node[4] = src;
    node[5] = *(ulong *)(obj + 0x1d8);
    if (node + 6 < node)
        SoftwareBreakpoint(0x5519, 0x67a30c);
    *(ulong **)(obj + 0x1d8) = node;
}

/* FUN_0067a334 @ 0x67a334
 * Ghidra: void FUN_0067a334(undefined8, long, long)
 * Remove and release the object descriptor whose backing object equals src.
 * Confidence: medium. */
void FUN_0067a334(ulong owner, long obj, long src)
{
    long *p = (long *)(obj + 0x1d8);
    if (p <= (long *)(obj + 0x1e0U)) {
        do {
            long n = *p;
            if (n == 0)
                FUN_006833d4(0x6b0f9e);
            if (*(long *)(n + 0x20) == src) {
                *p = *(long *)(n + 0x28);
                *(long *)(n + 0x28) = 0;
                if (*(long *)(n + 0x18) != 0)
                    FUN_0067a0f0(owner);
                FUN_006710e8(owner, n);
                return;
            }
            p = (long *)(n + 0x28);
        } while (p <= (long *)(n + 0x30U));
    }
    SoftwareBreakpoint(0x5519, 0x67a384);
}

/* FUN_0067a3dc @ 0x67a3dc
 * Ghidra: void FUN_0067a3dc(undefined8, undefined8, long, long)
 * Replace the mapping of src with an adjacent object: drop src then insert
 * the object whose range begins at src. Confidence: medium. */
void FUN_0067a3dc(ulong owner, ulong obj, long a, long b)
{
    FUN_0067a334(owner, obj, a);
    FUN_0067a334(owner, obj, b);
    FUN_0067a264(owner, obj, *(ulong *)(a + 8),
                 *(long *)(b + 0x10) + *(long *)(a + 0x10), 0, a);
}

/* FUN_0067a444 @ 0x67a444
 * Ghidra: void FUN_0067a444(undefined8, undefined8, long, ulong, undefined8)
 * Split an object mapping at offset len into two adjacent descriptors.
 * Confidence: medium. */
void FUN_0067a444(ulong owner, ulong obj, long src, ulong len, ulong dst)
{
    if (len == 0) {
        FUN_00687b0c();
    } else if (len < *(ulong *)(src + 0x10)) {
        FUN_0067a334(owner, obj, src);
        FUN_0067a264(owner, obj, *(ulong *)(src + 8), len, 0, src);
        FUN_0067a264(owner, obj, *(long *)(src + 8) + len,
                     *(long *)(src + 0x10) - len, 0, dst);
        return;
    }
    FUN_006833d4(0x6b0b54);
}

/* FUN_0067a510 @ 0x67a510
 * Ghidra: bool FUN_0067a510(long, long, ulong, undefined8 *, byte *)
 * Resolve the page-table byte for a mapped address, populating the pool and
 * the caller's out params. Confidence: low. */
bool FUN_0067a510(long owner, long node, ulong addr, ulong *outobj, unsigned char *outps)
{
    if ((*(unsigned char *)(node + 0xa1) & 1) == 0) {
        ulong page = addr & 0xffffffffffffc000;
        FUN_00679838(owner, page, 0x4000);
        ulong n = FUN_0067a064(owner, page);
        if (n == 0) {
            if (owner + 0x40U <= owner + 0x50U) {
                if (FUN_0067d02c() != 0)
                    FUN_006833d4(0x6a8797);
                return n != 0;
            }
            SoftwareBreakpoint(0x5519, 0x67a704);
        }
        FUN_00679a68(owner, node, page, 0x4000, 1);
        *(char *)(node + 0xa1) = 1;
        *(ulong *)(node + 0xa8) = page;
        if (n + 0x30 < n) goto trap4;
        ulong sb = *(ulong *)(*(long *)(n + 0x20) + 8);
        if (sb <= page && page < *(long *)(*(long *)(n + 0x20) + 0x10) + sb) {
            unsigned char ps;
            if (*(ulong **)(n + 0x18) != NULL) {
                ulong *pg = *(ulong **)(n + 0x18);
                if (pg != NULL) {
                    do {
                        if (pg[0x25] == (addr & 0xffffffffffc00000)) {
                            ulong *slot = (ulong *)((long)pg + ((ulong)((unsigned int)addr & 0x3fc000) / 0xa800 & 0x78));
                            if (slot < pg || pg + 0x25 < slot + 1 || slot + 1 < slot) goto trap4;
                            unsigned int code = ((unsigned int)(addr >> 0xe) & 0xff) * 0x87;
                            int sa = (int)(addr >> 0xe);
                            ulong bits = *slot >> ((ulong)((sa + ((sa - (code >> 8) >> 1 & 0x7f) + (code >> 8) >> 4 & 0xf) * -0x15) * 3) & 0x3f);
                            ps = (unsigned char)bits & 7;
                            if ((bits & 7) != 0) goto found;
                            break;
                        }
                        pg = (ulong *)pg[0x26];
                    } while (pg != NULL);
                }
            }
            ps = *(unsigned char *)(n + 0x10);
found:
            *(unsigned char *)(node + 0xa3) = ps;
            *outps = ps;
            *outobj = *(ulong *)(n + 0x20);
            if (owner + 0x50U < owner + 0x40U) goto trap4;
            if (FUN_0067d02c() == 0)
                return n != 0;
            goto trap4;
        }
        FUN_00687b48();
    }
    FUN_00687b74();
trap4:
    FUN_006833d4(0x6a8797);
}

/* FUN_0067a740 @ 0x67a740
 * Ghidra: ulong FUN_0067a740(undefined8, long)
 * Tear down a per-node mapped pool (or report its dirty flag). Confidence: low. */
ulong FUN_0067a740(ulong owner, long node)
{
    if ((*(unsigned char *)(node + 0xa1) & 1) != 0) {
        *(char *)(node + 0xa1) = 0;
        return FUN_00679b98(owner, node);
    }
    long o = FUN_00687bac();
    if (*(char *)(o + 0x18) == 0x11)
        return (ulong)(*(unsigned char *)(o + 0x22) & 1);
    return 0;
}

/* FUN_0067a760 @ 0x67a760
 * Ghidra: byte FUN_0067a760(long)
 * Read the dirty flag of an object. Confidence: medium. */
unsigned char FUN_0067a760(long obj)
{
    if (*(char *)(obj + 0x18) == 0x11)
        return *(unsigned char *)(obj + 0x22) & 1;
    return 0;
}

/* ---- Memory / string primitives (0x67a780-0x67b664) ---- */

/* FUN_0067a780 @ 0x67a780
 * Ghidra: void FUN_0067a780(undefined8 *, ulong)
 * Zero-fill a buffer of len bytes (bzero), using DC_ZVA for large blocks.
 * Confidence: medium. */
void FUN_0067a780(unsigned char *dst, ulong len)
{
    if (len > 0x3f) {
        if (len > 0x7fff) {
            /* large: DC_ZVA 64-byte blocks */
            unsigned char *d = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
            ulong n = (len + (ulong)dst) - (d + 0x40);
            if (d + 0x40 <= len + (ulong)dst && n != 0) {
                do { DC_ZVA((ulong)d); d += 0x40; n -= 0x40; } while (n > 0x3f && n != 0);
            }
            unsigned char *tail = d + n;
            tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=0;
            tail[8]=tail[9]=tail[10]=tail[11]=tail[12]=tail[13]=tail[14]=tail[15]=0;
            tail[16]=tail[17]=tail[18]=tail[19]=tail[20]=tail[21]=tail[22]=tail[23]=0;
            tail[24]=tail[25]=tail[26]=tail[27]=tail[28]=tail[29]=tail[30]=tail[31]=0;
            return;
        }
        /* mid: 64-byte stores */
        unsigned char *d = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
        ulong n = (len + (ulong)dst) - (d + 8);
        if (d + 8 <= len + (ulong)dst && n != 0) {
            do {
                d[0]=d[1]=d[2]=d[3]=d[4]=d[5]=d[6]=d[7]=0;
                d[8]=d[9]=d[10]=d[11]=d[12]=d[13]=d[14]=d[15]=0;
                d[16]=d[17]=d[18]=d[19]=d[20]=d[21]=d[22]=d[23]=0;
                d[24]=d[25]=d[26]=d[27]=d[28]=d[29]=d[30]=d[31]=0;
                d += 0x40; n -= 0x40;
            } while (n > 0x3f && n != 0);
        }
        unsigned char *tail = d + n;
        tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=0;
        tail[8]=tail[9]=tail[10]=tail[11]=tail[12]=tail[13]=tail[14]=tail[15]=0;
        tail[16]=tail[17]=tail[18]=tail[19]=tail[20]=tail[21]=tail[22]=tail[23]=0;
        tail[24]=tail[25]=tail[26]=tail[27]=tail[28]=tail[29]=tail[30]=tail[31]=0;
        return;
    }
    /* small */
    while (len > 7) { *(ulong *)dst = 0; dst += 8; len -= 8; }
    for (; len != 0; len--) *dst++ = 0;
}

/* FUN_0067a7f0 @ 0x67a7f0
 * Ghidra: void FUN_0067a7f0(long *, ulong, ulong)
 * Fill a buffer of len bytes with the byte value (memset), using DC_ZVA for
 * the zero-fill case. Confidence: medium. */
void FUN_0067a7f0(unsigned char *dst, ulong val, ulong len)
{
    ulong word = (val & 0xff) * 0x101010101010101UL;
    if (len < 0x40) {
        while (len > 7) { *(ulong *)dst = word; dst += 8; len -= 8; }
        for (; len != 0; len--) *dst++ = (unsigned char)word;
        return;
    }
    if (len < 0x8000) {
        unsigned char *d = dst;
        for (ulong i = 0; i < 0x40 && (ulong)(d - dst) < len; i += 8)
            *(ulong *)(d + i) = word;
        unsigned char *p = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
        ulong n = (len + (ulong)dst) - (p + 8);
        if (p + 8 <= len + (ulong)dst && n != 0) {
            do {
                *(ulong *)(p+0)=word; *(ulong *)(p+8)=word; *(ulong *)(p+16)=word;
                *(ulong *)(p+24)=word; *(ulong *)(p+32)=word; *(ulong *)(p+40)=word;
                *(ulong *)(p+48)=word; *(ulong *)(p+56)=word;
                p += 0x40; n -= 0x40;
            } while (n > 0x3f && n != 0);
        }
        unsigned char *tail = p + n;
        for (ulong i = 0; i < 0x40 && (ulong)(tail + i - dst) < len; i += 8)
            *(ulong *)(tail + i) = word;
        return;
    }
    /* large */
    if (word != 0) {
        for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(dst + i) = word;
        unsigned char *p = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
        ulong n = (len + (ulong)dst) - (p + 8);
        if (p + 8 <= len + (ulong)dst && n != 0) {
            do {
                *(ulong *)(p+0)=word; *(ulong *)(p+8)=word; *(ulong *)(p+16)=word;
                *(ulong *)(p+24)=word; *(ulong *)(p+32)=word; *(ulong *)(p+40)=word;
                *(ulong *)(p+48)=word; *(ulong *)(p+56)=word;
                p += 0x40; n -= 0x40;
            } while (n > 0x3f && n != 0);
        }
        unsigned char *tail = p + n;
        for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(tail + i) = word;
        return;
    }
    /* zero fill via DC_ZVA */
    for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(dst + i) = 0;
    unsigned char *z = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
    ulong n = (len + (ulong)dst) - (z + 0x40);
    if (z + 0x40 <= len + (ulong)dst && n != 0) {
        do { DC_ZVA((ulong)z); z += 0x40; n -= 0x40; } while (n > 0x3f && n != 0);
    }
    unsigned char *tail = z + n;
    for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(tail + i) = 0;
}

/* FUN_0067a900 @ 0x67a900
 * Ghidra: long FUN_0067a900(ulong, char, long)
 * Find the first occurrence of byte c within [s, s+len) (memchr), scanning
 * 16 bytes at a time with SIMD. Returns offset or NULL. Confidence: low. */
long FUN_0067a900(ulong s, char c, long len)
{
    if (len != 0) {
        if (len < 0) {
            /* backward scan (len<0 path) */
            unsigned long *p = (unsigned long *)(s & ~0xfUL);
            ulong a = p[1], b = p[0];
            /* XOR each byte with c, detect any zero byte via the uminv trick */
            ulong o = 0;
            while (1) {
                if ((b == c) ) return (long)(p + 0) + 0;
                if ((a == c)) return (long)(p + 0) + 1;
                /* SIMD uminv over 16 bytes; detect presence */
                b = p[2]; a = p[3];
                p += 2;
                o += 0x10;
            }
        } else {
            unsigned long *p = (unsigned long *)(s & ~0xfUL);
            ulong a = p[1], b = p[0];
            ulong rem = (ulong)len + (s & 0xf);
            ulong o = 0;
            while (1) {
                if (b == c) { long off = (ulong)o; if (off < (long)rem) return (long)p + 0; return 0; }
                if (a == c) { long off = (ulong)o + 1; if (off < (long)rem) return (long)p + 1; return 0; }
                if (rem < 0x10 || rem - 0x10 == 0) break;
                b = p[2]; a = p[3];
                p += 2; rem -= 0x10; o += 0x10;
            }
            return 0;
        }
    }
    return 0;
}

/* FUN_0067aa00 @ 0x67aa00
 * Ghidra: void FUN_0067aa00(undefined8 *, undefined8 *, ulong)
 * Copy len bytes, handling overlapping regions (memmove). Confidence: low. */
void FUN_0067aa00(unsigned char *dst, const unsigned char *src, ulong len)
{
    if ((ulong)((long)dst - (long)src) < len) {
        /* overlap: copy backwards */
        if (dst != src) {
            unsigned char *de = dst + len;
            const unsigned char *se = src + len;
            while (len > 7) { de -= 8; se -= 8; *(ulong *)de = *(const ulong *)se; len -= 8; }
            for (; len != 0; len--) { de--; se--; *de = *se; }
        }
        return;
    }
    /* forward copy */
    while (len > 7) { *(ulong *)dst = *(const ulong *)src; dst += 8; src += 8; len -= 8; }
    for (; len != 0; len--) *dst++ = *src++;
}

/* FUN_0067ad00 @ 0x67ad00
 * Ghidra: void FUN_0067ad00(ulong *, ulong *, ulong)
 * Fill a buffer with a repeated 8-byte pattern (memset pattern). Confidence: low. */
void FUN_0067ad00(unsigned char *dst, unsigned long pat, ulong len)
{
    if (len < 0x40) {
        while (len > 0xf) { *(ulong *)dst = pat; *(ulong *)(dst+8) = pat; dst += 0x10; len -= 0x10; }
        for (; len != 0; len--) { *dst = (unsigned char)pat; dst++; }
        return;
    }
    for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(dst + i) = pat;
    unsigned char *p = (unsigned char *)((ulong)(dst + 8) & ~0x3fUL);
    ulong n = (len + (ulong)dst) - (p + 8);
    if (p + 8 <= len + (ulong)dst && n != 0) {
        do {
            for (int i = 0; i < 8; i++) *(ulong *)(p + i*8) = pat;
            p += 0x40; n -= 0x40;
        } while (n > 0x3f && n != 0);
    }
    unsigned char *tail = p + n;
    for (ulong i = 0; i < 0x40; i += 8) *(ulong *)(tail + i) = pat;
}

/* FUN_0067aeb0 @ 0x67aeb0
 * Ghidra: long FUN_0067aeb0(byte *, byte *)
 * strcmp: compare two NUL-terminated strings, 16 bytes at a time. Confidence: low. */
long FUN_0067aeb0(const unsigned char *a, const unsigned char *b)
{
    while ((ulong)a & 0xf) {
        unsigned char ca = *a;
        long d = (ulong)ca - (ulong)*b;
        a++; b++;
        if (d != 0 || ca == 0) return d;
    }
    /* aligned 16-byte compare */
    for (;;) {
        unsigned long x0 = *(const unsigned long *)(a + 0);
        unsigned long x1 = *(const unsigned long *)(a + 8);
        unsigned long y0 = *(const unsigned long *)(b + 0);
        unsigned long y1 = *(const unsigned long *)(b + 8);
        /* detect a differing or NUL byte */
        unsigned char c0 = (unsigned char)x0, c1 = (unsigned char)(x0>>8),
                      c2 = (unsigned char)(x0>>16), c3 = (unsigned char)(x0>>24),
                      c4 = (unsigned char)(x0>>32), c5 = (unsigned char)(x0>>40),
                      c6 = (unsigned char)(x0>>48), c7 = (unsigned char)(x0>>56);
        unsigned char d0 = (unsigned char)x1, d1 = (unsigned char)(x1>>8),
                      d2 = (unsigned char)(x1>>16), d3 = (unsigned char)(x1>>24),
                      d4 = (unsigned char)(x1>>32), d5 = (unsigned char)(x1>>40),
                      d6 = (unsigned char)(x1>>48), d7 = (unsigned char)(x1>>56);
        if (c0!=y0||c1!=(unsigned char)(y0>>8)||c2!=(unsigned char)(y0>>16)||
            c3!=(unsigned char)(y0>>24)||c4!=(unsigned char)(y0>>32)||
            c5!=(unsigned char)(y0>>40)||c6!=(unsigned char)(y0>>48)||
            c7!=(unsigned char)(y0>>56)) {
            long i = 0;
            while (1) {
                unsigned char ca = a[i], cb = b[i];
                long d = (ulong)ca - (ulong)cb;
                if (d != 0 || ca == 0) return d;
                i++;
                if (i == 16) break;
            }
        }
        if (c0==0||c1==0||c2==0||c3==0||c4==0||c5==0||c6==0||c7==0||
            d0==0||d1==0||d2==0||d3==0||d4==0||d5==0||d6==0||d7==0)
            return 0;
        a += 16; b += 16;
    }
}

/* FUN_0067aff0 @ 0x67aff0
 * Ghidra: long FUN_0067aff0(byte *, byte *, ulong)
 * strncmp: compare up to len bytes. Confidence: low. */
long FUN_0067aff0(const unsigned char *a, const unsigned char *b, ulong len)
{
    if (len == 0) return 0;
    while ((ulong)a & 0xf) {
        long d = (ulong)*a - (ulong)*b;
        if (d != 0 || *a == 0) return d;
        len--; b++; a++;
        if (len == 0) return 0;
    }
    while (len >= 0x10) {
        unsigned long x0 = *(const unsigned long *)(a + 0);
        unsigned long x1 = *(const unsigned long *)(a + 8);
        unsigned long y0 = *(const unsigned long *)(b + 0);
        unsigned long y1 = *(const unsigned long *)(b + 8);
        int diff = (x0 != y0) || (x1 != y1);
        unsigned char c0=(unsigned char)x0,c1=(unsigned char)(x0>>8),c2=(unsigned char)(x0>>16),
                      c3=(unsigned char)(x0>>24),c4=(unsigned char)(x0>>32),c5=(unsigned char)(x0>>40),
                      c6=(unsigned char)(x0>>48),c7=(unsigned char)(x0>>56);
        unsigned char d0=(unsigned char)x1,d1=(unsigned char)(x1>>8),d2=(unsigned char)(x1>>16),
                      d3=(unsigned char)(x1>>24),d4=(unsigned char)(x1>>32),d5=(unsigned char)(x1>>40),
                      d6=(unsigned char)(x1>>48),d7=(unsigned char)(x1>>56);
        int nul = c0==0||c1==0||c2==0||c3==0||c4==0||c5==0||c6==0||c7==0||
                  d0==0||d1==0||d2==0||d3==0||d4==0||d5==0||d6==0||d7==0;
        if (diff || nul) {
            long i = 0;
            while (i < (long)len) {
                unsigned char ca = a[i], cb = b[i];
                long d = (ulong)ca - (ulong)cb;
                if (d != 0 || ca == 0) return d;
                i++;
            }
            return 0;
        }
        a += 16; b += 16; len -= 16;
    }
    for (; len != 0; len--) {
        long d = (ulong)*a - (ulong)*b;
        if (d != 0 || *a == 0) return d;
        a++; b++;
    }
    return 0;
}

/* FUN_0067b180 @ 0x67b180
 * Ghidra: long FUN_0067b180(ulong, long)
 * strlen with optional length bound. Confidence: low. */
long FUN_0067b180(ulong s, long max)
{
    if (max >= 0) {
        if (max == 0) return 0;
        unsigned long *p = (unsigned long *)(s & ~0xfUL);
        ulong off = max + (s & 0xf);
        ulong i = 0;
        for (;;) {
            unsigned long x0 = p[0], x1 = p[1];
            unsigned char c0=(unsigned char)x0,c1=(unsigned char)(x0>>8),c2=(unsigned char)(x0>>16),
                          c3=(unsigned char)(x0>>24),c4=(unsigned char)(x0>>32),c5=(unsigned char)(x0>>40),
                          c6=(unsigned char)(x0>>48),c7=(unsigned char)(x0>>56);
            unsigned char d0=(unsigned char)x1,d1=(unsigned char)(x1>>8),d2=(unsigned char)(x1>>16),
                          d3=(unsigned char)(x1>>24),d4=(unsigned char)(x1>>32),d5=(unsigned char)(x1>>40),
                          d6=(unsigned char)(x1>>48),d7=(unsigned char)(x1>>56);
            ulong z = 0;
            if (c0==0) z=0; else if (c1==0) z=1; else if (c2==0) z=2; else if (c3==0) z=3;
            else if (c4==0) z=4; else if (c5==0) z=5; else if (c6==0) z=6; else if (c7==0) z=7;
            else if (d0==0) z=8; else if (d1==0) z=9; else if (d2==0) z=10; else if (d3==0) z=11;
            else if (d4==0) z=12; else if (d5==0) z=13; else if (d6==0) z=14; else if (d7==0) z=15;
            else { p += 2; i += 0x10; if (i >= off) return (long)((ulong)p + (off - 1) - s) >= 0 ? (long)p + (long)off - (long)s : (long)p + (long)(off - 1) - (long)s; continue; }
            if (z <= off) { ulong o = z; return (long)p + (long)o - (long)s; }
            return (long)p + (long)off - (long)s;
        }
    }
    /* max < 0: unbounded */
    unsigned long *p = (unsigned long *)(s & ~0xfUL);
    for (;;) {
        unsigned long x0 = p[0], x1 = p[1];
        unsigned char c0=(unsigned char)x0,c1=(unsigned char)(x0>>8),c2=(unsigned char)(x0>>16),
                      c3=(unsigned char)(x0>>24),c4=(unsigned char)(x0>>32),c5=(unsigned char)(x0>>40),
                      c6=(unsigned char)(x0>>48),c7=(unsigned char)(x0>>56);
        unsigned char d0=(unsigned char)x1,d1=(unsigned char)(x1>>8),d2=(unsigned char)(x1>>16),
                      d3=(unsigned char)(x1>>24),d4=(unsigned char)(x1>>32),d5=(unsigned char)(x1>>40),
                      d6=(unsigned char)(x1>>48),d7=(unsigned char)(x1>>56);
        ulong z = 0;
        if (c0==0) z=0; else if (c1==0) z=1; else if (c2==0) z=2; else if (c3==0) z=3;
        else if (c4==0) z=4; else if (c5==0) z=5; else if (c6==0) z=6; else if (c7==0) z=7;
        else if (d0==0) z=8; else if (d1==0) z=9; else if (d2==0) z=10; else if (d3==0) z=11;
        else if (d4==0) z=12; else if (d5==0) z=13; else if (d6==0) z=14; else if (d7==0) z=15;
        else { p += 2; continue; }
        return (long)p + (long)z - (long)s;
    }
}

/* FUN_0067b220 @ 0x67b220
 * Ghidra: long FUN_0067b220(ulong)
 * strlen (unbounded). Confidence: low. */
long FUN_0067b220(ulong s)
{
    return FUN_0067b180(s, -1);
}

/* FUN_0067b280 @ 0x67b280
 * Ghidra: void FUN_0067b280(undefined8 param_1)
 * Fatal: report a range/overflow error with param_1 via the formatter. Confidence: low. */
void FUN_0067b280(ulong msg)
{
    (void)msg;
    FUN_0065562c(msg, (ulong *)0);
    FUN_0067b37c((unsigned char *)0, 0, 0);
}

/* FUN_0067b2ac @ 0x67b2ac
 * Ghidra: char * FUN_0067b2ac(char *, int, long)
 * memchr scalar fallback. Confidence: medium. */
char *FUN_0067b2ac(char *s, int c, long len)
{
    char *p = s + len;
    char *cur = s;
    for (;;) {
        char *cur2 = cur;
        if (len == 0) return NULL;
        if (p <= cur2 || cur2 < s) break;
        len--;
        cur = cur2 + 1;
        if (c == *cur2) return cur2;
    }
    SoftwareBreakpoint(0x5519, 0x67b2e8);
}

/* FUN_0067b2e8 @ 0x67b2e8
 * Ghidra: void FUN_0067b2e8(undefined1 *, undefined1 *, ulong)
 * memmove scalar fallback. Confidence: medium. */
void FUN_0067b2e8(unsigned char *dst, const unsigned char *src, ulong len)
{
    unsigned char *de = dst + len;
    const unsigned char *se = src + len;
    if ((ulong)((long)dst - (long)src) < len) {
        /* overlapping: copy backwards */
        unsigned char *d = dst + len;
        const unsigned char *s = src + len;
        while (len != 0) {
            if (s <= src || src + len <= s || d <= dst || dst + len <= d) goto trap5;
            *--d = *--s;
            len--;
        }
    } else {
        for (; len != 0; len--) {
            if (se <= src + len || src + len < src) goto trap5;
            if (de <= dst + len || dst + len < dst) goto trap5;
            dst[len-1] = src[len-1];
        }
    }
    if (dst <= de) return;
trap5:
    SoftwareBreakpoint(0x5519, 0x67b37c);
}

/* FUN_0067b37c @ 0x67b37c
 * Ghidra: void FUN_0067b37c(undefined1 *, undefined1, long)
 * memset scalar fallback. Confidence: medium. */
void FUN_0067b37c(unsigned char *dst, unsigned char c, long len)
{
    unsigned char *de = dst + len;
    unsigned char *p = dst;
    for (; len != 0; len--) {
        if (de <= p || p < dst) goto trap6;
        *p = c;
        p++;
    }
    if (dst <= de) return;
trap6:
    SoftwareBreakpoint(0x5519, 0x67b3b0);
}

/* FUN_0067b3b0 @ 0x67b3b0
 * Ghidra: int FUN_0067b3b0(byte *, byte *)
 * strcmp scalar fallback. Confidence: medium. */
int FUN_0067b3b0(const unsigned char *a, const unsigned char *b)
{
    unsigned char ca, cb;
    for (;;) {
        ca = *a;
        cb = *b;
        if (ca != *b || (cb = ca, *a == 0)) break;
        a++; b++;
    }
    return (int)ca - (int)cb;
}

/* FUN_0067b3e4 @ 0x67b3e4
 * Ghidra: long FUN_0067b3e4(long)
 * strlen scalar fallback. Confidence: medium. */
long FUN_0067b3e4(long s)
{
    long i = 0;
    while (*(char *)(s + i) != '\0') i++;
    return i;
}

/* FUN_0067b3fc @ 0x67b3fc
 * Ghidra: int FUN_0067b3fc(byte *, byte *, long)
 * strncmp scalar fallback. Confidence: medium. */
int FUN_0067b3fc(const unsigned char *a, const unsigned char *b, long len)
{
    for (;;) {
        if (len == 0) return 0;
        if ((unsigned int)*a - (unsigned int)*b != 0) break;
        unsigned char ca = *a;
        len--;
        a++; b++;
        if (ca == 0) return 0;
    }
    return (unsigned int)*a - (unsigned int)*b;
}

/* FUN_0067b42c @ 0x67b42c
 * Ghidra: long FUN_0067b42c(long, long)
 * strnlen scalar fallback. Confidence: medium. */
long FUN_0067b42c(long s, long max)
{
    long i;
    for (i = 0; (long)i != max && *(char *)(s + i) != '\0'; i++) {}
    return i;
}

/* ---- Object-list iterators (0x67b454-0x67b768) ---- */

/* FUN_0067b454 @ 0x67b454
 * Ghidra: ulong FUN_0067b454(undefined8, undefined8, int, long, undefined8, code *)
 * Count elements in a linked structure (optionally filtered by a callback),
 * counting child nodes too. Confidence: low. */
ulong FUN_0067b454(ulong a, ulong b, int countchildren, long root, ulong cookie, code *fn)
{
    cL4_w16_t start = (cL4_w16_t)FUN_006555fc(0x6b108f);
    ulong p = start.lo;
    ulong count = 0;
    ulong *node;
    while ((node = (ulong *)(root + p)) != NULL &&
           (fn == NULL || (*(int (**)(void))fn)(node, 0, cookie) != 0)) {
        if ((start.hi != 0) && (long *c = (long *)FUN_0067b704(node, 0)) != NULL) {
            while (c != NULL && (fn == NULL || (*(int (**)(void))fn)(c, 1, cookie) != 0)) {
                long *next = (long *)0;
                if (c[1] != 0) {
                    if (FUN_00655650(c[1]) != 0) {
                        count++;
                        next = (long *)*c;
                    }
                }
                c = next;
            }
            if (countchildren == 0) break;
        }
        if (node[1] == 0) break;
        count++;
        p = *node & 0xfffffffffffffff;
    }
    return count & ((long)count >> 0x3f ^ -1UL);
}

/* FUN_0067b478 @ 0x67b478
 * Ghidra: ulong FUN_0067b478(ulong, int, int, long, undefined8, code *)
 * Count elements from an offset in a linked structure with optional filter.
 * Confidence: low. */
ulong FUN_0067b478(ulong p0, int countchildren, int brk, long root, ulong cookie, code *fn)
{
    ulong count = 0;
    ulong *node;
    while ((node = (ulong *)(root + p0)) != NULL &&
           (fn == NULL || (*(int (**)(void))fn)(node, 0, cookie) != 0)) {
        if (countchildren != 0 && (long *c = (long *)FUN_0067b704(node, 0)) != NULL) {
            while (c != NULL && (fn == NULL || (*(int (**)(void))fn)(c, 1, cookie) != 0)) {
                long *next = (long *)0;
                if (c[1] != 0) {
                    if (FUN_00655650(c[1]) != 0) {
                        count++;
                        next = (long *)*c;
                    }
                }
                c = next;
            }
            if (brk == 0) break;
        }
        if (node[1] == 0) break;
        count++;
        p0 = *node & 0xfffffffffffffff;
    }
    return count & ((long)count >> 0x3f ^ -1UL);
}

/* FUN_0067b580 @ 0x67b580
 * Ghidra: ulong FUN_0067b580(long, long, ulong, undefined4 *)
 * Flatten a linked structure into an array, returning the element count.
 * Confidence: low. */
ulong FUN_0067b580(long root, long out, ulong max, unsigned int *plast)
{
    long *node;
    if (root == 0) return -1UL;
    if (plast != NULL) *plast = 0;
    ulong count;
    for (count = 0; root != 0 && count < max; count++) {
        ulong *n = (ulong *)FUN_0067b704(root, plast);
        if (n != NULL) {
            while (n != NULL && count < max) {
                ulong *next = NULL;
                if (n[1] != 0) {
                    long v = FUN_00655650(n[1]);
                    if (v != 0) {
                        if (out != 0) *(long *)(out + count * 8) = v + 1;
                        count++;
                        next = (ulong *)*n;
                    }
                }
                n = next;
            }
            break;
        }
        long nb = FUN_0067b768();
        if (nb == 0) break;
        ulong v = FUN_00655650();
        if (out != 0) *(ulong *)(out + count * 8) = v;
        FUN_0067b758();
    }
    return count & ((long)count >> 0x3f ^ -1UL);
}

/* FUN_0067b664 @ 0x67b664
 * Ghidra: ulong FUN_0067b664(ulong, long, ulong, long, code *, undefined8)
 * Map a linked structure through a callback into an array. Confidence: low. */
ulong FUN_0067b664(ulong p0, long out, ulong max, long root, code *fn, ulong cookie)
{
    ulong *node;
    if (out == 0) return -1UL;
    ulong count = 0;
    while ((node = (ulong *)(root + p0)) != NULL && count < max && node[1] != 0) {
        ulong v = (*(ulong (**)(void))fn)(node[1], cookie);
        *(ulong *)(out + count * 8) = v;
        count++;
        p0 = *node & 0xfffffffffffffff;
    }
    return count;
}

/* FUN_0067b704 @ 0x67b704
 * Ghidra: undefined8 FUN_0067b704(long, undefined4 *)
 * Fetch a node from the per-thread list, returning its payload (or 0).
 * Confidence: low. */
ulong FUN_0067b704(long node, unsigned int *pinfo)
{
    if ((*(unsigned char *)(node + 7) >> 4 & 1) != 0) {
        long *tp = (long *)tpidr_el0;
        long *slot = tp + 6;
        if (slot < tp || tp + 0x1f < tp + 7 || tp + 7 < slot)
            SoftwareBreakpoint(0x5519, 0x67b758);
        if (*slot != 0) {
            if (pinfo != NULL) *pinfo = *(unsigned int *)(*slot + 0x24);
            return *(ulong *)(node - 8);
        }
    }
    return 0;
}

/* FUN_0067b758 @ 0x67b758
 * Ghidra: void FUN_0067b758(void)
 * No-op (list release stub). Confidence: medium. */
void FUN_0067b758(void) { }

/* FUN_0067b768 @ 0x67b768
 * Ghidra: undefined8 FUN_0067b768(void)
 * Read the next list element from a register-resident pointer. Confidence: low. */
ulong FUN_0067b768(void)
{
    return 0;   /* unaff_x22 + 8 */
}

/* ---- printf / FILE writer (0x67b774-0x67d440) ---- */

/* FUN_0067bde4 @ 0x67bde4
 * Ghidra: undefined8 FUN_0067bde4(char *, undefined8)
 * Append a single char to the output buffer, growing it if needed.
 * Confidence: medium. */
ulong FUN_0067bde4(char *buf, ulong ch)
{
    if (*buf == 1) {
        FUN_0067d248(ch, *(ulong *)(buf + 8));
    } else {
        ulong len = *(ulong *)(buf + 0x20);
        ulong n = len + 1;
        if (n < len) return 0;              /* overflow */
        ulong cap = *(ulong *)(buf + 0x10);
        if (n < cap) {
            unsigned char *p = *(unsigned char **)(buf + 8);
            if (p + cap <= p + len || p + len < p)
                SoftwareBreakpoint(0x5519, 0x67bea4);
            p[len] = (char)ch;
        } else if (cap == n) {
            unsigned char *p = *(unsigned char **)(buf + 8);
            if (p + n <= p + len || p + len < p)
                SoftwareBreakpoint(0x5519, 0x67bea4);
            p[len] = 0;
        }
    }
    *(long *)(buf + 0x20) = *(long *)(buf + 0x20) + 1;
    return 1;
}

/* FUN_0067c628 @ 0x67c628
 * Ghidra: undefined8 FUN_0067c628(long, byte *, undefined8, long, undefined8, ulong)
 * Pad then write: fill leading/trailing padding to the field width, then
 * copy the payload and any suffix. Confidence: low. */
ulong FUN_0067c628(long buf, unsigned char *fmt, ulong lead, long nlead, ulong mid, ulong nmid)
{
    ulong width = nmid;
    if ((*fmt & 1) != 0)
        width = (ulong)*(unsigned int *)(fmt + 8);
    long len0 = *(long *)(buf + 0x20);
    if ((*fmt >> 6 & 1) == 0) {
        long pad = 0;
        if (width + nlead <= (ulong)*(unsigned int *)(fmt + 4))
            pad = (ulong)*(unsigned int *)(fmt + 4) - (width + nlead);
        if (FUN_0067c778(buf, 0x20, pad) == 0)
            return 0;
    }
    if (FUN_0067c878(buf, lead, nlead) != 0) {
        long pad = 0;
        if (nmid <= width)
            pad = width - nmid;
        if (FUN_0067c778(buf, 0x30, pad) != 0 &&
            FUN_0067c878(buf, mid, nmid) != 0) {
            if ((*fmt >> 6 & 1) != 0) {
                width = len0 + (ulong)*(unsigned int *)(fmt + 4);
                long tail = 0;
                if (*(ulong *)(buf + 0x20) <= width)
                    tail = width - *(ulong *)(buf + 0x20);
                if (FUN_0067c778(buf, 0x20, tail) == 0)
                    return 0;
            }
            *fmt = 0;
            return 1;
        }
    }
    return 0;
}

/* FUN_0067c778 @ 0x67c778
 * Ghidra: undefined8 FUN_0067c778(char *, undefined8, ulong)
 * Fill the output buffer with n copies of byte ch. Confidence: medium. */
ulong FUN_0067c778(char *buf, ulong ch, ulong n)
{
    if (n != 0) {
        ulong left = n;
        if (*buf == 1) {
            for (; left != 0; left--)
                FUN_0067d248(ch, *(ulong *)(buf + 8));
        } else {
            ulong len = *(ulong *)(buf + 0x20);
            if (len + n < len) return 0;
            ulong cap = *(ulong *)(buf + 0x10);
            if (len + n < cap) {
                unsigned char *p = *(unsigned char **)(buf + 8);
                if (p + cap < p + len || p + len < p || cap - len < n)
                    SoftwareBreakpoint(0x5519, 0x67c828);
                FUN_0067a7f0(p + len, ch, n);
            } else {
                long room = cap - len;
                if (len <= cap && room != 0) {
                    FUN_0067a7f0(*(long *)(buf + 8) + len, ch, room);
                    unsigned char *p = *(unsigned char **)(buf + 8);
                    if (p + cap <= p + room - 1 || p + room - 1 < p)
                        SoftwareBreakpoint(0x5519, 0x67c828);
                    p[room - 1] = 0;
                }
            }
        }
        *(ulong *)(buf + 0x20) = *(long *)(buf + 0x20) + n;
    }
    return 1;
}

/* FUN_0067c878 @ 0x67c878
 * Ghidra: undefined8 FUN_0067c878(char *, undefined8, ulong)
 * Copy n bytes from src into the output buffer. Confidence: medium. */
ulong FUN_0067c878(char *buf, ulong src, ulong n)
{
    if (n != 0) {
        if (*buf == 1) {
            FUN_0067d4a4(src, n, *(ulong *)(buf + 8));
        } else {
            ulong len = *(ulong *)(buf + 0x20);
            if (len + n < len) return 0;
            ulong cap = *(ulong *)(buf + 0x10);
            if (len + n < cap) {
                ulong dst = *(ulong *)(buf + 8) + len;
                if (*(ulong *)(buf + 8) + cap < dst || dst < *(ulong *)(buf + 8) ||
                    cap - len < n) goto trap7;
                FUN_0067aa00((unsigned char *)dst, (const unsigned char *)src, n);
            } else {
                ulong room = cap - len;
                if (len <= cap && room != 0) {
                    ulong dst = *(ulong *)(buf + 8) + len;
                    if (n < room || *(ulong *)(buf + 8) + cap < dst || dst < *(ulong *)(buf + 8))
                        goto trap7;
                    FUN_0067aa00((unsigned char *)dst, (const unsigned char *)src, room);
                    unsigned char *p = *(unsigned char **)(buf + 8);
                    if (p + cap <= p + room - 1 || p + room - 1 < p) goto trap7;
                    p[room - 1] = 0;
                }
            }
        }
        *(ulong *)(buf + 0x20) = *(long *)(buf + 0x20) + n;
    }
    return 1;
trap7:
    SoftwareBreakpoint(0x5519, 0x67c958);
}

/* FUN_0067c720 @ 0x67c720
 * Ghidra: void FUN_0067c720(undefined8, byte *, undefined8, undefined4)
 * Apply a precision to the output field and write it. Confidence: low. */
void FUN_0067c720(ulong buf, unsigned char *fmt, ulong src, unsigned int prec)
{
    if ((*fmt & 1) == 0) {
        cL4_w16_t r = (cL4_w16_t)FUN_0067ca44();
        FUN_0067b454(r.lo, r.hi, 0x6b1123, 0x18e);
    }
    if ((*fmt >> 3 & 1) != 0) {
        if (*(unsigned int *)(fmt + 8) < *(unsigned int *)(fmt + 4))
            *(unsigned int *)(fmt + 8) = *(unsigned int *)(fmt + 4);
        else goto do_write;
    }
    *(unsigned int *)(fmt + 8) = prec;
do_write:
    FUN_0067c628(buf, fmt, 0, 0, src, prec);
}

/* FUN_0067c18c @ 0x67c18c
 * Ghidra: undefined8 FUN_0067c18c(byte *, ulong *, long *)
 * Fetch the next printf argument per its size prefix; returns 1 and stores
 * the value, or 0 for an unsupported length modifier. Confidence: medium. */
ulong FUN_0067c18c(unsigned char *fmt, ulong *out, long *argp)
{
    if ((*fmt & 1) == 0) {
        *fmt |= 1;
        fmt[8] = 1; fmt[9] = 0; fmt[10] = 0; fmt[11] = 0;
    }
    short lmod = *(short *)(fmt + 2);
    ulong v;
    if (lmod != 0x6c6c) {
        if (lmod == 0x68) {
            unsigned short *p = (unsigned short *)*argp;
            *argp = (long)(p + 4);
            v = *p;
            goto done;
        }
        if (lmod != 0x6a && lmod != 0x6c && lmod != 0x74 && lmod != 0x7a) {
            if (lmod == 0x6868) {
                unsigned char *p = (unsigned char *)*argp;
                *argp = (long)(p + 8);
                v = *p;
            } else {
                if (lmod != 0) return 0;
                unsigned int *p = (unsigned int *)*argp;
                *argp = (long)(p + 2);
                v = *p;
            }
            goto done;
        }
    }
    ulong *p = (ulong *)*argp;
    *argp = (long)(p + 1);
    v = *p;
done:
    *out = v;
    return 1;
}

/* FUN_0067ca6c @ 0x67ca6c
 * Ghidra: void FUN_0067ca6c(undefined8, undefined8, undefined8, undefined8)
 * Format a string into the buffer (wrapper over the printf core). Confidence: low. */
void FUN_0067ca6c(ulong a, ulong b, ulong c, ulong d)
{
    FUN_0067b774(0, a, b, c, d);
}

/* FUN_0067ca84 @ 0x67ca84
 * Ghidra: void FUN_0067ca84(undefined8, ulong, undefined8, ulong, undefined8, undefined8)
 * Format with a size check: panic on overflow. Confidence: low. */
void FUN_0067ca84(ulong a, ulong alen, ulong b, ulong blen, ulong c, ulong d)
{
    if (alen <= blen) {
        FUN_0067ca6c(a, alen, c, d);
        return;
    }
    FUN_0067b280(0x6a612a);
}

/* FUN_0067b774 @ 0x67b774
 * Ghidra: void FUN_0067b774(long, undefined8, ulong, byte *, undefined8)
 * vcbprintf-style formatter: parse a format string and emit each field
 * through the output buffer writer. Confidence: low (large state machine). */
void FUN_0067b774(long iserr, ulong out, ulong limit, const unsigned char *fmt, ulong argbase)
{
    cL4_w16_t h = (cL4_w16_t)FUN_0067ca20();
    long bufend = h.hi;
    unsigned char flags = 0;                 /* accumulated %-flags byte */
    ulong width = 0, prec = 0;
    ulong outptr = out;
    ulong argp = argbase;                    /* var-arg cursor */
    ulong nout = 0;
    unsigned int w = 0;
    unsigned int p = 0;
    long xerr = 0;
    int bad = 0;

    if (h.lo == 0) {
        if (bufend != 0 || limit == 0) {
            /* fixed buffer mode */
            width = 0;
            outptr = bufend;
            prec = limit;
        } else {
            /* dynamic grow mode */
            width = 1;
            outptr = iserr;                  /* buffer base */
            thunk_FUN_0065569c(iserr);
            if (*(long *)(iserr + 0x10) != 0 && *(long *)(iserr + 0x10) != 0)
                goto body;
            thunk_FUN_00655774(iserr);
            return;
        }
    } else {
        width = 0xffffffff;
        if (bufend == 0 && limit == 0) {
            width = 1;
            outptr = iserr;
            thunk_FUN_0065569c(iserr);
            if (*(long *)(iserr + 0x10) != 0 && *(long *)(iserr + 0x10) != 0)
                goto body;
            thunk_FUN_00655774(iserr);
            return;
        }
    }

body:
    nout = 0;
    unsigned int field = 0;
    unsigned long state = 0;                 /* packed flags/width/prec */
    unsigned long wid = 0, prc = 0;
    for (;;) {
        unsigned char c = *fmt;
        if (c == 0) {
            if ((width & 1) == 0 && (nout < prec))
                *(unsigned char *)(outptr + nout) = 0;
            goto finish;
        }
        unsigned char s = (unsigned char)state;
        unsigned int st = field;
        if ((char)(unsigned char)state >= 0) {
            if (c == 0x25) {
                state = (state & ~0xffUL) | 0x80;
            } else {
                ulong ok = FUN_0067bde4(&width, (int)(char)c);
                if ((ok & 1) == 0) { bad = 1; goto finish; }
            }
            continue;
        }
        /* inside a %-directive */
        switch (c - 0x20) {
        case 0x25: case 0x26: case 0x27:
            state |= 2;
        case 0x45: case 0x46: case 0x47:
            if ((FUN_0067c24c((int)(char)c, &width, &state, &field) & 1) != 0) break;
            goto finish;
        case 0x43:
            if ((state & 1) == 0 && ((state >> 16) & 0xff) == 0) {
                FUN_0067c9a4();
                unsigned char ch = *(unsigned char *)(argp);
                if (FUN_0067c628(&width, &state, 0, 0, (ulong)&ch, 1) != 0) { state &= ~0xffUL; break; }
            }
            bad = 1; goto finish;
        case 0x44: case 0x49: {
            ulong v;
            if ((state & 1) == 0) { state |= 1; field = 1; }
            if (((state >> 16) & 0xff) == 0x6c6c) {
                FUN_0067c9a4();
                v = *(long *)(argp);
            } else if (((state >> 16) & 0xff) == 0x68) {
                FUN_0067c9a4();
                v = (long)*(short *)(argp);
            } else {
                if ((((state >> 16) & 0xff) != 0x6a) && (((state >> 16) & 0xff) != 0x6c) &&
                    (((state >> 16) & 0xff) != 0x74) && (((state >> 16) & 0xff) != 0x7a)) {
                    if (((state >> 16) & 0xff) == 0x6868) {
                        FUN_0067c9a4();
                        v = (long)*(signed char *)(argp);
                    } else {
                        if (((state >> 16) & 0xff) != 0) { bad = 1; goto finish; }
                        FUN_0067c9a4();
                        v = (long)*(int *)(argp);
                    }
                } else {
                    FUN_0067c9a4();
                    v = *(long *)(argp);
                }
            }
            if ((FUN_0067bea4(out, &width, (ulong)v, (int)((state>>8)&0xff), field, prc) & 1) != 0)
                break;
            bad = 1; goto finish;
        }
        case 0x48: case 0x4c:
            state = (state & ~0xffffUL) | ((state & 0xffff) << 8) | c;
            break;
        case 0x4f: case 0x55:
            if (((state >> 0) & 0xffff) == 0) {
                FUN_0067c9ec();
                ulong v = *(ulong *)(argp);
                if ((FUN_0067bea4(out, &width, v, (int)((state>>8)&0xff), field, prc) & 1) != 0)
                    break;
            }
            bad = 1; goto finish;
        case 0x50:
            if ((state & 1) != 0) { bad = 1; goto finish; }
            FUN_0067ca10();
            ulong pv = *(ulong *)(argp);
            state = (state & ~0xffUL) | 5;
            field = 0x10;
            goto fcall;
        case 0x53:
            if ((state & 0xc) == 0 && ((state >> 16) & 0xff) == 0) {
                FUN_0067ca10();
                ulong s = *(ulong *)(argp);
                long slen = FUN_0067b220(s);
                if ((slen & 1) == 0) { state |= 1; field = 6; }
                if (s + (ulong)slen >= s) {
                    if (FUN_0067c628(&width, &state, 0, 0, s, (ulong)slen) != 0) { state &= ~0xffUL; break; }
                }
            }
            bad = 1; goto finish;
        case 0x5a:
            if ((state & 1) == 0 && ((state >> 32) & 0xffffffffUL) != 0) {
                width = (state >> 32) * 10;
                state = (state & 0xffffffffUL) | (width << 32);
                field = 0;
            }
            break;
        case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15:
        case 0x16: case 0x17: case 0x18: case 0x19:
            if ((state & 1) == 0) {
                width = (c - 0x30) + ((state >> 32) & 0xffffffffUL) * 10;
                state = (state & 0xffffffffUL) | (width << 32);
            } else {
                width = (c - 0x30) + field * 10;
            }
            break;
        case 0x2c: case 0x4a: case 0x54:
            state = (state & ~0xffffffffUL) | c;
            break;
        case 0x2e:
            if ((state & 1) == 0 && ((state >> 16) & 0xff) == 0) {
                state = (state & ~0xffUL) | 4;
                field = 0;
            } else { bad = 1; goto finish; }
            break;
        case 0x38: case 0x58:
            state |= 2;
            FUN_0067c9ec();
            ulong v2 = *(ulong *)(argp);
fcall:
            if ((FUN_0067bea4(out, &width, v2, (int)((state>>8)&0xff), field, prc) & 1) != 0) {
                state &= ~0xffUL;
                break;
            }
            bad = 1; goto finish;
        case 0x3: case 0xb: case 0xd: case 0xe:
            if (((state >> 5) & 1) == 0) {
                state = (state & ~0x20UL) | 0x20;
            } else { bad = 1; goto finish; }
            break;
        default:
            bad = 1; goto finish;
        }
        continue;
    }
finish:
    FUN_00665d70(xerr, bad & 0xffffffff);
}

/* FUN_0067ca20 @ 0x67ca20
 * Ghidra: void FUN_0067ca20(void) (returns 16-byte)
 * Return the output-mode descriptor (empty). Confidence: low. */
cL4_w16_t FUN_0067ca20(void) { return (cL4_w16_t){0,0}; }

/* FUN_0067ca30 @ 0x67ca30
 * Ghidra: void FUN_0067ca30(void) (returns 16-byte)
 * Return an empty 16-byte descriptor. Confidence: low. */
cL4_w16_t FUN_0067ca30(void) { return (cL4_w16_t){0,0}; }

/* FUN_0067ca44 @ 0x67ca44
 * Ghidra: undefined1 [16] FUN_0067ca44(void)
 * Return a 16-byte {file,msg} descriptor for error reporting. Confidence: low. */
cL4_w16_t FUN_0067ca44(void) { return (cL4_w16_t){ 0x6b10cc, 0x6b10ec }; }

/* FUN_0067c994 @ 0x67c994 / FUN_0067c9b4 @ 0x67c9b4
 * No-op float-format helpers. Confidence: medium. */
void FUN_0067c994(void) { }
void FUN_0067c9b4(void) { }

/* FUN_0067c9a4 @ 0x67c9a4 / FUN_0067ca10 @ 0x67ca10
 * Advance the var-arg cursor by 8 bytes (via the saved frame pointer). */
void FUN_0067c9a4(void) { }
void FUN_0067ca10(void) { }

/* FUN_0067c9c4 @ 0x67c9c4
 * Ghidra: undefined1 [16] FUN_0067c9c4(void)
 * Return a 16-byte {lo,hi} stack descriptor. Confidence: low. */
cL4_w16_t FUN_0067c9c4(void) { return (cL4_w16_t){ 0x20, 0x10 }; }

/* FUN_0067c9d8 @ 0x67c9d8
 * Ghidra: void FUN_0067c9d8(void)
 * Mark a format descriptor as "in use" with a 6-byte width. Confidence: low. */
void FUN_0067c9d8(void) { }

/* FUN_0067c9ec @ 0x67c9ec
 * Ghidra: void FUN_0067c9ec(void)
 * Fetch the next var-arg (long) via the argument parser. Confidence: low. */
void FUN_0067c9ec(void) { }

/* FUN_0067ca00 @ 0x67ca00
 * Ghidra: void FUN_0067ca00(void)
 * Advance the var-arg cursor by one long. Confidence: low. */
void FUN_0067ca00(void) { }

/* FUN_0067ca58 @ 0x67ca58
 * Ghidra: undefined4 FUN_0067ca58(void)
 * Read the field-precision word from a register-resident descriptor. Confidence: low. */
unsigned int FUN_0067ca58(void) { return 0; }

/* FUN_0067bea4 @ 0x67bea4
 * Ghidra: void FUN_0067bea4(undefined8, undefined8, ulong, int, int, ulong)
 * Render a (u)int64 value into the output buffer honoring the field flags
 * (sign, base prefix, zero-pad, width/precision). Confidence: low. */
void FUN_0067bea4(ulong out, ulong buf, ulong val, int sign, int field, ulong prec)
{
    /* Parse flags already accumulated in `field` (bits: 1=alt,2=zero,4=left,
     * 8=plus,0x10=space,0x20=sharp). */
    unsigned char tmp[64];
    ulong base = prec & 0xffffffff;
    ulong v = val;
    ulong n = 0;
    if (base == 0) base = 10;
    do {
        unsigned char d = (unsigned char)(v % base);
        tmp[n++] = (d < 10) ? ('0'+d) : ('a'+d-10);
        v /= base;
    } while (v != 0);
    /* prefix for non-decimal + alternate form */
    int prefix = 0;
    int neg = 0;
    ulong vv = val;
    if (sign && (long)val < 0) { neg = 1; vv = (ulong)-(long)val; }
    /* rebuild digits from vv */
    n = 0;
    do {
        unsigned char d = (unsigned char)(vv % base);
        tmp[n++] = (d < 10) ? ('0'+d) : ('a'+d-10);
        vv /= base;
    } while (vv != 0);
    /* emit: prefix/sign, (zero-pad), digits */
    ulong ndig = n;
    ulong width = (field & 1) ? ((field >> 8) & 0xffff) : 0;
    long pad = 0;
    if ((field & 2) == 0) {               /* right-align */
        if (ndig + (neg||prefix?1:0) < width)
            pad = width - ndig - (neg||prefix?1:0);
        FUN_0067c778((char *)buf, 0x20, pad);
    }
    if (neg) FUN_0067bde4((char *)buf, '-');
    else if ((field & 8) != 0) FUN_0067bde4((char *)buf, '+');
    else if ((field & 0x10) != 0) FUN_0067bde4((char *)buf, ' ');
    if ((field & 2) != 0) {
        if (ndig + (neg||prefix?1:0) < width)
            pad = width - ndig - (neg||prefix?1:0);
        FUN_0067c778((char *)buf, '0', pad);
    }
    while (n != 0) FUN_0067bde4((char *)buf, tmp[--n]);
    if ((field & 4) != 0) {               /* left-align */
        if (ndig + (neg||prefix?1:0) < width) {
            pad = width - ndig - (neg||prefix?1:0);
            FUN_0067c778((char *)buf, 0x20, pad);
        }
    }
}

/* FUN_0067c24c @ 0x67c24c
 * Ghidra: void FUN_0067c24c(int, long, byte *, uint)
 * Format a double for %e/%g/%f into the output buffer using a scratch
 * decimal buffer. Confidence: low (float formatting). */
void FUN_0067c24c(int conv, long buf, unsigned char *fmt, unsigned int prec)
{
    unsigned char scratch[1024];
    FUN_0067ca20();
    if (conv == 0x65 || conv == 0x67 || conv == 0x66) {
        /* 0x65='e', 0x66='f', 0x67='g' */
        if ((*fmt & 1) == 0) FUN_0067c9d8();
        short lmod = *(short *)(fmt + 2);
        if (lmod == 0 || lmod == 0x6c || lmod == 0x4c) {
            FUN_0067ca00();
            /* fetch the double from the arg list */
            FUN_0067c994();
            FUN_0067ca58();
            ulong v = FUN_0067e9c0();
            unsigned int ndig = v > 0x3ff ? prec : (unsigned int)v;
            FUN_0067c720(buf, fmt, (ulong)scratch, ndig);
        } else {
            FUN_0067c994();
            FUN_0067c9b4();
            unsigned int ndig = FUN_0067dc08();
            unsigned int cap = ndig > 0x3ff ? 0x400 : ndig;
            FUN_0067c720(buf, fmt, (ulong)scratch, cap);
        }
        return;
    }
    FUN_00665d70(buf, 0);
}
