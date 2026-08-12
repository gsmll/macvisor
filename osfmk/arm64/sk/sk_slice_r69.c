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
 * Confidence: medium */
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
 * Confidence: medium */
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
        do {
            v = sk_cap_list_get((char *)d2);
            if ((v & 3) == 0) {
                out[0] = 0;
                out[1] = 0;
                out[2] = acc;
                out[3] = cap;
                return;
            }
            unsigned long r[4] = {0, 0, 0, 0};
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
    if ((b <= p && p + 1 <= lim) && p <= p + 1) {
        *p = 0;
        do {
            unsigned int i = idx;
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
    do {
        bool was = first;
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
        unsigned long v = CONCAT71(0, d2[1]);   /* hi word artifact */
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
            unsigned long rc = (**(unsigned long **)(r[4] + 0x18))(r[3], &newsz);
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
        rc = (**(unsigned long **)r[4])();
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
        unsigned long *pc = (unsigned long *)FUN_00668c94();
        unsigned long v = *pc;
        do {
            unsigned long cur = v;
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
