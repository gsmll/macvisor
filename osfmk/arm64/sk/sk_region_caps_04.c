/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 04: caps region 0x8ec20 - 0x92698.
 *
 * This region is the Exclave-Launcher IPC / cap-slot subsystem (string
 * anchors s_InternalExclaveLauncher_External_005c0dc0,
 * s_init_endpoint_asid_conclaveId_pa_005c0fc0). It is heavily obfuscated:
 * most functions run through opaque-predicate branches and a shared
 * deobfuscation buffer (DAT_00657778, data at DAT_00657798). Bodies below
 * preserve the original control flow and arithmetic; obfuscation semantics
 * are described per function. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

#define ROR64(x, n)  (((x) >> (n)) | ((x) << (64 - (n))))
#define CANARY      0xd37adfb44bfffed6ull
#define OBF_PRED()  (*(long *)(*(long *)((char *)cl4_ctx + 0x20) + 0x10) == 0)
/* Ghidra carry/borrow flags on 64-bit add/sub. */
#define SCARRY8(a, b)  (((unsigned long)(a) + (unsigned long)(b)) < (unsigned long)(a))
#define SBORROW8(a, b) ((unsigned long)(a) < (unsigned long)(b))

/* 16-byte return pair used by the reference getters. */
typedef struct { unsigned long lo; unsigned long hi; } cl4_pair_t;

void cl4_obf_done_1(unsigned long a, unsigned long b);   /* FUN_0008f7ac */
void cl4_ep_validate(unsigned char *, unsigned long, unsigned long, unsigned char); /* FUN_00090508 */
void cl4_ep_validate_dispatch_1(void);                  /* FUN_000907b0 */
void cl4_ep_setup_dispatch(void);                       /* FUN_000909e4 */
void cl4_ep_setup(long);                                /* FUN_0009087c */
void cl4_ep_unregister(void);                           /* FUN_000907d0 */
static unsigned long cl4_binding_describe(unsigned long tag, void *handler,
                                          unsigned long str, unsigned long fetch);
cl4_pair_t cl4_op_call3(long, unsigned long, unsigned long, unsigned long);  /* FUN_00091f8c */
cl4_pair_t cl4_op_call1(long, unsigned long);                              /* FUN_000920ec */
cl4_pair_t cl4_op_call0(long);                                             /* FUN_00092270 */
cl4_pair_t cl4_ep_send(long, unsigned long, unsigned long, unsigned long); /* FUN_00092394 */
cl4_pair_t cl4_ep_send2(long, unsigned long, unsigned long);              /* FUN_000924d4 */
cl4_pair_t cl4_ep_send3(long, unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0009261c */
void cl4_ep_send4(unsigned long, unsigned long, unsigned long, unsigned long, long); /* FUN_00092698 */
void cl4_trap(int a, unsigned long addr) __attribute__((noreturn));

/* ---- Shared cL4 helpers OUTSIDE this slice (extern, one-line notes) ---- */
extern void cl4_buf_release(unsigned long buf);          /* FUN_0036b118 */
extern void cl4_buf_release_fast(void);                  /* FUN_0036b6ac */
extern unsigned long cl4_buf_acquire(unsigned long buf); /* FUN_0036b270 */
extern int cl4_buf_cond(unsigned long buf);              /* FUN_003a261c */
extern unsigned long cl4_buf_key(int a);                 /* FUN_00324bf0 */
extern long cl4_buf_resolve(unsigned long buf, unsigned long key); /* FUN_00362acc */
extern long cl4_buf_resolve_fallback(void);              /* FUN_0006f6b4 */
extern void cl4_buf_frame_teardown(unsigned long *frame);/* FUN_0036a20c */
extern void cl4_buf_frame_init(long *ptr, unsigned long *frame); /* FUN_00002828 */
extern void cl4_buf_frame_fill(unsigned long *word, unsigned long *frame); /* FUN_0008110c */
extern unsigned long cl4_result_fetch(void);             /* FUN_001032b8 */
extern unsigned long cl4_result_advance(unsigned long o);/* FUN_0010319c */
extern void cl4_stack_canary_fail(void) __attribute__((noreturn)); /* FUN_0011d7e8 */
extern void cl4_defer_cleanup(void *fn, unsigned long *frame, unsigned long buf); /* FUN_001ae20c */
extern void cl4_fatal(const char *file, unsigned long line, unsigned long kind,
                      unsigned long code, unsigned long detail,
                      const char *func, unsigned long fnlen, unsigned long a, ...)
    __attribute__((noreturn));                           /* FUN_001afa84 */
extern void cl4_frame_restore(unsigned long *frame);     /* FUN_000026e8 */
extern void cl4_frame_capture(unsigned long *dst, unsigned long *src); /* FUN_0006a4c0 */
extern void cl4_slot_store(unsigned long *ptr, unsigned long val); /* FUN_0006e7c0 */
extern unsigned long cl4_slot_load(unsigned long *slot); /* FUN_00084100 */
extern void cl4_slot_open(unsigned long *slot);          /* FUN_0008e3b0 */
extern void cl4_slot_ref(unsigned long *slot);           /* FUN_0009455c */
extern void cl4_status_report(unsigned long status);     /* FUN_000944a8 */
extern unsigned long cl4_cap_check1(unsigned long a, unsigned long b, unsigned long c); /* FUN_000944f8 */
extern void cl4_cap_check2(unsigned long *a, unsigned long b, unsigned long c, unsigned long *d); /* FUN_000944b4 */
extern void cl4_cap_check3(unsigned long *a, unsigned long b); /* FUN_000944d8 */
extern int cl4_status_cmp(unsigned long a, unsigned long b); /* FUN_0006e6dc */
extern unsigned long cl4_msg_fetch(void);                /* FUN_0007c1c4 */
extern void cl4_field_lock(unsigned long *field, unsigned long *frame, unsigned long kind, unsigned long a); /* FUN_0036a1a0 */
extern unsigned long cl4_zone_alloc(unsigned long size, unsigned long count, unsigned long tag); /* FUN_0036a940 */
extern unsigned long cl4_alloc_bytes(unsigned long size, unsigned long tag); /* FUN_0036a804 */
extern void cl4_field_reset(unsigned long *field, unsigned long v); /* FUN_0036b7f8 */
extern void cl4_field_reset1(unsigned long *field, unsigned long v); /* FUN_0036b834 */
extern long cl4_obj_from_slot(unsigned long *slot);      /* FUN_0036b8b0 */
extern void cl4_ref_kind(unsigned long obj, int kind);   /* FUN_0036b2d0 */
extern void cl4_slot_release(unsigned long *slot);       /* FUN_0036b8c0 */
extern void cl4_slot_block_teardown(void);               /* FUN_0036b6f4 */
extern void cl4_self_capture(void);                      /* FUN_000027e8 */
extern void cl4_slot_commit(void);                       /* FUN_0008409c */
extern void cl4_cap_ref_enter(void);                     /* FUN_0009461c */
extern unsigned long cl4_cap_ref_fetch(void);            /* FUN_00094578 */
extern void cl4_cap_ref_advance(void);                   /* FUN_00094628 */
extern void cl4_cap_ref_setup(unsigned long *a, unsigned long *frame); /* FUN_0009456c */
extern void cl4_cap_ref_begin(unsigned long *a, unsigned long *frame); /* FUN_000945d0 */
extern long cl4_class_lookup(unsigned long *cls, unsigned long *vtable); /* FUN_00002534 */
extern void cl4_register_cleanup(void *cb);              /* FUN_00077770 */
extern void cl4_notify_append(void);                     /* FUN_001a1564 */
extern void cl4_notify_grow(int cond, unsigned long idx, int a); /* FUN_001a0774 */
extern long cl4_zalloc(unsigned long n, unsigned long n2); /* FUN_000719dc */
extern unsigned long cl4_realloc(unsigned long obj, unsigned long n); /* FUN_000828a4 */
extern unsigned long cl4_alloc_buf(unsigned long size);  /* FUN_00117cc4 */
extern unsigned long cl4_msg_obj_build(unsigned long a, unsigned long b); /* FUN_000dc634 */
extern unsigned long cl4_msg_obj_new(unsigned long a);   /* FUN_000dcde4 */
extern unsigned long cl4_cap_new(unsigned long buf, unsigned long a, unsigned long b, unsigned long c); /* FUN_001f0130 */
extern unsigned long cl4_handle_fetch(unsigned long idx);/* FUN_001003e8 */
extern long cl4_endpoint_new(unsigned long kind, unsigned long *slot); /* FUN_000ff728 */
extern unsigned long cl4_op_attach(unsigned long a, unsigned long *slot, unsigned long b, unsigned long c); /* FUN_00085258 */
extern unsigned long cl4_op_class(unsigned long a);      /* FUN_00086584 */
extern unsigned long cl4_class_handle(unsigned long a);  /* FUN_000ec8f8 */
extern unsigned long cl4_binding_register(unsigned long *desc); /* FUN_0004b520 */
extern void cl4_binding_release(unsigned long b);        /* FUN_0004b664 */
extern unsigned long cl4_obj_lookup1(unsigned long h, unsigned long *stack); /* FUN_0002887c */
extern unsigned long cl4_obj_lookup2(unsigned long h, unsigned long a, unsigned long b, unsigned long c); /* FUN_00028b14 */
extern unsigned long cl4_obj_validate(unsigned long obj, unsigned long cptr); /* FUN_00028aa4 */
extern void cl4_op_validate(unsigned long param, unsigned long cap); /* FUN_000a0278 */
extern void cl4_endpoint_bind(unsigned long kind, unsigned long ep, unsigned long param); /* FUN_00075fb4 */
extern void cl4_endpoint_unmap(unsigned long param);     /* FUN_00093a88 */
extern void cl4_endpoint_init_report(unsigned long a, unsigned long b, const char *file,
                                     unsigned long line, unsigned long kind,
                                     const char *fmt, unsigned long fl, unsigned long k,
                                     unsigned long code, unsigned long ep, unsigned long param); /* FUN_000fb1ac */
extern void cl4_slot_put(unsigned long obj);             /* FUN_0036a25d4 */
extern void cl4_preinit(void);                           /* FUN_0002f94c */
extern unsigned long cl4_fatal_entry(unsigned long a);   /* FUN_00027724 */
extern void cl4_error_report(unsigned long a, unsigned long b, unsigned long c, unsigned long d); /* FUN_000359a0 */
extern unsigned long cl4_op_dispatch1(unsigned long a);  /* FUN_0008644c */
extern unsigned long cl4_op_dispatch2(unsigned long a);  /* FUN_00077148 */
extern void cl4_op_dispatch3(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e); /* FUN_0008e958 */

/* ---- Globals (from Ghidra) ---- */
extern char *cl4_ctx;                                    /* unaff_x20 self/context */
extern unsigned char cl4_obf_buffer[];                   /* DAT_00657778; data DAT_00657798 */
extern unsigned long cl4_obf_cursor[2];                  /* _DAT_004c08a0/_004c08a8 */
extern unsigned long cl4_notify_idx;                     /* DAT_00657788 */
extern unsigned long cl4_notify_cap;                     /* DAT_00657790 */
extern unsigned char cl4_class_anchor[];                 /* DAT_0064c038 */
extern unsigned char cl4_vtable_anchor[];                /* DAT_004c1020 */
extern unsigned long cl4_binding_handle;                 /* DAT_004bb180 */
extern unsigned char cl4_slot_ref_tag[];                 /* DAT_0007bf58 */

/* ---- In-slice forward declarations ---- */
unsigned long cl4_prng_next(void);                       /* FUN_0008ec20 */
void cl4_obf_fill(unsigned long, long, unsigned long);   /* FUN_0008ed28 */
void cl4_dispatch_guard(unsigned long, long, unsigned long, long); /* FUN_0008efe0 */
unsigned char *cl4_obf_fill2(long);                      /* FUN_0008f034 */
void cl4_obf_cursor_adjust(long);                        /* FUN_0008f7c8 */
unsigned long cl4_slot_dispatch(unsigned long, unsigned long);   /* FUN_0008f840 */
unsigned long cl4_slot_dispatch2(unsigned long, unsigned long);  /* FUN_0008f8a8 */
unsigned long cl4_slot_dispatch3(unsigned long);         /* FUN_0008f910 */
unsigned long cl4_obf_commit(unsigned long, unsigned long, unsigned long, unsigned long,
                             unsigned long, unsigned long);  /* FUN_0008f9c4 */
unsigned long cl4_obf_final(void);                       /* FUN_0008f9dc */
void cl4_obf_release(long *, long, long, void (*)(unsigned long, long)); /* FUN_0008f9f4 */
void cl4_splice(unsigned long, long, long, unsigned long, long, long, unsigned long); /* FUN_0008fc24 */
void cl4_splice_move(long, long, long);                  /* FUN_0008fde4 */
unsigned long cl4_obf_copy(long, long, unsigned long, unsigned long, long); /* FUN_0008fe7c */
unsigned char *cl4_obf_resolve(long);                    /* FUN_0008fef4 */
void cl4_branch_guard(void);                             /* FUN_000900e4 */
void cl4_slot_40_set(unsigned long, unsigned long, unsigned long); /* FUN_00090238 */
void cl4_bitmap_scan(unsigned long, long, void (*)(unsigned long, unsigned long)); /* FUN_00091314 */
void cl4_ep_launcher_init(unsigned long, unsigned long, unsigned short, unsigned long); /* FUN_00091550 */

/* ------------------------------------------------------------------ *
 * Obfuscation layer.
 * ------------------------------------------------------------------ */

/* cl4_branch_guard == FUN_000900e4 @ 0x900e4: opaque branch guard that
 * locks the context sub-object field at +0x20. */
void cl4_branch_guard(void)
{
    cl4_field_lock((unsigned long *)((char *)cl4_ctx + 0x20),
                   (unsigned long *)8, 0x21, 0);
}

/* SoftwareBreakpoint(1, addr) — unrecoverable assertion trap. */
void cl4_trap(int a, unsigned long addr) __attribute__((noreturn));
void cl4_trap(int a, unsigned long addr) { __builtin_trap(); }

/* FUN_0008ec20 @ 0x0008ec20   (est. cl4_prng_next)
 * Ghidra: undefined8 FUN_0008ec20(void)
 * Advances the obfuscation PRNG (two-word xorshift-style LFSR in the module
 * context at +0x10/+0x18) and returns a derived 64-bit word; the low byte
 * is consumed by callers to fill the deobfuscation buffer. Two opaque
 * predicates never fire; a stack canary guards the frame.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x8ed24) = noreturn canary trap. */
unsigned long cl4_prng_next(void)
{
    unsigned long frame[3];
    unsigned long local, mix, canary = CANARY;

    cl4_buf_frame_init((long *)((char *)cl4_ctx + 0x20), &frame[0]);
    if (OBF_PRED()) {
        unsigned long frame2[3];
        unsigned long s0 = *(unsigned long *)((char *)cl4_ctx + 0x10);
        local = *(unsigned long *)((char *)cl4_ctx + 0x18) + s0;
        mix   = *(unsigned long *)((char *)cl4_ctx + 0x18) ^ s0;
        *(unsigned long *)((char *)cl4_ctx + 0x10) =
            ROR64(s0, 9) ^ (mix << 14) ^ mix;
        *(unsigned long *)((char *)cl4_ctx + 0x18) = ROR64(mix, 28);
        cl4_branch_guard();
        cl4_buf_frame_fill(&local, &frame2[0]);
        cl4_buf_frame_teardown(&frame2[0]);
    }
    cl4_branch_guard();
    if (OBF_PRED()) {
        cl4_buf_frame_teardown(&frame[0]);
        cl4_trap(1, 0x8ed24);
    }
    unsigned long result = cl4_result_fetch();
    if (((unsigned)result & 0xff00) == 0x100) {
        result = cl4_result_advance(*(long *)(*(long *)((char *)cl4_ctx + 0x20) + 0x10) - 1);
    }
    cl4_buf_frame_teardown(&frame[0]);
    if (canary != CANARY) cl4_stack_canary_fail();
    return result;
}

/* FUN_0008ed28 @ 0x0008ed28   (est. cl4_obf_fill)
 * Ghidra: void FUN_0008ed28(undefined8 param_1, long param_2, undefined8 param_3)
 * Obfuscated fill of the deobfuscation buffer (DAT_00657798). Iterates
 * `count` times (count read from the object at *(param_2-8), field +0x48),
 * obtaining one byte per step from the PRNG and writing it into the buffer
 * at the bit-reversed cursor position while carrying the cursor across the
 * two-word global pair. The opaque branches and the final indirect call
 * (Ghidra SUB_911a421090000010) are obfuscation noise.
 * Confidence: low
 * Notes: SoftwareBreakpoint traps mark borrow/overflow assertion checks. */
void cl4_obf_fill(unsigned long param_1, long param_2, unsigned long param_3)
{
    unsigned long carry = cl4_obf_cursor[0];
    unsigned long carryhi = cl4_obf_cursor[1];
    long count = *(long *)(*(long *)(param_2 - 8) + 0x48);
    long sa1 = param_3, sa0 = param_1, sa2 = param_2;
    unsigned char byte;
    int cond;

    if (0 < count) {
        long base = 0;
        unsigned long bitfield = 1;
        long pos, tmp, wide;
        do {
            byte = (unsigned char)cl4_prng_next();
            if (((bitfield & 1) == 0) ||
                (cond = cl4_buf_cond((unsigned long)cl4_obf_buffer), cond == 0)) {
                if (SBORROW8(bitfield >> 1, base)) cl4_trap(1, 0x8efd0);
                cl4_obf_cursor_adjust((bitfield >> 1) - base);
                base = carry;
                bitfield = carryhi;
            }
            unsigned long q0 = bitfield >> 1;
            pos = q0 - base;
            if (SBORROW8(q0, base)) cl4_trap(1, 0x8efc4);
            wide = pos;
            if ((bitfield & 1) != 0) {
                unsigned long k = cl4_buf_key(0);
                unsigned long acq = cl4_buf_acquire((unsigned long)cl4_obf_buffer);
                long obj = cl4_buf_resolve(acq, k);
                if (obj == 0) { cl4_buf_release((unsigned long)cl4_obf_buffer); obj = cl4_buf_resolve_fallback(); }
                long objsz = *(long *)(obj + 0x10);
                if ((long)&cl4_obf_buffer[0x20] + pos + base == obj + objsz + 0x20) {
                    unsigned long sz = *(unsigned long *)(obj + 0x18);
                    cl4_buf_release(0);
                    tmp = (sz >> 1) - objsz;
                    wide = pos + tmp;
                    if (SCARRY8(pos, tmp)) cl4_trap(1, 0x8efe0);
                } else {
                    cl4_buf_release(0);
                }
            }
            long next = pos + 1;
            tmp = pos;
            if (wide < next) {
                cl4_obf_cursor_adjust(pos);
                q0 = carryhi >> 1;
                tmp = q0 - carry;
                base = carry;
                bitfield = carryhi;
                if (SBORROW8(q0, carry)) cl4_trap(1, 0x8ef28);
            }
            bool borrow = false;
            wide = next - tmp;
            if (SBORROW8(next, tmp)) cl4_trap(1, 0x8efc8);
            if (wide != 0) {
                unsigned long k = cl4_buf_key(0);
                unsigned long acq = cl4_buf_acquire((unsigned long)cl4_obf_buffer);
                long obj = cl4_buf_resolve(acq, k);
                if (obj == 0) { cl4_buf_release((unsigned long)cl4_obf_buffer); obj = cl4_buf_resolve_fallback(); }
                if (SCARRY8(*(long *)(obj + 0x10), wide)) cl4_trap(1, 0x8efd4);
                *(long *)(obj + 0x10) += wide;
                cl4_buf_release(0);
                tmp = q0 + wide;
                if (SCARRY8(q0, wide)) cl4_trap(1, 0x8efd8);
                if (tmp < 0) cl4_trap(1, 0x8efdc);
                bitfield = bitfield & 1 | tmp * 2;
                borrow = SBORROW8(tmp, base);
                tmp = tmp - base;
                carryhi = bitfield;
            }
            *(unsigned char *)((long)&cl4_obf_buffer[0x20] + pos + base) = byte;
            if (borrow) cl4_trap(1, 0x8efcc);
            param_2 = sa2;
            param_1 = sa0;
        } while (tmp < count);
    }
    ((void (*)(unsigned long))0x911a421090000010ull)(param_1);
    unsigned long frame[2];
    frame[0] = param_2;
    cl4_defer_cleanup((void *)cl4_obf_done_1, &frame[0], (unsigned long)cl4_obf_buffer);
    cl4_buf_release((unsigned long)cl4_obf_buffer);
}

/* FUN_0008efe0 @ 0x0008efe0   (est. cl4_dispatch_guard)
 * Ghidra: void FUN_0008efe0(undefined8 param_1, long param_2, undefined8 param_3, long param_4)
 * If param_2 is nonzero, invoke the vtable method at +0x10 of the object at
 * *(param_4-8) with (param_1, param_2); otherwise trap.
 * Confidence: high
 * Notes: SoftwareBreakpoint(1,0x8f034) noreturn on null param_2. */
void cl4_dispatch_guard(unsigned long p1, long p2, unsigned long p3, long p4)
{
    if (p2 != 0) {
        ((void (*)(unsigned long, long))(*(unsigned long *)(*(long *)(p4 - 8) + 0x10)))(p1, p2);
        return;
    }
    cl4_trap(1, 0x8f034);
}

/* FUN_0008f034 @ 0x0008f034   (est. cl4_obf_fill2)
 * Ghidra: undefined * FUN_0008f034(long param_1)
 * Sibling of cl4_obf_fill filling `count` PRNG bytes into the deobfuscation
 * buffer; returns the buffer base (DAT_00657778).
 * Confidence: low
 * Notes: SoftwareBreakpoint traps mark assertion checks. */
unsigned char *cl4_obf_fill2(long count)
{
    unsigned long carry = cl4_obf_cursor[0];
    unsigned long carryhi = cl4_obf_cursor[1];
    unsigned char byte;
    int cond;

    if (0 < count) {
        long base = 0;
        unsigned long bitfield = 1;
        long pos, tmp, wide;
        do {
            byte = (unsigned char)cl4_prng_next();
            if (((bitfield & 1) == 0) ||
                (cond = cl4_buf_cond((unsigned long)cl4_obf_buffer), cond == 0)) {
                if (SBORROW8(bitfield >> 1, base)) cl4_trap(1, 0x8f254);
                cl4_obf_cursor_adjust((bitfield >> 1) - base);
                base = carry;
                bitfield = carryhi;
            }
            unsigned long q0 = bitfield >> 1;
            pos = q0 - base;
            if (SBORROW8(q0, base)) cl4_trap(1, 0x8f248);
            wide = pos;
            if ((bitfield & 1) != 0) {
                unsigned long k = cl4_buf_key(0);
                unsigned long acq = cl4_buf_acquire((unsigned long)cl4_obf_buffer);
                long obj = cl4_buf_resolve(acq, k);
                if (obj == 0) { cl4_buf_release((unsigned long)cl4_obf_buffer); obj = cl4_buf_resolve_fallback(); }
                long objsz = *(long *)(obj + 0x10);
                if ((long)&cl4_obf_buffer[0x20] + pos + base == obj + objsz + 0x20) {
                    unsigned long sz = *(unsigned long *)(obj + 0x18);
                    cl4_buf_release(0);
                    tmp = (sz >> 1) - objsz;
                    wide = pos + tmp;
                    if (SCARRY8(pos, tmp)) cl4_trap(1, 0x8f264);
                } else {
                    cl4_buf_release(0);
                }
            }
            long next = pos + 1;
            tmp = pos;
            if (wide < next) {
                cl4_obf_cursor_adjust(pos);
                q0 = carryhi >> 1;
                tmp = q0 - carry;
                base = carry;
                bitfield = carryhi;
                if (SBORROW8(q0, carry)) cl4_trap(1, 0x8f210);
            }
            bool borrow = false;
            wide = next - tmp;
            if (SBORROW8(next, tmp)) cl4_trap(1, 0x8f24c);
            if (wide != 0) {
                unsigned long k = cl4_buf_key(0);
                unsigned long acq = cl4_buf_acquire((unsigned long)cl4_obf_buffer);
                long obj = cl4_buf_resolve(acq, k);
                if (obj == 0) { cl4_buf_release((unsigned long)cl4_obf_buffer); obj = cl4_buf_resolve_fallback(); }
                if (SCARRY8(*(long *)(obj + 0x10), wide)) cl4_trap(1, 0x8f258);
                *(long *)(obj + 0x10) += wide;
                cl4_buf_release(0);
                tmp = q0 + wide;
                if (SCARRY8(q0, wide)) cl4_trap(1, 0x8f25c);
                if (tmp < 0) cl4_trap(1, 0x8f260);
                bitfield = bitfield & 1 | tmp * 2;
                borrow = SBORROW8(tmp, base);
                tmp = tmp - base;
                carryhi = bitfield;
            }
            *(unsigned char *)((long)&cl4_obf_buffer[0x20] + pos + base) = byte;
            if (borrow) cl4_trap(1, 0x8f250);
        } while (tmp < count);
    }
    return &cl4_obf_buffer[0];
}

/* ------------------------------------------------------------------ *
 * Tagged-list traversal helpers.
 * ------------------------------------------------------------------ */
/* FUN_0008f6c0 @ 0x0008f6c0   (est. cl4_obj_next_word)
 * Tagged list traversal: if low tag bit clear, advance node by the int at
 * +0xc; else follow the pointer at +0x18. Confidence: high */
long cl4_obj_next_word(unsigned long node)
{
    if ((node & 1) == 0)
        return (long)(node + 0xc) + (long)*(int *)(node + 0xc);
    return *(long *)((node & 0xfffffffffffffffeull) + 0x18);
}
/* FUN_0008f6f4 @ 0x0008f6f4   (est. cl4_obj_next_off8) — advance by int at +8,
 * indirect follows pointer at +0x10. Confidence: high */
long cl4_obj_next_off8(unsigned long node)
{
    if ((node & 1) == 0)
        return (long)(node + 8) + (long)*(int *)(node + 8);
    return *(long *)((node & 0xfffffffffffffffeull) + 0x10);
}
/* FUN_0008f728 @ 0x0008f728   (est. cl4_obj_next_off4) — indirect: load
 * pointer at +0, advance by int at +4. Confidence: high */
long cl4_obj_next_off4(unsigned long node)
{
    if ((node & 1) != 0)
        node = *(unsigned long *)(node & 0xfffffffffffffffeull);
    return (long)(node + 4) + (long)*(int *)(node + 4);
}
/* FUN_0008f758 @ 0x0008f758   (est. cl4_obj_next_offc) — indirect: load
 * pointer at +0, advance by int at +0xc. Confidence: high */
long cl4_obj_next_offc(unsigned long node)
{
    if ((node & 1) != 0)
        node = *(unsigned long *)(node & 0xfffffffffffffffeull);
    return (long)(node + 0xc) + (long)*(int *)(node + 0xc);
}
/* FUN_0008f970 @ 0x0008f970   (est. cl4_obj_next_off8b) — indirect: load
 * pointer at +0, advance by int at +8. Confidence: high */
long cl4_obj_next_off8b(unsigned long node)
{
    if ((node & 1) != 0)
        node = *(unsigned long *)(node & 0xfffffffffffffffeull);
    return (long)(node + 8) + (long)*(int *)(node + 8);
}

/* ------------------------------------------------------------------ *
 * Simple wrappers / field accessors.
 * ------------------------------------------------------------------ */
/* FUN_0008f264 / FUN_0008f268 @ 0x8f264/0x8f268 (est. cl4_release_ctx_20) —
 * release the context field at +0x20. Confidence: high */
void cl4_release_ctx_20a(void) { cl4_buf_release(*(unsigned long *)((char *)cl4_ctx + 0x20)); }
void cl4_release_ctx_20b(void) { cl4_buf_release(*(unsigned long *)((char *)cl4_ctx + 0x20)); }
/* FUN_0008f284 / FUN_0008f288 @ 0x8f284/0x8f288 (est. cl4_release_ctx_20_fast) —
 * release +0x20 then fast-teardown. Confidence: high */
void cl4_release_ctx_20_fast_a(void)
{ cl4_buf_release(*(unsigned long *)((char *)cl4_ctx + 0x20)); cl4_buf_release_fast(); }
void cl4_release_ctx_20_fast_b(void)
{ cl4_buf_release(*(unsigned long *)((char *)cl4_ctx + 0x20)); cl4_buf_release_fast(); }
/* FUN_0008f2b0 / FUN_0008f2ec @ 0x8f2b0/0x8f2ec (est. cl4_vcall_a8 / cl4_vcall_b0) —
 * indirect vtable calls via *cl4_ctx at +0xa8 / +0xb0. Confidence: high */
void cl4_vcall_a8(void)
{ ((void (*)(void))(*(unsigned long *)(*(unsigned long *)*((unsigned long *)cl4_ctx) + 0xa8)))(); }
void cl4_vcall_b0(void)
{ ((void (*)(void))(*(unsigned long *)(*(unsigned long *)*((unsigned long *)cl4_ctx) + 0xb0)))(); }
/* FUN_0008f57c / FUN_0008f5b8 @ 0x8f57c/0x8f5b8 (est. cl4_vcall_38 / cl4_vcall_40) —
 * indirect vtable calls via *cl4_ctx at +0x38 / +0x40. Confidence: high */
void cl4_vcall_38(void)
{ ((void (*)(void))(*(unsigned long *)(*(unsigned long *)*((unsigned long *)cl4_ctx) + 0x38)))(); }
void cl4_vcall_40(void)
{ ((void (*)(void))(*(unsigned long *)(*(unsigned long *)*((unsigned long *)cl4_ctx) + 0x40)))(); }

/* FUN_0008f5f4 @ 0x0008f5f4   (est. cl4_cond_check)
 * Ghidra: undefined8 FUN_0008f5f4(void)
 * If the context flag byte at +0x18 is clear return 0; otherwise run the
 * buffer condition check (FUN_003a261c) on *cl4_ctx. Confidence: high */
unsigned long cl4_cond_check(void)
{
    unsigned long *self = (unsigned long *)cl4_ctx;
    if ((*(unsigned char *)(self + 3) & 1) == 0)
        return 0;
    unsigned long v = *self;
    unsigned long r = cl4_buf_cond(v);
    *self = v;
    return r;
}

/* FUN_0008f630 @ 0x0008f630   (est. cl4_obj_insert)
 * Ghidra: void FUN_0008f630(undefined8 param_1, undefined8 param_2, long param_3, ulong param_4)
 * Insert `param_3 .. param_4/2` words into the object list: allocate
 * `param_4/2 - param_3` zeroed words, splice them at param_3, then realloc.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x8f6c0) on bad size. */
void cl4_obj_insert(unsigned long p1, unsigned long p2, long p3, unsigned long p4)
{
    unsigned long half = p4 >> 1;
    if (SBORROW8(half, p3)) cl4_trap(1, 0x8f6bc);
    long block = cl4_zalloc(half - p3, half - p3);
    if (p3 <= (long)half) {
        cl4_obf_copy(p3, half, (unsigned long)(block + 0x20), p1, p3);
        cl4_realloc((unsigned long)block, (unsigned long)p3);
        return;
    }
    cl4_trap(1, 0x8f6c0);
}

/* FUN_0008f788 / FUN_0008f78c @ 0x8f788/0x8f78c (est. cl4_op_dispatch_pair_1/2) —
 * dispatch op via cl4_op_dispatch3 with ctx +0x20/+0x10/+0x18. Conf: high */
void cl4_op_dispatch_pair_1(unsigned long a, unsigned long b)
{
    cl4_op_dispatch3(a, *(unsigned long *)((char *)cl4_ctx + 0x20),
                     *(unsigned long *)((char *)cl4_ctx + 0x10),
                     *(unsigned long *)((char *)cl4_ctx + 0x18), b);
}
void cl4_op_dispatch_pair_2(unsigned long a, unsigned long b)
{
    cl4_op_dispatch3(a, *(unsigned long *)((char *)cl4_ctx + 0x20),
                     *(unsigned long *)((char *)cl4_ctx + 0x10),
                     *(unsigned long *)((char *)cl4_ctx + 0x18), b);
}

/* FUN_0008f7ac / FUN_0008f7b0 @ 0x8f7ac/0x8f7b0 (est. cl4_obf_done_1/2) —
 * obfuscation-fill completion routed through cl4_dispatch_guard. Conf: med */
void cl4_obf_done_1(unsigned long a, unsigned long b)
{
    cl4_dispatch_guard(a, b, *(unsigned long *)((char *)cl4_ctx + 0x10),
                       *(unsigned long *)((char *)cl4_ctx + 0x18));
}
void cl4_obf_done_2(unsigned long a, unsigned long b)
{
    cl4_dispatch_guard(a, b, *(unsigned long *)((char *)cl4_ctx + 0x10),
                       *(unsigned long *)((char *)cl4_ctx + 0x18));
}

/* FUN_0008f7c8 @ 0x0008f7c8   (est. cl4_obf_cursor_adjust)
 * Ghidra: void FUN_0008f7c8(long param_1)
 * Advance the obfuscation-buffer cursor by `n`: commit via cl4_obf_commit,
 * then finalize via cl4_obf_final/cl4_obf_release and drop both buffer
 * references. Confidence: low */
void cl4_obf_cursor_adjust(long n)
{
    unsigned long *buf = (unsigned long *)cl4_obf_buffer;
    unsigned long r = cl4_obf_commit(n, n + 1, buf[0], buf[1], buf[2], buf[3]);
    unsigned long frame[2];
    frame[0] = r;
    /* leftover x0/x1 from cl4_obf_final are passed as the release callback
     * pair (obfuscation noise). */
    unsigned long pair0 = cl4_obf_final();
    unsigned long pair1 = 0;
    cl4_obf_release((long *)&frame[0], n, 0, (void (*)(unsigned long, long))pair0);
    cl4_buf_release(pair1);
    cl4_buf_release(r);
}

/* FUN_0008f840 @ 0x0008f840   (est. cl4_slot_dispatch)
 * Ghidra: undefined8 FUN_0008f840(undefined8 param_1, undefined8 param_2)
 * Dispatch an operation through the class vtable (+0x10) looked up for the
 * class/vtable anchor pair; returns param_2.
 * Confidence: medium */
unsigned long cl4_slot_dispatch(unsigned long p1, unsigned long p2)
{
    long cls = cl4_class_lookup((unsigned long *)&cl4_class_anchor[0], (unsigned long *)&cl4_vtable_anchor[0]);
    ((void (*)(unsigned long, unsigned long, long))(*(unsigned long *)(*(long *)(cls - 8) + 0x10)))(p2, p1, cls);
    return p2;
}
/* FUN_0008f8a8 @ 0x0008f8a8   (est. cl4_slot_dispatch2) — vtable +0x18. */
unsigned long cl4_slot_dispatch2(unsigned long p1, unsigned long p2)
{
    long cls = cl4_class_lookup((unsigned long *)&cl4_class_anchor[0], (unsigned long *)&cl4_vtable_anchor[0]);
    ((void (*)(unsigned long, unsigned long, long))(*(unsigned long *)(*(long *)(cls - 8) + 0x18)))(p2, p1, cls);
    return p2;
}
/* FUN_0008f910 @ 0x0008f910   (est. cl4_slot_dispatch3) — vtable +8, 1 arg. */
unsigned long cl4_slot_dispatch3(unsigned long p1)
{
    long cls = cl4_class_lookup((unsigned long *)&cl4_class_anchor[0], (unsigned long *)&cl4_vtable_anchor[0]);
    ((void (*)(unsigned long, long))(*(unsigned long *)(*(long *)(cls - 8) + 8)))(p1, cls);
    return p1;
}

/* FUN_0008f9a0 @ 0x0008f9a0   (est. cl4_register_cleanup_x)
 * Registers the cleanup handler at 0x64f5d0. Confidence: high */
void cl4_register_cleanup_x(void) { cl4_register_cleanup((void *)0x64f5d0); }

/* FUN_0008f9c4 @ 0x0008f9c4   (est. cl4_obf_commit)
 * Ghidra: void FUN_0008f9c4(p1..p6)
 * Forwards to cl4_splice with param_2 duplicated. Confidence: high */
unsigned long cl4_obf_commit(unsigned long p1, unsigned long p2, unsigned long p3,
                             unsigned long p4, unsigned long p5, unsigned long p6)
{
    cl4_splice(p1, p2, p2, p3, p4, p5, p6);
    return 0;
}

/* FUN_0008f9dc @ 0x0008f9dc   (est. cl4_obf_final)
 * Registers the cleanup handler FUN_0001a1c8. Confidence: high */
void cl4_obf_cb_1a1c8(void);
unsigned long cl4_obf_final(void)
{
    cl4_register_cleanup((void *)cl4_obf_cb_1a1c8);
    return 0;
}
/* out-of-slice callback target for cl4_obf_final (FUN_0001a1c8). */
void cl4_obf_cb_1a1c8(void) { }

/* thunk_FUN_000720a8 — memmove (dst, len, src). */
extern void cl4_memmove(unsigned long dst, long len, unsigned long src);

/* FUN_0008fe7c @ 0x0008fe7c   (est. cl4_obf_copy)
 * Ghidra: ulong FUN_0008fe7c(long param_1, long param_2, ulong param_3, undefined8 param_4, long param_5)
 * Release the buffer ref, then validate the copy range [p1,p2) against the
 * target p3..; if the ranges do not overlap, allocate and return the end
 * offset; otherwise trap (overlap is fatal).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x8fef4/0x8fef0) on overlap. */
unsigned long cl4_obf_copy(long p1, long p2, unsigned long p3, unsigned long p4, long p5)
{
    cl4_buf_release(p4);
    long len = p2 - p1;
    if (SBORROW8(p2, p1)) cl4_trap(1, 0x8feec);
    if (-1 < len) {
        if (p3 + len <= (unsigned long)(p5 + p1) ||
            (unsigned long)(p5 + p1 + len) <= p3) {
            cl4_alloc_buf(p3);
            return p3 + len;
        }
        cl4_trap(1, 0x8fef4);
    }
    cl4_trap(1, 0x8fef0);
}

/* FUN_0008fde4 @ 0x0008fde4   (est. cl4_splice_move)
 * Ghidra: void FUN_0008fde4(long param_1, long param_2, long param_3)
 * Move a region within the buffer: shift [param_1,param_2) by (param_3 -
 * length) and grow the buffer by the delta. Traps if param_3 < length or
 * the tail is invalid.
 * Confidence: low */
void cl4_splice_move(long p1, long p2, long p3)
{
    long len = p2 - p1;
    if (SBORROW8(p2, p1)) cl4_trap(1, 0x8fe68);
    if (len < 0) cl4_trap(1, 0x8fe6c);
    long delta = p3 - len;
    if (SBORROW8(p3, len)) cl4_trap(1, 0x8fe70);
    if (delta != 0) {
        unsigned long *buf = (unsigned long *)cl4_obf_buffer;
        if (SBORROW8(*(long *)(buf + 2), p2)) cl4_trap(1, 0x8fe74);
        cl4_memmove((unsigned long)((char *)buf + 0x20 + p2),
                    *(long *)(buf + 2) - p2,
                    (unsigned long)((char *)buf + 0x20 + p1 + p3));
        if (SCARRY8(*(long *)(buf + 2), delta)) cl4_trap(1, 0x8fe78);
        *(long *)(buf + 2) += delta;
    }
    if (p3 < 1)
        return;
    cl4_trap(1, 0x8fe7c);
}

/* FUN_0008fef4 @ 0x0008fef4   (est. cl4_obf_resolve)
 * Ghidra: undefined * FUN_0008fef4(long param_1)
 * Resolve the backing object for the buffer such that `param_1` bytes are
 * available; if the candidate region is empty, shrink (via cl4_splice_move)
 * and return the buffer base; otherwise return NULL. Heavy opaque
 * predicate / cursor math.
 * Confidence: low */
unsigned char *cl4_obf_resolve(long p1)
{
    unsigned long *buf = (unsigned long *)cl4_obf_buffer;
    if (cl4_buf_cond(buf[0]) != 0) {
        long l1 = buf[2];
        unsigned long half = (unsigned long)buf[3] >> 1;
        long l3 = half - l1;
        if (SBORROW8(half, l1)) cl4_trap(1, 0x90038);
        unsigned long u2 = buf[0];
        long l10 = buf[1];
        long l9 = l3;
        if ((buf[3] & 1) != 0) {
            unsigned long k = cl4_buf_key(0);
            unsigned long acq = cl4_buf_acquire(u2);
            unsigned char *obj = (unsigned char *)cl4_buf_resolve(acq, k);
            if (obj == 0) { cl4_buf_release(u2); obj = &cl4_obf_buffer[0]; }
            long objsz = *(long *)(obj + 0x10);
            if ((unsigned char *)(l10 + l1 + l3) == obj + objsz + 0x20) {
                unsigned long sz = *(unsigned long *)(obj + 0x18);
                cl4_buf_release(0);
                long t = (sz >> 1) - objsz;
                l9 = l3 + t;
                if (SCARRY8(l3, t)) cl4_trap(1, 0x90050);
            } else {
                cl4_buf_release(0);
            }
        }
        if (p1 <= l9) {
            unsigned long k = cl4_buf_key(0);
            unsigned long acq = cl4_buf_acquire(u2);
            unsigned char *obj = (unsigned char *)cl4_buf_resolve(acq, k);
            if (obj == 0) { cl4_buf_release(u2); obj = &cl4_obf_buffer[0]; }
            long free = ((l10 + l1) - (long)obj) - 0x20;
            long avail = l3 + free;
            if (!SCARRY8(l3, free)) {
                if (*(long *)(obj + 0x10) <= avail)
                    return obj;
                cl4_splice_move(avail, *(long *)(obj + 0x10), 0);
                return obj;
            }
            cl4_trap(1, 0x9003c);
        }
    }
    return 0;
}

/* FUN_0008fc24 @ 0x0008fc24   (est. cl4_splice)
 * Ghidra: void FUN_0008fc24(undefined8 param_1, long param_2, long param_3,
 *   undefined8 param_4, long param_5, long param_6, ulong param_7)
 * Compute the required size for a splice into the deobfuscation buffer and
 * allocate that many words. Contains the standard opaque-predicate cursor
 * bookkeeping (resolve backing object, fold the free/size fields).
 * Confidence: low
 * Notes: SoftwareBreakpoint traps mark assert checks. */
void cl4_splice(unsigned long p1, long p2, long p3, unsigned long p4,
                long p5, long p6, unsigned long p7)
{
    long l9 = (p7 >> 1) - p6;
    if (SBORROW8(p7 >> 1, p6)) cl4_trap(1, 0x8fdc8);
    if ((p7 & 1) == 0) {
        if (p2 <= l9) goto done;
    } else {
        unsigned long k = cl4_buf_key(0);
        unsigned long acq = cl4_buf_acquire(p4);
        unsigned char *obj = (unsigned char *)cl4_buf_resolve(acq, k);
        if (obj == 0) { cl4_buf_release(p4); obj = &cl4_obf_buffer[0]; }
        long objsz = *(long *)(obj + 0x10);
        unsigned char *cand = (unsigned char *)(p5 + p6 + l9);
        long l8;
        if (cand == obj + objsz + 0x20) {
            unsigned long sz = *(unsigned long *)(obj + 0x18);
            cl4_buf_release(0);
            long t = (sz >> 1) - objsz;
            l8 = l9 + t;
            if (SCARRY8(l9, t)) cl4_trap(1, 0x8fddc);
        } else {
            cl4_buf_release(0);
            l8 = l9;
        }
        acq = cl4_buf_acquire(p4);
        obj = (unsigned char *)cl4_buf_resolve(acq, k);
        if (p2 <= l8) {
            if (obj == 0) { cl4_buf_release(p4); obj = &cl4_obf_buffer[0]; }
            objsz = *(long *)(obj + 0x10);
            if (cand == obj + objsz + 0x20) {
                unsigned long sz = *(unsigned long *)(obj + 0x18);
                cl4_buf_release(0);
                long t = (sz >> 1) - objsz;
                if (SCARRY8(l9, t)) { l9 = l9 + t; cl4_trap(1, 0x8fde4); }
                l9 = l9 + t;
            } else {
                cl4_buf_release(0);
            }
            goto done;
        }
        if (obj == 0) { cl4_buf_release(p4); obj = &cl4_obf_buffer[0]; }
        objsz = *(long *)(obj + 0x10);
        if (cand == obj + objsz + 0x20) {
            unsigned long sz = *(unsigned long *)(obj + 0x18);
            cl4_buf_release(0);
            long t = (sz >> 1) - objsz;
            if (SCARRY8(l9, t)) { l9 = l9 + t; cl4_trap(1, 0x8fde0); }
            l9 = l9 + t;
        } else {
            cl4_buf_release(0);
        }
    }
    if (l9 + 0x4000000000000000 < 0) cl4_trap(1, 0x8fdd8);
    l9 = l9 << 1;
done:
    if (l9 <= p3) l9 = p3;
    cl4_zalloc(p1, l9);
}

/* FUN_0008f9f4 @ 0x0008f9f4   (est. cl4_obf_release)
 * Ghidra: void FUN_0008f9f4(long *param_1, long param_2, long param_3, code *param_4)
 * Commit a filled run in the deobfuscation buffer: resolve the backing
 * object, move/relocate the run via memmove or a fresh copy, invoke the
 * release callback, and realloc the buffer to the new cursor. Heavy opaque
 * bookkeeping.
 * Confidence: low */
void cl4_obf_release(long *p1, long p2, long p3, void (*cb)(unsigned long, long))
{
    unsigned long *buf = (unsigned long *)cl4_obf_buffer;
    unsigned long half = *(unsigned long *)(buf[1] + 8) >> 1;
    long l3 = half - *(long *)buf[1];
    if (SBORROW8(half, *(long *)buf[1])) cl4_trap(1, 0x8fbf8);
    long l12 = *p1;
    long l4 = *(long *)(l12 + 0x10) - p2;
    if (SBORROW8(*(long *)(l12 + 0x10), p2)) cl4_trap(1, 0x8fbfc);
    long l5 = l4 - p3;
    if (SBORROW8(l4, p3)) cl4_trap(1, 0x8fc00);
    if (SBORROW8(l3, p2)) cl4_trap(1, 0x8fc04);
    l4 = (l3 - p2) - l5;
    if (SBORROW8(l3 - p2, l5)) cl4_trap(1, 0x8fc08);
    unsigned long l1 = l12 + 0x20;
    unsigned long l8 = l1 + p2;
    unsigned long (*fn)(unsigned long, long) = (unsigned long (*)(unsigned long, long))cb;
    long l7 = (long)cl4_obf_resolve(l3);
    void (*save_cb)(unsigned long, long) = cb;
    long l10;
    if (l7 == 0) {
        l10 = *(long *)buf[1];
        long l3b = l10 + p2;
        if (SCARRY8(l10, p2)) cl4_trap(1, 0x8fc18);
        if (l3b < l10) cl4_trap(1, 0x8fc1c);
        unsigned long vtable = *buf;
        unsigned long u11 = *(unsigned long *)(*buf + 8);
        unsigned long u9 = *(unsigned long *)(buf[1] + 8);
        cl4_ref_kind(vtable, 2);
        u11 = cl4_obf_copy(l10, l3b, l1, vtable, (long)u9);
        cb(u11, p3);
        if (SCARRY8(l3b, l4)) cl4_trap(1, 0x8fc20);
        if ((long)(u9 >> 1) < l3b + l4) cl4_trap(1, 0x8fc24);
        l8 = l8 + p3;
        cl4_obf_copy(0, 0, 0, 0, 0);
    } else {
        l10 = *(long *)buf[1];
        long l2 = *(long *)(*buf + 8) + l10;
        if (l2 - (l7 + 0x20) < 0) cl4_trap(1, 0x8fc0c);
        cl4_memmove((unsigned long)l2, p2, l1);
        if (l4 < 0) cl4_trap(1, 0x8fc10);
        cb(l8, p3);
        l8 = l8 + p3;
        cl4_memmove((unsigned long)(l2 + p2 + l4), l5, 0);
        if ((l7 + 0x20 + *(long *)(l7 + 0x10)) - (l2 + l3) < 0) cl4_trap(1, 0x8fc14);
        *(unsigned long *)(l7 + 0x10) = 0;
        cl4_buf_release((unsigned long)l7);
    }
    unsigned long u11 = *buf;
    cl4_buf_acquire((unsigned long)l12);
    cl4_buf_release(u11);
    unsigned long au13 = cl4_realloc((unsigned long)l12, (unsigned long)l10);
    *buf = au13;
    *(long *)buf[1] = l8;
    *(void (**)(unsigned long, long))(buf[1] + 8) = save_cb;
}

/* ------------------------------------------------------------------ *
 * Message refresh / send / receive.
 * ------------------------------------------------------------------ */
/* FUN_0008f334 @ 0x0008f334   (est. cl4_msg_refresh)
 * Init a frame from the class anchor, fetch the current message, then
 * dispatch the slot. Confidence: medium */
void cl4_msg_refresh(void)
{
    unsigned long frame[3];
    cl4_buf_frame_init((long *)0x6ad9a0, &frame[0]);
    cl4_msg_fetch();
    cl4_slot_dispatch(0, (unsigned long)frame);
}
/* FUN_0008f378 @ 0x0008f378   (est. cl4_msg_refresh2)
 * Message-refresh variant: branch guard, field lock, dispatch2, frame
 * teardown, dispatch3. Confidence: low */
void cl4_msg_refresh2(void)
{
    unsigned long frame[3];
    cl4_branch_guard();
    cl4_field_lock(0, 0, 0, 0);
    cl4_slot_dispatch2(0, 0);
    cl4_buf_frame_teardown(&frame[0]);
    cl4_slot_dispatch3(0);
}
/* FUN_0008f3d0 @ 0x0008f3d0   (est. cl4_msg_emit)
 * Fetch the current message and lock its buffer with kind 0x21; returns a
 * code anchor (LAB_0006f910). Confidence: low */
unsigned char *cl4_msg_emit(void)
{
    unsigned long pair[2];
    cl4_branch_guard();
    pair[0] = cl4_msg_fetch();
    cl4_field_lock((unsigned long *)pair[0], (unsigned long *)pair[1], 0x21, 0);
    return (unsigned char *)0x6f910;
}
/* FUN_0008f41c @ 0x0008f41c   (est. cl4_msg_send)
 * Init frame, dispatch slot; if a message object was produced, capture it,
 * fetch the message and invoke the send callback; else trap.
 * Confidence: low; Notes: SoftwareBreakpoint(1,0x8f4cc). */
void cl4_msg_send(unsigned long param_1)
{
    unsigned long frame[3], frame2[3], saved[2];
    cl4_buf_frame_init((long *)0x6ad9a0, &frame[0]);
    cl4_slot_dispatch(0x6ad9a0, (unsigned long)frame2);
    if (saved[0] != 0) {
        cl4_frame_capture(frame2, &saved[0]);
        unsigned long pair[2];
        pair[0] = cl4_msg_fetch();
        pair[1] = 0;
        /* indirect send callback — Ghidra `(*extraout_x9)(...)` (leftover
         * register pointer, obfuscation). */
        ((void (*)(unsigned long, unsigned long, long, unsigned long))
            ((unsigned long *)((char *)cl4_ctx + 0x10))[0])(pair[0], pair[1], saved[0], saved[1]);
        cl4_frame_restore(frame2);
        return;
    }
    cl4_trap(1, 0x8f4cc);
}
/* FUN_0008f4cc @ 0x0008f4cc   (est. cl4_msg_receive)
 * Init frame, dispatch slot, fetch result and invoke the receive callback;
 * returns the 16-byte message pair. Confidence: low
 * Notes: SoftwareBreakpoint(1,0x8f57c). */
unsigned long cl4_msg_receive(void)
{
    unsigned long frame[3], frame2[3], saved[2];
    cl4_branch_guard();
    cl4_buf_frame_init(0, 0);
    cl4_slot_dispatch(0, 0);
    if (saved[0] != 0) {
        cl4_frame_capture(frame2, &saved[0]);
        unsigned long (*cb)(void) = (unsigned long (*)(void))cl4_op_dispatch1(saved[1]);
        unsigned long pair = cb();
        cl4_frame_restore(frame2);
        return pair;
    }
    cl4_trap(1, 0x8f57c);
}

/* ------------------------------------------------------------------ *
 * Empty / fatal helpers.
 * ------------------------------------------------------------------ */
/* FUN_0009009c / 000900ac / 000900bc / 000900d0 @ 0x9009c..0x900d0
 *   (est. cl4_nop_x) — empty stubs (no-op). Confidence: high */
void cl4_nop_1(void) { }
void cl4_nop_2(void) { }
void cl4_nop_3(void) { }
void cl4_nop_4(void) { }

/* FUN_00090054 @ 0x00090054   (est. cl4_fatal_prng_swi)
 * Fatal error path for the PRNG/software-interrupt handler.
 * Confidence: high (string matched "InternalExclaveLauncher::prng_swi") */
void cl4_fatal_prng_swi(unsigned long param_1)
{
    cl4_fatal("Fatal error", 0xb, 2, 0x202928676e726363ull, 0xee0064656c696166ull,
              "InternalExclaveLauncher::prng_swi", 0x22, 2);
}

/* FUN_00090c24 / 00090d5c / 00090e94 / 00090fcc @ 0x90c24..0x90fcc
 *   (est. cl4_fatal_ep_8a/8d/90/93) — fatal error paths for endpoint slot
 *   operations with distinct tags (0x8a, 0x8d, 0x90, 0x93).
 * Confidence: high (string matched "InternalExclaveLauncher::External") */
void cl4_fatal_ep_8a(void)
{
    cl4_fatal("Fatal error", 0xb, 2, 0xd000000000000036ull, 0x80000000005c0fe0ull,
              "InternalExclaveLauncher::External", 0x39, 2, 0x8a, 0);
}
void cl4_fatal_ep_8d(void)
{
    cl4_fatal("Fatal error", 0xb, 2, 0xd000000000000036ull, 0x80000000005c0fe0ull,
              "InternalExclaveLauncher::External", 0x39, 2, 0x8d, 0);
}
void cl4_fatal_ep_90(void)
{
    cl4_fatal("Fatal error", 0xb, 2, 0xd000000000000036ull, 0x80000000005c0fe0ull,
              "InternalExclaveLauncher::External", 0x39, 2, 0x90, 0);
}
void cl4_fatal_ep_93(void)
{
    cl4_fatal("Fatal error", 0xb, 2, 0xd000000000000036ull, 0x80000000005c0fe0ull,
              "InternalExclaveLauncher::External", 0x39, 2, 0x93, 0);
}

/* ------------------------------------------------------------------ *
 * List helpers.
 * ------------------------------------------------------------------ */
/* FUN_00090190 @ 0x00090190   (est. cl4_list_dispatch)
 * Invoke the vtable method at param_1[2]+0x10 with (*param_1, param_1[1]).
 * Confidence: medium
 * Notes: indirect jump, jumptable not recovered (0x901a4). */
void cl4_list_dispatch(unsigned long *p)
{
    ((void (*)(unsigned long, unsigned long))(*(unsigned long *)(p[2] + 0x10)))(p[0], p[1]);
}

/* FUN_00090150 @ 0x00090150   (est. cl4_list_clear)
 * If the list head is non-null, dispatch its teardown; then zero the three
 * list fields at +0x00/+0x08/+0x10 of the context. Confidence: high */
void cl4_list_clear(void)
{
    unsigned long *self = (unsigned long *)cl4_ctx;
    unsigned long head = self[0];
    if (head != 0) {
        unsigned long slot[3];
        slot[2] = self[2];
        slot[1] = self[1];
        slot[0] = head;
        cl4_list_dispatch(slot);
    }
    self[0] = 0;
    self[1] = 0;
    self[2] = 0;
}

/* FUN_000900f8 @ 0x000900f8   (est. cl4_obj_insert0)
 * Insert a single element via cl4_obj_insert. Confidence: high */
void cl4_obj_insert0(void) { cl4_obj_insert(0, 0, 0, 0); }

/* FUN_000901bc / 000901c0 @ 0x901bc/0x901c0 (est. cl4_store_58_a/b) —
 * store param_1 into the object at *(self+0x10), field +0x58. Conf: high */
void cl4_store_58_a(unsigned long v)
{ cl4_slot_store((unsigned long *)(*(unsigned long *)((char *)cl4_ctx + 0x10) + 0x58), v); }
void cl4_store_58_b(unsigned long v)
{ cl4_slot_store((unsigned long *)(*(unsigned long *)((char *)cl4_ctx + 0x10) + 0x58), v); }
/* FUN_000901ec / 000901f0 @ 0x901ec/0x901f0 (est. cl4_store_18_a/b) —
 * store param_1 into the context field at +0x18. Confidence: high */
void cl4_store_18_a(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x18), v); }
void cl4_store_18_b(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x18), v); }

/* ------------------------------------------------------------------ *
 * Cap-slot accessors (get / set / reference) for each slot offset.
 * ------------------------------------------------------------------ */
/* FUN_0009020c @ 0x0009020c   (est. cl4_slot_40_get) */
unsigned long cl4_slot_40_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0x40));
    return *(unsigned long *)((char *)cl4_ctx + 0x40);
}
/* FUN_00090238 @ 0x00090238   (est. cl4_slot_40_set) — open slot +0x40 and
 * store three fields. Confidence: high */
void cl4_slot_40_set(unsigned long p1, unsigned long p2, unsigned long p3)
{
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0x40));
    *(unsigned long *)((char *)cl4_ctx + 0x40) = p1;
    *(unsigned long *)((char *)cl4_ctx + 0x48) = p2;
    *(unsigned long *)((char *)cl4_ctx + 0x50) = p3;
}
/* FUN_00090280 @ 0x00090280   (est. cl4_slot_40_ref) — reference getter. */
cl4_pair_t cl4_slot_40_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0x40));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0x40);
    return r;
}
/* FUN_00090acc @ 0x00090acc   (est. cl4_slot_90_get) */
unsigned long cl4_slot_90_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0x90));
    return *(unsigned long *)((char *)cl4_ctx + 0x90);
}
/* FUN_00090af4 @ 0x00090af4   (est. cl4_slot_90_set) */
void cl4_slot_90_set(unsigned long v)
{
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0x90));
    *(unsigned long *)((char *)cl4_ctx + 0x90) = v;
}
/* FUN_00090b28 @ 0x00090b28   (est. cl4_slot_90_ref) */
cl4_pair_t cl4_slot_90_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0x90));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0x90);
    return r;
}
/* FUN_00090b6c @ 0x00090b6c   (est. cl4_slot_a0_get) — byte-valued slot. */
unsigned long cl4_slot_a0_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xa0));
    return *(unsigned char *)((char *)cl4_ctx + 0xa0);
}
/* FUN_00090b94 @ 0x00090b94   (est. cl4_slot_a0_set) */
void cl4_slot_a0_set(unsigned long v)
{
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xa0));
    *(unsigned char *)((char *)cl4_ctx + 0xa0) = (unsigned char)v;
}
/* FUN_00090bc8 @ 0x00090bc8   (est. cl4_slot_a0_ref) */
cl4_pair_t cl4_slot_a0_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xa0));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xa0);
    return r;
}

/* Paired (value, ref) cap slots: a8/b0, b8/c0, c8/d0, d8/e0, e8/f0, f8/100.
 * get() acquires the paired reference; set(v,aux) stores both fields;
 * ref() returns the reference pair. */

/* FUN_00090c80 @ 0x00090c80   (est. cl4_slot_a8_get) */
void cl4_slot_a8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xa8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0xb0));
    cl4_cap_ref_enter();
}
/* FUN_00090cbc @ 0x00090cbc   (est. cl4_slot_a8_set) */
void cl4_slot_a8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xa8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0xb0);
    *(unsigned long *)((char *)cl4_ctx + 0xa8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0xb0) = aux;
    cl4_buf_release(old);
}
/* FUN_00090d00 @ 0x00090d00   (est. cl4_slot_a8_ref) */
cl4_pair_t cl4_slot_a8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xa8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xa8);
    return r;
}
/* FUN_00090db8 @ 0x00090db8   (est. cl4_slot_b8_get) */
void cl4_slot_b8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xb8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0xc0));
    cl4_cap_ref_enter();
}
/* FUN_00090df4 @ 0x00090df4   (est. cl4_slot_b8_set) */
void cl4_slot_b8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xb8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0xc0);
    *(unsigned long *)((char *)cl4_ctx + 0xb8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0xc0) = aux;
    cl4_buf_release(old);
}
/* FUN_00090e38 @ 0x00090e38   (est. cl4_slot_b8_ref) */
cl4_pair_t cl4_slot_b8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xb8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xb8);
    return r;
}
/* FUN_00090ef0 @ 0x00090ef0   (est. cl4_slot_c8_get) */
void cl4_slot_c8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xc8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0xd0));
    cl4_cap_ref_enter();
}
/* FUN_00090f2c @ 0x00090f2c   (est. cl4_slot_c8_set) */
void cl4_slot_c8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xc8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0xd0);
    *(unsigned long *)((char *)cl4_ctx + 0xc8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0xd0) = aux;
    cl4_buf_release(old);
}
/* FUN_00090f70 @ 0x00090f70   (est. cl4_slot_c8_ref) */
cl4_pair_t cl4_slot_c8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xc8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xc8);
    return r;
}
/* FUN_00091028 @ 0x00091028   (est. cl4_slot_d8_get) */
void cl4_slot_d8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xd8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0xe0));
    cl4_cap_ref_enter();
}
/* FUN_00091064 @ 0x00091064   (est. cl4_slot_d8_set) */
void cl4_slot_d8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xd8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0xe0);
    *(unsigned long *)((char *)cl4_ctx + 0xd8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0xe0) = aux;
    cl4_buf_release(old);
}
/* FUN_000910a8 @ 0x000910a8   (est. cl4_slot_d8_ref) */
cl4_pair_t cl4_slot_d8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xd8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xd8);
    return r;
}
/* FUN_00091104 @ 0x00091104   (est. cl4_slot_e8_get) */
void cl4_slot_e8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xe8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0xf0));
    cl4_cap_ref_enter();
}
/* FUN_00091140 @ 0x00091140   (est. cl4_slot_e8_set) */
void cl4_slot_e8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xe8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0xf0);
    *(unsigned long *)((char *)cl4_ctx + 0xe8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0xf0) = aux;
    cl4_buf_release(old);
}
/* FUN_00091184 @ 0x00091184   (est. cl4_slot_e8_ref) */
cl4_pair_t cl4_slot_e8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xe8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xe8);
    return r;
}
/* FUN_000911e0 @ 0x000911e0   (est. cl4_slot_f8_get) */
void cl4_slot_f8_get(void)
{
    cl4_slot_load((unsigned long *)((char *)cl4_ctx + 0xf8));
    cl4_buf_acquire(*(unsigned long *)((char *)cl4_ctx + 0x100));
    cl4_cap_ref_enter();
}
/* FUN_0009121c @ 0x0009121c   (est. cl4_slot_f8_set) */
void cl4_slot_f8_set(unsigned long v, unsigned long aux)
{
    cl4_slot_commit();
    cl4_slot_open((unsigned long *)((char *)cl4_ctx + 0xf8));
    unsigned long old = *(unsigned long *)((char *)cl4_ctx + 0x100);
    *(unsigned long *)((char *)cl4_ctx + 0xf8) = v;
    *(unsigned long *)((char *)cl4_ctx + 0x100) = aux;
    cl4_buf_release(old);
}
/* FUN_00091260 @ 0x00091260   (est. cl4_slot_f8_ref) */
cl4_pair_t cl4_slot_f8_ref(void)
{
    cl4_slot_ref((unsigned long *)((char *)cl4_ctx + 0xf8));
    cl4_pair_t r; r.lo = (unsigned long)&cl4_slot_ref_tag[0]; r.hi = (unsigned long)((char *)cl4_ctx + 0xf8);
    return r;
}

/* FUN_00661500 — vtable slot handler address stored into ctx+0x38. */
extern void cl4_vtable_61500(void);
/* FUN_0007c0b8 — capture the current self/context pointer. */
extern void cl4_self_capture(void);
/* FUN_00027724 — fetch a fatal/error dispatch entry. */
extern unsigned long cl4_fatal_entry(unsigned long a);
/* FUN_003a25d4 — release/put the previous object in a slot. */
extern void cl4_slot_put(unsigned long obj);
/* FUN_002a4ab4 / thunk_FUN_002acbb8 — obfuscation trace/error setup. */
extern void cl4_trace_prep(unsigned long a);
extern void cl4_trace_prep2(unsigned long a, unsigned long b);
/* FUN_001f0130 re-declared (cl4_cap_new). */

/* FUN_000902c4 @ 0x000902c4   (est. cl4_slot_40_init)
 * Ghidra: void FUN_000902c4(long param_1)
 * Initialise the endpoint/launcher context from the message object `param_1`:
 * stash the object, build the message object, wire the vtable, zero the cap
 * slots, then validate the object's message field (+0x90) and register an op
 * dispatch; on success reports the pair and clears the slots.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x90460/0x90464) on missing/invalid message. */
void cl4_slot_40_init(long param_1)
{
    char *self = cl4_ctx;
    *(long *)(self + 0x10) = param_1;
    unsigned long field40 = *(unsigned long *)(param_1 + 0x40);
    unsigned short field48 = *(unsigned short *)(param_1 + 0x48);
    unsigned long obj = cl4_msg_obj_new(0);
    cl4_zone_alloc(obj, 0x28, 7);
    cl4_buf_acquire((unsigned long)param_1);
    unsigned long built = cl4_msg_obj_build(field48, field40);
    *(unsigned long *)(self + 0x18) = built;
    *(unsigned long *)(self + 0x30) = obj;
    *(void **)(self + 0x38) = (void *)cl4_vtable_61500;
    unsigned long *slots = (unsigned long *)(self + 0x40);
    slots[0] = 0; slots[1] = 0; slots[2] = 0;
    long msg = *(long *)(self + 0x10);
    unsigned long frame[3];
    cl4_field_lock((unsigned long *)(msg + 0x90), &frame[0], 0, 0);
    if (*(long *)(msg + 0x90) == 0) cl4_trap(1, 0x90460);
    cl4_preinit();
    cl4_slot_store((unsigned long *)(*(long *)(self + 0x10) + 0x58), (unsigned long)frame);
    cl4_pair_t p1, p2;
    cl4_frame_capture(&frame[0], &p1.lo);
    cl4_pair_t (*cb1)(unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch1(p2.hi);
    p1 = cb1(p1.lo, p2.hi);
    unsigned long o2 = *(unsigned long *)(self + 0x30);
    unsigned long o4 = *(unsigned long *)(self + 0x38);
    cl4_frame_capture((unsigned long *)(self + 0x18), &o2);
    cl4_pair_t (*cb2)(unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch2(o4);
    p2 = cb2(o2, o4);
    if (p2.hi != 0) {
        cl4_error_report(p1.lo, p1.hi, p2.lo, p2.hi);
        cl4_buf_release((unsigned long)param_1);
        cl4_frame_restore(&frame[0]);
        cl4_field_lock((unsigned long *)slots, &frame[0], 1, 0);
        slots[0] = 0; slots[1] = 0; slots[2] = 0;
        return;
    }
    cl4_trap(1, 0x90464);
}

/* FUN_00090464 @ 0x00090464   (est. cl4_ep_register)
 * Ghidra: undefined1 FUN_00090464(void)
 * Register the endpoint: take the object at ctx+0x10's +0x50 field, capture
 * self, invoke the registration vtable method (+0x80 of ctx) with a
 * validate-dispatch callback and the 0x672870 frame; returns the callback's
 * byte result.
 * Confidence: low */
unsigned char cl4_ep_register(void)
{
    char *self = cl4_ctx;
    unsigned long obj = *(unsigned long *)(*(long *)(self + 0x10) + 0x50);
    unsigned char result = 0;
    cl4_self_capture();
    void (*cb)(unsigned char *, void (*)(void), unsigned long *, unsigned long) =
        (void (*)(unsigned char *, void (*)(void), unsigned long *, unsigned long))
            *(unsigned long *)((char *)cl4_ctx + 0x80);
    cl4_buf_acquire(obj);
    unsigned long frame[3];
    cb(&result, (void (*)(void))cl4_ep_validate_dispatch_1, &frame[0], 0x672870);
    cl4_buf_release(obj);
    return result;
}

/* FUN_000907b0 / FUN_000907b4 @ 0x907b0/0x907b4 (est. cl4_ep_validate_dispatch)
 * Dispatch cl4_ep_validate with the context fields +0x10/+0x18/+0x20.
 * Confidence: high; duplicate bodies. */
void cl4_ep_validate_dispatch_1(void)
{
    cl4_ep_validate((unsigned char *)((char *)cl4_ctx + 0x10),
                    *(unsigned long *)((char *)cl4_ctx + 0x18),
                    *(unsigned char *)((char *)cl4_ctx + 0x20), 0);
}
void cl4_ep_validate_dispatch_2(void)
{
    cl4_ep_validate((unsigned char *)((char *)cl4_ctx + 0x10),
                    *(unsigned long *)((char *)cl4_ctx + 0x18),
                    *(unsigned char *)((char *)cl4_ctx + 0x20), 0);
}

/* FUN_00090508 @ 0x00090508   (est. cl4_ep_validate)
 * Ghidra: void FUN_00090508(undefined1 *param_1, long param_2, undefined8 param_3, undefined1 param_4)
 * Validate the endpoint object `param_2` for capability `param_3`: verify the
 * message field is present, run the op validation, and on success mark
 * *param_1 = 1 (the endpoint is usable). Fatal on a failed / missing message.
 * Confidence: low
 * Notes: fatal string "InternalExclaveLauncher::External"; canary guarded. */
void cl4_ep_validate(unsigned char *param_1, unsigned long param_2,
                     unsigned long param_3, unsigned char param_4)
{
    unsigned long canary = CANARY;
    unsigned long frame[3], local_c0;
    cl4_field_lock((unsigned long *)(param_2 + 0x40), &frame[0], 0, 0);
    if (*(long *)(param_2 + 0x40) == 0) {
        long msg = *(long *)(param_2 + 0x10);
        cl4_slot_store((unsigned long *)(msg + 0x58), (unsigned long)&local_c0);
        cl4_pair_t p1;
        cl4_frame_capture(&local_c0, &p1.lo);
        cl4_pair_t (*cb)(unsigned long, unsigned long) =
            (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch1(p1.hi);
        p1 = cb(p1.lo, p1.hi);
        unsigned long frame2[3];
        cl4_field_lock((unsigned long *)(param_2 + 0x40), &frame2[0], 0x21, 0);
        p1.lo = cl4_cap_check1(p1.lo, p1.hi, param_2 + 0x40);
        cl4_buf_frame_teardown(&frame2[0]);
        cl4_frame_restore(&local_c0);
        int bad = cl4_status_cmp(p1.lo, p1.hi);
        if ((bad != 0) || (*(long *)(param_2 + 0x40) == 0)) {
            unsigned long code = 0, detail = 0xe000000000000000ull;
            cl4_trace_prep(0x3c);
            cl4_trace_prep2(0xd00000000000003aull, 0x80000000005c1020ull);
            code = *(unsigned long *)(msg + 0x40);
            cl4_fatal_entry(0x671848);
            cl4_trace_prep2(0x677790, 0x671848);
            cl4_trace_prep2(0, 0);
            cl4_slot_put(0);
            cl4_fatal("Fatal error", 0xb, 2, code, detail,
                      "InternalExclaveLauncher::External", 0x39, 2, 0x56, 0);
        }
    }
    long msg2 = *(long *)(param_2 + 0x10);
    unsigned long frame3[3];
    cl4_field_lock((unsigned long *)(msg2 + 0x90), &frame3[0], 0, 0);
    long m90 = *(long *)(msg2 + 0x90);
    if (m90 == 0) cl4_trap(1, 0x906e4);
    unsigned long ok = cl4_obj_validate((unsigned long)m90, param_3);
    if ((ok & 1) == 0) {
        unsigned long lc[2], tri[3];
        lc[0] = lc[1] = 0;
        tri[0] = *(unsigned long *)(param_2 + 0x50);
        tri[1] = *(unsigned long *)(param_2 + 0x48);
        tri[2] = *(unsigned long *)(param_2 + 0x40);
        cl4_cap_check2(&tri[0], param_3, param_4, &lc[0]);
        if (cl4_status_cmp(0, 0) == 0) {
            if ((lc[0] & 1) == 0) {
                *param_1 = 1;
                goto done;
            }
            tri[0] = *(unsigned long *)(param_2 + 0x50);
            tri[1] = *(unsigned long *)(param_2 + 0x48);
            tri[2] = *(unsigned long *)(param_2 + 0x40);
            cl4_cap_check3(&tri[0], 0);
        }
    }
    *param_1 = 0;
done:
    if (canary == CANARY)
        return;
    cl4_stack_canary_fail();
}

/* FUN_000907d0 @ 0x000907d0   (est. cl4_ep_unregister)
 * Unregister the endpoint: take ctx+0x10's +0x50 object, capture self, call
 * the +0x80 vtable teardown with the 0x909e4 callback, then release the
 * object and restore the frame.
 * Confidence: low */
void cl4_ep_unregister(void)
{
    char *self = cl4_ctx;
    unsigned long obj = *(unsigned long *)(*(long *)(self + 0x10) + 0x50);
    cl4_self_capture();
    void (*cb)(void (*)(void)) =
        (void (*)(void (*)(void)))*(unsigned long *)((char *)cl4_ctx + 0x80);
    cl4_buf_acquire(obj);
    cb((void (*)(void))cl4_ep_setup_dispatch);
    cl4_buf_release(obj);
    cl4_buf_release(*(unsigned long *)(self + 0x10));
    cl4_frame_restore((unsigned long *)(self + 0x18));
}

/* FUN_0009087c @ 0x0009087c   (est. cl4_ep_setup)
 * Ghidra: void FUN_0009087c(long param_1)
 * Set up the endpoint object `param_1`: create a fresh capability, replace
 * the object's +0x88 message field, clear the slot block, and run the two op
 * dispatches; report the error pair if the second fails.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x909e4) on failure. */
void cl4_ep_setup(long param_1)
{
    long msg = *(long *)(param_1 + 0x10);
    unsigned long newcap = cl4_cap_new((unsigned long)cl4_obf_buffer, 0x677790, 0x660430, 0x6718b8);
    unsigned long frame[3];
    cl4_field_lock((unsigned long *)(msg + 0x88), &frame[0], 1, 0);
    unsigned long old = *(unsigned long *)(msg + 0x88);
    *(unsigned long *)(msg + 0x88) = newcap;
    cl4_slot_put(old);
    unsigned long frame2[3];
    cl4_field_lock((unsigned long *)(param_1 + 0x40), &frame2[0], 0x21, 0);
    cl4_list_clear();
    cl4_buf_frame_teardown(&frame2[0]);
    cl4_slot_store((unsigned long *)(msg + 0x58), (unsigned long)frame);
    cl4_pair_t p1, p2;
    cl4_frame_capture(&frame[0], &p1.lo);
    cl4_pair_t (*cb1)(unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch1(p1.hi);
    p1 = cb1(p1.lo, p1.hi);
    unsigned long frame3[3];
    cl4_slot_store((unsigned long *)(msg + 0x10), (unsigned long)frame3);
    cl4_frame_capture(&frame3[0], &p2.lo);
    cl4_pair_t (*cb2)(unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch2(p2.hi);
    p2 = cb2(p2.lo, p2.hi);
    if (p2.hi != 0) {
        cl4_error_report(p1.lo, p1.hi, p2.lo, p2.hi);
        cl4_frame_restore(&frame3[0]);
        cl4_frame_restore(&frame[0]);
        return;
    }
    cl4_trap(1, 0x909e4);
}

/* FUN_000909e4 / FUN_000909e8 @ 0x909e4/0x909e8 (est. cl4_ep_setup_dispatch) —
 * dispatch cl4_ep_setup. Confidence: high */
void cl4_ep_setup_dispatch(void) { cl4_ep_setup(0); }
void cl4_ep_setup_dispatch2(void) { cl4_ep_setup(0); }

/* FUN_00090a00 / FUN_00090a04 @ 0x90a00/0x90a04 (est. cl4_ep_unregister2) —
 * unregister then fast-teardown. Confidence: high */
void cl4_ep_unregister2_1(void) { cl4_ep_unregister(); cl4_buf_release_fast(); }
void cl4_ep_unregister2_2(void) { cl4_ep_unregister(); cl4_buf_release_fast(); }

/* FUN_00090a28 / FUN_00090a2c @ 0x90a28/0x90a2c (est. cl4_store_10_a/b) —
 * store param into the context +0x10 field. Confidence: high */
void cl4_store_10_a(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x10), v); }
void cl4_store_10_b(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x10), v); }

/* FUN_00090a48 @ 0x00090a48   (est. cl4_obj_or_clear)
 * Ghidra: void FUN_00090a48(undefined8 *param_1)
 * If the object resolved from the ctx+0x98 slot is non-null, store param_1
 * into its +0x18 field and release it; otherwise zero all five fields of
 * param_1.
 * Confidence: medium */
void cl4_obj_or_clear(unsigned long *param_1)
{
    long obj = cl4_obj_from_slot((unsigned long *)((char *)cl4_ctx + 0x98));
    if (obj != 0) {
        cl4_slot_store((unsigned long *)(obj + 0x18), *param_1);
        cl4_buf_release((unsigned long)obj);
        return;
    }
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[0] = 0;
    param_1[3] = 0;
    param_1[2] = 0;
}

/* FUN_00090aa4 / FUN_00090aa8 @ 0x90aa4/0x90aa8 (est. cl4_store_58b_a/b) —
 * store param into the ctx+0x58 field. Confidence: high */
void cl4_store_58b_a(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x58), v); }
void cl4_store_58b_b(unsigned long v) { cl4_slot_store((unsigned long *)((char *)cl4_ctx + 0x58), v); }

/* bit-reverse a 64-bit word (6 step swap sequence). */
static unsigned long cl4_bitreverse64(unsigned long x)
{
    x = (x & 0xaaaaaaaaaaaaaaaaull) >> 1 | (x & 0x5555555555555555ull) << 1;
    x = (x & 0xccccccccccccccccull) >> 2 | (x & 0x3333333333333333ull) << 2;
    x = (x & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (x & 0x0f0f0f0f0f0f0f0full) << 4;
    x = (x & 0xff00ff00ff00ff00ull) >> 8 | (x & 0x00ff00ff00ff00ffull) << 8;
    x = (x & 0xffff0000ffff0000ull) >> 16 | (x & 0x0000ffff0000ffffull) << 16;
    x = (x >> 32) | (x << 32);
    return x;
}

/* FUN_00091314 @ 0x00091314   (est. cl4_bitmap_scan)
 * Ghidra: void FUN_00091314(undefined8 param_1, long param_2, code *param_3)
 * Scan the endpoint's bitmap (a bitmap array at the object +0x40) and, for
 * every entry tagged 0x06 (a pending notification), enqueue its payload into
 * the shared notify buffer (DAT_00657798). The bitmap is scanned one 64-bit
 * word at a time, using bit-reversal to visit set bits. When the scan
 * completes, invoke the callback (param_3) with the buffer.
 * Confidence: medium
 * Notes: uses LZCOUNT (clz) on the bit-reversed+swapped word; grows the
 * notify buffer via cl4_notify_grow. */
void cl4_bitmap_scan(unsigned long param_1, long param_2, void (*param_3)(unsigned long, unsigned long))
{
    unsigned long frame[3];
    cl4_field_lock((unsigned long *)(param_2 + 0x88), &frame[0], 0, 0);
    long obj = *(long *)(param_2 + 0x88);
    unsigned long nwords = 1ul << ((unsigned long)*(unsigned char *)(obj + 0x20) & 0x3f);
    unsigned long mask = 0xffffffffffffffffull;
    if ((*(unsigned char *)(obj + 0x20) & 0x3f) < 6)
        mask = ~(-1ul << (nwords & 0x3f));
    unsigned long word = mask & *(unsigned long *)(obj + 0x40);
    cl4_buf_acquire((unsigned long)obj);
    long wi = 0;
    for (;;) {
        while (word != 0) {
            unsigned long rev = cl4_bitreverse64(word);
            word = word - 1 & word;              /* clear lowest set bit */
            long base = *(long *)(obj + 0x38) +
                        __builtin_clzll(rev >> 0x20 | rev << 0x20) * 0x10;
            if (*(char *)(base + wi * 0x400) == '\x06') {
                unsigned long payload = *(unsigned long *)(base + wi * 0x400 + 8);
                cl4_ref_kind(payload, 2);
                cl4_notify_append();
                unsigned long idx = cl4_notify_idx;
                unsigned long next = cl4_notify_idx + 1;
                if (cl4_notify_cap >> 1 <= cl4_notify_idx)
                    cl4_notify_grow(1 < cl4_notify_cap, next, 1);
                cl4_notify_idx = next;
                ((unsigned long *)&cl4_obf_buffer[0x20])[idx] = payload;
                cl4_buf_release(0);
            }
        }
        if (SCARRY8(wi, 1)) break;
        wi = wi + 1;
        if ((long)((nwords + 0x3f) >> 6) <= wi) {
            cl4_buf_release((unsigned long)obj);
            param_3(param_1, (unsigned long)cl4_obf_buffer);
            cl4_buf_release((unsigned long)cl4_obf_buffer);
            return;
        }
        word = ((unsigned long *)(obj + 0x40))[wi];
    }
    cl4_trap(1, 0x914c0);
}

/* FUN_000914c0 / FUN_000914c4 @ 0x914c0/0x914c4 (est. cl4_bitmap_scan_dispatch)
 * Dispatch cl4_bitmap_scan with the context fields. Confidence: high */
void cl4_bitmap_scan_dispatch(void)
{
    cl4_bitmap_scan(*(unsigned long *)((char *)cl4_ctx + 0x18),
                    *(unsigned long *)((char *)cl4_ctx + 0x20),
                    (void (*)(unsigned long, unsigned long))*(unsigned long *)((char *)cl4_ctx + 0x28));
}
void cl4_bitmap_scan_dispatch2(void)
{
    cl4_bitmap_scan(*(unsigned long *)((char *)cl4_ctx + 0x18),
                    *(unsigned long *)((char *)cl4_ctx + 0x20),
                    (void (*)(unsigned long, unsigned long))*(unsigned long *)((char *)cl4_ctx + 0x28));
}

/* FUN_000912a4 @ 0x000912a4   (est. cl4_ep_dispatch_setup)
 * Ghidra: void FUN_000912a4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Invoke the endpoint's +0x80 vtable method (of the object at ctx+0x50) with
 * the bitmap-scan dispatch callback and a stack frame.
 * Confidence: low */
void cl4_ep_dispatch_setup(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long frame[2];
    ((void (*)(void (*)(void), unsigned long *))
        *(unsigned long *)(*(unsigned long *)((char *)cl4_ctx + 0x50) + 0x80))
            (cl4_bitmap_scan_dispatch, &frame[0]);
}

/* FUN_000914e0 @ 0x000914e0   (est. cl4_ep_create)
 * Ghidra: undefined8 FUN_000914e0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Allocate a zone object, then run the launcher init; returns the zone
 * handle. Confidence: medium */
unsigned long cl4_ep_create(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4)
{
    unsigned long h = cl4_zone_alloc(0, 0, 0);
    cl4_ep_launcher_init(p1, p2, (unsigned short)p3, p4);
    return h;
}

/* Out-of-slice endpoint handlers referenced by the binding table. */
extern void cl4_ep_handler_92774(void);   /* FUN_00092774 */
extern void cl4_ep_handler_928c4(void);   /* FUN_000928c4 */
/* FUN_0000456c — default fatal/slot handler used for two slots. */
extern void cl4_vtable_0456c(void);

/* FUN_00091550 @ 0x00091550   (est. cl4_ep_launcher_init)
 * Ghidra: void FUN_00091550(undefined8 param_1, undefined8 param_2,
 *   undefined2 param_3, undefined8 param_4)
 * Initialise the Exclave-Launcher endpoint object: stash config, allocate the
 * slot/vspace block, create the message cap, then register a 9-entry
 * endpoint binding table (asid/conclave/IPC handlers) and run the lookup
 * dispatch. On success store the result in ctx+0x90; on failure tear down the
 * whole object block.
 * Confidence: high (verified 2026-08-12: binding handlers realigned to disassembly,
 *   success branch condition restored, tail intermediate calls + b9 restored) */
void cl4_ep_launcher_init(unsigned long p1, unsigned long p2, unsigned short p3,
                          unsigned long p4)
{
    char *self = cl4_ctx;
    long x21;                 /* unaff_x21: caller-set success flag (callee-saved input) */
    long x16r;                /* extraout_x16: opaque register base for the indirect dispatch */
    *(unsigned long *)(self + 0x90) = 0;
    cl4_field_reset((unsigned long *)(self + 0x98), 0);
    *(void **)(self + 0xa8) = (void *)cl4_fatal_ep_8a;  *(unsigned long *)(self + 0xb0) = 0;
    *(void **)(self + 0xb8) = (void *)cl4_fatal_ep_8d;  *(unsigned long *)(self + 0xc0) = 0;
    *(void **)(self + 0xc8) = (void *)cl4_fatal_ep_90;  *(unsigned long *)(self + 0xd0) = 0;
    *(void **)(self + 0xd8) = (void *)cl4_fatal_ep_93;  *(unsigned long *)(self + 0xe0) = 0;
    *(void **)(self + 0xe8) = (void *)cl4_vtable_0456c; *(unsigned long *)(self + 0xf0) = 0;
    *(void **)(self + 0xf8) = (void *)cl4_vtable_0456c; *(unsigned long *)(self + 0x100) = 0;
    *(unsigned long *)(self + 0x38) = p1;
    *(unsigned long *)(self + 0x40) = p2;
    *(unsigned short *)(self + 0x48) = p3;
    unsigned long h = cl4_class_handle(0);
    long slot = cl4_zone_alloc(h, 0x18, 7);
    unsigned long blk = cl4_alloc_bytes(0x10, (unsigned long)-1);
    *(unsigned long *)(slot + 0x10) = blk;
    *(long *)(self + 0x50) = slot;
    unsigned long newcap = cl4_cap_new((unsigned long)cl4_obf_buffer, 0x677790, 0x660430, 0x6718b8);
    *(unsigned long *)(self + 0x88) = newcap;
    unsigned long frame248[6];
    cl4_slot_store((unsigned long *)p4, (unsigned long)(self + 0x10));
    cl4_slot_store((unsigned long *)(self + 0x10), (unsigned long)frame248);
    unsigned long eh = cl4_handle_fetch(0);
    cl4_zone_alloc(eh, 0x52, 7);
    long ep = cl4_endpoint_new(0xd, (unsigned long *)frame248);
    if (x21 == 0) {          /* unaff_x21 == 0 (success path) */
        *(long *)(self + 0x80) = ep;
        unsigned long ep48 = *(unsigned long *)(ep + 0x48);
        cl4_slot_store((unsigned long *)p4, (unsigned long)frame248);
        unsigned long oc = cl4_op_class(0);
        unsigned long op3 = cl4_zone_alloc(oc, 0x48, 7);
        op3 = cl4_op_attach(ep48, (unsigned long *)frame248, p2, op3);
        *(unsigned long *)(self + 0x70) = oc;
        *(unsigned long *)(self + 0x78) = 0x65f9a0;
        *(unsigned long *)(self + 0x58) = op3;
        unsigned long frame2[3];
        cl4_cap_ref_setup((unsigned long *)(self + 0x90), &frame2[0]);
        cl4_field_lock(0, 0, 0, 0);
        *(unsigned long *)(self + 0x90) = 0;
        cl4_field_reset1((unsigned long *)(self + 0x98), 0);
        *(unsigned char *)(self + 0xa0) = 0;

        /* Register the 9 endpoint bindings. */
        unsigned long fetch;
        unsigned long b1, b2, b3, b4, b5, b6, b7, b8, b9;
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b1 = cl4_binding_describe(0x939fc, cl4_op_call3, 0x65fd60, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b2 = cl4_binding_describe(0x93a20, cl4_op_call1, 0x65fd88, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b3 = cl4_binding_describe(0x93a28, cl4_op_call1, 0x65fdb0, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b4 = cl4_binding_describe(0x93a30, cl4_op_call0, 0x65fdd8, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b5 = cl4_binding_describe(0x93a38, cl4_ep_send, 0x65fe00, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b6 = cl4_binding_describe(0x93a40, cl4_ep_send2, 0x65fe28, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b7 = cl4_binding_describe(0x93a48, cl4_ep_send3, 0x65fe50, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b8 = cl4_binding_describe(0x93a50, cl4_ep_handler_92774, 0x65fe78, fetch);
        fetch = cl4_cap_ref_fetch(); cl4_cap_ref_advance();
        b9 = cl4_binding_describe(0x93a58, cl4_ep_handler_928c4, 0x65fea0, fetch);

        cl4_buf_acquire(op3);
        cl4_buf_acquire(b2); cl4_buf_acquire(b3); cl4_buf_acquire(b4);
        cl4_buf_acquire(b5); cl4_buf_acquire(b6); cl4_buf_acquire(b7);
        cl4_buf_acquire(b8); cl4_buf_acquire(b9);
        cl4_buf_release(b9); cl4_buf_release(b8); cl4_buf_release(b7);
        cl4_buf_release(b6); cl4_buf_release(b5); cl4_buf_release(b4);
        cl4_buf_release(b3); cl4_buf_release(b2); cl4_buf_release(op3);

        unsigned long desc[9];
        desc[0] = b1; desc[1] = b2; desc[2] = b3; desc[3] = b4;
        desc[4] = b5; desc[5] = b6; desc[6] = b7; desc[7] = b8; desc[8] = b9;
        /* tail (faithful to decompile): self-capture, indirect dispatch through
         * *(x16r+0x60), frame capture, op dispatch, then the object lookups. */
        unsigned long slot = *(unsigned long *)(self + 0x50);
        cl4_self_capture();                                   /* FUN_000027e8 */
        {   unsigned long (*fp)(void) = *(unsigned long (**)(void))(x16r + 0x60);
            cl4_buf_acquire(slot);                            /* FUN_0036b270 */
            unsigned long iret = fp();                        /* (*pcVar20)() */
            cl4_buf_release(slot);                            /* FUN_0036b118 */
            unsigned long lk = cl4_obj_lookup1(iret, (unsigned long *)desc); /* FUN_0002887c */
            unsigned long p38 = *(unsigned long *)(self + 0x38);
            unsigned long p70 = *(unsigned long *)(self + 0x70);
            unsigned long p78 = *(unsigned long *)(self + 0x78);
            cl4_frame_capture((unsigned long *)(self + 0x58), (unsigned long *)p70);   /* FUN_0006a4c0 */
            cl4_pair_t (*fp2)(unsigned long, unsigned long) =
                (cl4_pair_t (*)(unsigned long, unsigned long))cl4_op_dispatch1(p78); /* FUN_0008644c */
            cl4_pair_t pair = fp2(p70, p78);                  /* (*pcVar20)(uVar1,uVar3) */
            unsigned long r = cl4_obj_lookup2(p38, pair.lo, pair.hi, lk); /* FUN_00028b14 */
            cl4_binding_release(b1); cl4_binding_release(b2); cl4_binding_release(b3);
            cl4_binding_release(b4); cl4_binding_release(b5); cl4_binding_release(b6);
            cl4_binding_release(b7); cl4_binding_release(b8); cl4_binding_release(b9);
            cl4_frame_restore((unsigned long *)p4);
            *(unsigned long *)(self + 0x90) = r;
        }
    } else {
        cl4_frame_restore((unsigned long *)p4);
        cl4_frame_restore((unsigned long *)(self + 0x10));
        cl4_buf_release(*(unsigned long *)(self + 0x50));
        cl4_slot_put(*(unsigned long *)(self + 0x88));
        cl4_slot_release((unsigned long *)(self + 0x98));
        cl4_buf_release(*(unsigned long *)(self + 0xb0));
        cl4_buf_release(*(unsigned long *)(self + 0xc0));
        cl4_buf_release(*(unsigned long *)(self + 0xd0));
        cl4_buf_release(*(unsigned long *)(self + 0xe0));
        cl4_buf_release(*(unsigned long *)(self + 0xf0));
        cl4_buf_release(*(unsigned long *)(self + 0x100));
        cl4_slot_block_teardown();
    }
}

/* static helper: build a binding descriptor and register it. */
static unsigned long cl4_binding_describe(unsigned long tag, void *handler,
                                          unsigned long str, unsigned long fetch)
{
    unsigned long desc[6];
    desc[0] = 0x6ad3a8;
    desc[1] = cl4_binding_handle;
    desc[2] = (unsigned long)handler;
    desc[3] = str;
    desc[4] = tag;
    desc[5] = fetch;
    return cl4_binding_register(desc);
}

/* ------------------------------------------------------------------ *
 * Endpoint op-call thunks (guarded indirect calls).
 * ------------------------------------------------------------------ */
/* FUN_00091f8c @ 0x00091f8c   (est. cl4_op_call3)
 * Call the op callback at p1+0x20 (3 args) under the lock at p1+0x28.
 * Confidence: high */
cl4_pair_t cl4_op_call3(long p1, unsigned long p2, unsigned long p3, unsigned long p4)
{
    cl4_pair_t (*cb)(unsigned long, unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long, unsigned long))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb(p2, p3, p4);
    cl4_buf_release(lk);
    return r;
}
/* FUN_000920ec @ 0x000920ec   (est. cl4_op_call1) — 1-arg callback. */
cl4_pair_t cl4_op_call1(long p1, unsigned long p2)
{
    cl4_pair_t (*cb)(unsigned long) =
        (cl4_pair_t (*)(unsigned long))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb(p2);
    cl4_buf_release(lk);
    return r;
}
/* FUN_00092270 @ 0x00092270   (est. cl4_op_call0) — 0-arg callback. */
cl4_pair_t cl4_op_call0(long p1)
{
    cl4_pair_t (*cb)(void) = (cl4_pair_t (*)(void))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb();
    cl4_buf_release(lk);
    return r;
}
/* FUN_00092394 @ 0x00092394   (est. cl4_ep_send) — 3-arg callback. */
cl4_pair_t cl4_ep_send(long p1, unsigned long p2, unsigned long p3, unsigned long p4)
{
    cl4_pair_t (*cb)(unsigned long, unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long, unsigned long))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb(p2, p3, p4);
    cl4_buf_release(lk);
    return r;
}
/* FUN_000924d4 @ 0x000924d4   (est. cl4_ep_send2) — 2-arg callback. */
cl4_pair_t cl4_ep_send2(long p1, unsigned long p2, unsigned long p3)
{
    cl4_pair_t (*cb)(unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb(p2, p3);
    cl4_buf_release(lk);
    return r;
}
/* FUN_0009261c @ 0x0009261c   (est. cl4_ep_send3) — 4-arg callback. */
cl4_pair_t cl4_ep_send3(long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5)
{
    cl4_pair_t (*cb)(unsigned long, unsigned long, unsigned long, unsigned long) =
        (cl4_pair_t (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long *)(p1 + 0x20);
    unsigned long lk = *(unsigned long *)(p1 + 0x28);
    cl4_buf_acquire(lk);
    cl4_pair_t r = cb(p2, p3, p4, p5);
    cl4_buf_release(lk);
    return r;
}

/* ------------------------------------------------------------------ *
 * Endpoint wrapper dispatches (status-reporting).
 * ------------------------------------------------------------------ */
/* FUN_00092000 @ 0x00092000   (est. cl4_ep_disconnect)
 * Disconnect an endpoint: validate the +0x88 message cap then unmap the
 * endpoint; report status (1 = no object, 4 = validate failed, 0 = ok).
 * Confidence: low */
void cl4_ep_disconnect(unsigned long param_1, long param_2)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(param_2 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(param_2 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0x88), &frame[0], 0x20, 0);
        cl4_op_validate(param_1, *(unsigned long *)(obj + 0x88));
        cl4_buf_frame_teardown(&frame[0]);
        if (/* validate result */ 0) {
            status = 4;
        } else {
            cl4_buf_release((unsigned long)obj);
            cl4_field_lock((unsigned long *)(obj + 0x88), &frame[0], 0x21, 0);
            cl4_endpoint_unmap(param_1);
            cl4_buf_frame_teardown(&frame[0]);
            cl4_buf_release((unsigned long)obj);
            status = 0;
        }
        cl4_buf_release((unsigned long)obj);
    }
    cl4_status_report(status);
}

/* FUN_00092144 @ 0x00092144   (est. cl4_ep_check_status)
 * Query the endpoint's +0xf8 slot callback; status 1 (no object) or 4
 * (callback failed). Confidence: low */
void cl4_ep_check_status(unsigned long param_1, long param_2)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(param_2 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(param_2 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0xf8), &frame[0], 0, 0);
        unsigned long (*cb)(unsigned long) = (unsigned long (*)(unsigned long))*(unsigned long *)(obj + 0xf8);
        unsigned long lk = *(unsigned long *)(obj + 0x100);
        cl4_buf_acquire(lk);
        unsigned long r = cb(param_1);
        cl4_buf_release(lk);
        cl4_buf_release((unsigned long)obj);
        status = 0;
        if ((r & 1) == 0) status = 4;
    }
    cl4_status_report(status);
}

/* FUN_000921f4 @ 0x000921f4   (est. cl4_ep_mark)
 * Mark the endpoint's +0xa0 flag byte set. Reports (obj == NULL).
 * Confidence: medium */
void cl4_ep_mark(long param_1)
{
    unsigned long frame[3];
    cl4_field_lock((unsigned long *)(param_1 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(param_1 + 0x10));
    if (obj != 0) {
        cl4_field_lock((unsigned long *)(obj + 0xa0), &frame[0], 1, 0);
        *(unsigned char *)(obj + 0xa0) = 1;
        cl4_buf_release((unsigned long)obj);
    }
    cl4_status_report(obj == 0);
}

/* FUN_000922c0 @ 0x000922c0   (est. cl4_ep_send_a8)
 * Send through the endpoint's +0xa8 slot callback (3 args); status 1/4.
 * Confidence: low */
void cl4_ep_send_a8(unsigned long p1, long p2, unsigned long p3, long p4)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(p4 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(p4 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0xa8), &frame[0], 0, 0);
        if (p2 < 0) cl4_trap(1, 0x92394);
        unsigned long (*cb)(unsigned long, long, unsigned long) =
            (unsigned long (*)(unsigned long, long, unsigned long))*(unsigned long *)(obj + 0xa8);
        unsigned long lk = *(unsigned long *)(obj + 0xb0);
        cl4_buf_acquire(lk);
        unsigned long r = cb(p1, p2, p3);
        cl4_buf_release(lk);
        cl4_buf_release((unsigned long)obj);
        status = 0;
        if ((r & 1) == 0) status = 4;
    }
    cl4_status_report(status);
}

/* FUN_00092408 @ 0x00092408   (est. cl4_ep_send_b8) — +0xb8 slot, 2 args. */
void cl4_ep_send_b8(unsigned long p1, long p2, long p3)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(p3 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(p3 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0xb8), &frame[0], 0, 0);
        if (p2 < 0) cl4_trap(1, 0x924d4);
        unsigned long (*cb)(unsigned long, long) =
            (unsigned long (*)(unsigned long, long))*(unsigned long *)(obj + 0xb8);
        unsigned long lk = *(unsigned long *)(obj + 0xc0);
        cl4_buf_acquire(lk);
        unsigned long r = cb(p1, p2);
        cl4_buf_release(lk);
        cl4_buf_release((unsigned long)obj);
        status = 0;
        if ((r & 1) == 0) status = 4;
    }
    cl4_status_report(status);
}

/* FUN_00092538 @ 0x00092538   (est. cl4_ep_send_c8) — +0xc8 slot, 4 args. */
void cl4_ep_send_c8(unsigned long p1, long p2, unsigned long p3, unsigned long p4, long p5)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(p5 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(p5 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0xc8), &frame[0], 0, 0);
        if (p2 < 0) cl4_trap(1, 0x9261c);
        unsigned long (*cb)(unsigned long, long, unsigned long, unsigned long) =
            (unsigned long (*)(unsigned long, long, unsigned long, unsigned long))*(unsigned long *)(obj + 0xc8);
        unsigned long lk = *(unsigned long *)(obj + 0xd0);
        cl4_buf_acquire(lk);
        unsigned long r = cb(p1, p2, p3, p4);
        cl4_buf_release(lk);
        cl4_buf_release((unsigned long)obj);
        status = 0;
        if ((r & 1) == 0) status = 4;
    }
    cl4_status_report(status);
}

/* FUN_00092698 @ 0x00092698   (est. cl4_ep_send4) — +0xd8 slot, 4 args. */
void cl4_ep_send4(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, long p5)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(p5 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(p5 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        cl4_field_lock((unsigned long *)(obj + 0xd8), &frame[0], 0, 0);
        unsigned long (*cb)(unsigned long, unsigned long, unsigned long, unsigned long) =
            (unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long *)(obj + 0xd8);
        unsigned long lk = *(unsigned long *)(obj + 0xe0);
        cl4_buf_acquire(lk);
        unsigned long r = cb(p1, p2, p3, p4);
        cl4_buf_release(lk);
        cl4_buf_release((unsigned long)obj);
        status = 0;
        if ((r & 1) == 0) status = 4;
    }
    cl4_status_report(status);
}

/* FUN_00091dbc @ 0x00091dbc   (est. cl4_ep_connect)
 * Ghidra: void FUN_00091dbc(undefined8 param_1, undefined8 param_2,
 *   undefined8 param_3, long param_4)
 * Connect to an endpoint: resolve the object from the param_4+0x10 slot,
 * validate its +0x88 message cap, and if valid create a fresh endpoint
 * object bound to the asid/conclave/pa tuple; report 0 on success / 1 on
 * failure.
 * Confidence: low
 * Notes: fatal init-report string
 *   s_init_endpoint_asid_conclaveId_pa_005c0fc0. */
void cl4_ep_connect(unsigned long p1, unsigned long p2, unsigned long p3, long p4)
{
    unsigned long frame[3];
    unsigned long status;
    cl4_field_lock((unsigned long *)(p4 + 0x10), &frame[0], 0, 0);
    long obj = cl4_obj_from_slot((unsigned long *)(p4 + 0x10));
    if (obj == 0) {
        status = 1;
    } else {
        long obj2 = cl4_obj_from_slot((unsigned long *)(obj + 0x98));
        if (obj2 == 0) {
            status = 1;
        } else {
            cl4_field_lock((unsigned long *)(obj + 0x88), &frame[0], 0x20, 0);
            cl4_op_validate(p1, *(unsigned long *)(obj + 0x88));
            cl4_buf_frame_teardown(&frame[0]);
            if (/* validate ok */ 0) {
                cl4_slot_store((unsigned long *)(obj2 + 0x18), (unsigned long)frame);
                unsigned long eh = cl4_handle_fetch(0);
                cl4_zone_alloc(eh, 0x52, 7);
                long ep = cl4_endpoint_new(p2, (unsigned long *)frame);
                cl4_field_lock((unsigned long *)(obj + 0x88), &frame[0], 0x21, 0);
                cl4_buf_acquire((unsigned long)ep);
                cl4_endpoint_bind(p2, (unsigned long)ep, p1);
                cl4_buf_frame_teardown(&frame[0]);
                cl4_buf_acquire((unsigned long)ep);
                cl4_endpoint_init_report(0xd000000000000019ull, 0x80000000005c0f80ull,
                                         "__AppleInternal__/Library/BuildRoot", 0x105, 2,
                                         "init_endpoint_asid/conclaveId/pa", 0x33, 2,
                                         0xc5, (unsigned long)ep, p3);
                cl4_buf_release((unsigned long)obj);
                cl4_buf_release((unsigned long)obj2);
                status = 0;
            } else {
                cl4_buf_release((unsigned long)obj);
                cl4_buf_release((unsigned long)obj2);
                status = 1;
            }
        }
        cl4_buf_release((unsigned long)obj);
    }
    cl4_status_report(status);
}
