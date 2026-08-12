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
extern long FUN_00668c94();
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
extern long FUN_0066a9bc();
extern long FUN_0066ab40();
extern long FUN_0066ad54();
extern long FUN_0066af84();
extern long FUN_006766cc();
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
extern long FUN_00679d44();
extern long FUN_0067a154();
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
extern long FUN_0068642c();
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
extern long FUN_00686c74();
extern long FUN_00686c8c();
extern long FUN_00686d10();
extern long FUN_00686d58();
extern long FUN_00686d90();
extern long FUN_00686dc8();
extern long FUN_00686e00();
extern long FUN_00686e38();
extern long FUN_00686e70();
extern long FUN_00686ea8();
extern long FUN_00686ee0();
extern long FUN_00686f08();
extern long FUN_00686f30();
extern long FUN_00686f68();
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
extern long FUN_00668c94();
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
extern long FUN_006766cc();
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
extern long FUN_00679d44();
extern long FUN_0067a154();
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
extern long FUN_00686c74();
extern long FUN_00686c8c();
extern long FUN_00686d10();
extern long FUN_00686d58();
extern long FUN_00686d90();
extern long FUN_00686dc8();
extern long FUN_00686e00();
extern long FUN_00686e38();
extern long FUN_00686e70();
extern long FUN_00686ea8();
extern long FUN_00686ee0();
extern long FUN_00686f08();
extern long FUN_00686f30();
extern long FUN_00686f68();
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

/* In-range static helper forward declarations (definitions follow). */
static void sk_cap_decode(unsigned long *out, unsigned long cap, unsigned long op,
                          unsigned long size, unsigned int flags);
static void sk_l4_error_format(unsigned long *out, unsigned char code);
static void sk_page_tree_lookup(unsigned long key);
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

/* FUN_00674e98 @ 0x00674e98  (est. sk_l4_error_format)
 * Ghidra: void FUN_00674e98(undefined8 *param_1, byte param_2)
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

/* FUN_0066b884 @ 0x0066b884  (est. sk_cap_decode)
 * Ghidra: void FUN_0066b884(ulong *param_1, ulong param_2, undefined8 param_3,
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
        sk_pair_t r1 = FUN_0066c8ac(ctx, cap, 8, 0);
        if (((r1.lo & 0xff) != 0) ||
            (r1 = FUN_0066c8ac(ctx, (unsigned long)(opc << 6 | 1) | size << 0x1c, 8, 0),
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
                sk_pair_t r = FUN_0066c8ac(bucket, e, 8, 0);
                if ((r.lo & 0xff) == 0) {
                    out[0] = size;
                    *(unsigned char *)(out + 1) = 1;
                    e = cap & 0xffffffffffffffc3 | (unsigned long)(slot * 4 + 4);
                    goto fill_e;
                }
fail_put:
                out[0] = 0;
                out[1] = 0;
                *(unsigned long (*)[2])(out + 2) = (unsigned long[2]){r1.lo, r1.hi};
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
                    sk_pair_t _pc = FUN_0066ca30(cb);
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
            sk_pair_t _p = FUN_0066ca30(b, e);
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
        sk_pair_t r = FUN_0066c204(bucket, op);
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
            sk_pair_t _p2 = FUN_0066ca30(bucket, (unsigned long)(opc << 6 | 1) | size << 0x1c);
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

/* FUN_0066c8ac @ 0x0066c8ac  (est. sk_cap_bucket_insert)
 * Ghidra: undefined1 [16] FUN_0066c8ac(ulong *param_1, ulong param_2, uint param_3,
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
    unsigned long *end = bucket + 8;
    unsigned long *lim = 0;
    if (bucket != 0) lim = end;
    unsigned int op = (unsigned int)cap >> 6 & 0x3fffff;
    status = 0x990001;
    unsigned long *p = bucket;
    for (;;) {
        if (((p < bucket) || (lim < p + 1)) || (p + 1 < p)) goto sb_break;
        unsigned long pos = idx;
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
            sk_pair_t r;
            r.hi = 0;
            r.lo = status;
            return r;
        }
    }
sb_break:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c9ec) */
}

/* FUN_0066ca30 @ 0x0066ca30  (est. sk_cap_bucket_op)
 * Ghidra: void FUN_0066ca30(long param_1, undefined8 param_2)
 * Performs a capability-bucket operation: bounds-checks the bucket, invokes the
 * bucket resolver FUN_0066cac4 with (local, param_1, param_2, 0), and returns.
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
            FUN_0066cac4(local, bucket, arg, 0);
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

/* FUN_0066c204 @ 0x0066c204  (est. sk_cap_bucket_resolve)
 * Ghidra: void FUN_0066c204(ulong *param_1, uint param_2)
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

/* FUN_0066c5d0 @ 0x0066c5d0  (est. sk_cap_tag_type)
 * Ghidra: uint FUN_0066c5d0(uint param_1)
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

/* FUN_0066c5f8 @ 0x0066c5f8  (est. sk_cap_iterate_free)
 * Ghidra: void FUN_0066c5f8(ulong param_1, code *UNRECOVERED_JUMPTABLE)
 * Iterates a capability value (param_1): for the direct (type 0/1) form calls
 * the callback with the tag field; for the type-2 bucket form calls the
 * callback for each occupied slot then frees the bucket; for the type-3 form
 * recursively releases the pointed structure via FUN_0066db74.
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
                FUN_0066db74();
                return;
            }
        }
    }
sb_break:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x66c76c) */
}

/* FUN_0066c354 @ 0x0066c354  (est. sk_cap_list_get)
 * Ghidra: ulong FUN_0066c354(char *param_1)
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

/* FUN_0066c084 @ 0x0066c084  (est. sk_cap_decode_tag)
 * Ghidra: void FUN_0066c084(undefined8 *param_1, ulong param_2, uint param_3)
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
                unsigned long p = FUN_0066c204(base).lo;
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

/* FUN_0066cac4 @ 0x0066cac4  (est. sk_cap_bucket_move)
 * Ghidra: void FUN_0066cac4(ulong *param_1, ulong *param_2, uint param_3,
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
            unsigned long lo = r.lo;
            unsigned long hi = r.hi;
            if ((lo & 0xff) == 0) goto done;
            goto err_store;
        }
        if (p7 < bucket) goto trap;
        unsigned long tail = bucket[7];
        sk_pair_t r = sk_cap_bucket_insert(bucket, cap, 8, 1);
        unsigned long lo = r.lo;
        unsigned long hi = r.hi;
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

/* FUN_0066db74 @ 0x0066db74  (est. sk_cap_bucket_free_rec)
 * Ghidra: void FUN_0066db74(ulong *param_1, code *param_2)
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

/* FUN_0066b1fc @ 0x0066b1fc  (est. sk_page_tree_lookup)
 * Ghidra: void FUN_0066b1fc(ulong param_1)
 * Searches the page-block free-tree (root at ctx+0x20) for a node whose key
 * (+0x28) equals (param_1 & ~0x3fff); descends left (+0x38) when the target is
 * lower, right (+0x40) otherwise. Returns via the tree node walk.
 * Confidence: medium */
static void sk_page_tree_lookup(unsigned long key)
{
    long ctx = FUN_0065be08(0x6fea48, 4, 8);
    unsigned long node = *(unsigned long *)(ctx + 0x20);
    while (node != 0) {
        if (*(unsigned long *)(node + 0x28) == (key & 0xffffffffffffc000)) {
            if (node <= node + 0x48) {
                return;
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
}

/* FUN_0066b468 @ 0x0066b468  (est. sk_page_bitmap_test_set)
 * Ghidra: bool FUN_0066b468(ulong *param_1, long param_2)
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

/* FUN_0066b038 @ 0x0066b038  (est. sk_page_tree_insert)
 * Ghidra: void FUN_0066b038(ulong *param_1, ulong param_2)
 * Inserts page-block node param_2 into the ordered free-tree whose root is
 * *param_1, keyed by the block base (+0x28, 16KB-aligned). Duplicate keys are a
 * fatal error. Rebalances via the child balance bytes at +0x22 and updates the
 * new root back through *param_1.
 * Confidence: medium */
static void sk_page_tree_insert(unsigned long *rootp, unsigned long node)
{
    unsigned long cur = *rootp;
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
    FUN_0066b038();
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
        unsigned long r = *(unsigned long *)(cur + 0x40);
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

/* FUN_0066b270 @ 0x0066b270  (est. sk_page_block_alloc)
 * Ghidra: ulong FUN_0066b270(long param_1, ulong param_2, ulong param_3)
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
                    unsigned long rc = FUN_0066b468(blk, addr);
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
            FUN_0066b038(ctx + 4, blk);
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

/* FUN_0066b520 @ 0x0066b520  (est. sk_page_block_free)
 * Ghidra: void FUN_0066b520(ulong param_1, long param_2)
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
    long *blk = (long *)FUN_0066b1fc(base);
    if (base < end) {
        long *head = blk + 9;
        long *node = blk;
        do {
            unsigned long next = base + 0x40;
            if (node == 0) {
                blk = (long *)FUN_0066b1fc(base);
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
                    blk = (long *)FUN_0066b1fc(base);
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
                int rc = FUN_0066b468(node, base);
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
 * (FUN_0066b884), passing (param_1, param_2, 0, 0) and a zero op.
 * Confidence: medium */
static void sk_tail_cap_decode_wrap(unsigned long a, unsigned long b)
{
    FUN_0066b884(a, b, 0, 0, 0);
}

/* FUN_0066bce0 @ 0x0066bce0  (est. sk_tail_cap_decode_wrap0)
 * Ghidra: void FUN_0066bce0(void)
 * Wrapper over the capability-decode helper FUN_0066b884; the decompiler
 * dropped all arguments (decodes the caller's current capability context).
 * Confidence: medium */
static void sk_tail_cap_decode_wrap0(void)
{
    FUN_0066b884(0, 0, 0, 0, 0);
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
 * Wrapper invoking the L4 error-code formatter FUN_00674e98.
 * Confidence: medium */
static void sk_tail_err_fmt0(void)
{
    FUN_00674e98();
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
 * Invokes the L4 error-code formatter FUN_00674e98 on a stack scratch buffer.
 * Confidence: medium */
static void sk_tail_err_fmt1(void)
{
    FUN_00674e98(&stack0x00000010);
}

/* FUN_006765c4 @ 0x006765c4  (est. sk_tail_err_fmt2)
 * Ghidra: void FUN_006765c4(void)
 * Invokes the L4 error-code formatter FUN_00674e98 on a stack scratch buffer.
 * Confidence: medium */
static void sk_tail_err_fmt2(void)
{
    FUN_00674e98(&stack0x00000018);
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
