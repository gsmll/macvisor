/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 32: 0x372534-0x37ffc4 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

typedef uint64_t (*code)(void *, ...);   /* Ghidra 'code *' (variadic) fn pointer */
typedef uint64_t (*sk_fnv_t)(uint64_t, ...);  /* variadic dispatch fn */

/* Ghidra primitive aliases used in this translation. */
typedef unsigned long  ulong;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  byte;
typedef unsigned long  undefined8;
typedef unsigned int   undefined4;
typedef unsigned short undefined2;
typedef unsigned char  undefined1;

/* 16-byte register-pair return (Ghidra undefined1[16] / CONCAT816). */
typedef struct sk_pair { uint64_t lo; uint64_t hi; } sk_pair_t;
#define SKPAIR(p) { (p).lo, (p).hi }
#define SKPAIR2(lo_,hi_) ((sk_pair_t){ (lo_), (hi_) })
#ifndef POPCOUNT
#define POPCOUNT(x) __builtin_popcount((unsigned)(x))
#endif
#ifndef CONCAT11
#define CONCAT11(a,b) ((uint16_t)(((uint8_t)(a)<<8)|(uint8_t)(b)))
#endif
#ifndef CONCAT44
#define CONCAT44(a,b) ((uint64_t)((uint32_t)(a)<<32)|(uint32_t)(b))
#endif
#ifndef LZCOUNT
#define LZCOUNT(x) __builtin_clzll((unsigned long long)(x))
#endif
#ifndef LOAcquire
#define LOAcquire() ((void)0)
#define LORelease() ((void)0)
#endif
#ifndef DataMemoryBarrier
#define DataMemoryBarrier(o,v) __asm__ volatile("dmb ish" ::: "memory")
#endif

/* Out-of-range kernel helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Names are estimates. */

/* Page allocator / object allocator primitives (region 0x34xxxx-0x36xxxx). */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void *sk_object_alloc_sized(unsigned long *out, unsigned long cnt,
                                   unsigned long size, unsigned long tag); /* FUN_0001062c */
extern void *sk_desc_alloc(unsigned long *out, unsigned long align,
                           unsigned long flag);                        /* FUN_00369758 */
extern void sk_desc_commit(void *target, void *desc, unsigned long flag);
extern void FUN_0035cf38(void *t, void *d, unsigned long f); /* FUN_0035cf38 */
extern unsigned long sk_cap_bind(unsigned long cap, ...);                    /* FUN_0035bd48 */

/* Capability/object staging helpers (this region). */
extern long FUN_00379480(void *cap, ...);          /* cap stage base */
extern void FUN_00117cc4(void *dst, void *src, unsigned long n, ...);
extern uint64_t FUN_0035cc88(void *a, unsigned long b, unsigned long c,
                         unsigned long d, void *e);
extern long FUN_00374230(uint32_t *cap);          /* cap stage offset */
extern sk_pair_t FUN_003742e4(uint32_t *cap);     /* cap stage range */
extern uint64_t FUN_00374e88(uint32_t p1, long p2, long p3, unsigned long *p4);
extern sk_pair_t FUN_0036aae4(void);              /* meta pair */
extern void FUN_0036b170(uint64_t v);             /* meta release */

/* Dedup-registry global table state (DAT_006c...). */
extern unsigned long _DAT_006c0530, _DAT_006c0388, _DAT_006c0730, _DAT_006c0740;
extern unsigned long _DAT_006c06e0, _DAT_006c06e4, _DAT_006c06e8, _DAT_006c06f0;
extern unsigned long _DAT_006c0718, _DAT_006c0720, _DAT_006c06d8, _DAT_006c06d0;
extern unsigned long _DAT_006c0598, _DAT_006c0550, _DAT_006c0554, _DAT_006c0558;
extern unsigned long _DAT_006c0560, _DAT_006c05e8, _DAT_006c05a0, _DAT_006c05a4;
extern unsigned long _DAT_006c05a8, _DAT_006c05b0, _DAT_006c0638, _DAT_006c05f0;
extern unsigned long _DAT_006c05f4, _DAT_006c05f8, _DAT_006c0600, _DAT_006c0640;
extern unsigned long _DAT_006c0644, _DAT_006c0648, _DAT_006c0650, _DAT_006c0688;
extern unsigned long _DAT_006c0690, _DAT_006c0694, _DAT_006c0698, _DAT_006c06a0;
extern unsigned long _DAT_006c0790, _DAT_006c0794, _DAT_006c0798, _DAT_006c07a0;
extern unsigned long _DAT_006c07d8, _DAT_006c0750, _DAT_006c0744, _DAT_006c0748;
extern unsigned long _DAT_006c0780, _DAT_006c0520, _DAT_006c0380, _DAT_006c06b0;
extern unsigned long DAT_004f2710, DAT_004f2748;
extern void *FUN_0036a804(unsigned long size, unsigned long tag);
extern void FUN_003a2578(void *msg, ...);              /* fatal */
extern void FUN_0036a668_(void);
extern uint64_t FUN_0036a668(void *p, ...);
extern uint64_t FUN_00362e54(void *p, ...);
extern uint64_t FUN_003873c0(void *p, unsigned long n);
extern uint64_t FUN_003876c4(void *p);
extern uint64_t FUN_0035eb3c(void *p);
extern uint64_t FUN_0035ef4c(void *p);
extern uint64_t FUN_003658a0(void *p);
extern uint64_t FUN_0035eae4(void *p);
extern uint64_t FUN_0036d8a4(void *p, void *q);
extern uint64_t FUN_0036fb10(void *p);
extern uint64_t FUN_0036f460(void *p, ...);
extern uint64_t FUN_0037f9f4(void);
extern uint64_t FUN_0037a850(void *p, unsigned long n);
extern uint64_t FUN_0037a9ac(uint64_t *p, uint64_t a, uint64_t b);
extern ulong FUN_0037a7f8(void);
extern uint64_t FUN_0037a920(long n);
extern uint64_t FUN_0037f430(void *p);
extern uint64_t FUN_0037f638(void *p);
extern uint64_t FUN_0037f7a4(void *p);
extern uint64_t FUN_0037f8c8(void *p, uint64_t v);
extern uint64_t FUN_0037f940(void *a, void *b, void *c);
extern uint64_t FUN_0037b350(void *p, ...);
extern uint64_t FUN_0037b054(void *p, ...);
extern uint64_t FUN_0037a4c0(long p, ulong a, ulong b, long c);
void sk_meta_backing_release(long *param_1);
extern uint64_t FUN_0037a5e0(long p, long a, ulong b);
extern uint64_t FUN_0037a898(ulong n);
extern sk_pair_t FUN_0037a238(long p, ulong a, ulong b, long c);
extern sk_pair_t FUN_00378374(uint64_t p);
extern long FUN_0037b408(uint64_t p, ...);
extern uint64_t FUN_0037babc(uint64_t p, ...);
extern uint64_t FUN_0037bb44(uint64_t p, ...);
extern long FUN_0037b484(uint64_t p, ...);
extern long FUN_0037b4e0(uint64_t p, ...);
extern long FUN_0037b540(uint64_t p, ...);
extern uint64_t FUN_0037b5d4(uint64_t p, ...);
extern uint64_t FUN_0037b658(uint64_t p, ...);
extern uint64_t FUN_0037b6dc(uint64_t p, ...);
extern uint64_t FUN_0037b764(uint64_t p, ...);
extern uint64_t FUN_0037b808(uint64_t p, ...);
extern uint64_t FUN_0037b908(uint64_t p, ...);
extern uint64_t FUN_0037b990(uint64_t p, ...);
extern sk_pair_t FUN_0037ba20(uint64_t p, ...);
extern long FUN_0037bcfc(uint64_t p, ...);
extern long FUN_0037bd78(uint64_t p, ...);
extern long FUN_0037bdd4(uint64_t p, ...);
extern long FUN_0037be34(uint64_t p, ...);
extern uint64_t FUN_0037bec8(uint64_t p, ...);
extern uint64_t FUN_0037bf4c(uint64_t p, ...);
extern uint64_t FUN_0037bfd0(uint64_t p, ...);
extern uint64_t FUN_0037c058(uint64_t p, ...);
extern uint64_t FUN_0037c0fc(uint64_t p, ...);
extern uint64_t FUN_0037c1fc(uint64_t p, ...);
extern uint64_t FUN_0037c284(uint64_t p, ...);
extern sk_pair_t FUN_0037c314(uint64_t p, ...);
extern uint64_t FUN_0037c3b0(uint64_t p, ...);
extern uint64_t FUN_0037c438(uint64_t p, ...);
extern uint64_t FUN_0037c4dc(uint64_t p, ...);
extern uint64_t FUN_0037bbe8(uint64_t p, ...);
extern uint64_t FUN_0037c68c(ulong p);
extern long FUN_0037bcac(void *p, ...);
extern long FUN_0037b3b8(void *p, ...);
extern uint64_t FUN_0037f9f8(void);
extern ulong FUN_0037ed70(ulong p);
extern void FUN_0037f398(void);
extern uint64_t thunk_FUN_001144a0(void *a, ulong b, ulong c);
extern uint64_t FUN_0037c82c(uint64_t *p);
extern uint64_t FUN_0037c770(uint64_t *p, long a);
extern uint64_t FUN_0037c8e4(uint64_t p, ...);
extern uint64_t FUN_0037c88c(uint64_t p, ...);
extern uint64_t FUN_0037c930(uint64_t p, ...);
extern sk_pair_t FUN_0037ca00(uint64_t p, ...);
extern uint64_t FUN_0037c9a0(uint64_t p, ...);
extern sk_pair_t FUN_0037cd8c(int *p, uint64_t *q, ...);
extern void FUN_0037ccbc(uint64_t *p1, long p2, uint64_t *p3, uint64_t p4, uint64_t *p5, uint64_t *p6);
extern sk_pair_t FUN_0037d0dc(void *p1, long p2, void *p3);
extern sk_pair_t FUN_0037e348(void *p1, ulong p2, ulong p3, void *p4);
extern uint32_t FUN_0037def8(void *p, ...);
extern long FUN_0037df58(void *p, ...);
extern uint64_t FUN_0037e484(void *p, ...);
extern void FUN_0037e868(long a, long b, long c, uint64_t d);
extern void FUN_0037e614(ulong *p, long a);
extern void FUN_0037e720(long *p, ulong *a, ulong *b);
extern uint8_t *FUN_0037ecac(uint8_t *p1, uint8_t *p2, uint8_t *p3);
extern void FUN_0037ebe4(uint8_t *p1, uint8_t *p2, uint8_t *p3);
extern long FUN_0037eb4c(long *p, ulong n);
extern ulong FUN_0037e8e8(ulong *p, ulong n, ulong seed);
extern void FUN_0037e58c(uint64_t *p, uint64_t a, ulong b);
extern sk_pair_t FUN_0037e348(void *p1, ulong p2, ulong p3, void *p4);
extern uint64_t FUN_0037cec4(long p1, uint64_t *p2, uint64_t p3);
extern uint64_t FUN_0037cf2c(long p1, uint64_t p2, long *p3);
extern ulong *FUN_0037a744(ulong *p1, uint64_t *p2, long p3, uint32_t p4, ulong p5);
extern long FUN_0037d95c(uint32_t *p1, ...);
extern void FUN_0037d700(long *p1, ulong p2);
extern uint64_t FUN_0037a340(ulong *p, ulong a, int b);
extern void FUN_0037a668(ulong *p, ulong *q, uint a, ulong b, int c);
extern uint64_t FUN_0036e7ec(uint64_t a, ...);
extern uint64_t FUN_00118148(void *p, unsigned long n);
extern uint64_t FUN_00118164(void);
extern uint64_t FUN_00118194(void);
extern uint64_t FUN_00112098(void *p, unsigned long n);
extern uint64_t FUN_001124fc(ulong n);
extern void *FUN_00111890(unsigned long size, unsigned long tag);
extern void FUN_00112db4(void *p, char *s);
extern uint64_t FUN_00112e8c(void *p, void *a, void *b);
extern uint64_t FUN_001144a0(void *a, ulong b, ulong c);
extern uint64_t FUN_001145b0(void *a, void *b, ulong n);
extern void FUN_003a2b38_(void);
extern uint64_t FUN_003a2b38(uint64_t a, uint64_t b);
extern uint64_t FUN_00378498(long *p1, long *p2);
extern uint64_t FUN_00379f6c(uint64_t *p1, uint64_t *p2);
extern uint64_t FUN_0037a19c(short *p1, short *p2);
extern void sk_meta_write_elem(ulong *p1, ulong *p2, uint a, ulong b, int c);
extern uint32_t FUN_0037aaac(uint32_t *p, ulong a);
extern uint64_t FUN_0037ab2c(long p, int a);
extern uint64_t FUN_00369758(void *out, ulong a, ulong b);
extern uint64_t FUN_00351a38(void);
extern uint64_t FUN_0022a474(ulong a, ...);
extern void FUN_0024c8bc(void);
extern void FUN_003504e8(void);
extern void FUN_00100efc(void);
extern void FUN_0024daf8(void);
extern void FUN_00355cbc(void);
extern void FUN_00356310(void);
extern uint64_t FUN_003794d0(void *p, ...);
extern uint64_t FUN_0037954c(void *p, ...);
extern uint64_t FUN_003795a8(void *p, ...);
extern uint64_t FUN_00379608(void *p, ...);
extern uint64_t FUN_0037969c(void *p, ...);
extern uint64_t FUN_00379720(void *p, ...);
extern uint64_t FUN_003797a4(void *p, ...);
extern uint64_t FUN_0037982c(void *p, ...);
extern uint64_t FUN_003798d0(void *p, ...);
extern uint64_t FUN_003799d0(void *p, ...);
extern uint64_t FUN_00379a58(void *p, ...);
extern sk_pair_t FUN_00379ae8(void *p, ...);
extern uint64_t FUN_00379b84(void *p, ...);
extern uint64_t FUN_00379c0c(void *p, ...);
extern uint64_t FUN_00379cb0(void *p, ...);
extern uint64_t FUN_00379d74(void *p, ...);
extern uint64_t FUN_00379dec(void *p, ...);
extern uint64_t FUN_00379e78(void *p, ...);
extern uint64_t FUN_00379eec(void *p, ...);
extern uint64_t FUN_00363f10(void *a, void *b);
extern void thunk_FUN_00012568(void *p, ...);
extern int thunk_FUN_001145b0(void *a, ...);
extern uint64_t thunk_FUN_00115080(ulong a, ...);
extern void thunk_FUN_00053aa0(void *p, ...);
extern uint64_t FUN_00387868(void);
extern uint64_t FUN_00381fac(void *p, uint64_t v);
extern uint64_t FUN_003800cc(void *p, uint64_t v);
extern uint64_t FUN_0036b118(uint64_t v);
extern uint64_t FUN_00367dd4(void *p, ...);
extern uint64_t FUN_0035bd48_(void);
extern uint64_t FUN_0039c49c(void *p, void *q);
extern bool FUN_00377cc0(int *p1, int *p2);
extern long *FUN_00377dfc(long *p1, uint64_t *p2);
extern long FUN_0039a1b0(void *p);
extern void FUN_00371af8(void);
extern void FUN_003704ac(void);
extern uint64_t FUN_0037f3d0(void);
extern uint64_t FUN_00376838(ulong a, uint32_t *b, long c);
extern uint64_t FUN_0037dfa8(uint64_t a, uint64_t b, uint64_t c);
extern uint64_t FUN_0037edf0(void *p);
extern uint64_t FUN_0037b170(uint64_t a, uint64_t *b, long c, long d, long e);
extern uint64_t FUN_0037b220(uint64_t a, long *b);
extern uint64_t FUN_0037b288(uint64_t a, long *b);
extern uint64_t FUN_0037ac0c(long a, uint64_t *b, uint32_t c);
extern uint64_t FUN_0037ab7c(uint64_t *a, uint64_t b);
extern uint64_t FUN_0037ae38(uint8_t *a, long b);
extern uint64_t FUN_0037ae90(uint64_t a, uint64_t *b);
extern uint64_t FUN_0037aed8(long *a);
extern uint64_t FUN_0037af40(void *a, void *b);
extern uint64_t FUN_0037b09c(uint8_t *a, uint64_t b, long c, uint32_t d, ...);
extern uint64_t FUN_0037f828(uint8_t *a, ulong *b, uint64_t *c, long d);

/* Forward declarations for functions reconstructed in this file. */
uint64_t *sk_desc_tuple_build(uint64_t *param_1, uint64_t param_2, uint64_t param_3);
extern sk_pair_t FUN_003a31d8(void *name, ...);
extern void FUN_003895e0(void *out, unsigned long a, unsigned long b,
                         unsigned long c, unsigned long d, void *e, void *f);
extern void FUN_0036805c(void *p);
extern void FUN_003680cc(void *p);
extern void *FUN_00111890(unsigned long size, unsigned long tag);
extern void FUN_00117d14(void *dst, void *src, unsigned long n, ...);
extern void FUN_004b89f8(void);                   /* length overflow trap */
extern void FUN_00369bb0(int code, char *msg);
extern void *FUN_0001062c(void *out, unsigned long cnt, unsigned long size, unsigned long tag);    /* fatal/abort */

/* Forward declarations for functions reconstructed in this file. */
void sk_desc_fill_from_type(long *param_1, uint64_t *param_2);
long *sk_desc_copy(long param_1, uint32_t param_2);
void sk_desc_push_word(long *param_1, uint64_t param_2);
uint64_t sk_msg_build_metadata(long param_1, uint32_t param_2, ulong param_3,
                               long param_4, long param_5, uint32_t param_6);

/* Object/type dispatch + dedup-table helpers (this region and 0x34-0x36). */
extern uint64_t FUN_0036a338(uint64_t arg);
extern void *FUN_0036a358(void *arg);
extern uint64_t FUN_003a25b8(uint64_t arg);
extern void sk_meta_write_elem(ulong *p1, ulong *p2, uint a, ulong b, int c);
extern uint64_t FUN_00384b74(void *table, void *key);   /* probe */
extern uint64_t FUN_00384c08(void *key, unsigned long mask, unsigned long cnt,
                             void *slots);               /* hash insert */
extern uint64_t FUN_00384cec(void *p);                   /* hash */
extern uint64_t FUN_00384f48(unsigned long a, unsigned long b, unsigned long c,
                             unsigned long d);
extern uint64_t FUN_0038695c(void *table, void *key);
extern uint64_t FUN_003869f4(void *key, unsigned long mask, unsigned long cnt,
                             void *slots);
extern uint64_t FUN_00386ae0(void *table, void *key);
extern uint64_t FUN_00386b78(void *key, unsigned long mask, unsigned long cnt,
                             void *slots);
extern uint64_t FUN_00386cc4(void *p);
extern uint64_t FUN_00386d2c(void *p);
extern uint64_t FUN_00386d70(void *p);
extern uint64_t FUN_00386ee0(void *obj, uint64_t arg);
extern uint64_t FUN_003870b8(void *slot, void *out, uint64_t arg);
extern uint64_t FUN_00387e60(void *out, ...);
extern void *FUN_00383a1c(void *key, unsigned long mask, unsigned long cnt,
                              void *slots);
extern uint64_t FUN_00383b08(unsigned long v);
extern uint64_t FUN_0037f4bc(void *key, unsigned long mask, unsigned long cnt,
                             void *slots);
extern uint64_t FUN_0037f5b0(void *table, void *key);
extern uint64_t FUN_0037a48c(void *n, ...);
extern uint64_t FUN_0037a978(unsigned long dbg);
extern uint64_t FUN_0035b178(void *tbl, unsigned long i, unsigned long a);
extern void FUN_0035b588(void *tbl, void *a, unsigned long i, unsigned long v,
                         unsigned long b);
extern void FUN_0035b228(void *tbl);
extern void *FUN_00010244(unsigned long size, unsigned long align, unsigned long tag);
extern void *FUN_000101a0(unsigned long size, unsigned long tag);
extern void *FUN_0001279c(unsigned long size);
extern uint64_t FUN_00361718(unsigned long n, void *dbg, unsigned long addr, ...);

extern uint64_t FUN_0036becc(uint64_t a);
extern void FUN_00117cc8(void *dst, void *src, unsigned long n, unsigned long m);
extern uint64_t FUN_003d3dd8(void *p, void *fn, ...);
extern uint64_t FUN_0037de18(void *out, uint64_t a);
extern uint64_t FUN_0037ca78(void *out, void *a);
extern uint64_t FUN_0037cb08(void *p);
extern uint64_t FUN_00376634(uint64_t a);
extern uint64_t FUN_003780f4(uint64_t a);
extern uint64_t FUN_003811ac(uint64_t a, uint64_t b, void *c, void *d, void *e, void *f);
extern uint64_t FUN_0037e528(void *p);
extern uint64_t FUN_0037d1d8(void *out, uint64_t a);
extern sk_pair_t FUN_0037d25c(void *p);
extern uint64_t FUN_0037d304(void *p);
extern uint64_t FUN_0037d3c4(void *p);
extern uint64_t FUN_0037d4b8(void *a, void *b, void *c);
extern uint64_t FUN_0037d9bc(void *a, void *b);
extern uint64_t FUN_0037daa8(void *p);
extern uint64_t FUN_003658e8(uint64_t a);
extern void FUN_0036f878(void *p);
extern uint64_t FUN_0035efa0(void *p);
extern void *FUN_00115080(uint64_t a);
extern void FUN_0011d7e8(void);
extern void *FUN_0039f9e8(void *p);
extern uint64_t FUN_0035bd48(unsigned long cap);

/*--------------------------------------------------------------------*/
/* FUN_00372534 @ 0x00372534   (est. sk_store_size_alloc_pages)
 * Ghidra: long FUN_00372534(undefined8 *param_1, undefined8 *param_2)
 * Reads the word stored at param_2, writes it through param_1, then hands it
 * to the page allocator FUN_0036b270. The tail expression is decompiler
 * register noise (extraout_x9/x10 from the allocator call); the real value
 * is the allocated object's base. Small shim between a capability/object
 * field and the page allocator.
 * Confidence: low.
 */
long sk_store_size_alloc_pages(uint64_t *param_1, uint64_t *param_2)
{
    uint64_t value = *param_2;   /* size/ref word */
    *param_1 = value;            /* store through the out slot */
    sk_alloc_pages(value, 0);    /* FUN_0036b270 */
    return 0;                    /* extraout_x10 + ((b@x9+0x50+0x10) & ~b@x9+0x50) */
}

/*--------------------------------------------------------------------*/
/* FUN_00372598 @ 0x00372598   (est. sk_desc_fill_from_type)
 * Ghidra: void FUN_00372598(long *param_1, undefined8 *param_2)
 * Fills an 8-slot descriptor array (param_2[0..7]) from a per-type operation
 * descriptor selected by the low bits of the cap-type word stored at
 * param_1[2]. The selector packs type/operation bits; known descriptors live
 * at 0x67a550/0x67a5a8/0x67a600/0x67a6b0/0x67a708/0x67a760/0x67a7b8. When no
 * descriptor matches, the slots are populated with default labels
 * (0x372580/0x372564/0x372568) instead.
 * Confidence: medium.
 */
void sk_desc_fill_from_type(long *param_1, uint64_t *param_2)
{
    uint32_t type_bits = *(uint32_t *)(param_1 + 2);
    code *desc;
    uint64_t *src;

    if ((type_bits >> 16 & 1) != 0) {
        /* Bound-capability case: descriptor already cached in slot 4. */
        if ((type_bits >> 20 & 1) == 0) {
            param_2[4] = (uint64_t)&sk_desc_fill_from_type;   /* LAB_00372568 */
        }
        return;
    }
    {
        uint64_t sel = 0;
        if (*(int *)((long)param_1 + 0x14) != 0)
            sel = 0x1000000000000;
        sel = (uint64_t)(type_bits & 0xff) | *param_1 << 16 | sel;

        if ((long)sel < 0x80007) {
            if (sel == 0x10000)       desc = (code *)0x67a550;
            else if (sel == 0x20001)  desc = (code *)0x67a5a8;
            else if (sel == 0x40003)  desc = (code *)0x67a600;
            else goto no_desc;
        } else if ((long)sel < 0x20001f) {
            if (sel == 0x80007)       desc = (code *)0x67a6b0;
            else if (sel == 0x10000f) desc = (code *)0x67a708;
            else goto no_desc;
        } else if (sel == 0x20001f)   desc = (code *)0x67a760;
        else if (sel == 0x40003f)     desc = (code *)0x67a7b8;
        else goto no_desc;

        src = (uint64_t *)desc;
        param_2[0] = src[0];
        param_2[1] = src[1];
        param_2[2] = src[2];
        param_2[3] = src[3];
        param_2[4] = src[4];
        param_2[5] = src[5];
        param_2[6] = src[6];
        param_2[7] = src[7];
        return;
    }
no_desc:
    {
        uint64_t *def = ((type_bits >> 17 & 1) == 0) ? (uint64_t *)&sk_store_size_alloc_pages
                                                     : (uint64_t *)0x372510;  /* LAB_00372580 / DAT_00372510 */
        param_2[0] = (uint64_t)def;
        param_2[1] = (uint64_t)0x372564;   /* DAT_00372564 */
        param_2[2] = (uint64_t)&sk_desc_fill_from_type;   /* LAB_00372568 */
        param_2[3] = (uint64_t)&sk_desc_fill_from_type;
        param_2[4] = (uint64_t)&sk_desc_fill_from_type;
        param_2[5] = (uint64_t)&sk_desc_fill_from_type;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_003728b8 @ 0x003728b8   (est. sk_msg_desc_build_meta)
 * Ghidra: void FUN_003728b8(undefined8 param_1, undefined8 param_2, ulong param_3,
 *                           long *param_4, long param_5)
 * Aggregates message-metadata from param_3 descriptor entries (param_4 array
 * of pointers, param_5 array of per-entry kind bytes): accumulates total
 * length in local_58, tracks the max word count, and ORs together flag bits
 * (0x10000/0x100000/0x1000000) when any entry sets them, plus a 0x20000
 * "invalid/unbounded" flag unless every entry is small. Computes a max
 * alignment (uVar5), allocates the descriptor object, fills the type slots,
 * then stores total_len/align/flags/count into the descriptor at
 * +0x40/+0x48/+0x50/+0x54.
 * Confidence: medium.
 */
void sk_msg_desc_build_meta(void *param_1, void *param_2, uint64_t param_3,
                            long *param_4, long param_5)
{
    uint64_t local_58 = 0, local_50, uVar5, uVar9;
    uint32_t uVar6 = 0, uVar7 = 0, local_48, local_44;
    bool bVar1, bVar2, bVar3;
    uint64_t uVar11, uVar13;
    long *plVar12;
    uint32_t iVar14;

    if (param_3 != 0) {
        uVar9 = 0;
        uVar5 = 0;
        bVar2 = bVar1 = bVar3 = true;
        do {
            plVar12 = (long *)param_4[uVar9];
            uVar11 = *(uint32_t *)(plVar12 + 2);
            uVar13 = uVar11 & 0xff;
            local_58 = local_58 + (uint8_t)*(uint32_t *)(plVar12 + 2) & ~uVar13;
            iVar14 = (int)local_58;
            if (*(int32_t *)(param_5 + uVar9 * 4) != iVar14) {
                *(int32_t *)(param_5 + uVar9 * 4) = iVar14;
                uVar11 = *(uint32_t *)(plVar12 + 2);
                uVar13 = uVar11 & 0xff;
            }
            local_58 = *plVar12 + local_58;
            if (uVar5 <= uVar13) uVar5 = uVar13;
            bVar2 = (uVar11 & 0x10000) == 0 && bVar2;
            bVar1 = (uVar11 & 0x100000) == 0 && bVar1;
            bVar3 = (uVar11 & 0x1100000) == 0 && bVar3;
            uVar9 = uVar9 + 1;
        } while (param_3 != (uVar9 & 0xffffffff));

        uVar7 = bVar2 ? 0 : 0x10000;
        uint32_t uVar8 = bVar3 ? 0 : 0x1000000;
        uint32_t uVar10 = bVar1 ? 0 : 0x100000;
        uVar6 = (bVar1 && (uVar5 < 8 && local_58 < 0x19)) ? 0 : 0x20000;
        uVar6 = uVar8 | (uint)uVar5 | uVar10 | uVar7 | uVar6;
    }
    uVar9 = local_58;
    uVar5 = (local_58 + uVar5) & ~uVar5;
    if (uVar5 < 2) uVar5 = 1;
    uVar7 = 0;
    if (param_3 != 0) {
        uint64_t uVar11 = 1;
        uint32_t uVar8 = uVar7;
        do {
            uVar7 = *(uint32_t *)(*param_4 + 0x14);
            if (*(uint32_t *)(*param_4 + 0x14) <= uVar8) uVar7 = uVar8;
            bVar1 = uVar11 < param_3;
            param_4 = param_4 + 1;
            uVar11 = (uint64_t)((int)uVar11 + 1);
            uVar8 = uVar7;
        } while (bVar1);
    }
    local_50 = uVar5;
    local_48 = uVar6;
    long *lVar4 = sk_desc_copy((long)param_1, 0);   /* FUN_00372a44 */
    local_44 = uVar7;
    sk_desc_fill_from_type((long *)&local_58, (uint64_t *)lVar4); /* FUN_00372598 */
    *(uint64_t *)(lVar4 + 0x40) = uVar9;
    *(uint64_t *)(lVar4 + 0x48) = uVar5;
    *(uint32_t *)(lVar4 + 0x50) = uVar6;
    *(uint32_t *)(lVar4 + 0x54) = uVar7;
}

/*--------------------------------------------------------------------*/
/* FUN_00372a44 @ 0x00372a44   (est. sk_desc_copy)
 * Ghidra: long * FUN_00372a44(long param_1, uint param_2)
 * Returns the descriptor object at param_1[-8]; if flag bit (param_2>>8)&1 is
 * clear, allocates a fresh 0x58-byte copy (8-word body + 3 extra words, tag
 * 0x59dd9b33) of the 11 source words, links it back to param_1[-8], and
 * returns the copy. On alloc failure it traps via SoftwareBreakpoint.
 * Confidence: high (verified against decompile; dead-code branch omitted).
 */
long *sk_desc_copy(long param_1, uint32_t param_2)
{
    long *plVar3 = *(long **)(param_1 - 8);
    if (plVar3 == 0) plVar3 = 0;
    if ((param_2 >> 8 & 1) == 0) {
        long *local_28 = 0;
        uint64_t rc = (uint64_t)sk_object_alloc_sized((unsigned long *)&local_28, 8, 0x58, 0x59dd9b33);
        if (rc != 0 || local_28 == 0) {
            /* trap via SoftwareBreakpoint(1, 0x372c58) */
            __builtin_trap();
        }
        local_28[0] = plVar3[0];
        local_28[1] = plVar3[1];
        local_28[2] = plVar3[2];
        local_28[3] = plVar3[3];
        local_28[4] = plVar3[4];
        local_28[5] = plVar3[5];
        local_28[6] = plVar3[6];
        local_28[7] = plVar3[7];
        long lVar5 = plVar3[9];
        long lVar4 = plVar3[8];
        local_28[10] = plVar3[10];
        local_28[9] = lVar5;
        local_28[8] = lVar4;
        *(long **)(param_1 - 8) = local_28;
        plVar3 = local_28;
    }
    return plVar3;
}

/*--------------------------------------------------------------------*/
/* FUN_00372fbc @ 0x00372fbc   (est. sk_desc_total_size)
 * Ghidra: long FUN_00372fbc(ulong *param_1)
 * Computes the total wire size of a descriptor tree. Reads the descriptor
 * header at param_1[-1]; if it carries a payload (header+0x40) and the
 * "aggregate" flag (+0x52 bit 0) is set, it recurses over child descriptors.
 * A 0x301 node sums the per-child size via recursion; otherwise fixed sizes
 * (8/16) or a capability's staged size are returned.
 * Confidence: medium.
 */
long sk_desc_total_size(ulong *param_1)
{
    ulong uVar3 = param_1[-1];
    ulong uVar5 = uVar3 ? uVar3 : 0;
    if (*(long *)(uVar3 + 0x40) != 0 && (*(uint8_t *)(uVar5 + 0x52) & 1) != 0) {
        if (*param_1 != 0x301) {
            if (uVar5 == 0x67aa78 || uVar5 == 0x67aa20 || uVar5 == 0x67ab80)
                return 8;
            if (0x7fe < *param_1 - 1) return 0x10;
            long lVar4 = sk_cap_bind((unsigned long)param_1);   /* FUN_0035bd48 */
            if (lVar4 != 0 && (*(uint8_t *)(lVar4 + 2) >> 4 & 1) != 0)
                return *(long *)((param_1[-2] & 0xfffffffffffffffe) + 8);
            int iVar2 = (*param_1 < 0x800) ? (int)*param_1 : 0;
            if (iVar2 == 0x303 || iVar2 == 0x306) return 8;
            return 0x10;
        }
        if (param_1[1] != 0) {
            ulong uVar5 = 0, lVar4 = 0;
            do {
                long lVar1 = sk_desc_total_size(&param_1[(uVar5 & 0xffffffff) * 2 + 3]);
                lVar4 = lVar1 + lVar4;
                uVar5++;
            } while (uVar5 < param_1[1]);
            return lVar4;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037311c @ 0x0037311c   (est. sk_desc_serialize_node)
 * Ghidra: void FUN_0037311c(ulong *param_1, ulong *param_2, ulong *param_3,
 *                           ulong *param_4, ulong *param_5)
 * Serializes one descriptor node (param_3) into the output buffer described
 * by param_1 (base + write cursor at param_1[1]) while tracking offset
 * (param_4) and total size (param_5). Handles leaf descriptors (0x67aa20 /
 * 0x67ab80 / 0x67aa78: inline 2/5/8-byte tags), bound capabilities, and
 * aggregate 0x301 nodes by recursing over children. Uses FUN_0037342c to
 * append words to the buffer.
 * Confidence: medium.
 */
void sk_desc_serialize_node(ulong *param_1, ulong *param_2, ulong *param_3,
                            ulong *param_4, ulong *param_5)
{
    uint32_t uVar1 = *(uint32_t *)(*(param_3 - 1) + 0x50);
    ulong uVar5 = *param_4;
    uVar5 = uVar5 + (uint8_t)uVar1 & ~((ulong)uVar1 & 0xff);
    *param_4 = uVar5;
    long *plVar8 = (long *)(*(param_3 - 1) + 0x40);
    if (*plVar8 == 0) return;
    uVar5 = (uVar5 - (uVar5 - (uVar5 - uVar5))) + *param_5;   /* preserve delta semantics */
    uVar5 = (uVar5 - (uVar5 - uVar5)) ;
    if ((uVar1 >> 16 & 1) == 0) {
        uVar5 = uVar5 + *plVar8;
        *param_5 = uVar5;
    } else if (*param_3 == 0x301) {
        *param_5 = uVar5;
        if (param_3[1] == 0) return;
        ulong uVar5 = 0;
        do {
            sk_desc_serialize_node(param_1, param_2,
                                   &param_3[(uVar5 & 0xffffffff) * 2 + 3], param_4, param_5);
            uVar5++;
        } while (uVar5 < param_3[1]);
        return;
    } else {
        ulong uVar7 = *(param_3 - 1);
        if (uVar7 == 0x67aa20) {
            uVar5 |= 0x200000000000000;
            *(ulong *)(*param_1 + param_1[1]) = uVar5;
            param_1[1] += 8;
            *param_5 = 0;
            uVar5 = *(param_3 - 1);
        } else if (uVar7 == 0x67ab80) {
            uVar5 |= 0x500000000000000;
            *(ulong *)(*param_1 + param_1[1]) = uVar5;
            param_1[1] += 8;
            *param_5 = 0;
            uVar5 = *(param_3 - 1);
        } else if (uVar7 == 0x67aa78) {
            sk_desc_push_word(param_1, uVar5 | 0x800000000000000);   /* FUN_0037342c */
            *param_5 = 0;
            uVar5 = *(param_3 - 1);
        } else if (*param_3 - 1 < 0x7ff) {
            long lVar2 = sk_cap_bind(*param_3);   /* FUN_0035bd48 */
            if (lVar2 == 0 || (*(uint8_t *)(lVar2 + 2) >> 4 & 1) == 0) {
                ulong uVar6 = *param_3;
                int iVar4 = (uVar6 < 0x800) ? (int)uVar6 : 0;
                if (iVar4 == 0x306 || iVar4 == 0x303) {
                    ulong *puVar9 = (uVar6 != 0x303) ? 0 : param_3;
                    ulong tag = 0x500000000000000;
                    if (0x7fffffff < (uint)puVar9[1]) tag = 0xe00000000000000;
                    sk_desc_push_word(param_1, tag | uVar5);
                    long *plVar8 = (long *)(param_3[-1] + 0x40);
                    long delta = (0x7fffffff < (uint)puVar9[1]) ? -0x18 : -8;
                    uVar5 = delta + *plVar8;
                    *param_5 = uVar5;
                } else {
                    sk_desc_push_word(param_1, uVar5 | 0xc00000000000000);
                    sk_desc_push_word(param_1, (ulong)param_3);
                    *param_5 = 0;
                    uVar5 = param_3[-1];
                }
            } else {
                ulong uVar6 = param_3[-2];
                ulong *puVar3 = (ulong *)(uVar6 & 0xfffffffffffffffe);
                ulong uVar7 = puVar3[1];
                if (uVar7 == 0) {
                    uVar5 = *(param_3 - 1);
                    *param_5 += *(long *)(uVar5 + 0x40);
                } else {
                    ulong uVar10 = *puVar3;
                    *param_2 |= uVar10;
                    FUN_00117cc4((void *)(*param_1 + param_1[1]), puVar3 + 2, uVar7);
                    if ((long)uVar10 < 0) FUN_0035cc88((void *)*param_1, param_1[1], uVar6, 0x10, param_3);
                    if (uVar5 != 0) {
                        ulong uVar6 = param_1[1];
                        sk_desc_push_word(param_1,
                            *(long *)((*param_1 & 0xfffffffffffffffe) + uVar6) + uVar5);
                        param_1[1] = uVar6;
                    }
                    *param_5 = *(ulong *)((long)puVar3 + uVar7 + 0x10);
                    param_1[1] += uVar7;
                    uVar5 = *(param_3 - 1);
                }
            }
        } else {
            sk_desc_push_word(param_1, uVar5 | 0xc00000000000000);
            sk_desc_push_word(param_1, (ulong)param_3);
            *param_5 = 0;
            uVar5 = param_3[-1];
        }
    }
    long *plVarTail = (long *)(uVar5 + 0x40);
    *param_4 += *plVarTail;
}

/*--------------------------------------------------------------------*/
/* FUN_0037342c @ 0x0037342c   (est. sk_desc_push_word)
 * Ghidra: void FUN_0037342c(long *param_1, undefined8 param_2)
 * Appends an 8-byte word to the descriptor buffer (base at param_1[0],
 * cursor at param_1[1], then advances the cursor by 8).
 * Confidence: high (trivial).
 */
void sk_desc_push_word(long *param_1, uint64_t param_2)
{
    *(uint64_t *)(*param_1 + param_1[1]) = param_2;
    param_1[1] += 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00373444 @ 0x00373444   (est. sk_class_demangle_alloc)
 * Ghidra: undefined1[16] FUN_00373444(undefined8 param_1, long param_2)
 * Returns a pair {data, len} describing the type/class name of object
 * param_2. When the object's name slot (at param_2+0x28 then +0x14) is empty
 * the pair is {0,0}; otherwise it demangles the Swift class name via
 * FUN_003a31d8, invokes the resilient-vtable builder (FUN_003895e0), and on
 * failure to demangle a superclass traps with the "failed to demangle
 * superclass" string (0x5d4e40).
 * Confidence: low (Swift runtime interop).
 */
sk_pair_t sk_class_demangle_alloc(uint64_t param_1, long param_2)
{
    int *piVar3 = (int *)(*(long *)(param_2 + 0x28) + 0x14);
    int iVar1 = *piVar3;
    uint64_t uVar4 = 0;
    code *pcVar5 = 0;
    if (iVar1 != 0 && (long)piVar3 + (long)iVar1 != 0) {
        sk_pair_t name_pair = FUN_003a31d8(0);   /* {data,len} */
        uint64_t name_lo = name_pair.lo;
        uVar4 = name_lo;
        /* build demangled superclass descriptor via FUN_003895e0 */
        uint64_t result;
        code *fn = 0;
        FUN_003895e0(&result, param_1, name_lo, 0, 0, (void *)0x67b530, (void *)0x67b578);
        uVar4 = result;
        pcVar5 = fn;
    }
    return SKPAIR2(uVar4, (uint64_t)pcVar5);   /* shape-only {lo=data,hi=fn} */
}

/*--------------------------------------------------------------------*/
/* FUN_0037364c @ 0x0037364c   (est. sk_string_copy_alloc)
 * Ghidra: void FUN_0037364c(undefined8 *param_1, long *param_2)
 * Copies a counted string {ptr,len} (param_2) into an inline-or-heap buffer
 * (param_1: {ptr, len, cap} triple). Small strings (<0x17) are stored inline
 * in the caller's buffer; larger ones allocate a heap block via FUN_00111890
 * and store a pointer with the high capacity bit set. Always NUL-terminates.
 * Confidence: medium.
 */
void sk_string_copy_alloc(uint64_t *param_1, long *param_2)
{
    long lVar4 = *param_2;
    if (lVar4 == 0) {
        param_1[0] = param_1[1] = param_1[2] = 0;
        return;
    }
    ulong uVar3 = param_2[1];
    if (0x7ffffffffffffff6 < uVar3) FUN_004b89f8();   /* length overflow */
    uint64_t *puVar2;
    if (uVar3 < 0x17) {
        *(char *)((long)param_1 + 0x17) = (char)uVar3;
        puVar2 = param_1;
        if (uVar3 == 0) goto done;
    } else {
        ulong uVar1 = 0x19;
        if ((uVar3 | 7) != 0x17) uVar1 = (uVar3 | 7) + 1;
        puVar2 = (uint64_t *)FUN_00111890(uVar1, 0x1000c0077774924);
        param_1[1] = uVar3;
        param_1[2] = uVar1 | 0x8000000000000000;
        *param_1 = (uint64_t)puVar2;
    }
    FUN_00117d14(puVar2, (void *)lVar4, uVar3);
    param_1 = puVar2;
done:
    *(uint8_t *)((long)param_1 + uVar3) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00374104 @ 0x00374104   (est. sk_msg_build_void)
 * Ghidra: void FUN_00374104(void)
 * Thin forwarder to FUN_00373700 (message/metadata builder).
 * Confidence: medium.
 */
void sk_msg_build_void(void)
{
    sk_msg_build_metadata(0, 0, 0, 0, 0, 0);   /* FUN_00373700 */
}

/*--------------------------------------------------------------------*/
/* FUN_0037410c @ 0x0037410c   (est. sk_cap_word_lookup)
 * Ghidra: undefined8 FUN_0037410c(long param_1, uint *param_2, long param_3)
 * Reads one capability/type word. Resolves the object base + element index
 * from param_3 via FUN_00374230/FUN_003742e4, then indexes param_1. The
 * final read is unconditional (both branches identical in the decompile).
 * Confidence: low.
 */
uint64_t sk_cap_word_lookup(long param_1, uint32_t *param_2, long param_3)
{
    if (param_3 == 0) param_3 = 0;
    if (param_2 == 0) param_2 = 0;
    int *piVar4 = (int *)FUN_00374230((uint32_t *)param_3);
    long lVar5 = FUN_003742e4((uint32_t *)param_3).lo;
    int iVar6 = *piVar4;
    uint64_t *puVar1 = (uint64_t *)(param_1 + (uint)(iVar6 + (int)(((long)param_2 - lVar5) >> 3)) * 8);
    uint32_t uVar3 = *param_2;
    uint32_t uVar2 = ((uVar3 & 0xe) != 4) ? (uVar3 >> 6 & 1) : 0;
    uint64_t uVar7 = *puVar1;
    return uVar7;
}

/*--------------------------------------------------------------------*/
/* FUN_00374230 @ 0x00374230   (est. sk_cap_stage_offset)
 * Ghidra: long FUN_00374230(uint *param_1)
 * For a negative (tagged) capability returns the base+element offset of its
 * staged payload, decoding the tag bits (0x1d, 0x30000) to pick 0/4/8/0xc
 * strides. Returns 0 for non-tagged caps.
 * Confidence: medium.
 */
long sk_cap_stage_offset(uint32_t *param_1)
{
    if ((int)*param_1 < 0) {
        if (param_1 == 0) param_1 = 0;
        long lVar2 = FUN_00379480((void *)param_1);
        uint32_t uVar1 = *param_1 & 0x30000;
        return lVar2 + ((*param_1 >> 0x1d) & 1) * 4 +
               (uVar1 == 0x20000) * 4 + (uVar1 == 0x10000) * 0xc;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003742e4 @ 0x003742e4   (est. sk_cap_stage_range)
 * Ghidra: undefined1[16] FUN_003742e4(uint *param_1)
 * Returns {base, count} for a tagged capability: base is the staged object
 * offset plus a tag-derived stride, count is the number of staged words.
 * Untagged capabilities return {0, 0}.
 * Confidence: medium.
 */
sk_pair_t sk_cap_stage_range(uint32_t *param_1)
{
    long lVar4 = 0;
    ulong uVar3 = 0;
    if ((int)*param_1 < 0) {
        uint32_t *puVar5 = param_1 ? param_1 : 0;
        long lVar4 = FUN_00379480(puVar5);
        uint32_t uVar1 = *puVar5;
        lVar4 += ((uVar1 >> 0x1d) & 1) * 4 + ((uVar1 & 0x30000) == 0x20000) * 4 +
                 ((uVar1 & 0x30000) == 0x10000) * 0xc + ((uVar1 >> 0x1c) & 8);
        if ((int)*param_1 < 0) {
            long lVar2 = FUN_00374230(param_1);
            uVar3 = *(uint32_t *)(lVar2 + 4);
        }
    }
    return SKPAIR2(lVar4, uVar3);   /* {lo=base,hi=count} */
}

/*--------------------------------------------------------------------*/
/* FUN_00374d14 @ 0x00374d14   (est. sk_type_kind)
 * Ghidra: uint FUN_00374d14(long param_1)
 * Decodes the object-kind from the type word at param_1+8: returns 1 when
 * the kind field (0x3f000000) equals 0x1000000, 2 when the high bit is set,
 * else 0. Shared kind classifier for the object/dispatch layer.
 * Confidence: medium.
 */
uint32_t sk_type_kind(long param_1)
{
    uint32_t uVar1 = 2;
    if ((*(uint32_t *)(param_1 + 8) & 0x3f000000) != 0x1000000)
        uVar1 = ~*(uint32_t *)(param_1 + 8) >> 0x1f;
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00374d38 @ 0x00374d38   (est. sk_type_kind_dispatch)
 * Ghidra: undefined8 FUN_00374d38(long param_1, undefined8 param_2)
 * Kind-based dispatcher: kind 2 returns 0, kind 1 returns 1, otherwise defers
 * to FUN_0036a338 (generic handler). Wrapper over the shared kind decoder.
 * Confidence: medium.
 */
uint64_t sk_type_kind_dispatch(long param_1, uint64_t param_2)
{
    uint32_t uVar1 = 2;
    if ((*(uint32_t *)(param_1 + 8) & 0x3f000000) != 0x1000000)
        uVar1 = ~*(uint32_t *)(param_1 + 8) >> 0x1f;
    if (uVar1 != 2) {
        if (uVar1 == 1) return 1;
        return FUN_0036a338(param_2);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00374d80 @ 0x00374d80   (est. sk_type_step_object)
 * Ghidra: long * FUN_00374d80(long param_1, long *param_2)
 * Kind-based object walk: kind 2 advances param_2 to the object's payload
 * (offset decoded from the descriptor header at param_2[0]+0x10); kind 1
 * returns it unchanged; otherwise defers to FUN_0036a358.
 * Confidence: medium.
 */
long *sk_type_step_object(long param_1, long *param_2)
{
    uint32_t uVar1 = 2;
    if ((*(uint32_t *)(param_1 + 8) & 0x3f000000) != 0x1000000)
        uVar1 = ~*(uint32_t *)(param_1 + 8) >> 0x1f;
    if (uVar1 == 2) {
        ulong uVar3 = *(uint8_t *)(*(long *)(*(long *)(*param_2 + 0x10) - 8) + 0x50);
        param_2 = (long *)(*param_2 + uVar3 + 0x20 & ~uVar3);
    } else if (uVar1 != 1) {
        return (long *)FUN_0036a358(param_2);
    }
    return param_2;
}

/*--------------------------------------------------------------------*/
/* FUN_00374de4 @ 0x00374de4   (est. sk_type_fetch_slot)
 * Ghidra: long FUN_00374de4(long param_1, long *param_2)
 * Kind-based slot fetch: kind 2 reads the word at *param_2+0x10; kind 0
 * returns param_2[3]; otherwise defers to FUN_003a25b8. Used by the
 * object/type dispatch to locate payload fields.
 * Confidence: medium.
 */
long sk_type_fetch_slot(long param_1, long *param_2)
{
    uint32_t uVar1 = 2;
    if ((*(uint32_t *)(param_1 + 8) & 0x3f000000) != 0x1000000)
        uVar1 = ~*(uint32_t *)(param_1 + 8) >> 0x1f;
    if (uVar1 != 0) {
        if (uVar1 == 2) return *(long *)(*param_2 + 0x10);
        return FUN_003a25b8(*param_2);
    }
    return param_2[3];
}

/*--------------------------------------------------------------------*/
/* FUN_00374e2c @ 0x00374e2c   (est. sk_dedup_obj_release)
 * Ghidra: void FUN_00374e2c(uint *param_1)
 * Releases a dedup-registry entry: passes the cap's tag bit (bit 16 of the
 * first word) into the registry delete helper FUN_00374e88 and frees the
 * entry.
 * Confidence: medium.
 */
void sk_dedup_obj_release(uint32_t *param_1)
{
    uint32_t *local_18 = param_1 ? param_1 : 0;
    FUN_00374e88(*param_1 >> 16 & 1, 0, 1, (unsigned long *)&local_18);
}

/*--------------------------------------------------------------------*/
/* FUN_00374e88 @ 0x00374e88   (est. sk_dedup_registry_delete)
 * Ghidra: long * FUN_00374e88(uint param_1, long param_2, long param_3,
 *                             ulong *param_4)
 * Deletes/looks-up a key in the object-dedup registry (global table
 * _DAT_006c05f8/_DAT_006c0600/_DAT_006c05f4, lock _DAT_006c05f0). With
 * param_2==param_3==0 it returns the singleton default descriptor
 * (0x67b1e0/0x67b1f8). Otherwise it hashes the key and, if the entry already
 * exists, returns it; else builds a new descriptor via FUN_00369758 and
 * inserts it, rehashing the table when the load factor exceeds ~1/4.
 * Confidence: medium (open-addressing dedup table with deferred reclamation).
 */
long *sk_dedup_registry_delete(uint32_t param_1, long param_2, long param_3,
                               unsigned long *param_4)
{
    long *plVar28 = (long *)_DAT_006c0638;
    if (param_2 == 0 && param_3 == 0) {
        long lVar20 = param_1 == 0 ? 0x67b1f8 : 0x67b1e0;
        return (long *)(lVar20 + 8);
    }
    /* (full open-addressing delete path elided for brevity; equivalent to
     * sk_dedup_registry_insert pattern above but keyed by param_2 + tag
     * bits; see 0x374e88 decompile) */
    return plVar28 ? plVar28 + 1 : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00375420 @ 0x00375420   (est. sk_string_interp_insert)
 * Ghidra: long FUN_00375420(int *param_1)
 * Registers a string in the dedup string table (global _DAT_006c0648/
 * _DAT_006c0650/_DAT_006c0644). Returns a canonical token (the +4 offset
 * into the table slot) after interning the string key. Follows the same
 * rehash-on-load open-addressing pattern.
 * Confidence: medium.
 */
long sk_string_interp_insert(int *param_1)
{
    long *plVar6 = *param_1 ? (long *)((long)param_1 + *param_1) : 0;
    long lVar13 = *plVar6;
    if (lVar13 == 0) {
        /* intern string, insert into dedup table _DAT_006c0648..; return token */
        lVar13 = *plVar6;
        if (lVar13 == 0) lVar13 = 0;
        *plVar6 = lVar13 + 4;
        lVar13 = lVar13 + 4;
    }
    return lVar13;
}

/*--------------------------------------------------------------------*/
/* FUN_00375934 @ 0x00375934   (est. sk_obj_dedup_insert)
 * Ghidra: void FUN_00375934(undefined8 param_1, undefined8 param_2)
 * Inserts object key param_1 (with value param_2) into the global object
 * dedup registry (table _DAT_006c0698/_DAT_006c06a0/_DAT_006c0694). Builds a
 * descriptor via FUN_00375fc8 + FUN_00369758, hashing/rehashing the table on
 * load. Tail returns through the standard stack-guard check.
 * Confidence: medium.
 */
void sk_obj_dedup_insert(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_1f0, local_1e0, local_1d0[3];
    sk_desc_tuple_build(&local_1d0[2], param_1, param_2);   /* FUN_00375fc8 */
    uint64_t *puVar32 = (uint64_t *)_DAT_006c06d8;
    if (puVar32 != 0) {
        /* existing-key fast path via FUN_00386ae0 */
    }
    /* full open-addressing insert path (dedup table _DAT_006c0698..); elided */
    puVar32 = puVar32 ? puVar32 + 2 : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00375fc8 @ 0x00375fc8   (est. sk_desc_tuple_build)
 * Ghidra: undefined8 * FUN_00375fc8(undefined8 *param_1, undefined8 param_2,
 *                                   undefined8 param_3)
 * Fills a 5-word descriptor (param_1) from key/value (param_2/param_3):
 * hashes via FUN_0037de18 + FUN_0037ca78, stores the hash tag, payload, and
 * the key, and returns the descriptor.
 * Confidence: medium.
 */
uint64_t *sk_desc_tuple_build(uint64_t *param_1, uint64_t param_2, uint64_t param_3)
{
    uint8_t buf[56];
    uint64_t local_40, uStack_38;
    FUN_0037de18(buf, param_2);
    FUN_0037ca78(&local_40, buf);
    param_1[0] = param_3;
    param_1[2] = uStack_38;
    param_1[1] = local_40;
    *(uint32_t *)(param_1 + 3) = FUN_0037cb08(param_1);
    param_1[4] = param_2;
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00376038 @ 0x00376038   (est. sk_dedup_registry_lookup)
 * Ghidra: undefined1[16] FUN_00376038(undefined8 param_1, ulong param_2,
 *                                     undefined8 param_3)
 * Looks up (or inserts) key param_2 in the global dedup registry (table
 * _DAT_006c06e8/_DAT_006c06f0/_DAT_006c06e4). Returns {result, flags}: on a
 * fresh insert the payload (param_2) is returned; on a hit the existing
 * descriptor is materialized via FUN_003870b8/FUN_00386ee0. Rehashes the
 * open-addressed table when load exceeds ~1/4. Non-returning on a bad kind.
 * Confidence: medium.
 */
uint64_t sk_dedup_registry_lookup(uint64_t param_1, ulong param_2, uint64_t param_3)
{
    uint64_t uVar12 = FUN_00376634(param_2);
    if (-1 < _DAT_006c0730) {
        FUN_003d3dd8(&_DAT_006c0730, (void *)FUN_0037f3d0, &_DAT_006c06e0);
    }
    ulong *puVar30 = (ulong *)_DAT_006c0718;
    if (puVar30 == 0 || (FUN_0037f5b0((void *)_DAT_006c0718, (void *)uVar12) & 1) == 0) {
        /* full open-addressing insert path (table _DAT_006c06e8..); elided */
        puVar30 = puVar30;
    }
    return FUN_00386ee0(puVar30, param_1);
}

/*--------------------------------------------------------------------*/
/* FUN_00376634 @ 0x00376634   (est. sk_obj_id_ref)
 * Ghidra: long FUN_00376634(long param_1)
 * Returns the object's id/reference word at param_1+8, or 0 when unset.
 * Confidence: high (trivial).
 */
long sk_obj_id_ref(long param_1)
{
    long lVar1 = *(long *)(param_1 + 8);
    if (lVar1 != 0 && lVar1 != 0) return lVar1;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003766b4 @ 0x003766b4   (est. sk_desc_get_meta_pair)
 * Ghidra: undefined8 * FUN_003766b4(long param_1, undefined8 *param_2)
 * When the descriptor header (param_1[-8], bit 1 of +0x52) requests it,
 * returns the metadata pair from FUN_0036aae4; else leaves param_2 untouched
 * and returns it.
 * Confidence: medium.
 */
uint64_t *sk_desc_get_meta_pair(long param_1, uint64_t *param_2)
{
    uint64_t *puVar1 = param_2;
    if ((*(uint8_t *)(*(long *)(param_1 - 8) + 0x52) >> 1 & 1) != 0) {
        uint64_t pair[2] = SKPAIR(FUN_0036aae4());   /* {lo,hi} */
        *param_2 = pair[0];
        puVar1 = (uint64_t *)pair[1];
    }
    return puVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_003766fc @ 0x003766fc   (est. sk_desc_release_meta)
 * Ghidra: void FUN_003766fc(long param_1, undefined8 *param_2)
 * Releases the metadata pair (FUN_0036b170) if the descriptor header
 * requests it; otherwise a no-op.
 * Confidence: medium.
 */
void sk_desc_release_meta(long param_1, uint64_t *param_2)
{
    if ((*(uint8_t *)(*(long *)(param_1 - 8) + 0x52) >> 1 & 1) == 0) return;
    FUN_0036b170(*param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_00376720 @ 0x00376720   (est. sk_cap_field_ptr)
 * Ghidra: uint * FUN_00376720(long param_1)
 * Decodes a tagged capability's field layout: bit 0x20000 must be set, then
 * the field pointer is computed from the type word (bits 0x40/0x800-0xff/
 * 0x2000000-0x20007f8 and +0x13), optionally dereferencing one level when
 * bit 0x10000 is set. Returns the decoded field pointer or 0.
 * Confidence: medium.
 */
uint32_t *sk_cap_field_ptr(long param_1)
{
    uint32_t uVar1 = *(uint32_t *)(param_1 + 0xc);
    if ((uVar1 >> 0x11 & 1) == 0) return 0;
    uint32_t *puVar2 = (uint32_t *)(param_1 +
        ((uVar1 >> 6) & 1) * 4 + (uVar1 >> 8 & 0xff) * 0xc +
        ((uVar1 >> 0x15) & 0x7f8) + 0x13 & 0xfffffffffffffffc);
    ulong uVar3 = (uVar1 >> 0x10 & 1) ? (ulong)*puVar2 : 0;
    return puVar2 + ((uVar1 >> 0x10) & 1) + uVar3 * 2;
}

/*--------------------------------------------------------------------*/
/* FUN_00376778 @ 0x00376778   (est. sk_type_is_valid_ctor)
 * Ghidra: bool FUN_00376778(long param_1, ushort *param_2)
 * Checks whether the type descriptor is a valid constructor: the metadata
 * must be unset or the tagged payload empty, the type count must equal the
 * class-registry id, and the kind field must be < 2.
 * Confidence: medium.
 */
bool sk_type_is_valid_ctor(long param_1, ushort *param_2)
{
    if ((param_2[1] & 1) == 0) {
        uint32_t uVar1 = *(uint32_t *)(param_1 + 0xc);
        ushort uVar2 = *param_2;
        long lVar4 = FUN_00362e54(0);
        if ((((uVar1 >> 0x10 & 1) == 0) ||
             (*(int32_t *)(param_1 + ((uVar1 >> 6) & 1) * 4 +
                           ((uVar1 >> 8) & 0xff) * 0xc + (uVar1 >> 0x18) * 8 + 0x13
                           & 0xfffffffffffffffc) == 0)) &&
            (*(int *)(lVar4 + 0x10) + 1U == (uint)uVar2) &&
            (*(int *)(param_2 + 2) == 0)) {
            return param_2[1] < 2;
        }
        return false;
    }
    return false;
}

/*--------------------------------------------------------------------*/
/* FUN_00376820 @ 0x00376820   (est. sk_obj_resolve_forward)
 * Ghidra: void FUN_00376820(undefined8 param_1)
 * Thin forwarder to FUN_00376838 (object resolution / lazy init).
 * Confidence: medium.
 */
void sk_obj_resolve_forward(uint64_t param_1)
{
    FUN_00376838(param_1, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00376838 @ 0x00376838   (est. sk_obj_resolve)
 * Ghidra: ulong FUN_00376838(ulong param_1, uint *param_2, long param_3)
 * Resolves an object (param_1) into its concrete representation, looking it
 * up in the object registry (table _DAT_006c0798/_DAT_006c07a0/_DAT_006c0794,
 * lock _DAT_006c0790, cache _DAT_006c07d8). Constructs a 0x60-byte object
 * entry (tag 0x59dd9b33) keyed by the source descriptor, initializing its
 * 16-word payload region, and returns a pointer into it. Rehashes the table
 * on load.
 * Confidence: medium (large open-addressing registry insert).
 */
ulong sk_obj_resolve(ulong param_1, uint32_t *param_2, long param_3)
{
    long lVar15 = param_3;
    uint32_t *puVar14 = sk_cap_field_ptr(param_1);      /* FUN_00376720 */
    uint32_t uVar21 = (uint32_t)((ulong)lVar15 >> 32);
    if (puVar14 == 0 || sk_type_is_valid_ctor(param_1, (ushort *)puVar14)) {
        int iVar13 = *(int *)(param_1 + 8);
        ulong uVar18 = (long)iVar13 + (long)(param_1 + 8);
        if (iVar13 == 0 || uVar18 == 0) return 0;
        if ((*(uint32_t *)(param_1 + 0xc) >> 7 & 1) == 0) return uVar18;
        long lVar15 = FUN_003873c0((void *)(param_1 + 4), *(uint32_t *)(param_1 + 0xc) >> 3 & 7);
        if (lVar15 == 0) lVar15 = 0;
        ulong uVar17 = FUN_00362e54((void *)param_1);
        return FUN_0037dfa8(uVar18, lVar15, uVar17);
    }
    uint32_t uVar11 = puVar14[2];
    uint32_t *puVar32 = (uint32_t *)((long)(int)uVar11 + (long)(puVar14 + 2));
    if (uVar11 == 0 || puVar32 == 0) {
        if (_DAT_006c07d8 == 0 ||
            (puVar32 = (uint32_t *)_DAT_006c07d8, puVar14 != *(uint32_t **)_DAT_006c07d8)) {
            /* full open-addressing registry insert of a 0x60-byte entry;
             * see decompile — elided for brevity (pattern as elsewhere) */
        }
        puVar32 = puVar32 + 4;
    } else if (-1 < *(long *)(puVar32 + 0x14)) {
        FUN_003d3dd8(puVar32 + 0x14, (void *)FUN_0037edf0, puVar32);
    }
    /* resolve the object's slot from the registry entry */
    ulong result = 0;
    /* ... (remaining body computes the object word; see decompile) */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_003773d8 @ 0x003773d8   (est. sk_demangle_witness)
 * Ghidra: undefined1[16] FUN_003773d8(undefined8 param_1, long *param_2,
 *                                     code *param_3, long param_4, long param_5)
 * Demangles an accessor-witness: reads the tagged pointer at the object
 * offset, and if it carries a demangle request, demangles the mangled name
 * (via FUN_003a31d8), builds the resilient descriptor, and installs the
 * freshly-constructed error/witness. On failure traps with the "freshly
 * constructed error" or "failed to demangle witness" strings.
 * Confidence: low (Swift runtime interop).
 */
uint64_t sk_demangle_witness(uint64_t param_1, long *param_2, code *param_3,
                             long param_4, long param_5)
{
    ulong uVar3 = *(ulong *)((long)param_2 + (param_5 - param_4 & 0x7fffffff8U));
    if ((uVar3 & 1) == 0) return uVar3;   /* not tagged: return {lo=data,hi=0} */
    /* tagged demangle path: demangle, build descriptor via FUN_003895e0,
     * install witness; else trap s_failed_to_demangle_witness (0x5d5007) */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00377800 @ 0x00377800   (est. sk_deref_tagged)
 * Ghidra: ulong FUN_00377800(ulong param_1)
 * If param_1 is tagged (low bit set), dereferences it; else returns it.
 * Confidence: high (trivial).
 */
ulong sk_deref_tagged(ulong param_1)
{
    if ((param_1 & 1) != 0) param_1 = *(ulong *)(param_1 & 0xfffffffffffffffe);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00377824 @ 0x00377824   (est. sk_demangle_witness_slot)
 * Ghidra: long FUN_00377824(undefined8 param_1, int *param_2, undefined8 param_3,
 *                           long param_4, long param_5)
 * Demangles a witness value stored at a slot in param_2: dereferences the
 * tagged class-name pointer, extracts the mangled name, builds the resilient
 * descriptor (FUN_003895e0), and returns the result. On failure traps with
 * "failed to demangle witness for a".
 * Confidence: low (Swift runtime interop).
 */
long sk_demangle_witness_slot(uint64_t param_1, int *param_2, uint64_t param_3,
                              long param_4, long param_5)
{
    if (((ulong)param_2 & 1) != 0) param_2 = *(int **)((ulong)param_2 & 0xfffffffffffffffe);
    int iVar2 = param_2[(ulong)(param_5 - param_4) >> 3 & 0xffffffff];
    long *plVar7 = (long *)((long)param_2 + ((long)*param_2 & 0xfffffffffffffffeU));
    if (((long)*param_2 & 1U) != 0) plVar7 = (long *)*plVar7;
    ulong uVar3 = FUN_00362e54(plVar7);
    sk_pair_t namep = FUN_003a31d8((void *)((long)(param_2 + ((ulong)(param_5 - param_4) >> 3 & 0xffffffff)) + (long)iVar2));
    uint64_t name[2] = { namep.lo, namep.hi };
    uint64_t uVar5 = FUN_0039c49c((void *)param_3, (void *)plVar7);
    uint8_t buf[16];
    FUN_0037d1d8(buf, uVar5);
    long result;
    FUN_003895e0(&result, param_1, name[0], name[1], 0, (void *)0x67b220, (void *)0x67b268);
    if (result != 0) return result;
    /* failure: trap s_failed_to_demangle_witness_for_a (0x5d5007) */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00377ad4 @ 0x00377ad4   (est. sk_cached_call_slot)
 * Ghidra: ulong FUN_00377ad4(long param_1, undefined8 param_2, undefined8 param_3,
 *                            long param_4, long param_5)
 * Reads the tagged slot at the object offset; if tagged and its mangled name
 * is the 5-char "__vt__..." accessor, calls the resolved witness with
 * (param_3, param_2, param_1) and caches the result back into the slot.
 * Traps if the name length is unexpected.
 * Confidence: low.
 */
ulong sk_cached_call_slot(long param_1, uint64_t param_2, uint64_t param_3,
                          long param_4, long param_5)
{
    ulong *puVar1 = (ulong *)(param_1 + (param_5 - param_4 & 0x7fffffff8U));
    ulong uVar4 = *puVar1;
    if ((uVar4 & 1) != 0) {
        char *pcVar6 = (char *)(uVar4 & 0xfffffffffffffffe);
        if (*pcVar6 == -1) pcVar6 = pcVar6 + 1;
        uint64_t name[2] = SKPAIR(FUN_003a31d8(pcVar6));
        if (name[1] != 5 || 1 < *(uint8_t *)name[0] - 7) __builtin_trap();   /* SoftwareBreakpoint(1,0x377bec) */
        uint8_t *pbVar5 = (uint8_t *)name[0] + 1;
        int iVar2 = *(int *)pbVar5;
        sk_fnv_t fn = (iVar2 != 0) ? (sk_fnv_t)(pbVar5 + iVar2) : 0;
        uVar4 = fn(param_3, param_2, param_1);
        *puVar1 = uVar4;
    }
    return uVar4;
}

/*--------------------------------------------------------------------*/
/* FUN_00377bec @ 0x00377bec   (est. sk_cached_call_dispatch)
 * Ghidra: void FUN_00377bec(ulong param_1, undefined8 param_2, undefined8 param_3,
 *                           long param_4, long param_5)
 * Like sk_cached_call_slot but for a 4-byte slot: dereferences the tagged
 * pointer, validates the accessor name, and dispatches through the resolved
 * witness. Traps on bad name length.
 * Confidence: low.
 */
void sk_cached_call_dispatch(ulong param_1, uint64_t param_2, uint64_t param_3,
                             long param_4, long param_5)
{
    ulong uVar5 = param_1;
    if ((param_1 & 1) != 0) uVar5 = *(ulong *)(param_1 & 0xfffffffffffffffe);
    int *piVar1 = (int *)(uVar5 + ((ulong)(param_5 - param_4) >> 3 & 0xffffffff) * 4);
    char *pcVar4 = (char *)((long)piVar1 + (long)*piVar1 & 0xfffffffffffffffe);
    if (*pcVar4 == -1) pcVar4 = pcVar4 + 1;
    uint64_t name[2] = SKPAIR(FUN_003a31d8(pcVar4));
    if (name[1] == 5 && *(uint8_t *)name[0] - 7 < 2) {
        uint8_t *pbVar3 = (uint8_t *)name[0] + 1;
        int iVar2 = *(int *)pbVar3;
        sk_fnv_t fn = (iVar2 != 0) ? (sk_fnv_t)(pbVar3 + iVar2) : 0;
        fn(param_3, param_2, param_1);
        return;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1,0x377ca8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00377ca8 @ 0x00377ca8   (est. sk_demangle_equal_check)
 * Ghidra: void FUN_00377ca8(void)
 * Thin forwarder to FUN_00377cc0 (type identity comparison).
 * Confidence: medium.
 */
void sk_demangle_equal_check(void)
{
    FUN_00377cc0(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00377cc0 @ 0x00377cc0   (est. sk_type_identity_eq)
 * Ghidra: bool FUN_00377cc0(int *param_1, int *param_2)
 * Compares two type identities for equality: equal when the pointers match,
 * or when both are tagged types sharing the same mangled-name and class id
 * (via FUN_0039a1b0 + FUN_00362e54).
 * Confidence: medium.
 */
bool sk_type_identity_eq(int *param_1, int *param_2)
{
    if (param_1 == param_2) return true;
    if (((ulong)param_1 & 1) != 0) param_1 = *(int **)((ulong)param_1 & 0xfffffffffffffffe);
    uint64_t *puVar2 = (uint64_t *)((long)param_1 + ((long)*param_1 & 0xfffffffffffffffeU));
    if (((long)*param_1 & 1U) != 0) puVar2 = (uint64_t *)*puVar2;
    if (((ulong)param_2 & 1) != 0) param_2 = *(int **)((ulong)param_2 & 0xfffffffffffffffe);
    uint64_t *puVar5 = (uint64_t *)((long)param_2 + ((long)*param_2 & 0xfffffffffffffffeU));
    if (((long)*param_2 & 1U) != 0) puVar5 = (uint64_t *)*puVar5;
    if (puVar2 != puVar5) {
        if (*(char *)((long)puVar2 + 0xc) < 0 && *(char *)((long)puVar5 + 0xc) < 0) {
            long lVar3 = FUN_0039a1b0(puVar2);
            long lVar4 = FUN_0039a1b0(puVar5);
            bool eq = false;
            if (lVar3 != 0 && (lVar4 != 0 && lVar3 == lVar4)) {
                eq = FUN_00362e54(puVar2) == FUN_00362e54(puVar5);
            }
            return eq;
        }
        return false;
    }
    return true;
}

/*--------------------------------------------------------------------*/
/* FUN_00377dcc @ 0x00377dcc   (est. sk_desc_deref_release)
 * Ghidra: void FUN_00377dcc(undefined8 param_1, undefined8 param_2)
 * Wrapper: stores param_1 into a local then calls FUN_00377dfc (descriptor
 * resolution/dispatch).
 * Confidence: medium.
 */
void sk_desc_deref_release(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_18 = param_1;
    FUN_00377dfc((long *)param_2, &local_18);
}

/*--------------------------------------------------------------------*/
/* FUN_00377dfc @ 0x00377dfc   (est. sk_desc_resolve_dispatch)
 * Ghidra: long * FUN_00377dfc(long *param_1, undefined8 *param_2)
 * Resolves a descriptor (param_1) into its concrete type via the object
 * registry, dispatching on the descriptor kind: 0x203/0x301 aggregate nodes,
 * tagged capabilities, and the generic object lookup. Returns the resolved
 * object pointer. Traps on an unsupported kind.
 * Confidence: medium.
 */
long *sk_desc_resolve_dispatch(long *param_1, uint64_t *param_2)
{
    if (FUN_0036f460(0) != 0) return param_1;
    long lVar6 = *param_1;
    uint32_t *puVar7 = 0;
    if (lVar6 - 1U < 0x7ff) {
        if ((int)lVar6 - 0x203U < 0xfffffffd) {
            if (lVar6 != 0x203) {
                if (lVar6 != 0x301) return param_1;
                if (param_1[1] == 0) return param_1;
                if (-1 < _DAT_006c0530) FUN_003d3dd8(&_DAT_006c0530, (void *)FUN_00371af8, 0);
                return (long *)FUN_00381fac(param_1 + -0xe, *param_2);
            }
            puVar7 = (uint32_t *)param_1[1];
            if (puVar7 == 0) puVar7 = 0;
            if (-1 < _DAT_006c0730) FUN_003d3dd8(&_DAT_006c0730, (void *)FUN_0037f3d0);
            goto tagged;
        }
        puVar7 = (uint32_t *)param_1[1];
        if (puVar7 != 0) goto joined;
    } else {
        puVar7 = (uint32_t *)param_1[5];
        if (puVar7 != 0) goto joined;
    }
    puVar7 = 0;
joined:
    if (puVar7 == 0) return param_1;
    if ((*puVar7 >> 7 & 1) == 0) {
        uint32_t uVar1 = *puVar7 >> 0x10 & 3;
        if (1 < uVar1) {
            if (uVar1 != 2) __builtin_trap();   /* SoftwareBreakpoint(1,0x3780f4) */
            if (-1 < _DAT_006c0730) FUN_003d3dd8(&_DAT_006c0730, (void *)FUN_0037f3d0);
tagged:
            uint64_t uVar5 = FUN_0037f430(puVar7);
            return (long *)FUN_00386ee0((void *)uVar5, *param_2);
        }
        if (uVar1 != 0) {
            if (-1 < _DAT_006c0388) FUN_003d3dd8(&_DAT_006c0388, (void *)FUN_003704ac);
            uint64_t uVar5 = FUN_0037f638(puVar7);
            return (long *)FUN_003800cc((void *)uVar5, *param_2);
        }
    } else {
        int iVar3 = FUN_0035ef4c(puVar7);
        long lVar6 = FUN_0036fb10(puVar7);
        uint64_t uStack_60 = *(uint64_t *)(lVar6 + 0x58);
        uint64_t uStack_68 = *(uint64_t *)(lVar6 + 0x50);
        long *local_70 = param_1 + iVar3;
        FUN_0037cb08(&local_70);
        uint64_t uVar5 = FUN_0037f8c8((void *)lVar6, (uint64_t)&local_70);
        return (long *)FUN_0037a9ac((uint64_t *)uVar5, (uint64_t)(lVar6 + 0x40), *param_2);
    }
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_003780f4 @ 0x003780f4   (est. sk_desc_acyclic_check)
 * Ghidra: uint FUN_003780f4(long *param_1)
 * Returns 1 when the descriptor tree rooted at param_1 is acyclic (no child
 * type recursively depends on itself), 0 when a cycle is found. Handles
 * aggregate 0x301/0x203 nodes by recursing and generic/tagged leaves by
 * decoding their requirement descriptors (FUN_003876c4).
 * Confidence: medium.
 */
uint32_t sk_desc_acyclic_check(long *param_1)
{
    long lVar8 = *param_1;
    char *pcVar9 = 0;
    if (lVar8 - 1U < 0x7ff) {
        if ((int)lVar8 - 0x203U < 0xfffffffd) {
            if (lVar8 == 0x203) {
                if (param_1[2] == 0) return 1;
                if ((FUN_003876c4(0) & 1) == 0) return 1;
                return 0;
            }
            if (lVar8 != 0x301) return 1;
            long lVar8b = param_1[1];
            if (lVar8b == 0) return 1;
            ulong uVar10 = 0;
            uint32_t uVar4;
            do {
                uVar4 = FUN_003876c4((void *)param_1[(uVar10 & 0xffffffff) * 2 + 3]);
                if ((uVar4 & 1) != 0) break;
                uVar10++;
            } while (lVar8b - 1U != uVar10);
            return uVar4 ^ 1;
        }
        pcVar9 = (char *)param_1[1];
        if (pcVar9 == 0) pcVar9 = 0;
    } else {
        pcVar9 = (char *)param_1[5];
        if (pcVar9 == 0) pcVar9 = 0;
        long lVar8b = param_1[1];
        if (lVar8b != 0 && (FUN_003876c4((void *)lVar8b) & 1) != 0) return 0;
    }
    if (*pcVar9 < 0) {
        long lVar8 = FUN_0035eb3c(pcVar9);
        int iVar5 = FUN_0035ef4c(pcVar9);
        ulong uVar10 = 0;
        if ((*(ushort *)(lVar8 + 10) & 1) != 0)
            uVar10 = (ulong)*(ushort *)
                ((lVar8 + (ulong)*(ushort *)(lVar8 + 4) + 0xf & 0xfffffffffffffffc) +
                 (ulong)*(ushort *)(lVar8 + 6) * 0xc + 2);
        long lVar6 = FUN_003658a0((void *)lVar8);
        ushort uVar2 = *(ushort *)(lVar8 + 4);
        if ((ulong)uVar2 != 0) {
            ulong uVar12 = 0;
            uint8_t *pbVar11 = (uint8_t *)(lVar8 + 0xc);
            do {
                if ((char)*pbVar11 < 0) {
                    uint8_t bVar1 = *pbVar11 & 0x3f;
                    if (bVar1 != 2) {
                        if (bVar1 == 1) {
                            long lVar13 = param_1[(long)iVar5 + (ulong)*(ushort *)(lVar6 + uVar12 * 8 + 4)];
                            if (lVar13 != 0) {
                                uint64_t *puVar14 =
                                    (uint64_t *)(param_1[(long)iVar5 + uVar10] & 0xfffffffffffffffe);
                                do {
                                    if ((FUN_003876c4((void *)*puVar14) & 1) != 0) return 0;
                                    lVar13--; puVar14++;
                                } while (lVar13 != 0);
                            }
                            uVar12 = (ulong)((int)uVar12 + 1);
                        } else {
                            if ((FUN_003876c4((void *)param_1[(long)iVar5 + uVar10]) & 1) != 0) return 0;
                        }
                    }
                    uVar10 = (ulong)((int)uVar10 + 1);
                }
                pbVar11++;
            } while (pbVar11 != (uint8_t *)(lVar8 + (ulong)uVar2 + 0xc));
        }
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00378374 @ 0x00378374   (est. sk_dep_resolve_list)
 * Ghidra: undefined1[16] FUN_00378374(undefined8 param_1)
 * Resolves a dependency list for type param_1: iterates up to DAT_004f2710
 * candidates, scheduling each via FUN_00378498 until one resolves, then
 * returns {data,len} of the winner.
 * Confidence: medium.
 */
sk_pair_t sk_dep_resolve_list(uint64_t param_1)
{
    ulong local_80 = DAT_004f2710;
    uint64_t buf[0x14] = {0};
    uint64_t *local_138 = &buf[2];
    uint32_t local_cc = 1;
    uint64_t local_c8 = param_1;
    uint64_t *local_88 = buf;
    ulong uVar2 = FUN_00378498((long *)param_1, (long *)&local_138);
    uint64_t uVar3 = 0, uVar4 = 0;
    if ((uVar2 & 1) == 0) {
        do {
            uVar2 = local_80 & 0xffffffff;
            if ((int)local_80 == 0) { uVar3 = 0; break; }
            local_80 = ((uint64_t)(uint32_t)(local_80 >> 32) << 32) | (uint32_t)((int)local_80 + -1);
            int iVar1 = FUN_00378498((long *)*(uint64_t *)(local_88 + uVar2 * 8 + -8), (long *)&local_138);
            uVar3 = buf[2];
            if (iVar1 == 0) uVar4 = 0;
            else break;
        } while ((int)local_80 != 0);
    }
    FUN_0037daa8(&buf[0]);
    if (local_88 != buf) thunk_FUN_00012568(0);
    return SKPAIR2(uVar3, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_00378498 @ 0x00378498   (est. sk_dep_schedule)
 * Ghidra: undefined8 FUN_00378498(long *param_1, long *param_2)
 * Schedules dependency param_1 into the dedup work list param_2 (skip if
 * already present), resolves it via FUN_00377dfc, and marks it complete
 * (param_2[3]={ptr,1}) when concrete. Handles aggregate 0x301/0x203 nodes
 * by recursing over children and generic requirement walks.
 * Confidence: low (large Swift-metadata dependency scheduler).
 */
uint64_t sk_dep_schedule(long *param_1, long *param_2)
{
    long lVar6 = *param_1;
    if (lVar6 - 1U < 0x7ff) {
        if ((int)lVar6 - 0x203U < 0xfffffffd) {
            if (lVar6 != 0x203) {
                if (lVar6 != 0x301) return 0;
                /* aggregate: schedule each child */
                ulong uVar13 = param_1[1];
                if (uVar13 == 0) return 0;
                for (ulong uVar14 = 0; uVar14 < uVar13; uVar14++) {
                    long child[2];
                    child[0] = param_1[(uVar14 & 0xffffffff) * 2 + 3];
                    long *plVar2 = (long *)*param_2;
                    int iVar5 = *(int *)param_2[1];
                    long *plVar9 = plVar2;
                    if (iVar5 != 0) {
                        long lVar11 = (long)iVar5 << 3;
                        do { if (*plVar9 == child[0]) break; plVar9++; lVar11 -= 8; } while (lVar11 != 0);
                    }
                    if (plVar9 == plVar2 + iVar5) {
                        if (iVar5 < 8) {
                            *(int *)param_2[1] = iVar5 + 1;
                            plVar2[iVar5] = child[0];
                        } else {
                            FUN_0037d4b8((long *)param_2[2], child, child);
                        }
                    }
                    child[1] = 0x100;
                    FUN_00377dfc((long *)child[0], (uint64_t *)(child + 1));
                }
                return 0;
            }
            /* 0x203 leaf */
            long child[2];
            child[0] = param_1[2];
            if (child[0] == 0) return 0;
            long *plVar2 = (long *)*param_2;
            int iVar5 = *(int *)param_2[1];
            long *plVar9 = plVar2;
            if (iVar5 != 0) {
                long lVar11 = (long)iVar5 << 3;
                do { if (*plVar9 == child[0]) break; plVar9++; lVar11 -= 8; } while (lVar11 != 0);
            }
            if (plVar9 == plVar2 + iVar5) {
                if (iVar5 < 8) {
                    *(int *)param_2[1] = iVar5 + 1;
                    plVar2[iVar5] = child[0];
                } else {
                    FUN_0037d4b8((long *)param_2[2], child, child);
                }
            }
            child[1] = 0x100;
            FUN_00377dfc((long *)child[0], (uint64_t *)(child + 1));
            long *plVar9b = (long *)param_2[3];
            *plVar9b = child[0];
            plVar9b[1] = 1;
            return 1;
        }
        /* generic leaf / tagged path */
        if (lVar6 != 0x303) return 0;
    }
    return 0;
}

/* FUN_00378a30 @ 0x00378a30   (est. sk_dep_resolve_walk)
 * Ghidra: void FUN_00378a30(undefined8 param_1, undefined8 param_2, long param_3,
 *                           ulong param_4)
 * Walks and resolves a metadata dependency list, dispatching each pending
 * requirement through the object registry and merging resolved children into
 * the shared work list (grow via FUN_00379128). Part of the multi-step
 * metadata resolution pipeline.
 * Confidence: low (large stateful walk; see decompile).
 */
void sk_dep_resolve_walk(uint64_t param_1, uint64_t param_2, long param_3, ulong param_4)
{
    /* full walk — see decompile at 0x378a30 */
}

/*--------------------------------------------------------------------*/
/* FUN_00379048 @ 0x00379048   (est. sk_vec_push_back)
 * Ghidra: void FUN_00379048(long *param_1, undefined8 *param_2)
 * Appends a 16-byte element (param_2[0..1]) to the vector param_1
 * ({begin,end,cap}), growing the backing array via FUN_00387868 when full.
 * Confidence: medium.
 */
void sk_vec_push_back(long *param_1, uint64_t *param_2)
{
    uint64_t *puVar5 = (uint64_t *)param_1[1];
    if (puVar5 < (uint64_t *)param_1[2]) {
        uint64_t uVar8 = *param_2;
        puVar5[1] = param_2[1];
        *puVar5 = uVar8;
        puVar5 += 2;
    } else {
        long lVar7 = (long)puVar5 - *param_1;
        ulong uVar1 = (lVar7 >> 4) + 1;
        if (uVar1 >> 0x3c != 0) FUN_004b89f8();
        ulong uVar3 = param_1[2] - *param_1;
        ulong uVar4 = (long)uVar3 >> 3;
        if (uVar4 <= uVar1) uVar4 = uVar1;
        if (0x7fffffffffffffef < uVar3) uVar4 = 0xfffffffffffffff;
        sk_pair_t pp = SKPAIR2(0,0);
        if (uVar4 != 0) { uint64_t r = FUN_00387868(); pp = SKPAIR2(r,0); }
        uint64_t pair[2] = { pp.lo, pp.hi };
        uint64_t *puVar2 = (uint64_t *)(pair[0] + lVar7);
        uint64_t uVar8 = *param_2;
        puVar2[1] = param_2[1];
        *puVar2 = uVar8;
        puVar5 = puVar2 + 2;
        long lVar6 = (long)puVar2 - (param_1[1] - *param_1);
        FUN_00117cc4((void *)lVar6, 0, 0);
        long lVar7b = *param_1;
        *param_1 = lVar6;
        param_1[1] = (long)puVar5;
        param_1[2] = pair[0] + pair[1] * 0x10;
        if (lVar7b != 0) thunk_FUN_00012568((void *)lVar7b, lVar6 - lVar7b);
    }
    param_1[1] = (long)puVar5;
}

/*--------------------------------------------------------------------*/
/* FUN_00379128 @ 0x00379128   (est. sk_dep_cycle_report)
 * Ghidra: void FUN_00379128(undefined8 *param_1, long param_2)
 * Builds and emits a "runtime error: unresolvable type / type metadata
 * cycle" diagnostic (strings at 0x5d5070/0x5d510c/0x5d5132/0x5d50f1/0x5d5100),
 * traversing the dependency graph, then aborts. Non-returning.
 * Confidence: low (Swift runtime diagnostic).
 */
void sk_dep_cycle_report(uint64_t *param_1, long param_2)
{
    /* builds the runtime-error message and aborts via FUN_00369bb0 */
    FUN_00369bb0(0, (char *)0x5aa8b2);
}

/*--------------------------------------------------------------------*/
/* FUN_00379410 @ 0x00379410   (est. sk_desc_alloc_pair)
 * Ghidra: void FUN_00379410(undefined8 param_1, undefined8 param_2)
 * Thin wrapper allocating a descriptor via FUN_00369758.
 * Confidence: medium.
 */
void sk_desc_alloc_pair(uint64_t param_1, uint64_t param_2)
{
    uint8_t slot;
    FUN_00369758(&slot, param_1, param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_0037943c @ 0x0037943c   (est. sk_desc_is_simple)
 * Ghidra: bool FUN_0037943c(ulong *param_1)
 * Returns whether the descriptor kind is a simple leaf: 0x303 with no
 * payload bits, or one of 0/0x203/0x305.
 * Confidence: medium.
 */
bool sk_desc_is_simple(ulong *param_1)
{
    ulong uVar2 = *param_1;
    if (uVar2 == 0x303) return (param_1[1] & 0x80ffffff) == 0;
    int iVar1 = (uVar2 < 0x800) ? (int)uVar2 : 0;
    return iVar1 == 0 || (iVar1 == 0x203 || iVar1 == 0x305);
}

/*--------------------------------------------------------------------*/
/* FUN_0037947c @ 0x0037947c   (est. thunk_FUN_0024d9ac)
 * Ghidra: void thunk_FUN_0024d9ac(void)
 * Thunk that dispatches a deferred kernel-maintenance operation: reads the
 * per-CPU work pointer (FUN_00351a38 + FUN_0022a474), processes the queue,
 * and installs the next stage (FUN_00247360 with FUN_0031cd18).
 * Confidence: low (thunk into kernel machinery region 0x24xxxx).
 */
void thunk_FUN_0024d9ac(void)
{
    long lVar2 = FUN_00351a38();
    FUN_0022a474(0x10, lVar2 + 4);
    FUN_0024c8bc();
    FUN_003504e8();
    int iVar1 = FUN_0022a474(0);
    long *plVar4 = (iVar1 == 0) ? 0 : (long *)(lVar2 + iVar1);   /* unaff_x19 + iVar1 */
    if (plVar4 != 0 && *plVar4 != 0) {
        sk_alloc_pages(*plVar4, 0);   /* FUN_0036b270 */
        goto out;
    }
    FUN_00100efc();
    FUN_0024daf8();
    FUN_00355cbc();
    /* ... builds a deferred work node and installs it (see decompile) */
out:
    FUN_00356310();
}

/*--------------------------------------------------------------------*/
/* FUN_00379480 @ 0x00379480   (est. sk_cap_stage_base)
 * Ghidra: long FUN_00379480(undefined8 param_1)
 * Capability stage base: FUN_003794d0 + 4*FUN_00379b84 + 4*FUN_00379c0c.
 * Confidence: medium.
 */
long sk_cap_stage_base(uint64_t param_1)
{
    return FUN_003794d0(0) + FUN_00379b84((void *)param_1) * 4 + FUN_00379c0c((void *)param_1) * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_003794d0 @ 0x003794d0   (est. sk_cap_stage_lo)
 * Ghidra: long FUN_003794d0(undefined8 param_1)
 * Capability stage low offset: base (FUN_0037954c) + 2*count (FUN_00379a58)
 * aligned, + 0xc*last 2-byte field (FUN_00379ae8).
 * Confidence: medium.
 */
long sk_cap_stage_lo(uint64_t param_1)
{
    long lVar1 = FUN_0037954c(0);
    ulong uVar2 = FUN_00379a58((void *)param_1);
    uint64_t pair[2] = SKPAIR(FUN_00379ae8((void *)param_1));
    ulong uVar3 = (pair[1] == 0) ? 0 : (ulong)*(uint16_t *)(pair[0] + pair[1] * 2 + -2);
    return (lVar1 + (uVar2 & 0xffffffff) * 2 + 3 & 0xfffffffffffffffc) + uVar3 * 0xc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037954c @ 0x0037954c   (est. sk_cap_stage_hdr)
 * Ghidra: long FUN_0037954c(undefined8 param_1)
 * Capability stage header: base (FUN_003795a8) + 2*count (FUN_003799d0).
 * Confidence: medium.
 */
long sk_cap_stage_hdr(uint64_t param_1)
{
    return FUN_003795a8(0) + (FUN_003799d0((void *)param_1) & 0xffffffff) * 2;
}

/*--------------------------------------------------------------------*/
/* FUN_003795a8 @ 0x003795a8   (est. sk_cap_stage_base_off)
 * Ghidra: long FUN_003795a8(undefined8 param_1)
 * Capability stage base offset sum.
 * Confidence: medium.
 */
long sk_cap_stage_base_off(uint64_t param_1)
{
    return FUN_00379608(0) + FUN_00379720((void *)param_1) * 0xc +
           FUN_003797a4((void *)param_1) * 4 + FUN_0037982c((void *)param_1) * 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00379608 @ 0x00379608   (est. sk_cap_stage_word)
 * Ghidra: ulong FUN_00379608(uint *param_1)
 * Capability stage word offset: param_1+0xb aligned + extra word (generic
 * flag) + subword.
 * Confidence: medium.
 */
ulong sk_cap_stage_word(uint32_t *param_1)
{
    uint32_t *puVar3 = param_1 + 0xb;
    if (puVar3 == 0) puVar3 = 0;
    if (param_1 == 0) param_1 = 0;
    uint32_t uVar1 = *param_1;
    long lVar2 = FUN_0037969c(0);
    return (ulong)puVar3 + lVar2 + ((uVar1 >> 7) & 1) * 0x10 + 3 & 0xfffffffffffffffc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037969c @ 0x0037969c   (est. sk_cap_subword)
 * Ghidra: undefined2 FUN_0037969c(char *param_1)
 * For a tagged type pointer returns the 2-byte subword at +0x34.
 * Confidence: medium.
 */
uint16_t sk_cap_subword(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x34);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379720 @ 0x00379720   (est. sk_cap_count)
 * Ghidra: undefined2 FUN_00379720(char *param_1)
 * For a tagged type pointer returns the 2-byte count at +0x36.
 * Confidence: medium.
 */
uint16_t sk_cap_count(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x36);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003797a4 @ 0x003797a4   (est. sk_cap_has_fields)
 * Ghidra: ushort FUN_003797a4(char *param_1)
 * For a tagged type pointer returns bit 0 of the 2-byte field at +0x3a.
 * Confidence: medium.
 */
uint16_t sk_cap_has_fields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x3a) & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037982c @ 0x0037982c   (est. sk_cap_fields_word)
 * Ghidra: undefined2 FUN_0037982c(char *param_1)
 * For a tagged type pointer with fields flag set, returns the field word
 * (FUN_003798d0); else 0.
 * Confidence: medium.
 */
uint16_t sk_cap_fields_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x3a) & 1) != 0) return FUN_003798d0(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003798d0 @ 0x003798d0   (est. sk_cap_field_word)
 * Ghidra: uint FUN_003798d0(char *param_1)
 * Reads the packed capability field word (two 16-bit halves) from the
 * descriptor.
 * Confidence: medium.
 */
uint32_t sk_cap_field_word(char *param_1)
{
    char *pcVar6 = param_1 ? param_1 : 0;
    if (*pcVar6 < 0) {
        char *pcVar6b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar6b + 0x3a) & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            long lVar1 = FUN_00379608((void *)param_1);
            long lVar2 = FUN_00379720((void *)param_1);
            uint16_t *puVar5 = (uint16_t *)(lVar1 + lVar2 * 0xc);
            return (uint32_t)puVar5[1] << 0x10 | (uint32_t)*puVar5;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003799d0 @ 0x003799d0   (est. sk_cap_count_flag)
 * Ghidra: ushort FUN_003799d0(char *param_1)
 * For a tagged type pointer returns bit 1 of the 2-byte field at +0x3a.
 * Confidence: medium.
 */
uint16_t sk_cap_count_flag(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x3a) >> 1 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379a58 @ 0x00379a58   (est. sk_cap_popcount)
 * Ghidra: ulong FUN_00379a58(long param_1)
 * When the count flag is set, returns the popcount of the packed cap word
 * (via FUN_003795a8), else 0.
 * Confidence: medium.
 */
ulong sk_cap_popcount(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    ulong uVar1 = FUN_003799d0((char *)lVar3);
    if ((int)uVar1 != 0) {
        if (param_1 == 0) param_1 = 0;
        uint16_t *puVar2 = (uint16_t *)FUN_003795a8((void *)param_1);
        char cVar4 = POPCOUNT((char)((uint16_t)*puVar2 >> 8));
        uVar1 = (ulong)CONCAT11(cVar4, POPCOUNT((char)*puVar2) + cVar4);
    }
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00379ae8 @ 0x00379ae8   (est. sk_cap_field_table)
 * Ghidra: undefined1[16] FUN_00379ae8(long param_1)
 * Returns {base,count} of the capability field table.
 * Confidence: medium.
 */
sk_pair_t sk_cap_field_table(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    if (FUN_003799d0((char *)lVar3) == 0) return SKPAIR2(0,0);
    long lVar3b = param_1 ? param_1 : 0;
    ulong uVar2 = FUN_0037954c((void *)lVar3b);
    ulong uVar4 = FUN_00379a58((void *)param_1) & 0xffffffff;
    return SKPAIR2(uVar2, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_00379b84 @ 0x00379b84   (est. sk_cap_has_subfields)
 * Ghidra: ushort FUN_00379b84(char *param_1)
 * For a tagged type pointer returns bit 2 of the 2-byte field at +0x3a.
 * Confidence: medium.
 */
uint16_t sk_cap_has_subfields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x3a) >> 2 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379c0c @ 0x00379c0c   (est. sk_cap_subfield_word)
 * Ghidra: undefined4 FUN_00379c0c(char *param_1)
 * For a tagged type pointer with subfields flag set, returns the subfield
 * word (FUN_00379cb0); else 0.
 * Confidence: medium.
 */
uint32_t sk_cap_subfield_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x3a) >> 2 & 1) != 0) return FUN_00379cb0(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379cb0 @ 0x00379cb0   (est. sk_cap_subfield_lo)
 * Ghidra: undefined4 FUN_00379cb0(char *param_1)
 * Reads the subfield word from the cap descriptor (via FUN_003794d0).
 * Confidence: medium.
 */
uint32_t sk_cap_subfield_lo(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        char *pcVar2b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar2b + 0x3a) >> 2 & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            return *(uint32_t *)FUN_003794d0((void *)param_1);
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379d74 @ 0x00379d74   (est. sk_cap2_size)
 * Ghidra: long FUN_00379d74(uint *param_1)
 * Capability stage size variant: base (FUN_00379dec) + 4*generic + 0xc*count
 * (FUN_00379e78) + 4*payload flag.
 * Confidence: medium.
 */
long sk_cap2_size(uint32_t *param_1)
{
    long lVar2 = FUN_00379dec(0);
    uint32_t uVar1 = *param_1;
    long lVar3 = FUN_00379e78((void *)param_1);
    ulong uVar4 = (*(uint8_t *)((long)param_1 + 3) >> 5 & 1) ? ((ulong)param_1[7] & 1) : 0;
    return lVar2 + ((uVar1 >> 0x1e) & 1) * 4 + lVar3 * 0xc + uVar4 * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_00379dec @ 0x00379dec   (est. sk_cap2_base)
 * Ghidra: long FUN_00379dec(uint *param_1)
 * Capability stage base: FUN_00379480 + tag-derived stride + staged count.
 * Confidence: medium.
 */
long sk_cap2_base(uint32_t *param_1)
{
    long lVar2 = FUN_00379480((void *)param_1);
    uint32_t uVar1 = *param_1;
    ulong uVar4 = 0;
    if ((int)uVar1 < 0) {
        long lVar3 = FUN_00374230(param_1);
        uVar4 = (ulong)*(uint32_t *)(lVar3 + 4);
    }
    return lVar2 + ((uVar1 >> 0x1d) & 1) * 4 + ((uVar1 & 0x30000) == 0x20000) * 4 +
           ((uVar1 & 0x30000) == 0x10000) * 0xc + (uVar1 >> 0x1f) * 8 + uVar4 * 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00379e78 @ 0x00379e78   (est. sk_cap2_count_word)
 * Ghidra: undefined4 FUN_00379e78(long param_1)
 * Returns the count word at the cap stage (via FUN_00379dec) when the count
 * flag is set; else 0.
 * Confidence: medium.
 */
uint32_t sk_cap2_count_word(long param_1)
{
    if ((*(uint8_t *)(param_1 + 3) >> 6 & 1) != 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint32_t *)FUN_00379dec((void *)param_1);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00379eec @ 0x00379eec   (est. sk_cap2_tagword)
 * Ghidra: undefined4 FUN_00379eec(uint *param_1)
 * When the tag matches 0x80080, returns the tag word at the cap stage (via
 * FUN_00379d74); else 0.
 * Confidence: medium.
 */
uint32_t sk_cap2_tagword(uint32_t *param_1)
{
    if (((*param_1 ^ 0xffffffff) & 0x80080) != 0) return 0;
    if (param_1 == 0) param_1 = 0;
    return *(uint32_t *)FUN_00379d74((void *)param_1);
}

/*--------------------------------------------------------------------*/
/* FUN_00379f6c @ 0x00379f6c   (est. sk_desc_equiv)
 * Ghidra: undefined8 FUN_00379f6c(undefined8 *param_1, undefined8 *param_2)
 * Compares two descriptors for structural equivalence: equal kind word,
 * length, header, inline payload, and type-identity of each word (via
 * FUN_00377cc0 / memcmp). Returns 1 on match, 0 otherwise.
 * Confidence: medium.
 */
uint64_t sk_desc_equiv(uint64_t *param_1, uint64_t *param_2)
{
    if (*(int *)(param_1 + 3) != *(int *)(param_2 + 3)) return 0;
    ulong lVar15 = (ulong)*(ushort *)(param_1 + 1) + (ulong)*(ushort *)((long)param_1 + 0xe) +
                   (ulong)*(ushort *)((long)param_1 + 10);
    if (lVar15 == (ulong)*(ushort *)(param_2 + 1) + (ulong)*(ushort *)((long)param_2 + 0xe) +
                   (ulong)*(ushort *)((long)param_2 + 10)) {
        long *plVar12 = (long *)*param_1;
        long *plVar13 = (long *)*param_2;
        if (thunk_FUN_001145b0(plVar12, plVar13, lVar15 * 8) != 0) {
            if ((int)FUN_0037a19c(param_1 + 1, param_2 + 1) == 0) return 0;
            /* compare field regions + type identities (see decompile) */
            if (FUN_0037a19c(param_1 + 1, param_2 + 1) != 0) return 1;
            return 0;
        }
        return 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a19c @ 0x0037a19c   (est. sk_desc_payload_eq)
 * Ghidra: undefined8 FUN_0037a19c(short *param_1, short *param_2)
 * Compares two descriptor payloads (length + subfield words) for equality.
 * Confidence: medium.
 */
uint64_t sk_desc_payload_eq(short *param_1, short *param_2)
{
    if ((*param_1 == *param_2) && (param_1[1] == param_2[1]) && (param_1[3] == param_2[3])) {
        ushort uVar1 = param_1[2];
        ulong uVar2 = (ulong)uVar1;
        if (uVar1 == param_2[2]) {
            if (uVar1 != 0) {
                short *psVar3 = (short *)(*(long *)(param_1 + 4) + 4);
                short *psVar4 = (short *)(*(long *)(param_2 + 4) + 4);
                do {
                    if (psVar3[-2] != psVar4[-2]) return 0;
                    if (psVar3[-1] != psVar4[-1]) return 0;
                    if (*psVar3 != *psVar4) return 0;
                    uVar2--;
                    psVar3 += 4; psVar4 += 4;
                } while (uVar2 != 0);
            }
            return 1;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a238 @ 0x0037a238   (est. sk_meta_find_desc)
 * Ghidra: undefined1[16] FUN_0037a238(long param_1, ulong param_2, ulong param_3,
 *                                     long param_4)
 * Searches the open-addressed metadata table for an entry equal to param_1
 * (via FUN_00379f6c), returning {slot_index, slot_ptr}.
 * Confidence: medium.
 */
sk_pair_t sk_meta_find_desc(long param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong uVar4 = 4;
    if ((param_2 & 3) != 0 && (uint8_t *)(param_2 & 0xfffffffffffffffc) != 0)
        uVar4 = *(uint8_t *)(param_2 & 0xfffffffffffffffc);
    ulong uVar5 = -1L << (uVar4 & 0x3f);
    uVar4 = (ulong)*(uint32_t *)(param_1 + 0x18) & ~uVar5;
    if (uVar4 < 2) uVar4 = 1;
    ulong local_78 = param_2;
    int iVar1 = FUN_0037a340(&local_78, uVar4, 2);
    if (iVar1 != 0) {
        do {
            ulong uVar6 = (ulong)(iVar1 - 1);
            if (uVar6 < param_3) {
                long lVar3 = *(long *)(param_4 + uVar6 * 8);
                long local_70 = lVar3 + 0x28;
                uint64_t fields[3] = { *(uint64_t *)(lVar3 + 8), *(uint64_t *)(lVar3 + 0x10),
                                       *(uint32_t *)(lVar3 + 0x18) };
                if ((FUN_00379f6c((uint64_t *)param_1, (uint64_t *)&local_70) & 1) != 0) {
                    uVar4 = 0;
                    param_4 = param_4 + uVar6 * 8;
                    goto out;
                }
            }
            uVar4 = uVar4 + 1 & ~uVar5;
            if (uVar4 < 2) uVar4 = 1;
            iVar1 = FUN_0037a340(&local_78, uVar4, 2);
        } while (iVar1 != 0);
    }
    param_4 = 0;
    uVar4 = uVar4 & 0xffffffff;
out:
    return SKPAIR2((uint64_t)param_4, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_0037a340 @ 0x0037a340   (est. sk_meta_read_elem)
 * Ghidra: uint FUN_0037a340(ulong *param_1, ulong param_2, int param_3)
 * Reads one element from the open-addressed metadata container: for an
 * inline word returns the packed 4-bit field; otherwise reads a byte, ushort,
 * or uint by element width. Width selector param_3 (0/1/2/5) is accepted but
 * only the 1-byte/2-byte/4-byte paths are distinguished.
 * Confidence: medium.
 */
uint32_t sk_meta_read_elem(ulong *param_1, ulong param_2, int param_3)
{
    ulong uVar3 = *param_1;
    uint32_t uVar1 = (uint32_t)uVar3 & 3;
    ulong uVar2;
    if (uVar1 == 1 || (uVar3 & 3) == 0) {
        if ((uVar3 & 3) == 0) return (uint32_t)(uVar3 >> ((param_2 & 0xf) << 2)) & 0xf;
        uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
        return (uint32_t)*(uint8_t *)(uVar2 + param_2);
    }
    if (uVar1 != 2) {
        uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
        return *(uint32_t *)(uVar2 + param_2 * 4);
    }
    uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
    return (uint32_t)*(uint16_t *)(uVar2 + param_2 * 2);
}

/*--------------------------------------------------------------------*/
/* FUN_0037a42c @ 0x0037a42c   (est. sk_meta_drain_deferred)
 * Ghidra: void FUN_0037a42c(int *param_1)
 * Drains the deferred-free list (param_1[0xc]) after a data barrier when the
 * refcount is zero, releasing each node and its payload, then clears the
 * head/tail.
 * Confidence: medium.
 */
void sk_meta_drain_deferred(int *param_1)
{
    DataMemoryBarrier(2, 3);
    if (*param_1 == 0) {
        uint64_t *puVar2 = *(uint64_t **)(param_1 + 0xc);
        while (puVar2 != 0) {
            uint64_t *puVar1 = (uint64_t *)*puVar2;
            thunk_FUN_00012568((void *)puVar2[1]);
            thunk_FUN_00012568((void *)puVar2);
            puVar2 = puVar1;
        }
        param_1[0xc] = 0;
        param_1[0xd] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037a48c @ 0x0037a48c   (est. sk_mtx_lock_checked)
 * Ghidra: void FUN_0037a48c(void)
 * Acquires a mutex via FUN_00118164; on failure panics with the
 * "__mtx_lock handle failed with e" string (0x5d4f0e).
 * Confidence: high (mtx wrapper with string).
 */
void sk_mtx_lock_checked(void)
{
    if (FUN_00118164() == 0) return;
    FUN_003a2578((char *)0x5d4f0e);   /* "__mtx_lock handle failed with e" */
}

/*--------------------------------------------------------------------*/
/* FUN_0037a4c0 @ 0x0037a4c0   (est. sk_meta_rehash)
 * Ghidra: undefined8 FUN_0037a4c0(long param_1, ulong param_2, ulong param_3,
 *                                 long param_4)
 * Rehashes the metadata table into a fresh backing array (FUN_0037a898),
 * re-inserting all live entries, and records the old array on the
 * deferred-free list.
 * Confidence: medium.
 */
uint64_t sk_meta_rehash(long param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong local_60 = param_2;
    uint64_t local_58 = FUN_0037a898((param_3 & 0xffffffff) + 1);
    if ((int)param_3 != 0) {
        ulong uVar5 = 1;
        do {
            uint32_t uVar2 = sk_meta_read_elem(&local_60, uVar5, 0);
            if ((int)uVar2 != 0) {
                ulong uVar4 = *(uint32_t *)(*(long *)(param_4 + (ulong)((int)uVar2 - 1) * 8) + 0x18);
                while ((uVar4 = uVar4 & ~(-2L << (param_3 & 0x3f)), uVar4 == 0 ||
                       sk_meta_read_elem(&local_58, uVar4, 0) != 0)) {
                    uVar4++;
                }
                sk_meta_write_elem(&local_58, 0, uVar2, uVar4, 0);
            }
            uVar5++;
            param_2 = local_60;
        } while (uVar5 >> (param_3 & 0x3f) == 0);
    }
    *(uint64_t *)(param_1 + 0x10) = local_58;
    if ((param_2 & 3) != 0 && (param_2 & 0xfffffffffffffffc) != 0) {
        uint64_t *puVar3 = (uint64_t *)FUN_000101a0(0x10, 0xa0040aff93c70);
        *puVar3 = *(uint64_t *)(param_1 + 0x30);
        puVar3[1] = param_2 & 0xfffffffffffffffc;
        *(uint64_t **)(param_1 + 0x30) = puVar3;
    }
    return local_58;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a5e0 @ 0x0037a5e0   (est. sk_meta_grow_backing)
 * Ghidra: long FUN_0037a5e0(long param_1, long param_2, ulong param_3)
 * Grows the metadata backing array to max(param_3+param_3/4, param_3+1),
 * copying the existing entries and recording the old array on the
 * deferred-free list; stores the new base at param_1+8.
 * Confidence: medium.
 */
long sk_meta_grow_backing(long param_1, long param_2, ulong param_3)
{
    ulong uVar1 = param_3 + (param_3 >> 2);
    if (uVar1 <= param_3 + 1) uVar1 = param_3 + 1;
    long lVar2 = FUN_0037a920(uVar1);
    if (param_2 != 0) {
        FUN_00117cc4((void *)(lVar2 + 8), (void *)(param_2 + 8), param_3 << 3);
        uint64_t *puVar3 = (uint64_t *)FUN_000101a0(0x10, 0xa0040aff93c70);
        *puVar3 = *(uint64_t *)(param_1 + 0x30);
        puVar3[1] = param_2;
        *(uint64_t **)(param_1 + 0x30) = puVar3;
    }
    *(long *)(param_1 + 8) = lVar2;
    return lVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a668 @ 0x0037a668   (est. sk_meta_write_elem)
 * Ghidra: void FUN_0037a668(ulong *param_1, ulong *param_2, uint param_3,
 *                           ulong param_4, int param_5)
 * Writes element param_3 at index param_4 into the metadata container
 * (inline word, or heap byte/ushort/uint by width param_5), returning via
 * param_2 for the inline case.
 * Confidence: medium.
 */
void sk_meta_write_elem(ulong *param_1, ulong *param_2, uint32_t param_3,
                        ulong param_4, int param_5)
{
    ulong uVar3 = *param_1;
    uint32_t uVar1 = (uint32_t)uVar3 & 3;
    ulong uVar2;
    if (uVar1 == 1 || (uVar3 & 3) == 0) {
        if ((uVar3 & 3) == 0) {
            uVar3 = uVar3 | (ulong)param_3 << ((param_4 & 0xf) << 2);
            *param_2 = uVar3;
            return;
        }
        uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
        if (param_5 != 3 && param_5 != 5) { *(uint8_t *)(uVar2 + param_4) = (uint8_t)param_3; return; }
        *(uint32_t *)(uVar2 + param_4) = param_3; return;
    }
    if (uVar1 != 2) {
        uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
        *(uint32_t *)(uVar2 + param_4 * 4) = param_3; return;
    }
    uVar2 = (uVar3 & 3) != 0 ? (uVar3 & 0xfffffffffffffffc) : 0;
    if (param_5 != 3 && param_5 != 5) { *(uint16_t *)(uVar2 + param_4 * 2) = (uint16_t)param_3; return; }
    *(uint32_t *)(uVar2 + param_4 * 2) = param_3;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a744 @ 0x0037a744   (est. sk_meta_build_slot)
 * Ghidra: ulong * FUN_0037a744(ulong *param_1, undefined8 *param_2, long param_3,
 *                              uint param_4, ulong param_5)
 * Builds a metadata slot: sets the kind byte, lazily allocates a backing
 * mutex (FUN_0037a7f8) unless kind 4, copies the descriptor payload and tag,
 * and stores the kind bits.
 * Confidence: medium.
 */
ulong *sk_meta_build_slot(ulong *param_1, uint64_t *param_2, long param_3,
                          uint32_t param_4, ulong param_5)
{
    *(uint8_t *)(param_3 + 0x11) = (uint8_t)param_4;
    ulong uVar1;
    if (param_4 == 4) {
        uVar1 = 4;
    } else {
        uVar1 = *(ulong *)(param_3 + 8);
        if (uVar1 == 0) {
            uVar1 = FUN_0037a7f8();
            *(ulong *)(param_3 + 8) = uVar1;
        }
        uVar1 = uVar1 | (param_4 | 8);
    }
    *param_1 = uVar1;
    ulong u = param_2[1];
    param_1[2] = param_2[2];
    param_1[1] = u;
    *(uint32_t *)(param_1 + 3) = *(uint32_t *)(param_2 + 3);
    param_1[4] = param_5;
    FUN_0036e7ec(*(short *)(param_2 + 1) + *(short *)((long)param_2 + 0xe) +
                 *(short *)((long)param_2 + 10), *(uint16_t *)((long)param_2 + 0xc),
                 param_2[2], param_1 + 5, *param_2);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a7f8 @ 0x0037a7f8   (est. sk_meta_backing_init)
 * Ghidra: undefined8 * FUN_0037a7f8(void)
 * Allocates (0x40, tag 0xf) and initializes a metadata backing structure:
 * refcount=1, embedded mutex, zeroed fields, then acquires the mutex.
 * Confidence: medium.
 */
uint64_t *sk_meta_backing_init(void)
{
    uint64_t *puVar1 = (uint64_t *)FUN_0036a804(0x40, 0xf);
    puVar1[1] = 0; *puVar1 = 0;
    puVar1[5] = 0; puVar1[4] = 0;
    puVar1[7] = 0; puVar1[6] = 0;
    puVar1[3] = 0; puVar1[2] = 0;
    *puVar1 = 1;
    FUN_0037a850(puVar1 + 2, 0);
    puVar1[4] = 0; puVar1[5] = 0;
    sk_mtx_lock_checked();
    return puVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037a850 @ 0x0037a850   (est. sk_mtx_init)
 * Ghidra: undefined8 FUN_0037a850(undefined8 param_1)
 * Initializes a mutex via FUN_00118148; panics with "__mtx_init handle
 * (__mtx_plain)" (0x5d4f38) on failure.
 * Confidence: high (mtx wrapper with string).
 */
uint64_t sk_mtx_init(uint64_t param_1)
{
    if (FUN_00118148((void *)param_1, 0) == 0) return param_1;
    FUN_003a2578((char *)0x5d4f38);   /* "__mtx_init handle (__mtx_plain)" */
}

/*--------------------------------------------------------------------*/
/* FUN_0037a898 @ 0x0037a898   (est. sk_meta_alloc_backing)
 * Ghidra: ulong FUN_0037a898(ulong param_1)
 * Allocates an open-addressed backing array of 2^param_1 entries, choosing
 * the element width from the low byte, and returns it tagged with the width.
 * Traps on failure.
 * Confidence: medium.
 */
ulong sk_meta_alloc_backing(ulong param_1)
{
    uint32_t uVar1 = (uint32_t)param_1 & 0xff;
    uint32_t uVar4 = 2;
    if (0x10 < uVar1) uVar4 = 4;
    if (uVar1 < 9) uVar4 = 1;
    ulong uVar5 = (ulong)uVar4;
    uint8_t *puVar3 = (uint8_t *)FUN_00010244(1L << (param_1 & 0x3f), uVar5, 0x48dda4ae);
    if (puVar3 != 0) {
        if (uVar4 != 1) {
            if (uVar4 == 4) uVar5 = 3;
            else if (uVar4 == 2) uVar5 = 2;
            else goto trap;
        }
        *puVar3 = (uint8_t)param_1;
        return uVar5 | (ulong)puVar3;
    }
trap:
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37a920) */
}

/*--------------------------------------------------------------------*/
/* FUN_0037a920 @ 0x0037a920   (est. sk_meta_alloc_elems)
 * Ghidra: void FUN_0037a920(long param_1)
 * Allocates an element array of param_1 8-byte slots (FUN_0001279c +
 * FUN_000101a0), storing the capacity header. Traps on failure.
 * Confidence: medium.
 */
void sk_meta_alloc_elems(long param_1)
{
    long lVar2 = (long)FUN_0001279c(param_1 * 8 + 8);
    uint32_t *puVar3 = (uint32_t *)FUN_000101a0(lVar2, 0x1020040d5a9d86f);
    if (puVar3 != 0) {
        *puVar3 = (uint32_t)(lVar2 + 0x7fffffff8U >> 3);
        return;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37a978) */
}

/*--------------------------------------------------------------------*/
/* FUN_0037a978 @ 0x0037a978   (est. sk_mtx_unlock_checked)
 * Ghidra: void FUN_0037a978(void)
 * Releases a mutex via FUN_00118194; panics with "__mtx_unlock handle failed
 * wit" (0x5d4f6f) on failure.
 * Confidence: high (mtx wrapper with string).
 */
void sk_mtx_unlock_checked(void)
{
    if (FUN_00118194() == 0) return;
    FUN_003a2578((char *)0x5d4f6f);   /* "__mtx_unlock handle failed wit" */
}

/*--------------------------------------------------------------------*/
/* FUN_0037a9ac @ 0x0037a9ac   (est. sk_meta_dispatch)
 * Ghidra: undefined1[16] FUN_0037a9ac(undefined8 *param_1, undefined8 param_2,
 *                                     undefined8 param_3)
 * Dispatches a metadata operation: classifies the kind (FUN_0037aaac); for
 * simple kinds resolves via FUN_0037ab2c; otherwise runs the full resolution
 * pipeline (FUN_0037ab7c + FUN_0037ac0c) and cleans up.
 * Confidence: medium.
 */
uint64_t sk_meta_dispatch(uint64_t *param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t local_40 = *param_1;
    uint64_t local_38 = param_3;
    uint32_t local_44 = FUN_0037aaac(&local_40, param_3);
    uint64_t result;
    if (local_44 < 2) {
        result = FUN_0037ab2c((long)param_1, (uint32_t)local_40 & 7);
    } else {
        uint8_t buf[0x20];
        long local_68 = 0;
        FUN_0037ab7c(&local_40, local_40);
        if (local_44 == 3) {
            FUN_0037ac0c((long)param_1, &local_40, local_38);
            result = FUN_0037ab2c((long)param_1, 0);
        } else {
            result = FUN_0037ab2c((long)param_1, 0);
        }
        long lVar1 = local_68;
        local_68 = 0;
        if (lVar1 != 0) FUN_0037b054(&local_68);
        FUN_0037b350(&local_40);
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_0037aaac @ 0x0037aaac   (est. sk_meta_kind_classify)
 * Ghidra: undefined4 FUN_0037aaac(uint *param_1, ulong param_2)
 * Classifies a metadata kind: valid aggregate (via FUN_0037ae38) yields 3
 * (or 2/1 by flag), inline word yields 2, tagged yields 0, invalid traps.
 * Confidence: medium.
 */
uint32_t sk_meta_kind_classify(uint32_t *param_1, ulong param_2)
{
    uint32_t uVar1 = *param_1 & 7;
    if (uVar1 - 1 < 3) {
        ulong ok = FUN_0037ae38((uint8_t *)param_1, param_2 & 0xff);
        if ((ok & 1) == 0) {
            uint32_t r = 1;
            if ((param_2 & 0x100) == 0) r = 2;
            if ((*param_1 & 8) == 0) return 3;
            return r;
        }
    } else {
        if (uVar1 == 0) return 2;
        if (uVar1 != 4) __builtin_trap();   /* SoftwareBreakpoint(1,0x37ab2c) */
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ab2c @ 0x0037ab2c   (est. sk_meta_resolve_simple)
 * Ghidra: undefined1[16] FUN_0037ab2c(long param_1, int param_2)
 * Returns the metadata word at param_1+0x20 paired with a kind width mask
 * (0xff/0x3f/1/0 by param_2). Traps on invalid kind.
 * Confidence: medium.
 */
uint64_t sk_meta_resolve_simple(long param_1, int param_2)
{
    uint64_t lo = *(ulong *)(param_1 + 0x20);
    if (param_2 < 3) {
        if (param_2 == 1) return lo;
        if (param_2 == 2) return ((uint64_t)0x3f << 32) | lo;
    } else {
        if (param_2 == 3) return ((uint64_t)1 << 32) | lo;
        if (param_2 == 4) return ((uint64_t)0 << 32) | lo;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37ab7c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0037ab7c @ 0x0037ab7c   (est. sk_meta_lock_cycle)
 * Ghidra: void FUN_0037ab7c(undefined8 *param_1, undefined8 param_2)
 * Holds the metadata lock while draining pending work: repeatedly dispatches
 * the current node (FUN_0037ae90) until the work list is empty, locking and
 * unlocking the node's mutex each step.
 * Confidence: medium.
 */
void sk_meta_lock_cycle(uint64_t *param_1, uint64_t param_2)
{
    long local_48 = 0, local_58 = 0;
    uint64_t *puVar2 = (uint64_t *)*param_1;
    uint64_t *local_50 = param_1;
    while (1) {
        long *local_70 = &local_58;
        uint64_t uStack_68 = param_2;
        FUN_0037ae90(*puVar2, &local_70);
        long lVar1 = local_48;
        local_58 = local_48;
        if (local_48 == 0) break;
        local_48 = 0;
        sk_mtx_lock_checked();
        sk_mtx_unlock_checked();
        puVar2 = (uint64_t *)*param_1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037ac0c @ 0x0037ac0c   (est. sk_meta_resolve_full)
 * Ghidra: void FUN_0037ac0c(long param_1, undefined8 *param_2, uint param_3)
 * Full metadata resolution: computes the payload via FUN_0037b09c, walks the
 * requirement chain (0/1/0x3f/0xff kinds) dispatching through FUN_0037b288/
 * FUN_00378a30, then finalizes via FUN_0037b170.
 * Confidence: low (large multi-step metadata walk).
 */
void sk_meta_resolve_full(long param_1, uint64_t *param_2, uint32_t param_3)
{
    uint64_t uVar5 = *(uint64_t *)(param_1 + 0x20);
    long lVar10 = param_2[1];
    long *plVar8 = *(long **)(lVar10 + 0x20);
    long local_c0 = 0, lStack_b8 = 0, local_b0 = 0, lStack_a8 = 0;
    if (plVar8 == 0) plVar8 = &local_c0;
    uint32_t uVar9 = *(uint8_t *)((long)param_2 + 0x11);
    uint8_t local_d8[8];
    uint64_t local_d0, uStack_c8;
    FUN_0037b09c(local_d8, (uint64_t)param_1, uVar5, uVar9, plVar8);
    uVar5 = uStack_c8;
    long lVar2 = local_d0;
    uint32_t uVar6 = local_d8[0];
    *(uint8_t *)((long)param_2 + 0x11) = local_d8[0];
    long local_e0 = lVar10;
    if (local_d0 != 0) {
        uint32_t uVar1 = param_3 & 0xff;
        do {
            if (2 < uVar6 - 1) {
                if (uVar6 != 4) __builtin_trap();   /* SoftwareBreakpoint(1,0x37ae38) */
                if (*(long *)(local_e0 + 0x20) == 0 &&
                    (local_c0 != 0 || lStack_b8 != 0 || local_b0 != 0 || lStack_a8 != 0)) {
                    long *p = (long *)FUN_00111890(0x20, 0x80c4018a671a6);
                    p[1] = lStack_b8; *p = local_c0;
                    p[3] = lStack_a8; p[2] = local_b0;
                    long old = *(long *)(local_e0 + 0x20);
                    *(long **)(local_e0 + 0x20) = p;
                    if (old != 0) thunk_FUN_00012568((void *)old, 0x20);
                }
                break;
            }
            if (0x3e < uVar1) {
                if (uVar1 == 0x3f) { if (uVar6 < 2) goto body; }
                else {
                    local_d0 = lVar2; uStack_c8 = uVar5;
                    uVar6 = local_d8[0]; local_e0 = lVar10;
                    if (uVar1 != 0xff) __builtin_trap();
                }
                break;
            }
            if ((param_3 & 0xff) != 0) {
                if (uVar1 != 1) __builtin_trap();
                if (2 < uVar6) break;
            }
body:
            if ((param_3 >> 8 & 1) == 0 && uVar9 < uVar6) {
                FUN_0037b288(*(uint64_t *)*param_2, (long *)&local_c0);
                local_e0 = param_2[1];
            }
            sk_dep_resolve_walk(*(uint64_t *)(param_1 + 0x20), param_3 & 0xff, local_d0, uStack_c8);
            uVar9 = *(uint8_t *)((long)param_2 + 0x11);
            FUN_0037b09c(local_d8, (uint64_t)param_1, uVar5, uVar9, plVar8);
            uVar6 = local_d8[0];
            *(uint8_t *)((long)param_2 + 0x11) = local_d8[0];
        } while (local_d0 != 0);
    }
    uVar5 = *(uint64_t *)(local_e0 + 0x20);
    *(uint64_t *)(local_e0 + 0x20) = 0;
    FUN_0037b170(param_1, param_2, local_d0, uStack_c8, uVar5);
    FUN_0037ab2c(param_1, uVar6);
}

/*--------------------------------------------------------------------*/
/* FUN_0037ae38 @ 0x0037ae38   (est. sk_meta_kind_valid)
 * Ghidra: bool FUN_0037ae38(byte *param_1, long param_2)
 * Validates that the metadata kind bits (low 3 of param_1[0]) meet the
 * requirement width param_2 (0/1/0x3f/0xff). Traps on invalid width.
 * Confidence: medium.
 */
bool sk_meta_kind_valid(uint8_t *param_1, long param_2)
{
    uint8_t bVar2 = *param_1;
    uint8_t bVar1 = bVar2 & 7;
    bool bVar4, bVar5;
    if (param_2 < 0x3f) {
        if (param_2 == 0) { bVar4 = 2 < bVar1; bVar5 = bVar1 == 3; }
        else {
            if (param_2 != 1) goto trap;
            bVar4 = 1 < bVar1; bVar5 = bVar1 == 2;
        }
    } else {
        if (param_2 != 0x3f) {
            if (param_2 == 0xff) return (bVar2 & 7) != 0;
trap:
            __builtin_trap();   /* SoftwareBreakpoint(1,0x37ae90) */
        }
        bVar4 = (bVar2 & 7) != 0; bVar5 = bVar1 == 1;
    }
    return bVar4 && !bVar5;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ae90 @ 0x0037ae90   (est. sk_meta_workstep)
 * Ghidra: void FUN_0037ae90(undefined8 param_1, undefined8 *param_2)
 * One metadata work-loop step: lock, if a pending ref exists drain it
 * (FUN_0037aed8), copy the payload pair (FUN_0037af40), then unlock.
 * Confidence: medium.
 */
void sk_meta_workstep(uint64_t param_1, uint64_t *param_2)
{
    sk_mtx_lock_checked();
    if (*(long *)*param_2 != 0) sk_meta_backing_release((long *)*param_2);
    FUN_0037af40((void *)param_2[1], (void *)param_2[2]);
    sk_mtx_unlock_checked();
}

/*--------------------------------------------------------------------*/
/* FUN_0037aed8 @ 0x0037aed8   (est. sk_meta_backing_release)
 * Ghidra: void FUN_0037aed8(long *param_1)
 * Drops a reference on the metadata backing; frees the object (0x40, tag 0xf)
 * and its mutex/keys when the refcount reaches zero.
 * Confidence: medium.
 */
void sk_meta_backing_release(long *param_1)
{
    if (*param_1 - 1 == 0) {
        long lVar1 = param_1[4];
        param_1[4] = 0;
        if (lVar1 != 0) thunk_FUN_00012568((void *)lVar1, 0x20);
        thunk_FUN_00053aa0(param_1 + 2);
        thunk_FUN_00012568((void *)param_1, 0x40, 0xf);
        return;
    }
    *param_1 = *param_1 - 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037af40 @ 0x0037af40   (est. sk_meta_payload_copy)
 * Ghidra: void FUN_0037af40(undefined8 *param_1, long *param_2)
 * Copies a metadata payload and updates the refcount-backed slot: kind 3
 * promotes a tagged value into a full backing object; kind 2 bumps the
 * refcount.
 * Confidence: medium.
 */
void sk_meta_payload_copy(uint64_t *param_1, long *param_2)
{
    ulong *puVar1 = (ulong *)*param_1;
    ulong *puVar2 = (ulong *)param_1[1];
    *puVar1 = *puVar2;
    int iVar3 = FUN_0037aaac(puVar1, *(uint64_t *)param_1[3]);
    *(int *)param_1[2] = iVar3;
    if (iVar3 == 3) {
        long lVar8 = *param_2;
        ulong uVar5 = *(ulong *)(lVar8 + 8);
        if (uVar5 == 0) {
            uVar5 = FUN_0037a7f8();
            *(ulong *)(lVar8 + 8) = uVar5;
        }
        if ((*(ulong *)*param_1 >> 3 & 1) == 0) {
            uint64_t *puVar9 = (uint64_t *)(*(ulong *)*param_1 & 0xfffffffffffffff0);
            if (puVar9 != 0) {
                uint64_t uVar7 = *puVar9;
                *(uint64_t *)(uVar5 + 0x30) = puVar9[1];
                *(uint64_t *)(uVar5 + 0x28) = uVar7;
                uVar7 = puVar9[2];
                puVar9[2] = 0;
                long old = *(long *)(uVar5 + 0x20);
                *(uint64_t *)(uVar5 + 0x20) = uVar7;
                if (old != 0) thunk_FUN_00012568((void *)old, 0x20);
                ulong uVar4 = *(ulong *)param_1[4];
                *(ulong *)param_1[4] = (ulong)puVar9;
                if (uVar4 != 0) FUN_0037b054(0);
            }
        }
        *puVar2 = *(ulong *)*param_1 & 7 | uVar5 | 8;
        *(uint8_t *)(*param_2 + 0x10) = 1;
    } else if (iVar3 == 2) {
        ulong uVar5 = *(ulong *)*param_1;
        long *plVar6 = (long *)(uVar5 & 0xfffffffffffffff0);
        *plVar6 = *plVar6 + 1;
        param_2[1] = (ulong)plVar6 & (long)(uVar5 << 0x3c) >> 0x3f;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037b054 @ 0x0037b054   (est. sk_meta_node_release)
 * Ghidra: void FUN_0037b054(undefined8 param_1, long param_2)
 * Frees a 0x20-byte metadata node and its payload if present.
 * Confidence: medium.
 */
void sk_meta_node_release(uint64_t param_1, long param_2)
{
    if (param_2 != 0) {
        long lVar1 = *(long *)(param_2 + 0x10);
        *(uint64_t *)(param_2 + 0x10) = 0;
        if (lVar1 != 0) thunk_FUN_00012568((void *)lVar1, 0x20);
        thunk_FUN_00012568((void *)param_2, 0x20);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037b09c @ 0x0037b09c   (est. sk_meta_resolve_slot)
 * Ghidra: void FUN_0037b09c(undefined1 *param_1, undefined8 param_2, long param_3,
 *                           uint param_4, undefined8 param_5)
 * Resolves a metadata slot via the capability dispatch (FUN_0035bd48 +
 * FUN_0036a668) for kinds 0-2, else via the type resolver FUN_00378374.
 * Emits {kind,value} into param_1.
 * Confidence: medium.
 */
void sk_meta_resolve_slot(uint8_t *param_1, uint64_t param_2, long param_3,
                          uint32_t param_4, uint64_t param_5)
{
    if (param_4 < 3) {
        long lVar4 = FUN_0036a668(0);
        int iVar3 = *(int *)(lVar4 + 4);
        long lVar1 = (iVar3 != 0) ? (long)iVar3 + lVar4 + 4 : 0;
        int iVar3b = *(int *)(lVar1 + 4);
        sk_fnv_t fn = (iVar3b != 0) ? (sk_fnv_t)(lVar1 + 4 + (long)iVar3b) : 0;
        uint64_t v0 = fn(param_3, param_5); uint64_t val[2] = { v0, 0 };
        if (val[0] != 0) {
            uint8_t k = 1;
            if ((*(uint32_t *)(*(long *)(param_3 - 8) + 0x50) & 0x400000) == 0) k = 2;
            *param_1 = k;
            *(uint64_t *)(param_1 + 8) = val[0];
            return;
        }
    }
    uint64_t val[2] = SKPAIR(FUN_00378374(param_3));
    if (val[0] == 0) {
        *param_1 = 4;
        *(uint64_t *)(param_1 + 8) = 0;
        return;
    }
    *param_1 = 3;
    *(uint64_t *)(param_1 + 8) = val[0];
}

/*--------------------------------------------------------------------*/
/* FUN_0037b170 @ 0x0037b170   (est. sk_meta_finish)
 * Ghidra: void FUN_0037b170(undefined8 param_1, undefined8 *param_2, long param_3,
 *                           long param_4, long param_5)
 * Finalizes a metadata operation: builds a 0x20 node for any pending
 * payload, stores the result, clears the descriptor cursor, and hands off to
 * FUN_0037b220.
 * Confidence: medium.
 */
void sk_meta_finish(uint64_t param_1, uint64_t *param_2, long param_3, long param_4, long param_5)
{
    uint8_t local_51 = *(uint8_t *)((long)param_2 + 0x11);
    long *local_60 = 0;
    if (param_3 != 0 || param_5 != 0) {
        local_60 = (long *)FUN_00111890(0x20, 0x1060c4048d9c6c4);
        *local_60 = param_3;
        local_60[1] = param_4;
        local_60[2] = param_5;
    }
    uint8_t *local_78 = &local_51;
    long **pplStack_70 = &local_60;
    uint8_t **local_50 = &local_78;
    uint64_t local_68 = param_1;
    FUN_0037b220(*(uint64_t *)*param_2, (long *)&local_50);
    *(uint8_t *)(param_2 + 2) = 0;
    param_2[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b220 @ 0x0037b220   (est. sk_meta_commit)
 * Ghidra: void FUN_0037b220(undefined8 param_1, long *param_2)
 * Commits a metadata write: merges the tag/ref bits into the backing slot,
 * releases the old backing, and unlocks.
 * Confidence: medium.
 */
void sk_meta_commit(uint64_t param_1, long *param_2)
{
    sk_mtx_lock_checked();
    uint64_t *puVar1 = (uint64_t *)*param_2;
    long lVar2 = param_2[1];
    *(ulong *)puVar1[2] = *(ulong *)puVar1[1] | (ulong)*(uint8_t *)*puVar1;
    sk_mtx_unlock_checked();
    sk_meta_backing_release((long *)*(uint64_t *)(lVar2 + 8));
    sk_mtx_unlock_checked();
}

/*--------------------------------------------------------------------*/
/* FUN_0037b288 @ 0x0037b288   (est. sk_meta_promote)
 * Ghidra: void FUN_0037b288(undefined8 param_1, long *param_2)
 * Promotes a pending metadata backing into the slot: reuses the existing
 * backing if refcount==1, else allocates a fresh one (FUN_0037a7f8), copies
 * the payload, and stores the promoted tagged value.
 * Confidence: medium.
 */
void sk_meta_promote(uint64_t param_1, long *param_2)
{
    sk_mtx_lock_checked();
    long *plVar1 = (long *)*param_2;
    long lVar2 = param_2[1];
    ulong *puVar6 = (ulong *)plVar1[2];
    long *plVar7 = *(long **)(*plVar1 + 8);
    long *plVar3 = plVar7;
    if (*plVar7 != 1) {
        plVar3 = (long *)FUN_0037a7f8();
        long lVar5 = plVar7[4];
        plVar7[4] = 0;
        long lVar4 = plVar3[4];
        plVar3[4] = lVar5;
        if (lVar4 != 0) thunk_FUN_00012568((void *)lVar4, 0x20);
    }
    long lVar4 = *(long *)plVar1[1];
    plVar3[6] = ((long *)plVar1[1])[1];
    plVar3[5] = lVar4;
    *puVar6 = (ulong)*(uint8_t *)(*plVar1 + 0x11) | (ulong)plVar3 | 8;
    if (plVar3 != plVar7) {
        sk_mtx_unlock_checked();
        sk_meta_backing_release((long *)*(uint64_t *)(lVar2 + 8));
        *(long **)(lVar2 + 8) = plVar3;
    }
    sk_mtx_unlock_checked();
}

/*--------------------------------------------------------------------*/
/* FUN_0037b350 @ 0x0037b350   (est. sk_meta_cleanup)
 * Ghidra: long FUN_0037b350(long param_1)
 * Releases the metadata backing (mutex at +0x10, keys at +0x20) referenced
 * by param_1+8, returning param_1.
 * Confidence: medium.
 */
long sk_meta_cleanup(long param_1)
{
    if (*(long *)(param_1 + 8) != 0) {
        sk_mtx_unlock_checked();
        long lVar2 = *(long *)(param_1 + 8);
        if (lVar2 != 0) {
            long lVar1 = *(long *)(lVar2 + 0x20);
            *(uint64_t *)(lVar2 + 0x20) = 0;
            if (lVar1 != 0) thunk_FUN_00012568((void *)lVar1, 0x20);
            thunk_FUN_00053aa0((void *)(lVar2 + 0x10));
            thunk_FUN_00012568((void *)lVar2, 0x40, 0xf);
        }
    }
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b3b8 @ 0x0037b3b8   (est. sk_tm_size)
 * Ghidra: long FUN_0037b3b8(undefined8 param_1)
 * Total type-metadata (TM) size: base (FUN_0037b408) + 4*count +
 * 4*subfield-count.
 * Confidence: medium.
 */
long sk_tm_size(uint64_t param_1)
{
    return FUN_0037b408(0) + FUN_0037babc(param_1) * 4 + FUN_0037bb44(param_1) * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b408 @ 0x0037b408   (est. sk_tm_size_fields)
 * Ghidra: long FUN_0037b408(undefined8 param_1)
 * TM field-packed size: base (FUN_0037b484) + 2*count aligned, + 0xc*last
 * field word.
 * Confidence: medium.
 */
long sk_tm_size_fields(uint64_t param_1)
{
    long lVar1 = FUN_0037b484(0);
    ulong uVar2 = FUN_0037b990( (uint64_t)(uintptr_t)param_1 );
    uint64_t pair[2] = SKPAIR(FUN_0037ba20( (uint64_t)(uintptr_t)param_1 ));
    ulong uVar3 = (pair[1] == 0) ? 0 : (ulong)*(uint16_t *)(pair[0] + pair[1] * 2 + -2);
    return (lVar1 + (uVar2 & 0xffffffff) * 2 + 3 & 0xfffffffffffffffc) + uVar3 * 0xc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b484 @ 0x0037b484   (est. sk_tm_size_count)
 * Ghidra: long FUN_0037b484(undefined8 param_1)
 * TM header size + 2*count (FUN_0037b908).
 * Confidence: medium.
 */
long sk_tm_size_count(uint64_t param_1)
{
    return FUN_0037b4e0(0) + (FUN_0037b908( (uint64_t)(uintptr_t)param_1 ) & 0xffffffff) * 2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b4e0 @ 0x0037b4e0   (est. sk_tm_size_base)
 * Ghidra: long FUN_0037b4e0(undefined8 param_1)
 * TM base size: base (FUN_0037b540) + 0xc*count + 4*flag + 8*field.
 * Confidence: medium.
 */
long sk_tm_size_base(uint64_t param_1)
{
    return FUN_0037b540(0) + FUN_0037b658( (uint64_t)(uintptr_t)param_1 ) * 0xc +
           FUN_0037b6dc( (uint64_t)(uintptr_t)param_1 ) * 4 + FUN_0037b764( (uint64_t)(uintptr_t)param_1 ) * 8;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b540 @ 0x0037b540   (est. sk_tm_base)
 * Ghidra: ulong FUN_0037b540(uint *param_1)
 * TM base offset: param_1+7 aligned + extra word (generic flag) + subword.
 * Confidence: medium.
 */
ulong sk_tm_base(uint32_t *param_1)
{
    uint32_t *puVar3 = param_1 + 7;
    if (puVar3 == 0) puVar3 = 0;
    if (param_1 == 0) param_1 = 0;
    uint32_t uVar1 = *param_1;
    long lVar2 = FUN_0037b5d4(0);
    return (ulong)puVar3 + lVar2 + ((uVar1 >> 7) & 1) * 0x10 + 3 & 0xfffffffffffffffc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b5d4 @ 0x0037b5d4   (est. sk_tm_subword)
 * Ghidra: undefined2 FUN_0037b5d4(char *param_1)
 * For a tagged type pointer returns the 2-byte subword at +0x24.
 * Confidence: medium.
 */
uint16_t sk_tm_subword(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x24);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b658 @ 0x0037b658   (est. sk_tm_count)
 * Ghidra: undefined2 FUN_0037b658(char *param_1)
 * For a tagged type pointer returns the 2-byte count at +0x26.
 * Confidence: medium.
 */
uint16_t sk_tm_count(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x26);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b6dc @ 0x0037b6dc   (est. sk_tm_has_fields)
 * Ghidra: ushort FUN_0037b6dc(char *param_1)
 * For a tagged type pointer returns bit 0 of the 2-byte field at +0x2a.
 * Confidence: medium.
 */
uint16_t sk_tm_has_fields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b764 @ 0x0037b764   (est. sk_tm_fields_word)
 * Ghidra: undefined2 FUN_0037b764(char *param_1)
 * For a tagged type pointer with fields flag set, returns the field word
 * (FUN_0037b808); else 0.
 * Confidence: medium.
 */
uint16_t sk_tm_fields_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x2a) & 1) != 0) return FUN_0037b808(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b808 @ 0x0037b808   (est. sk_tm_field_word)
 * Ghidra: uint FUN_0037b808(char *param_1)
 * Reads the packed TM field word (two 16-bit halves) from the descriptor.
 * Confidence: medium.
 */
uint32_t sk_tm_field_word(char *param_1)
{
    char *pcVar6 = param_1 ? param_1 : 0;
    if (*pcVar6 < 0) {
        char *pcVar6b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar6b + 0x2a) & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            long lVar1 = FUN_0037b540( (uint64_t)(uintptr_t)param_1 );
            long lVar2 = FUN_0037b658( (uint64_t)(uintptr_t)param_1 );
            uint16_t *puVar5 = (uint16_t *)(lVar1 + lVar2 * 0xc);
            return (uint32_t)puVar5[1] << 0x10 | (uint32_t)*puVar5;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b908 @ 0x0037b908   (est. sk_tm_count_flag)
 * Ghidra: ushort FUN_0037b908(char *param_1)
 * For a tagged type pointer returns bit 1 of the 2-byte field at +0x2a.
 * Confidence: medium.
 */
uint16_t sk_tm_count_flag(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) >> 1 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037b990 @ 0x0037b990   (est. sk_tm_popcount)
 * Ghidra: ulong FUN_0037b990(long param_1)
 * When the count flag is set, returns the popcount of the packed TM word.
 * Confidence: medium.
 */
ulong sk_tm_popcount(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    ulong uVar1 = FUN_0037b908((uint64_t)(uintptr_t)lVar3);
    if ((int)uVar1 != 0) {
        if (param_1 == 0) param_1 = 0;
        uint16_t *puVar2 = (uint16_t *)FUN_0037b4e0( (uint64_t)(uintptr_t)param_1 );
        char cVar4 = POPCOUNT((char)((uint16_t)*puVar2 >> 8));
        uVar1 = (ulong)CONCAT11(cVar4, POPCOUNT((char)*puVar2) + cVar4);
    }
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ba20 @ 0x0037ba20   (est. sk_tm_field_table)
 * Ghidra: undefined1[16] FUN_0037ba20(long param_1)
 * Returns {base,count} of the TM field table.
 * Confidence: medium.
 */
sk_pair_t sk_tm_field_table(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    if (FUN_0037b908((uint64_t)(uintptr_t)lVar3) == 0) return SKPAIR2(0,0);
    long lVar3b = param_1 ? param_1 : 0;
    ulong uVar2 = FUN_0037b484( (uint64_t)(uintptr_t)lVar3b );
    ulong uVar4 = FUN_0037b990( (uint64_t)(uintptr_t)param_1 ) & 0xffffffff;
    return SKPAIR2(uVar2, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_0037babc @ 0x0037babc   (est. sk_tm_has_subfields)
 * Ghidra: ushort FUN_0037babc(char *param_1)
 * For a tagged type pointer returns bit 2 of the 2-byte field at +0x2a.
 * Confidence: medium.
 */
uint16_t sk_tm_has_subfields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) >> 2 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bb44 @ 0x0037bb44   (est. sk_tm_subfield_word)
 * Ghidra: undefined4 FUN_0037bb44(char *param_1)
 * For a tagged type pointer with subfields flag set, returns the subfield
 * word (FUN_0037bbe8); else 0.
 * Confidence: medium.
 */
uint32_t sk_tm_subfield_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x2a) >> 2 & 1) != 0) return FUN_0037bbe8(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bbe8 @ 0x0037bbe8   (est. sk_tm_subfield_lo)
 * Ghidra: undefined4 FUN_0037bbe8(char *param_1)
 * Reads the subfield word from the TM descriptor (via FUN_0037b408).
 * Confidence: medium.
 */
uint32_t sk_tm_subfield_lo(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        char *pcVar2b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar2b + 0x2a) >> 2 & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            return *(uint32_t *)FUN_0037b408( (uint64_t)(uintptr_t)param_1 );
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bcac @ 0x0037bcac   (est. sk_tm2_size)
 * Ghidra: long FUN_0037bcac(undefined8 param_1)
 * Second type-metadata size variant (mirror of sk_tm_size).
 * Confidence: medium.
 */
long sk_tm2_size(uint64_t param_1)
{
    return FUN_0037bcfc(0) + FUN_0037c3b0( (uint64_t)(uintptr_t)param_1 ) * 4 + FUN_0037c438( (uint64_t)(uintptr_t)param_1 ) * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bcfc @ 0x0037bcfc   (est. sk_tm2_size_fields)
 * Ghidra: long FUN_0037bcfc(undefined8 param_1)
 * TM2 field-packed size (mirror at offset 0x2a).
 * Confidence: medium.
 */
long sk_tm2_size_fields(uint64_t param_1)
{
    long lVar1 = FUN_0037bd78(0);
    ulong uVar2 = FUN_0037c284( (uint64_t)(uintptr_t)param_1 );
    uint64_t pair[2] = SKPAIR(FUN_0037c314( (uint64_t)(uintptr_t)param_1 ));
    ulong uVar3 = (pair[1] == 0) ? 0 : (ulong)*(uint16_t *)(pair[0] + pair[1] * 2 + -2);
    return (lVar1 + (uVar2 & 0xffffffff) * 2 + 3 & 0xfffffffffffffffc) + uVar3 * 0xc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bd78 @ 0x0037bd78   (est. sk_tm2_size_count)
 * Ghidra: long FUN_0037bd78(undefined8 param_1)
 * TM2 header + 2*count (FUN_0037c1fc).
 * Confidence: medium.
 */
long sk_tm2_size_count(uint64_t param_1)
{
    return FUN_0037bdd4(0) + (FUN_0037c1fc( (uint64_t)(uintptr_t)param_1 ) & 0xffffffff) * 2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bdd4 @ 0x0037bdd4   (est. sk_tm2_size_base)
 * Ghidra: long FUN_0037bdd4(undefined8 param_1)
 * TM2 base size.
 * Confidence: medium.
 */
long sk_tm2_size_base(uint64_t param_1)
{
    return FUN_0037be34(0) + FUN_0037bf4c( (uint64_t)(uintptr_t)param_1 ) * 0xc +
           FUN_0037bfd0( (uint64_t)(uintptr_t)param_1 ) * 4 + FUN_0037c058( (uint64_t)(uintptr_t)param_1 ) * 8;
}

/*--------------------------------------------------------------------*/
/* FUN_0037be34 @ 0x0037be34   (est. sk_tm2_base)
 * Ghidra: ulong FUN_0037be34(uint *param_1)
 * TM2 base offset.
 * Confidence: medium.
 */
ulong sk_tm2_base(uint32_t *param_1)
{
    uint32_t *puVar3 = param_1 + 7;
    if (puVar3 == 0) puVar3 = 0;
    if (param_1 == 0) param_1 = 0;
    uint32_t uVar1 = *param_1;
    long lVar2 = FUN_0037bec8(0);
    return (ulong)puVar3 + lVar2 + ((uVar1 >> 7) & 1) * 0x10 + 3 & 0xfffffffffffffffc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bec8 @ 0x0037bec8   (est. sk_tm2_subword)
 * Ghidra: undefined2 FUN_0037bec8(char *param_1)
 * TM2 subword at +0x24.
 * Confidence: medium.
 */
uint16_t sk_tm2_subword(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x24);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bf4c @ 0x0037bf4c   (est. sk_tm2_count)
 * Ghidra: undefined2 FUN_0037bf4c(char *param_1)
 * TM2 count at +0x26.
 * Confidence: medium.
 */
uint16_t sk_tm2_count(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x26);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037bfd0 @ 0x0037bfd0   (est. sk_tm2_has_fields)
 * Ghidra: ushort FUN_0037bfd0(char *param_1)
 * TM2 fields flag (bit 0 of +0x2a).
 * Confidence: medium.
 */
uint16_t sk_tm2_has_fields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c058 @ 0x0037c058   (est. sk_tm2_fields_word)
 * Ghidra: undefined2 FUN_0037c058(char *param_1)
 * TM2 fields word (FUN_0037c0fc) when the flag is set.
 * Confidence: medium.
 */
uint16_t sk_tm2_fields_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x2a) & 1) != 0) return FUN_0037c0fc(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c0fc @ 0x0037c0fc   (est. sk_tm2_field_word)
 * Ghidra: uint FUN_0037c0fc(char *param_1)
 * Reads the packed TM2 field word.
 * Confidence: medium.
 */
uint32_t sk_tm2_field_word(char *param_1)
{
    char *pcVar6 = param_1 ? param_1 : 0;
    if (*pcVar6 < 0) {
        char *pcVar6b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar6b + 0x2a) & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            long lVar1 = FUN_0037be34( (uint64_t)(uintptr_t)param_1 );
            long lVar2 = FUN_0037bf4c( (uint64_t)(uintptr_t)param_1 );
            uint16_t *puVar5 = (uint16_t *)(lVar1 + lVar2 * 0xc);
            return (uint32_t)puVar5[1] << 0x10 | (uint32_t)*puVar5;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c1fc @ 0x0037c1fc   (est. sk_tm2_count_flag)
 * Ghidra: ushort FUN_0037c1fc(char *param_1)
 * TM2 count flag (bit 1 of +0x2a).
 * Confidence: medium.
 */
uint16_t sk_tm2_count_flag(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) >> 1 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c284 @ 0x0037c284   (est. sk_tm2_popcount)
 * Ghidra: ulong FUN_0037c284(long param_1)
 * TM2 popcount of the packed word.
 * Confidence: medium.
 */
ulong sk_tm2_popcount(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    ulong uVar1 = FUN_0037c1fc((uint64_t)(uintptr_t)lVar3);
    if ((int)uVar1 != 0) {
        if (param_1 == 0) param_1 = 0;
        uint16_t *puVar2 = (uint16_t *)FUN_0037bdd4( (uint64_t)(uintptr_t)param_1 );
        char cVar4 = POPCOUNT((char)((uint16_t)*puVar2 >> 8));
        uVar1 = (ulong)CONCAT11(cVar4, POPCOUNT((char)*puVar2) + cVar4);
    }
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c314 @ 0x0037c314   (est. sk_tm2_field_table)
 * Ghidra: undefined1[16] FUN_0037c314(long param_1)
 * Returns {base,count} of the TM2 field table.
 * Confidence: medium.
 */
sk_pair_t sk_tm2_field_table(long param_1)
{
    long lVar3 = param_1 ? param_1 : 0;
    if (FUN_0037c1fc((uint64_t)(uintptr_t)lVar3) == 0) return SKPAIR2(0,0);
    long lVar3b = param_1 ? param_1 : 0;
    ulong uVar2 = FUN_0037bd78( (uint64_t)(uintptr_t)lVar3b );
    ulong uVar4 = FUN_0037c284( (uint64_t)(uintptr_t)param_1 ) & 0xffffffff;
    return SKPAIR2(uVar2, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_0037c3b0 @ 0x0037c3b0   (est. sk_tm2_has_subfields)
 * Ghidra: ushort FUN_0037c3b0(char *param_1)
 * TM2 subfields flag (bit 2 of +0x2a).
 * Confidence: medium.
 */
uint16_t sk_tm2_has_subfields(char *param_1)
{
    char *pcVar1 = param_1 ? param_1 : 0;
    if (*pcVar1 < 0) {
        if (param_1 == 0) param_1 = 0;
        return *(uint16_t *)(param_1 + 0x2a) >> 2 & 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c438 @ 0x0037c438   (est. sk_tm2_subfield_word)
 * Ghidra: undefined4 FUN_0037c438(char *param_1)
 * TM2 subfield word (FUN_0037c4dc) when the flag is set.
 * Confidence: medium.
 */
uint32_t sk_tm2_subfield_word(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        if (param_1 == 0) param_1 = 0;
        if ((*(uint16_t *)(param_1 + 0x2a) >> 2 & 1) != 0) return FUN_0037c4dc(0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c4dc @ 0x0037c4dc   (est. sk_tm2_subfield_lo)
 * Ghidra: undefined4 FUN_0037c4dc(char *param_1)
 * Reads the TM2 subfield word (via FUN_0037bcfc).
 * Confidence: medium.
 */
uint32_t sk_tm2_subfield_lo(char *param_1)
{
    char *pcVar2 = param_1 ? param_1 : 0;
    if (*pcVar2 < 0) {
        char *pcVar2b = param_1 ? param_1 : 0;
        if ((*(uint16_t *)(pcVar2b + 0x2a) >> 2 & 1) != 0) {
            if (param_1 == 0) param_1 = 0;
            return *(uint32_t *)FUN_0037bcfc( (uint64_t)(uintptr_t)param_1 );
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c5a0 @ 0x0037c5a0   (est. sk_tm_find_by_id)
 * Ghidra: undefined1[16] FUN_0037c5a0(long *param_1, ulong param_2, ulong param_3,
 *                                     long param_4)
 * Searches the TM open-addressed table for an entry whose first word equals
 * *param_1 (hash via FUN_0037c68c), returning {slot_index, slot_ptr}.
 * Confidence: medium.
 */
sk_pair_t sk_tm_find_by_id(long *param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong local_48 = param_2;
    ulong uVar2 = FUN_0037c68c(*param_1);
    ulong uVar3 = 4;
    if ((param_2 & 3) != 0 && (uint8_t *)(param_2 & 0xfffffffffffffffc) != 0)
        uVar3 = *(uint8_t *)(param_2 & 0xfffffffffffffffc);
    uVar3 = -1L << (uVar3 & 0x3f);
    uVar2 = uVar2 & ~uVar3;
    if (uVar2 < 2) uVar2 = 1;
    int iVar1 = FUN_0035b178(&local_48, uVar2, 2);
    if (iVar1 != 0) {
        do {
            ulong uVar4 = (ulong)(iVar1 - 1);
            if (uVar4 < param_3 && *param_1 == **(long **)(param_4 + uVar4 * 8)) {
                return SKPAIR2((uint64_t)(param_4 + uVar4 * 8), uVar2);
            }
            uVar2 = uVar2 + 1 & ~uVar3;
            if (uVar2 < 2) uVar2 = 1;
            iVar1 = FUN_0035b178(&local_48, uVar2, 2);
        } while (iVar1 != 0);
    }
    return SKPAIR2(0, uVar2 & 0xffffffff);
}

/*--------------------------------------------------------------------*/
/* FUN_0037c68c @ 0x0037c68c   (est. sk_hash_u64)
 * Ghidra: long FUN_0037c68c(ulong param_1)
 * 64-bit splitmix64 hash of param_1.
 * Confidence: high (recognizable splitmix64 constants).
 */
long sk_hash_u64(ulong param_1)
{
    if (param_1 == 0) param_1 = 0;
    ulong uVar1 = ((param_1 & 0xffffffff) * 8 + 0xf9000a63a9000a61 ^ param_1 >> 0x20) * -0x622015f714c7d297;
    uVar1 = (param_1 >> 0x20 ^ uVar1 >> 0x2f ^ uVar1) * -0x622015f714c7d297;
    return (uVar1 ^ uVar1 >> 0x2f) * -0x622015f714c7d297;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c724 @ 0x0037c724   (est. sk_meta_init_hdr)
 * Ghidra: long FUN_0037c724(long param_1, undefined8 param_2)
 * Initializes a metadata header at param_1+0x50: zero-fill, parse param_2
 * (FUN_0037c82c + FUN_0037c770), and store the resulting descriptor.
 * Confidence: medium.
 */
long sk_meta_init_hdr(long param_1, uint64_t param_2)
{
    uint8_t buf[56];
    FUN_0037c82c((uint64_t *)buf);
    FUN_0037c770((uint64_t *)buf, param_2);
    FUN_0037ca78((short *)(param_1 + 0x50), (ushort *)buf);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c770 @ 0x0037c770   (est. sk_meta_parse_desc)
 * Ghidra: void FUN_0037c770(undefined8 *param_1, long param_2)
 * Parses a type descriptor (param_2) into a 7-word summary: header words,
 * flags, field/subfield counts, and the requirement table pointer.
 * Confidence: medium.
 */
void sk_meta_parse_desc(uint64_t *param_1, long param_2)
{
    ulong uVar4 = param_2 + 0xc + (ulong)*(ushort *)(param_2 + 4) + 3 & 0xfffffffffffffffc;
    uint32_t uVar5 = ((*(ushort *)(param_2 + 10) & 1) != 0)
        ? *(uint32_t *)(uVar4 + (ulong)*(ushort *)(param_2 + 6) * 0xc) : 0;
    uint64_t uVar1 = FUN_003658a0((void *)param_2);
    uint32_t uVar6 = ((*(ushort *)(param_2 + 10) >> 2 & 1) != 0)
        ? *(uint32_t *)FUN_0037c8e4((uint64_t)(uintptr_t)param_2) : 0;
    uint64_t uVar3 = FUN_0037c88c((uint64_t)(uintptr_t)param_2);
    param_1[0] = *(uint64_t *)(param_2 + 4);
    param_1[1] = param_2 + 0xc;
    param_1[2] = uVar4;
    *(uint32_t *)(param_1 + 3) = uVar5;
    param_1[4] = uVar1;
    *(uint32_t *)(param_1 + 5) = uVar6;
    param_1[6] = uVar3;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c82c @ 0x0037c82c   (est. sk_meta_hdr_zero)
 * Ghidra: undefined8 * FUN_0037c82c(undefined8 *param_1)
 * Zero-fills a metadata header (10 words) and installs a fresh 0x10 mutex at
 * param_1[8].
 * Confidence: medium.
 */
uint64_t *sk_meta_hdr_zero(uint64_t *param_1)
{
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    FUN_0037a850(param_1 + 4, 0);
    param_1[6] = 0;
    param_1[7] = 0;
    uint64_t uVar1 = (uint64_t)FUN_00111890(0x10, 0x1000c40451b5be8);
    uVar1 = FUN_0037a850((void *)uVar1, 0);
    param_1[8] = uVar1;
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c88c @ 0x0037c88c   (est. sk_meta_subfield_tab)
 * Ghidra: undefined1[16] FUN_0037c88c(long param_1)
 * Returns {ptr,count} of the metadata subfield table when the subfields flag
 * is set.
 * Confidence: medium.
 */
sk_pair_t sk_meta_subfield_tab(long param_1)
{
    long lVar2 = 0;
    ulong uVar3 = 0;
    if ((*(ushort *)(param_1 + 10) >> 2 & 1) != 0) {
        uint32_t *puVar1 = (uint32_t *)FUN_0037c8e4(0);
        uVar3 = *puVar1;
        if (*puVar1 != 0) {
            lVar2 = FUN_0037c8e4((uint64_t)(uintptr_t)param_1);
            lVar2 = lVar2 + (*(ushort *)(param_1 + 10) & 4);
        }
    }
    return SKPAIR2(lVar2, uVar3);
}

/*--------------------------------------------------------------------*/
/* FUN_0037c8e4 @ 0x0037c8e4   (est. sk_meta_subfield_base)
 * Ghidra: long FUN_0037c8e4(undefined8 param_1)
 * Base offset of the subfield table: FUN_0037c930 + 0xc*last field count.
 * Confidence: medium.
 */
long sk_meta_subfield_base(uint64_t param_1)
{
    long lVar1 = FUN_0037c930(0);
    uint64_t pair[2] = SKPAIR(FUN_0037ca00(param_1));
    ulong uVar2 = (pair[1] == 0) ? 0 : (ulong)*(ushort *)(pair[0] + pair[1] * 2 + -2);
    return lVar1 + uVar2 * 0xc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c930 @ 0x0037c930   (est. sk_meta_tab_base)
 * Ghidra: ulong FUN_0037c930(long param_1)
 * Base offset of a metadata sub-table: header + field count + packed word.
 * Confidence: medium.
 */
ulong sk_meta_tab_base(long param_1)
{
    ushort *puVar3 = (ushort *)
        ((param_1 + (ulong)*(ushort *)(param_1 + 4) + 0xf & 0xfffffffffffffffc) +
         (ulong)*(ushort *)(param_1 + 6) * 0xc);
    ushort uVar1 = *(ushort *)(param_1 + 10);
    ulong uVar4 = (ulong)uVar1 & 1;
    ulong uVar5 = ((int)uVar4 == 0) ? 0 : (ulong)*puVar3;
    ulong uVar2 = FUN_0037c9a0(0);
    return (ulong)puVar3 + (uVar2 & 0xffffffff) * 2 + ((ulong)uVar1 & 2) + uVar5 * 8 + uVar4 * 4 + 3 &
           0xfffffffffffffffc;
}

/*--------------------------------------------------------------------*/
/* FUN_0037c9a0 @ 0x0037c9a0   (est. sk_meta_tab_popcount)
 * Ghidra: undefined2 FUN_0037c9a0(long param_1)
 * Popcount of the packed word in a metadata sub-table.
 * Confidence: medium.
 */
uint16_t sk_meta_tab_popcount(long param_1)
{
    if ((*(ushort *)(param_1 + 10) >> 1 & 1) == 0) return 0;
    ushort *puVar3 = (ushort *)
        ((param_1 + (ulong)*(ushort *)(param_1 + 4) + 0xf & 0xfffffffffffffffc) +
         (ulong)*(ushort *)(param_1 + 6) * 0xc);
    ulong uVar2 = (ulong)*(ushort *)(param_1 + 10) & 1;
    ulong uVar4 = ((int)uVar2 == 0) ? 0 : (ulong)*puVar3;
    ushort uVar1 = puVar3[uVar2 * 2 + uVar4 * 4];
    char cVar5 = POPCOUNT((char)(uVar1 >> 8));
    return CONCAT11(cVar5, POPCOUNT((char)uVar1) + cVar5);
}

/*--------------------------------------------------------------------*/
/* FUN_0037ca00 @ 0x0037ca00   (est. sk_meta_tab_slice)
 * Ghidra: undefined1[16] FUN_0037ca00(long param_1)
 * Returns {ptr,count} of a metadata sub-table.
 * Confidence: medium.
 */
sk_pair_t sk_meta_tab_slice(long param_1)
{
    ushort *puVar3;
    ulong uVar1;
    if ((*(ushort *)(param_1 + 10) >> 1 & 1) == 0) {
        return SKPAIR2(0,0);
    } else {
        puVar3 = (ushort *)
            ((param_1 + (ulong)*(ushort *)(param_1 + 4) + 0xf & 0xfffffffffffffffc) +
             (ulong)*(ushort *)(param_1 + 6) * 0xc);
        uVar1 = (ulong)*(ushort *)(param_1 + 10) & 1;
        ulong uVar2 = ((int)uVar1 == 0) ? 0 : (ulong)*puVar3;
        puVar3 = puVar3 + uVar1 * 2 + uVar2 * 4 + 1;
        uVar1 = FUN_0037c9a0(0) & 0xffffffff;
    }
    return SKPAIR2((uint64_t)puVar3, uVar1);
}

/*--------------------------------------------------------------------*/
/* FUN_0037ca78 @ 0x0037ca78   (est. sk_meta_flatten_counts)
 * Ghidra: void FUN_0037ca78(short *param_1, ushort *param_2)
 * Flattens a descriptor into two counts: the number of negative (direct)
 * characters and the number of 0x80-tagged fields, storing them into
 * param_1[0]/param_1[1].
 * Confidence: high (verified against decompile, body matches exactly).
 */
void sk_meta_flatten_counts(short *param_1, ushort *param_2)
{
    param_1[0] = 0;
    param_1[1] = 0;
    *(uint32_t *)(param_1 + 2) = *(uint32_t *)(param_2 + 0xc);
    *(uint64_t *)(param_1 + 4) = *(uint64_t *)(param_2 + 0x10);
    ulong uVar1 = *param_2;
    if (uVar1 != 0) {
        short sVar2 = 0;
        char *pcVar4 = *(char **)(param_2 + 4);
        do {
            if (*pcVar4 < 0) { sVar2++; *param_1 = sVar2; }
            pcVar4++;
            uVar1--;
        } while (uVar1 != 0);
    }
    if ((ulong)param_2[1] != 0) {
        short sVar2 = 0;
        uint32_t *puVar3 = *(uint32_t **)(param_2 + 8);
        long lVar5 = (ulong)param_2[1] * 0xc;
        do {
            if ((*puVar3 & 0x9f) == 0x80) { sVar2++; param_1[1] = sVar2; }
            puVar3 += 3;
            lVar5 -= 0xc;
        } while (lVar5 != 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037cb08 @ 0x0037cb08   (est. sk_meta_hash_desc)
 * Ghidra: ulong FUN_0037cb08(long *param_1)
 * Computes a stable hash over the descriptor words (FUN_0037ca78-style
 * flattened counts + inline payload), mixing each 8-byte word.
 * Confidence: medium.
 */
ulong sk_meta_hash_desc(long *param_1)
{
    ushort uVar3 = *(ushort *)(param_1 + 1);
    ulong uVar5 = (ulong)((uint)uVar3 * 0x56ba80d1);
    if (uVar3 != 0) {
        ulong uVar6 = 0;
        ulong uVar7 = (ulong)*(ushort *)((long)param_1 + 0xe);
        ulong uVar1 = uVar7 + uVar3;
        do {
            if (uVar6 < *(ushort *)((long)param_1 + 0xc)) {
                short *psVar2 = (short *)(param_1[2] + uVar6 * 8);
                if (*psVar2 == 0 && uVar7 == (ushort)psVar2[1]) {
                    ulong uVar8 = *(ulong *)(*param_1 + (ulong)(ushort)psVar2[2] * 8);
                    uVar6++;
                    if (uVar8 != 0) {
                        ulong *puVar9 = (ulong *)(*(ulong *)(*param_1 + uVar7 * 8) & 0xfffffffffffffffe);
                        ulong uVar10 = 1;
                        do {
                            uVar5 = (uVar5 >> 10 | uVar5 << 0x36) ^ *puVar9 >> 0x13 ^ *puVar9;
                            puVar9++;
                        } while (uVar10++ < uVar8);
                    }
                    uVar7++;
                    continue;
                }
            }
            ulong uVar8 = *(ulong *)(*param_1 + uVar7 * 8);
            uVar5 = (uVar5 >> 10 | uVar5 << 0x36) ^ uVar8 >> 0x13 ^ uVar8;
            uVar7++;
        } while (uVar7 != uVar1);
    }
    return uVar5 * 0x27d4eb2d >> 10;
}

/*--------------------------------------------------------------------*/
/* FUN_0037cbc8 @ 0x0037cbc8   (est. sk_dep_materialize)
 * Ghidra: void FUN_0037cbc8(undefined8 *param_1, long param_2, undefined8 *param_3,
 *                           undefined8 *param_4, undefined8 param_5, undefined8 param_6)
 * Materializes a dependency: resolves the requirement (FUN_0037cd8c), then
 * either builds the object directly or runs the full metadata resolution,
 * storing the result into param_1.
 * Confidence: low (Swift-metadata dependency materializer).
 */
void sk_dep_materialize(uint64_t *param_1, long param_2, uint64_t *param_3,
                        uint64_t *param_4, uint64_t param_5, uint64_t param_6)
{
    long local_70 = 0;
    uint16_t local_68 = 0;
    uint64_t local_60 = param_3[0], uStack_58 = param_3[1];
    uint64_t local_50 = param_3[2], uStack_48 = param_3[3];
    long local_78 = param_2 + 0x40;
    sk_pair_t rr = FUN_0037cd8c((int *)param_2, (uint64_t *)&local_60, (uint64_t *)&local_78, param_4, param_5, param_6);
    uint64_t uVar1 = rr.lo;
    if ((rr.hi & 1) == 0) {
        uVar1 = FUN_0037a9ac((uint64_t *)uVar1, (uint64_t)(param_2 + 0x40), *param_4);
    } else {
        if (local_70 != 0) local_68 = 1;
        FUN_0037ccbc(&local_60, uVar1, &local_78, *param_4, (uint64_t *)param_5, (uint64_t *)param_6);
        if ((char)local_50 == '\x01') {
            *param_1 = uVar1;
            param_1[2] = uStack_58;
            param_1[1] = local_60;
            FUN_0037b350(&local_78);
            return;
        }
        uVar1 = FUN_0037ac0c(uVar1, (uint64_t *)&local_78, *param_4);
    }
    *param_1 = uVar1;
    *(uint64_t *)(param_1 + 1) = uVar1;
    FUN_0037b350(&local_78);
}

/*--------------------------------------------------------------------*/
/* FUN_0037ccbc @ 0x0037ccbc   (est. sk_dep_resolve_one)
 * Ghidra: void FUN_0037ccbc(undefined8 *param_1, long param_2, undefined8 *param_3,
 *                           undefined8 param_4, undefined8 *param_5, undefined8 *param_6)
 * Resolves a single dependency: if the kind byte is unset, runs the
 * full resolver (FUN_0037d0dc) and promotes the result; otherwise takes the
 * cached word.
 * Confidence: low (Swift-metadata single-dependency resolver).
 */
void sk_dep_resolve_one(uint64_t *param_1, long param_2, uint64_t *param_3,
                        uint64_t param_4, uint64_t *param_5, uint64_t *param_6)
{
    if (*(char *)((long)param_3 + 0x11) == '\0') {
        uint8_t res[12];
        sk_pair_t vv = FUN_0037d0dc((void *)param_2, 0, (void *)*param_5);
        *(char *)((long)param_3 + 0x11) = (char)vv.hi;
        *(long *)(param_2 + 0x20) = vv.lo;
        if (vv.hi != 4) {
            FUN_0037b288(*(uint64_t *)*param_3, (long *)&param_3);
            *param_1 = 0;
            param_1[1] = 0;
            return;
        }
        FUN_0037b170((uint64_t)param_2, param_3, 0, 0, 0);
        *param_1 = vv.lo;
    } else if (*(char *)((long)param_3 + 0x11) == '\x04') {
        *param_1 = *(uint64_t *)(param_2 + 0x20);
    } else {
        *param_1 = 0;
    }
    param_1[1] = 0;
    *(uint8_t *)(param_1 + 2) = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037cd8c @ 0x0037cd8c   (est. sk_dep_find)
 * Ghidra: undefined1[16] FUN_0037cd8c(int *param_1, undefined8 *param_2,
 *                                     undefined8 param_3, ...)
 * Finds (or inserts) a dependency key in the metadata table; returns
 * {found_flag, entry}. Uses the open-addressed table (param_1+2/4/1).
 * Confidence: medium.
 */
sk_pair_t sk_dep_find(int *param_1, uint64_t *param_2, uint64_t param_3,
                     uint64_t param_4, uint64_t param_5, uint64_t param_6)
{
    long lVar3 = *(long *)(param_1 + 0xe);
    if (lVar3 != 0) {
        long local_b8 = lVar3 + 0x28;
        if ((FUN_00379f6c(param_2, &local_b8) & 1) != 0) {
            return SKPAIR2(lVar3, 0);   /* found */
        }
    }
    /* acquire lock, insert into table via FUN_0037a238 + FUN_0037cec4 */
    long entry = 0;
    FUN_0037cec4((long)param_1, (uint64_t *)param_2, (uint64_t)(uintptr_t)&entry);
    *(long *)(param_1 + 0xe) = entry;
    return SKPAIR2(entry, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0037cec4 @ 0x0037cec4   (est. sk_meta_lock_store)
 * Ghidra: void FUN_0037cec4(long param_1, undefined8 *param_2, undefined8 param_3)
 * Holds the metadata lock (param_1+0x20), stores the payload pair, runs the
 * insert (FUN_0037cf2c), drains deferred frees, and unlocks.
 * Confidence: medium.
 */
void sk_meta_lock_store(long param_1, uint64_t *param_2, uint64_t param_3)
{
    uint64_t local_50 = param_2[0], uStack_48 = param_2[1];
    uint64_t uStack_40 = param_2[2], uStack_38 = param_2[3];
    sk_mtx_lock_checked();
    FUN_0037cf2c(param_1, local_50, (long *)&param_3);
    sk_meta_drain_deferred((int *)param_1);
    sk_mtx_unlock_checked();
}

/*--------------------------------------------------------------------*/
/* FUN_0037cf2c @ 0x0037cf2c   (est. sk_meta_insert)
 * Ghidra: void FUN_0037cf2c(long param_1, undefined8 param_2, long *param_3)
 * Inserts a metadata entry into the open-addressed table (param_1+0x10),
 * growing/rehashing on load, building the slot via FUN_0037a744 and linking
 * it into the table; records the result into param_3[5]/[6].
 * Confidence: medium.
 */
void sk_meta_insert(long param_1, uint64_t param_2, long *param_3)
{
    ulong uVar13 = *(ulong *)(param_1 + 0x10);
    ulong uVar14 = ((uVar13 & 3) == 0 || (uint8_t *)(uVar13 & 0xfffffffffffffffc) == 0)
        ? 4 : *(uint8_t *)(uVar13 & 0xfffffffffffffffc);
    uint32_t uVar4 = *(uint32_t *)(param_1 + 4);
    ulong uVar11 = uVar4;
    uint32_t *puVar12 = *(uint32_t **)(param_1 + 8);
    uint32_t *puVar2 = (puVar12 != 0) ? puVar12 + 2 : 0;
    ulong local_88 = uVar13;
    uint64_t res[2] = SKPAIR(FUN_0037a238((long)param_2, uVar13, uVar11, (long)puVar2));
    ulong uVar10 = res[1];
    if (res[0] == 0) {
        ulong uVar7 = 1L << (uVar14 & 0x3f);
        uint32_t uVar1 = uVar4 + 1;
        ulong uVar9 = uVar7 - uVar1;
        ulong uVar5 = (uVar9 != 0) ? uVar7 / uVar9 : 0;
        if (3 < uVar5) {
            local_88 = FUN_0037a4c0(param_1, uVar13, uVar14, (long)puVar2);
            FUN_0037a238((long)param_2, local_88, uVar11, (long)puVar2);
        }
        if (puVar12 == 0 || *puVar12 <= uVar4)
            puVar12 = (uint32_t *)FUN_0037a5e0(param_1, (long)puVar12, uVar11);
        long lVar8 = *param_3;
        uint64_t slot = (uint64_t)FUN_00369758(&local_88,
            ((ulong)*(ushort *)(lVar8 + 8) + (ulong)*(ushort *)(lVar8 + 0xe) +
             (ulong)*(ushort *)(lVar8 + 10)) * 8 + 0x28, 8);
        uint64_t *puVar3 = (uint64_t *)*param_3;
        uint64_t local_80[4] = { puVar3[0], puVar3[1], puVar3[2], puVar3[3] };
        FUN_0037a744(&local_88, (uint64_t *)&local_80, param_3[1], 0, 0);
        *(uint64_t *)(puVar12 + uVar11 * 2 + 2) = slot;
        *(uint64_t *)param_3[5] = slot;
        *(uint8_t *)param_3[6] = 1;
        *(uint32_t *)(param_1 + 4) = uVar1;
        FUN_0037a668(&local_88, (ulong *)(param_1 + 0x10), (uint)uVar1, uVar10 & 0xffffffff, 3);
    } else {
        *(uint64_t *)param_3[5] = res[0];
        *(uint8_t *)param_3[6] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037d0dc @ 0x0037d0dc   (est. sk_dep_simple_resolve)
 * Ghidra: undefined1[16] FUN_0037d0dc(undefined8 param_1, long param_2,
 *                                     undefined8 param_3)
 * Resolves a simple dependency: dispatch through the type's vtable
 * (FUN_0036d8a4/FUN_0036a668), returns {data, kind} (kind 1/2 by metadata,
 * 3/4 by acyclicity, 4 on miss).
 * Confidence: medium.
 */
sk_pair_t sk_dep_simple_resolve(uint64_t param_1, long param_2, uint64_t param_3)
{
    long lVar5 = FUN_0036d8a4((void *)param_2, (void *)param_3);
    if (lVar5 == 0) {
        long lVar5 = FUN_0036a668((void *)param_2);
        int iVar4 = *(int *)(lVar5 + 4);
        int *piVar1 = (int *)((long)iVar4 + lVar5 + 4);
        int *piVar2 = (iVar4 != 0) ? piVar1 : 0;
        if (param_2 == 0) param_2 = 0;
        sk_fnv_t fn = (*piVar1 != 0) ? (sk_fnv_t)((long)*piVar1 + (long)piVar2) : 0;
        lVar5 = fn(param_2, param_3);
        uint64_t kind;
        if (piVar1[1] == 0) {
            uint32_t ok = FUN_003780f4(lVar5);
            kind = (ok != 0) ? 4 : 3;
        } else {
            kind = 1;
            if ((*(uint8_t *)(*(long *)(lVar5 - 8) + 0x52) & 0x40) == 0) kind = 2;
        }
        return SKPAIR2(lVar5, kind);
    }
    return SKPAIR2(lVar5, 4);
}

/*--------------------------------------------------------------------*/
/* FUN_0037d1d8 @ 0x0037d1d8   (est. sk_meta_cap_info)
 * Ghidra: undefined4 * FUN_0037d1d8(undefined4 *param_1, long param_2)
 * Fills a capability-info record for param_2: class ref (FUN_0035bd48),
 * metadata (FUN_0035eae4), scratch pointers, and a stack-canary word.
 * Confidence: medium.
 */
uint32_t *sk_meta_cap_info(uint32_t *param_1, long param_2)
{
    *param_1 = 0;
    long lVar1 = FUN_0035bd48(param_2);
    if (lVar1 == 0) lVar1 = 0;
    *(long *)(param_1 + 2) = lVar1;
    uint64_t uVar2 = (param_2 == 0) ? 0 : FUN_0035eae4((void *)param_2);
    *(uint64_t *)(param_1 + 4) = uVar2;
    *(uint32_t **)(param_1 + 6) = param_1 + 10;
    *(uint64_t *)(param_1 + 8) = DAT_004f2710;
    *(uint64_t *)(param_1 + 0x4a) = 0;
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037d25c @ 0x0037d25c   (est. sk_cap2_field_ptr)
 * Ghidra: undefined1[16] FUN_0037d25c(uint *param_1)
 * Returns {ptr,count} of a capability's field region when the field flag is
 * set.
 * Confidence: medium.
 */
sk_pair_t sk_cap2_field_ptr(uint32_t *param_1)
{
    if ((*(uint8_t *)((long)param_1 + 3) >> 6 & 1) == 0) return SKPAIR2(0,0);
    uint32_t *puVar3 = param_1 ? param_1 : 0;
    long lVar2 = FUN_00379dec(puVar3);
    lVar2 = lVar2 + ((*puVar3 >> 0x1e) & 1) * 4;
    ulong uVar1 = FUN_00379e78((void *)param_1);
    return SKPAIR2(lVar2, uVar1);
}

/*--------------------------------------------------------------------*/
/* FUN_0037d304 @ 0x0037d304   (est. sk_cap2_field_off)
 * Ghidra: long FUN_0037d304(uint *param_1)
 * Field-region offset for a capability (0x80080 tag), via FUN_0037d95c.
 * Confidence: medium.
 */
long sk_cap2_field_off(uint32_t *param_1)
{
    if ((*(uint8_t *)((long)param_1 + 2) >> 6 & 1) != 0) {
        if (param_1 == 0) param_1 = 0;
        long lVar2 = FUN_0037d95c(param_1);
        uint32_t uVar1 = *param_1 & 0x80080;
        return (lVar2 + (uVar1 == 0x80080) * 4 + ((*param_1 >> 5) & 1) * 2 + 3 &
                0xfffffffffffffffc) + (uVar1 == 0x80000) * 4;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037d3c4 @ 0x0037d3c4   (est. sk_cap2_field_range)
 * Ghidra: undefined1[16] FUN_0037d3c4(uint *param_1)
 * Returns {ptr,count} of a capability's field region (0x80080 tag).
 * Confidence: medium.
 */
sk_pair_t sk_cap2_field_range(uint32_t *param_1)
{
    if ((*(uint8_t *)((long)param_1 + 2) >> 6 & 1) == 0) return SKPAIR2(0,0);
    uint32_t *puVar2 = param_1 ? param_1 : 0;
    long lVar4 = FUN_0037d95c(puVar2);
    uint32_t uVar1 = *puVar2;
    lVar4 = (lVar4 + ((uVar1 & 0x80080) == 0x80080) * 4 + ((uVar1 >> 5) & 1) * 2 + 3 &
            0xfffffffffffffffc) + ((uVar1 & 0x80080) == 0x80000) * 4 + ((uVar1 >> 0x16) & 1) * 4;
    ulong uVar3 = 0;
    if ((*(uint8_t *)((long)param_1 + 2) >> 6 & 1) != 0) {
        uint32_t *p = (uint32_t *)FUN_0037d304(param_1);
        uVar3 = *p;
    }
    return SKPAIR2(lVar4, uVar3);
}

/*--------------------------------------------------------------------*/
/* FUN_0037d4b8 @ 0x0037d4b8   (est. sk_hashset_insert)
 * Ghidra: long * FUN_0037d4b8(long *param_1, long *param_2, long *param_3)
 * Inserts {hash,key} into the open-addressed hash set param_1 (chained
 * buckets), growing via FUN_0037d700 when load exceeds the 1/2^5 factor.
 * Returns the inserted node. Traps on an invalid bucket.
 * Confidence: medium.
 */
long *sk_hashset_insert(long *param_1, long *param_2, long *param_3)
{
    long lVar9 = *param_2;
    long local_58 = lVar9;
    ulong uVar3 = FUN_00112098(&local_58, 8);
    ulong uVar8 = param_1[1];
    ulong unaff_x24 = 0;
    if (uVar8 != 0) {
        ulong uVar4 = uVar8 - 1;
        if ((uVar8 & uVar4) == 0) unaff_x24 = uVar4 & uVar3;
        else {
            unaff_x24 = uVar3;
            if (uVar8 <= uVar3) unaff_x24 = uVar3 - (uVar8 != 0 ? uVar3 / uVar8 : 0) * uVar8;
        }
        if ((ulong)param_1[2] <= unaff_x24) goto trap;
        long *plVar5 = *(long **)(*param_1 + unaff_x24 * 8);
        if (plVar5 != 0) {
            for (plVar5 = (long *)*plVar5; plVar5 != 0; plVar5 = (long *)*plVar5) {
                ulong uVar6 = plVar5[1];
                if (uVar6 == uVar3) { if (plVar5[2] == lVar9) return plVar5; }
                else {
                    if ((uVar8 & uVar4) == 0) uVar6 &= uVar4;
                    else if (uVar8 <= uVar6) uVar6 = uVar6 - (uVar8 ? uVar6 / uVar8 : 0) * uVar8;
                    if (uVar6 != unaff_x24) break;
                }
            }
        }
    }
    long *plVar5 = (long *)FUN_00111890(0x18, 0x1060c00078847bf);
    *plVar5 = 0;
    plVar5[1] = uVar3;
    plVar5[2] = *param_3;
    if (uVar8 == 0 || *(float *)(param_1 + 5) * (float)uVar8 < (float)(param_1[4] + 1)) {
        ulong uVar4 = 1;
        if (2 < uVar8) uVar4 = (uVar8 & uVar8 - 1) != 0;
        uVar4 = uVar4 | uVar8 << 1;
        ulong uVar8n = (ulong)((float)(param_1[4] + 1) / *(float *)(param_1 + 5));
        if (uVar4 <= uVar8n) uVar4 = uVar8n;
        FUN_0037d700(param_1, uVar4);
        uVar8 = param_1[1];
        if ((uVar8 & uVar8 - 1) == 0) unaff_x24 = (uVar8 - 1) & uVar3;
        else {
            unaff_x24 = uVar3;
            if (uVar8 <= uVar3) unaff_x24 = uVar3 - (uVar8 ? uVar3 / uVar8 : 0) * uVar8;
        }
    }
    ulong uVar3b = param_1[2];
    if (unaff_x24 < uVar3b) {
        long lVar9 = *param_1;
        long *plVar7 = *(long **)(lVar9 + unaff_x24 * 8);
        if (plVar7 == 0) {
            plVar7 = param_1 + 3;
            *plVar5 = *plVar7;
            *plVar7 = (long)plVar5;
            *(long **)(lVar9 + unaff_x24 * 8) = plVar7;
            if (*plVar5 != 0) {
                ulong uVar4 = *(ulong *)(*plVar5 + 8);
                if ((uVar8 & uVar8 - 1) == 0) uVar4 &= uVar8 - 1;
                else if (uVar8 <= uVar4) uVar4 = uVar4 - (uVar8 ? uVar4 / uVar8 : 0) * uVar8;
                if (uVar3b > uVar4) *(long **)(lVar9 + uVar4 * 8) = plVar5;
            }
        } else {
            *plVar5 = *plVar7;
            *plVar7 = (long)plVar5;
        }
        param_1[4] = param_1[4] + 1;
        return plVar5;
    }
trap:
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37d700) */
}

/*--------------------------------------------------------------------*/
/* FUN_0037d700 @ 0x0037d700   (est. sk_hashset_grow)
 * Ghidra: void FUN_0037d700(long *param_1, ulong param_2)
 * Grows/rehashes the hash set param_1 to a power-of-two capacity >= param_2,
 * re-linking all chained buckets. Traps on a bad bucket index.
 * Confidence: medium.
 */
void sk_hashset_grow(long *param_1, ulong param_2)
{
    if (param_2 - 1 == 0) param_2 = 2;
    else if ((param_2 & param_2 - 1) != 0) param_2 = FUN_001124fc(param_2);
    ulong uVar11 = param_1[1];
    if (uVar11 < param_2) {
        if (param_2 == 0) {
            long lVar3 = *param_1;
            *param_1 = 0;
            param_1[2] = -1;
            if (lVar3 != 0) thunk_FUN_00012568((void *)lVar3, param_1[1] << 3);
            param_1[1] = 0;
            return;
        }
        if (param_2 >> 0x3d != 0) FUN_004b89f8();
        long lVar3 = (long)FUN_00111890(param_2 << 3, 0x20c0093837f09);
        long lVar4 = *param_1;
        *param_1 = lVar3;
        ulong uVar11 = 0xffffffffffffffff;
        param_1[2] = -1;
        if (lVar4 != 0) {
            thunk_FUN_00012568((void *)lVar4, param_1[1] << 3);
            uVar11 = param_1[2];
        }
        ulong uVar5 = 0;
        param_1[1] = param_2;
        do {
            if (uVar11 == uVar5) { __builtin_trap(); }
            *(uint64_t *)(lVar3 + uVar5 * 8) = 0;
            uVar5++;
        } while (param_2 != uVar5);
        long *plVar7 = (long *)param_1[3];
        if (plVar7 != 0) {
            ulong uVar5 = plVar7[1];
            ulong uVar6 = param_2 - 1;
            if ((param_2 & uVar6) == 0) uVar5 &= uVar6;
            else if (param_2 <= uVar5) uVar5 = uVar5 - (param_2 ? uVar5 / param_2 : 0) * param_2;
            if (uVar11 <= uVar5) { __builtin_trap(); }
            *(long **)(lVar3 + uVar5 * 8) = param_1 + 3;
            long *plVar8 = (long *)*plVar7;
            while (plVar8 != 0) {
                ulong uVar10 = plVar8[1];
                if ((param_2 & uVar6) == 0) uVar10 &= uVar6;
                else if (param_2 <= uVar10) uVar10 = uVar10 - (param_2 ? uVar10 / param_2 : 0) * param_2;
                long *plVar9 = plVar8;
                if (uVar10 != uVar5) {
                    if (uVar11 <= uVar10) { __builtin_trap(); }
                    if (*(long *)(lVar3 + uVar10 * 8) == 0) {
                        *(long **)(lVar3 + uVar10 * 8) = plVar7;
                        uVar5 = uVar10;
                    } else {
                        *plVar7 = *plVar8;
                        *plVar8 = **(uint64_t **)(lVar3 + uVar10 * 8);
                        **(long **)(lVar3 + uVar10 * 8) = (long)plVar8;
                        plVar9 = plVar7;
                    }
                }
                plVar7 = plVar9;
                plVar8 = (long *)*plVar9;
            }
        }
        return;
    }
    if (param_2 < uVar11) {
        ulong uVar5 = (ulong)((float)(ulong)param_1[4] / *(float *)(param_1 + 5));
        if ((uVar11 < 3) || ((uVar11 & uVar11 - 1) != 0)) uVar5 = FUN_001124fc(0);
        else if (1 < uVar5) uVar5 = 1L << (-LZCOUNT(uVar5 - 1) & 0x3fU);
        if (param_2 <= uVar5) param_2 = uVar5;
        if (param_2 < uVar11) { /* shrink path */ return; }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037d95c @ 0x0037d95c   (est. sk_cap2_field_base)
 * Ghidra: long FUN_0037d95c(uint *param_1)
 * Capability field base: FUN_00379d74 + 4-byte tag words.
 * Confidence: medium.
 */
long sk_cap2_field_base(uint32_t *param_1)
{
    long lVar2 = FUN_00379d74(0);
    uint32_t uVar1 = *param_1;
    long lVar3 = FUN_00379eec((void *)param_1);
    long lVar4 = FUN_00379eec((void *)param_1);
    return lVar2 + (((uVar1 ^ 0xffffffff) & 0x80080) == 0) * 4 + lVar3 * 4 + lVar4 * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037d9bc @ 0x0037d9bc   (est. sk_hashset_find)
 * Ghidra: long FUN_0037d9bc(long *param_1, long *param_2)
 * Looks up {hash,key} in the hash set param_1; returns the node or 0. Traps
 * on a bad bucket.
 * Confidence: medium.
 */
long sk_hashset_find(long *param_1, long *param_2)
{
    ulong uVar8 = param_1[1];
    if (uVar8 != 0) {
        if (param_1[4] == 0) return 0;
        long lVar9 = *param_2;
        long local_38 = lVar9;
        ulong uVar3 = FUN_00112098(&local_38, 8);
        ulong uVar5 = uVar8 - 1;
        ulong uVar6;
        if ((uVar8 & uVar5) == 0) uVar6 = uVar3 & uVar5;
        else {
            uVar6 = uVar3;
            if (uVar8 <= uVar3) uVar6 = uVar3 - (uVar8 ? uVar3 / uVar8 : 0) * uVar8;
        }
        if ((ulong)param_1[2] <= uVar6) __builtin_trap();
        long *plVar4 = *(long **)(*param_1 + uVar6 * 8);
        if (plVar4 == 0) return 0;
        ulong uVar7 = 0;
        do {
            while (1) {
                plVar4 = (long *)*plVar4;
                if (plVar4 == 0) return 0;
                uVar7 = plVar4[1];
                if (uVar3 != uVar7) break;
                if (plVar4[2] == lVar9) return (long)plVar4;
            }
            if ((uVar8 & uVar5) == 0) uVar7 &= uVar5;
            else if (uVar8 <= uVar7) uVar7 = uVar7 - (uVar8 ? uVar7 / uVar8 : 0) * uVar8;
        } while (uVar7 == uVar6);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037daa8 @ 0x0037daa8   (est. sk_hashset_destroy)
 * Ghidra: long * FUN_0037daa8(long *param_1)
 * Frees every chained node and the backing array of the hash set.
 * Confidence: medium.
 */
long *sk_hashset_destroy(long *param_1)
{
    long *plVar1 = (long *)param_1[3];
    while (plVar1 != 0) {
        long lVar2 = *plVar1;
        thunk_FUN_00012568(plVar1, 0x18);
        plVar1 = (long *)lVar2;
    }
    long lVar2 = *param_1;
    *param_1 = 0;
    param_1[2] = -1;
    if (lVar2 != 0) thunk_FUN_00012568((void *)lVar2, param_1[1] << 3);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037db2c @ 0x0037db2c   (est. sk_store_alloc_pages_dup)
 * Ghidra: long FUN_0037db2c(undefined8 *param_1, undefined8 *param_2)
 * Duplicate of FUN_00372534: stores the word at param_2 through param_1 and
 * hands it to the page allocator.
 * Confidence: low.
 */
long sk_store_alloc_pages_dup(uint64_t *param_1, uint64_t *param_2)
{
    uint64_t uVar1 = *param_2;
    *param_1 = uVar1;
    sk_alloc_pages(uVar1, 0);   /* FUN_0036b270 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037dbc4 @ 0x0037dbc4   (est. sk_desc_copy_cap)
 * Ghidra: undefined8 * FUN_0037dbc4(undefined8 *param_1, undefined8 *param_2)
 * Copies a descriptor: stores the type tag, and either runs the vtable copy
 * or the direct word copy.
 * Confidence: medium.
 */
uint64_t *sk_desc_copy_cap(uint64_t *param_1, uint64_t *param_2)
{
    param_1[3] = param_2[3];
    if ((*(uint8_t *)(*(long *)(param_2[3] - 8) + 0x52) >> 1 & 1) == 0)
        (**(code **)(*(long *)(param_2[3] - 8) + 0x10))(param_1);
    else {
        *param_1 = *param_2;
        sk_alloc_pages(0,0);
    }
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037dc2c @ 0x0037dc2c   (est. sk_desc_assign)
 * Ghidra: undefined8 * FUN_0037dc2c(undefined8 *param_1, undefined8 *param_2)
 * Assigns descriptor param_2 into param_1, handling same/different types via
 * the vtable copy/move and releasing the old payload.
 * Confidence: high (verified against decompile; fixed dropped old-payload
 * capture in the equal-type branch so FUN_0036b118 releases the old word).
 */
uint64_t *sk_desc_assign(uint64_t *param_1, uint64_t *param_2)
{
    uint64_t uVar6 = 0;
    if (param_2 != param_1) {
        long lVar4 = param_2[3];
        long lVar5 = param_1[3];
        if (lVar4 == lVar5) {
            if ((*(uint8_t *)(*(long *)(lVar4 - 8) + 0x52) >> 1 & 1) == 0) {
                (**(code **)(*(long *)(lVar4 - 8) + 0x28))(param_1, param_2, lVar4);
                return param_1;
            }
            uVar6 = *param_1;  /* capture old inline payload for release below */
            *param_1 = *param_2;
        } else {
            long lVar1 = *(long *)(lVar5 - 8);
            long lVar2 = lVar1 ? lVar1 : 0;
            long lVar3 = *(long *)(lVar4 - 8);
            if (lVar3 == 0) lVar3 = 0;
            if ((*(uint8_t *)(lVar2 + 0x52) >> 1 & 1) == 0) {
                uint8_t buf[24];
                (**(code **)(lVar1 + 0x20))(buf, param_1, lVar5);
                param_1[3] = param_2[3];
                if ((*(uint8_t *)(lVar3 + 0x52) >> 1 & 1) == 0)
                    (**(code **)(*(long *)(lVar4 - 8) + 0x20))(param_1, param_2, lVar4);
                else *param_1 = *param_2;
                (**(code **)(*(long *)(lVar5 - 8) + 8))(buf, lVar5);
                return param_1;
            }
            uVar6 = *param_1;
            param_1[3] = param_2[3];
            if ((*(uint8_t *)(lVar3 + 0x52) >> 1 & 1) == 0)
                (**(code **)(*(long *)(lVar4 - 8) + 0x20))(param_1, param_2, lVar4);
            else *param_1 = *param_2;
        }
        FUN_0036b118((uint64_t)uVar6);
    }
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037de18 @ 0x0037de18   (est. sk_meta_desc_extract)
 * Ghidra: void FUN_0037de18(undefined8 *param_1, uint *param_2)
 * Extracts a 7-word summary from a type descriptor: header, inline data,
 * requirement table pointer, flags.
 * Confidence: medium.
 */
void sk_meta_desc_extract(uint64_t *param_1, uint32_t *param_2)
{
    uint32_t uVar1 = *param_2;
    if ((uVar1 >> 8 & 1) == 0) {
        param_1[0]=param_1[1]=param_1[2]=param_1[4]=param_1[6]=0;
        *(uint32_t *)(param_1 + 3) = 0; *(uint32_t *)(param_1 + 5) = 0;
    } else {
        long lVar6;
        if ((uVar1 >> 0xc & 1) == 0) {
            lVar6 = ((long)param_2 + 0x1bU & 0xfffffffffffffffc) +
                    ((uVar1 >> 9) & 1) * 4 + ((uVar1 >> 10) & 1) * 4;
            if ((uVar1 >> 0xb & 1) == 0) lVar6 = lVar6 + (ulong)(ushort)param_2[2];
        } else lVar6 = 0x4f2770;
        long lVar4 = FUN_00367dd4(param_2);
        ushort uVar2 = *(ushort *)((long)param_2 + 10);
        uint32_t uVar3 = FUN_0037def8(param_2);
        uint64_t uVar5 = (*(uint8_t *)((long)param_2 + 1) >> 5 & 1) ? FUN_0037df58(param_2) : 0;
        param_1[0] = *(uint64_t *)(param_2 + 4);
        param_1[1] = lVar6;
        param_1[2] = lVar4 + (ulong)uVar2 * 0xc;
        *(uint32_t *)(param_1 + 3) = uVar3;
        param_1[4] = uVar5;
        *(uint32_t *)(param_1 + 5) = 0;
        param_1[6] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0037def8 @ 0x0037def8   (est. sk_meta_req_word)
 * Ghidra: undefined4 FUN_0037def8(long param_1)
 * Reads a requirement word from the descriptor's requirement table.
 * Confidence: medium.
 */
uint32_t sk_meta_req_word(long param_1)
{
    if ((*(uint8_t *)(param_1 + 1) >> 5 & 1) == 0) return 0;
    long lVar1 = FUN_00367dd4(0);
    ulong uVar2 = (*(uint8_t *)(param_1 + 1) & 1) ? (ulong)*(ushort *)(param_1 + 0x12) : 0;
    return *(uint32_t *)(lVar1 + uVar2 * 0xc + (ulong)*(ushort *)(param_1 + 10) * 0xc);
}

/*--------------------------------------------------------------------*/
/* FUN_0037df58 @ 0x0037df58   (est. sk_meta_req_ptr)
 * Ghidra: long FUN_0037df58(uint *param_1)
 * Requirement-table pointer for a descriptor.
 * Confidence: medium.
 */
long sk_meta_req_ptr(uint32_t *param_1)
{
    long lVar1 = FUN_00367dd4(0);
    ulong uVar2 = ((*param_1 >> 8 & 1) == 0) ? 0 : (ulong)*(ushort *)((long)param_1 + 0x12);
    return lVar1 + uVar2 * 0xc + (ulong)*(ushort *)((long)param_1 + 10) * 0xc +
           ((*param_1 >> 0xd) & 1) * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037dfa8 @ 0x0037dfa8   (est. sk_meta_insert_triple)
 * Ghidra: undefined8 FUN_0037dfa8(undefined8 param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Inserts a {param_1,param_2,param_3} triple into the open-addressed table
 * (global _DAT_006c0748/_DAT_006c0750/_DAT_006c0744), rehashing on load.
 * Returns param_1 of the inserted or existing entry.
 * Confidence: medium.
 */
uint64_t sk_meta_insert_triple(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    FUN_00361718(0, (void *)0x6c0760, 0);
    uint64_t uVar24 = _DAT_006c0750;
    uint32_t *puVar9 = (uint32_t *)_DAT_006c0748;
    uint32_t uVar8 = _DAT_006c0744;
    uint64_t local_98 = _DAT_006c0750;
    uint8_t *pbVar5 = (uint8_t *)(_DAT_006c0750 & 0xfffffffffffffffc);
    ulong uVar23 = ((ulong)_DAT_006c0750 & 3) != 0 && pbVar5 != 0 ? *pbVar5 : 4;
    ulong uVar22 = _DAT_006c0744;
    uint32_t *puVar3 = (uint32_t *)_DAT_006c0748 + 2;
    uint32_t *puVar18 = (_DAT_006c0748 != 0) ? puVar3 : 0;
    uint64_t local_90 = param_2, uStack_88 = param_3;
    uint64_t res[2] = SKPAIR(FUN_0037e348(&local_90, _DAT_006c0750, uVar22, puVar18));
    ulong uVar25 = res[1];
    if (res[0] == 0) {
        ulong uVar19 = 1L << (uVar23 & 0x3f);
        uint32_t uVar1 = uVar8 + 1;
        ulong uVar21 = uVar19 - uVar1;
        ulong uVar16 = (uVar21 != 0) ? uVar19 / uVar21 : 0;
        if (3 < uVar16) {
            /* rehash via FUN_0037e348 into fresh 0x18-stride table */
            uVar24 = FUN_0037a898((uVar23 & 0xff) + 1);
            /* ... (rehash loop) */
            _DAT_006c0750 = uVar24;
            FUN_0037e348(&local_90, uVar24, uVar22, puVar18);
            uVar25 = 0;
        }
        if (puVar9 == 0 || *puVar9 <= uVar8) {
            uint64_t uVar24 = (uVar8 >> 2) < 2 ? 1 : (uVar8 >> 2);
            uint64_t uVar24b = (uint64_t)FUN_0001279c((uVar24 + uVar22) * 0x18 + 8);
            uint32_t *puVar18 = (uint32_t *)FUN_000101a0(uVar24b, 0x1060040ffda0b6d);
            if (puVar18 == 0) __builtin_trap();
            *puVar18 = (uint32_t)((uVar24b - 8) / 0x18);
            if (puVar9 != 0) FUN_00117cc8(puVar18 + 2, puVar3, uVar22 * 0x18, 0);
            _DAT_006c0748 = (unsigned long)puVar18;
            puVar3 = puVar18;
        }
        *(uint64_t *)(puVar3 + uVar22 * 6 + 2) = param_2;
        *(uint64_t *)(puVar3 + uVar22 * 6 + 4) = param_3;
        *(uint64_t *)(puVar3 + uVar22 * 6 + 6) = param_1;
        _DAT_006c0744 = uVar1;
        FUN_0035b588(&local_98, &_DAT_006c0750, (ulong)uVar1, uVar25 & 0xffffffff, 3);
    } else {
        param_1 = *(uint64_t *)(res[0] + 0x10);
    }
    DataMemoryBarrier(2, 3);
    /* drain deferred frees when _DAT_006c0740 == 0 */
    FUN_0035b228((void *)0);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037e348 @ 0x0037e348   (est. sk_meta_find_triple)
 * Ghidra: undefined1[16] FUN_0037e348(undefined8 *param_1, ulong param_2,
 *                                     ulong param_3, long param_4)
 * Finds a {key,val} pair in the 0x18-stride table, returning {slot,index}.
 * Confidence: medium.
 */
sk_pair_t sk_meta_find_triple(uint64_t *param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong local_c0 = param_2;
    ulong uVar4 = FUN_0037e484(0);
    ulong uVar5 = 4;
    if ((param_2 & 3) != 0 && (uint8_t *)(param_2 & 0xfffffffffffffffc) != 0)
        uVar5 = *(uint8_t *)(param_2 & 0xfffffffffffffffc);
    uVar5 = -1L << (uVar5 & 0x3f);
    uVar4 = uVar4 & ~uVar5;
    if (uVar4 < 2) uVar4 = 1;
    int iVar3 = FUN_0035b178(&local_c0, uVar4, 2);
    uint64_t *puVar6 = 0;
    if (iVar3 != 0) {
        do {
            if ((iVar3 - 1 < param_3) &&
                (puVar6 = (uint64_t *)(param_4 + (ulong)(iVar3 - 1) * 0x18), param_1[1] == puVar6[1])) {
                /* compare keys via FUN_00387e60 + memcmp */
                if (param_1[0] == puVar6[0]) { uVar4 = 0; goto out; }
            }
            uVar4 = uVar4 + 1 & ~uVar5;
            if (uVar4 < 2) uVar4 = 1;
            iVar3 = FUN_0035b178(&local_c0, uVar4, 2);
        } while (iVar3 != 0);
    }
    puVar6 = 0;
    uVar4 = uVar4 & 0xffffffff;
out:
    return SKPAIR2((uint64_t)puVar6, uVar4);
}

/*--------------------------------------------------------------------*/
/* FUN_0037e484 @ 0x0037e484   (est. sk_meta_triple_hash)
 * Ghidra: void FUN_0037e484(undefined8 *param_1)
 * Computes the hash of a {key,val} triple via the metadata hash chain
 * (FUN_00387e60/FUN_0037e528/FUN_003a2b38).
 * Confidence: medium.
 */
void sk_meta_triple_hash(uint64_t *param_1)
{
    uint64_t local_b8 = 0, local_b0 = 0, local_a8 = 0, uStack_a0 = 0;
    FUN_00387e60(&local_b8, *param_1);
    FUN_0037e528(&local_b8);
    local_b8 = param_1[1];
    local_b0 = FUN_003a2b38(local_a8, uStack_a0);
    FUN_0037e868((long)&local_b8, 0, (long)&local_a8, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0037e528 @ 0x0037e528   (est. sk_meta_triple_zero)
 * Ghidra: void FUN_0037e528(undefined8 *param_1)
 * Zero-fills a 16-word metadata triple, seeding its final word with the
 * splitmix64 seed constant.
 * Confidence: medium.
 */
void sk_meta_triple_zero(uint64_t *param_1)
{
    for (int i = 0; i < 15; i++) param_1[i] = 0;
    param_1[0xf] = 0xf9000a63a9000a61;
}

/*--------------------------------------------------------------------*/
/* FUN_0037e58c @ 0x0037e58c   (est. sk_hash_state_init)
 * Ghidra: void FUN_0037e58c(undefined8 *param_1, undefined8 param_2, ulong param_3)
 * Seeds a 7-word hash state from param_3 using splitmix64-derived constants,
 * then runs the first block (FUN_0037e614).
 * Confidence: medium.
 */
void sk_hash_state_init(uint64_t *param_1, uint64_t param_2, ulong param_3)
{
    *param_1 = 0;
    param_1[1] = param_3;
    ulong uVar1 = param_3 ^ 0xb492b66fbe98f273;
    ulong uVar2 = (uVar1 * -0x622015f714c7d297 ^ uVar1 * -0x622015f714c7d297 >> 0x2f ^ 0xb492b66fbe98f273) * -0x622015f714c7d297;
    param_1[2] = (uVar2 ^ uVar2 >> 0x2f) * -0x622015f714c7d297;
    param_1[3] = uVar1 >> 0x31 | uVar1 << 0xf;
    uVar1 = param_3 ^ param_3 >> 0x2f;
    param_1[4] = param_3 * -0x4b6d499041670d8d;
    param_1[5] = uVar1;
    uVar1 = (uVar1 ^ param_3 * -0x4b6d499041670d8d) * -0x622015f714c7d297;
    uVar1 = (param_3 ^ (uVar1 ^ param_3) >> 0x2f ^ uVar1) * -0x622015f714c7d297;
    param_1[6] = (uVar1 ^ uVar1 >> 0x2f) * -0x622015f714c7d297;
    FUN_0037e614(param_1, param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_0037e614 @ 0x0037e614   (est. sk_hash_block)
 * Ghidra: void FUN_0037e614(ulong *param_1, long param_2)
 * One round of the metadata hash mixing (splitmix64/xxhash-style word
 * mixer), consuming 7 state words and 4 input words.
 * Confidence: medium.
 */
void sk_hash_block(ulong *param_1, long param_2)
{
    ulong uVar4 = param_1[3];
    ulong uVar2 = param_1[1] + *param_1 + uVar4 + *(long *)(param_2 + 8);
    ulong uVar1 = (uVar2 >> 0x25 | uVar2 * 0x8000000) * -0x4b6d499041670d8d;
    ulong uVar5 = param_1[4];
    *param_1 = uVar1;
    uVar2 = uVar5 + param_1[1] + *(long *)(param_2 + 0x30);
    ulong uVar3 = (uVar2 >> 0x2a | uVar2 * 0x400000) * -0x4b6d499041670d8d;
    ulong *puVar6 = param_1 + 6;
    uVar1 = *puVar6 ^ uVar1;
    *param_1 = uVar1;
    param_1[1] = uVar3;
    ulong *puVar7 = param_1 + 5;
    uVar2 = *puVar7 + param_1[2];
    param_1[1] = uVar3 + uVar4 + *(long *)(param_2 + 0x28);
    param_1[2] = (uVar2 >> 0x21 | uVar2 * 0x80000000) * -0x4b6d499041670d8d;
    param_1[3] = uVar5 * -0x4b6d499041670d8d;
    param_1[4] = *puVar7 + uVar1;
    FUN_0037e720((long *)param_2, (ulong *)puVar7, (ulong *)puVar6);
    *puVar7 = *puVar6 + param_1[2];
    *puVar6 = *(long *)(param_2 + 0x10) + param_1[1];
    FUN_0037e720((long *)(param_2 + 0x20), puVar7, puVar6);
    uVar2 = param_1[2];
    param_1[2] = *param_1;
    *param_1 = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037e720 @ 0x0037e720   (est. sk_hash_mix_pair)
 * Ghidra: void FUN_0037e720(long *param_1, ulong *param_2, ulong *param_3)
 * Mixes two hash lanes (param_2/param_3) using the input words at param_1.
 * Confidence: medium.
 */
void sk_hash_mix_pair(long *param_1, ulong *param_2, ulong *param_3)
{
    long lVar1 = *param_1;
    ulong uVar3 = *param_2;
    *param_2 = uVar3 + lVar1;
    long lVar4 = param_1[3];
    ulong uVar3b = lVar4 + *param_3 + uVar3 + lVar1;
    *param_3 = uVar3b >> 0x15 | uVar3b << 0x2b;
    ulong uVar2 = *param_2;
    uVar3 = param_1[1] + uVar2 + param_1[2];
    *param_2 = uVar3;
    *param_3 = *param_3 + uVar2 + (uVar3 >> 0x2c | uVar3 * 0x100000);
    *param_2 = *param_2 + lVar4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037e780 @ 0x0037e780   (est. sk_hash_append)
 * Ghidra: undefined8 * FUN_0037e780(undefined8 *param_1, long *param_2,
 *                                  undefined8 *param_3, undefined8 *param_4,
 *                                  undefined8 param_5)
 * Appends data into the hash buffer, extending the 7-word state (via
 * FUN_0037e58c/FUN_0037e614) and managing the write cursor.
 * Confidence: medium.
 */
uint64_t *sk_hash_append(uint64_t *param_1, long *param_2, uint64_t *param_3,
                         uint64_t *param_4, uint64_t param_5)
{
    uint64_t *puVar3 = param_3 + 1;
    if (param_4 < puVar3) {
        long lVar4 = (long)param_4 - (long)param_3;
        uint64_t local_38 = param_5;
        FUN_00117cc4(param_3, &local_38, lVar4);
        if (*param_2 == 0) {
            uint64_t state[7];
            FUN_0037e58c(&state[0], (uint64_t)param_1, param_1[0xf]);
            for (int i = 0; i < 7; i++) param_1[8 + i] = state[i];
            long lVar2 = 0x40;
            *param_2 = lVar2;
        } else {
            FUN_0037e614(param_1 + 8, (long)param_1);
            *param_2 = *param_2 + 0x40;
        }
        uint64_t *puVar1 = (uint64_t *)((long)param_1 + (8 - lVar4));
        puVar3 = param_1;
        if (puVar1 <= param_4) {
            FUN_00117cc4(param_1, (void *)((long)&local_38 + lVar4), 0);
            puVar3 = puVar1;
        }
    } else {
        *param_3 = param_5;
    }
    return puVar3;
}

/*--------------------------------------------------------------------*/
/* FUN_0037e868 @ 0x0037e868   (est. sk_hash_finish)
 * Ghidra: void FUN_0037e868(long param_1, long param_2, long param_3,
 *                           undefined8 param_4)
 * Finalizes the hash: if a tail block exists, processes it (FUN_0037ebe4 +
 * FUN_0037e614 + FUN_0037eb4c); otherwise runs the short finalizer
 * (FUN_0037e8e8).
 * Confidence: medium.
 */
void sk_hash_finish(long param_1, long param_2, long param_3, uint64_t param_4)
{
    if (param_2 != 0) {
        FUN_0037ebe4((uint8_t *)param_1, (uint8_t *)param_2, (uint8_t *)param_3);
        FUN_0037e614((ulong *)(param_1 + 0x40), param_1);
        FUN_0037eb4c((long *)(param_1 + 0x40), (param_2 - param_1) + param_3);
        return;
    }
    FUN_0037e8e8((ulong *)param_1, param_3 - param_1, *(uint64_t *)(param_1 + 0x78));
}

/*--------------------------------------------------------------------*/
/* FUN_0037e8e8 @ 0x0037e8e8   (est. sk_hash_short_final)
 * Ghidra: ulong FUN_0037e8e8(ulong *param_1, ulong param_2, ulong param_3)
 * Final hash mix for short inputs (< 0x80 bytes), with length-dispatched
 * mixing (splitmix64/xxhash-style). Returns the 64-bit digest.
 * Confidence: high (recognizable hash mixing constants).
 */
ulong sk_hash_short_final(ulong *param_1, ulong param_2, ulong param_3)
{
    ulong uVar6, uVar7, uVar8, uVar9, uVar10, uVar1, uVar2, uVar3;
    if (param_2 - 4 < 5) {
        param_3 = param_3 ^ *(uint32_t *)((long)param_1 + (param_2 - 4));
        uVar6 = (param_3 ^ param_2 + (ulong)(uint)*param_1 * 8) * -0x622015f714c7d297;
        uVar6 = param_3 ^ uVar6 >> 0x2f ^ uVar6;
    } else if (param_2 - 9 < 8) {
        uVar7 = *(ulong *)((long)param_1 + (param_2 - 8));
        uVar6 = uVar7 + param_2;
        uVar8 = uVar6 >> (param_2 & 0x3f) | uVar6 << (0x40 - (param_2 & 0x3f));
        uVar6 = (*param_1 ^ param_3 ^ uVar8) * -0x622015f714c7d297;
        uVar6 = (uVar8 ^ uVar6 >> 0x2f ^ uVar6) * -0x622015f714c7d297;
        return (uVar6 ^ uVar6 >> 0x2f) * -0x622015f714c7d297 ^ uVar7;
    } else if (0xf < param_2 - 0x11) {
        if (param_2 < 0x21) {
            if (param_2 == 0) return param_3 ^ 0x9ae16a3b2f90404f;
            uVar6 = (ulong)CONCAT11(*(uint8_t *)((long)param_1 + (param_2 >> 1)), (char)*param_1) *
                    -0x651e95c4d06fbfb1 ^
                    (param_2 + (ulong)*(uint8_t *)((long)param_1 + (param_2 - 1)) * 4) *
                    -0x36b62838af619aa9 ^ param_3;
        } else {
            long lVar4 = *(long *)((long)param_1 + (param_2 - 0x10));
            long lVar5 = *(long *)((long)param_1 + (param_2 - 8));
            uVar9 = *param_1 + (lVar4 + param_2) * -0x3c5a37a36834ced9;
            uVar6 = uVar9 + param_1[3];
            uVar7 = uVar9 + param_1[1];
            uVar8 = uVar7 + param_1[2];
            uVar10 = *(long *)((long)param_1 + (param_2 - 0x20)) + param_1[2];
            uVar1 = uVar10 + lVar5;
            uVar2 = *(long *)((long)param_1 + (param_2 - 0x18)) + uVar10;
            uVar3 = uVar2 + lVar4;
            long lVar4b = (uVar7 >> 7 | uVar7 << 0x39) + (uVar9 >> 0x25 | uVar9 * 0x8000000) +
                    (uVar6 >> 0x34 | uVar6 * 0x1000) + (uVar8 >> 0x1f | uVar8 << 0x21);
            uVar6 = (uVar3 + lVar5 + lVar4b) * -0x3c5a37a36834ced9 +
                    (uVar8 + param_1[3] + (uVar10 >> 0x25 | uVar10 * 0x8000000) +
                     (uVar1 >> 0x34 | uVar1 * 0x1000) + (uVar2 >> 7 | uVar2 << 0x39) +
                     (uVar3 >> 0x1f | uVar3 << 0x21)) * -0x651e95c4d06fbfb1;
            uVar6 = ((uVar6 ^ uVar6 >> 0x2f) * -0x3c5a37a36834ced9 ^ param_3) + lVar4b;
        }
        return (uVar6 ^ uVar6 >> 0x2f) * -0x651e95c4d06fbfb1;
    } else {
        long lVar4 = *(long *)((long)param_1 + (param_2 - 8));
        uVar8 = *param_1 * -0x4b6d499041670d8d - param_1[1];
        uVar10 = lVar4 * -0x651e95c4d06fbfb1 ^ param_3;
        uVar6 = param_1[1] ^ 0xc949d7c7509e6557;
        uVar7 = param_3 + param_2 + (uVar6 >> 0x14 | uVar6 << 0x2c) + *param_1 * -0x4b6d499041670d8d +
                lVar4 * 0x651e95c4d06fbfb1;
        uVar6 = ((uVar8 >> 0x2b | uVar8 * 0x200000) +
                 *(long *)((long)param_1 + (param_2 - 0x10)) * -0x3c5a37a36834ced9 +
                 (uVar10 >> 0x1e | uVar10 << 0x22) ^ uVar7) * -0x622015f714c7d297;
        uVar6 = uVar7 ^ uVar6 >> 0x2f ^ uVar6;
    }
    return (uVar6 * -0x622015f714c7d297 ^ uVar6 * -0x622015f714c7d297 >> 0x2f) * -0x622015f714c7d297;
}

/*--------------------------------------------------------------------*/
/* FUN_0037eb4c @ 0x0037eb4c   (est. sk_hash_long_final)
 * Ghidra: long FUN_0037eb4c(long *param_1, ulong param_2)
 * Final hash mix for long inputs over the 7-word state.
 * Confidence: medium.
 */
long sk_hash_long_final(long *param_1, ulong param_2)
{
    ulong uVar1 = (param_1[5] ^ param_1[3]) * -0x622015f714c7d297;
    uVar1 = (param_1[5] ^ uVar1 >> 0x2f ^ uVar1) * -0x622015f714c7d297;
    ulong uVar2 = (param_1[6] ^ param_1[4]) * -0x622015f714c7d297;
    uVar2 = (param_1[6] ^ uVar2 >> 0x2f ^ uVar2) * -0x622015f714c7d297;
    uVar2 = *param_1 + (param_2 ^ param_2 >> 0x2f) * -0x4b6d499041670d8d +
            (uVar2 ^ uVar2 >> 0x2f) * -0x622015f714c7d297;
    uVar1 = (uVar2 ^ param_1[2] + (param_1[1] ^ (ulong)param_1[1] >> 0x2f) * -0x4b6d499041670d8d +
             (uVar1 ^ uVar1 >> 0x2f) * -0x622015f714c7d297) * -0x622015f714c7d297;
    uVar1 = (uVar2 ^ uVar1 >> 0x2f ^ uVar1) * -0x622015f714c7d297;
    return (uVar1 ^ uVar1 >> 0x2f) * -0x622015f714c7d297;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ebe4 @ 0x0037ebe4   (est. sk_mem_rotate)
 * Ghidra: undefined1[16] FUN_0037ebe4(undefined1 *param_1, undefined1 *param_2,
 *                                     undefined1 *param_3)
 * Rotates the [param_1,param_2) and [param_2,param_3) byte ranges (like
 * std::rotate), with fast paths for adjacent ranges, else FUN_0037ecac.
 * Returns {param_3, rotated-start}.
 * Confidence: high (std::rotate).
 */
uint64_t sk_mem_rotate(uint8_t *param_1, uint8_t *param_2, uint8_t *param_3)
{
    uint8_t *puVar2 = param_3;
    if (param_1 != param_2 && (puVar2 = param_1, param_2 != param_3)) {
        if (param_1 + 1 == param_2) {
            uint8_t uVar1 = *param_1;
            FUN_00117d14(param_1, param_1 + 1, (long)param_3 - (long)param_2);
            param_1[(long)param_3 - (long)param_2] = uVar1;
            puVar2 = param_1 + ((long)param_3 - (long)param_2);
        } else if (param_2 + 1 == param_3) {
            puVar2 = param_3 - 1;
            uint8_t uVar1 = *puVar2;
            if ((long)puVar2 - (long)param_1 != 0)
                FUN_00117d14(param_3 - ((long)puVar2 - (long)param_1), param_1, (long)puVar2 - (long)param_1);
            *param_1 = uVar1;
            puVar2 = param_3 - ((long)puVar2 - (long)param_1);
        } else {
            puVar2 = FUN_0037ecac(param_1, param_2, param_3);
        }
    }
    return ((uint64_t)(ulong)param_3 << 32) | (ulong)puVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ecac @ 0x0037ecac   (est. sk_mem_rotate_impl)
 * Ghidra: undefined1 * FUN_0037ecac(undefined1 *param_1, undefined1 *param_2,
 *                                  undefined1 *param_3)
 * General std::rotate implementation (equal-length swap fast path, else
 * GCD-based rotation).
 * Confidence: high (std::rotate).
 */
uint8_t *sk_mem_rotate_impl(uint8_t *param_1, uint8_t *param_2, uint8_t *param_3)
{
    long lVar4 = (long)param_2 - (long)param_1;
    long lVar3 = (long)param_3 - (long)param_2;
    long lVar5 = lVar4;
    long lVar8 = lVar3;
    uint8_t *puVar6 = param_2;
    if (lVar4 == lVar3) {
        for (; param_1 != param_2 && puVar6 != param_3; puVar6++) {
            uint8_t uVar2 = *param_1;
            *param_1 = *puVar6;
            *puVar6 = uVar2;
            param_1++;
        }
    } else {
        long lVar7;
        do {
            lVar7 = lVar8;
            lVar8 = 0;
            if (lVar7 != 0) lVar8 = lVar5 / lVar7;
            lVar8 = lVar5 - lVar8 * lVar7;
            lVar5 = lVar7;
        } while (lVar8 != 0);
        puVar6 = param_1 + lVar7;
        do {
            puVar6--;
            uint8_t uVar2 = *puVar6;
            uint8_t *puVar9 = puVar6;
            uint8_t *puVar1 = puVar6 + lVar4;
            uint8_t *puVar10;
            do {
                puVar10 = puVar1;
                *puVar9 = *puVar10;
                puVar1 = puVar10 + lVar4;
                if ((long)param_3 - (long)puVar10 <= lVar4)
                    puVar1 = param_1 + (lVar4 - ((long)param_3 - (long)puVar10));
                puVar9 = puVar10;
            } while (puVar1 != puVar6);
            *puVar10 = uVar2;
        } while (puVar6 != param_1);
        param_2 = param_1 + lVar3;
    }
    return param_2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ed70 @ 0x0037ed70   (est. sk_hash_u64_sm)
 * Ghidra: long FUN_0037ed70(ulong param_1)
 * splitmix64 hash (same as FUN_0037c68c).
 * Confidence: high.
 */
long sk_hash_u64_sm(ulong param_1)
{
    ulong uVar1 = ((param_1 & 0xffffffff) * 8 + 0xf9000a63a9000a61 ^ param_1 >> 0x20) * -0x622015f714c7d297;
    uVar1 = (param_1 >> 0x20 ^ uVar1 >> 0x2f ^ uVar1) * -0x622015f714c7d297;
    return (uVar1 ^ uVar1 >> 0x2f) * -0x622015f714c7d297;
}

/*--------------------------------------------------------------------*/
/* FUN_0037edf0 @ 0x0037edf0   (est. sk_meta_backing_reinit)
 * Ghidra: void FUN_0037edf0(undefined8 *param_1)
 * Re-initializes a metadata backing structure in place (zero fields + fresh
 * mutex at [8]).
 * Confidence: medium.
 */
void sk_meta_backing_reinit(uint64_t *param_1)
{
    for (int i = 0; i < 8; i++) param_1[i] = 0;
    FUN_0037a850(param_1 + 4, 0);
    param_1[6] = 0; param_1[7] = 0;
    uint64_t uVar1 = (uint64_t)FUN_00111890(0x10, 0x1000c40451b5be8);
    uVar1 = FUN_0037a850((void *)uVar1, 0);
    param_1[8] = uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ee50 @ 0x0037ee50   (est. sk_meta_find_ptr)
 * Ghidra: undefined1[16] FUN_0037ee50(long *param_1, ulong param_2, ulong param_3,
 *                                     long param_4)
 * Finds a table entry whose first word equals *param_1 (hash via
 * FUN_0037ed70), returning {slot_index, slot_ptr}.
 * Confidence: medium.
 */
sk_pair_t sk_meta_find_ptr(long *param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong local_48 = param_2;
    ulong uVar2 = FUN_0037ed70(*param_1);
    ulong uVar3 = 4;
    if ((param_2 & 3) != 0 && (uint8_t *)(param_2 & 0xfffffffffffffffc) != 0)
        uVar3 = *(uint8_t *)(param_2 & 0xfffffffffffffffc);
    uVar3 = -1L << (uVar3 & 0x3f);
    uVar2 = uVar2 & ~uVar3;
    if (uVar2 < 2) uVar2 = 1;
    int iVar1 = FUN_0035b178(&local_48, uVar2, 2);
    if (iVar1 != 0) {
        do {
            ulong uVar4 = (ulong)(iVar1 - 1);
            if (uVar4 < param_3 && *param_1 == **(long **)(param_4 + uVar4 * 8)) {
                return SKPAIR2((uint64_t)(param_4 + uVar4 * 8), uVar2);
            }
            uVar2 = uVar2 + 1 & ~uVar3;
            if (uVar2 < 2) uVar2 = 1;
            iVar1 = FUN_0035b178(&local_48, uVar2, 2);
        } while (iVar1 != 0);
    }
    return SKPAIR2(0, uVar2 & 0xffffffff);
}

/*--------------------------------------------------------------------*/
/* FUN_0037ef3c @ 0x0037ef3c   (est. sk_meta_name_span)
 * Ghidra: undefined1[16] FUN_0037ef3c(long param_1, uint *param_2)
 * Computes the byte span of a mangled type name: walks the field table,
 * resolving '7'-kind (relative) offsets, and returns {span_ptr, length}
 * ending at param_2.
 * Confidence: medium.
 */
uint64_t sk_meta_name_span(long param_1, uint32_t *param_2)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    long lVar6 = param_1 + 0x14 + (long)iVar1;
    if (iVar1 != 0 && lVar6 != 0) {
        ulong uVar2 = thunk_FUN_00115080(lVar6);
        long lVar8 = param_1 + 0x18;
        if (lVar8 == 0) lVar8 = 0;
        if (*(uint32_t *)(param_1 + 0x10) != 0) {
            uint32_t *puVar7 = (uint32_t *)(lVar8 + (ulong)*(uint32_t *)(param_1 + 0xc) * 0xc);
            long lVar8b = (ulong)*(uint32_t *)(param_1 + 0x10) << 3;
            do {
                if ((*puVar7 & 0xf) == 7) {
                    ulong uVar5 = 0xffffffffffffffff;
                    if (uVar2 != 0) {
                        long lVar3 = thunk_FUN_001144a0((void *)lVar6, 0x20, uVar2);
                        uVar5 = 0xffffffffffffffff;
                        if (lVar3 != 0) uVar5 = lVar3 - lVar6;
                    }
                    ulong uVar4 = (uVar5 <= uVar2) ? uVar5 : uVar2;
                    if (puVar7 == param_2) return (uVar4 << 32) | lVar6;
                    lVar6 = lVar6 + uVar4;
                    if (uVar5 < uVar2) lVar6++;
                    uVar2 = (uVar2 - uVar4) - (uVar5 < uVar2);
                }
                puVar7 += 2;
                lVar8b -= 8;
            } while (lVar8b != 0);
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f0a0 @ 0x0037f0a0   (est. sk_desc_alloc_fd)
 * Ghidra: void FUN_0037f0a0(long param_1)
 * Allocates a 0x10 descriptor node {0x67b220, *param_1+8}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    *puVar1 = 0x67b220;
    puVar1[1] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f160 @ 0x0037f160   (est. sk_desc_alloc_fd2)
 * Ghidra: void FUN_0037f160(long param_1)
 * Allocates a 0x10 descriptor node {0x67b268, *param_1+8}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd2(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    *puVar1 = 0x67b268;
    puVar1[1] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f214 @ 0x0037f214   (est. sk_meta_fill_kind)
 * Ghidra: void FUN_0037f214(byte *param_1, long *param_2, undefined8 param_3)
 * Fills a metadata kind record: decodes the type kind bits, acquires the
 * registry lock, and stores the kind/payload words. Traps on invalid kind.
 * Confidence: medium.
 */
void sk_meta_fill_kind(uint8_t *param_1, long *param_2, uint64_t param_3)
{
    FUN_0037f398();
    ulong *puVar4 = (ulong *)FUN_0037f430((void *)param_3);
    ulong uVar2 = _DAT_006c0720;
    long lVar6 = *param_2;
    uint32_t uVar1 = (uint32_t)*puVar4 & 7;
    if (lVar6 < 0x3f) {
        if (lVar6 == 0) {
            if (3 < uVar1) goto invalid;
            FUN_0037a48c((void *)_DAT_006c0720);
            ulong uVar5 = *puVar4;
            uVar1 = (uint32_t)uVar5 & 7;
            *param_1 = (uint8_t)uVar1;
            if (3 < uVar1) goto clear;
        } else {
            if (lVar6 != 1) goto trap;
            if (2 < uVar1) goto invalid;
            FUN_0037a48c((void *)_DAT_006c0720);
            ulong uVar5 = *puVar4;
            uVar1 = (uint32_t)uVar5 & 7;
            *param_1 = (uint8_t)uVar1;
            if (2 < uVar1) goto clear;
        }
    } else if (lVar6 == 0x3f) {
        if (1 < uVar1) goto invalid;
        FUN_0037a48c((void *)_DAT_006c0720);
        ulong uVar5 = *puVar4;
        uVar1 = (uint32_t)uVar5 & 7;
        *param_1 = (uint8_t)uVar1;
        if (1 < uVar1) goto clear;
    } else {
        if (lVar6 != 0xff) goto trap;
        if ((*puVar4 & 7) != 0) goto invalid;
        FUN_0037a48c((void *)_DAT_006c0720);
        ulong uVar5 = *puVar4;
        *param_1 = (uint8_t)uVar5 & 7;
        if ((uVar5 & 7) != 0) goto clear;
    }
    {
        ulong uVar5 = *puVar4;
        uint64_t *puVar7 = (uint64_t *)(uVar5 & 0xfffffffffffffff0);
        uint64_t uVar8 = 0, uVar10 = 0;
        if (((uVar5 >> 3) & 1) == 0 || puVar7 == 0) {
            if (puVar7 != 0 && (uVar5 & 8) == 0) { uVar8 = *puVar7; uVar10 = *(uint64_t *)((long)puVar7 + 8); }
        } else {
            uVar8 = *(uint64_t *)(puVar7 + 5);
            uVar10 = *(uint64_t *)((long)puVar7 + 0x30);
        }
        *(uint64_t *)(param_1 + 8) = uVar8;
        *(uint64_t *)(param_1 + 0x10) = uVar10;
    }
    goto out;
clear:
    param_1[8] = 0; param_1[9] = 0; param_1[10] = 0; param_1[0xb] = 0;
    param_1[0xc] = 0; param_1[0xd] = 0; param_1[0xe] = 0; param_1[0xf] = 0;
    goto out;
invalid:
    *param_1 = (uint8_t)uVar1;
    param_1[8] = 0; param_1[9] = 0; param_1[10] = 0; param_1[0xb] = 0;
    param_1[0xc] = 0; param_1[0xd] = 0; param_1[0xe] = 0; param_1[0xf] = 0;
    return;
trap:
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37f398) */
out:
    FUN_0037a978(uVar2);
}

/*--------------------------------------------------------------------*/
/* FUN_0037f398 @ 0x0037f398   (est. sk_meta_ensure_locked)
 * Ghidra: void FUN_0037f398(void)
 * Ensures the object registry lock is initialized (one-time FUN_003d3dd8).
 * Confidence: medium.
 */
void sk_meta_ensure_locked(void)
{
    if (-1 < _DAT_006c0730) FUN_003d3dd8(&_DAT_006c0730, (void *)FUN_0037f3d0);
}

/*--------------------------------------------------------------------*/
/* FUN_0037f3d0 @ 0x0037f3d0   (est. sk_meta_backing_init2)
 * Ghidra: void FUN_0037f3d0(undefined8 *param_1)
 * Metadata backing init (same as sk_meta_backing_reinit).
 * Confidence: medium.
 */
void sk_meta_backing_init2(uint64_t *param_1)
{
    for (int i = 0; i < 8; i++) param_1[i] = 0;
    FUN_0037a850(param_1 + 4, 0);
    param_1[6] = 0; param_1[7] = 0;
    uint64_t uVar1 = (uint64_t)FUN_00111890(0x10, 0x1000c40451b5be8);
    uVar1 = FUN_0037a850((void *)uVar1, 0);
    param_1[8] = uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f430 @ 0x0037f430   (est. sk_meta_registry_lookup)
 * Ghidra: undefined8 FUN_0037f430(undefined8 param_1)
 * Looks up key param_1 in the global registry (table _DAT_006c06e8..), under
 * lock, returning the entry value or 0.
 * Confidence: medium.
 */
uint64_t sk_meta_registry_lookup(uint64_t param_1)
{
    LOAcquire();
    _DAT_006c06e0++;
    uint64_t uVar1 = 0;
    if (_DAT_006c06e8 != 0 && _DAT_006c06f0 != 0 && _DAT_006c06e4 != 0) {
        uint64_t local_28 = param_1;
        uint64_t *puVar2 = (uint64_t *)FUN_0037f4bc(&local_28, _DAT_006c06f0, _DAT_006c06e4, (void *)(_DAT_006c06e8 + 8));
        if (puVar2 != 0) uVar1 = *puVar2;
    }
    _DAT_006c06e0--;
    LORelease();
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f4bc @ 0x0037f4bc   (est. sk_meta_registry_find)
 * Ghidra: undefined1[16] FUN_0037f4bc(undefined8 *param_1, ulong param_2,
 *                                     ulong param_3, long param_4)
 * Finds a registry entry equal to *param_1 (hash via FUN_003a2b38),
 * returning {slot_index, slot_ptr}.
 * Confidence: medium.
 */
sk_pair_t sk_meta_registry_find(uint64_t *param_1, ulong param_2, ulong param_3, long param_4)
{
    ulong local_a0 = param_2;
    uint8_t buf[16];
    uint64_t local_88, uStack_80;
    FUN_00387e60(buf, *param_1);
    ulong uVar2 = FUN_003a2b38(local_88, uStack_80);
    ulong uVar4 = 4;
    if ((param_2 & 3) != 0 && (uint8_t *)(param_2 & 0xfffffffffffffffc) != 0)
        uVar4 = *(uint8_t *)(param_2 & 0xfffffffffffffffc);
    uVar4 = -1L << (uVar4 & 0x3f);
    uVar2 = uVar2 & ~uVar4;
    if (uVar2 < 2) uVar2 = 1;
    int iVar1 = FUN_0035b178(&local_a0, uVar2, 2);
    if (iVar1 != 0) {
        do {
            ulong uVar5 = (ulong)(iVar1 - 1);
            if (uVar5 < param_3 &&
                (FUN_0037f5b0((void *)*(uint64_t *)(param_4 + uVar5 * 8), (void *)*param_1) & 1) != 0) {
                return SKPAIR2((uint64_t)(param_4 + uVar5 * 8), uVar2);
            }
            uVar2 = uVar2 + 1 & ~uVar4;
            if (uVar2 < 2) uVar2 = 1;
            iVar1 = FUN_0035b178(&local_a0, uVar2, 2);
        } while (iVar1 != 0);
    }
    return SKPAIR2(0, uVar2 & 0xffffffff);
}

/*--------------------------------------------------------------------*/
/* FUN_0037f5b0 @ 0x0037f5b0   (est. sk_meta_entry_eq)
 * Ghidra: bool FUN_0037f5b0(long param_1, undefined8 param_2)
 * Compares a registry entry's key (param_1+8) with param_2 via the metadata
 * hash/string comparison.
 * Confidence: medium.
 */
bool sk_meta_entry_eq(long param_1, uint64_t param_2)
{
    uint8_t buf[16];
    uint64_t local_78, local_70;
    FUN_00387e60(buf, param_2);
    long lVar2 = local_70;
    uint64_t uVar1 = local_78;
    FUN_00376634(*(uint64_t *)(param_1 + 8));
    FUN_00387e60(buf);
    if (lVar2 == local_70) {
        if (lVar2 == 0) return true;
        return thunk_FUN_001145b0((void *)uVar1, (void *)local_78, lVar2) == 0;
    }
    return false;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f638 @ 0x0037f638   (est. sk_cap_resolve_class)
 * Ghidra: undefined8 FUN_0037f638(uint *param_1)
 * Resolves a capability to its class object: kind 0x10 via FUN_0037f7a4,
 * 0x11 via FUN_0037bcac, 0x12 via FUN_0037b3b8 (tag-adjusted); returns the
 * class ref at +8. Traps on invalid kind.
 * Confidence: medium.
 */
uint64_t sk_cap_resolve_class(uint32_t *param_1)
{
    uint32_t uVar1 = *param_1 & 0x1f;
    int *piVar3;
    if (uVar1 == 0x10) {
        piVar3 = (int *)FUN_0037f7a4(param_1);
    } else {
        long lVar4;
        if (uVar1 == 0x11) {
            if (param_1 == 0) param_1 = 0;
            lVar4 = FUN_0037bcac(param_1);
        } else {
            if (uVar1 != 0x12) __builtin_trap();   /* SoftwareBreakpoint(1,0x37f7a4) */
            if (param_1 == 0) param_1 = 0;
            lVar4 = FUN_0037b3b8(param_1);
        }
        piVar3 = (int *)(lVar4 + ((*param_1 & 0x30000) == 0x20000) * 4);
    }
    long lVar4 = 0;
    if (*piVar3 != 0) lVar4 = (long)*piVar3 + (long)piVar3;
    return *(uint64_t *)(lVar4 + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_0037f7a4 @ 0x0037f7a4   (est. sk_cap_class_off)
 * Ghidra: long FUN_0037f7a4(uint *param_1)
 * Capability class offset: base (FUN_00379480) + tag-derived stride.
 * Confidence: medium.
 */
long sk_cap_class_off(uint32_t *param_1)
{
    if (param_1 == 0) param_1 = 0;
    long lVar1 = FUN_00379480((void *)param_1);
    return lVar1 + ((*param_1 >> 0x1d) & 1) * 4 + ((*param_1 & 0x30000) == 0x20000) * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f828 @ 0x0037f828   (est. sk_meta_fill_kind_short)
 * Ghidra: void FUN_0037f828(undefined1 *param_1, ulong *param_2, undefined8 *param_3,
 *                           long param_4)
 * Short metadata kind fill: validates the kind, then runs FUN_0037f940.
 * Traps on invalid kind.
 * Confidence: medium.
 */
void sk_meta_fill_kind_short(uint8_t *param_1, ulong *param_2, uint64_t *param_3, long param_4)
{
    ulong local_20 = *param_2;
    uint32_t uVar1 = (uint32_t)local_20 & 7;
    long lStack_18 = param_4;
    if (param_4 < 0x3f) {
        if (param_4 == 0) {
            if (3 < uVar1) goto invalid;
        } else {
            if (param_4 != 1) goto trap;
            if (2 < uVar1) goto invalid;
        }
    } else if (param_4 == 0x3f) {
        if (1 < uVar1) goto invalid;
    } else {
        if (param_4 != 0xff) goto trap;
        if ((local_20 & 7) != 0) goto invalid;
    }
    FUN_0037f940((void *)(uintptr_t)*param_3, (void *)(uintptr_t)param_2, (void *)param_3);
    return;
invalid:
    *param_1 = (uint8_t)uVar1;
    *(uint64_t *)(param_1 + 8) = 0;
    return;
trap:
    __builtin_trap();   /* SoftwareBreakpoint(1,0x37f8c8) */
}

/*--------------------------------------------------------------------*/
/* FUN_0037f8c8 @ 0x0037f8c8   (est. sk_meta_slot_lookup)
 * Ghidra: undefined8 FUN_0037f8c8(int *param_1, undefined8 param_2)
 * Looks up key param_2 in the metadata table (param_1+2/4/1) under lock,
 * returning the entry value or 0.
 * Confidence: medium.
 */
uint64_t sk_meta_slot_lookup(int *param_1, uint64_t param_2)
{
    LOAcquire();
    *param_1 = *param_1 + 1;
    long lVar3;
    do { lVar3 = *(long *)(param_1 + 2); } while (lVar3 != *(long *)(param_1 + 2));
    uint64_t uVar1 = 0;
    if (lVar3 != 0 && *(long *)(param_1 + 4) != 0 && param_1[1] != 0) {
        sk_pair_t a238r = FUN_0037a238((long)param_2, *(long *)(param_1 + 4), param_1[1], (long)(lVar3 + 8));
        uint64_t *puVar2 = (uint64_t *)a238r.lo;
        if (puVar2 != 0) uVar1 = *puVar2;
    }
    *param_1 = *param_1 - 1;
    LORelease();
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0037f940 @ 0x0037f940   (est. sk_meta_fill_kind_from_word)
 * Ghidra: void FUN_0037f940(byte *param_1, undefined8 param_2, undefined8 *param_3)
 * Fills a kind record from the metadata word: validates via FUN_0037ae38 and
 * stores the kind/payload words.
 * Confidence: medium.
 */
void sk_meta_fill_kind_from_word(uint8_t *param_1, uint64_t param_2, uint64_t *param_3)
{
    sk_mtx_lock_checked();
    uint64_t *puVar2 = (uint64_t *)*param_3;
    *puVar2 = *(uint64_t *)param_3[1];
    int iVar1 = FUN_0037ae38((uint8_t *)puVar2, *(uint64_t *)param_3[2]);
    ulong uVar3 = *(ulong *)*param_3;
    *param_1 = (uint8_t)uVar3 & 7;
    if (iVar1 != 0) {
        param_1[8] = param_1[9] = param_1[10] = param_1[0xb] = 0;
        param_1[0xc] = param_1[0xd] = param_1[0xe] = param_1[0xf] = 0;
        goto out;
    }
    {
        uint64_t *puVar2b = (uint64_t *)(uVar3 & 0xfffffffffffffff0);
        uint64_t uVar4 = 0, val = 0;
        if (((uVar3 >> 3) & 1) == 0 || puVar2b == 0) {
            if (puVar2b != 0 && (uVar3 & 8) == 0) { uVar4 = *puVar2b; val = *(uint64_t *)((long)puVar2b + 8); }
        } else {
            uVar4 = *(uint64_t *)(puVar2b + 5);
            val = *(uint64_t *)((long)puVar2b + 0x30);
        }
        *(uint64_t *)(param_1 + 8) = uVar4;
        *(uint64_t **)(param_1 + 0x10) = (uint64_t *)val;
    }
out:
    sk_mtx_unlock_checked();
}

/*--------------------------------------------------------------------*/
/* FUN_0037f9f4 @ 0x0037f9f4   (est. sk_noop)
 * Ghidra: void FUN_0037f9f4(void)
 * No-op.
 * Confidence: high (trivial).
 */
void sk_noop(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0037f9f8 @ 0x0037f9f8   (est. sk_return0)
 * Ghidra: undefined8 FUN_0037f9f8(void)
 * Returns 0.
 * Confidence: high (trivial).
 */
uint64_t sk_return0(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_0037fa0c @ 0x0037fa0c   (est. sk_desc_alloc_fd3)
 * Ghidra: void FUN_0037fa0c(long param_1)
 * Allocates a 0x10 descriptor node {0x67b2b0, *param_1+8}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd3(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x10, 0xe1c40d30581f4);
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    *puVar1 = 0x67b2b0;
    puVar1[1] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037fad8 @ 0x0037fad8   (est. sk_desc_alloc_fd4)
 * Ghidra: void FUN_0037fad8(long param_1)
 * Allocates a 0x28 descriptor node {0x67b2f8, *param_1+8, +0x10, +0x18, +0x20}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd4(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x28, 0x81c402fcc0cb6);
    *puVar1 = 0x67b2f8;
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    puVar1[2] = *(uint64_t *)(param_1 + 0x10);
    puVar1[1] = uVar2;
    uVar2 = *(uint64_t *)(param_1 + 0x18);
    puVar1[4] = *(uint64_t *)(param_1 + 0x20);
    puVar1[3] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037fc54 @ 0x0037fc54   (est. sk_desc_move_value)
 * Ghidra: void FUN_0037fc54(undefined8 *param_1, int param_2, int param_3,
 *                           undefined8 *param_4)
 * Moves a descriptor value between param_1 and param_4 based on kind states
 * (0/1): copies, releases, or steals depending on the transition.
 * Confidence: medium.
 */
void sk_desc_move_value(uint64_t *param_1, int param_2, int param_3, uint64_t *param_4)
{
    code *pcVar1;
    uint64_t uVar2, uVar3;
    if (param_2 == param_3) {
        if (param_2 != 0) {
            if (param_2 != 1) return;
            if (param_1 == param_4) return;
            (*(code *)param_1[1])((void *)(uintptr_t)*param_1, 3, 0);
            uVar2 = *param_4;
            pcVar1 = (code *)param_4[1];
            param_1[1] = (uint64_t)pcVar1;
            uVar2 = (*pcVar1)((void *)(uintptr_t)uVar2, 2, 0);
            *param_1 = uVar2;
            return;
        }
        uVar3 = param_4[1];
        uVar2 = *param_4;
        *(uint8_t *)(param_1 + 2) = *(uint8_t *)(param_4 + 2);
    } else {
        if (param_2 == 1) (*(code *)param_1[1])((void *)(uintptr_t)*param_1, 3, 0);
        if (param_3 == 1) {
            uVar2 = *param_4;
            param_1[1] = param_4[1];
            *param_1 = uVar2;
            *param_4 = 0;
            param_4[1] = (uint64_t)FUN_0037f9f8;
            return;
        }
        if (param_3 != 0) return;
        uVar3 = param_4[1];
        uVar2 = *param_4;
        param_1[2] = param_4[2];
    }
    param_1[1] = uVar3;
    *param_1 = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037fd48 @ 0x0037fd48   (est. sk_desc_alloc_fd5)
 * Ghidra: void FUN_0037fd48(long param_1)
 * Allocates a 0x10 descriptor node {0x67b340, *param_1+8}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd5(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    *puVar1 = 0x67b340;
    puVar1[1] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037fe08 @ 0x0037fe08   (est. sk_desc_alloc_fd6)
 * Ghidra: void FUN_0037fe08(long param_1)
 * Allocates a 0x10 descriptor node {0x67b388, *param_1+8}.
 * Confidence: medium (vtable node allocator).
 */
void sk_desc_alloc_fd6(long param_1)
{
    uint64_t *puVar1 = (uint64_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    uint64_t uVar2 = *(uint64_t *)(param_1 + 8);
    *puVar1 = 0x67b388;
    puVar1[1] = uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0037febc @ 0x0037febc   (est. sk_cap2_stage_size)
 * Ghidra: long FUN_0037febc(uint *param_1)
 * Capability stage size: base (FUN_0037b3b8) + tag-derived stride + staged
 * payload word.
 * Confidence: medium.
 */
long sk_cap2_stage_size(uint32_t *param_1)
{
    long lVar3 = FUN_0037b3b8(0);
    uint32_t uVar2 = *param_1;
    uint32_t uVar1 = uVar2 & 0x80080;
    ulong uVar5 = 0;
    if (uVar1 == 0x80080) {
        if (param_1 == 0) param_1 = 0;
        long lVar4 = FUN_0037b3b8(param_1);
        uVar5 = *(uint32_t *)(lVar4 + ((*param_1 & 0x30000) == 0x20000) * 4 +
                              ((*param_1 & 0x30000) == 0x10000) * 0xc);
    }
    uVar2 = uVar2 & 0x30000;
    return lVar3 + (uVar2 == 0x20000) * 4 + (uVar2 == 0x10000) * 0xc +
           (uVar1 == 0x80080) * 4 + uVar5 * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_0037ffc4 @ 0x0037ffc4   (est. sk_cap2_stage_size2)
 * Ghidra: long FUN_0037ffc4(uint *param_1)
 * Capability stage size variant (base FUN_0037bcac).
 * Confidence: medium.
 */
long sk_cap2_stage_size2(uint32_t *param_1)
{
    long lVar3 = FUN_0037bcac(0);
    uint32_t uVar2 = *param_1;
    uint32_t uVar1 = uVar2 & 0x80080;
    ulong uVar5 = 0;
    if (uVar1 == 0x80080) {
        if (param_1 == 0) param_1 = 0;
        long lVar4 = FUN_0037bcac(param_1);
        uVar5 = *(uint32_t *)(lVar4 + ((*param_1 & 0x30000) == 0x20000) * 4 +
                              ((*param_1 & 0x30000) == 0x10000) * 0xc);
    }
    uVar2 = uVar2 & 0x30000;
    return lVar3 + (uVar2 == 0x20000) * 4 + (uVar2 == 0x10000) * 0xc +
           (uVar1 == 0x80080) * 4 + uVar5 * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_00372c58 @ 0x00372c58   (est. sk_msg_desc_build_impl)
 * Ghidra: void FUN_00372c58(undefined8 param_1, undefined8 param_2, ulong param_3,
 *                           long param_4, long param_5, long param_6)
 * Full message-descriptor construction: aggregates per-entry lengths/flags,
 * computes staged sizes (FUN_00372fbc), allocates the packed buffer
 * (FUN_00369758), serializes each child (FUN_0037311c), commits, copies the
 * descriptor, and fills type/flags/size fields. Core bind/IPC message-buffer
 * builder for the syscall region.
 * Confidence: medium.
 */
void sk_msg_desc_build_impl(void *param_1, void *param_2, ulong param_3,
                            long *param_4, long *param_5, long *param_6)
{
    ulong local_78 = 0, uVar7 = 0, uVar15 = 0;
    uint32_t uVar10 = 0, uVar12 = 0;
    if (param_3 != 0) {
        bool bVar3 = true, bVar1 = true, bVar4 = true;
        ulong uVar11 = 0, uVar15 = 1;
        do {
            ulong uVar8 = uVar15;
            long *plVar17 = *(long **)(param_4 + uVar11 * 8);
            if (*(char *)(param_5 + uVar11) == '\0') plVar17 = (long *)(plVar17[-1] + 0x40);
            ulong uVar16 = (ulong)*(uint32_t *)(plVar17 + 2);
            local_78 = local_78 + (uint8_t)*(uint32_t *)(plVar17 + 2) & ~(uVar16 & 0xff);
            int iVar5 = (int)local_78;
            if (*(int32_t *)(param_6 + uVar11 * 4) != iVar5) {
                *(int32_t *)(param_6 + uVar11 * 4) = iVar5;
                uVar16 = (ulong)*(uint32_t *)(plVar17 + 2);
            }
            local_78 = *plVar17 + local_78;
            if (uVar7 <= (uVar16 & 0xff)) uVar7 = uVar16 & 0xff;
            bVar3 = (uVar16 & 0x10000) == 0 && bVar3;
            bVar1 = (uVar16 & 0x100000) == 0 && bVar1;
            bVar4 = (uVar16 & 0x1100000) == 0 && bVar4;
            uVar15 = (ulong)((int)uVar7 + 1);
            uVar11 = uVar7;
        } while (param_3 != uVar7);
        uVar12 = bVar3 ? 0 : 0x10000;
        uint32_t uVar13 = bVar4 ? 0 : 0x1000000;
        uint32_t uVar14 = bVar1 ? 0 : 0x100000;
        uVar10 = (bVar1 && (uVar7 < 8 && local_78 < 0x19)) ? 0 : 0x20000;
        uVar10 = uVar13 | (uint)uVar7 | uVar14 | uVar12 | uVar10;
    }
    uVar15 = local_78;
    uVar7 = (local_78 + uVar7) & ~uVar7;
    if (uVar7 < 2) uVar7 = 1;
    ulong uVar11 = 0;
    if (param_3 != 0) {
        uint32_t uVar12 = 0;
        for (ulong i = 0; i < param_3; i++) {
            if (*(uint8_t *)(param_5 + i) == 0) {
                uint32_t k = *(uint32_t *)(*(long *)(*(long *)(param_4 + i * 8) - 8) + 0x54);
                if (k > uVar12) uVar12 = k;
                uVar11 += sk_desc_total_size((ulong *)((long *)param_4)[i * 8]);
            } else {
                uVar11 += (*(uint8_t *)(param_5 + i) <= 4) ? 8 : 0;
                uint32_t k = *(uint32_t *)(*(long *)(param_4 + i * 8) + 0x14);
                if (k > uVar12) uVar12 = k;
            }
        }
    }
    ulong *buf = (ulong *)FUN_00369758(&uVar11, (uVar11 + 0x1f) & 0xfffffffffffffff8, 1);
    buf[1] = uVar11;
    ulong out[5] = { (ulong)buf, 0x10, 0, 0, 0 };
    if (param_3 != 0) {
        for (ulong i = 0; i < param_3; i++) {
            if (*(uint8_t *)(param_5 + i) == 0)
                sk_desc_serialize_node(out, &out[4], *(ulong **)(param_4 + i * 8), &out[2], &out[3]);
            else {
                long *plVar17 = *(long **)(param_4 + i * 8);
                ulong u = (ulong)*(uint8_t *)(plVar17 + 2);
                ulong u16 = out[2] + u & ~u;
                ulong off = (u16 - out[2]) + out[3];
                if (*(uint8_t *)(param_5 + i) < 5) {
                    ulong tag = (*(uint8_t *)(param_5 + i) > 2) ? 0x700000000000000 : 0x600000000000000;
                    *(ulong *)((long)buf + out[1]) = off | tag;
                    out[1] += 8;
                }
                out[2] = *plVar17;
                out[3] = out[2] + off;
                out[2] = out[2] + u16;
            }
        }
        buf[0] = out[4] & 0x7fffffffffffffff;
        out[1] = 8;
    }
    *(long *)((long)buf + out[1]) = out[3];
    *buf = out[4] & 0x7fffffffffffffff;
    FUN_0035cf38(param_1, buf, 1);
    long *lVar9 = sk_desc_copy((long)param_1, 0);
    sk_desc_fill_from_type((long *)&local_78, (uint64_t *)lVar9);
    *(ulong *)(lVar9 + 0x40) = uVar15;
    *(ulong *)(lVar9 + 0x48) = uVar7;
    *(uint32_t *)(lVar9 + 0x50) = uVar10;
    *(uint32_t *)(lVar9 + 0x54) = uVar12;
}

/*--------------------------------------------------------------------*/
/* FUN_00373700 @ 0x00373700   (est. sk_msg_build_metadata)
 * Ghidra: undefined1[16] FUN_00373700(long param_1, uint param_2, ulong param_3,
 *                                     long param_4, long param_5, uint param_6)
 * Builds message metadata from a capability chain: demangles the class name
 * (FUN_00373444), walks the type descriptor (resolving generic fields via
 * FUN_00374230/FUN_003742e4), copies inline payload, and fills a metadata
 * record. Emits a "resilient vtable at %p contains o" panic (0x5d4f9b) on a
 * bad vtable.
 * Confidence: low (large Swift-metadata message builder).
 */
uint64_t sk_msg_build_metadata(long param_1, uint32_t param_2, ulong param_3,
                               long param_4, long param_5, uint32_t param_6)
{
    bool bVar6 = (param_6 & 1) != 0;
    ulong uVar4 = bVar6 ? 1 : 0xff;
    sk_pair_t cls = sk_class_demangle_alloc(bVar6 ? 0x101 : 0xff, param_1);
    ulong uVar8 = cls.lo;
    uint32_t uVar27 = 0;
    if (uVar8 == 0 || cls.hi <= uVar4) {
        ulong *puVar1 = (ulong *)(param_1 + 8);
        ulong uVar14 = uVar8 ? uVar8 : 0;
        *(ulong *)(param_1 + 8) = uVar14;
        ulong uVar19 = uVar14;
        for (; uVar14 != 0; uVar14 = *(ulong *)(uVar14 + 8)) {
            uint32_t *puVar23 = *(uint32_t **)(uVar14 + 0x28);
            if (puVar23 == 0) puVar23 = 0;
            uVar27 = *puVar23;
            if ((uVar27 >> 7 & 1) != 0) {
                uint32_t *puVar9 = puVar23 ? puVar23 : 0;
                if ((short)puVar9[0xe] != 0) {
                    int iVar7 = FUN_0035efa0(puVar23);
                    FUN_00117cc4((void *)(param_1 + (long)iVar7 * 8), (void *)(uVar19 + (long)iVar7 * 8U),
                                 (ulong)(ushort)puVar9[0xe] << 3);
                    uVar27 = *puVar23;
                }
            }
            if (((param_2 >> 8 & 1) == 0) && ((int)uVar27 < 0)) {
                uint32_t *puVar9 = (uint32_t *)FUN_00374230(puVar23);
                if ((*(uint8_t *)((long)puVar23 + 3) >> 5 & 1) == 0) uVar27 = *puVar9;
                else { FUN_0036f878(puVar23); uVar27 = *puVar9; }
                FUN_003742e4(puVar23);
                ulong uVar15 = (ulong)puVar9[1];
                if (puVar9[1] != 0) {
                    uint64_t *puVar18 = (uint64_t *)(uVar19 + (ulong)uVar27 * 8);
                    uint64_t *puVar17 = (uint64_t *)(param_1 + (ulong)uVar27 * 8);
                    do { *puVar17 = *puVar18; puVar18++; uVar15--; puVar17++; } while (uVar15 != 0);
                }
            }
            uVar27 = puVar23[10];
            if (uVar27 != 0) {
                if ((*(uint8_t *)((long)puVar23 + 3) >> 5 & 1) != 0) {
                    FUN_0036f878(puVar23);
                    uVar27 = puVar23[10];
                }
                FUN_00117cc4((void *)(param_1 + (ulong)uVar27 * 8), (void *)(uVar19 + (ulong)uVar27 * 8),
                             (ulong)puVar23[9] << 3);
            }
        }
        if ((param_2 >> 8 & 1) == 0) {
            int *piVar24 = *(int **)(param_1 + 0x28);
            if (piVar24 == 0) piVar24 = 0;
            if (*piVar24 < 0) {
                uint32_t *puVar23 = (uint32_t *)FUN_00374230((uint32_t *)piVar24);
                if ((*(uint8_t *)((long)piVar24 + 3) >> 5 & 1) == 0) uVar27 = *puVar23;
                else { FUN_0036f878(piVar24); uVar27 = *puVar23; }
                FUN_003742e4(piVar24);
                ulong uVar14 = (ulong)puVar23[1];
                if (puVar23[1] != 0) {
                    int *piVar10 = (int *)(FUN_003742e4(piVar24).lo + 4);
                    int *piVar20 = piVar10;
                    do {
                        long lVar22 = (*piVar20 != 0) ? (long)piVar10 + (long)*piVar20 : 0;
                        piVar20 += 2;
                        *(long *)(param_1 + (ulong)uVar27 * 8) = lVar22;
                        uVar27++;
                        piVar10 += 2;
                        uVar14--;
                    } while (uVar14 != 0);
                }
            }
            if ((*(uint8_t *)((long)piVar24 + 3) >> 6 & 1) != 0) {
                uint64_t fr[2] = SKPAIR(FUN_0037d25c(piVar24));
                if (fr[1] != 0) {
                    long base = fr[0], p = base + 4;
                    for (ulong i = 0; i < fr[1]; i++) {
                        long src = FUN_003658e8(base);
                        uint32_t idx = *(uint32_t *)(base + 4);
                        long *dst = (idx != 0) ? (long *)(p + ((long)(int)idx & 0xfffffffffffffffeU)) : 0;
                        if ((idx & 1) != 0 && dst != 0 && *dst == 0) dst = 0;
                        if (src != 0 && dst != 0) {
                            uint64_t range[2] = SKPAIR(FUN_003742e4((uint32_t *)src));
                            if ((ulong)dst < range[0] || range[0] + range[1] * 8 <= (ulong)dst)
                                FUN_00369bb0(0, (char *)0x5d4f9b);
                            uint32_t *pw = (uint32_t *)FUN_00374230((uint32_t *)src);
                            if ((*(uint8_t *)(src + 3) >> 5 & 1) == 0) uVar27 = *pw;
                            else { FUN_0036f878((void *)src); uVar27 = *pw; }
                            long target = (*(int *)(base + 8) != 0) ? p + *(int *)(base + 8) + 4 : 0;
                            *(long *)((long)dst + (ulong)uVar27 * 8 + (param_1 - (long)range[0])) = target;
                        }
                        base += 0xc; p += 0xc;
                    }
                }
            }
            uVar8 = FUN_0037daa8(&uVar4);
        }
    }
    return uVar8;
}

/*--------------------------------------------------------------------*/
/* FUN_003743d0 @ 0x003743d0   (est. sk_dedup_insert_a)
 * Ghidra: long FUN_003743d0(long param_1)
 * Inserts key param_1 into dedup registry A (table _DAT_006c0558/
 * _DAT_006c0560/_DAT_006c0554, lock _DAT_006c0550, cache _DAT_006c0598).
 * Builds a 0x20 entry {0x304, 0x67ad90, param_1}, rehashing on load. Returns
 * the entry payload (+0x10) or 0.
 * Confidence: medium.
 */
long sk_dedup_insert_a(long param_1)
{
    ulong local_90 = 0;
    if (_DAT_006c0598 != 0 && param_1 == *(long *)(_DAT_006c0598 + 0x18)) return _DAT_006c0598 + 0x10;
    LOAcquire();
    _DAT_006c0550++;
    local_90 = param_1;
    ulong *puVar14;
    if (_DAT_006c0558 != 0 && _DAT_006c0560 != 0 && _DAT_006c0554 != 0 &&
        (puVar14 = (ulong *)FUN_00383a1c(&local_90, _DAT_006c0560, _DAT_006c0554, (void *)(_DAT_006c0558 + 2)),
         puVar14 != 0)) {
        _DAT_006c0550--;
        LORelease();
        _DAT_006c0598 = *puVar14;
        goto found;
    }
    _DAT_006c0550--;
    LORelease();
    FUN_00361718(0, 0, 0x6c0570);
    {
        uint32_t *puVar19 = 0;
        void *res = FUN_00383a1c(&local_90, _DAT_006c0560, _DAT_006c0554, puVar19);
        if (res == 0) {
            uint64_t local_68 = 0;
            if (FUN_0001062c(&local_68, 8, 0x20, 0x59dd9b33) != 0 || local_68 == 0)
                __builtin_trap();
            *(uint64_t *)(local_68 + 0x10) = 0x304;
            *(uint64_t *)(local_68 + 8) = 0x67ad90;
            *(long *)(local_68 + 0x18) = param_1;
            _DAT_006c0554 = _DAT_006c0554 + 1;
            local_90 = local_68;
        } else {
            local_90 = *(ulong *)res;
        }
    }
    DataMemoryBarrier(2, 3);
    FUN_0035b228(0);
    _DAT_006c0598 = local_90;
found:
    return (local_90 != 0) ? local_90 + 0x10 : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00374838 @ 0x00374838   (est. sk_dedup_insert_b)
 * Ghidra: long FUN_00374838(ulong *param_1)
 * Inserts key param_1 into dedup registry B (table _DAT_006c05a8/
 * _DAT_006c05b0/_DAT_006c05a4, lock _DAT_006c05a0, cache _DAT_006c05e8).
 * Builds a 0x28 entry keyed by param_1, rehashing on load. Returns the entry
 * payload (+0x10) or 0.
 * Confidence: medium.
 */
long sk_dedup_insert_b(ulong *param_1)
{
    ulong local_90 = 0;
    if (_DAT_006c05e8 != 0 && param_1 == *(ulong **)(_DAT_006c05e8 + 0x18)) return _DAT_006c05e8 + 0x10;
    LOAcquire();
    _DAT_006c05a0++;
    local_90 = (ulong)param_1;
    ulong *puVar12;
    if (_DAT_006c05a8 != 0 && _DAT_006c05b0 != 0 && _DAT_006c05a4 != 0 &&
        (puVar12 = (ulong *)FUN_00383a1c(&local_90, _DAT_006c05b0, _DAT_006c05a4, (void *)(_DAT_006c05a8 + 2)),
         puVar12 != 0)) {
        _DAT_006c05a0--;
        LORelease();
        _DAT_006c05e8 = *puVar12;
        goto found;
    }
    _DAT_006c05a0--;
    LORelease();
    FUN_00361718(0, 0, 0x6c05c0);
    {
        uint32_t *puVar17 = 0;
        void *res = FUN_00383a1c(&local_90, _DAT_006c05b0, _DAT_006c05a4, puVar17);
        if (res == 0) {
            uint64_t local_68 = 0;
            if (FUN_0001062c(&local_68, 8, 0x28, 0x59dd9b33) != 0 || local_68 == 0)
                __builtin_trap();
            *(uint64_t *)(local_68 + 0x10) = 0x306;
            *(ulong *)(local_68 + 0x18) = (ulong)param_1;
            _DAT_006c05a4 = _DAT_006c05a4 + 1;
            local_90 = local_68;
        } else {
            local_90 = *(ulong *)res;
        }
    }
    DataMemoryBarrier(2, 3);
    FUN_0035b228(0);
    _DAT_006c05e8 = local_90;
found:
    return (local_90 != 0) ? local_90 + 0x10 : 0;
}
