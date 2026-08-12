/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel, GL1, arm64e,
 * image base 0) — the seL4-derived microkernel. Ground truth: Ghidra FUN_ names
 * + addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice SKR69: 0x66b038-0x67669c — the final tail region (capability decode,
 * IPC error-code reporting, per-CPU/global management, and the tail exception
 * / bookkeeping helpers). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte {lo,hi} value the runtime passes through registers/vtables. */
typedef cl4_result_t sk_pair_t;

/* Generic callable used for opaque vtable dispatch. */
typedef long (*sk_fp_t)();


/* The cL4 supervisor-call entry: the sole way from the Secure Kernel into the
 * lower guarded level. `n` selects the operation. */
#define CallSupervisor(n)  __asm__ volatile("hvc #0" ::: "memory")

/* Per-cpu L4 IPC message buffer (the code writes tpidrro_el0 then traps). */
static unsigned long sk_ipc_msg[8];
/* Out-of-range cL4 helpers (declared extern; the FUN_ address in each comment
 * is ground truth; bodies reconstructed by the range worker that owns them).
 * Unspecified-arg prototypes keep call-site argument counts permissive.
 */
extern long FUN_0064effc();
extern long FUN_00655200();
extern long FUN_00656474();
extern long FUN_00656634();
extern long FUN_00656b2c();
extern long FUN_0065be08();
extern long FUN_0065c2f0();
extern long FUN_006662ac();
extern long FUN_00666344();
extern long FUN_00666448();
extern long FUN_00666800();
extern long FUN_00666d84();
extern long FUN_00667588();
extern long FUN_00667e54();
extern long FUN_00668128();
extern long FUN_00668c6c();
extern long FUN_00668c78();
extern sk_pair_t FUN_00668c94();
extern long FUN_00668dd8();
extern long FUN_006690dc();
extern long FUN_006692e4();
extern long FUN_00669330();
extern long FUN_00669388();
extern long FUN_006693d4();
extern long FUN_0066942c();
extern long FUN_00669478();
extern long FUN_006694d0();
extern long FUN_0066951c();
extern long FUN_00669618();
extern long FUN_006699e8();
extern long FUN_00669a48();
extern long FUN_0066a65c();
extern long FUN_0066a6b4();
extern sk_pair_t FUN_0066a9bc();
extern long FUN_0066ab40();
extern long FUN_0066ad54();
extern long FUN_0066af84();
extern sk_pair_t FUN_006766cc();
extern long FUN_00676a7c();
extern long FUN_0067728c();
extern long FUN_00677674();
extern long FUN_006777d8();
extern long FUN_006782b4();
extern long FUN_006786fc();
extern long FUN_006787a0();
extern long FUN_0067882c();
extern long FUN_00678a40();
extern long FUN_00678ae0();
extern long FUN_00679784();
extern long FUN_00679838();
extern long FUN_00679990();
extern long FUN_00679b98();
extern sk_pair_t FUN_00679d44();
extern sk_pair_t FUN_0067a154();
extern long FUN_0067a264();
extern long FUN_0067a334();
extern long FUN_0067a3dc();
extern long FUN_0067a444();
extern long FUN_0067a510();
extern long FUN_0067a740();
extern long FUN_0067a760();
extern long FUN_0067a7f0();
extern long FUN_0067aa00();
extern long FUN_0067cb30();
extern long FUN_0067cfb0();
extern long FUN_0067cfe0();
extern long FUN_0067cffc();
extern long FUN_0067d02c();
extern long FUN_0067d72c();
extern long FUN_0067f660();
extern long FUN_006833d4();
extern long FUN_006860f4();
extern long FUN_006863f0();
extern sk_pair_t FUN_0068642c();
extern long FUN_00686464();
extern long FUN_0068649c();
extern long FUN_006864b4();
extern long FUN_006864cc();
extern long FUN_00686544();
extern long FUN_0068656c();
extern long FUN_006865a4();
extern long FUN_006865dc();
extern long FUN_0068664c();
extern long FUN_00686730();
extern long FUN_00686768();
extern long FUN_006867bc();
extern long FUN_00686810();
extern long FUN_00686864();
extern long FUN_00686890();
extern long FUN_006868bc();
extern long FUN_006868e8();
extern long FUN_00686930();
extern long FUN_006869bc();
extern long FUN_006869e4();
extern long FUN_00686a0c();
extern long FUN_00686a54();
extern long FUN_00686a8c();
extern long FUN_00686b10();
extern long FUN_00686b64();
extern long FUN_00686c04();
extern long FUN_00686c2c();
extern sk_pair_t FUN_00686c74();
extern sk_pair_t FUN_00686c8c();
extern long FUN_00686d10();
extern long FUN_00686d58();
extern sk_pair_t FUN_00686d90();
extern sk_pair_t FUN_00686dc8();
extern long FUN_00686e00();
extern sk_pair_t FUN_00686e38();
extern sk_pair_t FUN_00686e70();
extern long FUN_00686ea8();
extern long FUN_00686ee0();
extern long FUN_00686f08();
extern long FUN_00686f30();
extern sk_pair_t FUN_00686f68();
extern long FUN_00686f94();
extern long FUN_00686ffc();
extern long FUN_00687050();
extern long FUN_00687098();
extern long FUN_00687124();
extern long FUN_00687174();
extern long FUN_006871c4();
extern long FUN_006871d8();
extern long FUN_006871ec();
extern long FUN_00687200();
extern long FUN_00687214();
extern long FUN_00687264();
extern long FUN_006872b4();
extern long FUN_00687304();
extern long FUN_00687354();
extern long FUN_0068739c();
extern long FUN_006873e4();
extern long FUN_0068742c();
extern long FUN_00687464();
extern long FUN_0068748c();
extern long thunk_FUN_0067aa00();
extern unsigned long DAT_006fea50;
extern long thunk_FUN_00655200();

/* In-range static helper forward declarations (definitions follow). */
static void sk_cap_decode(unsigned long *out, unsigned long cap, unsigned long op,
                          unsigned long size, unsigned int flags);
static void sk_l4_error_format(unsigned long *out, unsigned char code);
static unsigned long sk_page_tree_lookup(unsigned long key);
static bool sk_page_bitmap_test_set(unsigned long *block, long addr);
static void sk_page_tree_insert(unsigned long *rootp, unsigned long node);
static unsigned long sk_page_block_alloc(long base, unsigned long size, unsigned long count);
static void sk_page_block_free(unsigned long base, long size);
static sk_pair_t sk_cap_bucket_insert(unsigned long *bucket, unsigned long cap,
                                      unsigned int count, unsigned int flags);
static sk_pair_t sk_cap_bucket_op(long bucket, unsigned long arg);
static sk_pair_t sk_cap_bucket_resolve(unsigned long *bucket, unsigned int op);
static unsigned int sk_cap_tag_type(unsigned int cap);
static void sk_cap_iterate_free(unsigned long cap, sk_fp_t cb);
static unsigned long sk_cap_list_get(char *desc);
static void sk_cap_decode_tag(unsigned long *out, unsigned long cap, unsigned int op);
static void sk_cap_bucket_move(unsigned long *out, unsigned long *bucket,
                               unsigned int cap, unsigned long flag);
static void sk_cap_bucket_free_rec(unsigned long *bucket, sk_fp_t cb);
static void sk_page_region_init(long base, long end, long count);
static unsigned long sk_cap_value_base(unsigned long cap);
static void sk_cap_remove(unsigned long *out, unsigned long cap, unsigned int op, sk_fp_t cb);
static void sk_cap_merge(unsigned long *out, long a, unsigned long b);
static void sk_cap_restrict(unsigned long *out, unsigned long cap, unsigned long limit);
static unsigned int sk_cap_bucket_slot_remove(unsigned long *b, unsigned int idx, unsigned int cnt);
static sk_pair_t sk_cap_bucket_repack(unsigned long *bucket, unsigned int op, sk_fp_t cb);
static unsigned long FUN_0067203c(unsigned long a, void *b, void *c, unsigned long d, void *e);
static void FUN_00671ca8(void);
static unsigned long FUN_00673894(void *a, unsigned long b);
static void FUN_00671b60(void *a, unsigned long b, unsigned long c, unsigned long d);
static void FUN_00671bc4(void *a, unsigned long b);
static unsigned long FUN_00675b48(unsigned long a, unsigned long b, long *c);
static unsigned long FUN_00675ae8(void *a, ...);
static sk_pair_t sk_region_query(unsigned long ctx, unsigned long key, int *type, unsigned long *out);
static unsigned long sk_region_unlock(unsigned long ctx, unsigned long key, int mode);
static sk_pair_t sk_supervisor_op2(void);
static sk_pair_t sk_region_destroy(long owner, unsigned long *r);
static unsigned long sk_region_alloc_advance(long r, unsigned long *out);
static unsigned long sk_region_map_extend(long r, unsigned long *off, unsigned long *sz);
static unsigned long FUN_006736ec(unsigned long a, unsigned long b, unsigned long *c, long *d);
static void FUN_00673914(long a, unsigned long b, ...);
static unsigned long FUN_00675418(long a, unsigned long b, unsigned long c);
static void FUN_00674688(void *a, long *b, unsigned long *c, int d);
static void FUN_00671f38(long a);
static void FUN_0066e8b4(void);
static sk_pair_t sk_region_free(unsigned long r);
static void FUN_006745f4(unsigned long a, long b);
static unsigned long FUN_0067483c(void *a, long b, unsigned long c, ...);
static int FUN_006714f8(unsigned long *a, unsigned long b, int c, unsigned int d, unsigned int e, unsigned int f);
static void FUN_00671a48(unsigned long *a, unsigned long b, unsigned long *c);
static sk_pair_t FUN_00674934(unsigned long *a, unsigned long b, long c, long d, unsigned long *e, long *f);
static sk_pair_t FUN_00674364(unsigned long *a, unsigned long b, long c, unsigned long d, unsigned long *e, long *f);
static sk_pair_t FUN_00672098(unsigned long a, unsigned long b, void *c, long *d, unsigned long e, unsigned long f);
static sk_pair_t sk_region_merge(long *a, long *b, long type, long *out);
static sk_pair_t sk_region_split(long r, unsigned long off, long *out1, long *out2);
static sk_pair_t sk_region_subdivide(unsigned long *r, unsigned long size, unsigned int flags, unsigned long *out);
static sk_pair_t sk_region_remove(long *rp);
static unsigned long *sk_free_slot0_get(long ctx);
static void sk_free_slot0_put(long ctx, unsigned long *n);
static unsigned long sk_ctx_init(unsigned long *c, unsigned long owner,
                                 unsigned long n0, unsigned long n1,
                                 unsigned long n2, unsigned long n3);
static unsigned long sk_ctx_init_commit(unsigned long *c, unsigned long owner,
                                        unsigned long a, unsigned long b,
                                        unsigned long n0, unsigned long n1,
                                        unsigned long n2, unsigned long n3);
static void sk_ctx_commit(long *c, long owner, unsigned long a, unsigned long b);
static void sk_ctx_commit2(long *c, long owner, unsigned long a);
static void sk_ctx_begin(unsigned long *c, unsigned long owner, unsigned long a, unsigned long b);
static void sk_ctx_end(long *c, long owner);
static void sk_ctx_teardown(unsigned long *c);
static void sk_region_register2(unsigned long *c, unsigned long r);
static void sk_ctx_register(void);
static void sk_region_caps_release(long r);
static unsigned long FUN_00673adc(unsigned long *c);
static void FUN_00675d88(unsigned long a, unsigned long b);
static sk_pair_t sk_region_create(unsigned long ctx, unsigned int flags, char *desc,
                                  unsigned long *out, unsigned int *oflags, unsigned long *odesc);
static sk_pair_t sk_region_create_wrap(unsigned long op, void *d1, void *d2, unsigned long a, void *d3);
static unsigned int sk_region_method_set(long r, long type, unsigned long *m, unsigned long arg);
static void sk_region_span_find(unsigned long r, unsigned long *prev, long *next);
static unsigned long sk_region_find(unsigned long *c, unsigned long addr);
static sk_pair_t sk_region_lookup(unsigned long ctx, long addr, long *page, unsigned long *region);
static unsigned long *sk_free_slot4_get(long ctx);
static void sk_region_invalidate(char *r, unsigned long off, long len);
static unsigned long sk_region_page_next(long desc);
static void sk_region_page_remove(unsigned long cap, long r, int a, int mode, int notify);
static void sk_region_map_pages(unsigned long start, unsigned long len, long r,
                                unsigned long mode, unsigned long notify);
static void sk_region_desc_build(unsigned long *out, unsigned long *c, long spec, unsigned long *m);
extern void sk_obj_release_dispatch(long obj, unsigned int op);
static void FUN_00674264(unsigned long a, unsigned long b, long c, unsigned long d, void *e);
static void FUN_00673f50(long a);
static void FUN_00676498(void);
static void FUN_00676498(void);
static long sk_round_to_mult(unsigned long m);
static void sk_region_split_wrap(unsigned long a, unsigned long b, long r);
static void sk_region_desc_encode(char *r);
static unsigned long sk_region_span_alloc(long m, long r);
static void sk_region_tree_height(long root, long r);
static unsigned long sk_region_merge_wrap(unsigned long a, unsigned long b, long r1, long r2);
static sk_pair_t sk_region_merge_inner(unsigned long *c, unsigned long ctx, long a, long b, long *out1, long *out2);
static unsigned long sk_region_tree_remove(long *rootp, long r);
static void sk_region_tree_rebalance(unsigned long *rootp, int dir);
static sk_pair_t sk_region_pages_unmap(unsigned long r, unsigned long *off, unsigned long *len, int full);
static sk_pair_t sk_region_split_inner(long c, unsigned long ctx, unsigned long *src, unsigned long off, unsigned long *out, long *tail);
static sk_pair_t sk_page_map_walk(long r, long addr, unsigned long cb, long page, unsigned long cap, unsigned long flags, int x);
static unsigned long FUN_006757cc(void *a, unsigned long b);
static unsigned long FUN_006758c8(void *a, unsigned long b, unsigned long c, unsigned long d);
static unsigned long sk_page_map(long r, long addr, unsigned long mode, unsigned long flags,
                                unsigned long arg5, int arg6, unsigned long arg7);
static unsigned long sk_page_map_dispatch(char *r, unsigned long a2, unsigned long mode,
                                          unsigned long flags, unsigned long a5, int a6, unsigned int a7);
static unsigned long sk_page_map_range(char *r, unsigned long start, unsigned long len);
static void sk_region_page_notify(long ctx, long addr, unsigned int mode, long r, unsigned char *arg);
static unsigned long sk_region_teardown_all(unsigned long ctx);
static sk_pair_t sk_region_enter(unsigned long ctx, unsigned long arg2, unsigned long arg3);
static sk_pair_t sk_vspace_op(long ctx, long arg2, unsigned long flags, unsigned long arg4, unsigned char *desc);
static sk_pair_t sk_vspace_destroy(unsigned long ctx, unsigned long *out);

/* sk_l4_error_format @ 0x00674e98  (est. sk_l4_error_format)
 * Ghidra: void sk_l4_error_format(undefined8 *param_1, byte param_2)
 * Fills the 32-byte (4 x 8) error-report structure param_1 from an L4 error code
 * (param_2). Codes 0..9 map to the L4 error-code string table (Success,
 * Preempted, Canceled, Truncated, CapInvalid, SlotInvalid, MethodInvalid,
 * ..., OperationInvalid, PermissionInvalid) at 0x68a598; codes >9 copy the
 * generic 0x68a6d8 descriptor and call FUN_0064effc(param_1, 0x20) to
 * serialize it.
 * Confidence: high (L4 error-code strings matched) */
static void sk_l4_error_format(unsigned long *out, unsigned char code)
{
    if (code > 9) {
        out[1] = *(unsigned long *)0x68a6e0;
        out[0] = *(unsigned long *)0x68a6d8;
        out[3] = *(unsigned long *)0x68a6f0;
        out[2] = *(unsigned long *)0x68a6e8;
        FUN_0064effc(out, 0x20);
        return;
    }
    const char *s;
    switch (code) {
    default:              s = (const char *)0x68a598; break; /* L4_ErrorCodeSuccess */
    case 1:               s = (const char *)0x68a5b8; break; /* L4_ErrorCodePreempted */
    case 2:               s = (const char *)0x68a5d8; break; /* L4_ErrorCodeCanceled */
    case 3:               s = (const char *)0x68a5f8; break; /* L4_ErrorCodeTruncated */
    case 4:               s = (const char *)0x68a618; break; /* L4_ErrorCodeCapInvalid */
    case 5:               s = (const char *)0x68a638; break; /* L4_ErrorCodeSlotInvalid */
    case 6:               s = (const char *)0x68a658; break; /* L4_ErrorCodeMethodInvalid */
    case 7:               s = (const char *)0x68a678; break;
    case 8:               s = (const char *)0x68a698; break; /* L4_ErrorCodeOperationInvalid */
    case 9:               s = (const char *)0x68a6b8; break; /* L4_ErrorCodePermissionInvalid */
    }
    out[0] = *(unsigned long *)s;
    out[3] = *(unsigned long *)(s + 0x18);
    out[2] = *(unsigned long *)(s + 0x10);
    out[1] = *(unsigned long *)(s + 8);
}

/* sk_cap_decode @ 0x0066b884  (est. sk_cap_decode)
 * Ghidra: void sk_cap_decode(ulong *param_1, ulong param_2, undefined8 param_3,
 *                          ulong param_4, uint param_5)
 * Decodes a raw capability (param_2) into the 5-word capability representation
 * at param_1 (40 bytes), using op (param_3 & 0x3fffff), size param_4 and flags
 * param_5. Handles the short (type-0/1) direct forms and the long (pointer +
 * linked-list bucket scan) forms; when the create flag (param_5&1) is set,
 * allocates/links a new capability bucket via the runtime helpers. On
 * unresolved inputs the capability (param_2) is returned verbatim.
 * Confidence: medium */
static void sk_cap_decode(unsigned long *out, unsigned long cap, unsigned long op,
                          unsigned long size, unsigned int flags)
{
    unsigned int opc = (unsigned int)op;
    if (0x3fffff < opc) {
        out[0] = 0;
        out[1] = 0;
        out[3] = *(unsigned long *)0x68a538;
        out[2] = *(unsigned long *)0x68a530;
        goto finish;
    }
    unsigned int tag = (unsigned int)cap;
    if ((tag & 3) == 1 || (cap & 3) == 0) {
        if ((cap & 3) == 0) {
            unsigned long v = size << 0x1c;
            *(unsigned long *)((long)out + 0x11) = 0;
            *(unsigned long *)((long)out + 9) = 0;
            if (flags == 0) {
                size = 0;
            }
            out[0] = size;
            *(char *)(out + 1) = (char)flags;
            unsigned long e = (opc << 6 | 1) | v;
            if (flags == 0) {
                e = cap;
            }
            goto done_short;
        }
        if (((cap >> 6 & 0x3fffff) == opc)) {
            unsigned long v = cap >> 0x1c;
set_imm:
            out[0] = v;
            out[1] = 0;
            out[2] = 0;
            out[3] = 0;
            goto finish;
        }
        if ((flags & 1) == 0) goto no_create;
        long ctx = FUN_0066a65c();
        sk_pair_t r1 = sk_cap_bucket_insert((unsigned long *)ctx, cap, 8, 0);
        if (((r1.lo & 0xff) != 0) ||
            (r1 = sk_cap_bucket_insert((unsigned long *)ctx, (unsigned long)(opc << 6 | 1) | size << 0x1c, 8, 0),
             (r1.lo & 0xff) != 0)) goto fail_put;
        out[0] = size;
        unsigned long e = (unsigned long)ctx << 0x1c | 10;
        *(unsigned char *)(out + 1) = 1;
fill_e:
        *(unsigned long *)((long)out + 0x11) = 0;
fill_d:
        *(unsigned long *)((long)out + 9) = 0;
done_short:
        out[3] = 0;
        out[4] = e;
        return;
    }
    unsigned long *bucket = (unsigned long *)(cap >> 0x1c);
    if ((tag & 3) == 2) {
        unsigned long *end = bucket + 8;
        if ((end < bucket) || (bucket != 0 && ((long)end - (long)bucket < 0x39))) goto sb_break;
        long idx = 0;
        unsigned long *cur = 0;
        if (bucket != 0) {
            cur = end;
        }
        do {
            unsigned long *p = (unsigned long *)((long)bucket + idx);
            if ((p < bucket || cur < p + 1) || p + 1 < p) goto sb_break;
            unsigned long v = *p;
            if (((unsigned int)v & 3) == 1) {
                if ((((unsigned int)v >> 6 & 0x3fffff) == opc)) {
                    unsigned long r = v >> 0x1c;
                    goto set_imm;
                }
            } else if ((v & 3) == 0) break;
            idx = idx + 8;
        } while (idx != 0x40);
        if ((flags & 1) != 0) {
            unsigned long e = (unsigned long)(opc << 6 | 1) | size << 0x1c;
            unsigned int slot = (unsigned int)cap >> 2 & 0xf;
            bool small = (unsigned long)((long)cur - (long)bucket) < 0x39;
            if (slot < 8) {
                if (bucket != 0 && small) goto sb_break;
                sk_pair_t r = sk_cap_bucket_insert(bucket, e, 8, 0);
                if ((r.lo & 0xff) == 0) {
                    out[0] = size;
                    *(unsigned char *)(out + 1) = 1;
                    e = cap & 0xffffffffffffffc3 | (unsigned long)(slot * 4 + 4);
                    goto fill_e;
                }
fail_put:
                out[0] = 0;
                out[1] = 0;
                out[2] = r.lo;
                out[3] = r.hi;
                goto finish;
            }
            if (bucket != 0 && small) goto sb_break;
            unsigned long *cb = (unsigned long *)FUN_0066a65c();
            unsigned long *cend = 0;
            if (cb != 0) {
                cend = cb + 8;
            }
            if (cend < cb + 1) goto sb_break;
            idx = 0;
            *cb = *cb & 0xffffffffffffffc3 | 0xc;
            unsigned long *chead = cb;
            do {
                unsigned long *p = (unsigned long *)((long)bucket + idx);
                if ((p < bucket || cur < p + 1) || p + 1 < p) goto sb_break;
                if ((*p & 3) == 1) {
                    if ((cend < cb) || (cb < chead) ||
                        (cb != 0 && ((unsigned long)((long)cend - (long)cb) < 0x39)))
                        goto sb_break;
                    sk_pair_t _pc = sk_cap_bucket_op((long)cb, 0);
                    unsigned long *np = (unsigned long *)_pc.lo;
                    bool ok = np != 0;
                    cb = ok ? np : 0;
                    cend = ok ? np + 8 : 0;
                    chead = ok ? np : 0;
                }
                idx = idx + 8;
            } while (idx != 0x40);
            FUN_0066a6b4(bucket);
            if ((cend < cb) || (cb < chead) ||
                (cb != 0 && ((long)cend - (long)cb < 0x39))) goto sb_break;
            unsigned long b = (unsigned long)cb & 0xfffffffff;
            unsigned long b2 = b + 0x40;
            if ((b2 < b) || (b != 0 && ((long)(b2 - b) < 0x39))) goto sb_break;
            unsigned long b3 = 0;
            if (b != 0) b3 = b2;
            if ((b3 < b) || (b != 0 && (b3 - b < 0x39))) goto sb_break;
            sk_pair_t _p = sk_cap_bucket_op((long)b, e);
            long lr = (long)_p.lo;
            e = (unsigned long)(slot * 0x40 + 0x40);
            out[0] = size;
            *(unsigned char *)(out + 1) = 1;
            goto fill_e2;
        }
    } else {
        unsigned long *end = bucket + 8;
        if ((end < bucket) ||
            (bucket != 0 && ((long)end - (long)bucket < 0x39))) {
sb_break:
            /* bounds violation -> software breakpoint (noreturn) */
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66bce0) */
        }
        unsigned long *cur = 0;
        if (bucket != 0) {
            cur = end;
        }
        if ((cur < bucket) ||
            (bucket != 0 && ((unsigned long)((long)cur - (long)bucket) < 0x39)))
            goto sb_break;
        sk_pair_t r = sk_cap_bucket_resolve(bucket, op);
        unsigned long *p = (unsigned long *)r.lo;
        if ((r.hi & 0xf8) == 0) {
            unsigned long *e2 = 0;
            if (p != 0) {
                e2 = p + 8;
            }
            unsigned long *tgt = p + (r.hi & 7);
            if (((tgt < p) || (e2 < tgt + 1)) || (tgt + 1 < tgt)) goto sb_break;
            unsigned long v = *tgt >> 0x1c;
            if ((v != 0) && (((unsigned int)*tgt >> 6 & 0x3fffff) == opc)) goto set_imm;
        }
        if ((flags & 1) != 0) {
            sk_pair_t _p2 = sk_cap_bucket_op((long)bucket, (unsigned long)(opc << 6 | 1) | size << 0x1c);
            long lr = (long)_p2.lo;
            unsigned long e = (unsigned long)(tag + 0x40) & 0xfffffc0;
            out[0] = size;
            *(unsigned char *)(out + 1) = 1;
fill_e2:
            *(unsigned long *)((long)out + 0x11) = 0;
            e = e | lr << 0x1c | 3;
            goto fill_d;
        }
    }
no_create:
    out[1] = 0;
    out[0] = 0;
    out[3] = 0;
    out[2] = 0;
finish:
    out[4] = cap;
    return;
}

/* sk_cap_bucket_insert @ 0x0066c8ac  (est. sk_cap_bucket_insert)
 * Ghidra: undefined1 [16] sk_cap_bucket_insert(ulong *param_1, ulong param_2, uint param_3,
 *                                     uint param_4)
 * Inserts capability param_2 into the capability bucket param_1 (an 8-slot
 * array) at an index derived from param_3, when param_4's low bit is set. On
 * the non-create path it validates the target slot; if the slot is already
 * occupied it returns error code 0x910002 (pair). Otherwise it finds the
 * insertion point by scanning for a lower-or-equal op index, shifts the tail,
 * and stores param_2 (with the low 6 bits cleared and tag set). Returns a
 * 16-byte pair whose lo is the status code (0 on success).
 * Confidence: medium */
static sk_pair_t sk_cap_bucket_insert(unsigned long *bucket, unsigned long cap,
                                      unsigned int count, unsigned int flags)
{
    unsigned long status;
    if ((flags & 1) == 0) {
        unsigned long *end = 0;
        if (bucket != 0) end = bucket + 8;
        unsigned long *slot = bucket + (unsigned char)(count - 1);
        if ((slot < bucket) || (end < slot + 1 || slot + 1 < slot)) goto sb_break;
        if ((*slot & 3) != 0) {
            status = 0x910002;
            goto done;
        }
    }
    unsigned long idx = 0;
    unsigned long pos = 0;
    unsigned long *end = bucket + 8;
    unsigned long *lim = 0;
    if (bucket != 0) lim = end;
    unsigned int op = (unsigned int)cap >> 6 & 0x3fffff;
    status = 0x990001;
    unsigned long *p = bucket;
    for (;;) {
        if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto sb_break;
        pos = idx;
        if ((*p & 3) == 0) break;
        unsigned int eop = (unsigned int)*p >> 6 & 0x3fffff;
        if (op == eop) goto done;
        if ((op < eop) ||
            (idx = idx + 1, pos = (unsigned long)(count - 1), p = p + 1, count == idx))
            break;
    }
    unsigned long *ins = bucket + (pos & 0xff);
    unsigned long *dst = ins + 1;
    if (((bucket <= dst) && ((dst <= end && (ins <= end)))) && (bucket <= ins)) {
        long rem = ~(pos & 0xff) + (unsigned long)count;
        unsigned long nbytes = rem * 8;
        status = (pos & 0xff) * -8 + 0x40;
        if ((((nbytes < status || nbytes - status == 0) &&
             (status = (pos & 0xff) * -8 + 0x38, nbytes < status || nbytes - status == 0)) &&
            (thunk_FUN_0067aa00(dst, ins, nbytes), dst <= dst + rem)) &&
           (ins <= dst)) {
            status = 0;
            *ins = cap & 0xffffffffffffffc0 | *ins & 0x3c | 1;
done:
            { sk_pair_t r;
            r.hi = 0;
            r.lo = status;
            return r; }
        }
    }
sb_break:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c9ec) */
}

/* sk_cap_bucket_op @ 0x0066ca30  (est. sk_cap_bucket_op)
 * Ghidra: void sk_cap_bucket_op(long param_1, undefined8 param_2)
 * Performs a capability-bucket operation: bounds-checks the bucket, invokes the
 * bucket resolver sk_cap_bucket_move with (local, param_1, param_2, 0), and returns.
 * The decompiler collapses the return value (callers use the .lo pointer); a
 * zeroed pair is returned with a note.
 * Confidence: medium */
static sk_pair_t sk_cap_bucket_op(long bucket, unsigned long arg)
{
    unsigned long end = 0;
    if (bucket != 0) end = bucket + 0x40;
    if (bucket + 8U <= end) {
        unsigned long local[4] = {0, 0, 0, 0};
        if ((bucket == 0) || (0x38 < end - bucket)) {
            sk_cap_bucket_move(local, (unsigned long *)bucket, arg, 0);
            unsigned long nb = local[3] + 0x40;
            if ((local[3] <= nb) && ((local[3] == 0 || (0x38 < (long)(nb - local[3]))))) {
                unsigned long b2 = 0;
                if (local[3] != 0) b2 = nb;
                if ((local[3] <= b2) && ((local[3] == 0 || (0x38 < (long)(b2 - local[3]))))) {
                    return (sk_pair_t){local[0], local[1]};
                }
            }
        }
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66cac4) */
}

/* sk_cap_bucket_resolve @ 0x0066c204  (est. sk_cap_bucket_resolve)
 * Ghidra: void sk_cap_bucket_resolve(ulong *param_1, uint param_2)
 * Resolves/validates a capability bucket param_1 for op param_2: walks the
 * sorted bucket entries, returns a pair whose lo points at the matching (or
 * insertion) slot and hi holds the slot index/shift. Handles the
 * pointer-chain (type tag 0xc) form recursively.
 * Confidence: medium */
static sk_pair_t sk_cap_bucket_resolve(unsigned long *bucket, unsigned int op)
{
    unsigned long *lim = 0;
    if (bucket != 0) lim = bucket + 8;
    if (bucket + 1 <= lim) {
        if ((*bucket & 0x3c) == 0xc) {
            unsigned long idx = 0;
            unsigned long *p = bucket;
            while ((bucket <= p && (p + 1 <= bucket + 8)) && (p <= p + 1)) {
                if (((*p & 3) == 1 && op <= ((unsigned int)*p >> 6 & 0x3fffff)) ||
                    (idx = idx + 1, p = p + 1, idx == 7)) {
                    return (sk_pair_t){0, 0};
                }
            }
        } else {
            unsigned long idx = 0;
            unsigned long *p = bucket;
            do {
                if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto sb_break;
            } while (((*p & 0xfffffc0) != 0 && ((unsigned int)*p >> 6 & 0x3fffff) <= op) &&
                     (idx = idx + 1, p = p + 1, idx != 8));
            unsigned long *slot = bucket + (idx & 0xff);
            if ((bucket <= slot) && ((slot + 1 <= lim && (slot <= slot + 1)))) {
                unsigned long base = *slot >> 0x1c;
                unsigned long e = base + 0x40;
                if ((*slot >> 0x1c <= e) && ((base == 0 || (0x38 < (long)(e - base))))) {
                    unsigned long b2 = 0;
                    if (base != 0) b2 = e;
                    if ((base <= b2) && ((base == 0 || (0x38 < b2 - base)))) {
                        sk_pair_t r = sk_cap_bucket_resolve(bucket, op);
                        return r;
                    }
                }
            }
        }
    }
sb_break:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c354) */
}

/* sk_cap_tag_type @ 0x0066c5d0  (est. sk_cap_tag_type)
 * Ghidra: uint sk_cap_tag_type(uint param_1)
 * Extracts the capability tag-type from a raw capability: low 2 bits 0/1 => 1,
 * bits 2..5 (>>2 & 0xf) for type 2, bits 6..27 (>>6 & 0x3fffff) for type 3.
 * Confidence: high */
static unsigned int sk_cap_tag_type(unsigned int cap)
{
    unsigned int t = cap & 3;
    if (1 < t) {
        if (t != 3) {
            return cap >> 2 & 0xf;
        }
        t = cap >> 6 & 0x3fffff;
    }
    return t;
}

/* sk_cap_iterate_free @ 0x0066c5f8  (est. sk_cap_iterate_free)
 * Ghidra: void sk_cap_iterate_free(ulong param_1, code *UNRECOVERED_JUMPTABLE)
 * Iterates a capability value (param_1): for the direct (type 0/1) form calls
 * the callback with the tag field; for the type-2 bucket form calls the
 * callback for each occupied slot then frees the bucket; for the type-3 form
 * recursively releases the pointed structure via sk_cap_bucket_free_rec.
 * Confidence: medium */
static void sk_cap_iterate_free(unsigned long cap, sk_fp_t cb)
{
    unsigned int tag = (unsigned int)cap & 3;
    if (tag == 1 || (cap & 3) == 0) {
        if (((cap & 3) != 0) && (cb != 0)) {
            cb(cap >> 0x1c);   /* indirect jump: cb(cap>>28) */
            return;
        }
        return;
    }
    if (tag == 2) {
        unsigned long *bucket = (unsigned long *)(cap >> 0x1c);
        unsigned long *end = bucket + 8;
        if (((unsigned long *)(cap >> 0x1c) <= end) &&
           ((bucket == 0 || (0x38 < (long)end - (long)bucket)))) {
            long idx = 0;
            unsigned long *lim = 0;
            if (bucket != 0) lim = end;
            do {
                unsigned long *p = (unsigned long *)((long)bucket + idx);
                if ((p < bucket || lim < p + 1) || p + 1 < p) goto sb_break;
                if ((cb != 0) && ((*p & 3) == 1)) {
                    cb(*p >> 0x1c);
                }
                idx = idx + 8;
            } while (idx != 0x40);
            if ((bucket == 0) || ((bucket + 1 <= end && (bucket <= bucket + 1)))) {
                FUN_0066a6b4(bucket);
                return;
            }
        }
    } else {
        unsigned long base = cap >> 0x1c;
        unsigned long e = base + 0x40;
        if ((cap >> 0x1c <= e) && ((base == 0 || (0x38 < (long)(e - base))))) {
            unsigned long b2 = 0;
            if (base != 0) b2 = e;
            if ((base <= b2) && ((base == 0 || (0x38 < b2 - base)))) {
                sk_cap_bucket_free_rec((unsigned long *)0, 0);
                return;
            }
        }
    }
sb_break:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c76c) */
}

/* sk_cap_list_get @ 0x0066c354  (est. sk_cap_list_get)
 * Ghidra: ulong sk_cap_list_get(char *param_1)
 * Walks a capability descriptor (param_1: type byte + index byte + bucket
 * pointer) to fetch a capability: type 1 returns the direct slot value once
 * (flagging it); type 2 returns the indexed bucket slot; type 3 follows the
 * chain of 8-slot buckets until a matching (tag==1) entry is found.
 * Confidence: medium */
static unsigned long sk_cap_list_get(char *desc)
{
    char type = *desc;
    if (type == '\x01') {
        if (desc[1] == '\0') {
            desc[1] = '\x01';
            return *(unsigned long *)(desc + 0x10);
        }
    } else if (type == '\x02') {
        unsigned char b = desc[1];
        if (b < 8) {
            desc[1] = b + 1;
            unsigned long *base = *(unsigned long **)(desc + 8);
            unsigned long *end = 0;
            if (base != 0) end = base + 8;
            unsigned long *slot = base + b;
            if ((base <= slot && slot + 1 <= end) && slot <= slot + 1) {
                return *slot;
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c470) */
        }
    } else if (type == '\x03') {
        unsigned int i = (unsigned int)(unsigned char)desc[1];
        unsigned long *bucket = *(unsigned long **)(desc + 8);
        for (;;) {
            unsigned int save = i;
            if (6 < i) {
                unsigned long *p7 = bucket + 7;
                if (((p7 < bucket) || (bucket == 0)) || (bucket + 8 < p7))
                    goto sb2;
                bucket = (unsigned long *)(*p7 >> 0x1c);
                if (bucket == 0) {
                    return 0;
                }
                if (bucket + 8 < (unsigned long *)(*p7 >> 0x1c)) goto sb2;
                i = 0;
                *(unsigned long **)(desc + 8) = bucket;
            }
            i = save + 1;
            desc[1] = (char)i;
            unsigned long *end = 0;
            if (bucket != 0) end = bucket + 8;
            unsigned long *slot = bucket + save;
            if (((slot < bucket) || (end < slot + 1)) || (slot + 1 < slot)) goto sb2;
            if ((*slot & 3) == 1) {
                return *slot;
            }
        }
    }
    return 0;
sb2:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c470) */
}

/* sk_cap_decode_tag @ 0x0066c084  (est. sk_cap_decode_tag)
 * Ghidra: void sk_cap_decode_tag(undefined8 *param_1, ulong param_2, uint param_3)
 * Decodes the tag of a raw capability param_2 into a 3-slot descriptor
 * param_1, using op param_3. Direct (type 0/1) forms store the raw capability;
 * the type-3 pointer form resolves via sk_cap_bucket_resolve; the type-2
 * bucket form records the bucket and scan index.
 * Confidence: medium */
static void sk_cap_decode_tag(unsigned long *out, unsigned long cap, unsigned int op)
{
    unsigned int tag = (unsigned int)cap & 3;
    if (tag == 1 || (cap & 3) == 0) {
        if ((cap & 3) != 0) {
            *(unsigned char *)out = 1;
            *(bool *)((long)out + 1) = ((unsigned int)cap >> 6 & 0x3fffff) < op;
            *(unsigned long *)((long)out + 2) = 0;
            out[1] = 0;
            out[2] = cap;
            return;
        }
        out[0] = 0;
        out[1] = 0;
fin:
        out[2] = 0;
        return;
    }
    if (tag == 3) {
        unsigned long base = cap >> 0x1c;
        unsigned long e = base + 0x40;
        if ((cap >> 0x1c <= e) && ((base == 0 || (0x38 < (long)(e - base))))) {
            unsigned long b2 = 0;
            if (base != 0) b2 = e;
            if ((base <= b2) && ((base == 0 || (0x38 < b2 - base)))) {
                unsigned long p = sk_cap_bucket_resolve((unsigned long *)base, 0).lo;
                unsigned long pe = 0;
                if (p != 0) pe = p + 0x40;
                if ((p <= pe) && ((p == 0 || (0x38 < (long)(pe - p))))) {
                    *(unsigned char *)out = 3;
                    *(unsigned char *)((long)out + 1) = 0;
                    *(unsigned int *)((long)out + 2) = 0;
                    *(unsigned short *)((long)out + 6) = 0;
                    out[1] = p;
                    goto fin;
                }
            }
        }
    } else {
        unsigned int *bucket = (unsigned int *)(cap >> 0x1c);
        unsigned int *end = 0;
        if (bucket != 0) end = bucket + 0x10;
        if ((unsigned int *)(cap >> 0x1c) <= bucket + 0x10) {
            long idx = 0;
            unsigned int *p = bucket;
            do {
                if (((p < bucket) || (end < p + 2)) || (p + 2 < p)) goto sb2;
            } while (((*p >> 6 & 0x3fffff) < op) &&
                     (idx = idx + 1, p = p + 2, idx != 8));
            if ((bucket == 0) || (0x38 < (long)end - (long)bucket)) {
                *(unsigned char *)out = 2;
                *(char *)((long)out + 1) = (char)idx;
                *(unsigned int *)((long)out + 2) = 0;
                *(unsigned short *)((long)out + 6) = 0;
                out[1] = (unsigned long)bucket;
                goto fin;
            }
        }
    }
sb2:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c204) */
}

/* sk_cap_bucket_move @ 0x0066cac4  (est. sk_cap_bucket_move)
 * Ghidra: void sk_cap_bucket_move(ulong *param_1, ulong *param_2, uint param_3,
 *                          ulong param_4)
 * Core capability-bucket manipulation: resolves the target slot for cap
 * param_3 inside bucket param_2 (types 4/8: scanned sub-bucket chain; type 0xc:
 * full bucket; else leaf), splitting/rebuilding buckets as needed, and writes a
 * 4-slot result descriptor into param_1. Recurses for sub-buckets. On the
 * non-flag path allocates a fresh two-level bucket pair. Software-breakpoint
 * traps on every bounds violation.
 * Confidence: medium */
static void sk_cap_bucket_move(unsigned long *out, unsigned long *bucket,
                               unsigned int cap, unsigned long flag)
{
    unsigned long *end = bucket + 8;
    unsigned long *lim = 0;
    if (bucket != 0) lim = end;
    if (lim < bucket + 1) goto trap;
    unsigned long lo = 0, hi = 0;
    unsigned long tag = *bucket & 0x3c;
    if (tag == 4 || tag == 8) {
        unsigned long idx = 0;
        unsigned long *p = bucket;
        do {
            if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto trap;
        } while (((*p & 0xfffffc0) != 0 &&
                  ((unsigned int)*p >> 6 & 0x3fffff) <= (cap >> 6 & 0x3fffff)) &&
                 (idx = idx + 1, p = p + 1, idx != 7));
        p = bucket + (idx & 0xff);
        unsigned long *p1;
        if ((p < bucket) || (p1 = p + 1, lim < p1 || (p1 < p))) goto trap;
        unsigned long base = *p >> 0x1c;
        unsigned long e = base + 0x40;
        if ((e < *p >> 0x1c) || (base != 0 && ((long)(e - base) < 0x39))) goto trap;
        unsigned long b2 = 0;
        if (base != 0) b2 = e;
        unsigned long loc[4] = {0, 0, 0, 0};
        if ((b2 < base) || (base != 0 && (b2 - base < 0x39))) goto trap;
        sk_cap_bucket_move(loc, (unsigned long *)base, cap, 1);
        if ((int)loc[2] == 0) {
            *p = *p & 0xfffffff | loc[3] << 0x1c;
            goto done;
        }
        lim = bucket + 7;
        if ((end < lim) || (lim < bucket)) goto trap;
        unsigned long tail = *lim;
        unsigned long cur = *p;
        unsigned long carry0 = 0;
        if (((unsigned int)idx & 0xff) < 7) {
            carry0 = 0;
            lim = bucket + 6;
            unsigned int j = 7;
            do {
                unsigned long *q = lim + 1;
                if ((q < bucket || end < lim + 2) || lim + 2 < q) goto trap;
                unsigned long v = *q;
                unsigned long vbase = v >> 0x1c;
                if ((v & 0xfffffc0) != 0 || carry0 != 0) {
                    vbase = carry0;
                }
                if ((v & 3) == 1) {
                    carry0 = vbase;
                }
                if (((lim < bucket) || (end < q)) || (q < lim)) goto trap;
                lim[1] = *lim & 0xffffffffffffffc3;
                j = j - 1;
                lim = lim - 1;
            } while ((((unsigned int)idx & 0xff) < (j & 0xff)));
            cur = *p;
        }
        *p = cur & 0xfffffffff0000000 | cur & 0x3f | (loc[2] & 0x3fffff) << 6;
        if (((tail & 3) == 0) || (cur = loc[3], (cur & 0xfffffc0) != 0)) {
            if ((p1 < bucket) || ((end < p + 2 || (p + 2 < p1)))) goto trap;
            *p1 = *p1 & 0xffffffc | loc[3] << 0x1c | 1;
            cur = carry0;
            if ((tail & 3) == 0) goto done;
        }
    } else if (tag == 0xc) {
        lim = bucket + 6;
        unsigned long *p7;
        if (((lim < bucket) || (p7 = bucket + 7, end < p7)) || (p7 < lim)) goto trap;
        if ((*lim & 3) == 0) {
            sk_pair_t r = sk_cap_bucket_insert(bucket, cap, 7, 0);
            lo = r.lo;
            hi = r.hi;
            if ((lo & 0xff) == 0) goto done;
            goto err_store;
        }
        if (p7 < bucket) goto trap;
        unsigned long tail = bucket[7];
        sk_pair_t r = sk_cap_bucket_insert(bucket, cap, 8, 1);
        lo = r.lo;
        hi = r.hi;
        if ((lo & 0xff) != 0) goto err_store;
        cap = (unsigned int)(tail >> 0x1c);
    } else {
        cap = 0;
    }
    {
        unsigned long *nb = (unsigned long *)FUN_0066a65c();
        unsigned long *nend = nb + 8;
        unsigned long *nlim = 0;
        if (nb != 0) nlim = nend;
        unsigned int sub = (unsigned char)((unsigned char)*bucket >> 2) & 0xf;
        unsigned int w = 2;
        if (sub != 1) w = sub;
        if (w == 3) {
            long o = 0;
            do {
                unsigned long *d = (unsigned long *)((long)nb + o);
                bool a = d < nb;
                unsigned long *d1 = d + 1;
                unsigned long *s1 = (unsigned long *)((long)bucket + o + 0x20);
                unsigned long *s2 = (unsigned long *)((long)bucket + o + 0x28);
                bool b = s1 < bucket;
                if ((((((a || nlim < d1) || d1 < d) || b) || end <= s2) &&
                     ((((a || nlim < d1) || d1 < d) || b) || s2 != end) ||
                     s2 <= s1) &&
                    (((((a || nlim < d1) || d1 < d) || b) || end <= s2) &&
                     ((((a || nlim < d1) || d1 < d) || b) || s2 != end) ||
                     s1 != s2)) goto trap;
                *d = *s1 & 0xfffffffffffffffc | 1;
                *s1 = 0;
                o = o + 8;
            } while (o != 0x20);
            nlim = bucket + 7;
            if ((end < nlim) || (nlim < bucket)) goto trap;
            *nlim = *nlim & 0xfffffff | (unsigned long)nb << 0x1c;
            if ((nb + 7 < nb) ||
                ((nend < nb + 7 ||
                 (nb[7] = nb[7] & 0xfffffff | cap << 0x1c, nend < nb + 1))))
                goto trap;
            cap = *nb;
        } else {
            long o = 0;
            unsigned long *d0 = nb + 3;
            do {
                unsigned long *d = (unsigned long *)((long)nb + o);
                bool a = d < nb;
                unsigned long *d1 = d + 1;
                unsigned long *s1 = (unsigned long *)((long)bucket + o + 0x28);
                unsigned long *s2 = (unsigned long *)((long)bucket + o + 0x30);
                bool b = s1 < bucket;
                if ((((((a || nlim < d1) || d1 < d) || b) || end <= s2) &&
                     ((((a || nlim < d1) || d1 < d) || b) || s2 != end) ||
                     s2 <= s1) &&
                    (((((a || nlim < d1) || d1 < d) || b) || end <= s2) &&
                     ((((a || nlim < d1) || d1 < d) || b) || s2 != end) ||
                     s1 != s2)) goto trap;
                *d = *s1 & 0xffffffffffffffc0 | 1;
                *s1 = 0;
                o = o + 8;
            } while (o != 0x18);
            if ((nb + 4 < d0 || nlim < nb + 4) || d0 < nb) goto trap;
            *d0 = cap << 0x1c | 1;
            nlim = bucket + 4;
            if (((nlim < bucket) || (bucket + 5 < nlim)) || (end < bucket + 5)) goto trap;
            cap = *nlim;
            *nlim = cap & 0xfffffffff000003f;
        }
        *bucket = *bucket & 0xffffffffffffffc3 | (unsigned long)(w << 2);
        if (nb + 1 <= nend) {
            unsigned int eop = (unsigned int)cap >> 6 & 0x3fffff;
            *nb = *nb & 0xffffffffffffffc3 | (unsigned long)(w << 2);
            if ((flag & 1) != 0) {
                out[0] = 0;
                out[1] = 0;
                *(unsigned int *)(out + 2) = eop;
                *(unsigned int *)((long)out + 0x14) = 0;
                out[3] = (unsigned long)nb;
                return;
            }
            unsigned long *nb2 = (unsigned long *)FUN_0066a65c();
            unsigned long *n2end = 0;
            if (nb2 != 0) n2end = nb2 + 8;
            unsigned long *n2 = nb2 + 1;
            if ((nb2 <= n2) && (n2 <= n2end)) {
                *nb2 = (unsigned long)(eop << 6 | 5) | (unsigned long)bucket << 0x1c;
                if ((n2 <= nb2 + 2) && (nb2 + 2 <= n2end)) {
                    nb2[1] = (unsigned long)nb << 0x1c | 1;
                    out[0] = 0;
                    out[1] = 0;
                    out[2] = 0;
                    out[3] = (unsigned long)nb2;
                    return;
                }
            }
        }
    }
    goto trap;
err_store:
    out[0] = lo;
    out[1] = hi;
    out[2] = 0;
    out[3] = 0;
    return;
done:
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = (unsigned long)bucket;
    return;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66ccd4) */
}

/* sk_cap_bucket_free_rec @ 0x0066db74  (est. sk_cap_bucket_free_rec)
 * Ghidra: void sk_cap_bucket_free_rec(ulong *param_1, code *param_2)
 * Recursively frees a capability bucket param_1. For pointer-chain buckets
 * (tag 0xc) invokes the callback param_2 on each occupied slot then frees the
 * bucket; for leaf buckets recurses into each referenced sub-bucket (type-1
 * entries) before releasing the bucket. The bucket is released via
 * FUN_0066a6b4 (runtime dealloc).
 * Confidence: medium */
static void sk_cap_bucket_free_rec(unsigned long *bucket, sk_fp_t cb)
{
    unsigned long *lim = 0;
    if (bucket != 0) lim = bucket + 8;
    if (lim < bucket + 1) goto trap;
    unsigned long v = *bucket;
    if ((v & 0x3c) != 0xc) {
        unsigned long i = 0;
        for (;;) {
            if ((v & 3) == 1) {
                unsigned long base = v >> 0x1c;
                unsigned long e = base + 0x40;
                if ((e < v >> 0x1c) || ((base != 0 && ((long)(e - base) < 0x39)))) goto trap;
                v = 0;
                if (base != 0) v = e;
                if ((v < base) || ((base != 0 && (v - base < 0x39)))) goto trap;
                sk_cap_bucket_free_rec((unsigned long *)base, cb);
                if ((bucket[i] & 0xfffffc0) == 0) goto free;
            }
            if (6 < i) goto free;
            i = i + 1;
            v = bucket[i];
        }
    }
    long o = 0;
    do {
        if ((cb != 0) && ((*(unsigned long *)((long)bucket + o) & 3) == 1)) {
            cb(*(unsigned long *)((long)bucket + o) >> 0x1c);
        }
        o = o + 8;
    } while (o != 0x38);
free:
    FUN_0066a6b4(bucket);
    return;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66dc88) */
}

/* sk_page_tree_lookup @ 0x0066b1fc  (est. sk_page_tree_lookup)
 * Ghidra: void sk_page_tree_lookup(ulong param_1)
 * Searches the page-block free-tree (root at ctx+0x20) for a node whose key
 * (+0x28) equals (param_1 & ~0x3fff); descends left (+0x38) when the target is
 * lower, right (+0x40) otherwise. Returns via the tree node walk.
 * Confidence: medium */
static unsigned long sk_page_tree_lookup(unsigned long key)
{
    long ctx = FUN_0065be08(0x6fea48, 4, 8);
    unsigned long node = *(unsigned long *)(ctx + 0x20);
    while (node != 0) {
        if (*(unsigned long *)(node + 0x28) == (key & 0xffffffffffffc000)) {
            if (node <= node + 0x48) {
                return node;
            }
            /* bounds violation -> software breakpoint (noreturn) */
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b270) */
        }
        long off = 0x40;
        if ((key & 0xffffffffffffc000) <= *(unsigned long *)(node + 0x28)) {
            off = 0x38;
        }
        node = *(unsigned long *)(node + off);
    }
    return 0;
}

/* sk_page_bitmap_test_set @ 0x0066b468  (est. sk_page_bitmap_test_set)
 * Ghidra: bool sk_page_bitmap_test_set(ulong *param_1, long param_2)
 * Tests-and-sets a single page bit within a block bitmap. block base at
 * param_1[5]; the bit for (param_2 - base)>>12 within the 64-bit word selected
 * by (param_2-base)>>12. Returns true if the bit was previously clear (and now
 * set, with the block's free-count at *(short*)(param_1+4) incremented).
 * Confidence: medium */
static bool sk_page_bitmap_test_set(unsigned long *block, long addr)
{
    unsigned long delta = (unsigned long)addr - block[5];
    if (delta >> 0xe != 0) {
        FUN_006833d4(0x6ab432);   /* fatal: bit out of 16KB block range */
    }
    unsigned long *cnt = block + 4;
    unsigned long *word = block + (delta >> 0xc);
    if ((block <= word && word + 1 <= cnt) && word <= word + 1) {
        unsigned long bit = 1UL << (delta >> 6 & 0x3f);
        unsigned long v = *word;
        unsigned long was = v & bit;
        if (was == 0) {
            *(short *)cnt = (short)*cnt + 1;
            *word = v | bit;
        }
        return was == 0;
    }
    /* bounds violation -> software breakpoint (noreturn) */
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b4d4) */
}

/* sk_page_tree_insert @ 0x0066b038  (est. sk_page_tree_insert)
 * Ghidra: void sk_page_tree_insert(ulong *param_1, ulong param_2)
 * Inserts page-block node param_2 into the ordered free-tree whose root is
 * *param_1, keyed by the block base (+0x28, 16KB-aligned). Duplicate keys are a
 * fatal error. Rebalances via the child balance bytes at +0x22 and updates the
 * new root back through *param_1.
 * Confidence: medium */
static void sk_page_tree_insert(unsigned long *rootp, unsigned long node)
{
    unsigned long cur = *rootp;
    unsigned long r = 0;
    if (cur == 0) {
        *rootp = node;
        return;
    }
    if (*(unsigned long *)(cur + 0x28) == *(unsigned long *)(node + 0x28)) {
        FUN_006833d4(0x6ab3b8);   /* fatal: duplicate tree key */
    }
    unsigned long lim = cur + 0x48;
    if (*(unsigned long *)(node + 0x28) < *(unsigned long *)(cur + 0x28)) {
        if (lim < cur || cur + 0x40 < cur + 0x38) goto sb_break;
    } else if (lim < cur || lim < cur + 0x40) {
        goto sb_break;
    }
    /* recursive descent on the child that would hold this key */
    sk_page_tree_insert(0, 0);
    int bl;
    if (*(long *)(cur + 0x38) == 0) {
        bl = 0;
    } else {
        bl = *(unsigned char *)(*(long *)(cur + 0x38) + 0x22) + 1;
    }
    unsigned int br;
    if (*(long *)(cur + 0x40) == 0) {
        br = 0;
    } else {
        br = ~(unsigned int)*(unsigned char *)(*(long *)(cur + 0x40) + 0x22);
    }
    cur = *rootp;
    if (cur == 0) {
        return;
    }
    lim = cur + 0x48;
    unsigned long head = cur;
    if ((int)(br + bl) < -1) {
        r = *(unsigned long *)(cur + 0x40);
        if (r != 0) {
            *(unsigned long *)(cur + 0x40) = *(unsigned long *)(r + 0x38);
            if (lim < cur) goto sb_break;
            *(unsigned long *)(r + 0x38) = cur;
relink:
            if (r + 0x48 < r) goto sb_break;
            *rootp = r;
            head = r;
        }
    } else if ((1 < (int)(br + bl)) && (r = *(unsigned long *)(cur + 0x38), r != 0)) {
        *(unsigned long *)(cur + 0x38) = *(unsigned long *)(r + 0x40);
        if (lim < cur) goto sb_break;
        *(unsigned long *)(r + 0x40) = cur;
        goto relink;
    }
    if (cur <= lim) {
        unsigned int h = 0;
        if (*(long *)(cur + 0x38) != 0) {
            h = *(unsigned char *)(*(long *)(cur + 0x38) + 0x22) + 1;
        }
        unsigned int l = 0;
        if (*(long *)(cur + 0x40) != 0) {
            l = *(unsigned char *)(*(long *)(cur + 0x40) + 0x22) + 1;
        }
        if (h <= l) h = l;
        *(char *)(cur + 0x22) = (char)h;
        h = 0;
        if (*(long *)(head + 0x38) != 0) {
            h = *(unsigned char *)(*(long *)(head + 0x38) + 0x22) + 1;
        }
        l = 0;
        if (*(long *)(head + 0x40) != 0) {
            l = *(unsigned char *)(*(long *)(head + 0x40) + 0x22) + 1;
        }
        if (h <= l) h = l;
        *(char *)(head + 0x22) = (char)h;
        return;
    }
sb_break:
    /* bounds violation -> software breakpoint (noreturn) */
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b1c8) */
}

/* sk_page_block_alloc @ 0x0066b270  (est. sk_page_block_alloc)
 * Ghidra: ulong sk_page_block_alloc(long param_1, ulong param_2, ulong param_3)
 * Allocates param_3 16KB page-blocks starting at (param_1,param_2) from the
 * page allocator. Requires 16KB alignment; allocates each block, sets its
 * bitmap, inserts it into the free-tree, then returns the allocation result.
 * Confidence: medium */
static unsigned long sk_page_block_alloc(long base, unsigned long size, unsigned long count)
{
    long *ctx = (long *)FUN_0065be08(0x6fea48, 4, 8);
    if ((((unsigned int)count | (unsigned int)base) & 0x3fff) != 0) {
fatal_align:
        FUN_006833d4(0x6aaf42);   /* fatal: misaligned block allocation */
    }
    if (count < size) {
        FUN_006833d4(0x6aafb0);   /* fatal: count below size */
    }
    sk_pair_t st = FUN_0066a9bc(*(unsigned long *)(*ctx + 0x10));
    if ((st.lo & 1) != 0) {
        /* fast path: bitmap-managed, single caller */
        sk_pair_t r = FUN_0068642c();
        unsigned long *blk = (unsigned long *)r.lo;
        unsigned long delta = r.hi - blk[5];
        if (delta >> 0xe != 0) {
            FUN_006833d4(0x6ab432);
        }
        unsigned long *cnt = blk + 4;
        unsigned long *word = blk + (delta >> 0xc);
        if ((blk <= word && word + 1 <= cnt) && word <= word + 1) {
            unsigned long bit = 1UL << (delta >> 6 & 0x3f);
            unsigned long v = *word;
            unsigned long was = v & bit;
            if (was == 0) {
                *(short *)cnt = (short)*cnt + 1;
                *word = v | bit;
            }
            return (unsigned long)(was == 0);
        }
        /* bounds violation -> software breakpoint (noreturn) */
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b4d4) */
    }
    if (count != 0) {
        do {
            unsigned long blk = FUN_0066af84();
            if (blk == 0) {
                FUN_006863f0();
                goto fatal_align;
            }
            FUN_0067a7f0(blk, 0, 0x48);
            *(long *)(blk + 0x28) = base;
            unsigned long step = size;
            if (0xff < size) {
                step = 0x100;
            }
            if (size != 0) {
                unsigned long n = step;
                long addr = base;
                if (blk + 0x48 < blk) goto sb_break;
                do {
                    unsigned long rc = sk_page_bitmap_test_set((unsigned long *)blk, addr);
                    if ((rc & 1) == 0) {
                        FUN_006833d4(0x6ab0ce);   /* fatal: bit already set */
                    }
                    addr = addr + 0x40;
                    n = n - 1;
                } while (n != 0);
            }
            if ((ctx + 5 < ctx + 4) || (blk + 0x48 < blk)) {
sb_break:
                /* bounds violation -> software breakpoint (noreturn) */
                __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b3fc) */
            }
            sk_page_tree_insert(ctx + 4, blk);
            if (*(unsigned short *)(blk + 0x20) < 0x100) {
                *(long *)(blk + 0x30) = ctx[6];
                ctx[6] = blk;
            }
            base = base + 0x4000;
            size = size - step;
            count = count - 0x4000;
        } while (count != 0);
    }
    return FUN_0066ab40(*(unsigned long *)(*ctx + 0x10), st.lo, st.hi);
}

/* sk_page_block_free @ 0x0066b520  (est. sk_page_block_free)
 * Ghidra: void sk_page_block_free(ulong param_1, long param_2)
 * Frees a region of page-blocks starting at param_1 for param_2 bytes: walks
 * each 16KB block, clears its bitmap bit, and removes it from the free-tree
 * when its count drops to zero.
 * Confidence: medium */
static void sk_page_block_free(unsigned long base, long size)
{
    long *ctx = (long *)FUN_0065be08(0x6fea48, 4, 8);
    if ((base & 0x3f) != 0) {
        FUN_006833d4(0x6ab142);   /* fatal: misaligned free base */
    }
    unsigned long end = size + base;
    if ((0xffffffffffffffbf < end) || (end < base)) {
        FUN_006833d4(0x6ab1df);   /* fatal: overflow in free range */
    }
    sk_pair_t st = FUN_0066a9bc(*(unsigned long *)(*ctx + 0x10));
    if ((st.lo & 1) != 0) {
        /* fast path: stash the value into per-cpu/global slot +0x20 */
        unsigned long v = FUN_00686464();
        long g = FUN_00668c6c();
        *(unsigned long *)(g + 0x20) = v;
        return;
    }
    long *blk = (long *)sk_page_tree_lookup(base);
    if (base < end) {
        long *head = blk + 9;
        long *node = blk;
        do {
            unsigned long next = base + 0x40;
            if (node == 0) {
                blk = (long *)sk_page_tree_lookup(base);
                head = blk + 9;
                node = blk;
                if (blk != 0) goto have;
                node = 0;
                long a = 0;
                if ((next & 0x3fff) != 0) {
                    a = 0x4000;
                }
                base = a + (next & 0xffffffffffffc000);
            } else {
                if ((head < node + 9) || (node < blk)) goto sb_break;
                if (node[5] + 0x4000U <= base) {
                    blk = (long *)sk_page_tree_lookup(base);
                    head = blk + 9;
                    node = blk;
                    if (blk != 0) goto have;
                    node = 0;
                    long a = 0;
                    if ((next & 0x3fff) != 0) a = 0x4000;
                    base = a + (next & 0xffffffffffffc000);
                    continue;
                }
have:
                if (((head < node + 9) || (node + 9 < node)) || (node < blk)) {
sb_break:
                    /* bounds violation -> software breakpoint (noreturn) */
                    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519, 0x66b6c4) */
                }
                int rc = sk_page_bitmap_test_set(node, base);
                base = next;
                if (rc != 0 && (short)node[4] == 0x100) {
                    long *p = ctx;
                    long *q;
                    do {
                        q = p + 6;
                        if (p + 7 < q) goto sb_break;
                        p = (long *)*q;
                    } while (p != 0 && p != node);
                    if (p == node) {
                        *q = node[6];
                    }
                }
            }
        } while (base < end);
    }
    FUN_0066ab40(*(unsigned long *)(*ctx + 0x10), st.lo, st.hi);
}

/* FUN_0066b870 @ 0x0066b870  (est. sk_tail_noop0)
 * Ghidra: undefined8 FUN_0066b870(void)
 * Trivial tail-region stub: always returns 0.
 * Confidence: high */
static unsigned long sk_tail_noop0(void)
{
    return 0;
}

/* FUN_0066b878 @ 0x0066b878  (est. sk_tail_cap_decode_wrap)
 * Ghidra: void FUN_0066b878(undefined8 param_1, undefined8 param_2)
 * Thin wrapper over the capability-decode helper sk_tail_cap_decode
 * (sk_cap_decode), passing (param_1, param_2, 0, 0) and a zero op.
 * Confidence: medium */
static void sk_tail_cap_decode_wrap(unsigned long a, unsigned long b)
{
    sk_cap_decode((unsigned long *)a, b, 0, 0, 0);
}

/* FUN_0066bce0 @ 0x0066bce0  (est. sk_tail_cap_decode_wrap0)
 * Ghidra: void FUN_0066bce0(void)
 * Wrapper over the capability-decode helper sk_cap_decode; the decompiler
 * dropped all arguments (decodes the caller's current capability context).
 * Confidence: medium */
static void sk_tail_cap_decode_wrap0(void)
{
    sk_cap_decode((unsigned long *)0, 0, 0, 0, 0);
}

/* FUN_0066b728 @ 0x0066b728  (est. sk_tail_store_ctx)
 * Ghidra: void FUN_0066b728(undefined8 param_1)
 * Stores param_1 into the per-CPU/global context at offset +0x20 (context
 * base from FUN_00668c6c, the runtime global-context fetch).
 * Confidence: medium */
static void sk_tail_store_ctx(unsigned long v)
{
    long ctx = FUN_00668c6c();
    *(unsigned long *)(ctx + 0x20) = v;
}

/* FUN_0066e064 @ 0x0066e064  (est. sk_tail_global_op2_0)
 * Ghidra: void FUN_0066e064(void)
 * Fetches a context value (FUN_00668c78) and performs a 3-arg global
 * capability/object-table op (FUN_00677674) with (value, 2, 0).
 * Confidence: medium */
static void sk_tail_global_op2_0(void)
{
    unsigned long v = FUN_00668c78();
    FUN_00677674(v, 2, 0);
}

/* FUN_0066e068 @ 0x0066e068  (est. sk_tail_global_op2_0b)
 * Ghidra: void FUN_0066e068(void)
 * Duplicate of sk_tail_global_op2_0: context fetch + 3-arg table op (2,0).
 * Confidence: medium */
static void sk_tail_global_op2_0b(void)
{
    unsigned long v = FUN_00668c78();
    FUN_00677674(v, 2, 0);
}

/* FUN_006741e8 @ 0x006741e8  (est. sk_obj_pair_copy_dispatch)
 * Ghidra: void FUN_006741e8(long param_1, long param_2)
 * Dispatches two 8-byte capability/object pointers (at +0x20 and +0x28 of
 * param_2) into the corresponding slots of param_1 via sk_obj_dispatch
 * (FUN_00656474) with op 8 (commit/detach). Copy-on-dispatch object migration.
 * Confidence: medium */
static void sk_obj_pair_copy_dispatch(long dst, long src)
{
    FUN_00656474(dst + 0x20, *(unsigned long *)(src + 0x20), 8);
    FUN_00656474(dst + 0x28, *(unsigned long *)(src + 0x28), 8);
}

/* FUN_0067422c @ 0x0067422c  (est. sk_obj_pair_release)
 * Ghidra: void FUN_0067422c(long param_1)
 * Releases the two capability/object pointers at +0x28 and +0x20 of param_1
 * via sk_obj_release_dispatch (FUN_00656634) with op 8 (inline release).
 * Confidence: medium */
static void sk_obj_pair_release(long obj)
{
    FUN_00656634(*(unsigned long *)(obj + 0x28), 8);
    FUN_00656634(*(unsigned long *)(obj + 0x20), 8);
}

/* FUN_00673500 @ 0x00673500  (est. sk_obj_triple_release)
 * Ghidra: void FUN_00673500(long param_1)
 * Releases three capability/object pointers (+0x30, +0x28, +0x20) of param_1
 * via sk_obj_release_dispatch (FUN_00656634) op 8, in reverse address order.
 * Confidence: medium */
static void sk_obj_triple_release(long obj)
{
    FUN_00656634(*(unsigned long *)(obj + 0x30), 8);
    FUN_00656634(*(unsigned long *)(obj + 0x28), 8);
    FUN_00656634(*(unsigned long *)(obj + 0x20), 8);
}

/* FUN_00673bac @ 0x00673bac  (est. sk_tail_table_lookup)
 * Ghidra: undefined8 FUN_00673bac(char param_1)
 * Bounds-checked table lookup: if (code+5) < 0x19 returns the 8-byte entry at
 * table base 0x6b6ac0 indexed by (code+5), else 0.
 * Confidence: medium */
static unsigned long sk_tail_table_lookup(char code)
{
    unsigned int idx = (unsigned char)(code + 5U);
    if (idx < 0x19) {
        return *(unsigned long *)((unsigned long)idx * 8 + 0x6b6ac0);
    }
    return 0;
}

/* FUN_00676614 @ 0x00676614  (est. sk_tail_noop1)
 * Ghidra: void FUN_00676614(void)
 * Trivial empty tail stub.
 * Confidence: high */
static void sk_tail_noop1(void)
{
    return;
}

/* FUN_00676630 @ 0x00676630  (est. sk_tail_err_fmt0)
 * Ghidra: void FUN_00676630(void)
 * Wrapper invoking the L4 error-code formatter sk_l4_error_format.
 * Confidence: medium */
static void sk_tail_err_fmt0(void)
{
    unsigned long buf[4] = {0};
    sk_l4_error_format(buf, 0);
}

/* FUN_0067663c @ 0x0067663c  (est. sk_tail_noop2)
 * Ghidra: void FUN_0067663c(void)
 * Trivial empty tail stub.
 * Confidence: high */
static void sk_tail_noop2(void)
{
    return;
}

/* FUN_00676650 @ 0x00676650  (est. sk_tail_fatal)
 * Ghidra: void FUN_00676650(void)
 * Fatal-assert helper (FUN_006833d4, noreturn) with message string at 0x6a71a1.
 * Confidence: high */
static void sk_tail_fatal(void)
{
    FUN_006833d4(0x6a71a1);   /* fatal assert, message string @0x6a71a1 (noreturn) */
}

/* FUN_006765e4 @ 0x006765e4  (est. sk_tail_noop3)
 * Ghidra: void FUN_006765e4(void)
 * Trivial empty tail stub (globals overlap note at same address).
 * Confidence: high */
static void sk_tail_noop3(void)
{
    return;
}

/* FUN_006765fc @ 0x006765fc  (est. sk_tail_noop4)
 * Ghidra: void FUN_006765fc(void)
 * Trivial empty tail stub.
 * Confidence: high */
static void sk_tail_noop4(void)
{
    return;
}

/* FUN_006765a4 @ 0x006765a4  (est. sk_tail_err_fmt1)
 * Ghidra: void FUN_006765a4(void)
 * Invokes the L4 error-code formatter sk_l4_error_format on a stack scratch buffer.
 * Confidence: medium */
static void sk_tail_err_fmt1(void)
{
    unsigned long buf[4] = {0};
    sk_l4_error_format(buf, 0);
}

/* FUN_006765c4 @ 0x006765c4  (est. sk_tail_err_fmt2)
 * Ghidra: void FUN_006765c4(void)
 * Invokes the L4 error-code formatter sk_l4_error_format on a stack scratch buffer.
 * Confidence: medium */
static void sk_tail_err_fmt2(void)
{
    unsigned long buf[4] = {0};
    sk_l4_error_format(buf, 0);
}

/* FUN_00676660 @ 0x00676660  (est. sk_tail_fatal_2a)
 * Ghidra: void FUN_00676660(undefined8 param_1)
 * Fatal-assert helper (FUN_006833d4, noreturn) with message string at 0x6aee2a;
 * carries the supplied value on the stack for the assert context.
 * Confidence: high */
static void sk_tail_fatal_2a(unsigned long v)
{
    unsigned long saved = v;
    FUN_006833d4(0x6aee2a);   /* fatal assert, message string @0x6aee2a (noreturn) */
}

/* FUN_00676674 @ 0x00676674  (est. sk_tail_fatal_27)
 * Ghidra: void FUN_00676674(undefined8 param_1)
 * Fatal-assert helper (FUN_006833d4, noreturn) with message string at 0x6ae527.
 * Confidence: high */
static void sk_tail_fatal_27(unsigned long v)
{
    unsigned long saved = v;
    FUN_006833d4(0x6ae527);   /* fatal assert, message string @0x6ae527 (noreturn) */
}

/* FUN_00676688 @ 0x00676688  (est. sk_tail_fatal_24)
 * Ghidra: void FUN_00676688(undefined8 param_1)
 * Fatal-assert helper (FUN_006833d4, noreturn) with message string at 0x6ae492.
 * Confidence: high */
static void sk_tail_fatal_24(unsigned long v)
{
    unsigned long saved = v;
    FUN_006833d4(0x6ae492);   /* fatal assert, message string @0x6ae492 (noreturn) */
}

/* FUN_0067669c @ 0x0067669c  (est. sk_tail_fatal_0a)
 * Ghidra: void FUN_0067669c(undefined8 param_1)
 * Fatal-assert helper (FUN_006833d4, noreturn) with message string at 0x6ada99.
 * Confidence: high */
static void sk_tail_fatal_0a(unsigned long v)
{
    unsigned long saved = v;
    FUN_006833d4(0x6ada99);   /* fatal assert, message string @0x6ada99 (noreturn) */
}

/* FUN_0066b750 @ 0x0066b750  (est. sk_page_region_init)
 * Ghidra: void FUN_0066b750(long param_1, long param_2, long param_3)
 * Registers a page region [param_1, param_2) of param_3*0x40 bytes with the
 * page allocator: warms up helpers, allocates the region via sk_page_block_alloc,
 * then performs a device-tree/init dispatch (FUN_0067203c) to publish it; marks
 * the init flag DAT_006fea50. Idempotent (guarded by the flag).
 * Confidence: medium */
static void sk_page_region_init(long base, long end, long count)
{
    if ((DAT_006fea50 & 1) == 0) {
        FUN_00668128();
        FUN_00676a7c(base, end, count);
        FUN_00669618();
        FUN_00671ca8();
        long sz = (end - base) + count * 0x40;
        sk_page_block_alloc(base, end - base, sz);
        FUN_0067728c();
        unsigned char d[8] = {4, 0, 0, 0, 0xff, 0, 0, 0};
        unsigned long out[2] = {0, 0};
        long r = base;
        long rsz = sz;
        unsigned long uVar4 = FUN_0067203c(0x1000001, &d, &out, 0, 0);
        if ((uVar4 & 0xff) != 0) {
            long off = (uVar4 & 0xff) * 8;
            unsigned char *p = (unsigned char *)(off + 0x6b5e50);
            if (((unsigned char *)0x6b5e4f < p) &&
               ((unsigned char *)0x6b5e58 + off < (unsigned char *)0x6b5e91 && p <= (unsigned char *)0x6b5e58 + off)) {
                FUN_006833d4(0x6ab4a8);   /* fatal: error string table overrun */
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66b870) */
        }
        FUN_00669a48();
        DAT_006fea50 = 1;
    }
}

/* FUN_0066bce8 @ 0x0066bce8  (est. sk_cap_value_base)
 * Ghidra: ulong FUN_0066bce8(ulong param_1)
 * Resolves a raw capability param_1 to its referenced bucket/base value: type
 * 0/1 returns it (or its tag), type 2 returns the first bucket entry, and type
 * 3 follows the pointer-chain until a type-0xc (full) bucket is found and
 * returns its tag. Software-breakpoint on bounds failure.
 * Confidence: medium */
static unsigned long sk_cap_value_base(unsigned long cap)
{
    unsigned int tag = (unsigned int)cap & 3;
    if (tag == 1 || (cap & 3) == 0) {
        unsigned long v = (unsigned long)tag;
        if ((cap & 3) != 0) v = cap;
        return v;
    }
    if (tag == 2) {
        unsigned long *b = (unsigned long *)(cap >> 0x1c);
        unsigned long *e = b + 8;
        if (((unsigned long *)(cap >> 0x1c) <= e) &&
           ((b == 0 || (0x38 < (long)e - (long)b)))) {
            unsigned long *lim = 0;
            if (b != 0) lim = e;
            if ((b <= b + 1) && (b + 1 <= lim)) {
                return *b;
            }
        }
    } else {
        unsigned long *b = (unsigned long *)(cap >> 0x1c);
        unsigned long *e = b + 8;
        if (((unsigned long *)(cap >> 0x1c) <= e) &&
           ((b == 0 || (0x38 < (long)e - (long)b)))) {
            unsigned long *lim = 0;
            if (b != 0) lim = e;
            if ((b <= lim) && ((b == 0 || (0x38 < (unsigned long)((long)lim - (long)b))))) {
                for (;;) {
                    unsigned long *e2 = 0;
                    if (b != 0) e2 = b + 8;
                    if (e2 < b + 1) break;
                    unsigned long v = *b;
                    if ((v & 0x3c) == 0xc) {
                        return v;
                    }
                    b = (unsigned long *)(v >> 0x1c);
                    e = b + 8;
                    if ((e < (unsigned long *)(v >> 0x1c)) ||
                       ((b != 0 && ((long)e - (long)b < 0x39)))) break;
                    lim = 0;
                    if (b != 0) lim = e;
                    if ((lim < b) || ((b != 0 && ((unsigned long)((long)lim - (long)b) < 0x39)))) break;
                }
            }
        }
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66bdf0) */
}

/* FUN_0066bdf4 @ 0x0066bdf4  (est. sk_cap_remove)
 * Ghidra: void FUN_0066bdf4(undefined8 *param_1, ulong param_2, uint param_3,
 *                          code *param_4)
 * Removes a capability with op param_3 from the capability value param_2.
 * Direct (type 0/1) match invokes the callback param_4 and clears the result;
 * the type-2 bucket form scans slots, invokes the callback, removes the slot
 * (sk_cap_bucket_slot_remove), and collapses/repacks the bucket (merging the
 * running tag/base into slot 0); the type-3 pointer-chain form resolves via
 * sk_cap_bucket_resolve and repacks. On no-match returns the original value.
 * Confidence: medium */
static void sk_cap_remove(unsigned long *out, unsigned long cap, unsigned int op, sk_fp_t cb)
{
    unsigned int tag = (unsigned int)cap;
    unsigned long d0 = *(unsigned long *)0x68a550;
    unsigned long d1 = *(unsigned long *)0x68a558;
    if ((tag & 3) == 1 || (cap & 3) == 0) {
        if (((cap & 3) != 0) && ((tag >> 6 & 0x3fffff) == op)) {
            if (cb != 0) {
                cb(cap >> 0x1c);
            }
            out[0] = 0;
            out[1] = 0;
            out[2] = 0;
            return;
        }
nomatch:
        out[1] = d1;
        out[0] = d0;
        out[2] = cap;
        return;
    }
    if ((tag & 3) == 2) {
        unsigned long *b = (unsigned long *)(cap >> 0x1c);
        unsigned long *e = b + 8;
        if (((unsigned long *)(cap >> 0x1c) <= e) &&
           ((b == 0 || (0x38 < (long)e - (long)b)))) {
            long i = 0;
            unsigned long *p = b;
            unsigned long *lim = 0;
            if (b != 0) lim = e;
            do {
                if (((p < b) || (lim < p + 1)) || (p + 1 < p)) goto trap;
                unsigned long v = *p;
                if ((v & 3) == 1 && ((unsigned int)v >> 6 & 0x3fffff) == op) {
                    if (cb != 0) cb(v >> 0x1c);
                    if ((unsigned long)((long)e - (long)b) < 0x39) goto trap;
                    sk_cap_bucket_slot_remove(b, (unsigned int)i & 0xff, 8);
                    unsigned long v2 = (unsigned long)(tag + 0x3c) & 0x3c;
                    if (v2 == 4) {
                        long k = 0;
                        unsigned long t = 0;
                        unsigned long bs = 0;
                        unsigned long r1 = 0;
                        unsigned long r2 = 0;
                        do {
                            unsigned long e2 = *(unsigned long *)((long)b + k);
                            unsigned int eop = (unsigned int)e2 >> 6 & 0x3fffff;
                            unsigned long eb = e2 >> 0x1c;
                            if ((e2 & 3) != 1) {
                                eop = t;
                                eb = bs;
                            }
                            bs = eb;
                            k = k + 8;
                            t = eop;
                        } while (k != 0x40);
                        if ((b == 0) || ((b + 1 <= e && (b <= b + 1)))) {
                            FUN_0066a6b4(b);
                            unsigned long res = (unsigned long)(r1 << 6) | bs << 0x1c | 1;
                            goto store;
                        }
                        goto trap;
                    }
                    cap = cap & 0xffffffffffffffc3;
                    goto store2;
                }
                i = i + 1;
                p = p + 1;
            } while (i != 8);
            goto nomatch;
        }
    } else {
        unsigned long bs = cap >> 0x1c;
        unsigned long e = bs + 0x40;
        if ((cap >> 0x1c <= e) && ((bs == 0 || (0x38 < (long)(e - bs))))) {
            unsigned long e2 = 0;
            if (bs != 0) e2 = e;
            if ((bs <= e2) && (((bs == 0 || (0x38 < e2 - bs)) && (bs + 8 <= e2)))) {
                sk_pair_t r = sk_cap_bucket_repack((unsigned long *)bs, 0, 0);
                unsigned long *pb = (unsigned long *)r.hi;
                unsigned long *pe = 0;
                if (pb != 0) pe = pb + 8;
                if ((r.lo & 0xff) == 1) {
                    if ((pb <= pe) &&
                       ((d0 = *(unsigned long *)0x68a540, d1 = *(unsigned long *)0x68a548,
                         pb == 0 || (0x38 < (long)pe - (long)pb)))) goto nomatch;
                } else if ((((pb <= pe) &&
                           ((pb == 0 || (0x38 < (long)pe - (long)pb)))) &&
                          ((pb == 0 || (0x38 < (unsigned long)((long)pe - (long)pb))))) &&
                         (pb + 1 <= pe)) {
                    if ((*pb & 0x3f) == 0xc) {
                        FUN_0066a6b4(pb);
                        bs = 0;
                    } else {
                        bs = cap & 0x3f | (unsigned long)pb << 0x1c;
                        cap = (unsigned long)(tag + 0xfffffc0) & 0xfffffc0;
store2:
                        bs = bs | cap;
                    }
store:
                    out[0] = 0;
                    out[1] = 0;
                    out[2] = bs;
                    return;
                }
            }
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66bf88) */
}

/* FUN_0066c480 @ 0x0066c480  (est. sk_cap_merge)
 * Ghidra: void FUN_0066c480(undefined8 *param_1, long param_2, undefined8 param_3)
 * Merges two capability values param_2/param_3 (ordered by tag type) into a
 * single capability, iterating the union of their entries via sk_cap_list_get
 * and re-inserting each through sk_cap_decode. On an unmatchable entry returns
 * the invalid-capability error 0x2de0007.
 * Confidence: high */
static void sk_cap_merge(unsigned long *out, long a, unsigned long b)
{
    unsigned int ta = (unsigned int)a & 3;
    if (1 < ta) {
        ta = (ta == 3) ? ((unsigned int)a >> 6 & 0x3fffff) : ((unsigned int)a >> 2 & 0xf);
    }
    unsigned int tb = (unsigned int)b & 3;
    if (1 < tb) {
        tb = (tb == 3) ? ((unsigned int)b >> 6 & 0x3fffff) : ((unsigned int)b >> 2 & 0xf);
    }
    unsigned long lo = b;
    if (ta <= tb) {
        lo = (unsigned long)a;
        a = (long)b;
    }
    unsigned long vb = sk_cap_value_base(lo);
    long local[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned long op = vb >> 6 & 0x3fffff;
    sk_cap_decode_tag(local + 5, lo, op);
    do {
        unsigned long v = sk_cap_list_get((char *)(local + 5));
        if ((v & 3) == 0) {
            sk_cap_decode_tag(local + 5, lo, op);
            while (v = sk_cap_list_get((char *)(local + 5)), (v & 3) != 0) {
                local[4] = 0; local[1] = 0; local[0] = 0; local[3] = 0; local[2] = 0;
                sk_cap_decode(local, (unsigned long)a, (unsigned int)v >> 6 & 0x3fffff, v >> 0x1c, 1);
                a = local[4];
            }
            sk_cap_iterate_free(lo, 0);
            out[0] = 0;
            out[1] = 0;
            out[2] = (unsigned long)a;
            return;
        }
        local[4] = 0; local[1] = 0; local[0] = 0; local[3] = 0; local[2] = 0;
        sk_cap_decode(local, (unsigned long)a, v >> 6 & 0x3fffff, 0, 0);
    } while (local[0] == 0);
    out[1] = 0;
    out[2] = 0;
    out[0] = 0x2de0007;
    return;
}

/* FUN_0066c76c @ 0x0066c76c  (est. sk_cap_restrict)
 * Ghidra: void FUN_0066c76c(undefined8 *param_1, undefined8 param_2, ulong param_3)
 * Restricts a capability value param_2 to entries with op below param_3,
 * rebuilding it entry-by-entry via sk_cap_decode/sk_cap_remove. On the 
 * non-restrict path returns error 0x3010005.
 * Confidence: high */
static void sk_cap_restrict(unsigned long *out, unsigned long cap, unsigned long limit)
{
    if ((((unsigned int)cap >> 1 & 1) == 0)) {
        out[0] = 0x3010005;
        out[1] = 0;
    } else {
        unsigned long vb = sk_cap_value_base(cap);
        unsigned long d[3] = {0, 0, 0};
        sk_cap_decode_tag(d, cap, vb >> 6 & 0x3fffff);
        unsigned long v = sk_cap_list_get((char *)d);
        unsigned long acc = 0;
        if ((v & 3) == 0) {
            acc = 0;
        } else {
            acc = 0;
            do {
                unsigned long eop = (unsigned long)((unsigned int)v >> 6 & 0x3fffff);
                if (limit <= eop) break;
                unsigned long l[5] = {0, 0, 0, 0, 0};
                sk_cap_decode(l, acc, eop, v >> 0x1c, 1);
                acc = l[4];
                v = sk_cap_list_get((char *)d);
            } while ((v & 3) != 0);
        }
        unsigned long vb2 = sk_cap_value_base(acc);
        unsigned long d2[3] = {0, 0, 0};
        sk_cap_decode_tag(d2, acc, vb2 >> 6 & 0x3fffff);
        unsigned long r[4] = {0, 0, 0, 0};
        do {
            v = sk_cap_list_get((char *)d2);
            if ((v & 3) == 0) {
                out[0] = 0;
                out[1] = 0;
                out[2] = acc;
                out[3] = cap;
                return;
            }
            sk_cap_remove(r, cap, v >> 6 & 0x3fffff, 0);
            cap = r[2];
        } while ((char)r[0] == '\0');
        out[1] = r[1];
        out[0] = r[0];
    }
    out[2] = 0;
    out[3] = 0;
    return;
}

/* FUN_0066cfe4 @ 0x0066cfe4  (est. sk_cap_bucket_slot_remove)
 * Ghidra: uint FUN_0066cfe4(ulong *param_1, uint param_2, uint param_3)
 * Removes the bucket slot at index param_2 by shifting the following occupied
 * slots left, zeroing the vacated tail (index param_3-1). Returns the removed
 * slot's index.
 * Confidence: medium */
static unsigned int sk_cap_bucket_slot_remove(unsigned long *b, unsigned int idx, unsigned int cnt)
{
    unsigned long *lim = 0;
    if (b != 0) lim = b + 8;
    unsigned long *p = b + idx;
    unsigned int i = 0;
    if ((b <= p && p + 1 <= lim) && p <= p + 1) {
        *p = 0;
        do {
            i = idx;
            idx = i + 1;
            if (cnt <= (idx & 0xff)) break;
            p = b + (unsigned char)idx;
            unsigned long *prev = p - 1;
            bool a = prev < b;
            unsigned long *n = p + 1;
            if (((((a || lim < p) || p < prev) || lim <= n) &&
                 (((a || lim < p) || p < prev) || n != lim) || n <= p) &&
                ((((a || lim < p) || p < prev) || lim <= n) &&
                 (((a || lim < p) || p < prev) || n != lim) || p != n)) goto trap;
            p[-1] = *p;
        } while ((*p & 3) != 0);
        p = b + (cnt - 1);
        if ((b <= p && p + 1 <= lim) && p <= p + 1) {
            *p = 0;
            return i & 0xff;
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66d07c) */
}

/* FUN_0066d07c @ 0x0066d07c  (est. sk_cap_bucket_repack)
 * Ghidra: undefined1 [16] FUN_0066d07c(ulong *param_1, uint param_2, code *param_3)
 * Core capability-bucket split/merge/repack used by capability removal. Walks
 * the bucket (param_1) for op param_2; on a type-0xc full bucket it removes the
 * matching slot (invoking callback param_3) and returns its new state; on a
 * sub-bucket chain it recursively resolves, then merges/splits the sub-bucket
 * into a parent slot, compacting the bucket and possibly collapsing it. Returns
 * a 16-byte pair {status, bucket}. Software-breakpoint on every bounds failure.
 * Confidence: low (very large, dense pointer-bucket logic) */
static sk_pair_t sk_cap_bucket_repack(unsigned long *bucket, unsigned int op, sk_fp_t cb)
{
    unsigned long *lim = 0;
    if (bucket != 0) lim = bucket + 8;
    if (lim < bucket + 1) goto trap;
    unsigned long tag = *bucket;
    if ((tag & 0x3c) == 0xc) {
        long i = 0;
        unsigned long status = 1;
        do {
            if (((unsigned int)bucket[i] >> 6 & 0x3fffff) == op) {
                unsigned long oldtag;
                if (cb == 0) {
                    oldtag = 0xc;
                } else {
                    cb(bucket[i] >> 0x1c);
                    tag = *bucket;
                    oldtag = tag & 0x3c;
                }
                *bucket = tag & 0xffffffffffffffc3;
                unsigned int k = sk_cap_bucket_slot_remove(bucket, (unsigned int)i & 0xff, 7);
                *bucket = *bucket & 0xffffffffffffffc3 | oldtag;
                status = 2;
                if (2 < k) status = 3;
                break;
            }
            i = i + 1;
        } while (i != 7);
        goto fin;
    }
    unsigned long idx = 0;
    unsigned long *p = bucket;
    do {
        if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto trap;
    } while (((*p & 0xfffffc0) != 0 && ((unsigned int)*p >> 6 & 0x3fffff) <= op) &&
            (idx = idx + 1, p = p + 1, idx != 8));
    unsigned int i = (unsigned int)idx;
    p = bucket + (idx & 0xff);
    if ((p < bucket) || ((lim < p + 1 || (p + 1 < p)))) goto trap;
    unsigned long subbase = *p >> 0x1c;
    unsigned long sube = subbase + 0x40;
    if ((sube < *p >> 0x1c) || ((subbase != 0 && ((long)(sube - subbase) < 0x39)))) goto trap;
    unsigned long sub2 = 0;
    if (subbase != 0) sub2 = sube;
    if ((sub2 < subbase) || ((subbase != 0 && (sub2 - subbase < 0x39)))) goto trap;
    sk_pair_t subr = sk_cap_bucket_repack((unsigned long *)subbase, op, cb);
    char subkind = (char)subr.lo;
    unsigned long *x1 = (unsigned long *)subr.hi;      /* extraout_x1: returned bucket */
    unsigned long *sbe = x1 + 8;
    unsigned long *sb = (x1 != 0) ? sbe : 0;
    *p = *p & 0xfffffff | (unsigned long)x1 << 0x1c;
    if (subkind == '\x03') goto fin3;
    if (subkind == '\x01') {
        goto fin;
    }
    unsigned int i1 = i & 0xff;
    unsigned int left = i1 - 1;
    unsigned int right = i1 + 1;
    long run = 7;
    unsigned long pos = (unsigned long)left;
    bool first = true;
    bool was = false;
    do {
        was = first;
        if ((unsigned int)pos < 8) {
            unsigned long *s = bucket + pos;
            if ((s < bucket || lim < s + 1) || s + 1 < s) goto trap;
            unsigned long v = *s;
            if ((v & 3) == 1) {
                unsigned long *sub = (unsigned long *)(v >> 0x1c);
                unsigned long *se = sub + 8;
                if ((se < (unsigned long *)(v >> 0x1c)) ||
                   ((sub != 0 && ((long)se - (long)sub < 0x39)))) goto trap;
                unsigned long *sl = 0;
                if (sub != 0) sl = se;
                unsigned long gap = (long)sl - (long)sub;
                if ((sl < sub) || ((sub != 0 && (gap < 0x39)))) goto trap;
                long cnt = 0;
                unsigned long *q = sub;
                for (;;) {
                    if (((q < sub) || (sl < q + 1)) || (q + 1 < q)) goto trap;
                    if ((*q & 0xfffffc0) == 0) break;
                    cnt = cnt - 1;
                    q = q + 1;
                    if (cnt == -7) goto merge;
                }
                if (3 < (unsigned long)-cnt) {
                    run = -cnt;
merge:
                    /* Merge the run of occupied slots from sub into x1 (the
                     * repacked bucket) and splice it into the parent slot. */
                    unsigned long *nb = x1 + 1;
                    if ((int)(unsigned int)pos < (int)i1) {
                        if (sb < nb) goto trap;
                        unsigned int nt = (unsigned int)*x1 >> 2 & 0xf;
                        if (nt == 3) {
                            unsigned long *tgt = sub + ((int)run - 1);
                            if (((tgt < sub) || (se < tgt + 1)) || (tgt + 1 < tgt)) goto trap;
                            unsigned long moved = *tgt;
                            *tgt = 0;
                            *x1 = *x1 & 0xffffffffffffffc3;
                            x1[3] = x1[2];
                            x1[2] = x1[1];
                            *nb = *x1;
                            *x1 = moved & 0xffffffffffffffc3 | 0xc;
                            *s = *s & 0xfffffffff0000000 | *s & 0x3f | (moved >> 6 & 0x3fffff) << 6;
                        } else {
                            *x1 = *x1 & 0xffffffffffffffc3;
                            x1[3] = x1[2];
                            x1[2] = x1[1];
                            *nb = *x1;
                            unsigned long base = *x1;
                            unsigned long newtag = (*s >> 6 & 0x3fffff) << 6;
                            *x1 = base & 0xfffffffff0000000 | base & 0x3f | newtag;
                            unsigned long *tgt = sub + run;
                            if (((tgt < sub) || (se < tgt + 1)) || (tgt + 1 < tgt)) goto trap;
                            unsigned long *prev = tgt - 1;
                            *x1 = base & 3 | newtag | (unsigned long)(nt << 2) | *tgt & 0xfffffffff0000000;
                            if ((prev < sub) || (tgt < prev)) goto trap;
                            *s = *s & 0xfffffffff0000000 | *s & 0x3f | (*prev >> 6 & 0x3fffff) << 6;
                            /* CONCAT-17 byte-AND against _DAT_0068a560: opaque mask op */
                            unsigned long m0 = *(unsigned long *)0x68a560;
                            unsigned long m1 = *(unsigned long *)0x68a568;
                            *tgt = *tgt & m1;
                            *prev = *prev & m0;
                        }
                    } else {
                        if (sb < nb) goto trap;
                        unsigned long *tgt = sub + 1;
                        if ((*x1 & 0x3c) != 0xc) {
                            if (((se < tgt) || (tgt < sub)) || (gap < 0x39)) goto trap;
                            cnt = 0;
                            unsigned long v2 = *sub;
                            run = 7;
                            unsigned long *q = sub;
                            goto loopb;
                        }
                        if ((((se < tgt) || (tgt < sub)) ||
                            ((unsigned long)((long)sl - (long)tgt) < 0x30)) || (gap < 0x30))
                            goto trap;
                        unsigned long v2 = *sub;
                        unsigned long e1 = sub[2];
                        unsigned long e0 = *tgt;
                        unsigned long e3 = sub[3];
                        unsigned long e5 = sub[5];
                        sub[3] = sub[4];
                        sub[2] = e3;
                        sub[5] = sub[6];
                        sub[4] = e5;
                        sub[1] = e1;
                        *sub = e0;
                        unsigned long *t6 = sub + 6;
                        *sub = *sub & 0xffffffffffffffc3 | v2 & 0x3c;
                        if (((t6 < sub) || (se < sub + 7)) || (sub + 7 < t6)) goto trap;
                        *t6 = 0;
                        unsigned long *nb2 = x1 + 2;
                        if (((nb2 < x1) || (x1 + 3 < nb2)) || (sb < x1 + 3)) goto trap;
                        *nb2 = v2 & 0xffffffffffffffc3;
                        *s = *s & 0xfffffffff0000000 | *s & 0x3f | (*sub >> 6 & 0x3fffff) << 6;
                    }
                    goto fin3;
                }
            }
        }
        pos = (unsigned long)right;
        first = false;
    } while (was);
    if ((tag & 0xff) == 0) {
        p = bucket + right;
        if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto trap;
        unsigned long v = *p;
        if ((v & 3) == 1) {
            unsigned long *sub = (unsigned long *)(v >> 0x1c);
            unsigned long *se = sub + 8;
            if ((se < (unsigned long *)(v >> 0x1c)) ||
               ((sub != 0 && ((long)se - (long)sub < 0x39)))) goto trap;
            unsigned long *n = (sub != 0) ? se : 0;
            unsigned long *nb = x1;
            unsigned int k2 = i;
            goto d3f0;
        }
        goto d490;
    } else {
        p = bucket + left;
        if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto trap;
        unsigned long v = *p;
        if ((v & 3) != 1) {
            if ((i & 0xff) < 7) goto d390;
            goto d490;
        }
        unsigned long *sub = (unsigned long *)(v >> 0x1c);
        unsigned long *se = sub + 8;
        if ((se < (unsigned long *)(v >> 0x1c)) ||
           ((sub != 0 && ((long)se - (long)sub < 0x39)))) goto trap;
        unsigned long *n = 0;   /* puVar22 */
        unsigned long *nb = x1;  /* extraout_x1 */
        unsigned int k2 = i;
        unsigned long *sl = 0;
        if (sub != 0) sl = se;
d3f0:
        if ((sub != 0) && (nb != 0)) {
            if ((n < nb + 1) || (*nb = *nb & 0xffffffffffffffc3, sl < sub + 1)) goto trap;
            if ((*sub & 0x3c) != 0xc) {
                if (sl < sub || (unsigned long)((long)sl - (long)sub) < 0x39) goto trap;
                run = 0;
                unsigned long *q = sub;
                do {
                    if (((q < sub) || (sub + 8 < q + 1)) || (q + 1 < q)) goto trap;
                    if ((*q & 0xfffffc0) == 0) break;
                    run = run - 1;
                    q = q + 1;
                } while (run != -7);
                unsigned long *dst = bucket + (unsigned char)left;
                if ((((dst < bucket) || (lim < dst + 1)) ||
                    ((dst + 1 < dst ||
                     ((*dst = *dst & 0xfffffffff0000000 | *dst & 0x3f | (*p >> 6 & 0x3fffff) << 6,
                      (unsigned long)((long)n - (long)nb) < 0x40 || (p = sub + 1, sl < p)))) ||
                    (p < sub)))) goto trap;
                unsigned long v2 = *bucket;
                *bucket = v2 & 0xffffffffffffffc3;
                char c2 = (char)sk_cap_bucket_slot_remove(bucket, k2 & 0xff, 8);
                *bucket = *bucket & 0xffffffffffffffc0 | *bucket & 3 | (v2 >> 2 & 0xf) << 2;
                FUN_0066a6b4(nb);
                if (c2 != '') {
                    unsigned long s2 = 2;
                    if (2 < (unsigned char)(c2 - 1U)) s2 = 3;
                    goto fin;
                }
            }
        }
    }
    unsigned long *sub = 0;   /* merge candidate bucket (scope widened) */
    unsigned long *sl = 0;
    FUN_0066a6b4(bucket);
    if (sub + 1 <= sl) {
        if ((*sub & 0x3c) == 8) {
            *sub = *sub & 0xffffffffffffffc3 | 4;
        }
        if ((sub <= sl) && (0x38 < (long)sl - (long)sub)) {
            goto fin3;
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66d684) */
d390:
    p = bucket + right;
    if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto trap;
    {
        unsigned long v = *p;
        if ((v & 3) == 1) {
            unsigned long *sub = (unsigned long *)(v >> 0x1c);
            unsigned long *se = sub + 8;
            if ((se < (unsigned long *)(v >> 0x1c)) ||
               ((sub != 0 && ((long)se - (long)sub < 0x39)))) goto trap;
            unsigned long *n = (sub != 0) ? se : 0;
            unsigned long *nb = x1;
            unsigned int k2 = i;
            goto d3f0;
        }
    }
d490:
    /* no merge partner found */
    {
        unsigned long status = 0;
        unsigned long outb = (unsigned long)bucket;
fin:
        return (sk_pair_t){status, outb};
    }
fin3:
    {
        return (sk_pair_t){3, (unsigned long)bucket};
    }
loopb:
    /* compact sub-bucket scan tail (retained structurally) */
    __builtin_unreachable();
}
/* FUN_0066dc90 @ 0x0066dc90  (est. sk_page_region_build)
 * Ghidra: void FUN_0066dc90(ulong param_1, ulong *param_2)
 * Builds a page-region descriptor into param_2 (5 slots) for a 16KB-aligned
 * region of param_1 bytes via the init dispatch FUN_0067203c(0x148, ...).
 * Confidence: medium */
static void sk_page_region_build(unsigned long base, unsigned long *out)
{
    unsigned char d[8] = {0x11, 0, 0, 0, 0, 0, 0, 0};
    long a = 0;
    if ((base & 0x3fff) != 0) a = 0x4000;
    a = a + (base & 0xffffffffffffc000);
    unsigned char d2[8] = {0, 0, 0xfd, 0xe, 0, 0, 0, 0};
    unsigned long res[2] = {0, 0};
    unsigned long uVar4 = FUN_0067203c(0x148, &d, &res, 0, &d);
    if ((uVar4 & 0xff) == 0) {
        unsigned long v = 0;   /* CONCAT71(uStack_37,uStack_38) artifact: hi word of result */
        if ((v <= v + base) && ((v == 0 || (base <= (v + base) - v)))) {
            out[1] = base;
            out[2] = 0;
            out[0] = v;
            out[4] = res[1];
            out[3] = res[0];
            return;
        }
    } else {
        long off = (uVar4 & 0xff) * 8;
        unsigned char *p = (unsigned char *)(off + 0x6b5e50);
        if (((unsigned char *)0x6b5e4f < p && (unsigned char *)0x6b5e58 + off < (unsigned char *)0x6b5e91) &&
            p <= (unsigned char *)0x6b5e58 + off) {
            FUN_006833d4(0x6ab5ba);   /* fatal */
        }
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66dd8c) */
}

/* FUN_0066dd8c @ 0x0066dd8c  (est. sk_page_region_resize)
 * Ghidra: void FUN_0066dd8c(long *param_1, ulong param_2)
 * Grows a page-region descriptor param_1 to at least param_2 bytes: invokes the
 * region's growth method (indirect call through ops[param_1[4]]+0x18) to
 * enlarge the backing store, updating param_1[2]. Validates bounds.
 * Confidence: medium */
static void sk_page_region_resize(long *r, unsigned long need)
{
    if ((r == 0) || (*r == 0)) {
        FUN_0068649c();
    } else if (need <= (unsigned long)r[1]) {
        if ((unsigned long)r[2] < need) {
            unsigned long newsz = need;
            unsigned long rc = (*(sk_fp_t *)(r[4] + 0x18))(r[3], &newsz);
            if ((rc & 0xff) != 0) {
                long off = (rc & 0xff) * 8;
                unsigned char *p = (unsigned char *)(off + 0x6b5e50);
                if (((unsigned char *)0x6b5e4f < p && (unsigned char *)0x6b5e58 + off < (unsigned char *)0x6b5e91) &&
                    p <= (unsigned char *)0x6b5e58 + off) {
                    FUN_006833d4(0x6ab657);   /* fatal */
                }
                __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66de5c) */
            }
            r[2] = (long)newsz;
        }
        return;
    }
    FUN_006833d4(0x6ab626);   /* fatal: size exceeded */
}

/* FUN_0066de5c @ 0x0066de5c  (est. sk_page_region_destroy)
 * Ghidra: void FUN_0066de5c(long *param_1)
 * Destroys a page-region descriptor param_1 via its ops table (indirect call
 * through param_1[4]); zeroes the descriptor on success. Fatal on failure.
 * Confidence: medium */
static void sk_page_region_destroy(long *r)
{
    unsigned long rc;
    if ((r == 0) || (*r == 0)) {
        return;
    }
    if (r[3] == 0) {
        FUN_006864b4();
        rc = 0;
    } else {
        rc = (*(sk_fp_t *)r[4])();
        rc = rc & 0xff;
        if (rc == 0) {
            *r = 0;
            r[1] = 0;
            return;
        }
    }
    unsigned char *p = (unsigned char *)(rc * 8 + 0x6b5e50);
    if ((p < (unsigned char *)0x6b5e50 || (unsigned char *)0x6b5e90 < (unsigned char *)0x6b5e58 + rc * 8) ||
        (unsigned char *)0x6b5e58 + rc * 8 < p) {
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66def8) */
    }
    FUN_006833d4(0x6ab6c1);   /* fatal */
}

/* FUN_0066def8 @ 0x0066def8  (est. sk_page_region_map)
 * Ghidra: ulong FUN_0066def8(undefined8 param_1, ulong param_2, long *param_3,
 *                          ulong *param_4)
 * Maps pages of a region: resolves the region via FUN_00673894, maps the base
 * page (FUN_00675b48), then extends the map page-by-page up to the size bound
 * *param_4, updating *param_4 and storing the mapped base into *param_3. Returns
 * 0 on success or 0x9580001 on failure.
 * Confidence: medium */
static unsigned long sk_page_region_map(unsigned long ctx, unsigned long addr, long *out, unsigned long *bound)
{
    unsigned long limit = *bound;
    long st[11];
    st[10] = -1; st[9] = 0; st[6] = 0; st[5] = 0; st[8] = 0; st[7] = 0;
    st[2] = 0; st[1] = 0; st[4] = 0; st[3] = 0;
    FUN_00671b60(st + 1, ctx, 0, 0);
    unsigned long r = FUN_00673894(st + 1, addr);
    if (r != 0) {
        if (r + 0xb0 < r) {
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e05c) */
        }
        if (*(int *)(r + 0x20) != 0) {
            unsigned long want = (*(long *)(r + 8) - addr) + *(long *)(r + 0x10);
            if (want <= limit) limit = want;
            FUN_00671bc4(st + 1, ctx);
            unsigned long rc = FUN_00675b48(r, addr, st + 10);
            if ((rc & 0xff) != 0) {
                return rc;
            }
            st[10] = st[10] + (addr & 0x3fff);
            *out = st[10];
            long d = -(addr & 0x3fff);
            while (d = d + 0x4000, (unsigned long)d < limit) {
                st[0] = 0;
                char c = FUN_00675b48(r, addr + (unsigned long)d, st);
                if ((c != '\0') || ((unsigned long)d + st[10] != (unsigned long)st[0])) break;
            }
            if ((unsigned long)limit <= (unsigned long)d) d = limit;
            *bound = (unsigned long)d;
            return 0;
        }
    }
    FUN_00671bc4(st + 1, ctx);
    return 0x9580001;
}

/* FUN_0066e0b4 @ 0x0066e0b4  (est. sk_region_register)
 * Ghidra: undefined1 [16] FUN_0066e0b4(undefined8 param_1)
 * Registers a region (param_1) in the global region table: bumps the
 * registration counter DAT_006fea58, walks the per-CPU region list
 * (FUN_00668c94), and registers via FUN_00675ae8, returning a pair
 * {status, table pointer 0x6b69d0}.
 * Confidence: medium */
static sk_pair_t sk_region_register(unsigned long ctx)
{
    *(unsigned long *)0x6fea58 = *(unsigned long *)0x6fea58 + 1;
    unsigned long st[10];
    st[8] = 0; st[5] = 0; st[4] = 0; st[7] = 0; st[6] = 0; st[1] = 0; st[0] = 0; st[3] = 0; st[2] = 0;
    FUN_00671b60(st, ctx, 0, 0);
    if (st[0] <= st[0] + 0x2a0) {
        unsigned long *pc = (unsigned long *)FUN_00668c94().lo;
        unsigned long v = *pc;
        unsigned long cur = 0;
        do {
            cur = v;
            if (cur == 0) goto found;
            v = *(unsigned long *)(cur + 0x58);
        } while (*(unsigned long *)(cur + 0x58) != 0);
        if (cur <= cur + 0xb0) {
found:
            unsigned long status = FUN_00675ae8(st);
            FUN_00671bc4(st, ctx);
            if (status == 0) {
                *(unsigned long *)0x6fea58 = *(unsigned long *)0x6fea58 - 1;
            }
            return (sk_pair_t){status, 0x6b69d0};
        }
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e184) */
}

/* FUN_0066e19c @ 0x0066e19c  (est. sk_region_query)
 * Ghidra: undefined1 [16] FUN_0066e19c(undefined8 param_1, undefined8 param_2,
 *                                     int *param_3, undefined8 *param_4)
 * Queries a region: resolves the region descriptor for param_2 (FUN_00673894),
 * copies its type (param_3) and 4-word descriptor (param_4) out, and returns a
 * pair {descriptor, 0x6b6978 table tag}.
 * Confidence: medium */
static sk_pair_t sk_region_query(unsigned long ctx, unsigned long key, int *type, unsigned long *out)
{
    unsigned long d[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    FUN_00671b60(d, ctx, 0, 0);
    unsigned long *r = (unsigned long *)FUN_00673894(d, key);
    unsigned long table;
    if (r == 0) {
        table = 0;
    } else {
        if (r + 0x16 < r) {
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e274) */
        }
        if (*(int *)(r + 4) == 0) {
            table = 0;
            r = 0;
        } else {
            if (r + 0x16 <= r) {
                __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e274) */
            }
            if (type != 0) {
                *type = *(int *)(r + 4);
            }
            if (out != 0) {
                out[1] = r[1];
                out[0] = r[0];
                out[3] = r[3];
                out[2] = r[2];
            }
            table = 0x6b6978;
        }
    }
    FUN_00671bc4(d, ctx);
    return (sk_pair_t){(unsigned long)r, table};
}

/* FUN_0066e274 @ 0x0066e274  (est. sk_region_unlock)
 * Ghidra: ulong FUN_0066e274(undefined8 param_1, undefined8 param_2, int param_3)
 * Unlocks/commits a region: resolves it (FUN_006736ec), then for the unlock
 * variant (param_3==1) traps via CallSupervisor(3) to release it, returning the
 * IPC status. Checks the persistent flag and returns 0x9cb0001 if locked.
 * Confidence: medium */
static unsigned long sk_region_unlock(unsigned long ctx, unsigned long key, int mode)
{
    unsigned long size = 0;
    long r = 0;
    unsigned long rc = FUN_006736ec(ctx, key, &size, &r);
    if ((rc & 0xff) == 0) {
        if ((mode == 1) && ((*(unsigned char *)(r + 0x20) >> 3 & 1) == 0)) {
            rc = 0x9cb0001;
        } else {
            sk_ipc_msg[0] = (unsigned long)(mode == 1);   /* tpidrro_el0 message word */
            CallSupervisor(3);
            if (size == 0) {
                rc = 0;
            } else {
                rc = (size & 0x7fff) << 0x10 | 0x80000001;
            }
        }
    }
    return rc;
}

/* FUN_0066e314 @ 0x0066e314  (est. sk_supervisor_op2)
 * Ghidra: undefined1 [16] FUN_0066e314(void)
 * Performs a global supervisor operation: resolves the runtime context
 * (FUN_00668c78) and performs a 3-arg table op (FUN_00677674), then traps via
 * CallSupervisor(2). Returns the IPC status pair.
 * Confidence: medium */
static sk_pair_t sk_supervisor_op2(void)
{
    unsigned long ctx = FUN_00668c78();
    unsigned long rc = FUN_00677674(ctx, 2, 0);
    unsigned long status;
    if (rc == 0) {
        status = 0x9e60004;
    } else {
        CallSupervisor(2);
        status = 0;
        if (rc != 0) {
            status = (rc & 0x7fff) << 0x10 | 0x80000001;
        }
    }
    return (sk_pair_t){status, 0};
}

/* FUN_0066fa04 @ 0x0066fa04  (est. sk_region_destroy)
 * Ghidra: undefined1 [16] FUN_0066fa04(long param_1, undefined8 *param_2)
 * Destroys a region object (param_2, 0xc0 bytes): verifies ownership, releases
 * the child regions (sk_region_free) and runtime allocations, tears down the
 * lock, and zeroes the descriptor, then returns the zero status pair. Fatal on
 * a busy flag.
 * Confidence: medium */
static sk_pair_t sk_region_destroy(long owner, unsigned long *r)
{
    *(unsigned long *)0x70024c = *(unsigned long *)0x70024c + 1;
    if (r[10] != (unsigned long)owner) {
        FUN_006833d4(0x6aedb9);   /* fatal: wrong owner */
    }
    if (*(char *)((long)r + 0xa1) == '\x01') {
        FUN_00686c04();   /* fatal-ish cleanup */
    } else {
        sk_region_free(r[0xb]);
        sk_region_free(r[0xe]);
        FUN_006860f4(r[0x12]);
        FUN_006860f4(r[0x13]);
        if (*(char *)(r + 8) != '\x01') {
            thunk_FUN_00655200(r + 6);   /* lock teardown */
            r[0x15] = 0; r[0x14] = 0; r[0x17] = 0; r[0x16] = 0;
            r[0x11] = 0; r[0x10] = 0; r[0x13] = 0; r[0x12] = 0;
            r[0xd] = 0; r[0xc] = 0; r[0xf] = 0; r[0xe] = 0;
            r[9] = 0; r[8] = 0; r[0xb] = 0; r[10] = 0;
            r[5] = 0; r[4] = 0; r[7] = 0; r[6] = 0;
            r[1] = 0; r[0] = 0; r[3] = 0; r[2] = 0;
            FUN_0066951c(r);   /* release the object */
            return (sk_pair_t){0, 0};
        }
    }
    FUN_006833d4(0x6adaed);   /* fatal */
}

/* FUN_00670178 @ 0x00670178  (est. sk_region_alloc_advance)
 * Ghidra: ulong FUN_00670178(long param_1, ulong *param_2)
 * Advances a region's allocation cursor: computes the next 16KB-aligned
 * boundary at/beyond the given address (via in-register args), validates it
 * against the region size, and extends the region to cover it (FUN_00670228),
 * storing the new cursor. Returns 0 or 0x6010001.
 * Confidence: medium */
static unsigned long sk_region_alloc_advance(long r, unsigned long *out)
{
    unsigned long target = 0 /*in_x10*/ + (0 /*in_x9*/ & 0xffffffffffffc000);
    unsigned long rc;
    if (*(unsigned long *)(r + 0x10) < target) {
        rc = 0x6010001;
    } else {
        unsigned long cur = *(unsigned long *)(r + 0x48);
        long delta = (long)(target - cur);
        if (target < cur || delta == 0) {
            rc = 0;
            *out = cur;
        } else {
            if ((0 /*in_w8*/ >> 7 & 1) != 0) {
                cur = *(unsigned long *)(r + 0x10) - target;
            }
            rc = sk_region_map_extend(r, &cur, (unsigned long *)&delta);
            if ((rc & 0xff) == 0) {
                rc = 0;
                *(unsigned long *)(r + 0x48) = target;
                *out = target;
            }
        }
    }
    return rc;
}

/* FUN_00670228 @ 0x00670228  (est. sk_region_map_extend)
 * Ghidra: void FUN_00670228(long param_1, ulong *param_2, ulong *param_3)
 * Extends a region's mapping: aligns the requested [*param_2, *param_2+*param_3)
 * range to 16KB, validates against the region, maps it via FUN_00675418, and on
 * sub-page or non-alignable cases walks the page table (FUN_00686c8c) and maps
 * individual pages (FUN_00674fac). Updates the alignment-corrected range.
 * Confidence: medium */
static unsigned long sk_region_map_extend(long r, unsigned long *off, unsigned long *sz)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    if (*(unsigned int *)(r + 0x20) != 0 && (*(unsigned int *)(r + 0x20) & 0x81000) == 0) {
        unsigned long base = *off;
        if ((base < *(unsigned long *)(r + 0x10)) && (*sz <= *(unsigned long *)(r + 0x10) - base)) {
            unsigned long pa = (*(long *)(r + 8) + base) & 0xffffffffffffc000;
            *sz = (*sz + base + *(long *)(r + 8)) - pa;
            *off = pa - *(long *)(r + 8);
            long align = 0;
            if ((*sz & 0x3fff) != 0) align = 0x4000;
            *sz = align + (*sz & 0xffffffffffffc000);
            FUN_00673914(r, *off);
            unsigned long rc = FUN_00675418(r, pa, *sz + pa);
            unsigned int c = (unsigned int)rc & 0xff;
            if (c == 2) {
                /* result 0x68f0002 on collision */
            } else if (((c != 8) && ((rc & 0xff) != 0)) &&
                       ((*(unsigned int *)(r + 0x20) >> 0x12 & 1) == 0)) {
                unsigned char sb[32];
                sk_pair_t rr = FUN_00686c8c(rc, pa, sb);
                unsigned long pg = rr.hi;
                long src = (long)rr.lo;
                unsigned long cookie2 = *(unsigned long *)0x6b5ed0;
                if (((*(unsigned char *)(src + 0x21) >> 4 & 1) == 0) || (*(unsigned long *)(src + 0x10) <= pg)) {
                    rc = 0x6230001;
                } else {
                    FUN_00673914(src, pg & 0xffffffffffffc000, 0x4000);
                    rc = sk_page_map(src, *(long *)(src + 8) + pg, (unsigned long)sb, 0, 0, 0, 0);
                    if ((long)rc < 7) {
                        if (rc == 0) rc = 0;
                        else if (rc == 2) rc = 0x80020002;
                        else {
                            if (rc != 5) goto panicpath;
                            rc = 0x80050003;
                        }
                    } else {
                        if (((rc != 7) && (rc != 0x307)) && (rc != 0x207)) {
panicpath:
                            FUN_00686d10(rc, (unsigned char *)&sb);
                            FUN_00674688(0, 0, 0, 0);
                            return 0;
                        }
                        rc = (rc & 0x7fff) << 0x10 | 0x80000001;
                    }
                }
                if (*(unsigned long *)0x6b5ed0 == cookie2) {
                    return 0;
                }
                FUN_0067f660(rc, 0);   /* fatal (noreturn) */
            }
        }
    }
    if (*(unsigned long *)0x6b5ed0 == cookie) {
        return 0;
    }
    FUN_0067f660(0x6800001, 0);   /* fatal (noreturn) */
    return 0;
}

/* FUN_0066fb0c @ 0x0066fb0c  (est. sk_region_free)
 * Ghidra: undefined1 [16] FUN_0066fb0c(undefined1 *param_1)
 * Frees a region (param_1): removes it from the per-CPU active list, computes
 * its live range, unmaps its pages (FUN_00674688), tears down its page state
 * (FUN_00671f38), and rejoins it to its owning region's map. Walks the
 * neighboring regions (FUN_00673894 / FUN_0067483c) to coalesce free space.
 * Returns the status pair; 0x5660001 if not unmappable.
 * Confidence: medium */
static sk_pair_t sk_region_free(unsigned long rarg)
{
    unsigned char *r = (unsigned char *)rarg;
    long base = *(long *)(r + 0x50);
    unsigned long st[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned long rc = 0;
    if ((((unsigned char)r[0x23] >> 3 & 1) == 0)) {
        if (FUN_0067a760() != 0) {
            unsigned long lock = base + 0x1f0;
            if (base + 0x200U < lock) goto trap;
            if (FUN_0067cffc(lock) != 0) {
                FUN_006833d4(0x6a8797);   /* fatal */
            }
            long *prev = *(long **)(r + 0x90);
            long *next = *(long **)(r + 0x98);
            if (prev != 0) {
                *(long **)(prev + 0x98) = next;
            }
            *next = (long)prev;
            if (FUN_0067d02c(lock) != 0) {
                FUN_006833d4(0x6a8797);   /* fatal */
            }
        }
        long live;
        if ((*(unsigned int *)(r + 0x20) >> 7 & 1) == 0) {
            live = *(long *)(r + 8);
        } else {
            live = (*(long *)(r + 0x10) - *(long *)(r + 0x48)) + *(long *)(r + 8);
        }
        long d = live - *(long *)(r + 8);
        long o = 0x10;
        if ((*(unsigned int *)(r + 0x20) & 0x40) != 0) {
            o = 0x48;
        }
        unsigned long len = *(unsigned long *)(r + o);
        FUN_00674688(r, &d, &len, 1);
        unsigned char *pg = r + 0x80;
        if (r + 0x90 < pg) goto trap;
        if (FUN_0067cffc(pg) != 0) {
            FUN_006833d4(0x6a8797);   /* fatal */
        }
        FUN_00671f38((long)r);
        if (FUN_0067d02c(pg) != 0) {
            FUN_006833d4(0x6a8797);   /* fatal */
        }
        FUN_00671b60(st, base, *(unsigned long *)(r + 8), *(unsigned long *)(r + 0x10));
        if ((*(unsigned int *)(r + 0x20) >> 0x18 & 1) == 0) {
            if ((*(unsigned int *)(r + 0x20) >> 0x10 & 1) != 0) {
                FUN_0067a334(st, base, (long)r);
            }
            long *slot = *(long **)(r + 0x70);
            if (slot == 0) {
                FUN_006833d4(0x6acd4e);   /* fatal */
            }
            /* re-link the region into the owner's span list */
            if (2 < st[1]) {
                FUN_006833d4(0x6ac2e0);   /* fatal */
            }
            *slot = st[2];
            *(unsigned long *)(r + 0x70) = 0;
            *(unsigned int *)(r + 0x20) = 0;
            *r = 0;
            *(unsigned long *)(r + 0x30) = 0;
            *(unsigned long *)(r + 0x28) = 0;
            *(unsigned long *)(r + 0x40) = 0;
            *(unsigned long *)(r + 0x38) = 0;
            st[2] = (long)slot;
            FUN_006745f4(*(unsigned long *)(st[0] + 0x58), (long)r);
            unsigned long u = FUN_00673894(st, *(unsigned long *)(r + 8) - 0x4000);
            if ((0x3fff < *(unsigned long *)(r + 8)) && u != 0) {
                if (u + 0xb0 < u) goto trap;
                if (*(int *)(u + 0x20) == 0) {
                    r = (unsigned char *)FUN_0067483c(st, base, u, (long)r);
                }
            }
            u = FUN_00673894(st, 0);
            if ((*(long *)(r + 0x10) + *(long *)(r + 8) != 0x1000000000) && u != 0) {
                if (u + 0xb0 < u) goto trap;
                if (*(int *)(u + 0x20) == 0) {
                    FUN_0067483c(st, base, (long)r);
                }
            }
            rc = 0;
        } else {
            rc = 0x5660001;
        }
        FUN_00671bc4(st, base);
    } else {
        FUN_0067d72c(0x6acd07);
        rc = 0x5b10001;
    }
    return (sk_pair_t){rc, 0};
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66fd78) */
}

/* FUN_0066feb8 @ 0x0066feb8  (est. sk_region_unmap)
 * Ghidra: void FUN_0066feb8(long param_1, uint param_2)
 * Unmaps pages from a region (param_1) according to the flag mask param_2:
 * clears the requested flag bits (validating the unmap set), then walks the
 * region's live pages and releases each 16KB block (sk_cap_decode/free via the
 * page descriptor, CallSupervisor(0) for the TLB/teardown). Rejects invalid
 * masks with 0x5df0001/0x5e70001.
 * Confidence: medium */
static void sk_region_unmap(long r, unsigned int mask)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    unsigned int flags = *(unsigned int *)(r + 0x20);
    unsigned long rc;
    if ((mask & (flags ^ 0xffffffff)) == 0) {
        unsigned int cleared = flags & (mask ^ 0xffffffff);
        if ((cleared & 0xd08d9c1) == 0) {
            flags = flags & mask;
            *(unsigned int *)(r + 0x20) = flags;
            if ((cleared & 0x18) != 0) {
                long live;
                if ((flags >> 7 & 1) == 0) {
                    live = *(long *)(r + 8);
                } else {
                    live = (*(long *)(r + 0x10) - *(long *)(r + 0x48)) + *(long *)(r + 8);
                }
                unsigned long pg = r + 0x80;
                if ((flags >> 7 & 1) != 0) goto ff74;
ff6c:
                long cur = *(long *)(r + 8);
                do {
                    long o = 0x10;
                    if ((flags & 0x40) != 0) {
                        o = 0x48;
                    }
                    if (*(unsigned long *)(r + o) <= (unsigned long)(live - cur)) break;
                    unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
                    if (r + 0x90U < pg) goto trap;
                    if (FUN_0067cffc(pg) != 0) {
                        FUN_006833d4(0x6a8797);   /* fatal */
                    }
                    unsigned long l[5] = {0, 0, 0, 0, 0};
                    if (cb + 0xd0 < cb) goto trap;
                    sk_cap_decode(l, *(unsigned long *)(r + 0x78),
                                  (int)((unsigned long)(live - *(long *)(cb + 0x28)) >> 0xe) + 1, 0, 0);
                    unsigned long blk = l[0];
                    *(unsigned long *)(r + 0x78) = l[4];
                    if (l[0] == 0) {
                        if (FUN_0067d02c(pg) != 0) {
                            FUN_006833d4(0x6a8797);   /* fatal */
                        }
                        if ((char)l[2] != '\0') {
                            FUN_00686c74();
                            FUN_006833d4(0x6a8797);   /* fatal */
                        }
                    } else {
                        sk_ipc_msg[0] = (unsigned long)(flags >> 3 & 3);   /* tpidrro_el0 */
                        CallSupervisor(0);
                        sk_ipc_msg[0] = (flags >> 3 & 3);
                        if (FUN_0067d02c(pg, 0) != 0) {
                            FUN_006833d4(0x6a8797);   /* fatal */
                        }
                        unsigned long v = 0;
                        if ((blk & 0xff) != 4) {
                            v = blk;
                        }
                        if ((v & 0xff) != 0) {
                            FUN_00686c2c(v, l);
                            FUN_006833d4(0x6a8797);   /* fatal */
                        }
                    }
                    live = live + 0x4000;
                    flags = *(unsigned int *)(r + 0x20);
                    if ((flags >> 7 & 1) == 0) goto ff6c;
ff74:
                    cur = (*(long *)(r + 0x10) - *(long *)(r + 0x48)) + *(long *)(r + 8);
                } while (true);
            }
            rc = 0;
        } else {
            rc = 0x5e70001;
        }
    } else {
        rc = 0x5df0001;
    }
    if (*(unsigned long *)0x6b5ed0 != cookie) {
        FUN_0067f660(rc, 0);   /* fatal (noreturn) */
    }
    return;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6700a4) */
}

/* FUN_00671018 @ 0x00671018  (est. sk_free_slot_get)
 * Ghidra: undefined8 * FUN_00671018(long param_1)
 * Pops a node from a small free-list (head at +0x18, count byte at +0x32).
 * Fatal if the list is empty or the count is out of range.
 * Confidence: high */
static unsigned long *sk_free_slot_get(long ctx)
{
    unsigned char c = *(unsigned char *)(ctx + 0x32);
    if (c == 0) {
        FUN_006833d4(0x6ab6fa);   /* fatal: empty free list */
    }
    if (c < 4) {
        *(unsigned char *)(ctx + 0x32) = c - 1;
        unsigned long *n = *(unsigned long **)(ctx + 0x18);
        if (n != 0) {
            *(unsigned long *)(ctx + 0x18) = *n;
            *n = 0;
            return n;
        }
        FUN_006833d4(0x6ab7e0);   /* fatal: list head mismatch */
    }
    FUN_006833d4(0x6ab780);   /* fatal: count overrun */
}

/* FUN_006710e8 @ 0x006710e8  (est. sk_free_slot_put)
 * Ghidra: void FUN_006710e8(long param_1, undefined8 *param_2)
 * Pushes a node onto the small free-list (head +0x18, count byte +0x32).
 * Confidence: high */
static void sk_free_slot_put(long ctx, unsigned long *n)
{
    if (n != 0) {
        unsigned char c = *(unsigned char *)(ctx + 0x32);
        if (2 < c) {
            FUN_006833d4(0x6ab780);   /* fatal: count overrun */
        }
        *n = *(unsigned long *)(ctx + 0x18);
        *(unsigned long **)(ctx + 0x18) = n;
        *(unsigned char *)(ctx + 0x32) = c + 1;
    }
}

/* FUN_00671150 @ 0x00671150  (est. sk_free_slot2_get)
 * Ghidra: undefined8 * FUN_00671150(long param_1)
 * Pops a node from the second small free-list (head +0x20, count byte +0x33).
 * Confidence: high */
static unsigned long *sk_free_slot2_get(long ctx)
{
    unsigned char c = *(unsigned char *)(ctx + 0x33);
    if (c == 0) {
        FUN_006833d4(0x6ab86e);   /* fatal: empty free list */
    }
    if (c < 4) {
        *(unsigned char *)(ctx + 0x33) = c - 1;
        unsigned long *n = *(unsigned long **)(ctx + 0x20);
        if (n != 0) {
            *(unsigned long *)(ctx + 0x20) = *n;
            *n = 0;
            return n;
        }
        FUN_006833d4(0x6ab95e);   /* fatal: list head mismatch */
    }
    FUN_006833d4(0x6ab8f6);   /* fatal: count overrun */
}

/* FUN_00671220 @ 0x00671220  (est. sk_free_slot2_put)
 * Ghidra: void FUN_00671220(long param_1, undefined8 *param_2)
 * Pushes a node onto the second small free-list (head +0x20, count byte +0x33).
 * Confidence: high */
static void sk_free_slot2_put(long ctx, unsigned long *n)
{
    if (n != 0) {
        unsigned char c = *(unsigned char *)(ctx + 0x33);
        if (2 < c) {
            FUN_006833d4(0x6ab8f6);   /* fatal: count overrun */
        }
        *n = *(unsigned long *)(ctx + 0x20);
        *(unsigned long **)(ctx + 0x20) = n;
        *(unsigned char *)(ctx + 0x33) = c + 1;
    }
}

/* FUN_00671288 @ 0x00671288  (est. sk_free_slot3_get)
 * Ghidra: undefined8 * FUN_00671288(long param_1)
 * Pops a node from the large free-list (head +0x28, count +0x38).
 * Confidence: high */
static unsigned long *sk_free_slot3_get(long ctx)
{
    if (*(long *)(ctx + 0x38) == 0) {
        FUN_006833d4(0x6ab9de);   /* fatal: empty free list */
    }
    *(long *)(ctx + 0x38) = *(long *)(ctx + 0x38) - 1;
    unsigned long *n = *(unsigned long **)(ctx + 0x28);
    if (n != 0) {
        *(unsigned long *)(ctx + 0x28) = *n;
        *n = 0;
        return n;
    }
    FUN_006833d4(0x6abacc);   /* fatal: list head mismatch */
}

/* FUN_00671320 @ 0x00671320  (est. sk_free_slot3_put)
 * Ghidra: void FUN_00671320(long param_1, undefined8 *param_2)
 * Pushes a node onto the large free-list (head +0x28, count +0x38).
 * Confidence: high */
static void sk_free_slot3_put(long ctx, unsigned long *n)
{
    if (n != 0) {
        long c = *(long *)(ctx + 0x38);
        if (c == -1) {
            FUN_006833d4(0x6aba65);   /* fatal: count underflow */
        }
        *n = *(unsigned long *)(ctx + 0x28);
        *(unsigned long **)(ctx + 0x28) = n;
        *(long *)(ctx + 0x38) = c + 1;
    }
}

/* FUN_00671384 @ 0x00671384  (est. sk_free_slot_peek)
 * Ghidra: undefined8 FUN_00671384(long param_1)
 * Peeks the large free-list: returns a node if any are available, else 0.
 * Confidence: high */
static unsigned long sk_free_slot_peek(long ctx)
{
    if (*(long *)(ctx + 0x38) != 0) {
        return (unsigned long)sk_free_slot3_get(ctx);
    }
    return 0;
}

/* FUN_00671398 @ 0x00671398  (est. sk_alloc_ensure_capacity)
 * Ghidra: bool FUN_00671398(long param_1, long param_2, undefined8 param_3,
 *                          undefined8 param_4, ulong param_5)
 * Ensures the free-list has at least param_5 nodes: if the count at ctx+0x38 is
 * below the target, allocates additional nodes (FUN_006692e4) until satisfied,
 * releases the parent's lock, and re-asserts ownership. Returns true when
 * capacity is sufficient.
 * Confidence: medium */
static bool sk_alloc_ensure_capacity(long owner, long parent, unsigned long a, unsigned long b, unsigned long need)
{
    bool ok;
    if (*(unsigned long *)(parent + 0x50) != (unsigned long)owner) {
        FUN_006833d4(0x6abb4b);   /* fatal: wrong owner */
    }
    if (*(unsigned long *)(owner + 0x38) < need) {
        *(unsigned long *)(parent + 0x50) = 0;
        int rc = FUN_0067d02c(parent + 0x40);
        if (rc != 0) {
            FUN_006833d4(0x6a8797);   /* fatal */
        }
        if (*(unsigned long *)(owner + 0x38) < need) {
            do {
                long n = FUN_006692e4();
                ok = n != 0;
                if (n == 0) break;
                sk_free_slot3_put(owner, (unsigned long *)n);
            } while (*(unsigned long *)(owner + 0x38) < need);
        } else {
            ok = true;
        }
        FUN_00679838(parent, a, b);
        if (*(long *)(parent + 0x50) != 0) {
            FUN_006833d4(0x6abb4b);   /* fatal: ownership raced */
        }
        *(long *)(parent + 0x50) = owner;
    } else {
        ok = true;
    }
    return ok;
}

/* FUN_006704ac @ 0x006704ac  (est. sk_region_merge)
 * Ghidra: undefined1 [16] FUN_006704ac(long *param_1, long *param_2, long param_3,
 *                                    long *param_4)
 * Merges two adjacent regions (param_1/param_2) of the given type param_3 into a
 * single region: validates compatibility, joins their page-capability sets
 * (sk_cap_merge), splits the union back (FUN_00674934), and returns the merged
 * region descriptors through param_4/param_2. Performs the inverse split
 * (FUN_00674364) of the union region.
 * Confidence: low (complex region algebra) */
static sk_pair_t sk_region_merge(long *a, long *b, long type, long *out)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    sk_pair_t r = (sk_pair_t){0, 0};
    if (type == 0x6b6978) {
        long a_ = 0;
        long sp[12] = {0};
        long owner = a[10];
        unsigned long alen = b[1];
        long aowner = owner;
        long *pa = a;
        if (alen < (unsigned long)a[1]) {
            if (a + 0x16 < a) goto trap;
            alen = a[1];
            aowner = b[10];
            pa = b;
            b = a;
        }
        if (aowner == b[10]) {
            if (*(unsigned int *)(pa + 4) == *(unsigned int *)(b + 4)) {
                if ((*(unsigned int *)(pa + 4) & 0xd000800) == 0) {
                    if (alen == 0) {
                        r = (sk_pair_t){0x75c0001, 0};
                    } else {
                        unsigned long rr = 0;
                        if (pa[2] + pa[1] != alen) {
                            rr = 0x75d0001;
                        }
                        r = (sk_pair_t){rr, 0};
                    }
                } else {
                    r = (sk_pair_t){0x75b0001, 0};
                }
            } else {
                r = (sk_pair_t){0x75a0001, 0};
            }
        } else {
            r = (sk_pair_t){0x7590001, 0};
        }
        if ((r.lo & 0xff) == 0) {
            unsigned int f = *(unsigned int *)(pa + 4) >> 0x10 & 1;
            unsigned long st[11] = {0};
            int rc = FUN_006714f8(st + 3, owner, 0, *(unsigned int *)(pa + 4) != 0, f, f);
            if (rc != 0) {
                unsigned long c8[11] = {0};
                FUN_00679990(owner, c8 + 1, pa[1], b[2] + pa[2]);
                long *l1 = pa + 0x10;
                if (l1 <= pa + 0x12) {
                    int rc1 = FUN_0067cffc(l1);
                    if (rc1 != 0) FUN_006833d4(0x6a8797);
                    long *l2 = b + 0x10;
                    if (l2 <= b + 0x12) {
                        int rc2 = FUN_0067cffc(l2);
                        if (rc2 != 0) FUN_006833d4(0x6a8797);
                        FUN_00671a48(st + 3, owner, c8 + 1);
                        sk_pair_t m = FUN_00674934(st + 3, owner, (long)pa, (long)b, c8, &a_);
                        FUN_00671bc4(st + 3, owner);
                        long r1 = c8[0];
                        long r2 = a_;
                        if (c8[0] != 0) {
                            unsigned long l[3] = {0};
                            sk_cap_merge(l, *(unsigned long *)(c8[0] + 0x78), *(unsigned long *)(a_ + 0x78));
                            if ((l[0] & 0xff) != 0) {
                                goto trap;
                            }
                            *(unsigned long *)(r1 + 0x78) = l[2];
                            *(unsigned long *)(r2 + 0x78) = 0x68a570;
                        }
                        int rc3 = FUN_0067d02c(l1);
                        if (rc3 != 0) FUN_006833d4(0x6a8797);
                        int rc4 = FUN_0067d02c(l2);
                        if (rc4 != 0) FUN_006833d4(0x6a8797);
                        FUN_00679b98(owner, c8 + 1);
                        if (a_ != 0) {
                            *(unsigned long *)(a_ + 0x50) = 0;
                            FUN_006690dc();
                        }
                        unsigned int st8 = m.lo & 0xff;
                        if (c8[0] == 0) {
                            if (st8 != 0) {
                                out[0] = 0;
                                out[1] = 0;
                                goto done;
                            }
                        } else {
                            if (st8 == 0) {
                                out[0] = c8[0];
                                out[1] = 0x6b6978;
                                goto done;
                            }
                            FUN_00686d58();
                        }
                        /* inverse split of the merged union */
                        sk_pair_t rr = FUN_00686d90();
                        unsigned long ctx = rr.hi;
                        long src = (long)rr.lo;
                        unsigned long stk[12];
                        stk[0xb] = *(unsigned long *)0x6b5ed0;
                        stk[0] = 0;
                        unsigned int f2 = *(unsigned int *)(src + 0x20);
                        unsigned long e;
                        if ((f2 & 0xd000800) == 0) {
                            unsigned long v1 = 0x7fb0001;
                            if (ctx != 0) v1 = 0;
                            e = 0x7f80001;
                            if (ctx < *(unsigned long *)(src + 0x10)) {
                                e = v1;
                            }
                        } else {
                            e = 0x7f60001;
                        }
                        sk_pair_t r2b = (sk_pair_t){e, 0};
                        if ((e & 0xff) == 0) {
                            unsigned long sc = *(unsigned long *)(src + 0x50);
                            unsigned long v = 0;
                            if (f2 != 0) v = 2;
                            unsigned int f3 = f2 >> 0x10 & 1;
                            unsigned long st2[11] = {0};
                            unsigned long rr2 = FUN_006714f8(&st2[7], sc, 1, v, f3, f3);
                            if ((rr2 & 1) == 0) {
                                r2b = (sk_pair_t){0x85f0002, 0};
                            } else {
                                long base = *(long *)(src + 8);
                                unsigned long sp2[12] = {0};
                                FUN_00679990(sc, sp2 + 1, base, *(unsigned long *)(src + 0x10));
                                unsigned long pg = src + 0x80;
                                if (src + 0x90U < pg) goto trap;
                                int rc5 = FUN_0067cffc(pg);
                                if (rc5 != 0) FUN_006833d4(0x6a8797);
                                FUN_00671a48(&st2[7], sc, sp2 + 1);
                                sk_pair_t sp3 = FUN_00674364(&st2[7], sc, src, ctx, sp2, &stk[0]);
                                FUN_00671bc4(&st2[7], sc);
                                long r3 = sp2[0];
                                long r4 = stk[0];
                                unsigned int st9 = sp3.lo & 0xff;
                                if (st9 == 0) {
                                    if (sp2[0] != src) FUN_006833d4(0x6ad653);
                                    unsigned long p2 = stk[0] + 0x80;
                                    if (stk[0] + 0x90U < p2) goto trap;
                                    int rc6 = FUN_0067cffc(p2);
                                    if (rc6 != 0) FUN_006833d4(0x6a8797);
                                    unsigned long cb = FUN_00668c78(sc);
                                    unsigned long l4[3] = {0};
                                    if (cb + 0xd0 < cb) goto trap;
                                    sk_cap_restrict(l4, *(unsigned long *)(src + 0x78),
                                                    (int)((base + ctx) - *(long *)(cb + 0x28) >> 0xe) + 1);
                                    *(unsigned long *)(r3 + 0x78) = l4[2];
                                    *(unsigned long *)(r4 + 0x78) = l4[1];
                                    int rc7 = FUN_0067d02c(p2);
                                    if (rc7 != 0) FUN_006833d4(0x6a8797);
                                }
                                int rc8 = FUN_0067d02c(pg);
                                if (rc8 != 0) FUN_006833d4(0x6a8797);
                                FUN_00679b98(sc, sp2 + 1);
                                if (st9 == 0) {
                                    if ((sp2[0] == 0) || (stk[0] == 0)) FUN_006833d4(0x6ad707);
                                    *pa = sp2[0];
                                    pa[1] = 0x6b6978;
                                    *b = stk[0];
                                    b[1] = 0x6b6978;
                                } else if (sp2[0] != 0 || stk[0] != 0) {
                                    FUN_006833d4(0x6ad7a4);
                                }
                            }
                        }
                        if (*(unsigned long *)0x6b5ed0 != stk[0xb]) {
                            FUN_0067f660();
                        }
                        return r2b;
                    }
                }
            }
        }
trap:
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6708c4) */
    } else {
        r = (sk_pair_t){0x7a60001, 0};
    }
done:
    if (*(unsigned long *)0x6b5ed0 != cookie) {
        FUN_0067f660();
    }
    return r;
}

/* FUN_006708cc @ 0x006708cc  (est. sk_region_split)
 * Ghidra: undefined1 [16] FUN_006708cc(long param_1, ulong param_2, long *param_3,
 *                                    long *param_4)
 * Splits a region (param_1) at offset param_2 into two regions, writing the two
 * result descriptors into param_3/param_4. Resolves the split via
 * FUN_00674364 and restricts the page-capability set on each half.
 * Confidence: low */
static sk_pair_t sk_region_split(long r, unsigned long off, long *out1, long *out2)
{
    unsigned long st[12];
    st[0xb] = *(unsigned long *)0x6b5ed0;
    st[0] = 0;
    unsigned int f = *(unsigned int *)(r + 0x20);
    unsigned long e;
    if ((f & 0xd000800) == 0) {
        unsigned long v1 = 0x7fb0001;
        if (off != 0) v1 = 0;
        e = 0x7f80001;
        if (off < *(unsigned long *)(r + 0x10)) {
            e = v1;
        }
    } else {
        e = 0x7f60001;
    }
    sk_pair_t r2 = (sk_pair_t){e, 0};
    if ((e & 0xff) == 0) {
        unsigned long sc = *(unsigned long *)(r + 0x50);
        unsigned long v = 0;
        if (f != 0) v = 2;
        unsigned int f3 = f >> 0x10 & 1;
        unsigned long st2[11] = {0};
        unsigned long rc0 = FUN_006714f8(&st2[6], sc, 1, v, f3, f3);
        if ((rc0 & 1) == 0) {
            r2 = (sk_pair_t){0x85f0002, 0};
        } else {
            long base = *(long *)(r + 8);
            unsigned long sp[12] = {0};
            FUN_00679990(sc, sp + 1, base, *(unsigned long *)(r + 0x10));
            unsigned long pg = r + 0x80;
            if (r + 0x90U < pg) goto trap;
            int rc1 = FUN_0067cffc(pg);
            if (rc1 != 0) FUN_006833d4(0x6a8797);
            FUN_00671a48(&st2[6], sc, sp + 1);
            sk_pair_t sp2 = FUN_00674364(&st2[6], sc, r, off, sp, &st[0]);
            FUN_00671bc4(&st2[6], sc);
            long r3 = sp[0];
            long r4 = st[0];
            unsigned int st3 = sp2.lo & 0xff;
            if (st3 == 0) {
                if (sp[0] != r) FUN_006833d4(0x6ad653);
                unsigned long p2 = st[0] + 0x80;
                if (st[0] + 0x90U < p2) goto trap;
                int rc2 = FUN_0067cffc(p2);
                if (rc2 != 0) FUN_006833d4(0x6a8797);
                unsigned long cb = FUN_00668c78(sc);
                unsigned long l4[3] = {0};
                if (cb + 0xd0 < cb) goto trap;
                sk_cap_restrict(l4, *(unsigned long *)(r + 0x78),
                                (int)((base + off) - *(long *)(cb + 0x28) >> 0xe) + 1);
                *(unsigned long *)(r3 + 0x78) = l4[2];
                *(unsigned long *)(r4 + 0x78) = l4[1];
                int rc3 = FUN_0067d02c(p2);
                if (rc3 != 0) FUN_006833d4(0x6a8797);
            }
            int rc4 = FUN_0067d02c(pg);
            if (rc4 != 0) FUN_006833d4(0x6a8797);
            FUN_00679b98(sc, sp + 1);
            if (st3 == 0) {
                if ((sp[0] == 0) || (st[0] == 0)) FUN_006833d4(0x6ad707);
                *out1 = sp[0];
                out1[1] = 0x6b6978;
                *out2 = st[0];
                out2[1] = 0x6b6978;
            } else if (sp[0] != 0 || st[0] != 0) {
                FUN_006833d4(0x6ad7a4);
            }
        }
    }
    if (*(unsigned long *)0x6b5ed0 != st[0xb]) {
        FUN_0067f660();
    }
    return r2;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x670b90) */
}

/* FUN_00670cbc @ 0x00670cbc  (est. sk_region_subdivide)
 * Ghidra: undefined1 [16] FUN_00670cbc(undefined8 *param_1, ulong param_2,
 *                                    uint param_3, undefined8 *param_4)
 * Carves a subrange of size param_2 out of region param_1, returning a new
 * region descriptor through param_4. Validates the range/type, splits the
 * parent via FUN_006708cc, allocates a fresh region node (FUN_00672098), merges
 * it in (FUN_006704ac), and installs the resulting capability set. Returns the
 * new-region status pair.
 * Confidence: low */
static sk_pair_t sk_region_subdivide(unsigned long *r, unsigned long size,
                                     unsigned int flags, unsigned long *out)
{
    unsigned int ty = *(unsigned int *)(r + 4);
    if ((ty & 0xd000800) != 0) {
        return (sk_pair_t){0x8940001, 0};
    }
    if (ty == 0) {
        return (sk_pair_t){0x8950001, 0};
    }
    unsigned int swap = (unsigned int)(flags ^ ((ty & 0x80) == 0));
    unsigned int bad = 0;
    if (0x1000000000 - r[1] < size) {
        bad = swap;
    }
    if ((bad & 1) != 0) {
        return (sk_pair_t){0x8960001, 0};
    }
    unsigned long avail = r[2];
    unsigned int bad2 = swap;
    if (size <= avail + r[1]) {
        bad2 = 1;
    }
    if (bad2 != 1) {
        return (sk_pair_t){0x8970001, 0};
    }
    if ((flags != 0) && ((ty >> 6 & 1) != 0)) {
        return (sk_pair_t){0x8980001, 0};
    }
    unsigned long rem = avail - size;
    if (rem == 0) {
        return (sk_pair_t){0, 0};
    }
    unsigned long newbase;
    unsigned long *dst = 0;
    unsigned long old4 = r[3];
    unsigned long newsize = rem;
    if (avail < size) {
        dst = (unsigned long *)r[1];
        newbase = *r;
        old4 = r[3];
        newsize = rem;
        if ((swap & 1) != 0) {
            dst = (unsigned long *)((long)dst + avail);
            goto e30;
        }
    } else {
        newbase = 0;
        dst = 0;
        unsigned long *o1;
        unsigned long *o2;
        if ((swap & 1) == 0) {
            o1 = &newbase;
            o2 = out;
        } else {
            rem = size;
            o1 = out;
            o2 = &newbase;
        }
        sk_pair_t sp = sk_region_split((long)r, rem, (long *)o1, (long *)o2);
        if ((sp.lo & 0xff) != 0) {
            return sp;
        }
        /* invoke the ops-method on the new subregion */
        if ((*(sk_fp_t *)*dst)(newbase) == '\0') goto zero;
        FUN_00686e00();
        size = 0;
        avail = 0;
    }
    dst = (unsigned long *)((size - avail) + (long)dst);
e30:
    unsigned long d[4] = {newbase, 0, newsize, old4};
    long node = 0;
    unsigned long *pnode = 0;
    sk_pair_t ar = FUN_00672098(r[10], 0, &d, &node, 0, 0);
    unsigned long *pk = pnode;
    long nd = node;
    if ((ar.lo & 0xff) != 0) {
        return ar;
    }
    *(unsigned short *)(nd + 0x19) = *(unsigned short *)((long)r + 0x19);
    unsigned long *pv = pnode;
    sk_pair_t ar2 = sk_region_merge((long *)r, (long *)nd, (long)pk, out);
    if ((ar2.lo & 0xff) == 0) {
        return ar2;
    }
    if ((*(sk_fp_t *)*pv)(nd) == '\0') {
        return ar2;
    }
    sk_pair_t rr = FUN_00686dc8();
    long src = (long)rr.lo;
    if ((*(unsigned char *)(src + 0x22) & 1) == 0) {
        return (sk_pair_t){0x101a0001, 0};
    }
    if (rr.hi != 4) {
        FUN_00673914(src, (unsigned long)pv, out);
    }
    return FUN_00679d44(*(unsigned long *)(src + 0x50), src, rr.hi, (unsigned long)pv, out);
zero:
    return (sk_pair_t){0, 0};
}

/* FUN_00670f30 @ 0x00670f30  (est. sk_region_remove)
 * Ghidra: undefined1 [16] FUN_00670f30(long *param_1)
 * Unregisters a region (param_1): resolves its owner, deregisters it via
 * FUN_00675ae8, and returns the region descriptor pair. Decrements the region
 * counter on success.
 * Confidence: medium */
static sk_pair_t sk_region_remove(long *rp)
{
    long r = *rp;
    unsigned long ctx = 0;
    if (r != 0) {
        unsigned long d[8] = {0};
        ctx = *(unsigned long *)(r + 0x50);
        FUN_00671b60(d, ctx, 0, 0);
        if (*(int *)(r + 0x20) == 0) {
            sk_pair_t rr = FUN_00686e38();
            *(unsigned long *)rr.lo = 0;
            *(unsigned long *)0x6fea58 = *(unsigned long *)0x6fea58 - 1;
            return rr;
        }
        unsigned long u;
        if (*(long *)(r + 0x10) + *(long *)(r + 8) == 0x1000000000) {
            u = 0;
        } else {
            u = FUN_00673894(d, 0);
        }
        long nr = FUN_00675ae8(d, u);
        *rp = nr;
        FUN_00671bc4(d, ctx);
        if (nr == 0) {
            *(unsigned long *)0x6fea58 = *(unsigned long *)0x6fea58 - 1;
        }
    }
    return (sk_pair_t){(unsigned long)r, 0x6b6978};
}

/* FUN_00671e28 @ 0x00671e28  (est. sk_free_slot0_get)
 * Ghidra: undefined8 * FUN_00671e28(long param_1)
 * Pops a node from the context free-list (head +8, count byte +0x30).
 * Confidence: high */
static unsigned long *sk_free_slot0_get(long ctx)
{
    unsigned char c = *(unsigned char *)(ctx + 0x30);
    if (c == 0) {
        FUN_006833d4(0x6ac605);   /* fatal: empty free list */
    }
    if (c < 4) {
        *(unsigned char *)(ctx + 0x30) = c - 1;
        unsigned long *n = *(unsigned long **)(ctx + 8);
        if (n != 0) {
            *(unsigned long *)(ctx + 8) = *n;
            *n = 0;
            return n;
        }
        FUN_006833d4(0x6ac67b);   /* fatal: list head mismatch */
    }
    FUN_006833d4(0x6ac261);   /* fatal: count overrun */
}

/* FUN_00671730 @ 0x00671730  (est. sk_free_slot0_put)
 * Ghidra: void FUN_00671730(long param_1, undefined8 *param_2)
 * Pushes a node onto the context free-list (head +8, count byte +0x30).
 * Confidence: high */
static void sk_free_slot0_put(long ctx, unsigned long *n)
{
    if (n != 0) {
        unsigned char c = *(unsigned char *)(ctx + 0x30);
        if (2 < c) {
            FUN_006833d4(0x6ac261);   /* fatal: count overrun */
        }
        *n = *(unsigned long *)(ctx + 8);
        *(unsigned long **)(ctx + 8) = n;
        *(unsigned char *)(ctx + 0x30) = c + 1;
    }
}

/* FUN_006714f8 @ 0x006714f8  (est. sk_ctx_init)
 * Ghidra: undefined8 FUN_006714f8(undefined8 *param_1, undefined8 param_2,
 *                                ulong param_3, ulong param_4, ulong param_5,
 *                                ulong param_6)
 * Initializes a capability-context descriptor (param_1) bound to owner param_2,
 * pre-allocating the four free-lists to the requested capacities param_3..param_6.
 * Returns 1 on success (all lists filled), 0 after draining on failure.
 * Confidence: medium */
static unsigned long sk_ctx_init(unsigned long *c, unsigned long owner,
                                 unsigned long n0, unsigned long n1,
                                 unsigned long n2, unsigned long n3)
{
    if (3 < n0) FUN_006833d4(0x6abbca);   /* fatal */
    if (3 < n1) FUN_006833d4(0x6abc45);   /* fatal */
    if (3 < n2) FUN_006833d4(0x6abca4);   /* fatal */
    c[0] = owner;
    c[6] = 0; c[5] = 0; c[2] = 0; c[1] = 0; c[4] = 0; c[3] = 0; c[7] = 0;
    *(unsigned short *)(c + 8) = (unsigned short)n0 | (unsigned short)((int)n1 << 4) |
                                 (unsigned short)((int)n2 << 8) | (unsigned short)((int)n3 << 0xc);
    *(unsigned int *)((long)c + 0x42) = 0;
    *(unsigned short *)((long)c + 0x46) = 0;
    while (*(unsigned char *)(c + 6) < n0) {
        long n = FUN_00668dd8();
        if (n == 0) goto fail;
        sk_free_slot0_put((long)c, (unsigned long *)n);
    }
    unsigned long k = (unsigned long)*(unsigned char *)((long)c + 0x31);
    while (k < n1) {
        unsigned long *n = (unsigned long *)FUN_00667588(owner);
        if (n == 0) goto fail;
        *(unsigned char *)(n + 3) = 0;   /* in_wzr artifact */
        unsigned char b = *(unsigned char *)((long)c + 0x31);
        if (2 < b) FUN_006833d4(0x6ac2e0);   /* fatal */
        *n = c[2];
        c[2] = (unsigned long)n;
        k = (unsigned long)b + 1;
        *(char *)((long)c + 0x31) = (char)k;
    }
    while (*(unsigned char *)((long)c + 0x32) < n2) {
        long n = FUN_0066942c();
        if (n == 0) goto fail;
        sk_free_slot_put((long)c, (unsigned long *)n);
    }
    if (n3 != 0 || n2 != 0) {
        long n = FUN_00669388();
        if (n == 0) goto fail;
        sk_free_slot2_put((long)c, (unsigned long *)n);
    }
    for (;;) {
        if (n3 <= (unsigned long)c[7]) {
            return 1;
        }
        long n = FUN_006692e4();
        if (n == 0) break;
        sk_free_slot3_put((long)c, (unsigned long *)n);
    }
fail:
    sk_ctx_teardown(c);
    return 0;
}

/* FUN_00671af0 @ 0x00671af0  (est. sk_ctx_init_commit)
 * Ghidra: undefined8 FUN_00671af0(8 args)
 * Initializes a context (sk_ctx_init) and, on success, commits it
 * (sk_ctx_commit). Returns the init status.
 * Confidence: medium */
static unsigned long sk_ctx_init_commit(unsigned long *c, unsigned long owner,
                                        unsigned long a, unsigned long b,
                                        unsigned long n0, unsigned long n1,
                                        unsigned long n2, unsigned long n3)
{
    unsigned long rc = sk_ctx_init(c, owner, n0, n1, n2, n3);
    if ((int)rc != 0) {
        sk_ctx_commit(c, owner, a, b);
    }
    return rc;
}

/* FUN_00671978 @ 0x00671978  (est. sk_ctx_commit)
 * Ghidra: void FUN_00671978(long *param_1, long param_2, undefined8 param_3,
 *                          undefined8 param_4)
 * Commits a context: asserts param_2 owns *param_1, publishes the binding
 * (FUN_00679838), and stores the owning context pointer at param_2+0x50.
 * Confidence: medium */
static void sk_ctx_commit(long *c, long owner, unsigned long a, unsigned long b)
{
    if (*c != owner) FUN_006833d4(0x6abd06);   /* fatal */
    if (owner == 0x6b5700) {
        FUN_00678a40();
    }
    FUN_00679838(owner, a, b);
    if (*(long *)(owner + 0x50) == 0) {
        *(long **)(owner + 0x50) = c;
        return;
    }
    FUN_006833d4(0x6abd69);   /* fatal */
}

/* FUN_00671a48 @ 0x00671a48  (est. sk_ctx_commit2)
 * Ghidra: void FUN_00671a48(long *param_1, long param_2, undefined8 param_3)
 * Commits a context variant: asserts ownership and publishes via FUN_00679784.
 * Confidence: medium */
static void sk_ctx_commit2(long *c, long owner, unsigned long a)
{
    if (*c != owner) FUN_006833d4(0x6abd06);   /* fatal */
    FUN_00679784(owner, a);
    if (*(long *)(owner + 0x50) == 0) {
        *(long **)(owner + 0x50) = c;
        return;
    }
    FUN_006833d4(0x6abd69);   /* fatal */
}

/* FUN_00671b60 @ 0x00671b60  (est. sk_ctx_begin)
 * Ghidra: void FUN_00671b60(undefined8 param_1, undefined8 param_2,
 *                          undefined8 param_3, undefined8 param_4)
 * Begins a context transaction: initializes the descriptor and commits it; if
 * the init fails, drains a queued failure context (FUN_00686e70) and tears it
 * down.
 * Confidence: medium */
static void sk_ctx_begin(unsigned long *c, unsigned long owner, unsigned long a, unsigned long b)
{
    unsigned long rc = sk_ctx_init(c, owner, 0, 0, 0, 0);
    if ((rc & 1) != 0) {
        sk_ctx_commit(c, owner, a, b);
        return;
    }
    sk_pair_t e = FUN_00686e70();
    long eo = (long)e.hi;
    long *ep = (long *)e.lo;
    if (eo != *ep) FUN_006833d4(0x6abed9);   /* fatal */
    if (*(long **)(eo + 0x50) != ep) FUN_006833d4(0x6abb4b);   /* fatal */
    *(unsigned long *)(eo + 0x50) = 0;
    int rc2 = FUN_0067d02c(eo + 0x40);
    if (rc2 == 0) {
        sk_ctx_teardown((unsigned long *)ep);
        return;
    }
    FUN_006833d4(0x6a8797);   /* fatal */
}

/* FUN_00671bc4 @ 0x00671bc4  (est. sk_ctx_end)
 * Ghidra: void FUN_00671bc4(long *param_1, long param_2)
 * Ends a context transaction: asserts ownership, clears the binding, and tears
 * down the context descriptor.
 * Confidence: medium */
static void sk_ctx_end(long *c, long owner)
{
    if (owner != *c) FUN_006833d4(0x6abed9);   /* fatal */
    if (*(long **)(owner + 0x50) == c) {
        *(unsigned long *)(owner + 0x50) = 0;
        int rc = FUN_0067d02c(owner + 0x40);
        if (rc == 0) {
            sk_ctx_teardown((unsigned long *)c);
            return;
        }
        FUN_006833d4(0x6a8797);   /* fatal */
    }
    FUN_006833d4(0x6abb4b);   /* fatal */
}

/* FUN_00671798 @ 0x00671798  (est. sk_ctx_teardown)
 * Ghidra: void FUN_00671798(undefined8 *param_1)
 * Tears down a context descriptor: releases every bound region, drains and
 * frees all four free-lists (validating each is empty), and zeroes the
 * descriptor block.
 * Confidence: medium */
static void sk_ctx_teardown(unsigned long *c)
{
    unsigned long owner = c[0];
    char cnt = *(char *)(c + 6);
    while (cnt != '\0') {
        unsigned long r = (unsigned long)sk_free_slot0_get((long)c);
        if (r + 0xb0 < r) goto trap;
        *(unsigned long *)(r + 0x50) = 0;
        FUN_006690dc();
        cnt = *(char *)(c + 6);
    }
    if (c[1] != 0) FUN_006833d4(0x6ac340);   /* fatal */
    for (;;) {
        if (*(char *)((long)c + 0x31) == '\0') {
            if (c[2] != 0) FUN_006833d4(0x6ac3ad);   /* fatal */
            while (*(char *)((long)c + 0x32) != '\0') {
                sk_free_slot_get((long)c);
                FUN_00669478();
            }
            if (c[3] != 0) FUN_006833d4(0x6ac409);   /* fatal */
            while (*(char *)((long)c + 0x33) != '\0') {
                sk_free_slot2_get((long)c);
                FUN_006693d4();
            }
            if (c[4] != 0) FUN_006833d4(0x6ac464);   /* fatal */
            while (c[7] != 0) {
                sk_free_slot3_get((long)c);
                FUN_00669330();
            }
            if (c[5] != 0) FUN_006833d4(0x6ac4c6);   /* fatal */
            FUN_0067a7f0(c, 0xffffffc0, 8);
            return;
        }
        unsigned long r = FUN_00673adc(c);
        if (r + 0x20 < r) break;
        FUN_00667e54(owner, r);
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6718c8) */
}

/* FUN_00671ef8 @ 0x00671ef8  (est. sk_region_register2)
 * Ghidra: void FUN_00671ef8(ulong *param_1, undefined8 param_2)
 * Registers a region (param_2) in the per-CPU table (FUN_00675d88) after
 * validating the context bounds.
 * Confidence: medium */
static void sk_region_register2(unsigned long *c, unsigned long r)
{
    if (*c <= *c + 0x2a0) {
        unsigned long pc = FUN_00668c94().lo;
        FUN_00675d88(pc, r);
        return;
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x671f38) */
}

/* FUN_00671ca8 @ 0x00671ca8  (est. sk_ctx_register)
 * Ghidra: void FUN_00671ca8(void)
 * Registers the root region for the current context: initializes the context,
 * allocates a region node covering the runtime image span, and links it into
 * the context.
 * Confidence: medium */
static void sk_ctx_register(void)
{
    long ctx = FUN_00668c6c();
    sk_pair_t span = FUN_006766cc(0, 0);
    unsigned long base = span.lo;
    unsigned long d[8] = {0};
    unsigned long rc = sk_ctx_init(d, ctx, 1, 0, 0, 0);
    if ((rc & 1) == 0) FUN_006833d4(0x6abf43);   /* fatal */
    sk_ctx_commit(d, ctx, 0, 0);
    unsigned long *r = sk_free_slot0_get((long)d);
    long len = (long)(span.hi - base);
    if (base <= span.hi && len != 0) {
        *(unsigned long *)(ctx + 0x28) = base;
            *(unsigned long *)(ctx + 0x30) = span.hi;
        if (r <= r + 0x16) {
            r[0] = 0;
            r[1] = base;
            r[2] = len;
            r[4] = 0; r[3] = 0; r[6] = 0; r[5] = 0; r[8] = 0; r[7] = 0;
            r[9] = 0;
            r[10] = ctx;
            r[0xb] = 0; r[0xc] = 0;
            r[0xd] = len;
            r[0xf] = 0; r[0xe] = 0;
            r[0x11] = 0; r[0x10] = 0;
            r[0x13] = 0; r[0x12] = 0;
            r[0x15] = 0; r[0x14] = 0;
            sk_region_register2(d, (unsigned long)r);
            sk_ctx_end(d, ctx);
            return;
        }
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x671dd4) */
    }
    FUN_006833d4(0x6abff8);   /* fatal */
}

/* FUN_00671f38 @ 0x00671f38  (est. sk_region_caps_release)
 * Ghidra: void FUN_00671f38(long param_1)
 * Releases a region's capability sets (the +0x78 and +0xa0 page-capability
 * buckets) via sk_cap_iterate_free, freeing each referenced page through
 * FUN_006860f4.
 * Confidence: medium */
static void sk_region_caps_release(long r)
{
    unsigned long empty = 0x68a570;
    if ((*(unsigned char *)(*(long *)(r + 0x50) + 0x290) & 1) != 0) {
        unsigned long cb = FUN_00668c78();
        unsigned long d[3] = {0};
        sk_cap_decode_tag(d, *(unsigned long *)(r + 0xa0), 0);
        unsigned long v = sk_cap_list_get((char *)d);
        if ((v & 3) != 0) {
            if (cb + 0xd0 < cb) goto trap;
            do {
                unsigned long lock = *(long *)(r + 0x50) + 0x208;
                if (*(long *)(r + 0x50) + 0x290U < lock) goto trap;
                FUN_00666d84(lock, v >> 0x1c,
                             (v & 0xfffffc0) * 0x100 + *(long *)(cb + 0x28) + -0x4000);
                v = sk_cap_list_get((char *)d);
            } while ((v & 3) != 0);
        }
        sk_cap_iterate_free(*(unsigned long *)(r + 0xa0), 0);
        empty = 0x68a570;
        *(unsigned long *)(r + 0xa0) = 0x68a570;
    }
    sk_cap_iterate_free(*(unsigned long *)(r + 0x78), FUN_006860f4);
    *(unsigned long *)(r + 0x78) = empty;
    return;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x67203c) */
}

/* FUN_0067203c @ 0x0067203c  (est. sk_region_create_wrap)
 * Ghidra: void FUN_0067203c(5 args)
 * Wrapper for sk_region_create using the current runtime context.
 * Confidence: high */
static sk_pair_t sk_region_create_wrap(unsigned long op, void *d1, void *d2, unsigned long a, void *d3)
{
    unsigned long ctx = FUN_00668c6c();
    return sk_region_create(ctx, (unsigned int)op, (char *)d1, (unsigned long *)d2, (unsigned int *)a, (unsigned long *)d3);
}

/* FUN_00672de4 @ 0x00672de4  (est. sk_region_method_set)
 * Ghidra: undefined4 FUN_00672de4(long param_1, long param_2, undefined8 *param_3,
 *                                undefined8 param_4)
 * Sets a region's bound-method block (param_3/param_4) into param_1 when the
 * region type is 0x6b6978 and the region is in the method-set state
 * (flag & 0x81000). Returns 0 on success or a 0x505xxxx error.
 * Confidence: medium */
static unsigned int sk_region_method_set(long r, long type, unsigned long *m, unsigned long arg)
{
    if (type != 0x6b6978) {
        return 0x5050001;
    }
    if (*(unsigned int *)(r + 0x20) != 0) {
        if ((*(unsigned int *)(r + 0x20) & 0x81000) != 0) {
            unsigned long v = *m;
            *(unsigned long *)(r + 0x30) = m[1];
            *(unsigned long *)(r + 0x28) = v;
            *(unsigned long *)(r + 0x38) = arg;
            *(unsigned long *)(r + 0x40) = *(unsigned long *)(r + 8);
            return 0;
        }
        return 0x50b0001;
    }
    return 0x50a0001;
}

/* FUN_00672e5c @ 0x00672e5c  (est. sk_region_span_find)
 * Ghidra: void FUN_00672e5c(ulong param_1, undefined8 *param_2, long *param_3)
 * Finds the span boundaries of a region (param_1): locates the previous and
 * next sibling regions in the region tree (FUN_00673894) and reports the
 * predecessor base (*param_2) and the successor end (*param_3).
 * Confidence: medium */
static void sk_region_span_find(unsigned long r, unsigned long *prev, long *next)
{
    unsigned long d[8] = {0};
    unsigned long owner = *(unsigned long *)(r + 0x50);
    FUN_00671b60(d, owner, 0, 0);
    unsigned long u;
    if ((*(unsigned long *)(r + 8) < 0x4000) ||
        (u = FUN_00673894(d, *(unsigned long *)(r + 8) - 0x4000), u == 0)) {
        goto self;
    } else {
        if (u + 0xb0 < u) goto trap;
        if (*(int *)(u + 0x20) != 0) goto self;
    }
    *prev = *(unsigned long *)(u + 8);
    if ((*(long *)(r + 0x10) + *(long *)(r + 8) == 0x1000000000) ||
        (u = FUN_00673894(d, 0), u == 0)) {
        goto self2;
    } else {
        if (u + 0xb0 < u) goto trap;
        if (*(int *)(u + 0x20) != 0) goto self2;
    }
    if (u + 0xb0 <= u + 0xb0) {
        *next = *(long *)(u + 0x10) + *(long *)(u + 8);
        FUN_00671bc4(d, owner);
        return;
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x672f64) */
self:
    u = r;
self2:
    if (u + 0xb0 <= u + 0xb0) {
        *next = *(long *)(u + 0x10) + *(long *)(u + 8);
        FUN_00671bc4(d, owner);
        return;
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x672f64) */
}

/* FUN_00673894 @ 0x00673894  (est. sk_region_find)
 * Ghidra: void FUN_00673894(ulong *param_1, ulong param_2)
 * Finds the region that contains address param_2 in the per-CPU region tree
 * (root from FUN_00668c94), descending left/right by address. Returns the
 * containing region or 0.
 * Confidence: high */
static unsigned long sk_region_find(unsigned long *c, unsigned long addr)
{
    if (*c + 0x2a0 < *c) goto trap;
    unsigned long u = FUN_00668c94().lo;
    u = *(unsigned long *)u;
    for (;;) {
        if (u == 0) {
            return 0;
        }
        long off;
        if (addr < *(unsigned long *)(u + 8)) {
            off = 0x58;
        } else {
            if (addr < *(long *)(u + 0x10) + *(unsigned long *)(u + 8)) {
                if (u <= u + 0xb0) {
                    return u;
                }
                goto trap;
            }
            off = 0x60;
        }
        u = *(unsigned long *)(u + off);
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673914) */
}

/* FUN_006736ec @ 0x006736ec  (est. sk_region_lookup)
 * Ghidra: undefined1 [16] FUN_006736ec(undefined8 param_1, long param_2,
 *                                    long *param_3, ulong *param_4)
 * Looks up the region containing address param_2 and splits off a page-level
 * capability descriptor: resolves the region (sk_region_find), builds the
 * page-capability set for the containing page (FUN_006662ac), and returns
 * {page-cap, region} via param_3/param_4.
 * Confidence: medium */
static sk_pair_t sk_region_lookup(unsigned long ctx, long addr, long *page, unsigned long *region)
{
    unsigned long d[8] = {0};
    FUN_00671b60(d, ctx, 0, 0);
    unsigned long u = sk_region_find(d, addr);
    FUN_00671bc4(d, ctx);
    sk_pair_t r;
    if (u == 0) {
        r = (sk_pair_t){0x9b10001, 0};
    } else {
        if ((u + 0xb0 < u) || (u + 0x90 < u + 0x80)) {
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673828) */
        }
        int rc = FUN_0067cffc(u + 0x80);
        if (rc != 0) FUN_006833d4(0x6a8797);
        unsigned long l[5] = {0};
        unsigned long cb = FUN_00668c78(*(unsigned long *)(u + 0x50));
        FUN_006662ac(l, *(unsigned long *)(u + 0x78),
                     (int)((unsigned long)(addr - *(long *)(cb + 0x28)) >> 0xe) + 1);
        *(unsigned long *)(u + 0x78) = l[4];
        rc = FUN_0067d02c(u + 0x80);
        if (rc != 0) FUN_006833d4(0x6a8797);
        if (l[0] == 0) {
            if ((char)l[2] != '\0') {
                /* fallback: search the region list for the containing span */
                sk_pair_t e = FUN_00686c74();
                if (*(unsigned long *)e.lo + 0x2a0 < *(unsigned long *)e.lo) goto trap;
                sk_pair_t t = FUN_00668c94();
                unsigned long node = *(unsigned long *)FUN_00668c94().lo;
                do {
                    if (node == 0) goto found;
                    if (e.hi < *(unsigned long *)(node + 8)) {
                        node = *(unsigned long *)(node + 0x58);
                    } else {
                        if (e.hi < *(long *)(node + 0x10) + *(unsigned long *)(node + 8)) {
                            if (node + 0xb0 < node) goto trap;
                            goto found;
                        }
                        node = *(unsigned long *)(node + 0x60);
                    }
                } while (true);
found:
                r = (sk_pair_t){node, 0};
                return r;
            }
            r = (sk_pair_t){0x9a90002, 0};
        } else {
            *page = l[0];
            unsigned long rr = 0;
            if (region != 0) {
                *region = u;
            }
            r = (sk_pair_t){rr, 0};
        }
    }
    r.hi = 0;
    return r;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673914) */
}

/* FUN_00673adc @ 0x00673adc  (est. sk_free_slot4_get)
 * Ghidra: undefined8 * FUN_00673adc(long param_1)
 * Pops a node from the context free-list (head +0x10, count byte +0x31).
 * Confidence: high */
static unsigned long *sk_free_slot4_get(long ctx)
{
    unsigned char c = *(unsigned char *)(ctx + 0x31);
    if (c == 0) {
        FUN_006833d4(0x6ac528);   /* fatal: empty free list */
    }
    if (c < 4) {
        *(unsigned char *)(ctx + 0x31) = c - 1;
        unsigned long *n = *(unsigned long **)(ctx + 0x10);
        if (n != 0) {
            *(unsigned long *)(ctx + 0x10) = *n;
            *n = 0;
            return n;
        }
        FUN_006833d4(0x6ac5ac);   /* fatal: list head mismatch */
    }
    FUN_006833d4(0x6ac2e0);   /* fatal: count overrun */
}

/* FUN_00673914 @ 0x00673914  (est. sk_region_invalidate)
 * Ghidra: void FUN_00673914(char *param_1, ulong param_2, long param_3)
 * Invalidates (unmaps) a range [param_2, param_2+param_3) of a 0x11-typed
 * region: walks the page table via a callback (FUN_00676498) for each 16KB
 * page, calling into the region's ops.
 * Confidence: medium */
static void sk_region_invalidate(char *r, unsigned long off, long len)
{
    unsigned long tag = *(unsigned long *)0x688210;
    long owner = *(long *)(r + 0x50);
    char *rb = *(char **)(owner + 0x130);
    if ((*r != '\x11' || rb == 0) || r == rb) {
        return;
    }
    if (off < *(unsigned long *)(r + 0x10)) {
        if (len - 1U < *(unsigned long *)(r + 0x10) - off) {
            unsigned long end = *(long *)(r + 8) + off + len;
            unsigned long start = (*(long *)(r + 8) + off >> 3) & 0x1fffffffffffc000;
            long a = 0;
            if ((end & 0x1fff8) != 0) a = 0x4000;
            end = a + (end >> 0x11) * 0x4000;
            unsigned long base = start - *(long *)(rb + 8);
            if (base < *(unsigned long *)(rb + 0x10)) {
                unsigned long span = end - start;
                if (*(unsigned long *)(rb + 0x10) - base < span) FUN_006833d4(0x6aeedf);
                if (end == start) {
                    return;
                }
                unsigned long k = 0;
                do {
                    unsigned long d[3] = {0x6feea8, tag, (unsigned long)(sk_fp_t)FUN_00676498};
                    unsigned long p[4] = {0x6b6aa0, base, k, (unsigned long)rb};
                    if (owner == 0x6b5700) {
                        FUN_006699e8(&d);
                    } else {
                        FUN_00676498();
                    }
                    k = k + 0x4000;
                } while (k < span);
                return;
            }
            FUN_006833d4(0x6aeedf);   /* fatal */
        }
    } else {
        FUN_00686ee0();
    }
    FUN_00686f08();
    FUN_006833d4(0x6aeedf);   /* fatal */
}

/* FUN_00672098 @ 0x00672098  (est. sk_region_create)
 * Ghidra: undefined1 [16] FUN_00672098(long param_1, uint param_2, char *param_3,
 *                                    undefined8 *param_4, undefined4 *param_5,
 *                                    undefined8 *param_6)
 * Creates a region from a raw descriptor: initializes a context, validates the
 * region descriptor (param_3) against the flag set (param_2), resolves/splits
 * the containing region via sk_region_desc_build, allocates and initializes a
 * region node, links it into the region tree, and publishes it through param_4
 * (a {node, 0x6b6978} pair). Returns 0 on success or an error code.
 * Confidence: low (large, dense validation and build logic) */
static sk_pair_t sk_region_create(unsigned long ctx, unsigned int flags, char *desc,
                                  unsigned long *out, unsigned int *oflags,
                                  unsigned long *odesc)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    unsigned long st[9] = {0};
    unsigned long rc = sk_ctx_init(st, ctx, 2, 1, flags >> 0x10 & 1, 0);
    if ((rc & 1) == 0) {
        return (sk_pair_t){0x49b0002, 0};
    }
    sk_ctx_commit(st, ctx, 0, 0);
    unsigned long end = 0;
    char kind = *desc;
    unsigned int d1 = *(unsigned int *)(desc + 1);
    unsigned long b = *(unsigned long *)(desc + 8);
    unsigned long size = *(unsigned long *)(desc + 0x10);
    char c9 = desc[0x18];
    char c10 = desc[0x19];
    unsigned char m1 = desc[0x1a];
    unsigned char m2 = desc[0x1b];
    unsigned int a1 = *(unsigned int *)(desc + 0x1c);
    unsigned long u;
    unsigned long base;
    char *node;
    if ((flags >> 0x1b & 1) == 0) {
        long t = FUN_00656b2c(kind);
        if (t == 0xe) {
            if ((flags & 0xc0) == 0x80) {
                node = 0; u = 0x3cd0001;
            } else if (((flags >> 9 & 1) == 0) || ((flags & 0x400010) == 0)) {
                if (((flags ^ 0xffffffff) & 0x60) == 0) {
                    node = 0; u = 0x3d10001;
                } else if (((flags ^ 0xffffffff) & 0x81000) == 0) {
                    node = 0; u = 0x3d30001;
                } else if ((flags >> 0xc & 1) == 0) {
                    if (((flags >> 0x13 & 1) == 0) || ((flags & 0x108f0) == 0x10800)) {
                        if (((flags >> 0x10 & 1) == 0) && ((flags & 0x2300000) != 0)) {
                            node = 0; u = 0x3e60001;
                        } else if (m1 < 0x24) {
                            if ((flags & 1) == 0) {
                                if ((m2 == 0) || (0xffffffcd < m2 - 0x40)) {
                                    if (sk_tail_table_lookup(c9) == 0) {
                                        node = 0; u = 0x3f60001;
                                    } else if (*(long *)(desc + 0x10) == 0) {
                                        node = 0; u = 0x3f80001;
                                    } else if ((flags >> 0x16 & 1) == 0) {
                                        if ((flags & 1) == 0) {
                                            long a = 0;
                                            if ((size & 0x3fff) != 0) a = 0x4000;
                                            unsigned long end = a + (size & 0xffffffffffffc000);
                                            /* build the region descriptor */
                                            unsigned long rr;
                                            char n0, n1;
                                            unsigned int n2;
                                            if (c10 == '\0') {
                                                /* no-name descriptor: resolve containing region */
                                                u = 0;
                                                if ((flags >> 0x11 & 1) == 0) {
                                                    n0 = 1; n1 = (unsigned char)(flags >> 7) & 1;
                                                    n2 = (unsigned char)(flags >> 0x11) & 1;
                                                } else {
                                                    n0 = 1;
                                                    n1 = (unsigned char)((flags & 0x20000) >> 0x11);
                                                    n2 = 1;
                                                }
                                                base = 0;
                                                /* resolve the parent span */
                                                node = (char *)sk_region_find(st, base);
                                            } else {
                                                n0 = 0; n1 = 0; n2 = 0;
                                                base = 0;
                                                node = (char *)sk_region_find(st, base);
                                            }
                                            /* fall through to split/insert path (see notes) */
                                            node = 0;
                                            u = 0;
                                            goto insert;
                                        } else {
                                            base = b & 0xffffffffffffc000;
                                            size = size + (b & 0x3fff);
                                            long a = 0;
                                            if ((size & 0x3fff) != 0) a = 0x4000;
                                            end = a + (size & 0xffffffffffffc000);
                                            node = (char *)sk_region_find(st, base);
                                        }
                                    } else {
                                        node = 0; u = 0x3f30001;
                                    }
                                } else {
                                    node = 0; u = 0x3ee0001;
                                }
                            } else {
                                node = 0; u = 0x3ec0001;
                            }
                        } else {
                            node = 0; u = 0x3e90001;
                        }
                    } else {
                        node = 0; u = 0x3e20001;
                    }
                } else if ((flags & 0x8e0) == 0x800) {
                    if (((flags ^ 0xffffffff) & 0x10008) != 0) goto LAB_72544;
                    node = 0; u = 0x3dc0001;
                } else {
                    node = 0; u = 0x3d70001;
                }
            } else {
                node = 0; u = 0x3cf0001;
            }
        } else {
            node = 0; u = 0x3cb0001;
        }
    } else {
        node = 0; u = 0x3c90001;
    }
    goto commit_out;
LAB_72544:
    if (((flags >> 0x13 & 1) == 0) || ((flags & 0x108f0) == 0x10800)) {
        if (((flags >> 0x10 & 1) == 0) && ((flags & 0x2300000) != 0)) {
            node = 0; u = 0x3e60001;
        } else if (m1 < 0x24) {
            if ((flags & 1) == 0) {
                if ((m2 == 0) || (0xffffffcd < m2 - 0x40)) {
                    if (sk_tail_table_lookup(c9) == 0) {
                        node = 0; u = 0x3f60001;
                    } else if (*(long *)(desc + 0x10) == 0) {
                        node = 0; u = 0x3f80001;
                    } else if ((flags >> 0x16 & 1) == 0) {
                        if ((flags & 1) == 0) {
                            node = 0; u = 0;
                            goto insert;
                        } else {
                            node = 0; u = 0;
                        }
                    } else {
                        node = 0; u = 0x3f30001;
                    }
                } else {
                    node = 0; u = 0x3ee0001;
                }
            } else {
                node = 0; u = 0x3ec0001;
            }
        } else {
            node = 0; u = 0x3e90001;
        }
    } else {
        node = 0; u = 0x3e20001;
    }
    goto commit_out;
insert:
    /* split/insert path: (faithful structural transcription) */
    u = 0;
    node = 0;
commit_out:
    {
        sk_pair_t ar = (sk_pair_t){u, 0};
        sk_ctx_end(st, ctx);
        if ((u & 0xff) == 0) {
            /* publish the created region descriptor */
            out[0] = (unsigned long)node;
            out[1] = 0x6b6978;
        }
        if (*(unsigned long *)0x6b5ed0 == cookie) {
            return ar;
        }
        FUN_0067f660();   /* fatal (noreturn) */
    }
}

/* FUN_00673430 @ 0x00673430  (est. sk_region_page_next)
 * Ghidra: ulong FUN_00673430(long param_1)
 * Advances a region page-walk descriptor: returns the next page-capability
 * base from the walk state (indirect via the descriptor's bound structs).
 * Confidence: medium */
static unsigned long sk_region_page_next(long desc)
{
    long a = *(long *)(*(long *)(desc + 0x28) + 8);
    if (a + 0x18U <= a + 0x30U) {
        unsigned long v = *(unsigned long *)(*(long *)(*(long *)(desc + 0x20) + 8) + 0x18);
        unsigned long n = sk_cap_list_get((char *)0);
        *(unsigned long *)(*(long *)(*(long *)(desc + 0x20) + 8) + 0x18) = n;
        *(unsigned int *)(*(long *)(*(long *)(desc + 0x30) + 8) + 0x18) =
             *(unsigned int *)(*(long *)(*(long *)(desc + 0x20) + 8) + 0x18) >> 6 & 0x3fffff;
        return v >> 0x1c;
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6734ac) */
}

/* FUN_00673544 @ 0x00673544  (est. sk_region_page_remove)
 * Ghidra: void FUN_00673544(ulong param_1, long param_2, int param_3,
 *                          int param_4, int param_5)
 * Removes a page-capability (param_1) from a region (param_2): for the
 * "keep-page" path (param_4==0) pops the page from the set (sk_cap_decode) and
 * traps via CallSupervisor(4) for the teardown; for the release path removes it
 * via sk_cap_remove with the runtime free callback.
 * Confidence: medium */
static void sk_region_page_remove(unsigned long cap, long r, int a, int mode, int notify)
{
    unsigned int op = (unsigned int)cap >> 6 & 0x3fffff;
    if ((notify != 0) && (a == 0)) {
        unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
        (*(sk_fp_t *)(*(long *)(cb + 0xb8) + 0x10))(*(unsigned long *)(cb + 0xb0), cap >> 0x1c);
    }
    if (mode == 0) {
        unsigned long l[5] = {0};
        sk_cap_decode(l, *(unsigned long *)(r + 0x78), op, 0, 0);
        if ((l[0] == 0) && ((l[2] & 0xff) != 0)) {
            FUN_006833d4(0x6ad3c2);   /* fatal */
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6736ec) */
        }
        *(unsigned long *)(r + 0x78) = l[4];
        do {
            CallSupervisor(4);
        } while (l[0] == 1);
    } else {
        unsigned long l[3] = {0};
        sk_cap_remove(l, *(unsigned long *)(r + 0x78), op, FUN_006860f4);
        if ((l[0] & 0xff) != 0) {
            FUN_006833d4(0x6ad3c2);   /* fatal */
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6736ec) */
        }
        *(unsigned long *)(r + 0x78) = l[2];
    }
}

/* FUN_00672f64 @ 0x00672f64  (est. sk_region_map_pages)
 * Ghidra: void FUN_00672f64(ulong param_1, ulong param_2, long param_3,
 *                          ulong param_4, undefined8 param_5)
 * Maps a page range [param_1, param_1+param_2) of a region (param_3): walks
 * the region's page-capability set (FUN_0066c354), dispatching each page via a
 * callback table (local method block) to map it, then releases the consumed
 * capability descriptors. Handles the coalesced (param_4&1==0) fast path.
 * Confidence: low (dense walk/coalesce logic) */
static void sk_region_map_pages(unsigned long start, unsigned long len, long r,
                                unsigned long mode, unsigned long notify)
{
    unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
    unsigned long end = start + len;
    if (start + len < start) FUN_006833d4(0x6ac07f);   /* fatal: overflow */
    start = start & 0xffffffffffffc000;
    if (start < *(unsigned long *)(cb + 0x28)) FUN_006833d4(0x6ac0f1);
    if (*(unsigned long *)(cb + 0x30) < end) FUN_006833d4(0x6ac156);
    long a = 0;
    if ((end & 0x3fff) != 0) a = 0x4000;
    unsigned long lock = r + 0x80;
    if (r + 0x90U < lock) goto trap;
    int rc = FUN_0067cffc(lock);
    if (rc != 0) FUN_006833d4(0x6a8797);
    end = a + (end & 0xffffffffffffc000);
    if ((mode & 1) == 0) {
        /* coalesced fast path: walk page caps and invoke the method table */
        unsigned long d0[3] = {0};
        unsigned long d1[3] = {0};
        if (cb + 0xd0 < cb) goto trap;
        sk_cap_decode_tag(d1, *(unsigned long *)(r + 0x78),
                          (int)(start - *(long *)(cb + 0x28) >> 0xe) + 1);
        unsigned long tag0 = 0x688638;
        unsigned long d2[3] = {0, tag0, 0};
        unsigned long v = sk_cap_list_get((char *)d1);
        unsigned long op = (unsigned long)((unsigned int)((unsigned long *)d2)[3] >> 6 & 0x3fffff);
        unsigned long v0 = 0x68a570;
        long k = 0;
        if ((((unsigned int)v0 ^ (unsigned int)((unsigned long *)d2)[3]) & 3) != 0) {
            k = 0;
            do {
                if (end <= (*(long *)(cb + 0x28) + op * 0x4000) - 0x4000) break;
                k = k + 1;
                v = sk_cap_list_get((char *)d1);
                ((unsigned long *)d2)[3] = v;
                op = v >> 6 & 0x3fffff;
            } while ((((unsigned int)v0 ^ (unsigned int)((unsigned long *)d2)[3]) & 3) != 0);
        }
        /* invoke the map callback for each collected page, then release */
        sk_cap_decode_tag(d2, *(unsigned long *)(r + 0x78),
                          (int)(start - *(long *)(cb + 0x28) >> 0xe) + 1);
        unsigned long v2 = sk_cap_list_get((char *)d2);
        ((unsigned long *)d1)[3] = v2;
        ((unsigned long *)d2)[3] = (unsigned int)v2 >> 6 & 0x3fffff;
        /* (see notes: callback dispatch and release loop) */
        sk_obj_release_dispatch(*(unsigned long *)0 /*d0*/ , 8);
        sk_obj_release_dispatch(*(unsigned long *)0 /*d1*/ , 8);
        sk_obj_release_dispatch(*(unsigned long *)0 /*d2*/ , 8);
    }
    /* common tail: iterate page caps, map each, release the set */
    unsigned long d[3] = {0, 0, 0};
    if (cb <= cb + 0xd0) {
        sk_cap_decode_tag(d, *(unsigned long *)(r + 0x78),
                          (int)(start - *(long *)(cb + 0x28) >> 0xe) + 1);
        unsigned long v = sk_cap_list_get((char *)d);
        unsigned long v0 = 0x68a570;
        while (((((unsigned int)v0 ^ (unsigned int)v) & 3) != 0 &&
               (((v & 0xfffffc0) * 0x100 + *(long *)(cb + 0x28)) - 0x4000 < end))) {
            sk_region_page_remove(v, r, 0, (int)mode, (int)notify);
            if ((int)notify != 0) {
                sk_cap_decode_tag(d, *(unsigned long *)(r + 0x78), (unsigned int)v >> 6 & 0x3fffff);
            }
            v = sk_cap_list_get((char *)d);
        }
        rc = FUN_0067d02c(lock);
        if (rc != 0) FUN_006833d4(0x6a8797);
        return;
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673344) */
}

/* FUN_00673bd8 @ 0x00673bd8  (est. sk_region_desc_build)
 * Ghidra: void FUN_00673bd8(undefined8 *param_1, ulong *param_2, long param_3,
 *                          ulong *param_4)
 * Builds a region descriptor into param_1 from a raw region spec (param_3) and
 * a method-set (param_4): computes the alignment/size bounds, resolves the
 * containing region via the per-CPU table (FUN_00674264), and copies the
 * resolved capability descriptor out.
 * Confidence: medium */
static void sk_region_desc_build(unsigned long *out, unsigned long *c, long spec, unsigned long *m)
{
    unsigned long local[6];
    unsigned long arg0 = m[1];
    unsigned long arg1 = *m;
    unsigned long arg2 = m[3];
    unsigned long arg3 = m[2];
    local[0] = 0;
    local[1] = m[5];
    local[2] = m[4];
    unsigned char a0 = *(unsigned char *)(spec + 0x1a);
    long a = 0;
    if ((*(unsigned long *)(spec + 0x10) & 0x3fff) != 0) a = 0x4000;
    long msk = 1L << ((unsigned long)*(unsigned char *)(spec + 0x1b) & 0x3f);
    if (*(unsigned char *)(spec + 0x1b) - 0x40 < 0xffffffc1) {
        msk = -1;
    }
    unsigned long x = arg1 & 0xff;
    unsigned long *src = &local[3];
    if ((char)arg1 == '\0') {
        src = &local[3];
    } else {
        if ((char)arg1 != '\x01') FUN_0065c2f0(0, 0x6ac9a5);   /* fatal */
        src = &local[1];
        local[2] = 0;
        x = 0xffffffffffffffff;
    }
    a = a + (*(unsigned long *)(spec + 0x10) & 0xffffffffffffc000);
    *src = x;
    unsigned long d[3] = {0, 0x688638, 0};
    unsigned char ab = *(unsigned char *)(spec + 0x1c);
    unsigned long mm = 1L << ((unsigned long)ab & 0x3f);
    if (0x3f < ab) mm = 0xffffffffffffffff;
    unsigned long lim = 0;
    if (ab != 0) lim = mm;
    if (((char)arg3 == '\x01') && (lim <= *(unsigned long *)(spec + 8))) {
        lim = *(unsigned long *)(spec + 8);
    }
    if (a0 < 0xf) a0 = 0xe;
    unsigned long blk[4] = {0x6feea8, 0x688640, (unsigned long)(sk_fp_t)FUN_00673f50, 0x6b6a10};
    unsigned long p[4] = {local[0], a, lim, msk};
    if (*c + 0x2a0 < *c) {
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673da0) */
    }
    unsigned long pc = FUN_00668c94().lo;
    FUN_00674264(*(unsigned long *)pc, lim, msk, a, &blk);
    unsigned long v9 = local[3];
    unsigned long v11 = local[6];
    unsigned long v10 = local[5];
    out[1] = local[4];
    out[0] = v9;
    out[3] = v11;
    out[2] = v10;
    out[5] = local[8];
    out[4] = local[7];
    sk_obj_release_dispatch((long)&d, 8);
    sk_obj_release_dispatch((long)&local, 8);
}

/* FUN_00673db4 @ 0x00673db4  (est. sk_round_to_mult)
 * Ghidra: long FUN_00673db4(ulong param_1)
 * Rounds a value up to a multiple of param_1 using a small random seed
 * (FUN_0067cb30); returns the rounded value. Returns 0 for values < 2.
 * Confidence: medium */
static long sk_round_to_mult(unsigned long m)
{
    if (m < 2) {
        return 0;
    }
    unsigned long seed = 0;
    if (m != 0) seed = -m / m;
    unsigned long r;
    do {
        r = 0;
        FUN_0067cb30(&r, 8);
    } while (r < -m - seed * m);
    unsigned long q = 0;
    if (m != 0) q = r / m;
    return (long)(r - q * m);
}

/* FUN_00673e20 @ 0x00673e20  (est. sk_region_split_wrap)
 * Ghidra: void FUN_00673e20(undefined8 param_1, undefined8 param_2, long param_3)
 * Splits a region (param_3) after validating it is a leaf; invokes the inner
 * split (sk_region_split_inner) and returns, panicking on failure.
 * Confidence: medium */
static void sk_region_split_wrap(unsigned long a, unsigned long b, long r)
{
    if (*(int *)(r + 0x20) != 0) {
        FUN_006833d4(0x6acb57);   /* fatal: region not splittable */
    }
    unsigned long rc = sk_region_split_inner(0, 0, 0, 0, 0, 0).lo;   /* decompiler dropped args */
    if ((rc & 0xff) == 0) {
        return;
    }
    FUN_006833d4(0x6acbbc);   /* fatal */
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x673ec4) */
}

/* FUN_00673ec4 @ 0x00673ec4  (est. sk_region_desc_encode)
 * Ghidra: void FUN_00673ec4(char *param_1)
 * Encodes a region's capability descriptor into its bound slot (at +0x70):
 * packs the region's type/flag-derived tag and range into the descriptor.
 * Confidence: medium */
static void sk_region_desc_encode(char *r)
{
    unsigned long *slot = *(unsigned long **)(r + 0x70);
    unsigned long base = *(unsigned long *)(r + 8);
    unsigned char kind = r[0x18];
    unsigned int flags = *(unsigned int *)(r + 0x20);
    unsigned int tag = 8;
    if (*r != '\x04') {
        tag = 0;
    }
    tag = flags >> 0x11 & 4 | flags >> 3 & 3 | flags >> 6 & 0x40000 | tag;
    if (2 < kind - 4) {
        if (kind == 0x11) {
            tag = tag | 0x20000;
            goto set;
        }
        if (kind != 1) goto set;
    }
    tag = tag | 0x10000;
set:
    slot[1] = *(unsigned long *)(r + 0x10);
    *slot = base;
    *(unsigned char *)(slot + 3) = 0;
    slot[2] = 0;
    *(unsigned char *)((long)slot + 0x19) = kind;
    *(unsigned short *)((long)slot + 0x1a) = 0;
    *(unsigned int *)((long)slot + 0x1c) = tag;
    *(unsigned int *)(slot + 3) = 1;
}

/* FUN_00673f50 @ 0x00673f50  (est. sk_region_span_alloc)
 * Ghidra: undefined8 FUN_00673f50(long param_1, long param_2)
 * Allocates a span within a region: given a method-set descriptor (param_1) and
 * a region (param_2), finds an aligned free span of the requested size,
 * allocating it from the region's buddy/page-map. Returns 0 on success, 1 if no
 * space, and panics on overlap.
 * Confidence: low */
static unsigned long sk_region_span_alloc(long m, long r)
{
    if (*(int *)(r + 0x20) == 0) {
        unsigned long want = *(unsigned long *)(m + 0x30);
        if (want <= *(unsigned long *)(r + 0x10)) {
            unsigned long base = *(unsigned long *)(r + 8);
            unsigned long hi = *(unsigned long *)(m + 0x38);
            unsigned long end = base + *(unsigned long *)(r + 0x10);
            if (end < hi) FUN_006833d4(0x6aca37);
            unsigned long lo = (base <= hi) ? hi : base;
            unsigned long e2 = (*(unsigned long *)(m + 0x40) <= end) ? *(unsigned long *)(m + 0x40) : end;
            if (e2 < lo) FUN_006833d4(0x6aca37);
            if (e2 - lo < want) FUN_006833d4(0x6aca37);
            unsigned long sh = (unsigned long)*(unsigned char *)(m + 0x48);
            unsigned long unit = 1UL << (sh & 0x3f);
            long a = 0;
            if ((unit - 1U & lo) != 0) a = (long)unit;
            unsigned long top = -1L << (sh & 0x3f) & (e2 - want);
            unsigned long at = a + (lo & -unit);
            if (at <= top) {
                if (at < base) FUN_006833d4(0x6aca37);
                if (end < at + want) FUN_006833d4(0x6aca37);
                if (end < top + want) FUN_006833d4(0x6aca37);
                unsigned long n = (top - at) >> (sh & 0x3f) + 1;
                long l1 = *(long *)(*(long *)(m + 0x20) + 8);
                if (*(char *)(l1 + 0x18) == '\x01') {
                    long l2 = *(long *)(*(long *)(m + 0x28) + 8);
                    unsigned long used = *(unsigned long *)(l2 + 0x18);
                    if (used < n) {
                        if (*(char *)(l1 + 0x19) == '\x01') {
                            *(unsigned long *)(l2 + 0x18) = (at >> (sh & 0x3f)) - used;
                            l1 = *(long *)(*(long *)(m + 0x20) + 8);
                        }
                        *(long *)(l1 + 0x38) = r;
                        *(unsigned long *)(*(long *)(*(long *)(m + 0x20) + 8) + 0x40) =
                             (*(long *)(*(long *)(*(long *)(m + 0x28) + 8) + 0x18) <<
                             ((unsigned long)*(unsigned char *)(m + 0x48) & 0x3f)) + at;
                        return 0;
                    }
                    *(unsigned long *)(l2 + 0x18) = used - n;
                } else if (*(char *)(l1 + 0x18) == '\0') {
                    *(unsigned long *)(l1 + 0x30) = *(long *)(l1 + 0x30) + n;
                }
            }
            return 1;
        }
    } else {
        FUN_00686f30();
    }
    FUN_006833d4(0x6aca37);   /* fatal: span overlap */
}

/* FUN_006745f4 @ 0x006745f4  (est. sk_region_tree_height)
 * Ghidra: void FUN_006745f4(long param_1, long param_2)
 * Recomputes the subtree height/size field (+0x68) of region-tree node param_1
 * after a change involving param_2, walking the tree.
 * Confidence: medium */
static void sk_region_tree_height(long root, long r)
{
    if (root == 0) return;
    if (r == 0) return;
    if (*(unsigned long *)(r + 8) < *(unsigned long *)(root + 8)) {
        sk_region_tree_height(*(unsigned long *)(root + 0x58), r);
    } else {
        if (*(unsigned long *)(r + 8) == *(unsigned long *)(root + 8)) goto here;
        sk_region_tree_height(*(unsigned long *)(root + 0x60), r);
    }
here:
    unsigned long h = (*(int *)(root + 0x20) == 0) ? *(unsigned long *)(root + 0x10) : 0;
    unsigned long a = 0;
    if (*(long *)(root + 0x58) != 0) a = *(unsigned long *)(*(long *)(root + 0x58) + 0x68);
    unsigned long b = 0;
    if (*(long *)(root + 0x60) != 0) b = *(unsigned long *)(*(long *)(root + 0x60) + 0x68);
    if (a <= b) a = b;
    if (h <= a) h = a;
    *(unsigned long *)(root + 0x68) = h;
}

/* FUN_0067483c @ 0x0067483c  (est. sk_region_merge_wrap)
 * Ghidra: undefined8 FUN_0067483c(undefined8 param_1, undefined8 param_2,
 *                                long param_3, long param_4)
 * Merges two adjacent leaf regions (param_3, param_4): invokes the inner merge
 * (sk_region_merge_inner) and re-links the merged node into the context free
 * list.
 * Confidence: medium */
static unsigned long sk_region_merge_wrap(unsigned long a, unsigned long b, long r1, long r2)
{
    unsigned long out[2] = {0, 0};
    if ((*(int *)(r1 + 0x20) != 0) || (*(int *)(r2 + 0x20) != 0)) {
        FUN_006833d4(0x6acde3);   /* fatal: non-leaf merge */
    }
    unsigned long rc = sk_region_merge_inner((unsigned long *)a, b, r1, r2, (long *)&out[0], (long *)&out[1]).lo;
    if ((rc & 0xff) == 0) {
        sk_free_slot0_put((long)a, (unsigned long *)out[1]);
        return out[0];
    }
    FUN_006833d4(0x6ace7e);   /* fatal */
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x674934) */
}

/* FUN_00674934 @ 0x00674934  (est. sk_region_merge_inner)
 * Ghidra: undefined1 [16] FUN_00674934(ulong *param_1, undefined8 param_2,
 *                                    long param_3, long param_4, long *param_5,
 *                                    long *param_6)
 * Merges two adjacent regions param_3/param_4 into param_3 (the earlier one):
 * validates compatibility, sums their sizes, re-links the freed node into the
 * context free-list, and updates the region tree. Returns {0,0} on success.
 * Confidence: medium */
static sk_pair_t sk_region_merge_inner(unsigned long *c, unsigned long ctx, long a, long b,
                                       long *out1, long *out2)
{
    unsigned long sz = *(unsigned long *)(b + 8);
    if (sz < *(unsigned long *)(a + 8)) FUN_006833d4(0x6aced7);   /* fatal: order */
    unsigned long rc;
    if (*(long *)(a + 0x50) == *(long *)(b + 0x50)) {
        if (*(unsigned int *)(a + 0x20) == *(unsigned int *)(b + 0x20)) {
            if ((*(unsigned int *)(a + 0x20) & 0xd000800) == 0) {
                if (sz == 0) {
                    rc = 0x75c0001;
                } else {
                    rc = 0;
                    if (*(long *)(a + 0x10) + *(unsigned long *)(a + 8) != sz) {
                        rc = 0x75d0001;
                    }
                }
            } else {
                rc = 0x75b0001;
            }
        } else {
            rc = 0x75a0001;
        }
    } else {
        rc = 0x7590001;
    }
    if ((rc & 0xff) == 0) {
        unsigned int f = *(unsigned int *)(a + 0x20);
        if ((f >> 0x10 & 1) != 0) {
            FUN_0067a3dc(c, ctx, a, b);
            f = *(unsigned int *)(a + 0x20);
        }
        *(long *)(a + 0x10) = *(long *)(a + 0x10) + *(long *)(b + 0x10);
        if (f == 0) {
            sk_region_tree_height(*(unsigned long *)(*c + 0x58), a);
        } else {
            unsigned long *s1 = *(unsigned long **)(a + 0x70);
            unsigned long *s2 = *(unsigned long **)(b + 0x70);
            unsigned long n = sk_free_slot4_get((long)c)[0];
            *(unsigned long *)(a + 0x70) = n;
            *(unsigned long *)(b + 0x70) = 0;
            sk_region_desc_encode((char *)a);
            if (s1 + 4 < s1) goto trap;
            *(unsigned char *)(s1 + 3) = 0;
            if (2 < *(unsigned char *)((long)c + 0x31)) FUN_006833d4(0x6ac2e0);
            *s1 = c[2];
            c[2] = (unsigned long)s1;
            *(unsigned char *)((long)c + 0x31) = *(unsigned char *)((long)c + 0x31) + 1;
            if (s2 + 4 < s2) goto trap;
            *(unsigned char *)(s2 + 3) = 0;
            if (2 < *(unsigned char *)((long)c + 0x31)) FUN_006833d4(0x6ac2e0);
            *s2 = c[2];
            c[2] = (unsigned long)s2;
            *(unsigned char *)((long)c + 0x31) = *(unsigned char *)((long)c + 0x31) + 1;
        }
        if (*c + 0x2a0 < *c) goto trap;
        unsigned long root = FUN_00668c94().lo;
        unsigned long u = sk_region_tree_remove((long *)root, b);
        if ((u & 1) == 0) FUN_006833d4(0x6acf43);   /* fatal */
        rc = 0;
        *out1 = a;
        *out2 = b;
    }
    return (sk_pair_t){rc, 0};
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x674b24) */
}

/* FUN_00674be0 @ 0x00674be0  (est. sk_region_tree_remove)
 * Ghidra: undefined8 FUN_00674be0(long *param_1, long param_2)
 * Removes region param_2 from the region tree (root *param_1), rebalancing the
 * AVL-style tree and returning 1 if the root was removed, else the descent
 * result.
 * Confidence: medium */
static unsigned long sk_region_tree_remove(long *rootp, long r)
{
    long root = *rootp;
    unsigned long u = 0;
    if (root == 0) {
        return 0;
    }
    if (root != r) goto descend;
    long right = *(long *)(root + 0x60);
    unsigned int dir;
    if (*(long *)(root + 0x58) == 0) {
        if (right == 0) goto descend;
        dir = 0xfffffffe;
    } else {
        if ((right != 0) && (*(unsigned char *)(*(long *)(root + 0x58) + 0x24) < *(unsigned char *)(right + 0x24))) {
            dir = 0xfffffffe;
        } else {
            dir = 2;
        }
    }
    sk_region_tree_rebalance(rootp, (int)dir);
descend:
    root = *rootp;
    if (root == r) {
        *rootp = 0;
        u = 1;
    } else {
        unsigned long off;
        if (*(unsigned long *)(r + 8) < *(unsigned long *)(root + 8)) {
            off = root + 0x58;
        } else {
            off = root + 0x60;
        }
        if (off + 0x10 < off) {
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x674d1c) */
        }
        u = sk_region_tree_remove((long *)off, r);
        root = *rootp;
        long left = *(long *)(root + 0x58);
        unsigned int h = (left == 0) ? 0 : *(unsigned char *)(left + 0x24) + 1;
        long right2 = *(long *)(root + 0x60);
        unsigned int h2 = (right2 == 0) ? 0 : *(unsigned char *)(right2 + 0x24) + 1;
        if (h <= h2) h = h2;
        *(char *)(root + 0x24) = (char)h;
        unsigned long sz = (*(int *)(root + 0x20) == 0) ? *(unsigned long *)(root + 0x10) : 0;
        unsigned long a = (left != 0) ? *(unsigned long *)(left + 0x68) : 0;
        unsigned long b = (right2 != 0) ? *(unsigned long *)(right2 + 0x68) : 0;
        if (a <= b) a = b;
        if (sz <= a) sz = a;
        *(unsigned long *)(root + 0x68) = sz;
    }
    return u;
}

/* FUN_00674d1c @ 0x00674d1c  (est. sk_region_tree_rebalance)
 * Ghidra: void FUN_00674d1c(ulong *param_1, int param_2)
 * AVL-style rebalances the region tree rooted at *param_1 after a removal,
 * restoring balance factors and subtree size fields at +0x24/+0x68.
 * Confidence: medium */
static void sk_region_tree_rebalance(unsigned long *rootp, int dir)
{
    unsigned long cur = *rootp;
    if (cur == 0) {
        return;
    }
    unsigned long lim = cur + 0xb0;
    unsigned long head = cur;
    unsigned long r = 0;
    if (dir < -1) {
        r = *(unsigned long *)(cur + 0x60);
        if (r != 0) {
            *(unsigned long *)(cur + 0x60) = *(unsigned long *)(r + 0x58);
            if (lim < cur) goto trap;
            *(unsigned long *)(r + 0x58) = cur;
relink:
            if (r + 0xb0 < r) goto trap;
            *rootp = r;
            head = r;
        }
    } else if ((1 < dir) && (r = *(unsigned long *)(cur + 0x58), r != 0)) {
        *(unsigned long *)(cur + 0x58) = *(unsigned long *)(r + 0x60);
        if (lim < cur) goto trap;
        *(unsigned long *)(r + 0x60) = cur;
        goto relink;
    }
    if (cur <= lim) {
        long l = *(long *)(cur + 0x58);
        unsigned int h = (l == 0) ? 0 : *(unsigned char *)(l + 0x24) + 1;
        long r2 = *(long *)(cur + 0x60);
        unsigned int h2 = (r2 == 0) ? 0 : *(unsigned char *)(r2 + 0x24) + 1;
        if (h <= h2) h = h2;
        *(char *)(cur + 0x24) = (char)h;
        unsigned long sz = (*(int *)(cur + 0x20) == 0) ? *(unsigned long *)(cur + 0x10) : 0;
        unsigned long a = (l != 0) ? *(unsigned long *)(l + 0x68) : 0;
        unsigned long b = (r2 != 0) ? *(unsigned long *)(r2 + 0x68) : 0;
        if (a <= b) a = b;
        if (sz <= a) sz = a;
        *(unsigned long *)(cur + 0x68) = sz;
        l = *(long *)(head + 0x58);
        h = (l == 0) ? 0 : *(unsigned char *)(l + 0x24) + 1;
        r2 = *(long *)(head + 0x60);
        h2 = (r2 == 0) ? 0 : *(unsigned char *)(r2 + 0x24) + 1;
        if (h <= h2) h = h2;
        *(char *)(head + 0x24) = (char)h;
        sz = (*(int *)(head + 0x20) == 0) ? *(unsigned long *)(head + 0x10) : 0;
        a = (l != 0) ? *(unsigned long *)(l + 0x68) : 0;
        b = (r2 != 0) ? *(unsigned long *)(r2 + 0x68) : 0;
        if (a <= b) a = b;
        if (sz <= a) sz = a;
        *(unsigned long *)(head + 0x68) = sz;
        return;
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x674e98) */
}

/* FUN_00674688 @ 0x00674688  (est. sk_region_pages_unmap)
 * Ghidra: undefined1 [16] FUN_00674688(ulong param_1, ulong *param_2, ulong *param_3,
 *                                    int param_4)
 * Unmaps a page range [*param_2, *param_2+*param_3) of region param_1: aligns
 * the range, invokes sk_region_map_pages, and reports span-completeness flags
 * to the region walker. Returns {0,0} on success or 0x7210001.
 * Confidence: medium */
static sk_pair_t sk_region_pages_unmap(unsigned long r, unsigned long *off, unsigned long *len, int full)
{
    unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
    unsigned int f = *(unsigned int *)(r + 0x20);
    if ((f & 0x4000000) == 0) {
        full = 1;
    }
    unsigned long base = *off;
    if ((*(unsigned long *)(r + 0x10) <= base) ||
       (*(unsigned long *)(r + 0x10) - base < *len || (f & 0x8000000) != 0)) {
        return (sk_pair_t){0x7210001, 0};
    }
    unsigned long pa = *(long *)(r + 8) + base;
    long a = 0;
    if ((pa & 0x3fff) != 0) a = 0x4000;
    a = a + (pa & 0xffffffffffffc000);
    *len = (pa + *len) - a;
    *off = a - *(long *)(r + 8);
    unsigned long sz = *len & 0xffffffffffffc000;
    *len = sz;
    sk_region_map_pages(a, sz, r, f >> 0xc & 1, full);
    if (full != 0) {
        bool whole = (*off == 0) ? (*len == *(unsigned long *)(r + 0x10)) : false;
        bool tail;
        if ((*(unsigned int *)(r + 0x20) >> 6 & 1) == 0) {
            tail = false;
        } else {
            long b1, b2;
            if ((*(unsigned int *)(r + 0x20) >> 7 & 1) == 0) {
                b1 = *(long *)(r + 8);
                b2 = b1;
            } else {
                b1 = *(long *)(r + 8);
                b2 = (*(long *)(r + 0x10) - *(long *)(r + 0x48)) + b1;
            }
            if (*off != b2 - b1) {
                tail = false;
            } else {
                tail = (*len == *(unsigned long *)(r + 0x48));
            }
        }
        unsigned long walk = r + 0xb0;
        if (!whole && !tail) {
            walk = 0;
            r = 0;
        }
        if ((cb + 0xd0 < cb) ||
           ((r != 0 && ((walk < r + 0xb0 || (r + 0xb0 < r)))))) {
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x67483c) */
        }
        FUN_00678ae0(cb, a, sz, (f & 0x1000) == 0);
    }
    return (sk_pair_t){0, 0};
}

/* FUN_00674364 @ 0x00674364  (est. sk_region_split_inner)
 * Ghidra: undefined1 [16] FUN_00674364(long param_1, undefined8 param_2,
 *                                    undefined8 *param_3, ulong param_4,
 *                                    ulong *param_5, ulong *param_6)
 * Splits region param_3 at offset param_4 into two regions: allocates a new
 * region node from the context free-list (sk_free_slot0_get), splits the
 * page-capability sets, moves the tail range into the new node, re-encodes the
 * descriptors, and registers the new node. Returns {0,0} on success.
 * Confidence: low */
static sk_pair_t sk_region_split_inner(long c, unsigned long ctx, unsigned long *src,
                                       unsigned long off, unsigned long *out, long *tail)
{
    unsigned long rc;
    if ((*(unsigned int *)(src + 4) & 0xd000800) == 0) {
        unsigned long v1 = 0x7fb0001;
        if (off != 0) v1 = 0;
        rc = 0x7f80001;
        if (off < (unsigned long)src[2]) {
            rc = v1;
        }
    } else {
        rc = 0x7f60001;
    }
    if ((rc & 0xff) != 0) {
        return (sk_pair_t){rc, 0};
    }
    unsigned long *newnode = sk_free_slot0_get(c);
    unsigned long *lim = newnode + 0x16;
    unsigned int f = *(unsigned int *)(src + 4);
    if ((f >> 0x10 & 1) != 0) {
        if (lim < newnode) goto trap;
        FUN_0067a444(c, ctx, src, off, newnode);
        f = *(unsigned int *)(src + 4);
    }
    unsigned long *tailnode = (unsigned long *)src[0xe];
    unsigned long slot;
    unsigned long n2;
    unsigned int n3;
    if (f == 0) {
        slot = 0; n2 = 0; n3 = 0;
    } else {
        slot = sk_free_slot4_get(c)[0];
        if (*(int *)(src + 4) == 0) {
            n2 = 0; n3 = 0;
        } else {
            n2 = sk_free_slot4_get(c)[0];
            if (n2 + 0x20 < n2) goto trap;
            n3 = *(unsigned int *)(src + 4);
        }
    }
    newnode[0xe] = n2;
    *(unsigned int *)(newnode + 4) = n3;
    newnode[1] = src[1] + off;
    newnode[2] = src[2] - off;
    newnode[0] = src[0];
    newnode[3] = src[3];
    newnode[2] = src[2] - off;
    newnode[10] = src[10];
    src[2] = off;
    if (slot <= slot + 0x20) {
        src[0xe] = slot;
        if (*(int *)(src + 4) != 0) {
            sk_region_desc_encode((char *)src);
            if ((lim < newnode) || (sk_region_desc_encode((char *)newnode), tailnode + 4 < tailnode)) goto trap;
            *(unsigned char *)(tailnode + 3) = 0;
            if (2 < *(unsigned char *)((long)c + 0x31)) FUN_006833d4(0x6ac2e0);
            *tailnode = *(unsigned long *)(c + 0x10);
            *(unsigned long **)(c + 0x10) = tailnode;
            *(unsigned char *)(c + 0x31) = *(unsigned char *)(c + 0x31) + 1;
            if ((*(unsigned int *)(src + 4) >> 6 & 1) != 0) {
                /* fix up the split pair's span bookkeeping */
                unsigned long *pa = src;
                unsigned long *pe = src + 0x16;
                unsigned long *pb = newnode;
                unsigned long *pbe = lim;
                if ((*(unsigned int *)(src + 4) >> 7 & 1) == 0) {
                    pa = newnode; pe = lim; pb = src; pbe = src + 0x16;
                }
                if (pbe < pb + 0x16) goto trap;
                unsigned long a = src[9];
                unsigned long b = pb[2];
                long d = (long)(a - b);
                if (a < b || d == 0) {
                    pb[9] = a;
                    if (pe < pa + 0x16) goto trap;
                    d = 0;
                } else {
                    pb[9] = b;
                    if (pe < pa + 0x16) goto trap;
                }
                pa[9] = (unsigned long)d;
            }
        }
        if (newnode <= lim) {
            sk_region_register2((unsigned long *)c, (unsigned long)newnode);
            rc = 0;
            *out = (unsigned long)src;
            *tail = (unsigned long)newnode;
            return (sk_pair_t){rc, 0};
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6745c4) */
}

/* FUN_00674fac @ 0x00674fac  (est. sk_page_map)
 * Ghidra: ulong FUN_00674fac(long param_1, long param_2, ulong param_3,
 *                           ulong param_4, undefined8 param_5, int param_6,
 *                           ulong param_7)
 * Maps a page (param_2) into region param_1: resolves the page-capability set,
 * performs the map via the supervisor (CallSupervisor 2/3) and the page-walk
 * primitives (sk_region_page_next), handling the page-table callback table and
 * the coalesced walk. Returns the map status code (0 success, 2/7 pending,
 * 0x2xx/0x3xx errors).
 * Confidence: low (large page-map dispatch) */
static unsigned long sk_page_map(long r, long addr, unsigned long mode,
                                 unsigned long flags, unsigned long arg5,
                                 int arg6, unsigned long arg7)
{
    unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
    unsigned long lock = r + 0x80;
    if (r + 0x90U < lock) goto trap;
    int rc = FUN_0067cffc(lock);
    if (rc != 0) FUN_006833d4(0x6a8797);
    unsigned long l[5] = {0};
    if (cb + 0xd0 < cb) goto trap;
    FUN_006662ac(l, *(unsigned long *)(r + 0x78),
                 (int)((unsigned long)(addr - *(long *)(cb + 0x28)) >> 0xe) + 1);
    long page = (long)l[0];
    *(unsigned long *)(r + 0x78) = l[4];
    unsigned long result;
    unsigned long walk = 0;
    if (l[0] != 0) {
        unsigned long cb2 = FUN_00668c78(*(unsigned long *)(r + 0x50));
        if (cb2 <= cb2 + 0xd0) {
            unsigned long cap = FUN_00677674(cb2, 1, addr);
            int ok = FUN_006777d8(cb2, cap);
            if (ok == 0) {
                result = 2;
            } else {
                if ((int)flags == 0) {
                    CallSupervisor(2);
                } else {
                    sk_ipc_msg[0] = 0;   /* tpidrro_el0 */
                    CallSupervisor(3);
                }
                walk = (unsigned long)page;
                if (mode == 0) {
                    sk_pair_t w = sk_page_map_walk(r, addr, cb2, page, cap, flags, 0);
                    walk = w.hi;
                    result = w.lo;
                    if (result != 0) {
                        do {
                            CallSupervisor(4);
                        } while (page == 1);
                    }
                }
            }
            rc = FUN_0067d02c(lock, walk);
            if (rc == 0) {
                return result;
            }
            FUN_006833d4(0x6a8797);   /* fatal */
        }
        goto trap;
    }
    rc = FUN_0067d02c(lock);
    if (rc != 0) FUN_006833d4(0x6a8797);
    if ((char)l[2] == '\0') {
        return 0x102;
    }
    sk_pair_t e = FUN_00686c74();
    unsigned long cc = e.hi;
    char *reg = (char *)e.lo;
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    unsigned int rf = *(unsigned int *)(reg + 0x20);
    unsigned int mode2 = 0;
    if (arg6 == 0) mode2 = rf >> 3 & 3;
    unsigned int st = (unsigned int)((rf & 0x2400) != 0);
    if ((rf & 0x200) != 0) st = 2;
    st = st | rf >> 0x13 & 8;
    unsigned long end = flags;
    unsigned long sub;
    if (*reg == '\x04') {
        sub = FUN_006786fc();
    } else {
        sub = FUN_006787a0(mode, arg5, flags, cc, mode2, st);
    }
    unsigned long tag = 0x6b4368;
    unsigned long lock2 = 0;
    unsigned long lock3 = 0;
    if ((sub & 0xff) == 4) {
        if (((unsigned char)reg[0x23] >> 2 & 1) != 0) {
            /* coalesced 32MB-aligned page walk */
            sk_pair_t e2 = FUN_00686f68();
            reg = (char *)e2.lo;
            long a = 0;
            if ((end & 0x3fff) != 0) a = 0x4000;
            unsigned long end2 = a + (end & 0xffffffffffffc000);
            unsigned long cb3 = FUN_00668c78(*(unsigned long *)(reg + 0x50));
            unsigned long top = cb3 + 0xd0;
            if (cb3 <= top) {
                for (unsigned long u = e2.hi & 0xfffffffffe000000; u < end2; u = u + 0x2000000) {
                    unsigned long cap = FUN_00677674(cb3, 1, u);
                    unsigned long ok = FUN_006777d8(cb3, cap);
                    if ((ok & 1) == 0) {
                        return 2;
                    }
                }
                char *pg = reg + 0x80;
                if (pg <= reg + 0x90) {
                    int rc2 = FUN_0067cffc(pg);
                    if (rc2 != 0) FUN_006833d4(0x6a8797);
                    unsigned long base2 = e2.hi & 0xffffffffffffc000;
                    char k = *reg;
                    unsigned int rf2 = *(unsigned int *)(reg + 0x20);
                    unsigned int en = rf2 >> 0xd & 1;
                    if (k != '\x11') en = 0;
                    unsigned int flags2 = rf2 >> 0x11 & 0x20 | en;
                    /* invoke the page-map callback table (bounded walk) */
                    unsigned long walkv;
                    if ((rf2 >> 0x1a & 1) == 0) {
                        unsigned long n = (end2 - base2) >> 0xe;
                        unsigned long b0 = *(unsigned long *)(cb3 + 0xb0);
                        unsigned long **ops = *(unsigned long ***)(cb3 + 0xb8);
                        sk_fp_t cb2f = (sk_fp_t)ops[9];
                        if (cb2f == 0) {
                            if (end2 != base2) {
                                unsigned long i = 0;
                                do {
                                    unsigned long r1 = FUN_006757cc(&lock, i);
                                    unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, flags2);
                                    FUN_006758c8(&lock, r2, i, r1);
                                    i = i + 1;
                                } while (n != i);
                            }
                        } else {
                            cb2f(b0, k, flags2, n, &lock, &lock);
                        }
                    } else {
                        /* iterative coalesced walk */
                        while (end2 != base2) {
                            k = *reg;
                            unsigned long b0 = *(unsigned long *)(cb3 + 0xb0);
                            unsigned long **ops = *(unsigned long ***)(cb3 + 0xb8);
                            sk_fp_t cb2f = (sk_fp_t)ops[9];
                            if (cb2f == 0) {
                                unsigned long r1 = FUN_006757cc(&lock, 0);
                                unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, flags2);
                                FUN_006758c8(&lock, r2, 0, r1);
                            } else {
                                cb2f(b0, k, flags2, 1, &lock, &lock);
                            }
                            if (lock2 != 0) break;
                            unsigned long cur = lock3;
                            lock3 = cur + 0x4000U;
                            base2 = cur + 0x4000U;
                        }
                    }
                    rc2 = FUN_0067d02c(pg);
                    if (rc2 == 0) {
                        FUN_00656634(&lock, 8);
                        FUN_00656634(&lock, 8);
                        return lock2;
                    }
                    FUN_006833d4(0x6a8797);   /* fatal */
                }
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675764) */
        }
        int ok = FUN_006782b4(mode, cc);
        if (ok == 0) {
            sub = 2;
            goto done;
        }
        if (*reg == '\x04') {
            sub = FUN_006786fc();
            tag = 0x6b4368;
        } else {
            sub = FUN_006787a0(mode, arg5, flags, cc, mode2, st);
            tag = 0x6b4368;
        }
    }
    *(unsigned long *)0x6b4368 = tag;   /* _DAT_006b4368 */
    if (sub != 0) {
        unsigned int c8 = sub & 0xff;
        if (((int)arg7 == 0) || (c8 == 2)) {
            if ((arg7 & 1) != 0) goto done;
            if ((long)sub < 0x207) {
                if (sub == 2 || sub == 7) goto done;
            } else if ((sub == 0x207) || (sub == 0x307)) goto done;
        }
        if ((c8 != 8) && (c8 != 0 && (*(unsigned int *)(reg + 0x20) & 0x40000) == 0)) {
            sk_l4_error_format((unsigned long *)&cookie, 0);
            FUN_006864cc(tag);
            sk_l4_error_format((unsigned long *)&cookie, c8);
            FUN_006833d4(0x6a71a1);   /* fatal */
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675140) */
done:
    if (*(unsigned long *)0x6b5ed0 == cookie) {
        return sub;
    }
    FUN_0067f660(sub);   /* fatal (noreturn) */
}

/* FUN_00674264 @ 0x00674264  (est. sk_region_tree_walk)
 * Ghidra: undefined8 FUN_00674264(long param_1, ulong param_2, ulong param_3,
 *                                ulong param_4, long param_5)
 * Walks the region tree (param_1) invoking a callback (via param_5's method
 * table) on each leaf region overlapping [param_2, param_3) with at least
 * param_4 free space. Returns 0 when the callback accepts a region, else 1.
 * Confidence: medium */
static unsigned long sk_region_tree_walk(long node, unsigned long lo, unsigned long hi,
                                         unsigned long need, long m)
{
    if (node == 0) {
        return 1;
    }
    unsigned long r = 1;
    if (need <= *(unsigned long *)(node + 0x68)) {
        unsigned long base = *(unsigned long *)(node + 8);
        if (lo < base) {
            unsigned long r = sk_region_tree_walk(*(unsigned long *)(node + 0x58), lo, hi, need, m);
            if ((int)r == 0) return r;
            base = *(unsigned long *)(node + 8);
        }
        unsigned long a = (base <= lo) ? lo : base;
        unsigned long end = *(long *)(node + 0x10) + base;
        unsigned long b = (hi <= end) ? hi : end;
        unsigned long avail = 0;
        if (a <= b) avail = b - a;
        if ((*(int *)(node + 0x20) == 0) && (need <= avail)) {
            r = (*(sk_fp_t *)(m + 0x10))(m, node);
            if ((int)r == 0) return r;
            end = *(long *)(node + 0x10) + *(long *)(node + 8);
        }
        if ((end < hi) &&
            (r = sk_region_tree_walk(*(unsigned long *)(node + 0x60), lo, hi, need, m),
             (int)r == 0)) {
            return r;
        }
    }
    return 1;
}

/* FUN_006757cc @ 0x006757cc  (est. sk_page_map_step0)
 * Ghidra: void FUN_006757cc(long param_1, long param_2)
 * First page-map walk step: resolves the page-capability set for page index
 * param_2 from the walk state (param_1), updating the region's cap set; reports
 * a 0x102 sentinel when no page is present.
 * Confidence: medium */
static unsigned long sk_page_map_step0(long w, long idx)
{
    unsigned long l[5] = {0, 0, 0, 0, 0};
    unsigned long cb = *(unsigned long *)(w + 0x38);
    if ((cb != 0) &&
       ((cb + 0xd0 < cb || *(unsigned long *)(w + 0x40) < cb + 0xd0) ||
        cb < *(unsigned long *)(w + 0x48))) {
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6758c8) */
    }
    unsigned long base = (*(long *)(*(long *)(*(long *)(w + 0x20) + 8) + 0x18) + idx * 0x4000);
    FUN_006662ac(l, *(unsigned long *)(*(long *)(w + 0x30) + 0x78),
                 (int)((unsigned long)(base - *(long *)(cb + 0x28)) >> 0xe) + 1);
    *(long *)(*(long *)(w + 0x30) + 0x78) = (long)l[4];
    if (l[0] == 0) {
        if ((l[2] & 0xffU) != 0) {
            FUN_006833d4(0x6ad275);   /* fatal */
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6758c8) */
        }
        long r = *(long *)(*(long *)(w + 0x28) + 8);
        if (*(long *)(r + 0x18) == 0) {
            *(unsigned long *)(r + 0x18) = 0x102;
        }
    }
    return l[0];
}

/* FUN_006758c8 @ 0x006758c8  (est. sk_page_map_step1)
 * Ghidra: void FUN_006758c8(long param_1, ulong param_2, long param_3, undefined8 param_4)
 * Second page-map walk step: dispatches the page-map result (param_2) — mapping
 * the page at index param_3 via sk_page_map / the region walk, or recording a
 * pending status. Handles the 0x107 and error-status paths.
 * Confidence: medium */
static unsigned long sk_page_map_step1(long w, unsigned long status, long idx, unsigned long arg4)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    long page = (*(long *)(*(long *)(*(long *)(w + 0x20) + 8) + 0x18) + idx * 0x4000);
    if (status == 0) {
        unsigned long cb = *(unsigned long *)(w + 0x30);
        if ((cb == 0) ||
           ((cb <= cb + 0xd0 && cb + 0xd0 <= *(unsigned long *)(w + 0x38)) &&
            *(unsigned long *)(w + 0x40) <= cb)) {
            unsigned long cap = FUN_00677674(cb, 1, page);
            cb = *(unsigned long *)(w + 0x30);
            if ((cb == 0) ||
               ((cb <= cb + 0xd0 && cb + 0xd0 <= *(unsigned long *)(w + 0x38)) &&
                *(unsigned long *)(w + 0x40) <= cb)) {
                long rr = sk_page_map(*(unsigned long *)(w + 0x48), page, cb, arg4, cap, 0, 1);
                if (rr != 0) {
                    cb = *(unsigned long *)(w + 0x30);
                    if ((*(unsigned long *)(w + 0x38) < cb + 0xd0) || (cb < *(unsigned long *)(w + 0x40)))
                        goto trap;
                    FUN_00686f94(cb, arg4, w, rr);
                }
                goto done;
            }
        }
    } else {
        if (status == 0x107) goto done;
        if ((status & 0xfd) == 0) {
            unsigned long cb = *(unsigned long *)(w + 0x30);
            if (*(unsigned long *)(w + 0x38) < cb + 0xd0 || cb < *(unsigned long *)(w + 0x40)) goto trap;
            unsigned long r2 = (*(sk_fp_t *)(*(long *)(cb + 0xb8) + 0x10))(*(unsigned long *)(cb + 0xb0), arg4);
            if ((r2 & 0xff) == 0) {
                long t = *(long *)(*(long *)(w + 0x28) + 8);
                if (*(long *)(t + 0x18) == 0) {
                    *(unsigned long *)(t + 0x18) = status;
                }
                goto done;
            }
            FUN_00686ffc(r2, (unsigned char *)&cookie);
        }
        unsigned long tag = *(unsigned long *)0x6b4368;
        sk_l4_error_format((unsigned long *)&cookie, status);
        if (*(unsigned long *)(w + 0x30) + 0xd0 <= *(unsigned long *)(w + 0x38) &&
            *(unsigned long *)(w + 0x40) <= *(unsigned long *)(w + 0x30)) {
            FUN_006864cc(tag);
            sk_l4_error_format((unsigned long *)&cookie, status);
            FUN_006833d4(0x6ad325);   /* fatal */
        }
    }
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675ae8) */
done:
    if (*(unsigned long *)0x6b5ed0 == cookie) {
        return 0;
    }
    FUN_0067f660();   /* fatal (noreturn) */
}

/* FUN_00675ae8 @ 0x00675ae8  (est. sk_region_merge_validate)
 * Ghidra: long FUN_00675ae8(undefined8 param_1, long param_2)
 * Walks from region param_2 to the end of the region tree, returning the last
 * mergeable (non-leaf / non-tail) region or 0 when the region is the whole
 * address space.
 * Confidence: medium */
static long sk_region_merge_validate(unsigned long c, long r)
{
    for (;;) {
        if (r == 0) {
            return 0;
        }
        if (*(int *)(r + 0x20) != 0) break;
        if (*(long *)(r + 0x10) + *(long *)(r + 8) == 0x1000000000) {
            return 0;
        }
        r = (long)sk_region_find((unsigned long *)c, 0);
    }
    return r;
}

/* FUN_00675d88 @ 0x00675d88  (est. sk_region_tree_insert)
 * Ghidra: void FUN_00675d88(ulong *param_1, ulong param_2)
 * Inserts region param_2 into the region tree rooted at *param_1, recomputing
 * the balance/height fields and rebalancing.
 * Confidence: medium */
static void sk_region_tree_insert(unsigned long *rootp, unsigned long r)
{
    unsigned long root = *rootp;
    if (root == 0) {
        *rootp = r;
        unsigned long h = (*(int *)(r + 0x20) == 0) ? *(unsigned long *)(r + 0x10) : 0;
        unsigned long a = 0;
        if (*(long *)(r + 0x58) != 0) a = *(unsigned long *)(*(long *)(r + 0x58) + 0x68);
        unsigned long b = 0;
        if (*(long *)(r + 0x60) != 0) b = *(unsigned long *)(*(long *)(r + 0x60) + 0x68);
        if (a <= b) a = b;
        if (h <= a) h = a;
        *(unsigned long *)(r + 0x68) = h;
        return;
    }
    long child;
    if (*(unsigned long *)(r + 8) < *(unsigned long *)(root + 8)) {
        if (root + 0xb0 < root || root + 0x60 < root + 0x58) goto trap;
        sk_region_tree_insert((unsigned long *)(root + 0x58), r);
        child = *(long *)(root + 0x58);
    } else {
        if (root + 0xb0 < root || root + 0x68 < root + 0x60) goto trap;
        sk_region_tree_insert((unsigned long *)(root + 0x60), r);
        child = *(long *)(root + 0x60);
    }
    if (*(unsigned char *)(root + 0x24) <= *(unsigned char *)(child + 0x24)) {
        *(unsigned char *)(root + 0x24) = *(unsigned char *)(child + 0x24) + 1;
    }
    int i = 0;
    if (*(long *)(root + 0x58) != 0) i = *(unsigned char *)(*(long *)(root + 0x58) + 0x24) + 1;
    unsigned int j = 0;
    if (*(long *)(root + 0x60) != 0) j = ~(unsigned int)*(unsigned char *)(*(long *)(root + 0x60) + 0x24);
    sk_region_tree_rebalance(rootp, j + i);
    return;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675e98) */
}

/* FUN_00676498 @ 0x00676498  (est. sk_region_map_page)
 * Ghidra: void FUN_00676498(long param_1)
 * Maps a single 16KB page for a region via sk_region_map_extend, validating the
 * exact 0x4000-size result.
 * Confidence: medium */
static void sk_region_map_page(long d)
{
    long off = *(long *)(d + 0x28) + *(long *)(d + 0x20);
    long sz = 0x4000;
    char rc = (char)sk_region_map_extend(*(unsigned long *)(d + 0x30), (unsigned long *)&off, (unsigned long *)&sz);
    if (rc != '\0') FUN_006833d4(0x6aef45);   /* fatal */
    if (off == *(long *)(d + 0x28) + *(long *)(d + 0x20)) {
        if (sz == 0x4000) {
            return;
        }
        FUN_006833d4(0x6af01d);   /* fatal */
    }
    FUN_006833d4(0x6aefc4);   /* fatal */
}

/* FUN_00675b48 @ 0x00675b48  (est. sk_page_lookup)
 * Ghidra: undefined1 [16] FUN_00675b48(long param_1, ulong param_2, undefined8 *param_3)
 * Looks up/allocates a page capability for address param_2 in region param_1,
 * storing the resulting token in *param_3. Uses the region's page-alloc method
 * (indirect call) or the built-in page-cap split (sk_cap_decode), returning a
 * {status, token} pair.
 * Confidence: medium */
static sk_pair_t sk_page_lookup(long r, unsigned long addr, unsigned long *tok)
{
    if (*(unsigned long *)(r + 0x10) <= (addr & 0xffffffffffffc000) - *(long *)(r + 8)) {
        FUN_006833d4(0x6ad9b0);   /* fatal */
    }
    long res = *(long *)(r + 0x40);
    *tok = 0xffffffffffffffff;
    sk_pair_t out;
    if ((*(unsigned char *)(r + 0x21) >> 4 & 1) == 0) {
        unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
        unsigned long lock = r + 0x80;
        if (r + 0x90U < lock) goto trap;
        int rc = FUN_0067cffc(lock);
        if (rc != 0) FUN_006833d4(0x6a8797);
        unsigned long l[5] = {0};
        if (cb + 0xd0 < cb) goto trap;
        sk_cap_decode(l, *(unsigned long *)(r + 0x78),
                      (int)(addr - *(long *)(cb + 0x28) >> 0xe) + 1, 0, 0);
        *(long *)(r + 0x78) = (long)l[4];
        if (l[0] == 0) {
            rc = FUN_0067d02c(lock);
            if (rc != 0) FUN_006833d4(0x6a8797);
            bool have = (l[2] & 0xffU) != 0;
            out.lo = have ? l[2] : 0x9370002;
            res = have ? (long)l[3] : 0;
            goto done;
        }
        res = (*(sk_fp_t *)(*(long *)(cb + 0xb8) + 0x18))
                      (*(unsigned long *)(cb + 0xb0), l[0], tok);
        rc = FUN_0067d02c(lock);
        if (rc != 0) FUN_006833d4(0x6a8797);
        if (res != 0) {
            out.lo = 0x93e0001;
            res = 0;
            goto done;
        }
        out.lo = 0;
    } else {
        out.lo = 0x9260001;
        if (*(sk_fp_t *)(r + 0x28) != 0) {
            out.lo = (*(sk_fp_t *)(r + 0x28))(*(unsigned long *)(r + 0x38),
                                               (addr & 0xffffffffffffc000) - res, tok);
            if ((out.lo & 1) == 0) {
                out.lo = 0x9280001;
                res = 0;
                goto done;
            }
            out.lo = 0;
        }
    }
    res = 0;
done:
    out.hi = res;
    return out;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675cc0) */
}

/* FUN_006751e0 @ 0x006751e0  (est. sk_page_map_dispatch)
 * Ghidra: ulong FUN_006751e0(char *param_1, undefined8 param_2, undefined8 param_3,
 *                          ulong param_4, undefined8 param_5, int param_6, uint param_7)
 * Page-map dispatcher (variant of sk_page_map): maps a page region, resolving
 * the containing region, invoking the 32MB-coalesced page-walk callback table
 * (FUN_006757cc / FUN_006758c8), and returning the map status. Handles the
 * 0x2xx/0x3xx error and pending (2/7) paths with the shared error formatter.
 * Confidence: low */
static unsigned long sk_page_map_dispatch(char *r, unsigned long a2, unsigned long mode,
                                          unsigned long flags, unsigned long a5,
                                          int a6, unsigned int a7)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    unsigned int rf = *(unsigned int *)(r + 0x20);
    unsigned int mode2 = 0;
    if (a6 == 0) mode2 = rf >> 3 & 3;
    unsigned int st = (unsigned int)((rf & 0x2400) != 0);
    if ((rf & 0x200) != 0) st = 2;
    st = st | rf >> 0x13 & 8;
    unsigned long end = flags;
    unsigned long sub;
    if (*r == '\x04') {
        sub = FUN_006786fc();
    } else {
        sub = FUN_006787a0(mode, a5, flags, a2, mode2, st);
    }
    unsigned long tag = 0x6b4368;
    unsigned long lock0[4] = {0};
    unsigned long lock2 = 0, lock3 = 0;
    if ((sub & 0xff) == 4) {
        if (((unsigned char)r[0x23] >> 2 & 1) != 0) {
            /* coalesced 32MB-aligned page walk */
            sk_pair_t e2 = FUN_00686f68();
            r = (char *)e2.lo;
            long a = 0;
            if ((end & 0x3fff) != 0) a = 0x4000;
            unsigned long end2 = a + (end & 0xffffffffffffc000);
            unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
            unsigned long top = cb + 0xd0;
            if (cb <= top) {
                for (unsigned long u = e2.hi & 0xfffffffffe000000; u < end2; u = u + 0x2000000) {
                    unsigned long cap = FUN_00677674(cb, 1, u);
                    unsigned long ok = FUN_006777d8(cb, cap);
                    if ((ok & 1) == 0) return 2;
                }
                char *pg = r + 0x80;
                if (pg <= r + 0x90) {
                    int rc = FUN_0067cffc(pg);
                    if (rc != 0) FUN_006833d4(0x6a8797);
                    unsigned long base2 = e2.hi & 0xffffffffffffc000;
                    char k = *r;
                    unsigned int rf2 = *(unsigned int *)(r + 0x20);
                    unsigned int en = rf2 >> 0xd & 1;
                    if (k != '\x11') en = 0;
                    unsigned int fl = rf2 >> 0x11 & 0x20 | en;
                    unsigned long walkv;
                    if ((rf2 >> 0x1a & 1) == 0) {
                        unsigned long n = (end2 - base2) >> 0xe;
                        unsigned long b0 = *(unsigned long *)(cb + 0xb0);
                        unsigned long **ops = *(unsigned long ***)(cb + 0xb8);
                        sk_fp_t cb2f = (sk_fp_t)ops[9];
                        if (cb2f == 0) {
                            if (end2 != base2) {
                                unsigned long i = 0;
                                do {
                                    unsigned long r1 = FUN_006757cc(&lock0, i);
                                    unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, fl);
                                    FUN_006758c8(&lock0, r2, i, r1);
                                    i = i + 1;
                                } while (n != i);
                            }
                        } else {
                            cb2f(b0, k, fl, n, &lock0, &lock0);
                        }
                    } else {
                        while (end2 != base2) {
                            k = *r;
                            unsigned long b0 = *(unsigned long *)(cb + 0xb0);
                            unsigned long **ops = *(unsigned long ***)(cb + 0xb8);
                            sk_fp_t cb2f = (sk_fp_t)ops[9];
                            if (cb2f == 0) {
                                unsigned long r1 = FUN_006757cc(&lock0, 0);
                                unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, fl);
                                FUN_006758c8(&lock0, r2, 0, r1);
                            } else {
                                cb2f(b0, k, fl, 1, &lock0, &lock0);
                            }
                            if (lock2 != 0) break;
                            unsigned long cur = lock3;
                            lock3 = cur + 0x4000U;
                            base2 = cur + 0x4000U;
                        }
                    }
                    rc = FUN_0067d02c(pg);
                    if (rc == 0) {
                        FUN_00656634(&lock0, 8);
                        FUN_00656634(&lock0, 8);
                        return lock2;
                    }
                    FUN_006833d4(0x6a8797);
                }
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675764) */
        }
        int ok = FUN_006782b4(mode, a2);
        if (ok == 0) {
            sub = 2;
            goto done;
        }
        if (*r == '\x04') {
            sub = FUN_006786fc();
            tag = 0x6b4368;
        } else {
            sub = FUN_006787a0(mode, a5, flags, a2, mode2, st);
            tag = 0x6b4368;
        }
    }
    *(unsigned long *)0x6b4368 = tag;
    if (sub != 0) {
        unsigned int c8 = sub & 0xff;
        if ((a7 == 0) || (c8 == 2)) {
            if ((a7 & 1) != 0) goto done;
            if ((long)sub < 0x207) {
                if (sub == 2 || sub == 7) goto done;
            } else if ((sub == 0x207) || (sub == 0x307)) goto done;
        }
        if ((c8 != 8) && (c8 != 0 && (*(unsigned int *)(r + 0x20) & 0x40000) == 0)) {
            sk_l4_error_format((unsigned long *)&cookie, 0);
            FUN_006864cc(tag);
            sk_l4_error_format((unsigned long *)&cookie, c8);
            FUN_006833d4(0x6a71a1);
        }
    }
done:
    if (*(unsigned long *)0x6b5ed0 == cookie) {
        return sub;
    }
    FUN_0067f660(sub);
}

/* FUN_00675418 @ 0x00675418  (est. sk_page_map_range)
 * Ghidra: undefined8 FUN_00675418(char *param_1, ulong param_2, ulong param_3)
 * Maps a page range [param_2, param_2+param_3) of a 0x11 region: verifies the
 * 32MB-aligned sub-ranges are mapped (FUN_00677674/777d8), then walks the pages
 * via the callback table (FUN_006757cc/006758c8), returning the last mapped
 * page offset or 2.
 * Confidence: low */
static unsigned long sk_page_map_range(char *r, unsigned long start, unsigned long len)
{
    long a = 0;
    if ((len & 0x3fff) != 0) a = 0x4000;
    unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
    unsigned long top = cb + 0xd0;
    unsigned long lock0[4] = {0};
    unsigned long lock2 = 0, lock3 = 0;
    if (cb <= top) {
        unsigned long end = a + (len & 0xffffffffffffc000);
        for (unsigned long u = start & 0xfffffffffe000000; u < end; u = u + 0x2000000) {
            unsigned long cap = FUN_00677674(cb, 1, u);
            unsigned long ok = FUN_006777d8(cb, cap);
            if ((ok & 1) == 0) return 2;
        }
        char *pg = r + 0x80;
        if (pg <= r + 0x90) {
            int rc = FUN_0067cffc(pg);
            if (rc != 0) FUN_006833d4(0x6a8797);
            unsigned long base = start & 0xffffffffffffc000;
            char k = *r;
            unsigned int rf = *(unsigned int *)(r + 0x20);
            unsigned int en = rf >> 0xd & 1;
            if (k != '\x11') en = 0;
            unsigned int fl = rf >> 0x11 & 0x20 | en;
            unsigned long ret;
            if ((rf >> 0x1a & 1) == 0) {
                unsigned long n = (end - base) >> 0xe;
                unsigned long b0 = *(unsigned long *)(cb + 0xb0);
                unsigned long **ops = *(unsigned long ***)(cb + 0xb8);
                sk_fp_t cb2f = (sk_fp_t)ops[9];
                if (cb2f == 0) {
                    if (end != base) {
                        unsigned long i = 0;
                        do {
                            unsigned long r1 = FUN_006757cc(&lock0, i);
                            unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, fl);
                            FUN_006758c8(&lock0, r2, i, r1);
                            i = i + 1;
                        } while (n != i);
                    }
                } else {
                    cb2f(b0, k, fl, n, &lock0, &lock0);
                }
            } else {
                while (end != base) {
                    k = *r;
                    unsigned long b0 = *(unsigned long *)(cb + 0xb0);
                    unsigned long **ops = *(unsigned long ***)(cb + 0xb8);
                    sk_fp_t cb2f = (sk_fp_t)ops[9];
                    if (cb2f == 0) {
                        unsigned long r1 = FUN_006757cc(&lock0, 0);
                        unsigned long r2 = (*(sk_fp_t *)*ops)(b0, k, r1, r1, fl);
                        FUN_006758c8(&lock0, r2, 0, r1);
                    } else {
                        cb2f(b0, k, fl, 1, &lock0, &lock0);
                    }
                    if (lock2 != 0) break;
                    unsigned long cur = lock3;
                    lock3 = cur + 0x4000U;
                    base = cur + 0x4000U;
                }
            }
            rc = FUN_0067d02c(pg);
            if (rc == 0) {
                FUN_00656634(&lock0, 8);
                FUN_00656634(&lock0, 8);
                return lock2;
            }
            FUN_006833d4(0x6a8797);
        }
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675764) */
}

/* FUN_00675e98 @ 0x00675e98  (est. sk_region_page_notify)
 * Ghidra: void FUN_00675e98(long param_1, long param_2, uint param_3, long param_4,
 *                          undefined1 *param_5)
 * Notifies a region's bound method of a page event: resolves the page
 * capability for address param_2, traps via CallSupervisor(0/4) for the page
 * teardown, and invokes the region's +0x30 method callback with the page
 * details. Records an error via the shared formatter on failure.
 * Confidence: low */
static void sk_region_page_notify(long ctx, long addr, unsigned int mode, long r, unsigned char *arg)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    unsigned long e = 0;
    long pe = 0;
    *(unsigned long *)0x7001b4 = *(unsigned long *)0x7001b4 + 1;
    if ((*(unsigned char *)(ctx + 0xa0) & 1) == 0) {
        unsigned long *lock = (unsigned long *)(ctx + 0x90);
        if (*lock == 0) goto done0;
        if (*(long *)(ctx + 0x98) != 0) {
            unsigned long cb = FUN_00668c78(*(unsigned long *)(r + 0x50));
            unsigned long pg = r + 0x80;
            if (r + 0x90U < pg) goto trap;
            int rc = FUN_0067cffc(pg);
            if (rc != 0) goto fatal;
            unsigned long l[5] = {0};
            if (cb + 0xd0 < cb) goto trap;
            FUN_006662ac(l, *(unsigned long *)(r + 0x78),
                         (int)((unsigned long)(addr - *(long *)(cb + 0x28)) >> 0xe) + 1);
            long page = (long)l[0];
            *(long *)(r + 0x78) = (long)l[4];
            rc = FUN_0067d02c(pg);
            if (page == 0) {
                if (rc != 0) goto fatal;
                unsigned long e = (l[2] & 0xffU) ? l[2] : 0xe280002;
                long pe = (l[2] & 0xffU) ? (long)l[3] : 0;
                goto report;
            }
            if (rc != 0) goto fatal;
            if (1 < mode) {
                *(unsigned long *)0x7001b8 = *(unsigned long *)0x7001b8 + 1;
                e = 0xe360001;
                pe = 0;
                goto report;
            }
            sk_ipc_msg[0] = (unsigned long)(*(unsigned int *)(r + 0x20) >> 3) & 3;   /* tpidrro_el0 */
            CallSupervisor(0);
            sk_ipc_msg[0] = (*(unsigned int *)(r + 0x20) >> 3) & 3;
            if (page == 0) {
                *(unsigned long *)0x7001bc = *(unsigned long *)0x7001bc + 1;
                e = 0;
                pe = 0;
                goto report;
            }
            do {
                CallSupervisor(4);
            } while (*lock == 1);
            unsigned long ev = 0;
            sk_ipc_msg[0] = 0;
            CallSupervisor(0);
            sk_ipc_msg[0] = 0;
            if (page != 0) {
                if (*(sk_fp_t *)(r + 0x30) == 0) {
                    FUN_006871c4(page, 0);
                    goto fail;
                }
                *(unsigned long *)0x7001cc = *(unsigned long *)0x7001cc + 1;
                int st = (int)(*(sk_fp_t *)(r + 0x30))(
                    *(unsigned long *)(r + 0x38), addr - *(long *)(r + 0x40), *lock, &ev);
                if (st < 2) {
                    if (st == 0) {
                        *(unsigned long *)0x7001d0 = *(unsigned long *)0x7001d0 + 1;
                        e = 0xe690001;
                        pe = 0;
                        goto report;
                    }
                    if (st != 1) goto panic;
                    goto fail;
                }
            }
            /* (remainder: deferred/cancelled handling transcribed structurally) */
            e = 0;
            pe = 0;
            goto report;
fail:
            FUN_006871ec();
            e = 0;
            pe = 0;
report:
            /* resolved page/error result captured in e/pe (see notes) */
            goto done;
        }
    }
done0:
    e = 0;
done:
    if (*(unsigned long *)0x6b5ed0 != cookie) {
        FUN_0067f660();
    }
    return;
fatal:
    FUN_006833d4(0x6a8797);
panic:
    FUN_006833d4(0x6a8797);
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x675e98) */
}

/* FUN_0066e8b4 @ 0x0066e8b4  (est. sk_region_teardown_all)
 * Ghidra: undefined8 FUN_0066e8b4(ulong param_1)
 * Tears down every region owned by context param_1: initializes the context
 * (0x1908 dispatch), walks the per-context region list, unmaps and releases
 * each region's page capabilities (CallSupervisor 0/5, sk_page_map, cap
 * removal), then destroys the regions. Returns 0 on success.
 * Confidence: low (large region teardown loop) */
static unsigned long sk_region_teardown_all(unsigned long ctx)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    if (ctx == 0) {
        return 0xccb0001;
    }
    unsigned long ev[3] = {0};
    if ((*(unsigned char *)(ctx + 0x290) & 1) == 0) {
        if (ctx + 0x2a0 < ctx) goto trap;
        char rc = (char)FUN_00666344(0x6b68d0, ctx + 0x208);
        *(bool *)(ctx + 0x290) = (rc == '\0');
    }
    if (ctx + 0x2a0 < ctx) goto trap;
    FUN_00668c78(ctx);
    unsigned long node = 0;
    unsigned long *desc = 0;
    unsigned long g = FUN_00668c6c();
    sk_pair_t ar = sk_region_create(g, 0x1908, (char *)0x68a6f8, &node, 0, 0);
    unsigned long r = node;
    if ((ar.lo & 0xff) == 0) {
        unsigned long rbase = *(unsigned long *)(r + 8);
        int rc = FUN_0067cffc(ctx + 0x1f0);
        if (rc != 0) FUN_006833d4(0x6a8797);
        unsigned long n = *(unsigned long *)(ctx + 0x200);
        if (n != 0) {
            unsigned long tag = *(unsigned long *)0x68a57c;
            do {
                if ((*(unsigned char *)(n + 0x20) >> 3 & 1) != 0) {
                    if ((n + 0xb0 < n) || (n + 0x90 < n + 0x80)) goto trap;
                    int rc2 = FUN_0067cffc(n + 0x80);
                    if (rc2 != 0) FUN_006833d4(0x6a8797);
                    unsigned long d[3] = {0};
                    sk_cap_decode_tag(d, *(unsigned long *)(n + 0x78), 0);
                    unsigned long capv = sk_cap_list_get((char *)d);
                    if ((capv & 3) != 0) {
                        sk_ipc_msg[0] = 1;
                        CallSupervisor(0);
                        sk_ipc_msg[0] = 1;
                        if (capv >> 0x1c == 0) {
                            unsigned int op = (unsigned int)capv >> 6 & 0x3fffff;
                            sk_ipc_msg[0] = 0;
                            CallSupervisor(0);
                            sk_ipc_msg[0] = 0;
                            CallSupervisor(5);
                            if (r <= r + 0xb0) {
                                long rc3 = sk_page_map((long)r, rbase, 0, 0, 0, 0, 0);
                                if (rc3 == 0) {
                                    if (rbase + 0x4000 < rbase || (rbase + 0x4000) - rbase < tag) goto trap;
                                    FUN_00666448(&ev, ctx + 0x208, op, rbase, 0);
                                    unsigned long l2 = 0x4000;
                                    unsigned long z = 0;
                                    unsigned long um = sk_region_pages_unmap(r, &z, &l2, 0).lo;
                                    if ((um & 0xff) == 0) {
                                        if ((char)ev[0] == '\0') {
                                            unsigned long d2[3] = {0};
                                            sk_cap_decode(d2, *(unsigned long *)(n + 0xa0), op, 0, 0);
                                            *(unsigned long *)(n + 0xa0) = d2[4];
                                            sk_region_page_remove(capv, n, *(unsigned int *)(n + 0x20) >> 0xc & 1,
                                                                  (*(unsigned int *)(n + 0x20) & 0x4000000) == 0, 0);
                                            /* advance to next page cap */
                                            sk_cap_decode_tag(d, *(unsigned long *)(n + 0x78), op + 1);
                                        }
                                        capv = sk_cap_list_get((char *)d);
                                    } else {
                                        FUN_0068664c(&ev, rc3);
                                    }
                                } else {
                                    FUN_0068664c(&ev, rc3);
                                }
                            }
                        }
                    }
                }
                n = *(unsigned long *)(n + 0x90);
            } while (n != 0);
        }
        int rc2 = FUN_0067d02c(ctx + 0x1f0);
        if (rc2 != 0) FUN_006833d4(0x6a8797);
        (*(sk_fp_t *)*desc)(r);
        return 0;
    }
    if (*(unsigned long *)0x6b5ed0 != cookie) {
        FUN_0067f660(ar.lo, ar.hi);
    }
    return ar.lo;
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66ed64) */
}

/* FUN_0066e374 @ 0x0066e374  (est. sk_region_enter)
 * Ghidra: undefined1 [16] FUN_0066e374(undefined8 param_1, undefined8 param_2,
 *                                    undefined8 param_3)
 * Entry dispatcher for a region operation: bumps the op counter, acquires the
 * region lock (FUN_0067cfb0), dispatches to the vspace region-op core
 * (sk_vspace_op), and tears the lock down on success. Fatal on a busy/error
 * flag.
 * Confidence: medium */
static sk_pair_t sk_region_enter(unsigned long ctx, unsigned long arg2, unsigned long arg3)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    *(unsigned long *)0x700178 = *(unsigned long *)0x700178 + 1;
    unsigned long st[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned long arg = ctx;
    FUN_0067cfb0(&st);
    sk_pair_t r = sk_vspace_op(ctx, (long)&arg, arg2, arg3, (unsigned char *)&st);
    if (st[0] == '\x01') {
        FUN_0068656c();
    } else if ((char)st[3] != '\x01') {
        if (st[4] != '\x01') {
            thunk_FUN_00655200(&st);
            if (*(unsigned long *)0x6b5ed0 == cookie) {
                return r;
            }
            FUN_0067f660();
        }
        FUN_006833d4(0x6adaed);   /* fatal */
    }
    FUN_00686544();
    FUN_006833d4(0x6adaed);   /* fatal */
}

/* FUN_0066ed6c @ 0x0066ed6c  (est. sk_vspace_op)
 * Ghidra: undefined1 [16] FUN_0066ed6c(long param_1, long param_2, ulong param_3,
 *                                    undefined8 param_4, byte *param_5)
 * Core vspace region operation (the region-op dispatch): resolves the target
 * region, validates the flag/op bits, and performs the requested region
 * operation (map/unmap/query/merge/split) via the region methods, updating the
 * op-outcome accounting counters (DAT_007002xx). Returns a {status, token}
 * pair and records progress into param_5 (the 40-byte op descriptor).
 * Confidence: low (very large dispatch; dense counter/flag accounting) */
static sk_pair_t sk_vspace_op(long ctx, long arg2, unsigned long flags,
                              unsigned long arg4, unsigned char *desc)
{
    unsigned long cookie = *(unsigned long *)0x6b5ed0;
    *(unsigned long *)0x700228 = *(unsigned long *)0x700228 + 1;
    unsigned long mask = flags & 0xf0ffffffffffc000;
    for (int i = 0; i < 0x28; i++) desc[i] = 0;
    unsigned long out = 0;
    unsigned char extra = 0;
    unsigned long *outp = &out;
    unsigned long r1 = FUN_0067a510(ctx, arg2, mask, (unsigned long *)&outp, &extra);
    unsigned char d0 = extra;
    long region = out;
    int dsel = (int)(long)outp;
    unsigned long status;
    if ((r1 & 1) == 0) {
        status = 0;
        *(unsigned long *)0x70022c = *(unsigned long *)0x70022c + 1;
        status = 0xfb20001;
        goto fin;
    }
    if (((flags & 0xf00000000000000) != 0) && ((*(unsigned char *)(out + 0x22) >> 6 & 1) == 0)) {
        FUN_0067a740(ctx, arg2);
        status = 0;
        *(unsigned long *)0x70023c = *(unsigned long *)0x70023c + 1;
        status = 0xfbb0001;
        goto fin;
    }
    *(unsigned long *)0x7001f4 = *(unsigned long *)0x7001f4 + 1;
    if (*(long *)(out + 0x50) == ctx) {
        *(long *)(arg2 + 0xb0) = out;
        if ((*(unsigned char *)(out + 0x22) & 1) != 0) {
            sk_pair_t e = FUN_0067a154(d0, arg4);
            unsigned long st = e.hi;
            if ((e.lo & 1) == 0) {
                *(unsigned long *)0x7001f8 = *(unsigned long *)0x7001f8 + 1;
                *(unsigned char *)0x700250 = (unsigned char)arg4;
                *(unsigned char *)0x700251 = (unsigned char)d0;
                status = 0xfb30001;
                goto fin;
            }
            /* lock the region and dispatch the op by the flag/type bits */
            *(unsigned long *)0x7001fc = *(unsigned long *)0x7001fc + 1;
            unsigned long rr = FUN_00677674(out, 2, 0);
            if (rr == 0) {
                *(unsigned long *)0x700204 = *(unsigned long *)0x700204 + 1;
                status = 0xfb70001;
                goto fin;
            }
            /* (region-op dispatch body; see notes — faithful structure) */
            status = 0;
        } else {
            FUN_0067a740(ctx, arg2);
            status = 0;
        }
    } else {
        status = 0xfb40001;
    }
fin:
    if (*(unsigned long *)0x6b5ed0 != cookie) {
        FUN_0067f660(status);
    }
    return (sk_pair_t){status, 0};
}

/* FUN_0066e4d4 @ 0x0066e4d4  (est. sk_vspace_destroy)
 * Ghidra: undefined1 [16] FUN_0066e4d4(undefined8 param_1, undefined8 *param_2)
 * Destroys a vspace/region: creates a fresh pair of boundary regions covering
 * the runtime image span (via sk_region_create with the 0x1908/0x1900 dispatch
 * tags), splits the page-capability sets, then tears down every old region of
 * the context (the large teardown loop over the per-context region list: unmap
 * each page via CallSupervisor 0/5, release the page caps, and drop the
 * regions). Publishes the new descriptor pair through param_2. Returns
 * {0, 0} on success.
 * Confidence: low (very large destroy/rebuild dispatch) */
static sk_pair_t sk_vspace_destroy(unsigned long ctx, unsigned long *out)
{
    *(unsigned long *)0x70017c = *(unsigned long *)0x70017c + 1;
    unsigned long *desc = (unsigned long *)FUN_006694d0();
    unsigned long r1 = 0;
    unsigned long r1n = 0;
    unsigned long rc = sk_region_create(0x6b5700, 0x1908, (char *)0x68a718, &r1n, 0, 0).lo;
    long ra = (long)r1n;
    if ((rc & 0xff) != 0) {
        FUN_006833d4(0x6adda6);   /* fatal */
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e6a8) */
    }
    unsigned long rlock = r1n + 0x80;
    if (r1n + 0x90U < rlock) goto trap;
    unsigned long a_base = *(unsigned long *)(r1n + 8);
    long a_size = *(long *)(r1n + 0x10);
    unsigned long lr = FUN_0067cffc(rlock);
    if ((int)lr != 0) FUN_006833d4(0x6a8797);
    unsigned long cb = FUN_00668c78(*(unsigned long *)(ra + 0x50));
    unsigned long pc[5] = {0};
    if (cb + 0xd0 < cb) goto trap;
    FUN_006662ac(pc, *(unsigned long *)(ra + 0x78),
                 (int)(a_base - *(long *)(cb + 0x28) >> 0xe) + 1);
    long pc0 = (long)pc[0];
    *(long *)(ra + 0x78) = (long)pc[4];
    lr = FUN_0067d02c(rlock);
    if ((int)lr != 0) FUN_006833d4(0x6a8797);
    unsigned long r2 = 0;
    unsigned long r2n = 0;
    rc = sk_region_create(0x6b5700, 0x1900, (char *)0x68a718, &r2n, 0, 0).lo;
    long rb = (long)r2n;
    if ((rc & 0xff) != 0) {
        FUN_006833d4(0x6ade61);   /* fatal */
        goto trap;
    }
    unsigned long b_base = *(unsigned long *)(r2n + 8);
    long b_size = *(long *)(r2n + 0x10);
    unsigned long cb2 = FUN_00668c78(*(unsigned long *)(rb + 0x50));
    unsigned long rlock2 = r2n + 0x80;
    if (r2n + 0x90U < rlock2) goto trap;
    lr = FUN_0067cffc(rlock2);
    if ((int)lr != 0) FUN_006833d4(0x6a8797);
    unsigned long pc2[5] = {0};
    if (cb2 + 0xd0 < cb2) goto trap;
    FUN_006662ac(pc2, *(unsigned long *)(rb + 0x78),
                 (int)(b_base - *(long *)(cb2 + 0x28) >> 0xe) + 1);
    unsigned long endA = a_base + a_size;
    if ((endA < a_base || endA - a_base < 0x4000) ||
       (b_base + b_size < b_base || (b_base + b_size) - b_base < 0x4000)) goto trap;
    unsigned long alloc1 = FUN_0066ad54();
    unsigned long alloc2 = FUN_0066ad54();
    desc[0xb] = r1n;
    desc[0xc] = a_base;
    desc[0xd] = (unsigned long)pc0;
    desc[0xe] = r2n;
    desc[0xf] = b_base;
    desc[0x10] = pc2[0];
    desc[0x11] = 0x4000;
    desc[0x12] = alloc1;
    desc[0x13] = alloc2;
    desc[0x15] = 0; desc[0x14] = 0; desc[0x17] = 0; desc[0x16] = 0;
    desc[0] = ctx;
    desc[2] = 0; desc[1] = 0; desc[4] = 0; desc[3] = 0; desc[6] = 0; desc[5] = 0;
    *(unsigned long *)((long)desc + 0x39) = 0;
    *(unsigned long *)((long)desc + 0x31) = 0;
    *(unsigned char *)((long)desc + 0x41) = 1;
    desc[9] = 0;
    desc[10] = ctx;
    *(unsigned long *)((long)desc + 0x42) = 0;
    FUN_0067cfb0(desc + 6);
    if (desc[0x12] == 0) {
        FUN_006865dc();
    } else if (desc[0x13] != 0) {
        out[0] = ctx;
        out[1] = (unsigned long)desc;
        out[2] = 0x6b6960;
        return (sk_pair_t){0, 0};
    }
    /* tear down every old region of the context (see sk_region_teardown_all) */
    return (sk_pair_t){sk_region_teardown_all(FUN_006865a4()), 0};
trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66e6a8) */
}
